/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : tds_ul_om_def.h
  版 本 号   : 初稿
  作    者   : h00130263
  生成日期   : 2012年8月30日
  最近修改   :
  功能描述   : TDS UL OM DEF / TDS上行可维可测接口
  函数列表   :
  修改历史   :
  1.日    期   : 2012年8月30日
    作    者   : h00130263
    修改内容   : 创建文件

******************************************************************************/
#ifndef TDSUL_OM_DEF_H_
#define TDSUL_OM_DEF_H_


#include "om_base_def.h"
#include "tds_datapath_interface.h"
//#include "tds_ul_interface.h"
#include "TPsTPhyInterface.h"

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define TDS_UL_MAX_TS_NUM             (0x6)
#define MAX_TRCH_CNT                  (maxTrCH)//6->8          //最大传输信道数
#define MAX_TRCH                      (maxTrCH)//6->8
#define MAX_TS_CNT                    (5)           //最大时隙数
//OM 类型定义
typedef enum
{
    TPHY_REQ_UL_REPORT_ENA         = OM_TCMD_ID(TPHY_UL_MID, OM_TYPE_REQ, 0x0),
    TPHY_REQ_UL_PWR_SET,
    TPHY_REQ_UL_SS_SET,
    TPHY_REQ_UL_UPPCH_LOOP,
    TPHY_REQ_UL_DATA_SAMPLE,
    TPHY_REQ_UL_ZERO_PADDING,
    TPHY_REQ_UL_SPEED_REPORT,

    TPHY_REQ_TAS_REPORT,  //+TAS OM 20141014 借用TDS UL的OM结构
    TPHY_REQ_DPDT_REPORT, //songwenning

    TPHY_REQ_UL_REQ_BUTT,
}TPHY_REQ_UL_ENUM;

typedef enum
{
    TPHY_TRACE_UL_PRACH_SEND_EVT              = OM_TCMD_ID(TPHY_UL_MID, OM_TYPE_TRACE, 0x0),
    TPHY_TRACE_UL_DPCH_CONFIG_EVT,
    TPHY_TRACE_UL_DPCH_SEND_EVT,
    TPHY_TRACE_UL_HO_SYNC_EVT,
    TPHY_TRACE_UL_EPUCH_CONFIG_EVT,
    TPHY_TRACE_UL_EPUCH_SEND_EVT,
    TPHY_TRACE_UL_LOOP_TEST_EVT,
    TPHY_TRACE_UL_DRIVER_EVT,
    TPHY_TRACE_UL_FPACH_RCV_EVT,
    TPHY_TRACE_UL_PRACH_CC_EVT,
    TPHY_TRACE_UL_DPCH_CC_EVT,
    TPHY_TRACE_UL_EPUCH_CC_EVT,
    TPHY_TRACE_UL_UPPCH_BC_EVT,
    TPHY_TRACE_UL_CHAN_BC_EVT,
    TPHY_TRACE_UL_DPCH_TPC_FILL_EVT,
    TPHY_TRACE_UL_SS_ADJUST_EVT,
    TPHY_TRACE_UL_FIR_INT_EVT,
    TPHY_TRACE_UL_CC_BBPREG_HEAD_EVT,        //上报BBP参数
    TPHY_TRACE_UL_CC_BBPREG_TRCH_EVT,
    TPHY_TRACE_UL_CC_BBPREG_TS_EVT,
    TPHY_TRACE_UL_CC_PARA_EVT,          //上报CC编码参数
    TPHY_TRACE_UL_BC_PARA_EVT,           //上报BC调制参数
    TPHY_TRACE_UL_EDCH_BBPREG_EVT,      //上报EDCH信道编码寄存器参数
    TPHY_TRACE_UL_HSPDSCH_CONFIG_EVT,
    TPHY_TRACE_UL_SWITCH_CHANGE_EVT,

    TPHY_TRACE_TAS_RSCP_STATE_EVT,
    TPHY_TRACE_TAS_DPDT_SWITCH_EVT,
    TPHY_TRACE_TAS_STATE_CHANGE_EVT,
    TPHY_TRACE_TAS_GIVE_RSCP_EVT,
    TPHY_TRACE_TAS_GIVE_IDLE_EVT,
    TPHY_TRACE_TAS_GIVE_DCH_EVT,
    TPHY_TRACE_TAS_SEARCH_EVT,
    TPHY_TRACE_DPDT_REPORT_EVT,
	
    TPHY_TRACE_UL_HSSICH_PARA_EVT,
    TPHY_TRACE_MAS_ESTIMATE_HIGH,
    TPHY_TRACE_MAS_ESTIMATE_LOW,
    TPHY_TRACE_MAS_ESTIMATE_END,
    TPHY_TRACE_MAS_GET_NEXT_ANT,
    TPHY_TRACE_MAS_TRACE_REPORT,
    TPHY_TRACE_MAS_ERROR_REPORT,
    TPHY_TRACE_MAS_CONN_UPDATE_ACTIVE,
    TPHY_TRACE_MAS_CONN_UPDATE_PASSIVE,
    TPHY_TRACE_MAS_CONN_PROBE,
    TPHY_TRACE_MAS_SET_CONN_RUNSTATE,
    TPHY_TRACE_MAS_PAGE_CONFICT_CHECK,
    TPHY_TRACE_UL_EVT_BUTT
}TPHY_TRACE_EMU_EVT_ENUM;

