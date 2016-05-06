/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : LUPAppItf.h
  Description     : L2AppItf.c header file
  History         :
     1.h42180       2009-3-31     Draft Enact
     2.Date         : 2010/8/5
       Author       : l62099
       Modification : 将IDLE态数据缓存大小从12改为256
     3.Date         : 2010/8/19
       Author       : y00151394
       Modification : 将APP接收队列大小从512改为1024

******************************************************************************/

#ifndef __LUPAPPITF_H__
#define __LUPAPPITF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "LUPZeroCopy.h"
#include "OmCommon.h"
#include "LUPQueue.h"
#include "AppL2Interface.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/

#define APPITF_DATA_REQ_QUE_SIZE        1024        /*暂定512*/
#define APPITF_DATA_IND_QUE_SIZE        512         /*暂定64*/
#define APPITF_APP_IDLE_BUF_QUE_SIZE    256         /*Idle状态下缓冲队列长度*/
#define APPITF_APP_DATA_MAX_SIZE        1500        /*典型IP包为1500字节,因此暂定1500*/

#define PS_OM_MAX_DRB_NUM                  8  /*目前业务场景只支持8个DRB，可维可测使用*/

#define L2_THR_STAT_UNSIGN_LONG_MAX               (0x7FFFFFFFUL)
#define L2_THR_STAT_MAX_NUM                       10
#define L2_THR_STAT_BYTE_CNT_MAX                  (L2_THR_STAT_UNSIGN_LONG_MAX/1000)

#define NCM_DEVICE_NUM   2    /*BSP NCM 网卡数目*/

extern VOS_UINT32  g_ulUlFcThroughputStat;
#define FC_UL_THROUGHPUT_STAT_INC(n)    (g_ulUlFcThroughputStat += (n))

/*****************************************************************************
 结构名    : LRLC_STATE_EN
 协议表格  :
 ASN.1描述 :
 结构说明  : 用户面时延优化模式枚举定义
*****************************************************************************/

enum LUP_LATENCY_OPT_MODE_EN
{
    LUP_LOM_MODE_NORMAL     = 0,       /*正常模式*/
    LUP_LOM_MODE_OPTIMIZE      ,       /*时延优化模式*/

    LUP_LOM_MODE_BUTT
};

extern VOS_UINT32 g_ulLupLatencyOptMode;
extern VOS_UINT32 g_ulLupLatencyOptSwitch;
extern VOS_UINT32 g_ulLomSduCnt;
extern VOS_UINT32 g_ulLomOmSwitch;
#define LUP_GET_LATENCY_OPT_MODE()      ((PS_TRUE == g_ulLupLatencyOptSwitch) ? g_ulLupLatencyOptMode:LUP_LOM_MODE_NORMAL)
#define LUP_SET_LATENCY_OPT_MODE(n)     (g_ulLupLatencyOptMode = (n))

#define LUP_INC_LOM_SDU_COUNTER()       (g_ulLomSduCnt = TTF_MOD_ADD(g_ulLomSduCnt,  1, 0x80000000))
#define LUP_GET_LOM_SDU_COUNTER()       (g_ulLomSduCnt)
#define LUP_GET_LOM_NEW_SDU_CNT(ulCurr, ulLast)      (TTF_MOD_SUB((ulCurr), (ulLast), 0x80000000))

extern VOS_VOID LUP_LatencyOptModeCtrl(VOS_VOID);


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/



/*****************************************************************************
 枚举名    : L2_DCM_SCELL_STATUS_ENUM
 枚举说明  : SCELL状态
*****************************************************************************/
typedef enum
{
    L2_MAC_SCELL_ACTIVE    = 0,
    L2_MAC_SCELL_DEACTIVE,
    L2_MAC_SCELL_NOT_CONFIG,
    L2_MAC_SCELL_BUTT
}L2_DCM_SCELL_STATUS_ENUM;

typedef VOS_UINT8 L2_DCM_SCELL_STATUS_ENUM_UINT8;
/*****************************************************************************
   5 STRUCT
*****************************************************************************/

/*IP地址*/
typedef struct
{
    VOS_UINT8   aucIPaddr[4];
    VOS_UINT8   ucInitFlag;
    VOS_UINT8   aucRev[3];
}GIP_ADDR_STRU;


