/*******************************************************************************
*
*
*                Copyright 2011, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              lldp_fsm.h
*
*  Project Code: V2R3C06
*   Module Name:   
*  Date Created: 2011-09-27
*        Author: liangjicheng 00103192
*   Description: 状态机头文件:状态机宏定义 结构定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2011-09-27   liangjicheng 00103192   Create
*
*******************************************************************************/
#ifndef _LLDP_FSM_H_
#define _LLDP_FSM_H_

#ifdef  __cplusplus
extern "C"{
#endif

/*****************************************************************************/
/* Maximum number of FSM instances for which coverage information is stored. */
/*****************************************************************************/
#define LLDP_FSM_MAX_INSTANCES 30

#define LLDP_MAX_TTL    0xffff
#define LLDP_TTL  (g_stLldpLocalSystemData.stConfigutation.ulTxHoldMultiplier *g_stLldpLocalSystemData.stConfigutation.ulTxInterval + 1)

/**STRUCT+********************************************************************/
/* Structure:   LLDP_FSM_ENTRY                                                    */
/*                                                                           */
/* Description: Entry in an LLDP_FSM Table.                                       */
/*****************************************************************************/
typedef struct lldp_fsm_entry
{
  ULONG next_state;
  ULONG action;
  ULONG count[LLDP_FSM_MAX_INSTANCES];
} LLDP_FSM_ENTRY;

/* PUB ACTION*/
#define LLDP_ACT_NO   0
#define LLDP_ACT_ERR   0xff
#define LLDP_FSM_ERR   0xFF

/******** 无输入 ********/
#define LLDP_NULL_INPUT                      0

/*****************************************************************************/
/* TRANSMIT                                                                  */
/*****************************************************************************/
#define LLDP_TRANSMIT_NUM_INPUTS        6
#define LLDP_TRANSMIT_NUM_STATES        4
#define LLDP_TRANSMIT_NUM_ACTIONS       4

/* TRANSMIT EVENT */
/************** 发送状态机输入条件消息***************/
#define LLDP_SEND_ENABLEDTX_INPUT       1       /** (adminStatus == enabledRxTx) || (adminStatus == enabledTxOnly) **/
#define LLDP_SEND_DISABLEDTX_INPUT      2       /** (adminStatus == disabled) || (adminStatus == enabledRxOnly) **/
#define LLDP_SEND_TXNOW_INPUT           3       /** (txNow == TRUE ) && (txCredit >0) **/
#define LLDP_SEND_TXSHUTDOWNWHILE_INPUT 4       /** txShutdownWhile == 0 **/
#define LLDP_SEND_UCT_INPUT             5       /** UCT **/
#define LLDP_SEND_BEGIN_INPUT           6       /** BEGIN **/

/* TRANSMIT STATE */
#define LLDP_STATE_TX_LLDP_INITIALIZE         1
#define LLDP_STATE_TX_IDLE                    2
#define LLDP_STATE_TX_SHUTDOWN_FRAME          3
#define LLDP_STATE_TX_INFO_FRAME              4

/* TRANSMIT ACTION */
#define LLDP_ACT_TX_LLDP_INITIALIZE         1
#define LLDP_ACT_TX_IDLE                    2
#define LLDP_ACT_TX_SHUTDOWN_FRAME          3
#define LLDP_ACT_TX_INFO_FRAME              4


/*****************************************************************************/
/* TIMER                                                                     */
/*****************************************************************************/
#define LLDP_TRANSMITTIMER_NUM_INPUTS       8
#define LLDP_TRANSMITTIMER_NUM_STATES       6
#define LLDP_TRANSMITTIMER_NUM_ACTIONS       6

/* TIMER EVENT */
/************** 发送定时器状态机输入条件消息***************/
#define LLDP_TIMER_ENABLEDTX_INPUT          1       /** (adminStatus == enabledRxTx) || (adminStatus == enabledTxOnly) **/
#define LLDP_TIMER_LOCALCHANGE_INPUT        2       /** localChange == TRUE **/
#define LLDP_TIMER_TXTTR_INPUT              3       /** txTTR == 0 **/
#define LLDP_TIMER_NEWNEIGHBOR_INPUT        4       /** newNeighbor == TRUE **/
#define LLDP_TIMER_TXTICK_INPUT             5       /** txTick == TRUE **/
#define LLDP_TIMER_UCT_INPUT                6       /** UCT **/
#define LLDP_TIMER_PORTORTXDISABLED_INPUT   7       /** (portEnabled==FALSE)||(adminStatus==disabled)||(adminStatus== 
                                                                    enabledRxOnly) **/
