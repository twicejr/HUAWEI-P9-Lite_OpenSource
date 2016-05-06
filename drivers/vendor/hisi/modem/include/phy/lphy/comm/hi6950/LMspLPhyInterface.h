/*****************************************************************************
  文 件 名   : LmspLPhyInterface.h
  版 本 号   : V1.0
  作    者   : DSP
  生成日期   : 2013年
  功能描述   : LMSP和LDSP之间的接口文件，主要是CT和BT使用
  修改历史   :
  1.日    期 : 2013年12月13日
    作    者 : DSP
    修改内容 : 创建文件

  2.日    期 : 2013年8月29日
    作    者 : luzhejun
    修改内容 : 增加LTE与WIFI共存的接口


*****************************************************************************/
#ifndef _LMSP_LPHY_INTERFACE
#define _LMSP_LPHY_INTERFACE

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

#ifdef MBX_RTT_CBT
#define CT_OM_MSG_HANDLING_DOWN         (0)
#define CT_OM_MSG_PARA_ERROR            (1)
#define CT_OM_TEST_MODE_REQ                (0x65)
#define CT_OM_BANDSW_SET_REQ               (0x66)
#define CT_OM_FCHAN_SET_REQ                (0x67)
#define CT_OM_AFC_C1_FIXSET_REQ            (0x12c)
#define CT_OM_AFC_C1_FIXREFRESH_REQ        (0x12d)
#define CT_OM_AFC_C2_FIXSET_REQ            (0x12e)
#define CT_OM_AFC_C2_FIXREFRESH_REQ        (0x12f)
#define CT_OM_DCXO_AFC_CALI_REQ            (0x130)
#define CT_OM_DCXO_HKADC_QUERY_REQ         (0x131)
#define CT_OM_CALIDCOC_SET_REQ             (0x132)
#define CT_OM_DCOC_RESULT_QUERY_REQ        (0x133)
#define CT_OM_CALIIP2_SET_REQ              (0x134)
#define CT_OM_IP2_RESULT_QUERY_REQ         (0x135)
#define CT_OM_CALITXIQ_SET_REQ             (0x136)
#define CT_OM_TXIQ_RESULT_QUERY_REQ        (0x137)
#define CT_OM_APC_CALI_PARASET_REQ         (0x138)
#define CT_OM_AGC_CALI_PARASET_REQ         (0x139)
#define CT_OM_APC_CALI_START_REQ           (0x13a)
#define CT_OM_TRIG_STARTUS_QUERY_REQ       (0x13b)
#define CT_OM_AGC_CALI_RESULT_QUERY_REQ    (0x13c)
#define CT_OM_TEMP_QUERY_REQ               (0x13d)
#define CT_OM_DCXO_TEMP_REFRESH_REQ        (0x13e)
#define CT_OM_LTXON_REQ                    (0x13f)

/*Noise Tool Begin*/
#define NOISE_TOOL_OM_PARA_SET_REQ         (0x140)
#define NOISE_TOOL_OM_RST_QRY_REQ          (0x141)
/*Noise Tool End*/

#define NCIT_OM_PARA_SET_REQ               (0x15e)
#define NCIT_OM_BW_SET_REQ                 (0x15f)
#define NCIT_OM_SYNC_SET_REQ               (0x160)
#define NCIT_OM_SYNC_STATUS_QUERY_REQ      (0x161)
#define NCIT_OM_SEGMENT_SET_REQ            (0x162)
#define NCIT_OM_TXMODU_SET_REQ             (0x163)
#define NCIT_OM_TXRBNUM_SET_REQ            (0x164)
#define NCIT_OM_TX_RBPOS_SET_REQ           (0x165)
#define NCIT_OM_TX_POW_SET_REQ             (0x166)
#define NCIT_OM_TX_CHTYPE_SET_REQ          (0x167)
#define NCIT_OM_SEGMENT_LEN_SET_REQ        (0x168)
#define NCIT_OM_RX_STAPERIOD_SET_REQ       (0x169)
#define NCIT_OM_RX_UPPARA_SET_REQ          (0x16a)
#define NCIT_OM_TEST_STATUS_QUERY_REQ      (0x16b)
#define NCIT_OM_RX_BLER_QUERY_REQ          (0x16C)
#define NCIT_OM_TEST_START_REQ             (0x16d)
#define NCIT_OM_TEST_STOP_REQ              (0x16e)
#define NCIT_OM_TDD_SBFN_SET_REQ           (0x16f)
#define NCIT_OM_COMPARA_SET_REQ            (0x172)
#define NCIT_OM_TXPARA_SET_REQ             (0x173)

/*工具侧需求不同的版本消息ID不能相同,所以此处与austin不一样*/
#define RFTOOL_OM_TRX_SET_REQ             (0X5050)  /*参数配置*/
#define RFTOOL_OM_RSSI_QRY_REQ            (0x5051)  /*RSSI 上报*/
#define RFTOOL_OM_RSSI_STAR_REQ           (0x5052)  /*RSSI 查询启动*/

#endif
#define OM_PHY_CT_TEST_MODE_REQ		                 0X10000
#define PHY_OM_CT_TEST_MODE_CNF		                 0X10000
#define OM_PHY_CT_TXON_REQ	                         0X10020
#define PHY_OM_CT_TXON_CNF		                     0X10020
#define OM_PHY_CT_FREQ_SET_REQ	                     0X10040
#define PHY_OM_CT_FREQ_SET_CNF		                 0X10040
#define OM_PHY_CT_TXPOW_SET_REQ	                     0X10060
#define PHY_OM_CT_TXPOW_SET_CNF		                 0X10060
#define OM_PHY_CT_VCTCXO_SET_REQ	                 0X10080
#define PHY_OM_CT_VCTCXO_SET_CNF		             0X10080
#define OM_PHY_CT_RXON_REQ	                         0X100A0
#define PHY_OM_CT_RXON_CNF		                     0X100A0
#define OM_PHY_CT_RXANT_SET_REQ	                     0X100C0
#define PHY_OM_CT_RXANT_SET_CNF		                 0X100C0
#define OM_PHY_CT_AAGC_SET_REQ	                     0X100E0
#define PHY_OM_CT_AAGC_SET_CNF		                 0X100E0
#define OM_PHY_CT_MEAS_RSSI_REQ	                     0X10100
#define PHY_OM_CT_MEAS_RSSI_CNF		                 0X10100
#define PHY_OM_CT_RSSI_IND		                     0X10110

/* 温度获取接口*/
#define OM_PHY_CT_VOLTAGE_REQ		                 0X10111
#define PHY_OM_CT_VOLTAGE_CNF		                 0X10111

/* AT^FAGC*/
#define OM_PHY_FAGC_REQ		                         0X10112
#define PHY_OM_FAGC_CNF		                         0X10112

#define OM_PHY_CT_FPA_SET_REQ                        0x10113 /*AT^FPA*/
#define PHY_OM_CT_FPA_SET_CNF                        0x10113

#define OM_PHY_CT_FDAC_SET_REQ                       0x10114 /*AT^FDAC*/
#define PHY_OM_CT_FDAC_SET_CNF                       0x10114


#define OM_PHY_CT_TSELRF_SET_REQ                     0x10115 /*AT^TSELRF*/
#define PHY_OM_CT_TSELRF_SET_CNF                     0x10115

#define OM_PHY_CT_FWAVE_SET_REQ                      0x10116
#define PHY_OM_CT_FWAVE_SET_CNF                      0x10116

#define OM_PHY_CT_F_FREQ_SET_REQ                    (0x10120)
#define PHY_OM_CT_F_FREQ_SET_CNF                    (0x10120)

#define OM_PHY_CT_F_TXPOW_SET_REQ                   (0X10130)
#define PHY_OM_CT_F_TXPOW_SET_CNF        (0X10130)

#define OM_PHY_CT_F_AAGC_SET_REQ         (0X10140)
#define PHY_OM_CT_F_AAGC_SET_CNF         (0X10140)

#define PHY_OM_CT_F_MEAS_RSSI_IND        (0X10150)

#define PHY_OM_CT_F_MEAS_CMTMS_IND       (0X10160)

#define OM_PHY_CT_F_PA_SET_REQ           (0X10170)
#define PHY_OM_CT_F_PA_SET_CNF           (0X10170)

#define OM_PHY_CT_F_SEGMENT_SET_REQ      (0X10180)
#define PHY_OM_CT_F_SEGMENT_SET_CNF      (0X10180)

#define OM_PHY_CT_F_TXWAVE_SET_REQ       (0X10190)
#define PHY_OM_CT_F_TXWAVE_SET_CNF       (0X10190)

#define OM_PHY_CT_F_TRIGGER_SET_REQ      (0X101A0)
#define PHY_OM_CT_F_TRIGGER_SET_CNF      (0X101A0)

#define OM_PHY_CT_F_TRIGGER_RD_REQ       (0X101B0)
#define PHY_OM_CT_F_TRIGGER_RD_CNF       (0X101B0)


#define OM_PHY_CT_F_FBLK_SET_REQ         (0X101C0)
#define PHY_OM_CT_F_FBLK_SET_CNF         (0X101C0)

#define OM_PHY_CT_F_FIPSTART_SET_REQ     (0X101D0)
#define PHY_OM_CT_F_FIPSTART_SET_CNF     (0X101D0)
#define PHY_OM_CT_F_MEAS_IP2_IND          (0X101E0)

#define OM_PHY_CT_F_MAX_POWER_SET_REQ     (0X101f0)
#define PHY_OM_CT_F_MAX_POWER_SET_CNF     (0X101f0)

#define OM_PHY_CT_F_PA_POWER_SET_REQ      (0X101f4)
#define PHY_OM_CT_F_PA_POWER_SET_CNF       (0X101f4)

#define OM_PHY_LTESCINFO_RD_REQ          (0X101C2)
#define PHY_OM_LTESCINFO_RD_CNF          (0X101C2)

#define OM_PHY_CT_F_BANDSW_SET_REQ             (0X101F5)
#define PHY_OM_CT_F_BANDSW_SET_CNF             (0X101F5)


#define OM_PHY_BT_TEMP_DISPATCH_REQ        (0x10340)
#define PHY_OM_BT_TEMP_DISPATCH_CNF        (0x10340)

#define OM_PHY_CT_F_FPDMS_REQ              (0X101F6)
#define PHY_OM_CT_F_FPDMS_CNF              (0X101F6)

#define OM_PHY_CT_F_PD_AUTO_CAL_REQ             (0X101f7)
#define PHY_OM_CT_F_PD_AUTO_CAL_CNF             (0X101f7)
#define PHY_OM_CT_F_PD_AUTO_CAL_IND             (0X101f8)

