

#ifndef __TPSTPHYINTERFACE_H__
#define __TPSTPHYINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#ifndef LPS_RTT
#include "vos.h"
#include "LPSCommon.h"
#else
#define PS_MSG_ID_TDS_PS_BASE   0x1355
#define VOS_MSG_HEADER
#endif
/*trch change 6 to 8 add marco*/
#include  "product_config.h"

/*#pragma pack(4) */
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/

#define hiPDSCHidentities          1
#define hiPUSCHidentities          1
#define hiRM                       256
#define maxAC                      16
#define maxAdditionalMeas          4
#define maxASC                     8
#define maxASCmap                  7
#define maxASCpersist              6
#define maxCCTrCH                  1
#define maxCellMeas                32
#define maxCellMeas_1              31
#define maxCNdomains               2
#define maxCPCHsets                1
#define maxDPCH_DLchan             8
#define maxDPDCH_UL                6
#define maxDRACclasses             1
#define maxFACHPCH                 8
#define maxFreq                    8
#define maxFreqBandsFDD            1
#define maxFreqBandsTDD            4
#define maxFreqBandsGSM            1
#define maxHProcesses              8
#define maxHSSCCHs                 4
#define maxInterSysMessages        4
#define maxLoCHperRLC              2
#define maxMAC_d_PDUsizes          8
#define maxMeasEvent               8
#define maxMeasIntervals           3
#define maxMeasParEvent            2
#define maxNumCDMA2000Freqs        1
#define maxNumGSMFreqRanges        1
#define maxNumFDDFreqs             1
#define maxNumTDDFreqs             8
#define maxNoOfMeas                16
#define maxOtherRAT                1
#define maxOtherRAT_16             1
#define maxPage1                   8
#define maxPCPCH_APsig             1
#define maxPCPCH_APsubCh           1
#define maxPCPCH_CDsig             1
#define maxPCPCH_CDsubCh           1
#define maxPCPCH_SF                1
#define maxPCPCHs                  1
#define maxPDCPAlgoType            8
#define maxPDSCH                   1
#define maxPDSCH_TFCIgroups        1
#define maxPRACH                   16
#define maxPRACH_FPACH             8
#define maxPredefConfig            16
#define maxPUSCH                   1
#define maxRABsetup                16
#define maxQueueIDs                8
#define maxRAT                     1
/*trchnum 6 change 8 maxrb 10 change 16*/
#ifdef TL_PS_MAX_TRCH_NUM_8
#define maxRB                      16
#else
#define maxRB                      10
#endif
#define maxRBallRABs               27
#define maxRBMuxOptions            4
#define maxRBperRAB                3
#define maxReportedGSMCells        8
#define maxRL                      1
#define maxRL_1                    1
#define maxROHC_PacketSizes_r4     16
#define maxROHC_Profile_r4         16
#define maxSat                     16
#define maxSCCPCH                  16
#define maxSIB                     32
#define maxSIB_FACH                8
#define maxSIBperMsg               16
#define maxSRBsetup                8
#define maxSystemCapability        1
#define maxTDD128Carrier           6
#define maxTF                      24
#define maxTF_CPCH                 1
#define MAX_SIB16_INSTANCE         16

#define maxNumEUTRAFreqs           8
#define maxEUTRACellPerFreq        16
#define maxGANSSSat                64
#define maxMeasCSGRange            4
#define maxSIrequest               4
#define maxCellMeasOnSecULFreq     32
#define maxMeasEventOnSecULFreq    8
#define maxMeasOccasionPattern     5
#define maxCommonHRNTI             4
#define maxEDCHs                   32
#define maxERUCCH                  256
#define maxERNTIgroup              32
#define maxERNTIperGroup           2
#define maxDedicatedCSGFreq        4
#define maxPrio                    8
#define maxNumGSMCellGroup         16
#define maxHNBNameSize             48
#define maxGANSS                   8
#define maxSgnType                 8
#define maxReportedEUTRAFreqs      4
#define maxReportedEUTRACellPerFreq 4


#define maxTFC                     128

#define maxTFCsub                  60
#define maxTFCI_2_Combs            1
#define maxTGPS                    1
/*trchnum 6 change 8*/
#ifdef TL_PS_MAX_TRCH_NUM_8
#define maxTrCH                    8
#else
#define maxTrCH                    6
#endif
#define maxTrCHpreconf             6
#define maxTS                      6
#define maxTS_1                    5
#define maxTS_LCR                  6
#define maxTS_LCR_1                5
#define maxURA                     8
#define MAX_DPCH_DATA_LEN			1500

#define MAX_TDM_NUM                6

#define maxMacDFlow                8
#define maxBeta                    8
#define maxEagch                   4
#define maxEhich                   4
#define maxPrach                   2
#define maxE_DCHMACdFlow           8
#define maxNumEagch                4
#define maxNumEhich                4
#define maxRlcPduSize              32

#define ulbitMask_1                0x00000001
#define ulbitMask_2                0x00000003
#define ulbitMask_3                0x00000007
#define ulbitMask_4                0x0000000f
#define ulbitMask_5                0x0000001f
#define ulbitMask_6                0x0000003f
#define ulbitMask_7                0x0000007f
#define ulbitMask_8                0x000000ff
#define ulbitMask_9                0x000001ff
#define ulbitMask_10               0x000003ff
#define ulbitMask_11               0x000007ff
#define ulbitMask_12               0x00000fff
#define ulbitMask_13               0x00001fff
#define ulbitMask_14               0x00003fff
#define ulbitMask_15               0x00007fff
#define ulbitMask_16               0x0000ffff
#define ulbitMask_17               0x0001ffff
#define ulbitMask_20               0x000fffff
#define ulbitMask_22               0x003fffff
#define ulbitMask_24               0x00ffffff
#define ulbitMask_30               0x3fffffff
#define ulbitMask_32               0xffffffff


/* define constance for DHI work mode*/
#define  DHI_NORMAL
#define  DHI_TEST
#define  DHI_INVALID




#define  MAX_DHI_DATA_LEN  704
/*#define  MAX_DHI_DATA_LEN_SCCPCH 1408*/


#define  MAX_HS_PDU_LEN    1800
#define  maxIntraCellNum   32
#define  maxIscpNum        32
#define maxMeasFreq 9
#define maxIscpMeasFreq 3
#define maxMeasNum 64
#define maxFreqBand 12
#define maxPoint 36
#define maxCellNum 64

/*add for dm*/
#define maxBsicNum          8
#define maxGsmCellNum       32

#define MAX_TMSI_LEN         4
#define MAX_PTMSI_LEN        4

/*moved from hl1_mac.het  ylm 20100805*/
#ifdef TL_PS_MAX_TRCH_NUM_8
#define  MAX_DHI_LEN                     2600
#else
#define  MAX_DHI_LEN                     2100
#endif

/*TDS用户面性能优化:PDCP零拷贝q00208938 20151008 begin*/
/*#define MAX_PDCP_HEADER_LEN             3*/
#define MAX_PDCP_HEADER_LEN             (0)
/*TDS用户面性能优化:PDCP零拷贝q00208938 20151008 end*/

#define MAX_FRAME_NUM                   8192 /* sub frame*/

#define TPDC_DATA_REQ_QUE_SIZE          512

#define TDS_MAX_BAR_CELLID              8
#define TDS_MAX_FREQ                    (24) /*一个同频+8个异频*/
#define TDS_MAX_DETECT_CELL_PER_FREQ    (6)/*一个频点最多的detect小区个数*/

/*物理层一次请求写入NV最大个数*/
#define TRRC_TPHY_MAX_NV_WRITE_NUM        4

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum
{
      /*TPS-->TPhy Request  Begin*/
        OP_L1_NULL_REQ                  = (PS_MSG_ID_TDS_PS_BASE + 0x0000),  /*PS_MSG_ID_TDS_PS_BASE = 0x1355(4949)*/

        OP_L1_CELL_MEAS_REQ,
        OP_L1_HW_PARA_INIT_REQ,
        OP_L1_ICS_MEAS_REQ,
        OP_L1_FREQ_ADJUST_REQ,
        OP_L1_MIDAMBLE_READ_REQ,
        OP_L1_FREQ_FINE_REQ,
        OP_L1_PHASE_DETECT_REQ,
        OP_L1_PCCPCH_READ_REQ,
        OP_L1_PICH_READ_REQ,
        OP_L1_IDL_MEAS_REQ,    /*10*/
        OP_L1_PRACH_SEND_REQ,
        OP_L1_SCCPCH_READ_REQ,
        OP_L1_DPCH_CONFIG_REQ,
        OP_L1_DPCH_SEND_REQ,
        OP_L1_VCD_REQ,

        OP_L1_DCH_MEAS_REQ,
        OP_L1_HO_SYNC_SEND_REQ,
        OP_L1_PWR_SWEEP_REQ,
        OP_L1_CELL_SEARCH_REQ,
        OP_L1_HL1_SFN_REQ,        /*20*/
        OP_L1_LOOP_TEST_REQ,
        OP_L1_IDL_TASK_REQ,
        OP_L1_HSPDSCH_CONFIG_REQ,
        //OP_L1_IDL_TASK_REQ,

        OP_L1_MCCH_READ_REQ,
        OP_L1_MTCH_READ_REQ,
        OP_L1_MBMS_STOP_REQ,

        OP_L1_EPUCH_CONFIG_REQ,
        OP_L1_EPUCH_SEND_REQ,
        // 20090928  PDM100 UMAC
        OP_L1_BSIC_REQ,
        OP_L1_STOP_BSIC_REQ,       /*30*/
        OP_L1_PRE_SYNC_REQ,
        OP_L1_GAP_INFO_REQ,
        OP_L1_IRAT_MEAS_REQ,
        OP_L1_IRAT_INACTIVE_REQ,
        OP_RABMCOM_DATA_REQ,

        /* TDS主模非DCH态下，使用此原语将GL测量频点通知TDSP。若G/L频点个数为0，表示释放。 */
        ID_TMAC_TPHY_IRAT_MEAS_REQ,

        /* 释放物理层原语 */
        ID_TMAC_TPHY_REL_REQ,      /*37*/
        ID_L2_HPA_STATE_CHANGE_REQ,
        ID_TRRC_TPHY_SET_WORK_MODE_REQ,
        OP_L1_IDL_PCH_REQ,
        ID_TRRC_TPHY_NOTCH_REQ,

        ID_TMAC_TPHY_BSIC_FRAME_REQ,

        ID_TPHY_STOP_CELL_SELECT_REQ,

        ID_TRRC_TPHY_NV_WRITE_RSP,
        ID_TRRC_TPHY_DPDT_CMD_REQ,          /*消息方向 TRRC -> TPHY*/
        ID_TRRC_TPHY_SWTICH_IND,

        ID_TMAC_TPHY_REQ_BUTT,    /*butten*/

        /*---------------------------------TPS-->TPhy Request  End---------------------------------*/


        /*-------------------------------TPhy-->TPS  Cnf & Ind Begin-------------------------------*/

        //OP_L1_VB_SYNC                   = (PS_MSG_ID_TDS_PS_BASE + 0x0032),
        /* OP_L1_VB_SYNC,*/
        OP_L1_VB_SYNC                   = (PS_MSG_ID_TDS_PS_BASE + 0x0050),
        OP_L1_CELL_MEAS_CNF,
        OP_L1_ICS_MEAS_CNF,
        OP_L1_FREQ_ADJUST_CNF,
        OP_L1_MIDAMBLE_READ_CNF,
        OP_L1_FREQ_FINE_CNF,
        OP_L1_PHASE_DETECT_CNF,
        OP_L1_PCCPCH_READ_CNF,
        OP_L1_PICH_READ_IND,
        OP_L1_IDL_MEAS_IND,
        OP_L1_FPACH_READ_CNF,    /*10*/
        OP_L1_SCCPCH_READ_IND,
        OP_L1_DPCH_READ_IND,
        OP_L1_DPCH_SYNC_IND,

        /* 对OP_L1_DCH_MEAS_REQ的回复 */
        ID_L1_DCH_MEAS_CNF,
        OP_L1_DCH_MEAS_IND,
        OP_L1_PWR_SWEEP_CNF,
        OP_L1_CELL_SEARCH_CNF,
        OP_L1_DSP_CNF,
        OP_L1_FCH_MEAS_IND,
        OP_L1_HSPDSCH_READ_IND, /*20*/

        //20100406
        OP_L1_ZSP_ABNORMAL_IND,
        //OP_L1_HSUPA_INFO_IND
        OP_L1_HSUPA_INFO_IND,
        OP_L1_HARQ_IND,

        //20090928 PDM100 UMAC
        /* 对OP_L1_BSIC_REQ的回复 */
        ID_L1_BSIC_CNF,
        OP_L1_BSIC_IND,
        OP_L1_STOP_BSIC_CNF,
        //gongjian 20101123  D_PS_PDM100_UMAC_V0.6.3_003
        OP_L1_PRE_SYNC_CNF,
        OP_L1_IRAT_MEAS_IND,
        OP_L1_IRAT_INACTIVE_CNF,
        OP_L1_GAP_END_IND,  /*30*/

        OP_HL1_SCHEDULE_IND,
        OP_HL1_END,

        OP_RABMCOM_DATA_IND,
        OP_RABMCOM_SUSPEND_IND,
        OP_RABMCOM_RESUME_IND ,

        /* 对OP_L1_IRAT_MEAS_REQ的回复 */
        ID_L1_IRAT_MEAS_CNF,

        /* 对ID_TMAC_TPHY_IRAT_MEAS_REQ的回复 */
        ID_TMAC_TPHY_IRAT_MEAS_CNF,

        /* 释放物理层原语 */
        ID_TMAC_TPHY_REL_CNF,

        /* 增加上报LoadDsp相关参数*/
        ID_L1_DYNA_LOAD_DSP_IND ,/*39*/
        ID_L2_HPA_STATE_CHANGE_CNF,
        ID_TRRC_TPHY_SET_WORK_MODE_CNF,
        OP_L1_IDL_PCH_IND,
        ID_TRRC_TPHY_ERRLOG_IND,//by wxm errlog

        ID_TPHY_STOP_CELL_SELECT_CNF,

        OP_DSDS_RF_STATE_CHANGE_IND,

        ID_TRRC_TPHY_NV_WRITE_IND,
        ID_TRRC_TPHY_DPDT_CMD_IND,           /*消息方向 TPHY -> TRRC*/

        ID_TRRC_TPHY_BUTT

      /*TPhy-->TPS  Cnf & Ind End*/

    };
