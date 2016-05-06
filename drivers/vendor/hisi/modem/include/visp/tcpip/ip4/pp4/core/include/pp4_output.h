/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pp4_output.h
*
*  Project Code: VISP1.5
*   Module Name: PP4  
*  Date Created: 2002-06-18
*        Author: chenshuanglong(28510)
*   Description: pp4_output.c的头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2002-06-18   chenshuanglong(28510)   Create
*  2006-11-01   zhoutong(43740)         规范性整改
*
*******************************************************************************/


#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _PP4_OUTPUT_H_
#define _PP4_OUTPUT_H_

/*
 * Structure stored in mbuf in inpcb.ip_options
 * and passed to ip_output when ip options are in use.
 * The actual length of the options (including ipopt_dst)
 * is in m_len.
 */
typedef struct tagIPOPTION
{
    struct tagINADDR    ipopt_stDst;   /* first-hop dst if source routed */
    char   ipopt_chList_a[MAX_IPOPTLEN]; /* options proper */
}IPOPTION_S;

extern LONG IP_AddMembership(ULONG ulOptionName, MBUF_S *pstMBuf, 
            IPMOPTIONS_S **ppstIpMop, IPMULTI_S **ppstIPMulti, ULONG *pulIndex);
extern LONG IP_DropMembership(IPMREQ_S *pstMReq, IPMOPTIONS_S *pstIpMop, ULONG ulIndex);

extern ULONG IP_FindMembership(IPMOPTIONS_S *pstIpMop, IPMREQ_S *pstMReq, ULONG *pulIndex);

/* IP报文发送 */
extern ULONG IP_Output(MBUF_S *pstMBuf, MBUF_S *pstMOpt, struct tagROUTE *pstRo,
             LONG lFlags, struct tagIPMOPTIONS *pstIpMo);
extern ULONG IP_Output_ForInternal(struct tagMBuf *pstMBuf, struct tagMBuf *pstMOpt, struct tagROUTE *pstRo, 
                                   LONG lFlags, struct tagIPMOPTIONS *pstIpMo );
/* 释放多播选项 */
extern void IP_FreeMOptions(IPMOPTIONS_S *pstIpMo);

extern USHORT Ip_NewId(VOID);

#endif  /* _PP4_OUTPUT_H_  */

#ifdef  __cplusplus
}
#endif


