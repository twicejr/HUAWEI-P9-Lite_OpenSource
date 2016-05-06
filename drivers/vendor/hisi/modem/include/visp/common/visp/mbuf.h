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

/*
Remark:*/
#define MBUF_GET_TAG_MPLS_PTR(pstMBufM)   (& ( (pstMBufM)->stUserTagData.stMplsPacketInfo))

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
    /* Modified by z00208058/w00207740, U8定义冲突, 2012/5/7 */
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
    UCHAR   ucDccFlowID;             /* DCC报文流标记ID*/
    UCHAR   ucDccFlag;                /*DCC 标记*/
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

    ULONG ulEncapType;             /*Eth报文封装类型: 目前只有Eth2/SNAP格式 */    
    USHORT usIpv6SourcePort;        /*对TCP、UDP报文，是源端口号，对ICMP6报文是type*/
    USHORT usIpv6DestinationPort;   /*对TCP、UDP报文，是目的端口号，对ICMP6报文是code*/
    ULONG ulIpVersion;             /*ip version*/
    /*Added by zhoushisong202096, 更改TCP重组队列, 2013/11/5 */ 
    struct tagMBuf * pstPrevMBuf;/*上一个mbuf， NULL表示无效，其他表示有效*/        
    UCHAR *pu8NetLayerHeader;    /* 指向报文的网络层首部 */
    ULONG ulReserved[4];           /*保留为以后使用*/
}MBUF_S;/*mbuf的头标签数据结构*/

/*设置L2IF模块的报文入端口接口索引*/
#define MBUF_SET_PORTIFINDEX(pstMBufM, PortIfIndex)\
{\
    (pstMBufM)->stUserTagData.stCommonInfo.ulPortIfIndex = PortIfIndex;\
}

/*获取L2IF模块的报文入端口接口索引*/
#define MBUF_GET_PORTIFINDEX(pstMBufM) ( (pstMBufM)->stUserTagData.stCommonInfo.ulPortIfIndex )

#define MBUF_ASSIGN_VLANID(pstMBuf,usVLANID) ((pstMBuf)->stUserTagData.usVID = (USHORT)(usVLANID))
#define MBUF_GET_VLANID(pstMBuf) ((pstMBuf)->stUserTagData.usVID)

#define ARP_LOG_GET_VLANHEAD(pstMBuf) pstMBuf->stUserTagData.unPacketInfoRelevantToPhysical.ulTemp
#define ARP_LOG_SET_VLANHEAD(pstMBuf,ulVlanHead) \
{\
    pstMBuf->stUserTagData.unPacketInfoRelevantToPhysical.ulTemp = ulVlanHead;\
}
/* End of addition */

/*private data type------------------------------------------------------END*/

/*private function----------------------------------------------------------*/

MBUF_DATABLOCKDESCRIPTOR_S * MBUF_CreateDBDescriptorAndDB(ULONG ulDataBlockLength, ULONG ulType, ULONG ulModuleID);
ULONG MBUF_PullUp(MBUF_S * pstMBuf, ULONG ulLength, ULONG ulModuleID);
ULONG MBUF_PrependDataBlock(MBUF_S * pstMBuf, ULONG ulLength, ULONG ulModuleID);
VOID MBUF_CutHeadInMultiDataBlock(MBUF_S * pstMBuf, ULONG ulLength);

extern VOID MBUF_DestroyFunc(CHAR *szCurrentFileName, ULONG ulLine, MBUF_S *pMBuf);
extern ULONG TCPIP_GetUserDBRef(VOID * pBuf, ULONG * pulRetRef );

/*private function----------------------------------------------------------END*/

/*************************************************************************


                                 PUBLIC SECTION



You can use the following items as the programmer manual described
**************************************************************************/

#define MBUF_TYPE_DATA     1

#define MBUF_FAIL ((ULONG) 1)/*接口操作失败*/
#define MBUF_OK   ((ULONG) 0)/*接口操作成功*/
#define MBUF_INPUT_NULL        ((ULONG) 2)/*mbuf接口入参为空*/
#define MBUF_DB_LENGTH_ERROR   ((ULONG) 3)/*mbuf接口入参DB长度错误*/
#define MBUF_INPUT_HOOK_NULL   ((ULONG) 4)/*mbuf接口入参DB长度错误*/




