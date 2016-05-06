

#ifndef _IPSAFE_BASETYPE_H_
#define _IPSAFE_BASETYPE_H_

#ifdef  __cplusplus
extern "C" {
#endif

#define IPSAFE_YES      1
#define IPSAFE_NO       0

#define IPSAFE_OK          0        /*Success*/
#define IPSAFE_ERR         1        /*Failure*/

/* the following datatype should only be used for ACL API to maintain consistency with previous version */
/* Default is BIG-End */
#ifndef IPSAFE_ORDER_LITTLE_ENDIAN
#define IPSAFE_LITTLE_ENDIAN        IPSAFE_NO
#define IPSAFE_BIG_ENDIAN           IPSAFE_YES
#else
#define IPSAFE_LITTLE_ENDIAN        IPSAFE_YES
#define IPSAFE_BIG_ENDIAN           IPSAFE_NO
#endif

#ifndef CHAR
#define CHAR char
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef SHORT
#define SHORT short
#endif

#ifndef USHORT
#define USHORT  unsigned short
#endif

#ifndef LONG
#define LONG long
#endif

#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef INT8
#define INT8 char
#endif

#ifndef UINT8
#define UINT8 unsigned char
#endif

#ifndef INT16
#define INT16 short
#endif

#ifndef UINT16
#define UINT16 unsigned short
#endif

#ifndef INT32
#define INT32 int
#endif

#ifndef UINT32
#define UINT32 unsigned int
#endif

#ifndef UINT64
#if (IPSAFE_OS_WINDOWS == IPSAFE_YES)
    #define UINT64 unsigned __int64
#else
    #define UINT64 unsigned long long
#endif
#endif

#ifndef VOID
#define VOID void
#endif

/*Some systems define NULL as (-1), in our system, NULL must be (0). */
#ifdef NULL
#undef NULL
#endif

#define NULL    0 


#ifndef BOOL_TRUE
typedef UINT16 BOOL_T;
 #define BOOL_TRUE ((BOOL_T)1)
#endif
#ifndef BOOL_FALSE
 #define BOOL_FALSE ((BOOL_T)0)
#endif

#ifndef IPSAFE_ERROR
 #define IPSAFE_ERROR -1
#endif

#ifndef IPSAFE_OK
 #define IPSAFE_OK 0
#endif

#ifndef BOOL_TRUE
typedef UINT16 BOOL_T;
 #define BOOL_TRUE ((BOOL_T)1)
#endif
#ifndef BOOL_FALSE
 #define BOOL_FALSE ((BOOL_T)0)
#endif

#ifndef VOS_OK
#define VOS_OK                 (0)
#endif
#ifndef VOS_ERR
#define VOS_ERR                (1)    
#endif

#define IPSAFE_NATMODID  0




#if (IPSAFE_LITTLE_ENDIAN == IPSAFE_YES)
#define IPSAFE_NTOHL(x)                   ((((x) & 0x000000ff) << 24) | \
                                          (((x) & 0x0000ff00) <<  8) | \
                                          (((x) & 0x00ff0000) >>  8) | \
                                          (((x) & 0xff000000) >> 24))

#define IPSAFE_HTONL(x)                   ((((x) & 0x000000ff) << 24) | \
                                          (((x) & 0x0000ff00) <<  8) | \
                                          (((x) & 0x00ff0000) >>  8) | \
                                          (((x) & 0xff000000) >> 24))

#define IPSAFE_NTOHS(x)                   ((UINT16)((((x) & 0x00ff) << 8) | \
                                          (((x) & 0xff00) >> 8)))

#define IPSAFE_HTONS(x)                   ((UINT16)((((x) & 0x00ff) << 8) | \
                                          (((x) & 0xff00) >> 8)))

#else

#define IPSAFE_NTOHL(x) (x)

#define IPSAFE_NTOHS(x) (x)

#define IPSAFE_HTONL(x) (x)

#define IPSAFE_HTONS(x) (x)

#endif

#ifndef LEN_4
 #define LEN_4 4
#endif

#ifndef LEN_16
 #define LEN_16 16
#endif

#ifndef LEN_32
 #define LEN_32 32
#endif

#ifndef LEN_64
 #define LEN_64 64
#endif

#ifndef LEN_128
 #define LEN_128 128
#endif

#ifndef LEN_256
 #define LEN_256 256
#endif

#ifndef LEN_512
 #define LEN_512 512
#endif

#ifndef LEN_1024
 #define LEN_1024 1024
#endif

#ifndef LEN_2048
 #define LEN_2048 2048
#endif

#ifndef LEN_3096
 #define LEN_3096 3096
#endif

 typedef UINT32   IPSAFE_TCP_SEQ;


/*STRUCT< The TCP header structure.>*/
typedef struct tagIPSAFETCPHDR
{
    UINT16  usSrcPort;                     /*Source Port*/
    UINT16  usDstPort;                     /*Destination Port*/
    IPSAFE_TCP_SEQ    seqSeqNumber;        /*Sequence Number*/
    IPSAFE_TCP_SEQ    seqAckNumber;        /*Acknowledgement Number*/
#if IPSAFE_LITTLE_ENDIAN == IPSAFE_YES
    UINT8   ucX2:4,
    ucOffset:4;
#else
    UINT8   ucOffset:4, /* warning:nonstandard extension used : bit field types other than LONG. */
    ucX2:4;     /* warning:nonstandard extension used : bit field types other than LONG. */
#endif
    UINT8   ucFlags;
    UINT16      usWnd;
    UINT16      usCheckSum;
    UINT16      usUrgentPoint;
} IPSAFE_TCPHDR_S;

