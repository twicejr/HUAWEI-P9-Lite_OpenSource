/*
 *	slimbus is a kernel driver which is used to manager SLIMbus devices
 *	Copyright (C) 2014	Hisilicon

 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.

 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.

 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/mutex.h>
#include <linux/delay.h>
#include <linux/completion.h>
#include <linux/workqueue.h>
#include <linux/wakelock.h>

#include "slimbus_drv.h"
#include <hisi/hilog.h>
#include <dsm/dsm_pub.h>

#define RFC_MAX_DEVICES 						 32
#define SOC_DEVICE_NUM							 3
#define HI6402_DEVICE_NUM						 3
#define ENUMERATION_TIMES						 400

/* used for element RD/WR protection*/
struct mutex	slimbus_mutex;
spinlock_t		slimbus_spinlock;

/*
 * List of enumerated devices
 */
typedef struct {
	uint8_t devices;
	uint8_t framerCount;
	uint8_t genericCount;
	uint8_t interfaceCount;
	uint8_t managerCount;
	uint8_t framerLa[RFC_MAX_DEVICES];
	uint8_t genericLa[RFC_MAX_DEVICES];
	uint8_t interfaceLa[RFC_MAX_DEVICES];
	uint8_t managerLa[RFC_MAX_DEVICES];
} RFC_EnumeratedDevices;

/*
 * Requested Values and Information Slices
 */
typedef struct {
	uint8_t* ptr;
	uint8_t size;
	uint8_t transactionId;
	bool received;
	bool valueRequested;
	bool informationRequested;
	bool error;
	struct completion read_finish;
	struct completion request_finish;
} RFC_InternalReply;

/*
 * Variables set by interrupts, used for reporting results
 */
typedef struct {
	bool ieUnsupportedMsg;
	bool ieExError;
	bool ieReconfigObjection;
	uint8_t reportedPresence;
	uint8_t reportedAbsence;
} RFC_SlimbusEvents;

/*
 * Global Variables
 */

/* Pointer to driver object */
static CSMI_OBJ *csmiDrv;
static void 	*devm_slimbus_priv;

static RFC_EnumeratedDevices		slimbusDevices;
static RFC_InternalReply	internalReply;
static RFC_SlimbusEvents	events;
volatile uint32_t					lostms_times = 0;
volatile uint32_t					slimbus_drv_log_count = 50;
int slimbus_irq_state = 0;
volatile bool int_need_clear = false;

/* 2us */
#define REG_ACCESS_TIME_DIFF 2
static int64_t last_time = 0;
static uint32_t dsm_notify_limit = 1;
static uintptr_t asp_base_reg;
static platform_type_t plat_type = PLATFORM_PHONE;
static struct workqueue_struct *slimbus_lost_sync_wq = NULL;
static struct delayed_work slimbus_lost_sync_delay_work;
static struct wake_lock slimbus_wake_lock;

static void slimbus_dump_state(slimbus_dump_state_t type);

volatile uint32_t slimbus_drv_lostms_get(void)
{
	return lostms_times;
}
EXPORT_SYMBOL(slimbus_drv_lostms_get);

void slimbus_drv_lostms_set(uint32_t count)
{
	lostms_times = count;
}
EXPORT_SYMBOL(slimbus_drv_lostms_set);

volatile bool slimbus_int_need_clear_get(void)
{
	return int_need_clear;
}
EXPORT_SYMBOL(slimbus_int_need_clear_get);

void slimbus_int_need_clear_set(volatile bool flag)
{
	int_need_clear = flag;
}
EXPORT_SYMBOL(slimbus_int_need_clear_set);

static int64_t get_timeus(void)
{
	struct timeval time;
	int64_t timeus = 0;

	do_gettimeofday(&time);
	timeus = 1000000 * time.tv_sec + time.tv_usec;

	return timeus;
}

/*
 * Interrupts Handler
 * When interrupt from SLIMbus Manager was received,
 * isr() function should be called.
 */
static irqreturn_t RFC_IrqHandler(uint32_t value, void * data)
{
	/* Process interrupt by the driver */

	csmiDrv->isr(devm_slimbus_priv);

	return IRQ_HANDLED;
}

static void RFC_ClearEvents(void)
{
	events.ieExError = 0;
	events.ieReconfigObjection = 0;
	events.ieUnsupportedMsg = 0;
	events.reportedPresence = 0;
	events.reportedAbsence = 0;
}

static void RFC_PrintIeStatus(CSMI_InformationElements *ie)
{
	if (ie->coreUnsprtdMsg || ie->coreDataTxCol || ie->coreReconfigObjection || ie->coreExError) {
		SLIMBUS_DEV_LIMIT_INFO("Core: UNSPRTD_MSG:%X DATA_TX_COL:%X RECONFIG_OBJECTION:%X EX_ERROR:%X \n",
			ie->coreUnsprtdMsg, ie->coreDataTxCol, ie->coreReconfigObjection, ie->coreExError);
	}
	if (ie->interfaceMcTxCol || ie->interfaceLostFs || ie->interfaceLostSfs || ie->interfaceLostMs || ie->interfaceDataSlotOverlap) {
		SLIMBUS_DEV_LIMIT_INFO("Interface: MC_TX_COL:%X LOST_FS:%X LOST_SFS:%X LOST_MS:%X DATA_SLOT_OVERLAP:%X\n",
			ie->interfaceMcTxCol, ie->interfaceLostFs, ie->interfaceLostSfs, ie->interfaceLostMs, ie->interfaceDataSlotOverlap);
	}
	if (ie->managerActiveManager) {
		SLIMBUS_DEV_LIMIT_INFO("Manager: ACTIVE_MANAGER:%X\n", ie->managerActiveManager);
	}
	if (ie->framerQuality || ie->framerGcTxCol || ie->framerFiTxCol || ie->framerFsTxCol || ie->framerActiveFramer) {
		SLIMBUS_DEV_LIMIT_INFO("Framer: QUALITY:%X GC_TX_COL:%X FI_TX_COL:%X FS_TX_COL:%X ACTIVE_FRAMER:%X\n",
			ie->framerQuality, ie->framerGcTxCol, ie->framerFiTxCol, ie->framerFsTxCol, ie->framerActiveFramer);
	}

	if (ie->interfaceLostFs || ie->interfaceLostSfs || ie->interfaceLostMs) {
		if (dsm_notify_limit == SLIMBUS_LOSTMS_COUNT) {
			slimbus_dump_state(SLIMBUS_DUMP_LOSTMS);
			if (!dsm_client_ocuppy(dsm_audio_client)) {
				dsm_client_record(dsm_audio_client, "DSM_HI6402_SLIMBUS_LOST_MS\n");
				dsm_client_notify(dsm_audio_client, DSM_HI6402_SLIMBUS_LOST_MS);
			}
		}
		dsm_notify_limit++;
	}
}

