/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : viterbi_om_def.h
  版 本 号   : 初稿
  作    者   : chenguangwen
  生成日期   : 2011年3月8日
  最近修改   :
  功能描述   : 定义Viterbi模块OM需要上报的结构体,该文件最终会交付给HiStudio使用
  函数列表   :
  修改历史   :
  1.日    期   : 2011年3月8日
    作    者   : chenguangwen
    修改内容   : 创建文件

  2.日    期   : 2011年6月8日
    作    者   : chenguangwen
    修改内容   : [DTS2011060800603]新增OM代码合入

  3.日    期   : 2011年11月24日
    作    者   : c00174696
    修改内容   : [DTS2011112307116]合入半静态新特性

  4.日    期   : 2011年11月28日
    作    者   : chenguangwen
    修改内容   : [DTS2011111800531]Pilot版本合入

  5.日    期   : 2012年02月21日
    作    者   : chenguangwen
    修改内容   : [DTS2011122806532]修改TDD配比0进程号计算

  6.日    期   : 2012年4月18日
     作    者   : sunyanjie，yushujing，xueqiuyan
     修改内容   : [DTS2012041802974]OM优化修改

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

#ifndef __VITERBI_OM_DEF_H__
#define __VITERBI_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */

#define     MAX_CELL_NUM_DL                    2

#if    (MAX_CELL_NUM_DL !=  LPHY_FEATURE_MAX_CARRIER_NUM)
    #error "(MAX_CELL_NUM_DL !=  LPHY_FEATURE_MAX_CARRIER_NUM)"
#endif

/************************************************************
                           1. REQ命令和对应的数据结构定义
************************************************************/
enum __LPHY_REQ_VITERBI__
{
    LPHY_REQ_VITERBI_STUB_DCI_ENA                   = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_REQ, 0x1),
    LPHY_REQ_VITERBI_RPT_CFI_ENA,
    LPHY_REQ_VITERBI_RPT_CFI_STAT_ENA,
    LPHY_REQ_VITERBI_RPT_PDCCH_SINR_ENA,
    LPHY_REQ_VITERBI_RPT_PDCCH_DL_GRANT_ENA,
    LPHY_REQ_VITERBI_RPT_PDCCH_UL_GRANT_ENA,
    LPHY_REQ_VITERBI_RPT_PDCCH_PWR_GRANT_ENA,
    LPHY_REQ_VITERBI_RPT_PDCCH_GRANT_STAT_ENA,
    LPHY_REQ_VITERBI_RPT_PDCCH_CCE_INFO_ENA,
    LPHY_REQ_VITERBI_RPT_PDCCH_BLER_ENA,
    LPHY_DT_VITERBI_RPT_CFI_INFO_REQ               = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_REQ, 0x100),
    LPHY_DT_VITERBI_RPT_PDCCH_GRANT_STAT_REQ,
    LPHY_DT_VITERBI_RPT_PDCCH_DL_GRANT_INFO_REQ,
    LPHY_DT_VITERBI_RPT_PDCCH_BLER_REQ,
};

/*上报周期, 仅作参考*/
typedef enum __LPHY_REQ_DECODE_PERIOD_RPT___
{
    PERIOD_1        = 0,
    PERIOD_2,
    PERIOD_4,
    PERIOD_8,
    PERIOD_16,
    PERIOD_32,
    PERIOD_64,
    PERIOD_128,
    PERIOD_256,
    PERIOD_512,
    PERIOD_1024,
    PERIOD_2048,
}LPHY_REQ_DECODE_PERIOD_RPT_ENUM;
typedef UINT16 LPHY_REQ_DECODE_PERIOD_RPT_ENUM_UINT16;

/*打桩DCI开关*/
typedef enum
{
    OM_STUB_DCI1A    = 0,
    OM_STUB_DCIX,
}PDCCH_STUB_DCI_ENUM;
typedef UINT16 PDCCH_STUB_DCI_ENUM_UINT16;

typedef struct
{
    OM_REQ_ENABLE_ENUM enStubDciEna;
    UINT32 ulDciMsb;
    UINT32 ulDciLsb;
    PDCCH_STUB_DCI_ENUM_UINT16 enStubDciType;
    UINT16 usReserved;
}LPHY_REQ_VITERBI_STUB_DCI_ENA_STRU;

/*上报CFI值开关*/
typedef struct
{
    OM_REQ_ENABLE_ENUM enRptCfiEna;
}LPHY_REQ_VITERBI_RPT_CFI_ENA_STRU;

/*上报CFI统计开关*/
typedef struct
{
    OM_REQ_ENABLE_ENUM enRptCfiStatEna;
    UINT32 ulRptCfiStatPeriod;
}LPHY_REQ_VITERBI_RPT_CFI_STAT_ENA_STRU;

/*上报PDCCH SINR开关*/
typedef struct
{
    OM_REQ_ENABLE_ENUM enRptPdcchSinrEna;
}LPHY_REQ_VITERBI_RPT_PDCCH_SINR_ENA_STRU;

/*上报下行授权开关*/
typedef struct
{
    OM_REQ_ENABLE_ENUM enRptPdcchDlGrantEna;
}LPHY_REQ_VITERBI_RPT_PDCCH_DL_GRANT_ENA_STRU;

/*上报上行授权开关*/
typedef struct
{
    OM_REQ_ENABLE_ENUM enRptPdcchUlGrantEna;
}LPHY_REQ_VITERBI_RPT_PDCCH_UL_GRANT_ENA_STRU;

/*上报功率授权开关*/
typedef struct
{
    OM_REQ_ENABLE_ENUM enRptPdcchPwrGrantInfoEna;
}LPHY_REQ_VITERBI_RPT_PDCCH_PWR_GRANT_ENA_STRU;

/*上报授权统计开关*/
typedef struct
{
    OM_REQ_ENABLE_ENUM enRptPdcchGrantStatEna;
    UINT32 ulRptPdcchGrantStatPeriod;
}LPHY_REQ_VITERBI_RPT_PDCCH_GRANT_STAT_ENA_STRU;

/*上报CCE信息开关*/
typedef struct
{
    OM_REQ_ENABLE_ENUM enRptPdcchCCEInfoEna;
}LPHY_REQ_VITERBI_RPT_PDCCH_CCE_INFO_ENA_STRU;

/*上报PDCCH BLER开关*/
typedef struct
{
    OM_REQ_ENABLE_ENUM enRptPdcBlerEna;
    UINT32 ulRptPdcchBlerPeriod;
}LPHY_REQ_VITERBI_RPT_PDCCH_BLER_ENA_STRU;


