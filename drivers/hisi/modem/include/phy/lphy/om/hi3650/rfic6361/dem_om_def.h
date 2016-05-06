/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dem_om_def.h
  版 本 号   : 初稿
  作    者   : Hong Huiyong
  生成日期   : 2011年1月15日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  -------------------------------------------------------------------------------
  1.日    期   : 2010年11月4日
    作    者   : 洪慧勇
    修改内容   : 新生成函数
-------------------------------------------------------------------------------
  2.日    期   : 2011年7月4日
    作    者   : 洪慧勇
    修改内容   : DTS2011122802269 根据算法要求，将双码字解调默认算法设置为QRM。
-------------------------------------------------------------------------------
 3.日    期   : 2012年04月17日
   作    者   : Shen Guang
   修改内容   : [DTS2012022700423]FDD-TDD互操作
-------------------------------------------------------------------------------
  4.日    期   : 2012年4月18日
     作    者   : sunyanjie，yushujing，xueqiuyan
     修改内容   : [DTS2012041802974]OM优化修改

******************************************************************************/


#ifndef __DEM_OM_DEFINE_H__
#define __DEM_OM_DEFINE_H__


typedef enum __PBCH_TYPE_ENUM__
{
   DEM_PB_TYPE_HANDOVER = 0,
   DEM_PB_TYPE_CAMPLED,
   DEM_PB_TYPE_RL,
   DEM_PB_TYPE_TESTMODE,
   DEM_PB_TYPE_SFN_SYNC
 }PBCH_TYPE_ENUM;

typedef UINT16 PBCH_OPERATE_SRC_ENUM_UINT16;

typedef enum __PBCH_DETECT_MODE_ENUM__
{
    PB_NONBLIND_DETECTION = 0,
    PB_BLIND_DETECTION_TTI ,
    PB_BLIND_DETECTION_TXANT,
    PB_BLIND_DETECTION_FULL
}PBCH_DETECT_MODE_ENUM;

typedef UINT16 PBCH_DETECT_MODE_ENUM_UINT16;



//#define DEM_OM_MAX_PAYLOAD_LENGTH    64
#define DEM_OM_MAX_PAYLOAD_LENGTH    64 * 2				//alex ca
#define DEM_OM_MSG_HEADER_LENGTH     12
#define DEM_OM_EXTRA_MSG_HEADER_LEN  4




//-----------------------------------------------
//  1.  DEM REQ 结构体定义和申明
//-----------------------------------------------

typedef enum __LPHY_REQ_MSGID_DEM_ENUM__
{
    LPHY_REQ_DEM_RESERVED  = OM_CMD_ID(LPHY_DEM_MID, OM_TYPE_REQ, 0x0),
    LPHY_REQ_DEM_PBCH_BLER,                    
    LPHY_REQ_DEM_PHICH_BLER, 
    LPHY_REQ_DEM_TRACE_INFO_SWITCH,
    LPHY_REQ_DEM_DEBUG_INFO_SWITCH,
    LPHY_REQ_DEM_ERROR_INFO_SWITCH,
    LPHY_REQ_DEM_PDSCH_ALG_CONFIG,   
    LPHY_REQ_DEM_PDSCH_MCS_RB_STAT_RPT,     
    LPHY_REQ_DEM_PDSCH_MIMO_SWITCH_RPT, 
    LPHY_REQ_DEM_PDSCH_RB_OCCUPATION_RPT, 
    LPHY_REQ_DEM_PHICH_DECODE_STATUS_RPT, 
    LPHY_REQ_DEM_DSP_INT_DURATION_RPT, 
    LPHY_REQ_DEM_IRC_PDC_OM_CONFIG,
	LPHY_REQ_DEM_IRC_PDS_OM_CONFIG   
}LPHY_REQ_MSGID_DEM_ENUM;

typedef UINT32 LPHY_REQ_MSGID_DEM_ENUM_UINT32;


/* PBCH BLER REQ CMD Structure */                



