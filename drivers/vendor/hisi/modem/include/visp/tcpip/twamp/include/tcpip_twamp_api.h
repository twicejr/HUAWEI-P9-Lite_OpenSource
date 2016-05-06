/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                            tcpip_twamp_api.h
*
*  Project Code:
*   Module Name: TWAMP API
*  Date Created: 2013-03-13
*        Author:
*   Description: Contains the TWAMP Client and the Reflector API(s)
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE                            NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2013-03-13                                             Create
*
*******************************************************************************/
#ifndef __TCPIP_TWAMP_API_H__
#define __TCPIP_TWAMP_API_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TWAMP_Init(ULONG ulTWAMPTaskPri);
* @endcode
*
* @par Description
* Initializes the TWAMP Module, Initializes both TWAMP Client and the TWAMP Reflector.
*
* @param[in] ulTWAMPTaskPri Indicates the TWAMP task Priority.[]
* @param[out]   []
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned []
*
* @type API Type
* Synchronous.
*
* @par Dependency
* tcpip_twamp_api.h
*
* @par Note
* \n
*
*
*/
extern ULONG TCPIP_TWAMP_Init(ULONG ulTWAMPTaskPri);


/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TCPIP_TWAMP_SetReflGConfig(TCPIP_TWAMP_REFL_GCONFIG_S *pstReflGConfig)
* @endcode
*
* @par Description
* Configures the Reflector with the global Parameters, these are the default parameters
* for each of the reflectors that will be created after calling this API.  It is an optional API
* if user doesnot call this API then the default parameters will be taken for all the reflectors.
* User has an option of overriding the global values in the start Reflector API.
*
* @param[in] pstReflConfig Contains the Reflector Global configuration.[]
* @param[out]   []
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned  []
*
* @type API Type
* Synchronous.
*
* @par Dependency
* tcpip_twamp_api.h
*
* @par Note
* \n
*
* @par Related Topics
* TCPIP_TWAMP_GetReflGConfig
*
*/
extern ULONG TCPIP_TWAMP_SetReflGConfig(TCPIP_TWAMP_REFL_GCONFIG_S *pstReflGConfig);

/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TCPIP_TWAMP_GetReflGConfig(TCPIP_TWAMP_REFL_GCONFIG_S *pstReflGConfig)
* @endcode
*
* @par Description
* Retreives the  values which are configured using the  TCPIP_TWAMP_SetReflGConfig API.
* If user calls this API without setting the global value then Default values will be returned.
*
* @param[in]  []
* @param[out] pstReflConfig Contains the Reflector global configuration []
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned  []
*
* @type API Type
* Synchronous.
*
* @par Dependency
* tcpip_twamp_api.h
*
* @par Note
* \n
*
* @par Related Topics
* TCPIP_TWAMP_SetReflGConfig
*
*/
extern ULONG TCPIP_TWAMP_GetReflGConfig(TCPIP_TWAMP_REFL_GCONFIG_S *pstReflGConfig);

/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TCPIP_TWAMP_StartReflector(ULONG ulResponderId, TCPIP_TWAMP_REFL_CONFIG_S *pstReflConf)
* @endcode
*
* @par Description
* Initialize the host as role of server and session-reflector to acknowledge the TCP connections.
* The values which are passed in the pstReflConf will be used for the Reflector creation, If 0 is passed
* then it will refer the global configuration.
* It is an Asynchrounous API it will only do the the basic validation and post a event to the core module
* to create the Reflector, It will then return success to the user.
*
* @param[in] ulResponderId Contains the Responder Id[]
* @param[in] pstReflConf Contains the Reflector Configuration[]
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned  []
*
* @type API Type
* Asynchronous.
*
* @par Dependency
* tcpip_twamp_api.h
*
* @par Note
* Using the Log file user will be knowing the whether the creation of the Reflector fails or not.
*
* The option Parameters should be validated and then passed by the user VISP does not validate any parameters.
*Passing of invalid value may result in improper behavior.
*
* If any Set socket option fails then the error will be ignored and it will parse further options.
*
* Only non-zero values for VRF(ulVrfIndex) will be considered.
*
* @par Related Topics
* TCPIP_TWAMP_StopReflector
*
*/
extern ULONG TCPIP_TWAMP_StartReflector(ULONG ulResponderId, TCPIP_TWAMP_REFL_CONFIG_S *pstReflConf);



