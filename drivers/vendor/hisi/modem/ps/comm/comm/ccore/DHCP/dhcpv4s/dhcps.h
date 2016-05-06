/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Dhcpcs.h
  版 本 号   : 初稿
  作    者   : luoxinsheng
  生成日期   : 2007年11月3日
  最近修改   :
  功能描述   : DHCPServer相关的数据定义
  函数列表   :
  修改历史   :
  1.日    期   : 2007年11月3日
    作    者   : c57548
    修改内容   : 创建文件

******************************************************************************/
#ifndef __DHCPS_H__
#define __DHCPS_H__
/**************************************************************************\
*  Copyright (c) 2000-2002, Huawei Tech. Co., Ltd.
*  All rights reserved.
* 
*  File name:  dhcps.h
*  Project:    Quidway S8016 Dhcp Server
*  Author:     wanghui
*  Version:    V1.0
*  Date:       2001-12-29
*  Description:DHCP SERVER的头文件
*  History:  
*  Others: 
\**************************************************************************/


#define DHCPS_INTERNAL       1     /* 表明采用内置DHCP SERVER */
#define DHCPS_EXTERNAL       0     /* 表明采用外置DHCP SERVER */ 

#define DHCPS_UNICAST        1
#define DHCPS_BROADCAST      0

typedef struct  tagDhcpServerDiag
{
    ULONG ulDhcpRcvTotal;                       /* DHCP收到的报文的总数 */
    
    ULONG ulDhcpRcvFromNps;            /* DHCP收到的从NPS过来的报文数 */    
    ULONG ulDhcpRcvFromSocket;      /* DHCP收到的从socket过来的报文数 */
    
    ULONG ulDhcpSendTotal;          /* DHCP server发出的报文总数 */
    
    ULONG ulDhcpClientPktDeclineTotal; /* DHCP server收到的DECLINE报文数 */
    ULONG ulDhcpClientPktInformTotal;  /* DHCP server收到的INFORM报文数 */
    ULONG ulDhcpClientPktDiscoverTotal;/* DHCP server收到的DISCOVER报文数 */
    ULONG ulDhcpClientPktRequestTotal; /* DHCP server收到的REQUEST报文数 */
    ULONG ulDhcpClientPktReleaseTotal;  /* DHCP server收到的RELEASE报文数 */
    ULONG ulDhcpServerPktOfferTotal;   /* DHCP server发出的OFFER报文数 */
    ULONG ulDhcpServerPktAckTotal;     /* DHCP server发出的ACK报文数 */
    ULONG ulDhcpServerPktNakTotal;     /* DHCP server发出的NAK报文数 */

    /* 一些错误统计信息 */
    ULONG ulDhcpRcvUnknownTotal;       /* DHCP server收到的未知报文总数 */
    ULONG ulMemMallocErrNum;           /* 主要记录dhcpr.c中内存分配失败的次数 */
}DHCPServerDIAG_S;

typedef struct tagSEtherAddr {
    unsigned char AddrByte[6];
} SEtherAddr;


#ifndef SUCCESS
#define SUCCESS                 0
#define FAILURE                  1
#endif

#define  VLAN_MIN_VLANID            2
#define  VLAN_MAX_VLANID            4094

void DHCPS_PrintDebug(CHAR *pcStr );
#define DHCPSOPTION_COUNT 18

#define L2IF_SUCCESS     VOS_OK
#define L2IF_FAILURE     VOS_ERR

#define ETHERNETHARDWARETYPE 1
#define ETHERNETHARDWARELEN  6 

#define DHCP_PKT_BUFF_SIZE 2048 /* 接收dhcp报文的缓存大小 */

/*DHCP报文中"options"字段对应的标志位*/
#define DHCPSUBNETMASK_CODE_FLAGBIT  1 
#define DHCPROUTERIP_CODE_FLAGBIT    (1<<1) 
#define DHCPDNSIP_CODE_FLAGBIT       (1<<2)
#define DHCPDOMAINNAME_CODE_FLAGBIT  (1<<3)

#define DHCPNBNS_CODE_FLAGBIT        (1<<4) 
#define DHCPNBDS_CODE_FLAGBIT        (1<<5) 
#define DHCPNBNT_CODE_FLAGBIT        (1<<6) 
#define DHCPNBSCOPE_CODE_FLAGBIT     (1<<7) 

#define DHCPIPLEASETIME_CODE_FLAGBIT (1<<8)  
#define DHCPRENEWTIME_CODE_FLAGBIT   (1<<9)  
#define DHCPREBINDTIME_CODE_FLAGBIT  (1<<10)  

