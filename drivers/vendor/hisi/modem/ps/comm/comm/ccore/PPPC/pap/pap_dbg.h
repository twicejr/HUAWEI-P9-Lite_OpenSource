/************************************************************************
 *                                                                      *
 *                             pap_dbg.h	                            *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/06/14                                      *
 *  Author:             Zhu Fengzhi                                     *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           PPP的PAP协议模块DEBUG私有宏定义		            *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 * Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
 *                     ALL RIGHTS RESERVED                              *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *   这个文件定义了PAP协议模块DEBUG的全部私有宏定义						*
 *                                                                      *
 ************************************************************************/

#if( VRP_MODULE_LINK_PPP == VRP_YES )

#if( VRP_MODULE_LINK_PPP_PAP == VRP_YES )

#ifndef      _PAP_DBG_H_
#define      _PAP_DBG_H_

#ifdef      __cplusplus
extern "C" {
#endif		/* end of __cplusplus */


/*PAP 内部的事件代码 */
#define	PAP_INITIALIZATION		0
#define PAP_SERVERLOWERUP		1
#define PAP_CLIENTLOWERUP		2
#define	PAP_LOWERDOWN			3
#define PAP_RECEIVEREQUEST		4
#define	PAP_AAARESULT		    5
#define	PAP_RECEIVEACK			6
#define	PAP_RECEIVENAK			7
#define	PAP_REQUESTTIMEOUT		8
#define	PAP_CODEREJECT			9
#define PAP_WAITREQTIMEOUT		10
#define PAP_WAITAAARSPTIMEOUT	11
#define	PAP_ERROREVENT			12

/*状态代码*/
#define CLIENT_STATE		0
#define	SERVER_STATE		1

VOID PAP_Debug_Packet(PPPINFO_S* , UCHAR *, VOS_UINT32 , VOS_UINT16 , UCHAR );
VOID PAP_Debug_StateChange(PPPINFO_S *, UCHAR ,UCHAR );
VOID PAP_Debug_Event(PPPINFO_S* , UCHAR );
VOID PAP_Debug_Error(PPPINFO_S *, VOS_UINT16 , CHAR *);


#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _PAP_DBG_H_ */

#endif  /* #if( VRP_MODULE_LINK_PPP_PAP == VRP_YES ) */

#endif	/* #if( VRP_MODULE_LINK_PPP == VRP_YES ) */


