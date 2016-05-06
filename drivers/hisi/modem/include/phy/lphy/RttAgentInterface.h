/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : RttAgentInterface.h
  版 本 号   : 初稿
  作    者   : x00312156
  生成日期   : 2015年1月27日
  最近修改   :
  功能描述   : 定义RTT AGENT和其他模块的接口，包括与A核Errlog
  的接口，与TLPHY的接口

  函数列表   :
  修改历史   :
------------------------------------------------------------------------------
  1.日    期   : 	2015年1月27日
    作    者   : 	x00312156
    修改内容   : 	创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __RTTAGENT_INTERFACE_H__
#define __RTTAGENT_INTERFACE_H__


#ifndef LPS_RTT
#include "vos.h"
#else
#ifndef __DSP_PCLINT__
#define VOS_MSG_HEADER
#endif
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define ERRLOG_STATUS_CLOSE   ( 0 )
#define ERRLOG_STATUS_OPEN    ( 1 )

#define TLPHY_ERR_LOG_CTRL_LEVEL_NULL         ( 0 )   /* ErrLog等级未定义*/
#define TLPHY_ERR_LOG_CTRL_LEVEL_CRITICAL     ( 1 )   /* ErrLog等级为紧急 */
#define TLPHY_ERR_LOG_CTRL_LEVEL_MAJOR        ( 2 )   /* ErrLog等级为重要 */
#define TLPHY_ERR_LOG_CTRL_LEVEL_MINOR        ( 3 )   /* ErrLog等级为次要 */
#define TLPHY_ERR_LOG_CTRL_LEVEL_WARNING      ( 4 )   /* ErrLog等级为提示 */

#define TLPHY_OM_SEND_MSG_COUNT               ( 3 )   /*TLPHY每次申请重传OM消息的条数*/
#define TLPHY_OM_SEND_CONTENT_LENGTH_IN_16BIT ( 2 )   /*TLPHY重传OM消息信息长度*/
#define TLPHY_RTTAGENT_MSG_HEADLEN_IN_8BIT    ( 8 )   /* enMsgType+ulMsgLen 的字节长度*/

#define TLPHY_RTTAGENT_AFCLOCK_STATUS_INFO_LENGTH_IN_16BIT  (2)       /*TLPHY发送给RTT AGENT的AFC锁定状态消息长度*/
#define TLPHY_AGENT_RFICSSI_IND_LENGTH_IN_16BIT             (2)       /*TLPHY上报给AGENT的RFIC寄存器配置值消息长度*/
#define UNLIMITED_COUNT_REPORT                              (65535)   /*上报次数为无限次*/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32
 枚举说明  : TLPHY和RTT代理之间的消息类型
*****************************************************************************/
enum RTTAGENT_TLPHY_MSGTYPE_ENUM
{
    /* MBX 发送给AGENT的消息类型 */
    MBX_TO_RTTAGENT_REQ = 0,
    /* TPHY发送给代理的消息类型 */
    TPHY_AGENT_ERRLOG_REQ,                    /* TPHY上报MAS CHR非连接态请求 */
    TPHY_AGENT_STORE_OM_REQ,                  /* TPHY上报OM缓存请求 */
    TPHY_AGENT_SEND_OM_REQ,                   /* TPHY上报OM重传请求 */
    TPHY_MAS_CHR_CONN_REQ,                    /* TPHY上报MAS CHR连接态请求 */

    /* LPHY发送给代理的消息类型 */
    LPHY_AGENT_ERRLOG_REQ = 32,               /* LPHY上报MAS CHR非连接态请求 */
    LPHY_AGENT_STORE_OM_REQ,                  /* LPHY上报OM缓存请求 */
    LPHY_AGENT_SEND_OM_REQ,                   /* LPHY上报OM重传请求 */	
    LPHY_AGENT_PAGING_CRC_INFO,               /* LPHY上报PAGING CRC信息 */
    LPHY_MAS_CHR_CONN_REQ,                    /* LPHY上报MAS CHR连接态请求 */        