/***********************************************************************************************
 * Event Handlers
 ***********************************************************************************************/

/**
 * Handler for Device Class driver request
 * @param[in] logicalAddress Device's Logical Address
 * @return Device Class
 */
static CSMI_DeviceClass CLBK_DeviceClassHandler(uint8_t logicalAddress)
{
	uint8_t i;

	/* Active Manager always has 0xFF as logical address */
	if (logicalAddress == 0xFF)
		return CSMI_DC_MANAGER;


	/* Loop through list of enumerated Framer devices */
	for (i = 0; i < slimbusDevices.framerCount; i++) {
		if (logicalAddress == slimbusDevices.framerLa[i])
			return CSMI_DC_FRAMER;
	}
	/* Loop through list of enumerated Generic devices */
	for (i = 0; i < slimbusDevices.genericCount; i++) {
		if (logicalAddress == slimbusDevices.genericLa[i])
			return CSMI_DC_GENERIC;
	}

	/* Loop through list of enumerated Interface devices */
	for (i = 0; i < slimbusDevices.interfaceCount; i++) {
		if (logicalAddress == slimbusDevices.interfaceLa[i])
			return CSMI_DC_INTERFACE;
	}
	/* Loop through list of enumerated Generic devices
	 * Not needed in most cases.
	 * Usually there is only one manager in the system
	 * and it's active, so always has 0xFF as logical address */
	for (i = 0; i < slimbusDevices.managerCount; i++) {
		if (logicalAddress == slimbusDevices.managerLa[i])
			return CSMI_DC_MANAGER;
	}

	return CSMI_DC_INTERFACE;
}


/**
 * Handler for Logical Address for device driver request
 * Will be called for each device which sent REPORT_PRESENCE Message, if enumerateDevices was enabled.
 * @param[in] enumerationAddress Device's Enumeration Address
 * @param[in] class Device Class
 * @return Logical Address
 */
static uint8_t CLBK_AssignLogicalAddressHandler(uint64_t enumerationAddress, CSMI_DeviceClass class)
{

	/*
	 * Valid Logical Addresses are in range 0x00 - 0xEF.
	 * Logical Addresses 0xF[0-E] are reserved.
	 * 0xFF = active Manager
	 * If invalid value is returned, it will be ignored by the driver, and device will not be enumerated.
	 */
	uint8_t logicalAddress = 0xF0;

	switch (class) {
	/* New logical address with offset 0x00 */
	case CSMI_DC_FRAMER:
		logicalAddress = 0x20 + slimbusDevices.framerCount;
		slimbusDevices.framerLa[slimbusDevices.framerCount++] = logicalAddress;
		break;

	/* New logical address with offset 0x40 */
	case CSMI_DC_INTERFACE:
		logicalAddress = 0x40 | slimbusDevices.interfaceCount;
		slimbusDevices.interfaceLa[slimbusDevices.interfaceCount++] = logicalAddress;
		break;

	case CSMI_DC_GENERIC:
		 /*
				* Use Enumeration Addresses to assign always the same logical addresses for known devices,
				* regardless of the presence report order
				*/
		switch (enumerationAddress) {
		/*Device 1 Generic Device, example Enumeration Address, Change might be needed*/
		case SOC_EA_GENERIC_DEVICE:
			logicalAddress = SOC_LA_GENERIC_DEVICE;
			break;

		/* Device 2 Generic Device, example Enumeration Address, Change might be needed */
		case HI6402_EA_GENERIC_DEVICE:
		case (HI6402_EA_GENERIC_DEVICE & 0xfffffffffffe):
			logicalAddress = HI6402_LA_GENERIC_DEVICE;
			break;

		/* Unknown Generic Device, New logical address with offset 0x80 */
		default:
			logicalAddress = 0x80 | slimbusDevices.genericCount;
			break;
		}
		slimbusDevices.genericLa[slimbusDevices.genericCount++] = logicalAddress;
		break;

	/*
		* In most cases not needed.
		 * If there is one manager in the system, it will be active, and always have 0xFF as logical address.
		 * Active Managers don't need enumeration
		 */
	case CSMI_DC_MANAGER:
		/* New logical address with offset 0xE0 */
		logicalAddress = 0xE0 | slimbusDevices.managerCount;
		slimbusDevices.managerLa[slimbusDevices.managerCount++] = logicalAddress;
		break;

	/* Unknown device class code. Don't assign logical address (Invalid values (0xF[0-F]) are ignored by the driver). */
	default:
		return 0xF0;
	}

	slimbusDevices.devices++;

	//pr_info("[%s:%d], class:%x, EA:%llx, LA:%x, !\n", __FUNCTION__, __LINE__,
	//	  class, enumerationAddress, logicalAddress);

	return logicalAddress;
}


/**
 * Handler for Receiving Message
 * Will be called for message that was received by Manager.
 * @param[in] pD driver's private data.
 * @param[in] message received message as structure
 */
static void CLBK_ReceivedMessageHandler(void* pD, struct CSMI_Message* message)
{
	/* todo: add function */
	slimbus_irq_state = 0x100 + message->messageCode;
}


/**
 * Handler for Sending Message
 * Will be called for message that will be send by Manager.
 * @param[in] pD driver's private data.
 * @param[in] message message to be sent as structure
 */
static void CLBK_SendingMessageHandler(void* pD, struct CSMI_Message* message)
{
	/* todo: add function */
}

/**
 * Handler for Reported Information Element
 * Will be called for REPORT_INFORMATION message that was received by Manager.
 * @param[in] pD driver's private data.
 * @param[in] sourceLa source device's Logical Address
 * @param[in] informationElements Structure with decoded information elements
 */
static void CLBK_InformationElementsHandler(void* pD, uint8_t sourceLa, struct CSMI_InformationElements* informationElements)
{
	CSMI_DeviceClass deviceClass = CLBK_DeviceClassHandler(sourceLa);

	switch (deviceClass) {
	case CSMI_DC_MANAGER:
		SLIMBUS_DEV_LIMIT_INFO("- Source Device Class:Manager, Source Logic Address: %02X\n", sourceLa);
		break;
	case CSMI_DC_GENERIC:
		SLIMBUS_DEV_LIMIT_INFO("- Source Device Class:Generic, Source Logic Address: %02X\n", sourceLa);
		break;
	case CSMI_DC_FRAMER:
		SLIMBUS_DEV_LIMIT_INFO("- Source Device Class:Framer, Source Logic Address: %02X\n", sourceLa);
		break;
	case CSMI_DC_INTERFACE:
		SLIMBUS_DEV_LIMIT_INFO("- Source Device Class:Interface, Source Logic Address: %02X\n", sourceLa);
		break;
	default:
		break;
	}
	RFC_PrintIeStatus(informationElements);

	/* If value or information was requested but it resulted in error, set variables here */
	if ((internalReply.valueRequested) || (internalReply.informationRequested)) {
		if ((informationElements->coreUnsprtdMsg) || (informationElements->coreExError)) {
			internalReply.error = 1;
			internalReply.valueRequested = 0;
			internalReply.informationRequested = 0;
		}
	}

	if (informationElements->coreExError)
		events.ieExError = 1;
	if (informationElements->coreUnsprtdMsg)
		events.ieUnsupportedMsg = 1;
	if (informationElements->coreReconfigObjection)
		events.ieReconfigObjection = 1;
}

