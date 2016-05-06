/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : UL_om_def.h
  版 本 号   : 初稿
  作    者   : l00131321
  生成日期   : 2011年3月15日
  最近修改   :
  功能描述   : 定义上行模块OM需要上报的结构体,该文件最终会交付给HiStudio使用
  函数列表   :
  修改历史   :
  1.日    期   : 2011年3月15日
    作    者   : l00131321
    修改内容   : 创建文件
  -------------------------------------------------------------------------------
  2.日    期   : 2011年6月28日
    作    者   : l00131321
    修改内容   : [DTS2011062802382]OM新增需求合入
 -------------------------------------------------------------------------------
  3.日    期   : 2011年8月23日
    作    者   : l00131321
    修改内容   : [DTS2011082402841]合入OM 统计MAC数据无效
 -------------------------------------------------------------------------------
  4.日    期   : 2011年11月16日
   作    者   : sunyanjie
   修改内容   : [DTS2011111602553]同步合入V1问题单
-------------------------------------------------------------------------------
  5.日    期   : 2011年11月24日
    作    者   : c00174696
    修改内容   : [DTS2011112307116]合入半静态及TTI Bundling新特性
-------------------------------------------------------------------------------
  6.日    期   : 2011年10月25日
    作    者   : sunyanjie
    修改内容   : [DTS2011102502995]合入TTI_BUNDLING新特性
-------------------------------------------------------------------------------
 7.日    期   : 2012年05月2日
  作    者   : yushujing
  修改内容   : [DTS2012042705688]上下行半静态并发时，pdcch存在误码问题修改
-------------------------------------------------------------------------------
  8.日    期   : 2012年4月18日
     作    者   : sunyanjie，yushujing，xueqiuyan
     修改内容   : [DTS2012041802974]OM优化修改
-------------------------------------------------------------------------------
  9.日    期   : 2012年9月7日
    作    者   : xueqiuyan
    修改内容   : [CMCC_DT]CMCC路测版本开发

  ******************************************************************************/

/************************************************************
                     包含其它模块的头文件
************************************************************/

/************************************************************
                               宏定义
************************************************************/

/************************************************************
                             数据结构定义
************************************************************/

/************************************************************
                             接口函数声明
 ************************************************************/

#ifndef __UL_OM_DEF_H__
#define __UL_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*下行TDD 模式接收到最大下行子帧数目*/
#define UL_TDD_MAX_DL_SUBFRAME_NUM 9
#define UL_MAX_SUBFRAME_NUM 10
#define UL_Pusch_Code_Rate     930
#define UL_MAX_PWR (INT16)23
#define UL_MIN_PWR (INT16)(-40)
#define UL_MAX_CELL_NUM LPHY_MAX_UL_CARRIER_NUM
#define UL_MAX_TB_NUM 2

#define OM_UL_MAX_CELL_NUM 2

#define PWR_VALID(sPwr) ((sPwr >= UL_MIN_PWR)&&(sPwr <= UL_MAX_PWR))

/* BEGIN: Added by l00131321, 2011/6/28   问题单号:DTS2011062802382*/
#define UL_OM_RPT_PERIOD 1000


#define POWER_INVALID_VALUE 0x7f



#define DT_INVALID_VALUE 0x7f
#define UL_OM_DT_RPT_PERIOD 200



#define MAX_PHR_SIZE        7
#define LTE_UL_MAX_CELL_NUM LPHY_FEATURE_MAX_CARRIER_NUM      /*当前版本支持最多小区个数为*/
#define UL_CQI_DATA_LEN     9

#define PUSCH_CAP_STR_RV_INDEX 6
#define PUSCH_CAP_STR_RB_NUM_INDEX 8
#define PUSCH_CAP_OM_STR_RB_NUM_INDEX 1
#define PUSCH_CAP_OM_STR_REG_LEN 3
/************************************************************
                           1. REQ命令和对应的数据结构定义
************************************************************/
typedef enum __LPHY_REQ_MSGID_UL__
{
    LPHY_REQ_UL_BASIC_INFO              =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0x1),
    LPHY_REQ_UL_RANDOM_ACCESS_INFO      =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0x2),
    LPHY_REQ_UL_CTRL_INFO               =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0x3),
    LPHY_REQ_UL_ACK_INFO                =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0x4),
    LPHY_REQ_UL_STAT_INFO               =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0x5),
    LPHY_REQ_UL_CAPTURE_INFO            =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0x6),
    LPHY_REQ_UL_UCI_TEST                =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0x7),
    LPHY_REQ_UL_POWER_CONFIG            =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0x8),
    LPHY_REQ_UL_PHR_INFO                =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0x9),

    /* BEGIN: Added by l00131321, 2011/6/7   问题单号:DTS2011062802382*/
    LPHY_REQ_UL_SCHEDUL_STATIC_INFO     =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0xa),
    LPHY_REQ_UL_HARQBLER_INFO           =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0xb),
    LPHY_REQ_UL_PD_INFO                 =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0xd),

    LPHY_SG_UL_SCHEDULE_STAT_INFO_REQ   =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0xe),
    LPHY_SG_UL_POWER_INFO_REQ           =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0xf),
    LPHY_SG_UL_PUSCH_INFO_REQ           =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0x10),
    //LPHY_SG_UL_ACCESS_INFO_REQ          =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0x11),

    /* BEGIN: Added by m00128895, 2015/10/16   PN:HP 降SAR特性开发*/
    LPHY_REQ_UL_HP_SAR_INFO             =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0x11),

    LPHY_DT_UL_POWER_INFO_REQ           =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_REQ, 0x100),
    LPHY_DT_UL_PUSCH_INFO_REQ          ,
    LPHY_DT_UL_SCHEDULE_STAT_INFO_REQ  ,
    LPHY_DT_HARQ_INFO_REQ              ,
    LPHY_DT_UL_ACCESS_INFO_REQ         ,
    LPHY_DT_TA_INFO_REQ                ,
    LPHY_DT_PUSCH_HARQ_BLER_STAT_REQ
}LPHY_REQ_MSGID_UL_ENUM;

/*****************************************************************************
 枚举名    : UL_OM_ACTIVE_FLG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 上行OM激活标志
*****************************************************************************/
enum UL_OM_ACTIVE_FLG_ENUM
{
    UL_OM_DEACTIVE = 0,
    UL_OM_ACTIVE
};
typedef UINT16 UL_OM_ACTIVE_FLG_ENUM_UINT16;

typedef struct __LPHY_REQ_UL_BASIC_INFO_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usReportPeriod;
}LPHY_REQ_UL_BASIC_INFO_STRU;

typedef struct __LPHY_REQ_UL_RANDOM_ACCESS_INFO_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usReportRfReg;
}LPHY_REQ_UL_RANDOM_ACCESS_INFO_STRU;

typedef struct __LPHY_REQ_UL_CTRL_INFO_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usUciBitMap;
}LPHY_REQ_UL_CTRL_INFO_STRU;

typedef struct __LPHY_REQ_UL_ACK_INFO_STRU_
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usRsvd;
}LPHY_REQ_UL_ACK_INFO_STRU;

typedef struct __LPHY_REQ_UL_STAT_INFO_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usBitMap;
    UINT32 ulStaRptTyp;
}LPHY_REQ_UL_STAT_INFO_STRU;

typedef struct __LPHY_REQ_UL_CAPTURE_INFO_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usBitMap;
}LPHY_REQ_UL_CAPTURE_INFO_STRU;
typedef struct
{
    UINT16 usRptCnt;
    UINT16 usFailCnt;
}UL_OM_PRACH_FAIL_OM_STRU;



/*ACK码字指示枚举结构*/
enum UL_CODE_IND_ENUM
{
    SINGLE_WORD = 0,
    DOUBLE_WORD,
    INVALID_WORD
};
typedef UINT16 UL_CODE_IND_ENUM_UINT16;

/*ACK调度类型枚举结构*/
enum UL_SCHED_TYPE_ENUM
{
    NON_PERSISTENT = 0,                    /*动态*/
    PERSISTENT,
    INVALID_SCHED                          /*半静态*/
};
typedef UINT16 UL_SCHED_TYPE_ENUM_UINT16;

/*下行解调TPC类型枚举结构*/
enum UL_TPC_TYPE_ENUM
{
    DCI3_3A = 0,                           /*DCI3/3A类型TPC*/
    DCIX,                                  /*其它类型TPC*/
    DCI_TPC_N,                            /*用于确定n1资源索引的TPC*/
    INVALID_DCI
};
typedef UINT16 UL_TPC_TYPE_ENUM_UINT16;

/*TPC数值枚举结构*/
enum UL_TPC_ENUM
{
    TPC_0 = 0,
    TPC_1,
    TPC_2,
    TPC_3,
    INVALID_TPC
};
typedef UINT16 UL_TPC_ENUM_UINT16;

/*ACK数据枚举结构*/
enum UL_ACK_ENUM
{
    NACK = 0,
    ACK,
    DTX,
    INVALID_ACK
};
typedef UINT16 UL_ACK_ENUM_UINT16;

enum UL_CHANNEL_SELECT_ENUM
{
    UL_CHANNEL_PUSCH = 0,
    UL_CHANNEL_PUCCH,
    UL_CHANNEL_INVALID
};
typedef UINT16 UL_CHANNEL_SELECT_ENUM_UINT16;

typedef struct
{
    UL_TPC_ENUM_UINT16         enTPC;
    UL_TPC_TYPE_ENUM_UINT16    enTPCType;
    UL_SCHED_TYPE_ENUM_UINT16  enSchedType;
    UL_CODE_IND_ENUM_UINT16    enCodeInd;
    UL_ACK_ENUM_UINT16         enAckCode1;
    UL_ACK_ENUM_UINT16         enAckCode2;
    UINT16                     usNcce;
    UINT16                     usDAI;
    UINT16                     usRecFrame;
    UINT16                     usRecSubFrame;
}UL_OM_ACK_INFO_STRU;

/*****************************************************************************
 结构名    : UL_OM_CQI_REPORT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OMCQI上报信息结构
*****************************************************************************/
/* BEGIN: Added by l00131321, 2011/9/21   问题单号:DTS2011092100251*/
#if 0
typedef struct
{
    UINT16  usPeriodORAperiodInd;   /*-1:无效结果;0:周期CQI报告;1:非周期CQI报告*/
    UINT16  usSFN;                  /*CQI待发送的帧号*/
    UINT16  usSubFrame;             /*CQI待发送的子帧号*/
    UINT8   ucRIinfo;               /*RI信息0 无效，1 表示RI 为1，2表示RI为2，其它值保留*/
    UINT8   ucPMILength;            /*新增PMI报告长度,单位bit, for dem*/
    UINT8   ucPMINum;               /*新增PMI个数,dor dem*/
    UINT8   ucCQILength;            /*CQI报告长度,单位bit,for ul*/
    UINT16  usRev;
    UINT32  aulPMIReport[2];        /*新增PMI报告,for dem*/
    UINT32  aulCQIReport[4];        /*CQI报告*/
}UL_OM_CQI_REPORT_INFO_STRU;
#endif

typedef struct
{
    /*报告对应的帧和子帧号*/
    UINT16  usSFN;                  /*CQI待发送的帧号*/
    UINT16  usSubFrame;             /*CQI待发送的子帧号*/

    /*给上下模块的发送报告*/
    UINT16  usPeriodORAperiodInd;   /*0:无效结果;1:周期CQI报告;2:非周期CQI报告*/
    UINT8   ucRIinfo;               /*RI信息0 无效，1 表示RI 为1，2表示RI为2，其它值保留*/
    UINT8   ucCQILength;            /*CQI报告长度,单位bit,for ul*/
    UINT32  aulCQIReport[UL_CQI_DATA_LEN];        /*CQI报告*/

    /*给解调模块的报告*/
    UINT8   ucPmiValid;             /*PMI是否有效标记*/
    UINT8   ucSubbandNum;           /*子带个数*/
    UINT8   ucSubbandWidth;         /*子带大小*/
    UINT8   ucPMIValue[25];         /*PMI值*/

}UL_OM_CQI_REPORT_INFO_STRU;


typedef struct __LPHY_REQ_UL_UCI_TEST_STRU__
{
    UINT16 usSubFrame;     /*期待在哪一子帧发送*/
    UINT16 usBitMap;       /*bit0:   0:主小区ACK信息无效;1:主小区ACK信息有效
                             bit1:   0:CQI信息无效;1:CQI信息有效
                             bit2:   0:SR信息无效; 1:SR信息有效
                             bit3:   0:PUSCH无效; 1:PUSCH有效
                             bit4:   0:辅小区ACK信息无效;1:辅小区ACK信息有效
                             */

    UINT16 usAckInfoNum;   /*ACK信息个数*/
    UINT16 usCqiPucchResIdx;  /*CQI资源索引*/
    UINT16 usAnAndCqiValidFlg;
    UINT16 usSpsAckCount;
    UINT16 usAckNoDTX;
    UINT16 usAckLastRecIdx;
    UL_OM_ACK_INFO_STRU astAckInfo[4];
    UL_OM_CQI_REPORT_INFO_STRU stCqiInfoStru;
}LPHY_REQ_UL_UCI_TEST_STRU;

typedef enum
{
    PWRCTRL_OFF_AND_CLOSEDLOOP_OFF = 0,
    PWRCTRL_ON_AND_CLOSEDLOOP_OFF,
    PWR_STUB_SET,
    PWRCTRL_ON_AND_CLOSEDLOOP_ON
}OM_PWRCTRL_SWITCH_ENUM;

typedef UINT32 OM_PWRCTRL_SWITCH_ENUM_32;

typedef enum
{
    COMPENSATE_OFF = 0,
    COMPENSATE_ON
}OM_COMPENSATE_SWITCH_ENUM;

typedef UINT32 OM_COMPENSATE_SWITCH_ENUM_32;

typedef struct
{
    OM_PWRCTRL_SWITCH_ENUM_32    ulPuschPwrCtrlSwitch            :2;
    OM_PWRCTRL_SWITCH_ENUM_32    ulPucchPwrCtrlSwitch            :2;
    OM_PWRCTRL_SWITCH_ENUM_32    ulSrsPwrCtrlSwitch              :2;
    OM_PWRCTRL_SWITCH_ENUM_32    ulPrachPwrCtrlSwitch            :2;
    OM_COMPENSATE_SWITCH_ENUM_32 ulFreqCmpnstSwitch              :1;
    OM_COMPENSATE_SWITCH_ENUM_32 ulTempCmpnstSwitch              :1;
    UINT32 ulSpare                         :22;
}PHY_OM_UPLINK_PWR_CTRL_STRU;