#define OM_PHY_CT_F_PD_CAL_REQ                 (0X101f9)
#define PHY_OM_CT_F_PD_CAL_CNF                 (0X101f9)
#define PHY_OM_CT_F_PD_CAL_IND                 (0X101fA)
//^FCALIIP2S IDs
#define OM_PHY_CT_F_CALIIP2_SET_REQ (0x10220)
#define PHY_OM_CT_F_CALIIP2_SET_CNF (0x10220)
#define PHY_OM_CT_F_CALIIP2_IND     (0x10221)

//^FCALIDCOCS IDs
#define OM_PHY_CT_F_CALIDCOCS_SET_REQ (0x10230)
#define PHY_OM_CT_F_CALIDCOCS_SET_CNF (0x10230)
#define PHY_OM_CT_F_CALIDCOCS_IND (0x10231)

//^FCALITXIQ IDs
#define OM_PHY_CT_F_CALITXIQ_SET_REQ (0x10240)
#define PHY_OM_CT_F_CALITXIQ_SET_CNF (0x10240)
#define PHY_OM_CT_F_CALITXIQ_IND (0x10241)

//^FGAINSTATES IDs
#define OM_PHY_CT_F_GAINSTATE_SET_REQ (0x10250)
#define PHY_OM_CT_F_GAINSTATE_SET_CNF (0x10250)

//^FDBBATTS IDs
#define OM_PHY_CT_F_DBBATT_SET_REQ (0x10260)
#define PHY_OM_CT_F_DBBATT_SET_CNF (0x10260)

//^FBBATTS IDs
#define OM_PHY_CT_F_BBATT_SET_REQ  (0x10270)
#define PHY_OM_CT_F_BBATT_SET_CNF  (0x10270)

//^FCALIIP2SMRF IDS
#define OM_PHY_CT_F_CALIIP2_SET_MUTIRF_REQ     (0X10280)
#define PHY_OM_CT_F_CALIIP2_SET_MUTIRF_CNF     (0X10280)
#define PHY_OM_CT_F_CALIIP2_MUTIRF_IND         (0X10281)
#define OM_PHY_CT_F_CALIDCOCS_SET_MUTIRF_REQ (0x10290)
#define PHY_OM_CT_F_CALIDCOCS_SET_MUTIRF_CNF (0x10290)
#define PHY_OM_CT_F_CALIDCOCS_MUTIRF_IND     (0x10291)

/**********************以下为非信令综测的消息定义******************************/
#define OM_PHY_SYN_SSYNC_SET_REQ             (0x10200)
#define PHY_OM_SYN_SSYNC_SET_CNF             (0x10200)

/* ^SSYNC 非信令综测查询单板同步状态*/
#define OM_PHY_SYN_SSYNC_RD_REQ              (0x10201)
#define PHY_OM_SYN_SSYNC_IND                 (0x10201)

/* ^STXBW 非信令综测设置发射带宽*/
#define OM_PHY_SYN_STXBW_SET_REQ             (0x10202)
#define PHY_OM_SYN_STXBW_SET_CNF             (0x10202)

/* ^SSUBFRAME 非信令综测设置子帧配比*/
#define OM_PHY_SYN_SSUBFRAME_SET_REQ           (0x10204)
#define PHY_OM_SYN_SSUBFRAME_SET_CNF           (0x10204)

/* ^STXCHAN 非信令综测设置上行发射信道*/
#define OM_PHY_SYN_STXCHAN_SET_REQ           (0x10205)
#define PHY_OM_SYN_STXCHAN_SET_CNF           (0x10205)

/*^SPARA*/
/*非信令综测设置信道参数*/
#define OM_PHY_SYN_SPARA_SET_REQ           (0x1020F)
#define PHY_OM_SYN_SPARA_SET_CNF           (0x1020F)

#define OM_PHY_SYN_SPARA_RD_REQ             (0x10210)
#define PHY_OM_SYN_SPARA_RD_CNF             (0x10210)

/*^SSEGNUM非信令综测设置segment数量*/
#define OM_PHY_SYN_SSEGNUM_SET_REQ           (0x10211)
#define PHY_OM_SYN_SSEGNUM_SET_CNF           (0x10211)

#define OM_PHY_SYN_SSEGNUM_RD_REQ            (0x10212)
#define PHY_OM_SYN_SSEGNUM_RD_CNF            (0x10212)

/* ^STXMODUS 非信令综测设置调制方式*/
#define OM_PHY_SYN_STXMODUS_SET_REQ          (0x10206)
#define PHY_OM_SYN_STXMODUS_SET_CNF          (0x10206)

/* ^STXRBNUMS 非信令综测设置RB数量*/
#define OM_PHY_SYN_STXRBNUMS_SET_REQ         (0x10207)
#define PHY_OM_SYN_STXRBNUMS_SET_CNF         (0x10207)

/* ^STXRBPOSS 非信令综测设置RB位置*/
#define OM_PHY_SYN_STXRBPOSS_SET_REQ         (0x10208)
#define PHY_OM_SYN_STXRBPOSS_SET_CNF         (0x10208)

/* ^STXPOWS 非信令综测设置发射功率*/
#define OM_PHY_SYN_STXPOWS_SET_REQ           (0x10209)
#define PHY_OM_SYN_STXPOWS_SET_CNF           (0x10209)

/* ^STXCHANTYPES 非信令综测设置信道类型*/
#define OM_PHY_SYN_STXCHANTYPES_SET_REQ      (0x1020A)
#define PHY_OM_SYN_STXCHANTYPES_SET_CNF      (0x1020A)

/* ^SSEGLEN 非信令综测设置SEGMENT长度*/
#define OM_PHY_SYN_SSEGLEN_SET_REQ          (0x1020B)
#define PHY_OM_SYN_SSEGLEN_SET_CNF          (0x1020B)

/*^SRXPOW非信令综测接收测试的功率设置*/
#define OM_PHY_SYN_SRXPOW_SET_REQ          (0x10213)
#define PHY_OM_SYN_SRXPOW_SET_CNF          (0x10213)
#define OM_PHY_SYN_SRXPOW_RD_REQ           (0x10214)
#define PHY_OM_SYN_SRXPOW_RD_CNF           (0x10214)

/*^SRXSUBFRA非信令综测接收测试的子帧数量*/
#define OM_PHY_SYN_SRXSUBFRA_SET_REQ          (0x10215)
#define PHY_OM_SYN_SRXSUBFRA_SET_CNF          (0x10215)
#define OM_PHY_SYN_SRXSUBFRA_RD_REQ           (0x10216)
#define PHY_OM_SYN_SRXSUBFRA_RD_CNF           (0x10216)

/*^SRXBLER非信令综测接收测试查询误码率*/
#define OM_PHY_SYN_SRXBLER_RD_REQ           (0x10217)
#define PHY_OM_SYN_SRXBLER_RD_CNF           (0x10217)

/* ^SSTART 非信令综测启动发射并状态查询*/
#define OM_PHY_SYN_SSTART_SET_REQ            (0x1020C)
#define PHY_OM_SYN_SSTART_SET_CNF            (0x1020C)

/* ^SSTART 非信令综测状态查询*/
#define OM_PHY_SYN_SSTART_RD_REQ             (0x1020D)
#define PHY_OM_SYN_SSTART_RD_CNF             (0x1020D)

/* ^SSTOP 非信令综测停止上行发射*/
#define OM_PHY_SYN_SSTOP_SET_REQ             (0x1020E)
#define PHY_OM_SYN_SSTOP_SET_CNF             (0x1020E)

#define OM_PHY_SYN_SRXSET_SET_REQ            (0x10213)
#define PHY_OM_SYN_SRXSET_SET_CNF            (0x10213)

#define OM_PHY_BT_FPOW_SET_REQ                (0x10214)
#define PHY_OM_BT_FPOW_SET_CNF                (0x10214)

/*查询 TDS 下行 BER 结果*/
#define OM_PHY_SYN_SRXBER_RD_REQ           (0x10218)
#define PHY_OM_SYN_SRXBER_RD_CNF           (0x10218)

#define OM_PHY_COMM_CMD_SET_REQ            (0x102A0)
#define PHY_OM_COMM_CMD_SET_CNF            (0x102A0)
#define PHY_OM_COMM_CMD_IND                (0x102A1)

#define OM_PHY_FPLLSTATUS_RD_REQ           (0x102A2)
#define PHY_OM_FPLLSTATUS_RD_CNF           (0x102A2)

#define OM_PHY_NOISE_CFG_REQ                  (0x102A3)
#define PHY_OM_NOISE_RSSI_IND                  (0x102A4)

//IP2校准支持最大频点数
#define CT_IP2_CAL_FREQ_NUM 4

//DCOC校准，AGC档位个数
#define CT_F_CALIDCOCS_AGC_NUM 16

//GainState参数最大个数
#define CT_F_GAINSTATE_MAX_NUM  60

//DBB衰减参数最大个数
#define CT_F_DBBATT_MAX_NUM CT_F_GAINSTATE_MAX_NUM

//BB衰减参数最大个数
#define CT_F_BBATT_MAX_NUM_CT CT_F_GAINSTATE_MAX_NUM

/* Modify channel number from 16 to 32 by daizhicheng for V7R2/V9R1*/
#define CT_F_FREQ_UL_LIST_MAX_NUM 32
#define CT_F_FREQ_DL_LIST_MAX_NUM 32

#define POW_MAX_NUM             (30)
#define TX_POW_MAX_NUM          (20*2*3 + 32)
/* Modify channel number from 16 to 32 by daizhicheng for V7R2/V9R1*/
#define FREQ_MAX_NUM            (32)

#define NOISETOOL_MAX_PWR_NUM       (1)
#define NOISETOOL_SEGMENT_LEN         (5)
#define NOISETOOL_MEAS_OFFSET    (3)

#define CT_MAX_RFIC_PATH_NUM          2
#define CT_MAX_RX_ANT_NUM             4

#define CT_TDS_MODE             2

/* LTE与WIFI共存特性MSP下发给物理层最大的参数组数目 */
#define    LMSP_LPHY_MAX_COEX_PARA_NUM                        6

#define LMSP_LPHY_MSG_HDR                (0x2000)
#define LPHY_LMSP_MSG_HDR                (0x2100)

#define LWCOEX_MSG_TYPE                (0x1)

#define LMSP_TDS_BAND39_INDEX            5         /*TDS_BANDF*/
#define LMSP_TDS_BAND34_INDEX            0         /*TDS_BANDA*/