/************************************************************
                           2. CNF数据结构定义
************************************************************/
typedef enum __LPHY_VITERBI_OM_CNF__
{
    LPHY_CNF_VITERBI_STUB_DCI_ENA                   = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_CNF, 0x1),
    LPHY_CNF_VITERBI_RPT_CFI_ENA,
    LPHY_CNF_VITERBI_RPT_CFI_STAT_ENA,
    LPHY_CNF_VITERBI_RPT_SINR_ENA,
    LPHY_CNF_VITERBI_RPT_PDCCH_DL_GRANT_ENA,
    LPHY_CNF_VITERBI_RPT_PDCCH_UL_GRANT_ENA,
    LPHY_CNF_VITERBI_RPT_PDCCH_PWR_GRANT_ENA,
    LPHY_CNF_VITERBI_RPT_PDCCH_GRANT_STAT_ENA,
    LPHY_CNF_VITERBI_RPT_PDCCH_CCE_INFO_ENA,
    LPHY_CNF_VITERBI_RPT_PDCCH_BLER_ENA
}LPHY_CNF_VITERBI_ENUM;


/************************************************************
                           3. Ind数据结构定义
************************************************************/
typedef enum __LPHY_IND_VITERBI__
{
    LPHY_IND_VITERBI_RPT_CFI                = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_IND, 0x1),
    LPHY_IND_VITERBI_RPT_CFI_SCELL,
    LPHY_IND_VITERBI_RPT_PDCCH_SINR,
    LPHY_IND_VITERBI_RPT_PDCCH_DL_GRANT,
    LPHY_IND_VITERBI_RPT_PDCCH_UL_GRANT,
    LPHY_IND_VITERBI_RPT_PDCCH_PWR_GRANT,
    LPHY_IND_VITERBI_RPT_PDCCH_GRANT_STAT,
    LPHY_IND_VITERBI_RPT_PDCCH_CCE_INFO,
    LPHY_IND_VITERBI_RPT_PDCCH_BLER
}LPHY_IND_VITERBI_ENUM;

/*上报CFI值*/
typedef struct __LPHY_VITERBI_RPT_CFI_OM_IND__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usCfi;
    UINT16 usCcFlag;
}LPHY_IND_VITERBI_RPT_CFI_STRU;

/*上报CFI统计*/
typedef struct __LPHY_VITERBI_RPT_CFI_STAT_OM_IND__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 ulCfi1Num;
    UINT32 ulCfi2Num;
    UINT32 ulCfi3Num;
    UINT32 ulCfiTotalNum;
}LPHY_IND_VITERBI_RPT_CFI_STAT_STRU;

/*上报PDCCH SINR*/
typedef struct
{
    UINT32 ulDlDciPower[2][3];    /*下行DCI软件度量值*/
    UINT32 ulUlDciPower;                        /*上行DCI软件度量值*/
    UINT32 ulRsNoisePower[2][2];     /*天线0与1的平均宽带噪声功率*/
    INT32  lDlDciSINR[2];         /*下行DCI信干噪比*/
    INT32  lUlDciSINR;                          /*上行DCI信干噪比*/
}PDCCH_SINR_INFO_STRU;

typedef struct __LPHY_VITERBI_RPT_PDCCH_SINR_OM_IND__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    PDCCH_SINR_INFO_STRU stPdcSinrInfo;
}LPHY_IND_VITERBI_RPT_PDCCH_SINR_STRU;

/*上报下行授权*/
typedef enum
{
    OM_DCI_0    = 0,
    OM_DCI_1,
    OM_DCI_1A,
    OM_DCI_1B,
    OM_DCI_1C,
    OM_DCI_1D,
    OM_DCI_2,
    OM_DCI_2A,
    OM_DCI_2B,
    /* BEGIN: Added by yushujing, 2014/12/2   问题单号:3_3a_mod*/
    OM_DCI_2C,
    OM_DCI_3,
    OM_DCI_3A
}PDCCH_GRANT_DCI_ENUM;
typedef UINT8 PDCCH_GRANT_DCI_ENUM_UINT8;

typedef enum
{
    OM_RA_RNTI    = 0,
    OM_P_RNTI,
    OM_SI_RNTI,
    OM_C_RNTI,
    OM_SPS_RNTI,
    OM_TC_RNTI,
    OM_TPC_PUCCH_RNTI,
    OM_TPC_PUSCH_RNTI
}PDCCH_GRANT_RNTI_ENUM;
typedef UINT8 PDCCH_GRANT_RNTI_ENUM_UINT8;

typedef struct __LPHY_VITERBI_RPT_PDCCH_DL_GRANT_OM_IND__
{
    UINT16 usSysFn;
    UINT8  ucSubFn;
    PDCCH_GRANT_DCI_ENUM_UINT8 enDciType;
    UINT16 usCcFlag;
    UINT16 usRsv;
    UINT32 ulDciMsb;
    UINT32 ulDciLsb;
    PDCCH_GRANT_RNTI_ENUM_UINT8 enRntiType;
    UINT8  ucRbNum;
    UINT8  ucTpc;
    UINT8  ucDai;
    UINT8  ucHarqNum;
    UINT8  ucSwapFlag;
    UINT8  ucPrecodeInfo;
    UINT8  ucAggLevel;          /*路测中是保留字*/
    UINT8  ucMcs1;
    UINT8  ucNdi1;
    UINT8  ucRV1;
    UINT8  ucNewReTrans1;       /*路测中是保留字*/
    UINT32 ulTbSize1;
    UINT8  ucMcs2;
    UINT8  ucNdi2;
    UINT8  ucRV2;
    UINT8  ucNewReTrans2;       /*路测中是保留字*/
    UINT32 ulTbSize2;
}LPHY_IND_VITERBI_RPT_PDCCH_DL_GRANT_STRU;

/*上报上行授权*/
typedef struct __LPHY_VITERBI_RPT_PDCCH_UL_GRANT_OM_IND__
{
    UINT16 usSysFn;
    UINT8  ucSubFn;
    PDCCH_GRANT_RNTI_ENUM_UINT8 enRntiType;     /*路测中是保留字*/
    UINT32 ulDciMsb;
    UINT32 ulDciLsb;
    UINT16 usAggLevel;                          /*SG需求*/
    UINT8  ucHoppingFlag;
    UINT8  ucRbStart;
    UINT8  ucRbNum;
    UINT8  ucMcs;
    UINT8  ucNdi;
    UINT8  ucTpc;
    UINT8  ucDMRS;
    UINT8  ucUlIndex;
    UINT8  ucDai;
    UINT8  ucCqiReq;
    UINT32 ulTbSize;
    UINT8  ucNewReTrans;
    UINT8  ucRsd0;
    UINT16 usRsd1;
}LPHY_IND_VITERBI_RPT_PDCCH_UL_GRANT_STRU;

/*上报功率授权*/
typedef enum
{
    OM_PWR_GRANT_DCI_3    = 0,
    OM_PWR_GRANT_DCI_3A,
}PDCCH_PWR_GRANT_DCI_ENUM;
typedef UINT8 PDCCH_PWR_GRANT_DCI_ENUM_UINT8;

