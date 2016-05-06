/** ***************************************************************************

                   (C), 2001-2011,

 ******************************************************************************
 * @file
 * @brief
 * This is the main interface to ESS.
 * @author    jgw13952
 * @author    Johan Uden
 * @version
 * @date      1990-2011
 * @copyright Huawei Technologies Sweden AB
******************************************************************************/

/*****************************************************************************
  1 Other files included
*****************************************************************************/
#ifndef INCLUSION_GUARD_ESS_H_
#define INCLUSION_GUARD_ESS_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#include "stdint.h"
#include "fwk_ess_ll.h"
/*****************************************************************************
  2 Macro definitions
*****************************************************************************/
/**
 * Sets the count field of the time specification. This specifies when the job
 * shall execute for the first time.
 */
#define ESS_TIME_SET_FIRST_EXECUTE(time,count) ((time)[1] = (count))

/**
 * Sets the depth field of time specification. This specifies the granularity
 * with which time is given. This field cannot be bigger than the depth of
 * of the scheduling loop hierarchy.
 */
#define ESS_TIME_SET_TIME_DEPTH(time,depth)    ((time)[0] = (depth))

/**
 * Sets the event ID where the job shall be executed
 */
#define ESS_TIME_SET_TIME(time,depth,value)    ((time)[depth+2] = (value))

/*****************************************************************************
  3 Enumeration declaration
*****************************************************************************/

/**
 * ESS error codes used in ESS logs
 */
enum ESS_error_value_e {
  /** Parameter error */
  ESS_E_PARAM,
  /** ESS out of memory */
  ESS_E_OUT_OF_MEMORY,
  /** ESS encountered an unknown handle */
  ESS_E_BAD_HANDLE,
  /** ESS encountered an unknown itnerrupt ID */
  ESS_E_BAD_INTERRUPT_ID,
  /** ESS encountered a missed deadline */
  ESS_E_DEADLINE_MISSED_ID,
  /** End marker */
  ESS_E_BUTT
};

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
/**
 * ESS handle type, can hold any ESS handle
 */
typedef union ESS_HANDLE_UNION *ESS_Handle_t;


/**
 * ESS job function type
 */
typedef void(*ESS_Job_t)(void *);

/**
 * In ESS time is relative to a handle and can be given with the
 * granularity of each underlying scheduling loops, as deep as is
 * needed down to the interrupt loop that drives the schedule.
 * Time is represented as an array of integers.
 *
 * The first integer defines how deep into a scheduling hierarchy time
 * is given. Together with the ESS scheduling loop handles this gives
 * the granularity with which time can be given. The second integer
 * contains the value of the loop counter when the job shall execute
 * the for the first time. This allows the user to program jobs into
 * the future.The remaining integers refer to event numbers of the
 * underlying scheduling hierarchies.
 *
 * For instance if a scheduling hierarchy is defined with frame rate
 * and slot rate scheduling loops as:
   @code
   ESS_Handle_t qslot = ESS_ConfigureSchedulingInterrupt(INTERRUPT);
   ESS_Handle_t slot_rate = ESS_ConfigureSchedulerLoop(qslot, 4);
   ESS_Handle_t frame_rate = ESS_ConfigureSchedulerLoop(slot, 15);
   @endcode
 * Then defining start as:
   @code
   // {depth of time hierarchy,
   // first slot or quarter slot when this job shall execute,
   // slot number or quarter slot number when the job executes}
   ESS_Time_t start = {1, 0, 3};
   @endcode
 * and using start with the frame_rate handle
   @code
   my_pfJobFun_handle = AddJobb(frame_rate, start, prio, pstJob, pvPar);
   @endcode
 * means first time the job executes is frame 0, time granularity is
 * slot and the time is slot 3.  Using start with the slot_rate handle
   @code
   my_pfJobFun_handle = AddJobb(slot_rate, start, prio, pstJob, pvPar);
   @endcode
 * means first time the job shall execute is slot 0, time granularity
 * is quarter slot and the time is quarter slot 3.  If start instead
 * is defined as:
   @code
   ESS_Time_t start = {2, 1, 3, 1}; // {slot number, depth, quarter slot number}
   @endcode
 * and used with the frame_rate handle
   @code
   my_pfJobFun = AddJobb(frame_rate, start, prio, pstJob, pvPar);
   @endcode
 * means time granularity is quarter slot and the time is slot 3
 * quarter slot 1. Using this time with the slot_rate handle would be
 * an error because the depth of the slot_rate scheduling hierarchy is
 * only 1 (namely the quarter slot interrupts).
 * Typical usage:
 * @code
   ESS_Time_t aTime = { 0, 0 , 0, 0 };

   // if this is used with a loop hirarchy interrupt<-slot<-frame, and the job
   // is added to the frame loop
   ESS_TIME_SET_FIRST_EXECUTE(aTime, 11); // execute for the first time Fn=11
   ESS_TIME_SET_TIME_DEPTH(aTime, 2);     // granularity is interrupt
   ESS_TIME_SET_TIME(aTime, 0, 12);       // slot 12
   ESS_TIME_SET_TIME(aTime, 1, 3);        // QS 3
 * @endcode
 */
