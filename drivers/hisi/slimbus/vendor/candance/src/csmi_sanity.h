/**********************************************************************
 * Copyright (C) 2014 Cadence Design Systems
 * All rights reserved.
 **********************************************************************
 * WARNING: This file is auto-generated using api-generator utility.
 *			Do not edit it manually.
 **********************************************************************
 * Cadence Core Driver for SLIMbus Manager Interface
 **********************************************************************/

/**
 * This file contains sanity API functions. The purpose of sanity functions
 * is to check input parameters validity. They take the same parameters as
 * original API functions and return 0 on success or EINVAL on wrong parameter
 * value(s).
 */


#ifndef _CSMI_SANITY_H_
#define _CSMI_SANITY_H_

#include <csmi.h>
#include <cdn_stdtypes.h>
#include <cdn_errno.h>

/**
 * Checks validity of parameters for function probe
 * @param[out] requiredMemory Required memory in bytes.
 * @param[in] config Driver and hardware configuration.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_ProbeSanity(const CSMI_Config* config, uint16_t* requiredMemory)
{
	if (config == NULL)
		return EINVAL;
	if (requiredMemory == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function init
 * @param[in] callbacks Event Handlers and Callbacks.
 * @param[in] config Specifies driver/hardware configuration.
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_InitSanity(void* pD, const CSMI_Config* config, CSMI_Callbacks* callbacks)
{
	if (pD == NULL)
		return EINVAL;
	if (config == NULL)
		return EINVAL;
	if (callbacks == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function isr
 * @param[in] pD Pointer to driver's private data object filled by init.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_IsrSanity(void* pD)
{
	if (pD == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function start
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_StartSanity(void* pD)
{
	if (pD == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function stop
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_StopSanity(void* pD)
{
	if (pD == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function destroy
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_DestroySanity(void* pD)
{
	if (pD == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function setInterrupts
 * @param[in] interruptMask SLIMbus Manager interrupt mask.
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_SetInterruptsSanity(void* pD, uint8_t interruptMask)
{
	if (pD == NULL)
		return EINVAL;




	return 0;
}
/**
 * Checks validity of parameters for function getInterrupts
 * @param[out] interruptMask Pointer to place where SLIMbus Manager interrupt mask will be written.
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_GetInterruptsSanity(void* pD, uint8_t* interruptMask)
{
	if (pD == NULL)
		return EINVAL;
	if (interruptMask == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function setDataPortInterrupts
 * @param[in] interruptMask Data Port interrupt mask.
 * @param[in] portNumber Data Port number. Valid value ranges from 0 to 63.
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_SetDataPortInterruptsSanity(void* pD, uint8_t portNumber, uint8_t interruptMask)
{
	if (pD == NULL)
		return EINVAL;


	if (portNumber > (63))
		return EINVAL;


	if (interruptMask > (63))
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function getDataPortInterrupts
 * @param[out] interruptMask Pointer to place where Data Port interrupt mask will be written.
 * @param[in] portNumber Data Port number. Valid value ranges from 0 to 63.
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_GetDataPortInterruptsSanity(void* pD, uint8_t portNumber, uint8_t* interruptMask)
{
	if (pD == NULL)
		return EINVAL;
	if (interruptMask == NULL)
		return EINVAL;


	if (portNumber > (63))
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function clearDataPortFifo
 * @param[in] portNumber Data Port number. Valid value ranges from 0 to 63.
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_ClearDataPortFifoSanity(void* pD, uint8_t portNumber)
{
	if (pD == NULL)
		return EINVAL;


	if (portNumber > (63))
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function
 * setPresenceRateGeneration
 * @param[in] enable If true Presence Rate Generation for specified Data Port will be enabled; if not then it will be disabled.
 * @param[in] portNumber Data Port number. Valid value ranges from 0 to 63.
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_SetPresenceRateGenerationSanity(void* pD, uint8_t portNumber, bool enable)
{
	if (pD == NULL)
		return EINVAL;


	if (portNumber > (63))
		return EINVAL;




	return 0;
}
/**
 * Checks validity of parameters for function
 * getPresenceRateGeneration
 * @param[out] enable Pointer to place where information about Presence Rate Generation will be written.
 * @param[in] portNumber Data Port number. Valid value ranges from 0 to 63.
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_GetPresenceRateGenerationSanity(void* pD, uint8_t portNumber, bool* enable)
{
	if (pD == NULL)
		return EINVAL;
	if (enable == NULL)
		return EINVAL;


	if (portNumber > (63))
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function assignMessageCallbacks
 * @param[in] msgCallbacks SLIMbus Messages Callbacks.
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_AssignMessageCallbacksSanity(void* pD, CSMI_MessageCallbacks* msgCallbacks)
{
	if (pD == NULL)
		return EINVAL;
	if (msgCallbacks == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function sendRawMessage
 * @param[in] messageLength Raw message length.
 * @param[in] message Pointer to raw message.
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_SendRawMessageSanity(void* pD, void* message, uint8_t messageLength)
{
	if (pD == NULL)
		return EINVAL;
	if (message == NULL)
		return EINVAL;


	if (messageLength < (CSMI_MESSAGE_MIN_LENGTH) || messageLength > (CSMI_MESSAGE_MAX_LENGTH))
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function sendMessage
 * @param[in] message Pointer to struct message.
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_SendMessageSanity(void* pD, CSMI_Message* message)
{
	if (pD == NULL)
		return EINVAL;
	if (message == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function getRegisterValue
 * @param[out] regContent Register data output.
 * @param[in] regAddress Register address.
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_GetRegisterValueSanity(void* pD, uint16_t regAddress, uint32_t* regContent)
{
	if (pD == NULL)
		return EINVAL;
	if (regContent == NULL)
		return EINVAL;




	return 0;
}
/**
 * Checks validity of parameters for function setRegisterValue
 * @param[in] regContent Register data input.
 * @param[in] regAddress Register address.
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_SetRegisterValueSanity(void* pD, uint16_t regAddress, uint32_t regContent)
{
	if (pD == NULL)
		return EINVAL;






	return 0;
}
/**
 * Checks validity of parameters for function setMessageChannelLapse
 * @param[in] mchLapse New Message Channel Lapse value
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_SetMessageChannelLapseSanity(void* pD, uint8_t mchLapse)
{
	if (pD == NULL)
		return EINVAL;


	if (mchLapse > (15))
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function getMessageChannelLapse
 * @param[out] mchLapse Current Message Channel Lapse value
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_GetMessageChannelLapseSanity(void* pD, uint8_t* mchLapse)
{
	if (pD == NULL)
		return EINVAL;
	if (mchLapse == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function getMessageChannelUsage
 * @param[out] mchUsage Current Message Channel Usage
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_GetMessageChannelUsageSanity(void* pD, uint16_t* mchUsage)
{
	if (pD == NULL)
		return EINVAL;
	if (mchUsage == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function
 * getMessageChannelCapacity
 * @param[out] mchCapacity Current Message Channel Capacity
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_GetMessageChannelCapacitySanity(void* pD, uint16_t* mchCapacity)
{
	if (pD == NULL)
		return EINVAL;
	if (mchCapacity == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function setSnifferMode
 * @param[in] state New state
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_SetSnifferModeSanity(void* pD, bool state)
{
	if (pD == NULL)
		return EINVAL;




	return 0;
}
/**
 * Checks validity of parameters for function getSnifferMode
 * @param[out] state Current state
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_GetSnifferModeSanity(void* pD, bool* state)
{
	if (pD == NULL)
		return EINVAL;
	if (state == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function setFramerEnabled
 * @param[in] state New state
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_SetFramerEnabledSanity(void* pD, bool state)
{
	if (pD == NULL)
		return EINVAL;




	return 0;
}
/**
 * Checks validity of parameters for function getFramerEnabled
 * @param[out] state Current state
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_GetFramerEnabledSanity(void* pD, bool* state)
{
	if (pD == NULL)
		return EINVAL;
	if (state == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function setDeviceEnabled
 * @param[in] state New state
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_SetDeviceEnabledSanity(void* pD, bool state)
{
	if (pD == NULL)
		return EINVAL;




	return 0;
}
/**
 * Checks validity of parameters for function getDeviceEnabled
 * @param[out] state Current state
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_GetDeviceEnabledSanity(void* pD, bool* state)
{
	if (pD == NULL)
		return EINVAL;
	if (state == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function setGoAbsent
 * @param[in] state New state
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_SetGoAbsentSanity(void* pD, bool state)
{
	if (pD == NULL)
		return EINVAL;




	return 0;
}
/**
 * Checks validity of parameters for function getGoAbsent
 * @param[out] state Current state
 * @param[in] pD Pointer to driver's private data object.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_GetGoAbsentSanity(void* pD, bool* state)
{
	if (pD == NULL)
		return EINVAL;
	if (state == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function setFramerConfig
 * @param[in] framerConfig Pointer to structure containing Framer configuration.
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_SetFramerConfigSanity(void* pD, CSMI_FramerConfig* framerConfig)
{
	if (pD == NULL)
		return EINVAL;
	if (framerConfig == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function getFramerConfig
 * @param[out] framerConfig Pointer to structure to which Framer configuration will be written.
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_GetFramerConfigSanity(void* pD, CSMI_FramerConfig* framerConfig)
{
	if (pD == NULL)
		return EINVAL;
	if (framerConfig == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function setGenericDeviceConfig
 * @param[in] genericDeviceConfig Pointer to structure containing Generic Device configuration.
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_SetGenericDeviceConfigSanity(void* pD, CSMI_GenericDeviceConfig* genericDeviceConfig)
{
	if (pD == NULL)
		return EINVAL;
	if (genericDeviceConfig == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function getGenericDeviceConfig
 * @param[out] genericDeviceConfig Pointer to structure to which Generic Device configuration will be written.
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_GetGenericDeviceConfigSanity(void* pD, CSMI_GenericDeviceConfig* genericDeviceConfig)
{
	if (pD == NULL)
		return EINVAL;
	if (genericDeviceConfig == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function getDataPortStatus
 * @param[in] portNumber Selected Port Number
 * @param[out] portStatus Pointer to structure to which Framer configuration will be written.
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_GetDataPortStatusSanity(void* pD, uint8_t portNumber, CSMI_DataPortStatus* portStatus)
{
	if (pD == NULL)
		return EINVAL;
	if (portStatus == NULL)
		return EINVAL;


	if (portNumber > (63))
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function unfreeze
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_UnfreezeSanity(void* pD)
{
	if (pD == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function cancelConfiguration
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_CancelConfigurationSanity(void* pD)
{
	if (pD == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function getStatusSynchronization
 * @param[out] sfSync If 1, the SLIMbus Manager achieved superframe synchronization. Not returned if NULL was passed.
 * @param[out] sfbSync If 1, the SLIMbus Manager achieved superframe block synchronization. Not returned if NULL was passed.
 * @param[out] mSync If 1, the SLIMbus Manager achieved message synchronization. Not returned if NULL was passed.
 * @param[out] fSync If 1, the SLIMbus Manager achieved frame synchronization. Not returned if NULL was passed.
 * @param[out] phSync If 1, the SLIMbus Manager achieved phase synchronization and clock signal generated by the Generic device is valid. Not returned if NULL was passed.
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_GetStatusSynchronizationSanity(void* pD, bool* fSync, bool* sfSync, bool* mSync, bool* sfbSync, bool* phSync)
{
	if (pD == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function getStatusDetached
 * @param[out] detached If 1, the SLIMbus Manager is detached from the bus after successful transmission of REPORT_ABSENT message.
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_GetStatusDetachedSanity(void* pD, bool* detached)
{
	if (pD == NULL)
		return EINVAL;
	if (detached == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function getStatusSlimbus
 * @param[out] subframeMode This variable contains the Subframe Mode read from the Framing Information during superframe synchronization and after reconfiguration (from the payload of the NEXT_SUBFRAME_MODE message sent by the SLIMbus Manager). Not returned if NULL was passed.
 * @param[out] clockGear This variable contains the Clock Gear read from the Framing Information during superframe synchronization and after reconfiguration (from the payload of the NEXT_SUBFRAME_MODE message sent by the SLIMbus Manager). Not returned if NULL was passed.
 * @param[out] rootFr This variable contains the Root Frequency read from the Framing Information during superframe synchronization and after reconfiguration (from the payload of the NEXT_SUBFRAME_MODE message sent by the SLIMbus Manager). Not returned if NULL was passed.
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_GetStatusSlimbusSanity(void* pD, CSMI_SubframeMode* subframeMode, CSMI_ClockGear* clockGear, CSMI_RootFrequency* rootFr)
{
	if (pD == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function msgAssignLogicalAddress
 * @param[in] newLa New Logical Address
 * @param[in] destinationEa Destination's Enumeration Address
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgAssignLogicalAddressSanity(void* pD, uint64_t destinationEa, uint8_t newLa)
{
	if (pD == NULL)
		return EINVAL;




	if (newLa > (239))
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function msgResetDevice
 * @param[in] destinationLa Destination's Logic Address
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgResetDeviceSanity(void* pD, uint8_t destinationLa)
{
	if (pD == NULL)
		return EINVAL;




	return 0;
}
/**
 * Checks validity of parameters for function msgChangeLogicalAddress
 * @param[in] destinationLa Destination's Logic Address
 * @param[in] newLa New Logical Address
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgChangeLogicalAddressSanity(void* pD, uint8_t destinationLa, uint8_t newLa)
{
	if (pD == NULL)
		return EINVAL;




	if (newLa > (239))
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function
 * msgChangeArbitrationPriority
 * @param[in] broadcast Broadcast Message to all devices
 * @param[in] destinationLa Destination's Logic Address, used if broadcast = 0
 * @param[in] newArbitrationPriority New Arbitration Priority
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgChangeArbitrationPrioritySanity(void* pD, bool broadcast, uint8_t destinationLa, CSMI_ArbitrationPriority newArbitrationPriority)
{
	if (pD == NULL)
		return EINVAL;






	if (
		newArbitrationPriority != CSMI_AP_LOW	&&
		newArbitrationPriority != CSMI_AP_DEFAULT	&&
		newArbitrationPriority != CSMI_AP_HIGH	 &&
		newArbitrationPriority != CSMI_AP_MANAGER_1   &&
		newArbitrationPriority != CSMI_AP_MANAGER_2   &&
		newArbitrationPriority != CSMI_AP_MANAGER_3   &&
		newArbitrationPriority != CSMI_AP_MAXIMUM
	)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function
 * msgRequestSelfAnnouncement
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgRequestSelfAnnouncementSanity(void* pD)
{
	if (pD == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function msgConnectSource
 * @param[in] destinationLa Destination's Logic Address
 * @param[in] channelNumber Data Channel Number
 * @param[in] portNumber Port Number to be connected to data channel
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgConnectSourceSanity(void* pD, uint8_t destinationLa, uint8_t portNumber, uint8_t channelNumber)
{
	if (pD == NULL)
		return EINVAL;




	if (portNumber > (63))
		return EINVAL;




	return 0;
}
/**
 * Checks validity of parameters for function msgConnectSink
 * @param[in] destinationLa Destination's Logic Address
 * @param[in] channelNumber Data Channel Number
 * @param[in] portNumber Port Number to be connected to data channel
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgConnectSinkSanity(void* pD, uint8_t destinationLa, uint8_t portNumber, uint8_t channelNumber)
{
	if (pD == NULL)
		return EINVAL;




	if (portNumber > (63))
		return EINVAL;




	return 0;
}
/**
 * Checks validity of parameters for function msgDisconnectPort
 * @param[in] destinationLa Destination's Logic Address
 * @param[in] portNumber Port Number to be disconnected from data channel
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgDisconnectPortSanity(void* pD, uint8_t destinationLa, uint8_t portNumber)
{
	if (pD == NULL)
		return EINVAL;




	if (portNumber > (63))
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function msgChangeContent
 * @param[in] dataLength Data Length
 * @param[in] dataType Data Type
 * @param[in] presenceRate Presence Rate
 * @param[in] frequencyLockedBit Frequency Locked Bit
 * @param[in] channelLink Channel Link
 * @param[in] channelNumber Data Channel Number
 * @param[in] pD Pointer to driver's private data.
 * @param[in] auxiliaryBitFormat Auxiliary Bit Format
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgChangeContentSanity(void* pD, uint8_t channelNumber, bool frequencyLockedBit, CSMI_PresenceRate presenceRate, CSMI_AuxFieldFormat auxiliaryBitFormat, CSMI_DataType dataType, bool channelLink, uint8_t dataLength)
{
	if (pD == NULL)
		return EINVAL;


	if (channelNumber > (255))
		return EINVAL;




	if (
		presenceRate != CSMI_PR_12K   &&
		presenceRate != CSMI_PR_24K   &&
		presenceRate != CSMI_PR_48K   &&
		presenceRate != CSMI_PR_96K   &&
		presenceRate != CSMI_PR_192K   &&
		presenceRate != CSMI_PR_384K   &&
		presenceRate != CSMI_PR_768K   &&
		presenceRate != CSMI_PR_11025	&&
		presenceRate != CSMI_PR_22050	&&
		presenceRate != CSMI_PR_44100	&&
		presenceRate != CSMI_PR_88200	&&
		presenceRate != CSMI_PR_176400	 &&
		presenceRate != CSMI_PR_352800	 &&
		presenceRate != CSMI_PR_705600	 &&
		presenceRate != CSMI_PR_4K	 &&
		presenceRate != CSMI_PR_8K	 &&
		presenceRate != CSMI_PR_16K   &&
		presenceRate != CSMI_PR_32K   &&
		presenceRate != CSMI_PR_64K   &&
		presenceRate != CSMI_PR_128K   &&
		presenceRate != CSMI_PR_256K   &&
		presenceRate != CSMI_PR_512K
	)
		return EINVAL;


	if (
		auxiliaryBitFormat != CSMI_AF_NOT_APPLICABLE   &&
		auxiliaryBitFormat != CSMI_AF_ZCUV	 &&
		auxiliaryBitFormat != CSMI_AF_USER_DEFINED
	)
		return EINVAL;


	if (
		dataType != CSMI_DF_NOT_INDICATED	&&
		dataType != CSMI_DF_LPCM   &&
		dataType != CSMI_DF_IEC61937   &&
		dataType != CSMI_DF_PACKED_PDM_AUDIO   &&
		dataType != CSMI_DF_USER_DEFINED_1	 &&
		dataType != CSMI_DF_USER_DEFINED_2
	)
		return EINVAL;




	if (dataLength > (31))
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function msgRequestInformation
 * @param[in] broadcast Broadcast Message to all devices
 * @param[in] destinationLa Destination's Logic Address, used if broadcast = 0
 * @param[in] transactionId Transaction ID
 * @param[in] elementCode Element Code
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgRequestInformationSanity(void* pD, bool broadcast, uint8_t destinationLa, uint8_t transactionId, uint16_t elementCode)
{
	if (pD == NULL)
		return EINVAL;










	return 0;
}
/**
 * Checks validity of parameters for function
 * msgRequestClearInformation
 * @param[in] destinationLa Destination's Logic Address, used if broadcast = 0
 * @param[in] clearMaskSize Clear Mask size
 * @param[in] broadcast Broadcast Message to all devices
 * @param[in] clearMask Pointer to Clear Mask (0 (NULL) to 16 bytes). If the size of Clear Mask is smaller than the size of the Information Slice, the Device shall pad the MSBs of Clear Mask with ones. If the size of Clear Mask is larger than the size of the Information Slice, the Device shall change only the portion of the Information Map corresponding to the identified Information Slice.
 * @param[in] elementCode Element Code
 * @param[in] pD Pointer to driver's private data.
 * @param[in] transactionId Transaction ID
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgRequestClearInformationSanity(void* pD, bool broadcast, uint8_t destinationLa, uint8_t transactionId, uint16_t elementCode, uint8_t* clearMask, uint8_t clearMaskSize)
{
	if (pD == NULL)
		return EINVAL;












	return 0;
}
/**
 * Checks validity of parameters for function msgClearInformation
 * @param[in] destinationLa Destination's Logic Address, used if broadcast = 0
 * @param[in] clearMaskSize Clear Mask size
 * @param[in] broadcast Broadcast Message to all devices
 * @param[in] clearMask Pointer to Clear Mask (0 (NULL) to 16 bytes). If the size of Clear Mask is smaller than the size of the Information Slice, the Device shall pad the MSBs of Clear Mask with ones. If the size of Clear Mask is larger than the size of the Information Slice, the Device shall change only the portion of the Information Map corresponding to the identified Information Slice.
 * @param[in] elementCode Element Code
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgClearInformationSanity(void* pD, bool broadcast, uint8_t destinationLa, uint16_t elementCode, uint8_t* clearMask, uint8_t clearMaskSize)
{
	if (pD == NULL)
		return EINVAL;










	return 0;
}
/**
 * Checks validity of parameters for function msgBeginReconfiguration
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgBeginReconfigurationSanity(void* pD)
{
	if (pD == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function msgNextActiveFramer
 * @param[in] outgoingFramerClockCycles Number of Outgoing Framer Clock cycles
 * @param[in] incomingFramerLa Incoming Framer's Logic Address
 * @param[in] pD Pointer to driver's private data.
 * @param[in] incomingFramerClockCycles Number of Incoming Framer Clock cycles
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgNextActiveFramerSanity(void* pD, uint8_t incomingFramerLa, uint16_t outgoingFramerClockCycles, uint16_t incomingFramerClockCycles)
{
	if (pD == NULL)
		return EINVAL;


	if (incomingFramerLa > (239))
		return EINVAL;


	if (outgoingFramerClockCycles > (4095))
		return EINVAL;


	if (incomingFramerClockCycles > (4095))
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function msgNextSubframeMode
 * @param[in] newSubframeMode New Subframe Mode
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgNextSubframeModeSanity(void* pD, CSMI_SubframeMode newSubframeMode)
{
	if (pD == NULL)
		return EINVAL;


	if (
		newSubframeMode != CSMI_SM_24_CSW_32_SL   &&
		newSubframeMode != CSMI_SM_16_CSW_32_SL   &&
		newSubframeMode != CSMI_SM_16_CSW_24_SL   &&
		newSubframeMode != CSMI_SM_12_CSW_32_SL   &&
		newSubframeMode != CSMI_SM_12_CSW_24_SL   &&
		newSubframeMode != CSMI_SM_8_CSW_32_SL	 &&
		newSubframeMode != CSMI_SM_8_CSW_24_SL	 &&
		newSubframeMode != CSMI_SM_6_CSW_32_SL	 &&
		newSubframeMode != CSMI_SM_6_CSW_24_SL	 &&
		newSubframeMode != CSMI_SM_6_CSW_8_SL	&&
		newSubframeMode != CSMI_SM_4_CSW_32_SL	 &&
		newSubframeMode != CSMI_SM_4_CSW_24_SL	 &&
		newSubframeMode != CSMI_SM_4_CSW_8_SL	&&
		newSubframeMode != CSMI_SM_4_CSW_6_SL	&&
		newSubframeMode != CSMI_SM_3_CSW_32_SL	 &&
		newSubframeMode != CSMI_SM_3_CSW_24_SL	 &&
		newSubframeMode != CSMI_SM_3_CSW_8_SL	&&
		newSubframeMode != CSMI_SM_3_CSW_6_SL	&&
		newSubframeMode != CSMI_SM_2_CSW_32_SL	 &&
		newSubframeMode != CSMI_SM_2_CSW_24_SL	 &&
		newSubframeMode != CSMI_SM_2_CSW_8_SL	&&
		newSubframeMode != CSMI_SM_2_CSW_6_SL	&&
		newSubframeMode != CSMI_SM_1_CSW_32_SL	 &&
		newSubframeMode != CSMI_SM_1_CSW_24_SL	 &&
		newSubframeMode != CSMI_SM_1_CSW_8_SL	&&
		newSubframeMode != CSMI_SM_1_CSW_6_SL	&&
		newSubframeMode != CSMI_SM_8_CSW_8_SL
	)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function msgNextClockGear
 * @param[in] newClockGear New Clock Gear
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgNextClockGearSanity(void* pD, CSMI_ClockGear newClockGear)
{
	if (pD == NULL)
		return EINVAL;


	if (
		newClockGear != CSMI_CG_0	&&
		newClockGear != CSMI_CG_1	&&
		newClockGear != CSMI_CG_2	&&
		newClockGear != CSMI_CG_3	&&
		newClockGear != CSMI_CG_4	&&
		newClockGear != CSMI_CG_5	&&
		newClockGear != CSMI_CG_6	&&
		newClockGear != CSMI_CG_7	&&
		newClockGear != CSMI_CG_8	&&
		newClockGear != CSMI_CG_9	&&
		newClockGear != CSMI_CG_10
	)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function msgNextRootFrequency
 * @param[in] newRootFrequency New Root Frequency
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgNextRootFrequencySanity(void* pD, CSMI_RootFrequency newRootFrequency)
{
	if (pD == NULL)
		return EINVAL;


	if (
		newRootFrequency != CSMI_RF_0	&&
		newRootFrequency != CSMI_RF_1	&&
		newRootFrequency != CSMI_RF_2	&&
		newRootFrequency != CSMI_RF_3	&&
		newRootFrequency != CSMI_RF_4	&&
		newRootFrequency != CSMI_RF_5	&&
		newRootFrequency != CSMI_RF_6	&&
		newRootFrequency != CSMI_RF_7	&&
		newRootFrequency != CSMI_RF_8	&&
		newRootFrequency != CSMI_RF_9
	)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function msgNextPauseClock
 * @param[in] newRestartTime New Restart Time
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgNextPauseClockSanity(void* pD, CSMI_RestartTime newRestartTime)
{
	if (pD == NULL)
		return EINVAL;


	if (
		newRestartTime != CSMI_RT_FAST_RECOVERY   &&
		newRestartTime != CSMI_RT_CONSTANT_PHASE_RECOVERY	&&
		newRestartTime != CSMI_RT_UNSPECIFIED_DELAY
	)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function msgNextResetBus
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgNextResetBusSanity(void* pD)
{
	if (pD == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function msgNextShutdownBus
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgNextShutdownBusSanity(void* pD)
{
	if (pD == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function msgNextDefineChannel
 * @param[in] channelNumber Data Channel Number
 * @param[in] segmentDistribution Segment Distribution
 * @param[in] transportProtocol Transport Protocol
 * @param[in] pD Pointer to driver's private data.
 * @param[in] segmentLength Segment Length
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgNextDefineChannelSanity(void* pD, uint8_t channelNumber, CSMI_TransportProtocol transportProtocol, uint16_t segmentDistribution, uint8_t segmentLength)
{
	if (pD == NULL)
		return EINVAL;


	if (channelNumber > (255))
		return EINVAL;


	if (
		transportProtocol != CSMI_TP_ISOCHRONOUS   &&
		transportProtocol != CSMI_TP_PUSHED   &&
		transportProtocol != CSMI_TP_PULLED   &&
		transportProtocol != CSMI_TP_LOCKED   &&
		transportProtocol != CSMI_TP_ASYNC_SIMPLEX	 &&
		transportProtocol != CSMI_TP_ASYNC_HALF_DUPLEX	 &&
		transportProtocol != CSMI_TP_EXT_ASYNC_SIMPLEX	 &&
		transportProtocol != CSMI_TP_EXT_ASYNC_HALF_DUPLEX	 &&
		transportProtocol != CSMI_TP_USER_DEFINED_1   &&
		transportProtocol != CSMI_TP_USER_DEFINED_2
	)
		return EINVAL;


	if (segmentDistribution > (4095))
		return EINVAL;


	if (segmentLength > (31))
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function msgNextDefineContent
 * @param[in] dataLength Data Length
 * @param[in] dataType Data Type
 * @param[in] presenceRate Presence Rate
 * @param[in] frequencyLockedBit Frequency Locked Bit
 * @param[in] channelLink Channel Link
 * @param[in] channelNumber Data Channel Number
 * @param[in] pD Pointer to driver's private data.
 * @param[in] auxiliaryBitFormat Auxiliary Bit Format
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgNextDefineContentSanity(void* pD, uint8_t channelNumber, bool frequencyLockedBit, CSMI_PresenceRate presenceRate, CSMI_AuxFieldFormat auxiliaryBitFormat, CSMI_DataType dataType, bool channelLink, uint8_t dataLength)
{
	if (pD == NULL)
		return EINVAL;


	if (channelNumber > (255))
		return EINVAL;




	if (
		presenceRate != CSMI_PR_12K   &&
		presenceRate != CSMI_PR_24K   &&
		presenceRate != CSMI_PR_48K   &&
		presenceRate != CSMI_PR_96K   &&
		presenceRate != CSMI_PR_192K   &&
		presenceRate != CSMI_PR_384K   &&
		presenceRate != CSMI_PR_768K   &&
		presenceRate != CSMI_PR_11025	&&
		presenceRate != CSMI_PR_22050	&&
		presenceRate != CSMI_PR_44100	&&
		presenceRate != CSMI_PR_88200	&&
		presenceRate != CSMI_PR_176400	 &&
		presenceRate != CSMI_PR_352800	 &&
		presenceRate != CSMI_PR_705600	 &&
		presenceRate != CSMI_PR_4K	 &&
		presenceRate != CSMI_PR_8K	 &&
		presenceRate != CSMI_PR_16K   &&
		presenceRate != CSMI_PR_32K   &&
		presenceRate != CSMI_PR_64K   &&
		presenceRate != CSMI_PR_128K   &&
		presenceRate != CSMI_PR_256K   &&
		presenceRate != CSMI_PR_512K
	)
		return EINVAL;


	if (
		auxiliaryBitFormat != CSMI_AF_NOT_APPLICABLE   &&
		auxiliaryBitFormat != CSMI_AF_ZCUV	 &&
		auxiliaryBitFormat != CSMI_AF_USER_DEFINED
	)
		return EINVAL;


	if (
		dataType != CSMI_DF_NOT_INDICATED	&&
		dataType != CSMI_DF_LPCM   &&
		dataType != CSMI_DF_IEC61937   &&
		dataType != CSMI_DF_PACKED_PDM_AUDIO   &&
		dataType != CSMI_DF_USER_DEFINED_1	 &&
		dataType != CSMI_DF_USER_DEFINED_2
	)
		return EINVAL;




	if (dataLength > (31))
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function msgNextActivateChannel
 * @param[in] channelNumber Data Channel Number
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgNextActivateChannelSanity(void* pD, uint8_t channelNumber)
{
	if (pD == NULL)
		return EINVAL;




	return 0;
}
/**
 * Checks validity of parameters for function msgNextDeactivateChannel
 * @param[in] channelNumber Data Channel Number
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgNextDeactivateChannelSanity(void* pD, uint8_t channelNumber)
{
	if (pD == NULL)
		return EINVAL;




	return 0;
}
/**
 * Checks validity of parameters for function msgNextRemoveChannel
 * @param[in] channelNumber Data Channel Number
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgNextRemoveChannelSanity(void* pD, uint8_t channelNumber)
{
	if (pD == NULL)
		return EINVAL;




	return 0;
}
/**
 * Checks validity of parameters for function msgReconfigureNow
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgReconfigureNowSanity(void* pD)
{
	if (pD == NULL)
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function msgRequestValue
 * @param[in] broadcast Broadcast Message to all devices
 * @param[in] destinationLa Destination's Logic Address, used if broadcast = 0
 * @param[in] transactionId Transaction ID
 * @param[in] elementCode Element Code
 * @param[in] pD Pointer to driver's private data.
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgRequestValueSanity(void* pD, bool broadcast, uint8_t destinationLa, uint8_t transactionId, uint16_t elementCode)
{
	if (pD == NULL)
		return EINVAL;










	return 0;
}
/**
 * Checks validity of parameters for function msgRequestChangeValue
 * @param[in] destinationLa Destination's Logic Address, used if broadcast = 0
 * @param[in] valueUpdate Pointer to Value Update (0 (NULL) to 16 bytes).
 * @param[in] broadcast Broadcast Message to all devices
 * @param[in] elementCode Element Code
 * @param[in] pD Pointer to driver's private data.
 * @param[in] valueUpdateSize Value Update size
 * @param[in] transactionId Transaction ID
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgRequestChangeValueSanity(void* pD, bool broadcast, uint8_t destinationLa, uint8_t transactionId, uint16_t elementCode, uint8_t* valueUpdate, uint8_t valueUpdateSize)
{
	if (pD == NULL)
		return EINVAL;










	if (valueUpdateSize > (16))
		return EINVAL;


	return 0;
}
/**
 * Checks validity of parameters for function msgChangeValue
 * @param[in] destinationLa Destination's Logic Address, used if broadcast = 0
 * @param[in] valueUpdate Pointer to Value Update (0 (NULL) to 16 bytes).
 * @param[in] broadcast Broadcast Message to all devices
 * @param[in] elementCode Element Code
 * @param[in] pD Pointer to driver's private data.
 * @param[in] valueUpdateSize Value Update size
 * @return 0 success
 * @return EINVAL invalid parameters
 */
static inline int CSMI_MsgChangeValueSanity(void* pD, bool broadcast, uint8_t destinationLa, uint16_t elementCode, uint8_t* valueUpdate, uint8_t valueUpdateSize)
{
	if (pD == NULL)
		return EINVAL;








	if (valueUpdateSize > (16))
		return EINVAL;


	return 0;
}

#endif	/* _CSMI_SANITY_H_ */
