/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
  文 件 名   : tds_che_om_def.h
  版 本 号   : 初稿
  作    者   : l00213459
  生成日期   : 2012年11月12日
  最近修改   :
  功能描述   : 信道估计OM上报
  函数列表   :
  修改历史   :
  1.日    期   : 2012年11月12日
     作    者   : l00213459
    修改内容   : 创建文件

******************************************************************************/

#ifndef _TDS_CHE_OM_DEF_H_
#define _TDS_CHE_OM_DEF_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/************************************************************
                     包含其它模块的头文件
************************************************************/
//#include "balong_lte_dsp.h"
#include "om_base_def.h"

/************************************************************
                               宏定义
************************************************************/

typedef struct TPHY_REQ_JD_REPORT_SWITCH
{
	UINT16 usTsBitMap;
	OM_REQ_ENABLE_ENUM_UINT16 enCheCfgRpt;
    OM_REQ_ENABLE_ENUM_UINT16 enRxSignRpt;
    UINT16 enInitCheRpt;
    OM_REQ_ENABLE_ENUM_UINT16 enActWinRpt;
    OM_REQ_ENABLE_ENUM_UINT16 enAlphaRpt;
    UINT16 enLlrRpt;
    OM_REQ_ENABLE_ENUM_UINT16 enCheJdIFRpt;
    OM_REQ_ENABLE_ENUM_UINT16 enJdCdIFRpt;
    OM_REQ_ENABLE_ENUM_UINT16 enJdTimeRpt;
    OM_REQ_ENABLE_ENUM_UINT16 enNoiseRpt;
}TPHY_REQ_JD_REPORT_SWITCH_STRU;

typedef struct TPHY_REQ_CHE_NVPARA_SWITCH
{
    UINT16 usThSaleIc;                    /*噪声限幅门限*/
    UINT16 usNoiseLimit;                  /*噪声最小值*/
    UINT16 usRev0;
    UINT16 usRev1;
}TPHY_REQ_CHE_NVPARA_SWITCH_STRU;


typedef enum __TDS_CHE_CODE_TYPE__
{
	 SCCH = 1,
	 PCCPCH,
	 AGCH,
	 HICH,
	 FPACH,
	 PICH,
	 NSHICH,
	 SCCPCH,
	 DPCH,
	 DSCH
}TDS_CHE_CODE_TYPE_ENUM;

typedef UINT16  TDS_CHE_CODE_TYPE_ENUM_UINT16;
/************************************************************
                             数据结构定义
************************************************************/






/************************************************************
                             函数声明
************************************************************/
typedef enum TDS_JD_OM_RPT_IND
{
    TPHY_REQ_JD_SWITCH                         = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_REQ, 0x0),
    TPHY_REQ_JD_CHE_CFG_IND                    = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_REQ, 0x1),
    TPHY_REQ_JD_RX_SIGN_IND                    = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_REQ, 0x2),
    TPHY_REQ_INIT_CHE_IND                      = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_REQ, 0x3),
    TPHY_REQ_JD_LLR_IND                        = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_REQ, 0x4),
    TPHY_REQ_CHE_JD_INTERFACE_IND              = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_REQ, 0x5),
    TPHY_REQ_JD_CD_INTERFACE_IND               = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_REQ, 0x6),
    TPHY_REQ_CHE_ALPHAFILTER_IND               = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_REQ, 0x7),
    TPHY_REQ_CHE_ACTWIN_IND                    = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_REQ, 0x8),
    TPHY_REQ_CHE_TIME_IND                      = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_REQ, 0x9),
    TPHY_REQ_CHE_PARA                          = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_REQ, 0xa),
    TPHY_REQ_CHE_NOISE_RPT                     = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_REQ, 0xb)
}TPHY_OM_REQ_JD_STRU;

/************************************************************
                     ERROR数据结构定义
************************************************************/
typedef enum
{
    TPHY_ERROR_CHE_MORE_FIR_ERROR              = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_ERROR, 0x1),
    TPHY_ERROR_CHE_NO_CONFIG_ERROR             = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_ERROR, 0x2),
    TPHY_ERROR_CHE_DIV_ZREO                    = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_ERROR, 0x3),
    TPHY_ERROR_CHE_MOD_ZREO                    = OM_TCMD_ID(TPHY_CHE_MID, OM_TYPE_ERROR, 0x4),

}TPHY_CHE_ERROR_ENUM;

typedef struct
{
    UINT16      usSysSfn;        /*系统子帧号*/
    UINT16      usSysTs;         /*系统时隙号*/
    UINT16      usChipNum[4];
}TPHY_OM_TRACE_CHE_TIME_STRU;


typedef struct
{
    UINT16 usSfnId;                            /*子帧号*/
    UINT16 usTsId;                             /*时隙号*/
    UINT16 usMidId;                            /*小区ID*/
    UINT16 usKLocal;                           /*本小区K值*/
    UINT16 usLocCellPos;                       /*窗长*/
    UINT16 usCellNum;                          /*小区数*/
    UINT8 usCodeNum;                           /*分配的码道数*/
    UINT8 usSf;                                /*扩频因子*/
    UINT8 usMidMode;                           /*Midamble分配方式。0:default;1:common;2: Specific;*/
    UINT8 usMidShift;                          /*MIDAMBLE 偏移，仅uMidMode为2时有效*/

    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code0Type;    /*信道类型*/
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code1Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code2Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code3Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code4Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code5Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code6Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code7Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code8Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code9Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code10Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code11Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code12Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code13Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code14Type;
    TDS_CHE_CODE_TYPE_ENUM_UINT16    Code15Type;

    UINT16 ausDmuMode[16];                     /*调制方式*/
} TPHY_OM_REQ_CHE_CFG_PARA_STRU;

