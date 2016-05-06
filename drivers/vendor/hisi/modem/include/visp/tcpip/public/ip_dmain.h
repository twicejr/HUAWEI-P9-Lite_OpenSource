/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ip_dmain.h
*
*  Project Code: VISPV1R5
*   Module Name: Public  
*  Date Created: 2006-6-19
*        Author: X36317
*   Description: IP域定义的宏和结构体
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-6-19  X36317         Create the first version.
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _IP_DMAIN_H_
#define _IP_DMAIN_H_


#define SLOWTIMEOUT                             500
#define FASTTIMEOUT                             200


/**********************************************************************
* from ip_proto.h in vrp code
**********************************************************************/
struct tagDOMAIN;
struct tagSOCKET;
typedef struct tagPROTOSW
{
    /* Modified by X36317, 将此变量类型有short改为LONG，以解决ARM CPU四字节对齐问题, 2006/5/20 */
    LONG   pr_sType;              /* socket type used for */ 
    struct tagDOMAIN *pr_pDomain; /* domain protocol a member of */
    SHORT  pr_sProtocol;          /* protocol number */
    SHORT  pr_sFlags;             /* see below */

    /* protocol-protocol hooks */
    VOID   (*pr_pfInput)(MBUF_S *pRcvSeg, LONG);                               /* input to protocol (from below) */
    LONG   (*pr_pfOutput)(MBUF_S *,VOID *,VOID*,ULONG,VOID*);                  /* output to protocol (from above) */
    VOID   (*pr_pfCtlInput)(LONG,VOID *,VOID *);                               /* control input (from below) */
    LONG   (*pr_pfCtlOutput)(LONG,struct tagSOCKET *, LONG, LONG, MBUF_S **);  /* control output (from above) */

    /* user-protocol hook */
    LONG   (*pr_pfUsrReq)(struct tagSOCKET *, LONG, VOID *, VOID *, VOID *);   /* user request: see list below */

    /* utility hooks */
    VOID   (*pr_pfInit)();       /* initialization hook */
    VOID   (*pr_pfFastTimO)();   /* fast timeout (200ms) */
    VOID   (*pr_pfSlowTimO)();   /* slow timeout (500ms) */
    VOID   (*pr_pfDrain)();      /* flush any excess space possible */
    LONG   (*pr_pfSysCtl)(LONG *,ULONG,VOID *,ULONG *,VOID *,ULONG);           /* sysctl for protocol */
}PROTOSW_S;


typedef struct  tagDOMAIN
{
    int     dom_nFamily;            /* AF_xxx */
    CHAR    *dom_pName;
    VOID    (*dom_pfInit)(VOID);    /* initialize domain data structures */
    int     (*dom_pfExternalize)(MBUF_S *); /* externalize access rights */
    int     (*dom_pfDispose)(MBUF_S *);     /* dispose of internalized rights */
    struct tagPROTOSW   *dom_pProtoSw, *dom_pNextProtoSw;
    struct tagDOMAIN    *dom_pNext;
    int     (*dom_pfRtAttach)(VOID **, int);/* initialize routing table */
    int     dom_nRtOffset;          /* an arg to rtattach, in bits */
    int     dom_nMaxRtKey;          /* for routing layer */
}DOMAIN_S;


extern DOMAIN_S *g_pstDomains;

/*此宏用来增加域*/
#define ADDDOMAIN(x) \
{ \
    extern DOMAIN_S x; \
    x.dom_pNext = g_pstDomains; \
    g_pstDomains = &x; \
}

extern CHAR g_acVISPOuterVer[48];

/*  interface in ip_dmain.c  */
extern ULONG IP_AllInit();
extern PROTOSW_S *PF_FindType( LONG lFamily, LONG lType);
extern PROTOSW_S *PF_FindProto( LONG lFamily, LONG lProto, LONG lType);
extern LONG NET_SysCtl(LONG *plName, ULONG ulNameLen, VOID *pOld,
                       ULONG *pulOldLen, VOID *pNew, ULONG ultNewLen);
extern LONG SysCtl_int(VOID *a, ULONG *b, VOID *c, ULONG d, LONG *e);

ULONG TCPIP_GetCPUType(CHAR * pCPUType);
LONG TCPIP_GetVersion(CHAR *pVerInfo);

#endif  /* _IP_DMAIN_H_ */

#ifdef  __cplusplus
}
#endif


