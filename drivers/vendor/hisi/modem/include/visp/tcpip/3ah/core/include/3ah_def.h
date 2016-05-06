/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              3ah_def.h
*
*  Project Code: VISPV100R007
*   Module Name: ETH OAM 3AH 
*  Date Created: 2008-2-28
*        Author: LY(57500)
*   Description: 3AH模块的宏和枚举
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2008-2-28  LY(57500)     Create the first version.
*
*******************************************************************************/
#ifndef _3AH_DEF_H_
#define _3AH_DEF_H_

#ifdef __cplusplus
extern "C"{
#endif

#ifndef MACADDRLEN
#define MACADDRLEN       6       /*physical地址长度*/
#endif

#define VLANTYPE_DOT1Q   0x8100  /* VLAN 802.1q格式*/
#define DOT1Q_TAG_SIZE   4


#define OAM3AH_LINKEVENT_NUM        4       /* 3ah支持的链路事件总数    */

#define SLOW_PROTOCOL_SUBTYPE_OAM   0x03    /* 慢协议OAM子类型          */

#define OAMPDU_HEADER_LEN           18      /* OAMPDU 头长度(不含TLV)   */

#define OAMPDU_OUI_LENGTH           3       /* OUI Length               */

#define OAMPDU_VERSION              0x01    /* OAM Version              */

#define OAMPDU_MAX_TX_COUNT         10      /* max number of OAMPDUs send per period */

/* min frame size of OAMPDU,exclude FCS */
#define OAMPDU_MIN_FRAME_SIZE       60

/* frame size of OAMPDU,inlude FCS      */
#define OAMPDU_MAX_PDUSIZE          1518    /* max size     */
#define OAMPDU_MIN_PDUSIZE          64      /* min size     */
#define OAMPDU_DEFAULT_PDUSIZE      128     /* default size */

/* for errored frame seconds summary, timer interval always 1s */
#define OAM3AH_FRMSECSUM_INTERVAL   1000

/* OAM configuration field default:
   OAM MODE: Active mode (1)   
   Unidirectional Support: YES (1) -- 为支持PTN
   OAM Remote Loopback Support:Yes (1)
   Link Events:Support (1)
   Variable Retrieval:No (0)  
*/
#define OAM3AH_DEFAULT_OAM_CONFIG 0x0F /* binary: 0000 1111 */

/* info revision is start at zero,so the default value of remote info revision must different from zero */
#define OAM3AH_DEFAULT_REMOTE_INFO_REVISION     0x5555

/* the default window,in terms of 100ms */
#define OAM3AH_DEFAULT_ERR_SYMPRD_WINDOW            10
/* 错误符号周期事件窗口值配置模式为符号数模式时的默认值.协议规定默认值为1s内驱动能够接收的符号数，
   产品也不清楚符号是如何定义的,所以这里将符号理解为字节数.
   该默认值是按照100M Bit/s算出来的，即(100*1024*1024)/8=13107200）*/
#define OAM3AH_DEFAULT_ERR_SYMPRD_WINDOW_SYMMODE    13107200
#define OAM3AH_DEFAULT_ERR_FRAME_WINDOW             10
#define OAM3AH_DEFAULT_ERR_FRMPRD_WINDOW            10
/* 错帧周期事件窗口值配置模式为帧数目模式时的默认值.协议规定默认值为1s内驱动能够接收的最小尺寸帧数目，
   该默认值是按照100M Bit/s，最小尺寸帧大小64字节算出来的，即(100*1024*1024)/8/64=204800）*/
#define OAM3AH_DEFAULT_ERR_FRMPRD_WINDOW_NUMMODE    204800
#define OAM3AH_DEFAULT_ERR_FRMSECSUM_WINDOW         600

/* the default threshold,four link event is same  */
#define OAM3AH_DEFAULT_ERR_THRESHOLD            1

/* default send times of link event oampdu  */
#define OAM3AH_LINK_EVENT_SEND_TIMES            3

/* for reset fsm */
#define OAM3AH_FALSE                        0
#define OAM3AH_TRUE                         1

/* define link event enable & disable */
#define OAM3AH_LINK_EVENT_DISABLE               0
#define OAM3AH_LINK_EVENT_ENABLE                1

/*define  min & max OAMPDU size*/
#define OAM3AH_MIN_PDUSIZE                  64
#define OAM3AH_MAX_PDUSIZE                  1518

/* define min & max lb test pkt size */
#define OAM3AH_MIN_LBTESTPKT_SIZE           48
#define OAM3AH_MAX_LBTESTPKT_SIZE           1500

/* debug level mask */
#define OAM3AH_DBG_OAMPDU_MASK              0x01    /* 报文调试掩码         */
#define OAM3AH_DBG_FSMTRANS_MASK            0x02    /* 状态机迁移调试掩码   */
#define OAM3AH_DBG_LBDATA_MASK              0x04    /* 环回测试数据调试掩码 */
#define OAM3AH_DBG_ERR_MASK                 0x08    /* 错误情况输出掩码     */

#define OAM3AH_DBG_ALL                      0x0F    /* 所有调试开关 */

/* detect interval(ms) & code define    */
#define OAM3AH_DETECT_INTERVAL_3                3
#define OAM3AH_DETECT_INTERVAL_10               10
#define OAM3AH_DETECT_INTERVAL_20               20
#define OAM3AH_DETECT_INTERVAL_50               50
#define OAM3AH_DETECT_INTERVAL_100              100
#define OAM3AH_DETECT_INTERVAL_200              200
#define OAM3AH_DETECT_INTERVAL_500              500
#define OAM3AH_DETECT_INTERVAL_1000             1000

/* 默认探测周期 */
#define OMA3AH_DEFAULT_DETECT_INTERVAL          OAM3AH_DETECT_INTERVAL_1000

/* 链路超时时间是探测时间的五倍 */
#define OAM3AH_LOSTTIME_MULTI                   5

/* 默认链路超时周期 */
#define OAM3AH_DEFAULT_LOST_TIME                (OAM3AH_DETECT_INTERVAL_1000 * OAM3AH_LOSTTIME_MULTI)

/* lb ctrl lost time */
#define OAM3AH_LB_TIMEOUT_INTERVAL_2000         2000

/*环回报文重发的次数*/
#define OAM3AH_LB_CMD_RETRY_TIMES                3

/* code interval code(保存在oam pdu 中info tlv定义的 configuration字段中的3位保留字段) */
#define OAM3AH_DETECT_CODE_1000                 0x0 /* 三位表示: 000, 标准探测间隔  */
#define OAM3AH_DETECT_CODE_3                    0x3 /* 三位表示: 011, 扩展探测间隔;兼容数通 */
#define OAM3AH_DETECT_CODE_10                   0x1 /* 三位表示: 001, 扩展探测间隔;兼容数通 */
#define OAM3AH_DETECT_CODE_20                   0x2 /* 三位表示: 010, 扩展探测间隔  */
#define OAM3AH_DETECT_CODE_50                   0x4 /* 三位表示: 100, 扩展探测间隔  */
#define OAM3AH_DETECT_CODE_100                  0x5 /* 三位表示: 101, 扩展探测间隔  */
#define OAM3AH_DETECT_CODE_200                  0x6 /* 三位表示: 110, 扩展探测间隔  */
#define OAM3AH_DETECT_CODE_500                  0x7 /* 三位表示: 111, 扩展探测间隔  */

/* local stable & local evaluating two-bit encoding     */
/* remote stable & remote evaluating two-bit encoding   */
enum
{
    OAM3AH_DSCVR_STATUS_UNSATISFIED,    /* Unsatisfied,Discovery can not completed  */
    OAM3AH_DSCVR_STATUS_NOT_COMPLETED,  /* Discovery process has not completed      */
    OAM3AH_DSCVR_STATUS_SATISFIED,      /* Discovery process has completed          */
    OAM3AH_DSCVR_STATUS_RESERVED,       /* Reserved                                 */
};

/* parse field action define */
typedef enum
{
    PARSER_FORWARD = 0,  /* 00 = Device is forwarding non-OAMPDUs to higher sublayser        */
    PARSER_LB,           /* 01 = Device is looping back non-OAMPDUs to the lower sublayer    */
    PARSER_DISCARD,      /* 10 = Device is discarding non-OAMPDUs                            */
    PARSER_RESERVED,     /* 11 = Reserved. This value shall not be sent.If the value 11 is 
                            received,it should be ignored and not change the last received value. */
}OAM3AH_PARSER_ACTION_E;

/* multiplexer field action define */
typedef enum
{
    MULTIPLEXER_FORWARD = 0,            /* 0 = Device is forwarding non-OAMPDU */
    MULTIPLEXER_DISCARD = 1             /* 1 = Device is discarding non-OAMPDU */
}OAM3AH_MULTIPLEXER_ACTION_E;

/* loopback control code in loopback OAMPDU */
enum
{
    OAM3AH_ENABLE_REMOTE_LB = 1,    /* enable LB CMD    */
    OAM3AH_DISABLE_REMOTE_LB = 2,   /* disable LB CMD   */
    OAM3AH_REMOTE_LB_CMD_RESERVED
};

/* LOCAL & REMOTE discovery status */
enum 
{
    OAM3AH_LOCAL_DISCOVERY_COMPLETED = 1,   /* local has completed discovery    */
    OAM3AH_REMOTE_DISCOVERY_COMPLETED,      /* remote has completed discovery   */
};

/* OAMPDU CODE define */
typedef enum
{
    OAM3AH_CODE_INFORMATION = 0,
    OAM3AH_CODE_EVENT_NOTIFICATIOIN,
    OAM3AH_CODE_VAR_REQUEST,
    OAM3AH_CODE_VAR_RESPONSE,
    OAM3AH_CODE_LOOPBACK_CONTROL,
    OAM3AH_CODE_DUPLICATE_EVENT_NOTIFICATION,
    OAM3AH_CODE_UNSOPPORTED,
    
    OAM3AH_CODE_ORG_SPECIFIC = 0xfe,

    OAM3AH_CODE_RESERVED
}OAM3AH_OAMDPU_CODE_E;

/* oampdu code for statistic */
enum
{
    OAM3AH_INFO_OAMPDU = 1,
    OAM3AH_EVENT_OAMPDU,
    OAM3AH_LBCTL_OAMPDU,
    OAM3AH_DROP_OAMPDU,
    OAM3AH_FAULT_OAMPDU,
};

/* OAM3AH information tlv type define */
typedef enum
{
    OAM3AH_END_OF_INFO_TLV = 0,
    OAM3AH_LOCAL_INFORMATION,
    OAM3AH_REMOTE_INFORMATION,

    OAM3AH_ORG_SPEC_INFORMATION = 0xfe,
    OAM3AH_RESERVED_INFORMATION,
}OAM3AH_INFORMATION_TYPE_E;

/* max info tlv in send oampdu  */
#define OAM3AH_INFO_TLV_NUM     3

/* 事件类型枚举定义         */
typedef enum enLinkEventType
{
    OAM3AH_END_OF_EVENT_TLV = 0,
    OAM3AH_ERR_SYMPRD_EVENT = 1,    /* 错误符号周期事件 */
    OAM3AH_ERR_FRAME_EVENT,         /* 错帧事件         */
    OAM3AH_ERR_FRMPRD_EVENT,        /* 错帧周期事件     */
    OAM3AH_ERR_FRMSECSUM_EVENT,     /* 错帧秒事件       */

    OAM3AH_ORG_SPEC_EVENT = 0xfe,    /* 组织自定义事件,当前不支持发送和解析 */
    OAM3AH_RESERVED_EVENT,          /* 保留事件         */   
}OAM3AH_LINKEVENT_TYPE_E;

/* 故障类型枚举定义         */
typedef enum enFaultType
{
    OAM3AH_FAULT_LINKFAULT,         /* 链路故障         */
    OAM3AH_FAULT_DYINGGASP,         /* 致命故障         */
    OAM3AH_FAULT_CRITICALEVT,       /* 紧急事件         */
}OAM3AH_FAULT_TYPE_E;

   
/* define state field bit flags */
#define OAM3AH_STATE_MAIN_FIELD     0xff00
#define OAM3AH_STATE_SUB_FIELD      0x00ff

/* 状态机主状态枚举,*/
/* 如对状态机状态有增删要同步g_sz3ahFsmIdle,g_asz3ahFsmDscvr,g_asz3ahFsmLb字符串数组变量 */
typedef enum
{
    OAM3AH_STATE_IDLE,              /* 空闲状态,未使能3ah   */
    OAM3AH_STATE_DISCOVERY = 0x100, /* 发现状态             */
    OAM3AH_STATE_LOOPBACK = 0x200,  /* 环回状态             */
}OAM3AH_STATE_E;

/* 发现状态枚举定义 */
/* 如对状态机状态有增删要同步g_sz3ahFsmIdle,g_asz3ahFsmDscvr,g_asz3ahFsmLb字符串数组变量 */
typedef enum
{
    OAM3AH_DSCVR_NONE = OAM3AH_STATE_DISCOVERY,
        
    OAM3AH_DSCVR_FAULT,
    OAM3AH_DSCVR_PASSIVE_WAIT,
    OAM3AH_DSCVR_ACTIVE_SEND_LOCAL,
    OAM3AH_DSCVR_SEND_LOCAL_REMOTE,
    OAM3AH_DSCVR_SEND_LOCAL_REMOTE_OK,
    OAM3AH_DSCVR_SEND_ANY,  
    
    OAM3AH_DSCVR_UNKNOWN,
}OAM3AH_DISCOVERY_E;

/* 环回状态枚举定义 */
/* 如对状态机状态有增删要同步g_sz3ahFsmIdle,g_asz3ahFsmDscvr,g_asz3ahFsmLb字符串数组变量 */
typedef enum
{
    OAM3AH_LB_IDLE = OAM3AH_STATE_LOOPBACK,
        
    OAM3AH_LB_NO,           /* no loopback in progress                  */
    OAM3AH_LB_INITIATING,   /* start loopback process with it's perr    */
    OAM3AH_LB_REMOTE,       /* in loopback mode with it's peer          */
    OAM3AH_LB_TERMINATING,  /* start terminating loopback               */
    OAM3AH_LB_LOCAL,        /* in loopback mode(remote controlled)      */
    OAM3AH_LB_UNKNOWN,      /* unknown state                            */
}OAM3AH_LBPK_STATE_E;

/* 为支持状态机变迁函数处理特定义如下宏 */
typedef enum
{
    OAM3AH_INVALID = 0, /* 非法状态                 */
    OAM3AH_DISCOVERING, /* 含OAM3AH_STATE_IDLE状态及小于OAM3AH_DSCVR_SEND_ANY的DSCVR状态 */
    OAM3AH_SENDANY,     /* OAM3AH_DSCVR_SEND_ANY    */
    OAM3AH_LBREMOTE,    /* OAM3AH_LB_REMOTE         */
    OAM3AH_LBLOCAL,     /* OAM3AH_LB_LOCAL          */
    OAM3AH_LBING,       /* 除OAM3AH_LB_REMOTE/OAM3AH_LB_LOCAL外的环回处理中间状态 */
}OAM3AH_FP_STATE_E;

/* main state */
#define OAM3AH_MAIN_STATE(pstPorInfo) \
    ((pstPorInfo)->ulFsmState & OAM3AH_STATE_MAIN_FIELD)

/* judge discovery is completed or not */
#define OAM3AH_DISCOVERY_COMPLETED(pstPorInfo) \
    ((pstPorInfo)->ulFsmState >= OAM3AH_DSCVR_SEND_ANY)

/* judge discovery process status */
#define OAM3AH_DISCOVERY_PROCESS_STATUS(pstPorInfo) \
    ((pstPorInfo)->usDscvrProcessStatue)
    
/* local discover status */
#define OAM3AH_LOCAL_DSCVR_STATUS(pstPorInfo) \
    ((pstPorInfo)->unFlags.s.uslclDscvrStatus)

/* remote discover status */
#define OAM3AH_REMOTE_DSCVR_STATUS(pstPortInfo) \
    ((pstPortInfo)->unFlags.s.usRmtDscvrStatus)

/* remote revision */
#define OAM3AH_REMOTE_INFO_REVISION(pstPorInfo) \
    ((pstPorInfo)->stRmtInfoTlv.usRevision)
    
/* local info revision */
#define OAM3AH_LOCAL_INFO_REVISION(pstPortInfo) \
    ((pstPortInfo)->stLclInfoTlv.usRevision)

/* local oamconfig */
#define OAM3AH_LOCAL_OAMCONFIG(pstPortInfo) \
    ((pstPortInfo)->stLclInfoTlv.unOamCfg.ucConfig)

/* remote oamconfig */
#define OAM3AH_REMOTE_OAMCONFIG(pstPortInfo) \
    ((pstPortInfo)->stRmtInfoTlv.unOamCfg.ucConfig)

/* local oampdu cfg */
#define OAM3AH_LOCAL_MAXOAMPDUSIZE(pstPortInfo) \
    ((pstPortInfo)->stLclInfoTlv.usOamPduCfg)
    
/* remote oampdu cfg */
#define OAM3AH_REMOTE_MAXOAMPDUSIZE(pstPortInfo) \
    (VOS_NTOHS((pstPortInfo)->stRmtInfoTlv.usOamPduCfg))

/* remote state valid */
#define OAM3AH_REMOTE_STATE_VALID(pstPortInfo) \
    ( OAM3AH_DSCVR_STATUS_NOT_COMPLETED != (pstPortInfo)->unFlags.s.uslclDscvrStatus)

/* local detect interval */
#define OAM3AH_LOCAL_DETECTINTERVAL(pstPortInfo) \
    ((pstPortInfo)->stLclInfoTlv.unOamCfg.s.ucDetectInterval)

/* remote detect interval */
#define OAM3AH_REMOTE_DETECTINTERVAL(pstPortInfo) \
    ((pstPortInfo)->stRmtInfoTlv.unOamCfg.s.ucDetectInterval)

/* lcl board state */
#define OAM3AH_BOARDSTATE(pstPortInfo) \
    ((pstPortInfo)->stOrgSpecInfo.ulLclBoardState)

/* 0xec: 11101100 */
/* we just care about bit 7 6 5 3 2 in OAM Configuration field of Info TLV */
/* bit 7~5: Detect Interval */
/* bit 4: Variable Retrieval */
/* bit 3: Link Event Support */
/* bit 2: OAM LoopBack Support */
/* bit 1: Unidirectional Support */
/* bit 0: OAM mode */
#define OAM3AH_LOCAL_SATISFIED(pstPortInfo) \
    (((pstPortInfo)->stLclInfoTlv.unOamCfg.ucConfig & 0xe0) \
     == ((pstPortInfo)->stRmtInfoTlv.unOamCfg.ucConfig & 0xe0))

/* 两端是否都是被动模式的判断宏 */
#define OAM3AH_BOTH_PASSIVE_MODE(pstPortInfo) \
((OAM3AH_PASSIVE_MODE == ((pstPortInfo)->stLclInfoTlv.unOamCfg.ucConfig & 0x1)) \
  && (OAM3AH_PASSIVE_MODE == ((pstPortInfo)->stRmtInfoTlv.unOamCfg.ucConfig & 0x1)))
     
/* fault bit in oampdu flag field */
#define OAM3AH_PDU_FLAG_LINKFAULT(pstPortInfo)\
    ((pstPortInfo)->unFlags.s.usLinkFalut)
#define OAM3AH_PDU_FLAG_DYINGGASP(pstPortInfo)\
    ((pstPortInfo)->unFlags.s.usDyingGasp)
#define OAM3AH_PDU_FLAG_CRITICALEVENT(pstPortInfo)\
    ((pstPortInfo)->unFlags.s.usCriticalEvent)

/* get Local Multiplexer and Parser Action */
#define OAM3AH_LOCAL_MUX_ACTION(pstPortInfo)\
    ((pstPortInfo)->stLclInfoTlv.unState.s.ucMuxAction)
#define OAM3AH_LOCAL_PAR_ACTION(pstPortInfo)\
        ((pstPortInfo)->stLclInfoTlv.unState.s.ucParserAction)
        
/* get Remote Multiplexer and Parser Action */
#define OAM3AH_REMOTE_MUX_ACTION(pstPortInfo)\
    ((pstPortInfo)->stRmtInfoTlv.unState.s.ucMuxAction)
#define OAM3AH_REMOTE_PAR_ACTION(pstPortInfo)\
        ((pstPortInfo)->stRmtInfoTlv.unState.s.ucParserAction)
        
/* Errored type */
#define OAM3AH_EVENT_TYPE(pstErrEvent)\
    ((pstErrEvent)->stLinkEventInfo.ulEventType)
    
/* Errored Window */
#define OAM3AH_EVENT_WINDOW(pstErrEvent) \
    ((pstErrEvent)->stLinkEventInfo.stDulErrWindows.ulDulLo)
    
/* Modified by z00208058/w00207740, 3AH链路事件窗口和门限规格扩展, 2012/5/12 */
/* Errored Threshold */
#define OAM3AH_EVENT_THRESHOLDHI(pstErrEvent) \
    ((pstErrEvent)->stLinkEventInfo.stDulErrThreshold.ulDulHi)

#define OAM3AH_EVENT_THRESHOLDLo(pstErrEvent) \
    ((pstErrEvent)->stLinkEventInfo.stDulErrThreshold.ulDulLo)

/* Errored Event Running Total */
#define OAM3AH_EVENT_TOTAL(pstErrEvent) \
    ((pstErrEvent)->stLinkEventInfo.ulEventRunTotal)

/* Errored Event time stamp */
#define OAM3AH_EVENT_TIMESTAMP(pstErrEvent) \
    ((pstErrEvent)->stLinkEventInfo.ulEventStamp)

/* local OAM mode */
#define OAM3AH_LOCAL_OAMMODE(pstPortInfo) \
    ((pstPortInfo)->stLclInfoTlv.unOamCfg.s.ucOamMode)

/* remote OAM mode */
#define OAM3AH_REMOTE_OAMMODE(pstPortInfo) \
    ((pstPortInfo)->stRmtInfoTlv.unOamCfg.s.ucOamMode)

/* Is 3ah enabled */
#define OAM3AH_IS_ENABLED(pstPortInfo) ( OAM3AH_ENABLE == (pstPortInfo)->ul3ahEnable)

/* Is 3ah disabled*/
#define OAM3AH_IS_DISABLED(pstPortInfo) ( OAM3AH_DISABLE == (pstPortInfo)->ul3ahEnable)

/* Is 3ah virtual enabled */
#define OAM3AH_IS_VIRTUAL_ENABLED(pstPortInfo) ( OAM3AH_VIRTUAL_ENABLE == (pstPortInfo)->ul3ahEnable)


/* 故障使能/状态记录位的宏定义*/
#define OAM3AH_FAULT_LINKFAULT_BIT          0x01    /* 链路事件 */
#define OAM3AH_FAULT_DYINGGASP_BIT          0x02    /* 致命故障 */
#define OAM3AH_FAULT_CRITICALEVT_BIT        0x04    /* 紧急事件 */

/* 故障位掩码 */
#define OAM3AH_FLAGS_CRITICAL_EVENTS        0x07

/* 位设置/清除/是否设置判断宏 */
#define OAM3AH_FLAG_SET(t,f)    ((t) |= (f))
#define OAM3AH_FLAG_CLR(t,f)    ((t) &= ~(f))
#define OAM3AH_FLAG_ISSET(t,f)  (((t) & (f)) ? 1 : 0)

/* 设置故障使能值宏 */
#define OAM3AH_SET_FAULT_ENABLE(pstPortInfo, ulFaultMask, ulEnableValue) \
{\
    /* 使能 */\
    if (ulEnableValue)\
    {\
        OAM3AH_FLAG_SET((pstPortInfo)->ulFaultEnable, (ulFaultMask));\
    }\
    /* 去使能 */\
    else\
    {\
        OAM3AH_FLAG_CLR((pstPortInfo)->ulFaultEnable, (ulFaultMask));\
    }\
}

/* 3AH模块定时器回调函数指针 */
typedef VOID (*OAM3AH_TIMER_FUNC)(ULONG ulIfIndex);

/* 3AH模块数据结构SID定义:模块内唯一 */
#define  SID_COMP_OAM3AH_PORTINFO_S         0x01
#define  SID_COMP_OAM3AH_DLL_S              0x02
#define  SID_COMP_OAM3AH_LINKEVT_S          0x03

/* 3AH模块告警宏 */
#define OAM_3AH_WARNINGOUT(pstWarnParam) TCPIP_WarningOut(WARNING_3AH, (pstWarnParam))

/* 事件标识第二个8位表示主要事件类型 */
#define OAM3AH_EVENT_MAIN_FIELD             0xff00

/* 状态机驱动本地事件定义 */
/* 如对事件类型有增删要同步g_asz3ahEvtCtrl字符串数组变量 */
typedef enum
{
    OAM3AH_EVT_CTRL_IDLE = 0x0000,

    OAM3AH_EVT_DISABLE,
    OAM3AH_EVT_ENABLE,

    OAM3AH_EVT_CFG_MUX_FWD,
    OAM3AH_EVT_CFG_MUX_DISCARD,
    OAM3AH_EVT_CFG_ENABLE_REMOTE_LB,
    OAM3AH_EVT_CFG_DISABLE_REMOTE_LB,

    OAM3AH_EVT_LOCAL_LOST_LINK,
    OAM3AH_EVT_LOCAL_LINK_FAULT,
    OAM3AH_EVT_LOCAL_LINK_OK,
    OAM3AH_EVT_LOCAL_DYING_GASP,
    OAM3AH_EVT_LOCAL_CRITICAL_EVENT,

    OAM3AH_EVT_LCL_UNSATISFIED,
    OAM3AH_EVT_LCL_SATISFIED,

    OAM3AH_EVT_LCL_HA,  /* 专门用于HA备份调试使用 */

    OAM3AH_EVT_RCV_INFO = 0x100,
    OAM3AH_EVT_LPBK_CMD = 0x200,
}OAM3AH_CTRL_EVENTS_E;

/* 状态机驱动对端事件定义 */
/* 如对事件类型有增删要同步g_asz3ahEvtRmt字符串数组变量 */
typedef enum
{
    OAM3AH_EVT_RCV_INFO_NONE = OAM3AH_EVT_RCV_INFO,
    OAM3AH_EVT_RMT_LINK_FAULT,
    OAM3AH_EVT_RMT_DYING_GASP,
    OAM3AH_EVT_RMT_CRITICAL_EVENT,
    
    OAM3AH_EVT_RMT_STATEINFO_CHANGED,
    OAM3AH_EVT_RMT_UNSATISFIED,
    OAM3AH_EVT_RMT_NOT_COMPLETED,
    OAM3AH_EVT_RMT_CHGDETECT,               /* 发现对端去改变探测周期不去清零统计信息 */
    OAM3AH_EVT_RMT_SATISFIED,
}OAM3AH_EVT_RMT_INFO_E;

/* 状态机驱动环回控制事件定义 */
/* 如对事件类型有增删要同步g_asz3ahEvtLb字符串数组变量 */
enum
{
    OAM3AH_EVT_LPBK_CMD_RSV = OAM3AH_EVT_LPBK_CMD,
    OAM3AH_EVT_ENABLE_REMOTE_LB,
    OAM3AH_EVT_DISABLE_REMOTE_LB,

    OAM3AH_EVT_LB_TIMEOUT
};

/* 报文发送接收标志 */
#define OAM3AH_PKT_SND      0
#define OAM3AH_PKT_RCV      1

/* NP MODE */
#define OAM3AH_NP_VISP      0   /* VISP软件模式 */
#define OAM3AH_NP_HALF      1   /* 半NP模式     */
#define OAM3AH_NP_FULL      2   /* 全NP模式     */

/* Organization Specific Information Tlv 中填充的主用板备用板值宏定义 */
#define OAM3AH_ORG_BOARDSTATE_MASTE 0xAB
#define OAM3AH_ORG_BOARDSTATE_SLAVE 0xBA

/* get board state from org spec tlv value */
/* 0 ------- OAM3AH_BOARD_STATE_NULL   (0)  (对端无通告)
   0xAB ---- OAM3AH_BOARD_STATE_MASTER (1)  (对端通告主用信息)
   0xBA ---- OAM3AH_BOARD_STATE_SLAVE  (2)  (对端通告备用信息)  
*/
#define OAM3AH_GET_BOARDSTATE(ulType) \
    (0 == (ulType)) ? OAM3AH_BOARD_STATE_NULL : \
    ((OAM3AH_ORG_BOARDSTATE_MASTE == (ulType)) ? OAM3AH_BOARD_STATE_MASTER : OAM3AH_BOARD_STATE_SLAVE)

/* get board type(org spec value) from board state */
/* OAM3AH_BOARD_STATE_NULL   (0) ----- 0    (不向对端通告)
   OAM3AH_BOARD_STATE_MASTER (1) ----- 0xAB (向对端通告主用信息)
   OAM3AH_BOARD_STATE_SLAVE  (2) ----- 0xBA (向对端通告备用信息)  
*/
#define OAM3AH_GET_BOARDTYPE(ulState) \
    (OAM3AH_BOARD_STATE_NULL == (ulState)) ? 0 : \
    ((OAM3AH_BOARD_STATE_MASTER == (ulState)) ? OAM3AH_ORG_BOARDSTATE_MASTE : OAM3AH_ORG_BOARDSTATE_SLAVE)


/* check oui validity,0-invalid; 1-valid */
#define OAM3AH_CHECK_OUI(aucOUI,ulOuiCheckRet) \
{\
    LONG lCmpRet1 = 1;\
    LONG lCmpRet2 = 1;\
    (VOID)VOS_Mem_Cmp((VOID*)(aucOUI), (VOID*)g_aucHuaweiOui[0], OAMPDU_OUI_LENGTH, &lCmpRet1);\
    (VOID)VOS_Mem_Cmp((VOID*)(aucOUI), (VOID*)g_aucHuaweiOui[1], OAMPDU_OUI_LENGTH, &lCmpRet2);\
    ulOuiCheckRet = !((lCmpRet1 != 0) && (lCmpRet2 != 0));\
}

#define OAM3AH_Timer_Resize(ulTimerId,ulNewTime)\
{\
    if(ulTimerId)\
    {\
        (VOID)VOS_Timer_Resize((ulTimerId),(ulNewTime));\
    }\
}

#define OAM3AH_Timer_Resume(ulTimerId)\
{\
    if(ulTimerId)\
    {\
        if (!OAM_3AH_Timer_IsStoped(ulTimerId))\
        {\
            /* 必须先Pause然后再Resume，否则不能重新开始计时! */\
            (VOID)VOS_Timer_Pause (ulTimerId);\
        }\
        (VOID)VOS_Timer_Resume(ulTimerId);\
    }\
}

#define OAM3AH_Timer_Pause(ulTimerId)\
{\
    if(ulTimerId && (!OAM_3AH_Timer_IsStoped(ulTimerId)))\
    {\
        (VOID)VOS_Timer_Pause(ulTimerId);\
    }\
}
    
/* 从探测阶段(SEND_ANY)退回到发现阶段时的定时器处理宏 */
#define OAM3AH_BACK_TO_DSCVR_TIMER_DEAL(pstPortInfo) \
{\
    if (OAM3AH_NP_VISP == g_stOam3ahModInfo.ulNpMode)/* NP为软件模式 */\
    {\
        /* 发现阶段以标准周期探测 */\
        OAM3AH_Timer_Resize((pstPortInfo)->ulPduTimerId, g_ulDefaultDetectIntervar);\
        OAM3AH_Timer_Resize((pstPortInfo)->ulLostLinkTimerId, g_ulDefaultlostLinkTime);\
    }\
    else if (OAM3AH_NP_FULL== g_stOam3ahModInfo.ulNpMode)/* 全NP */\
    {\
        /* 重启链路超时定时器 */\
        /* OAM3AH_Timer_Resume((pstPortInfo)->ulPduTimerId);*/\
        /* 如果状态机退回为FAULT/PASSIVE_WAIT/SEND_LOCAL，则链路超时定时器应该是停止状态 */\
        if ((pstPortInfo)->ulFsmState > OAM3AH_DSCVR_ACTIVE_SEND_LOCAL)\
        {\
            OAM3AH_Timer_Resume((pstPortInfo)->ulLostLinkTimerId);\
        }\
    }\
    else /* 半NP */\
    {\
        /*重置链路超时定时器周期值 */\
        /* OAM3AH_Timer_Resume((pstPortInfo)->ulPduTimerId);*/\
        OAM3AH_Timer_Resize((pstPortInfo)->ulLostLinkTimerId, g_ulDefaultlostLinkTime);\
    }\
}

/* 检查用户配置的链路事件窗口值是否合法 */
#define OAM3AH_WINDOW_10    10 
#define OAM3AH_WINDOW_100   100 
#define OAM3AH_WINDOW_600   600 
#define OAM3AH_WINDOW_9000  9000 
/* Modified by z00208058/w00207740, 3AH链路事件窗口和门限规格扩展, 2012/5/12 */
#define OAM3AH_LINKEVT_CHECK_WINDOW(ulLinkEventType,stdulErrWindow,ulCheckWin)\
{\
    ulCheckWin = OAM3AH_OK;\
    if ((OAM3AH_ERR_SYMPRD_EVENT == ulLinkEventType) || (OAM3AH_ERR_FRAME_EVENT == ulLinkEventType))\
    {\
        if ((OAM3AH_ERR_SYMPRD_EVENT == ulLinkEventType) && (1 == g_stOam3ahModInfo.ulErrSymPrdEventSetMode))\
        {\
            /* 错误符号周期事件(符号数模式)窗口配置的符号数只要大于0就可以,取值范围为1~ULONG可表示的最大值4294967295,步长1 */\
            if (DULONG_S_COMPARE_ULONG(stdulErrWindow, 1) < 0)\
            {\
                ulCheckWin = OAM3AH_ERR_EVENT_WIN;\
            }\
        }\
        else\
        {\
            if ((DULONG_S_COMPARE_ULONG(stdulErrWindow, OAM3AH_WINDOW_10) < 0) || ((DULONG_S_COMPARE_ULONG(stdulErrWindow, OAM3AH_WINDOW_600) > 0) || (0 != (stdulErrWindow.ulDulLo% 10))))\
            {\
                /* 错误符号周期事件(时间模式)/错帧事件窗口值10~600(0.1s单位),步长10(0.1s单位),单位下面都一样 */\
                ulCheckWin = OAM3AH_ERR_EVENT_WIN;\
            }\
        }\
    }\
    else if (OAM3AH_ERR_FRMPRD_EVENT == ulLinkEventType)\
    {\
        /* 错帧周期事件窗口值配置模式为0表示配置的窗口值为时间值;为1表示配置的窗口值为帧数目 */\
        if(0 == g_stOam3ahModInfo.ulErrFrmPrdEventSetMode)\
        {\
            /* 错帧周期事件窗口配置的时间值为1~600,步长1 */\
            if ((DULONG_S_COMPARE_ULONG(stdulErrWindow, 1) < 0) || (DULONG_S_COMPARE_ULONG(stdulErrWindow, OAM3AH_WINDOW_600) > 0))\
            {\
                ulCheckWin = OAM3AH_ERR_EVENT_WIN;\
            }\
        }\
        else\
        {\
            /* 错帧周期事件窗口配置的帧数目只要大于0就可以,取值范围为1~ULONG可表示的最大值4294967295,步长1 */\
            if (DULONG_S_COMPARE_ULONG(stdulErrWindow, 1) < 0)\
            {\
                ulCheckWin = OAM3AH_ERR_EVENT_WIN;\
            }\
        }\
    }\
    else /* 调用宏前前面已经有判断type值,到此处必为OAM3AH_ERR_FRMSECSUM_EVENT */\
    {\
        if ((DULONG_S_COMPARE_ULONG(stdulErrWindow, OAM3AH_WINDOW_100) < 0) || (DULONG_S_COMPARE_ULONG(stdulErrWindow, OAM3AH_WINDOW_9000) > 0) || (0 != (stdulErrWindow.ulDulLo % 10)))\
        {\
            ulCheckWin = OAM3AH_ERR_EVENT_WIN;\
        }\
    }\
}

/* Modified by z00208058/w00207740, 3AH链路事件窗口和门限规格扩展, 2012/5/12 */
/* 检查用户配置的链路事件门限值是否合法 */
#define OAM3AH_THRESHOLD_900    900 
#define OAM3AH_LINKEVT_CHECK_THRESHOLD(ulLinkEventType, stdulErrThres, ulCheckThres)\
{\
    ulCheckThres = OAM3AH_OK;\
    if (OAM3AH_ERR_FRMSECSUM_EVENT == ulLinkEventType)\
    {\
        if ((DULONG_S_COMPARE_ULONG(stdulErrThres, 1) < 0) || (DULONG_S_COMPARE_ULONG(stdulErrThres, OAM3AH_THRESHOLD_900) > 0))\
        {\
            ulCheckThres = OAM3AH_ERR_EVENT_THRESH;\
        }\
    }\
    else\
    {\
        /* 错误符号周期事件，错帧事件，错帧周期事件门限值的最大值不做限制，取ULONG可表示的最大值4294967295 */\
        if (DULONG_S_COMPARE_ULONG(stdulErrThres, 1) < 0)\
        {\
             ulCheckThres = OAM3AH_ERR_EVENT_THRESH;\
        }\
    }\
}

/* 错帧/错帧秒事件是否为NP实现 */
#define OAM3AH_FRAMEEVT_ACT_NP (1 == g_stOam3ahModInfo.ulFrmAct)

/* 填充/获取字段所使用的一些宏操作 */
/* 从字符指针cp获得一个char给c，cp指针加1 */
#define OAM3AH_GETCHAR(c, cp) { \
    (c) = *(cp); \
    (cp) ++ ; \
}

