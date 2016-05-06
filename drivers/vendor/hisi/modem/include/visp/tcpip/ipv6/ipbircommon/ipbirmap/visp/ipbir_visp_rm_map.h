/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              ipbir_visp_rm_map.h
*
*    Project Code:  IPOS IR V1R2
*    Version     :  Initial Draft
*    Module Name :  IPB IR
*    Create Date :  2006/08/23
*    Author      :  IPv6 Team
*    Description :  To define VISP specific RM macros
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-08-23  Rajat       Created for defining VISP related RM macros
************************************************************************/



#ifndef _IPB_IR_VISP_RM_MAPP_H_
#define _IPB_IR_VISP_RM_MAPP_H_

#ifdef    __cplusplus
extern "C"{
#endif

#include "common/visp/VISP_IR_SFIB.h"

/*  Never Compiled for VISP case*/
#define   IPB_IR_RM_IM_IFNETSENDMSG6(usInstanceID, pstIfnetMsg)


#define IPB_IR_IS_RM_EXIST \
    g_stIP6ADDR_SRM_CallBack.pfIP6_Addr_Shell_Srm_Callback

#define   IPB_IR_IM_RM_IPSENDMSG6(usInstanceID,pstIpMsg) \
    (g_stIP6ADDR_SRM_CallBack.pfIP6_Addr_Shell_Srm_Callback)((USHORT)usInstanceID,(IP6_ADDR_NOTIFY_MSG_S *)pstIpMsg)


/*  Never Compiled for VISP case*/
#define IPB_IR_IM6_PROCESSISLINKCTRL(ifindex, ensiocifup, pRet)




/**********************************************************************
In current code
ADDR6_TORT_MSG_S  stMsgToRoute;

stMsgToRoute.ulIfnetIndex = ulIfIndex;
stMsgToRoute.ucMsgType = RTM_NEWADDRESS;
stMsgToRoute.ucPrefixLength = (UCHAR)pstIp6IfAddr->ia6_ulPrefixLength;
stMsgToRoute.aulLogAddr[0] = stIn6Addr.u6_addr.u6_uladdr[0];
stMsgToRoute.aulLogAddr[1] = stIn6Addr.u6_addr.u6_uladdr[1];
stMsgToRoute.aulLogAddr[2] = stIn6Addr.u6_addr.u6_uladdr[2];
stMsgToRoute.aulLogAddr[3] = stIn6Addr.u6_addr.u6_uladdr[3];




In changed code
IPB_IR_ADDR_TO_RM_S stMsgToRM = {0};

IPB_IR_ADDR_SET_RM_MSG_IFINDEX( stMsgToRM , ulIfIndex );
IPB_IR_ADDR_SET_RM_MSG_TYPE_ADD( stMsgToRM );
IPB_IR_ADDR_SET_RM_MSG_PREFIXLENGTH(stMsgToRM , pstIp6IfAddr->ia6_ulPrefixLength);
IPB_IR_ADDR_SET_RM_MSG_LOGADDR0(stMsgToRM,stIn6Addr.u6_addr.u6_uladdr[0]);
IPB_IR_ADDR_SET_RM_MSG_LOGADDR1(stMsgToRM,stIn6Addr.u6_addr.u6_uladdr[1]);
IPB_IR_ADDR_SET_RM_MSG_LOGADDR2(stMsgToRM,stIn6Addr.u6_addr.u6_uladdr[2]);
IPB_IR_ADDR_SET_RM_MSG_LOGADDR3(stMsgToRM,stIn6Addr.u6_addr.u6_uladdr[3]);

*****************************************************************************/

#define IPB_IR_ADDR_TO_RM_S \
    SFIB_AM6_MSG_S

#define IPB_IR_ADDR_SET_RM_MSG_IFINDEX(stMsg , val) \
    stMsg.ulIfnetIndex = val
#define IPB_IR_ADDR_SET_RM_MSG_TYPE_ADD( stMsg ) \
    stMsg.ulMsgType = SFIB_AM6_NEW_ADDRESS

#define IPB_IR_ADDR_SET_RM_MSG_TYPE_DEL( stMsg ) \
    stMsg.ulMsgType = SFIB_AM6_DEL_ADDRESS
#define IPB_IR_ADDR_SET_RM_MSG_PREFIXLENGTH(stMsg,val) \
    stMsg.ulSubMaskLen = val

#define IPB_IR_ADDR_SET_RM_MSG_LOGADDR0(stMsg,val) \
    stMsg.ulLogAddr[0] = val

#define IPB_IR_ADDR_SET_RM_MSG_LOGADDR1(stMsg,val) \
    stMsg.ulLogAddr[1] = val

#define IPB_IR_ADDR_SET_RM_MSG_LOGADDR2( stMsg,val ) \
    stMsg.ulLogAddr[2] = val

#define IPB_IR_ADDR_SET_RM_MSG_LOGADDR3( stMsg,val ) \
    stMsg.ulLogAddr[3] = val


#define IPB_IR_ADDR_RM_INIT \
    VOS_OK



#ifdef __cplusplus
}
#endif        /* end of __cplusplus */


#endif  /* end of _IPB_IR_VISP_RM_MAPP_H_ */
