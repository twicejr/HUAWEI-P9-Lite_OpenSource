/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              poec_def.h   
 *
 *  Project Code: VISP1.5
 *   Module Name: PPPoE Client
 *  Date Created: 2003-01-11
 *        Author: liuhui
 *   Description: PPPoE Client模块的宏定义
 *               
 *----------------------------------------------------------------------*
 *  Modification History 
 *  DATE             NAME               DESCRIPTION
 *  2003-01-11       liuhui             Create file
 *  2005-09-15       t45114             Modify  
 *  2006-03-30       liai               Adjust for D00660
 *  2006/04/21      liai                Adjust for D00865
 *  2006-05-12      languanghua         支持ARM CPU 四字节对齐
 *  2006-05-13      l48923              Delete useless code
 ************************************************************************/

#ifndef  _POEC_DEF_H_
#define  _POEC_DEF_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "tcpip/pppoec/include/poec_api.h"

/* 系统中允许同时运行的PPPoE Client session数目 */
#define PPPOE_CLIENT_MAX_SESSION 255

/*PPPoE 报文方向，收:0; 发:1*/
#define PPPOE_IN  0
#define PPPOE_OUT 1

/* references: RFC 2516 */
/* 针对PPPoE 的ETHER_TYPE域  */
#define PPPOE_ETH_P_DISC 0x8863 /* discovery stage */
#define PPPOE_ETH_P_SESS 0x8864 /* session stage */

/*** PPPoE Client Session状态 ***/
#define PPPOE_STATE_IDLE        0   /*空闲状态，没有开始PPPoE 呼叫*/
#define PPPOE_STATE_PADI_SENT   1   /*发出padi报文等待pado报文*/
#define PPPOE_STATE_PADR_SENT   2   /*发出padr报文等待pads报文*/
#define PPPOE_STATE_PPP_NEG     3   /*开始session阶段的ppp协商*/
#define PPPOE_STATE_PPP_UP      4   /*session阶段ppp协商已经通过，可以传输数据*/

#define PPPOE_STATE_DISCOVERY   5   /* PPPoE处于Discivery阶段 */
#define PPPOE_STATE_SESSION     6   /* PPPoE处于Session阶段 */

/*PPP在验证过程中传递给DDR的命令原语*/
#define PPPOE_PPP_NEG_UP        1   /*链路层告知PPPOE IPCP UP*/
/* Added by Sunmo(44939) for A82D12574 */
#define PPPOE_PPP_NEG_DOWN      2   /*链路层告知PPPOE IPCP DOWN*/

/*** PPPoE Client定时器参数 ***/
#define PPPOE_TIMER_MAX_LEN     32  /*PPPoE Client超时处理的最大时长:32秒*/
#define PPPOE_TIMER_MIN_LEN     1   /*PPPoE Client超时处理的最小时长:1秒*/
#define PPPOE_SESSION_RESTART_TIMER_LEN     16  /*会话被reset 命令清除后重新连接的延时:16秒*/


/*PPPoE Client所用的DIALER口MTU*/
#define PPPOE_DIALER_MTU        1450

/***PPP 报文头相关长度***/
#define PPPOE_PPP_ADD_CON_LEN   2   /*PPP 数据的FF03地址控制字段长度*/
#define PPPOE_PPP_PROTOCOL_LEN  2   /*ppp 协议字段长度*/

/* ethernet 头长度 */
#define PPPOE_ETHER_HEADER_LEN  14

/*PPPoE VER & Type 字段长度*/
#define PPPOE_VER_TYPE_LEN      1

/*PPPoE Code 字段长度*/
#define PPPOE_CODE_LEN          1

/*PPPoE Session ID 字段长度*/
#define PPPOE_SESSION_ID_LEN    2

/*PPPoE Length 字段长度*/
#define PPPOE_LENGTH_LEN        2

/* 携带有Vlan ID字段的ethernet头长度 */
#define PPPOE_ETHER_HEADER_LEN_VLAN     18

