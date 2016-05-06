/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              mbuf.h
*
*  Project Code: VISPV100R005
*   Module Name: Mbuf
*  Date Created: 2000-3-25
*        Author: zhang hong yan(19316)
*   Description: 此文件定义Mbuf相关的宏和数据结构
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)  Creat the first version.
*  2006-4-27  wang xin(03278)        根据编程规范，对文件进行规范化整理
*  2006-05-10  lu yao(60000758)     为支持ARM CPU字节对齐特性，修改结构。
*  2006-07-06 xiehuaguo             修改MBUF State字段赋值的开关中断保护 A82d03169
*******************************************************************************/

#ifndef _MBUF_H_
#define _MBUF_H_

#ifdef    __cplusplus
extern "C"{
#endif

/******************************************************************************

                              user tag data

******************************************************************************/
typedef struct tagMBufCommonInfo
{
    ULONG ulReceiveIfnetIndex;/*ethernet, 输入接口的ifnet索引，0表示本机产生的包*/
    ULONG ulSendIfnetIndex;/*ethernet*/

    /* V100R006 Lijing 52889 Add for Trunk */
    ULONG ulPhyInputIfIndex;    /* Trunk下的成员端口收到ARP请求后将端口的接口索引记录下来，
                                   保证ARP响应的报文从同一个成员端口发出 */

    ULONG ulSendAtIndex;
    ULONG ulQueueID;        /* 当前不支持MP板间捆绑，可以将QueID放到MBUF_S中 */
    /*ULONG ulPacketLength;*//*如果此值总等于mbuf中数据的长度，则可以去掉此域*/
    ULONG ulFlag;/*标志，各位的含义由宏MBUF_FLAG_XXXXXXXXXXXXXX定义*/

    ULONG ulPortIfIndex;   /*L2IF模块入端口接口索引*/
}MBUF_COMMON_INFO_S;

typedef struct tagMBufX25Info
{
    USHORT  usX25OutLCI;    /*出接口虚电路号*/
    UCHAR  ucX25InLCDIsXOT;    /*入接口虚电路类型是否为XOT*/
    UCHAR  ucX25OutLCDIsXOT;    /*出接口虚电路类型是否为XOT*/
    LONG  lX25OutSocketID;    /*出口为XOT时，出LCD的SocketID*/
    USHORT  usPktTyp;        /*X25分组的类型*/
    UCHAR   ucPadding[2];
    /*addition end for X25ENH*/

}MBUF_X25_INFO_S;

typedef struct tagMBufEthernetInfo
{
    UCHAR ucSourceMacAddress[8];/*ethernet*//*the excessive 2 bytes is only for byte alignment*/
    UCHAR ucDstMacAddress[8];
}MBUF_ETHERNET_INFO_S;

typedef struct tagMBufFrameRelayInfo
{
    ULONG ulFrInfo;

}MBUF_FRAME_RELAY_INFO_S;

typedef struct tagMBufATMInfo
{
    ULONG ulATMInfo;
    ULONG ulPhyInfo;
    ULONG ulVccIndex;
}MBUF_ATM_INFO_S;

typedef struct tagMBufPPPInfo
{
    USHORT usProtocol; /*报文的Ppp协议号*/
    USHORT usReserved;
}MBUF_PPP_INFO_S;

typedef struct tagMBufIpPacketInfo
{
    /*IP的信息,从IP包的各个域中获得*/
    UCHAR ucServiceType;/*the type of service domain in ip head, 其中包含precedence*/
    UCHAR ucIsFragment;/*is fragment or not */
    UCHAR ucProtocolId;/*the protocol in ip head, TCP UDP ICMP*/
    UCHAR ucReserve;/*for byte alignment*/
    ULONG ulSourceIpAddress;
    ULONG ulDestinationIpAddress;
    /*IP承载协议的信息，如果是IP包是片段，则下面两个域无意义，如果不是片段，则它们的含义如注释中所说明*/
    USHORT usSourcePortOrIcmpType;/*对TCP、UDP报文，是源端口号，对ICMP报文是type*/
    USHORT usDestinationPortOrIcmpCode;/*对TCP、UDP报文，是目的端口号，对ICMP报文是code*/

    ULONG ulLoopTimes;        /* 该IP报文在本机内部循环处理的次数, IP*/
    ULONG ulIpPktType;        /* 该报文是否是广播报文，在IP_forward和IP_Distrubute中使用 */
    ULONG ulNextHopIpAddress;/*下一跳的地址，从路由表中获得*//*ethernet*/
    ULONG ulRevBoardId;        /* 快速转发中使用,板间转发对端板号 */
    ULONG ulLenExpIcmpOption;   /*  保存ICMP选项长度  */
}MBUF_IP_PACKET_INFO_S;

#define MBUF_MACADDRLEN 6

typedef struct tagMBufIp6PacketInfo
{
    ULONG ulLoopTimes;      /* 该IP报文在本机内部循环处理的次数*/
    ULONG ulIpPktType;      /* 报文属性 */

    /*
    下一跳的结构应该是IN6ADDR_S,但是因为头文件引用的关系,
    定义后将导致原有的文件无法编译通过,只能定义一个相同的结构代替
    */
    /* Modified by z00208058/w00207740, u8定义冲突, 2012/5/8 */
    struct {
        UCHAR ucaddr[16];
    }stNextHopIpAddr;       /*下一跳的地址，从路由表中获得*/
    
    /* 链路层地址 */
    union
    {
        UCHAR szLinkEtherAddr[MBUF_MACADDRLEN]; /* physical地址 */
    }unLinkAddr;

    UCHAR ucServiceType;/* used by qos, be similar to the ipv4,IPv6报文通信流类型TrafficClass */
    /* UCHAR ucReserve; for future use and byte alignment */
    UCHAR ucHopLimit   ;/* ipv6 hoplimit信息,BFD支持IPv6的时候需要跳数 */

    UCHAR ucProtocolID;     /* IPv6报文携带的上层协议号, 由IANA统一编码: TCP: 6, UDP: 17, ICMP6: 58 */
    UCHAR ucReserve[3];     /* 预留未使用字段 */
}MBUF_IP6_PACKET_INFO_S;

typedef struct tagMBufMplsPacketInfo
{
    ULONG ulL3Info; /* record info about network layer */

    ULONG    ulVrfIndex;
}MBUF_MPLS_PACKET_INFO_S;

typedef struct tagMBufIpxPacketInfo
{
    ULONG ulTemp;
}MBUF_IPX_PACKET_INFO_S;

typedef struct tagMBUF_UserTagData/*this data type is public, can be used by user*/
{
    /*共有的信息*/
    MBUF_COMMON_INFO_S stCommonInfo;

    /*与物理层相关的信息，例如以太网的发送者的physical地址，X.25的线路号等*/
    ULONG ulPhysicalType;
    union
    {
        ULONG ulTemp;   /* 该字段已用于存放VLAN头信息 */
    }unPacketInfoRelevantToPhysical;

    /*与链路层相关的信息*/
    ULONG ulLinkType;/*X.25, ethernet*/
    union
    {
        MBUF_X25_INFO_S stX25Info;
        MBUF_ETHERNET_INFO_S stEthernetInfo;
        MBUF_FRAME_RELAY_INFO_S stFrameRelayInfo;
        MBUF_ATM_INFO_S stATMInfo;
        MBUF_PPP_INFO_S stPppInfo;
    }unPacketInfoRelevantToLink;

    MBUF_MPLS_PACKET_INFO_S stMplsPacketInfo;

    /*与网络层的信息*/
    ULONG ulNetworkType;/*IP, IPX，ARP,其他*//*ethernet*/
    union
    {
        MBUF_IP_PACKET_INFO_S stIpPacketInfo;
        MBUF_IPX_PACKET_INFO_S stIpxPacketInfo;

        MBUF_IP6_PACKET_INFO_S stIp6PacketInfo;
    }unPacketInfoRelevantToNetwork;
    /*module macro removed by Desh*/
    ULONG ulNatPtFlag; /*  to hold ipv6 natpt info */

    /*传输层相关的信息*/
    ULONG   ulAntiMultiFlag;

    UCHAR   aucSockAddr[36]; /*地址信息的最大长度不会超过36字节*/
    
    USHORT usVID;
    USHORT usPingMode;
    
    /* Add by z62474 for DCC */
    UCHAR   ucDccFlowID;             /* DCC报文流标记ID */
    UCHAR   ucDccFlag;               /* DCC 标记 */
    /* End*/

    UCHAR   ucUserSpecifyFlag;  /* 是否用户指定了下一跳或者出接口信息 */
    UCHAR   ucPad;
    ULONG   ulPrivateData[4];   /* 产品可使用的私用数据，具体内容由使用者定义 */
}MBUF_USERTAGDATA_S;

/*************************************************************************




                            PRIVATE SECTION



IMPORTANT

You can NOT use any of the following items!!!
**************************************************************************/

/*private data type------------------------------------------------------*/

typedef struct tagMBUF_DataBlockDescriptor/**/
{
    ULONG  ulState;
    ULONG  ulType;
    ULONG  ulOption;

    ULONG  ulDataBlockSource;/*DB的来源，详细解释见下宏定义*/
    UCHAR *pucSysBlockCtl;/*驱动DB的MBUF地址*/

    ULONG  ulDataLength;/*数据块中数据的长度，取值范围[0, ulDataBlockLength]*/
    UCHAR *pucData;/*数据块中数据的起始地址, [pucDataBlock, pucDataBlock + ulDataBlockLength]*/
    ULONG  ulDataBlockLength;/*数据块的总长度, 2048 或 4096 */
    UCHAR *pucDataBlock;/*数据块的起始地址， NULL表示无效，其他表示有效*/
    struct tagMBUF_DataBlockDescriptor * pstNextDataBlockDescriptor;/*下一个数据块描述符， NULL表示无效，其他表示有效*/
}MBUF_DATABLOCKDESCRIPTOR_S;/*数据块描述符数据结构*/

#define FILENAME_LEN 16
typedef struct tagMBuf
{
    ULONG ulState;
    struct tagMBuf * pstNextMBuf;/*下一个mbuf， NULL表示无效，其他表示有效*/
    ULONG ulTotalDataLength;/*mbuf中数据的总长度，其值为数据块描述符链中所有描述符的ulDataLength的和*/
    ULONG ulDataBlockNumber;/*mbuf中数据块的个数，其值为数据块描述符链中所有描述符的个数
                            （或数据块的个数，数据块的个数总等于数据块描述符的个数）*/

    /*
    other info about this packet such as QoS's PACKETINFO_S,
    fast switching info, etc.
    */
    MBUF_USERTAGDATA_S stUserTagData;

    /*如需要对MBUF中添加信息加在这下面*/
    ULONG ulHeadLenth;/*报文首部长度*/
    ULONG ulEntry;/* Head Cache结点的地址*/
    MBUF_DATABLOCKDESCRIPTOR_S stDataBlockDescriptor;/*第一个数据块描述符，是数据块描述符链表的第一个结点*/

    /* 与性能优化相关 */
    USHORT usPktType;
    USHORT usSocketID;

    CHAR  cFileName[FILENAME_LEN]; /*记录当前调用函数的文件名*/
    ULONG ulFileLine;              /*记录当前调用函数的行号*/
    ULONG ulTaskID;                /*记录当前调用任务ID*/
    ULONG ulModID;                 /*模块ID*/

    ULONG ulEncapType;             /* Eth报文封装类型: 目前只有Eth2/SNAP格式 */  

    USHORT usIpv6SourcePort;        /*对TCP、UDP报文，是源端口号，对ICMP6报文是type*/
    USHORT usIpv6DestinationPort;   /*对TCP、UDP报文，是目的端口号，对ICMP6报文是code*/
    ULONG ulIpVersion;             /*ip version*/
    ULONG ulTimeStampHigh;         /* 高字节时间戳 */
    ULONG ulTimeStampLow;         /* 低字节时间戳 */
    
    /*Added by zhoushisong202096, 更改TCP重组队列, 2013/11/5 */ 
    struct tagMBuf * pstPrevMBuf;/*上一个mbuf， NULL表示无效，其他表示有效*/        
    UCHAR *pu8NetLayerHeader;    /* 指向报文的网络层首部 */
    
    ULONG ulReserved[2];           /*保留为以后使用*/

    
}MBUF_S;/*mbuf的头标签数据结构*/
    

/*保存Mbuf相关的预配置参数值*/
typedef struct MbufCfgInfo
{
    ULONG ulHeadCacheNum;
    ULONG ulDBDCacheNum;
    ULONG ulDBCacheNum;
    ULONG ulHeadCacheMask;
    ULONG ulDBDCacheMask;
    ULONG ulDBCacheMask;
    ULONG ulCacheLock;
    /*Added by zhoushisong202096, 支持MBUF预留长度可扩展, 2013/11/25 */
    ULONG ulReservedExtHeadLength;
}MBUFCFGINFO_S;

/*获取MBUF的状态*/
typedef struct tagMbufStatusInfo
{
    ULONG ulHeadCacheNum;      /*MBUF Head预配置数量*/
    ULONG ulDBDCacheNum;       /*DBD总数*/
    ULONG ulDBCacheNum;        /*DB总数*/
    ULONG ulHeadCacheFreeNum;  /*未被使用的MBUF HEAD数量*/
    ULONG ulDBDCacheFreeNum;   /*未被使用DBD数量*/
    ULONG ulDBCacheFreeNum;    /*未被使用DB数量*/
}MBUFSTATUSINFO_S;

/*STRUCT<注册用户管理DB的钩子函数原型>*/
typedef struct tagTCPIP_USER_DB_HOOK
{
    USHORT usMBufDataBlockLength;  /*用户分配的DB块长度范围：2048~65535*/
    USHORT usRes; 
    VOID* (*AllocUserDB_HOOK_FUNC)(USHORT usLen); /*分配用户分配的DB，函数返回值即为分配的DB内存指针 */
    ULONG (*FreeUserDB_HOOK_FUNC)(VOID * pBuf); /*释放用户分配的DB */
    ULONG (*IncRefUserDB_HOOK_FUNC)(VOID * pBuf); /*增加 DB的引用计数，参考VOS_Mem_IncRef */
    ULONG (*DecRefUserDB_HOOK_FUNC)(VOID * pBuf); /*减少 DB的引用计数，参考VOS_Free中对引用计数的处理 */
    ULONG (*GetRefUserDB_HOOK_FUNC) (VOID * pBuf, ULONG * pulRetRef ); /*获取 DB的引用计数，参考VOS_Mem_GetRef */
}TCPIP_USER_DB_HOOK_S;

/* Added by z43740 for API整改:适配函数改为注册方式,2008/03/27 */
typedef ULONG (*FreeSysDB_HOOK_FUNC)(MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor);
typedef ULONG (*DupSysDB_HOOK_FUNC)(MBUF_DATABLOCKDESCRIPTOR_S * pstSrcDataBlockDescriptor,
                                    MBUF_DATABLOCKDESCRIPTOR_S * pstDstDataBlockDescriptor);
typedef ULONG (*GetSysDBRefCnt_HOOK_FUNC)(MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor,
                                          ULONG *pulCount);
typedef ULONG (*DecSysDBRefCnt_HOOK_FUNC)(MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor);
/* End of addition by z43740,2008/03/27 */


/*private data type------------------------------------------------------END*/


/*private macro----------------------------------------------------------*/
/*no parameters*/

#define MBUF_MBUF_SIZE ( sizeof(MBUF_S) )
#define MBUF_DATA_BLOCK_DESC_SIZE ( sizeof(MBUF_DATABLOCKDESCRIPTOR_S) )
#define MBUF_DATA_BLOCK2048_SIZE 2048
#define MBUF_DATA_BLOCK4096_SIZE 4096

#define MBUF_MAGIC_WORD                0x12345678

/*with parameters*/
#define MBUF_MIN(a,b) (((a) < (b)) ? (a) : (b))


/*private macro----------------------------------------------------------END*/


/*private function----------------------------------------------------------*/

/****************************************************************************
*    Func Name: MBUF_CreateDBDescriptorAndDB()
*  Description: to create a data block and a data block descriptor,
*               then link the data block to the data block descriptor.
*               The size of data block is as the ulDataBlockLength specified.
*        Input: ULONG ulDataBlockLength:数据块长度
*               ULONG ulType:数据块类型
*               ULONG ulModuleID:调用者的模块号
*       Output: 无
*       Return: NULL:失败
*               其它值:MBUF的DB Descriptor指针
*      Caution: this function assiged 5 items
*               pucDataBlock
*               pstNextDataBlockDescriptor(NULL)
*               ulDataBlockLength
*               ulType
*               ulOption(0)
*               remain the following items
*               pucData
*               ulDataLength
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
MBUF_DATABLOCKDESCRIPTOR_S * MBUF_CreateDBDescriptorAndDB(ULONG ulDataBlockLength, ULONG ulType, ULONG ulModuleID);
/****************************************************************************
*    Func Name: MBUF_PullUp()
*  Description: create a data block and data block descriptor, 
*               then move the first ulLength data to the data block,
*               then insert the data block and data block descriptor 
*               into the head of data block list
*        Input: MBUF_S * pstMBuf:MBUF
*               ULONG ulLength:the first ulLength data that need be moved to the data block
*               ULONG ulModuleID:模块号
*       Output: 无
*       Return: MBUF_OK:   成功
*               MBUF_FAIL: 失败
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
ULONG MBUF_PullUp(MBUF_S * pstMBuf, ULONG ulLength, ULONG ulModuleID);
/****************************************************************************
*    Func Name: MBUF_PrependDataBlock()
*  Description: create a data block and data block descriptor, 
*               then insert the data block and data block descriptor into the head of mbuf list
*        Input: MBUF_S * pstMBuf:MBUF
*               ULONG ulLength:长度
*               ULONG ulModuleID:模块号
*       Output: 无
*       Return: MBUF_OK:   成功
*               MBUF_FAIL: 失败
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
ULONG MBUF_PrependDataBlock(MBUF_S * pstMBuf, ULONG ulLength, ULONG ulModuleID);
/****************************************************************************
*    Func Name: MBUF_CutHeadInMultiDataBlock()
*  Description: cut the first ulLength data that may be in multiple data blocks of the pstMBuf
*        Input: MBUF_S * pstMBuf:MBUF
*               ULONG ulLength:长度
*       Output: 无
*       Return: 无
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
VOID MBUF_CutHeadInMultiDataBlock(MBUF_S * pstMBuf, ULONG ulLength);

/*******************************************************************************
*    Func Name: MBUF_DestroyFunc
* Date Created: 2009-02-25
*       Author: z00104207
*  Description: 为配合VR7C03 lib小型化需求，将MBUF_Destroy宏改成函数调用
*        Input: CHAR *szCurrentFileName:文件名
*               ULONG ulLine:           行号
*               MBUF_S *pMBuf:          MBUF指针
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-25   z00104207/l00111779     Create
*
*******************************************************************************/
VOID MBUF_DestroyFunc(CHAR *szCurrentFileName, ULONG ulLine, MBUF_S *pMBuf);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncUserMngDBHook
* Date Created: 2013-12-19
*       Author: lihaiming 00218630
*      Purpose: 获取用户管理 DB的引用计数
*  Description: 
*        Input: VOID * pBuf
*       Output: ULONG * pulRetRef: DB的引用计数
*       Return: 成功：VOS_OK
*               失败：VOS_ERR
*      Caution: 
*        Since: V300R002C00
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-19   lihaiming 00218630        Create
*
*******************************************************************************/
ULONG TCPIP_GetUserDBRef(VOID * pBuf, ULONG * pulRetRef );

/*private function----------------------------------------------------------END*/








/*************************************************************************




                                 PUBLIC SECTION



You can use the following items as the programmer manual described
**************************************************************************/


/*public macro----------------------------------------------------------*/
/*macro without parameters*/

/*DB的来源*/
#define MBUF_DATA_NORMAL 0/*DB是从协议栈申请的*/
#define MBUF_DATA_ETHDRV 1/*DB是从以太驱动申请的*/
#define MBUF_DATA_PPPDRV 2/*DB是从PPP驱动申请的*/
#define MBUF_DATA_USERMNG 3/*DB是用户申请的*/

#define MBUF_HEAD_CACHE_NUM         4096            /* MBUF Head缓冲个数 */
#define MBUF_HEAD_CACHE_MASK        (MBUF_HEAD_CACHE_NUM - 1)

#define MBUF_DBD_CACHE_NUM          4096            /* MBUF DBD缓冲个数  */
#define MBUF_DBD_CACHE_MASK         (MBUF_DBD_CACHE_NUM - 1)

#define MBUF_DB_CACHE_NUM           8192            /* MBUF DB缓冲个数   */
#define MBUF_DB_CACHE_MASK          (MBUF_DB_CACHE_NUM - 1)

#define MBUF_DEF_CACHE_NUM          128             /*默认MBUF CACHE个数*/

#define MBUF_FAIL ((ULONG) 1)/*接口操作失败*/
#define MBUF_OK   ((ULONG) 0)/*接口操作成功*/
#define MBUF_INPUT_NULL        ((ULONG) 2)/*mbuf接口入参为空*/
#define MBUF_DB_LENGTH_ERROR   ((ULONG) 3)/*mbuf接口入参DB长度错误*/
#define MBUF_INPUT_HOOK_NULL   ((ULONG) 4)/*mbuf接口入参DB长度错误*/


#define MBUF_TYPE_DATA     1
#define MBUF_TYPE_CONTROL  2
#define MBUF_TYPE_NAME     3
#define MBUF_TYPE_OOBDATA  4
#define MBUF_TYPE_SOOPTS   5

#define MBUF_TYPE_MPLS     8
#define MBUF_TYPE_MPLS_SW  9
#define MBUF_TYPE_MPLS_VPN 10

/* add magic number for mbuf */
#define MBUF_IDLE          0x49444C45  /* ASCII of "IDLE"*/
#define MBUF_BUSY          0x42555359  /* ASCII of "BUSY"*/

#define MBUF_MAX_MID         256    /*模块内存统计中允许的最大模块ID对应的数组索引*/

extern ULONG   gulMBufHeadCacheFreeNum;
extern ULONG   gulMBufHeadCacheFreeIndex;
extern ULONG   gulMBufHeadCacheAllocIndex;
extern ULONG   gulMbufHeadCacheFailedCount;
extern MBUF_S** gstMBufHeadCache;

extern ULONG   gulMBufDBDCacheFreeNum;
extern ULONG   gulMBufDBDCacheFreeIndex;
extern ULONG   gulMBufDBDCacheAllocIndex;
extern ULONG   gulMbufDBDCacheFailedCount;
extern MBUF_DATABLOCKDESCRIPTOR_S** gstMBufDBDCache;

extern ULONG   gulMBufDBCacheFreeNum;
extern ULONG   gulMBufDBCacheFreeIndex;
extern ULONG   gulMBufDBCacheAllocIndex;
extern ULONG   gulMbufDBCacheFailedCount;
extern UCHAR** gstMBufDBCache;

extern MBUFCFGINFO_S g_stMbufCfgInfo;

extern ULONG g_ulMbufStatByMID[MBUF_MAX_MID + 1];

/*Add for S-IP-002-MBUF.002 支持产品管理内存作为DB控制块*/
extern TCPIP_USER_DB_HOOK_S *g_pfTCPIPUserDBMng;
extern USHORT g_usMBufDataBlockLength;

/*******************************************************************************
*    Func Name: TCPIP_Safe_Mem_Set
* Date Created: 2014-12-13
*       Author: likaikun213099
*  Description: mem_set安全/非安全函数实现(Balong包括在了非安全分支)
*        Input: VOID *pDest:
*               ULONG ulDstMaxLen:
*               CHAR uChar:
*               ULONG ulCount:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-13   likaikun213099          Create
*
*******************************************************************************/
extern ULONG TCPIP_Safe_Mem_Set(VOID *pDest, ULONG ulDstMaxLen, CHAR uChar, ULONG ulCount);

/*******************************************************************************
*    Func Name: TCPIP_FreeSysDB
*  Description: 释放从驱动申请的DB
*        Input: MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor:要释放DB的DBD
*       Output: 
*       Return: VOS_ERR:失败
*               VOS_OK:释放成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2004-7-7     zhany hong yan(19316)   Create
*
*******************************************************************************/
extern ULONG TCPIP_FreeSysDB (MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor);
/*******************************************************************************
*    Func Name: MBUF_LOG_Info
*  Description: 提供给MBUF使用封装日志记录宏，以解决产品引用mbuf.h文件时对日志文件的依赖
*               注意:日志一般不允许封装,但此点特殊,所以要求日志的记录要达到各代码记录点
*        Input: ULONG ulCaseType:日志点记录处
*               MBUF_S *pstMbuf:MBUF指针
*               CHAR *cCurrentFileName:当前文件名
*               ULONG ulCurrentFileLine:当前文件行号
*               ULONG ulCurrentTaskId:当前任务ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-25   wuhailan                Create
*
*******************************************************************************/
extern VOID MBUF_LOG_Info (ULONG ulCaseType, MBUF_S *pstMbuf,
                           CHAR *cCurrentFileName, ULONG ulCurrentFileLine, ULONG ulCurrentTaskId);
/*******************************************************************************
*    Func Name: TCPIP_GetFileName
*  Description: 获取不带路径的文件名
*        Input: CHAR *pstFile:传入的待路径的文件名
*               ULONG ulstrMaxLen:存放返回文件名的空间大小,
*                                 拷贝的字符串长度只占ulstrMaxLen-1个字符，最后一个字符作为\0用
*       Output: CHAR *pstFileName:返回不带路径的文件名
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wuhailan                Create
*
*******************************************************************************/
extern VOID TCPIP_GetFileName(CHAR *pstFile, CHAR *pstFileName, ULONG ulstrMaxLen);
/*******************************************************************************
*    Func Name: MBUF_FreeMbuf
*  Description: 释放MBUF信息
*        Input: MBUF_S *pstMBuf:MBUF指针
*       Output: 
*       Return: 返回VOS_OK
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-05-17   wuhailan                Create
*
*******************************************************************************/
extern ULONG MBUF_FreeMbuf(MBUF_S *pstMBuf);

#if defined(TCPIP_DOPRA_V2) && defined(DOPRAV2)
extern VOID *VOS_Malloc( ULONG ulInfo, SIZE_T ulSize );
#else
extern VOID * VOS_Malloc( ULONG ulInfo, ULONG ulSize );
#endif

#ifndef PCLINT_FOR_VOS_MEM
#define PCLINT_FOR_VOS_MEM
#if defined(TCPIP_DOPRA_V2) && defined(DOPRAV2)
extern ULONG VOS_Mem_Copy(VOID * pDestPtr, const VOID * pSrcPtr, SIZE_T uvCopyLen);
extern ULONG VOS_Mem_Set( CHAR * pBufPtr, CHAR uChar, SIZE_T ulSetLen );
extern ULONG VOS_Mem_Zero( CHAR * pBufPtr, SIZE_T ulSetLen );
#else
extern ULONG VOS_Mem_Copy( VOID * pDestPtr,const VOID * pSrcPtr,ULONG ulCopyLen );
extern ULONG VOS_Mem_Set( CHAR * pBufPtr, CHAR uChar, ULONG ulSetLen );
extern ULONG VOS_Mem_Zero( CHAR * pBufPtr, ULONG ulSetLen );
#endif
#endif

extern ULONG VOS_Free( VOID *pBuf );
extern ULONG VOS_SplImp(LONG *plRetSpl);
extern ULONG VOS_SplX(LONG lSpl);

extern ULONG VOS_Mem_GetRef( VOID * pBuf, ULONG * pulRetRef );
extern ULONG VOS_T_GetSelfID( ULONG * pulTaskID );

extern VOID TCPIP_SchedPoint_Check_Delay(VOID);

/* macro with parameters */
/* Modified by likaikun213099, mbuf.h对外公开，安全编译宏在产品链接阶段找不到, 
   2014/12/13   问题单号:DTS2014121300931  */
#ifndef TCPIP_Mem_Set
#define TCPIP_Mem_Set(pDstPtr, uChar, ulSetLen)                 TCPIP_Safe_Mem_Set(pDstPtr, ulSetLen, uChar, ulSetLen)
#endif

#ifndef TCPIP_Mem_Copy
#define TCPIP_Mem_Copy(pDstPtr, dst_size, pSrcPtr, copy_size)   TCPIP_Safe_Mem_Copy(pDstPtr, dst_size, pSrcPtr, copy_size)
#endif
/*End of Modified by likaikun213099, 2014/12/13   问题单号:DTS2014121300931  */

/*采用预配置方式,用以判断是否需要对MBUF Cache进行共享数据互斥保护*/
#define MBUF_CACHE_LOCK(ulValue) \
{\
    if (g_stMbufCfgInfo.ulCacheLock != VRP_NO)\
    {\
        (VOID)VOS_SplImp(&(ulValue));\
    }\
}

#define MBUF_CACHE_UNLOCK(ulValue) \
{\
    if (g_stMbufCfgInfo.ulCacheLock != VRP_NO)\
    {\
        (VOID)VOS_SplX(ulValue);\
    }\
}

/*申请Mbuf头*/
#define MBUF_ALLOC_HEAD(pstMBufHead)\
{\
    LONG iFastMbufMask = 0;\
    /*gulMbufHeadAllocCount++;*/\
    MBUF_CACHE_LOCK(iFastMbufMask);\
    if ( gulMBufHeadCacheFreeNum > 0 )\
    {\
        (pstMBufHead) = gstMBufHeadCache[gulMBufHeadCacheAllocIndex]; \
        gstMBufHeadCache[gulMBufHeadCacheAllocIndex] = NULL; \
        gulMBufHeadCacheAllocIndex = (gulMBufHeadCacheAllocIndex + 1) & g_stMbufCfgInfo.ulHeadCacheMask;\
        gulMBufHeadCacheFreeNum--;\
        if(MBUF_IDLE != pstMBufHead->ulState)\
        {\
            MBUF_LOG_Info(6, 0, 0, 0, 0);\
            /*VOS_DBGASSERT(0);*/\
        }\
    }\
    else \
    {\
\
        ULONG ulMemInfo = 0;\
        ulMemInfo = TCPIP_GetMemInfo(MID_COMP_MBUF);\
        gulMbufHeadCacheFailedCount++;\
        pstMBufHead = (MBUF_S *)VOS_Malloc(ulMemInfo, MBUF_MBUF_SIZE);\
    }\
    if(NULL != pstMBufHead)\
    {\
        (VOID)TCPIP_Mem_Set((VOID *)pstMBufHead, 0, MBUF_MBUF_SIZE); \
        (pstMBufHead)->stDataBlockDescriptor.ulDataBlockSource = MBUF_DATA_NORMAL;\
        (pstMBufHead)->stDataBlockDescriptor.pucSysBlockCtl = NULL;\
        (pstMBufHead)->ulHeadLenth = 0;\
        (pstMBufHead)->ulEntry = NULL;\
\
        (pstMBufHead)->ulState = MBUF_BUSY;\
        (pstMBufHead)->stDataBlockDescriptor.ulState = MBUF_BUSY;\
    }\
    MBUF_CACHE_UNLOCK(iFastMbufMask);\
}

/*释放Mbuf头*/
#define MBUF_FREE_HEAD(pstMBufHead)\
{\
    LONG iFastMbufMask = 0;\
\
    if (pstMBufHead->ulState != MBUF_BUSY)\
    {\
        MBUF_LOG_Info(0, 0, 0, 0, 0);\
        /*VOS_DBGASSERT(0);*/\
    }\
    MBUF_CACHE_LOCK(iFastMbufMask);\
    pstMBufHead->ulState = MBUF_IDLE;\
    pstMBufHead->stDataBlockDescriptor.ulState = MBUF_IDLE;\
    if (gulMBufHeadCacheFreeNum >= g_stMbufCfgInfo.ulHeadCacheNum)\
    {\
        (VOID)VOS_Free(pstMBufHead);\
    }\
    else\
    {\
        gstMBufHeadCache[gulMBufHeadCacheFreeIndex] = (pstMBufHead); \
        gulMBufHeadCacheFreeIndex = (gulMBufHeadCacheFreeIndex + 1) & g_stMbufCfgInfo.ulHeadCacheMask; \
        gulMBufHeadCacheFreeNum++;\
    }\
    MBUF_CACHE_UNLOCK(iFastMbufMask);\
}

/*申请Mbuf DBD*/
#define MBUF_ALLOC_DBD(pstMBufDBD)\
{\
    LONG iFastMbufMask = 0;\
    MBUF_CACHE_LOCK(iFastMbufMask);\
    if ( gulMBufDBDCacheFreeNum > 0 )\
    {\
        (pstMBufDBD) = gstMBufDBDCache[gulMBufDBDCacheAllocIndex]; \
        gstMBufDBDCache[gulMBufDBDCacheAllocIndex] = NULL; \
        gulMBufDBDCacheAllocIndex = (gulMBufDBDCacheAllocIndex + 1) & g_stMbufCfgInfo.ulDBDCacheMask;\
        gulMBufDBDCacheFreeNum--;\
        if(MBUF_IDLE != pstMBufDBD->ulState)\
        {\
            MBUF_LOG_Info(7, 0, 0, 0, 0);\
            /*VOS_DBGASSERT(0);*/\
        }\
    }\
    else \
    {\
\
        ULONG ulMemInfo = 0;\
        ulMemInfo = TCPIP_GetMemInfo(MID_COMP_MBUF);\
        gulMbufDBDCacheFailedCount++;\
        pstMBufDBD = (MBUF_DATABLOCKDESCRIPTOR_S *)VOS_Malloc(ulMemInfo, MBUF_DATA_BLOCK_DESC_SIZE);\
    }\
    if((pstMBufDBD) != NULL)\
    {\
        (VOID)TCPIP_Mem_Set((VOID *)pstMBufDBD, 0, MBUF_DATA_BLOCK_DESC_SIZE); \
        (pstMBufDBD)->ulDataBlockSource = MBUF_DATA_NORMAL;\
        (pstMBufDBD)->pucSysBlockCtl = NULL;\
\
        (pstMBufDBD)->ulState = MBUF_BUSY;\
    }\
    MBUF_CACHE_UNLOCK(iFastMbufMask);\
}

/*释放Mbuf DBD*/
#define MBUF_FREE_DBD(pstMBufDBD)\
{\
    LONG iFastMbufMask = 0;\
\
    if (pstMBufDBD->ulState != MBUF_BUSY)\
    {\
        MBUF_LOG_Info(1, 0, 0, 0, 0);\
        /*VOS_DBGASSERT(0);*/\
    }\
    MBUF_CACHE_LOCK(iFastMbufMask);\
    pstMBufDBD->ulState = MBUF_IDLE;\
    if (gulMBufDBDCacheFreeNum >= g_stMbufCfgInfo.ulDBDCacheNum)\
    {\
        (VOID)VOS_Free(pstMBufDBD);\
    }\
    else\
    {\
        gstMBufDBDCache[gulMBufDBDCacheFreeIndex] = (pstMBufDBD);\
        gulMBufDBDCacheFreeIndex = (gulMBufDBDCacheFreeIndex + 1) & g_stMbufCfgInfo.ulDBDCacheMask; \
        gulMBufDBDCacheFreeNum++;\
    }\
    MBUF_CACHE_UNLOCK(iFastMbufMask);\
}

/*申请Mbuf DB*/ /* Modified for A82D22552 to got rid of calling VOS_Malloc2048 */
#define MBUF_ALLOC_DB(pstMBufDB, ulDataBlockSource) \
{\
    LONG iFastMbufMask = 0;\
    MBUF_CACHE_LOCK(iFastMbufMask);\
    if ( NULL != g_pfTCPIPUserDBMng) \
    {\
        (pstMBufDB) = g_pfTCPIPUserDBMng->AllocUserDB_HOOK_FUNC(g_usMBufDataBlockLength);\
        if(NULL != (pstMBufDB))\
        {\
             ulDataBlockSource = MBUF_DATA_USERMNG;\
        }\
    }\
    else if ( gulMBufDBCacheFreeNum > 0 )\
    {\
        (pstMBufDB) = gstMBufDBCache[gulMBufDBCacheAllocIndex]; \
        gstMBufDBCache[gulMBufDBCacheAllocIndex] = NULL; \
        gulMBufDBCacheAllocIndex = (gulMBufDBCacheAllocIndex + 1) & g_stMbufCfgInfo.ulDBCacheMask;\
        gulMBufDBCacheFreeNum--;\
    }\
    else \
    {\
\
        ULONG ulMemInfo = 0;\
        ulMemInfo = TCPIP_GetMemInfo(MID_COMP_MBUF);\
        gulMbufDBCacheFailedCount++;\
        pstMBufDB = (UCHAR *)VOS_Malloc(ulMemInfo, MBUF_DATA_BLOCK2048_SIZE);\
    }\
    MBUF_CACHE_UNLOCK(iFastMbufMask);\
}

/*释放Mbuf DB*/
#define MBUF_FREE_DB(pstMBufDBD)\
{\
    if((pstMBufDBD)->ulDataBlockSource == MBUF_DATA_USERMNG)\
    {\
        (VOID)g_pfTCPIPUserDBMng->FreeUserDB_HOOK_FUNC((pstMBufDBD)->pucDataBlock);\
    }\
    else if((pstMBufDBD)->ulDataBlockSource != MBUF_DATA_NORMAL)\
    {\
        (VOID)TCPIP_FreeSysDB((pstMBufDBD));\
    }\
    else\
    {\
        LONG iFastMbufMask = 0;\
        MBUF_CACHE_LOCK(iFastMbufMask);\
        if ((gulMBufDBCacheFreeNum >= g_stMbufCfgInfo.ulDBCacheNum)\
            || (MBUF_DATA_BLOCK2048_SIZE != (pstMBufDBD)->ulDataBlockLength))\
        {\
            (VOID)VOS_Free((pstMBufDBD)->pucDataBlock);\
        }\
        else\
        {\
            ULONG ulFastMbufRetVal = 0;\
            ULONG ulFastMbufReferenceCount = 0;\
            ulFastMbufRetVal = VOS_Mem_GetRef((pstMBufDBD)->pucDataBlock, & ulFastMbufReferenceCount);\
            if(ulFastMbufRetVal != 0)\
            {\
                ulFastMbufReferenceCount = 2;\
            }\
            if (1 == ulFastMbufReferenceCount)\
            {\
                gstMBufDBCache[gulMBufDBCacheFreeIndex] = ((pstMBufDBD)->pucDataBlock);\
                gulMBufDBCacheFreeIndex = (gulMBufDBCacheFreeIndex + 1) & g_stMbufCfgInfo.ulDBCacheMask; \
                gulMBufDBCacheFreeNum++;\
            }\
            else\
            {\
                (VOID)VOS_Free((pstMBufDBD)->pucDataBlock);\
            }\
        }\
        MBUF_CACHE_UNLOCK(iFastMbufMask);\
    }\
}

/* Added by X36317, 新增为支持ARM CPU字节对齐特性使用的公共宏, 2006/5/9 */
#ifdef TCPIP_SUPPORT_ARMCPU
/*将Mbuf报文交给上层协议时需调用此宏。此宏的作用是判断报文的起始地址是否4字节的整数倍，
如果不是，则需要新申请一个DB，将原来报文Mbuf内容Copy到新的DB中*/
#define MBUF_ADJUST_DB(pMBuf)\
{\
    ULONG ulReserveLen = 0;\
    UCHAR *pucData = NULL;\
    UCHAR *pucDataBlock = NULL;\
    UCHAR *pucNewDataBlock = NULL;\
    if (((pMBuf) != NULL) && ((pMBuf)->stDataBlockDescriptor.pucDataBlock != NULL))\
    {\
        pucData = MBUF_MTOD((pMBuf), UCHAR *);\
        if (((ULONG)pucData & 0x00000003) != 0)\
        {\
            pucDataBlock = (pMBuf)->stDataBlockDescriptor.pucDataBlock;\
            ulReserveLen = (ULONG)(pucData - pucDataBlock); \
            MBUF_ALLOC_DB(pucNewDataBlock, (pMBuf)->stDataBlockDescriptor.ulDataBlockSource);\
            if (pucNewDataBlock != NULL)\
            {\
                ulReserveLen -= (ulReserveLen & 0x00000003);\
                (VOID)TCPIP_Mem_Copy(pucNewDataBlock + ulReserveLen, (pMBuf)->stDataBlockDescriptor.ulDataLength,pucData, (pMBuf)->stDataBlockDescriptor.ulDataLength);\
                MBUF_FREE_DB(&((pMBuf)->stDataBlockDescriptor));\
                (pMBuf)->stDataBlockDescriptor.pucDataBlock = pucNewDataBlock;\
                (pMBuf)->stDataBlockDescriptor.pucData = pucNewDataBlock + ulReserveLen;\
                (pMBuf)->stDataBlockDescriptor.ulDataBlockSource = MBUF_DATA_NORMAL;\
                (pMBuf)->stDataBlockDescriptor.pucSysBlockCtl = NULL;\
                (pMBuf)->stDataBlockDescriptor.ulDataBlockLength = g_usMBufDataBlockLength;\
            }\
         }\
     }\
}
#else /*如果不是ARM CPU，则此宏不需要做任何操作*/
#define MBUF_ADJUST_DB(pMBuf)
#endif


#define MBUF_CREATE_BY_DATA_BLOCK(pstMBufM, pucDataBlockM, ulDataBlockLengthM,    pucDataM, \
    ulDataLengthM, ulReceiveIfnetIndexM, ulModuleIDM)\
{\
    MBUF_ALLOC_HEAD(pstMBufM);\
    if( (pstMBufM) != NULL)\
    {\
        (pstMBufM)->stDataBlockDescriptor.pstNextDataBlockDescriptor = NULL;\
        (pstMBufM)->stDataBlockDescriptor.pucDataBlock = (pucDataBlockM);\
        (pstMBufM)->stDataBlockDescriptor.ulDataBlockLength = (ulDataBlockLengthM);\
        (pstMBufM)->stDataBlockDescriptor.pucData = (pucDataM);\
        (pstMBufM)->stDataBlockDescriptor.ulDataLength = (ulDataLengthM);\
        (pstMBufM)->stDataBlockDescriptor.ulDataBlockSource = MBUF_DATA_NORMAL;\
        (pstMBufM)->stDataBlockDescriptor.pucSysBlockCtl = NULL;\
        (pstMBufM)->stDataBlockDescriptor.ulType = MBUF_TYPE_DATA;\
        (pstMBufM)->stDataBlockDescriptor.ulOption = 0;\
        \
        (VOID)TCPIP_Mem_Set( (VOID *) (& pstMBufM->stUserTagData), 0 , sizeof(MBUF_USERTAGDATA_S));\
        (pstMBufM)->ulHeadLenth = 0;\
        (pstMBufM)->ulEntry = NULL;\
        (pstMBufM)->ulTotalDataLength = (ulDataLengthM);\
        (pstMBufM)->ulDataBlockNumber = 1;\
        (pstMBufM)->stUserTagData.stCommonInfo.ulReceiveIfnetIndex = (ulReceiveIfnetIndexM);\
        (pstMBufM)->pstNextMBuf = NULL;\
        \
        if (((ulModuleIDM) >= MID_COMP_BASE) && ((ulModuleIDM) <= (MID_COMP_BASE + 0x00FF0000)))\
        {\
            ULONG ulMidIndex = ((ulModuleIDM) - MID_COMP_BASE) >> 16;\
            (pstMBufM)->ulModID = (ulModuleIDM);\
            g_ulMbufStatByMID[ulMidIndex]++; \
        }\
        else\
        {\
            (pstMBufM)->ulModID = 0;\
            g_ulMbufStatByMID[MBUF_MAX_MID]++;\
        }\
    }\
}


