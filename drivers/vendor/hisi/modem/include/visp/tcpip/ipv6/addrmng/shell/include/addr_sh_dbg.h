/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : addr_sh_dbg.h
  Version       : IPBIRV100R003.IPv6.E001
  Author        : KLSrini
  Created       : 2006/12/4
  Last Modified :
  Description   : addr_sh_dbg.h header file
  Function List :
  History       :
  1.Date        : 2006/12/4
    Author      : KLSrini
    Modification: Created file for AC4D01246
    Problem Number: AC4D01246     Author:KLSrini,   Date:2006/12/4
    Description   :  Exception with router restart when change Controller
                    interface mode with IPv6 debug
******************************************************************************/

#ifndef _ADDR_SH_DBG_H_
#define _ADDR_SH_DBG_H_


#ifdef __cplusplus
extern "C" {
#endif

#ifndef LEN_1024
#define LEN_1024 1024
#endif
#ifndef LEN_64
#define LEN_64   64
#endif

#define ADDR_MAX_LOG_LEN    255
#define IP6_ADDR_SH_DBG     (VOID) IP6_Addr_SH_DbgToIPOSIC
#define ADDR6_DBGID_DBG     0

VOID IP6_SH_Log_Text(CHAR *pMessage, ...);
extern ULONG VOS_strlen(const CHAR *Str); /*Changed by wan for VISPV1R7 integration*/
ULONG IP6_Addr_SH_DbgToIPOSIC(ULONG ulDbgID, ...);

#ifdef __cplusplus
}
#endif/* end of __cplusplus */

#endif  /* end of _ADDR_SH_DBG_H_ */

