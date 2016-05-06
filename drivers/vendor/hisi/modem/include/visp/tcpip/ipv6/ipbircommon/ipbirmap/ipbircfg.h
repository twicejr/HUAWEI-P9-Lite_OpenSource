/************************************************************************
 *                                                                      *
 *                             IPBIRCFG.H                                *
 *                                                                      *
 *  Project Code:       IPBIRV1R2                                       *
 *  Create Date:                                            *
 *  Author:                                               *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:                                                           *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *             Copyright 2000 - 2011 HuaWei Tech, Inc.                  *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 ************************************************************************/

#ifndef _IPBIRCFG_H
#define _IPBIRCFG_H

#ifdef  __cplusplus
extern "C"{
#endif

/* This file currently is same as iposircfg.h, but we still include this file
instead of iposircfg.h, as we dont change in our c file to cater to VISP or
IPOS , for any future changes done in iposircfg.h */

//#define ARM_SUPPORT              VRP_NO  /* Modified by Arvind for ND Host Integ */

#define PRODUCT_TYPE_AP_NODEB               1
#define PRODUCT_TYPE_WVISP_V1               2
#define PRODUCT_TYPE_WVISP_V2               3
#define PRODUCT_TYPE_WVISP_V1V2             4
#define PRODUCT_TYPE_NODEB_V1               5
#define PRODUCT_TYPE_NODEB_V2               6
#define PRODUCT_TYPE_NODEB_V1V2             7
#define PRODUCT_TYPE_TRAN_WVISP_V1          8
#define PRODUCT_TYPE_TRAN_WVISP_V2          9
#define PRODUCT_TYPE_TRAN_WVISP_V1V2        10
#define PRODUCT_TYPE_TRAN_NODEB_V1          11
#define PRODUCT_TYPE_TRAN_NODEB_V2          12
#define PRODUCT_TYPE_TRAN_NODEB_V1V2        13

#define PRODUCT_TYPE_AP_LIBS_CUST           14
#define PRODUCT_TYPE_TRAN_WVISP_V1_CUST     15
#define PRODUCT_TYPE_TRAN_WVISP_V2_CUST     16
#define PRODUCT_TYPE_TRAN_WVISP_V1V2_CUST   17
#define PRODUCT_TYPE_TRAN_NODEB_V1_CUST     18
#define PRODUCT_TYPE_TRAN_NODEB_V2_CUST     19
#define PRODUCT_TYPE_TRAN_NODEB_V1V2_CUST   20
#define PRODUCT_TYPE_WVRP                   21
#define PRODUCT_TYPE_AP_ARM_LIBS            22
#define PRODUCT_TYPE_AP_WVISP_V1V2          23
#define PRODUCT_TYPE_ARM_AP_NODEB           24
#define PRODUCT_TYPE_AP_WVISP_ARM_LIBS      25
#define PRODUCT_TYPE_TRAN_LIBS              26
#define PRODUCT_TYPE_WVISP_V1V2_CUST        27
#define PRODUCT_TYPE_NODEB_V1V2_CUST        28

#define PRODUCT_TYPE_SGSN_NODEB_V1V2        29
#define PRODUCT_TYPE_SGSN_WVISP_V1V2        30
#define PRODUCT_TYPE_SGSN_750_V1            31
#define PRODUCT_TYPE_SGSN_MIPS_V1V2         32
/******************************************************/
/*  CAUTION: Please do not modify the below lines 
    	     and the comment, since it will affect the
    	     build automation                         */
/******************************************************/
#if 1 /*For Wvisp*/
/*  NODEB ,   HERT ,  WVISP , WVRP  */
#define IR_PRODUCT_BUILD_TYPE PRODUCT_TYPE_TRAN_WVISP_V1V2
#endif

/*Compile Macro:if TCPIP_NOVRP is defined, it means VISP enviroment*/
#ifdef TCPIP_NOVRP

/*Compile Macro:if TCPIP_NOVRP is defined, it means VISP enviroment*/
#define TCPIP_IN_VRP             VRP_NO
#define IPOS_NON_VRP             VRP_NO

#ifndef ARM_SUPPORT
#define ARM_SUPPORT              VRP_NO  /* Modified by Arvind for ND Host Integ */
#endif
/* IKEv2: To support new log framework */
#define IPOS_LOG                 VRP_NO


#include "common/visp/tcpip_config.h"
#include "common/visp/task_lock.h"
#include "ipbircommon/ipbirmap/visp/ipbir_visp_env_map.h"

#else

/* IKEv2: To support new log framework */
#define IPOS_LOG                 VRP_YES

/*Compile Macro:if IPOS_INVRP is defined, it means VRP enviroment*/
#ifdef IPOS_INVRP

/*Compile Macro:if TCPIP_NOVRP is defined, it means VISP enviroment*/
#define TCPIP_IN_VRP             VRP_YES
#define IPOS_NON_VRP             VRP_NO

/* Footprint changes : Start */
#define IPOS_UTIL                VRP_NO
/* Footprint changes : End */

#ifndef _IPOSCFG_H_
#define _IPOSCFG_H_


#endif
#include "vrpcfg.h"
#include "ipbircommon/ipbirmap/ipos/ipbir_ipos_env_map.h"

#else

/*if no compile macro, use IPOS enviroment*/
#define TCPIP_IN_VRP             VRP_YES
#define IPOS_NON_VRP             VRP_YES
/* Footprint changes : Start */
#define IPOS_UTIL                VRP_YES
/* Footprint changes : End */

#include "iposcfg.h"

#include "ipbircommon/ipbirmap/ipos/ipbir_ipos_env_map.h"

#endif /* #ifdef IPOS_INVRP */
#endif /* #ifdef TCPIP_NOVRP */

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _IPBIRCFG_H_ */