/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TCPIP_TWAMP_StopReflector(ULONG uResponderId);
* @endcode
*
* @par Description
* de-Initialize the host as role of server and session-reflector,
* close all control connections and sessions and release all resources.
* It is an Asynchrounous API it will only do the the basic validation and post a event to the core module
* to stop the Reflector, It will then return success to the user.
*
* @param[in] uResponderId Responder Id to identify the particular reflector[]
* @param[out] []
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned  []
*
* @type API Type
* Asynchronous.
*
* @par Dependency
* tcpip_twamp_api.h
*
* @par Note
* Using the Log file user will be knowing the whether the stopping of the Reflector is success or not.
*
* @par Related Topics
* TCPIP_TWAMP_StartReflector
*
*/
extern ULONG TCPIP_TWAMP_StopReflector(ULONG ulResponderId);

/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TCPIP_TWAMP_OpenReflTestSessTable(ULONG uResponderId, ULONG *pulWaitListHandle);
* @endcode
*
* @par Description
* Opens the Reflector Test session table associated with the particular reflector.
*
* @param[in] uResponderId Responder Id to identify the particular reflector[]
* @param[out] pulWaitListHandle  Waitlist handle[]
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned  []
*
* @type API Type
* Synchronous.
*
* @par Dependency
* tcpip_twamp_api.h
*
* @par Note
* \n
*
* @par Related Topics
* TCPIP_TWAMP_GetReflTestSessInfo
* TCPIP_TWAMP_CloseReflTestSessTable
*
*/
extern ULONG TCPIP_TWAMP_OpenReflTestSessTable(ULONG ulResponderId, ULONG *pulWaitListHandle);

/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TCPIP_TWAMP_GetReflTestSessInfo(ULONG uResponderId, ULONG ulEntryWaitList,
*              TCPIP_TWAMP_REFL_SESS_S *pstRefTestSessionInfo);
* @endcode
*
* @par Description
* Retrieves the Test Session Information using the waitlist handle which was
* opened using the TCPIP_TWAMP_OpenReflTestSessTable API
*
* @param[in] uResponderId Responder Id to identify the particular reflector[]
* @param[in] ulEntryWaitList Waitlist handleI[]
* @param[out] pstTestSessionInfo Test SessionInfo[]
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned  []
*
* @type API Type
* Synchronous.
*
* @par Dependency
* tcpip_twamp_api.h
*
* @par Note
* \n
*
* @par Related Topics
* TCPIP_TWAMP_OpenReflTestSessTable
* TCPIP_TWAMP_CloseReflTestSessTable
*
*/
extern ULONG TCPIP_TWAMP_GetReflTestSessInfo(ULONG ulResponderId, ULONG ulEntryWaitList,
                       TCPIP_TWAMP_REFL_SESS_S *pstTestSessionInfo);

/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TCPIP_TWAMP_CloseReflTestSessTable(ULONG ulWaitListHandle);
* @endcode
*
* @par Description
* Closes the wailtlist handle ulWaitListHandle whcih was opened using the TCPIP_TWAMP_OpenReflTestSessTable
*
* @param[in] ulWaitListHandle Waitlist handle[]
* @param[out] []
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned []
*
* @type API Type
* Synchronous.
*
* @par Dependency
* tcpip_twamp_api.h
*
* @par Note
* \n
*
* @par Related Topics
* TCPIP_TWAMP_OpenReflTestSessTable
* TCPIP_TWAMP_GetReflTestSessInfo
*
*/
extern ULONG TCPIP_TWAMP_CloseReflTestSessTable(ULONG ulWaitListHandle);


