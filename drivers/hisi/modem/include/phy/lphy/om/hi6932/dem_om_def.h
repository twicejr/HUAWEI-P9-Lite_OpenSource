


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
//  1.  DEM REQ ????????
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
	LPHY_REQ_DEM_IRC_PDS_OM_CONFIG,
	LPHY_DT_DEM_PDSCH_MCS_STAT_RPT_REQ = OM_CMD_ID(LPHY_DEM_MID, OM_TYPE_REQ, 0x100),     
    LPHY_DT_DEM_PHICH_BLER_REQ ,            
    LPHY_DT_PDSCH_TM_MODE_INFO_REQ ,        
    LPHY_DT_DEM_PDSCH_PRB_STAT_RPT_REQ  
}LPHY_REQ_MSGID_DEM_ENUM;

typedef UINT32 LPHY_REQ_MSGID_DEM_ENUM_UINT32;


/* PBCH BLER REQ CMD Structure */                



typedef struct __LPHY_DEM_PBCH_CTRL_INFO__
{
    UINT16  usCellID;
    UINT16  usFreqID;
    
    /*Inter FDD-TDD*/
    LRRC_LPHY_BAND_IND_ENUM_UINT16      enBandInd;                              /* ???? */
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

typedef UINT16 DEM_PDSCH_SFBC_ALG_SELECT_METHOD_ENUM_UINT16;

typedef enum __DEM_PDSCH_SDM2_ALG_SELECT_METHOD_ENUM__
{
   DEM_PDSCH_SM_ALG_ADAPTIVE = 0,
   DEM_PDSCH_SM_ALG_FIX_QRM,
   DEM_PDSCH_SM_ALG_FIX_SIC,
   DEM_PDSCH_SM_ALG_FIX_MMSE,
}DEM_PDSCH_SDM2_ALG_SELECT_METHOD_ENUM;

typedef UINT16 DEM_PDSCH_SDM2_ALG_SELECT_METHOD_ENUM_UINT16;


typedef struct __DEM_PDSCH_SHIFT_CONFIG_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT8                       ucBitShiftIrcOFF;
    UINT8                       ucBitShiftIrcON;
}DEM_PDSCH_SHIFT_CONFIG_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT8                       ucLlrSignFlag;
    UINT8                       ucSoftFctor;
    UINT16                      usNoiseBitThr;
    UINT16                      usNoiseBitMin;
}DEM_PDSCH_SHIFT_CTRL_STRU;

typedef struct
{
    INT8                       ucMmseS0;
    INT8                       ucMmseS1;
    INT8                       ucQrmS0;
    INT8                       ucQrmS1;
}DEM_PDSCH_COMB_FACTOR_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16                      usCombThr;
    UINT16                      usMmseScale;
    UINT16                      usRev;
}DEM_PDSCH_COMB_TH_STRU;

typedef struct
{
    UINT8                        ucHorderModEna;
    UINT8                        ucHOrderMod;
    UINT8                        ucHOrderTabEna;
    UINT8                        ucHOrderTab;
}DEM_PDSCH_QRM_H_ORDER_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16    enEna;
    UINT8                        usTrgtbtY;
    UINT8                        usTrgtbtH;
}DEM_PDSCH_TARGET_BIT_STRU;

typedef struct
{
    UINT32 ulPdsQrmIdx0;
    UINT32 ulPdsQrmIdx1;
}DEM_PDSCH_QRM_IDX_STRU;

typedef struct __LPHY_REQ_DEM_PDSCH_ALG_CONFIG_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16			  enEnAbleAll;//alex ca
    UINT16								  usBfPort7or8SIMOFlag;//alex ca
    DEM_PDSCH_SFBC_ALG_SELECT_METHOD_ENUM_UINT16 enDemPdschSfbcAlg;
    DEM_PDSCH_SDM2_ALG_SELECT_METHOD_ENUM_UINT16 enDemPdschSdm2Alg;

    DEM_PDSCH_SHIFT_CONFIG_STRU  stCh0C0ShiftPara;
    DEM_PDSCH_SHIFT_CONFIG_STRU  stCh0C1ShiftPara;
    DEM_PDSCH_SHIFT_CONFIG_STRU  stCh1ShiftPara;
    DEM_PDSCH_SHIFT_CONFIG_STRU  stCh2ShiftPara;
    DEM_PDSCH_SHIFT_CONFIG_STRU  stSicC0ShiftPara;
    DEM_PDSCH_SHIFT_CONFIG_STRU  stSicC1ShiftPara;
    DEM_PDSCH_SHIFT_CTRL_STRU    stPdsShiftCtrl;
    DEM_PDSCH_COMB_FACTOR_STRU   stPdsCombFactor;
    DEM_PDSCH_COMB_FACTOR_STRU   stPdsCJFactor;
    DEM_PDSCH_COMB_TH_STRU       stPdsCombTh;
    DEM_PDSCH_QRM_H_ORDER_STRU   stQrmHOrderAlgCpnfig;
    DEM_PDSCH_TARGET_BIT_STRU    stTargetBit;
    DEM_PDSCH_QRM_IDX_STRU       stPdsQrmIdx;
}LPHY_REQ_DEM_PDSCH_ALG_CONFIG_STRU;