/*****************************************************************************
 结构名    : APP_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :APP层统计信息的结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32               ulMaxRate;            /*最大速率*/
    VOS_UINT32               ulRate;               /*平均速率*/
    VOS_UINT32               ulPacketsCntOK;       /*成功包数*/
    VOS_UINT32               ulPacketsCntErr;      /*出错包数*/
    VOS_UINT32               ulPacketsCntOverflow; /*溢出包数,未能发送或接收*/
} APP_STAT_INFO_STRU;

/*****************************************************************************
 结构名    : L2_APP_THROUGHPUT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :L2向OM周期上报APP层Tx与Rx统计信息的结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                       ulMsgId;
    APP_MSG_HEADER
    VOS_UINT32                       ulOpId;
    APP_STAT_INFO_STRU               stRxThoughputInfo; /*接收统计信息*/
    APP_STAT_INFO_STRU               stTxThoughputInfo; /*发送统计信息*/
} L2_APP_THROUGHPUT_IND_STRU;

/*****************************************************************************
 结构名    : L2_APP_THROUGHPUT_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :L2周期上报APP层Tx与Rx统计信息命令处理结构
*****************************************************************************/
typedef struct
{
    APP_CMD_ENUM_UINT8                enState;
    VOS_UINT8                         ucRsv[3];
    VOS_UINT32                        ulRptPeriod;       /*单位ms，最小值100ms，步长100ms*/
    VOS_UINT32                        ulCurTime;         /*当前时间*/
    VOS_UINT32                        ulPreTime;         /*上一次的时间*/
    VOS_UINT32                        ulPreTxTotalLen;   /*上一次发送的总字节数据,间隔5ms*/
    VOS_UINT32                        ulCurTxTotalLen;   /*当前发送的总字节数据*/
    VOS_UINT32                        ulPreRxTotalLen;   /*上一次接收的总字节数据,间隔5ms*/
    VOS_UINT32                        ulCurRxTotalLen;   /*当前接收的总字节数据*/
    APP_STAT_INFO_STRU                stRxThoughputInfo; /*接收统计信息*/
    APP_STAT_INFO_STRU                stTxThoughputInfo; /*发送统计信息*/
} L2_APP_THROUGHPUT_STAT_INFO_STRU;


/*****************************************************************************
 结构名    : L2_THROUGHPUT_ULDL_STAT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :L2各层上/下行流量统计信息的结构。同时用于数传可维可测监控和L2内部的流量统计
*****************************************************************************/
typedef struct
{
    VOS_UINT32                 ulUlDataRate;        /*上行数据速率*/
    VOS_UINT32                 ulDlDataRate;        /*下行数据速率*/
} L2_THROUGHPUT_ULDL_STAT_STRU;

/*****************************************************************************
 结构名    : L1_THROUGHPUT_ULDL_STAT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :L1 UL/DL统计信息的结构。只用于L2内部的流量统计
*****************************************************************************/
typedef struct
{
    VOS_UINT32                 ulSinr;              /*SINR*/
    VOS_UINT32                 ulL1ThruputRight;    /*下行速率*/
    VOS_UINT32                 ulL1ThruputTotal;    /*下行数据速率*/
} L1_THROUGHPUT_ULDL_STAT_STRU;

/*****************************************************************************
 结构名    : L2_DRB_THROUGHPUT_ULDL_STAT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :L2各DRB上/下行流量统计信息的结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                 ulRbId;              /*RB ID*/
    VOS_UINT32                 ulUlDataRate;        /*上行数据速率*/
    VOS_UINT32                 ulDlDataRate;        /*下行数据速率*/
} L2_DRB_THROUGHPUT_ULDL_STAT_STRU;

/*****************************************************************************
 结构名    : L2_OM_THROUGHPUT_STAT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :L2向MSP周期上报数传可维可测结果的信息结构。 只用于数传可维可测监控
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      ulTimeStamp;         /*时间戳，通过PS_GET_TICK()获得*/
    VOS_UINT16                                      usFrame;             /*帧号*/
    VOS_UINT16                                      usSubFrame;          /*子帧号*/
    VOS_UINT32                                      ulRptPeriod;         /*上报周期*/
    L2_THROUGHPUT_ULDL_STAT_STRU                    stAppThoughputInfo;  /*APP发送给PDCP/APP接收到PDCP的统计信息*/
    L2_THROUGHPUT_ULDL_STAT_STRU                    stPdcpThoughputInfo; /*PDCP发送给RLC/PDCP接收到RLC的统计信息*/
    L2_THROUGHPUT_ULDL_STAT_STRU                    stRlcThoughputInfo;  /*RLC发送给MAC/RLC接收到MAC的统计信息*/
    L2_THROUGHPUT_ULDL_STAT_STRU                    stMacThoughputInfo;  /*MAC发送给RTT/MAC接收到RTT的统计信息*/
    L2_DRB_THROUGHPUT_ULDL_STAT_STRU                stDrbThoughputInfo[PS_OM_MAX_DRB_NUM];/*DRB上下行收到的流量统计信息*/
} L2_OM_THROUGHPUT_STAT_IND_STRU;

