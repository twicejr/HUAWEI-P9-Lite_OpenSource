/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : ppp_inc.h
  版 本 号   : 初稿
  作    者   : h50774
  生成日期   : 2012年4月16日
  最近修改   :
  功能描述   : 头文件引用封装
  函数列表   :
  修改历史   :
  1.日    期   : 2012年4月16日
    作    者   : h50774
    修改内容   : 创建文件

******************************************************************************/

#ifndef __PPP_INC_H__
#define __PPP_INC_H__

#include "vos.h"
#include "v_lib.h"
#include "v_typdef.h"
#include "v_msg.h"
#include "vrpcfg.h"
#include "PsTypeDef.h"

#include "PsCommonDef.h"

#include "sm_simulator_mbuf.h"
#include "ppp_am_public.h"

#include "ppp_def.h"
#include "ppp_type.h"
#include "ppp_dbug.h"
#include "ppp_init.h"
#include "ppp_comp.h"
#include "ppp_task.h"

#include "ppp_perf.h"

#include "lcp_type.h"
#include "lcp_func.h"
#include "lcp_def.h"

#include "ipcp_typ.h"
#include "ipcp_fun.h"
#include "ipcp_def.h"

#include "pap_def.h"
#include "pap_type.h"
#include "pap_func.h"
#include "pap_dbg.h"

#include "chap_def.h"
#include "chap_typ.h"
#include "chap_fun.h"




#if (VRP_MODULE_LINK_PPP_CCP == VRP_YES)

#include "stac_pub.h"
#include "stac_inc.h"

#include "stac_def.h"
#include "stac_typ.h"
#include "stac_fun.h"

#include "mppc_pub.h"
#include "mppc_inc.h"

#include "mppc_def.h"
#include "mppc_typ.h"
#include "mppc_fun.h"
#endif

#include "ccp_type.h"
#include "ccp_func.h"
#include "ccp_def.h"

#include "pppc_eap_def.h"
#include "pppc_eap_typ.h"
#include "pppc_eap_fun.h"

#include "ipv6cp_typ.h"
#include "ipv6cp_fun.h"
#include "ipv6cp_def.h"
#include "vsncp_def.h"

#include "ppp_var.h"
#include "ppp_func.h"
#include "ppp_cmp_public.h"


#endif /* __PPP_INC_H__ */
