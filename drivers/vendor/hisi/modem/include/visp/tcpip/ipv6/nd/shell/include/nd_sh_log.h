/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : nd_sh_log.h
  Version       : Initial Draft
  Author        : S.SenthilKumar
  Created Date  : 2007/01/21
  Last Modified :
  Description   : nd_sh_log.h header file
  Function List :
  History       :
******************************************************************************/

#ifndef _ND_SH_LOG_H
#define _ND_SH_LOG_H


#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/
extern IPOS_IC_InfoAttr_S  g_stND_LogInfo[];
extern IPOS_IC_InfoAttr_S  g_stND_DbgInfo[];
extern CHAR *g_pszIP6NDLogFmtStrs[];
extern CHAR *g_pszIP6NDDbgFmtStrs[];
extern const ULONG g_ulNDMaxLogID;
extern const ULONG g_ulNDMaxDbgID;
extern ULONG g_ulNDMid;

/* extern ULONG g_ulNDDebugFlag; */
extern ULONG g_ulNDCliState;

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/
extern ULONG (*pfIP6ND_SendInfo)(ULONG ulMID, ULONG ulFlag, ULONG ulIndex,
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
#define     NO_USE(var)     (VOID)(var)
#endif

#define IP6_ND_ENABLE_CLI     1
#define IP6_ND_DISABLE_CLI    0

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/

#ifdef __cplusplus
}
#endif/* end of __cplusplus */

#endif  /* end of _ND_SH_LOG_H */
