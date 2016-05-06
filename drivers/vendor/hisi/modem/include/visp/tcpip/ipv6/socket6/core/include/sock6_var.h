/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock6_var.h
*
*  Project Code: VISP1.5
*   Module Name: 
*  Date Created: 2000-4-3
*        Author: chenbin
*   Description: the global value of socket, they are extern here
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2000-4-3    chenbin          Creat the first version.
*  2006-04-27  luyao            根据编程规范，对文件进行规范化整理
*
*******************************************************************************/


#ifndef        _SOCK6_VAR_H
#define        _SOCK6_VAR_H

#ifdef    __cplusplus
extern    "C"{
#endif


#ifndef MIN
#define MIN(a, b)       ((a) < (b) ? (a) : (b))
#endif  /* MIN */
#ifndef MAX
#define MAX(a, b)       ((a) > (b) ? (a) : (b))
#endif



#define  SYSTRC_IPV6_SOCK6_BASE        9
/* Macros defined for systrace implementation. Each maro defines a file ID */
#define IP6_SOCK_PMTU_C    ((SYSTRC_IPV6_SOCK6_BASE << 8) + 010)
#define IP6_SOCK_PCB6_C    ((SYSTRC_IPV6_SOCK6_BASE << 8) + 011)
#define IP6_SOCK_CMD_C    ((SYSTRC_IPV6_SOCK6_BASE << 8) + 012)
#define IP6_SOCK_COMP_C    ((SYSTRC_IPV6_SOCK6_BASE << 8) + 014)

/* Variables for lisence enable/disable */
#define IP6_SOCK6_ENABLE_CLI 1
#define IP6_SOCK6_DISABLE_CLI 0

/* end of lisence related variables */


/*********************************************************
*  for  call back
*********************************************************/
extern PMTU_CALLBACKUP_SET_S    stPmtuCallBack ;

extern SOSB6_CALLBACUP_SET_S       stSOSB6CallBack   ;

extern IN6PCB_CALLBACUP_SET_S stIN6PCBCallBack ;




extern LONG         lRemote6HostTotal;
extern SOCKHOST_S  st6Host[MAXHOSTNUM];



/* VRPV5_IPV6_DEV_ENH BEGIN  - Rajesh S  13-06-2003  for vrp5.0 */

extern IN6ADDR_S   stZeroIn6Addr; /* Zero address */

 /* VRPV5_IPV6_DEV_ENH END  */


/* VRPV5_IPV6_DEV_ENH BEGIN  - Rajesh S  13-06-2003  for vrp5.0 */
extern IN6PCB_S         g_stTcpIn6pcbConnHead; /* head of queue of active tcpcb's */
extern IN6PCBHASH_S       g_stTcp6Hash;  /* tcp hash table structure */
  /* VRPV5_IPV6_DEV_ENH END  */


/* VRPV5_IPV6_DEV_ENH BEGIN  - Rajesh S  13-06-2003  for vrp5.0 */
extern IN6PCB_S   g_stUdpIn6pcbConnHead;
extern IN6PCBHASH_S g_stUdp6Hash;
  /* VRPV5_IPV6_DEV_ENH END  */


/* VRPV5_IPV6_DEV_ENH BEGIN  - Rajesh S  13-06-2003  for vrp5.0 */
/*********************************************************
*  for RAWIP
*********************************************************/
extern IN6PCB_S             g_stRawIn6pcb;   /* inpcb of rawip6 */
extern IN6ADDR_S            g_stIn6AddrAny;
  /* VRPV5_IPV6_DEV_ENH END  */

/*sunil added for Sock6 cli disable */
extern ULONG g_ulSOCK6CliState;
/*end of addition for Sock6 cli disable */

extern SOCKDBUGFILTRD_S  g_stDbugSock6Filter;
extern ULONG g_ulSock6DbugFlag ;

  
#define IP6   41



extern IP_SOCK_SH_CALLBACUP_SET_S g_stSOCK6CallBack;
extern SOCK_MOD_INFO_S g_stSOCK6ModInfo;
extern struct IIF_COMP_DNSC_ComIntFUNVtbl       *g_pstSOCK6DNSCVtbl;
/* add by l57500,06/12/08, for get pathmtu in sock6_hc.c */
extern struct IIF_IP6_PMTU_ComIntCFGVtbl    *g_pstSock6PmtuCfgVtbl;  


#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif

