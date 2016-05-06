#ifndef __TDS_oM_equip_def____H_
#define __TDS_oM_equip_def____H_

#include "type_define.h"
#include "om_base_def.h"
#ifdef MS_VC6_PLATFORM
#include "balong_tds_dsp.h"
#endif

#if 0
// DSP CT 命令范围[0x00010000,0x00010F00)
// CT命令定义必须为：(0x00010000=<DSP CMDID<0x00010F00)


//^FCALIIP2S IDs
#define OM_PHY_CT_F_CALIIP2_SET_REQ (0x10220)
#define PHY_OM_CT_F_CALIIP2_SET_CNF (0x10220)
#define PHY_OM_CT_F_CALIIP2_IND (0x10221)

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
#define OM_PHY_CT_F_BBATT_SET_REQ (0x10270)
#define PHY_OM_CT_F_BBATT_SET_CNF (0x10270)


#define OM_PHY_CT_TEST_MODE_REQ                      0X10000
#define PHY_OM_CT_TEST_MODE_CNF                      0X10000
#define OM_PHY_CT_TXON_REQ                           0X10020
#define PHY_OM_CT_TXON_CNF                           0X10020
#define OM_PHY_CT_FREQ_SET_REQ                       0X10040
#define PHY_OM_CT_FREQ_SET_CNF                       0X10040
#define OM_PHY_CT_TXPOW_SET_REQ                      0X10060
#define PHY_OM_CT_TXPOW_SET_CNF                      0X10060
#define OM_PHY_CT_VCTCXO_SET_REQ                     0X10080
#define PHY_OM_CT_VCTCXO_SET_CNF                     0X10080
#define OM_PHY_CT_RXON_REQ                           0X100A0
#define PHY_OM_CT_RXON_CNF                           0X100A0
#define OM_PHY_CT_RXANT_SET_REQ                      0X100C0
#define PHY_OM_CT_RXANT_SET_CNF                      0X100C0
#define OM_PHY_CT_AAGC_SET_REQ                       0X100E0
#define PHY_OM_CT_AAGC_SET_CNF                       0X100E0
#define OM_PHY_CT_MEAS_RSSI_REQ                      0X10100
#define PHY_OM_CT_MEAS_RSSI_CNF                      0X10100
#define PHY_OM_CT_RSSI_IND                           0X10110
#define OM_PHY_CT_VOLTAGE_REQ                        0X10111
#define PHY_OM_CT_VOLTAGE_CNF                        0X10111

#define PHY_OM_FAGC_CNF                              0X10112
#define OM_PHY_FAGC_REQ                              0X10112

#define OM_PHY_CT_TSELRF_SET_REQ                     0x10115
#define PHY_OM_CT_TSELRF_SET_CNF                     0x10115


#define OM_PHY_CT_FWAVE_SET_REQ                     0x10116
#define PHY_OM_CT_FWAVE_SET_CNF                     0x10116


#define OM_PHY_CT_F_FREQ_SET_REQ         (0x10120)
#define PHY_OM_CT_F_FREQ_SET_CNF         (0x10120)

#define OM_PHY_CT_F_TXPOW_SET_REQ        (0X10130)
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

#define OM_PHY_CT_F_BLK_REQ               (0x101c0)
#define PHY_OM_CT_F_BLK_CNF               (0x101c0)

#define OM_PHY_CT_F_IP2START_REQ          (0x101d0)
#define PHY_OM_CT_F_IP2START_CNF          (0x101d0)

#define PHY_OM_CT_F_IP2_IND               (0x101e0)

#define OM_PHY_CT_F_MAX_POWER_SET_REQ           (0X101f0)
#define PHY_OM_CT_F_MAX_POWER_SET_CNF           (0X101f0)

#define OM_PHY_CT_F_PA_POWER_SET_REQ           (0X101f4)
#define PHY_OM_CT_F_PA_POWER_SET_CNF           (0X101f4)

#define OM_PHY_CT_F_BANDSW_SET_REQ           (0X101f5)
#define PHY_OM_CT_F_BANDSW_SET_CNF           (0X101f5)
#define OM_PHY_CT_F_FDMS_REQ                 (0X101f6)
#define PHY_OM_CT_F_FDMS_CNF                 (0X101f6)