/* 将字符c写到字符指针cp处，cp指针加1 */
#define OAM3AH_PUTCHAR(c, cp) { \
    *(cp) = (UCHAR) (c); \
    (cp) ++ ; \
}

/* 从字符指针cp获得一个ushort值给s，cp指针加2 */
#define OAM3AH_GETSHORT(s, cp) { \
    USHORT usTemp;\
    VOS_CopyVar((usTemp), *((USHORT*)(cp)));\
    (s) = VOS_NTOHS(usTemp);\
    (cp) += sizeof(USHORT) ; \
}

/* 从字符指针cp获得一个ushort值给s,不对指针做偏移 */
#define OAM3AH_GETSHORT_NOSHIFT(s, cp) { \
    USHORT usTemp;\
    VOS_CopyVar((usTemp), *((USHORT*)(cp)));\
    (s) = VOS_NTOHS(usTemp);\
}

/* 将ushort变量s的值写到字符指针cp处，cp指针加2 */
#define OAM3AH_PUTSHORT(s, cp) { \
    USHORT usTemp;\
    (usTemp) = (USHORT)(s);\
    (usTemp) = (USHORT)VOS_HTONS(usTemp);\
    VOS_CopyVar(*(((USHORT*)(cp))), (usTemp));\
    (cp) += sizeof(USHORT) ; \
}

