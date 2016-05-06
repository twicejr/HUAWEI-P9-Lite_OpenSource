/*****************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------
*                              TCP6_fsm.h
*
*    Project Code:  VRP5.0
*    Module Name:  IP6 TCP6
*    Create Date:  2003/06/27
*    Version     : Initial Draft
*    Author:       Naina Gupta
*    Description:  TCP6 state macros defined
*-----------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------
*  2003-06-27  Naina Gupta         Created
******************************************************************
*/


#ifndef _TCP6_FSM_H
#define _TCP6_FSM_H

#ifdef    __cplusplus
extern    "C"{
#endif

#define    TCP6S_HAVERCVDSYN(s)    ((s) >= TCP6S_SYN_RECEIVED)
#define TCP6S_HAVERCVDFIN(s) ((s) >= TCP6S_TIME_WAIT)
#define TCP6S_ESTABLISH(s)   ((s) == TCP6S_ESTABLISHED)

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif

