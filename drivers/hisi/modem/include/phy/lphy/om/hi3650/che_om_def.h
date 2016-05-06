/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : che_om_def.h
  版 本 号   : 初稿
  作    者   : liweihua 174474
  生成日期   : 2011年1月12 日
  最近修改   :
  功能描述   : 定义CHE模块OM需要上报的结构体,该文件最终会交付给HiStudio使用
  函数列表   :
  修改历史   :
  1.日    期   : 2011年1月12日
    作    者   : liweihua 174474
    修改内容   : 创建文件

******************************************************************************/

/************************************************************
                     包含其它模块的头文件
************************************************************/

/************************************************************
                               宏定义
************************************************************/
#define PDPMRSDESPWINDOWNUM 3

/************************************************************
                             数据结构定义
************************************************************/

/************************************************************
                             接口函数声明
 ************************************************************/

#ifndef __CHE_OM_DEF_H__
#define __CHE_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/************************************************************
                           1. REQ命令和对应的数据结构定义
************************************************************/
/* BEGIN: Added by l00174474, 2011/6/8   问题单号:DTS2011060804183*/
#define    CHE_LCR_VELOCITY_DECI_FDD    12
#define    CHE_COR_COEF_THRE_NUM        6
#define    CHE_SFLAG_FACTOR_NUM         47
#define    CHE_LCR_AGC_CONVERT_PERIOD   131
#define    CHE_LCR_DATA_BUFFER_LENGTH   CHE_LCR_AGC_CONVERT_PERIOD - 3

typedef enum 
{
    CHE_HIGH_VELOCITY = 0,
    CHE_LOW_VELOCITY  = 1

}CHE_VELOCITY_JUDGE_ENUM;
typedef UINT16 CHE_VELOCITY_JUDGE_ENUM_UINT16;

typedef enum __LPHY_REQ_CHE__
{
    LPHY_REQ_CHE_PBCH_EN             = OM_CMD_ID(LPHY_CHE_MID, OM_TYPE_REQ, 0x0),
    LPHY_REQ_CHE_PDCCH_EN,
    LPHY_REQ_CHE_PDSCH_EN,
    LPHY_REQ_CHE_REPORT_EN,
    LPHY_REQ_CHE_STUB_SNR_FLAG_EN,           /*0x30380004*/
    LPHY_REQ_CHE_STUB_VELO_FLAG_EN,          /*0x30380005*/
    LPHY_REQ_CHE_STUB_TRMS_FLAG_EN,          /*0x30380006*/
    LPHY_REQ_CHE_STUB_INIT_SUBFRM_EN,        /*0x30380007*/
    LPHY_REQ_CHE_STUB_LAST_SUBFRM_EN,        /*0x30380008*/
    LPHY_REQ_CHE_STUB_DAGC_GAIN_EN,          /*0x30380009*/
    LPHY_REQ_CHE_STUB_BF_SCENE_FLAG_EN,      /*0x3038000a*/
    LPHY_REQ_CHE_THRED_DRS_CRS_RSRP_EN,      /*0x3038000b*/
    LPHY_REQ_CHE_THRED_DAGC_STEP_FACTOR_EN,  /*0x3038000c*/
    LPHY_REQ_CHE_THRED_VEL_CR_EN,            /*0x3038000d*/
    LPHY_REQ_CHE_THRED_VEL_LCR_EN,           /*0x3038000e*/
    LPHY_REQ_CHE_THRED_SNR_EN,               /*0x3038000f*/
    LPHY_REQ_CHE_IRC_RUU_DIAG_EN,            /*0x30380010*/
    LPHY_REQ_CHE_IRC_FIXED_N1_EN,            /*0x30380011*/
    LPHY_REQ_CHE_MBMS_SG_EN,                 /*0x30380012*/
    LPHY_REQ_CHE_MBMS_RPT_TM_AGC_ALPHA_EN,   /*0x30380013*/
    LPHY_REQ_CHE_MBMS_STUB_SNR_EN,           /*0x30380014*/
    LPHY_REQ_CHE_MBMS_STUB_VELO_EN,          /*0x30380015*/
    LPHY_REQ_CHE_MBMS_STUB_DOPPLER_EN,       /*0x30380016*/
    LPHY_REQ_CHE_MBMS_STUB_TINTERP_EN,       /*0x30380017*/
    LPHY_REQ_CHE_MBMS_STUB_ALPHA_EN,         /*0x30380018*/
    LPHY_REQ_CHE_MBMS_STUB_ALPHA_CLOSE_EN,   /*0x30380019*/
    LPHY_REQ_CHE_CRS_STUB_ALPHA_CLOSE_EN,    /*0x3038001a*/
    LPHY_REQ_CHE_STUB_BF_SNR_STEP_EN,         /*0x3038001b*/
    LPHY_REQ_CHE_CRS_STUB_ALPHA_VALUE_EN,    /*0x3038001c*/
    LPHY_REQ_CHE_MRS_TRMS_DATA_EN,
    LPHY_REQ_CHE_MRS_SNR_DATA_EN

}LPHY_CHE_REQ_ENUM;