#define LMSP_TDS_MAX_BAND_NUM            6

/*****************************************************************************
 枚举名    : LMSP_LPHY_MSG_ID_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LMSP -> LPHY 接口消息ID
*****************************************************************************/
enum LMSP_LPHY_MSG_ID_ENUM
{
    /* MSP发给物理层的原语 */
    ID_LMSP_LPHY_LTE_WIFI_COEX_SET_REQ       = LMSP_LPHY_MSG_HDR + LWCOEX_MSG_TYPE,
    ID_LMSP_LPHY_LTE_WIFI_COEX_SET_CNF       = LPHY_LMSP_MSG_HDR + LWCOEX_MSG_TYPE,
    ID_LMSP_LPHY_BUTT
};
typedef VOS_UINT32    LMSP_LPHY_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LMSP_LPHY_COEX_BW_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum LMSP_LPHY_COEX_BW_TYPE_ENUM
{
    LMSP_LPHY_COEX_BAND_WIDTH_6RB              = 0,       /* 带宽为1.4M */
    LMSP_LPHY_COEX_BAND_WIDTH_15RB,                       /* 带宽为3M */
    LMSP_LPHY_COEX_BAND_WIDTH_25RB,                       /* 带宽为5M */
    LMSP_LPHY_COEX_BAND_WIDTH_50RB,                       /* 带宽为10M */
    LMSP_LPHY_COEX_BAND_WIDTH_75RB,                       /* 带宽为15M */
    LMSP_LPHY_COEX_BAND_WIDTH_100RB,                      /* 带宽为20M */
    LMSP_LPHY_COEX_BAND_WIDTH_BUTT
};
typedef UINT16    LMSP_LPHY_COEX_BW_TYPE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : LMSP_LPHY_COEX_ENABLE_IND_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum LMSP_LPHY_COEX_ENABLE_IND_ENUM
{
    LMSP_LPHY_COEX_DISABLE     = 0, /*在指定的带宽上关闭共存方案*/
    LMSP_LPHY_COEX_ENABLE ,         /*在指定的带宽上打开共存方案*/
    LMSP_LPHY_COEX_BUTT
};
typedef UINT16    LMSP_LPHY_COEX_ENABLE_IND_ENUM_UINT16;


/*****************************************************************************
 枚举名    : LMSP_LPHY_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum LMSP_LPHY_RESULT_ENUM
{
    LMSP_LPHY_RESULT_SUCC                 = 0,
    LMSP_LPHY_RESULT_FAIL ,
    LMSP_LPHY_RESULT_BUTT
};
typedef UINT16    LMSP_LPHY_RESULT_ENUM_UINT16;





typedef struct
{
    UINT32 ulMsgId;
}PHY_MSP_CT_SINGLE_CNF_STRU;

#ifdef MBX_RTT_CBT
typedef struct
{
    UINT32 ulMsgId;
    UINT16 usStatus;
    UINT16 usRsv;
} OM_MSG_CNF_STRU;
#endif
/*****************************************************************************
 描述 : MSP收到AT^TMODE命令后判断为非信令模式时下发该原语告知RTT，
        AT命令里其它模式不下发本原语
 ID   : OM_PHY_CT_TEST_MODE_REQ,PHY_OM_CT_TEST_MODE_CNF
 REQ  : OM_PHY_CT_TEST_MODE_REQ_STRU
 CNF  : PHY_OM_CT_TEST_MODE_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;

    /*1: 非信令普通校准模式*/
    /*6：非信令快速校准模式*/
    UINT16 usTMode;     /* 模式配置*/
    UINT16 usRsv;
} OM_PHY_CT_TEST_MODE_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_TEST_MODE_CNF_STRU;


/*****************************************************************************
 描述 : 指示物理层打开上行通道。RTT收到该原语上行通道必须一直打开，直至MSP通过本原语关闭上行。
 ID   : OM_PHY_CT_TXON_REQ,PHY_OM_CT_TXON_CNF
 REQ  : OM_PHY_CT_TXON_REQ_STRU
 CNF  : PHY_OM_CT_TXON_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */

    /* 0:表示关闭发射机*/
	  /* 1:表示打开发射机，包括基带调制和RF发射通道*/
    /* 2:表示只打开RFIC Transmitter和PA ，BB调制通道不打开，用于VCTCXO校准*/
    UINT16 usTxType;                     /*Tx打开类型*/
    UINT16 usRsv;
} OM_PHY_CT_TXON_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_TXON_CNF_STRU;

typedef struct
{
    UINT32 ulMsgId;
}OM_PHY_FPLLSTATUS_RD_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
    UINT16 tx_status;
    UINT16 rx_status;
}PHY_OM_FPLLSTATUS_RD_CNF_STRU;


/*****************************************************************************
 描述 : 若当前发射通道打开（Tx类型为1或2），则RTT认为本原语配置上行频点，若发射通道关闭，
        则认为是下行频点。MSP须将AT^FCHAN命令中的信道号根据36.101协议规定查表转为实际频点值，
        转换过程参考附录4。
 ID   : OM_PHY_CT_FREQ_SET_REQ,PHY_OM_CT_FREQ_SET_CNF
 REQ  : OM_PHY_CT_FREQ_SET_REQ_STRU
 CNF  : PHY_OM_CT_FREQ_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */

    /* 频点信息，*/
    /* 频栅间隔100Khz，如配置值26200对应频点2.62GHz*/
    UINT16 usUlFreq;                   /*频点信息*/
    UINT16 usDlFreq;                   /*频点信息*/
    UINT16 usMode;    /*6,FDD;7,TDD */
    UINT16 usBandNum;
} OM_PHY_CT_FREQ_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_FREQ_SET_CNF_STRU;


/*****************************************************************************
 描述 : 配置上行发射功率。RTT收到该原语后应立即改变上行发射功率
 ID   : OM_PHY_CT_TXPOW_SET_REQ,PHY_OM_CT_TXPOW_SET_CNF
 REQ  : OM_PHY_CT_FREQ_SET_REQ_STRU
 CNF  : PHY_OM_CT_FREQ_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */

    /* 单位：dBm*/
    INT16  sTxPower;                     /*上行发射功率*/
    UINT16 usRsv;
} OM_PHY_CT_TXPOW_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_TXPOW_SET_CNF_STRU;

/*****************************************************************************
 描述 : 配置上行发射功率。RTT收到该原语后应立即改变上行发射功率
 ID   : OM_PHY_CT_VCTCXO_SET_REQ,PHY_OM_CT_VCTCXO_SET_CNF
 REQ  : OM_PHY_CT_FREQ_SET_REQ_STRU
 CNF  : PHY_OM_CT_FREQ_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/

typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */

    /* VCTCXO控制电压		[0,65535]*/
    UINT16 usVctcxoCtrl;                 /*Vctcxo控制字*/
    UINT16 usRsv;
} OM_PHY_CT_VCTCXO_SET_REQ_STRU;


typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_VCTCXO_SET_CNF_STRU;

/*****************************************************************************/

/*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */
    UINT8  ucLevel;
    UINT8  ucPading[3];

} OM_PHY_CT_FPA_SET_REQ_STRU;


typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_FPA_SET_CNF_STRU;


/*****************************************************************************

*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */
    UINT16  usApc;
    UINT16  usRsv;

} OM_PHY_CT_FDAC_SET_REQ_STRU;


typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_FDAC_SET_CNF_STRU;


/*****************************************************************************
 描述 : 指示打开物理层接收机。由于物理层在进入非信令模式已打开接收双通道，
        此处收到原语后不做接收处理，直接返回CNF原语
 ID   : OM_PHY_CT_RXON_REQ,PHY_OM_CT_RXON_CNF
 REQ  : OM_PHY_CT_RXON_REQ_STRU
 CNF  : PHY_OM_CT_RXON_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/

typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */

    UINT16 usRxType;                     /*Rx打开类型*/
    UINT16 usRsv;
} OM_PHY_CT_RXON_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_RXON_CNF_STRU;

/*****************************************************************************
 描述 : 配置RX通道。RTT收到该原语后选定需要进行RSSI折算和上报的接收通道。
      注意RTT在非信令模式下Rx双通道都一直打开。若本原语指示关闭双通道，
      RTT不做任何处理。
 ID   : OM_PHY_CT_RXANT_SET_REQ,PHY_OM_CT_RXANT_SET_CNF
 REQ  : OM_PHY_CT_RXANT_SET_REQ_STRU
 CNF  : PHY_OM_CT_RXANT_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/

typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */

    /* 0:关闭双通道*/
    /* 1:只打开通道1*/
    /* 2:只打开通道2*/
    /* 3:打开双通道*/
    UINT16 usRxAntType;                  /* RX通道选择 */
    UINT16 usRsv;
} OM_PHY_CT_RXANT_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_RXANT_SET_CNF_STRU;

/*****************************************************************************
AT^TSELRF
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */
    UINT8  ucPath;
    UINT8  ucGroup;
    UINT16 usRsv;
} OM_PHY_CT_TSELRF_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_TSELRF_SET_CNF_STRU;


/*****************************************************************************
 描述 : 配置RFIC的AAGC总增益，用于下行AGC表的校准，单位为dB。
      RTT收到该原语后将RFIC的总增益立即改为原语指示的增益值。
 ID   : OM_PHY_CT_AAGC_SET_REQ,PHY_OM_CT_AAGC_SET_CNF
 REQ  : OM_PHY_CT_AAGC_SET_REQ_STRU
 CNF  : PHY_OM_CT_AAGC_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */

    /* [0,127]	单位:dB。*/
    UINT16 usAAGCValue;                  /* AAGC增益值 */
    UINT16 usRsv;
} OM_PHY_CT_AAGC_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_AAGC_SET_CNF_STRU;

/*****************************************************************************
 描述 :指示RTT启动物理层RSSI测量，用于下行AGC表的校准。RTT收到该原语后启动RSSI
       测量，完成后通过PHY_OM_CT_RSSI_IND原语上报对应RX通道的RSSI测量结果
 ID   : OM_PHY_CT_MEAS_RSSI_REQ,PHY_OM_CT_MEAS_RSSI_CNF
 REQ  : OM_PHY_CT_MEAS_RSSI_REQ_STRU
 CNF  : PHY_OM_CT_MEAS_RSSI_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */
} OM_PHY_CT_MEAS_RSSI_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_MEAS_RSSI_CNF_STRU;
/*****************************************************************************
 描述 :指示启动物理层热敏电阻电压测量，
 ID   :
 REQ  : OM_PHY_CT_VOLTAGE_REQ_STRU
 CNF  : PHY_OM_CT_VOLTAGE_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */
} OM_PHY_CT_VOLTAGE_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
    UINT32 ulVoltage;
} PHY_OM_CT_VOLTAGE_CNF_STRU;