#define  OM_PHY_BT_FPOW_SET_REQ      (0x10214)
#define  PHY_OM_BT_FPOW_SET_CNF      (0x10214)

//^SRXSUBFRA非信令综测接收测试的子帧数量
#define MSP_PHY_NCIT_RXSUBFRA_SET_REQ         (0x10215)
#define PHY_MSP_NCIT_RXSUBFRA_SET_CNF         (0x10215)


// ^SSTART 非信令综测启动接收统计
#define MSP_PHY_NCIT_START_SET_REQ            (0x1020C)
#define PHY_MSP_NCIT_START_SET_CNF            (0x1020C)

// ^SSTOP 非信令综测停止接收统计
#define MSP_PHY_NCIT_STOP_SET_REQ             (0x1020E)
#define PHY_MSP_NCIT_STOP_SET_CNF             (0x1020E)
#endif

#define PHY_MSP_NCIT_RX_BER_REQ                (0x10218)
#define PHY_MSP_NCIT_RX_BER_IND                (0x10218)




typedef enum TDS_BT_OM_REQ_MSGID
{
    TPHY_REQ_BT_FIX_POWER = OM_TCMD_ID(TPHY_BT_MID, OM_TYPE_REQ, 0x1),
    TPHY_REQ_BT_COMP_SWITCH = OM_TCMD_ID(TPHY_BT_MID, OM_TYPE_REQ, 0x2),
    TPHY_REQ_BT_FIX_TX_CODE = OM_TCMD_ID(TPHY_BT_MID, OM_TYPE_REQ, 0x3),
    TPHY_REQ_EQUIP_RPT_SWITCH = OM_TCMD_ID(TPHY_BT_MID, OM_TYPE_REQ, 0x4),
}TDS_BT_OM_REQ_MSGID_ENUM;
typedef enum TDS_CT_OM_REQ_MSGID
{
    TPHY_REQ_CT_FIX_POWER = OM_TCMD_ID(TPHY_CT_MID, OM_TYPE_REQ, 0x1),

}TDS_CT_OM_REQ_MSGID_ENUM;

typedef struct TPHY_REQ_EQUIP_RPT_SWITCH
{
    OM_REQ_ENABLE_ENUM_UINT16 enRx;
    OM_REQ_ENABLE_ENUM_UINT16 enTx;
}TPHY_REQ_EQUIP_RPT_SWITCH_STRU;

typedef struct TPHY_REQ_BT_FIX_POWER
{
    OM_REQ_ENABLE_ENUM_UINT16 enFixPow;
    INT16 sPower;
}TPHY_REQ_BT_FIX_POWER_STRU;

typedef struct TPHY_REQ_BT_COMP_SWITCH
{
    OM_REQ_ENABLE_ENUM_UINT16 enFreqSwitch;
    OM_REQ_ENABLE_ENUM_UINT16 enTempSwitch;
}TPHY_REQ_BT_COMP_SWITCH_STRU;

typedef struct TPHY_REQ_BT_FIX_TX_CODE 
{
    OM_REQ_ENABLE_ENUM_UINT16 enFixSwitch;
    UINT16 usPaLevel;
    UINT16 usDbbAtt;
    UINT16 usRfCode;
    UINT16 rsd1;
    UINT16 rsd2;
}TPHY_REQ_BT_FIX_TX_CODE_STRU;
    