#ifdef   __WIN32_PLATFORM__
#pragma pack(push, 1)
#endif

typedef struct tagLAM_MACIP
{
    ULONG ulIPAddr;
    ULONG ulFwdInfo;
}VOS_PACKED LAM_MACIP;

#ifdef   __WIN32_PLATFORM__
#pragma pack(pop, 1)
#endif

#define DEBUG_HASH   0
#define SMARTBITS_EMU 0

#define DHCP_MAX_VLANID       4094          /* 最大可用的VLANID值 */ 
#define DHCP_MIN_VLANID       2             /* 最小可用的vlanid值 */ 
#define DHCPR_DEFAULTVLAN     1             /*系统默认的vlan的初始值*/

#define DHCP_MAX_PORT_NUM 512              /* l3支持的最大端口数目 */

/* 将系统中得到的PORT号转为全局编号,最大256个端口 */
/*********************************************************************
 * 现在只有两种子卡GE和FE，每个接口板可以有一个FE子卡（端口0～15）； *
 * 每个接口板可以有2个GE子卡（每个子卡端口0～1）;                    * 
 * 按以下算法,16*(SLOTNO-1)+PICNO*2+PORTNO将每个板的端口统一编号     *
 *********************************************************************/
#define DHCP_GPORT(stInfo) (32*((stInfo).ucSlotNo-1)+(stInfo).ucPICNo*2+(stInfo).ucPortNo)

#define MAX_DHCP_SERVER_GROUP 20    /* L3支持的最大的DHCP SERVER组的个数 */
#define MIN_DHCP_SERVER_GROUP 1
#define MAX_DHCP_SERVER_NUM   2     /* 每个SERVER组支持的SERVER的数目 */

#define _DEBUG_DHCPRELAY 1          /* DHCP RELAY的调试开关 */

#define    DHCPS_PORT        67          /* 用于标识DHCP SERVER的UDP端口号 */
#define    DHCPC_PORT        68          /* 用于标识DHCP CLIENT的UDP端口号 */

#define CLIENTID_LEN         7
#define ETHERNETHARDWARETYPE 1
#define ETHERNETHARDWARELEN  6 

#define  MAGICCOOKIE         0x63825363 /* 网络字节序,DHCP OPTION开始的四个字节为魔术字，用于校验 */
#define  ENDOFOPTIONS        0xff       /* DHCP OPTION的结束标识 */   

#define DHCPOPTION_COUNT     8         /* DHCP OPTION中L3关心的项目的个数,这个需要最后确定 */


#define DHCPSUBNETMASK_CODE  0x01 /* DHCP报文"options"字段含有"Subnet mask"选项的标识字 */
#define DHCPROUTERIP_CODE    0x03 /* DHCP报文"options"字段含有"Routet "选项的标识字 */
#define DHCPDNSIP_CODE       0x06 /*DHCP报文"options"字段含有"DNS server "选项的标识字*/
#define DHCPHOSTNAME_CODE    0x0c /*DHCP报文"options"字段含有"Host name"选项的标识字*/
#define DHCPDOMAINNAME_CODE  0x0f /*DHCP报文"options"字段含有"Domain name"选项的标识字*/
#define DHCPNBNS_CODE        0x2c /*DHCP报文"options"字段含有"Netbios name server"选项的标识字*/
#define DHCPNBDS_CODE        0x2d /*DHCP报文"options"字段含有"Netbios data distribute server"选项的标识字*/
#define DHCPNBNT_CODE        0x2e /*DHCP报文"options"字段含有"Netbios node type"选项的标识字*/
#define DHCPNBSCOPE_CODE     0x2f /*DHCP报文"options"字段含有"Netbios scope"选项的标识字*/
#define DHCPVENDORINFO_CODE  0x29  /*DHCP报文"options"字段含有"Vendor specific information"选项的标识字*/
#define DHCPREQUESTEDIP_CODE 0x32 /* DHCP报文"options"字段含有"Requested Ip"选项的标识字 */
#define DHCPIPLEASETIME_CODE 0x33  /*DHCP报文"options"字段含有"Dhcp Ip address lease time"选项的标识字*/
#define DHCPMESSAGETYPE_CODE 0x35 /* DHCP报文"options"字段含有"Dhcp Message Type"选项的标识字 */
#define DHCPSERVERIP_CODE    0x36 /* DHCP报文"options"字段含有"Dhcp Server Ip"选项的标识字 */
#define DHCPREQPARAM_CODE    0x37 /* DHCP报文"options"字段含有"Requested parameter list"选项的标识字 */
#define DHCPRENEWTIME_CODE   0x3a /* DHCP报文"options"字段含有"Renew time"选项的标识字 */
#define DHCPREBINDTIME_CODE  0x3b /* DHCP报文"options"字段含有"Rebind time"选项的标识字 */
#define DHCPCLIENTID_CODE    0x3d /* DHCP报文"options"字段含有"Dhcp client Id"选项的标识字 */
#define DHCPCLASSID_CODE    0x3c /* DHCP报文"options"字段含有"Dhcp class Id"选项的标识字 */