/*****************************************************************************
 描述 :指示RTT启动物理层RSSI测量，用于下行AGC表的校准。RTT收到该原语后启动RSSI
       测量，完成后通过PHY_OM_CT_RSSI_IND原语上报对应RX通道的RSSI测量结果
 ID   : PHY_OM_CT_RSSI_IND
 REQ  : NA
 CNF  : NA
 IND  : PHY_OM_CT_RSSI_IND_STRU
 说明 :
*****************************************************************************/

/* usRxANT1ValidFlag	Rx通道1有效标志		[0,1]	0:Rx通道1无效，sRxANT1RSSI值无效*/
/* 1:Rx通道1有效，sRxANT1RSSI值有效*/
/* sRxANT1RSSI	Rx通道1的RSSI		[-110*8,-20*8]	单位:1/8dBm，只在usRxANT1ValidFlag=1有效*/
/* usRxANT2ValidFlag	Rx通道2有效标志		[0,1]	0:Rx通道2无效，sRxANT2RSSI值无效*/
/* 1:Rx通道2有效，sRxANT2RSSI值有效*/
/* sRxANT2RSSI	Rx通道2的RSSI		[-110*8,-20*8]	单位:1/8dBm，只在usRxANT2ValidFlag=1有效*/
typedef struct
{
    UINT32 ulMsgId;
    UINT16 usRxANT1ValidFlag;
    INT16  sRxANT1RSSI;
    UINT16 usRxANT2ValidFlag;
    INT16  sRxANT2RSSI;
    UINT16 usRxANT3ValidFlag;
    INT16  sRxANT3RSSI;
    UINT16 usRxANT4ValidFlag;
    INT16  sRxANT4RSSI;
} PHY_OM_CT_RSSI_IND_STRU;

/* OM_PHY_POWER_CONFIG_REQ*/
#if 0
typedef struct
{
    UINT32 ulMsgId;
    PHY_OM_UPLINK_PWR_CTRL_STRU stulPwrCtrlFlag;
    INT16  sPucchTxPower;
    INT16  sPuschTxPower;
    INT16  sSrsTxPower;
    INT16  sPrachTxPower;
}OM_PHY_POWER_CONFIG_REQ_STRU;
#endif
/*****************************************************************************
 描述 : AGC查询
 ID   : OM_PHY_FAGC_REQ,PHY_OM_FAGC_CNF
 REQ  : OM_PHY_FAGC_REQ_STRU
 CNF  : PHY_OM_FAGC_CNF_STRU
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */
} OM_PHY_FAGC_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
    INT16 sRsrp;
    INT16 sRsv;
} PHY_OM_FAGC_CNF_STRU;

/****************************************************************************************************
描述:   IP2校准，用于^FCALIIP2S
ID:     OM_PHY_CT_F_CALIIP2_SET_REQ,      PHY_OM_CT_F_CALIIP2_SET_CNF,      PHY_OM_CT_F_CALIIP2_IND
结构:   OM_PHY_CT_F_CALIIP2_SET_REQ_STRU, PHY_OM_CT_F_CALIIP2_SET_CNF_STRU, PHY_OM_CT_F_CALIIP2_IND_STU
******************************************************************************************************/
typedef struct
{
	UINT32 ulMsgId;
	UINT16 usChanNum;
	UINT16 usRsv;
	UINT16 usChan[CT_IP2_CAL_FREQ_NUM];
}OM_PHY_CT_F_CALIIP2_SET_REQ_STRU;

typedef struct
{
	UINT32 ulMsgId;
}PHY_OM_CT_F_CALIIP2_SET_CNF_STRU;

typedef struct
{
	UINT32 ulMsgId;
	UINT16 usChanNum;
	UINT16 usRsv;
	UINT16 usMain_I_DivOff[CT_IP2_CAL_FREQ_NUM];
	UINT16 usMain_Q_DivOff[CT_IP2_CAL_FREQ_NUM];
	UINT16 usMain_I_DivOn[CT_IP2_CAL_FREQ_NUM];
	UINT16 usMain_Q_DivOn[CT_IP2_CAL_FREQ_NUM];
	UINT16 usDiv_I[CT_IP2_CAL_FREQ_NUM];
	UINT16 usDiv_Q[CT_IP2_CAL_FREQ_NUM];
}PHY_OM_CT_F_CALIIP2_IND_STRU;


/****************************************************************************************************
描述:   IP2校准，用于^FCALIIP2S
ID:     OM_PHY_CT_F_CALIIP2_SET_REQ,      PHY_OM_CT_F_CALIIP2_SET_CNF,      PHY_OM_CT_F_CALIIP2_IND
结构:   OM_PHY_CT_F_CALIIP2_SET_REQ_STRU, PHY_OM_CT_F_CALIIP2_SET_CNF_STRU, PHY_OM_CT_F_CALIIP2_IND_STU
******************************************************************************************************/
typedef struct
{
	UINT32 ulMsgId;
    UINT16 usBand;                            /*band 号  */
    UINT16 usFreqNum;                         /*频点数目 */
    UINT16 usRfid;                            /*RF通道   */
	UINT16 usRsv;
    UINT16 usFreq[CT_IP2_CAL_FREQ_NUM]; /*频点列表 */
}OM_PHY_CT_F_CALIIP2_SET_MUTIRF_REQ_STRU;

typedef struct
{
	UINT32 ulMsgId;
}PHY_OM_CT_F_CALIIP2_SET_MUTIRF_CNF_STRU;

typedef struct
{
    UINT16 usValidFlg;
    UINT16 usRsv;
	UINT16 usMain_I_DivOff[CT_IP2_CAL_FREQ_NUM];
	UINT16 usMain_Q_DivOff[CT_IP2_CAL_FREQ_NUM];
	UINT16 usMain_I_DivOn[CT_IP2_CAL_FREQ_NUM];
	UINT16 usMain_Q_DivOn[CT_IP2_CAL_FREQ_NUM];
	UINT16 usDiv_I[CT_IP2_CAL_FREQ_NUM];
	UINT16 usDiv_Q[CT_IP2_CAL_FREQ_NUM];
}CT_RF_IIP2_CAL_ITEM;

typedef struct
{
	UINT32    ulMsgId;
#ifdef MBX_RTT_CBT
    UINT16 usMsgStatus;
    UINT16 usCalStatus;
#endif
	UINT16    usChanNum;
	UINT16    usRsv;
	CT_RF_IIP2_CAL_ITEM  astIp2CalRst[CT_MAX_RFIC_PATH_NUM];
}PHY_OM_CT_F_CALIIP2_MUTIRF_IND_STRU;


/****************************************************************************************************
描述:   DCOC校准，用于^FCALIDCOCS
ID:     OM_PHY_CT_F_CALIDCOCS_SET_REQ,      PHY_OM_CT_F_CALIDCOCS_SET_CNF,      PHY_OM_CT_F_CALIDCOCS_IND
结构:   OM_PHY_CT_F_CALIDCOCS_SET_REQ_STRU, PHY_OM_CT_F_CALIDCOCS_SET_CNF_STRU, PHY_OM_CT_F_CALIDCOCS_IND_STRU
******************************************************************************************************/
typedef struct
{
	UINT32 ulMsgId;
	UINT16 usChannel;
	UINT16 usRsv;
}OM_PHY_CT_F_CALIDCOCS_SET_REQ_STRU;

typedef struct
{
	UINT32 ulMsgId;
}PHY_OM_CT_F_CALIDCOCS_SET_CNF_STRU;

typedef struct
{
	UINT32 ulMsgId;
#ifdef MBX_RTT_CBT
    UINT16 usMsgStatus;
    UINT16 usCalStatus;
#endif
	UINT16 usNOBLK_ANT1_I[CT_F_CALIDCOCS_AGC_NUM];
    UINT16 usNOBLK_ANT1_Q[CT_F_CALIDCOCS_AGC_NUM];
	UINT16 usBLK_ANT1_I[CT_F_CALIDCOCS_AGC_NUM];
    UINT16 usBLK_ANT1_Q[CT_F_CALIDCOCS_AGC_NUM];
	UINT16 usNOBLK_ANT2_I[CT_F_CALIDCOCS_AGC_NUM];
    UINT16 usNOBLK_ANT2_Q[CT_F_CALIDCOCS_AGC_NUM];
	UINT16 usBLK_ANT2_I[CT_F_CALIDCOCS_AGC_NUM];
    UINT16 usBLK_ANT2_Q[CT_F_CALIDCOCS_AGC_NUM];
}PHY_OM_CT_F_CALIDCOCS_IND_STRU;

/****************************************************************************************************
描述:   DCOC校准，用于^FCALIDCOCSMRF
ID:     OM_PHY_CT_F_CALIDCOCS_MULTIRF_SET_REQ,      PHY_OM_CT_F_CALIDCOCS_MULTIRF_SET_CNF,      PHY_OM_CT_F_CALIDCOCS_MULTIRF_IND
结构:   OM_PHY_CT_F_CALIDCOCS_MULTIRF_SET_REQ_STRU, PHY_OM_CT_F_CALIDCOCS_MULTIRF_SET_CNF_STRU, PHY_OM_CT_F_CALIDCOCS_MULTIRF_IND_STRU
******************************************************************************************************/
typedef struct
{
	UINT32 ulMsgId;
    UINT16 usFreq;  /*频点  */
    UINT16 usBand;  /*BAND号*/
    UINT16 usRfid;  /*RF通道*/
	UINT16 usRsv;
}OM_PHY_CT_F_CALIDCOCS_SET_MUTIRF_REQ_STRU;

typedef struct
{
	UINT32 ulMsgId;
}PHY_OM_CT_F_CALIDCOCS_SET_MUTIRF_CNF_STRU;

typedef struct
{
     UINT16 usAntCompDCI[CT_F_CALIDCOCS_AGC_NUM];
     UINT16 usAntCompDCQ[CT_F_CALIDCOCS_AGC_NUM];
}CT_RF_DOCOC_ANT_ITEM_STRU;

typedef struct
{
    UINT16 usValidFlg;
    UINT16 usValidAntNum;
    CT_RF_DOCOC_ANT_ITEM_STRU   astAntCal[CT_MAX_RX_ANT_NUM];
}CT_RF_DCOCS_DCCOMP_ITEM_STRU;

