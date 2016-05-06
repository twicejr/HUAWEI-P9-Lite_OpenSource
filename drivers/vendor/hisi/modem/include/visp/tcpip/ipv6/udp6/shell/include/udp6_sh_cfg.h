

/*******************************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-------------------------------------------------------------------------------
*                              udp6_sh_cfg.h
*
*    Project Code: VRP5.0
*    Module Name:  IP6 BASIC UDP6
*    Create Date:  2003/04/29
*         Author:  Sunil Dutt
*     Description: Shell cfg implement header file for UDP6 module
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2003-06-10  Sunil Dutt    Create
*  2006-06-08  Alok          Updated for 14 Fly-Check rules adherence
*                            for IPOSIR-V1R1-IPv6
*  2006-06-20  Arvind        Updated for Component Version Display
*                            changes
*  2007-10-29  Suraj+72063   Updated max. statisticis bufsize & temp bufsize
********************************************************************************
*/

#ifndef _UDP6_SH_CFG_H
#define _UDP6_SH_CFG_H

#ifdef    __cplusplus
extern    "C"{
#endif

#define  CMOTABID_UDP6              0x01

#define UDP6_GLOBAL            0x12
#define UDP6_TABLE             0x13


#define IP6_UDP6_ENABLE_CLI           1
#define IP6_UDP6_DISABLE_CLI          0

#define UDP6_DBUG_OFF 0
#define UDP6_DBUG_ON  1

#define UDP6_DEBUG_UNDO  2

#define CFGMIB_UDP6INDATAGRAMS       CFG_CMO_DEF(MID_UDP6, UDP6_GLOBAL, 1)
#define CFGMIB_UDP6NOPORTS           CFG_CMO_DEF(MID_UDP6, UDP6_GLOBAL, 2)
#define CFGMIB_UDP6INERRORS          CFG_CMO_DEF(MID_UDP6, UDP6_GLOBAL, 3)
#define CFGMIB_UDP6OUTDATAGRAMS      CFG_CMO_DEF(MID_UDP6, UDP6_GLOBAL, 4)


#define IPV6UDPTABLE_TBL                                 5
#define CFGMIB_IPV6UDPLOCALADDRESS   CFG_CMO_DEF(MID_UDP6, IPV6UDPTABLE_TBL, 1)
#define CFGMIB_IPV6UDPLOCALPORT      CFG_CMO_DEF(MID_UDP6, IPV6UDPTABLE_TBL, 2)
#define CFGMIB_IPV6UDPIFINDEX        CFG_CMO_DEF(MID_UDP6, IPV6UDPTABLE_TBL, 3)

#define OID_UDP6_CLEARSTATISTICS     CFG_CMO_DEF(MID_UDP6, CMOTABID_UDP6,0)
#define OID_UDP6_DEBUG_PACKET        CFG_CMO_DEF(MID_UDP6, CMOTABID_UDP6,1)
#define OID_UDP6_DEBUG_TASKID        CFG_CMO_DEF(MID_UDP6, CMOTABID_UDP6,2)
#define OID_UDP6_DEBUG_SOCKID        CFG_CMO_DEF(MID_UDP6, CMOTABID_UDP6,3)
#define OID_UDP6_SHOWSTATISTICS      CFG_CMO_DEF(MID_UDP6, CMOTABID_UDP6,4)

#define TBL_UDP6_SHOW_COM_VERSION          0x14


#define CMO_UDP6_SHOW_COM_VERSION      \
                  CFG_CMO_DEF(MID_UDP6, TBL_UDP6_SHOW_COM_VERSION, 1)
#define CMO_UDP6_SHOW_COM_TEST_VERSION \
                  CFG_CMO_DEF(MID_UDP6, TBL_UDP6_SHOW_COM_VERSION, 2)

/* Added by Anand - V1R7 Workspace Integration */
#define UDP6_MEM_ZERO(m_pBufPtr, m_ulBufLen)\
                        (VOID)TCPIP_Mem_Set((CHAR *)(m_pBufPtr), 0, (m_ulBufLen))

/* CMD element enum*/
enum enum_UDP6
{
    /* debug ip6 packet */

    UDP6_DBG_PACKET,              /* 1 */
    UDP6_CMDELEMENT,               /* 2 */
    UDP6_CMDELEMENT_IP,
    UDP6_CMDELEMENT_TASKID,
    UDP6_CMDELEMENT_SOCKID,
    UDP6_CMDELEMENT_UDPPKT,
    UDP6_CMDELEMENT_UDPSHOW,
    UDP6_CMDELEMENT_UDPSTAT,
    UDP6_CMDELEMENT_SHOWCOM,
    UDP6_CMDELEMENT_SHOWCOMVER,
    UDP6_CMDELEMENT_SHOWCOMTESTVER,
    UDP6_CMDELEMENT_SHOWCOMVERUDP6,
    UDP6_CMDELEMENT_SHOWCOMTESTVERUDP6

};


VOID IP6_UDP6_SH_ShowStatist(ULONG ulExecID);
extern ULONG  IP6_UDP6_ProDbugFilter(ULONG ulFlag, ULONG ulTaskId,
                                              ULONG ulSockId);
extern ULONG IP6_UDP6_SH_DebugPkt(ULONG ulflag);

#endif


extern struct IIF_IP6_UDP6_INITVtbl      * g_pstUDP6ComInitTable;
extern struct IIF_IP6_UDP6_CFGVtbl      * g_pstUDP6ComCfgTable;
extern struct IIF_IP6_UDP6_FUNVtbl      * g_pstUDP6ComFunTable;

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