typedef enum
{
    TPHY_ERROR_UL_CC_TFOVERFLOW                = OM_TCMD_ID(TPHY_UL_MID, OM_TYPE_ERROR, 0x0),
    TPHY_ERROR_UL_CC_TFCOVERFLOW,
    TPHY_ERROR_UL_CC_ZEROPARA,
    TPHY_ERROR_UL_CC_INVTRCHID,
    TPHY_ERROR_UL_CC_INVSTATUS,
    TPHY_ERROR_UL_BC_PARAERR,
    TPHY_ERROR_UL_ZEROPADDING_LEN_OVERFLOW,
    TPHY_ERROR_UL_DMA_PARAERR,
    TPHY_ERROR_UL_PRIM_PARAERROR,
    TPHY_ERROR_UL_EDCH_CCPARAERR,
    TPHY_ERROR_UL_EUCCH_INVNUM,
    TPHY_ERROR_UL_SICH_INVSTATE,
    TPHY_ERROR_UL_EPUCH_CHNINVALID,
    TPHY_ERROR_UL_EPUCH_CCLOST,
    TPHY_ERROR_UL_CC_DELAY,
    TPHY_ERROR_UL_DPCH_CCLOST,
    TPHY_ERROR_UL_ERR_BUTT
} TPHY_ERROR_UL_ENUM;

typedef enum
{
    TPHY_TRACE_UL_PRACH_CC_OUT_DATA_IND              = OM_TCMD_ID(TPHY_UL_MID, OM_TYPE_IND, 0x0),
    TPHY_TRACE_UL_DPCH_CC_OUT_DATA_IND,
    TPHY_TRACE_UL_EPUCH_CC_OUT_DATA_IND,
    TPHY_TRACE_UL_EUCCH_CC_OUT_DATA_IND,
    TPHY_TRACE_UL_BC_SLOT_DATA_IND,
    TPHY_TRACE_UL_PRACH_SRC_DATA_IND,
    TPHY_TRACE_UL_DPCH_SRC_DATA_IND,
    TPHY_TRACE_UL_EPUCH_SRC_DATA_IND,
    TPHY_TRACE_UL_FIR_DATA_IND,
    TPHY_TRACE_UL_IND_BUTT,
}TPHY_TRACE_EMU_IND_ENUM;

typedef enum
{
    TPHY_UL_OM_SWITCH_OFF = 0,
    TPHY_UL_OM_SWITCH_ON,
}TPHY_UL_OM_SWITCH_ENUM;

//REQ
typedef struct
{
    TPHY_UL_OM_SWITCH_ENUM    enTphyUlReportEn;
    TPHY_UL_OM_SWITCH_ENUM    enTphyUlSgReportEn;
}TPHY_REQ_UL_REPORT_ENA_STRU;

typedef struct
{
    UINT16 usTti;
    UINT16 usTbNum;
    UINT16 usTbSize;
} CC_TFC_STRU;

typedef struct
{
    UINT16 usChnCodeType;
    UINT16 usRmAttr;
    UINT16 usCrcCode;
} CC_SMTFINF_STRU;

typedef struct
{
    UINT16 usTbNum;
    UINT16 usTbSize;
} CC_DATADESC_STRU;

typedef struct
{
    UINT16  usCcTrchNum;
    UINT16  ausCcRuSF1[MAX_TS_CNT];
    UINT16  ausCcRuSF2[MAX_TS_CNT];
    UINT16  usCcTsNum;
    UINT16  ausCcServiceType[MAX_TRCH_CNT];
    UINT16  usCcPuncturingLimit;
    UINT16  ausCcModulateMode[MAX_TS_CNT];
    UINT16  usCcDynamicSF;
    UINT16  usCcInter2Mode;
    UINT16  usCcAllowedTfcNum;
    UINT16  ausCtfciCode[MAX_TS_CNT];
    UINT16  ausCcSsTpcSymbols[MAX_TS_CNT];
    UINT16  ausTfNum[MAX_TRCH_CNT];
    UINT16  usPsOffset;                              //added for double PS
    UINT16  usTbnum1Ind;
    UINT16  *pausCcAllowedTfci;                      //128
    UINT16  *pausCtfc;                               //128
    //UINT16  *pausCcSemistaticTfInfo;                 //18

    CC_TFC_STRU         *pastTfList;            //432
    CC_SMTFINF_STRU     *pastSemStaticTfInfo;   //18
    CC_DATADESC_STRU    astDataDesc[MAX_TRCH_CNT];          //12
} DCH_PRIM_INFO_STRU;

typedef struct
{
    UINT16  usAccChannelCodingType;
    UINT16  usAccCcCdCrcSize;
    UINT16  usAccCcCdTbNum;
    UINT16  usAccCcCdTbSize;
    //UINT16  ausPrimChannelCode[4];
    UINT16  ausSf[4];
    UINT16  ausChannelCode[4];
    UINT16  usAccCcCdTti;
    UINT16  usResv;
} PRACH_PRIM_INFO_STRU;

typedef struct
{
    UINT16  usCcCdChannelCodeType;
    UINT16  ausCcRuSF1[5];
    UINT16  usCcTsNum;
    UINT16  usCcCdCrcSize;
    UINT16  usCcModulateMode;
    UINT16  usCcHsupaRsn;
    UINT16  usCcRvIndex;
    UINT16  usEucchSymbolNum;
    CC_TFC_STRU  stCcTransportFormat;
    UINT16  usReserved;
} EDCH_PRIM_INFO_STRU;

typedef struct
{
    UINT16  *pausBcCcPingBuf;                       //1320
    INT16   sGainFactor;
    UINT16  ausCcRuSF1[MAX_TS_CNT];
    UINT16  ausCcRuSF2[MAX_TS_CNT];
    UINT16  usCcTsNum;
    UINT16  ausCcRuNum[MAX_TS_CNT];
    UINT16  ausCcRuNumPrach[MAX_TS_CNT];
    UINT16  ausEveryTsOffset[MAX_TS_CNT*2];
    UINT16  ausEveryTsOffsetPrach[MAX_TS_CNT*2];
    UINT16  ausFirstTpcOffset[MAX_TS_CNT];
    UINT16  ausSecondTpcOffset[MAX_TS_CNT];
} CC_OUT_INFO_STRU;

