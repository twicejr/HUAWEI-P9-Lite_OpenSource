/*************************************************************************
 *
 *              Copyright 2006, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              fw_acl_def.h
 *
 *  Project Code: VISP1.6
 *   Module Name: ACL4
 *  Date Created: 2006-12-01
 *        Author: lijing 52889
 *   Description: 宏定义
 *   Version:      1
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2006-12-01      lijing 52889    Create
 *  2008-10-24      liangjicheng   C02NEWR-ACL  support SCTP
 *  2012-02-16      r00902615      Added new Macro ACL_DELETE_ALL_RULE
 *
 ************************************************************************/
#ifndef _FW_ACL_DEF_H_
#define _FW_ACL_DEF_H_

#ifdef  __cplusplus
extern "C" 
{
#endif


/**********************************************************
*   IP首部相关宏定义
***********************************************************/
/* IP首部TOS字段的宏定义 */
#define ACL_TOS_NORMAL              0x0
#define ACL_TOS_MIN_MONETARY_COST   0x1
#define ACL_TOS_MAX_RELIABILITY     0x2
#define ACL_TOS_MAX_THROUGHPUT      0x4
#define ACL_TOS_MIN_DELAY           0x8
#define ACL_TOS_ALL                 0xff
#define ACL_TOS_MASK                0x1e
#define ACL_GET_TOS(p)              (((p) & ACL_TOS_MASK)>>1)

/* IP首部优先级字段的宏定义 */
#define ACL_PRE_ROUTINE             0x0
#define ACL_PRE_PRIORITY            0x1
#define ACL_PRE_IMMEDIATE           0x2
#define ACL_PRE_FLASH               0x3
#define ACL_PRE_FLASH_OVERRIDE      0x4
#define ACL_PRE_CRITICAL            0x5
#define ACL_PRE_INTERNET            0x6
#define ACL_PRE_NETWORK             0x7
#define ACL_PRE_ALL                 0xff
#define ACL_PRE_MASK                0xe0
#define ACL_GET_PRE(p)              (((p) & ACL_PRE_MASK)>>5)

/* IP首部DSCP字段的宏定义 */
#define ACL_DSCP_ALL                0xff
#define ACL_DSCP_MASK               0xfc
#define ACL_GET_DSCP(p)             (((p) & ACL_DSCP_MASK)>>2)


/* 取报文各字段的宏定义 */
#define IPPROTOCAL(pIp)     pIp->ip_chPr
#define IPSRCADDR(pIp)      pIp->ip_stSrc.s_ulAddr
#define IPDSTADDR(pIp)      pIp->ip_stDst.s_ulAddr
#define IPTOS(pIp)          ((pIp->ip_chTOS>>1)&0x0f)
#define IPPRECEDENCE(pIp)   ((pIp->ip_chTOS>>5)&0x07)
#define TCPSPORT(pTcp)      pTcp->usSrcPort
#define TCPDPORT(pTcp)      pTcp->usDstPort
#define UDPSPORT(pUdp)      pUdp->uh_usSPort
#define UDPDPORT(pUdp)      pUdp->uh_usDPort
#define ICMPTYPE(pIcmp)     pIcmp->icmp_chType
#define ICMPCODE(pIcmp)     pIcmp->icmp_chCode
#define IPDSCP(pIp)         ((pIp->ip_chTOS>>2)&0x3f)

/**********************************************************
*   忽略位相关宏定义，在报文匹配时可对指定字段不予比较
***********************************************************/
/* 忽略字段各位的定义 */
#define ACL_SIPByte     0x0001     
#define ACL_DIPByte     0x0002
#define ACL_PROByte     0x0004
#define ACL_TOSByte     0x0008
#define ACL_PREByte     0x0010
#define ACL_SPORTByte   0x0020
#define ACL_DPORTByte   0x0040
#define ACL_DSCPByte    0x0400

/* Begin:VISP1.7C03 VRF wangchengyang,2009-01-21 */
#define ACL_VRFByte     0x0080

/* End:VISP1.7C03 VRF wangchengyang,2009-01-21 */

/* 获取忽略位标志 */
#define ACL_ING_SIP(ulByte)         (ACL_SIPByte & (ulByte))
#define ACL_ING_DIP(ulByte)         (ACL_DIPByte & (ulByte))
#define ACL_ING_PRO(ulByte)         (ACL_PROByte & (ulByte))
#define ACL_ING_TOS(ulByte)         (ACL_TOSByte & (ulByte))
#define ACL_ING_PRE(ulByte)         (ACL_PREByte & (ulByte))
#define ACL_ING_SPORT(ulByte)       (ACL_SPORTByte & (ulByte))
#define ACL_ING_DPORT(ulByte)       (ACL_DPORTByte & (ulByte))
#define ACL_ING_DSCP(ulByte)        (ACL_DSCPByte & (ulByte))

/* Begin:VISP1.7C03 VRF wangchengyang,2009-01-21 */
#define ACL_ING_VRF(ulByte)        (ACL_VRFByte & (ulByte))

/* End:VISP1.7C03 VRF wangchengyang,2009-01-21 */

/* 设置忽略位信息 */
#define ACL_SETING_SIP(ulByte)      ((ulByte) |= ACL_SIPByte)
#define ACL_SETING_DIP(ulByte)      ((ulByte) |= ACL_DIPByte)
#define ACL_SETING_PRO(ulByte)      ((ulByte) |= ACL_PROByte)
#define ACL_SETING_TOS(ulByte)      ((ulByte) |= ACL_TOSByte)
#define ACL_SETING_PRE(ulByte)      ((ulByte) |= ACL_PREByte)
#define ACL_SETING_SPORT(ulByte)    ((ulByte) |= ACL_SPORTByte)
#define ACL_SETING_DPORT(ulByte)    ((ulByte) |= ACL_DPORTByte)
#define ACL_SETING_DSCP(ulByte)     ((ulByte) |= ACL_DSCPByte)

/**********************************************************
*   规格类型相关宏定义
***********************************************************/
/* 缺省规则类型ID */
#define ACL_BASIC_RULE_TYPE     1
#define ACL_ADVANCE_RULE_TYPE   2
#define ACL_IFBASED_RULE_TYPE   3
#define ACL_EXTMAC_RULE_TYPE    4


/**********************************************************
*   规格组相关宏定义
***********************************************************/
/* 最大规则组序号总和 */

/*Modified from 9999 to 28999 - Rishab Joshi. */
#define ACL_MAX_GROUPNUM_SUM  32999

/* 缺省规则类型的规则组序号缺省值 */
#define ACL_BAS_DEFAULT_MIN     2000
#define ACL_BAS_DEFAULT_MAX     2999

#define ACL_ADV_DEFAULT_MIN     3000
#define ACL_ADV_DEFAULT_MAX     3999

/* Added by Rishab Joshi for IPSEC requirement. */
#define ACL_ADV_DEFAULT_MAX_IPSEC       26999

#define ACL_IF_DEFAULT_MIN      1000
#define ACL_IF_DEFAULT_MAX      1999

#define ACL_EXTMAC_DEFAULT_MIN  4000
#define ACL_EXTMAC_DEFAULT_MAX  4999 /* Changed from 4099 to 4999 for C06 */

#define ACL_EXTADV_DEFAULT_MIN  5000

/* 全局最大规则数 */
/*B015 liangjicheng 2008-12-12 SGSN NEWR 3000->10000*/

/* Modified from 10000 to 20000 - Rishab Joshi. */
#define ACL_MAX_ALLRULE_SUM   24000

/* 一个规则组下最大规则数 */
#define ACL_MAX_GROUPRULE_SUM   1024

/* 规则组步长范围 */
#define ACL_MIN_STEP    1
#define ACL_MAX_STEP    20

/* 规则组默认步长 */
#define ACL_DEFAULT_STEP    5


/* 协议号取值范围 */
#define ACL_MIN_PROID    0
#define ACL_MAX_PROID    255

/*Begin C02NEWR-ACL liangjicheng 2008-10-24   */
/* ICMP Code号取值范围 */
#define ACL_MIN_ICMPCODE  0
/* #define ACL_MAX_ICMPCODE  15 */
#define ACL_MAX_ICMPCODE  255

/* ICMP Type号取值范围 */
#define ACL_MIN_ICMPTYPE  0
/* fine ACL_MAX_ICMPTYPE  19 */
#define ACL_MAX_ICMPTYPE  255
/*End    C02NEWR-ACL */


/* 无效规则组序号 */
#define ACL_INVALID_GROUPNUM    0

/* 无效规则索引 */
#define ACL_INVALID_SUBNO       0xffffffff
#define ACL_DELETE_ALL_RULE     0xffffffff

/* 以太MTU */
#define ACL_ETHERNETMTU     0x0600

/*以太网帧格式*/
#define ACL_PKTFMT_ETHNT_2   0
#define ACL_PKTFMT_EN_SNAP   1
#define ACL_PKTFMT_8023_IPX  2
#define ACL_PKTFMT_8022_IPX  3

/* VLAN 类型值 */
#define  ACL_VLANTYPE_DOT1Q   0x8100 

/* VLAN头的长度 */
#define  ACL_VLANHDR_SIZE   4 



/**********************************************************
*   其他宏定义
***********************************************************/

/* 规则组是否存在 */
#define ACL_GROUP_IS_EXIST(pstGroup) ((pstGroup) != NULL)

/* waitlist ID */
#define ACL_WaitListID 9006

/* physical地址长度 */
#define ACL_MACADDR_LEN 6

/* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */
#define ACL_DEFAULT_VRFINDEX 0
#define ACL_ANY_VRFINDEX     0xFFFFFFFFL

/* End:VISP1.7C03 VRF wangchengyang,2009-01-20 */

/* ACL Flags */
#define ACL_YES 1
#define ACL_NO  0

/* ACL Flags */
#define ACL_ENABLED 1
#define ACL_DISABLED 0


/* ACL的范围 */
#define ACL_NUM_MIN             1

#define ACL_BAS_MIN             1
#define ACL_BAS_MAX             99

#define ACL_ADV_MIN             100
#define ACL_ADV_MAX             199

#define ACL_NUM_MIDDLE          199

/* VRPV3R001M06B03D003_BRIDGE_TZB 支持过滤以太帧头的ACL */
#define ACL_EXTMAC_MIN          700
#define ACL_EXTMAC_MAX          799

#define ACL_NUM_MIDDLE2         1000

#define ACL_IF_MIN              1000
#define ACL_IF_MAX              1999

#define ACL_BAS_MIN_EXT         2000
#define ACL_BAS_MAX_EXT         2999

#define ACL_ADV_MIN_EXT         3000
#define ACL_ADV_MAX_EXT         3999

#define ACL_NUM_MIDDLE3         3999 /* add for SACL */

#define ACL_EXTMAC_MIN_EXT      4000
#define ACL_EXTMAC_MAX_EXT      4999 /* Changed from 4099 to 4999 for C06 */

#define ACL_NUM_MIDDLE4         4999 /* Changed from 4099 to 4999 for C06 */

/* simple acl 规则最大数 */
#define SACL_MAX_RULE_NUM       (1024*32)

/* simple acl 规则编号的范围 */
#define ACL_SIMPLE_MIN          10000
#define ACL_SIMPLE_MAX          (10000 + (SACL_MAX_RULE_NUM) - 1)


#ifndef VRP_MODULE_SEC_ETH_ACL
#define VRP_MODULE_SEC_ETH_ACL VRP_YES
#endif

#ifndef VRP_MODULE_SACL
#define VRP_MODULE_SACL VRP_NO
#endif


/* 下面的宏要从大到小定义 */
#if(VRP_MODULE_SACL == VRP_YES)
    #define ACL_NUM_MAX                     ACL_SIMPLE_MAX
    #define ACL_MAX_NUMBERACL_COUNT         (ACL_SIMPLE_MAX + 1)
#elif(VRP_MODULE_SEC_ETH_ACL == VRP_YES)
    #define ACL_NUM_MAX                     ACL_NUM_MIDDLE4
    #define ACL_MAX_NUMBERACL_COUNT         (ACL_NUM_MIDDLE4 + 1)
#else
    #define ACL_NUM_MAX                     ACL_NUM_MIDDLE3
    #define ACL_MAX_NUMBERACL_COUNT         (ACL_NUM_MIDDLE3 + 1)
#endif

/* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */
#ifndef ACL_MAX_VRFNAME_LENGTH
#define ACL_MAX_VRFNAME_LENGTH      31               
#endif

/* End:VISP1.7C03 VRF wangchengyang,2009-01-20 */

/*ACL_ShowGroup输出规则个数 liuyu B016*/
#define ACL_ALL_RULE 1
#define ACL_SINGLE_RULE 0

/* ACL关注的ICMP首部长度 */
#define ACL_ICMP_HEADLEN 4

#define ACL_IS_RANGE(x, min, max)   (((x) <= (max)) && ((x) >= (min)))

#define ACL_LOCK_ACL    0 
#define ACL_LOCK_RFC    1
#define ACL_LOCK_SFE    2
#define ACL_LOCK_TIMER  3
#define ACL_NUM_LOCKS   4

#define ACL_OK 0

/* 规则组匹配顺序 */
#define ACL_MATCHORDER_DEFAULT  0
#define ACL_MATCHORDER_CONFIG   1
#define ACL_MATCHORDER_AUTO     2


/*Begin C02NEWR-ACL liangjicheng 2008-10-24   PROT_SCTP*/
/*#define PROT_SCTP        132*/

/*End C02NEWR-ACL liangjicheng 2008-10-24   PROT_SCTP*/

/*Bhaskar 28-10-2009: Comment End*/

/* 端口号取值范围 */
#define ACL_MIN_PORTNUM 0
#define ACL_MAX_PORTNUM 65535

/* 任意地址 */
#define IPADDRANY ((127 << 24) + (255 << 16) + (255 << 8) + 254)

/* 任意接口索引 */
#define IFINDEXANY 0xffffffff

#define  ACL_DSTSRCMAC_SIZE   12

/*注册命令行*/
/*TRNG_RegCmd();*/

#define FW_ACL_COMMON_TIMER_MILLSEC  (1 * 60) * 1000

#ifndef ETHARP_INPUT
#define ETHARP_INPUT 0
#endif

#ifndef ETHARP_OUTPUT
#define ETHARP_OUTPUT 1
#endif

#ifndef NO_USE
#define     NO_USE(var)     (VOID)(var)
#endif

#ifdef  __cplusplus
}
#endif
   
#endif

