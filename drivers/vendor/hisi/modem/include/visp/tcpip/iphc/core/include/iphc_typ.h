/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         iphc_typ.h
 *
 *  Project Code: VISP
 *   Module Name: IPHC
 *  Date Created: 2000/08/15
 *        Author: wangyue
 *   Description: 对IP + TCP，IP + UDP，以及IP + UDP + RTP格式  
 *                的报文头进行压缩和解压   
 *                注：
 *
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2006-03-30      xiehuaguo       Adjust for D00647
 *  2006-05-11      luyao           为支持ARM CPU字节对齐特性，修改结构。
 *
 ************************************************************************/
 
#ifndef _IPHC_TYP_H_
#define _IPHC_TYP_H_


#ifdef __cplusplus
extern "C" {
#endif

#define IPHC_INPUT_CONTINUE                     1
#define IPHC_INPUT_DROP                         2
#define IPHC_INPUT_UNKNOWN_PROTOCAL             3

#define IPHC_RPC_FUNC_ID_SHOW_CONTEXT           1
#define IPHC_RPC_FUNC_ID_HOT_INSERT_VT_RECOVER  2

#define PPP_FULL_HEADER                     0x0061
#define PPP_Compressed_TCP                  0x0063
#define PPP_Compressed_TCP_NODELTA          0x2063
#define PPP_Compressed_NON_TCP              0x0065
#define PPP_Compressed_UDP_8                0x0067
#define PPP_Compressed_UDP_16               0x2067
#define PPP_Compressed_RTP_8                0x0069
#define PPP_Compressed_RTP_16               0x2069
#define PPP_CONTEXT_STATE                   0x2065

#define DEF_TCP_SPACE           15
#define DEF_NON_TCP_SPACE       15
#define DEF_F_MAX_PERIOD        256
#define DEF_F_MAX_TIME          5
#define DEF_MAX_HEADER          168


/*定义压缩格式报文的CID格式*/
#define CID_CHAR                1
#define CID_SHORT               2

/*定义可压缩的TCP以及RTP格式报文最大连接数*/
#define TOTAL_RTP_CID            1000
#define TOTAL_TCP_CID            256

/*定义RFC2509中PPP之上的IPHC协议所需协商的各参数*/
#define MIN_WRAP_NUM            3
#define TCP_SPACE_NUM           15
#define NON_TCP_SPACE_NUM       15
#define F_MAX_PERIOD_NUM        256
#define F_MAX_TIME_NUM          5
#define    MAX_HEADER_NUM       168

/*定义压缩和解压错误返回值*/
#define Compressed_NULL         0x0000
#define Decompressed_NULL       0x0000

/*定义IP报文的协议号*/
#define IP_HEADER               0x0021

/*定义IP报文的子报文协议号*/
#define IP_PROTOCOL_TCP         0x06
#define IP_PROTOCOL_UDP         0x11

/*定义压缩和解压的报文类型协议号*/
#define FULL_HEADER             0x0061
#define Compressed_TCP          0x0063
#define Compressed_TCP_NODELTA  0x2063
#define Compressed_NON_TCP      0x0065
#define Compressed_UDP_8        0x0067
#define Compressed_UDP_16       0x2067
#define Compressed_RTP_8        0x0069
#define Compressed_RTP_16       0x2069
#define CONTEXT_STATE           0x2065

/*定义使用到的BOOL值常量*/
#define IPHC_FALSE              0
#define IPHC_TRUE               1

#ifndef IPHC_LITTLE_ENDIAN
#define IPHC_LITTLE_ENDIAN      1        /* for x86 */
#endif

#ifndef IPHC_BIG_ENDIAN
#define IPHC_BIG_ENDIAN         2        /* for mpc */
#endif

#ifndef IPHC_BYTE_ORDER
#if (VRP_LITTLE_ENDIAN == VRP_YES)
#define IPHC_BYTE_ORDER         IPHC_LITTLE_ENDIAN
#else
#define IPHC_BYTE_ORDER         IPHC_BIG_ENDIAN
#endif
#endif

enum enIPHCIndex 
{
    HELP_IPHC_DEBUG_RTP_ON      = 0,
    HELP_IPHC_DEBUG_TCP_ON      = 1,
    HELP_IPHC_DEBUG_RTP_OFF     = 2,
    HELP_IPHC_DEBUG_TCP_OFF     = 3,
    IPHC_CmdProc_Err_WrongIf,
    IPHC_CmdProc_Err_CRtpNotSupport,
    IPHC_CmdProc_Err_CTcpNotSupport,
    IPHC_CmdProc_Err_CRtpNotStart    
};

/* 引入的模块ID */
typedef struct tagIPHC_Mod_Info
{
    ULONG ulMID_IPHC;
    ULONG ulSID_IPHC_CONTEXT_S;
    ULONG ulSID_MBUF_S;
}IPHC_MOD_INFO_S;

/* Shell向Core注册的回调函数集 */
typedef struct tagIPHC_SHELL_CALLBACK_SET
{
    VOID (*pfIPHC_DebugOutString) (CHAR * szStr);
}IPHC_SHELL_CALLBACK_SET_S;

typedef struct tagIPHC_SHOW_RPC_STRUCT
{
     ULONG ulType;
     ULONG ulIfIndex;
     ULONG ulRtpOrTcp;
}IPHC_SHOW_RPC_STRUCT_S;

typedef struct tagIPHC_HOT_INSERT_IFINFO
{
     ULONG   ulIfIndex;
     USHORT  usRtpConnectNumber;
     USHORT  usTcpConnectNumber;
     ULONG   ulCCompanyFormat;
}IPHC_HOT_INSERT_IFINFO_S  ;

typedef struct tagIPHC_HOT_INSERT_NOTIFY
{
     ULONG ulType;
     ULONG ulIfCount;         
     IPHC_HOT_INSERT_IFINFO_S stIfInfo[1];
}IPHC_HOT_INSERT_NOTIFY_S  ;


/*
* RTP data header
*/
typedef struct tagRtp_Hdr_t{
#if IPHC_BYTE_ORDER == IPHC_LITTLE_ENDIAN                        
    UCHAR cc     : 4;           /* CSRC count */
    UCHAR x      : 1;           /* header extension flag */
    UCHAR p      : 1;           /* padding flag */
    UCHAR version: 2;           /* protocol version */
    UCHAR pt     : 7;           /* payload type */
    UCHAR m      : 1;           /* marker bit */
#else
    UCHAR version: 2;           /* protocol version */
    UCHAR p      : 1;           /* padding flag */
    UCHAR x      : 1;           /* header extension flag */
    UCHAR cc     : 4;           /* CSRC count */
    UCHAR m      : 1;           /* marker bit */
    UCHAR pt     : 7;           /* payload type */
#endif
    USHORT seq;                 /* sequence number */
    ULONG ts;                   /* timestamp */
    ULONG ssrc;                 /* synchronization source */
    /*unsigned long csrc[1];*/  /* optional CSRC list */
} rtp_hdr_t;


/*TCP格式压缩报文的CID格式,第一部分*/
typedef struct tagIPHC_TCP_CID_FIRST
{
    UCHAR pkt_lsb;          /*LSB of packet sequence number*/
    UCHAR cid;              /*CID*/
    UCHAR ucPadding[2];
}IPHC_TCP_CID_FIRST_S;
/*TCP格式压缩报文的CID格式,第一部分*/

/*TCP格式压缩报文的CID格式,第二部分*/
typedef struct tagIPHC_TCP_CID_SECOND
{
    UCHAR pkt_msb;          /*MSB of packet sequence number*/
    UCHAR zero;             /*always be zero*/
    UCHAR ucPadding[2];
}IPHC_TCP_CID_SECOND_S;

/*8 BIT格式的RTP压缩报文的CID格式，第一部分*/
typedef struct tagIPHC_RTP_CID8_FIRST
{
#if IPHC_BYTE_ORDER == IPHC_LITTLE_ENDIAN                        
    UCHAR gen : 6,          /*generation number,equal to zero in IPv4*/
          d   : 1,          /*always be 1*/
          v   : 1;          /*cid version,0 for 8bit CID,1 for 16bit CID*/
    UCHAR cid;              /*CID*/
    UCHAR ucPadding[2];
#else
    UCHAR v   : 1,          /*cid version,0 for 8bit CID,1 for 16bit CID*/
          d   : 1,          /*always be 1*/
          gen : 6;          /*generation number,equal to zero in IPv4*/
    UCHAR cid;              /*CID*/
    UCHAR ucPadding[2];
#endif
}IPHC_RTP_CID8_FIRST_S;

/*8 BIT格式的RTP压缩报文的CID格式，第二部分*/
typedef struct tagIPHC_RTP_CID8_SECOND
{
#if IPHC_BYTE_ORDER == IPHC_LITTLE_ENDIAN                    
    UCHAR z1;               /*zerofield:equal to zero all the time*/
    UCHAR seq : 4,          /*sequence number*/
          z2  : 4;          /*zerofield:equal to zero all the time*/
    UCHAR ucPadding[2];
#else
    UCHAR z1;               /*zerofield:equal to zero all the time*/
    UCHAR z2  : 4,          /*zerofield:equal to zero all the time*/
          seq : 4;          /*sequence number*/
    UCHAR ucPadding[2];
#endif
}IPHC_RTP_CID8_SECOND_S;

/*16 BIT格式的RTP压缩报文的CID格式,第一部分*/
typedef struct tagIPHC_RTP_CID16_FIRST
{
#if IPHC_BYTE_ORDER == IPHC_LITTLE_ENDIAN
    UCHAR gen : 6,          /*generation number,equal to zero in IPv4*/
          d   : 1,          /*always be 1*/
          v   : 1;          /*cid version,0 for 8bit CID,1 for 16bit CID*/
    UCHAR seq : 4,          /*sequence number*/
          zero: 4;          /*always be zero*/
    UCHAR ucPadding[2];
#else
    UCHAR v   : 1,          /*cid version,0 for 8bit CID,1 for 16bit CID*/
          d   : 1,          /*always be 1*/
          gen : 6;          /*generation number,equal to zero in IPv4*/
    UCHAR zero: 4,          /*always be zero*/
          seq : 4;          /*sequence number*/
    UCHAR ucPadding[2];
#endif
}IPHC_RTP_CID16_FIRST_S;

/*16 BIT格式的RTP压缩报文的CID格式,第二部分*/
typedef struct tagIPHC_RTP_CID16_SECOND
{
    USHORT cid;             /*CID*/
    UCHAR ucPadding[2];
}IPHC_RTP_CID16_SECOND_S;

/*8 BIT RTP CID 格式*/
typedef struct tagIPHC_RTP_CID8
{
    struct tagIPHC_RTP_CID8_FIRST      *first;       /*use ip_slen field to store it*/
    struct tagIPHC_RTP_CID8_SECOND     *second;      /*use uh_sulen field to store it*/
}IPHC_RTP_CID8_S;

/*16 BIT RTP CID格式*/
typedef struct tagIPHC_RTP_CID16
{
    struct tagIPHC_RTP_CID16_FIRST   *first;   /*use ip_slen field to store it*/
    struct tagIPHC_RTP_CID16_SECOND  *second;  /*use uh_sulen field to store it*/
}IPHC_RTP_CID16_S;

/* TCP CID 格式*/
typedef union tagIPHC_RTP_CID
{
    struct tagIPHC_RTP_CID8   *cid8;     /* 8-bit cid */
    struct tagIPHC_RTP_CID16  *cid16;    /* 16-bit cid */
}IPHC_RTP_CID_U;


/*TCP格式报文的变量编解码数据结构*/
typedef struct tagIPHC_TCP_DELTA_TYPE
{
    UCHAR   type;           /*1: one byte delta;  2: two byte delta; 3: error delta*/                
    UCHAR   first;          /*first byte of the delta value*/
    UCHAR   second;         /*second byte of the delta value*/
    UCHAR   third;          /*third byte of the delta value*/
    USHORT  value;          /*delta value*/
    UCHAR   ucPadding[2];
}IPHC_TCP_DELTA_TYPE_S;

/* 修改了R_octet中成员的次序 */
/*COMPRESSED_TCP格式压缩报文*/
typedef struct tagIPHC_Compressed_TCP
{
    UCHAR cid;                /*cid*/
    union tagIPHC_Compressed_TCP_FLAG_UNION
    {
        struct tagIPHC_Compressed_TCP_FLAG_UNION_STRUCT
        {
#if IPHC_BYTE_ORDER == IPHC_LITTLE_ENDIAN                        
            UCHAR U:1,      /*if it has urgent pointer value*/
                  W:1,      /*if it has weidnow delta*/
                  A:1,      /*if it has acknowledge number delta*/
                  S:1,      /*if it has sequence number delta*/
                  P:1,      /*the tcp header's P bit*/
                  I:1,      /*if the ip_id delta != 1*/
                  O:1,      /*if the tcp header's options changed*/
                  R:1;      /*if it has R-octet*/
#else
            UCHAR R:1,      /*if it has R-octet*/
                  O:1,      /*if the tcp header's options changed*/
                  I:1,      /*if the ip_id delta != 1*/
                  P:1,      /*the tcp header's P bit*/
                  S:1,      /*if it has sequence number delta*/
                  A:1,      /*if it has acknowledge number delta*/
                  W:1,      /*if it has weidnow delta*/
                  U:1;      /*if it has urgent pointer value*/
#endif
        }bit;
        UCHAR octet;        /*由8 bit标识组成*/
    }flag;
    USHORT tcp_chk;         /*tcp checksum*/
    union tagIPHC_Compressed_TCP_R_OCTET_UNION
    {
        struct tagIPHC_Compressed_NON_TCP_R_OCTET_UNION_STRUCT
        {
#if IPHC_BYTE_ORDER == IPHC_LITTLE_ENDIAN                        
            UCHAR ip_tos    :2,     /*bit 6\7 of the ip tos field*/
                  tcp_flags :2,     /*flags is a CHAR and this is the first two bit of that CHAR*/
                  tcp_ucX2  :4;     /*tcp reversed field*/
                  /* ip_tos    :2; */    /*bit 6\7 of the ip tos field*/
#else
            UCHAR /* ip_tos    :2, */    /*bit 6\7 of the ip tos field*/
                  tcp_ucX2  :4,     /*tcp reversed field*/
                  tcp_flags :2,     /*flags is a CHAR and this is the first two bit of that CHAR*/
                  ip_tos    :2;     /*bit 6\7 of the ip tos field*/
                                    
#endif
        }bit;
        UCHAR octet;         /*reserved field in tcp and bit 6\7 of the ip tos field*/
    }R_octet;    /*R_otect = (UCHAR)(tcp->ucX2 | tcp->ucFlags >> 6 | ip->ip_chTOS&0x03  */
    UCHAR  ucPadding[3];
    struct tagIPHC_TCP_DELTA_TYPE u_value;    /*urgent pointer value of tcp header*/
    struct tagIPHC_TCP_DELTA_TYPE w_delta;    /*window delta of tcp header*/
    struct tagIPHC_TCP_DELTA_TYPE a_delta;    /*acknowledgement number delta of tcp header*/
    struct tagIPHC_TCP_DELTA_TYPE s_delta;    /*sequence number delta    of tcp header*/
    struct tagIPHC_TCP_DELTA_TYPE i_delta;    /*ip id delta*/
}IPHC_Compressed_TCP_S;

/*COMPRESSED_NON_TCP格式压缩报文*/
typedef struct tagIPHC_Compressed_NON_TCP
{
    UCHAR cid_lsb;          /*lsb of the cid*/
    UCHAR cid_msb;          /*msb of the cid, if it is a 16-bit one*/
    union tagIPHC_Compressed_NON_TCP_UNION
    {
        struct tagIPHC_Compressed_NON_TCP_UNION_STRUCT
        {
#if IPHC_BYTE_ORDER == IPHC_LITTLE_ENDIAN                        
            UCHAR gen:6,    /*generation number*/
                  d  :1,    /*0: no rtp;  1: has rtp*/
                  v  :1;    /*0: 8-bit;  1: 16-bit*/    
#else
            UCHAR v  :1,    /*0: 8-bit;  1: 16-bit*/    
                  d  :1,    /*0: no rtp;  1: has rtp*/
                  gen:6;    /*generation number*/
#endif
        }u_struct;
        UCHAR u_part;
    }comp_non_tcp_union;
    UCHAR ucPadding;
}IPHC_Compressed_NON_TCP_S;

/*COMPRESSED_UDP格式压缩报文*/
typedef struct tagIPHC_COMPRESSED_UDP
{            
    UCHAR cid_msb;        /*for 16-bit cid ; msb of the cid*/
    UCHAR cid_lsb;        /*for 8bit pContext session ID*/            
    union tagIPHC_COMPRESSED_UDP_upart
    {
           struct tagIPHC_COMPRESSED_UDP_upart_struct
        {
#if IPHC_BYTE_ORDER == IPHC_LITTLE_ENDIAN        
            UCHAR seq:4,    /*sequence number*/        
                  I  :1,    /*I=1——delta IPv4 ID field in use*/                    
                  T  :1,    /*equal to zero here*/                    
                  S  :1,    /*equal to zero here*/                    
                  m  :1;    /*equal to zero here*/            
#else        
            UCHAR m  :1,    /*equal to zero here*/                    
                  S  :1,    /*equal to zero here*/                    
                  T  :1,    /*equal to zero here*/                    
                  I  :1,    /*I=1——delta IPv4 ID field in use*/                    
                  seq:4;    /*sequence number*/
#endif
        }upart_struct;
        UCHAR part;         /*second part of the struct*/
    }upart;
    UCHAR ucPadding_1;
    USHORT udp_chk;         /*udp checksum*/
    UCHAR ucPadding_2[2];
}IPHC_COMPRESSED_UDP_S;

/*COMPRESSED_RTP格式压缩报文*/
typedef struct tagIPHC_COMPRESSED_RTP
{                
    UCHAR cid_msb;        /*for 16-bit cid ,msb of the cid*/
    UCHAR cid_lsb;        /*for 8bit pContext session ID*/    
    union tagIPHC_COMPRESSED_RTP_first_union
    {    
        struct tagIPHC_COMPRESSED_RTP_FIRST_upart_struct
        {                    
#if IPHC_BYTE_ORDER == IPHC_LITTLE_ENDIAN
            UCHAR seq:4,    /*sequence number*/
                  I  :1,    /*I=1——delta IPv4 ID field in use*/
                  T  :1,    /*equal to zero here*/
                  S  :1,    /*equal to zero here*/
                  m  :1;    /*equal to zero here*/            
#else
            UCHAR m  :1,    /*equal to zero here*/                                
                  S  :1,    /*equal to zero here*/                                
                  T  :1,    /*equal to zero here*/                                
                  I  :1,    /*I=1——delta IPv4 ID field in use*/                                
                  seq:4;    /*sequence number*/
#endif
        }upart_struct;
        UCHAR first;        /*first part of the packet header*/
    }first_union;
    union tagIPHC_COMPRESSED_RTP_second_union
    {
        struct tagIPHC_COMPRESSED_RTP_SECOND_upart_struct
        {
#if IPHC_BYTE_ORDER == IPHC_LITTLE_ENDIAN
            UCHAR cc:4,     /*CSRC list count*/            
                  I1:1,     /*I1=1——delta IPv4 ID field in use*/                                
                  T1:1,     /*T1=1——delta RTP timestamp field in use*/                                
                  S1:1,     /*S1=1——delta RTP sequence field in use*/                                
                  M1:1;     /*M1  ——M bit in the RTP header*/                    
#else
            UCHAR M1:1,     /*M1  ——M bit in the RTP header*/                                
                  S1:1,     /*S1=1——delta RTP sequence field in use*/                                
                  T1:1,     /*T1=1——delta RTP timestamp field in use*/                                
                  I1:1,     /*I1=1——delta IPv4 ID field in use*/                                
                  cc:4;     /*CSRC list count*/
#endif        
        }upart_struct;
        UCHAR second;   /*second part of the packet header*/
    }second_union;
    ULONG delta_seq;    /*delta RTP sequence*/
}IPHC_COMPRESSED_RTP_S;

#pragma    pack( 1 )

/*8 bit RTP 类型 CONTEXT_STATE格式报文*/
typedef struct tagIPHC_CONTEXT_STATE_STRUCT_RTP_8
{
    UCHAR cid;         /*session pContext ID*/
    union tagIPHC_CONTEXT_STATE_upart_8
    {
        struct tagIPHC_CONTEXT_STATE_upart_struct_8
        {
/*#if IPHC_BYTE_ORDER == IPHC_LITTLE_ENDIAN            for c公司 */
#if IPHC_BYTE_ORDER == IPHC_BIG_ENDIAN        
            UCHAR seq:4,    /*sequence number*/
                  z1 :3,    /*zerofield1,equal to zero all the time*/
                  I  :1;    /*I=1 ,must retransfor*/
            UCHAR gen:6,    /*generation number,equal to zero in IPv4*/
                  z2 :2;    /*zerofield2,equal to zero all the time*/
#else
            UCHAR I  :1,    /*I=1 ,must retransfor*/
                  z1 :3,    /*zerofield1,equal to zero all the time*/
                  seq:4;    /*sequence number*/
            UCHAR z2 :2,    /*zerofield2,equal to zero all the time*/
                  gen:6;    /*generation number,equal to zero in IPv4*/
#endif
        }upart_struct;
        struct tagIPHC_CONTEXT_STATE_upart_struct_char_8
        {
            UCHAR first;    /*seq,z1 & I*/
            UCHAR second;   /*gen & z2*/
        }upart_char;
    }upart;
    /* UCHAR ucPadding; */
}IPHC_CONTEXT_STATE_STRUCT_RTP_8_S;

/*8 BIT RTP CONTEXT_STATE报文*/
typedef struct tagIPHC_CONTEXT_STATE_RTP_8
{
    UCHAR v;        /*version,1 for 8bit CID*/
    UCHAR c;        /*pContext count*/
    struct tagIPHC_CONTEXT_STATE_STRUCT_RTP_8 s[256];  /*CONTEXT_STATE_STRUCT ARRAY*/
}IPHC_CONTEXT_STATE_RTP_ARR_8_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

/*16 bit RTP CONTEXT_STATE格式*/
typedef struct tagIPHC_CONTEXT_STATE_STRUCT_RTP_16
{
    USHORT cid;     /*session pContext ID*/
    union tagIPHC_CONTEXT_STATE_upart_16
    {
        struct tagIPHC_CONTEXT_STATE_upart_struct_16
        {
/*#if IPHC_BYTE_ORDER == IPHC_LITTLE_ENDIAN    for c公司 */
#if IPHC_BYTE_ORDER == IPHC_BIG_ENDIAN        

            UCHAR seq:4,    /*sequence number*/
                  z1 :3,    /*zerofield1,equal to zero all the time*/
                  I  :1;    /*I=1 ,must retransfor*/
            UCHAR gen:6,    /*generation number,equal to zero in IPv4*/
                  z2 :2;    /*zerofield2,equal to zero all the time*/
#else
            UCHAR I  :1,    /*I=1 ,must retransfor*/
                  z1 :3,    /*zerofield1,equal to zero all the time*/
                  seq:4;    /*sequence number*/
            UCHAR z2 :2,    /*zerofield2,equal to zero all the time*/
                  gen:6;    /*generation number,equal to zero in IPv4*/
#endif
        }upart_struct;
        struct tagIPHC_CONTEXT_STATE_upart_struct_char_16
        {
            UCHAR first;    /*seq,z1 & I*/
            UCHAR second;   /*gen & z2*/
        }upart_char;
    }upart;
}IPHC_CONTEXT_STATE_STRUCT_RTP_16_S;


#pragma    pack( 1 )

/*16 bit RTP CONTEXT_STATE报文*/
typedef struct tagIPHC_CONTEXT_STATE_RTP_16
{
    UCHAR v;      /*version,1 for 8bit CID*/
    UCHAR c;      /*pContext count*/
    struct tagIPHC_CONTEXT_STATE_STRUCT_RTP_16 s[256];   /*CONTEXT_STATE_STRUCT ARRAY*/
}IPHC_CONTEXT_STATE_RTP_ARR_16_S;


/*CONTEXT_STATE格式压缩报文*/
typedef struct tagIPHC_CONTEXT_STATE_TCP
{
    UCHAR v;            /*version,1 for 8bit CID*/
    UCHAR c;            /*pContext count*/
    UCHAR cid[256];     /*CONTEXT_STATE_STRUCT ARRAY*/
}IPHC_CONTEXT_STATE_TCP_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

/*TCP格式CID数组结构*/    
typedef struct tagIPHC_TCP_CID_ARRAY_STRUCT
{
    UCHAR  cid;   /*cid*/
    UCHAR ucPadding[3];
    struct tagIPHC_TCP_CID_ARRAY_STRUCT *next;  /*next free CID_ARRAY_STRUCT*/
    struct tagIPHC_TCP_CONTEXT_TABLE_STRUCT *con;  /*point to the CONTEXT_TABLE_STRUCT whose cid equal to this one*/
}IPHC_TCP_CID_ARRAY_STRUCT_S;

/*Non-TCP格式CID数组结构*/    
typedef struct tagIPHC_NON_TCP_CID_ARRAY_STRUCT
{
    USHORT cid;    /*cid*/
    UCHAR  gen:6,  /*last generation number*/
           pud:2;  /*no use*/
    UCHAR ucPadding;
    struct tagIPHC_NON_TCP_CID_ARRAY_STRUCT *next;  /*next free CID_ARRAY_STRUCT*/
    struct tagIPHC_NON_TCP_CONTEXT_TABLE_STRUCT *con; /*point to the CONTEXT_TABLE_STRUCT whose cid equal to this one*/
}IPHC_NON_TCP_CID_ARRAY_STRUCT_S;




/*TCP格式压缩存储结构*/
typedef struct tagIPHC_TCP_CONTEXT_TABLE_STRUCT
{    
    union tagIPHC_TCP_CONTEXT_TABLE_STRUCT_HEADER_UNION
    {
        struct tagIP iphdr;       /*full ip header1*/
        CHAR         chHdr[MAX_HEADER_NUM];
    }header;
    struct tagTCPHDR *tcphdr;       /*full tcp header*/
    UCHAR            cid;           /*session pContext ID*/
    UCHAR            packet_type:4, /*packet type 1——3 */
                                    /* 1: IP + TCP */
                     valid:2,       /*if this pContext valid*/
                     use_recently:2;/*if this pContext used recently*/
    UCHAR            index;         /*index of the context_table*/
    UCHAR ucPadding;
    struct tagIPHC_TCP_CONTEXT_TABLE_STRUCT *next;  /*next context_table_struct*/
    struct tagIPHC_TCP_CONTEXT_TABLE_STRUCT *prev;  /*prev context_table_struct*/
}IPHC_TCP_CONTEXT_TABLE_STRUCT_S;

/*RTP格式压缩存储结构*/
typedef struct tagIPHC_NON_TCP_CONTEXT_TABLE_STRUCT
{    
    struct tagIP iphdr;            /*full ip header1*/        
    struct tagUDPHDR udphdr;       /*full udp header*/
    struct tagRtp_Hdr_t rtphdr;    /*full rtp header*/
    LONG   delta_ip_id;     /*last ip header delta IP ID*/
    LONG   delta_rtp_ts;    /*delta rtp timestamp*/
    UCHAR  seq:4,           /*sequence number of last compressed packet*/
           last_seq:4;      /*sequence number of last full_header*/
    UCHAR  gen:6,           /*NON_TCP packet generation number*/
           valid:1,         /*if this pContext is valid*/
           use_recently:1;  /*if this pContext used recently*/
    UCHAR  ucPadding_1[2];
    ULONG  F_LAST;          /*time of last full_header transmited*/
    ULONG  F_START;         /*time of this pContext started*/
    USHORT F_PERIOD;        /*largest number of compressed packet can be transmited between full_headers*/
    USHORT C_NUM;           /*number of compressed packet transmited from last full_header*/
    USHORT cid;             /*session pContext ID*/
    UCHAR  packet_type;     /*packet type 1——6 */
    UCHAR  ucPadding_2;
                            /* 2: IP + UDP  */
                            /* 3: IP + UDP + RTP */
    USHORT index;           /*index of the context_table*/
    UCHAR  ucPadding_3[2];
    struct tagIPHC_NON_TCP_CONTEXT_TABLE_STRUCT *next; /*next context_table_struct*/
    struct tagIPHC_NON_TCP_CONTEXT_TABLE_STRUCT *prev; /*prev context_table_struct*/
}IPHC_NON_TCP_CONTEXT_TABLE_STRUCT_S;


/*TCP格式压缩存储表*/
typedef struct tagIPHC_TCP_CONTEXT_TABLE
{
    struct tagIPHC_TCP_CONTEXT_TABLE_STRUCT *con[TOTAL_TCP_CID];
    struct tagIPHC_TCP_CID_ARRAY_STRUCT     cid[TOTAL_TCP_CID];
    struct tagIPHC_TCP_CID_ARRAY_STRUCT     *free_cid;  /*point to the free cid in the cid array*/
}IPHC_TCP_CONTEXT_TABLE_S;

/*RTP 格式压缩存储表*/
typedef struct tagIPHC_NON_TCP_CONTEXT_TABLE
{
    struct tagIPHC_NON_TCP_CONTEXT_TABLE_STRUCT *con[TOTAL_RTP_CID];
    struct tagIPHC_NON_TCP_CID_ARRAY_STRUCT     cid[TOTAL_RTP_CID];
    struct tagIPHC_NON_TCP_CID_ARRAY_STRUCT     *free_cid;  /*point to the free cid in the cid array*/
}IPHC_NON_TCP_CONTEXT_TABLE_S;


/*TCP格式解压存储结构*/
typedef struct tagIPHC_TCP_CONTEXT_ARRAY_STRUCT
{
    union tagIPHC_TCP_CONTEXT_ARRAY_HEADER_UNION
    {
        struct tagIP iphdr;  /*full ip header1*/
        CHAR   chHdr[MAX_HEADER_NUM];
    }header;
    struct tagTCPHDR *tcphdr;/*full tcp header*/
    UCHAR  cid;            
    UCHAR  packet_type :4,   /*IP + TCP ——1 */
           valid       :2,
           use_recently:2;
    UCHAR  invalid_count;    /*invalid times*/
    UCHAR  ucPadding;
}IPHC_TCP_CONTEXT_ARRAY_STRUCT_S;



/*RTP格式解压存储结构*/
typedef struct tagIPHC_NON_TCP_CONTEXT_ARRAY_STRUCT
{
    struct tagIP        iphdr;          /*full ip header1*/
    struct tagUDPHDR    udphdr;         /*full udp header*/
    struct tagRtp_Hdr_t rtphdr;         /*full rtp header*/
    LONG   delta_ip_id;     /*last IP header delta IP id*/
    LONG   delta_rtp_ts;    /*delta rtp timestamp*/
    USHORT seq:4,           /*compressed packet sequence*/
           invalid_count:12;
    UCHAR  gen:6,           /*packet generation number*/
           valid:1,
           use_recently:1;
    UCHAR  ucPadding;
    ULONG  P_LAST;          /*time of last packet received*/
    USHORT cid;            
    UCHAR  packet_type;     /*IP + TCP ——1 */
    UCHAR  non_tcp_delta;
}IPHC_NON_TCP_CONTEXT_ARRAY_STRUCT_S;


/*接收报文调试信息*/
typedef struct tagIPHC_DEBUG_RCVD_INFO
{
    ULONG total;            /* total packet received */
    ULONG compressed;       /* total compressed packet received */
    ULONG error;            /* total error packet received */
    ULONG drop;             /* total packet droped */
    ULONG buf_copy;         /* total buffer copies */
    ULONG buf_fail;         /* total buffer failures */
}IPHC_DEBUG_RCVD_INFO_S;


/*发送报文调试信息*/
typedef struct tagIPHC_DEBUG_SENT_INFO
{
    ULONG total;            /* total packet sent */
    ULONG compressed;       /* total compressed packet sent */
    ULONG saved_bytes;      /* total bytes saved */
    ULONG sent_bytes;       /* total bytes sent */
    ULONG total_bytes;      /* total bytes of the packets */
    ULONG sentfullhead;     /* total full head packets sent */
}IPHC_DEBUG_SENT_INFO_S;


/*调试连接信息*/
typedef struct tagIPHC_DEBUG_CONNECT_INFO
{
    ULONG rx;               /* total recieved connection cid */
    ULONG tx;               /* total sent connection cid */
    ULONG long_search;      /* total times of LONG searches */
    ULONG miss;             /* total times of misses */
    ULONG five_min_miss;    /* total times of missed in last five minites */
    ULONG last_miss_rate;   /* last miss rate */
    ULONG max_miss_rate;    /* max miss rate */
  /*float last_miss_rate;*/ /* last miss rate */
  /*float max_miss_rate;*/  /* max miss rate */
}IPHC_DEBUG_CONNECT_INFO_S;




/*调试信息结构*/
typedef struct tagIPHC_DEBUG_RTP_TCP_COMPRESSION
{
    struct tagIPHC_DEBUG_RCVD_INFO    rcvd;        /*received packet information*/
    struct tagIPHC_DEBUG_SENT_INFO    sent;        /*sent packet information*/
    struct tagIPHC_DEBUG_CONNECT_INFO connection;  /*connection information*/
}IPHC_DEBUG_RTP_TCP_COMPRESSION_S;


/*TCP和RTP格式调试信息*/
typedef struct tagIPHC_DEBUG_IPHC
{
    struct tagIPHC_DEBUG_RTP_TCP_COMPRESSION rtp_info;  /* rtp compression information */
    struct tagIPHC_DEBUG_RTP_TCP_COMPRESSION tcp_info;  /* tcp compression information */
}IPHC_DEBUG_IPHC_S;



/*压缩解压模块数据存储表*/
typedef struct tagIPHC_COMPRESSION_CONTEXT
{
    struct tagIPHC_CONTEXT_TABLE *comp_con;      /*pContext used by compression part*/
    struct tagIPHC_CONTEXT_ARRAY *decomp_con;    /*pContext used by decompression part*/
    ULONG  now_time;        /*from started to now*/
    LONG   timerID;         /*for timer*/
    LONG   timeouttime;     /*time to call function: IPHC_TimerCall*/
    UCHAR  cid_type;        /* 1: 8-bit cid ;  2: 16-bit cid */
    UCHAR  MIN_WRAP;        /*minimum time of generation value wrap around, 3 seconds*/
    UCHAR  ucPadding[2];
    struct tagIPHC_DEBUG_IPHC debug_info;        /* debug information of iphc */
    LONG   DELETE_UDP_CHKSUM;   /* delete the UDP chksum while compressing the headers */
    LONG   CCOMPANY;            /* 对端是否C公司 */
    LONG   CONGESTION;          /* 是否拥塞 */
    LONG   CONGESTION_TIME;     /* 拥塞次数 */
    LONG   TOTAL;               /* 压缩解压次数 */
    LONG   ERROR;               /* 错误次数 */
}IPHC_COMPRESSION_CONTEXT_S;


/*TCP和RTP格式压缩存储表*/
typedef struct tagIPHC_CONTEXT_TABLE
{
    struct tagIPHC_TCP_CONTEXT_TABLE        tcp_tab;        /*TCP pContext table*/
    struct tagIPHC_NON_TCP_CONTEXT_TABLE    non_tcp_tab;    /*NON_TCP pContext table*/
    
    ULONG  ulCompressionType;   /* 压缩类型: 0--所有报文都压缩, 1--只压缩TCP, 2--只压缩non-TCP, 3--禁止压缩所有报文 */
    ULONG  ulRtpCompression;    /* RTP压缩开关: 0--不压缩RTP首部, 1--压缩RTP首部 */

    USHORT F_MAX_PERIOD;    /*largest number of compressed non_tcp headers that may be sent without sending a full header ,default is 256*/
    USHORT F_MAX_TIME;      /*compressed headers may not be sent more than F_MAX_TIME seconds after sending last full header.default is 5*/
    USHORT MAX_HEADER;      /*the largest header size in octets that may be compressed,default is 168 octets.
                                which covers 
                                - two IPv6 base headers
                                - a keyed MD5 authentication header
                                - a maximum-sized TCP header
                                MAX_HEADER must be at least 60 octets and at most 65535 octets*/
    USHORT TCP_SPACE;       /*maximum cid value for tcp.default is 15,3-255*/
    USHORT NON_TCP_SPACE;   /*maximum cid value for non-tcp.default is 15,3-999*/
    UCHAR  ucPadding[2];
    
}IPHC_CONTEXT_TABLE_S;

/*解压存储数组*/
typedef struct tagIPHC_CONTEXT_ARRAY
{
    struct tagIPHC_TCP_CONTEXT_ARRAY_STRUCT     *tcp_arr[TOTAL_TCP_CID];
    struct tagIPHC_NON_TCP_CONTEXT_ARRAY_STRUCT *non_tcp_arr[TOTAL_RTP_CID];

    ULONG  ulCompressionType;   /* 压缩类型: 0--所有报文都压缩, 1--只压缩TCP, 2--只压缩non-TCP, 3--禁止压缩所有报文 */
    ULONG  ulRtpCompression;    /* RTP压缩开关: 0--不压缩RTP首部, 1--压缩RTP首部 */
    
    USHORT F_MAX_PERIOD;    /*largest number of compressed non_tcp headers that may be sent without sending a full header ,default is 256*/
    USHORT F_MAX_TIME;      /*compressed headers may not be sent more than F_MAX_TIME seconds after sending last full header.default is 5*/
    USHORT MAX_HEADER;      /*the largest header size in octets that may be compressed,default is 168 octets.
                                which covers 
                                - two IPv6 base headers
                                - a keyed MD5 authentication header
                                - a maximum-sized TCP header
                                MAX_HEADER must be at least 60 octets and at most 65535 octets*/
    USHORT TCP_SPACE;       /*maximum cid value for tcp.default is 15,3-255*/
    USHORT NON_TCP_SPACE;   /*maximum cid value for non-tcp.default is 15,3-999*/
    UCHAR  ucPadding[2];
}IPHC_CONTEXT_ARRAY_S;



/*RTP格式报文的变量编解码数据结构*/
typedef union tagIPHC_RTP_DELTA_TYPE
{
    struct tagIPHC_DELTA_first_struct
    {
#if IPHC_BYTE_ORDER == IPHC_LITTLE_ENDIAN
        ULONG type;         /*the same as above*/
        UCHAR pud;          /*not used here*/
        UCHAR third;        /*third byte of the delta value*/    
        UCHAR second;       /*second byte of the delta value*/
        UCHAR first;        /*first byte of the delta value*/
        /* c0 40 00——first=c0,second=40,third=00 */
        /* bf ff   ——first=bf,second=ff */
#else
        ULONG type;         /*the same as above*/
        UCHAR first;        /*first byte of the delta value*/
        UCHAR second;       /*second byte of the delta value*/
        UCHAR third;        /*third byte of the delta value*/    
        UCHAR pud;          /*not used here*/ /* c0 40 00——first=c0,second=40,third=00 */
        /* c0 40 00——first=c0,second=40,third=00 */
        /* bf ff   ——first=bf,second=ff */
#endif
    }first_struct;
    struct tagIPHC_DELTA_second_struct
    {
        ULONG type;         /*the same as above*/
        LONG  value;        /*delta value*/
    }second_struct;
}IPHC_RTP_DELTA_TYPE_U;
#ifdef __cplusplus
}
#endif

#endif