/*STRUCT< The UDP header structure.>*/
typedef struct tagIPSAFEUDPHDR
{
    UINT16    uh_usSPort;        /* source port */
    UINT16    uh_usDPort;        /* destination port */
    INT16     uh_sULen;          /* UDP length */
    UINT16    uh_usSum;          /* UDP checksum */
}IPSAFE_UDPHDR_S;

/*STRUCT< The internal address structure.>*/
typedef struct tagIPSAFEINADDR
{
    UINT32 s_ulAddr;            /*address*/
}IPSAFE_INADDR_S;

/*STRUCT< The structure of IP packet.>*/
typedef struct IPSAFEtagIP
{
#if IPSAFE_LITTLE_ENDIAN == IPSAFE_YES
    UINT8   ip_chHLen:4;        /* header length */
    UINT8   ip_chVer: 4;         /* version */
#else
    UINT8  ip_chVer:  4;         /* version */
    UINT8  ip_chHLen: 4;        /* header length */
#endif
    UINT8   ip_chTOS;           /* type of service */
    UINT16  ip_usLen;           /* total length */
#define ip_sLen ip_usLen
    UINT16  ip_usId;            /* identification */
    UINT16  ip_usOff;           /* fragment offset field */
#define ip_sOff ip_usOff
#define IP_DF 0x4000            /* dont fragment flag */
#define IP_MF 0x2000            /* more fragments flag */
#define IP_OFFMASK 0x1fff       /* mask for fragmenting bits */
    UINT8   ip_chTTL;           /* time to live */
    UINT8   ip_chPr;            /* protocol */
    UINT16  ip_usSum;           /* checksum */
    struct  tagIPSAFEINADDR ip_stSrc;
    struct  tagIPSAFEINADDR ip_stDst; /* source and dest address */
}IPSAFE_IP_S;

/*STRUCT< The structure of ICMP packet.>*/
typedef struct tagIPSAFE_ICMP
{
    UINT8   icmp_chType;        /* type of message, see below */
    UINT8   icmp_chCode;        /* type sub code */
    UINT16  icmp_usCksum;       /* ones complement cksum of struct */
    union
    {
        UINT8  ih_chPPtr;               /* ICMP_PARAMPROB */
        UINT32 ih_stGwAddr;   /* ICMP_REDIRECT */
        struct tagIPSAFEIHIDSEQ
        {
            UINT16  icd_nsId;
            UINT16  icd_nsSeq;
        } ipsafe_ih_stIdSeq;
        
        INT32     ih_nVoid;

        /* ICMP_UNREACH_NEEDFRAG -- Path MTU Discovery (RFC1191) */
        struct tagIPSAFEIHPMTU
        {
            UINT16 ipm_nsVoid;
            UINT16 ipm_nsNextMtu;
        } ipsafe_ih_stPMtu;
    }ipsafe_icmp_unHun;
#define ipsafe_icmp_chPPtr     ipsafe_icmp_unHun.ih_chPPtr
#define ipsafe_icmp_stGwAddr   ipsafe_icmp_unHun.ih_stGwAddr
#define ipsafe_icmp_nsId       ipsafe_icmp_unHun.ipsafe_ih_stIdSeq.icd_nsId
#define ipsafe_icmp_nsSeq      ipsafe_icmp_unHun.ipsafe_ih_stIdSeq.icd_nsSeq
#define ipsafe_icmp_nVoid      ipsafe_icmp_unHun.ih_nVoid
#define ipsafe_icmp_nsPmVoid   ipsafe_icmp_unHun.ipsafe_ih_stPMtu.ipm_nsVoid
#define ipsafe_icmp_nsNextMtu  ipsafe_icmp_unHun.ipsafe_ih_stPMtu.ipm_nsNextMtu
    union
    {
        struct tagIPSAFEIDTS
        {
            UINT32  its_ntOTime;
            UINT32  its_ntRTime;
            UINT32  its_ntTTime;
        } ipsafe_id_stTS;
        struct tagIPSAFEIDIP
        {
            IPSAFE_IP_S idi_stIp;
            /* options and then 64 bits of data */
        } ipsafe_id_stIp;
        UINT32   id_ulMask;
        CHAR     id_chData_a[9];
    } ipsafe_icmp_unDun;

#define ipsafe_icmp_ntOTime    ipsafe_icmp_unDun.ipsafe_id_stTS.its_ntOTime
#define ipsafe_icmp_ntRTime    ipsafe_icmp_unDun.ipsafe_id_stTS.its_ntRTime
#define ipsafe_icmp_ntTTime    ipsafe_icmp_unDun.ipsafe_id_stTS.its_ntTTime
#define ipsafe_icmp_stIp       ipsafe_icmp_unDun.ipsafe_id_stIp.idi_stIp
#define ipsafe_icmp_ulMask     ipsafe_icmp_unDun.id_ulMask
#define ipsafe_icmp_chData_a   ipsafe_icmp_unDun.id_chData_a
}IPSAFE_ICMP_S;




#ifdef  __cplusplus
}
#endif


#endif

