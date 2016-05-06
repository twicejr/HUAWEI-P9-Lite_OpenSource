/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
 文 件 名   : AFC.h
 版 本 号   : 初稿
 作    者   : Shen Guang
 生成日期   : 2010年12月23日
 最近修改   :
 功能描述   : AFC的头文件
 函数列表   :
 修改历史   :
 1.日    期   : 2010年12月23日
   作    者   : Shen Guang
   修改内容   : 创建文件

 2.日    期   : 2011年06月27日
   作    者   : Shen Guang
   修改内容   : [DTS2011062706076]AFC OM定义使用枚举变量，便于hso显示

 3.日    期   : 2011年07月04日
   作    者   : Shen Guang
   修改内容   : [DTS2011070403581]AFC OM优化
 -------------------------------------------------------------------------------
 4.日    期  : 2011年8月09日
   作    者   : Shen Guang
   修改内容   : DTS2011090300756 规避BBP邻区AFC问题
 5.日    期  : 2012年2月3日
   作    者   : Shen Guang
   修改内容   : DTS2012020200427 邻区AFC  Pdm计算错误
 6.日    期   : 2012年02月25日
   作    者   : shenguang
   修改内容   : [DTS2012020505442]重选切换时AFC备份累计频偏

******************************************************************************/
#ifndef __AFC_OM_DEF_H__
#define __AFC_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */


/************************************************************
                     包含其它模块的头文件
************************************************************/
#include "lte_nv_para_define.h"             /**/

#include "rfe_om_def.h"
/************************************************************
                               宏定义
************************************************************/

#define AFC_MAX_NCELL_PER_FREQ_NUM     3
#ifndef LPHY_MAX_RX_ANTENNA_NUM
#define LPHY_MAX_RX_ANTENNA_NUM   4
#endif
#define AFC_MAX_RS_WIN_LEN                 (130)
#ifndef LPHY_BBP_SHIFT_NUM
#define  LPHY_BBP_SHIFT_NUM  2/* that is (LPHY_MAX_RX_ANT_NUM/LPHY_MAX_RX_ANT_NUM)*/
#endif

#define AFC_PDM_WINDOW_LEN  128

#define TL_DCXO_POLY_COEF_NUM_SG     (4)          /*TL_DCXO_POLY_COEF_NUM*/

#define AFC_HST_MODE
//#define MLAFC_DEF
//#define MLAFC_TEST_ONLY

/************************************************************
                             数据结构定义
************************************************************/

/************************************************************
                             接口函数声明
 ************************************************************/


/************************************************************
                           1. REQ命令和对应的数据结构定义
************************************************************/
typedef enum
{
    LPHY_REQ_AFC_REPORT_ENA         = OM_CMD_ID(LPHY_AFC_MID, OM_TYPE_REQ, 0x0),
    LPHY_REQ_AFC_PD_STATUS_ENA,
    LPHY_REQ_AFC_LOOP_STATE_ENA,
    LPHY_REQ_AFC_FIXED_PDM_ENA,
    LPHY_REQ_AFC_FILTER_STEP_SELECTION_ENA,
    LPHY_REQ_AFC_FIXED_FILTER_STEP_ENA,
    LPHY_REQ_NC_AFC_REPORT_ENA,
    LPHY_REQ_MBMS_STUB_ENA,
    LPHY_REQ_AFC_TEMP_COMP_ENA,
    LPHY_REQ_AFC_HST_ENA,
    LPHY_REQ_AFC_HST_OPEN_ENA,
    LPHY_REQ_AFC_ML_OPEN_ENA,
    LPHY_DT_AFC_REPORT_REQ          = OM_CMD_ID(LPHY_AFC_MID, OM_TYPE_REQ, 0x100),
}LPHY_REQ_AFC_ENUM;

typedef enum
{
    AFC_OM_SWITCH_OFF = 0,
    AFC_OM_SWITCH_ON,
}AFC_OM_SWITCH_ENUM;
typedef UINT16 AFC_OM_SWITCH_ENUM_UINT16;

typedef struct
{
   AFC_OM_SWITCH_ENUM_UINT16    enNcAfcReportEn;
}LPHY_REQ_NC_AFC_REPORT_ENA_STRU;

typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16      usFixedPDMEn;    /*1 使能固定PDM*/
    UINT16      usFixedPDM;      /*1 固定PDM值*/
}LPHY_REQ_AFC_FIXED_PDM_ENA_STRU;

typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16   enAfcMbmsStubEn;
}LPHY_REQ_AFC_MBMS_STUB_ENA_STRU;

// Define the struct bits
typedef struct
{
    UINT32    CpSel               : 1   ; // [0]
    UINT32    DtxcpSel            : 1   ; // [1]
    UINT32    PssSel              : 1   ; // [2]
    UINT32    ForceOL             : 1   ; // [3]
    UINT32    Reserved            : 28  ; //[31..4]
} AFC_OLPD_SEL_BITS_STRU;

typedef union
{
    AFC_OLPD_SEL_BITS_STRU  bits;

    // Define an unsigned member
    UINT32    ulOLPDSel;

} AFC_OLPD_SEL_UNION;


typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16      enOLPDSelEn;    /*1 使能外环鉴频模式*/
    AFC_OLPD_SEL_UNION             unOPLDFlag;      /*1 外环鉴频模式*/
}LPHY_REQ_AFC_OLPD_SELECTION_ENA_STRU;