/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TCPIP_TWAMP_GetReflStats(ULONG uResponderId, TCPIP_TWAMP_REFL_STATS_S *pstStats)
* @endcode
*
* @par Description
* Retrieves the Reflector statistics for the coresponding Responder ID.
*
* @param[in] uResponderId Responder Id to identify the particular reflector[]
* @param[out] pstStats Reflector stats[]
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned []
*
* @type API Type
* Synchronous.
*
* @par Dependency
* tcpip_twamp_api.h
*
* @par Note
* \n
*
* @par Related Topics
* TCPIP_TWAMP_ClearReflStats
*
*/
extern ULONG TCPIP_TWAMP_GetReflStats(ULONG ulResponderId, TCPIP_TWAMP_REFL_STATS_S *pstStats);


/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TCPIP_TWAMP_ClearReflStats(ULONG uResponderId)
* @endcode
*
* @par Description
* Clears the Reflector statistics for the coresponding Responder ID.
*
* @param[in] uResponderId Responder Id to identify the particular reflector[]
* @param[out] []
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned []
*
* @type API Type
* Synchronous.
*
* @par Dependency
* tcpip_twamp_api.h
*
* @par Note
* \n
*
* @par Related Topics
* TCPIP_TWAMP_GetReflStats
*
*/
extern ULONG TCPIP_TWAMP_ClearReflStats(ULONG ulResponderId);


/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TCPIP_TWAMP_ConnectCtrlClient(ULONG ulClientId, TCPIP_TWAMP_CTRLCLIENT_CONFIG_S *pstCtrlConf);
*
* @endcode
*
* @par Description
* Initialize the host as role of client and session-sender to initiate the TCP connection.
* It is an Asysnchronous API which will do the basic validation and post the event to the core
* module to do the TWAMP Connection with the TWAMP Reflector.
* It will notifiy the control connection status using the hook which is registered using the
* TCPIP_TWAMP_RegClientCtrlHook
*
* @param[in] ulClientId Client Id []
* @param[in] pstCtrlConf Configuration to be used for the connection to the reflector[]
* @param[out] []
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned []
*
* @type API Type
* Asynchronous.
*
* @par Dependency
* tcpip_twamp_api.h
*
* @par Note
* 1) If the establishment of the control connection closes then it will cleanup the resouces and notify to the user
* about the failure and then again it will try to establish the connection, this will continue till the connection is
* successful or user closes the connection using the TCPIP_TWAMP_CloseCtrlClient API.
*
* 2) The option Parameters should be validated and then passed by the user VISP does not validate any parameters.
* Passing of invalid value may result in improper behavior.
*If any Set socket option fails then the error will be ignored and it will parse further options.
*
* 3) In the Standby board the timestamp values should not be used for any processing as this value is not getting updated and also the
*     state is not getting updated, only the success the core control session is downloaded to the standby board.
* 4) Only non-zero values for VRF(ulVrfIndex) will be considered.
*
* @par Related Topics
* TCPIP_TWAMP_CloseCtrlClient
* TCPIP_TWAMP_RegClientCtrlHook
*
*/
extern ULONG TCPIP_TWAMP_ConnectCtrlClient(ULONG ulClientId, TCPIP_TWAMP_CTRLCLIENT_CONFIG_S *pstCtrlConf);

/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TCPIP_TWAMP_CloseCtrlClient(ULONG uClientId);
* @endcode
*
* @par Description
* Closes the control connection which was established using the TCPIP_TWAMP_ConnectCtrlClient API.
* It is an Asynchronous API it will post a event to the core module and then return success to the user.
* It will notify to the user about the statusign the using the hook which is registered using the TCPIP_TWAMP_RegClientCtrlHook.
*
* @param[in] uClientId Client Id []
* @param[out] []
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned []
*
*
* @type API Type
* Asynchronous.
*
* @par Dependency
* tcpip_twamp_api.h
*
* @par Note
* \n
*
* @par Related Topics
* TCPIP_TWAMP_ConnectCtrlClient
* TCPIP_TWAMP_RegClientCtrlHook
*
*/
extern ULONG TCPIP_TWAMP_CloseCtrlClient(ULONG ulClientId);

