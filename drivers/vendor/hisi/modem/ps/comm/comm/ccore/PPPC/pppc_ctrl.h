
#ifndef      _PPPC_CTRL_H_
#define      _PPPC_CTRL_H_

#ifdef      __cplusplus
extern "C" {
#endif      /* end of __cplusplus */

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "AtPppInterface.h"
#include "PsCommonDef.h"
#include "product_config.h"
#include "TTFUtil.h"
#include "v_IO.h"
#include "TTFComm.h"
#include "TTFLink.h"
#include "taf_aps_ppp_pif.h"
#include "cnas_cttf_ehrpd_ehsm_ppp_pif.h"
#include "PsTypeDef.h"
#include "cttf_hrpd_pa_ppp_pif.h"
#include "pppc_pa_agent.h"
#include "UsimPsInterface.h"

#include "TtfDrvInterface.h"
#include "pppc_uim.h"
#include "TtfIpComm.h"


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define PPPC_FEATURE_ON                 (1)
#define PPPC_FEATURE_OFF                (0)

#if (FEATURE_OFF  == FEATURE_MULTI_MODEM)
#define PPPC_FEATURE_MULTI_MODEM        PPPC_FEATURE_OFF
#define PPPC_MAX_MODEM_NUM              (1)
#define PPPC_FEATURE_MODEM_2            PPPC_FEATURE_OFF
#else
#define PPPC_FEATURE_MULTI_MODEM        PPPC_FEATURE_ON
#if (3 == MULTI_MODEM_NUMBER)
#define PPPC_MAX_MODEM_NUM              (3)
#define PPPC_FEATURE_MODEM_2            PPPC_FEATURE_ON
#else
#define PPPC_MAX_MODEM_NUM              (2)
#define PPPC_FEATURE_MODEM_2            PPPC_FEATURE_OFF
#endif
#endif


/* 当上下行积累的报文帧数达到门限时,需要触发PPPC处理报文,是一种保护机制 */
#define PPPC_MAX_NOTIFY_PPPC_PROC_CNT           (200)

/* 当上下行处理的次数达到门限时,需要触发PPPC延时释放CPU,是一种保护机制 */
#define PPPC_MAX_NOTIFY_PPPC_DELAY_CNT          (50)

/* 以太网数据帧的物理特性是其长度必须在46~1500字节之间 */
#define PPPC_MIN_FRAME_LEN                      (46)
#define PPPC_MAX_FRAME_LEN                      (1500)

/* 1X和HRPD场景下RLP发送给PPPC的分片报文可能的最大值 */
#define PPPC_MAX_FRAGMENT_BIT_LEN               (12288)

/* 上行数据TTF内存所存储的最大长度 */
#define PPPC_MAX_UL_ENCAP_LEN                   (1600)

/* 当处理次数达到门限时退出PPPC,用于唤醒PPPC任务 */
#define PPPC_REACH_MAX_PROC_TIMER_AWAKE_LEN     (300)

/* 上行数据内存缓存片数,每片长度最大PPPC_MAX_UL_ENCAP_LEN字节 */
#define PPPC_MAX_UL_ENCAP_MEM_NUM               (2)

/* CDS的上行数据最长1500字节,经过PPP处理后最多扩展为1(0x7e)+3(0xff03)+4(0x0021)+1500*2+4(FCS)+1(0x7e) */
#define PPPC_MAX_UL_DATA_LEN                    (3013)

/* 当下行节点数累计达到100(每个节点最多可能有20片报文)个时,启动300ms定时器处理下行队列 */
#define PPPC_MAX_DL_NODE_CNT                    (100)

/* 接入鉴权延时处理时长 */
#define PPPC_AA_DELAY_TIMER_LEN                 (5000)

/* PPPC收到上行报文的事件掩码位 */
#define PPPC_UL_PKT_EVENT                       (0x1)

/* PPPC收到下行报文的事件掩码位 */
#define PPPC_DL_PKT_EVENT                       (0x2)

/* 上行任务连续调用最大次数 */
#define PPPC_UL_CONTINUOUS_MAX_CALL_CNT         (50)

#define PPPC_OM_TRANS_DATA_OFFSET_LEN           /*lint -e(545) -e(413)*/offsetof(CTTF_PPPC_TRACE_DATA_STRU, aucValue)
#define PPPC_OM_DIAL_CNF_OFFSET_LEN             /*lint -e(545) -e(413)*/offsetof(PPPC_AT_CDMA_DIAL_MODE_CNF_STRU, enMsgId)
#define PPPC_OM_ACT_CNF_OFFSET_LEN              /*lint -e(545) -e(413)*/offsetof(PPP_APS_ACT_CNF_STRU, enMsgId)
#define PPPC_OM_DEACT_CNF_OFFSET_LEN            /*lint -e(545) -e(413)*/offsetof(PPP_APS_DEACT_CNF_STRU, enMsgId)
#define PPPC_OM_DEACT_NOTIFY_OFFSET_LEN         /*lint -e(545) -e(413)*/offsetof(PPP_APS_DEACT_NTF_STRU, enMsgId)

#define PPPC_OM_ATTACH_CNF_OFFSET_LEN           /*lint -e(545) -e(413)*/offsetof(CTTF_CNAS_EHRPD_ATTACH_CNF_STRU, enMsgId)
#define PPPC_OM_DETACH_CNF_OFFSET_LEN           /*lint -e(545) -e(413)*/offsetof(CTTF_CNAS_EHRPD_DETACH_CNF_STRU, enMsgId)
#define PPPC_OM_PDN_CONN_CNF_OFFSET_LEN         /*lint -e(545) -e(413)*/offsetof(CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU, enMsgId)
#define PPPC_OM_PDN_DISC_CNF_OFFSET_LEN         /*lint -e(545) -e(413)*/offsetof(CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU, enMsgId)
#define PPPC_OM_DETACH_IND_OFFSET_LEN           /*lint -e(545) -e(413)*/offsetof(CTTF_CNAS_EHRPD_DETACH_IND_STRU, enMsgId)
#define PPPC_OM_PDN_DISC_IND_OFFSET_LEN         /*lint -e(545) -e(413)*/offsetof(CTTF_CNAS_EHRPD_PDN_DISC_IND_STRU, enMsgId)

#define PPPC_OM_QOS_REQ_OFFSET_LEN              /*lint -e(545) -e(413)*/offsetof(PPP_CTTF_HRPD_MFPA_QOS_REQ_STRU, enMsgId)
#define PPPC_OM_QOS_CLOSE_REQ_OFFSET_LEN        /*lint -e(545) -e(413)*/offsetof(PPP_CTTF_HRPD_MFPA_QOS_CLOSE_REQ_STRU, enMsgId)


#define PPPC_PDN_ID_UNIQUE                      (1)
#define PPPC_PPP_ID_FOR_ACCESS_AUTH             (0)                             /* 用于接入鉴权的PPP ID固定填写为0 */
#define PPPC_PPP_ID_MIN                         (1)
#define PPPC_PPP_ID_MAX                         (PPP_MAX_USER_NUM)
#define PPPC_MAX_PA_BINDING_APP_NUM             (3)
#define PPPC_HRPD_PA_DATA_STREAM_NUM            (2)                             /* 发数时流号默认填为2，与标杆一致 */

/* 激活PPP撞上接入鉴权时启定时器延时处理支持的最大定时器个数 */
#define PPPC_ACCESS_AUTH_DELAY_PROC_TIMER_MAX_NUM           (3)

/* 当在做初始接入鉴权时收到NAS的激活请求需要启动定时器延时处理 */
#define PPPC_ACCESS_AUTH_HRPD_ACT_DELAY_PROC_TIMER_LEN      (60000)

/**
 * Maximum number of NAI.
 */
#define PPPC_HRPD_MAX_NUM_NAI                   (15)

#define PPPC_HRPD_MAX_NAI_LENGTH                (255)

/* Get high 16 bits from 32 bits */
#define PPPC_GET_HIGH_16_BITS(ulVal)            (((ulVal) >> 16) & 0xFF)

/* Get low 16 bits from 32 bits */
#define PPPC_GET_LOW_16_BITS(ulVal)             ((ulVal) & 0xFF)

#define PPPC_MIN_ACTIVE_ENTITY                  (1)

#define PPPC_AUTH_SWITCH_ON                     (1)

#define PPPC_AUTH_SWITCH_OFF                    (0)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : PPPC_PROC_LINK_DIRECTION_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 判断处理上下行队列的依据
*****************************************************************************/
enum PPPC_PROC_LINK_DIRECTION_ENUM
{
    PPPC_PROC_BY_STAMP                  = 0,                /* 按照时间戳处理上下行队列 */
    PPPC_PROC_UL_NODE                   = 1,                /* 处理上行队列 */
    PPPC_PROC_DL_NODE                   = 2,                /* 处理下行队列 */

    PPPC_PROC_BUTT
};
typedef VOS_UINT16  PPPC_PROC_LINK_DIRECTION_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PPPC_INNER_MSG_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 上行或下行有报文要发时通知PPP模块处理
*****************************************************************************/
enum PPPC_INNER_MSG_TYPE_ENUM
{
    PPPC_HDLC_PROC_AS_FRM_PACKET_IND    = 0,                /* 收到上行待硬件HDLC封装报文 */

    PPPC_DATA_PROC_BUTT
};
typedef VOS_UINT16  PPPC_INNER_MSG_TYPE_ENUM_UINT16;

/** ****************************************************************************
 * Name        : PPPC_HRPD_PA_STREAM_STATE_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum PPPC_HRPD_PA_STREAM_STATE_ENUM
{
    PPPC_STREAM_CLOSE_STATE             = 0x00,
    PPPC_STREAM_OPEN_STATE              = 0x01,
    PPPC_STREAM_STATE_BUTT              = 0x02
};
typedef VOS_UINT8 PPPC_HRPD_PA_STREAM_STATE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : PPPC_ACCESS_AUTH_ACT_MODE_ENUM
 *
 * Description :
 *******************************************************************************/
enum PPPC_ACCESS_AUTH_ACT_MODE_ENUM
{
    PPPC_ACCESS_AUTH_ACT_MODE_HRPD          = 0,
    PPPC_ACCESS_AUTH_ACT_MODE_EHRPD_ATTACH  = 1,
    PPPC_ACCESS_AUTH_ACT_MODE_EHRPD_PDN     = 2,

    PPPC_ACCESS_AUTH_ACT_MODE_BUTT
};
typedef VOS_UINT16 PPPC_ACCESS_AUTH_ACT_MODE_ENUM_UINT16;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/
/*****************************************************************************
 结构名    :PPPC_UIM_MSG_STRU
 结构说明  :PPPC与卡交互消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;          /* 消息ID */
}PPPC_UIM_MSG_STRU;


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/** ****************************************************************************
* Name        : PPPC_DATA_Q_NOTIFY_CNT_STRU
*
* Description : PPP上下行队列从空到非空的通知消息计数.
*******************************************************************************/
typedef struct
{
    volatile VOS_UINT32                 ulNotifyMsgCnt;                         /* PPPC消息队列中待处理的消息个数 */
    VOS_SPINLOCK                        stSpinLock;                             /* 队列锁 */
} PPPC_DATA_Q_NOTIFY_CNT_STRU;