typedef VOS_UINT32    TPS_TPHY_MSG_ID_ENUM_UINT32;


/*****************************************************************************
 枚举名    : TLRRC_TLPHY_DPDT_CMD_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 发送DPST命令的功能
*****************************************************************************/

enum TRRC_TPHY_DPDT_CMD_ENUM
{
    TRRC_TPHY_SET_SWITCH           = 0,    /*开关 */
    TRRC_TPHY_SET_VALUE            = 1,    /* 设置值 */
    TRRC_TPHY_DPDT_VALUE_QRY               /*查询*/
};
typedef VOS_UINT16  TRRC_TPHY_DPDT_CMD_ENUM_UINT16;


/*****************************************************************************
 枚举名    : TDS_REL_CAUSE_ENUM
 结构说明  : 标识释放的原因
 后续有其它需求再添加释放原因值
*****************************************************************************/
enum TDS_REL_CAUSE_ENUM
{
    TDS_REL_CAUSE_TDS_MEAS = 0x01,
    TDS_REL_CAUSE_GSM_MEAS = 0x02,
    TDS_REL_CAUSE_LTE_MEAS = 0x04,
    TDS_REL_CAUSE_WCDMA_MEAS = 0x08,
    TDS_REL_CAUSE_BUTT
};
typedef VOS_UINT16 TDS_REL_CAUSE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : TDS_RESULT_ENUM
 结构说明  : 标识结果

*****************************************************************************/
enum TDS_RESULT_ENUM
{
    TDS_RESULT_SUCC,
    TDS_RESULT_FAIL,
    TDS_RESULT_BUTT
};
typedef VOS_UINT16 TDS_RESULT_ENUM_UINT16;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : TRRC_TPHY_STOP_CELL_SELECT_CAUSE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : 停止搜索小区的原因
*****************************************************************************/
enum TRRC_TPHY_STOP_CELL_SELECT_CAUSE_ENUM
{
    TRRC_TPHY_STOP_CELL_SELECT_RESEARCH_STOP,   /*搜索过程中需要重新搜小区*/

    TRRC_TPHY_STOP_CELL_SELECT_BUIT
};
typedef VOS_UINT16 TRRC_TPHY_STOP_CELL_SELECT_CAUSE_ENUM_UINT16;
/*****************************************************************************
 结构名    : TRRC_TPHY_STOP_CELL_SELECT_RLST_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : 停止搜索小区的原因
*****************************************************************************/
enum TRRC_TPHY_STOP_CELL_SELECT_RLST_ENUM
{
    TRRC_TPHY_STOP_CELL_SELECT_CNF_SUCC,   /*停止成功*/
    TRRC_TPHY_STOP_CELL_SELECT_CNF_FAIL,
    TRRC_TPHY_STOP_CELL_SELECT_CNF_BUIT
};
typedef VOS_UINT16 TRRC_TPHY_STOP_CELL_SELECT_RLST_ENUM_UINT16;


/*****************************************************************************
 结构名    : TRRC_TPHY_DPDT_CMD_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TPS_TPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    TRRC_TPHY_DPDT_CMD_ENUM_UINT16                      enCmdIndex;           /*判断指令*/
    VOS_UINT8                                           ucSwitchFlag;      /*0关 1开*/
    VOS_UINT8                                           ucRev[3];
    VOS_UINT32                                          ulDpdtValue;
}TRRC_TPHY_DPDT_CMD_REQ_STRU;

/*****************************************************************************
 结构名    : TRRC_TPHY_DPDT_CMD_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TPS_TPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    VOS_UINT8                                           ucRev[2];
    VOS_UINT32                                          ulDpdtValue;
}TRRC_TPHY_DPDT_CMD_IND_STRU;


/*****************************************************************************
 结构名    : TRRC_TPHY_STOP_CELL_SELECT_REQ
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知物理层停止当前搜小区的流程
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                        enMsgId;
    VOS_UINT16                                        usOpId;
    TRRC_TPHY_STOP_CELL_SELECT_CAUSE_ENUM_UINT16      enStopCause;    /*停止搜网原因 */

}TRRC_TPHY_STOP_CELL_SELECT_REQ;
/*****************************************************************************
 结构名    : TRRC_TPHY_STOP_CELL_SELECT_CNF
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层回复停止搜网结果
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                        enMsgId;
    VOS_UINT16                                        usOpId;
    TRRC_TPHY_STOP_CELL_SELECT_RLST_ENUM_UINT16       enStopRlst;    /*停止搜网结果*/

}TRRC_TPHY_STOP_CELL_SELECT_CNF;



typedef struct
{
    VOS_UINT16          usFreq;
    VOS_UINT8           ucRssiLvl;
    VOS_UINT8           ucCellNum;
    VOS_UINT8           aucCellid[TDS_MAX_DETECT_CELL_PER_FREQ];
    VOS_UINT8           aucRscpLvl[TDS_MAX_DETECT_CELL_PER_FREQ];
    VOS_UINT8           aucIscpLvl[TDS_MAX_DETECT_CELL_PER_FREQ];
}T_DETECT_CELL_STRU;
typedef struct
{
    VOS_UINT16          usFreqNum;
    VOS_UINT16          usRsv;
    T_DETECT_CELL_STRU  astDetectCell[TDS_MAX_FREQ];
}T_DETECT_CELL_LIST_STRU;
//-----------------------------------------------------------------------------
typedef struct T_SemistaticTfInformation_DHI_Tag
{
  VOS_UINT16      channelCodingType;
  VOS_UINT16      rateMatchingAttribute;
  VOS_UINT16      crcSize;
  VOS_UINT16      reserved;              // for align

}T_SemistaticTfInformation_DHI;

typedef struct T_TransportFormat_DHI_Tag
{
  VOS_UINT16      tti;
  VOS_UINT16      tbNum;
  VOS_UINT16     tbSize;
  VOS_UINT16      reserved;
}T_TransportFormat_DHI;

typedef struct  T_PlmnReduce_Tag
{
  VOS_UINT16       mcc;//Mobile Colour Code (octet 1, octet 2 bits 1 to 4)
  VOS_UINT16       mnc;  //Mobile Network Code (octet 3, octet 2bits 5 to 8);
}T_PlmnRedcue;

typedef struct T_TmsiAndLaiReduce_Tag
{
  VOS_UINT16                            tmsi[MAX_TMSI_LEN];
  T_PlmnRedcue            plmnIdentity;//???? where definated???
  VOS_UINT16                            reserved;
  VOS_UINT16                            lac;//BIT STRING (SIZE (16))
}T_TmsiAndLaiReduce;

typedef struct T_PTmsiAndRaiReduce_Tag
{
  VOS_UINT16                             pTmsi[MAX_PTMSI_LEN];
  T_PlmnRedcue             plmnIdentity;//??????
  VOS_UINT16                             lac;//BIT STRING (SIZE (16))
  VOS_UINT16                             rac;
}T_PTmsiAndRaiReduce;

typedef struct T_InitialUeIdentity_Tag
{
  VOS_UINT16                             ueIdType; // 1st bit:imeisv; 2st bit: imei;3rd bit: imsi;4th bit:tmsi 5th bit:p_tmsi:
  VOS_UINT16                             imsiLen;
  VOS_UINT16                             imsi[15];  // 15 digits content .not include odd/even digit
  T_TmsiAndLaiReduce    tmsiAndLai;
  T_PTmsiAndRaiReduce pTmsiAndRai;
  VOS_UINT16                             imeiLen;
  VOS_UINT16                             reserved;
  VOS_UINT16                             imei[15];//// 15 digit content .
  VOS_UINT16                             rrcMode;
  VOS_UINT16                             uRnti[2];
  VOS_UINT16  reserved2;
}T_InitialUeIdentity;



//-----------------------------------------------------------------------------
typedef struct T_ResourceDesc_Tag
{
  VOS_UINT8   timeslotNumber;
  VOS_UINT8   midambleAllocationMode;
  VOS_UINT8   midambleShift;
  VOS_UINT8   midambleConfiguration;
} T_ResourceDesc;

typedef struct T_BcInfo_Tag
{
  VOS_UINT16  modulateMode;
  VOS_UINT16  midambleAllocMode;
  VOS_UINT16  midambleShift;
  VOS_UINT16  midambleConfiguration;
  VOS_UINT16  cellId;
  VOS_UINT16  channelCode[2];
  VOS_UINT16  sf[2];
  VOS_UINT16  reserved;
}T_BcInfo;

typedef struct T_CcInfo_Tag
{
  VOS_UINT16 trchNum;
  VOS_UINT16 ruSf1[maxTS_1];
  VOS_UINT16 ruSf2[maxTS_1];
  VOS_UINT16 tsNum;
  VOS_UINT16 serviceType[maxTrCH];
  VOS_UINT16 puncturingLimit;
  VOS_UINT16 modulateMode[maxTS_1];
  VOS_UINT16 dynamicSF;
  VOS_UINT16 interSecondMode;
  VOS_UINT16 allowedTfcNum;
  VOS_UINT16 tfciCode[maxTS_1];
  VOS_UINT16 ssTpcSymbols[maxTS_1];
  VOS_UINT16 reserved;
  VOS_UINT16 tfNum[maxTrCH];
  VOS_UINT16 allowedTfci[maxTFC];
  T_TransportFormat_DHI tfList[maxTrCH][maxTF];
  VOS_UINT16 ctfc[maxTFC];
  T_SemistaticTfInformation_DHI semistaticTfInformation[maxTrCH];
  VOS_UINT16 ruNum[maxTS_1];
  VOS_UINT16 minimumTfcNum;
  VOS_UINT16 minimumTfci[maxTFC];
  VOS_UINT16 additionalSsTpcSymbols[maxTS_1];
  VOS_UINT16 referenceTfcId;
  VOS_UINT16 gainFactor;
  VOS_UINT16 reserved1;
}T_CcInfo;

