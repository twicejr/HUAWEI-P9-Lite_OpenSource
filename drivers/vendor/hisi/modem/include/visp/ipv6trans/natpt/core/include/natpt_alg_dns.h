/************************************************************************
 *
 *    Copyright 2003, Huawei Technologies Co. Ltd  India Institute  
 *                     ALL RIGHTS RESERVED                           
 *                                                 
 *----------------------------------------------------------------------*
 *
 *                             natpt_alg_dns.h
 *
 *  Project Code:       VRPv5 
 *  Create Date:        2003-7-9
 *  Author:             Desh   (VRPv5 IPv6 Team) 
 *  Document:          This file contains all the definitions for the DNS ALG
 *  Function Description:
 *  
 *----------------------------------------------------------------------*
 *  Modification History 
 *  DATE        NAME             DESCRIPTION
 *  
 *  
 ************************************************************************/


#ifndef _NATPT_ALG_DNS_H
#define _NATPT_ALG_DNS_H


#ifdef  __cplusplus
extern  "C"{
#endif


/*----------------------------------------------*
 * Header Files                
 *----------------------------------------------*/


 
#define NATPT_DNS_ALG_REFUSE_REQUEST 1 
#define NATPT_DNS_ALG_MAX_DNS_PKT_SIZE 1500 
#define NATPT_DNS_ALG_TYPE_AAAA 11
#define NATPT_DNS_ALG_MAXDNAME 1025
#define NATPT_DNS_ALG_END_OF_INPUT 111
#define NATPT_DNS_ALG_TTL_FOR_MAP 0
#define NATPT_DNS_ALG_MAXCDNAME 255
#define NATPT_DNS_ALG_INDIR_MASK 0xc0  
#define NATPT_DNS_ALG_MAXLBL 63
#define NATPT_MAX_DNPTR 20

#define  NATPT_ALG_DNSREQUEST  0
/*----------------------------------------------*
 * External Variables            
 *----------------------------------------------*/
 


 
/*----------------------------------------------*
 * Global Variables    
 *----------------------------------------------*/

/*----------------------------------------------*
 * Data Structures
 *----------------------------------------------*/

typedef struct tagNATPTGDnsQueryPara
{
    USHORT usQueryLen;
    USHORT usQueryType;
    USHORT usQueryClass; 
}NATPTGDnsQueryPara_S;









/*----------------------------------------------*
 * Functions
 *----------------------------------------------*/

LONG NATPTG_DNS_GetQueryPara(UCHAR* pucQueryBuff, USHORT usBuffLen, NATPTGDnsQueryPara_S *pstQueryPara) ;
ULONG   NATPT_DNS_ALG_TranslateMsg(MBUF_S *pMBufIn, MBUF_S **pMBufOut, UCHAR ucDir,ULONG ulHdrLen);
ULONG NATPT_DNS_ALG_ProcessQuery(UCHAR **ppucInQuery, UCHAR **ppucOutQuery, USHORT usQdCnt, UCHAR ucDir) ;
ULONG NATPT_DNS_ALG_ProcessRR (UCHAR **ppucInQuery, UCHAR **ppucOutQuery,USHORT usRrCnt, UCHAR ucDir) ;
ULONG NATPT_DNS_ALG_Translate_ReverseName (UCHAR* pucName,  UCHAR ucDir) ;
ULONG NATPT_DNS_ALG_Get_V4Addr( UCHAR *pucName, ULONG *pulV4Addr) ;
ULONG NATPT_DNS_ALG_Get_V6Addr(UCHAR *pucName, IN6ADDR_S *pstV6Addr) ;
ULONG NATPT_DNS_ALG_Create_V4_ReverseName(UCHAR *pucName, ULONG *pulV4Addr) ;
ULONG NATPT_DNS_ALG_Create_V6_ReverseName(UCHAR *pucName, IN6ADDR_S *pstV6Addr) ;
ULONG NATPT_DNS_ALG_Translate_RData(USHORT usRRType, UCHAR * pucRData, UCHAR * pucOutRR,  USHORT *pusOutRdLen , ULONG *pulOutRRttl) ;
LONG NATPT_DNS_ALG_dn_expand(const UCHAR *pucMsg, const UCHAR *pucEomOrig, const UCHAR *pucComp_dn, CHAR *pcExp_dn, LONG lLength) ;
LONG NATPT_DNS_ALG_dn_comp(const CHAR *pcExp_dn, UCHAR *pucComp_dn, LONG lLength, UCHAR **ppucDnptrs, UCHAR **ppucLastdnptr) ;
LONG NATPT_DNS_ALG_dn_find(UCHAR *pucExp_dn, UCHAR *pucMsg, UCHAR **ppucDnptrs, UCHAR **ppucLastdnptr) ;

ULONG NATPT_DNS_ALG_IPv4toIPv6(MBUF_S *pstMBufIn, MBUF_S **pstMBufOut, VOID* pstHash,USHORT usHdrLen,UCHAR ucProtocol) ;
ULONG NATPT_DNS_ALG_IPv6toIPv4(MBUF_S *pstMBufIn, MBUF_S **pstMBufOut, VOID* pstHash,USHORT usHdrLen,UCHAR ucProtocol) ;
LONG NATPT_Mklower (LONG lCh);
#define     NATPTG_DNS_QNAME_COMPRESS(QName)        QName & 0xC0
#define NATPT_GET_UDP_HDR_INFO(usUdpLen, pstUdpHdr, \
                    pucPayload, ulPayloadLen) \
{\
    pucPayload      = (UCHAR *)pstUdpHdr + sizeof(UDPHDR_S); \
    usUdpLen       = (USHORT)VOS_NTOHS(pstUdpHdr->uh_sULen); \
    ulPayloadLen    = (ULONG)(usUdpLen - sizeof(UDPHDR_S)); \
}


