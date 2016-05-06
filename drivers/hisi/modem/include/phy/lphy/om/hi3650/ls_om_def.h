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
#ifndef __LS_OM_DEF_H__
#define __LS_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */

/************************************************************
                     包含其它模块的头文件
************************************************************/
#include "lte_nv_para_define.h"             /**/
/************************************************************
                               宏定义
************************************************************/
//#define LS_LPHY_FEATURE_MAX_CARRIER_NUM 2
#define NUM_OF_MRS_RB	6
#define NUM_OF_MRS_SYMB  3

#define LS_MAX_SUPPORTED_NEIGHBORCELL     8
#ifndef LPHY_MAX_RX_ANTENNA_NUM
#define LPHY_MAX_RX_ANTENNA_NUM   2
#endif

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
	LPHY_REQ_LS_SAMPLING_REPORT_ENA         = OM_CMD_ID(LPHY_LS_MID, OM_TYPE_REQ, 0x0),
	LPHY_REQ_LS_TRU_FIXED_NOISE_STUB,			/*固定TRU噪声打桩*/	
	LPHY_REQ_MLS_SAMPLEING_REPORT_ENA,    //MRS LS result report ID
}LPHY_REQ_MSGID_LS_ENUM;

typedef enum
{
    LS_OM_SWITCH_OFF = 0,
    LS_OM_SWITCH_ON,
}LS_OM_SWITCH_ENUM;
typedef UINT16 LS_OM_SWITCH_ENUM_UINT16;

typedef enum
{
    MLS_OM_SWITCH_OFF = 0,
    MLS_OM_SWITCH_ON,
}MLS_OM_SWITCH_ENUM;
typedef UINT16 MLS_OM_SWITCH_ENUM_UINT16;

typedef struct
{
   OM_REQ_ENABLE_ENUM_UINT16    enLsSamplingReportEn;
   UINT16     usCarrierIndex;
   UINT16     usTXAntIndex;
   UINT16     usReserved;
   
}LPHY_REQ_LS_SAMPLEING_REPORT_ENA_STRU;

typedef struct
{
   MLS_OM_SWITCH_ENUM_UINT16    enMLsSamplingReportEn; 
   UINT16     usRxAntIndex;
}LPHY_REQ_MLS_SAMPLEING_REPORT_ENA_STRU;

typedef struct __LPHY_REQ_TIMING_FIXED_NOISE_STRU__
{
    OM_REQ_ENABLE_ENUM           enEna;          /*0,不使能定时模块; 1,使能定时*/
	UINT32   ulTruNoiseValue;
}LPHY_REQ_LS_TRU_FIXED_NOISE_STRU;


/************************************************************
                           3. Sg数据结构定义
************************************************************/


/************************************************************
                           4. TRACE数据结构定义
************************************************************/
typedef enum
{
    LPHY_TRACE_LS_SAMPLING_REPORT_ENA         = OM_CMD_ID(LPHY_LS_MID, OM_TYPE_TRACE, 0x1),
	LPHY_TRACE_MLS_SAMPLING_REPORT_ENA,   // report ID for MRS LS
}LPHY_TRACE_LS_ENUM;
typedef struct
{
	UINT32	 ulDagcGain;
	UINT32   ulLen_AagcGain;
	UINT32	 ulIndex;
	UINT32	 ulDoneFlag;
}LS_FRAME_HEADER_STRU;

typedef struct
{
    INT16 	asLsIn[NUM_OF_RB_20M*NUM_OF_CRS_RB][NUM_OF_IQPATH];//W100*2=200
	//UINT32   aulPad[2];
	LS_FRAME_HEADER_STRU  stLsHeader;	
}LS_FRAME_20M_STRU;
typedef struct
{
    INT16 	asLsIn[NUM_OF_RB_15M*NUM_OF_CRS_RB][NUM_OF_IQPATH];//W75*2=150
	UINT32   aulPad[2];
	LS_FRAME_HEADER_STRU  stLsHeader;	
}LS_FRAME_15M_STRU;

typedef struct
{
    INT16 	asLsIn[NUM_OF_RB_10M*NUM_OF_CRS_RB][NUM_OF_IQPATH];//W50*2=100
	//UINT32   aulPad[2];
	LS_FRAME_HEADER_STRU  stLsHeader;	
}LS_FRAME_10M_STRU;

