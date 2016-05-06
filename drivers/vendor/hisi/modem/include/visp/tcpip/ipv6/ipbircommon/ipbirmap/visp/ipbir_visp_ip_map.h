#ifndef _IPB_IR_VISP_IP_MAPP_H_
#define _IPB_IR_VISP_IP_MAPP_H_

#ifdef    __cplusplus
extern "C"{
#endif



#include "common/visp/VISP_IR_IP4PUB.h"  /*Common headfile visp provided*/


LONG VRPAdapt_IP_Get_IpDefTTl(VOID);
USHORT VRPAdapt_IP_Get_IpId(VOID);
ULONG VRPAdapt_IP_Get_IF_MainIpAddr(ULONG ulIfIndex);
ULONG VRPAdapt_IP_IF_IsBroadcast(ULONG ulIpAddr, VOID * pstIfNet);
USHORT VRPAdapt_IP_IN_Cksum(VOID * pstMBuf, LONG lLen);
ULONG VRPAdapt_IP_IsInvalidAddr(ULONG ulIpAddr);
ULONG VRPAdapt_IP_Output(MBUF_S * pstMBuf, MBUF_S * pstMOpt, ROUTE_S * pstRo, LONG lFlags, IPMOPTIONS_S * pstIpMo);
ULONG VRPAdapt_IP_RegisterDomain(DOMAIN_S * pstDomain);
VOID VRPAdapt_IP_Set_IncreaseIpId(VOID);
VOID VRPAdapt_IP_StrIpOptions(VOID * pMBuf, VOID * pMOpt);
ULONG VRPAdapt_IP_PP4_RegProtocolSwitch(ULONG ulFlag, PROTOSW_S * pstRegPST);
ULONG VRPAdapt_IP_PP4_Intermediate_Hook_Register(ULONG ulType, ULONG ulPriority,
                                IP_PP4_INTERMEDIATE_HOOK_FUNC pfIpFwHookFunc);



#define IPB_IR_IP_IN_CKSUM(pstMBuf, lLen) VRPAdapt_IP_IN_Cksum(pstMBuf, lLen)

#define IPB_IR_IP_STRIPOPTIONS(pMBuf, pMOpt) \
        VRPAdapt_IP_StrIpOptions(pMBuf, pMOpt)

#define IPB_IR_IP_GET_IPDEFTTL()        VRPAdapt_IP_Get_IpDefTTl()

#define IPB_IR_IP_GET_IPID()            VRPAdapt_IP_Get_IpId()

#define IPB_IR_IP_SET_INCREASEIPID()    VRPAdapt_IP_Set_IncreaseIpId()

#define IPB_IR_IP_OUTPUT(pstMBuf, pstMOpt, pstRo, lFlags, pstIpMo) \
    VRPAdapt_IP_Output(pstMBuf, pstMOpt, pstRo, lFlags, pstIpMo)

#define IPB_IR_IP_IF_ISBROADCAST(ulIpAddr, pstIfNet) \
    VRPAdapt_IP_IF_IsBroadcast(ulIpAddr, pstIfNet)

#define IPB_IR_IP_GET_IF_MAINIPADDR(ulIfIndex)   VRPAdapt_IP_Get_IF_MainIpAddr(ulIfIndex)

#define IPB_IR_IP_REGISTER_DOMAIN(pstDomain)  \
            VRPAdapt_IP_RegisterDomain(pstDomain)

#define IPB_IR_IP_ISINVALIDADDR(ulIpAddr)    VRPAdapt_IP_IsInvalidAddr(ulIpAddr)

#define IPB_IR_IP_PP4_RegProtocolSwitch(ulFlag,pstRegPST)  VRPAdapt_IP_PP4_RegProtocolSwitch(ulFlag,pstRegPST)

#define IPB_IR_IP_PP4_Intermediate_Hook_Register(ulType,ulPriority,pfIpFwHookFunc) \
    VRPAdapt_IP_PP4_Intermediate_Hook_Register(ulType,ulPriority,pfIpFwHookFunc)


#define IPB_IR_QUE_GETIPINPUTQUEID()  \
        VRPAdapt_GetIPInputQueID()


/* James: Modified for V1R7 */
#define IPB_IR_QUE_ENQUEUE(pstMbuf)  \
         Que_EnQueue(pstMbuf)


#ifdef __cplusplus
}
#endif        /* end of __cplusplus */


#endif  /* end of _IPB_IR_VISP_IP_MAPP_H_ */