typedef struct
{
    UINT16  usTrchId;
    UINT16  ausCcTrchCnt[MAX_TRCH];
    UINT16  ausCcTrchCntPrach[MAX_TRCH];

    UINT16  *pausCcCsData;                          //160  added for cs
    UINT16  *pausCcCsSubA;                          //27
    UINT16  *pausCcCsSubB;                          //27
    UINT16  *pausCcCsSubC;                          //27
    UINT16  *pausCcPsData;                          //528
    UINT16  *pausCcDcchData;                        //12

    UINT16  *pausCcPrachData;

    UINT16  *pausEdchData;                          //698

    DCH_PRIM_INFO_STRU *pstDchPrimInfo;
    PRACH_PRIM_INFO_STRU *pstPrachPrimInfo;
    EDCH_PRIM_INFO_STRU *pstEDchPrimInfo;
    CC_OUT_INFO_STRU *pstCcOutInfo;
} CC_PARA_STRU;

//STATISTICS
typedef struct
{
    UINT32    ulTphyUlInitNum;
    UINT32    ulTphyUlSetupNum;
    UINT32    ulTphyUlRelNum;
    UINT32    ulTphyUlPrachSendReqNum;
    UINT32    ulTphyUlDpchConfigReqNum;
    UINT32    ulTphyUlDpchSendReqNum;
    UINT32    ulTphyUlHspdschConfigReqNum;
    UINT32    ulTphyUlEpuchConfigReqNum;
    UINT32    ulTphyUlEpuchSendReqNum;
    UINT32    ulTphyUlHoSyncReqNum;
    UINT32    ulTphyUlPrachCcTrigNum;
    UINT32    ulTphyUlPrachCcProcNum;
    UINT32    ulTphyUlBcProcNum;
    UINT32    ulTphyUlDriverTrigNum;
    UINT32    ulTphyUlDriverProcNum;
    UINT32    ulTphyUlDpchCcTrigNum;
    UINT32    ulTphyUlDpchCcProcNum;
    UINT32    ulTphyUlEpuchCcTrigNum;
    UINT32    ulTphyUlEpuchCcProcNum;
    UINT32    ulTphyUlSubFrmIntNum;
    UINT32    ulTphyUlFirIntNum;
    UINT32    ulTphyUlFpachRcvNum;
    UINT32    ulTphyUlFpachFailNum;
}TPHY_UL_CHANCTRL_STAT_STRU;

//TRACE
typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
}TPHY_TRACE_UL_COMM_STRU;

typedef struct
{
    UINT16 usSfn;
    UINT16 usSwitch;
}TPHY_TRACE_UL_SWITCH_CHANGE_STRU;

typedef struct
{
    UINT16 usSfn;
    UINT16 usAn;
    UINT16 usCqi;
    UINT16 usTbs;
    UINT16 usRmf;
    UINT16 usRes;
}TPHY_TRACE_UL_HSSICH_PARA_STRU;

typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
    UINT16  usCcTbLen[MAX_TRCH];
    UINT32  usDestDataAddr[MAX_TRCH];
    UINT32  usSrcDataAddr[MAX_TRCH];
}TPHY_TRACE_UL_DPCH_SEND_STRU;

typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
    UINT32  ulDpchBitSpeed;
    UINT32  ulDpchKBitSpeed;
    UINT32  ulEdchBitSpeed;
    UINT32  ulEdchKBitSpeed;
    UINT16  usTxTsId[TDS_UL_MAX_TS_NUM];
    UINT16  usTxTsPwr[TDS_UL_MAX_TS_NUM];
    UINT16  usTxTsFreq[TDS_UL_MAX_TS_NUM];
    UINT16  usTxTsChnNum[TDS_UL_MAX_TS_NUM];
    TDS_DATA_PATH_LOG_IN_STRU astUlTxDriverPara[TDS_UL_MAX_TS_NUM];
}TPHY_TRACE_UL_DRIVER_STRU;
/*BEGIN: by humin, 2015/05/07*/
typedef struct
{
    UINT16 usSignatureRefNum;
    UINT16 usRelativeSubFrmNum;
    UINT16 usUpPchPosition;
    UINT16 usRachTxPowerLevel;
    UINT16 usExUpPchPosition;
    UINT16 usFpachRcvSfn;
}TDS_UL_FPACH_BURST_INFO_STRU;
/*END: by humin, 2015/05/07*/
typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
    TDS_UL_FPACH_BURST_INFO_STRU  stFpachBurstInfo;
}TPHY_TRACE_UL_FPACH_RCV_STRU;

/*typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
    CC_PARA_STRU  stCcPara;
}TPHY_TRACE_UL_CC_STRU;
*/

typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
    PRACH_PRIM_INFO_STRU  stPrachCcPara;
}TPHY_TRACE_UL_PRACH_CC_STRU;

typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
    //DCH_PRIM_INFO_STRU  stDpchCcPara;
}TPHY_TRACE_UL_DPCH_CC_STRU;



typedef struct
{
    UINT16   usEucchTbsizeIndex;
    UINT16   usEucchRsn;
    UINT16   usEucchHarqProcessId;
    UINT16   usEucchNum;
    UINT16   usEucchTsNum;
    UINT16   ausEucchTpc[2];
    UINT16   ausEucchNumTs[5];
    UINT16   *pusEucchResultTs;
}TDS_UL_EUCCH_PARA;

typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
    EDCH_PRIM_INFO_STRU  stEdchCcPara;
    TDS_UL_EUCCH_PARA stEucchPara;
}TPHY_TRACE_UL_EPUCH_CC_STRU;

typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
    UINT16  ausAccSyncUlCode[8];
    UINT32  aulUpPchBcData[128];
}TPHY_TRACE_UL_UPPCH_BC_STRU;