typedef struct __LPHY_REQ_UL_POWER_CONFIG_STRU__
{
    PHY_OM_UPLINK_PWR_CTRL_STRU stulPwrCtrlSwitch;
    INT16  sPucchTxPower;
    INT16  sPuschTxPower;
    INT16  sSrsTxPower;
    INT16  sPrachTxPower;
}LPHY_REQ_UL_POWER_CONFIG_STRU;

typedef struct __LPHY_REQ_UL_PHR_INFO_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16    usReportPeriod;
} LPHY_REQ_UL_PHR_INFO_STRU;

/* BEGIN: Added by l00131321, 2011/6/7   问题单号:DTS2011062802382*/
typedef struct __LPHY_REQ_UL_SCHEDUl_STATIC_INFO_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16    usReportPeriod;
} LPHY_REQ_UL_SCHEDUl_STATIC_INFO_STRU;

typedef struct __LPHY_REQ_UL_HARQBLER_INFO_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16    usReportPeriod;
} LPHY_REQ_UL_HARQBLER_INFO_STRU;


/* BEGIN: Added by l00131321, 2012/12/13   问题单号:V7R2_MODIFY*/
/*SRS配置参数结构*/
typedef struct
{
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16 enSrsCommInfoValidFlg;
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16 enSrsDedicatedInfoValidFlg;
    LRRC_LPHY_SRS_COMM_INFO_STRU          stSrsCommInfo;
    LRRC_LPHY_SRS_DEDICATED_INFO_STRU     stSrsDedicatedInfo;

    /* BEGIN: Added by l00131321, 2012/11/9   问题单号:V7R2_MODIFY*/
    /*增加非周期SRS专有部分参数*/
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16 enSrsDedicatedAperiodicInfoValidFlg;  /* R10 非周期专有SRS参数是否有效 */
    LRRC_LPHY_SRS_DEDI_APERIOD_INFO_STRU  stSrsDedicatedAperiodicInfo;          /* R10 非周期专有SRS参数 */

    /*根据RRC配置索引查表计算得到的SRS传输周期和偏移量*/
    UINT16                              usSrsPeriod;
    UINT16                              ausSrsOffset[2];

    /* BEGIN: Added by l00131321, 2012/11/9   问题单号:V7R2_MODIFY*/
    UINT16                              usApSrsPeriod;
    UINT16                              ausApSrsOffset[2];
}UL_SRS_CFG_PARA_STRU;

/************************************************************
                           2. CNF数据结构定义
************************************************************/



/************************************************************
                           3. Ind数据结构定义
************************************************************/
typedef enum __LPHY_IND_MSGID_UL__
{
    LPHY_IND_UL_BASIC_INFO             = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x1),
    LPHY_IND_UL_RANDOM_ACCESS_INFO     = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x2),
    LPHY_IND_UL_CTRL_INFO              = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x3),
    LPHY_IND_UL_ACK_INFO               = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x4),
    LPHY_IND_UL_PUSCH_STAT_INFO        = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x5),
    LPHY_IND_UL_PUCCH_STAT_INFO        = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x6),
    LPHY_IND_UL_PRACH_STAT_INFO        = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x7),
    LPHY_IND_UL_SRS_STAT_INFO          = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x8),
    LPHY_IND_UL_PUCCH_CAPTURE_INFO     = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x9),
    LPHY_IND_UL_PUSCH_CAPTURE_INFO     = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0xa),
    LPHY_IND_UL_SRS_CAPTURE_INFO       = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0xb),
    LPHY_IND_UL_PHR_INFO               = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0xc),
    /* BEGIN: Added by l00131321, 2011/6/8   问题单号:DTS2011062802382*/
    LPHY_IND_UL_SCHEUL_STATIC_INFO     = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0xd),
    LPHY_IND_UL_HARQBLER_INFO          = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0xe),
    LPHY_IND_UL_PD_INFO                = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0xf),
    //LPHY_IND_UL_PUSCH_33A_INFO         = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0xf),
    //LPHY_IND_UL_PUCCH_33A_INFO         = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x10)
    LPHY_IND_UL_PUSCH_CAPTURE_INFO_SCELL = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x10),
    LPHY_IND_UL_SRS_CAPTURE_INFO_SCELL   = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x11),

	#if 0
    LPHY_UL_POWER_INFO_IND              =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x12),
    LPHY_UL_PUSCH_INFO_CA_IND           =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x13),
    LPHY_UL_SCHEDULE_STAT_INFO_IND      =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x14),
    LPHY_UL_ACCESS_INFO_IND             =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x15),
	#endif
    //LPHY_PUSCH_HARQ_BLER_STAT_IND       =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x16)
    /* BEGIN: Added by m00128895, 2015/10/16   PN:HP 降SAR特性开发*/
    LPHY_IND_UL_HP_SAR_INFO                = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x20)
}LPHY_IND_MSGID_UL_ENUM;

typedef enum __LPHY_SG_MSGID_UL__
{
    LPHY_UL_POWER_INFO_IND              =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_SG, 0x1),
    LPHY_UL_PUSCH_INFO_CA_IND           =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_SG, 0x2),
    LPHY_UL_SCHEDULE_STAT_INFO_IND      =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_SG, 0x3),
    //LPHY_UL_ACCESS_INFO_IND             =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_SG, 0x4)
    //LPHY_PUSCH_HARQ_BLER_STAT_IND       =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_IND, 0x16)
}LPHY_SG_MSGID_UL_ENUM;



typedef struct
{
    UINT16 usDci3ValidFlag;                  /*PUSCH DCI3、3a存在标志*/
    UINT16 usDci3Tpc;
    UINT16 usSendSfn;
    UINT16 usRsv;
}UL_PUSCH_33A_TPC_PARA_STRU;
typedef struct
{
    UINT16 usDci3CalcFlag;                  /*当前是否进行了33a的计算 0:未进行 1:有进行*/
    UINT16 usRsv;
    UL_PUSCH_33A_TPC_PARA_STRU astPusch33aTpcPara[UL_MAX_SUBFRAME_NUM];
}UL_PUSCH_33A_TPC_CTRL_INFO_STRU;

typedef struct
{
    UINT16 usSfn;
    UINT16 usSbfn;
    UL_PUSCH_33A_TPC_CTRL_INFO_STRU stPusch33aTpcInfo;
}UL_OM_PUSCH_33A_TPC_IND_STRU;

typedef struct
{
    UINT16 usDci3ValidFlag;/*PUCCH DCI3、3a存在标志*/
    UINT16 usDci3Tpc;
    UINT16 usSendSfn;
    UINT16 usRsv;
}UL_PUCCH_33A_TPC_PARA_STRU;
typedef struct
{
    UL_PUCCH_33A_TPC_PARA_STRU astPucch33aTpcPara[UL_MAX_SUBFRAME_NUM][UL_TDD_MAX_DL_SUBFRAME_NUM];
    UL_PUCCH_33A_TPC_PARA_STRU stPucch33aTemp;  //用于保存 配比5 子帧9 的备份信息
    /* BEGIN: Added by l00131321, 2012/12/3   问题单号:V7R2_MODIFY*/

    UINT16 usCnt[UL_MAX_SUBFRAME_NUM];
    UINT16 usDci3CalcFlag;
    UINT16 usRevd;
}UL_PUCCH_33A_TPC_CTRL_INFO_STRU;

typedef struct
{
    UINT16 usSfn;
    UINT16 usSbfn;
    //UL_PUCCH_33A_TPC_CTRL_INFO_STRU stPucch33aTpcInfo;
    UL_PUCCH_33A_TPC_PARA_STRU astPucch33aTpcPara[UL_TDD_MAX_DL_SUBFRAME_NUM];
    UL_PUCCH_33A_TPC_PARA_STRU stPucch33aTemp;  //用于保存 配比5 子帧9 的备份信息
}UL_OM_PUCCH_33A_TPC_IND_STRU;

enum UL_SRS_SYMBOL_IND_ENUM
{
    NON_SYMBOL = 0,
    LAST_FIRST_SYMBOL,
    LAST_SECOND_SYMBOL,
    LAST_ALL_SYMBOL
};
typedef UINT16 UL_SRS_SYMBOL_IND_ENUM_UINT16;


/* BEGIN: Added by l00131321, 2012/11/12   问题单号:V7R2_MODIFY*/
enum UL_SRS_TYPE_ENUM
{
    PERIOD_SRS = 0,
    APERIOD_SRS
};
typedef UINT16 UL_SRS_TYPE_ENUM_UINT16;


typedef enum
{
    UL_DCI0_GRANT = 0,
    UL_SEMI_PESIST_GRANT,
    UL_RAR_GRANT,
    UL_GRANT_INVALID
}UL_GRANT_TYPE_ENUM;

typedef struct
{
    /*授权类型*/
    UL_GRANT_TYPE_ENUM  enUlGrantType;           /*RAR授权指示，用于计算RAR发送功率中的f(i)*/
    UINT16              usHarqProcNum;           /*用来读取初始授权的带宽*/

    /*TPC相关*/
    UINT16              usTpcExistFlg;           /*TPC存在标志*/
    UINT16              usTpcType;               /*tpc类型 0:DCI0; 1:DCI3; 2:3A; 3:RAR*/
    UINT16              usTpcIdx;                /*TPC索引*/
    INT16               sTpc;
    INT16               sP0;
    INT16               sP0Nominal;
    INT16               sP0Ue;
    UINT16              usCurMPusch;
    UINT16              usRBNum;
    UINT16              usPl;
    UINT16              usAlf;                   /* 左移10bit，即乘以1024*/
    INT16               sDeltaF;
    /*累积量fi保存*/
    INT16               sfi;                     /*累积量计算结果，每次使用都更新*/
    INT16               sfiTmp;                  /* f(i)中间变量 */
    INT16               sCalTransPwr;            /*计算功率保存*/
    INT16               sTransPwr;               /*发送功率保存*/
    INT16               sPhr;

    /* BEGIN: Added by l00131321, 2012/11/23   问题单号:V7R2_MODIFY*/
    INT16               sPucPusTotalPwr;
    /* BEGIN: Added by l00131321, 2012/12/4   问题单号:V7R2_MODIFY*/
    //UINT16              usRevd;
    INT16              sPhr2;                   /*Type2PHR*/
    INT16              sPmax;
    UINT16             usPbValue;               /*MAC上报MPR*/
} UL_CUR_PUSCH_PWR_PARA_STRU;

/*当前PUCCH功控参数结构,用于PUCCH 功控参数计算*/
typedef struct
{
    UINT16              usPucchFormat;
    INT16               sP0;
    INT16               sP0Nominal;
    INT16               sP0Ue;
    UINT16              usPl;
    UINT16              usHCqiAck;
    UINT16              usHarqBit;
    UINT16              usCqiBit;
    INT16               sDeltaF_PUCCH;
    INT16               sGiValue;                /*g(i)值*/
    INT16               sTpcValue;               /*TPC调整值*/
    INT16               sCalTransPwr;
    /*发送功率保存*/
    INT16               sTransPwr;               /*记录当前终端发射功率，用于和终端最大发送功率*/
    UINT16              ausTpc[9];
    INT16               s33aTpcValue;
    //UINT16              usRsv;

    INT16               sPmax;
}UL_CUR_PUCCH_PWR_CTRL_PARA_STRU;

typedef struct
{
    /*参数计算*/
    INT16               sSrsOffset;
    UINT16              usSrsRBNum;
    UINT16              usMSrs;

    INT16               sP0;
    INT16               sP0Nominal;
    INT16               sP0Ue;
    UINT16              usPl;
    UINT16              usAlf;                   /* 左移10bit，即乘以1024*/
    /*累积量fi保存*/
    INT16               sfi;                     /*累积量计算结果，每次使用都更新*/
    INT16               sCalTransPwr;            /*计算功率保存*/
    INT16               sTransPwr;               /*发送功率保存*/
    UINT16              usRsvd;
} UL_CUR_SRS_PWR_PARA_STRU;

typedef struct __LPHY_IND_UL_BASIC_INFO_STRU__
{
    UINT16 usSFN;                              /*小区SFN号*/
    UINT16 usSubFrameFn;                       /*小区子帧号*/
    UINT16 usUpChannelType;                    /*上行发送物理信道类型.Bit0:发送PUCCH;Bit1:发送PUSCH;Bit2:发送SRS;Bit3:发送PRACH;*/
    UINT16 usRsv;
    UL_SRS_SYMBOL_IND_ENUM_UINT16 aenSRSSymbInd[OM_UL_MAX_CELL_NUM];/*指示SRS在那个符号发送*/
    UINT16 usUCIInd;                           /*指示UCI的内容:Bit0:表示包含CQI报告;Bit1:表示包含ACK;Bit2:表示包含SR*/
    UINT16 usPuccdFormat;                      /*PUCCH格式*/
    UINT16 ausPuschMcs[OM_UL_MAX_CELL_NUM];                         /*PUSCH调制方式：0:BPSK;1:QPSK;2:16QAM;3:64QAM*/
    UINT32 ausPuschTB[OM_UL_MAX_CELL_NUM];                          /*UL-SCH的TB块长度*/
    INT16  asPucchPuschTxPower[OM_UL_MAX_CELL_NUM];                 /*PUCCH、PUSCH或者PRACH的发射功率，单位dBm*/
    INT16  asSRSTxPower[OM_UL_MAX_CELL_NUM];
    UL_CUR_PUSCH_PWR_PARA_STRU      astPuschPwrPara[OM_UL_MAX_CELL_NUM];
    UL_CUR_PUCCH_PWR_CTRL_PARA_STRU stPucchPwrPara;
    UL_CUR_SRS_PWR_PARA_STRU        astSrsPwrPara[OM_UL_MAX_CELL_NUM];
}LPHY_IND_UL_BASIC_INFO_STRU;

/*****************************************************************************
 结构名    : LPHY_IND_UL_RANDOM_ACCESS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OM随机接入信息指示结构
*****************************************************************************/
typedef struct __LPHY_IND_UL_RANDOM_ACCESS_INFO_STRU__
{
    UINT16 usSFN;
    UINT16 usSubFrameFn;

    UINT16 usPreambleIndex;

    UINT16 usPreambleRecSfn;
    UINT16 usPreambleRecSbfn;
    UINT16 usPreambleTranSfn;
    UINT16 usPreambleTranSbfn;

    UINT16 usWindowLen;
    UINT16 usPrachCfgIndex;
    UINT16 usPrachFormat;

    INT16  sTransPwr;
    INT16  sPreambleTxPower;
    UINT16 usRaRntiValue;
    UINT16 usPathLoss;

    UINT16 usK0;
    UINT16 usU;
    UINT16 usCv;
    UINT16 usRv;

}LPHY_IND_UL_RANDOM_ACCESS_INFO_STRU;