    /*TLPHY 发送给代理的消息类型*/
	TLPHY_AGENT_SEND_AFCLOCK_STATUS_INFO_CNF = 56,     /* TLPHY上报AFC锁定状态请求*/
	TLPHY_AGENT_TXRX_PARA_INFO,                           /* TLPHY上报TX PWR信息 */
	TLPHY_AGENT_RFICSSI_IND,                           /* TLPHY上报RFIC寄存器配置值 */
	TLPHY_AGENT_REPORT_ERROR_INFO,

    /* 以下是RTT AGENT发送给TLPHY的消息类型 */
    AGENT_TO_TLPHY_INFO_START = 63,

    AGENT_TLPHY_ERRLOG_CTRL_INFO,             /* 代理发送给TLPHY 的ERRLOG配置 */
    /* 代理发送给TPHY 的消息类型 */
    AGENT_TPHY_SEND_OM_CNF,                   /* TPHY OM消息重传确认 */

    /* 代理发送给LPHY 的消息类型 */
    AGENT_LPHY_SEND_OM_CNF,                   /* LPHY OM消息重传确认 */

	AGENT_TLPHY_AFC_STATUS_REQ,                /* 代理发送给物理层的AFC锁定状态上报请求*/
	AGENT_TLPHY_TXRX_PARA_INFO_REQ,             /* 代理发送给TLPHY的上行Tx Power信息查询请求*/
	AGENT_TLPHY_RFICSSIRD_REQ,                /*AGENT发送给TLPHY的RFIC寄存器配置值查询请求*/

    /* 装备融合 */
    TLPHY_TO_EQUIP_NOTIFY,                    /* AGENT -> AGENT */

    AGENT_TLPHY_MSG_BUTT
};
typedef VOS_UINT32 RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32;

/*****************************************************************************
枚举名    : TLPHY_MTA_AFCLOCK_STATUS_ENUM
枚举说明  : GPS 参考时钟频率锁定状态枚举
*****************************************************************************/
enum TLPHY_MTA_AFCLOCK_STATUS_ENUM
{
    TLPHY_MTA_AFCLOCK_UNLOCKED = 0,    /*GPS 参考时钟频率非锁定状态*/
    TLPHY_MTA_AFCLOCK_LOCKED,          /*GPS 参考时钟频率锁定状态*/
    TLPHY_MTA_AFCLOCK_STATUS_BUTT
};
typedef VOS_UINT16 TLPHY_MTA_AFCLOCK_STATUS_ENUM_UINT16;

/*****************************************************************************
枚举名    : RTTAGENT_AFCLOCK_STATUS_REPORT_CONTROL_FLAG_ENUM
枚举说明  : AFC 锁定状态上报控制枚举
*****************************************************************************/
enum RTTAGENT_AFCLOCK_STATUS_REPORT_CONTROL_FLAG_ENUM
{
    RTTAGENT_STOP_REPORT_CONTROL_FLAG = 0,    /* 停止上报控制标记 */
    RTTAGENT_ALLOW_REPORT_CONTROL_FLAG,       /* 允许上报控制标记 */
    RTTAGENT_REPORT_CONTROL_FLAG_BUTT
};
typedef VOS_UINT16 RTTAGENT_AFCLOCK_STATUS_REPORT_CONTROL_FLAG_ENUM_UINT16;
/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/

/*****************************************************************************
 结构名    : TPHY_ERRLOG_TAS_INFO_STRU
 结构说明  :TPHY和A核Errlog之间的接口数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32         ulAntSwitchSlice;     /* TAS切换的时间戳 */
    VOS_UINT16         usDpdtState;          /* 切换后的DPDT状态，0直通，1交叉 */
    VOS_INT16          ssAntValuemain;       /* 切换后的主集天线接收信号测量值 */
    VOS_INT16          ssSwitchDelta;        /* 主辅天线测量值Delta */
    VOS_UINT16         usBlankType;          /* 切换时的状态 */
    VOS_UINT16         usTsEn;               /* 是否有TAS授权，0无授权，1有授权 */
    VOS_UINT16         usAgentSwitchFlag;    /* 是否为代理切换，0非代理切，1代理切 */
    VOS_UINT16         usTasState;           /* 切换时的TAS状态，HAPPY/UNHAPPY 等 */
    VOS_UINT16         usReserve;            /* 预留，保持四字节对齐 */
}TPHY_ERRLOG_TAS_INFO_STRU;

