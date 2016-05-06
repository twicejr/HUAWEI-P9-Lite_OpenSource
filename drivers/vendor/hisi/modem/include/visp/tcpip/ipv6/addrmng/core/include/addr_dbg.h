/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : addr_dbg.h
  Version       : IPBIRV100R003.IPv6.E001
  Author        : S.SenthilKumar
  Created       : 2007/01/21
  Last Modified :
  Description   : addr_dbg.h header file
  Function List :
  History       :
  1.Date        : 2007/01/21
    Author      : S.SenthilKumar
    Modification: Created file
******************************************************************************/

#ifndef _ADDR_DBG_H_
#define _ADDR_DBG_H_

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/
extern ULONG VOS_strlen(const CHAR * Str);  /*Changed by wan for VISPV1R7 integration*/
extern ULONG IP6_ADDR6_Send_Log_Text(CHAR *pMessage);

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
/* Added for IPv6 Log Information */
#define ADDR_MAX_LOG_LEN    255

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _ADDR_DBG_H_ */