/*上行模块使能*/
enum UL_ENABLE_ENUM
{
    DISABLE = 0,
    ENABLE
};
typedef UINT16 UL_ENABLE_ENUM_UINT16;

/*上行模块有效标识*/
enum UL_VALID_ENUM
{
    UL_INVALID = 0,
    UL_VALID
};
typedef UINT16 UL_VALID_ENUM_UINT16;

/*上行模块状态机*/
enum UL_STATE_ENUM
{
    IDLE_STATE = 0,
    PREAMBLE_SEND_STATE,
    UL_DEDICATED_STATE
};
typedef UINT16 UL_STATE_ENUM_UINT16;


/*上行模块信道控制信息结构*/
#if 0
typedef struct
{
    UL_ENABLE_ENUM_UINT16 enPucchEn;
    UL_ENABLE_ENUM_UINT16 enPuschEn;
    UL_ENABLE_ENUM_UINT16 enPrachEn;
    UL_ENABLE_ENUM_UINT16 enSrsEn;
    UL_ENABLE_ENUM_UINT16 enAckTranEn;
    UL_STATE_ENUM_UINT16  enUlCurState;
    UL_VALID_ENUM_UINT16  enSrsSchedValid; /*SRS周期调度有效标识*/
    /* BEGIN: Added by l00131321, 2012/11/12   问题单号:V7R2_MODIFY*/
    UL_VALID_ENUM_UINT16  enSrsApSchedValid; /*SRS非周期调度有效标识*/


    UL_VALID_ENUM_UINT16  enSrSchedValid;  /*SR调度有效标识*/
    UINT16 usCurSfn;
    UINT16 usCurSbfn;
    UINT16                usRevd;
}UL_CTRL_INFO_STRU;
#endif

typedef struct
{
    UL_ENABLE_ENUM_UINT16 enPuschEn;
    UL_ENABLE_ENUM_UINT16 enPrachEn;
    UL_ENABLE_ENUM_UINT16 enSrsEn;
    UL_ENABLE_ENUM_UINT16 enPusUciEn;
    UL_STATE_ENUM_UINT16  enUlCurState;
    UL_VALID_ENUM_UINT16  enSrsSchedValid; /*SRS周期调度有效标识*/
    UL_VALID_ENUM_UINT16  enSrsApSchedValid; /*SRS非周期调度有效标识*/
    UINT16 usRsv;
}UL_CA_CHAN_CTRL_INFO_STRU;

typedef struct
{
    UL_CA_CHAN_CTRL_INFO_STRU astCaChanctrlInfo[OM_UL_MAX_CELL_NUM];
    UL_ENABLE_ENUM_UINT16 enPucchEn;
    UL_ENABLE_ENUM_UINT16 enAckTranEn;
    UL_VALID_ENUM_UINT16  enSrSchedValid;  /*SR调度有效标识*/
    UINT16                usRevd;
    UINT16 usCurSfn;
    UINT16 usCurSbfn;
}UL_CTRL_INFO_STRU;


/*****************************************************************************
 结构名    : UL_CUR_UCI_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OM上行当前UCI结构
*****************************************************************************/
typedef enum
{
    INVALID_CQI_REPORT = 0,
    PERIOD_CQI_REPORT,
    APERIOD_CQI_REPORT
}UL_CQI_RPT_TYPE_ENUM;

typedef UINT16 UL_CQI_RPT_TYPE_ENUM_UINT16;

/*当前UCI信息结构*/
typedef   struct
{
    UINT8   ucPmiValid;             /*PMI是否有效标记*/
    UINT8   ucSubbandNum;           /*子带个数*/
    UINT8   ucSubbandWidth;         /*子带大小*/
    UINT8   ucPMIValue[25];         /*PMI值*/

    UINT32  ulRiData;

}UL_CUR_UCI_PMI_STRU;

/*当前UCI信息结构*/
typedef   struct
{
    UL_ENABLE_ENUM_UINT16  enCqiEn ;
    UL_ENABLE_ENUM_UINT16  enSrEn;
    UL_ENABLE_ENUM_UINT16  enRiEn ;
    UL_ENABLE_ENUM_UINT16  enAckEn;
    UL_CQI_RPT_TYPE_ENUM_UINT16 enCqiRptType;
    //UINT16                 usRev;
    UINT8                       ucCellIndex;  /*dci0中带CqiReq的载波索引,非周期时cqi有效*/
    UINT8                       enCc;         //DTS2014081602301 PCQI上报对应载波索引
    UINT32          aulCqiData[UL_CQI_DATA_LEN];
    UINT32          ulCqiLen ;
    UINT32          ulRiData;
    UINT32          ulRiLen ;
    UINT32          ulAckData;
    UINT32          ulAckLen;
    UINT16          usCqiTranSfn;   /*由CQI模块确定*/
    UINT16          usCqiTranSbfn;

    /* BEGIN: Added by d00130305, 2012/11/24   问题单号:V7R2_MODIFY*/
//    UINT8   ucPmiValid;             /*PMI是否有效标记*/
//    UINT8   ucSubbandNum;           /*子带个数*/
//    UINT8   ucSubbandWidth;         /*子带大小*/
//    UINT8   ucPMIValue[25];         /*PMI值*/
    UINT16  usAckChSel;
    UINT16  usRiChSel;
    UINT16  usCqiChSel;
    UINT16  usRevd;
    UINT8  ucAckCcSel;
    UINT8  ucCqiCcSel;
    UINT8  ucRiCcSel;
    UINT8  ucSrPeriSbfn;                  /*sr周期位置*/
    UL_CUR_UCI_PMI_STRU     astUciCsiStr[LPHY_FEATURE_MAX_CARRIER_NUM];
}UL_CUR_UCI_STRU;
typedef   struct
{
    UL_ENABLE_ENUM_UINT16  enCqiEn ;
    UL_ENABLE_ENUM_UINT16  enSrEn;
    UL_ENABLE_ENUM_UINT16  enRiEn ;
    UL_ENABLE_ENUM_UINT16  enAckEn;
    UL_CQI_RPT_TYPE_ENUM_UINT16 enCqiRptType;
    UINT8                       ucCellIndex;  /*dci0中带CqiReq的载波索引,非周期时cqi有效*/
    UINT8                       enCc;         //DTS2014081602301 PCQI上报对应载波索引
    UINT32          aulCqiData[UL_CQI_DATA_LEN];
    UINT32          ulCqiLen ;
    UINT32          ulRiData;
    UINT32          ulRiLen ;
    UINT32          ulAckData;
    UINT32          ulAckLen;
    UINT16          usCqiTranSfn;   /*由CQI模块确定*/
    UINT16          usCqiTranSbfn;

    /* End: Added by d00130305, 2013/3/24   问题单号:V7R2_MODIFY*/
    UINT16  usAckChSel;
    UINT16  usRiChSel;
    UINT16  usCqiChSel;
    UINT16  usRevd;
    UINT8  ucAckCcSel;
    UINT8  ucCqiCcSel;
    UINT8  ucRiCcSel;
    UINT8  ucRsv;
}UL_CUR_UCI_OM_STRU;

typedef struct __LPHY_IND_UL_CTRL_INFO_STRU__
{
    UL_CTRL_INFO_STRU stUlCtrlInfo;     /*上行控制相关信息*/
    UL_CUR_UCI_OM_STRU stCurUciInfo ;      /*UCI信息结构*/
    //UINT16 ausRsvd[32];
}LPHY_IND_UL_CTRL_INFO_STRU;


/*****************************************************************************
 结构名    : UL_TDD_ACK_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TDD模式ACK信息结构
*****************************************************************************/
/*TDD模式下行HARQ ACK信息存储结构*/

/*定义半静态状态*/
typedef enum
{
    /*注意: 不要随意调整枚举顺序, 上行半静态会按枚举值取舍以节省代码空间和MIPS*/
    SPS_INVALID      = 0,
    SPS_RELEASE,            /*表示该授权为释放授权*/
    SPS_ACTIVE,             /*表示该授权为激活授权*/
    SPS_RETRAN,             /*表示该授权为重传授权*/
    SPS_CONFIG_GRANT        /*表示该授权为配置授权*/
}SPS_STATUS_ENUM;
typedef UINT16 SPS_STATUS_ENUM_UINT16;

typedef struct
{
    UL_SCHED_TYPE_ENUM_UINT16 aenAckSchedType[UL_TDD_MAX_DL_SUBFRAME_NUM];
    UL_CODE_IND_ENUM_UINT16   aenAckCodeInd[UL_TDD_MAX_DL_SUBFRAME_NUM];
    UL_ACK_ENUM_UINT16        aenAckCode1[UL_TDD_MAX_DL_SUBFRAME_NUM];
    UL_ACK_ENUM_UINT16        aenAckCode2[UL_TDD_MAX_DL_SUBFRAME_NUM];
    UL_TPC_TYPE_ENUM_UINT16   aenAckTpcType[UL_TDD_MAX_DL_SUBFRAME_NUM];
    UL_TPC_ENUM_UINT16        aenAckTpc[UL_TDD_MAX_DL_SUBFRAME_NUM];
    UINT16                    ausAckDAI[UL_TDD_MAX_DL_SUBFRAME_NUM];
    UINT16                    ausAckNcce[UL_TDD_MAX_DL_SUBFRAME_NUM];
    UINT16                    usAckTotal;
    UINT16                    usAckNoDTX;
    UINT16                    usSpsAckCount;             /*半静态ACK数目*/
    UINT16                    usAckLastRecIdx;
    UINT16                    usDbWordCnt;
    //UINT16                    usRev;
    //SPS_STATUS_ENUM       enSpsGrantStatus; /*指示当前半静态授权状态*/
    SPS_STATUS_ENUM_UINT16  aenSpsGrantStatus[UL_TDD_MAX_DL_SUBFRAME_NUM];
    UL_VALID_ENUM_UINT16      aenAckCodeChange[UL_TDD_MAX_DL_SUBFRAME_NUM];/*0表示无码字交换，1表示有码字交换*/
    UINT16                    usSpecialNum;
    UINT16                    ausCcsDciInd[UL_TDD_MAX_DL_SUBFRAME_NUM];/*交叉调度PDSCH对应DCI是在主小区还是辅小区，0:主小区，1:辅小区*/
    UINT16                    usRev;
}UL_TDD_ACK_STRU;

/*****************************************************************************
 枚举名    : UL_TRAN_IND_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : ACK传输指示
*****************************************************************************/
/*ACK传输指示枚举结构*/
enum UL_TRAN_IND_ENUM
{
    INIT_TRAN = 0,
    RE_TRAN,
    INVALID_TRAN_IND
};
typedef UINT16 UL_TRAN_IND_ENUM_UINT16;

/*****************************************************************************
 枚举名    : UL_PUC1bCS_ACK_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : ACK传输指示
*****************************************************************************/
/*ACK传输指示枚举结构*/
enum UL_PUC1bCS_ACK_TYPE_ENUM
{
    PUCCH_1bCS_ACK_TYPE_FDD = 0,
    PUCCH_1bCS_ACK_TYPE_M1 = 1,/*M1*/
    PUCCH_1bCS_ACK_TYPE_M2,/*M1*/
    PUCCH_1bCS_ACK_TYPE_M34,/*M3和M4*/
    PUCCH_1bCS_ACK_TYPE_F3,/*Format 3退为1bCs*/
    PUCCH_1bCS_ACK_TYPE_BUTT

};
typedef UINT16 UL_PUC1bCS_ACK_TYPE_ENUM_UINT16;

typedef struct
{
    UL_ENABLE_ENUM_UINT16 enPuschEn;       //pusch使能标志
    UL_ENABLE_ENUM_UINT16 enPucchEn;       //pucch使能标志
    UL_ENABLE_ENUM_UINT16 enPrachEn;       //prach使能标志
    UL_ENABLE_ENUM_UINT16 enBack1stSrsEn;  //S子帧倒数1st SRS使能标志或U子帧SRS使能标志
    UL_ENABLE_ENUM_UINT16 enBack2stSrsEn;  //S子帧倒数2nd SRS使能标志
    UINT16 usSysNumFlag;                   //1表示Pusch/pucch use 12 ofdm sym，0表示Pusch/pucch use 11 ofdm sym
    UINT16 usPreambleFormat;               //prach格式
    UINT16 usPrachSfrmCounter;             //prach子帧计数
    UINT16 usUlCcIdx;
    UINT16 usReserved;
} LTE_RFIN_UL_SFRM_INFO_STRU;


/*****************************************************************************
 结构名    : UL_CUR_TDD_ACK_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TDD模式当前子帧ACK信息结构
*****************************************************************************/
/*TDD模式当前下行HARQ ACK信息存储结构*/
typedef struct
{
    UL_TDD_ACK_STRU                 stCurTddAck;
    UINT16                          usAckIdxforPucch1;
    UINT16                          usNbundleIdx;
    UL_TRAN_IND_ENUM_UINT16         enTranInd;
    UINT16                          usRevd;
    UINT16                          usAckPucchResIdx;
    UINT16                          enAckPucchType;/*PUCCH承载ACK对应的类型*/

    UL_PUC1bCS_ACK_TYPE_ENUM_UINT16 enPucch1bCsAckType;
    UINT16                          usRevd2;

}UL_CUR_TDD_ACK_STRU;

/*****************************************************************************
 结构名    : UL_FDD_ACK_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : FDD模式ACK信息结构
*****************************************************************************/
/*FDD模式下行HARQ ACK存储结构*/
typedef struct
{
    UL_SCHED_TYPE_ENUM_UINT16 enAckSchedType;
    UL_CODE_IND_ENUM_UINT16   enAckCodeInd;        /*当前码字数目*/
    UL_ACK_ENUM_UINT16        enAckCode1;
    UL_ACK_ENUM_UINT16        enAckCode2;
    UL_TPC_TYPE_ENUM_UINT16   enAckTpcType;
    UL_TPC_ENUM_UINT16        enAckTpc;
    UINT16                    usAckNcce;
    SPS_STATUS_ENUM_UINT16    enSpsGrantStatus; /*指示当前半静态授权状态*/
    UL_VALID_ENUM_UINT16      enAckCodeChange;
    UINT16                    usCcsDciInd;
}UL_FDD_ACK_STRU;

