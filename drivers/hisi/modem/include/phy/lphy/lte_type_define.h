/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : lte_para.h
  版 本 号   : 初稿
  作    者   : tuzhiguo(52067)
  生成日期   : 2010年12月28日
  最近修改   :
  功能描述   : 和协议相关的类型定义
  函数列表   :
  修改历史   :
  1.日    期   : 2010年12月28日
    作    者   : tuzhiguo(52067)
    修改内容   : 创建文件
 2.日    期   : 2012年04月17日
   作    者   : Shen Guang
   修改内容   : [DTS2012022700423]FDD-TDD互操作

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

#ifndef __LTE_TYPE_DEFINE_H__
#define __LTE_TYPE_DEFINE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*
    LTE协议中常见带宽定义: 1.4M, 3M, 5M, 10M ,15M ,20M
*/
typedef enum __LTE_BAND_WIDTH_E__
{
    LTE_BAND_WIDTH_1D4M = 0,
    LTE_BAND_WIDTH_3M,
    LTE_BAND_WIDTH_5M,
    LTE_BAND_WIDTH_10M,
    LTE_BAND_WIDTH_15M,
    LTE_BAND_WIDTH_20M,
	LTE_BAND_WIDTH_BUTT
 }LTE_BAND_WIDTH_E;
typedef UINT16 LTE_BAND_WIDTH_ENUM_UINT16;


/*
    LTE协议中的定义循环前缀类型: normal or extened.
*/
typedef enum __LTE_CP_TYPE_E__
{
    LTE_CP_TYPE_NORMAL = 0,
    LTE_CP_TYPE_EXTENDED
}LTE_CP_TYPE_E;
typedef UINT16 LTE_CP_TYPE_ENUM_UINT16;


/*
    LTE协议中定义的帧结构类型: fdd or tdd
*/
typedef enum __LTE_FRAME_TYPE_E__
{
    LTE_FRAME_TYPE_FDD = 0,
    LTE_FRAME_TYPE_TDD
}LTE_FRAME_TYPE_E;
typedef UINT16 LTE_FRAME_TYPE_ENUM_UINT16;

typedef enum
{
    RX_PLL_QUERY = 0,
    TX_PLL_QUERY,
    PLL_QUERY_BUTT
}PLL_QUERY_TYPE;
typedef UINT16 PLL_QUERY_TYPE_U16;

typedef enum
{
    PLL_UNLOCK = 0,
    PLL_LOCK,
    PLL_QUERY_FAIL,
    PLL_BUTT
}PLL_STATUS_ENUM;
typedef UINT16 PLL_STATUS_ENUM_U16;


/*
    LTE协议中规定的TDD对应的子帧类型,参见协议211，4.2节: uplink,special,downlink.
*/
typedef enum __LTE_TDD_SUBFRAME_TYPE_E__
{
    LTE_TDD_SUBFRAME_TYPE_DOWNLINK = 0,
    LTE_TDD_SUBFRAME_TYPE_SPECIAL,
    LTE_TDD_SUBFRAME_TYPE_UPLINK,
    LTE_TDD_SUBFRAME_TYPE_MRS,
    LTE_TDD_SUBFRAME_TYPE_MBSFN,
    LTE_TDD_SUBFRAME_TYPE_BUTT
}LTE_TDD_SUBFRAME_TYPE_E;
typedef UINT16 LTE_TDD_SUBFRAME_TYPE_ENUM_UINT16;


/*
    LTE协议中规定的TDD对应的上下行子帧配比，参见协议211 4.2节.
*/
typedef enum __LTE_TDD_UD_CFG_E__
{
    LTE_TDD_UD_CFG_0 = 0,           /* DSUUU DSUUU*/
    LTE_TDD_UD_CFG_1,               /* DSUUD DSUUD*/
    LTE_TDD_UD_CFG_2,               /* DSUDD DSUDD*/
    LTE_TDD_UD_CFG_3,               /* DSUUU DDDDD*/
    LTE_TDD_UD_CFG_4,               /* DSUUD DDDDD*/
    LTE_TDD_UD_CFG_5,               /* DSUDD DDDDD*/
    LTE_TDD_UD_CFG_6                /* DSUUU DSUUD*/
}LTE_TDD_UD_CFG_E;
typedef UINT16 LTE_TDD_UD_CFG_ENUM_UINT16;