/**
 * Handler for REPLY_VALUE Messages
 * @param[in] pD driver's private data
 * @param[in] sourceLa source device's Logical Address
 * @param[in] transactionId Transaction ID
 * @param[in] valueSlice pointer to received Value data
 * @param[in] valueSliceLength size of received Value
 */
static void CLBK_MsgReplyValue(void* pD, uint8_t sourceLa, uint8_t transactionId, uint8_t* valueSlice, uint8_t valueSliceLength)
{

	/*
	 * If Value was requested and its transaction ID is equal to received reply,
	 * then copy its value to internal structure
	 */
	if (internalReply.valueRequested) {
		if (internalReply.transactionId == transactionId) {
			memcpy((void*) internalReply.ptr, (void*) valueSlice, valueSliceLength);
			internalReply.received = 1;
			internalReply.valueRequested = 0;
			slimbus_irq_state = 3;
			complete(&(internalReply.read_finish));
		} else {
			pr_err("[%s:%d] transactionId error! (%#x %#x)\n", __FUNCTION__, __LINE__, internalReply.transactionId, transactionId);
		}
	} else {
		pr_err("[%s:%d] replyvalue error!\n", __FUNCTION__, __LINE__);
	}
}

/**
 * Handler for REPORT_PRESENCE Messages
 * @param[in] pD driver's private data
 * @param[in] sourceEa source device's Enumeration Address
 * @param[in] deviceClass source device's Device Class
 * @param[in] deviceClassVersion source device's Device Class Version
 */
static void CLBK_MsgReportPresentHandler(void* pD, uint64_t sourceEa, CSMI_DeviceClass deviceClass, uint8_t deviceClassVersion)
{
	events.reportedPresence++;
}


/**
 * Handler for REPORT_ABSENT Messages
 * @param[in] pD driver's private data
 * @param[in] sourceLa source device's Logical Address
 */
static void CLBK_MsgReportAbsentHandler(void* pD, uint8_t sourceLa)
{
	events.reportedAbsence++;
}


/**
 * Handler for REPORT_INFORMATION Messages
 * @param[in] pD driver's private data
 * @param[in] sourceLa source device's Logical Address
 * @param[in] elementCode Element Code
 * @param[in] informationSlice pointer to reported Information Slice
 * @param[in] informationSliceLength reported Information Slice size
 */
static void CLBK_MsgReportInformationHandler(void* pD, uint8_t sourceLa, uint16_t elementCode, uint8_t* informationSlice, uint8_t informationSliceLength)
{
	/* todo: add function */
}

/**
 * Handler for REPLY_INFORMATION Messages
 * @param[in] pD driver's private data
 * @param[in] sourceLa source device's Logical Address
 * @param[in] transactionId Transaction ID
 * @param[in] informationSlice pointer to reported Information Slice
 * @param[in] informationSliceLength reported Information Slice size
 */
static void CLBK_MsgReplyInformationHandler(void* pD, uint8_t sourceLa, uint8_t transactionId, uint8_t* informationSlice, uint8_t informationSliceLength)
{

	/*
	 * If Information was requested and its transaction ID is equal to received reply,
	 * then copy its value to internal structure
	 */
	if (internalReply.informationRequested) {
		if (internalReply.transactionId == transactionId) {
			memcpy((void*) internalReply.ptr, (void*) informationSlice, informationSliceLength);
			internalReply.received = 1;
			internalReply.informationRequested = 0;
			slimbus_irq_state = 4;
			complete(&(internalReply.request_finish));
		} else {
			pr_err("[%s:%d] transactionId error! (%#x %#x)\n", __FUNCTION__, __LINE__, internalReply.transactionId, transactionId);
		}
	} else {
		pr_err("[%s:%d] ReplyInformation error!\n", __FUNCTION__, __LINE__);
	}
}

static void slimbus_lost_sync_cb(struct work_struct *work)
{
	bool fSync = false;
	bool sfSync = false;
	bool mSync = false;
	bool sfbSync = false;
	bool phSync = false;
	uint32_t ret = 0;
	uint32_t wait_timeout = 0;

	while ((!fSync | !sfSync | !mSync) && (wait_timeout++ < 100)) {
		ret = csmiDrv->getStatusSynchronization(devm_slimbus_priv, &fSync, &sfSync, &mSync, &sfbSync, &phSync);
		if (ret) {
			SLIMBUS_DEV_LIMIT_ERR("get sync status error\n");
		}
		usleep_range(300, 350);
	}

	if (fSync & sfSync & mSync) {
		ret = slimbus_track_recover();
		if (ret) {
			SLIMBUS_DEV_LIMIT_ERR(" track recover failed\n");
		}
		SLIMBUS_DEV_LOSTMS_RECOVER("wait_timeout:%d, fSync:%x, sfSync:%x, mSync:%x, sfbSync:%x, phSync:%x\n", wait_timeout, fSync, sfSync, mSync, sfbSync, phSync);
	} else {
		SLIMBUS_DEV_LIMIT_ERR("recover failed! wait_timeout:%d \n", wait_timeout);
	}

}

static void CLBK_ManagerInterruptsHandler(void* pD, CSMI_Interrupt interrupt)
{
	struct task_struct *slimbus_thread;
	uint32_t ret;

	if (interrupt & CSMI_INT_SYNC_LOST) {

		SLIMBUS_DEV_LIMIT_ERR("LOST SYNC, interrupt:%#x \n", interrupt);
		wake_lock_timeout(&slimbus_wake_lock, msecs_to_jiffies(1000));
		queue_delayed_work(slimbus_lost_sync_wq, &slimbus_lost_sync_delay_work, msecs_to_jiffies(50));
	}
}

/**
 * Create Element Code
 * @param[in] address element address
 * @param[in] byteAccess 1 for byte access, 0 for element access
 * @param[in] sliceSize size of slice
 * @return Element Code
 */