#define LPHY_REQ_DEM_PDSCH_ALG_CONFIG_DEFAULT {     0,                                            \
                                                    0,											  \
                                                    DEM_PDSCH_SFBC_ALG_ADAPTIVE,                  \
                                                    DEM_PDSCH_SM_ALG_ADAPTIVE,                    \
                                                    {0,0,0},                                      \
                                                    {0,0,0},                                      \
                                                    {0,0,0},                                      \
                                                    {0,0,0},                                      \
                                                    {0,0,0},                                      \
                                                    {0,0,0},                                      \
                                                    {0,0,0,0,0},                                  \
                                                    {0,0,0,0},                                    \
                                                    {0,0,0,0},                                    \
                                                    {0,0,0,0},                                    \
                                                    {0,0,0,0},                                    \
                                                    {0,0,0},                                      \
                                                    {0,0}                                         \
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
    UINT16 ucPdcIrcOmSwitchEn;                       /*0 disable switch; 1 enable switch*/
    UINT16 ucPdcIrcFlag;                             /*0 irc off; 1 irc on*/
} LPHY_REQ_DEM_IRC_SWITCH_STRU;
typedef struct
{
	UINT16 ucPdcIrcOmSnrThrEn;						/*0 disable switch; 1 enable switch*/
	INT16 sPdcIrcSnrThr;								/*0 irc off; 1 irc on*/
} LPHY_REQ_DEM_IRC_SNR_THR_STRU;
typedef struct
{
    UINT16 ucPdcIrcRuuModeEn;                        /*0 disable switch; 1 enable switch*/
    UINT16 ucPdcIrcRuuMode;                          /*0 cmu ; 1 ls*/
}LPHY_REQ_DEM_IRC_RUU_MODE_STRU;

typedef struct
{
	UINT16 ucPdcIrcRuuTTIswEn;						/*0 disable switch; 1 enable switch*/
	UINT16 ucPdcIrcRuuTTISwitch;						/*0 ls; 1 cmu*/
}LPHY_REQ_DEM_IRC_TTI_SWITCH_STRU;

typedef struct
{
    UINT16 ucPdcIrcBlEstEn;                          /*0 disable switch; 1 enable switch*/
    UINT16 ucPdcIrcBlEst;                            /*0 balance est. off; 1 balance est. on*/
}LPHY_REQ_DEM_IRC_BL_EST_STRU;
typedef struct
{
	UINT16 ucPdcIrcAdapThrEn;						/*0 disable switch; 1 enable switch*/
	UINT8 ucPdcIrcAdapThrA;
	UINT8 ucPdcIrcAdapThrB;
}LPHY_REQ_DEM_IRC_ADAP_THR_STRU;

typedef struct
{
    UINT16 ucPdcIrcAdapGranEn;   /*0 disable switch; 1 enable switch*/
    UINT16 ucPdcIrcAdapGranN2;
} LPHY_REQ_DEM_IRC_ADAP_GRANN2_STRU;

typedef struct
{
	UINT16 ucIrcRuuSet0En;	/*0 disable switch; 1 enable switch*/
	UINT16 ucIrcRuuSet0; 		/*非主对角线置零指示*/
}LPHY_REQ_DEM_IRC_RUU_SET0_STRU;

typedef struct
{
    UINT16 ucPDCRuuCoefEn;   /*0 disable switch; 1 enable switch*/
	UINT16 usPDCRuuDCoef; 	/*PDCCH Ruu主对角线元素修正系数*/
	UINT16 usPDCRuuNDCoef; 	/*PDCCH Ruu非主对角线元素修正系数*/
	UINT16 ucRsv;
}LPHY_REQ_DEM_IRC_PDC_RUU_COEF_STRU;

