
#ifndef _VLINK_H_
#define _VLINK_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


#define VLINK_MAX(X, Y)   (((X)>(Y)) ? (X) : (Y))

#define PPI_INVALID_VLINKINDEX      0

/* 注意: VLINK_ROUTE_PROT_VLINK需要与 qc0rtmib.h 中的宏ATG_QC_PROT_VLINK值同步,标明该路由是i3上报的直连路由*/
#define VLINK_ROUTE_PROT_VLINK      0x00130000

typedef struct tagIPC_VLINK_STAT
{
    ULONG ulErrVlinkIndexCount;         /*IPC vlinkIndex 非法上报次数*/
    ULONG ulErrVlink6IndexCount;        /*IPC6 vlinkIndex 非法上报次数*/
    ULONG ulErrVrfIndexCount;           /*IPC vrfIndex 非法上报次数*/
//    ULONG ulErrVrfIndex6Count;          /*IPC6 vrfIndex 非法上报次数,v6暂时不支持vrf，后续可以放开*/
} IPC_VLINK_STAT_S;


typedef struct tagVLINK_NODE
{
    ULONG   ulVlinkIndex;       /*Vlink索引*/
    ULONG   ulIpAddr;           /*地址*/
    ULONG   ulIp6Addr[4];       /* IP6地址 */
    UINTPTR ulHandle;           /*保存Vlink路由的节点头*/
    ULONG   ulRtCount;          /*Vlink路由计数*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    ULONG   ulVrfIndex;
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    AVL3_NODE_S stVlinkNode;    /* AVL Node */
}VLINK_NODE_S;

/* Add for DTS2011022102588, by tanyiming00171953, at 2011-02-22. 修改原因: 新增Vlink路由查询接口,增强Vlink维测手段  */
typedef struct tagVLINK_RT4_ENTRY
{
     ULONG  ulRt_Dest;  
     ULONG  ulRt_Dest_PrefLen;
     ULONG  ulRt_Nexthop;
     ULONG  ulRt_Flags;         /* route flags -RTF_GATEWAY, RTF_HOST */ 
     ULONG  ulRt_IfIndex;       /* index of outgoing interface */
     ULONG  ulRt_ATIndex;       /* index of virtual link between rt_stLclAddr */
     ULONG  ulRt_Slot;          /* slot num of outgoing interface */
     ULONG  ulRt_Loc;           /* local address */
     ULONG  ulRt_Loc_PrefLen;   /* local address mask lenth */
     ULONG  ulRTPri;            /* route priority */
     
     UCHAR   ucIfName[MAX_IF_NAME_LENGTH + 1];
     ULONG  ulVrfIndex;
     ULONG  ulLastUpdTime;
     struct tagVLINK_RT4_ENTRY*   pstRt_Next;  
     struct tagVLINK_RT4_ENTRY*   pstRt_Prev;  
     VLINK_NODE_S*   pstVlink_Node;
} VLINK_RT4_ENTRY_S;

typedef enum enVLINKPPIOPER
{
    VLINK_PPI_ADD,
    VLINK_PPI_DEL,
    VLINK_PPI_UPDATE,
}VLINKPPIOPER_E;

typedef struct tagVLINK_PPI_HOOK
{
    /*VlinkIndex索引更新邋通知 */
    ULONG (*pfVLINK_PPI_INDEX_Update)(ULONG ulOperType, VLINK_NODE_S *pstVlinkNode,ULONG ulIfIndex);
    /*FIB4节点更新通知 */
    /*Modified by l00147446 DTS2010080601639 产品在连续调用删除地址，接口去绑定VRF的情况下 无任务切换 会导致VLINK路由残留 2010/8/14*/
    ULONG (*pfVLINK_PPI_NODE_Update)(ULONG ulOperType,ULONG ulVrfIndex,RT4_ENTRY_S *pstRtEntry, ULONG *pulVlinkIndex,ULONG *pulNpFlag);
    /*FIB6节点更新通知 */    
    ULONG (*pfVLINK6_PPI_NODE_Update)(ULONG ulOperType,ULONG ulVrf6Index,RT6_ENTRY_S *pstRtEntry, ULONG *pulVlinkIndex,ULONG *pulNpFlag);
    /*FIB4主机路由更新通知*/
    ULONG (*pfVLINK_PPI_ROUTE_Update)(ULONG ulOperType, PPI_RTMSG4_S *pstPPIRtMsg);
    /*FIB6主机路由更新通知*/
    ULONG (*pfVLINK_PPI_ROUTE6_Update)(ULONG ulOperType, PPI_RTMSG6_S *pstPPIRtMsg,ULONG ulNpFlag);
}VLINK_PPI_HOOK_S;

LONG VLINK_COMPARE(VOID *a, VOID *b);
#define VLINK_OFFSETOF(STRUCT,FIELD) (ULONG)((UCHAR *)(&((STRUCT *)0)->FIELD) - (UCHAR *)0)



