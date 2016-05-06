/*******************************************************************************
*
*
*                Copyright 2011, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              lldp_var.h
*
*  Project Code: V2R3C06
*   Module Name:   
*  Date Created: 2011-09-27
*        Author: liangjicheng 00103192
*   Description: 变量声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2011-09-27   liangjicheng 00103192   Create
*
*******************************************************************************/
#ifndef _LLDP_VAR_H_
#define _LLDP_VAR_H_

#ifdef  __cplusplus
extern "C"{
#endif

extern LLDP_LOCAL_SYS_INFO_S    g_stLldpLocalSystemData;    /*本地设备系统信息*/
extern LLDP_LOCAL_SYS_STAT_S g_stLldpLocalSysStat;     /*系统统计信息*/
extern LLDP_LOCAL_PORT_S **g_stLldpLocalPortArray;       /*本地端口表项链表LLDP_LOCAL_PORT_S*/
extern ULONG g_ulLldpLocalPortNum;      /*本地端口数量*/
extern BOOL_T g_bLLDP_ShellInit;   /*LLDP是否初始化成功*/

/*Added by guo00178934, 系统最大邻居数, 2011/11/8   问题单号:DTS2011110104340 */
extern ULONG  g_ulLldpRemmTotal;             /*系统邻居总数*/
/* End of Added by guo00178934, 2011/11/8   问题单号:DTS2011110104340 */


/* Global semaphore for LLDP */
extern ULONG g_ulSemForLldp ;

/*LLDPRUN任务的任务ID和消息队列ID*/
extern ULONG ulLLDPTaskID;


extern ULONG txFastInit;
extern ULONG reinitDelay;
extern ULONG msgTxInterval;

extern ULONG g_ulLLDPControlQueID;
extern ULONG g_ulLLDPTimerQueID;
extern ULONG g_ulLLDPRcvQueID;
extern ULONG g_ulLLDPTransmitTimerQueID;

extern ULONG g_ulLLDPDebugSwitch;
extern ULONG g_ulLLDPDebugIfIndexFilter;
extern ULONG g_ulLLDPDebugMACTypeFilter;
extern ULONG g_ulLLDPRemIndex;

extern ULONG g_ulLLDPSendPktFilter;
extern ULONG g_ulLLDPReceivePktFilter;

/*Added by limin00188004, 增加报文发送时选择802.1或802.3协议规定的Link Aggregation TLV, 2011/11/4   问题单号:DTS2011110806987 */
extern ULONG g_ulLLDPLinkAggrTlvSwitch;    /*值为0, 选择发送802.1中的规定; 值大于0，选择发送802.3中的规定。*/
/* End of Added by limin00188004, 2011/11/4   问题单号:DTS2011110806987 */

/*Added by zhangliangzhi00187023, 【检视发现问题】需要支持下发组播地址过滤功能, 2012/8/29   问题单号:DTS2012082907401 */
extern UCHAR g_lldp_szEthDMA[LLDP_MAX_MACTYPE_SIZE][LLDP_MAC_ADDR_LEN] ;
/* End of Added by zhangliangzhi00187023, 2012/8/29   问题单号:DTS2012082907401 */

/*Added by luogaowei, 上报告警携带的邻居信息, 2013/3/30, DTS2013040700481 */
extern LLDP_REM_INFO_S  *g_pstLLDPWarningRemInfo;

/*added by w00217009,LLDP端口添加方式，默认0由visp创建接口时联动添加，为1则由产品调用api进行添加,DTS2013060608306*/
extern ULONG g_ulLLDPAddPortMode;

extern LLDP_GETEXTTLV_HOOK_FUNC g_stLLDPGetExtTlv;

extern LLDP_INPUT_HOOK_FUNC g_stLLDPInputHook;

/* Global value for storing LLDP maximum supported interface*/
extern ULONG g_ulLldpMaxLocalPortNum;

/* Global value for storing LLDP maximum neighbour interface*/
extern ULONG g_ulLldpMaxNbrNum;

#ifdef  __cplusplus
}
#endif

#endif