typedef struct
{
    UINT16 ucTGT_WEn;    /*0 disable switch; 1 enable switch*/
    UINT16 ucTGT_W;
} LPHY_REQ_DEM_IRC_UC_TGT_W_STRU;

typedef struct
{
    UINT16 ucCqiRuuCoefEn;   /*0 disable switch; 1 enable switch*/
	UINT16 usCqiRuuDCoef; 	/*CQI Ruu主对角线元素修正系数*/
	UINT16 usCqiRuuNDCoef; 	/*CQI Ruu非主对角线元素修正系数*/
	UINT16 ucRsv;
}LPHY_REQ_DEM_IRC_CQI_RUU_COEF_STRU;
typedef struct
{
    UINT16 ucCqiIrcThrAEn;    /*0 disable switch; 1 enable switch*/
	UINT16 ucCqiIrcThrA; 	        /*CQI IRC门限值*/
}LPHY_REQ_DEM_IRC_CQI_THRA_STRU;


typedef struct
{
	LPHY_REQ_DEM_IRC_SWITCH_STRU stPdcIrcSwitch;

	LPHY_REQ_DEM_IRC_SNR_THR_STRU stPdcIrcSnrThr;

	LPHY_REQ_DEM_IRC_RUU_MODE_STRU stPdcIrcRuuMode;

	LPHY_REQ_DEM_IRC_TTI_SWITCH_STRU stPdcIrcRuuTTIswitch;

	LPHY_REQ_DEM_IRC_BL_EST_STRU stPdcIrcBlEst;

	LPHY_REQ_DEM_IRC_ADAP_THR_STRU stPdcIrcAdaptiveThr;

	LPHY_REQ_DEM_IRC_ADAP_GRANN2_STRU stPdcIrcAdaptiveGran;

	LPHY_REQ_DEM_IRC_RUU_SET0_STRU stPdcIrcRuuSet0;

	LPHY_REQ_DEM_IRC_UC_TGT_W_STRU stPdcIrcTGT_W;

	LPHY_REQ_DEM_IRC_PDC_RUU_COEF_STRU stPdcIrcRuuCoef;

	LPHY_REQ_DEM_IRC_CQI_RUU_COEF_STRU stCqiIrcRuuCoef;

    LPHY_REQ_DEM_IRC_CQI_THRA_STRU stCqiIrcThrA;

}LPHY_REQ_DEM_IRC_PDC_OM_CONFIG_STRU;

#define LPHY_REQ_DEM_IRC_PDC_OM_CONFIG_DEFAULT  		{{0,1},\
														 {0,20},\
														 {0,1},\
														 {0,1},\
														 {0,1},\
														 {0,0,0},\
														 {0,3},\
														 {0,0},\
														 {0,13},\
														 {0,1023,1023,0},\
														 {0,1023,1023,0},\
														 {0,20}}

/*LPHY_REQ_DEM_IRC_PDS_OM_CONFIG*/

typedef struct
{
    UINT16 ucPdsIrcAdapThrEn;                        /*0 disable switch; 1 enable switch*/
    UINT8 ucPdsIrcAdapThrA;
    UINT8 ucPdsIrcAdapThrB;
} LPHY_REQ_PDS_IRC_ADAP_THR_STRU;
typedef struct
{
    UINT16 ucPdsBFIrcAdapThrEn;                      /*0 disable switch; 1 enable switch*/
    UINT8 ucPdsBFIrcAdapThrA;
    UINT8 ucPdsBFIrcAdapThrB;
} LPHY_REQ_PDS_IRC_BF_ADAP_THR_STRU;

typedef struct
{
    UINT16 ucRuuModeEn;  /*0 disable switch; 1 enable switch*/
	UINT16 ucRuuMode;		/*RuuMode：0表示用CMU噪声计算，1表示用CRS计算*/
} LPHY_REQ_PDS_IRC_RUU_MODE_STRU;

typedef struct
{
    UINT16 ucPdsIrcEn;   /*0 disable switch; 1 enable switch*/
	UINT16 ucPdsIrcFlag;		/*非BF模式IRC开关*/
} LPHY_REQ_PDS_IRC_FLAG_STRU;

typedef struct
{
    UINT16 ucPdsBfIrcEn; /*0 disable switch; 1 enable switch*/
	UINT16 ucPdsBfIrcFlag;		/*BF模式IRC开关*/
} LPHY_REQ_PDS_IRC_BF_FLAG_STRU;

