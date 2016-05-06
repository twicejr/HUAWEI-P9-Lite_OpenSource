/*****************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------
*                              tcp6_time.h
*
*    Project Code:  VRP5.0
*    Module Name:  IP6 TCP6
*   Version     : Initial Draft
*    Create Date:  2003/06/27
*    Author:       Naina Gupta
*    Description:  TCP6 timer range set macro
*-----------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------
*  2003-06-27  Naina Gupta         Created
*  2006-06-06  Alok       Updated for 14 Fly-Check rules adherence
*                         for IPOSIR-V1R1-IPv6
******************************************************************
*/

#ifndef _TCP6_TIME_H
#define _TCP6_TIME_H

#ifdef    __cplusplus
extern    "C"{
#endif


/* Force a time value to be in a certain range. */
#define    TCP6T_RANGESET(tv, value, tvmin, tvmax) { \
    (tv) = (value); \
    if ((tv) < (tvmin)) \
    { \
        (tv) = (tvmin); \
    } \
    else \
    { \
        if ((tv) > (tvmax)) \
        { \
            (tv) = (tvmax); \
        } \
    } \
}


#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif
