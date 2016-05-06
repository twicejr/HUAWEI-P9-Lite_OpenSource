/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              icmp_core.h
*
* Project Code: VISPV100R005
*  Module Name: ICMP4
* Date Created: 2006-01-24
*       Author: Li LiXiang
*  Description: 定义CORE中使用到的结构体
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-24   Li LiXiang              Create
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _ICMP_CORE_H_
#define _ICMP_CORE_H_

/* ICMP4模块使用的SID统一在此定义,一个函数对应一个SID */
#define    SID_COMP_ICMP4_ICMP_CREATEICMP   1
#define    SID_COMP_ICMP4_ICMP_INPUT        2
#define    SID_COMP_ICMP4_ICMP_REFLECT      3
#define    SID_COMP_ICMP4_ICMP_REFLECTENQUE 4
#define    SID_COMP_ICMP4_ICMP_SEND         5

#define    SID_COMP_ICMP4_ICMP_SETPINGALLOWLIST 6
#define    SID_COMP_ICMP4_ICMP_SLLNODE 7
#define    SID_COMP_ICMP4_ICMP_SLL 8

struct tagMBuf;
struct tagIP;
struct tagICMP;

typedef struct tagIpIcmpModInfo
{
    ULONG ulModId;
    ULONG ulSubModId;
} IP_ICMP_MOD_INFO_S;

typedef struct tagIpIcmpIcCallbackSet
{
    VOID (*pfICMP_PacketDiscard_Msg)(struct tagMBuf *pMBuf, ULONG ulErrCode);
    ULONG (*pfICMP_DebugIcmpPacket)(struct tagICMP* pstIcmp, struct tagIP* pstIp,ULONG ulDebugType);

}IP_ICMP_IC_CALLBACK_SES_S;

#endif  /*  _ICMP_CORE_H_  */

#ifdef  __cplusplus
}
#endif

