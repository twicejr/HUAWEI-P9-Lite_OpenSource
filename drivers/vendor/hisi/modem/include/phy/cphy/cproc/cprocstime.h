/**

                   Huawei Technologies Sweden AB (C), 2001-2011,

 ******************************************************************************
 * @file
 * The user interface to the CPROC_1X system time service. CPROC_1X receives
 * priodic notificaiton of the CPROC 1X system time. This time is saved and
 * is provided to user when @ref CPROC_STIME_GetSystemTime. A number of
 * macros for reading parts and validating the system time.
 * @brief
 * Public interface to the CPROC system time service.
 * @author  JGW13952
 * @version
 * @date    2013/11/18 13:57(+0100)
 * @copyright Huawei Technologies Sweden AB
******************************************************************************/

/*****************************************************************************
  1 Other files included
*****************************************************************************/
#ifndef INCLUSION_GUARD_CPROC1XSTIME_H
#define INCLUSION_GUARD_CPROC1XSTIME_H

#include "vos.h"
#include "cdma_timing_drv.h"
#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*****************************************************************************
  2 Macro definitions
*****************************************************************************/
/**
 * Value used to indicate an invalid system time.
 */
#define CPROC_STIME_INVALID_VALUE (0xffffffffffffffffULL)

/**
 * Returns VOS_FALSE if the system time in uSystemTime is invalid, else
 * VOS_TRUE is returned.
 *
 * @param[in]   uSystemTime System time returned by CPROC_STIME_GetSystemTime
 */
#define CPROC_STIME_VALID(uSystemTime)                       \
    ( ( (CPROC_STIME_GET_HIGH_BITS(uSystemTime)              \
         == CPROC_STIME_INVALID_VALUE )                      \
     && (CPROC_STIME_GET_LOW_BITS(uSystemTime)               \
         == CPROC_STIME_INVALID_VALUE ) )                    \
      ? VOS_FALSE                                            \
      : VOS_TRUE )


/**
 * @deprecated Use CDMA_Timing_GetSystemTime80ms() instead.
 */
#define CPROC_STIME_SYSTEM_1X 0

/**
 * @deprecated Use CDMA_Timing_GetSystemTime80ms() instead.
 */
#define CPROC_STIME_GET_FULL_VALUE(uSystemTime)     uSystemTime

/**
 * @deprecated Use CDMA_Timing_GetSystemTime80ms() instead.
 */
#define CPROC_STIME_SYSTEM_TIME_UNION VOS_UINT64

/**
 * @deprecated Use CDMA_Timing_GetSystemTime80ms() instead.
 */
#define CPROC_STIME_GetSystemTime(enSystem) CDMA_Timing_GetSystemTime80ms(enSystem)
/*****************************************************************************
  3 Enumeration declaration
*****************************************************************************/

/*****************************************************************************
  4 Message Header declaration
*****************************************************************************/

/*****************************************************************************
  5 Message declarations
*****************************************************************************/

/*****************************************************************************
  6 STRUCT declarations
*****************************************************************************/

/*****************************************************************************
  7 UNION declarations
*****************************************************************************/

/*****************************************************************************
  8 OTHER declarations
*****************************************************************************/

/*****************************************************************************
  9 Global variables
*****************************************************************************/

/*****************************************************************************
  10 Function declarations
*****************************************************************************/
/**
   Returns the current system time from the last interrupt.
   If no valid 1X system time is available, all '1' is returned.
   The granularity of the returned time is in 80 ms.
   Time is counted from 1 Jan 1980.

   @param[in] enCdmaMode indicates what system (1X/HRPD) time is requested
   @return    system time no older than 10 ms or
              CPROC_SYSTEM_TIME_INVALID_VALUE
*/
VOS_UINT64 CDMA_Timing_GetSystemTime80ms( enum CDMA_TIMING_RTT_ENUM enCdmaMode);

/**
   Returns the current system time from the last interrupt.
   If no valid 1X system time is available, all '1' is returned.
   The granularity of the returned time is in 10 ms.
   Time is counted from last 80ms system tick.

   @param[in] enCdmaMode indicates what system (1X) time is requested
   @return    system time no older than 10 ms or
              CPROC_SYSTEM_TIME_INVALID_VALUE
*/
VOS_UINT32 CDMA_Timing_GetSystemTime10ms( enum CDMA_TIMING_RTT_ENUM enCdmaMode);

/**
   Returns the current system time from the last interrupt.
   If no valid 1X system time is available, all '1' is returned.
   The granularity of the returned time is in PCGs.
   Time is counted from last 80ms system tick.

   @param[in] enCdmaMode indicates what system (1X) time is requested
   @return    system time no older than 10 ms or
              CPROC_SYSTEM_TIME_INVALID_VALUE
*/
VOS_UINT32 CDMA_Timing_GetSystemTimePCG( enum CDMA_TIMING_RTT_ENUM enCdmaMode);

/**
   Returns the current system time from the last interrupt.
   If no valid HRPD system time is available, all '1' is returned.
   The granularity of the returned time is in HRPD Slot.
   Time is counted from last 80ms system tick.

   @param[in] enCdmaMode indicates what system (HRPD) time is requested
   @return    system time no older than 10 ms or
              CPROC_SYSTEM_TIME_INVALID_VALUE
*/
VOS_UINT32 CDMA_Timing_GetSystemTimeSlot( enum CDMA_TIMING_RTT_ENUM enCdmaMode);

/**
   Returns the current system time from the last interrupt.
   If no valid HRPD system time is available, all '1' is returned.
   The granularity of the returned time is in HRPD Sub Frames.
   Time is counted from last 80ms system tick.

   @param[in] enCdmaMode indicates what system (HRPD) time is requested
   @return    system time no older than 10 ms or
              CPROC_SYSTEM_TIME_INVALID_VALUE
*/
VOS_UINT32 CDMA_Timing_GetSystemTimeSubFrame( enum CDMA_TIMING_RTT_ENUM enCdmaMode);

/**
 * Update the timestamp.
 *
 * CDMA_Timing_GetSystemTimeXX wíll return the latest 10ms tick or the time
 * from latest call to CDMA_Timing_UpdateSystemTime();
 *
 * @param[in] enCdmaMode indicates what system (1X/HRPD) time is requested
 */
VOS_VOID CDMA_Timing_UpdateSystemTime(enum CDMA_TIMING_RTT_ENUM enCdmaMode);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INCLUSION_GUARD_CPROC1XSTIME_H */