#define VLINK_INIT_NODE(NODE)            (NODE).parent = NULL;                \
                                         (NODE).left = NULL;                  \
                                         (NODE).right = NULL;                 \
                                         (NODE).sLeftHeight = -1;                \
                                         (NODE).sRightHeight = -1

/* Add for DTS2011022102588, by tanyiming00171953, at 2011-02-22. 修改原因: 新增Vlink路由查询接口,增强Vlink维测手段  */                                         
#define VLINK_SET_RT4_ENTRY(VLINKRTNODE,RTNODE,VLINKNODE,VID)  \
                                         (VOID)TCPIP_Mem_Set ((CHAR*)VLINKRTNODE, 0, sizeof(VLINK_RT4_ENTRY_S));\
                                         (VLINKRTNODE)->ulRt_Dest = (RTNODE)->ulRt_Dest;                \
                                         (VLINKRTNODE)->ulRt_Dest_PrefLen = (RTNODE)->ulRt_Dest_PrefLen;                \
                                         (VLINKRTNODE)->ulRt_Nexthop = (RTNODE)->ulRt_Nexthop;                \
                                         (VLINKRTNODE)->ulRt_Flags = (RTNODE)->ulRt_Flags;                \
                                         (VLINKRTNODE)->ulRt_IfIndex = (RTNODE)->ulRt_IfIndex;                \
                                         (VLINKRTNODE)->ulRt_ATIndex = (RTNODE)->ulRt_ATIndex;                \
                                         (VLINKRTNODE)->ulRt_Slot = (RTNODE)->ulRt_Slot;                \
                                         (VLINKRTNODE)->ulRt_Loc = (RTNODE)->ulRt_Loc;                \
                                         (VLINKRTNODE)->ulRt_Loc_PrefLen = (RTNODE)->ulRt_Loc_PrefLen;                \
                                         (VLINKRTNODE)->ulRTPri = (RTNODE)->ulRTPri;                \
                                         (VOID)TCPIP_Mem_Copy((VLINKRTNODE)->ucIfName,IF_MAX_INTERFACE_NAME_LEN + 1,(RTNODE)->ucIfName,IF_MAX_INTERFACE_NAME_LEN + 1);\
                                         (VLINKRTNODE)->ulVrfIndex = VID;\
                                         (VLINKRTNODE)->pstVlink_Node = (VLINKNODE)                                         

/* Modified by y00176567, at 2011-05-27. 修改原因: 消除VC三级告警 */
/* (PPINODE)->ucDestPrefixLength = (UCHAR)((VLINKNODE)->ulRt_Dest_PrefLen),添加(UCHAR),保证两端类型一致 */
/* (PPINODE)->ucLocalPrefixLength = (UCHAR)(VLINKNODE)->ulRt_Loc_PrefLen; 添加(UCHAR),保证两端类型一致 */
#define VLINK_GET_RT4_ENTRY(PPINODE,VLINKNODE)           (PPINODE)->ulDestination = VOS_NTOHL((VLINKNODE)->ulRt_Dest);                \
                                         (PPINODE)->ucDestPrefixLength = (UCHAR)((VLINKNODE)->ulRt_Dest_PrefLen);                \
                                         (PPINODE)->ulNexthop = VOS_NTOHL((VLINKNODE)->ulRt_Nexthop);                \
                                         (PPINODE)->ulFlags = (VLINKNODE)->ulRt_Flags;                \
                                         (PPINODE)->ulIfIndex = (VLINKNODE)->ulRt_IfIndex;                \
                                         (PPINODE)->ulATIndex = (VLINKNODE)->ulRt_ATIndex;                \
                                         (PPINODE)->ulSlot = (VLINKNODE)->ulRt_Slot;                \
                                         (PPINODE)->ulLocalAddress = VOS_NTOHL((VLINKNODE)->ulRt_Loc);                \
                                         (PPINODE)->ucLocalPrefixLength = (UCHAR)((VLINKNODE)->ulRt_Loc_PrefLen);                \
                                         (PPINODE)->usRTPri = (USHORT)(VLINKNODE)->ulRTPri;                \
                                         (VOID)TCPIP_Mem_Copy((PPINODE)->ucIfName,IF_MAX_INTERFACE_NAME_LEN + 1,(VLINKNODE)->ucIfName,IF_MAX_INTERFACE_NAME_LEN + 1);\
                                         (PPINODE)->ulVrfIndex = (VLINKNODE)->ulVrfIndex


#define VLINK_INSERT(TREE, NODE, TREE_INFO)                                    \
        (NULL == AVL3_FindToInsert(&(TREE), &(NODE), &(TREE_INFO)))
    
#define VLINK_DELETE(TREE, NODE)            AVL3_DeleteNode(&(TREE), &(NODE))
    