/*****************************************************************************
 结构名    : UL_CUR_FDD_ACK_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : FDD模式当前子帧ACK信息结构
*****************************************************************************/
/*FDD模式当前下行HARQ ACK信息存储结构*/
typedef struct
{
    UL_FDD_ACK_STRU                 stCurFddAck;
    UL_TRAN_IND_ENUM_UINT16         enTranInd;
    UINT16                          usRecSbfn;
    UINT16                          usAckPucchResIdx;
    UINT16                          enAckPucchType;/*PUCCH承载ACK对应的类型*/
}UL_CUR_FDD_ACK_STRU;

/*****************************************************************************
 结构名    : UL_ACK_RESULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ACK处理后结果
*****************************************************************************/
/*ACK处理后结果*/
typedef struct
{
    UL_VALID_ENUM_UINT16  enACKValid;
    UINT16                usRevd;
    UINT32                ulAckData;
    UINT32                ulAckLen;
}UL_ACK_RESULT_STRU;

/*****************************************************************************
 结构名    : LPHY_IND_UL_ACK_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ACK数据指示结构
*****************************************************************************/
typedef struct __LPHY_IND_UL_ACK_INFO_STRU__
{
    UINT16 usSFN;
    UINT16 usSubFrameFn;
    UINT16 enTDDFeedbackMode;
    UINT16 usRsvd;
    union
    {
        UL_CUR_TDD_ACK_STRU stUlCurTddAck[LTE_UL_MAX_CELL_NUM];
        UL_CUR_FDD_ACK_STRU stUlCurFddAck[LTE_UL_MAX_CELL_NUM];
    }unCurAck;
    UL_ACK_RESULT_STRU stUlAckResult;
}LPHY_IND_UL_ACK_INFO_STRU;


 /*****************************************************************************
 结构名    : UL_OM_PRACH_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OMPrach统计信息结构
*****************************************************************************/
typedef struct
{
    UINT32 ulPRACHSetupReqCount;/*PRACH信道建立请求次数*/
    UINT32 ulPRACHSetupReqErrCount; /*PRACH信道建立失败次数*/
    UINT32 ulAccessReqCount;/*MAC下发的接入请求计数*/
    UINT32 ulPrachSchdErrCount; /*PRACH调度错误计数*/
    UINT32 ulPrachParaCalCount; /*PRACH参数计算次数统计*/
    UINT32 ulPrachBppCfgCount;  /*PRACH寄存器配置计数*/
}UL_OM_PRACH_STAT_INFO_STRU;

/*****************************************************************************
 结构名    : UL_OM_PUSCH_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OMPUSCH统计信息结构
*****************************************************************************/
typedef struct
{
    UINT32 ulPUSCHSetupReqCount;    /*PUSCH信道建立请求次数*/
    UINT32 ulPUSCHHoReqCount;       /*PUSCH信道切换请求次数统计*/
    UINT32 ulPuschSetupProcNumCount;/*PUSCH信道建立正确处理统计*/
    UINT32 ulPuschHoProcNumCount; /*PUSCH信道切换参数更新次数*/
    UINT32 ulRARReqCount;           /*RAR请求计数*/
    UINT32 ulRARSchedCount;         /*RAR调度计数*/
    UINT32 ulDCISchedCount;         /*DCI调度次数计数*/
    UINT32 ulTtiBundlingProcCount;  /*TTI重传处理次数计数*/
    UINT32 ulUlDCI0SchedErrCount;
    UINT32 ulCodParaCalCount;       /*编码参数计算计数*/
    UINT32 ulCodParaCalErrCount;    /*编码参数计算出错计数*/
    UINT32 ulCodParaCfgCount;       /*编码参数BPP配置计数*/
    UINT32 ulModParaCalCount;       /*调制参数计算计数*/
    UINT32 ulModParaCfgCount;       /*调制参数BPP配置计数*/
    UINT32 ulPwrCalCount;           /*功率计算处理计数*/
}UL_OM_PUSCH_STAT_INFO_STRU;

/*****************************************************************************
 结构名    : UL_OM_PUCCH_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OMPUCCH统计信息结构
*****************************************************************************/
typedef struct
{
    UINT32 ulPucchSetupReqCount;        /*PUCCH信道建立请求计数*/
    UINT32 ulPucchHoReqCount;           /*PUCCH信道切换请求计数*/
    UINT32 ulPucchRecfgCount;           /*PUCCH信道重配置计数*/
    UINT32 ulPucchTranCtrlCount;        /*PUCCH传输控制计数*/
    UINT32 ulSrCfgCount;                /*SR参数配置计数*/
    UINT32 ulSrReqCount;                /*SR请求计数*/
    UINT32 ulSrTranCtrlCount;            /*SR传输控制计数*/
    UINT32 ulSrSchedCount;              /*SR调度计数*/
    UINT32 ulSrProcInPUCCHCount;        /*SR在PUCCH信道发送计数*/
    UINT32 ulSrProcSimuPUSCHCount;      /*SR发送时存在授权*/
    UINT32 ulAckListUpdateCount;        /*ACK接口调用计数*/
    UINT32 ulAckStoreCount;             /*ACK保存计数*/
    UINT32 ulAckSchedCount;             /*ACK调度有效计数*/
    UINT32 ulAckDataProcErrCount;       /*ACK数据处理错误计数*/
    UINT32 ulAckProcInPUCCHCount;       /*ACK在PUCCH信道实际发送的次数*/
    UINT32 ulAckProcInPUSCHCount;       /*ACK在PUSCH信道实际发送的次数*/
    UINT32 ulCqiUpdateCount;            /*CQI接口调用计数*/
    UINT32 ulCqiSchedValidCount;        /*CQI调度有效计数*/
    UINT32 ulCqiProcInPUCCHCount;       /*CQI在PUCCH信道发送计数*/
    UINT32 ulCqiProcInPUSCHCount;       /*CQI在PUSCH信道发送计数*/
    UINT32 ulRiPcellSchedValidCount;    /*主小区RI调度有效计数*/
    UINT32 ulRiScellSchedValidCount;    /*辅小区RI调度有效计数*/
    UINT32 ulRiPScellSchedValidCount;   /*主辅小区RI调度有效计数*/
    UINT32 ulRiProcInPUCCHCount;        /*RI在PUCCH信道发送计数*/
    UINT32 ulRiProcInPUSCHCount;        /*RI在PUSCH信道发送计数*/
    UINT32 ulPucchModParaCalCount;      /*PUCCH调制参数计算计数*/
    UINT32 ulPucchModParaCalErrCount;   /*PUSCH调制参数计算出错计数*/
    UINT32 ulPUCCH1ModParaCfgCount;     /*PUCCH Format 1/1a/1b调制参数BPP配置计数*/
    UINT32 ulPUCCH2ModParaCfgCount;     /*PUCCH Format 2/2a/2b调制参数BPP配置计数*/
    UINT32 ulPucchPwrCalCount;          /*PUCCH功率计算处理计数*/
}UL_OM_PUCCH_STAT_INFO_STRU;

/*****************************************************************************
 结构名    : UL_OM_PWR_CTRL_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OM功控统计信息结构
*****************************************************************************/
typedef struct
{
    UINT32 usPuschTPCCfgInvalidErrCount;
    UINT32 usTpcCalErrCount;
    UINT32 usPwrCommParaInvalidCount;
    UINT32 usPwrDedicatedParaInvalidCount;
}UL_OM_PWR_CTRL_STAT_INFO_STRU;

/*****************************************************************************
 结构名    : UL_OM_SRS_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OMSRS统计信息结构
*****************************************************************************/
/*SRS相关统计*/
typedef struct
{
    UINT32 ulSrsCfgReqCount;             /*SRS配置请求计数*/
    UINT32 ulSrsSchedCount;              /*SRS调度有效计数*/
    /* BEGIN: Added by l00131321, 2012/12/18   问题单号:V7R2_MODIFY*/
    UINT32 ulApSrsSchedCount;
    UINT32 ulSrsModParaCalCount;         /*SRS调制参数计算计数 */
    UINT32 ulSrsModParaCalErrCount;      /*SRS调制参数计算错误计数 */
    UINT32 ulSrsBbpParaCfgCount;         /*SRSBBP配置计数*/
    UINT32 ulSrsPwrCalCount;             /*SRS功率计算计数*/
    UINT32 ulSrsEnableCount;             /*SRS有效次数计数*/
}UL_OM_SRS_STAT_INFO_STRU;


/*****************************************************************************
 结构名    : UL_OM_OTHER_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OM其它统计信息结构
*****************************************************************************/
typedef struct
{
    UINT32 ulTARecCount;
    UINT32 ulMaxPwrReqCount;
}UL_OM_OTHER_STAT_INFO_STRU;


/*****************************************************************************
 结构名    : UL_PUCCH_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OMUCI测试请求结构
*****************************************************************************/

typedef struct
{
    /*原语解析部分*/
    UINT32 ulSrCfgErrCount;                            /*SR参数配置错误计数*/
    UINT32 ulSrSchedErrCount;                          /*SR调度错误计数*/
    UINT32 ulPucchTpcCfgErrCount;                      /*TPC配置错误计数*/
    UINT32 ulDAIErrCount;                              /*DAI错误计数*/
    UINT32 ulAckUpdateErrCount;                        /*ACK接口更新错误计数*/
    UINT32 ulAckInvalidErrCount;                       /*ACK数据无效错误计数*/
    UINT32 ulFddAckStoreTimeErrCount;                  /*LTE_FRAME_TYPE_FDD ACK保存时序错误计数*/
    UINT32 ulFddAckStoreErrCount;                      /*LTE_FRAME_TYPE_FDD ACK保存错误计数*/
    UINT32 ulFddAckSchedErrCount;                      /*LTE_FRAME_TYPE_FDD ACK调度错误计数*/
    UINT32 ulTddAckStoreTimeErrCount;                  /*LTE_FRAME_TYPE_TDD ACK保存时序错误计数*/
    UINT32 ulTddAckRecSbfnErrCount;                    /*LTE_FRAME_TYPE_TDD ACK接收子帧错误计数*/
    UINT32 ulTddAckSchedErrCount;                      /*LTE_FRAME_TYPE_TDD ACK调度错误计数*/
    UINT32 ulTddAckNumErrCount;                        /*LTE_FRAME_TYPE_TDD ACK接收次数错误计数*/
    UINT32 ulTddBundAckProcForPuschErrCount;           /*LTE_FRAME_TYPE_TDD PUSCH Bund ACK处理错误计数*/
    UINT32 ulTddMultiAckProcForPuschErrCount;          /*LTE_FRAME_TYPE_TDD PUCCH Multi ACK处理错误计数*/
    UINT32 ulTddBundAckProcForPucchErrCount;           /*LTE_FRAME_TYPE_TDD PUCCH Bund ACK处理错误计数*/
    UINT32 ulTddMultiAckProcForPucchErrCount;          /*LTE_FRAME_TYPE_TDD PUCCH Multi ACK处理错误计数*/
    UINT32 ulTddAckDataLossErrCount;                   /*LTE_FRAME_TYPE_TDD ACK数据丢失错误计数*/
    UINT32 ulTddAckResIdxErrCount;                     /*LTE_FRAME_TYPE_TDD ACK资源表索引错误计数*/
    UINT32 ulTddMultiAddressErrCount;                  /*LTE_FRAME_TYPE_TDD ACK Multi表地址错误计数*/
    UINT32 ulPucchFormatErrcount;                      /*PUCCH格式错误计数*/
    UINT32 ulPucch1ResIdxGetErrCount;                  /*PUCCH Format1/1a/1b资源索引错误计数*/
    UINT32 ulCqiLenErrCount;                           /*CQI长度错误计数*/
    UINT32 ulAckLenErrCount;                           /*ACK长度错误计数*/
    UINT32 ulCqiTranTimeErrCount;                      /*CQI传输时序错误计数*/
    UINT32 ulSimuCqiAndSrErrCount;                     /*CQI/SR同传错误计数*/
    UINT32 ulSimuAckAndCqiErrCount;                    /*CQI/ACK同传错误计数*/
    UINT32 ulSimuAckAndCqiCfgDropCount;                /*CQI/ACK同传配置不支持丢弃计数*/
    UINT32 ulSimuAckAndCqiScellDropCount;              /*CQI/ACK同传辅小区存在ACK丢弃计数*/
    UINT32 ulSimuAckAndCqiTTiBundDropCount;            /*CQI/ACK同传Tti Bundling丢弃计数*/
    UINT32 ulNcceErrCount;                             /*Ncce错误计数*/
    UINT32 ulPucchDeltaShiftErrCount;                  /*Deltashift错误计数*/

    UINT32 ulPhrCfgErrCount;                           /*PHR配置错误计数*/
    UINT32 ulMacHeadValidErrCount;                     /* MAC PHY Head头有效标志错误计数*/
    UINT32 ulPucch1bCsAckResIdxErrCount;               /*PUCCH 1bCs ACK资源表索引错误计数*/
    UINT32 ulPucch1bCsAckTableErrCount;                /*PUCCH 1bCs ACK资源表查询错误计数*/
    UINT32 ulPucch1bCsResIdxGetErrCount;               /*PUCCH Format1b  Cs资源索引错误计数*/
    UINT32 ulPucch3ResIdxGetErrCount;                  /*PUCCH Format3资源索引错误计数*/
    UINT32 ulPucch2ResIdxGetErrCount;                  /*PUCCH Format2资源索引错误计数*/

    UINT32 ulPucch1bCsPwtErrCount;                     /*PUCCH Format1bCs功率索引引错误计数*/
    UINT32 ulPucch3PwtErrCount;                        /*PUCCH Format3功率索引引错误计数*/
    UINT32 ulPucchnHarqErrCount;                       /*PUCCH FormatnHarq错误计数*/

    UINT32 ulPucch1bCsM1M2ErrCount;                    /*PUCCH Format M1M2错误计数*/
    UINT32 ulPucch1bCsM3M4ErrCount;                    /*PUCCH Format M3M4错误计数*/

    UINT32 ulAckDummyErrorCount;                       /*分支异常错误*/

}UL_PUCCH_STAT_INFO_STRU;
/*****************************************************************************
 结构名    : UL_PUSCH_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OMUCI测试请求结构
*****************************************************************************/
typedef struct
{
    /*原语解析部分*/
    UINT32 ulMsgChanTypeErrCount;
    UINT32 ulMsgHopModErrCount;

    UINT32 ulParaInvalidErrCount;
    UINT32 ulSpsParaInvalidErrCount;

    UINT32 ulBandWithCfgErrCount;
    UINT32 ulDCINumErrCount;
    UINT32 ulTPC0ErrCount;

    /*参数计算部分错误*/
    UINT32 ulImcsErrCount;
    UINT32 ulRBSumErrCount;
    UINT32 ulCqiReqFlgErrCount;
    UINT32 ulCqiDataNotReadyErrCount;
    UINT32 ulCalKposErrCount;
    UINT32 ulResAlloType1EvenErrCount;
    UINT32 ulResAlloType1OddErrCount;
    UINT32 ulHoppingInfoErrCount;
    UINT32 ulAckQCalParaInvalidErrCount;
    UINT32 ulDmrsCs1IndexErrCount;
    UINT32 ulDmrsCs2IndexErrCount;
    UINT32 ulAckCtrlInfoMcsOffsetIdxErrCount;
    UINT32 ulCqiCtrlInfoMcsOffsetIdxErrCount;
    UINT32 ulRiCtrlInfoMcsOffsetIdxErrCount;
    UINT32 ulHoppingOffsetErrCount;
    UINT32 ulType2ResourceAssinErr;
    UINT32 ulDeltaSSErrCount;
    UINT32 ulNsbErrCount;
    UINT32 ulRBNumInvalidErrCount;

    UINT32 ulDci0TpcIdxErrCount;
    UINT32 ulPuschTpcCfgInvalidErrCount;
    UINT32 ulPuschPwrAccuCalErrCount;
    UINT32 ulHarqProcNumCalErrCount;
    /*参数配置*/
    UINT32 ulModParaCalErrCount;
    UINT32 ulCodParaCfgCountErrCount;                   /*Deltashift错误计数*/
    UINT32 ulMacPduUnequalDspErrCount;                  /*DSP与MAC不一致错误计数*/
    UINT32 ulOnlyUciPuschDisabErrCount;                 /*Deltashift错误计数*/
    UINT32 ulMacInValidErrCnt;                          /*Deltashift错误计数*/
    UINT32 ulTtiBundlNprbErrCnt;
}UL_PUSCH_STAT_INFO_STRU;
/*****************************************************************************
 结构名    : UL_PRACH_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OMUCI测试请求结构
*****************************************************************************/
typedef struct
{
    UINT32 ulPRACHHoReqCount;
    UINT32 ulPreambleFormatErrCount;

    UINT32 ulMsgChanTypeErrCount;
    UINT32 ulMsgRootSeqErrCount;
    UINT32 ulMsgNcsIndErrCount;
    UINT32 ulMsgPrachCfgIndErrCount;
    UINT32 ulRaReqMaskCodeIndexErrCount;
    UINT32 ulMsgPreambleIndErrCount;

    UINT32 ulRARSchedErrCount;
    UINT32 ulParaInvalidErrCount;

    UINT32 ulRARGrantUlDelayErrCount;
    UINT32 ulRARSchedError;             /*RAR错过了发送时隙错误*/
    UINT32 ulPrachResouceIndCount;
    UINT32 ulTddFrmStruErrCount;        /*FDD模式下，帧结构类型错误，即不在0~6范围内*/

    UINT32 ulRootuAndCvCalErrCont;
    UINT32 ulFddCalPrbIndexErrCount;
    UINT32 ulRBStartPosErrCount;

    /*bpp配置相关计数*/
    UINT16 usBppCfgErrCount;
    UINT16 usRsv;
}UL_PRACH_STAT_INFO_STRU;
/*****************************************************************************
 结构名    : UL_SRS_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OMUCI测试请求结构
*****************************************************************************/
typedef struct
{
    UINT32 ulSrsCfgErrCount;               /*SRS配置错误计数*/
    UINT32 ulSrsNraErrCount;               /*SRS Nra错误计数*/
    UINT32 ulSrsBandErrCount;              /*SRS带宽配置错误计数*/
    UINT32 ulSrsMsrsMaxCalErrCount;        /*SRS Msrsmax计算错误计数*/
    UINT32 ulMsrsCalErrCount;              /*SRS Msrs计算错误计数*/
    UINT32 ulUpptsK0PieCalErrCount;        /*SRS Uppts k0pie计算错误计数*/

}UL_SRS_STAT_INFO_STRU;
/*****************************************************************************
 结构名    : LPHY_IND_UL_PRACH_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OMUCI测试请求结构
*****************************************************************************/
typedef struct __LPHY_IND_UL_PRACH_STAT_INFO_STRU__
{
    UINT16 usOmType;
    UINT16 usSfn;
    UINT16 usSbfn;
    UINT16 usRsvd;
    UL_OM_PRACH_STAT_INFO_STRU stOmPrachStatInfo;
    UL_PRACH_STAT_INFO_STRU stUlPrachStatInfo;
}LPHY_IND_UL_PRACH_STAT_INFO_STRU;


