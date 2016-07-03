
#ifndef _ETHVLN_PUBLIC_H_
#define _ETHVLN_PUBLIC_H_
#ifdef  __cplusplus
extern "C"{
#endif

#include"tcpip/vlan/include/ethvln_api.h"

enum 
{
    ETHVLAN_DEBUG_RECEIVE,
    ETHVLAN_DEBUG_SEND
};

/* VLAN一致性告警查找时的匹配方式,完全匹配 */
#define ETHVLAN_WARN_MATCH_EXACT        0
/* VLAN一致性告警查找时的匹配方式,只匹配本地IP */
#define ETHVLAN_WARN_MATCH_LOCALIP      1
/* VLAN一致性告警查找时的匹配方式,只匹配VLANID */
#define ETHVLAN_WARN_MATCH_VLANID       2
/* VLAN一致性告警查找时的匹配方式,通配 */
#define ETHVLAN_WARN_MATCH_WILD         3


typedef  struct tagETHVLAN_VID_NODE
{
 
    ULONG        ulMainIfIndex;                  /*该VID 所配置的主接口索引*/
    ULONG        ulSubIfIndex;                   /*VID所在的子接口索引*/
    struct  tagETHVLAN_VID_NODE * pstNextSubInf; /*下一个具有同VID的以太子接口*/
    struct  tagETHVLAN_VID_NODE * pstPrevSubInf; /*前一个具有同VID的以太子接口*/   
    struct  tagETHVLAN_VID_NODE * pstNextVID;    /*子接口下配置的下一个VID的节点*/

    struct  tagETHVLAN_VID_NODE * pstPrevVID;    /*子接口下配置的前一个VID的节点*/

    /*该VID的统计信息*/
    ULONG      ulVIDReceivePacketCount;
    ULONG      ulVIDTransmitPacketCount;
    ULONG      ulVIDReceiveByteCount;
    ULONG      ulVIDTransmitByteCount;

    USHORT      usVID ;                         /*本节点的VLANID*/
    USHORT      encapType ;
    UCHAR        ucDebugVlanPacket;
    UCHAR        ucRsv[3];
}ETHVLAN_VID_NODE_S;

/* VLAN一致性告警节点 */
typedef struct tagVLAN_CONSISTENCY_WARN_NODE
{
    struct tagVLAN_CONSISTENCY_WARN_NODE *pstPrevNode;
    struct tagVLAN_CONSISTENCY_WARN_NODE *pstNextNode;
    ULONG  ulSubIfIndex;        /* 子接口索引 */
    ULONG  ulLocalIP;           /* 本机IP,主机序 */
    ULONG  ulNeighbourIP;       /* 邻居IP,主机序 */
    USHORT usNeighbourVlanID;   /* 邻居IP所在VLAN */
    USHORT usReserve;           /* 保留字段 */
}VLAN_CONSISTENCY_WARN_NODE_S;
/* VLAN一致性告警链表 */
typedef struct tagVLAN_CONSISTENCY_WARN_LIST
{
    VLAN_CONSISTENCY_WARN_NODE_S    *pstHeadList;
    VLAN_CONSISTENCY_WARN_NODE_S    *pstTailList;
    ULONG  ulCurWarningNum; /* 队列中的当前告警数目 */
    ULONG  ulMaxWarningNum; /* 配置的最大告警数目 */
}VLAN_CONSISTENCY_WARN_LIST_S;

typedef  struct tagETHVLAN_PORTINFO
{
    ULONG   ulEncapType;                        /*封装的VLAN 的格式 0-ETHVLAN_NONE 1-DOT1Q 2-ISL */
    ULONG   ulRecvMbufErr;                      /*主接口统计信息*/
    ULONG   ulRecvInvalidVid;                   /*主接口统计信息*/
    ULONG   ulRecvInvalidSubIfStat;             /*子接口统计信息*/
    ULONG   ulRecvInvalidSubEncapType;          /*子接口统计信息*/
    ULONG   ulSendMbufErr;                      /*子接口统计信息*/
    ULONG   ulSendInvalidVid;                   /*子接口统计信息*/
    ULONG   ulSendPhyErr;                       /*子接口统计信息*/

    ULONG   ulVlanNum;                          /*接口下封装的VLAN的数量*/ 
    USHORT  usMinVID ;                          /*子接口上封装的最小的VLANID*/
    USHORT  usMaxVID ;                          /*子接口上封装的最大的VLANID*/

    ETHVLAN_VID_NODE_S * pstHeadNode;           /*指向VLAN的子接配置的VLAN的头结点*/
    ETHVLAN_VID_NODE_S * pstTailNode;           /*指向VLAN的子接配置的VLAN的尾结点*/
    
    VLAN_CONSISTENCY_WARN_LIST_S stVlanWarningList; /* VLAN配置不一致告警队列 */
 }ETHVLAN_PORTINFO_S;

#define  ETHVLAN_GETPORTINFOBYSUBIF(pstSubIf) \
     ((ETHVLAN_PORTINFO_S *)((IF_GETMTSOFT(pstSubIf))?(((ETHARP_MTSOFTCSUB_S*)IF_GETMTSOFT(pstSubIf))->ulVLANPortInfo):NULL))

#define ETHVLAN_GETPORTINFOBYIF(pstIf) \
     ((ETHVLAN_PORTINFO_S *)((IF_GETMTSOFT(pstIf))?(((ETHARP_MTSOFTC_S*)IF_GETMTSOFT(pstIf))->ulVLANPortInfo):NULL))
#define  ETHVLAN_GETVLANNODE( usVID, ifIndex,ulEncapType,ppVidNode)\
{\
    (*(ppVidNode)) = g_pstVIDNode[(usVID)];\
    while (*(ppVidNode) != NULL)\
    {\
        if ( (((USHORT)(ulEncapType) == ((*(ppVidNode))->encapType)) )  \
            && ((*(ppVidNode))->ulMainIfIndex == (ifIndex)\
            || (*(ppVidNode))->ulSubIfIndex == (ifIndex)))\
        {\
            break;\
        }\
        (*(ppVidNode)) = (*(ppVidNode))->pstNextSubInf;/*取得下一个同一VID */\
    }\
}

/* 从VLAN告警链表中取出最前面的告警节点 */
#define ETHVLN_WARNINGLIST_REMOVE_FIRSTNODE(pstWarningList, pstWarningNode) \
{\
    (pstWarningNode) = (pstWarningList)->pstHeadList;\
    if ((pstWarningNode) != NULL)\
    {\
        (pstWarningList)->pstHeadList =  (pstWarningNode)->pstNextNode;\
        if ((pstWarningNode)->pstNextNode)\
        {\
            (pstWarningNode)->pstNextNode->pstPrevNode = NULL;\
        }\
        (pstWarningList)->ulCurWarningNum--;\
        if ((pstWarningList)->pstTailList == (pstWarningNode) )\
        {\
            (pstWarningList)->pstTailList = (pstWarningNode)->pstPrevNode;\
        }\
    }\
}

/* 将告警节点插入告警链表尾部 */
#define ETHVLN_WARNINGLIST_INSERT_TO_TAIL(pstWarningList, pstWarningNode) \
{\
    /* 空链表 */\
    if (NULL == (pstWarningList)->pstTailList)\
    {\
        (pstWarningList)->pstTailList = (pstWarningList)->pstHeadList = (pstWarningNode);\
    }\
    else\
    {\
        (pstWarningList)->pstTailList->pstNextNode = (pstWarningNode);\
        (pstWarningNode)->pstPrevNode = (pstWarningList)->pstTailList;\
        (pstWarningList)->pstTailList = (pstWarningNode);\
    }\
    (pstWarningList)->ulCurWarningNum++;\
}


#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif /* end of  _ETHVLN_PUBLIC_H_*/


