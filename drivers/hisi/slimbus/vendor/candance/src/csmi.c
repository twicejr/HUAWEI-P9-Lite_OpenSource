/**********************************************************************
 * Copyright (C) 2014 Cadence Design Systems
 * All rights reserved.
 **********************************************************************

 **********************************************************************
 * Cadence Slimbus Manager Low Interface
 **********************************************************************/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/delay.h>

#include "cdn_stdint.h"
#include "cdn_errno.h"
#include <csmi.h>
#include <cdn_stdtypes.h>
#include <cdn_errno.h>
#include "csmi_sanity.h"
#include "csmi_regs.h"
#include "cps.h"
#include "slimbus_debug.h"

/*lint -e750*/
/* SLIMbus Message Fields */
#define CSMI_MESSAGE_ARBITRATION_TYPE_MASK					   0x0F
#define CSMI_MESSAGE_ARBITRATION_TYPE_SHIFT 				   4
#define CSMI_MESSAGE_ARBITRATION_TYPE_OFFSET				   0
#define CSMI_MESSAGE_ARBITRATION_EXTENSION_MASK 			   0x01
#define CSMI_MESSAGE_ARBITRATION_EXTENSION_SHIFT			   3
#define CSMI_MESSAGE_ARBITRATION_EXTENSION_OFFSET			   0
#define CSMI_MESSAGE_ARBITRATION_PRIORITY_MASK				   0x07
#define CSMI_MESSAGE_ARBITRATION_PRIORITY_SHIFT 			   0
#define CSMI_MESSAGE_ARBITRATION_PRIORITY_OFFSET			   0
#define CSMI_MESSAGE_SOURCE_ADDRESS_OFFSET					   1

#define CSMI_MESSAGE_MESSAGE_TYPE_MASK						   0x7
#define CSMI_MESSAGE_MESSAGE_TYPE_SHIFT 					   5
#define CSMI_MESSAGE_MESSAGE_TYPE_OFFSET					   0
#define CSMI_MESSAGE_REMAINING_LENGTH_MASK					   0x1F
#define CSMI_MESSAGE_REMAINING_LENGTH_SHIFT 				   0
#define CSMI_MESSAGE_REMAINING_LENGTH_OFFSET				   0
#define CSMI_MESSAGE_MESSAGE_CODE_MASK						   0x7F
#define CSMI_MESSAGE_MESSAGE_CODE_SHIFT 					   0
#define CSMI_MESSAGE_MESSAGE_CODE_OFFSET					   1
#define CSMI_MESSAGE_MESSAGE_DESTINATION_TYPE_MASK			   0x3
#define CSMI_MESSAGE_MESSAGE_DESTINATION_TYPE_SHIFT 		   4
#define CSMI_MESSAGE_MESSAGE_DESTINATION_TYPE_OFFSET		   2
#define CSMI_MESSAGE_PRIMARY_INTEGRITY_MASK 				   0xF
#define CSMI_MESSAGE_PRIMARY_INTEGRITY_SHIFT				   0
#define CSMI_MESSAGE_PRIMARY_INTEGRITY_OFFSET				   2
#define CSMI_MESSAGE_DESTINATION_ADDRESS_OFFSET 			   3
#define CSMI_MESSAGE_MESSAGE_INTEGRITY_OFFSET				   0
#define CSMI_MESSAGE_MESSAGE_INTEGRITY_MASK 				   0xF
#define CSMI_MESSAGE_MESSAGE_INTEGRITY_SHIFT				   4
#define CSMI_MESSAGE_RESPONSE_CODE_OFFSET					   0
#define CSMI_MESSAGE_RESPONSE_CODE_MASK 					   0xF
#define CSMI_MESSAGE_RESPONSE_CODE_SHIFT					   0

/* Other Message related defines */
#define CSMI_MESSAGE_ARBITRATION_LENGTH_LONG				   7
#define CSMI_MESSAGE_ARBITRATION_LENGTH_SHORT				   2
#define CSMI_MESSAGE_HEADER_LENGTH_BROADCAST				   3
#define CSMI_MESSAGE_HEADER_LENGTH_SHORT					   4
#define CSMI_MESSAGE_HEADER_LENGTH_LONG 					   9

/* SLIMBus Messages Codes Defines */
/* Shared Message Channel Management Messages */
#define CSMI_MESSAGE_CODE_REPORT_PRESENT					   0x01
#define CSMI_MESSAGE_CODE_ASSIGN_LOGICAL_ADDRESS			   0x02
#define CSMI_MESSAGE_CODE_RESET_DEVICE						   0x04
#define CSMI_MESSAGE_CODE_CHANGE_LOGICAL_ADDRESS			   0x08
#define CSMI_MESSAGE_CODE_CHANGE_ARBITRATION_PRIORITY		   0x09
#define CSMI_MESSAGE_CODE_REQUEST_SELF_ANNOUNCEMENT 		   0x0C
#define CSMI_MESSAGE_CODE_REPORT_ABSENT 					   0x0F
/* Data Space Management Messages */
#define CSMI_MESSAGE_CODE_CONNECT_SOURCE					   0x10
#define CSMI_MESSAGE_CODE_CONNECT_SINK						   0x11
#define CSMI_MESSAGE_CODE_DISCONNECT_PORT					   0x14
#define CSMI_MESSAGE_CODE_CHANGE_CONTENT					   0x18
/* Information Messages */
#define CSMI_MESSAGE_CODE_REQUEST_INFORMATION				   0x20
#define CSMI_MESSAGE_CODE_REQUEST_CLEAR_INFORMATION 		   0x21
#define CSMI_MESSAGE_CODE_REPLY_INFORMATION 				   0x24
#define CSMI_MESSAGE_CODE_CLEAR_INFORMATION 				   0x28
#define CSMI_MESSAGE_CODE_REPORT_INFORMATION				   0x29
/* Value Element Messages */
#define CSMI_MESSAGE_CODE_REQUEST_VALUE 					   0x60
#define CSMI_MESSAGE_CODE_REQUEST_CHANGE_VALUE				   0x61
#define CSMI_MESSAGE_CODE_REPLY_VALUE						   0x64
#define CSMI_MESSAGE_CODE_CHANGE_VALUE						   0x68
/* Synchronized Event Messages */
#define CSMI_MESSAGE_CODE_BEGIN_RECONFIGURATION 			   0x40
#define CSMI_MESSAGE_CODE_NEXT_ACTIVE_FRAMER				   0x44
#define CSMI_MESSAGE_CODE_NEXT_SUBFRAME_MODE				   0x45
#define CSMI_MESSAGE_CODE_NEXT_CLOCK_GEAR					   0x46
#define CSMI_MESSAGE_CODE_NEXT_ROOT_FREQUENCY				   0x47
#define CSMI_MESSAGE_CODE_NEXT_PAUSE_CLOCK					   0x4A
#define CSMI_MESSAGE_CODE_NEXT_RESET_BUS					   0x4B
#define CSMI_MESSAGE_CODE_NEXT_SHUTDOWN_BUS 				   0x4C
#define CSMI_MESSAGE_CODE_NEXT_DEFINE_CHANNEL				   0x50
#define CSMI_MESSAGE_CODE_NEXT_DEFINE_CONTENT				   0x51
#define CSMI_MESSAGE_CODE_NEXT_ACTIVATE_CHANNEL 			   0x54
#define CSMI_MESSAGE_CODE_NEXT_DEACTIVATE_CHANNEL			   0x55
#define CSMI_MESSAGE_CODE_NEXT_REMOVE_CHANNEL				   0x58
#define CSMI_MESSAGE_CODE_RECONFIGURE_NOW					   0x5F


/* SLIMbus Payload Fields */
#define CSMI_MESSAGE_PAYLOAD_ELEMENT_CODE_BYTE_ADDRESS_SHIFT   4
#define CSMI_MESSAGE_PAYLOAD_ELEMENT_CODE_BYTE_ADDRESS_MASK    0x0FFF
#define CSMI_MESSAGE_PAYLOAD_ELEMENT_CODE_SLICE_SIZE_SHIFT	   0
#define CSMI_MESSAGE_PAYLOAD_ELEMENT_CODE_SLICE_SIZE_MASK	   0x07
#define CSMI_MESSAGE_PAYLOAD_ELEMENT_CODE_BIT_NUMBER_SHIFT	   0
#define CSMI_MESSAGE_PAYLOAD_ELEMENT_CODE_BIT_NUMBER_MASK	   0x07
#define CSMI_MESSAGE_PAYLOAD_ELEMENT_CODE_ACCESS_TYPE_SHIFT    3
#define CSMI_MESSAGE_PAYLOAD_ELEMENT_CODE_ACCESS_TYPE_MASK	   0x01
#define CSMI_MESSAGE_PAYLOAD_DATA_CHANNEL_NUMBER_SHIFT		   0
#define CSMI_MESSAGE_PAYLOAD_DATA_CHANNEL_NUMBER_MASK		   0xFF
#define CSMI_MESSAGE_PAYLOAD_PRESENCE_RATE_SHIFT			   0
#define CSMI_MESSAGE_PAYLOAD_PRESENCE_RATE_MASK 			   0x7F
#define CSMI_MESSAGE_PAYLOAD_FREQUENCY_LOCKED_BIT_SHIFT 	   7
#define CSMI_MESSAGE_PAYLOAD_FREQUENCY_LOCKED_BIT_MASK		   0x01
#define CSMI_MESSAGE_PAYLOAD_DATA_TYPE_SHIFT				   0
#define CSMI_MESSAGE_PAYLOAD_DATA_TYPE_MASK 				   0x0F
#define CSMI_MESSAGE_PAYLOAD_AUXILIARY_BIT_FORMAT_SHIFT 	   4
#define CSMI_MESSAGE_PAYLOAD_AUXILIARY_BIT_FORMAT_MASK		   0x0F
#define CSMI_MESSAGE_PAYLOAD_DATA_LENGTH_SHIFT				   0
#define CSMI_MESSAGE_PAYLOAD_DATA_LENGTH_MASK				   0x1F
#define CSMI_MESSAGE_PAYLOAD_CHANNEL_LINK_SHIFT 			   5
#define CSMI_MESSAGE_PAYLOAD_CHANNEL_LINK_MASK				   0x01
#define CSMI_MESSAGE_PAYLOAD_SEGMENT_DISTRIBUTION_LOW_SHIFT    0
#define CSMI_MESSAGE_PAYLOAD_SEGMENT_DISTRIBUTION_LOW_MASK	   0xFF
#define CSMI_MESSAGE_PAYLOAD_SEGMENT_DISTRIBUTION_HIGH_SHIFT   0
#define CSMI_MESSAGE_PAYLOAD_SEGMENT_DISTRIBUTION_HIGH_MASK    0x0F
#define CSMI_MESSAGE_PAYLOAD_TRANSPORT_PROTOCOL_SHIFT		   4
#define CSMI_MESSAGE_PAYLOAD_TRANSPORT_PROTOCOL_MASK		   0x0F
#define CSMI_MESSAGE_PAYLOAD_SEGMENT_LENGTH_SHIFT			   0
#define CSMI_MESSAGE_PAYLOAD_SEGMENT_LENGTH_MASK			   0x1F
#define CSMI_MESSAGE_PAYLOAD_PORT_NUMBER_SHIFT				   0
#define CSMI_MESSAGE_PAYLOAD_PORT_NUMBER_MASK				   0x3F
#define CSMI_MESSAGE_PAYLOAD_TRANSACTION_ID_SHIFT			   0
#define CSMI_MESSAGE_PAYLOAD_TRANSACTION_ID_MASK			   0xFF
#define CSMI_MESSAGE_PAYLOAD_LOGICAL_ADDRESS_SHIFT			   0
#define CSMI_MESSAGE_PAYLOAD_LOGICAL_ADDRESS_MASK			   0xFF
#define CSMI_MESSAGE_PAYLOAD_ARBITRATION_PRIORITY_SHIFT 	   0
#define CSMI_MESSAGE_PAYLOAD_ARBITRATION_PRIORITY_MASK		   0x07
#define CSMI_MESSAGE_PAYLOAD_OUTGOING_FRAMER_CYCLES_LOW_SHIFT  0
#define CSMI_MESSAGE_PAYLOAD_OUTGOING_FRAMER_CYCLES_LOW_MASK   0xFF
#define CSMI_MESSAGE_PAYLOAD_OUTGOING_FRAMER_CYCLES_HIGH_SHIFT 0
#define CSMI_MESSAGE_PAYLOAD_OUTGOING_FRAMER_CYCLES_HIGH_MASK  0x0F
#define CSMI_MESSAGE_PAYLOAD_INCOMING_FRAMER_CYCLES_LOW_SHIFT  4
#define CSMI_MESSAGE_PAYLOAD_INCOMING_FRAMER_CYCLES_LOW_MASK   0x0F
#define CSMI_MESSAGE_PAYLOAD_INCOMING_FRAMER_CYCLES_HIGH_SHIFT 0
#define CSMI_MESSAGE_PAYLOAD_INCOMING_FRAMER_CYCLES_HIGH_MASK  0xFF
#define CSMI_MESSAGE_PAYLOAD_SUBFRAME_MODE_SHIFT			   0
#define CSMI_MESSAGE_PAYLOAD_SUBFRAME_MODE_MASK 			   0x1F
#define CSMI_MESSAGE_PAYLOAD_CLOCK_GEAR_SHIFT				   0
#define CSMI_MESSAGE_PAYLOAD_CLOCK_GEAR_MASK				   0x0F
#define CSMI_MESSAGE_PAYLOAD_ROOT_FREQUENCY_SHIFT			   0
#define CSMI_MESSAGE_PAYLOAD_ROOT_FREQUENCY_MASK			   0x0F
#define CSMI_MESSAGE_PAYLOAD_RESTART_TIME_SHIFT 			   0
#define CSMI_MESSAGE_PAYLOAD_RESTART_TIME_MASK				   0xFF

#define CSMI_ELEMENT_CODE_BYTE_BASED_ACCESS 				   1
#define CSMI_ELEMENT_CODE_ELEMENTAL_ACCESS					   0
#define CSMI_ELEMENT_CODE_LENGTH							   2
#define CSMI_TRANSACTION_ID_LENGTH							   1


/* SLIMbus Information Elements */
/* Interface Device Class-specific Information Elements */
#define CSMI_IE_INTERFACE_DATA_SLOT_OVERLAP_ADDRESS 		   0x400
#define CSMI_IE_INTERFACE_DATA_SLOT_OVERLAP_SHIFT			   4
#define CSMI_IE_INTERFACE_DATA_SLOT_OVERLAP_MASK			   0x1
#define CSMI_IE_INTERFACE_DATA_SLOT_OVERLAP_READONLY		   0

#define CSMI_IE_INTERFACE_LOST_MS_ADDRESS					   0x400
#define CSMI_IE_INTERFACE_LOST_MS_SHIFT 					   3
#define CSMI_IE_INTERFACE_LOST_MS_MASK						   0x1
#define CSMI_IE_INTERFACE_LOST_MS_READONLY					   0

#define CSMI_IE_INTERFACE_LOST_SFS_ADDRESS					   0x400
#define CSMI_IE_INTERFACE_LOST_SFS_SHIFT					   2
#define CSMI_IE_INTERFACE_LOST_SFS_MASK 					   0x1
#define CSMI_IE_INTERFACE_LOST_SFS_READONLY 				   0

#define CSMI_IE_INTERFACE_LOST_FS_ADDRESS					   0x400
#define CSMI_IE_INTERFACE_LOST_FS_SHIFT 					   1
#define CSMI_IE_INTERFACE_LOST_FS_MASK						   0x1
#define CSMI_IE_INTERFACE_LOST_FS_READONLY					   0

#define CSMI_IE_INTERFACE_MC_TX_COL_ADDRESS 				   0x400
#define CSMI_IE_INTERFACE_MC_TX_COL_SHIFT					   0
#define CSMI_IE_INTERFACE_MC_TX_COL_MASK					   0x1
#define CSMI_IE_INTERFACE_MC_TX_COL_READONLY				   0

/* Manager Class-specific Information Elements */
#define CSMI_IE_MANAGER_ACTIVE_MANAGER_ADDRESS				   0x400
#define CSMI_IE_MANAGER_ACTIVE_MANAGER_SHIFT				   0
#define CSMI_IE_MANAGER_ACTIVE_MANAGER_MASK 				   0x1
#define CSMI_IE_MANAGER_ACTIVE_MANAGER_READONLY 			   1

/* Framer Class-specific Information Elements */
#define CSMI_IE_FRAMER_QUALITY_ADDRESS						   0x400
#define CSMI_IE_FRAMER_QUALITY_SHIFT						   6
#define CSMI_IE_FRAMER_QUALITY_MASK 						   0x3
#define CSMI_IE_FRAMER_QUALITY_READONLY 					   1

#define CSMI_IE_FRAMER_GC_TX_COL_ADDRESS					   0x400
#define CSMI_IE_FRAMER_GC_TX_COL_SHIFT						   3
#define CSMI_IE_FRAMER_GC_TX_COL_MASK						   0x1
#define CSMI_IE_FRAMER_GC_TX_COL_READONLY					   0

#define CSMI_IE_FRAMER_FI_TX_COL_ADDRESS					   0x400
#define CSMI_IE_FRAMER_FI_TX_COL_SHIFT						   2
#define CSMI_IE_FRAMER_FI_TX_COL_MASK						   0x1
#define CSMI_IE_FRAMER_FI_TX_COL_READONLY					   0

#define CSMI_IE_FRAMER_FS_TX_COL_ADDRESS					   0x400
#define CSMI_IE_FRAMER_FS_TX_COL_SHIFT						   1
#define CSMI_IE_FRAMER_FS_TX_COL_MASK						   0x1
#define CSMI_IE_FRAMER_FS_TX_COL_READONLY					   0

#define CSMI_IE_FRAMER_ACTIVE_FRAMER_ADDRESS				   0x400
#define CSMI_IE_FRAMER_ACTIVE_FRAMER_SHIFT					   0
#define CSMI_IE_FRAMER_ACTIVE_FRAMER_MASK					   0x1
#define CSMI_IE_FRAMER_ACTIVE_FRAMER_READONLY				   1

/* Core Information Elements */
#define CSMI_IE_CORE_DEVICE_CLASS_ADDRESS					   0x009
#define CSMI_IE_CORE_DEVICE_CLASS_SHIFT 					   0
#define CSMI_IE_CORE_DEVICE_CLASS_MASK						   0xFF
#define CSMI_IE_CORE_DEVICE_CLASS_READONLY					   1

#define CSMI_IE_CORE_DEVICE_CLASS_VERSION_ADDRESS			   0x008
#define CSMI_IE_CORE_DEVICE_CLASS_VERSION_SHIFT 			   0
#define CSMI_IE_CORE_DEVICE_CLASS_VERSION_MASK				   0xFF
#define CSMI_IE_CORE_DEVICE_CLASS_VERSION_READONLY			   1

#define CSMI_IE_CORE_EX_ERROR_ADDRESS						   0x000
#define CSMI_IE_CORE_EX_ERROR_SHIFT 						   3
#define CSMI_IE_CORE_EX_ERROR_MASK							   0x1
#define CSMI_IE_CORE_EX_ERROR_READONLY						   0

#define CSMI_IE_CORE_RECONFIG_OBJECTION_ADDRESS 			   0x000
#define CSMI_IE_CORE_RECONFIG_OBJECTION_SHIFT				   2
#define CSMI_IE_CORE_RECONFIG_OBJECTION_MASK				   0x1
#define CSMI_IE_CORE_RECONFIG_OBJECTION_READONLY			   1