/*****************************************************************************
 结构名    : LPHY_IND_UL_PUSCH_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OMUCI测试请求结构
*****************************************************************************/
typedef struct __LPHY_IND_UL_PUSCH_STAT_INFO_STRU__
{
    UINT16 usSfn;
    UINT16 usSbfn;
    UL_OM_PUSCH_STAT_INFO_STRU stOmPuschStatInfo;
    UL_PUSCH_STAT_INFO_STRU stUlPuschStatInfo;
}LPHY_IND_UL_PUSCH_STAT_INFO_STRU;


/*****************************************************************************
 结构名    : LPHY_IND_UL_PUCCH_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OMUCI测试请求结构
*****************************************************************************/
typedef struct __LPHY_IND_UL_PUCCH_STAT_INFO_STRU__
{
    UINT16 usSfn;
    UINT16 usSbfn;
    UL_OM_PUCCH_STAT_INFO_STRU stOmPucchStatInfo;
    UL_PUCCH_STAT_INFO_STRU stUlPucchStatInfo;
}LPHY_IND_UL_PUCCH_STAT_INFO_STRU;
/*****************************************************************************
 结构名    : LPHY_IND_UL_SRS_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OMUCI测试请求结构
*****************************************************************************/
typedef struct __LPHY_IND_UL_SRS_STAT_INFO_STRU__
{
    UINT16 usSfn;
    UINT16 usSbfn;
    UL_OM_SRS_STAT_INFO_STRU stOmSrsStatInfo;
    UL_SRS_STAT_INFO_STRU stUlSrsStatInfo;
}LPHY_IND_UL_SRS_STAT_INFO_STRU;




/*****************************************************************************
 枚举名    : UL_TRAN_IND_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : ACK传输指示
*****************************************************************************/
/*PUCCH格式枚举结构*/
enum UL_PUCCH_FORMAT_ENUM
{
    PUCCH_FORMAT_1 = 0,
    PUCCH_FORMAT_1a,
    PUCCH_FORMAT_1b,
    PUCCH_FORMAT_1b_CS,
    PUCCH_FORMAT_2,
    PUCCH_FORMAT_2a,
    PUCCH_FORMAT_2b,
    /* BEGIN: Added by l00131321, 2012/11/24   问题单号:V7R2_MODIFY*/
    PUCCH_FORMAT_3,
    PUCCH_FORMAT_INVALID
};
typedef UINT16 UL_PUCCH_FORMAT_ENUM_UINT16;

/*****************************************************************************
 枚举名    : UL_HIGHSPEED_FLG_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 高低速标志
*****************************************************************************/
/*PRACH 高低速标志，用于preamble码产生，对应unrestricted set和restricted set*/
enum UL_HIGHSPEED_FLG_ENUM
{
    HIGH_SPEED_FLAG_FALSE = 0, /*对应unrestricted set*/
    HIGH_SPEED_FLAG_TURE       /*对应restricted set*/
};
typedef UINT16 UL_HIGHSPEED_FLG_ENUM_UINT16;

/*****************************************************************************
 结构名    : UL_OM_BBP_PARA_CAPTURE_FLG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OMBBP参数捕获标志结构
*****************************************************************************/
typedef struct
{
    UINT16 usBbpParaActFlg;
    UINT16 usBitmap;
}UL_OM_BBP_PARA_CAPTURE_FLG_STRU;

/*****************************************************************************
 结构名    : UL_OM_STAT_INFO_CAPTURE_FLG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OM统计信息捕获标志结构
*****************************************************************************/
typedef struct
{
    UINT16 usStatInfoActFlg;
    UINT16 usBitmap;
    UINT32 ulStaRptTyp;
}UL_OM_STAT_INFO_CAPTURE_FLG_STRU;

/*****************************************************************************
 结构名    : UL_OM_STAT_INFO_CAPTURE_FLG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OM统计信息标志结构
*****************************************************************************/
typedef struct
{
    UL_OM_ACTIVE_FLG_ENUM_UINT16  enInfoActflag;
    UINT16  usPeriod;
    UINT16  usPeriodCount;
    UINT16  usRsv;
}UL_OM_CTRL_INFO_STRU;

/* BEGIN: Added by m00128895, 2015/10/16   PN:HP 降SAR特性开发*/
typedef struct UL_OM_HP_SAR_INFO
{
    UINT16 usDprOnFlag;      /*当前DPR开关状态*/
    INT16  sSarAverPow;      /*当前平均发射功率，1/8 dBm*/
    UINT32 ulSarAverPowLiner;/*当前平均发射功率,线性值*/
    INT16  sCurTxPow;        /*当前发射功率，1/8 dBm*/
    UINT16 us32kTime;        /*当前功率统计时刻*/
}UL_OM_HP_SAR_INFO_STRU;

/*****************************************************************************
 结构名    : UL_OM_DATA_CAPTURE_FLG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OM数据捕获标志结构
*****************************************************************************/
typedef struct
{
    UINT16 usBasicInfoActFlg;
    UINT16 usRandomAccessActFlg;
    UINT16 usCtrlInfoActFlg;
    UINT16 usAckInfoActFlg;
    UINT32 ulUciBitMap;
/* BEGIN: Added by m00128895, 2015/10/16   PN:HP 降SAR特性开发*/
#ifdef LPHY_FEATURE_LOWER_SAR_ENABLE
    UINT32 enHpSarInfoFlag;  /*HP降SAR信息OM开关*/
#endif
    UL_OM_STAT_INFO_CAPTURE_FLG_STRU stStatInfoCapFlg;
    UL_OM_BBP_PARA_CAPTURE_FLG_STRU stBbpParaCapFlg;
    UL_OM_CTRL_INFO_STRU stBasicInfoActFlg;
    UL_OM_CTRL_INFO_STRU stPhrCtrlInfo;
}UL_OM_DATA_CAPTURE_FLG_STRU;

/*****************************************************************************
 结构名    : UL_OM_PWR_SET_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OM功率设置结构
*****************************************************************************/
typedef struct
{
   UINT16 usPuschPwrCtrlSwitch;
   UINT16 usPuschClosedLoopSwitch;
   UINT16 usPucchPwrCtrlSwitch;
   UINT16 usPucchClosedLoopSwitch;
   UINT16 usSrsPwrCtrlSwitch;
   UINT16 usPrachPwrCtrlSwitch;
   INT16  sPuschTxPower;
   INT16  sPucchTxPower;
   INT16  sSrsTxPower;
   INT16  sPrachTxPower;
}UL_OM_PWR_SET_STRU;



/*****************************************************************************
 结构名    : UL_PUSCH_BPP_CODING_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OMPUSCHBBP编码配置参数结构
*****************************************************************************/

/*PUSCH BPP编码参数配置寄存器，各个字代表的意思参数软硬件接口,共13个寄存器*/

/*PUSCH BPP编码参数配置寄存器，各个字代表的意思参数软硬件接口,共11个寄存器*/

typedef struct
{
    /*PUSCH_SBFN_REG*/
    UINT32 ulPROCESS_NUM    :4;
    UINT32 ulSUBFRAME_NUM   :4;
    UINT32 ulFRAME_NUM      :10;
    UINT32                  :14;
    /*ULSCH_TB_REG*/
    UINT32 ulQM_PUSCH       :3;
    UINT32                  :1;
    UINT32 ulTB_SIZE        :17;
    UINT32                  :11;
    /*SEG_NEG_CB_REG*/
    UINT32 ulC1_UL_SCH      :4;  /*C-*/
    UINT32 ulK1_UL_SCH      :13; /*K-*/
    UINT32                  :15;
    /*SEG_POS_CB_FILL_REG*/
    UINT32 ulC2_UL_SCH      :4;  /*C+*/
    UINT32 ulK2_UL_SCH      :13; /*K+*/
    UINT32                  :3;
    UINT32 ulN_TB_NULL      :6;
    UINT32                  :6;
    /*TURBO_PARA_KNEG_REG*/
    UINT32 ulF1_C1_UL_SCH   :9;  /*f1 for C-*/
    UINT32                  :3;
    UINT32 ulF2_C1_UL_SCH   :10; /*f2 for C-*/
    UINT32                  :10;
    /*TURBO_PARA_KPOS_REG*/
    UINT32 ulF1_C2_UL_SCH   :9;  /*f1 for C+*/
    UINT32                  :3;
    UINT32 ulF2_C2_UL_SCH   :10; /*f2 for C+*/
    UINT32                  :10;
    /*TURBO_RM_EDW_REG*/
    UINT32 ulC1_E_UL_SCH    :17; /*E for C-*/
    UINT32                  :3;
    UINT32 ulRvinx          :2;  /*冗余版本号*/
    UINT32                  :10;
    /*TURBO_RM_EUP_REG*/
    UINT32 ulC2_E_UL_SCH    :17; /*E for C+*/
    UINT32                  :3;
    UINT32 ulGama           :4;
    UINT32                  :8;
    /*PUSCH_INTERLEAVER_REG*/
    UINT32 ulRbNum          :7;  /*RbNum数目,BBP自己计算信道交织行列*/
    UINT32                  :1;
    UINT32 ulSCH_SYMB_NUM   :4;  /*指示最后一个符号是否发送SRS,0:不发送，1:发送*/
    UINT32                  :20;
    /*PUSCH_Q_RI_CQI_REG*/
    UINT32 ulQ_CQI_PUSCH    :14; /*Q'cqi*/
    UINT32                  :2;
    UINT32 ulQ_RI_PUSCH     :13; /*Q'ri*/
    UINT32                  :3;
    /*PUSCH_ACK_REG*/
    UINT32 ulAckScrEn       :1;
    UINT32                  :3;
    UINT32 ulNbundleIdx     :2;
    UINT32                  :10;
    UINT32 ulQ_ACK_PUSCH    :13; /*Q'ack*/
    UINT32                  :3;
}UL_PUSCH_BPP_CODING_PARA_STRU;

