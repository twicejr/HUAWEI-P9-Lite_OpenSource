/**********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited        
*                          All Rights Reserved                                 
*----------------------------------------------------------------------
*                              Ippmng.h                                            
*    Project Code:  VRP5.0                                                     
*    Module Name:  IP6 PP                                                     
*    Create Date:  2003/06/09                                               
*    Author:       Mahaveera Jain                                             
*    Description:  To define data structure for PP component     
*-----------------------------------------------------------------------
*  Modification History                                                        
*  DATE        NAME             DESCRIPTION                                    
*  ----------------------------------------------------------------------
*  2003-06-09  Mahaveer Jain    Create                       
*  2006-05-11   luyao           为支持ARM CPU字节对齐特性，修改结构。
*************************************************************************/
#ifndef _IP6_IPPMNG_H
#define _IP6_IPPMNG_H

#ifdef __cplusplus
extern "C"{
#endif

#define MAX_KEY_LEN     10

typedef struct tagPP_MOD_INFO_S
{
    ULONG ulModID; /* Module id;*/
    ULONG ulSubModID; /* Sub module id;*/
    ULONG ulLocalIPC_Tid; /* IPC tunnel id for module self;*/
    ULONG ulPeerIPC_Tid; /* IPC tunnel id for peer module, such as server tid in client server model;*/
} IP6_PP_MOD_INFO_S;

#define IP6_PP_TIMER  0x10

#define IP6_PP_FAST_TIMER 0x2
#define IP6_PP_FASTTIMEOUT 200
#define IP6_PP_SLOW_TIMER 0x1
#define IP6_PP_SLOWTIMEOUT 500


typedef struct tagPP_Msg_S
{
    ULONG          ulMajorMsgType;   /* IP6_PP_TIMER_TIMEOUT.. */
    ULONG          ulSubMsgType;     
}IP6_PP_MSG_S;

/* Timeout message */
typedef struct tag_PP_Timer_Msg_S
{
   ULONG          ulMajorMsgType;   
   ULONG          ulSubMsgType;     
   VOID          *pData;            
}IP6_PP_Timer_MSG_S;

/* default state of the forwarding enabling */
#define IP6_PP_FORWARD_DEF 0x0

/* 下面定义的是IPv6基本协议处理模块的SID */
#define SID_IP6_GETVALIDPKT         0x001
#define SID_IP6_ADDHDRS             0x002
#define SID_IP6_MULTILOOPBACK       0x003
#define SID_IP6_FRAGCOPY            0x004
#define SID_IP6_FRAGHDRCHECK        0x005
#define SID_IP6_UNFRAGPARTALLOC     0x006
#define SID_IP6_FRAGMENT            0x007
#define SID_IP6_FRAG_MAKECONT       0x008
#define SID_IP6_FRAG_CREATREASSQ    0x009
#define SID_IP6_FRAG_CREATFRAG      0x00a
#define SID_IP6_FRAG_CONCATENATE    0x00b
#define SID_IP6_BUILDRUN            0x00c
#define SID_IP6_CREATRCVCTRL        0x00d
#define SID_IP6_CREATOPTION         0x00e
#define SID_IP6_CREATMULTIOPTION    0x00f
#define SID_IP6_HBHHEADER           0x010
#define SID_IP6_DESTHEADER          0x011
#define SID_IP6_ROUTEHEADER         0x012
#define SID_IP6_GETNEXTHDR          0x013
#define SID_IP6_GETPREVHDR          0x014
#define SID_IP6_PP_PM_INTER         0x015
#define SID_IP6_PP_PM               0x016
#define SID_IP6_PP_HA               0x017
#define SID_PP_TIMER                0x018
#define SID_IP6_EXTHEADER           0x019

#define IP6_PP_SOURCE_CLI 0x2
#define IP6_PP_SOURCE_LCS 0x3

/* For Sys Trace */
#define IP6_PP                      0x0010

typedef struct tagIP6_PP_SPECS_FUN_VALUE
{
    UCHAR uchKey[MAX_KEY_LEN];
    UCHAR ucPadding[4-((MAX_KEY_LEN)%4)];
    ULONG ulAvail_Value; /*0 Unavailable, 1: Available */
} IP6_PP_SPECS_FUN_VALUE_S;


typedef struct tagIP6_PP_SH_CALLBACUP_SET_S
{
    ULONG (*pfIP6_PP_SH_ShellAsynEnQue)(IP6_PP_Timer_MSG_S *pstMsg); 
    VOID (*pfIP6_PP_SH_SendInfo2IC)( MBUF_S *pstMBuf, ULONG ulIfIndex, const CHAR *pszInfo,
                                     const CHAR *pszPrompt); 
    /*syn D038 by x36308 2005-7-5*/
    VOID (*pfIP6_PP_SH_SendLogInfo2IC) (ULONG ulLogType, UCHAR *pszInfo);
    ULONG (*pfIP6_PP_PositionRegHook)(ULONG); 
    /*w39533 2004-11-08 sync D24*/
    /* Begin : Defect ID: BYAD11918,     Modifier:Rajesh,   Date:2004/9/30 
    Reason   : To resolve component issues*/
    ULONG (*pfIP6_PP_SH_RegisterCliChangeNotify)(ULONG (* pfIP6_PP_NotifyCliChange)(ULONG ulCliState));
} IP6_PP_SH_CALLBACUP_SET_S; 

#ifdef __cplusplus
}
#endif

#endif

