/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : turbo_om_def.h
  版 本 号   : 初稿
  作    者   : chenguangwen
  生成日期   : 2011年3月8日
  最近修改   :
  功能描述   : 定义Turbo模块OM需要上报的结构体,该文件最终会交付给HiStudio使用
  函数列表   :
  修改历史   :
  1.日    期   : 2011年3月8日
    作    者   : chenguangwen
    修改内容   : 创建文件

  2.日    期   : 2011年6月8日
    作    者   : chenguangwen
    修改内容   : [DTS2011060800603]新增OM代码合入

  3.日    期   : 2011年7月14日
    作    者   : chenguangwen
    修改内容   : [DTS20110701404324]新增OM代码合入
    
  4.日    期   : 2011年11月28日
    作    者   : chenguangwen
    修改内容   : [DTS2011111800531]Pilot版本合入   
    
  5.日    期   : 2011年12月14日
    作    者   : chenguangwen
    修改内容   : [DTS2011121306897]合入eMBMS算法需求       

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

#ifndef __TURBO_OM_DEF_H__
#define __TURBO_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */



/************************************************************
                           1. REQ命令和对应的数据结构定义
************************************************************/
enum __LPHY_REQ_TURBO__
{
    LPHY_REQ_TURBO_CFG_HARQ_SWITCH_ENA          = OM_CMD_ID(LPHY_TURBO_MID, OM_TYPE_REQ, 0x1),
    LPHY_REQ_TURBO_CFG_HARQ_RE_TRAN_SWITCH_ENA,
    LPHY_REQ_TURBO_RPT_DLSCH_BLER_ENA,
    LPHY_REQ_TURBO_RPT_DLSCH_HARQ_BLER_ENA,
    LPHY_REQ_TURBO_RPT_DL_THROUGHPUT_STAT_ENA,
    LPHY_REQ_TURBO_RPT_DL_TRAN_SUCC_STAT_ENA,
    LPHY_DT_TURBO_RPT_DLSCH_BLER_REQ            = OM_CMD_ID(LPHY_TURBO_MID, OM_TYPE_REQ, 0x100),        
    LPHY_DT_TURBO_RPT_DL_THROUGHPUT_STAT_REQ 
};

typedef struct
{
    OM_REQ_ENABLE_ENUM enCfgHarqSwitchEna;
}LPHY_REQ_TURBO_CFG_HARQ_SWITCH_ENA_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM enCfgHarqReTranSwitchEna;
    UINT32 ulCfgReTranTotalTimes;
}LPHY_REQ_TURBO_CFG_HARQ_RE_TRAN_SWITCH_ENA_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM enRptDlschBlerEna;
    UINT32 ulRptDlschBlerPeriod;
}LPHY_REQ_TURBO_RPT_DLSCH_BLER_ENA_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM enRptDlschHarqBlerEna;
    UINT32 ulRptDlschHarqBlerPeriod;
}LPHY_REQ_TURBO_RPT_DLSCH_HARQ_BLER_ENA_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM enRptDlThrghputBlerEna;
    UINT32 ulRptDlThrghputPeriod;
}LPHY_REQ_TURBO_RPT_DL_THROUGHPUT_STAT_ENA_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM enRptDlTranSuccStatEna;
    UINT32 ulRptDlTranSuccStatPeriod;
}LPHY_REQ_TURBO_RPT_DL_TRAN_SUCC_STAT_ENA_STRU;


/************************************************************
                           2. CNF数据结构定义
************************************************************/
enum __LPHY_CNF_TURBO__
{
    LPHY_CNF_TURBO_CFG_HARQ_SWITCH_ENA          = OM_CMD_ID(LPHY_TURBO_MID, OM_TYPE_CNF, 0x1),
    LPHY_CNF_TURBO_RPT_DLSCH_BLER_ENA,
    LPHY_CNF_TURBO_RPT_DLSCH_HARQ_BLER_ENA,
    LPHY_CNF_TURBO_RPT_DL_THROUGHPUT_STAT_ENA,
    LPHY_CNF_TURBO_RPT_DL_TRAN_SUCC_STAT_ENA
};