/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TCPIP_TWAMP_GetCtrlClientSessInfo (ULONG ulClientId,
*           TCPIP_TWAMP_CTRLCLIENT_SESS_S *pstCtrlSessInfo);
* @endcode
*
* @par Description
* Retrivies the control client session information for the coresponding the Client ID.
*
* @param[in] uClientId Client Id []
* @param[out] pstCtrlSessInfo Contains the session information []
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned []
*
* @type API Type
* Synchronous.
*
* @par Dependency
* tcpip_twamp_api.h
*
* @par Note
* \n
*
* @par Related Topics
*
*
*/
extern ULONG TCPIP_TWAMP_GetCtrlClientSessInfo (ULONG ulClientId,
           TCPIP_TWAMP_CTRLCLIENT_SESS_S *pstCtrlSessInfo);


/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TCPIP_TWAMP_ShowCtrlClientSessInfo (ULONG ulClientId);
* @endcode
*
* @par Description
* Displays the Control Client session information for the coresponding Client ID.
*
* @param[in] uClientId Client Id []
* @param[out] []
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned []
*
* @par Dependency
* tcpip_twamp_api.h
*
* @type API Type
* Synchronous.
*
* @par Note
* \n
*
* @par Related Topics
*
*
*/
extern ULONG TCPIP_TWAMP_ShowCtrlClientSessInfo (ULONG ulClientId);

/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
*  ULONG TCPIP_TWAMP_AddTwampSender(ULONG ulClientId, ULONG ulSenderId,
*   TCPIP_TWAMP_SENDER_CONF_S *pstSenderConf);
* @endcode
*
* @par Description
* TCPIP_TWAMP_AddTwampSender Initialize the host as role of session-sender to initiate the TWAMP test session.
* It is an Asynchronous API which will do basic validation and return success to the user, Internally it will post
* an event to the core module whic will do the test session establishment with the Reflector. User will be notified
* of the status of this using the hook which is registered using the TCPIP_TWAMP_RegSenderSessHook.
*
* @param[in] uClientId Client Id []
* @param[in] ulSenderId Contains the Sender Id[]
* @param[in] pstSenderConf Sender Configuration[]
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned []
*
* @type API Type
* Asynchronous.
*
* @par Dependency
* tcpip_twamp_api.h
*
* @par Note
* If the Control connection associated with the ulClientId is still IN PROGRESS then it
* will put the sender in the pending state till the Control connection is successful.
* If the control path has gone down , This API will not able to detect the Path.
* If the Socket recieves the fin then user will be notified about the same but it will
* not do contorl connection renegotiation.
*
* The ulPktSize in  TCPIP_TWAMP_SENDER_CONF_S *pstSenderConf should be either 0 or >=42
*
* \n
*
* @par Related Topics
* TCPIP_TWAMP_RegClientCtrlHook
*
*/
extern ULONG TCPIP_TWAMP_AddTwampSender(ULONG ulClientId,  ULONG ulSenderId,
    TCPIP_TWAMP_SENDER_CONF_S *pstSenderConf);


/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TCPIP_TWAMP_DelTwampSender(ULONG uClientId, ULONG uSenderId);
* @endcode
*
* @par Description
* TCPIP_TWAMP_DelTwampSender de-Initialize the host as role of session-sender, close TWAMP test sessions and release
* corresponding resources. It is an asynchronous API it will do the basic validation and returns success to the user.
*
* @param[in] uClientId Client Id []
* @param[in] uSenderId Sender Id[]
* @param[out][]
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned []
*
* @type API Type
* Asynchronous.
*
* @par Dependency
* tcpip_twamp_api.h
*
* @par Note
* \n
*
* @par Related Topics
* TCPIP_TWAMP_AddTwampSender
*
*/
extern ULONG TCPIP_TWAMP_DelTwampSender(ULONG ulClientId, ULONG ulSenderId);

