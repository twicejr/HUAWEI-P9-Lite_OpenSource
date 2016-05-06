/************************************************************************
 *                                                                      *
 *                             ccp_func.h                               *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        			                                    *
 *  Author:                         			                        *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           PPPµÄCCPÐ­ÒéÄ£¿éË½ÓÐº¯Êý                        *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *                                                                      *
 ************************************************************************/

#ifdef		__cplusplus
extern		"C"{
#endif

#ifndef _CCP_FUNC_H_
#define _CCP_FUNC_H_
/********************************************************************/
VOS_VOID PPP_CCP_ReceiveEventFromCore (VOS_VOID *pstCcpInfo, VOS_UINT32 ulCmd, char *pPara);

VOID PPP_CCP_SendResetReq(PPPINFO_S* pstPppInfo) ;

VOS_VOID PPP_CCP_init (PPPINFO_S* pstPppInfo);


VOID PPP_CCP_ReceivePacket (VOID *pstCcpInfo, UCHAR* pHead, UCHAR* pPacket, VOS_UINT32 ulLen,VOS_UINT32 ulRPIndex) ;/* Modified by liutao 38563 at 2004-09-22 V800R002 for PPPÑ¹ËõÒÆÖ² */

VOS_UINT16 PPP_CCP_cilen(PPPFSM_S *);         /* Return length of our CI */
VOID PPP_CCP_addci(PPPFSM_S *,  UCHAR *); /* Add our CI */
VOS_UINT16 PPP_CCP_ackci(PPPFSM_S *, UCHAR *, VOS_UINT32);    /* Peer ack'd our CI */
VOS_UINT16 PPP_CCP_nakci(PPPFSM_S *, UCHAR *, VOS_UINT32);    /* Peer nak'd our CI */
VOS_UINT16 PPP_CCP_rejci(PPPFSM_S *, UCHAR *, VOS_UINT32);    /* Peer rej'd our CI */
UCHAR PPP_CCP_reqci(PPPFSM_S *, UCHAR *, VOS_UINT32 *); /* Rcv CI */
VOID PPP_CCP_up(PPPFSM_S *);     /* We're UP */
VOID PPP_CCP_down(PPPFSM_S *);       /* We're DOWN */
VOID PPP_CCP_finished(PPPFSM_S *);
VOS_UINT16 PPP_CCP_extcode(PPPFSM_S *, UCHAR , UCHAR , UCHAR *, UCHAR *, VOS_UINT32, VOS_UINT32);/* Modified by liutao 38563 at 2004-09-22 V800R002 for PPPÑ¹ËõÒÆÖ² */

VOID PPP_CCP_disabled( PPPFSM_S *f ); /* dyo 99.8.23 */


VOID PPP_CCP_rresetreq (PPPFSM_S *f, UCHAR id, UCHAR *pHead, UCHAR *pPacket, VOS_UINT32 ulLen,VOS_UINT32 ulRPIndex) ;/* Modified by liutao 38563 at 2004-09-22 V800R002 for PPPÑ¹ËõÒÆÖ² */
VOID PPP_CCP_rresetack (PPPFSM_S *f, UCHAR id, UCHAR *pPacket, VOS_UINT32 ulLen,VOS_UINT32 ulRPIndex) ;/* Modified by liutao 38563 at 2004-09-22 V800R002 for PPPÑ¹ËõÒÆÖ² */

VOID PPP_CCP_resetci( PPPFSM_S * );

VOID PPP_CCP_SendResetReqTimeout(VOID *pPppInfo);/*WGGSN_B03_L2TP_PPPC_COMP*/
/********************************************************************/



#endif /* _CCP_FUNC_H_ */

#ifdef		__cplusplus
}
#endif
