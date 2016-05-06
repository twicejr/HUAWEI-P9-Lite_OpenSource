

#ifndef __TLL2ErrorLog_H__
#define __TLL2ErrorLog_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "product_config.h"
#include "omnvinterface.h"
#include "omerrorlog.h"
#include "omringbuffer.h"
#include "SysNvId.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define TLL2_LTE_RING_BUFFER_SIZE    (1024 * 4)  /* TLL2_LTE errlog 申请buffer的大小 */
#define TLL2_TDS_RING_BUFFER_SIZE    (1024 * 4)  /* TLL2_TDS errlog 申请buffer的大小 */

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 枚举名    : TLL2_ERRLOG_MODEM_ID_ENUM
 枚举说明  : TLL2 MODEM_ID
*****************************************************************************/
enum TLL2_ERRLOG_MODEM_ID_ENUM
{
    TLL2_ERRLOG_MODEM_ID_0        = 0x00 ,      /* 主卡 */
    TLL2_ERRLOG_MODEM_ID_1        = 0x01 ,      /* 副卡 */
    TLL2_ERRLOG_MODEM_ID_REV1     = 0x02 ,      /* 保留 */
    TLL2_ERRLOG_MODEM_ID_REV2     = 0x03 ,      /* 保留 */

    TLL2_ERRLOG_MODEM_ID_BUTT
};
typedef VOS_UINT16 TLL2_ERRLOG_MODEM_ID_ENUM_UINT16;

/*****************************************************************************
 枚举名    : TLL2_ERRLOG_ALM_LEVEL_ENUM
 枚举说明  : TLL2告警级别
*****************************************************************************/
enum TLL2_ERRLOG_ALM_LEVEL_ENUM
{
    TLL2_ERRLOG_ALM_LEVEL_CRITICAL   = 0x01,        /*紧急*/
    TLL2_ERRLOG_ALM_LEVEL_MAJOR      = 0x02,        /*重要*/
    TLL2_ERRLOG_ALM_LEVEL_MINOR      = 0x03,        /*次要*/
    TLL2_ERRLOG_ALM_LEVEL_WARNING    = 0x04,        /*提示*/

    TLL2_ERRLOG_ALM_LEVEL_BUTT
};
typedef VOS_UINT16  TLL2_ERRLOG_ALM_LEVEL_ENUM_UINT16;

/*****************************************************************************
 枚举名    : TLL2_ERRLOG_ALM_TYPE_ENUM
 枚举说明  : TLL2告警 类型
*****************************************************************************/
enum TLL2_ERRLOG_ALM_TYPE_ENUM
{
    TLL2_ERRLOG_ALM_TYPE_COMMUNICATION          = 0x00,     /* 通信*/
    TLL2_ERRLOG_ALM_TYPE_QUALITY_OF_SERVICE     = 0x01,     /* 业务质量*/
    TLL2_ERRLOG_ALM_TYPE_PROCESS_ERROR          = 0x02,     /* 处理出错*/
    TLL2_ERRLOG_ALM_TYPE_EQUIPMENT_ERROR        = 0x03,     /* 设备故障*/
    TLL2_ERRLOG_ALM_TYPE_ENVIRONMENTAL_ERROR    = 0x04,     /* 环境故障*/

    TLL2_ERRLOG_ALM_TYPE_BUTT
};
typedef VOS_UINT16  TLL2_ERRLOG_ALM_TYPE_ENUM_UINT16;



/*****************************************************************************
 枚举名    : TLL2_LTE_ERROR_ALARM_ID_ENUM
 枚举说明  : TLL2_LTE 告警ID
*****************************************************************************/
enum TLL2_LTE_ERROR_ALARM_ID_ENUM
{
    TLL2_LMAC_RAR_NOTMATCH = 1,
    TLL2_LMAC_RAR_TIMEOUT,
    TLL2_LMAC_CONTENT_TIMEOUT,
    TLL2_LMAC_CONTENT_NOTMATCH,
    TLL2_LMAC_OVER_PBL_MAX_TXNUM,
    TLL2_LMAC_MSG3_FAIL,
    TLL2_LMAC_TA_TIMEOUT,
    TLL2_LMAC_OVER_MAX_SR_SEND,
    TLL2_LRLC_UL_AM_MAX_RETXNUM,
    TLL2_LRLC_DL_TBMEM_FULL,
    TLL2_LPDCP_ERROR_INTEGRITY_VERIFY,