typedef struct
{
	UINT32 ulMsgId;
#ifdef MBX_RTT_CBT
    UINT16 usMsgStatus;
	UINT16 usCalStatus;
#endif
    UINT16 usChanNum;
    UINT16 usRsv;
    CT_RF_DCOCS_DCCOMP_ITEM_STRU  astDcocCalRst[CT_MAX_RFIC_PATH_NUM];
}PHY_OM_CT_F_CALIDCOCS_MUTIRF_IND_STRU;


/****************************************************************************************************
描述:   TXIQ校准，用于^FTXIQ
ID:     OM_PHY_CT_F_CALITXIQ_SET_REQ,       PHY_OM_CT_F_CALITXIQ_SET_CNF,       PHY_OM_CT_F_CALITXIQ_IND
结构:   OM_PHY_CT_F_CALIDCOCS_SET_REQ_STRU, PHY_OM_CT_F_CALIDCOCS_SET_CNF_STRU, PHY_OM_CT_F_CALIDCOCS_IND_STRU
******************************************************************************************************/
typedef struct
{
	UINT32 ulMsgId;
    UINT16 usFreq;      /*频点*/
    UINT16 usBand;      /*BAND号*/
    UINT16 usRfid;      /*RF通道*/
	UINT16 usRsv;
}OM_PHY_CT_F_TXIQ_SET_REQ_STRU;

typedef struct
{
	UINT32 ulMsgId;
}PHY_OM_CT_F_TXIQ_SET_CNF_STRU;

typedef struct
{
	UINT32 ulMsgId;
#ifdef MBX_RTT_CBT
    UINT16 usMsgStatus;/*0表示OK*/
    UINT16 usCalStatus;
#endif
	UINT16 usAmplitude;
	UINT16 usPhase;
	UINT16 usDCI;
	UINT16 usDCQ;
}PHY_OM_CT_F_TXIQ_IND_STRU;

/****************************************************************************************************
描述:   设置GainState参数，用于^FGAINSTATES
ID:     OM_PHY_CT_F_GAINSTATE_SET_REQ,       PHY_OM_CT_F_GAINSTATE_SET_CNF
结构:   OM_PHY_CT_F_CALIDCOCS_SET_REQ_STRU, PHY_OM_CT_F_CALIDCOCS_SET_CNF_STRU
******************************************************************************************************/
typedef struct
{
	UINT32 ulMsgId;
	UINT16 usGainStateNum;
	UINT16 usRsv;
	UINT16 ausGainState[TX_POW_MAX_NUM];
}OM_PHY_CT_F_GAINSTATE_SET_REQ_STRU;

typedef struct
{
	UINT32 ulMsgId;
}PHY_OM_CT_F_GAINSTATE_SET_CNF_STRU;

/****************************************************************************************************
描述:   设置DBB衰减参数，用于^FDBBATTS
ID:     OM_PHY_CT_F_DBBATT_SET_REQ,         PHY_OM_CT_F_DBBATT_SET_CNF
结构:   OM_PHY_CT_F_CALIDCOCS_SET_REQ_STRU, PHY_OM_CT_F_CALIDCOCS_SET_CNF_STRU
******************************************************************************************************/
typedef struct
{
	UINT32 ulMsgId;
	UINT16 usDbbCodeNum;
	UINT16 usDbbCode;
}OM_PHY_CT_F_DBBATT_SET_REQ_STRU;

typedef struct
{
	UINT32 ulMsgId;
}PHY_OM_CT_F_DBBATT_SET_CNF_STRU;

/****************************************************************************************************
描述:   设置BB衰减参数，用于^FBBATTS
ID:     OM_PHY_CT_F_BBATT_SET_REQ,      PHY_OM_CT_F_BBATT_SET_CNF
结构:   OM_PHY_CT_F_BBATT_SET_REQ_STRU, PHY_OM_CT_F_BBATT_SET_CNF_STRU
******************************************************************************************************/
typedef struct
{
	UINT32 ulMsgId;
	UINT16 usBbAttNum;
	UINT16 usRsv;
	UINT16 usBbAtt[CT_F_BBATT_MAX_NUM_CT];
}OM_PHY_CT_F_BBATT_SET_REQ_STRU;

typedef struct
{
	UINT32 ulMsgId;
}PHY_OM_CT_F_BBATT_SET_CNF_STRU;

/*AT^FPDMS*/
typedef struct
{
   UINT32 ulMsgId;
   UINT32 ulIsEnable;
}OM_PHY_CT_F_FPDMS_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
}PHY_OM_CT_F_FPDMS_SET_CNF_STRU;

/*TEMP*/
typedef struct
{
   UINT32 ulMsgId;
   UINT16 usTempVal;
   UINT16 usRsv;
}OM_PHY_BT_TEMP_DISPATCH_REQ_STRU;
/*****************************************************************************
AT^BANDSW
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;
	UINT16 usMode;
	UINT16 usBand;
	UINT16 usUlFreq;
	UINT16 usDLFreq;
	UINT16 usDlAbbChanIndex;
    UINT16 usUlAbbChanIndex;
	UINT16 usRsv;
}OM_PHY_CT_F_BANDSW_SET_REQ_STRU;
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_BANDSW_SET_CNF_STRU;



/*****************************************************************************
 描述 : 当前发射通道打开。
        则认为是下行频点。MSP须将AT^FCHANS命令中的信道号根据36.101协议规定查表转为实际频点值，
        转换过程参考附录4。
 ID   : OM_PHY_CT_F_FREQ_SET_REQ,PHY_OM_CT_F_FREQ_SET_CNF
 REQ  : OM_PHY_CT_F_FREQ_SET_REQ_STRU
 CNF  : PHY_OM_CT_F_FREQ_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识*/
    UINT32 ulMode;                       /* MODE TDD：7；FDD：6*/
    UINT16 usUlListNum; /* 上行设置的个数，对应ausUlFreqInfo，最多16个*/
    UINT16 usDlListNum; /* 下行设置的个数，对应ausDlFreqInfo，最多16个*/

    /* 频点信息，*/
    /* 频栅间隔100Khz，如配置值26200对应频点2.62GHz*/
    UINT16 ausUlFreqInfo[CT_F_FREQ_UL_LIST_MAX_NUM];       /* 上行频点信息*/
    UINT16 ausDlFreqInfo[CT_F_FREQ_DL_LIST_MAX_NUM];       /* 下行频点信息*/
} OM_PHY_CT_F_FREQ_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_FREQ_SET_CNF_STRU;


/*****************************************************************************
 描述 : 配置上行发射功率。RTT收到该原语后应立即改变上行发射功率
 ID   : OM_PHY_CT_F_TXPOW_SET_REQ,PHY_OM_CT_F_TXPOW_SET_CNF
 REQ  : OM_PHY_CT_F_TXPOW_SET_REQ_STRU
 CNF  : PHY_OM_CT_F_TXPOW_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
#define CT_POWER_SET_MAX_NUM             (30)
typedef struct
{
    UINT32 ulMsgId;                          /* 消息标识 */

    /* 单位：dBm*/
    UINT16 usTxPowerNum;                     /* 指定在asTxPower的个数*/
    UINT16 usRsv;
    /* 发射功率列表，以空格分割，每个值的长度为一个字 ，单位为dBm*/
    INT16  ausTxPower[CT_POWER_SET_MAX_NUM];  /*上行发射功率*/
} OM_PHY_CT_F_TXPOW_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_TXPOW_SET_CNF_STRU;


/*****************************************************************************
 描述 : 配置RFIC的AAGC总增益，用于下行AGC表的校准，单位为dB。
      RTT收到该原语后将RFIC的总增益立即改为原语指示的增益值。
 ID   : OM_PHY_CT_F_AAGC_SET_REQ,PHY_OM_F_CT_AAGC_SET_CNF
 REQ  : OM_PHY_CT_F_AAGC_SET_REQ_STRU
 CNF  : PHY_OM_CT_F_AAGC_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/

#define CT_F_AAGC_SET_MAX_NUM    (30)
typedef struct
{
    UINT32 ulMsgId;                               /* 消息标识*/
    UINT16 usAagcNum;
    UINT16 usRsv;

    /*取值范围0～255，其中Hi6910的范围为151-234。*/
    UINT8 aucAAGCValue[CT_F_AAGC_SET_MAX_NUM];    /* AAGC增益值*/
} OM_PHY_CT_F_AAGC_SET_REQ_STRU;

#define CT_MAX_RX_CAL_NUM (50)

typedef struct
{
    UINT16 usFreq;
	UINT16 usGainIdx;
}CT_RX_OPT_PARA_STRU;

typedef struct
{
    UINT32 ulMsgId;         /* 消息标识*/
    UINT16 usTrigerFreq;
    UINT16 usRxCalNum;;
    UINT16 usSegmentLen;       /*segment长度*/
    UINT16 usMeasOffset;    /* 表示测量起始位置偏移，单位ms，取值范围0~20，无默认值*/

    CT_RX_OPT_PARA_STRU astRxOptPara[CT_MAX_RX_CAL_NUM];

} CT_AGC_CAL_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;           /* 消息标识*/
    UINT16 usAagcNum;
    UINT16 usRsv;
    UINT32 aulAGCValue[CT_F_AAGC_SET_MAX_NUM];  /* AAGC增益值 前8为NO BLK，再8为BLK*/
} CT_AAGC_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_AAGC_SET_CNF_STRU;

/*****************************************************************************
 描述 :
 ID   : PHY_OM_CT_F_MEAS_RSSI_IND
 REQ  : NA
 CNF  : NA
 IND  : PHY_OM_CT_F_MEAS_RSSI_IND_STRU
 说明 :
*****************************************************************************/
typedef struct
{
    /* AT指令集-装备定义:*/
    /*  个值采用正值表示，精确到0.125dBm定制值信息，取值范围为160~880。*/
    /*  如果当前的RSSI值为-85.125dBm，范围值为-85.125dbm*(-1)/0.125dbm = 681*/

    INT16  sRxANT1RSSI;
    INT16  sRxANT2RSSI;
	INT16  sRxANT3RSSI;
    INT16  sRxANT4RSSI;
} CT_F_ANT_RSSI_STRU;

typedef struct
{
    UINT32 ulMsgId;
    UINT16 usFreqNum;
    UINT16 usPowNum;

    CT_F_ANT_RSSI_STRU  astRxANTRSSI[FREQ_MAX_NUM][POW_MAX_NUM];
} PHY_OM_CT_F_MEAS_RSSI_IND_STRU;