typedef enum TDS_EQUIP_OM_RPT_ID
{
    TPHY_EQUIP_TX_COMP_TRACE_IND = OM_TCMD_ID(TPHY_BT_MID, OM_TYPE_TRACE, 0x1),
    TPHY_EQUIP_RX_COMP_TRACE_IND,
}TDS_EQUIP_OM_RPT_ID_ENUM;
typedef enum TDS_EQUIP_NCIT_OM_RPT_ID
{
    TPHY_EQUIP_NCIT_START_TRACE_IND = OM_TCMD_ID(TPHY_NCIT_MID, OM_TYPE_TRACE, 0x1),
    TPHY_EQUIP_NCIT_END_TRACE_IND,
}TDS_EQUIP_NCIT_OM_RPT_ID_ENUM;
typedef enum TDS_EQUIP_CT_OM_RPT_ID
{
    TPHY_EQUIP_TRACE_IND = OM_TCMD_ID(TPHY_CT_MID, OM_TYPE_TRACE, 0x0),
    TPHY_EQUIP_TX_CAL_IND,
    TPHY_EQUIP_RX_CAL_IND,
    TPHY_EQUIP_RX_CAL_ANTPOW_IND,
    TPHY_EQUIP_RX_SYNC_IND,
    TPHY_EQUIP_RFCODE_REQ_IND,
    TPHY_EQUIP_DBBCODE_REQ_IND,
    TPHY_EQUIP_F_FREQ_SET_REQ_IND,
    TPHY_EQUIP_FREQ_TEST_MODE_REQ_IND,
    TPHY_EQUIP_F_PA_SET_REQ_IND,
    TPHY_EQUIP_F_SEGMENT_SET_REQ_IND,
    TPHY_EQUIP_F_TXWAVE_SET_REQ_IND,
    TPHY_EQUIP_F_AAGC_SET_REQ_IND,
    TPHY_EQUIP_L_TXON_SET_REQ_IND,
    TPHY_EQUIP_L_BANDSW_SET_REQ_IND,
    TPHY_EQUIP_L_FREQ_SET_REQ_IND,
    TPHY_EQUIP_L_AGC_SET_REQ_IND,
    TPHY_EQUIP_L_RXON_SET_REQ_IND,
    TPHY_EQUIP_L_FWAVE_SET_REQ_IND,
}TDS_EQUIP_CT_OM_RPT_ID_ENUM;
typedef struct TDS_EQUIP_RPT_RX_COMP
{
    INT16 sTotal;
    INT16 sFreq;

    INT16 sTemp;
    INT16 sFreqComp;

    INT16 sTempComp;
    INT16 sAgcType;

    INT16 sAgcIndex;
    INT16 rsd;
}TDS_EQUIP_RPT_RX_COMP_STRU;
typedef struct TDS_EQUIP_RPT_TX_COMP
{
    UINT16 usSubFnNum;
    UINT16 usSlotNum;
    INT16 sFreq;
    INT16 sTemp;

    INT16 sFreqComp;
    INT16 sTempComp;

    INT16 sInputPow;
    INT16 sPaLevel;

    INT16  sBbAtt;
    UINT16 usRfCode;
    INT16 sDbbAtt;
    INT16  sRes;
}TDS_EQUIP_RPT_TX_COMP_STRU;

