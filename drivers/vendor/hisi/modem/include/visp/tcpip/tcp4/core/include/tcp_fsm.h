/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcp_fsm.h
*
*  Project Code: VISP1.5
*   Module Name: IP TCP4  
*  Date Created: 2000-03-25
*        Author: Chen Bin
*   Description: ¶¨ÒåTCPµÄ×´Ì¬
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2000-03-25  Chen Bin         Create the first version.
*
*******************************************************************************/

#ifndef _TCP_FSM_H
#define _TCP_FSM_H

#ifdef  __cplusplus
extern  "C"{
#endif

/* TCP connection state definations. */

#define TCPS_CLOSED         0   /* closed */
#define TCPS_LISTEN         1   /* listening for connection */
#define TCPS_SYN_SENT       2   /* active, have sent syn */
#define TCPS_SYN_RECEIVED   3   /* have send and received syn */

#define TCPS_ESTABLISHED    4   /* established */
#define TCPS_CLOSE_WAIT     5   /* rcvd fin, waiting for close */

#define TCPS_FIN_WAIT_1     6   /* have closed, sent fin */
#define TCPS_CLOSING        7   /* closed xchd FIN; await FIN ACK */
#define TCPS_LAST_ACK       8   /* had fin and close; await FIN ACK */
#define TCPS_FIN_WAIT_2     9   /* have closed, fin is acked */
#define TCPS_TIME_WAIT      10  /* in 2*msl quiet wait after close */

#define TCP_NSTATES         11
#define TCP_DELTCB          11  /* for SNMP */

#define TCPS_HAVERCVDSYN(s) ((s) >= TCPS_SYN_RECEIVED)
#define TCPS_HAVERCVDFIN(s) ((s) >= TCPS_TIME_WAIT)
#define TCPS_ESTABLISH(s)   ((s) == TCPS_ESTABLISHED)

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */


#endif