/*****************************************************************************
 结构名    : LPHY_ERRLOG_TAS_INFO_STRU
 结构说明  :LPHY和A核Errlog之间的接口数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32         ulAntSwitchSlice;      /* TAS切换的时间戳 */
    VOS_UINT16         usDpdtState;           /* 切换后的DPDT状态，0直通，1交叉 */
    VOS_INT16          ssAntValuemain;        /* 切换后的主集天线接收信号测量值 */
    VOS_INT16          ssSwitchDelta;         /* 主辅天线测量值Delta */
    VOS_UINT16         usBlankType;           /* 切换时的状态 */
    VOS_UINT16         usTsEn;                /* 是否有TAS授权，0无授权，1有授权 */
    VOS_UINT16         usAgentSwitchFlag;     /* 是否为代理切换，0非代理切，1代理切 */
    VOS_UINT16         usTasState;            /* 切换时的TAS状态，HAPPY/UNHAPPY 等 */
    VOS_UINT16         usReserve;             /* 预留，保持四字节对齐 */
}LPHY_ERRLOG_TAS_INFO_STRU;

typedef struct
{
    VOS_UINT8                ucConnDpdtState;       /* 切换后的DPDT状态，
                                                                                        0 : TAS直通/MAS直通,
                                                                                        1 : TAS交叉/MAS直通,
                                                                                        2 : TAS直通/MAS交叉,
                                                                                        3 : TAS交叉/MAS交叉,*/
    VOS_INT8                 ucConnDpdtAlgo;       /* 连接态明切、盲切算法， 0 : 明切 , 1 : 盲切 */
    VOS_INT8                 ucConnMasState;       /* 连接态MAS算法阶段
                                                                                        LTE_ASU_STATE_STABLE   = 0,0 稳态，处于满足GOOD门限阶段
                                                                                        LTE_ASU_STATE_TAS  1
                                                                                        LTE_ASU_STATE_MAS  2
                                                                                        LTE_ASU_STATE_XTAS 3
                                                                                        LTE_ASU_STATE_HYST 4     处于冻结态，此阶段算法不能运行*/
    VOS_UINT8                ucCompareAnt;         /*  1st byte: current use,  2nd byte: Target compare
                                                                                           (ex: 0x23 = Current:Ant2, Compare:Ant3)*/
}TLPHY_MAS_CONNECTED_STATE_INFO_STRU;

typedef struct
{
    VOS_UINT32                ulSwitchSlice;         /*  切换时间戳 */
    VOS_UINT16                usSwitchDirection;     /* 切换天线方向
                                                                                             1st byte: Source,  2nd byte: Target
                                                                                              (ex: 0x23 = 从ant2切到ant3)    */
    VOS_INT16                 ssSwitchBefSignal;     /* 切换前接收RSCP/RSRP*/
    VOS_INT16                 ssSwitchAftSignal;     /* 切换后接收RSCP/RSRP*/
    VOS_INT16                 ssSwitchBefTxPower;    /* 切换前发射功率  */
    VOS_INT16                 ssSwitchAftTxPower;    /* 切换后发射功率  */
    VOS_UINT16                usReserve;            /* 预留，保持四字节对齐 */
}TLPHY_MAS_SWITCH_STATE_INFO_STRU;