typedef struct
{
    //DPCH or PRACH
    UINT16  usMidId;            //BC input,the Midamble ID
    UINT16  usChannelFlag;      //BC input, the flag of channel type
    UINT16  usTxPower;          //BC input, the send power of the timeslot
    //DPCH 
    UINT16  usModulateMode;     //BC input,modulation mode, 0:QPSK; 1:8PSK; 2:16QAM
    UINT16  usMidambleAllocMode;//BC input,consided the Up Link ,only 2 cases ,defaultMidamble mode:0, SpecificMidamble:2
    UINT16  usMidambleShift;    //BC input,only in SpecificMidamble, use it  
    UINT16  usK;                //BC input,the max user number,the value = 1/2 fact value
    UINT16  usResverd1;
    UINT16  ausChannelCode[2];   //BC input,MaxRuNum=2,first word is first RU's SF and usCode Number ,second word is second RU's SF and usCode Number                  
    UINT16  usCcRuNum;    //BC input,RU's number,don't consided the HsSich
    UINT16  usCcSf1;      //BC input,first RU's SF, !!!!!!注意，usCcSf1和usCcSf2必须前后相邻
    UINT16  usCcSf2;      //BC input,second RU's SF
    UINT16  usGainFactor; //BC input,beta factor
    UINT16  *pusBcCcBuf;   //BC input,the adress of bit data of DPCH or PRACH in this timeslot, Data length [176]
    UINT16  usDpchPower;  //BC input, the power of dpch
    
    //HSDPA HsSich          
    UINT16  usHsSichChannelCode;       //BC input,HsSich RU's SF and usCode Number
    UINT16  usHsSichMidambleAllocMode; //BC input,defaultMidamble mode:0, SpecificMidamble:2
    UINT16  usHsSichMidambleShift;//BC input,only in SpecificMidamble, use it  
    UINT16  usHsSichK;            //BC input,the max user number,the value = 1/2 fact value
    UINT16  usNackAckPoweroffset; //BC input,use to calculate Adjust factor
    UINT16  usNackAckFlag;        //BC input,Nack error flag
    UINT16  usResverd2;
    UINT16  *pusHsSichBuffer;      //BC input,bit data of HsSich, Data length [6] 
    //UINT16  ChannelPowChange;   //BC input, change the channel power
    UINT16  usHsSichPower;        //BC input, the power of Sich
   
    //HSUPA E-PUCH or E-RUCCH                   
    UINT16  usHsupaChannelCode;      //BC input,Epch or Erucch RU's SF and usCode Number         
    UINT16  usHsupaModulateMode;     //BC input,modulation mode, 0:QPSK; 2:16QAM ,ERUCCH is QPSK 
    UINT16  usHsupaMidambleAllocMode;//BC input,defaultMidamble mode:0, SpecificMidamble:2
    UINT16  usHsupaMidambleShift;    //BC input,only in SpecificMidamble, use it  
    UINT16  usHsupaK;                //BC input,the max user number,the value = 1/2 fact value
    UINT16  usEucchNumber;           //Bc input, Eucchnumber=tpcnumber 
    INT16   sHsupaGainFactor;       //BC input, E-PUCH's gainfactor,Erucch no gainfactor  
    UINT16  *pusHsupaBuffer;          //BC input,bit data of Edch or Erucch                  
    UINT16  *pusEucchBuffer;          //BC input,bit data of Eucch  
    UINT16  usHsupaPower;            //BC input, the power of Epuch or Erucch      
           
    //BC out               
    INT16   sPowersetting; //BC output,db format send to DSP1 for every time slot
    INT16  *psTxData;      //BC output,the transfers burst, Data length [1728]       
    UINT16  usSysRfPoint;   //BC input, for 1db power step adjust 
    UINT16  usPowContrFlag; //BC input, for Channel usCode power control index
} T_BC_STRU;

typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
    UINT16  usBcTotalTsNum;
    UINT16  usDmaTsCnt;
    UINT16  ausUlTsInfo[TDS_UL_MAX_TS_NUM];
    T_BC_STRU stBcInputPara;
}TPHY_TRACE_UL_BC_STRU;

typedef struct
{
    UINT16    ausTpcSs16SFSymbol[MAX_TS_CNT];        //Tpc symbol number
    UINT16    ausfirstTPCoffset[MAX_TS_CNT];         //start fill position if even frame
    UINT16    aussecondTPCoffset[MAX_TS_CNT];        //start fill position if odd frame
    UINT16    ausModulateMode[MAX_TS_CNT];           //Modulation mode
} TDS_UL_CC_FILLTPC;

typedef struct 
{         
    UINT16              usRxTsNum;
    UINT16              usPowerSysFrameCnt;           //system frame counter,and use to get relativeframe         
    UINT16              ausDlTpc[4];                  //CalTpc's result
    TDS_UL_CC_FILLTPC   stFillTpcPara;                //Cc parameter, length 9 word
    INT16 *             psBcCcBuf;                      //CC out data, fill Tpc in it. Length 132*3*2 word   
}TDS_UL_FILL_TPC;

typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
    TDS_UL_FILL_TPC stFillDpchTpcPara;
}TPHY_TRACE_UL_DPCH_TPC_FILL_STRU;

typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
    INT16   sLastTxSumSs;
    INT16   sCurrentTxSumSs;
    INT16   sSsAdjust;
    UINT16  usTxAdvPluseCnt;
    UINT16  usTxAdvNegCnt;
    UINT16  usTxDtxPos;
}TPHY_TRACE_UL_SS_ADJUST_STRU;


typedef struct
{
    UINT32  ulBeginSfn;
    UINT32  ulBeginChip;
    UINT32  ulEndSfn;
    UINT32  ulEndChip;
    UINT32  ulTfpTxIntFlag;
    UINT16  usDmaTsCnt;
    UINT16  usBcTotalTsNum;
    UINT16  usUlSyncDmaFlag;
    UINT16  usDmaLen;
    UINT32  ulDmaSourceAddr;
    UINT32  ulDmaDestAddr;
}TPHY_TRACE_UL_FIR_INT_STRU;

//STUB
typedef struct
{
    UINT16 usUpPchSwitch;       /*UpPch发射功率打桩开关*/
    UINT16 usRachSwitch;        /*Rach发射功率打桩开关*/
    UINT16 usDpchSwitch;        /*Dpch发射功率打桩开关*/
    UINT16 usEpuchSwitch;       /*Epuch发射功率打桩开关*/
    UINT16 usSichSwitch;        /*Sich发射功率打桩开关*/
    UINT16 usUpPchPower;        /*UpPch发射功率*/
    UINT16 usRachPower;         /*Rach发射功率*/
    UINT16 usDpchPower;         /*Dpch发射功率*/
    UINT16 usEpuchPower;        /*Epuch发射功率*/
    UINT16 usSichPower;         /*Sich发射功率*/
}TDS_UL_TX_POWER_SET_STRU;

