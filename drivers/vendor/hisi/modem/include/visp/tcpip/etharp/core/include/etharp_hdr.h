/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              etharp_hdr.h
*
*  Project Code: VR7C03
*   Module Name: ETHARP  
*  Date Created: 2009-03-02
*        Author: zhongweihua/zhangchi(00104207/00142640)
*   Description: ETHARP体检报告
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-03-02   zhongweihua/zhangchi(00104207/00142640)  Create
*
*******************************************************************************/

#ifndef _ETHARP_HDR_H_
#define _ETHARP_HDR_H_

#ifdef  __cplusplus
extern "C"{
#endif

/* ETHARP体检报告数据结构 */

/* ARP表项更新信息结构 */
typedef struct tagETHARP_HEALTH_ARPUPDATE
{
    TCPIP_TIME_S stUpdateTime;
    ULONG   ulIfIndex;
    ULONG   ulIpAddr;             /* 主机序 */ 
    UCHAR   ucMacAddr[MACADDRLEN];  
    UCHAR   ucResevred[2];
    
    /* 2010-5-25,zKF23859,BC3D03074,增加vrfindex字段  */
    ULONG   ulVrfIndex;
    
}ETHARP_HEALTH_ARPUPDATE_S;

/* ARP解析失败信息结构 */
typedef struct tagETHARP_HEALTH_ARPRESOLVEFAIL
{
    ULONG   ulIfIndex;
    ULONG   ulIpAddr;
    TCPIP_TIME_S stUpdateTime;
}ETHARP_HEALTH_ARPRESOLVEFAIL_S;

typedef struct tagETHARP_HEALTH_STATISTIC
{
    ULONG ulIfIndex;
    ETHSTAT_S stEtharpStatistic;
}ETHARP_HEALTH_STATISTIC_S;

extern VOID ETHARP_Health_BatchCheckup();

extern ULONG ETHARP_Health_ArpCheckup();
extern ULONG ETHARP_Health_StatisticCheckUp();
extern ULONG ETHARP_Health_ArpResolveFailCheckUp();
extern ULONG ETHARP_Health_ProxyRelayCheckUp();
extern ULONG ETHARP_LastWord_BatchCheckup(CHAR *pstBuf, ULONG *pulLastWordLen);

#ifdef  __cplusplus
}
#endif
#endif

