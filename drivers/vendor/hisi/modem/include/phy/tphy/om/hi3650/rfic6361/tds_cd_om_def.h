/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
  文 件 名   : Tds_Cd_Om_def.h
  版 本 号   : 初稿
  作    者   : m00211054
  生成日期   : 2012年07月06日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
-------------------------------------------------------------------------------
  1.日    期 :
    作    者 :
    修改内容 : created
******************************************************************************/
#ifndef __TDS_CD_OM_DEF_H__
#define __TDS_CD_OM_DEF_H__

#ifdef __cplusplus
#if __cplusplus
        extern "C"{
#endif
#endif /* __cplusplus */
#include "balong_lte_dsp.h"


/************************************************************
                           1. REQ命令和对应的数据结构定义
************************************************************/
//#define TPHY_REQ_CD_OM_REP_SWITCH    OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_REQ, 0x0)
typedef enum
{
    TPHY_REQ_CD_OM_REP_DPCH             = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_REQ, 0x0),
    TPHY_REQ_CD_OM_REP_DEC              = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_REQ, 0x1),
    TPHY_REQ_CD_OM_REP_PCCPCH           = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_REQ, 0x2),
    TPHY_REQ_CD_OM_REP_FPACH            = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_REQ, 0x3),
    TPHY_REQ_CD_OM_REP_SCCPCH           = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_REQ, 0x4),
    TPHY_REQ_CD_OM_REP_DSCH             = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_REQ, 0x5),

}TPHY_CD_OM_REQ_ENUM;


/************************************************************
                             枚举定义
************************************************************/

typedef enum TDS_CD_OM_RPT_DSCH_IND
{
    TPHY_IND_CD_SOFTBIT_INPUT_DSCH      = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x00),
    TPHY_IND_CD_HARQ_PARA_INPUT_DSCH    = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x01),
    TPHY_IND_CD_TURBO_PARA_INPUT_DSCH   = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x02),
    TPHY_IND_CD_TURBO_BIT_OUTPUT_DSCH   = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x03),
    TPHY_IND_CD_TURBO_CRC_DSCH          = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x04),
    TPHY_IND_CD_PARA_DSCH               = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x05),

}TDS_CD_OM_RPT_DSCH_IND_ENUM;

typedef enum TDS_CD_OM_RPT_DPCH_IND
{
    TPHY_IND_CD_SOFTBIT_INPUT_DPCH      = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x10),
    TPHY_IND_CD_HARQ_DATA_INPUT_DPCH    = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x11),
    TPHY_IND_CD_HARQ_PARA_INPUT_DPCH    = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x12),
    TPHY_IND_CD_HARQ_DATA_OUTPUT_DPCH   = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x13),
    TPHY_IND_CD_TFCI_DATA_DPCH          = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x14),
    TPHY_IND_CD_TFCI_DPCH               = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x15),
    TPHY_IND_CD_SB_FLAG_DPCH            = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x16),
    TPHY_IND_CD_CDTABLE                 = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x17),

}TDS_CD_OM_RPT_DPCH_IND_ENUM;

typedef enum TDS_CD_OM_RPT_DEC_IND
{
    TPHY_IND_CD_VIT_PARA_INPUT      = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x20),
    TPHY_IND_CD_VIT_DATA_INPUT      = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x21),
    TPHY_IND_CD_VIT_DATA_OUTPUT     = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x22),
    TPHY_IND_CD_VIT_CRC             = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x23),

    TPHY_IND_CD_TURBO_PARA_INPUT    = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x24),
    TPHY_IND_CD_TURBO_DATA_INPUT    = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x25),
    TPHY_IND_CD_TURBO_DATA_OUTPUT   = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x26),
    TPHY_IND_CD_TURBO_CRC           = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x27),
}TDS_CD_OM_RPT_DEC_IND_ENUM;

typedef enum TDS_CD_OM_RPT_PCCPCH_IND
{
    TPHY_IND_CD_SOFTBIT_INPUT_PCCPCH      = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x30),

}TDS_CD_OM_RPT_PCCPCH_IND_ENUM;

typedef enum TDS_CD_OM_RPT_FPACH_IND
{
    TPHY_IND_CD_SOFTBIT_INPUT_FPACH      = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x40),

}TDS_CD_OM_RPT_FPACH_IND_ENUM;

typedef enum TDS_CD_OM_RPT_SCCPCH_IND
{
    TPHY_IND_CD_SOFTBIT_INPUT_SCCPCH      = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x50),

}TDS_CD_OM_RPT_SCCPCH_IND_ENUM;

typedef enum TDS_CD_OM_RPT_BLER_IND
{
    TPHY_IND_CD_DPA_BLER                  = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x90),
    TPHY_IND_VOICE_TX                     = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x91),
    TPHY_IND_VOICE_RX                     = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x92),
	TPHY_IND_VOICE_WARNING                = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x93),
}TDS_CD_OM_RPT_BLER_IND_ENUM;

typedef enum TDS_CD_OM_RPT_DSCH_PDU_BLER_IND
{
    TPHY_IND_CD_DSCH_PDU_BLER      = OM_TCMD_ID(TPHY_CD_MID, OM_TYPE_IND, 0x95),
}TDS_CD_OM_RPT_DSCH_PDU_BLER_ENUM;
/************************************************************
                             结构体
************************************************************/

typedef struct TDS_CD_OM_RPT_CTRL
{
    TDS_SWITCH_FALG_ENUM_UINT16  usCdSoftBitInRptEnb;
    TDS_SWITCH_FALG_ENUM_UINT16  usCdSoftBitBbpRptEnb;
}TDS_CD_OM_REQ_CTRL_STRU;

typedef struct TDS_CD_OM_BLER_CTRL
{
    TDS_SWITCH_FALG_ENUM_UINT16  usCdDschBlerRptEnb;
    //TDS_SWITCH_FALG_ENUM_UINT16  usCdHarqParaInputDschRptEnb;
    //TDS_SWITCH_FALG_ENUM_UINT16  usCdTurboParaInputDschRptEnb;
    //TDS_SWITCH_FALG_ENUM_UINT16  usCdTurboBitOutputDschRptEnb;
    //TDS_SWITCH_FALG_ENUM_UINT16  usCdTurboCrcDschRptEnb;
    TDS_SWITCH_FALG_ENUM_UINT16  usTpyVoiceRptEnb;
}TDS_CD_OM_BLER_CTRL_STRU;


typedef struct TDS_CD_OM_DSCH_IND_RPT_CTRL
{
    TDS_SWITCH_FALG_ENUM_UINT16  usCdSoftBitInputDschRptEnb;
    TDS_SWITCH_FALG_ENUM_UINT16  usCdHarqParaInputDschRptEnb;
    TDS_SWITCH_FALG_ENUM_UINT16  usCdTurboParaInputDschRptEnb;
    TDS_SWITCH_FALG_ENUM_UINT16  usCdTurboBitOutputDschRptEnb;
    TDS_SWITCH_FALG_ENUM_UINT16  usCdTurboCrcDschRptEnb;
    TDS_SWITCH_FALG_ENUM_UINT16  usCdDschParaRptEnb;
}TDS_CD_OM_DSCH_IND_CTRL_STRU;

typedef struct TDS_CD_OM_DPCH_IND_RPT_CTRL
{
    TDS_SWITCH_FALG_ENUM_UINT16  usCdSoftBitInputDpchRptEnb;
    TDS_SWITCH_FALG_ENUM_UINT16  usCdHarqDataInputDpchRptEnb;
    TDS_SWITCH_FALG_ENUM_UINT16  usCdHarqParaInputDpchRptEnb;
    TDS_SWITCH_FALG_ENUM_UINT16  usCdHarqDataOutputDpchRptEnb;
    TDS_SWITCH_FALG_ENUM_UINT16  usCdTfciDataDpchRptEnb;
    TDS_SWITCH_FALG_ENUM_UINT16  usCdTfciDpchRptEnb;
    TDS_SWITCH_FALG_ENUM_UINT16  usCdSbFlagDpchRptEnb;
    TDS_SWITCH_FALG_ENUM_UINT16  usCdDpchCdTableRptEnb;

}TDS_CD_OM_DPCH_IND_CTRL_STRU;

typedef struct TDS_CD_OM_DEC_IND_RPT_CTRL
{
    TDS_SWITCH_FALG_ENUM_UINT16  usCdVitParaInputRptEnb;
    TDS_SWITCH_FALG_ENUM_UINT16  usCdVitDataInputRptEnb;
    TDS_SWITCH_FALG_ENUM_UINT16  usCdVitDataOutputRptEnb;
    TDS_SWITCH_FALG_ENUM_UINT16  usCdVitCrcRptEnb;

    TDS_SWITCH_FALG_ENUM_UINT16  usCdTurboParaInputRptEnb;
    TDS_SWITCH_FALG_ENUM_UINT16  usCdTurboDataInputRptEnb;
    TDS_SWITCH_FALG_ENUM_UINT16  usCdTurboDataOutputRptEnb;
    TDS_SWITCH_FALG_ENUM_UINT16  usCdTurboCrcRptEnb;
}TDS_CD_OM_DEC_IND_CTRL_STRU;

typedef struct TDS_CD_OM_PCCPCH_IND_RPT_CTRL
{
    TDS_SWITCH_FALG_ENUM_UINT16  usCdSoftBitInputPccpchRptEnb;
    TDS_SWITCH_FALG_ENUM_UINT16  usreserved;
}TDS_CD_OM_PCCPCH_IND_CTRL_STRU;

typedef struct TDS_CD_OM_FPACH_IND_RPT_CTRL
{
    TDS_SWITCH_FALG_ENUM_UINT16  usCdSoftBitInputFpachRptEnb;
    TDS_SWITCH_FALG_ENUM_UINT16  usreserved;
}TDS_CD_OM_FPACH_IND_CTRL_STRU;

typedef struct TDS_CD_OM_SCCPCH_IND_RPT_CTRL
{
    TDS_SWITCH_FALG_ENUM_UINT16  usCdSoftBitInputSccpchRptEnb;
    TDS_SWITCH_FALG_ENUM_UINT16  usreserved;
}TDS_CD_OM_SCCPCH_IND_CTRL_STRU;

typedef enum __OM_VOICETPYE__
{
    AMR_TYPE_4_75K                  =0,
    AMR_TYPE_5_15K                  =1,
    AMR_TYPE_5_9K                   =2,
    AMR_TYPE_6_7K                   =3,
    AMR_TYPE_7_4K                   =4,
    AMR_TYPE_7_95K                  =5,
    AMR_TYPE_10_2K                  =6,
    AMR_TYPE_12_2K                  =7,
    AMR_TYPE_SID										=8,
    AMR_TYPE_NO_DATA								=15,
}OM_VOICETPYE_ENUM;
typedef UINT16 OM_VOICETPYE_ENUM_UINT16;
typedef enum __OM_VOICETPYE_OK__
{
    VOICE_BAD                       =0,
    VOICE_GOOD                      =1,
}OM_VOICEQUATPYE_ENUM;
typedef UINT16 OM_VOICEQUATPYE_ENUM_UINT16;
typedef enum __OM_VOICETPYE_FLAG__
{
    VOICE_SUCCESS                      =0,
    VOICE_FAIL                         =1,
}OM_VOICEFLAGTPYE_ENUM;
typedef UINT16 OM_VOICEFLAGTPYE_ENUM_UINT16;
typedef enum __OM_VOICE_WARNING_TPYE_FLAG__
{
    VOICE_SIR_NOT_GOOD                      =0,
    VOICE_UL_LOST                           =1,
}OM_VOICE_WARNING_TPYE_FLAG_ENUM;
typedef UINT16 OM_VOICE_WARNING_TPYE_FLAG_ENUM_UINT16;
typedef struct
{
    UINT16 usSfn;
    OM_VOICETPYE_ENUM_UINT16 usAmrType;
    OM_VOICEQUATPYE_ENUM_UINT16 usQua;
    OM_VOICEFLAGTPYE_ENUM_UINT16 usFlag;
}TDS_VOICE_RPT_STRU;
typedef struct
{
    OM_VOICE_WARNING_TPYE_FLAG_ENUM_UINT16 usWarningType;
    UINT16 usRscp;
    UINT16 usBler;
    UINT16 usScale;
    UINT16 usUlFrameLostNum;
    UINT16 usrsd1;
}TDS_VOICE_WARNING_RPT_STRU;