/************************************************************
                           3. Ind数据结构定义
************************************************************/
typedef enum __LPHY_IND_TURBO__
{
    LPHY_IND_TURBO_RPT_DLSCH_BLER               = OM_CMD_ID(LPHY_TURBO_MID, OM_TYPE_IND, 0x1),
    LPHY_IND_TURBO_RPT_DLSCH_HARQ_BLER,
    LPHY_IND_TURBO_RPT_DL_THROUGHPUT_STAT,
    LPHY_IND_TURBO_RPT_DL_TRAN_SUCC_STAT
}LPHY_IND_TURBO_ENUM;

#define     OM_TURBO_PMCH_RPT_SUBFRAME_NUM       10
typedef struct __LPHY_TURBO_RPT_DLSCH_BLER_OM_IND__
{
    /*DL-SCH*/
    UINT16 ausDlschCW0TotalNum[DL_MAX_CELL_NUM];
    UINT16 ausDlschCW0ErrorNum[DL_MAX_CELL_NUM];
    UINT16 ausDlschCW1TotalNum[DL_MAX_CELL_NUM];
    UINT16 ausDlschCW1ErrorNum[DL_MAX_CELL_NUM];
    UINT32 aulDlschAccuCW0TotalNum[DL_MAX_CELL_NUM];
    UINT32 aulDlschAccuCW0ErrorNum[DL_MAX_CELL_NUM];
    UINT32 aulDlschAccuCW1TotalNum[DL_MAX_CELL_NUM];
    UINT32 aulDlschAccuCW1ErrorNum[DL_MAX_CELL_NUM];

    /*PMCH*/
    UINT16 usPmchTotalNum;
    UINT16 usPmchErrorNum;
    UINT32 ulPmchAccuTotalNum;
    UINT32 ulPmchAccuErrorNum;
    UINT32 ulPmchAccuSubFrameTotalNum[OM_TURBO_PMCH_RPT_SUBFRAME_NUM];
    UINT32 ulPmchAccuSubFrameErrorNum[OM_TURBO_PMCH_RPT_SUBFRAME_NUM];
}LPHY_IND_TURBO_RPT_DLSCH_BLER_STRU;

typedef struct __LPHY_TURBO_RPT_DLSCH_HARQ_BLER_OM_IND__
{
    UINT16 ausCW0InitTotal[DL_MAX_CELL_NUM];
    UINT16 ausCW0InitError[DL_MAX_CELL_NUM];
    UINT16 ausCW1InitTotal[DL_MAX_CELL_NUM];
    UINT16 ausCW1InitError[DL_MAX_CELL_NUM];
    UINT16 ausCW0ReTotal[DL_MAX_CELL_NUM];
    UINT16 ausCW0ReError[DL_MAX_CELL_NUM];
    UINT16 ausCW1ReTotal[DL_MAX_CELL_NUM];
    UINT16 ausCW1ReError[DL_MAX_CELL_NUM];
    UINT32 aulAccuCW0InitTotal[DL_MAX_CELL_NUM];
    UINT32 aulAccuCW0InitError[DL_MAX_CELL_NUM];
    UINT32 aulAccuCW1InitTotal[DL_MAX_CELL_NUM];
    UINT32 aulAccuCW1InitError[DL_MAX_CELL_NUM];
    UINT32 aulAccuCW0ReTotal[DL_MAX_CELL_NUM];
    UINT32 aulAccuCW0ReError[DL_MAX_CELL_NUM];
    UINT32 aulAccuCW1ReTotal[DL_MAX_CELL_NUM];
    UINT32 aulAccuCW1ReError[DL_MAX_CELL_NUM];
}LPHY_IND_TURBO_RPT_DLSCH_HARQ_BLER_STRU;

typedef struct __LPHY_TURBO_RPT_DL_THROUGHPUT_STAT_OM_IND__
{
    UINT32 aulCW0TotalBitNum[DL_MAX_CELL_NUM];
    UINT32 aulCW1TotalBitNum[DL_MAX_CELL_NUM];
}LPHY_IND_TURBO_RPT_DL_THROUGHPUT_STAT_STRU;

