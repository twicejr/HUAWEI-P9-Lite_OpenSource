#ifndef __CSU_OM_DEF_H__
#define __CSU_OM_DEF_H__


#define MAX_IC_CELL_NUM_SOPPORT			2
#define MAX_ROU_SCAN_NOD_NUM			100
#define BANDSCAN_RSSI_BW_UNIT_SPAN		11
#define MAX_CELL_NUM_IN_1_QUEUE			(33)

#define DDR_DATA_PACKET_LEN			240

/*****************************************************************************
 数据结构说明  : 小区信息类型定义
*****************************************************************************/
typedef struct __CSU_CELL_INFO_STRU__
{
	UINT16 usCellID;        	//9u
	UINT8  ucCpMode;           	//1u
	UINT8  ucSFType;         	//1u
	INT16  sFFO;            	//16s
	INT16  sRssi;            	//16s

	INT16  sRsrp;
	INT16  sRsrq;
	UINT16 usStep2Ratio;    	//16u
	UINT16 usStep1Ratio;    	//10u

	UINT32 ulIto;           	//
}CSU_CELL_INFO_STRU;

typedef struct __CSU_CELLLIST_NODE_INFO_STRU__
{
	UINT8  ucCellAge;       	//小区存在年龄
	UINT8  ucRenewAge;     		//小区搜索到但未更新的次数
	UINT8  ucDiffCpAge;			//不相同CP类型年龄
	UINT8  ucOverCnt;			//本小区超越基准小区的次数统计
	UINT8  ucEmuValid;			//测量有效标志
	UINT8  ucWeakAge;			//弱小区年龄
	UINT8  ucRsvd0;				//
	UINT8  ucRsvd1;				//
	CSU_CELL_INFO_STRU stInfo;
}CSU_CELLLIST_NODE_INFO_STRU;


typedef struct
{
	UINT16       usBaseCellVld;
	UINT16       usBaseCellInvalidCnt;
	UINT16       usBaseCellId;
	UINT16       usBaseCellCp;
	UINT32       ulBaseCellIto;
	INT16		 sRssiEsti;
}CS_BASE_CELL_INFO_STRU;


/*****************************************************************************
 数据结构说明  : LPHY_CSU_OM_REQ_类型定义
*****************************************************************************/
typedef enum __LPHY_OM_REQ_CSU_ID_ENUM__
{
	LPHY_CSU_OM_REQ_RESERVED = OM_CMD_ID(LPHY_CSU_MID, OM_TYPE_REQ, 0x0),
	LPHY_CSU_OM_REQ_TD_IC,
	LPHY_CSU_OM_REQ_STEP1_NO_IC,
	LPHY_CSU_OM_REQ_STEP1_IN_IC,
	LPHY_CSU_OM_REQ_STEP2,
	LPHY_CSU_OM_REQ_BANDSCAN,
	LPHY_CSU_OM_REQ_AIDED_AGC,
	LPHY_CSU_OM_REQ_EMU_LIST,
	LPHY_CSU_OM_REQ_STAT,
	LPHY_CSU_OM_REQ_IRAT,
	LPHY_CSU_OM_REQ_PRINT_CTRL,
	LPHY_CSU_OM_REQ_DSP_CS_STOP_CTRL,
	LPHY_CSU_OM_REQ_DSP_BS_STOP_CTRL,
	LPHY_CSU_OM_REQ_BUTT,
}LPHY_OM_REQ_CSU_ID_ENUM;