typedef struct tagDNSHDR_S 
{
    USHORT  usID ;      /* query identification number */
#if VRP_BIG_ENDIAN == VRP_YES
            /* fields in third byte */
    USHORT  usQR: 1;        /* response flag */
    USHORT  usOpcode: 4;    /* purpose of message */
    USHORT  usAA: 1;        /* authoritive answer */
    USHORT  usTC: 1;        /* truncated message */
    USHORT  usRD: 1;        /* recursion desired */
            /* fields in fourth byte */
    USHORT  usRA: 1;        /* recursion available */
    USHORT  usUnused :1;    /* unused bits (MBZ as of 4.9.3a3) */
    USHORT  usAD: 1;        /* authentic data from named */
    USHORT  usCD: 1;        /* checking disabled by resolver */
    USHORT  usRCode :4; /* response code */
#endif
#if VRP_LITTLE_ENDIAN == VRP_YES
            /* fields in third byte */
    USHORT  usRD :1;        /* recursion desired */
    USHORT  usTC :1;        /* truncated message */
    USHORT  usAA :1;        /* authoritive answer */
    USHORT  usOpcode :4;    /* purpose of message */
    USHORT  usQR :1;        /* response flag */
            /* fields in fourth byte */
    USHORT  usRCode :4; /* response code */
    USHORT  usCD: 1;        /* checking disabled by resolver */
    USHORT  usAD: 1;        /* authentic data from named */
    USHORT  usUnused :1;    /* unused bits (MBZ as of 4.9.3a3) */
    USHORT  usRA :1;        /* recursion available */
#endif
            /* remaining bytes */
    USHORT  usQDcount ; /* number of question entries */
    USHORT  usANcount ; /* number of answer entries */
    USHORT  usNScount ; /* number of authority entries */
    USHORT  usARcount ; /* number of resource entries */
} DNSHDR_S;



/*---------------------------------------------*/
#define GETSHORT        NS_GET16
#define PUTSHORT       NS_PUT16
#define GETLONG         NS_GET32
#define PUTLONG        NS_PUT32
 
