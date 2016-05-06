/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pppmux_muxcp.h
*
*  Project Code: VISPV100R005
*   Module Name: PPPMUX
*  Date Created: 2006-5-11
*        Author: ZhouTong(43740)
*   Description: PPPMUXCP函数声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-5-11  ZhouTong(43740)   Create
*
*******************************************************************************/

#ifndef _PPPMUX_MUXCP_H_
#define _PPPMUX_MUXCP_H_

#ifdef  __cplusplus
extern "C"{
#endif

/* pppmux_muxcp.c*/
VOID PPP_MUXCP_ReceiveEventFromCore ( VOID *pstMuxcpInfo, ULONG ulCmd, char *pPara );
VOID PPP_MUXCP_Init (PPPINFO_S* pstPppInfo);
VOID PPP_MUXCP_ReceivePacket (VOID *pstMuxcpInfo, UCHAR *pucHead, UCHAR *pucPacket, ULONG ulLen);

VOID   PPP_MUXCP_resetci (PPPFSM_S *pstFsm);
USHORT PPP_MUXCP_cilen (PPPFSM_S *pstFsm);
VOID   PPP_MUXCP_addci (PPPFSM_S *pstFsm, UCHAR *pucPacket);
USHORT PPP_MUXCP_ackci (PPPFSM_S *pstFsm, UCHAR *pucPacket, ULONG ulLen);
USHORT PPP_MUXCP_nakci (PPPFSM_S *pstFsm, UCHAR *pucPacket, ULONG ulLen);
USHORT PPP_MUXCP_rejci (PPPFSM_S *pstFsm, UCHAR *pucPacket, ULONG ulLen);
UCHAR  PPP_MUXCP_reqci (PPPFSM_S *pstFsm, UCHAR *pucPacket, ULONG *pulLen);

VOID  PPP_MUXCP_up (PPPFSM_S *pstFsm);
ULONG PPP_MUXCP_upcheck (PPPFSM_S *pstFsm);
ULONG PPP_MUXCP_upresetci(PPPINFO_S *);
VOID  PPP_MUXCP_down (PPPFSM_S *pstFsm);
VOID  PPP_MUXCP_finished (PPPFSM_S *pstFsm);
VOID  PPP_MUXCP_starting (PPPFSM_S *pstFsm);
/* Add for DTS2011042101452, by z00166124, at 2011-04-21. 修改原因: 定时器传入接口索引指针 */
VOID PPP_MUXCP_FSM_TimeOut(VOID *pIfIndex);
VOID PPP_MUXCP_Ncp_Reset(VOID *pIfIndex);

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _PPPMUX_MUXCP_H_ */
