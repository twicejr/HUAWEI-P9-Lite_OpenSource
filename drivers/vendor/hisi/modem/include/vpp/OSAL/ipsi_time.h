/**
Copyright(C) 2007, Huawei Tech. India Pvt. Ltd.
            ALL RIGHTS RESERVED

Author     : Jayaraghavendran K
FileName     :ipsi_time.h 
Version      :1
Date         :: 2007-01-08
Description: This file contains all the time related functions.
History:<author>   <date>          <desc>
*/

#ifndef __IPSI_TIME_H_
#define __IPSI_TIME_H_

#include "ipsi_types.h"
#ifndef IPSEC_VISP
#include "time.h"
#include "limits.h"
#endif

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef IPSEC_VISP
#define IPSI_LONG_MAX LONG_MAX
#endif


//used in ipsi_recvfrom_timeout
typedef struct ipsi_timeval_st
{
    long    tvSec;         /* seconds */
    long    tvUSec;        /* and microseconds */
}IPSI_TIMEVAL_S;

/**
    @brief          The ipsi_get_utc_time function will give the time
                    since the Epoch
                    (00:00:00 UTC, January 1, 1970), measured in seconds.

    @param[out]     tim   Pointer to a variable of type ipsi_time_t in which
                    the time value is stored.
    @retval         IPSI_SUCCESS   On Success
                    IPSI_FAILURE   On Failure
*/
IPSILINKDLL int ipsi_get_utc_time(ipsi_time_t *tim);

#ifdef IPSEC_VISP
extern struct tm;
#endif

/**
    @brief          The ipsi_get_mktime function will convert the tm structure 
                    into seconds and subtract the local timezone value.

    @param[out]     lTime - The pointer to variable of type ipsi_time_t in
                    which the time value is stored.
                          
    @param[in]      pstTime - Pointer to a variable struct tm which has to 
                    be converted to seconds

    @retval         IPSI_SUCCESS   On Success
                    IPSI_FAILURE   On Failure
*/
IPSILINKDLL int ipsi_get_mktime(struct tm * pstTime,ipsi_time_t *lTime);


/**
    @brief          The ipsi_gmtime function will convert the seconds into
                    tm structure

    @param[in]      lTime - The variable of type ipsi_time_t in
                    which the time value is stored.
                          
    @param[out]     pstTime - Pointer to a variable struct tm which has to 
                    be converted to seconds

    @retval         pstTime   On Success
                    NULL   On Failure
*/
IPSILINKDLL struct tm * ipsi_gmtime(const ipsi_time_t lTime,
                struct tm * pstTime);


/**
    @brief          The ipsi_tick function will get clock ticks

    @retval         Ticks elapsed 
*/

IPSILINKDLL long ipsi_tick(void);

/**
    @brief          The ipsi_tick_ex function will get clock ticks

    @retval         Ticks elapsed 
*/

IPSILINKDLL long ipsi_tick_ex(void);






/**
    @brief          The ipsi_tick_in_sec function will get number of ticks
                        per second

    @retval         Ticks Per Second
*/
IPSILINKDLL long ipsi_ticks_per_second(void);

/**
    @brief          The ipsi_get_utc_time_ex function will give the time
                    since the Epoch
                    (00:00:00 UTC, January 1, 1970), measured in seconds.

    @param[out]     pstSysTime   Pointer to a variable of type DATETIME_S

    @retval         IPSI_SUCCESS   On Success
                    IPSI_FAILURE   On Failure
*/

IPSILINKDLL int ipsi_get_utc_time_ex(DATETIME_S **pstSysTime);