static uint16_t RFC_CreateElementCode(uint16_t address, bool byteAccess, CSMI_SliceSize sliceSize)
{
	/*
	 * Element Code
	 * 16 bit;
	 * [15: 4] element address
	 * [ 3: 3] access type (1 - byte based, 0 - elemental)
	 * [ 2: 0] value slice size
	 */
	return (address << 4) | (byteAccess << 3) | (sliceSize);
}

static uint32_t RFC_CheckEvent(void)
{
	uint32_t ret = 0;

	if (events.ieExError)  {
		pr_err("Bus Reconfiguration failed, one or more devices reported Execution Error.");
		ret = EIO;
	}
	if (events.ieUnsupportedMsg)  {
		pr_err("Bus Reconfiguration failed, one or more devices reported Unsupported Message.");
		ret = EIO;
	}
	if (events.ieReconfigObjection)  {
		pr_err("Bus Reconfiguration failed, one or more devices reported Reconfig Objection.");
		ret = EIO;
	}

	return ret;
}

/*
 * Event handlers
 * If handler is not used it should have NULL assigned to its pointer.
 */
static struct CSMI_Callbacks event_callbacks = {
	.onAssignLogicalAddress 		= CLBK_AssignLogicalAddressHandler,
	.onDeviceClassRequest			= CLBK_DeviceClassHandler,
	.onMessageReceived				= CLBK_ReceivedMessageHandler,
	.onMessageSending				= CLBK_SendingMessageHandler,
	.onInformationElementReported	= CLBK_InformationElementsHandler,
	.onDataPortInterrupt			= NULL,
	.onManagerInterrupt 			= CLBK_ManagerInterruptsHandler,
	.onRawMessageReceived			= NULL,
	.onRawMessageSending			= NULL,
};

/*
 * Message handlers
 * If handler is not used it should have NULL assigned to its pointer.
 * Each handler corresponds with one Message that can be received by manager.
 * These handlers can be changed at any time via assignMessageHandlers function.
 */
static struct CSMI_MessageCallbacks message_callbacks = {
	.onMsgReportPresent 			= CLBK_MsgReportPresentHandler,
	.onMsgReportAbsent				= CLBK_MsgReportAbsentHandler,
	.onMsgReplyInformation			= CLBK_MsgReplyInformationHandler,
	.onMsgReportInformation 		= CLBK_MsgReportInformationHandler,
	.onMsgReplyValue				= CLBK_MsgReplyValue,
};

/*
 * General configuration
 */
static CSMI_Config general_cfg = {
	.regBase						= 0x0,
	.eaInstanceValue				= 0x00,
	.eaProductId					= 0xC100,
	.eaInterfaceId					= 0x00,
	.eaFramerId 					= 0x01,
	.eaGenericId					= 0x02,
	.enumerateDevices				= 1,
	.enableDevice					= 1,
	.enableFramer					= 1,
	.disableHardwareCrcCalculation	= 0,
	.snifferMode					= 0,
	.retryLimit 					= 4,
	.limitReports					= 0,
	.reportAtEvent					= 0,
};

/*
 * Framer in Manager component configuration
 * If cfg.enableFramer was set to 0, this configuration may be skipped.
 * If cfg.enableFramer was set to 1 and configuration was skipped, then
 * IP's default values will be used.
 */
static CSMI_FramerConfig framer_cfg = {
	.rootFrequenciesSupported		= 0xFFFF,
	.quality						= CSMI_FQ_LOW_JITTER,
	.pauseAtRootFrequencyChange 	= 0,
};

/*
 * Generic Device in Manager component configuration
 * If cfg.enableDevice was set to 0, this configuration may be skipped
 * If cfg.enableDevice was set to 1 and configuration was skipped, then
 * IP's default values will be used.
 */
static CSMI_GenericDeviceConfig device_cfg = {
	.presenceRatesSupported 		= 0xFFFFFF,
	.referenceClockSelector 		= CSMI_RC_CLOCK_GEAR_6,
	.transportProtocolIsochronous	= 1,
	.transportProtocolPushed		= 1,
	.transportProtocolPulled		= 1,
	.dataPortClockPrescaler 		= 2,
	.cportClockDivider				= 0,
	.dmaTresholdSink				= 0x10,
	.dmaTresholdSource				= 0x10,
	.sinkStartLevel 				= 0,
};

int slimbus_dev_init(platform_type_t platform_type)
{
	int ret = 0;
	int wait_times = 0;
	uint32_t slimbus_dev_num = SOC_DEVICE_NUM;
	static uint32_t first_init = 0;

	mutex_lock(&slimbus_mutex);
	lostms_times = 0;

	RFC_ClearEvents();
	memset(&slimbusDevices, 0, sizeof(RFC_EnumeratedDevices));

	/* Initialize the driver and hardware */
	ret = csmiDrv->init(devm_slimbus_priv, &general_cfg, &event_callbacks);
	if (ret) {
		pr_err("Init function failed with result: %d \n", ret);
		goto exit;
	}

	/* Assign Message Handlers */
	ret = csmiDrv->assignMessageCallbacks(devm_slimbus_priv, &message_callbacks);
	if (ret) {
		pr_err("AssignMessageCallbacks function failed with result: %d \n", ret);
		goto exit;
	}

	/* Set Framer Configuration */
	ret = csmiDrv->setFramerConfig(devm_slimbus_priv, &framer_cfg);
	if (ret) {
		pr_err("SetFramerConfig function failed with result: %d \n", ret);
		goto exit;
	}

	/* Set Generic Device Configuration */
	ret = csmiDrv->setGenericDeviceConfig(devm_slimbus_priv, &device_cfg);
	if (ret) {
		pr_err("SetGenericDeviceConfig function failed with result: %d \n", ret);
		goto exit;
	}

	/* Start the Driver and enable Manager and its interrupts */
	ret = csmiDrv->start(devm_slimbus_priv);
	if (ret) {
		pr_err("Start function failed with result: %d \n", ret);
		goto exit;
	}

	first_init++;
	int_need_clear = false;

	/*
	 * Wait some time.
	 * SLIMBus works asynchronically to the application.
	 * During this delay devices will be enumerated using interrupts and handlers.
	 */

	/* Print number of devices which sent REPORT_PRESENCR message */
	if (platform_type == PLATFORM_PHONE)
		slimbus_dev_num = SOC_DEVICE_NUM + HI6402_DEVICE_NUM - ((first_init == 1) ? 1 : 0);

	while ((slimbusDevices.devices < slimbus_dev_num) && (wait_times < ENUMERATION_TIMES)) {
		/* enumeration need 4ms normally, wait 40ms here is enough */
		usleep_range(100, 150);
		wait_times++;
	}

	pr_info("platype:%d, Discovered devices: %d, enumerated devices: %d!\n", platform_type, events.reportedPresence, slimbusDevices.devices);

	mutex_unlock(&slimbus_mutex);

	if ((slimbusDevices.devices <= SOC_DEVICE_NUM) && (slimbus_dev_num > SOC_DEVICE_NUM)) {
		slimbus_drv_reset_bus();
		/* wait for bus reset until device enumerated */
		wait_times = 0;
		while ((slimbusDevices.devices < slimbus_dev_num) && (wait_times < ENUMERATION_TIMES)) {
			/* enumeration need 4ms normally, wait 40ms here is enough */
			usleep_range(100, 150);
			wait_times++;
		}

		pr_info("After busreset, Discovered devices: %d, enumerated devices: %d!\n", events.reportedPresence, slimbusDevices.devices);
		if (ENUMERATION_TIMES == wait_times) {
			pr_err("retry fail, and phone will mute.\n");
		}
	}
	SLIMBUS_DEV_LOSTMS_RECOVER("slimbus init\n");

	return ret;
exit:
	slimbus_dump_state(SLIMBUS_DUMP_LOSTMS);
	mutex_unlock(&slimbus_mutex);
	return ret;
}

int slimbus_drv_init(platform_type_t platform_type, void *slimbus_reg, void *asp_reg, int irq)
{
	int ret = 0;
	uint16_t slimbus_priv_obj_size = 0;

	mutex_init(&slimbus_mutex);
	spin_lock_init(&slimbus_spinlock);
	init_completion(&(internalReply.read_finish));
	init_completion(&(internalReply.request_finish));
	wake_lock_init(&slimbus_wake_lock, WAKE_LOCK_SUSPEND, "slimbus_wake_lock");

	general_cfg.regBase = (uintptr_t)slimbus_reg;
	asp_base_reg = (uintptr_t)asp_reg;
	plat_type = platform_type;

	/* Get API function pointers for this Driver instance */
	csmiDrv = CSMI_GetInstance();

	/* Probe driver for required memory */
	ret = csmiDrv->probe(&general_cfg, &slimbus_priv_obj_size);
	if (ret) {
		pr_err("Probe function failed with result: %d \n", ret);
		goto exit;
	}

	if (0 == slimbus_priv_obj_size) {
		pr_err("slimbus prve obj size is zero\n");
		ret = -ENOMEM;
		goto exit;
	}

	/* Allocation of memory required by the driver */
	devm_slimbus_priv = kmalloc(slimbus_priv_obj_size, GFP_KERNEL);
	if (!devm_slimbus_priv) {
		pr_err("malloc private data failed!\n");
		ret = -ENOMEM;
		goto exit;
	}

	/* Enable SLIMbus interrupt */
	ret = request_irq(
					irq,
					(void *)RFC_IrqHandler,
					IRQF_TRIGGER_HIGH | IRQF_SHARED | IRQF_NO_SUSPEND,
					"asp_irq_slimbus",
					devm_slimbus_priv);

	if (ret < 0) {
		pr_err("could not claim irq %d\n", ret);
		HiLOGE("audio", "Slimbus_drv", "could not claim irq %d\n", ret);
		ret = -ENODEV;
		goto request_irq_failed;
	}

	ret = slimbus_dev_init(platform_type);
	if (ret) {
		ret = -ENODEV;
		goto dev_init_failed;
	}

	slimbus_lost_sync_wq = create_singlethread_workqueue("slimbus_lost_sync_wq");
	if (!slimbus_lost_sync_wq) {
		pr_err("work queue create failed\n");
		goto request_irq_failed;
	}
	INIT_DELAYED_WORK(&slimbus_lost_sync_delay_work, slimbus_lost_sync_cb);

	return 0;

dev_init_failed:
	free_irq(irq, devm_slimbus_priv);
request_irq_failed:
	kfree(devm_slimbus_priv);
	devm_slimbus_priv = NULL;
exit:
	mutex_destroy(&slimbus_mutex);
	wake_lock_destroy(&slimbus_wake_lock);

	return ret;
}

int slimbus_drv_stop(void)
{
	int result = 0;

	mutex_lock(&slimbus_mutex);

	result = csmiDrv->stop(devm_slimbus_priv);
	if (result != 0) {
		pr_err("SLIMbus stop failed with result: %d \n", result);
	}

	mutex_unlock(&slimbus_mutex);
	return result;
}

int slimbus_drv_release(int irq)
{
	free_irq(irq, devm_slimbus_priv);
	mutex_destroy(&slimbus_mutex);
	wake_lock_destroy(&slimbus_wake_lock);
	if(slimbus_lost_sync_wq) {
		cancel_delayed_work(&slimbus_lost_sync_delay_work);
		flush_workqueue(slimbus_lost_sync_wq);
		destroy_workqueue(slimbus_lost_sync_wq);
	}
	if (devm_slimbus_priv != NULL) {
		kfree(devm_slimbus_priv);
		devm_slimbus_priv = NULL;
	}

	return 0;
}

int slimbus_drv_bus_configure(slimbus_bus_config_t *bus_config)
{
	int 				ret 	= 0;
	CSMI_SubframeMode	sm;
	CSMI_RootFrequency	rf;
	CSMI_ClockGear		cg;

	mutex_lock(&slimbus_mutex);

	RFC_ClearEvents();

	/* configure bus */
	ret += csmiDrv->msgBeginReconfiguration(devm_slimbus_priv);
	ret += csmiDrv->msgNextClockGear(devm_slimbus_priv, bus_config->cg);
	ret += csmiDrv->msgNextSubframeMode(devm_slimbus_priv, bus_config->sm);
	ret += csmiDrv->msgReconfigureNow(devm_slimbus_priv);
	if (ret) {
		pr_err("Bus reconfiguration failed with error: %d\n", ret);
		HiLOGE("audio", "Slimbus_drv", "Bus reconfiguration failed with error: %d\n", ret);
		goto exit;
	}

	/* wait for param update */
	if (plat_type == PLATFORM_FPGA) {
		usleep_range(10000, 10050);
	} else {
		usleep_range(1000, 1050);
	}

	csmiDrv->getStatusSlimbus(devm_slimbus_priv, &sm, &cg, &rf);

	if ((sm != (CSMI_SubframeMode)bus_config->sm)
		|| (rf != (CSMI_RootFrequency)bus_config->rf)
		|| (cg != (CSMI_ClockGear)bus_config->cg)) {
		pr_err("Bus Reconfiguration failed, ret=%d!\n", ret);
		ret = EINVAL;
	}

exit:
	mutex_unlock(&slimbus_mutex);

	return ret;
}

