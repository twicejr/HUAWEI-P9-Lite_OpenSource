/************************************************************************
 *                                                                      *
 *                          fastmbuf.h                                  *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/12/04                                      *
 *  Author:             David.Fan                                       *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           快速MBUF主模块                                  *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 * Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
 *                     ALL RIGHTS RESERVED                              *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *               本文件包括快速MBUF的定义	                            *
 *                                                                      *
 ************************************************************************/

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _FAST_MBUF_H_
#define _FAST_MBUF_H_

/* ------------------------------------  CPCI Fast MBuf ----------------------------------------*/
/*                                                                                              */
/* ------------------------------------  CPCI Fast MBuf ----------------------------------------*/
/* dengyiou for performance optimizing 2004-01-30 */
/* 8040内存紧张，还是保持128块fast mbuf。其它产品统统改为256 */
#if(VRP_PRODUCT_8040 == VRP_YES)
#define FASTMBUF_HEAD_MBUF_CACHE_NUM    128     /* CPCI Fast MBUF缓冲个数,2的整数倍 */
#define FASTMBUF_HEAD_MBUF_CACHE_MASK   (FASTMBUF_HEAD_MBUF_CACHE_NUM - 1)
                                                /* CPCI Fast MBUF缓冲个数的掩码 */
#define FASTMBUF_HEAD_MBUF_RECACHE_NUM  64      /* CPCI Fast MBUF缓冲的恢复临界值 */
#else
/* dengyiou 2004-02-20 for IZB test: increase head cache */
#if( VRP_MODULE_ATM_CELL_TRANSPORT == VRP_YES )
#define FASTMBUF_HEAD_MBUF_CACHE_NUM    8192    /* CPCI Fast MBUF缓冲个数,2的整数倍 */
#define FASTMBUF_HEAD_MBUF_CACHE_MASK   (FASTMBUF_HEAD_MBUF_CACHE_NUM - 1)
                                                /* CPCI Fast MBUF缓冲个数的掩码 */
#define FASTMBUF_HEAD_MBUF_RECACHE_NUM  8192    /* CPCI Fast MBUF缓冲的恢复临界值 */
#else
#define FASTMBUF_HEAD_MBUF_CACHE_NUM    256     /* CPCI Fast MBUF缓冲个数,2的整数倍 */
#define FASTMBUF_HEAD_MBUF_CACHE_MASK   (FASTMBUF_HEAD_MBUF_CACHE_NUM - 1)
                                                /* CPCI Fast MBUF缓冲个数的掩码 */
#define FASTMBUF_HEAD_MBUF_RECACHE_NUM  256     /* CPCI Fast MBUF缓冲的恢复临界值 */
#endif
#endif
#define FASTMBUF_HEAD_DATABLOCK_LENGTH  2036    /* 预先定义的MBUF的大小,与CPCI传送内存块大小有关 */

extern ULONG   gulFastMBufHeadCacheFreeNum;
extern ULONG   gulFastMBufHeadCacheFreeIndex;
extern ULONG   gulFastMBufHeadCacheAllocIndex;
extern MBUF_S* gstFastMBufHeadCache[FASTMBUF_HEAD_MBUF_CACHE_NUM];

/* 是FAST MBUF Head with CPCI内存吗 */
#define IS_CPCIMBUF_MBUF(pstMBufTemp) (MBUF_GET_FLAG(pstMBufTemp) & MBUF_FLAG_IPC_MEMORY)

/* 本宏的调用者必须关中断 */
#define FASTMBUF_HEAD_INNER_ALLOC_MBUF(pstMBufTemp)\
{\
    if ( gulFastMBufHeadCacheFreeNum > 0 )\
    {\
        (pstMBufTemp) = gstFastMBufHeadCache[gulFastMBufHeadCacheAllocIndex]; \
        gstFastMBufHeadCache[gulFastMBufHeadCacheAllocIndex] = NULL; \
        gulFastMBufHeadCacheAllocIndex = (gulFastMBufHeadCacheAllocIndex + 1) & FASTMBUF_HEAD_MBUF_CACHE_MASK;\
        gulFastMBufHeadCacheFreeNum--;\
    }\
    else \
    {\
        pstMBufTemp = NULL;\
    }\
}

/* 本宏的调用者必须关中断 */
#define FASTMBUF_HEAD_FREE_MBUF(pstMBufTemp)\
{\
    if ( gulFastMBufHeadCacheFreeNum < FASTMBUF_HEAD_MBUF_CACHE_NUM )\
    {\
        gstFastMBufHeadCache[gulFastMBufHeadCacheFreeIndex] = (pstMBufTemp); \
        gulFastMBufHeadCacheFreeIndex = (gulFastMBufHeadCacheFreeIndex + 1) & FASTMBUF_HEAD_MBUF_CACHE_MASK; \
            gulFastMBufHeadCacheFreeNum++; /* 空闲指针++ */ \
    }\
    else \
    {\
        VOS_DBGASSERT(1 == 0);\
    }\
}

/* 将CPCI数据块加入到MBUF控制头中 */
#define FASTMBUF_HEAD_ADD_DATA_BLOCK_2040(pstMBufTemp, pucDataBlockM, ulDataBlockLengthM, pucDataM, ulDataLengthM) \
{\
    if ( gulFastMBufHeadCacheFreeNum > 0 )\
    {\
        FASTMBUF_HEAD_INNER_ALLOC_MBUF(pstMBufTemp);\
        \
        (pstMBufTemp)->stDataBlockDescriptor.pucDataBlock = (pucDataBlockM);\
        (pstMBufTemp)->stDataBlockDescriptor.ulDataBlockLength = (ulDataBlockLengthM);\
        (pstMBufTemp)->stDataBlockDescriptor.pucData = (pucDataM);\
        (pstMBufTemp)->stDataBlockDescriptor.ulDataLength = (ulDataLengthM);\
        (pstMBufTemp)->ulTotalDataLength = (ulDataLengthM);\
        \
        (pstMBufTemp)->stDataBlockDescriptor.pstNextDataBlockDescriptor = NULL;\
        (pstMBufTemp)->ulDataBlockNumber = 1;\
        (pstMBufTemp)->pstNextMBuf = NULL;\
    }\
    else\
    {\
        pstMBufTemp = VOS_Malloc( MID_IP_FF | SID_MBUF_S, MBUF_MBUF_SIZE);\
        if (pstMBufTemp)\
        {\
            (VOID)VOS_Mem_Zero(&( (pstMBufTemp) -> stUserTagData ),sizeof(MBUF_USERTAGDATA_S));\
            (pstMBufTemp)->stDataBlockDescriptor.pucDataBlock = (pucDataBlockM);\
            (pstMBufTemp)->stDataBlockDescriptor.ulDataBlockLength = (ulDataBlockLengthM);\
            (pstMBufTemp)->stDataBlockDescriptor.pucData = (pucDataM);\
            (pstMBufTemp)->stDataBlockDescriptor.ulDataLength = (ulDataLengthM);\
            (pstMBufTemp)->ulTotalDataLength = (ulDataLengthM);\
            \
            (pstMBufTemp)->stDataBlockDescriptor.pstNextDataBlockDescriptor = NULL;\
            (pstMBufTemp)->ulDataBlockNumber = 1;\
            (pstMBufTemp)->pstNextMBuf = NULL;\
        }\
        else\
        {\
            (pstMBufTemp) = 0;\
        }\
    }\
}
/* ------------------------------------  CPCI Fast MBuf End  ------------------------------*/


/* ------------------------------------  Fast MBuf ----------------------------------------*/
/*                                                                                         */
/* ------------------------------------  Fast MBuf ----------------------------------------*/
#define FASTMBUF_PREALLOC_DATALEN1  2048    /* 预先申请的MBUF的大小 */

/* dengyiou for performance optimizing 2004-01-30 */
/* 8040内存紧张，还是保持128块fast mbuf。其它产品统统改为512(共占用1M内存，影响不大) */
#if(VRP_PRODUCT_8040 == VRP_YES)
#define FASTMBUF_MBUF_CACHE_NUM 128         /* Fast MBUF缓冲个数,2的整数倍 */
#define FASTMBUF_PREALLOC_MBUF_NUM  100     /* 预先申请的MBUF个数,小于FASTMBUF_MBUF_CACHE_NUM */
#else
/* dengyiou for IZB test 2004-02-25 */
/* 信元透传的情况下，收到的都是53字节信元，要消耗大量快mbuf，所以放大快mbuf数目 */
#if( VRP_MODULE_ATM_CELL_TRANSPORT == VRP_YES )
#define FASTMBUF_MBUF_CACHE_NUM 1024        /* Fast MBUF缓冲个数,2的整数倍 */
#define FASTMBUF_PREALLOC_MBUF_NUM  1024    /* 预先申请的MBUF个数,小于FASTMBUF_MBUF_CACHE_NUM */
#else
#define FASTMBUF_MBUF_CACHE_NUM 512         /* Fast MBUF缓冲个数,2的整数倍 */
#define FASTMBUF_PREALLOC_MBUF_NUM  512     /* 预先申请的MBUF个数,小于FASTMBUF_MBUF_CACHE_NUM */
#endif
#endif
#define FASTMBUF_MBUF_CACHE_MASK    (FASTMBUF_MBUF_CACHE_NUM - 1)
                                            /* Fast MBUF缓冲个数的掩码 */

