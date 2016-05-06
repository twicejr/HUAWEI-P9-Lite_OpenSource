/** ***************************************************************************

                   Huawei Technologies Sweden AB (C), 2001-2011,

 ******************************************************************************
 * @file
 * @brief
 * This is the interface between the ESS and the driver of the HW that
 * generates the events that drives the ESS scheduling loops.
 *
 * The driver is responsible for filtering events so only events that are
 * requested by scheduling loops are passed on to the ESS
 * interrupt_handler.  Also, the driver must provide functions to
 * enable and disable interrupts from the HW that generates the
 * events, so ESS can manipulate the job lists that are associated
 * with each event in an interrupt safe manner. Finally, an interface
 * for getting the current counter of the underlying event loop shall
 * be implemented.
 *
 * @author    jgw13952
 * @author    Johan Uden
 * @version
 * @date      1990-2011
 * @copyright Huawei Technologies Sweden AB
******************************************************************************/

/*****************************************************************************
  1 Other files included
*****************************************************************************/
#ifndef INCLUSION_GUARD_ESS_LL_H_
#define INCLUSION_GUARD_ESS_LL_H_

#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */

#include "stdint.h"

/*****************************************************************************
  2 Macro definitions
*****************************************************************************/

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
/**
 * Enables one or more interrupt instances that drives ESS. The function shall
 * increment the numer of requests for each requested interrupt instance.
 *
 * @param[in] swOffset   The event that is needed by a scheduling loop.
 * @param[in] uwPeriod   The period with which events are enabled. All events in the
 *                       the interval [0..loopSize-1] that fulfill swOffset + N*uwPeriod
 *                       will be enabled. If uwPeriod is the same as loopSize only one
 *                       interrupt will be enabled.
 */
typedef void (*ESS_LL_RequestEvent_t)(uint32_t uwOffset,
                                      uint32_t uwPeriod);

/**
 * Releases a previous request for one or more interrupt instances that drives
 * ESS. When there are no requester for an interrupt instance, it shall be
 * disabled by the function.
 *
 * @param swOffset The event that is no longer needed by any scheduling loop.
 * @param uwPeriod The uwPeriod with which events are disabled. All events in the
 *                 the interval [0..loopSize-1] that fulfill swOffset + N*uwPeriod
 *                 will be disabled.
 */
    typedef void (*ESS_LL_ReleaseEvent_t)(uint32_t uwOffset,
                                          uint32_t uwPeriod);


/**
 * Shall enable the reception of the timing unit inerrupt. Shall not change
 * the setting for individual events in the interrupt loop.
 */
typedef void (*ESS_LL_Enable_t)( int32_t swInterruptEnable );

/**
 * Shall disable the reception of the timing unit inerrupt. Shall not change
 * the setting for individual events in the interrupt loop
 */
typedef int32_t (*ESS_LL_Disable_t)( void );

/**
 * Shall return the current time give by the timing unit. The timing unit
 * counts the events cyclically, and it this count that shall be returned
 * by the function.
 */
typedef uint32_t (*ESS_LL_GetCurrentTime_t)(void);
typedef void (*ESS_LL_SetCurrentTime_t)(uint32_t);

typedef struct __ESS_LL_IF_STRU__
{
    ESS_LL_RequestEvent_t    ESS_LL_RequestEvent;
    ESS_LL_ReleaseEvent_t    ESS_LL_ReleaseEvent;
    ESS_LL_Enable_t          ESS_LL_Enable;
    ESS_LL_Disable_t         ESS_LL_Disable;
    ESS_LL_GetCurrentTime_t  ESS_LL_GetCurrentTime;
    ESS_LL_SetCurrentTime_t  ESS_LL_SetCurrentTime;
} ESS_LL_IF_STRU;

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


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* INCLUSION_GUARD_ESS_LL_H_ */

