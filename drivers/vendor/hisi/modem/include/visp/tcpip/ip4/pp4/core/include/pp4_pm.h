/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pp4_pm.h
*
*  Project Code: VISP1.5
*   Module Name: PP4  
*  Date Created: 2002-06-18
*        Author: chenshuanglong(28510)
*   Description: pp4_pm.c头文件
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

#ifndef _PP4_PM_H_
#define _PP4_PM_H_


/* SOCKRAW type put in the second of PST. it is used as the wildcard */
#define IP_PP4_RAWSOCKET_PLACE    1
#define IP_PP4_PST_FREE_NUMBER    6

#define IP_PP4_NEWID_TIMEOUT      2

typedef VOID (*INPUT_FUN)(MBUF_S *pRcvSeg, LONG);
typedef LONG (*OUTPUT_FUN)(MBUF_S *,VOID *,VOID*,ULONG,VOID*);
typedef VOID (*CTLINPUT_FUN)(LONG,VOID *,VOID *);
typedef LONG (*CTLOUTPUT_FUN)(LONG, struct tagSOCKET *, LONG, LONG, MBUF_S **);
typedef LONG (*USRREQ_FUN)(struct tagSOCKET *, LONG, VOID *,VOID *, VOID *);
/*
typedef    VOID   (*INIT_FUN)();
typedef    VOID   (*FASTTIMO_FUN)();s
typedef    VOID   (*SLOWTIMO_FUN)();
typedef    VOID   (*DRAIN_FUN)();
*/
typedef LONG (*SYSCTL_FUN)(LONG *,ULONG,VOID *,ULONG *,VOID *,ULONG);


extern ULONG g_ulPSTCurrentIndex;   /* 当前协议开关表个数 */
extern ULONG g_ulMaxPSTNumbers;     /* 协议开关表数目上限 */

extern UCHAR g_szchIpProtoX_a[IPPROTO_MAX];  /* user protocol input function table */


extern PROTOSW_S stInetSw_a[];      /* protocol switch table,defined in in_proto.c */
extern DOMAIN_S  stInetDomain;      /* domain name table,defined in in_proto.c */

extern ULONG IP_PP4_RegProtocolSwitch(ULONG ulFlag, PROTOSW_S * pstRegPST);
extern ULONG IP_PP4_PmInitProtocol();
extern ULONG IP_RegisterDomain(DOMAIN_S * pDomain);


#endif  /* _PP4_PM_H_  */

#ifdef  __cplusplus
}
#endif