    TLL2_LMAC_SCHED_INFO,
    TLL2_LRLC_UL_INFO,
    TLL2_LRLC_DL_INFO,
    TLL2_LPDCP_UL_INFO,
    TLL2_LPDCP_DL_INFO,
    TLL2_LTE_STATS_INFO,
    TLL2_LTE_BUFFER_OVERFLOW,
    TLL2_LTE_ERRLOG_ALARM_ID_BUTT
};
typedef VOS_UINT16 TLL2_LTE_ERROR_ALARM_ID_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TLL2_TDS_ERROR_ALARM_ID_ENUM
 枚举说明  : TLL2_TDS 告警ID
*****************************************************************************/
enum TLL2_TDS_ERROR_ALARM_ID_ENUM
{
    TLL2_TMAC_OUT_OF_SYNC = 1,
    TLL2_TMAC_QUEUE_FULL,
    TLL2_TMAC_SENDMSG_FAIL,
    TLL2_TRLC_RST,
    TLL2_TRLC_UL_BUFFER_FULL,
    TLL2_TPDCP_FAIL,
    TLL2_TMAC_HSUPA_INFO,
    TLL2_TMAC_HSDPA_INFO,
    TLL2_TRLC_UL_TRANS_INFO,
    TLL2_TRLC_DL_TRANS_INFO,
    TLL2_TRLC_STATICS_INFO,

    TLL2_TDS_BUFFER_OVERFLOW,
    TLL2_TDS_ERRLOG_ALARM_ID_BUTT
};
typedef VOS_UINT16 TLL2_TDS_ERROR_ALARM_ID_ENUM_UINT8;


/*****************************************************************************
   5 STRUCT
*****************************************************************************/

/*****************************************************************************
 结构名    : LTE_ERRLOG_MAC_RAR_NOTMATCH_INFO
 结构说明  : MAC 随机接入子头匹配失败
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG消息头 */
    VOS_UINT16                          usFrame;        /*帧号*/
    VOS_UINT8                           ucSubFrame;     /*子帧号*/
    VOS_UINT8                           ucMatchFlag;    /*子头匹配成功指示，0:失败，1:成功*/
    VOS_UINT8                           ucBiFlag;       /*BI值指示，0:无效，1:有效*/
    VOS_UINT8                           ucBiIndex;      /*BI值索引*/
    VOS_UINT8                           aucRev[2];      /*4字节对齐*/
}LTE_ERRLOG_MAC_RAR_NOTMATCH_INFO;

/*****************************************************************************
 结构名    : LTE_ERRLOG_MAC_RAR_TIMEROUT_INFO
 结构说明  : MAC 接收RAR超时
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG消息头 */
    VOS_UINT8                           enTimerID;
    VOS_UINT8                           aucRev[3];      /*4字节对齐*/
}LTE_ERRLOG_MAC_RAR_TIMEROUT_INFO;

/*****************************************************************************
 结构名    : LTE_ERRLOG_MAC_CONTENTION_TIMEROUT_INFO
 结构说明  : MAC 接收竞争解决消息超时
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG消息头 */
    VOS_UINT8                           enTimerID;
    VOS_UINT8                           aucRev[3];      /*4字节对齐*/
}LTE_ERRLOG_MAC_CONTENTION_TIMEROUT_INFO;

/*****************************************************************************
 结构名    : LTE_ERRLOG_MAC_CONTENT_NOTMATCH_INFO
 结构说明  : MAC 解析Msg4头出错,Msg4匹配失败
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG消息头 */
    VOS_UINT8                           enMatchFlg;
    VOS_UINT8                           aucRev[3];      /*4字节对齐*/
}LTE_ERRLOG_MAC_CONTENT_NOTMATCH_INFO;

/*****************************************************************************
 结构名    : LTE_ERRLOG_MAC_OVER_PBL_MAX_TXNUM_INFO
 结构说明  : MAC 随机接入Preamble达到最大发送次数
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG消息头 */
    VOS_UINT8                           ucRaTxNum;      /*随机接入重发计数器：*/
    VOS_UINT8                           ucPblMaxTxNum;  /*随机接入Preamble最大发送次数*/
    VOS_UINT8                           aucRev[2];      /*4字节对齐*/
}LTE_ERRLOG_MAC_OVER_PBL_MAX_TXNUM_INFO;

/*****************************************************************************
 结构名    : LTE_ERRLOG_MAC_MSG3_FAIL_INFO
 结构说明  : Msg3错误
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG消息头 */
    VOS_UINT32                          ulTbSize;
    VOS_UINT16                          usSendFrame;
    VOS_UINT8                           ucSendSubFrame;
    VOS_UINT8                           ucSchedValid;
    VOS_UINT8                           ucHarqId;       /*发送时刻HARQ进程号*/
    VOS_UINT8                           enSchedMode;
    VOS_UINT8                           ucPucchEnable;  /*发送时刻是否存在PUCCH发送*/
    VOS_UINT8                           aucRev;         /*4字节对齐*/
}LTE_ERRLOG_MAC_MSG3_FAIL_INFO;

/*****************************************************************************
 结构名    : LTE_ERRLOG_MAC_TA_TIME_OUT_INFO
 结构说明  : MAC ta 定时器超时
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG消息头 */
    VOS_UINT32                          ulTaTimeOutNum;
    VOS_UINT8                           enTimerID;
    VOS_UINT8                           aucRev[3];      /*4字节对齐*/
}LTE_ERRLOG_MAC_TA_TIME_OUT_INFO;

/*****************************************************************************
 结构名    : LTE_ERRLOG_MAC_OVER_MAX_SR_SEND_INFO
 结构说明  : MAC 调度请求发送达到最大次数
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;           /* ERR LOG消息头 */
    VOS_UINT16                          usSrDynMaxNum;
    VOS_UINT16                          usSrLastFrame;      /*SR上次发送的帧号*/
    VOS_UINT8                           ucSrLastSubFrame;   /*SR上次发送的子帧号*/
    VOS_UINT8                           ucSrCounter;        /*SR累计次数*/
    VOS_UINT8                           aucRev[2];          /*4字节对齐*/
}LTE_ERRLOG_MAC_OVER_MAX_SR_SEND_INFO;

/*****************************************************************************
 结构名    : LTE_ERRLOG_RLC_UL_AM_MAX_RETXNUM_INFO
 结构说明  : RLC上行AM重传达到最大次数
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;           /* ERR LOG消息头 */
    VOS_UINT32                          ulPduMaxRetxNum;    /*最大的重传次数*/
    VOS_UINT32                          ulPduSn;
    VOS_UINT16                          usRetxNum;
    VOS_UINT8                           ucRbId;
    VOS_UINT8                           aucRev;             /*4字节对齐*/
}LTE_ERRLOG_RLC_UL_AM_MAX_RETXNUM_INFO;


/*****************************************************************************
 结构名    : LTE_ERRLOG_RLC_DL_TBMEM_FULL_INFO
 结构说明  : RLC下行TB内存满
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG消息头 */
    VOS_UINT8                           ucRbId;
    VOS_UINT8                           aucRev[3];      /*4字节对齐*/
}LTE_ERRLOG_RLC_DL_TBMEM_FULL_INFO;

/*****************************************************************************
 结构名    : LTE_ERRLOG_PDCP_ERROR_INTEGRITY_VERIFY_INFO
 结构说明  : PDCP 完整性验证错误
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG消息头 */
    VOS_UINT8                           ucRbId;
    VOS_UINT8                           aucRev[3];      /*4字节对齐*/
}LTE_ERRLOG_PDCP_ERROR_INTEGRITY_VERIFY_INFO;

/*****************************************************************************
 结构名    : TDS_ERRLOG_MAC_OUTOFSYNC_INFO
 结构说明  : MAC失步
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;           /* ERR LOG消息头 */
    VOS_UINT8                           cause;              /*T312 expired：0；T313 expired：1*/
    VOS_UINT8                           inActivationTime;
    VOS_UINT8                           tfcsIdentity;
    VOS_UINT8                           aucRev;             /*4字节对齐*/
}TDS_ERRLOG_MAC_OUTOFSYNC_INFO;

/*****************************************************************************
 结构名    : TDS_ERRLOG_MAC_QUEUEFULL_INFO
 结构说明  : MAC队列满结构体
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG消息头 */
    VOS_UINT32                          LossMsgID;
}TDS_ERRLOG_MAC_QUEUEFULL_INFO;

/*****************************************************************************
 结构名    : TDS_ERRLOG_MAC_SENDMSGFAIL_INFO
 结构说明  : MAC消息发送失败结构体
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG消息头 */
    VOS_UINT32                          FailMsgID;
}TDS_ERRLOG_MAC_SENDMSGFAIL_INFO;

/*****************************************************************************
 结构名    : TDS_ERRLOG_RLC_RST_INFO
 结构说明  : RLC RST信息
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG消息头 */
    VOS_UINT8                           rbIdentity;
    VOS_UINT8                           aucRev[3];      /*4字节对齐*/
}TDS_ERRLOG_RLC_RST_INFO;

