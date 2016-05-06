/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.83
	GENERATOR: ed-c-recog
	http://www.Dafocus.it/
**************************************************************************/

#include "ed_c_recog.h"
#include "ed_lib.h"
#include "L3Downlink.h"
#include "L3Uplink.h"
#include "PLENDownlink.h"
#include "Downlink_RLC_MAC.h"
#include "Uplink_RLC_MAC.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_ED_C_RECOG_C
/*lint -e961*/
/*lint -e958*/
/*lint -e830*/
/*lint -e744*/
/*lint -e760*/


void SETPRESENT_TL3Downlink_Data (TL3Downlink_Data* sp, TL3Downlink_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TL3Downlink_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_L3Downlink_ASSIGNMENT_COMMAND: {
			INIT_c_ASSIGNMENT_COMMAND (&(sp->Data.fld_c_ASSIGNMENT_COMMAND));
			break;
		}
		
		case ID_L3Downlink_CHANNEL_MODE_MODIFY: {
			INIT_c_CHANNEL_MODE_MODIFY (&(sp->Data.fld_c_CHANNEL_MODE_MODIFY));
			break;
		}
		
		case ID_L3Downlink_CHANNEL_RELEASE: {
			INIT_c_CHANNEL_RELEASE (&(sp->Data.fld_c_CHANNEL_RELEASE));
			break;
		}
		
		case ID_L3Downlink_CIPHERING_MODE_COMMAND: {
			INIT_c_CIPHERING_MODE_COMMAND (&(sp->Data.fld_c_CIPHERING_MODE_COMMAND));
			break;
		}
		
		case ID_L3Downlink_CLASSMARK_ENQUIRY: {
			INIT_c_CLASSMARK_ENQUIRY (&(sp->Data.fld_c_CLASSMARK_ENQUIRY));
			break;
		}
		
		case ID_L3Downlink_FREQUENCY_REDEFINITION: {
			INIT_c_FREQUENCY_REDEFINITION (&(sp->Data.fld_c_FREQUENCY_REDEFINITION));
			break;
		}
		
		case ID_L3Downlink_HANDOVER_COMMAND: {
			INIT_c_HANDOVER_COMMAND (&(sp->Data.fld_c_HANDOVER_COMMAND));
			break;
		}
		
		case ID_L3Downlink_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND: {
			INIT_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND (&(sp->Data.fld_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND));
			break;
		}
		
		case ID_L3Downlink_PHYSICAL_INFORMATION: {
			INIT_c_PHYSICAL_INFORMATION (&(sp->Data.fld_c_PHYSICAL_INFORMATION));
			break;
		}
		
		case ID_L3Downlink_RR_STATUS: {
			INIT_c_RR_STATUS (&(sp->Data.fld_c_RR_STATUS));
			break;
		}
		
		case ID_L3Downlink_APPLICATION_INFORMATION: {
			INIT_c_APPLICATION_INFORMATION (&(sp->Data.fld_c_APPLICATION_INFORMATION));
			break;
		}
		
		default:;
	}
}

void FREE_TL3Downlink_Data (TL3Downlink_Data* sp)
{
	switch (sp->Type) {
		case ID_L3Downlink_ASSIGNMENT_COMMAND: {
			FREE_c_ASSIGNMENT_COMMAND (&(sp->Data.fld_c_ASSIGNMENT_COMMAND));
			break;
		}
		
		case ID_L3Downlink_CHANNEL_MODE_MODIFY: {
			FREE_c_CHANNEL_MODE_MODIFY (&(sp->Data.fld_c_CHANNEL_MODE_MODIFY));
			break;
		}
		
		case ID_L3Downlink_CHANNEL_RELEASE: {
			FREE_c_CHANNEL_RELEASE (&(sp->Data.fld_c_CHANNEL_RELEASE));
			break;
		}
		
		case ID_L3Downlink_CIPHERING_MODE_COMMAND: {
			FREE_c_CIPHERING_MODE_COMMAND (&(sp->Data.fld_c_CIPHERING_MODE_COMMAND));
			break;
		}
		
		case ID_L3Downlink_CLASSMARK_ENQUIRY: {
			FREE_c_CLASSMARK_ENQUIRY (&(sp->Data.fld_c_CLASSMARK_ENQUIRY));
			break;
		}
		
		case ID_L3Downlink_FREQUENCY_REDEFINITION: {
			FREE_c_FREQUENCY_REDEFINITION (&(sp->Data.fld_c_FREQUENCY_REDEFINITION));
			break;
		}
		
		case ID_L3Downlink_HANDOVER_COMMAND: {
			FREE_c_HANDOVER_COMMAND (&(sp->Data.fld_c_HANDOVER_COMMAND));
			break;
		}
		
		case ID_L3Downlink_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND: {
			FREE_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND (&(sp->Data.fld_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND));
			break;
		}
		
		case ID_L3Downlink_PHYSICAL_INFORMATION: {
			FREE_c_PHYSICAL_INFORMATION (&(sp->Data.fld_c_PHYSICAL_INFORMATION));
			break;
		}
		
		case ID_L3Downlink_RR_STATUS: {
			FREE_c_RR_STATUS (&(sp->Data.fld_c_RR_STATUS));
			break;
		}
		
		case ID_L3Downlink_APPLICATION_INFORMATION: {
			FREE_c_APPLICATION_INFORMATION (&(sp->Data.fld_c_APPLICATION_INFORMATION));
			break;
		}
		
		default:;
	}

	sp->Type = ID_L3Downlink_Unrecognized;
}

void SETPRESENT_TL3Uplink_Data (TL3Uplink_Data* sp, TL3Uplink_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TL3Uplink_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_L3Uplink_ASSIGNMENT_COMPLETE: {
			INIT_c_ASSIGNMENT_COMPLETE (&(sp->Data.fld_c_ASSIGNMENT_COMPLETE));
			break;
		}
		
		case ID_L3Uplink_ASSIGNMENT_FAILURE: {
			INIT_c_ASSIGNMENT_FAILURE (&(sp->Data.fld_c_ASSIGNMENT_FAILURE));
			break;
		}
		
		case ID_L3Uplink_CHANNEL_MODE_MODIFY_ACKNOWLEDGE: {
			INIT_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE (&(sp->Data.fld_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE));
			break;
		}
		
		case ID_L3Uplink_CIPHERING_MODE_COMPLETE: {
			INIT_c_CIPHERING_MODE_COMPLETE (&(sp->Data.fld_c_CIPHERING_MODE_COMPLETE));
			break;
		}
		
		case ID_L3Uplink_CLASSMARK_CHANGE: {
			INIT_c_CLASSMARK_CHANGE (&(sp->Data.fld_c_CLASSMARK_CHANGE));
			break;
		}
		
		case ID_L3Uplink_GPRS_SUSPENSION_REQUEST: {
			INIT_c_GPRS_SUSPENSION_REQUEST (&(sp->Data.fld_c_GPRS_SUSPENSION_REQUEST));
			break;
		}
		
		case ID_L3Uplink_HANDOVER_COMPLETE: {
			INIT_c_HANDOVER_COMPLETE (&(sp->Data.fld_c_HANDOVER_COMPLETE));
			break;
		}
		
		case ID_L3Uplink_HANDOVER_FAILURE: {
			INIT_c_HANDOVER_FAILURE (&(sp->Data.fld_c_HANDOVER_FAILURE));
			break;
		}
		
		case ID_L3Uplink_MEASUREMENT_REPORT: {
			INIT_c_MEASUREMENT_REPORT (&(sp->Data.fld_c_MEASUREMENT_REPORT));
			break;
		}
		
		case ID_L3Uplink_PAGING_RESPONSE: {
			INIT_c_PAGING_RESPONSE (&(sp->Data.fld_c_PAGING_RESPONSE));
			break;
		}
		
		case ID_L3Uplink_RR_INITIALISATION_REQUEST: {
			INIT_c_RR_INITIALISATION_REQUEST (&(sp->Data.fld_c_RR_INITIALISATION_REQUEST));
			break;
		}
		
		case ID_L3Uplink_RR_STATUS: {
			INIT_c_RR_STATUS (&(sp->Data.fld_c_RR_STATUS));
			break;
		}
		
		case ID_L3Uplink_EXTENDED_MEASUREMENT_REPORT: {
			INIT_c_EXTENDED_MEASUREMENT_REPORT (&(sp->Data.fld_c_EXTENDED_MEASUREMENT_REPORT));
			break;
		}
		
		case ID_L3Uplink_APPLICATION_INFORMATION: {
			INIT_c_APPLICATION_INFORMATION (&(sp->Data.fld_c_APPLICATION_INFORMATION));
			break;
		}
		
		default:;
	}
}

