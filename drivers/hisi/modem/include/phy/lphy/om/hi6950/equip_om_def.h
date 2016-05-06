/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : equip_om_def.h
  版 本 号   : 初稿
  作    者   : zengshangyou
  生成日期   : 2011年11月18日
  最近修改   :
  功能描述   : 定义装备OM需要上报的结构体
  函数列表   :
  修改历史   :
  1.日    期   : 2011年11月18日
    作    者   : z00189258
    修改内容   : 创建文件

******************************************************************************/

/************************************************************
                     包含其它模块的头文件
************************************************************/
#include "om_base_def.h"
#include "LMspLPhyInterface.h"
/************************************************************
                               宏定义
************************************************************/

/************************************************************
                             数据结构定义
************************************************************/

/************************************************************
                             接口函数声明
 ************************************************************/

#ifndef __EQUIP_OM_DEF_H__
#define __EQUIP_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */



/************************************************************
                    1. REQ命令和对应的数据结构定义
************************************************************/
typedef enum
{
    LPHY_REQ_EQUIP_BT_REQUEST           = OM_CMD_ID(LPHY_BT_MID, OM_TYPE_REQ, 0x1),
}LPHY_EQUIP_REQ_ENUM;


typedef struct
{
    OM_REQ_ENABLE_ENUM usTxCmpOmSwitch;
    OM_REQ_ENABLE_ENUM usRxCmpOmSwitch;
}LPHY_OM_REQ_EQUIP_STRU;

/************************************************************
                    2. CNF数据结构定义
************************************************************/


/************************************************************
                    3. Ind数据结构定义
************************************************************/
typedef enum
{
    LTE_CELL_SEARCH_SUCCESS,
    LTE_CELL_MAIN_CELL_CAMP_SUCCESS,
}NCIT_OM_REPORT_ENMU;
typedef UINT16 LTE_NCIT_OM_REPORT_UNIT16;
typedef enum
{
    LPHY_IND_EQUIP_BT_CMP_TX_REPORT = OM_CMD_ID(LPHY_BT_MID, OM_TYPE_IND, 0x1),
    LPHY_IND_EQUIP_BT_CMP_RX_REPORT,
}LPHY_EQUIP_BT_CMP_IND_ENUM;

typedef enum
{
    LPHY_IND_EQUIP_FREQ_COMP_REPORT = OM_TCMD_ID(TPHY_BT_MID, OM_TYPE_TRACE, 0x1),
    LPHY_IND_EQUIP_TX_COMP_REPORT,
}LPHY_EQUIP_BT_CMP_TRACE_ENUM;
typedef enum
{
	 LPHY_REQ_EQUIP_CT_REQUEST           = OM_CMD_ID(LPHY_CT_MID, OM_TYPE_REQ, 0x1),
}LPHY_EQUIP_CT_REQ_ENUM;
typedef enum
{
    LPHY_TRACE_EQUIP_NCIT_PRITASK_REPORT = OM_CMD_ID(TPHY_NCIT_MID, OM_TYPE_TRACE, 0x1),
    LPHY_TRACE_EQUIP_NCIT_UP_START_REPORT,
    LPHY_TRACE_EQUIP_NCIT_UP_END_REPORT,
    LPHY_TRACE_EQUIP_NCIT_DOWN_START_REPORT,
    LPHY_TRACE_EQUIP_NCIT_DOWN_END_REPORT,
}LPHY_EQUIP_NCIT_CMP_TRACE_ENUM;


typedef struct
{
    UINT16 usCalMaxPwr;      /*根据校准结果计算的最大功率能力*/
    INT16  sPwrCalc;         /*计算功率*/
    UINT16 usPbVal;          /*AMPR和MPR回退值*/
    INT16  sSarMax;          /*降SAR后限定的最大功率*/
    UINT16 usChType;         /*信道类型*/
    INT16  sPowerIn;
    UINT16 usPdmVal;
    INT16  sAptCmp;
    INT16  sPwrAftPd;
    UINT16 usTxFreqCmpNum;   /*查表获得的补偿频点个数*/
    UINT32 ulCentPoint;      /*当前计算的中心频点*/
    INT16  sFreqCmpVal;
    INT16  sTempIndex;
    INT16  sCurMaxPower;
    UINT16 usTempVal;
    UINT16 usPaLevel;        /*PA档位*/
    UINT16 usDbbAttWord;
    UINT16 usAbbAttWord;
    UINT16 usRfCode;         /*RF控制字*/
    INT16  sFilterCmp;
    INT16  sBandWithCmp;
    UINT16 usPdDela;
    UINT16 usRsv2;
}BT_TX_CMP_OM_INFO_STRU;