#define CSMI_IE_CORE_DATA_TX_COL_ADDRESS					   0x000
#define CSMI_IE_CORE_DATA_TX_COL_SHIFT						   1
#define CSMI_IE_CORE_DATA_TX_COL_MASK						   0x1
#define CSMI_IE_CORE_DATA_TX_COL_READONLY					   0

#define CSMI_IE_CORE_UNSPRTD_MSG_ADDRESS					   0x000
#define CSMI_IE_CORE_UNSPRTD_MSG_SHIFT						   0
#define CSMI_IE_CORE_UNSPRTD_MSG_MASK						   0x1
#define CSMI_IE_CORE_UNSPRTD_MSG_READONLY					   0

#define CSMI_IE_CLASS_SPECIFIC_OFFSET						   0x400
#define CSMI_IE_CORE_OFFSET 								   0x0

/* Transport Protocols */
#define CSMI_TP_ISOCHRONOUS_MASK							   1
#define CSMI_TP_ISOCHRONOUS_SHIFT							   0
#define CSMI_TP_PUSHED_MASK 								   1
#define CSMI_TP_PUSHED_SHIFT								   1
#define CSMI_TP_PULLED_MASK 								   1
#define CSMI_TP_PULLED_SHIFT								   2

/* SLIMbus Device Classes */
#define CSMI_DEVICE_CLASS_MANAGER							   0xFF
#define CSMI_DEVICE_CLASS_FRAMER							   0xFE
#define CSMI_DEVICE_CLASS_INTERFACE 						   0xFD
#define CSMI_DEVICE_CLASS_GENERIC							   0x00

/* Misc defines */
#define CSMI_RX_FIFO_MSG_MAX_SIZE							   64
#define CSMI_TX_FIFO_MSG_MAX_SIZE							   64
#define CSMI_DATA_DIRECTION_SOURCE							   0
#define CSMI_DATA_DIRECTION_SINK							   1
#define CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER					   0xFF

#define CSMI_RX_FIFO_FLAG_RX_OVERFLOW						   8
#define CSMI_RX_FIFO_FLAG_RX_MSG_LEN						   0
#define CSMI_RX_FIFO_FLAG_RX_MSG_MASK						   0x3F
#define CSMI_RX_FIFO_FLAG_OFFSET							   15


/* Get/Set Message fields Macros */

/**
 * Returns Message field Mask
 * @param[in] name message field name
 * @return message field mask
 */
#define CSMI_GetMsgFieldMask(name)							   (CSMI_MESSAGE_ ## name ## _MASK)

/**
 * Returns Message field Shift bits
 * @param[in] name message field name
 * @return message field Shift bits
 */
#define CSMI_GetMsgFieldShift(name) 						   (CSMI_MESSAGE_ ## name ## _SHIFT)

/**
 * Returns Message field Offset
 * @param[in] name message field name
 * @return message field offset
 */
#define CSMI_GetMsgFieldOffset(name)						   (CSMI_MESSAGE_ ## name ## _OFFSET)

/*
 * Calculates Message field Offset
 * @param[in] name message field name
 * @param[in] offset additional offset
 * @return message field offset
 */
#define CSMI_CalcMsgFieldOffset(name, offset)				   (offset + (CSMI_GetMsgFieldOffset(name)))

/*
 * Returns Message field value
 * @param[in] source raw message byte array
 * @param[in] offset additional offset
 * @param[in] name message field name
 * @return message field value
 */
#define CSMI_GetMsgField(source, offset, name)				   ((source[CSMI_CalcMsgFieldOffset(name, offset)] >> (CSMI_GetMsgFieldShift(name))) & (CSMI_GetMsgFieldMask(name)))

/*
 * Sets Message field value
 * @param[in] target raw message byte array
 * @param[in] value message field value
 * @param[in] offset additional offset
 * @param[in] name message field name
 */
#define CSMI_SetMsgField(target, value, offset, name)		   target[CSMI_CalcMsgFieldOffset(name, offset)] &= ~((CSMI_GetMsgFieldMask(name)) << (CSMI_GetMsgFieldShift(name))); \
																target[CSMI_CalcMsgFieldOffset(name, offset)] |= ((value) & (CSMI_GetMsgFieldMask(name))) << (CSMI_GetMsgFieldShift(name))

/* Get/Set Message Payload Fields Macros */

/**
 * Returns Message Payload field Mask
 * @param[in] name message payload field name
 * @return message payload field mask
 */
#define CSMI_GetMsgPayloadFieldMask(name)					   (CSMI_MESSAGE_PAYLOAD_ ## name ## _MASK)

/**
 * Returns Message Payload field Shift bits
 * @param[in] name message payload field name
 * @return message payload field Shift bits
 */
#define CSMI_GetMsgPayloadFieldShift(name)					   (CSMI_MESSAGE_PAYLOAD_ ## name ## _SHIFT)

/*
 * Calculates Message payload field
 * @param[in] name message payload field name
 * @param[in] value message payload field value
 * @return message payload field
 */
#define CSMI_MsgPayloadField(name, value)					   (((value) & (CSMI_GetMsgPayloadFieldMask(name))) << (CSMI_GetMsgPayloadFieldShift(name)))

/*
 * Returns Message Payload field value
 * @param[in] payload raw message payload byte array
 * @param[in] name message field name
 * @return message payload field value
 */
#define CSMI_GetMsgPayloadField(name, payload)				   (((payload) >> (CSMI_GetMsgPayloadFieldShift(name))) & (CSMI_GetMsgPayloadFieldMask(name)))

/*
 * Calculates Byte Based Element Code
 * @param[in] byteAddress
 * @param[in] sliceSize
 * @return element code
 */
#define CSMI_ElementCodeByteBased(byteAddress, sliceSize)	   (CSMI_MsgPayloadField(ELEMENT_CODE_BYTE_ADDRESS, byteAddress) | CSMI_MsgPayloadField(ELEMENT_CODE_SLICE_SIZE, sliceSize) | CSMI_MsgPayloadField(ELEMENT_CODE_ACCESS_TYPE, CSMI_ELEMENT_CODE_BYTE_BASED_ACCESS))


/* Get/Set Information Elements Macros */

/**
 * Returns Information Element Address
 * @param[in] name information element name
 * @return information element address
 */
#define CSMI_GetIeFieldAddress(name)						   (CSMI_IE_ ## name ## _ADDRESS)

/**
 * Returns Information Element Mask
 * @param[in] name information element name
 * @return information element mask
 */
#define CSMI_GetIeFieldMask(name)							   (CSMI_IE_ ## name ## _MASK)

/**
 * Returns Information Element Shift bits
 * @param[in] name information element name
 * @return information element shift bits
 */
#define CSMI_GetIeFieldShift(name)							   (CSMI_IE_ ## name ## _SHIFT)

/**
 * Returns Information Element Read Only value
 * @param[in] name information element name
 * @return information element read only value
 */
#define CSMI_GetIeFieldReadOnly(name)						   (CSMI_IE_ ## name ## _READONLY)

/**
 * Returns Information Element Shifted Mask
 * @param[in] name information element name
 * @return information element shifted mask
 */
#define CSMI_GetIeMaskShifted(name) 						   ((CSMI_GetIeFieldMask(name)) << (CSMI_GetIeFieldShift(name)))

/**
 * Returns Information Element field value
 * @param[in] is source information slice
 * @param[in] name information element field name
 * @return information element value
 */
#define CSMI_GetIeField(name, is)							   (((is) >> CSMI_GetIeFieldShift(name)) & CSMI_GetIeFieldMask(name))

/**
 * Assigns Information Element value with Byte Access to target variable
 * @param[out] output target variable
 * @param[in] name information element field name
 * @param[in] address source information slice address
 * @param[in] is source information slice
 */
#define CSMI_GetIeByteAccess(output, name, address, is) 	   if ((CSMI_GetIeFieldAddress(name)) == (address)) \
																	output = CSMI_GetIeField(name, (is))
/**
 * Assigns Information Element value with Elemental Access to target variable
 * @param[out] output target variable
 * @param[in] name information element field name
 * @param[in] address source information slice address
 * @param[in] bitNumber source information slice bit number
 * @param[in] is source information slice
 */
#define CSMI_GetIeElementalAccess(output, name, address, bitNumber, is) \
																if (((CSMI_GetIeFieldAddress(name)) == (address)) && ((CSMI_GetIeFieldShift(name)) == (bitNumber))) \
																	output = (is) & (CSMI_GetIeFieldMask(name))


/**
 * Sets up Information Element mask with Byte Access to target variable
 * If Information Element is not clearable (is read-only) it will be removed from clear mask
 * @param[in] name information element field name
 * @param[in] address source information slice address
 * @param[inout] is source information slice
 */
#define CSMI_ClearIeByteAccess(name, address, is)			   if ((CSMI_GetIeFieldReadOnly(name)) && ((CSMI_GetIeFieldAddress(name)) == (address))) \
																	is &= (uint8_t)(~(CSMI_GetIeMaskShifted(name)))

/**
 * Sets up Information Element mask with Elemental Access to target variable
 * If Information Element is not clearable (is read-only) it will be removed from clear mask
 * @param[in] name information element field name
 * @param[in] address source information slice address
 * @param[in] bitNumber source information slice bit number
 * @param[inout] is source information slice
 */
#define CSMI_ClearIeElementalAccess(name, address, bitNumber, is) \
																if ((CSMI_GetIeFieldReadOnly(name)) && ((CSMI_GetIeFieldAddress(name)) == (address)) && ((CSMI_GetIeFieldShift(name)) == (bitNumber))) \
																	is &= (uint8_t)(~(CSMI_GetIeFieldMask(name)))

/**
 * Returns Transport Protocol bitfield Mask
 * @param[in] name transport protocol name
 * @return Transport Protocol bitfield Mask
 */
#define CSMI_GetTpFieldMask(name)							   (CSMI_TP_ ## name ## _MASK)

/**
 * Returns Transport Protocol bitfield Shift bits
 * @param[in] name transport protocol name
 * @return Transport Protocol bitfield Shift bits
 */
#define CSMI_GetTpFieldShift(name)							   (CSMI_TP_ ## name ## _SHIFT)

/*
 * Calculates Transport Protocol bit field
 * @param[in] name transport protocol name
 * @param[in] value 1 if transport protocol is supported, 0 otherwise
 * @return transport protocol supported bitfield
 */
#define CSMI_TpField(name, value)							   (((value) & (CSMI_GetTpFieldMask(name))) << (CSMI_GetTpFieldShift(name)))

/*
 * Returns Transport Protocol bit field value
 * @param[in] name transport protocol name
 * @param[in] reg register value
 * @return 1 if transport protocol is supported, 0 otherwise
 */
#define CSMI_GetTpField(name, reg)							   (((reg) >> (CSMI_GetTpFieldShift(name))) & (CSMI_GetTpFieldMask(name)))

/**
 * Returns lower byte of variable
 * @param[in] data input data
 * @return lower byte
 */
#define CSMI_LowerByte(data)								   ((data) & 0xFF)

/**
 * Returns higher byte of variable
 * @param[in] data input data
 * @return higher byte
 */
#define CSMI_HigherByte(data)								   (((data) >> 8) & 0xFF)

/**
 * Returns lower nibble of the higher byte of variable
 * @param[in] data input data
 * @return lower nibble of higher byte
 */
#define CSMI_HigherByteLowerNibble(data)					   (((data) >> 8) & 0x0F)

/**
 * Returns 48-bit long field
 * @param[in] source source byte array
 * @param[in] offset offset of array
 * @return uint64_t with 48 bits of data
 */
#define CSMI_GetField6B(source, offset) \
	(((uint64_t)(source)[(offset)] << 40) \
	| ((uint64_t)(source)[(offset) + 1] << 32) \
	| ((uint64_t)(source)[(offset) + 2] << 24) \
	| ((uint64_t)(source)[(offset) + 3] << 16) \
	| ((uint64_t)(source)[(offset) + 4] << 8) \
	| ((uint64_t)(source)[(offset) + 5]))

/**
 * Sets 48-bit long field in target byte array
 * @param[out] target target byte array
 * @param[in] value input value
 * @param[in] offset offset of array
 */
#define CSMI_SetField6B(target, value, offset) \
	(target)[offset] = (uint8_t)((uint64_t)(value) >> 40); \
	(target)[(offset) + 1] = (uint8_t)((uint64_t)(value) >> 32); \
	(target)[(offset) + 2] = (uint8_t)((uint64_t)(value) >> 24); \
	(target)[(offset) + 3] = (uint8_t)((uint64_t)(value) >> 16); \
	(target)[(offset) + 4] = (uint8_t)((uint64_t)(value) >> 8); \
	(target)[(offset) + 5] = (uint8_t)(value)

/**
 * Returns 8-bit long field
 * @param[in] source source byte array
 * @param[in] offset offset of array
 * @return 8 bits of data
 */
#define CSMI_GetField1B(source, offset) 					   (source[offset])

/**
 * Sets 8-bit long field in target byte array
 * @param[out] target target byte array
 * @param[in] value input value
 * @param[in] offset offset of array
 */
#define CSMI_SetField1B(target, value, offset)				   (target[offset] = (value) & 0xFF)


/**
 * Reads Register's value
 * @param[in] reg register address in csmi_regs structure
 * @return register's value
 */
#define CSMI_ReadReg(reg)									   CPS_UncachedRead32((uint32_t*) &(instance->registers->reg))

/**
 * Writes Register's value
 * @param[in] reg register address in csmi_regs structure
 * @param[in] data register value
 */
#define CSMI_WriteReg(reg, data)							   CPS_UncachedWrite32((uint32_t*) &(instance->registers->reg), (data))


/*
 * Structures
 */

typedef struct csmi_regs CSMI_Registers;

typedef struct {
	uintptr_t registerBase;
	CSMI_Registers *registers;
	bool disableHardwareCrcCalculation;
	bool enumerateDevices;
	volatile bool sendingFailed;
	volatile bool sendingFinished;
	CSMI_Callbacks basicCallbacks;
	CSMI_MessageCallbacks messageCallbacks;

	//CSMI_Channel *channels[CSMI_MAX_CHANNELS];
	//uint16_t numChannels;

} CSMI_Instance;

extern int slimbus_irq_state;
extern spinlock_t slimbus_spinlock;

/*
 * Forward declarations
 */

static uint32_t CSMI_MsgAssignLogicalAddress(void* pD, uint64_t destinationEa, uint8_t newLa);
static uint32_t CSMI_MsgClearInformation(void* pD, bool broadcast, uint8_t destinationLa, uint16_t elementCode, uint8_t* clearMask, uint8_t clearMaskSize);

/*
 * Internal functions
 */

/**
 * Masks or unmasks INT_EN interrupts
 * @param[in] instance driver instance
 * @param[in] enabled mask(0) unmask(1) INT_EN interrupts
 */
static void CSMI_Set_INT_EN_Enabled(CSMI_Instance *instance, bool enabled) {
	uint32_t regval = 0;

	regval = CSMI_ReadReg(INTERRUPTS.INT_EN);
	INTERRUPTS__INT_EN__INT_EN__MODIFY(regval, enabled);
	CSMI_WriteReg(INTERRUPTS.INT_EN, regval);
}

/**
 * Convert CSMI_SliceSize enum to size [bytes]
 * @param[in] sliceSize sliceSize as enum
 * @return slice size in bytes
 */
static inline uint8_t CSMI_SliceSizeToBytes(CSMI_SliceSize sliceSize) {
	switch (sliceSize) {
	case CSMI_SS_1_BYTE:
		return 1;
	case CSMI_SS_2_BYTES:
		return 2;
	case CSMI_SS_3_BYTES:
		return 3;
	case CSMI_SS_4_BYTES:
		return 4;
	case CSMI_SS_6_BYTES:
		return 6;
	case CSMI_SS_8_BYTES:
		return 8;
	case CSMI_SS_12_BYTES:
		return 12;
	case CSMI_SS_16_BYTES:
		return 16;
	default:
	    SLIMBUS_CORE_LIMIT_ERR("slice size is invalid: %d\n", sliceSize);
		return 0;
	}
}

/**
 * Fills memory area with zeroes
 * @param[in] memPtr pointer to memory
 * @param[in] size size of memory
 */
static void CSMI_ClearMemory(void *memPtr, uint16_t size) {
	uint8_t* memory = (uint8_t*) memPtr;
	memset(memory, 0x00, size);
}

/**
 * Calculate Primary Integrity (CRC4)
 * @param[in] data pointer to message buffer
 * @param[in] offset offset
 * @param[in] dataLen number of bytes to be used for checksum
 * @param[in] initVal initial value (should be 0)
 * @return CRC4
 */
static uint32_t CSMI_CrcPrimaryIntegrity(uint8_t *data, uint8_t offset, uint8_t dataLen, uint8_t initVal) {
	uint8_t crc = initVal;
	uint8_t tmp0 = 0;
	uint8_t tmp1 = 0;
	uint8_t i, bit;

	for (i = offset; i < offset + dataLen; i++) {
		for (bit = 0; bit < 8; bit++) {
			if ((i == dataLen -1) && (bit == 4)) // Only lower four bits from last byte
				break;
			tmp0 = (((crc & 8) >> 3) ^ (((data[i] << bit) & 128) >> 7)) & 1;
			tmp1 = (((crc & 1) ^ tmp0) << 1) & 2;
			crc = ((crc << 1) & 12) | tmp1 | tmp0;
		}
	}
	return crc;
}

/**
 * Calculate Message Integrity (CRC4)
 * @param[in] data pointer to message buffer
 * @param[in] offset offset
 * @param[in] dataLen number of bytes to be used for checksum
 * @param[in] initVal initial value (should be primary integrity)
 * @return CRC4
 */
static uint32_t CSMI_CrcMessageIntegrity(uint8_t *data, uint8_t offset, uint8_t dataLen, uint8_t initVal) {
	uint8_t crc = initVal;
	uint8_t tmp0 = 0;
	uint8_t tmp1 = 0;
	uint8_t i, bit;

	for (i = offset; i < offset + dataLen; i++) {
		// Only higher four bits from first byte
		for (bit = (i == offset) ? 4 : 0; bit < 8; bit++) {
			tmp0 = (((crc & 8) >>3 ) ^ (((data[i] << bit) & 128) >> 7)) & 1;
			tmp1 = (((crc & 1) ^ tmp0) << 1) & 2;
			crc = (((crc << 1) & 12) | tmp1 | tmp0) & 0xFF;
		}
	}
	return crc;
}

/**
 * Decode message - convert array of bytes to structure
 * @param[in] instance driver instance
 * @param[in] receivedMessage buffer with message from TX_FIFO
 * @param[in] message pointer to allocated struct to be filled with contents of message
 * @return 0 if OK
 * @return EINVAL if received message has errors (invalid length, CRC errors etc.)
 */
