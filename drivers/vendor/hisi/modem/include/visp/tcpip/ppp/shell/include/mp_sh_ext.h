/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                               mp_sh_ext.h
 *
 *  Project Code: VISP1.5
 *   Module Name: MP
 *  Date Created: 2005-09-28
 *        Author: songrujie
 *   Description: MP模块引用其他模块的函数接口申明和
 *                外部变量申明私有全局变量的引用说明
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2005-09-28      songrujie       Create
 *  2006-03-31      ZhuKun          Adjust for D00663
 *  2006-04-21      ZhuKun          Adjust for D00876
 *  2006-05-13      l48923          Delete useless code
 *
 *************************************************************************/

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

/* IFNET函数 */
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

/* VOS 函数 */
extern VOS_UINT32 VOS_T_GetSelfID( VOS_UINT32 * pulTaskID );


#ifdef  __cplusplus
}
#endif

#endif  /* end of _MP_SH_EXT_H_ */