extern ULONG   gulFastMBufCacheFreeNum;
extern ULONG   gulFastMBufCacheFreeIndex;
extern ULONG   gulFastMBufCacheAllocIndex;
extern MBUF_S* gstFastMBufCache[FASTMBUF_MBUF_CACHE_NUM];


/* 是FAST MBUF内存吗 */
#define IS_FASTMBUF_MBUF(pstMBufTemp) (MBUF_GET_FLAG(pstMBufTemp) & MBUF_FLAG_FAST_MBUF)

/* 标记MBUF为FAST MBUF */
/* dengyiou 2004-09-15 for IAS pruning */
#if(VRP_MODULE_IPV6 == VRP_YES)
#define MBUF_SET_FASTMBUF_NATPT(pstMBufTemp) \
        (pstMBufTemp)->stUserTagData.ulNatPtFlag = 0
#else
#define MBUF_SET_FASTMBUF_NATPT(pstMBufTemp)  
#endif

/* changed by mayun 2004-03-18 */
#if( VRP_OPTIM_MBUF == VRP_YES )
    #define SET_MBUF_FASTMBUF_MBUF(pstMBufTemp) \
    {\
        (pstMBufTemp)->stUserTagData.stCommonInfo.ulSendIfnetIndex = 0;\
        (pstMBufTemp)->stDataBlockDescriptor.ulType = MBUF_TYPE_DATA;\
        (pstMBufTemp)->stUserTagData.stCommonInfo.ulFlag = 0;\
        (pstMBufTemp)->stUserTagData.ulAntiMultiFlag = 0;\
        /* dengyiou 2004-09-15 for IAS pruning */\
        /* (pstMBufTemp)->stUserTagData.ulNatPtFlag = 0;*/\
        MBUF_SET_FASTMBUF_NATPT(pstMBufTemp);\
        MBUF_ZERO_TAG_LINK(pstMBufTemp); \
        MBUF_SET_MQC_CLASSNO(pstMBufTemp, 0);\
        MBUF_ASSIGN_VLANID(pstMBufTemp, 0);\
        MBUF_ASSIGN_PVCID(pstMBufTemp, 0);\
        MBUF_ASSIGN_ATMCLP(pstMBufTemp,0);\
        /*add by gwei for layer2 QOS project */\
        MBUF_ASSIGN_ORIGIN_RECV_IFINDEX(pstMBufTemp, 0);\
        /* Fixed for MPLS forwarding . some  time fail to ping */\
        (pstMBufTemp)->stUserTagData.stMplsPacketInfo.ulVrfIndex = 0;\
        (pstMBufTemp)->stUserTagData.stMplsPacketInfo.ulL3Info = 0;\
        /* Fixed By Rajesh 2004-03-26 ping is not working some times */\
        VOS_Mem_Set( (VOID *) (MBUF_GET_TAG_NETWORK_IP_PTR(pstMBufTemp)), 0 , sizeof(MBUF_IP_PACKET_INFO_S));\
        /*if (MBUF_GET_TAG_NETWORK_TYPE(pstMBufTemp) == AF_INET)\
        {\
            MBUF_IP_PACKET_INFO_S	*pstIpInfo;\
            pstIpInfo = MBUF_GET_TAG_NETWORK_IP_PTR(pstMBufTemp);\
            MBUF_ASSIGN_IP_INFO_LOOPTIMES( pstIpInfo, 0 ); \
            MBUF_ASSIGN_IP_INFO_PKT_TYPE( pstIpInfo, 0 ); \
            (pstMBufTemp)->stUserTagData.stMplsPacketInfo.ulVrfIndex = 0;\
        }\
        else\
        {\
            MBUF_INIT_IP6PACKETINFO_FASTMBUF(pstMBufTemp);\
        }*/\
        VOS_DBGASSERT((pstMBufTemp)->stDataBlockDescriptor.pstNextDataBlockDescriptor == NULL); \
        VOS_DBGASSERT((pstMBufTemp)->ulTotalDataLength ==(pstMBufTemp)->stDataBlockDescriptor.ulDataLength); \
        VOS_DBGASSERT((pstMBufTemp)->ulDataBlockNumber == 1);\
        (pstMBufTemp)->pstNextMBuf = NULL;\
        MBUF_INIT_FIREWALL_FASTMBUF(pstMBufTemp);\
    }
