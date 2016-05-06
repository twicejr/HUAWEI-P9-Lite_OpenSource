/**

                   Huawei Technologies Sweden AB (C), 2001-2011,

 ******************************************************************************
 * @file
 * @brief
 * Interface for an advanced, optimized FSM.
 *
 * @author F73150
 * @version
 * @date 2013/09/02 13:27(+0200)
 * @copyright Huawei Technologies Sweden AB
******************************************************************************/

/*****************************************************************************
  1 Other files included
*****************************************************************************/
#ifndef INCLUSION_GUARD_FWK_FSM_H
#define INCLUSION_GUARD_FWK_FSM_H

#include "stdint.h"
#include "fwk_log.h"
#ifdef CPROC_UT_PRINT
#include "cproc_1x_util_ess.h"
#include "cproc_tc_msg_support.h"
#endif

enum FSM_ERROR_MSG_ENUM {
    CPROC_FSM_LOG_STATE_CHANGE = 578000,
    CPROC_FSM_LOG_EVENT,
    CPROC_FSM_LOG_OUT_OF_RANGE_STATE,
    CPROC_FSM_LOG_ENTER_ERROR_STATE,
    CPROC_FSM_LOG_PDB_INSERT_PILOT,          /* 578004 */
    CPROC_FSM_LOG_PDB_REMOVE_PILOT,
    CPROC_FSM_LOG_PDB_NEIGHBOR_LIST,
    CPROC_FSM_LOG_CM_EVENT_HANDLE_EXCEPTION, /* Print event instead of reset */
    CPROC_FSM_LOG_RECEIVER_PID_EXCEPTION,
    CPROC_FSM_LOG_SET_TEST_MODE
};

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*****************************************************************************
  2 Macro definitions
*****************************************************************************/

/**
 * Return value from FSM if the event don't have an associated handler.
 * @sa CPROC_FSM_HandleEvent
 */
#define CPROC_FSM_EVENT_NOT_HANDLED ( 1 )

/**
 * Return value from FSM if the event had an associated handler.
 * @sa CPROC_FSM_HandleEvent
 */
#define CPROC_FSM_EVENT_HANDLED ( 0 )

/**
 * Retun value from a event handler to the FSM if the handler don't want to
 * change the state.
 * @note
 *  The value is chosen as: 5= S, 7 =T, 8 = eight/ate => 578 = STATE
 *  0xFFFF etc are avoided as they are used in too many other places.
 *
 * @sa CPROC_FSM_HandleEvent
 */
#define CPROC_FSM_REMAIN_IN_STATE ( 0x578000 )

/**
 * Return a error code from an event handler to CPROC_FSM_HandleEvent
 * CPROC_FSM_HandleEvent will propagate the value to its client.
 * An FSM will remain in ERROR state until the error handler return an new
 * state or CPROC_FSM_SetState is called.
 *
 * @note
 *  The value is chosen as: 5= S, 7 =T, 8 = eight/ate => 578 = STATE
 *  0xFFFF etc are avoided as they are used in too many other places.
 *
 * @sa CPROC_FSM_HandleEvent
 */
#define CPROC_FSM_ERROR_STATE ( 0xDEAD578 )

/**
 * Macro for ease use of CPROC_FSM_StateName()
 *
 * @param[in] fsm  A handle from CPROC_FSM_RegisterFsm().
 * @param[in] state A named state value, will be converted to a string
 *                  in the call to CPROC_FSM_StateName().
 * @sa CPROC_FSM_StateName
 */
#define CPROC_FSM_STATE_NAME(fsm, state) CPROC_FSM_StateName(fsm, state, #state)

#if 1
/**
 * Report entry to error state and the pointer to the FSM.
 */
#define CPROC_FSM_LOG_ERROR(pstFsm)                         \
    CPROC_1X_LogFunction(UPHY_MNTN_RPT_LEVEL_ERROR,         \
                         FILE_IDENTIFYER,                   \
                         __LINE__,                          \
                         2,                                 \
                         CPROC_FSM_LOG_ENTER_ERROR_STATE,   \
                         (uint32_t)pstFsm,                \
                         578,                               \
                         0,                                 \
                         0)