/* ethernet 广播地址 */
#define PPPOE_MAC_BCAST_ADDR "\xff\xff\xff\xff\xff\xff"

/***以太网头长度***/
#define PPPOE_HEADER_LEN        20  /*PPPoE 头信息，包括以太网帧头*/
#define PPPOE_HEADER_LEN_VLAN   24  /*PPPoE 头信息，包括以太网帧头(有vlan)*/


/* PPPoE 净荷的长度包括头信息 */
#define PPPOE_MIN_ETHERNET_PAYLOAD  6       /*PPPoE 帧头*/
#define PPPOE_MAX_ETHERNET_PAYLOAD  1500    /*ethernet MTU*/

/*删除VirtualAccess接口的延迟时间*/
#define PPPOE_DELVAIF_TIMER         10

/*** 各种Ethernet 帧长度 ***/

/*PPPoE 最短的以太网帧长*/
#define PPPOE_MIN_ETHERNET_LEN \
    ( PPPOE_ETHER_HEADER_LEN + PPPOE_MIN_ETHERNET_PAYLOAD )
#define PPPOE_MIN_ETHERNET_LEN_VLAN \
    ( PPPOE_ETHER_HEADER_LEN_VLAN + PPPOE_MIN_ETHERNET_PAYLOAD )

/*PPPoE 最长的以太网帧长*/
/* 不带 VLan ID*/
#define PPPOE_MAX_ETHERNET_LEN \
    ( PPPOE_ETHER_HEADER_LEN + PPPOE_MAX_ETHERNET_PAYLOAD )
/* 带 VLan ID*/
#define PPPOE_MAX_ETHERNET_LEN_VLAN \
    ( PPPOE_ETHER_HEADER_LEN_VLAN + PPPOE_MAX_ETHERNET_PAYLOAD )


/*PPPoE TAG-TYPE 字段长度*/
#define PPPOE_TAG_TYPE_LEN      2

/*PPPoE TAG-LENGTH 字段长度*/
#define PPPOE_TAG_LENGTH_LEN    2

/*PPPoE TAG 头长度（包括type和length两个字段）*/
#define PPPOE_TAG_HEAD_LEN ( PPPOE_TAG_TYPE_LEN + PPPOE_TAG_LENGTH_LEN )

/*PPPoE Tag域的最大长度，包括PPPOE_TAG_HEAD_LENGTH*/
#define PPPOE_MAX_TAG_LEN ( PPPOE_MAX_ETHERNET_PAYLOAD \
        - PPPOE_MIN_ETHERNET_PAYLOAD )

/*PPPoE Tag域PAYLOAD(TAGVALUE)的最大长度*/
#define PPPOE_MAX_TAG_PAYLOAD_LEN ( PPPOE_MAX_ETHERNET_PAYLOAD \
        - PPPOE_MIN_ETHERNET_PAYLOAD - PPPOE_TAG_HEAD_LEN )

/*PPPoE Version & Type, 目前为0x11*/
#define PPPOE_VERSION_1_TYPE_1  0x11

/* PPPoE 的各种codes编码 */
#define PPPOE_CODE_SESS 0x00 /* PPPoE时段  PPPoE session */
#define PPPOE_CODE_PADI 0x09 /* PPPoE主动发现开始  PPPoE Active Discovery Initiation */
#define PPPOE_CODE_PADO 0x07 /* PPPoE主动发现意图  PPPoE Active Discovery Offer */
#define PPPOE_CODE_PADR 0x19 /* PPPoE主动发现请求  PPPoE Active Discovery Request */
#define PPPOE_CODE_PADS 0x65 /* PPPoE主动发现时间确认  PPPoE Active Discovery Session-confirmation */
#define PPPOE_CODE_PADT 0xa7 /* PPPoE主动发现终止  PPPoE Active Discovery Terminate */