typedef enum
{
    AFC_KLOW_SELECTION  = 0,
	AFC_KHIGH_SELECTION = 1,
}AFC_FILTER_STEP_MODE_ENUM;
typedef UINT16 AFC_FILTER_STEP_MODE_ENUM_UINT16;
typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16             enFilterStepSelEn;    /*1 使能选择滤波步长模式*/
    AFC_FILTER_STEP_MODE_ENUM_UINT16      enFilterStepMode;      /*1 滤波步长模式*/
}LPHY_REQ_AFC_FILTER_STEP_SELECTION_ENA_STRU;

typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16      enFixedFilterStepEn;    /*1 使能固定滤波步长*/
    UINT16                         usFixedFilterStep;      /*1 固定滤波步长值*/
}LPHY_REQ_AFC_FIXED_FILTER_STEP_ENA_STRU;

typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16 enReportEn;    /*1 使能AFC状态上报*/
    UINT16 usRsv;
}LPHY_REQ_AFC_REPORT_ENA_STRU;

typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16 enReportEn;    /*1 使能AFC状态上报*/
    UINT16 usRsv;
}LPHY_REQ_AFC_UL_ENA_STRU;

typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16 enReportEn;    /*1 使能AFC状态上报*/
    UINT16 usRsv;
}LPHY_REQ_AFC_HST_REPORT_ENA_STRU;

typedef struct
{
    AFC_OM_SWITCH_ENUM                  enDebugEn;    /*1 使能AFC状态上报*/
}LPHY_REQ_AFC_LOOP_STATE_ENA_STRU;

typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16           enPDStatusEn;
}LPHY_REQ_AFC_PD_STATUS_ENA_STRU;

typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16           enReportEn;    /*1 使能AFC温补功能*/
}LPHY_REQ_AFC_TEMP_COMP_ENA_STRU;


typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16           enHstEn;       /* fixed to 1 for lab-test only, to get a better high speed(such as 250km/h) performance. */
    UINT16                              usAfcAccFoReadPeriod;
    INT32                               lHstVelThrsh;
    UINT16                              usTempDelta;
    UINT16                              usTestHstEn;
    INT32                               lFoVarThresh;
    UINT32                              ulLowThredCounter;
}LPHY_REQ_AFC_HST_ENA_STRU;

typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16           enHstOpenEn;
    UINT16                              usRev;
}LPHY_REQ_AFC_HST_OPEN_ENA_STRU;

typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16           enMlOpenEn;
    UINT16                              usRev;
}LPHY_REQ_AFC_ML_OPEN_ENA_STRU;

typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16           enRficFreqEn;
    UINT16                              usRev;
}LPHY_REQ_AFC_RFIC_FREQ_ENA_STRU;

typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16           enSccTpaEn;
    UINT16                              usRev;
}LPHY_REQ_AFC_SCC_TPA_ENA_STRU;


/************************************************************
                           2. CNF数据结构定义
************************************************************/

typedef enum
{
    AFC_SCC_EVT_LS_SCC_INIT = 1,
    AFC_SCC_EVT_INIT_START_SERVER_CELL,
}AFC_SCC_EVT_ENUM;
typedef UINT16 AFC_SCC_EVT_ENUM_UINT16;


typedef enum
{
    AFC_RUN_STATE = 1,              /*AFC周期鉴频启动*/
    AFC_STOP_STATE,                 /*AFC周期鉴频停止*/
} AFC_STATE_ENUM;
typedef UINT16 AFC_STATE_ENUM_UINT16;

typedef enum
{
    AFC_IN_CYCLE_UNLOCK = 0,             /*AFC内环失锁*/
    AFC_IN_CYCLE_LOCK = 1,           /*AFC内环锁定*/
} AFC_LOOP_STATE_ENUM;
typedef UINT16 AFC_LOOP_STATE_ENUM_UINT16;

typedef enum
{
    AFC_OL_STOP = 0,              /*AFC外环鉴频停止*/
    AFC_TDPD_CP = 1,              /*AFC外环 CP鉴频*/
    AFC_TDPD_DTXCP  = 2,          /*AFC外环 DTXCP鉴频*/
    AFC_TDPD_PSS  = 3,            /*AFC外环 PSS鉴频*/
} AFC_OLPD_MODE_ENUM;
typedef UINT16 AFC_OLPD_MODE_ENUM_UINT16;

typedef enum
{
    AFC_RSPD = 0,
    AFC_OLPD_CP,
    AFC_OLPD_DTX,
    AFC_OLPD_PSS,
}AFC_PD_TYPE_ENUM;
typedef UINT16   AFC_PD_TYPE_ENUM_UINT16;

typedef enum
{
    AFC_NORMAL_TMPERATURE,
    AFC_NON_NORMAL_TMPERATURE
}AFC_TMPERATUR_RANGE_ENUM;
typedef UINT16 AFC_TMPERATUR_RANGE_ENUM_UINT16;

typedef enum
{
    AFC_HIGH_DRX_PERIOD,
    AFC_LOW_DRX_PERIOD
}AFC_DRX_PERIOD_ENUM;
typedef UINT16 AFC_DRX_PERIOD_ENUM_UINT16;

typedef enum
{
    DCXO_TC_AFCFREQPPM = 0,
    DCXO_TC_POLYCOEFF,
    DCXO_TC_DEFAULTCOEFF,
    DCXO_TC_BUTT
} DCXO_TC_OM_REPORT_MODE;
typedef UINT16 DCXO_TC_OM_REPORT_MODE_UINT16;

/*相关系数门限指示，供RS和CP使用*/
typedef struct
{
    UINT16    usCcInd;                   //相关系数门限指示
    UINT16    usCCPassThrdCnt;          //通过门限2的次数
}AFC_CC_STAT_STRU;

typedef struct
{
    INT32    lReal;//复数的实部
    INT32    lImag;//复数的虚部
}AFC_COMPLEX_STRU;