typedef struct T_CdInfo_Tag
{
  VOS_UINT16  ccTrchId;
  VOS_UINT16  trchNum;
  VOS_UINT16  puncturingLimit;
  VOS_UINT16  tsNum;
  VOS_UINT16  tfcNum;
  VOS_UINT16  secondInterleavingMode;
  VOS_UINT16  dwDpchOffset;
  VOS_UINT16  serviceType[maxTrCH];
  VOS_UINT16  tfciCoding[maxTS_1];
  VOS_UINT16  modulation[maxTS_1];
  VOS_UINT16  ssTpcSymbols[maxTS_1];
  VOS_UINT16  sf[maxTS_1];
  VOS_UINT16  allowedRuNum[maxTS_1];
  VOS_UINT16  ctfc[maxTFC];
  VOS_UINT16  tfNum[maxTrCH];
  T_TransportFormat_DHI  tfList[maxTrCH][maxTF];
  VOS_UINT16  additionalSsTpcSymbols[maxTS_1];
  VOS_UINT16  reserved;
  T_SemistaticTfInformation_DHI  semistaticTfInformation[maxTrCH];
}T_CdInfo;

typedef struct T_CellDescDhi_Tag
{
  VOS_UINT16  frequency;
  VOS_UINT16  cellId;
}T_CellDescDhi;

typedef struct T_DriverInfo_Tag
{
  VOS_UINT16 tsId;
  VOS_UINT16 freq;
}T_DriverInfo;

typedef struct T_DwCrl_Tag
{
  VOS_UINT16  rxTsNum;
  VOS_UINT16  blerQualityValue[maxTrCH];
  VOS_UINT16  rxRepetitionPeriod;
  VOS_UINT16  rxRepetitionLen;
  VOS_UINT16  dlcctrchOffset;
  VOS_UINT16  targetSir;
  VOS_UINT16  scellPathLoss;  //for align to TCN360_V1.10.0  gongjian  20100914
}T_DwCrl;

typedef struct T_EpuchCcInfo_Tag
{
  VOS_UINT16  qpskOr16Qam;
  VOS_UINT16  rsn;
  VOS_UINT16  tbsizeIndex;
  VOS_UINT16  prri;
  VOS_UINT16  crri;
  VOS_UINT16  trri;
  VOS_UINT16  nEucchNumInd;
  VOS_UINT16  tbSize;
}T_EpuchCcInfo;

typedef struct T_FreqBand_Tag
{
  VOS_UINT16   startPoint;
  VOS_UINT16   endPoint;
}T_FreqBand;

typedef struct T_HeaderInfo_Tag
{
  VOS_UINT32   primitiveFlag;  /*适配HPA，改为u32并提到结构体开始位置*/
  VOS_UINT16   subFrameNum;
  VOS_UINT16   workMode;
  VOS_UINT16   stateFlag;
  VOS_UINT16   spareLen;       /*20041124 acording DHI v1.1.2 2004-11-15*/
  VOS_UINT16   length;
  VOS_UINT16   reserved;       /*增加一个u16的字段进行对齐*/
} T_HeaderInfo;

typedef struct T_JdInfo_Tag
{
   VOS_UINT16  tsId;
   VOS_UINT16  freq;
   VOS_UINT16  physicalType;
   VOS_UINT16  codeNum;
   VOS_UINT16  code[16];
   VOS_UINT16  sf;
   VOS_UINT16  midambleConfiguration;
   VOS_UINT16  midambleShift;
   VOS_UINT16  midambleAllocationMode;
   VOS_UINT16  modulationMode;
   VOS_UINT16  cellId;
}T_JdInfo;

typedef struct T_HsscchInfoDhi_Tag
{
  T_JdInfo hsScchInfo;
  VOS_UINT16 blerTarget;
  VOS_UINT16 hssichTimeslotNumber;
  T_BcInfo hsSichBcInfo;
  VOS_UINT16 nackAckPowerOffset;
  VOS_UINT16 powerLevelHssich;
  VOS_UINT16 tpcStepSize;
  VOS_UINT16 reserved;
}T_HsscchInfoDhi;

typedef struct T_HsdpaInfo_Tag
{
  VOS_UINT16  uarfcnCarrier;
  VOS_UINT16  harqNumberOfProcesses;
  VOS_UINT16  harqMemorySize[maxHProcesses];
  VOS_UINT16  midambleAllocationMode;
  VOS_UINT16  midambleShift;
  VOS_UINT16  midambleConfiguration;
  VOS_UINT16  flushSoftBuffer;
  VOS_UINT16  reserved;
  VOS_UINT16  hsscchNum;
  T_HsscchInfoDhi  hsscchInfo[maxHSSCCHs];
}T_HsdpaInfo;

typedef struct T_HsMeasInfo_Tag
{
  VOS_UINT16  hsSichRtbs;
  VOS_UINT16  hsSichRmf;
  VOS_UINT16  hsSichTxPower;
  VOS_UINT16  hsPdschRscp;
  VOS_UINT16  hsPdschSir;
  VOS_UINT16  hsScchSsStep;
  VOS_UINT16  hsScchTpcStep;
  VOS_UINT16  hsScchRscp;
  VOS_UINT16  hsScchSir;
  VOS_UINT16  hsScchSirTarget;
  VOS_UINT16  hsScchMSI;
  VOS_UINT16  hsScchMissNum;
}T_HsMeasInfo;


typedef struct T_HsUpaPc_Tag
{
  VOS_UINT16  prxBaseDes;
  VOS_UINT16  beaconPlEst;
  VOS_UINT16  tpcStepSize;
  VOS_UINT16  pebasePowerControlGap;
  VOS_UINT16  upSyncStepSize;
  VOS_UINT16  upSyncFrequency;
}T_HsUpaPc;


typedef struct T_MbsfnInfoDhi_Tag
{
  VOS_UINT16  rxTsNum;
  VOS_UINT16  reserved;
  T_DriverInfo  rxDriverInfo[6];
  VOS_UINT16  mbsfnCellParaId[6];
}T_MbsfnInfoDhi;

typedef struct T_NonSchedulePhysicalInfo_Tag{
  VOS_UINT16  numEucch;
  VOS_UINT16  freq;
  VOS_UINT16  timeslotResourceRelatedInfo;
  VOS_UINT16  codeResourceInfo;
  VOS_UINT16  sfnNum;
  VOS_UINT16  repetitionPeriod;
  VOS_UINT16  repetitionLength;
  VOS_UINT16  frameOffset;
  T_DriverInfo  eHichRxDriverInfo;
  T_JdInfo  eHichJdInfo;
  VOS_UINT16  signatureSequenceGroupIndex;
  VOS_UINT16  reserved;
}T_NonSchedulePhysicalInfo;

typedef struct T_RachCcInfo_Tag
{
  VOS_UINT16  crcSize;
  VOS_UINT16  channelCodingType;
  VOS_UINT16  tbNum;
  VOS_UINT16  tbSize;
  VOS_UINT16  tti;
  VOS_UINT16  reserved;
}T_RachCcInfo;

typedef struct T_ReselectPara_Tag
{
  VOS_INT16  sOfIntra;//20090115
  VOS_INT16  sOfInter;//20090115
  VOS_UINT16  epout;
  VOS_UINT16  qhyst;
  VOS_INT16  Qrxlevmin[maxCellNum];//20090115
  VOS_INT16  maxTxPower[maxCellNum];
  VOS_INT16  qOffset1Sn[maxCellNum-1];
  VOS_UINT16  Nreselect;
  VOS_UINT16  Nerror;
  VOS_UINT16  reserved;
}T_ReselectPara;

typedef struct T_ReselectParaHcs_Tag
{
  VOS_UINT16  useOfHcs;//not use:0
  VOS_INT16  sOfSearchHCS;//20070321
  VOS_UINT16  tCRMax;
  VOS_UINT16  hcsPrio[maxCellNum];
  VOS_UINT16  qOfHCS[maxCellNum];
  VOS_UINT16  penaltyTime[maxCellNum];//not used :0
  VOS_UINT16  temporaryOffset1[maxCellNum];
  VOS_UINT16  reserved;
}T_ReselectParaHcs;

typedef struct T_SchedulePhysicalInfo_Tag{
  VOS_UINT16  rdiFlag;
  VOS_UINT16  eAgchBlerTarget;
  VOS_UINT16  tpcStepSize;
  VOS_UINT16  numEagch;
  T_DriverInfo  eAgchRxDriverInfo[maxNumEagch];
  T_JdInfo  eAgchJdInfo[maxNumEagch];
  VOS_UINT16  numEhich;
  VOS_UINT16  reserved;
  VOS_UINT16  ei[maxNumEhich];
  T_JdInfo  eHichJdInfo[maxNumEhich];
}T_SchedulePhysicalInfo;

typedef struct T_SyncUlInfo_Tag
{
  VOS_UINT16  syncUlFreq;
  VOS_UINT16  reserved;
  VOS_UINT16  syncUlCodeNum;
  VOS_UINT16  pathLoss;
  VOS_UINT16  syncUlCode[8];
  VOS_UINT16  timingAdvance;
  VOS_UINT16  powerLevel;
  VOS_UINT16  wt;
  VOS_UINT16  upPchPositionInfo;
}T_SyncUlInfo;

typedef struct T_TbDataDesc_Tag
{
  VOS_UINT16    tbNum;
  VOS_UINT16    tbSize;
}T_TbDataDesc;

typedef struct T_TsChMeas_Tag
{
  VOS_UINT16 rscp;
  VOS_UINT16 iscp;
  VOS_UINT16 sir;
  VOS_UINT16 ci;
}T_TsChMeas;

typedef struct T_TdmInfoDhi_Tag
{
  VOS_UINT16    tdmRep;
  VOS_UINT16    tdmOffset;
  VOS_UINT16    tdmLength;
  VOS_UINT16    n;
}T_TdmInfoDhi;

typedef struct T_UpCrl_Tag
{
  VOS_UINT16  txTsNum;
  VOS_UINT16  txRepetitionPeriod;
  VOS_UINT16  txRepetitionLen;
  VOS_UINT16  ulcctrchOffset;
  VOS_UINT16  maxAllowedUlTxPower;
  VOS_UINT16  powerLevel;
  VOS_UINT16  tpcStepSize;
  VOS_UINT16  ssStepSize;
  VOS_UINT16  ssFrequency;
  VOS_UINT16  ulDpchOffset;
}T_UpCrl;

typedef struct T_EpuchControlInfo_Tag
{
  VOS_UINT16  eRnti;
  VOS_UINT16  harqInfo;
  VOS_UINT16  nEhich;
  VOS_UINT16  tRucch;
  VOS_UINT16  numTs;
  VOS_UINT16  tsId[maxTS_1];
  T_BcInfo  epuchBcInfo[maxTS_1];
  VOS_UINT16  nonSchedNehich;
  VOS_UINT16  reserved1;
}T_EpuchControlInfo;

/*****************************************************************************
 结构名    : T_L1_DSDS_RF_STATE_CHANGE_IND
 协议表格  :
 ASN.1描述 :
 结构说明  : DCH态、FCH态物理层上报RF状态
*****************************************************************************/
typedef struct T_L1_DSDS_RF_STATE_CHANGE_IND_Tag
{
  T_HeaderInfo  header;
  VOS_UINT8     ucNoRF;
  VOS_UINT8     aucRev[3];
}T_L1_DSDS_RF_STATE_CHANGE_IND;

/*****************************************************************************
 枚举名    : TMAC_TPHY_DSDS_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : 指示物理层RF状态
*****************************************************************************/
enum TMAC_TPHY_DSDS_ENUM
{
    TMAC_TPHY_DSDS_RF = 0,
    TMAC_TPHY_DSDS_NO_RF = 1
};
typedef VOS_UINT8 TMAC_TPHY_DSDS_ENUM_UINT8;

typedef struct T_L1_NULL_REQ_Tag
{
  T_HeaderInfo  header;
  VOS_UINT32           sleepTime;
}T_L1_NULL_REQ;

typedef struct T_L1_PWR_SWEEP_REQ_Tag
{
  T_HeaderInfo  header;
  VOS_UINT16  sweepId;
  VOS_UINT16  syncStatus;
  VOS_UINT16  freqBandNum;
  VOS_UINT16  reserved;
  T_FreqBand  freqBand[maxFreqBand];
}T_L1_PWR_SWEEP_REQ;

