

#ifndef __PSNDIS_H__
#define __PSNDIS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "vos.h"
#include "ImmInterface.h"
#include "AtNdisInterface.h"
#include "AdsDeviceInterface.h"
#include "PsTypeDef.h"
#include "TTFComm.h"
#if (VOS_OS_VER != VOS_WIN32)
#include "NdisDrv.h"
#include <msp_nvim.h>
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*hujianbo:以下函数与底软定义不一致，将其去掉，改成直接包含DrvInterface.h*/


/* DHCP选项中最大租约时间长度，单位小时，366天 */
#define TTF_NDIS_DHCP_MAX_LEASE_HOUR            8784

/*IPV6 MTU NV项默认取值*/
#define TTF_NDIS_IPV6_MTU_DEFAULT               1500      /*单位为字节*/

#define Ndis_NvimItem_Read( ulId, pItemData, usItemDataLen ) \
    NDIS_NV_READX( MODEM_ID_0, ulId, (VOS_VOID *)(pItemData), usItemDataLen)

/*ARP*/
#define ETH_ARP_REQ_TYPE                0x0100      /*ARP Request*/
#define ETH_ARP_RSP_TYPE                0x0200      /*ARP Reply*/
#define ETH_ARP_FIXED_MSG_LEN           8           /*ARP固定部分长度*/

/*IP*/
/*#define IPPACKET_MIN_LEN                (1500)
 */
#define IPV4_FIX_HDR_LEN                (20)       /* IPV4固定头长度*/
#define IPV4_HDR_TTL                    (128)      /* IPV4 头中的TTL字段默认值*/

#define IP_IPV4_VERSION                 (4)        /* IP V4版本号      */
#define IP_PROTOCOL_UDP                 (0x11)     /* IP承载协议是UDP  */
#define IP_PROTOCOL_TCP                 (0x06)     /* IP承载协议是TCP  */
#define IP_PROTOCOL_ICMP                (0x01)     /* IP承载协议是ICMP */

/*DHCP报文目的端口67,定义为网络字节序*/
#define UDP_DHCP_SERVICE_PORT           (0x4300)   /* DHCP服务的端口号 */
#define UDP_DHCP_CLIENT_PORT            (0x4400)   /* DHCP Client的端口号*/

/*NDIS上行任务事件*/
#define NDIS_UL_EVENT_RECIVE_USB_DATA      (0x0001)

/*NDIS下行任务事件*/
#define NDIS_DL_EVENT_RECIVE_ADS_DATA      (0x0002)

/*Userplane huibo begin*/
#define NDIS_ENTITY_RABNUM                 (2)
#define NDIS_ENTITY_IPV4INDEX              (0)
#define NDIS_ENTITY_IPV6INDEX              (1)
#define NDIS_ENTITY_IPV4ADDRNUM            (9)

#define NDIS_ENTITY_IPV4                   (0x1)    /*该NDIS实体对应承载支持IPV4*/
#define NDIS_ENTITY_IPV6                   (0x2)    /*该NDIS实体对应承载支持IPV4*/
/*NDIS 根据RabId获得Index*/
/*#define NDIS_GetIndexByRabId(ucRabId)      ((ucRabId) - MIN_VAL_EPSID)*/
/*Userplane huibo end*/

#define NDIS_SPE_CACHE_HDR_SIZE         (IMM_MAC_HEADER_RES_LEN + sizeof(ETH_IPFIXHDR_STRU))


#if (VOS_OS_VER != VOS_WIN32)
    /*单板PID,FID，待定义*/
    #define NDIS_TASK_PID     PS_PID_APP_NDIS
    #define NDIS_TASK_FID     PS_FID_APP_NDIS_PPP_DIPC

#ifdef MSP_GUNAS_AT_UNITE
    #define APP_AT_PID        WUEPS_PID_AT
#else
    #define APP_AT_PID        MSP_APP_DS_MUX_PID
#endif
#else
    #define NDIS_TASK_PID     PS_PID_NDIS
    /*#define NDIS_ULTASK_PID     LUEPS_PID_NDIS_UL
 */

    /*#define NDIS_ULTASK_FID     LUEPS_FID_APP_UL_NDIS
 */
    #define NDIS_TASK_FID     LUEPS_FID_APP_NDIS

    #define APP_AT_PID        LUEPS_PID_AT
#endif


#define NDIS_MODULE_UL          UE_MODULE_NDIS_UL
#define NDIS_MODULE_DL          UE_MODULE_NDIS_DL
#define NDIS_MODULE_COM          UE_MODULE_NDIS_COM