typedef struct
{
    UINT16 usSsFixSwitch;       /*定时调整打桩开关*/
    INT16  sSsValue;            /*定时调整值*/
}TDS_UL_TX_SS_SET_STRU;

typedef struct
{
    UINT16 usUpPchLoopwitch;    /*UpPch循环发送开关*/
    UINT16 usRsv;               
}TDS_UL_TX_PRACH_SET_STRU;

typedef struct
{
    UINT16 usDataSampleSwitch;    /*数据内容上报开关*/
    UINT16 usRsv;               
}TDS_UL_TX_DATA_SAMPLE_SET_STRU;

typedef struct
{
    UINT16 usZeroPaddingBefore;
    UINT16 usZeroPaddingAfter;               
}TDS_UL_TX_ZERO_PADDIND_STRU;

typedef struct
{
    UINT16 usSpeedCapSfnNum;    /* 每次统计的子帧个数(200的倍数,200个子帧为1s) */
    UINT16 usSpeedReportEna;    /* 速率上报使能 */
}TDS_UL_SPEED_REPORT_STRU;


typedef struct
{
    UINT16 usSichStubSwitch;
    UINT16 usTbsizeIndex;
    UINT16 usModType;
    UINT16 usRes;
} TDS_UL_HSSICH_STUB_STRU;

//STAT
//Cc&Bc统计量
typedef struct
{
    UINT32 ulTphyUlCcMainNum;               //调用CcMain入口函数的次数
    UINT32 ulTphyUlCcMainInvStatusNum;      //调用CcMain函数时发生状态错误的次数
    UINT32 ulTphyUlCcMainInvTrchIdNum;      //调用CcMain函数时信道类型错误的次数
    UINT32 ulTphyUlEdchCcMainNum;           //调用EdchCcMain入口函数的次数
    UINT32 ulTphyUlCcSubTaskTrigNum;        //调用CcSubTask函数的次数
    UINT32 ulTphyUlCcSubTaskCallNum;        //调用编码子任务的次数
    UINT32 ulTphyUlCcWaitTaskExcNum;        //编码停等状态子任务实际执行的次数
    UINT32 ulTphyUlCcFinishTaskExcNum;      //编码完成状态子任务实际执行次数 
    UINT32 ulTphyUlCcSwaitIsrNum;           //调用停等中断处理函数的次数
    UINT32 ulTphyUlCcFinishIsrNum;          //调用完成中断处理函数的次数
    UINT32 ulTphyUlEdchFinishIsrNum;        //调用EDCH编码完成中断处理函数的次数
    UINT32 ulTphyUlCcSetRegDataDmaIsrNum;   //调用设置寄存器数据DMA中断处理函数的次数
    UINT32 ulTphyUlCcGetInt1DataDmaIsrNum;  //调用获取1次交织数据DMA中断处理函数的次数
    UINT32 ulTphyUlCcGetMapDataDmaIsrNum;   //调用获取物理信道映射数据DMA中断处理函数的次数
    UINT32 ulTphyUlCcSbNum;                 //调用填充SB函数的次数
    UINT32 ulTphyUlBcMainNum;               //调用BcMain入口函数的次数
} TPHY_UL_CCBC_STAT_STRU;


typedef struct
{
    UINT16 usSubFrameNum;
    UINT16 usChnTypeIdx;
    
    UINT32 ulInt2RegData;
    UINT32 ulSubSegRegData;
}TDS_UL_BBP_REG_HEAD_STRU;

typedef struct
{
    UINT32 ulTrchNum;
    UINT32 ulCrcRegData;
    UINT32 ulEncRegData;
    UINT32 ulInt1RegData;
    UINT32 ulRmCommRegData;
    UINT32 ulCheckBit1RegData;
    UINT32 ulCheckBit2RegData;
}TDS_UL_BBP_REG_TRCH_STRU;

typedef struct
{
    UINT32 ulTsNum;
    UINT32 ulPhCfgRegData;
    UINT32 ulPhBsRegData;
}TDS_UL_BBP_REG_TS_STRU;

typedef struct
{
    UINT16 usChnCodeType;
    UINT16 usRmAttr;
    UINT16 usCrcCode;
} TDS_UL_CCSMTFINF_STRU;

typedef struct
{
    UINT16  usTrchNum;                                      //传输信道数
    UINT16  usTsNum;                                        //时隙数
    UINT16  usCcDynamicSF;
    UINT16  ausServiceType[MAX_TRCH_CNT];                   //01
    UINT16  ausCcModulateMode[MAX_TS_CNT];
    UINT16  ausSsTpcSymbols[MAX_TS_CNT];
    UINT16  ausCcRuSF1[MAX_TS_CNT];
    UINT16  ausCcRuSF2[MAX_TS_CNT];
    UINT16  ausTti[MAX_TRCH_CNT];
    UINT16  ausFi[MAX_TRCH_CNT];
    UINT16  ausTfciLen[MAX_TS_CNT];
    TDS_UL_CCSMTFINF_STRU astSmtfInf[MAX_TRCH_CNT];
    
    UINT16 usSubFrameNum;
    UINT16 usChnTypeIdx;
    UINT16 ausRuNum[MAX_TS_CNT];
    UINT16 usResv;
}TDS_UL_CCPARA_STRU;