/* PPPoE 的各种tag type类型 */
#define PPPOE_TAG_END_OF_LIST           0x0000  /* PPPoE_TAG结束表 */
#define PPPOE_TAG_SERVICE_NAME          0x0101  /* PPPoE_TAG服务名 */
#define PPPOE_TAG_AC_NAME               0x0102  /* PPPoE_TAGac名 */
#define PPPOE_TAG_HOST_UNIQ             0x0103  /* PPPoE_TAG主机标志 */
#define PPPOE_TAG_AC_COOKIE             0x0104  /* PPPoE_TAG*/
#define PPPOE_TAG_VENDOR_SPECIFIC       0x0105  /* PPPoE_TAG细节*/
#define PPPOE_TAG_RELAY_SESSION_ID      0x0110  /* PPPoE_TAG回复时段ID*/
#define PPPOE_TAG_SERVICE_NAME_ERROR    0x0201  /* PPPoE_TAG服务名错误 */
#define PPPOE_TAG_AC_SYSTEM_ERROR       0x0202  /* PPPoE_TAGac系统错误 */
#define PPPOE_TAG_GENERIC_ERROR         0x0203  /* PPPoE_TAG一般错误 */

/*PPPoE 各种tag的长度*/
#define PPPOE_LEN_SEVICENAME_TAG        0x0000
#define PPPOE_LEN_HOSTUNIQ_TAG          0x0002

/*PPPoE PADT 报文净荷的长度*/
#define PPPOE_PADT_PAYLOAD_LEN          0


/*PPPoE Client所用的Dialer Bundle范围*/
#define PPPOE_DIALER_BUNDLE_LOW         1
#define PPPOE_DIALER_BUNDLE_HIGH        255


/*Host-Uniq tag Enable or Disable*/
#define PPPOE_CLIENT_SESSION_HOSTUINQ_ENABLE    1
#define PPPOE_CLIENT_SESSION_HOSTUINQ_DISABLE   0

/*PPPoE Client Idle-Timeout Enalbe or Disable*/
#define PPPOE_CLIENT_SESSION_IDLE_TIMEOUT_ENABLE    1
#define PPPOE_CLIENT_SESSION_IDLE_TIMEOUT_DISABLE   0

/*PPPoE Client Session Trigger mode Enalbe or Disable*/
#define PPPOE_CLIENT_SESSION_TRIGGER_ENABLE     1
#define PPPOE_CLIENT_SESSION_TRIGGER_DISABLE    0


/*PPPoE Client应用是否使能*/
#define PPPOE_CLIENT_ENABLE     1   /*使能*/
#define PPPOE_CLIENT_DISABLE    0   /*禁止*/

#define PPPOE_SUCCESS           0   /*处理成功*/
#define PPPOE_FAILURE           1   /*处理失败*/

/*Queue Length的各种长度*/
#define PPPOE_CLIENT_QUEUE_LENGTH_MIN_LENGTH        1   /*最小*/
#define PPPOE_CLIENT_QUEUE_LENGTH_MAX_LENGTH        100 /*最大*/
#define PPPOE_CLIENT_SESSION_DEFAULT_QUEUE_LENGTH   10  /*缺省*/

#define PPPOE_CLIENT_IDLE_MIN_TIME  1       /*最小Idle超时*/
#define PPPOE_CLIENT_IDLE_MAX_TIME  65535   /*最大Idle超时*/

#ifndef AF_PPPOE_CLIENT
#define AF_PPPOE_CLIENT             14      /*PPPoE Client包标志*/
#endif

#define PPPOE_CLINET_BACKUP_DISC    1 
#define PPPOE_CLINET_BACKUP_CONN    2

/*PPPoE Client所使用的一些宏操作*/
/* 从字符指针cp获得一个char给c，cp指针加1 */
#define PPPOE_GET_CHAR(c, cp) { \
    (c) = *( (UCHAR *)(cp) ); \
    (cp) += 1 ; \
}

/* 将字符c写到字符指针cp处，cp指针加1 */
#define PPPOE_PUT_CHAR(c, cp) { \
    *( (UCHAR *)(cp) ) = (c) ; \
    (cp) += 1 ; \
}