typedef struct
{
    UINT16 usSubFnNum;
    UINT16 usSlotNum;

    UINT16 usBerSubFrmNum;
}TDS_EQUIP_RPT_NCIT_STRU;
typedef enum TDS_EQUIP_TRACE_MSG_ID
{
    OM_PHY_CT_TEST_MODE_REQ_ENUM = OM_PHY_CT_TEST_MODE_REQ,
    OM_PHY_CT_FWAVE_SET_REQ_ENUM = OM_PHY_CT_FWAVE_SET_REQ,
    OM_PHY_CT_TXON_REQ_ENUM = OM_PHY_CT_TXON_REQ,
    OM_PHY_CT_VCTCXO_SET_REQ_ENUM = OM_PHY_CT_VCTCXO_SET_REQ,
    OM_PHY_CT_F_FREQ_SET_REQ_ENUM = OM_PHY_CT_F_FREQ_SET_REQ,
    OM_PHY_CT_F_AAGC_SET_REQ_ENUM = OM_PHY_CT_F_AAGC_SET_REQ,
    OM_PHY_CT_F_PA_SET_REQ_ENUM = OM_PHY_CT_F_PA_SET_REQ,
    OM_PHY_CT_F_SEGMENT_SET_REQ_ENUM = OM_PHY_CT_F_SEGMENT_SET_REQ,
    OM_PHY_CT_F_TXWAVE_SET_REQ_ENUM = OM_PHY_CT_F_TXWAVE_SET_REQ,
    OM_PHY_CT_F_TRIGGER_SET_REQ_ENUM = OM_PHY_CT_F_TRIGGER_SET_REQ,
    OM_PHY_CT_F_TRIGGER_RD_REQ_ENUM = OM_PHY_CT_F_TRIGGER_RD_REQ,
    OM_PHY_CT_F_BANDSW_SET_REQ_ENUM = OM_PHY_CT_F_BANDSW_SET_REQ,
    OM_PHY_CT_F_GAINSTATE_SET_REQ_ENUM = OM_PHY_CT_F_GAINSTATE_SET_REQ,
    OM_PHY_CT_F_DBBATT_SET_REQ_ENUM = OM_PHY_CT_F_DBBATT_SET_REQ,
    OM_PHY_CT_F_BBATT_SET_REQ_ENUM = OM_PHY_CT_F_BBATT_SET_REQ,

    OM_PHY_BT_FPOW_SET_REQ_ENUM = OM_PHY_BT_FPOW_SET_REQ,
    MSP_PHY_NCIT_RXSUBFRA_SET_REQ_ENUM = OM_PHY_SYN_SRXSUBFRA_SET_REQ,//MSP_PHY_NCIT_RXSUBFRA_SET_REQ,
    MSP_PHY_NCIT_START_SET_REQ_ENUM = OM_PHY_SYN_SSTART_SET_REQ,//MSP_PHY_NCIT_START_SET_REQ,
    MSP_PHY_NCIT_STOP_SET_REQ_ENUM = OM_PHY_SYN_SSTOP_SET_REQ,//MSP_PHY_NCIT_STOP_SET_REQ,
    PHY_OM_CT_F_MEAS_RSSI_IND_ENUM = PHY_OM_CT_F_MEAS_RSSI_IND,
    PHY_OM_CT_F_MEAS_CMTMS_IND_ENUM = PHY_OM_CT_F_MEAS_CMTMS_IND,
    OM_PHY_CT_MEAS_RSSI_REQ_ENUM = OM_PHY_CT_MEAS_RSSI_REQ,

    OM_PHY_CT_FREQ_SET_REQ_ENUM = OM_PHY_CT_FREQ_SET_REQ,
    OM_PHY_CT_AAGC_SET_REQ_ENUM = OM_PHY_CT_AAGC_SET_REQ,
    OM_PHY_CT_RXON_REQ_ENUM = OM_PHY_CT_RXON_REQ,
    OM_PHY_CT_TSELRF_SET_REQ_ENUM = OM_PHY_CT_TSELRF_SET_REQ,
    PHY_OM_CT_RSSI_IND_ENUM  =    PHY_OM_CT_RSSI_IND,

    PHY_MSP_NCIT_RPT_BER_CNF_ENUM = 0xffffff01,
    
    PHY_MSP_EQUIP_TDS_TRACE_ENUM= 0xf0000000,
    
    EQUIP_TDS_TRACE_LOW_TX_ENUM = 0xf1000000,
    EQUIP_TDS_TRACE_LOW_RX_ENUM,
    
    EQUIP_TDS_TRACE_RX_SYNC_START_ENUM=0xf2000000,
    EQUIP_TDS_TRACE_RX_SYNC_END_ENUM,
    EQUIP_TDS_TRACE_RX_FIX_GAIN_ENUM,
    EQUIP_TDS_TRACE_RX_CAL_POWER_ENUM,
    EQUIP_TDS_TRACE_RX_SWEEP_FREQ_ENUM,
    
    EQUIP_TDS_TRACE_TX_SWEEP_FREQ_ENUM=0xf3000000,
    EQUIP_TDS_TRACE_TX_FIX_POWER_ENUM,
    

}TDS_EQUIP_TRACE_MSG_ID_ENUM;
typedef enum LTE_EQUIP_TRACE_MSG_ID
{

    EQUIP_LTE_RX_SYNC_TRACE_ENUM = 0xf0000011,
    EQUIP_LTE_TX_CAL_TRACE_ENUM = 0xf0000012,
    EQUIP_LTE_RX_SSI_TRACE_ENUM = 0xf0000013,
    EQUIP_LTE_RX_CAL_TRACE_ENUM = 0xf0000014,

}LTE_EQUIP_TRACE_MSG_ID_ENUM;
typedef enum TDS_EQUIP_TRACE_MSG_FLG
{
    TDS_EQUIP_OM_FLG_REQ = 0,
    TDS_EQUIP_OM_FLG_CNF = 1,

}TDS_EQUIP_TRACE_MSG_FLG_ENUM;
typedef enum LTE_EQUIP_TRACE_MSG_FLG
{
    LTE_EQUIP_OM_FLG_REQ = 0,
    LTE_EQUIP_OM_FLG_CNF = 1,
    
}LTE_EQUIP_TRACE_MSG_FLG_ENUM;