typedef struct
{
    //DPCH or PRACH
    UINT16  usMidId;            //BC input,the Midamble ID
    UINT16  usChannelFlag;      //BC input, the flag of channel type
    UINT16  usTxPower;          //BC input, the send power of the timeslot
    //DPCH 
    UINT16  usModulateMode;     //BC input,modulation mode, 0:QPSK; 1:8PSK; 2:16QAM
    UINT16  usMidambleAllocMode;//BC input,consided the Up Link ,only 2 cases ,defaultMidamble mode:0, SpecificMidamble:2
    UINT16  usMidambleShift;    //BC input,only in SpecificMidamble, use it  
    UINT16  usK;                //BC input,the max user number,the value = 1/2 fact value
    UINT16  ausChannelCode[2];   //BC input,MaxRuNum=2,first word is first RU's SF and usCode Number ,second word is second RU's SF and usCode Number                  
    UINT16  usCcRuNum;    //BC input,RU's number,don't consided the HsSich
    UINT16  usCcSf1;      //BC input,first RU's SF
    UINT16  usCcSf2;      //BC input,second RU's SF
    UINT16  usGainFactor; //BC input,beta factor
    
    //HSDPA HsSich          
    UINT16  usHsSichChannelCode;       //BC input,HsSich RU's SF and usCode Number
    UINT16  usHsSichMidambleAllocMode; //BC input,defaultMidamble mode:0, SpecificMidamble:2
    UINT16  usHsSichMidambleShift;//BC input,only in SpecificMidamble, use it  
    UINT16  usHsSichK;            //BC input,the max user number,the value = 1/2 fact value
    UINT16  usNackAckPoweroffset; //BC input,use to calculate Adjust factor
    UINT16  usNackAckFlag;        //BC input,Nack error flag
   
    //HSUPA E-PUCH or E-RUCCH                   
    UINT16  usHsupaChannelCode;      //BC input,Epch or Erucch RU's SF and usCode Number         
    UINT16  usHsupaModulateMode;     //BC input,modulation mode, 0:QPSK; 2:16QAM ,ERUCCH is QPSK 
    UINT16  usHsupaMidambleAllocMode;//BC input,defaultMidamble mode:0, SpecificMidamble:2
    UINT16  usHsupaMidambleShift;    //BC input,only in SpecificMidamble, use it  
    UINT16  usHsupaK;                //BC input,the max user number,the value = 1/2 fact value
    UINT16  usEucchNumber;           //Bc input, Eucchnumber=tpcnumber 
    INT16   sHsupaGainFactor;       //BC input, E-PUCH's gainfactor,Erucch no gainfactor     
           
    //BC out                    
    UINT16  usPowContrFlag; //BC input, for Channel usCode power control index
    UINT16  usSubFrameNum;
}TDS_UL_BCPARA_STRU;
typedef struct
{
    UINT16 usSfn;
    UINT16 usSwitch;
} TDS_UL_SWITCH_CHANGE_STRU;

typedef struct
{
    UINT32 ulTrchNum;
    UINT16 usTfIdx;
    UINT16 usTfNum;
}TDS_UL_TFOVERFLOW_ERR_STRU;

typedef struct
{
    UINT16 usTfcIdx;
    UINT16 usAllowedTfcNum;
}TDS_UL_TFCOVERFLOW_ERR_STRU;

typedef struct
{
    UINT16 usTrchNum;
    UINT16 usTbNum;
    UINT32 ulSumRmN;
}TDS_UL_ZEROPARA_ERR_STRU;

typedef struct
{
    UINT16 usSubFrameNum;
    UINT16 usTrchId;
}TDS_UL_INVTRCHID_ERR_STRU;


typedef struct
{
    UINT16 usSubFrameNum;
    UINT16 usCurState;
    UINT16 usIsRunning;
    UINT16 usEntry;         //0->CcMain, 1->CcSubMain
}TDS_UL_INVSTATUS_ERR_STRU;

typedef struct
{
    UINT16 usSubFrameNum;
    UINT16 usErrType;
    UINT16 usErrPara[4];
    UINT16 usBcExcTrace;
    UINT16 usResv;
}TDS_UL_BCPARA_ERR_STRU;

typedef struct
{
    UINT16 usSfn;
    UINT16 usEucchTsNum;
    UINT16 usEucchNum;
    UINT16 usRes;
} TDS_UL_EUCCH_NUM_ERR_STRU;

typedef struct
{
    UINT16 usSfn;
    UINT16 usScchIdIndex;
    UINT16 usAirSfn;
    UINT16 usCrc;
} TDS_UL_SICH_INVSTATE_ERR_STRU;

typedef struct
{
    UINT16 usSfn;
    UINT16 usTsNum;
    UINT16 usSendSfn;
    UINT16 usChnFlag;
} TDS_UL_EPUCH_CHNINVALID_ERR_STRU;


typedef struct
{
    UINT16 usZeroPaddingBefore;
    UINT16 usZeroPaddingAfter;
    UINT16 usZeroPaddingAll;
    UINT16 usZeroPaddingLim;
}TDS_UL_ZEROPADDING_LEN_OVERFLOW_STRU;

typedef struct
{
    UINT32 ulTfpTxIntFlag;
}TDS_UL_DMA_PARAERR_STRU;

typedef struct
{
    UINT32 ulPara[4];
}TDS_UL_PRIM_PARAERR_STRU;



typedef struct
{
    UINT32 ulTbSize;           //HSUPA传输块大小
    UINT32 ulCrcPara;          //CRC配置
    UINT32 ulEncPara;          //编码参数
    UINT32 ulInt1Para;         //一次交织参数
    UINT32 ulRmNumPara;        //速率匹配数据量
    UINT32 ulSysBitPara;       //系统位校验参数
    UINT32 ulP1BitPara;        //第一校验位参数
    UINT32 ulP2BitPara;        //第二校验位参数
    UINT32 ulNcNrPara;         //速率系统比特所占矩阵行数、列数
    UINT32 ulAddrIniPara;      //速率匹配后校验比特起始地址
    UINT32 ulInt2Para;         //二次交织和星座重排参数
    UINT32 ulCtrlBits;         //HSUPA寄存器控制位
    UINT32 ulIntEnable;        //中断使能寄存器
    UINT32 ulIntFlag;          //中断状态寄存器
} TDS_UL_EDCH_REG_BBP_PARA;;


typedef struct
{
    UINT32 ulErrId;
} TDS_UL_EDCH_PARA_ERR_STRU;