/** ****************************************************************************
* Name        : PPPC_DATA_LINK_NODE_STRU
*
* Description : 上下行数据链表.
*******************************************************************************/
typedef struct
{
    TTF_NODE_ST                         stNode;                                 /* PPP上下行链表 */
    VOS_UINT32                          ulTimeStamp;                            /* 入队时间戳 */
    PPPC_RAT_MODE_ENUM_UINT8            enRatMode;                              /* 接入模式 */
    VOS_UINT8                           ucPdnId;                                /* 承载号 */
    IP_DATA_TYPE_ENUM_UINT8             enIpDataType;                           /* IP包类型, 只用于上行 */
    VOS_UINT8                           ucStreamNum;                            /* 流号,HRPD/eHRPD使用 */
    VOS_UINT8                           ucNumReservLabels;                      /**< MFPA/EMPA relevant only */
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT8                           aucReservLabel[CTTF_HRPD_PA_MAX_NUM_RESERV_LABELS];
    VOS_UINT16                          usHigherLayerProtocol;                  /* usHigherLayerProtocol */
    VOS_UINT8                           aucReserv[2];
    VOS_UINT32                          ulPduCnt;                               /* 指示一个节点中存储的TTF内存块数 */
    TTF_MEM_ST                         *pstPduMem;                              /* PPP上下行报文,内部串联 */
    PS_DATA_EXT_INFO_STRU              *pstUlDataInfo;                           /* data info of cds */
}PPPC_DATA_LINK_NODE_STRU;

/** ****************************************************************************
* Name        : APS_CMD_MSG_LINK_NODE_STRU
*
* Description : 存储APS发给PPP的消息
*******************************************************************************/
typedef  struct
{
    TAF_APS_PPP_PIF_MSG_TYPE_ENUM_UINT16    enMsgType;                          /* 消息类型 */
    TAF_APS_PPP_RAT_MODE_ENUM_UINT8         enMode;
    TAF_APS_PPP_ADDR_TYPE_ENUM_UINT8        enPdnType;
    TAF_APS_PPP_AUTH_TYPE_ENUM_UINT8        enAuthType;                         /* 配置的鉴权类型 */
    VOS_UINT8                               aucReserved[3];
}APS_CMD_LINK_NODE_STRU;

/** ****************************************************************************
* Name        : PPPC_DATA_PROC_NOTIFY_MSG
*
* Description : 数据通知消息.
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */        /*_H2ASN_Skip*/
    PPPC_INNER_MSG_TYPE_ENUM_UINT16     enMsgType;                              /* 消息类型 */      /*_H2ASN_Skip*/
    VOS_UINT8                           aucResv[2];
}PPPC_DATA_PROC_NOTIFY_MSG;

/** ****************************************************************************
* Name        : EHSM_CMD_MSG_LINK_NODE_STRU
*
* Description : 存储EHSM发给PPP的消息
*******************************************************************************/
typedef  struct
{
    CNAS_CTTF_EHRPD_PIF_MSG_TYPE_ENUM_UINT16    enMsgType;             /* 消息类型 */
    CNAS_CTTF_EHRPD_PDN_TYPE_ENUM_UINT8     enPdnType;
    CNAS_CTTF_EHRPD_ATTACH_TYPE_ENUM_UINT8  enAttachType;
    VOS_UINT8                               ucAddressAllocCause;
    VOS_UINT8                               aucReserved[3];
    CNAS_CTTF_EHRPD_APN_STRU                stApn;
    CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU        stPdnAddress;
    CNAS_CTTF_EHRPD_PCO_STRU                stPco;
    VOS_UINT8                               aucIpv4DefaultRouterAddress[CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN];
}EHSM_CMD_LINK_NODE_STRU;