typedef struct T_L1_PWR_SWEEP_CNF_Tag
{
  T_HeaderInfo  header;
  VOS_UINT16  sweepId;
  VOS_UINT16  freqPointNum;
  VOS_UINT16  freq [maxPoint];
  VOS_UINT16  dwptsRssi[maxPoint];
  VOS_UINT16  carrierRssi[maxPoint];
  VOS_UINT8  ucNoRF;
  VOS_UINT8  aucRev[3];
}T_L1_PWR_SWEEP_CNF;

typedef struct T_L1_CELL_SEARCH_REQ_Tag
{
  T_HeaderInfo  header;
  VOS_UINT16  cellSearchId;
  VOS_UINT16  syncStatus;
  VOS_UINT16  freq;
  VOS_UINT16  syncId;
  VOS_UINT16  midambleId;
  VOS_UINT16  reserved;
  VOS_UINT32  ulBarNum;          // 新增被禁小区个数
  VOS_UINT16  ausBarCellId[TDS_MAX_BAR_CELLID];   // 新增被禁小区列表
}T_L1_CELL_SEARCH_REQ;

typedef struct T_L1_CELL_SEARCH_CNF_Tag
{
  T_HeaderInfo  header;
  VOS_UINT16  cellSearchId;
  VOS_UINT16  successFlag;
  T_CellDescDhi  cellDesc;
  VOS_UINT16  blockTailFramNum;
  VOS_UINT16  activeSyncNum;
  VOS_UINT16  syncId[maxIntraCellNum];
  VOS_UINT16  rscp[maxIntraCellNum];
  VOS_UINT16  rssi;
  VOS_UINT16  dwptsRssi;
  T_TsChMeas  dwptsMeas;
  T_TsChMeas  pccpchMeas;
  VOS_UINT8  ucNoRF;
  VOS_UINT8  aucRev[3];
}T_L1_CELL_SEARCH_CNF;

typedef struct T_L1_ICS_MEAS_REQ_Tag
{
  T_HeaderInfo     header;
  VOS_UINT16  icsMeasId;
  VOS_UINT16  intraCellNum;
  VOS_UINT16  frequency;
  VOS_UINT16  cellId[maxIntraCellNum];
}T_L1_ICS_MEAS_REQ;

typedef struct T_L1_ICS_MEAS_CNF_Tag
{
  T_HeaderInfo  header;
  VOS_UINT16  icsMeasId;
  VOS_UINT16  intraCellNum;
  VOS_UINT16  rscp[maxIntraCellNum];
  VOS_UINT16  rssi[maxIntraCellNum];
}T_L1_ICS_MEAS_CNF;

typedef struct T_L1_PCCPCH_READ_REQ_Tag
{
  T_HeaderInfo  header;
  T_JdInfo  pccpchInfo;
  VOS_UINT16  pccpchBlkNum;
  VOS_UINT16  pchParaValid;
  VOS_UINT16  pagingPeriod;
  VOS_UINT16  pchSfn;
  T_JdInfo  pchInfo;
  T_CdInfo  pchCdInfo;
  VOS_UINT32  firstCellSearchFlag;
}T_L1_PCCPCH_READ_REQ;

typedef struct T_L1_PCCPCH_READ_CNF_Tag
{
  T_HeaderInfo  header;
  VOS_UINT16  crcFlag;
  VOS_UINT8   systemInfo[32];
  VOS_UINT16  rscp;
  VOS_UINT16  rssi;
  VOS_UINT16  reserved;
}T_L1_PCCPCH_READ_CNF;

#if 1
typedef struct T_L1_IDL_TASK_REQ_Tag
{
  T_HeaderInfo               header;
  VOS_UINT16  taskType;
  VOS_UINT16  pichSubFrameNum;
  T_JdInfo  pichInfo;
  VOS_UINT16  q;
  VOS_UINT16  lpi;
  VOS_UINT16  pagingPeriod;
  VOS_UINT16  pchSfn;
  T_JdInfo  pchInfo;
  T_CdInfo  pchCdInfo;
  VOS_UINT16  measId;
  VOS_UINT16  cellNum;
  T_CellDescDhi cell[maxCellNum];
  VOS_UINT16  iscp[maxCellNum];
  T_ReselectPara  zspReselectPara;
  T_InitialUeIdentity  ueIdentity;
  VOS_UINT16  sleepFlag;
  //20090928 PDM100 UMAC
  VOS_UINT16  gsmCellNum;
  VOS_UINT16  gsmCell[maxGsmCellNum];
  T_ReselectParaHcs zspReselectParaHcs;  // for align to TCN360_V1.10.0 gongjian 20100914
}T_L1_IDL_TASK_REQ;

#endif


#if 1
typedef struct T_L1_IDL_PCH_REQ_Tag
{
  T_HeaderInfo               header;
  VOS_UINT16  pichSubFrameNum;
  
  VOS_UINT16  repofPagingFlag;
  T_JdInfo  pichInfo;
  VOS_UINT16  q;
  VOS_UINT16  lpi;
  VOS_UINT16  pagingPeriod;
  VOS_UINT16  pchSfn;
  T_JdInfo  pchInfo;
  T_CdInfo  pchCdInfo;
}T_L1_IDL_PCH_REQ;

typedef struct T_L1_IDL_PCH_IND_Tag
{
  T_HeaderInfo  header;
  VOS_UINT16  pchPresent;
}T_L1_IDL_PCH_IND;

typedef struct T_L1_IDL_MEAS_REQ_Tag
{
  T_HeaderInfo        header;
  VOS_UINT16  measId;
  VOS_UINT16  cellNum;
  T_CellDescDhi cell[maxCellNum];
  VOS_UINT16  iscp[maxCellNum];
}T_L1_IDL_MEAS_REQ;

typedef struct T_L1_IDL_MEAS_IND_Tag
{
  T_HeaderInfo  header;
  VOS_UINT16  measId;
  VOS_UINT16  cellNum;
  VOS_UINT16  rscp[maxCellNum];
  VOS_INT16  validS[maxCellNum];
  VOS_INT16  cellR[maxCellNum];
  VOS_UINT16  rssi[maxCellNum];
  VOS_UINT16  sir[maxCellNum];
  VOS_UINT16  pccpchCi[maxCellNum];
  VOS_UINT16  iscp[maxCellNum][7];
  VOS_UINT16  frequency;//for reduce energe 20081210
  VOS_UINT16  cellId;
  T_DETECT_CELL_LIST_STRU    stDetectCellList;
  VOS_UINT8  ucNoRF;
  VOS_UINT8  aucRev[3];
}T_L1_IDL_MEAS_IND;

typedef struct H_T_L1_IDL_PCH_IND_Tag
{
	VOS_MSG_HEADER
	VOS_UINT32				ulMsgName;
	T_L1_IDL_PCH_IND		L1_IDL_PCH_IND;
} H_T_L1_IDL_PCH_IND;

#endif

typedef struct T_L1_PICH_READ_IND_Tag
{
  T_HeaderInfo  header;
  VOS_UINT16            pchPresent;
  VOS_UINT8            pichData[88];
}T_L1_PICH_READ_IND;

typedef struct T_L1_PRACH_SEND_REQ_Tag
{
  T_HeaderInfo        header;
  VOS_UINT16                 prachId;
  VOS_UINT16                 prachType;
  T_JdInfo  fpachInfo;
  T_DriverInfo  rachDriverInfo;
  T_SyncUlInfo  syncUlCtrlInfo;
  VOS_UINT16  prachNum;
  VOS_UINT16  powerDelta;
  VOS_UINT16  maxAllowedUlTxPower;
  VOS_UINT16  modulateMode;
  VOS_UINT16  midambleAllocMode;
  VOS_UINT16  midambleShift;
  VOS_UINT16  midambleConfiguration;
  VOS_UINT16  cellId;
  VOS_UINT16  channelCode[4];
  VOS_UINT16  sf[4];
  T_RachCcInfo  rachCcInfo;
  VOS_UINT8  data[MAX_DHI_DATA_LEN];
}T_L1_PRACH_SEND_REQ;

typedef struct T_L1_FPACH_READ_CNF_Tag
{
  T_HeaderInfo  header;
  VOS_UINT16           prachId;
  VOS_UINT16           crcFlag;
  VOS_UINT16           phInfoMess[4];
  VOS_UINT16           fpachRxPwr;
  VOS_UINT16           prachTxPwr;
  VOS_UINT16           prachTimeAdvance;
  VOS_UINT16           subSfn;
}T_L1_FPACH_READ_CNF;

typedef struct T_McchConfigInfo_Tag
{
  VOS_UINT16   accessInfoPeriod;
  VOS_UINT16   repetitionPeriod;
  VOS_UINT16   modificationperiod;
  VOS_UINT16  reserved;
}T_McchConfigInfo;

typedef struct T_L1_SCCPCH_READ_REQ_Tag
{
  T_HeaderInfo   header;
  VOS_UINT16  sccpchId;
  VOS_UINT16  reserved1;
  T_JdInfo  sccpchJdInfo;
  T_CdInfo  sccpchCdInfo;
  VOS_UINT16  sccpchRepPeriod;
  VOS_UINT16  sccpchRepLen;
  VOS_UINT16  sccpchOffset;
  VOS_UINT16  fachOccFlag;
  VOS_UINT16  crntiModMrep;
  VOS_UINT16  mrep;
  VOS_UINT16  reserved2;
  VOS_UINT16  measId;
  VOS_UINT16  measReportPeriod;
  VOS_UINT16  cellNum;
  T_CellDescDhi cell[maxCellNum];
  VOS_UINT16  iscp[maxCellNum];
  VOS_UINT16  reserved3;
  VOS_UINT16  mcchId;
  T_McchConfigInfo mcchConfiguratinoInfo;
  //20090928 PDM100 UMAC
  VOS_UINT16  gsmCellNum;
  VOS_UINT16  gsmCell[maxGsmCellNum];
  VOS_UINT16  reserved;
}T_L1_SCCPCH_READ_REQ;

typedef struct T_L1_SCCPCH_READ_IND_Tag
{
  T_HeaderInfo   header;
  VOS_UINT16  trchNum;
  VOS_UINT16  sccpchId;
  VOS_UINT16  crcFlag[maxTrCH];
  T_TbDataDesc  tbDataDesc[maxTrCH];
  VOS_UINT8  data[MAX_DHI_DATA_LEN];
  T_CellDescDhi cellDesc;
  VOS_UINT16  mcchId;
  VOS_UINT16  reserved;
}T_L1_SCCPCH_READ_IND;

typedef struct T_L1_FCH_MEAS_IND_Tag
{
  T_HeaderInfo  header;
  VOS_UINT16  measId;
  VOS_UINT16  cellNum;
  VOS_UINT16  rscp[maxCellNum];
  VOS_UINT16  rssi[maxCellNum];
  VOS_UINT16  sir[maxCellNum];
  VOS_UINT16  pccpchCi[maxCellNum];
  VOS_UINT16  iscp[maxCellNum][7];
  VOS_UINT16  tadv;
  VOS_UINT16  sfn;
  //20090928 PDM100 UMAC
  VOS_UINT16  gsmCellNum;
  VOS_UINT16  rssiGsm[maxGsmCellNum];
  VOS_UINT16  agc[maxGsmCellNum];
  VOS_UINT16  usNoRF;
  T_DETECT_CELL_LIST_STRU    stDetectCellList;
}T_L1_FCH_MEAS_IND;

/* DMO Begin */
#define    TDS_DMO_LCR_SEQ_NUM     5
enum TDS_DMO_PURP_BIT_MAP_ENUM
{
    TDS_MEAS_PURP_NULL       = 0x00,
    TDS_MEAS_PURP_INTER_FREQ = 0x01,
    TDS_MEAS_PURP_GSM_RSSI   = 0x02,
    TDS_MEAS_PURP_BSIC_IDEN  = 0x04,
    TDS_MEAS_PURP_BSIC_RECFM = 0x08,
    TDS_MEAS_PURP_EUTRA      = 0x10,
    TDS_MEAS_PURP_BUTT
};
typedef VOS_UINT8 TDS_DMO_PURP_BIT_MAP_ENUM_UINT8;
typedef struct
{
    VOS_UINT16                       usOffset;            /* 0~511 */
    VOS_UINT16                       usMeasLen;           /* 1~512 */
    VOS_UINT8                        ucK;                 /* 1~9 */
    VOS_UINT8                        ucTimeslotBitMap;    /* 透传网络配置 */
    VOS_UINT16                       usReserved;
}TDS_COMM_MEAS_OCCASION_PARA;