typedef struct
{
    TLPHY_MAS_SWITCH_STATE_INFO_STRU stWholeSwitchState;    /* 整轮切换 */
    TLPHY_MAS_SWITCH_STATE_INFO_STRU stSignalSwitchState;    /* 单次切换 */
    VOS_UINT16                       usBand;                /* 切换的频段 */
    VOS_UINT16                       usSwitchRoundCnt;      /* 切换比较次数
                                                                                                    1st byte: Round#,  2nd byte: Count#
                                                                                                    (ex: 0x23 = Round2 Count3)*/

}TLPHY_MAS_CONNECTED_DPDT_INFO_STRU;

typedef struct
{
    VOS_UINT32                ulCompareSlice;       /* 比较阶段的时间戳 */
    VOS_UINT16                usCompareBand;        /* 比较阶段的频段 */
    VOS_INT16                 ssCompareAnt0Signal;  /* 比较阶段天线0接收RSCP/RSRP*/
    VOS_INT16                 ssCompareAnt1Signal;  /* 比较阶段天线1接收RSCP/RSRP*/
    VOS_INT16                 ssCompareAnt2Signal;  /* 比较阶段天线2接收RSCP/RSRP*/
    VOS_INT16                 ssCompareAnt3Signal;  /* 比较阶段天线3接收RSCP/RSRP*/
    VOS_UINT16                usReserve;            /* 预留，保持四字节对齐 */
}TLPHY_MAS_CONNECTED_COMPARE_INFO_STRU;

typedef struct
{
    VOS_UINT8                 ucNonConnDpdtStatus; /* 切换后的DPDT状态，
                                                                                       0 : TAS直通/MAS直通,
                                                                                       1 : TAS交叉/MAS直通,
                                                                                       2 : TAS直通/MAS交叉,
                                                                                       3 : TAS交叉/MAS交叉,*/
    VOS_UINT8                 ucNonConnMasAlgo;    /* 非连接态的状态 , 1: Searching ,  2: Access, 3 : Idle */
    VOS_UINT8                 ucAgentFlag;         /* 代理是否生效 */
    VOS_UINT8                 ucIdleSwitchStaus;   /*idle 切换后是否是happy状态，0 : Fail , 1 : Success*/
}TLPHY_MAS_NONCONN_STATE_INFO_STRU;

typedef struct
{
    VOS_UINT8                 ucMasAuthorizeFlag;  /*Mas的授权状态                                                   
                                                                                      0 : TAS无/MAS无,
                                                                                     1 : TAS有/MAS无,
                                                                                     2 : TAS无/MAS有,
                                                                                     3 : TAS有/MAS有,*/
    VOS_UINT8                 ucIdleHappyState; /*  TAS_REPORT_STATE_IDLE_UNHAPPY = 0,
                                                                                     TAS_REPORT_STATE_IDLE_HAPPY   = 1, */
    VOS_UINT8                 ucSignalState;    /* 
                                                                                     TAS_REPORT_STATE_IDLE_POOR = 0,
                                                                                     TAS_REPORT_STATE_IDLE_GOOD = 1,
                                                                                     TAS_REPORT_STATE_CONN_POOR = 0, 
                                                                                     TAS_REPORT_STATE_CONN_GOOD = 1 */
    VOS_UINT8                 ucRsv;                 
}TLPHY_MAS_Current_STATE_INFO_STRU;

typedef struct
{
    TLPHY_MAS_NONCONN_STATE_INFO_STRU           stMasNonConnState;
    TLPHY_MAS_Current_STATE_INFO_STRU           stMasCurrentState;
    TLPHY_MAS_CONNECTED_STATE_INFO_STRU         stMasConnState;
    TLPHY_MAS_CONNECTED_DPDT_INFO_STRU          stMasConnDpdt;
    TLPHY_MAS_CONNECTED_COMPARE_INFO_STRU       stMasConnCompare;
    VOS_UINT16                                  usRlfAuthorizeFlag;
    VOS_UINT16                                  usRsv;
}TLPHY_ERRLOG_MAS_INFO_STRU;