typedef struct
{
    INT8  acCdSoftBit[16000];
} TPHY_CD_OM_SOFTBIT_STRU;

typedef struct
{
    INT8  cCdSoftBit;
} TPHY_CD_OM_ONE_SOFTBIT_STRU;

typedef struct
{
    UINT32  alCdWords[5000];
} TPHY_CD_OM_WORD_STRU;

typedef struct
{
    UINT32  alCdWord;
} TPHY_CD_OM_ONE_WORD_STRU;

typedef struct
{
    UINT16                 usNewTrans;
    UINT16                 usReTransNum;
    UINT16                 usTotalNdi;
    UINT16                 usNewTransCrcWrong;
    UINT16                 usReTransCrcWrong;
    UINT16                 usNewTransBler;
    UINT16                 usReTransBler;
    UINT16                 ausResv[3];
}TDS_CD_OM_DSCH_PDU_BLER_STRU;
typedef struct __BLER
{
    UINT16 usCdDschBler;
    UINT16 usCdDpchBler;
    UINT16 usCdDschDecAllCnt;
    UINT16 usCdDschRate;
    UINT16 usCdDschErrCnt;
    UINT16 usCdDpchErrCnt;
    UINT16 usCdDpchDecAllCnt;
    UINT16 usCdvoiceTcnt;
    UINT16 usCdVoiceTErrCnt;
    UINT16 usCdreserved;
    UINT32 ulCdVoiceAllCnt;
    UINT32 ulCdVoiceErrCnt;
} TPHY_CD_OM_BLER_STRU;
typedef struct __CDTABLE
{
    UINT16 usCdServiceType;
    UINT16 usCDTTI;
    UINT16 usTbNum;
    UINT16 usTbSize;
    UINT16 usCdcrcSize;
    UINT16 usCdCrcAftL;
    UINT16 usCdConcatenateAftL;
    UINT16 usCdSegBlockNum;
    UINT16 usCdSegBlockLen;
    UINT16 usCdChannelCodeType;
    UINT16 usCdChannelCodeAftL;
    UINT16 usCdInter1AftL;
    UINT16 usCdFi;
    UINT16 usCdOffsetAddr;
    UINT16 usCdBlockSize;
    UINT16 usCdRMInd;
    UINT16 usCdRMBefL;
    UINT16 usCDRMAftL;
    UINT16 ausCdeini[16];
    UINT16 usCdTbNumOld;
    UINT16 usTrchFrameCnt;
    UINT16 usHarqOutFlg[8];
    UINT32 ulCdDetaNLen;
} TPHY_CD_OM_CDTABLE_STRU;
typedef struct __DSCH_PARA
{
		UINT16 usHspdschSfn;
		UINT16 usHspdschModulation;
	  UINT16 usHspdschRV;
	  UINT16 usHspdschTbsize;
	  UINT16 usHarqProcess;
	  UINT16 usHspdschTs;
	  UINT16 usHspdschTslen;
	  UINT16 usHspdschEcode;
	  UINT16 usHspdschScode;
	  UINT16 usHspdschRuSF;
	  UINT16 usHspdschNewIndicate;
	  UINT16 usNowHpow;
	  UINT16 usCombinationType;
	  UINT16 rsd;
} TPHY_CD_OM_DSCH_PARA_STRU;

typedef struct
{
    TPHY_CD_OM_CDTABLE_STRU stcdtable[6];
} TPHY_CD_OM_CDTABLE_ALL_STRU;

extern TDS_VOICE_RPT_STRU         gstVoiceRpt;


extern void TDS_CD_TphyVoiceOmRpt(UINT16 usIsTx,TDS_VOICE_RPT_STRU strptstru);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

/******************************** end *************************************/

