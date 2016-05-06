/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              ipbir_visp_inf_map.h
*
*    Project Code:  IPOS IR V1R2
*    Version     :  Initial Draft
*    Module Name :  IPB IR
*    Create Date :  2007/12/05
*    Author      :  IPv6 Team
*    Description :  To include Common component specific header files
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*-----------------------------------------------------------------------
*
*
************************************************************************/

#ifndef _IPBIR_VISP_INF_MAP_H_
#define _IPBIR_VISP_INF_MAP_H_

/* -------------------------------------------------------------------------- */
/* Include Product Header files - Based on the selected Product */
#if (IPB_IR_PRODUCT_TYPE == IPB_IR_PRODUCT_VISP)

#include "ipbircommon/ipbirmap/visp/visp/ipbir_visp_inf.h"

#elif (IPB_IR_PRODUCT_TYPE == IPB_IR_PRODUCT_NODE_B)

#include "ipbircommon/ipbirmap/visp/nodeb/ipbir_nodeb_inf.h"

#else /* Unknown product */

/* Unknown product */
#error Unknown Product, Please select a product in ipbir_product.h and build

#endif

#endif  /* end of _IPBIR_VISP_INF_MAP_H_ */
