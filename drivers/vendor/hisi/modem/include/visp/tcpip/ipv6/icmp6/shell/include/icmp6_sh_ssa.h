/********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*--------------------------------------------------------------------
*                              icmp6_sh_ssa.h
*
*    Project Code : VRP5.0
*    Module Name  : IP6 ICMP6
*    Create Date  : 2003/06/22
*         Author  : Mahaveer Jain
*        Version  :
*     Description : Shell SSA implement header file for ICMP6 module
*--------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -------------------------------------------------------------------
*  2003-06-22  Mahaveer Jain    Create
**********************************************************************/
#ifndef _ICMP6_SH_SSA_H
#define _ICMP6_SH_SSA_H

#ifdef _cplusplus
extern "C"{
#endif

#define IP6_ICMP6_TIMER_TIMEOUT 0x1

/* Structure contains ICMP6 message type and subtype */
typedef struct tagICMP6_Msg_S
{

    ULONG   ulMajorMsgType;   /* IP6_ICMP6_TIMER_TIMEOUT */
    ULONG   ulSubMsgType;

}IP6_ICMP6_MSG_S;

typedef VOS_TIMERMSG_S IP6_ICMP6_Timer_MSG_S;

#ifndef pfRCV_FUN
typedef VOID (*pfRCV_FUN)(MBUF_S *,ULONG);
#endif

#ifdef _cplusplus
}
#endif /* _cplusplus */

#endif  /* _ICMP6_SH_SSA_H */