/** ****************************************************************************
* Name        : PPPC_APS_MSG_LINK_NODE_STRU
*
* Description : 存储APS/EHSM发给PPP的消息链表节点
*******************************************************************************/
typedef  struct
{
    TTF_NODE_ST                             stNode;                             /* 便于队列挂接 */
    VOS_UINT32                              ulSenderPid;                        /* 发送消息的PID */
    VOS_UINT16                              usOpId;
    VOS_UINT8                               ucPppId;
    VOS_UINT8                               ucPdnId;
    PS_BOOL_ENUM_UINT8                      enIsHandling;                       /* PS_TRUE:当前有节点正在处理 PS_FALSE:没有节点被处理 */
    VOS_UINT8                               aucReserved[3];
    APS_CMD_LINK_NODE_STRU                  stApsCmdNode;
    EHSM_CMD_LINK_NODE_STRU                 stEhsmCmdNode;
}PPPC_APS_MSG_LINK_NODE_STRU;

/** ****************************************************************************
* Name        : PPPC_PID_PDNID_MAPPING_STRU
*
* Description : ppp id和Pdn id映射信息
*******************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucPdnId;
    VOS_UINT8                                               ucPppId;
    PS_BOOL_ENUM_UINT8                                      enValidFlag;
    VOS_UINT8                                               aucReserved[1];
}PPPC_PID_PDNID_MAPPING_STRU;

/*******************************************************************************
* Name        : PPPC_CONTEXT_INFO_STRU
*
* Description : 存储HRPD(包括eHRPD)模块的上下文信息
*******************************************************************************/
typedef struct
{
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16               aenApplicationType[3];
    PS_BOOL_ENUM_UINT8                                      enIsSendOpenFlag;   /* 状态是Close的流的条数 */
    PS_BOOL_ENUM_UINT8                                      enIsDoingAcessAuth; /* 正在与BSC进行接入鉴权协商 */
    VOS_UINT8                                               ucAccessAuthLen;
    VOS_UINT8                                               aucReserv[2];
    CTTF_HRPD_PA_CONNECTION_STATUS_ENUM_UINT8               enConnectionStatus; /* 接入鉴权connection的状态 */
    VOS_UINT8                                               aucAccessAuthUserName[CNAS_CTTF_EHRPD_MAX_AUTHDATA_USERNAME_LEN+1]; /* 与BSC接入鉴权用户名 */
    VOS_UINT32                                              ulRandu;
    VOS_UINT32                                              ulPppInactTimerLen;  /* MAX PPP Inactive Timer Len */
}PPPC_HRPD_CONTEXT_STRU;