/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TCPIP_TWAMP_GetTwampTestSessInfo(ULONG uClientId, ULONG uSenderId,
*    TCPIP_TWAMP_TEST_SESS_INFO_S *pstTestSessionInfo);
*
* @endcode
*
* @par Description
* TCPIP_TWAMP_GetTwampTestSessInfo Retrives the test session information for the coresponding
* Client ID and Sender ID.
*
* @param[in] uClientId Client Id []
* @param[in] uSenderId Sender Id[]
* @param[out]pstTestSessionInfo Session Info []
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned []
*
* @par Dependency
* tcpip_twamp_api.h
*
* @type API Type
* Synchronous.
*
* @par Note
* \n
*
* @par Related Topics
*
*
*/
extern ULONG TCPIP_TWAMP_GetTwampTestSessInfo(ULONG ulClientId, ULONG ulSenderId,
    TCPIP_TWAMP_TEST_SESS_INFO_S *pstTestSessionInfo);

/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TCPIP_TWAMP_ShowTwampTestSessInfo(ULONG uClientId, ULONG uSenderId);
* @endcode
*
* @par Description
* TCPIP_TWAMP_ShowTwampTestSessInfo Displays the test session information for the coresponding
* Client ID and Sender ID.
*
* @param[in] uClientId Client Id []
* @param[in] uSenderId Sender Id[]
* @param[out][]
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned []
*
* @type API Type
* Synchronous.
*
* @par Dependency
* tcpip_twamp_api.h
*
* @par Note
* \n
*
* @par Related Topics
*
*
*/
extern ULONG TCPIP_TWAMP_ShowTwampTestSessInfo(ULONG ulClientId, ULONG ulSenderId);

/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TCPIP_TWAMP_RegResponderCtrlHook(TCPIP_HOOK_TWAMP_REFL_FUNC pfnRefltHook);
* @endcode
*
* @par Description
* TCPIP_TWAMP_RegResponderCtrlHook Registers the Hook function to get the test session.
* Notifies about control connection and session states in responder side using this Hook Function
* and also notifies the event whic is of type TWAMP_RESPONDER_CTRL_STATE_E.
*
* @param[in] pfnRefltHook Hook details Id[]
* @param[out][]
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned []
*
* @type API Type
* Synchronous.
*
* @par Dependency
* tcpip_twamp_api.h
*
* @par Note
* \n
*
* @par Related Topics
*
*
*/
extern ULONG TCPIP_TWAMP_RegResponderCtrlHook(TCPIP_HOOK_TWAMP_REFL_FUNC pfnRefltHook);

/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TCPIP_TWAMP_RegClientCtrlHook(TCPIP_HOOK_TWAMP_CTRL_FUNC pfnCtrlHook);
* @endcode
*
* @par Description
* TCPIP_TWAMP_RegClientCtrlHook registers the hook function to get the control connection status notification.
* The states which are passed to the user in the hook function is of type TWAMP_SESS_STATE_E.
*
* @param[in] pfnCtrlHook Client Hook function Id[]
* @param[out][]
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned []
*
* @type API Type
* Synchronous.
*
* @par Dependency
* tcpip_twamp_api.h
*
* @par Note
* \n
*
* @par Related Topics
*
*
*/
extern ULONG TCPIP_TWAMP_RegClientCtrlHook(TCPIP_HOOK_TWAMP_CTRL_FUNC pfnCtrlHook);

/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TCPIP_TWAMP_RegSenderSessHook(TCPIP_HOOK_TWAMP_SESS_FUNC pfnSessHook);
* @endcode
*
* @par Description
* TCPIP_TWAMP_RegSenderSessHook registers the hook function to get the status on the on test
* session establishment. The states which are passed to the user in the hook function is of type TWAMP_SESS_STATE_E.
*
* @param[in] pfnSessHook test session Hook function Id[]
* @param[out][]
*
* @type API Type
* Synchronous.
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned []
*
* @par Dependency
* tcpip_twamp_api.h
*
* @par Note
* \n
*
* @par Related Topics
*
*
*/
extern ULONG TCPIP_TWAMP_RegSenderSessHook(TCPIP_HOOK_TWAMP_SESS_FUNC pfnSessHook);

