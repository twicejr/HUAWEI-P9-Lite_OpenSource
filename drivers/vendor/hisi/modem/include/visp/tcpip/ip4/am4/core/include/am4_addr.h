/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              am4_addr.h
*
*  Project Code: VISPV100R005
*   Module Name: AM4  
*  Date Created: 2006-01-04
*        Author: Li LiXiang
*   Description: 声明了AM中内部使用的一些函数
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-04   Li LiXiang              Create
*  2006-04-21   Jiangtao                根据编程规范，对文件进行规范化整理 
*  2007-12-07   f54882                  for A82D21769,新增两个函数申明
*  2009-03-17   liangjicheng            BC3D01271 【AM4】删除地址，消息上报 增加函数
                                        IP_Get_Second_IpAddr
*
*******************************************************************************/
 
#ifdef __cplusplus
extern "C" {
#endif


#ifndef _AM4_ADDR_H_
#define _AM4_ADDR_H_


#ifndef MIN
#define MIN(a, b)       ((a) < (b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b)       ((a) > (b) ? (a) : (b))
#endif


/* 主要用于主控板向接口板通知时，作为标志中的一位通知来
 * 事件。不能与地址标志重复。（因为都用地址的ipif_ulAddrFlag）
 */
#define IP_ADD       0x0100   /* 添加地址 */
#define IP_DEL       0x0200   /* 删除地址 */
#define IP_CHA       0x0400   /* 改变地址 */
#define IP_OTH       0x0800   /* 不通知链路层 */
#define IP_INVALID   0x1000   /* 是PPP报上来的，检测不合法 */

/* 增加地址时的操作标志 */
#define LINKTAIL      1     /* 从链尾插入 */
#define CHECKCONFLICT 2     /* 检测冲突 */
#define INVALID       4     /* 地址有效性检测 */
#define PPP           8     /* PPP negotiated */
#define IP_DELSEC     512   /* 删除从地址,通知Eth删除ARP表项 */

/* 通知地址操作类型时使用的标志位,根据这些标志位决定向外部发出的通知 */
#define BEFORE_DEL    0x0010
#define AFTER_DEL     0x0020
#define BEFORE_ADD    0x0040
#define AFTER_ADD     0x0080
#define IP_PRIMARY    0x0100
#define IP_SECONDARY  0x0200


/* VRF's address tree check operation flag */
#define IP_PPP_FLAG   0x01

#define ARP_PROXY_SAMESUBNET   2 

#define NO_INCLUDE    0x02
#define ANY_INCLUDE   0x04
#define IP_BORROW_FLAG   0x08 /* 该标记表示不与借用地址进行冲突检测 */

#define DHCP4C_CFG_FLAG   0x100  /*标记DHCP4C可以获取相同的网段的地址*/

typedef struct tagIPInsertPos
{
    IP_radix_node *pstNode;
    USHORT usOpCode;
    USHORT usDiffBitLen;
} IPInsertPos;


typedef struct tagIPCMDMSG
{
    ULONG   ipif_ulIndexIf;     /* 接口索引 */
    ULONG   ipif_ulFlags;       /* 接口标志位：广播属性、NBMA属性IFF_BROADCAST、IFF_NBMA*/
    ULONG   ipif_ulAddrFlag;    /* 接口地址的特性：地址协商、借用地址、有自己的地址、IFF_NEGOTIATE,*/
    ULONG   ipif_ulBorrowIfIndex;
    CHAR    ipif_szIfName[ IF_MAX_INTERFACE_NAME_LEN+1];   /*  接口名  */
    ULONG   ulNum;
    ULONG   ulMultiNum;
    
    ULONG       ulIcmpRedirect; 
    ULONG       ulIcmpHostUnreach;

    IPIFADDR_S  ipif_stIpIfAddrList[MAXADDR_ON_ONEIF]; /* 接口的单播地址链：双向链表 */
    IPMULTI_S   ipif_stIPIfMultiList[1];    /*接口的多播地址链:  循环链表*/
}IP_IPCMDMSG_S;



/* 遍历本接口的地址 */
#define V_LIST_EMPTY(ptr)   ((ptr)->ia_v_pNext == (ptr))
#define V_LIST_FIRST(ptr)   ((ptr)->ia_v_pNext)
#define V_LIST_NEXT(ptr)    ((ptr)->ia_v_pNext)
#define V_LIST_LAST(ptr)    ((ptr)->ia_v_pPrev)
#define V_LIST_SCAN(pHead, pNode) \
    for ((pNode) = V_LIST_FIRST((pHead)); (pNode) != (pHead); (pNode) = V_LIST_NEXT((pNode)))

/* 遍历全局的地址 */
#define H_LIST_EMPTY(ptr)   ((ptr)->ia_h_pNext == (ptr))
#define H_LIST_FIRST(ptr)   ((ptr)->ia_h_pNext)
#define H_LIST_NEXT(ptr)    ((ptr)->ia_h_pNext)
#define H_LIST_LAST(ptr)    ((ptr)->ia_h_pPrev)
#define H_LIST_SCAN(pHead, pNode) \
    for ((pNode) = H_LIST_FIRST((pHead)); (pNode) != (pHead); (pNode) = H_LIST_NEXT((pNode)))


/*
 * changed for permitting address overlap 2002-10-30 by mayun & yuyong
 * now use radix tree
 */
extern ULONG IP_InsertTree(IPIFNET_S *pstIpIf, IPIFADDR_S *pstAddr);  
extern ULONG IP_DeleteTree(IPIFADDR_S *pstAddr);
extern ULONG IP_CheckOverlap(IPIFNET_S *pstIpIf, ULONG ulIpAddr, ULONG ulMask, ULONG ulFlag);

IPMULTI_S *IPIF_AddMulti(INADDR_S *pstIn, IPIFNET_S *pstIpIf);
LONG IPIF_DelMulti( INADDR_S *pstInAddr, IPIFNET_S *pstIpIf );
ULONG IP_GetNumOfLend( IPIFNET_S *pstCurIf );
ULONG IP_Del_AllOfIfIpAddr( IPIFNET_S *pstIpIf, UCHAR ucVrrpFlag );
ULONG IP_DelAll(IPIFNET_S *pstIpIf);
VOID IP_NotifyWithAddrChange(ULONG ulIfIndex, ULONG ulIpAddrFlag,  ULONG ulActionTime );
IPIFADDR_S * IP_FindAddrWithMask( ULONG ulIpAddr, ULONG ulIpMask ,IPIFNET_S *pstIpIf );
ULONG IP_Del_Addr( ULONG ulIpAddr, ULONG  ulIpMask, IFNET_S *pstIfNet );
IPIFADDR_S * IP_Find_SameIpAddr( ULONG ulIpAddr, IPIFNET_S *pstIpIf );
ULONG IP_Get_First_IpAddr(IPIFNET_S *pstIpIf, ULONG *pulFirstAddr, ULONG *pulFirstMask);
/*Begin BC3D01271 liangjicheng 2009-03-17*/
ULONG IP_Get_Second_IpAddr( IPIFNET_S *pstIpIf, ULONG *pulSecondAddr, ULONG *pulSecondMask );
/*End BC3D01271 liangjicheng 2009-03-17*/
ULONG IP_Add_Addr(ULONG ulIpAddr, ULONG ulIpMask, ULONG ulIpDstAddr, IFNET_S *pstIfNet, ULONG ulAddrFlag);
ULONG IP_Del_AllOfIfIpMultiAddr( IPIFNET_S *pstIpIf );

ULONG IP_AM4_AddBorrowOtherAddr(IPIFNET_S* pstMyIpIf, IPIFNET_S*pstLendIpIf);
ULONG IP_AM4_RemoveBorrowOtherAddr(IPIFNET_S* pstMyIpIf);

VOID DealWithOthersBorrowMyIPaddr(IPIFNET_S *pstCurIf, ULONG ulCmd, UCHAR ucNofityFlag);
ULONG IP_ConflictIpAddressSpecial(ULONG ulIfIndex, ULONG ulAddr, ULONG ulMask);
ULONG IP_ConflictIpAddressSpecial_PT(ULONG ulIfIndex, ULONG ulAddr, ULONG ulMask);

ULONG IP_NotifyRmAddrChange(PIPIFNET_S pstIpIf, ULONG ulIpAddr, ULONG ulIpMask, ULONG ulMainIpAddr, ULONG ulAction);
VOID DealWithOthersBorrowMyIPaddr_PT(IPIFNET_S *pstCurIf, ULONG ulCmd);
IPIFADDR_S *IP_GetBestIpAddrByVrf(SOCKADDRIN_S *pstSockInAddr, ULONG ulVrfIndex);
IPIFADDR_S *IP_GetBestIpIfForDontroute(SOCKADDRIN_S *pstSockInAddr, ULONG ulVrfIndex);
ULONG IP_SetIpConflictFlag(IFNET_S* pIf, ULONG ulIpAddr);
ULONG IP_ClearIpConflictFlag(IFNET_S* pIf, ULONG ulIpAddr);
BOOL_T IP_AM4_SupportSameSubAddr();

#endif  /* end of _AM4_ADDR_H_ */ 

#ifdef __cplusplus
}
#endif/* end of __cplusplus */