/*******************************************************************************
* Name        : PPPC_CONTEXT_INFO_STRU
*
* Description : ppp模块上下文信息
*******************************************************************************/
typedef struct
{
    MODEM_ID_ENUM_UINT16                                    enModemId;
    TAF_APS_PPP_CDATA_DIAL_MODE_ENUM_UINT8                  enDialMode;         /* PPP默认为中继模式 TAF_APS_PPP_CDATA_DIAL_MODE_RELAY */
    PPPC_RAT_MODE_ENUM_UINT8                                enRatMode;          /* 当前网络模式1X/HRPD/eHRPD */
    VOS_UINT32                                              ulSendPid;          /* 发起激活的Pid */
    VOS_UINT16                                              usMru;              /* PPPC任务启动时赋值，其他时候不允许修改该值 */
    PS_BOOL_ENUM_UINT8                                      enCaveEnable;       /* CAVE算法使能开关，0不支持CAVE算法 */
    TAF_APS_PPP_ADDR_TYPE_ENUM_UINT8                        enPdnType;
    VOS_UINT32                                              ulUserNameLen;      /* 长度不会超过TAF_APS_PPP_MAX_AUTHDATA_USERNAME_LEN */
    VOS_UINT32                                              ulPasswordLen;      /* 长度不会超过TAF_APS_PPP_MAX_AUTHDATA_PASSWORD_LEN */
    VOS_UINT8                                               aucUserName[TAF_APS_PPP_MAX_AUTHDATA_USERNAME_LEN+1]; /* 鉴权用户名 */
    VOS_UINT8                                               aucPassword[TAF_APS_PPP_MAX_AUTHDATA_PASSWORD_LEN+1]; /* 鉴权密码 */
    VOS_UINT32                                              ulPppIdBitMask;     /* 用bit位来记录当前已使用的PppId,从bit1开始表示 */
    VOS_UINT32                                              aulPppIdMapPdnId[PPP_MAX_USER_NUM + 1];   /* 映射PdnId,用bit来映射当前PppId对应的多个PdnId */
    PPPC_HRPD_CONTEXT_STRU                                  stHrpdContext;
}PPPC_CONTEXT_INFO_STRU;

/** ****************************************************************************
* Name        : PPPC_DATA_UL_ENCAP_MEM_STRU
*
* Description : 上行数据储存在PPPC的内存结构,为数组形式有两个元素.
*******************************************************************************/
typedef struct
{
    TTF_MEM_ST                                             *pstDataPtr;         /* 储存上行数据的内存,长度1600字节 */
    PS_BOOL_ENUM_UINT8                                      enPtrIsUsed;        /* 指示内存是否使用 */
    VOS_UINT8                                               aucReserv[3];
} PPPC_DATA_UL_ENCAP_MEM_STRU;

/** ****************************************************************************
* Name        : PPPC_HRPD_RESERVATION_QOS_INFO_STRU
*
* Description : 应用通知PPPC发起QoS协商时携带的信息
*******************************************************************************/
typedef struct
{
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16               enApplicationType;
    VOS_UINT8                                               ucNumFwdReservations;                                           /**< Number of reservation labels 1..CTTF_HRPD_MAX_NUM_RESERVATIONS_PER_QOS_REQ */
    VOS_UINT8                                               ucNumRevReservations;                                           /**< Number of reservation labels 1..CTTF_HRPD_MAX_NUM_RESERVATIONS_PER_QOS_REQ */
    CTTF_HRPD_QOS_STRU                                      astFwdReservations[CTTF_HRPD_MAX_NUM_RESERVATIONS_PER_QOS_REQ]; /**< Parameters for each reservation */
    CTTF_HRPD_QOS_STRU                                      astRevReservations[CTTF_HRPD_MAX_NUM_RESERVATIONS_PER_QOS_REQ]; /**< Parameters for each reservation */
} PPPC_HRPD_RESERVATION_QOS_INFO_STRU;

/** ****************************************************************************
* Name        : PPPC_HRPD_RESERVATION_QOS_CLOSE_INFO_STRU
*
* Description : 应用通知PPPC发起QoS协商时携带的信息
*******************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucNumFwdReservations;                                           /**< Number of reservation labels 1..CTTF_HRPD_MAX_NUM_RESERVATIONS_PER_QOS_REQ */
    VOS_UINT8                                               ucNumRevReservations;                                           /**< Number of reservation labels 1..CTTF_HRPD_MAX_NUM_RESERVATIONS_PER_QOS_REQ */
    VOS_UINT8                                               aucReserv1[2];
    VOS_UINT8                                               aucFwdReservationLabels[CTTF_HRPD_MAX_NUM_RESERVATIONS_PER_QOS_REQ];
    VOS_UINT8                                               aucRevReservationLabels[CTTF_HRPD_MAX_NUM_RESERVATIONS_PER_QOS_REQ];
}PPPC_HRPD_RESERVATION_QOS_CLOSE_INFO_STRU;