/*V7R2-DT增加CA L2 吞吐量上报结构体定义的代码 q00208938 2014/03/24，begin*/
typedef struct
{
    CA_CELL_STATUS_STRU stCaCellStatus;
    L2_THROUGHPUT_ULDL_STAT_STRU stMacThroughput;  /*MAC层上下行吞吐量*/
}MAC_CA_THROUGHPUT_STRU;

/*****************************************************************************
 结构名    : CA_L2_OM_THROUGHPUT_STAT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :L2向MSP周期上报数传可维可测结果的信息结构。 只用于数传可维可测监控
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulTimeStamp;  /*时间戳，通过PS_GET_TICK()获得*/
    VOS_UINT16 usFrame;  /*帧号*/
    VOS_UINT16 usSubFrame;  /*子帧号*/
    VOS_UINT32 ulRptPeriod;  /*上报周期*/
    L2_THROUGHPUT_ULDL_STAT_STRU stAppThroughputInfo;  /*APP发送给PDCP/APP接收到PDCP的统计信息*/
    L2_THROUGHPUT_ULDL_STAT_STRU stPdcpThroughputInfo;  /*PDCP发送给RLC/PDCP接收到RLC的统计信息*/
    L2_THROUGHPUT_ULDL_STAT_STRU stRlcThroughputInfo;  /*RLC发送给MAC/RLC接收到MAC的统计信息*/
    L2_THROUGHPUT_ULDL_STAT_STRU stMacTotalThroughputInfo;  /*MAC发送给RTT/MAC接收到RTT的统计信息*/
    L2_DRB_THROUGHPUT_ULDL_STAT_STRU astDrbThroughputInfo[PS_OM_MAX_DRB_NUM];/*DRB上下行收到的流量统计信息*/
    MAC_CA_THROUGHPUT_STRU astMacCaThroughput[CA_MAX_CELL_NUM]; /*长度为8，数组下标代表CellIndex，0:PCell，1~7:SCell*/
} CA_L2_OM_THROUGHPUT_STAT_IND_STRU;
/*V7R2-DT增加CA L2吞吐量上报结构体定义的代码 q00208938 2014/03/24，end*/

/*****************************************************************************
 结构名    : L2_LAYER_SDU_COUNT_STAT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :L2各层上/下行SDU个数统计信息的结构。用于数传可维可测监控
*****************************************************************************/
typedef struct
{
    VOS_UINT32                 ulReceivedCnt;           /*上行接收的SDU数目PC侧->空口*/
    VOS_UINT32                 ulReceivedLength;        /*上行接收的SDU累加长度 单位:字节*/
    VOS_UINT32                 ulDiscardedCnt;          /*上行丢弃的SDU数目*/
    VOS_UINT32                 ulTransmittedCnt;        /*下行发送的SDU数目*/
    VOS_UINT32                 ulTransmittedLength;     /*下行发送的SDU累加长度 单位:字节*/
} L2_LAYER_SDU_COUNT_STAT_STRU;


/*****************************************************************************
 结构名    : LPS_RLC_MODE_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
enum LPS_RLC_MODE_ENUM
{
    LPS_RLC_MODE_AM                         = 0,                                    /* AM */
    LPS_RLC_MODE_UM                         = 1,                                    /* UM */
    LPS_RLC_MODE_TM                         = 2,                                    /* TM */
    LPS_RLC_MODE_BUTT
};
typedef VOS_UINT8 LPS_RLC_MODE_ENUM_UINT8;