typedef struct
{
    UINT16 usAgcLevel;
	UINT16 usBandWidth;
    UINT16 usHighFreq;
    UINT16 usLowFreq;
    INT16  usTempCompValResult;
    INT16  usFreqCalNum;
    UINT16 usFreqGetNum;
	UINT16 usGetFreqList[FREQ_MAX_NUM];
	UINT16 usGetFreqCompList[FREQ_MAX_NUM];
    UINT16 usFreq;
    UINT16 sCmpVal;
	UINT16 usFreqCmpValResult;
}BT_RX_CMP_OM_INFO_STRU;

typedef struct
{
    UINT16 usSysFn;
    UINT16 usSubFn;

    UINT32 ulLowFreq;
    UINT32 ulHighFreq;
    UINT32 ulCenterFreq;
    UINT32 ulTemp;
    UINT32 sFilterCmp;
}OM_REPORT_FREQ_COMPENSATION_STRU;
typedef struct
{
    UINT16 usSysFn;
    UINT16 usSubFn;

    INT16  sPowIn;
    UINT16 usPaLevel;
    UINT16 usFreq;
    UINT16 usBandWidth;

    INT16  sFreqComp;
    INT16  sTempComp;
    INT16  sGainstatusIndex;
    INT16  sBBAtt;
    INT16  sDbbAtt;
    UINT16 usRfCode;
    UINT16 usDbbCode;
    UINT16 usRes;
}OM_REPORT_BT_COMPENSATION_STRU;
/*
**NCIT OM 上报TRACE结构体
*/
typedef struct
{
    UINT16 usSysFn;
    UINT16 usSubFn;

    UINT32 ulSubFnCnt;
    UINT32 usSegmentCnt;
}OM_REPORT_NCIT_SEGMENT_CNT_STRU;

/*
**NCIT OM 上报TRACE结构体
*/
typedef struct
{
    UINT16 usSysFn;
    UINT16 usSubFn;

    UINT32 ulFnCnt;
}OM_REPORT_NCIT_FRAME_CNT_STRU;
/************************************************************
                    4. TRACE数据结构定义
************************************************************/

/************************************************************
                    5. ERROR数据结构定义
************************************************************/
typedef struct
{
    OM_REQ_ENABLE_ENUM usCtTxCalOmSwitch;
    OM_REQ_ENABLE_ENUM usCtRxCalSyncOmSwitch;
    OM_REQ_ENABLE_ENUM usCtRxCalOmSwitch;
    OM_REQ_ENABLE_ENUM usCtRxCalSsiReportOmSwitch;
    OM_REQ_ENABLE_ENUM usCtTrigOmSwitch;
    OM_REQ_ENABLE_ENUM usCtApcGainCommReqOmSwitch;
}LPHY_OM_REQ_EQUIP_CT_STRU;
typedef struct LPHY_EQUIP_GET_TX_RF_CODE_REQ
{
    UINT16 usRfCodeNum;
    UINT16 ausRfCode[TX_POW_MAX_NUM]; /*Rf控制字*/
}LPHY_EQUIP_GET_TX_RF_CODE_REQ_STRU;
typedef struct LPHY_EQUIP_DBB_CODE_REQ
{
    UINT16 usDbbCodeNum;     /*DBB控制字数*/
    UINT16 usDbbCode;        /*DBB控制字*/
}LPHY_EQUIP_DBB_CODE_REQ_STRU;
typedef struct LPHY_EQUIP_CT_APC_GAIN_REQ_PARA
{
    UINT16 usWave;                                 /* CW波：0， LTE波：1  */
    UINT16 usSegment;                              /* 发送单一功率时长，单位ms  */
    UINT16 usRsv;
	UINT16 usFreqNum;
    UINT16 ausFreqList[FREQ_MAX_NUM];
    UINT32 ulTxRfCodeNum;                          /*上行RF控制字*/
    UINT16 ausTxRfCode [TX_POW_MAX_NUM];           /*发射功率控制字，包括RF和IF两部分*/
    UINT16 usDbbNum;                               /**/
    UINT16 usDbbCode;                              /*DBB功率控制字*/
    UINT32 ulPaNum;
    UINT8  aucPaLevel[TX_POW_MAX_NUM];
    UINT32 ulPwrNum;
    INT16  sPowerTable[TX_POW_MAX_NUM];            /*功率LIST*/
    UINT32 ulAptEnbFlg;
    UINT32 ulPdEnbFlg;
    UINT16 usVgaCfg;
    UINT16 usDacCfg;
}LPHY_EQUIP_CT_APC_GAIN_REQ_STRU;
typedef struct LPHY_EQUIP_TRIG_INPUT_PARA
{
    UINT16 usSubFramNum;        /*子帧数*/
    UINT16 usSysFramNum;        /*系统帧数*/
    UINT16 usBandIndx;          /*Band索引*/
    UINT16 usAbbChan;           /*ABB通道选择*/
    UINT16 usTxRfCode;          /*Rf控制字*/
    UINT16 usFreqInfo;          /*频率信息*/
    UINT8  ucPaLevel;           /*PA档位信息*/
    UINT8  ucRsv;
    UINT16 usDBBIndex;
}LPHY_EQUIP_TRIG_INPUT_STRU;
typedef struct LPHY_EQUIP_RX_SYNC_INPUT_PARA
{
    UINT16 usSubFramNum;         /*子帧计数*/
    UINT16 usSysFramNum;         /*系统帧数*/
    UINT16 usFreqInfo;           /*频率信息*/
    UINT16 usGainStateIndex;     /*增益档位索引*/
    UINT16 usTxRfCode;           /*Rf控制字*/
    UINT16 usTxDBBCode;          /*DBB控制字*/
    UINT8  ucPaLevel;            /*PA档位信息*/
    UINT8  usResv;
    UINT16 usResv2;      /*统计系统帧号*/
}LPHY_EQUIP_RX_SYNC_INPUT_STRU;