typedef enum
{
    OM_PWR_GRANT_TPC_PUCCH_RNTI    = 0,
    OM_PWR_GRANT_TPC_PUSCH_RNTI,
}PDCCH_PWR_GRANT_RNTI_ENUM;
typedef UINT8 PDCCH_PWR_GRANT_RNTI_ENUM_UINT8;

typedef struct __LPHY_VITERBI_RPT_PDCCH_PWR_GRANT_OM_IND__
{
    UINT16 usSysFn;
    UINT8  ucSubFn;
    PDCCH_PWR_GRANT_DCI_ENUM_UINT8  enDciType;
    UINT32 ulDciMsb;
    PDCCH_PWR_GRANT_RNTI_ENUM_UINT8 enRntiType;
    UINT8  ucCceStart;       /*路测中是保留字*/
    UINT16 usAggLevel;       /*路测中是保留字*/
}LPHY_IND_VITERBI_RPT_PDCCH_PWR_GRANT_STRU;

/*上报授权统计*/
#define     OM_VITERBI_PDCCH_GRANT_STAT_LEN       44       /*Viterbi授权统计需清零的数据长度, Bytes, 注意需要与接口同步*/
typedef struct __LPHY_VITERBI_RPT_PDCCH_GRANT_STAT_OM_IND__
{
    /* BEGIN: Modified by h00130263, 2013/6/8   问题单号:v7r2_code_size_opt*/
    //UINT16 usCfi1Num;
    //UINT16 usCfi2Num;
    //UINT16 usCfi3Num;
    UINT16 ausCfiNum[3];
    UINT16 usRsd1;
    UINT16 usUlGrantNum;
    UINT16 usDlGrantNum;
    /* BEGIN: Modified by h00130263, 2013/6/8   问题单号:v7r2_code_size_opt*/
    //UINT16 usCce1Num;
    //UINT16 usCce2Num;
    //UINT16 usCce4Num;
    //UINT16 usCce8Num;
    UINT16 usCceNum[4];
    UINT16 usDci0Num;
    UINT16 usDci1Num;
    UINT16 usDci1ANum;
    UINT16 usDci1BNum;
    UINT16 usDci1CNum;
    UINT16 usDci1DNum;
    UINT16 usDci2Num;
    UINT16 usDci2ANum;
    UINT16 usDci2BNum;
    UINT16 usDci3Num;
    UINT16 usDci3ANum;
    UINT16 usRsd2;
    /* BEGIN: Modified by h00130263, 2013/6/8   问题单号:v7r2_code_size_opt*/
    //UINT32 ulAccuCfi1Num;
    //UINT32 ulAccuCfi2Num;
    //UINT32 ulAccuCfi3Num;
    UINT32 aulAccuCfiNum[3];
    UINT32 ulAccuUlGrantNum;
    UINT32 ulAccuDlGrantNum;
    /* BEGIN: Modified by h00130263, 2013/6/8   问题单号:v7r2_code_size_opt*/
    //UINT32 ulAccuCce1Num;
    //UINT32 ulAccuCce2Num;
    //UINT32 ulAccuCce4Num;
    //UINT32 ulAccuCce8Num;
    UINT32 ulAccuCceNum[4];
    UINT32 ulAccuDci0Num;
    UINT32 ulAccuDci1Num;
    UINT32 ulAccuDci1ANum;
    UINT32 ulAccuDci1BNum;
    UINT32 ulAccuDci1CNum;
    UINT32 ulAccuDci1DNum;
    UINT32 ulAccuDci2Num;
    UINT32 ulAccuDci2ANum;
    UINT32 ulAccuDci2BNum;
    UINT32 ulAccuDci3Num;
    UINT32 ulAccuDci3ANum;
}LPHY_IND_VITERBI_RPT_PDCCH_GRANT_STAT_STRU;

/*上报CCE信息*/
typedef struct __LPHY_VITERBI_RPT_PDCCH_CCE_INFO_OM_IND__
{
    UINT16 usSysFn;
    UINT8  ucSubFn;
    PDCCH_GRANT_DCI_ENUM_UINT8  enDciType;
    PDCCH_GRANT_RNTI_ENUM_UINT8 enRntiType;
    UINT8  ucCceStart;
    UINT8  ucAggLevel;
    UINT8  ucRsd;
}LPHY_IND_VITERBI_RPT_PDCCH_CCE_INFO_STRU;

/*上报PDCCH BLER*/
typedef struct __LPHY_VITERBI_RPT_PDCCH_BLER_OM_IND__
{
    UINT32 ulPdcchErrorNum[2];         /*定义为无任何有效的DCI(包括上下行)就算一次 -> 算法需求, 但不清楚定义, 故DSP自己定义*/
    UINT32 ulPdcchTotalNum[2];         /*定义为只要VDL浮动中断上来就算一次, 注意对于DTX情况总数要累加, 但错误数亦累加*/
    UINT32 ulPdcchAccuErrorNum[2];     /*累积量*/
    UINT32 ulPdcchAccuTotalNum[2];     /*累积量*/
}LPHY_IND_VITERBI_RPT_PDCCH_BLER_STRU;


/************************************************************
                           4. TRACE数据结构定义
************************************************************/
typedef enum __LPHY_TRACE_VITERBI_ENUM__
{
    /*PBCH, ID 1 - 31*/
    LPHY_TRACE_VITERBI_PBCH_DECODE_START                = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_TRACE, 0x1),
    LPHY_TRACE_VITERBI_PBCH_DECODE_FAIL,
    LPHY_TRACE_VITERBI_PBCH_DECODE_SUCCESS,

    /*PDCCH ID 32 - 4095*/
    LPHY_TRACE_VITERBI_CFI_FLOAT_INT_TRIGGERED          = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_TRACE, 0x20),
    LPHY_TRACE_VITERBI_PDCCH_DECODE_START,
    LPHY_TRACE_VITERBI_PDCCH_FLOAT_INT_TRIGGERED,
    LPHY_TRACE_VITERBI_PDCCH_DCI_PARSE_FINISHED,
    LPHY_TRACE_VITERBI_PDCCH_ORDER_TRIGGER_RA,
    LPHY_TRACE_VITERBI_PDCCH_ORDER_TRIGGER_RA_SUCCESS,
    LPHY_TRACE_VITERBI_PDCCH_RAR_TIMEOUT,
    LPHY_TRACE_VITERBI_PDCCH_DL_SPS_ACTIVATE,
    LPHY_TRACE_VITERBI_PDCCH_DL_SPS_RELEASE,
    LPHY_TRACE_VITERBI_PDCCH_UL_SPS_ACTIVATE,
    LPHY_TRACE_VITERBI_PDCCH_UL_SPS_RELEASE,
    LPHY_TRACE_VITERBI_PDCCH_DTX,
    LPHY_TRACE_VITERBI_PDCCH_MULTI_RNTI_COEXIST,
    LPHY_TRACE_VITERBI_PDCCH_MULTI_DATA_RNTI_COEXIST,
    LPHY_TRACE_VITERBI_PDCCH_DL_TC_RNTI_RECEIVED,
    LPHY_TRACE_VITERBI_PDCCH_RA_RNTI_RECEIVED,
    LPHY_TRACE_VITERBI_PDCCH_CONNECT_MAC_RA_SUCCESS,
    LPHY_TRACE_VITERBI_PDCCH_DL_SPS_PERIOD_CONFIG,
    LPHY_TRACE_VITERBI_PDCCH_UL_SPS_PERIOD_CONFIG,
    LPHY_TRACE_VITERBI_PDCCH_DL_SPS_PARA_UPDATE,
    LPHY_TRACE_VITERBI_PDCCH_UL_SPS_PARA_UPDATE,
    LPHY_TRACE_VITERBI_LMAC_UL_SPS_RELEASE,
    LPHY_TRACE_VITERBI_MCCH_CHANGE_NOTIFY,
    LPHY_TRACE_VITERBI_PDCCH_UL_SPEC_CFG,
    LPHY_TRACE_VITERBI_PHICH_RESULT,
    LPHY_TRACE_VITERBI_CRC_OK_RETRAN,
    LPHY_TRACE_VITERBI_SWAP_VALID,
    LPHY_TRACE_VITERBI_MSG3_ACK_RECEIVED,
    LPHY_TRACE_VITERBI_PDCCH_ORDER_DL_DCI_RECEIVED,
    LPHY_TRACE_VITERBI_PDCCH_ORDER_DCI0_RECEIVED,
    LPHY_TRACE_VITERBI_TC_RNTI_INVALID,
    LPHY_TRACE_VITERBI_PDCCH_DCI_PARSE_FINISHED_SCELL,
}LPHY_TRACE_VITERBI_ENUM;
typedef UINT16 LPHY_TRACE_VITERBI_ENUM_UINT16;

/*PBCH*/
typedef struct __LPHY_VITERBI_PBCH_DECODE_START_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 ulPbchCombineFlag;
    UINT32 ulPbchDecodeCnt;
    UINT32 ulPbchCfgPara;
}LPHY_TRACE_ERROR_VITERBI_PBCH_DECODE_STRU;

typedef struct __LPHY_VITERBI_PBCH_DECODE_SUCCESS_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usTxAnteNum;
    UINT16 usSfn;
    UINT32 ulPbchData;
}LPHY_TRACE_VITERBI_PBCH_DECODE_SUCCESS_STRU;

/*PDCCH*/
typedef struct __LPHY_VITERBI_CFI_FLOAT_INT_TRIGGERED_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usCfiValue;
    UINT16 usBandWidth;
}LPHY_TRACE_VITERBI_CFI_FLOAT_INT_TRIGGERED_STRU;

typedef struct __LPHY_VITERBI_PDCCH_DCI_PARSE_FINISHED_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usDlBbpNum;
    UINT16 usDlDataGrantValid;
    UINT16 usDlGrantNum;
    UINT16 usDci0BbpNum;
    UINT16 usDci0CRntiSelNum;
    UINT16 usDci0TcRntiSelNum;
    UINT16 usDci0SpsRntiSelNum;
    UINT16 usDci0Num;
    UINT16 usDci0MacHarqNum;
    UINT16 ausDci0HarqInfo[2];
}LPHY_TRACE_VITERBI_PDCCH_DCI_PARSE_FINISHED_STRU;
typedef struct __LPHY_VITERBI_PDCCH_DCI_PARSE_FINISHED_SCELL_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usDlBbpNum;
    UINT16 usDlDataGrantValid;
    UINT16 usDlGrantNum;
}LPHY_TRACE_VITERBI_PDCCH_DCI_PARSE_FINISHED_SCELL_STRU;

typedef struct __LPHY_VITERBI_PDCCH_ORDER_TRIGGER_RA_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usPreambleIdx;
    UINT16 usPrachMaskIdx;
    UINT32 ulDci1AMsb;
    UINT32 ulGrpValidNum;
}LPHY_TRACE_VITERBI_PDCCH_ORDER_TRIGGER_RA_STRU;

typedef struct __LPHY_VITERBI_PDCCH_ORDER_TRIGGER_RA_SUCCESS_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
}LPHY_TRACE_VITERBI_PDCCH_ORDER_TRIGGER_RA_SUCCESS_STRU;

typedef struct __LPHY_VITERBI_PDCCH_RAR_TIMEOUT_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
}LPHY_TRACE_VITERBI_PDCCH_RAR_TIMEOUT_STRU;

typedef struct __LPHY_VITERBI_PDCCH_DL_SPS_ACTIVATE_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 ulGrantNum;
}LPHY_TRACE_VITERBI_PDCCH_DL_SPS_ACTIVATE_STRU;

typedef struct __LPHY_VITERBI_PDCCH_DL_SPS_RELEASE_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 ulGrantNum;
}LPHY_TRACE_VITERBI_PDCCH_DL_SPS_RELEASE_STRU;

typedef struct
{
    UINT16                 usInitSysFn;                     /*该初始授权接收帧号*/
    UINT16                 usInitSubFn;                     /*该初始授权接收子帧号*/
    UINT16                 usRecvSysFn;                     /*当前接收帧号*/
    UINT16                 usRecvSubFn;                     /*当前接收子帧号*/
    UINT16                 usTranSysFn;                     /*当前生效帧号*/
    UINT16                 usTranSubFn;                     /*当前生效子帧号*/
    UINT16                 usOddEvenFlag;                   /*奇偶位置标志, 0: 偶位置, 1: 奇位置*/
    INT16                  sSubFnOffset;                    /*子帧偏移, 仅在上下行配比1至4情况下不为0*/
    UINT32                 ulNextPeriodPos;                 /*下次生效周期位置*/
    UINT32                 ulActualPeriodNum;               /*实际周期生效次数*/
    UINT32                 ulTotalPeriodNum;                /*周期生效次数*/
    DCI0_STRU              stUlGrantInfo;
}OM_UL_SPS_INIT_GRANT_STRU;

typedef struct __LPHY_VITERBI_PDCCH_UL_SPS_ACTIVATE_OM_TRACE__
{
    UINT32 ulHarqIndex;
    OM_UL_SPS_INIT_GRANT_STRU stUlSpsInitGrant;
}LPHY_TRACE_VITERBI_PDCCH_UL_SPS_ACTIVATE_STRU;

typedef struct __LPHY_VITERBI_PDCCH_UL_SPS_RELEASE_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
}LPHY_TRACE_VITERBI_PDCCH_UL_SPS_RELEASE_STRU;

typedef enum
{
    PDCCH_RESPOND_DTX_TDD_SPEC    = 0,
    PDCCH_RESPOND_DTX_BF_SPEC,
    PDCCH_RESPOND_DTX_NO_GRANT
}PDCCH_RESPOND_DTX_ENUM;
typedef UINT16 PDCCH_RESPOND_DTX_TYPE_ENUM_UINT16;
typedef struct __LPHY_VITERBI_PDCCH_DTX_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    PDCCH_RESPOND_DTX_TYPE_ENUM_UINT16 enDtxRespType;
    UINT16 usRsd;
}LPHY_TRACE_VITERBI_PDCCH_DTX_STRU;