/*****************************************************************************
 结构名    : L2_DRB_SDU_COUNT_STAT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :L2各DRB上/下行SDU个数统计信息的结构。用于数传可维可测监控
*****************************************************************************/
typedef struct
{
    VOS_UINT8                  ucRbId;                 /*RB ID*/
    LPS_RLC_MODE_ENUM_UINT8    ucRlcMode;              /*RLC模式*/
    VOS_UINT8                  aucRed[2];              /*保留*/
    VOS_UINT32                 ulTxHfn;                /*UL TX HFN*/
    VOS_UINT32                 ulRxHfn;                /*DL RX HFN*/
    VOS_UINT32                 ulReceivedCnt;          /*上行接收的SDU数目*/
    VOS_UINT32                 ulReceivedLength;       /*上行接收的SDU累加长度*/
    VOS_UINT32                 ulDiscardedCnt;        /*上行丢弃的SDU数目*/
    VOS_UINT32                 ulTransmittedCnt;       /*下行发送的SDU数目*/
    VOS_UINT32                 ulTransmittedLength;    /*下行发送的SDU累加长度*/
} L2_DRB_SDU_COUNT_STAT_STRU;


/*****************************************************************************
 结构名    : L2_OM_SDU_STAT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :L2向MSP周期上报SDU可维可测结果的信息结构。 只用于数传可维可测监控
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      ulTimeStamp;         /*时间戳，通过PS_GET_TICK()获得*/
    VOS_UINT16                                      usFrame;             /*帧号*/
    VOS_UINT16                                      usSubFrame;          /*子帧号*/
    VOS_UINT32                                      ulRptPeriod;         /*上报周期*/
    L2_LAYER_SDU_COUNT_STAT_STRU                    stUsbSduCountInfo[NCM_DEVICE_NUM];   /*USB SDU的统计信息*/
    L2_LAYER_SDU_COUNT_STAT_STRU                    stIpSduCountInfo;    /*IP SDU的统计信息*/
    L2_LAYER_SDU_COUNT_STAT_STRU                    stRabmSduCountInfo;  /*RABM SDU的统计信息*/
    L2_LAYER_SDU_COUNT_STAT_STRU                    stPdcpSduCountInfo;  /*PDCP SDU的统计信息*/
    L2_LAYER_SDU_COUNT_STAT_STRU                    stRlcSduCountInfo;   /*RLC SDU的统计信息*/
    L2_LAYER_SDU_COUNT_STAT_STRU                    stMacSduCountInfo;   /*MAC SDU的统计信息*/
    L2_LAYER_SDU_COUNT_STAT_STRU                    stPhySduCountInfo;   /*PHY SDU的统计信息*/
    L2_DRB_SDU_COUNT_STAT_STRU                      stDrbSduCountInfo[PS_OM_MAX_DRB_NUM];/*DRB上下行收到的流量统计信息*/
} L2_OM_SDU_STAT_IND_STRU;

/*****************************************************************************
 结构名    : L1_THROUGHPUT_PROCESS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :L1UL/DL动态处理结果结构。 只用于L2内部的流量统计
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      ulSinr[L2_THR_STAT_MAX_NUM];               /*SINR*/
    VOS_UINT32                                      ulL1ThruputRight[L2_THR_STAT_MAX_NUM];     /*下行速率*/
    VOS_UINT32                                      ulL1ThruputTotal[L2_THR_STAT_MAX_NUM];     /*下行速率*/
} L1_THROUGHPUT_PROC_ULDL_STRU;

/*****************************************************************************
 结构名    : L2_THROUGHPUT_PROCESS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :L2各层UL/DL动态处理结果结构。 同时用于数传可维可测监控和L2内部的流量统计，数传可维可测监控每次只上报一个点
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      ulUlRate[L2_THR_STAT_MAX_NUM];     /*上行速率*/
    VOS_UINT32                                      ulDlRate[L2_THR_STAT_MAX_NUM];     /*下行速率*/
} L2_THROUGHPUT_PROC_ULDL_STRU;

/*****************************************************************************
 结构名    : L2_THROUGHPUT_PROCESS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :L2各层UL/DL动态统计信息结构。 同时用于数传可维可测监控和L2内部的流量统计
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      ulPreUlTotalLen;                   /*上一次统计上行发送的总字节数据*/
    VOS_UINT32                                      ulCurUlTotalLen;                   /*当前统计上行发送的总字节数据*/
    VOS_UINT32                                      ulPreDlTotalLen;                   /*上一次统计下行接收的总字节数据*/
    VOS_UINT32                                      ulCurDlTotalLen;                   /*当前统计下行接收的总字节数据*/
    L2_THROUGHPUT_PROC_ULDL_STRU                    stUlDlInfo;                        /*各层动态处理结果*/
} L2_THROUGHPUT_PROC_INFO_STRU;