typedef struct
{
    UINT32 ulTdsUlErrBitMap;
    UINT32 ulCcErrBitMap;
    UINT32 ulBcErrBitMap;
    UINT32 ulChCtrlErrBitMap;
    UINT32 ulDriverBitMap;
} TDS_UL_ERROR_STAT_STRU;

typedef struct
{
    UINT16 usSfn;
    UINT16 usResverd;
} TDS_UL_ERROR_EPUCH_CCLOST_STRU;

typedef struct
{
    UINT16 usLastCcSfn;
    UINT16 usCurCcSfn;
} TDS_UL_ERROR_DPCH_CCLOST_STRU;


typedef struct
{
    UINT16 usChnType;
    UINT16 usExpCcTs;
    UINT16 usCurTs;
    UINT16 usRes;
} TDS_UL_CC_DELAY_ERR_STRU;

typedef struct _TPHY_MAS_PAGE_CHECK_OM_STRU{
    UINT16        usRsv;
    UINT16        usProbeState;
    UINT32        ulCurAbsTime;
    UINT32        ulTasStart;
    UINT32        ulTasEnd;
    UINT32        ulSlavePchStart;
    UINT32        ulSlavePchEnd;
    UINT16        usSlaveCheckResult;
}TPHY_MAS_PAGE_CHECK_OM_STRU;

typedef struct _TPHY_MAS_SETCON_OM_STRU{
    UINT16        usRcmState;
    UINT16        usPriState;
    UINT16        usNewRunState;
    UINT16        usRsv;
}TPHY_MAS_SETCON_OM_STRU;

typedef struct _TPHY_MAS_GETANT_OM_STRU_{
    UINT16        usCurAntIdx;
    UINT16        usNextAntIdx;
    UINT16        usSwitchFlg;
    UINT16        usMeasIdx;
    UINT16        usInitAntIdx;
    UINT16        usRound;
}TPHY_MAS_GETANT_OM_STRU;

typedef struct _TPHY_MAS_CONN_PROBE_OM_STRU_{
    UINT16        usAntSwt;
    UINT16        usConflictWithPage;
    UINT16        usInHyst;
    UINT16        usGoodEnough;
    UINT16        usAntComplet;
    UINT16        usMeasSwt;
}TPHY_MAS_CONN_PROBE_OM_STRU;

/*一般OM上报，用于取代printf打印 上报的内容不固定 用于问题定位 可扩展*/
typedef struct _TPHY_MAS_TRACE_OM_STRU_{
    UINT32        ulOmType;
    INT32         slPrint1;
    INT32         slPrint2;
    INT32         slPrint3;
    INT32         slPrint4;
    UINT32        ulPrint5;
    UINT32        ulPrint6;
}TPHY_MAS_TRACE_OM_STRU;

typedef struct _TPHY_MAS_CONN_UPDATE_OM_STRU_{
    UINT16        usRcmState;
    UINT16        usRunState;
    INT32         slCurRsrp;
    INT32         slOutStbRsrpThr;
    INT32         slCurSinr;
    INT32         slOutStbSinrThr;
    UINT32        ulCurPoorCnt;
    UINT32        ulOutStbCntThr;
}TPHY_MAS_CONN_UPDATE_OM_STRU;

typedef struct _TPHY_MAS_COMPARE_OM_STRU_{
    INT32         slRsrpDelta;
    UINT32        ulDeltaHighThr;
    UINT32        ulDeltaLowThr;
    UINT16        usCntHigh;
    UINT16        usCntHighThr;
    UINT16        usCntLow;
    UINT16        usCntLowThr;
    UINT16        usCntTotal;
    UINT16        usCntTotalThr;
    UINT8         ucSwtFlg;
    UINT8         ucCmpEndFlg;
    UINT16        usRsv3;
}TPHY_MAS_COMPARE_OM_STRU;

typedef UINT8 TDS_TAS_NEW_STATE_ENUM_UINT8;


//天线发生切换时上报的OM结构体
typedef struct _TDS_ASU_SWITCH_OM_STRU_{
    //连接态TAS200收到的测量值
    INT32        slGiveConnAnt0;
    INT32        slGiveConnAnt1;

    //idle和dch态收到的侧量 用来判断TAS250状态
    INT32        slGiveConnRsrp;
    INT32        slGiveConnScale;
    INT32        slGiveIdleRsrp;
    INT32        slGiveIdleScale;
}TDS_ASU_SWITCH_OM_STRU;

typedef struct _TDS_ASU_DPDT_SWITCH_STRU_{
    TDS_ASU_SWITCH_OM_STRU      stSwitchOm;
    UINT32                      ulDpdtCurrState;//当前的dpdt状态 1-交叉  0-直通态
    UINT32                      ulBlankType;
    UINT32                      ulRsv;
}TDS_ASU_DPDT_SWITCH_STRU;

//用于OM上报的ASU结构体，意义同TDS_ASU_DATA_STRU
typedef struct _TDS_ASU_OM_REPORT_STRU_{
    UINT32                         ulRsv3;
    UINT8                          ucInitPrachState;   //是否是初始随机接入态
    TDS_TAS_NEW_STATE_ENUM_UINT8   enTasNewState;      //当前TAS要转换的状态
    UINT16                         usCurrNGI_Scale;    //IDLE态SCALE门限 NOT GOOD连续的次数

    UINT16                         usCurrNPI_Scale;    //IDLE态SCALE门限 NOT POOR连续的次数
    UINT16                         usCurrNGI_Rsrp;     //IDLE态RSCP门限 NOT GOOD连续的次数

    UINT16                         usCurrNPI_Rsrp;     //IDLE态RSCP门限 NOT POOR连续的次数
    TDS_TAS_NEW_STATE_ENUM_UINT8   enTasOldState;      //当前TAS转换前的状态
    TDS_TAS_NEW_STATE_ENUM_UINT8   enIdleLastHappyState;

    UINT16                         usPrachFailNum;     //rach接入失败的连续次数
    UINT16                         usCurrNGC;          //scale/rscp 同时not good的连续次数

    UINT16                         usCurrNPC;          //scale/rscp 同时not poor的连续次数
    UINT16                         usRsv2;
    TDS_ASU_SWITCH_OM_STRU         stGiveSubPara;
}TDS_ASU_OM_REPORT_STRU;