static uint32_t CSMI_DecodeMessage(CSMI_Instance *instance, uint8_t *receivedMessage, uint8_t messageLen, CSMI_Message *message) {
	uint8_t i;
	uint8_t remainingLength = 0;
	uint8_t lengthArbitrationField = 0;
	uint8_t lengthHeaderField = 0;
	uint8_t offset = 0;

	/**
	 *	Arbitration Field: 2 or 7 bytes
	 *	BYTE  0:	Arbitration Type, Arbitration Extension, Arbitration Priority
	 *	BYTE  1:	Source Logical Address / Enumeration Address [7:0]
	 *	BYTES 2-6:	NA / Source Enumeration Address [47:8]
	 */
	message->arbitrationType = CSMI_GetMsgField(receivedMessage, offset, ARBITRATION_TYPE);
	switch (message->arbitrationType) {
	case CSMI_AT_LONG:
		message->sourceAddress = CSMI_GetField6B(receivedMessage, CSMI_GetMsgFieldOffset(SOURCE_ADDRESS));
		lengthArbitrationField = CSMI_MESSAGE_ARBITRATION_LENGTH_LONG;
		break;
	case CSMI_AT_SHORT:
		message->sourceAddress = CSMI_GetField1B(receivedMessage, CSMI_GetMsgFieldOffset(SOURCE_ADDRESS));
		lengthArbitrationField = CSMI_MESSAGE_ARBITRATION_LENGTH_SHORT;
		break;
	default:
		SLIMBUS_CORE_LIMIT_ERR("arbitration type is invalid: %d\n", message->arbitrationType);
		return EINVAL;
	}
	message->arbitrationPriority = CSMI_GetMsgField(receivedMessage, offset, ARBITRATION_PRIORITY);

	/*
	 *	Header Field : 3, 4 or 9 bytes
	 *	BYTE  0:	Message Type, Remaining Length
	 *	BYTE  1:	Message Code
	 *	BYTE  2:	Destination Type, Primary Integrity
	 *	BYTE  3:	Destination Logical Address / Enumeration Address [7:0]
	 *	BYTES 4-8:	NA / Destination Enumeration Address [47:8]
	 */
	offset = lengthArbitrationField;

	message->messageType = CSMI_GetMsgField(receivedMessage, offset, MESSAGE_TYPE);
	remainingLength = CSMI_GetMsgField(receivedMessage, offset, REMAINING_LENGTH);
	message->messageCode = CSMI_GetMsgField(receivedMessage, offset, MESSAGE_CODE);
	message->destinationType = CSMI_GetMsgField(receivedMessage, offset, MESSAGE_DESTINATION_TYPE);

	switch (message->destinationType) {
	case CSMI_DT_BROADCAST:
		lengthHeaderField = CSMI_MESSAGE_HEADER_LENGTH_BROADCAST;
		message->destinationAddress = 0x0;
		break;

	case CSMI_DT_LOGICAL_ADDRESS:
		lengthHeaderField = CSMI_MESSAGE_HEADER_LENGTH_SHORT;
		message->destinationAddress = CSMI_GetField1B(receivedMessage, offset + CSMI_GetMsgFieldOffset(DESTINATION_ADDRESS));
		break;

	case CSMI_DT_ENUMERATION_ADDRESS:
		lengthHeaderField = CSMI_MESSAGE_HEADER_LENGTH_LONG;
		message->destinationAddress = CSMI_GetField6B(receivedMessage, offset + CSMI_GetMsgFieldOffset(DESTINATION_ADDRESS));
		break;

	default:
		SLIMBUS_CORE_LIMIT_ERR("destination type is invalid: %d\n", message->destinationType);
		return EINVAL;
	}

	/* Payload length */
	offset = lengthArbitrationField + lengthHeaderField;

	if (remainingLength > (CSMI_MESSAGE_PAYLOAD_MAX_LENGTH + lengthHeaderField)) {
		SLIMBUS_CORE_LIMIT_ERR("remaining length is invalid: %d, %d\n", remainingLength, (CSMI_MESSAGE_PAYLOAD_MAX_LENGTH + lengthHeaderField));
		return EINVAL;
	}

	message->payloadLength = remainingLength - lengthHeaderField;

	/*
	 * Message Integrity and Response Field
	 * BYTE 0:		Message Integrity, Message Response
	 */
	message->response = CSMI_GetMsgField(receivedMessage, (offset + message->payloadLength), RESPONSE_CODE);
	if (CSMI_MR_POSITIVE_ACK != message->response) {
		SLIMBUS_CORE_LIMIT_ERR("SLIMbus received message not PACK:%#x ! \n", message->response);//fixme: by lyq
	}

	/* Payload data */
	for (i = 0; i < message->payloadLength; i++)
		message->payload[i] = CSMI_GetField1B(receivedMessage, offset + i);

	return 0;
}

/**
 * Encode message - convert structure to array of bytes
 * @param[in] instance driver instance
 * @param[out] memoryToFill allocated memory buffer for TX_FIFO, must be filled with zeroes
 * @param[in] message struct with message
 * @return 0 if message has errors
 * @return size of generated message [bytes] if OK
 */
static uint32_t CSMI_EncodeMessage(CSMI_Instance *instance, uint8_t *memoryToFill, CSMI_Message *message) {
	uint8_t i;
	uint8_t remainingLength = 0;
	uint8_t primaryIntegrity = 0;
	uint8_t messageIntegrity = 0;
	uint8_t offset = 0;
	uint8_t lengthArbitrationField = 0;
	uint8_t lengthHeaderField = 0;
	uint8_t primaryIntegrityBytes = 0;

	/* Arbitration Field: 2 or 7 bytes */
	CSMI_SetMsgField(memoryToFill, message->arbitrationType, offset, ARBITRATION_TYPE);

	switch (message->arbitrationType) {
	case CSMI_AT_LONG:
		CSMI_SetField6B(memoryToFill, message->sourceAddress, CSMI_GetMsgFieldOffset(SOURCE_ADDRESS));
		lengthArbitrationField = CSMI_MESSAGE_ARBITRATION_LENGTH_LONG;
		break;
	case CSMI_AT_SHORT:
		CSMI_SetField1B(memoryToFill, message->sourceAddress, CSMI_GetMsgFieldOffset(SOURCE_ADDRESS));
		lengthArbitrationField = CSMI_MESSAGE_ARBITRATION_LENGTH_SHORT;
		break;
	default:
		SLIMBUS_CORE_LIMIT_ERR("arbitration type is invalid: %d\n", message->arbitrationType);
		return 0;
	}
	CSMI_SetMsgField(memoryToFill, message->arbitrationPriority, offset, ARBITRATION_PRIORITY);
	CSMI_SetMsgField(memoryToFill, 0, offset, ARBITRATION_EXTENSION);

	/* Header Field: 3, 4 or 9 bytes */
	offset = lengthArbitrationField;

	CSMI_SetMsgField(memoryToFill, message->messageType, offset, MESSAGE_TYPE);
	CSMI_SetMsgField(memoryToFill, message->messageCode, offset, MESSAGE_CODE);
	CSMI_SetMsgField(memoryToFill, message->destinationType, offset, MESSAGE_DESTINATION_TYPE);

	switch (message->destinationType) {
	case CSMI_DT_BROADCAST:
		lengthHeaderField = CSMI_MESSAGE_HEADER_LENGTH_BROADCAST;
		break;

	case CSMI_DT_LOGICAL_ADDRESS:
		lengthHeaderField = CSMI_MESSAGE_HEADER_LENGTH_SHORT;
		CSMI_SetField1B(memoryToFill, message->destinationAddress, offset + CSMI_GetMsgFieldOffset(DESTINATION_ADDRESS));
		break;

	case CSMI_DT_ENUMERATION_ADDRESS:
		lengthHeaderField = CSMI_MESSAGE_HEADER_LENGTH_LONG;
		CSMI_SetField6B(memoryToFill, message->destinationAddress, offset + CSMI_GetMsgFieldOffset(DESTINATION_ADDRESS));
		break;

	default:
		SLIMBUS_CORE_LIMIT_ERR("destination type is invalid: %d\n", message->destinationType);
		return 0;
	}

	remainingLength = message->payloadLength + lengthHeaderField;
	CSMI_SetMsgField(memoryToFill, remainingLength, offset, REMAINING_LENGTH);

	/* Primary Integrity */
	if (instance->disableHardwareCrcCalculation) {
		primaryIntegrityBytes = offset + CSMI_GetMsgFieldOffset(DESTINATION_ADDRESS);
		primaryIntegrity = CSMI_CrcPrimaryIntegrity(memoryToFill, 0, primaryIntegrityBytes, 0);
		CSMI_SetMsgField(memoryToFill, primaryIntegrity, offset, PRIMARY_INTEGRITY);
	}

	/* Payload data */
	offset = lengthArbitrationField + lengthHeaderField;
	for (i = 0; i < message->payloadLength; i++)
		CSMI_SetField1B(memoryToFill, message->payload[i], offset + i);

	/* Message integrity */
	if (instance->disableHardwareCrcCalculation) {
		messageIntegrity = CSMI_CrcMessageIntegrity(memoryToFill, primaryIntegrityBytes -1, remainingLength - 3 + 1, primaryIntegrity);
		CSMI_SetMsgField(memoryToFill, messageIntegrity, (offset + message->payloadLength), MESSAGE_INTEGRITY);
	}
	return lengthArbitrationField + lengthHeaderField + message->payloadLength + 1;/* [false alarm]:fortify Îó¾¯  */

}

/**
 * Transmit data to TX_FIFO
 * @param[in] instance driver instance
 * @param[in] txFifoData pointer to the data buffer
 * @param[in] txFifoDataSize size of data to transmit [bytes]
 * @param[in] wait wait until message is sent (TX_ERR interrupt must be enabled!)
 * @return 0 if OK
 * @return EIO if not OK
 */
static uint32_t CSMI_FifoTransmit(CSMI_Instance *instance, uint8_t *txFifoData, uint8_t txFifoDataSize, _Bool wait) {
	uint8_t i;
	uint8_t regsToWrite = 0;
	uint32_t *txFifoData32b = (uint32_t *) txFifoData;
	uint32_t reg;
	uint32_t timeout = 0;
	uint32_t ret = 0;

	do { //If TX_FIFO is full, wait until it's not
		reg = CSMI_ReadReg(COMMAND_STATUS.STATE);
		if (++timeout == 0) {
			SLIMBUS_CORE_LIMIT_ERR("SLIMbus send message wait TX_FULL timeout!\n");
			return EIO;
		}
	} while ((COMMAND_STATUS__STATE__TX_FULL__READ(reg)) == 1);

	if (slimbus_int_need_clear_get()) {
		CSMI_Set_INT_EN_Enabled(instance, 0);
	}

	timeout = 0;
	instance->sendingFailed = 0;
	instance->sendingFinished = 0;
	regsToWrite = (txFifoDataSize >> 2) + ((txFifoDataSize & 0x3) != 0); //regsToWrite = txFifoDataSize / 4 + 1 if txFifoDataSize % 4 > 0

	for (i = 0; i < regsToWrite; i++, txFifoData32b++) {
		CSMI_WriteReg(MESSAGE_FIFOS.MC_FIFO[i], *txFifoData32b);
	}

	reg = CSMI_ReadReg(COMMAND_STATUS.COMMAND);
	COMMAND_STATUS__COMMAND__TX_PUSH__SET(reg);
	CSMI_WriteReg(COMMAND_STATUS.COMMAND, reg);

	do { //If TX_PUSH command is still in progress, wait until it's finished
		reg = CSMI_ReadReg(COMMAND_STATUS.STATE);
		if (++timeout == 0) {
			SLIMBUS_CORE_LIMIT_ERR("SLIMbus send message wait TX_PUSH timeout!\n");
			ret = EIO;
			goto exit;
		}
	} while (COMMAND_STATUS__STATE__TX_PUSH__READ(reg));

	if (wait) { //If wait == 1 then function waits for confirmation of message reception
		timeout = 0;
		for (;;) {
			reg = CSMI_ReadReg(INTERRUPTS.INT);    //If message was transmitted in an interrupt (e.g. from callback), sending* variables won't be set by another interrupt. In that case polling is used.
			if (INTERRUPTS__INT__TX_ERR__READ(reg)) {
				if (slimbus_int_need_clear_get()) {
					reg = 0;
					INTERRUPTS__INT__TX_ERR__SET(reg);
					CSMI_WriteReg(INTERRUPTS.INT, reg);
				}
				SLIMBUS_CORE_LIMIT_ERR("SLIMbus send message TX_ERR happened!\n");
				ret = EIO;
				goto exit;
			}

			if (INTERRUPTS__INT__TX_INT__READ(reg)) {
				if (slimbus_int_need_clear_get()) {
					reg = 0;
					INTERRUPTS__INT__TX_INT__SET(reg);
					CSMI_WriteReg(INTERRUPTS.INT, reg);
				}
				goto exit;
			}

			if (instance->sendingFailed) {	  //CSMI_Irq will read and clear interrupt flag before it will be accessed here by polling. These variables are set by interrupt handling function.
				SLIMBUS_CORE_LIMIT_ERR("SLIMbus send message failed!\n");
				ret = EIO;
				goto exit;
			}

			if (instance->sendingFinished)
				goto exit;

			if (++timeout == 0) {
				SLIMBUS_CORE_LIMIT_ERR("SLIMbus send message timeout!\n");
				ret = EIO;
				goto exit;
			}
		}
	}

exit:
	if (slimbus_int_need_clear_get()) {
		CSMI_Set_INT_EN_Enabled(instance, 1);
	}

	return ret;
}

/**
 * Receive data from RX_FIFO
 * @param[in] instance driver instance
 * @param[out] rxFifoData pointer to memory to be filled with received data
 * @param[in] rxFifoMaxSize max size of data buffer
 * @return size of received data if OK
 * @return 0 if message overflowed or received message is bigger than available data buffer
 */
static uint32_t CSMI_FifoReceive(CSMI_Instance *instance, uint8_t *rxFifoData, uint8_t rxFifoMaxSize) {
	uint32_t rxFifoFlag = 0;
	uint8_t rxFifoMsgSize = 0;
	uint8_t i;
	uint8_t regsToRead = 0;
	uint8_t result = 0;
	uint32_t *rxFifoData32b = (uint32_t *) rxFifoData;
	uint32_t reg;
	rxFifoFlag = CSMI_ReadReg(MESSAGE_FIFOS.MC_FIFO[CSMI_RX_FIFO_FLAG_OFFSET]);

	if (rxFifoFlag & (1 << CSMI_RX_FIFO_FLAG_RX_OVERFLOW)) { //Message Overflow
		result = 0;
		SLIMBUS_CORE_LIMIT_ERR("SLIMbus RX_FIFO Message Overflow! \n");
		goto rxFifoEnd;
	}

	rxFifoMsgSize = rxFifoFlag & CSMI_RX_FIFO_FLAG_RX_MSG_MASK;
	if (rxFifoMsgSize > rxFifoMaxSize) {
		result = 0;
		goto rxFifoEnd;
	}
	regsToRead = (rxFifoMsgSize >> 2) + ((rxFifoMsgSize & 0x3) != 0); //regsToRead = rxFifoMsgSize / 4 + 1 if rxFifoSize % 4 > 0

	for (i = 0; i < regsToRead; i++, rxFifoData32b++) {
		*rxFifoData32b = CSMI_ReadReg(MESSAGE_FIFOS.MC_FIFO[i]);
	}
	result = rxFifoMsgSize;

rxFifoEnd:
	reg = CSMI_ReadReg(COMMAND_STATUS.COMMAND);
	COMMAND_STATUS__COMMAND__RX_PULL__SET(reg);
	CSMI_WriteReg(COMMAND_STATUS.COMMAND, reg);
	return result;
}

/**
 * Transmit SLIMBus message
 * @param[in] instance driver instance
 * @param[in] message pointer to message struct
 * @return 0 if OK
 * @return EINVAL if message structure is invalid
 * @return EIO if an error occurred while sending data to TX_FIFO
 */
static uint32_t CSMI_TransmitMessage(CSMI_Instance *instance, CSMI_Message *message) {
	uint8_t txFifoData[CSMI_TX_FIFO_MSG_MAX_SIZE];
	uint8_t fifoSize = 0;
	uint32_t result = 0;
	unsigned long flag = 0;

	CSMI_ClearMemory((void*) txFifoData, CSMI_TX_FIFO_MSG_MAX_SIZE);

	if (instance->basicCallbacks.onMessageSending != NULL)
		instance->basicCallbacks.onMessageSending((void *) instance, message);

	fifoSize = CSMI_EncodeMessage(instance, txFifoData, message);
	if (fifoSize == 0) {
		SLIMBUS_CORE_LIMIT_ERR("encode message fail\n");
		return EINVAL;
	}

	if (instance->basicCallbacks.onRawMessageSending != NULL)
		instance->basicCallbacks.onRawMessageSending((void *) instance, (void *) txFifoData, fifoSize);

	spin_lock_irqsave(&slimbus_spinlock, flag);
	result = CSMI_FifoTransmit(instance, txFifoData, fifoSize, 1);
	spin_unlock_irqrestore(&slimbus_spinlock, flag);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("fifo transmit fail\n");
		return EIO;
	}

	return 0;
}



/**
 * Assign logical address to a discovered device
 * @param[in] instance driver instance
 * @param[in] message received REPORT_PRESENT message
 * @return 0 if OK
 * @return EIO if there was an IO error
 * @return EINVAL if AssignLogicalAddressHandler is invalid
 */
static inline uint32_t CSMI_AssignLogicalAddress(CSMI_Instance *instance, CSMI_Message *message) {
	uint8_t logicalAddress = 0x0;
	if (instance->basicCallbacks.onAssignLogicalAddress == NULL) {
		SLIMBUS_CORE_LIMIT_ERR("instance->basicCallbacks.onAssignLogicalAddress is NULL\n");
		return EINVAL;
	}

	logicalAddress = instance->basicCallbacks.onAssignLogicalAddress(message->sourceAddress, message->payload[0]);
	if (logicalAddress > 0xEF) { //Reserved value was used
		SLIMBUS_CORE_LIMIT_ERR("logical address is invalid: %x\n", logicalAddress);
		return EINVAL;
	}
	return CSMI_MsgAssignLogicalAddress((void *) instance, message->sourceAddress, logicalAddress);
}

/**
 * Check Received Information Element for errors and possible callbacks
 * Also clears received information elements.
 * @param[in] instance driver instance
 * @param[in] message received REPORT_INFORMATION message
 * @return 0 if OK
 * @return EINVAL if invalid message, or invalid device class was received
 */