typedef struct
{
    TLPHY_MAS_Current_STATE_INFO_STRU           stMasCurrentState;
    TLPHY_MAS_CONNECTED_STATE_INFO_STRU         stMasConnState;
    TLPHY_MAS_CONNECTED_DPDT_INFO_STRU          stMasConnDpdt;
    TLPHY_MAS_CONNECTED_COMPARE_INFO_STRU       stMasConnCompare;
    VOS_UINT16                                  usRlfAuthorizeFlag;
    VOS_UINT16                                  usRsv;
}TLPHY_CONN_MAS_INFO_STRU;

typedef struct
{
    TLPHY_MAS_NONCONN_STATE_INFO_STRU           stMasNonConnState;
    TLPHY_MAS_Current_STATE_INFO_STRU           stMasCurrentState;
}TLPHY_NONCONN_MAS_INFO_STRU;

/*****************************************************************************
 结构名    : RTTAGENT_TLPHY_MSG_STRU
 结构说明  :RTT AGENT和TLPHY的接口消息结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32    enMsgType;       /* 消息类型 */
    VOS_UINT32                            ulMsgLen;        /* 消息长度acuContent的实际字长度 */
    VOS_UINT8                             aucContent[4];   /* 消息内容 */
}RTTAGENT_TLPHY_MSG_STRU;

/*****************************************************************************
 结构名    : TPHY_AGENT_ERRLOG_REQ_STRU
 结构说明  :RTT AGENT和TPHY的天线切换非连接态关键消息结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32    enMsgType;        /* 消息类型为TPHY_AGENT_ERRLOG_REQ */
    VOS_UINT32                            ulMsgLen;         /* 消息长度为sizeof(PHY_ERRLOG_TPHY_TAS_INFO_STRU) /2*/
    TLPHY_NONCONN_MAS_INFO_STRU           stTphyMasInfo;    /* TPHY天线切换关键信息 */
}TPHY_AGENT_ERRLOG_REQ_STRU;

/*****************************************************************************
 结构名    : TPHY_MAS_CHR_CONN_REQ_STRU
 结构说明  :RTT AGENT和TPHY的天线切换连接态关键消息结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32    enMsgType;        /* 消息类型为TPHY_AGENT_ERRLOG_REQ */
    VOS_UINT32                            ulMsgLen;         /* 消息长度为sizeof(PHY_ERRLOG_TPHY_TAS_INFO_STRU) /2*/
    TLPHY_CONN_MAS_INFO_STRU              stTphyMasInfo;    /* TPHY天线切换关键信息 */
}TPHY_MAS_CHR_CONN_REQ_STRU;

/*****************************************************************************
 结构名    :LPHY_AGENT_ERRLOG_REQ_STRU
 结构说明  :RTT AGENT和TPHY的天线切换非连接态关键消息结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32     enMsgType;        /* 消息类型为LPHY_AGENT_ERRLOG_REQ */
    VOS_UINT32                             ulMsgLen;         /* 消息长度为sizeof(PHY_ERRLOG_LPHY_TAS_INFO_STRU) /2*/
    TLPHY_NONCONN_MAS_INFO_STRU            stLphyMasInfo;    /* LPHY天线切换关键信息 */
}LPHY_AGENT_ERRLOG_REQ_STRU;

/*****************************************************************************
 结构名    :LPHY_MAS_CHR_CONN_REQ_STRU
 结构说明  :RTT AGENT和TPHY的天线切换连接态关键消息结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32     enMsgType;        /* 消息类型为LPHY_AGENT_ERRLOG_REQ */
    VOS_UINT32                             ulMsgLen;         /* 消息长度为sizeof(PHY_ERRLOG_LPHY_TAS_INFO_STRU) /2*/
    TLPHY_CONN_MAS_INFO_STRU               stLphyMasInfo;    /* LPHY天线切换关键信息 */
}LPHY_MAS_CHR_CONN_REQ_STRU;