typedef struct __LPHY_DEM_PBCH_CTRL_INFO__
{
    UINT16  usCellID;
    UINT16  usFreqID;
    
    /*Inter FDD-TDD*/
    LRRC_LPHY_BAND_IND_ENUM_UINT16      enBandInd;                              /* 频带指示 */
    LRRC_LPHY_LTE_MODE_TYPE_ENUM_UINT16 enLteModeType;

    UINT16  usTxAntNum;
    UINT16  enDuplex;
    UINT16  enRBNumInd;
    PBCH_DETECT_MODE_ENUM_UINT16  enPbchDetMode;
}LPHY_DEM_PBCH_CTRL_INFO;

typedef struct __LPHY_REQ_DEM_PBCH_BLER_SRTU__
{
    UINT8  ucTestModeFlg;    
    UINT8  ucCombineStatus;
    UINT8  ucBlerResetFlg;
    UINT8  ucBlerReportFlg;
    UINT16 usChannelResetFlg;
    UINT16 usReportInterval;
    LPHY_DEM_PBCH_CTRL_INFO stPbchDemInfo;
}LPHY_REQ_DEM_PBCH_BLER_SRTU;

#define DEM_PBCH_TM_INFO_DEFAULT {0,0,0,0,0,0}



#define DEM_PBCH_BLER_REQUEST_STRU_DEFAULT {    LPHY_FALSE,             \
                                                LPHY_TRUE,              \
                                                LPHY_FALSE,             \
                                                LPHY_FALSE,             \
                                                LPHY_FALSE,             \
                                                1000,                   \
                                                DEM_PBCH_TM_INFO_DEFAULT\
                                            }
                                                
    

/* PHICH BLER REQ CMD Structure */

typedef struct __PHICH_INFO_STRU__
{
    UINT8  ucSeqIdx;
    UINT8  ucGrpIdx;
}PHICH_INFO_STRU;


typedef struct __LPHY_REQ_DEM_PHICH_BLER_SRTU__
{
    UINT8  ucTestModeFlg;    
    UINT8  ucGrpNum;
    UINT8  ucBlerResetFlg;
    UINT8  ucBlerReportFlg;
    UINT32 ulReportInterval;
    PHICH_INFO_STRU stPhichInfo[2];
}LPHY_REQ_DEM_PHICH_BLER_SRTU;

#define DEM_PHICH_PARA_DEFAULT      {{0,0},{0,0}}

#define DEM_PHICH_BLER_REQUEST_STRU_DEFAULT {   LPHY_FALSE,             \
                                                0,                      \
                                                LPHY_FALSE,             \
                                                LPHY_FALSE,             \
                                                1000,                   \
                                                DEM_PHICH_PARA_DEFAULT  \
                                            }
                                                


/* DEM Trace REQ CMD Structure */

typedef struct __LPHY_REQ_DEM_TRACE_INFO_SWITCH_STRU__
{
    UINT32 DemTraceInfoSwitchStatus;
}LPHY_REQ_DEM_TRACE_INFO_SWITCH_STRU;

/* DEM Debug REQ CMD Structure */
typedef struct __LPHY_REQ_DEM_DEBUG_INFO_SWITCH_STRU__
{
    UINT32 DemDebugInfoSwitchStatus;
}LPHY_REQ_DEM_DEBUG_INFO_SWITCH_STRU;

/* DEM ERROR REQ CMD Structure */
typedef struct __LPHY_REQ_DEM_ERROR_INFO_SWITCH_STRU__
{
    UINT32 DemErrorInfoSwitchStatus;
}LPHY_REQ_DEM_ERROR_INFO_SWITCH_STRU;

/* DEM PDSCH ALG CONFIG Structure */
typedef enum __PDSCH_DEM_SOFTBIT_SHIFT_CONFIG_ENUM__
{
   PDSCH_DEM_SOFTBIT_SHIFT_CONFIG_ADAPTIVE = 0,
   PDSCH_DEM_SOFTBIT_SHIFT_CONFIG_MANUAL,
}PDSCH_DEM_SOFTBIT_SHIFT_CONFIG_ENUM;