typedef struct
{
    INT16  asRxData[864 * 2];
} TPHY_OM_REQ_RX_SIGN_STRU;

typedef struct
{
    INT16  asInitChe[128 * 2];
} TPHY_OM_REQ_INIT_CHE_STRU;

typedef struct
{
    INT8  acSoftData[176];
} TPHY_OM_REQ_JD_SOFT_DATA_STRU;

typedef  struct
{
    UINT32  pulChEst;                   /* 信道估计结果,[128*2*3]128chip*3小区*4byte */
    UINT32  pulRxData;                  /*接收数据信号*/
    UINT32  pulSrMidamble;              /*Midamble干扰重构信号*/
    UINT32  ulNoise;                    /*噪声方差*/
    UINT16  usTotalWin;                 /*激活窗个数，0~16*/
    UINT16  usSF;                       /*扩频因子，1或16*/
	UINT16  usK;                 /*激活码道个数，0~16*/
    UINT16  usTotalVRU;                 /*激活码道个数，0~16*/
    UINT32  ulLocalVRU;                 /*本用户激活码道个数，0~16*/
    UINT16  ausChanID[16];              /*每个码道的码道号，0~15*/
    UINT16  ausModuType[16];            /*每个码道的调制方式，QPSK/16QAM*/
    UINT16  ausWinID[16];               /*每个窗的窗号，0~(3*WinLen-1)*/
    UINT16  ausWinVRU[16];              /*每个窗包含的码道个数，1~16*/
    UINT16  ausVRUScramID[16];          /*每个码道对应的小区ID，0~127*/
} TPHY_OM_REQ_CHE_JD_INTERFACE_STRU;

typedef struct
{
    UINT16     usRxSfn;               /*接收子帧号*/
    UINT16     usRxTsId;              /*接收时隙号*/
	UINT8      ucRuActiveFlag[16];    /*码道激活标志*/
    UINT8      ucCctrchType[16];      /*信道类型*/
    UINT16     usModulationType[16];  /*对应码道调制类型*/
    INT32      psJdCdData[16];        /*JdCdData地址*/
    
    UINT16     usDpchTsNum;           /*一个子帧内Dpch分配的时隙数，范围0~5*/
    UINT16     usDschTsNum;           /*一个子帧内Dsch分配的时隙数，范围0~5*/
    UINT16     usScchNum;             /*一个子帧内需要译码的Scch的个数，范围0~4*/
    UINT16     usAgchNum;             /*一个子帧内需要译码的Agch的个数，范围0~4*/
    UINT16     usScchTsId[4];             /*所在时隙，范围0~6*/
    UINT8      ucScchFirstCode[4];        /*第一个码道位置，范围0~15*/
    UINT8      ucScchSecondCode[4];       /*第二个码道位置，范围0~15*/
    UINT16     usAgchTsId[4];             /*所在时隙，范围0~6*/
    UINT8      ucAgchFirstCode[4];        /*第一个码道位置，范围0~15*/
    UINT8      ucAgchSecondCode[4];       /*第二个码道位置，范围0~15*/
     
} TPHY_OM_REQ_JDCD_INTERFACE_NEW_STRU;

typedef  struct
{
    UINT32 ulPathPwrLast[96];       /*上子帧径功率*/
    INT8   ucCodeType[16];          /*上子帧信道类型*/
    INT8   ucActWinFlag[16];        /*激活窗状态*/
    INT16  sShiftCurrent;           /*当前移位值*/
    INT16  sShiftLast;              /*上子帧移位值*/
	INT16  sAgcGainLast;            /*上子帧Agc增益*/
	INT16  sAgcGainCur;             /*当前子帧Agc增益*/
    INT32  lNoiseLast;              /*上子帧噪声*/
    INT32  lNoiseCurrent;           /*当前子帧噪声*/
    INT16  sFirstTsFlag;            /*第一个时隙标志*/
	INT16  sTimingOffsetFlag;       /*定时调整标志*/
	INT16  sAgcRatio;
	INT16  sReserved[5];
} TDS_OM_CHE_ALPHAFILTER_STRU;


typedef  struct
{
    UINT32 Cell0WinPwr[16];
    INT8   Cell0ActWinFlag[16];
    INT32  Cell0NoisePwr;
    UINT16 Cell0Id;
    UINT16 Cell0MaxPathPos;
    UINT32 Cell0SrPtr;
    UINT32 Cell0CirPtr;

    UINT32 Cell1WinPwr[16];
    INT8   Cell1ActWinFlag[16];
    INT32  Cell1NoisePwr;
    UINT16 Cell1Id;
    UINT16 Cell1MaxPathPos;
    UINT32 Cell1SrPtr;
    UINT32 Cell1CirPtr;

    UINT32 Cell2WinPwr[16];
    INT8   Cell2ActWinFlag[16];
    INT32  Cell2NoisePwr;
    UINT16 Cell2Id;
    UINT16 Cell2MaxPathPos;
    UINT32 Cell2SrPtr;
    UINT32 Cell2CirPtr;
} TDS_CHE_COMMON_DATA_STRU;

typedef  struct
{
    INT32 lNoise1;
    INT32 lNoise2;
	INT32 lNoiseThFlag;
	INT32 lRev;
} TDS_CHE_NOISE_RPT_STRU;


extern TPHY_REQ_JD_REPORT_SWITCH_STRU gstJdReportSwitch;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __TDS_CHE_OM_DEF_H__ */