/* 从字符指针cp获得一个ushort值给s，cp指针加2 */
#define PPPOE_GET_SHORT(s, cp) { \
    VOS_CopyVar((s), *((USHORT *)(cp))); \
    (cp) += 2 ; \
}

/* 将ushort变量s的值写到字符指针cp处，cp指针加2 */
#define PPPOE_PUT_SHORT(s, cp) { \
    VOS_CopyVar(*((USHORT*)(cp)), (s)) ; \
    (cp) += 2 ; \
}

/* 从字符指针cp获得一个ulong值给s，cp指针加4 */
#define PPPOE_GET_LONG(l, cp) { \
    VOS_CopyVar((l) , *((ULONG *)(cp))); \
    (cp) += 4 ; \
}

/* 将ulong变量l的值写到字符指针cp处，cp指针加4 */
#define PPPOE_PUT_LONG(l, cp) { \
    VOS_CopyVar(*((ULONG*)(cp)),(l)) ; \
    (cp) += 4 ; \
}

/*将地址ULONG型转换成SOCKADDR_S类型(网络或主机顺序不同类转换)*/
#define PPPOE_IpAddrUlongToSock(ulAddr,pstAddr) \
{ \
    pstAddr->sa_ucLen = sizeof(ULONG) + 2; \
    pstAddr->sa_ucFamily = AF_INET; \
    VOS_CopyVar(*(ULONG*)(pstAddr->sa_cData), ulAddr); \
}

/* 设置/清除debug标志的宏 */
#define POEC_CMD_SETDBGFLAG(ulTargetFlag, ulFlagToSet, bSetFlag) \
        ((ulTargetFlag) = ((bSetFlag)?((ulTargetFlag) | (ulFlagToSet)):((ulTargetFlag) & ~(ulFlagToSet))))


/*报文方向*/
#define PPPOE_CLIENT_IN  0
#define PPPOE_CLIENT_OUT 1


/*Add DialNumber*/
#define NO_BUNDLENUMBER         0       /*Dialer BundleNumber最小的序号是1*/
#define MIN_BUNDLENUMBER        1       /*Dialer BundleNumber最小的序号是1*/
#define MAX_BUNDLENUMBER        255     /*Dialer BundleNumber最大的序号是255*/

#ifndef VOS_TM_IS_TICKING
#define VOS_TM_IS_TICKING       0xA5
#endif
#ifndef VOS_TM_IS_PAUSED
#define VOS_TM_IS_PAUSED        0xAE
#endif


/*----------------------------------------------*
 * 定义错误码
 *----------------------------------------------*/
#define PPPOE_CLIENT_ERR_NULL_IFNET           0x01000001  /*IFNET指针为NULL*/
#define PPPOE_CLIENT_ERR_NOT_ENABLE_PPPOE     0x01000002  /*没有使能PPPOE Client模块*/
#define PPPOE_CLIENT_ERR_SOURCE_MAC           0x01000003  /*源physical地址非法*/
#define PPPOE_CLIENT_ERR_ETHER_TYPE           0x01000004  /*以太网帧类型错误*/
#define PPPOE_CLIENT_ERR_PACKET_LEN           0x01000005  /*报文长度非法*/
#define PPPOE_CLIENT_ERR_COMMAND              0x01000006  /*错误的控制信息命令字*/
#define PPPOE_CLIENT_ERR_NULL_POINTER         0x01000007  /*MBUF报文指针为NULL*/


/*-----------------------------------------------------------*
 * 定义SID，PPPoE Client模块内部使用(需删去vos_id.h中的定义)
 *-----------------------------------------------------------*/
#define SID_COMP_PPPOEC_CLIENT_CB        ( 1 )
#define SID_COMP_PPPOEC_SESSION          ( 2 )