#else  /* VRP_OPTIM_MBUF == VRP_NO */
    #define SET_MBUF_FASTMBUF_MBUF(pstMBufTemp) \
    {\
        (pstMBufTemp)->stUserTagData.stCommonInfo.ulSendIfnetIndex = 0;\
        (pstMBufTemp)->stDataBlockDescriptor.ulType = MBUF_TYPE_DATA;\
        (pstMBufTemp)->stDataBlockDescriptor.ulOption = 0;\
        (pstMBufTemp)->stUserTagData.stCommonInfo.ulFlag = 0;\
        (pstMBufTemp)->stUserTagData.ulAntiMultiFlag = 0 ;\
        /* dengyiou 2004-09-15 for IAS pruning */\
        /* (pstMBufTemp)->stUserTagData.ulNatPtFlag = 0;*/\
        MBUF_SET_FASTMBUF_NATPT(pstMBufTemp);\
        /*  MBUF_ZERO_TAG_LINK(pstMBufTemp); */ \
        MBUF_SET_MQC_CLASSNO(pstMBufTemp, 0);\
        MBUF_ASSIGN_VLANID(pstMBufTemp, 0);\
        MBUF_ASSIGN_PVCID(pstMBufTemp, 0);\
        MBUF_ASSIGN_ATMCLP(pstMBufTemp,0);\
        /*add by gwei for layer2 QOS project */\
        MBUF_ASSIGN_ORIGIN_RECV_IFINDEX(pstMBufTemp, 0);\
        /* Fixed for MPLS forwarding . some  time fail to ping */\
        (pstMBufTemp)->stUserTagData.stMplsPacketInfo.ulVrfIndex = 0;\
        (pstMBufTemp)->stUserTagData.stMplsPacketInfo.ulL3Info = 0;\
        /* Fixed By Rajesh 2004-03-26 ping is not working some times */\
        VOS_Mem_Set( (VOID *) (MBUF_GET_TAG_NETWORK_IP_PTR(pstMBufTemp)), 0 , sizeof(MBUF_IP_PACKET_INFO_S));\
        /*if (MBUF_GET_TAG_NETWORK_TYPE(pstMBufTemp) == AF_INET)\
        {\
            MBUF_IP_PACKET_INFO_S   *pstIpInfo;\
            \
            pstIpInfo = MBUF_GET_TAG_NETWORK_IP_PTR(pstMBufTemp);\
            pstIpInfo->ulLoopTimes = 0; \
            pstIpInfo->ulIpPktType = 0; \
            /*(pstMBufTemp)->stUserTagData.stMplsPacketInfo.ulVrfIndex = 0;*/\
        }\
        else *//*Changed by Evan 2004,04,15*/\
        /*{\
            MBUF_INIT_IP6PACKETINFO_FASTMBUF(pstMBufTemp);\
        }*/\
        VOS_DBGASSERT((pstMBufTemp)->stDataBlockDescriptor.pstNextDataBlockDescriptor == NULL);\
        VOS_DBGASSERT((pstMBufTemp)->ulTotalDataLength == (pstMBufTemp)->stDataBlockDescriptor.ulDataLength);\
        VOS_DBGASSERT((pstMBufTemp)->ulDataBlockNumber == 1);\
        (pstMBufTemp)->pstNextMBuf = NULL;\
        MBUF_INIT_FIREWALL_FASTMBUF(pstMBufTemp);\
    }
#endif
/* end of mayun */

/* 本宏的调用者必须关中断 */
#define FASTMBUF_INNER_ALLOC_MBUF(pstMBufTemp)\
{\
    if ( gulFastMBufCacheFreeNum > 0 )\
    {\
        (pstMBufTemp) = gstFastMBufCache[gulFastMBufCacheAllocIndex]; \
        gstFastMBufCache[gulFastMBufCacheAllocIndex] = NULL; \
        gulFastMBufCacheAllocIndex = (gulFastMBufCacheAllocIndex + 1) & FASTMBUF_MBUF_CACHE_MASK;\
        gulFastMBufCacheFreeNum--;\
    }\
    else \
    {\
        pstMBufTemp = NULL;\
    }\
}