#define T_A         ns_t_a             /******************************************/
#define T_NS        ns_t_ns            /******************************************/
#define T_MD        ns_t_md            /******************************************/
#define T_MF        ns_t_mf            /******************************************/
#define T_CNAME     ns_t_cname         /******************************************/
#define T_SOA       ns_t_soa           /******************************************/
#define T_MB        ns_t_mb            /******************************************/
#define T_MG        ns_t_mg            /******************************************/
#define T_MR        ns_t_mr            /******************************************/
#define T_NULL      ns_t_null          /******************************************/
#define T_WKS       ns_t_wks           /******************************************/
#define T_PTR       ns_t_ptr           /******************************************/
#define T_HINFO     ns_t_hinfo         /******************************************/
#define T_MINFO     ns_t_minfo         /******************************************/
#define T_MX        ns_t_mx            /******************************************/
#define T_TXT       ns_t_txt           /******************************************/
#define T_RP        ns_t_rp            /******************************************/
#define T_AFSDB     ns_t_afsdb         /******************************************/
#define T_X25       ns_t_x25           /******************************************/
#define T_ISDN      ns_t_isdn          /******************************************/
#define T_RT        ns_t_rt            /******************************************/
#define T_NSAP      ns_t_nsap          /******************************************/
#define T_NSAP_PTR  ns_t_nsap_ptr      /******************************************/
#define T_SIG       ns_t_sig           /******************************************/
#define T_KEY       ns_t_key           /******************************************/
#define T_PX        ns_t_px            /******************************************/
#define T_GPOS      ns_t_gpos          /******************************************/
#define T_AAAA      ns_t_aaaa          /******************************************/
#define T_LOC       ns_t_loc           /******************************************/
#define T_NXT       ns_t_nxt           /******************************************/
#define T_EID       ns_t_eid           /******************************************/
#define T_NIMLOC    ns_t_nimloc        /******************************************/
#define T_SRV       ns_t_srv           /******************************************/
#define T_ATMA      ns_t_atma          /******************************************/
#define T_NAPTR     ns_t_naptr         /******************************************/
#define T_TSIG      ns_t_tsig          /******************************************/
#define T_IXFR      ns_t_ixfr          /******************************************/
#define T_AXFR      ns_t_axfr          /******************************************/
#define T_MAILB     ns_t_mailb         /******************************************/
#define T_MAILA     ns_t_maila         /******************************************/
#define T_ANY       ns_t_any           /******************************************/

#define C_IN        ns_c_in
#define C_CHAOS     ns_c_chaos
#define C_HS        ns_c_hs
/*----------------------------------------------*
 * External Variables            
 *----------------------------------------------*/

/*----------------------------------------------*
 * Global Variables    
 *----------------------------------------------*/

/*----------------------------------------------*
 * External Functions
 *----------------------------------------------*/

/*----------------------------------------------*
 * Functions
 *----------------------------------------------*/