typedef struct __LPHY_TURBO_RPT_DL_TRAN_SUCC_CELL__
{
    UINT16 usCW0InitSuccNum;
    UINT16 usCW0ReTran1SuccNum;
    UINT16 usCW0ReTran2SuccNum;
    UINT16 usCW0ReTran3SuccNum;
    UINT16 usCW0ReTran4SuccNum;
    UINT16 usRsd1;
    UINT16 usCW1InitSuccNum;
    UINT16 usCW1ReTran1SuccNum;
    UINT16 usCW1ReTran2SuccNum;
    UINT16 usCW1ReTran3SuccNum;
    UINT16 usCW1ReTran4SuccNum;
    UINT16 usRsd2;
}LPHY_TURBO_RPT_DL_TRAN_SUCC_CELL_STRU;
typedef struct __LPHY_TURBO_RPT_DL_TRAN_SUCC_STAT_OM_IND__
{
    LPHY_TURBO_RPT_DL_TRAN_SUCC_CELL_STRU astCellSuccStat[DL_MAX_CELL_NUM];
}LPHY_IND_TURBO_RPT_DL_TRAN_SUCC_STAT_STRU;


/************************************************************
                           4. TRACE数据结构定义
************************************************************/
typedef enum __LPHY_TRACE_TURBO_ENUM__
{
    LPHY_TRACE_TURBO_DECODE_FLOAT_INT_TRIGGERED         = OM_CMD_ID(LPHY_TURBO_MID, OM_TYPE_TRACE, 0x1),
    LPHY_TRACE_TURBO_DECODE_DATA_DMA_REPORT,
    LPHY_TRACE_TURBO_DECODE_SIB,
    LPHY_TRACE_TURBO_DECODE_PCH,
    LPHY_TRACE_TURBO_DECODE_FLOAT_INT_PCELL,
    LPHY_TRACE_TURBO_DECODE_FLOAT_INT_SCELL,
}LPHY_TRACE_TURBO_ENUM;
typedef UINT16 LPHY_TRACE_TURBO_ENUM_UINT16;

/*Turbo译码完成浮动中断Trace*/
typedef struct
{
    UINT16 usChanValidFlag;           /*0: 失能, 1: 使能*/
    UINT16 usCrcFlag;                 /*0: 错误, 1: 正确, 注意与BBP定义相反*/
    UINT32 ulTbs;                     /*TBS*/
    UINT32 ulG;                       /*G*/
    //UINT32 ulRamAddr;                 /*RAM源地址*/
}PDSCH_DECODE_RESULT_COM_STRU;

typedef struct
{
    UINT16 enRntiType;
    UINT16 usHarqNum;
    UINT16 usKmimo;
    UINT16 usTbSwapFlag;
    UINT16 usPmchValidFlag;
    UINT16 usAreaId;
    UINT16 usPmchIdx;
    UINT16 usReserved;
    PDSCH_DECODE_RESULT_COM_STRU astDlschTbDecResult[2];
}PDSCH_DLSCH_DECODE_RESULT_STRU;

typedef struct
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    PDSCH_DLSCH_DECODE_RESULT_STRU stDlschDecResult;
    PDSCH_DECODE_RESULT_COM_STRU   stBcchDecResult;
    PDSCH_DECODE_RESULT_COM_STRU   stPchDecResult;
}PDSCH_DECODE_RESULT_STRU;
typedef struct __LPHY_TRACE_TURBO_DECODE_FLOAT_INT_PCELL_OM_TRACE__
{
    PDSCH_DECODE_RESULT_STRU stDecodeResult;
    UINT16 usIntFlag;
    UINT16 usRsv;
}LPHY_TRACE_TURBO_DECODE_FLOAT_INT_PCELL_STRU;
typedef struct __LPHY_TRACE_TURBO_DECODE_FLOAT_INT_SCELL_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usIntFlag;
    UINT16 usCcStoreIdx;
    PDSCH_DLSCH_DECODE_RESULT_STRU stScellDecodeResult;
}LPHY_TRACE_TURBO_DECODE_FLOAT_INT_SCELL_STRU;

typedef struct __LPHY_TURBO_DECODE_FLOAT_INT_TRIGGERED_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 ulTdlErrRptReg;
    UINT32 ulTdlIntStatReg;
    UINT32 ulIntAlmReg;
    //LPHY_PDSCH_DECODE_RESULT_STRU stPdschDecResult;
}LPHY_TRACE_TURBO_DECODE_FLOAT_INT_TRIGGERED_STRU;

