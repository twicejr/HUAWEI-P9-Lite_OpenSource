/******************************************************************************
*
*              Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.
*                          All Rights Reserved
*
*------------------------------------------------------------------------------
*    Project Code   : VRP5.0
*    Module Name    : IP6 ND
*    Version        : IPBIRV100R003.IPv6.E001
*    File Name      : Nd_nbcache.h
*    Create Date    : 2003/06/25
*    Author         : Santosh G Kulkarni
*    Description    : the interface module of ND
*------------------------------------------------------------------------------
*  Modification History
*
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2003-06-25  Santosh G Kulkarni     Create
*******************************************************************************/
#ifndef    _ND_NBCACHE_H_
#define    _ND_NBCACHE_H_

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
/* NA message flag values */
#define ND_ISNOTROUTER            0
#define ND_ISROUTER               1
#define ND_HAVENOLLA              0
#define ND_HAVELLA                1

/* Avail value (ND_PAF_INF_NBENTRIES_AVAIL) will not exceed entries to delete
   (g_ulNDEntryToDelete)

   Minimum value for 'ND_PAF_INF_NBENTRIES_AVAIL' is 128
   Default 'g_ulNDEntryToDelete' is 100
   'g_ulNDEntryToDelete' can configure less than avail value */
#define IP6_ND_PERMISSIBLE_LIMIT  \
        (ND_PAF_INF_NBENTRIES_AVAIL - g_ulNDEntryToDelete)

/* Macro to define default number of force delete neighbor cache entries */
#define IP6_ND_NBENTRYDELBYFORCE  100

/* Macro to define max number of neighbor cache entries to be delete at a
   time */
#define IP6_ND_MAXDELETEATATIME     10

/* Macro to remove Magic Number */
#define TIMEDELAY_500               500

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif    /* end of _ND_NBCACHE_H_ */