/* add magic number for mbuf */
#define MBUF_IDLE          0x49444C45  /* ASCII of "IDLE"*/
#define MBUF_BUSY          0x42555359  /* ASCII of "BUSY"*/

#define MBUF_TYPE_SOOPTS   5

#define MBUF_DATA_BLOCK2048_SIZE 2048

#define MBUF_DATA_NORMAL 0/*DB是从协议栈申请的*/
#define MBUF_DATA_USERMNG 3/*DB是用户申请的*/

#define MBUF_AMFLAG_DECAPSULATED    0x00000400  /*for ipsec inbound packet*/

#define MBUF_GET_PTR_NEXT_MBUF(pstMBufM) ( (pstMBufM)->pstNextMBuf )

#define MBUF_GET_FLAG(pstMBufM) ( (pstMBufM)->stUserTagData.stCommonInfo.ulFlag )

/* 得到MBUF中IPv6控制结构指针 */
#define MBUF_GET_TAG_NETWORK_IP6_PTR(pstMBufM) (& ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIp6PacketInfo ))

#define MBUF_ASSIGN_SEND_IFNET_INDEX(pstMBufM, ulSendIfnetIndexM) \
    ((pstMBufM)->stUserTagData.stCommonInfo.ulSendIfnetIndex = (ulSendIfnetIndexM))

#define MBUF_ASSIGN_SEND_AT_INDEX(pstMBufM, ulSendAtIndexM) \
        ((pstMBufM)->stUserTagData.stCommonInfo.ulSendAtIndex = (ulSendAtIndexM))
/* End of addition by z43740,2008/03/16 */

#define MBUF_ASSIGN_RECEIVE_IFNET_INDEX(pstMBufM, ulReceiveIfnetIndexM) \
{\
    if ((pstMBufM)->stUserTagData.stCommonInfo.ulReceiveIfnetIndex != (ulReceiveIfnetIndexM))\
    {\
        MBUF_CLEAR_AMFLAG(pstMBufM, MBUF_AMFLAG_DECAPSULATED);\
    }\
    (pstMBufM)->stUserTagData.stCommonInfo.ulReceiveIfnetIndex = (ulReceiveIfnetIndexM);\
}

#define MBUF_GET_AMFLAG(pstMBufM) ( (pstMBufM)->stUserTagData.ulAntiMultiFlag )
#define MBUF_SET_AMFLAG(pstMBufM, ulFlagM) ((pstMBufM)->stUserTagData.ulAntiMultiFlag |= (ulFlagM))
#define MBUF_CLEAR_AMFLAG(pstMBufM, ulFlagM) ((pstMBufM)->stUserTagData.ulAntiMultiFlag &= ( ~(ulFlagM) ))

#define MBUF_GET_TAG_MPLS_VPNID(psMBufM, ulXId)\
{\
        ulXId = (psMBufM)->stUserTagData.stMplsPacketInfo.ulVrfIndex; \
}

#define MBUF_SET_TAG_MPLS_VPNID(psMBufM, ulXId)\
{\
        (psMBufM)->stUserTagData.stMplsPacketInfo.ulVrfIndex = ulXId; \
}

extern VOID MBUF_LOG_Info (ULONG ulCaseType, MBUF_S *pstMbuf,
                           CHAR *cCurrentFileName, ULONG ulCurrentFileLine, ULONG ulCurrentTaskId);
extern VOID TCPIP_GetFileName(CHAR *pstFile, CHAR *pstFileName, ULONG ulstrMaxLen);
extern ULONG MBUF_FreeMbuf(MBUF_S *pstMBuf);

MBUF_S * MBUF_ReferenceCopy(MBUF_S * pstMBuf, ULONG ulOffset, ULONG ulLength, ULONG ulModuleID);

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
     ULONG ulReferenceCount=0; /*CodeCC Error: 25376  Fix */\
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
#define MBUF_MTOD(pstMBufM, DataTypeM) ( (DataTypeM)  (pstMBufM)->stDataBlockDescriptor.pucData )


#define MBUF_GET_TOTAL_DATA_LENGTH(pstMBufM) ( (pstMBufM)->ulTotalDataLength )

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

/*public macro----------------------------------------------------------END*/

/*public function---------------------------------------------------------------------*/
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

MBUF_S * MBUF_CreateByCopyBuffer(ULONG ulReserveHeadSpace, ULONG ulLength, UCHAR * pucBuffer, ULONG ulType, ULONG ulModuleID);
MBUF_S * MBUF_CreateForControlPacket(ULONG ulReserveHeadSpace, ULONG ulLength, ULONG ulType, ULONG ulModuleID);

ULONG MBUF_CopyDataFromBufferToMBuf(MBUF_S * pstMBuf, ULONG ulOffset, ULONG ulLength, UCHAR * pucBuffer, ULONG ulModuleID);
ULONG MBUF_CopyDataFromMBufToBuffer(MBUF_S * pstMBuf, ULONG ulOffset, ULONG ulLength, UCHAR * pucBuffer);
MBUF_S * MBUF_RawCopy(MBUF_S * pstMBuf, ULONG ulOffset, ULONG ulLength, ULONG ulReserveHeadSpace, ULONG ulModuleID);

ULONG MBUF_Concatenate(MBUF_S * pstDestinationMBuf, MBUF_S * pstSourceMBuf, ULONG ulModuleID);/*when ok, pstSourceMBuf is NOT valid any more*/
ULONG MBUF_NeatConcatenate_Chain(MBUF_S *pstMbufHead, ULONG ulModuleID);
ULONG MBUF_CutPart(MBUF_S * pstMBuf, ULONG ulOffset, ULONG ulLength);
ULONG MBUF_CutTail(MBUF_S * pstMBuf, ULONG ulLength);

UCHAR * MBUF_AppendMemorySpace(MBUF_S * pstMBuf, ULONG ulLength, ULONG ulModuleID);

/*public function---------------------------------------------------------------------END*/

/***************************************************************************

                        user tag data macro

***************************************************************************/
#define MBUF_FLAG_MULTICAST    0x00000002

#define MBUF_FLAG_CONF            0x00000010    /*for ipsec, packet has been encrypted*/
#define MBUF_FLAG_AUTH            0x00000020    /*for ipsec, packet has been authenticated*/
#define MBUF_FLAG_TUNNEL          0x00000040    /*for ipsec, packet has been added tunnel IP head*/
#define MBUF_FLAG_ENCAPSULATED    0x00000800  /*for ipsec outbound packet*/


#define MBUF_GET_RECEIVE_IFNET_INDEX(pstMBufM) ( (pstMBufM)->stUserTagData.stCommonInfo.ulReceiveIfnetIndex )

#define MBUF_GET_SEND_IFNET_INDEX(pstMBufM) ( (pstMBufM)->stUserTagData.stCommonInfo.ulSendIfnetIndex )

#define MBUF_GET_SEND_AT_INDEX(pstMBufM) ( (pstMBufM)->stUserTagData.stCommonInfo.ulSendAtIndex )

#define MBUF_SET_FLAG(pstMBufM, ulFlagM) ((pstMBufM)->stUserTagData.stCommonInfo.ulFlag |= (ulFlagM))
#define MBUF_CLEAR_FLAG(pstMBufM, ulFlagM) ((pstMBufM)->stUserTagData.stCommonInfo.ulFlag &= ( ~(ulFlagM) ))

#define MBUF_ASSIGN_QUEUE_ID(pstMBufM, ulQueIDM) \
    ((pstMBufM)->stUserTagData.stCommonInfo.ulQueueID = (ulQueIDM))


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

/* 设置报文中下一跳physical地址 */
#define MBUF_ASSIGN_IPV6_NEXTHOPMACADDR(pstMBufM, szMac) \
((VOID)TCPIP_Mem_Copy((UCHAR *)((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIp6PacketInfo.unLinkAddr.szLinkEtherAddr),MBUF_MACADDRLEN, \
(UCHAR *)szMac, MBUF_MACADDRLEN))

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

#define MBUF_TR_ICMP6_DELIVEREDTOUP             0x0000001D

#define MBUF_AMFLAG_IPSEC6_ENCAPSULATED_IPV6    0x00000200

/* Added by sumangala*/
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

/* 获取以太帧封装类型(Eth2/SNAP) */
#define MBUF_GET_ETHERNET_ENCAP_TYPE(pstMBufM)\
    ((pstMBufM)->ulEncapType)

/* 设置以太帧封装类型(Eth2/SNAP) */    
#define MBUF_SET_ETHERNET_ENCAP_TYPE(pstMBufM,ulFlagM)\
    (((pstMBufM)->ulEncapType ) = (ulFlagM))


#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif    /* end of _MBUF_H_ */

