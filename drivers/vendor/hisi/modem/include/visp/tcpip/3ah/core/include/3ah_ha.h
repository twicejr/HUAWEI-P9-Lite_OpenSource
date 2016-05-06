/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              3ah_ha.h
*
*  Project Code: VISPV100R007
*   Module Name: ETH OAM 3AH  
*  Date Created: 2008-2-28
*        Author: LY(57500)
*   Description: 3AH模块HA头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2008-2-28  LY(57500)     Create the first version.
*
*******************************************************************************/
#ifndef _3AH_HA_H_
#define _3AH_HA_H_

#ifdef __cplusplus
extern "C"{
#endif


/*  3AH模块HA备份消息头     */
typedef struct tagOam3ahHaHead
{
    USHORT  usBakType;          /* 3AH备份消息类型  */
    USHORT  usBakLen;           /* 3AH备份消息长度  */
}OAM3AH_HA_HEAD_S;

/* ha tlv head(type+len) */
typedef struct tagOam3ahHaTlv
{
    USHORT  usHaTlvType;
    USHORT  usHaTlvLen;
}OAM3AH_HA_TLV_HEAD_S;

/* 用户配置的链路事件窗口门限参数备份结构 */
typedef struct tagHaEventWinThrsh
{
    ULONG   ulEventType;          /* 链路事件类型,暂时可不用,主要为后续可能扩充使用,需要通过此区分不同的新增链路事件*/
    ULONG   ulEventEnable;        /* 是否使能         */
    ULONG   ulEventWindow;        /* 链路事件窗口     */
    ULONG   ulEventThresh;        /* 链路事件门限     */
}OAM3AH_HA_LINKEVT_S;

/* INFO TLV HA备份结构 */
typedef struct tagHaInfoTlv
{
        UCHAR   ucInfoType;             /* INFO TYPE: 本端或对端        */
        UCHAR   ucInfoLen;              /* INFO LEN:当前0x10            */
        UCHAR   ucOamVersion;           /* OAM 版本号                   */
        UCHAR   ucState;                /* INFO TLV状态字段             */
        USHORT  usRevision;             /* 配置版本号                   */
        USHORT  usOamPduCfg;            /* OAMPDU大小字段               */
        UCHAR   ucOamCfg;               /* OAMPDU config字段            */
        UCHAR   aucOUI[OAMPDU_OUI_LENGTH];   /* OUI厂商信息              */
        ULONG   ulVendorInfo;           /* 产品信息                     */
}OAM3AH_HA_INFOTLV_S;

/* info oampdu: org spec tlv back; append to OAM3AH_HA_PORTCFG_S */
typedef struct tagOam3ahInfoOrgSpec
{
    ULONG ulLclBoardState;  /* 0 - OAM3AH_BOARD_STATE_NULL,1-OAM3AH_BOARD_STATE_MASTER,2-OAM3AH_BOARD_STATE_SLAVE */
    ULONG ulRmtBoardState;  /* 0,1,2 - same pre */
}OAM3AH_HA_INFO_ORGSPEC_S;

/* 端口配置信息备份结构 */
typedef struct tagOam3ahHaPortInfo
{
    ULONG   ulIfIndex;                  /* 接口索引                     */
    ULONG   ul3ahEnable;                /* 接口使能标记                 */
    ULONG   ulDetectIntervar;           /* 探测周期,ms为单位            */
    ULONG   ulFsmState;                 /* 接口3AH状态机状态            */
    USHORT  usDscvrProcessStatue;       /* 本地或对端发现是否完成       */
    UCHAR   aucPeerMacAddr[MACADDRLEN]; /* 对端physical地址                  */
    USHORT  usFlags;                    /* OAMPDU flag字段              */
    USHORT  usLbTestMode;               /* 环回测试模式,0=VISP软件测试模式;1=NP环回测试模式                     */
    ULONG   ulFaultEnable;              /* 故障通告使能状态,从低0位到低2位分别表示链路故障/致命故障/紧急事件    */

    OAM3AH_HA_LINKEVT_S     stEventSymPrd;      /* 错误符号周期事件窗口和门限   */
    OAM3AH_HA_LINKEVT_S     stEventFrame;       /* 错帧事件窗口和门限           */
    OAM3AH_HA_LINKEVT_S     stEventFrmPrd;      /* 错帧周期事件窗口和门限       */
    OAM3AH_HA_LINKEVT_S     stEventFrmSecSum;   /* 错帧秒事件窗口和门限         */
    
    OAM3AH_HA_INFOTLV_S     stHaLclInfoTlv;     /* 本端INFO TLV                 */
    OAM3AH_HA_INFOTLV_S     stHaRmtInfoTlv;     /* 对端INFO TLV                 */
}OAM3AH_HA_PORTCFG_S;

/* Modified by z00208058/w00207740, 3AH链路事件窗口和门限规格扩展, 2012/5/10 */
/* 用户配置的支持64位链路事件窗口门限参数备份结构 */
typedef struct tagHaEventWinThrshEx
{
    ULONG   ulEventType;          /* 链路事件类型,暂时可不用,主要为后续可能扩充使用,需要通过此区分不同的新增链路事件*/
    ULONG   ulEventEnable;        /* 是否使能         */
    DULONG_S stdulEventWindow;        /* 链路事件窗口     */
    DULONG_S stdulEventThresh;        /* 链路事件门限     */
}OAM3AH_HA_LINKEVT_Ex_S;


typedef struct tagHaEventWinThrshTlv
{
    OAM3AH_HA_LINKEVT_Ex_S     stEventSymPrd;      /* 错误符号周期事件窗口和门限   */
    OAM3AH_HA_LINKEVT_Ex_S     stEventFrame;       /* 错帧事件窗口和门限           */
    OAM3AH_HA_LINKEVT_Ex_S     stEventFrmPrd;      /* 错帧周期事件窗口和门限       */
    OAM3AH_HA_LINKEVT_Ex_S     stEventFrmSecSum;   /* 错帧秒事件窗口和门限         */
}OAM3AH_HA_LINKEVT_TLV_S;

/* 备份链路事件配置信息到HA备份包中 */
#define OAM3AH_HA_PACK_LINKEVT(pst3ahBakEvt, pst3ahLinkEvt)\
{\
    (pst3ahBakEvt)->ulEventType = OAM3AH_EVENT_TYPE(pst3ahLinkEvt);\
    (pst3ahBakEvt)->ulEventEnable = (pst3ahLinkEvt)->ulEventEnable;\
    (pst3ahBakEvt)->ulEventWindow = 0;\
    (pst3ahBakEvt)->ulEventThresh = 0; \
}

/* 从备份包中恢复链路配置信息 */
#define OAM3AH_HA_UNPACK_LINKEVT(pst3ahLinkEvt,pst3ahBakEvt)\
{\
    OAM3AH_EVENT_TYPE(pst3ahLinkEvt)= (pst3ahBakEvt)->ulEventType;\
    (pst3ahLinkEvt)->ulEventEnable = (pst3ahBakEvt)->ulEventEnable;\
    (pst3ahLinkEvt)->stdulEventWindow.ulDulLo = (pst3ahBakEvt)->ulEventWindow;\
    OAM3AH_EVENT_THRESHOLDLo(pst3ahLinkEvt) = (pst3ahBakEvt)->ulEventThresh; \
}

#define OAM3AH_HA_PACK_LINKEVT_EX(pst3ahBakEvt, pst3ahLinkEvt)\
{\
    (pst3ahBakEvt)->ulEventType = OAM3AH_EVENT_TYPE(pst3ahLinkEvt);\
    (pst3ahBakEvt)->ulEventEnable = (pst3ahLinkEvt)->ulEventEnable;\
    DULONG_S_COPY((pst3ahBakEvt)->stdulEventWindow, (pst3ahLinkEvt)->stdulEventWindow);\
    DULONG_S_COPY((pst3ahBakEvt)->stdulEventThresh, pst3ahLinkEvt->stLinkEventInfo.stDulErrThreshold);\
}

#define OAM3AH_HA_UNPACK_LINKEVT_EX(pst3ahLinkEvt,pst3ahBakEvt)\
{\
    OAM3AH_EVENT_TYPE(pst3ahLinkEvt)= (pst3ahBakEvt)->ulEventType;\
    (pst3ahLinkEvt)->ulEventEnable = (pst3ahBakEvt)->ulEventEnable;\
    DULONG_S_COPY((pst3ahLinkEvt)->stdulEventWindow, (pst3ahBakEvt)->stdulEventWindow);\
    DULONG_S_COPY(pst3ahLinkEvt->stLinkEventInfo.stDulErrThreshold, (pst3ahBakEvt)->stdulEventThresh); \
}

/* 备份TLV信息到HA备份包中 */
#define OAM3AH_HA_PACK_INFOTLV(pst3ahBakInfo, pst3ahInfo) \
{\
    (pst3ahBakInfo)->ucInfoType = (pst3ahInfo)->ucInfoType;\
    (pst3ahBakInfo)->ucInfoLen = (pst3ahInfo)->ucInfoLen;\
    (pst3ahBakInfo)->ucOamVersion = (pst3ahInfo)->ucOamVersion;\
    (pst3ahBakInfo)->ucState = (pst3ahInfo)->unState.ucState;\
    (pst3ahBakInfo)->usRevision = (pst3ahInfo)->usRevision;\
    (pst3ahBakInfo)->usOamPduCfg = (pst3ahInfo)->usOamPduCfg;\
    (pst3ahBakInfo)->ucOamCfg = (pst3ahInfo)->unOamCfg.ucConfig;\
    (VOID)TCPIP_Mem_Copy((pst3ahBakInfo)->aucOUI, OAMPDU_OUI_LENGTH, (pst3ahInfo)->aucOUI, OAMPDU_OUI_LENGTH);\
    (pst3ahBakInfo)->ulVendorInfo = (pst3ahInfo)->ulVendorInfo;\
}

/* 从备份包中恢复TLV信息 */
#define OAM3AH_HA_UNPACK_INFOTLV(pst3ahInfo, pst3ahBakInfo) \
{\
    (pst3ahInfo)->ucInfoType = (pst3ahBakInfo)->ucInfoType;\
    (pst3ahInfo)->ucInfoLen = (pst3ahBakInfo)->ucInfoLen;\
    (pst3ahInfo)->ucOamVersion = (pst3ahBakInfo)->ucOamVersion;\
    (pst3ahInfo)->unState.ucState = (pst3ahBakInfo)->ucState;\
    (pst3ahInfo)->usRevision = (pst3ahBakInfo)->usRevision;\
    (pst3ahInfo)->usOamPduCfg = (pst3ahBakInfo)->usOamPduCfg;\
    (pst3ahInfo)->unOamCfg.ucConfig = (pst3ahBakInfo)->ucOamCfg;\
    (VOID)TCPIP_Mem_Copy((pst3ahInfo)->aucOUI, OAMPDU_OUI_LENGTH, (pst3ahBakInfo)->aucOUI, OAMPDU_OUI_LENGTH);\
    (pst3ahInfo)->ulVendorInfo = (pst3ahBakInfo)->ulVendorInfo;\
}

/* 备份类型－保存在公共HA结构头的ucOperation字段 */
#define OAM3AH_HA_BATCH         0x1
#define OAM3AH_HA_REALTIME      0x2

/* 3AH备份消息类型     */
typedef enum enOam3ahHaBakType
{
    OAM3AH_HA_PORTCFG = 0x0100,         /* 控制块备份,后续PORTCFG字段更新子TLV的TYPE值为0x0101、0x0102、etc ... */
    OAM3AH_HA_INFO_ORGSPEC = 0x0101,    /* info OAMPDU: ORG SPEC TLV(board type) */
    /* Modified by z00208058/w00207740, 3AH链路事件窗口和门限规格扩展, 2012/5/12 */
    OAM3AH_HA_LINKEVT = 0x0102,         /* DULONG LINKEVT TLV TYPE*/

    OAM3AH_HA_GLOBAL_DISABLE = 0x0200,  /* 全局去使能备份   */

    OAM3AH_HA_GLOBALVAR = 0x0300,       /* 3AH全局变量备份 */
    OAM3AH_HA_GLOBALVAR_NEGOUTTIME = 0x0301,  /* 首次协商不通过对外告警时间 */


}OAM3AH_HA_BAKTYPE_E;

/* 备份类型高8位表示主类型 */
#define OAM3AH_MAIN_TYPE_MASK   0xff00
/* 获取主备份类型 */
#define OAM3AH_HA_MAINTYPE(ulBakType) \
    ((ulBakType) & OAM3AH_MAIN_TYPE_MASK)

/* 实时备份命令字 */
/* 如有更新请同步g_asz3ahRtBakDbgInfo字符串数组 */
typedef enum enOam3ahHaBakCmd
{
    OAM3AH_HA_BAKCFG = 0,               /* 备份配置消息     */
    OAM3AH_HA_BAKGDISABLE,              /* 备份全局去使能   */
    OAM3AH_HA_BAKGVAR,                   /* 备份全局变量 */
}OAM3AH_HA_BAKCMD_E;

/* HA调试信息输出宏 */
#define OAM3AH_DBG_OUTPUT(szInfo) TCPIP_DebugOutput(szInfo)

/* 设置OAM3AH HA内部模块报文头 */
#define SET_OAM3AH_HA_HEAD(pst3ahBakHdr, ulBakType, ulBakLen)\
{\
    (pst3ahBakHdr)->usBakType = (USHORT)(ulBakType);\
    (pst3ahBakHdr)->usBakLen  = (USHORT)(ulBakLen);\
}

extern OAM3AH_HASTAT_S g_stOam3ahHaStat;

/* HA调试信息输出宏 */
#define OAM3AH_HA_DBG_OUTPUT(szInfo) (VOID)TCPIP_IC_SendMsg(0, 0, szInfo)

/* 将链路配置信息打印到内存中 */
#define OAM3AH_SPRINTF_HA_LINKEVT(pst3ahBakEvt, szDbgStr, iDbgLen)\
{\
    iDbgLen += TCPIP_SNPRINTF(szDbgStr + iDbgLen, LEN_1024 - iDbgLen, P2("\r\n%20s: %lu", "- Link Evt Type", (pst3ahBakEvt)->ulEventType));\
    iDbgLen += TCPIP_SNPRINTF(szDbgStr + iDbgLen, LEN_1024 - iDbgLen, P2("\r\n%20s: %lu", "Link Evt Enable", (pst3ahBakEvt)->ulEventEnable));\
    iDbgLen += TCPIP_SNPRINTF(szDbgStr + iDbgLen, LEN_1024 - iDbgLen, P2("\r\n%20s: %lu(decisecond)", "Link Evt Window", (pst3ahBakEvt)->ulEventWindow));\
    iDbgLen += TCPIP_SNPRINTF(szDbgStr + iDbgLen, LEN_1024 - iDbgLen, P2("\r\n%20s: %lu", "Link Evt Thresh", (pst3ahBakEvt)->ulEventThresh));\
}

/* Modified by z00208058/w00207740, 3AH链路事件窗口和门限规格扩展, 2012/5/12 */
/* 将链路配置信息打印到内存中 */
#define OAM3AH_SPRINTF_HA_LINKEVT_EX(pst3ahBakEvt, szDbgStr, iDbgLen)\
{\
    iDbgLen += TCPIP_SNPRINTF(szDbgStr + iDbgLen, LEN_1024 - iDbgLen, P2("\r\n%20s: %lu", "- Link Evt Type", (pst3ahBakEvt)->ulEventType));\
    iDbgLen += TCPIP_SNPRINTF(szDbgStr + iDbgLen, LEN_1024 - iDbgLen, P2("\r\n%20s: %lu", "Link Evt Enable", (pst3ahBakEvt)->ulEventEnable));\
    iDbgLen += TCPIP_SNPRINTF(szDbgStr + iDbgLen, LEN_1024 - iDbgLen, P3("\r\n%20s: %lu %lu(decisecond)", "Link Evt Window", (pst3ahBakEvt)->stdulEventWindow.ulDulHi, (pst3ahBakEvt)->stdulEventWindow.ulDulLo));\
    iDbgLen += TCPIP_SNPRINTF(szDbgStr + iDbgLen, LEN_1024 - iDbgLen, P3("\r\n%20s: %lu %lu", "Link Evt Thresh", (pst3ahBakEvt)->stdulEventThresh.ulDulHi, (pst3ahBakEvt)->stdulEventThresh.ulDulLo));\
}

#ifdef __cplusplus
}
#endif      /* end of __cplusplus   */

#endif      /* end of _3AH_HA_H_    */

