/*************************************************************************
 *
 *              Copyright 2009, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 *
 *-----------------------------------------------------------------------*
 *
 *                              acl6_inc.h
 *
 *  Project Code: VISP1.8
 *   Module Name: ACL6
 *  Date Created:
 *        Author:
 *   Description: 提供acl6模块主要头文件的包含
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *
 ************************************************************************/
#ifndef _ACL6_INC_H_
#define _ACL6_INC_H_

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef TCPIP_MODULE_BEMINI
#define TCPIP_MODULE_MINI        VRP_YES
#else
#define TCPIP_MODULE_MINI        VRP_NO
#endif

#include "vos/vospubh/basetype.h"
#include "vos/vospubh/vos_util.h"
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/vos_ker.h"
#include "vos/vospubh/mbuf.h"
#include "vos/vospubh/compbase.h"

#include "acl6/include/acl6_api.h"
#include "acl6/shell/include/acl6_ppi.h"

#include "acl6/include/acl6_def.h"
#include "acl6/include/acl6_pub.h"
#include "acl6/include/acl6_cbb_api.h"
#include "acl6/include/acl6_func.h"
#include "acl6/include/acl6_var.h"
#include "acl6/include/aclfw6_api.h"
#include "acl6/include/aclfw6_internal.h"
#include "acl6/shell/include/acl6_sh.h"

#include "tcpip/public/tcpip_log.h"
#include "tcpip/public/tcpip_basefun.h"

#ifdef  __cplusplus
}
#endif

#endif
