/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              osicp_funp.h
 *
 *  Project Code: VISPV1R6C03
 *   Module Name: osicp
 *  Date Created: 2007-07-11
 *        Author: Zhangchunyu
 *   Description:  OSICP Core模块私有函数说明     
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2007-07-11      Zhangchunyu        Create
 *
 *************************************************************************/

#ifndef      _OSICP_FUNP_H_
#define      _OSICP_FUNP_H_

#ifdef      __cplusplus
extern "C" {
#endif		/* end of __cplusplus */

/* 接口函数 */
VOID PPP_OSICP_Init(PPPINFO_S *) ;
VOID PPP_OSICP_ReceiveEventFromCore (VOID *, ULONG , char *) ;
VOID PPP_OSICP_ReceivePacket (VOID *, UCHAR* , UCHAR* , ULONG ) ;

/* 回调函数 */
VOID   PPP_OSICP_resetci(PPPFSM_S *f) ;
USHORT PPP_OSICP_cilen(PPPFSM_S *) ;
VOID   PPP_OSICP_addci(PPPFSM_S *, UCHAR *) ;
USHORT PPP_OSICP_ackci(PPPFSM_S *, UCHAR *, ULONG) ;
USHORT PPP_OSICP_nakci(PPPFSM_S *, UCHAR *, ULONG) ;
USHORT PPP_OSICP_rejci(PPPFSM_S *, UCHAR *, ULONG) ;
UCHAR  PPP_OSICP_reqci(PPPFSM_S *, UCHAR *, ULONG *) ;
VOID   PPP_OSICP_up(PPPFSM_S *) ;
VOID   PPP_OSICP_down(PPPFSM_S *) ;
VOID   PPP_OSICP_finished(PPPFSM_S *) ;
VOID   PPP_OSICP_starting(PPPFSM_S *) ;

/* 内部函数 */
ULONG PPP_OSICP_UpResetCi(PPPINFO_S *) ;
/* Add for DTS2011042101452, by z00166124, at 2011-04-21. 修改原因: 定时器传入接口索引指针 */
VOID PPP_OSICP_FSM_TimeOut(VOID *pIfIndex);
VOID PPP_OSICP_Ncp_Reset(VOID *pIfIndex);

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _OSICP_FUNC_H_ */