typedef struct
{
    UINT8 ucPDSCrsRuuCoefEn;    /*0 disable switch; 1 enable switch*/
	UINT16 usPDSCrsRuuDCoef; 	/* PDSCH CRS Ruu主对角线元素修正系数*/
	UINT16 usPDSCrsRuuNDCoef; 	/* PDSCH CRS  Ruu非主对角线元素修正系数*/
	UINT8 ucRsv[3];
} LPHY_REQ_PDS_IRC_CRS_RUU_COEF_STRU;

typedef struct
{
    UINT8 ucPDSDrsRuuCoefEn;    /*0 disable switch; 1 enable switch*/
	UINT16 usPDSDrsRuuDCoef; 	/*PDSCH DRS Ruu主对角线元素修正系数*/
	UINT16 usPDSDrsRuuNDCoef; 	/* PDSCH DRS Ruu非主对角线元素修正系数*/
	UINT8 ucRsv[3];
} LPHY_REQ_PDS_IRC_DRS_RUU_COEF_STRU;

typedef struct
{
    UINT16 ucCrsWhitenRuuSize2En;     /*0 disable switch; 1 enable switch*/
	UINT16 ucCrsWhitenRuuSize2; 	/*PDS CRS IRC颗粒度2 */
} LPHY_REQ_PDS_IRC_CRS_WHITEN_RUU_SIZE2_STRU;

typedef struct
{
    UINT16 ucDrsWhitenRuuSize2En;     /*0 disable switch; 1 enable switch*/
	UINT16 ucDrsWhitenRuuSize2; 	/*PDS DRS IRC颗粒度 2*/
} LPHY_REQ_PDS_IRC_DRS_WHITEN_RUU_SIZE2_STRU;


typedef struct
{
	LPHY_REQ_PDS_IRC_ADAP_THR_STRU stPdsIrcAdaptiveThr;
	LPHY_REQ_PDS_IRC_BF_ADAP_THR_STRU stPdsBFIrcAdaptiveThr;

	LPHY_REQ_PDS_IRC_RUU_MODE_STRU stRuuMode;

	LPHY_REQ_PDS_IRC_FLAG_STRU stPdsIrcFlag;

	LPHY_REQ_PDS_IRC_BF_FLAG_STRU stPdsBfIrcFlag;

	LPHY_REQ_PDS_IRC_CRS_RUU_COEF_STRU stPDSCrsRuuCoef;

	LPHY_REQ_PDS_IRC_DRS_RUU_COEF_STRU stPDSDrsRuuCoef;

	LPHY_REQ_PDS_IRC_CRS_WHITEN_RUU_SIZE2_STRU stPdsCrsIrcWhitenRuuSize2;

	LPHY_REQ_PDS_IRC_DRS_WHITEN_RUU_SIZE2_STRU stPdsDrsIrcWhitenRuuSize2;

}LPHY_REQ_DEM_IRC_PDS_OM_CONFIG_STRU;

#define LPHY_REQ_DEM_IRC_PDS_OM_CONFIG_DEFAULT  		{{0,0,0},\
															  {0,0,0},\
															  {0,0},\
															  {0,0},\
															  {0,0},\
															  {0,1023,1023,{0,0,0}},\
															  {0,1023,1023,{0,0,0}},\
															  {0,3},\
															  {0,3}}

//-----------------------------------------------
//  2.  DEM IND ????????
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
    UINT16 usSysFN;        /*??????*/
    UINT16 usSubFN;        /*?????  */  
    UINT16 usCellID;       /*??????*/
    UINT16 usFreqID;       /*??????*/
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
    UINT16 usSysFN;        /*??????*/
    UINT16 usSubFN;        /*?????  */  
    UINT16 usCellID;       /*??????*/
    UINT16 usTestMode;     /*??????*/

    UINT32 aulCntACKAccu[OM_UL_MAX_CELL_NUM][UL_MAX_TB_NUM];
    UINT32 aulCntNAKAccu[OM_UL_MAX_CELL_NUM][UL_MAX_TB_NUM];
    UINT32 aulCntACKPeriod[OM_UL_MAX_CELL_NUM][UL_MAX_TB_NUM];
    UINT32 aulCntNAKPeriod[OM_UL_MAX_CELL_NUM][UL_MAX_TB_NUM];
    UINT32 aulInitTransNACKNum[OM_UL_MAX_CELL_NUM][UL_MAX_TB_NUM];
    UINT32 aulInitTransTotalNum[OM_UL_MAX_CELL_NUM][UL_MAX_TB_NUM];
    UINT32 aulReTransNACKNum[OM_UL_MAX_CELL_NUM][UL_MAX_TB_NUM];
    UINT32 aulReTransTotalNum[OM_UL_MAX_CELL_NUM][UL_MAX_TB_NUM];
    UINT32 aulResidualNACKNum[OM_UL_MAX_CELL_NUM][UL_MAX_TB_NUM];
    UINT32 aulResidualTotalNum[OM_UL_MAX_CELL_NUM][UL_MAX_TB_NUM];
}LPHY_SG_DEM_PHICH_BLER_RPT_STRU;