/*****************************************************************************
 结构名    : TLPHY_AGENT_SEND_OM_REQ_STRU
 结构说明  :RTT AGENT和TLPHY的OM重传消息结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32     enMsgType;         /* 消息类型为TPHY_AGENT_SEND_OM_REQ、LPHY_AGENT_SEND_OM_REQ */
    VOS_UINT32                             ulMsgLen;          /* 消息长度为2 */
    VOS_UINT32                             ulOmSendMsgCount;  /* 重发的OM消息条数 */
}TLPHY_AGENT_SEND_OM_REQ_STRU;

/*****************************************************************************
 结构名    : AGENT_TLPHY_SEND_OM_CNF_STRU
 结构说明  :RTT AGENT和TLPHY的OM重传消息确认结构体
*****************************************************************************/
typedef struct
{
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32     enMsgType;          /* 消息类型为AGENT_TPHY_SEND_OM_CNF、AGENT_LPHY_SEND_OM_CNF */
    VOS_UINT32                             ulMsgLen;           /* 消息长度为2 */
    VOS_UINT32                             ulOmRemainMsgCount; /* 剩余的OM消息条数 */
}AGENT_TLPHY_SEND_OM_CNF_STRU;

/*****************************************************************************
结构名    : AGENT_TLPHY_ERRLOG_CTRL_INFO_STRU
结构说明  : RTT AGENT转发给TLPHY的ERRLOG控制信息
*****************************************************************************/
typedef struct
{
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32     enMsgType;          /* 消息类型为AGENT_TLPHY_ERRLOG_CTRL_INFO */
    VOS_UINT32                             ulMsgLen;           /* 消息长度为2 */
    VOS_UINT16                             usErrLogCtrlFlag;   /* ERRLOG打开标识，0关闭，1打开 */
    VOS_UINT16                             usAlmLevel;         /* ERRLOG上报级别 */
}AGENT_TLPHY_ERRLOG_CTRL_INFO_STRU;

/*****************************************************************************
 结构名    : TLPHY_MTA_AFCLOCK_STATUS_RPT_STRU
 结构说明  : TLPHY 上报到RTT AGENT的AFC锁定状态消息结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32        enMsgType; //消息类型
    VOS_UINT32                                ulMsgLen;  //消息长度
    TLPHY_MTA_AFCLOCK_STATUS_ENUM_UINT16      enStatus;  //锁定状态
    VOS_UINT16                                ausReserved1[1];
}TLPHY_AGENT_AFCLOCK_STATUS_RPT_STRU;

/*****************************************************************************
 结构名    : TLPHY_AGENT_REPORT_ERROR_RPT_STRU
 结构说明  : TLPHY 上报到RTT AGENT的邮箱错误信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                ulCount;  //ERROR COUNT;
}TLPHY_REPORT_ERROR_MESSAGE_STRU;

typedef struct
{
    VOS_MSG_HEADER
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32        enMsgType; //消息类型
    VOS_UINT32                                ulMsgLen;  //消息长度
    TLPHY_REPORT_ERROR_MESSAGE_STRU           stMessage;
}TLPHY_AGENT_REPORT_ERROR_RPT_STRU;


/*****************************************************************************
 结构名    : AGENT_TLPHY_AFCLOCK_STATUS_RPT_NTF_STRU
 结构说明  : 由RTT Agent下发到TLPHY的AFC锁定状态查询消息结构体
*****************************************************************************/
typedef struct
{
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32        enMsgType; //消息类型
    VOS_UINT32                                ulMsgLen;  //消息长度
    VOS_UINT16                                usReportCtrolFlag;   //0:停止上报，1:启动上报，无限次上报时需要下发停止上报时才停止上报，其他情况DSP上报次数达到最大次数时才停止上报
    VOS_UINT16                                usReportCount;       //上报次数，若是0xffff则无限次上报
    VOS_UINT16                                usReportDuration;    //上报间隔，以ms为单位，粒度为10ms的整数倍，上报次数大于1时有效
    VOS_UINT16                                ausReserved[1];
}AGENT_TLPHY_AFCLOCK_STATUS_RPT_NTF_STRU;

