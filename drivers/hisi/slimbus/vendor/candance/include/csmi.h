/**********************************************************************
 * Copyright (C) 2014 Cadence Design Systems, Inc.
 * All rights reserved worldwide.
 **********************************************************************
 * WARNING: This file is auto-generated using api-generator utility.
 *			Do not edit it manually.
 **********************************************************************
 * Cadence Core Driver for SLIMbus Manager Interface
 **********************************************************************/

#ifndef _CSMI_H_
#define _CSMI_H_

#include "cdn_errno.h"
#include "cdn_stdtypes.h"

/** @defgroup ConfigInfo  Configuration and Hardware Operation Information
 *	The following definitions specify the driver operation environment that
 *	is defined by hardware configuration or client code. These defines are
 *	located in the header file of the core driver.
 *	@{
 */

/**********************************************************************
* Defines
**********************************************************************/
/** Maximum message payload length */
#define	CSMI_MESSAGE_PAYLOAD_MAX_LENGTH 28

/** Maximum message length */
#define	CSMI_MESSAGE_MAX_LENGTH 39

/** Minimum message length */
#define	CSMI_MESSAGE_MIN_LENGTH 6

/**
 *	@}
 */


/** @defgroup DataStructure Dynamic Data Structures
 *	This section defines the data structures used by the driver to provide
 *	hardware information, modification and dynamic operation of the driver.
 *	These data structures are defined in the header file of the core driver
 *	and utilized by the API.
 *	@{
 */

/**********************************************************************
 * Forward declarations
 **********************************************************************/
struct CSMI_InformationElement;
struct CSMI_Channel;
struct CSMI_Message;
struct CSMI_FramerConfig;
struct CSMI_GenericDeviceConfig;
struct CSMI_InformationElements;
struct CSMI_DataPortStatus;
struct CSMI_Config;
struct CSMI_Callbacks;
struct CSMI_MessageCallbacks;

/**********************************************************************
 * Enumerations
 **********************************************************************/
typedef enum
{
	/** No Arbitration */
	CSMI_AT_NONE = 0,
	/** Long Arbitration */
	CSMI_AT_LONG = 5,
	/** Short Arbitration */
	CSMI_AT_SHORT = 15,
} CSMI_ArbitrationType;

typedef enum
{
	/** Low Priority Messages */
	CSMI_AP_LOW = 1,
	/** Default Messages */
	CSMI_AP_DEFAULT = 2,
	/** High Priority Messages */
	CSMI_AP_HIGH = 3,
	/** Manager assigned only */
	CSMI_AP_MANAGER_1 = 4,
	/** Manager assigned only */
	CSMI_AP_MANAGER_2 = 5,
	/** Manager assigned only */
	CSMI_AP_MANAGER_3 = 6,
	/** Maximum Priority, for test and debug only */
	CSMI_AP_MAXIMUM = 7,
} CSMI_ArbitrationPriority;

typedef enum
{
	/** Core Message */
	CSMI_MT_CORE = 0,
	/** Destination-referred Class-specific Message */
	CSMI_MT_DESTINATION_REFERRED_CLASS_SPECIFIC_MESSAGE = 1,
	/** Destination-referred User Message */
	CSMI_MT_DESTINATION_REFERRED_USER_MESSAGE = 2,
	/** Source-referred Class-specific Message */
	CSMI_MT_SOURCE_REFERRED_CLASS_SPECIFIC_MESSAGE = 5,
	/** Source-referred User Message */
	CSMI_MT_SOURCE_REFERRED_USER_MESSAGE = 6,
} CSMI_MessageType;

typedef enum
{
	/** Destination is a Logical Address */
	CSMI_DT_LOGICAL_ADDRESS = 0,
	/** Destination is an Enumeration Address */
	CSMI_DT_ENUMERATION_ADDRESS = 1,
	/** All Devices are Destinations, no Destination Address included in Header */
	CSMI_DT_BROADCAST = 3,
} CSMI_DestinationType;

typedef enum
{
	/** Positive Acknowledge */
	CSMI_MR_POSITIVE_ACK = 10,
	/** Negative Acknowledge */
	CSMI_MR_NEGATIVE_ACK = 15,
	/** No Response */
	CSMI_MR_NO_RESPONSE = 0,
} CSMI_MessageResponse;

/** SLIMbus Transport Protocols. */
typedef enum
{
	/** Isochronous Protocol (Multicast). */
	CSMI_TP_ISOCHRONOUS = 0,
	/** Pushed Protocol (Multicast). */
	CSMI_TP_PUSHED = 1,
	/** Pulled Protocol (Unicast). */
	CSMI_TP_PULLED = 2,
	/** Locked Protocol (Multicast). */
	CSMI_TP_LOCKED = 3,
	/** Asynchronous Protocol - Simplex (Unicast). */
	CSMI_TP_ASYNC_SIMPLEX = 4,
	/** Asynchronous Protocol - Half-duplex (Unicast). */
	CSMI_TP_ASYNC_HALF_DUPLEX = 5,
	/** Extended Asynchronous Protocol - Simplex (Unicast). */
	CSMI_TP_EXT_ASYNC_SIMPLEX = 6,
	/** Extended Asynchronous Protocol - Half-duplex (Unicast). */
	CSMI_TP_EXT_ASYNC_HALF_DUPLEX = 7,
	/** User Defined 1. */
	CSMI_TP_USER_DEFINED_1 = 14,
	/** User Defined 2. */
	CSMI_TP_USER_DEFINED_2 = 15,
} CSMI_TransportProtocol;

/** Presence Rates. */
typedef enum
{
	CSMI_PR_12K = 1,
	CSMI_PR_24K = 2,
	CSMI_PR_48K = 3,
	CSMI_PR_96K = 4,
	CSMI_PR_192K = 5,
	CSMI_PR_384K = 6,
	CSMI_PR_768K = 7,
	CSMI_PR_11025 = 9,
	CSMI_PR_22050 = 10,
	CSMI_PR_44100 = 11,
	CSMI_PR_88200 = 12,
	CSMI_PR_176400 = 13,
	CSMI_PR_352800 = 14,
	CSMI_PR_705600 = 15,
	CSMI_PR_4K = 16,
	CSMI_PR_8K = 17,
	CSMI_PR_16K = 18,
	CSMI_PR_32K = 19,
	CSMI_PR_64K = 20,
	CSMI_PR_128K = 21,
	CSMI_PR_256K = 22,
	CSMI_PR_512K = 23,
} CSMI_PresenceRate;

/** Data types. */
typedef enum
{
	/** Not indicated. */
	CSMI_DF_NOT_INDICATED = 0,
	/** LPCM audio. */
	CSMI_DF_LPCM = 1,
	/** IEC61937 Compressed audio. */
	CSMI_DF_IEC61937 = 2,
	/** Packed PDM audio. */
	CSMI_DF_PACKED_PDM_AUDIO = 3,
	/** User Defined 1. */
	CSMI_DF_USER_DEFINED_1 = 14,
	/** User Defined 2. */
	CSMI_DF_USER_DEFINED_2 = 15,
} CSMI_DataType;

/** Auxilary Field formats formats. */
typedef enum
{
	/** Not applicable. */
	CSMI_AF_NOT_APPLICABLE = 0,
	/** ZCUV for tunneling IEC60958. */
	CSMI_AF_ZCUV = 1,
	/** User defined. */
	CSMI_AF_USER_DEFINED = 11,
} CSMI_AuxFieldFormat;

/** SLIMbus interrupts. */
typedef enum
{
	/** Generation of any interrupts, regardless of setting of the other interrupt enable bits. */
	CSMI_INT_EN = 1,
	/** Generation of interrupt when RX_FIFO is not empty. */
	CSMI_INT_RX = 2,
	/** Generation of interrupt when TX_FIFO becomes empty (after transmitting all messages). */
	CSMI_INT_TX = 4,
	/** Generation of interrupt when any message from TX_FIFO is not transmitted successfully. */
	CSMI_INT_TX_ERR = 8,
	/** Generation of interrupt when any of main synchronization bits (F_SYNC, SF_SYNC, M_SYNC) toggles into LOW, and the IP is not detached due to REPORT_ABSENT message. */
	CSMI_INT_SYNC_LOST = 16,
	/** Generation of interrupt at the reconfiguration boundary. */
	CSMI_INT_RCFG = 32,
	/** Generation of interrupt when usage of message channel exceeded 75 percent in 'MCH_LAPSE+1' superframes in a row. */
	CSMI_INT_MCH = 64,
} CSMI_Interrupt;

/** Data Port interrupts. */
typedef enum
{
	/** Channel activation. */
	CSMI_DP_INT_ACT = 1,
	/** Channel content definition. */
	CSMI_DP_INT_CON = 2,
	/** Channel definition. */
	CSMI_DP_INT_CHAN = 4,
	/** Data Port DMA request. */
	CSMI_DP_INT_DMA = 8,
	/** Data Port FIFO overflow. */
	CSMI_DP_INT_OVF = 16,
	/** Data Port FIFO underrun. */
	CSMI_DP_INT_UND = 32,
} CSMI_DataPortInterrupt;

/** Quality of the CLK signal that is generated by the Framer. */
typedef enum
{
	/** Potentially irregular punctured clock unsuitable for use as a timing reference for generic phaselocked loops. */
	CSMI_FQ_PUNCTURED = 0,
	/** Irregular clock that has a lower-frequency regular clock embedded. For example, such clocks can be created by cyclic pulse swallowing. */
	CSMI_FQ_IRREGULAR = 1,
	/** Regular clock that potentially has more than 1 ns RMS of wideband jitter (100 Hz measurement corner, see [AES01]). */
	CSMI_FQ_REGULAR = 2,
	/** Low-jitter clock that is known to have less than 1 ns RMS of wideband jitter (100 Hz measurement corner, see [AES01]). */
	CSMI_FQ_LOW_JITTER = 3,
} CSMI_FramerQuality;

/** User Value / Information Elements Slice sizes. */
typedef enum
{
	/** Slice size is 1 byte. */
	CSMI_SS_1_BYTE = 0,
	/** Slice size is 2 bytes. */
	CSMI_SS_2_BYTES = 1,
	/** Slice size is 3 bytes. */
	CSMI_SS_3_BYTES = 2,
	/** Slice size is 4 bytes. */
	CSMI_SS_4_BYTES = 3,
	/** Slice size is 6 bytes. */
	CSMI_SS_6_BYTES = 4,
	/** Slice size is 8 bytes. */
	CSMI_SS_8_BYTES = 5,
	/** Slice size is 12 bytes. */
	CSMI_SS_12_BYTES = 6,
	/** Slice size is 16 bytes. */
	CSMI_SS_16_BYTES = 7,
	/** Slice size max */
	CSMI_SS_MAX	= 8,
} CSMI_SliceSize;

/** SLIMbus device classes */
typedef enum
{
	/** Manager Class Device */
	CSMI_DC_MANAGER = 255,
	/** Framer Class Device */
	CSMI_DC_FRAMER = 254,
	/** Interface Class Device */
	CSMI_DC_INTERFACE = 253,
	/** Generic Class Device */
	CSMI_DC_GENERIC = 0,
} CSMI_DeviceClass;

typedef enum
{
	/** Clock Gear 6 */
	CSMI_RC_CLOCK_GEAR_6 = 0,
	/** Clock Gear 7 */
	CSMI_RC_CLOCK_GEAR_7 = 1,
	/** Clock Gear 8 */
	CSMI_RC_CLOCK_GEAR_8 = 2,
	/** Clock Gear 9 */
	CSMI_RC_CLOCK_GEAR_9 = 3,
} CSMI_ReferenceClock;

/** Subframe Mode Codings. CSW - Control Space Width (Slots), SL - Subframe Length (Slots) */
typedef enum
{
	CSMI_SM_24_CSW_32_SL = 31,
	CSMI_SM_16_CSW_32_SL = 29,
	CSMI_SM_16_CSW_24_SL = 28,
	CSMI_SM_12_CSW_32_SL = 27,
	CSMI_SM_12_CSW_24_SL = 26,
	CSMI_SM_8_CSW_32_SL = 25,
	CSMI_SM_8_CSW_24_SL = 24,
	CSMI_SM_6_CSW_32_SL = 23,
	CSMI_SM_6_CSW_24_SL = 22,
	CSMI_SM_6_CSW_8_SL = 21,
	CSMI_SM_4_CSW_32_SL = 19,
	CSMI_SM_4_CSW_24_SL = 18,
	CSMI_SM_4_CSW_8_SL = 17,
	CSMI_SM_4_CSW_6_SL = 16,
	CSMI_SM_3_CSW_32_SL = 15,
	CSMI_SM_3_CSW_24_SL = 14,
	CSMI_SM_3_CSW_8_SL = 13,
	CSMI_SM_3_CSW_6_SL = 12,
	CSMI_SM_2_CSW_32_SL = 11,
	CSMI_SM_2_CSW_24_SL = 10,
	CSMI_SM_2_CSW_8_SL = 9,
	CSMI_SM_2_CSW_6_SL = 8,
	CSMI_SM_1_CSW_32_SL = 7,
	CSMI_SM_1_CSW_24_SL = 6,
	CSMI_SM_1_CSW_8_SL = 5,
	CSMI_SM_1_CSW_6_SL = 4,
	/** 100% Control Space, 0% Data Space */
	CSMI_SM_8_CSW_8_SL = 0,
} CSMI_SubframeMode;

/** SLIMbus Frequencies and Clock Gear Codings. */
typedef enum
{
	/** Not Indicated, Min: 0 MHz, Max: 28.8 MHz */
	CSMI_CG_0 = 0,
	/** Min: 0.025 MHz, Max: 0.05625 MHz */
	CSMI_CG_1 = 1,
	/** Min: 0.05 MHz, Max: 0.1125 MHz */
	CSMI_CG_2 = 2,
	/** Min: 0.1 MHz, Max: 0.225 MHz */
	CSMI_CG_3 = 3,
	/** Min: 0.2 MHz, Max: 0.45 MHz */
	CSMI_CG_4 = 4,
	/** Min: 0.4 MHz, Max: 0.9 MHz */
	CSMI_CG_5 = 5,
	/** Min: 0.8 MHz, Max: 1.8 MHz */
	CSMI_CG_6 = 6,
	/** Min: 1.6 MHz, Max: 3.6 MHz */
	CSMI_CG_7 = 7,
	/** Min: 3.2 MHz, Max: 7.2 MHz */
	CSMI_CG_8 = 8,
	/** Min: 6.4 MHz, Max: 14.4 MHz */
	CSMI_CG_9 = 9,
	/** Min: 12.8 MHz, Max: 28.8 MHz */
	CSMI_CG_10 = 10,
} CSMI_ClockGear;

/** SLIMbus Root Frequency (RF) and Phase Modulus (PM) Codings. */
typedef enum
{
	/** RF: Not Indicated, PM: 160 */
	CSMI_RF_0 = 0,
	/** RF: 24.576 MHz, PM: 160 */
	CSMI_RF_1 = 1,
	/** RF: 22.5792 MHz, PM: 147 */
	CSMI_RF_2 = 2,
	/** RF: 15.36 MHz, PM: 100 */
	CSMI_RF_3 = 3,
	/** RF: 16.8 MHz, PM: 875 */
	CSMI_RF_4 = 4,
	/** RF: 19.2 MHz, PM: 125 */
	CSMI_RF_5 = 5,
	/** RF: 24 MHz, PM: 625 */
	CSMI_RF_6 = 6,
	/** RF: 25 MHz, PM: 15625 */
	CSMI_RF_7 = 7,
	/** RF: 26 MHz, PM: 8125 */
	CSMI_RF_8 = 8,
	/** RF: 27 MHz, PM: 5625 */
	CSMI_RF_9 = 9,
} CSMI_RootFrequency;

/** Restart Time Values. */
typedef enum
{
	/** After a restart request, the active Framer shall resume toggling the CLK line within four cycles of the CLK line frequency (as indicated by the Clock Gear and Root Frequency) used for the upcoming Frame. Optional. */
	CSMI_RT_FAST_RECOVERY = 0,
	/** After the restart request, the active Framer shall resume toggling the CLK line so the duration of the Pause is an integer number of Superframes in the upcoming Clock Gear. Optional. */
	CSMI_RT_CONSTANT_PHASE_RECOVERY = 1,
	/** After a restart request, the active Framer shall resume toggling the CLK line after an unspecified delay. Mandatory */
	CSMI_RT_UNSPECIFIED_DELAY = 2,
} CSMI_RestartTime;

