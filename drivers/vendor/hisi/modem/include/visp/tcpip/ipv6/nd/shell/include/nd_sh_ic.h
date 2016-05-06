/******************************************************************************
*
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*
*------------------------------------------------------------------------------
*    Project Code   : VRP5.0
*    Module Name    : IP6 ND
*    Version        : Initial Draft
*    File Name      : ND_SH_IC.H
*    Create Date    : 2003/06/25
*    Author         : Santosh G Kulkarni
*    Description    : the IC interface module of ND
*------------------------------------------------------------------------------
*  Modification History
*
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2003-06-25  Santosh G Kulkarni     Create
*******************************************************************************/
#ifndef _ND_SH_IC_H
#define _ND_SH_IC_H

#ifdef    __cplusplus
extern "C"{
#endif

#define BUFFER  0x307

LONG IP6_ND_SH_DebugAll(void);

LONG IP6_ND_SH_NoDebugAll(void);

ULONG  IP6_ND_SH_Reg2IC(VOID);

ULONG IP6_ND_SH_SendNDMSGDebugInfoToIC(const IN6ADDR_S *pstAddress,
       ULONG ulIfIndex,
       ULONG ulMsgType, ULONG ulType);

ULONG IP6_ND_SH_SendPrefixDebugInfoToIC(const IN6ADDR_S *pstPrefix,
                                  ULONG ulPrefixLen,
                                  ULONG ulLFlag, ULONG ulAFlag);

ULONG IP6_ND_SH_SendNBEntryDebugInfoToIC(const IN6ADDR_S *pstAddress,
        ULONG ulIfIndex, ULONG ulOldState, ULONG ulNewState,
        ULONG ulType);

extern CHAR * inet_ntop6(const CHAR *pSrcAddr,CHAR *pszDstAddr,
                            ULONG ulAddrLen);


ULONG IP6_ND_SH_SendInfoStrToIC (ULONG ulLogType, const CHAR *pszInfo);

/* Log and Debug String ID Encoding */
#define IP6_ND_LOGID_DEF(LogId) IC_INFOID_DEF(MID_ND, IC_INFO_LOG, LogId)
#define IP6_ND_DBGID_DEF(DbgId) IC_INFOID_DEF(MID_ND, IC_INFO_DEBUG, DbgId)

extern ULONG (*pfIP6ND_SendInfo)(ULONG ulMID, ULONG ulFlag, ULONG ulIndex,
                          VOID *pInfo, VOID *pInfoType, va_list arg);

extern LONG (*pfIP6ND_IC_RegInfo)(CHAR *szModuName,
                           IPOS_IC_InfoAttr_S* pstInfoAttrArray,
                           ULONG ulInfoNum);

#ifdef    __cplusplus
}

#endif    /* end of __cplusplus */

#endif    /* end of _ND_SH_IC_H_ */