/* 从字符指针cp获得一个ulong值给s，cp指针加4 */
#define OAM3AH_GETLONG(l, cp) { \
    ULONG ulTemp;\
    VOS_CopyVar((ulTemp), *((ULONG*)(cp)));\
    (l) = VOS_NTOHL(ulTemp);\
    (cp) += sizeof(ULONG) ; \
}

/* 从字符指针cp获得一个ulong值给s，不对指针做偏移 */
#define OAM3AH_GETLONG_NOSHIFT(l, cp) { \
    ULONG ulTemp;\
    VOS_CopyVar((ulTemp), *((ULONG*)(cp)));\
    (l) = VOS_NTOHL(ulTemp);\
}

/* 将ulong变量l的值写到字符指针cp处，cp指针加4 */
#define OAM3AH_PUTLONG(l, cp) { \
    ULONG ulTemp;\
    (ulTemp) = (l);\
    (ulTemp) = (ULONG)VOS_HTONL(ulTemp);\
    VOS_CopyVar(*(((ULONG*)(cp))), (ulTemp));\
    (cp) += sizeof(ULONG) ; \
} 

/* 报文处理时延注册函数 */
typedef ULONG (*DEALPKT_TIMETEST__HOOK_FUNC) (ULONG ulDealStatus);

/* 报文处理状态,性能测试使用 */
#define OAM3AH_RCV_DEALPKT_BEGIN        0x01
#define OAM3AH_RCV_DEALPKT_END          0x02

