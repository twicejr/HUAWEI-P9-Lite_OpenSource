/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.83
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#include "Downlink_RLC_MAC.h"
#include "ed_c_known_ie.h"
#include "ed_tlv.h"
#include "CSN1DataTypes.h"

#include "UserDefinedDataTypes.h"
/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_DOWNLINK_RLC_MAC_C
/*lint -e961*/
/*lint -e958*/
/*lint -e527*/

c_Individualpriorities            gstPccoGsmIndiPri;


/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Cell_Change_Order
-----------------------------------------------------------------*/
long DECODE_c_Packet_Cell_Change_Order (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Cell_Change_Order* ED_CONST Destin, long Length)
{
	int Len=0;
    c_Individualpriorities              *pstPccoGsmIndiPri;

	Len = DECODE_BODY_c_Packet_Cell_Change_Order (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

    pstPccoGsmIndiPri           = GAS_GetPccoGsmIndiPriAddr();
    memset(pstPccoGsmIndiPri,0x00,sizeof(c_Individualpriorities));

    DECODE_c_Individualpriorities(( char* )Destin->contents.GSM_target_cell.Individual_Priorities.value,
                                  ( long )0,
                                  pstPccoGsmIndiPri,
                                  ( long )Destin->contents.GSM_target_cell.Individual_Priorities.usedBits);

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Cell_Change_Order
-----------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Cell_Change_Order (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Cell_Change_Order* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_Packet_Cell_Change_Order_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:496> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 496, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:497> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 496, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Downlink_Assignment
-----------------------------------------------------------------*/
long DECODE_c_Packet_Downlink_Assignment (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Downlink_Assignment* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_Packet_Downlink_Assignment (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Downlink_Assignment
-----------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Downlink_Assignment (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Downlink_Assignment* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_Packet_Downlink_Assignment_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:498> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 498, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:499> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 498, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Measurement_Order
-----------------------------------------------------------------*/
long DECODE_c_Packet_Measurement_Order (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Measurement_Order* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_Packet_Measurement_Order (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Measurement_Order
-----------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Measurement_Order (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Measurement_Order* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_Packet_Measurement_Order_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:500> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 500, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:501> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 500, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Polling_Request
-----------------------------------------------------------------*/
long DECODE_c_Packet_Polling_Request (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Polling_Request* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_Packet_Polling_Request (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Polling_Request
-----------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Polling_Request (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Polling_Request* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_Packet_Polling_Request_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:502> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 502, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:503> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 502, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Power_Control_Timing_Advance
-----------------------------------------------------------------*/
long DECODE_c_Packet_Power_Control_Timing_Advance (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Power_Control_Timing_Advance* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_Packet_Power_Control_Timing_Advance (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Power_Control_Timing_Advance
-----------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Power_Control_Timing_Advance (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Power_Control_Timing_Advance* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_Packet_Power_Control_Timing_Advance_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:504> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 504, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:505> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 504, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Queueing_Notification
-----------------------------------------------------------------*/
long DECODE_c_Packet_Queueing_Notification (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Queueing_Notification* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_Packet_Queueing_Notification (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Queueing_Notification
-----------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Queueing_Notification (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Queueing_Notification* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_Packet_Queueing_Notification_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:506> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 506, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:507> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 506, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Timeslot_Reconfigure
-----------------------------------------------------------------*/
long DECODE_c_Packet_Timeslot_Reconfigure (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Timeslot_Reconfigure* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_Packet_Timeslot_Reconfigure (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Timeslot_Reconfigure
-----------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Timeslot_Reconfigure (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Timeslot_Reconfigure* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_Packet_Timeslot_Reconfigure_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:508> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 508, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:509> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 508, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_TBF_Release
-----------------------------------------------------------------*/
long DECODE_c_Packet_TBF_Release (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_TBF_Release* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_Packet_TBF_Release (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_TBF_Release
-----------------------------------------------------------------*/
long DECODE_BODY_c_Packet_TBF_Release (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_TBF_Release* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_Packet_TBF_Release_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:510> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 510, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:511> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 510, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Uplink_Ack_Nack
-----------------------------------------------------------------*/
long DECODE_c_Packet_Uplink_Ack_Nack (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Uplink_Ack_Nack* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_Packet_Uplink_Ack_Nack (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Uplink_Ack_Nack
-----------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Uplink_Ack_Nack (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Uplink_Ack_Nack* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_Packet_Uplink_Ack_Nack_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:512> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 512, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:513> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 512, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Uplink_Assignment
-----------------------------------------------------------------*/
long DECODE_c_Packet_Uplink_Assignment (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Uplink_Assignment* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_Packet_Uplink_Assignment (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Uplink_Assignment
-----------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Uplink_Assignment (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Uplink_Assignment* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_Packet_Uplink_Assignment_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:514> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 514, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:515> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 514, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Cell_Change_Continue
-----------------------------------------------------------------*/
long DECODE_c_Packet_Cell_Change_Continue (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Cell_Change_Continue* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_Packet_Cell_Change_Continue (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Cell_Change_Continue
-----------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Cell_Change_Continue (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Cell_Change_Continue* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_Packet_Cell_Change_Continue_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:516> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 516, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:517> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 516, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Neighbour_Cell_Data
-----------------------------------------------------------------*/
long DECODE_c_Packet_Neighbour_Cell_Data (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Neighbour_Cell_Data* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_Packet_Neighbour_Cell_Data (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Neighbour_Cell_Data
-----------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Neighbour_Cell_Data (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Neighbour_Cell_Data* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_Packet_Neighbour_Cell_Data_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:518> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 518, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:519> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 518, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Serving_Cell_Data
-----------------------------------------------------------------*/
long DECODE_c_Packet_Serving_Cell_Data (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Serving_Cell_Data* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_Packet_Serving_Cell_Data (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Serving_Cell_Data
-----------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Serving_Cell_Data (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Serving_Cell_Data* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_Packet_Serving_Cell_Data_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:520> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 520, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:521> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 520, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Access_Reject
-----------------------------------------------------------------*/
long DECODE_c_Packet_Access_Reject (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Access_Reject* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_Packet_Access_Reject (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Access_Reject
-----------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Access_Reject (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Access_Reject* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_Packet_Access_Reject_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:522> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 522, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:523> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 522, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Paging_Request
-----------------------------------------------------------------*/
long DECODE_c_Packet_Paging_Request (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Paging_Request* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_Packet_Paging_Request (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Paging_Request
-----------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Paging_Request (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Paging_Request* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_Packet_Paging_Request_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:524> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 524, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:525> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 524, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_PDCH_Release
-----------------------------------------------------------------*/
long DECODE_c_Packet_PDCH_Release (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_PDCH_Release* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_Packet_PDCH_Release (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_PDCH_Release
-----------------------------------------------------------------*/
long DECODE_BODY_c_Packet_PDCH_Release (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_PDCH_Release* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_Packet_PDCH_Release_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:526> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 526, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:527> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 526, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_PRACH_Parameters
-----------------------------------------------------------------*/
long DECODE_c_Packet_PRACH_Parameters (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_PRACH_Parameters* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_Packet_PRACH_Parameters (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_PRACH_Parameters
-----------------------------------------------------------------*/
long DECODE_BODY_c_Packet_PRACH_Parameters (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_PRACH_Parameters* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_Packet_PRACH_Parameters_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:528> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 528, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:529> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 528, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Downlink_Dummy_Control_Block
-----------------------------------------------------------------*/
long DECODE_c_Packet_Downlink_Dummy_Control_Block (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Downlink_Dummy_Control_Block* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_Packet_Downlink_Dummy_Control_Block (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Downlink_Dummy_Control_Block
-----------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Downlink_Dummy_Control_Block (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Downlink_Dummy_Control_Block* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_Packet_Downlink_Dummy_Control_Block_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:530> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 530, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:531> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 530, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PSI1
-----------------------------------------------------------------*/
long DECODE_c_PSI1 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI1* ED_CONST Destin, long Length)
{
    /* Added by f48555 for GSM_R6协议升级Phase2, 2010_02_08，begin */
    ED_LONG                                          ulRetVal;
    c_PSI1_message_content_GPRS_Cell_Options         *pstGprsCellOption;
    /* Added by f48555 for GSM_R6协议升级Phase2, 2010_02_08，end */
    int Len=0;

    Len = DECODE_BODY_c_PSI1 (Buffer, (BitOffset+6), Destin, Length-(6));
    if (Len < 0) return Len;

    /* Added by f48555 for GSM_R6协议升级Phase2, 2010_02_08，begin */
    pstGprsCellOption   = &Destin->contents.GPRS_Cell_Options;
    ulRetVal            = GAS_ENCODIX_CheckGprsCellOptionExtVersion((c_SI13RestOctets_NoPBCCH_GPRS_Cell_Options*)pstGprsCellOption);

    if ( ED_FALSE == ulRetVal )
    {
        return (-1);
    }
    /* Added by f48555 for GSM_R6协议升级Phase2, 2010_02_08，end */

    return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PSI1
-----------------------------------------------------------------*/
long DECODE_BODY_c_PSI1 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI1* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_PSI1_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:532> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 532, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:533> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 532, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PSI2
-----------------------------------------------------------------*/
long DECODE_c_PSI2 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI2* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_PSI2 (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PSI2
-----------------------------------------------------------------*/
long DECODE_BODY_c_PSI2 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI2* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_PSI2_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:534> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 534, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:535> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 534, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PSI3
-----------------------------------------------------------------*/
long DECODE_c_PSI3 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI3* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_PSI3 (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PSI3
-----------------------------------------------------------------*/
long DECODE_BODY_c_PSI3 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI3* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_PSI3_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:536> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 536, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:537> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 536, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PSI3_bis
-----------------------------------------------------------------*/
long DECODE_c_PSI3_bis (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI3_bis* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_PSI3_bis (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PSI3_bis
-----------------------------------------------------------------*/
long DECODE_BODY_c_PSI3_bis (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI3_bis* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_PSI3_bis_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:538> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 538, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:539> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 538, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PSI4
-----------------------------------------------------------------*/
long DECODE_c_PSI4 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI4* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_PSI4 (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PSI4
-----------------------------------------------------------------*/
long DECODE_BODY_c_PSI4 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI4* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_PSI4_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:540> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 540, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:541> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 540, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PSI5
-----------------------------------------------------------------*/
long DECODE_c_PSI5 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI5* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_PSI5 (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PSI5
-----------------------------------------------------------------*/
long DECODE_BODY_c_PSI5 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI5* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_PSI5_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:542> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 542, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:543> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 542, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PSI13
-----------------------------------------------------------------*/
long DECODE_c_PSI13 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI13* ED_CONST Destin, long Length)
{
    /* Added by f48555 for GSM_R6协议升级Phase2, 2010_02_08，begin */
    ED_LONG                                         ulRetVal;
    c_PSI13_message_content_GPRS_Cell_Options       *pstGprsCellOption;
    /* Added by f48555 for GSM_R6协议升级Phase2, 2010_02_08，end */
    int Len=0;

    Len = DECODE_BODY_c_PSI13 (Buffer, (BitOffset+6), Destin, Length-(6));
    if (Len < 0) return Len;

    /* Added by f48555 for GSM_R6协议升级Phase2, 2010_02_08，begin */
    pstGprsCellOption   = &Destin->contents.GPRS_Cell_Options;
    ulRetVal            = GAS_ENCODIX_CheckGprsCellOptionExtVersion((c_SI13RestOctets_NoPBCCH_GPRS_Cell_Options*)pstGprsCellOption);

    if ( ED_FALSE == ulRetVal )
    {
        return (-1);
    }
    /* Added by f48555 for GSM_R6协议升级Phase2, 2010_02_08，end */

    return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PSI13
-----------------------------------------------------------------*/
long DECODE_BODY_c_PSI13 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI13* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_PSI13_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:544> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 544, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:545> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 544, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PSI14
-----------------------------------------------------------------*/
long DECODE_c_PSI14 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI14* ED_CONST Destin, long Length)
{
    /* Added by f48555 for GSM_R6协议升级Phase2, 2010_02_08，begin */
    ED_LONG                                                             ulRetVal;
    c_PSI14_message_content_CCCH_Access_Information_GPRS_Cell_Options   *pstGprsCellOption;
    /* Added by f48555 for GSM_R6协议升级Phase2, 2010_02_08，end */
    int Len=0;

    Len = DECODE_BODY_c_PSI14 (Buffer, (BitOffset+6), Destin, Length-(6));
    if (Len < 0) return Len;

    /* Added by f48555 for GSM_R6协议升级Phase2, 2010_02_08，begin */
    pstGprsCellOption   = &Destin->contents.CCCH_Access_Information.GPRS_Cell_Options;
    ulRetVal            = GAS_ENCODIX_CheckGprsCellOptionExtVersion((c_SI13RestOctets_NoPBCCH_GPRS_Cell_Options*)pstGprsCellOption);

    if ( ED_FALSE == ulRetVal )
    {
        return (-1);
    }
    /* Added by f48555 for GSM_R6协议升级Phase2, 2010_02_08，end */

    return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PSI14
-----------------------------------------------------------------*/
long DECODE_BODY_c_PSI14 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI14* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_PSI14_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:546> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 546, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:547> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 546, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PSI3_ter
-----------------------------------------------------------------*/
long DECODE_c_PSI3_ter (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI3_ter* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_PSI3_ter (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PSI3_ter
-----------------------------------------------------------------*/
long DECODE_BODY_c_PSI3_ter (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI3_ter* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_PSI3_ter_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:548> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 548, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:549> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 548, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PSI3_quater
-----------------------------------------------------------------*/
long DECODE_c_PSI3_quater (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI3_quater* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_PSI3_quater (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PSI3_quater
-----------------------------------------------------------------*/
long DECODE_BODY_c_PSI3_quater (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI3_quater* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_PSI3_quater_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:550> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 550, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:551> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 550, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Serving_Cell_SI
-----------------------------------------------------------------*/
long DECODE_c_Packet_Serving_Cell_SI (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Serving_Cell_SI* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_Packet_Serving_Cell_SI (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Serving_Cell_SI
-----------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Serving_Cell_SI (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Serving_Cell_SI* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_Packet_Serving_Cell_SI_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:552> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 552, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:553> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 552, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PS_Handover_Command
-----------------------------------------------------------------*/
long DECODE_c_PS_Handover_Command (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PS_Handover_Command* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_PS_Handover_Command (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PS_Handover_Command
-----------------------------------------------------------------*/
long DECODE_BODY_c_PS_Handover_Command (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PS_Handover_Command* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_PS_Handover_Command_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:554> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 554, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:555> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 554, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Physical_Information
-----------------------------------------------------------------*/
long DECODE_c_Packet_Physical_Information (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Physical_Information* ED_CONST Destin, long Length)
{
	int Len=0;

	Len = DECODE_BODY_c_Packet_Physical_Information (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;

	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE Packet_Physical_Information
-----------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Physical_Information (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Physical_Information* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;

	/*-----------------------------------------------------
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_Packet_Physical_Information_message_content (Buffer, CurrOfs, &(Destin->contents), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:556> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 556, (Destin->contents));
	}
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:557> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 556, (Destin->contents));
	}
#endif



	return (CurrOfs - BitOffset);
}
int Match_c_Packet_Cell_Change_Order (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 1) /* message type */
	);
}

int Match_c_Packet_Downlink_Assignment (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 2) /* message type */
	);
}

int Match_c_Packet_Measurement_Order (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 3) /* message type */
	);
}

int Match_c_Packet_Polling_Request (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 4) /* message type */
	);
}

int Match_c_Packet_Power_Control_Timing_Advance (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 5) /* message type */
	);
}

int Match_c_Packet_Queueing_Notification (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 6) /* message type */
	);
}

int Match_c_Packet_Timeslot_Reconfigure (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 7) /* message type */
	);
}

int Match_c_Packet_TBF_Release (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 8) /* message type */
	);
}

int Match_c_Packet_Uplink_Ack_Nack (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 9) /* message type */
	);
}

int Match_c_Packet_Uplink_Assignment (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 10) /* message type */
	);
}

int Match_c_Packet_Cell_Change_Continue (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 11) /* message type */
	);
}

int Match_c_Packet_Neighbour_Cell_Data (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 12) /* message type */
	);
}

int Match_c_Packet_Serving_Cell_Data (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 13) /* message type */
	);
}

int Match_c_Packet_Access_Reject (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 33) /* message type */
	);
}

int Match_c_Packet_Paging_Request (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 34) /* message type */
	);
}

int Match_c_Packet_PDCH_Release (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 35) /* message type */
	);
}

int Match_c_Packet_PRACH_Parameters (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 36) /* message type */
	);
}

int Match_c_Packet_Downlink_Dummy_Control_Block (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 37) /* message type */
	);
}

int Match_c_PSI1 (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 49) /* message type */
	);
}

int Match_c_PSI2 (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 50) /* message type */
	);
}

int Match_c_PSI3 (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 51) /* message type */
	);
}

int Match_c_PSI3_bis (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 52) /* message type */
	);
}

int Match_c_PSI4 (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 53) /* message type */
	);
}

int Match_c_PSI5 (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 54) /* message type */
	);
}

int Match_c_PSI13 (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 55) /* message type */
	);
}

int Match_c_PSI14 (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 58) /* message type */
	);
}

int Match_c_PSI3_ter (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 60) /* message type */
	);
}

int Match_c_PSI3_quater (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 61) /* message type */
	);
}

int Match_c_Packet_Serving_Cell_SI (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 32) /* message type */
	);
}

int Match_c_PS_Handover_Command (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 21) /* message type */
	);
}

int Match_c_Packet_Physical_Information (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 22) /* message type */
	);
}

/*lint +e958*/
/*lint +e961*/
/*lint +e527*/

