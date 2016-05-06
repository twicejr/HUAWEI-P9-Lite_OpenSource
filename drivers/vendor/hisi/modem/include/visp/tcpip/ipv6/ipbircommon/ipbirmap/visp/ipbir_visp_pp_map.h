/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              ipbir_visp_pp_map.h
*
*    Project Code:  IPOS IR V1R2
*    Version     :  Initial Draft
*    Module Name :  IPB IR
*    Create Date :  2006/08/23
*    Author      :  IPv6 Team
*    Description :  To define VISP specific PPMNG macros
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-08-23  IPv6 Team   Created for defining VISP related PPMNG macros
************************************************************************/

#ifndef _IPB_IR_VISP_PP_MAPP_H_
#define _IPB_IR_VISP_PP_MAPP_H_



#include "common/visp/VISP_IR_PPmng.h"
#include "common/ipos/ipv6/ip6_pub.h"

LONG VRPAdapt_IP6_PP_IF_Output(VOID *pstMBuf);
ULONG VRPAdapt_IP6_PP_Output (VOID *pstMBuf, VOID *pstOpt, ULONG ulZoneId, \
                                LONG lFlags, VOID *pstMo);
USHORT VRPAdapt_IP6_PP_Cksum (VOID *pstMBuf, UCHAR ucNext, LONG lOff, LONG lLen);
ULONG VRPAdapt_IP6_PP_PM_Protocol_Register (LONG lPID, VOID* pstProtocolInfo);
LONG VRPAdapt_IP6_PP_GetNextHdr(VOID *pstMBuf, ULONG ulOff, \
                                ULONG ulProto, ULONG *pulNxtProto);
ULONG VRPAdapt_IP6_PP_Get_PSTField (SHORT sType, UCHAR ucProtocol, \
                                IP6_PP_PROTOCOLFIELD ePfield, VOID *pvRetVal);
ULONG VRPAdapt_IP6_PP_UnicastRouting_GetStatus (USHORT usVrfindex);
LONG VRPAdapt_IP6_PP_GetLastHdr(VOID *pstMBuf, ULONG ulOff, ULONG ulProto, ULONG *pulNxtProto);
ULONG VRPAdapt_IP6_PP_Register_IPv6_Notify(IP6_PP_Register_Notify fpFunPtr);
ULONG VRPAdapt_IP6_PP_Function_GetStatus (VOID);
ULONG VRPAdapt_IP6_PP_RegisterCliChangeNotify ( ULONG (* pfIP6_PP_NotifyCliChange) (ULONG ulCliState) );
ULONG VRPAdapt_IP6_PP_IsUpperLayerRegistered (VOID);
ULONG VRPAdapt_IP6_PP_FreeInterfaceStats (VOID *pstIntfIP6Stat);
VOID * VRPAdapt_IP6_PP_AllocateInterfaceStats (VOID);
ULONG VRPAdapt_IP6_PP_ExtHdrLen (VOID *pstPktOpts);
LONG VRPAdapt_IP6_PP_CtlOutput ( LONG lOper, UINTPTR ulSocket, LONG lLevel, LONG lOptName, VOID **ppMBuf);
VOID * VRPAdapt_IP6_PP_CopyPktOpts (VOID *pstOpts);
VOID VRPAdapt_IP6_PP_SaveControl (UINTPTR ulIn6Pcb,VOID *pstIp6,VOID **ppstMBuf,VOID *pstOpt, VOID **ppstPrevOpt);
UCHAR* VRPAdapt_IP6_PP_GetPrevHdr (VOID *pstMBuf, ULONG *pulOff, ULONG *pulProto);
LONG VRPAdapt_IP6_PP_SetPktOptions (VOID *pstMBuf,VOID *pstOpt,  ULONG ulPriv, ULONG ulNeedcopy);
VOID VRPAdapt_IP6_PP_ClearPktOpts (VOID*pOpt, LONG lOptName);
VOID VRPAdapt_IP6_PP_Incr_Statistics (ULONG uletmpIp6Stats);


#define IPB_IR_IP6_PP_IF_OUTPUT(pstMbuf)\
    VRPAdapt_IP6_PP_IF_Output(pstMbuf)

#define IPB_IR_IP6_PP_OUTPUT(pstMBuf, pstOpt, ulZoneId, lFlags, pstMo)\
    VRPAdapt_IP6_PP_Output(pstMBuf, pstOpt, ulZoneId, lFlags, pstMo)

#define IPB_IR_IP6_PP_CKSUM(pstMBuf, ucNext, lOff, lLen)\
    VRPAdapt_IP6_PP_Cksum(pstMBuf, ucNext, lOff, lLen)