/**
 * Report change state to a undefined state.
 */
#define CPROC_FSM_LOG_ERROR_STATE( pstFsm, uwState )             \
    CPROC_1X_LogFunction(UPHY_MNTN_RPT_LEVEL_ERROR,              \
                         FILE_IDENTIFYER,                        \
                         __LINE__,                               \
                         4,                                      \
                         CPROC_FSM_LOG_OUT_OF_RANGE_STATE,       \
                         (uint32_t)pstFsm,                     \
                         (uint32_t)pstFsm->swCurrentState,     \
                         (uint32_t)uwState,                    \
                         578)


/**
 * Report reception of a event and the current state.
 */
#ifdef CPROC_UT_PRINT
#define CPROC_FSM_LOG_EVENT(pstFsm, uwEvent)                            \
    {                                                                   \
        uint32_t uwFSMLog80msTime,uwFSMLog10msTime;                   \
        if( CPROC_1X_ESS_UTIL_GetEssLoopAddr()->hESS64x80msLoop )       \
        {                                                               \
            ESS_GetSchedulingCount( CPROC_1X_ESS_UTIL_GetEssLoopAddr()->hESS64x80msLoop, &uwFSMLog10msTime, &uwFSMLog80msTime ); \
        }                                                               \
        else                                                            \
        {                                                               \
            uwFSMLog10msTime = 0;                                       \
            uwFSMLog80msTime = 0;                                       \
        }                                                               \
        printf("%d:%d Rec    State:%d, %s (%d)\n",uwFSMLog80msTime & 0x3f,uwFSMLog10msTime & 0x07,pstFsm->swCurrentState,TB_FindSignalName(uwEvent),uwEvent); \
    }
#else
#define CPROC_FSM_LOG_EVENT(pstFsm, uwEvent)                            \
    CPROC_1X_LogFunction(UPHY_MNTN_RPT_LEVEL_INFO,                      \
                         FILE_IDENTIFYER,                               \
                         __LINE__,                                      \
                         4,                                             \
                         CPROC_FSM_LOG_EVENT,                           \
                         (uint32_t)pstFsm,                            \
                         (uint32_t)pstFsm->swCurrentState,            \
                         (uint32_t)uwEvent,                           \
                         578)
#endif

/**
 * Report change of state. Current and next state if logged.
 */
#define CPROC_FSM_LOG_STATE_CHANGE(pstFsm, uwNextState)         \
    CPROC_1X_LogFunction(UPHY_MNTN_RPT_LEVEL_INFO,              \
                         FILE_IDENTIFYER,                       \
                         __LINE__,                              \
                         4,                                     \
                         CPROC_FSM_LOG_STATE_CHANGE,            \
                         (uint32_t)pstFsm,                    \
                         (uint32_t)pstFsm->swCurrentState,    \
                         (uint32_t)uwNextState,               \
                         578)

/*****************************************************************************
  6 STRUCT declarations
*****************************************************************************/
#else
#define CPROC_FSM_LOG_ERROR(pstFsm)
#define CPROC_FSM_LOG_ERROR_STATE( pstFsm, uwState )
#define CPROC_FSM_LOG_EVENT(pstFsm, uwCurState, uwEvent)
#define CPROC_FSM_LOG_STATE_CHANGE(pstFsm, uwNextState)
#endif
/**
 * Return type for a event handler.
 * shall be a valid state in the FSM there the function belong or
 * CPROC_FSM_REMAIN_IN_STATE if the handler what to remain in current
 * state.
 * @sa CPROC_FSM_REMAIN_IN_STATE
 */
typedef int32_t CPROC_FSM_STATE_T;

/**
 * Event handler
 */
typedef CPROC_FSM_STATE_T (*CPROC_FSM_EVENT_HANDLER)( void*, int32_t );

/**
 * Structure that connects an event with an specific handler.
 * Every state builds up by a table of events and eventhandlers.
 * if the first element in the table is not null the CPROC_FSM_HandleEvent
 * will call this handler if the event don't match any event in the table.
 * The table should be terminated with a "{null, 0}" element.
 *
 * @sa struct STATE_TABLE_STRU
 */