/*****************************************************************************
 结构名    : TDS_ERRLOG_RLC_UL_BUFFERFULL_INFO
 结构说明  : RLC UL buffer 满
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG消息头 */
    VOS_UINT8                           rbIdentity;
    VOS_UINT8                           aucRev[3];      /*4字节对齐*/
}TDS_ERRLOG_RLC_UL_BUFFERFULL_INFO;


/*****************************************************************************
 结构名    : TDS_ERRLOG_PDCP_FAIL_INFO
 结构说明  : pdcp错误信息上报内容
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG消息头 */
    VOS_UINT32                          failCause;
}TDS_ERRLOG_PDCP_FAIL_INFO;


/*****************************************************************************
 结构名    : TLL2_ERRLOG_BUFFER_OVERFLOW_STRU
 结构说明  :缓存区溢出
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG消息头 */
    VOS_UINT32                          ulCount;        /* 缓存区溢出计数 */
}TLL2_ERRLOG_BUFFER_OVERFLOW_STRU;

/*****************************************************************************
 结构名    : LTE_MAC_SCHED_INFO_STRU
 结构说明  : LTE L2 MAC上行调度信息结构体
*****************************************************************************/

typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;

    VOS_UINT16                          usFrameNo;          /*帧号*/
    VOS_UINT16                          usSubFrameNo;       /*子帧号*/

    VOS_UINT8                           ucShortBsrGrpId;    /*短BSR group ID号*/
    VOS_UINT8                           ucShortBsrValue;    /*短BSR 值*/
    VOS_UINT8                           ucLongBsr0Value;    /* group 0长BSR值*/
    VOS_UINT8                           ucLongBsr1Value;    /* group 1长BSR值*/

    VOS_UINT8                           ucLongBsr2Value;    /* group 2长BSR值*/
    VOS_UINT8                           ucLongBsr3Value;    /* group 3长BSR值*/
    VOS_UINT16                          usRsv;              /*保留字段*/
    VOS_UINT32                          ulUlGrantSize;      /* 上行授权值*/
}LTE_ERRLOG_MAC_SCHED_INFO_STRU;


/*****************************************************************************
 结构名    : LTE_RLC_UL_TRANS_INFO_STRU
 结构说明  : LTE L2 RLC上行数传信息结构体
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU               stHeader;

    VOS_UINT16                           usFrameNo;         /*帧号*/
    VOS_UINT16                           usSubFrameNo;      /*子帧号*/

    VOS_UINT16                           usRbId;            /*RB ID*/
    VOS_UINT16                           usTransSn;         /*发送的RLC PDU SN值*/

    VOS_UINT16                           usVTs;             /*RLC VTS*/
    VOS_UINT16                           usVTa;             /*RLC VTA*/

    VOS_UINT32                           ulReTxSn;          /*RLC 上行重传SN值*/

}LTE_ERRLOG_RLC_UL_TRANS_INFO_STRU;

/*****************************************************************************
 结构名    : LTE_RLC_DL_TRANS_INFO_STRU
 结构说明  :LTE L2 RLC下行数传信息结构体
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;

    VOS_UINT16                            usFrameNo;        /*帧号*/
    VOS_UINT16                            usSubFrameNo;     /*子帧号*/

    VOS_UINT16                            usRbId;           /*RB ID*/
    VOS_UINT16                            usRecvSn;         /*接收的RLC PDU SN值*/

    VOS_UINT16                            usVRr;            /*RLC VR(R)*/
    VOS_UINT16                            usVRh;            /*RLC VR(H)下行接收到的最大SN值*/

    VOS_UINT16                            usVRMs;           /*RLC VR(MS)*/
    VOS_UINT16                            usVRx;            /*RLC VR(X)*/

}LTE_ERRLOG_RLC_DL_TRANS_INFO_STRU;

/*****************************************************************************
 结构名    : LTE_PDCP_DL_TRANS_INFO_STRU
 结构说明  :LTE L2 PDCP上行数传信息结构体
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;

    VOS_UINT16                            usFrameNo;        /*帧号*/
    VOS_UINT16                            usSubFrameNo;     /*子帧号*/

    VOS_UINT32                            ulRbId;           /*RB ID*/

    VOS_UINT32                            ulDlLastSubmitSn; /*PDCP下行上次递交的SN值*/
    VOS_UINT32                            ulDlRxSn;         /*PDCP下行接收的SN值*/
    VOS_UINT32                            ulDlNextRxSn;     /*PDCP下行下一个接收的SN值*/
    VOS_UINT32                            ulDlRxHfn;        /*PDCP下行HFN值*/

}LTE_ERRLOG_PDCP_DL_TRANS_INFO_STRU;

