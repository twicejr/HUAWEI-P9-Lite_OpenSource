/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_type.h
*
*  Project Code:
*   Module Name: PTPV2 def
*  Date Created: 2014-03-03
*        Author: luoagwoei & dutianyi
*   Description: PTPV2特性宏定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-03-03  luoagwoei & dutianyi      Create
*******************************************************************************/

#ifndef _PTPV2_DEF_H_
#define _PTPV2_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

#define PTPV2_YES 1
#define PTPV2_NO  0

#define PTPV2_CREATE  1
#define PTPV2_DELETE  0

/*定义PTPV2模块MID/SID*/
#define PTPV2_MID       MID_COMP_PTPV2
#define SID_PTP_FOREIGN_MASTER   1
#define SID_PTP_PORTINFO         2
#define SID_PTP_SUBPORTINFO      3
#define SID_PTP_PORTMANAGEINFO   4
#define SID_PTP_GLOBALINFO       5
#define SID_PTP_TIMER            6

/* PTP版本号 */
#define PTPV2_VERSION       2

/* Keep alive 报文的发送间隔 64S */
#define PTPV2_LIVE_INTERVAL     6

/* PTPV2任务名 */
#define PTPV2_TASK_NAME     "PTP2"

/*PTPV2队列长度*/
#define PTPV2_QDEPTH      2048

/*PTPV2队列类型标志*/
#define PTPV2_QMODE       VOS_Q_FIFO | VOS_Q_SYN

#define PTPV2_EVT_TASK_OVER_Q      0x00010000

/* 事件id需要使用高16位*/
#define PTPV2_IEEE8023MSG_EVENT_ID  0x00020000      /*MAC报文写入到PTP队列使用该消息*/
#define PTPV2_IEEE8023_MSG_TYPE 0x00001000          /*MAC报文写入到PTP队列MSG[0]使用该标识*/



#define VLANTYPE_DOT1Q  0x8100              /* VLAN 802.1q格式*/
#define PTPV2_IEEE8023_ETHTYPE  0x88F7      /*1588 OVER MAC 以太类型*/

#define DOT1Q_TAG_SIZE  4

#define PTPV2_MACADDRLEN  6

#define PTPV2_HEADER_LEN 34

/* PTP报文最大长度 */
#define PTPV2_MAXIMUM_PKT_SIZE   2048

#define PTPV2_VERSION                     2

#define PTPV2_MAX_PORTNO    128  /*最大的PTP端口个数*/
#define PTPV2_MIN_PORTNO     1   /*最小的PTP端口个数*/

#define SE_ASYNC   0x0020


#define TCPIP_PTP_WARN_BMC_FAIL_FLAG    0x0001  /* PTP选源失败告警标记*/

#define PTPV2_TIMER_DELETE 1
#define PTPV2_TIMER_NOT_DELETE 0

#define  PTPV2_FSM_MODE_OC_MASTER  1
#define  PTPV2_FSM_MODE_OC_SLAVE   2
#define  PTPV2_FSM_MODE_BC         3

extern int PTPV2_compare(void *a, void *b);
#define PTPV2_init_avl_node(NODE)            (NODE).parent = 0;                \
                                             (NODE).left = 0;                  \
                                             (NODE).right = 0;                 \
                                             (NODE).sLeftHeight = -1;                \
                                             (NODE).sLeftHeight = -1
#define PTPV2_Tree_offset(STRUCT,FIELD) (unsigned short)((unsigned char *)(&((STRUCT *)1)->FIELD) - (unsigned char *)1)
#define PTPV2_avl_insert(TREE, NODE, TREE_INFO) (NULL == AVL3_FindToInsert(&(TREE), &(NODE), &(TREE_INFO)))
#define PTPV2_avl_delete(TREE, NODE)            AVL3_DeleteNode(&(TREE), &(NODE))
#define PTPV2_find(TREE, KEY, TREE_INFO) AVL3_FindNode(&(TREE), (KEY), &(TREE_INFO))

#define PTPV2_avl_next(NODE, TREE_INFO) AVL3_GetNextNode(&(NODE), &(TREE_INFO))
#define PTPV2_avl_first(TREE, TREE_INFO) AVL3_GetFirstNode(&(TREE), &(TREE_INFO))

#define  TCPIP_PTP_FOREIGN_MASTER_LEN   8

#define PTPV2_CLASSQL_NUM     16

/*BMC 选源策略，目前仅支持1588选源*/
#define  TCPIP_PTP_BMC_POLICY_1588     1
#define  TCPIP_PTP_BMC_POLICY_G8265    2
#define  TCPIP_PTP_BMC_POLICY_G8275    3

/*当前源是否优选源标记*/
#define PTPV2_PRI_CLASS  1
#define PTPV2_NOT_PRI_CLASS  0

/*stepsRemoved最大有效值*/
#define PTPV2_MAX_STEPSREMOVED  255

/* 延时机制定义 */
typedef enum tagTCPIP_PTP_DELAY_MACHENISM_E
{
    /*目前仅支持E2E*/
    TCPIP_PTP_DELAY_MACHENISM_E2E = 0X01,          /* 请求_响应延时机制 */
    TCPIP_PTP_DELAY_MACHENISM_P2P = 0X02,          /* 对端延时机制 */
    TCPIP_PTP_DELAY_MACHENISM_DISABLE = 0XFE       /* 延时机制不作用 */
} TCPIP_PTP_DELAY_MECHENISM_E;


/* 定义单多播模式 */
typedef enum tagTCPIP_PTP_CLOCK_CAST_MODE_E
{
    TCPIP_PTP_CLOCK_UNICAST_MODE,             /* 单播模式*/
    TCPIP_PTP_CLOCK_MULTICAST_MODE,           /* 多播模式*/
    TCPIP_PTP_CLOCK_IEEE8023_MODE             /* OVER MAC模式*/
} TCPIP_PTP_CLOCK_CAST_MODE_E;


/* 定义协议枚举类型 */
typedef enum tagTCPIP_PTP_PROTOCAL_TYPE_E
{
    TCPIP_PTP_PROTOCAL_UDP_IPV4 = 1,
    TCPIP_PTP_PROTOCAL_UDP_IPV6,
    TCPIP_PTP_PROTOCAL_IEEE_802
} TCPIP_PTP_PROTOCAL_TYPE_E;

#ifdef __cplusplus
}
#endif


#endif

