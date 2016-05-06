/*************************************************************************
 *
 *              Copyright 2009, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              acl6_pub.h
 *
 *  Project Code: VISP1.8
 *   Module Name: ACL6
 *  Date Created: 
 *        Author: 
 *   Description: 数据结构的定义
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 ************************************************************************/
#ifndef _ACL6_PUB_H_
#define _ACL6_PUB_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include "acl6/include/acl6_cbb_api.h"



/* ACL6规则 */
typedef struct tagACL6_RuleNode
{
    VOID  *pContent;                        /* 规则内容，根据ACL6规则的类型决定 */
    ULONG  ulRuleIndex;                     /* 规则索引 */
    ULONG  ulCount;                         /* 匹配该规则的次数 */
    struct tagACL6_RuleNode * pstNode;      /* 下一条规则 */
}ACL6_RULE_NODE_S;

/* ACL6规则组 */
typedef struct tagACL6_Group
{
    ULONG ulVer;                    /* 暂不使用，留待扩展 */
    ULONG ulMatchOrder;             /* 匹配顺序:0-配置顺序,1-自动顺序 */
    ULONG ulRuleNum;                /* 该规则组下已有的规则总数 */
    ULONG ulGroupIndex;             /* 规则组序号 */
    ULONG ulTypeID;                 /* 所属规则类型ID */

    ACL6_RULE_NODE_S *pRuleNode;    /* 下属规则链表表头 */
    CHAR *pACL6Description;         /* 该规则组的描述信息 */
    ULONG ulIndexStep;              /* 该规则组的步长 */
    ULONG ulNextRuleIndex;          /* 待分配的规则索引 */
    ULONG ulRuleNodeSize;           /* 规则内容的大小,指pRuleNode->pCoutent的内容大小 */
} ACL6_GROUP_S;

/* ACL6规则类型 */
typedef struct tagAcl6_Type
{
    ULONG ulTypeID;         /* 规则类型ID（1－16） */
    ULONG ulLowNo;          /* 规则组序号下限 */
    ULONG ulUpNo;           /* 规则组序号上限 */
    ULONG ulRuleNodeSize;   /* 规则内容的大小 */
    /* 比较两个节点是否相同 */
    ULONG (*pFuncComp)(VOID *, VOID *); 
    /* 判断规则是否合适插入某规则之前，前一个参数是待插入规则，后一个参数是被插入规则 */
    ULONG (*pFuncBefore)(VOID *, VOID *); 
    /* 比较一个规则节点是否和包匹配，前一个参数是规则内容，后一个参数是待匹配报文信息 */
    ULONG (*pFuncRuleComp)(VOID *, VOID *); 
    /* 创建一个规则节点 */
    VOID* (*pFuncCreateNode)();
    /* 释放一个规则节点 */
    VOID (*pFuncReleaseNode)(VOID*);    
    ACL6_GROUP_S **ppstGroup;/* 规则组指针数组 */
} ACL6_TYPE_S;

/* ACL6高级规则端口号及协议信息检查结构 */
typedef struct tagACL6_CheckProPort
{
    UCHAR ucProtoBegin;
    UCHAR ucProtoEnd;
    UCHAR ucPadding[2];
    ULONG ulPortOpType;
    ACL6_PORT_RANGE_S stPort;
} ACL6_CHECK_PRO_PORT_S;

/* ACL6规则数据结构入口 */
typedef struct tagACL6_AccessList
{
    ULONG ulACL6GroupSum;
    ACL6_TYPE_S* pstACL6Type[ACL6_MAX_TYPEID + 1];   
} ACL6_ACCESSLIST_S;


/* 从IPv6报文中提取的信息 */
typedef struct tagIP6PacketInfo 
{
    UCHAR szSrcAddr[ACL6_IPV6_ADDR_LEN];            /* 源IPv6地址 */            
    UCHAR szDstAddr[ACL6_IPV6_ADDR_LEN];            /* 目的IPv6地址 */ 
    USHORT usSrcPort;            /* 源端口号 or ICMPv6 Type*/            
    USHORT usDstPort;            /* 目的端口号 or ICMPv6 Code*/            
    UCHAR ucFO;                  /* True - 非首片的分片报文 
                                                                 False - 首片的分片报文或不分片报文*/
    UCHAR ucProto;               /* 协议号范围最大值 */
    UCHAR ucClass;               /* Traffic Class */
    UCHAR ucHopLm;               /* Hop Limit值 */
    ULONG ulIfIndex;             /* 接口索引 */ 
    ULONG ulVrfIndex;            /* Vrf index */
    ULONG ulIgnoreByte;          /* 忽略比较字段 */
} IP6PACKETINFO_S;

/* 产品需要使用ACL6_IP6_S,因此在api.h中也定义了一份,注意结构体必须与acl6_cbb_api.h中的ACL6_IP6_S定义保持一致 */
/*IPv6基本报头*/
#ifndef _ACL6_IP6_S
#define _ACL6_IP6_S

typedef struct tagACL6_Ip6
{
    ULONG ulTclassFlow;      /* 4 bits version, 8 bits traffic class and 20 bits of flow-ID */
    USHORT usPayLen;         /* 16 bits payload length */
    UCHAR ucNextHd;          /* 8 bits next header */
    UCHAR ucHopLm;           /* 8 bits hop limit */
    UCHAR szSrcAddr[ACL6_IPV6_ADDR_LEN];            /* 源IPv6地址 */            
    UCHAR szDstAddr[ACL6_IPV6_ADDR_LEN];            /* 目的IPv6地址 */ 
} ACL6_IP6_S;
#endif

