/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ping_pub.h
*
*  Project Code: VISP1.5
*   Module Name: ping
*  Date Created: 2000/06/21
*        Author: luyao(60000758)
*   Description: PING模块用到的数据结构的声text件 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-4-28   luyao(60000758)  Creat the first version.
*  2006-04-27  luyao            根据编程规范，对文件进行规范化整理
*  2006-05-10  luyao(60000758)  为支持ARM CPU字节对齐特性，修改结构。
*
*******************************************************************************/

#ifndef _PING_PUB_H_
#define _PING_PUB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/ping/include/ping_api.h"

#define PING_6             1
#define PING_4             0
#define PING_Vrf_YES   1
#define PING_Vrf_NO    0
#define PING_SUCESS   -1
#define PING_ERROR    -2
typedef struct tagPINGModuleInfo  {
    ULONG ulModID;        /* Module id;*/
    ULONG ulSubModID;     /* Sub module id;*/
} PING_MOD_INFO_S;


/*------------------------------------------------------------------------*\
* ip 数据报头结构
\*------------------------------------------------------------------------*/
typedef struct tagPingIP    
{
#if VRP_LITTLE_ENDIAN == VRP_YES 
        UCHAR  ucIP_hl : 4 ;               /* header length                    */
        UCHAR  ucIP_v : 4 ;                /* version                          */
#endif
#if VRP_BIG_ENDIAN == VRP_YES
        UCHAR ucIP_v : 4 ;                 /* version                          */
        UCHAR ucIP_hl : 4 ;                /* header length                    */
#endif
        UCHAR ucIP_tos ;                   /* Type of service                  */
        USHORT usIP_len ;                  /* Total packet length              */
        USHORT usIP_id ;                   /* Datagram identification          */
        USHORT usIP_off ;                  /* Fragment offset                  */
        UCHAR ucIP_ttl ;                   /* Time to live                     */
        UCHAR ucIP_p ;                     /* Protocol                         */
        USHORT usIP_sum ;                  /* Checksum                         */
        INADDR_S stIp_src ;                /* Source address                   */
        INADDR_S stIp_dst ;                /* Destination address              */
        
 } PingIP_S;

typedef struct tagPING_OUTPUT_S
{
   ULONG    ulKindID      ;         /* ulFlagID= PING_PRINT  :only display string   */
   CHAR     szHostname[IP_HOSTNAME_LEN + 1] ;  /* CLI_HOSTNAME_LENGTH */
   UCHAR    ucPadding_1[4-((IP_HOSTNAME_LEN + 1)%4)]; 
   ULONG    lDatalen ;
   CHAR     szStr[100];             /*通用*/
   LONG     lResult;                /*发送的结果*/
   ULONG    ulTransmitted ;         /* sequence # for outbound packets = #sent    */
   ULONG    ulReceived ;            /* # of packets we got back                   */
   ULONG    ulRepeats ;             /* number of duplicates                       */
   CHAR     szFmt [11] ;    
   UCHAR    ucPadding_2; 
   ULONG    ulTmin  ;               /* minimum round trip time                    */
   ULONG    ulTmax ;                /* maximum round trip time                    */
   ULONG    ulAvg;
   UCHAR    pucC,pucD ;
   UCHAR    icmp_chCode;            /* type sub code  */
   UCHAR    ucPadding_3; 
   struct tagINADDR stGwAddr;       /* ICMP_REDIRECT  */
   UCHAR    ih_chPPtr;              /* ICMP_PARAMPROB */
   UCHAR    ucPadding_4[3]; 
   PingIP_S *pstIp   ;              /* ip head  */
   ULONG     ulPinKind ;            /* 0: ipv4 address 1: ipv6 address */
} PING_OUTPUT_S;
   
typedef  LONG (*pf_Output)(PING_OUTPUT_S* pstOutput,ULONG ulExecID);
typedef  ULONG (*pf_isstop)(ULONG ulExecID);
/*------------------------------------------------------------------------*\
* 回调 数据结构
\*------------------------------------------------------------------------*/
typedef struct tagPingCallbackSet
{
     LONG  (*pfPING_Output)(PING_OUTPUT_S* pstOutput,ULONG ulExecID);
     ULONG (*pfPING_UserStop)(ULONG ulExecID);
}PING_CALLBACK_SET_S;

#ifdef __cplusplus
}
#endif

#endif