/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* TCPIP_TWAMP_ReflNotifySessEvent(TCPIP_TWAMP_REFL_NOTIFY_S *pstSenderConf);
* @endcode
*
* @par Description
* Using this API user will notify the test session status, expiry of the Refwait time.
* The states which are notified are of the type TWAMP_REFL_EVENT_E.
*
* @param[in] uClientId Client Id []
* @param[in] uSenderId Sender Id[]
* @param[out][]
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned []
*
* @type API Type
* Asynchronous.
*
* @par Dependency
* tcpip_twamp_api.h
*
* @par Note
* VRF Index would be retirived from the Responder ID and same will be passed to the PPI so
* VRF Index passed by the user will be ignored.
* \n
*
* @par Related Topics
*
*
*/
extern ULONG TCPIP_TWAMP_ReflNotifySessEvent(TCPIP_TWAMP_REFL_NOTIFY_S *pstSenderConf);


/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* TCPIP_TWAMP_PPI_HookRegister(TCPIP_TWAMP_PPI_HOOK_S *pstHookFunc);
* @endcode
*
* @par Description
* Using This API user can Register PPI Hook functions to for TWAMP Module.
* The operation type enum is TWAMP_PPI_OPER_TYPE_E.
*
* @param[in] TCPIP_TWAMP_PPI_HOOK_S *pstHookFunc []
*
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned []
*
* @type API Type
* Asynchronous.
*
* @par Dependency
* tcpip_twamp_api.h
*tcpip_twamp_def.h
*
* @par Note
* 1) The API should be called before Twamp Initialization
* \n
*
* @par Related Topics
*
*
*/
extern ULONG TCPIP_TWAMP_PPI_HookRegister(TCPIP_TWAMP_PPI_HOOK_S *pstHookFunc);


/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TCPIP_TWAMP_GetReflConfig(ULONG ulResponderId, TCPIP_TWAMP_REFL_CONFIG_S *pstReflConf)
* @endcode
*
* @par Description
* Retrieves the Reflector Configuration for the Corresponding Responder ID.
*
* @param[in] ulResponderId Contains the Responder Id[]
* @param[OUT] pstReflConf Contains the Reflector Configuration[]
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned  []
*
* @type API Type
* Synchronous.
*
* @par Dependency
* tcpip_twamp_api.h
*
* @par Note
* Configured socket options wouldnot be returned to the user.
* 
*
* @par Related Topics
* TCPIP_TWAMP_StartReflector
*
*/
extern ULONG TCPIP_TWAMP_GetReflConfig(ULONG ulResponderId, TCPIP_TWAMP_REFL_CONFIG_S *pstReflConf);

/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TCPIP_TWAMP_SenderNotify(ULONG ulClientId,  ULONG ulSenderId, ULONG ulEvent)
* @endcode
*
* @par Description
* Retrieves the Reflector Configuration for the Corresponding Responder ID.
*
* @param[in] ulClientId Contains client Id of the main control connection[]
* @param[in]SenderId sender Id for test session for which the session should be renegotiated[]
* @param[in]ulEvent Event given by the user based on which the functionality will take place[

*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned  []
*
* @type API Type
* Synchronous.
*
* @par Dependency
* tcpip_twamp_api.h
* TWAMP_SENDER_EVENT_E
*
* @par Note
* 
*
* @par Related Topics
* TCPIP_TWAMP_AddTwampSender
*
*/
extern ULONG TCPIP_TWAMP_SenderNotify(ULONG ulClientId,  ULONG ulSenderId, ULONG ulEvent);

/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TCPIP_TWAMP_RegSystemFunc(TCPIP_TWAMP_SYS_HOOK_FUN_S *pstHookFunc)
* @endcode
*
* @par Description
* Register the user functions with the twamp module. If user passes NULL for any of the function then the default VOS function will be invoked.
* Following function registeration is supported
* VOS_Tm_Since1970
* VOS_Tm_Now
* VOS_Free
* VOS_Malloc
* VOS_T_Delete
* VOS_T_Create
*
* @param[in] pstHookFunc Hook functions[]
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned  []
*
* @type API Type
* Synchronous.
*
* @par Dependency
* 
*
* @par Note
* 1) The API should be called before Twamp Initialization
*
* @par Related Topics
* 
*
*/
extern ULONG TCPIP_TWAMP_RegSystemFunc(TCPIP_TWAMP_SYS_HOOK_FUN_S *pstHookFunc);