/* 本宏的调用者必须关中断 */
#define FASTMBUF_ALLOC_MBUF(pstMBufTemp)\
{\
    if ( gulFastMBufCacheFreeNum > 0 )\
    {\
        (pstMBufTemp) = gstFastMBufCache[gulFastMBufCacheAllocIndex]; \
        gstFastMBufCache[gulFastMBufCacheAllocIndex] = NULL; \
        gulFastMBufCacheAllocIndex = (gulFastMBufCacheAllocIndex + 1) & FASTMBUF_MBUF_CACHE_MASK;\
        (pstMBufTemp)->stDataBlockDescriptor.pucData = ((UCHAR*)((pstMBufTemp)->stDataBlockDescriptor.pucDataBlock) + 300);\
        gulFastMBufCacheFreeNum--;\
    }\
    else \
    {\
        pstMBufTemp = NULL;\
    }\
}

/* 本宏的调用者必须关中断 */
#define FASTMBUF_FREE_MBUF(pstMBufTemp)\
{\
    gstFastMBufCache[gulFastMBufCacheFreeIndex] = (pstMBufTemp); \
    gulFastMBufCacheFreeIndex = (gulFastMBufCacheFreeIndex + 1) & FASTMBUF_MBUF_CACHE_MASK; \
    gulFastMBufCacheFreeNum++;  /* 空闲指针++ */ \
}


/* 本宏的调用者必须关中断 */
#if( VRP_OPTIM_MBUF == VRP_YES )
/* 为了不影响效率，只初始化了出接口索引。 by heqiangc, 2001-10-29 */
#define FASTMBUF_EXCHANGE_DATA_BLOCK_2048(pstMBufTemp, pucDataBlockM, ulDataBlockLengthM, \
    pucDataM, ulDataLengthM, ulReceiveIfnetIndexM, pDataBlockReturn)\
{\
    if ( gulFastMBufCacheFreeNum > 0 )\
    {\
        FASTMBUF_INNER_ALLOC_MBUF(pstMBufTemp);\
        \
        (pDataBlockReturn) = (pstMBufTemp)->stDataBlockDescriptor.pucDataBlock;\
        {/*检查该数据块是否合法，d12298 wuxiaoqian 2001/12/20*/\
            char chTemp;\
            chTemp = *((char*)pucDataBlockM-1);\
            *((char*)pucDataBlockM-1) = chTemp;\
        }\
        (pstMBufTemp)->stDataBlockDescriptor.pucDataBlock = (pucDataBlockM);\
        (pstMBufTemp)->stDataBlockDescriptor.ulDataBlockLength = (ulDataBlockLengthM);\
        (pstMBufTemp)->stDataBlockDescriptor.pucData = (pucDataM);\
        (pstMBufTemp)->stDataBlockDescriptor.ulDataLength = (ulDataLengthM);\
        (pstMBufTemp)->ulTotalDataLength = (ulDataLengthM);\
        \
        VOS_DBGASSERT((pstMBufTemp)->stDataBlockDescriptor.ulType == MBUF_TYPE_DATA);/*???*/\
        VOS_DBGASSERT((pstMBufTemp)->stDataBlockDescriptor.pstNextDataBlockDescriptor == NULL);\
        VOS_DBGASSERT((pstMBufTemp)->ulDataBlockNumber == 1);\
        VOS_DBGASSERT((pstMBufTemp)->pstNextMBuf == NULL);\
        \
        (pstMBufTemp)->stUserTagData.stCommonInfo.ulReceiveIfnetIndex = (ulReceiveIfnetIndexM);\
        (pstMBufTemp)->stUserTagData.stCommonInfo.ulSendIfnetIndex = 0;\
    }\
    else\
    {\
        (pDataBlockReturn) = (UCHAR *)VOS_Malloc(MID_FASTMBUF, FASTMBUF_PREALLOC_DATALEN1);\
        if (pDataBlockReturn)\
        {\
            MBUF_CREATE_BY_DATA_BLOCK(pstMBufTemp,\
                    pucDataBlockM,\
                    ulDataBlockLengthM,\
                    pucDataM,\
                    ulDataLengthM,\
                    ulReceiveIfnetIndexM,\
                    MID_FASTMBUF);\
            if (pstMBufTemp == NULL)\
            {\
                (pstMBufTemp) = 0;\
                (VOID)VOS_Free(pDataBlockReturn);\
                (pDataBlockReturn) = 0;\
            }\
        }\
        else\
        {\
            (pstMBufTemp) = 0;\
            (pDataBlockReturn) = 0;\
        }\
    }\
}
#else
#define FASTMBUF_EXCHANGE_DATA_BLOCK_2048(pstMBufTemp, pucDataBlockM, ulDataBlockLengthM, \
    pucDataM, ulDataLengthM, ulReceiveIfnetIndexM, pDataBlockReturn)\
{\
    if ( gulFastMBufCacheFreeNum > 0 )\
    {\
        FASTMBUF_INNER_ALLOC_MBUF(pstMBufTemp);\
        \
        (pDataBlockReturn) = (pstMBufTemp)->stDataBlockDescriptor.pucDataBlock;\
        {/*检查该数据块是否合法，d12298 wuxiaoqian 2001/12/20*/\
            char chTemp;\
            chTemp = *((char*)pucDataBlockM-1);\
            *((char*)pucDataBlockM-1) = chTemp;\
        }\
        (pstMBufTemp)->stDataBlockDescriptor.pucDataBlock = (pucDataBlockM);\
        (pstMBufTemp)->stDataBlockDescriptor.ulDataBlockLength = (ulDataBlockLengthM);\
        (pstMBufTemp)->stDataBlockDescriptor.pucData = (pucDataM);\
        (pstMBufTemp)->stDataBlockDescriptor.ulDataLength = (ulDataLengthM);\
        (pstMBufTemp)->ulTotalDataLength = (ulDataLengthM);\
        \
        VOS_DBGASSERT((pstMBufTemp)->stDataBlockDescriptor.ulType == MBUF_TYPE_DATA);/*???*/\
        VOS_DBGASSERT((pstMBufTemp)->stDataBlockDescriptor.ulOption == 0);\
        VOS_DBGASSERT((pstMBufTemp)->stDataBlockDescriptor.pstNextDataBlockDescriptor == NULL);\
        VOS_DBGASSERT((pstMBufTemp)->ulDataBlockNumber == 1);\
        VOS_DBGASSERT((pstMBufTemp)->pstNextMBuf == NULL);\
        \
        (pstMBufTemp)->stUserTagData.stCommonInfo.ulReceiveIfnetIndex = (ulReceiveIfnetIndexM);\
        (pstMBufTemp)->stUserTagData.stCommonInfo.ulSendIfnetIndex = 0;\
    }\
    else\
    {\
        (pDataBlockReturn) = (UCHAR *)VOS_Malloc(MID_FASTMBUF, FASTMBUF_PREALLOC_DATALEN1);\
        if (pDataBlockReturn)\
        {\
            MBUF_CREATE_BY_DATA_BLOCK(pstMBufTemp,\
                    pucDataBlockM,\
                    ulDataBlockLengthM,\
                    pucDataM,\
                    ulDataLengthM,\
                    ulReceiveIfnetIndexM,\
                    MID_FASTMBUF);\
            if (pstMBufTemp == NULL)\
            {\
                (pstMBufTemp) = 0;\
                (pDataBlockReturn) = 0;\
            }\
        }\
        else\
        {\
            (pstMBufTemp) = 0;\
            (pDataBlockReturn) = 0;\
        }\
    }\
}
#endif

/* 本宏的调用者必须关中断 */
#define FASTMBUF_APPEND_MEMORY_SPACE(pstMBufM, ulAppendLength, pucAppending, DataTypeM)\
{\
    MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor;\
    \
    if( (pstMBufM) != NULL)\
    {\
        pstDataBlockDescriptor = &( (pstMBufM)->stDataBlockDescriptor );\
        {\
            if( ((ULONG)(pstDataBlockDescriptor->pucData - pstDataBlockDescriptor->pucDataBlock) + (ulAppendLength) \
                + (pstDataBlockDescriptor->ulDataLength) ) <= pstDataBlockDescriptor->ulDataBlockLength )\
            {\
                (pucAppending) = (DataTypeM) (pstDataBlockDescriptor->pucData + pstDataBlockDescriptor->ulDataLength);\
                pstDataBlockDescriptor->ulDataLength += (ulAppendLength);\
                (pstMBufM)->ulTotalDataLength += (ulAppendLength);\
            }\
            else\
            {\
                (pucAppending) = NULL;\
            }\
        }\
    }\
    else\
    {\
        (pucAppending) = NULL;\
    }\
}

#if( VRP_OPTIM_MBUF == VRP_YES )
#define FASTMBUF_CLEAR_USERTAG(pstMBufM)\
{\
    MBUF_IP_PACKET_INFO_S   *pstIpInfo;\
    \
    (pstMBufM)->stUserTagData.stCommonInfo.ulFlag = 0;\
    pstIpInfo = MBUF_GET_TAG_NETWORK_IP_PTR(pstMBufM);\
    MBUF_ASSIGN_IP_INFO_LOOPTIMES( pstIpInfo, 0 ); \
    MBUF_ASSIGN_IP_INFO_PKT_TYPE( pstIpInfo, 0 );\
}
#else
#define FASTMBUF_CLEAR_USERTAG(pstMBufM)\
{\
    MBUF_IP_PACKET_INFO_S   *pstIpInfo;\
    \
    (pstMBufM)->stUserTagData.stCommonInfo.ulFlag = 0;\
    pstIpInfo = MBUF_GET_TAG_NETWORK_IP_PTR(pstMBufM);\
    pstIpInfo->ulLoopTimes = 0; \
    pstIpInfo->ulIpPktType = 0; \
}
#endif /* VRP_OPTIM_MBUF == VRP_YES */