/** Information Element category. */
typedef enum
{
	CSMI_IEC_CORE = 0,
	CSMI_IEC_CLASS = 1,
	CSMI_IEC_USER = 2,
} CSMI_InformationElementCategory;

/** Information Element access type. */
typedef enum
{
	CSMI_IEAT_ELEMENTAL = 0,
	CSMI_IEAT_BYTE = 1,
} CSMI_InformationElementAccessType;

/**********************************************************************
 * Callbacks
 **********************************************************************/
/** Requests Logical Address for SLIMbus Device. Called function should return proper [0x00 - 0xEF] and unique Logical Address. */
typedef uint8_t (*CSMI_AssignLogicalAddressHandler)(uint64_t enumerationAddress, CSMI_DeviceClass class);

/** Requests Device Class for assigned Logical Address. Called function should return Device Class. Mandatory. */
typedef CSMI_DeviceClass (*CSMI_DeviceClassHandler)(uint8_t logicalAddress);

/** Callback for manager interrupts */
typedef void (*CSMI_ManagerInterruptsHandler)(void* pD, CSMI_Interrupt interrupt);

/** Callback for data ports interrupts */
typedef void (*CSMI_DataPortInterruptsHandler)(void* pD, uint8_t dataPortNumber, CSMI_DataPortInterrupt dataPortInterrupt);

/** Callback for receiving SLIMbus Raw Message (before decoding). */
typedef void (*CSMI_ReceivedRawMessageHandler)(void* pD, void* message, uint8_t messageLength);

/** Callback for receiving SLIMbus Message (after decoding). */
typedef void (*CSMI_ReceivedMessageHandler)(void* pD, struct CSMI_Message* message);

/** Callback for sending SLIMbus Raw Message (after encoding). */
typedef void (*CSMI_SendingRawMessageHandler)(void* pD, void* message, uint8_t messageLength);

/** Callback for sending SLIMbus Message (before encoding). */
typedef void (*CSMI_SendingMessageHandler)(void* pD, struct CSMI_Message* message);

/** Callback for SLIMbus Reports of Information Elements. */
typedef void (*CSMI_InformationElementsHandler)(void* pD, uint8_t sourceLa, struct CSMI_InformationElements* informationElements);

/** Callback for SLIMbus REPORT_PRESENT Message, which is sent by an unenumerated Device to announce its presence on the bus. */
typedef void (*CSMI_MsgReportPresentHandler)(void* pD, uint64_t sourceEa, CSMI_DeviceClass deviceClass, uint8_t deviceClassVersion);

/** Callback for SLIMbus REPORT_ABSENT Message, which shall be sent from a Device to announce that it is about to leave the bus. */
typedef void (*CSMI_MsgReportAbsentHandler)(void* pD, uint8_t sourceLa);

/** Callback for SLIMbus REPLY_INFORMATION Message, which is sent by a Device in response to a REQUEST_INFORMATION or REQUEST_CLEAR_INFORMATION Message. */
typedef void (*CSMI_MsgReplyInformationHandler)(void* pD, uint8_t sourceLa, uint8_t transactionId, uint8_t* informationSlice, uint8_t informationSliceLength);

/** Callback for SLIMbus REPORT_INFORMATION Message, which used by a Device to inform another Device about a change in an Information Slice. */
typedef void (*CSMI_MsgReportInformationHandler)(void* pD, uint8_t sourceLa, uint16_t elementCode, uint8_t* informationSlice, uint8_t informationSliceLength);

/** Callback for SLIMbus REPLY_VALUE Message, which is sent by a Device in response to a REQUEST_VALUE or REQUEST_CHANGE_VALUE Message. */
typedef void (*CSMI_MsgReplyValueHandler)(void* pD, uint8_t sourceLa, uint8_t transactionId, uint8_t* valueSlice, uint8_t valueSliceLength);

/**********************************************************************
 * Structures and unions
 **********************************************************************/
/** Structure describing Information Element. */
typedef struct CSMI_InformationElement
{
	/** Byte address. */
	uint16_t address;
	/** Slice size to be accessed. Valid for elemental access type. */
	CSMI_SliceSize ss;
	/** Bit number pointing to Information Element's lowest bit. Valid for Byte access type. */
	uint8_t bn;
	/** Category of Information Element. It can be Core, Class-specific and User defined. */
	CSMI_InformationElementCategory category;
	/** Buffer for storing Information Element Slice. */
	uint8_t slice[16];
}  CSMI_InformationElement;

/** SLIMbus Data Channel and its content structure definition. */
typedef struct CSMI_Channel
{
	/** Channel number. This number is used as a channel identifier. */
	uint8_t cn;
	/** Transport Protocol. Cadence's SLIMbus Manager Controller IP currently supports only Isochronous, Pushed and Pulled Protocols. */
	CSMI_TransportProtocol tp;
	/** Length of a Segment (in Slots). Valid value ranges from 1 to 31. */
	uint8_t sl;
	/** Frequency Locked bit indicating whether the content flow is known to be frequency locked to the SLIMbus CLK signal. */
	bool fl;
	/** Specifies presence rate. */
	CSMI_PresenceRate pr;
	/** Specifies Auxiliary Field format. */
	CSMI_AuxFieldFormat af;
	/** Data type. */
	CSMI_DataType dt;
	/** Channel link bit. When true, indicates that the content of channel 'cn' is related to that of channel 'ch-1'. */
	bool cl;
	/** Length of the Data field (in Slots). Valid value ranges from 1 to 31 */
	uint8_t dl;
}  CSMI_Channel;

/** SLIMbus Message structure definition. */
typedef struct CSMI_Message
{
	/** Arbitration Type */
	CSMI_ArbitrationType arbitrationType;
	/** Source Address, if Arbitration Type == AT_SHORT used as Logic Address, if Arbitration Type == AT_Long used as Enumeration Address. */
	uint64_t sourceAddress;
	/** Arbitration Priority */
	CSMI_ArbitrationPriority arbitrationPriority;
	/** Message Type */
	CSMI_MessageType messageType;
	/** Message Codes are specific to a Message Type. */
	uint8_t messageCode;
	/** Destination Type */
	CSMI_DestinationType destinationType;
	/** Destination Address, if Destination Type == DT_LOGICAL_ADDRESS used as Logic Address, if Destination Type == DT_ENUMERATION_ADDRESS used as Enumeration Address, ignored if Destination Type == DT_BROADCAST. */
	uint64_t destinationAddress;
	/** Message Payload */
	uint8_t payload[28];
	/** Message Payload Length */
	uint8_t payloadLength;
	/** Message Response */
	CSMI_MessageResponse response;
}  CSMI_Message;

/** Structure describing configuration of the Framer device implemented in SLIMbus Manager. */
typedef struct CSMI_FramerConfig
{
	/** Each bit of this vector corresponds to one of 16 Root Frequencies specified by the SLIMbus standard. When the bit is 1 then the corresponding Root Frequency is supported by the Framer device implemented in SLIMBUS_MANAGER. When bit is 0 then the corresponding Root Frequency is not supported, and the attempt of reconfiguration SLIMBUS_MANAGER using that Root Frequency will result in RECONFIG_OBJECTION. */
	uint16_t rootFrequenciesSupported;
	/** Used to set quality of the CLK signal that is generated by the FRAMER device implemented in SLIMBUS_MANAGER. */
	CSMI_FramerQuality quality;
	/** When 1 and the FRAMER device change the Root Frequency, after reconfiguration boundary the Framer stops the SLIMbus clock leaving the SLIMbus clock line at 0 state. To start toggle the clock line, the UNFREEZE bit in the COMMAND register must be set. When 0 the FRAMER device change the Root Frequency without stopping the clock line. */
	bool pauseAtRootFrequencyChange;
}  CSMI_FramerConfig;

