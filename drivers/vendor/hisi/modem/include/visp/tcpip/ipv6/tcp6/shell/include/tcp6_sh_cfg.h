/****************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*----------------------------------------------------------------
*                              Tcp6_sh_cfg.h
*
*    Project Code: VRP5.0
*    Module Name : IP6 BASIC PP
*    Version     : Initial Draft
*    Create Date : 2003/04/29
*    Author      : Naina Gupta
*    Description : Shell cfg implement header file for PP module
*-----------------------------------------------------------------
*  Modification History
*  DATE        NAME       DESCRIPTION
*  ----------------------------------------------------------------
*  2003-06-10  Naina      Create
*  2006-06-02  Alok       Updated for 14 Fly-Check rules adherence
*                         for IPOSIR-V1R1-IPv6
*  2006-06-20  Arvind     Updated for Component Version Display
*                         changes
*  2006-08-29  Prabhu H   Updated for RFC 4022 MIB implmentation
*  2006-10-19 Suraj+72063 Updated for display default configuration
*******************************************************************/


#ifndef _TCP6_SH_CFG_H
#define _TCP6_SH_CFG_H

#ifdef  __cplusplus
extern "C"{
#endif

#define CMOTABID_TCP6            0x01


#define IP6_TCP6_ENABLE_CLI      1
#define IP6_TCP6_DISABLE_CLI     0

#define TCP6_MAX_STATSTICS_BUFSIZE  2560
#define SID_TCP6_STATSTICS_BUF 100

#define OID_TCP6_FINTIME         CFG_CMO_DEF(MID_TCP6,CMOTABID_TCP6,1)
#define OID_TCP6_SYNTIME         CFG_CMO_DEF(MID_TCP6,CMOTABID_TCP6,2)
#define OID_TCP6_WINSIZE         CFG_CMO_DEF(MID_TCP6,CMOTABID_TCP6,3)
#define OID_TCP6_DEBUG           CFG_CMO_DEF(MID_TCP6,CMOTABID_TCP6,4)
#define OID_TCP6_DEBUGFLAG       CFG_CMO_DEF(MID_TCP6,CMOTABID_TCP6,5)
#define OID_TCP6_DEBUG_TRANSA    CFG_CMO_DEF(MID_TCP6,CMOTABID_TCP6,6)
#define OID_TCP6_TCPCBADDR       CFG_CMO_DEF(MID_TCP6,CMOTABID_TCP6,7)
#define OID_TCP6_SHOW            CFG_CMO_DEF(MID_TCP6,CMOTABID_TCP6,8)

#define OID_TCP6_SHOWSTATISTICS  CFG_CMO_DEF(MID_TCP6,CMOTABID_TCP6,9)
#define OID_TCP6_CLEARSTATISTICS CFG_CMO_DEF(MID_TCP6,CMOTABID_TCP6,10)
#define OID_TCP6_DEBUG_TASKID    CFG_CMO_DEF(MID_TCP6,CMOTABID_TCP6,11)
#define OID_TCP6_DEBUG_SOCKID    CFG_CMO_DEF(MID_TCP6,CMOTABID_TCP6,12)

#define CMO_TCP6_LOCALADDRESS    CFG_CMO_DEF(MID_TCP6,CMOTABID_TCP6,13)
#define CMO_TCP6_LOCALPORT       CFG_CMO_DEF(MID_TCP6,CMOTABID_TCP6,14)
#define CMO_TCP6_FOREIGNADDRESS  CFG_CMO_DEF(MID_TCP6,CMOTABID_TCP6,15)
#define CMO_TCP6_FOREIGNPORT     CFG_CMO_DEF(MID_TCP6,CMOTABID_TCP6,16)

#define CMO_TCP6_DEFCONFIG     CFG_CMO_DEF(MID_TCP6,CMOTABID_TCP6,17)


#define TCP6_GLOBAL         0x10
#define TCP6_CONN           0x11

#define CFGMIB_TCP6RTOALGORITHM      CFG_CMO_DEF(MID_TCP6, TCP6_GLOBAL, 1)
#define CFGMIB_TCP6RTOMIN            CFG_CMO_DEF(MID_TCP6, TCP6_GLOBAL, 2)
#define CFGMIB_TCP6RTOMAX            CFG_CMO_DEF(MID_TCP6, TCP6_GLOBAL, 3)
#define CFGMIB_TCP6MAXCONN           CFG_CMO_DEF(MID_TCP6, TCP6_GLOBAL, 4)
#define CFGMIB_TCP6ACTIVEOPENS       CFG_CMO_DEF(MID_TCP6, TCP6_GLOBAL, 5)
#define CFGMIB_TCP6PASSIVEOPENS      CFG_CMO_DEF(MID_TCP6, TCP6_GLOBAL, 6)
#define CFGMIB_TCP6ATTEMPTFAILS      CFG_CMO_DEF(MID_TCP6, TCP6_GLOBAL, 7)
#define CFGMIB_TCP6ESTABRESETS       CFG_CMO_DEF(MID_TCP6, TCP6_GLOBAL, 8)
#define CFGMIB_TCP6CURRESTAB         CFG_CMO_DEF(MID_TCP6, TCP6_GLOBAL, 9)
#define CFGMIB_TCP6INSEGS            CFG_CMO_DEF(MID_TCP6, TCP6_GLOBAL, 10)
#define CFGMIB_TCP6OUTSEGS           CFG_CMO_DEF(MID_TCP6, TCP6_GLOBAL, 11)
#define CFGMIB_TCP6RETRANSSEGS       CFG_CMO_DEF(MID_TCP6, TCP6_GLOBAL, 12)
#define CFGMIB_TCP6INERRS            CFG_CMO_DEF(MID_TCP6, TCP6_GLOBAL, 14)
#define CFGMIB_TCP6OUTRSTS           CFG_CMO_DEF(MID_TCP6, TCP6_GLOBAL, 15)

#define IPV6TCPCONNTABLE_TBL   5

#define CFGMIB_IPV6TCPCONNLOCALADDRESS  \
                            CFG_CMO_DEF(MID_TCP6, IPV6TCPCONNTABLE_TBL, 1)
#define CFGMIB_IPV6TCPCONNLOCALPORT     \
                            CFG_CMO_DEF(MID_TCP6, IPV6TCPCONNTABLE_TBL, 2)
#define CFGMIB_IPV6TCPCONNREMADDRESS    \
                            CFG_CMO_DEF(MID_TCP6, IPV6TCPCONNTABLE_TBL, 3)
#define CFGMIB_IPV6TCPCONNREMPORT       \
                            CFG_CMO_DEF(MID_TCP6, IPV6TCPCONNTABLE_TBL, 4)
#define CFGMIB_IPV6TCPCONNIFINDEX       \
                            CFG_CMO_DEF(MID_TCP6, IPV6TCPCONNTABLE_TBL, 5)
#define CFGMIB_IPV6TCPCONNSTATE         \
                            CFG_CMO_DEF(MID_TCP6, IPV6TCPCONNTABLE_TBL, 6)

#define TCP6_DBGID_PACKET   IC_INFOID_DEF(MID_TCP6,IC_INFO_DEBUG,0)
#define TCP6_DBGID_TRANSA   IC_INFOID_DEF(MID_TCP6,IC_INFO_DEBUG,1)

#define TBL_TCP6_SHOW_COM_VERSION       0x12


#define CMO_TCP6_SHOW_COM_VERSION      \
                  CFG_CMO_DEF(MID_TCP6, TBL_TCP6_SHOW_COM_VERSION, 1)
#define CMO_TCP6_SHOW_COM_TEST_VERSION \
                  CFG_CMO_DEF(MID_TCP6, TBL_TCP6_SHOW_COM_VERSION, 2)

#define TCP6_MAX_DEFAULTCFG_BUFSIZE 512
#define TCP6_BYTES_TO_KILOBYES 1024
#define TCP6_MAX_STATSTICS_TEMP_BUFSIZE 256

#define TCP6_MAX_STATSTICS_512_BUFSIZE 512

/* To avoid blocking of CPU while getting TCP6 connections this is the limit */
#define TCP6_MAX_CONN_DISPLAY_COUNT 100


/* TCP6 command element objects */
enum enum_TCP6
{
    TCP6_CMDELEMENT_TCPCFG,
    TCP6_CMDELEMENT_IPV6CFG,
    TCP6_CMDELEMENT_TIMER,
    TCP6_CMDELEMENT_SYNTIME,
    TCP6_CMDELEMENT_INTEGER2_600,
    TCP6_CMDELEMENT_FINWAIT,
    TCP6_CMDELEMENT_INTEGER76_3600,
    TCP6_CMDELEMENT_WINSIZE,
    TCP6_CMDELEMENT_INTEGER1_32,
    TCP6_CMDELEMENT_TCPDBUG,
    TCP6_CMDELEMENT_TCPPKT,
    TCP6_CMDELEMENT_TCPTSC,
    TCP6_CMDELEMENT_TCPSHOW,
    TCP6_CMDELEMENT_TCPBRIEF,
    TCP6_CMDELEMENT_TASKID,
    TCP6_CMDELEMENT_SOCKID,
    TCP6_CMDELEMENT_TCPSTAT,
    TCP6_CMDELEMENT_TCPCB,
    TCP6_CMDELEMENT_TCPCBADDR,
    TCP6_CMDELEMENT_SHOWCOM,
    TCP6_CMDELEMENT_SHOWCOMVER,
    TCP6_CMDELEMENT_SHOWCOMTESTVER,
    TCP6_CMDELEMENT_SHOWCOMVERTCP6,
    TCP6_CMDELEMENT_SHOWCOMTESTVERTCP6,
    TCP6_CMDELEMENT_LOCALIP6ADDRESS,
    TCP6_CMDELEMENT_FOREIGNIP6ADDRESS,
    TCP6_CMDELEMENT_LOCALPORT,
    TCP6_CMDELEMENT_FOREIGNPORT,

    TCP6_CMDELEMENT_DISPDEFAULT,
    TCP6_CMDELEMENT_INFO

};

VOID  IP6_TCP6_SH_SHOWTCP6(ULONG ulExecID);
VOID  IP6_TCP6_SH_ShowStatist(ULONG ulExecID);
VOID  IP6_TCP6_SH_ClearStatist(VOID);

/* Reason: Two new APIs "TCP6_Sh_PrintPort" and "TCP6_Sh_PrintState" are
           being duplicated in shell from core to avoid direct access of
           core APIs and "TCP6_ProcessTCPCBString" has been moved to shell
           since it involves processing a string*/
VOID TCP6_Sh_PrintPort(USHORT usPort,CHAR *pszBuf,INT32 i32BufLen);
VOID TCP6_Sh_PrintState(SHORT sState,CHAR *pszBuf,INT32 i32BufLen);

CHAR * Tcp6_SH_inet_ntop6(const CHAR *pszSrcAddr,CHAR *pszDstAddr,
                                  ULONG ulAddrLen);

/* Begin : Moving the prototype to the source file [tcp6_sh_cfg.c ]
   since it leads to dependency compilation errors in
   tcp6_sh_tree.c. Moreover, this function is called
   only from tcp6_sh_cfg.c and also defined there */

ULONG IP6_TCP6_SH_ShowConnStats(IN6ADDR_S*pstLAddr, ULONG ulLPort,
                                                                       IN6ADDR_S *pstFAddr, ULONG ulFPort,
                                                                       ULONG ulExecID);
ULONG IP6_TCP6_SH_ShowPerTcp6ConnStats_fromSocket(ULONG ulSockId, ULONG ulTaskId, ULONG ulExecID);



//extern void vos_printf(char *fmt, ...);

extern struct IIF_IP6_TCP6_INITVtbl   * g_pstTCP6ComInitTable;
extern struct IIF_IP6_TCP6_CFGVtbl   * g_pstTCP6ComCfgTable;
extern struct IIF_IP6_TCP6_FUNVtbl   * g_pstTCP6ComFunTable;

/* Added by Anand - V1R7 Workspace Integration */
#define TCP6_MEM_ZERO(m_pBufPtr, m_ulBufLen)\
            (VOID)TCPIP_Mem_Set((CHAR *)(m_pBufPtr), 0, (m_ulBufLen))

/* Added by Anand - V1R7 Workspace Integration */
#define TCP6_MEM_SET(m_pBufPtr, m_cBufVal, m_ulBufLen)\
            (VOID)TCPIP_Mem_Set((CHAR *)(m_pBufPtr), (m_cBufVal), (m_ulBufLen))

extern UINT8 g_u8Tcp6CookieSwitch;

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* #ifndef _TCP6_SH_CFG_H */

