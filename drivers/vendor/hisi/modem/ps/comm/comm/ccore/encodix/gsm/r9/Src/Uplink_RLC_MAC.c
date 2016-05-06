/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.83
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#include "Uplink_RLC_MAC.h"
#include "ed_c_known_ie.h"
#include "ed_tlv.h"
#include "CSN1DataTypes.h"



/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_UPLINK_RLC_MAC_C
/*lint -e961*/
/*lint -e958*/

/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Cell_Change_Failure
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_Packet_Cell_Change_Failure (char* Buffer, long BitOffset, const c_Packet_Cell_Change_Failure* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 0, 6);
		CurrOfs += 6;
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part */
		Len = ENCODE_c_Packet_Cell_Change_Failure_message_content (Buffer, CurrOfs, &(Source->contents));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:558> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Cell_Change_Failure
-----------------------------------------------------------------*/
long ENCODE_c_Packet_Cell_Change_Failure (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Cell_Change_Failure* ED_CONST Source)
{
	return L3_ENCODE_c_Packet_Cell_Change_Failure (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Cell_Change_Failure
-----------------------------------------------------------------*/
long ENCODE_BODY_c_Packet_Cell_Change_Failure (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Cell_Change_Failure* ED_CONST Source)
{
	return L3_ENCODE_c_Packet_Cell_Change_Failure (Buffer, BitOffset, Source, 1);
}

/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Control_Acknowledgement
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_Packet_Control_Acknowledgement (char* Buffer, long BitOffset, const c_Packet_Control_Acknowledgement* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 1, 6);
		CurrOfs += 6;
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part */
		Len = ENCODE_c_Packet_Control_Acknowledgement_message_content (Buffer, CurrOfs, &(Source->contents));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:559> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Control_Acknowledgement
-----------------------------------------------------------------*/
long ENCODE_c_Packet_Control_Acknowledgement (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Control_Acknowledgement* ED_CONST Source)
{
	return L3_ENCODE_c_Packet_Control_Acknowledgement (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Control_Acknowledgement
-----------------------------------------------------------------*/
long ENCODE_BODY_c_Packet_Control_Acknowledgement (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Control_Acknowledgement* ED_CONST Source)
{
	return L3_ENCODE_c_Packet_Control_Acknowledgement (Buffer, BitOffset, Source, 1);
}

/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Downlink_Ack_Nack
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_Packet_Downlink_Ack_Nack (char* Buffer, long BitOffset, const c_Packet_Downlink_Ack_Nack* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 2, 6);
		CurrOfs += 6;
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part */
		Len = ENCODE_c_Packet_Downlink_Ack_Nack_message_content (Buffer, CurrOfs, &(Source->contents));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:560> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Downlink_Ack_Nack
-----------------------------------------------------------------*/
long ENCODE_c_Packet_Downlink_Ack_Nack (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Downlink_Ack_Nack* ED_CONST Source)
{
	return L3_ENCODE_c_Packet_Downlink_Ack_Nack (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Downlink_Ack_Nack
-----------------------------------------------------------------*/
long ENCODE_BODY_c_Packet_Downlink_Ack_Nack (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Downlink_Ack_Nack* ED_CONST Source)
{
	return L3_ENCODE_c_Packet_Downlink_Ack_Nack (Buffer, BitOffset, Source, 1);
}

/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Uplink_Dummy_Control_Block
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_Packet_Uplink_Dummy_Control_Block (char* Buffer, long BitOffset, const c_Packet_Uplink_Dummy_Control_Block* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 3, 6);
		CurrOfs += 6;
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part */
		Len = ENCODE_c_Packet_Uplink_Dummy_Control_Block_message_content (Buffer, CurrOfs, &(Source->contents));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:561> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Uplink_Dummy_Control_Block
-----------------------------------------------------------------*/
long ENCODE_c_Packet_Uplink_Dummy_Control_Block (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Uplink_Dummy_Control_Block* ED_CONST Source)
{
	return L3_ENCODE_c_Packet_Uplink_Dummy_Control_Block (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Uplink_Dummy_Control_Block
-----------------------------------------------------------------*/
long ENCODE_BODY_c_Packet_Uplink_Dummy_Control_Block (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Uplink_Dummy_Control_Block* ED_CONST Source)
{
	return L3_ENCODE_c_Packet_Uplink_Dummy_Control_Block (Buffer, BitOffset, Source, 1);
}

/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Measurement_Report
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_Packet_Measurement_Report (char* Buffer, long BitOffset, const c_Packet_Measurement_Report* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 4, 6);
		CurrOfs += 6;
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part */
		Len = ENCODE_c_Packet_Measurement_Report_message_content (Buffer, CurrOfs, &(Source->contents));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:562> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Measurement_Report
-----------------------------------------------------------------*/
long ENCODE_c_Packet_Measurement_Report (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Measurement_Report* ED_CONST Source)
{
	return L3_ENCODE_c_Packet_Measurement_Report (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Measurement_Report
-----------------------------------------------------------------*/
long ENCODE_BODY_c_Packet_Measurement_Report (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Measurement_Report* ED_CONST Source)
{
	return L3_ENCODE_c_Packet_Measurement_Report (Buffer, BitOffset, Source, 1);
}

/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Resource_Request
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_Packet_Resource_Request (char* Buffer, long BitOffset, const c_Packet_Resource_Request* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 5, 6);
		CurrOfs += 6;
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part */
		Len = ENCODE_c_Packet_Resource_Request_message_content (Buffer, CurrOfs, &(Source->contents));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:563> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Resource_Request
-----------------------------------------------------------------*/
long ENCODE_c_Packet_Resource_Request (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Resource_Request* ED_CONST Source)
{
	return L3_ENCODE_c_Packet_Resource_Request (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Resource_Request
-----------------------------------------------------------------*/
long ENCODE_BODY_c_Packet_Resource_Request (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Resource_Request* ED_CONST Source)
{
	return L3_ENCODE_c_Packet_Resource_Request (Buffer, BitOffset, Source, 1);
}

/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Mobile_TBF_Status
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_Packet_Mobile_TBF_Status (char* Buffer, long BitOffset, const c_Packet_Mobile_TBF_Status* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 6, 6);
		CurrOfs += 6;
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part */
		Len = ENCODE_c_Packet_Mobile_TBF_Status_message_content (Buffer, CurrOfs, &(Source->contents));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:564> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Mobile_TBF_Status
-----------------------------------------------------------------*/
long ENCODE_c_Packet_Mobile_TBF_Status (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Mobile_TBF_Status* ED_CONST Source)
{
	return L3_ENCODE_c_Packet_Mobile_TBF_Status (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Mobile_TBF_Status
-----------------------------------------------------------------*/
long ENCODE_BODY_c_Packet_Mobile_TBF_Status (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Mobile_TBF_Status* ED_CONST Source)
{
	return L3_ENCODE_c_Packet_Mobile_TBF_Status (Buffer, BitOffset, Source, 1);
}

/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_PSI_Status
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_Packet_PSI_Status (char* Buffer, long BitOffset, const c_Packet_PSI_Status* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 7, 6);
		CurrOfs += 6;
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part */
		Len = ENCODE_c_Packet_PSI_Status_message_content (Buffer, CurrOfs, &(Source->contents));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:565> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_PSI_Status
-----------------------------------------------------------------*/
long ENCODE_c_Packet_PSI_Status (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_PSI_Status* ED_CONST Source)
{
	return L3_ENCODE_c_Packet_PSI_Status (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_PSI_Status
-----------------------------------------------------------------*/
long ENCODE_BODY_c_Packet_PSI_Status (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_PSI_Status* ED_CONST Source)
{
	return L3_ENCODE_c_Packet_PSI_Status (Buffer, BitOffset, Source, 1);
}

/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE EGPRS_Packet_Downlink_Ack_Nack
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_EGPRS_Packet_Downlink_Ack_Nack (char* Buffer, long BitOffset, const c_EGPRS_Packet_Downlink_Ack_Nack* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 8, 6);
		CurrOfs += 6;
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part */
		Len = ENCODE_c_EGPRS_Packet_Downlink_Ack_Nack_message_content (Buffer, CurrOfs, &(Source->contents));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:566> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE EGPRS_Packet_Downlink_Ack_Nack
-----------------------------------------------------------------*/
long ENCODE_c_EGPRS_Packet_Downlink_Ack_Nack (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_EGPRS_Packet_Downlink_Ack_Nack* ED_CONST Source)
{
	return L3_ENCODE_c_EGPRS_Packet_Downlink_Ack_Nack (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE EGPRS_Packet_Downlink_Ack_Nack
-----------------------------------------------------------------*/
long ENCODE_BODY_c_EGPRS_Packet_Downlink_Ack_Nack (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_EGPRS_Packet_Downlink_Ack_Nack* ED_CONST Source)
{
	return L3_ENCODE_c_EGPRS_Packet_Downlink_Ack_Nack (Buffer, BitOffset, Source, 1);
}

/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Enhanced_Measurement_Report
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_Packet_Enhanced_Measurement_Report (char* Buffer, long BitOffset, const c_Packet_Enhanced_Measurement_Report* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 10, 6);
		CurrOfs += 6;
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part */
		Len = ENCODE_c_Packet_Enhanced_Measurement_Report_message_content (Buffer, CurrOfs, &(Source->contents));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:567> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Enhanced_Measurement_Report
-----------------------------------------------------------------*/
long ENCODE_c_Packet_Enhanced_Measurement_Report (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Enhanced_Measurement_Report* ED_CONST Source)
{
	return L3_ENCODE_c_Packet_Enhanced_Measurement_Report (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Enhanced_Measurement_Report
-----------------------------------------------------------------*/
long ENCODE_BODY_c_Packet_Enhanced_Measurement_Report (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Enhanced_Measurement_Report* ED_CONST Source)
{
	return L3_ENCODE_c_Packet_Enhanced_Measurement_Report (Buffer, BitOffset, Source, 1);
}

/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE Additional_MS_Radio_Access_Capabilities
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_Additional_MS_Radio_Access_Capabilities (char* Buffer, long BitOffset, const c_Additional_MS_Radio_Access_Capabilities* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 11, 6);
		CurrOfs += 6;
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part */
		Len = ENCODE_c_Additional_MS_Radio_Access_Capabilities_message_content (Buffer, CurrOfs, &(Source->contents));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:568> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE Additional_MS_Radio_Access_Capabilities
-----------------------------------------------------------------*/
long ENCODE_c_Additional_MS_Radio_Access_Capabilities (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Additional_MS_Radio_Access_Capabilities* ED_CONST Source)
{
	return L3_ENCODE_c_Additional_MS_Radio_Access_Capabilities (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE Additional_MS_Radio_Access_Capabilities
-----------------------------------------------------------------*/
long ENCODE_BODY_c_Additional_MS_Radio_Access_Capabilities (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Additional_MS_Radio_Access_Capabilities* ED_CONST Source)
{
	return L3_ENCODE_c_Additional_MS_Radio_Access_Capabilities (Buffer, BitOffset, Source, 1);
}

/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Cell_Change_Notification
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_Packet_Cell_Change_Notification (char* Buffer, long BitOffset, const c_Packet_Cell_Change_Notification* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 12, 6);
		CurrOfs += 6;
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part */
		Len = ENCODE_c_Packet_Cell_Change_Notification_message_content (Buffer, CurrOfs, &(Source->contents));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:569> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Cell_Change_Notification
-----------------------------------------------------------------*/
long ENCODE_c_Packet_Cell_Change_Notification (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Cell_Change_Notification* ED_CONST Source)
{
	return L3_ENCODE_c_Packet_Cell_Change_Notification (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_Cell_Change_Notification
-----------------------------------------------------------------*/
long ENCODE_BODY_c_Packet_Cell_Change_Notification (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_Cell_Change_Notification* ED_CONST Source)
{
	return L3_ENCODE_c_Packet_Cell_Change_Notification (Buffer, BitOffset, Source, 1);
}

/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_SI_Status
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_Packet_SI_Status (char* Buffer, long BitOffset, const c_Packet_SI_Status* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 13, 6);
		CurrOfs += 6;
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part */
		Len = ENCODE_c_Packet_SI_Status_message_content (Buffer, CurrOfs, &(Source->contents));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:570> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_SI_Status
-----------------------------------------------------------------*/
long ENCODE_c_Packet_SI_Status (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_SI_Status* ED_CONST Source)
{
	return L3_ENCODE_c_Packet_SI_Status (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE Packet_SI_Status
-----------------------------------------------------------------*/
long ENCODE_BODY_c_Packet_SI_Status (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_Packet_SI_Status* ED_CONST Source)
{
	return L3_ENCODE_c_Packet_SI_Status (Buffer, BitOffset, Source, 1);
}

int Match_c_Packet_Cell_Change_Failure (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 0) /* message type */
	);
}

int Match_c_Packet_Control_Acknowledgement (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 1) /* message type */
	);
}

int Match_c_Packet_Downlink_Ack_Nack (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 2) /* message type */
	);
}

int Match_c_Packet_Uplink_Dummy_Control_Block (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 3) /* message type */
	);
}

int Match_c_Packet_Measurement_Report (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 4) /* message type */
	);
}

int Match_c_Packet_Resource_Request (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 5) /* message type */
	);
}

int Match_c_Packet_Mobile_TBF_Status (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 6) /* message type */
	);
}

int Match_c_Packet_PSI_Status (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 7) /* message type */
	);
}

int Match_c_EGPRS_Packet_Downlink_Ack_Nack (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 8) /* message type */
	);
}

int Match_c_Packet_Enhanced_Measurement_Report (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 10) /* message type */
	);
}

int Match_c_Additional_MS_Radio_Access_Capabilities (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 11) /* message type */
	);
}

int Match_c_Packet_Cell_Change_Notification (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 12) /* message type */
	);
}

int Match_c_Packet_SI_Status (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 13) /* message type */
	);
}

/*lint +e958*/
/*lint +e961*/
