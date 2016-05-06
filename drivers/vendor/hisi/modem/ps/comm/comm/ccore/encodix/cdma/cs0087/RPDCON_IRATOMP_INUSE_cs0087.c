/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/
/*lint -e959 -e530 -e774 -e572 -e778 -e525 -e539 -e701 -e123 -e438 -e119 -e506 -e529 -e550 -e666 -e713 -e719 -e730 -e734 -e744 -e801 -e801 -e813 -e830 -e40 */
#define ENCODIX_CS0087

#include "RPDCON_IRATOMP_INUSE_cs0087.h"
#include "ed_c_known_ie_cs0087.h"
#include "ed_tlv.h"
#include "CSN1DataTypes_cs0087.h"
#if ED_COMMON_CRC != 0x328E3625 && ED_VERSION != 10152 && ED_VERSION != 10153
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.154
#endif


#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE RPDCON_IRATOMP_INUSE_QuickConfig
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_RPDCON_IRATOMP_INUSE_QuickConfig (char* Buffer, ED_EXLONG BitOffset, const c_RPDCON_IRATOMP_INUSE_QuickConfig* Source, int Mode, struct SCSN1CContextSet* pCSN1CContextSet)
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
		Len = ENCODE_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents (Buffer, CurrOfs, (&(Source->contents)), pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:100> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE RPDCON_IRATOMP_INUSE_QuickConfig
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDCON_IRATOMP_INUSE_QuickConfig (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATOMP_INUSE_QuickConfig* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_RPDCON_IRATOMP_INUSE_QuickConfig (Buffer, BitOffset, Source, 0, pCSN1CContextSet);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE RPDCON_IRATOMP_INUSE_QuickConfig
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDCON_IRATOMP_INUSE_QuickConfig (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATOMP_INUSE_QuickConfig* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_RPDCON_IRATOMP_INUSE_QuickConfig (Buffer, BitOffset, Source, 1, pCSN1CContextSet);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE RPDCON_IRATOMP_INUSE_QuickConfig
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDCON_IRATOMP_INUSE_QuickConfig (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATOMP_INUSE_QuickConfig* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	int Len=0;
	
	Len = DECODE_BODY_c_RPDCON_IRATOMP_INUSE_QuickConfig (Buffer, (BitOffset+8), Destin, Length-(8), pCSN1CContextSet);
	if (Len < 0) return Len;
	
	return Len+8;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE RPDCON_IRATOMP_INUSE_QuickConfig
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDCON_IRATOMP_INUSE_QuickConfig (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATOMP_INUSE_QuickConfig* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
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
	RetLen = DECODE_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents (Buffer, CurrOfs, (&(Destin->contents)), Len, pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:101> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 101, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:102> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 101, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE RPDCON_IRATOMP_INUSE_SectorParameters
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_RPDCON_IRATOMP_INUSE_SectorParameters (char* Buffer, ED_EXLONG BitOffset, const c_RPDCON_IRATOMP_INUSE_SectorParameters* Source, int Mode, struct SCSN1CContextSet* pCSN1CContextSet)
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
		Len = ENCODE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents (Buffer, CurrOfs, (&(Source->contents)), pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:103> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE RPDCON_IRATOMP_INUSE_SectorParameters
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDCON_IRATOMP_INUSE_SectorParameters (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATOMP_INUSE_SectorParameters* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_RPDCON_IRATOMP_INUSE_SectorParameters (Buffer, BitOffset, Source, 0, pCSN1CContextSet);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE RPDCON_IRATOMP_INUSE_SectorParameters
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDCON_IRATOMP_INUSE_SectorParameters (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATOMP_INUSE_SectorParameters* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_RPDCON_IRATOMP_INUSE_SectorParameters (Buffer, BitOffset, Source, 1, pCSN1CContextSet);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE RPDCON_IRATOMP_INUSE_SectorParameters
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDCON_IRATOMP_INUSE_SectorParameters (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATOMP_INUSE_SectorParameters* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	int Len=0;
	
	Len = DECODE_BODY_c_RPDCON_IRATOMP_INUSE_SectorParameters (Buffer, (BitOffset+8), Destin, Length-(8), pCSN1CContextSet);
	if (Len < 0) return Len;
	
	return Len+8;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE RPDCON_IRATOMP_INUSE_SectorParameters
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDCON_IRATOMP_INUSE_SectorParameters (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATOMP_INUSE_SectorParameters* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
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
	RetLen = DECODE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents (Buffer, CurrOfs, (&(Destin->contents)), Len, pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:104> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 104, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:105> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 104, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE RPDCON_IRATOMP_INUSE_HRPDSilenceParameters
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters (char* Buffer, ED_EXLONG BitOffset, const c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters* Source, int Mode, struct SCSN1CContextSet* pCSN1CContextSet)
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
		Len = ENCODE_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters_contents (Buffer, CurrOfs, (&(Source->contents)), pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:106> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE RPDCON_IRATOMP_INUSE_HRPDSilenceParameters
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters (Buffer, BitOffset, Source, 0, pCSN1CContextSet);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE RPDCON_IRATOMP_INUSE_HRPDSilenceParameters
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters (Buffer, BitOffset, Source, 1, pCSN1CContextSet);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE RPDCON_IRATOMP_INUSE_HRPDSilenceParameters
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	int Len=0;
	
	Len = DECODE_BODY_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters (Buffer, (BitOffset+8), Destin, Length-(8), pCSN1CContextSet);
	if (Len < 0) return Len;
	
	return Len+8;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE RPDCON_IRATOMP_INUSE_HRPDSilenceParameters
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
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
	RetLen = DECODE_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters_contents (Buffer, CurrOfs, (&(Destin->contents)), Len, pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:107> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 107, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:108> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 107, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE RPDCON_IRATOMP_INUSE_OtherRATNeighborList
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList (char* Buffer, ED_EXLONG BitOffset, const c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList* Source, int Mode, struct SCSN1CContextSet* pCSN1CContextSet)
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
		Len = ENCODE_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents (Buffer, CurrOfs, (&(Source->contents)), pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:109> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE RPDCON_IRATOMP_INUSE_OtherRATNeighborList
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList (Buffer, BitOffset, Source, 0, pCSN1CContextSet);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE RPDCON_IRATOMP_INUSE_OtherRATNeighborList
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	return L3_ENCODE_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList (Buffer, BitOffset, Source, 1, pCSN1CContextSet);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE RPDCON_IRATOMP_INUSE_OtherRATNeighborList
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	int Len=0;
	
	Len = DECODE_BODY_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList (Buffer, (BitOffset+8), Destin, Length-(8), pCSN1CContextSet);
	if (Len < 0) return Len;
	
	return Len+8;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE RPDCON_IRATOMP_INUSE_OtherRATNeighborList
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
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
	RetLen = DECODE_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents (Buffer, CurrOfs, (&(Destin->contents)), Len, pCSN1CContextSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:110> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 110, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:111> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 110, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
int Match_c_RPDCON_IRATOMP_INUSE_QuickConfig (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8)) == 0) /* message type */
	);
}

int Match_c_RPDCON_IRATOMP_INUSE_SectorParameters (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8)) == 1) /* message type */
	);
}

int Match_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8)) == 2) /* message type */
	);
}

int Match_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8)) == 3) /* message type */
	);
}