/*此宏用来Mbuf切头*/
#define MBUF_CUT_HEAD(pstMBufM, ulLengthM)\
{\
    if( (pstMBufM) != NULL )\
    {\
        if( (pstMBufM)->stDataBlockDescriptor.ulDataLength >= (ulLengthM) )\
        {\
            (pstMBufM)->stDataBlockDescriptor.pucData += (ulLengthM);\
            (pstMBufM)->stDataBlockDescriptor.ulDataLength -= (ulLengthM);\
            (pstMBufM)->ulTotalDataLength -= (ulLengthM);\
        }\
        else\
        {\
            MBUF_CutHeadInMultiDataBlock( (pstMBufM), (ulLengthM) );\
        }\
    }\
}

/*此宏用来使Mbuf指定长度内容连续*/
#define MBUF_MAKE_MEMORY_CONTINUOUS(pstMBufM, ulLengthM, ulModuleIDM, ulResultM) \
{\
    if( (pstMBufM) != NULL )\
    {\
        if( (pstMBufM)->stDataBlockDescriptor.ulDataLength < (ulLengthM) )\
        {\
            (ulResultM) = MBUF_PullUp( (pstMBufM), (ulLengthM), (ulModuleIDM) );\
        }\
        else\
        {\
            (ulResultM) = MBUF_OK;\
        }\
    }\
    else\
    {\
        (ulResultM) = MBUF_FAIL;\
    }\
}