typedef enum
{
    LPHY_REQ_CHE_DISABLE = 0,
    LPHY_REQ_CHE_ENABLE
} LPHY_CHE_REQ_ENABLE_ENUM;

typedef  UINT16  LPHY_CHE_REQ_ENABLE_ENUM_UINT16;

typedef struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usPbCheInfoEn;     /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv;
} LPHY_REQ_CHE_PBCH_EN_STRU;

typedef struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usPdcCheInfoEn;     /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv;
} LPHY_REQ_CHE_PDCCH_EN_STRU;


typedef struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usPdsCheInfoEn;     /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv;
} LPHY_REQ_CHE_PDSCH_EN_STRU;

typedef struct
{
    LPHY_REQ_CHE_PBCH_EN_STRU     stPbReportSwitch;
    LPHY_REQ_CHE_PDCCH_EN_STRU    stPdcReportSwitch;
    LPHY_REQ_CHE_PDSCH_EN_STRU    stPdsReportSwitch;

} LPHY_REQ_CHE_SWITCH_STRU;
typedef struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    enEnable;          /*1 使能上报, 0关闭上报*/
    LPHY_CA_CC_ENUM_UINT16             enCcIndex;      
} LPHY_REQ_CHE_REPORT_EN_STRU;

typedef struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCheSGEn;          /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv;
} LPHY_REQ_CHE_SG_EN_STRU;
/* BEGIN: Added by l00174474, 2011/6/8   问题单号:DTS2011060804183*/

/*Timing, CPE, AGC*/
typedef struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCheTimingCpeAgcEn;    /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv;
} LPHY_REQ_CHE_RPT_TM_CPE_AGC_EN_STRU;


/*INTP  and  Preprocessing*/
typedef struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCheIntpPrepEn;    /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv;
} LPHY_REQ_CHE_RPT_INTP_PREP_EN_STRU;


typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCheAlphaEn;    /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv0;
} LPHY_REQ_CHE_RPT_ALPHA_FILTER_EN_STRU;

/*STUB*/
typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCheSnrStubEn;
    INT16                              asSnrFlagRx[2];
    //INT16                              sSnrFlagRx0;
    //INT16                              sSnrFlagRx1;
    INT16                              sRsv0;
} LPHY_REQ_CHE_STUB_SNR_FLAG_EN_STRU;

typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCheVelStubEn;
    INT16                              sVeloFlag;
} LPHY_REQ_CHE_STUB_VELO_FLAG_EN_STRU;

typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCheTrmsStubEn;
    INT16                              sTrmsFlag;

} LPHY_REQ_CHE_STUB_TRMS_FLAG_EN_STRU;
typedef enum
{
    CHE_INIT_SUB_FRAME_FLAG = 2,
    CHE_NON_INIT_SUB_FRAME_FLAG = 3
} LPHY_CHE_INIT_SUBFRAME_FLAG_ENUM;
typedef  UINT16  LPHY_CHE_INIT_SUBFRAME_FLAG_ENUM_UINT16;

typedef enum
{
    CHE_LAST_VALID_SUBFRM_FLAG = 4,
    CHE_NON_LAST_VALID_SUBFRM_FLAG = 5
} LPHY_CHE_LAST_SUBFRAME_FLAG_ENUM;
typedef  UINT16  LPHY_CHE_LAST_SUBFRAME_FLAG_ENUM_UINT16;

typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCheInitSubFrmStubEn;
    LPHY_CHE_INIT_SUBFRAME_FLAG_ENUM_UINT16    enInitFlag;
} LPHY_REQ_CHE_STUB_INIT_SUBFRM_EN_STRU;

typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCheLastSubFrmStubEn;
    LPHY_CHE_LAST_SUBFRAME_FLAG_ENUM_UINT16    enLastFlag;
} LPHY_REQ_CHE_STUB_LAST_SUBFRM_EN_STRU;


typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCheDAgcGainStubEn;
    UINT16                             usDAgcGain;
} LPHY_REQ_CHE_STUB_DAGC_GAIN_EN_STRU;


typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCheBFSceneStubEn;
    UINT16                             usSceneFlag;

} LPHY_REQ_CHE_STUB_BF_SCENE_FLAG_EN_STRU;

/*THRESHOLD CONFIGURATION*/

typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM  usCheDCrsRsrpThreEn;
    UINT16                           usLimitThre;
    UINT16                           usRsrpThre;
} LPHY_REQ_CHE_THRED_DRS_CRS_RSRP_EN_STRU;

typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16  usCheDagcFactorEn;
    UINT16                           usDagcFactor;

} LPHY_REQ_CHE_THRED_DAGC_STEP_FACTOR_EN_STRU;

typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16  usCheCRThreEn;
    UINT16                           ausTrms01[CHE_COR_COEF_THRE_NUM];
    UINT16                           ausTrms2[CHE_COR_COEF_THRE_NUM];
} LPHY_REQ_CHE_THRED_VEL_CR_EN_STRU;

typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16  usCheLCRThreEn;
    UINT8                            aucLcrVel[CHE_LCR_VELOCITY_DECI_FDD];

} LPHY_REQ_CHE_THRED_VEL_LCR_EN_STRU;


typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16  usCheSNRThreEn;
    UINT32                           aulSFlagThre[CHE_SFLAG_FACTOR_NUM];

} LPHY_REQ_CHE_THRED_SNR_EN_STRU;

/*IRC debug switch*/
typedef struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usDiagSetZeroEn;     /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv;
} LPHY_REQ_CHE_IRC_RUU_DIAG_EN_STRU;

typedef struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usFixedN1En;         /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv;
} LPHY_REQ_CHE_IRC_FIXED_N1_EN_STRU;

/*MBMS*/
typedef struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCheMbmsSGEn;          /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv;
} LPHY_REQ_CHE_MBMS_SG_EN_STRU;

/*MBMS Timing, CPE, AGC*/
typedef struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usTimingAgcAlphaEn;    /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv;
} LPHY_REQ_CHE_MBMS_RPT_TM_AGC_ALPHA_EN_STRU;

/*STUB*/
typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usSnrStubEn;
    UINT16                             sRsv0;
    UINT16                             usTdSnrFlagRx0;
    UINT16                             usTdSnrFlagRx1;
    UINT16                             usFdSnrFlagRx0;
    UINT16                             usFdSnrFlagRx1;
    UINT16                             usAlpSnrFlagRx0;
    UINT16                             usAlpSnrFlagRx1;

} LPHY_REQ_CHE_MBMS_STUB_SNR_EN_STRU;

typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usVelStubEn;
    INT16                              sVeloFlag;
} LPHY_REQ_CHE_MBMS_STUB_VELO_EN_STRU;

typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usDoppStubEn;
    UINT16                             usDoppFlag;
} LPHY_REQ_CHE_MBMS_STUB_DOPPLER_EN_STRU;


typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usTrmsStubEn;
    UINT16                             usTInterpFlag;

} LPHY_REQ_CHE_MBMS_STUB_TINTERP_EN_STRU;

typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usAlphaStubEn;
    UINT16                             Rsv;
    UINT16                             usDemAlpha;
    UINT16                             usRuuAlpha;

} LPHY_REQ_CHE_MBMS_STUB_ALPHA_EN_STRU;


typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usMbmsAlphaCloseStubEn;
    UINT16                             Rsv;

} LPHY_REQ_CHE_MBMS_STUB_ALPHA_CLOSE_STRU;


typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCrsAlphaCloseStubEn;
    UINT16                             Rsv;
} LPHY_REQ_CHE_CRS_STUB_ALPHA_CLOSE_STRU;

typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM    enCrsStubAlphaEn;
    UINT32                      ulAlphaValue;
} LPHY_REQ_CHE_CRS_STUB_ALPHA_VALUE_STRU;


typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usBfSnrStubEn;
    UINT16                             usStep;

} LPHY_REQ_CHE_STUB_BF_SNR_STEP_STRU;

typedef struct __LPHY_REQ_CHE_MRS_TRMS_DATA_EN_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16                      usRsv;
}LPHY_REQ_CHE_MRS_TRMS_DATA_EN_STRU;

typedef struct __LPHY_REQ_CHE_MRS_SNR_DATA_EN_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16                      usRsv;
}LPHY_REQ_CHE_MRS_SNR_DATA_EN_STRU;

