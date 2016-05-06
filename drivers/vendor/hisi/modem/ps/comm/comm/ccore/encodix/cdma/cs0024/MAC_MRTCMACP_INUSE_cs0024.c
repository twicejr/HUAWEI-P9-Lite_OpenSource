/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/
/*lint -e959 -e530 -e774 -e572 -e778 -e525 -e539 -e701 -e123 -e438 -e119 -e506 -e529 -e550 -e666 -e713 -e719 -e730 -e734 -e744 -e801 -e801 -e813 -e830 -e40 */
#define ENCODIX_CS0024

#include "MAC_MRTCMACP_INUSE_cs0024.h"
#include "ed_c_known_ie_cs0024.h"
#include "ed_tlv.h"
#include "CSN1DataTypes_cs0024.h"
#if ED_COMMON_CRC != 0x328E3625 && ED_VERSION != 10152 && ED_VERSION != 10153
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.154
#endif


#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_RTCAck
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_MAC_MRTCMACP_INUSE_RTCAck (char* Buffer, ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_RTCAck* Source, int Mode, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 0, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->contents> DOT=<.> */
		Len = ENCODE_c_MAC_MRTCMACP_INUSE_RTCAck_contents (Buffer, CurrOfs, (&(Source->contents)), pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:607> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_RTCAck
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MAC_MRTCMACP_INUSE_RTCAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_RTCAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_MAC_MRTCMACP_INUSE_RTCAck (Buffer, BitOffset, Source, 0, pCSN1CContextSet);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_RTCAck
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MAC_MRTCMACP_INUSE_RTCAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_RTCAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_MAC_MRTCMACP_INUSE_RTCAck (Buffer, BitOffset, Source, 1, pCSN1CContextSet);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_RTCAck
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MAC_MRTCMACP_INUSE_RTCAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MAC_MRTCMACP_INUSE_RTCAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	int Len=0;
	
	Len = DECODE_BODY_c_MAC_MRTCMACP_INUSE_RTCAck (Buffer, (BitOffset+8), Destin, Length-(8), pCSN1CContextSet);
	if (Len < 0) return Len;
	
	return Len+8;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_RTCAck
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MAC_MRTCMACP_INUSE_RTCAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MAC_MRTCMACP_INUSE_RTCAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_MAC_MRTCMACP_INUSE_RTCAck_contents (Buffer, CurrOfs, (&(Destin->contents)), Len, pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:608> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 608, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:609> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 608, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_CarrierRequest
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_MAC_MRTCMACP_INUSE_CarrierRequest (char* Buffer, ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_CarrierRequest* Source, int Mode, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 4, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->contents> DOT=<.> */
		Len = ENCODE_c_MAC_MRTCMACP_INUSE_CarrierRequest_contents (Buffer, CurrOfs, (&(Source->contents)), pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:610> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_CarrierRequest
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MAC_MRTCMACP_INUSE_CarrierRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_CarrierRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_MAC_MRTCMACP_INUSE_CarrierRequest (Buffer, BitOffset, Source, 0, pCSN1CContextSet);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_CarrierRequest
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MAC_MRTCMACP_INUSE_CarrierRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_CarrierRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_MAC_MRTCMACP_INUSE_CarrierRequest (Buffer, BitOffset, Source, 1, pCSN1CContextSet);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_CarrierRequest
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MAC_MRTCMACP_INUSE_CarrierRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MAC_MRTCMACP_INUSE_CarrierRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	int Len=0;
	
	Len = DECODE_BODY_c_MAC_MRTCMACP_INUSE_CarrierRequest (Buffer, (BitOffset+8), Destin, Length-(8), pCSN1CContextSet);
	if (Len < 0) return Len;
	
	return Len+8;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_CarrierRequest
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MAC_MRTCMACP_INUSE_CarrierRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MAC_MRTCMACP_INUSE_CarrierRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_MAC_MRTCMACP_INUSE_CarrierRequest_contents (Buffer, CurrOfs, (&(Destin->contents)), Len, pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:611> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 611, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:612> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 611, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped (char* Buffer, ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped* Source, int Mode, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 5, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->contents> DOT=<.> */
		Len = ENCODE_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped_contents (Buffer, CurrOfs, (&(Source->contents)), pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:613> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped (Buffer, BitOffset, Source, 0, pCSN1CContextSet);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped (Buffer, BitOffset, Source, 1, pCSN1CContextSet);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	int Len=0;
	
	Len = DECODE_BODY_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped (Buffer, (BitOffset+8), Destin, Length-(8), pCSN1CContextSet);
	if (Len < 0) return Len;
	
	return Len+8;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped_contents (Buffer, CurrOfs, (&(Destin->contents)), Len, pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:614> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 614, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:615> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 614, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck (char* Buffer, ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck* Source, int Mode, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->contents> DOT=<.> */
		Len = ENCODE_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck_contents (Buffer, CurrOfs, (&(Source->contents)), pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:616> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck (Buffer, BitOffset, Source, 0, pCSN1CContextSet);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck (Buffer, BitOffset, Source, 1, pCSN1CContextSet);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	int Len=0;
	
	Len = DECODE_BODY_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck (Buffer, (BitOffset+8), Destin, Length-(8), pCSN1CContextSet);
	if (Len < 0) return Len;
	
	return Len+8;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck_contents (Buffer, CurrOfs, (&(Destin->contents)), Len, pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:617> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 617, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:618> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 617, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_Request
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_MAC_MRTCMACP_INUSE_Request (char* Buffer, ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_Request* Source, int Mode, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 2, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->contents> DOT=<.> */
		Len = ENCODE_c_MAC_MRTCMACP_INUSE_Request_contents (Buffer, CurrOfs, (&(Source->contents)), pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:619> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_Request
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MAC_MRTCMACP_INUSE_Request (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_Request* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_MAC_MRTCMACP_INUSE_Request (Buffer, BitOffset, Source, 0, pCSN1CContextSet);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_Request
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MAC_MRTCMACP_INUSE_Request (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_Request* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_MAC_MRTCMACP_INUSE_Request (Buffer, BitOffset, Source, 1, pCSN1CContextSet);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_Request
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MAC_MRTCMACP_INUSE_Request (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MAC_MRTCMACP_INUSE_Request* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	int Len=0;
	
	Len = DECODE_BODY_c_MAC_MRTCMACP_INUSE_Request (Buffer, (BitOffset+8), Destin, Length-(8), pCSN1CContextSet);
	if (Len < 0) return Len;
	
	return Len+8;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_Request
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MAC_MRTCMACP_INUSE_Request (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MAC_MRTCMACP_INUSE_Request* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_MAC_MRTCMACP_INUSE_Request_contents (Buffer, CurrOfs, (&(Destin->contents)), Len, pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:620> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 620, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:621> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 620, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_Grant
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_MAC_MRTCMACP_INUSE_Grant (char* Buffer, ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_Grant* Source, int Mode, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 3, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->contents> DOT=<.> */
		Len = ENCODE_c_MAC_MRTCMACP_INUSE_Grant_contents (Buffer, CurrOfs, (&(Source->contents)), pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:622> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_Grant
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MAC_MRTCMACP_INUSE_Grant (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_Grant* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_MAC_MRTCMACP_INUSE_Grant (Buffer, BitOffset, Source, 0, pCSN1CContextSet);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_Grant
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MAC_MRTCMACP_INUSE_Grant (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_Grant* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_MAC_MRTCMACP_INUSE_Grant (Buffer, BitOffset, Source, 1, pCSN1CContextSet);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_Grant
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MAC_MRTCMACP_INUSE_Grant (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MAC_MRTCMACP_INUSE_Grant* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	int Len=0;
	
	Len = DECODE_BODY_c_MAC_MRTCMACP_INUSE_Grant (Buffer, (BitOffset+8), Destin, Length-(8), pCSN1CContextSet);
	if (Len < 0) return Len;
	
	return Len+8;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_Grant
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MAC_MRTCMACP_INUSE_Grant (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MAC_MRTCMACP_INUSE_Grant* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_MAC_MRTCMACP_INUSE_Grant_contents (Buffer, CurrOfs, (&(Destin->contents)), Len, pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:623> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 623, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:624> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 623, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_AttributeUpdateRequest
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest (char* Buffer, ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest* Source, int Mode, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 82, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->contents> DOT=<.> */
		Len = ENCODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest_contents (Buffer, CurrOfs, (&(Source->contents)), pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:625> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_AttributeUpdateRequest
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest (Buffer, BitOffset, Source, 0, pCSN1CContextSet);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_AttributeUpdateRequest
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest (Buffer, BitOffset, Source, 1, pCSN1CContextSet);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_AttributeUpdateRequest
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	int Len=0;
	
	Len = DECODE_BODY_c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest (Buffer, (BitOffset+8), Destin, Length-(8), pCSN1CContextSet);
	if (Len < 0) return Len;
	
	return Len+8;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_AttributeUpdateRequest
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest_contents (Buffer, CurrOfs, (&(Destin->contents)), Len, pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:626> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 626, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:627> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 626, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_AttributeUpdateAccept
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept (char* Buffer, ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept* Source, int Mode, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 83, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->contents> DOT=<.> */
		Len = ENCODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept_contents (Buffer, CurrOfs, (&(Source->contents)), pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:628> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_AttributeUpdateAccept
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept (Buffer, BitOffset, Source, 0, pCSN1CContextSet);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_AttributeUpdateAccept
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept (Buffer, BitOffset, Source, 1, pCSN1CContextSet);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_AttributeUpdateAccept
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	int Len=0;
	
	Len = DECODE_BODY_c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept (Buffer, (BitOffset+8), Destin, Length-(8), pCSN1CContextSet);
	if (Len < 0) return Len;
	
	return Len+8;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_AttributeUpdateAccept
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept_contents (Buffer, CurrOfs, (&(Destin->contents)), Len, pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:629> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 629, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:630> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 629, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_AttributeUpdateReject
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateReject (char* Buffer, ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_AttributeUpdateReject* Source, int Mode, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 84, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->contents> DOT=<.> */
		Len = ENCODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateReject_contents (Buffer, CurrOfs, (&(Source->contents)), pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:631> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_AttributeUpdateReject
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateReject (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_AttributeUpdateReject* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateReject (Buffer, BitOffset, Source, 0, pCSN1CContextSet);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_AttributeUpdateReject
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MAC_MRTCMACP_INUSE_AttributeUpdateReject (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MAC_MRTCMACP_INUSE_AttributeUpdateReject* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateReject (Buffer, BitOffset, Source, 1, pCSN1CContextSet);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_AttributeUpdateReject
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateReject (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MAC_MRTCMACP_INUSE_AttributeUpdateReject* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	int Len=0;
	
	Len = DECODE_BODY_c_MAC_MRTCMACP_INUSE_AttributeUpdateReject (Buffer, (BitOffset+8), Destin, Length-(8), pCSN1CContextSet);
	if (Len < 0) return Len;
	
	return Len+8;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE MAC_MRTCMACP_INUSE_AttributeUpdateReject
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MAC_MRTCMACP_INUSE_AttributeUpdateReject (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MAC_MRTCMACP_INUSE_AttributeUpdateReject* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateReject_contents (Buffer, CurrOfs, (&(Destin->contents)), Len, pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:632> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 632, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:633> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 632, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
int Match_c_MAC_MRTCMACP_INUSE_RTCAck (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8)) == 0) /* message type */
	);
}

int Match_c_MAC_MRTCMACP_INUSE_CarrierRequest (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8)) == 4) /* message type */
	);
}

int Match_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8)) == 5) /* message type */
	);
}

int Match_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8)) == 6) /* message type */
	);
}

int Match_c_MAC_MRTCMACP_INUSE_Request (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8)) == 2) /* message type */
	);
}

int Match_c_MAC_MRTCMACP_INUSE_Grant (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8)) == 3) /* message type */
	);
}

int Match_c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8)) == 82) /* message type */
	);
}

int Match_c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8)) == 83) /* message type */
	);
}

int Match_c_MAC_MRTCMACP_INUSE_AttributeUpdateReject (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8)) == 84) /* message type */
	);
}

