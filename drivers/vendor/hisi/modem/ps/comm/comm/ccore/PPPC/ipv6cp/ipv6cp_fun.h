
/************************************************************************
 *                                                                      *
 *                             ipv6cp_fun.h                               *
 *                                                                      *
 *  Project Code:                                                 *
 *  Create Date:        2009/12/29                                      *
 *  Author:             z00129699                                      *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           IPV6CP模块私有函数说明                            *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *   这个文件包含了IPV6CP模块所有私有函数的申明                           *
 *                                                                      *
 ************************************************************************/

#ifndef      _IPV6CP_FUNC_H_
#define      _IPV6CP_FUNC_H_

#ifdef      __cplusplus
extern "C" {
#endif		/* end of __cplusplus */

/* 接口函数 */
VOID PPP_IPV6CP_Init(PPPINFO_S *, VOS_UINT16 *, VOS_UINT16 *) ;
VOID PPP_IPV6CP_ReceiveEventFromCore (VOID *, VOS_UINT32 , char *) ;
VOID PPP_IPV6CP_ReceivePacket (VOID *, UCHAR* , UCHAR* , VOS_UINT32 ) ;

/* 回调函数 */
VOID PPP_IPV6CP_resetci(PPPFSM_S *f) ;
VOS_UINT16 PPP_IPV6CP_cilen(PPPFSM_S *) ;
VOID PPP_IPV6CP_addci(PPPFSM_S *, UCHAR *) ;
VOS_UINT16 PPP_IPV6CP_ackci(PPPFSM_S *, UCHAR *, VOS_UINT32) ;
VOS_UINT16 PPP_IPV6CP_nakci(PPPFSM_S *, UCHAR *, VOS_UINT32) ;
VOS_UINT16 PPP_IPV6CP_rejci(PPPFSM_S *, UCHAR *, VOS_UINT32) ;
UCHAR PPP_IPV6CP_reqci(PPPFSM_S *, UCHAR *, VOS_UINT32 *) ;
VOID PPP_IPV6CP_up(PPPFSM_S *) ;
VOID PPP_IPV6CP_down(PPPFSM_S *) ;
VOID PPP_IPV6CP_finished(PPPFSM_S *) ;
VOID PPP_IPV6CP_starting(PPPFSM_S *) ;

/* 内部函数 */
VOS_UINT32 PPP_IPV6CP_UpResetCi(PPPINFO_S *) ;
VOS_UINT32 PPP_ipv6_intfid_check(VOS_UINT16 *pstIpv6addr, VOS_UINT32 ullen);

extern VOID PPP_IPV6CP_Pactket_Proc(PPPINFO_S *pstPppInfo,
                                         UCHAR*     pHead,
                                         UCHAR*     pPacket,
                                         VOS_UINT32      ulLen);

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _IPV6CP_FUNC_H_ */