/*****************************************************************************
 结构名    : L2_DRB_THROUGHPUT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :L2本地用于记录DRB UL/DL动态统计信息结构。
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                       ucRbId;                            /*DRB ID*/
    VOS_UINT8                                       ucValid;                           /*统计有效标志位.1-有效,0-无效*/
    VOS_UINT8                                       aucRsv[2];
    VOS_UINT32                                      ulPreUlTotalLen;                   /*上一次统计上行发送的总字节数据*/
    VOS_UINT32                                      ulCurUlTotalLen;                   /*当前统计上行发送的总字节数据*/
    VOS_UINT32                                      ulPreDlTotalLen;                   /*上一次统计下行接收的总字节数据*/
    VOS_UINT32                                      ulCurDlTotalLen;                   /*当前统计下行接收的总字节数据*/
    L2_THROUGHPUT_PROC_ULDL_STRU                    stUlDlInfo;                        /*各层动态处理结果*/
} L2_DRB_THROUGHPUT_INFO_STRU;


/*****************************************************************************
 结构名    : L2_DRB_THROUGHPUT_PROC_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :DRB 动态统计信息结构。
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRbNum;                           /*有效的RB 个数*/
    VOS_UINT8                           aucRsv[3];
    L2_DRB_THROUGHPUT_INFO_STRU         stDrbThoughtputInfo[PS_OM_MAX_DRB_NUM]; /*各个DRB吞吐量动态统计信息*/

} L2_DRB_THROUGHPUT_PROC_INFO_STRU;

/*****************************************************************************
 结构名    : L2_THROUGHPUT_PROCESS_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :L2各层流量统计全局信息结构。 同时用于数传可维可测监控和L2内部的流量统计
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                       ulStatFlag;            /*流量统计开始/停止标志*/
    VOS_UINT32                                       ulThrMomStatFlag;      /*1:开启数传可维可测监控，则停止L2内部流量统计； 0: 停止数传可维可测监控，则可进行L2内部流量统计*/
    VOS_UINT32                                       ulStatPeriod;          /*统计周期，单位: ms，最小步长: */
    VOS_UINT32                                       ulRptPeriod;           /*上报周期，单位: ms，最小步长: */
    VOS_UINT32                                       ulCurStatTime;         /*当前统计的时间*/
    VOS_UINT32                                       ulPreStatTime;         /*上一次统计的时间*/
    VOS_UINT32                                       ulCurRptTime;          /*当前上报的时间*/
    VOS_UINT32                                       ulPreRptTime;          /*上一次上报的时间*/
    VOS_UINT32                                       ulValidStatNum;         /*已统计的有效点数。 数传可维可测监控时一次上报只统计一个点*/
    VOS_UINT32                                       ulTimeStamp[L2_THR_STAT_MAX_NUM];        /*时间戳，通过PS_GET_TICK()获得*/
    VOS_UINT16                                       usFrame[L2_THR_STAT_MAX_NUM];            /*帧号*/
    VOS_UINT16                                       usSubFrame[L2_THR_STAT_MAX_NUM];         /*子帧号*/
    L2_THROUGHPUT_PROC_INFO_STRU                     stAppThoughputInfo;    /*APP层统计信息*/
    L2_THROUGHPUT_PROC_INFO_STRU                     stPdcpThoughputInfo;   /*PDCP动态统计信息*/
    L2_THROUGHPUT_PROC_INFO_STRU                     stRlcThoughputInfo;    /*RLC动态统计信息*/
    L2_THROUGHPUT_PROC_INFO_STRU                     stMacThoughputInfo;    /*MAC动态统计信息*/
    L2_DRB_THROUGHPUT_PROC_INFO_STRU                 stL2DrbThoughputInfo;  /*各个DRB动态统计信息*/

    /*V7R2-DT增加CA SCell MAC下行吞吐量结构体的代码 q00208938 2014/03/24，begin*/
    L2_THROUGHPUT_PROC_INFO_STRU astMacCaThroughputInfo[CA_MAX_CELL_NUM];  /*CA MAC动态统计信息*/
    /*V7R2-DT增加CA SCell MAC下行吞吐量结构体的代码 q00208938 2014/03/24，end*/
} L2_THROUGHPUT_PROC_STAT_INFO_STRU;
/*****************************************************************************
 结构名    : L2_DRB_LOCAL_SDU_COUNT_STAT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :本地保存的L2各DRB上/下行SDU个数统计信息结构。用于数传可维可测监控
*****************************************************************************/
typedef struct
{
    VOS_UINT8                  ucRbId;                 /*RB ID*/
    VOS_UINT8                  ucValid;                /*统计有效标志位  1-信息有效,0-无效*/
    LPS_RLC_MODE_ENUM_UINT8    ucRlcMode;              /*RLC模式*/
    VOS_UINT8                  ucRsvd;                 /*保留*/
    VOS_UINT32                 ulTxHfn;                /*UL TX HFN*/
    VOS_UINT32                 ulRxHfn;                /*DL RX HFN*/
    VOS_UINT32                 ulReceivedCnt;          /*上行接收的SDU数目*/
    VOS_UINT32                 ulReceivedLength;       /*上行接收的SDU累加长度*/
    VOS_UINT32                 ulDiscardedCnt;        /*上行丢弃的SDU数目*/
    VOS_UINT32                 ulTransmittedCnt;       /*下行发送的SDU数目*/
    VOS_UINT32                 ulTransmittedLength;    /*下行发送的SDU累加长度*/
} L2_DRB_LOCAL_SDU_COUNT_STAT_STRU;