/*****************************************************************************
 数据结构说明  : LPHY_CSU_OM_IND_类型定义
*****************************************************************************/
typedef enum __LPHY_SG_MSGID_CSU_SG_ENUM__
{
    LPHY_SG_CSU_RESERVED        = OM_CMD_ID(LPHY_CSU_MID,OM_TYPE_SG,0x0),
    LPHY_SG_CSU_PRT_TD_IC,
	LPHY_SG_CSU_RPT_STEP1_NO_IC,
	LPHY_SG_CSU_RPT_STEP1_IC,
	LPHY_SG_CSU_RPT_STEP2,
	LPHY_SG_CSU_RPT_BANDSCAN_RSSI,
	LPHY_SG_CSU_RPT_BANDSCAN_PSS,
	LPHY_SG_CSU_RPT_AIDED_AGC,
	LPHY_SG_CSU_RPT_EMU_LIST,
	LPHY_SG_CSU_RPT_STAT,
	LPHY_SG_CSU_RPT_IRAT,
	LPHY_SG_CSU_RPT_DDR_DATA,
	LPHY_SG_CSU_RPT_BUTT,
}LPHY_SG_MSGID_CSU_SG_ENUM;
typedef struct __LPHY_CSU_OM_IND_DDR_DATA_STRU__
{
	UINT8  ucAntNumber;
	UINT8  ucAntIndex;
	UINT8  ucAntFinishedFlag[2];
	UINT32 ulPacketIndex;

	UINT32 ulDDRData[DDR_DATA_PACKET_LEN];

}LPHY_CSU_OM_IND_DDR_DATA_STRU;

#define LPHY_CSU_OM_IND_DDR_DATA_DEFAULT	{\
												0,\
												0,\
												{0},\
												0,\
												{0}\
											}

/*****************************************************************************
 数据结构说明  : LPHY_CSU_OM_REQ_TD_IC 相关的OM结构体定义
*****************************************************************************/
typedef struct __LPHY_CSU_OM_REQ_TD_IC_STRU__
{
	UINT8 ucDisplayFlag;
	UINT8 ucTD_IC_Switch;
	UINT8 ucMaxICCellNum;
	UINT8 ucStep2Ratio_IC;

	UINT8 ucStep2Ratio_IC_H;
	UINT8 ucNoiseZoneZFSwitchInit;
	UINT8 ucNoiseZoneZFSwitchNonInit;
	UINT8 ucSideReshapeSwitch;

	UINT8 ucTimeFail_interFCell0;
	UINT8 ucTimeFail_interFCell1;
	UINT8 ucVStep2Ratio;
	UINT8 ucStep1NoIcSdrEN;
}LPHY_CSU_OM_REQ_TD_IC_STRU;


#define LPHY_CSU_OM_REQ_TD_IC_DEFAULT 	{\
											1,1,1,24,\
											32,1,0,1,\
											5,3,0,1	 \
										}

typedef struct __LPHY_CSU_OM_IND_TD_IC_Cell_INFO_STRU__
{
	UINT16 usCellID;
	UINT16 usPos;
	UINT16 enCpMode;
	INT16  sAngle;
	UINT16 usICFlag;
	UINT16 usTimeFail;
	UINT16 usStep2R_NoIC;
	UINT16 usStep1Ratio;
}LPHY_CSU_OM_IND_TD_IC_Cell_INFO_STRU;

typedef struct __LPHY_CSU_OM_IND_TD_IC_STRU__
{
	LPHY_CSU_OM_REQ_TD_IC_STRU	stOmReqTdIc;
	UINT32 						ulCurICCellNum;

	LPHY_CSU_OM_IND_TD_IC_Cell_INFO_STRU stIcCellList[MAX_IC_CELL_NUM_SOPPORT];

}LPHY_CSU_OM_IND_TD_IC_STRU;

#define LPHY_CSU_OM_IND_TD_IC_DEFAULT	{\
											LPHY_CSU_OM_REQ_TD_IC_DEFAULT,\
											0,\
											{\
												{0,0,0,0,0,0,0,0},\
												{0,0,0,0,0,0,0,0}\
											}\
										}


/*****************************************************************************
 数据结构说明  : LPHY_CSU_OM_REQ_STEP1_NO_IC/LPHY_CSU_OM_REQ_STEP1_IN_IC 相关的OM结构体定义
*****************************************************************************/
typedef struct __CS_START_STATUS_REG_STRU__
{
	UINT32	bCsuStartTime		:18;
	UINT32	bSubFrameIdx		:4;
	UINT32	bCsuInterFlag		:1;
	UINT32	bStep1SuccNum		:5;
	UINT32  b5msIdx				:4;
}CS_START_STATUS_REG_STRU;