/** ****************************************************************************
* Name        : PPPC_ACT_HRPD_DELAY_PROC_TIMER_STRU
*
* Description : 初始接入鉴权时收到激活请求延时处理结构
*******************************************************************************/
typedef struct
{
    HTIMER                                                  hDelayProcTimer;    /* 需要延时处理的定时器 */
    VOS_VOID                                               *pstMsgPtr;          /* 储存需要延时处理的激活消息内容 */
}PPPC_ACT_HRPD_DELAY_PROC_TIMER_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_VOID PPPC_HDLC_HARD_ProcAsFrmPacket
(
    VOS_UINT16       usPppId,
    VOS_UINT16       usProtocol,
    TTF_MEM_ST      *pstMem
);

extern VOS_UINT32 PPPC_HDLC_HARD_FrmPacket
(
    PPP_ID                              usPppId,
    VOS_UINT16                          usProtocol,
    TTF_LINK_ST                        *pstUlDataQ,
    VOS_UINT32                         *pulDealCurCnt
);

extern VOS_UINT32 PPPC_HDLC_HARD_DefPacket
(
    TTF_LINK_ST                        *pstDlDataQ,
    VOS_UINT16                          usPppId,
    VOS_UINT32                         *pulDealCnt
);

extern VOS_UINT32 PPPC_Init(enum VOS_INIT_PHASE_DEFINE InitPhase );
extern VOS_VOID PPPC_MsgProc( struct MsgCB * pMsg );

extern VOS_VOID PPPC_ShowDLProcStats(VOS_VOID);
extern VOS_VOID PPPC_ShowULProcStats(VOS_VOID);
VOS_VOID PPPC_1X_IncreaseNegoRcvCnt(VOS_VOID);
VOS_VOID PPPC_HRPD_IncreaseNegoRcvCnt(VOS_VOID);

VOS_UINT8 *PPP_GetUlEncapDataPtr(VOS_VOID);
VOS_VOID PPP_InitEncapDataPtr(VOS_VOID);
VOS_VOID PPPC_ClearUlEncapMem(VOS_VOID);

VOS_UINT16 PPPC_HRPD_GetAppType(VOS_VOID);
VOS_UINT8 PPPC_HRPD_GetStreamNumber(VOS_UINT8 ucPppId);

TTF_MEM_ST *PPPC_AdapterMBuftoTtfMemory
(
    PMBUF_S                            *pstMBuf,
    VOS_UINT32                          ulMemPoolId,
    VOS_UINT32                          ulOffset,
    VOS_UINT32                          ulLength
);