/*
    LTE协议中规定的TDD对应的特殊子帧类型, 见协议211 4.2节.
*/
typedef enum __LTE_TDD_SPEC_SUBFRM_CFG_E__
{
    LTE_TDD_SPEC_SUBFRM_CFG_0 = 0,
    LTE_TDD_SPEC_SUBFRM_CFG_1,
    LTE_TDD_SPEC_SUBFRM_CFG_2,
    LTE_TDD_SPEC_SUBFRM_CFG_3,
    LTE_TDD_SPEC_SUBFRM_CFG_4,
    LTE_TDD_SPEC_SUBFRM_CFG_5,
    LTE_TDD_SPEC_SUBFRM_CFG_6,
    LTE_TDD_SPEC_SUBFRM_CFG_7,
    LTE_TDD_SPEC_SUBFRM_CFG_8,
    LTE_TDD_SPEC_SUBFRM_CFG_9
}LTE_TDD_SPEC_SUBFRM_CFG_E;
typedef UINT16 LTE_TDD_SPEC_SUBFRM_CFG_ENUM_UINT16;


/*
    LTE协议中规定的调制方式: bpsk,qpsk, qam16, qam64
*/
typedef enum __LTE_MODULATION_SCHEME_E__
{
    LTE_MODULATION_SCHEME_BPSK =1,
    LTE_MODULATION_SCHEME_QPSK =2,
    LTE_MODULATION_SCHEME_QAM16=4,
    LTE_MODULATION_SCHEME_QAM64=6,
    LTE_MODULATION_SCHEME_BUTT
}LTE_MODULATION_SCHEME_E;
typedef UINT16 LTE_MODULATION_SCHEME_ENUM_UINT16;

typedef enum __LTE_PHY_CH_TYPE_E__
{
    LTE_PHY_CH_TYPE_PBCH,
    LTE_PHY_CH_TYPE_PCFICH,
    LTE_PHY_CH_TYPE_PDCCH,
    LTE_PHY_CH_TYPE_PHICH,
    LTE_PHY_CH_TYPE_PDSCH,
    LTE_PHY_CH_TYPE_PUCCH,
    LTE_PHY_CH_TYPE_PUSCH,
    LTE_PHY_CH_TYPE_PMCH
}LTE_PHY_CH_TYPE_E;
typedef UINT16 LTE_PHY_CH_TYPE_ENUM_UINT16;

/*
    LTE协议中规定的pdsch信道的传输方式，供8种: 参见协议213 7.1节
*/
typedef enum __LTE_PDSCH_TRANS_SCHEME_E__
{
    LTE_PDSCH_TRANS_SCHEME_PORT0 = 0,           /*1,发送端只有一根发射天线，采用该模式*/
    LTE_PDSCH_TRANS_SCHEME_SFBC,                /*2,发送端有2根或4根发射天线时可以采用该种传输模式*/
    LTE_PDSCH_TRANS_SCHEME_OPEN_LOOP_SM,        /*3,开环空间复用模式*/
    LTE_PDSCH_TRANS_SCHEME_CLOSE_LOOP_SM,       /*4,闭环空间复用模式*/
    LTE_PDSCH_TRANS_SCHEME_MU_MIMO,             /*5,多用户MIMO*/
    LTE_PDSCH_TRANS_SCHEME_CLOSE_LOOP_RI_1,     /*6,闭环 Rank=1 预编码模式*/
    LTE_PDSCH_TRANS_SCHEME_PORT5,               /*7,单天线口传输模式，port5*/
    LTE_PDSCH_TRANS_SCHEME_PORT78,              /*8,单天线口传输模式，port7,port8*/
    LTE_PDSCH_TRANS_SCHEME_PORT7,               /*undefined*/
    LTE_PDSCH_TRANS_SCHEME_PORT8                /*undefined*/
}LTE_PDSCH_TRANS_SCHEME_E;
typedef UINT16 LTE_PDSCH_TRANS_SCHEME_ENUM_UINT16;