typedef enum __DEM_PDSCH_SFBC_ALG_SELECT_METHOD_ENUM__
{
   DEM_PDSCH_SFBC_ALG_FIX_MMSE = 0,
   DEM_PDSCH_SFBC_ALG_FIX_MRC,
   DEM_PDSCH_SFBC_ALG_ADAPTIVE 
}DEM_PDSCH_SFBC_ALG_SELECT_METHOD_ENUM;

typedef enum __DEM_PDSCH_SDM2_ALG_SELECT_METHOD_ENUM__
{
   DEM_PDSCH_SDM2_ALG_ADAPTIVE = 0,
   DEM_PDSCH_SDM2_ALG_FIX_QRM,
   DEM_PDSCH_SDM2_ALG_FIX_SIC,
   DEM_PDSCH_SDM2_ALG_FIX_MMSE,
}DEM_PDSCH_SDM2_ALG_SELECT_METHOD_ENUM;

typedef struct __DEM_PDSCH_SHIFT_CONFIG_STRU__
{
    UINT16 usBitShiftIrcOFF;
    UINT16 usBitShiftIrcON;
}DEM_PDSCH_SHIFT_CONFIG_STRU;

typedef struct __LPHY_REQ_DEM_PDSCH_ALG_CONFIG_STRU__
{
    DEM_PDSCH_SFBC_ALG_SELECT_METHOD_ENUM enDemPdschSfbcAlg;
    DEM_PDSCH_SDM2_ALG_SELECT_METHOD_ENUM enDemPdschSdm2Alg;
    PDSCH_DEM_SOFTBIT_SHIFT_CONFIG_ENUM   enSoftBitSftFlag;
    UINT16								  usBfPort7or8SIMOFlag;//alex ca
    DEM_PDSCH_SHIFT_CONFIG_STRU  stSIMOShiftPara;
    DEM_PDSCH_SHIFT_CONFIG_STRU  stSFBCMRCShiftPara;
    DEM_PDSCH_SHIFT_CONFIG_STRU  stSFBCMMSEShiftPara;
    DEM_PDSCH_SHIFT_CONFIG_STRU  stSMD1ShiftPara;
    DEM_PDSCH_SHIFT_CONFIG_STRU  stMMSEShiftPara;
    DEM_PDSCH_SHIFT_CONFIG_STRU  stQRMShiftPara;
}LPHY_REQ_DEM_PDSCH_ALG_CONFIG_STRU;

#define LPHY_REQ_DEM_PDSCH_ALG_CONFIG_DEFAULT {     DEM_PDSCH_SFBC_ALG_ADAPTIVE,                \
                                                    DEM_PDSCH_SDM2_ALG_ADAPTIVE,                \
                                                    PDSCH_DEM_SOFTBIT_SHIFT_CONFIG_ADAPTIVE,    \
                                                    0,											\
                                                    {0,0},                                      \
                                                    {0,0},                                      \
                                                    {0,0},                                      \
                                                    {0,0},                                      \
                                                    {0,0},                                      \
                                                    {0,0}                                       \
                                              }



/* DEM PDSCH throughout report REQ CMD Structure */
typedef struct __LPHY_REQ_DEM_PDSCH_MIMO_SWITCH_RPT_STRU__
{
    UINT16 usRptSwitch;
    UINT16 usRptPeriod;
}LPHY_REQ_DEM_PDSCH_MIMO_SWITCH_RPT_STRU;

#define LPHY_REQ_DEM_PDSCH_MIMO_SWITCH_RPT_DEFAULT {LPHY_OFF,1000}

/* DEM PDSCH Rb occupation report REQ CMD Structure */
typedef struct __LPHY_REQ_DEM_PDSCH_RB_OCCUPATION_RPT_STRU__
{
    UINT16 usRptSwitch;
    UINT16 usRptPeriod;
}LPHY_REQ_DEM_PDSCH_RB_OCCUPATION_RPT_STRU;

#define LPHY_REQ_DEM_PDSCH_RB_OCCUPATION_RPT_DEFAULT {LPHY_OFF,1000}

/* DEM PDSCH MCS Rb Stat. report REQ CMD Structure */
typedef struct __LPHY_REQ_DEM_PDSCH_MCS_RB_STAT_RPT_STRU__
{
    UINT16 usRptSwitch;
    UINT16 usRptPeriod;
}LPHY_REQ_DEM_PDSCH_MCS_RB_STAT_RPT_STRU;