#define NDIS_L4_AT              0xF030 /* MSP AT的模块ID*/

/*A核监控-关键事件上报事件ID偏移,需保证与PS已有ID值不重复*/
#define NDIS_OM_KEY_EVENT_BASE_ID         0x11000



#define NDIS_OM_ID(ulModuleId, ulLogType)     DIAG_ID(ulModuleId, ulLogType)


#define NDIS_ReportEventLog(ulModuleId,ulLogType, ulEventID)
#define NDIS_LOG(ModulePID, SubMod, Level, pcString)
#define NDIS_LOG1(ModulePID, SubMod, Level, pcString, lPara1)
#define NDIS_LOG2(ModulePID, SubMod, Level, pcString, lPara1,lPara2)
#define NDIS_LOG3(ModulePID, SubMod, Level, pcString, lPara1,lPara2,lPara3)
#define NDIS_LOG4(ModulePID, SubMod, Level, pcString, lPara1,lPara2,lPara3,lPara4)

#define NDIS_INFO_LOG(ModuleId, String)
#define NDIS_INFO_LOG1(ModuleId, String,Para1)
#define NDIS_INFO_LOG2(ModuleId, String,Para1,Para2)
#define NDIS_INFO_LOG3(ModuleId, String,Para1,Para2,Para3)
#define NDIS_INFO_LOG4(ModuleId, String,Para1,Para2,Para3,Para4)


#define NDIS_WARNING_LOG(ModuleId, String)
#define NDIS_WARNING_LOG1(ModuleId, String,Para1)
#define NDIS_WARNING_LOG2(ModuleId, String,Para1,Para2)
#define NDIS_WARNING_LOG3(ModuleId, String,Para1,Para2,Para3)
#define NDIS_WARNING_LOG4(ModuleId, String,Para1,Para2,Para3,Para4)

#define NDIS_ERROR_LOG(ModuleId, String)
#define NDIS_ERROR_LOG1(ModuleId, String,Para1)
#define NDIS_ERROR_LOG2(ModuleId, String,Para1,Para2)
#define NDIS_ERROR_LOG3(ModuleId, String,Para1,Para2,Para3)
#define NDIS_ERROR_LOG4(ModuleId, String,Para1,Para2,Para3,Para4)


/*通过ModemId和BearerID组合成ExBearerID，高2bit为ModemId,低6bit为BearerID*/
#define NDIS_FORM_EXBID(ModemId,BearerId)          ((VOS_UINT8)(((ModemId) << 6) | (BearerId)))

/*从扩展ExBearerID中获得ModemId*/
#define NDIS_GET_MODEMID_FROM_EXBID(ExBearerId)    (VOS_UINT16)(((ExBearerId) & 0xC0) >> 6)

/*从扩展ExBearerID中获得BearerID*/
#define NDIS_GET_BID_FROM_EXBID(ExBearerId)      (VOS_UINT8)((ExBearerId) & 0x3F)

#if (defined(CONFIG_BALONG_SPE))
#define NDIS_SPE_MEM_CB(pstImmZc)       ((NDIS_SPE_MEM_CB_STRU *)&((pstImmZc)->dma))

/*lint -emacro({717}, NDIS_SPE_MEM_MAP)*/
#define NDIS_SPE_MEM_MAP(pstImmZc, ulLen)\
            do\
            {\
                if (VOS_TRUE == NDIS_IsSpeMem(pstImmZc))\
                {\
                    NDIS_SpeMemMapRequset(pstImmZc, ulLen);\
                }\
            } while(0)

/*lint -emacro({717}, NDIS_SPE_MEM_UNMAP)*/
#define NDIS_SPE_MEM_UNMAP(pstImmZc, ulLen)\
            do\
            {\
                if (VOS_TRUE == NDIS_IsSpeMem(pstImmZc))\
                {\
                    NDIS_SpeMemUnmapRequset(pstImmZc, ulLen);\
                }\
            } while(0)
#else
#define NDIS_SPE_MEM_MAP(pstImmZc, ulLen)
#define NDIS_SPE_MEM_UNMAP(pstImmZc, ulLen)
#endif



#ifdef _lint
#define ACPU_PID_ADS_UL     211
#endif


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum
{
   ARP_PAYLOAD   = 0x0608,
   IP_PAYLOAD    = 0x0008,
   IPV6_PAYLOAD  = 0xdd86,
   GMAC_PAYLOAD_BUTT
}GMAC_PAYLOAD_TYPE_ENUM;