static inline uint32_t CSMI_CheckInformationElement(CSMI_Instance *instance, CSMI_Message *message) {
	uint16_t elementCode;
	uint16_t ecByteAddress;
	bool ecAccessByteBased; 		// 1 - Byte-based Access, 0 - Elemental Access
	CSMI_SliceSize ecSliceSize;    // For Byte-based Access
	uint8_t ecBitNumber;			// For Elemental Access  //fixme: by lyq
	CSMI_DeviceClass deviceClass;
	CSMI_InformationElements ie;
	uint8_t i;
	uint8_t* informationSlice;
	uint8_t informationSliceLen;

	if (message->messageCode != CSMI_MESSAGE_CODE_REPORT_INFORMATION) {
		SLIMBUS_CORE_LIMIT_ERR("message code is invalid: %d\n", message->messageCode);
		return EINVAL;
	}

	/*
	 * Payload:
	 * 0	EC		 [7:0]
	 * 1	EC		[15:8]
	 * 2	IS		 [7:0]
	 * N+1	IS [8N-1:8N-8]
	 */
	elementCode = message->payload[0] | (message->payload[1] << 8);
	ecAccessByteBased = CSMI_GetMsgPayloadField(ELEMENT_CODE_ACCESS_TYPE, elementCode);
	ecByteAddress = CSMI_GetMsgPayloadField(ELEMENT_CODE_BYTE_ADDRESS, elementCode);
	if (ecAccessByteBased) {
		ecSliceSize = CSMI_GetMsgPayloadField(ELEMENT_CODE_SLICE_SIZE, elementCode);
		if (CSMI_SliceSizeToBytes(ecSliceSize) != (message->payloadLength - 2)) {
			SLIMBUS_CORE_LIMIT_ERR("payload don't match witch slice size: %d, %d\n", CSMI_SliceSizeToBytes(ecSliceSize), (message->payloadLength - 2));
			return EINVAL; //Received Slice Size is different than payload
		}
	} else {
		ecBitNumber = CSMI_GetMsgPayloadField(ELEMENT_CODE_BIT_NUMBER, elementCode);
	}

	informationSlice = &(message->payload[CSMI_ELEMENT_CODE_LENGTH]);
	informationSliceLen = message->payloadLength - CSMI_ELEMENT_CODE_LENGTH;

	if (informationSliceLen == 0) {
		SLIMBUS_CORE_LIMIT_ERR("information slice len is zero\n");
		return EINVAL;
	}

	CSMI_ClearMemory((void *) &ie, sizeof(CSMI_InformationElements));

	if (ecByteAddress >= CSMI_IE_CLASS_SPECIFIC_OFFSET) {
		deviceClass = instance->basicCallbacks.onDeviceClassRequest(message->sourceAddress);
		switch (deviceClass) {
		case CSMI_DC_MANAGER:
			if (ecAccessByteBased) {
				for (i = 0; i < informationSliceLen; i++) {
					CSMI_GetIeByteAccess(ie.managerActiveManager, MANAGER_ACTIVE_MANAGER, ecByteAddress + i, informationSlice[i]);
					CSMI_ClearIeByteAccess(MANAGER_ACTIVE_MANAGER, ecByteAddress + i, informationSlice[i]);
				}
			} else {
				CSMI_GetIeElementalAccess(ie.managerActiveManager, MANAGER_ACTIVE_MANAGER, ecByteAddress, ecBitNumber, informationSlice[0]);
				CSMI_ClearIeElementalAccess(MANAGER_ACTIVE_MANAGER, ecByteAddress, ecBitNumber, informationSlice[0]);
			}
			break;

		case CSMI_DC_FRAMER:
			if (ecAccessByteBased) {
				for (i = 0; i < informationSliceLen; i++) {
					CSMI_GetIeByteAccess(ie.framerGcTxCol, FRAMER_GC_TX_COL, ecByteAddress + i, informationSlice[i]);
					CSMI_ClearIeByteAccess(FRAMER_GC_TX_COL, ecByteAddress + i, informationSlice[i]);

					CSMI_GetIeByteAccess(ie.framerFiTxCol, FRAMER_FI_TX_COL, ecByteAddress + i, informationSlice[i]);
					CSMI_ClearIeByteAccess(FRAMER_FI_TX_COL, ecByteAddress + i, informationSlice[i]);

					CSMI_GetIeByteAccess(ie.framerFsTxCol, FRAMER_FS_TX_COL, ecByteAddress + i, informationSlice[i]);
					CSMI_ClearIeByteAccess(FRAMER_FS_TX_COL, ecByteAddress + i, informationSlice[i]);

					CSMI_GetIeByteAccess(ie.framerActiveFramer, FRAMER_ACTIVE_FRAMER, ecByteAddress + i, informationSlice[i]);
					CSMI_ClearIeByteAccess(FRAMER_ACTIVE_FRAMER, ecByteAddress + i, informationSlice[i]);

					CSMI_GetIeByteAccess(ie.framerQuality, FRAMER_QUALITY, ecByteAddress + i, informationSlice[i]);
					CSMI_ClearIeByteAccess(FRAMER_QUALITY, ecByteAddress + i, informationSlice[i]);
				}
			} else {
				CSMI_GetIeElementalAccess(ie.framerGcTxCol, FRAMER_GC_TX_COL, ecByteAddress, ecBitNumber, informationSlice[0]);
				CSMI_ClearIeElementalAccess(FRAMER_GC_TX_COL, ecByteAddress, ecBitNumber, informationSlice[0]);

				CSMI_GetIeElementalAccess(ie.framerFiTxCol, FRAMER_FI_TX_COL, ecByteAddress, ecBitNumber, informationSlice[0]);
				CSMI_ClearIeElementalAccess(FRAMER_FI_TX_COL, ecByteAddress, ecBitNumber, informationSlice[0]);

				CSMI_GetIeElementalAccess(ie.framerFsTxCol, FRAMER_FS_TX_COL, ecByteAddress, ecBitNumber, informationSlice[0]);
				CSMI_ClearIeElementalAccess(FRAMER_FS_TX_COL, ecByteAddress, ecBitNumber, informationSlice[0]);

				CSMI_GetIeElementalAccess(ie.framerActiveFramer, FRAMER_ACTIVE_FRAMER, ecByteAddress, ecBitNumber, informationSlice[0]);
				CSMI_ClearIeElementalAccess(FRAMER_ACTIVE_FRAMER, ecByteAddress, ecBitNumber, informationSlice[0]);

				CSMI_GetIeElementalAccess(ie.framerQuality, FRAMER_QUALITY, ecByteAddress, ecBitNumber, informationSlice[0]);
				CSMI_ClearIeElementalAccess(FRAMER_QUALITY, ecByteAddress, ecBitNumber, informationSlice[0]);
			}
			break;

		case CSMI_DC_INTERFACE:
			if (ecAccessByteBased) {
				for (i = 0; i < informationSliceLen; i++) {
					CSMI_GetIeByteAccess(ie.interfaceDataSlotOverlap, INTERFACE_DATA_SLOT_OVERLAP, ecByteAddress + i, informationSlice[i]);
					CSMI_ClearIeByteAccess(INTERFACE_DATA_SLOT_OVERLAP, ecByteAddress + i, informationSlice[i]);

					CSMI_GetIeByteAccess(ie.interfaceLostMs, INTERFACE_LOST_MS, ecByteAddress + i, informationSlice[i]);
					CSMI_ClearIeByteAccess(INTERFACE_LOST_MS, ecByteAddress + i, informationSlice[i]);

					CSMI_GetIeByteAccess(ie.interfaceLostSfs, INTERFACE_LOST_SFS, ecByteAddress + i, informationSlice[i]);
					CSMI_ClearIeByteAccess(INTERFACE_LOST_SFS, ecByteAddress + i, informationSlice[i]);

					CSMI_GetIeByteAccess(ie.interfaceLostFs, INTERFACE_LOST_FS, ecByteAddress + i, informationSlice[i]);
					CSMI_ClearIeByteAccess(INTERFACE_LOST_FS, ecByteAddress + i, informationSlice[i]);

					CSMI_GetIeByteAccess(ie.interfaceMcTxCol, INTERFACE_MC_TX_COL, ecByteAddress + i, informationSlice[i]);
					CSMI_ClearIeByteAccess(INTERFACE_MC_TX_COL, ecByteAddress + i, informationSlice[i]);
				}
			} else {
				CSMI_GetIeElementalAccess(ie.interfaceDataSlotOverlap, INTERFACE_DATA_SLOT_OVERLAP, ecByteAddress, ecBitNumber, informationSlice[0]);
				CSMI_ClearIeElementalAccess(INTERFACE_DATA_SLOT_OVERLAP, ecByteAddress, ecBitNumber, informationSlice[0]);

				CSMI_GetIeElementalAccess(ie.interfaceLostMs, INTERFACE_LOST_MS, ecByteAddress, ecBitNumber, informationSlice[0]);
				CSMI_ClearIeElementalAccess(INTERFACE_LOST_MS, ecByteAddress, ecBitNumber, informationSlice[0]);

				CSMI_GetIeElementalAccess(ie.interfaceLostSfs, INTERFACE_LOST_SFS, ecByteAddress, ecBitNumber, informationSlice[0]);
				CSMI_ClearIeElementalAccess(INTERFACE_LOST_SFS, ecByteAddress, ecBitNumber, informationSlice[0]);

				CSMI_GetIeElementalAccess(ie.interfaceLostFs, INTERFACE_LOST_FS, ecByteAddress, ecBitNumber, informationSlice[0]);
				CSMI_ClearIeElementalAccess(INTERFACE_LOST_FS, ecByteAddress, ecBitNumber, informationSlice[0]);

				CSMI_GetIeElementalAccess(ie.interfaceMcTxCol, INTERFACE_MC_TX_COL, ecByteAddress, ecBitNumber, informationSlice[0]);
				CSMI_ClearIeElementalAccess(INTERFACE_MC_TX_COL, ecByteAddress, ecBitNumber, informationSlice[0]);
			}
			break;

		case CSMI_DC_GENERIC:
			break;

		default:
			SLIMBUS_CORE_LIMIT_ERR("device class is invalide: %d\n", deviceClass);
			return EINVAL;
		}
	} else {
		if (ecAccessByteBased) {
			for (i = 0; i < informationSliceLen; i++) { //Information Slice is bytes 2 and up of the Payload, loop through all received bytes
				CSMI_GetIeByteAccess(ie.coreExError, CORE_EX_ERROR, ecByteAddress + i, informationSlice[i]);
				CSMI_ClearIeByteAccess(CORE_EX_ERROR, ecByteAddress + i, informationSlice[i]);

				CSMI_GetIeByteAccess(ie.coreReconfigObjection, CORE_RECONFIG_OBJECTION, ecByteAddress + i, informationSlice[i]);
				CSMI_ClearIeByteAccess(CORE_RECONFIG_OBJECTION, ecByteAddress + i, informationSlice[i]);

				CSMI_GetIeByteAccess(ie.coreDataTxCol, CORE_DATA_TX_COL, ecByteAddress + i, informationSlice[i]);
				CSMI_ClearIeByteAccess(CORE_DATA_TX_COL, ecByteAddress + i, informationSlice[i]);

				CSMI_GetIeByteAccess(ie.coreUnsprtdMsg, CORE_UNSPRTD_MSG, ecByteAddress + i, informationSlice[i]);
				CSMI_ClearIeByteAccess(CORE_UNSPRTD_MSG, ecByteAddress + i, informationSlice[i]);

				CSMI_ClearIeByteAccess(CORE_DEVICE_CLASS, ecByteAddress + i, informationSlice[i]);
				CSMI_ClearIeByteAccess(CORE_DEVICE_CLASS_VERSION, ecByteAddress + i, informationSlice[i]);
			}
		} else {	//Information Slice is 1 Information Element
			CSMI_GetIeElementalAccess(ie.coreExError, CORE_EX_ERROR, ecByteAddress, ecBitNumber, informationSlice[0]);
			CSMI_ClearIeElementalAccess(CORE_EX_ERROR, ecByteAddress, ecBitNumber, informationSlice[0]);

			CSMI_GetIeElementalAccess(ie.coreReconfigObjection, CORE_RECONFIG_OBJECTION, ecByteAddress, ecBitNumber, informationSlice[0]);
			CSMI_ClearIeElementalAccess(CORE_RECONFIG_OBJECTION, ecByteAddress, ecBitNumber, informationSlice[0]);

			CSMI_GetIeElementalAccess(ie.coreDataTxCol, CORE_DATA_TX_COL, ecByteAddress, ecBitNumber, informationSlice[0]);
			CSMI_ClearIeElementalAccess(CORE_DATA_TX_COL, ecByteAddress, ecBitNumber, informationSlice[0]);

			CSMI_GetIeElementalAccess(ie.coreUnsprtdMsg, CORE_UNSPRTD_MSG, ecByteAddress, ecBitNumber, informationSlice[0]);
			CSMI_ClearIeElementalAccess(CORE_UNSPRTD_MSG, ecByteAddress, ecBitNumber, informationSlice[0]);

			CSMI_ClearIeElementalAccess(CORE_DEVICE_CLASS, ecByteAddress, ecBitNumber, informationSlice[0]);
			CSMI_ClearIeElementalAccess(CORE_DEVICE_CLASS_VERSION, ecByteAddress, ecBitNumber, informationSlice[0]);
		}
	}

	if (instance->basicCallbacks.onInformationElementReported!= NULL)
		instance->basicCallbacks.onInformationElementReported((void *) instance, message->sourceAddress, &ie);

	//Clear received Information Element
	CSMI_MsgClearInformation((void *) instance, 0, message->sourceAddress, elementCode, informationSlice, informationSliceLen);

	return 0;
}

/**
 * Process received message.
 * Calls callbacks (if assigned)
 * Calls decoding and clear of reported information element
 * @param[in] instance driver instance
 * @param[in] message received message
 * @return 0 if OK
 * @return EIO if there was an IO error(s)
 * @return EINVAL if invalid message was received
 * @return ENOMEM if internal reply has been received, but previous one has not been acknowledged
 */
static inline uint32_t CSMI_ProcessReceivedMessage(CSMI_Instance *instance, CSMI_Message *message) {

	switch (message->messageCode) {
	case CSMI_MESSAGE_CODE_REPORT_PRESENT:		   //Payload: 0 - Device Class code, 1 - Device Class Version
		if (instance->messageCallbacks.onMsgReportPresent != NULL)
			instance->messageCallbacks.onMsgReportPresent((void *) instance, message->sourceAddress, message->payload[0], message->payload[1]);

		if (instance->enumerateDevices)
			return CSMI_AssignLogicalAddress(instance, message);
		break;

	case CSMI_MESSAGE_CODE_REPORT_ABSENT:		   //Payload: None
		if (instance->messageCallbacks.onMsgReportAbsent != NULL)
			instance->messageCallbacks.onMsgReportAbsent((void *) instance, message->sourceAddress);
		break;

	case CSMI_MESSAGE_CODE_REPLY_INFORMATION:	   //Payload: 0 - Transaction ID, 1 => 16 - Information Slice
		if (instance->messageCallbacks.onMsgReplyInformation != NULL)
			instance->messageCallbacks.onMsgReplyInformation((void *) instance, message->sourceAddress, message->payload[0], &(message->payload[CSMI_TRANSACTION_ID_LENGTH]), message->payloadLength - CSMI_TRANSACTION_ID_LENGTH);
		break;

	case CSMI_MESSAGE_CODE_REPORT_INFORMATION:	   //Payload: 0 - Element Code [7:0], 1 - Element Code [15:8] 2 => 17 - Information Slice
		if (instance->messageCallbacks.onMsgReportInformation != NULL)
			instance->messageCallbacks.onMsgReportInformation((void *) instance, message->sourceAddress, message->payload[0] | (message->payload[1] << 8), &(message->payload[CSMI_ELEMENT_CODE_LENGTH]), message->payloadLength - CSMI_ELEMENT_CODE_LENGTH);
		CSMI_CheckInformationElement(instance, message);
		break;

	case CSMI_MESSAGE_CODE_REPLY_VALUE: 		   //Payload: 0 - Transaction ID, 1 => 16 - Value Slice
		if (instance->messageCallbacks.onMsgReplyValue != NULL)
			instance->messageCallbacks.onMsgReplyValue((void *) instance, message->sourceAddress, message->payload[0], &(message->payload[CSMI_TRANSACTION_ID_LENGTH]), message->payloadLength - CSMI_TRANSACTION_ID_LENGTH);
		break;

	default:
		SLIMBUS_CORE_LIMIT_ERR("mesage code is invalid: %d\n", message->messageCode);
		return EINVAL;

	}
	return 0;
}

/**
 * Receive all SLIMbus messages from RX_FIFO
 * @param[in] instance driver instance
 * @return 0 if OK
 * @return EIO if there was an error(s)
 */
static inline uint8_t CSMI_ReceiveMessages(CSMI_Instance *instance) {
	uint8_t rxFifoData[CSMI_RX_FIFO_MSG_MAX_SIZE];
	uint8_t fifoSize = 0;
	uint32_t reg = 0;
	uint8_t errors = 0;
	CSMI_Message rxMsg;

	for (;;) {
		reg = CSMI_ReadReg(COMMAND_STATUS.STATE);
		if (COMMAND_STATUS__STATE__RX_PULL__READ(reg))
			continue;

		if (COMMAND_STATUS__STATE__RX_NOTEMPTY__READ(reg) == 0)
			return 0;

		fifoSize = CSMI_FifoReceive(instance, rxFifoData, CSMI_RX_FIFO_MSG_MAX_SIZE);
		if ((fifoSize > 0) && (fifoSize <= CSMI_MESSAGE_MAX_LENGTH)) {
			if (instance->basicCallbacks.onRawMessageReceived != NULL)
				instance->basicCallbacks.onRawMessageReceived((void *) instance, (void *) rxFifoData, fifoSize);

			errors += CSMI_DecodeMessage(instance, rxFifoData, fifoSize, &rxMsg);
			if (errors)
				SLIMBUS_CORE_LIMIT_ERR("decode message fail\n");

			if (instance->basicCallbacks.onMessageReceived != NULL)
				instance->basicCallbacks.onMessageReceived((void *) instance, &rxMsg);

			errors += (CSMI_ProcessReceivedMessage(instance, &rxMsg) != 0);
			if (errors)
				SLIMBUS_CORE_LIMIT_ERR("process message fail\n");
		}
	}
	return errors ? EIO : 0;													/* [false alarm]:fortify Îó¾¯  */
}


/**
 * Wait until previous configuration is set (CFG_STROBE bit is cleared)
 * @param[in] instance driver instance
 * @return 0 if OK
 * @return EIO if polling CFG_STROBE timeouted
 */
static uint32_t CSMI_CfgStrobeCheck(CSMI_Instance *instance) {
	uint32_t reg = 0;
    uint32_t timeout_count = 0;

	reg = CSMI_ReadReg(CONFIGURATION.CONFIG_MODE);
	/* If Manager component is disabled do not poll CFG_STROBE bit */
	if ((CONFIGURATION__CONFIG_MODE__ENABLE__READ(reg)) == 0)
		return 0;

	reg = CSMI_ReadReg(COMMAND_STATUS.COMMAND);
	while (COMMAND_STATUS__COMMAND__CFG_STROBE__READ(reg)) {
		msleep(1);
		reg = CSMI_ReadReg(COMMAND_STATUS.COMMAND);
		if (++timeout_count == 100) {
			SLIMBUS_CORE_LIMIT_ERR("cfg strobe check timeout\n");
			return EIO;
		}
	}

	return 0;
}

/**
 * Set CFG_STROBE bit to apply changes in CONFIG Registers
 * @param[in] instance driver instance
 * @param[in] force force CFG_STROBE regardless of the ENABLE bit
 */
static void CSMI_CfgStrobeSet(CSMI_Instance *instance, bool force) {
	uint32_t reg = 0;
	if (!force) {
		reg = CSMI_ReadReg(CONFIGURATION.CONFIG_MODE);
		if ((CONFIGURATION__CONFIG_MODE__ENABLE__READ(reg)) == 0)
			return;
	}

	reg = CSMI_ReadReg(COMMAND_STATUS.COMMAND);
	COMMAND_STATUS__COMMAND__CFG_STROBE__SET(reg);
	CSMI_WriteReg(COMMAND_STATUS.COMMAND, reg);
}

/*
 * API Functions
 */

static uint32_t CSMI_Probe(const CSMI_Config* config, uint16_t* requiredMemory) {

	uint32_t result = CSMI_ProbeSanity(config, requiredMemory);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	*requiredMemory = sizeof(CSMI_Instance);
	return 0;
}


