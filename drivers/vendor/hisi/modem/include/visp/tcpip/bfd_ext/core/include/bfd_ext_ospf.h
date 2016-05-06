/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_ext_ospf.h
*
*  Project Code: VISPV100R007
*   Module Name: BFD EXTERN
*  Date Created: 2008-07-24
*        Author: qinyun
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME              DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-07-24      qinyun            Create
*
*******************************************************************************/
#ifndef _BFD_EXT_OSPF_H_
#define _BFD_EXT_OSPF_H_

#ifdef __cplusplus
extern "C" {
#endif

/*Added by guojianjun178934, BFD6和OSPFv3联动，要做刷新动作, 2014/9/16   问题单号:DTS2014090205788 */
/*BFD Ext的网络类型转换为BFD对应的IP版本*/
#define BFD_EXT_IP_VERTION_MAP(IP_VERTION)  \
  (((IP_VERTION) == BFD_EXT_TABLE_IPV4) ? BFD_OVER_IPV4 : BFD_OVER_IPV6)
/* End of Added by guojianjun178934, 2014/9/16   问题单号:DTS2014090205788 */

typedef struct tagBfdOspfRuleEntry
{
    struct tagBfdOspfRuleEntry   *pstNextRule;        
    ULONG   ulRuleType; 
    ULONG   ulIfIdOrProcId; 
    UCHAR   szIfFullName[BFD_EXT_MAX_INTF_NAME_LEN + 1];
    ULONG   ulInstanceID;                 /*OSPFV3接口Instance ID*/
    ULONG   ulMinTxInterval;              /* BFD期望的发送间隔 */ 
    ULONG   ulMinRxInterval;              /* BFD的本地接收能力 */ 
    ULONG   ulDetectMult ;                /* BFD的本地检测倍数 */ 
    USHORT  usEnable ;                    /* 使能OSPF联动标志:1-Enable,0-Disable */ 
    USHORT  usBlock ;                     /* 使能接口Block功能标志:1-Block,0-Unblock */ 
}BFD_OSPF_RULE_ENTRY_S;

typedef struct tagBfdOspfRuleTable
{
    /*Modified by liangjicheng 00103192, , 2011/10/27   问题单号: REQ-201108278323-BFD-SPEC */
    /* ULONG   ulBlockNumber;    */        
    /* ULONG   ulRuleNumber;     */  
    ULONG   ulProcNumber;
    ULONG   ulIntfNumber;
    /*End of Modified by liangjicheng 00103192, 2011/10/27   问题单号: REQ-201108278323-BFD-SPEC */
    struct tagBfdOspfRuleEntry   stRelatingRule;        
}BFD_OSPF_RULE_TABLE_S;

/*************************************/
/*          过滤器结构体             */
/*************************************/
typedef struct tagBfdForOspfFilter
{ 
    ULONG ulNetworkType;
    ULONG ulProcIndex;
    ULONG ulIfIndex;
    ULONG ulInstanceID;   /*接口InstanceID(用于OSPFV3查询过滤)*/
    ULONG ulFilterType;   /*过滤类型：BFD_OSPF_FILTER_X*/
    ULONG ulFilterEnableFlag;/*进程号，VRF ID，接口索引有效无效标志*/
}BFD_FOR_OSPF_FILTER_S;

extern VOID *Extern_BFD_GetNextRuleByFilter(VOID *pFilter,VOID *pCurEntry);
extern ULONG Extern_BFD_AddOspfRule(ULONG ulNetworkType, BFD_API_OSPF_RULE_OP_S *pstBFDOSPFRuleInput);
extern ULONG Extern_BFD_DelOspfRule(ULONG ulNetworkType, ULONG ulProcIndex, UCHAR *pszIfName, ULONG ulInstanceID);
extern ULONG Extern_BFD_OSPF_NodeAddFun(ULONG ulIfIndex,ULONG ulProcIndex,ULONG ulInstanceId,
                                            ULONG ulRouterId,ULONG *pSrcIp,ULONG *pDstIp,ULONG ulNetworkType);
extern ULONG Extern_BFD_OSPF_NodeDelFun(ULONG ulIfIndex,ULONG ulProcIndex,ULONG ulInstanceId,
                                            ULONG ulRouterId,ULONG ulNetworkType);
extern ULONG Extern_BFD_OSPF_ProcShutDownFun(ULONG ulProcIndex,ULONG ulNetworkType);
extern ULONG Extern_BFD_FindOspfRelation(ULONG *pulSessionId,ULONG ulIfIndex,ULONG ulProcId,
                                            ULONG ulInstanceId,ULONG ulRouterId,ULONG ulNeworkType);
extern VOID Extern_BFD_OSPF_DelDataOnly( BFD_RELATION_TABLE_S *pstBfdRelationTable);
extern VOID * Extern_BFD_GetNextOspfRelationByFilter(VOID *pFilter,VOID *pCurEntry);

/*Begin BC3D02903 liangjicheng 2010-04-19 */
extern VOID Extern_BFD_ProcOSPFRuleUpdate(BFD_EXT_OSPF_RULE_MSG *pstOSPFRuleMsg);
/*End   BC3D02903 liangjicheng 2010-04-19 */
/*Added by guojianjun178934, BFD6和OSPFv3联动，要做刷新动作, 2014/9/12   问题单号:S-IP-C20-003-OSPFv3.001  */
extern VOID Extern_BFD_ProcOSPFV2RuleUpdate();
extern VOID Extern_BFD_ProcOSPFV3RuleUpdate(BFD_EXT_OSPF_RULE_MSG *pstOSPFRuleUpdateMsg);
/* End of Added by guojianjun178934, 2014/9/12   问题单号:S-IP-C20-003-OSPFv3.001  */

#ifdef __cplusplus
}
#endif

#endif