typedef struct
{
    UINT32    ulCoPower;//相关系数分子部分
    UINT32    ulPower;//相关系数分母部分
}AFC_CC_STRU;

/*RS相关系数门限指示*/
typedef struct
{
    UINT16    usThrd1;     /*门限1*/
    UINT16    usThrd2;     /*门限2*/
    UINT16    usThrd3;     /*门限3*/
    UINT16    usThrd4;     /*门限3*/
    UINT16    usThrd5;     /*门限3*/
    UINT16    usThrd6;     /*门限3*/
    UINT16    usThrd7;     /*门限3*/
    UINT16    usThrd8;     /*门限3*/
}AFC_RSCC_THRE_STRU;

typedef struct
{
    UINT16                        usThreshold;
    UINT16                        usWinLen;
    UINT16                        usDataNum; /* 锁定窗中鉴频数据个数*/
    AFC_LOOP_STATE_ENUM_UINT16    enAFCLoopCurState;//AFC环路状态，内环失锁，内环锁定
}AFC_LOCK_STATE_STRU;


typedef struct
{
    AFC_LOCK_STATE_STRU           stIlUnlockState;

    UINT16                        usRemainFOWinLen;
    UINT16                        usRemainFreqNum; /* 残留频偏窗中鉴频数据个数*/
    UINT16                        usRemainFreqLevel;  //残留频偏分档指示
    UINT16                        usLockToUnFlag;
}AFC_LOCK_PARA_STRU;
/************************************************************
                           3. Sg数据结构定义
************************************************************/

typedef enum
{
    LPHY_SG_AFC_REPORT_ENA         = OM_CMD_ID(LPHY_AFC_MID, OM_TYPE_SG, 0x0),
    LPHY_SG_NC_AFC_REPORT_ENA,
    LPHY_SG_AFC_PCC_REPORT_ENA,
    LPHY_SG_AFC_SCC0_REPORT_ENA,
    LPHY_SG_AFC_SCC1_REPORT_ENA,
    LPHY_SG_AFC_SCC2_REPORT_ENA,
    LPHY_SG_AFC_INIT_PHASE_PCC_ENA,
    LPHY_SG_AFC_INIT_PHASE_SCC_ENA,
	LPHY_SG_AFC_UL_REPORT_ENA,
	LPHY_SG_AFC_HST_FO_ENA,
    LPHY_SG_AFC_HST_TEMP_ENA,
	LPHY_SG_AFC_DCXO_TC_ENA,
    LPHY_SG_AFC_DCXO_TC_INTERFACE_ENA,
}LPHY_SG_AFC_ENUM;

typedef struct
{
    UINT16    usCC;
    UINT16    usCCAlpha;
}AFC_ALPHA_FLT_STRU;

typedef struct
{
    AFC_ALPHA_FLT_STRU  stAlphaA;//相关系数分子作限幅的结果,算法图中,A/C
    AFC_ALPHA_FLT_STRU  stAlphaB;//相关系数分子未作限幅的结果,算法图中,B/D
}AFC_ALPHA_STRU;

typedef struct
{
    UINT16                   usAlphaStateFlag;//Alpha滤波初始化标志
    UINT16                   usReserved;
    AFC_ALPHA_STRU           astAlpha[LPHY_MAX_RX_ANTENNA_NUM];                 /*天线0、1的CP Alpha滤波结果*/
}AFC_ALPHA_DATA_STRU;
typedef enum
{
    AFC_PD_UNDONE = 0,
    AFC_PD_DONE,
    AFC_PD_INVALID ,
}AFC_PD_DONE_ENUM;
typedef UINT16 AFC_PD_DONE_ENUM_UINT16;

/*CP相关系数门限指示*/
typedef struct
{
    UINT16    usThrd1;     /*门限1*/
    UINT16    usThrd2;     /*门限2*/
    UINT16    usThrd3;     /*门限3*/
    UINT16    usThrd4;     /*门限4*/
    UINT16    usThrd5;     /*门限5*/
    UINT16    usreserved;
}AFC_CPCC_THRE_STRU;

/**/
typedef struct
{
    AFC_CC_STAT_STRU      astRsCCind[LPHY_MAX_RX_ANTENNA_NUM];    /*天线0、1的RS相关系数门限指示*/
    AFC_RSCC_THRE_STRU    stRSCCThre;
    UINT16                ausCCFlag[LPHY_MAX_RX_ANTENNA_NUM];     /*残留频偏指示*/

    UINT16                usRSCCIndMax;           /*两天线内环环CCInd中的最大值*/
    UINT16                usCCFlagMax;            /*两天线CCFlag中的最大值*/
    UINT16                usRSCCIndMin; /* need size alignment  */
    UINT16                usRsv;
}AFC_CC_IND_STRU;

typedef struct
{
    UINT16    usIndex;
    UINT16    usCounter;
    UINT16    usIndexLow;
    UINT16    usReserved;
}AFC_KLOWSNR_STRU;

typedef struct
{
    UINT16    usFOHighThreshold;
    UINT16    usFOLowThreshold;
    UINT16    usAdjustStpHigh;
    UINT16    usAdjustStpLow;
}AFC_KHIGHSNR_CFG_STRU;