typedef struct TPHY_EQUIP_TRACE_RPT
{
    TDS_EQUIP_TRACE_MSG_ID_ENUM enMsgId;
    UINT32 ulContent0;
    UINT32 ulContent1;
    UINT32 ulContent2;
    UINT32 ulContent3;
    UINT32 ulContent4;
    UINT32 ulContent5;
}TPHY_EQUIP_TRACE_RPT_STRU;
    
typedef struct TPHY_EQUIP_GET_TX_RF_CODE_REQ
{
    UINT16 usRfCodeNum;
    UINT16 ausRfCode[TX_POW_MAX_NUM]; /*Rf???*/
}TPHY_EQUIP_GET_TX_RF_CODE_REQ_STRU;
typedef struct TPHY_EQUIP_DBB_CODE_REQ
{
    UINT16 usDbbCodeNum;     /*DBB????*/
    UINT16 usDbbCode;        /*DBB???*/
}TPHY_EQUIP_DBB_CODE_REQ_STRU;
typedef struct TPHY_EQUIP_RX_SYNC_INPUT_PARA
{
    UINT16 usSubFramNum;         /*????*/
    UINT16 usSlotNum;            /*????*/
    UINT16 usCtSubFramCnt;
    UINT16 usFreqInfo;           /*????*/
    UINT16 usGainStateCnt;     /*??????*/
    UINT16 usTxRfCode;           /*Rf???*/
    UINT16 usTxDBBCode;          /*DBB???*/
    UINT16 usResv;
    UINT8  ucPaLevel;            /*PA????*/
    UINT8  ucResv;
}TPHY_EQUIP_RX_SYNC_INPUT_STRU;
typedef struct TPHY_EQUIP_TX_CAL_INPUT_PARA
{
    UINT16 usSubFramNum;        /*????*/
    UINT16 usSlotNum;           /*????*/
    UINT16 usCtSubFramCnt;
    UINT16 usFreqNum;
    UINT16 usFreqcnt;
    UINT16 usFreqInfo;          /*????*/
    UINT16 usGainStateNum;
    UINT16 usGainStateCnt;
    UINT16 usTxRfCode;          /*Rf???*/
    UINT16 usTxDBBCode;         /*DBB???*/
    UINT8  ucPaLevel;           /*PA????*/
    UINT8  ucResv;
    UINT16 usResv;
}TPHY_EQUIP_TX_CAL_INPUT_STRU;
typedef struct TPHY_EQUIP_RX_CAL_INPUT_PARA
{
    UINT16 usSubFramNum;        /*????*/
    UINT16 usSlotNum;           /*????*/
    UINT16 usCtSubFramCnt;
    UINT16 usRxFreqNum;
    UINT16 usRxFreqcnt;
    UINT16 usRxFreqInfo;
    UINT16 usRxGainStateNum;
    UINT16 usRxGainCnt;
    UINT16 usRxRfCode;          /*Rf???*/
    INT16  usRxGain;
    UINT16 usBand;              /*Band??*/
    UINT16 usResv;
}TPHY_EQUIP_RX_CAL_INPUT_STRU;
typedef struct TPHY_EQUIP_RX_RSSI_PARA
{
    UINT16 usSubFramNum;
    UINT16 usSlotNum;
    UINT16 usCtSubFramCnt;
    UINT16 usFreqCnt;           /*????*/
    UINT16 usGainCnt;           /*??????*/
    UINT16 usRxSsiAntPowSum;    /*??????*/
    UINT16 usResv;
}TPHY_EQUIP_RX_RSSI_STRU;
void TDS_BT_OmReq(UINT32 ulMsgId, UINT32 ulSessionId, void* pstMsg, UINT32 ulMsgSize);    

#endif /* __TDS_oM_equip_def____H_ */