/*****************************************************************************
 数据结构  : PSS_ROUGH_SYNC_INFO_STRU
 结构说明  : PSS同步上报信息成员结构体
*****************************************************************************/
typedef  struct __PSS_SYNC_INFO_STRU__
{
	UINT32 Nid2	:2;
	UINT32 Pos	:14;
	UINT32 Corr	:10;
	UINT32 Rsvd	:6;

	INT16  Phase;
	INT16  Freq;
}PSS_SYNC_INFO_STRU;

typedef struct __LPHY_CSU_OM_REQ_STEP1_STRU__
{
	UINT8  ucDisplayFlag;
	UINT8  ucFilterEnable;
	UINT8  ucFilterCoef0[8];
	UINT8  ucFilterCoef1[8];

	UINT8  ucFilterMaxIdx;
	UINT8  ucWindowEnable;
	UINT16 ucWindowLength;
}LPHY_CSU_OM_REQ_STEP1_STRU;


#define LPHY_CSU_OM_REQ_STEP1_DEFAULT	{\
											0,1,\
											{1,1,21,1,13,11,9,1},\
											{0,1, 6,2, 6, 6,6,3},\
											3,0,9600\
										}


typedef struct __LPHY_CSU_OM_IND_STEP1_STRU__
{
	LPHY_CSU_OM_REQ_STEP1_STRU	stOmReqStep1;
	UINT16 						usFreqInfo;
	UINT8 						ucCurPssNum;
	UINT8 						uc5msIdx;
    UINT16                      usStep1BbpIndex;
	PSS_SYNC_INFO_STRU			astPssSyncInfo[16];
}LPHY_CSU_OM_IND_STEP1_STRU;

#define LPHY_CSU_OM_IND_STEP1_DEFAULT	{\
											LPHY_CSU_OM_REQ_STEP1_DEFAULT,\
											0xffff,\
											0,\
											0,\
											0,\
											{\
												{0,0,0,0,0,0},\
												{0,0,0,0,0,0},\
												{0,0,0,0,0,0},\
												{0,0,0,0,0,0},\
												{0,0,0,0,0,0},\
												{0,0,0,0,0,0},\
												{0,0,0,0,0,0},\
												{0,0,0,0,0,0},\
												{0,0,0,0,0,0},\
												{0,0,0,0,0,0},\
												{0,0,0,0,0,0},\
												{0,0,0,0,0,0},\
												{0,0,0,0,0,0},\
												{0,0,0,0,0,0},\
												{0,0,0,0,0,0},\
												{0,0,0,0,0,0}\
											}\
										}

/*****************************************************************************
 数据结构说明  : LPHY_CSU_OM_REQ_STEP2 相关的OM结构体定义
*****************************************************************************/
typedef struct __LPHY_CSU_OM_REQ_STEP2_STRU__
{
	UINT8  ucDisplayFlag;
	UINT8  ucFreqCorrEn;
	UINT8  ucFFoSrc;
	UINT8  ucZFNoizeZone;
	UINT8  ucRatioTH_Init[8];
	UINT8  ucRatioTH_Norm[8];
	UINT8  ucRatioTH_Gap[4];
	UINT8  ucMaxDelay;
	UINT8  ucLeakLength;
}LPHY_CSU_OM_REQ_STEP2_STRU;

#define LPHY_CSU_OM_REQ_STEP2_DEFAULT 	{\
											0,1,0,1,\
											{32,26,26,25,25,25,25,25},\
											{21,21,21,22,22,22,22,22},\
											{21,18,18,18},\
											9,\
											2\
										}

typedef struct __LPHY_CSU_OM_IND_STEP2_SSS_DET_INFO_STRU__
{
	UINT16 	usCellID;
	UINT16 	usPos;

	UINT8 	ucCpMode;
	UINT8 	uc5msInd;
	UINT8	ucIcFlag;
	UINT8	uc5msCnt;

	INT16  	lAngle;
	UINT16  usS1R;
	UINT16  usS2R;
	UINT16  usSSR;
}LPHY_CSU_OM_IND_STEP2_SSS_DET_INFO_STRU;


