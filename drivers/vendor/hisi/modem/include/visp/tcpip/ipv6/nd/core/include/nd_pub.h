/******************************************************************************
*
*            Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.
*                          All Rights Reserved
*
*------------------------------------------------------------------------------
*    Project Code   : VRP5.0
*    Module Name    : IP6 ND
*    Version        : IPBIRV100R003.IPv6.E001
*    File Name      : Nd_pub.h
*    Create Date    : 2003/06/25
*    Author         : Santosh G Kulkarni
*    Description    : the interface module of ND
*------------------------------------------------------------------------------
*  Modification History
*
*  DATE        NAME                   DESCRIPTION
*  ----------------------------------------------------------------------------
*  2003-06-25  Santosh G Kulkarni     Create
*******************************************************************************/
#ifndef    _ND_PUB_H_
#define    _ND_PUB_H_

#ifdef    __cplusplus
extern "C"{
#endif

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

/* Macro to remove Magic Number */
#define TIMEOUTVALUE_1000   1000
#define TIMEOUTVALUE_100    100
#define TIMEOUTVALUE_5000   5000
#define PRIORITY_3          3
#define PRIORITY_4          4
#define CONVERTION_MILLISEC 1000
#define CONVERTION_DAY_HR   24
#define CONVERTION_HR_MIN   60
#define CONVERTION_MIN_SEC  60
#define DELAYINMILLISEC_100 100

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/

#define IP6_ND_NB_ENTRY_ENDOFTREE  4

typedef VOID (*pfConvtoVoidFunc)(VOID *);

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif    /* end of _ND_PUB_H_ */