//TAS trace上报，可配置上报的频率
typedef struct _TPHY_TAS_RSCP_STATE_STRU_{
	UINT32   					ulTasNewState;
	UINT32   					ulTasOldState;
    UINT32                      ulDpdtCurrState;  //当前的dpdt状态 1-交叉  0-直通
    UINT32                      ulRsv;
}TPHY_TAS_RSCP_STATE_STRU;

typedef struct
{
    UINT16 				  usMsgID;//各个PHY可以不一样
    UINT16 				  usToolsID;
	UINT16                usCurrentBand;
    UINT16                usAuthorize;
	UINT16                usWholeRoundAnt;
    UINT16                usSingleRoundAnt;    
    INT16                 ssCompareAnt0Signal;  /* 比较阶段天线0接收RSCP/RSRP*/
    INT16                 ssCompareAnt1Signal;  /* 比较阶段天线1接收RSCP/RSRP*/
    INT16                 ssCompareAnt2Signal;  /* 比较阶段天线2接收RSCP/RSRP*/
    INT16                 ssCompareAnt3Signal;  /* 比较阶段天线3接收RSCP/RSRP*/	
}TDS_OM_DPDT_STATE_IND_STRU;
//发生状态变化时上报的OM
typedef struct _TDS_ASU_STATE_STRU_{
    UINT32       ulTasNewState;   //转换后的状态
    UINT32       ulTasOldState;   //转换前的状态
    UINT32       ulDpdtCurrState; //当前的dpdt状态 1-交叉  0-直通态
    UINT32       ulRsv0;
    UINT32       ulRsv1;
}TDS_ASU_STATE_STRU;

//连接态上报的主辅天线测量值OM
typedef struct _TDS_ASU_GIVE_RSCP_STRU_{

    //TAS200连接态测量上报给TAS模块用来做天线切换判断
    INT32       slGiveRscpAnt0;
    INT32       slGiveRscpAnt1;

    //当前的dpdt状态 1-交叉  0-直通态
    UINT32      ulDpdtCurrState;
    INT32       slGiveRscpAnt0Filter;
    INT32       slGiveRscpAnt1Filter;

    INT32       slGiveRscpDelta;
    UINT32      ulCnt;
    UINT32      ulRsv;
}TDS_ASU_GIVE_RSCP_STRU;

//连接态上报进入PROTECT状态时的天线状态
typedef struct _TDS_ASU_TAS_HYST_STRU_{
    UINT32      ulDpdtCurrState; //当前的dpdt状态 1-交叉  0-直通态
    UINT32      ulRsv;
}TDS_ASU_TAS_HYST_STRU;


//idle态上报的主天线能量值OM
typedef struct _TDS_ASU_IDLE_STRU_{
    UINT32       ulRsv3;
    UINT8        ucInitPrachState;   //是否是初始随机接入态
    UINT8        ucTasNewState;
    UINT16       usCurrNGI_Rsrp;

    UINT16       usCurrNPI_Rsrp;
    UINT16       usCurrNGI_Scale;

    UINT16       usCurrNPI_Scale;
    TDS_TAS_NEW_STATE_ENUM_UINT8   enTasOldState;      //当前TAS转换前的状态
    UINT8                          ucRsv;
}TDS_ASU_IDLE_STRU;

typedef struct _TDS_ASU_IDLE_RSCP_STRU_{
    INT16             slGiveRscp;
    INT16             slRsv1;
    UINT32            ulGiveScale;


    TDS_ASU_IDLE_STRU stTdsIdleGive;
    UINT16            usDpdtCurrState;
    UINT16            usRsv2;
}TDS_ASU_IDLE_RSCP_STRU;

//连接态上报的主天线测量值OM
typedef struct _TDS_ASU_DCH_RSCP_STRU_{
    UINT32        ulDchNewState;
    UINT32        ulDchOldState;
    UINT16        usCurrNGC;
    UINT16        usCurrNPC;
    INT16         slGiveRscp;
    UINT16        usDpdtCurrState;
    UINT32        ulGiveScale;
    UINT32        ulRsv;
}TDS_ASU_DCH_RSCP_STRU;

//searching过程中上报的实时状态OM
typedef struct _TDS_TAS_SEARCH_STATE_STRU_{
    UINT32      ulMidPwr;              /*中间窗功率*/
    UINT32      ulSfmCnt;              /*连续的子帧数*/
    UINT8       ucRcmRsped;            /*是否收到了RCM回应*/
    UINT8       ucTasDominate;         /*是否有TAS主控权*/

    UINT8       ucSearchDpdtValid;     /*根据门限判决是否需要切天线*/
    UINT8       ucDpdtDone;            /*是否已经切过交叉态*/

    UINT8       ucTasSearch;           /*是否TAS搜*/
    UINT8       ucDpdtOld;             /*旧的dpdt状态*/

    UINT8       ucOmSource;            /*标识该OM是频段搜还是频点搜上报的*/
    UINT8       ucRsv2;                /*保留*/
    INT32       slRsv3;                /*保留*/
}TDS_TAS_SEARCH_STATE_STRU;

//用于TDS TAS的OM开关控制
typedef struct
{
    OM_REQ_ENABLE_ENUM enRptChanEna;
    UINT32             ulRptTasPeriod;
}TPHY_OM_REQ_TASCTRL_STAT_ENA_STRU;
typedef struct
{
    TPHY_OM_REQ_TASCTRL_STAT_ENA_STRU stRptTasEna;
    UINT32                            ulRptTasPeriodCnt;
}TPHY_OM_REQ_TAS_STAT_ENA_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM enRptDpdtEna;
    UINT16             usRev;
}TPHY_OM_REQ_DPDT_STAT_ENA_STRU;
/*TAS OM end*/
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