typedef struct
{
    INT16                         sFilterInFOest;
    UINT16                        usFilterStep;
    UINT16                        usLoopAdjustStepLimit;
    UINT16                        usFilterInCCind;
    INT32                         lCurFOAdj;    //当前频偏调整量
    INT32                         lAccFO;       //频偏调整量累加值
    INT32                         lRemainFO;    //v8r1添加残留频偏变量  xuyoujiang
    INT16                         asRSLockWin[AFC_MAX_RS_WIN_LEN];   /* 窗中rs鉴频数据 */
    //UINT16                        *pusRemainFOThresh;
    AFC_KLOWSNR_STRU              stKlowSNR;
    AFC_KHIGHSNR_CFG_STRU         stKHighSNR;
    /*环路状态*/
    AFC_LOCK_PARA_STRU            stLockPara;
    INT32                         OutLoopFilterHz;
    UINT16                        usReadPos;
    UINT16                        usRsv;
}AFC_LOOP_FILTER_STRU;
typedef struct
{
    UINT16                        usCurPDM;     //环路输出频偏
    UINT16                        usInitPDM;

    /* BEGIN: Added by s00175552, 2011/9/24   问题单号:DTS2011083102976*/
    UINT16                        usMultiModePdm;
    UINT16                        usPDMConfig;
    /* END: Added by s00175552, 2011/9/24   问题单号:DTS2011083102976*/
    INT32                         lInitF0;      //初始频偏
    INT32                         lCsInitF0;      //初始频偏
    INT32                         lInitF0Compensation;      //初始频偏
    UINT32                        ulDeltFOCompensation;
    INT32                         lRFLoopFilterPCCIni;
    INT32                         lRFLoopFilterPCCCur;
    UINT16                        usHTrainFlag;
    UINT16                        usXOResetFlag;/* for SINGLE_XO only */
    INT32                         lOutXOAdjustHz;/* for the time RF open */
    UINT32                        ulOutPLLAdjust;/* for periodical adjustment */
    UINT16                        AfcScale; /* NV para ????? */
    UINT16                        usAfcScaleHz;

    UINT16                        usSccTpaConfig;
    UINT16                        usRev;
}AFC_PDM_CTRL_STRU;


typedef struct
{
    //AFC_LOOP_STATE_ENUM_UINT16    enAFCLoopCurState;//AFC环路状态，内环失锁，外环失锁，外环锁定
    /*环路滤波*/

    AFC_LOOP_FILTER_STRU          stLoopFilter;
    AFC_PDM_CTRL_STRU             stPdmCtrl;

}AFC_LOOP_CTRL_STRU;


/*鉴频结果输出*/
typedef enum
{
    AFC_BBP_RUN = 1,
    AFC_BBP_HOLD,
    AFC_BBP_STOP
}AFC_PD_CONTROL_ENUM;
typedef UINT16 AFC_PD_CONTROL_ENUM_UINT16;

typedef enum{
AFC_BBP_UNHOLD_BIT,
AFC_BBP_HOLD_BIT
}AFC_MODULE_HOLD_ENUM;


typedef enum
{
    AFC_EMBMS_HOLD = LPHY_TRUE,
    AFC_EMBMS_UNHOLD = LPHY_FALSE
}AFC_EMBMS_HOLD_CONFIG_ENUM;
typedef UINT16 AFC_EMBMS_HOLD_CONFIG_ENUM_UINT16;
typedef enum
{
    AFC_REFRESH_PDM_SUCCESS = 0,
    AFC_REFRESH_PDM_FAIL_UNLOCK,
    AFC_REFRESH_PDM_FAIL_CC,
    AFC_REFRESH_PDM_FAIL_PAR,
    AFC_REFRESH_PDM_FAIL_TEMP,
}AFC_REFRESH_PDM_CODE_ENUM;
typedef UINT16 AFC_REFRESH_PDM_CODE_ENUM_UINT16;

typedef struct
{

    /*外环BBP输出:*/
    /*CP鉴频叉积和s19,相关系数分子u31分母u22*/
    /*DTXCP鉴频叉积和s19*/
    /*PSS鉴频叉积和s31*/
    /*内环BBP输出*/
    /*RS鉴频叉积和s19,相关系数分子u31分母u22*/

    AFC_COMPLEX_STRU    astPwr[LPHY_MAX_RX_ANTENNA_NUM];         /*天线0外环鉴频叉积和结果，分为实部和虚部*/
    AFC_COMPLEX_STRU    stCordicIn;        /*两天线叉积和合并，Cordic频偏计算模块输入*/
    /*相关系数*/
    AFC_CC_STRU         astCC[LPHY_MAX_RX_ANTENNA_NUM];               /*天线0、1外环相关系数分子和分母*/
    UINT16              ausShiftN[LPHY_BBP_SHIFT_NUM];

    /*Alpha滤波*/
    AFC_ALPHA_DATA_STRU      stAlphaData;                 /*天线0、1的CP Alpha滤波结果*/

    AFC_PD_DONE_ENUM_UINT16       enPDDoneFlag;
    AFC_PD_CONTROL_ENUM_UINT16    enPDCtrl;
    UINT16                        usFirstFrameFlag;
    UINT16                        usFrameCounter;

    AFC_EMBMS_HOLD_CONFIG_ENUM_UINT16 enPdHoldFlag;
    /*鉴频计算结果*/
    INT16                         sPDFOEst;//频偏估计
    UINT16                        usPeriod;//鉴频周期
    UINT16                        usLHz;
    //UINT16    usCounter;//鉴频周期内子帧计数
}AFC_PD_STATE_STRU;
typedef struct
{
    AFC_PD_STATE_STRU       stRSPDState;//AFC内环鉴频状态
    AFC_CC_IND_STRU         stAFCCCInd;
}AFC_PD_RESULT_STRU;


typedef enum __MLAFC_BETA_ENUM__
{
    BETA_POS=0,
    BETA_ZERO,
    BETA_NEG,
    AFC_ML_BETA_ENUM_NUM=3
}MLAFC_BTEA_ENUM;

typedef enum __MLAFC_SYM_INTVL_ENUM__
{
    SYM_INTVL_47 = 0,
    SYM_INTVL_04,/* change order for bbp change */
    SYM_INTVL_BUTT=2
}MLAFC_SYM_INTV_ENUM;

