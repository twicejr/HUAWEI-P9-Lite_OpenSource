/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              3ah_type.h
*
*  Project Code: VISPV100R007
*   Module Name: ETH OAM 3AH  
*  Date Created: 2008-2-28
*        Author: LY(57500)
*   Description: 3AH模块数据结构定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2008-2-28  LY(57500)     Create the first version.
*
*******************************************************************************/
#ifndef _3AH_TYPE_H_
#define _3AH_TYPE_H_

#ifdef __cplusplus
extern "C"{
#endif

/* 本地保存的链路事件数据 */
typedef struct tagLinkEventInfo
{
    ULONG ulEventType;          /* 事件类型             */
    ULONG ulEventStamp;         /* 记录发生事件的时间戳 */

    DULONG_S stDulErrWindows;
    DULONG_S stDulErrThreshold;
    DULONG_S stDulErrValue;
    DULONG_S stDulErrRunTotal;

    ULONG ulEventRunTotal;      /* OAM复位依赖发生链路事件总数 */    
}OAM3AH_LINKEVENT_INFO_S;

/* 链路事件管理数据结构 */
typedef struct tagLinkEvent
{
    ULONG ulEventEnable;        /* 事件的使能标志位                                 */
    ULONG ulEventTimerId;       /* 链路事件定时器ID,当前只有错帧事件/错帧秒事件使用 */
    ULONG ulCount;              /* 目前仅错帧秒用来记录当前描述                     */

    VOID (*pfTimerFunc)(ULONG ulIfIndex);   /* 定时器回调函数指针,当前只有错帧事件/错帧秒事件使用   */
    DULONG_S stDulErrCnt;       /* 存储从底层读取的错帧数,当前只有错帧事件/错帧秒事件使用           */
    /* Modified by z00208058/w00207740, 3AH链路事件窗口和门限规格扩展, 2012/5/12 */
    DULONG_S stdulEventWindow;        /* 存储用户配置的窗口值;周期事件的窗口需要驱动转换,故不能直接保存到stLinkEventInfo中  */
    /* 用户配置的链路事件门限参数直接保存在下面的stLinkEventInfo中,供组包用 */
    
    OAM3AH_LINKEVENT_INFO_S stLinkEventInfo;
}OAM3AH_LINKEVENT_S;

/* 报文TLV数据结构,必须强制一字节对齐 */
#pragma pack(1)

/* 3AH OAMPDU HEAD -- 15字节 */
typedef struct tagOamPduHead
{
    UCHAR   ucDstMacAddr[MACADDRLEN];   /* 慢协议多播MAC: 01-80-C2-00-00-02 */
    UCHAR   ucSrcMacAddr[MACADDRLEN];   /* 源MAC                            */

    USHORT  usType;                     /* 慢协议类型: 8809                 */

    UCHAR   ucSubType;                  /* OAMPDU子类型                     */
}OAMPDU_HEAD_S;

/* 带VLAN头的3AH报文 */
typedef  struct  tagOamVlanPduHead
{
    UCHAR   ucDstMacAddr[MACADDRLEN];   /* 慢协议多播MAC: 01-80-C2-00-00-02 */
    UCHAR   ucSrcMacAddr[MACADDRLEN];   /* 源MAC                            */
    USHORT  usTPID ;                    /* 802.1q Protype 8100 */
    USHORT  usTCI ;                     /*user User_priority CFI VLANID */
    USHORT  usType;                     /* 慢协议类型: 8809                 */
    UCHAR   ucSubType;                  /* OAMPDU子类型                     */
}OAMPDU_VLAN_HEAD_S;


/* 错误符号周期事件TLV定义 */
typedef struct tagOam3ahEventSymPrd
{
    UCHAR       ucEventType;                /* 事件类型,0x01                    */
    UCHAR       ucEventLen;                 /* 事件长度,0x28                    */
    USHORT      usEventStamp;               /* 记录事件发生的时间戳,单位100ms   */

    DULONG_S    stDulErrWindows;            /* 事件门限                         */
    DULONG_S    stDulErrThreshold;          /* 事件窗口                         */
    DULONG_S    stDulErrSymbols;            /* 本周期错误符号数                 */
    DULONG_S    stDulErrRunTotal;           /* OAM复位后错误符号总数            */

    ULONG       ulEventRunTotal;            /* OAM复位后错误编码TLV事件总数     */
}OAM3AH_EVENT_SYMPRD_S;

/* 错帧事件TLV */
typedef struct tagOam3ahEventFrame
{
    UCHAR       ucEventType;                /* 事件类型,0x02                    */
    UCHAR       ucEventLen;                 /* 事件长度,0x1A                    */
    USHORT      usEventStamp;               /* 记录事件发生的时间戳,单位100ms   */

    USHORT      usErrWindows;               /* 事件窗口                         */
    ULONG       ulErrThreshold;             /* 事件门限                         */
    ULONG       ulErrFrames;                /* 本周期错帧数                     */
    DULONG_S    stDulErrRunTotal;           /* OAM复位后错帧总数                */

    ULONG       ulEventRunTotal;            /* OAM复位后错误编码TLV事件总数     */
}OAM3AH_EVENT_FRAME_S;

/* 错帧周期事件TLV定义 */
typedef struct tagOam3ahEventFrmPrd
{
    UCHAR       ucEventType;                /* 事件类型,0x03                    */
    UCHAR       ucEventLen;                 /* 事件长度,0x1C                    */
    USHORT      usEventStamp;               /* 记录事件发生的时间戳,单位100ms   */

    ULONG       ulErrWindows;               /* 事件窗口                         */
    ULONG       ulErrThreshold;             /* 事件门限                         */
    ULONG       ulErrFrames;                /* 本周期错帧数                     */
    DULONG_S    stDulErrRunTotal;           /* OAM复位错帧总数                  */

    ULONG       ulEventRunTotal;            /* OAM复位后错误编码TLV事件总数     */
}OAM3AH_EVENT_FRMPRD_S;

/* 错帧秒事件TLV定义 */
typedef struct tagOam3ahEventFrmSecSum
{
    UCHAR       ucEventType;                /* 事件类型,0x04                    */
    UCHAR       ucEventLen;                 /* 事件长度,0x12                    */
    USHORT      usEventStamp;               /* 记录事件发生的时间戳,单位100ms   */

    USHORT      usErrWindows;               /* 事件窗口                         */
    USHORT      usErrThreshold;             /* 事件门限                         */
    USHORT      usErrSecSum;                /* 本周期错帧秒数                   */
    ULONG       ulErrRunTotal;              /* OAM复位总错帧秒数                */

    ULONG       ulEventRunTotal;            /* OAM复位后错误编码TLV事件总数     */
}OAM3AH_EVENT_FRMSECSUM_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif


/* 3AH OAMPDU flags字段定义 */
typedef union unOamPduFlags_U
{
    struct tagOamPduFlags
    {
#if (VRP_BIG_ENDIAN == VRP_YES)
        USHORT  usReserved:9;       /* 15:7 Reserved                            */
        USHORT  usRmtDscvrStatus:2; /* 6:5  Remote Stable & Remote Evaluating   */
        USHORT  uslclDscvrStatus:2; /* 4:3  Local Stable & Local Evaluating    */
        USHORT  usCriticalEvent:1;  /* 2    Critical Event                      */
        USHORT  usDyingGasp:1;      /* 1    unrecoverable condition             */
        USHORT  usLinkFalut:1;      /* 0    PHY detect Link Fault               */
#else
        USHORT  usLinkFalut:1;      /* 0    PHY detect Link Fault               */
        USHORT  usDyingGasp:1;      /* 1    unrecoverable condition             */
        USHORT  usCriticalEvent:1;  /* 2    Critical Event                      */
        USHORT  uslclDscvrStatus:2; /* 4:3  Local Stable & Local Evaluating    */
        USHORT  usRmtDscvrStatus:2; /* 6:5  Remote Stable & Remote Evaluating   */
        USHORT  usReserved:9;       /* 15:7 Reserved                            */
#endif
    }s;
    
    USHORT  usFlags;
}OAMPDU_FLAGS_U;

/* 3AH OAMPDU configuration字段定义   */
typedef union tagOamPduConfig_U
{
    struct tagOamPduConfig
    {
#if (VRP_BIG_ENDIAN == VRP_YES)        
        UCHAR ucDetectInterval:3;   /* 协议保留,扩展用来标识探测速率                    */
        UCHAR ucVarRetrieval:1;     /* Variable Retrieval: 1=Support;0=Not Support      */
        UCHAR ucLinkEvent:1;        /* Link Events: 1=Support;0=Not Support             */
        UCHAR ucOamLbSupport:1;     /* Remote Loopback Support: 1=Support;0=Not Support */
        UCHAR ucUniSupport:1;       /* Unidirectional Support: 1=Support;,0=Not Support */
        UCHAR ucOamMode:1;          /* 本地OAM Mode: 1=Active;0=Passive                 */
#else
        UCHAR ucOamMode:1;          /* 本地OAM Mode: 1=Active;0=Passive                 */
        UCHAR ucUniSupport:1;       /* Unidirectional Support: 1=Support;,0=Not Support */
        UCHAR ucOamLbSupport:1;     /* Remote Loopback Support: 1=Support;0=Not Support */
        UCHAR ucLinkEvent:1;        /* Link Events: 1=Support;0=Not Support             */
        UCHAR ucVarRetrieval:1;     /* Variable Retrieval: 1=Support;0=Not Support      */
        UCHAR ucDetectInterval:3;   /* 协议保留,扩展用来标识探测速率                    */
#endif
    }s;

    UCHAR ucConfig;
}OAMPDU_CONFIG_U;

/* 3AH OAMPDU state 字段定义 */
typedef union tagOamPduState_U
{
    struct tagOamPduState
    {
#if (VRP_BIG_ENDIAN == VRP_YES)        
        UCHAR ucRsv:5;          /* 7:3 Reserved                 */
        UCHAR ucMuxAction:1;    /* 2   Multiplexer Action       */
        UCHAR ucParserAction:2; /* 1:0 Parser Action            */
#else
        UCHAR ucParserAction:2; /* 1:0 Parser Action            */
        UCHAR ucMuxAction:1;    /* 2   Multiplexer Action       */
        UCHAR ucRsv:5;          /* 7:3 Reserved                 */
#endif
    }s;

    UCHAR ucState;
}OAMPDU_STATE_U;

#pragma pack(1)
/* OAMPDU IFNO TLV结构定义 */
typedef struct tagOamPduInfoTlv
{
    UCHAR   ucInfoType;                 /* 信息类型                         */
    UCHAR   ucInfoLen;                  /* 信息长度,0x10                    */
    UCHAR   ucOamVersion;               /* OAM版本号                        */
    USHORT  usRevision;                 /* Info TLV修订版本号               */
    OAMPDU_STATE_U  unState;            /* OAM状态信息                      */
    OAMPDU_CONFIG_U unOamCfg;           /* OAM配置信息                      */
    USHORT  usOamPduCfg;                /* OAMPDU配置信息:最大OAMPDU尺寸    */
    UCHAR   aucOUI[OAMPDU_OUI_LENGTH];  /* 厂商唯一标识                     */
    ULONG   ulVendorInfo;               /* 用于区别厂商产品的标识,未使用    */
}OAMPDU_INFO_TLV_S;

/* Organization Specific Information Tlv */
typedef struct tagOamPduOrgSpecTlv
{
    UCHAR ucInfoType; /* 信息类型: 0xFE OAM3AH_ORG_SPEC_INFORMATION */
    UCHAR ucInfoLen;  /* 信息长度 */
    UCHAR aucOUI[OAMPDU_OUI_LENGTH]; /* 厂商唯一标识 */
    UCHAR ucBoardType; /* 当前定义的是板子主用/备用状态: 0xAB标识主用板;0xBA表示备用板 */
}OAMPDU_ORGSPEC_TLV_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

typedef struct tagOamPduOrgSpecInfo
{
    ULONG ulLclBoardState; /* 本端主备板状态;0-不向对端通告;1-向对端通告本端主用板状态;2-向对端通告本端备用板状态 */
    OAMPDU_ORGSPEC_TLV_S stLclOrgSpecTlv;
    OAMPDU_ORGSPEC_TLV_S stRmtOrgSpecTlv;
}OAM3AH_ORGSPEC_INFO_S;

/* 3AH控制块 */
typedef struct tagOam3ahPortInfo
{
    DLL_NODE_S  stNode;             /* 用于构造双向链表             */

    ULONG   ulIfIndex;              /* 接口索引                     */
    ULONG   ul3ahEnable;            /* 接口使能标记                 */
    ULONG   ulDetectIntervar;       /* 探测周期,ms为单位            */
    ULONG   ulFsmState;             /* 接口3AH状态机状态            */
    USHORT  usDscvrProcessStatue;   /* 本地或对端发现是否完成       */
    UCHAR   aucPeerMacAddr[MACADDRLEN];  /* 对端physical地址              */
    USHORT  usLbTestMode;           /* 环回测试模式,0=VISP软件测试模式;1=NP环回测试模式 */

    OAMPDU_FLAGS_U unFlags;         /* OAMPDU flag字段              */
    OAMPDU_INFO_TLV_S stLclInfoTlv; /* 本地INFO TLV配置信息         */
    OAMPDU_INFO_TLV_S stRmtInfoTlv; /* 对端INFO TLV配置信息         */
    ULONG   ulPduCnt;               /* 每秒最多发送OAMPDU计数,初始值为10    */

    ULONG   ulPduTimerId;           /* 周期发送定时器ID             */
    ULONG   ulLostLinkTimerId;      /* 对端链路丢失探测定时器ID     */
    
    /* 环回相关 */
    ULONG   ulLbTimerId;            /* 环回超时定时器ID             */    
    ULONG   ulLbCtrlPduRetryTimes;  /* 环回控制报文重试次数         */
    
    /* 事件故障管理相关字段 */
    ULONG   ulFaultEnable;          /* 故障通告使能状态,从低0位到低2位分别表示链路故障/致命故障/紧急事件 */
    ULONG   ulLclFault;             /* 本地故障标识,同上说明        */
    ULONG   ulRmtFault;             /* 对端故障标识,同上说明        */
    
    USHORT  usLclSeqNum;            /* 本端链路事件序列号           */
    USHORT  usRmtSeqNum;            /* 对端链路事件序列号           */
    
    /* 0: Errored Symbol Period Event           */
    /* 1: Errored Frame Event                   */
    /* 2: Errored Frame Period Event            */
    /* 3: Errored Frame Seconds Summary Event   */
    OAM3AH_LINKEVENT_S stLinkEvent[OAM3AH_LINKEVENT_NUM];

    OAM3AH_PDUSTAT_S stStatistic;  /* 3AH OAMPDU 统计信息          */
    ULONG   ulDebugSwitch;         /* 3ah调试开关                  */

    OAM3AH_ORGSPEC_INFO_S stOrgSpecInfo;  
    ULONG   ulHasNpUpdate;         /* 记录是否已经进行了np会话下发 */  
    ULONG   ulNegTimeCnt;          /* 首次协商不过对外告警计时 */    
}OAM3AH_PORTINFO_S;


#define     DLLOAM3AHPORTINFO(x)      ((OAM3AH_PORTINFO_S *)(x)) 


/* 状态机迁移的数据结构定义 */
typedef struct tagOam3ahFsmTran
{
    ULONG ulStartState;        /* 初始状态,枚举值,参见相关定义 */
    ULONG ulTranCondition;     /* 驱动事件,枚举值,参见相关定义 */
    ULONG ulEndState;          /* 终止状态,枚举值,参见相关定义 */
}OAM3AH_FSMTRAN_S;

/* Shell向Core注册的回调函数集 */
typedef struct tagOam3ahShellCallbackSet
{
    /* 调试信息输出函数 */
    VOID (*pfOAM_3AH_DebugOutString) (CHAR * szStr);
}OAM3AH_SHELL_CALLBACK_SET_S;

/* 底层通知周期事件参数结构 */
typedef struct tagOam3ahLinkEvtParam
{
    DULONG_S    stdulWindows;
    DULONG_S    stdulThreshold;
    DULONG_S    stdulErrorNum;
    DULONG_S    stdulErrRunTotal;
}OAM3AH_LINKEVT_PARAM_S;

#ifdef __cplusplus
}
#endif      /* end of __cplusplus   */

#endif      /* end of _3AH_TYPE_H_  */

