/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              iraw_ip.h
*
*  Project Code: VISP1.5
*   Module Name: RawIP4
*  Date Created: 2003-06-23
*        Author: Sunil Dutt
*   Description: To define RawIP4 component interfaces 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2003-06-23  Sunil Dutt       Create the first version.
*  2006-04-27  luyao            根据编程规范，对文件进行规范化整理
*
*******************************************************************************/

#ifndef _IRAW_IP_H_
#define _IRAW_IP_H_

#ifdef  __cplusplus
extern "C"{
#endif


struct tagMBuf;
struct tagROUTE;
struct tagRIP4_MOD_INFO;
struct tagRIPSTAT;
struct tagSOCKET;


/* the configure interfaces provided by the component. */
DECLARE_INTERFACE( IIF_IP4_RIP4_ComIntCfg)
{
    IUNKNOWN_METHODS
    
    METHOD_(ULONG,pfRIP4_Init_Com) (COM_ID_INFO_S *pComInfo, ULONG ulComLen);
    METHOD_(ULONG,pfRIP4_Activate_Com)();
    METHOD_(ULONG,pfRIP4_SetModuleInfo) (struct  tagRIP4_MOD_INFO *pMInfo);
    METHOD_(ULONG,pfRIP4_ResetStatistics) (VOID);
    METHOD_(ULONG,pfRIP4_GetStatistics) (struct tagRIPSTAT *pstRipStats);
    METHOD_(ULONG,pfRAWIP_GetPerRawip4ConnStats)(struct tagRAWIP4CONN_S *pstConnInfo, struct tagRAWIP4PERSTAT_S  *pstRetStats);
    METHOD_(ULONG,pfRAWIP_ResetPerRawip4ConnStats)(struct tagRAWIP4CONN_S *pstConnInfo);    
};


/* the functional interfaces provided by the component. */
DECLARE_INTERFACE( IIF_IP4_RIP4_ComIntFun)
{
    IUNKNOWN_METHODS

    METHOD_(VOID,pfRIP4_Input) ( struct tagMBuf *ppstMBuf);
    METHOD_(LONG,pfRIP4_Output)( struct tagMBuf *pMBuf, VOID *pSock,VOID* xxx1,ULONG ulDst,VOID* xxx2);
    METHOD_(LONG,pfRIP4_CtlOutput)(LONG lOper, VOID *pSock,LONG lLevel, LONG lOptName, struct tagMBuf **ppMBuf);
    METHOD_(LONG,pfRIP4_Usrreq)(struct tagSOCKET * pSock, LONG lReq,struct tagMBuf * pstMBuf, 
                                struct tagMBuf * pstMName, struct tagMBuf * pstMCtl);
};


typedef struct tagRIP4_INT_OBJ
{
    struct IIF_IP4_RIP4_ComIntCfg * pstIComInt_RIP4_Cfg;
    struct IIF_IP4_RIP4_ComIntFun * pstIComInt_RIP4_Fun;

} RIP4_INT_OBJ_S;

extern RIP4_INT_OBJ_S g_stIPV4_RIP_INT_OBJ; /*RawIP4组件的初始化对象,供实现组件使用*/


#ifdef  __cplusplus
}
#endif

#endif /* __IRAW_IP6__ */


