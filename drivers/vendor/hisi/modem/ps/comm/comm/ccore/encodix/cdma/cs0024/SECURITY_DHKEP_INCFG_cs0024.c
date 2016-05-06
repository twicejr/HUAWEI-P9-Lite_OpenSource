/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/
/*lint -e959 -e530 -e774 -e572 -e778 -e525 -e539 -e701 -e123 -e438 -e119 -e506 -e529 -e550 -e666 -e713 -e719 -e730 -e734 -e744 -e801 -e801 -e813 -e830 -e40 */
#define ENCODIX_CS0024

#include "SECURITY_DHKEP_INCFG_cs0024.h"
#include "ed_c_known_ie_cs0024.h"
#include "ed_tlv.h"
#include "CSN1DataTypes_cs0024.h"
#if ED_COMMON_CRC != 0x328E3625 && ED_VERSION != 10152 && ED_VERSION != 10153
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.154
#endif


#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_KeyRequest
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SECURITY_DHKEP_INCFG_KeyRequest (char* Buffer, ED_EXLONG BitOffset, const c_SECURITY_DHKEP_INCFG_KeyRequest* Source, int Mode, struct SCSN1CContextSet* pCSN1CContextSet)
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
		Len = ENCODE_c_SECURITY_DHKEP_INCFG_KeyRequest_contents (Buffer, CurrOfs, (&(Source->contents)), pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:427> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_KeyRequest
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SECURITY_DHKEP_INCFG_KeyRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SECURITY_DHKEP_INCFG_KeyRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_SECURITY_DHKEP_INCFG_KeyRequest (Buffer, BitOffset, Source, 0, pCSN1CContextSet);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_KeyRequest
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SECURITY_DHKEP_INCFG_KeyRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SECURITY_DHKEP_INCFG_KeyRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_SECURITY_DHKEP_INCFG_KeyRequest (Buffer, BitOffset, Source, 1, pCSN1CContextSet);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_KeyRequest
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SECURITY_DHKEP_INCFG_KeyRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SECURITY_DHKEP_INCFG_KeyRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SECURITY_DHKEP_INCFG_KeyRequest (Buffer, (BitOffset+8), Destin, Length-(8), pCSN1CContextSet);
	if (Len < 0) return Len;
	
	return Len+8;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_KeyRequest
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SECURITY_DHKEP_INCFG_KeyRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SECURITY_DHKEP_INCFG_KeyRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
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
	RetLen = DECODE_c_SECURITY_DHKEP_INCFG_KeyRequest_contents (Buffer, CurrOfs, (&(Destin->contents)), Len, pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:428> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 428, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:429> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 428, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_KeyResponse
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SECURITY_DHKEP_INCFG_KeyResponse (char* Buffer, ED_EXLONG BitOffset, const c_SECURITY_DHKEP_INCFG_KeyResponse* Source, int Mode, struct SCSN1CContextSet* pCSN1CContextSet)
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
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 1, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->contents> DOT=<.> */
		Len = ENCODE_c_SECURITY_DHKEP_INCFG_KeyResponse_contents (Buffer, CurrOfs, (&(Source->contents)), pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:430> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_KeyResponse
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SECURITY_DHKEP_INCFG_KeyResponse (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SECURITY_DHKEP_INCFG_KeyResponse* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_SECURITY_DHKEP_INCFG_KeyResponse (Buffer, BitOffset, Source, 0, pCSN1CContextSet);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_KeyResponse
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SECURITY_DHKEP_INCFG_KeyResponse (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SECURITY_DHKEP_INCFG_KeyResponse* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_SECURITY_DHKEP_INCFG_KeyResponse (Buffer, BitOffset, Source, 1, pCSN1CContextSet);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_KeyResponse
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SECURITY_DHKEP_INCFG_KeyResponse (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SECURITY_DHKEP_INCFG_KeyResponse* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SECURITY_DHKEP_INCFG_KeyResponse (Buffer, (BitOffset+8), Destin, Length-(8), pCSN1CContextSet);
	if (Len < 0) return Len;
	
	return Len+8;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_KeyResponse
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SECURITY_DHKEP_INCFG_KeyResponse (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SECURITY_DHKEP_INCFG_KeyResponse* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
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
	RetLen = DECODE_c_SECURITY_DHKEP_INCFG_KeyResponse_contents (Buffer, CurrOfs, (&(Destin->contents)), Len, pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:431> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 431, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:432> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 431, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_ANKeyComplete
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SECURITY_DHKEP_INCFG_ANKeyComplete (char* Buffer, ED_EXLONG BitOffset, const c_SECURITY_DHKEP_INCFG_ANKeyComplete* Source, int Mode, struct SCSN1CContextSet* pCSN1CContextSet)
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
		Len = ENCODE_c_SECURITY_DHKEP_INCFG_ANKeyComplete_contents (Buffer, CurrOfs, (&(Source->contents)), pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:433> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_ANKeyComplete
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SECURITY_DHKEP_INCFG_ANKeyComplete (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SECURITY_DHKEP_INCFG_ANKeyComplete* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_SECURITY_DHKEP_INCFG_ANKeyComplete (Buffer, BitOffset, Source, 0, pCSN1CContextSet);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_ANKeyComplete
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SECURITY_DHKEP_INCFG_ANKeyComplete (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SECURITY_DHKEP_INCFG_ANKeyComplete* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_SECURITY_DHKEP_INCFG_ANKeyComplete (Buffer, BitOffset, Source, 1, pCSN1CContextSet);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_ANKeyComplete
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SECURITY_DHKEP_INCFG_ANKeyComplete (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SECURITY_DHKEP_INCFG_ANKeyComplete* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SECURITY_DHKEP_INCFG_ANKeyComplete (Buffer, (BitOffset+8), Destin, Length-(8), pCSN1CContextSet);
	if (Len < 0) return Len;
	
	return Len+8;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_ANKeyComplete
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SECURITY_DHKEP_INCFG_ANKeyComplete (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SECURITY_DHKEP_INCFG_ANKeyComplete* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
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
	RetLen = DECODE_c_SECURITY_DHKEP_INCFG_ANKeyComplete_contents (Buffer, CurrOfs, (&(Destin->contents)), Len, pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:434> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 434, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:435> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 434, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_ATKeyComplete
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SECURITY_DHKEP_INCFG_ATKeyComplete (char* Buffer, ED_EXLONG BitOffset, const c_SECURITY_DHKEP_INCFG_ATKeyComplete* Source, int Mode, struct SCSN1CContextSet* pCSN1CContextSet)
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
		Len = ENCODE_c_SECURITY_DHKEP_INCFG_ATKeyComplete_contents (Buffer, CurrOfs, (&(Source->contents)), pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:436> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_ATKeyComplete
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SECURITY_DHKEP_INCFG_ATKeyComplete (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SECURITY_DHKEP_INCFG_ATKeyComplete* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_SECURITY_DHKEP_INCFG_ATKeyComplete (Buffer, BitOffset, Source, 0, pCSN1CContextSet);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_ATKeyComplete
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SECURITY_DHKEP_INCFG_ATKeyComplete (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SECURITY_DHKEP_INCFG_ATKeyComplete* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_SECURITY_DHKEP_INCFG_ATKeyComplete (Buffer, BitOffset, Source, 1, pCSN1CContextSet);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_ATKeyComplete
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SECURITY_DHKEP_INCFG_ATKeyComplete (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SECURITY_DHKEP_INCFG_ATKeyComplete* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SECURITY_DHKEP_INCFG_ATKeyComplete (Buffer, (BitOffset+8), Destin, Length-(8), pCSN1CContextSet);
	if (Len < 0) return Len;
	
	return Len+8;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_ATKeyComplete
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SECURITY_DHKEP_INCFG_ATKeyComplete (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SECURITY_DHKEP_INCFG_ATKeyComplete* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
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
	RetLen = DECODE_c_SECURITY_DHKEP_INCFG_ATKeyComplete_contents (Buffer, CurrOfs, (&(Destin->contents)), Len, pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:437> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 437, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:438> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 437, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_ConfigurationRequest
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SECURITY_DHKEP_INCFG_ConfigurationRequest (char* Buffer, ED_EXLONG BitOffset, const c_SECURITY_DHKEP_INCFG_ConfigurationRequest* Source, int Mode, struct SCSN1CContextSet* pCSN1CContextSet)
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
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 80, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->contents> DOT=<.> */
		Len = ENCODE_c_SECURITY_DHKEP_INCFG_ConfigurationRequest_contents (Buffer, CurrOfs, (&(Source->contents)), pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:439> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_ConfigurationRequest
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SECURITY_DHKEP_INCFG_ConfigurationRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SECURITY_DHKEP_INCFG_ConfigurationRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_SECURITY_DHKEP_INCFG_ConfigurationRequest (Buffer, BitOffset, Source, 0, pCSN1CContextSet);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_ConfigurationRequest
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SECURITY_DHKEP_INCFG_ConfigurationRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SECURITY_DHKEP_INCFG_ConfigurationRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_SECURITY_DHKEP_INCFG_ConfigurationRequest (Buffer, BitOffset, Source, 1, pCSN1CContextSet);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_ConfigurationRequest
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SECURITY_DHKEP_INCFG_ConfigurationRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SECURITY_DHKEP_INCFG_ConfigurationRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SECURITY_DHKEP_INCFG_ConfigurationRequest (Buffer, (BitOffset+8), Destin, Length-(8), pCSN1CContextSet);
	if (Len < 0) return Len;
	
	return Len+8;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_ConfigurationRequest
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SECURITY_DHKEP_INCFG_ConfigurationRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SECURITY_DHKEP_INCFG_ConfigurationRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
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
	RetLen = DECODE_c_SECURITY_DHKEP_INCFG_ConfigurationRequest_contents (Buffer, CurrOfs, (&(Destin->contents)), Len, pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:440> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 440, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:441> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 440, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_ConfigurationResponse
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SECURITY_DHKEP_INCFG_ConfigurationResponse (char* Buffer, ED_EXLONG BitOffset, const c_SECURITY_DHKEP_INCFG_ConfigurationResponse* Source, int Mode, struct SCSN1CContextSet* pCSN1CContextSet)
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
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 81, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->contents> DOT=<.> */
		Len = ENCODE_c_SECURITY_DHKEP_INCFG_ConfigurationResponse_contents (Buffer, CurrOfs, (&(Source->contents)), pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:442> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_ConfigurationResponse
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SECURITY_DHKEP_INCFG_ConfigurationResponse (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SECURITY_DHKEP_INCFG_ConfigurationResponse* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_SECURITY_DHKEP_INCFG_ConfigurationResponse (Buffer, BitOffset, Source, 0, pCSN1CContextSet);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_ConfigurationResponse
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SECURITY_DHKEP_INCFG_ConfigurationResponse (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SECURITY_DHKEP_INCFG_ConfigurationResponse* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_SECURITY_DHKEP_INCFG_ConfigurationResponse (Buffer, BitOffset, Source, 1, pCSN1CContextSet);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_ConfigurationResponse
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SECURITY_DHKEP_INCFG_ConfigurationResponse (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SECURITY_DHKEP_INCFG_ConfigurationResponse* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SECURITY_DHKEP_INCFG_ConfigurationResponse (Buffer, (BitOffset+8), Destin, Length-(8), pCSN1CContextSet);
	if (Len < 0) return Len;
	
	return Len+8;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SECURITY_DHKEP_INCFG_ConfigurationResponse
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SECURITY_DHKEP_INCFG_ConfigurationResponse (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SECURITY_DHKEP_INCFG_ConfigurationResponse* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
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
	RetLen = DECODE_c_SECURITY_DHKEP_INCFG_ConfigurationResponse_contents (Buffer, CurrOfs, (&(Destin->contents)), Len, pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:443> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 443, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:444> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 443, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
int Match_c_SECURITY_DHKEP_INCFG_KeyRequest (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8)) == 0) /* message type */
	);
}

int Match_c_SECURITY_DHKEP_INCFG_KeyResponse (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8)) == 1) /* message type */
	);
}

int Match_c_SECURITY_DHKEP_INCFG_ANKeyComplete (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8)) == 2) /* message type */
	);
}

int Match_c_SECURITY_DHKEP_INCFG_ATKeyComplete (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8)) == 3) /* message type */
	);
}

int Match_c_SECURITY_DHKEP_INCFG_ConfigurationRequest (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8)) == 80) /* message type */
	);
}

int Match_c_SECURITY_DHKEP_INCFG_ConfigurationResponse (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8)) == 81) /* message type */
	);
}

