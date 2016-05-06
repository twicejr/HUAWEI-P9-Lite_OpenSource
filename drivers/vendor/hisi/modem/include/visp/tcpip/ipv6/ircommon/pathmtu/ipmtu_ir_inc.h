/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : ipmtu_ir_inc.h
  Version       : Initial Draft
  Author        : Sandeep71635
  Created       : 2007/12/14
  Last Modified :
  Description   : PMTU interfaces exposed to IR components
  Function List :
  History       :
  1.Date        : 2007/12/14
    Author      : Sandeep71635
    Modification: Created file

******************************************************************************/
#ifndef __IPMTU_IR_INC_H__
#define __IPMTU_IR_INC_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "common/ipos/ipv6/basic/pathmtu/ipmtu_inc.h"
#include "ipv6/ircommon/pathmtu/pmtu_ir_pub.h"

/* Interface IDs declration */
#define IID_IP6_PMTU_IR_FUN               101

/*Declaration of IR FUN interface*/
DECLARE_INTERFACE(IIF_IP6_PMTU_IR_FUN)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIP6_PMTU_ICMP_Input)(IP6_CTLPARAM_S *pstTooBigNotify);
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __IPMTU_IR_INC_H__ */
