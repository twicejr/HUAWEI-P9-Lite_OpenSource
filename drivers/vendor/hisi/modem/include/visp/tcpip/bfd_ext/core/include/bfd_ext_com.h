/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_ext_com.h
*
*  Project Code: VISPV100R007
*   Module Name: BFD EXTERN
*  Date Created: 
*        Author: 
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME         DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-07-24   qinyun       Create
*  2008-11-03   Q62011       Add for BC3D00658, BFD_OSPF_RULE_TYPE_INTF,
*                            BFD_OSPF_RULE_TYPE_PROC转移到api头文件中供用户使用
*******************************************************************************/
#ifndef _BFD_EXT_COM_H_
#define _BFD_EXT_COM_H_

#ifdef __cplusplus
extern "C" {
#endif
/*************************************/
/*              宏定义               */
/*************************************/
#define SID_EXT_BFD_OSPF_RULE_S 1
#define SID_EXT_BFD_RTM_NODE_S  2

/*#define BFD_OSPF_MAX_BLOCK_NUM      32   */
/*#define BFD_OSPF_MAX_RULE_NUM       32   */
/*#define BFD_STATIC_MAX_RELATION_NUM 32   */
/*#define BFD_STATIC_ONE_SESS_MAX_NUM 1    */
#define BFD_OSPF_MAX_BLOCK_NUM      64
#define BFD_OSPF_MAX_RULE_NUM       64
#define BFD_STATIC_MAX_RELATION_NUM  10*1024
#define BFD_STATIC_ONE_SESS_MAX_NUM  10*1024

#define BFD_STATIC_DETECT_TIME_DEFAULT  10*1000
#define BFD_STATIC_DETECT_TIME_MAX      50*1000
#define BFD_STATIC_DETECT_MAX_SECS      50
#define BFD_STATIC_DETECT_MIN_SECS      1

/*与BFD_MAX_SESSION_ID保持一致，若BFD模块的会话个数处理有修改则需要相应修改本模块的处理*/
#define BFD_EXT_MIN_SESSION_ID             1          /* BFD最小session id*/
#define BFD_EXT_MAX_SESSION_ID          2000          /* BFD最大session id*/

#define BFD_EXT_TRUE                       1
#define BFD_EXT_FALSE                      0

/*标志位*/
#define BFD_EXT_YES     1
#define BFD_EXT_NO      0

typedef struct tagBFD_ADDR6_S
{
    ULONG     u6_uladdr[4];
}BFD_ADDR6_S;

#define HASH_BFD1(ulAddr) \
(((USHORT)((ULONG)(ulAddr)>>16)) ^ ((USHORT)(ulAddr)))

#define HASH_BFD2(pAddr6) \
     (HASH_BFD1(((BFD_ADDR6_S *)(pAddr6))->u6_uladdr[0]) ^ HASH_BFD1(((BFD_ADDR6_S *)(pAddr6))->u6_uladdr[1]) ^ \
      HASH_BFD1(((BFD_ADDR6_S *)(pAddr6))->u6_uladdr[2]) ^ HASH_BFD1(((BFD_ADDR6_S *)(pAddr6))->u6_uladdr[3]))

#define BFD_RELATION_HASH(ulVrfIndex, ulSessionID) \
    ((((((ulVrfIndex)>>11) + ((ulVrfIndex)&0x3ff) + ((ulSessionID)>>11) + \
        ((ulSessionID)&0x3ff))*(0x9e370001))>>(32-11))%(g_ulBFDMaxSessionNum))

#define BFD_EXT_INVALID_VRFINDEX 0xFFFFFFFF

/*modify by q62011 for ospfv3 */
typedef enum tagBFD_EXT_TABLE_NUM_E
{
    BFD_EXT_TABLE_IPV4 = 0,
    BFD_EXT_TABLE_IPV6,
    BFD_EXT_TABLE_MAX_NUM
}BFD_EXT_TABLE_NUM;

/* End of Added by qinyun62011, 2011/2/9   问题单号:V2R3C03-ROTUE-MERGE */

typedef struct tagBFD_ENTRY_S
{
    struct tagBFD_ENTRY_S   *pstNextEntry;        
} BFD_ENTRY_S;

/* Modified by likaikun213099, 解决staticnode资源释放后异步访问问题，采用了异步延迟释放，
   统一垃圾回收机制, 2014/12/25   问题单号:DTS2014122404643  */
typedef struct tagBFD_STATIC_NODE_S
{
    struct tagBFD_STATIC_NODE_S   *pstNextNode;  
    struct tagBFD_STATIC_NODE_S   *pstPreNode;
    struct tagBFD_STATIC_NODE_S   *pstLeft; /* 左子树 */
    struct tagBFD_STATIC_NODE_S   *pstRight; /* 右子树 */    
    VOID   *pTable;        
    ULONG   ulDstIp[4]; 
    ULONG   ulPreLen; 
    ULONG   ulNextHop[4]; 
    ULONG   ulIfIndex; 
    ULONG   ulTimeId;  
    ULONG   ulVrfIndex; /* Vrf Index V4,V6共用 */
    ULONG   ulIpVersion;/* 区分是V4还是V6的HASH节点 */
    ULONG   ulDelayFree;/* 延迟删除标记 */
} BFD_STATIC_NODE_S ;

typedef struct tagBFD_STATIC_NODE_GC_S
{
    SLL_NODE_S  stSllNode;
    BFD_STATIC_NODE_S  *pFreeHandle;
}BFD_STATIC_NODE_GC_S; /*BFD静态联动数据 垃圾回收数据*/
/*End of Modified by likaikun213099, 2014/12/25   问题单号:DTS2014122404643  */

/*modify by q62011 for ospfv3 */
typedef struct tagBFD_OSPF_NODE_S
{
    struct tagBFD_OSPF_NODE_S   *pstNextNode;        
    VOID   *pTable;        
    ULONG   ulInstanceId;     /*OSPFV3有效*/      
    ULONG   ulRouterId;        /*邻居的Route ID(网络序)*/      
    ULONG   ulIfIndex;            
    ULONG   ulProcId;           /*OSPF/OSPFV3实例号*/
} BFD_OSPF_NODE_S ;
/* End of Added by qinyun62011, 2011/2/9   问题单号:V2R3C03-ROTUE-MERGE */

typedef union unBFD_RELATION_PARA_U
{
    struct tagOSPFTbl
    {
        ULONG   ulNumber;       
        BFD_OSPF_NODE_S stNodeHd;
    }Bfd_For_Ospf;
    struct tagStaticTbl
    {
        ULONG   ulNumber;       
        ULONG   ulProcId;           /*RTM实例号*/
        BFD_STATIC_NODE_S stNodeHd;
    }Bfd_For_Static;
}BFD_RELATION_PARA_U;

typedef struct tagBFD_RELATION_TABLE_S
{
    ULONG   ulBfdVrfIndex;  /*BFD绑定的VRF*/
    ULONG   ulRelationVrfIndex;  /*realtion table的VRF，不同vrf的静态路由或者ospf可以关联同一个BFD*/
    ULONG   ulProcType;         /*路由协议类型，支持OSPF、RTM */
    ULONG   ulBfdSessId;        /*对应的BFD会话索引，初始化后任何情况都不应该清零*/
    ULONG   ulNetworkType;       /*类型，0-IPv4联动,1-IPv6联动 */
    BFD_RELATION_PARA_U  unRelationPara;
    struct tagBFD_RELATION_TABLE_S *pstNext;
} BFD_RELATION_TABLE_S;


typedef struct tagBFD_RELATION_HASHTABLE_S
{
    struct tagBFD_STATIC_NODE_S   *pstLeft; /* 左子树 */
    struct tagBFD_STATIC_NODE_S   *pstRight; /* 右子树 */
}BFD_RELATION_HASHTABLE_S;

typedef struct tagBfdRealtionHashNode
{
    ULONG ulBfdVrfIndex;
    ULONG ulBfdSessionID;
    BFD_RELATION_TABLE_S *pstBfdRelationTable;
    struct tagBfdRealtionHashNode *pstNext;
}BFD_RELATION_HASH_NODE_S;

typedef struct tagBfdRealtionHash
{
    BFD_RELATION_HASH_NODE_S *pstBfdHashNode;
}BFD_RELATION_HASH_S;

typedef struct tagOspfMsg
{
    /*modify by q62011 for ospfv3 */
    /*ULONG ulRouterId;           OSPF路由表索引ID
    ULONG ulIfIndex;            OSPF路由出接口
    ULONG ulLocalIp;            本端地址
    ULONG ulPeerIp;             对端地址*/
    ULONG ulNbrKey;                /*OSPF邻居查找关键字，V2是Route ID，V3是Instace ID*/
    ULONG ulIfIndex;               /*OSPF路由出接口*/
    ULONG ulLocalIp[LEN_4];        /*本端地址*/
    ULONG ulPeerIp[LEN_4];         /*对端地址*/
    ULONG ulIpType;                /*地址类型，BFD_OVER_IPV4(0)-IPv4地址,BFD_OVER_IPV6(1)-IPv6地址*/
    /* End of Added by qinyun62011, 2011/2/9   问题单号:V2R3C03-ROTUE-MERGE */
}BFD_TO_OSPF_MSG_S;/*与BFD_NTY_OSPF保持一致*/
typedef struct tagRtmMsg
{
    ULONG ulDstIp[LEN_4];       /*静态路由目的地址*/
    ULONG ulPreLen;             /*静态路由掩码长度*/
    ULONG ulNextHop[LEN_4];     /*静态路由下一跳地址*/
    ULONG ulOutIndex;           /*静态路由出接口索引*/
    ULONG ulIpType;             /*地址类型，BFD_OVER_IPV4(0)-IPv4地址,BFD_OVER_IPV6(1)-IPv6地址*/
}BFD_TO_RTM_MSG_S;/*与BFD_TO_RTM_DATA保持一致*/

typedef ULONG(*BFD_IFNET_GET_INDEX_BY_NAME)( CHAR *pszIfName, ULONG *pulIfIndex);
typedef ULONG(*BFD_IFNET_GET_NAME_BY_INDEX)( ULONG ulIfIndex, CHAR *pszIfName);

extern ULONG Extern_BFD_Init(VOID);
extern ULONG Extern_BFD_RegStatNotifyHook( BFD_RM_NOTIFY_HOOK_FUNC pfStatNotifyFunc );
extern ULONG Extern_BFD_RegOspfAndRtmType( ULONG ulOspf, ULONG ulRtm );
extern ULONG Extern_BFD_NotifyHook(ULONG ulSessionID, ULONG ulState,ULONG ulDstIP, ULONG ulSrcIP, 
                                         ULONG ulInIfIndex, ULONG ulAppGroup);
extern ULONG Extern_BFD_NotifyVrfHook(BFD_NOTIFY_BYVRF_S *pstBfdNotifyByVrf);
extern ULONG Extern_BFD6_NotifyHook(BFD6_NOTIFY_S *pstBfdNotify);

extern ULONG Extern_BFD_SetDbgSwitch(ULONG ulNetworkType, ULONG ulSwitch);
extern ULONG Extern_BFD_CheckDbgSwitch(ULONG ulNetworkType, ULONG ulRelaType);
extern VOID Extern_BFD_RemoveEntry(BFD_ENTRY_S *pstPrevEntry,BFD_ENTRY_S *pstCurEntry);
extern VOID Extern_BFD_InsertEntry(BFD_ENTRY_S *pstCurEntry,BFD_ENTRY_S *pstNewEntry);
extern VOID Extern_BFD_StateNotify(ULONG ulNotifyType, ULONG ulSessionID, ULONG ulVrfIndex, 
                                                        ULONG ulDstIP, ULONG ulSrcIP, ULONG ulInIfIndex, ULONG ulNewSessionID);
extern CHAR* VOS_IpAddrToStr(ULONG ulAddr, CHAR * szStr);
extern LONG VOS_strcmp(const CHAR *,const CHAR *);
extern VOID* TCPIP_Malloc(ULONG ulInfo, ULONG ulSize);
extern ULONG TCPIP_Free(VOID* pBuf);
extern VOID BFD_Begin_PT();
extern VOID BFD_End_PT();

extern ULONG Extern_BFD6_HashFunc(ULONG *ulDestIp,ULONG ulPrefixLen,ULONG *ulNextHop, ULONG ulVrfIndex);
extern ULONG Extern_BFD_HashFunc(ULONG *ulDestIp,ULONG ulPrefixLen,ULONG *ulNextHop, ULONG ulVrfIndex);
extern VOID Extern_BFD_AddToHashRelation(BFD_RELATION_HASHTABLE_S * pstHashNode, BFD_STATIC_NODE_S *pstBfdStNode);
extern VOID Extern_BFD_DelFromHashRelation(BFD_RELATION_HASHTABLE_S * pstHashNode, BFD_STATIC_NODE_S *pstBfdStNode);
extern VOID Extern_BFD_DelFromRelationTable(BFD_STATIC_NODE_S *pstBfdStNode);
extern BFD_RELATION_TABLE_S *Extern_BFD_GetRelationTable(BFD_RELATION_HASH_S *pstRelationHashRoot,
                                        ULONG ulBfdVrf, ULONG ulRealtionVrf, ULONG ulSessionID);
extern ULONG Extern_BFD_DelRelationTable(BFD_RELATION_HASH_S *pstRelationHashRoot,
                                                ULONG ulBfdVrf, ULONG ulRealtionVrf, ULONG ulSessionID);
extern ULONG Extern_BFD_AddRelationTable(BFD_RELATION_HASH_S *pstRelationHashRoot,
                                                   BFD_RELATION_TABLE_S *pstBfdRelationTable,
                                                   ULONG ulBfdVrf, ULONG ulSessionID);
extern ULONG Extern_BFD_RelationTabExchangeID(BFD_RELATION_HASH_S *pstRelationHashRoot,
                                        ULONG ulBfdVrf, ULONG ulOldSessionID, ULONG ulNewSessionID);
extern BFD_RELATION_HASH_NODE_S *Extern_BFD_GetRelationHash(BFD_RELATION_HASH_S *pstRelationHashRoot,
                                                    ULONG ulBfdVrf, ULONG ulSessionID);
extern VOID BFD_GC_TimeOut(VOID *pArg);

#ifdef __cplusplus
}
#endif

#endif