/*
    LTE规定的连接状态,参见协议133定义
*/
typedef enum __LTE_RRC_STATE_E__
{
    LTE_RRC_STATE_NULL = 0,
    LTE_RRC_STATE_IDLE,
    LTE_RRC_STATE_CONNECTED,
    LTE_RRC_STATE_BUTT
}LTE_RRC_STATE_E;
typedef UINT16 LTE_RRC_STATE_ENUM_UINT16;


/*
    LTE规定的drx状态,参见协议321或者331
*/
typedef enum __LTE_DRX_STATE_E__
{
    LTE_DRX_STATE_NO,
    LTE_DRX_STATE_YES,
}LTE_DRX_STATE_E;
typedef UINT16 LTE_DRX_STATE_ENUM_UINT16;

typedef enum __LTE_DRX_TIMING_STATE_E__
{
    LTE_DRX_STATE_NO_PRESYNC,
    LTE_DRX_STATE_YES_PRESYNC
}LTE_DRX_TIMING_STATE_E;
typedef UINT16 LTE_DRX_TIMING_STATE_ENUM_UINT16;

typedef enum __LTE_DRX_PERIOD_E__
{
    LTE_DRX_PERIOD_320MS=0,
    LTE_DRX_PERIOD_640MS,
    LTE_DRX_PERIOD_1280MS,
    LTE_DRX_PERIOD_2560MS,
}LTE_DRX_PERIOD_E;
typedef UINT16 LTE_DRX_PERIOD_ENUM_UINT16;



/*
    GAP相关的状态定义:
        非激活:     上电后就是非激活状态，或者有原语通知gap释放就是非激活状态;
        激活:       收到gap激活通知后，内部就是激活状态;
        INVALID:    未收到激活原语，或者原语通知激活gap后且当前子帧并不是在gap周期期间;
        VALID:      原语通知激活gap后，并且当前子帧处在gap周期期间
*/
typedef enum __LTE_GAP_ACTIVE_STATE_E__
{
    LTE_GAP_ACTIVE_STATE_NO,                          /*GAP非激活状态*/
    LTE_GAP_ACTIVE_STATE_YES                          /*GAP激活状态*/
}LTE_GAP_ACTIVE_STATE_E;
typedef UINT16 LTE_GAP_ACTIVE_STATE_ENUM_UINT16;

typedef enum __LTE_GAP_STATE_E__
{
    LTE_GAP_STATE_INVALID,                              /*GAP未被激活或者GAP被激活但是无效(非gap子帧)*/
    LTE_GAP_STATE_VALID                                /*GAP被激活且有效*/
}LTE_GAP_STATE_E;
typedef UINT16 LTE_GAP_STATE_ENUM_UINT16;

/*
    MBSFN相关的状态定义:
        非激活:     上电后就是非激活状态，或者有原语通知MBSFN释放就是非激活状态;
        激活:       收到MBSFN激活原语后，内部就是激活状态;
        INVALID:    未收到激活原语，或者原语通知激活MBSFN后且当前子帧并不是在MBSFN周期期间;
        VALID:      原语通知激活MBSFN后，并且当前子帧处在MBSFN周期期间
*/
typedef enum __LTE_MBSFN_ACTIVE_STATE_E__
{
    LTE_MBSFN_ACTIVE_STATE_NO,                          /*MBSFN非激活状态*/
    LTE_MBSFN_ACTIVE_STATE_YES                          /*MBSFN原语激活了*/
}LTE_MBSFN_ACTIVE_STATE_E;
typedef UINT16 LTE_MBSFN_ACTIVE_STATE_ENUM_UINT16;

