/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ping_fun.h
*
*  Project Code: VISP1.5
*   Module Name: ping
*  Date Created: 2002-8-20
*        Author: fu jibin
*   Description: 声明PING6用户的函数
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2002-8-20  fu jibin          Creat the first version.
*  2006-04-27  luyao            根据编程规范，对文件进行规范化整理
*
*******************************************************************************/


/* Defect id BYAD01452 - Modified by Suraj 21st Oct 2003.
#if (VRP_MODULE_IPV6 == VRP_YES)*/

#ifndef _PING_FUNC_H_
#define _PING_FUNC_H_

#ifdef __cplusplus
extern "C" {
#endif

/*回调函数主要用来输出调试信息*/
extern PING_CALLBACK_SET_S   g_stPingCallBackFunction;
/*AM4组件功能虚表*/
extern struct IIF_IPV4_IP_AM4_ComIntFUNVtbl         * g_pstPingAM4ComFunTable;

/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-05   */
/* VRF 模块功能虚表指针 */
extern struct IIF_VRF_ComIntFUNVtbl                 *g_pstPingVrfComFunTable ;
/* End:VISP1.7C03 VRF wangchengyang,2009-02-05   */

extern struct IIF_VRF6_ComIntFUNVtbl                 *g_pstPingVrf6ComFunTable ;

/*Added by w00207740, DTS2013032900271,路由模式下使用ping，指定出接口与下一跳，不指定源IP时，不能发送报文, 2013/6/26 */
extern struct IIF_IP6_ND_COMMONVtbl            *g_pstIpv6NDCommonPingVtbl ;

/* 同步D21代码  x36530  2004-9-11  */
/* Global pointer for the Address Management Component Vtable*/

#define PING_TIMELEFT(ulCurrentTime,ulTimeStart,ulTimeInterval,ullastTime,ulTimeShift,ulTimeLeft)\
{\
    (ulCurrentTime) = PIN_Timer_Read ( );\
    \
    if ( (ulCurrentTime) < (ullastTime) )\
    { \
       (ulTimeInterval) = ( ULONG )( (ulCurrentTime) + \
           ( ( PIN_MAXTIME ) - (ullastTime) ) ); \
       (ullastTime) = (ulCurrentTime); \
    } \
    else \
    { \
       (ulTimeInterval) = (ulCurrentTime) - (ullastTime); \
       (ullastTime) = (ulCurrentTime); \
    } \
    \
    (ulTimeShift)+= (ulTimeInterval); \
    (ulTimeLeft) -= (ulTimeInterval); \
    if ( ( LONG )(ulTimeLeft) <= 0 ) \
    { \
        (ulTimeLeft)=0; \
    } \
}

#define PIN_CHECKFORDF(Ping4_usDF) ((1 == Ping4_usDF) ? PIN_IP_HEADLEN : 0 )

 /* PING模块与IP6相关的组建功能接口  */
extern struct  IIF_IP6_ADDR_ComIntFunVtbl   *g_pstIP6PingV6AddrFunTable;
LONG PING_Ping ( ULONG ulExecID, Ping6Param_S  *pPing6Param);
VOID PING_Pinger ( Ping6Param_S * pstPing6Param, ULONG ulExecID );
LONG PING_PrintPacket ( Ping6Param_S * pstPing6Param, CHAR * pcBuf, LONG lRecvLen,SOCKADDR_IN6_S *  pstFrom, ULONG ulSendSeq, ULONG ulExecID );
LONG PING_Get_HopLim(msghdr * pstRecvMsg);

/*Modified by dengxiong for D00173*/
LONG PING_DoPing(ULONG ulExecID, Ping_Comm_S  *stPingParam);
VOID PIN_Finish ( PingParam_S *, ULONG );

LONG PIN_Ping ( ULONG ulExecID, PingParam_S  *stPingData);
/*Modified by zhongyu206043, 修改返回值为ULONG型，支持ping报文DF标识 for S.PING.1.1, 2012/8/18 */
LONG PIN_Pinger ( PingParam_S *, ULONG );
LONG PIN_PrintPacket ( PingParam_S * , CHAR * , LONG , struct sockaddr_in * ,ULONG ,ULONG ,ULONG);
CHAR * PIN_PrintAddr ( PingParam_S * , ULONG, CHAR* );
USHORT PIN_InCksum ( USHORT * , LONG );
LONG  PIN_Fill ( PingParam_S * , CHAR * ,ULONG);
VOID PIN_PrintIcmph ( ICMP_S *, ULONG );

CHAR * PIN_NToA(ULONG ulAddr,CHAR szStrAddr[LEN_128]);

extern TCPIP_PINGOutput_HOOK_FUNC g_pstPINGOutputHook;
extern TCPIP_PINGSTAT_HOOK_FUNC g_pfPingStatOutputHook;
VOID TCPIP_PINOutput(CHAR *szBuf);
VOID TCPIP_PINOutputEx(CHAR *szBuf,ULONG ulExecID);
ULONG PING_SetTos(UCHAR ucTos);
ULONG PING_GetTos(UCHAR *pucTos);
LONG PIN_CheckAndSetParam( PingParam_S *stPingParam ,PingParam_S *pstPingData);

/* Added by y00176567, at 2011-05-27. 修改原因: 消除VC三级告警 */
extern LONG isxdigit(CHAR);

#ifdef __cplusplus
}
#endif

#endif  /*end of _PING6_FUNC_H_*/

/* Defect id BYAD01452 - Modified by Suraj 21st Oct 2003.
#endif */