#define LLDP_TIMER_BEGIN_INPUT              8       /** BEGIN **/

/* TIMER STATE */
#define LLDP_STATE_TX_TIMER_INITIALIZE      1
#define LLDP_STATE_TX_TIMER_IDLE            2
#define LLDP_STATE_TX_TIMER_EXPIRES         3
#define LLDP_STATE_TX_TICK                  4
#define LLDP_STATE_SIGNAL_TX                5
#define LLDP_STATE_TX_FAST_START            6


/* TIMER ACTION */
#define LLDP_ACT_TX_TIMER_INITIALIZE        1
#define LLDP_ACT_TX_TIMER_IDLE              2
#define LLDP_ACT_TX_TIMER_EXPIRES           3
#define LLDP_ACT_TX_TICK                    4
#define LLDP_ACT_SIGNAL_TX                  5
#define LLDP_ACT_TX_FAST_START              6


/*****************************************************************************/
/* RECEIVE                                                                   */
/*****************************************************************************/
#define LLDP_RECEIVE_NUM_INPUTS             11
#define LLDP_RECEIVE_NUM_STATES             7
#define LLDP_RECEIVE_NUM_ACTIONS            7

/* RECEIVE EVNET */
/************** 接收状态机输入条件消息***************/
#define LLDP_RECV_RXINFOAGE_INPUT           1       /** rxInfoAge == TRUE **/
#define LLDP_RECV_PORTENABLED_INPUT         2       /** portEnabled == TRUE **/
#define LLDP_RECV_UCT_INPUT                 3       /** UCT **/
#define LLDP_RECV_ENABLEDRX_INPUT           4       /** (adminStatus == enabledRxTx) || (adminStatus == enabledRxOnly) **/    
#define LLDP_RECV_RCVFRAME_INPUT            5       /** rcvFrame == TRUE **/
#define LLDP_RECV_DISABLEDRX_INPUT          6       /** (adminStatus == disabled) || (adminStatus == enabledTxOnly) **/
#define LLDP_RECV_RXTTL_INPUT               7       /** rxTTL == 0 **/
#define LLDP_RECV_RXCHANGES_INPUT           8       /** ((rxTTL!= 0) && (rxChanges == TRUE) **/
#define LLDP_RECV_BADFRAME_INPUT            9       /** (badFrame == TRUE) || ((rxTTL!= 0) && (rxChanges == 
                                                                    FALSE))  **/
#define LLDP_RECV_PORTDISABLEDNOAGE_INPUT   10      /** (rxInfoAge == FALSE) &&(portEnabled == FALSE) **/
#define LLDP_RECV_BEGIN_INPUT               11      /** BEGIN **/

/* RECEIVE STATE */
#define LLDP_STATE_LLDP_WAIT_PORT_OPERATIONAL   1
#define LLDP_STATE_DELETE_AGED_INFO             2
#define LLDP_STATE_RX_LLDP_INITIALIZE           3
#define LLDP_STATE_RX_WAIT_FOR_FRAME            4
#define LLDP_STATE_RX_FRAME                     5
#define LLDP_STATE_DELETE_INFO                  6
#define LLDP_STATE_UPDATE_INFO                  7

/* RECEIVE ACTION */
#define LLDP_ACT_LLDP_WAIT_PORT_OPERATIONAL     1
#define LLDP_ACT_DELETE_AGED_INFO               2
#define LLDP_ACT_RX_LLDP_INITIALIZE             3
#define LLDP_ACT_RX_WAIT_FOR_FRAME              4
#define LLDP_ACT_RX_FRAME                       5
#define LLDP_ACT_DELETE_INFO                    6
#define LLDP_ACT_UPDATE_INFO                    7



/*****************************************************************************/
/* State for LLDP FSMs. When updating this table, don't forget to update the    */
/* array initialization below.                                               */
/*****************************************************************************/

#ifdef  __cplusplus
}
#endif

#endif