typedef struct
{
    INT32    lReal;
    INT32    lImag;
}LPHY_COMPLEX_STRU;

typedef struct __AFC_ML_CP_RELATED_CONST__
{
    UINT16 AFC_ML_BETA;
    UINT16 *AFC_ML_L_HZ;
    UINT16 *AFC_ML_E_FACTOR;
    INT16  (*AFC_ML_CITA_FACTOR)[AFC_ML_BETA_ENUM_NUM];
    UINT16 *AFC_ML_GroupLen;
	UINT16 *AFC_ML_AVER_FACTOR;
    LPHY_COMPLEX_STRU  (*AFC_ML_INV_MATRIX_A)[AFC_ML_BETA_ENUM_NUM][AFC_ML_BETA_ENUM_NUM];
}AFC_ML_CP_RELATED_CONST;

typedef struct
{
    AFC_PD_STATE_STRU       stRSPDState[AFC_ML_BETA_ENUM_NUM][SYM_INTVL_BUTT];//AFC内环鉴频状态
    AFC_CC_IND_STRU         stAFCCCInd[AFC_ML_BETA_ENUM_NUM];
    INT32                   lTrialFoeGroup[10];
    UINT16                  usPeriod;
	UINT16                  usPdDoneFlag;
}AFC_MLPD_RESULT_STRU;


#define AFC_MAX_CCFLAG                     (5)
#define AFC_MAX_CCFLAG_LEVEL               (4)

typedef struct
{
    UINT16  ausPeriod[2];
    UINT16  ausCCFlagWindowslenth[6][5];
    UINT16  ausCCFlagThreNCP[4];
    UINT16  ausCCFlagThreECP[4];
    UINT16  ausRsThrd2Fdd[2][6];
    UINT16  ausRsThrd3Fdd[2][6];
    UINT16  ausRsThrd2TddCfg0[2][6];
    UINT16  ausRsThrd3TddCfg0[2][6];
    UINT16  ausRsThrd2TddNCfg0[2][6];
    UINT16  ausRsThrd3TddNCfg0[2][6];
    UINT16  ausRsThrd4[2];
    UINT16  ausRsThrd5[2];
    UINT16  usRsThrd6;
    UINT16  usRsThrd7;
    UINT16  usRsThrd8;
/*    UINT16  usReserved;*/
    UINT16  usRSCCIndThreHL;
    UINT16  usThresh1ML[2][6];

}AFC_RS_PARA_CONFIG_STRU;
typedef struct
{
    AFC_PD_RESULT_STRU        stRsPdResult;
    AFC_RS_PARA_CONFIG_STRU   stRsConfig;
    AFC_LOOP_FILTER_STRU      stLoopFilter;
}AFC_PROC_STRU;
typedef struct
{
    INT32    lCrsInitAccFo;
    INT32    lEmbmaThetaInitial;
    INT32    lEmbmaPhaseStep;
    INT32    lEmbmsOutPhase;
    INT32    lEmbmaBaseBandFo;
}AFC_EMBMS_PHASE_STRU;
typedef struct
{
    UINT16   usCellId;
    UINT16   usFreqInfo;
    UINT16   usPDM;
    UINT16   usFilterStep;

    UINT16                        usRemainFreqLevel;  //残留频偏分档指示
    AFC_LOOP_STATE_ENUM_UINT16    enAFCLoopCurState;//AFC环路状态，内环失锁，内环锁定

    INT32    lAccFO;       //频偏调整量累加值
    INT32    lInitF0;

}AFC_BACKUP_CELL_PARA_STRU;
typedef struct
{
    UINT16                    usCellID;
    UINT16                    usFreqInfo;
    AFC_PROC_STRU             stCrsProc;

}AFC_CARRIER_PARA_STRU;


typedef struct
{
    INT32 lPhaseInitNext;
    INT32 lPhaseInit;/* for DL, before adding carrier and RF offset */
    INT32 lPhaseDelta; /* for DL*//* for UL,  lPhaseDelta*UL_FREQ/DL_FREQ */
    INT32 lPhaseDeltaStandard; /* for DL, with 30.72 sample rate */
    INT32 lOffsetDL;

    INT32 lConverIni;/* for recording carrier and RF offset */
    INT32 lConverStep;

    INT32 lInitCur;/* for DL, after adding carrier and RF offset */
    INT32 lPhaseStep;

    INT32  lInitFo;
    UINT16 usInitFoValid;
    RFE_SAMPLE_RATE_ENUM_UINT16 enSampleRate;

    INT32  lUlPhaseDelta;
    UINT16 usUlFreqInfo;
    RFE_SAMPLE_RATE_ENUM_UINT16 enUlSampleRate;
    UINT16                      usUlSampleRateUpdate;
    UINT16                      usRev;
}AFC_DL_TPA_PARA_STRU;

typedef struct
{
    UINT16                       usUlInitConfig;
    UINT16                       usDlCcIndex;
	INT32                        lUlAccInitPhase;

	UINT16                       usUlInitConvertCfg;
	RFE_SAMPLE_RATE_ENUM_UINT16  enSampleRate;
	INT32                        lConvertStep;
	INT32                        lAccConvertInitPhase;

	INT32                        lPhaseUpPts;
}AFC_UL_TPA_PARA_STRU;