#define TM_MODE_NUM 8
/* IND Structure define for PDSCH_THROUGHTOUT_RPT */
typedef struct __LPHY_IND_DEM_PDSCH_MIMO_SWITCH_RPT_STRU__
{
    UINT16 usSysFN;        /*??????*/
    UINT16 usSubFN;        /*?????  */
    UINT16 usReportCnt;
    UINT16 usReserved;
    UINT32 aulMimoSwitchStatArray[DL_MAX_CELL_NUM][TM_MODE_NUM];//alex ca
    LRRC_LPHY_PDSCH_TM_MODE_ENUM_UINT16 enTransMode[DL_MAX_CELL_NUM]; //[cc]
}LPHY_IND_DEM_PDSCH_MIMO_SWITCH_RPT_STRU;


/* IND Structure define for PDSCH_RB_OCCUPATION_RPT */
typedef struct __PDSCH_RB_CNT_STRU__
{
    UINT32 ulTotalRBNum;
    UINT16 ausRbCntArray[2][100];
}PDSCH_RB_CNT_STRU;

typedef struct __LPHY_IND_DEM_PDSCH_RB_OCCUPATION_RPT_STRU__
{
    UINT16 usSysFN;        /*??????*/
    UINT16 usSubFN;        /*?????  */  
    UINT16 usReportCnt;  
    UINT16 usReserved;

    PDSCH_RB_CNT_STRU astRbCnt[DL_MAX_CELL_NUM]; //alex ca
    //UINT32 aulTotalRBNum[4];//alex ca
    //UINT16 ausRbCntArray[2][2][100];//alex ca for HSO doesn't support 3 dimension array

    //UINT16 ausRbCntArrayCC0[2][100];//alex ca
    //UINT16 ausRbCntArrayCC1[2][100];//alex ca

}LPHY_IND_DEM_PDSCH_RB_OCCUPATION_RPT_STRU;


/* IND Structure define for PDSCH_MCS_RB_STAT_RPT */
typedef struct __MCS_RB_CNT_STRU__
{
    UINT16 usCwCnt[2];
    UINT16 usCwRbCnt[2];
}MCS_RB_CNT_STRU;

typedef struct __DL_MOD_CNT_STRU__
{
    UINT32 aulQPSKTotalNum[2]; //[cwo/cw1]
    UINT32 aul16QAMTotalNum[2];
    UINT32 aul64QAMTotalNum[2];
}DL_MOD_CNT_STRU;

typedef struct __LPHY_IND_DEM_PDSCH_MCS_RB_STAT_RPT_STRU__
{
    UINT16 usSysFN;        /*??????*/
    UINT16 usSubFN;        /*?????  */  
    UINT16 usReportCnt;    
    UINT16 usReserved;
    UINT32 aulTotalRBNum[DL_MAX_CELL_NUM];//alex ca
    MCS_RB_CNT_STRU astMcsRbStatArray[DL_MAX_CELL_NUM][32];//alex ca  [cc][mcs0~31]
    DL_MOD_CNT_STRU astDlMod[DL_MAX_CELL_NUM];//alex ca [CC]
}LPHY_IND_DEM_PDSCH_MCS_RB_STAT_RPT_STRU;



/* IND Structure define for dsp Interrupt duration_RPT */
typedef struct __INT_SYM_DURATION_STRU__
{
    UINT32 ulOneTimeDuration;
    UINT32 ulAverageDuration;
}INT_SYM_DURATION_STRU;

typedef struct __LPHY_IND_DEM_DSP_INT_DURATION_RPT_STRU__
{
    UINT16 usSysFN;        /*??????*/
    UINT16 usSubFN;        /*?????  */  
    UINT16 usReportCnt;    
    UINT16 usReserved;
    INT_SYM_DURATION_STRU stIntDuraArray[14];
}LPHY_IND_DEM_DSP_INT_DURATION_RPT_STRU;