#define LPHY_REQ_DEM_PDSCH_MCS_RB_STAT_RPT_DEFAULT {LPHY_OFF,1000}


/* DEM PHICH decode status report REQ CMD Structure */
typedef struct __LPHY_REQ_DEM_PHICH_DECODE_STATUS_RPT_STRU__
{
    UINT16 usRptSwitch;
    UINT16 usRptPeriod;
}LPHY_REQ_DEM_PHICH_DECODE_STATUS_RPT_STRU;

#define LPHY_REQ_DEM_PHICH_DECODE_STATUS_RPT_DEFAULT {LPHY_OFF,1}


/* DEM interrupt duration report REQ CMD Structure */
typedef struct __LPHY_REQ_DEM_DSP_INT_DURATION_RPT_STRU__
{
    UINT16 usRptSwitch;
    UINT16 usRptPeriod;
}LPHY_REQ_DEM_DSP_INT_DURATION_RPT_STRU;

#define LPHY_REQ_DEM_DSP_INT_DURATION_RPT_DEFAULT {LPHY_OFF,1000}

/*LPHY_REQ_DEM_IRC_PDC_OM_CONFIG*/
typedef struct
{
	struct
	{
		UINT8 ucPdcIrcOmSwitchEn;						/*0 disable switch; 1 enable switch*/
		UINT8 ucPdcIrcFlag;								/*0 irc off; 1 irc on*/
	} stPdcIrcSwitch;
	
	struct
	{
		UINT8 ucPdcIrcRuuModeEn;						/*0 disable switch; 1 enable switch*/
		UINT8 ucPdcIrcRuuMode;							/*0 cmu ; 1 ls*/
	} stPdcIrcRuuMode;

	struct
	{
		UINT8 ucPdcIrcRuuTTIswEn;						/*0 disable switch; 1 enable switch*/
		UINT8 ucPdcIrcRuuTTISwitch;						/*0 ls; 1 cmu*/
	} stPdcIrcRuuTTIswitch;

	struct
	{
		UINT8 ucPdcIrcBlEstEn;							/*0 disable switch; 1 enable switch*/
		UINT8 ucPdcIrcBlEst; 							/*0 balance est. off; 1 balance est. on*/
	} stPdcIrcBlEst;

	struct
	{
		UINT8 ucPdcIrcAdapThrEn;						/*0 disable switch; 1 enable switch*/
		UINT8 ucPdcIrcAdapThrA;							
		UINT8 ucPdcIrcAdapThrB;							
	} stPdcIrcAdaptiveThr;

	struct
	{
		UINT8 ucPdcIrcAdapGranEn;						/*0 disable switch; 1 enable switch*/
		UINT8 ucPdcIrcAdapGranN1; 						
		UINT8 ucPdcIrcAdapGranN2; 						
	} stPdcIrcAdaptiveGran;
	
	
}LPHY_REQ_DEM_IRC_PDC_OM_CONFIG_STRU;

#define LPHY_REQ_DEM_IRC_PDC_OM_CONFIG_DEFAULT  		{{0,1},\
														 {0,1},\
														 {0,1},\
														 {0,1},\
														 {0,0,0},\
														 {0,6,3}}

/*LPHY_REQ_DEM_IRC_PDS_OM_CONFIG*/
typedef struct
{
	struct
	{
		UINT8 ucPdsIrcAdapThrEn;						/*0 disable switch; 1 enable switch*/
		UINT8 ucPdsIrcAdapThrA;							
		UINT8 ucPdsIrcAdapThrB;							
	} stPdsIrcAdaptiveThr;
	struct
	{
		UINT8 ucPdsBFIrcAdapThrEn;						/*0 disable switch; 1 enable switch*/
		UINT8 ucPdsBFIrcAdapThrA;							
		UINT8 ucPdsBFIrcAdapThrB;							
	} stPdsBFIrcAdaptiveThr;

}LPHY_REQ_DEM_IRC_PDS_OM_CONFIG_STRU;

