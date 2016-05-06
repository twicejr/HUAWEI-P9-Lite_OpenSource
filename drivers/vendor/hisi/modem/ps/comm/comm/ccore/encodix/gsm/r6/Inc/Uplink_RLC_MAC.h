/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.83
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __Uplink_RLC_MAC_h
#define __Uplink_RLC_MAC_h
#include "ed_lib.h"
#include "ed_c.h"
#include "ed_user.h"
#include "endec_configs.h"


#ifdef __cplusplus
	extern "C" {
#endif

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Cell_Change_Failure".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_Packet_Cell_Change_Failure (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Cell_Change_Failure* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Cell_Change_Failure".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_Packet_Cell_Change_Failure (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Cell_Change_Failure* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Control_Acknowledgement".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_Packet_Control_Acknowledgement (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Control_Acknowledgement* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Control_Acknowledgement".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_Packet_Control_Acknowledgement (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Control_Acknowledgement* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Downlink_Ack_Nack".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_Packet_Downlink_Ack_Nack (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Downlink_Ack_Nack* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Downlink_Ack_Nack".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_Packet_Downlink_Ack_Nack (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Downlink_Ack_Nack* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Uplink_Dummy_Control_Block".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_Packet_Uplink_Dummy_Control_Block (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Uplink_Dummy_Control_Block* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Uplink_Dummy_Control_Block".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_Packet_Uplink_Dummy_Control_Block (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Uplink_Dummy_Control_Block* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Measurement_Report".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_Packet_Measurement_Report (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Measurement_Report* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Measurement_Report".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_Packet_Measurement_Report (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Measurement_Report* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Resource_Request".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_Packet_Resource_Request (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Resource_Request* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Resource_Request".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_Packet_Resource_Request (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Resource_Request* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Mobile_TBF_Status".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_Packet_Mobile_TBF_Status (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Mobile_TBF_Status* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Mobile_TBF_Status".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_Packet_Mobile_TBF_Status (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Mobile_TBF_Status* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_PSI_Status".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_Packet_PSI_Status (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_PSI_Status* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_PSI_Status".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_Packet_PSI_Status (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_PSI_Status* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EGPRS_Packet_Downlink_Ack_Nack".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_EGPRS_Packet_Downlink_Ack_Nack (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_EGPRS_Packet_Downlink_Ack_Nack* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EGPRS_Packet_Downlink_Ack_Nack".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_EGPRS_Packet_Downlink_Ack_Nack (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_EGPRS_Packet_Downlink_Ack_Nack* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Enhanced_Measurement_Report".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_Packet_Enhanced_Measurement_Report (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Enhanced_Measurement_Report* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Enhanced_Measurement_Report".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_Packet_Enhanced_Measurement_Report (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Enhanced_Measurement_Report* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Additional_MS_Radio_Access_Capabilities".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_Additional_MS_Radio_Access_Capabilities (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Additional_MS_Radio_Access_Capabilities* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Additional_MS_Radio_Access_Capabilities".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_Additional_MS_Radio_Access_Capabilities (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Additional_MS_Radio_Access_Capabilities* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Cell_Change_Notification".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_Packet_Cell_Change_Notification (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Cell_Change_Notification* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Cell_Change_Notification".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_Packet_Cell_Change_Notification (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Cell_Change_Notification* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_SI_Status".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_Packet_SI_Status (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_SI_Status* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_SI_Status".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_Packet_SI_Status (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_SI_Status* ED_CONST Source);

int Match_c_Packet_Cell_Change_Failure (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_Control_Acknowledgement (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_Downlink_Ack_Nack (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_Uplink_Dummy_Control_Block (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_Measurement_Report (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_Resource_Request (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_Mobile_TBF_Status (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_PSI_Status (const char* Buffer, ED_CONST long BitOffset);
int Match_c_EGPRS_Packet_Downlink_Ack_Nack (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_Enhanced_Measurement_Report (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Additional_MS_Radio_Access_Capabilities (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_Cell_Change_Notification (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_SI_Status (const char* Buffer, ED_CONST long BitOffset);

#ifdef __cplusplus
	};
#endif
#endif

