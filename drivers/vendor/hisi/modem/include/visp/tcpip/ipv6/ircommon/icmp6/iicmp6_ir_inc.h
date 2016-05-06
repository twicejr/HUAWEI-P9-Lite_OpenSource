/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : iicmp6_ir_inc.h
  Version       : Initial Draft
  Author        : Saravanya71677
  Created       : 2007/12/12
  Last Modified :
  Description   : iicmp6_ir_inc.h header file
  Function List :
  History       :
  1.Date        : 2007/12/12
    Author      : Saravanya71677
    Modification: Created file

******************************************************************************/

#ifndef __IICMP6_IR_INC_H__
#define __IICMP6_IR_INC_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "common/ipos/ipv6/basic/icmp6/iicmp6_inc.h"

/* Interface IDs declaration */
#define IID_IP6_ICMP6_IR_FUN       (IID_IPV6_BASE + 16)

/**********************
   Function VTable
***********************/

/* ICMP6 Function VTable Structure - Level 2 */
DECLARE_INTERFACE (IIF_IP6_ICMP6_IR_FUN)
{
    IUNKNOWN_METHODS
    METHOD_ (ULONG, pfIP6_ICMP6_ICMP6InfoInit) (VOID *pvIP6Ifnet);
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __IICMP6_IR_INC_H__ */