int slimbus_drv_request_info(uint8_t  targetLa, uint16_t address, slimbus_slice_size_t sliceSize, void *valueRead)
{
	int ret = 0;
	uint16_t elementCode = 0;

	mutex_lock(&slimbus_mutex);

	internalReply.received = 0;
	internalReply.transactionId += 1;
	internalReply.ptr = valueRead;
	internalReply.informationRequested = 1;

	INIT_COMPLETION(internalReply.request_finish);

	/* create element code set byte address mode*/
	elementCode = RFC_CreateElementCode(address, 1, (CSMI_SliceSize)sliceSize);

	RFC_ClearEvents();
	mb();
	ret = csmiDrv->msgRequestInformation(devm_slimbus_priv, 0, targetLa, internalReply.transactionId, elementCode);
	if (ret) {
		SLIMBUS_DRV_LIMIT_ERR("Sending REQUEST_INFORMATION failed with ret: %d, ID:%#x !\n", ret, internalReply.transactionId);
		goto exit;
	}

	/* Wait for reply (received using callback) */
	if (wait_for_completion_timeout(&(internalReply.request_finish), msecs_to_jiffies(500)) == 0) {
		SLIMBUS_DRV_LIMIT_ERR("REQUEST_INFORMATION Message timeout: received:%#x ID:%#x slimbus_irq_state:%#x !\n",
			internalReply.received, internalReply.transactionId, slimbus_irq_state);
		ret = EIO;
		goto exit;
	}

	if (internalReply.error) {
		internalReply.error = 0;
		internalReply.informationRequested = 0;

		SLIMBUS_DRV_LIMIT_ERR("REQUEST_INFORMATION Message error\n");
		ret = EIO;
	}

exit:
	mutex_unlock(&slimbus_mutex);

	return ret;
}
EXPORT_SYMBOL(slimbus_drv_request_info);

#define GIC_BASE_ADDR	0xE82B0000
#define GIC_SIZE		0x7fff
static void slimbus_dump_state(slimbus_dump_state_t type)
{
	uint64_t gic_base_addr;
	uint32_t state[9] = {0};
	uint8_t  framersoc = 0;
	uint8_t  framercodec = 0;

	memset(state, 0, sizeof(state));

	if (plat_type == PLATFORM_FPGA) {
		SLIMBUS_DRV_LIMIT_ERR("fpga platform, don't dump register!\n");
		return;
	}

	switch (type) {
	case SLIMBUS_DUMP_IRQ:
		state[0] = readl((void __iomem *)(general_cfg.regBase + 0x3c));
		state[1] = readl((void __iomem *)(general_cfg.regBase + 0x24));
		gic_base_addr = (uint64_t)ioremap(GIC_BASE_ADDR, GIC_SIZE);
		if (!gic_base_addr) {
			pr_err("[%s:%d] ioremap failed! \n", __func__, __LINE__);
			return;
		}
		state[2] = readl((void __iomem *)(gic_base_addr + 0x1214));
		state[3] = readl((void __iomem *)(gic_base_addr + 0x1314));
		state[4] = readl((void __iomem *)(gic_base_addr + 0x1414));
		state[5] = readl((void __iomem *)(gic_base_addr + 0x2014));
		state[6] = readl((void __iomem *)(gic_base_addr + 0x2018));
		iounmap((void __iomem *)gic_base_addr);
		SLIMBUS_DRV_LIMIT_ERR("0x3c:%#x 0X24:%#x; gic:(%#x,%#x,%#x,%#x,%#x)!\n",
			state[0], state[1], state[2], state[3], state[4], state[5], state[6]);
		break;

	case SLIMBUS_DUMP_FRAMER:
		state[0] = readl((void __iomem *)(general_cfg.regBase + 0x28));
		slimbus_drv_request_info(0x20, 0x400, SLIMBUS_SS_1_BYTE, &framersoc);
		slimbus_drv_request_info(0x21, 0x400, SLIMBUS_SS_1_BYTE, &framercodec);
		pr_info("[%s:%d] 0x28:%#x, framer(0x20):%#x, framer(0x21):%#x !\n",
			__func__, __LINE__, state[0], framersoc, framercodec);
		break;

	case SLIMBUS_DUMP_LOSTMS:
		state[0] = readl((void __iomem *)(general_cfg.regBase + 0x0));
		state[1] = readl((void __iomem *)(general_cfg.regBase + 0x20));
		state[2] = readl((void __iomem *)(general_cfg.regBase + 0x24));
		state[3] = readl((void __iomem *)(general_cfg.regBase + 0x28));
		state[4] = readl((void __iomem *)(asp_base_reg + 0x8));
		state[5] = readl((void __iomem *)(asp_base_reg + 0x14));
		state[6] = readl((void __iomem *)(asp_base_reg + 0x18));
		state[7] = readl((void __iomem *)(asp_base_reg + 0x20));
		state[8] = readl((void __iomem *)(asp_base_reg + 0x38));

		SLIMBUS_DEV_LIMIT_INFO("0x0:%#x, 0x20:%#x, 0x24:%#x, 0x28:%#x\n", state[0], state[1], state[2], state[3]);
		SLIMBUS_DEV_LIMIT_INFO("0xe008:%#x, 0xe014:%#x, 0xe018:%#x, 0xe020:%#x, 0xe038:%#x;\n",
			state[4], state[5], state[6], state[7], state[8]);
		break;
	default:
		pr_err("[%s:%d] default! \n", __func__, __LINE__);
		break;
	}
}

/*
* Slimbus Element read
* @param[in] address 16 bits element address
* @param[in] slicesize size of slize
* @param[in] valueRead value of the address
* @return value of element address
*/
int slimbus_drv_element_read(uint8_t  targetLa, uint16_t address, slimbus_slice_size_t sliceSize, void *valueRead)
{
	int 	 ret = 0;
	uint16_t elementCode = 0;

	mutex_lock(&slimbus_mutex);

	/*lint -e666*/
	if (abs(get_timeus() - last_time) < REG_ACCESS_TIME_DIFF) {
		udelay(2);
	}
	/*lint +e666*/
	internalReply.received = 0;
	internalReply.transactionId += 1;
	internalReply.valueRequested = 1;
	internalReply.ptr = valueRead;
	slimbus_irq_state = 0;

	INIT_COMPLETION(internalReply.read_finish);

	/* create element code set byte address mode*/
	elementCode = RFC_CreateElementCode(address, 1, (CSMI_SliceSize)sliceSize);

	RFC_ClearEvents();
	mb();
	ret = csmiDrv->msgRequestValue(devm_slimbus_priv, 0, targetLa, internalReply.transactionId, elementCode);
	if (ret) {
		SLIMBUS_DRV_LIMIT_ERR("Sending REQUEST_VALUE failed with ret: %d ID:%#x slimbus_irq_state:%#x \n", ret, internalReply.transactionId, slimbus_irq_state);
		slimbus_dump_state(SLIMBUS_DUMP_IRQ);
		goto exit;
	}

	if (wait_for_completion_timeout(&(internalReply.read_finish), msecs_to_jiffies(500)) == 0) {
		SLIMBUS_DRV_LIMIT_ERR("REQUEST_VALUE Message timeout: received:%#x ID:%#x slimbus_irq_state:%#x !\n", internalReply.received, internalReply.transactionId, slimbus_irq_state);
		slimbus_dump_state(SLIMBUS_DUMP_IRQ);
		ret = EIO;
		goto exit;
	}

	if (internalReply.error) {
		internalReply.error = 0;
		internalReply.valueRequested = 0;

		SLIMBUS_DRV_LIMIT_ERR("REQUEST_VALUE Message error\n");
		ret = EIO;
	} else {
		SLIMBUS_DEV_LOSTMS_RECOVER("slimbus recover!\n");
	}

exit:
	last_time = get_timeus();
	mutex_unlock(&slimbus_mutex);

	return ret;
}