typedef struct __LPHY_CSU_OM_IND_STEP2_STRU__
{
	LPHY_CSU_OM_REQ_STEP2_STRU	stOmReqStep2;
	UINT16 						usCurPssNum;
	UINT16 						usFreqInfo;

	LPHY_CSU_OM_IND_STEP2_SSS_DET_INFO_STRU stSssDetInfo[16];

}LPHY_CSU_OM_IND_STEP2_STRU;


#define	LPHY_CSU_OM_IND_STEP2_DEFAULT	{\
											LPHY_CSU_OM_REQ_STEP2_DEFAULT,\
											0,\
											0xffff,\
											{\
												{0,0,0,0,0,0,0,0,0,0},\
												{0,0,0,0,0,0,0,0,0,0},\
												{0,0,0,0,0,0,0,0,0,0},\
												{0,0,0,0,0,0,0,0,0,0},\
												{0,0,0,0,0,0,0,0,0,0},\
												{0,0,0,0,0,0,0,0,0,0},\
												{0,0,0,0,0,0,0,0,0,0},\
												{0,0,0,0,0,0,0,0,0,0},\
												{0,0,0,0,0,0,0,0,0,0},\
												{0,0,0,0,0,0,0,0,0,0},\
												{0,0,0,0,0,0,0,0,0,0},\
												{0,0,0,0,0,0,0,0,0,0},\
												{0,0,0,0,0,0,0,0,0,0},\
												{0,0,0,0,0,0,0,0,0,0},\
												{0,0,0,0,0,0,0,0,0,0},\
												{0,0,0,0,0,0,0,0,0,0} \
											}\
										}

/*****************************************************************************
 数据结构说明  : LPHY_CSU_OM_REQ_BANDSCAN 相关的OM结构体定义
*****************************************************************************/
typedef struct __LPHY_CSU_OM_REQ_BANDSCAN_STRU__
{
	UINT8  ucDisplayFlag;
	UINT8  ucHiPowZoneDisp;
	UINT8  ucHiPrioBandDisp;
	UINT8  ucBandScanInfDisp;
	UINT8  ucHiPowZoneDet;
	UINT8  ucHiPowZoneWin;
	UINT16 usPssRatio;
	UINT16 usFreqPointNum;
	UINT16 usFreqCorrSet[3];
}LPHY_CSU_OM_REQ_BANDSCAN_STRU;


#define LPHY_CSU_OM_REQ_BANDSCAN_DEFAULT	{\
												0,0,0,0,\
												1,8,200,\
												1,\
												{0,0,0}\
											}

typedef struct __ONE_HI_POW_ZONE_INFO_S__
{
	UINT8  ucStartIdx;
	UINT8  ucEndIdx;
	SINT16 ssAverRssi;
}ONE_HI_POW_ZONE_INFO_S;

typedef struct __LPHY_HIGH_POW_ZONE_INFO_STRU__
{
	UINT32 					ulHiPowZoneNum;
	ONE_HI_POW_ZONE_INFO_S 	astHiPowZone[16];
}LPHY_HIGH_POW_ZONE_INFO_STRU;

#define LPHY_HIGH_POW_ZONE_INFO_STRU_DEFAULT	{\
													0,\
													{\
														{0,0,0},\
														{0,0,0},\
														{0,0,0},\
														{0,0,0},\
														{0,0,0},\
														{0,0,0},\
														{0,0,0},\
														{0,0,0},\
														{0,0,0},\
														{0,0,0},\
														{0,0,0},\
														{0,0,0},\
														{0,0,0},\
														{0,0,0},\
														{0,0,0},\
														{0,0,0}\
													}\
												}


/*频段链表节点数据结构*/
typedef struct __ONE_RSSI_BANDSCAN_RES_INFO_S__
{
	UINT16 usCentralFreq;
	SINT16 ssAverageRssi;
    UINT16 usAgcBsFreq;
}ONE_RSSI_BANDSCAN_RES_INFO_S;



typedef struct __LPHY_ORDERED_BAND_LIST_STRU__
{
	UINT32							ulTotalBandNum;
	ONE_RSSI_BANDSCAN_RES_INFO_S 	astHiPowZone[MAX_ROU_SCAN_NOD_NUM];
}LPHY_ORDERED_BAND_LIST_STRU;