VOS_VOID PPPC_IsReadyToRespActCmd(VOS_VOID* pPppInfo);
VOS_VOID PPPC_JudgeApsCmdRseultWhenDeleteCB(VOS_UINT8 ucPppId);
VOS_VOID PPPC_ClearUlDataQ(VOS_VOID);
VOS_VOID PPPC_ClearDlDataQ(VOS_VOID);
VOS_VOID PPPC_SendApsDeactNotify(VOS_UINT8 ucPppId);
VOS_UINT32 PPPC_ULSendNegoFrame(PMBUF_S *pstMBuf, VOS_UINT32 ulRPIndex);
VOS_VOID PPPC_RespApsDeActCmd(VOS_UINT32 ulResult);
VOS_UINT32 PPPC_GetPppIdByPdn(VOS_UINT8 ucPdnId, VOS_UINT8 *pucPppId);
VOS_UINT32 PPPC_1XHrpdGetPdnId(VOS_UINT16 usPppId, VOS_UINT8 *pucPdnId);
VOS_UINT32 PPPC_SndDlDataNotify(VOS_VOID);
VOS_UINT32 PPPC_SndUlDataNotify(VOS_VOID);
VOS_VOID PPPC_MappingPppIdandPdnId(VOS_UINT8 ucPppId, VOS_UINT8 ucPdnId);
VOS_VOID PPPC_ClearMappingByPppId(VOS_UINT8 ucPppId);
VOS_VOID PPPC_ActReqMsgNodeProc(VOS_VOID);
VOS_VOID PPPC_DeActReqMsgNodeProc(VOS_VOID);
TAF_APS_PPP_CDATA_DIAL_MODE_ENUM_UINT8 PPPC_GetDialMode(VOS_VOID);
VOS_UINT32 PPPC_RcvCdsUlFrame
(
    VOS_UINT8                           ucPdnId,
    TTF_MEM_ST                         *pstTtfMemory,
    PPPC_RAT_MODE_ENUM_UINT8            enRatMode,
    PS_DATA_EXT_INFO_STRU              *pstUlDataInfo,
    VOS_UINT8                           ucPppId
);
VOS_VOID PPP_SendRlpDlDatatoCds
(
    VOS_UINT16                          usStartSeq,
    VOS_UINT16                          usEndSeq,
    VOS_UINT8                           ucPdnId,
    TTF_MEM_ST                         *pstData,
    PPPC_RAT_MODE_ENUM_UINT8            ucRatMode
);
VOS_UINT32 PPPC_GetCurrentPdnId(VOS_UINT8 *pucPdnId);
VOS_UINT32 PPPC_1X_GetPdnId(VOS_UINT8 ucPppId, VOS_UINT8 *pucPdnId);
PPPC_RAT_MODE_ENUM_UINT8 PPPC_GetRatMode(VOS_VOID);
VOS_UINT32 PPPC_GetCurrentPppId
(
    PPPC_RAT_MODE_ENUM_UINT8            enRateMode,
    VOS_UINT8                           ucStreamNum,
    VOS_UINT8                          *pucPppId
);
VOS_UINT16 PPP_GetDefaultMru(VOS_VOID);
VOS_UINT16 PPPC_GetModemId(VOS_VOID);
VOS_VOID PPPC_SendEhsmDetachNotify(VOS_UINT8 ucPppId);
VOS_VOID PPPC_RespApsActFail
(
    APS_PPP_ACT_REQ_STRU               *pstPppActReq
);
VOS_VOID PPPC_RespApsDeActFail
(
    APS_PPP_DEACT_REQ_STRU             *pstPppDeActReq
);
VOS_VOID PPPC_RespEhsmAttachFail
(
    CNAS_CTTF_EHRPD_ATTACH_REQ_STRU    *pstAttachReq
);
VOS_VOID PPPC_RespEhsmPdnConnectFail
(
    CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU  *pstPdnConnectReq
);
VOS_VOID PPPC_RespEhsmPdnDisconnect
(
    CNAS_CTTF_EHRPD_RSLT_ENUM_UINT8     enResult,
    CNAS_CTTF_EHRPD_PDN_DISC_REQ_STRU  *pstPdnDisconnectReq
);
VOS_VOID PPPC_SendPdnConnectCnf
(
    PPPC_APS_MSG_LINK_NODE_STRU        *pstMsgLinkNode,
    VOS_UINT32                          ulResult
);
VOS_VOID PPPC_DequeueProc(PPPC_PROC_LINK_DIRECTION_ENUM_UINT16 enProcDire);
VOS_VOID PPPC_AwakeSelfReachMaxProcTimeoutProc(VOS_VOID);
VOS_VOID PPPC_ChangeAccessAuthState
(
    PS_BOOL_ENUM_UINT8                  enIsDoingAcessAuth,
    VOS_UINT8                           ucPppId
);
VOS_UINT32 PPPC_HRPD_GetFileReq(USIMM_DEF_FILEID_ENUM_UINT32 enFileID);
PS_BOOL_ENUM_UINT8 PPPC_IsCaveAlgorithmEnable(VOS_VOID);
VOS_VOID PPPC_SaveAccessAuthUserNameInfo(VOS_UINT8 *pstMsg);
VOS_UINT32 PPPC_HRPD_GetAppTypeByStreamNum
(
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16  *penAppType,
    VOS_UINT8                                   ucStreamNum
);
VOS_VOID PPPC_SetInitAccessAuthMode(PS_BOOL_ENUM_UINT8 enAccessAuth);
PS_BOOL_ENUM_UINT8 PPPC_GetInitAccessAuthMode(VOS_VOID);
VOS_VOID PPPC_TafActReqProc
(
    APS_PPP_ACT_REQ_STRU               *pstPppActReq
);
VOS_VOID PPPC_MsgEhsmProc(struct MsgCB * pMsg);
PS_BOOL_ENUM_UINT8 PPPC_EhsmDetachProcWhenAccessAuth(VOS_VOID);
VOS_VOID PPPC_RespApsDeActDirect
(
    VOS_UINT32                          ulResult,
    APS_PPP_DEACT_REQ_STRU             *pstPppDeActReq
);
VOS_VOID PPPC_RespEhsmDetach
(
    CNAS_CTTF_EHRPD_RSLT_ENUM_UINT8     enResult,
    CNAS_CTTF_EHRPD_DETACH_REQ_STRU    *pstDetachReq
);
VOS_VOID PPPC_AwakeSelfProcUlDataTimeoutProc(VOS_VOID);
PMBUF_S *PPPC_AdapterTtfMemorytoMBuf(TTF_MEM_ST *pstTtfMem);
VOS_VOID PPPC_SaveRunCaveRandu(VOS_UINT32 ulRandu);