typedef enum __LTE_MBSFN_STATE_E__
{
    LTE_MBSFN_STATE_INVALID,                            /*MBSFN被激活但是无效(非MBSFN子帧)*/
    LTE_MBSFN_STATE_VALID                              /*MBSFN被激活且有效*/
}LTE_MBSFN_STATE_E;
typedef UINT16 LTE_MBSFN_STATE_ENUM_UINT16;


/*
    LTE规定的系统帧号、子帧号、符号标识，参见协议211。
*/
#define LTE_TIMING_MAX_MFN                                      1223
typedef struct __LTE_TIMING_INFO_STRU__
{
    UINT16                                  usSysFrmNum;        /*系统帧号: 0~1023*/
    UINT16                                  usSubFrmNum;        /*子帧号: 0~9 */
    UINT16                                  usSymNum;           /*符号: 0~13 or 0~11*/
    UINT16                                  usAfn;              /*AFN: 0~1023*/
    UINT16                                  usMfn;              /*MFN: 0~1223*/
    UINT16                                  usReserved;
}LTE_TIMING_INFO_STRU;


/*
    算法规定的信道空间相关性:
*/
typedef enum __LTE_CHAN_SPACE_CORR__
{
    LTE_CHAN_SPACE_CORR_HIGH = 0,
    LTE_CHAN_SPACE_CORR_MID,
    LTE_CHAN_SPACE_CORR_LOW
} LTE_CHAN_SPACE_CORR_ENUM;
typedef UINT8 LTE_CHAN_SPACE_CORR_ENUM_UINT8;


/*
    小区信息结构体定义
*/

typedef enum __CC_STATE_ENUM__
{
	CC_INVALID,
	CC_EXIST,
	CC_VALID,
	CC_STATE_BUTT
}CC_STATE_ENUM;

typedef UINT16	CC_STATE_ENUM_UINT16;




typedef struct __LTE_CELL_INFO_STRU__
{
	CC_STATE_ENUM_UINT16                    enCcState;          /*载波状态*/
    UINT16                                  usCellId;           /*小区id = 3*nid2 + nid1*/
    UINT16                                  usFreqInfo;         /*小区频点*/
    UINT16									usBandNum;
    UINT8                                   ucTransAntNum;      /*发射天线数*/
    UINT8                                   ucRecvAntNum;       /*接收天线数*/
    LTE_CP_TYPE_ENUM_UINT16                 enCpType;           /*cp类型*/
    LTE_BAND_WIDTH_ENUM_UINT16              enDlBandWidth;      /*eNodeB下行带宽*/
    LTE_FRAME_TYPE_ENUM_UINT16              enFrameType;        /*帧类型:FDD or TDD*/
    LTE_TDD_UD_CFG_ENUM_UINT16              enUDCfg;            /*TDD帧类型，上下行子帧配比*/
    LTE_TDD_SPEC_SUBFRM_CFG_ENUM_UINT16     enSpecSubframeCfg;  /*TDD帧类型，特殊子帧格式*/
    UINT16                                  usBSFreqForAgc;
    UINT16                                  usRsv;
}LTE_CELL_INFO_STRU;

typedef struct __LTE_DUAL_PSS_SCAN_INFO_STRU__
{
    INT32                                   ssOffSet0;           /*频移量1*/
    INT32                                   ssOffSet1;           /*频移量2*/
    UINT16                                  usFreqInfo0;
    UINT16                                  usFreqInfo1;
    UINT16                                  usDualPssFlag;       /*并行扫频标志位*/
    UINT16                                  usBSFreqForAgc;
}LTE_DUAL_PSS_SCAN_INFO_STRU;

typedef struct __LTE_CELL_UL_INFO_STRU__
{
    UINT16                              usUlFreqInfo;       /*上行频点*/
    LTE_BAND_WIDTH_ENUM_UINT16          enULBandWidth ;     /*上行带宽参数*/
    UINT16                              usUlBandNum;        /*上行BAND*/
    UINT8                               ucUlTransAntNum;      /*发射天线数*/
    UINT8                               ucReserv;       /**/
}LTE_CELL_UL_INFO_STRU;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __LTE_PARA_H__ */