#define LPHY_ORDERED_BAND_LIST_STRU_DEFAULT		{\
													0,\
													{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
													{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
													{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
													{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
													{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
													{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
													{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
													{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
													{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
													{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}\
												}

/*频段链表节点数据结构*/
typedef struct __BANDSCAN_PSS_NOD_STRU__
{
	UINT16  usStep1Ratio;
	UINT16  usCenterBand;
}BANDSCAN_PSS_NOD_STRU;

typedef struct __LPHY_CSU_OM_IND_BS_PSS_IND_STRU__
{
	UINT8					ucTotalBandNum;
	UINT8					ucPssEvaTime;
	UINT8					ucFreqCorrIdx;
	UINT8					ucReserved;
	BANDSCAN_PSS_NOD_STRU 	astPssScanInf[BANDSCAN_RSSI_BW_UNIT_SPAN];
}LPHY_CSU_OM_IND_BS_PSS_RPT_STRU;

#define  LPHY_CSU_OM_IND_BS_PSS_RPT_STRU_DEFAULT	{\
														0,0,0,0,\
														{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}\
													}

#define aucPssScanList_DEFAULT		{\
										0,0,0,0,0,0,0,0,0,0,\
										0,0,0,0,0,0,0,0,0,0,\
										0,0,0,0,0,0,0,0,0,0,\
										0,0,0,0,0,0,0,0,0,0,\
										0,0,0,0,0,0,0,0,0,0,\
										0,0,0,0,0,0,0,0,0,0,\
										0,0,0,0,0,0,0,0,0,0,\
										0,0,0,0,0,0,0,0,0,0,\
										0,0,0,0,0,0,0,0,0,0,\
										0,0,0,0,0,0,0,0,0,0\
									}

typedef struct __LPHY_CSU_OM_IND_BANDSCAN_STRU__
{
	LPHY_CSU_OM_REQ_BANDSCAN_STRU	stOmReqBandscan;
	LPHY_HIGH_POW_ZONE_INFO_STRU	stHiPowZoneList;
	LPHY_ORDERED_BAND_LIST_STRU		stRssiBandList;
	UINT8							aucPssScanList[MAX_ROU_SCAN_NOD_NUM];
}LPHY_CSU_OM_IND_BANDSCAN_STRU;


#define LPHY_CSU_OM_IND_BANDSCAN_STRU_DEFAULT	{\
													LPHY_CSU_OM_REQ_BANDSCAN_DEFAULT,\
													LPHY_HIGH_POW_ZONE_INFO_STRU_DEFAULT,\
													LPHY_ORDERED_BAND_LIST_STRU_DEFAULT,\
													aucPssScanList_DEFAULT\
												}

/*****************************************************************************
 数据结构说明  : LPHY_CSU_OM_REQ_AIDED_AGC 相关的OM结构体定义
*****************************************************************************/
typedef struct __LPHY_CSU_OM_REQ_AIDED_AGC_STRU__
{
	UINT32  ulDisplayFlag;
}LPHY_CSU_OM_REQ_AIDED_AGC_STRU;


typedef struct __LPHY_CSU_OM_IND_AIDED_AGC_STRU__
{
	LPHY_CSU_OM_REQ_AIDED_AGC_STRU	stOmReqAidedAgc;
	UINT32							ulPssSigPow;
}LPHY_CSU_OM_IND_AIDED_AGC_STRU;


#define	LPHY_CSU_OM_IND_AIDED_AGC_STRU_DEFAULT	{{0},0}

/*****************************************************************************
 数据结构说明  : LPHY_CSU_OM_REQ_EMU_LIST 相关的OM结构体定义
*****************************************************************************/

typedef struct __EMU_LIST_MAINTAIN_PARA_STRU__
{
	UINT16	usDelta1;
	UINT16	usDelta2;
	UINT16 	usEpsilon;
	UINT16 	usN_NULL;
	UINT16 	usT0;
	UINT16 	usT1;
}EMU_LIST_MAINTAIN_PARA_STRU;

typedef struct __LPHY_CSU_OM_REQ_EMU_LIST_STRU__
{
	UINT16	 usEmuListDispFlag;
	UINT8	 ucT_CP;
	UINT8	 ucN_NULL;
	EMU_LIST_MAINTAIN_PARA_STRU stHomeIdleList;
	EMU_LIST_MAINTAIN_PARA_STRU stHomeConnList;
	EMU_LIST_MAINTAIN_PARA_STRU stIntraIdleList;
	EMU_LIST_MAINTAIN_PARA_STRU stIntraConnList;
	EMU_LIST_MAINTAIN_PARA_STRU stInterIdleList;
	EMU_LIST_MAINTAIN_PARA_STRU stInterConnList;
}LPHY_CSU_OM_REQ_EMU_LIST_STRU;

#define EMU_LIST_MAINTAIN_PARA_HOME_DEFAULT		{20,10,5,18,4,1}
#define EMU_LIST_MAINTAIN_PARA_OTHER_DEFAULT	{20,10,300,18,4,1}

typedef enum __EMU_LIST_TYPE_ENUM__
{
	EMU_LIST_PServer,
	EMU_LIST_SServer,
	EMU_LIST_EmuList0,
	EMU_LIST_EmuList1,
	EMU_LIST_EmuList2,
	EMU_LIST_EmuList3,
	EMU_LIST_EmuList4,
	EMU_LIST_EmuList5,
	EMU_LIST_EmuList6,
	EMU_LIST_EmuList7,
}EMU_LIST_TYPE_ENUM;

typedef UINT16 	EMU_LIST_TYPE_ENUM_UINT16;


typedef struct __LPHY_CSU_OM_REQ_RPT_LIST_STRU__
{
	EMU_LIST_TYPE_ENUM_UINT16			enCellList;	//本队列类型
	LRRC_LPHY_LTE_MODE_TYPE_ENUM_UINT16 enDuplex;	//本队列对LTE双工模式
	UINT16 								usFreq;		//本队列对应频点
	UINT16 								usLen;		//队列长度
	UINT16 								usBaseFlg;	//本队列是否需要选择基准小区
	UINT16 								usBaseIdx;	//本队列基准小区的索引，索引为(-1)的时候表示基准小区不存在
	CSU_CELLLIST_NODE_INFO_STRU			astCellList[MAX_CELL_NUM_IN_1_QUEUE];
}LPHY_CSU_OM_REQ_RPT_LIST_STRU;


typedef struct __LPHY_CSU_OM_IND_EMU_LIST_STRU__
{
	LPHY_CSU_OM_REQ_EMU_LIST_STRU	stOmReqEmuList;
	LPHY_CSU_OM_REQ_RPT_LIST_STRU	stRptEmuList;
}LPHY_CSU_OM_IND_EMU_LIST_STRU;

#define LPHY_CSU_OM_REQ_EMU_LIST_STRU_DEFAULT	{	0,\
													4,\
													18,\
													EMU_LIST_MAINTAIN_PARA_HOME_DEFAULT,\
													EMU_LIST_MAINTAIN_PARA_HOME_DEFAULT,\
													EMU_LIST_MAINTAIN_PARA_OTHER_DEFAULT,\
													EMU_LIST_MAINTAIN_PARA_OTHER_DEFAULT,\
													EMU_LIST_MAINTAIN_PARA_OTHER_DEFAULT,\
													EMU_LIST_MAINTAIN_PARA_OTHER_DEFAULT\
												}

#define CSU_CELLLIST_NODE_INFO_STRU_DEFAULT		{0,0,0,0,0,0,0,0,{0,0,0,0,0,0,0,0,0,0}}

#define LPHY_CSU_OM_REQ_RPT_LIST_STRU_DEFAULT	{	0,\
													0,\
													0,\
													0,\
													0,\
													0,\
													{	CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT,\
														CSU_CELLLIST_NODE_INFO_STRU_DEFAULT\
													}\
												}

#define LPHY_CSU_OM_IND_EMU_LIST_STRU_DEFAULT	{\
													LPHY_CSU_OM_REQ_EMU_LIST_STRU_DEFAULT,\
													LPHY_CSU_OM_REQ_RPT_LIST_STRU_DEFAULT\
												}

/*****************************************************************************
 数据结构说明  : LPHY_CSU_OM_REQ_STAT 相关的OM结构体定义
*****************************************************************************/
typedef struct __LPHY_CSU_OM_REQ_STAT_STRU__
{
	UINT16 usStatRptEn;
	UINT16 usStatPeriod;
	UINT16 usFreq;
	UINT16 usCellNum;
	UINT16 usCellList[32];
}LPHY_CSU_OM_REQ_STAT_STRU;

#define LPHY_CSU_OM_REQ_STAT_STRU_DEFAULT	{\
												0,0,0,0,\
												{\
													0,0,0,0,0,0,0,0,\
													0,0,0,0,0,0,0,0,\
													0,0,0,0,0,0,0,0,\
													0,0,0,0,0,0,0,0\
												}\
											}



typedef struct __LPHY_CSU_OM_RPT_STAT_STRU__
{
	UINT32 ulTotalRound;
	UINT32 ulSuccRound;
	UINT32 ulAccuFaAlm;
}LPHY_CSU_OM_RPT_STAT_STRU;

#define LPHY_CSU_OM_RPT_STAT_STRU_DEFAULT	{0,0,0}

typedef struct __LPHY_CSU_OM_IND_STAT_STRU__
{
	LPHY_CSU_OM_REQ_STAT_STRU	stOmReqStat;
	LPHY_CSU_OM_RPT_STAT_STRU   stStatInf;
}LPHY_CSU_OM_IND_STAT_STRU;

#define LPHY_CSU_OM_IND_STAT_STRU_DEFAULT	{\
												LPHY_CSU_OM_REQ_STAT_STRU_DEFAULT,\
												LPHY_CSU_OM_RPT_STAT_STRU_DEFAULT\
											}