/*此宏用来使Mbuf向前扩展一定长度*/
/*the ulLengthM must <= 2048*/
#define MBUF_PREPEND_MEMORY_SPACE(pstMBufM, ulLengthM, ulModuleIDM, ulResultM)\
{\
    /*modify by w62223 for coverity warning-type:UNINIT*/ \
     ULONG ulReferenceCount = 0;\
     MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor;\
     \
     if( (pstMBufM) != NULL)    \
     {\
        pstDataBlockDescriptor = &( (pstMBufM)->stDataBlockDescriptor );\
        if (MBUF_DATA_USERMNG == pstDataBlockDescriptor->ulDataBlockSource)\
        {\
            if(TCPIP_GetUserDBRef(pstDataBlockDescriptor->pucDataBlock, &ulReferenceCount) != 0)\
            {\
                ulReferenceCount = 2;\
            }\
        }\
        else if (pstDataBlockDescriptor->ulDataBlockSource == MBUF_DATA_NORMAL)\
        {\
            if (VOS_Mem_GetRef(pstDataBlockDescriptor->pucDataBlock, &ulReferenceCount) != 0)\
            {\
               ulReferenceCount = 2;\
            }\
        }\
        else\
        {\
            if (TCPIP_GetSysDBRefCnt(pstDataBlockDescriptor, &ulReferenceCount) != 0)\
            {\
                ulReferenceCount = 2;\
            }\
        }\
        if(ulReferenceCount == 1 \
            && (ULONG) (pstDataBlockDescriptor->pucData - pstDataBlockDescriptor->pucDataBlock) >= (ulLengthM) )\
        {\
            pstDataBlockDescriptor->pucData -= (ulLengthM);\
            pstDataBlockDescriptor->ulDataLength += (ulLengthM);\
            (pstMBufM)->ulTotalDataLength += (ulLengthM);\
            (ulResultM) = MBUF_OK;\
        }\
        else\
        {\
            (ulResultM) = MBUF_PrependDataBlock( (pstMBufM), (ulLengthM), (ulModuleIDM) );\
        }\
    }\
    else\
    {\
        (ulResultM) = MBUF_FAIL;\
    }\
}


