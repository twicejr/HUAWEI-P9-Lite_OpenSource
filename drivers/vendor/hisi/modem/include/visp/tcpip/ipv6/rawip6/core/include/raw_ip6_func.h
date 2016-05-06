/****************************************************************************/
/*                                                                          */
/*                          raw_ip6_func.h                                  */
/*                                                                          */
/*  Project Code    : VRP3.0                                                */
/*  Author          : Mayun                                                 */
/*  Version         : Initial Draft                                         */
/*  Create Date     : 2002-8-20                                             */
/*  Description     : 本文件是rawip6的数据结构描述                          */
/*  Others          :                                                       */
/*--------------------------------------------------------------------------*/
/*  Function List   :                                                       */
/*  Name                Function                                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.     */
/*                      ALL RIGHTS RESERVED                                 */
/*                                                                          */
/****************************************************************************/
#ifndef _RAW_IP6_FUNC_H_
#define _RAW_IP6_FUNC_H_


#ifdef  __cplusplus
extern "C"{
#endif

 VOID IP6_RIP6_Init(VOID);
 ULONG IP6_RIP6_Input (MBUF_S **ppstMBuf, ULONG *pulOff, ULONG ulProto);
 LONG IP6_RIP6_Output(MBUF_S *pstMBuf, UINTPTR ulSock,
                            SOCKADDR_IN6_S *pstDstAddr,MBUF_S *pstMCtl);

 LONG IP6_RIP6_CtlOutput(LONG lOper, UINTPTR  ulSock,LONG lLevel,
                     LONG lOptName, MBUF_S **ppMBuf);
 LONG IP6_RIP6_Usrreq(UINTPTR  ulSock, LONG lReq,VOID *pstMBuf,
                 VOID *pstMName, VOID *pstMCtl);

VOID IP6_RIP6_Reg_SockAPI (SOSB6_CALLBACUP_SET_S *pfSocketTL6CallBack);
VOID IP6_RIP6_Reg_IN6PCBAPI(
         IN6PCB_CALLBACUP_SET_S *pfIn6PCBTL6CallBack);


#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _RAW_IP6_H_ */