/************************************************************
                           2. CNF数据结构定义
************************************************************/
typedef enum __LPHY_CNF_CHE__
{
    LPHY_CNF_CHE_PBCH_EN             = OM_CMD_ID(LPHY_CHE_MID, OM_TYPE_CNF, 0x1),
    LPHY_CNF_CHE_PDCCH_EN,
    LPHY_CNF_CHE_PDSCH_EN,
    LPHY_CNF_CHE_SG_EN,
    LPHY_CNF_CHE_RPT_TM_CPE_AGC_EN,
    LPHY_CNF_CHE_RPT_INTP_PREP_EN,
    LPHY_CNF_CHE_RPT_ALPHA_FILTER_EN,
    LPHY_CNF_CHE_STUB_SNR_FLAG_EN,
    LPHY_CNF_CHE_STUB_VELO_FLAG_EN,
    LPHY_CNF_CHE_STUB_TRMS_FLAG_EN,
    LPHY_CNF_CHE_STUB_INIT_SUBFRM_EN,
    LPHY_CNF_CHE_STUB_LAST_SUBFRM_EN,
    LPHY_CNF_CHE_STUB_DAGC_GAIN_EN,
    LPHY_CNF_CHE_STUB_BF_SCENE_FLAG_EN,
    LPHY_CNF_CHE_THRED_DRS_CRS_RSRP_EN,
    LPHY_CNF_CHE_THRED_DAGC_STEP_FACTOR_EN,
    LPHY_CNF_CHE_THRED_VEL_CR_EN,
    LPHY_CNF_CHE_THRED_VEL_LCR_EN,
    LPHY_CNF_CHE_THRED_SNR_EN,
    LPHY_CNF_CHE_IRC_RUU_DIAG_EN,
    LPHY_CNF_CHE_IRC_FIXED_N1_EN,
    LPHY_CNF_CHE_MBMS_SG_EN,
    LPHY_CNF_CHE_MBMS_RPT_TM_AGC_ALPHA_EN,
    LPHY_CNF_CHE_MBMS_STUB_SNR_EN,
    LPHY_CNF_CHE_MBMS_STUB_VELO_EN,
    LPHY_CNF_CHE_MBMS_STUB_DOPPLER_EN,
    LPHY_CNF_CHE_MBMS_STUB_TINTERP_EN,
    LPHY_CNF_CHE_MBMS_STUB_ALPHA_EN

} LPH_CNF_CHE_ENUM;
/************************************************************
                           3. Sg数据结构定义
************************************************************/

typedef enum __LPHY_SG_CHE__
{
    LPHY_SG_CHE_PARA_REPORT             = OM_CMD_ID(LPHY_CHE_MID, OM_TYPE_SG, 0x0),//CHE_CHN_STATE_CALC_STRU
    LPHY_SG_CHE_TRMS_REPORT, //CHE_TRMS_REPORT_STRU
    LPHY_SG_CHE_INFO_REPORT, //CHE_INFO_STRU
    LPHY_SG_CHE_MRS_TRMS_REPORT,
    LPHY_SG_CHE_MRS_SNR_REPORT
} LPHY_SG_CHE_ENUM;

typedef struct
{
    UINT16  usCellId;
    UINT16  usSysFN;

    UINT16  usSubFN;
    UINT16  usVShift;
    UINT16  usTxAntNum;
    UINT16  usRxAntNum;

    LTE_BAND_WIDTH_ENUM_UINT16          enBandWidth;
    LTE_CP_TYPE_ENUM_UINT16             enCpMode;

    LTE_FRAME_TYPE_ENUM_UINT16          enDuplex;
    LTE_TDD_UD_CFG_ENUM_UINT16          enTddUDConfig;

    LTE_TDD_SPEC_SUBFRM_CFG_ENUM_UINT16 enSpecSubFormat;
    UINT16                              usResvered;

}  CHE_CELL_INFO_STRU;

typedef struct
{
    UINT8    ucPbChnInitFlag;
    UINT8    ucPdcChnInitFlag;
    UINT8    ucPdsChnInitFlag;
    UINT8    ucRsv;

} CHE_INIT_SUBFRM_STRU;
typedef struct
{
    UINT16   usMcsValid;
    UINT16   usMcs;
}CHE_MCS_INFO_STRU;


typedef struct  _CHE_BBP_CONFIG_INPUT
{
    CHE_CELL_INFO_STRU    stCellInfo;
    /* current subframe is init subframe*/
    UINT32                ulCurInitSubFrmFlag;
    /*next subframe is init subframe, calcu at sym12 */
    UINT32                ulPostInitSubFrmFlag;
    /*the last valid subframe,        calcu at sym12*/
    UINT32                ulLastVaSubFlag;
    /*sepcial subframe pattern 4 indication for normal cp,
    3for extend cp */
    UINT32                ulPattern4Flag;
    /*sepcial subframe pattern 0 or 5 indication
    for normal cp,  0 or 4 for extend cp*/
    UINT32                ulPattern0or5Flag;
    /*sepcial subframe pattern 9/7(NCP/ECP) indication*/
    UINT32                ulPattern9Flag;
    /*is Tdd Switch or not*/
    UINT32                ulIsTddSwitchFlag;
    /*MCS valid and value*/
    CHE_MCS_INFO_STRU stMcsInfo;

    UINT32  ulAlphaValue;
    UINT16  usLNASwitchFlag;
    UINT16  usPrevPdsActived;
	
    UINT8   ucLastPrevPdsActive;
    UINT8   ucPrevPdcActived;   /*前一个子帧PDC是否启动*/
    UINT8   ucPdcFrontTtiFlag;
	UINT8   ucPdsFrontTtiFlag;
	
	UINT8   ucPdsLastTtiFlag;
	UINT8   ucIirInitFlag;
	UINT16  usReserved;
	UINT16  asLastSnr[2];
	UINT16  usAntSwitchFlag;
} CHE_CONFIG_BBP_INPUT;

typedef struct
{
    /*config bbp interface info*/
    CHE_CONFIG_BBP_INPUT      stBbpCfgInput;

    /*init PB subframe state flag*/
    CHE_INIT_SUBFRM_STRU      stInitSubframe;


    UINT8                     ucTx01LastValSym;
    UINT8                     ucTx23LastValSym;

}CHE_INFO_STRU;

typedef struct  _CHE_TRAFFIC_CH_STRU
{

    /*DL-SCH or RAR*/
    UINT16    usCH0Type;
    /*Channel0 info*/
    UINT16    usCH0DemValid;
    UINT16    usCH0CodeWordNum;
    UINT16    usCH0MCS0;
    UINT16    usCH0MCS1;
    /*Channel1 info*/
    UINT16    usCH1DemValid;
    UINT16    usCH1MCS;
    /*Channel2 info*/
    UINT16    usCH2DemValid;
    UINT16    usCH2MCS;
    UINT16    usHarqFlag;
    /*Trms hold nv item*/
    UINT16    usTrmsHoldValue;
    UINT16    usRvs0;

} CHE_TRAFFIC_CH_STRU;

typedef struct
{
	UINT8    aucPbchTimeWiener[2]; //PBCH_PRE_SNR_HV/PBCH_PRE_SNR_LV
	UINT8    aucPbchFreqWiener[2];//PBCH_FREQ_SNR_HV/PBCH_FREQ_SNR_LV

	UINT8    aucPdcTimeWiener[2];//PDC_TIME_WIENER_SNR_HV_LTRMS/PDC_TIME_WIENER_SNR_HV_HTRMS/PDC_TIME_WIENER_SNR_LV_LTRMS/PDC_TIME_WIENER_SNR_LV_HTRMS
	UINT8    aucPdcFreqWiener[2];//PDC_FREQ_WIENER_SNR_HV_LTRMS/PDC_FREQ_WIENER_SNR_HV_HTRMS/PDC_FREQ_WIENER_SNR_LV_LTRMS/PDC_FREQ_WIENER_SNR_LV_HTRMS
	
	UINT8    aucPdcInterp[2];//PDC_INTERP_WIENER_SNR_HV_LTRMS/PDC_INTERP_WIENER_SNR_HV_HTRMS/PDC_INTERP_WIENER_SNR_LV_LTRMS/PDC_INTERP_WIENER_SNR_LV_HTRMS

	UINT8    aucPdsTimeWiener[2];//PDS_TIME_WIENER_SNR_HV_LTRMS/PDS_TIME_WIENER_SNR_HV_HTRMS/PDS_TIME_WIENER_SNR_LV_LTRMS/PDS_TIME_WIENER_SNR_LV_HTRMS
	
	UINT8    aucPdsFreqWiener[2];//PDS_FREQ_WIENER_SNR_HV_LTRMS/PDS_FREQ_WIENER_SNR_HV_HTRMS/PDS_FREQ_WIENER_SNR_LV_LTRMS/PDS_FREQ_WIENER_SNR_LV_HTRMS
	UINT8    aucPdsInterp[2];//PDS_INTERP_WIENER_SNR_HV_LTRMS/PDS_INTERP_WIENER_SNR_HV_HTRMS/PDS_INTERP_WIENER_SNR_LV_LTRMS/PDS_INTERP_WIENER_SNR_LV_HTRMS
	
	UINT8    ucPbchSnrFlag;//PBCH_SNR_HV/PBCH_SNR_LV
	UINT8    ucPdcSnrFlag;//PDC_SNR_HV/PDC_SNR_LV
	UINT8    ucPdsSnrFlag;//PDS_SNR_HV/PDS_SNR_LV
	UINT8    ucCqiSnrFlag;//CQI_SNR_HV/CQI_SNR_LV

	UINT8    ucVSnrFlag;//
	UINT8    ucIirSnrFlag;
    UINT8    aucSflagRx[2];       /*Sflag Rx0*/
    
	UINT8    aucCsiFreqWiener[2];//PDS_TIME_WIENER_SNR_HV_LTRMS/PDS_TIME_WIENER_SNR_HV_HTRMS/PDS_TIME_WIENER_SNR_LV_LTRMS/PDS_TIME_WIENER_SNR_LV_HTRMS
	UINT16   usReserved;
} CHE_SNR_OUTPUT_INFO_STRU;
typedef struct
{
    UINT32  aulWeightPowData[CHE_LCR_DATA_BUFFER_LENGTH];
    INT8    acSignPowerDiff[CHE_LCR_DATA_BUFFER_LENGTH];
    UINT32  ulLastApaFilPow;
    UINT32  ulAveragePower24U;             /*不使用PAR方法时需要保留的平均功率值，
                                                     对Alpha滤波之后的值进行统计*/
    UINT32  ulMaxPower;
    UINT16  usParOld;
    UINT16  usParNew;
    
    UINT16  usPAR;
    UINT16  usReserved;
    
    UINT8   ucAwgnFlag;                     /*峰均比判别后，得出是否是AWGN。 如是，则在速度判决时判定为低速*/
    UINT8   ucLcrOld;
    UINT8   ucTddInterpOldIndex;
    UINT8   ucTddInterpIndex;//ucTddInterpIndex
    
    UINT8   ucLcrAgcCalcFSM;
    UINT8   ucAgcCalcBuffNum;
    UINT8   ucLcrNew;
    UINT8   ucLCR;
    
    UINT8   ucLCRVelocity;
    UINT8   ucTooLowPow;
    UINT8   ucLcrTddValidFlag;
    UINT8   ucLcrGapValidFlag;   
    
	UINT8   ucInsertLcr;
	UINT8   ucInsertAgcCounter;
	UINT8   ucInsertAgcFlag;
    UINT8   ucReserved;
    //UINT8   ucLcrSmoothFSM;                 /*平滑的FSM*/
	//UINT8   ucLcrUpdateFlag;
	//UINT8   ucCrUpdateFlag;

    //UINT32  ulAgcGainProduct;               /*AGC的连续乘的结果*/
    //UINT16  usTddIntpGapState;              /*GAP 的起始状态*/
    //UINT16  usNxtSubFrm;                    /*下一个需要进入的子帧*/

}CHE_LCR_VEL_INFO_STRU;
typedef struct
{
    INT32    alCheTimeCorrOutAcc[2];
    INT32             lTDRxAverage;
    INT32    alCheFreqCorrOutAcc[2];
    INT32             lFDRxAverage;
	INT16    sCorrVelocityFlag;
	INT16   sCRVForPmch;
}CHE_CORR_VELO_INPUT_STRU;

