/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_acl4.h
*
*  Project Code: VISPV1R6
*   Module Name: ACL4  
*  Date Created: 2007-8-17
*        Author: X36317
*   Description: ACL4模块为外部模块提供的头文件集
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2007-8-17  X36317            Create the first version.
*  2008-09-10   liangjicheng          V1R7C02 同步V1R7C01  
*
*******************************************************************************/

#ifndef _TCPIP_ACL4_H_
#define _TCPIP_ACL4_H_

#ifdef __cplusplus
extern "C"{
#endif

//#include "tcpip/public/tcpip_config.h"

//#include "acl4/include/acl_inc.h" 
#include "acl/shell/include/fw_acl_sh.h"
//#include "acl4/include/acl_api.h"
#include "public/entry/tcpip_entry.h"

 /*Begin 2008-09-10 V1R7C02 同步V1R7C01*/
#include "acl/shell/include/fw_acl_ppi.h"
 /*End    2008-09-10 V1R7C02 同步V1R7C01*/

#ifdef __cplusplus
}
#endif      /* end of __cplusplus       */

#endif      /* end of _TCPIP_ACL4_H_    */