typedef struct
{
    VOS_UINT8                        ucPattenId;                       /* 0 ~ 4 */
    VOS_UINT8                        ucStatusFlag;                     /* 0: active   1:deact */
    TDS_DMO_PURP_BIT_MAP_ENUM_UINT8  ucMeasPurposeBitMap;
    VOS_UINT8                        ucReserved;
    TDS_COMM_MEAS_OCCASION_PARA      stMeasOccPara;
}TDS_COMM_DMO_LCR_STRU;
typedef struct
{
    VOS_UINT8                        ucValidFlag;                       /* 1:有效  0:无效 */
    VOS_UINT8                        ucReserved[3];
    TDS_COMM_DMO_LCR_STRU            astDMOLcrList[TDS_DMO_LCR_SEQ_NUM];
}TDS_COMM_DMO_LCR_SEQ_STRU;
/* DMO End */

typedef struct T_L1_DPCH_CONFIG_REQ_Tag
{
  T_HeaderInfo  header;
  VOS_UINT16  masterFreq;
  VOS_UINT16  tstdIndicator;
  VOS_UINT16  syncDiff;
  VOS_UINT16  syncNeeded;
  VOS_UINT16  n313;
  VOS_UINT16  n312;
  VOS_UINT16  n315;
  VOS_UINT16  specialBurstScheduling;
  T_DwCrl  dpchDownControl;
  T_DriverInfo  rxDriverInfo[maxTS_1];
  T_JdInfo  jdInfo[maxTS_1];
  T_CdInfo  dpchCdInfo;
  T_UpCrl  dpchUpControl;
  T_DriverInfo  txDriverInfo[maxTS_1];
  T_BcInfo  bcInfo[maxTS_1];
  T_CcInfo  dpchCcInfo;
  VOS_UINT16  pccpchTxPower;
  VOS_UINT16  reserved;
  /* DMO Begin */
  TDS_COMM_DMO_LCR_SEQ_STRU  stDMOLcrSeq;
  /* DMO End */
}T_L1_DPCH_CONFIG_REQ;

typedef struct T_L1_DPCH_SYNC_IND_Tag
{
  T_HeaderInfo  header;
  VOS_UINT16            syncFlag;
  VOS_UINT16  reserved;
}T_L1_DPCH_SYNC_IND;

typedef struct T_L1_DPCH_READ_IND_Tag
{
  T_HeaderInfo  header;
  VOS_UINT16  trchNum;
  VOS_UINT16  dataTypeIndication;
  T_TbDataDesc  tbDataDesc[maxTrCH];
  VOS_UINT32  crcFlag[maxTrCH];
  //VOS_UINT8  data[MAX_DHI_DATA_LEN];
  VOS_UINT8  data[MAX_DPCH_DATA_LEN];/*1500*/
}T_L1_DPCH_READ_IND;

typedef struct T_L1_DPCH_SEND_REQ_Tag
{
  T_HeaderInfo   header;
  VOS_UINT16  trchNum;
  VOS_UINT16  dataTypeIndication;
  T_TbDataDesc  tbDataDesc[maxTrCH];
  VOS_UINT8  data[MAX_DHI_DATA_LEN << 1];
}T_L1_DPCH_SEND_REQ;

typedef struct T_L1_HO_SYNC_SEND_REQ_Tag
{
  T_HeaderInfo    header;
  VOS_UINT16   hoId;
  VOS_UINT16   reserved;
  VOS_UINT16   masterFreq;
  VOS_UINT16   syncDiff;
  T_JdInfo  fpachInfo;
  T_SyncUlInfo  syncUlCtrlInfo;
}T_L1_HO_SYNC_SEND_REQ;

typedef struct T_L1_DCH_MEAS_REQ_Tag
{
  T_HeaderInfo    header;
  VOS_UINT16  measId;
  VOS_UINT16  reportPeriod;
  /*DETECT CELL MODIFIY BEGIN*/
  VOS_UINT16  usDetectFlag;                                                            /*Detect小区开关*/
  VOS_UINT16  usReserved;
  /*DETECT CELL MODIFIY END*/
  VOS_UINT16  cellNum;
  VOS_UINT16  intraCellNum;
  T_CellDescDhi cell[maxCellNum];
  VOS_UINT16  iscp[maxCellNum];
  VOS_UINT16  intraCell[maxIntraCellNum];
  VOS_UINT16  internalMeasFlag;
  VOS_UINT16  measTrchNum;
  VOS_UINT16  totalCrc[maxTrCH];
  VOS_UINT16  badCrc[maxTrCH];
  VOS_UINT16  pendingAfterTrigger[maxTrCH];

  VOS_UINT16  measListNoChange;  // for align to TCN360_V1.10.0
  //20090928 PDM100 UMAC

  VOS_UINT16  usLteMeasFreqNum;                                                        /* 待测LTE频点个数 */
  VOS_UINT16  usIdleIntervalK;                                                         /* 取值范围[2,3] */
  VOS_UINT16  usIdleIntervalOffset;                                                    /* 取值范围[0,7] */
  VOS_UINT16  usReserveds;

  VOS_UINT16  gsmCellNum;
  VOS_UINT16  gsmCell[maxGsmCellNum];
  TDS_COMM_DMO_LCR_SEQ_STRU  stDMOLcrSeq;
}T_L1_DCH_MEAS_REQ;

typedef struct T_L1_DCH_MEAS_CNF_Tag
{
  T_HeaderInfo   header;
  VOS_UINT16            measId;
  VOS_UINT16            usReserved;
}T_L1_DCH_MEAS_CNF;

typedef struct T_L1_DCH_MEAS_IND_Tag
{
  T_HeaderInfo  header;
  VOS_UINT16  measId;
  VOS_UINT16  measFlag;
  VOS_UINT16  reserved;
  VOS_UINT16  cellNum;
  VOS_UINT16  rscpLevel[maxCellNum];    //20100303 update DHI interface gongjian
  VOS_UINT16  rssi[maxCellNum];
  VOS_UINT16  iscp[maxCellNum][7];
  VOS_UINT16  syncDiff[maxCellNum];
  VOS_UINT16  event5aFlag;
  VOS_UINT16  measTrchNum;
  VOS_UINT16  dlTransChBler[maxTrCH];
  VOS_UINT16  dlTsSir [7];
  VOS_UINT16  dlTsRscp[7];
  VOS_UINT16  dlTsRssi[7];
  VOS_UINT16  dlTsIscp[7];
  VOS_UINT16  dlTsCi[7];
  VOS_UINT16  ulTsTxPower[7];
  VOS_UINT16  tadv;
  VOS_UINT16  sfn;
  //20090928 PDM100 UMAC
  VOS_UINT16  gsmCellNum;
  VOS_UINT16  rssiGsm[maxGsmCellNum];
  VOS_UINT16  agc[maxGsmCellNum];
  VOS_UINT16  usNoRF;
  T_DETECT_CELL_LIST_STRU    stDetectCellList;
}T_L1_DCH_MEAS_IND;

typedef struct T_L1_VCD_REQ_Tag
{
  T_HeaderInfo  header;
  VOS_UINT16           vcdCode;
}T_L1_VCD_REQ;

typedef struct T_L1_LOOP_TEST_REQ_Tag
{
  T_HeaderInfo  header;
  VOS_UINT16           cause;
  VOS_UINT16           reserved;
}T_L1_LOOP_TEST_REQ;

typedef struct T_L1_HSPDSCH_CONFIG_REQ_Tag
{
  T_HeaderInfo  header;
  VOS_UINT16  newHrnti;
  VOS_UINT16  multiCarrierNumber;
  T_HsdpaInfo  hsdpaInfo[maxTDD128Carrier];
  VOS_UINT16  physicalLayerCategory;
  VOS_UINT16  powerControlGap;
  VOS_UINT16  pathlossCompensationSwitch;
  VOS_UINT16  reserved;
}T_L1_HSPDSCH_CONFIG_REQ;

typedef struct T_L1_HSPDSCH_READ_IND_Tag
{
  T_HeaderInfo  header;
  VOS_UINT16           uarfcnCarrier;
  VOS_UINT16           crcFlag;
  VOS_UINT16           tbSize;
  VOS_UINT8            data[MAX_HS_PDU_LEN];
  VOS_UINT16           reserved;
}T_L1_HSPDSCH_READ_IND;

typedef struct T_L1_EPUCH_CONFIG_REQ_Tag
{
  T_HeaderInfo   header;
  VOS_UINT16  startFlag;
  VOS_UINT16  maxWaitTime;
  T_HsUpaPc  epuchPowerControl;
  T_EpuchControlInfo  epuchControl;
  T_NonSchedulePhysicalInfo  nonSchedulePhysicalInfo;
  T_SchedulePhysicalInfo  schedulePhysicalInfo;
}T_L1_EPUCH_CONFIG_REQ;

typedef struct T_L1_EPUCH_SEND_REQ_Tag
{
  T_HeaderInfo   header;
  T_EpuchCcInfo  epuchCcInfo;
  VOS_UINT16  referenceBetaE;
  VOS_UINT16  harqId;
  VOS_UINT16  pathLoss;
  VOS_UINT16  peBase;
  VOS_UINT16  headerSize;
  VOS_UINT8    macHeader[6];
  VOS_UINT16  dataSize;
  VOS_UINT8   data[1394];
  VOS_UINT8   siInfo[3];
  VOS_UINT8  reserved;
}T_L1_EPUCH_SEND_REQ;

typedef struct T_L1_HSUPA_INFO_IND_Tag
{
  T_HeaderInfo   header;
  VOS_UINT16  harqIndPresent;//0bit:agch;1bit:scedule hich;2bit:non scedule hich
  VOS_UINT16  prri;
  VOS_UINT16  crri;
  VOS_UINT16  trri;
  VOS_UINT16  rdi;
  VOS_UINT16  nEucchNumInd;
  VOS_UINT16  scheduleHarqId;
  VOS_UINT16  scheduleAckOrNack;
  VOS_UINT16  nonScheduleHarqId;
  VOS_UINT16  nonScheduleAckOrNack;
  VOS_UINT16  peBase;
  VOS_UINT16  reserved;
}T_L1_HSUPA_INFO_IND;

typedef struct T_L1_MCCH_READ_REQ_Tag
{
  T_HeaderInfo      header;
  VOS_UINT16  mcchId;
  VOS_UINT16  trchNum;
  VOS_UINT16  sccpchId;
  VOS_UINT16  rxTsNumber;
  VOS_UINT16  trchType[maxTrCH];
  T_DriverInfo  mbmsDriverInfo[maxTS_1];
  T_JdInfo  rxmbmsInfo[maxTS_1];
  T_CdInfo  mbmsCdInfo;
  T_McchConfigInfo mcchConfigInfo;
}T_L1_MCCH_READ_REQ;

typedef struct T_L1_MTCH_READ_REQ_Tag
{
  T_HeaderInfo   header;
  VOS_UINT16  sccpchPowerOffset;
  VOS_UINT16  rxTsNumber;
  VOS_UINT16  sccpchId;
  VOS_UINT16  tdmNum;
  T_JdInfo  rxMtchInfo[maxTS_1];
  T_CdInfo  mtchCdInfo;
  T_TdmInfoDhi  tdmInfo[MAX_TDM_NUM];
  T_MbsfnInfoDhi mbsfnInfo[MAX_TDM_NUM];
}T_L1_MTCH_READ_REQ;

typedef struct T_L1_MBMS_STOP_REQ_Tag
{
  T_HeaderInfo   header;
  VOS_UINT16             stopId;
  VOS_UINT16             mcchId;
}T_L1_MBMS_STOP_REQ;