/*IPv6扩展报头*/
typedef struct tagACL6_Ip6NextHd
{
    UCHAR ucNextHd;      /* 8 bits next header */
    UCHAR ucHdLen;       /* 8 bits header length*/
} ACL6_IP6_NEXT_HD_S;

/* Fragment Header */
typedef struct tagACL6_Ip6Frag
{
    UCHAR  ucNextHd;     /* next header */
    UCHAR  ucReserved;   /* reserved field */
    USHORT usOfflg;      /* 13 bits offset, 2 bits reserved, 1 bit M flag */
    ULONG  ulIdent;      /* identification */
}ACL6_IP6_FRAG_S;

/* UDP6 Header*/
typedef struct tagACL6_Udp6Hd
{
    USHORT    usSrcPort;        /* source port */
    USHORT    usDstPort;        /* destination port */
    SHORT     sULen;          /* udp length */
    USHORT    usSum;          /* udp checksum */
}ACL6_UDP6_S;

/*TCP6 Header*/
typedef struct tagACL6_Tcp6Hd
{
    USHORT usSrcPort;
    USHORT usDstPort;
    ULONG ulSeqNumber;
    ULONG ulAckNumber;
#if (VRP_LITTLE_ENDIAN == VRP_YES)
    UCHAR ucX2:4,
    ucOffset:4;
#else
    UCHAR ucOffset:4, /* warning:nonstandard extn used :bit field types other than LONG. */
    ucX2:4;             /* warning:nonstandard extn used : bit field types other than LONG. */
#endif
    UCHAR ucFlags;
    USHORT usWnd;
    USHORT usCheckSum;
    USHORT usUrgentPoint;
} ACL6_TCP6_S;

/*ICMP6 Header*/
typedef struct tagACL6_Icmp6Hd
{
    UCHAR  ucType;           /* type of message, see below */
    UCHAR  ucCode;           /* type sub code */
    USHORT usChksum;         /* ones complement cksum of struct */
    UCHAR  ucData[4];        /* type-specific field */
} ACL6_ICMP6_S;

/* ACL6规则端口号匹配使用结构体 */
typedef struct tagACL6_CheckPort
{
    USHORT usPktPort;
    UCHAR ucPadding[2];
    ULONG ulPortOpType;
    ACL6_PORT_RANGE_S stPort;
} ACL6_CHECK_PORT_S;


typedef struct tagACL6_Item
{
    ACL6_IP6ADDR_S stSrcIp;/* 源地址 */
    ACL6_IP6ADDR_S stDstIp;/* 目的地址 */
    UCHAR           ucPID;  /* 协议号 */
    UCHAR           ucPadding[3];
    USHORT          usSP;   /* 源端口号，网络序 */
    USHORT          usEndSP;   /* 源端口号，网络序 */
    USHORT          usDP;   /* 目的端口号，网络序 */
    USHORT          usEndDP;   /* 目的端口号，网络序 */
    ULONG           ulVrfIndex; /* 指定VRF，如果匹配所有则VrfIndex配置为0xFFFFFFFFL,如果没有使用VRF则填写0 */
} ACL6_Item, * PACL6_Item;

#ifndef _ACL6CONFIG_S
#define _ACL6CONFIG_S
typedef struct tagAcl6Config
{
    ULONG ulAclNumMin;          /* 最小规则组序号 */
    ULONG ulAclNumMax;          /* 最大规则组序号 */
    ULONG ulAclBasMinExt;       /* 最小基本规则组序号 */
    ULONG ulAclBasMaxExt;       /* 最大基本规则组序号 */
    ULONG ulAclAdvMinExt;       /* 最小扩展规则组序号 */
    ULONG ulAclAdvMaxExt;       /* 最大扩展规则组序号 */
    ULONG ulIpAddrAny[LEN_4];          /* 地址通配符 */
    ULONG ulAclDeny;            /* acl deny取值 */
    ULONG ulAclPermit;          /* acl permit取值 */
    ULONG ulAclNotfound;        /* acl notfound取值 */
} ACL6CONFIG_S, *PACL6CONFIG_S;
#endif

/*acl6 变化通知*/
#define ACL6_UPDATE_GROUP_DELETE         1
#define ACL6_UPDATE_RULE_DELETE          2
#define ACL6_UPDATE_RULE_MODIFY          3
#define ACL6_UPDATE_RULE_ADD             4
#define ACL6_UPDATE_GROUP_DELETE_ALL     5


#ifndef _PF_ACL6_REFRESHCALLBACK
#define _PF_ACL6_REFRESHCALLBACK
/*为0 表示处理所有的*/
typedef VOID (*PF_ACL6_REFRESHCALLBACK)(ULONG ulGroupId, ULONG ulRuleId, ULONG ulEventType);
#endif

typedef struct tagACL6_UPDATE_CALLBACK_NODE
{
    PF_ACL6_REFRESHCALLBACK pfCallBack;
    ULONG ulModuleId;
    struct tagACL6_UPDATE_CALLBACK_NODE *pstNext;
}ACL6_UPDATE_CALLBACK_NODE_S;

#ifdef  __cplusplus
}
#endif

#endif