#define MBUF_GET_DATA_BLOCK_DESC(pstMBufM) ( & ( (pstMBufM)->stDataBlockDescriptor) )


#define MBUF_GET_DATA_BLOCK_DESC_INFO(pstDataBlockDescriptorM, pucDataM, ulDataLengthM, pstNextDataBlockDescriptorM)\
{\
    (pucDataM) = (pstDataBlockDescriptorM)->pucData;\
    (ulDataLengthM) = (pstDataBlockDescriptorM)->ulDataLength;\
    (pstNextDataBlockDescriptorM) = (pstDataBlockDescriptorM)->pstNextDataBlockDescriptor;\
}

#define MBUF_MTOD(pstMBufM, DataTypeM) ( (DataTypeM)  (pstMBufM)->stDataBlockDescriptor.pucData )

#define MBUF_GET_PTR_NEXT_MBUF(pstMBufM) ( (pstMBufM)->pstNextMBuf )
#define MBUF_ASSIGN_PTR_NEXT_MBUF(pstMBufM, pstNextMBufM) ((pstMBufM)->pstNextMBuf = (pstNextMBufM))

#define MBUF_GET_TOTAL_DATA_LENGTH(pstMBufM) ( (pstMBufM)->ulTotalDataLength )
#define MBUF_GET_DATA_BLOCK_NUMBER(pstMBufM) ( (pstMBufM)->ulDataBlockNumber )