/*Turbo译码数据面DMA上报Trace*/
typedef struct __TDL_DMA_CHAN_S__
{
    UINT32                      ulDestAddr;
    UINT32                      ulLen;
    UINT32                      ulEnable;
    //UINT32                      ulRsv;
}TDL_DMA_CHAN_STRU;

typedef struct __TDL_DMA_DESCRIPTOR__
{
    //UINT32                      ulChanNum;
    TDL_DMA_CHAN_STRU           stSCH0Pcc;
    TDL_DMA_CHAN_STRU           stSCH1Pcc;
    TDL_DMA_CHAN_STRU           stBCCH;
    TDL_DMA_CHAN_STRU           stPCH;
    TDL_DMA_CHAN_STRU           stHeadSCH0Pcc;
    TDL_DMA_CHAN_STRU           stHeadSCH1Pcc;
    TDL_DMA_CHAN_STRU           stHeadBCCH;
    TDL_DMA_CHAN_STRU           stHeadPCH;


    TDL_DMA_CHAN_STRU           stSCH0Scc;
    TDL_DMA_CHAN_STRU           stSCH1Scc;
    TDL_DMA_CHAN_STRU           stHeadSCH0Scc;
    TDL_DMA_CHAN_STRU           stHeadSCH1Scc;
}TDL_DMA_DESCRIPTOR_STRU;
typedef struct __LPHY_TRACE_TURBO_DECODE_DATA_DMA_REPORT_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    TDL_DMA_DESCRIPTOR_STRU stTdlDmaDescriptor;
}LPHY_TRACE_TURBO_DECODE_DATA_DMA_REPORT_STRU;
typedef struct __LPHY_TRACE_TURBO_DECODE_TRACE_RPT_OM_TRACE__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 aulData[4];
}LPHY_TRACE_TURBO_DECODE_TRACE_RPT_STRU;


/************************************************************
                           5. ERROR数据结构定义
************************************************************/
typedef enum __LPHY_ERROR_TURBO_ENUM__
{
    /*PDSCH, ERROR ID 1 - 63*/
    LPHY_ERROR_TURBO_CB_NUM_ZERO                        = OM_CMD_ID(LPHY_TURBO_MID, OM_TYPE_ERROR, 0x1),
    LPHY_ERROR_TURBO_CHN_NUM_ZERO,
    LPHY_ERROR_TURBO_DATA_DMA_EXCEPTION,
    LPHY_ERROR_TURBO_PDSCH_DECODE_EXCEPTION,

    /*PDSCH, WARNING ID 64 - 4095*/
    LPHY_WARNING_TURBO_DEM_CHN_MISMATCH                 = OM_CMD_ID(LPHY_TURBO_MID, OM_TYPE_ERROR, 0x40),
    LPHY_WARNING_TURBO_DEM_CHN_NUM_ZERO,
    LPHY_WARNING_TURBO_TB_IDX_OVERFLOW,
    LPHY_WARNING_TURBO_CHN_TYPE_MISMATCH,
    LPHY_WARNING_TURBO_TRAN_SCHEME_MISMATCH,
    LPHY_WARNING_TURBO_TRAN_LAYER_MISMATCH,
    LPHY_WARNING_TURBO_TBS_UPDATE_WRONG_RNTI,
    LPHY_WARNING_TURBO_ACK_RE_TRAN,
    LPHY_WARNING_TURBO_PPU_CALC_WRONG,
    LPHY_WARNING_TURBO_K_SEARCH_WRONG,
    LPHY_WARNING_TURBO_NON_EIGHT_BYTES_ALIGN,
    LPHY_WARNING_TURBO_DMA_CHN_TYPE_MISMATCH,
}LPHY_ERROR_TURBO_ENUM;
typedef UINT16 LPHY_ERROR_TURBO_ENUM_UINT16;

typedef struct __LPHY_TURBO_CB_NUM_ZERO_OM_ERROR__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usCplus;
    UINT16 usCminus;
}LPHY_ERROR_TURBO_CB_NUM_ZERO_STRU;