typedef struct
{
    /*TURBO_RM_EDW_REG*/
    UINT32 ulC1_E_UL_SCH    :17; /*E for C-*/
    UINT32                  :3;
    UINT32 ulRvinx          :2;  /*冗余版本号*/
    UINT32                  :10;
	/*PUSCH_INTERLEAVER_REG*/
    UINT32 ulRbNum          :7;  /*RbNum数目,BBP自己计算信道交织行列*/
    UINT32                  :1;
    UINT32 ulSCH_SYMB_NUM   :4;  /*指示最后一个符号是否发送SRS,0:不发送，1:发送*/
    UINT32                  :20;
	/*PUSCH_Q_RI_CQI_REG*/
    UINT32 ulQ_CQI_PUSCH    :14; /*Q'cqi*/
    UINT32                  :2;
    UINT32 ulQ_RI_PUSCH     :13; /*Q'ri*/
    UINT32                  :3;
	/*PUSCH_ACK_REG*/
    UINT32 ulAckScrEn       :1;
    UINT32                  :3;
    UINT32 ulNbundleIdx     :2;
    UINT32                  :10;
    UINT32 ulQ_ACK_PUSCH    :13; /*Q'ack*/
    UINT32                  :3;
}UL_PUSCH_BPP_CODING_PARA_OM_STRU;
/*****************************************************************************
 结构名    : UL_PUSCH_BBP_MOD_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OMPUSCHBBP调制配置参数结构
*****************************************************************************/
/*根据最新接口调整此数据结构，20090429*/
typedef struct
{
    //UINT32 aulModReg[9];
    UINT32 aulModReg[10];
    #if 0
    /*PUSCH_SCRAMBL_REG*/
    UINT32 ulScr_X2_Init            :31;
    UINT32                          :1;
    /*PUSCH_EVEN_REG*/
    UINT32 ulU_PUSCH_EVEN           :5;
    UINT32                          :3;
    UINT32 ulQ_PUSCH_EVEN           :11;
    UINT32                          :1;
    UINT32 ulN_DMRS_EVEN_PUSCH      :4;
    /* BEGIN: Added by l00131321, 2012/11/22   问题单号:V7R2_MODIFY*/
    //UINT32 ulRB_START_EVEN          :7;
    //UINT32                          :1;
    UINT32 ulPUS_EVEN_NPRB_STYLE    :1;
    UINT32                          :7;
    /*PUSCH_ODD_REG*/
    UINT32 ulU_PUSCH_ODD            :5;
    UINT32                          :3;
    UINT32 ulQ_PUSCH_ODD            :11;
    UINT32                          :1;
    UINT32 ulN_DMRS_ODD_PUSCH       :4;
    /* BEGIN: Added by l00131321, 2012/11/22   问题单号:V7R2_MODIFY*/
    //UINT32 ulRB_START_ODD           :7;
    //UINT32                          :1;
    UINT32 ulPUS_ODD_NPRB_STYLE       :1;
    UINT32                            :7;

    /*PUSCH_EVEN_RB_POS*/
    UINT32 ulPUS_EVEN0_NPRB           :7;
    UINT32                            :1;
    UINT32 ulPUS_EVEN0_RBLEN          :7;
    UINT32                            :1;
    UINT32 ulPUS_EVEN1_NPRB           :7;
    UINT32                            :1;
    UINT32 ulPUS_EVEN1_RBLEN          :7;
    UINT32                            :1;

    /*PUSCH_ODD_RB_POS*/
    UINT32 ulPUS_ODD0_NPRB            :7;
    UINT32                            :1;
    UINT32 ulPUS_ODD0_RBLEN           :7;
    UINT32                            :1;
    UINT32 ulPUS_ODD1_NPRB            :7;
    UINT32                            :1;
    UINT32 ulPUS_ODD1_RBLEN           :7;
    UINT32                            :1;

    /*PUSCH_DMRS_REG*/
    UINT32 ulw_0                      :1;
    UINT32 ulw_1                      :1;
    UINT32                           :30;

    /*PUSCH_AMP_REG*/
    UINT32 ulpus_amp_b                :17;
    UINT32                            :15;
    #endif
}UL_PUSCH_BBP_MOD_PARA_STRU;

#if 0
/*****************************************************************************
 结构名    : UL_OM_DCI0_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OMDCI0结构
*****************************************************************************/
typedef struct
{
    UINT16 usSemiStaticFlag; /*动态/半静态调度指示*/
    UINT16 usInitGrantFlag;  /*初始授权标志*/
    UINT16 usDci0ExistFlag;      /*DCI0存在标志*/
    UINT16 usHoppingFlag;    /*Hopping flag*/
    UINT16 usTbSize;         /*TB size */
    UINT16 usRIV;             /*冗余版本号*/
    UINT16 usImcs;              /*调制阶数*/
    UINT16 usNewIndex;        /*新数据指示*/
    UINT16 usPuschTpc;       /*TPC command for scheduled PUSCH*/
    UINT16 usCyclicDmrs;     /*Cyclic shift for DM RS*/
    UINT16 usUlIndex;        /*UL index*/
    UINT16 usCqiRequest;     /*CQI request*/
    UINT16 usRbStart;        /*RB起始位置*/
    UINT16 usRbNum;          /*RB数目*/
    UINT16 usHopInfo;        /*调频信息*/
    UINT16 usDaiInfo;        /*DAI信息域*/
}UL_OM_DCI0_STRU;
#endif
/* BEGIN: Added by l00131321, 2012/12/13   问题单号:V7R2_MODIFY*/
enum UL_RB_ALLOC_TYPE_ENUM
{
    UL_RB_ALLOC_TYPE0 = 0,
    UL_RB_ALLOC_TYPE1 = 1,
    UL_RB_ALLOC_INVALID
};
typedef UINT16 UL_RB_ALLOC_TYPE_ENUM_UINT16;

/*****************************************************************************
 结构名    : UL_TB_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/

typedef struct
{
    UINT8 ucTbValid;         /*tb是否使能*/
    UINT8 ucInitGrantFlag;  /*初始授权标志,1-初始,0-重传*/
    UINT8 ucNewTransFlag;    /*指示是否为第一次收到的授权,0xffff-没有授权，1-已经收到授权*/
    UINT8 ucNewIndex;        /*NDI指示*/
    UINT16 usImcs;           /*调制阶数*/
    UINT16 usRsv;
    UINT32 ulTbSize;         /*TB size */
} UL_TB_STRU;


/* DCI 格式 */
typedef enum __UL_DCI_TYPE_ENUM__
{
    UL_DCI0 = 0,
    UL_DCI4,
    UL_RAR
}UL_DCI_TYPE_ENUM;
typedef UINT16 UL_DCI_TYPE_ENUM_UINT16;

/*****************************************************************************
 结构名    : UL_DCI_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    UINT8 ucUlDciExistFlag;      /*上行DCI存在标志,1-存在,0-不存在 */
    UINT8 ucUlMimoHarqFlag;      /* 上行MIMO 当前PHICH 一个TB ACK，另一TB NACK时，置标志使能 */
    UINT16 usSemiStaticFlag;    /*动态/半静态调度指示,0-动态,1-静态*/
    SPS_STATUS_ENUM enSemiGrantType;    /*指示当前授权是半静态激活/释放授权还是其他授权1-激活或释放授权，0-其他授权*/
    UL_TB_STRU  astTbData[2];
    UL_DCI_TYPE_ENUM_UINT16 enDciType;     /* DCI类型指示，DCI0或DCI4 */
    UINT16 usAntPort;
    UINT16 usCif;
    UINT16 usHoppingFlag;    /*Hopping flag*/
    UINT32 ulRbAssign;
    UINT16 usPuschTpc;       /*TPC command for scheduled PUSCH*/
    UINT16 usCyclicDmrs;     /*Cyclic shift for DM RS*/
    UINT16 usUlIndex;        /*UL index*/
    UINT16 usDaiInfo;        /*DAI信息域*/
    UINT16 usCqiRequest;     /*CQI request*/
    UINT16 usSrsReq;
    UL_RB_ALLOC_TYPE_ENUM_UINT16 enRbAllocType;
    UINT16 usPrecodeInfo;
    UINT16 usRbNum;          /*RB数目*/
    UINT16 usHopInfo;        /*跳频信息*/
    UINT16 usOnlyUciInfoFlg;
    UINT16 usRnti;
    UINT16 usRbNum0;
    UINT16 usRbNum1;
    UINT16 usRbStart0;
    UINT16 usRbStart1;

    UINT16 usRIV;          /*冗余版本号*/ /* 确认是否保留 */
    UINT16 usRsv;
}UL_DCI_STRU;

#if 0
/*****************************************************************************
 结构名    : DCI0_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/

typedef struct
{
    UINT16 usSemiStaticFlag; /*动态/半静态调度指示,0-动态,1-静态*/
    UINT16 usInitGrantFlag;  /*初始授权标志,1-初始,0-重传*/
    UINT16 usDci0ExistFlag;      /*DCI0存在标志,1-存在,0-不存在*/
    UINT16 usNewTransFlag;    /*指示是否为第一次收到的授权,0xffff-没有授权，1-已经收到授权*/
    SPS_STATUS_ENUM enSemiGrantType;    /*指示当前授权是半静态激活/释放授权还是其他授权1-激活或释放授权，0-其他授权*/
    UINT16 usAntPort;
    UINT16 usHoppingFlag;    /*Hopping flag*/
    UINT16 usTbSize;         /*TB size */
    UINT16 usRIV;             /*冗余版本号*/
    UINT16 usImcs;              /*调制阶数*/
    UINT16 usNewIndex;        /*新数据指示*/
    UINT16 usPuschTpc;       /*TPC command for scheduled PUSCH*/
    UINT16 usCyclicDmrs;     /*Cyclic shift for DM RS*/
    UINT16 usUlIndex;        /*UL index*/
    UINT16 usCqiRequest;     /*CQI request*/
    //UINT16 usRbStart;        /*RB起始位置*/
    UINT16 usRbNum;          /*RB数目*/
    UINT16 usHopInfo;        /*调频信息*/
    UINT16 usDaiInfo;        /*DAI信息域*/
    UINT16 usOnlyUciInfoFlg;
    UINT16 usRnti;
    /* BEGIN: Added by l00131321, 2012/12/17   问题单号:V7R2_MODIFY*/
    UL_RB_ALLOC_TYPE_ENUM_UINT16 enRbAllocType;
    UINT32 ulRbAssign;
    UINT16 usRbNum0;
    UINT16 usRbNum1;
    UINT16 usRbStart0;
    UINT16 usRbStart1;
}DCI0_STRU;
#endif

/*****************************************************************************
 结构名    : UL_OM_PUSCH_CAPTURE_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OMPUSCH捕获参数结构
*****************************************************************************/
typedef struct
{
    UINT32 ulProcessID;
    UL_DCI_STRU stDciInfo;
    UL_PUSCH_BPP_CODING_PARA_OM_STRU stPUSCHBbpCodingPara;
    //UL_PUSCH_BBP_MOD_PARA_STRU stPuschBbpModPara;
}UL_OM_PUSCH_CAPTURE_PARA_STRU;

/*****************************************************************************
 结构名    : UL_MOD_PUCCH1_BBP_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PUCCH格式1/1a/1b BBP配置参数结构
*****************************************************************************/


typedef struct
{
    /*PUCCH_FORMAT_REG*/
    UINT32 ulPUCCH_FORMAT     :3;
    UINT32                    :29;

    /*PUCCH_COMMON_REG*/
    UINT32 ulU_EVEN           :5;                      /*偶时隙基序列组号u*/
    UINT32                    :3;
    UINT32 ulEVEN_PRB_INDEX   :7;                      /*偶时隙PRB位置*/
    UINT32                    :1;
    UINT32 ulU_ODD            :5;                      /*奇时隙基序列组号u*/
    UINT32                    :3;
    UINT32 ulODD_PRB_INDEX    :7;                      /*奇时隙PRB位置*/
    UINT32                    :1;

    /*PUCCH1_PARA_REG*/
    UINT32 ulEVEN_OC_INDEX    :2;                      /*偶时隙正交序列索引*/
    UINT32                    :2;
    UINT32 ulODD_OC_INDEX     :2;                      /*偶时隙正交序列索引*/
    UINT32                    :2;
    UINT32 ulEVEN_S_NS        :1;                       /*偶时隙加扰系数*/
    UINT32                    :3;
    UINT32 ulODD_S_NS         :1;                       /*偶时隙加扰系数*/
    UINT32                    :3;
    UINT32 ulODD_N_SF_PUCCH   :3;                       /*奇时隙PUCCH格式指示*/
    UINT32                    :13;

    /* BEGIN: Added by l00131321, 2012/11/24   问题单号:V7R2_MODIFY*/
    /*PUCCH23_SCRAMBL_REG*/
    UINT32 ulPUCCH2_SCRAMBL   :31;                       /*PUCCH格式23扰码初相*/
    UINT32                    :1;

    /*PUCCH123_EVEN_NCS_REG*/
    UINT32 ulEVEN_NCS         :28;                      /*偶时隙循环移位*/
    UINT32                    :4;

    /*PUCCH123_ODD_NCS_REG*/
    UINT32 ulODD_NCS          :28;                      /*奇时隙循环移位*/
    UINT32                    :4;

    /*PUCCH3_PARA_REG*/
    UINT32 ulPUC3_NOC_EVEN    :3;                      /*偶时隙正交序列索引*/
    UINT32                    :1;
    UINT32 ulPUC3_NOC_ODD     :3;                      /*奇时隙正交序列索引*/
    UINT32                    :1;
    UINT32 ulPUC3_NSF_ODD     :3;                      /*奇时隙符号格式*/
    UINT32                    :21;

    /*PUCCH_AMP_REG*/
    UINT32 ulPUC_AMP_B        :17;
    UINT32                    :15;

    /*PUCCH_ANTENNA_REG*/
    UINT32 ulAntennaSel       :1;
    UINT32                    :31;

}UL_PUCCH_BBP_MOD_PARA_STRU;