static uint32_t CSMI_Init(void* pD, const CSMI_Config* config, CSMI_Callbacks* callbacks) {
	CSMI_Instance* instance;
	uint32_t reg;

	uint32_t result = CSMI_InitSanity(pD, config, callbacks);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	if (callbacks->onDeviceClassRequest == NULL) {
		SLIMBUS_CORE_LIMIT_ERR("device class request callback is NULL\n");
		return EINVAL;
	}

	if ((callbacks->onAssignLogicalAddress == NULL) && (config->enumerateDevices == 1)) {
		SLIMBUS_CORE_LIMIT_ERR("assign logical address callback is NULL\n");
		return EINVAL;
	}

	if (config->eaInterfaceId == config->eaGenericId) {
		SLIMBUS_CORE_LIMIT_ERR("config->eaInterfaceId == config->eaGenericId\n");
		return EINVAL;
	}

	if (config->eaInterfaceId == config->eaFramerId) {
		SLIMBUS_CORE_LIMIT_ERR("config->eaInterfaceId == config->eaFramerId\n");
		return EINVAL;
	}

	if (config->eaGenericId == config->eaFramerId) {
		SLIMBUS_CORE_LIMIT_ERR("config->eaGenericId == config->eaFramerId\n");
		return EINVAL;
	}

	instance = (CSMI_Instance*) pD;
	instance->registerBase = config->regBase;
	instance->registers = (CSMI_Registers*) config->regBase;

	/* Exit if Manager component is already enabled */
	reg = CSMI_ReadReg(CONFIGURATION.CONFIG_MODE);
	if (CONFIGURATION__CONFIG_MODE__ENABLE__READ(reg)) {
		SLIMBUS_CORE_LIMIT_ERR("operation now in progress\n");
		return EINPROGRESS;
	}

	instance->sendingFailed = 0;
	instance->sendingFinished = 0;

	/* CONFIG_MODE - Configuration Mode */
	reg = CSMI_ReadReg(CONFIGURATION.CONFIG_MODE);

	CONFIGURATION__CONFIG_MODE__SNIFFER_MODE__MODIFY(reg, config->snifferMode);
	CONFIGURATION__CONFIG_MODE__MANAGER_MODE__SET(reg);

	CONFIGURATION__CONFIG_MODE__FR_EN__MODIFY(reg, config->enableFramer);
	CONFIGURATION__CONFIG_MODE__DEV_EN__MODIFY(reg, config->enableDevice);

	CONFIGURATION__CONFIG_MODE__RETRY_LMT__MODIFY(reg, config->retryLimit);
	CONFIGURATION__CONFIG_MODE__REPORT_AT_EVENT__MODIFY(reg, config->reportAtEvent);

	instance->disableHardwareCrcCalculation = config->disableHardwareCrcCalculation;
	CONFIGURATION__CONFIG_MODE__CRC_CALC_DISABLE__MODIFY(reg, config->disableHardwareCrcCalculation);

	CONFIGURATION__CONFIG_MODE__LMTD_REPORT__MODIFY(reg, config->limitReports);
	CONFIGURATION__CONFIG_MODE__RECONF_TX_DIS__CLR(reg);

	CSMI_WriteReg(CONFIGURATION.CONFIG_MODE, reg);

	/* CONFIG_EA - Enumeration Address Part 1 */
	reg = CSMI_ReadReg(CONFIGURATION.CONFIG_EA);
	CONFIGURATION__CONFIG_EA__PRODUCT_ID__MODIFY(reg, config->eaProductId);
	CONFIGURATION__CONFIG_EA__INSTANCE_VAL__MODIFY(reg, config->eaInstanceValue);
	CSMI_WriteReg(CONFIGURATION.CONFIG_EA, reg);

	/* CONFIG_EA2 - Enumeration Address Part 2 */
	reg = CSMI_ReadReg(CONFIGURATION.CONFIG_EA2);
	CONFIGURATION__CONFIG_EA2__DEVICE_ID_1__MODIFY(reg, config->eaInterfaceId);
	CONFIGURATION__CONFIG_EA2__DEVICE_ID_2__MODIFY(reg, config->eaGenericId);
	CONFIGURATION__CONFIG_EA2__DEVICE_ID_3__MODIFY(reg, config->eaFramerId);
	CSMI_WriteReg(CONFIGURATION.CONFIG_EA2, reg);


	/* INT_EN  - Interrupts Enable */
	reg = CSMI_ReadReg(INTERRUPTS.INT_EN);
	INTERRUPTS__INT_EN__RX_INT_EN__SET(reg);		//Enable interrupt for receiving messages
	INTERRUPTS__INT_EN__TX_ERR_EN__SET(reg);		//Enable interrupt for sending messages error
	INTERRUPTS__INT_EN__TX_INT_EN__SET(reg);		//Enable interrupt for sending messages
	INTERRUPTS__INT_EN__SYNC_LOST_EN__SET(reg);		//Enable interrupt for sync lost

	CSMI_WriteReg(INTERRUPTS.INT_EN, reg);

	instance->enumerateDevices = config->enumerateDevices;

	CPS_BufferCopy((uint8_t*) &(instance->basicCallbacks), (uint8_t*) callbacks, sizeof(CSMI_Callbacks));
	CSMI_ClearMemory((void*) &(instance->messageCallbacks), sizeof(CSMI_MessageCallbacks));

	return 0;
}

static uint32_t CSMI_Isr(void* pD) {
	CSMI_Instance* instance;
	uint32_t reg, copy;
	bool dataPortInterrupt = false;
	uint8_t i, j;
	CSMI_DataPortInterrupt dataPortIrq;

	uint32_t result = CSMI_IsrSanity(pD);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	/* Check INT register */
	reg = CSMI_ReadReg(INTERRUPTS.INT);
	if (reg) { //Interrupt occurred in INT register
		if (instance->basicCallbacks.onManagerInterrupt != NULL) {
			CSMI_Interrupt interrupts;
			interrupts = reg;
			instance->basicCallbacks.onManagerInterrupt(pD, interrupts);
		}

		if (INTERRUPTS__INT__TX_INT__READ(reg))
			instance->sendingFinished = 1;
		if (INTERRUPTS__INT__TX_ERR__READ(reg))
			instance->sendingFailed = 1;
		if (INTERRUPTS__INT__RX_INT__READ(reg)) {
			slimbus_irq_state = 1;
			CSMI_ReceiveMessages(instance);
		}

		dataPortInterrupt = INTERRUPTS__INT__PORT_INT__READ(reg);

		/* Clear interrupts */
		CSMI_WriteReg(INTERRUPTS.INT, reg);
	}

	if (dataPortInterrupt != 0) {

		for (i = 0; i < 16; i++) {
			reg = CSMI_ReadReg(PORT_INTERRUPTS.P_INT[i]);

			if (reg == 0) //If all bits in the register are low, then there is no interrupt
				continue;

			if (instance->basicCallbacks.onDataPortInterrupt != NULL) { //There is callback assigned
				copy = reg;
				for (j = 0; j < 4; j++) {	//P_INT register has 4 the same 8 bit registers with interrupts
					dataPortIrq = 0;
					dataPortIrq |=	(PORT_INTERRUPTS__P_INT__P0_ACT_INT__READ(copy)) ? CSMI_DP_INT_ACT : 0;
					dataPortIrq |=	(PORT_INTERRUPTS__P_INT__P0_CON_INT__READ(copy)) ? CSMI_DP_INT_CON : 0;
					dataPortIrq |=	(PORT_INTERRUPTS__P_INT__P0_CHAN_INT__READ(copy)) ? CSMI_DP_INT_CHAN : 0;
					dataPortIrq |=	(PORT_INTERRUPTS__P_INT__P0_DMA_INT__READ(copy)) ? CSMI_DP_INT_DMA : 0;
					dataPortIrq |=	(PORT_INTERRUPTS__P_INT__P0_OVF_INT__READ(copy)) ? CSMI_DP_INT_OVF : 0;
					dataPortIrq |=	(PORT_INTERRUPTS__P_INT__P0_UND_INT__READ(copy)) ? CSMI_DP_INT_UND : 0;

					copy >>= 8;

					if (dataPortIrq != 0) {
						instance->basicCallbacks.onDataPortInterrupt(pD, (i * 4 + j), dataPortIrq);
					}
				}
			}
			CSMI_WriteReg(PORT_INTERRUPTS.P_INT[i], reg); // Clear contents of the port interrupt register
		}
   }

	return 0;
}


static uint32_t CSMI_Start(void* pD) {
	CSMI_Instance* instance;
	uint32_t reg;
	uint32_t timeout_count = 0;

	uint32_t result = CSMI_StartSanity(pD);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	/* Exit if Manager component is already enabled */
	reg = CSMI_ReadReg(CONFIGURATION.CONFIG_MODE);
	if (CONFIGURATION__CONFIG_MODE__ENABLE__READ(reg)) {
		SLIMBUS_CORE_LIMIT_ERR("operation now in progress\n");
		return EINPROGRESS;
	}

	/* Enable component */
	CONFIGURATION__CONFIG_MODE__ENABLE__SET(reg);
	CSMI_WriteReg(CONFIGURATION.CONFIG_MODE, reg);

	/* Enable all interrupts */
	reg = CSMI_ReadReg(INTERRUPTS.INT_EN);
	INTERRUPTS__INT_EN__INT_EN__SET(reg);
	CSMI_WriteReg(INTERRUPTS.INT_EN, reg);

	CSMI_CfgStrobeSet(instance, 1);

	/* Wait for synchronization with SLIMbus */
	reg = CSMI_ReadReg(COMMAND_STATUS.STATE);
	while ((COMMAND_STATUS__STATE__F_SYNC__READ(reg) == 0)
		|| (COMMAND_STATUS__STATE__SF_SYNC__READ(reg) == 0)
		|| (COMMAND_STATUS__STATE__M_SYNC__READ(reg) == 0)) {
        msleep(1);
		reg = CSMI_ReadReg(COMMAND_STATUS.STATE);
    	if (++timeout_count == 100) {
			SLIMBUS_CORE_LIMIT_ERR("SLIMbus start wait sync timeout!\n");
			return EIO;
		}
    }

	return 0;
}


static uint32_t CSMI_Stop(void* pD) {
	CSMI_Instance* instance;
	uint32_t reg;
	uint32_t result = CSMI_StopSanity(pD);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	if (CSMI_CfgStrobeCheck(instance)) {
		SLIMBUS_CORE_LIMIT_ERR("strobe check fail\n");
		return EIO;
	}

	/* Disable all interrupts */
	reg = CSMI_ReadReg(INTERRUPTS.INT_EN);
	INTERRUPTS__INT_EN__INT_EN__CLR(reg);
	CSMI_WriteReg(INTERRUPTS.INT_EN, reg);

	/* Disable component */
	reg = CSMI_ReadReg(CONFIGURATION.CONFIG_MODE);
	CONFIGURATION__CONFIG_MODE__ENABLE__CLR(reg);
	CSMI_WriteReg(CONFIGURATION.CONFIG_MODE, reg);

	CSMI_CfgStrobeSet(instance, 1);

	return 0;
}


static uint32_t CSMI_Destroy(void* pD) {
	uint32_t result = CSMI_DestroySanity(pD);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
	   return result;
	}

	return CSMI_Stop(pD);
}


static uint32_t CSMI_SetInterrupts(void* pD, uint8_t interruptMask) {
	CSMI_Instance* instance;
	uint32_t reg = 0;

	uint32_t result = CSMI_SetInterruptsSanity(pD, interruptMask);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	reg = interruptMask;

	/* Make sure that mandatory interrupts are enabled */
	INTERRUPTS__INT_EN__INT_EN__SET(reg);		//Enable interrupts
	INTERRUPTS__INT_EN__RX_INT_EN__SET(reg);	//Interrupt for receiving messages
	INTERRUPTS__INT_EN__TX_ERR_EN__SET(reg);	//Interrupt for sending messages error
	INTERRUPTS__INT_EN__TX_INT_EN__SET(reg);	//Interrupt for sending messages

	CSMI_WriteReg(INTERRUPTS.INT_EN, reg);

	return 0;
}


static uint32_t CSMI_GetInterrupts(void* pD, uint8_t* interruptMask) {
	CSMI_Instance* instance;
	uint32_t reg;

	uint32_t result = CSMI_GetInterruptsSanity(pD, interruptMask);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	reg = CSMI_ReadReg(INTERRUPTS.INT_EN);
	*interruptMask = reg;

	return 0;
}


static uint32_t CSMI_SetDataPortInterrupts(void* pD, uint8_t portNumber, uint8_t interruptMask)  {
	CSMI_Instance* instance;
	uint8_t portAddress;
	uint32_t reg;

	uint32_t result = CSMI_SetDataPortInterruptsSanity(pD, portNumber, interruptMask);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	portAddress = portNumber / 4;
	//There are 4 Port registers per 1 32 bit P_INT_EN register

	reg = CSMI_ReadReg(PORT_INTERRUPTS.P_INT_EN[portAddress]);

	switch (portNumber % 4) {
	case 0:
		PORT_INTERRUPTS__P_INT_EN__P0_ACT_INT_EN__MODIFY(reg, (interruptMask & CSMI_DP_INT_ACT) != 0 );
		PORT_INTERRUPTS__P_INT_EN__P0_CON_INT_EN__MODIFY(reg, (interruptMask & CSMI_DP_INT_CON) != 0 );
		PORT_INTERRUPTS__P_INT_EN__P0_CHAN_INT_EN__MODIFY(reg, (interruptMask & CSMI_DP_INT_CHAN) != 0 );
		PORT_INTERRUPTS__P_INT_EN__P0_DMA_INT_EN__MODIFY(reg, (interruptMask & CSMI_DP_INT_DMA) != 0 );
		PORT_INTERRUPTS__P_INT_EN__P0_OVF_INT_EN__MODIFY(reg, (interruptMask & CSMI_DP_INT_OVF) != 0 );
		PORT_INTERRUPTS__P_INT_EN__P0_UND_INT_EN__MODIFY(reg, (interruptMask & CSMI_DP_INT_UND) != 0 );
		break;
	case 1:
		PORT_INTERRUPTS__P_INT_EN__P1_ACT_INT_EN__MODIFY(reg, (interruptMask & CSMI_DP_INT_ACT) != 0 );
		PORT_INTERRUPTS__P_INT_EN__P1_CON_INT_EN__MODIFY(reg, (interruptMask & CSMI_DP_INT_CON) != 0 );
		PORT_INTERRUPTS__P_INT_EN__P1_CHAN_INT_EN__MODIFY(reg, (interruptMask & CSMI_DP_INT_CHAN) != 0 );
		PORT_INTERRUPTS__P_INT_EN__P1_DMA_INT_EN__MODIFY(reg, (interruptMask & CSMI_DP_INT_DMA) != 0 );
		PORT_INTERRUPTS__P_INT_EN__P1_OVF_INT_EN__MODIFY(reg, (interruptMask & CSMI_DP_INT_OVF) != 0 );
		PORT_INTERRUPTS__P_INT_EN__P1_UND_INT_EN__MODIFY(reg, (interruptMask & CSMI_DP_INT_UND) != 0 );
		break;
	case 2:
		PORT_INTERRUPTS__P_INT_EN__P2_ACT_INT_EN__MODIFY(reg, (interruptMask & CSMI_DP_INT_ACT) != 0 );
		PORT_INTERRUPTS__P_INT_EN__P2_CON_INT_EN__MODIFY(reg, (interruptMask & CSMI_DP_INT_CON) != 0 );
		PORT_INTERRUPTS__P_INT_EN__P2_CHAN_INT_EN__MODIFY(reg, (interruptMask & CSMI_DP_INT_CHAN) != 0 );
		PORT_INTERRUPTS__P_INT_EN__P2_DMA_INT_EN__MODIFY(reg, (interruptMask & CSMI_DP_INT_DMA) != 0 );
		PORT_INTERRUPTS__P_INT_EN__P2_OVF_INT_EN__MODIFY(reg, (interruptMask & CSMI_DP_INT_OVF) != 0 );
		PORT_INTERRUPTS__P_INT_EN__P2_UND_INT_EN__MODIFY(reg, (interruptMask & CSMI_DP_INT_UND) != 0 );
		break;
	case 3:
		PORT_INTERRUPTS__P_INT_EN__P3_ACT_INT_EN__MODIFY(reg, (interruptMask & CSMI_DP_INT_ACT) != 0 );
		PORT_INTERRUPTS__P_INT_EN__P3_CON_INT_EN__MODIFY(reg, (interruptMask & CSMI_DP_INT_CON) != 0 );
		PORT_INTERRUPTS__P_INT_EN__P3_CHAN_INT_EN__MODIFY(reg, (interruptMask & CSMI_DP_INT_CHAN) != 0 );
		PORT_INTERRUPTS__P_INT_EN__P3_DMA_INT_EN__MODIFY(reg, (interruptMask & CSMI_DP_INT_DMA) != 0 );
		PORT_INTERRUPTS__P_INT_EN__P3_OVF_INT_EN__MODIFY(reg, (interruptMask & CSMI_DP_INT_OVF) != 0 );
		PORT_INTERRUPTS__P_INT_EN__P3_UND_INT_EN__MODIFY(reg, (interruptMask & CSMI_DP_INT_UND) != 0 );
		break;
	default:
		break;
	}
	CSMI_WriteReg(PORT_INTERRUPTS.P_INT_EN[portAddress], reg);

	return 0;
}


static uint32_t CSMI_GetDataPortInterrupts(void* pD, uint8_t portNumber, uint8_t* interruptMask) {
	CSMI_Instance* instance;
	uint8_t portAddress;
	uint32_t reg;
	CSMI_DataPortInterrupt output = 0;

	uint32_t result = CSMI_GetDataPortInterruptsSanity(pD, portNumber, interruptMask);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	portAddress = portNumber / 4;
	//There are 4 Port registers per 1 32 bit P_INT_EN register
	reg = CSMI_ReadReg(PORT_INTERRUPTS.P_INT_EN[portAddress]);

	switch (portNumber % 4) {
	case 0:
		output |=  (PORT_INTERRUPTS__P_INT_EN__P0_ACT_INT_EN__READ(reg)) ? CSMI_DP_INT_ACT : 0;
		output |=  (PORT_INTERRUPTS__P_INT_EN__P0_CON_INT_EN__READ(reg)) ? CSMI_DP_INT_CON : 0;
		output |=  (PORT_INTERRUPTS__P_INT_EN__P0_CHAN_INT_EN__READ(reg)) ? CSMI_DP_INT_CHAN : 0;
		output |=  (PORT_INTERRUPTS__P_INT_EN__P0_DMA_INT_EN__READ(reg)) ? CSMI_DP_INT_DMA : 0;
		output |=  (PORT_INTERRUPTS__P_INT_EN__P0_OVF_INT_EN__READ(reg)) ? CSMI_DP_INT_OVF : 0;
		output |=  (PORT_INTERRUPTS__P_INT_EN__P0_UND_INT_EN__READ(reg)) ? CSMI_DP_INT_UND : 0;
		break;
	case 1:
		output |=  (PORT_INTERRUPTS__P_INT_EN__P1_ACT_INT_EN__READ(reg)) ? CSMI_DP_INT_ACT : 0;
		output |=  (PORT_INTERRUPTS__P_INT_EN__P1_CON_INT_EN__READ(reg)) ? CSMI_DP_INT_CON : 0;
		output |=  (PORT_INTERRUPTS__P_INT_EN__P1_CHAN_INT_EN__READ(reg)) ? CSMI_DP_INT_CHAN : 0;
		output |=  (PORT_INTERRUPTS__P_INT_EN__P1_DMA_INT_EN__READ(reg)) ? CSMI_DP_INT_DMA : 0;
		output |=  (PORT_INTERRUPTS__P_INT_EN__P1_OVF_INT_EN__READ(reg)) ? CSMI_DP_INT_OVF : 0;
		output |=  (PORT_INTERRUPTS__P_INT_EN__P1_UND_INT_EN__READ(reg)) ? CSMI_DP_INT_UND : 0;
		break;
	case 2:
		output |=  (PORT_INTERRUPTS__P_INT_EN__P2_ACT_INT_EN__READ(reg)) ? CSMI_DP_INT_ACT : 0;
		output |=  (PORT_INTERRUPTS__P_INT_EN__P2_CON_INT_EN__READ(reg)) ? CSMI_DP_INT_CON : 0;
		output |=  (PORT_INTERRUPTS__P_INT_EN__P2_CHAN_INT_EN__READ(reg)) ? CSMI_DP_INT_CHAN : 0;
		output |=  (PORT_INTERRUPTS__P_INT_EN__P2_DMA_INT_EN__READ(reg)) ? CSMI_DP_INT_DMA : 0;
		output |=  (PORT_INTERRUPTS__P_INT_EN__P2_OVF_INT_EN__READ(reg)) ? CSMI_DP_INT_OVF : 0;
		output |=  (PORT_INTERRUPTS__P_INT_EN__P2_UND_INT_EN__READ(reg)) ? CSMI_DP_INT_UND : 0;
		break;
	case 3:
		output |=  (PORT_INTERRUPTS__P_INT_EN__P3_ACT_INT_EN__READ(reg)) ? CSMI_DP_INT_ACT : 0;
		output |=  (PORT_INTERRUPTS__P_INT_EN__P3_CON_INT_EN__READ(reg)) ? CSMI_DP_INT_CON : 0;
		output |=  (PORT_INTERRUPTS__P_INT_EN__P3_CHAN_INT_EN__READ(reg)) ? CSMI_DP_INT_CHAN : 0;
		output |=  (PORT_INTERRUPTS__P_INT_EN__P3_DMA_INT_EN__READ(reg)) ? CSMI_DP_INT_DMA : 0;
		output |=  (PORT_INTERRUPTS__P_INT_EN__P3_OVF_INT_EN__READ(reg)) ? CSMI_DP_INT_OVF : 0;
		output |=  (PORT_INTERRUPTS__P_INT_EN__P3_UND_INT_EN__READ(reg)) ? CSMI_DP_INT_UND : 0;
		break;
	default:
		break;
	}
	*interruptMask = output;

	return 0;
}


