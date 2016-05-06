/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              trrt_type.h
*
*  Project Code: VISP1.5
*   Module Name: Traceroute Module 
*  Date Created: 2003-07-14
*        Author: suraj( )
*   Description: TRRT模块主要结构体声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2003-07-14  suraj( )         Creat the first version.
*  2006-05-10  luyao(60000758)  为支持ARM CPU字节对齐特性，修改结构。
*
*******************************************************************************/

#ifndef _TRRT_TYPE_H_
#define _TRRT_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif


typedef struct tagOutData
{
    UCHAR          ucSeq;            /* sequence number of this packet */
    UCHAR          ucTTL;            /* ucTTL packet left with */
    UCHAR          ucPadding[2]; 
    struct timeval         stTv;     /* time packet left */
}OutData_S;
typedef struct tagTraceRoute
{
    LONG                 lOptions;   /*Used to set the Display mode for the traceroute. Can be TRACERT6_F_VERBOSE 
                                        TRACERT6_F_NUMERIC for future enhancement - verbose option.*/
    LONG                 lTimeout;   /*Timeout for wait period*/
    LONG                 lProbes;    /*NUmber of probes*/
    LONG                 lMinTTL;    /* Minimum Hop Limit*/
    LONG                 lMaxTTL;    /*Max Hop Limit*/
    USHORT               usPortNum;  /*Destination Port Number*/
    USHORT               usIdent;    /*Identifier*/
    LONG                 lPackLen;   /* total length of packet */
    UCHAR                pucPacket[TRACERT_MAXRCVDATALEN]; /* 512 bytes*/
    LONG                 lRcvSock;   /* receive (icmp) socket file descriptor */
    LONG                 lSndSock;   /* send (udp) socket file descriptor */
    CHAR                *szHostName;
    union
        {
            struct tagTrrt6_S
            {
                LONG                  lRcvHopLimit;      /* Receive Hoplimit for the ICMPv6 reply*/
                IP6_PKTINFO_S         stRcvPktInfo;      /* Receive PktInfo for the ICMPv6 
                                                            reply to get destination address*/
                SOCKADDR_IN6_S        stWhereTo6;       
            }Trrt6_S;
            
            struct tagTrrt4_S
            {
                struct sockaddr_in     stWhereTo ;         
            }Trrt4_S;
        }Trrt_Un;
    
#define trrt_stWhereTo              Trrt_Un.Trrt4_S.stWhereTo
#define trrt_lRcvHopLimit          Trrt_Un.Trrt6_S.lRcvHopLimit
#define trrt_stRcvPktInfo           Trrt_Un.Trrt6_S.stRcvPktInfo
#define trrt_stWhereTo6            Trrt_Un.Trrt6_S.stWhereTo6

}TraceRouteParam_S;


#ifdef __cplusplus
}
#endif

#endif