typedef enum __ns_type 
{
    ns_t_invalid = 0,   /* Cookie. */
    ns_t_a = 1,     /* 主机地址 Host address. */
    ns_t_ns = 2,        /* 授权服务器 Authoritative server. */
    ns_t_md = 3,        /* 邮件地址 Mail destination. */
    ns_t_mf = 4,        /* 信件代理 Mail forwarder. */
    ns_t_cname = 5,     /* 规范名 Canonical name. */
    ns_t_soa = 6,       /* 开始授权区域 Start of authority zone. */
    ns_t_mb = 7,        /* 邮箱域名 Mailbox domain name. */
    ns_t_mg = 8,        /* 邮件组成员 Mail group member. */
    ns_t_mr = 9,        /* 邮件重命名 Mail rename name. */
    ns_t_null = 10,     /* 源记录空 Null resource record. */
    ns_t_wks = 11,      /* 已知服务 Well known service. */
    ns_t_ptr = 12,      /* 域名指示器 Domain name pointer. */
    ns_t_hinfo = 13,    /* 主机信息 Host information. */
    ns_t_minfo = 14,    /* 邮箱信息 Mailbox information. */
    ns_t_mx = 15,       /* 邮件路由信息 Mail routing information. */
    ns_t_txt = 16,      /* 文件内容 Text strings. */
    ns_t_rp = 17,       /* 负责人 Responsible person. */
    ns_t_afsdb = 18,    /* AFS cell数据库 AFS cell database. */
    ns_t_x25 = 19,      /* X_25呼叫地址 X_25 calling address. */
    ns_t_isdn = 20,     /* ISDN呼叫地址 ISDN calling address. */
    ns_t_rt = 21,       /* 路由器 Router. */
    ns_t_nsap = 22,     /* NSAP地址 NSAP address. */
    ns_t_nsap_ptr = 23, /* 反向NSAP查找 Reverse NSAP lookup (deprecated). */
    ns_t_sig = 24,      /* 安全签名 Security signature. */
    ns_t_key = 25,      /* 安全key Security key. */
    ns_t_px = 26,       /* X.400邮件映射  X.400 mail mapping. */
    ns_t_gpos = 27,     /* 地理位置 Geographical position (withdrawn). */
    ns_t_aaaa = 28,     /* Ip6地址 Ip6 Address. */
    ns_t_loc = 29,      /* 区域信息 Location Information. */
    ns_t_nxt = 30,      /* 下一区域（安全）Next domain (security). */
    ns_t_eid = 31,      /* 重点标识符 Endpoint identifier. */
    ns_t_nimloc = 32,   /* Nimrod Locator. */
    ns_t_srv = 33,      /* 服务器选择 Server Selection. */
    ns_t_atma = 34,     /* ATM地址 ATM Address */
    ns_t_naptr = 35,    /* 命名授权 Naming Authority PoinTeR */
    ns_t_kx = 36,       /* Key交换 Key Exchange */
    ns_t_cert = 37,     /* 证明记录 Certification record */
    ns_t_a6 = 38,       /* IPv6地址 IPv6 address (deprecates AAAA) */
    ns_t_dname = 39,    /* 非结束 Non-terminal DNAME (for IPv6) */
    ns_t_sink = 40,     /* Kitchen sink (experimentatl) */
    ns_t_opt = 41,      /* EDNS0选项 EDNS0 option (meta-RR) */
    ns_t_tkey = 249,    /* 变化key Transaction key */
    ns_t_tsig = 250,    /* 交易签名 Transaction signature. */
    ns_t_ixfr = 251,    /* 增加转移区 Incremental zone transfer. */
    ns_t_axfr = 252,    /* 转移区域授权 Transfer zone of authority. */
    ns_t_mailb = 253,   /* 转移邮箱记录 Transfer mailbox records. */
    ns_t_maila = 254,   /* 转移邮件代理记录 Transfer mail agent records. */
    ns_t_any = 255,     /* 通配符匹配 Wildcard match. */
    ns_t_zxfr = 256,    /* 特殊绑定，非标准 BIND-specific, nonstandard. */
    ns_t_max = 65536
} ns_type;


#define NS_GET16(s, cp)  { \
    register UCHAR *usCP = (UCHAR *)(cp); \
    (s) = (USHORT)(((USHORT)usCP[0] << 8) \
        | ((USHORT)usCP[1])) \
        ; \
    (cp) += sizeof(USHORT); \
}


#define NS_PUT16(s, cp) { \
     USHORT t_s = (USHORT)(s); \
     UCHAR *t_cp = (UCHAR *)(cp); \
    *t_cp++ = (UCHAR)(t_s >> 8); \
    *t_cp   = (UCHAR)t_s; \
    (cp) += sizeof(USHORT); \
} 


/*Modified for removal of Level-4 warning by Archana*/
#define NS_GET32(l, cp) { \
    register UCHAR *t_cp = (UCHAR *)(cp); \
    (l) = ((LONG)t_cp[0] << 24) \
        | ((LONG)t_cp[1] << 16) \
        | ((LONG)t_cp[2] << 8) \
        | ((LONG)t_cp[3]) \
        ; \
    (cp) += sizeof(LONG); \
} 



#define NS_PUT32(l, cp) { \
    register LONG t_l = (LONG)(l); \
    register UCHAR *t_cp = (UCHAR *)(cp); \
    *t_cp++ =(UCHAR) (t_l >> 24); \
    *t_cp++ =(UCHAR) (t_l >> 16); \
    *t_cp++ = (UCHAR) (t_l >> 8); \
    *t_cp   = (UCHAR) (t_l); \
    (cp) += sizeof(LONG); \
} 


typedef enum __ns_class 
{
    ns_c_invalid = 0,   /* Cookie. */
    ns_c_in = 1,        /* Internet. */
    ns_c_2 = 2,     /* unallocated/unsupported. */
    ns_c_chaos = 3,     /* MIT Chaos-net. */
    ns_c_hs = 4,        /* MIT Hesiod. */
    /* Query class values which do not appear in resource records */
    ns_c_none = 254,    /* for prereq. sections in update requests */
    ns_c_any = 255,     /* Wildcard match. */
    ns_c_max = 65536
} ns_class;

#ifdef  __cplusplus
}
#endif

#endif