extern ULONG FASTMBUF_Free( MBUF_S* pstMBuf );
extern VOID VOS_ChangeMID(VOID *ptr , ULONG newMid);
/*========guojianweu add 4K FAST MBUF 支持==2002-06-27 D12845===========**/
#if (VRP_MODULE_VOS_FAST_MBUF_4096 == VRP_YES)

#define FASTMBUF_PREALLOC_DATALEN2      4096    /* 预先申请的MBUF的大小 */

extern ULONG  gulFastMBufPreallocNum4096  ; /* Fast MBUF缓冲个数,2的整数倍 */
extern ULONG  gulFastMBufCacheMask4096  ;

#define   FASTMBUF_MBUF_CACHE_NUM4096  1024/* Fast MBUF缓冲个数,2的整数倍 */
#define   FASTMBUF_PREALLOC_MBUF_NUM4096 gulFastMBufPreallocNum4096 /* 预先申请的MBUF个数,小于FASTMBUF_MBUF_CACHE_NUM */
#define   FASTMBUF_MBUF_CACHE_MASK4096  gulFastMBufCacheMask4096  /* Fast MBUF缓冲个数的掩码 */


extern ULONG   gulFastMBuf4096Volume;
extern ULONG   gulFastMBufCacheFreeNum4096;
extern ULONG   gulFastMBufCacheFreeIndex4096;
extern ULONG   gulFastMBufCacheAllocIndex4096;
extern MBUF_S* gstFastMBufCache4096[FASTMBUF_MBUF_CACHE_NUM4096];



/* 本宏的调用者必须关中断 */
#define FASTMBUF_ALLOC_MBUF4096(pstMBufTemp)\
{\
    if ( gulFastMBufCacheFreeNum4096 > 0 )\
    {\
        (pstMBufTemp) = gstFastMBufCache4096[gulFastMBufCacheAllocIndex4096]; \
        gstFastMBufCache4096[gulFastMBufCacheAllocIndex4096] = NULL; \
        gulFastMBufCacheAllocIndex4096 = (gulFastMBufCacheAllocIndex4096 + 1) & FASTMBUF_MBUF_CACHE_MASK4096;\
        (pstMBufTemp)->stDataBlockDescriptor.pucData = ((UCHAR*)((pstMBufTemp)->stDataBlockDescriptor.pucDataBlock) + 300);\
        gulFastMBufCacheFreeNum4096--;\
    }\
    else \
    {\
        pstMBufTemp = NULL;\
    }\
}

/* 本宏的调用者必须关中断 */
#define FASTMBUF_FREE_MBUF4096(pstMBufTemp)\
{\
        gstFastMBufCache4096[gulFastMBufCacheFreeIndex4096] = (pstMBufTemp); \
        gulFastMBufCacheFreeIndex4096 = (gulFastMBufCacheFreeIndex4096 + 1) & FASTMBUF_MBUF_CACHE_MASK4096; \
        gulFastMBufCacheFreeNum4096++; /* 空闲指针++ */ \
}