typedef struct T_L1_CELL_MEAS_REQ_Tag
{
  T_HeaderInfo     header;
  VOS_UINT16  cellMeasId;
  VOS_UINT16  cellNum;
  T_CellDescDhi cell[maxCellNum];
  //20090928 PDM100 UMAC
  VOS_UINT16  gsmCellNum;
  VOS_UINT16  gsmCell[maxGsmCellNum];
  VOS_UINT16  reserved;
}T_L1_CELL_MEAS_REQ;

typedef struct T_L1_CELL_MEAS_CNF_Tag
{
  T_HeaderInfo  header;
  VOS_UINT16  cellMeasId;
  VOS_UINT16  cellNum;
  VOS_UINT16  rscp[maxCellNum];
  VOS_UINT16  rssi[maxCellNum];
  //20090928 PDM100 UMAC
  VOS_UINT16  gsmCellNum;
  VOS_UINT16  rssiGsm[maxGsmCellNum];
  VOS_UINT16  agc[maxGsmCellNum];
  VOS_UINT16  usNoRF;
}T_L1_CELL_MEAS_CNF;
//20100406
typedef struct  T_L1_ZSP_ABNORMAL_IND_Tag
{
  T_HeaderInfo  header;
}T_L1_ZSP_ABNORMAL_IND;

typedef struct T_L1_BSIC_REQ_Tag
{
  T_HeaderInfo   header;
  VOS_UINT16            decodeId;
  VOS_UINT16            gsmCellNum;
  VOS_UINT16            gsmCell[maxBsicNum];
  VOS_UINT16            bsicType[maxBsicNum];
  VOS_UINT16            tdSfn [maxBsicNum];
  VOS_UINT16            tdChipOffset [maxBsicNum];
  VOS_UINT32            gsmSfn[maxBsicNum];
}T_L1_BSIC_REQ;

typedef struct T_L1_BSIC_CNF_Tag
{
  T_HeaderInfo   header;
  VOS_UINT16            decodeId;
  VOS_UINT16            usReserved;
}T_L1_BSIC_CNF;

typedef struct T_L1_BSIC_IND_Tag
{
  T_HeaderInfo   header;
  VOS_UINT16            decodeId;
  VOS_UINT16            gsmCellNum;
  VOS_UINT16            gsmCell[maxBsicNum];
  VOS_UINT16            syncStatus[maxBsicNum];
  VOS_UINT16            bsic[maxBsicNum];
  VOS_UINT16            tdSfn[maxBsicNum];
  VOS_UINT16            tdChipOffset[maxBsicNum];
  VOS_UINT32            gsmSfn[maxBsicNum];
}T_L1_BSIC_IND;

typedef struct T_L1_STOP_BSIC_REQ_Tag
{
  T_HeaderInfo   header;
}T_L1_STOP_BSIC_REQ;

typedef struct T_L1_STOP_BSIC_CNF_Tag
{
  T_HeaderInfo   header;
}T_L1_STOP_BSIC_CNF;

typedef struct T_L1_PRE_SYNC_REQ_Tag
{
  T_HeaderInfo   header;
  VOS_UINT16            frequency;
  VOS_UINT16            cellId;
  // gongjian 20101123  D_PS_PDM100_UMAC_V0.6.3_003
  VOS_UINT16            switchTriBusFlag;
  VOS_UINT16  reserved;
}T_L1_PRE_SYNC_REQ;

 // gongjian 20101123  D_PS_PDM100_UMAC_V0.6.3_003
typedef struct T_L1_PRE_SYNC_CNF_Tag
{
  T_HeaderInfo   header;
}T_L1_PRE_SYNC_CNF;

typedef struct T_L1_GAP_INFO_REQ_Tag
{
  T_HeaderInfo   header;
  VOS_UINT16            lastGap;
  VOS_UINT16            offSet;
  VOS_UINT32            duration;
}T_L1_GAP_INFO_REQ;

/*****************************************************************************
 枚举名    : L1_RAT_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 系统接入类型
*****************************************************************************/
enum L1_RAT_TYPE_ENUM
{
    RAT_TYPE_LTE                              = 0,                              /* LTE */
    RAT_TYPE_GSM                                 ,                              /* GSM */
    RAT_TYPE_UTRA                                ,                              /* UTRA */
    RAT_TYPE_BUTT
};
typedef VOS_UINT16 L1_RAT_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : L1_RAT_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : G(L)->TDS测量协议状态类型
*****************************************************************************/
enum L1_RAT_STATUS_ENUM
{
    RAT_STATUS_IDLE                           = 0,
    RAT_STATUS_CONNECTED                         ,
    RAT_STATUS_BUTT
};
typedef VOS_UINT16 L1_RAT_STATUS_ENUM_UINT16;


typedef struct T_L1_IRAT_MEAS_REQ_Tag
{
  T_HeaderInfo   header;
  L1_RAT_TYPE_ENUM_UINT16            enRatType;                                 /* 当前主模 */
  L1_RAT_STATUS_ENUM_UINT16          enRatStatus;                               /* 当前主模状态 */
  VOS_UINT16            lastGap;
  VOS_UINT16            offSet;
  VOS_UINT32            duration;
  VOS_UINT16            frameSync;
  VOS_UINT16            measId;
  /* TL优化:接口需要体现高优先级 */
  VOS_UINT16            cellNum;
  VOS_UINT16            reserved;      //20100303 update DHI interface gongjian
  T_CellDescDhi  cell[maxCellNum];
}T_L1_IRAT_MEAS_REQ;

typedef struct T_L1_IRAT_MEAS_CNF_Tag
{
  T_HeaderInfo   header;
  VOS_UINT16            measId;
  VOS_UINT16            reserved;
}T_L1_IRAT_MEAS_CNF;

typedef struct T_RssiMeasRslt_Tag
{
  VOS_UINT16            usArfcn;
  VOS_INT16            sRssi;
}T_RssiMeasRslt;


typedef struct T_L1_IRAT_MEAS_IND_Tag
{
  T_HeaderInfo   header;
  VOS_UINT16            measId;
  VOS_UINT16            cellNum;
  T_CellDescDhi  cell[maxCellNum];
  VOS_UINT16            rscp[maxCellNum];
  T_RssiMeasRslt stRssiMeasRslt[maxMeasFreq];
  T_DETECT_CELL_LIST_STRU    stDetectCellList;
}T_L1_IRAT_MEAS_IND;

typedef struct T_L1_IRAT_INACTIVE_REQ_Tag
{
  T_HeaderInfo   header;
  /* TL优化:加枚举 */
  /* 0 ：保存所有参数，在下一个gap 内继续被中断的任务（仅用于驻留在GSM 模，进行TD 搜网和的TD 预定义的情况）。
     1 ：当前的任务已经被取消，不用保存和这个任务相关的任何参数。
     2 ：只用于开机，激活的是GSM 模，需要关闭ZSP 的情况。
     0x1000 : TDS从模时，使用此原因值通知TPHY释放从模测量。
  */
  VOS_UINT16            cause;
  VOS_UINT16            usResvd;
}T_L1_IRAT_INACTIVE_REQ;

typedef struct T_L1_IRAT_INACTIVE_CNF_Tag
{
  T_HeaderInfo   header;
  VOS_INT16      sTaValue;
  VOS_UINT16     usResvd;
}T_L1_IRAT_INACTIVE_CNF;

typedef struct T_L1_GAP_END_IND_Tag
{
  T_HeaderInfo   header;
}T_L1_GAP_END_IND;


typedef struct T_L1_VCD_PLAY_REQ_Tag
{
  T_HeaderInfo   header;
  VOS_UINT16             controlType;
  VOS_UINT16             toneId;
  VOS_UINT16             playTimes;
  VOS_UINT16             callState;
}T_L1_VCD_PLAY_REQ;



/*****************************************************************************
 结构名    : TMAC_TPHY_REL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC发送给phy释放请求，phy收到后按照不同的释放需求进行相应操作
  T2G/L 异系统间切换时，在通知TPHY进入RAT态前，下发此原因携带原因值默认为0x06，释放GL测量信息
*****************************************************************************/
typedef struct TMAC_TPHY_REL_REQ_Tag
{
  T_HeaderInfo                  header;
  VOS_UINT16                           usRelCause;
  VOS_UINT16                           usReserved;
} TMAC_TPHY_REL_REQ_STRU;
/*****************************************************************************
 结构名    : TMAC_TPHY_BSIC_FRAME_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct TMAC_TPHY_BSIC_FRAME_IND_Tag
{
  T_HeaderInfo                         header;
  VOS_UINT8                           ucFrameLength;               /* 接口增加偷帧长度: 单位ms*/
  VOS_UINT8                           ucResv[3];
} TMAC_TPHY_BSIC_FRAME_IND_STRU;


/*****************************************************************************
 结构名    : TMAC_TPHY_REL_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TMAC_TPHY_REL_REQ_STRU 回复消息
*****************************************************************************/
typedef struct TMAC_TPHY_REL_CNF_Tag
{
  T_HeaderInfo                  header;
  TDS_RESULT_ENUM_UINT16        usRslt;//0 succ, 1 fail
  VOS_UINT16                           usReserved;
} TMAC_TPHY_REL_CNF_STRU;


/*****************************************************************************
 结构名    : TMAC_TPHY_IRAT_MEAS_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TDS主模非DCH态下，使用此原语将GL测量频点通知TDSP。若G/L频点个数为0，表示释放。
*****************************************************************************/
typedef struct TMAC_TPHY_IRAT_MEAS_REQ_Tag
{
  T_HeaderInfo       header;
  VOS_UINT16                usOpId;
  VOS_UINT16                reserved;
  VOS_UINT16                usLteMeasFreqNum;
  VOS_UINT16                usGsmMeasFreqNum;
} TMAC_TPHY_IRAT_MEAS_REQ_STRU;

/*****************************************************************************
 结构名    : TMAC_TPHY_IRAT_MEAS_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TMAC_TPHY_IRAT_MEAS_REQ_STRU的回复结构
*****************************************************************************/
typedef struct TMAC_TPHY_IRAT_MEAS_CNF_Tag
{
  T_HeaderInfo       header;
  VOS_UINT16                usOpId;
  VOS_UINT16                reserved;
} TMAC_TPHY_IRAT_MEAS_CNF_STRU;


//the structure are moved from hl1_mac.het -----begin  20100805  ylm
//-----------------------------------------------------------------------------
//
typedef struct T_DhiReqHead_Tag
{
  VOS_UINT16    scheduleFn;
  VOS_UINT16    sendFn;
} T_DhiReqHead;

//-----------------------------------------------------------------------------
typedef union T_DhiReqMsg_Tag
{
  T_L1_NULL_REQ           L1_NULL_REQ;
  T_L1_CELL_MEAS_REQ      L1_CELL_MEAS_REQ;
  T_L1_PCCPCH_READ_REQ    L1_PCCPCH_READ_REQ;
  T_L1_IDL_MEAS_REQ       L1_IDL_MEAS_REQ;
  T_L1_IDL_PCH_REQ        L1_IDL_PCH_REQ;
  T_L1_PRACH_SEND_REQ     L1_PRACH_SEND_REQ;
  T_L1_SCCPCH_READ_REQ    L1_SCCPCH_READ_REQ;
  T_L1_DPCH_CONFIG_REQ    L1_DPCH_CONFIG_REQ;
  T_L1_DPCH_SEND_REQ      L1_DPCH_SEND_REQ;
  T_L1_EPUCH_CONFIG_REQ   L1_EPUCH_CONFIG_REQ;
  T_L1_EPUCH_SEND_REQ     L1_EPUCH_SEND_REQ;
  T_L1_DCH_MEAS_REQ       L1_DCH_MEAS_REQ;
  T_L1_HO_SYNC_SEND_REQ   L1_HO_SYNC_SEND_REQ;
  T_L1_PWR_SWEEP_REQ      L1_PWR_SWEEP_REQ;
  T_L1_CELL_SEARCH_REQ    L1_CELL_SEARCH_REQ;
  T_L1_LOOP_TEST_REQ      L1_LOOP_TEST_REQ;
  T_L1_IDL_TASK_REQ       L1_IDL_TASK_REQ;
  T_L1_MCCH_READ_REQ      L1_MCCH_READ_REQ;
  T_L1_MTCH_READ_REQ      L1_MTCH_READ_REQ;
  T_L1_MBMS_STOP_REQ      L1_MBMS_STOP_REQ;
  T_L1_HSPDSCH_CONFIG_REQ L1_HSPDSCH_CONFIG_REQ;

  //20090928 PDM100 UMAC
  T_L1_BSIC_REQ           L1_BSIC_REQ;
  T_L1_STOP_BSIC_REQ      L1_STOP_BSIC_REQ;
  T_L1_PRE_SYNC_REQ       L1_PRE_SYNC_REQ;
  T_L1_GAP_INFO_REQ       L1_GAP_INFO_REQ;
  T_L1_IRAT_MEAS_REQ      L1_IRAT_MEAS_REQ;
  T_L1_IRAT_INACTIVE_REQ  L1_IRAT_INACTIVE_REQ;

  /* TRRC CHANGE FOR RESEL begin */
  TMAC_TPHY_IRAT_MEAS_REQ_STRU TMAC_TPHY_IRAT_MEAS_REQ;
  TMAC_TPHY_REL_REQ_STRU TMAC_TPHY_REL_REQ;
  /* TRRC CHANGE FOR RESEL end */

  TMAC_TPHY_BSIC_FRAME_IND_STRU TMAC_TPHY_BSIC_FRAME_IND;

} T_DhiReqMsg;

