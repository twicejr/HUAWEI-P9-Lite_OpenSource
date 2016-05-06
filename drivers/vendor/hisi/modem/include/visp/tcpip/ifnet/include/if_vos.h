/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         IF_VOS.H 
 *
 *  Project Code: VISP1.5
 *   Module Name: IFNET
 *  Date Created: 2004/04/28
 *        Author: luohanjun
 *   Description: 
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2004/04/28      luohanjun       Create File
 *  2006/03/30      liai            Adjust for D00654
 *  2006/04/21      liai            Adjust for D00878
 *  2007/09/20      luowentong 00105073 删除在产品工程目录(vos/vospubh)中没有的头文件
 ************************************************************************/
#ifndef _IF_VOS_H_
#define _IF_VOS_H_
     
#ifdef  __cplusplus
     extern "C"{
#endif

#include "vos/vospubh/basetype.h"

/* 2007-9-19由l00105073修改，问题单A82D20236：tcpip_ifnet.h包含的头文件有包含长路径*/
#include "vos/vospubh/vos_def.h"

/* #include "dopra/vos/include/v_typdef.h" */

#include "vos/vospubh/vos_id.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/vos_ker.h"
#include "vos/vospubh/vos_arg.h"
#include "vos/vospubh/vos_lib.h"

#include "vos/vospubh/vos_intr.h"
/* #include "vos/vosprih/vos_kerx.h" */

#include "vos/vospubh/mbuf.h"

#include "vos/vospubh/vos_util.h"
#include "vos/vospubh/utldll.h"
#include "vos/vospubh/utlsll.h"

#include "vos/vospubh/wlst_inc.h"

#include "vos/vospubh/ipc_inc.h"
#include "vos/vospubh/rpc_inc.h"

#include "vos/vospubh/vos_task.h"
#include "vos/vospubh/vos_que.h"

/* #if( VRP_MODULE_IFNET_EXT == VRP_YES ) */
/* 由l00105073修改，问题单A82D20236：tcpip_ifnet.h包含的头文件有包含长路径*/
#include "vos/vospubh/compbase.h"
#include "vos/vospubh/iunknown.h"
#include "vos/vospubh/icompfactory.h"
/* #endif */

#include "vos/vospubh/license.h"
/* #include "vos/vosregex/vos_regx.h" */ 
#include "vos/vospubh/paf.h"

/* #include "root/appinit.h" */
#include "public/entry/tcpip_entry.h"
#include "tcpip/public/tcpip_basefun.h"

#define CID_ROUT_RMIPV4                     CID_ROUT_BASE + 1

/* Interface IDs declration */
#define IID_ROUT_RMIPV4_INTF_RPM4           IID_ROUT_BASE + 10
#define IID_ROUT_RMIPV4_INTF_URT4           IID_ROUT_BASE + 11
#define IID_ROUT_RMIPV4_INTF_IM4            IID_ROUT_BASE + 12
#define IID_ROUT_RMIPV4_INTF_MSR            IID_ROUT_BASE + 13
#define IID_ROUT_RMIPV4_INTF_CFG4           IID_ROUT_BASE + 14
#define IID_ROUT_RMIPV4_INTF_RCOM4          IID_ROUT_BASE + 15


#define CID_MPLS_LSPM                ( CID_MPLS_BASE )

#define IID_MPLS_LSPM_INTF_PUB       ( IID_MPLS_BASE + 3 )

#define CID_ROUT_RMIPV6             CID_ROUT_BASE + 2

/* Interface IDs of IPV6 Component */
#define IID_ROUT_RMIPV6_INTF_URT6   IID_ROUT_BASE + 20
#define IID_ROUT_RMIPV6_INTF_IM6    IID_ROUT_BASE + 21
#define IID_ROUT_RMIPV6_INTF_RPM6   IID_ROUT_BASE + 22 
#define IID_ROUT_RMIPV6_INTF_CFG6   IID_ROUT_BASE + 23

#ifdef  __cplusplus
}
#endif

#endif