#define MBUF_GET_DATA_BLOCK_DESC_TYPE(pstDataBlockDescriptorM) ((pstDataBlockDescriptorM)->ulType)
#define MBUF_ASSIGN_DATA_BLOCK_DESC_TYPE(pstDataBlockDescriptorM, ulTypeM) ((pstDataBlockDescriptorM)->ulType = (ulTypeM))

#define MBUF_GET_DATA_BLOCK_DESC_OPTION(pstDataBlockDescriptorM) ((pstDataBlockDescriptorM)->ulOption)
#define MBUF_SET_DATA_BLOCK_DESC_OPTION(pstDataBlockDescriptorM, ulOptionM) ((pstDataBlockDescriptorM)->ulOption |= (ulOptionM))
#define MBUF_CLEAR_DATA_BLOCK_DESC_OPTION(pstDataBlockDescriptorM, ulOptionM) ((pstDataBlockDescriptorM)->ulOption &= (~(ulOptionM)))
#define MBUF_GET_NONZERO_DATA_BLOCK_NUMBER(pstMBufM, ulNonzeroDataBlockNumberM)\
{\
    MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor;\
    \
    (ulNonzeroDataBlockNumberM) = 0;\
    for(pstDataBlockDescriptor = MBUF_GET_DATA_BLOCK_DESC(pstMBufM);\
        pstDataBlockDescriptor != NULL;\
        pstDataBlockDescriptor = pstDataBlockDescriptor->pstNextDataBlockDescriptor)\
    {\
        if(pstDataBlockDescriptor->ulDataLength != 0)\
        {\
            (ulNonzeroDataBlockNumberM) ++;\
        }\
    }\
}

/*
下面的宏用于释放一个MBUF链,
目前MBUF中没有相应的宏,MBUF_Destroy只释放一个MBUF,以后应将这个宏加到MBUF模块中
*/
#define FREE_MBUF_CHAIN(pstMBuf) \
{ \
    MBUF_S *pTmpMBuf = pstMBuf; \
    \
    while (NULL != pTmpMBuf) \
    { \
        pstMBuf = MBUF_GET_PTR_NEXT_MBUF(pTmpMBuf); \
        MBUF_Destroy(pTmpMBuf); \
        pTmpMBuf = pstMBuf; \
    } \
}

#define MBUF_SET_HEADLENTH(pMbuf, ulLenth) ((pMbuf)->ulHeadLenth = (ulLenth))
#define MBUF_GET_HEADLENTH(pMbuf)  ((pMbuf)->ulHeadLenth)
#define MBUF_ADD_HEADLENTH(pMbuf, ulLenth) ((pMbuf)->ulHeadLenth += (ulLenth))

/*public macro----------------------------------------------------------END*/



/*public function---------------------------------------------------------------------*/

/****************************************************************************
*    Func Name: MBUF_CreateByCopyBuffer()
*  Description: 通过拷贝buffer创建MBUF
*        Input: ULONG ulReserveHeadSpace:保留的头空间
*               ULONG ulLength:长度
*               UCHAR * pucBuffer:缓冲区
*               ULONG ulType:类型
*               ULONG ulModuleID:模块号,暂未用
*       Output: 无
*       Return: NULL:失败
*               其它值:创建的MBUF
*      Caution: even if both ulReserveHeadSpace and ulLength are 0, 
*               this function will create a DB
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
MBUF_S * MBUF_CreateByCopyBuffer(ULONG ulReserveHeadSpace, ULONG ulLength, UCHAR * pucBuffer, ULONG ulType, ULONG ulModuleID);
/****************************************************************************
*    Func Name: MBUF_CreateForControlPacket()
*  Description: 创建一个MBuf(不含数据)
*        Input: ULONG ulReserveHeadSpace:保留的头空间
*               ULONG ulLength:长度
*               ULONG ulType:类型
*               ULONG ulModuleID:模块号,暂未用
*       Output: 无
*       Return: NULL:失败
*               其它值:创建的MBUF
*      Caution: even if both ulReserveHeadSpace and ulLength are 0, 
*               this function will create a DB
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
MBUF_S * MBUF_CreateForControlPacket(ULONG ulReserveHeadSpace, ULONG ulLength, ULONG ulType, ULONG ulModuleID);
/****************************************************************************
*    Func Name: MBUF_CreateBySysBuffer()
*  Description: 使用传进来带数据的驱动DB构造一个MBUF
*        Input: UCHAR * pucBuffer:驱动DB的地址
*               ULONG ulLength:驱动DB数据长度
*               ULONG ulDBLenth:驱动DB的长度
*               UCHAR *pucCtl:驱动DB的MBUF地址
*               ULONG ulDataSource:驱动DB的来源,1 --以太驱动2--ppp驱动
*               ULONG ulType:DB数据的类型
*               ULONG ulModuleID:模块号,暂未用
*       Output: 无
*       Return: NULL:失败
*               其它值:创建的MBUF
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
MBUF_S * MBUF_CreateBySysBuffer(UCHAR * pucBuffer, ULONG ulLength, ULONG ulDBLenth,\
                                UCHAR *pucCtl, ULONG ulDataSource, ULONG ulType, ULONG ulModuleID);

/****************************************************************************
*    Func Name: MBUF_CopyDataFromBufferToMBuf()
*  Description: 从buffer拷贝数据到MBUF
*        Input: MBUF_S * pstMBuf: Mbuf指针
*               ULONG ulOffset:   偏移量
*               ULONG ulLength:   拷贝长度
*               UCHAR * pucBuffer:拷贝到的buf
*               ULONG ulModuleID: 模块ID
*       Output: 无
*       Return: MBUF_OK:   成功
*               MBUF_FAIL: 失败
*      Caution: this function can deal with the mbuf whose first DB does not exist
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
ULONG MBUF_CopyDataFromBufferToMBuf(MBUF_S * pstMBuf, ULONG ulOffset, ULONG ulLength, UCHAR * pucBuffer, ULONG ulModuleID);
/****************************************************************************
*    Func Name: MBUF_CopyDataFromMBufToBuffer()
*  Description: 从MBUF拷贝数据到buffer
*        Input: MBUF_S * pstMBuf:MBUF指针
*               ULONG ulOffset:偏移量
*               ULONG ulLength:长度
*               UCHAR * pucBuffer:buffer
*       Output: 无
*       Return: MBUF_OK:   成功
*               MBUF_FAIL: 失败
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
ULONG MBUF_CopyDataFromMBufToBuffer(MBUF_S * pstMBuf, ULONG ulOffset, ULONG ulLength, UCHAR * pucBuffer);
/****************************************************************************
*    Func Name: MBUF_ReferenceCopy()
*  Description: MBUF引用拷贝
*        Input: MBUF_S * pstMBuf:MBUF
*               ULONG ulOffset:偏移量
*               ULONG ulLength:长度
*               ULONG ulModuleID:模块号
*       Output: 无
*       Return: NULL:失败
*               其它值:拷贝创建的MBUF
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
MBUF_S * MBUF_ReferenceCopy(MBUF_S * pstMBuf, ULONG ulOffset, ULONG ulLength, ULONG ulModuleID);
/****************************************************************************
*    Func Name: MBUF_RawCopy()
*  Description: MBUF 真实拷贝
*        Input: MBUF_S * pstMBuf:MBUF
*               ULONG ulOffset:偏移量
*               ULONG ulLength:长度
*               ULONG ulReserveHeadSpace:保留头空间
*               ULONG ulModuleID:模块号
*       Output: 无
*       Return: NULL:失败
*               其它值:创建的MBUF
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
MBUF_S * MBUF_RawCopy(MBUF_S * pstMBuf, ULONG ulOffset, ULONG ulLength, ULONG ulReserveHeadSpace, ULONG ulModuleID);

/****************************************************************************
*    Func Name: MBUF_Concatenate()
*  Description: 两个MBUF Concatenate
*        Input: MBUF_S * pstDestinationMBuf:目的MBUF
*               MBUF_S * pstSourceMBuf:源MBUF
*               ULONG ulModuleID:模块号,暂未用
*       Output: 无
*       Return: MBUF_OK:   成功
*               MBUF_FAIL: 失败
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
ULONG MBUF_Concatenate(MBUF_S * pstDestinationMBuf, MBUF_S * pstSourceMBuf, ULONG ulModuleID);/*when ok, pstSourceMBuf is NOT valid any more*/
/****************************************************************************
*    Func Name: MBUF_NeatConcatenate_Chain()
*  Description: 把控制信息的mbuf链组成一个mbuf;
*        Input: MBUF_S *pstMbufHead:指向mbuf链的头指针
*               ULONG ulModuleID:模块号
*       Output: 无
*       Return: 0:成功
*               1:失败
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
ULONG MBUF_NeatConcatenate_Chain(MBUF_S *pstMbufHead, ULONG ulModuleID);
/****************************************************************************
*    Func Name: MBUF_Fragment()
*  Description: MBUF分片
*        Input: MBUF_S * pstMBuf:MBUF
*               ULONG ulLength:长度
*               ULONG ulModuleID:模块号
*       Output: 无
*       Return: NULL:空
*               其它值:分片后的MBUF
*      Caution: return surplus, pstMBuf store the first ulLength data
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
MBUF_S * MBUF_Fragment(MBUF_S * pstMBuf, ULONG ulLength, ULONG ulModuleID);/*return the surplus data, pstMBuf is the first ulLength data*/

