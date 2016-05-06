/************************************************************************
 *
 *    Copyright 2003, Huawei Technologies Co. Ltd  India Institute  
 *                     ALL RIGHTS RESERVED                           
 *                                                 
 *----------------------------------------------------------------------*
 *
 *                             natpt_sh_cmo.h
 *
 *  Project Code:       VRPv5 
 *  Create Date:        2003-7-18
 *  Author:             Soumya   (VRPv5 IPv6 Team) 
 *  Document:
 *  Function Description: This file has all the CMo related definations.
 *  
 *----------------------------------------------------------------------*
 *  Modification History 
 *  DATE        NAME             DESCRIPTION
 *  
 *  2003-10-26 Soumya            For Defect BYAD03058 
 * 2003-11-13   Archana P V     for Defect BYAD03928 
 *  2003-12-2  Usha             For Defect BYAD04881 
 *  2003-12-24 Usha             For defect BYAD05918
 *  2003-01-12 Archana P V      For defect BYAD06698
 ************************************************************************/



#ifndef _NATPT_SH_CMO_H
#define _NATPT_SH_CMO_H

#ifdef	__cplusplus
extern	"C"{
#endif

/*----------------------------------------------*
 * Global Variables    
 *----------------------------------------------*/

#define TBL_NATPT_ENABLE                0x10
#define TBL_NATPT_SETSTATICV6V4BOUND    0x11
#define TBL_NATPT_SETSTATICV4V6BOUND    0x12
#define TBL_NATPT_AGEOUT                0x13
#define TBL_NATPT_MAXSESSIONS           0x14
#define TBL_NATPT_CLEAR                 0x15
#define TBL_NATPT_DEBUG                 0x16
#define TBL_NATPT_CONFADDRGROUP         0x17
#define TBL_NATPT_DYNV6BOUND            0x18
#define TBL_NATPT_DYNV4BOUND            0x19
#define TBL_NATPT_PREFIX                0x20
#define TBL_NATPT_DISPLAY               0x21

/* for defect BYAD04881 */
#define TBL_NATPT_TRAFCLASS             0x22 

/* for defect BYAD11433 */
#define TBL_NATPT_ALLOWPRVADDR          0x23

/* Elements of NATPT_Enable Command */
#define CMO_NATPT_IFINDEX     CFG_CMO_DEF(MID_NATPT,TBL_NATPT_ENABLE,1)
#define CMO_NATPT_ENABLENO    CFG_CMO_DEF(MID_NATPT, TBL_NATPT_ENABLE,2)

/* Elements of the NATPT_Cmd_SetStaticV6V4bound*/
#define CMO_NATPT_STIPV6ADD			CFG_CMO_DEF(MID_NATPT, TBL_NATPT_SETSTATICV6V4BOUND,   1)
#define CMO_NATPT_STIPV4ADD			CFG_CMO_DEF(MID_NATPT, TBL_NATPT_SETSTATICV6V4BOUND,   2)
#define CMO_NATPT_STATICV6V4NO      CFG_CMO_DEF(MID_NATPT, TBL_NATPT_SETSTATICV6V4BOUND,   3)

/* Elements of the NATPT_Cmd_SetStaticV4V6bound*/
#define CMO_NATPT_STV4IPV4ADD  CFG_CMO_DEF(MID_NATPT, TBL_NATPT_SETSTATICV4V6BOUND,   1)
#define CMO_NATPT_STV4IPV6ADD  CFG_CMO_DEF(MID_NATPT, TBL_NATPT_SETSTATICV4V6BOUND,   2)
#define CMO_NATPT_V6SERVER	   CFG_CMO_DEF(MID_NATPT, TBL_NATPT_SETSTATICV4V6BOUND,   3)
#define CMO_NATPT_TCP          CFG_CMO_DEF(MID_NATPT, TBL_NATPT_SETSTATICV4V6BOUND,   4)
#define CMO_NATPT_UDP          CFG_CMO_DEF(MID_NATPT, TBL_NATPT_SETSTATICV4V6BOUND,   5)
#define CMO_NATPT_IPV4PORT     CFG_CMO_DEF(MID_NATPT, TBL_NATPT_SETSTATICV4V6BOUND,   6)
#define CMO_NATPT_IPV6PORT     CFG_CMO_DEF(MID_NATPT, TBL_NATPT_SETSTATICV4V6BOUND,   7)
#define CMO_NATPT_STV4V6NO	   CFG_CMO_DEF(MID_NATPT, TBL_NATPT_SETSTATICV4V6BOUND,   8)


/* Elements of the NATPT_Cmd_AgeOut */
#define CMO_NATPT_UDPTIME                   CFG_CMO_DEF(MID_NATPT, TBL_NATPT_AGEOUT,   1)
#define CMO_NATPT_DNSTIME                   CFG_CMO_DEF(MID_NATPT, TBL_NATPT_AGEOUT, 2)
#define CMO_NATPT_TCPTIME                   CFG_CMO_DEF(MID_NATPT, TBL_NATPT_AGEOUT, 3)
#define CMO_NATPT_FINRSTTIME                CFG_CMO_DEF(MID_NATPT, TBL_NATPT_AGEOUT, 4)
#define CMO_NATPT_ICMPTIME                  CFG_CMO_DEF(MID_NATPT, TBL_NATPT_AGEOUT, 5)
#define CMO_NATPT_SYNTIME                   CFG_CMO_DEF(MID_NATPT, TBL_NATPT_AGEOUT, 6)
#define CMO_NATPT_FRAGTIME                  CFG_CMO_DEF(MID_NATPT, TBL_NATPT_AGEOUT, 7)
#define CMO_NATPT_TIMEVALUE                 CFG_CMO_DEF(MID_NATPT, TBL_NATPT_AGEOUT, 8)
#define CMO_NATPT_TCPTIMEVALUE              CFG_CMO_DEF(MID_NATPT, TBL_NATPT_AGEOUT, 9)/*Added for defect BYAD03058*/
#define CMO_NATPT_DEFAULTTIME               CFG_CMO_DEF(MID_NATPT, TBL_NATPT_AGEOUT, 10)

/* Elements of the NATPT_Cmd_SetMaxSessions */
#define CMO_NATPT_MAXSESSION                CFG_CMO_DEF(MID_NATPT, TBL_NATPT_MAXSESSIONS, 1)
#define CMO_NATPT_MAXSESSNO			        CFG_CMO_DEF(MID_NATPT, TBL_NATPT_MAXSESSIONS, 2)

/* Elements of the NATPT_Cmd_Debug */
#define CMO_NATPT_DEBUGEVENTS       CFG_CMO_DEF(MID_NATPT, TBL_NATPT_DEBUG, 1)
#define CMO_NATPT_DEBUGPACKET       CFG_CMO_DEF(MID_NATPT, TBL_NATPT_DEBUG, 2)
#define CMO_NATPT_DEBUGALG          CFG_CMO_DEF(MID_NATPT, TBL_NATPT_DEBUG, 3)
#define CMO_NATPT_DEBUGNO           CFG_CMO_DEF(MID_NATPT, TBL_NATPT_DEBUG, 4)
#define CMO_NATPT_DEBUGIFNAME		CFG_CMO_DEF(MID_NATPT, TBL_NATPT_DEBUG, 5)
#define CMO_NATPT_DEBUGIFTYPE		CFG_CMO_DEF(MID_NATPT, TBL_NATPT_DEBUG, 6)
#define CMO_NATPT_DEBUGIFNUMBER		CFG_CMO_DEF(MID_NATPT, TBL_NATPT_DEBUG, 7)
 /* for defect BYAD05918 */
#define CMO_NATPT_DEBUGALL          CFG_CMO_DEF(MID_NATPT, TBL_NATPT_DEBUG, 8)

/* Elements of the NATPT_Cmd_ConfIpv4AddrGrp */
#define CMO_NATPT_GROUPNUMBER       CFG_CMO_DEF(MID_NATPT, TBL_NATPT_CONFADDRGROUP, 1)
#define CMO_NATPT_STARTADDR         CFG_CMO_DEF(MID_NATPT, TBL_NATPT_CONFADDRGROUP, 2)
#define CMO_NATPT_ENDADDR           CFG_CMO_DEF(MID_NATPT, TBL_NATPT_CONFADDRGROUP, 3)
#define CMO_NATPT_ADDRGRPNO         CFG_CMO_DEF(MID_NATPT, TBL_NATPT_CONFADDRGROUP, 4)

/* Elements of the NATPT_Cmd_DynV6Bound */
#define CMO_NATPT_DYNV6ACLNO            CFG_CMO_DEF(MID_NATPT, TBL_NATPT_DYNV6BOUND, 1)
#define CMO_NATPT_DYNV6ACLNAME          CFG_CMO_DEF(MID_NATPT, TBL_NATPT_DYNV6BOUND, 2)
#define CMO_NATPT_DYNV6PREFIX           CFG_CMO_DEF(MID_NATPT, TBL_NATPT_DYNV6BOUND, 3)
#define CMO_NATPT_DYNADDRGRPNO          CFG_CMO_DEF(MID_NATPT, TBL_NATPT_DYNV6BOUND, 4)
#define CMO_NATPT_DYNPAT                CFG_CMO_DEF(MID_NATPT, TBL_NATPT_DYNV6BOUND, 5)
#define CMO_NATPT_DYNIFNAME             CFG_CMO_DEF(MID_NATPT, TBL_NATPT_DYNV6BOUND, 6)
#define CMO_NATPT_V6BIFTYPE			CFG_CMO_DEF(MID_NATPT, TBL_NATPT_DYNV6BOUND, 7)
#define CMO_NATPT_V6BIFNUM       CFG_CMO_DEF(MID_NATPT, TBL_NATPT_DYNV6BOUND, 8)
#define CMO_NATPT_DYNV6BOUNDNO          CFG_CMO_DEF(MID_NATPT, TBL_NATPT_DYNV6BOUND, 9)

/* Elements of the NATPT_Cmd_DynV4Bound */
#define CMO_NATPT_ACLNO             CFG_CMO_DEF(MID_NATPT, TBL_NATPT_DYNV4BOUND, 1)
#define CMO_NATPT_ACLNAME           CFG_CMO_DEF(MID_NATPT, TBL_NATPT_DYNV4BOUND, 2)
#define CMO_NATPT_DYNV4PREFIX       CFG_CMO_DEF(MID_NATPT, TBL_NATPT_DYNV4BOUND, 3)
#define CMO_NATPT_DYNV4BOUNDNO      CFG_CMO_DEF(MID_NATPT, TBL_NATPT_DYNV4BOUND, 4)

/* Elements of the NATPT_Cmd_Prefix */
#define CMO_NATPT_PREFIX		CFG_CMO_DEF(MID_NATPT, TBL_NATPT_PREFIX, 1)
#define CMO_NATPT_PFIFNAME		CFG_CMO_DEF(MID_NATPT, TBL_NATPT_PREFIX, 2)
#define CMO_NATPT_PFXIFTYPE		CFG_CMO_DEF(MID_NATPT, TBL_NATPT_PREFIX, 3)
#define CMO_NATPT_PFXIFNUM   	CFG_CMO_DEF(MID_NATPT, TBL_NATPT_PREFIX, 4)
#define CMO_NATPT_NXTHOP		CFG_CMO_DEF(MID_NATPT, TBL_NATPT_PREFIX, 5)
#define CMO_NATPT_PREFIXNO		CFG_CMO_DEF(MID_NATPT, TBL_NATPT_PREFIX, 6)

/* Elements of the NATPT_Cmd_Display */
#define CMO_NATPT_DISPLAY       CFG_CMO_DEF(MID_NATPT, TBL_NATPT_DISPLAY, 1)
#define CMO_NATPT_SLOTNO        CFG_CMO_DEF(MID_NATPT, TBL_NATPT_DISPLAY, 2)
/*Defect From DTS : BYAD06698
  Modified By     : Archana P V 
  Main Logic      : Filtering for sessions based on protocol*/
#define CMO_NATPT_DISSESSPRO    CFG_CMO_DEF(MID_NATPT, TBL_NATPT_DISPLAY, 3) 

/* Elements of the NATPT_Cmd_Clear */
#define CMO_NATPT_CLEARNATPT	CFG_CMO_DEF(MID_NATPT, TBL_NATPT_CLEAR, 1)
/*Added for Defect BYAD03928*/
#define CMO_NATPT_CLEARSTAT     CFG_CMO_DEF(MID_NATPT, TBL_NATPT_CLEAR, 2)
#define CMO_NATPT_CLEARSLOTNO   CFG_CMO_DEF(MID_NATPT, TBL_NATPT_CLEAR, 3)


/* Elements of NATPT_Cmd_TrafficClass */
/* for defect BYAD04881 */
#define CMO_NATPT_TRAFFICCLASS  CFG_CMO_DEF(MID_NATPT, TBL_NATPT_TRAFCLASS, 1)
#define CMO_NATPT_TOS           CFG_CMO_DEF(MID_NATPT, TBL_NATPT_TRAFCLASS, 2)
#define CMO_NATPT_TRAFCLASSNO   CFG_CMO_DEF(MID_NATPT, TBL_NATPT_TRAFCLASS, 3)   
/* End of defect BYAD04881 */

/* for defect BYAD11433 */
#define CMO_NATPT_ALLOWPRVADDRNO  CFG_CMO_DEF(MID_NATPT, TBL_NATPT_ALLOWPRVADDR, 1)
/* End of defect BYAD11433 */

#ifdef	__cplusplus
}
#endif

#endif

