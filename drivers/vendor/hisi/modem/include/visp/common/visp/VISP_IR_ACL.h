/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              VISP_IR_ACL.h
*
*  Project Code: VISPV1R6C02
*   Module Name:   
*  Date Created: 2007-07-31
*        Author: luogaowei61496
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-07-31   luogaowei61496          Create
*
*******************************************************************************/

#ifndef _VISP_IR_ACL_H_
#define _VISP_IR_ACL_H_

#ifdef  __cplusplus
extern "C"{
#endif

/* 存放规则中的地址和掩码 */
typedef struct tagIR_ACL_Range32 
{
    ULONG ulAddr;    
    ULONG ulMask;    
} IR_ACL_RANGE32_S;

#ifndef _ACL_ITEM
#define _ACL_ITEM
/* ACL的子项,提供给IPSEC模块调用 */
typedef struct tagACL_Item
{
    IR_ACL_RANGE32_S   stSIP;  /* 源地址 */
    IR_ACL_RANGE32_S   stDIP;  /* 目的地址 */
    UCHAR           ucPID;  /* 协议号 */
    UCHAR           ucPadding[3];
    USHORT          usSP;   /* 源端口号 */
    USHORT          usDP;   /* 目的端口号 */
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */
    ULONG           ulVrfIndex; /* 指定VRF，如果匹配所有则VrfIndex配置为0xFFFFFFFFL,如果没有使用VRF则填写0 */
    /* End: VISP1.7C03 VRF wangchengyang,2009-01-20 */

    USHORT          usSPEnd; /*Source port End. Port Range will be considered only when this field is non-zero. */        
    USHORT          usDPEnd; /* Dest port End.Port Range will be considered only when this field is non-zero. */        
} ACL_Item, * PACL_Item;
#endif

#ifndef _ACLCONFIG_S
#define _ACLCONFIG_S
/* ACL config information */
typedef struct tagAclConfig
{
    ULONG ulAclNumMin;          /* 最小规则组序号 */
    ULONG ulAclNumMax;          /* 最大规则组序号 */
    ULONG ulAclBasMinExt;       /* 最小基本规则组序号 */
    ULONG ulAclBasMaxExt;       /* 最大基本规则组序号 */
    ULONG ulAclAdvMinExt;       /* 最小扩展规则组序号 */
    ULONG ulAclAdvMaxExt;       /* 最大扩展规则组序号 */
    ULONG ulIpAddrAny;          /* 地址通配符 */
    ULONG ulAclDeny;            /* acl deny取值 */
    ULONG ulAclPermit;          /* acl permit取值 */
    ULONG ulAclNotfound;        /* acl notfound取值 */
} ACLCONFIG_S, *PACLCONFIG_S;
#endif

#pragma    pack( 1 )
typedef struct  tagAclETHERHDR
{
    UCHAR                   ucHdrDstMacAddr[6];     /*目的physical地址*/ 
    UCHAR                   ucHdrSrcMacAddr[6];     /*源physical地址  */
    USHORT                  usHdrType;              /*协议类型   */
}ACL_ETHARP_ETHERHDR_S;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

/* 无效规则索引 */
#define ACL_INVALID_SUBNO       0xffffffff

/*
    when delete all rule of given group, ulRuleId is 0;
    when delete one group, ulRuleId is 0;
    when delete all group, ulGroupId and ulRuleId is 0.
 */
#ifndef _PF_ACLREFRESHCALLBACK
#define _PF_ACLREFRESHCALLBACK
typedef VOID (*PF_ACLREFRESHCALLBACK)(ULONG ulGroupId, ULONG ulRuleId, ULONG ulEventType);
#endif

#define ACL_UPDATE_GROUP_DELETE         1
#define ACL_UPDATE_RULE_DELETE          2
#define ACL_UPDATE_RULE_MODIFY          3
#define ACL_UPDATE_RULE_ADD             4
#define ACL_UPDATE_GROUP_DELETE_ALL     5
/* End of addition by z43740 2008/03/12 */

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif    /* end of _VISP_IR_ACL_H_ */