typedef struct
{
    UINT32 ulMsgId;
    UINT16 usFreqNum;
    UINT16 usPowNum;

    CT_F_ANT_RSSI_STRU  astRxANTRSSI[CT_MAX_RX_CAL_NUM];
} CT_RX_MEAS_RSSI_IND_STRU;

/*****************************************************************************
 描述 :
 ID   : PHY_OM_CT_F_MEAS_CMTMS_IND
 REQ  : NA
 CNF  : NA
 IND  : PHY_OM_CT_F_MEAS_CMTMS_IND_STRU
 说明 :
*****************************************************************************/

typedef struct
{
    UINT32  ulMsgId;
#ifdef MBX_RTT_CBT
    UINT16  usMsgStatus;
    UINT16  usCmtsReadStatus;
#endif
    UINT16  usCmtmsNum; 					     /* 温度值数量，取值范围为0～16*/
    UINT16  usType;

    UINT16  ausCmtms[TX_POW_MAX_NUM]; /* 温度值列表，取值范围为0～256，若温度值数量为0则没有温度值列表*/

} PHY_OM_CT_F_MEAS_CMTMS_IND_STRU;


/*****************************************************************************
 描述 : 指示RTT设置PA
 ID   : OM_PHY_CT_F_PA_SET_REQ,PHY_OM_CT_F_PA_SET_CNF
 REQ  : OM_PHY_CT_F_PA_SET_REQ_STRU
 CNF  : PHY_OM_CT_F_PA_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
#define CT_F_PA_SET_MAX_NUM   (30)
typedef struct
{
    UINT32 ulMsgId;
    UINT16 usLevelNum;
    UINT16 usRsv;
    UINT8 aucLvlList[CT_F_PA_SET_MAX_NUM];
} OM_PHY_CT_F_PA_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_PA_SET_CNF_STRU;

/*****************************************************************************
 描述 : 配置使能PD标志
 ID   : OM_PHY_CT_F_PD_REQ_STRU,OM_PHY_CT_F_PD_CNF_STRU
 REQ  : OM_PHY_CT_F_PD_REQ_STRU
 CNF  : OM_PHY_CT_F_PD_CNF_STRU
 IND  : PHY_OM_CT_F_PD_IND_STRU
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                          /* 消息标识 */
    UINT32 ulPdEnbFlg;                       /*指示PD是否使能*/
    UINT16 usDacCfg;
    UINT16 usVgaCfg;
} OM_PHY_CT_F_PD_REQ_STRU;

typedef PHY_MSP_CT_SINGLE_CNF_STRU PHY_OM_CT_F_PD_CNF_STRU;

typedef struct
{
    UINT32 ulMsgId;                      /*消息标识  */
    UINT16 ausFreqVota[FREQ_MAX_NUM][POW_MAX_NUM];
} PHY_OM_CT_F_PD_IND_STRU;

/*****************************************************************************
 描述 : PD自校准使能
 ID   : OM_PHY_CT_F_PD_AUTOCAL_REQ_STRU,OM_PHY_CT_F_AUTO_CAL_CNF_STRU
 REQ  : OM_PHY_CT_F_AUTO_CAL_REQ_STRU
 CNF  : PHY_OM_CT_F_PD_AUTO_IND_STRU
 IND  : NAN
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识   */
    UINT32 ulPdAutoFlg;                  /*指示PD是否使能*/
} OM_PHY_CT_F_PD_AUTOCAL_REQ_STRU;

typedef PHY_MSP_CT_SINGLE_CNF_STRU PHY_OM_CT_F_PD_AUTOCAL_CNF_STRU;

typedef struct
{
    UINT32 ulMsgId;                      /*消息标识  */
    UINT16 usDacCfg;                     /*自校准获得的DAC配置*/
    UINT16 usVgaCfg;                     /*自校准获得的VGA配置*/
    UINT16 usVgaErrorFlg;                /*VGA校准异常标志*/
    UINT16 usRsv;
} PHY_OM_CT_F_PD_AUTO_IND_STRU;

/*****************************************************************************
 描述 : 指示RTT设置SEGMENT
 ID   : OM_PHY_CT_F_SEGMENT_SET_REQ,PHY_OM_CT_F_SEGMENT_SET_CNF
 REQ  : OM_PHY_CT_F_SEGMENT_SET_REQ_STRU
 CNF  : PHY_OM_CT_F_SEGMENT_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */
    UINT16 usSegment;                    /* 10,20毫秒 */
    UINT16 measOffset;                   /* 表示测量起始位置偏移，单位ms，取值范围0~20，无默认值*/
	UINT16 measLen;                      /* 表示测量长度，单位ms，取值范围0~20，无默认值 */
    UINT16 usRsv;
} OM_PHY_CT_F_SEGMENT_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_SEGMENT_SET_CNF_STRU;

/*****************************************************************************
 描述 : 指示RTT设置发射波形
 ID   : OM_PHY_CT_F_TXWAVE_SET_REQ,PHY_OM_CT_F_TXWAVE_SET_CNF
 REQ  : OM_PHY_CT_F_TXWAVE_SET_REQ_STRU
 CNF  : PHY_OM_CT_F_TXWAVE_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */

    /* < wave_type >  设置发射机的发射波形*/
    /*   0    CW波型（DSP默认配置为CW波型）*/
    /*   1    LTE波型(1.4M)*/
    /*   2    LTE波型(3M)*/
    /*   3    LTE波型(5M)*/
    /*   4    LTE波型(10M)*/
    /*   5    LTE波型(15M)*/
    /*   6    LTE波型(20M)*/
    /*   11  TDS波型(1.6M)*/
    UINT16 usWaveType;

    INT16 usPower;
} OM_PHY_CT_F_TXWAVE_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_TXWAVE_SET_CNF_STRU;

/*****************************************************************************
 描述 : 启动快速校准TRIGGER及后续校准流程
 ID   : OM_PHY_CT_F_TRIGGER_SET_REQ,PHY_OM_CT_F_TRIGGER_SET_CNF 设置ID
        OM_PHY_CT_F_TRIGGER_RD_REQ,PHY_OM_CT_F_TRIGGER_RD_CNF   查询ID
 REQ  : OM_PHY_CT_F_TRIGGER_SET_REQ_STRU OM_PHY_CT_F_TRIGGER_RD_REQ_STRU
 CNF  : PHY_OM_CT_F_TRIGGER_SET_CNF_STRU PHY_OM_CT_F_TRIGGER_RD_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */

    /* 0    发送通道校准*/
    /* 1    接收通道校准（接收默认为双通道）*/
    /* 2    发射/接收通道同时校准（接收默认为双通道）*/
    UINT8 ucType;

    UINT8 padding[3];
} OM_PHY_CT_F_TRIGGER_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_TRIGGER_SET_CNF_STRU;

typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */
} OM_PHY_CT_F_TRIGGER_RD_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;

#ifdef MBX_RTT_CBT
    UINT16 usMsgStatus;
    UINT16 usRsv;
#endif
    /* 0    发送通道校准*/
    /* 1    接收通道校准（接收默认为双通道）*/
    /* 2    发射/接收通道同时校准（接收默认为双通道）*/
    UINT8 ucType;

    /* 快速校准状态*/
    /* 0    未启动或执行完毕*/
    /* 1    执行中*/
    UINT8 ucStatus;

    UINT8 ucRsv[2];
} PHY_OM_CT_F_TRIGGER_RD_CNF_STRU;

/*BLOCKING*/
typedef struct
{
    UINT32 ulMsgId;
	UINT16 usIsBLKMode;
	UINT16 usRsv;
}OM_PHY_CT_F_BLK_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
}PHY_OM_CT_F_BLK_SET_CNF_STRU;

/*IP2*/
typedef struct
{
    UINT32 ulMsgId;       /*消息标识*/
    UINT16 usBand;        /*IP2校准band值*/
    UINT16 usRsv;
} OM_PHY_CT_F_IP2START_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;       /*消息标识*/
} PHY_OM_CT_F_IP2START_CNF_STRU;


typedef struct
{
    UINT32 ulMsgId;       /*消息标识*/
    INT16 ulIP2Value1;     /*IP2校准结果1*/
    INT16 ulIP2Value2;     /*IP2校准结果2*/
} PHY_OM_CT_F_MEAS_IP2_IND_STRU;
/*PHY_OM_CT_F_MEAS_IP2_IND_STRU*/

/*****************************************************************************
 描述 : MAXPOWER校准请求
 ID   : OM_PHY_CT_F_MAX_POWER_REQ,PHY_OM_CT_F_MAX_POWER_CNF
 REQ  : OM_PHY_CT_F_MAX_POWER_REQ_STRU
 CNF  : PHY_OM_CT_F_MAX_POWER_CNF_STRU
 IND  : NAN
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识*/
    UINT16 usPaLevelNum;                 /*需要校准的PA 档位数目0-4*/
    UINT16 usPaReduceGain;               /*新增20111029；0-20*/
} OM_PHY_CT_F_MAX_POWER_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;                      /*消息标识*/
} PHY_OM_CT_F_MAX_POWER_SET_CNF_STRU;

/*****************************************************************************
 描述 : PAPOWER设置
 ID   : OM_PHY_CT_F_PA_POWER_SET_REQ,PHY_OM_CT_F_PA_POWER_SET_CNF
 REQ  : OM_PHY_CT_F_PA_POWER_SET_REQ_STRU
 CNF  : PHY_OM_CT_F_PA_POWER_SET_CNF_STRU
 IND  : NAN
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识*/
    UINT16 usPaLevelNum;
    UINT16 usRsv;
    INT16 asMaxPwrList[4];              /*校准后的MAXPOWER值*/
} OM_PHY_CT_F_PA_POWER_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;                      /*消息标识*/
} PHY_OM_CT_F_PA_POWER_SET_CNF_STRU;

/*****************************************************************************
 描述 : 8.6	服务小区信息查询命令^LTESCINFO
 ID   : OM_PHY_RD_LTESCINFO_REQ_STRU,OM_PHY_RD_LTESCINFO_CNF_STRU   查询ID
 REQ  : OM_PHY_RD_LTESCINFO_REQ_STRU
 CNF  : OM_PHY_RD_LTESCINFO_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */
} OM_PHY_RD_LTESCINFO_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;

    UINT16 usCid;     /* 物理小区ID,取值范围：0 ~ 503 ，65535表示没有获取到当前服务小区ID*/

    INT16  usDlSinr ; /* 下行链路信噪比,取值范围：-20 ~ 30*/
    UINT16 usDlBw ;   /* LTE downlink bandwidth*/

    UINT8  ucNumAnt;  /* 当前天线个数,0~4*/
    UINT8  ucRsv;
} PHY_OM_RD_LTESCINFO_CNF_STRU;