#define LPHY_REQ_DEM_IRC_PDS_OM_CONFIG_DEFAULT  		{{0,0,0},{0,0,0}}

//-----------------------------------------------
//  2.  DEM IND 结构体定义和申明
//-----------------------------------------------

typedef enum __LPHY_SG_MSGID_DEM_SG_ENUM__
{
    LPHY_SG_DEM_RESERVED        = OM_CMD_ID(LPHY_DEM_MID,OM_TYPE_SG,0),
    LPHY_SG_DEM_PBCH_BLER_RPT,
    LPHY_SG_DEM_PHICH_BLER_RPT,
    LPHY_IND_DEM_PDSCH_MCS_RB_STAT_RPT, 
    LPHY_IND_DEM_PDSCH_MIMO_SWITCH_RPT, 
    LPHY_IND_DEM_PDSCH_RB_OCCUPATION_RPT, 
    LPHY_IND_DEM_PHICH_DECODE_STATUS_RPT, 
    LPHY_IND_DEM_DSP_INT_DURATION_RPT, 
}LPHY_SG_MSGID_DEM_SG_ENUM;

typedef UINT32 LPHY_SG_MSGID_DEM_SG_ENUM_UINT32;



/* SG Structure define for Demodulation module */
typedef struct __LPHY_SG_DEM_PBCH_BLER_RPT_STRU__
{
    UINT16 usSysFN;        /*上报系统帧号*/
    UINT16 usSubFN;        /*上报子帧号  */  
    UINT16 usCellID;       /*上报消息类型*/
    UINT16 usFreqID;       /*上报消息长度*/
    UINT32 ulTotalTTI;
    UINT32 ulCNTSuccess;
    UINT8  ucPbchDetMode;
    UINT8  ucCombineFlag;
    UINT8  ucIRCStatus;
    UINT8  ucDecodeAll; 
    UINT32 ulRptCnt; 
    
}LPHY_SG_DEM_PBCH_BLER_RPT_STRU;


/* SG Structure define for Demodulation module */
typedef struct __LPHY_SG_DEM_PHICH_BLER_RPT_STRU__
{
    UINT16 usSysFN;        /*上报系统帧号*/
    UINT16 usSubFN;        /*上报子帧号  */  
    UINT16 usCellID;       /*上报消息类型*/
    UINT16 usTestMode;     /*上报消息长度*/

    UINT32 ulCntACKAccu;
    UINT32 ulCntNAKAccu;
    UINT32 ulCntACKPeriod;
    UINT32 ulCntNAKPeriod;    
}LPHY_SG_DEM_PHICH_BLER_RPT_STRU;


/* IND Structure define for PDSCH_THROUGHTOUT_RPT */
typedef struct __LPHY_IND_DEM_PDSCH_MIMO_SWITCH_RPT_STRU__
{
    UINT16 usSysFN;        /*上报系统帧号*/
    UINT16 usSubFN;        /*上报子帧号  */  
    UINT16 usReportCnt;  
    UINT16 usReserved;    
    UINT32 aulMimoSwitchStatArray[2][7];//alex ca
}LPHY_IND_DEM_PDSCH_MIMO_SWITCH_RPT_STRU;


/* IND Structure define for PDSCH_RB_OCCUPATION_RPT */
typedef struct __LPHY_IND_DEM_PDSCH_RB_OCCUPATION_RPT_STRU__
{
    UINT16 usSysFN;        /*上报系统帧号*/
    UINT16 usSubFN;        /*上报子帧号  */  
    UINT16 usReportCnt;  
    UINT16 usReserved;
    UINT32 aulTotalRBNum[2];//alex ca
    //UINT16 ausRbCntArray[2][2][100];//alex ca for HSO doesn't support 3 dimension array
    UINT16 ausRbCntArrayCC0[2][100];//alex ca
    UINT16 ausRbCntArrayCC1[2][100];//alex ca
}LPHY_IND_DEM_PDSCH_RB_OCCUPATION_RPT_STRU;


/* IND Structure define for PDSCH_MCS_RB_STAT_RPT */
typedef struct __MCS_RB_CNT_STRU__
{
    UINT16 usCwCnt[2];
    UINT16 usCwRbCnt[2];
}MCS_RB_CNT_STRU;

