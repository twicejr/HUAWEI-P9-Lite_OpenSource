/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ping_type.h
*
*  Project Code: VISP1.5
*   Module Name: ping
*  Date Created: 2006-4-28
*        Author: luyao(60000758)
*   Description: 定义ping模块用到的数据结构
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-4-28  luyao(60000758)   Creat the first version.
*  2006-04-27 luyao             根据编程规范，对文件进行规范化整理
*
*******************************************************************************/


#ifndef _PING_TYPE_H_
#define _PING_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagPingParam
{
    LONG      lOptions ;                     /* socket option */
    ULONG     lDatalen ;                     /* 发送的报文长度 */
    LONG      lSocket ;                      /* socket file descriptor */

    CHAR      szHostName[IP_HOSTNAME_LEN+1]; /*  系统网络名称 */
    UCHAR     ucPadding_1[4-((IP_HOSTNAME_LEN+3)%4)];
    USHORT    usIdent ;                      /* the identity of the icmp packet */
    ULONG     ulMore;                        /* 报文发送时间间隔,单位:ms*/

    union
    {
        struct  tagPing6
        {
            SOCKADDR_IN6_S st6Whereto ;      /* for ipv6  */
            IN6ADDR_S stSourAddr;            /* 出接口的源地址 */
            IN6ADDR_S stNextHop;             /* 下一跳地址 */
            ULONG     ulHopLimit;            /* HOP limit */
            ULONG     ulOutIfnetIndex;       /* 出接口索引 */
            CHAR      szInterface[MAX_IF_NAME_LENGTH + 1];  /* character array for interface name input */
            ULONG     ulTos6;                 /* Tos */
            ULONG     ulForeverFlag;          /* 不间断ping6, 1表示不间断ping, 0该字段无意义 */
            ULONG     ulVrf6Index;             /* Vrf6Index */
            ULONG     ulVrf6Flag ;
        }Ping6_S;
        struct  tagPing4
        {
           struct sockaddr_in stWhereto ;    /* for ipv4 */
           ULONG     ulVrfFlag ;             /* PING_Vrf_NO or  PING_Vrf_YES */
           /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-05,内部数据结构,使用index,将名称废弃   */
           /* CHAR      *szVrfName; */             /* 私网标识名 */
           /* End: VISP1.7C03 VRF wangchengyang,2009-02-05 */
           ULONG     ulSourceAddr;           /* 出接口的源地址 */
           ULONG     ulIfIndex;              /* 出接口索引 */
           ULONG     ulRdqnv[6];             /* Flag of Parameter (-R -d -q -n -v -t) have been specified */
           ULONG     ulTTL;                  /* 设置的TTL值 */
           ULONG     ulTos;                  /* 设置的TOS值 */

           /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-05 */
           ULONG     ulVrfIndex;             /* VrfIndex */
           /* End: VISP1.7C03 VRF wangchengyang,2009-02-05 */
           ULONG     ulNextHop;              /* 指定下一跳*/
           USHORT    usDF;                   /* 为0表示不设置DF标志，为1则设置DF标志，默认为0 */
           UCHAR     ucRes[2];
        }Ping4_S;

    }Ping_Un;

#define Ping6_st6Whereto             Ping_Un.Ping6_S.st6Whereto
#define Ping6_stSourAddr             Ping_Un.Ping6_S.stSourAddr
#define Ping6_stNextHop              Ping_Un.Ping6_S.stNextHop
#define Ping6_ulHopLimit             Ping_Un.Ping6_S.ulHopLimit
#define Ping6_ulOutIfnetIndex        Ping_Un.Ping6_S.ulOutIfnetIndex
#define Ping6_szInterface            Ping_Un.Ping6_S.szInterface
#define Ping6_ulTos6                 Ping_Un.Ping6_S.ulTos6
#define Ping6_ulForeverFlag          Ping_Un.Ping6_S.ulForeverFlag
#define Ping6_ulVrf6Index             Ping_Un.Ping6_S.ulVrf6Index
#define Ping6_ulVrfF6lag              Ping_Un.Ping6_S.ulVrf6Flag

#define Ping4_stWhereto              Ping_Un.Ping4_S.stWhereto
#define Ping4_ulVrfFlag              Ping_Un.Ping4_S.ulVrfFlag
/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-05,内部数据结构PingParam_S,使用index,将名称废弃
#define Ping4_szVrfName              Ping_Un.Ping4_S.szVrfName
End: VISP1.7C03 VRF wangchengyang,2009-02-05 */
#define Ping4_ulIfIndex              Ping_Un.Ping4_S.ulIfIndex
#define Ping4_ulRdqnv                Ping_Un.Ping4_S.ulRdqnv
#define Ping4_ulTTL                  Ping_Un.Ping4_S.ulTTL
#define Ping4_ulTos                  Ping_Un.Ping4_S.ulTos
#define Ping4_ulSourceAddr           Ping_Un.Ping4_S.ulSourceAddr

/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-05 */
#define Ping4_ulVrfIndex             Ping_Un.Ping4_S.ulVrfIndex
/* End: VISP1.7C03 VRF wangchengyang,2009-02-05 */
#define Ping4_ulNextHop              Ping_Un.Ping4_S.ulNextHop
#define Ping4_usDF                   Ping_Un.Ping4_S.usDF


/*--------------------------------------------------------------------*\
 * counters
\*--------------------------------------------------------------------*/
    ULONG     ulPackets ;         /* max packets to transmit                    */
    ULONG     ulReceived ;        /* # of packets we got back                   */
    ULONG     ulRepeats ;         /* number of duplicates                       */
    ULONG     ulTransmitted ;     /* sequence # for outbound packets = #sent    */
    ULONG     ulTimeout  ;        /* interval between packets                 */

/*--------------------------------------------------------------------*\
 * timing
\*--------------------------------------------------------------------*/
    LONG      lTiming ;           /* flag to do timing                         */
    ULONG     ulTmin  ;           /* minimum round trip time                  */
    ULONG     ulTmax ;            /* maximum round trip time                  */
    ULONG     ulTsum ;            /* sum of all times, for doing average      */

    ULONG     lMx_dup_ck ;        /* 接收列表中可接收报文的最大数量 */
    CHAR      cRcvd_tbl[PIN_MAX_DUP_CHK / 8] ;  /* 重复报文的标志位 */
    CHAR      szFillString[PIN_PADLEN + 1] ;  /* 报文的填充值 */
    UCHAR     ucPadding_2[3];     /* 为支持ARM CPU填充数据结构 */
    UCHAR     *szOutpack ;        /* 发送报文指针 */

} PingParam_S,Ping6Param_S;




#ifdef __cplusplus
}
#endif

#endif  /*end of _PING6_FUNC_H_*/

