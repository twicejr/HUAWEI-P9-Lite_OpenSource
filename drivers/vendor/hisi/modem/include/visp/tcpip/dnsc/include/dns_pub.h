/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dns_pub.h
*
*  Project Code: VISP1.5
*   Module Name: DNSC Module  
*  Date Created: 2002-11-25
*        Author: Sun Yanfeng(32084)
*   Description: 这个头文件定义VISP中DNS模块的数据结构  
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2002-11-25  Sun Yanfeng(32084)   Creat the first version.
*  2006-05-10  lu yao(60000758)     为支持ARM CPU字节对齐特性，修改结构。
*
*******************************************************************************/

#ifndef _DNS_PUB_H_
#define _DNS_PUB_H_

#ifdef  __cplusplus
extern "C" {
#endif

#define DNS_HOSTBUF_LEN 8192                 /* 同步D21代码  x36530  2004-9-7  */

/* 域名服务器中CASHE的最大个数*/
#define DNS_DOMAIN_CACHE_NUM    50

extern ULONG g_ulDnscExecInforIndex;


#define pDnsInfo Inf_Dnsc_En

/* check if user press Ctrl+C */
#define   TRRT_CTRL_C                      1
#define   TRRT_NO_BREAK                    0

typedef struct tagDnscOutString
{
   ULONG ulErrNo;   
   CHAR  szIPAddrBuf[50] ; 
   UCHAR ucPadding[2]; 
}DnscOutString;

typedef struct tagDNSCCallbackSet
{ 
    ULONG (*pfDNS_OutputResult)(ULONG ulExecID, DnscOutString *pstOutput);
    ULONG (*pfDNS_Isstop)(ULONG ulExecID);
}DNSC_CALLBACK_SET_S;

typedef  VOID (*tagDNS_SendICDebugInfo)(CHAR* szString );

typedef struct tagDnsComModuleInfo
{
    ULONG  ulModID;
    ULONG ulSubModID;    
}DNS_MOD_INFO_S;

typedef struct tagSetServer_S
{
    ULONG  ulNoFlag;           /* 0:增加域名服务器  非0:删除域名服务器 */
    ULONG  ulServerIpFlag ;    /* 是否指定了域名服务器地址: 当ulNoFlag=1,且此处为０，则删除所有的域名服务器 */
    ULONG  ulIpv6Flag;                     
    union
    {
        ULONG  ulServerIp;                        /* Ipv4地址 */
        struct tagDns6
        {
            IN6ADDR_S stServerIp6;                /* Ipv6地址 */
            CHAR szIfName[MAX_IF_NAME_LENGTH + 1];/* 接口名 */
        }Dns6;
    }Dns_Un;

#define Dns6_stServerIp6    Dns_Un.Dns6.stServerIp6
#define Dns6_szIfName       Dns_Un.Dns6.szIfName
#define Dns4_ulServerIp     Dns_Un.ulServerIp
}SetServer_S ;


/*************sunyanfeng added*************/
/* add from sock_pub.h */
typedef struct  DNS_CACHE 
{
    CHAR    szHostName[IP_HOSTNAME_LEN+ 1];         /* official name of host */ /* 10->21 by mayun 20010608 */
    UCHAR   ucPadding[4-((IP_HOSTNAME_LEN+ 1)%4)];
    CHAR    h_aliases[4][IP_HOSTNAME_LEN+1];        /* alias list */
    LONG    laddrtype;                              /* indicates the address type stored in szaddr*/
    CHAR    szAddr[20];                             /* list of addresses */
    struct  DNS_CACHE *pstPrev;     
    struct  DNS_CACHE *pstNext; 
    ULONG   ulTTL;          /*the number of the TTL,which mean what time should hold the list */        
}DNS_CACHE_S;              

typedef struct  DNS_Total_Cache 
{
    ULONG   ulTotalCacheNum;                               /* the number of the cache */
    struct  DNS_CACHE  *pstDNS_CaEntryHead;  
    struct  DNS_CACHE  *pstDNS_CaEntryTail;
}DNS_Total_Cache_S;

typedef struct tagIPV6_DNS_SERVADDRINFO
{   
    IN6ADDR_S stIpAddr;
    ULONG     ulIfIndex;
    CHAR      szInterfaceName[DNS_MAX_INTERFACE_NAME_LEN + 1];   
}IPV6_DNS_SERVADDRINFO_S;

/*dns域名信息结构*/
typedef struct  tagDomainInfo
{
     ULONG  ulDomainServer[DNS_DOMAIN_SERVER_NUM];
     IPV6_DNS_SERVADDRINFO_S stDomainServer6[DNS_DOMAIN_SERVER_NUM];
     CHAR   szDomainList[DNS_DOMAIN_LIST_NUM][DNS_DOMAIN_LIST_NAME_LENGTH + 1];
     UCHAR  ucPadding[2]; 
}DomainInfo_S;

typedef struct DNSC_Serv_Info
{
UCHAR                   ucIPType;   /* ipv4 or ipv6 */ 
union {
    ULONG ulIP4Addr;
    IPV6_DNS_SERVADDRINFO_S stIP6ServInfo;
}servAddr;
} DNSC_Serv_Info_S;

#ifdef  __cplusplus
}
#endif

#endif