static uint32_t CSMI_ClearDataPortFifo(void* pD, uint8_t portNumber) {
	CSMI_Instance* instance;
	uint8_t portAddress;
	uint32_t reg;

	uint32_t result = CSMI_ClearDataPortFifoSanity(pD, portNumber);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	portAddress = portNumber / 4;
	//There are 4 Port registers per 1 32 bit P_INT_EN register

	reg = CSMI_ReadReg(PORT_INTERRUPTS.P_INT_EN[portAddress]);

	switch (portNumber % 4) {
	case 0:
		PORT_INTERRUPTS__P_INT_EN__P0_FIFO_CLR__SET(reg);
		break;
	case 1:
		PORT_INTERRUPTS__P_INT_EN__P1_FIFO_CLR__SET(reg);
		break;
	case 2:
		PORT_INTERRUPTS__P_INT_EN__P2_FIFO_CLR__SET(reg);
		break;
	case 3:
		PORT_INTERRUPTS__P_INT_EN__P3_FIFO_CLR__SET(reg);
		break;
	default:
		break;
	}
	CSMI_WriteReg(PORT_INTERRUPTS.P_INT_EN[portAddress], reg);

	return 0;
}


static uint32_t CSMI_SetPresenceRateGeneration(void* pD, uint8_t portNumber, bool enable) {
	CSMI_Instance* instance;
	uint8_t portAddress;
	uint32_t reg;

	uint32_t result = CSMI_SetPresenceRateGenerationSanity(pD, portNumber, enable);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	portAddress = portNumber / 4;
	//There are 4 Port registers per 1 32 bit P_INT_EN register

	reg = CSMI_ReadReg(PORT_INTERRUPTS.P_INT_EN[portAddress]);

	switch (portNumber % 4) {
	case 0:
		PORT_INTERRUPTS__P_INT_EN__P0_PR_GEN_EN__MODIFY(reg, enable);
		break;
	case 1:
		PORT_INTERRUPTS__P_INT_EN__P1_PR_GEN_EN__MODIFY(reg, enable);
		break;
	case 2:
		PORT_INTERRUPTS__P_INT_EN__P2_PR_GEN_EN__MODIFY(reg, enable);
		break;
	case 3:
		PORT_INTERRUPTS__P_INT_EN__P3_PR_GEN_EN__MODIFY(reg, enable);
		break;
	default:
		break;
	}
	CSMI_WriteReg(PORT_INTERRUPTS.P_INT_EN[portAddress], reg);

	return 0;
}


static uint32_t CSMI_GetPresenceRateGeneration(void* pD, uint8_t portNumber, bool* enable) {
	CSMI_Instance* instance;
	uint8_t portAddress;
	uint32_t reg;

	uint32_t result = CSMI_GetPresenceRateGenerationSanity(pD, portNumber, enable);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	portAddress = portNumber / 4;
	reg = CSMI_ReadReg(PORT_INTERRUPTS.P_INT_EN[portAddress]);

	switch (portNumber % 4) {
	case 0:
		*enable = PORT_INTERRUPTS__P_INT_EN__P0_PR_GEN_EN__READ(reg);
		break;
	case 1:
		*enable = PORT_INTERRUPTS__P_INT_EN__P1_PR_GEN_EN__READ(reg);
		break;
	case 2:
		*enable = PORT_INTERRUPTS__P_INT_EN__P2_PR_GEN_EN__READ(reg);
		break;
	case 3:
		*enable = PORT_INTERRUPTS__P_INT_EN__P3_PR_GEN_EN__READ(reg);
		break;
	default:
		break;
	}

	return 0;
}


static uint32_t CSMI_AssignMessageCallbacks(void* pD, CSMI_MessageCallbacks* msgCallbacks) {
	CSMI_Instance* instance;

	uint32_t result = CSMI_AssignMessageCallbacksSanity(pD, msgCallbacks);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	CPS_BufferCopy((uint8_t*) &(instance->messageCallbacks), (uint8_t*) msgCallbacks, sizeof(CSMI_MessageCallbacks));

	return 0;
}


static uint32_t CSMI_SendRawMessage(void* pD, void* message, uint8_t messageLength) {
	CSMI_Instance* instance;

	uint32_t result = CSMI_SendRawMessageSanity(pD, message, messageLength);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	return CSMI_FifoTransmit(instance, (uint8_t *) message, messageLength, 1);
}


static uint32_t CSMI_SendMessage(void* pD, CSMI_Message* message) {
	CSMI_Instance* instance;

	uint32_t result = CSMI_SendMessageSanity(pD, message);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	return CSMI_TransmitMessage(instance, message);
}

static uint32_t CSMI_GetRegisterValue(void* pD, uint16_t regAddress, uint32_t* regContent) {
	CSMI_Instance* instance;

	uint32_t result = CSMI_GetRegisterValueSanity(pD, regAddress, regContent);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	if (regAddress & 0x3) { //Register address must be aligned to 32-bits
		SLIMBUS_CORE_LIMIT_ERR("reg address is invalid: 0x%x\n", regAddress);
		return EINVAL;
	}

	*regContent = CPS_UncachedRead32((uint32_t *) instance->registerBase + (regAddress >> 2) );

	return 0;
}


static uint32_t CSMI_SetRegisterValue(void* pD, uint16_t regAddress, uint32_t regContent) {
	CSMI_Instance* instance;

	uint32_t result = CSMI_SetRegisterValueSanity(pD, regAddress, regContent);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	if (regAddress & 0x3) { //Register address must be aligned to 32-bits
		SLIMBUS_CORE_LIMIT_ERR("reg address is invalid: 0x%x\n", regAddress);
		return EINVAL;
	}

	CPS_UncachedWrite32((uint32_t *) instance->registerBase + (regAddress >> 2), regContent);

	return 0;
}


static uint32_t CSMI_SetMessageChannelLapse(void* pD, uint8_t mchLapse) {
	CSMI_Instance* instance;
	uint32_t reg;

	uint32_t result = CSMI_SetMessageChannelLapseSanity(pD, mchLapse);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	reg = CSMI_ReadReg(COMMAND_STATUS.MCH_USAGE);
	COMMAND_STATUS__MCH_USAGE__MCH_LAPSE__MODIFY(reg, mchLapse);
	CSMI_WriteReg(COMMAND_STATUS.MCH_USAGE, reg);

	return 0;
}

static uint32_t CSMI_GetMessageChannelLapse(void* pD, uint8_t* mchLapse) {
	CSMI_Instance* instance;
	uint32_t reg;

	uint32_t result = CSMI_GetMessageChannelLapseSanity(pD, mchLapse);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	reg = CSMI_ReadReg(COMMAND_STATUS.MCH_USAGE);
	*mchLapse = COMMAND_STATUS__MCH_USAGE__MCH_LAPSE__READ(reg);

	return 0;
}

static uint32_t CSMI_GetMessageChannelUsage(void* pD, uint16_t* mchUsage) {
	CSMI_Instance* instance;
	uint32_t reg;

	uint32_t result = CSMI_GetMessageChannelUsageSanity(pD, mchUsage);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}


	instance = (CSMI_Instance*) pD;

	reg = CSMI_ReadReg(COMMAND_STATUS.MCH_USAGE);
	*mchUsage = COMMAND_STATUS__MCH_USAGE__MCH_USAGE__READ(reg);

	return 0;
}

static uint32_t CSMI_GetMessageChannelCapacity(void* pD, uint16_t* mchCapacity) {
	CSMI_Instance* instance;
	uint32_t reg;

	uint32_t result =CSMI_GetMessageChannelCapacitySanity(pD, mchCapacity);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	reg = CSMI_ReadReg(COMMAND_STATUS.MCH_USAGE);
	*mchCapacity = COMMAND_STATUS__MCH_USAGE__MCH_CAPACITY__READ(reg);

	return 0;
}


static uint32_t CSMI_SetSnifferMode(void* pD, bool state) {
	CSMI_Instance* instance;
	uint32_t reg;

	uint32_t result = CSMI_SetSnifferModeSanity(pD, state);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	if (CSMI_CfgStrobeCheck(instance)) {
		SLIMBUS_CORE_LIMIT_ERR("strobe check fail\n");
		return EIO;
	}

	reg = CSMI_ReadReg(CONFIGURATION.CONFIG_MODE);
	CONFIGURATION__CONFIG_MODE__SNIFFER_MODE__MODIFY(reg, state);
	CSMI_WriteReg(CONFIGURATION.CONFIG_MODE, reg);

	CSMI_CfgStrobeSet(instance, 0);

	return 0;
}


static uint32_t CSMI_GetSnifferMode(void* pD, bool* state) {
	CSMI_Instance* instance;
	uint32_t reg;

	uint32_t result = CSMI_GetSnifferModeSanity(pD, state);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	reg = CSMI_ReadReg(CONFIGURATION.CONFIG_MODE);
	*state = CONFIGURATION__CONFIG_MODE__SNIFFER_MODE__READ(reg);

	return 0;
}


static uint32_t CSMI_SetFramerEnabled(void* pD, bool state) {
	CSMI_Instance* instance;
	uint32_t reg;

	uint32_t result = CSMI_SetFramerEnabledSanity(pD, state);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	if (CSMI_CfgStrobeCheck(instance)) {
		SLIMBUS_CORE_LIMIT_ERR("strobe check fail\n");
		return EIO;
	}

	reg = CSMI_ReadReg(CONFIGURATION.CONFIG_MODE);
	CONFIGURATION__CONFIG_MODE__FR_EN__MODIFY(reg, state);
	CSMI_WriteReg(CONFIGURATION.CONFIG_MODE, reg);

	CSMI_CfgStrobeSet(instance, 0);

	return 0;
}


static uint32_t CSMI_GetFramerEnabled(void* pD, bool* state) {
	CSMI_Instance* instance;
	uint32_t reg;

	uint32_t result = CSMI_GetFramerEnabledSanity(pD, state);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	reg = CSMI_ReadReg(CONFIGURATION.CONFIG_MODE);
	*state = CONFIGURATION__CONFIG_MODE__FR_EN__READ(reg);

	return 0;
}


static uint32_t CSMI_SetDeviceEnabled(void* pD, bool state) {
	CSMI_Instance* instance;
	uint32_t reg;

	uint32_t result = CSMI_SetDeviceEnabledSanity(pD, state);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	if (CSMI_CfgStrobeCheck(instance)) {
		SLIMBUS_CORE_LIMIT_ERR("strobe check fail\n");
		return EIO;
	}

	reg = CSMI_ReadReg(CONFIGURATION.CONFIG_MODE);
	CONFIGURATION__CONFIG_MODE__DEV_EN__MODIFY(reg, state);
	CSMI_WriteReg(CONFIGURATION.CONFIG_MODE, reg);

	CSMI_CfgStrobeSet(instance, 0);

	return 0;
}


static uint32_t CSMI_GetDeviceEnabled(void* pD, bool* state) {
	CSMI_Instance* instance;
	uint32_t reg;

	uint32_t result = CSMI_GetDeviceEnabledSanity(pD, state);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	reg = CSMI_ReadReg(CONFIGURATION.CONFIG_MODE);
	*state = CONFIGURATION__CONFIG_MODE__DEV_EN__READ(reg);

	return 0;
}


static uint32_t CSMI_SetGoAbsent(void* pD, bool state) {
	CSMI_Instance* instance;
	uint32_t reg;

	uint32_t result = CSMI_SetGoAbsentSanity(pD, state);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	if (CSMI_CfgStrobeCheck(instance)) {
		SLIMBUS_CORE_LIMIT_ERR("strobe check fail\n");
		return EIO;
	}

	reg = CSMI_ReadReg(CONFIGURATION.CONFIG_MODE);
	CONFIGURATION__CONFIG_MODE__GO_ABSENT__MODIFY(reg, state);
	CSMI_WriteReg(CONFIGURATION.CONFIG_MODE, reg);

	CSMI_CfgStrobeSet(instance, 0);

	return 0;
}


static uint32_t CSMI_GetGoAbsent(void* pD, bool* state) {
	CSMI_Instance* instance;
	uint32_t reg;

	uint32_t result = CSMI_GetGoAbsentSanity(pD, state);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	reg = CSMI_ReadReg(CONFIGURATION.CONFIG_MODE);
	*state = CONFIGURATION__CONFIG_MODE__GO_ABSENT__READ(reg);

	return 0;
}


static uint32_t CSMI_SetFramerConfig(void* pD, CSMI_FramerConfig* framerConfig) {
	CSMI_Instance* instance;
	uint32_t reg;

	uint32_t result = CSMI_SetFramerConfigSanity(pD, framerConfig);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	if ((framerConfig->quality != CSMI_FQ_IRREGULAR)
	     && (framerConfig->quality != CSMI_FQ_LOW_JITTER)
	     && (framerConfig->quality != CSMI_FQ_PUNCTURED)
	     && (framerConfig->quality != CSMI_FQ_REGULAR)) {
		SLIMBUS_CORE_LIMIT_ERR("framer config's quality is invalid: %d\n", framerConfig->quality);
		return EINVAL;
	}

	instance = (CSMI_Instance*) pD;

	if (CSMI_CfgStrobeCheck(instance)) {
		SLIMBUS_CORE_LIMIT_ERR("strobe check fail\n");
		return EIO;
	}

	reg = CSMI_ReadReg(CONFIGURATION.CONFIG_FR);
	CONFIGURATION__CONFIG_FR__PAUSE_AT_RFCHNG__MODIFY(reg, framerConfig->pauseAtRootFrequencyChange);
	CONFIGURATION__CONFIG_FR__QUALITY__MODIFY(reg, framerConfig->quality);
	CONFIGURATION__CONFIG_FR__RF_SUPP__MODIFY(reg, framerConfig->rootFrequenciesSupported);
	CSMI_WriteReg(CONFIGURATION.CONFIG_FR, reg);

	CSMI_CfgStrobeSet(instance, 0);

	return 0;
}


static uint32_t CSMI_GetFramerConfig(void* pD, CSMI_FramerConfig* framerConfig) {
	CSMI_Instance* instance;
	uint32_t reg;

	uint32_t result = CSMI_GetFramerConfigSanity(pD, framerConfig);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	reg = CSMI_ReadReg(CONFIGURATION.CONFIG_FR);
	framerConfig->pauseAtRootFrequencyChange = CONFIGURATION__CONFIG_FR__PAUSE_AT_RFCHNG__READ(reg);
	framerConfig->quality = CONFIGURATION__CONFIG_FR__QUALITY__READ(reg);
	framerConfig->rootFrequenciesSupported = CONFIGURATION__CONFIG_FR__RF_SUPP__READ(reg);

	return 0;
}


static uint32_t CSMI_SetGenericDeviceConfig(void* pD, CSMI_GenericDeviceConfig* genericDeviceConfig) {
	CSMI_Instance* instance;
	uint32_t reg;
	uint8_t temp;

	uint32_t result = CSMI_SetGenericDeviceConfigSanity(pD, genericDeviceConfig);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	/* Checking input structure parameters */
	/* Limit maximum values, based on register field length */
	if (genericDeviceConfig->presenceRatesSupported > 0xFFFFFF) {
		SLIMBUS_CORE_LIMIT_ERR("device config param is invalid: 0x%x\n", genericDeviceConfig->presenceRatesSupported);
		return EINVAL;
	}

	if (genericDeviceConfig->dataPortClockPrescaler > 0xF) {
		SLIMBUS_CORE_LIMIT_ERR("device config param is invalid: 0x%x\n", genericDeviceConfig->dataPortClockPrescaler);
		return EINVAL;
	}

	if (genericDeviceConfig->cportClockDivider > 0x7) {
		SLIMBUS_CORE_LIMIT_ERR("device config param is invalid: 0x%x\n", genericDeviceConfig->cportClockDivider);
		return EINVAL;
	}

	if ((genericDeviceConfig->referenceClockSelector != CSMI_RC_CLOCK_GEAR_6)
			&& (genericDeviceConfig->referenceClockSelector != CSMI_RC_CLOCK_GEAR_7)
			&& (genericDeviceConfig->referenceClockSelector != CSMI_RC_CLOCK_GEAR_8)
			&& (genericDeviceConfig->referenceClockSelector != CSMI_RC_CLOCK_GEAR_9)) {
		SLIMBUS_CORE_LIMIT_ERR("device config param is invalid: 0x%x\n", genericDeviceConfig->referenceClockSelector);
 		return EINVAL;
	}

	instance = (CSMI_Instance*) pD;

	if (CSMI_CfgStrobeCheck(instance)) {
		SLIMBUS_CORE_LIMIT_ERR("strobe check fail\n");
		return EIO;
	}

	reg = CSMI_ReadReg(CONFIGURATION.CONFIG_PR_TP);
	CONFIGURATION__CONFIG_PR_TP__PR_SUPP__MODIFY(reg, genericDeviceConfig->presenceRatesSupported);
	temp  = CSMI_TpField(ISOCHRONOUS, genericDeviceConfig->transportProtocolIsochronous);
	temp |= CSMI_TpField(PUSHED, genericDeviceConfig->transportProtocolPushed);
	temp |= CSMI_TpField(PULLED, genericDeviceConfig->transportProtocolPulled);
	CONFIGURATION__CONFIG_PR_TP__TP_SUPP__MODIFY(reg, temp);
	CSMI_WriteReg(CONFIGURATION.CONFIG_PR_TP, reg);

	reg = CSMI_ReadReg(CONFIGURATION.CONFIG_CPORT);
	CONFIGURATION__CONFIG_CPORT__CPORT_CLK_DIV__MODIFY(reg, genericDeviceConfig->cportClockDivider);
	CSMI_WriteReg(CONFIGURATION.CONFIG_CPORT, reg);

	reg = CSMI_ReadReg(CONFIGURATION.CONFIG_DPORT);
	CONFIGURATION__CONFIG_DPORT__SINK_START_LVL__MODIFY(reg, genericDeviceConfig->sinkStartLevel);
	CONFIGURATION__CONFIG_DPORT__DPORT_CLK_PRESC__MODIFY(reg, genericDeviceConfig->dataPortClockPrescaler);
	CONFIGURATION__CONFIG_DPORT__REFCLK_SEL__MODIFY(reg, genericDeviceConfig->referenceClockSelector);
	CSMI_WriteReg(CONFIGURATION.CONFIG_DPORT, reg);

	reg = CSMI_ReadReg(CONFIGURATION.CONFIG_THR);
	CONFIGURATION__CONFIG_THR__SRC_THR__MODIFY(reg, genericDeviceConfig->dmaTresholdSource);
	CONFIGURATION__CONFIG_THR__SINK_THR__MODIFY(reg, genericDeviceConfig->dmaTresholdSink);
	CSMI_WriteReg(CONFIGURATION.CONFIG_THR, reg);

	CSMI_CfgStrobeSet(instance, 0);

	return 0;
}


