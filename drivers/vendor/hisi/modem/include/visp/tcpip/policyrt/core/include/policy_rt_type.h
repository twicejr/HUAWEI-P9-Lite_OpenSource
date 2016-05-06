/*******************************************************************************
*
*
*                Copyright 2013, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              policy_rt_type.h
*
*  Project Code: VISPV300R002
*   Module Name: POLICY RT 
*  Date Created: 2013-08-12
*        Author: Chandra
*   Description: Policy route related APIs declarations and data structures are 
*                defined in th file.
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2013-08-12   Chandra    Create
*
*******************************************************************************/
#ifndef _POLICY_RT_TYPE_H_
#define _POLICY_RT_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define POLICYRT_TRUE 1
#define POLICYRT_FALSE 0

#define POLICYRT_VRF_MID 0x00000002

#define POLICYRT_MAX_APPLY_ITEM 2

typedef struct tagPOLICYRT_APPLY_INTF
{
    ULONG ulIfApply;              /* Interface index */
    ULONG ulUserData ;          /* Store the data given by user */
} POLICYRT_APPLY_INTF_S;

typedef struct tagPOLICYRT_APPLY_NH
{
    ULONG ulNextHopApply;   /* Nexthop address */
    struct tagPOLICY_NEXTHOP_LIST *nhListPtr;
} POLICYRT_APPLY_NH_S;

typedef union tagPOLICYRT_APPLY_U
{
    POLICYRT_APPLY_INTF_S stApplyIf;
    POLICYRT_APPLY_NH_S stApplyNh;
} POLICYRT_APPLY_ITEM_U;

typedef struct tagPOLICYRT_APPLY
{
    UCHAR ucApplyType;       /* Interface (0) OR NextHop (1) */
    UCHAR ucRes[3];
    POLICYRT_APPLY_ITEM_U unItem;
} POLICYRT_APPLY_S;

typedef struct tagPOLICYRT_NODE
{
    ULONG ulNodeID;
    ULONG ulAclGroup;
    UCHAR ucActive;             /* give the status of policy node.
                                                   1- effective (download to TRAN)
                                                   0 - non-effective (not download) */
    UCHAR ucApplyItemCnt;
    UCHAR ucNeedToUpdateTRAN;  /* Set to TRUE, when user update match (or) Apply.
                                  Make it FALSE once invoke Finish call */
    UCHAR ucAdminStatus;             /*Admin status of the node. Default: Enable */
    POLICYRT_APPLY_S stApplyItem[2]; 
    VOID *pstPolicyGroup;   /* Back pointer to policy group for waitlist, this need to be analyze further*/
    struct tagPOLICYRT_NODE *nextNode;
} POLICYRT_NODE_S;

typedef struct tagPOLICY_CNTRL_BLK
{
    ULONG ulPolicyID;
    ULONG ulVrfIndex;
    UCHAR ucActionType;
    UCHAR ucRes[1];	
    USHORT usNodeCnt;
    POLICYRT_NODE_S *nodeList;
    struct tagPOLICY_CNTRL_BLK *nextBlk;
} POLICY_CNTRL_BLK_S;

/* Data structure to maintain the node with only NextHop apply item configured */
typedef struct tagPOLICY_NEXTHOP_LIST
{
    ULONG ulVrfIndex;
    ULONG ulPolicyID;
    ULONG ulNodeID;
    ULONG ulNextHopApplyIf; /* Derived NextHop Apply item out-interface */
    ULONG ulInfIPAddr;       /* Matched Interface address */
    ULONG ulMaskLen;          /* Matched interface IP mask length */
    
    POLICYRT_NODE_S *nodePtr;
    struct tagPOLICY_NEXTHOP_LIST *nextNHnode;
} POLICY_NEXTHOP_LIST;


/* Type of IP event which can be notified to POLICYRT from AM4 */
typedef enum tagPOLICYRT_EVENT_E
{
    POLICYRT_IP_ADD_EVENT  = 0,
    POLICYRT_IP_DEL_EVENT,
    POLICYRT_TRUNKPORT_ADD_EVENT,
    POLICYRT_TRUNKPORT_REMOVE_EVENT,
    POLICYRT_EVENT_MAX
} POLICYRT_EVENT_E ;

typedef enum tagPOLICYRT_SUBNET_CMP_E
{
    POLICYRT_SAME_SUBNET  = 0,
    POLICYRT_BETTER_SUBNET,
    POLICYRT_POOR_SUBNET,
    POLICYRT_UNMATCHED_SUBNET,
    POLICYRT_UNKNOWN_SUBNET
} POLICYRT_SUBNET_CMP_E;



/* Create policy route table based on number of VRFs (1 ~ 1024) configured in the system */
/* Get the value of 'g_ulVrfMaxInstanceNum' and create those many pointers at initialization time.*/
extern ULONG g_ulPolicyRtInitFlag;
extern POLICY_CNTRL_BLK_S **gPolicyRtTable;
extern POLICY_NEXTHOP_LIST **gPolicyNHOnlyList;
extern ULONG g_ulPolicyRtPolicyNum;
extern ULONG  g_ulPolicyRtPolicyNodeNum;
extern ULONG g_ulPolicyRtVrfNum;
extern struct IIF_VRF_ComIntFUNVtbl * g_pstPolicyRtVrfVtbl;
extern struct IIF_IFNET_ComIntFUNVtbl* g_pstPolcyRtIfFunVtbl;
extern struct IIF_IPV4_IP_AM4_ComIntFUNVtbl* g_pstPRtAm4FunVtbl;
extern ULONG (*g_pfIntfStateChangeNotifyPolicyRt)(ULONG, ULONG, VOID *);
extern ULONG (*g_pfIpChangeNotifyPolicyRoute)(ULONG, ULONG, ULONG, ULONG);

ULONG PolicyRt_VRF_DelCallback( ULONG ulEvents , VOID * pulVrfIndex);

ULONG PolicyRt_DelIfNotifyCallback(ULONG ulIfIndex);

ULONG POLCYRT_IfStatusNotifyCallback(ULONG ulIfIndex, ULONG ulCmd, VOID *pData);

VOID POLICYRT_ProcessUpEvent(ULONG ulIfIndex);
VOID POLICYRT_ProcessDownEvent(ULONG ulIfIndex);


ULONG POLCYRT_AM4StatusNotifyCallback(ULONG ulIpEvent, ULONG ulIpAddr, ULONG ulIfIndex,ULONG ulMask);

#ifdef __cplusplus
}
#endif   /* end of __cplusplus */

#endif   /* end of _POLICY_RT_TYPE_H_ */