/*
* Slimbus Element write
* @param[in] address 16 bits element address
* @param[in] valueWrite value write to element address
* @param[in] slicesize size of slize
* @return
*/
int slimbus_drv_element_write(uint8_t  targetLa, uint16_t address, slimbus_slice_size_t sliceSize, void *valueWrite)
{
	int 	 ret = 0;
	uint16_t elementCode = 0;
	uint32_t valuesize[8] = {1,2,3,4,6,8,12,16};

	mutex_lock(&slimbus_mutex);

	/*lint -e666*/
	if (abs(get_timeus() - last_time) < REG_ACCESS_TIME_DIFF) {
		udelay(2);
	}
	/*lint +e666*/
	RFC_ClearEvents();

	elementCode = RFC_CreateElementCode(address, 1, (CSMI_SliceSize)sliceSize);

	ret = csmiDrv->msgChangeValue(devm_slimbus_priv, 0, targetLa, elementCode, (uint8_t *)valueWrite, valuesize[sliceSize]);
	if (ret) {
		SLIMBUS_DRV_LIMIT_ERR("Sending CHANGE_VALUE failed with ret: %d \n", ret);
	} else {
		SLIMBUS_DEV_LOSTMS_RECOVER("slimbus recover!\n");
	}

	last_time = get_timeus();

	mutex_unlock(&slimbus_mutex);

	return ret;
}

int slimbus_drv_track_configure(slimbus_channel_property_t *channel, uint32_t ch_num)
{
	int 	 ret = 0;
	uint32_t i		= 0;
	uint32_t j		= 0;

	mutex_lock(&slimbus_mutex);

	/* configure channels */
	RFC_ClearEvents();

	for (i=0; i < ch_num; i++) {
		/*Connecting Source to Data Channel */

		ret += csmiDrv->msgConnectSource(devm_slimbus_priv, channel[i].source.la, channel[i].source.pn, channel[i].cn);

		/* Connecting Sink(s) to Data Channel */
		for (j = 0; j < channel[i].sink_num; j++) {
			ret += csmiDrv->msgConnectSink(devm_slimbus_priv, channel[i].sinks[j].la, channel[i].sinks[j].pn, channel[i].cn);
		}
		if (ret) {
			pr_err("Connecting source or sink(s) failed.");
			HiLOGE("audio", "Slimbus_drv", "Connecting source or sink(s) failed.");
			goto exit;
		}
	}

	/* Configure and define Channels */
	ret = csmiDrv->msgBeginReconfiguration(devm_slimbus_priv);
	if (ret) {
		pr_err("Sending BEGIN_RECONFIGURATION failed with ret: %d \n", ret);
		goto exit;
	}

	for (i = 0; i < ch_num; i++) {
		/* Configuring Data Channel */
		ret += csmiDrv->msgNextDefineChannel(devm_slimbus_priv, channel[i].cn, channel[i].tp, channel[i].sd, channel[i].sl);
		ret += csmiDrv->msgNextDefineContent(devm_slimbus_priv, channel[i].cn, channel[i].fl, channel[i].pr, channel[i].af, channel[i].dt, channel[i].cl, channel[i].dl);

	}
	if (ret) {
		pr_err("Configuring and Activating Data Channels failed. ");
		HiLOGE("audio", "Slimbus_drv", "Configuring and Activating Data Channels failed. ");
		goto exit;
	}

	ret = csmiDrv->msgReconfigureNow(devm_slimbus_priv);
	if (ret) {
		pr_err("Sending RECONFIGURE_NOW failed with ret: %d \n", ret);
		goto exit;
	}

	if (RFC_CheckEvent()) {
		pr_err("Channel configuration failed!\n");
		HiLOGE("audio", "Slimbus_drv", "Channel configuration failed!\n");
	}

exit:
	mutex_unlock(&slimbus_mutex);
	return ret;
}

int slimbus_drv_track_activate(slimbus_channel_property_t *channel, uint32_t ch_num)
{
	int 	 ret = 0;
	uint32_t i		= 0;

	mutex_lock(&slimbus_mutex);
	RFC_ClearEvents();

	/* Configure and active Channels */
	ret = csmiDrv->msgBeginReconfiguration(devm_slimbus_priv);
	if (ret) {
		pr_err("Sending BEGIN_RECONFIGURATION failed with ret: %d \n", ret);
		goto exit;
	}

	for (i = 0; i < ch_num; i++) {
		/* Activating Data Channel */
		ret += csmiDrv->msgNextActivateChannel(devm_slimbus_priv, channel[i].cn);

		channel[i].active = 1;
	}
	if (ret) {
		pr_err("Activate channel failed! ret:%d !\n", ret);
		goto exit;
	}

	ret = csmiDrv->msgReconfigureNow(devm_slimbus_priv);
	if (ret) {
		pr_err("Sending RECONFIGURE_NOW failed with ret: %d \n", ret);
		goto exit;
	}

	ret = RFC_CheckEvent();
	if (ret) {
		pr_err("Channel activate failed!\n");
		goto exit;
	}

exit:
	mutex_unlock(&slimbus_mutex);
	return ret;
}

int slimbus_drv_track_deactivate(slimbus_channel_property_t *channel, uint32_t ch_num)
{
	int 	 ret = 0;
	uint32_t i		= 0;

	mutex_lock(&slimbus_mutex);

	RFC_ClearEvents();

	/* Configure and deactivate Channels */
	ret = csmiDrv->msgBeginReconfiguration(devm_slimbus_priv);
	if (ret) {
		pr_err("Sending BEGIN_RECONFIGURATION failed with ret: %d \n", ret);
		goto exit;
	}

	for (i = 0; i < ch_num; i++) {
		/* Deactivating Data Channel */
		ret += csmiDrv->msgNextDeactivateChannel(devm_slimbus_priv, channel[i].cn);

		channel[i].active = 0;
	}
	if (ret) {
		pr_err("Configuring and Deactivating Data Channels failed. ");
		HiLOGE("audio", "Slimbus_drv", "Configuring and Deactivating Data Channels failed. ");
		goto exit;
	}

	csmiDrv->msgReconfigureNow(devm_slimbus_priv);
	if (ret) {
		pr_err("Sending RECONFIGURE_NOW failed with ret: %d \n", ret);
		goto exit;
	}

	if (RFC_CheckEvent()) {
		pr_err("Channel Deactivate failed!\n");
	}

exit:
	mutex_unlock(&slimbus_mutex);

	return ret;
}


