

#ifndef __CDMA_TIMING_DRV_H__
#define __CDMA_TIMING_DRV_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2  macro definition
*****************************************************************************/

#define CDMA_TIMING_CLIENT_BUTT         (16)     /* max clients of every period */

#define CHIP_PER_SLOT                   (2048)
#define SLOT_PER_SUBFRAME               (4)
#define SUBFRAME_PER_FRAME               4
/*****************************************************************************
  3  enum definition
*****************************************************************************/
/**
 * Used to select between 1x mode or HRPD mode.
 */
enum CDMA_TIMING_RTT_ENUM
{
    CDMA_TIMING_RTT_1X,
    CDMA_TIMING_RTT_HRPD,
    CDMA_TIMING_RTT_BUTT
};
typedef VOS_UINT16 CDMA_TIMING_RTT_ENUM_UINT16;


enum CDMA_TIMING_PERIOD_ENUM
{
    /** For 1x only 10ms period is supported */
    CDMA_TIMING_PERIOD_10_00_MS_1X,


    CDMA_TIMING_PERIOD_2048_CHIP_HRPD,
    CDMA_TIMING_PERIOD_4096_CHIP_HRPD,
    CDMA_TIMING_PERIOD_8192_CHIP_HRPD,
    CDMA_TIMING_PERIOD_BUTT
};
typedef VOS_UINT16 CDMA_TIMING_PERIOD_ENUM_UINT16;

/**
 * Driver time format
 * Could be used in any call to CPROC_STIME_*
 *
 * @sa CPROC_STIME_GetSystemTime80ms
 */
#ifndef __CDMA_TIMING_DRV_INTERNAL_H__
struct CDMA_TIME_S {
    VOS_UINT32 i[2];
};
#endif
typedef struct CDMA_TIME_S CDMA_TIME;
/*****************************************************************************
  6 STRUCT definition
*****************************************************************************/
/**
 * Callback type used by the clients to timing driver.
 */
typedef void (* CDMA_TIME_CALL_BACK_T)(CDMA_TIME pstCdmaSysTime, void *pvParam);

struct CDMA_TIME_CALL_BACK_CLIENT_STRU;

typedef struct CDMA_TIME_CALL_BACK_CLIENT_STRU *CDMA_TIME_HANDLE_STRU;

typedef struct
{
    VOS_UINT16            uhw1xIntStatus;    /* Interrupt status of 1x   */
    VOS_UINT16            uhwHrpdIntStatus;  /* Interrupt status of HRPD */
} CDMA_TIMING_INTERRUPT_STATUS_STRU;


/*****************************************************************************
  10 function definition
*****************************************************************************/

/**
 * Register a system time interrupt handler. Each system supports two different
 * configuations of the system time interrupts. Either the same period is used
 * with two different time offsets, or two different periods can be used each
 * with separate (or same) time offsets.
 *
 *
 * @param[in] enCdmaMode   1x or HRPD @ref CDMA_TIMING_RTT_ENUM
 * @param[in] enPeriod     @ref CDMA_TIMING_PERIOD_ENUM
 * @param[in] swTimeShift  Number of PCGs that the interupt shall be shifted
 *                         from syten time tick. The parameter can have the
 *                         value[-63,63]
 * @param[in] pfCallback   Registerd callback for interrupt.
 * @param[in] pvParam      Second Parameter to callback function.
 *
 * @return Handle to a Time Event, or NULL on error.
 */
CDMA_TIME_HANDLE_STRU CDMA_RequestTimeEvent(enum CDMA_TIMING_RTT_ENUM enCdmaMode,
                                            enum CDMA_TIMING_PERIOD_ENUM enPeriod,
                                            VOS_INT32 swTimeShift,
                                            CDMA_TIME_CALL_BACK_T pfCallback,
                                            VOS_VOID *pvParam);

/**
 * Release and stop more callbacks.
 *
 * @param[in]  pstEventHandle Handler returned from CDMA_RequestTimeEvent()
 */
VOS_UINT32 CDMA_ReleaseTimeEvent(CDMA_TIME_HANDLE_STRU pstEventHandle);

/**
   Converts the time Time and returns it in same format as
   CPROC_STIME_Get1xSystemTime80ms().

   @param[in] Time Time oto be conberted into 80ms units.
   @param[in] enCdmaMode CDMA_TIMING_RTT_1X or CDMA_TIMING_RTT_EVDO.
   @return    system time pointed out by time.
*/
VOS_UINT64 CDMA_Timing_ConvertSystemTime80ms(CDMA_TIME Time, enum CDMA_TIMING_RTT_ENUM enCdmaMode);