/*****************************************************************************
 结构名    : UL_OM_PUCCH_CAPTURE_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OMPUCCH捕获参数结构
*****************************************************************************/
typedef struct
{
    UL_PUCCH_FORMAT_ENUM_UINT16 enPUCCH_Format;
    union
    {
        UINT16 usnPUCCH1;
        UINT16 usnPUCCH2;
        UINT16 usnPUCCH3;
    }unPucchResoureIdx;

    UL_PUCCH_BBP_MOD_PARA_STRU stPucchBbpPara;
}UL_OM_PUCCH_CAPTURE_PARA_STRU;

/*****************************************************************************
 结构名    : UL_MOD_SRS_BBP_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OMSRSBBP调制参数结构
*****************************************************************************/
/*SRS BBP配置参数结构*/

typedef struct
{
   /*SRS_POS_REG*/
   UINT32 ulK0_LAST1    :11;
   UINT32               :1;
   UINT32 ulK0_LAST2    :11;
   UINT32               :1;
   UINT32 ulSymInd      :2;
   UINT32               :6;

   /*SRS_BASE_REG*/
   UINT32 ulSRS_Q       :11;
   UINT32               :1;
   UINT32 ulSRS_U       :5;
   UINT32               :3;
   UINT32 ulN_SRS       :3;
   UINT32               :9;

   /*SRS_LEN_REG*/
   UINT32 ulSRS_N_ZC_RS :11;
   UINT32               :1;
   UINT32 ulM_SC_B      :11;
   UINT32               :9;

   /* BEGIN: Added by l00131321, 2012/11/24   问题单号:V7R2_MODIFY*/
   /*SRS_AMP_REG*/
   UINT32 ulSRS_AMP_B   :17;
   UINT32               :15;
   /*SRS_ANTENNA_REG*/
   UINT32 ulSRS_ANTENNA;

}UL_MOD_SRS_BBP_PARA_STRU;

/*****************************************************************************
 结构名    : PHY_OM_UPLINK_CAPTURE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OM上行捕获指示结构
*****************************************************************************/
typedef struct
{
    UINT16 usOmType;
    UINT16 usSfn;
    UINT16 usSbfn;
    UINT16 usRev;
    union
    {
        UL_OM_PUCCH_CAPTURE_PARA_STRU stPucchCaptruePara;
        UL_OM_PUSCH_CAPTURE_PARA_STRU stPuschCaptruePara;
        UL_MOD_SRS_BBP_PARA_STRU stSrsBbpPara;
    }unCaptrueInfo;
}PHY_OM_UPLINK_CAPTURE_IND_STRU;

typedef struct __LPHY_IND_UL_PUSCH_CAPTURE_INFO_STRU__
{
    UINT16 usOmType;
    UINT16 usSfn;
    UINT16 usSbfn;
    UINT16 usPuschRate;
    /* BEGIN: Added by l00131321, 2011/8/24   问题单号:DTS2011082402841*/
    //UINT32 ulMacDataInvalid;
    UINT32 ulWarningReg;
    INT16 sPuschTransPwr;
    UINT16 usRev;
    UL_OM_PUSCH_CAPTURE_PARA_STRU stPuschCaptruePara;

}LPHY_IND_UL_PUSCH_CAPTURE_INFO_STRU;

typedef struct __LPHY_IND_UL_PUCCH_CAPTURE_INFO_STRU__
{
    UINT16 usOmType;
    UINT16 usSfn;
    UINT16 usSbfn;
    /* UINT16 usRev; */
    INT16 sPucchTransPwr;
    UL_PUCCH_FORMAT_ENUM_UINT16 enPUCCH_Format;
    //UL_OM_PUCCH_CAPTURE_PARA_STRU stPucchCaptruePara;
}LPHY_IND_UL_PUCCH_CAPTURE_INFO_STRU;

typedef struct __LPHY_IND_UL_SRS_CAPTURE_INFO_STRU__
{
    UINT16 usOmType;
    UINT16 usSfn;
    UINT16 usSbfn;
    /* UINT16 usRev; */
    INT16 sSrsTransPwr;
    /* BEGIN: Added by l00131321, 2012/12/6   问题单号:V7R2_MODIFY*/
    //UL_SRS_CFG_PARA_STRU stSrsCfg;
    UL_MOD_SRS_BBP_PARA_STRU stSrsBbpPara;
}LPHY_IND_UL_SRS_CAPTURE_INFO_STRU;

/* BEGIN: Added by l00131321, 2011/6/7   问题单号:DTS2011062802382*/

typedef struct
{
    UINT32 ulMcsCnt[UL_MAX_TB_NUM];  //[cw0/cw1]
    UINT32 ulRBTotal[UL_MAX_TB_NUM];
}UL_MCS_RB_STRU;

typedef struct __LPHY_IND_UL_SCHEUL_STATIC_INFO_STRU__
{
    UL_MCS_RB_STRU astMcsRb[OM_UL_MAX_CELL_NUM][32];  /*[cc][mcs] --V7R5_DT 1.6 根据路测需求做了上行 MCS/RB统计 CC 和 TB的扩展 ，其余参数未扩展 */

    UINT32 aulSlot0RbCnt[OM_UL_MAX_CELL_NUM][100];
    UINT32 aulSlot1RbCnt[OM_UL_MAX_CELL_NUM][100];
    UINT32 aulRbTotal[OM_UL_MAX_CELL_NUM];
    UINT32 ulPeriodCnt;
}LPHY_IND_UL_SCHEUL_STATIC_INFO_STRU;


typedef struct
{
    UINT32 ulTotal;
    UINT32 ulIniBler;
    UINT32 ulReBler;
}UL_HARQBLER_STRU;


typedef struct __LPHY_IND_UL_HARQBLER_INFO_STRU__
{
    UL_HARQBLER_STRU stPeriod;
    UL_HARQBLER_STRU stAccumTotal;
    UINT32 ulPeriodCnt;
}LPHY_IND_UL_HARQBLER_INFO_STRU;

#if 0
typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16    usRsv;
}LPHY_REQ_UL_PD_INFO_STRU;


typedef struct
{
    INT16                       sulPwr;        /*当前子帧发送功率*/
    INT16                       sDeltap;       /*当前子帧发射用到的DelatP补偿*/
    UINT16                      usPdval;       /*PD回读值*/
    UINT16                      usIfEnablePd;  /*当前子帧是否使能下个子帧的PD*/
    UINT16                      usIfReadPd;    /*当前子帧是否使能子帧的PD*/
    UINT32                      ulCenterUlPonit; /*中心频点*/
    UINT16                      usPdRbSum;        /*RF本身的原因，低RB个数PD回读不准确*/
    UINT16                      usRsv;
}UL_PD_SBSFN_INFO_STRU;
typedef struct
{
    UINT16                      usIfValidDelta;
    INT16                       usPdDelta;
    UINT16                      usCenFreq;
    INT16                       sPwrByPd1;
    INT16                       sPwrByPd2;
    UINT16                      usPdSfn;
    UINT16                      usPdSbfn;
    UINT16                      usPdPwrVlidNum;
    INT16                       sPdPwrDeltSum;
	UINT16                      usRsv;
    UL_PD_SBSFN_INFO_STRU       ausSbsfnPdinfo[UL_MAX_SUBFRAME_NUM];
}UL_PD_STATE_STRU;

typedef struct
{
    UINT16                      usNoContinuStat;
    UINT16                      usNoEnable;
    UINT16                      usLongThan10msStat;
    UINT16                      usInvalidPwr;
    UINT16                      usPdReadFail;
    UINT16                      usPdRangeOut;
}UL_PD_STAT_STRU;

typedef struct
{
    UINT16 usSfn;
    UINT16 usSbfn;
    UINT16 usNoContinuStat;
    UL_PD_STAT_STRU             stPdStatInfo;
    UL_PD_STATE_STRU            stPdState;
}LPHY_IND_UL_PD_INFO_STRU;

#endif
enum
{
    DCI_INVALID = 0,
    UL_DCI_VALID,
    DL_DCI_VALID
};
typedef UINT16 RAR_DCI_VALID_ENUM_UINT16;
enum
{
    UL_ACCESS_INVALID = 0,
    UL_ACCESS_START,
    UL_ACCESS_FINISH
};
typedef UINT16 UL_ACCESS_STATUS_ENUM_UINT16;

enum
{
    UL_MSG3_INVALID = 0,
    UL_MSG3_START,
    UL_MSG3_ACK_RECEIVE
};
typedef UINT16 UL_MSG3_STATUS_ENUM_UINT16;

typedef struct
{
    /* BEGIN: Added by sunyanjie, 2011/11/14   问题单号:DTS2011111602553*/
    //UINT16 usMsg3SndFlg;
    UL_MSG3_STATUS_ENUM_UINT16 enMsg3SndFlg;
    UINT16 usAccessMode;
    UINT16 usTcRnti;
    UINT16 usPdcchOrderFlg;
    UINT16 usRarAck;
    UINT16 usRarHarqNum;
    UL_ACCESS_STATUS_ENUM_UINT16 enAccessStatus;
    RAR_DCI_VALID_ENUM_UINT16 enDciReceived;
}UL_RAR_PROCESS_STRU;


typedef struct
{
    UINT32 ulMsgId;
    UINT16 usSfn;
    UINT16 usSbSfn;
    UINT32 aulTraceInfo[4];
}OM_DSP_TRACE_INFO;

typedef enum
{
    DCI0_INVALID = 0,
    DCI0_VALID,
    DCI0_USED
}DCI_VALID_ENUM;

typedef UINT16 DCI_VALID_ENUM_UINT16;


/*****************************************************************************
 结构名    : UL_GRANT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    DCI_VALID_ENUM_UINT16 usDci0ValidFlag;
    //UINT16 usUlTpcValidFlag;     /*3/3A有效标志*/
    UINT16 usFrameNum;       /*生效帧号*/
    UINT16 usSubFrameNum;    /*生效子帧号*/
    //UINT16 usUlTpc;          /*PUSCH的3/3A的TPC*/
    UINT16 usUeAntMode;
    //DCI0_STRU stDci0;
    UL_DCI_STRU stDciInfo;
}UL_GRANT_STRU;

typedef struct
{
    UINT16 usSfn;
    UINT16 usSbfn;

    UINT16 usPucchPuschSimul;
    INT16 sPhr;
    INT16 sPhr2;
    INT16 sPmax;

    UINT8 ucPhrType;
    UINT8 aucPhrValue[MAX_PHR_SIZE];
    //UINT8 aucRev[2];
}PHY_OM_PHR_INFO_IND_STRU;

enum __MCS_QM_ENUM__
{
    MCS_QPSK_MOD = 0,
    MCS_16QAM_MOD,
    MCS_64QAM_MOD,
    MCS_QM_INVALID
};
typedef UINT16 MCS_QM_ENUM_UINT16;

/************************************************************
                           4. TRACE数据结构定义
************************************************************/
typedef enum __LPHY_TRACE_UL_ENUM__
{
    LPHY_TRACE_UL_LOG_STATE_REQ_ERR           = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x1),
    LPHY_TRACE_UL_LOG_SRS_CFG_ERR             = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x2),
    LPHY_TRACE_UL_LOG_ACKTPC_INVALID_ERR      = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x3),
    LPHY_TRACE_UL_LOG_FDD_ACK_STORE_ERR       = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x4),
    LPHY_TRACE_UL_LOG_TDD_ACK_REC_SUBFRM_ERR  = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x5),
    LPHY_TRACE_UL_LOG_TDD_ACK_STORE_ERR       = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x6),
    LPHY_TRACE_UL_LOG_TDD_ACK_NUM_ERR         = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x7),
    LPHY_TRACE_UL_LOG_MULTI_ADDRESS_ERR       = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x8),
    LPHY_TRACE_UL_LOG_NCCE_ERR                = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x9),
    LPHY_TRACE_UL_LOG_PUCCH_FORMAT_ERR        = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0xA),
    LPHY_TRACE_UL_LOG_PRACH_CFG_IDX_ERR       = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0xB),
    LPHY_TRACE_UL_LOG_TPC_IDX_ERR             = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0xC),
    LPHY_TRACE_UL_LOG_RAR_SLOT_ERR            = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0xD),
    LPHY_TRACE_UL_LOG_SRS_CELL_CFG_IDX_ERR    = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0xE),
    LPHY_TRACE_UL_LOG_PRACH_FORMAT_ERR        = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0xF),
    LPHY_TRACE_UL_LOG_PREAMBLE_IDX_ERR        = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x10),
    LPHY_TRACE_UL_LOG_NCS_IDX_ERR             = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x11),
    LPHY_TRACE_UL_LOG_ROOTSEQ_IDX_ERR         = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x12),
    LPHY_TRACE_UL_LOG_RA_PRB_ERR              = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x13),
    LPHY_TRACE_UL_LOG_HALF_SEARCH_ERR         = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x14),
    LPHY_TRACE_UL_LOG_IMCS_ERR                = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x15),
    LPHY_TRACE_UL_LOG_RBSUM_ERR               = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x16),
    LPHY_TRACE_UL_LOG_CQIREQ_ERR              = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x17),
    LPHY_TRACE_UL_LOG_HOPPINGINFO_ERR         = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x18),
    LPHY_TRACE_UL_LOG_RIV_ERR                 = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x19),
    LPHY_TRACE_UL_LOG_DMRS1_ERR               = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x1A),
    LPHY_TRACE_UL_LOG_DMRS2_ERR               = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x1B),
    LPHY_TRACE_UL_LOG_RBNUM_ERR               = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x1C),
    LPHY_TRACE_UL_LOG_BANDWIDTH_INDEX_ERR     = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x1D),
    LPHY_TRACE_UL_LOG_MASKCODE_INDEX_ERR      = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x1E),
    LPHY_TRACE_UL_LOG_CQI_TRANS_TIME_ERR      = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x1F),
    LPHY_TRACE_UL_LOG_FDD_ACK_SCHED_ERR       = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x20),
    LPHY_TRACE_UL_LOG_TDD_ACK_SCHED_ERR       = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x21),
    LPHY_TRACE_UL_LOG_CODERATE_EX_ERR         = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x22),
    LPHY_TRACE_UL_LOG_MBX_ERR                 = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x23),
    LPHY_TRACE_UL_LOG_TTI_BUNDL_STATE_CHANGE  = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x24),
    LPHY_TRACE_UL_TA_TIMER_TIMEOUT_ERR        = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x25),
    LPHY_TRACE_UL_CHANNEL_RELEASE             = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x26),
    LPHY_TRACE_UL_SRS_CONFIG                  = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x27),
    LPHY_TRACE_UL_SRS_RELEASE                 = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x28),
    LPHY_TRACE_UL_HARQ_MAX_NUM_ERR            = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x29),
    LPHY_TRACE_UL_UCI_ONLY_CONFIG             = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x2A),
    LPHY_TRACE_UL_PREAMBLE_TRANS_REQUEST      = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x2B),
    LPHY_TRACE_UL_PREAMBLE_TRANSMIT           = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x2C),
    LPHY_TRACE_UL_NONCONTENT_RAR_CONFIG       = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x2D),
    LPHY_TRACE_UL_CONTENT_RAR_CONFIG          = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x2E),
    LPHY_TRACE_UL_MSG3_TRANSMIT               = OM_CMD_ID(LPHY_UL_MID, OM_TYPE_TRACE, 0x2F),
}LPHY_TRACE_UL_ENUM;