typedef struct __LPHY_TURBO_CHN_NUM_ZERO_OM_ERROR__
{
    UINT32 ulTdlErrRptReg;
    PDSCH_DECODE_RESULT_STRU stPdschDecResult;
}LPHY_ERROR_TURBO_CHN_NUM_ZERO_STRU;

typedef struct __LPHY_TURBO_DATA_DMA_EXCEPTION_OM_ERROR__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 ulErrorType;
}LPHY_ERROR_TURBO_DATA_DMA_EXCEPTION_STRU;

typedef struct __LPHY_TURBO_PDSCH_DECODE_EXCEPTION_OM_ERROR__
{
    UINT32 ulTdlErrRptReg;
    PDSCH_DECODE_RESULT_STRU stPdschDecResult;
}LPHY_ERROR_TURBO_PDSCH_DECODE_EXCEPTION_STRU;

typedef struct __LPHY_TURBO_TURBO_DEM_CHN_OM_ERROR__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usDemChanNum;
    UINT16 usDciChanNum;
    UINT16 usCcFlg;
    UINT16 usRsv;
}LPHY_ERROR_TURBO_DEM_CHN_STRU;

typedef struct __LPHY_TURBO_TRAN_SCHEME_MISMATCH_OM_ERROR__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 ulTranScheme;
}LPHY_ERROR_TURBO_TRAN_SCHEME_MISMATCH_STRU;

typedef struct __LPHY_TURBO_TRAN_LAYER_MISMATCH_OM_ERROR__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 ulTranLayer;
}LPHY_ERROR_TURBO_TRAN_LAYER_MISMATCH_STRU;

typedef struct __LPHY_TURBO_NON_EIGHT_BYTES_ALIGN_OM_ERROR__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 ulDestAddr;
}LPHY_ERROR_TURBO_NON_EIGHT_BYTES_ALIGN_STRU;



/************************************************************
                           6. DEBUG数据结构定义
************************************************************/

#define     OM_TURBO_MAX_CFG_REG_IMG_LEN       ((0x112C - 0x0FD8) / 4 + 1)       /*Turbo配置的数据长度, DW, 注意需要软硬件接口同步*/

typedef enum __LPHY_DEBUG_TURBO_ENUM__
{
    LPHY_DEBUG_TURBO_PDSCH_CFG_REGS_IMAGE         = OM_CMD_ID(LPHY_TURBO_MID, OM_TYPE_DEBUG, 0x1),
    LPHY_DEBUG_TURBO_PDSCH_G_PARA,
    LPHY_DEBUG_TURBO_PMCH_CFG_PARA,
}LPHY_DEBUG_TURBO_ENUM;
typedef UINT16 LPHY_DEBUG_TURBO_ENUM_UINT16;


typedef struct __LPHY_TURBO_PDSCH_CFG_REGS_IMAGE_OM_DEBUG__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT32 aulRegImg[2][OM_TURBO_MAX_CFG_REG_IMG_LEN];/*扩展为2通道*/
}LPHY_DEBUG_TURBO_PDSCH_CFG_REGS_IMAGE_STRU;

typedef struct
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usCellId;
    UINT16 usDuplex;
    UINT16 usNumRbDl;
    UINT16 usTxAntNum;
    UINT16 usCpType;
    UINT16 usTddUDConfig;
    UINT16 usSFrameType;
    UINT16 usSubFrameType;
    UINT16 usCtrlSymNum;
    UINT16 usTransScheme;
}PDSCH_DECODE_SYS_INFO_STRU;

typedef struct __LPHY_TURBO_PDSCH_G_PARA_OM_DEBUG__
{
    UINT16 usNumReRealUse;
    UINT16 usNumReSlotSum;
    UINT16 usNumReCtrlInfo;
    UINT16 usNumReRsRemain;
    UINT16 usNumReRsBf;
    UINT16 usNumReSS;
    UINT16 usNumRePbch;
    UINT16 usRsd;
    PDSCH_DECODE_SYS_INFO_STRU stPdschSysInfo;
    UINT8 ucBitmapArray[2][100];
}LPHY_DEBUG_TURBO_PDSCH_G_PARA_STRU;