/**
   Converts the time Time and returns it in same format as
   CPROC_STIME_Get1xSystemTime10ms().

   @param[in] Time Time oto be conberted into 10ms units.
   @param[in] enCdmaMode CDMA_TIMING_RTT_1X or CDMA_TIMING_RTT_EVDO.
   @return    system time pointed out by time.
*/
VOS_UINT32 CDMA_Timing_ConvertSystemTime10ms(CDMA_TIME Time, enum CDMA_TIMING_RTT_ENUM enCdmaMode);

/**
   Converts the time Time and returns it in same format as
   CPROC_STIME_Get1xSystemTimePCG().

   @param[in] Time Time oto be conberted into PCGs.
   @param[in] enCdmaMode CDMA_TIMING_RTT_1X or CDMA_TIMING_RTT_EVDO.
   @return    system time pointed out by time.
*/
VOS_UINT32 CDMA_Timing_ConvertSystemTimePCG(CDMA_TIME Time, enum CDMA_TIMING_RTT_ENUM enCdmaMode);

/**
   Converts the time Time and returns it in same format as
   CPROC_STIME_Get1xSystemTime10ms().

   @param[in] Time Time oto be conberted into HRPD slots.
   @param[in] enCdmaMode CDMA_TIMING_RTT_HRPD.
   @return    system time pointed out by time.
*/
VOS_UINT32 CDMA_Timing_ConvertSystemTimeSlot(CDMA_TIME Time, enum CDMA_TIMING_RTT_ENUM enCdmaMode);

/**
   Converts the time Time and returns it in same format as
   CPROC_STIME_Get1xSystemTime10ms().

   @param[in] Time Time oto be conberted into HRPD Sub Frames.
   @param[in] enCdmaMode CDMA_TIMING_RTT_HRPD.
   @return    system time pointed out by time.
*/
VOS_UINT32 CDMA_Timing_ConvertSystemTimeSubFrame(CDMA_TIME Time, enum CDMA_TIMING_RTT_ENUM enCdmaMode);

/**
 * Converter back to HW time.
 *
 * @param enCdmaMode CDMA_TIMING_RTT_1X.
 * @param time80ms Time from 1980 in units of 80ms.
 * @param timePCG PCG unit in the latest 80ms frame.
 *
 * @return Time in harware format.
 */
VOS_UINT64 CDMA_Timing_ConvertToHWTime(enum CDMA_TIMING_RTT_ENUM enCdmaMode,
                                       VOS_UINT64 time80ms,
                                       VOS_UINT32 timePCG );

/**
 * Converter back to HW time.
 *
 * @param time80ms Time from 1980 in units of 80ms.
 * @param timeSlot unit in the latest 80ms frame.
 *
 * @return Time in harware format.
 */
VOS_UINT64 CDMA_Timing_ConvertToHWTimeHrpd(VOS_UINT64 time80ms,
                                           VOS_UINT32 timeSlot );

/**
 * Read the system time from hardware.
 *
 * @param[in] enCdmaMode             ::CDMA_TIMING_RTT_1X or ::CDMA_TIMING_RTT_HRPD
 * @param[out] pstSystemTimeValue    Variable to put timestamp in.
 */
VOS_VOID CDMA_Timing_Drv_ReadHwSystemTime
(
    CDMA_TIMING_RTT_ENUM_UINT16         enCdmaMode,
    CDMA_TIME                         *pstSystemTimeValue
);

void CDMA_Timing_Drv_Initialize( void );

/**
 * Set CDMA Timing interrupt control status.
 *
 * @param[in] enCdmaMode             ::CDMA_TIMING_RTT_1X or ::CDMA_TIMING_RTT_HRPD
 * @param[in] uhwEnable             True or False.
 */
VOS_VOID CDMA_Timing_SetInterruptCtrlStatus
(
    CDMA_TIMING_RTT_ENUM_UINT16            enCdmaMode,
    VOS_UINT16                             uhwEnable
);

/**
 * Read the CDMA interrupt status.
 *
 * @param[in] enCdmaMode             ::CDMA_TIMING_RTT_1X or ::CDMA_TIMING_RTT_HRPD
 *
 * return Interrupt status by CdmaMode.
 */
VOS_UINT16 CDMA_Timing_GetInterruptCtrlStatus
(
    CDMA_TIMING_RTT_ENUM_UINT16            enCdmaMode
);

/**
 * Multi Modem, CPROC init before bbp power on,
 * so After Rx ACTIVE_REQ from APM，CPROC enablde the timing interrupt
 *
 * @param[in] enCdmaMode             ::CDMA_TIMING_RTT_1X or ::CDMA_TIMING_RTT_HRPD
 */
void EnableTimingInterrupt(enum CDMA_TIMING_RTT_ENUM enCdmaMode);
void ResumeHaltInterrupt1XHandle(VOS_UINT32  uwEnable);
void ResumeHaltInterruptHRPDHandle(VOS_UINT32  uwEnable);

int ValidHandle( CDMA_TIME_HANDLE_STRU pstEventHandle );


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