int slimbus_drv_track_remove(slimbus_channel_property_t *channel, uint32_t ch_num)
{
	int 	 ret = 0;
	uint32_t i		= 0;

	mutex_lock(&slimbus_mutex);

	RFC_ClearEvents();

	/* Configure and remove Channels */
	ret = csmiDrv->msgBeginReconfiguration(devm_slimbus_priv);
	if (ret) {
		pr_err("Sending BEGIN_RECONFIGURATION failed with ret: %d \n", ret);
		goto exit;
	}

	for (i = 0; i < ch_num; i++) {
		/* remove Data Channel */
		ret += csmiDrv->msgNextRemoveChannel(devm_slimbus_priv, channel[i].cn);
	}
	if (ret) {
		pr_err("Configuring and remove Data Channels failed. ");
		goto exit;
	}

	csmiDrv->msgReconfigureNow(devm_slimbus_priv);
	if (ret) {
		pr_err("Sending RECONFIGURE_NOW failed with ret: %d \n", ret);
		goto exit;
	}

	if (RFC_CheckEvent()) {
		pr_err("Channel removed failed!\n");
	}

exit:
	mutex_unlock(&slimbus_mutex);

	return ret;
}

int slimbus_drv_switch_framer(uint8_t  laif, uint16_t NCo, uint16_t NCi, slimbus_bus_config_t *bus_config)
{
	int ret 	= 0;
	static int8_t last_laif = 0;

	mutex_lock(&slimbus_mutex);

	if (laif != last_laif)	{

		pr_info("[%s:%d] la:0x%x, NCo:0x%x, NCi:0x%x cg:0x%x !\n", __FUNCTION__, __LINE__, laif, NCo, NCi, bus_config->cg);
		RFC_ClearEvents();
		ret += csmiDrv->msgBeginReconfiguration(devm_slimbus_priv);
		if (laif == slimbusDevices.framerLa[SLIMBUS_FRAMER_HI6402_ID]) {
			ret += csmiDrv->msgNextClockGear(devm_slimbus_priv, bus_config->cg);
		}
		ret += csmiDrv->msgNextActiveFramer(devm_slimbus_priv, laif, NCo, NCi);
		if (laif == slimbusDevices.framerLa[SLIMBUS_FRAMER_SOC_ID]) {
			ret += csmiDrv->msgNextClockGear(devm_slimbus_priv, bus_config->cg);
		}
		ret += csmiDrv->msgReconfigureNow(devm_slimbus_priv);
		if (ret) {
			pr_err("Bus switch framer failed with error: %d\n", ret);
			HiLOGE("audio", "Slimbus_drv", "Bus switch framer failed with error: %d\n", ret);
			goto exit;
		}

		/*param would be updated in one superframe, 250us*/
		usleep_range(500, 550);

		last_laif = laif;

	}else {
		pr_err("[%s:%d] switch to the same framer la:0x%x!\n", __FUNCTION__, __LINE__, laif);
	}

exit:
	mutex_unlock(&slimbus_mutex);

	slimbus_dump_state(SLIMBUS_DUMP_FRAMER);

	return ret;
}

int slimbus_drv_pause_clock(slimbus_restart_time_t newrestarttime)
{
	int ret 	= 0;

	mutex_lock(&slimbus_mutex);

	/* make sure boundary of pause_clock is clean */
	udelay(300);
	RFC_ClearEvents();
	ret += csmiDrv->msgBeginReconfiguration(devm_slimbus_priv);
	ret += csmiDrv->msgNextPauseClock(devm_slimbus_priv, newrestarttime);
	ret += csmiDrv->msgReconfigureNow(devm_slimbus_priv);
	if (ret) {
		pr_err("Bus switch framer failed with error: %d\n", ret);
	}

	udelay(300);

	mutex_unlock(&slimbus_mutex);

	return ret;
}

int slimbus_drv_resume_clock(void)
{
	int ret = 0;
	mutex_lock(&slimbus_mutex);

	ret = csmiDrv->unfreeze(devm_slimbus_priv);
	if (ret) {
		pr_err("unfreeze clock failed with error: %d\n", ret);
	}

	mutex_unlock(&slimbus_mutex);

	return ret;
}

int slimbus_drv_reset_bus(void)
{
	int ret 	= 0;

	mutex_lock(&slimbus_mutex);

	RFC_ClearEvents();

	memset(&slimbusDevices, 0, sizeof(RFC_EnumeratedDevices));

	ret += csmiDrv->msgBeginReconfiguration(devm_slimbus_priv);
	ret += csmiDrv->msgNextResetBus(devm_slimbus_priv);
	ret += csmiDrv->msgReconfigureNow(devm_slimbus_priv);
	if (ret) {
		pr_err("Reset bus failed with error: %d\n", ret);
		HiLOGE("audio", "Slimbus_drv", "Reset bus failed with error: %d\n", ret);
	}

	mutex_unlock(&slimbus_mutex);

	return ret;
}
EXPORT_SYMBOL(slimbus_drv_reset_bus);

int slimbus_drv_shutdown_bus(void)
{
	int ret 	= 0;

	mutex_lock(&slimbus_mutex);

	RFC_ClearEvents();

	ret += csmiDrv->msgBeginReconfiguration(devm_slimbus_priv);
	ret += csmiDrv->msgNextShutdownBus(devm_slimbus_priv);
	ret += csmiDrv->msgReconfigureNow(devm_slimbus_priv);
	if (ret) {
		pr_err("Shutdown bus failed with error: %d\n", ret);
	}

	mutex_unlock(&slimbus_mutex);

	return ret;
}

uint8_t slimbus_drv_get_framerla(int framer_id)
{
	uint8_t la = 0;

	if (framer_id < slimbusDevices.framerCount) {
		la = slimbusDevices.framerLa[framer_id];
	} else {
		if (slimbusDevices.framerCount > 0)
			la = slimbusDevices.framerLa[0];
		pr_err("[%s:%d] wrong framer_id ! framer_id is %d, framerCount is %d. la:%d \n", __FUNCTION__, __LINE__, framer_id, slimbusDevices.framerCount, la);
		dump_stack();
	}

	return la;
}

