/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ping_sh_info.h
*
*  Project Code: VISP1.5
*   Module Name: ping
*  Date Created: 2000-06-21
*        Author: Luojiewen
*   Description:  本文件定义了Ping模块的错误码
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2000-06-21  Luojiewen        Creat the first version.
*  2006-04-27  luyao            根据编程规范，对文件进行规范化整理
*
*******************************************************************************/

#ifndef _PING_INFO_H_
#define _PING_INFO_H_


#ifdef __cplusplus
extern "C" {
#endif
    
/*------------------------------------------------------------------------*/
/* Index of Message                                                       */
/*------------------------------------------------------------------------*/
 

enum enum_PING 
 {
    PING_PING=0, 
    PING_PROTOCOL6,
    PING_PROTOCOL4,
    PING_SETSNDREQ_COUNT,
    PING_SNDREQ_COUNT,
    PING_REC_ROUTE,
    PING_SEND_INTERFACE,
    PING_INTERFACE_TYPE,
    PING_INTERFACE_NUMBER,
    PING_INTERFACE_NAME,
    PING_SETTTL_VALUE,
    PING_TTL_VALUE,
    PING_REOMTE_ADDR,
    PING_SETTOS_VALUE,
    PING_TOS_VALUE,
    PING_SETVPN_INSTANSE,
    PING_VPN_INSTANSE,
    PING_SHOW_NORESPONSE,
    PING_NO_RESLOVENAME,
    PING_NO_DISPLAYOTHER,
    PING_OPEN_SODEBUG,
    PING_TIMEOUT_VALUE,
    PING_SETTIMEOUT_VALUE,
    PING_REQ_LENGTH,
    PING_SETREQ_LENGTH,
    PING_FILL_PATTERN,
    PING_SETFILL_PATTERN,
    PING_SET_SOURCEADDRESS,
    PING_SOURCEADDRESS,
    PING_SETSENDICMP_INTERAVL,
    PING_SENDICMP_INTERAVL,
    PING_SET_MORETIME,
    PING_MORETIME,
    PING_MAX,
};

/*注意:
如果修改错误码，请同步修改ping_sh_info.c文件中的
CHAR * Inf_Ping_En[]和CHAR * Inf_Ping_Ch[] 描述信息*/
enum enumPing6String
{
    PING_PING_UNKNOWN_HOST =0,          /* 0 */
    PING_PING_OUT_MEMORY,               /* 1 */
    PING_SOCKET_ERROR,                  /* 2 */
    PING_RECORD_ROUTE_ERROR,            /* 3 */
    PING_TITLE,                         /* 4 */
    PING_TITLE_EXT,                     /* 5 */
/* End of modification */
    PING_REQUEST_TIME_OUT,              /* 6 */
    PING_PING_RECVFORM_ERROR,           /* 7 */
    PING_PING_INFO_DISPLAY,             /* 8 */
    PING_PING_PACKET_SHORT,             /* 9 */
    /* First page */    
    PING_REPLY_INFO,                    /* 10 */
    PING_REPLY_INFO6,                   /* 11 */    
    PING_DELAY_TIME,                    /* 12 */
    PING_DUP,                           /* 13 */
    PING_WRONG_DATA_INFO,               /* 14 */
    PING_BYTES_INFO,                    /* 15 */
    PING_LOOSE_RECORD_ROUTE,            /* 16 */
    PING_SAME_ROUTE,                    /* 17 */
    PING_RECORD_ROUTE,                  /* 18 */
    PING_NOP,                           /* 19 */
    PING_UNKNOWN_OPTION,                /* 20 */
    PING_PING_STATISTICS,               /* 21 */
    PING_PACKET_TRANSMIT_NUMBER,        /* 22 */
    PING_PACKET_RECEIVED,               /* 23 */
    /* second page */
    PING_DUPLICATE,                     /* 24 */
    PING_SOMEBODY_PRINT_PACKET,         /* 25 */
    PING_PACKET_LOSS,                   /* 26 */
    PING_ROUND_TRIP,                    /* 27 */
    PING_ECHO_REPLY,                    /* 28 */
    PING_DEST_NET_UNREACH,              /* 29 */
    PING_DEST_HOST_UNREACH,             /* 30 */
    PING_DEST_PROTOCOL_UNREACH,         /* 31 */
    PING_DEST_PORT_UNREACH,             /* 32 */
    PING_FRAG_AND_DF,                   /* 33 */
    PING_SOURCE_ROUTE_FAILED,           /* 34 */
    PING_DEST_UNREACH_CODE,             /* 35 */
    PING_SOURCE_QUENCH,                 /* 36 */
    PING_REDIRECT_NETWORK,              /* 37 */
    PING_REDIRECT_HOST,                 /* 38 */
    PING_SERVICE_NETWORK_REDIRECT,      /* 39 */
    PING_SERVICE_HOST_REDIRECT,         /* 40 */
    PING_REDIRECT_BAD_CODE,             /* 41 */
    PING_NEW_ADDR,                      /* 42 */
    /* third page */
    PING_ECHO_REQUEST,                  /* 43 */
    PING_TIME_LIVE_EXCEED,              /* 44 */
    PING_FRAG_REASSEMBLY_EXCEED,        /* 45 */
    PING_TIME_EXCEED_CODE,              /* 46 */
    PING_PARAM_PROBLEM_POINTER,         /* 47 */
    PING_TIMESTAMP,                     /* 48 */
    PING_TIMESTAMP_REPLY,               /* 49 */
    PING_INFO_REQUEST,                  /* 50 */
    PING_INFO_REPLY,                    /* 51 */
    PING_ADDR_MASK_REQUEST,             /* 52 */
    PING_ADDR_MASK_REPLY,               /* 53 */
    PING_BAD_ICMP_TYPE ,                /* 54 */
    PING_VR_HL_TOS,                     /* 55 */
    PING_TCP_INFO,                      /* 56 */
    PING_UDP_INFO,                      /* 57 */
    PING_PATTERN_SPECIFY_PROMPT,        /* 58 */
    PING_PATTERN,                       /* 59 */
    PING_SELECTLOCADDR,                 /* 60 */
    PING_ERRIN,                         /* 61 */
    PING6_INPUT_IFNET,                  /* 62 */
    PING6_SEND_ERROR,                   /* 63 */
    PING6_INVALID_SOURCE,               /* 64 */
    PING6_SOURCE_SETFAILED,             /* 65 */
    PING_HOST_RESOLVED,                 /* 66 */
    PING_UNKNOWN_VRF,                   /* 67 */
    PING_INVALID_TTL,                   /* 68 */
    PING_INVALID_TOS,                   /* 69 */
    PING_IPV6_UNSPECIFIED,              /* 70 */
    PING_SOURCEADDR_ERROR,              /* 71 */
    PING_DESTADDR_ERROR,                /* 72 */
    PING_INTERFACENAME_ERR,             /* 73 */
    PING_GETINTERFACEINFO_ERR,          /* 74 */
    PING_INTERADDR_ERR,                 /* 75 */
    PING_INTERNAME_ADDRERR,             /* 76 */
    PING_INTERNAME_MADDRERR,            /* 77 */
    PING_NO_INTERFACENAME,              /* 78 */
    PING_FILL_PACKET_ERR,               /* 79 */
    PING_INVAILD_ADDRESS,               /* 80 */
    PING_UNABLE_GETADDR,                /* 81 */
    PING_BADPACKETLEN,                  /* 82 */
    PING_BADPADLEN,                     /* 83 */
    PING_BADRECVLEN,                    /* 84 */
    PING_IP_HEAD,                       /* 85 */      
    PING_STRING,                        /* 86 */
    PING_NEEDFRAG                       /* 87 */
};

/*Ping6 注册命令用到的信息*/
/*
extern VRP_INFORMATION strPing_Info[];
*/
extern ULONG g_ulPingExecInforIndex;
extern CHAR * Inf_Ping_Ch[];
extern CHAR * Inf_Ping_En[];

#ifdef __cplusplus
}
#endif


#endif