typedef struct __LPHY_VITERBI_PDCCH_MULTI_RNTI_COEXIST_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usRaRntiFlag;
    UINT16 usSpsRntiFlag;
    UINT16 usCTcRntiFlag;
    UINT16 usSiRntiFlag;
    UINT16 usPRntiFlag;
    UINT16 usRsd;
}LPHY_TRACE_VITERBI_PDCCH_MULTI_RNTI_COEXIST_STRU;

//typedef struct __LPHY_VITERBI_PDCCH_MULTI_DATA_RNTI_COEXIST_OM_TRACE__
//{
//    UINT16 usSysFn;
//    UINT16 usSubFn;
//    UINT16 usRaRntiFlag;
//    UINT16 usSpsRntiFlag;
//    UINT16 usCTcRntiFlag;
//    UINT16 usSiRntiFlag;
//    UINT16 usPRntiFlag;
//    UINT16 usRsd;
//}LPHY_TRACE_VITERBI_PDCCH_MULTI_DATA_RNTI_COEXIST_STRU;

typedef struct __LPHY_VITERBI_PDCCH_DL_TC_RNTI_RECEIVED_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    PDCCH_GRANT_DCI_ENUM_UINT8  enDciType;
    PDCCH_GRANT_RNTI_ENUM_UINT8 enRntiType;
    UINT16 usRntiValue;
}LPHY_TRACE_VITERBI_PDCCH_DL_TC_RNTI_RECEIVED_STRU;

typedef struct __LPHY_VITERBI_PDCCH_RA_RNTI_RECEIVED_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    PDCCH_GRANT_DCI_ENUM_UINT8  enDciType;
    PDCCH_GRANT_RNTI_ENUM_UINT8 enRntiType;
    UINT16 usRntiValue;
    UINT16 usRarGrantCnt;
    UINT16 usRsd;
}LPHY_TRACE_VITERBI_PDCCH_RA_RNTI_RECEIVED_STRU;

typedef struct __LPHY_VITERBI_PDCCH_CONNECT_MAC_RA_SUCCESS_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
}LPHY_TRACE_VITERBI_PDCCH_CONNECT_MAC_RA_SUCCESS_STRU;

typedef struct __LPHY_VITERBI_PDCCH_DL_SPS_PERIOD_CONFIG_OM_TRACE__
{
    UINT16 usCurrSysFn;
    UINT16 usCurrSubFn;
    UINT16 usInitSysFn;
    UINT16 usInitSubFn;
    UINT32 ulNextPeriodPos;
    UINT32 ulActualPeriodNum;
    UINT32 ulTotalPeriodNum;
    UINT16 usSemiSchedInteval;
    UINT16 usGrantStatus;
}LPHY_TRACE_VITERBI_PDCCH_DL_SPS_PERIOD_CONFIG_STRU;

typedef struct __LPHY_VITERBI_PDCCH_UL_SPS_PERIOD_CONFIG_OM_TRACE__
{
    OM_UL_SPS_INIT_GRANT_STRU stUlSpsInitGrant;
}LPHY_TRACE_VITERBI_PDCCH_UL_SPS_PERIOD_CONFIG_STRU;

/*上下行半静态公共数据结构*/
typedef struct
{
    UINT16 enSpsConfigEnabled;
    UINT16 enPersistSchedInterval;
    UINT16 usNumOfSpsProcess;
    UINT16 enTwoIntervalsCfgValidFlg;
}OM_SEMI_SCHED_STRU;

typedef struct __LPHY_VITERBI_PDCCH_SPS_PARA_UPDATE_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usSpsRntiValidFlg;
    UINT16 usSpsRntiValue;
    OM_SEMI_SCHED_STRU stDlSemiSched;
    OM_SEMI_SCHED_STRU stUlSemiSched;
}LPHY_TRACE_VITERBI_PDCCH_SPS_PARA_UPDATE_STRU;

/*上行MAC指示半静态释放数据结构*/
typedef struct __LPHY_VITERBI_LMAC_UL_SPS_RELEASE_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
}LPHY_TRACE_VITERBI_LMAC_UL_SPS_RELEASE_STRU;

/*MCCH变更通知数据结构*/
typedef struct __LPHY_VITERBI_MCCH_CHANGE_NOTIFY_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usMbSfnFlag;
    UINT16 usMRntiValidFlag;
    UINT16 usMRntiValue;
    UINT16 ausDciValidFlag[2];
    UINT8  aucMcchNotifyData[2];
    UINT16 ausDciPower[2];
    UINT16 ausDciBlindTimes[2];
}LPHY_TRACE_VITERBI_MCCH_CHANGE_NOTIFY_STRU;

#define     MAX_TDD_UL_HARQ_NUM			(0x7)        	/*TDD最大上行HARQ进程数*/
#define 	MAX_TDD_UD_CFG_NUM     		(0x7)			/*TDD最大上下行配比个数*/

typedef struct
{
	UINT16 usValidFlag;		/*是否有效标志*/
	UINT16 usInitFlag;
	UINT16 usCurrSendPos;
  	UINT16 usNextSendPos; 	/*下一次发送位置*/
	UINT16 usDci0RecvFlag;
	UINT16 usReserved;
}PDCCH_TDD_UL_SPEC_HARQ_STRU;

typedef struct
{
  	PDCCH_TDD_UL_SPEC_HARQ_STRU astTddUlSpecHarq[MAX_TDD_UL_HARQ_NUM];
}PDCCH_TDD_UL_SPEC_CFG_STRU;

typedef struct __LPHY_VITERBI_PDCCH_UL_SPEC_CFG_OM_TRACE__
{
    UINT16 usCurrSysFn;
    UINT16 usCurrSubFn;
    UINT16 usTranSysFn;
    UINT16 usTranSubFn;
	UINT16 usHarqNum;
    UINT16 usTddUDConfig;
    PDCCH_TDD_UL_SPEC_CFG_STRU astTddUlSpecCfg[MAX_TDD_UD_CFG_NUM];
}LPHY_TRACE_VITERBI_PDCCH_UL_SPEC_CFG_STRU;