VOS_UINT32 PPPC_UIM_MD5ChapAuthReq(PPPINFO_S *pstPppInfo, PPPC_AUTH_MSG_STRU *pstAuthMsg);

VOS_VOID PPPC_SendEhsmPdnDisconnectNotify(VOS_UINT8 ucPdnId);

PS_BOOL_ENUM_UINT8 PPPC_IsPdnIdUsing(VOS_UINT8 ucPdnId);

VOS_VOID PPPC_ReceiveLCPTermReq(VOS_UINT8 ucPppId);

VOS_VOID PPPC_JudgeCmdRseultWhenDeleteCB(VOS_UINT8 ucPppId);

VOS_VOID PPPC_StopAllAccessAuthDelayProcTimer(VOS_VOID);
VOS_VOID PPPC_HRPD_SendRpaAccessAuthRsp
(
    CTTF_HRPD_PPP_ACCESS_AUTH_RESULT_ENUM_UINT8 enResult
);
VOS_VOID PPPC_HRPD_SendRpaAccessAuthPhaseInd(VOS_VOID);
VOS_VOID PPPC_GetPppAuthInfo(CTTF_PPPC_AUTH_INFO_STRU *pstPppAuthInfo);
VOS_VOID PPPC_SetupPpp(VOS_UINT8 ucPppId);
VOS_VOID PPPC_SetAuthSwitch
(
    VOS_UINT32        ulPapSwitch,
    VOS_UINT32        ulChapSwitch
);
VOS_VOID PPPC_AccessAuthDelayProcTimeoutProc
(
    PPPC_ACCESS_AUTH_ACT_MODE_ENUM_UINT16 enActMode
);

VOS_VOID PPPC_AccessAuthDelayTimeoutproc();

VOS_UINT32 PPPC_DeletePppId(VOS_UINT8 ucPppId);

VOS_VOID PPPC_RespEhsmPdnDisconnectCmd(VOS_UINT32 ulResult);

VOS_VOID PPPC_RespEhsmPdnConnectCmd
(
    VOS_VOID                           *pVsncpInfo,
    VOS_UINT32                          ulResult
);
VOS_VOID PPPC_StartPppInactiveTimer(VOS_UINT8 ucPppId);
VOS_VOID PPPC_InactivePppTimeoutProc(VOS_UINT8 ucPppId);
VOS_VOID PPPC_ActAccessAuth(PPPINFO_S *pstPppInfo);
VOS_VOID PPPC_SetAttachErrorCode(CNAS_CTTF_EHRPD_ERROR_CODE_ENUM_UINT16  enErrorCode);
VOS_VOID PPPC_SendEhsmModifyInd(PPPVSNCPINFO_S *pstVSNCPInfo);
VOS_VOID PPPC_ExtractPdnInfoFromHeadNode(VOS_VOID);
VOS_VOID PPPC_HRPD_SendOpenStreamReq(VOS_VOID);


#if (FEATURE_ON == FEATURE_MULTI_MODEM)
extern VOS_UINT32 I1_PIH_RegUsimCardStatusIndMsg(VOS_UINT32 ulRegPID);
#endif

#if (PPPC_FEATURE_ON == PPPC_FEATURE_MULTI_MODEM)
extern TAF_APS_PPP_LINK_STATUS_ENUM_UINT8 I1_TAF_APS_GetPppLinkStatus(VOS_VOID);
#endif

#if (PPPC_FEATURE_ON == PPPC_FEATURE_MODEM_2)
extern TAF_APS_PPP_LINK_STATUS_ENUM_UINT8 I2_TAF_APS_GetPppLinkStatus(VOS_VOID);
#endif


#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _PPP_VAR_H_ */



