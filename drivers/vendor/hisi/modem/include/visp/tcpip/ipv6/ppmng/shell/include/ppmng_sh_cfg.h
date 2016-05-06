/****************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited        
*                          All Rights Reserved                                 
*----------------------------------------------------------------
*                              ppmng_sh_cfg.h                                     
*                                                                              
*    Project Code: VRP5.0                                                      
*    Module Name:  IP6 BASIC PP                                                
*    Create Date:  2003/04/29                                                  
*         Author:  Mahaveer Jain                                               
*     Description: Shell cfg implement header file for PP module               
*-----------------------------------------------------------------
*  Modification History                                                        
*  DATE        NAME             DESCRIPTION                                    
*  ----------------------------------------------------------------
*  2003-06-10  Mahaveer Jain    Create                                         
*******************************************************************/
#ifndef _PP_SH_CFG_H
#define _PP_SH_CFG_H

#ifdef      __cplusplus
extern "C" {
#endif        /* end of __cplusplus */


#define IP6_PP_ENABLE_CLI           1
#define IP6_PP_DISABLE_CLI          0

#define TBL_IP6_FORWARDING                0x01
#define TBL_IP6_DISPLAYSTATISTICS     0x02
#define TBL_IP6_RESETSTATISTICS        0x03
#define TBL_IP6_DEBUG                           0x04
#define TBL_IP6_REDIRECT                      0x05
#define TBL_IP6_MAINFRAG                      0x06

#define SID_IP6_PP_BUILDRUN     0x100000

#define IP6_PPMNG_SH_CONFIG ((SYSTRC_IPV6_PPMNG_BASE << 8) + 40) 
#define IP6_PPMNG_SH_HA ((SYSTRC_IPV6_PPMNG_BASE << 8) + 41) 
#define IP6_PPMNG_SH_IC ((SYSTRC_IPV6_PPMNG_BASE << 8) + 42)
#define IP6_PPMNG_SH_INIT ((SYSTRC_IPV6_PPMNG_BASE << 8) + 43) 
#define IP6_PPMNG_SH_LCS ((SYSTRC_IPV6_PPMNG_BASE << 8) + 44) 
#define IP6_PPMNG_SH_SSA ((SYSTRC_IPV6_PPMNG_BASE << 8) + 45) 

#define IP6_DISPLAYSTATISTICS_FLAG      0x01
#define IP6_RESETSTATISTICS_FLAG          0x02

#define HOST_TO_NETWORK         0x01
#define NETWORK_TO_HOST         0x02
#define NO_USE(var)     (VOID)(var)
#define MAX_IP6_COMPONENTS 10

#define MIB_IP6_GLOBAL                    0x7

#define CMO_IP6_PP_ENABLE                                CFG_CMO_DEF(MID_COMP_PPMNG, TBL_IP6_FORWARDING, 0)
#define CMO_IP6_PP_DISABLE                               CFG_CMO_DEF(MID_COMP_PPMNG, TBL_IP6_FORWARDING, 1)

#define CMO_IP6_PP_DISPLAYSTATISTICS            CFG_CMO_DEF(MID_COMP_PPMNG, TBL_IP6_DISPLAYSTATISTICS, 0)
#define CMO_IP6_PP_DISPLAYSLOTSTATS             CFG_CMO_DEF(MID_COMP_PPMNG, TBL_IP6_DISPLAYSTATISTICS, 1)

#define CMO_IP6_PP_RESETSTATISTICS                CFG_CMO_DEF(MID_COMP_PPMNG, TBL_IP6_RESETSTATISTICS, 0)
#define CMO_IP6_PP_RESETSLOTSTATISTICS        CFG_CMO_DEF(MID_COMP_PPMNG, TBL_IP6_RESETSTATISTICS, 1)

#define CMO_IP6_PP_DEBUG_PACKET                    CFG_CMO_DEF(MID_COMP_PPMNG, TBL_IP6_DEBUG, 0)

#define CMO_IP6_PP_DEBUG_UNDO                        CFG_CMO_DEF(MID_COMP_PPMNG, TBL_IP6_DEBUG, 1)
/*added by zhangyaping for IP6_FMEF*/
#define CMO_IP6_PP_DEBUG_PACKET_ERROR       CFG_CMO_DEF(MID_COMP_PPMNG, TBL_IP6_DEBUG, 2)
#define CMO_IP6_PP_DEBUG_PACKET_ACL           CFG_CMO_DEF(MID_COMP_PPMNG, TBL_IP6_DEBUG, 3)
#define CMO_IP6_PP_DEBUG_PACKET_DEBUGACL           CFG_CMO_DEF(MID_COMP_PPMNG, TBL_IP6_DEBUG, 4)

#define CMO_IP6_PP_REDIRECT                              CFG_CMO_DEF(MID_COMP_PPMNG, TBL_IP6_REDIRECT, 0)
#define CMO_IP6_PP_REDIRECT_UNDO                    CFG_CMO_DEF(MID_COMP_PPMNG, TBL_IP6_REDIRECT, 1)

#define CMO_IP6_PP_MAINFRAG                         CFG_CMO_DEF(MID_COMP_PPMNG, TBL_IP6_MAINFRAG, 0)
#define CMO_IP6_PP_MAINFRAG_UNDO                    CFG_CMO_DEF(MID_COMP_PPMNG, TBL_IP6_MAINFRAG, 1)


#define IPV6IFSTATSTABLE_TBL 07
#define CFGMIB_IPV6IFENTRY                CFG_CMO_DEF(MID_COMP_PPMNG, IPV6IFSTATSTABLE_TBL, 21)

#define IPV6IFTABLE_TBL      0x2 
#define CFGMIB_IPV6IFINDEX     CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 1)
#define CFGMIB_IPV6IFDESCR     CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 2)
#define CFGMIB_IPV6IFLOWERLAYER     CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 3)
#define CFGMIB_IPV6IFEFFECTIVEMTU     CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 4)
#define CFGMIB_IPV6IFREASMMAXSIZE     CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 5)
#define CFGMIB_IPV6IFIDENTIFIER     CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 6)
#define CFGMIB_IPV6IFIDENTIFIERLENGTH     CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 7)
#define CFGMIB_IPV6IFPHYSICALADDRESS     CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 8)
#define CFGMIB_IPV6IFADMINSTATUS     CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 9)
#define CFGMIB_IPV6IFOPERSTATUS     CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 10)
#define CFGMIB_IPV6IFLASTCHANGE     CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 11)

#define CFGMIB_IPV6IFSTATSINRECEIVES     CFG_CMO_DEF(MID_COMP_PPMNG, IPV6IFSTATSTABLE_TBL, 1)
#define CFGMIB_IPV6IFSTATSINHDRERRORS     CFG_CMO_DEF(MID_COMP_PPMNG, IPV6IFSTATSTABLE_TBL, 2)
#define CFGMIB_IPV6IFSTATSINTOOBIGERRORS     CFG_CMO_DEF(MID_COMP_PPMNG, IPV6IFSTATSTABLE_TBL, 3)
#define CFGMIB_IPV6IFSTATSINNOROUTES     CFG_CMO_DEF(MID_COMP_PPMNG, IPV6IFSTATSTABLE_TBL, 4)
#define CFGMIB_IPV6IFSTATSINADDRERRORS     CFG_CMO_DEF(MID_COMP_PPMNG, IPV6IFSTATSTABLE_TBL, 5)
#define CFGMIB_IPV6IFSTATSINUNKNOWNPROTOS     CFG_CMO_DEF(MID_COMP_PPMNG, IPV6IFSTATSTABLE_TBL, 6)
#define CFGMIB_IPV6IFSTATSINTRUNCATEDPKTS     CFG_CMO_DEF(MID_COMP_PPMNG, IPV6IFSTATSTABLE_TBL, 7)
#define CFGMIB_IPV6IFSTATSINDISCARDS     CFG_CMO_DEF(MID_COMP_PPMNG, IPV6IFSTATSTABLE_TBL, 8)
#define CFGMIB_IPV6IFSTATSINDELIVERS     CFG_CMO_DEF(MID_COMP_PPMNG, IPV6IFSTATSTABLE_TBL, 9)
#define CFGMIB_IPV6IFSTATSOUTFORWDATAGRAMS     CFG_CMO_DEF(MID_COMP_PPMNG, IPV6IFSTATSTABLE_TBL, 10)
#define CFGMIB_IPV6IFSTATSOUTREQUESTS     CFG_CMO_DEF(MID_COMP_PPMNG, IPV6IFSTATSTABLE_TBL, 11)
#define CFGMIB_IPV6IFSTATSOUTDISCARDS     CFG_CMO_DEF(MID_COMP_PPMNG, IPV6IFSTATSTABLE_TBL, 12)
#define CFGMIB_IPV6IFSTATSOUTFRAGOKS     CFG_CMO_DEF(MID_COMP_PPMNG, IPV6IFSTATSTABLE_TBL, 13)
#define CFGMIB_IPV6IFSTATSOUTFRAGFAILS     CFG_CMO_DEF(MID_COMP_PPMNG, IPV6IFSTATSTABLE_TBL, 14)
#define CFGMIB_IPV6IFSTATSOUTFRAGCREATES     CFG_CMO_DEF(MID_COMP_PPMNG, IPV6IFSTATSTABLE_TBL, 15)
#define CFGMIB_IPV6IFSTATSREASMREQDS     CFG_CMO_DEF(MID_COMP_PPMNG, IPV6IFSTATSTABLE_TBL, 16)
#define CFGMIB_IPV6IFSTATSREASMOKS     CFG_CMO_DEF(MID_COMP_PPMNG, IPV6IFSTATSTABLE_TBL, 17)
#define CFGMIB_IPV6IFSTATSREASMFAILS     CFG_CMO_DEF(MID_COMP_PPMNG, IPV6IFSTATSTABLE_TBL, 18)
#define CFGMIB_IPV6IFSTATSINMCASTPKTS     CFG_CMO_DEF(MID_COMP_PPMNG, IPV6IFSTATSTABLE_TBL, 19)
#define CFGMIB_IPV6IFSTATSOUTMCASTPKTS     CFG_CMO_DEF(MID_COMP_PPMNG, IPV6IFSTATSTABLE_TBL, 20)

enum enum_IP6
{
    IP6_DEBUGGING_IPV6,
    IP6_DEBUGGING_PACKET,
    /*added by zhangyaping for IP6_FMEF*/
    IP6_DEBUGGING_PACKET_ERROR,
    IP6_DEBUGGING_PACKET_ACL,
    IP6_STAT_IPV6,
    IP6_STATISTICS,
    IP6_FORWARDING_IPV6,         
    IP6_SLOT,
    IP6_SLOTNUMBER,
    IP6_REDIRECT_IP6,
    IP6_REDIRECT_ICMPV6,
    IP6_REDIRECT_REDIRECT,
    IP6_MAIN_FRAG
};

ULONG IP6_PP_SH_CmdReg();

typedef struct tagIP6_STAT_REQUEST
{
    ULONG   ulReqTypeFlag;          
    ULONG   ulSlotNumber;           
}IP6STAT_REQUEST_S;

typedef struct tagIP6MIBMSG
{
    ULONG          ulIpv6IfIndex;
    ULONG          ulcfgMibIP6Stats;
    UCHAR          ucFlag;        /* SET, GET or GET_NEXT   */
    ULONG          ulData;
} IP6MIBMSG_S;      

typedef struct tagDisplayMSG
{
    ULONG          ulFlag;        /* Display or Reset Statistics */
} IP6_Display_MSG_S;      

typedef struct tagClearIp6CountersReply
{
    ULONG    ulClearResult;
} IP6_CLEARCOUNTERS_REPLY_S;

typedef struct tagIP6_PLUGIN_DATA
{
    ULONG ulForwardingFlag;
    ULONG ulDebugFlag;
    /*added by zhangyaping for IP6_FMEF*/
    ULONG ulErrpktDebugFlag;
    ULONG ulAclNumber;
    
} IP6_PLUGIN_DATA_S;

VOID IP6_PP_SH_CmdReg_Forwarding();
VOID IP6_PP_SH_CmdReg_DisplayStatistics();
VOID IP6_PP_SH_CmdReg_ResetStatistics();
VOID IP6_PP_SH_CmdReg_Debug();
ULONG IP6_PP_SH_RegBuildRun();
ULONG IP6_PP_SH_ConfigProc( VOID *pMsgRcv, VOID **ppMsgSnd );
VOID IP6_PP_SH_CmdPro_Forwarding (VOID *pMsgRcv, VOID **ppMsgSnd);
VOID IP6_PP_SH_CmdPro_DisplayStatistics( VOID * pMsgRcv, VOID **ppMsgSnd );
ULONG IP6_PP_SH_CmdPro_ResetStatistics( VOID * pMsgRcv, VOID **ppMsgSnd );
VOID IP6_PP_SH_CmdPro_Redirect(VOID *pMsgRcv, VOID **ppMsgSnd);
VOID IP6_PP_SH_GlobalTableMib (VOID * pMsgRcv, VOID **ppMsgSnd);
VOID IP6_PP_SH_CmdPro_Debug(VOID *pMsgRcv, VOID **ppMsgSnd);
ULONG IP6_PP_SH_RegBuildRunCallBack(CHAR szSectionName[SECTION_NAME_LEN], 
        CHAR** pszBuildRunInfo);
VOID IP6_PP_SH_CmdReg_Redirect();

ULONG IP6_PP_SH_CmdRegRPC();

ULONG IP6_PP_SH_StatShowAndClearCallBack(ULONG ulSrcNode, 
        ULONG ulSrcModuleId, VOID *pReceiveData,  ULONG ulReceiveDataLen,
        VOID **ppSendData, ULONG *pulSendDataLen);

   /*w39533 2004-11-08 sync D24*/
  /* Begin : Defect ID: BYAD11918,     Modifier:Rajesh,   Date:2004/9/30 
           Reason   : To resolve component issues*/
ULONG IP6_PP_SH_RegisterCliChangeNotify(ULONG (* pfIP6_PP_NotifyCliChange)(ULONG ulCliState));


ULONG IP6_PP_SH_MibCallBack(ULONG ulSrcNode, ULONG ulSrcModuleId, VOID *pReceiveData,
        ULONG ulReceiveDataLen, VOID **ppSendData, ULONG *pulSendDataLen);

ULONG IP6_PP_SH_NotifyCliChange(ULONG ulCliState);

#ifdef      __cplusplus
}
#endif        /* end of __cplusplus */
#endif