/* 定时器状态宏,OAM_3AH_Timer_IsStoped使用.
 * 说明:为避免VISP引入对dopra新的依赖函数故自定义函数 OAM_3AH_Timer_IsStoped;该函数需要使用下面两个宏,
 * 这两个宏在dopra头文件v_relatm.h中有定义,但包含则存在nodeb版本编译问题,故在此重复定义如下两个宏
 */
#ifndef VOS_TM_IS_PAUSED
#define VOS_TM_IS_PAUSED        0xAE      /*相对定时器的状态是中止态        */
#endif
#ifndef VOS_TM_IS_DELETED
#define VOS_TM_IS_DELETED       0x55      /*相对定时器的状态是被删除态      */
#endif

#define OAM3AH_MAX_NEG_TIME 600         /* 设置首次协商不过对外告警最大时间,单位为s */
#define OAM3AH_NEGWARNING_TIMEINIT  (ULONG)~0x0  /* 0xFFFFFFFF */
#define OAM3AH_NEGWARNING_TIMEDONE  (ULONG)~0x1  /* 0xFFFFFFFE */

#define OAM3AH_WARN_TRACE_SENDANY_BIT 0x01       /* SENDANY告警追踪 */
#define OAM3AH_WARN_TRACE_LB_LCL_BIT  0x02       /* 环回响应稳态告警追踪 */
#define OAM3AH_WARN_TRACE_LB_RMT_BIT  0x04       /* 环回发起稳态告警追踪 */

/* 代码注释专用宏-以便于在SI的symbol窗口查看代码,该宏名不宜太长,否则效果不佳 */
#define NOTE(x)                         1

#ifdef __cplusplus
}
#endif      /* end of __cplusplus   */


#endif      /* end of _3AH_DEF_H_   */