/*******************************************************************************
*    Func Name:  ipsi_comparedates                                               *
*  Description:  Reads in two DATETIME_S structures and compares them.  It       *
*                 specifies whether first date is BEFORE,AFTER  or SAME as       *
*                 second date.  It aso gives the difference between the two     *
*                 dates.                                                           *
*        Input:  DATETIME_S* pDateA, the first date                               *
*                 DATETIME_S* pDateB, the second date                           *
*       Output:     SEC_UINT32 *pDiffSeconds, the difference between the two       *
*                 dates in secondfs                                               *
*       Return:     DATE_COMPARE_E, The enum specifying whether the first date    *
*                 is before, afer ,or same as second date.                       *
*                 Possible Values :                                               *
*                 ERROR_CMP- error in comparison                                   *
*                 EQUAL_DATE - the two dates are same                           *
*                 BEFORE_DATE - first date is before second date                   *
*                 AFTER_DATE - first date is after second date                   *
*      Caution: -                                                               *
*------------------------------------------------------------------------------*
*  Modification History                                                        *
*  DATE        NAME             DESCRIPTION                                    *
*  --------------------------------------------------------------------------  *
*  YYYY-MM-DD                                                                  *
*                                                                              *
*******************************************************************************/


IPSILINKDLL DATE_COMPARE_E ipsi_comparedates(const DATETIME_S* pDateA,
                                const DATETIME_S* pDateB,
                                unsigned int *pulDiffSeconds);

/*******************************************************************************
*    Func Name:  ipsi_comparedates_ex                                           *
*  Description:  Reads in two DATETIME_S structures and compares them.  It       *
*                 specifies whether first date is BEFORE,AFTER  or SAME as       *
*                 second date.  It aso gives the difference between the two     *
*                 dates.                                                           *
*        Input:  DATETIME_S* pDateA, the first date                               *
*                 DATETIME_S* pDateB, the second date                           *
*       Output:     SEC_TIME_T *pDiffSeconds, the difference between the two       *
*                 dates in secondfs                                               *
*       Return:     DATE_COMPARE_E, The enum specifying whether the first date    *
*                 is before, afer ,or same as second date.                       *
*                 Possible Values :                                               *
*                 ERROR_CMP- error in comparison                                   *
*                 EQUAL_DATE - the two dates are same                           *
*                 BEFORE_DATE - first date is before second date                   *
*                 AFTER_DATE - first date is after second date                   *
*      Caution: -                                                               *
*------------------------------------------------------------------------------*
*  Modification History                                                        *
*  DATE        NAME             DESCRIPTION                                    *
*  --------------------------------------------------------------------------  *
*  YYYY-MM-DD                                                                  *
*                                                                              *
*******************************************************************************/
IPSILINKDLL DATE_COMPARE_E ipsi_comparedates_ex(const DATETIME_S* pDateA,
                                const DATETIME_S* pDateB,
                                SEC_TIME_T *pulDiffSeconds);




/**
    @brief          The ipsi_timezone function will returns the timezone value
                        in second

    @retval         returns the timezone value
*/
IPSILINKDLL long ipsi_timezone(void);


/**
    @brief          The ipsi_tick_in_sec_ex function will get number of ticks
                        per second

    @retval         Ticks Per Second
*/
IPSILINKDLL long ipsi_ticks_per_second_ex(void);

/**
    @brief          The ipsi_localtime function will returns the localtime value
                       with the time value passed.

    @retval         returns the local time of the system
*/
IPSILINKDLL int ipsi_localtime(const ipsi_time_t *timer,
                                            struct tm *localTime);

/**
    @brief          The ipsi_asctime function will returns the C string containing
                       the date and time information in human readable format.

    @retval         returns the date and time in human readable format
*/
IPSILINKDLL int ipsi_asctime(const struct tm *pstTime, char *pcAscTime);


/**
    @breif            ipsi_sleep_ex function suspends the execution of the current
                    thread for a specified interval passed as parameter.
    
    @param[in]        uiTime Unsigned integer that specifies the milliseconds

    @retval            None
*/

IPSILINKDLL void ipsi_sleep_ex(unsigned int uiTime);


#ifdef  __cplusplus
}
#endif
#endif