//-----------------------------------------------------------------------------
// for MAC
typedef struct H_T_DhiReqMsg_Tag
{
  T_DhiReqHead  signalHeader;
  VOS_UINT32            msgSelect;
//VOS_UINT8            reserved;
//  VOS_UINT16           reserved1;
  T_DhiReqMsg   reqMsg;
} H_T_DhiReqMsg;

typedef struct
{
    VOS_MSG_HEADER
    T_DhiReqMsg   reqMsg;
} TDS_L2_HPA_MSG_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgId;
    VOS_UINT32              ulDspLoadFlag;//1-ICS,2-ACC,3-DCH,4-IDL,5-IRAT
} TL2_TPHY_STATE_CHANGE_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                           ulMsgId;
    VOS_UINT32                           ulRslt;         /*状态迁移结果*/
}TL2_TPHY_STATE_CHANGE_CNF_STRU;

typedef enum TRRC_TPHY_WORK_MODE_CFG_RESULT
{
    TRRC_TPHY_WORK_MODE_CFG_SUCC = 0,
    TRRC_TPHY_WORK_MODE_CFG_FAIL,
}TRRC_TPHY_WORK_MODE_CFG_RESULT_ENUM;



// for DSP
typedef struct H_T_MCU_CMD_Tag
{
  T_DhiReqHead      signalHeader;
  VOS_UINT32        msgSelect;
  VOS_UINT16        reqMsg[MAX_DHI_LEN];
} H_T_MCU_CMD;
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------

typedef struct H_T_L1_CELL_MEAS_CNF_Tag
{
  /* 20111102 l38432 MsgBlock_TDS Rel begin */
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;

    // T_MsgHeader            signalHeader;
    /* 20111102 l38432 MsgBlock_TDS Rel end */
  T_L1_CELL_MEAS_CNF  L1_CELL_MEAS_CNF;
} H_T_L1_CELL_MEAS_CNF;

//-----------------------------------------------------------------------------

typedef struct H_T_L1_PCCPCH_READ_CNF_Tag
{
  /* 20111102 l38432 MsgBlock_TDS Rel begin */
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;

    // T_MsgHeader            signalHeader;
    /* 20111102 l38432 MsgBlock_TDS Rel end */
  T_L1_PCCPCH_READ_CNF    L1_PCCPCH_READ_CNF;
} H_T_L1_PCCPCH_READ_CNF;

typedef struct H_T_L1_IDL_MEAS_IND_Tag
{
  /* 20111102 l38432 MsgBlock_TDS Rel begin */
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;

    // T_MsgHeader            signalHeader;
    /* 20111102 l38432 MsgBlock_TDS Rel end */
  T_L1_IDL_MEAS_IND  L1_IDL_MEAS_IND;
} H_T_L1_IDL_MEAS_IND;

//-----------------------------------------------------------------------------
typedef struct H_T_L1_FPACH_READ_CNF_Tag
{
  /* 20111102 l38432 MsgBlock_TDS Rel begin */
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;

    // T_MsgHeader            signalHeader;
    /* 20111102 l38432 MsgBlock_TDS Rel end */
  T_L1_FPACH_READ_CNF     L1_FPACH_READ_CNF;
} H_T_L1_FPACH_READ_CNF;

//-----------------------------------------------------------------------------
//20100803  ylm
/*typedef struct H_T_L1_PICH_READ_IND_Tag
{
  T_MsgHeader             signalHeader;
  T_L1_PICH_READ_IND      L1_PICH_READ_IND;
} H_T_L1_PICH_READ_IND;*/
//-----------------------------------------------------------------------------
typedef struct H_T_L1_SCCPCH_READ_IND_Tag
{
  /* 20111102 l38432 MsgBlock_TDS Rel begin */
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;

    // T_MsgHeader            signalHeader;
    /* 20111102 l38432 MsgBlock_TDS Rel end */
  T_L1_SCCPCH_READ_IND    L1_SCCPCH_READ_IND;
} H_T_L1_SCCPCH_READ_IND;
//-----------------------------------------------------------------------------
typedef struct H_T_L1_HSUPA_INFO_IND_Tag
{
  /* 20111102 l38432 MsgBlock_TDS Rel begin */
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;

    // T_MsgHeader            signalHeader;
    /* 20111102 l38432 MsgBlock_TDS Rel end */
  T_L1_HSUPA_INFO_IND   L1_HSUPA_INFO_IND;
} H_T_L1_HSUPA_INFO_IND;

//-----------------------------------------------------------------------------
typedef struct H_T_L1_DPCH_READ_IND_Tag
{
  /* 20111102 l38432 MsgBlock_TDS Rel begin */
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;

    // T_MsgHeader            signalHeader;
    /* 20111102 l38432 MsgBlock_TDS Rel end */
  T_L1_DPCH_READ_IND      L1_DPCH_READ_IND;
} H_T_L1_DPCH_READ_IND;
//-----------------------------------------------------------------------------

typedef struct H_T_L1_DPCH_SYNC_IND_Tag
{
  /* 20111102 l38432 MsgBlock_TDS Rel begin */
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;

    // T_MsgHeader            signalHeader;
    /* 20111102 l38432 MsgBlock_TDS Rel end */
  T_L1_DPCH_SYNC_IND      L1_DPCH_SYNC_IND;
} H_T_L1_DPCH_SYNC_IND;

//-----------------------------------------------------------------------------

typedef struct H_T_L1_DCH_MEAS_IND_Tag
{
  /* 20111102 l38432 MsgBlock_TDS Rel begin */
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;

    // T_MsgHeader            signalHeader;
    /* 20111102 l38432 MsgBlock_TDS Rel end */
  T_L1_DCH_MEAS_IND       L1_DCH_MEAS_IND;
} H_T_L1_DCH_MEAS_IND;

//-----------------------------------------------------------------------------

typedef struct H_T_L1_PWR_SWEEP_CNF_Tag
{
  /* 20111102 l38432 MsgBlock_TDS Rel begin */
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;

    // T_MsgHeader            signalHeader;
    /* 20111102 l38432 MsgBlock_TDS Rel end */
  T_L1_PWR_SWEEP_CNF      L1_PWR_SWEEP_CNF;
} H_T_L1_PWR_SWEEP_CNF;
//-----------------------------------------------------------------------------

typedef struct H_T_L1_CELL_SEARCH_CNF_Tag
{
  /* 20111102 l38432 MsgBlock_TDS Rel begin */
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;

    // T_MsgHeader            signalHeader;
    /* 20111102 l38432 MsgBlock_TDS Rel end */
  T_L1_CELL_SEARCH_CNF    L1_CELL_SEARCH_CNF;
} H_T_L1_CELL_SEARCH_CNF;
//-----------------------------------------------------------------------------
//20060305
typedef struct H_T_L1_FCH_MEAS_IND_Tag
{
  /* 20111102 l38432 MsgBlock_TDS Rel begin */
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;

    // T_MsgHeader            signalHeader;
    /* 20111102 l38432 MsgBlock_TDS Rel end */
  T_L1_FCH_MEAS_IND       L1_FCH_MEAS_IND;
} H_T_L1_FCH_MEAS_IND;

//-----------------------------------------------------------------------------
//20070129
typedef struct H_T_L1_HSPDSCH_READ_IND_Tag
{
  /* 20111102 l38432 MsgBlock_TDS Rel begin */
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;

    // T_MsgHeader            signalHeader;
    /* 20111102 l38432 MsgBlock_TDS Rel end */
  T_L1_HSPDSCH_READ_IND   L1_HSPDSCH_READ_IND;
} H_T_L1_HSPDSCH_READ_IND;

typedef struct H_T_HL1_SCHEDULE_IND_Tag
{
  /* 20111102 l38432 MsgBlock_TDS Rel begin */
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;

    // T_MsgHeader            signalHeader;
    /* 20111102 l38432 MsgBlock_TDS Rel end */
} H_T_HL1_SCHEDULE_IND;


//20090928 PDM100 UMAC

typedef struct H_T_L1_BSIC_IND_Tag
{
  /* 20111102 l38432 MsgBlock_TDS Rel begin */
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;

    // T_MsgHeader            signalHeader;
    /* 20111102 l38432 MsgBlock_TDS Rel end */
  T_L1_BSIC_IND           L1_BSIC_IND;
} H_T_L1_BSIC_IND;

typedef struct H_T_L1_STOP_BSIC_CNF_Tag
{
  /* 20111102 l38432 MsgBlock_TDS Rel begin */
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;

    // T_MsgHeader            signalHeader;
    /* 20111102 l38432 MsgBlock_TDS Rel end */
  T_L1_STOP_BSIC_CNF      L1_STOP_BSIC_CNF;
} H_T_L1_STOP_BSIC_CNF;

typedef struct H_T_L1_IRAT_MEAS_IND_Tag
{
  /* 20111102 l38432 MsgBlock_TDS Rel begin */
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;

    // T_MsgHeader            signalHeader;
    /* 20111102 l38432 MsgBlock_TDS Rel end */
  T_L1_IRAT_MEAS_IND      L1_IRAT_MEAS_IND;
} H_T_L1_IRAT_MEAS_IND;

typedef struct H_T_L1_IRAT_INACTIVE_CNF_Tag
{
  /* 20111102 l38432 MsgBlock_TDS Rel begin */
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;

    // T_MsgHeader            signalHeader;
    /* 20111102 l38432 MsgBlock_TDS Rel end */
  T_L1_IRAT_INACTIVE_CNF  L1_IRAT_INACTIVE_CNF;
} H_T_L1_IRAT_INACTIVE_CNF;

typedef struct H_T_L1_GAP_END_IND_Tag
{
  /* 20111102 l38432 MsgBlock_TDS Rel begin */
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;

    // T_MsgHeader            signalHeader;
    /* 20111102 l38432 MsgBlock_TDS Rel end */
  T_L1_GAP_END_IND        L1_GAP_END_IND;
} H_T_L1_GAP_END_IND;

typedef struct T_VB_SYNC_PARA_Tag
{
  VOS_UINT16 scheduleFn;
  VOS_UINT8  optype;
}T_VB_SYNC_PARA;

// gongjian 20101123  D_PS_PDM100_UMAC_V0.6.3_003
typedef struct H_T_L1_PRE_SYNC_CNF_Tag
{
  /* 20111102 l38432 MsgBlock_TDS Rel begin */
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;

    // T_MsgHeader            signalHeader;
    /* 20111102 l38432 MsgBlock_TDS Rel end */
  T_L1_PRE_SYNC_CNF       L1_PRE_SYNC_CNF;
} H_T_L1_PRE_SYNC_CNF;

/* LT RESEL BEGIN */
typedef struct H_T_L1_IRAT_MEAS_CNF_Tag
{
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;

    T_L1_IRAT_MEAS_CNF       L1_IRAT_MEAS_CNF;
} H_T_L1_IRAT_MEAS_CNF;