typedef enum IP_CLASS_TYPE
{
    IP_A_CLASS                              = 0x0,/*A类型IP*/
    IP_B_CLASS                              = 0x1,/*B类型IP*/
    IP_C_CLASS                              = 0x2,/*C类型IP*/
    IP_CLASS_BUTT
}IP_CLASS_TYPE_ENUM;
typedef VOS_UINT32  IP_CLASS_TYPE_UINT32;

/*****************************************************************************
 结构名    : NDIS_RAB_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : NDIS承载类型枚举
*****************************************************************************/
typedef enum
{
    NDIS_RAB_NULL     = 0,                /*该承载未激活*/
    NDIS_RAB_IPV4     = 1,                /*该承载只支持IPV4*/
    NDIS_RAB_IPV6     = 2,                /*该承载只支持IPV6*/
    NDIS_RAB_IPV4V6   = 3,                /*该承载同时支持IPV4和IPV6*/
    NDIS_RAB_BUTT
}NDIS_RAB_TYPE_ENUM;
typedef VOS_UINT8 NDIS_RAB_TYPE_UINT8;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/
#define NAS_NDIS_MAX_ITEM   11
/*****************************************************************************
结构名    : IPV4_CFG_ITEM_STRU
协议表格  :
ASN.1描述 :
结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8    aucUeIpV4Addr[IPV4_ADDR_LEN];
    VOS_UINT8    aucGwIpV4Addr[IPV4_ADDR_LEN];
    VOS_UINT8    aucNmaskIpV4Addr[IPV4_ADDR_LEN];
    VOS_UINT32   ulDnsServerNum;


} IPV4_CFG_ITEM_STRU;

/*****************************************************************************
结构名    : IPV6_CFG_ITEM_STRU
协议表格  :
ASN.1描述 :
结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8    aucUeIpV6Addr[IPV6_ADDR_LEN];
    VOS_UINT8    aucGwIpV6Addr[IPV6_ADDR_LEN];
    VOS_UINT8    aucNmaskIpV6Addr[IPV6_ADDR_LEN];
} IPV6_CFG_ITEM_STRU;

/*****************************************************************************
 结构名    : NAS_NDIS_ARPCFG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : NAS NDIS配置
*****************************************************************************/
typedef struct
{
    VOS_UINT32           ulIpV4ValidNum;
    IPV4_CFG_ITEM_STRU   autIpV4Cfg[NAS_NDIS_MAX_ITEM];

    VOS_UINT32           ulIpV6ValidNum;
    IPV4_CFG_ITEM_STRU   autIpV6Cfg[NAS_NDIS_MAX_ITEM];
}NAS_NDIS_ARPCFG_REQ_STRU;

/*****************************************************************************
 结构名    : IPV4_ADDR_ITEM_UN
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef union
{
    VOS_UINT8    aucIPAddr[IPV4_ADDR_LEN];
    VOS_UINT32   ulIpAddr;
} IPV4_ADDR_ITEM_UN;

/*****************************************************************************
结构名    : IPV6_ADDR_ITEM_UN
协议表格  :
ASN.1描述 :
结构说明  :
*****************************************************************************/
typedef union
{
    VOS_UINT8    aucIPAddr[IPV6_ADDR_LEN];
    VOS_UINT32   ulIpAddr[4];
} IPV6_ADDR_ITEM_UN;

/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)   /*单字节对齐*/
#pragma pack(1)
#else
#pragma pack(push, 1)
#endif