/*发射校准消息上报结构体*/
typedef struct LPHY_EQUIP_TX_CAL_INPUT_PARA
{
    UINT16 usSubFramNum;        /*子帧数*/
    UINT16 usSysFramNum;        /*系统帧数*/
    UINT16 usCtSubFramCnt;
    UINT16 usFreqNum;           /*频点个数*/
    UINT16 usFrequnceCnt;     /*频率索引计数*/
    UINT16 usFreqInfo;          /*频率信息*/
    UINT16 usGainStateNum;      /*校准档位数*/
    UINT16 usGainStateIndex;    /*增益档位索引*/
    UINT16 usTxRfCode;          /*Rf控制字*/
    UINT8  ucPaLevel;           /*PA档位信息*/
    UINT16 usBandIndx;          /*Band索引*/
    UINT16 usAbbChan;           /*ABB通道选择*/
    UINT8  ucResv;
    UINT16 usResv;
}LPHY_EQUIP_TX_CAL_INPUT_STRU;
typedef struct LPHY_EQUIP_RX_CAL_INPUT_PARA
{
    UINT16 usSubFramNum;        /*子帧数*/
    UINT16 usSysFramNum;        /*系统帧数*/
    UINT16 usCtSubFramCnt;
    UINT16 usRxFreqNum;
    UINT16 usRxFreqCnt;
    UINT16 usRxFreqInfo;        /*频率信息*/
    UINT16 usRxGainNum;
    UINT16 usRxGainCnt;       /*增益档位索引*/
    UINT16 usRxRfCode;          /*Rf控制字*/
    UINT16 usRxGain;            /*接收增益*/
    UINT16 usBand;              /*Band信息*/
    UINT16 usResv;
}LPHY_EQUIP_RX_CAL_INPUT_STRU;
typedef struct LPHY_EQUIP_RX_RSSI_PARA
{
    UINT16 usSubFramNum;        /*子帧数*/
    UINT16 usSysFramNum;        /*系统帧数*/
    UINT16 usCtSubFramCnt;
    UINT16 usFreqCnt;           /*频率计数*/
    UINT16 usGainCnt;           /*增益档位计数*/
    UINT16 usRxSsiAnt1PowSum;    /*天线1接收功率统计*/
    UINT16 usRxSsiAnt2PowSum;    /*天线2接收功率统计*/
}LPHY_EQUIP_RX_RSSI_STRU;
typedef enum LTE_EQUIP_CT_OM_RPT_ID
{
    LPHY_EQUIP_CT_TX_CAL_REPORT = OM_LCMD_ID(LPHY_BT_MID, OM_TYPE_IND, 0x100),
    LPHY_EQUIP_CT_RX_CAL_REPORT,
    LPHY_EQUIP_CT_RX_CAL_ANTPOW_REPORT,
    LPHY_EQUIP_CT_RX_SYNC_REPORT ,
    LPHY_EQUIP_RFCODE_REQ_REPORT ,
    LPHY_EQUIP_DBBCODE_REQ_REPORT ,
    LPHY_EQUIP_CT_TRIG_REPORT,
    LPHY_EQUIP_CT_APC_GAIN_COMM_REQ_REPORT,
    LPHY_EQUIP_CT_TX_NV_INFO_REPORT,
	LPHY_EQUIP_CT_RX_NV_INFO_REPORT
}LTE_EQUIP_CT_OM_RPT_ID_ENUM;

typedef struct
{
    INT16 sHigh2MidThre;
	INT16 sMid2HighThre;
	INT16 sMid2LowThre;
	INT16 sLow2MidThre;
}OM_NV_PA_LEVEL_THRE_STRU;
typedef struct
{
    UINT16 usFreqNum;
    UINT16 usRes;
    UINT16 ausTxCalFreqList[RF_TX_FREQ_NUM];           /*TX校准频点，由低到高放置*/
    INT16  asTxCalCompListWired[RF_TX_FREQ_NUM];       /*TX有线频率补偿，实验室填写 默认全0，1/8db*/
    INT16  asTxCalCompListWireless[RF_TX_FREQ_NUM];    /*TX无线频率补偿，实验室填写 默认全0，1/8db*/
}OM_NV_LTE_TX_CAL_LIST_STRU;
typedef struct
{
    UINT16  ausGainNumsNeedCalEachPaLevel[RF_PA_GAIN_NUM];/*每个pa档位需要校准rfgain 的个数*/
    UINT16  sDbbValue;
    UINT16  ausLteApcTable[RF_TX_GAIN_6362_NUM][RF_BBGAIN_NUM_PER_RFGAIN];
}OM_NV_LTE_APC_TABLE_STRU;
typedef struct
{
    INT16  asPaDiff[RF_PA_GAIN_NUM];/*pa中低档位和高档位的功率差，第一个值填0  如 0 -5 -10*/
    UINT16 usRes;
    INT16  asRfDefaultPower[RF_TX_GAIN_6362_NUM][RF_BBGAIN_NUM_PER_RFGAIN];
}OM_NV_LTE_DEFAULT_POW_TABLE_STRU;
typedef struct
{
    UINT16      usFreqNum;
    UINT16      usRes;
    UINT16      usRxCalibrFreqList[RF_RX_FREQ_NUM];            /*Rx频率校准表*/
}OM_NV_LTE_RX_CAL_LIST_STRU;
typedef struct
{
    UINT8     ucAGCAcsMinGainZ;
    UINT8     ucAGCNbMinGainY;
    UINT8     ucReserved;
    UINT8     ucDefaultGain0;
    UINT8     ucDefaultGain1;
    UINT8     ucDefaultGain2;
    UINT16    usReserved;
    UINT32     ulAGCGainTable[AGC_MAX_GAIN_LEVEL];
    UINT32     ulAGCAcsGainTable[AGC_MAX_GAIN_LEVEL];
    UINT32     ulAGCNbGainTable[AGC_MAX_GAIN_LEVEL];
    UINT32     ulRFIdxTable[2][AGC_MAX_GAIN_LEVEL];
    INT16      sRFErrorTable[2][AGC_MAX_GAIN_LEVEL];
}OM_NV_AGC_BAND_GAIN_TABLE_STRU;
typedef struct LPHY_EQUIP_CT_TX_PATH_NV_PARA
{
    UINT16                          usBand;
	OM_NV_PA_LEVEL_THRE_STRU           stPaThre;          /*PA档位门限*/
    OM_NV_LTE_TX_CAL_LIST_STRU         stTxCalFreqListLab;      /*TX校准频点，由低到高放置*/
    OM_NV_LTE_APC_TABLE_STRU           stApcTableLab;           /*k3v5_bzj apc teble pre band*/
    OM_NV_LTE_DEFAULT_POW_TABLE_STRU   stTxDefaultPowLab;       /*k3v5_bzj rf默认发射功率，做校准门限判断使用*/
}LPHY_EQUIP_CT_TX_PATH_NV_INPUT_STRU;
typedef struct LPHY_EQUIP_CT_RX_PATH_NV_PARA
{
    UINT16                          usBand;
    OM_NV_LTE_RX_CAL_LIST_STRU         stRxCalFreqListLab;
    OM_NV_AGC_BAND_GAIN_TABLE_STRU         stRxAgcTableLab;
}LPHY_EQUIP_CT_RX_PATH_NV_INPUT_STRU;
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif 

