/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                               mp_sh_init.h
 *
 *  Project Code: VISP1.5
 *   Module Name: MP
 *  Date Created: 2005-09-08
 *        Author: yaochengliang
 *   Description: MP Shell intial include functions declare
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2005-09-08      y36299          Create
 *  2006-03-31      ZhuKun          Adjust for D00663
 *  2006-04-21      ZhuKun          Adjust for D00876
 *
 *************************************************************************/

#ifndef _MP_SH_INIT_H
#define _MP_SH_INIT_H

#ifdef  __cplusplus
extern  "C"{
#endif


ULONG MP_SH_Init();
ULONG MP_SH_DeInit();
ULONG MP_DDR_GetFatherIfIndex(IFNET_S *pstIfnet);
VOID  MP_DDR_ResetIdleTimeout(IFNET_S *pstSonIf);
ULONG MP_DDR_IoCtl(IFNET_S * pstIf, ULONG sCommand, CHAR * pszDataLink);
ULONG MP_QUE_EnDropQue(MBUF_S *pMBuf);

extern VOID PPP_ShowDebugInfo( char *szString, ULONG ulLen);

extern struct ComponentInfo m_CompMPInfo;

#ifdef  __cplusplus
}
#endif

#endif/*#ifndef _MP_SH_INIT_H*/

