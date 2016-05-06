/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.83
	GENERATOR: ed-c-recog
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __ed_c_recog_h
#define __ed_c_recog_h
#include "ed_c.h"

#include "ed_user.h"
#define ED_MAXSIZE 600
#include "endec_configs.h"

#ifdef __cplusplus
	extern "C" {
#endif

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group L3Downlink
--------------------------------------------------------------------*/
typedef enum {
	ID_L3Downlink_Unrecognized = 0,
	ID_L3Downlink_ASSIGNMENT_COMMAND,
	ID_L3Downlink_CHANNEL_MODE_MODIFY,
	ID_L3Downlink_CHANNEL_RELEASE,
	ID_L3Downlink_CIPHERING_MODE_COMMAND,
	ID_L3Downlink_CLASSMARK_ENQUIRY,
	ID_L3Downlink_FREQUENCY_REDEFINITION,
	ID_L3Downlink_HANDOVER_COMMAND,
	ID_L3Downlink_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND,
	ID_L3Downlink_PHYSICAL_INFORMATION,
	ID_L3Downlink_RR_STATUS,
	ID_L3Downlink_APPLICATION_INFORMATION
} TL3Downlink_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group L3Downlink
--------------------------------------------------------------------*/
typedef struct {
	TL3Downlink_Type Type;
	int ProtocolDiscriminator;
	int MessageType;
	union {
		c_ASSIGNMENT_COMMAND fld_c_ASSIGNMENT_COMMAND;
		c_CHANNEL_MODE_MODIFY fld_c_CHANNEL_MODE_MODIFY;
		c_CHANNEL_RELEASE fld_c_CHANNEL_RELEASE;
		c_CIPHERING_MODE_COMMAND fld_c_CIPHERING_MODE_COMMAND;
		c_CLASSMARK_ENQUIRY fld_c_CLASSMARK_ENQUIRY;
		c_FREQUENCY_REDEFINITION fld_c_FREQUENCY_REDEFINITION;
		c_HANDOVER_COMMAND fld_c_HANDOVER_COMMAND;
		c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND fld_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND;
		c_PHYSICAL_INFORMATION fld_c_PHYSICAL_INFORMATION;
		c_RR_STATUS fld_c_RR_STATUS;
		c_APPLICATION_INFORMATION fld_c_APPLICATION_INFORMATION;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TL3Downlink_Data;
#define INIT_TL3Downlink_Data(sp) (ED_RESET_MEM ((sp), sizeof (TL3Downlink_Data)), (sp)->Type=ID_L3Downlink_Unrecognized)
void FREE_TL3Downlink_Data (TL3Downlink_Data* sp);

void SETPRESENT_TL3Downlink_Data(TL3Downlink_Data* sp, TL3Downlink_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group L3Uplink
--------------------------------------------------------------------*/
typedef enum {
	ID_L3Uplink_Unrecognized = 0,
	ID_L3Uplink_ASSIGNMENT_COMPLETE,
	ID_L3Uplink_ASSIGNMENT_FAILURE,
	ID_L3Uplink_CHANNEL_MODE_MODIFY_ACKNOWLEDGE,
	ID_L3Uplink_CIPHERING_MODE_COMPLETE,
	ID_L3Uplink_CLASSMARK_CHANGE,
	ID_L3Uplink_GPRS_SUSPENSION_REQUEST,
	ID_L3Uplink_HANDOVER_COMPLETE,
	ID_L3Uplink_HANDOVER_FAILURE,
	ID_L3Uplink_MEASUREMENT_REPORT,
	ID_L3Uplink_PAGING_RESPONSE,
	ID_L3Uplink_RR_INITIALISATION_REQUEST,
	ID_L3Uplink_RR_STATUS,
	ID_L3Uplink_APPLICATION_INFORMATION
} TL3Uplink_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group L3Uplink
--------------------------------------------------------------------*/
typedef struct {
	TL3Uplink_Type Type;
	int ProtocolDiscriminator;
	int MessageType;
	union {
		c_ASSIGNMENT_COMPLETE fld_c_ASSIGNMENT_COMPLETE;
		c_ASSIGNMENT_FAILURE fld_c_ASSIGNMENT_FAILURE;
		c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE fld_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE;
		c_CIPHERING_MODE_COMPLETE fld_c_CIPHERING_MODE_COMPLETE;
		c_CLASSMARK_CHANGE fld_c_CLASSMARK_CHANGE;
		c_GPRS_SUSPENSION_REQUEST fld_c_GPRS_SUSPENSION_REQUEST;
		c_HANDOVER_COMPLETE fld_c_HANDOVER_COMPLETE;
		c_HANDOVER_FAILURE fld_c_HANDOVER_FAILURE;
		c_MEASUREMENT_REPORT fld_c_MEASUREMENT_REPORT;
		c_PAGING_RESPONSE fld_c_PAGING_RESPONSE;
		c_RR_INITIALISATION_REQUEST fld_c_RR_INITIALISATION_REQUEST;
		c_RR_STATUS fld_c_RR_STATUS;
		c_APPLICATION_INFORMATION fld_c_APPLICATION_INFORMATION;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TL3Uplink_Data;
#define INIT_TL3Uplink_Data(sp) (ED_RESET_MEM ((sp), sizeof (TL3Uplink_Data)), (sp)->Type=ID_L3Uplink_Unrecognized)
void FREE_TL3Uplink_Data (TL3Uplink_Data* sp);

void SETPRESENT_TL3Uplink_Data(TL3Uplink_Data* sp, TL3Uplink_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group PLENDownlink
--------------------------------------------------------------------*/
typedef enum {
	ID_PLENDownlink_Unrecognized = 0,
	ID_PLENDownlink_IMMEDIATE_ASSIGNMENT,
	ID_PLENDownlink_IMMEDIATE_ASSIGNMENT_EXTENDED,
	ID_PLENDownlink_IMMEDIATE_ASSIGNMENT_REJECT,
	ID_PLENDownlink_PAGING_REQUEST_TYPE_1,
	ID_PLENDownlink_PAGING_REQUEST_TYPE_2,
	ID_PLENDownlink_PAGING_REQUEST_TYPE_3,
	ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_1,
	ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_2,
	ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_2BIS,
	ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_2TER,
	ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_2QUATER,
	ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_3,
	ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_4,
	ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_5,
	ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_5BIS,
	ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_5TER,
	ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_6,
	ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_7,
	ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_8,
	ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_9,
	ID_PLENDownlink_SYSTEM_INFORMATION_TYPE_13
} TPLENDownlink_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group PLENDownlink
--------------------------------------------------------------------*/
typedef struct {
	TPLENDownlink_Type Type;
	int ProtocolDiscriminator;
	int MessageType;
	union {
		c_IMMEDIATE_ASSIGNMENT fld_c_IMMEDIATE_ASSIGNMENT;
		c_IMMEDIATE_ASSIGNMENT_EXTENDED fld_c_IMMEDIATE_ASSIGNMENT_EXTENDED;
		c_IMMEDIATE_ASSIGNMENT_REJECT fld_c_IMMEDIATE_ASSIGNMENT_REJECT;
		c_PAGING_REQUEST_TYPE_1 fld_c_PAGING_REQUEST_TYPE_1;
		c_PAGING_REQUEST_TYPE_2 fld_c_PAGING_REQUEST_TYPE_2;
		c_PAGING_REQUEST_TYPE_3 fld_c_PAGING_REQUEST_TYPE_3;
		c_SYSTEM_INFORMATION_TYPE_1 fld_c_SYSTEM_INFORMATION_TYPE_1;
		c_SYSTEM_INFORMATION_TYPE_2 fld_c_SYSTEM_INFORMATION_TYPE_2;
		c_SYSTEM_INFORMATION_TYPE_2BIS fld_c_SYSTEM_INFORMATION_TYPE_2BIS;
		c_SYSTEM_INFORMATION_TYPE_2TER fld_c_SYSTEM_INFORMATION_TYPE_2TER;
		c_SYSTEM_INFORMATION_TYPE_2QUATER fld_c_SYSTEM_INFORMATION_TYPE_2QUATER;
		c_SYSTEM_INFORMATION_TYPE_3 fld_c_SYSTEM_INFORMATION_TYPE_3;
		c_SYSTEM_INFORMATION_TYPE_4 fld_c_SYSTEM_INFORMATION_TYPE_4;
		c_SYSTEM_INFORMATION_TYPE_5 fld_c_SYSTEM_INFORMATION_TYPE_5;
		c_SYSTEM_INFORMATION_TYPE_5BIS fld_c_SYSTEM_INFORMATION_TYPE_5BIS;
		c_SYSTEM_INFORMATION_TYPE_5TER fld_c_SYSTEM_INFORMATION_TYPE_5TER;
		c_SYSTEM_INFORMATION_TYPE_6 fld_c_SYSTEM_INFORMATION_TYPE_6;
		c_SYSTEM_INFORMATION_TYPE_7 fld_c_SYSTEM_INFORMATION_TYPE_7;
		c_SYSTEM_INFORMATION_TYPE_8 fld_c_SYSTEM_INFORMATION_TYPE_8;
		c_SYSTEM_INFORMATION_TYPE_9 fld_c_SYSTEM_INFORMATION_TYPE_9;
		c_SYSTEM_INFORMATION_TYPE_13 fld_c_SYSTEM_INFORMATION_TYPE_13;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TPLENDownlink_Data;
#define INIT_TPLENDownlink_Data(sp) (ED_RESET_MEM ((sp), sizeof (TPLENDownlink_Data)), (sp)->Type=ID_PLENDownlink_Unrecognized)
void FREE_TPLENDownlink_Data (TPLENDownlink_Data* sp);

void SETPRESENT_TPLENDownlink_Data(TPLENDownlink_Data* sp, TPLENDownlink_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group Downlink_RLC_MAC
--------------------------------------------------------------------*/
typedef enum {
	ID_Downlink_RLC_MAC_Unrecognized = 0,
	ID_Downlink_RLC_MAC_Packet_Cell_Change_Order,
	ID_Downlink_RLC_MAC_Packet_Downlink_Assignment,
	ID_Downlink_RLC_MAC_Packet_Measurement_Order,
	ID_Downlink_RLC_MAC_Packet_Polling_Request,
	ID_Downlink_RLC_MAC_Packet_Power_Control_Timing_Advance,
	ID_Downlink_RLC_MAC_Packet_Queueing_Notification,
	ID_Downlink_RLC_MAC_Packet_Timeslot_Reconfigure,
	ID_Downlink_RLC_MAC_Packet_TBF_Release,
	ID_Downlink_RLC_MAC_Packet_Uplink_Ack_Nack,
	ID_Downlink_RLC_MAC_Packet_Uplink_Assignment,
	ID_Downlink_RLC_MAC_Packet_Cell_Change_Continue,
	ID_Downlink_RLC_MAC_Packet_Neighbour_Cell_Data,
	ID_Downlink_RLC_MAC_Packet_Serving_Cell_Data,
	ID_Downlink_RLC_MAC_Packet_Access_Reject,
	ID_Downlink_RLC_MAC_Packet_Paging_Request,
	ID_Downlink_RLC_MAC_Packet_PDCH_Release,
	ID_Downlink_RLC_MAC_Packet_PRACH_Parameters,
	ID_Downlink_RLC_MAC_Packet_Downlink_Dummy_Control_Block,
	ID_Downlink_RLC_MAC_PSI1,
	ID_Downlink_RLC_MAC_PSI2,
	ID_Downlink_RLC_MAC_PSI3,
	ID_Downlink_RLC_MAC_PSI3_bis,
	ID_Downlink_RLC_MAC_PSI4,
	ID_Downlink_RLC_MAC_PSI5,
	ID_Downlink_RLC_MAC_PSI13,
	ID_Downlink_RLC_MAC_PSI14,
	ID_Downlink_RLC_MAC_PSI3_ter,
	ID_Downlink_RLC_MAC_PSI3_quater,
	ID_Downlink_RLC_MAC_Packet_Serving_Cell_SI
} TDownlink_RLC_MAC_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group Downlink_RLC_MAC
--------------------------------------------------------------------*/
typedef struct {
	TDownlink_RLC_MAC_Type Type;
	int MessageType;
	union {
		c_Packet_Cell_Change_Order fld_c_Packet_Cell_Change_Order;
		c_Packet_Downlink_Assignment fld_c_Packet_Downlink_Assignment;
		c_Packet_Measurement_Order fld_c_Packet_Measurement_Order;
		c_Packet_Polling_Request fld_c_Packet_Polling_Request;
		c_Packet_Power_Control_Timing_Advance fld_c_Packet_Power_Control_Timing_Advance;
		c_Packet_Queueing_Notification fld_c_Packet_Queueing_Notification;
		c_Packet_Timeslot_Reconfigure fld_c_Packet_Timeslot_Reconfigure;
		c_Packet_TBF_Release fld_c_Packet_TBF_Release;
		c_Packet_Uplink_Ack_Nack fld_c_Packet_Uplink_Ack_Nack;
		c_Packet_Uplink_Assignment fld_c_Packet_Uplink_Assignment;
		c_Packet_Cell_Change_Continue fld_c_Packet_Cell_Change_Continue;
		c_Packet_Neighbour_Cell_Data fld_c_Packet_Neighbour_Cell_Data;
		c_Packet_Serving_Cell_Data fld_c_Packet_Serving_Cell_Data;
		c_Packet_Access_Reject fld_c_Packet_Access_Reject;
		c_Packet_Paging_Request fld_c_Packet_Paging_Request;
		c_Packet_PDCH_Release fld_c_Packet_PDCH_Release;
		c_Packet_PRACH_Parameters fld_c_Packet_PRACH_Parameters;
		c_Packet_Downlink_Dummy_Control_Block fld_c_Packet_Downlink_Dummy_Control_Block;
		c_PSI1 fld_c_PSI1;
		c_PSI2 fld_c_PSI2;
		c_PSI3 fld_c_PSI3;
		c_PSI3_bis fld_c_PSI3_bis;
		c_PSI4 fld_c_PSI4;
		c_PSI5 fld_c_PSI5;
		c_PSI13 fld_c_PSI13;
		c_PSI14 fld_c_PSI14;
		c_PSI3_ter fld_c_PSI3_ter;
		c_PSI3_quater fld_c_PSI3_quater;
		c_Packet_Serving_Cell_SI fld_c_Packet_Serving_Cell_SI;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TDownlink_RLC_MAC_Data;
#define INIT_TDownlink_RLC_MAC_Data(sp) (ED_RESET_MEM ((sp), sizeof (TDownlink_RLC_MAC_Data)), (sp)->Type=ID_Downlink_RLC_MAC_Unrecognized)
void FREE_TDownlink_RLC_MAC_Data (TDownlink_RLC_MAC_Data* sp);

void SETPRESENT_TDownlink_RLC_MAC_Data(TDownlink_RLC_MAC_Data* sp, TDownlink_RLC_MAC_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group Uplink_RLC_MAC
--------------------------------------------------------------------*/
typedef enum {
	ID_Uplink_RLC_MAC_Unrecognized = 0,
	ID_Uplink_RLC_MAC_Packet_Cell_Change_Failure,
	ID_Uplink_RLC_MAC_Packet_Control_Acknowledgement,
	ID_Uplink_RLC_MAC_Packet_Downlink_Ack_Nack,
	ID_Uplink_RLC_MAC_Packet_Uplink_Dummy_Control_Block,
	ID_Uplink_RLC_MAC_Packet_Measurement_Report,
	ID_Uplink_RLC_MAC_Packet_Resource_Request,
	ID_Uplink_RLC_MAC_Packet_Mobile_TBF_Status,
	ID_Uplink_RLC_MAC_Packet_PSI_Status,
	ID_Uplink_RLC_MAC_EGPRS_Packet_Downlink_Ack_Nack,
	ID_Uplink_RLC_MAC_Packet_Enhanced_Measurement_Report,
	ID_Uplink_RLC_MAC_Additional_MS_Radio_Access_Capabilities,
	ID_Uplink_RLC_MAC_Packet_Cell_Change_Notification,
	ID_Uplink_RLC_MAC_Packet_SI_Status
} TUplink_RLC_MAC_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group Uplink_RLC_MAC
--------------------------------------------------------------------*/
typedef struct {
	TUplink_RLC_MAC_Type Type;
	int MessageType;
	union {
		c_Packet_Cell_Change_Failure fld_c_Packet_Cell_Change_Failure;
		c_Packet_Control_Acknowledgement fld_c_Packet_Control_Acknowledgement;
		c_Packet_Downlink_Ack_Nack fld_c_Packet_Downlink_Ack_Nack;
		c_Packet_Uplink_Dummy_Control_Block fld_c_Packet_Uplink_Dummy_Control_Block;
		c_Packet_Measurement_Report fld_c_Packet_Measurement_Report;
		c_Packet_Resource_Request fld_c_Packet_Resource_Request;
		c_Packet_Mobile_TBF_Status fld_c_Packet_Mobile_TBF_Status;
		c_Packet_PSI_Status fld_c_Packet_PSI_Status;
		c_EGPRS_Packet_Downlink_Ack_Nack fld_c_EGPRS_Packet_Downlink_Ack_Nack;
		c_Packet_Enhanced_Measurement_Report fld_c_Packet_Enhanced_Measurement_Report;
		c_Additional_MS_Radio_Access_Capabilities fld_c_Additional_MS_Radio_Access_Capabilities;
		c_Packet_Cell_Change_Notification fld_c_Packet_Cell_Change_Notification;
		c_Packet_SI_Status fld_c_Packet_SI_Status;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TUplink_RLC_MAC_Data;
#define INIT_TUplink_RLC_MAC_Data(sp) (ED_RESET_MEM ((sp), sizeof (TUplink_RLC_MAC_Data)), (sp)->Type=ID_Uplink_RLC_MAC_Unrecognized)
void FREE_TUplink_RLC_MAC_Data (TUplink_RLC_MAC_Data* sp);

void SETPRESENT_TUplink_RLC_MAC_Data(TUplink_RLC_MAC_Data* sp, TUplink_RLC_MAC_Type toBeSetPresent);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_L3Downlink (const char* buffer, TL3Downlink_Data* data, int bitLen);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_L3Downlink (const char* buffer, int len, TL3Downlink_Data* data);
#endif


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_PLENDownlink (const char* buffer, TPLENDownlink_Data* data, int bitLen);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_PLENDownlink (const char* buffer, int len, TPLENDownlink_Data* data);
#endif


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_Downlink_RLC_MAC (const char* buffer, TDownlink_RLC_MAC_Data* data, int bitLen);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_Downlink_RLC_MAC (const char* buffer, int len, TDownlink_RLC_MAC_Data* data);
#endif

#ifdef __cplusplus
	};
#endif
#endif