typedef struct  _CHE_VELOCITY_FLAG_STRU
{
    /*LCR 和 CR 判断之后的速度标志,速度档位判断依据*/
    INT32     lRawVelocity;
    /*PDCCH time domain preprocessing velocity*/
    UINT8    ucPdcTimeWienerVFlag;
    UINT8    ucPdsTimeWienerVFlag;
    UINT8    ucPdcTimeIntrepVFlag;
    UINT8    ucPdsTimeIntrepVFlag;
    /*velocity for selecting RS number*/
    UINT8    ucPreVelocityFlag;
    /*IIR Filtering*/
    UINT8    ucIirVFlag;
    /*velocity Flag for snr estimation*/
    UINT8    ucSnrVFlag;
    /*PDC noise whiten velocity flag*/
    //UINT8    ucPdcWhitenVFlag;
    /*PDS noise whiten velocity flag*/
    UINT8    ucPdsWhitenVFlag;
    /*CQI noise whiten velocity flag*/
    UINT8    ucCqiWhitenVFlag;
    /*Pbch noise whiten velocity flag*/
    //UINT8    ucPbchWhitenVFlag;
    /*Timing velocity*/
    UINT8    ucTimingVFlag;
    /*rsv*/
    //UINT8    aucRsv[3];

} CHE_VELOCITY_FLAG_STRU;
typedef struct
{
    UINT32    aulRsrpAcc[2];       /* rsrp0 Accumlation for 80ms*/
    UINT32    aulPnAcc[2];          /* noise Accumlation for 80ms*/
    UINT32    ulCounter;        /* Accumlation counter including UP and DOWN slot for TDD,  all downlink slot for FDD*/
} CHE_SNR_INPUT_INFO_STRU;
typedef struct
{
    UINT32    aulCqiTimeFactor[2];
    UINT32    aulCqiFreqFactor[2];
    UINT16    usTtiInterFlag;
    UINT16    usNoiseMulFactor;
}CHE_CQI_FACTOR_STRU;