#define UL_TRACE_ERR_LEN   16

typedef struct __LPHY_TRACE_UL_CODERATE_EX_ERR_INFO_STRU__
{
    UINT16 usSfn;
    UINT16 usSbfn;
    UINT32 ulTBSize;
    UINT32 usCalRateG;
    UINT32 usPuschRate;
}LPHY_TRACE_UL_CODERATE_EX_ERR_INFO_STRU;

typedef struct __LPHY_TRACE_UL_FRAME_INFO_STRU__
{
    UINT16 usSfn;
    UINT16 usSbfn;
    UINT16 ulData[4];
}LPHY_TRACE_UL_FRAME_INFO_STRU;


typedef struct __LPHY_TRACE_UL_SRS_CONFIG_STRU__
{
    UINT16 usSfn;
    UINT16 usSbfn;
    UINT16 usUlSrsConfigPeriod;
    UINT16 usReserved;
}LPHY_TRACE_UL_SRS_CONFIG_STRU;

typedef struct __LPHY_TRACE_UL_RAR_CONFIG_STRU__
{
    UINT16 usSfn;
    UINT16 usSbfn;
    UINT16 enRaAccessType;
    UINT16 usTaVal;
}LPHY_TRACE_UL_RAR_CONFIG_STRU;


typedef struct __LPHY_HARQ_INFO_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usRptHarqInfoPeriod;
} LPHY_HARQ_INFO_REQ_STRU;

typedef struct __LPHY_SG_UL_SCHEDULE_STAT_INFO_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16    usReportPeriod;
} LPHY_SG_UL_SCHEDULE_STAT_INFO_REQ_STRU;

typedef struct __LPHY_SG_PUSCH_HARQ_BLER_STAT_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usTransSuccRptPeriod;
}LPHY_SG_PUSCH_HARQ_BLER_STAT_REQ_STRU;

typedef struct
{
    UINT16 usPowerInfoActFlg;
    UINT16 usPuschInfoActFlg;
    //LPHY_HARQ_INFO_REQ_STRU stHarqInfoActPara;
    UINT16 usUlAccessInfoActFlg;
    LPHY_SG_UL_SCHEDULE_STAT_INFO_REQ_STRU stUlSchedStatActPara; //1.11
    //LPHY_SG_PUSCH_HARQ_BLER_STAT_REQ_STRU stUlPuschHarqBlerStatPara;
}UL_SG_OM_DATA_REQUEST_FLG_STRU;

typedef struct __LPHY_SG_UL_SCHEDULE_STAT_INFO_IND_STRU__
{
    //UINT32 aulMcsCnt[2][2][32];  //[cc][tb][mcs]
    UINT32 aulQPSKTotalNum[OM_UL_MAX_CELL_NUM][UL_MAX_TB_NUM]; //[cc][tb]
    UINT32 aul16QAMTotalNum[OM_UL_MAX_CELL_NUM][UL_MAX_TB_NUM];
    UINT32 aul64QAMTotalNum[OM_UL_MAX_CELL_NUM][UL_MAX_TB_NUM];
    UINT32 aulThroughput[OM_UL_MAX_CELL_NUM][UL_MAX_TB_NUM];
}LPHY_SG_UL_SCHEDULE_STAT_INFO_IND_STRU;

typedef struct __LPHY_SG_UL_POWER_INFO_IND_STRU__
{
    UINT16  usSFN;
    UINT16  usSubFn;
    INT16   sPuschTransPwr[OM_UL_MAX_CELL_NUM];  //[cc]
    INT16   sP0[OM_UL_MAX_CELL_NUM];
    UINT16  usPl[OM_UL_MAX_CELL_NUM];
    UINT16  usAlf[OM_UL_MAX_CELL_NUM];
    INT16   sFi[OM_UL_MAX_CELL_NUM];
    INT16   sPucchTransPwr;//辅小区不支持puc
    INT16   sGiValue;//辅小区不支持puc
    INT16   sSrsTransPwr[OM_UL_MAX_CELL_NUM];
    UINT16  usSrsRBNum[OM_UL_MAX_CELL_NUM];
    //UINT16  usRsv[2];
}LPHY_SG_UL_POWER_INFO_IND_STRU; //1.1


typedef struct __LPHY_UL_POWER_INFO_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usRsv;
}LPHY_UL_POWER_INFO_REQ_STRU;


typedef struct
{
    UINT16  usUlMcs;
    MCS_QM_ENUM_UINT16  enUlModSched;
    UINT32  ulTbSize;
    UINT16  usRvIndex;
    UINT16  usRsv;
}TB_PARA_STRU;

typedef struct __UL_PUSCH_RB_PARA_STRU__
{
	UL_RB_ALLOC_TYPE_ENUM_UINT16 enRbAllocType;
    UINT16  usPuschRb0Num;
    UINT16  usPuschRb0Start;
    UINT16  usPuschRb1Num;
    UINT16  usPuschRb1Start;
    UINT16  usRsv;
    TB_PARA_STRU  astTbPara[UL_MAX_TB_NUM];//[tb]
} UL_PUSCH_RB_PARA_STRU;//1.4

typedef struct __LPHY_UL_PUSCH_INFO_IND_STRU__
{
    UINT16  usSFN;
    UINT16  usSubFn;
    UINT16  usHarqId[OM_UL_MAX_CELL_NUM];//[cc]
    UINT16  usPuschRate[OM_UL_MAX_CELL_NUM];
    SINT16  sPuschTransPwr[OM_UL_MAX_CELL_NUM];
    UL_PUSCH_RB_PARA_STRU astPusRb[OM_UL_MAX_CELL_NUM];//[cc]
} LPHY_UL_PUSCH_INFO_IND_STRU;//1.4

typedef struct __LPHY_UL_PUSCH_INFO_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usRsv;
} LPHY_UL_PUSCH_INFO_REQ_STRU;
#if 0
typedef struct __LPHY_UL_ACCESS_INFO_IND_STRU__
{
    UINT16 usSFN;
    UINT16 usSubFn;
    INT16  sPrachTransPower[OM_UL_MAX_CELL_NUM];
    UINT16 usRaRntiValue[OM_UL_MAX_CELL_NUM];
}LPHY_UL_ACCESS_INFO_IND_STRU;//1.1(2)

typedef struct __LPHY_UL_ACCESS_INFO_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usRsv;
} LPHY_UL_ACCESS_INFO_REQ_STRU;
#endif
typedef struct
{
    UINT32 ulSchedStatCnt;
}UL_SG_OM_DATA_REPORT_COUNT_STRU;

typedef struct
{
    UINT32 aulTransSuccNum[5];
    UINT32 ulReTransFailNum;
}LPHY_PUSCH_HARQ_BLER_STAT_IND_STRU;





/************************************************************
                           5. DT路测数据结构定义
************************************************************/

/*****************************************************************************
结构名    : UL_OM_DATA_CAPTURE_FLG_STRU
协议表格  :
ASN.1描述 :
结构说明  :
*****************************************************************************/



/*typedef enum __LPHY_DT_REQ_MSGID_UL__
{
    LPHY_DT_UL_POWER_INFO_REQ              =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_DT, 0x1),
    LPHY_DT_UL_PUSCH_INFO_REQ              =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_DT, 0x2),
    LPHY_DT_UL_SCHEDULE_STAT_INFO_REQ      =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_DT, 0x3),
    LPHY_DT_HARQ_INFO_REQ                  =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_DT, 0x4),
    LPHY_DT_UL_ACCESS_INFO_REQ             =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_DT, 0x5),
    LPHY_DT_TA_INFO_REQ                    =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_DT, 0x6),
    LPHY_DT_PUSCH_HARQ_BLER_STAT_REQ      =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_DT, 0x7)

}LPHY_DT_REQ_MSGID_UL_ENUM;*/


typedef struct __LPHY_DT_UL_POWER_INFO_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usRsv;
}LPHY_DT_UL_POWER_INFO_REQ_STRU;
typedef struct __LPHY_DT_UL_PUSCH_INFO_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usRsv;
} LPHY_DT_UL_PUSCH_INFO_REQ_STRU;

typedef struct __LPHY_DT_UL_SCHEDULE_STAT_INFO_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16    usReportPeriod;
} LPHY_DT_UL_SCHEDULE_STAT_INFO_REQ_STRU;

typedef struct __LPHY_DT_HARQ_INFO_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usRptHarqInfoPeriod;
} LPHY_DT_HARQ_INFO_REQ_STRU;

typedef struct __LPHY_DT_UL_ACCESS_INFO_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usRsv;
} LPHY_DT_UL_ACCESS_INFO_REQ_STRU;

typedef struct __LPHY_DT_TA_INFO_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usRsv;
}LPHY_DT_TA_INFO_REQ_STRU;
typedef struct __LPHY_DT_PUSCH_HARQ_BLER_STAT_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16 usTransSuccRptPeriod;
}LPHY_DT_PUSCH_HARQ_BLER_STAT_REQ_STRU;




typedef enum __LPHY_DT_IND_MSGID_UL__
{
    LPHY_DT_UL_POWER_INFO_IND              =  OM_CMD_ID(LPHY_UL_MID, OM_TYPE_DT, 0x1),
    LPHY_DT_UL_PUSCH_INFO_IND             ,
    LPHY_DT_UL_PUSCH_INFO_CA_IND          ,
    LPHY_DT_UL_SCHEDULE_STAT_INFO_IND     ,
    LPHY_DT_HARQ_INFO_IND                 ,
    LPHY_DT_HARQ_INFO_CA_IND              ,
    LPHY_DT_UL_ACCESS_INFO_IND            ,
    LPHY_DT_TA_INFO_IND                   ,
    LPHY_DT_PUSCH_HARQ_BLER_STAT_IND

}LPHY_DT_IND_MSGID_UL_ENUM;


typedef struct __LPHY_DT_UL_POWER_INFO_IND_STRU__
{
    UINT16  usSFN;
    UINT16  usSubFn;
    INT16   sPuschTransPwr;
    INT16   sP0;
    UINT16  usPl;
    UINT16  usAlf;
    INT16   sFi;
    INT16   sPucchTransPwr;
    INT16   sGiValue;
    INT16   sSrsTransPwr;
    UINT16  usSrsRBNum;
    UINT16  usRsv;
}LPHY_DT_UL_POWER_INFO_IND_STRU;


typedef struct __LPHY_DT_UL_PUSCH_INFO_IND_STRU__
{
    UINT16  usSFN;
    UINT16  usSubFn;
	UL_RB_ALLOC_TYPE_ENUM_UINT16 enRbAllocType;
    UINT16  usPuschRb0Num;
    UINT16  usPuschRb0Start;
    UINT16  usPuschRb1Num;
    UINT16  usPuschRb1Start;
    UINT16  usRvIndex;
    UINT16  usUlMcs;
    MCS_QM_ENUM_UINT16  enUlModSched;
    UINT16  usTbSize;
    UINT16  usHarqId;
} LPHY_DT_UL_PUSCH_INFO_IND_STRU;



typedef struct __LPHY_DT_UL_SCHEDULE_STAT_INFO_IND_STRU__
{
    UINT32 aulMcsCnt[32];
    UINT32 ulQPSKTotalNum;
    UINT32 ul16QAMTotalNum;
    UINT32 ul64QAMTotalNum;
    UINT32 ulThroughput;
}LPHY_DT_UL_SCHEDULE_STAT_INFO_IND_STRU;

typedef struct __LPHY_DT_HARQ_INFO_CA_IND_STRU__
{
    UINT8  ucCcValidFlg;
	UINT8  ucCcIdx;
	UINT16 usRsv;

    UINT16 usPuschMaxTransNum;
    UINT16 usUlHarqProcessNum;
    UINT16 usDlHarqProcessNum;
    UINT16 usRsv0;
}LPHY_DT_HARQ_INFO_CA_IND_STRU;

typedef struct __LPHY_DT_UL_ACCESS_INFO_IND_STRU__
{
    UINT16 usSFN;
    UINT16 usSubFn;
    INT16  sPrachTransPower;
    UINT16 usRaRntiValue;
}LPHY_DT_UL_ACCESS_INFO_IND_STRU;

typedef struct __LPHY_DT_TA_INFO_IND_STRU__
{
    UINT16   usSFN;
    UINT16   usSubFn;
    UINT16   usTaValue;
    UINT16   usRsv;
    UINT8    ucCcValidFlag;
    UINT8    ucCcIdx;
    INT16    sTimeDeviation;
}LPHY_DT_TA_INFO_IND_STRU;

typedef struct
{
    UINT32 ulTransSuccNum[5];
    UINT32 ulReTransFailNum;
}LPHY_DT_PUSCH_HARQ_BLER_STAT_IND_STRU;


typedef struct
{
    UINT16 usPowerInfoActFlg;
    UINT16 usPuschInfoActFlg;
    LPHY_DT_HARQ_INFO_REQ_STRU stHarqInfoActPara;
    UINT16 usUlAccessInfoActFlg;
    UINT16 usTaInfoActFlg;
    LPHY_DT_UL_SCHEDULE_STAT_INFO_REQ_STRU stUlSchedStatActPara;
    LPHY_DT_PUSCH_HARQ_BLER_STAT_REQ_STRU stUlPuschHarqBlerStatPara;

}UL_DT_OM_DATA_REQUEST_FLG_STRU;


typedef struct
{
    UINT32 ulSchedStatCnt;
    UINT32 ulHarqRptCnt;
    UINT32 ulHarqBlerStatCnt;
}UL_DT_OM_DATA_REPORT_COUNT_STRU;



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __UL_OM_DEF_H__ */