/*****************************************************************************
 结构名    : LTE_PDCP_UL_TRANS_INFO_STRU
 结构说明  :LTE L2 PDCP下行数传信息结构体
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;

    VOS_UINT16                            usFrameNo;        /*帧号*/
    VOS_UINT16                            usSubFrameNo;     /*子帧号*/

    VOS_UINT32                            ulRbId;           /*RB ID*/

    VOS_UINT32                            ulUlNextAckSn;    /*PDCP上行下一个确认的SN值*/
    VOS_UINT32                            ulUlTxSn;         /*PDCP上行发送的SN值*/

    VOS_UINT32                            ulUlNextTxSn;     /*PDCP上行下一个发送的SN值*/
    VOS_UINT32                            ulUlTxHfn;        /*PDCP上行HFN值*/


}LTE_ERRLOG_PDCP_UL_TRANS_INFO_STRU;

/*****************************************************************************
 结构名    : LTE_L2_STATICS_INFO_STRU
 结构说明  :LTE L2 数传统计信息结构体
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                stHeader;

    VOS_UINT16                            usFrameNo;          /*帧号*/
    VOS_UINT16                            usSubFrameNo;       /*子帧号*/

    VOS_UINT32                            ulRbId;             /*RB ID*/
    VOS_UINT32                            ulCdsUlTxNum;       /*CDS 上行发送数据包统计个数*/
    VOS_UINT32                            ulPdcpUlTxNum;      /*PDCP 上行发送数据包统计个数*/
    VOS_UINT32                            ulPdcpUlAckNum;     /*PDCP 上行发送数据包得到确认的统计个数*/
    VOS_UINT32                            ulPdcpUlDiscNum;    /*PDCP 上行丢弃的数据包统计个数*/
    VOS_UINT32                            ulRohcCompNum;      /*PDCP ROHC上行压缩的数据包统计个数*/
    VOS_UINT32                            ulRlcUlTxNum;       /*RLC上行发送数据包统计个数*/
    VOS_UINT32                            ulRlcDiscNum;       /*RLC 上行丢弃的数据包统计个数*/
    VOS_UINT32                            ulMacUlSchedSuccNum;/*MAC 上行成功调度的数据包统计个数*/
    VOS_UINT32                            ulMacSendSrNum;     /*MAC 发送SR的统计个数*/

   VOS_UINT32                            ulMacDlDemultipleSucc; /*MAC 下行解复用成功的统计个数*/
    VOS_UINT32                            ulRlcDlRxNum;          /*RLC下行接收数据包统计个数*/
    VOS_UINT32                            ulPdcpDlRxNum;         /*PDCP下行接收数据包统计个数*/
    VOS_UINT32                            ulRohcDecpFailNum;     /*ROHC下行解压缩失败数据包统计个数*/
    VOS_UINT32                            ulRohcDecpSuccNum;     /*ROHC下行解压缩成功数据包统计个数*/
    VOS_UINT32                            ulCdsDlRxNum;          /*CDS下行接收数据包统计个数*/

}LTE_ERRLOG_L2_STATICS_INFO_STRU;


/*****************************************************************************
 结构名    : TDS_ERRLOG_MAC_HSUPA_INFO_STRU
 结构说明  TDS MAC HSUPA信息结构体
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;

    VOS_UINT16                          usSysFramNo;    /*系统帧号*/
    VOS_UINT16                          usTbSize;       /*MAC UPA上行授权大小*/

    VOS_UINT8                           ucSnpl;         /*MAC UPA SNPL 邻区路损值*/
    VOS_UINT8                           ucUph;          /*MAC UPA UPH*/
    VOS_UINT8                           ucTebs;         /*MAC UPA TEBS*/
    VOS_UINT8                           ucPrri;         /*MAC UPA PRRI*/

    VOS_UINT8                           ucTrri;         /*MAC UPA TRRI*/
    VOS_UINT8                           ucCrri;         /*MAC UPA CRRI*/
    VOS_UINT8                           ucRscpLevel;    /*MAC 服务小区RSCP值*/
    VOS_UINT8                           ucRsv;          /*保留*/

}TDS_ERRLOG_MAC_HSUPA_INFO_STRU;

