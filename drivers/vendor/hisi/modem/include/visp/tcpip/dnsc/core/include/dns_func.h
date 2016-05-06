/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dns_func.h
*
*  Project Code: VISP1.5
*   Module Name: DNSC Module  
*  Date Created: 2002-11-25
*        Author: Sun Yanfeng(32084)
*   Description: 声明DNS的外部接口和本地查询类函数 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2002-11-25  Sun Yanfeng(32084)         Creat the first version.
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif
#ifndef _I_DNSC_FUNC_H_
#define _I_DNSC_FUNC_H_

IP6_PKTINFO_S *DNSC_Get_RcvPktInfo(msghdr * pstRecvMsg);
LONG dnsc_getid(void);
LONG DNSC_gethostbyname4(CHAR *name, struct hostenthw *hp,LONG laddr_type);
VOID DNSC_iniRes_taskid(LONG staskid);
hostentdns_s *DNSC_gethostbyname2(CHAR *name, LONG af, LONG taskid);
LONG DNSC_res_send(UCHAR *buf, ULONG buflen, UCHAR **ppucAnsBuf, LONG *pAnsBufSiz, 
    ULONG taskid, LONG ltype, CHAR *name);
LONG DNSC_res_tcp_send(UCHAR *buf, ULONG buflen, UCHAR **ppucAnsBuf, LONG *pAnsSiz, ULONG taskid, ULONG ulSendServNum, fd_set *pdsmask);
LONG DNSC_res_tcp6_send(UCHAR *buf, ULONG buflen, UCHAR **ppucAnsBuf, LONG *pAnsSiz, ULONG taskid, ULONG ulSendServNum, fd_set *pdsmask);
LONG DNSC_res_queriesmatch(UCHAR *buf1, UCHAR *eom1, UCHAR *buf2, UCHAR *eom2);
LONG DNSC_res_nameinquery(CHAR *name,  LONG type, LONG lclass,
                    UCHAR *buf, UCHAR *eom);

LONG DNSC_res_isourserver(struct sockaddr_in *inp, LONG taskid,ULONG ul_IfIndex);
LONG DNSC_res_mkquery(LONG op, CHAR *dname, LONG lclass, LONG type, UCHAR *data, LONG datalen, UCHAR *newrr_in, UCHAR *buf, LONG buflen, LONG taskid);
void DNSC_putlong( ULONG l,  UCHAR *msgp);
VOID DNSC_putshort( USHORT s,  UCHAR *msgp);
LONG dnsc_find(UCHAR *exp_dn, UCHAR *msg, UCHAR **dnptrs, UCHAR **lastdnptr);
LONG dnsc_mklower(LONG ch);
LONG dnsc_comp(const CHAR *exp_dn, UCHAR *comp_dn, LONG length, UCHAR **dnptrs, UCHAR **lastdnptr);
LONG dnsc_expand(const UCHAR *msg, const UCHAR *eomorig, const UCHAR *comp_dn, CHAR *exp_dn, LONG length);
LONG DNSC_res_querydomain(CHAR *name, CHAR *domain, LONG lclass, LONG type, UCHAR **ppucAnsBuf, LONG *panslen, LONG taskid);
LONG DNSC_res_search(CHAR *name, LONG lclass, LONG type, UCHAR **ppucAnsBuf, LONG anslen, LONG taskid);
LONG DNSC_res_query(CHAR *name, LONG lclass, LONG type, UCHAR **ppucAnsBuf, LONG *anslen, LONG taskid);
VOID DNSC_res_close(LONG taskid);
ULONG DNSC_GetIfIndexByName(CHAR *szIntfName);
ULONG DNSC_FillSendPktInfo (IP6_PKTINFO_S *stPktInfo, ULONG ulIfIndex);

/* syn D038 by x36530 20050715*/

extern struct hostent *DNSC_GetHost( CHAR *pName,LONG laddrtype, ULONG ulPolicy );
/*end of modification*/


struct hostent *DNSC_Res_SearchLocal(CHAR *pName,LONG laddrtype);

struct hostent *DNSC_Res_SearchEntry(CHAR *pszName,LONG laddrtype);

VOID  DNSC_Sock_TimeCallBack(VOID *pArg);
ULONG  DNSC_Cache_Refresh(hostenthw_s *pstDNSHostTent);
ULONG DNSC_Cache_Clear(ULONG ulProtocolFlag);
hostentdns_s *DNSC_AnalyAnswer(UCHAR *pucAnsBuf, ULONG ulAnsLen, char *pszQuerName, ULONG ulQueType, 
                                                            ULONG ulTaskId);
ULONG DNSC_HostName_Check( CHAR  *pszDomainName);

ULONG DNSC_Getlong(UCHAR *msgp);
USHORT DNSC_Getshort(UCHAR *msgp);

ULONG DNS_GetSrcIPByServerIP(ULONG ulDnsServerIP);

UINT32 DNS_IsUnderscore(LONG ch);

#endif
#ifdef  __cplusplus
}
#endif