/*Debug information ID*/
/*注意:
如果修改错误码，请同步修改poec_proc.c文件中的
char * Inf_PPPOE_Client_Dbg_Err[]描述信息*/
typedef enum tagPOEC_DEBUG_INFO_INDEX
{
    /****parsing tag error*****/
    PPPOE_CLIENT_PARSE_ERR_TAG_LEN_ERR_PADO,
    PPPOE_CLIENT_PARSE_ERR_NONZERO_END_OF_LIST_PADO1,
    PPPOE_CLIENT_PARSE_ERR_NONZERO_END_OF_LIST_PADO2,
    PPPOE_CLIENT_PARSE_ERR_HOST_UNIQ_NOT_2_PADO,
    PPPOE_CLIENT_PARSE_ERR_HOST_UNIQ_OUT_OF_RANGE_PADO,
    PPPOE_CLIENT_PARSE_ERR_TAG_LEN_ERR_PADS,
    PPPOE_CLIENT_PARSE_ERR_NONZERO_END_OF_LIST_PADS1,
    PPPOE_CLIENT_PARSE_ERR_NONZERO_END_OF_LIST_PADS2,
    PPPOE_CLIENT_PARSE_ERR_HOST_UNIQ_NOT_2_PADS,
    PPPOE_CLIENT_PARSE_ERR_HOST_UNIQ_OUT_OF_RANGE_PADS,
    /****parsing tag error*****/

    PPPOE_CLIENT_PARSE_ERR_INFO_INDEX_MAX
}POEC_DEBUG_INFO_INDEX;


/* PPPOE Client的debug 类型 */
#define PPPOE_CLIENT_DEBUG_DATA_FLAG    0x0001
#define PPPOE_CLIENT_DEBUG_ERROR_FLAG   0x0002
#define PPPOE_CLIENT_DEBUG_EVENT_FLAG   0x0004
#define PPPOE_CLIENT_DEBUG_PACKET_FLAG  0x0008
#define PPPOE_CLIENT_DEBUG_VERBOSE_FLAG 0x0010
#define PPPOE_CLIENT_DEBUG_GR_FLAG      0x0020
#define PPPOE_CLIENT_DEBUG_ALL_FLAG     0xffff /* 由于0xffffffff是命令行的CLI_USELESS_PARA值，故使用0xffff */


/*从poec_sh_def.h移到此处，modified for D00016 by t45114, 2005/12/01*/
#ifndef IC_INFO_PARA_MAXLEN
#define IC_INFO_PARA_MAXLEN             1024
#endif

/*调试打印报文的最大长度*/
#define PPPOE_CLIENT_PRINT_PACKET_LEN   128

#define POEC_SET_SESSION_INFO(pstSession, stSessionInfo)\
{\
    (stSessionInfo).ulEthIfIndex = ((TCPIP_HA_GetBoardType() == TCPIP_HA_AMB) ? \
                                    (pstSession)->pstEthIf->if_ulIfIndex : (ULONG)(UINTPTR)(pstSession)->pstEthIf);\
    (stSessionInfo).ulSessionId  = (pstSession)->usSessionId;\
    (VOID)TCPIP_Mem_Copy((stSessionInfo).szHisMacAddr, PPPOE_MAC_LEN, (pstSession)->szHisMacAddr, PPPOE_MAC_LEN);\
    (VOID)TCPIP_Mem_Copy((stSessionInfo).szOurMacAddr, PPPOE_MAC_LEN, (pstSession)->szOurMacAddr, PPPOE_MAC_LEN);\
}

#define POEC_NP_CREATE 0x1

typedef enum tagPOEC_PKT_TYPE_TO_SEND
{
    POEC_PKT_TYPE_PADI,             /* 要发送PADI报文 */
    POEC_PKT_TYPE_PADR,             /* 要发送PADR报文 */
    POEC_PKT_TYPE_PADT,             /* 要发送PADT报文 */
}POEC_PKT_TYPE_TO_SEND_E;

#define PPPOE_CLIENT_RCV_PADO      1  /* 收到PADO报文 */
#define PPPOE_CLIENT_RCV_PADS      2  /* 收到PADS报文 */


#ifdef __cplusplus
}
#endif

#endif 