/*****************************************************************************
 描述 : 非信令综测设置单板同步状态
 在调试状态下触发UE与综测仪（MT8820C/CMW500）的同步过程，若同步成功直接返回OK，否则返回ERROR。
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 ID   : OM_PHY_SYN_SSYNC_SET_REQ,PHY_OM_SYN_SSYNC_SET_CNFs
 REQ  : OM_PHY_SYN_SSYNC_SET_REQ_STRU
 CNF  : PHY_OM_SYN_SSYNC_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;     /* 消息标识 */
    UINT16 usMode;      /* MODE TDD：1；FDD：0*/
    UINT16 usBand;      /* LTE频段信息，取值范围1～50，如7代表Band7*/
    UINT16 usUlchannel; /* 上行同步信道，取值范围0～65535*/
    UINT16 usDlchannel; /* 下行同步信道，取值范围0～65535*/
} OM_PHY_SYN_SSYNC_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_SSYNC_SET_CNF_STRU;

/*****************************************************************************
 描述 : 非信令综测查询单板同步状态
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 ID   : OM_PHY_SYN_SSYNC_RD_REQ,PHY_OM_SYN_SSYNC_RD_CNF
 REQ  : OM_PHY_SYN_SSYNC_RD_REQ_STRU
 CNF  : PHY_OM_SYN_SSYNC_RD_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
/*DSP主动上报*/
typedef struct
{
    UINT32 ulMsgId;

    /* UE与综测仪同步状态 */
		/* 0	已经同步成功*/
		/* 1	未同步或同步失败*/
    UINT32 ulStatus;
} PHY_OM_SYN_SSYNC_RPT_IND_STRU;


/*****************************************************************************
 描述 : ^STXBW 非信令综测设置发射带宽
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 该命令需要在设置非信令综测同步（^SSYNC）后执行(MSP可以加简单判断，初步实现可以先不加入)
 ID   : OM_PHY_SYN_STXBW_SET_REQ,PHY_OM_SYN_STXBW_SET_CNF
 REQ  : OM_PHY_SYN_STXBW_SET_REQ_STRU
 CNF  : PHY_OM_SYN_STXBW_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;

    /* 置综测测试上行发射带宽的列表，取值范围0~5，默认值为0*/
    /* 0	1.4M*/
    /* 1	3M*/
    /* 2	5M*/
    /* 3	10M*/
    /* 4	15M*/
    /* 5	20M*/
    UINT16 usBandwide;
    UINT16 usRsv;
} OM_PHY_SYN_STXBW_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_STXBW_SET_CNF_STRU;

/*****************************************************************************
 描述 : ^SCONFIG 非信令综测设置子帧配比
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 ID   : OM_PHY_SYN_SCONFIG_SET_REQ,PHY_OM_SYN_SCONFIG_SET_CNF
 REQ  : OM_PHY_SYN_SCONFIG_SET_REQ_STRU
 CNF  : PHY_OM_SYN_SCONFIG_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;

    /* RTT通过usFrameNumer/usFrameDeno,计算子帧配比usFrameNumer=7，usFrameDeno=6，*/
    /* usFrameNumer/usFrameDeno=7/6*/
    UINT16 usSubFrameAssign;
    UINT16 usSubFramePattern;
} OM_PHY_SYN_SSUBFRAME_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_SSUBFRAME_SET_CNF_STRU;

/*****************************************************************************
 描述 : ^STXCHAN 非信令综测
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 该命令需要在设置非信令综测同步（^SSYNC）后执行(MSP可以加简单判断，初步实现可以先不加入)
 ID   : OM_PHY_SYN_STXCHAN_SET_REQ,PHY_OM_SYN_STXCHAN_SET_CNF
 REQ  : OM_PHY_SYN_STXCHAN_SET_REQ_STRU
 CNF  : PHY_OM_SYN_STXCHAN_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;

    /* 上行同步信道，取值范围0～65535*/
    UINT16 usUlchannel ;
    UINT16 usRsv;
} OM_PHY_SYN_STXCHAN_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_STXCHAN_SET_CNF_STRU;

/*****************************************************************************
 描述 : ^SPARA 非信令综测设置子帧配比
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。

 ID   :
 REQ  :
 CNF  :
 IND  : NA
 说明 :
*****************************************************************************/

typedef struct
{
	UINT32 ulMsgId;
	/*设置参数类型，取值范围0~32*/
	UINT16 usType;
	/*设置参数值，取值范围0~65535*/
	UINT16 usValue;

} OM_PHY_SYN_SPARA_SET_REQ_STRU;
typedef struct
{
	UINT32 ulMsgId;

} PHY_OM_SYN_SPARA_SET_CNF_STRU;
/*****************************************************************************
 描述 : ^SSEGNUM 非信令综测设置SEGMENT的数量
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。

 ID   :
 REQ  :
 CNF  :
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
	UINT32 ulMsgId;
	UINT16 usSegNum;
	UINT16 usReserved;

} OM_PHY_SYN_SSEGNUM_SET_REQ_STRU;
typedef struct
{
	UINT32 ulMsgId;

} PHY_OM_SYN_SSEGNUM_SET_CNF_STRU;

/*****************************************************************************
 描述 : ^STXMODUS 非信令综测设置调制方式
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 该命令需要在设置非信令综测同步（^SSYNC）后执行(MSP可以加简单判断，初步实现可以先不加入)
 ID   : OM_PHY_SYN_STXMODUS_SET_REQ,PHY_OM_SYN_STXMODUS_SET_CNF
 REQ  : OM_PHY_SYN_STXMODUS_SET_REQ_STRU
 CNF  : PHY_OM_SYN_STXMODUS_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;

    /* 设置综测测试调制方式的数量，取值范围0~50，默认值为0*/
    UINT16 usModulution_num  ;
	UINT16 usRsv;

    /* 设置综测测试调试方式列表，取值范围0~2，默认值为0*/
    /* （其中0代表QPSK，1代表16QAM，2代表64QAM）*/
    UINT16  usModulation_list [256];

} OM_PHY_SYN_STXMODUS_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_STXMODUS_SET_CNF_STRU;
/*****************************************************************************
 描述 : ^STXRBNUMS 非信令综测设置RB数量
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。

 ID   :
 REQ  :
 CNF  :
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;
    /* 设置综测测试上行发射RB的数量，取值范围0~50，默认值为0*/
    UINT16 usRb_num;
	UINT16 usRsv;
	/* 设置综测测试上行发射RB的列表，取值范围1~100，默认值1*/
    UINT16 usrb_list[256];
} OM_PHY_SYN_STXRBNUMS_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_STXRBNUMS_SET_CNF_STRU;


/*****************************************************************************
 描述 : ^STXRBPOSS 非信令综测设置RB位置
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 该命令需要在设置非信令综测同步（^SSYNC）及RB数量（^SRBNUMS）后执行。(MSP可以加简单判断，初步实现可以先不加入)
 ID   : OM_PHY_SYN_STXRBPOSS_SET_REQ,PHY_OM_SYN_STXRBPOSS_SET_CNF
 REQ  : OM_PHY_SYN_STXRBPOSS_SET_REQ_STRU
 CNF  : PHY_OM_SYN_STXRBPOSS_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;

    UINT16 usRbpos_num; /* 设置综测测试上行发射RB位置的数量，取值范围0~50，默认值为0*/
	UINT16 usRsv;

	UINT16 usrbpos_list[256];  /* 设置综测测试上行发射RB位置的列表，取值范围0~99，默认值为0*/
} OM_PHY_SYN_STXRBPOSS_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_STXRBPOSS_SET_CNF_STRU;

/*****************************************************************************
 描述 : ^STXPOWS 非信令综测设置发射功率
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 该命令需要在设置非信令综测同步（^SSYNC）后执行。(MSP可以加简单判断，初步实现可以先不加入)
 ID   : OM_PHY_SYN_STXPOWS_SET_REQ,PHY_OM_SYN_STXPOWS_SET_CNF
 REQ  : OM_PHY_SYN_STXPOWS_SET_REQ_STRU
 CNF  : PHY_OM_SYN_STXPOWS_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;

    UINT16 ulPow_num;   /* 设置综测测试上行发射RB位置的数量，取值范围0~50，默认值为0*/
	UINT16 usRsv;

	INT16 slPow_list[256];  /* 设置综测测试上行发射RB位置的列表，取值范围0~99，默认值为0*/
} OM_PHY_SYN_STXPOWS_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_STXPOWS_SET_CNF_STRU;


/*****************************************************************************
 描述 : ^STXCHANTYPES 非信令综测设置信道类型
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 该命令需要在设置非信令综测同步（^SSYNC）后执行。(MSP可以加简单判断，初步实现可以先不加入)
 ID   : OM_PHY_SYN_STXCHANTYPES_SET_REQ,PHY_OM_SYN_STXCHANTYPES_SET_CNF
 REQ  : OM_PHY_SYN_STXCHANTYPES_SET_REQ_STRU
 CNF  : PHY_OM_SYN_STXCHANTYPES_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;

    UINT16 usType_num; /* 设置综测测试上行发射信道的数量，取值范围0~50，默认值为0*/
    UINT16 usRsv;
		/* 0	PUSCH*/
		/* 1	PUCCH*/
		/* 2	PRACH*/
    UINT16 usType_list[256];/*	设置综测测试上行发射信道的列表，取值范围0~2*/
} OM_PHY_SYN_STXCHANTYPES_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_STXCHANTYPES_SET_CNF_STRU;

/*****************************************************************************
 描述 : ^SSEGLEN 非信令综测设置SEGMENT长度
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 该命令需要在设置非信令综测同步（^SSYNC）后执行。(MSP可以加简单判断，初步实现可以先不加入)
 ID   : OM_PHY_SYN_SSEGMENT_SET_REQ,PHY_OM_SYN_SSEGMENT_SET_CNF
 REQ  : OM_PHY_SYN_SSEGMENT_SET_REQ_STRU
 CNF  : PHY_OM_SYN_SSEGMENT_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;
    /* 10	10ms*/
    /* 20	20ms*/
	/* 50	50ms*/
	/* 100	100ms*/
    UINT16 usSegment_Len; /* 设置综测测试上行发射信道的数量，取值范围0~50，默认值为0*/


    UINT16 usReserved;
} OM_PHY_SYN_SSEGLEN_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_SSEGLEN_SET_CNF_STRU;

