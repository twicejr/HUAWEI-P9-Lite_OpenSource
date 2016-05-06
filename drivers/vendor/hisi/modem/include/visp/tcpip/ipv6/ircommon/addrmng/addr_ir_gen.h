/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : addr_ir_gen.h
  Version       : IPBIRV100R003.IPv6.E001
  Author        : Anand S
  Created       : 2007/12/11
  Last Modified :
  Description   : addr_ir_gen.h header file
  Function List :
  History       :
  1.Date        : 2007/12/11
    Author      : Anand S
    Modification: Created file

******************************************************************************/

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/

/*----------------------------------------------*
 * module-wide global variables                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * constants                                    *
 *----------------------------------------------*/

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/

#ifndef __ADDR_IR_GEN_H__
#define __ADDR_IR_GEN_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#if (VRP_YES == IP6_NDHOST)
#define IIF_IP6_ADDR_GENERIC_INTVtbl  IIF_IP6_ADDR_HOST_INITVtbl
#define IIF_IP6_ADDR_GENERIC_CFGVtbl  IIF_IP6_ADDR_HOST_CFGVtbl
#define IIF_IP6_ADDR_GENERIC_FUNVtbl  IIF_IP6_ADDR_HOST_FUNVtbl

#define IIF_IP6_ADDR_GENERIC_IR_FUNVtbl  IIF_IP6_ADDR_HOST_IR_FUNVtbl

#define IIF_IP6_ADDR_GENERIC_INT_INITVtbl IIF_IP6_ADDR_HOST_INT_INITVtbl
#define IIF_IP6_ADDR_GENERIC_INT_FUNVtbl  IIF_IP6_ADDR_HOST_INT_FUNVtbl
#define IIF_IP6_ADDR_GENERIC_INT_HSBVtbl
#define IIF_IP6_ADDR_GENERIC_INT_TESTVtbl IIF_IP6_ADDR_HOST_INT_TESTVtbl
#define IIF_IP6_ADDR_GENERIC_INT_SSAVtbl  IIF_IP6_ADDR_HOST_INT_SSAVtbl

#define  IID_IP6_ADDR_GENERIC_INIT IID_IP6_ADDR_HOST_INIT
#define  IID_IP6_ADDR_GENERIC_CFG  IID_IP6_ADDR_HOST_CFG
#define  IID_IP6_ADDR_GENERIC_FUN  IID_IP6_ADDR_HOST_FUN

#define IID_IP6_ADDR_GENERIC_IR_FUN IID_IP6_ADDR_HOST_IR_FUN

#define IID_IP6_ADDR_GENERIC_INT_INIT IID_IP6_ADDR_HOST_INT_INIT
#define IID_IP6_ADDR_GENERIC_INT_FUN  IID_IP6_ADDR_HOST_INT_FUN
#define IID_IP6_ADDR_GENERIC_INT_HSB
#define IID_IP6_ADDR_GENERIC_INT_TEST IID_IP6_ADDR_HOST_INT_TEST
#define IID_IP6_ADDR_GENERIC_INT_SSA  IID_IP6_ADDR_HOST_INT_SSA
#else

#define IIF_IP6_ADDR_GENERIC_INTVtbl  IIF_IP6_ADDR_INITVtbl
#define IIF_IP6_ADDR_GENERIC_CFGVtbl  IIF_IP6_ADDR_CFGVtbl
#define IIF_IP6_ADDR_GENERIC_FUNVtbl  IIF_IP6_ADDR_FUNVtbl

#define IIF_IP6_ADDR_GENERIC_IR_FUNVtbl  IIF_IP6_ADDR_IR_FUNVtbl

#define IIF_IP6_ADDR_GENERIC_INT_INITVtbl IIF_IP6_ADDR_INT_INITVtbl
#define IIF_IP6_ADDR_GENERIC_INT_FUNVtbl  IIF_IP6_ADDR_INT_FUNVtbl
#define IIF_IP6_ADDR_GENERIC_INT_HSBVtbl  IIF_IP6_ADDR_INT_HSBVtbl
#define IIF_IP6_ADDR_GENERIC_INT_TESTVtbl IIF_IP6_ADDR_INT_TESTVtbl
#define IIF_IP6_ADDR_GENERIC_INT_SSAVtbl  IIF_IP6_ADDR_INT_SSAVtbl

#define  IID_IP6_ADDR_GENERIC_INIT  IID_IP6_ADDR_INIT
#define  IID_IP6_ADDR_GENERIC_CFG   IID_IP6_ADDR_CFG
#define  IID_IP6_ADDR_GENERIC_FUN   IID_IP6_ADDR_FUN

#define IID_IP6_ADDR_GENERIC_IR_FUN IID_IP6_ADDR_IR_FUN

#define IID_IP6_ADDR_GENERIC_INT_INIT IID_IP6_ADDR_INT_INIT
#define IID_IP6_ADDR_GENERIC_INT_FUN  IID_IP6_ADDR_INT_FUN
#define IID_IP6_ADDR_GENERIC_INT_HSB  IID_IP6_ADDR_INT_HSB
#define IID_IP6_ADDR_GENERIC_INT_TEST IID_IP6_ADDR_INT_TEST
#define IID_IP6_ADDR_GENERIC_INT_SSA  IID_IP6_ADDR_INT_SSA
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __ADDR_IR_GEN_H__ */