/** Structure describing configuration of the Generic device and its Data Ports implemented in SLIMbus Manager. */
typedef struct CSMI_GenericDeviceConfig
{
	/** Presence Rates supported by Generic device. Each bit of this vector corresponds to one of 24 not reserved values of the Presence Rate specified by the SLIMbus standard, range b0000000...b0010111 is considered. When the bit is 1 then the corresponding Presence Rate is supported by the Generic device implemented in SLIMBUS_MANAGER. When bit is 0 then the corresponding Presence Rate is not supported, and the attempt of connecting SLIMBUS_MANAGER data port to channel with corresponding Presence Rate will result in EX_ERROR. */
	uint32_t presenceRatesSupported;
	/** When 1 then the Isochronous Transport protocol is supported by the Generic device implemented in SLIMBUS_MANAGER. When the bit is 0 then the Isochronous Transport Protocol is not supported, and the attempt of connecting SLIMBUS_MANAGER data port to channel with Isochronous Transport protocol will result in EX_ERROR. */
	bool transportProtocolIsochronous;
	/** When 1 then the Pushed Transport protocol is supported by the Generic device implemented in SLIMBUS_MANAGER. When the bit is 0 then the Pushed Transport Protocol is not supported, and the attempt of connecting SLIMBUS_MANAGER data port to channel with Pushed Transport protocol will result in EX_ERROR. */
	bool transportProtocolPushed;
	/** When 1 then the Pulled Transport protocol is supported by the Generic device implemented in SLIMBUS_MANAGER. When the bit is 0 then the Pulled Transport Protocol is not supported, and the attempt of connecting SLIMBUS_MANAGER data port to channel with Pulled Transport protocol will result in EX_ERROR. */
	bool transportProtocolPulled;
	/** Level of FIFO at which sink port starts releasing data. Must be lower than DATA_FIFO_SIZE. Recommended value, for DATA_FIFO_SIZE = 4 is 2. */
	uint8_t sinkStartLevel;
	/** This 4-bit number defining prescaler used for Data Port clock (dport_clock) generation. For each data port, SLIMBUS_MANAGER generates data port clock with frequency related with data channel segment rate. And the ratio between segment rate and generated data port clock is defined as 2*PORT_CLK_PRESC. Accepted values: 2 to 8. For values 0 and 1, functionality is the same as for value 2. For values 9 and above, functionality is not specified. */
	uint8_t dataPortClockPrescaler;
	/** Used for generation of cport_clk_o. Frequency of cport_clk_o = sb_clk_i_n frequency divided by {CPORT_CLK_DIV+1}. */
	uint8_t cportClockDivider;
	/** Defines the reference clock generated out of the SLIMbus clock. */
	CSMI_ReferenceClock referenceClockSelector;
	/** When level of Source Data Port FIFO falls below that threshold then DMA request is generated for Source data ports, and if enabled, DMA request interrupt is generated. */
	uint16_t dmaTresholdSource;
	/** When level of Sink Data Port FIFO exceeds that threshold then DMA request is generated for Sink data ports, and if enabled, DMA request interrupt is generated. */
	uint16_t dmaTresholdSink;
}  CSMI_GenericDeviceConfig;

/** State of Information Elements */
typedef struct CSMI_InformationElements
{
	/** Core IE - There has been a Message execution error */
	bool coreExError;
	/** Core IE - The Device objects to the bus reconfiguration */
	bool coreReconfigObjection;
	/** Core IE - A Collision was detected in a Data Channel */
	bool coreDataTxCol;
	/** Core IE - An unsupported Message has been received */
	bool coreUnsprtdMsg;
	/** Interface Device Class Specific IE - Internal Port contention */
	bool interfaceDataSlotOverlap;
	/** Interface Device Class Specific IE - Lost Message synchronization */
	bool interfaceLostMs;
	/** Interface Device Class Specific IE - Lost Superframe synchronization */
	bool interfaceLostSfs;
	/** Interface Device Class Specific IE - Lost Frame synchronization */
	bool interfaceLostFs;
	/** Interface Device Class Specific IE - Message Channel Collision detected */
	bool interfaceMcTxCol;
	/** Manager Device Class Specific IE - The Device is the active Manager */
	bool managerActiveManager;
	/** Framer Device Class Specific IE - Quality of the generated clock (Optional) */
	CSMI_FramerQuality framerQuality;
	/** Framer Device Class Specific IE - Guide Channel Collision detected */
	bool framerGcTxCol;
	/** Framer Device Class Specific IE - Framing Information Collision detected */
	bool framerFiTxCol;
	/** Framer Device Class Specific IE - Frame Sync Symbol Collision detected */
	bool framerFsTxCol;
	/** Framer Device Class Specific IE - The Device is the active Framer */
	bool framerActiveFramer;
}  CSMI_InformationElements;

/** Structure describing status of Generic Data Port implemented in the Manager component. */
typedef struct CSMI_DataPortStatus
{
	/** 1 if Data Port is activated. Data Port is regarded to be activated if it is connected, configured and activated. Otherwise it is regarded as deactivated. */
	bool active;
	/** 1 if content the channel connected with Data Port is defined (consequence of NEXT_DEFINE_CONTENT or CHANGE_CONTENT message). */
	bool contentDefined;
	/** 1 if the channel connected with Data Port is defined (consequence of NEXT_DEFINE_CHANNEL message). */
	bool channelDefined;
	/** 1 if Data Port is connected as Sink. 0 if Data Port is disconnected or connected as Source. */
	bool sink;
	/** 1 if overflow occurred for Data Port. */
	bool overflow;
	/** 1 if underrun occurred for Data Port. */
	bool underrun;
	/** Implemented only when access to the Data Port is selected through AHB. In such case it notifies about one of the following conditions: - Corresponding Data Port is configured as SOURCE and its internal FIFO is not full (ready for next data). - Corresponding Data Port FIFO is not empty. When access to the Data Port is selected through Direct interface then this bit is fixed to 0. */
	bool dportReady;
	/** Segment Interval decoded from Segment Distribution defined for the connected channel. Part of Channel Definition. */
	uint16_t segmentInterval;
	/** Transport Protocol defined for the connected channel. Part of Channel Definition. */
	CSMI_TransportProtocol transportProtocol;
	/** Presence Rate defined for the connected channel. Part of Content Definition. */
	CSMI_PresenceRate presenceRate;
	/** FR bit defined for the connected channel. Part of Content Definition. */
	bool frequencyLock;
	/** Data Type defined for the connected channel. Part of Content Definition. */
	CSMI_DataType dataType;
	/** Data Length defined for the connected channel. Part of Content Definition. */
	uint8_t dataLength;
	/** This variable contains number of port to which this Data Port is linked to. Valid of corresponding CH_LINK is HIGH. Value 63 may indicate that the linked port has not been found despite of CH_LINK=1. Part of Content Definition. */
	uint8_t portLinked;
	/** CL bit defined for the connected channel. Part of Content Definition. */
	bool channelLink;
}  CSMI_DataPortStatus;

/** Configuration parameters passed to probe & init functions. */
typedef struct CSMI_Config
{
	/** Base address of the register space. */
	uintptr_t regBase;
	/** Base address of the DMA descriptors space. */
	uintptr_t dmaBase;
	/** If 1, the Sniffer functionality is enabled. In this mode all messages tracked in the message channel are written to RX_FIFO, regardless of response status. */
	bool snifferMode;
	/** If 1, the internal Framer device is enabled. If set 0, the internal Framer device is disabled. */
	bool enableFramer;
	/** If 1, the internal Generic device is enabled. If set 0, the internal Generic device is disabled. */
	bool enableDevice;
	/** Maximum number of retransmissions in case of collision or not positive acknowledgement. */
	uint8_t retryLimit;
	/** When 1, REPORT_INFORMATION message is transmitted independent on state of Information Element before the event occurrence (i.e. Information Element does not have to be cleared to enable next generation of corresponding REPORT_INFORMATION). */
	bool reportAtEvent;
	/** If 1, CRC fields in the messages transmitted from TX_FIFO hardware calculation of CRC is disabled (CRC will be calculated by the CPU). If 0, CRC fields are calculated automatically in the IP. */
	bool disableHardwareCrcCalculation;
	/** If 1, reporting using REPORT_INFORMATION is limited only to mandatory reporting. I.e. only REPORT_INFORMATION messages related with Information Elements specific for the Interface Device Class are supported (MC_TX_COL, LOST_FS, LOST_SFS, LOST_MS, DATA_SLOT_OVERLAP) */
	bool limitReports;
	/** Product ID. Part of SLIMbus Enumeration Address. */
	uint16_t eaProductId;
	/** Instance Value. Part of SLIMbus Enumeration Address. */
	uint8_t eaInstanceValue;
	/** Device ID of the Interface device - part of Enumeration Address. */
	uint8_t eaInterfaceId;
	/** Device ID of the Generic device - part of Enumeration Address. */
	uint8_t eaGenericId;
	/** Device ID of the Framer device - part of Enumeration Address. */
	uint8_t eaFramerId;
	/** If enabled, the driver will enumerate devices using AssignLogicalAddressHandler. If disabled user will have to perform enumeration of devices using Messages. */
	bool enumerateDevices;
}  CSMI_Config;

/** Structure containing pointers to functions defined by user that will be called when specific event occurs. */
typedef struct CSMI_Callbacks
{
	/** Request for Logical Address. Required if enumerateDevices in CSMI_Config is enabled. */
	CSMI_AssignLogicalAddressHandler onAssignLogicalAddress;
	/** Request for Device Class for Logical Address. Mandatory. */
	CSMI_DeviceClassHandler onDeviceClassRequest;
	/** Callback for SLIMbus Reports of Information Elements. Optional, unused if NULL was assigned. */
	CSMI_InformationElementsHandler onInformationElementReported;
	/** Callback for Manager Interrupts. Optional, unused if NULL was assigned. */
	CSMI_ManagerInterruptsHandler onManagerInterrupt;
	/** Callback for Data Ports Interrupts. Optional, unused if NULL was assigned. */
	CSMI_DataPortInterruptsHandler onDataPortInterrupt;
	/** Callback for Receiving SLIMbus Raw Message (before decoding). Optional, unused if NULL was assigned. */
	CSMI_ReceivedRawMessageHandler onRawMessageReceived;
	/** Callback for receiving SLIMbus Message (after decoding). Optional, unused if NULL was assigned. */
	CSMI_ReceivedMessageHandler onMessageReceived;
	/** Callback for sending SLIMbus Raw Message (after encoding). Optional, unused if NULL was assigned. */
	CSMI_SendingRawMessageHandler onRawMessageSending;
	/** Callback for sending SLIMbus Message (before encoding). Optional, unused if NULL was assigned. */
	CSMI_SendingMessageHandler onMessageSending;
}  CSMI_Callbacks;

/** Structure containing pointers to functions defined by user that will be called when specific SLIMbus message has been received. */
typedef struct CSMI_MessageCallbacks
{
	/** Callback for REPORT_PRESENT Message. Unused if NULL was assigned. */
	CSMI_MsgReportPresentHandler onMsgReportPresent;
	/** Callback for REPORT_ABSENT Message. Unused if NULL was assigned. */
	CSMI_MsgReportAbsentHandler onMsgReportAbsent;
	/** Callback for REPLY_INFORMATION Message. Unused if NULL was assigned. */
	CSMI_MsgReplyInformationHandler onMsgReplyInformation;
	/** Callback for REPORT_INFORMATION Message. Unused if NULL was assigned. */
	CSMI_MsgReportInformationHandler onMsgReportInformation;
	/** Callback for REPLY_VALUE Message. Unused if NULL was assigned. */
	CSMI_MsgReplyValueHandler onMsgReplyValue;
}  CSMI_MessageCallbacks;

/**
 *	@}
 */

/** @defgroup DriverObject Driver API Object
 *	API listing for the driver. The API is contained in the object as
 *	function pointers in the object structure. As the actual functions
 *	resides in the Driver Object, the client software must first use the
 *	global GetInstance function to obtain the Driver Object Pointer.
 *	The actual APIs then can be invoked using obj->(api_name)() syntax.
 *	These functions are defined in the header file of the core driver
 *	and utilized by the API.
 *	@{
 */

/**********************************************************************
 * API methods
 **********************************************************************/
