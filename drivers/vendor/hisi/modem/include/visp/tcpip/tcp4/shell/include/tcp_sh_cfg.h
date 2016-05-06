/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcp_sh_cfg.h
*
*  Project Code: VISP1.5
*   Module Name: IP TCP4  
*  Date Created: 2003-04-29
*        Author: Sunil Dutt
*   Description: Shell cfg implement header file for TCP
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2003-04-29  Sunil Dutt       Create the first version.
*
*******************************************************************************/
#ifdef    __cplusplus
extern    "C"{
#endif


#ifndef _TCP_SH_CFG_H
#define _TCP_SH_CFG_H


#define CMOTABID_TCP            0x01

#define TCP_VJ_ALGORITHM        4
#define TCP_UNKNOWN_VALUE       0 

#define IP_TCP_ENABLE_CLI      1
#define IP_TCP_DISABLE_CLI     0


#define OID_TCP_FINTIME         CFG_CMO_DEF(MID_COMP_TCP4,CMOTABID_TCP,1)
#define OID_TCP_SYNTIME         CFG_CMO_DEF(MID_COMP_TCP4,CMOTABID_TCP,2)
#define OID_TCP_WINSIZE         CFG_CMO_DEF(MID_COMP_TCP4,CMOTABID_TCP,3)
#define OID_TCP_DEBUG           CFG_CMO_DEF(MID_COMP_TCP4,CMOTABID_TCP,4)
#define OID_TCP_DEBUGFLAG       CFG_CMO_DEF(MID_COMP_TCP4,CMOTABID_TCP,5)
#define OID_TCP_DEBUG_TRANSA    CFG_CMO_DEF(MID_COMP_TCP4,CMOTABID_TCP,6)
#define OID_TCP_TCPCBADDR       CFG_CMO_DEF(MID_COMP_TCP4,CMOTABID_TCP,7)
#define OID_TCP_SHOW            CFG_CMO_DEF(MID_COMP_TCP4,CMOTABID_TCP,8)

#define OID_TCP_SHOWSTATISTICS  CFG_CMO_DEF(MID_COMP_TCP4,CMOTABID_TCP,9)
#define OID_TCP_CLEARSTATISTICS CFG_CMO_DEF(MID_COMP_TCP4,CMOTABID_TCP,10)
#define OID_TCP_DEBUG_TASKID    CFG_CMO_DEF(MID_COMP_TCP4,CMOTABID_TCP,11)
#define OID_TCP_DEBUG_SOCKID    CFG_CMO_DEF(MID_COMP_TCP4,CMOTABID_TCP,12)


/* 定义TABLE ID, 注意定义的TABLE ID不能和TCP_CMO.H中定义的TABLE ID冲突 */
#define TCP_GLOBAL       0x10
#define TCP_Conn         0x11
#define UDP_GLOBAL       0x12
#define UDP_TABLE        0x13

/*added by xujin for md5 trap*/
#define HWTCPTrap_TBL 0x14

#define CFGMIB_HWTCPPROTOCOL     CFG_CMO_DEF(MID_COMP_TCP4, HWTCPTrap_TBL, 1)   /*modifed by x36317 2004-10-27*/
#define CFGMIB_HWTCPVRFNAME      CFG_CMO_DEF(MID_COMP_TCP4, HWTCPTrap_TBL, 2)   /*modifed by x36317 2004-10-27*/

/* 定义TCP非表型变量的CMO */
#define CFGMIB_TCPRTOALGORITHM           CFG_CMO_DEF( MID_COMP_TCP4, TCP_GLOBAL, 1 )
#define CFGMIB_TCPRTOMIN                 CFG_CMO_DEF( MID_COMP_TCP4, TCP_GLOBAL, 2 )
#define CFGMIB_TCPRTOMAX                 CFG_CMO_DEF( MID_COMP_TCP4, TCP_GLOBAL, 3 )
#define CFGMIB_TCPMAXCONN                CFG_CMO_DEF( MID_COMP_TCP4, TCP_GLOBAL, 4 )
#define CFGMIB_TCPACTIVEOPENS            CFG_CMO_DEF( MID_COMP_TCP4, TCP_GLOBAL, 5 )
#define CFGMIB_TCPPASSIVEOPENS           CFG_CMO_DEF( MID_COMP_TCP4, TCP_GLOBAL, 6 )
#define CFGMIB_TCPATTEMPTFAILS           CFG_CMO_DEF( MID_COMP_TCP4, TCP_GLOBAL, 7 )
#define CFGMIB_TCPESTABRESETS            CFG_CMO_DEF( MID_COMP_TCP4, TCP_GLOBAL, 8 )
#define CFGMIB_TCPCURRESTAB              CFG_CMO_DEF( MID_COMP_TCP4, TCP_GLOBAL, 9 )
#define CFGMIB_TCPINSEGS                 CFG_CMO_DEF( MID_COMP_TCP4, TCP_GLOBAL, 10 )
#define CFGMIB_TCPOUTSEGS                CFG_CMO_DEF( MID_COMP_TCP4, TCP_GLOBAL, 11 )
#define CFGMIB_TCPRETRANSSEGS            CFG_CMO_DEF( MID_COMP_TCP4, TCP_GLOBAL, 12 )
#define CFGMIB_TCPINERRS                 CFG_CMO_DEF( MID_COMP_TCP4, TCP_GLOBAL, 13 )
#define CFGMIB_TCPOUTRSTS                CFG_CMO_DEF( MID_COMP_TCP4, TCP_GLOBAL, 14 )

/*  定义tcpConnTable表型变量的CMO */
#define CFGMIB_TCPCONNSTATE              CFG_CMO_DEF( MID_COMP_TCP4, TCP_Conn, 1 )
#define CFGMIB_TCPCONNLOCALADDRESS       CFG_CMO_DEF( MID_COMP_TCP4, TCP_Conn, 2 )
#define CFGMIB_TCPCONNLOCALPORT          CFG_CMO_DEF( MID_COMP_TCP4, TCP_Conn, 3 )
#define CFGMIB_TCPCONNREMADDRESS         CFG_CMO_DEF( MID_COMP_TCP4, TCP_Conn, 4 )
#define CFGMIB_TCPCONNREMPORT            CFG_CMO_DEF( MID_COMP_TCP4, TCP_Conn, 5 )

enum enum_TCP 
{
    TCP_CMDELEMENT_TCPCFG, 
    TCP_CMDELEMENT_IPV6CFG,
    TCP_CMDELEMENT_TIMER,
    TCP_CMDELEMENT_SYNTIME, 
    TCP_CMDELEMENT_INTEGER2_600, 
    TCP_CMDELEMENT_FINWAIT, 
    TCP_CMDELEMENT_INTEGER76_3600, 
    TCP_CMDELEMENT_WINSIZE, 
    TCP_CMDELEMENT_INTEGER1_32, 
    TCP_CMDELEMENT_TCPDBUG, 
    TCP_CMDELEMENT_TCPPKT, 
    TCP_CMDELEMENT_TCPTSC, 
    TCP_CMDELEMENT_TCPMD5,
    TCP_CMDELEMENT_TCPSHOW, 
    TCP_CMDELEMENT_TCPBRIEF, 
    TCP_CMDELEMENT_TASKID,
    TCP_CMDELEMENT_SOCKID,    
    TCP_CMDELEMENT_TCPSTAT,
    TCP_CMDELEMENT_TCPCB,
    TCP_CMDELEMENT_TCPCBADDR    
    
};

VOID PrintState(SHORT state,CHAR *pBuf, ULONG ulLen);

VOID TCP_GlobalTableMib ( VOID * pMsgRcv, VOID **ppMsgSnd );
VOID TCP_ConnTableMib( VOID * pMsgRcv, VOID **ppMsgSnd );

VOID TCP_RegToCmdLine();

VOID TCP_ShowStatist(ULONG ulExecID);
VOID TCP_ResetStatist(VOID);
VOID TCP_ShowTCP(ULONG ulExecID);
VOID TCP_ShowTCPCB(void *pAddress,ULONG ulExecID_TCP);
#endif

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */
     