/****************************************************************************
*    Func Name: MBUF_CutAndFreeHead()
*  Description: MBUF砍头并释放
*        Input: MBUF_S * pstMBuf:MBUF
*               ULONG ulLength:长度
*       Output: 无
*       Return: MBUF_OK:   成功
*               MBUF_FAIL: 失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
ULONG MBUF_CutAndFreeHead(MBUF_S * pstMBuf, ULONG ulLength);
/****************************************************************************
*    Func Name: MBUF_CutPart()
*  Description: MBUF砍掉部分
*        Input: MBUF_S * pstMBuf:MBUF
*               ULONG ulOffset:偏移量
*               ULONG ulLength:长度
*       Output: 无
*       Return: MBUF_OK:   成功
*               MBUF_FAIL: 失败
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
ULONG MBUF_CutPart(MBUF_S * pstMBuf, ULONG ulOffset, ULONG ulLength);
/****************************************************************************
*    Func Name: MBUF_CutTail()
*  Description: cut and free tail
*        Input: MBUF_S * pstMBuf:MBUF
*               ULONG ulLength:长度
*       Output: 无
*       Return: MBUF_OK:   成功
*               MBUF_FAIL: 失败
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
ULONG MBUF_CutTail(MBUF_S * pstMBuf, ULONG ulLength);

/****************************************************************************
*    Func Name: MBUF_AppendMemorySpace()
*  Description: MBUF添加内存空间
*        Input: MBUF_S * pstMBuf:MBUF
*               ULONG ulLength:长度
*               ULONG ulModuleID:模块号
*       Output: 无
*       Return: NULL:失败
*               其它值:增加的数据块地址
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
UCHAR * MBUF_AppendMemorySpace(MBUF_S * pstMBuf, ULONG ulLength, ULONG ulModuleID);
/****************************************************************************
*    Func Name: MBUF_AssignZero()
*  Description: MBUF内容清0
*        Input: MBUF_S * pstMBuf:MBUF
*       Output: 无
*       Return: MBUF_OK:   成功
*               MBUF_FAIL: 失败
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
ULONG MBUF_AssignZero(MBUF_S * pstMBuf);

/****************************************************************************
*    Func Name: MBUF_ReferenceCopyByDescriptor()
*  Description: 根据Descriptor引用拷贝MBUF
*        Input: MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor:数据块
*               ULONG ulOffset:偏移量
*               ULONG ulLength:长度
*               ULONG ulModuleID:模块号,暂未用
*       Output: 无
*       Return: NULL:失败
*               其它值:创建的MBUF
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
MBUF_S * MBUF_ReferenceCopyByDescriptor(MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor,  ULONG ulOffset, ULONG ulLength,  ULONG ulModuleID);

/****************************************************************************
*    Func Name: MBUF_NeatConcatenate()
*  Description: MBUF Neat Concatenate
*        Input: MBUF_S * pstDestinationMBuf:目的MBUF
*               MBUF_S * pstSourceMBuf:源MBUF
*               ULONG ulModuleID:模块号，暂未用
*       Output: MBUF_DATABLOCKDESCRIPTOR_S ** ppstLastDataBlockDescriptor:数据块
*       Return: MBUF_OK:   成功
*               MBUF_FAIL: 失败
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
ULONG MBUF_NeatConcatenate(MBUF_S * pstDestinationMBuf, MBUF_S * pstSourceMBuf, MBUF_DATABLOCKDESCRIPTOR_S ** ppstLastDataBlockDescriptor, ULONG ulModuleID);

/****************************************************************************
*    Func Name: MBUF_RegMbufCfgInfo()
*  Description: 注册MBUF配置参数的函数
*        Input: MBUFCFGINFO_S *pstMbufCfgInfo:配置参数集合
*       Output: 无
*       Return: MBUF_OK:   成功
*               MBUF_FAIL: 失败
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
ULONG MBUF_RegMbufCfgInfo(MBUFCFGINFO_S *pstMbufCfgInfo);
/*******************************************************************************
*    Func Name: MBUF_GetMbufStatusInfo
*  Description: 获取MBUF的状态信息
*        Input: 
*       Output: MBUF_STATUS_S: *pstMbufStatus mbuf状态
*       Return: MBUF_OK 成功
*               MBUF_FAIL 参数错误
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-11   mafeng 59090            Create
*
*******************************************************************************/
ULONG MBUF_GetMbufStatusInfo(MBUFSTATUSINFO_S* pstMbufStatus);