typedef struct
{
    /**
     * function that get called when the event corresponding
     * event is passed to CPROC_FSM_HandleEvent.
     */
    CPROC_FSM_EVENT_HANDLER pfEventHandler;
    /**
     * Matching event number that will cause eventhandler to be called.
     */
    int32_t swEvent;
}CPROC_FSM_EVENT_ACTION_STRU;

/**
 * Basic type for a state in a state machine.
 * The state machine is defind as a table of states.
 * The first state shall be 0 and then incresed by
 * one for each element in the table.
 *
 * @code
 EVENT_ACTION_STRU state_0_actions [] = {
   { null, 0},
   { h1s1, event1},
   { h2s1, event2},
   {null, 0}
   };

 EVENT_ACTION_STRU state_1_actions[] = {
   { default_handler_s1, 0},
   {null, 0}
   };

 EVENT_ACTION_STRU state_2_actions [] = {
   { default_handler_s2, 0},
   { h1s3, event1},
   { h2s3, event2},
   { h3s3, event3},
   {null, 0}
   };

 STATE_TABLE_STRU my_FSM_table[] ={
   {0, state_0_actions},
   {1, state_1_actions},
   {2, state_2_actions},
 };
 * @endcode
 * @sa struct EVENT_ACTION
*/
typedef struct CPROC_FSM_STATE_TABLE
{
    const int32_t swState;
    CPROC_FSM_EVENT_ACTION_STRU const *pstEvents;
}CPROC_FSM_STATE_TABLE_STRU;

/*****************************************************************************
  8 OTHER declarations
*****************************************************************************/
/**
 * FSM Handle.
 * Returnd by CPROC_FSM_RegisterFsm and shall be handed as an id to all further
 * calls to FSM.
 * @sa CPROC_FSM_RegisterFsm
 */
typedef struct CPROC_FSM_HANDLE_STRU *CPROC_FSM_Handle_t;


/*****************************************************************************
  10 Function declarations
*****************************************************************************/

/** **************************************************************************
  @fn        CPROC_FSM_Handle_t CPROC_FSM_RegisterFsm(
                  CPROC_FSM_STATE_TABLE_STRU const *pstStateTable,
                  int32_t swMaxState,
                  int32_t (*pfErrorHandler)(void *) );
  @details   Register a state machine in FSM.
  @param[in] pstStateTable table with states and enent tables.
  @param[in] swMaxState Lenght of the state table.
  @param[in] pfErrorHandler function that are called when a event handler
             returns CPROC_FSM_ERROR_STATE and then as long as
             the FSM remains in this state.
  @return    a handle that identify the registered machine.
*/
/*
  History        :
  1.Date         : 2013/10/21
    Author       : F73150
    Modification : Created function

*****************************************************************************/
CPROC_FSM_Handle_t CPROC_FSM_RegisterFsm( CPROC_FSM_STATE_TABLE_STRU const *pstStateTable,
                                          int32_t swMaxState,
                                          CPROC_FSM_EVENT_HANDLER pfErrorHandler);

/** **************************************************************************
  @fn        int32_t CPROC_FSM_HandleEvent(CPROC_FSM_Handle_t pstFsm,
                                       void *pMsg,
                                       int32_t swEvent );
  @details   Calls the registered event handler for the specific event and current state.
  @param[in] pstFsm A handle from CPROC_FSM_RegisterFsm.
  @param[in] pMsg argument passed to the eventhandler.
  @param[in] swEvent Event to match in the EVENT_ACTION_STRU table for the
             current state.
  @return    CPROC_FSM_EVENT_HANDLED if it found an event handler.
             CPROC_FSM_EVENT_NOT_HANDLED if there was no handler and no default handler
                                   registered in current state.
             CPROC_FSM_ERROR_IN_STATE if the handler returned that.
*/
/*
  History        :
  1.Date         : 2013/10/21
    Author       : F73150
    Modification : Created function

*****************************************************************************/
int32_t CPROC_FSM_HandleEvent(CPROC_FSM_Handle_t pstFsm,
                                void          *pMsg,
                                int32_t          swEvent );

