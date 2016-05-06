
#ifndef _TCPIP_PUB_STAT_H_
#define _TCPIP_PUB_STAT_H_

#ifdef  __cplusplus
extern  "C"{
#endif

#include "tcpip/tcp4/include/tcp_api.h"
#include "tcpip/ip4/am4/include/am4_api.h"
#include "tcpip/ip4/pp4/include/pp4_api.h"
#include "tcpip/dhcp4c/include/dhcp4c_api.h"
#include "tcpip/ptp/include/ptp_cbb_api.h"
#include "tcpip/synce/include/synce_api.h"
#include "tcpip/etharp/include/etharp_api.h"

#define MAX_TCP_SOCK_INFO_NUM   16
#define MAX_IPIF_STAT_NUM       12
#define MAX_PTP_SLAVE_STAT_NUM  2
#define MAX_SYNCE_PDUSTAT_NUM   2
#define MAX_ETHSTAT_NUM         3

/*日志用魔术字*/
#define PUB_STAT_MAGIC_NUM      0x1A3B5C7D

typedef struct tagTCPIPDataStat
{
    TCPSTAT_S stTcpStat;                                /*TCP 全局统计                        */
    ULONG   ulMagicNumber0;                             /*魔术字，用于检查日志是否对齐，下同  */
    TCP_SOCK_INFO_S stTcpConStat[MAX_TCP_SOCK_INFO_NUM];/*针对socket的TCP统计                 */
    ULONG   ulMagicNumber1;
    IPSTAT_S stGloalIpStat;                             /*全局IP统计信息                      */    
    ULONG   ulMagicNumber2;
    IPIFSTAT_LIST_S stIpIfStatList[MAX_IPIF_STAT_NUM];  /*基于接口的IP统计,MP子链路不进行统计 */    
    ULONG   ulMagicNumber3;
    DHCP4C_STATISTIC_S stDhcpStat;                      /*DHCP报文统计                        */
    ULONG   ulMagicNumber4;
    PTP_SLAVE_STAT_LIST_S stPtpStatList[MAX_PTP_SLAVE_STAT_NUM];/*1588报文统计                */
    ULONG   ulMagicNumber5;
    SYNCE_PDUSTAT_LIST_S stSynceStatList[MAX_SYNCE_PDUSTAT_NUM];/*只记录eth接口               */
    ULONG   ulMagicNumber6;
    ETHSTAT_LIST_S stEthStatList[MAX_ETHSTAT_NUM];      /*只记录eth接口                       */
    ULONG   ulMagicNumber7;
} TCPIP_DATA_STAT_S;

/* 获取PTP统计回调 */
typedef ULONG (*PTP_PUBGET_STAT_FUNC)(PTP_SLAVE_STAT_LIST_S *pstStatList, ULONG ulListSize);

/*******************************************************************************
*    Func Name: TCPIP_GetAllDataStats
* Date Created: 2012-09-17
*       Author: heyijun 00218462
*  Description: 获取系统各个模块的统计信息
*        Input: NONE
*       Output: TCPIP_DATA_STAT_S *pstIPAllData
*       Return: VOS_OK or 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-17   heyijun 00218462        Create for DTS2012092803600
*
*******************************************************************************/
extern ULONG TCPIP_GetAllDataStats(TCPIP_DATA_STAT_S *pstIPAllData);

/*********************************全局变量定义********************************/

#ifdef  __cplusplus
}
#endif

#endif

