/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              trrt_pub.h
*
*  Project Code: VISP1.5
*   Module Name: Traceroute Module 
*  Date Created: 2003-07-14
*        Author: Suraj( )
*   Description: TRRT模块宏定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2003-07-14  Suraj( )             Creat the first version.
*  2006-05-10  luyao(60000758)      为支持ARM CPU字节对齐特性，修改结构。
*
*******************************************************************************/

#ifndef _TRRT_PUB_H_
#define _TRRT_PUB_H_
#ifdef __cplusplus
extern "C" {
#endif

/***********************************************
 *   常量                                      *
 ***********************************************/
#define TRRT_6                   1 
#define TRRT_4                   0
#define VRF_YES                  1 
#define VRF_NO                   0

#define SID_TRRT_STAT            1  /* TraceRoute统计信息结构体TCPIP_TRRT_STAT_S */

/***********************************************
 *    回 调 函 数 参 数 数 据 结 构            *
 ***********************************************/

typedef struct tagTRRT_RESULT_S
{
    ULONG  ulInfoID   ;               /* 指明信息类型 */
    CHAR   *szHostname;
    LONG   lMaxTTL ;
    CHAR   szStr[80];                  
    LONG   lPackLen;                  /* 发送的结果 */
    ULONG  ulTransmitted;             /* sequence # for outbound packets = #sent */
    ULONG  ulReceived ;               /* # of packets we got back */
    ULONG  ulRepeats ;                /* number of duplicates */
    CHAR   szFmt[LEN_64]     ;     
    ULONG  ulTmin  ;                  /* minimum round trip time */
    ULONG  ulTmax ;                   /* maximum round trip time */
    ULONG  ulAvg;
    UCHAR  ucType,ucCode ;
    UCHAR  icmp_chCode;               /* type sub code */
    UCHAR  ucTos;                     /* IP首部TOS字段值 */
    struct tagINADDR stGwAddr;        /* ICMP_REDIRECT */
    UCHAR  ih_chPPtr;                 /* ICMP_PARAMPROB */
    UCHAR  ucPadding_2[3]; 
    LONG   lOptions;
    ULONG  ulFlag    ;                /* trrt4  or trrt6 */
    union
    {
        struct tagTrrt4
        {
            struct sockaddr_in stFrom4;
            INADDR_S    stDst4;     /* Destination address */
        }Trrt4_S;
        struct  tagTrrt6
        {
            SOCKADDR_IN6_S stFrom6;
            IN6ADDR_S   stDst6;
        }Trrt6_S;
    }Trrt_Un;
 #define   trrt_stDst4       Trrt_Un.Trrt4_S.stDst4
 #define   trrt_stDst6       Trrt_Un.Trrt6_S.stDst6
 #define   trrt_stFrom4    Trrt_Un.Trrt4_S.stFrom4
 #define   trrt_stFrom6    Trrt_Un.Trrt6_S.stFrom6

    /* VISP向产品输出TraceRoute统计信息需求新增 */
    ULONG ulHops;        /* 当前跳数 */
    ULONG ulQueryId;     /* 针对当前跳数的尝试次数 */
    ULONG ulMtu;         /* MTU值 */
} TRRT_RESULT_S;

/***********************************************
 *    回调函数数据结构                         *
 ***********************************************/
typedef struct tagTRRT_SH_CALLBACK_S
{
    VOID   (*pfTRRT_OutputResult)(ULONG ulExecID, TRRT_RESULT_S *pstOutput);
    ULONG  (*pfTRRT_IsUserStop)(ULONG ulExecID);
}TRRT_SH_CALLBACK_S;

typedef struct tagTrrtComModuleInfo
{
    ULONG  ulModID;
    ULONG ulSubModID;    
}TRRT_MOD_INFO_S;


/*========================================================================*/
/*    MACRO and CONST of tracert                                          */
/*========================================================================*/

#define TRACERT_MAXHOSTNAMELEN  IP_HOSTNAME_LEN+1
#define TRACERT_MY_IDENT        0xabcd
#define TRACERT_MAXRCVDATALEN  512            /* Maximum length of data that can be received */

#define TRACERT_TIME_OUT        5000          /*Timeout in Milliseconds*/
#define TRACERT_PROBE_COUNT     3             /*NUmber of probes*/
#define TRACERT_MIN_TTL         1             /*Minimum Hop Limit*/  
#define TRACERT_MAX_TTL         30            /*Default max Hop Limit*/
#define TRACERT_MAXIMAL_TTL     255           /*Max Hop Limit*/
#define TRACERT_PORT_NUMBER     52889         /*Destination Port Number*/
#define TRACERT_F_NUMERIC       0x02
#define TRACERT_F_VERBOSE       0x04

/*Error values */
#define TRACERT_STOP -2             /* used to stop the traceroute execution from the CLI */
#define TRACERT_MINRESPLEN 12       /* Min length of the response packet to be a valid packet */

/*SYSTRACE related options*/
#define SYSTRC_IPV6_TRACERT6_BASE 00
#define IPV6_TRACERT6_CMD ((SYSTRC_IPV6_TRACERT6_BASE << 8) + 010)
#define IPV6_TRACERT6_PKTPROC ((SYSTRC_IPV6_TRACERT6_BASE << 8) + 011)
#define IPV6_TRACERT6_IO ((SYSTRC_IPV6_TRACERT6_BASE << 8) + 012)

#define TRACERT_ERR_NOHOPLIMIT     -1        /*return value for illegal hoplimit*/

/*traceroute packet errors.*/
#define TRACERT_PKTERROR            0          /*Incorrect packet received.*/
#define TRACERT_PKTTIME_EXCEEDED   -1   /*ICMP6 time exceed response received.*/

/*String Size Changed from 19 to 31 by Prasad BugID:BYADO5214 on 18/12/2003*/
/*To Make the it Consistent with VRFNAME Size in other Modules*/
#define TRACERT_VRFNAMELEN      31 

/* TRRT使用的SID统一在此定义 */

#define SID_TRRT_SENDBUF           1  /* traceroute报文 */

/* end of SID */

#ifdef __cplusplus
}
#endif

#endif