/*****************************************************************************
 结构名    : TDS_ERRLOG_MAC_HSDPA_INFO_STRU
 结构说明  TDS MAC HSDPA信息结构体
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;
    VOS_UINT16                          usSysFramNo;    /*系统帧号*/
    VOS_UINT16                          usTsn;          /*MAC HSDPA 发送SN值*/
    VOS_UINT16                          usExpectedSn;   /*MAC HSDPA 期待的下一个SN*/
    VOS_UINT16                          usTbSize;       /*MAC HSDPA 下行授权大小*/

}TDS_ERRLOG_MAC_HSDPA_INFO_STRU;

/*****************************************************************************
 结构名    : TDS_ERRLOG_L2_STATICS_INFO_STRU
 结构说明  TDS L2数传统计信息结构体
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;

    VOS_UINT16                          usSysFramNo;    /*系统帧号*/
    VOS_UINT16                          usRsv;

    VOS_UINT8                           ucMacState;     /*MAC当前状态*/
    VOS_UINT8                           ucHsupaFlag;    /*MAC HSUPA是否生效*/
    VOS_UINT8                           ucHsdpaFlag;    /*MAC HSDPA是否生效*/
    VOS_UINT8                           ucRbId;         /*RB ID值*/

    VOS_UINT32                          ulPdcpUlRxNum;  /*PDCP上行从RABM接收到的SDU数目*/
    VOS_UINT32                          ulPdcpUlTxNum;  /*PDCP层上行发送数据包个数*/
    VOS_UINT32                          ulRlcUlTxNum;   /*RLC层上行发送数据包个数*/
    VOS_UINT32                          ulMacUlTxNum;   /*MAC层上行发送数据包个数*/

    VOS_UINT32                          ulPdcpDlTxNum;  /*PDCP下行发送给RABM的SDU数目*/
    VOS_UINT32                          ulPdcpDlRxNum;  /*PDCP层下行接收数据包个数*/
    VOS_UINT32                          ulRlcDlRxNum;   /*RLC层下行接收数据包个数*/
    VOS_UINT32                          ulMacDlRxNum;   /*MAC层下行接收数据包个数*/

}TDS_ERRLOG_L2_STATICS_INFO_STRU;

/*****************************************************************************
 结构名    : TDS_ERRLOG_RLC_UL_TRANS_INFO_STRU
 结构说明  TDS L2 RLC上行数传信息结构体
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;

    VOS_UINT16                          usSysFramNo;    /*系统帧号*/
    VOS_UINT16                          usUlSendSn;     /*RLC层上行发送的PDU SN值*/

    VOS_UINT8                           ucRbId;         /*RB ID*/
    VOS_UINT8                           ucPduSize;      /*RLC 层PDU 大小，单位byte*/
    VOS_UINT8                           ucPduNum;       /*一次组包RLC PDU个数*/
    VOS_UINT8                           ucRsv;

    VOS_UINT32                          ulRlcBo;        /*RLC 层缓存量统计*/
    VOS_UINT32                          ulPdcpBo;       /*PDCP 层缓存量统计*/

    VOS_UINT16                          usVTs;          /*RLC 层窗口变量VTS*/
    VOS_UINT16                          usVTa;          /*RLC 层窗口变量VTA*/

}TDS_ERRLOG_RLC_UL_TRANS_INFO_STRU;

/*****************************************************************************
 结构名    : TDS_ERRLOG_RLC_DL_TRANS_INFO_STRU
 结构说明  TDS L2 RLC下行数传信息结构体
*****************************************************************************/
typedef struct
{

    OM_ERR_LOG_HEADER_STRU              stHeader;

    VOS_UINT16                          usSysFramNo;    /*系统帧号*/
    VOS_UINT16                          usDlRecvSn;     /*RLC层下行发送的PDU SN值*/


    VOS_UINT8                           ucRbId;         /*RB ID*/
    VOS_UINT8                           ucPduSize;      /*RLC 层PDU 大小，单位byte*/
    VOS_UINT8                           ucPduNum;       /*一次组包RLC PDU个数*/
    VOS_UINT8                           ucRsv;

    VOS_UINT16                          usVRr;          /*RLC 层窗口变量VR(R)*/
    VOS_UINT16                          usVRh;          /*RLC 层窗口变量VR(H)*/

}TDS_ERRLOG_RLC_DL_TRANS_INFO_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/



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

#endif /* end of TLL2ErrorLog.h */