/*DHCP报文中"options"字段对应的标志位*/
#define DHCPSUBNETMASK_CODE_FLAGBIT  1 
#define DHCPROUTERIP_CODE_FLAGBIT    (1<<1) 
#define DHCPDNSIP_CODE_FLAGBIT       (1<<2)
#define DHCPDOMAINNAME_CODE_FLAGBIT  (1<<3)

#define DHCPNBNS_CODE_FLAGBIT        (1<<4) 
#define DHCPNBDS_CODE_FLAGBIT        (1<<5) 
#define DHCPNBNT_CODE_FLAGBIT        (1<<6) 
#define DHCPNBSCOPE_CODE_FLAGBIT     (1<<7) 

#define DHCPIPLEASETIME_CODE_FLAGBIT (1<<8)  
#define DHCPRENEWTIME_CODE_FLAGBIT   (1<<9)  
#define DHCPREBINDTIME_CODE_FLAGBIT  (1<<10)  

#define DHCPRELEASEPKT_LEN   328

#define DHCP_IPTTL           16


#define MACHDRLEN             14        /* 用于封装报文的二层头的长度 */              
#define IPHDRLEN             20     /* 用于封装报文的IP头的长度 */  
#define UDPHDRLEN            8      /* 用于封装报文的UDP头的长度 */
#define MIN_DHCP_UDP_LEN     308    /* 承载DHCP报文的UDP报文的最小长度 */
#define MIN_DHCP_LEN         236    /* DHCP报文头的最小长度 */

/*IP包中的几个上层协议类型值*/
#define UDP_PROTOTYPE        17
#define TCP_PROTOTYPE        6
#define ICMP_PROTOTYPE       1

#define DHCPFIXEDFIELD_LEN   (ULONG)sizeof(DHCP_S) /* 236bytes */

#define HOP_LIMIT          4    /* DHCP报文的跳数限制 */

#define DHCP_PKT_BUFF_SIZE 2048 /* 接收dhcp报文的缓存大小 */

#define DHCP_DEBUG_ON      0
#define DHCP_DEBUG_OFF     1

#define DHCP_VLANTAG_TYPE   0x8100
#define IP_DGRAM_TYPE       0x0800           /* 表示MAC后封装的是IP报文 */
#define INBROADCASTIP       0xFFFFFFFF     /* IP广播地址 */

#define DHCP_QUEUELEN    500     /* 消息队列的长度 */
#define EV_DHCP_RCV     0x04
#define EV_DHCP_MSG     0x03

/*开关,用于打开定时清hash表操作,为0时,清hash操作被屏蔽,为1时启用. */
#define TIMEHASH    0           

#define DHCP_DELHASH_TIMESPAN 3600000 /* 定时定时器的时间间隔,以毫秒为单位,每1小时调用一次回调函数*/

/*SOCKET描述符的取值范围的最大最小值*/
#define MINSOCKVALUE          1
#define MAXSOCKVALUE          3072 

#define DHCP_VLANTAG_SIZE     4


#define DHCP_GET_VLANID(ulFwdInfo) (USHORT)((ulFwdInfo) & 0x0000FFFF)
#define DHCP_GET_PORTNO(ulFwdInfo) (UCHAR)(((ulFwdInfo) >> 16) & 0x0000001F)
#define DHCP_GET_PICNO(ulFwdInfo)  (UCHAR)(((ulFwdInfo) >> 21) & 0x00000003)
#define DHCP_GET_SLOTNO(ulFwdInfo) (UCHAR)(((ulFwdInfo) >> 24) & 0x000000FF)

/*用于MBUF_TR_RegisterReceiver中强制类型转换*/ 
typedef    VOID (*pfRCV_FUN)(PMBUF_S *,ULONG ); 

/*用于注册定时器回调函数的强制类型转换*/
typedef VOID  (*pfDhcpTimerFunc)(VOID *); 

/* DHCP消息类型: */
enum enDHCPR_MSG
{
   DHCPDISCOVER=1,
   DHCPOFFER,
   DHCPREQUEST,
   DHCPDECLINE,
   DHCPACK,
   DHCPNAK,
   DHCPRELEASE,
   DHCPINFORM
};


