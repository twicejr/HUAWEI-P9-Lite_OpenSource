/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              VISP_IR_AC6L.h
*
*  Project Code: VISPV1R8C03
*   Module Name:   
*  Date Created: 2010-01-27
*        Author: luogaowei61496
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2010-01-27   luogaowei61496          Create
*
*******************************************************************************/

#ifndef _VISP_IR_ACL6_H_
#define _VISP_IR_ACL6_H_

#ifdef  __cplusplus
extern "C"{
#endif


#ifndef ACL6_IPV6_ADDR_LEN
#define ACL6_IPV6_ADDR_LEN   16
#endif

#ifndef _IR_ACL6_IP6ADDR_S
#define _IR_ACL6_IP6ADDR_S
typedef struct tagIR_Acl6Ip6Addr 
{
    UCHAR ucAddr[ACL6_IPV6_ADDR_LEN];    /*IPv6地址信息，网络序*/
    ULONG ulMaskLen;     /*IPv6地址掩码长度*/
} IR_ACL6_IP6ADDR_S;
#endif

#ifndef _ACL6_ITEM
#define _ACL6_ITEM
typedef struct tagACL6_Item
{
    IR_ACL6_IP6ADDR_S stSrcIp;/* 源地址 */
    IR_ACL6_IP6ADDR_S stDstIp;/* 目的地址 */
    UCHAR           ucPID;  /* 协议号 */
    UCHAR           ucPadding[3];
    USHORT          usSP;   /* 源端口号，网络序 */
    USHORT          usEndSP;/* 源端口号结束值，网络序 */
    USHORT          usDP;   /* 目的端口号，网络序 */
    USHORT          usEndDP;/* 目的端口号结束值，网络序 */
    ULONG           ulVrfIndex; /* 指定VRF，如果匹配所有则VrfIndex配置为0xFFFFFFFFL,如果没有使用VRF则填写0 */
} ACL6_Item, * PACL6_Item;

#endif

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


#ifndef _PF_ACL6_REFRESHCALLBACK
#define _PF_ACL6_REFRESHCALLBACK
/*zero means process all node*/
typedef VOID (*PF_ACL6_REFRESHCALLBACK)(ULONG ulGroupId, ULONG ulRuleId, ULONG ulEventType);
#endif

#define ACL6_UPDATE_GROUP_DELETE         1
#define ACL6_UPDATE_RULE_DELETE          2
#define ACL6_UPDATE_RULE_MODIFY          3
#define ACL6_UPDATE_RULE_ADD             4
#define ACL6_UPDATE_GROUP_DELETE_ALL     5

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif    /* end of _VISP_IR_ACL_H_ */