/*****************************************************************************
 结构名    : L2_DRB_SDU_COUNT_STAT_PROC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :本地用于L2各DRB SDU数目统计全局信息结构。
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRbNum;                           /*有效的RB 个数*/
    VOS_UINT8                           aucRsv[3];
    L2_DRB_LOCAL_SDU_COUNT_STAT_STRU    stDrbSduCountInfo[PS_OM_MAX_DRB_NUM];/*DRB上下行收到的流量统计信息*/
}L2_DRB_SDU_COUNT_STAT_PROC_STRU;


/*****************************************************************************
 结构名    : L2_SDUCNT_PROC_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :本地用于L2各层 SDU数目统计全局信息结构。
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                       ulStatFlag;            /*SDU数目统计开始/停止标志*/
    VOS_UINT32                                       ulStatPeriod;          /*统计周期，单位: ms，最小步长: 此处无用*/
    VOS_UINT32                                       ulRptPeriod;           /*上报周期，单位: ms，最小步长: */
    VOS_UINT32                                       ulCurStatTime;         /*当前统计的时间*/
    VOS_UINT32                                       ulPreStatTime;         /*上一次统计的时间*/
    VOS_UINT32                                       ulCurRptTime;          /*当前上报的时间*/
    VOS_UINT32                                       ulPreRptTime;          /*上一次上报的时间*/
    VOS_UINT32                                       ulValidStatNum;         /*已统计的有效点数。 数传可维可测监控时一次上报只统计一个点*/
    VOS_UINT32                                       ulTimeStamp[L2_THR_STAT_MAX_NUM];        /*时间戳，通过PS_GET_TICK()获得*/
    VOS_UINT16                                       usFrame[L2_THR_STAT_MAX_NUM];            /*帧号*/
    VOS_UINT16                                       usSubFrame[L2_THR_STAT_MAX_NUM];         /*子帧号*/
    L2_LAYER_SDU_COUNT_STAT_STRU               stUsbSduCountInfo;     /*USB SDU的统计信息*/
    L2_LAYER_SDU_COUNT_STAT_STRU               stIpSduCountInfo;      /*IP SDU的统计信息*/
    L2_LAYER_SDU_COUNT_STAT_STRU               stRabmSduCountInfo;    /*RABM SDU的统计信息*/
    L2_LAYER_SDU_COUNT_STAT_STRU               stPdcpSduCountInfo;    /*PDCP SDU的统计信息*/
    L2_LAYER_SDU_COUNT_STAT_STRU               stRlcSduCountInfo;     /*RLC SDU的统计信息*/
    L2_LAYER_SDU_COUNT_STAT_STRU               stMacSduCountInfo;     /*MAC SDU的统计信息*/
    L2_LAYER_SDU_COUNT_STAT_STRU               stPhySduCountInfo;     /*PHY SDU的统计信息*/
    L2_DRB_SDU_COUNT_STAT_PROC_STRU                  stDrbSduCntProcInfo;   /*DRB SDU的统计信息*/

} L2_SDUCNT_PROC_STAT_INFO_STRU;