typedef struct
{
    /*Trms calculation input*/
    CHE_TRAFFIC_CH_STRU       stTrafficChInPut;

    /*SNR calculation output*/
    CHE_SNR_OUTPUT_INFO_STRU  stSnrOutPut;

	CHE_LCR_VEL_INFO_STRU     stLcrVelInput;
    /*相关系数的速度输入数据*/
    CHE_CORR_VELO_INPUT_STRU    stCorrVelInPut;
    /*velocity calculation output*/
    CHE_VELOCITY_FLAG_STRU    stVelFinalFlag;

    /*SNR calculation input*/
    CHE_SNR_INPUT_INFO_STRU   stSnrInPut;

    /*CQI Factor*/
    CHE_CQI_FACTOR_STRU       stCqiFactor;

    /*相关系数的速度输出结果*/
    /*Trms output for pdc and pds*/
    UINT32    ulCheTrmsFlag;
    /*doppler estimation output*/
    UINT32    ulDopplerFlag;
    UINT16    us80msTimerCounter;
    UINT16    us80msTimerInd;
	UINT8     enCcIndex;
    UINT8     ucReserved;
    UINT16    usReserved;

} CHE_CHN_STATE_CALC_STRU;
typedef struct
{
    /*Trms calculation input*/
    CHE_TRAFFIC_CH_STRU       stTrafficChInPut;
    /*Trms output for pdc and pds*/
    UINT32    ulCheTrmsFlag;
	UINT8     enCcIndex;
    UINT8     ucReserved;
    UINT16    usReserved;
    
}CHE_TRMS_REPORT_STRU;

	
typedef struct __CHE_MRS_DELAYSPREAD_DATA_STU__
{
	
	UINT8  ucPDPPARAlphaFirst;	 //Flag for first PARalpha calculation
	UINT8  ucWinValidFlag[PDPMRSDESPWINDOWNUM];
	UINT8  ucWin1NoValidPath;  //set to 1 means the first window has no valid path
	UINT8  ucWinNoValidPath;   //set t01 means the nfft window has no valid path
	UINT8  ucWinProtectFlag_All;  //nfft windows's Protect Flag.
	UINT8  ucTrmsFlag;	 // Output: TrmsFlag   4u
	UINT8  ucWinProtectFlag[PDPMRSDESPWINDOWNUM];  //three windows protect flag
	UINT8  ucReserved0;

	UINT16 usPDPPeakWidth;		//PDP peak's bit width
	UINT16 usPDPRtShiftValue;	//PDP's Right shift value  23u->17u NSAU
	UINT16 usPDPPAR[PDPMRSDESPWINDOWNUM];		//11u
	UINT16 usPDPPARAlpha[PDPMRSDESPWINDOWNUM];	//11u
	UINT16 usPDPPARAlphaLast[PDPMRSDESPWINDOWNUM]; //13u	
	UINT16 ucReserved1;
	
	UINT32 ulPDPPeak[PDPMRSDESPWINDOWNUM];		 //23u
	UINT32 ulPDPAverage[PDPMRSDESPWINDOWNUM];	//18u
	UINT32 ulPowerThrehold1[PDPMRSDESPWINDOWNUM];  //Valid Path Threhold1, one per window, 23u
	UINT32 ulPowerThrehold2;   //Valid Path Threhold2, 23u
	UINT32 ulWin1PathSum;	 //window 1's valid path power sum
	UINT32 ulWin1PathMom1;	//window 1's valid path moment 1
	UINT32 ulWin1PathMom2;	//window 2's valid path moment 2
	UINT32 ulWinPathSum;   //nfft window's valid path power sum
	UINT32 ulWinPathMom1;  //nfft window's valid path moment1
	UINT32 ulWinPathMom2;  //nfft window's valid path moment2
} CHE_MRS_DELAYSPREAD_DATA_STU;
	
typedef struct	 __CHE_MRS_SNR_OUT_STU__    //PMCH SNR estimation result
{
	UINT16 usPMCHFSNRType[2];
	UINT16 usPMCHTSNRType[2];
	UINT16 usPMCHAMSNRType[2];
	UINT16 usAGCMtoM;
	UINT16 usReserved;
	
	UINT32 ulMDAGCFGain;
	UINT32 ulSDAGCFGain;
	UINT32 aulAccMRSPower[2];
	UINT32 ulURSRP[2];
	UINT32 ulMRSRP[2];
	UINT32 ulAGCCRSRP[2];
	UINT32 ulAGCNoise[2];
} CHE_MRS_SNR_OUT_STU;

typedef struct	 __CHE_MRS_VELOCITY_OUT_STU__    //PMCH SNR estimation result
{
	INT16 usOutVelocityOutFlag;
	UINT16 usOutDopplerFlag;
	INT16 usOutSNRVFlag;
    UINT16 usReserved;
} CHE_MRS_VELOCITY_OUT_STU;


/************************************************************
                           3. Ind数据结构定义
************************************************************/
typedef enum __LPHY_IND_CHE__
{
    LPHY_IND_CHE_PBCH_EN             = OM_CMD_ID(LPHY_CHE_MID, OM_TYPE_IND, 0x1),
    LPHY_IND_CHE_PDCCH_EN,
    LPHY_IND_CHE_PDSCH_EN,
    LPHY_IND_CHE_MBMS_SG_EN,             /*0x303f0008*/
    LPHY_IND_CHE_MBMS_RPT_TM_AGC_ALPHA   /*0x303f0009*/
} LPHY_IND_CHE_ENUM;


typedef struct __LPHY_CHE_IND_PHY_CHANNEL_REPORT_
{
    UINT8       ucActiveFlag;                 /*激活标志*/
    UINT8       ucRsv0;
    UINT16      usSFN;                        /*系统帧号*/
    UINT16      usSubFN;                      /*子帧号*/
    UINT8       ucRsSelVel;                   /*RS选择的速度*/
    UINT8       ucPdcPreVel;                  /*PDC的预处理速度*/
    UINT32      aCheInfo[20];                 /*总的输入信息*/
    UINT32      aPhChInfo[40];                /*物理信道寄存器信息*/
} LPHY_IND_CHE_PHY_CHANNEL_REPORT_STRU;

#if 0
typedef struct
{
    UINT16  usDoppler;                    /*多普勒频移               */
    UINT16  usBfSnrRx0;                   /*BF SNR档位Rx0            */
    UINT16  usBfSnrRx1;                   /*BF SNR档位Rx1            */
    UINT16  usTrms;                       /*时延估计档位索引         */
    UINT16  usNonBfSnrRx0;                /*非BF模式SNR档位Rx0       */
    UINT16  usNonBfSnrRx1;                /*非BF模式SNR档位Rx1       */
    UINT16  usVelocityFlag;               /*速度指示                 */
    INT16   sVelofCorr;                   /*相关系数的速度判别结果   */
    INT32   lTDCorrCoef;                  /*相关系数的时域相关系数   */
    INT32   lFDCorrCoef;                  /*相关系数的频域相关系数   */
    INT16   sOutVelocity;                 /*raw outvelocity*/
    UINT16  usLcrPar;
    UINT32  ulDrsRsrpRx0;                 /*DRS RSRP0*/
    UINT32  ulDrsRsrpRx1;
    INT16   sRsv0;
    INT16   sRsv1;
    UINT16  usRsv2;
    UINT16  usRsv3;
    INT32   lRsv4;
    INT32   lRsv5;
} LPHY_IND_CHE_SG_EN_STRU;
#endif
typedef struct
{
    UINT8   ucTimeSnrRx0;                 /*TSNR档位Rx0             */
    UINT8   ucTimeSnrRx1;                 /*TSNR档位Rx1             */
    UINT8   ucFreqSnrRx0;                 /*FSNR档位Rx0             */
    UINT8   ucFreqSnrRx1;                 /*FSNR档位Rx1             */

    UINT8   usDoppler;                    /*Doppler指示              */
    UINT8   usTrms;                       /*时延估计档位索引         */
    INT8    Rsv0;
    INT8    Rsv1;

    INT32   lTDCorrCoef;                  /*MRS相关系数的时域相关系数   */
    INT32   lFDCorrCoef;                  /*MRS相关系数的频域相关系数   */

    INT8    cCrvForPmch;                  /*CRS相关系数的速度判别结果  */
    INT8    cMCrv;                        /*MRS相关系数的速度判别结果  */
    INT8    cCfv;                         /*CFV  */
    INT8    cIirVelFlag;                  /*速度估计总档位  */

    INT16   Rsv2;
    INT16   Rsv3;

} LPHY_IND_CHE_EMBMS_SG_EN_STRU;

typedef struct
{
    INT16    sLeftTimingDiff;
    INT16    sRightTimingDiff;
    UINT16   usAgcLeftAmpgainRx0;
    UINT16   usAgcLeftAmpgainRx1;
    UINT16   usAgcLeftPowGainRx0;
    UINT16   usAgcLeftPowGainRx1;
    UINT16   usRuuAlphaVal;
    UINT16   usDemAlphaVal;

} LPHY_IND_CHE_MBMS_RPT_TM_AGC_ALPHA_EN_STRU;

/************************************************************
                           4. TRACE数据结构定义
************************************************************/

/************************************************************
                    5. ERROR数据结构定义
************************************************************/

typedef enum
{
    LPHY_CHE_ERR_CELL_ID         = OM_CMD_ID(LPHY_CHE_MID, OM_TYPE_ERROR, 0x1),
    LPHY_CHE_ERR_SUBFRAME_NUM,
    LPHY_CHE_ERR_NOISE_ZERO,
    LPHY_CHE_ERR_SFLAG_OVERFLOW,
    LPHY_CHE_ERR_VEL_OVERFLOW,
    LPHY_CHE_ERR_OM_REQ_ID,
    LPHY_CHE_ERR_MAX_QM_MODE,
    LPHY_CHE_ERR_OM_DUMMY_FUNC,
    LPHY_CHE_ERR_EXTRA_PA_IND,
    LPHY_CHE_ERR_PA_INDEX,
    LPHY_CHE_ERR_QM_VALUE,
    LPHY_CHE_ERR_FREQ_OFFSET,
    LPHY_CHE_ERR_2D_FLAG

}  LPHY_CHE_OM_ERROR_ENUM;

typedef UINT32  LPHY_CHE_OM_ERROR_ENUM_UINT32;

typedef struct
{
    UINT16      usSysFrmNum;    /*系统帧号*/
    UINT16      usSubFrmNum;    /*子帧号*/
    UINT16      usSymbNum;      /*当前符号数*/
    UINT16      usReserved;
    UINT32      ulData0;
    UINT32      ulData1;
    UINT32      ulData2;

} LPHY_CHE_OM_ERROR_STRU;

typedef  struct
{
    INT16  sDRS_SnrP5P7Rx0;
    INT16  sDRS_SnrP5P7Rx1;
    INT16  sDRS_SnrP8Rx0;
    INT16  sDRS_SnrP8Rx1;
}CHE_DRS_SNR_STRU;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CHE_OM_DEF_H__ */