typedef struct __AFC_PARA_CONFIG_BBP__
{
    UINT32 bAFCLshiftBit:5 ;/* left shift bit before noise convert */
    UINT32 bRsv1:3;
    UINT32 bShiftRSTargetBit:5;/* right shift target bit for rs */
    UINT32 bRsv2:3;
    UINT32 bShiftPowTargetBit:5;/* right shift target bit for power */
    UINT32 bRsv3:11;

    UINT32 bNoiseConvEnable:1;/* 0:diable noise convert;           1: enable noise_convert*/
    UINT32 bNoiseConvMode:2; /*0:symbol level    1:subframe level   2~3: stub */
    UINT32 bRsv4:5;
    UINT32 bNoisePowBitLowThresh:5;/* to limit noise range  for noise converting */
    UINT32 bRsv5:3;
    UINT32 bNoisePowBitHighThresh:5;/* to limit noise range for noise converting */
    UINT32 bRsv6:11;
}AFC_PARA_CONFIG_BBP;/* little endian */

typedef union __AFC_PARA_CONFIG_BBP__UNION_
{
    AFC_PARA_CONFIG_BBP bits;
    struct
    {
        UINT32 ulAfcCfg1Reg;
        UINT32 ulAfcCfg2Reg;
    }ul;
}AFC_PARA_CONFIG_BBP_UNION;



typedef struct
{
    UINT32 ulFOAccAverage;
    INT32  lTcInitFo;
    INT32  lFreqRatio;
    INT16  sPastTmperature;      //上一次查询温度，单位0.1摄氏度
    INT16  sCurrTmperature;      //当前温度
    INT16  sTmperatureDiffCnt;   //温差大于门限计数
    INT16  sFreqOutRangeCnt;
    INT16  sFreqLockErr;         //误锁定指示
    INT16  sRes;

}AFC_DCXO_TEMPERATURE_COMPENSATE;

typedef struct
{
    SINT32 aslAccFoSlidingWindow[AFC_PDM_WINDOW_LEN];
    SINT32 slAccFoSum;
    UINT16 usAccFoDataNum;
    UINT16 usPdPeriodNum;
    UINT16 usReadIdx;
    SINT16 sLastFoTemp;
    SINT16 sCurFoTemp;
    SINT16 sLastTemp;
    UINT16 usTempValid;
    UINT16 usTempReadNum;
    SINT32 slFoComp;
    INT64  lTotalFoVar;
    INT64  lFoVarThresh;
}AFC_HSTRAIN_RESULT_STRU;

typedef struct
{
    SINT32 aslAccFoSlidingWindow[AFC_PDM_WINDOW_LEN];
    SINT32 slAccFoSum;
    UINT16 usAccFoDataNum;
    UINT16 usPdPeriodNum;
    UINT16 usReadIdx;
    SINT16 sLastFoTemp;
    SINT16 sCurFoTemp;
    UINT16 usRev;
    SINT32 slFoComp;
    SINT32 lTotalFoVar;
    SINT32 lFoVarThresh;
}AFC_HST_FO_STRU;

typedef struct
{
    SINT16 sLastTemp;
    UINT16 usTempValid;
    UINT16 usTempReadNum;
    UINT16 usRev;
}AFC_HST_TEMP_STRU;

typedef struct
{
    AFC_HST_FO_STRU   stHstFo;
    AFC_HST_TEMP_STRU stHstTemp;
}AFC_HST_OM_STRU;


typedef struct
{
    UINT16 usFratioSetFlag;
	UINT16 usReserved;
    INT32  lFratio;
    INT32  lLMasterInitFO;
    UINT16 usTcSetFlag;
    UINT16 usInitFOSetFlag;
}AFC_SWITCH_TO_L_MASTER;


typedef struct
{
    INT32  lAccFO;
    INT16  sLastTemperature;
    INT16  sCurrTemperature;
    UINT16 usConfigFlag;
	UINT16 usReserved;
}AFC_BGS_CONFIG;

typedef struct
{
    INT16  sLastTemperature;
    INT16  sCurrTemperature;
	UINT16 usTCFlag;
	UINT16 usReserved;
}AFC_SWITCHBACK_TC;

typedef struct
{
    AFC_CARRIER_PARA_STRU     astCaAfc;

    AFC_STATE_ENUM_UINT16     aenAFCState;
    UINT8                     ucAfcContinuouseFrmFlag;
    UINT8                     ucSccMacCfg;

    AFC_DL_TPA_PARA_STRU      stAfcDlTpaPara;
	
	LTE_BAND_WIDTH_ENUM_UINT16 enBandWidth;
    UINT16                     usInitMibSucFlag;
}AFC_CC_PARA_STRU;

typedef struct
{
    UINT16                    usSweepCounter;
    AFC_STATE_ENUM_UINT16     enAFCMbmsState;
    UINT16                    usAfcMbmsContinuouseFrmFlag;
    UINT16                    usPccRficFreq;
    UINT16                    usPccRficFreqFlag;
    UINT16                    usRev;

    AFC_PROC_STRU             stMrsProc;
    AFC_PDM_CTRL_STRU         stPdmCtrl;
    AFC_EMBMS_PHASE_STRU      stEmbmsPhase;
    AFC_BACKUP_CELL_PARA_STRU stHoBackupPara;
    AFC_BACKUP_CELL_PARA_STRU stBgsAnrBackupPara;
    AFC_DCXO_TEMPERATURE_COMPENSATE stAfcTmperatureComp;
	AFC_SWITCH_TO_L_MASTER    stAfcSwitchToL;
    AFC_BGS_CONFIG            stAfcBgsConfig;
	AFC_SWITCHBACK_TC         stAfcSwitchbackTc;

   /* added mlafc result recorded */
    AFC_MLPD_RESULT_STRU      stMLRsPdResult;

    //AFC_HSTRAIN_RESULT_STRU   stHSTResult;
}AFC_NONCC_PARA_STRU;

typedef struct
{
    AFC_CC_PARA_STRU          astAfcCc[LPHY_FEATURE_MAX_CARRIER_NUM];
    AFC_NONCC_PARA_STRU       stAfcNonCc;
    AFC_UL_TPA_PARA_STRU      astAfcUlTpa[LPHY_MAX_UL_CARRIER_NUM];
}AFC_PARA_STRU;

typedef struct
{
    UINT16      usCellId;      //小区ID
    INT16       sPDFOEst;      //频偏
    UINT16      usCurPDM;      //PDM
    UINT16      usRSCCIndMax;  //相关系数因子
    UINT16      usFilterStep;
    INT16       sFilterInFOest;
    UINT16      usReserved;
    AFC_LOOP_STATE_ENUM_UINT16    enAFCLoopCurState;   //环路锁定标志
    INT32       lInitF0;
    INT32       lAccFO;
}LPHY_NC_AFC_REPORT_STRU;

typedef struct
{
    UINT16                     usFreqInfo;
    LTE_BAND_WIDTH_ENUM_UINT16 enBandwidth;
    UINT16                     usMsrCellNum;
    UINT16                     usTxNum;
    LPHY_NC_AFC_REPORT_STRU    astNcAfcReport[AFC_MAX_NCELL_PER_FREQ_NUM];
}LPHY_SG_NC_AFC_REPORT_ENA_STRU;

typedef struct
{
    DCXO_TC_OM_REPORT_MODE_UINT16  enCalcMode;
    INT16                          sCurrTemp;
    INT32					       lAfcValue;
    INT32                          lDelta;
    UINT32					       aulMantissaDefault[TL_DCXO_POLY_COEF_NUM_SG];  /* 依次存放a0,a1,a2,a3的尾数 */
	UINT16					       ausExponentDefault[TL_DCXO_POLY_COEF_NUM_SG];  /* 依次存放a0,a1,a2,a3的指数 */
}LPHY_SG_AFC_DCXO_TC_STRU;

typedef struct
{
    DCXO_TC_OM_REPORT_MODE_UINT16  enCalcMode;
    INT16                          sCurrTemp;
    INT32					       lAfcValue;
    INT32                          lDelta;
}LPHY_SG_AFC_DCXO_TC_INTERFACE_STRU;
/************************************************************
                           4. TRACE数据结构定义
************************************************************/
typedef enum
{
    LPHY_TRACE_AFC_LOOP_STATE         = OM_CMD_ID(LPHY_AFC_MID, OM_TYPE_TRACE, 0x1),
    LPHY_TRACE_AFC_OLPD_MODE,
    LPHY_TRACE_AFC_STATE,
    LPHY_TRACE_AFC_PARA_UPDATE,
    LPHY_TRACE_AFC_CA_UPDATE,
}LPHY_TRACE_AFC_ENUM;

/* BEGIN: Added by s00175552, 2011/7/4   问题单号:DTS2011070403581*/
typedef struct
{
    UINT32      ulLineNum;
    AFC_LOOP_STATE_ENUM_UINT16      enNewLoopState;
    UINT16      usReserved;
}LPHY_TRACE_AFC_LOOP_STATE_STRU;
/* END: Added by s00175552, 2011/7/4   问题单号:DTS2011070403581*/

typedef struct
{
    UINT32      ulLineNum;
    AFC_PD_TYPE_ENUM_UINT16      ulOlpdMode;
}LPHY_TRACE_AFC_OLPD_MODE_STRU;

typedef struct
{
    UINT32      ulLineNum;
    AFC_STATE_ENUM      ulAfcState;
}LPHY_TRACE_AFC_STATE_STRU;
typedef enum
{
    AFC_SWITCH_CELL = 0,
    AFC_SWITCHBACK,
    AFC_INIT_START,
    AFC_UPDATE_DL_PARA,
    AFC_CAMPCELL,
    AFC_UPDATE_UL_SAMPLERATE,
    AFC_STOP_SERVE_CELL,
}AFC_UPDATE_CELL_CAUSE_ENUM;

typedef UINT16 AFC_UPDATE_CELL_CAUSE_ENUM_UINT16;

typedef struct
{
    AFC_UPDATE_CELL_CAUSE_ENUM_UINT16 enUpdateCause;
    RFE_SAMPLE_RATE_ENUM_UINT16       enUlSampleRate;
    INT32                             lUlPhaseDelta;
    UINT16                            usUlFreqInfo;
    UINT16                            usUlIndex;
    UINT16                            usDlFreqInfo;
    UINT16                            usRev;
}LPHY_TRACE_AFC_PARA_UPDATE_STRU;

typedef enum
{
    AFC_CONTIGOUS_CA = 0,
    AFC_NONCONTIGOUS_CA,
    AFC_SCC_START,
    AFC_SCC_STOP,
    AFC_SCC_TPA_CONFIG,
}AFC_CA_STATUS_ENUM;

typedef UINT16 AFC_CA_STATUS_ENUM_UINT16;

typedef struct
{
    AFC_CA_STATUS_ENUM_UINT16   enCaStatus;
    LPHY_CA_CC_ENUM_UINT16      enCcIndex;
    RFE_SAMPLE_RATE_ENUM_UINT16 enSampleRate;
    UINT16                      usFreqInfo;
    INT32                       lDeltaPhase;
    INT32                       lInitFo;
    INT32                       lAccFo;
    INT32                       lConvertStep;
}LPHY_TRACE_AFC_CA_UPDATE_STRU;
/************************************************************
                           5. ERROR数据结构定义
************************************************************/
typedef enum
{
    LPHY_ERROR_AFC_ARRAY_INDEX         = OM_CMD_ID(LPHY_AFC_MID, OM_TYPE_ERROR, 0x1),
    LPHY_ERROR_AFC_CASE,
    LPHY_ERROR_AFC_ZERO_DIV,
    LPHY_WARNING_AFC_RTT_SWITCH_OFF,
}LPHY_ERROR_AFC_ENUM;