static uint32_t CSMI_GetGenericDeviceConfig(void* pD, CSMI_GenericDeviceConfig* genericDeviceConfig) {
	CSMI_Instance* instance;
	uint32_t reg;
	uint8_t temp;

	uint32_t result = CSMI_GetGenericDeviceConfigSanity(pD, genericDeviceConfig);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	reg = CSMI_ReadReg(CONFIGURATION.CONFIG_PR_TP);
	genericDeviceConfig->presenceRatesSupported = CONFIGURATION__CONFIG_PR_TP__PR_SUPP__READ(reg);
	temp = CONFIGURATION__CONFIG_PR_TP__TP_SUPP__READ(reg);
	genericDeviceConfig->transportProtocolIsochronous = CSMI_GetTpField(ISOCHRONOUS, temp);
	genericDeviceConfig->transportProtocolPushed = CSMI_GetTpField(PUSHED, temp);
	genericDeviceConfig->transportProtocolPulled = CSMI_GetTpField(PULLED, temp);

	reg = CSMI_ReadReg(CONFIGURATION.CONFIG_CPORT);
	genericDeviceConfig->cportClockDivider = CONFIGURATION__CONFIG_CPORT__CPORT_CLK_DIV__READ(reg);

	reg = CSMI_ReadReg(CONFIGURATION.CONFIG_DPORT);
	genericDeviceConfig->sinkStartLevel = CONFIGURATION__CONFIG_DPORT__SINK_START_LVL__READ(reg);
	genericDeviceConfig->dataPortClockPrescaler = CONFIGURATION__CONFIG_DPORT__DPORT_CLK_PRESC__READ(reg);
	genericDeviceConfig->referenceClockSelector = CONFIGURATION__CONFIG_DPORT__REFCLK_SEL__READ(reg);

	reg = CSMI_ReadReg(CONFIGURATION.CONFIG_THR);
	genericDeviceConfig->dmaTresholdSource = CONFIGURATION__CONFIG_THR__SRC_THR__READ(reg);
	genericDeviceConfig->dmaTresholdSink = CONFIGURATION__CONFIG_THR__SINK_THR__READ(reg);

	return 0;
}

static uint32_t CSMI_GetDataPortStatus(void* pD, uint8_t portNumber, CSMI_DataPortStatus* portStatus) {
	CSMI_Instance* instance;
	uint32_t reg;

	uint32_t result = CSMI_GetDataPortStatusSanity(pD, portNumber, portStatus);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	reg = CSMI_ReadReg(PORT_STATE[portNumber].P_STATE_0);
	portStatus->active = PORT_STATE__P_STATE_0__ACTIVE__READ(reg);
	portStatus->contentDefined = PORT_STATE__P_STATE_0__CONTENT_DEFINED__READ(reg);
	portStatus->channelDefined = PORT_STATE__P_STATE_0__CHANNEL_DEFINED__READ(reg);
	portStatus->sink = PORT_STATE__P_STATE_0__SINK__READ(reg);
	portStatus->overflow = PORT_STATE__P_STATE_0__OVF__READ(reg);
	portStatus->underrun = PORT_STATE__P_STATE_0__UND__READ(reg);
	portStatus->dportReady = PORT_STATE__P_STATE_0__DPORT_READY__READ(reg);
	portStatus->segmentInterval = PORT_STATE__P_STATE_0__S_INTERVAL__READ(reg);
	portStatus->transportProtocol = PORT_STATE__P_STATE_0__TR_PROTOCOL__READ(reg);

	reg = CSMI_ReadReg(PORT_STATE[portNumber].P_STATE_1);
	portStatus->presenceRate = PORT_STATE__P_STATE_1__P_RATE__READ(reg);
	portStatus->frequencyLock = PORT_STATE__P_STATE_1__FR_LOCK__READ(reg);
	portStatus->dataType = PORT_STATE__P_STATE_1__DATA_TYPE__READ(reg);
	portStatus->dataLength = PORT_STATE__P_STATE_1__DATA_LENGTH__READ(reg);
	portStatus->portLinked = PORT_STATE__P_STATE_1__PORT_LINKED__READ(reg);
	portStatus->channelLink = PORT_STATE__P_STATE_1__CH_LINK__READ(reg);

	return 0;
}

static uint32_t CSMI_Unfreeze(void* pD) {
	CSMI_Instance* instance;
	uint32_t reg;

	uint32_t result = CSMI_UnfreezeSanity(pD);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;
	reg = CSMI_ReadReg(COMMAND_STATUS.COMMAND);
	COMMAND_STATUS__COMMAND__UNFREEZE__SET(reg);
	CSMI_WriteReg(COMMAND_STATUS.COMMAND, reg);

	return 0;
}


static uint32_t CSMI_CancelConfiguration(void* pD) {
	CSMI_Instance* instance;
	uint32_t reg = 0;

	uint32_t result = CSMI_CancelConfigurationSanity(pD);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;
	reg = CSMI_ReadReg(COMMAND_STATUS.COMMAND);
	COMMAND_STATUS__COMMAND__CFG_STROBE__CLR(reg);
	COMMAND_STATUS__COMMAND__CFG_STROBE_CLR__SET(reg);
	CSMI_WriteReg(COMMAND_STATUS.COMMAND, reg);

	return 0;
}


static uint32_t CSMI_GetStatusSynchronization(void* pD, bool* fSync, bool* sfSync, bool* mSync, bool* sfbSync, bool* phSync) {
	CSMI_Instance* instance;
	uint32_t reg;

	uint32_t result = CSMI_GetStatusSynchronizationSanity(pD, fSync, sfSync, mSync, sfbSync, phSync);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	reg = CSMI_ReadReg(COMMAND_STATUS.STATE);
	if (fSync != NULL)
		*fSync = COMMAND_STATUS__STATE__F_SYNC__READ(reg);
	if (sfSync != NULL)
		*sfSync = COMMAND_STATUS__STATE__SF_SYNC__READ(reg);
	if (mSync != NULL)
		*mSync = COMMAND_STATUS__STATE__M_SYNC__READ(reg);
	if (sfbSync != NULL)
		*sfbSync = COMMAND_STATUS__STATE__SFB_SYNC__READ(reg);
	if (phSync != NULL)
		*phSync = COMMAND_STATUS__STATE__PH_SYNC__READ(reg);

	return 0;
}

static uint32_t CSMI_GetStatusDetached(void* pD, bool* detached) {
	CSMI_Instance* instance;
	uint32_t reg;

	uint32_t result = CSMI_GetStatusDetachedSanity(pD, detached);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	reg = CSMI_ReadReg(COMMAND_STATUS.STATE);
	*detached = COMMAND_STATUS__STATE__DETACHED__READ(reg);

	return 0;
}

static uint32_t CSMI_GetStatusSlimbus(void* pD, CSMI_SubframeMode* subframeMode, CSMI_ClockGear* clockGear, CSMI_RootFrequency* rootFr)
{
	CSMI_Instance* instance;
	uint32_t reg;

	uint32_t result = CSMI_GetStatusSlimbusSanity(pD, subframeMode, clockGear, rootFr);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	reg = CSMI_ReadReg(COMMAND_STATUS.STATE);
	if (subframeMode != NULL)
	   *subframeMode = COMMAND_STATUS__STATE__SUBFRAME_MODE__READ(reg);
	if (clockGear != NULL)
	   *clockGear = COMMAND_STATUS__STATE__CLOCK_GEAR__READ(reg);
	if (rootFr != NULL)
	   *rootFr = COMMAND_STATUS__STATE__ROOT_FR__READ(reg);

	return 0;
}

