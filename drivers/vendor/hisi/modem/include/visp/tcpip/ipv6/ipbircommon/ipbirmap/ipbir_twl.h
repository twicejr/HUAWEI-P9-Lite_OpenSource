/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : ipbir_twl.h
  Version       : Initial Draft
  Author        : Shraddha70428
  Created       : 2007/11/27
  Last Modified :
  Description   : TWL APIs and datastructures to be used in IPBIR Compoents
  Function List :
  History       :
  1.Date        : 2007/11/27
    Author      : Shraddha70428
    Modification: Created file

******************************************************************************/


#ifndef __IPBIR_TWL_H__
#define __IPBIR_TWL_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#if (VRP_YES == TCPIP_IN_VRP)
#include "util/twl_api.h"               /* for IPOS map*/
#else
#include "ipbircommon/source/visp/include/twl_api.h"  /* for VISP map*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __IPBIR_TWL_H__ */