void FREE_TL3Uplink_Data (TL3Uplink_Data* sp)
{
	switch (sp->Type) {
		case ID_L3Uplink_ASSIGNMENT_COMPLETE: {
			FREE_c_ASSIGNMENT_COMPLETE (&(sp->Data.fld_c_ASSIGNMENT_COMPLETE));
			break;
		}
		
		case ID_L3Uplink_ASSIGNMENT_FAILURE: {
			FREE_c_ASSIGNMENT_FAILURE (&(sp->Data.fld_c_ASSIGNMENT_FAILURE));
			break;
		}
		
		case ID_L3Uplink_CHANNEL_MODE_MODIFY_ACKNOWLEDGE: {
			FREE_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE (&(sp->Data.fld_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE));
			break;
		}
		
		case ID_L3Uplink_CIPHERING_MODE_COMPLETE: {
			FREE_c_CIPHERING_MODE_COMPLETE (&(sp->Data.fld_c_CIPHERING_MODE_COMPLETE));
			break;
		}
		
		case ID_L3Uplink_CLASSMARK_CHANGE: {
			FREE_c_CLASSMARK_CHANGE (&(sp->Data.fld_c_CLASSMARK_CHANGE));
			break;
		}
		
		case ID_L3Uplink_GPRS_SUSPENSION_REQUEST: {
			FREE_c_GPRS_SUSPENSION_REQUEST (&(sp->Data.fld_c_GPRS_SUSPENSION_REQUEST));
			break;
		}
		
		case ID_L3Uplink_HANDOVER_COMPLETE: {
			FREE_c_HANDOVER_COMPLETE (&(sp->Data.fld_c_HANDOVER_COMPLETE));
			break;
		}
		
		case ID_L3Uplink_HANDOVER_FAILURE: {
			FREE_c_HANDOVER_FAILURE (&(sp->Data.fld_c_HANDOVER_FAILURE));
			break;
		}
		
		case ID_L3Uplink_MEASUREMENT_REPORT: {
			FREE_c_MEASUREMENT_REPORT (&(sp->Data.fld_c_MEASUREMENT_REPORT));
			break;
		}
		
		case ID_L3Uplink_PAGING_RESPONSE: {
			FREE_c_PAGING_RESPONSE (&(sp->Data.fld_c_PAGING_RESPONSE));
			break;
		}
		
		case ID_L3Uplink_RR_INITIALISATION_REQUEST: {
			FREE_c_RR_INITIALISATION_REQUEST (&(sp->Data.fld_c_RR_INITIALISATION_REQUEST));
			break;
		}
		
		case ID_L3Uplink_RR_STATUS: {
			FREE_c_RR_STATUS (&(sp->Data.fld_c_RR_STATUS));
			break;
		}
		
		case ID_L3Uplink_EXTENDED_MEASUREMENT_REPORT: {
			FREE_c_EXTENDED_MEASUREMENT_REPORT (&(sp->Data.fld_c_EXTENDED_MEASUREMENT_REPORT));
			break;
		}
		
		case ID_L3Uplink_APPLICATION_INFORMATION: {
			FREE_c_APPLICATION_INFORMATION (&(sp->Data.fld_c_APPLICATION_INFORMATION));
			break;
		}
		
		default:;
	}

	sp->Type = ID_L3Uplink_Unrecognized;
}

void SETPRESENT_TPLENDownlink_Data (TPLENDownlink_Data* sp, TPLENDownlink_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TPLENDownlink_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_PLENDownlink_IMMEDIATE_ASSIGNMENT: {
			INIT_c_IMMEDIATE_ASSIGNMENT (&(sp->Data.fld_c_IMMEDIATE_ASSIGNMENT));
			break;
		}
		
		case ID_PLENDownlink_IMMEDIATE_ASSIGNMENT_EXTENDED: {
			INIT_c_IMMEDIATE_ASSIGNMENT_EXTENDED (&(sp->Data.fld_c_IMMEDIATE_ASSIGNMENT_EXTENDED));
			break;
		}
		
		case ID_PLENDownlink_IMMEDIATE_ASSIGNMENT_REJECT: {
			INIT_c_IMMEDIATE_ASSIGNMENT_REJECT (&(sp->Data.fld_c_IMMEDIATE_ASSIGNMENT_REJECT));
			break;
		}
		
		case ID_PLENDownlink_PAGING_REQUEST_TYPE_1: {
			INIT_c_PAGING_REQUEST_TYPE_1 (&(sp->Data.fld_c_PAGING_REQUEST_TYPE_1));
			break;
		}
		
		case ID_PLENDownlink_PAGING_REQUEST_TYPE_2: {
			INIT_c_PAGING_REQUEST_TYPE_2 (&(sp->Data.fld_c_PAGING_REQUEST_TYPE_2));
			break;
		}
		
		case ID_PLENDownlink_PAGING_REQUEST_TYPE_3: {
			INIT_c_PAGING_REQUEST_TYPE_3 (&(sp->Data.fld_c_PAGING_REQUEST_TYPE_3));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_1: {
			INIT_c_SYSTEM_INFORMATION_TYPE_1 (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_1));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_2: {
			INIT_c_SYSTEM_INFORMATION_TYPE_2 (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_2));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_2BIS: {
			INIT_c_SYSTEM_INFORMATION_TYPE_2BIS (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_2BIS));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_2TER: {
			INIT_c_SYSTEM_INFORMATION_TYPE_2TER (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_2TER));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_2QUATER: {
			INIT_c_SYSTEM_INFORMATION_TYPE_2QUATER (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_2QUATER));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_2N: {
			INIT_c_SYSTEM_INFORMATION_TYPE_2N (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_2N));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_3: {
			INIT_c_SYSTEM_INFORMATION_TYPE_3 (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_3));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_4: {
			INIT_c_SYSTEM_INFORMATION_TYPE_4 (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_4));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_5: {
			INIT_c_SYSTEM_INFORMATION_TYPE_5 (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_5));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_5BIS: {
			INIT_c_SYSTEM_INFORMATION_TYPE_5BIS (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_5BIS));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_5TER: {
			INIT_c_SYSTEM_INFORMATION_TYPE_5TER (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_5TER));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_6: {
			INIT_c_SYSTEM_INFORMATION_TYPE_6 (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_6));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_7: {
			INIT_c_SYSTEM_INFORMATION_TYPE_7 (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_7));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_8: {
			INIT_c_SYSTEM_INFORMATION_TYPE_8 (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_8));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_9: {
			INIT_c_SYSTEM_INFORMATION_TYPE_9 (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_9));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_13: {
			INIT_c_SYSTEM_INFORMATION_TYPE_13 (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_13));
			break;
		}
		
		case ID_PLENDownlink_EXTENDED_MEASUREMENT_ORDER: {
			INIT_c_EXTENDED_MEASUREMENT_ORDER (&(sp->Data.fld_c_EXTENDED_MEASUREMENT_ORDER));
			break;
		}
		
		default:;
	}
}

void FREE_TPLENDownlink_Data (TPLENDownlink_Data* sp)
{
	switch (sp->Type) {
		case ID_PLENDownlink_IMMEDIATE_ASSIGNMENT: {
			FREE_c_IMMEDIATE_ASSIGNMENT (&(sp->Data.fld_c_IMMEDIATE_ASSIGNMENT));
			break;
		}
		
		case ID_PLENDownlink_IMMEDIATE_ASSIGNMENT_EXTENDED: {
			FREE_c_IMMEDIATE_ASSIGNMENT_EXTENDED (&(sp->Data.fld_c_IMMEDIATE_ASSIGNMENT_EXTENDED));
			break;
		}
		
		case ID_PLENDownlink_IMMEDIATE_ASSIGNMENT_REJECT: {
			FREE_c_IMMEDIATE_ASSIGNMENT_REJECT (&(sp->Data.fld_c_IMMEDIATE_ASSIGNMENT_REJECT));
			break;
		}
		
		case ID_PLENDownlink_PAGING_REQUEST_TYPE_1: {
			FREE_c_PAGING_REQUEST_TYPE_1 (&(sp->Data.fld_c_PAGING_REQUEST_TYPE_1));
			break;
		}
		
		case ID_PLENDownlink_PAGING_REQUEST_TYPE_2: {
			FREE_c_PAGING_REQUEST_TYPE_2 (&(sp->Data.fld_c_PAGING_REQUEST_TYPE_2));
			break;
		}
		
		case ID_PLENDownlink_PAGING_REQUEST_TYPE_3: {
			FREE_c_PAGING_REQUEST_TYPE_3 (&(sp->Data.fld_c_PAGING_REQUEST_TYPE_3));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_1: {
			FREE_c_SYSTEM_INFORMATION_TYPE_1 (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_1));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_2: {
			FREE_c_SYSTEM_INFORMATION_TYPE_2 (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_2));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_2BIS: {
			FREE_c_SYSTEM_INFORMATION_TYPE_2BIS (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_2BIS));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_2TER: {
			FREE_c_SYSTEM_INFORMATION_TYPE_2TER (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_2TER));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_2QUATER: {
			FREE_c_SYSTEM_INFORMATION_TYPE_2QUATER (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_2QUATER));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_2N: {
			FREE_c_SYSTEM_INFORMATION_TYPE_2N (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_2N));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_3: {
			FREE_c_SYSTEM_INFORMATION_TYPE_3 (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_3));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_4: {
			FREE_c_SYSTEM_INFORMATION_TYPE_4 (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_4));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_5: {
			FREE_c_SYSTEM_INFORMATION_TYPE_5 (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_5));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_5BIS: {
			FREE_c_SYSTEM_INFORMATION_TYPE_5BIS (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_5BIS));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_5TER: {
			FREE_c_SYSTEM_INFORMATION_TYPE_5TER (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_5TER));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_6: {
			FREE_c_SYSTEM_INFORMATION_TYPE_6 (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_6));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_7: {
			FREE_c_SYSTEM_INFORMATION_TYPE_7 (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_7));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_8: {
			FREE_c_SYSTEM_INFORMATION_TYPE_8 (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_8));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_9: {
			FREE_c_SYSTEM_INFORMATION_TYPE_9 (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_9));
			break;
		}
		
		case ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_13: {
			FREE_c_SYSTEM_INFORMATION_TYPE_13 (&(sp->Data.fld_c_SYSTEM_INFORMATION_TYPE_13));
			break;
		}
		
		case ID_PLENDownlink_EXTENDED_MEASUREMENT_ORDER: {
			FREE_c_EXTENDED_MEASUREMENT_ORDER (&(sp->Data.fld_c_EXTENDED_MEASUREMENT_ORDER));
			break;
		}
		
		default:;
	}

	sp->Type = ID_PLENDownlink_Unrecognized;
}