typedef struct __LPHY_TURBO_PMCH_CFG_PARA_OM_DEBUG__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usAreaId;
    UINT16 usMcchFlag;
    UINT16 usMtchFlag;
    UINT16 usPmchIdx;
    UINT16 usCpType;
    UINT16 usPdcchSymNum;
    UINT16 usNPrb;
    UINT16 usImcs;
    UINT16 usQm;
    UINT16 enTransScheme;
    UINT32 ulTbs;
    UINT32 ulG;
}LPHY_DEBUG_TURBO_PMCH_CFG_PARA_STRU;


/************************************************************
                           7. DT 数据结构定义
************************************************************/

/*typedef enum __LPHY_DT_TURBO_REQ_ENUM__
{
    LPHY_DT_TURBO_RPT_DLSCH_BLER_REQ         = OM_CMD_ID(LPHY_TURBO_MID, OM_TYPE_DT, 0x1),
    LPHY_DT_TURBO_RPT_DL_THROUGHPUT_STAT_REQ = OM_CMD_ID(LPHY_TURBO_MID, OM_TYPE_DT, 0x2)

}LPHY_DT_TURBO_REQ_ENUM;*/

typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16 enRptDlschBlerEna;
    UINT16 usRptDlschBlerPeriod;
}LPHY_DT_TURBO_RPT_DLSCH_BLER_REQ_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16 enRptDlThrghputBlerEna;
    UINT16 usRptDlThrghputPeriod;
}LPHY_DT_TURBO_RPT_DL_THROUGHPUT_STAT_REQ_STRU;



typedef enum __LPHY_DT_TURBO_IND_ENUM__
{
    LPHY_DT_TURBO_RPT_DLSCH_BLER_IND         = OM_CMD_ID(LPHY_TURBO_MID, OM_TYPE_DT, 0x1),
    LPHY_DT_TURBO_RPT_DLSCH_BLER_CA_IND       ,
    LPHY_DT_TURBO_RPT_DL_THROUGHPUT_STAT_IND  ,
    LPHY_DT_TURBO_RPT_DL_THROUGHPUT_STAT_CA_IND

}LPHY_DT_TURBO_IND_ENUM;

typedef struct __LPHY_DT_TURBO_RPT_DLSCH_BLER_IND_STRU__
{
    UINT8 ucCcValidFlg;
    UINT8 ucCcIdx;
    UINT16 usRsv;

    UINT32 aulDlschAccuTotalNum[2];
    UINT32 aulDlschAccuNackNum[2];
    UINT32 aulDlschAccuAckNum[2];
    UINT32 aulTransSuccNum[2][5];
    UINT32 aulReTransFailNum[2];
    UINT32 aulInitTransNACKNum[2];
    UINT32 aulInitTransTotalNum[2];
    UINT32 aulReTransNACKNum[2];
    UINT32 aulReTransTotalNum[2];
    UINT32 aulResidualNACKNum[2];
    UINT32 aulResidualTotalNum[2];
}LPHY_DT_TURBO_RPT_DLSCH_BLER_IND_STRU;

typedef struct __LPHY_DT_TURBO_RPT_DL_THROUGHPUT_STAT_IND_STRU__
{
    UINT8 ucCcValidFlg;
    UINT8 ucCcIdx;
    UINT16 usRsv;

    UINT32 ulCW0TotalBitNum;
    UINT32 ulCW1TotalBitNum;
    UINT32 ulTotalBitNum;
}LPHY_DT_TURBO_RPT_DL_THROUGHPUT_STAT_IND_STRU;


/* END:   by songwenning, 2014/3/19 */

/*BEGIN: by humin, 2015/05/07*/
#if 1

/************************************************************
                             数据结构定义
************************************************************/
typedef struct
{
    LPHY_REQ_TURBO_CFG_HARQ_RE_TRAN_SWITCH_ENA_STRU stReqCfgHarqReTranSwitchEna;
    UINT32 ulReTranCnt;
}LPHY_REQ_TURBO_CFG_HARQ_RE_TRAN_SWITCH_STRU;

