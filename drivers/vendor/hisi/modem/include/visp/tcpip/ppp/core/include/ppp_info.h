/************************************************************************
 *                                                                      *
 *                          模块名PPP_info.h                            *
 *                                                                      *
 *  Project Code:                                                       *
 *  Create Date:                                                        *
 *  Author:                                                             *
 *  Modify Date:                                                        *
 *            VRPV3R001M07，刘凯，2002/11/29                            *
 *                -- 在enum_PPP中增加了PPP_VJCOMP_DEBUG                 *
 *                -- 对链路质量的定义增加了编译宏                       *
 *            VRPV3R001M07, liminglei 27056, 2002.10.29                 *
 *                -- 在enum_PPP中增加了                                 *
 *                                    PPP_REQUEST_CALLBACK              *
 *                                    PPP_NTSTRING_CALLBACK             *
 *                                    PPP_NTSTRINGCB_HELP               *
 *                                    PPP_QUALITY_CLOSEPER              *
 *                                    PPP_QUALITY_RESUMEPER             *
 *  Document:                                                           *
 *  Function:                                                           *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *  Copyright 2000-2002 VRP3.1 Team Beijing Institute HuaWei Tech, Inc. *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *    信息字符串索引外部引用头文件。                                    *
 *                                                                      *
 ************************************************************************/

#ifdef    __cplusplus
extern "C"{
#endif

enum enum_ppp 
{
    PPP_ENPPP,
    PPP_PPP,
    PPP_NEGO_PARAMETER, 
    PPP_NEGO_TIMEOUT, 
    PPP_NEGO_TIMEOUT_SECOND, 
    PPP_ENCAP, 
    PPP_COMPRESS_METHOD, 
    PPP_STAC_LZS, 
    PPP_DEBUG_INFORMATION, 
    PPP_CORE_DEBUG, 
    PPP_IPCP_DEBUG, 
    PPP_LCP_DEBUG, 
    PPP_ERROR_DEBUG, 
    PPP_EVENT_DEBUG, 
    PPP_PACKET_DEBUG, 
    PPP_STATE_DEBUG, 
    PPP_ALL_DEBUG, 
    PPP_EVENT_CORE, 
    PPP_CCP_DEBUG, 
    PPP_SCP_DEBUG, 
    PPP_IP_DEBUG, 
    PPP_PAP_DEBUG, 
    PPP_CHAP_DEBUG, 
    PPP_DEBUG_INTERFACE, 
    /*
    PPP_INTERFACE_NAME, 
    PPP_INTERFACE_TYPE, 
    PPP_INTERFACE_NUMBER, 
    */
    PPP_OSICP_DEBUG, 
    PPP_OSINPDU_DEBUG, 
    PPP_MPLSCP_DEBUG, 
    PPP_MPLSUNICAST_DEBUG, 
    PPP_MPLSMULTICAST_DEBUG, 
    PPP_MP_DEBUG, 
    PPP_AUTH_TYPE, 
    PPP_AUTH_PAP, 
    PPP_AUTH_CHAP, 
    PPP_CHAP_CALLIN, 
    PPP_DEFAULT_SCHEME,
    PPP_DEFAULT_AUTHLIST, 
    PPP_AUTH_LISTNAME, 
    PPP_SET_ACCOUNT, 
    PPP_DEFAULT_ACCOUNTLIST, 
    PPP_NAMED_ACCOUNTLIST, 
    PPP_CHAP_PARAMETER, 
    PPP_HOSTNAME, 
    PPP_CHAP_HOST_NAME,
    PPP_LOCAL_SECRET, 
    PPP_NOHIDE_PASSWORD, 
    PPP_HIDE_PASSWORD, 
    PPP_USER_PASSWORD0,
    PPP_USER_PASSWORD7,
    /*End of D24898*/
    PPP_PAP_PARAMETER, 
    PPP_HOSTNAME_SECRET, 
    PPP_PAP_NAME, 
    PPP_PAP_PASSWORD, 
    PPP_CALLBACK, 
    PPP_ACCEPT_CALLBACK, 
    PPP_REQUEST_CALLBACK,
    PPP_NTSTRING_CALLBACK,
    PPP_NTSTRINGCB_HELP, 

    PPP_IPCP_INFO,
    PPP_IPCP_DNS,
    PPP_IPCP_DNS_REJECT,
    PPP_IPCP_DNS_ACCEPT,
    PPP_IPCP_DNS_PRIMADDR,
    PPP_IPCP_DNS_SNDADDR,
    PPP_VJCOMP_DEBUG,

    PPP_IP6CP_DEBUG,
    PPP_IP6_DEBUG,

    PPP_PACKET_SEND,
    PPP_ACTION_DEBUG,

/* VRPV3R001M07，刘凯，2002/11/29，end */
    ppp_MAX 
};


/* Added by z43740:增加错误描述, 2006/05/22*/
extern CHAR* g_apszPPPErrorInfo_En[];

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */
