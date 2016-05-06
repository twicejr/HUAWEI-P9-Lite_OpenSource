/**

                   Huawei Technologies Sweden AB (C), 2001-2011,

 ******************************************************************************
 * @file
 * @brief
 * Interface for an advanced, optimized FSM.
 *
 * @author F73150
 * @version
 * @date 2014/10/15 13:27(+0200)
 * @copyright Huawei Technologies Sweden AB
******************************************************************************/

/*****************************************************************************
  1 Other files included
*****************************************************************************/
#ifndef INCLUSION_GUARD_UFSM_H
#define INCLUSION_GUARD_UFSM_H

#include "stdint.h"
#include "fwk_log.h"

enum UFSM_ERROR_MSG_ENUM {
    UFSM_LOG_STATE_CHANGE = 578000,
    UFSM_LOG_EVENT,
    UFSM_LOG_OUT_OF_RANGE_STATE,
    UFSM_LOG_ENTER_ERROR_STATE
};

struct _ErrorCode{
    int32_t swCurrentState;
    int32_t ErrorCode;
};

struct stateError{
    int32_t swCurrentState;
    int32_t uwNewErrorState;
};


struct stateChange{
    int32_t swCurrentState;
    int32_t uwNewState;
};

struct NewEvent{
    int32_t swCurrentState;
    int32_t Event;
};

union logtype{
    struct stateChange state_change;
    struct NewEvent new_event;
    struct stateError state_error;
    struct _ErrorCode error_code;
};

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*****************************************************************************
  2 Macro definitions
*****************************************************************************/

/**
 * Return value from FSM if the event doesn't have an associated handler.
 * @sa UFSM_HandleEvent
 */
#define UFSM_EVENT_NOT_HANDLED ( 0x578FFFF )

/**
 * Return value from FSM if the event had an associated handler.
 * @sa UFSM_HandleEvent
 */
#define UFSM_EVENT_HANDLED ( 0 )

/**
 * Retun value from an event handler to the FSM if the handler doesn't want to
 * change the state.
 *
 * @note
 *  The value is chosen as: 5= S, 7 =T, 8 = eight/ate => 578 = STATE
 *  0xFFFF etc are avoided as they are used in too many other places.
 *
 * @sa UFSM_HandleEvent
 */
#define UFSM_REMAIN_IN_STATE ( 0x5780000 )

/**
 * Return a error code from an event handler to UFSM_HandleEvent
 * UFSM_HandleEvent will propagate the value to its client.
 * An FSM will remain in ERROR state until the error handler returns a new
 * state or UFSM_SetState is called.
 *
 * @note
 *  The value is chosen as: 5= S, 7 =T, 8 = eight/ate => 578 = STATE
 *  0xFFFF etc are avoided as they are used in too many other places.
 *
 * @sa UFSM_HandleEvent
 */
#define UFSM_ERROR_STATE ( 0x578DEAD )

/**
 * Return value from an event handler to the FSM if the handler wants
 * to send it to the children
 */
#define UFSM_FORWARD_TO_CHILD ( 0x00010000 )

/**
 * Event is passed from UFSM_RegisterFsm() to pfInitHandler if
 * the parameter is used.
 */
#define UFSM_CREATE_EVENT 0

/**
 * Event is passed from UFSM_KillFsm() to pfInitHandler if the
 * parameter was used when creating the FSM.
 */
#define UFSM_KILL_EVENT 1

/**
 * Event is passed from UFSM_RegisterFsm() to pfInitHandler if
 * the parameter is used.
 */
#define UFSM_ADD_EXPORT_EVENT 2
#define UFSM_ADD_EXTERN_EVENT 2

/**
 * Fuction identifyer for an even that is expected but not want to be handled.
 *
 * No function will be called for handling the event but
 * UFSM_HandleEvent() will still report @ref UFSM_EVENT_HANDLED.
 */
#define UFSM_IGNORE_EVENT ((UFSM_EVENT_HANDLER)1)

/**
 * UFSM Handler that will ignore pushed events from children
 *
 * This is used to prevent pushing of events to the caller of the top FSM(s)
 *
 * hParent in the top FSM EXTERN_STRU shall be set to UFSM_IGNORE_PUSH_EVENT
 */
#define UFSM_IGNORE_PUSH_EVENT ((UFSM_Handle_t)NULL)

#ifdef _MSC_VER

/**
 * Add an default handler to a state.
 */
#define UFSM_EVENT_ACTION_DEFAULT_HANDLER(handler) {handler, 0, #handler, NULL}

/**
 * Macro to add an event action.
 */
#define UFSM_EVENT_ACTION_ADD(handler, event) {handler, event, #handler, #event}

/**
 * Closing a action table.
 */
#define UFSM_EVENT_ACTION_TERMINATE() {NULL, 0, NULL, NULL}

#else

#define UFSM_EVENT_ACTION_DEFAULT_HANDLER(handler) {handler, 0}
#define UFSM_EVENT_ACTION_ADD(handler, event) {handler, event}
#define UFSM_EVENT_ACTION_TERMINATE() {NULL, 0}

#endif

/**
 * Adding a child to a state.
 */
#define UFSM_CHILD_ADD(child,child_param) {child, child_param}

/**
 * Closing a child table.
 */
#define UFSM_CHILD_TERMINATE() {NULL, NULL}

#ifdef _MSC_VER
/**
 * Adding a state to a state machine table.
 */
#define UFSM_STATE_ADD(state,event_table,child_table)   \
    {state, event_table, child_table, #state}
#else
#define UFSM_STATE_ADD(state,event_table,child_table)   \
    {state, event_table, child_table}
#endif

/*****************************************************************************
  6 STRUCT declarations
*****************************************************************************/
/**
 * Return type for a event handler.
 *
 * It shall be a valid state in the FSM which the function belongs to or
 * UFSM_REMAIN_IN_STATE if the handler want to remain in the current
 * state. The event handler can also return UFSM_ERROR_STATE in case
 * of an unhandled error.
 *
 * @sa UFSM_REMAIN_IN_STATE, UFSM_ERROR_STATE
 */
typedef int32_t UFSM_STATE_T;

/**
 * Protorype for a function that should be registerd together with an
 * event in UFSM_PushEvent(). It will be qalled in case of that the
 * FSM is killed or UFSM_FlushEventQueue() is called.
 *
 * The purpos for the cleaner is to give the application a chanse to
 * free memory if the event is not used when the FSM is killed.
 */
typedef void (*UFSM_EVENT_CLEANER)(void *, int32_t);

/**
 * Event handler interface.
 *
 * Every event handler takes three arguments. The first is an instance
 * pointer initialized by the inithandler passed to
 * UFSM_Register().
 * Second and third arguments are the second and third
 * parameter passed to UFSM_HandleEvent().
 */
typedef UFSM_STATE_T (*UFSM_EVENT_HANDLER)( void*, void*, int32_t );

/**
 * Structure that connects an event with a specific handler.  Every
 * state is built up by a table of events and event handlers. If the
 * first element in the table is not null the UFSM_HandleEvent() will
 * call this handler if an event doesn't match any event in the table,
 * it will act as a default handler.  The table shall be terminated
 * with a "{null, 0}" element.
 *
 * If FSM_HandleEvent() cant find a handler for a given event it will
 * return @ref UFSM_EVENT_NOT_HANDLED
 *
 * @sa struct STATE_TABLE_STRU
 */
typedef struct
{
    /**
     * Pointer to the function that will be called when swEvent
     * event is passed to UFSM_HandleEvent when the FSM is in the state
     * desrcibed by an UFSM_EVENT_ACTION_STRU
     */
    UFSM_EVENT_HANDLER pfEventHandler;
    /**
     * Matching event number that will cause pfEvnentHandler to be called.
     */
    int32_t swEvent;
#ifdef _MSC_VER
    /** eventhandler name expanded by macro Used to make pretty print in UT/ST */
    char *strEventHandler;
    /** Event namne expanded by macro. Used to make pretty print in UT/ST. */
    char *strEvent;
#endif
}UFSM_EVENT_ACTION_STRU;

/**
 * @brief
 * Basic type for a state in a state machine.
 * The state machine is defind as a table of states.
 * The first state shall be 0 and then incresed by
 * one for each element in the table.
 *
 * @code
 UFSM_EVENT_ACTION_STRU state_0_actions [] = {
   { NULL, 0},
   { h1s0, event1},
   { h2s0, event2},
   { NULL, 0}
   };

 UFSM_EVENT_ACTION_STRU state_2_actions[] = {
   { default_handler_s2, 0},
   { NULL, 0}
   };

 UFSM_EVENT_ACTION_STRU state_3_actions [] = {
   { default_handler_s3, 0},
   { h1s3, event1},
   { h2s3, event2},
   { h3s3, event3},
   { NULL, 0}
   };

 UFSM_STATE_TABLE_STRU my_FSM_table[] ={
   {0, state_0_actions},
   {1, NULL},
   {2, state_2_actions},
   {3, state_3_actions},
   {4, NULL},
   {5, NULL}
 };
 * @endcode
 *
 * If a state doesn't contain a UFSM_EVENT_ACTION_STRU it is considered a
 * exit state. If an event handler returns an exit state the FSM will be
 * deleted and UFSM_HandleEvent() will returnthe exit state.
 *
 * The number of elements in the table shall be the same as swMaxState
 * passed to UFSM_Register()
 *
 * @sa struct UFSM_EVENT_ACTION_STRU UFSM_Register
*/
typedef struct UFSM_STATE_TABLE
{
    /** @brief State ID */
    const int32_t swState;
    /** @brief Pointer to event handler table for the given state. An
     * exit state is defined as a state with no event table connected
     * to it. */
    UFSM_EVENT_ACTION_STRU const *pstEvents;
}UFSM_STATE_TABLE_STRU;

/*****************************************************************************
  8 OTHER declarations
*****************************************************************************/
/**
 * FSM Handle.
 * Returnd by UFSM_Register() and shall be handed as an id to all further
 * calls to the FSM engine.
 *
 * @note The handle that shall be passed to UFSM_Error() and
 * UFSM_GetError() is not the same handle. The handle passed to the
 * init handler during initialization shall be used for calls to these
 * APIs.
 *
 * @sa UFSM_Register
 */
typedef struct UFSM_HANDLE_STRU *UFSM_Handle_t;

typedef struct UFSM_FSM UFSM_FSM_STRU;
/* function prototype for getting handle and extern struct to child */
typedef void (*UFSM_GET_CHILD)(void*, UFSM_Handle_t**, void**);
/* function prorotype for getting register parameters */
typedef void (*UFSM_GET_CHILD_PARAMS)(UFSM_FSM_STRU*);

/* child definition */
typedef struct UFSM_CHILD
{
    UFSM_GET_CHILD getChild;
    UFSM_GET_CHILD_PARAMS getChildParameters;
}UFSM_CHILD_STRU;

/* state table including children */
typedef struct UFSM_STATE_DEF
{
    /** @brief State ID */
    const int32_t swState;
    /** @brief Pointer to event handler table for the given state. An
     * exit state is defined as a state with no event table connected
     * to it. */
    UFSM_EVENT_ACTION_STRU const *pstEvents;
    /* child definition */
    UFSM_CHILD_STRU const *pstChildren;
#ifdef _MSC_VER
    /** State name expanded by macro. Used to make pretty print in UT/ST */
    char *strState;
#endif

}UFSM_STATE_DEF_STRU;

/* register parameter struct */
typedef struct UFSM_FSM
{
    UFSM_STATE_DEF_STRU const *pstStateTable;
    int32_t swMaxState;
    char *name;
    size_t sizeUserSpace;
    UFSM_EVENT_HANDLER pfInitHandler;
    int32_t swLogId;
    size_t extraStorage;
    struct UFSM_LogFunctions *pstLogFunctions;
} UFSM_FSM_STRU;



/*****************************************************************************
  10 Function declarations
*****************************************************************************/

/**
   Register a state machine in FSM.
   @param[in] pastStateTable  Table with states and enent tables.
   @param[in] swMaxState      Number of states in state table.

   @param[in] name            Null terminated string with an identifyer to the FSM,
                              mainly used for debug purpose.

   @param[in] sizeInstancePtr Size of the instance pointer passed to event handlers.

   @param[in] pfInitHandler   Function called after the user space is allocated.
                              Called again before deallocation of user space when FSM
                              is killed.
                              The init handler will be called as if UFSM_HandleEvent()
                              was called with the created FSM as an argument that should
                              be passed to the handler i.e. the init hanler will get the
                              fsm as its second argument. That could be used for storing
                              a reference to the FSM in the user space e.g:
                              @code
                              init_handler(void* my_space, void *fsm, int32_t swEvent )
                              {
                                if (UFSM_CREATE_EVENT == swEvent)
                                {
                                  my_space->my_state_mashine = fsm;
                                  return 0;
                                }
                                else if(UFSM_KILL_EVENT == swEvent)
                                return 0;
                              }
                              @endcode

   @param[in] pstExport       Pointer to export struct which is used for export of data to the
                              register of the FSM.

   @note The fsm handler passed to the init handler is not the same as
         the one returned to the FSM creator and is to be used from
         inside the state machine. It can not be used for calls to
         UFSM_HandleEvent() but shall be used in calles to
         UFSM_Error() and UFSM_GetError().

   @return    A handle that identify the registered machine.
*/
UFSM_Handle_t UFSM_Register( UFSM_STATE_TABLE_STRU const *pastStateTable,
                             int32_t swMaxState,
                             char *name,
                             size_t sizeInstancePtr,
                             UFSM_EVENT_HANDLER pfInitHandler,
                             void* pstExport);

/**
 * Registers an Errorhandler to an FSM. The error handler has the same
 * interrface as a normal Event handler and shall return the same type
 * of value. If the error handler can handle an error it is ok to
 * return a new state or @ref UFSM_REMAIN_IN_STATE otherwise the error
 * handler shall return @ref UFSM_ERROR_STATE. In that case UFSM will
 * kill the state machine. If UFSM_Error() was called the error
 * handler is called directly with the same paramerers as the latest
 * call to the event handler. Giving the application a chance to clean
 * up. During this run the UFSM_GetError() will return the error code
 * that UFSM_Error() was reprting after that UFSM_GetError() will
 * report 0.
 *
 * If an event handler returns @ref UFSM_ERROR_STATE the error handler
 * will be called with its second and third arguments set to zero.
 *
 * @param[in] pstFsm          Pointer to a handle from UFSM_RegisterFsm.
 * @param[in] pfErrorHandler  Function that is called when an event handler
                              returns UFSM_ERROR_STATE and then as long as
                              the FSM remains in this state.
 */
void UFSM_RegisterErrorHandler( UFSM_Handle_t *pstFsm,
                                UFSM_EVENT_HANDLER pfErrorHandler);

/**
  @brief Calls the registered event handler for the specific event in
  current state.

  This function is the core in the FSM engine everything else is built
  up to support this funtion.

  UFSM_HandleEvent will call the specific event handler that is
  registered to handle the event in the current state. After that it
  will update the state to the return value from the event handler and
  return the new state to the caller. If the event handler calls
  UFSM_Error() or return @ref UFSM_ERROR_STATE it will call the error
  handler.

  If an event handler returns @ref UFSM_ERROR_STATE or a state that
  is outside the state table, UFSM_HandleEvent will call the error handler without
  the second and third parameter and UFSM_GetError() will report zero.

  If the event handler called UFSM_Error() it will end the current
  execution path and call the error handler with the same argument as
  the event handler was called with. UFSM_GetError() will return the the
  second parameter passed to UFSM_Error(). It is recommended that
  the application has unique error values for easier implementation of
  error handling.

  If the event handler returns an state without an event table or if
  the error handler returns @ref UFSM_ERROR_STATE or any state outside
  the event table the FSM will be deleted. And the init/exit handler
  will be called with @ref UFSM_KILL_EVENT as the event.

  UFSM_HandleEvent and all other calls to UFSM takes a pointer to a
  UFSM_Handle_t as input instead of a UFSM_Handle_t. That makes it
  possible for UFSM_Register and UFSM_Kill() to remove the handle from
  the caller. The other APIs do it of consistency reason.

  @code
  UFSM_Handle_t my_life;
  my_life = UFSM_Register (my_FSM_table, MY_BUTT, NULL, "", 0)

  new_state = UFSM_HandleEvent(&my_life, birthday_msg, BIRTHDAY_GREETINGS )
  @endcode

  UFSM_HandleEvent has killed my_life if the new state is a exit
  state, so after the call my_life might be zero.

  @param[in] pstFsm Pointer to a handle from UFSM_Register().
  @param[in] pMsg Argument passed to the event handler. This will be
                  the second parameter passed to the event handler.
  @param[in] swEvent Event to match in the EVENT_ACTION_STRU table for the
             current state.
  @return    New state in the FSM on succesful exit. If the new state
             is an exit state the FSM will be deleted. It is the applications
             responsibility to know if the state is an exit state or not.
             No more calls can be done to and FSM that has been deleted.
             UFSM_EVENT_NOT_HANDLED If there was no handler and no default handler
                                    registered in current state.
             UFSM_ERROR_STATE       If case of error. The FSM will be deleted in this state.
*/
int32_t UFSM_HandleEvent(UFSM_Handle_t *pstFsm,
                           void          *pMsg,
                           int32_t      swEvent );

/**
 * Called from any subrutine to an event handler to reprot an error.
 *
 * @param[in] pstFsm      Pointer to a handle passed to the init handler during the registraion of the FSM.
 * @param[in] swErrorCode Spesific error number, can be requested from the error handler
 *                        by a call to UFSM_GetError()
 *
 * @note Calls to UFSM_Error() and UFSM_GetError() shall use the fsm handle passed to
 * the init handler. Not the handle returned by UFSM_Register()
 *
 * @note Function will not return in a normal manner, instead execution will be passed
 * to the error handler and then the UFSM_HandleEvent() will return.
 *
 * @warning UFSM_Error can only be used from the event handler and its
 * sub functions. Calling UFSM_Error after that UFSM_HandleEvent() has
 * returned leads to undefined behavior and calling UFSM_Error with a
 * FSM handle from a higher ranking FSM do so too. It should only be
 * used with a handle to the current and closest FSM.
 *
 * @sa UFSM_GetError
 */
void UFSM_Error(UFSM_Handle_t *pstFsm, int32_t swErrorCode);

/**
 * Used by the error handler to get the error code reported by the
 * application.
 *
 * @note UFSM_Error() and UFSM_GetError() shall use the fsm passed to
 * the init handler. Not the handle returned by UFSM_Register()
 *
 * @param[in] pstFsm      Pointer to a handle passed to the init handler during the registraion of the FSM.
 * @return The error code reported by a call to UFSM_Error() untill UFSM_HandleEvent()
 *         returns, after that it will report 0.
 *
 * @sa UFSM_Error
 */
int32_t UFSM_GetError(UFSM_Handle_t *pstFsm);

/**
  Returns the current state.
  @param[in] pstFsm Pointer to a handle from UFSM_RegisterFsm.
  @return    Current state
*/
int32_t UFSM_GetState(UFSM_Handle_t *pstFsm);

/**
   Used to manualy kill or delete the FSM independently of the state or
   status of the FSM. The API can not be used on an already killed
   FSM, or an FSM that has returned an exit state.

   @param[in] pstFsm Pointer to a handle from UFSM_RegisterFsm.

   @return    .
*/
void UFSM_Kill(UFSM_Handle_t *pstFsm);

/**
 * Add an event on the state machines event qeue
 *
 * @note
 * This API should use the fsm handle that is published in inithandlern.
 *
 * @param[in] pstFsm      Pointer to a handle passed to the init
 *                        handler during the registraion of the FSM.
 * @param[in] pMsg        Pointer to a user defined message.
 * @param[in] swEvent     Event ID to store.
 * @param[in] pfEventCleaner  Function used to clean up the pMsg pointer
 *                            in case that the FSM die and that there
 *                            is events in the queue.
 */
void UFSM_PushEvent(UFSM_Handle_t *pstFsm, void * pMsg, int32_t swEvent, UFSM_EVENT_CLEANER pfEventCleaner);

/**
 * Get an event from the event queue.
 *
 * @param[in] pstFsm    Pointer to a handle from UFSM_RegisterFsm.
 * @param[out] pMsg    Pointer to a messege pointer. The function will fill in the value.
 * @param[out] pswEvent Pointer to a event. The function will fill in the value.
 *
 * @return Zero if the queue was empty and non zero if it manage to take out a message from the queue.
 */
int32_t UFSM_PopEvent(UFSM_Handle_t *pstFsm, void **pMsg, int32_t *pswEvent);

/**
 * Empty the event gueue and call the pfEventCleaner for each event in the queue.
 * @param[in] pstFsm Pointer to a handle from UFSM_RegisterFsm.
 */
void UFSM_FlushEventQueue(UFSM_Handle_t *pstFsm);

/**
  @brief Calls the registered event handler for the specific event in
  current state.

  This function is the core in the FSM engine everything else is built
  up to support this funtion.

  If the FSM handle is not initiated UFSM_Register() will be called.

  UFSM_Process will call the specific event handler that is
  registered to handle the event in the current state. After that it
  will update the state to the return value from the event handler and
  return UFSM_EVENT_HANDLED to the caller. If the event handler calls
  UFSM_Error() or return @ref UFSM_ERROR_STATE it will call the error
  handler.

  If no event handler is present the event will be sent to the children.

  If an event handler returns @ref UFSM_ERROR_STATE or a state that
  is outside the state table, UFSM_HandleEvent will call the error handler without
  the second and third parameter and UFSM_GetError() will report zero.

  If the event handler called UFSM_Error() it will end the current
  execution path and call the error handler with the same argument as
  the event handler was called with. UFSM_GetError() will return the the
  second parameter passed to UFSM_Error(). It is recommended that
  the application has unique error values for easier implementation of
  error handling.

  If the event handler returns an state without an event table or if
  the error handler returns @ref UFSM_ERROR_STATE or any state outside
  the event table the FSM will be deleted. And the init/exit handler
  will be called with @ref UFSM_KILL_EVENT as the event.

  UFSM_HandleEvent and all other calls to UFSM takes a pointer to a
  UFSM_Handle_t as input instead of a UFSM_Handle_t. That makes it
  possible for UFSM_Register and UFSM_Kill() to remove the handle from
  the caller. The other APIs do it of consistency reason.

  @param[in] ppstFsm Pointer to a handle
  @param[in] GetParameters pointer to function to get FSM parameters for
                           registration
  @param[in] pMsg Argument passed to the event handler. This will be
                  the second parameter passed to the event handler.
  @param[in] swEvent Event to match in the EVENT_ACTION_STRU table for the
                     current state.
  @return    UFSM_EVENT_HANDLED on succesful exit. If the new state
             is an exit state the FSM will be deleted. No more calls can be
             done to and FSM that has been deleted.
             UFSM_EVENT_NOT_HANDLED If there was no handler and no default handler
                                    registered in current state, and no children, or
                                    no chidren with handler.
             UFSM_ERROR_STATE       If case of error. The FSM will be deleted in this state.
 */
int32_t UFSM_Process(UFSM_Handle_t *ppstFsm,
                     void (*GetParameters)(UFSM_FSM_STRU*),
                     void *Extern,
                     void *pMsg,
                     int32_t swEvent);

struct UFSM_LogFunctions
{
    /**
     * Called when UFSM_HandleEvent() recives a new event.
     */
    int (*pfLogEvent)(void * pWorld, void *logEntry, int32_t swCurrentState, int32_t swEvent);

    /**
     * called when the FSM update to the new state returned by the event handler.
     */
    int (*pfLogStateChange)(void * pWorld, void *logEntry, int32_t swCurrentState, int32_t uwNewState);

    /**
     * Called when an event handler returned @ref UFSM_ERROR_STATE
     */
    int (*pfLogError)(void * pWorld, void *logEntry, int32_t swCurrentState, int32_t swErrorCode);

    /**
     * Called when an event handler return a state that is bigger than
     * the biggest registerd state.
     */
    int (*pfLogErrorState)(void * pWorld, void *logEntry, int32_t swCurrentState, int32_t uwNewState);
};

/**
 * Function for installing customized loghandlers.
 *
 * @param[in] pstFsm  Pointer to a handle from UFSM_RegisterFsm.
 * @param[in] swLogId Log Id to identify
 * @param[in] LogEvent pointer to a log function.
 */
void UFSM_LogControl( UFSM_Handle_t *pstFsm,
                      int32_t swLogId,
                      size_t extraStorage,
                      struct UFSM_LogFunctions *pstLogFunctions);


#ifdef _MSC_VER
/* Functions used for system test and unit test only. */
int32_t UFSM_ProcessInternal(UFSM_Handle_t *phFsm,
                     void (*GetParameters)(UFSM_FSM_STRU*),
                     void *Extern,
                     void *pMsg,
                     int32_t swEvent);

extern int32_t UFSM_Test_GetCurrentState(UFSM_Handle_t fsm);
extern void UFSM_Test_SetCurrentState(UFSM_Handle_t fsm,int32_t state);
extern void UFSM_Test_SetMagic(UFSM_Handle_t fsm,int32_t magic);
extern char* UFSM_Test_getName(UFSM_Handle_t fsm);
extern void* UFSM_Test_getUserArea(UFSM_Handle_t fsm);
/**
  Sets state in the fsm.
  @param[in] pstFsm Pointer to a handle from UFSM_RegisterFsm.
  @param[in] swState New state in the fsm.

  @note If the new state is not valid the function will call the error handler.

  @return The state that is given if the state exist in the FSM. or
          UFSM_ERROR_STATE. If the state is outsid the FSM and the
          error handler can't take care of the problem. The FSM will
          be deleted if the new state is a errorstate or if the error
          handler can't handle a value that is outside the FSM states.

*/
int32_t UFSM_SetState(UFSM_Handle_t *pstFsm,
                        int32_t swState);


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INCLUSION_GUARD_UFSM_H */