typedef struct H_T_TMAC_TPHY_IRAT_MEAS_CNF_Tag
{
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;

    TMAC_TPHY_IRAT_MEAS_CNF_STRU       L1_TMAC_TPHY_IRAT_MEAS_CNF;
} H_T_TMAC_TPHY_IRAT_MEAS_CNF;
/* LT RESEL END */

typedef struct H_T_TMAC_TPHY_REL_CNF_Tag
{
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;

    TMAC_TPHY_REL_CNF_STRU       TMAC_TPHY_REL_CNF;
} H_T_TMAC_TPHY_REL_CNF;



//the structure are moved from hl1_mac.het -----end  20100805  ylm

typedef struct H_T_L1_ZSP_ABNORMAL_IND_Tag
{
  /* 20111102 l38432 MsgBlock_TDS Rel begin */
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;

    // T_MsgHeader            signalHeader;
    /* 20111102 l38432 MsgBlock_TDS Rel end */
  T_L1_ZSP_ABNORMAL_IND   L1_ZSP_ABNORMAL_IND;
} H_T_L1_ZSP_ABNORMAL_IND;

/* 增加动态LoadDsp上报功能 */
/*****************************************************************************
 枚举名    : TDS_DHI_STATE_ENUM
 结构说明  : 标识DHI对应的状态
 MAC_L1 State: 0--NULL   1--SEL   2--IDL 3--ACC 4-- FCH  5--DCH   6--SLP 7-- IRAT
*****************************************************************************/
enum TDS_DHI_STATE_ENUM
{
    TDS_DHI_STATE_NULL,
    TDS_DHI_STATE_SEL,
    TDS_DHI_STATE_IDL,
    TDS_DHI_STATE_ACC,
    TDS_DHI_STATE_FCH,
    TDS_DHI_STATE_DCH,
    TDS_DHI_STATE_SLP,
    TDS_DHI_STATE_IRAT,
    TDS_DHI_STATE_BUTT
};
typedef VOS_UINT8 TDS_DHI_STATE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TDS_LOAD_DSP_STATE_ENUM
 结构说明  : 标识DHI对应的状态
 DSP  Dynamic load module:1-ICS  2-ACC  3-DCH 4-IDL 5-IRAT
*****************************************************************************/
enum TDS_LOAD_DSP_STATE_ENUM
{
    TDS_LOAD_DSP_STATE_NULL,
    TDS_LOAD_DSP_STATE_ICS,
    TDS_LOAD_DSP_STATE_ACC,
    TDS_LOAD_DSP_STATE_DCH,
    TDS_LOAD_DSP_STATE_IDL,
    TDS_LOAD_DSP_STATE_IRAT,
    TDS_LOAD_DSP_STATE_BUTT
};
typedef VOS_UINT8 TDS_LOAD_DSP_STATE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : T_L1_DYNA_LOAD_DSP_IND_Tag
 结构说明  : 上报参数动态LoadDsp的各个参数
*****************************************************************************/
typedef struct T_L1_DYNA_LOAD_DSP_IND_Tag
{
    TDS_DHI_STATE_ENUM_UINT8      enDhiState;
    TDS_DHI_STATE_ENUM_UINT8      enNextDhiState;
    TDS_LOAD_DSP_STATE_ENUM_UINT8 enLoadDspModule;
    VOS_UINT8                     ucRcv;
}T_L1_DYNA_LOAD_DSP_IND;

/*****************************************************************************
 枚举名    : H_T_L1_DYNA_LOAD_DSP_IND_Tag
 结构说明  :
*****************************************************************************/
typedef struct H_T_L1_DYNA_LOAD_DSP_IND_Tag
{
    VOS_MSG_HEADER
    VOS_UINT32                    ulMsgName;

    T_L1_DYNA_LOAD_DSP_IND        stDynamicLoadDspInd;
} H_T_L1_DYNA_LOAD_DSP_IND;

typedef struct H_T_L1_DCH_MEAS_CNF_Tag
{
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;

    T_L1_DCH_MEAS_CNF       stL1DchMeasCnf;
} H_T_L1_DCH_MEAS_CNF;

#define TRRC_TPHY_WORK_MODE_TYPE_ENUM_UINT16 VOS_UINT16


enum TRRC_TPHY_WORK_MODE_ENUM
{
    TRRC_TPHY_WORK_MODE_TYPE_ACTIVE                = 0,     /* TDS 处于主模*/
    TRRC_TPHY_WORK_MODE_TYPE_INACTIVE              = 1,     /* TDS 处于从模*/
    TRRC_TPHY_WORK_MODE_TYPE_BUTT
};

enum TRRC_TPHY_SET_WORK_MODE_REASON_ENUM
{
    TRRC_TPHY_SET_WORK_MODE_REASON_POWEROFF              = 1,                   /* 关机引起 */
    TRRC_TPHY_SET_WORK_MODE_REASON_IRAT                  = 2,   /* 互操作添加*/
    TRRC_TPHY_SET_WORK_MODE_REASON_BUTT
};
typedef VOS_UINT16 TRRC_TPHY_SET_WORK_MODE_REASON_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_DSDS_RFSHARED_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :DSDS特性新增，RF shared是否使能
*****************************************************************************/
enum TRRC_TPHY_DSDS_RFSHARED_ENUM
{
    TRRC_TPHY_DSDS_RFSHARED_DISABLE           = 0,    /* 不启动 */
    TRRC_TPHY_DSDS_RFSHARED_ENABLE            = 1,    /* 启动 */
    TRRC_TPHY_DSDS_RFSHARED_BUTT
};
typedef VOS_UINT16  TRRC_TPHY_DSDS_RFSHARED_ENUM_UINT16;

/*****************************************************************************
 枚举名    : TRRC_TPHY_SET_WORK_MODE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                     /*_H2ASN_Skip*/
    VOS_UINT32                                  enMsgId;               /*_H2ASN_Skip*/
    VOS_UINT16                                  usOpId;
    TRRC_TPHY_WORK_MODE_TYPE_ENUM_UINT16        enWorkModeType;        /* 指示TDS工作模式 */
    TRRC_TPHY_SET_WORK_MODE_REASON_ENUM_UINT16  enSetWorkModeReason;   /*切模原因*/
    TRRC_TPHY_DSDS_RFSHARED_ENUM_UINT16         enDsdsRfShardFlg;
}TRRC_TPHY_SET_WORK_MODE_REQ_STRU;

enum TRRC_TPHY_RESULT_ENUM
{
    TRRC_TPHY_RESULT_SUCC                 = 0,                /* 成功 */
    TRRC_TPHY_RESULT_FAIL ,                                   /* 失败 */
    TRRC_TPHY_RESULT_FAIL_MASTER_TO_MASTER ,               /*失败原因：主模切主模  */
    TRRC_TPHY_RESULT_FAIL_TWO_MASTER,                      /* 失败原因：TL都为主模 */
    TRRC_TPHY_RESULT_BUTT
};
typedef VOS_UINT16    TRRC_TPHY_RESULT_ENUM_UINT16;
#if 1
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    VOS_UINT32                                enMsgId;          /*_H2ASN_Skip*/
    VOS_UINT16                                usOpId;
    TRRC_TPHY_RESULT_ENUM_UINT16              enWorkModeCfgRslt;
}TRRC_TPHY_SET_WORK_MODE_CNF_STRU;
#endif

/*****************************************************************************
 枚举名    : TRRC_TPHY_NOTCH_STATE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :  通知物理层启动NOTCH通道指示
*****************************************************************************/

enum TRRC_TPHY_NOTCH_STATE_ENUM
{
    TRRC_TPHY_NOTCH_OPEN_FLAG_FALSE          = 0,    /* 不启动 */
    TRRC_TPHY_NOTCH_OPEN_FLAG_TRUE           = 1,    /* 启动 */
    TRRC_TPHY_NOTCH_OPEN_FLAG_BUTT
};
typedef VOS_UINT16  TRRC_TPHY_NOTCH_STATE_ENUM_UINT16;

/*****************************************************************************
 结构名    : TRRC_TPHY_NOTCH_BYPASS_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC透传MTC NOTCH BYPASS 启动消息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                              enMsgId;        /*_H2ASN_Skip*/
    VOS_UINT16                              usOpId;         /* 操作标识 */
    TRRC_TPHY_NOTCH_STATE_ENUM_UINT16       enStartFlag;    /* 启动标识 */
}TRRC_TPHY_NOTCH_REQ_STRU;



typedef struct
{
	VOS_UINT16 usModuFormat;//调制方式0 --QPSK    1--16QAM
	VOS_UINT16 usTbiOut;//TB索引,相应TBSIZE大小25321-970， 9.2.3.3.1-9.2.3.3.6*/
}TDS_ERRLOG_CQI_INFO_STRU;

typedef struct
{
	VOS_INT16 sSinrDB;//DPCH  sir
	VOS_UINT16 usRev;
}TDS_ERRLOG_SINR_INFO_STRU;

typedef struct
{
	VOS_INT16 sDpchPwr;
	VOS_INT16 sEpuchPwr;
}TDS_ERRLOG_UL_POWER_STRU;

typedef struct
{
    T_HeaderInfo  header;
    VOS_UINT16                                usOpId;
    VOS_UINT16                                usRev;
    TDS_ERRLOG_CQI_INFO_STRU                  stCqiInfo;
    TDS_ERRLOG_SINR_INFO_STRU                 stSinrInfo;
    TDS_ERRLOG_UL_POWER_STRU                  stUlPwrInfo;
}T_TRRC_TPHY_ERRLOG_INFO_IND_STRU;
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    VOS_UINT32                                enMsgId;          /*_H2ASN_Skip*/
    T_TRRC_TPHY_ERRLOG_INFO_IND_STRU          stErrLogInfo;
}TRRC_TPHY_ERRLOG_INFO_IND_STRU;


/*****************************************************************************
 结构名    : TRRC_TPHY_NV_ITEM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 需要存储的NV结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16          usNvId;
    VOS_UINT16        usNvItemLength;    /* 请求写入NV数据长度*/
    VOS_UINT32        ulNvItemAddress;        /* 待写入NV TCM地址*/
} TRRC_TPHY_NV_ITEM_STRU;

/*****************************************************************************
 结构名    : TRRC_TPHY_NV_WRITE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DSP请求RRC存储NV消息结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TPS_TPHY_MSG_ID_ENUM_UINT32        enMsgId;
    VOS_UINT16                         usOpId;
    VOS_UINT16                         usNvItemNum;
    TRRC_TPHY_NV_ITEM_STRU             astNvItems[TRRC_TPHY_MAX_NV_WRITE_NUM];
} TRRC_TPHY_NV_WRITE_IND_STRU;

/*****************************************************************************
 结构名    : TRRC_TPHY_NV_WRITE_RSP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC完成NV存储后回复DSP消息结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TPS_TPHY_MSG_ID_ENUM_UINT32           enMsgId;
    VOS_UINT16                            usOpId;
    TRRC_TPHY_RESULT_ENUM_UINT16          enResult;
} TRRC_TPHY_NV_WRITE_RSP_STRU;


enum TRRC_TPHY_SWITCH_IND_TYPE_ENUM
{
    TRRC_TPHY_ANTEN_SWITCH_MSG_TYPE       = 0,
    TRRC_TPHY_SAR_REDUCTION_PRI_MSG_TYPE
};
typedef VOS_UINT16 TRRC_TPHY_SWITCH_IND_TYPE_ENUM_UNIT16;

/*****************************************************************************
 结构名    : TRRC_TPHY_SWITCH_IND_STRU
 协议表格  : rrc和Phy之间的接口 ,天线状态.ucSARSwitch: 0表示无线，1表示有线
 ASN.1描述 :
 结构说明  : TRRC_TPHY_SWITCH_IND_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TPS_TPHY_MSG_ID_ENUM_UINT32                         enMsgId;                /*_H2ASN_Skip*/
    TRRC_TPHY_SWITCH_IND_TYPE_ENUM_UNIT16               ulMsgType;
    VOS_UINT16                                          usSarReductionPri;      /*功率回退等级*/
    VOS_UINT8                                           ucAntenSwitch;          /*天线状态*/
    VOS_UINT8                                           ucRev[3];
}TRRC_TPHY_SWITCH_IND_STRU;


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

#endif /* end of TPsTPhyInterface.h */