typedef struct
{
    INT16 	asLsIn[NUM_OF_RB_5M*NUM_OF_CRS_RB][NUM_OF_IQPATH];//W25*2=50
	UINT32   aulPad[2];
	LS_FRAME_HEADER_STRU  stLsHeader;	
}LS_FRAME_5M_STRU;

typedef struct
{
    INT16 	asLsIn[NUM_OF_RB_3M*NUM_OF_CRS_RB][NUM_OF_IQPATH];//W15*2=30
	UINT32   aulPad[2];
	LS_FRAME_HEADER_STRU  stLsHeader;	
}LS_FRAME_3M_STRU;

typedef struct
{
    INT16 	asLsIn[NUM_OF_RB_1P4M*NUM_OF_CRS_RB][NUM_OF_IQPATH];//W6*2=12
	//UINT32   aulPad[2];
	LS_FRAME_HEADER_STRU  stLsHeader;	
}LS_FRAME_1P4M_STRU;
#if 0
typedef union
{
	LS_FRAME_20M_STRU	astLsFrame20M[LPHY_FEATURE_MAX_CARRIER_NUM][NUM_OF_RS_SYMB][NUM_OF_TX_ANT][NUM_OF_RX_ANT];
	LS_FRAME_15M_STRU	astLsFrame15M[LPHY_FEATURE_MAX_CARRIER_NUM][NUM_OF_RS_SYMB][NUM_OF_TX_ANT][NUM_OF_RX_ANT];
	LS_FRAME_10M_STRU	astLsFrame10M[LPHY_FEATURE_MAX_CARRIER_NUM][NUM_OF_RS_SYMB][NUM_OF_TX_ANT][NUM_OF_RX_ANT];
	LS_FRAME_5M_STRU	astLsFrame5M[LPHY_FEATURE_MAX_CARRIER_NUM][NUM_OF_RS_SYMB][NUM_OF_TX_ANT][NUM_OF_RX_ANT];
	LS_FRAME_3M_STRU	astLsFrame3M[LPHY_FEATURE_MAX_CARRIER_NUM][NUM_OF_RS_SYMB][NUM_OF_TX_ANT][NUM_OF_RX_ANT];
	LS_FRAME_1P4M_STRU	astLsFrame1P4M[LPHY_FEATURE_MAX_CARRIER_NUM][NUM_OF_RS_SYMB][NUM_OF_TX_ANT][NUM_OF_RX_ANT];
}LS_FRAME_UNION;
#else
typedef union
{
	LS_FRAME_20M_STRU	astLsFrame20M[NUM_OF_RX_ANT];
	LS_FRAME_15M_STRU	astLsFrame15M[NUM_OF_RX_ANT];
	LS_FRAME_10M_STRU	astLsFrame10M[NUM_OF_RX_ANT];
	LS_FRAME_5M_STRU	astLsFrame5M[NUM_OF_RX_ANT];
	LS_FRAME_3M_STRU	astLsFrame3M[NUM_OF_RX_ANT];
	LS_FRAME_1P4M_STRU	astLsFrame1P4M[NUM_OF_RX_ANT];
}LS_FRAME_UNION;
#endif

typedef struct
{

/*定义一个符号内MRS的长度，包括IQ两路*/
    INT16 	asMLsIn[NUM_OF_RB_20M*NUM_OF_MRS_RB][NUM_OF_IQPATH];
	//UINT32   aulPad[2];
	LS_FRAME_HEADER_STRU stMLsHeader;
}MLS_FRAME_20M_STRU;

typedef struct
{
    INT16 	asMLsIn[NUM_OF_RB_15M*NUM_OF_MRS_RB][NUM_OF_IQPATH];	
	INT32	MLSPad[2];
	LS_FRAME_HEADER_STRU stMLsHeader;
}MLS_FRAME_15M_STRU;

typedef struct
{
    INT16 	asMLsIn[NUM_OF_RB_10M*NUM_OF_MRS_RB][NUM_OF_IQPATH];
	//UINT32   aulPad[2];
	LS_FRAME_HEADER_STRU stMLsHeader;
}MLS_FRAME_10M_STRU;

