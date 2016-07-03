

#ifndef _MP_SH_EXT_H_
#define _MP_SH_EXT_H_

#ifdef  __cplusplus
extern "C"{
#endif

extern ULONG IF_GetVTIndexByNumber( ULONG ulVirtualTemplateNum );
extern ULONG IF_GetSlotByIndex(ULONG ulIfIndex);
extern IFNET_S * IF_GetIfByFullName(CHAR * szFull);

extern IFNET_S* IF_CreateMpVirtualAccess( ULONG ulVTIndex, CHAR *pcData, ULONG ulDataLen );
extern ULONG IF_EnDropQueue(MBUF_S *);
extern ULONG IF_BoardIsUp( ULONG ulSlot );

/* IFNETº¯Êý */
extern IFNET_S* IF_CreateVirtualAccess(ULONG ulVTIndex, ULONG ulEthIndex, USHORT usSectionID, UCHAR* pucMAC );
extern ULONG IF_BeforeEncap( IFNET_S *pIf , ULONG *ulShutdown, ULONG ulExecID, ULONG ulNewProtocol );
extern ULONG IF_AfterEncap( IFNET_S *pIf , ULONG ulShutdown );
extern CHAR *VirtualTemplateName;
extern ULONG  gulMaxBoardNum;
extern IFNET_S *IF_SearchIfFromChain( IFNET_S *pIf , ULONG ulSearch );
extern IFNET_S* IF_GetConfigHead(VOID);
extern LONG IF_JudgeNameOrder (CHAR *Sour,CHAR *if_pName);
extern ULONG getMainboardId(VOID);
extern ULONG getSelfBoardId(VOID);

/* VOS º¯Êý */
extern VOS_UINT32 VOS_T_GetSelfID( VOS_UINT32 * pulTaskID );


#ifdef  __cplusplus
}
#endif

#endif  /* end of _MP_SH_EXT_H_ */
