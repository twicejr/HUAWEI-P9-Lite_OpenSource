/******************************************************************************
*
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*
*------------------------------------------------------------------------------
*    Project Code   : VRP5.0
*    Module Name    : VISP Adapter for ICMP6
*    Version        : Initial Draft
*    File Name      : icmpv6_api.h
*    Create Date    : 2008/09/09
*    Author         : Suraj R (72063)
*    Description    : VISP adapter for ICMP6
*------------------------------------------------------------------------------
* Modification History
* DATE        NAME              DESCRIPTION
* ------------------------------------------------------------------------
* 2008/09/09  Suraj R (72063)   Create
**************************************************************************
*/

#ifndef      _ICMP6_API_H_
#define      _ICMP6_API_H_

#ifdef      __cplusplus
extern "C"{
#endif

#define ADAPT_MAX_DISP_LENGTH   80

#define ICMP6ADP_SHOWERRORINFO  VRP_YES
#define ICMP6ADP_AUTOINIT       VRP_YES


#define ICMP6ADP_OK VOS_OK
#define ICMP6ADP_ERR VOS_ERR

#define ICMP6ADP_DISPLAY(m_string) TCPIP_InfoOutput(m_string)


#define ICMP6ADP_ERROR_STARTVALUE 0x600
#define ICMP6ADP_ERROR_MAXVALUE   0xffffffff

/* Return Values */
typedef enum tagICMP6_ADP_ERRORNUM_E
{
    ICMP6ADP_ERR_MEMBERFN_UNAVAILABLE = ICMP6ADP_ERROR_STARTVALUE,
    ICMP6ADP_ERR_INIT_NOTDONE,
    ICMP6ADP_ERR_OPFAIL,
    ICMP6ADP_ERR_INVALID_IFNAME,
    ICMP6ADP_ERR_INVALIDINPUT,
    ICMP6ADP_ERRORNUM_ULONG_PAD = ICMP6ADP_ERROR_MAXVALUE
}ICMP6_ADP_ERRORNUM_E;

/* Initialize ICMP6 Component */
extern ULONG ICMP6_InitAdapt();

/* Display ICMPv6 Statistics per interface */
/* Internally calls Core API to Get Interface Statistics */
extern ULONG ICMP6_DisplayIntfStatistics(CHAR *pszIfName);

/* Enable / Disable ICMPv6 Debugging */
extern ULONG ICMP6_DebugSwitch(ULONG ulFlag);

/* Reset Interface Statistics */
extern ULONG ICMP6_ResetIntfStatistics(CHAR *pszIfName);

/* Get Global Statistics by Type */
extern ULONG ICMP6_GetGlobalStatisticsByType(ICMP6STATFIELD efield,
                                               UCHAR ucType, ULONG *pulVal);

/* Reset Global Statistics */
extern ULONG ICMP6_ResetGlobalStatisticsByType(ICMP6STATFIELD efield,
                                                            UCHAR ucType);

/* Get All Global Statistics */
extern ULONG ICMP6_GetAllGlobalStatistics(ICMP6STAT_S *pstIcmp6Stat);

/* Reset All ICMP6 Statistics */
extern ULONG ICMP6_ResetAllStatistics();

/* Increment Global as well as Interface Level Statistics */
extern ULONG ICMP6_IncrementStatistics(CHAR *szIfName,
                                    ICMP6STATFIELD eStatType,
                                    UCHAR ucType);

/* Enable or disable Too-Big-Error RateLimiting */
extern ULONG ICMP6_SetTooBigErrorRateLimit (ULONG ulRateStatus);

/* Set or Reset Error Packet Rate Limiting Bucket Size / Interval */
extern ULONG ICMP6_ErrorRateLimitUpdate(const ICMP6_ERRRATE_MSG_S *pstBuf);

/* Get ICMP6 Error Rate Limit Interval */
extern ULONG ICMP6_ErrorRateLimitGetValue (ULONG *pulInterval,
                                                            ULONG *pulTokkens);

extern ULONG ICMP6_EnableDisableIntfDestUnReachError (ULONG ulIfIndex,
                                                ULONG ulOperation);

/* Generate ICMP6 Error */
extern ULONG ICMP6_GenerateError(MBUF_S *pstMBuf, UCHAR ucType,
                                                    UCHAR ucCode, LONG lParam);

/* ICMPv6 Flow Register Callback */
extern ULONG ICMP6_Flow_RegisterCallback(ICMP6_EXT_CALLBACK_S *pstCallBack);

/*******************************************************************************
*    Func Name: ICMP6_GetIntfStatistics
* Date Created: 2014-07-04
*       Author: wling 00201943
*  Description: 显示接口icmp6报文统计信息
*        Input: ULONG ulIfIndex:接口索引
*        Output: ICMP6STAT_S *psticmp6stat:icmp6报文统计信息
*       Return: 
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-07-04   wuling 00201943     Create
*
*******************************************************************************/
ULONG ICMP6_GetIntfStatistics(ULONG ulIfIndex, ICMP6STAT_S *psticmp6stat);

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _ICMP6_API_H_ */