typedef struct
{
    LPHY_REQ_TURBO_CFG_HARQ_SWITCH_ENA_STRU     stReqCfgHarqSwitchEna;
    LPHY_REQ_TURBO_CFG_HARQ_RE_TRAN_SWITCH_STRU stReqCfgHarqReTranSwitch;
}LPHY_REQ_TURBO_CFG_ENA_STRU;

typedef struct
{
    LPHY_REQ_TURBO_RPT_DLSCH_BLER_ENA_STRU stReqRptDlschBlerEna;
    UINT32 ulPeriodRptCnt;
}LPHY_REQ_TURBO_RPT_DLSCH_BLER_STRU;

typedef struct
{
    LPHY_REQ_TURBO_RPT_DLSCH_HARQ_BLER_ENA_STRU stReqRptDlschHarqBlerEna;
    UINT32  ulPeriodRptCnt;
}LPHY_REQ_TURBO_RPT_DLSCH_HARQ_BLER_STRU;

typedef struct
{
    LPHY_REQ_TURBO_RPT_DL_THROUGHPUT_STAT_ENA_STRU stReqRptDlThrghputStatEna;
    UINT32  ulPeriodRptCnt;
}LPHY_REQ_TURBO_RPT_DL_THROUGHPUT_STAT_STRU;

typedef struct
{
    LPHY_REQ_TURBO_RPT_DL_TRAN_SUCC_STAT_ENA_STRU stReqRptDlTranSuccStatEna;
    UINT32  ulPeriodRptCnt;
}LPHY_REQ_TURBO_RPT_DL_TRAN_SUCC_STAT_STRU;

typedef struct
{
    LPHY_REQ_TURBO_RPT_DLSCH_BLER_STRU          stReqRptDlschBler;
    LPHY_REQ_TURBO_RPT_DLSCH_HARQ_BLER_STRU     stReqRptDlschHarqBler;
    LPHY_REQ_TURBO_RPT_DL_THROUGHPUT_STAT_STRU  stReqRptDlThrghputStat;
    LPHY_REQ_TURBO_RPT_DL_TRAN_SUCC_STAT_STRU   stReqRptDlTranSuccStat;
}LPHY_REQ_TURBO_RPT_ENA_STRU;

typedef struct
{
    LPHY_IND_TURBO_RPT_DLSCH_BLER_STRU          stRptDlschBler;
    LPHY_IND_TURBO_RPT_DLSCH_HARQ_BLER_STRU     stRptDlschHarqBler;
    LPHY_IND_TURBO_RPT_DL_THROUGHPUT_STAT_STRU  stRptDlThrgputStat;
    LPHY_IND_TURBO_RPT_DL_TRAN_SUCC_STAT_STRU   stRptDlTranSuccStat;
}LPHY_IND_TURBO_RPT_STRU;

typedef struct
{
    LPHY_DT_TURBO_RPT_DLSCH_BLER_REQ_STRU stReqRptDlschBlerEna;
    UINT32 ulPeriodRptCnt;
}LPHY_DT_TURBO_RPT_DLSCH_BLER_REQ_CNT_STRU;

typedef struct
{
    LPHY_DT_TURBO_RPT_DL_THROUGHPUT_STAT_REQ_STRU stReqRptDlThrghputStatEna;
    UINT32  ulPeriodRptCnt;
}LPHY_DT_TURBO_RPT_DL_THROUGHPUT_STAT_REQ_CNT_STRU;

typedef struct
{
    LPHY_DT_TURBO_RPT_DLSCH_BLER_REQ_CNT_STRU          stDtReqRptDlschBler;
    LPHY_DT_TURBO_RPT_DL_THROUGHPUT_STAT_REQ_CNT_STRU  stDtReqRptDlThrghputStat;
}LPHY_DT_REQ_TURBO_RPT_ENA_STRU;

typedef struct
{
    LPHY_DT_TURBO_RPT_DLSCH_BLER_IND_STRU          stDtRptDlschBler;
    LPHY_DT_TURBO_RPT_DL_THROUGHPUT_STAT_IND_STRU  stDtRptDlThrgputStat;
}LPHY_DT_IND_TURBO_RPT_STRU;

/* END:   by songwenning, 2014/3/19 */
#endif
/*END: by humin, 2015/05/07*/
#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif /* __cplusplus */


#endif /* __TURBO_OM_DEF_H__ */