void SETPRESENT_TDownlink_RLC_MAC_Data (TDownlink_RLC_MAC_Data* sp, TDownlink_RLC_MAC_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TDownlink_RLC_MAC_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_Downlink_RLC_MAC_Packet_Cell_Change_Order: {
			INIT_c_Packet_Cell_Change_Order (&(sp->Data.fld_c_Packet_Cell_Change_Order));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Downlink_Assignment: {
			INIT_c_Packet_Downlink_Assignment (&(sp->Data.fld_c_Packet_Downlink_Assignment));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Measurement_Order: {
			INIT_c_Packet_Measurement_Order (&(sp->Data.fld_c_Packet_Measurement_Order));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Polling_Request: {
			INIT_c_Packet_Polling_Request (&(sp->Data.fld_c_Packet_Polling_Request));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Power_Control_Timing_Advance: {
			INIT_c_Packet_Power_Control_Timing_Advance (&(sp->Data.fld_c_Packet_Power_Control_Timing_Advance));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Queueing_Notification: {
			INIT_c_Packet_Queueing_Notification (&(sp->Data.fld_c_Packet_Queueing_Notification));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Timeslot_Reconfigure: {
			INIT_c_Packet_Timeslot_Reconfigure (&(sp->Data.fld_c_Packet_Timeslot_Reconfigure));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_TBF_Release: {
			INIT_c_Packet_TBF_Release (&(sp->Data.fld_c_Packet_TBF_Release));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Uplink_Ack_Nack: {
			INIT_c_Packet_Uplink_Ack_Nack (&(sp->Data.fld_c_Packet_Uplink_Ack_Nack));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Uplink_Assignment: {
			INIT_c_Packet_Uplink_Assignment (&(sp->Data.fld_c_Packet_Uplink_Assignment));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Cell_Change_Continue: {
			INIT_c_Packet_Cell_Change_Continue (&(sp->Data.fld_c_Packet_Cell_Change_Continue));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Neighbour_Cell_Data: {
			INIT_c_Packet_Neighbour_Cell_Data (&(sp->Data.fld_c_Packet_Neighbour_Cell_Data));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Serving_Cell_Data: {
			INIT_c_Packet_Serving_Cell_Data (&(sp->Data.fld_c_Packet_Serving_Cell_Data));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Access_Reject: {
			INIT_c_Packet_Access_Reject (&(sp->Data.fld_c_Packet_Access_Reject));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Paging_Request: {
			INIT_c_Packet_Paging_Request (&(sp->Data.fld_c_Packet_Paging_Request));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_PDCH_Release: {
			INIT_c_Packet_PDCH_Release (&(sp->Data.fld_c_Packet_PDCH_Release));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_PRACH_Parameters: {
			INIT_c_Packet_PRACH_Parameters (&(sp->Data.fld_c_Packet_PRACH_Parameters));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Downlink_Dummy_Control_Block: {
			INIT_c_Packet_Downlink_Dummy_Control_Block (&(sp->Data.fld_c_Packet_Downlink_Dummy_Control_Block));
			break;
		}
		
		case ID_Downlink_RLC_MAC_PSI1: {
			INIT_c_PSI1 (&(sp->Data.fld_c_PSI1));
			break;
		}
		
		case ID_Downlink_RLC_MAC_PSI2: {
			INIT_c_PSI2 (&(sp->Data.fld_c_PSI2));
			break;
		}
		
		case ID_Downlink_RLC_MAC_PSI3: {
			INIT_c_PSI3 (&(sp->Data.fld_c_PSI3));
			break;
		}
		
		case ID_Downlink_RLC_MAC_PSI3_bis: {
			INIT_c_PSI3_bis (&(sp->Data.fld_c_PSI3_bis));
			break;
		}
		
		case ID_Downlink_RLC_MAC_PSI4: {
			INIT_c_PSI4 (&(sp->Data.fld_c_PSI4));
			break;
		}
		
		case ID_Downlink_RLC_MAC_PSI5: {
			INIT_c_PSI5 (&(sp->Data.fld_c_PSI5));
			break;
		}
		
		case ID_Downlink_RLC_MAC_PSI13: {
			INIT_c_PSI13 (&(sp->Data.fld_c_PSI13));
			break;
		}
		
		case ID_Downlink_RLC_MAC_PSI14: {
			INIT_c_PSI14 (&(sp->Data.fld_c_PSI14));
			break;
		}
		
		case ID_Downlink_RLC_MAC_PSI3_ter: {
			INIT_c_PSI3_ter (&(sp->Data.fld_c_PSI3_ter));
			break;
		}
		
		case ID_Downlink_RLC_MAC_PSI3_quater: {
			INIT_c_PSI3_quater (&(sp->Data.fld_c_PSI3_quater));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Serving_Cell_SI: {
			INIT_c_Packet_Serving_Cell_SI (&(sp->Data.fld_c_Packet_Serving_Cell_SI));
			break;
		}
		
		case ID_Downlink_RLC_MAC_PS_Handover_Command: {
			INIT_c_PS_Handover_Command (&(sp->Data.fld_c_PS_Handover_Command));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Physical_Information: {
			INIT_c_Packet_Physical_Information (&(sp->Data.fld_c_Packet_Physical_Information));
			break;
		}
		
		default:;
	}
}

void FREE_TDownlink_RLC_MAC_Data (TDownlink_RLC_MAC_Data* sp)
{
	switch (sp->Type) {
		case ID_Downlink_RLC_MAC_Packet_Cell_Change_Order: {
			FREE_c_Packet_Cell_Change_Order (&(sp->Data.fld_c_Packet_Cell_Change_Order));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Downlink_Assignment: {
			FREE_c_Packet_Downlink_Assignment (&(sp->Data.fld_c_Packet_Downlink_Assignment));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Measurement_Order: {
			FREE_c_Packet_Measurement_Order (&(sp->Data.fld_c_Packet_Measurement_Order));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Polling_Request: {
			FREE_c_Packet_Polling_Request (&(sp->Data.fld_c_Packet_Polling_Request));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Power_Control_Timing_Advance: {
			FREE_c_Packet_Power_Control_Timing_Advance (&(sp->Data.fld_c_Packet_Power_Control_Timing_Advance));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Queueing_Notification: {
			FREE_c_Packet_Queueing_Notification (&(sp->Data.fld_c_Packet_Queueing_Notification));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Timeslot_Reconfigure: {
			FREE_c_Packet_Timeslot_Reconfigure (&(sp->Data.fld_c_Packet_Timeslot_Reconfigure));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_TBF_Release: {
			FREE_c_Packet_TBF_Release (&(sp->Data.fld_c_Packet_TBF_Release));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Uplink_Ack_Nack: {
			FREE_c_Packet_Uplink_Ack_Nack (&(sp->Data.fld_c_Packet_Uplink_Ack_Nack));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Uplink_Assignment: {
			FREE_c_Packet_Uplink_Assignment (&(sp->Data.fld_c_Packet_Uplink_Assignment));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Cell_Change_Continue: {
			FREE_c_Packet_Cell_Change_Continue (&(sp->Data.fld_c_Packet_Cell_Change_Continue));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Neighbour_Cell_Data: {
			FREE_c_Packet_Neighbour_Cell_Data (&(sp->Data.fld_c_Packet_Neighbour_Cell_Data));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Serving_Cell_Data: {
			FREE_c_Packet_Serving_Cell_Data (&(sp->Data.fld_c_Packet_Serving_Cell_Data));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Access_Reject: {
			FREE_c_Packet_Access_Reject (&(sp->Data.fld_c_Packet_Access_Reject));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Paging_Request: {
			FREE_c_Packet_Paging_Request (&(sp->Data.fld_c_Packet_Paging_Request));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_PDCH_Release: {
			FREE_c_Packet_PDCH_Release (&(sp->Data.fld_c_Packet_PDCH_Release));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_PRACH_Parameters: {
			FREE_c_Packet_PRACH_Parameters (&(sp->Data.fld_c_Packet_PRACH_Parameters));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Downlink_Dummy_Control_Block: {
			FREE_c_Packet_Downlink_Dummy_Control_Block (&(sp->Data.fld_c_Packet_Downlink_Dummy_Control_Block));
			break;
		}
		
		case ID_Downlink_RLC_MAC_PSI1: {
			FREE_c_PSI1 (&(sp->Data.fld_c_PSI1));
			break;
		}
		
		case ID_Downlink_RLC_MAC_PSI2: {
			FREE_c_PSI2 (&(sp->Data.fld_c_PSI2));
			break;
		}
		
		case ID_Downlink_RLC_MAC_PSI3: {
			FREE_c_PSI3 (&(sp->Data.fld_c_PSI3));
			break;
		}
		
		case ID_Downlink_RLC_MAC_PSI3_bis: {
			FREE_c_PSI3_bis (&(sp->Data.fld_c_PSI3_bis));
			break;
		}
		
		case ID_Downlink_RLC_MAC_PSI4: {
			FREE_c_PSI4 (&(sp->Data.fld_c_PSI4));
			break;
		}
		
		case ID_Downlink_RLC_MAC_PSI5: {
			FREE_c_PSI5 (&(sp->Data.fld_c_PSI5));
			break;
		}
		
		case ID_Downlink_RLC_MAC_PSI13: {
			FREE_c_PSI13 (&(sp->Data.fld_c_PSI13));
			break;
		}
		
		case ID_Downlink_RLC_MAC_PSI14: {
			FREE_c_PSI14 (&(sp->Data.fld_c_PSI14));
			break;
		}
		
		case ID_Downlink_RLC_MAC_PSI3_ter: {
			FREE_c_PSI3_ter (&(sp->Data.fld_c_PSI3_ter));
			break;
		}
		
		case ID_Downlink_RLC_MAC_PSI3_quater: {
			FREE_c_PSI3_quater (&(sp->Data.fld_c_PSI3_quater));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Serving_Cell_SI: {
			FREE_c_Packet_Serving_Cell_SI (&(sp->Data.fld_c_Packet_Serving_Cell_SI));
			break;
		}
		
		case ID_Downlink_RLC_MAC_PS_Handover_Command: {
			FREE_c_PS_Handover_Command (&(sp->Data.fld_c_PS_Handover_Command));
			break;
		}
		
		case ID_Downlink_RLC_MAC_Packet_Physical_Information: {
			FREE_c_Packet_Physical_Information (&(sp->Data.fld_c_Packet_Physical_Information));
			break;
		}
		
		default:;
	}

	sp->Type = ID_Downlink_RLC_MAC_Unrecognized;
}

void SETPRESENT_TUplink_RLC_MAC_Data (TUplink_RLC_MAC_Data* sp, TUplink_RLC_MAC_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TUplink_RLC_MAC_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_Uplink_RLC_MAC_Packet_Cell_Change_Failure: {
			INIT_c_Packet_Cell_Change_Failure (&(sp->Data.fld_c_Packet_Cell_Change_Failure));
			break;
		}
		
		case ID_Uplink_RLC_MAC_Packet_Control_Acknowledgement: {
			INIT_c_Packet_Control_Acknowledgement (&(sp->Data.fld_c_Packet_Control_Acknowledgement));
			break;
		}
		
		case ID_Uplink_RLC_MAC_Packet_Downlink_Ack_Nack: {
			INIT_c_Packet_Downlink_Ack_Nack (&(sp->Data.fld_c_Packet_Downlink_Ack_Nack));
			break;
		}
		
		case ID_Uplink_RLC_MAC_Packet_Uplink_Dummy_Control_Block: {
			INIT_c_Packet_Uplink_Dummy_Control_Block (&(sp->Data.fld_c_Packet_Uplink_Dummy_Control_Block));
			break;
		}
		
		case ID_Uplink_RLC_MAC_Packet_Measurement_Report: {
			INIT_c_Packet_Measurement_Report (&(sp->Data.fld_c_Packet_Measurement_Report));
			break;
		}
		
		case ID_Uplink_RLC_MAC_Packet_Resource_Request: {
			INIT_c_Packet_Resource_Request (&(sp->Data.fld_c_Packet_Resource_Request));
			break;
		}
		
		case ID_Uplink_RLC_MAC_Packet_Mobile_TBF_Status: {
			INIT_c_Packet_Mobile_TBF_Status (&(sp->Data.fld_c_Packet_Mobile_TBF_Status));
			break;
		}
		
		case ID_Uplink_RLC_MAC_Packet_PSI_Status: {
			INIT_c_Packet_PSI_Status (&(sp->Data.fld_c_Packet_PSI_Status));
			break;
		}
		
		case ID_Uplink_RLC_MAC_EGPRS_Packet_Downlink_Ack_Nack: {
			INIT_c_EGPRS_Packet_Downlink_Ack_Nack (&(sp->Data.fld_c_EGPRS_Packet_Downlink_Ack_Nack));
			break;
		}
		
		case ID_Uplink_RLC_MAC_Packet_Enhanced_Measurement_Report: {
			INIT_c_Packet_Enhanced_Measurement_Report (&(sp->Data.fld_c_Packet_Enhanced_Measurement_Report));
			break;
		}
		
		case ID_Uplink_RLC_MAC_Additional_MS_Radio_Access_Capabilities: {
			INIT_c_Additional_MS_Radio_Access_Capabilities (&(sp->Data.fld_c_Additional_MS_Radio_Access_Capabilities));
			break;
		}
		
		case ID_Uplink_RLC_MAC_Packet_Cell_Change_Notification: {
			INIT_c_Packet_Cell_Change_Notification (&(sp->Data.fld_c_Packet_Cell_Change_Notification));
			break;
		}
		
		case ID_Uplink_RLC_MAC_Packet_SI_Status: {
			INIT_c_Packet_SI_Status (&(sp->Data.fld_c_Packet_SI_Status));
			break;
		}
		
		default:;
	}
}

void FREE_TUplink_RLC_MAC_Data (TUplink_RLC_MAC_Data* sp)
{
	switch (sp->Type) {
		case ID_Uplink_RLC_MAC_Packet_Cell_Change_Failure: {
			FREE_c_Packet_Cell_Change_Failure (&(sp->Data.fld_c_Packet_Cell_Change_Failure));
			break;
		}
		
		case ID_Uplink_RLC_MAC_Packet_Control_Acknowledgement: {
			FREE_c_Packet_Control_Acknowledgement (&(sp->Data.fld_c_Packet_Control_Acknowledgement));
			break;
		}
		
		case ID_Uplink_RLC_MAC_Packet_Downlink_Ack_Nack: {
			FREE_c_Packet_Downlink_Ack_Nack (&(sp->Data.fld_c_Packet_Downlink_Ack_Nack));
			break;
		}
		
		case ID_Uplink_RLC_MAC_Packet_Uplink_Dummy_Control_Block: {
			FREE_c_Packet_Uplink_Dummy_Control_Block (&(sp->Data.fld_c_Packet_Uplink_Dummy_Control_Block));
			break;
		}
		
		case ID_Uplink_RLC_MAC_Packet_Measurement_Report: {
			FREE_c_Packet_Measurement_Report (&(sp->Data.fld_c_Packet_Measurement_Report));
			break;
		}
		
		case ID_Uplink_RLC_MAC_Packet_Resource_Request: {
			FREE_c_Packet_Resource_Request (&(sp->Data.fld_c_Packet_Resource_Request));
			break;
		}
		
		case ID_Uplink_RLC_MAC_Packet_Mobile_TBF_Status: {
			FREE_c_Packet_Mobile_TBF_Status (&(sp->Data.fld_c_Packet_Mobile_TBF_Status));
			break;
		}
		
		case ID_Uplink_RLC_MAC_Packet_PSI_Status: {
			FREE_c_Packet_PSI_Status (&(sp->Data.fld_c_Packet_PSI_Status));
			break;
		}
		
		case ID_Uplink_RLC_MAC_EGPRS_Packet_Downlink_Ack_Nack: {
			FREE_c_EGPRS_Packet_Downlink_Ack_Nack (&(sp->Data.fld_c_EGPRS_Packet_Downlink_Ack_Nack));
			break;
		}
		
		case ID_Uplink_RLC_MAC_Packet_Enhanced_Measurement_Report: {
			FREE_c_Packet_Enhanced_Measurement_Report (&(sp->Data.fld_c_Packet_Enhanced_Measurement_Report));
			break;
		}
		
		case ID_Uplink_RLC_MAC_Additional_MS_Radio_Access_Capabilities: {
			FREE_c_Additional_MS_Radio_Access_Capabilities (&(sp->Data.fld_c_Additional_MS_Radio_Access_Capabilities));
			break;
		}
		
		case ID_Uplink_RLC_MAC_Packet_Cell_Change_Notification: {
			FREE_c_Packet_Cell_Change_Notification (&(sp->Data.fld_c_Packet_Cell_Change_Notification));
			break;
		}
		
		case ID_Uplink_RLC_MAC_Packet_SI_Status: {
			FREE_c_Packet_SI_Status (&(sp->Data.fld_c_Packet_SI_Status));
			break;
		}
		
		default:;
	}

	sp->Type = ID_Uplink_RLC_MAC_Unrecognized;
}

#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif

#ifndef XSCT_CMICRO
#define ED_SDL_ACCESS_UNION(signalName,position) (((yPDP_##signalName)SignalIn)->Param##position)
#else
#define ED_SDL_ACCESS_UNION(signalName,position) (signalData.data_##signalName.Param##position)
#endif



int SetDecode_L3Downlink (const char* buffer, TL3Downlink_Data* data, int bitLen)
{
	int retLen = 0;
	
	/*-----------------------------------------------------------------
		Key is set to a single value containing protocol discriminator,
		skip indicator and message type.
		For example, message ASSIGNMENT_COMMAND has:
			skip indicator         = 0000 (0x0)
			protocol discriminator = 0110 (0x6)
			message type           = 00101110 (0x2E)
		In this case, key will be set to 0x602E.
		Skip indicator could be in some cases a transaction identifier.
		In such cases, it will be set to 0 for matching purposes.
	------------------------------------------------------------------*/
	unsigned /****/ int key /*1*/ = ((((unsigned char)buffer [0]) << 8) | ((unsigned char)buffer [1]))& 0x0FFF/*2*/;/*3*/
		data->ProtocolDiscriminator = (int)(((unsigned char)buffer [0]) & 0x0f);
	data->MessageType = (int)((unsigned char)buffer [1]);
	
	switch (key) {
			/* Detect signal ASSIGNMENT_COMMAND */
		case 0x062E: {
			SETPRESENT_TL3Downlink_Data (data, ID_L3Downlink_ASSIGNMENT_COMMAND);
			INIT_c_ASSIGNMENT_COMMAND (&data->Data.fld_c_ASSIGNMENT_COMMAND);
			retLen = DECODE_c_ASSIGNMENT_COMMAND (buffer, 0, &(data->Data.fld_c_ASSIGNMENT_COMMAND), bitLen);
		
			return retLen;
		}
		/* Detect signal CHANNEL_MODE_MODIFY */
		case 0x0610: {
			SETPRESENT_TL3Downlink_Data (data, ID_L3Downlink_CHANNEL_MODE_MODIFY);
			INIT_c_CHANNEL_MODE_MODIFY (&data->Data.fld_c_CHANNEL_MODE_MODIFY);
			retLen = DECODE_c_CHANNEL_MODE_MODIFY (buffer, 0, &(data->Data.fld_c_CHANNEL_MODE_MODIFY), bitLen);
		
			return retLen;
		}
		/* Detect signal CHANNEL_RELEASE */
		case 0x060D: {
			SETPRESENT_TL3Downlink_Data (data, ID_L3Downlink_CHANNEL_RELEASE);
			INIT_c_CHANNEL_RELEASE (&data->Data.fld_c_CHANNEL_RELEASE);
			retLen = DECODE_c_CHANNEL_RELEASE (buffer, 0, &(data->Data.fld_c_CHANNEL_RELEASE), bitLen);
		
			return retLen;
		}
		/* Detect signal CIPHERING_MODE_COMMAND */
		case 0x0635: {
			SETPRESENT_TL3Downlink_Data (data, ID_L3Downlink_CIPHERING_MODE_COMMAND);
			INIT_c_CIPHERING_MODE_COMMAND (&data->Data.fld_c_CIPHERING_MODE_COMMAND);
			retLen = DECODE_c_CIPHERING_MODE_COMMAND (buffer, 0, &(data->Data.fld_c_CIPHERING_MODE_COMMAND), bitLen);
		
			return retLen;
		}
		/* Detect signal CLASSMARK_ENQUIRY */
		case 0x0613: {
			SETPRESENT_TL3Downlink_Data (data, ID_L3Downlink_CLASSMARK_ENQUIRY);
			INIT_c_CLASSMARK_ENQUIRY (&data->Data.fld_c_CLASSMARK_ENQUIRY);
			retLen = DECODE_c_CLASSMARK_ENQUIRY (buffer, 0, &(data->Data.fld_c_CLASSMARK_ENQUIRY), bitLen);
		
			return retLen;
		}
		/* Detect signal FREQUENCY_REDEFINITION */
		case 0x0614: {
			SETPRESENT_TL3Downlink_Data (data, ID_L3Downlink_FREQUENCY_REDEFINITION);
			INIT_c_FREQUENCY_REDEFINITION (&data->Data.fld_c_FREQUENCY_REDEFINITION);
			retLen = DECODE_c_FREQUENCY_REDEFINITION (buffer, 0, &(data->Data.fld_c_FREQUENCY_REDEFINITION), bitLen);
		
			return retLen;
		}
		/* Detect signal HANDOVER_COMMAND */
		case 0x062B: {
			SETPRESENT_TL3Downlink_Data (data, ID_L3Downlink_HANDOVER_COMMAND);
			INIT_c_HANDOVER_COMMAND (&data->Data.fld_c_HANDOVER_COMMAND);
			retLen = DECODE_c_HANDOVER_COMMAND (buffer, 0, &(data->Data.fld_c_HANDOVER_COMMAND), bitLen);
		
			return retLen;
		}
		/* Detect signal INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND */
		case 0x0663: {
			SETPRESENT_TL3Downlink_Data (data, ID_L3Downlink_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND);
			INIT_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND (&data->Data.fld_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND);
			retLen = DECODE_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND (buffer, 0, &(data->Data.fld_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND), bitLen);
		
			return retLen;
		}
		/* Detect signal PHYSICAL_INFORMATION */
		case 0x062D: {
			SETPRESENT_TL3Downlink_Data (data, ID_L3Downlink_PHYSICAL_INFORMATION);
			INIT_c_PHYSICAL_INFORMATION (&data->Data.fld_c_PHYSICAL_INFORMATION);
			retLen = DECODE_c_PHYSICAL_INFORMATION (buffer, 0, &(data->Data.fld_c_PHYSICAL_INFORMATION), bitLen);
		
			return retLen;
		}
		/* Detect signal RR_STATUS */
		case 0x0612: {
			SETPRESENT_TL3Downlink_Data (data, ID_L3Downlink_RR_STATUS);
			INIT_c_RR_STATUS (&data->Data.fld_c_RR_STATUS);
			retLen = DECODE_c_RR_STATUS (buffer, 0, &(data->Data.fld_c_RR_STATUS), bitLen);
		
			return retLen;
		}
		/* Detect signal APPLICATION_INFORMATION */
		case 0x0638: {
			SETPRESENT_TL3Downlink_Data (data, ID_L3Downlink_APPLICATION_INFORMATION);
			INIT_c_APPLICATION_INFORMATION (&data->Data.fld_c_APPLICATION_INFORMATION);
			retLen = DECODE_c_APPLICATION_INFORMATION (buffer, 0, &(data->Data.fld_c_APPLICATION_INFORMATION), bitLen);
		
			return retLen;
		}

	}
	data->Type = ID_L3Downlink_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_L3Downlink (const char* buffer, int len, TL3Downlink_Data* data)
	{
             /*
             if (SetDecode_L3Downlink (buffer, data, len*8) < 0) {
                     return ED_FALSE;
              }
              else {
                     return ED_TRUE;
              }
               */
              return SetDecode_L3Downlink (buffer, data, len*8);  
	}
#endif

#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif

#ifndef XSCT_CMICRO
#define ED_SDL_ACCESS_UNION(signalName,position) (((yPDP_##signalName)SignalIn)->Param##position)
#else
#define ED_SDL_ACCESS_UNION(signalName,position) (signalData.data_##signalName.Param##position)
#endif



int SetDecode_PLENDownlink (const char* buffer, TPLENDownlink_Data* data, int bitLen)
{
	int retLen = 0;
	
	/*-----------------------------------------------------------------
		Key is set to a single value containing protocol discriminator,
		skip indicator and message type.
		For example, message ASSIGNMENT_COMMAND has:
			skip indicator         = 0000 (0x0)
			protocol discriminator = 0110 (0x6)
			message type           = 00101110 (0x2E)
		In this case, key will be set to 0x602E.
		Skip indicator could be in some cases a transaction identifier.
		In such cases, it will be set to 0 for matching purposes.
	------------------------------------------------------------------*/
	unsigned /****/ int key /*1*/ = ((((unsigned char)buffer [1]) << 8) | ((unsigned char)buffer [2]))& 0x0FFF/*2*/;/*3*/
		data->ProtocolDiscriminator = (int)(((unsigned char)buffer [1]) & 0x0f);
	data->MessageType = (int)((unsigned char)buffer [2]);
	
	switch (key) {
			/* Detect signal IMMEDIATE_ASSIGNMENT */
		case 0x063F: {
			SETPRESENT_TPLENDownlink_Data (data, ID_PLENDownlink_IMMEDIATE_ASSIGNMENT);
			INIT_c_IMMEDIATE_ASSIGNMENT (&data->Data.fld_c_IMMEDIATE_ASSIGNMENT);
			retLen = DECODE_c_IMMEDIATE_ASSIGNMENT (buffer, 0, &(data->Data.fld_c_IMMEDIATE_ASSIGNMENT), bitLen);
		
			return retLen;
		}
		/* Detect signal IMMEDIATE_ASSIGNMENT_EXTENDED */
		case 0x0639: {
			SETPRESENT_TPLENDownlink_Data (data, ID_PLENDownlink_IMMEDIATE_ASSIGNMENT_EXTENDED);
			INIT_c_IMMEDIATE_ASSIGNMENT_EXTENDED (&data->Data.fld_c_IMMEDIATE_ASSIGNMENT_EXTENDED);
			retLen = DECODE_c_IMMEDIATE_ASSIGNMENT_EXTENDED (buffer, 0, &(data->Data.fld_c_IMMEDIATE_ASSIGNMENT_EXTENDED), bitLen);
		
			return retLen;
		}
		/* Detect signal IMMEDIATE_ASSIGNMENT_REJECT */
		case 0x063A: {
			SETPRESENT_TPLENDownlink_Data (data, ID_PLENDownlink_IMMEDIATE_ASSIGNMENT_REJECT);
			INIT_c_IMMEDIATE_ASSIGNMENT_REJECT (&data->Data.fld_c_IMMEDIATE_ASSIGNMENT_REJECT);
			retLen = DECODE_c_IMMEDIATE_ASSIGNMENT_REJECT (buffer, 0, &(data->Data.fld_c_IMMEDIATE_ASSIGNMENT_REJECT), bitLen);
		
			return retLen;
		}
		/* Detect signal PAGING_REQUEST_TYPE_1 */
		case 0x0621: {
			SETPRESENT_TPLENDownlink_Data (data, ID_PLENDownlink_PAGING_REQUEST_TYPE_1);
			INIT_c_PAGING_REQUEST_TYPE_1 (&data->Data.fld_c_PAGING_REQUEST_TYPE_1);
			retLen = DECODE_c_PAGING_REQUEST_TYPE_1 (buffer, 0, &(data->Data.fld_c_PAGING_REQUEST_TYPE_1), bitLen);
		
			return retLen;
		}
		/* Detect signal PAGING_REQUEST_TYPE_2 */
		case 0x0622: {
			SETPRESENT_TPLENDownlink_Data (data, ID_PLENDownlink_PAGING_REQUEST_TYPE_2);
			INIT_c_PAGING_REQUEST_TYPE_2 (&data->Data.fld_c_PAGING_REQUEST_TYPE_2);
			retLen = DECODE_c_PAGING_REQUEST_TYPE_2 (buffer, 0, &(data->Data.fld_c_PAGING_REQUEST_TYPE_2), bitLen);
		
			return retLen;
		}
		/* Detect signal PAGING_REQUEST_TYPE_3 */
		case 0x0624: {
			SETPRESENT_TPLENDownlink_Data (data, ID_PLENDownlink_PAGING_REQUEST_TYPE_3);
			INIT_c_PAGING_REQUEST_TYPE_3 (&data->Data.fld_c_PAGING_REQUEST_TYPE_3);
			retLen = DECODE_c_PAGING_REQUEST_TYPE_3 (buffer, 0, &(data->Data.fld_c_PAGING_REQUEST_TYPE_3), bitLen);
		
			return retLen;
		}
		/* Detect signal SYSTEM_INFORMATION_TYPE_1 */
		case 0x0619: {
			SETPRESENT_TPLENDownlink_Data (data, ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_1);
			INIT_c_SYSTEM_INFORMATION_TYPE_1 (&data->Data.fld_c_SYSTEM_INFORMATION_TYPE_1);
			retLen = DECODE_c_SYSTEM_INFORMATION_TYPE_1 (buffer, 0, &(data->Data.fld_c_SYSTEM_INFORMATION_TYPE_1), bitLen);
		
			return retLen;
		}
		/* Detect signal SYSTEM_INFORMATION_TYPE_2 */
		case 0x061A: {
			SETPRESENT_TPLENDownlink_Data (data, ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_2);
			INIT_c_SYSTEM_INFORMATION_TYPE_2 (&data->Data.fld_c_SYSTEM_INFORMATION_TYPE_2);
			retLen = DECODE_c_SYSTEM_INFORMATION_TYPE_2 (buffer, 0, &(data->Data.fld_c_SYSTEM_INFORMATION_TYPE_2), bitLen);
		
			return retLen;
		}
		/* Detect signal SYSTEM_INFORMATION_TYPE_2BIS */
		case 0x0602: {
			SETPRESENT_TPLENDownlink_Data (data, ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_2BIS);
			INIT_c_SYSTEM_INFORMATION_TYPE_2BIS (&data->Data.fld_c_SYSTEM_INFORMATION_TYPE_2BIS);
			retLen = DECODE_c_SYSTEM_INFORMATION_TYPE_2BIS (buffer, 0, &(data->Data.fld_c_SYSTEM_INFORMATION_TYPE_2BIS), bitLen);
		
			return retLen;
		}
		/* Detect signal SYSTEM_INFORMATION_TYPE_2TER */
		case 0x0603: {
			SETPRESENT_TPLENDownlink_Data (data, ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_2TER);
			INIT_c_SYSTEM_INFORMATION_TYPE_2TER (&data->Data.fld_c_SYSTEM_INFORMATION_TYPE_2TER);
			retLen = DECODE_c_SYSTEM_INFORMATION_TYPE_2TER (buffer, 0, &(data->Data.fld_c_SYSTEM_INFORMATION_TYPE_2TER), bitLen);
		
			return retLen;
		}
		/* Detect signal SYSTEM_INFORMATION_TYPE_2QUATER */
		case 0x0607: {
			SETPRESENT_TPLENDownlink_Data (data, ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_2QUATER);
			INIT_c_SYSTEM_INFORMATION_TYPE_2QUATER (&data->Data.fld_c_SYSTEM_INFORMATION_TYPE_2QUATER);
			retLen = DECODE_c_SYSTEM_INFORMATION_TYPE_2QUATER (buffer, 0, &(data->Data.fld_c_SYSTEM_INFORMATION_TYPE_2QUATER), bitLen);
		
			return retLen;
		}
		/* Detect signal SYSTEM_INFORMATION_TYPE_2N */
		case 0x0645: {
			SETPRESENT_TPLENDownlink_Data (data, ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_2N);
			INIT_c_SYSTEM_INFORMATION_TYPE_2N (&data->Data.fld_c_SYSTEM_INFORMATION_TYPE_2N);
			retLen = DECODE_c_SYSTEM_INFORMATION_TYPE_2N (buffer, 0, &(data->Data.fld_c_SYSTEM_INFORMATION_TYPE_2N), bitLen);
		
			return retLen;
		}
		/* Detect signal SYSTEM_INFORMATION_TYPE_3 */
		case 0x061B: {
			SETPRESENT_TPLENDownlink_Data (data, ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_3);
			INIT_c_SYSTEM_INFORMATION_TYPE_3 (&data->Data.fld_c_SYSTEM_INFORMATION_TYPE_3);
			retLen = DECODE_c_SYSTEM_INFORMATION_TYPE_3 (buffer, 0, &(data->Data.fld_c_SYSTEM_INFORMATION_TYPE_3), bitLen);
		
			return retLen;
		}
		/* Detect signal SYSTEM_INFORMATION_TYPE_4 */
		case 0x061C: {
			SETPRESENT_TPLENDownlink_Data (data, ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_4);
			INIT_c_SYSTEM_INFORMATION_TYPE_4 (&data->Data.fld_c_SYSTEM_INFORMATION_TYPE_4);
			retLen = DECODE_c_SYSTEM_INFORMATION_TYPE_4 (buffer, 0, &(data->Data.fld_c_SYSTEM_INFORMATION_TYPE_4), bitLen);
		
			return retLen;
		}
		/* Detect signal SYSTEM_INFORMATION_TYPE_5 */
		case 0x061D: {
			SETPRESENT_TPLENDownlink_Data (data, ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_5);
			INIT_c_SYSTEM_INFORMATION_TYPE_5 (&data->Data.fld_c_SYSTEM_INFORMATION_TYPE_5);
			retLen = DECODE_c_SYSTEM_INFORMATION_TYPE_5 (buffer, 0, &(data->Data.fld_c_SYSTEM_INFORMATION_TYPE_5), bitLen);
		
			return retLen;
		}
		/* Detect signal SYSTEM_INFORMATION_TYPE_5BIS */
		case 0x0605: {
			SETPRESENT_TPLENDownlink_Data (data, ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_5BIS);
			INIT_c_SYSTEM_INFORMATION_TYPE_5BIS (&data->Data.fld_c_SYSTEM_INFORMATION_TYPE_5BIS);
			retLen = DECODE_c_SYSTEM_INFORMATION_TYPE_5BIS (buffer, 0, &(data->Data.fld_c_SYSTEM_INFORMATION_TYPE_5BIS), bitLen);
		
			return retLen;
		}
		/* Detect signal SYSTEM_INFORMATION_TYPE_5TER */
		case 0x0606: {
			SETPRESENT_TPLENDownlink_Data (data, ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_5TER);
			INIT_c_SYSTEM_INFORMATION_TYPE_5TER (&data->Data.fld_c_SYSTEM_INFORMATION_TYPE_5TER);
			retLen = DECODE_c_SYSTEM_INFORMATION_TYPE_5TER (buffer, 0, &(data->Data.fld_c_SYSTEM_INFORMATION_TYPE_5TER), bitLen);
		
			return retLen;
		}
		/* Detect signal SYSTEM_INFORMATION_TYPE_6 */
		case 0x061E: {
			SETPRESENT_TPLENDownlink_Data (data, ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_6);
			INIT_c_SYSTEM_INFORMATION_TYPE_6 (&data->Data.fld_c_SYSTEM_INFORMATION_TYPE_6);
			retLen = DECODE_c_SYSTEM_INFORMATION_TYPE_6 (buffer, 0, &(data->Data.fld_c_SYSTEM_INFORMATION_TYPE_6), bitLen);
		
			return retLen;
		}
		/* Detect signal SYSTEM_INFORMATION_TYPE_7 */
		case 0x061F: {
			SETPRESENT_TPLENDownlink_Data (data, ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_7);
			INIT_c_SYSTEM_INFORMATION_TYPE_7 (&data->Data.fld_c_SYSTEM_INFORMATION_TYPE_7);
			retLen = DECODE_c_SYSTEM_INFORMATION_TYPE_7 (buffer, 0, &(data->Data.fld_c_SYSTEM_INFORMATION_TYPE_7), bitLen);
		
			return retLen;
		}
		/* Detect signal SYSTEM_INFORMATION_TYPE_8 */
		case 0x0618: {
			SETPRESENT_TPLENDownlink_Data (data, ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_8);
			INIT_c_SYSTEM_INFORMATION_TYPE_8 (&data->Data.fld_c_SYSTEM_INFORMATION_TYPE_8);
			retLen = DECODE_c_SYSTEM_INFORMATION_TYPE_8 (buffer, 0, &(data->Data.fld_c_SYSTEM_INFORMATION_TYPE_8), bitLen);
		
			return retLen;
		}
		/* Detect signal SYSTEM_INFORMATION_TYPE_9 */
		case 0x0604: {
			SETPRESENT_TPLENDownlink_Data (data, ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_9);
			INIT_c_SYSTEM_INFORMATION_TYPE_9 (&data->Data.fld_c_SYSTEM_INFORMATION_TYPE_9);
			retLen = DECODE_c_SYSTEM_INFORMATION_TYPE_9 (buffer, 0, &(data->Data.fld_c_SYSTEM_INFORMATION_TYPE_9), bitLen);
		
			return retLen;
		}
		/* Detect signal SYSTEM_INFORMATION_TYPE_13 */
		case 0x0600: {
			SETPRESENT_TPLENDownlink_Data (data, ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_13);
			INIT_c_SYSTEM_INFORMATION_TYPE_13 (&data->Data.fld_c_SYSTEM_INFORMATION_TYPE_13);
			retLen = DECODE_c_SYSTEM_INFORMATION_TYPE_13 (buffer, 0, &(data->Data.fld_c_SYSTEM_INFORMATION_TYPE_13), bitLen);
		
			return retLen;
		}
		/* Detect signal EXTENDED_MEASUREMENT_ORDER */
		case 0x0637: {
			SETPRESENT_TPLENDownlink_Data (data, ID_PLENDownlink_EXTENDED_MEASUREMENT_ORDER);
			INIT_c_EXTENDED_MEASUREMENT_ORDER (&data->Data.fld_c_EXTENDED_MEASUREMENT_ORDER);
			retLen = DECODE_c_EXTENDED_MEASUREMENT_ORDER (buffer, 0, &(data->Data.fld_c_EXTENDED_MEASUREMENT_ORDER), bitLen);
		
			return retLen;
		}

	}
	data->Type = ID_PLENDownlink_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_PLENDownlink (const char* buffer, int len, TPLENDownlink_Data* data)
	{
              /*
              if (SetDecode_PLENDownlink (buffer, data, len*8) < 0)
              {
		       return ED_FALSE;
		}
		else 
		{
		       return ED_TRUE;
              }
              */
             return SetDecode_PLENDownlink (buffer, data, len*8);  
	}
#endif

#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif

#ifndef XSCT_CMICRO
#define ED_SDL_ACCESS_UNION(signalName,position) (((yPDP_##signalName)SignalIn)->Param##position)
#else
#define ED_SDL_ACCESS_UNION(signalName,position) (signalData.data_##signalName.Param##position)
#endif



int SetDecode_Downlink_RLC_MAC (const char* buffer, TDownlink_RLC_MAC_Data* data, int bitLen)
{
	int retLen = 0;
	
	/*-----------------------------------------------------------------
		Key is set to a single value containing protocol discriminator,
		skip indicator and message type.
		For example, message ASSIGNMENT_COMMAND has:
			skip indicator         = 0000 (0x0)
			protocol discriminator = 0110 (0x6)
			message type           = 00101110 (0x2E)
		In this case, key will be set to 0x602E.
		Skip indicator could be in some cases a transaction identifier.
		In such cases, it will be set to 0 for matching purposes.
	------------------------------------------------------------------*/
	unsigned /****/ int key /*1*/ = ((unsigned char)buffer [0])>> 2/*2*/;/*3*/
	data->MessageType = (int)key;
	
	switch (key & 0xFF3F) {
			/* Detect signal Packet_Cell_Change_Order */
		case 0x0001: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_Packet_Cell_Change_Order);
			INIT_c_Packet_Cell_Change_Order (&data->Data.fld_c_Packet_Cell_Change_Order);
			retLen = DECODE_c_Packet_Cell_Change_Order (buffer, 0, &(data->Data.fld_c_Packet_Cell_Change_Order), bitLen);
		
			return retLen;
		}
		/* Detect signal Packet_Downlink_Assignment */
		case 0x0002: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_Packet_Downlink_Assignment);
			INIT_c_Packet_Downlink_Assignment (&data->Data.fld_c_Packet_Downlink_Assignment);
			retLen = DECODE_c_Packet_Downlink_Assignment (buffer, 0, &(data->Data.fld_c_Packet_Downlink_Assignment), bitLen);
		
			return retLen;
		}
		/* Detect signal Packet_Measurement_Order */
		case 0x0003: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_Packet_Measurement_Order);
			INIT_c_Packet_Measurement_Order (&data->Data.fld_c_Packet_Measurement_Order);
			retLen = DECODE_c_Packet_Measurement_Order (buffer, 0, &(data->Data.fld_c_Packet_Measurement_Order), bitLen);
		
			return retLen;
		}
		/* Detect signal Packet_Polling_Request */
		case 0x0004: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_Packet_Polling_Request);
			INIT_c_Packet_Polling_Request (&data->Data.fld_c_Packet_Polling_Request);
			retLen = DECODE_c_Packet_Polling_Request (buffer, 0, &(data->Data.fld_c_Packet_Polling_Request), bitLen);
		
			return retLen;
		}
		/* Detect signal Packet_Power_Control_Timing_Advance */
		case 0x0005: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_Packet_Power_Control_Timing_Advance);
			INIT_c_Packet_Power_Control_Timing_Advance (&data->Data.fld_c_Packet_Power_Control_Timing_Advance);
			retLen = DECODE_c_Packet_Power_Control_Timing_Advance (buffer, 0, &(data->Data.fld_c_Packet_Power_Control_Timing_Advance), bitLen);
		
			return retLen;
		}
		/* Detect signal Packet_Queueing_Notification */
		case 0x0006: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_Packet_Queueing_Notification);
			INIT_c_Packet_Queueing_Notification (&data->Data.fld_c_Packet_Queueing_Notification);
			retLen = DECODE_c_Packet_Queueing_Notification (buffer, 0, &(data->Data.fld_c_Packet_Queueing_Notification), bitLen);
		
			return retLen;
		}
		/* Detect signal Packet_Timeslot_Reconfigure */
		case 0x0007: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_Packet_Timeslot_Reconfigure);
			INIT_c_Packet_Timeslot_Reconfigure (&data->Data.fld_c_Packet_Timeslot_Reconfigure);
			retLen = DECODE_c_Packet_Timeslot_Reconfigure (buffer, 0, &(data->Data.fld_c_Packet_Timeslot_Reconfigure), bitLen);
		
			return retLen;
		}
		/* Detect signal Packet_TBF_Release */
		case 0x0008: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_Packet_TBF_Release);
			INIT_c_Packet_TBF_Release (&data->Data.fld_c_Packet_TBF_Release);
			retLen = DECODE_c_Packet_TBF_Release (buffer, 0, &(data->Data.fld_c_Packet_TBF_Release), bitLen);
		
			return retLen;
		}
		/* Detect signal Packet_Uplink_Ack_Nack */
		case 0x0009: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_Packet_Uplink_Ack_Nack);
			INIT_c_Packet_Uplink_Ack_Nack (&data->Data.fld_c_Packet_Uplink_Ack_Nack);
			retLen = DECODE_c_Packet_Uplink_Ack_Nack (buffer, 0, &(data->Data.fld_c_Packet_Uplink_Ack_Nack), bitLen);
		
			return retLen;
		}
		/* Detect signal Packet_Uplink_Assignment */
		case 0x000A: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_Packet_Uplink_Assignment);
			INIT_c_Packet_Uplink_Assignment (&data->Data.fld_c_Packet_Uplink_Assignment);
			retLen = DECODE_c_Packet_Uplink_Assignment (buffer, 0, &(data->Data.fld_c_Packet_Uplink_Assignment), bitLen);
		
			return retLen;
		}
		/* Detect signal Packet_Cell_Change_Continue */
		case 0x000B: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_Packet_Cell_Change_Continue);
			INIT_c_Packet_Cell_Change_Continue (&data->Data.fld_c_Packet_Cell_Change_Continue);
			retLen = DECODE_c_Packet_Cell_Change_Continue (buffer, 0, &(data->Data.fld_c_Packet_Cell_Change_Continue), bitLen);
		
			return retLen;
		}
		/* Detect signal Packet_Neighbour_Cell_Data */
		case 0x000C: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_Packet_Neighbour_Cell_Data);
			INIT_c_Packet_Neighbour_Cell_Data (&data->Data.fld_c_Packet_Neighbour_Cell_Data);
			retLen = DECODE_c_Packet_Neighbour_Cell_Data (buffer, 0, &(data->Data.fld_c_Packet_Neighbour_Cell_Data), bitLen);
		
			return retLen;
		}
		/* Detect signal Packet_Serving_Cell_Data */
		case 0x000D: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_Packet_Serving_Cell_Data);
			INIT_c_Packet_Serving_Cell_Data (&data->Data.fld_c_Packet_Serving_Cell_Data);
			retLen = DECODE_c_Packet_Serving_Cell_Data (buffer, 0, &(data->Data.fld_c_Packet_Serving_Cell_Data), bitLen);
		
			return retLen;
		}
		/* Detect signal Packet_Access_Reject */
		case 0x0021: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_Packet_Access_Reject);
			INIT_c_Packet_Access_Reject (&data->Data.fld_c_Packet_Access_Reject);
			retLen = DECODE_c_Packet_Access_Reject (buffer, 0, &(data->Data.fld_c_Packet_Access_Reject), bitLen);
		
			return retLen;
		}
		/* Detect signal Packet_Paging_Request */
		case 0x0022: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_Packet_Paging_Request);
			INIT_c_Packet_Paging_Request (&data->Data.fld_c_Packet_Paging_Request);
			retLen = DECODE_c_Packet_Paging_Request (buffer, 0, &(data->Data.fld_c_Packet_Paging_Request), bitLen);
		
			return retLen;
		}
		/* Detect signal Packet_PDCH_Release */
		case 0x0023: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_Packet_PDCH_Release);
			INIT_c_Packet_PDCH_Release (&data->Data.fld_c_Packet_PDCH_Release);
			retLen = DECODE_c_Packet_PDCH_Release (buffer, 0, &(data->Data.fld_c_Packet_PDCH_Release), bitLen);
		
			return retLen;
		}
		/* Detect signal Packet_PRACH_Parameters */
		case 0x0024: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_Packet_PRACH_Parameters);
			INIT_c_Packet_PRACH_Parameters (&data->Data.fld_c_Packet_PRACH_Parameters);
			retLen = DECODE_c_Packet_PRACH_Parameters (buffer, 0, &(data->Data.fld_c_Packet_PRACH_Parameters), bitLen);
		
			return retLen;
		}
		/* Detect signal Packet_Downlink_Dummy_Control_Block */
		case 0x0025: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_Packet_Downlink_Dummy_Control_Block);
			INIT_c_Packet_Downlink_Dummy_Control_Block (&data->Data.fld_c_Packet_Downlink_Dummy_Control_Block);
			retLen = DECODE_c_Packet_Downlink_Dummy_Control_Block (buffer, 0, &(data->Data.fld_c_Packet_Downlink_Dummy_Control_Block), bitLen);
		
			return retLen;
		}
		/* Detect signal PSI1 */
		case 0x0031: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_PSI1);
			INIT_c_PSI1 (&data->Data.fld_c_PSI1);
			retLen = DECODE_c_PSI1 (buffer, 0, &(data->Data.fld_c_PSI1), bitLen);
		
			return retLen;
		}
		/* Detect signal PSI2 */
		case 0x0032: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_PSI2);
			INIT_c_PSI2 (&data->Data.fld_c_PSI2);
			retLen = DECODE_c_PSI2 (buffer, 0, &(data->Data.fld_c_PSI2), bitLen);
		
			return retLen;
		}
		/* Detect signal PSI3 */
		case 0x0033: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_PSI3);
			INIT_c_PSI3 (&data->Data.fld_c_PSI3);
			retLen = DECODE_c_PSI3 (buffer, 0, &(data->Data.fld_c_PSI3), bitLen);
		
			return retLen;
		}
		/* Detect signal PSI3_bis */
		case 0x0034: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_PSI3_bis);
			INIT_c_PSI3_bis (&data->Data.fld_c_PSI3_bis);
			retLen = DECODE_c_PSI3_bis (buffer, 0, &(data->Data.fld_c_PSI3_bis), bitLen);
		
			return retLen;
		}
		/* Detect signal PSI4 */
		case 0x0035: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_PSI4);
			INIT_c_PSI4 (&data->Data.fld_c_PSI4);
			retLen = DECODE_c_PSI4 (buffer, 0, &(data->Data.fld_c_PSI4), bitLen);
		
			return retLen;
		}
		/* Detect signal PSI5 */
		case 0x0036: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_PSI5);
			INIT_c_PSI5 (&data->Data.fld_c_PSI5);
			retLen = DECODE_c_PSI5 (buffer, 0, &(data->Data.fld_c_PSI5), bitLen);
		
			return retLen;
		}
		/* Detect signal PSI13 */
		case 0x0037: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_PSI13);
			INIT_c_PSI13 (&data->Data.fld_c_PSI13);
			retLen = DECODE_c_PSI13 (buffer, 0, &(data->Data.fld_c_PSI13), bitLen);
		
			return retLen;
		}
		/* Detect signal PSI14 */
		case 0x003A: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_PSI14);
			INIT_c_PSI14 (&data->Data.fld_c_PSI14);
			retLen = DECODE_c_PSI14 (buffer, 0, &(data->Data.fld_c_PSI14), bitLen);
		
			return retLen;
		}
		/* Detect signal PSI3_ter */
		case 0x003C: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_PSI3_ter);
			INIT_c_PSI3_ter (&data->Data.fld_c_PSI3_ter);
			retLen = DECODE_c_PSI3_ter (buffer, 0, &(data->Data.fld_c_PSI3_ter), bitLen);
		
			return retLen;
		}
		/* Detect signal PSI3_quater */
		case 0x003D: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_PSI3_quater);
			INIT_c_PSI3_quater (&data->Data.fld_c_PSI3_quater);
			retLen = DECODE_c_PSI3_quater (buffer, 0, &(data->Data.fld_c_PSI3_quater), bitLen);
		
			return retLen;
		}
		/* Detect signal Packet_Serving_Cell_SI */
		case 0x0020: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_Packet_Serving_Cell_SI);
			INIT_c_Packet_Serving_Cell_SI (&data->Data.fld_c_Packet_Serving_Cell_SI);
			retLen = DECODE_c_Packet_Serving_Cell_SI (buffer, 0, &(data->Data.fld_c_Packet_Serving_Cell_SI), bitLen);
		
			return retLen;
		}
		/* Detect signal PS_Handover_Command */
		case 0x0015: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_PS_Handover_Command);
			INIT_c_PS_Handover_Command (&data->Data.fld_c_PS_Handover_Command);
			retLen = DECODE_c_PS_Handover_Command (buffer, 0, &(data->Data.fld_c_PS_Handover_Command), bitLen);
		
			return retLen;
		}
		/* Detect signal Packet_Physical_Information */
		case 0x0016: {
			SETPRESENT_TDownlink_RLC_MAC_Data (data, ID_Downlink_RLC_MAC_Packet_Physical_Information);
			INIT_c_Packet_Physical_Information (&data->Data.fld_c_Packet_Physical_Information);
			retLen = DECODE_c_Packet_Physical_Information (buffer, 0, &(data->Data.fld_c_Packet_Physical_Information), bitLen);
		
			return retLen;
		}

	}
	data->Type = ID_Downlink_RLC_MAC_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_Downlink_RLC_MAC (const char* buffer, int len, TDownlink_RLC_MAC_Data* data)
	{
             /*
              if (SetDecode_Downlink_RLC_MAC (buffer, data, len*8) < 0) {
                      return ED_FALSE;
              }
              else {
                      return ED_TRUE;
              }
              */
              return SetDecode_Downlink_RLC_MAC (buffer, data, len*8);   
	}
#endif


/*lint +e958*/
/*lint +e961*/
/*lint +e830*/
/*lint +e744*/
/*lint +e760*/