#define IPB_IR_IP6_PP_PM_PROTOCOL_REGISTER(lPID, pstProtocolInfo)\
   VRPAdapt_IP6_PP_PM_Protocol_Register(lPID, pstProtocolInfo)

#define IPB_IR_IP6_PP_GETNEXTHDR(pstMbuf, ulOff , ulProto, pulNxtProto)\
   VRPAdapt_IP6_PP_GetNextHdr(pstMbuf, ulOff, ulProto, pulNxtProto)

#define IPB_IR_IP6_PP_GET_PSTFIELD(sType, ucProtocol, ePfield , pvRetVal)\
   VRPAdapt_IP6_PP_Get_PSTField(sType, ucProtocol, ePfield,pvRetVal)

#define IPB_IR_IP6_PP_UNICASTROUTING_GETSTATUS(usVrfIndex)\
   VRPAdapt_IP6_PP_UnicastRouting_GetStatus(usVrfIndex)

#define IPB_IR_IP6_PP_GETLASTHDR(pstMBuf, ulOff, ulProto, pulNxtProto)\
   VRPAdapt_IP6_PP_GetLastHdr(pstMBuf, ulOff, ulProto, pulNxtProto)

#define IPB_IR_IP6_PP_REGISTERIPV6NOTIFY(pfunc) \
   VRPAdapt_IP6_PP_Register_IPv6_Notify(pfunc)

#define IPB_IR_IP6_PP_FUNCTION_GETSTATUS()\
   VRPAdapt_IP6_PP_Function_GetStatus()

#define IPB_IR_IP6_PP_REGISTERCLICHANGENOTIFY(pfunc)\
   VRPAdapt_IP6_PP_RegisterCliChangeNotify(pfunc)

#define IPB_IR_IP6_PP_ISUPPERLAYERREGISTERED()\
   VRPAdapt_IP6_PP_IsUpperLayerRegistered()


/* Reason : Compilation change   Mod:Bharath */
#define IPB_IR_IP6_PP_FREEINTERFACESTATS(pstIntfIP6Stat)\
   VRPAdapt_IP6_PP_FreeInterfaceStats(pstIntfIP6Stat)

#define IPB_IR_IP6_PP_ALLOCATEINTERFACESTATS()\
   VRPAdapt_IP6_PP_AllocateInterfaceStats()

#define IPB_IR_IP6_PP_EXTHDRLEN(pstPktOpts)  \
   VRPAdapt_IP6_PP_ExtHdrLen((VOID *)pstPktOpts)

#define IPB_IR_IP6_PP_CTLOUTPUT(lOper, ulSocket, lLevel, lOptName, ppMBuf)  \
   VRPAdapt_IP6_PP_CtlOutput(lOper, ulSocket, lLevel, lOptName, (VOID **)ppMBuf)

#define IPB_IR_IP6_PP_COPYPKTOPTS(pstPktOpts)  \
   VRPAdapt_IP6_PP_CopyPktOpts((VOID *)pstPktOpts)

#define IPB_IR_IP6_PP_SAVECONTROL(ulIn6Pcb, pstIp6, ppstMBuf, pstOpt, ppstPrevOpt)   \
   VRPAdapt_IP6_PP_SaveControl(ulIn6Pcb, (VOID *)pstIp6, (VOID **)ppstMBuf, (VOID *)pstOpt, (VOID **)ppstPrevOpt)

#define IPB_IR_IP6_PP_GETPREVHDR(pstMBuf, pulOff, pulProto)  \
   VRPAdapt_IP6_PP_GetPrevHdr((VOID *)pstMBuf, pulOff, pulProto)

#define IPB_IR_IP6_PP_SETPKTOPTIONS(pstMBuf,pstPktOpt, ulPriv, ulNeedcopy)   \
   VRPAdapt_IP6_PP_SetPktOptions((VOID *)pstMBuf,(VOID *)pstPktOpt, ulPriv, ulNeedcopy)

#define IPB_IR_IP6_PP_CLEARPKTOPTS(pPktOpt, lOptName)   \
   VRPAdapt_IP6_PP_ClearPktOpts((VOID *)pPktOpt, lOptName)

#define IPB_IR_IP6_PP_INCR_STATISTICS(etmpIp6Stats)   \
   VRPAdapt_IP6_PP_Incr_Statistics(etmpIp6Stats)

#define IPB_IR_IP6_MOPTIONS_S \
       IP6_MOPTIONS_S


#endif  /* end of _IPB_IR_VISP_PP_MAPP_H_ */