typedef struct __LPHY_VITERBI_PHICH_RESULT_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usPhichOrgNum;
    UINT16 usPhichNum;
	UINT16 usPhichIdx;
	UINT8  aucPhichResult[2];
}LPHY_TRACE_VITERBI_PHICH_RESULT_STRU;
typedef struct __LPHY_VITERBI_TRACE_REPORT_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 usData[4];
}LPHY_TRACE_VITERBI_TRACE_REPORT_STRU;
/************************************************************
                           5. ERROR数据结构定义
************************************************************/
typedef enum __LPHY_ERROR_VITERBI_ENUM__
{
    /*PBCH, ERROR ID 1 - 15*/
    LPHY_ERROR_VITERBI_PBCH_CELL_PARA_FAIL              = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_ERROR, 0x1),
    LPHY_ERROR_VITERBI_PBCH_DET_MODE_FAIL,
    LPHY_ERROR_VITERBI_PBCH_DECODE_UNFINISHED,

    /*PBCH, WARNING ID 16 - 31*/
    LPHY_WARNING_VITERBI_PBCH_RESERVED                  = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_ERROR, 0x10),

    /*PDCCH, ERROR ID 32 - 63*/
    LPHY_ERROR_VITERBI_PDCCH_NO_RNTI                    = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_ERROR, 0x20),
    LPHY_ERROR_VITERBI_PDCCH_INVALID_CFI,
    LPHY_ERROR_VITERBI_PDCCH_DEC_UNFINISHED,
    LPHY_ERROR_VITERBI_PHICH_NUM_OVERFLOW,
    LPHY_ERROR_VITERBI_PDCCH_TDD_UL_HARQ_OVERFLOW,

    /*PDCCH, WARNING ID 64 - 4095*/
    LPHY_WARNING_VITERBI_PDCCH_CHN_NUM_OVERFLOW         = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_ERROR, 0x40),
    LPHY_WARNING_VITERBI_PDCCH_NOISE_PWR_ZERO,
    LPHY_WARNING_VITERBI_SPS_PARA_MISMATCH,
}LPHY_ERROR_VITERBI_ENUM;
typedef UINT16 LPHY_ERROR_VITERBI_ENUM_UINT16;

/*PBCH*/
typedef struct __LPHY_VITERBI_PBCH_DET_MODE_FAIL_OM_ERROR__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 ulPbchDetMode;
}LPHY_ERROR_VITERBI_PBCH_DET_MODE_FAIL_STRU;

/*PDCCH*/
typedef struct __LPHY_VITERBI_PDCCH_NO_RNTI_OM_ERROR__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usPdcChnValid;
    UINT16 usRntiValid;
}LPHY_ERROR_VITERBI_PDCCH_NO_RNTI_STRU;

typedef struct __LPHY_VITERBI_PDCCH_INVALID_CFI_OM_ERROR__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usCfiValue;
    UINT16 usBandWidth;
}LPHY_ERROR_VITERBI_PDCCH_INVALID_CFI_STRU;

typedef struct __LPHY_VITERBI_PDCCH_DEC_UNFINISHED_OM_ERROR__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usPdcDecFinish;
    UINT16 usCfiValid;
}LPHY_ERROR_VITERBI_PDCCH_DEC_UNFINISHED_STRU;

typedef struct __LPHY_VITERBI_PDCCH_CHN_NUM_OVERFLOW_OM_ERROR__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 ulChanNum;
}LPHY_ERROR_VITERBI_PDCCH_CHN_NUM_OVERFLOW_STRU;

typedef struct __LPHY_VITERBI_PDCCH_NOISE_PWR_ZERO_OM_ERROR__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 ulNoisePwr;
    UINT32 ulSignalPwr;
}LPHY_ERROR_VITERBI_PDCCH_NOISE_PWR_ZERO_STRU;


/************************************************************
                           6. DEBUG数据结构定义
************************************************************/
/*Viterbi上报的数据长度, DW, 注意需要软硬件接口同步, 由于目前HSO不支持条件宏方式区分, 此处给出较大值, MPW: 0x204, Pilot: 0x230*/
#define     OM_VITERBI_MAX_RPT_PCELL_REG_IMG_LEN       ((0x378 - 0x200) / 4 + 1)
#define     OM_VITERBI_MAX_RPT_SCELL_REG_IMG_LEN       ((0x484 - 0x37c) / 4 + 1)
#define     OM_VITERBI_CFG_REG_IMG_LEN                 ((0xbc - 0x5c) / 4 + 1)

typedef enum __LPHY_DEBUG_VITERBI_ENUM__
{
    /*PBCH, INFO ID  1 - 63*/
    LPHY_DEBUG_VITERBI_PBCH_GAP                          = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_DEBUG, 0x1),

    /*PDCCH, INFO ID 64 - 4095*/
    LPHY_DEBUG_VITERBI_PDCCH_DCI_LEN                     = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_DEBUG, 0x40),
    LPHY_DEBUG_VITERBI_PDCCH_SEARCH_SPACE,
    LPHY_DEBUG_VITERBI_PDCCH_RPT_REGS_IMAGE,
    LPHY_DEBUG_VITERBI_PDCCH_CDRX_HARQ_RTT,
    LPHY_DEBUG_VITERBI_PDCCH_CFG_REGS_IMAGE,
    LPHY_DEBUG_VITERBI_PDCCH_RPT_REGS_IMAGE_SCELL,
}LPHY_DEBUG_VITERBI_ENUM;
typedef UINT16 LPHY_DEBUG_VITERBI_ENUM_UINT16;

/*PBCH*/
typedef struct __LPHY_VITERBI_PBCH_GAP_OM_DEBUG__
{
    UINT16 usPrevSfn;
    UINT16 usCurrSfn;
}LPHY_DEBUG_VITERBI_PBCH_GAP_STRU;

/*PDCCH*/
typedef enum
{
    RNTI_INVALID = 0,
    RNTI_EXIST,
    RNTI_VALID,
    RNTI_BUTT
}OM_RNTI_STATUS_ENUM;
typedef UINT16 OM_RNTI_STATUS_ENUM_UINT16;

typedef struct
{
    OM_RNTI_STATUS_ENUM_UINT16 enRntiStatus;
    UINT16 usRntiValue;
}OM_RNTI_STRU;

typedef struct
{
    UINT32       ulRntiValidFlag;  /*存在RNTI标志*/
    OM_RNTI_STRU stRaRnti;         /*RA-RNTI*/
    OM_RNTI_STRU stPRnti;          /*P-RNTI*/
    OM_RNTI_STRU stSiRnti;         /*SI-RNTI*/
    OM_RNTI_STRU stCRnti;          /*C-RNTI*/
    OM_RNTI_STRU stSpsRnti;        /*SPS-RNTI*/
    OM_RNTI_STRU stTcRnti;         /*TC-RNTI*/
    OM_RNTI_STRU stPucchTpcRnti;   /*PUCCH-TPC-RNTI*/
    OM_RNTI_STRU stPuschTpcRnti;   /*PUSCH-TPC-RNTI*/
    OM_RNTI_STRU stMRnti;          /*M-RNTI*/
}OM_RNTI_LIST_STRU;

typedef struct __LPHY_VITERBI_PDCCH_DCI_LEN_OM_DEBUG__
{
    UINT16            usDci1CLen;

    UINT16            usDci01ACommLen;
    UINT16            ausDci01AUeLen[2];
    UINT16            ausDciXLen[2];
    //UINT16            ausTranMode[2];

    OM_RNTI_LIST_STRU stRntiList;
}LPHY_DEBUG_VITERBI_PDCCH_DCI_LEN_STRU;

typedef struct __LPHY_VITERBI_PDCCH_SEARCH_SPACE_OM_DEBUG__
{
    UINT16 usMiBlindDetFlag;
    UINT16 usStartLocUeL1;
    UINT16 usStartLocUeL2;
    UINT16 usStartLocUeL4;
    UINT16 usStartLocUeL8;
    UINT16 usSrchTimesUeL1;
    UINT16 usSrchTimesUeL2;
    UINT16 usSrchTimesUeL4;
    UINT16 usSrchTimesUeL8;
    UINT16 usSrchTimesBdMiZero;
    UINT16 usSrchTimesBdMiOne;
    UINT16 usSrchTimesBdMiTwo;
    UINT16 usNcceNum;
    UINT16 usRsd;
}LPHY_DEBUG_VITERBI_PDCCH_SEARCH_SPACE_STRU;

typedef struct __LPHY_VITERBI_PDCCH_RPT_REGS_IMAGE_OM_DEBUG__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 ulIntAlarm;
    UINT32 aulRegImg[OM_VITERBI_MAX_RPT_PCELL_REG_IMG_LEN];
}LPHY_DEBUG_VITERBI_PDCCH_RPT_REGS_IMAGE_STRU;

typedef struct __LPHY_VITERBI_PDCCH_RPT_REGS_IMAGE_SCELL_OM_DEBUG__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 aulRegImg[OM_VITERBI_MAX_RPT_SCELL_REG_IMG_LEN];
}LPHY_DEBUG_VITERBI_PDCCH_RPT_REGS_IMAGE_SCELL_STRU;
/*HARQ RTT Timer标志*/
typedef enum
{
    HARQ_RTT_DL = 0,
    HARQ_RTT_UL_DCI0,
    HARQ_RTT_UL_PHICH,
}HARQ_RTT_TIMER_TYPE_ENUM;
typedef UINT16 HARQ_RTT_TIMER_TYPE_ENUM_UINT16;

typedef struct
{
    UINT16 usHarqRttTimerValidFlag;
    HARQ_RTT_TIMER_TYPE_ENUM_UINT16 enHarqRttTimerType;
    UINT16 usHarqNum;
    UINT16 usHarqRttTimer;
    UINT16 usNewTranFlag;
    UINT16 usSemiGrantFlag;
}LPHY_PDCCH_CDRX_HARQ_RTT_COM_STRU;

typedef struct
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    LPHY_PDCCH_CDRX_HARQ_RTT_COM_STRU stDlHarqRtt;
    LPHY_PDCCH_CDRX_HARQ_RTT_COM_STRU astUlHarqRttDci0[2];
    LPHY_PDCCH_CDRX_HARQ_RTT_COM_STRU astUlHarqRttPhich[2];
}LPHY_PDCCH_CDRX_HARQ_RTT_STRU;
typedef struct __LPHY_VITERBI_PDCCH_CFG_REGS_IMAGE_OM_DEBUG__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 ulCaPara;
    UINT32 aulRegImg[OM_VITERBI_CFG_REG_IMG_LEN];
}LPHY_DEBUG_VITERBI_PDCCH_CFG_REGS_IMAGE_STRU;


/*BEGIN: by humin, 2015/05/08*/
#if 1
/************************************************************
                             数据结构定义
************************************************************/
typedef struct
{
    LPHY_REQ_VITERBI_STUB_DCI_ENA_STRU      stReqStubDciEna;
}LPHY_REQ_VITERBI_CFG_ENA_STRU;

typedef struct
{
    LPHY_REQ_VITERBI_RPT_CFI_STAT_ENA_STRU  stReqRptCfiStatEna;
    UINT32 ulPeriodRptCnt;
}LPHY_REQ_VITERBI_RPT_CFI_STAT_STRU;

typedef struct
{
    LPHY_REQ_VITERBI_RPT_PDCCH_GRANT_STAT_ENA_STRU stReqRptPdcchGrantStatEna;
    UINT32 ulPeriodRptCnt;
}LPHY_REQ_VITERBI_RPT_PDCCH_GRANT_STAT_STRU;

typedef struct
{
    LPHY_REQ_VITERBI_RPT_PDCCH_BLER_ENA_STRU stReqRptPdcBlerEna;
    UINT32 ulPeriodRptCnt;
}LPHY_REQ_VITERBI_RPT_PDCCH_BLER_STRU;

typedef struct
{
    LPHY_REQ_VITERBI_RPT_CFI_ENA_STRU               stReqRptCfiEna;
    LPHY_REQ_VITERBI_RPT_CFI_STAT_STRU              stReqRptCfiStat;
    LPHY_REQ_VITERBI_RPT_PDCCH_SINR_ENA_STRU        stReqRptPdcchSinrEna;
    LPHY_REQ_VITERBI_RPT_PDCCH_DL_GRANT_ENA_STRU    stReqRptPdcchDlGrantEna;
    LPHY_REQ_VITERBI_RPT_PDCCH_UL_GRANT_ENA_STRU    stReqRptPdcchUlGrantEna;
    LPHY_REQ_VITERBI_RPT_PDCCH_PWR_GRANT_ENA_STRU   stReqRptPdcchPwrGrantEna;
    LPHY_REQ_VITERBI_RPT_PDCCH_GRANT_STAT_STRU      stReqRptPdcchGrantStat;
    LPHY_REQ_VITERBI_RPT_PDCCH_CCE_INFO_ENA_STRU    stReqRptPdcchCceInfo;
    LPHY_REQ_VITERBI_RPT_PDCCH_BLER_STRU            stReqRptPdcchBler;
}LPHY_REQ_VITERBI_RPT_ENA_STRU;

typedef struct
{
    LPHY_IND_VITERBI_RPT_CFI_STAT_STRU          stRptCfiStat;
    LPHY_IND_VITERBI_RPT_PDCCH_GRANT_STAT_STRU  stRptPdcGrantStat;
    LPHY_IND_VITERBI_RPT_PDCCH_BLER_STRU        stRptPdcBlerStat;
}LPHY_IND_VITERBI_RPT_STRU;


/************************************************************
                           7.DT命令和对应的数据结构定义
************************************************************/
typedef UINT16 PDCCH_GRANT_DCI_ENUM_UINT16;

/*DT上报CFI 开关*/
typedef struct
{
   OM_REQ_ENABLE_ENUM_UINT16 enRptCfiEna;
   UINT16 usRsv;
}LPHY_DT_VITERBI_RPT_CFI_INFO_REQ_STRU;

/*DT上报 授权统计 开关*/
typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16  enRptPdcchGrantStatEna;
    UINT16 ulRptPdcchGrantStatPeriod;
}LPHY_DT_VITERBI_RPT_PDCCH_GRANT_STAT_REQ_STRU;

/*DT上报 下行授权 开关*/
typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16 enRptPdcchDlGrantEna;
    UINT16 usRsv;
}LPHY_DT_VITERBI_RPT_PDCCH_DL_GRANT_INFO_REQ_STRU;

/*DT上报 PDCCH BLER开关*/
typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16 enRptPdcBlerEna;
    UINT16 ulRptPdcchBlerPeriod;
}LPHY_DT_VITERBI_RPT_PDCCH_BLER_REQ_STRU;

typedef enum __LPHY_DT_IND_VITERBI__
{
    LPHY_DT_VITERBI_RPT_CFI_INFO_CA_IND                   = OM_CMD_ID(LPHY_VITERBI_MID, OM_TYPE_DT, 0x1),
    LPHY_DT_VITERBI_RPT_PDCCH_GRANT_CA_STAT_IND,
    LPHY_DT_VITERBI_RPT_PDCCH_DL_GRANT_CA_INFO_IND,
    LPHY_DT_VITERBI_RPT_PDCCH_BLER_CA_IND,
}LPHY_DT_IND_VITERBI;

typedef struct __LPHY_DT_VITERBI_CFI_INFO_STRU__
{
    UINT8 ucCcValidFlg;
    UINT8 ucCcIdx;
    UINT16 ulCfi;
}LPHY_DT_VITERBI_CFI_INFO_STRU;

/*DT上报CFI值*/
typedef struct __LPHY_DT_VITERBI_RPT_CFI_INFO_CA_IND_STRU__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    LPHY_DT_VITERBI_CFI_INFO_STRU stDtCfiInfo[MAX_CELL_NUM_DL];
}LPHY_DT_VITERBI_RPT_CFI_INFO_CA_IND_STRU;

/*DT上报授权统计信息*/
typedef struct __LPHY_DT_VITERBI_RPT_PDCCH_GRANT_STAT_CA_IND_STRU__
{
    UINT8 ucCcValidFlg;
    UINT8 ucCcIdx;
    UINT16 usRsv;
    UINT32 ulAccuUlGrantNum;
    UINT32 ulAccuDlGrantNum;
    UINT32 ulAccuCce1Num;
    UINT32 ulAccuCce2Num;
    UINT32 ulAccuCce4Num;
    UINT32 ulAccuCce8Num;
    UINT32 ulAccuDci0Num;
    UINT32 ulAccuDci1Num;
    UINT32 ulAccuDci1ANum;
    UINT32 ulAccuDci1BNum;
    UINT32 ulAccuDci1CNum;
    UINT32 ulAccuDci1DNum;
    UINT32 ulAccuDci2Num;
    UINT32 ulAccuDci2ANum;
    UINT32 ulAccuDci2BNum;
    UINT32 ulAccuDci3Num;
    UINT32 ulAccuDci3ANum;
} LPHY_DT_VITERBI_RPT_PDCCH_GRANT_STAT_CA_IND_STRU;


/*DT上报下行授权信息*/
typedef struct __LPHY_DT_VITERBI_RPT_PDCCH_DL_GRANT_INFO_IND_STRU__
{
    UINT8 ucCcValidFlg;
    UINT8 ucCcIdx;
    UINT16 usRsv;
    UINT16 usRbNum;
    UINT16 usRbStart;
    UINT16 usHarqId;
    //UINT16 usRsv;
    PDCCH_GRANT_DCI_ENUM_UINT16 enDciType;
    UINT8  ucCW0Mcs;
    UINT8  ucCW1Mcs;
    UINT8  ucDlCW0ModSched;
    UINT8  ucDlCW1ModSched;
    UINT16 usCW0RvIndex;
    UINT16 usCW1RvIndex;
    UINT32 ulCW0TbSize;
    UINT32 ulCW1TbSize;
    UINT16 ulTransScheme;
    UINT16 usRsv2;
}LPHY_DT_VITERBI_RPT_PDCCH_DL_GRANT_INFO_IND_STRU;

typedef struct __LPHY_DT_VITERBI_RPT_PDCCH_DL_GRANT_INFO_CA_IND_STRU__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    LPHY_DT_VITERBI_RPT_PDCCH_DL_GRANT_INFO_IND_STRU stDtPdcchGrantInfo[MAX_CELL_NUM_DL];
}LPHY_DT_VITERBI_RPT_PDCCH_DL_GRANT_INFO_CA_IND_STRU;


/*DT上报PDCCH_BLER信息*/
typedef struct __LPHY_DT_VITERBI_RPT_PDCCH_BLER_CA_IND_STRU__
{
    UINT8 ucCcValidFlg;
    UINT8 ucCcIdx;
    UINT16 usRsv;
    UINT32 ulPdcchAccuErrorNum;
    UINT32 ulPdcchAccuTotalNum;
}LPHY_DT_VITERBI_RPT_PDCCH_BLER_CA_IND_STRU;

typedef struct
{
    LPHY_DT_VITERBI_RPT_PDCCH_GRANT_STAT_REQ_STRU  stRptPdcchGrantStatEna;
    UINT32 ulPeriodRptCnt;
}LPHY_DT_VITERBI_RPT_PDCCH_GRANT_STAT_REQ_CNT_STRU;

typedef struct
{
    LPHY_DT_VITERBI_RPT_PDCCH_BLER_REQ_STRU stRptPdcBlerEna;
    UINT32 ulPeriodRptCnt;
}LPHY_DT_VITERBI_RPT_PDCCH_BLER_REQ_CNT_STRU;

typedef struct
{
    LPHY_DT_VITERBI_RPT_CFI_INFO_REQ_STRU              stDtReqRptCfiInfo;
    LPHY_DT_VITERBI_RPT_PDCCH_GRANT_STAT_REQ_CNT_STRU  stDtReqRptPdcchGrantStat;
    LPHY_DT_VITERBI_RPT_PDCCH_DL_GRANT_INFO_REQ_STRU   stDtReqRptPdcchDlGrantInfo;
    LPHY_DT_VITERBI_RPT_PDCCH_BLER_REQ_CNT_STRU        stDtReqRptPdcchBler;
}LPHY_DT_REQ_VITERBI_RPT_ENA_STRU;


typedef struct
{
    LPHY_DT_VITERBI_RPT_PDCCH_GRANT_STAT_CA_IND_STRU      stDtIndRptPdcchGrantStat[MAX_CELL_NUM_DL];
    LPHY_DT_VITERBI_RPT_PDCCH_BLER_CA_IND_STRU            stDtIndRptPdcBlerStat[MAX_CELL_NUM_DL];
    LPHY_DT_VITERBI_RPT_CFI_INFO_CA_IND_STRU stDtIndRptCfiVal;
    LPHY_DT_VITERBI_RPT_PDCCH_DL_GRANT_INFO_CA_IND_STRU stDtIndRptPdcchGrantInfo;
}LPHY_DT_IND_VITERBI_RPT_STRU;
#endif
/*END: by humin, 2015/05/08*/

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif /* __cplusplus */


#endif /* __VITERBI_OM_DEF_H__ */


