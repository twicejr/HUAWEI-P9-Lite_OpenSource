/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         IF_TYPE.H 
 *
 *  Project Code: VISP1.5
 *   Module Name: IFNET
 *  Date Created: 2004/03/28
 *        Author: luohanjun
 *   Description: 
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2004/03/28      luohanjun       Create File
 *  2006/03/30      liai            Adjust for D00654
 *  2006/04/21      liai            Adjust for D00878
 *  2006-05-10   luyao(60000758)    为支持ARM CPU字节对齐特性，修改结构。
 *
 ************************************************************************/

#ifndef _TCPIP_IF_TYPE_H_
#define _TCPIP_IF_TYPE_H_

#ifdef  __cplusplus
extern "C"{
#endif


typedef struct Vector
{
    ULONG    ulUsedMax;            /* 已用的最大单元号  */
    ULONG    ulAllocedMax;         /* 已分配的最大单元号*/
    VOID **  Pindex;               /* 地址数组          */
} VECTOR_S;
typedef  VECTOR_S * PVECTOR_S;



/* 以下四个结构要保持字段相同，仅区分通知函数的类型 */
typedef struct tagIF_MSG_FUNLINK_S  
{
    IF_MSG_NOTIFYFN   if_pfNotifyFn ;  /* 通知函数 */ 
    ULONG   if_ulPriority;   /* 优先级 */   
    struct tagIF_MSG_FUNLINK_S* if_pNext;
}IF_MSG_FUNLINK_S ;

typedef struct tagIF_LMSG_FUNLINK_S  
{
    IF_LMSG_NOTIFYFN   if_pfNotifyFn ;  /* 通知函数 */ 
    ULONG   if_ulPriority;   /* 优先级 */   
    struct tagIF_LMSG_FUNLINK_S* if_pNext;
}IF_LMSG_FUNLINK_S ;

typedef struct tagIF_PTR_FUNLINK_S  
{
    IF_PTR_NOTIFYFN   if_pfNotifyFn ;  /* 通知函数 */ 
    ULONG   if_ulPriority;   /* 优先级 */   
    struct tagIF_PTR_FUNLINK_S* if_pNext;
}IF_PTR_FUNLINK_S ;

/*单向函数链节点结构，用于注册、注销以上各通知函数*/
typedef struct tagIF_FUNLINK_S  
{
    void*   if_pfNotifyFn ;  /* 通知函数 */ 
    ULONG   if_ulPriority;   /* 优先级 */   
    struct tagIF_FUNLINK_S* if_pNext;
}IF_FUNLINK_S ;
/*end for A82D20427*/


/*定时器结构*/
typedef struct tagX_Timer
{
    ULONG ulStartFlag;  /*启动定时器标志 VRP_YES /VRP_NO*/
    ULONG ulTimerPeriod;/*值为定时器周期常量，以秒为单位*/
}IF_TIMER_S;
 

#define CLI_CMD_TEMPLET_IF_ETHERNET         "ethernet"
#define CLI_CMD_TEMPLET_IF_SERIAL           "serial"
#define CLI_CMD_TEMPLET_IF_NULL             "null"
#define CLI_CMD_TEMPLET_IF_LOOPBACK         "loopback"

#define CLI_CMD_TEMPLET_IF_DIALER          "dialer"
#define CLI_CMD_TEMPLET_VIRTUAL_TEMPLATE   "virtual-template"
#define CLI_CMD_TEMPLET_IF_ATM             "atm"
#define CLI_CMD_TEMPLET_MULTILINK          "mp-group"

#define CLI_NO_CMD_TEMPLET                 "NoCMDTemplet"     /* 标识没有命令模板 */

#define CLI_CMD_TEMPLET_IF_VI             "vi"

#define CLI_CMD_TEMPLET_IF_UI             "ui"

#define CLI_CMD_TEMPLET_IF_VLANIF          "vlanif"

#define CLI_CMD_TEMPLET_IF_TUNNEL         "tunnel"

#ifdef  __cplusplus
}
#endif

#endif