typedef struct
{
    INT16 	asMLsIn[NUM_OF_RB_5M*NUM_OF_MRS_RB][NUM_OF_IQPATH];	
	INT32	MLSPad[2];
	LS_FRAME_HEADER_STRU stMLsHeader;
}MLS_FRAME_5M_STRU;

typedef struct
{
    INT16 	asMLsIn[NUM_OF_RB_3M*NUM_OF_MRS_RB][NUM_OF_IQPATH];
	INT32	MLSPad[2];
	LS_FRAME_HEADER_STRU stMLsHeader;
}MLS_FRAME_3M_STRU;

typedef struct
{
    INT16 	asMLsIn[NUM_OF_RB_1P4M*NUM_OF_MRS_RB][NUM_OF_IQPATH];
	//UINT32   aulPad[2];
	LS_FRAME_HEADER_STRU stMLsHeader;
}MLS_FRAME_1P4M_STRU;

typedef union
{
	MLS_FRAME_20M_STRU	astMLsFrame20M;
	MLS_FRAME_15M_STRU	astMLsFrame15M;
	MLS_FRAME_10M_STRU	astMLsFrame10M;
	MLS_FRAME_5M_STRU	astMLsFrame5M;
	MLS_FRAME_3M_STRU	astMLsFrame3M;
	MLS_FRAME_1P4M_STRU	astMLsFrame1P4M;
}MLS_FRAME_UNION;


typedef struct
{
    UINT16    usSysFrameNum;
    UINT16    usSubFrameNum;
	
    UINT16    usSymbNum;
	UINT16    usCarrierIndex;

	UINT16    usTxAntIndex;
	UINT16    enBandwidth;
	
       //LS_FRAME_UNION   unCurSymboldata;	
	LS_FRAME_20M_STRU	stCurSymboldata[NUM_OF_RX_ANT];
    //LS_FRAME_UNION   unLastSymboldata;	
    
	//LS_FRAME_1P4M_STRU	stLastSymboldata[NUM_OF_RX_ANT];
}LPHY_TRACE_LS_SAMPLING_REPORT_STRU;

typedef struct
{
    UINT16    usSysFrameNum;
    UINT16    usSubFrameNum;
	
    UINT16    usSymbNum;

	UINT16    usRxAntIndex;
	UINT16    enBandwidth;
	UINT16    usReserved;
		
	MLS_FRAME_20M_STRU	stCurSymboldata;

}LPHY_TRACE_MLS_SAMPLING_REPORT_STRU;


/************************************************************
                           5. ERROR数据结构定义
************************************************************/
#if 0
typedef enum
{
    LPHY_ERROR_AFC_ARRAY_INDEX         = OM_CMD_ID(LPHY_AFC_MID, OM_TYPE_ERROR, 0x1),
    LPHY_ERROR_AFC_CASE,
    LPHY_ERROR_AFC_ZERO_DIV,
    LPHY_WARNING_AFC_RTT_SWITCH_OFF,
}LPHY_ERROR_AFC_ENUM;

/************************************************************
                           7. Ind数据结构定义
************************************************************/
typedef enum
{
    LPHY_IND_AFC_PD_STATUS_ENA         = OM_CMD_ID(LPHY_AFC_MID, OM_TYPE_IND, 0x1),
    LPHY_IND_AFC_LOOP_STATE_ENA,
}LPHY_IND_AFC_ENUM;


#endif
void Ls_OmReq(UINT32 ulMsgId, UINT32 ulSessionId, void* pstMsg, UINT32 ulMsgSize);
void LTE_SdrProcIsrSymb0(void);
void LTE_FreqTimeProcIsrSymb0(void);
void LTE_SdrProcIsrSymb6(void);
void LTE_FreqTimeProcIsrSymb6(void);
void LTE_SdrProcIsrSymbA(void);
void LTE_FreqTimeProcIsrSymbA(void);
void   LS_UpdateCurrentCellInfo(void);
void LS_Init(void);
void LS_DmaInit(void);
void LS_SccStart(LTE_CELL_INFO_STRU *pstCellInfo);
void LS_SccStop(void); 
void   LS_HoldPccCurSubFrame(void);

void   LS_Hold(void);
void   LS_UnHold(void);
extern void LS_SetSampling(UINT32 ulFlag);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __AFC_OM_DEF_H__ */