/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TCPIP_TWAMP_OpenCtrlSessTable(ULONG ulResponderId, UINTPTR *pulWaitListHandle)
* @endcode
*
* @par Description
* Open the handle for the Control sesion List for a particular Responder Id.
*
* @param[in] ULONG ulResponderId : Responder Id for Which the control session handle is needed
*@param[out] ULONG *pulWaitListHandle: out for the API(handle for Subsequent APIs)
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned  []
*
* @type API Type
* Synchronous.
*
* @par Dependency
* 
*
* @par Note
* \n
*
* @par Related Topics
* TCPIP_TWAMP_GetCtrlSessInfo
* TCPIP_TWAMP_CloseCtrlSessTable
*/
extern ULONG TCPIP_TWAMP_OpenCtrlSessTable(ULONG ulResponderId, UINTPTR *pulWaitListHandle);

/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TCPIP_TWAMP_GetCtrlSessInfo(ULONG ulResponderId, ULONG ulEntryWaitList,
*                       TCPIP_TWAMP_REFL_SESS_S *pstCtrlSessionInfo);
* @endcode
*
* @par Description
* Retrieves the Control Session Information using the waitlist handle which was
* opened using the TCPIP_TWAMP_OpenCtrlSessTable API
*
* @param[in] uResponderId Responder Id to identify the particular reflector[]
* @param[in] ulEntryWaitList Waitlist handleI[]
* @param[out] pstCtrlSessionInfo Control SessionInfo[]
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned  []
*
* @type API Type
* Synchronous.
*
* @par Dependency
* tcpip_twamp_api.h
*
* @par Note
* \n
*
* @par Related Topics
* TCPIP_TWAMP_OpenCtrlSessTable
* TCPIP_TWAMP_CloseCtrlSessTable
*
*/
extern ULONG TCPIP_TWAMP_GetCtrlSessInfo(ULONG ulResponderId, UINTPTR ulEntryWaitList,
                       TCPIP_TWAMP_REFL_SESS_S *pstCtrlSessionInfo);


/**
* @defgroup TWAMP
* @ingroups TWAMP
* @par Prototype
* @code
* ULONG TCPIP_TWAMP_CloseCtrlSessTable(ULONG ulWaitListHandle);
* @endcode
*
* @par Description
* Closes the wailtlist handle ulWaitListHandle which was opened using the TCPIP_TWAMP_OpenCtrlSessTable
*
* @param[in] ulWaitListHandle Waitlist handle[]
* @param[out] []
*
* @retval ULONG On Success [TWAMP_OK|]
* @retval ULONG On Failure  non Zero value will be returned []
*
* @type API Type
* Synchronous.
*
* @par Dependency
* tcpip_twamp_api.h
*
* @par Note
* \n
*
* @par Related Topics
* TCPIP_TWAMP_OpenCtrlSessTable
* TCPIP_TWAMP_GetCtrlSessInfo
*
*/
extern ULONG TCPIP_TWAMP_CloseCtrlSessTable(UINTPTR ulWaitListHandle);

#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */
#endif   /* end of __TCPIP_TWAMP_API_H__ */
