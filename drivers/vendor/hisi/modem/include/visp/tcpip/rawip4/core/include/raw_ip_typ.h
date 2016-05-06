/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              raw_ip_typ.h
*
*  Project Code: VISP1.5
*   Module Name: RawIP
*  Date Created: 2002-8-20
*        Author: Mayun
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2002-8-20   Mayun            Creat the first version.
*  2006-04-27  luyao            根据编程规范，对文件进行规范化整理
*
*******************************************************************************/

#ifndef _RAW_IP6_TYP_H_
#define _RAW_IP6_TYP_H_


#ifdef  __cplusplus
extern "C"{
#endif

/****************************************************************************/
/*                              Macro Defination                            */
/****************************************************************************/
#define RIPSNDQ     8192
#define RIPRCVQ     8192

#define IP6_RIP6_SOCK_SET_PARAM  (g_pfRIP6SocketAPI->pfIP6_Socket_SetParameter)
#define IP6_RIP6_SOCK_GET_PARAM  (g_pfRIP6SocketAPI->pfIP6_Socket_GetParameter)

#define  RIP6_ASYNRECALL  (g_pfRIP6SocketAPI->pfSO6_AsynReCall)
#define  RIP6_SOWAKEUP  (g_pfRIP6SocketAPI->pfSo6WakeUp)
#define  RIP6_ASYNWAKEUP  (g_pfRIP6SocketAPI->pfSO6_AsynWakeUp)
#define  RIP6_SB_APPENDADDR  (g_pfRIP6SocketAPI->pfSB6_AppendAddr)
#define  RIP6_SOCANTSENDMORE  (g_pfRIP6SocketAPI->pfSO6_CantSendMore)
#define  RIP6_SOISCONNECTED  (g_pfRIP6SocketAPI->pfSO6_IsConnected)
#define  RIP6_SOISDISCONNECTED  (g_pfRIP6SocketAPI->pfSO6_IsDisconnected)
#define  RIP6_SO_RESERVE  (g_pfRIP6SocketAPI->pfSO6_Reserve)



#define IP6_RIP6_IN6PCB_SET_PARAM       g_pfRIP6In6PCBCallBack->pfIP6_IN6PCB_SetParameter
#define IP6_RIP6_IN6PCB_GET_PARAM       g_pfRIP6In6PCBCallBack->pfIP6_IN6PCB_GetParameter
   
#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _RAW_IP6_H_ */
 