/* 本宏的调用者必须关中断 */
/* 为了不影响效率，只初始化了出接口索引?*/
#define FASTMBUF_EXCHANGE_DATA_BLOCK_4096(pstMBufTemp, pucDataBlockM, ulDataBlockLengthM, \
    pucDataM, ulDataLengthM, ulReceiveIfnetIndexM, pDataBlockReturn)\
{\
    VOS_DBGASSERT(gulFastMBuf4096Volume);\
    VOS_DBGASSERT(ulDataBlockLengthM == FASTMBUF_PREALLOC_DATALEN2);\
    if ( gulFastMBufCacheFreeNum4096 > 0 )\
    {\
        (pstMBufTemp) = gstFastMBufCache4096[gulFastMBufCacheAllocIndex4096]; \
        gstFastMBufCache4096[gulFastMBufCacheAllocIndex4096] = NULL; \
        gulFastMBufCacheAllocIndex4096 = (gulFastMBufCacheAllocIndex4096 + 1) & FASTMBUF_MBUF_CACHE_MASK4096;\
        gulFastMBufCacheFreeNum4096--;\
        \
        (pDataBlockReturn) = (pstMBufTemp)->stDataBlockDescriptor.pucDataBlock;\
        \
        {/*检查该数据块是否合法，d12298 wuxiaoqian 2001/12/20*/\
            char chTemp;\
            chTemp = *((char*)pucDataBlockM-1);\
            *((char*)pucDataBlockM-1) = chTemp;\
        }\
        (pstMBufTemp)->stDataBlockDescriptor.pucDataBlock = (pucDataBlockM);\
        (pstMBufTemp)->stDataBlockDescriptor.ulDataBlockLength = (ulDataBlockLengthM);\
        (pstMBufTemp)->stDataBlockDescriptor.pucData = (pucDataM);\
        (pstMBufTemp)->stDataBlockDescriptor.ulDataLength = (ulDataLengthM);\
        (pstMBufTemp)->ulTotalDataLength = (ulDataLengthM);\
        (pstMBufTemp)->stDataBlockDescriptor.ulType = MBUF_TYPE_DATA;\
        \
        VOS_DBGASSERT((pstMBufTemp)->stDataBlockDescriptor.ulType == MBUF_TYPE_DATA);/*???*/\
        VOS_DBGASSERT((pstMBufTemp)->stDataBlockDescriptor.pstNextDataBlockDescriptor == NULL);\
        VOS_DBGASSERT((pstMBufTemp)->ulDataBlockNumber == 1);\
        VOS_DBGASSERT((pstMBufTemp)->pstNextMBuf == NULL);\
        \
        (pstMBufTemp)->stUserTagData.stCommonInfo.ulReceiveIfnetIndex = (ulReceiveIfnetIndexM);\
        (pstMBufTemp)->stUserTagData.stCommonInfo.ulSendIfnetIndex = 0;\
    }\
    else\
    {\
        (pDataBlockReturn) = (UCHAR *)VOS_Malloc(MID_FASTMBUF, FASTMBUF_PREALLOC_DATALEN2);\
        if (pDataBlockReturn)\
        {\
            MBUF_CREATE_BY_DATA_BLOCK(pstMBufTemp,\
                    pucDataBlockM,\
                    ulDataBlockLengthM,\
                    pucDataM,\
                    ulDataLengthM,\
                    ulReceiveIfnetIndexM,\
                    MID_FASTMBUF);\
            if (pstMBufTemp == NULL)\
            {\
                (pstMBufTemp) = 0;\
                (VOID)VOS_Free(pDataBlockReturn);\
                (pDataBlockReturn) = 0;\
            }\
        }\
        else\
        {\
            (pstMBufTemp) = 0;\
            (pDataBlockReturn) = 0;\
        }\
    }\
}

/*FASTMBUF_Free 中使用该宏 free 4K MBUF*/
#define FASTMBUF4096_FREE(pstMBuf)\
if (FASTMBUF_PREALLOC_DATALEN2 == pstMBuf->stDataBlockDescriptor.ulDataBlockLength)    \
    {\
       if (gulFastMBuf4096Volume == 0)/*判断是否打开?4096 FASTMBUF */\
       {\
          return MBUF_FAIL;\
       }\
       \
       if ( ( VOS_OK != VOS_Mem_GetRef(pstMBuf->stDataBlockDescriptor.pucDataBlock, &lRef ) )\
        || ( 1 != lRef ) )\
        {\
          return MBUF_FAIL;\
        }\
           \
        (VOID)VOS_SplImp(&imask);           /* 关中断 */\
        \
        if (gulFastMBufCacheFreeNum4096 >= FASTMBUF_PREALLOC_MBUF_NUM4096)\
        {\
          (VOID)VOS_SplX(imask);            /* 开中断 */\
          return MBUF_FAIL;\
        }\
        \
       VOS_ChangeMID((VOID *)pstMBuf, MID_FASTMBUF);\
       VOS_ChangeMID((VOID *)(pstMBuf->stDataBlockDescriptor.pucDataBlock), MID_FASTMBUF);\
              \
        SET_MBUF_FASTMBUF_MBUF(pstMBuf); \
        FASTMBUF_FREE_MBUF4096(pstMBuf); \
        (VOID)VOS_SplX(imask);          /* 开中断 */ \
        return MBUF_OK;  \
      \
    } 

extern ULONG FASTMBUF4096_Init( VOID );

#endif /*End of (R8070_4096FASTMBUF == VRP_YES)*/
/*===========4K FAST MBUF END ===========D12845=====================*/

#endif /* end of _FAST_MBUF_H_ */

#ifdef __cplusplus
}
#endif /* end of __cplusplus */