typedef struct CSMI_OBJ
{
	/**
	 * Returns the memory requirements for a driver instance.
	 * @param[out] requiredMemory Required memory in bytes.
	 * @param[in] config Driver and hardware configuration.
	 * @return EOK On success (requiredMemory variable filled).
	 * @return EINVAL If config contains invalid values or not supported configuration.
	 */
	uint32_t (*probe)(const CSMI_Config* config, uint16_t* requiredMemory);

	/**
	 * Instantiates the CSMI Core Driver, given the required blocks of
	 * memory (this includes initializing the instance and the underlying
	 * hardware). If a client configuration is required (likely to always
	 * be true), it is passed in also. Returns an instance pointer, which
	 * the client must maintain and pass to all other driver functions.
	 * (except probe).
	 * @param[in] callbacks Event Handlers and Callbacks.
	 * @param[in] config Specifies driver/hardware configuration.
	 * @param[in] pD Pointer to driver's private data object.
	 * @return EOK On success
	 * @return EINPROGRESS If SLIMbus Manager is already running.
	 * @return EINVAL If illegal/inconsistent values in 'config' doesn't support feature(s) required by 'config' parameters.
	 */
	uint32_t (*init)(void* pD, const CSMI_Config* config, CSMI_Callbacks* callbacks);

	/**
	 * CSMI Core Driver's ISR. Platform-specific code is responsible for
	 * ensuring this gets called when the corresponding hardware's
	 * interrupt is asserted. Registering the ISR should be done after
	 * calling init, and before calling start. The driver's ISR will not
	 * attempt to lock any locks, but will perform client callbacks. If
	 * the client wishes to defer processing to non-interrupt time, it is
	 * responsible for doing so. This function must not be called after
	 * calling destroy and releasing private data memory.
	 * @param[in] pD Pointer to driver's private data object filled by init.
	 * @return 0 on success
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*isr)(void* pD);

	/**
	 * Start the CSMI driver, enabling interrupts. This is called after
	 * the client has successfully initialized the driver and hooked the
	 * driver's ISR (the isr member of this struct) to the IRQ. Driver
	 * will also enumerate all discovered devices.
	 * @param[in] pD Pointer to driver's private data object.
	 * @return 0 on success
	 * @return EINPROGRESS If SLIMbus Manager is already running.
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*start)(void* pD);

	/**
	 * The client may call this to disable the hardware (disabling its
	 * IRQ at the source and disconnecting it if applicable). Also, a
	 * best-effort is made to cancel any pending transactions.
	 * @param[in] pD Pointer to driver's private data object.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*stop)(void* pD);

	/**
	 * This performs an automatic stop and then de-initializes the
	 * driver. The client may not make further requests on this instance.
	 * @param[in] pD Pointer to driver's private data object.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*destroy)(void* pD);

	/**
	 * Sets (enable or disable) SLIMbus Manager interrupt mask.
	 * @param[in] interruptMask SLIMbus Manager interrupt mask.
	 * @param[in] pD Pointer to driver's private data object.
	 * @return EOK On success.
	 * @return EINVAL if input parameters are invalid.
	 */
	uint32_t (*setInterrupts)(void* pD, uint8_t interruptMask);

	/**
	 * Obtains information about SLIMbus Manager enabled interrupts.
	 * @param[out] interruptMask Pointer to place where SLIMbus Manager interrupt mask will be written.
	 * @param[in] pD Pointer to driver's private data object.
	 * @return EOK On success.
	 * @return EINVAL If pD or interruptMask is NULL.
	 */
	uint32_t (*getInterrupts)(void* pD, uint8_t* interruptMask);

	/**
	 * Sets (enable or disable) Data Port interrupt mask.
	 * @param[in] interruptMask Data Port interrupt mask.
	 * @param[in] portNumber Data Port number. Valid value ranges from 0 to 63.
	 * @param[in] pD Pointer to driver's private data object.
	 * @return EOK On success.
	 * @return EINVAL If pD is NULL or portNumber is invalid.
	 */
	uint32_t (*setDataPortInterrupts)(void* pD, uint8_t portNumber, uint8_t interruptMask);

	/**
	 * Obtains information about Data Port enabled interrupts.
	 * @param[out] interruptMask Pointer to place where Data Port interrupt mask will be written.
	 * @param[in] portNumber Data Port number. Valid value ranges from 0 to 63.
	 * @param[in] pD Pointer to driver's private data object.
	 * @return EOK On success.
	 * @return EINVAL If portNumber is invalid.
	 */
	uint32_t (*getDataPortInterrupts)(void* pD, uint8_t portNumber, uint8_t* interruptMask);

	/**
	 * Clears Data Port FIFO. Used when Data Port FIFO is accessed
	 * through AHB.
	 * @param[in] portNumber Data Port number. Valid value ranges from 0 to 63.
	 * @param[in] pD Pointer to driver's private data object.
	 * @return EOK On success.
	 * @return EINVAL If pD is NULL or portNumber is invalid.
	 */
	uint32_t (*clearDataPortFifo)(void* pD, uint8_t portNumber);

	/**
	 * Sets (enable or disable) Presence Rate Generation.
	 * @param[in] enable If true Presence Rate Generation for specified Data Port will be enabled; if not then it will be disabled.
	 * @param[in] portNumber Data Port number. Valid value ranges from 0 to 63.
	 * @param[in] pD Pointer to driver's private data object.
	 * @return EOK On success.
	 * @return EINVAL If pD is NULL or portNumber is invalid.
	 */
	uint32_t (*setPresenceRateGeneration)(void* pD, uint8_t portNumber, bool enable);

	/**
	 * Obtains information about Presence Rate Generation.
	 * @param[out] enable Pointer to place where information about Presence Rate Generation will be written.
	 * @param[in] portNumber Data Port number. Valid value ranges from 0 to 63.
	 * @param[in] pD Pointer to driver's private data object.
	 * @return EOK On success.
	 * @return EINVAL If pD or enabled is NULL or portNumber is invalid.
	 */
	uint32_t (*getPresenceRateGeneration)(void* pD, uint8_t portNumber, bool* enable);

	/**
	 * Assigns callbacks for receiving SLIMbus messages
	 * @param[in] msgCallbacks SLIMbus Messages Callbacks.
	 * @param[in] pD Pointer to driver's private data object.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*assignMessageCallbacks)(void* pD, CSMI_MessageCallbacks* msgCallbacks);

	/**
	 * Send Raw SLIMbus Message (bytes)
	 * @param[in] messageLength Raw message length.
	 * @param[in] message Pointer to raw message.
	 * @param[in] pD Pointer to driver's private data object.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*sendRawMessage)(void* pD, void* message, uint8_t messageLength);

	/**
	 * Send SLIMbus message.
	 * @param[in] message Pointer to struct message.
	 * @param[in] pD Pointer to driver's private data object.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*sendMessage)(void* pD, CSMI_Message* message);

	/**
	 * Read contents of SLIMbus Manager's register. Register Address must
	 * be aligned to 32-bits.
	 * @param[out] regContent Register data output.
	 * @param[in] regAddress Register address.
	 * @param[in] pD Pointer to driver's private data object.
	 * @return 0 on success
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*getRegisterValue)(void* pD, uint16_t regAddress, uint32_t* regContent);

	/**
	 * Write contents to SLIMbus Manager's register. Register Address
	 * must be aligned to 32-bits.
	 * @param[in] regContent Register data input.
	 * @param[in] regAddress Register address.
	 * @param[in] pD Pointer to driver's private data object.
	 * @return 0 on success
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*setRegisterValue)(void* pD, uint16_t regAddress, uint32_t regContent);

	/**
	 * Sets message channel Lapse. 4-bit variable defining number of
	 * superframes for which messages channel usage is being monitored to
	 * not exceed 75% bandwidth. If message channel usage exceeds 75% in
	 * MCH_LAPSE+1 superframes in a row, then MCH_INT can be generated,
	 * if enabled.
	 * @param[in] mchLapse New Message Channel Lapse value
	 * @param[in] pD Pointer to driver's private data object.
	 * @return 0 on success
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*setMessageChannelLapse)(void* pD, uint8_t mchLapse);

	/**
	 * Returns current value of message channel Lapse.
	 * @param[out] mchLapse Current Message Channel Lapse value
	 * @param[in] pD Pointer to driver's private data object.
	 * @return 0 on success
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*getMessageChannelLapse)(void* pD, uint8_t* mchLapse);

	/**
	 * Returns current value of message channel usage.
	 * @param[out] mchUsage Current Message Channel Usage
	 * @param[in] pD Pointer to driver's private data object.
	 * @return 0 on success
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*getMessageChannelUsage)(void* pD, uint16_t* mchUsage);

	/**
	 * Returns current value of message channel capacity.
	 * @param[out] mchCapacity Current Message Channel Capacity
	 * @param[in] pD Pointer to driver's private data object.
	 * @return 0 on success
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*getMessageChannelCapacity)(void* pD, uint16_t* mchCapacity);

	/**
	 * Enable or Disable Sniffer Mode. If 1, the Sniffer functionality is
	 * enabled. In this mode all messages tracked in the message channel
	 * are written to RX_FIFO, regardless of response status.
	 * @param[in] state New state
	 * @param[in] pD Pointer to driver's private data object.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*setSnifferMode)(void* pD, bool state);

	/**
	 * Returns state of Sniffer Mode feature.
	 * @param[out] state Current state
	 * @param[in] pD Pointer to driver's private data object.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*getSnifferMode)(void* pD, bool* state);

	/**
	 * Enable or Disable internal Framer. If 1, the internal Framer
	 * device is enabled. If set 0, the internal Framer device is
	 * disabled.
	 * @param[in] state New state
	 * @param[in] pD Pointer to driver's private data object.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*setFramerEnabled)(void* pD, bool state);

	/**
	 * Returns state of internal Framer.
	 * @param[out] state Current state
	 * @param[in] pD Pointer to driver's private data object.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*getFramerEnabled)(void* pD, bool* state);

	/**
	 * Enable or Disable internal Generic Device. If 1, the internal
	 * Generic device is enabled. If set 0, the internal Generic device
	 * is disabled.
	 * @param[in] state New state
	 * @param[in] pD Pointer to driver's private data object.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*setDeviceEnabled)(void* pD, bool state);

	/**
	 * Returns state of internal Generic Device.
	 * @param[out] state Current state
	 * @param[in] pD Pointer to driver's private data object.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*getDeviceEnabled)(void* pD, bool* state);

	/**
	 * If set to 1, then whole SLIMbus Manager will be detached from
	 * SLIMbus. While detached it will not be able to receive and send
	 * messages, and internal Framer and Generic Device will be disabled.
	 * It will also lose assigned Logical Addresses, and will have to be
	 * enumerated again
	 * @param[in] state New state
	 * @param[in] pD Pointer to driver's private data object.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*setGoAbsent)(void* pD, bool state);

	/**
	 * Informs if SLIMbus Manager Component was set to Go Absent.
	 * @param[out] state Current state
	 * @param[in] pD Pointer to driver's private data object.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*getGoAbsent)(void* pD, bool* state);

	/**
	 * Sets Framer configuration.
	 * @param[in] framerConfig Pointer to structure containing Framer configuration.
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*setFramerConfig)(void* pD, CSMI_FramerConfig* framerConfig);

	/**
	 * Obtains Framer configuration.
	 * @param[out] framerConfig Pointer to structure to which Framer configuration will be written.
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*getFramerConfig)(void* pD, CSMI_FramerConfig* framerConfig);

	/**
	 * Sets Generic Device configuration.
	 * @param[in] genericDeviceConfig Pointer to structure containing Generic Device configuration.
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*setGenericDeviceConfig)(void* pD, CSMI_GenericDeviceConfig* genericDeviceConfig);

	/**
	 * Obtains Generic Device configuration.
	 * @param[out] genericDeviceConfig Pointer to structure to which Generic Device configuration will be written.
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*getGenericDeviceConfig)(void* pD, CSMI_GenericDeviceConfig* genericDeviceConfig);

	/**
	 * Obtains status of Data port implemented in the Generic Device in
	 * Manager component.
	 * @param[in] portNumber Selected Port Number
	 * @param[out] portStatus Pointer to structure to which Framer configuration will be written.
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*getDataPortStatus)(void* pD, uint8_t portNumber, CSMI_DataPortStatus* portStatus);

	/**
	 * When the IP is in PAUSE state, and the Framer function is enabled,
	 * then calling this function forces to generate a toggle at SLIMbus
	 * data line, what in turn wakes-up SLIMbus from PAUSE state. When
	 * the Framer function is enabled, internal Framer is active and
	 * pausing at Root Frequency change is enabled using
	 * pauseAtRootFrequencyChange parameter, then calling this function
	 * resumes the operation of the Framer after change of Root
	 * Frequency.
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*unfreeze)(void* pD);

	/**
	 * Cancels pending configuration (clears CFG_STROBE).
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*cancelConfiguration)(void* pD);

	/**
	 * Returns status of Manager Synchronization with SLIMbus
	 * @param[out] sfSync If 1, the SLIMbus Manager achieved superframe synchronization. Not returned if NULL was passed.
	 * @param[out] sfbSync If 1, the SLIMbus Manager achieved superframe block synchronization. Not returned if NULL was passed.
	 * @param[out] mSync If 1, the SLIMbus Manager achieved message synchronization. Not returned if NULL was passed.
	 * @param[out] fSync If 1, the SLIMbus Manager achieved frame synchronization. Not returned if NULL was passed.
	 * @param[out] phSync If 1, the SLIMbus Manager achieved phase synchronization and clock signal generated by the Generic device is valid. Not returned if NULL was passed.
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*getStatusSynchronization)(void* pD, bool* fSync, bool* sfSync, bool* mSync, bool* sfbSync, bool* phSync);

	/**
	 * Informs if SLIMbus Manager is detached from the bus after
	 * successful transmission of REPORT_ABSENT message.
	 * @param[out] detached If 1, the SLIMbus Manager is detached from the bus after successful transmission of REPORT_ABSENT message.
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*getStatusDetached)(void* pD, bool* detached);

	/**
	 * Returns information about SLIMbus operation properties
	 * @param[out] subframeMode This variable contains the Subframe Mode read from the Framing Information during superframe synchronization and after reconfiguration (from the payload of the NEXT_SUBFRAME_MODE message sent by the SLIMbus Manager). Not returned if NULL was passed.
	 * @param[out] clockGear This variable contains the Clock Gear read from the Framing Information during superframe synchronization and after reconfiguration (from the payload of the NEXT_SUBFRAME_MODE message sent by the SLIMbus Manager). Not returned if NULL was passed.
	 * @param[out] rootFr This variable contains the Root Frequency read from the Framing Information during superframe synchronization and after reconfiguration (from the payload of the NEXT_SUBFRAME_MODE message sent by the SLIMbus Manager). Not returned if NULL was passed.
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*getStatusSlimbus)(void* pD, CSMI_SubframeMode* subframeMode, CSMI_ClockGear* clockGear, CSMI_RootFrequency* rootFr);

	/**
	 * Sends ASSIGN_LOGICAL_ADDRESS Message, which assigns a Logical
	 * Address to a Device.
	 * @param[in] newLa New Logical Address
	 * @param[in] destinationEa Destination's Enumeration Address
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgAssignLogicalAddress)(void* pD, uint64_t destinationEa, uint8_t newLa);

	/**
	 * Sends RESET_DEVICE Message, which informs a Device to perform its
	 * reset procedure.
	 * @param[in] destinationLa Destination's Logic Address
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgResetDevice)(void* pD, uint8_t destinationLa);

	/**
	 * Sends CHANGE_LOGICAL_ADDRESS Message, which changes the value of
	 * the Logical Address of the destination Device.
	 * @param[in] destinationLa Destination's Logic Address
	 * @param[in] newLa New Logical Address
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgChangeLogicalAddress)(void* pD, uint8_t destinationLa, uint8_t newLa);

	/**
	 * Sends CHANGE_ARBITRATION_PRIORITY Message, which is sent to one or
	 * more Devices to change the value of their Arbitration Priority.
	 * @param[in] broadcast Broadcast Message to all devices
	 * @param[in] destinationLa Destination's Logic Address, used if broadcast = 0
	 * @param[in] newArbitrationPriority New Arbitration Priority
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgChangeArbitrationPriority)(void* pD, bool broadcast, uint8_t destinationLa, CSMI_ArbitrationPriority newArbitrationPriority);

	/**
	 * Sends REQUEST_SELF_ANNOUNCEMENT Message, which requests an
	 * unenumerated Device retransmit a REPORT_PRESENT Message.
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgRequestSelfAnnouncement)(void* pD);

	/**
	 * Sends CONNECT_SOURCE Message, which informs the Device to connect
	 * the specified Port, to the specified Data Channel. The Port shall
	 * act as the data source for the Data Channel.
	 * @param[in] destinationLa Destination's Logic Address
	 * @param[in] channelNumber Data Channel Number
	 * @param[in] portNumber Port Number to be connected to data channel
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgConnectSource)(void* pD, uint8_t destinationLa, uint8_t portNumber, uint8_t channelNumber);

	/**
	 * Sends CONNECT_SINK Message, which informs the Device to connect
	 * the specified Port, to the specified Data Channel. The Port shall
	 * act as the data sink for the Data Channel.
	 * @param[in] destinationLa Destination's Logic Address
	 * @param[in] channelNumber Data Channel Number
	 * @param[in] portNumber Port Number to be connected to data channel
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgConnectSink)(void* pD, uint8_t destinationLa, uint8_t portNumber, uint8_t channelNumber);

	/**
	 * Sends DISCONNECT_PORT Message, which informs the Device to
	 * disconnect the Port specified by Port Number.
	 * @param[in] destinationLa Destination's Logic Address
	 * @param[in] portNumber Port Number to be disconnected from data channel
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgDisconnectPort)(void* pD, uint8_t destinationLa, uint8_t portNumber);

	/**
	 * Sends CHANGE_CONTENT Message, which broadcasts detailed
	 * information about the structure of the Data Channel contents.
	 * @param[in] dataLength Data Length
	 * @param[in] dataType Data Type
	 * @param[in] presenceRate Presence Rate
	 * @param[in] frequencyLockedBit Frequency Locked Bit
	 * @param[in] channelLink Channel Link
	 * @param[in] channelNumber Data Channel Number
	 * @param[in] pD Pointer to driver's private data.
	 * @param[in] auxiliaryBitFormat Auxiliary Bit Format
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgChangeContent)(void* pD, uint8_t channelNumber, bool frequencyLockedBit, CSMI_PresenceRate presenceRate, CSMI_AuxFieldFormat auxiliaryBitFormat, CSMI_DataType dataType, bool channelLink, uint8_t dataLength);

	/**
	 * Sends REQUEST_INFORMATION Message, which instructs a Device to
	 * send the indicated Information Slice.
	 * @param[in] broadcast Broadcast Message to all devices
	 * @param[in] destinationLa Destination's Logic Address, used if broadcast = 0
	 * @param[in] transactionId Transaction ID
	 * @param[in] elementCode Element Code
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgRequestInformation)(void* pD, bool broadcast, uint8_t destinationLa, uint8_t transactionId, uint16_t elementCode);

	/**
	 * Sends REQUEST_CLEAR_INFORMATION Message, which instructs a Device
	 * to send the indicated Information Slice and to clear all, or
	 * parts, of that Information Slice.
	 * @param[in] destinationLa Destination's Logic Address, used if broadcast = 0
	 * @param[in] clearMaskSize Clear Mask size
	 * @param[in] broadcast Broadcast Message to all devices
	 * @param[in] clearMask Pointer to Clear Mask (0 (NULL) to 16 bytes). If the size of Clear Mask is smaller than the size of the Information Slice, the Device shall pad the MSBs of Clear Mask with ones. If the size of Clear Mask is larger than the size of the Information Slice, the Device shall change only the portion of the Information Map corresponding to the identified Information Slice.
	 * @param[in] elementCode Element Code
	 * @param[in] pD Pointer to driver's private data.
	 * @param[in] transactionId Transaction ID
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgRequestClearInformation)(void* pD, bool broadcast, uint8_t destinationLa, uint8_t transactionId, uint16_t elementCode, uint8_t* clearMask, uint8_t clearMaskSize);

	/**
	 * Sends CLEAR_INFORMATION Message, which instructs a Device to
	 * selectively clear all, or parts, of the Information Slice.
	 * @param[in] destinationLa Destination's Logic Address, used if broadcast = 0
	 * @param[in] clearMaskSize Clear Mask size
	 * @param[in] broadcast Broadcast Message to all devices
	 * @param[in] clearMask Pointer to Clear Mask (0 (NULL) to 16 bytes). If the size of Clear Mask is smaller than the size of the Information Slice, the Device shall pad the MSBs of Clear Mask with ones. If the size of Clear Mask is larger than the size of the Information Slice, the Device shall change only the portion of the Information Map corresponding to the identified Information Slice.
	 * @param[in] elementCode Element Code
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgClearInformation)(void* pD, bool broadcast, uint8_t destinationLa, uint16_t elementCode, uint8_t* clearMask, uint8_t clearMaskSize);

	/**
	 * Sends BEGIN_RECONFIGURATION Message, which informs all Devices of
	 * the start of a Reconfiguration Sequence.
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgBeginReconfiguration)(void* pD);

	/**
	 * Sends Message NEXT_ACTIVE_FRAMER, which informs a Device that the
	 * active Framer is going to hand over the role of Framer to a
	 * specified inactive Framer with the Logical Address.
	 * @param[in] outgoingFramerClockCycles Number of Outgoing Framer Clock cycles
	 * @param[in] incomingFramerLa Incoming Framer's Logic Address
	 * @param[in] pD Pointer to driver's private data.
	 * @param[in] incomingFramerClockCycles Number of Incoming Framer Clock cycles
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgNextActiveFramer)(void* pD, uint8_t incomingFramerLa, uint16_t outgoingFramerClockCycles, uint16_t incomingFramerClockCycles);

	/**
	 * Sends Message NEXT_SUBFRAME_MODE, which informs all destinations
	 * that the active Manager intends to change the Subframe Mode.
	 * @param[in] newSubframeMode New Subframe Mode
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgNextSubframeMode)(void* pD, CSMI_SubframeMode newSubframeMode);

	/**
	 * Sends NEXT_CLOCK_GEAR Message, which informs all destinations that
	 * the active Manager intends to change the Clock Gear.
	 * @param[in] newClockGear New Clock Gear
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgNextClockGear)(void* pD, CSMI_ClockGear newClockGear);

	/**
	 * Sends NEXT_ROOT_FREQUENCY Message, which informs all destinations
	 * that the active Manager intends to change the Root Frequency.
	 * @param[in] newRootFrequency New Root Frequency
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgNextRootFrequency)(void* pD, CSMI_RootFrequency newRootFrequency);

	/**
	 * Sends NEXT_PAUSE_CLOCK Message, which informs all destinations
	 * that the active Manager intends to have the active Framer pause
	 * the bus.
	 * @param[in] newRestartTime New Restart Time
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgNextPauseClock)(void* pD, CSMI_RestartTime newRestartTime);

	/**
	 * Sends NEXT_RESET_BUS Message, which informs all destinations that
	 * the active Manager intends to have the active Framer reset the
	 * bus.
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgNextResetBus)(void* pD);

	/**
	 * Sends NEXT_SHUTDOWN_BUS Message, which informs all destinations
	 * that the active Manager intends to shutdown the bus.
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgNextShutdownBus)(void* pD);

	/**
	 * Sends NEXT_DEFINE_CHANNEL Message, which informs a Device that the
	 * active Manager intends to define the parameters of a Data Channel.
	 * @param[in] channelNumber Data Channel Number
	 * @param[in] segmentDistribution Segment Distribution
	 * @param[in] transportProtocol Transport Protocol
	 * @param[in] pD Pointer to driver's private data.
	 * @param[in] segmentLength Segment Length
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgNextDefineChannel)(void* pD, uint8_t channelNumber, CSMI_TransportProtocol transportProtocol, uint16_t segmentDistribution, uint8_t segmentLength);

	/**
	 * Sends NEXT_DEFINE_CONTENT Message, which informs a Device how the
	 * Data Channel CN shall be used.
	 * @param[in] dataLength Data Length
	 * @param[in] dataType Data Type
	 * @param[in] presenceRate Presence Rate
	 * @param[in] frequencyLockedBit Frequency Locked Bit
	 * @param[in] channelLink Channel Link
	 * @param[in] channelNumber Data Channel Number
	 * @param[in] pD Pointer to driver's private data.
	 * @param[in] auxiliaryBitFormat Auxiliary Bit Format
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgNextDefineContent)(void* pD, uint8_t channelNumber, bool frequencyLockedBit, CSMI_PresenceRate presenceRate, CSMI_AuxFieldFormat auxiliaryBitFormat, CSMI_DataType dataType, bool channelLink, uint8_t dataLength);

	/**
	 * Sends NEXT_ACTIVATE_CHANNEL Message, which is used to switch on
	 * the specified Data Channel.
	 * @param[in] channelNumber Data Channel Number
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgNextActivateChannel)(void* pD, uint8_t channelNumber);

	/**
	 * Sends NEXT_DEACTIVATE_CHANNEL Message, which is used to switch off
	 * the specified Data Channel.
	 * @param[in] channelNumber Data Channel Number
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgNextDeactivateChannel)(void* pD, uint8_t channelNumber);

	/**
	 * Sends NEXT_REMOVE_CHANNEL Message, which is used to switch off and
	 * disconnect the specified Data Channel.
	 * @param[in] channelNumber Data Channel Number
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgNextRemoveChannel)(void* pD, uint8_t channelNumber);

	/**
	 * Sends RECONFIGURE_NOW Message, which is used to change the bus
	 * configuration.
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgReconfigureNow)(void* pD);

	/**
	 * Sends REQUEST_VALUE Message, which instructs a Device to send the
	 * indicated Value Slice.
	 * @param[in] broadcast Broadcast Message to all devices
	 * @param[in] destinationLa Destination's Logic Address, used if broadcast = 0
	 * @param[in] transactionId Transaction ID
	 * @param[in] elementCode Element Code
	 * @param[in] pD Pointer to driver's private data.
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgRequestValue)(void* pD, bool broadcast, uint8_t destinationLa, uint8_t transactionId, uint16_t elementCode);

	/**
	 * Sends REQUEST_CHANGE_VALUE Message, which instructs a Device to
	 * send the specified Value Slice and to update that Value Slice.
	 * @param[in] destinationLa Destination's Logic Address, used if broadcast = 0
	 * @param[in] valueUpdate Pointer to Value Update (0 (NULL) to 16 bytes).
	 * @param[in] broadcast Broadcast Message to all devices
	 * @param[in] elementCode Element Code
	 * @param[in] pD Pointer to driver's private data.
	 * @param[in] valueUpdateSize Value Update size
	 * @param[in] transactionId Transaction ID
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgRequestChangeValue)(void* pD, bool broadcast, uint8_t destinationLa, uint8_t transactionId, uint16_t elementCode, uint8_t* valueUpdate, uint8_t valueUpdateSize);

	/**
	 * Sends CHANGE_VALUE Message, which instructs a Device to update the
	 * indicated Value Slice.
	 * @param[in] destinationLa Destination's Logic Address, used if broadcast = 0
	 * @param[in] valueUpdate Pointer to Value Update (0 (NULL) to 16 bytes).
	 * @param[in] broadcast Broadcast Message to all devices
	 * @param[in] elementCode Element Code
	 * @param[in] pD Pointer to driver's private data.
	 * @param[in] valueUpdateSize Value Update size
	 * @return 0 on success
	 * @return EIO if operation failed
	 * @return EINVAL if input parameters are invalid
	 */
	uint32_t (*msgChangeValue)(void* pD, bool broadcast, uint8_t destinationLa, uint16_t elementCode, uint8_t* valueUpdate, uint8_t valueUpdateSize);

} CSMI_OBJ;

/**
 * In order to access the CSMI APIs, the upper layer software must call
 * this global function to obtain the pointer to the driver object.
 * @return CSMI_OBJ* Driver Object Pointer
 */
extern CSMI_OBJ *CSMI_GetInstance(void);

/**
 *	@}
 */


#endif	/* _CSMI_H_ */
