/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : addr_sh_log.h
  Version       : IPBIRV100R003.IPv6.E001
  Author        : S.SenthilKumar
  Created       : 2007/01/21
  Last Modified :
  Description   : addr_sh_log.h header file
  Function List :
  History       :
  DATE        NAME             DESCRIPTION
******************************************************************************/

#ifndef _ADDR_SH_LOG_H_
#define _ADDR_SH_LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/
extern IPOS_IC_InfoAttr_S  g_stAddr_LogInfo[];
extern IPOS_IC_InfoAttr_S  g_stAddr_DbgInfo[];
extern CHAR  *g_pszIP6AddrLogFmtStrs[];
extern CHAR  *g_pszIP6AddrDbgFmtStrs[];
extern const ULONG g_ulAddrMaxLogId;
extern const ULONG g_ulAddrMaxDbgId;
extern const ULONG g_ulAddrMid;

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/
extern ULONG (*pfIP6Addr_SendInfo)(ULONG ulMID, ULONG ulFlag, ULONG ulIndex,
                                   VOID *pInfo, VOID *pInfoType, va_list arg);

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/

/*----------------------------------------------*
 * module-wide global variables                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * constants                                    *
 *----------------------------------------------*/

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/
#ifndef NO_USE
#define NO_USE(var)     (VOID)(var)
#endif

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/

#ifdef __cplusplus
}
#endif/* end of __cplusplus */

#endif  /* end of _ADDR_SH_LOG_H_ */