/*****************************************************************************
 结构名    : LUP_APPSTATSTRU_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 统计信息结构
*****************************************************************************/
typedef struct LUP_APPSTAT
{
    VOS_UINT32    ulMemTransFailNum;
    VOS_UINT32    ulAppRxIpPktCnt;
    VOS_UINT32    ulAppRxIpPktLen;
    VOS_UINT32    ulEnAppReqQueSucc;
    VOS_UINT32    ulEnAppReqQueFail;
    VOS_UINT32    ulDeAppReqQueSucc;
    VOS_UINT32    ulRelAppReqQueNum;

}LUP_APPSTATSTRU_STRU;


/*DCM logger*/
/*****************************************************************************
 结构名    : MAC_BSR_SUBHDR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC BSR 子头信息上报
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucValidFlag;     /*1-BSR 控制元有效*/
    VOS_UINT8    ucBsrType;      /*0-short bsr;1-truncated bsr;2-long bsr*/
    VOS_UINT8    ucBufferSize0;
    VOS_UINT8    ucBufferSize1;
    VOS_UINT8    ucBufferSize2;
    VOS_UINT8    ucBufferSize3;
    VOS_UINT16   usRsv;
}MAC_BSR_SUBHDR_STRU;

/*****************************************************************************
 结构名    : MAC_PHR_SUBHDR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC PHR 子头信息上报
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucValidFlag;     /*1-PHR 控制元有效*/
    VOS_UINT8    ucPhrType;      /*0-PHR;1-Extend PHR*/
    VOS_UINT8    ucRsv[2];
}MAC_PHR_SUBHDR_STRU;

/*****************************************************************************
 结构名    : MAC_PADDING_SUBHDR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC PADDING 子头信息上报
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucValidFlag;     /*1-有padding 内容*/
    VOS_UINT8    ucRsv[3];
}MAC_PADDING_SUBHDR_STRU;


/*****************************************************************************
 结构名    : MAC_CRNTI_SUBHDR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC CRNTI 子头信息上报
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucValidFlag;     /*1-CRNTI 控制元有效*/
    VOS_UINT8    ucRsv;
    VOS_UINT16   usCRnti;
}MAC_CRNTI_SUBHDR_STRU;

/*****************************************************************************
 结构名    : MAC_SDU_DATA_HEADER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC SDU 子头信息上报
*****************************************************************************/
typedef struct
{
    VOS_UINT8     ucData[9];      /*SDU前9个字节*/
    VOS_UINT8     ucLchId;     /*逻辑信道ID*/
    VOS_UINT16    usSduLen;
}MAC_SDU_DATA_HEADER_STRU;


/*****************************************************************************
 结构名    : MAC_SDU_DATA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC SDU信息上报
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucValidFlag;
    VOS_UINT8    ucSduNum;
    VOS_UINT8    ucRsv[2];
    MAC_SDU_DATA_HEADER_STRU   stMacSduData[3]; /*只保存3个SDU*/
}MAC_SDU_DATA_STRU;


/*****************************************************************************
 结构名    : L2_MAC_UL_HEADER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC PUSCH 子头信息上报
*****************************************************************************/
typedef struct
{
    MAC_BSR_SUBHDR_STRU         stMacBsrInfo;
    MAC_PHR_SUBHDR_STRU         stMacPhrInfo;
    MAC_CRNTI_SUBHDR_STRU       stMacCrntiInfo;
    MAC_SDU_DATA_STRU           stMacSduInfo;
}L2_MAC_UL_HEADER_STRU;

/*****************************************************************************
 结构名    : MAC_CA_SUBHDR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC CA 子头信息上报
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucValidFlag;     /*1-CA控制元有效*/
    VOS_UINT8    ucSCellStatus;      /*bit 1-7 为1,则说明对应的SCell 激活；bit 0 为reserved*/
    VOS_UINT8    ucRsv[2];
}MAC_CA_SUBHDR_STRU;

/*****************************************************************************
 结构名    : MAC_CRI_SUBHDR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC CRI 子头信息上报
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucValidFlag;     /*1-竞争解决标识 控制元有效*/
    VOS_UINT8    ucCRI[6];      /*竞争解决indentity*/
    VOS_UINT8    ucRsv;
}MAC_CRI_SUBHDR_STRU;