/*****************************************************************************
 描述 : ^SRXPOW 非信令综测接收测试的功率设置
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。



 ID  :
 REQ :
 CNF :
 IND : NA
 说明 :
*****************************************************************************/
typedef struct
{
	UINT32 ulMsgId;
	UINT16 usSwitch;
	INT16  sPower;
	UINT16 usMod;
	UINT16 usRBNum;
	UINT16 usRBPos;
	UINT16 usRsv;

}OM_PHY_SYN_SRXSET_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_SRXSET_SET_CNF_STRU;

/*****************************************************************************
 描述 : ^SRXSUBFRA 非信令综测接收测试的子帧数量
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。



 ID  :
 REQ :
 CNF :
 IND : NA
 说明 :
*****************************************************************************/
typedef struct
{
	UINT32 ulMsgId;
	UINT16 usSubFrameNum;
	UINT16 usReserved;

}OM_PHY_SYN_SRXSUBFRA_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_SRXSUBFRA_SET_CNF_STRU;
/*****************************************************************************
 描述 : ^SRXBLER 非信令综测接收测试查询误码率
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。



 ID  :
 REQ :
 CNF :
 IND : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;
    UINT32 ulBler[2];
	INT16  sSnr[2];
} PHY_OM_SYN_SRXMEAS_RPT_IND_STRU;

typedef struct
{
    UINT32 ulMsgId;
    UINT32 ulBersum;
	UINT32 ulBerErr;
	UINT32 usRsv;
} PHY_OM_SYN_SRXMEAS_TDS_RPT_IND_STRU;


typedef struct
{
    UINT32 ulMsgId;
	INT16  usPower;
	UINT16 usRsv;
} OM_PHY_SYN_FPOW_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_FPOW_SET_CNF_STRU;
/*****************************************************************************
 描述 : ^SSTART 非信令综测启动发射并状态查询
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 调试状态下启动sequence方式的非信令综测。
 该命令需要在设置AT^SSYNC、AT^SMODUS、AT^STXBWS、AT^SPOWS、AT^SCHANS、AT^SSEGMENT命令后执行。其它模式下返回错误码。
 (MSP可以加简单判断，初步实现可以先不加入)
 ID   : OM_PHY_SYN_SSTART_SET_REQ,PHY_OM_SYN_SSTART_SET_CNF
 REQ  : OM_PHY_SYN_SSTART_SET_REQ_STRU
 CNF  : PHY_OM_SYN_SSTART_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;
	UINT16 usType;
	UINT16 usRsv;
} OM_PHY_SYN_SSTART_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_SSTART_SET_CNF_STRU;

/*****************************************************************************
 描述 : ^SSTOP 非信令综测停止上行发射
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 ID   : OM_PHY_SYN_SSTOP_SET_REQ,PHY_OM_SYN_SSTOP_SET_CNF
 REQ  : OM_PHY_SYN_SSTOP_SET_REQ_STRU
 CNF  : PHY_OM_SYN_SSTOP_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;

	UINT16 usType;
	UINT16 usRsv;
} OM_PHY_SYN_SSTOP_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_SSTOP_SET_CNF_STRU;


// *****************************************************************************
// 描述 : 波形与功率设置
// ID   : OM_PHY_CT_FWAVE_SET_REQ,PHY_OM_CT_FWAVE_SET_CNF
// REQ  : OM_PHY_CT_FWAVE_SET_REQ_STRU
// CNF  : PHY_OM_CT_FWAVE_SET_CNF_STRU
// 说明 :
// *****************************************************************************
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */
    UINT16 usType;                       /*0:表示continues wave信号; 1:表示1.4MHz LTE信号*/
    INT16 usPower;                       /*2300:23db*/
} OM_PHY_CT_FWAVE_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_FWAVE_SET_CNF_STRU;



/*****************************************************************************
 结构名    : LMSP_LPHY_COEX_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    LMSP_LPHY_COEX_BW_TYPE_ENUM_UINT16         enCoexBWType;
    LMSP_LPHY_COEX_ENABLE_IND_ENUM_UINT16      enCoexEnableInd;
    UINT16                                     usTx_begin;
    UINT16                                     usTx_End;
    INT16                                      sTxPower;
    UINT16                                     usRx_begin;
    UINT16                                     usRx_End;
    UINT16                                     usReserved;
} LMSP_LPHY_COEX_PARA_STRU;

/*****************************************************************************
 结构名    : LMSP_LPHY_LTE_WIFI_COEX_SET_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    LMSP_LPHY_MSG_ID_ENUM_UINT32               enMsgId;
    UINT16                                     usCoexParaNum;
    UINT16                                     usCoexParaSize;
    LMSP_LPHY_COEX_PARA_STRU                   astCoexPara[LMSP_LPHY_COEX_BAND_WIDTH_BUTT];
} LMSP_LPHY_LTE_WIFI_COEX_SET_REQ_STRU;

/*****************************************************************************
 结构名    : LMSP_LPHY_LTE_WIFI_COEX_SET_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    LMSP_LPHY_MSG_ID_ENUM_UINT32               enMsgId;
    UINT16                                     usReserved;
    LMSP_LPHY_RESULT_ENUM_UINT16               enCoexParaConfigResult;
} LMSP_LPHY_LTE_WIFI_COEX_SET_CNF_STRU;

// *****************************************************************************
// 描述 : 通用AT命令设置
// ID   : OM_PHY_COMM_CMD_SET_REQ,PHY_OM_COMM_CMD_SET_CNF,PHY_OM_COMM_CMD_IND
// REQ  : OM_PHY_COMM_CMD_SET_REQ_STRU
// CNF  : PHY_OM_COMM_CMD_SET_CNF_STRU
// 说明 :
// *****************************************************************************
#define MAX_COMM_CMD_LEN 1152

typedef struct
{
    UINT32 ulMsgId;                  /* 消息标识 */
    UINT32 ulDataLen;                /* 数据长度 */
    INT8   cData[MAX_COMM_CMD_LEN];   /* 数据     */
}OM_PHY_COMM_CMD_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;                  /* 消息标识 */
    UINT32 ulDataLen;                /* 数据长度 */
    INT8   cData[MAX_COMM_CMD_LEN];   /* 数据     */
}PHY_OM_COMM_CMD_SET_CNF_STRU;

typedef PHY_OM_COMM_CMD_SET_CNF_STRU PHY_OM_COMM_CMD_IND_STRU;


typedef struct
{
    UINT16 usFreq;
    UINT16 usTxRfCodeIndex;           /*发射功率控制字，包括RF和IF两部分*/
    UINT8 ucPaLevel;
    UINT8 ucRsv[3];
}CT_TX_OPT_PARA_STRU;

typedef struct
{
    UINT16 usWave;                                 /* CW波：0， LTE波：1  */
    UINT16 usSegment;                              /* 发送单一功率时长，单位ms  */
    UINT32 usTxCalNum;

    CT_TX_OPT_PARA_STRU astTxOptPara[TX_POW_MAX_NUM];
}CT_F_TX_PARA_STRU;

typedef struct
{
    UINT32 ulCmdId;                      /*消息标识*/
    CT_F_TX_PARA_STRU    stTxPara;
} CT_F_APCCAL_SET_REQ_STRU;

typedef struct
{
    UINT32 ulCmdId;                      /*消息标识*/
    UINT8  ucType;
    UINT8  aucRsv[3];
} CT_F_APCCAL_START_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;           /*消息标识*/
    UINT16 usMode;            /*UE 模式*/
    UINT16 usBand;            /*频段*/
    UINT16 usDLStFreq;       /*下行扫频起始频点*/
    UINT16 usDLEdFreq;       /*下行扫频结束频点*/
    UINT16 usFreqStep;       /*下行扫频步长*/
    INT16   usTxPwr;            /*上行发射功率*/
    UINT16 usBandWidth;
    UINT16 usRsv;
}OM_PHY_NOISE_CFG_REQ_STRU;

typedef struct
{
    UINT16 usDLFreq;       /*当前测量频点*/
    INT16   sDLPriRssi;   /*PHY上报主集频点对应的RSSI*/
    INT16   sDLDivRssi;   /*PHY上报分集频点对应的RSSI*/
    UINT16 usRsv;
}PHY_NOISE_RESULT_STRU;
typedef struct
{
    UINT16 usDLRssiNum;
    UINT16 usRsv;
    PHY_NOISE_RESULT_STRU astDlRssiResult[32];
}LHPA_NOISE_RESULT_STRU;
typedef struct
{
    UINT32 ulMsgId;
    LHPA_NOISE_RESULT_STRU  stRssiInd;
}PHY_OM_NOISE_RSSI_IND_STRU;

/*通用AT命令CmdId*/
typedef enum
{
	COMM_AT_CMD_ID_RFTEST              = 0x0,
	COMM_AT_CMD_QUERY_BANDINFO,
	COMM_AT_CMD_QUERY_RX_POWER,
	COMM_AT_CMD_QUERY_HKADC,

    COMM_AT_CT_AAGCSET_CMDID           = 0x6,
    COMM_AT_CT_APCCAL_CMDID            = 0x7,
    COMM_AT_CT_APCSTART_CMDID          = 0x8,
    COMM_AT_CT_TXPARA_CMDID            = 0x9,
    COMM_AT_ET_SWITCH_CMDID            = 0xa,
    COMM_AT_ET_VOUT_CAL_REQ_CMDID,
    COMM_AT_ET_VOUT_REPORT_CMDID,
    COMM_AT_ET_LUT_SET_CMDID,
    COMM_AT_ET_FINEDLY_PARA_SET_CMDID,
    COMM_AT_ET_EVELY_SET_CMDID,
    COMM_AT_CT_CA_RF_RCCAL_Req,
    COMM_AT_CT_RFCAL_SETCODE_CMDID,
	COMM_AT_COM_NOTCH_SET              = 0x14,
	COMM_AT_CMD_XO_C2FIX               = 0x15,
	COMM_AT_CMD_XO_FRESH_C2FIX,
	COMM_AT_CMD_XO_C1FIX,
	COMM_AT_CMD_XO_FRESH_C1FIX,
	COMM_AT_CMD_XO_AFC_CAL,
	COMM_AT_CMD_XO_QUERY_HKADC,
	COMM_AT_CMD_XO_FRESH_AFC_TEMP,
	COMM_AT_CMD_RF_TOOL               //0x22
}NCIT_BTCT_COMM_AT_CMDID;



#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#elif defined(MS_VC6_PLATFORM)
#pragma pack(pop)
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


#endif //end of _DSP_CT_EX2_H

