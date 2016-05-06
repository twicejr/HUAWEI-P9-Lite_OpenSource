/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_pcap_api.h
*
*  Project Code: VISP
*   Module Name:   
*  Date Created: 2009-04-08
*        Author: wuhailan103194
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-04-08   wuhailan103194          Create
*  2012-03-31   pengrui                 DTS2012033004012网络整改,剥离分层获取报文功能
*               对外发布的lib中不包括该功能,产品不能使用该文件中的任何内容.
*******************************************************************************/
#ifndef __TCPIP_PCAP_API_H__
#define __TCPIP_PCAP_API_H__

#ifdef __cplusplus
extern "C"{
#endif

/*****************************宏定义**************************************************/

/*链路类型, 目前VISP仅支持ETH和PPP类型和ATM类型 */
#define PCAP_LINK_TYPE_ETH               1 /* Ethernet (10Mb) */
#define PCAP_LINK_TYPE_PPP               9 /* Point-to-point Protocol */
#define PCAP_LINK_TYPE_ATM_RFC1483      11 /* LLC/SNAP encapsulated atm */

#define PCAP_LINK_NULL                   0 /* no link-layer encapsulation */
#define PCAP_LINK_TYPE_ETH3MB            2 /* Experimental Ethernet (3Mb) */
#define PCAP_LINK_TYPE_AX25              3 /* Amateur Radio AX.25 */
#define PCAP_LINK_TYPE_PRONET            4 /* Proteon ProNET Token Ring */
#define PCAP_LINK_TYPE_CHAOS             5 /* Chaos */
#define PCAP_LINK_TYPE_IEEE802           6 /* IEEE 802 Networks */
#define PCAP_LINK_TYPE_ARCNET            7 /* ARCNET */
#define PCAP_LINK_TYPE_SLIP              8 /* Serial Line IP */
#define PCAP_LINK_TYPE_FDDI             10 /* FDDI */
#define PCAP_LINK_TYPE_RAW              12 /* raw IP */
#define PCAP_LINK_TYPE_SLIP_BSDOS       13 /* BSD/OS Serial Line IP */
#define PCAP_LINK_TYPE_PPP_BSDOS        14 /* BSD/OS Point-to-point Protocol */

#define PCAP_FILEHEAD_LEN               24 /* PCAP外层封装的文件头长度 */
#define PCAP_FILEHEAD_MAGIC     0xa1b2c3d4 /* PCAP外层封装的文件头中的魔术字字段值 */
#define PCAP_FILEHEAD_VERSION_MAJOR      2 /* PCAP外层封装的文件头中的VERSION MAJOR字段值 */
#define PCAP_FILEHEAD_VERSION_MINOR      4 /* PCAP外层封装的文件头中的VERSION MINOR字段值 */
#define PCAP_FILEHEAD_SNAPLEN       0xffff /* 默认支持最大65535字节长度的报文输出 */

#define PCAP_MACADDRLEN                  6 /* physical地址长度 */

#define PCAP_DIRECTION_IN                2 /* 支持报文接收方向上获取报文 */
#define PCAP_DIRECTION_OUT               1 /* 支持报文发送方向上获取报文 */
#define PCAP_DIRECTION_ALL               0 /* 支持报文接收和发送方向上获取报文 */

/*****************************枚举结构错误码定义********************************************/
typedef enum enPcapPktFilterErrorCode
{
    PCAP_OK = VOS_OK,                   /* 0 OK    */
    PCAP_ERR,                           /* 1 未知错误 */
    PCAP_ERR_PARAWRONG,
    PCAP_ERR_INVALID_SWITCH,
    PCAP_ERR_POINTER_NULL,
    PCAP_ERR_INVALID_TYPE,
    PCAP_ERR_IFISNULL,
    PCAP_ERR_INVALID_IFTYPE,
    PCAP_ERR_INVALID_DIRECTION
}TCPIP_PCAP_ERRCODE_E;

/*****************************数据结构定义********************************************/

typedef struct TCPIP_TIMEVAL
{
    ULONG  tv_sec;       /* no. of seconds */
    ULONG  tv_usec;      /* no. of micro seconds */
}TCPIP_TIMEVAL_S;

typedef struct TCPIP_PCAP_PKTHDR
{
    TCPIP_TIMEVAL_S ts;     /* time stamp */
    ULONG           caplen; /* length of portion present */
    ULONG           len;    /* length this packet (off wire) */
}TCPIP_PCAP_PKTHDR_S;

typedef struct TCPIP_PCAP_FILE_HEADER
{
    ULONG    magic;
    USHORT   version_major;
    USHORT   version_minor;
    LONG     thiszone;     /* gmt to local correction */
    ULONG    sigfigs;      /* accuracy of timestamps */
    ULONG    snaplen;      /* max length saved portion of each pkt */
    ULONG    linktype;     /* data link type (DLT_*) */
}TCPIP_PCAP_FILE_HEADER_S;


typedef struct TCPIP_PKT_FILTER
{
    ULONG ulIfIndex;
    ULONG ulProtocol;
    ULONG ulSrcIP;
    ULONG ulDstIP;
    UCHAR ucSrcMac[PCAP_MACADDRLEN];
    UCHAR ucDstMac[PCAP_MACADDRLEN];
    ULONG ulInOrOut;   /*  0-默认值，表示支持发送和接收；1-表示发送；2--表示接收 */
}TCPIP_PKT_FILTER_S;

typedef ULONG (*TCPIP_PCAP_PKTFILTER_OUTPUT_HOOK_FUNC)(CHAR *pcBuf, ULONG ulMsglen, ULONG ulLinkType);

/********************************函数声明*********************************************/

/*******************************************************************************
*    Func Name: TCPIP_Pcap_RegFuncPktFilterOutput
* Date Created: 2009-04-08
*       Author: wuhailan103194
*  Description: 分层获取报文输出信息注册钩子
*        Input: TCPIP_PCAP_PKTFILTER_OUTPUT_HOOK_FUNC pfFunc:函数钩子指针
*       Output: 
*       Return: 成功VOS_OK,其他返回失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-08   wuhailan103194          Create
*
*******************************************************************************/
extern ULONG TCPIP_Pcap_RegFuncPktFilterOutput(TCPIP_PCAP_PKTFILTER_OUTPUT_HOOK_FUNC pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_Pcap_SetPacketFilter
* Date Created: 2009-04-08
*       Author: wuhailan103194
*  Description: 分层获取报文功能接口设置及过滤规则设置接口
*        Input: ULONG ulSwitch:功能开关
*               ULONG ulFilterType:过滤类型
*               TCPIP_PKT_FILTER_S *pstFilterRule:过滤规则
*               ULONG ulMaxPkt:允许输出的最大报文数目
*       Output: 
*       Return: 成功VOS_OK,其他返回失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-08   wuhailan103194          Create
*
*******************************************************************************/
extern ULONG TCPIP_Pcap_SetPacketFilter(ULONG ulSwitch, ULONG ulFilterType, TCPIP_PKT_FILTER_S *pstFilterRule, ULONG ulMaxPkt);

/*******************************************************************************
*    Func Name: TCPIP_Pcap_GetFileHead
* Date Created: 2009-04-10
*       Author: wuhailan103194
*  Description: 获取PCAP外层封装的文件头信息,当前通过VISP该接口给出去的封装头win32小头序下二进制值为:
*               以太链路类型:
*               D4 C3 B2 A1 02 00 04 00 00 00 00 00 00 00 00 00
*               FF FF 00 00 01 00 00 00
*               或者
*               PPP点对点链路类型:
*               D4 C3 B2 A1 02 00 04 00 00 00 00 00 00 00 00 00
*               FF FF 00 00 09 00 00 00
*               即处理如下:
*               stPcapFileHdr.linktype = ulLinkType;
*               stPcapFileHdr.snaplen  = 0xffff;
*               stPcapFileHdr.magic    = 0xa1b2c3d4;
*               stPcapFileHdr.version_major = 2;
*               stPcapFileHdr.version_minor = 4;  
*               用户也可以参考VISP头文件中的TCPIP_PCAP_FILE_HEADER_S结构字段描述给出Ethereal文件头格式描述
*        Input: ULONG ulLinkType:链路类型
*       Output: CHAR szFileHead[PCAP_FILEHEAD_LEN]:返回的文件头信息,要求由用户传入24字节长度内存
*       Return: 成功VOS_OK,其他返回失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-10   wuhailan103194          Create
*
*******************************************************************************/
extern ULONG TCPIP_Pcap_GetFileHead(CHAR szFileHead[PCAP_FILEHEAD_LEN], ULONG ulLinkType);

#ifdef __cplusplus
}
#endif      /* end of __cplusplus   */

#endif /* __TCPIP_PCAP_API_H__ */