/* IND Structure define for PHICH decode status RPT */
typedef struct __LPHY_IND_DEM_PHICH_DECODE_STATUS_RPT_STRU__
{
    UINT16 usSysFN;        /*??????*/
    UINT16 usSubFN;        /*?????  */  
    UINT16 usReportCnt;    
    UINT16 usPhichNum;
    UINT16 usPhichRes[2];
}LPHY_IND_DEM_PHICH_DECODE_STATUS_RPT_STRU;



//---------------------------------------------------------
//  3.  DEM debug info ????????[???????]
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
    UINT16      usSysFN;        /*??????*/
    UINT16      usSubFN;        /*?????*/    
    UINT32      ulPaylod[DEM_OM_MAX_PAYLOAD_LENGTH];
}LPHY_DEM_DEBUG_REPORT_OM_IND;


//---------------------------------------------------------
//  4.  DEM error info ????????[???????]
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
    UINT16      usSysFN;        /*??????*/
    UINT16      usSubFN;        /*?????*/    
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

    UINT16 usSysFN;        /*??????*/
    UINT16 usSubFN;        /*?????  */

    UINT16 usReportCnt;
    UINT16 usReserved;

    UINT32 ulTotalRBNum;
    UINT16 ausRbCntArray[2][100];

}LPHY_IND_DEM_PDSCH_RB_STAT_RPT_STRU;


typedef enum __LPHY_DT_MSGID_DEM_IND_ENUM__
{
    LPHY_DT_DEM_PDSCH_MCS_STAT_RPT_IND    = OM_CMD_ID(LPHY_DEM_MID,OM_TYPE_DT,0x1),
    LPHY_DT_DEM_PHICH_BLER_IND            ,
    LPHY_DT_PDSCH_TM_MODE_INFO_IND        ,
    //new add
    LPHY_DT_PDSCH_TM_SCHEME_INFO_IND      , 
    LPHY_DT_DEM_PDSCH_MCS_STAT_RPT_CA_IND ,  
    LPHY_DT_PDSCH_TM_MODE_INFO_CA_IND     ,   
    LPHY_DT_DEM_PDSCH_PRB_STAT_RPT_CA_IND    
}LPHY_DT_MSGID_DEM_IND_ENUM;





//---------------------------------------------------------
//  5.  DEM trace info ????????[???????]
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
    UINT16      usSysFN;        /*??????*/
    UINT16      usSubFN;        /*?????*/    

    PBCH_OPERATE_SRC_ENUM_UINT16 enOpSrc;
    UINT16      usOPID;        /*????ID*/
    UINT16      usCellID;      /*??????*/
    UINT16      usFreqId;      /*??????*/
    UINT16      usResult;
    UINT16      usReserved;    
}LPHY_DEM_TRACE_REPORT_OM_IND;
typedef struct __LPHY_DEM_TRACE_TIMING_UPDATA_OM_IND__
{
    UINT16      usSysFN;        /*??????*/
    UINT16      usSubFN;        /*?????*/
    UINT16      usDecodeSfn;
    UINT16      usRsd;

}LPHY_DEM_TRACE_TIMING_UPDATA_OM_IND;

//-----------------------------------------------
//  6.  DEM DT ????????
//-----------------------------------------------
/*typedef enum __LPHY_DT_MSGID_DEM_REQ_ENUM__
{
    LPHY_DT_DEM_PDSCH_MCS_STAT_RPT_REQ      = OM_CMD_ID(LPHY_DEM_MID,OM_TYPE_DT,0x1),
    LPHY_DT_DEM_PHICH_BLER_REQ              = OM_CMD_ID(LPHY_DEM_MID,OM_TYPE_DT,0x2),
    LPHY_DT_PDSCH_TM_MODE_INFO_REQ          = OM_CMD_ID(LPHY_DEM_MID,OM_TYPE_DT,0x3),
    //LPHY_DT_PDSCH_TM_SCHEME_INFO_REQ          = OM_CMD_ID(LPHY_DEM_MID,OM_TYPE_DT,0x4),
    LPHY_DT_DEM_PDSCH_PRB_STAT_RPT_REQ          = OM_CMD_ID(LPHY_DEM_MID,OM_TYPE_DT,0x5)

}LPHY_DT_MSGID_DEM_REQ_ENUM;*/



#endif
