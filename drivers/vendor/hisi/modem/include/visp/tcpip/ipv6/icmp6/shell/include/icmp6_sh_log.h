/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : icmp6_sh_log.h
  Version       : Initial Draft
  Author        : S.SenthilKumar
  Created       : 2007/01/21
  Last Modified :
  Version       :
  Description   : icmp6_sh_log.h header file
  Function List :
  History       :
*---------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  --------------------------------------------------------------------
* 2006-09-14   Alok       Updated for 14 Fly-Check rules adherence
*                         for IPBIRV1R2.IPv6
**********************************************************************
*/

#ifndef _icmp6_sh_log_H_
#define _icmp6_sh_log_H_


#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/
extern IPOS_IC_InfoAttr_S  g_astIcmp6_LogInfo[];
extern IPOS_IC_InfoAttr_S  g_astIcmp6_DbgInfo[];
extern CHAR *g_aszIP6Icmp6LogFmtStrs[];
extern CHAR *g_aszIP6Icmp6DbgFmtStrs[];
extern ULONG g_ulICMP6Mid;
extern ULONG g_ulICMP6MaxLogId;
extern ULONG g_ulICMP6MaxDbgId;
extern ULONG g_ulIP6ICMP6DebugFlag;
extern ULONG g_ulICMP6CliState;

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/
extern ULONG (*pfIP6Icmp6_SendInfo)(ULONG ulMID, ULONG ulFlag, ULONG ulIndex,
                                   VOID *pInfo, VOID *pInfoType, va_list arg);

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/
/* To remove L4 warning regarding unused function arguments */
#ifndef NO_USE
#define NO_USE(macro_var)     (VOID)(macro_var)
#endif

#define IP6_ICMP6_ENABLE_CLI           1
#define IP6_ICMP6_DISABLE_CLI          0

#ifdef __cplusplus
}
#endif/* end of __cplusplus */

#endif  /* end of _icmp6_sh_log_H_ */