/*lint -e958*/
/*lint -e959*/
    /*****************************************************************************
     结构名    : ARP帧结构
     协议表格  :
     ASN.1描述 :
     结构说明  :
    *****************************************************************************/
    typedef struct
    {
        VOS_UINT8            aucDstAddr[ETH_MAC_ADDR_LEN];
        VOS_UINT8            aucSrcAddr[ETH_MAC_ADDR_LEN];
        VOS_UINT16           usFrameType;

        VOS_UINT16           usHardwareType;
        VOS_UINT16           usProtoType;
        VOS_UINT8            ucHardwareLen;
        VOS_UINT8            ucProtoLen;
        VOS_UINT16           usOpCode;

        VOS_UINT8            aucSenderAddr[ETH_MAC_ADDR_LEN];
        IPV4_ADDR_ITEM_UN    unSenderIP;
        VOS_UINT8            aucTargetAddr[ETH_MAC_ADDR_LEN];
        IPV4_ADDR_ITEM_UN    unTargetIP;

        VOS_UINT8   aucRev[18];
    }ETH_ARP_FRAME_STRU;
    /*****************************************************************************
         结构名    :  发给SPE的MAC头
         协议表格  :
         ASN.1描述 :
         结构说明  :
        *****************************************************************************/
        typedef struct
        {
            VOS_UINT8            aucDstAddr[ETH_MAC_ADDR_LEN];
            VOS_UINT8            aucSrcAddr[ETH_MAC_ADDR_LEN];
            VOS_UINT32           ulResv;
        }SPE_MAC_ETHER_HEADER_STRU;

    /*****************************************************************************
     结构名    : ETH_IPFIXHDR_STRU
     协议表格  :
     ASN.1描述 :
     结构说明  : IP固定头
    *****************************************************************************/
    typedef struct
    {
        VOS_UINT8    ucIpHdrLen:4;                 /* header length */
        VOS_UINT8    ucIpVer:4;                    /* version */

        VOS_UINT8    ucServiceType;                /* type of service */
        VOS_UINT16   usTotalLen;                   /* total length */
        VOS_UINT16   usIdentification;             /* identification */
        VOS_UINT16   usOffset;                     /* fragment offset field */
        VOS_UINT8    ucTTL;                        /* time to live*/
        VOS_UINT8    ucProtocol;                   /* protocol */
        VOS_UINT16   usCheckSum;                   /* checksum */
        VOS_UINT32   ulSrcAddr;                    /* source address */
        VOS_UINT32   ulDestAddr;                   /* dest address */
    }ETH_IPFIXHDR_STRU;

    /*****************************************************************************
     结构名    : ETH_UDPHDR_STRU
     协议表格  :
     ASN.1描述 :
     结构说明  : UDP头
    *****************************************************************************/
    typedef struct
    {
        VOS_UINT16      usSrcPort;                 /* source port */
        VOS_UINT16      usDstPort;                 /* dest port */
        VOS_UINT16      usLen;                     /* udp length */
        VOS_UINT16      usChecksum;                /* udp check sum*/
    }ETH_UDPHDR_STRU;

    /*****************************************************************************
     结构名    : IPV4 UDP包结构
     协议表格  :
     ASN.1描述 :
     结构说明  :
    *****************************************************************************/
    typedef struct
    {
        VOS_UINT8           aucDstAddr[ETH_MAC_ADDR_LEN];
        VOS_UINT8           aucSrcAddr[ETH_MAC_ADDR_LEN];
        VOS_UINT16          usFrameType;

    ETH_IPFIXHDR_STRU   stIpHdt;
    VOS_UINT8           aucRev[4];
}ETHFRM_IPV4_PKT_STRU;

/*****************************************************************************
 结构名    : IPV4 IP包结构
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    ETH_IPFIXHDR_STRU   stIpHdt;
    VOS_UINT8           aucRev[4];
}ETHFRM_IPV4_IPPKT_STRU;

/*lint -e959*/
/*lint -e958*/

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif

#if (defined(CONFIG_BALONG_SPE))
/*****************************************************************************
 结构名    : NDIS_SPE_MEM_CB_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : SPE MEM CB结构
*****************************************************************************/
typedef struct
{
    dma_addr_t                          ulDmaAddr;

} NDIS_SPE_MEM_CB_STRU;
#endif

/*****************************************************************************
 结构名    : NDIS_ARP_PERIOD_TIMER_STRU
 协议表格  :
 ASN.1描述 :　
 结构说明  : ARP周期定时器结构体
*****************************************************************************/
typedef struct
{
    HTIMER                              hTm;                                    /* 定时器指针 */
    VOS_UINT32                          ulName;                                 /* 定时器名字 */
    VOS_UINT32                          ulTimerValue;                           /* 定时器时长*/
}NDIS_ARP_PERIOD_TIMER_STRU;