typedef struct __LPHY_IND_DEM_PDSCH_MCS_RB_STAT_RPT_STRU__
{
    UINT16 usSysFN;        /*上报系统帧号*/
    UINT16 usSubFN;        /*上报子帧号  */  
    UINT16 usReportCnt;    
    UINT16 usReserved;
    UINT32 aulTotalRBNum[2];//alex ca
    MCS_RB_CNT_STRU astMcsRbStatArray[2][32];//alex ca
}LPHY_IND_DEM_PDSCH_MCS_RB_STAT_RPT_STRU;



/* IND Structure define for dsp Interrupt duration_RPT */
typedef struct __INT_SYM_DURATION_STRU__
{
    UINT32 ulOneTimeDuration;
    UINT32 ulAverageDuration;
}INT_SYM_DURATION_STRU;

typedef struct __LPHY_IND_DEM_DSP_INT_DURATION_RPT_STRU__
{
    UINT16 usSysFN;        /*上报系统帧号*/
    UINT16 usSubFN;        /*上报子帧号  */  
    UINT16 usReportCnt;    
    UINT16 usReserved;
    INT_SYM_DURATION_STRU stIntDuraArray[14];
}LPHY_IND_DEM_DSP_INT_DURATION_RPT_STRU;



/* IND Structure define for PHICH decode status RPT */
typedef struct __LPHY_IND_DEM_PHICH_DECODE_STATUS_RPT_STRU__
{
    UINT16 usSysFN;        /*上报系统帧号*/
    UINT16 usSubFN;        /*上报子帧号  */  
    UINT16 usReportCnt;    
    UINT16 usPhichNum;
    UINT16 usPhichRes[2];
}LPHY_IND_DEM_PHICH_DECODE_STATUS_RPT_STRU;



//---------------------------------------------------------
//  3.  DEM debug info 结构体定义和申明[共用上报结构体]
//---------------------------------------------------------

typedef enum __LPHY_DBG_MSGID_DEM_DEBUG_ENUM__
{
    LPHY_DBG_DEM_RESERVED  = OM_CMD_ID(LPHY_DEM_MID,OM_TYPE_DEBUG,0),
    LPHY_DBG_DEM_PBCH_CTRL_INFO,
    LPHY_DBG_DEM_PBCH_BBP_IMAGE,
    
    LPHY_DBG_DEM_PDCCH_CTRL_INFO,
    LPHY_DBG_DEM_PDCCH_BBP_IMAGE,

    LPHY_DBG_DEM_PDSCH_CTRL_INFO,
    LPHY_DBG_DEM_PDSCH_BBP_IMAGE,    
}LPHY_DBG_MSGID_DEM_DEBUG_ENUM;
typedef UINT32 LPHY_DBG_MSGID_DEM_DEBUG_ENUM_UINT32;

typedef struct __LPHY_DEM_DEBUG_REPORT_OM_IND__
{
    UINT16      usSysFN;        /*上报系统帧号*/
    UINT16      usSubFN;        /*上报子帧号*/    
    UINT32      ulPaylod[DEM_OM_MAX_PAYLOAD_LENGTH];
}LPHY_DEM_DEBUG_REPORT_OM_IND;


//---------------------------------------------------------
//  4.  DEM error info 结构体定义和申明[共用上报结构体]
//---------------------------------------------------------

/* Error Message Report Format */

typedef enum __LPHY_ERR_MSGID_DEM_ERROR_ENUM__
{
    LPHY_ERR_DEM_RESERVED = OM_CMD_ID(LPHY_DEM_MID,OM_TYPE_ERROR,0),
    LPHY_ERR_DEM_PBCH_DECODE_UNFINISHED,
    LPHY_ERR_DEM_PBCH_DECODE_TIMEOUT,
    LPHY_ERR_DEM_PBCH_UNEXPECTED_CAMPEL,
    LPHY_ERR_DEM_PBCH_UNEXPECTED_OPERSRC,        
}LPHY_ERR_MSGID_DEM_ERROR_ENUM;
typedef UINT32 LPHY_ERR_MSGID_DEM_ERROR_ENUM_UINT32;

