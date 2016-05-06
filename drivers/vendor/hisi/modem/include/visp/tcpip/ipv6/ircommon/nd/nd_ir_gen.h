/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : nd_ir_gen.h
  Version       : Initial Draft
  Author        : Anand S
  Created       : 2007/12/11
  Last Modified :
  Description   : nd_ir_gen.h header file
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

#ifndef __ND_IR_GEN_H__
#define __ND_IR_GEN_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#if (VRP_YES == IP6_NDHOST)

/* Level 1 Interface V-table pointers */
#define IIF_IP6_ND_GENERIC_INTVtbl  IIF_IP6_ND_HOST_INITVtbl
#define IIF_IP6_ND_GENERIC_CFGVtbl  IIF_IP6_ND_HOST_CFGVtbl
#define IIF_IP6_ND_GENERIC_FUNVtbl  IIF_IP6_ND_HOST_FUNVtbl
#define IIF_IP6_ND_GENERIC_DHCP6C_AdaptVtbl IIF_IP6_ND_HOST_DHCP6ADAPTVtbl

/* Level 2 Interface V-table pointers */
#define IIF_IP6_ND_GENERIC_IR_FUNVtbl  IIF_IP6_ND_HOST_IR_FUNVtbl

/* Level 3 Interface V-table pointers */
#define IIF_IP6_ND_GENERIC_INT_INITVtbl IIF_IP6_ND_HOST_INT_INITVtbl
#define IIF_IP6_ND_GENERIC_INT_TESTVtbl  IIF_IP6_ND_HOST_INT_TESTVtbl
#define IIF_IP6_ND_GENERIC_INT_FUNVtbl  IIF_IP6_ND_HOST_INT_FUNVtbl
#define IIF_IP6_ND_GENERIC_INT_SSAVtbl IIF_IP6_ND_HOST_INT_SSAVtbl

/* Level 1 Interface V-table ID */
#define  IID_IP6_ND_GENERIC_INIT  IID_IP6_ND_HOST_INIT
#define  IID_IP6_ND_GENERIC_CFG   IID_IP6_ND_HOST_CFG
#define  IID_IP6_ND_GENERIC_FUN   IID_IP6_ND_HOST_FUN
#define  IID_IP6_ND_GENERIC_DHCP6CAdapt IID_IP6_ND_HOST_DHCP6CAdapt

/* Level 2 Interface V-table ID */
#define IID_IP6_ND_GENERIC_IR_FUN IID_IP6_ND_HOST_IR_FUN

/* Level 3 Interface V-table ID */
#define IID_IP6_ND_GENERIC_INT_INIT IID_IP6_ND_HOST_INT_INIT
#define IID_IP6_ND_GENERIC_INT_FUN  IID_IP6_ND_HOST_INT_FUN
#define IID_IP6_ND_GENERIC_INT_TEST IID_IP6_ND_HOST_INT_TEST
#define IID_IP6_ND_GENERIC_INT_SSA  IID_IP6_ND_HOST_INT_SSA

#else

/* Level 1 Interface V-table pointers */
#define IIF_IP6_ND_GENERIC_INTVtbl  IIF_IP6_ND_INITVtbl
#define IIF_IP6_ND_GENERIC_CFGVtbl  IIF_IP6_ND_CFGVtbl
#define IIF_IP6_ND_GENERIC_FUNVtbl  IIF_IP6_ND_FUNVtbl

/* Level 2 Interface V-table pointers */
#define IIF_IP6_ND_GENERIC_IR_FUNVtbl  IIF_IP6_ND_IR_FUNVtbl

/* Level 3 Interface V-table pointers */
#define IIF_IP6_ND_GENERIC_INT_INITVtbl IIF_IP6_ND_INT_INITVtbl
#define IIF_IP6_ND_GENERIC_INT_TESTVtbl  IIF_IP6_ND_INT_TESTVtbl
#define IIF_IP6_ND_GENERIC_INT_FUNVtbl  IIF_IP6_ND_INT_FUNVtbl
#define IIF_IP6_ND_GENERIC_INT_SSAVtbl IIF_IP6_ND_INT_SSAVtbl


#define  IID_IP6_ND_GENERIC_INIT  IID_IP6_ND_INIT
#define  IID_IP6_ND_GENERIC_CFG   IID_IP6_ND_CFG
#define  IID_IP6_ND_GENERIC_FUN   IID_IP6_ND_FUN
#define  IID_IP6_ND_GENERIC_DHCP6CAdapt VOID

#define IID_IP6_ND_GENERIC_IR_FUN IID_IP6_ND_IR_FUN

#define IID_IP6_ND_GENERIC_INT_INIT IID_IP6_ND_INT_INIT
#define IID_IP6_ND_GENERIC_INT_FUN  IID_IP6_ND_INT_FUN
#define IID_IP6_ND_GENERIC_INT_TEST IID_IP6_ND_INT_TEST
#define IID_IP6_ND_GENERIC_INT_SSA  IID_IP6_ND_INT_SSA

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __ND_IR_GEN_H__ */