/*****************************************************************************
 结构名    : NDIS_IPV4_INFO_STRU包结构
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32           ulArpInitFlg;   /*是否已获得UE的ARP映射*/
    VOS_UINT32           ulArpRepFlg;    /*ARP请求发送后受到Reply标志*/
    IPV4_ADDR_ITEM_UN    unUeIpInfo;     /*UE IP,源于NAS配置*/
    IPV4_ADDR_ITEM_UN    unGwIpInfo;     /*GW IP,源于NAS配置*/
    IPV4_ADDR_ITEM_UN    unNmIpInfo;     /*NetMask,源于NAS配置*/
    VOS_UINT8            aucUeMacAddr[ETH_MAC_ADDR_LEN];
    VOS_UINT8            aucMacFrmHdr[ETH_MAC_HEADER_LEN]; /*完整以太帧头，便于组包*/
    NDIS_ARP_PERIOD_TIMER_STRU  stArpPeriodTimer; /*为了同64位操作系统兼容，保持在8字节对齐位置*/

    /*DHCP Server Info*/
    VOS_UINT32           ulIpAssignStatus;
    IPV4_ADDR_ITEM_UN    unPrimDnsAddr;
    IPV4_ADDR_ITEM_UN    unSecDnsAddr;
    IPV4_ADDR_ITEM_UN    unPrimWinsAddr;
    IPV4_ADDR_ITEM_UN    unSecWinsAddr;

} NDIS_IPV4_INFO_STRU;

/*****************************************************************************
 结构名    : NDIS_ENTITY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    NDIS_RAB_TYPE_UINT8             ucRabType;
    VOS_UINT8                       ucRabId; /*保存的是ExRabId的值*/
    PS_BOOL_ENUM_UINT8              enUsed;  /*PS_TRUE:该实体被使用，PS_FALSE:该实体空闲*/
    VOS_UINT8                       ucRev;   /*预留字节*/
    UDI_HANDLE                      ulHandle;
    NDIS_IPV4_INFO_STRU             stIpV4Info;
    VOS_INT32                       lSpePort;
    VOS_UINT32                      ulSpeIpfFlag;
} NDIS_ENTITY_STRU;

/*****************************************************************************
结构名    : NDIS_STAT_INFO_STRU
协议表格  :
ASN.1描述 :
结构说明  : NDIS统计量结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32      ulDicardUsbFrmNum;        /*上行丢弃的USB数据包个数*/
    VOS_UINT32      ulRecvUsbPktSuccNum;      /*上行成功接收到USB的包的个数*/
    VOS_UINT32      ulSendPktToAdsSucNum;     /*上行发送到ADS成功的个数*/
    VOS_UINT32      ulDicardAdsPktNum;        /*下行被丢弃的ADS 数据包NUM*/
    VOS_UINT32      ulRecvAdsPktSuccNum;      /*下行从ADS收到包成功个数*/
    VOS_UINT32      ulGetIpv6MacFailNum;      /*下行发包时获取IPV6 MAC地址失败个数 */
    VOS_UINT32      ulDlPktDiffRabNum;        /*下行数据包类型和承载类型不一致个数*/
    VOS_UINT32      ulAddMacHdrFailNum;       /*添加MAC头失败的统计*/
    VOS_UINT32      ulDlSendPktFailNum;       /*发送包失败的统计量*/
    VOS_UINT32      ulDlSendPktSuccNum;       /*下行成功发送数据包至底软的统计量*/

    VOS_UINT32      ulRecvDhcpPktNum;         /*接收到的DHCP包*/

    /*ARP 统计信息*/
    VOS_UINT32      ulRecvArpReq;             /*收到的ARP Request包*/
    VOS_UINT32      ulRecvArpReply;           /*收到的ARP Reply包*/
    VOS_UINT32      ulProcArpError;           /*处理ARP失败个数*/
    VOS_UINT32      ulSendArpReqSucc;         /*发送ARP Request成功包*/
    VOS_UINT32      ulSendArpReqFail;         /*发送ARP Request失败数*/
    VOS_UINT32      ulArpReplyNotRecv;        /*ARP请求没有收到Rely的计数*/
    VOS_UINT32      ulSendArpReply;           /*发送ARP REPLY个数*/
    VOS_UINT32      ulSendArpDhcpNDFailNum;   /*发送ARP或DHCP或ND包失败个数*/
}NDIS_STAT_INFO_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
extern NDIS_STAT_INFO_STRU        g_stNdisStatStru;
#define   NDIS_STAT_UL_DISCARD_USBPKT(n)              (g_stNdisStatStru.ulDicardUsbFrmNum          += (n))
#define   NDIS_STAT_UL_RECV_USBPKT_SUCC(n)            (g_stNdisStatStru.ulRecvUsbPktSuccNum        += (n))
#define   NDIS_STAT_UL_SEND_ADSPKT(n)                 (g_stNdisStatStru.ulSendPktToAdsSucNum        += (n))
#define   NDIS_STAT_DL_DISCARD_ADSPKT(n)              (g_stNdisStatStru.ulDicardAdsPktNum          += (n))
#define   NDIS_STAT_DL_RECV_ADSPKT_SUCC(n)            (g_stNdisStatStru.ulRecvAdsPktSuccNum        += (n))
#define   NDIS_STAT_DL_GET_IPV6MAC_FAIL(n)            (g_stNdisStatStru.ulGetIpv6MacFailNum        += (n))
#define   NDIS_STAT_DL_PKT_DIFF_RAB_NUM(n)            (g_stNdisStatStru.ulDlPktDiffRabNum          += (n))
#define   NDIS_STAT_DL_ADDMACFRM_FAIL(n)              (g_stNdisStatStru.ulAddMacHdrFailNum         += (n))
#define   NDIS_STAT_DL_SEND_USBPKT_FAIL(n)            (g_stNdisStatStru.ulDlSendPktFailNum         += (n))
#define   NDIS_STAT_DL_SEND_USBPKT_SUCC(n)            (g_stNdisStatStru.ulDlSendPktSuccNum         += (n))

