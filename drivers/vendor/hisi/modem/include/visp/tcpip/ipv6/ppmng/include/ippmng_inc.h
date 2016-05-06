/**********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              ippmng_inc.h
*    Project Code:  VRP5.0
*    Module Name:  IP6 PP
*    Create Date:  2003/06/23
*    Author:          Mahaveera Jain
*    Description:   To define PP component interfaces
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2003-06-23  Mahaveer Jain    Create
*******************************************************************************/
#ifndef _IP6_IPPMNG_INC_H
#define _IP6_IPPMNG_INC_H

#ifdef __cplusplus
extern "C"{
#endif

/* Please follow the below sequence before including ippmng_inc.h */
#ifndef _BASETYPE_H_
#error "Please include vos/vospubh/basetype.h"
#endif

#ifndef _MBUF_H_
#error "Please include vos/vospubh/mbuf.h"
#endif

#ifndef _INCLUDE_COMPBASE_H
#error "Please include vos/vospubh/compbase.h"
#endif

#ifndef _PAF_H
#error "Please include vos/vospubh/paf.h"
#endif
#include "tcpip/ifnet/include/ifnet_api.h"

#ifndef _IF_IIFNET_INC_H_
#error "Please include tcpip/ifnet/include/iifnet_inc.h"
#endif

#ifndef _IP6_PUB_H_
#error "Please include ipv6/ppmng/core/include/ppmng_pub.h"
#endif

#ifndef _SOCK6_PUB_H
#error "Please include socket/pubinc/sock6_pub.h"
#endif

#ifndef _IP6_IPPMNG_H
#error "Please include ipv6/ppmng/core/include/ippmng.h"
#endif

#ifndef _IP6_PPMNG_H
#error "Please include ipv6/ppmng/core/include/ppmng.h"
#endif

DECLARE_INTERFACE (IIF_IP6_PP_ComIntCFG)
{
    IUNKNOWN_METHODS
    /*Component interface*/
    /* Component initialisation routine */
    METHOD_(ULONG, pfIP6_PP_Init_Com) (COM_ID_INFO_S *pstComInfo, ULONG ulComLen);
    METHOD_(ULONG, pfIP6_PP_Activate_Com) ();
    /* set module info */
    METHOD_(ULONG, pfIP6_PP_SetModuleInfo)(IP6_PP_MOD_INFO_S *pstMInfo);
    /* Callback routine sets */
    METHOD_(ULONG,  pfIP6_PP_RegisterAll)(IP6_PP_SH_CALLBACUP_SET_S *pstPPShellCallback);

    METHOD_(ULONG, pfIP6_PP_MIB_GetGlobalStatistics) (IP6STAT_S *pstIpStat);
    METHOD_(ULONG, pfIP6_PP_MIB_SetGlobalStatistics) (IP6_PP_MIB_OBJECTS etmpMIBObjects, ULONG ulData);
    METHOD_(ULONG, pfIP6_PP_MIB_Set_Statistics) (ULONG ulIpv6IfIndex, ULONG ulenumMib, ULONG ulIpv6IfStats);
    METHOD_(ULONG, pfIP6_PP_MIB_Get_Statistics) (ULONG ulIpv6IfIndex, IP6STAT_S *pstIp6Stat);
    METHOD_(ULONG, pfIP6_PP_MIB_Reset_Statistics) (ULONG ulIpv6IfIndex);

    /* Stat related routines */
    METHOD_(ULONG, pfIP6_PP_SetStatistics) ();
    METHOD_(ULONG, pfIP6_PP_GetStatistics) (IP6_ICMP6_STATS_S *pstIp6Icmp6Stats);
    METHOD_(ULONG, pfIP6_PP_SetRedirect) (ULONG ulRedirectFlag);
    /*modified by zhangyaping for IP6_FMEF*/
    METHOD_(VOID, pfIP6_PP_SetDebugFlag) (ULONG ulDebugFlag , ULONG ulErrpktDebugFlag);
    METHOD_(VOID, pfIP6_PP_Set_LocalFragOnMainboard) (ULONG ulLocalFragOnMainboardFlag);
    METHOD_(ULONG, pfIP6_PP_PktTypeStat_Register) (TCPIP_PP6_PKTTYPE_STAT_KEY_S  *pKey);
    METHOD_(ULONG, pfIP6_PP_PktTypeStat_UnRegister) (TCPIP_PP6_PKTTYPE_STAT_KEY_S  *pKey);
    METHOD_(ULONG, pfIP6_PP_GetPP6PktTypeStat) (TCPIP_PP6_PKTTYPE_STAT_KEY_S  *pKey, 
                                          TCPIP_PP6_PKTTYPE_STAT_S *pstFlowStat);
    METHOD_(ULONG, pfIP6_PP_ClrPP6PktTypeStat) (TCPIP_PP6_PKTTYPE_STAT_KEY_S  *pKey);

};

DECLARE_INTERFACE (IIF_IP6_PP_ComIntFun)
{
    IUNKNOWN_METHODS
    /* IO routines */
    /*w39533 sync D25 2004-12-03*/
    /* Begin : Defect ID: BYAD11865,     Modifier:Rajesh,   Date:2004/11/16
      Reason   : Component issues*/
    METHOD_(MBUF_S *,pfIP6_PP_CheckValidPkt) (MBUF_S *pstMBuf);
    METHOD_(VOID,  pfIP6_PP_Input)(MBUF_S * pstMBuf);
    METHOD_(ULONG,  pfIP6_PP_Output)(MBUF_S *pstMBuf, IP6_PKTOPTS_S *pstOpt, ULONG ulZoneId,
                                    LONG lFlags, IP6_MOPTIONS_S *pstMo);
    METHOD_(ULONG,  pfIP6_PP_IF_Output)(MBUF_S * pstMBuf);

    METHOD_(LONG,  pfIP6_PP_CtlOutput)(LONG lOper, UINTPTR ulSocket, LONG lLevel, LONG lOptName, MBUF_S **ppMBuf);
    METHOD_(LONG, pfIP6_PP_SetPktOptions) (UINTPTR pSocket, MBUF_S *pMBuf, IP6_PKTOPTS_S *pOpt, ULONG priv, ULONG needcopy);
    METHOD_(VOID, pfIP6_PP_SaveControl) (UINTPTR ulIn6Pcb, IP6_S *pstIp6, MBUF_S **ppstMBuf,
                           IP6_RECVPKTOPTS_S *pstOpt, IP6_RECVPKTOPTS_S **ppstPrevOpt);
    METHOD_(VOID, pfIP6_PP_ClearPktOpts) (IP6_PKTOPTS_S *pOpt, LONG lOptName);
    METHOD_(VOID, pfIP6_PP_FreePcbOpts) (IP6_PKTOPTS_S *pOpt);
    METHOD_(VOID, pfIP6_PP_FreeMOptions) (IP6_MOPTIONS_S *pstIpMo);
    METHOD_(IP6_PKTOPTS_S *, pfIP6_PP_CopyPktOpts) (IP6_PKTOPTS_S *pstOpts);
    METHOD_(ULONG, pfIP6_PP_ExtHdrLen) (IP6_PKTOPTS_S *pstPktOpts);

    /* Protocol Management routines */
    /* Protocol register routines */
    METHOD_(ULONG, pfIP6_PP_PM_Protocol_Register) (LONG lPID, IP6_PP_PROTOSW_S *pstProtocolInfo);
    METHOD_(ULONG,  pfIP6_PP_PM_RegisterHook)(ULONG ulType, ULONG ulpriority, IP6_PP_Register pfIpFwHookFunc);

    METHOD_(LONG, pfIP6_PP_GetLastHdr)(MBUF_S *pstMBuf, ULONG ulOff, ULONG ulProto, ULONG *pulNxtProto);
    METHOD_(LONG, pfIP6_PP_GetNextHdr) (MBUF_S *pstMBuf, ULONG ulOff, ULONG ulProto, ULONG *pulNxtProto);
    METHOD_(UCHAR *, pfIP6_PP_GetPrevHdr) (MBUF_S *pstMBuf, ULONG *pulOff, ULONG *pulProto);

    METHOD_(VOID, pfIP6_PP_Incr_Statistics) (ULONG uletmpIp6Stats);

    METHOD_(ULONG, pfIP6_PP_PM_Get_PST) (ULONG ulProtocolNumber, IP6_PP_PROTOSW_S **pstProtocolInfo);
    METHOD_(ULONG, pfIP6_PP_Get_PSTField) (SHORT sType, UCHAR ucProtocol,
                                            IP6_PP_PROTOCOLFIELD ePfield, VOID *pvRetVal);

    METHOD_(VOID, pfIP6_PP_SOSB6_Socket_RegisterCallBack)(SOSB6_CALLBACUP_SET_S *pstSOSB6CallBack);
    METHOD_(VOID, pfIP6_PP_IN6PCB_Socket_RegisterCallBack)(IN6PCB_CALLBACUP_SET_S *pstIN6PCBCallBack);

    /* Checksum routine */
    METHOD_(USHORT, pfIP6_PP_Cksum) (MBUF_S * m, UCHAR nxt, LONG off, LONG len);
    METHOD_(ULONG,   pfIP6_PP_Function_GetStatus)();
    METHOD_(ULONG, pfIP6_PP_Register_IPv6_Notify)(IP6_PP_Register_Notify fpFunPtr);
    METHOD_(ULONG, pfIP6_PP_UnicastRouting_GetStatus) ();
 /*w39533 2004-11-08 sync D24*/
/* Modified by Rajesh for Product support Defect id BYAD11615 */
    METHOD_(VOID, pfIP6_PP_SetProduct)(IP6_PRODUCT  eProduct , ULONG ulPValue);
    METHOD_(ULONG,pfIP6_PP_GetProduct)(IP6_PRODUCT  eProduct);
    /* Begin : Defect ID: BYAD12096,     Modifier:Rajesh,   Date:2004/10/15
        Reason   : To provide generic function pointer registration*/
    METHOD_(VOID,pfIP6_PP_SetProductFuncPoint)(IP6_PRODUCT  eProduct, void *);
    METHOD_(VOID*,pfIP6_PP_GetProductFuncPoint)(IP6_PRODUCT  eProduct);
    /* Begin : Defect ID: BYAD11918,     Modifier:Rajesh,   Date:2004/9/30
    Reason   : To resolve component issues*/
    METHOD_(ULONG, pfIP6_PP_RegisterCliChangeNotify)(ULONG (* pfIP6_PP_NotifyCliChange)(ULONG ulCliState));
};

DECLARE_INTERFACE (IIF_IP6_PP_ComIntSSA)
{
    IUNKNOWN_METHODS
    METHOD_ (ULONG, pfIP6_PP_TimerProcess)(IP6_PP_Timer_MSG_S *pstMsg);
};

typedef struct tagPP_INT_OBJ_S
{
    IIF_IP6_PP_ComIntCFG   *pComIntCFG;
    IIF_IP6_PP_ComIntFun   *pComIntFUN;
    IIF_IP6_PP_ComIntSSA   *pComIntSSA;
}PP_INT_OBJ_S;

#ifdef __cplusplus
}
#endif

#endif

