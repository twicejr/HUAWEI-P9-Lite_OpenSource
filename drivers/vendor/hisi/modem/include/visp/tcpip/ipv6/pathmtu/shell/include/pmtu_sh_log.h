/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : pmtu_sh_log.h
  Version       : Initial Draft
  Author        : S.SenthilKumar
  Create date   : 2007/01/21
  Last Modified :
  Description   : pmtu_sh_log.h header file
  Function List :
  History       :
******************************************************************************/

#ifndef _pmtu_sh_log_H_
#define _pmtu_sh_log_H_


#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/
extern IPOS_IC_InfoAttr_S  g_stPmtu_LogInfo[];
extern IPOS_IC_InfoAttr_S  g_stPmtu_DbgInfo[];
extern CHAR *g_pszIP6PmtuLogFmtStrs[];
extern CHAR *g_pszIP6PmtuDbgFmtStrs[];
extern const ULONG g_ulPmtuMaxLogId;
extern const ULONG g_ulPmtuMaxDbgId;
extern const ULONG g_ulPmtuMid;

extern ULONG g_ulIP6PMTUDebugFlag;
extern ULONG g_ulPMTUCliState;

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/
extern ULONG (*pfIP6Pmtu_SendInfo)(ULONG ulMID, ULONG ulFlag, ULONG ulIndex,
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

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/


#ifndef NO_USE
#define     NO_USE(var)     (VOID)(var)
#endif

/* For CLI enable and Disable.*/
#define IP6_PMTU_ENABLE_CLI     1
#define IP6_PMTU_DISABLE_CLI    0

#ifdef __cplusplus
}
#endif/* end of __cplusplus */

#endif  /* end of _pmtu_sh_log_H_ */