typedef struct __LPHY_DEM_ERROR_REPORT_OM_IND__
{
    UINT16      usSysFN;        /*上报系统帧号*/
    UINT16      usSubFN;        /*上报子帧号*/    
    UINT32      ulPaylod[DEM_OM_MAX_PAYLOAD_LENGTH];
}LPHY_DEM_ERROR_REPORT_OM_IND;


#define LPHY_DT_PDSCH_TM_MODE_INFO_REQ_DEFAULT {LPHY_OFF,200}
typedef struct __LPHY_DT_PDSCH_TM_MODE_INFO_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16  usRptPeriod;
} LPHY_DT_PDSCH_TM_MODE_INFO_REQ_STRU;

typedef struct __LPHY_DT_PDSCH_TM_MODE_INFO_IND_STRU__
{
    UINT8 ucCcValidFlg;
    UINT8 ucCcIdx;
    UINT16 usRsv0;

    UINT16     usSFN;
    UINT16     usSubFn;

    LRRC_LPHY_PDSCH_TM_MODE_ENUM_UINT16 enTransMode;
    UINT16 usRsv1;
} LPHY_DT_PDSCH_TM_MODE_INFO_IND_STRU;


typedef struct __LPHY_DT_DEM_PDSCH_MCS_STAT_RPT_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16    usReportPeriod;
} LPHY_DT_DEM_PDSCH_MCS_STAT_RPT_REQ_STRU;

#define LPHY_DT_DEM_PDSCH_MCS_STAT_RPT_REQ_DEFAULT {LPHY_OFF,200}
#define LPHY_DT_DEM_PHICH_BLER_REQ_DEFAULT {LPHY_OFF,200}

typedef struct __LPHY_DT_DEM_PHICH_BLER_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16    usReportPeriod;
}LPHY_DT_DEM_PHICH_BLER_REQ_STRU;

typedef struct __LPHY_DT_DEM_PDSCH_MCS_STAT_RPT_IND_STRU__
{
    UINT8 ucCcValidFlg;
    UINT8 ucCcIdx;
    UINT16 usRsv;

    UINT32 aulCW0McsStatArray[32];
    UINT32 aulCW1McsStatArray[32];
    UINT32 aulQPSKTotalNum[2];
    UINT32 aul16QAMTotalNum[2];
    UINT32 aul64QAMTotalNum[2];
}LPHY_DT_DEM_PDSCH_MCS_STAT_RPT_IND_STRU;


typedef struct __LPHY_DT_DEM_PHICH_BLER_IND_STRU__
{
    UINT32 ulACKAccuNum;
    UINT32 ulNACKAccuNum;
    UINT32 ulAccuTotalNum;
    UINT32 ulInitTransNACKNum;
    UINT32 ulInitTransTotalNum;
    UINT32 ulReTransNACKNum;
    UINT32 ulReTransTotalNum;
    UINT32 ulResidualNACKNum;
    UINT32 ulResidualTotalNum;
}LPHY_DT_DEM_PHICH_BLER_IND_STRU;


typedef struct __LPHY_IND_DEM_PDSCH_RB_STAT_RPT_STRU__
{
    UINT8 ucCcValidFlg;
    UINT8 ucCcIdx;
    UINT16 usRsv;

    UINT16 usSysFN;        /*上报系统帧号*/
    UINT16 usSubFN;        /*上报子帧号  */

    UINT16 usReportCnt;
    UINT16 usReserved;

    UINT32 ulTotalRBNum;
    UINT16 ausRbCntArray[2][100];

}LPHY_IND_DEM_PDSCH_RB_STAT_RPT_STRU;