typedef uint32_t ESS_Time_t[];

/*****************************************************************************
  9 Global variables
*****************************************************************************/

/*****************************************************************************
  10 Function declarations
*****************************************************************************/
/** **************************************************************************
  @fn           ESS_ConfigureSchedulingInterrupt


  @details      Configures an interrupt that drives a scheduling hierarchy.

  @param[in]    ESS_InstallHandler The physical interrupt driver that drives scheduling

  @return       A handle that shall be used by the user to reference
                the scheduling interrupt in future calls to ESS.
*/

ESS_Handle_t ESS_ConfigureSchedulingInterrupt(void (*ESS_InstallHandler)( uint32_t *, ESS_LL_IF_STRU *,
                                                                           void ( *pfCallback ) ( void *, uint32_t ),
                                                                           void   *) );

/** **************************************************************************
  @fn           ESS_ConfigureSchedulerLoop

  @details      Creates a Scheduling loop to which jobs can be added. The loop will
                count from 0 to uwMaxCounter - 1. This count is used by jobs to
                specify when they shall execute for the first time. Jobs added to
                the loop will execute every uwPeriod of events of the underlying
                loop (interrupt or loop handle)

   @param[in] unHandle   Handle to the underlying event that drives the
                       loop. This can either be an interrupt or another
                       scheduling loop
   @param[in] uwPeriod The number of the underlying events that will be counted
                       before the attached jobs execute
   @param[in] uwMaxCounter The period of the counter that is used to specify
                      the first time jobs shall execute when they are added.
  @sa           ESS_Time_t
  @return       A handle that shall be used to reference this scheduling loop
                in future calls to ESS
*/
ESS_Handle_t ESS_ConfigureSchedulerLoop( ESS_Handle_t unHandle,
                                         uint32_t uwPeriod,
                                         uint32_t uwMaxCounter );


/** **************************************************************************
  @fn           void ESS_SetSchedulingCount( ESS_Handle_t unHandle,
                             uint32_t uwTickCounter,
                             uint32_t uwLoopCounter)

  @details      Sets the counter of a scheduling loop to value. This way the
                loop can be sycnhronized to the physical world.

  @param[in]    unHandle  Handle to the scheduling for which scheduling count
                shall be set.
  @param[in]    uwTickCounter New value for the counter that counts ticks from
                parent loop
  @param[in]    uwLoopCounter New value for the loop counter

  @return       void
*/
void ESS_SetSchedulingCount( ESS_Handle_t unHandle,
                             uint32_t uwTickCounter,
                             uint32_t uwLoopCounter);

uint32_t ESS_GetLoopCycleLength( ESS_Handle_t unHandle );
uint32_t ESS_GetLoopCounterPeriod( ESS_Handle_t unHandle );

/** **************************************************************************
  @fn           void ESS_GetSchedulingCount( ESS_Handle_t unHandle,
                             uint32_t *uwTickCounter,
                             uint32_t *uwLoopCounter)

  @details      Returns the current counter value for the scheduling loop
                referenced by the handle.

  @param[in]    unHandle Handle to the scheduling loop.
  @param[out]   uwTickCounter Current value of the counter
                that counts ticks from parent loop.
  @param[out]   uwLoopCounter Current value of the loop counter.

  @return       void
*/
void ESS_GetSchedulingCount( ESS_Handle_t unHandle,
                             uint32_t *uwTickCounter,
                             uint32_t *uwLoopCounter);

/** **************************************************************************
  @fn           ESS_Handle_t ESS_AddJob( ESS_Handle_t unHandle,
                                         ESS_Time_t auwStart,
                                         int32_t swPriority,
                                         ESS_Job_t pfJobFun,
                                         void *pvVar )

  @details      Adds a recurring job to a a work queue. The job will be executed
                each time the time defined by auwStart occurs. The job will be waiting
                until the counter of the loop handle to which the job has been
                added reaches the value specified by 'auwStart' (@sa
                ESS_Time_t).
                Note 1; jobs can only be added to handles that are
                created by ESS_CreateSchedulingLoop!
                Note: Jobs are per defeault added in the waiting state (waiting for
                the loop counter to reach the value specified in auwStart @sa
                ESS_Time_t).  If it is the intention that the job shall start at
                the earliest possilbe time, call ESS_Enable with the job handle as
                parameter to expicitly enable the job.

  @param[in] unHandle    A reference to the scheduling loop to which the job is added.
  @param[in] auwStart    A pointer to the array that defines the start time for the job.
  @param[in] swPriority  Lower is value is higher priority. Priority is between 0 and 7.
  @param[in] pfJobFun    A pointer to the function that implementes the job
  @param[in] pvVar       A pointer that will used as parameter when the function pointer
                         to the pfJobFun is called.

  @sa ESS_Delete ESS_Disable ESS_Enable ESS_Time_t

  @return    A handle that can be used to reference the pfJobFun in other calls to ESS.g
*/
ESS_Handle_t ESS_AddJob( ESS_Handle_t unHandle,
                         const ESS_Time_t auwStart,
                         int32_t swPriority,
                         ESS_Job_t pfJobFun,
                         void *pvVar );

/** **************************************************************************
  @fn           ESS_Handle_t ESS_AddOneshotJob(ESS_Handle_t unHandle,
                                               ESS_Time_t auwStart,
                                               int32_t swPriority,
                                               ESS_Job_t pfJobFun,
                                               void *pvVar )

  @details      Adds an oneshot pfJobFun to a a work queue. The pfJobFun will be
                execute the first time the time defined by auwStart occurs. After it
                has executed, it will be removed from the task list for that
                scheduling point. Note: Jobs are per defeault added in the waiting
                state (waiting for the loop counter to reach the value specified in
                auwStart @sa ESS_Time_t).  If it is the intention that the job shall
                start at the earliest possilbe time, call ESS_Enable with the job
                handle as parameter to expicitly enable the job.

  @param[in] unHandle    A reference to the scheduling loop to which the job is added.
  @param[in] auwStart    A pointer to the array that defines the start time for the job.
  @param[in] swPriority  Lower is value is higher priority. Priority is between 0 and 7.
  @param[in] pfJobFun    A pointer to the function that implementes the job
  @param[in] pvVar       A pointer that will used as parameter when the function pointer
                         to the pfJobFun is called.
  @sa ESS_Delete ESS_Disable ESS_Enable ESS_Time_t

  @return    A handle that can be used to reference the pfJobFun in other calls to ESS.
*/
ESS_Handle_t ESS_AddOneshotJob(ESS_Handle_t unHandle,
                    const ESS_Time_t auwStart,
                    int32_t swPriority,
                    ESS_Job_t pfJobFun,
                    void *pvVar );

/** **************************************************************************
  @fn           void ESS_SetDeadline(ESS_Handle_t unHandle, ESS_Time_t swDeadline)

  @details      Sets the deadline for a job. When the job has completed a check
                that the job has completed in time is made. If a real time
                violation has occured, a log is made.

  @sa ESS_AddJob, ESS_AddOneshotJob ESS_Time_t

  @param[in] unHandle      A reference to the scheduling loop to which the job
                         is added.
  @param[in] swDeadline  A pointer to the array that defines the deadline time
                         for the job.

  @return       void
*/
void ESS_SetDeadline(ESS_Handle_t unHandle, const ESS_Time_t swDeadline);

/** **************************************************************************
  @fn           void ESS_Enable(ESS_Handle_t unHandle)

  @details      Enables all paJobs associated with the handle


  @param[in]    unHandle  A reference to the scheduling loop

  @return       void
*/
void ESS_Enable(ESS_Handle_t unHandle);

/** **************************************************************************
  @fn           void ESS_Disable(ESS_Handle_t unHandle)

  @details      Disables all paJobs associated with the handle

  @param[in]    unHandle  A reference to the scheduling loop

  @return       void
*/
void ESS_Disable(ESS_Handle_t unHandle);

/** **************************************************************************
  @fn           void ESS_Delete(ESS_Handle_t unHandle)

  @details      Deletes all paJobs associated with the handle

  @param[in]    unHandle  A reference to the scheduling loop

  @return       void
*/
void ESS_Delete(ESS_Handle_t unHandle);


void FWK_ESS_DumpConfig( ESS_Handle_t unHandle, char* dump_name );

/** **************************************************************************
  @fn           void ESS_IsJobActive(ESS_Handle_t unLoopHandle, ESS_Handle_t  unJobHandle)

  @details      Check one shot job associated with the Rethandle

  @param[in]    unLoopHandle  A reference to the scheduling loop
                unJobHandle   A reference to the scheduling Job

  @return       TRUE: Job is active, FALSE: Job is inactive
*/

int32_t ESS_IsJobActive(ESS_Handle_t   unLoopHandle, ESS_Handle_t  unJobHandle);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INCLUSION_GUARD_ESS_H_ */
