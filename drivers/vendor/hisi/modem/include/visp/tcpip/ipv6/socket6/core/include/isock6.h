/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              isock6.h
*
*  Project Code: VISP1.5
*   Module Name: Socket6
*  Date Created: 2006-4-29
*        Author: luyao(60000758)
*   Description: Vtable definitions for FIBContainer component interfaces
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-4-29   luyao(60000758)  Creat the first version.
*  2006-04-27  luyao            根据编程规范，对文件进行规范化整理
*
*******************************************************************************/

#ifndef _ISOCK6_H_
#define _ISOCK6_H_

#ifdef __cplusplus
extern "C"{
#endif

struct tagSOCKADDR;
struct tagIN6Addr;
struct tagSOCKADDR_IN6;
struct tagSOCKHOST;
struct tagSOCKET;
struct tagIN6PCB;
struct tagIP6_S;
struct tagSOCK_MOD_INFO_S;
struct tagIP_SOCK_SH_CALLBACUP_SET_S;
struct tagSOCKDBUGFILTRD;
struct tagUIO;

DECLARE_INTERFACE( IIF_IP6_SOCK_ComIntCFG)
{
        IUNKNOWN_METHODS
            
        METHOD_ (ULONG,pfSOCK6_Init_Com) (const COM_ID_INFO_S *pComInfo, ULONG ulComLen);
        METHOD_ (ULONG,pfSOCK6_Activate_Com)();
        METHOD_ (ULONG,pfSOCK6_Set_Module_Info)(struct tagSOCK_MOD_INFO_S * pstMInfo);
        METHOD_ (ULONG,pfSOCK6_RegisterAll)(struct tagIP_SOCK_SH_CALLBACUP_SET_S * pfCallBackSet);
        
        METHOD_ (USHORT,pfSOCK6_AddHost)(CHAR * stHostName, CHAR * stHostIP);
        METHOD_ (USHORT,pfSOCK6_DelHost)(LONG lKind,CHAR *stHostName, CHAR *stHostIP);
        METHOD_ (LONG,pfSOCK6_GetHost)(ULONG ulIndex , struct tagSOCKHOST **ppHost);

        METHOD_ (LONG,pfSOCK6_GetSock)(ULONG ulTaskId,LONG iFd,struct tagSOCKET **ppSocket);
    
        METHOD_ (ULONG,pfSOCK6_OpenObject)(ULONG ulMainType, UINTPTR * pulHandle);
        METHOD_ (ULONG,pfSOCK6_CloseObject)(UINTPTR  ulHandle);
        METHOD_ (LONG,pfSOCK6_Get_Object_First)(UINTPTR ulHandle, ULONG ulSocketType,struct tagIN6PCB **ppReturnInPCB);
        METHOD_ (LONG,pfSOCK6_Get_Object_Next)(UINTPTR ulHandle,ULONG ulSocketType,struct tagIN6PCB *pCurrentInPCB, struct tagIN6PCB **ppReturnInPCB);
        
        METHOD_ (LONG,pfSOCK6_DebugAll)( VOID );
        METHOD_ (LONG,pfSOCK6_NoDebugAll)( VOID );
        METHOD_ (LONG,pfSOCK6_ShowDebugging)( CHAR *szStatusStr,ULONG ulMaxLen ,ULONG ulDebugIndx,UINTPTR *pulWaitlistHandle,ULONG ulInterface);
        METHOD_(ULONG,pfSOCK_ProIp6DbugFilter)(ULONG ulFlag, struct tagSOCKDBUGFILTRD *pstDbugFiltRd, ULONG ulTaskId, ULONG ulSockId);
};


DECLARE_INTERFACE( IIF_IP6_SOCK_ComIntFUN)
{
        IUNKNOWN_METHODS
        METHOD_(CHAR * ,pfinet_ntop6)(const CHAR *pSrcAddr,CHAR *pszDstAddr,ULONG ulAddrLen);
        METHOD_(LONG ,pfinet_pton6)(const CHAR *szSrcAddr, VOID *pDstAddr);
        METHOD_(VOID * ,pfIN6PCB_GetNextPCB)(VOID *pParam,VOID **pNewParam);
        METHOD_(ULONG ,pfSOCK6_GetDebugFlag)();
        METHOD_(SOCKDBUGFILTRD_S * ,pfSOCK6_GetFilter)();
        METHOD_(struct hostent * ,pfgethostbyname6)(CHAR *pName, ULONG ulPolicy);
        METHOD_(struct hostent * ,pfgethostbyaddr6)(CHAR *pAddr,LONG iLen,LONG iType);
        
        METHOD_(ULONG, pfHeadCache6_GetSingleInfo)(ULONG ulTaskId, LONG iFd, IN6ADDR_S* pstDstAddr6, USHORT usDstPort, 
                                            struct tag_HeadCache *pstEntry);
	    METHOD_(ULONG, pfHeadCache6_LookUpSrcAddr)(SOCKET_S *pSocket, IN6ADDR_S *pstDstAddr, USHORT usDstPort, 
                                              IN6ADDR_S *pstSrcAddr, USHORT *pusSrcPort);
        METHOD_(LONG, pfHeadCache6_SendData)(SOCKET_S *pSocket, struct tagUIO *pUio, UINTPTR*pulEntryAddr);
};



typedef struct tagIPV6_SOCK_INT_OBJ_S
{
    struct IIF_IP6_SOCK_ComIntCFG * g_IComInt_SOCK6_CFG;
    struct IIF_IP6_SOCK_ComIntFUN * g_IComInt_SOCK6_FUN;
} IPV6_SOCK_INT_OBJ_S;


#define IP6_SOCK_EXT_COMIF_CNT  8 


#ifdef __cplusplus
}
#endif

#endif