/* Added by z43740 for API整改:适配函数改为注册方式,2008/03/27 */
/*******************************************************************************
*    Func Name: TCPIP_RegFuncFreeSysDBHook
*  Description: 注册释放系统DB的函数指针
*        Input: FreeSysDB_HOOK_FUNC pfHookFunc:函数指针
*       Output: 
*       Return: VOS_OK      成功
*               VOS_ERR     函数指针为空
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-27   zhoutong(43740)         Create
*
*******************************************************************************/
ULONG TCPIP_RegFuncFreeSysDBHook(FreeSysDB_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncDupSysDBHook
*  Description: 注册赋值系统DB的函数指针
*        Input: DupSysDB_HOOK_FUNC pfHookFunc:函数指针
*       Output: 
*       Return: VOS_OK      成功
*               VOS_ERR     函数指针为空
*      Caution: 如果系统DB引用计数大于0，需采用reference copy并增加引用计数
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-27   zhoutong(43740)         Create
*
*******************************************************************************/
ULONG TCPIP_RegFuncDupSysDBHook(DupSysDB_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetSysDBRefCntHook
*  Description: 注册获取系统DB引用计数的函数指针
*        Input: GetSysDBRefCnt_HOOK_FUNC pfHookFunc:函数指针
*       Output: 
*       Return: VOS_OK      成功
*               VOS_ERR     函数指针为空
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-27   zhoutong(43740)         Create
*
*******************************************************************************/
ULONG TCPIP_RegFuncGetSysDBRefCntHook(GetSysDBRefCnt_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncDecSysDBRefCntHook
*  Description: 注册减少系统DB的引用计数的函数指针
*        Input: DecSysDBRefCnt_HOOK_FUNC pfHookFunc:函数指针
*       Output: 
*       Return: VOS_OK      成功
*               VOS_ERR     函数指针为空
*      Caution: 在引用计数为0时，需要释放系统DB
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-27   zhoutong(43740)         Create
*
*******************************************************************************/
ULONG TCPIP_RegFuncDecSysDBRefCntHook(DecSysDBRefCnt_HOOK_FUNC pfHookFunc);
/* End of addition by z43740,2008/03/27 */

/*******************************************************************************
*    Func Name: TCPIP_RegFuncUserMngDBHook
* Date Created: 2013-12-19
*       Author: lihaiming 00218630
*      Purpose: 注册用户管理DB的钩子
*  Description: 
*        Input: TCPIP_USER_DB_HOOK_S *pstHookFunc 钩子函数
*                                       
*       Output: 
*       Return: 成功：VOS_OK
*               失败：VOS_ERR
*      Caution: 需要在协议栈初始化之前注册
*        Since: V300R002C00
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-19   lihaiming 00218630        Create
*
*******************************************************************************/
ULONG TCPIP_RegFuncUserMngDBHook(TCPIP_USER_DB_HOOK_S *pstHookFunc);

/*public function---------------------------------------------------------------------END*/
/****************************************************************************************



                       mbuf queue interface


*****************************************************************************************/
typedef struct tagMBufQueue
{
    MBUF_S * pstHeadMBuf;
    MBUF_S * pstTailMBuf;
    ULONG ulCurrentLength;
    ULONG ulMaxLength;
}MBUF_QUEUE_S;

#define MBUF_QUE_INIT(pstMBufQueueM, ulMaxLengthM)\
{\
    (pstMBufQueueM)->pstHeadMBuf = NULL;\
    (pstMBufQueueM)->pstTailMBuf = NULL;\
    (pstMBufQueueM)->ulCurrentLength = 0;\
    (pstMBufQueueM)->ulMaxLength = (ulMaxLengthM);\
}

#define MBUF_QUE_NOT_EMPTY(pstMBufQueueM) ( (pstMBufQueueM)->ulCurrentLength )
#define MBUF_QUE_IS_FULL(pstMBufQueueM) ( (pstMBufQueueM)->ulCurrentLength >=  (pstMBufQueueM)->ulMaxLength )
#define MBUF_QUE_ENQUEUE(pstMBufQueueM, pstMBufM)\
{\
    MBUF_ASSIGN_PTR_NEXT_MBUF( (pstMBufM), NULL);\
    if( (pstMBufQueueM)->pstTailMBuf != NULL)/*queue is NOT empty*/\
    {\
        MBUF_ASSIGN_PTR_NEXT_MBUF( (pstMBufQueueM)->pstTailMBuf, (pstMBufM) );\
    }\
    else/*queue is empty*/\
    {\
        (pstMBufQueueM)->pstHeadMBuf = (pstMBufM);\
    }\
    (pstMBufQueueM)->pstTailMBuf = (pstMBufM);\
    (pstMBufQueueM)->ulCurrentLength++;\
}

#define MBUF_QUE_DEQUEUE(pstMBufQueueM, pstMBufM)\
{\
    (pstMBufM) = (pstMBufQueueM)->pstHeadMBuf;\
    if((pstMBufM) != NULL)/*queue is NOT empty*/\
    {\
        (pstMBufQueueM)->pstHeadMBuf = MBUF_GET_PTR_NEXT_MBUF( (pstMBufM) );\
        (pstMBufQueueM)->ulCurrentLength--;\
        if( (pstMBufQueueM)->pstTailMBuf == (pstMBufM) )/*this (pstMBufM) is the last in the queue*/\
        {\
            (pstMBufQueueM)->pstTailMBuf = NULL;\
        }\
    }\
}

#define MBUF_QUE_CATENATE(pstDestinationMBufQueueM, pstSourceMBufQueueM)\
{\
    if( (pstDestinationMBufQueueM)->pstTailMBuf == NULL)/*destination is empty*/\
    {\
        /*that source is empty or not has no difference to this process*/\
        (pstDestinationMBufQueueM)->pstHeadMBuf = (pstSourceMBufQueueM)->pstHeadMBuf;\
        (pstDestinationMBufQueueM)->pstTailMBuf = (pstSourceMBufQueueM)->pstTailMBuf;\
        (pstDestinationMBufQueueM)->ulCurrentLength = (pstSourceMBufQueueM)->ulCurrentLength;\
    }\
    else/*destination is NOT empty*/\
    {\
        if( (pstSourceMBufQueueM)->pstHeadMBuf != NULL)/*source is NOT empty*/\
        {\
            MBUF_ASSIGN_PTR_NEXT_MBUF( (pstDestinationMBufQueueM)->pstTailMBuf, (pstSourceMBufQueueM)->pstHeadMBuf);\
            (pstDestinationMBufQueueM)->pstTailMBuf = (pstSourceMBufQueueM)->pstTailMBuf;\
            (pstDestinationMBufQueueM)->ulCurrentLength += (pstSourceMBufQueueM)->ulCurrentLength;\
        }\
        /*when source is empty, nothing need to do*/\
    }\
    (pstSourceMBufQueueM)->pstHeadMBuf = NULL;\
    (pstSourceMBufQueueM)->pstTailMBuf = NULL;\
    (pstSourceMBufQueueM)->ulCurrentLength = 0;\
}


#define MBUF_QUE_PEEK(pstMBufQueueM) ((pstMBufQueueM)->pstHeadMBuf)

#define MBUF_QUE_GET_CURRENT_LENGTH(pstMBufQueueM) ((pstMBufQueueM)->ulCurrentLength)

#define MBUF_QUE_GET_MAX_LENGTH(pstMBufQueueM) ((pstMBufQueueM)->ulMaxLength)

#define MBUF_QUE_GET_ALL( pstMBufQueueM, pstMBufM)\
{\
    ( pstMBufM )= ( pstMBufQueueM )->pstHeadMBuf;\
    ( pstMBufQueueM )->pstHeadMBuf = NULL;\
    ( pstMBufQueueM )->pstTailMBuf = NULL;\
    ( pstMBufQueueM )->ulCurrentLength = 0;\
}

#define MBUF_QUE_DEAL_PACKET(pstMBufQueueM, ulCountM, pfDeal)\
{\
    MBUF_S * pstMBufM;\
    MBUF_S * pstTempMBuf;\
    ULONG ulCount;\
    \
    ulCount = (ulCountM);\
    pstTempMBuf = (pstMBufQueueM)->pstHeadMBuf;\
    (pstMBufQueueM)->ulCurrentLength -= ulCount;\
    for(; ulCount > 0; ulCount-- )\
    {\
        pstMBufM = pstTempMBuf;\
        pstTempMBuf = MBUF_GET_PTR_NEXT_MBUF(pstMBufM);\
        MBUF_ASSIGN_PTR_NEXT_MBUF( pstMBufM, NULL );\
        (VOID)pfDeal(pstMBufM);\
        (VOID)TCPIP_SchedPoint_Check_Delay();\
    }\
    (pstMBufQueueM)->pstHeadMBuf = pstTempMBuf;\
}

#define MBUF_QUE_PREPEND(pstMBufQueueM, pstMBufM)\
{\
    MBUF_ASSIGN_PTR_NEXT_MBUF(pstMBufM, ( pstMBufQueueM )->pstHeadMBuf);\
    ( pstMBufQueueM )->pstHeadMBuf = pstMBufM;\
    if( NULL == ( pstMBufQueueM )->pstTailMBuf )\
    {\
        ( pstMBufQueueM )->pstTailMBuf = pstMBufM;\
    }\
    ( pstMBufQueueM )->ulCurrentLength ++;\
}

#define MBUF_QUE_FREE(pstMBufQueueM)\
{\
    MBUF_S * pstMBuf;\
    MBUF_S * pstNextMBuf;\
    \
    pstMBuf = ( pstMBufQueueM )->pstHeadMBuf;\
    while(pstMBuf != NULL)\
    {\
        pstNextMBuf = MBUF_GET_PTR_NEXT_MBUF(pstMBuf);\
        MBUF_Destroy(pstMBuf);\
        pstMBuf = pstNextMBuf;\
    }\
    ( pstMBufQueueM )->pstHeadMBuf = NULL;\
    ( pstMBufQueueM )->pstTailMBuf = NULL;\
    ( pstMBufQueueM )->ulCurrentLength = 0;\
}

/***************************************************************************

                        user tag data macro

***************************************************************************/
#define MBUF_FLAG_BROADCAST     0x00000001
#define MBUF_FLAG_MULTICAST     0x00000002
#define MBUF_FLAG_URGENT_PACKET 0x00000004
/************************************************
L2&L3为支持产品的底层发送，在发送的MBUF中设置如下两个MBUF标记：
1、对于指定二层端口的单播报文，如:ARP应答报文、IP数据报文等，
   VISP在待发送的MBUF中设置报文标记 MBUF_FLAG_SINGLECAST；
   产品底层在发送处理中，识别此标记后，可以根据出端口直接发送，也可以进行L2查表转发；
2、对于链路层协议报文，如MSTP、OAM、LACP等，由于这些报文都是MAC组播的，但都必须在指定端口上发送(而不能VLAN内广播)；
   VISP在待发送的MBUF中设置报文标记 MBUF_FLAG_PROTOCOLCAST，并指定出端口；
   产品底层在发送处理中，必须根据指定出端口来发送报文（不可在VLAN内广播）；
*************************************************/
#define MBUF_FLAG_SINGLECAST    0x00000008
#define MBUF_FLAG_PROTOCOLCAST  0x00000080

#define MBUF_FLAG_MFORWARD_IO    0x00040000

#define MBUF_FLAG_CONF            0x00000010    /*for ipsec, packet has been encrypted*/
#define MBUF_FLAG_AUTH            0x00000020    /*for ipsec, packet has been authenticated*/
#define MBUF_FLAG_TUNNEL          0x00000040    /*for ipsec, packet has been added tunnel IP head*/
#define MBUF_FLAG_ENCAPSULATED    0x00000800  /*for ipsec outbound packet*/

#define MBUF_FLAG_COMPRESSED_TCP_PACKET        0x00000100
#define MBUF_FLAG_ORDER_PACKET        0x00000200

#define MBUF_FLAG_RECORD_ROUTE        0x00010000

#define MBUF_FLAG_RTP_LLQ_PACKET        0x00100000 /*出队打入MBUF*/
#define MBUF_FLAG_LINK_FRAGMENT_PACKET 0x00200000 /*链路层分片入队打入MBUF*/

#define MBUF_FLAG_FRF12_FRAGMENT_PACKET        0x00400000 /*出队打入MBUF*/

#define MBUF_FLAG_HEADCACHE  0x00800000 /*Head Cache报文*/

/* add for BfdOverTrunkPort */
#define MBUF_FLAG_BFD_OVER_TRUNKPORT 0x00020000
#define MBUF_SET_BFD_TRUNKPORT_IFNET_INDEX(pstMBufM, ulOutIfnetIndex) \
{\
    (pstMBufM)->stUserTagData.stCommonInfo.ulPhyInputIfIndex = (ulOutIfnetIndex);\
}
#define MBUF_GET_BFD_TRUNKPORT_IFNET_INDEX(pstMBuf) \
    ((pstMBuf)->stUserTagData.stCommonInfo.ulPhyInputIfIndex)

#define MBUF_AMFLAG_DECAPSULATED    0x00000400  /*for ipsec inbound packet*/
#define MBUF_AMFLAG_QOSINPUT             0x00000001

#define MBUF_GET_USER_TAG_DATA_PTR(pstMBufM) (&((pstMBufM)->stUserTagData))
#define MBUF_GET_RECEIVE_IFNET_INDEX(pstMBufM) ( (pstMBufM)->stUserTagData.stCommonInfo.ulReceiveIfnetIndex )
#define MBUF_ASSIGN_RECEIVE_IFNET_INDEX(pstMBufM, ulReceiveIfnetIndexM) \
{\
    if ((pstMBufM)->stUserTagData.stCommonInfo.ulReceiveIfnetIndex != (ulReceiveIfnetIndexM))\
    {\
        MBUF_CLEAR_AMFLAG(pstMBufM, MBUF_AMFLAG_DECAPSULATED);\
    }\
    (pstMBufM)->stUserTagData.stCommonInfo.ulReceiveIfnetIndex = (ulReceiveIfnetIndexM);\
}

/*设置L2IF模块的报文入端口接口索引*/
#define MBUF_SET_PORTIFINDEX(pstMBufM, PortIfIndex)\
{\
    (pstMBufM)->stUserTagData.stCommonInfo.ulPortIfIndex = PortIfIndex;\
}

/*获取L2IF模块的报文入端口接口索引*/
#define MBUF_GET_PORTIFINDEX(pstMBufM) ( (pstMBufM)->stUserTagData.stCommonInfo.ulPortIfIndex )

#define MBUF_GET_SEND_IFNET_INDEX(pstMBufM) ( (pstMBufM)->stUserTagData.stCommonInfo.ulSendIfnetIndex )
#define MBUF_ASSIGN_SEND_IFNET_INDEX(pstMBufM, ulSendIfnetIndexM) \
    ((pstMBufM)->stUserTagData.stCommonInfo.ulSendIfnetIndex = (ulSendIfnetIndexM))

#define MBUF_GET_SEND_AT_INDEX(pstMBufM) ( (pstMBufM)->stUserTagData.stCommonInfo.ulSendAtIndex )
#define MBUF_ASSIGN_SEND_AT_INDEX(pstMBufM, ulSendAtIndexM) \
    ((pstMBufM)->stUserTagData.stCommonInfo.ulSendAtIndex = (ulSendAtIndexM))

#define MBUF_GET_IP_INFO_REV_BOARD_ID(pstMBufM) ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIpPacketInfo.ulRevBoardId)
#define MBUF_ASSIGN_IP_INFO_REV_BOARD_ID(pstMBufM, ulSendSlot) ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIpPacketInfo.ulRevBoardId = ulSendSlot )


#define MBUF_GET_FLAG(pstMBufM) ( (pstMBufM)->stUserTagData.stCommonInfo.ulFlag )
#define MBUF_SET_FLAG(pstMBufM, ulFlagM) ((pstMBufM)->stUserTagData.stCommonInfo.ulFlag |= (ulFlagM))
#define MBUF_CLEAR_FLAG(pstMBufM, ulFlagM) ((pstMBufM)->stUserTagData.stCommonInfo.ulFlag &= ( ~(ulFlagM) ))
#define MBUF_GET_AMFLAG(pstMBufM) ( (pstMBufM)->stUserTagData.ulAntiMultiFlag )
#define MBUF_SET_AMFLAG(pstMBufM, ulFlagM) ((pstMBufM)->stUserTagData.ulAntiMultiFlag |= (ulFlagM))
#define MBUF_CLEAR_AMFLAG(pstMBufM, ulFlagM) ((pstMBufM)->stUserTagData.ulAntiMultiFlag &= ( ~(ulFlagM) ))

#define MBUF_GET_QUEUE_ID(pstMBufM) ((pstMBufM)->stUserTagData.stCommonInfo.ulQueueID)
#define MBUF_ASSIGN_QUEUE_ID(pstMBufM, ulQueIDM) \
    ((pstMBufM)->stUserTagData.stCommonInfo.ulQueueID = (ulQueIDM))

#define MBUF_LINK_TYPE_X25                1
#define MBUF_LINK_TYPE_ETHERNET           2
#define MBUF_LINK_TYPE_FRAME_RELAY        3

#define MBUF_GET_TAG_LINK_TYPE(pstMBufM) ((pstMBufM)->stUserTagData.ulLinkType)
#define MBUF_ASSIGN_TAG_LINK_TYPE(pstMBufM, ulLinkTypeM) ((pstMBufM)->stUserTagData.ulLinkType = ulLinkTypeM)

#define MBUF_GET_TAG_LINK_X25_PTR(pstMBufM) (& ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToLink.stX25Info ))
#define MBUF_GET_TAG_LINK_ETHERNET_PTR(pstMBufM) (& ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToLink.stEthernetInfo ))

#define MBUF_GET_TAG_LINK_FRAME_RELAY_PTR(pstMBufM) (& ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToLink.stFrameRelayInfo ))

#define MBUF_GET_TAG_LINK_ATM_PTR(pstMBufM) (& ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToLink.stATMInfo ))

#define MBUF_GET_TAG_VCCINDEX_ATM_PTR(pstMBufM) ( ((CHAR*)&(pstMBufM->stUserTagData.unPacketInfoRelevantToLink.stATMInfo)) + 8 )

#define MBUF_GET_LINK_PPP_PROTOCOL(pstMBufM) \
((pstMBufM)->stUserTagData.unPacketInfoRelevantToLink.stPppInfo.usProtocol)


#define MBUF_ASSIGN_LINK_PPP_PROTOCOL(pstMBufM,usProtocolM) \
((pstMBufM)->stUserTagData.unPacketInfoRelevantToLink.stPppInfo.usProtocol = \
(usProtocolM))

#define MBUF_GET_NETWORK_IP_PROTOCOL(pstMBufM)\
    ((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIpPacketInfo.ucProtocolId)
#define MBUF_GET_NETWORK_IP_DESPORT(pstMBufM)\
    ((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIpPacketInfo.usDestinationPortOrIcmpCode)

#define MBUF_NETWORK_TYPE_IP            1
#define MBUF_NETWORK_TYPE_IPX           2

#define MBUF_GET_TAG_NETWORK_TYPE(pstMBufM) ((pstMBufM)->stUserTagData.ulNetworkType)
#define MBUF_ASSIGN_TAG_NETWORK_TYPE(pstMBufM, ulNetworkTypeM) \
    ((pstMBufM)->stUserTagData.ulNetworkType = ulNetworkTypeM)

#define MBUF_GET_TAG_NETWORK_IP_PTR(pstMBufM) (& ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIpPacketInfo ))

#define MBUF_GET_TAG_MPLS_PTR(pstMBufM)   (& ( (pstMBufM)->stUserTagData.stMplsPacketInfo))

#define MBUF_GET_TAG_MPLS_VPNID(psMBufM, ulXId)\
{\
        ulXId = (psMBufM)->stUserTagData.stMplsPacketInfo.ulVrfIndex; \
}

#define MBUF_SET_TAG_MPLS(pstMBufM, ulToken, ulFlag) \
{\
        (pstMBufM)->stUserTagData.stMplsPacketInfo.ulL3Info |= (ulFlag);    \
        (pstMBufM)->stUserTagData.stMplsPacketInfo.ulVrfIndex = (ulToken);\
}

#define MBUF_SET_TAG_MPLS_VPNID(psMBufM, ulXId)\
{\
        (psMBufM)->stUserTagData.stMplsPacketInfo.ulVrfIndex = ulXId; \
}

/* 得到MBUF中IPv6控制结构指针 */
#define MBUF_GET_TAG_NETWORK_IP6_PTR(pstMBufM) (& ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIp6PacketInfo ))

/* 得到报文中下一跳physical地址的指针 */
#define MBUF_GET_IPV6_NEXTHOPMACADDR(pstMBufM) \
((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIp6PacketInfo.unLinkAddr.szLinkEtherAddr)

/* 设置报文中下一跳physical地址 */
#define MBUF_ASSIGN_IPV6_NEXTHOPMACADDR(pstMBufM, szMac) \
((VOID)TCPIP_Mem_Copy((UCHAR *)((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIp6PacketInfo.unLinkAddr.szLinkEtherAddr),MBUF_MACADDRLEN, \
(UCHAR *)szMac, MBUF_MACADDRLEN))

#define MBUF_GET_IP_INFO_ICMP_TYPE(pstMBufM)   ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIpPacketInfo.usSourcePortOrIcmpType )
#define MBUF_SET_IP_INFO_ICMP_TYPE(pstMBufM, ulType)\
    ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIpPacketInfo.usSourcePortOrIcmpType = (USHORT)(ulType) )

#define MBUF_GET_IP_INFO_ICMP_CODE(pstMBufM)   ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIpPacketInfo.usDestinationPortOrIcmpCode )
#define MBUF_SET_IP_INFO_ICMP_CODE(pstMBufM, ulCode)\
    ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIpPacketInfo.usDestinationPortOrIcmpCode = (USHORT)(ulCode) )

/* V100R006 Lijing 52889 Add for Trunk */
#define MBUF_SET_INPUT_PHY_IFINDEX(pstMBuf, ulIfIndex) \
    ((pstMBuf)->stUserTagData.stCommonInfo.ulPhyInputIfIndex = (ulIfIndex))

/* V100R006 Lijing 52889 Add for Trunk */
#define MBUF_GET_INPUT_PHY_IFINDEX(pstMBuf) \
    ((pstMBuf)->stUserTagData.stCommonInfo.ulPhyInputIfIndex)

#define MBUF_SET_DCC_FLOWID(pstMBufM, ucDccPktFlowID) (pstMBufM->stUserTagData.ucDccFlowID = ucDccPktFlowID)
#define MBUF_GET_DCC_FLOWID(pstMBufM) (pstMBufM->stUserTagData.ucDccFlowID)

/* Add by z62474 for DCC */
#define MBUF_SET_DCCFLAG(pstMBufM, ulFlagM) ((pstMBufM)->stUserTagData.ucDccFlag |= (ulFlagM))
#define MBUF_CLEAR_DCCFLAG(pstMBufM, ulFlagM) ((pstMBufM)->stUserTagData.ucDccFlag &= (~(ulFlagM)))
#define MBUF_GET_DCCFLAG(pstMBufM) ((pstMBufM)->stUserTagData.ucDccFlag)
#define MBUF_FLAG_DCCSTREAM_RCV       0x01
#define MBUF_FLAG_DCCSTREAM_SND       0x02
#define MBUF_FLAG_DCCSTREAM_DESTROY   0x04
/* END */

#define MBUF_PING_COMMON                   0x00 
#define MBUF_PING_OUTIF_SPECIFY            0x01 
#define MBUF_PING_OUTIF_NEXTHOP            0x02 

#define MBUF_ASSIGN_PING_MODE(pstMBufM, usPingMode) \
    ((pstMBufM)->stUserTagData.usPingMode = (usPingMode))

#define MBUF_GET_PING_MODE(pstMBufM) ((pstMBufM)->stUserTagData.usPingMode)


#define MBUF_GET_SRC_PORT_IP6(pstMBufM)   ( (pstMBufM)->usIpv6SourcePort )
#define MBUF_SET_SRC_PORT_IP6(pstMBufM, ulType)\
    ( (pstMBufM)->usIpv6SourcePort = (ulType) )

#define MBUF_GET_DST_PORT_IP6(pstMBufM)   ( (pstMBufM)->usIpv6DestinationPort )
#define MBUF_SET_DST_PORT_IP6(pstMBufM, ulCode)\
    ( (pstMBufM)->usIpv6DestinationPort = (ulCode) )

#define MBUF_IP4_VERSION                   0x04 
#define MBUF_IP6_VERSION                   0x06 
#define MBUF_GET_IP_VER(pstMBufM)   ( (pstMBufM)->ulIpVersion )
#define MBUF_SET_IP_VER(pstMBufM, ulVersion)\
    ( (pstMBufM)->ulIpVersion = (ulVersion) )

#define MBUF_SPECIFY_OUTIF_FLAG          0x01
#define MBUF_SPECIFY_NEXTHOP_FLAG        0x02

/* 获取MBUF指定下一跳或出接口标记信息 */
#define MBUF_GET_SPECIFY_FLAG(pstMBufM) ((pstMBufM)->stUserTagData.ucUserSpecifyFlag)

/* 设置MBUF指定下一跳或出接口标记信息 */
#define MBUF_ASSIGN_SPECIFY_FLAG(pstMBufM,ucSpecifyFlagM)\
(((pstMBufM)->stUserTagData.ucUserSpecifyFlag) = (ucSpecifyFlagM))

/* MBUF 自有数据的地址 */
#define MBUF_GET_PRIVATE_DATA_PTR(pstMBufM) (&(pstMBufM)->stUserTagData.ulPrivateData[0])
/*******************************************************************************
*    Func Name: TCPIP_GetSysDBRefCnt
*  Description: 获取系统DB的引用计数
*        Input: MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor:要获取引用计数DB对应的DBD
*       Output: ULONG *pulCount:引用计数
*       Return: VOS_OK:总返回成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2004-7-7     zhany hong yan(19316)   Create
*
*******************************************************************************/
extern ULONG TCPIP_GetSysDBRefCnt(MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor, ULONG *pulCount);

/* 下面两个宏是从ppmng_pub.h移到mbuf.h中的 */
#define MBUF_IP6ADDRLEN 16
/* 得到报文中下一跳IPv6地址的指针 */
#define MBUF_GET_IPV6_NEXTHOPADDR(pstMBufM) \
    (&((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIp6PacketInfo.stNextHopIpAddr))

/* 设置报文中下一跳IPv6地址 */
#define MBUF_ASSIGN_IPV6_NEXTHOPADDR(pstMBufM, addr) \
    ((VOID)TCPIP_Mem_Copy((VOID *)&((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIp6PacketInfo.stNextHopIpAddr),MBUF_IP6ADDRLEN, \
    (VOID *)&addr, MBUF_IP6ADDRLEN))

/* 获取MBUF中的IPV6报文协议号 */
#define MBUF_GET_IPV6_PROTOCOL_ID(pstMBufM) \
    ((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIp6PacketInfo.ucProtocolID)

/* 设置MBUF中的IPV6报文协议号 */
#define MBUF_SET_IPV6_PROTOCOL_ID(pstMBufM, ucProtocolIDM) \
    ((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIp6PacketInfo.ucProtocolID = (ucProtocolIDM))

/* 获取MBUF中的IPV6报文通信流类别 */
#define MBUF_GET_IPV6_TRAFFIC_CLASS(pstMBufM) \
    ((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIp6PacketInfo.ucServiceType)

/* 设置MBUF中的IPV6报文通信流类别 */
#define MBUF_SET_IPV6_TRAFFIC_CLASS(pstMBufM, ucServiceTypeM) \
    ((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIp6PacketInfo.ucServiceType = (ucServiceTypeM))

/* 获取MBUF中的IPV6报文类型标识 */
#define MBUF_GET_IP6_INFO_PKT_TYPE(pstMBufM)\
    ((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIp6PacketInfo.ulIpPktType)

/* 获取VLAN头信息(包括VLAN类型和值),主机序 */
#define MBUF_GET_VLAN_HEAD_VALUE(pstMBufM) \
    ((pstMBufM)->stUserTagData.unPacketInfoRelevantToPhysical.ulTemp)

/* 设置VLAN头信息(包括VLAN类型和值),主机序 */
#define MBUF_SET_VLAN_HEAD_VALUE(pstMBufM, ulVlanHeadM) \
    ((pstMBufM)->stUserTagData.unPacketInfoRelevantToPhysical.ulTemp = (ulVlanHeadM))

#define MBUF_Destroy(pMBuf) \
{ \
    ULONG ulLine = __LINE__;\
    CHAR  szCurrentFileName[FILENAME_LEN];\
    MBUF_S *pst_MBuf = pMBuf;\
    \
    TCPIP_GetFileName((CHAR*)__FILE__, szCurrentFileName, FILENAME_LEN);\
    \
    MBUF_DestroyFunc(szCurrentFileName, ulLine, pst_MBuf);\
}

#define MBUF_ASSIGN_VLANID(pstMBuf,usVLANID) ((pstMBuf)->stUserTagData.usVID = (USHORT)(usVLANID))
#define MBUF_GET_VLANID(pstMBuf) ((pstMBuf)->stUserTagData.usVID)

#define ARP_LOG_GET_VLANHEAD(pstMBuf) pstMBuf->stUserTagData.unPacketInfoRelevantToPhysical.ulTemp
#define ARP_LOG_SET_VLANHEAD(pstMBuf,ulVlanHead) \
{\
    pstMBuf->stUserTagData.unPacketInfoRelevantToPhysical.ulTemp = ulVlanHead;\
}
/* End of addition */

/*************************与性能优化有关的宏*************************/
/* 设置主机接收标志 */
#define MBUF_SET_IPTYPE_OURRCV(pMbuf)\
{\
    (pMbuf)->usPktType = OPTIM_MBUF_OURRCV;\
}

/* 设置socket ID */
/* Modified by y00176567, at 2011-05-26. 修改原因: 消除VC三级告警 */
/* iFd前面添加(USHORT)，进行强制类型转换以和左边表达式类型一致 */
#define MBUF_SET_SOCKET_ID(pMbuf, iFd)\
{\
    (pMbuf)->usSocketID = (USHORT)(iFd);\
}

/* 获取socket ID */
#define MBUF_GET_SOCKET_ID(pMbuf, iFd)\
{\
    (iFd) = (pMbuf)->usSocketID;\
}

#define MBUF_GET_IP_INFO_PKT_TYPE(pstMBufM)\
    ((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIpPacketInfo.ulIpPktType)

#define MBUF_SET_IP_INFO_PKT_TYPE(pstMBufM,flag)\
    ((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIpPacketInfo.ulIpPktType |= flag)

/*************************与性能优化有关的宏*************************/

/* 获取以太帧封装类型(Eth2/SNAP) */
#define MBUF_GET_ETHERNET_ENCAP_TYPE(pstMBufM)\
    ((pstMBufM)->ulEncapType)

/* 设置以太帧封装类型(Eth2/SNAP) */    
#define MBUF_SET_ETHERNET_ENCAP_TYPE(pstMBufM,ulFlagM)\
    (((pstMBufM)->ulEncapType ) = (ulFlagM))

/*****************************时间戳操作宏*****************************/
/* Modify by z00171897/s00176784, at 2011-06-02. 修改原因: 支持获取保存ARP报文队列 */
/* 设置低字节时间戳 */
#define MBUF_SET_TIMESTAMP_LOW(pstMbuf,ulTimeMinSecondLow) \
    ((pstMbuf)->ulTimeStampLow = (ulTimeMinSecondLow))

/* 设置高字节时间戳 */
#define MBUF_SET_TIMESTAMP_HIGH(pstMbuf, ulTimeMinSecondHigh) \
    ((pstMbuf)->ulTimeStampHigh = (ulTimeMinSecondHigh))

/* 获取低字节时间戳 */
#define MBUF_GET_TIMESTAMP_LOW(pstMbuf)       ((pstMbuf)->ulTimeStampLow)

/* 获取高字节时间戳 */
#define MBUF_GET_TIMESTAMP_HIGH(pstMbuf)      ((pstMbuf)->ulTimeStampHigh)

/* 根据模块ID做Mbuf自增统计 */
#define MBUF_ADD_STAT_BY_MID(pstMbuf, ulModuleId)\
{\
    pstMbuf->ulModID = ulModuleId;\
    if ((ulModuleId >= MID_COMP_BASE) && (ulModuleId <= (MID_COMP_BASE + 0x00FF0000)))\
    {\
        ULONG ulMidIndex = (ulModuleId - MID_COMP_BASE) >> 16;\
        g_ulMbufStatByMID[ulMidIndex]++;\
    }\
    else\
    {\
        pstMbuf->ulModID = 0;\
        g_ulMbufStatByMID[MBUF_MAX_MID]++;\
    }\
}

/* 根据模块ID做Mbuf自减统计 */
#define MBUF_DEC_STAT_BY_MID(pstMbuf)\
{\
    if (0 == pstMbuf->ulModID)\
    {\
        g_ulMbufStatByMID[MBUF_MAX_MID]--;\
    }\
    else\
    {\
        ULONG ulMidIndex = (pstMbuf->ulModID - MID_COMP_BASE) >> 16;\
        ulMidIndex &= (ULONG)0xff;\
        g_ulMbufStatByMID[ulMidIndex]--;\
    }\
}

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif    /* end of _MBUF_H_ */