typedef struct tagEtherAddr
{
    UCHAR  ucAddrByte[6];
}EtherAddr_S;


typedef struct tagMACHDR
{
    EtherAddr_S stDstMacAddr;    /* 目的MAC地址 */
    EtherAddr_S stSrcMacAddr;    /* 源MAC地址 */
    USHORT      usHdrType;            /* 协议类型 */
}MACHDR_S;        

typedef struct tagMACHDRWITHTAG
{
    EtherAddr_S stDstMacAddr;    /* 目的MAC地址 */
    EtherAddr_S stSrcMacAddr;    /* 源MAC地址 */
    USHORT      usVlanType;     /* vlan type*/
    USHORT      usVlanId;
    USHORT      usHdrType;         /* 协议类型 */
}MACHDRWITHTAG_S;        

/* 以下的选项还要修改,删除某项或添加某些项 */
/**************************************************************************************
*说明:由于DHCP报文的option域是可以变化的，依据用户的报文携带的信息而变化，因此这个结构体无法真实反映
*dhcp option段的报文情况，之所以定义这个结构体，是为了在遍历option段的时候记录一些感兴趣的信息，无法
*象dhcp_s那样按顺序一一对应的反映出报文，而且这里之所以采用指针，而没有用变量，只是不想再单独为option
*分配内容，因为它总是依赖于dhcp报文头的，只需用一些指针来保存感兴趣的选项在dhcp报文中的地址位置即可。
*实际上完全可以采用变量来记录感兴趣选项，因为以前一直采用指针记录的方式，这里也不作更改了，但是需要记住
*的是DHCPOPTION_S不一一对应真正的dhcp报文中的option的所有内容，这与DHCP_S不同。
*值得说明的是:使用指针有很多灵活性，可以减少定义变量的数量，不必每一小项都定义一个变量。
****************************************************************************************/
typedef struct tagDHCPOPTION
{
    ULONG  ulSubnetMask;
    ULONG *pulRouterIp;               /*默认网关option:code = 3*/
    UCHAR ucRouterIpLen;
    ULONG *pulDNSIp;                  /*DNS服务器option:code = 6*/
    UCHAR ucDNSIpLen;
    ULONG  ulMagicCookie;
    UCHAR *pucHostName;               /*主机名option:code = 12*/    
    ULONG  ulHostNameLen;
    UCHAR *pucDomainName;             /*域名option:code = 15*/
    UCHAR ucDomainNameLen;
  /*NetBios选项*/
    ULONG *pulNBNSIp;                 /*Netbios名称服务器option:code = 44*/
    UCHAR ucNBNSIpLen;
    ULONG *pulNBDSIp;                 /*Netbios数据分发服务器option:code = 45*/
    UCHAR ucNBDSIpLen; 
    UCHAR *pucNBNodeType;             /*Netbios节点类型option:code = 46*/
    UCHAR *pucNBScope;                /*Netbios范围option:code = 47*/
    UCHAR ucNBScopeLen;
  /*DHCP option*/
    ULONG *pulReqIp;                  /*客户想要的IP地址option:code = 50*/
    ULONG *pulLeaseTime;              /*IP地址租期option:code = 51*/
    UCHAR *pucDHCPMsgType;            /*DHCP消息类型option:code = 53*/
    ULONG *pulDHCPServerIp;           /*DHCP服务器IP地址option:code = 54*/
    UCHAR *pucReqParamList;           /*客户请求的参数列表option:code = 55*/
    UCHAR ucReqParamListLen;
    ULONG *pulRenewTime;              /*续延时间option:code = 58*/
    ULONG *pulRebindTime;             /*重新绑定时间option:code = 59*/
    UCHAR *pucClientId;               /*客户标识option:code = 61*/
    ULONG  ulClientIdLen;
  /*为支持CM,IDT而设定的专门的厂商选项*/
    UCHAR *pucVendorOption;           /*厂商特定信息option:code = 43*/
    UCHAR ucVendorOptinLen;
  /*记录'option'结束符的位置*/
    UCHAR *pucEndOfOption;
}DHCPOPTION_S;

typedef struct tagDHCPR_INFOHDR
{
    UCHAR    ucSlotNo;
    UCHAR    ucReserved1:1;    /* 其中2Bit预留 */
    UCHAR    ucPICNo:2;        /* 2Bit为适配卡号 */
    UCHAR    ucPortNo:5;    /* 4Bit为端口号 */
    USHORT   usVlanId;
}DHCPR_INFOHDR_S;

typedef struct tagMAC_HASHDATA
{
    EtherAddr_S stUserMacAddr; /* 用户主机的MAC地址 */
    DHCPR_INFOHDR_S stDhcpFwdInfo;  
    /* 存储时是按4个字节来的,这里补2个字节,使占用空间为4的倍数. */
    UCHAR ucClrFlag;
    UCHAR RESERVED; 
}MACHASH_S;

typedef struct tagDHCP_SERVER_GROUP
{
     ULONG   ulServerAddr1;
     ULONG   ulServerAddr2;
}DHCP_SERVER_GROUP_S;

typedef struct tagDHCP_UDP_FATEHEAD
{
     ULONG   ulSrcIp;
     ULONG   ulDestIp;
     UCHAR   ucPad;
     UCHAR   ucProtocal;
     SHORT   sUdpLen;
}DHCP_UDP_FATEHEAD_S;

typedef struct  tagDhcpDiagPort
{
    ULONG ulFwdInfo;
    ULONG ulPacketNum;
}DHCPDIAGPORT_S;

typedef struct  tagDhcpDiag
{
    ULONG ulDhcpRcvTotal;                       /* DHCP收到的报文的总数 */
    
    /*各个vlan收到的DHCP报文数*/
    ULONG ulDhcpRcvFromVlan[DHCP_MAX_VLANID + 1];        /* 数组的参数为VlanId */

    DHCPDIAGPORT_S stPacketFromPort[DHCP_MAX_PORT_NUM];
    
    ULONG ulDhcpRcvFromNps;            /* DHCP收到的从NPS过来的报文数 */    

    ULONG ulDhcpServerPktTotal;     /* DHCP收到的server发来的报文数 */    
    
    
    ULONG ulDhcpSendToServer;          /* DHCP发送到SERVER的报文数 */
    
    ULONG ulDhcpClientPktTotal;        /* DHCP收到的CLIENT发过来的报文总数 */
    ULONG ulDhcpClientPktUnicast;      /* DHCP收到的CLIENT发来的单播报文数 */
    ULONG ulDhcpClientPktBroadcast;    /* DHCP收到的CLIENT发来的广播报文数 */

    ULONG ulDhcpClientPktDeclineTotal; /* DHCP收到的DECLINE报文数 */
    ULONG ulDhcpClientPktInformTotal;  /* DHCP收到的INFORM报文数 */
    ULONG ulDhcpClientPktDiscoverTotal;/* DHCP收到的DISCOVER报文数 */
    ULONG ulDhcpClientPktRequestTotal; /* DHCP收到的REQUEST报文数 */
    ULONG ulDhcpServerPktOfferTotal;   /* DHCP收到的OFFER报文数 */
    ULONG ulDhcpServerPktAckTotal;     /* DHCP收到的ACK报文数 */
    ULONG ulDhcpServerPktNakTotal;     /* DHCP收到的NAK报文数 */

    /* 一些错误统计信息 */
    ULONG ulNotDhcpRequestPkt;         /* 处理请求报文函数收到的非请求报文数 */
    ULONG ulNotDhcpReplyPkt;           /* 响应处理函数收到的非响应报文数 */
    ULONG ulMemMallocErrNum;           /* 主要记录dhcpr.c中内存分配失败的次数 */
}DHCPDIAG_S;

/*untagged属性定义：*/
#define    VMS_TAGGED                0
#define    VMS_UNTAGGED            1

#define MBUF_FLAG_VLAN_SINGLECAST  0x00200000
#define MBUF_TR_DHCPR               0x0000000b

/*租期是否起作用的枚举变量*/
typedef enum tagIPPOOL_LEASE_FLAG
{
    LEASE_ABLE =0,
    LEASE_DISABLE
}IPPOOL_LEASE_FLAG;

/**********************VLAN相关ENUM定义**********************/
/* VLAN类型 */
enum enVlanType
{
    VLAN_TYPE_INVALID = 0,
    VLAN_TYPE_DEFAULT,            /* 缺省VLAN类型        */
    VLAN_TYPE_COMMON,            /* 普通VLAN类型        */
    VLAN_TYPE_SUPER,            /* super VLAN类型   */
    VLAN_TYPE_SUB,                /* sub VLAN类型        */
    VLAN_TYPE_PORT                /* 局部 VLAN类型    */
};

#define L2IF_MAX_VLAN_NUM       4096    /*系统最大允许vlan号*/

#define DHCP_SRV_EV_QUIT         0x00000001
#define DHCP_SRV_EV_CLNT         0x00000002



#endif