/*****************************************************************************
 结构名    : AGENT_TLPHY_RFICSSIRD_REQ_STRU
 结构说明  : 由RTT Agent下发到TLPHY的RFIC SSI寄存器值查询消息结构体

 1.日    期 : 2015年11月12日
   作    者 : l00314907
   创建内容 : 新建
*****************************************************************************/
typedef struct
{
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32        enMsgType;
    VOS_UINT32                                ulMsgLen;
    VOS_UINT16                                usChannelNo;    /* RFIC通道号 */
    VOS_UINT16                                usRficReg;      /* 寄存器地址 */
}AGENT_TLPHY_RFICSSIRD_REQ_STRU;

/*****************************************************************************
 结构名    : TLPHY_AGENT_RFICSSIRD_IND_STRU
 结构说明  : TLPHY上报给RTT Agent的RFIC SSI寄存器值消息结构体

 1.日    期 : 2015年11月12日
   作    者 : l00314907
   创建内容 : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32        enMsgType;   //消息类型
    VOS_UINT32                                ulMsgLen;    //消息长度
    VOS_UINT32                                ulRegValue;  //寄存器配置值
}TLPHY_AGENT_RFICSSIRD_IND_STRU;
/*****************************************************************************
结构名    : TLPHY_AGENT_PAGING_CRC_STRU
结构说明  :LPHY发送给RTT AGENT的PAGING CRC信息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32    enMsgType;         /* 消息类型为TPHY_AGENT_SEND_OM_REQ、LPHY_AGENT_SEND_OM_REQ */
    VOS_UINT32                            ulMsgLen;          /* 消息长度为16bit 长度，6*/
    INT32                                 lRsrp;             /* Paging crc fail时的RSRP值*/
    INT32                                 lRsrq;             /* Paging crc fail时的RSRQ值*/
    INT16                                 sSnrR0;            /* Paging crc fail时天线0的SNR值*/
    INT16                                 sSnrR1;            /* Paging crc fail时天线1的SNR值*/
}TLPHY_AGENT_PAGING_CRC_STRU;

typedef struct
{
    INT16                             sRsrp;
    INT16                             sRsrq;
}EMU_CHR_RPT_PARA_STRU;

/*****************************************************************************
结构名    : MBX_TLPHY_CHR_RPT_PARA
结构说明  : TLPHY上报到MBX后再上报给CHR的结构，支持扩展
*****************************************************************************/

typedef struct
{
    UINT16                            usCellId;
    UINT16                            usDlFreqInfo;
    UINT16                            usUlFreqInfo;
    UINT16                            usBandInd;
    EMU_CHR_RPT_PARA_STRU             stEmuRptPara;
}TLPHY_CHR_RPT_PARA_STRU;

/*****************************************************************************
结构名    : TLPHY_AGENT_TXRX_PARA_STRU
结构说明  :LPHY发送给RTT AGENG的上行TX PWR信息
*****************************************************************************/
typedef struct
{
	VOS_MSG_HEADER
	RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32    enMsgType;         /* 消息类型 */
	VOS_UINT32                            ulMsgLen;          /* 消息长度为 */
    TLPHY_CHR_RPT_PARA_STRU               stRptPara;
	VOS_UINT32                            ulTimeStamp;       /* NAS下发请求前最后一次上行发送对应的时间戳 */
    VOS_INT32                             lUlTxPwr;          /* NAS下发请求前最后一次上行发送对应的发送功率 */
}TLPHY_AGENT_TXRX_PARA_STRU;


/*****************************************************************************
结构名    : AGENT_TLPHY_TXRX_INFO_REQ_STRU
结构说明  :LPHY发送给RTT AGENG的上行TX PWR信息
*****************************************************************************/
typedef struct
{
	RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32    enMsgType;         /* 消息类型 */
	VOS_UINT32                            ulMsgLen;          /* 消息长度为2 */
	VOS_UINT32                            ulTxPowerReqCnt;       /* RTT Agent向TLPHY发送TX PWR请求次数 */
}AGENT_TLPHY_TXRX_INFO_REQ_STRU;


/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __RTTAGENT_INTERFACE_H__ */