#define   NDIS_STAT_UL_RECV_DHCPPKT(n)                (g_stNdisStatStru.ulRecvDhcpPktNum           += (n))

#define   NDIS_STAT_UL_RECV_ARP_REQUEST(n)            (g_stNdisStatStru.ulRecvArpReq               += (n))
#define   NDIS_STAT_DL_RECV_ARP_REPLY(n)              (g_stNdisStatStru.ulRecvArpReply             += (n))
#define   NDIS_STAT_PROC_ARP_FAIL(n)                  (g_stNdisStatStru.ulProcArpError             += (n))
#define   NDIS_STAT_DL_SEND_ARP_REQUEST_SUCC(n)       (g_stNdisStatStru.ulSendArpReqSucc           += (n))
#define   NDIS_STAT_DL_SEND_ARP_REQUEST_FAIL(n)       (g_stNdisStatStru.ulSendArpReqFail           += (n))
#define   NDIS_STAT_ARPREPLY_NOTRECV(n)               (g_stNdisStatStru.ulArpReplyNotRecv          += (n))
#define   NDIS_STAT_DL_SEND_ARP_REPLY(n)              (g_stNdisStatStru.ulSendArpReply             += (n))
#define   NDIS_STAT_DL_SEND_ARPDHCPPKT_FAIL(n)        (g_stNdisStatStru.ulSendArpDhcpNDFailNum     += (n))

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_UINT32 Ndis_Init( VOS_VOID );
extern VOS_UINT32 Ndis_ProcArpMsg(ETH_ARP_FRAME_STRU* pstArpMsg, VOS_UINT8 ucRabId);
extern VOS_VOID Ndis_UlNcmFrmProc(VOS_UINT8 ucExRabId, IMM_ZC_STRU *pstImmZc);
extern VOS_UINT32 Ndis_DlSendNcm(VOS_UINT8 ucRabId, ADS_PKT_TYPE_ENUM_UINT8 ucPktType, IMM_ZC_STRU *pstImmZc);
extern VOS_UINT32  Ndis_SendRequestArp(NDIS_IPV4_INFO_STRU  *pstArpInfoItem, VOS_UINT8 ucRabId);
extern VOS_UINT32 Ndis_ChkRabIdValid(VOS_UINT8 ucRabId);
extern NDIS_ENTITY_STRU* NDIS_GetEntityByRabId(VOS_UINT8 ucExRabId);
extern NDIS_ENTITY_STRU* NDIS_AllocEntity(VOS_VOID);
extern VOS_VOID Ndis_StopARPTimer(NDIS_ARP_PERIOD_TIMER_STRU *pstArpPeriodTimer);

extern VOS_UINT32 Ndis_MsgHook (VOS_UINT8 *pucData,VOS_UINT32 ulLength,
     AT_NDIS_MSG_TYPE_ENUM_UINT32 enMsgId);

extern VOS_VOID Ndis_LomTraceRcvUlData(VOS_VOID);
extern VOS_VOID Ndis_LomTraceRcvDlData(VOS_VOID);
extern VOS_UINT8 Ndis_FindRabIdBySpePort(VOS_INT32 lPort, VOS_UINT16 usFrameType);
extern VOS_UINT8 Ndis_FindRabIdByHandle(UDI_HANDLE ulhandle, VOS_UINT16 usFrameType);
extern VOS_UINT32 Ndis_DlUsbSendNcm(VOS_UINT8 ucExRabId, ADS_PKT_TYPE_ENUM_UINT8 ucPktType, IMM_ZC_STRU *pstImmZc);



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

#endif /* end of LUPNdis.c */