/** **************************************************************************
  @fn        int32_t CPROC_FSM_GetState(CPROC_FSM_Handle_t pstFsm);
  @details   Returns the current state.
  @param[in] pstFsm A handle from CPROC_FSM_RegisterFsm.
  @return    Current state
*/
/*
  History        :
  1.Date         : 2013/10/21
    Author       : F73150
    Modification : Created function

*****************************************************************************/
int32_t CPROC_FSM_GetState(CPROC_FSM_Handle_t pstFsm);

/** **************************************************************************
  @fn        void CPROC_FSM_SetState(CPROC_FSM_Handle_t pstFsm,
                      int32_t swState);
  @details   Sets state in the fsm.
  @param[in] pstFsm A handle from CPROC_FSM_RegisterFsm.
  @param[in] swState New state in the fsm.

  @note if the new state is not valid the function will call the error handler.

  @return    Void.
*/
/*
  History        :
  1.Date         : 2013/10/21
    Author       : F73150
    Modification : Created function

*****************************************************************************/
void CPROC_FSM_SetState(CPROC_FSM_Handle_t pstFsm,
                      int32_t swState);

/** **************************************************************************
  @fn        void CPROC_FSM_KillFsm(CPROC_FSM_Handle_t pstFsm)

  @details   Remove an FSM and free the memory.
  @param[in] pstFsm A handle from CPROC_FSM_RegisterFsm.

  @return    Void.
*/
/*
  History        :
  1.Date         : 2013/10/21
    Author       : F73150
    Modification : Created function

*****************************************************************************/
void CPROC_FSM_KillFsm(CPROC_FSM_Handle_t pstFsm);

/**
 * Create a trace in IFF format for the given FSM.
 *
 * @param[in] pstFsm A handle from CPROC_FSM_RegisterFsm.
 * @param[in] name Name of the trace.
 */
void CPROC_FSM_StartTrace(CPROC_FSM_Handle_t pstFsm,
                              char * name);
/**
 * Map a State ID to a string.
 * @param[in] pstFsm A handle from CPROC_FSM_RegisterFsm.
 * @param[in] state The ID of the state to be named.
 * @param[in] name NULL terminated string. Name of state.
 *
 * One easy way to StateName is to use the macro:
 * @code
 * enum state_e {
 *   STATE_INIT,
 *   STATE_FOO,
 *   STATE_BAR,
 *   STATE_BUTT
 * };
 * myFsm = CPROC_FSM_RegisterFsm(pstStateTable, STATE_BUTT, NULL);
 * CPROC_FSM_StartTrace(myFsm, "myFsmTrace.iff");
 * CPROC_FSM_STATE_NAME(myFsm, STATE_INIT);
 * CPROC_FSM_STATE_NAME(myFsm, STATE_FOO);
 * CPROC_FSM_STATE_NAME(myFsm, STATE_BAR);
 * @endcode
 *
 * @sa CPROC_FSM_STATE_NAME
 */
void CPROC_FSM_StateName(CPROC_FSM_Handle_t pstFsm,
                             CPROC_FSM_STATE_T state,
                             char * name);

/**
 * Stop trace FSM state chages. Will close the Dump.
 * It is not possible to apend data after is.
 *
 * @param[in] pstFsm A handle from CPROC_FSM_RegisterFsm.
 *
 * @sa CPROC_FSM_StartTrace()
 */
void CPROC_FSM_StopTrace(CPROC_FSM_Handle_t pstFsm);

#ifdef _MSC_VER
/* Functions used for system test and unit test only. */

extern int32_t FSM_Test_GetCurrentState(CPROC_FSM_Handle_t fsm);
extern void FSM_Test_SetCurrentState(CPROC_FSM_Handle_t fsm,int32_t state);
extern void FSM_Test_SetMagic(CPROC_FSM_Handle_t fsm,int32_t magic);

#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INCLUSION_GUARD_FWK_FSM_H */