static uint32_t CSMI_MsgAssignLogicalAddress(void* pD, uint64_t destinationEa, uint8_t newLa) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;

	uint32_t result = CSMI_MsgAssignLogicalAddressSanity(pD, destinationEa, newLa);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_ASSIGN_LOGICAL_ADDRESS;
	txMsg.destinationType = CSMI_DT_ENUMERATION_ADDRESS;
	txMsg.destinationAddress = destinationEa;

	/*
	 * Payload:
	 * 0	LA [7:0]
	 */
	txMsg.payload[0] = CSMI_MsgPayloadField(LOGICAL_ADDRESS, newLa);
	txMsg.payloadLength = 1;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgResetDevice(void* pD, uint8_t destinationLa) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;

	uint32_t result = CSMI_MsgResetDeviceSanity(pD, destinationLa);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_RESET_DEVICE;
	txMsg.destinationType = CSMI_DT_LOGICAL_ADDRESS;
	txMsg.destinationAddress = destinationLa;

	/*
	 * Payload:
	 * None
	 */
	txMsg.payloadLength = 0;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgChangeLogicalAddress(void* pD, uint8_t destinationLa, uint8_t newLa) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;

	uint32_t result = CSMI_MsgChangeLogicalAddressSanity(pD, destinationLa, newLa);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_CHANGE_LOGICAL_ADDRESS;
	txMsg.destinationType = CSMI_DT_LOGICAL_ADDRESS;
	txMsg.destinationAddress = destinationLa;

	/*
	 * Payload:
	 * 0	LA [7:0]
	 */
	txMsg.payload[0] = CSMI_MsgPayloadField(LOGICAL_ADDRESS, newLa);
	txMsg.payloadLength = 1;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgChangeArbitrationPriority(void* pD, bool broadcast, uint8_t destinationLa, CSMI_ArbitrationPriority newArbitrationPriority) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;

	uint32_t result = CSMI_MsgChangeArbitrationPrioritySanity(pD, broadcast, destinationLa, newArbitrationPriority);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_CHANGE_ARBITRATION_PRIORITY;
	if (broadcast) {
		txMsg.destinationType = CSMI_DT_BROADCAST;
		txMsg.destinationAddress = 0x00;
	} else {
		txMsg.destinationType = CSMI_DT_LOGICAL_ADDRESS;
		txMsg.destinationAddress = destinationLa;
	}

	/*
	 * Payload:
	 * 0	AP [2:0]
	 */
	txMsg.payload[0] = CSMI_MsgPayloadField(ARBITRATION_PRIORITY, newArbitrationPriority);
	txMsg.payloadLength = 1;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgRequestSelfAnnouncement(void* pD) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;

	uint32_t result = CSMI_MsgRequestSelfAnnouncementSanity(pD);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_REQUEST_SELF_ANNOUNCEMENT;
	txMsg.destinationType = CSMI_DT_BROADCAST;
	txMsg.destinationAddress = 0x00;

	/*
	 * Payload:
	 * None
	 */
	txMsg.payloadLength = 0;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgConnectSource(void* pD, uint8_t destinationLa, uint8_t portNumber, uint8_t channelNumber) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;

	uint32_t result = CSMI_MsgConnectSourceSanity(pD, destinationLa, portNumber, channelNumber);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_CONNECT_SOURCE;
	txMsg.destinationType = CSMI_DT_LOGICAL_ADDRESS;
	txMsg.destinationAddress = destinationLa;

	/*
	 * Payload:
	 * 0	PN [5:0]
	 * 1	CN [7:0]
	 */
	txMsg.payload[0] = CSMI_MsgPayloadField(PORT_NUMBER, portNumber);
	txMsg.payload[1] = CSMI_MsgPayloadField(DATA_CHANNEL_NUMBER, channelNumber);
	txMsg.payloadLength = 2;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgConnectSink(void* pD, uint8_t destinationLa, uint8_t portNumber, uint8_t channelNumber) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;

	uint32_t result = CSMI_MsgConnectSinkSanity(pD, destinationLa, portNumber, channelNumber);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_CONNECT_SINK;
	txMsg.destinationType = CSMI_DT_LOGICAL_ADDRESS;
	txMsg.destinationAddress = destinationLa;

	/*
	 * Payload:
	 * 0	PN [5:0]
	 * 1	CN [7:0]
	 */
	txMsg.payload[0] = CSMI_MsgPayloadField(PORT_NUMBER, portNumber);
	txMsg.payload[1] = CSMI_MsgPayloadField(DATA_CHANNEL_NUMBER, channelNumber);
	txMsg.payloadLength = 2;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgDisconnectPort(void* pD, uint8_t destinationLa, uint8_t portNumber) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;

	uint32_t result = CSMI_MsgDisconnectPortSanity(pD, destinationLa, portNumber);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_DISCONNECT_PORT;
	txMsg.destinationType = CSMI_DT_LOGICAL_ADDRESS;
	txMsg.destinationAddress = destinationLa;

	/*
	 * Payload:
	 * 0	PN [5:0]
	 */
	txMsg.payload[0] = CSMI_MsgPayloadField(PORT_NUMBER, portNumber);
	txMsg.payloadLength = 1;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgChangeContent(void* pD, uint8_t channelNumber, bool frequencyLockedBit, CSMI_PresenceRate presenceRate, CSMI_AuxFieldFormat auxiliaryBitFormat, CSMI_DataType dataType, bool channelLink, uint8_t dataLength) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;

	uint32_t result = CSMI_MsgChangeContentSanity(pD, channelNumber, frequencyLockedBit, presenceRate, auxiliaryBitFormat, dataType, channelLink, dataLength);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_CHANGE_CONTENT;
	txMsg.destinationType = CSMI_DT_BROADCAST;
	txMsg.destinationAddress = 0x00;

	/*
	 * Payload:
	 * 0	CN [7:0]
	 * 1	FL [7:7]	PR [6:0]
	 * 2	AF [7:4]	DT [3:0]
	 * 3	CL [5:5]	DL [4:0]
	 */
	txMsg.payload[0] = CSMI_MsgPayloadField(DATA_CHANNEL_NUMBER, channelNumber);
	txMsg.payload[1] = CSMI_MsgPayloadField(PRESENCE_RATE, presenceRate) | CSMI_MsgPayloadField(FREQUENCY_LOCKED_BIT, frequencyLockedBit);
	txMsg.payload[2] = CSMI_MsgPayloadField(DATA_TYPE, dataType) | CSMI_MsgPayloadField(AUXILIARY_BIT_FORMAT, auxiliaryBitFormat);
	txMsg.payload[3] = CSMI_MsgPayloadField(DATA_LENGTH, dataLength) | CSMI_MsgPayloadField(CHANNEL_LINK, channelLink);
	txMsg.payloadLength = 4;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgRequestInformation(void* pD, bool broadcast, uint8_t destinationLa, uint8_t transactionId, uint16_t elementCode) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;

	uint32_t result = CSMI_MsgRequestInformationSanity(pD, broadcast, destinationLa, transactionId, elementCode);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_REQUEST_INFORMATION;
	if (broadcast) {
		txMsg.destinationType = CSMI_DT_BROADCAST;
		txMsg.destinationAddress = 0x00;
	} else {
		txMsg.destinationType = CSMI_DT_LOGICAL_ADDRESS;
		txMsg.destinationAddress = destinationLa;
	}

	/*
	 * Payload:
	 * 0	TID [7:0]
	 * 1	EC [ 7:0]
	 * 2	EC [15:8]
	 */
	txMsg.payload[0] = CSMI_MsgPayloadField(TRANSACTION_ID, transactionId);
	txMsg.payload[1] = CSMI_LowerByte(elementCode);
	txMsg.payload[2] = CSMI_HigherByte(elementCode);
	txMsg.payloadLength = 3;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgRequestClearInformation(void* pD, bool broadcast, uint8_t destinationLa, uint8_t transactionId, uint16_t elementCode, uint8_t* clearMask, uint8_t clearMaskSize) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;
	uint8_t i;
	uint32_t result = CSMI_MsgRequestClearInformationSanity(pD, broadcast, destinationLa, transactionId, elementCode, clearMask, clearMaskSize);

	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	if ((clearMask == NULL) && (clearMaskSize > 0)) {
		SLIMBUS_CORE_LIMIT_ERR("input param is invalid\n");
		return EINVAL;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_REQUEST_CLEAR_INFORMATION;
	if (broadcast) {
		txMsg.destinationType = CSMI_DT_BROADCAST;
		txMsg.destinationAddress = 0x00;
	} else {
		txMsg.destinationType = CSMI_DT_LOGICAL_ADDRESS;
		txMsg.destinationAddress = destinationLa;
	}

	/*
	 * Payload:
	 * 0	TID [7:0]
	 * 1	EC [ 7:0]
	 * 2	EC [15:8]
	 * 3	CM [ 7:0]
	 * N+2	CM [8N-1: 8N-8]
	 */
	txMsg.payload[0] = CSMI_MsgPayloadField(TRANSACTION_ID, transactionId);
	txMsg.payload[1] = CSMI_LowerByte(elementCode);
	txMsg.payload[2] = CSMI_HigherByte(elementCode);
	for (i = 0; i < clearMaskSize; i++)
		txMsg.payload[i+3] = clearMask[i];
	txMsg.payloadLength = 3 + clearMaskSize;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgClearInformation(void* pD, bool broadcast, uint8_t destinationLa, uint16_t elementCode, uint8_t* clearMask, uint8_t clearMaskSize) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;
	uint8_t i;
	uint32_t result = CSMI_MsgClearInformationSanity(pD, broadcast, destinationLa, elementCode, clearMask, clearMaskSize);

	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	if ((clearMask == NULL) && (clearMaskSize > 0)) {
		SLIMBUS_CORE_LIMIT_ERR("input param is invalid\n");
		return EINVAL;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_CLEAR_INFORMATION;
	if (broadcast) {
		txMsg.destinationType = CSMI_DT_BROADCAST;
		txMsg.destinationAddress = 0x00;
	} else {
		txMsg.destinationType = CSMI_DT_LOGICAL_ADDRESS;
		txMsg.destinationAddress = destinationLa;
	}

	/*
	 * Payload:
	 * 0	EC [ 7:0]
	 * 1	EC [15:8]
	 * 2	CM [ 7:0]
	 * N+1	CM [8N-1: 8N-8]
	 */
	txMsg.payload[0] = CSMI_LowerByte(elementCode);
	txMsg.payload[1] = CSMI_HigherByte(elementCode);
	for (i = 0; i < clearMaskSize; i++)
		txMsg.payload[i+2] = clearMask[i];
	txMsg.payloadLength = 2 + clearMaskSize;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgBeginReconfiguration(void* pD) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;

	uint32_t result = CSMI_MsgBeginReconfigurationSanity(pD);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_BEGIN_RECONFIGURATION;
	txMsg.destinationType = CSMI_DT_BROADCAST;
	txMsg.destinationAddress = 0x00;

	/*
	 * Payload:
	 * None
	 */
	txMsg.payloadLength = 0;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgNextActiveFramer(void* pD, uint8_t incomingFramerLa, uint16_t outgoingFramerClockCycles, uint16_t incomingFramerClockCycles) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;

	uint32_t result = CSMI_MsgNextActiveFramerSanity(pD, incomingFramerLa, outgoingFramerClockCycles, incomingFramerClockCycles);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_NEXT_ACTIVE_FRAMER;
	txMsg.destinationType = CSMI_DT_BROADCAST;
	txMsg.destinationAddress = 0x00;

	/*
	 * Payload:
	 * 0	LAIF [7:0]
	 * 1	NCo  [7:0]
	 * 2	NCi  [3:0]	NCo [11:8]
	 * 3	NCo [11:4]
	 */
	txMsg.payload[0] = CSMI_MsgPayloadField(LOGICAL_ADDRESS, incomingFramerLa);
	txMsg.payload[1] = CSMI_MsgPayloadField(OUTGOING_FRAMER_CYCLES_LOW, CSMI_LowerByte(outgoingFramerClockCycles));
	txMsg.payload[2] = CSMI_MsgPayloadField(OUTGOING_FRAMER_CYCLES_HIGH, CSMI_HigherByte(outgoingFramerClockCycles))
					 | CSMI_MsgPayloadField(INCOMING_FRAMER_CYCLES_LOW, CSMI_LowerByte(incomingFramerClockCycles));
	txMsg.payload[3] = CSMI_MsgPayloadField(INCOMING_FRAMER_CYCLES_HIGH, CSMI_HigherByte(incomingFramerClockCycles));
	txMsg.payloadLength = 4;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgNextSubframeMode(void* pD, CSMI_SubframeMode newSubframeMode) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;

	uint32_t result = CSMI_MsgNextSubframeModeSanity(pD, newSubframeMode);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_NEXT_SUBFRAME_MODE;
	txMsg.destinationType = CSMI_DT_BROADCAST;
	txMsg.destinationAddress = 0x00;

	/*
	 * Payload:
	 * 0	SM [4:0]
	 */
	txMsg.payload[0] = CSMI_MsgPayloadField(SUBFRAME_MODE, newSubframeMode);
	txMsg.payloadLength = 1;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgNextClockGear(void* pD, CSMI_ClockGear newClockGear) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;

	uint32_t result = CSMI_MsgNextClockGearSanity(pD, newClockGear);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_NEXT_CLOCK_GEAR;
	txMsg.destinationType = CSMI_DT_BROADCAST;
	txMsg.destinationAddress = 0x00;

	/*
	 * Payload:
	 * 0	CG [3:0]
	 */
	txMsg.payload[0] = CSMI_MsgPayloadField(CLOCK_GEAR, newClockGear);
	txMsg.payloadLength = 1;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgNextRootFrequency(void* pD, CSMI_RootFrequency newRootFrequency) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;

	uint32_t result = CSMI_MsgNextRootFrequencySanity(pD, newRootFrequency);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_NEXT_ROOT_FREQUENCY;
	txMsg.destinationType = CSMI_DT_BROADCAST;
	txMsg.destinationAddress = 0x00;

	/*
	 * Payload:
	 * 0	RF [3:0]
	 */
	txMsg.payload[0] = CSMI_MsgPayloadField(ROOT_FREQUENCY, newRootFrequency);
	txMsg.payloadLength = 1;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgNextPauseClock(void* pD, CSMI_RestartTime newRestartTime) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;

	uint32_t result = CSMI_MsgNextPauseClockSanity(pD, newRestartTime);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_NEXT_PAUSE_CLOCK;
	txMsg.destinationType = CSMI_DT_BROADCAST;
	txMsg.destinationAddress = 0x00;

	/*
	 * Payload:
	 * 0	RT [7:0]
	 */
	txMsg.payload[0] = CSMI_MsgPayloadField(RESTART_TIME, newRestartTime);
	txMsg.payloadLength = 1;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgNextResetBus(void* pD) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;

	uint32_t result = CSMI_MsgNextResetBusSanity(pD);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_NEXT_RESET_BUS;
	txMsg.destinationType = CSMI_DT_BROADCAST;
	txMsg.destinationAddress = 0x00;

	/*
	 * Payload:
	 * None
	 */
	txMsg.payloadLength = 0;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgNextShutdownBus(void* pD) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;

	uint32_t result = CSMI_MsgNextShutdownBusSanity(pD);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_NEXT_SHUTDOWN_BUS;
	txMsg.destinationType = CSMI_DT_BROADCAST;
	txMsg.destinationAddress = 0x00;

	/*
	 * Payload:
	 * None
	 */
	txMsg.payloadLength = 0;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgNextDefineChannel(void* pD, uint8_t channelNumber, CSMI_TransportProtocol transportProtocol, uint16_t segmentDistribution, uint8_t segmentLength) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;

	uint32_t result = CSMI_MsgNextDefineChannelSanity(pD, channelNumber, transportProtocol, segmentDistribution, segmentLength);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_NEXT_DEFINE_CHANNEL;
	txMsg.destinationType = CSMI_DT_BROADCAST;
	txMsg.destinationAddress = 0x00;

	/*
	 * Payload:
	 * 0	CN [7:0]
	 * 1	SD [7:0]
	 * 2	TP [7:4]	SD [11:8]
	 * 3				SL [4:0]
	 */
	txMsg.payload[0] = CSMI_MsgPayloadField(DATA_CHANNEL_NUMBER, channelNumber);
	txMsg.payload[1] = CSMI_MsgPayloadField(SEGMENT_DISTRIBUTION_LOW, CSMI_LowerByte(segmentDistribution));
	txMsg.payload[2] = CSMI_MsgPayloadField(SEGMENT_DISTRIBUTION_HIGH, CSMI_HigherByte(segmentDistribution))
					 | CSMI_MsgPayloadField(TRANSPORT_PROTOCOL, transportProtocol);
	txMsg.payload[3] = CSMI_MsgPayloadField(SEGMENT_LENGTH, segmentLength);
	txMsg.payloadLength = 4;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgNextDefineContent(void* pD, uint8_t channelNumber, bool frequencyLockedBit, CSMI_PresenceRate presenceRate, CSMI_AuxFieldFormat auxiliaryBitFormat, CSMI_DataType dataType, bool channelLink, uint8_t dataLength) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;

	uint32_t result = CSMI_MsgNextDefineContentSanity(pD, channelNumber, frequencyLockedBit, presenceRate, auxiliaryBitFormat, dataType, channelLink, dataLength);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_NEXT_DEFINE_CONTENT;
	txMsg.destinationType = CSMI_DT_BROADCAST;
	txMsg.destinationAddress = 0x00;

	/*
	 * Payload:
	 * 0	CN [7:0]
	 * 1	FL [7:7]	PR [6:0]
	 * 2	AF [7:4]	DT [3:0]
	 * 3	CL [5:5]	DL [4:0]
	 */
	txMsg.payload[0] = CSMI_MsgPayloadField(DATA_CHANNEL_NUMBER, channelNumber);
	txMsg.payload[1] = CSMI_MsgPayloadField(FREQUENCY_LOCKED_BIT, frequencyLockedBit)
					 | CSMI_MsgPayloadField(PRESENCE_RATE, presenceRate);
	txMsg.payload[2] = CSMI_MsgPayloadField(AUXILIARY_BIT_FORMAT, auxiliaryBitFormat)
					 | CSMI_MsgPayloadField(DATA_TYPE, dataType);
	txMsg.payload[3] = CSMI_MsgPayloadField(CHANNEL_LINK, channelLink)
					 | CSMI_MsgPayloadField(DATA_LENGTH, dataLength);
	txMsg.payloadLength = 4;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgNextActivateChannel(void* pD, uint8_t channelNumber) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;
	uint32_t result = CSMI_MsgNextActivateChannelSanity(pD, channelNumber);

	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_NEXT_ACTIVATE_CHANNEL;
	txMsg.destinationType = CSMI_DT_BROADCAST;
	txMsg.destinationAddress = 0x00;

	/*
	 * Payload:
	 * 0	CN [7:0]
	 */
	txMsg.payload[0] = CSMI_MsgPayloadField(DATA_CHANNEL_NUMBER, channelNumber);
	txMsg.payloadLength = 1;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgNextDeactivateChannel(void* pD, uint8_t channelNumber) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;

	uint32_t result = CSMI_MsgNextDeactivateChannelSanity(pD, channelNumber);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_NEXT_DEACTIVATE_CHANNEL;
	txMsg.destinationType = CSMI_DT_BROADCAST;
	txMsg.destinationAddress = 0x00;

	/*
	 * Payload:
	 * 0	CN [7:0]
	 */
	txMsg.payload[0] = CSMI_MsgPayloadField(DATA_CHANNEL_NUMBER, channelNumber);
	txMsg.payloadLength = 1;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgNextRemoveChannel(void* pD, uint8_t channelNumber) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;

	uint32_t result = CSMI_MsgNextRemoveChannelSanity(pD, channelNumber);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_NEXT_REMOVE_CHANNEL;
	txMsg.destinationType = CSMI_DT_BROADCAST;
	txMsg.destinationAddress = 0x00;

	/*
	 * Payload:
	 * 0	CN [7:0]
	 */
	txMsg.payload[0] = CSMI_MsgPayloadField(DATA_CHANNEL_NUMBER, channelNumber);
	txMsg.payloadLength = 1;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgReconfigureNow(void* pD) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;

	uint32_t result = CSMI_MsgReconfigureNowSanity(pD);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_RECONFIGURE_NOW;
	txMsg.destinationType = CSMI_DT_BROADCAST;
	txMsg.destinationAddress = 0x00;

	/*
	 * Payload:
	 * None
	 */
	txMsg.payloadLength = 0;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgRequestValue(void* pD, bool broadcast, uint8_t destinationLa, uint8_t transactionId, uint16_t elementCode) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;

	uint32_t result = CSMI_MsgRequestValueSanity(pD, broadcast, destinationLa, transactionId, elementCode);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_REQUEST_VALUE;
	if (broadcast) {
		txMsg.destinationType = CSMI_DT_BROADCAST;
		txMsg.destinationAddress = 0x00;
	} else {
		txMsg.destinationType = CSMI_DT_LOGICAL_ADDRESS;
		txMsg.destinationAddress = destinationLa;
	}

	/*
	 * Payload:
	 * 0	TID [7:0]
	 * 1	EC [ 7:0]
	 * 2	EC [15:8]
	 */
	txMsg.payload[0] = CSMI_MsgPayloadField(TRANSACTION_ID, transactionId);
	txMsg.payload[1] = CSMI_LowerByte(elementCode);
	txMsg.payload[2] = CSMI_HigherByte(elementCode);
	txMsg.payloadLength = 3;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgRequestChangeValue(void* pD, bool broadcast, uint8_t destinationLa, uint8_t transactionId, uint16_t elementCode, uint8_t* valueUpdate, uint8_t valueUpdateSize) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;
	uint8_t i;

	uint32_t result = CSMI_MsgRequestChangeValueSanity(pD, broadcast, destinationLa, transactionId, elementCode, valueUpdate, valueUpdateSize);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	if ((valueUpdate == NULL) && (valueUpdateSize > 0)) {
		SLIMBUS_CORE_LIMIT_ERR("input param is invalid\n");
		return EINVAL;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_REQUEST_CHANGE_VALUE;
	if (broadcast) {
		txMsg.destinationType = CSMI_DT_BROADCAST;
		txMsg.destinationAddress = 0x00;
	} else {
		txMsg.destinationType = CSMI_DT_LOGICAL_ADDRESS;
		txMsg.destinationAddress = destinationLa;
	}

	/*
	 * Payload:
	 * 0	TID [7:0]
	 * 1	EC [ 7:0]
	 * 2	EC [15:8]
	 * 3	VU [ 7:0]
	 * N+2	VU [8N-1: 8N-8]
	 */
	txMsg.payload[0] = CSMI_MsgPayloadField(TRANSACTION_ID, transactionId);
	txMsg.payload[1] = CSMI_LowerByte(elementCode);
	txMsg.payload[2] = CSMI_HigherByte(elementCode);
	for (i = 0; i < valueUpdateSize; i++)
		txMsg.payload[i + CSMI_ELEMENT_CODE_LENGTH + CSMI_TRANSACTION_ID_LENGTH] = valueUpdate[i];
	txMsg.payloadLength = CSMI_ELEMENT_CODE_LENGTH + CSMI_TRANSACTION_ID_LENGTH + valueUpdateSize;

	return CSMI_TransmitMessage(instance, &txMsg);
}


static uint32_t CSMI_MsgChangeValue(void* pD, bool broadcast, uint8_t destinationLa, uint16_t elementCode, uint8_t* valueUpdate, uint8_t valueUpdateSize) {
	CSMI_Instance* instance;
	CSMI_Message txMsg;
	uint8_t i;

	uint32_t result = CSMI_MsgChangeValueSanity(pD, broadcast, destinationLa, elementCode, valueUpdate, valueUpdateSize);
	if (result) {
		SLIMBUS_CORE_LIMIT_ERR("check sanity fail\n");
		return result;
	}

	if ((valueUpdate == NULL) && (valueUpdateSize > 0)) {
		SLIMBUS_CORE_LIMIT_ERR("input param is invalid\n");
		return EINVAL;
	}

	instance = (CSMI_Instance*) pD;

	txMsg.arbitrationType = CSMI_AT_SHORT;
	txMsg.sourceAddress = CSMI_MESSAGE_SOURCE_ACTIVE_MANAGER;
	txMsg.arbitrationPriority = CSMI_AP_DEFAULT;
	txMsg.messageType = CSMI_MT_CORE;
	txMsg.messageCode = CSMI_MESSAGE_CODE_CHANGE_VALUE;
	if (broadcast) {
		txMsg.destinationType = CSMI_DT_BROADCAST;
		txMsg.destinationAddress = 0x00;
	} else {
		txMsg.destinationType = CSMI_DT_LOGICAL_ADDRESS;
		txMsg.destinationAddress = destinationLa;
	}

	/*
	 * Payload:
	 * 0	EC [ 7:0]
	 * 1	EC [15:8]
	 * 2	VU [ 7:0]
	 * N+1	VU [8N-1: 8N-8]
	 */
	txMsg.payload[0] = CSMI_LowerByte(elementCode);
	txMsg.payload[1] = CSMI_HigherByte(elementCode);
	for (i = 0; i < valueUpdateSize; i++)
		txMsg.payload[i + CSMI_ELEMENT_CODE_LENGTH] = valueUpdate[i];
	txMsg.payloadLength = CSMI_ELEMENT_CODE_LENGTH + valueUpdateSize;

	return CSMI_TransmitMessage(instance, &txMsg);
}


CSMI_OBJ driver = {
	.probe = CSMI_Probe,
	.init = CSMI_Init,
	.isr = CSMI_Isr,
	.start = CSMI_Start,
	.stop = CSMI_Stop,
	.destroy = CSMI_Destroy,
	.setInterrupts = CSMI_SetInterrupts,
	.getInterrupts = CSMI_GetInterrupts,
	.setDataPortInterrupts = CSMI_SetDataPortInterrupts,
	.getDataPortInterrupts = CSMI_GetDataPortInterrupts,
	.clearDataPortFifo = CSMI_ClearDataPortFifo,
	.setPresenceRateGeneration = CSMI_SetPresenceRateGeneration,
	.getPresenceRateGeneration = CSMI_GetPresenceRateGeneration,
	.assignMessageCallbacks = CSMI_AssignMessageCallbacks,
	.sendRawMessage = CSMI_SendRawMessage,
	.sendMessage = CSMI_SendMessage,
	.getRegisterValue = CSMI_GetRegisterValue,
	.setRegisterValue = CSMI_SetRegisterValue,
	.setMessageChannelLapse = CSMI_SetMessageChannelLapse,
	.getMessageChannelLapse = CSMI_GetMessageChannelLapse,
	.getMessageChannelUsage = CSMI_GetMessageChannelUsage,
	.getMessageChannelCapacity = CSMI_GetMessageChannelCapacity,
	.setSnifferMode = CSMI_SetSnifferMode,
	.getSnifferMode = CSMI_GetSnifferMode,
	.setFramerEnabled = CSMI_SetFramerEnabled,
	.getFramerEnabled = CSMI_GetFramerEnabled,
	.setDeviceEnabled = CSMI_SetDeviceEnabled,
	.getDeviceEnabled = CSMI_GetDeviceEnabled,
	.setGoAbsent = CSMI_SetGoAbsent,
	.getGoAbsent = CSMI_GetGoAbsent,
	.setFramerConfig = CSMI_SetFramerConfig,
	.getFramerConfig = CSMI_GetFramerConfig,
	.setGenericDeviceConfig = CSMI_SetGenericDeviceConfig,
	.getGenericDeviceConfig = CSMI_GetGenericDeviceConfig,
	.unfreeze = CSMI_Unfreeze,
	.cancelConfiguration = CSMI_CancelConfiguration,
	.getStatusSynchronization = CSMI_GetStatusSynchronization,
	.getStatusDetached = CSMI_GetStatusDetached,
	.getStatusSlimbus = CSMI_GetStatusSlimbus,
	.getDataPortStatus = CSMI_GetDataPortStatus,
	.msgAssignLogicalAddress = CSMI_MsgAssignLogicalAddress,
	.msgResetDevice = CSMI_MsgResetDevice,
	.msgChangeLogicalAddress = CSMI_MsgChangeLogicalAddress,
	.msgChangeArbitrationPriority = CSMI_MsgChangeArbitrationPriority,
	.msgRequestSelfAnnouncement = CSMI_MsgRequestSelfAnnouncement,
	.msgConnectSource = CSMI_MsgConnectSource,
	.msgConnectSink = CSMI_MsgConnectSink,
	.msgDisconnectPort = CSMI_MsgDisconnectPort,
	.msgChangeContent = CSMI_MsgChangeContent,
	.msgRequestInformation = CSMI_MsgRequestInformation,
	.msgRequestClearInformation = CSMI_MsgRequestClearInformation,
	.msgClearInformation = CSMI_MsgClearInformation,
	.msgBeginReconfiguration = CSMI_MsgBeginReconfiguration,
	.msgNextActiveFramer = CSMI_MsgNextActiveFramer,
	.msgNextSubframeMode = CSMI_MsgNextSubframeMode,
	.msgNextClockGear = CSMI_MsgNextClockGear,
	.msgNextRootFrequency = CSMI_MsgNextRootFrequency,
	.msgNextPauseClock = CSMI_MsgNextPauseClock,
	.msgNextResetBus = CSMI_MsgNextResetBus,
	.msgNextShutdownBus = CSMI_MsgNextShutdownBus,
	.msgNextDefineChannel = CSMI_MsgNextDefineChannel,
	.msgNextDefineContent = CSMI_MsgNextDefineContent,
	.msgNextActivateChannel = CSMI_MsgNextActivateChannel,
	.msgNextDeactivateChannel = CSMI_MsgNextDeactivateChannel,
	.msgNextRemoveChannel = CSMI_MsgNextRemoveChannel,
	.msgReconfigureNow = CSMI_MsgReconfigureNow,
	.msgRequestValue = CSMI_MsgRequestValue,
	.msgRequestChangeValue = CSMI_MsgRequestChangeValue,
	.msgChangeValue = CSMI_MsgChangeValue,
};

CSMI_OBJ *CSMI_GetInstance(void) {
	return &driver;
}