#define VLINK_FIND(TREE, KEY, TREE_INFO)    AVL3_FindNode(&(TREE), (KEY), &(TREE_INFO))
    
#define VLINK_NEXT(NODE, TREE_INFO)         AVL3_GetNextNode(&(NODE), &(TREE_INFO))
    
    
#define VLINK_FIRST(TREE, TREE_INFO)        AVL3_GetFirstNode(&(TREE), &(TREE_INFO))

/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

#define ROUTE4_DEL_EQUAL(pstDelRt4,pstEntryRt4) ((pstDelRt4)->ulRt_Dest ==(pstEntryRt4)->ulRt_Dest \
                                                && (pstDelRt4)->ulRt_Dest_PrefLen == (pstEntryRt4)->ulRt_Dest_PrefLen\
                                                && (pstDelRt4)->ulRt_Nexthop == (pstEntryRt4)->ulRt_Nexthop\
                                                &&(pstDelRt4)->ulRt_IfIndex == (pstEntryRt4)->ulRt_IfIndex\
                                                )
                                                
VOID VLINK_Module_Init();
ULONG VLINK_PPI_HookRegister(VLINK_PPI_HOOK_S *pstHookFunc);
/*Modified by l00147446 DTS2010080601639 产品在连续调用删除地址，接口去绑定VRF的情况下 无任务切换 会导致VLINK路由残留 2010/8/14*/
ULONG VLINK_PPI_NODE_Update(ULONG ulOperType,ULONG ulVrfIndex,RT4_ENTRY_S *pstRtEntry, ULONG *pulVlinkIndex,ULONG *pulNpFlag);
ULONG VLINK6_PPI_NODE_Update(ULONG ulOperType,ULONG ulVrf6Index,RT6_ENTRY_S *pstRt6Entry, ULONG *pulVlinkIndex,ULONG *pulNpFlag);
ULONG VLINK_PPI_INDEX_Update(ULONG ulOperType, VLINK_NODE_S *pstVlinkNode,ULONG ulIfIndex);
ULONG VLINK_PPI_ROUTE_Update(ULONG ulOperType, PPI_RTMSG4_S *pstPPIRtMsg);
ULONG VLINK_PPI_ROUTE6_Update(ULONG ulOperType, PPI_RTMSG6_S *pstPPIRtMsg,ULONG ulNpFlag);

/*Modified by l00147446 DTS2010080601639 产品在连续调用删除地址，接口去绑定VRF的情况下 无任务切换 会导致VLINK路由残留 2010/8/14*/
ULONG VLINK_NodeRegister(ULONG ulVrfIndex,RT4_ENTRY_S *pstRtEntry, ULONG *pulVlinkIndex,ULONG *pulNpFlag);
ULONG VLINK_NodeUnRegister(ULONG ulVrfIndex,RT4_ENTRY_S *pstRtEntry, ULONG *pulVlinkIndex,ULONG *pulNpFlag);
ULONG VLINK_IndexUpdate(ULONG ulVrfIndex,ULONG ulIpAddr,ULONG ulVlinkIndex,ULONG ulOper,ULONG ulIfIndex);
ULONG VLINK6_NodeRegister(ULONG ulVrf6Index,RT6_ENTRY_S *pstRt6Entry, ULONG *pulVlinkIndex,ULONG *pulNpFlag);
ULONG VLINK6_NodeUnRegister(ULONG ulVrf6Index,RT6_ENTRY_S *pstRt6Entry, ULONG *pulVlinkIndex,ULONG *pulNpFlag);
ULONG VLINK6_IndexUpdate(ULONG ulVrf6Index,ULONG ulIp6Addr[4],ULONG ulVlinkIndex,ULONG ulOper,ULONG ulIfIndex);
ULONG Vlink_Rt6Compare(RT6_ENTRY_S *pstDelRt6 , RT6_ENTRY_S *pstEntryRt6);
VOID VLINK_DbgVlinkIndexUpdate(ULONG ulIpAddr,ULONG ulVlinkIndex,ULONG ulOper,ULONG ulIfIndex);
VOID VLINK6_DbgVlinkIndexUpdate(ULONG ulIp6Addr[4],ULONG ulVlinkIndex,ULONG ulOper,ULONG ulIfIndex);

VOID VLINK6_DbgVlinkRoute(ULONG ulOper,RT6_ENTRY_S *pstNewRtEntry);
/* Add for DTS2011022102588, by tanyiming00171953, at 2011-02-22. 修改原因: 新增Vlink路由查询接口,增强Vlink维测手段  */
/* VOID VLINK_DbgVlinkRoute(ULONG ulOper,RT4_ENTRY_S *pstNewRtEntry); */
VOID VLINK_DbgVlinkRoute(ULONG ulOper,VLINK_RT4_ENTRY_S *pstNewRtEntry);
VOID *VLINK_GetNextEntryByFilter(VOID *pFilter,VOID *pCurEntry);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _VLINK_H_ */