typedef enum __LPHY_DT_MSGID_DEM_IND_ENUM__
{
    LPHY_DT_DEM_PDSCH_MCS_STAT_RPT_IND    = OM_CMD_ID(LPHY_DEM_MID,OM_TYPE_DT,0x1001),
    LPHY_DT_DEM_PHICH_BLER_IND            = OM_CMD_ID(LPHY_DEM_MID,OM_TYPE_DT,0x1002),
    LPHY_DT_PDSCH_TM_MODE_INFO_IND        = OM_CMD_ID(LPHY_DEM_MID,OM_TYPE_DT,0x1003),
    //new add
    LPHY_DT_PDSCH_TM_SCHEME_INFO_IND        = OM_CMD_ID(LPHY_DEM_MID,OM_TYPE_DT,0x1004),
    LPHY_DT_DEM_PDSCH_MCS_STAT_RPT_CA_IND    = OM_CMD_ID(LPHY_DEM_MID,OM_TYPE_DT,0x9001),
    LPHY_DT_PDSCH_TM_MODE_INFO_CA_IND        = OM_CMD_ID(LPHY_DEM_MID,OM_TYPE_DT,0x9003),
    LPHY_DT_DEM_PDSCH_PRB_STAT_RPT_CA_IND        = OM_CMD_ID(LPHY_DEM_MID,OM_TYPE_DT,0x9005)
}LPHY_DT_MSGID_DEM_IND_ENUM;





//---------------------------------------------------------
//  5.  DEM trace info 结构体定义和申明[共用上报结构体]
//---------------------------------------------------------

/* Trace Message Report Format */
typedef enum __LPHY_TRC_MSGID_DEM_TRACE_ENUM__
{
    LPHY_TRC_DEM_RESERVED = OM_CMD_ID(LPHY_DEM_MID,OM_TYPE_TRACE,0),
    LPHY_TRC_DEM_PBCH_REPORT_RL_IND,
    LPHY_TRC_DEM_PBCH_REPORT_CAMPEL_CNF,
    LPHY_TRC_DEM_PBCH_REPORT_HANDOVER_CNF,
    LPHY_TRC_DEM_PBCH_TIMING_UPDATA,
}LPHY_TRC_MSGID_DEM_TRACE_ENUM;
typedef UINT32 LPHY_TRC_MSGID_DEM_TRACE_ENUM_UINT32;

typedef struct __LPHY_DEM_TRACE_REPORT_OM_IND__
{
    UINT16      usSysFN;        /*上报系统帧号*/
    UINT16      usSubFN;        /*上报子帧号*/    

    PBCH_OPERATE_SRC_ENUM_UINT16 enOpSrc;
    UINT16      usOPID;        /*上报消息ID*/
    UINT16      usCellID;      /*上报消息类型*/
    UINT16      usFreqId;      /*上报消息长度*/
    UINT16      usResult;
    UINT16      usReserved;    
}LPHY_DEM_TRACE_REPORT_OM_IND;
typedef struct __LPHY_DEM_TRACE_TIMING_UPDATA_OM_IND__
{
    UINT16      usSysFN;        /*上报系统帧号*/
    UINT16      usSubFN;        /*上报子帧号*/
    UINT16      usDecodeSfn;
    UINT16      usRsd;

}LPHY_DEM_TRACE_TIMING_UPDATA_OM_IND;

//-----------------------------------------------
//  6.  DEM DT 结构体定义和申明
//-----------------------------------------------
typedef enum __LPHY_DT_MSGID_DEM_REQ_ENUM__
{
    LPHY_DT_DEM_PDSCH_MCS_STAT_RPT_REQ      = OM_CMD_ID(LPHY_DEM_MID,OM_TYPE_DT,0x1),
    LPHY_DT_DEM_PHICH_BLER_REQ              = OM_CMD_ID(LPHY_DEM_MID,OM_TYPE_DT,0x2),
    LPHY_DT_PDSCH_TM_MODE_INFO_REQ          = OM_CMD_ID(LPHY_DEM_MID,OM_TYPE_DT,0x3),
    //LPHY_DT_PDSCH_TM_SCHEME_INFO_REQ          = OM_CMD_ID(LPHY_DEM_MID,OM_TYPE_DT,0x4),
    LPHY_DT_DEM_PDSCH_PRB_STAT_RPT_REQ          = OM_CMD_ID(LPHY_DEM_MID,OM_TYPE_DT,0x5)

}LPHY_DT_MSGID_DEM_REQ_ENUM;



#endif