/*****************************************************************************
 结构名    : MAC_TA_SUBHDR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC TA 子头信息上报
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucValidFlag;     /*1-TA 控制元有效*/
    VOS_UINT8    ucTaValue;
    VOS_UINT8    ucRsv[2];
}MAC_TA_SUBHDR_STRU;

/*****************************************************************************
 结构名    : MAC_DRX_SUBHDR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC DRX 子头信息上报
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucValidFlag;     /*1-DRX 控制元有效*/
    VOS_UINT8    ucRsv[3];
}MAC_DRX_SUBHDR_STRU;


/*****************************************************************************
 结构名    : L2_MAC_DL_HEADER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC PDSCH 子头信息上报
*****************************************************************************/
typedef struct
{
    MAC_CA_SUBHDR_STRU         stMacCaInfo;
    MAC_TA_SUBHDR_STRU         stMacTaInfo;
    MAC_CRI_SUBHDR_STRU        stMacCriInfo;
    MAC_DRX_SUBHDR_STRU        stMacDrxInfo;
    MAC_SDU_DATA_STRU          stMacSduInfo;
}L2_MAC_DL_HEADER_STRU;

/*****************************************************************************
 结构名    : L2_MAC_DL_HEADER_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT32                enMsgName;                    /* 消息类型 */      /* _H2ASN_Skip */
    L2_MAC_DL_HEADER_STRU         stMacDlData;
}L2_MAC_DL_HEADER_INFO_STRU;

/*****************************************************************************
 结构名    : L2_MAC_UL_HEADER_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT32                enMsgName;                    /* 消息类型 */      /* _H2ASN_Skip */
    L2_MAC_UL_HEADER_STRU         stMacUlData;

}L2_MAC_UL_HEADER_INFO_STRU;

/*****************************************************************************
 结构名    :L2_DCM_CA_CTRL_ELEMENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  SCELL MAC CE上报结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                    /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT32                          enMsgName;                    /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usSCellCtrlRevSFN;
    VOS_UINT16                          usSCellCtrlRevSubSFN;
    L2_DCM_SCELL_STATUS_ENUM_UINT8      aucScellIndex[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];
}L2_DCM_CA_CTRL_ELEMENT_STRU;

extern L2_MAC_DL_HEADER_STRU  g_stL2MacDlHdrInfo;
extern L2_MAC_UL_HEADER_STRU  g_stL2MacUlHdrInfo;
/*end DCM*/

extern LUP_APPSTATSTRU_STRU     g_stLupAppStat;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_UINT32 UP_InitAppItf( VOS_VOID);

/*****************************************************************************
  9 OTHERS
*****************************************************************************/

/*仅用于测试*/
#if (VOS_OS_VER == VOS_WIN32)

extern LUP_QUEUE_STRU  *g_pstAppDataIndQue;     /*App数据:PS->APP*/

extern VOS_UINT32 LUP_DataIndQueInit(void);
extern VOS_UINT32 APPITF_SndDataReq(LUP_MEM_ST *pData, VOS_UINT32 ulLen);
extern VOS_VOID   APPITF_RcvDataReq(void);
extern LUP_MEM_ST * APPITF_AllocMem(VOS_UINT32 ulSize);
extern VOS_UINT32 APPITF_FreeMem(LUP_MEM_ST *pMem);
extern VOS_UINT32 APPITF_RcvDataInd(VOS_UINT8 *pBuff, VOS_UINT32 *pulLen);
extern VOS_UINT32 APPITF_SndDataInd(LUP_MEM_ST *pData);

extern VOS_VOID APPITF_RcvDataReq_Stub(void);
VOS_UINT32 STUB_DriverSendAppDataToPs(VOS_UINT32 ulRbId, VOS_UINT16 usLen);
VOS_UINT32 STUB_DriverRcvAppDataFromPs(void);
#endif

extern LUP_QUEUE_STRU  *g_pstAppDataReqQue;     /*App数据:APP->PS*/
extern VOS_UINT32 LUP_DataReqQueInit(void);
extern VOS_VOID LUP_RcvDataReq(void);
extern VOS_VOID LUP_RelDataReq(VOS_VOID);


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of LUPAppItf.h */