typedef struct
{
    UINT32      ulLineNum;//__LINE__
    UINT32      ulIncorrectValue;
}LPHY_ERROR_AFC_ARRAY_INDEX_STRU;

typedef struct
{
    UINT32      ulLineNum;//__LINE__
    UINT32      ulCurrentCase;
    UINT32      ulLastCase;
}LPHY_ERROR_AFC_CASE_STRU;

typedef struct
{
    UINT32      ulLineNum;//__LINE__
}LPHY_ERROR_AFC_ZERO_DIV_STRU;

/************************************************************
                           7. Ind数据结构定义
************************************************************/
typedef enum
{
    LPHY_IND_AFC_PD_STATUS_ENA         = OM_CMD_ID(LPHY_AFC_MID, OM_TYPE_IND, 0x1),
    LPHY_IND_AFC_LOOP_STATE_ENA,
}LPHY_IND_AFC_ENUM;


typedef struct
{
    AFC_PD_TYPE_ENUM_UINT16       enPDType;
    UINT16                        usAlphaStateFlag;//Alpha滤波初始化标志
    INT16                         sPDFOEst;//频偏估计
    UINT16                        usPeriod;//鉴频周期
    UINT16                        ausCCFlag[LPHY_MAX_RX_ANTENNA_NUM];
    UINT16                        ausDTXFlag[LPHY_MAX_RX_ANTENNA_NUM];
    UINT16                        usCCAlphaA[LPHY_MAX_RX_ANTENNA_NUM];
    UINT16                        usCCAlphaB[LPHY_MAX_RX_ANTENNA_NUM];
    AFC_CC_STAT_STRU              astCCind[LPHY_MAX_RX_ANTENNA_NUM];    /*天线0、1的RS相关系数门限指示*/
    AFC_COMPLEX_STRU              astPwr[LPHY_MAX_RX_ANTENNA_NUM];         /*天线0外环鉴频叉积和结果，分为实部和虚部*/
    AFC_CC_STRU                   astCC[LPHY_MAX_RX_ANTENNA_NUM];               /*天线0、1外环相关系数分子和分母*/
    AFC_RSCC_THRE_STRU            stCCThre;
}LPHY_IND_AFC_PD_STATUS_ENA_STRU;

typedef struct
{
    /*环路滤波*/
    AFC_LOOP_STATE_ENUM_UINT16      enAFCLoopCurState;//AFC环路状态，内环失锁，外环失锁，外环锁定
    UINT16      usLastCellPDM;
    UINT16      usFilterInCCind;
    INT16       sFilterInFOest;

    INT32       lCurFOAdj;    //当前频偏调整量
    INT32       lAccFO;       //频偏调整量累加值
    INT32       lInitF0;      //初始频偏
    AFC_LOCK_PARA_STRU            stLockPara;
} LPHY_IND_AFC_LOOP_STATE_ENA_STRU;


typedef struct
{
    UINT16      usFOestUnderFlg;
    UINT16      usFixRawVelocityFlg;
}AFC_HS_DL_PARA_STRU;

typedef struct
{
    UINT32  ulFilterStateFlag;
    SINT32  slFilterIn;
    SINT32  slFilterCoef;
    SINT32  slACCFOReg;
    SINT16  sFOest;
    UINT16  usFOestPassCtl;
    SINT16  sLastTemp;
    SINT16  sCurTemp;
    SINT32  slFoComp;
}AFC_UL_ALPHA_FLT_STRU;
typedef struct
{
    UINT16      usULPDMConfig;
    UINT16      usDLFreqInfo;
    UINT16      usULFreqInfo;
    UINT16      usFrameType;
    UINT32      ulAFCthres0;
    UINT32      ulAFCthres1;
    SINT32      slULCurBBRotator;
    SINT32      slULLastBBRotator;
    SINT32      slULCurACCFO;
    SINT32      slDLCurACCFO;
    SINT32      slACCFOlongTerm;
    SINT32      slPhaseUL;
    UINT32      ulLowThredCounter;
    AFC_UL_ALPHA_FLT_STRU stULFilter;
}AFC_UL_PARA_STRU;

/************************************************************
                           8. DT路测数据结构定义
************************************************************/
/*typedef enum
{
    LPHY_DT_AFC_REPORT_REQ         = OM_CMD_ID(LPHY_AFC_MID, OM_TYPE_DT, 0x1)

}LPHY_DT_AFC_REQ_ENUM;*/

typedef struct
{
    AFC_OM_SWITCH_ENUM_UINT16    enAfcReportEn;
    UINT16   usReportPeriod;
}LPHY_DT_AFC_REPORT_REQ_STRU;

typedef enum
{
    LPHY_DT_AFC_REPORT_RESERVED         = OM_CMD_ID(LPHY_AFC_MID, OM_TYPE_DT, 0x0),
    LPHY_DT_AFC_REPORT_IND,
    LPHY_DT_AFC_REPORT_CA_IND

}LPHY_DT_AFC_IND_ENUM;

typedef struct _LPHY_DT_AFC_REPORT_CA_IND_STRU__
{
    UINT8      ucCcValidFlg;
	UINT8      ucCcIdx;
	UINT16     usRsv;

    UINT16     usSFN;
    UINT16     usSubFn;
    UINT16     usPeriod;
    UINT16     usRsv0;
    INT32      lCurFOAdj;
}LPHY_DT_AFC_REPORT_CA_IND_STRU;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __AFC_OM_DEF_H__ */