/*****************************************************************************
 数据结构说明  : LPHY_CSU_OM_REQ_PRINT_CTRL 相关的OM结构体定义
*****************************************************************************/
typedef struct __LPHY_CSU_OM_REQ_PRINT_CTRL_STRU__
{
	UINT8 ucStep1ResDispFlg;
	UINT8 ucStep2ResDispFlg;
	UINT8 ucRlRptResDispFlg;
	UINT8 ucReservedFlg;
}LPHY_CSU_OM_REQ_PRINT_CTRL_STRU;

#define LPHY_CSU_OM_REQ_PRINT_CTRL_STRU_DEFAULT 	{0,1,0,0}

/*****************************************************************************
 数据结构说明  : LPHY_CSU_OM_REQ_DSP_STOP_CTRL 相关的OM结构体定义
*****************************************************************************/
typedef enum __LPHY_CSU_OM_REQ_DSP_STOP_SRC_ENUM__
{
	MAX_NUM_CELL_STOP	  	= 0,
	EXPECT_CELL_LOST_STOP 	= 1,
	EXPECT_CELL_DETECT_STOP = 2,
}CSU_DSP_STOP_SRC_ENUM;

typedef UINT8	CSU_DSP_STOP_SRC_ENUM_UINT8;

typedef struct __LPHY_CSU_OM_REQ_DSP_CS_STOP_CTRL_STRU__
{
	UINT8 							ucStopEnable;
	CSU_DSP_STOP_SRC_ENUM_UINT8 	enStopMode;
	UINT16 	usFreq;
	UINT8 	ucMaxCellNumber;
	UINT8 	enCpMode;
	UINT16 	usExpectCellID;
}LPHY_CSU_OM_REQ_DSP_CS_STOP_CTRL_STRU;

#define LPHY_CSU_OM_REQ_DSP_CS_STOP_CTRL_STRU_DEFAULT	{0,0,0,0,0,0}

typedef struct __LPHY_CSU_OM_REQ_DSP_BS_STOP_CTRL_STRU__
{
	UINT32 ulBsPssStopFreq;
	UINT32 ulBsPssStopThLo;
	UINT32 ulBsPssStopThHi;
	UINT32 ulBsPssStopFlag;
}LPHY_CSU_OM_REQ_DSP_BS_STOP_CTRL_STRU;

#define LPHY_CSU_OM_REQ_DSP_BS_STOP_CTRL_STRU_DEFAULT	{0,0,0,0}

#endif

