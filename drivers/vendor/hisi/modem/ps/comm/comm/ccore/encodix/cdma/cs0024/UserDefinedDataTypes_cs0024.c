/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/
/*lint -e959 -e530 -e774 -e572 -e778 -e525 -e539 -e701 -e123 -e438 -e119 -e506 -e529 -e550 -e666 -e713 -e719 -e730 -e734 -e744 -e801 -e801 -e813 -e830 -e40 */
#define ENCODIX_CS0024

#include "UserDefinedDataTypes_cs0024.h"
#include "ed_c_known_ie_cs0024.h"
#include "ed_tlv.h"
#include "CSN1DataTypes_cs0024.h"
#if ED_COMMON_CRC != 0x328E3625 && ED_VERSION != 10152 && ED_VERSION != 10153
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.154
#endif


#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Packet_Application_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Packet_Application_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int valueSize = 0;
		int i;
		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0xff: valueSize = 8; break;
			default:;
		}

		if (valueSize > 0) {
			for (i=0; i<Source->Values.items; i++) {
				PUSH_INT (Source->Values.data [i], valueSize);
			}
		}

		return CurrOfs - BitOffset;

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Packet_Application_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Packet_Application_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Default_Packet_Application_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Default_Packet_Application_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}
		int valueSize = 0;

		Destin->AttributeId = (ED_LONG)SHIFT_INT (8);
		switch (Destin->AttributeId) {
			case 0xff: {
				valueSize = 8;
				break;
			}
			default:;
		}
		if (valueSize > 0) {
			int noOfItems = (Length - 8) / valueSize;
			int i;
			SETITEMS_c_Air_Default_Packet_Application_Attributes_Values (&Destin->Values, noOfItems);
			for (i=0; i<noOfItems; i++) {
				Destin->Values.data [i] = (ED_LONG)SHIFT_INT (valueSize);
			}
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Packet_Application_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Packet_Application_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 8);
		/* No complex attributes available for this protocol */
		PUSH_INT (Source->Value, 8);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Packet_Application_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Packet_Application_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(8);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Multi_Flow_Packet_Application_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Multi_Flow_Packet_Application_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int valueSize = 0;
		int i;

		int ret;
#ifndef ED_EXTRAPARAMS_CALL
#define ED_EXTRAPARAMS_CALL
#endif
#define EDX_ENCODE(TYPNAM) case U_c_Air_Multi_Flow_Packet_Application_Attributes_complex_##TYPNAM: ret = ENCODE_c_Air_Multi_Flow_Packet_Application_Attributes_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); if (ret < 0) return ret; CurrOfs+=ret; break;
		PUSH_INT (Source->AttributeId, 16);
		switch (GETPRESENT_c_Air_Multi_Flow_Packet_Application_Attributes_complex (&Source->complex)) {
			EDX_ENCODE (SupportedHigherLayerProtocols)
			EDX_ENCODE (ATSupportedQoSProfiles)
			EDX_ENCODE (ANSupportedQoSProfiles)
			EDX_ENCODE (MaxRLPFlows)
			EDX_ENCODE (MaxReservations)
			EDX_ENCODE (FlowNNIdentificationFwd)
			EDX_ENCODE (FlowNNIdentificationRev)
			EDX_ENCODE (FlowNNTimersFwd)
			EDX_ENCODE (FlowNNTimersRev)
			EDX_ENCODE (FlowNNReservationFwd)
			EDX_ENCODE (FlowNNReservationRev)
			EDX_ENCODE (ReservationKKQoSRequestFwd)
			EDX_ENCODE (ReservationKKQoSRequestRev)
			EDX_ENCODE (ReservationKKQoSResponseFwd)
			EDX_ENCODE (ReservationKKQoSResponseRev)
			default:;
		}
		switch (Source->AttributeId) {
			case 0xfff9: valueSize = 8; break;
			case 0xfffc: valueSize = 8; break;
			case 0xffff: valueSize = 8; break;
			default:;
		}
		if ((Source->AttributeId & 0xff00) == 0xe700) {
			valueSize = 8;
		}
		else if ((Source->AttributeId & 0xff00) == 0xf600) {
			valueSize = 8;
		}
		else if ((Source->AttributeId & 0xff00) == 0xf700) {
			valueSize = 16;
		}
		else if ((Source->AttributeId & 0xff00) == 0xf800) {
			valueSize = 8;
		}
		else if ((Source->AttributeId & 0xff00) == 0xf900) {
			valueSize = 8;
		}
		else if ((Source->AttributeId & 0xff00) == 0xfa00) {
			valueSize = 8;
		}
		else if ((Source->AttributeId & 0xff00) == 0xfb00) {
			valueSize = 8;
		}
		else if ((Source->AttributeId & 0xff00) == 0xfc00) {
			valueSize = 8;
		}
		else if ((Source->AttributeId & 0xff00) == 0xfd00) {
			valueSize = 8;
		}
		else if ((Source->AttributeId & 0xff00) == 0xfe00) {
			valueSize = 8;
		}

		if (valueSize > 0) {
			for (i=0; i<Source->Values.items; i++) {
				PUSH_INT (Source->Values.data [i], valueSize);
			}
		}

		return CurrOfs - BitOffset;
#undef EDX_ENCODE

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Multi_Flow_Packet_Application_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Multi_Flow_Packet_Application_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Multi_Flow_Packet_Application_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Multi_Flow_Packet_Application_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}
		int valueSize = 0;

		Destin->AttributeId = (ED_LONG)SHIFT_INT (16);
		switch (Destin->AttributeId) {
			case 0x0000: {
				EDX_DECODE (SupportedHigherLayerProtocols)
				break;
			}
			case 0x0002: {
				EDX_DECODE (ATSupportedQoSProfiles)
				break;
			}
			case 0x0003: {
				EDX_DECODE (ANSupportedQoSProfiles)
				break;
			}
			case 0x0004: {
				EDX_DECODE (MaxRLPFlows)
				break;
			}
			case 0x0005: {
				EDX_DECODE (MaxReservations)
				break;
			}
			case 0xfff9: {
				valueSize = 8;
				break;
			}
			case 0xfffc: {
				valueSize = 8;
				break;
			}
			case 0xffff: {
				valueSize = 8;
				break;
			}
			default:;
		}
		if ((Destin->AttributeId & 0xff00) == 0x0100) {
			EDX_DECODE (FlowNNIdentificationFwd)
		}
		else if ((Destin->AttributeId & 0xff00) == 0x0200) {
			EDX_DECODE (FlowNNIdentificationRev)
		}
		else if ((Destin->AttributeId & 0xff00) == 0x0300) {
			EDX_DECODE (FlowNNTimersFwd)
		}
		else if ((Destin->AttributeId & 0xff00) == 0x0400) {
			EDX_DECODE (FlowNNTimersRev)
		}
		else if ((Destin->AttributeId & 0xff00) == 0x0500) {
			EDX_DECODE (FlowNNReservationFwd)
		}
		else if ((Destin->AttributeId & 0xff00) == 0x0600) {
			EDX_DECODE (FlowNNReservationRev)
		}
		else if ((Destin->AttributeId & 0xff00) == 0x0700) {
			EDX_DECODE (ReservationKKQoSRequestFwd)
		}
		else if ((Destin->AttributeId & 0xff00) == 0x0800) {
			EDX_DECODE (ReservationKKQoSRequestRev)
		}
		else if ((Destin->AttributeId & 0xff00) == 0x0900) {
			EDX_DECODE (ReservationKKQoSResponseFwd)
		}
		else if ((Destin->AttributeId & 0xff00) == 0x0a00) {
			EDX_DECODE (ReservationKKQoSResponseRev)
		}
		else if ((Destin->AttributeId & 0xff00) == 0xe700) {
			valueSize = 8;
		}
		else if ((Destin->AttributeId & 0xff00) == 0xf600) {
			valueSize = 8;
		}
		else if ((Destin->AttributeId & 0xff00) == 0xf700) {
			valueSize = 16;
		}
		else if ((Destin->AttributeId & 0xff00) == 0xf800) {
			valueSize = 8;
		}
		else if ((Destin->AttributeId & 0xff00) == 0xf900) {
			valueSize = 8;
		}
		else if ((Destin->AttributeId & 0xff00) == 0xfa00) {
			valueSize = 8;
		}
		else if ((Destin->AttributeId & 0xff00) == 0xfb00) {
			valueSize = 8;
		}
		else if ((Destin->AttributeId & 0xff00) == 0xfc00) {
			valueSize = 8;
		}
		else if ((Destin->AttributeId & 0xff00) == 0xfd00) {
			valueSize = 8;
		}
		else if ((Destin->AttributeId & 0xff00) == 0xfe00) {
			valueSize = 8;
		}
		if (valueSize > 0) {
			int noOfItems = (Length - 16) / valueSize;
			int i;
			SETITEMS_c_Air_Multi_Flow_Packet_Application_Attributes_Values (&Destin->Values, noOfItems);
			for (i=0; i<noOfItems; i++) {
				Destin->Values.data [i] = (ED_LONG)SHIFT_INT (valueSize);
			}
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Multi_Flow_Packet_Application_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Multi_Flow_Packet_Application_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 16);
		switch (Source->AttributeId) {
			case 0x0000:
			case 0x0002:
			case 0x0003:
			case 0x0004:
			case 0x0005:
			case 0x0100:
			case 0x0200:
			case 0x0300:
			case 0x0400:
			case 0x0500:
			case 0x0600:
			case 0x0700:
			case 0x0800:
			case 0x0900:
			case 0x0a00: PUSH_INT (Source->Value, 8); break;
			default: PUSH_INT (Source->Value, 8); break;
		}
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Multi_Flow_Packet_Application_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Multi_Flow_Packet_Application_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(16);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Stream_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Stream_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int ret;
#ifndef ED_EXTRAPARAMS_CALL
#define ED_EXTRAPARAMS_CALL
#endif
#define EDX_ENCODE(TYPNAM) case U_c_Air_Default_Stream_Protocol_Attributes_complex_##TYPNAM: ret = ENCODE_c_Air_Default_Stream_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); if (ret < 0) return ret; CurrOfs+=ret; break;
		PUSH_INT (Source->AttributeId, 8);
		switch (GETPRESENT_c_Air_Default_Stream_Protocol_Attributes_complex (&Source->complex)) {
			EDX_ENCODE (StreamConfiguration)
			default:;
		}

		return CurrOfs - BitOffset;
#undef EDX_ENCODE

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Stream_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Stream_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Default_Stream_Protocol_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Default_Stream_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}

		Destin->AttributeId = (ED_LONG)SHIFT_INT (8);
		switch (Destin->AttributeId) {
			case 0x00: {
				EDX_DECODE (StreamConfiguration)
				break;
			}
			default:;
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Stream_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Stream_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0x00: PUSH_INT (Source->Value, 8); break;
			default:;
		}
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Stream_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Stream_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(8);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Generic_Virtual_Stream_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Generic_Virtual_Stream_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int valueSize = 0;
		int i;
		PUSH_INT (Source->AttributeId, 16);
		if ((Source->AttributeId & 0xff00) == 0xff00) {
			valueSize = 16;
		}

		if (valueSize > 0) {
			for (i=0; i<Source->Values.items; i++) {
				PUSH_INT (Source->Values.data [i], valueSize);
			}
		}

		return CurrOfs - BitOffset;

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Generic_Virtual_Stream_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Generic_Virtual_Stream_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Generic_Virtual_Stream_Protocol_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Generic_Virtual_Stream_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}
		int valueSize = 0;

		Destin->AttributeId = (ED_LONG)SHIFT_INT (16);
		if ((Destin->AttributeId & 0xff00) == 0xff00) {
			valueSize = 16;
		}
		if (valueSize > 0) {
			int noOfItems = (Length - 16) / valueSize;
			int i;
			SETITEMS_c_Air_Generic_Virtual_Stream_Protocol_Attributes_Values (&Destin->Values, noOfItems);
			for (i=0; i<noOfItems; i++) {
				Destin->Values.data [i] = (ED_LONG)SHIFT_INT (valueSize);
			}
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Generic_Virtual_Stream_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Generic_Virtual_Stream_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 16);
		/* No complex attributes available for this protocol */
		PUSH_INT (Source->Value, 16);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Generic_Virtual_Stream_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Generic_Virtual_Stream_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(16);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Session_Management_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Session_Management_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int valueSize = 0;
		int i;
		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0xff: valueSize = 16; break;
			default:;
		}

		if (valueSize > 0) {
			for (i=0; i<Source->Values.items; i++) {
				PUSH_INT (Source->Values.data [i], valueSize);
			}
		}

		return CurrOfs - BitOffset;

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Session_Management_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Session_Management_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Default_Session_Management_Protocol_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Default_Session_Management_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}
		int valueSize = 0;

		Destin->AttributeId = (ED_LONG)SHIFT_INT (8);
		switch (Destin->AttributeId) {
			case 0xff: {
				valueSize = 16;
				break;
			}
			default:;
		}
		if (valueSize > 0) {
			int noOfItems = (Length - 8) / valueSize;
			int i;
			SETITEMS_c_Air_Default_Session_Management_Protocol_Attributes_Values (&Destin->Values, noOfItems);
			for (i=0; i<noOfItems; i++) {
				Destin->Values.data [i] = (ED_LONG)SHIFT_INT (valueSize);
			}
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Session_Management_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Session_Management_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 8);
		/* No complex attributes available for this protocol */
		PUSH_INT (Source->Value, 16);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Session_Management_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Session_Management_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(8);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Address_Management_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Address_Management_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int valueSize = 0;
		int i;
		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0xff: valueSize = 16; break; /* EXCEPTION */
			default:;
		}
		switch (Source->AttributeId) {
			case 0xfb: valueSize = 8; break;
			case 0xfc: valueSize = 8; break;
			case 0xfd: valueSize = 8; break;
			case 0xfe: valueSize = 8; break;
			case 0xff: valueSize = 16; break;
			default:;
		}

		if (valueSize > 0) {
			for (i=0; i<Source->Values.items; i++) {
				PUSH_INT (Source->Values.data [i], valueSize);
			}
		}

		return CurrOfs - BitOffset;

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Address_Management_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Address_Management_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Default_Address_Management_Protocol_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Default_Address_Management_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}
		int valueSize = 0;

		Destin->AttributeId = (ED_LONG)SHIFT_INT (8);
		switch (Destin->AttributeId) {
			case 0xfb: {
				valueSize = 8;
				break;
			}
			case 0xfc: {
				valueSize = 8;
				break;
			}
			case 0xfd: {
				valueSize = 8;
				break;
			}
			case 0xfe: {
				valueSize = 8;
				break;
			}
			case 0xff: {
				valueSize = 16;
				break;
			}
			default:;
		}
		if (valueSize > 0) {
			int noOfItems = (Length - 8) / valueSize;
			int i;
			SETITEMS_c_Air_Default_Address_Management_Protocol_Attributes_Values (&Destin->Values, noOfItems);
			for (i=0; i<noOfItems; i++) {
				Destin->Values.data [i] = (ED_LONG)SHIFT_INT (valueSize);
			}
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Address_Management_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Address_Management_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0xff: PUSH_INT (Source->Value, 16); break; /* LEN EXCEPTION */
			default: PUSH_INT (Source->Value, 8); break;
		}
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Address_Management_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Address_Management_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(8);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Session_Configuration_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Session_Configuration_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int valueSize = 0;
		int i;

		int ret;
#ifndef ED_EXTRAPARAMS_CALL
#define ED_EXTRAPARAMS_CALL
#endif
#define EDX_ENCODE(TYPNAM) case U_c_Air_Default_Session_Configuration_Protocol_Attributes_complex_##TYPNAM: ret = ENCODE_c_Air_Default_Session_Configuration_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); if (ret < 0) return ret; CurrOfs+=ret; break;
		PUSH_INT (Source->AttributeId, 16);
		switch (GETPRESENT_c_Air_Default_Session_Configuration_Protocol_Attributes_complex (&Source->complex)) {
			EDX_ENCODE (PriorSession)
			EDX_ENCODE (ATSupportedApplicationSubtypes)
			default:;
		}
		switch (Source->AttributeId) {
			case 0x0100: valueSize = 16; break;
			case 0x0101: valueSize = 16; break;
			case 0x0102: valueSize = 16; break;
			case 0x0110: valueSize = 16; break;
			default:;
		}
		if ((Source->AttributeId & 0xff00) == 0x0000) {
			valueSize = 16;
		}

		if (valueSize > 0) {
			for (i=0; i<Source->Values.items; i++) {
				PUSH_INT (Source->Values.data [i], valueSize);
			}
		}

		return CurrOfs - BitOffset;
#undef EDX_ENCODE

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Session_Configuration_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Session_Configuration_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Default_Session_Configuration_Protocol_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Default_Session_Configuration_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}
		int valueSize = 0;

		Destin->AttributeId = (ED_LONG)SHIFT_INT (16);
		switch (Destin->AttributeId) {
			case 0x1000: {
				EDX_DECODE (PriorSession)
				break;
			}
			case 0x1001: {
				EDX_DECODE (ATSupportedApplicationSubtypes)
				break;
			}
			case 0x0100: {
				valueSize = 16;
				break;
			}
			case 0x0101: {
				valueSize = 16;
				break;
			}
			case 0x0102: {
				valueSize = 16;
				break;
			}
			case 0x0110: {
				valueSize = 16;
				break;
			}
			default:;
		}
		if ((Destin->AttributeId & 0xff00) == 0x0000) {
			valueSize = 16;
		}
		if (valueSize > 0) {
			int noOfItems = (Length - 16) / valueSize;
			int i;
			SETITEMS_c_Air_Default_Session_Configuration_Protocol_Attributes_Values (&Destin->Values, noOfItems);
			for (i=0; i<noOfItems; i++) {
				Destin->Values.data [i] = (ED_LONG)SHIFT_INT (valueSize);
			}
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Session_Configuration_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Session_Configuration_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 16);
		switch (Source->AttributeId) {
			case 0x1000:
			case 0x1001: PUSH_INT (Source->Value, 8); break;
			default: PUSH_INT (Source->Value, 16); break;
		}
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Session_Configuration_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Session_Configuration_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(16);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Generic_Multimode_Capability_Discovery_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Generic_Multimode_Capability_Discovery_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int valueSize = 0;
		int i;
		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0xfa: valueSize = 8; break;
			case 0xfb: valueSize = 8; break;
			case 0xfc: valueSize = 8; break;
			case 0xfd: valueSize = 8; break;
			case 0xfe: valueSize = 8; break;
			case 0xff: valueSize = 8; break;
			default:;
		}

		if (valueSize > 0) {
			for (i=0; i<Source->Values.items; i++) {
				PUSH_INT (Source->Values.data [i], valueSize);
			}
		}

		return CurrOfs - BitOffset;

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Generic_Multimode_Capability_Discovery_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Generic_Multimode_Capability_Discovery_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Generic_Multimode_Capability_Discovery_Protocol_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Generic_Multimode_Capability_Discovery_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}
		int valueSize = 0;

		Destin->AttributeId = (ED_LONG)SHIFT_INT (8);
		switch (Destin->AttributeId) {
			case 0xfa: {
				valueSize = 8;
				break;
			}
			case 0xfb: {
				valueSize = 8;
				break;
			}
			case 0xfc: {
				valueSize = 8;
				break;
			}
			case 0xfd: {
				valueSize = 8;
				break;
			}
			case 0xfe: {
				valueSize = 8;
				break;
			}
			case 0xff: {
				valueSize = 8;
				break;
			}
			default:;
		}
		if (valueSize > 0) {
			int noOfItems = (Length - 8) / valueSize;
			int i;
			SETITEMS_c_Air_Generic_Multimode_Capability_Discovery_Protocol_Attributes_Values (&Destin->Values, noOfItems);
			for (i=0; i<noOfItems; i++) {
				Destin->Values.data [i] = (ED_LONG)SHIFT_INT (valueSize);
			}
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Generic_Multimode_Capability_Discovery_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Generic_Multimode_Capability_Discovery_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 8);
		/* No complex attributes available for this protocol */
		PUSH_INT (Source->Value, 8);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Generic_Multimode_Capability_Discovery_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Generic_Multimode_Capability_Discovery_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(8);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Air_Link_Management_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Air_Link_Management_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int valueSize = 0;
		int i;
		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0xff: valueSize = 8; break;
			default:;
		}

		if (valueSize > 0) {
			for (i=0; i<Source->Values.items; i++) {
				PUSH_INT (Source->Values.data [i], valueSize);
			}
		}

		return CurrOfs - BitOffset;

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Air_Link_Management_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Air_Link_Management_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Default_Air_Link_Management_Protocol_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Default_Air_Link_Management_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}
		int valueSize = 0;

		Destin->AttributeId = (ED_LONG)SHIFT_INT (8);
		switch (Destin->AttributeId) {
			case 0xff: {
				valueSize = 8;
				break;
			}
			default:;
		}
		if (valueSize > 0) {
			int noOfItems = (Length - 8) / valueSize;
			int i;
			SETITEMS_c_Air_Default_Air_Link_Management_Protocol_Attributes_Values (&Destin->Values, noOfItems);
			for (i=0; i<noOfItems; i++) {
				Destin->Values.data [i] = (ED_LONG)SHIFT_INT (valueSize);
			}
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Air_Link_Management_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Air_Link_Management_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 8);
		/* No complex attributes available for this protocol */
		PUSH_INT (Source->Value, 8);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Air_Link_Management_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Air_Link_Management_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(8);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Idle_State_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Idle_State_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int ret;
#ifndef ED_EXTRAPARAMS_CALL
#define ED_EXTRAPARAMS_CALL
#endif
#define EDX_ENCODE(TYPNAM) case U_c_Air_Default_Idle_State_Protocol_Attributes_complex_##TYPNAM: ret = ENCODE_c_Air_Default_Idle_State_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); if (ret < 0) return ret; CurrOfs+=ret; break;
		PUSH_INT (Source->AttributeId, 8);
		switch (GETPRESENT_c_Air_Default_Idle_State_Protocol_Attributes_complex (&Source->complex)) {
			EDX_ENCODE (PreferredControlChannelCycle)
			default:;
		}

		return CurrOfs - BitOffset;
#undef EDX_ENCODE

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Idle_State_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Idle_State_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Default_Idle_State_Protocol_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Default_Idle_State_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}

		Destin->AttributeId = (ED_LONG)SHIFT_INT (8);
		switch (Destin->AttributeId) {
			case 0x00: {
				EDX_DECODE (PreferredControlChannelCycle)
				break;
			}
			default:;
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Idle_State_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Idle_State_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0x00: PUSH_INT (Source->Value, 8); break;
			default:;
		}
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Idle_State_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Idle_State_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(8);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Enhanced_Idle_State_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Enhanced_Idle_State_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int valueSize = 0;
		int i;

		int ret;
#ifndef ED_EXTRAPARAMS_CALL
#define ED_EXTRAPARAMS_CALL
#endif
#define EDX_ENCODE(TYPNAM) case U_c_Air_Enhanced_Idle_State_Protocol_Attributes_complex_##TYPNAM: ret = ENCODE_c_Air_Enhanced_Idle_State_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); if (ret < 0) return ret; CurrOfs+=ret; break;
		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0xfe: valueSize = 16; break; /* EXCEPTION */
			default:;
		}
		switch (GETPRESENT_c_Air_Enhanced_Idle_State_Protocol_Attributes_complex (&Source->complex)) {
			EDX_ENCODE (PreferredControlChannelCycle)
			EDX_ENCODE (SlottedMode)
			EDX_ENCODE (PagingMask)
			default:;
		}
		switch (Source->AttributeId) {
			case 0xfc: valueSize = 8; break;
			case 0xfd: valueSize = 8; break;
			case 0xfe: valueSize = 16; break;
			case 0xff: valueSize = 8; break;
			default:;
		}

		if (valueSize > 0) {
			for (i=0; i<Source->Values.items; i++) {
				PUSH_INT (Source->Values.data [i], valueSize);
			}
		}

		return CurrOfs - BitOffset;
#undef EDX_ENCODE

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Enhanced_Idle_State_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Enhanced_Idle_State_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Enhanced_Idle_State_Protocol_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Enhanced_Idle_State_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}
		int valueSize = 0;

		Destin->AttributeId = (ED_LONG)SHIFT_INT (8);
		switch (Destin->AttributeId) {
			case 0x00: {
				EDX_DECODE (PreferredControlChannelCycle)
				break;
			}
			case 0x01: {
				EDX_DECODE (SlottedMode)
				break;
			}
			case 0x02: {
				EDX_DECODE (PagingMask)
				break;
			}
			case 0xfc: {
				valueSize = 8;
				break;
			}
			case 0xfd: {
				valueSize = 8;
				break;
			}
			case 0xfe: {
				valueSize = 16;
				break;
			}
			case 0xff: {
				valueSize = 8;
				break;
			}
			default:;
		}
		if (valueSize > 0) {
			int noOfItems = (Length - 8) / valueSize;
			int i;
			SETITEMS_c_Air_Enhanced_Idle_State_Protocol_Attributes_Values (&Destin->Values, noOfItems);
			for (i=0; i<noOfItems; i++) {
				Destin->Values.data [i] = (ED_LONG)SHIFT_INT (valueSize);
			}
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Enhanced_Idle_State_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Enhanced_Idle_State_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0xfe: PUSH_INT (Source->Value, 16); break; /* LEN EXCEPTION */
			case 0x00:
			case 0x01:
			case 0x02: PUSH_INT (Source->Value, 8); break;
			default: PUSH_INT (Source->Value, 8); break;
		}
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Enhanced_Idle_State_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Enhanced_Idle_State_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(8);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Quick_Idle_State_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Quick_Idle_State_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int valueSize = 0;
		int i;

		int ret;
#ifndef ED_EXTRAPARAMS_CALL
#define ED_EXTRAPARAMS_CALL
#endif
#define EDX_ENCODE(TYPNAM) case U_c_Air_Quick_Idle_State_Protocol_Attributes_complex_##TYPNAM: ret = ENCODE_c_Air_Quick_Idle_State_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); if (ret < 0) return ret; CurrOfs+=ret; break;
		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0xfe: valueSize = 16; break; /* EXCEPTION */
			default:;
		}
		switch (GETPRESENT_c_Air_Quick_Idle_State_Protocol_Attributes_complex (&Source->complex)) {
			EDX_ENCODE (PreferredControlChannelCycle)
			EDX_ENCODE (SlottedMode)
			EDX_ENCODE (PagingMask)
			EDX_ENCODE (QuickPaging)
			default:;
		}
		switch (Source->AttributeId) {
			case 0xfc: valueSize = 8; break;
			case 0xfd: valueSize = 8; break;
			case 0xfe: valueSize = 16; break;
			case 0xff: valueSize = 8; break;
			default:;
		}

		if (valueSize > 0) {
			for (i=0; i<Source->Values.items; i++) {
				PUSH_INT (Source->Values.data [i], valueSize);
			}
		}

		return CurrOfs - BitOffset;
#undef EDX_ENCODE

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Quick_Idle_State_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Quick_Idle_State_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Quick_Idle_State_Protocol_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Quick_Idle_State_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}
		int valueSize = 0;

		Destin->AttributeId = (ED_LONG)SHIFT_INT (8);
		switch (Destin->AttributeId) {
			case 0x00: {
				EDX_DECODE (PreferredControlChannelCycle)
				break;
			}
			case 0x01: {
				EDX_DECODE (SlottedMode)
				break;
			}
			case 0x02: {
				EDX_DECODE (PagingMask)
				break;
			}
			case 0x03: {
				EDX_DECODE (QuickPaging)
				break;
			}
			case 0xfc: {
				valueSize = 8;
				break;
			}
			case 0xfd: {
				valueSize = 8;
				break;
			}
			case 0xfe: {
				valueSize = 16;
				break;
			}
			case 0xff: {
				valueSize = 8;
				break;
			}
			default:;
		}
		if (valueSize > 0) {
			int noOfItems = (Length - 8) / valueSize;
			int i;
			SETITEMS_c_Air_Quick_Idle_State_Protocol_Attributes_Values (&Destin->Values, noOfItems);
			for (i=0; i<noOfItems; i++) {
				Destin->Values.data [i] = (ED_LONG)SHIFT_INT (valueSize);
			}
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Quick_Idle_State_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Quick_Idle_State_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0xfe: PUSH_INT (Source->Value, 16); break; /* LEN EXCEPTION */
			case 0x00:
			case 0x01:
			case 0x02:
			case 0x03: PUSH_INT (Source->Value, 8); break;
			default: PUSH_INT (Source->Value, 8); break;
		}
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Quick_Idle_State_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Quick_Idle_State_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(8);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Route_Update_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Route_Update_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int valueSize = 0;
		int i;

		int ret;
#ifndef ED_EXTRAPARAMS_CALL
#define ED_EXTRAPARAMS_CALL
#endif
#define EDX_ENCODE(TYPNAM) case U_c_Air_Default_Route_Update_Protocol_Attributes_complex_##TYPNAM: ret = ENCODE_c_Air_Default_Route_Update_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); if (ret < 0) return ret; CurrOfs+=ret; break;
		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0xfe: valueSize = 16; break; /* EXCEPTION */
			default:;
		}
		switch (GETPRESENT_c_Air_Default_Route_Update_Protocol_Attributes_complex (&Source->complex)) {
			EDX_ENCODE (SearchParameters)
			EDX_ENCODE (SetManagementSameChannelParameters)
			EDX_ENCODE (SetManagementDifferentChannelParameters)
			EDX_ENCODE (SupportedCDMAChannels)
			default:;
		}
		switch (Source->AttributeId) {
			case 0x03: valueSize = 8; break;
			case 0xfd: valueSize = 8; break;
			case 0xfe: valueSize = 16; break;
			case 0xff: valueSize = 8; break;
			default:;
		}

		if (valueSize > 0) {
			for (i=0; i<Source->Values.items; i++) {
				PUSH_INT (Source->Values.data [i], valueSize);
			}
		}

		return CurrOfs - BitOffset;
#undef EDX_ENCODE

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Route_Update_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Route_Update_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Default_Route_Update_Protocol_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Default_Route_Update_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}
		int valueSize = 0;

		Destin->AttributeId = (ED_LONG)SHIFT_INT (8);
		switch (Destin->AttributeId) {
			case 0x00: {
				EDX_DECODE (SearchParameters)
				break;
			}
			case 0x01: {
				EDX_DECODE (SetManagementSameChannelParameters)
				break;
			}
			case 0x02: {
				EDX_DECODE (SetManagementDifferentChannelParameters)
				break;
			}
			case 0x04: {
				EDX_DECODE (SupportedCDMAChannels)
				break;
			}
			case 0x03: {
				valueSize = 8;
				break;
			}
			case 0xfd: {
				valueSize = 8;
				break;
			}
			case 0xfe: {
				valueSize = 16;
				break;
			}
			case 0xff: {
				valueSize = 8;
				break;
			}
			default:;
		}
		if (valueSize > 0) {
			int noOfItems = (Length - 8) / valueSize;
			int i;
			SETITEMS_c_Air_Default_Route_Update_Protocol_Attributes_Values (&Destin->Values, noOfItems);
			for (i=0; i<noOfItems; i++) {
				Destin->Values.data [i] = (ED_LONG)SHIFT_INT (valueSize);
			}
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Route_Update_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Route_Update_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0xfe: PUSH_INT (Source->Value, 16); break; /* LEN EXCEPTION */
			case 0x00:
			case 0x01:
			case 0x02:
			case 0x04: PUSH_INT (Source->Value, 8); break;
			default: PUSH_INT (Source->Value, 8); break;
		}
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Route_Update_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Route_Update_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(8);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Multicarrier_Route_Update_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Multicarrier_Route_Update_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int valueSize = 0;
		int i;

		int ret;
#ifndef ED_EXTRAPARAMS_CALL
#define ED_EXTRAPARAMS_CALL
#endif
#define EDX_ENCODE(TYPNAM) case U_c_Air_Multicarrier_Route_Update_Protocol_Attributes_complex_##TYPNAM: ret = ENCODE_c_Air_Multicarrier_Route_Update_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); if (ret < 0) return ret; CurrOfs+=ret; break;
		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0xfe: valueSize = 16; break; /* EXCEPTION */
			default:;
		}
		switch (GETPRESENT_c_Air_Multicarrier_Route_Update_Protocol_Attributes_complex (&Source->complex)) {
			EDX_ENCODE (SearchParameters)
			EDX_ENCODE (SetManagementParameters)
			EDX_ENCODE (SupportedCDMAChannels)
			EDX_ENCODE (SupportedDRXPatterns)
			default:;
		}
		switch (Source->AttributeId) {
			case 0xf6: valueSize = 8; break;
			case 0xf7: valueSize = 8; break;
			case 0xf8: valueSize = 8; break;
			case 0xf9: valueSize = 8; break;
			case 0xfa: valueSize = 8; break;
			case 0xfb: valueSize = 8; break;
			case 0xfc: valueSize = 8; break;
			case 0xfd: valueSize = 8; break;
			case 0xfe: valueSize = 16; break;
			case 0xff: valueSize = 8; break;
			default:;
		}

		if (valueSize > 0) {
			for (i=0; i<Source->Values.items; i++) {
				PUSH_INT (Source->Values.data [i], valueSize);
			}
		}

		return CurrOfs - BitOffset;
#undef EDX_ENCODE

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Multicarrier_Route_Update_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Multicarrier_Route_Update_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Multicarrier_Route_Update_Protocol_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Multicarrier_Route_Update_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}
		int valueSize = 0;

		Destin->AttributeId = (ED_LONG)SHIFT_INT (8);
		switch (Destin->AttributeId) {
			case 0x00: {
				EDX_DECODE (SearchParameters)
				break;
			}
			case 0x01: {
				EDX_DECODE (SetManagementParameters)
				break;
			}
			case 0x04: {
				EDX_DECODE (SupportedCDMAChannels)
				break;
			}
			case 0x05: {
				EDX_DECODE (SupportedDRXPatterns)
				break;
			}
			case 0xf6: {
				valueSize = 8;
				break;
			}
			case 0xf7: {
				valueSize = 8;
				break;
			}
			case 0xf8: {
				valueSize = 8;
				break;
			}
			case 0xf9: {
				valueSize = 8;
				break;
			}
			case 0xfa: {
				valueSize = 8;
				break;
			}
			case 0xfb: {
				valueSize = 8;
				break;
			}
			case 0xfc: {
				valueSize = 8;
				break;
			}
			case 0xfd: {
				valueSize = 8;
				break;
			}
			case 0xfe: {
				valueSize = 16;
				break;
			}
			case 0xff: {
				valueSize = 8;
				break;
			}
			default:;
		}
		if (valueSize > 0) {
			int noOfItems = (Length - 8) / valueSize;
			int i;
			SETITEMS_c_Air_Multicarrier_Route_Update_Protocol_Attributes_Values (&Destin->Values, noOfItems);
			for (i=0; i<noOfItems; i++) {
				Destin->Values.data [i] = (ED_LONG)SHIFT_INT (valueSize);
			}
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Multicarrier_Route_Update_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Multicarrier_Route_Update_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0xfe: PUSH_INT (Source->Value, 16); break; /* LEN EXCEPTION */
			case 0x00:
			case 0x01:
			case 0x04:
			case 0x05: PUSH_INT (Source->Value, 8); break;
			default: PUSH_INT (Source->Value, 8); break;
		}
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Multicarrier_Route_Update_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Multicarrier_Route_Update_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(8);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Overhead_Messages_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Overhead_Messages_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int valueSize = 0;
		int i;
		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0xfc: valueSize = 8; break;
			case 0xfd: valueSize = 8; break;
			case 0xfe: valueSize = 8; break;
			case 0xff: valueSize = 8; break;
			default:;
		}

		if (valueSize > 0) {
			for (i=0; i<Source->Values.items; i++) {
				PUSH_INT (Source->Values.data [i], valueSize);
			}
		}

		return CurrOfs - BitOffset;

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Overhead_Messages_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Overhead_Messages_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Overhead_Messages_Protocol_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Overhead_Messages_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}
		int valueSize = 0;

		Destin->AttributeId = (ED_LONG)SHIFT_INT (8);
		switch (Destin->AttributeId) {
			case 0xfc: {
				valueSize = 8;
				break;
			}
			case 0xfd: {
				valueSize = 8;
				break;
			}
			case 0xfe: {
				valueSize = 8;
				break;
			}
			case 0xff: {
				valueSize = 8;
				break;
			}
			default:;
		}
		if (valueSize > 0) {
			int noOfItems = (Length - 8) / valueSize;
			int i;
			SETITEMS_c_Air_Overhead_Messages_Protocol_Attributes_Values (&Destin->Values, noOfItems);
			for (i=0; i<noOfItems; i++) {
				Destin->Values.data [i] = (ED_LONG)SHIFT_INT (valueSize);
			}
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Overhead_Messages_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Overhead_Messages_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 8);
		/* No complex attributes available for this protocol */
		PUSH_INT (Source->Value, 8);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Overhead_Messages_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Overhead_Messages_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(8);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_DH_Key_Exchange_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_DH_Key_Exchange_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int valueSize = 0;
		int i;
		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0x00: valueSize = 8; break;
			default:;
		}

		if (valueSize > 0) {
			for (i=0; i<Source->Values.items; i++) {
				PUSH_INT (Source->Values.data [i], valueSize);
			}
		}

		return CurrOfs - BitOffset;

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_DH_Key_Exchange_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_DH_Key_Exchange_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_DH_Key_Exchange_Protocol_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_DH_Key_Exchange_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}
		int valueSize = 0;

		Destin->AttributeId = (ED_LONG)SHIFT_INT (8);
		switch (Destin->AttributeId) {
			case 0x00: {
				valueSize = 8;
				break;
			}
			default:;
		}
		if (valueSize > 0) {
			int noOfItems = (Length - 8) / valueSize;
			int i;
			SETITEMS_c_Air_DH_Key_Exchange_Protocol_Attributes_Values (&Destin->Values, noOfItems);
			for (i=0; i<noOfItems; i++) {
				Destin->Values.data [i] = (ED_LONG)SHIFT_INT (valueSize);
			}
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_DH_Key_Exchange_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_DH_Key_Exchange_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 8);
		/* No complex attributes available for this protocol */
		PUSH_INT (Source->Value, 8);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_DH_Key_Exchange_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_DH_Key_Exchange_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(8);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_SHA_1_Authentication_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_SHA_1_Authentication_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int valueSize = 0;
		int i;
		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0x00: valueSize = 16; break;
			default:;
		}

		if (valueSize > 0) {
			for (i=0; i<Source->Values.items; i++) {
				PUSH_INT (Source->Values.data [i], valueSize);
			}
		}

		return CurrOfs - BitOffset;

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_SHA_1_Authentication_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_SHA_1_Authentication_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_SHA_1_Authentication_Protocol_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_SHA_1_Authentication_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}
		int valueSize = 0;

		Destin->AttributeId = (ED_LONG)SHIFT_INT (8);
		switch (Destin->AttributeId) {
			case 0x00: {
				valueSize = 16;
				break;
			}
			default:;
		}
		if (valueSize > 0) {
			int noOfItems = (Length - 8) / valueSize;
			int i;
			SETITEMS_c_Air_SHA_1_Authentication_Protocol_Attributes_Values (&Destin->Values, noOfItems);
			for (i=0; i<noOfItems; i++) {
				Destin->Values.data [i] = (ED_LONG)SHIFT_INT (valueSize);
			}
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_SHA_1_Authentication_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_SHA_1_Authentication_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 8);
		/* No complex attributes available for this protocol */
		PUSH_INT (Source->Value, 16);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_SHA_1_Authentication_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_SHA_1_Authentication_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(8);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Enhanced_Control_Channel_MAC_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Enhanced_Control_Channel_MAC_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int valueSize = 0;
		int i;
		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0x00: valueSize = 8; break;
			default:;
		}

		if (valueSize > 0) {
			for (i=0; i<Source->Values.items; i++) {
				PUSH_INT (Source->Values.data [i], valueSize);
			}
		}

		return CurrOfs - BitOffset;

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Enhanced_Control_Channel_MAC_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Enhanced_Control_Channel_MAC_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Enhanced_Control_Channel_MAC_Protocol_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Enhanced_Control_Channel_MAC_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}
		int valueSize = 0;

		Destin->AttributeId = (ED_LONG)SHIFT_INT (8);
		switch (Destin->AttributeId) {
			case 0x00: {
				valueSize = 8;
				break;
			}
			default:;
		}
		if (valueSize > 0) {
			int noOfItems = (Length - 8) / valueSize;
			int i;
			SETITEMS_c_Air_Enhanced_Control_Channel_MAC_Protocol_Attributes_Values (&Destin->Values, noOfItems);
			for (i=0; i<noOfItems; i++) {
				Destin->Values.data [i] = (ED_LONG)SHIFT_INT (valueSize);
			}
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Enhanced_Control_Channel_MAC_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Enhanced_Control_Channel_MAC_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 8);
		/* No complex attributes available for this protocol */
		PUSH_INT (Source->Value, 8);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Enhanced_Control_Channel_MAC_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Enhanced_Control_Channel_MAC_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(8);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Access_Channel_MAC_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Access_Channel_MAC_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int ret;
#ifndef ED_EXTRAPARAMS_CALL
#define ED_EXTRAPARAMS_CALL
#endif
#define EDX_ENCODE(TYPNAM) case U_c_Air_Default_Access_Channel_MAC_Protocol_Attributes_complex_##TYPNAM: ret = ENCODE_c_Air_Default_Access_Channel_MAC_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); if (ret < 0) return ret; CurrOfs+=ret; break;
		PUSH_INT (Source->AttributeId, 8);
		switch (GETPRESENT_c_Air_Default_Access_Channel_MAC_Protocol_Attributes_complex (&Source->complex)) {
			EDX_ENCODE (InitialConfiguration)
			EDX_ENCODE (PowerParameters)
			default:;
		}

		return CurrOfs - BitOffset;
#undef EDX_ENCODE

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Access_Channel_MAC_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Access_Channel_MAC_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Default_Access_Channel_MAC_Protocol_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Default_Access_Channel_MAC_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}

		Destin->AttributeId = (ED_LONG)SHIFT_INT (8);
		switch (Destin->AttributeId) {
			case 0x00: {
				EDX_DECODE (InitialConfiguration)
				break;
			}
			case 0x01: {
				EDX_DECODE (PowerParameters)
				break;
			}
			default:;
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Access_Channel_MAC_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Access_Channel_MAC_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0x00:
			case 0x01: PUSH_INT (Source->Value, 8); break;
			default:;
		}
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Access_Channel_MAC_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Access_Channel_MAC_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(8);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Enhanced_Access_Channel_MAC_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Enhanced_Access_Channel_MAC_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int valueSize = 0;
		int i;

		int ret;
#ifndef ED_EXTRAPARAMS_CALL
#define ED_EXTRAPARAMS_CALL
#endif
#define EDX_ENCODE(TYPNAM) case U_c_Air_Enhanced_Access_Channel_MAC_Protocol_Attributes_complex_##TYPNAM: ret = ENCODE_c_Air_Enhanced_Access_Channel_MAC_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); if (ret < 0) return ret; CurrOfs+=ret; break;
		PUSH_INT (Source->AttributeId, 8);
		switch (GETPRESENT_c_Air_Enhanced_Access_Channel_MAC_Protocol_Attributes_complex (&Source->complex)) {
			EDX_ENCODE (InitialConfiguration)
			default:;
		}
		switch (Source->AttributeId) {
			case 0xf8: valueSize = 8; break;
			case 0xf9: valueSize = 8; break;
			case 0xfa: valueSize = 8; break;
			case 0xfb: valueSize = 8; break;
			case 0xfc: valueSize = 8; break;
			case 0xfd: valueSize = 8; break;
			case 0xfe: valueSize = 8; break;
			case 0xff: valueSize = 8; break;
			default:;
		}

		if (valueSize > 0) {
			for (i=0; i<Source->Values.items; i++) {
				PUSH_INT (Source->Values.data [i], valueSize);
			}
		}

		return CurrOfs - BitOffset;
#undef EDX_ENCODE

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Enhanced_Access_Channel_MAC_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Enhanced_Access_Channel_MAC_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Enhanced_Access_Channel_MAC_Protocol_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Enhanced_Access_Channel_MAC_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}
		int valueSize = 0;

		Destin->AttributeId = (ED_LONG)SHIFT_INT (8);
		switch (Destin->AttributeId) {
			case 0x00: {
				EDX_DECODE (InitialConfiguration)
				break;
			}
			case 0xf8: {
				valueSize = 8;
				break;
			}
			case 0xf9: {
				valueSize = 8;
				break;
			}
			case 0xfa: {
				valueSize = 8;
				break;
			}
			case 0xfb: {
				valueSize = 8;
				break;
			}
			case 0xfc: {
				valueSize = 8;
				break;
			}
			case 0xfd: {
				valueSize = 8;
				break;
			}
			case 0xfe: {
				valueSize = 8;
				break;
			}
			case 0xff: {
				valueSize = 8;
				break;
			}
			default:;
		}
		if (valueSize > 0) {
			int noOfItems = (Length - 8) / valueSize;
			int i;
			SETITEMS_c_Air_Enhanced_Access_Channel_MAC_Protocol_Attributes_Values (&Destin->Values, noOfItems);
			for (i=0; i<noOfItems; i++) {
				Destin->Values.data [i] = (ED_LONG)SHIFT_INT (valueSize);
			}
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Enhanced_Access_Channel_MAC_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Enhanced_Access_Channel_MAC_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0x00: PUSH_INT (Source->Value, 8); break;
			default: PUSH_INT (Source->Value, 8); break;
		}
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Enhanced_Access_Channel_MAC_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Enhanced_Access_Channel_MAC_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(8);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Forward_Traffic_Channel_MAC_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Forward_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int valueSize = 0;
		int i;

		int ret;
#ifndef ED_EXTRAPARAMS_CALL
#define ED_EXTRAPARAMS_CALL
#endif
#define EDX_ENCODE(TYPNAM) case U_c_Air_Default_Forward_Traffic_Channel_MAC_Protocol_Attributes_complex_##TYPNAM: ret = ENCODE_c_Air_Default_Forward_Traffic_Channel_MAC_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); if (ret < 0) return ret; CurrOfs+=ret; break;
		PUSH_INT (Source->AttributeId, 8);
		switch (GETPRESENT_c_Air_Default_Forward_Traffic_Channel_MAC_Protocol_Attributes_complex (&Source->complex)) {
			EDX_ENCODE (HandoffDelays)
			EDX_ENCODE (DRCLock)
			default:;
		}
		switch (Source->AttributeId) {
			case 0xfd: valueSize = 16; break;
			case 0xff: valueSize = 16; break;
			default:;
		}

		if (valueSize > 0) {
			for (i=0; i<Source->Values.items; i++) {
				PUSH_INT (Source->Values.data [i], valueSize);
			}
		}

		return CurrOfs - BitOffset;
#undef EDX_ENCODE

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Forward_Traffic_Channel_MAC_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Forward_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Default_Forward_Traffic_Channel_MAC_Protocol_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Default_Forward_Traffic_Channel_MAC_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}
		int valueSize = 0;

		Destin->AttributeId = (ED_LONG)SHIFT_INT (8);
		switch (Destin->AttributeId) {
			case 0x00: {
				EDX_DECODE (HandoffDelays)
				break;
			}
			case 0x01: {
				EDX_DECODE (DRCLock)
				break;
			}
			case 0xfd: {
				valueSize = 16;
				break;
			}
			case 0xff: {
				valueSize = 16;
				break;
			}
			default:;
		}
		if (valueSize > 0) {
			int noOfItems = (Length - 8) / valueSize;
			int i;
			SETITEMS_c_Air_Default_Forward_Traffic_Channel_MAC_Protocol_Attributes_Values (&Destin->Values, noOfItems);
			for (i=0; i<noOfItems; i++) {
				Destin->Values.data [i] = (ED_LONG)SHIFT_INT (valueSize);
			}
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0x00:
			case 0x01: PUSH_INT (Source->Value, 8); break;
			default: PUSH_INT (Source->Value, 16); break;
		}
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(8);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Enhanced_Forward_Traffic_Channel_MAC_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Enhanced_Forward_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int valueSize = 0;
		int i;

		int ret;
#ifndef ED_EXTRAPARAMS_CALL
#define ED_EXTRAPARAMS_CALL
#endif
#define EDX_ENCODE(TYPNAM) case U_c_Air_Enhanced_Forward_Traffic_Channel_MAC_Protocol_Attributes_complex_##TYPNAM: ret = ENCODE_c_Air_Enhanced_Forward_Traffic_Channel_MAC_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); if (ret < 0) return ret; CurrOfs+=ret; break;
		PUSH_INT (Source->AttributeId, 8);
		switch (GETPRESENT_c_Air_Enhanced_Forward_Traffic_Channel_MAC_Protocol_Attributes_complex (&Source->complex)) {
			EDX_ENCODE (HandoffDelays)
			EDX_ENCODE (DRCTranslationOffset)
			default:;
		}
		switch (Source->AttributeId) {
			case 0xf3: valueSize = 8; break;
			case 0xf4: valueSize = 8; break;
			case 0xf5: valueSize = 8; break;
			case 0xf6: valueSize = 8; break;
			case 0xf7: valueSize = 8; break;
			case 0xf8: valueSize = 8; break;
			case 0xf9: valueSize = 8; break;
			case 0xfa: valueSize = 8; break;
			case 0xfb: valueSize = 8; break;
			case 0xfc: valueSize = 8; break;
			case 0xfd: valueSize = 8; break;
			case 0xfe: valueSize = 8; break;
			case 0xff: valueSize = 8; break;
			default:;
		}

		if (valueSize > 0) {
			for (i=0; i<Source->Values.items; i++) {
				PUSH_INT (Source->Values.data [i], valueSize);
			}
		}

		return CurrOfs - BitOffset;
#undef EDX_ENCODE

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Enhanced_Forward_Traffic_Channel_MAC_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Enhanced_Forward_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Enhanced_Forward_Traffic_Channel_MAC_Protocol_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Enhanced_Forward_Traffic_Channel_MAC_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}
		int valueSize = 0;

		Destin->AttributeId = (ED_LONG)SHIFT_INT (8);
		switch (Destin->AttributeId) {
			case 0x00: {
				EDX_DECODE (HandoffDelays)
				break;
			}
			case 0x01: {
				EDX_DECODE (DRCTranslationOffset)
				break;
			}
			case 0xf3: {
				valueSize = 8;
				break;
			}
			case 0xf4: {
				valueSize = 8;
				break;
			}
			case 0xf5: {
				valueSize = 8;
				break;
			}
			case 0xf6: {
				valueSize = 8;
				break;
			}
			case 0xf7: {
				valueSize = 8;
				break;
			}
			case 0xf8: {
				valueSize = 8;
				break;
			}
			case 0xf9: {
				valueSize = 8;
				break;
			}
			case 0xfa: {
				valueSize = 8;
				break;
			}
			case 0xfb: {
				valueSize = 8;
				break;
			}
			case 0xfc: {
				valueSize = 8;
				break;
			}
			case 0xfd: {
				valueSize = 8;
				break;
			}
			case 0xfe: {
				valueSize = 8;
				break;
			}
			case 0xff: {
				valueSize = 8;
				break;
			}
			default:;
		}
		if (valueSize > 0) {
			int noOfItems = (Length - 8) / valueSize;
			int i;
			SETITEMS_c_Air_Enhanced_Forward_Traffic_Channel_MAC_Protocol_Attributes_Values (&Destin->Values, noOfItems);
			for (i=0; i<noOfItems; i++) {
				Destin->Values.data [i] = (ED_LONG)SHIFT_INT (valueSize);
			}
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Enhanced_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Enhanced_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0x00:
			case 0x01: PUSH_INT (Source->Value, 8); break;
			default: PUSH_INT (Source->Value, 8); break;
		}
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Enhanced_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Enhanced_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(8);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Multicarrier_Forward_Traffic_Channel_MAC_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Multicarrier_Forward_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int valueSize = 0;
		int i;

		int ret;
#ifndef ED_EXTRAPARAMS_CALL
#define ED_EXTRAPARAMS_CALL
#endif
#define EDX_ENCODE(TYPNAM) case U_c_Air_Multicarrier_Forward_Traffic_Channel_MAC_Protocol_Attributes_complex_##TYPNAM: ret = ENCODE_c_Air_Multicarrier_Forward_Traffic_Channel_MAC_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); if (ret < 0) return ret; CurrOfs+=ret; break;
		PUSH_INT (Source->AttributeId, 8);
		switch (GETPRESENT_c_Air_Multicarrier_Forward_Traffic_Channel_MAC_Protocol_Attributes_complex (&Source->complex)) {
			EDX_ENCODE (HandoffDelays)
			EDX_ENCODE (ATSupportedPacketFormats)
			EDX_ENCODE (TentativeDRCtoTxDRCMap)
			EDX_ENCODE (ExtendedSpans)
			default:;
		}
		switch (Source->AttributeId) {
			case 0xef: valueSize = 8; break;
			case 0xf0: valueSize = 8; break;
			case 0xf2: valueSize = 8; break;
			case 0xf3: valueSize = 8; break;
			case 0xf4: valueSize = 8; break;
			case 0xf5: valueSize = 8; break;
			case 0xf6: valueSize = 8; break;
			case 0xf7: valueSize = 8; break;
			case 0xf8: valueSize = 8; break;
			case 0xfb: valueSize = 8; break;
			case 0xfc: valueSize = 8; break;
			case 0xfe: valueSize = 8; break;
			case 0xff: valueSize = 8; break;
			default:;
		}

		if (valueSize > 0) {
			for (i=0; i<Source->Values.items; i++) {
				PUSH_INT (Source->Values.data [i], valueSize);
			}
		}

		return CurrOfs - BitOffset;
#undef EDX_ENCODE

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Multicarrier_Forward_Traffic_Channel_MAC_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Multicarrier_Forward_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Multicarrier_Forward_Traffic_Channel_MAC_Protocol_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Multicarrier_Forward_Traffic_Channel_MAC_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}
		int valueSize = 0;

		Destin->AttributeId = (ED_LONG)SHIFT_INT (8);
		switch (Destin->AttributeId) {
			case 0x00: {
				EDX_DECODE (HandoffDelays)
				break;
			}
			case 0x01: {
				EDX_DECODE (ATSupportedPacketFormats)
				break;
			}
			case 0x02: {
				EDX_DECODE (TentativeDRCtoTxDRCMap)
				break;
			}
			case 0x03: {
				EDX_DECODE (ExtendedSpans)
				break;
			}
			case 0xef: {
				valueSize = 8;
				break;
			}
			case 0xf0: {
				valueSize = 8;
				break;
			}
			case 0xf2: {
				valueSize = 8;
				break;
			}
			case 0xf3: {
				valueSize = 8;
				break;
			}
			case 0xf4: {
				valueSize = 8;
				break;
			}
			case 0xf5: {
				valueSize = 8;
				break;
			}
			case 0xf6: {
				valueSize = 8;
				break;
			}
			case 0xf7: {
				valueSize = 8;
				break;
			}
			case 0xf8: {
				valueSize = 8;
				break;
			}
			case 0xfb: {
				valueSize = 8;
				break;
			}
			case 0xfc: {
				valueSize = 8;
				break;
			}
			case 0xfe: {
				valueSize = 8;
				break;
			}
			case 0xff: {
				valueSize = 8;
				break;
			}
			default:;
		}
		if (valueSize > 0) {
			int noOfItems = (Length - 8) / valueSize;
			int i;
			SETITEMS_c_Air_Multicarrier_Forward_Traffic_Channel_MAC_Protocol_Attributes_Values (&Destin->Values, noOfItems);
			for (i=0; i<noOfItems; i++) {
				Destin->Values.data [i] = (ED_LONG)SHIFT_INT (valueSize);
			}
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Multicarrier_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Multicarrier_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0x00:
			case 0x01:
			case 0x02:
			case 0x03: PUSH_INT (Source->Value, 8); break;
			default: PUSH_INT (Source->Value, 8); break;
		}
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Multicarrier_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Multicarrier_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(8);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Reverse_Traffic_Channel_MAC_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Reverse_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int ret;
#ifndef ED_EXTRAPARAMS_CALL
#define ED_EXTRAPARAMS_CALL
#endif
#define EDX_ENCODE(TYPNAM) case U_c_Air_Default_Reverse_Traffic_Channel_MAC_Protocol_Attributes_complex_##TYPNAM: ret = ENCODE_c_Air_Default_Reverse_Traffic_Channel_MAC_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); if (ret < 0) return ret; CurrOfs+=ret; break;
		PUSH_INT (Source->AttributeId, 8);
		switch (GETPRESENT_c_Air_Default_Reverse_Traffic_Channel_MAC_Protocol_Attributes_complex (&Source->complex)) {
			EDX_ENCODE (PowerParameters)
			EDX_ENCODE (RateParameters)
			default:;
		}

		return CurrOfs - BitOffset;
#undef EDX_ENCODE

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Reverse_Traffic_Channel_MAC_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Reverse_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Default_Reverse_Traffic_Channel_MAC_Protocol_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Default_Reverse_Traffic_Channel_MAC_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}

		Destin->AttributeId = (ED_LONG)SHIFT_INT (8);
		switch (Destin->AttributeId) {
			case 0x00: {
				EDX_DECODE (PowerParameters)
				break;
			}
			case 0x01: {
				EDX_DECODE (RateParameters)
				break;
			}
			default:;
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0x00:
			case 0x01: PUSH_INT (Source->Value, 8); break;
			default:;
		}
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(8);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Subtype_1_Reverse_Traffic_Channel_MAC_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Subtype_1_Reverse_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int ret;
#ifndef ED_EXTRAPARAMS_CALL
#define ED_EXTRAPARAMS_CALL
#endif
#define EDX_ENCODE(TYPNAM) case U_c_Air_Subtype_1_Reverse_Traffic_Channel_MAC_Protocol_Attributes_complex_##TYPNAM: ret = ENCODE_c_Air_Subtype_1_Reverse_Traffic_Channel_MAC_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); if (ret < 0) return ret; CurrOfs+=ret; break;
		PUSH_INT (Source->AttributeId, 8);
		switch (GETPRESENT_c_Air_Subtype_1_Reverse_Traffic_Channel_MAC_Protocol_Attributes_complex (&Source->complex)) {
			EDX_ENCODE (PowerParameters)
			EDX_ENCODE (RateParameters)
			default:;
		}

		return CurrOfs - BitOffset;
#undef EDX_ENCODE

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Subtype_1_Reverse_Traffic_Channel_MAC_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Subtype_1_Reverse_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Subtype_1_Reverse_Traffic_Channel_MAC_Protocol_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Subtype_1_Reverse_Traffic_Channel_MAC_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}

		Destin->AttributeId = (ED_LONG)SHIFT_INT (8);
		switch (Destin->AttributeId) {
			case 0x00: {
				EDX_DECODE (PowerParameters)
				break;
			}
			case 0x01: {
				EDX_DECODE (RateParameters)
				break;
			}
			default:;
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Subtype_1_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Subtype_1_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0x00:
			case 0x01: PUSH_INT (Source->Value, 8); break;
			default:;
		}
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Subtype_1_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Subtype_1_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(8);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Subtype_3_Reverse_Traffic_Channel_MAC_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Subtype_3_Reverse_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int valueSize = 0;
		int i;

		int ret;
#ifndef ED_EXTRAPARAMS_CALL
#define ED_EXTRAPARAMS_CALL
#endif
#define EDX_ENCODE(TYPNAM) case U_c_Air_Subtype_3_Reverse_Traffic_Channel_MAC_Protocol_Attributes_complex_##TYPNAM: ret = ENCODE_c_Air_Subtype_3_Reverse_Traffic_Channel_MAC_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); if (ret < 0) return ret; CurrOfs+=ret; break;
		PUSH_INT (Source->AttributeId, 16);
		switch (GETPRESENT_c_Air_Subtype_3_Reverse_Traffic_Channel_MAC_Protocol_Attributes_complex (&Source->complex)) {
			EDX_ENCODE (AuxiliaryPilotChannelParameters)
			EDX_ENCODE (CommonPowerParameters)
			EDX_ENCODE (MaxNumSubPackets)
			EDX_ENCODE (PermittedPayload)
			EDX_ENCODE (PilotStrength)
			EDX_ENCODE (PowerParameters128)
			EDX_ENCODE (PowerParameters256)
			EDX_ENCODE (PowerParameters512)
			EDX_ENCODE (PowerParameters768)
			EDX_ENCODE (PowerParameters1024)
			EDX_ENCODE (PowerParameters1536)
			EDX_ENCODE (PowerParameters2048)
			EDX_ENCODE (PowerParameters3072)
			EDX_ENCODE (PowerParameters4096)
			EDX_ENCODE (PowerParameters6144)
			EDX_ENCODE (PowerParameters8192)
			EDX_ENCODE (PowerParameters12288)
			EDX_ENCODE (RequestParameters)
			EDX_ENCODE (RRIChannelPowerParameters)
			EDX_ENCODE (TxT2Pmax)
			EDX_ENCODE (MaxMACFlows)
			EDX_ENCODE (AssociatedFlowsNN)
			EDX_ENCODE (BucketFactorNN)
			EDX_ENCODE (T2PInflowRangeNN)
			EDX_ENCODE (T2PTransitionFunctionNN)
			default:;
		}
		switch (Source->AttributeId) {
			case 0xfd00: valueSize = 8; break;
			case 0xfe00: valueSize = 8; break;
			case 0xfe01: valueSize = 8; break;
			case 0xfff2: valueSize = 8; break;
			case 0xfff3: valueSize = 8; break;
			case 0xfff4: valueSize = 8; break;
			case 0xfff5: valueSize = 8; break;
			case 0xfff6: valueSize = 8; break;
			case 0xfff7: valueSize = 8; break;
			case 0xfff8: valueSize = 8; break;
			case 0xfff9: valueSize = 8; break;
			case 0xfffa: valueSize = 8; break;
			case 0xfffb: valueSize = 8; break;
			case 0xfffc: valueSize = 8; break;
			case 0xfffd: valueSize = 8; break;
			case 0xfffe: valueSize = 8; break;
			case 0xffff: valueSize = 8; break;
			default:;
		}
		if ((Source->AttributeId & 0xff00) == 0xf900) {
			valueSize = 8;
		}
		else if ((Source->AttributeId & 0xff00) == 0xfa00) {
			valueSize = 8;
		}
		else if ((Source->AttributeId & 0xff00) == 0xfb00) {
			valueSize = 8;
		}
		else if ((Source->AttributeId & 0xff00) == 0xfc00) {
			valueSize = 8;
		}
		else if ((Source->AttributeId & 0xff00) == 0xfd00) {
			valueSize = 8;
		}
		else if ((Source->AttributeId & 0xff00) == 0xfe00) {
			valueSize = 8;
		}

		if (valueSize > 0) {
			for (i=0; i<Source->Values.items; i++) {
				PUSH_INT (Source->Values.data [i], valueSize);
			}
		}

		return CurrOfs - BitOffset;
#undef EDX_ENCODE

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Subtype_3_Reverse_Traffic_Channel_MAC_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Subtype_3_Reverse_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Subtype_3_Reverse_Traffic_Channel_MAC_Protocol_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Subtype_3_Reverse_Traffic_Channel_MAC_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}
		int valueSize = 0;

		Destin->AttributeId = (ED_LONG)SHIFT_INT (16);
		switch (Destin->AttributeId) {
			case 0x0000: {
				EDX_DECODE (AuxiliaryPilotChannelParameters)
				break;
			}
			case 0x0001: {
				EDX_DECODE (CommonPowerParameters)
				break;
			}
			case 0x0002: {
				EDX_DECODE (MaxNumSubPackets)
				break;
			}
			case 0x0003: {
				EDX_DECODE (PermittedPayload)
				break;
			}
			case 0x0004: {
				EDX_DECODE (PilotStrength)
				break;
			}
			case 0x0005: {
				EDX_DECODE (PowerParameters128)
				break;
			}
			case 0x0006: {
				EDX_DECODE (PowerParameters256)
				break;
			}
			case 0x0007: {
				EDX_DECODE (PowerParameters512)
				break;
			}
			case 0x0008: {
				EDX_DECODE (PowerParameters768)
				break;
			}
			case 0x0009: {
				EDX_DECODE (PowerParameters1024)
				break;
			}
			case 0x000a: {
				EDX_DECODE (PowerParameters1536)
				break;
			}
			case 0x000b: {
				EDX_DECODE (PowerParameters2048)
				break;
			}
			case 0x000c: {
				EDX_DECODE (PowerParameters3072)
				break;
			}
			case 0x000d: {
				EDX_DECODE (PowerParameters4096)
				break;
			}
			case 0x000e: {
				EDX_DECODE (PowerParameters6144)
				break;
			}
			case 0x000f: {
				EDX_DECODE (PowerParameters8192)
				break;
			}
			case 0x0010: {
				EDX_DECODE (PowerParameters12288)
				break;
			}
			case 0x0011: {
				EDX_DECODE (RequestParameters)
				break;
			}
			case 0x0012: {
				EDX_DECODE (RRIChannelPowerParameters)
				break;
			}
			case 0x0013: {
				EDX_DECODE (TxT2Pmax)
				break;
			}
			case 0x0014: {
				EDX_DECODE (MaxMACFlows)
				break;
			}
			case 0xfd00: {
				valueSize = 8;
				break;
			}
			case 0xfe00: {
				valueSize = 8;
				break;
			}
			case 0xfe01: {
				valueSize = 8;
				break;
			}
			case 0xfff2: {
				valueSize = 8;
				break;
			}
			case 0xfff3: {
				valueSize = 8;
				break;
			}
			case 0xfff4: {
				valueSize = 8;
				break;
			}
			case 0xfff5: {
				valueSize = 8;
				break;
			}
			case 0xfff6: {
				valueSize = 8;
				break;
			}
			case 0xfff7: {
				valueSize = 8;
				break;
			}
			case 0xfff8: {
				valueSize = 8;
				break;
			}
			case 0xfff9: {
				valueSize = 8;
				break;
			}
			case 0xfffa: {
				valueSize = 8;
				break;
			}
			case 0xfffb: {
				valueSize = 8;
				break;
			}
			case 0xfffc: {
				valueSize = 8;
				break;
			}
			case 0xfffd: {
				valueSize = 8;
				break;
			}
			case 0xfffe: {
				valueSize = 8;
				break;
			}
			case 0xffff: {
				valueSize = 8;
				break;
			}
			default:;
		}
		if ((Destin->AttributeId & 0xff00) == 0x0100) {
			EDX_DECODE (AssociatedFlowsNN)
		}
		else if ((Destin->AttributeId & 0xff00) == 0x0300) {
			EDX_DECODE (BucketFactorNN)
		}
		else if ((Destin->AttributeId & 0xff00) == 0x1500) {
			EDX_DECODE (T2PInflowRangeNN)
		}
		else if ((Destin->AttributeId & 0xff00) == 0x1600) {
			EDX_DECODE (T2PTransitionFunctionNN)
		}
		else if ((Destin->AttributeId & 0xff00) == 0xf900) {
			valueSize = 8;
		}
		else if ((Destin->AttributeId & 0xff00) == 0xfa00) {
			valueSize = 8;
		}
		else if ((Destin->AttributeId & 0xff00) == 0xfb00) {
			valueSize = 8;
		}
		else if ((Destin->AttributeId & 0xff00) == 0xfc00) {
			valueSize = 8;
		}
		else if ((Destin->AttributeId & 0xff00) == 0xfd00) {
			valueSize = 8;
		}
		else if ((Destin->AttributeId & 0xff00) == 0xfe00) {
			valueSize = 8;
		}
		if (valueSize > 0) {
			int noOfItems = (Length - 16) / valueSize;
			int i;
			SETITEMS_c_Air_Subtype_3_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Values (&Destin->Values, noOfItems);
			for (i=0; i<noOfItems; i++) {
				Destin->Values.data [i] = (ED_LONG)SHIFT_INT (valueSize);
			}
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Subtype_3_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Subtype_3_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 16);
		switch (Source->AttributeId) {
			case 0x0000:
			case 0x0001:
			case 0x0002:
			case 0x0003:
			case 0x0004:
			case 0x0005:
			case 0x0006:
			case 0x0007:
			case 0x0008:
			case 0x0009:
			case 0x000a:
			case 0x000b:
			case 0x000c:
			case 0x000d:
			case 0x000e:
			case 0x000f:
			case 0x0010:
			case 0x0011:
			case 0x0012:
			case 0x0013:
			case 0x0014:
			case 0x0100:
			case 0x0300:
			case 0x1500:
			case 0x1600: PUSH_INT (Source->Value, 8); break;
			default: PUSH_INT (Source->Value, 8); break;
		}
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Subtype_3_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Subtype_3_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(16);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Multicarrier_Reverse_Traffic_Channel_MAC_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Multicarrier_Reverse_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int valueSize = 0;
		int i;

		int ret;
#ifndef ED_EXTRAPARAMS_CALL
#define ED_EXTRAPARAMS_CALL
#endif
#define EDX_ENCODE(TYPNAM) case U_c_Air_Multicarrier_Reverse_Traffic_Channel_MAC_Protocol_Attributes_complex_##TYPNAM: ret = ENCODE_c_Air_Multicarrier_Reverse_Traffic_Channel_MAC_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); if (ret < 0) return ret; CurrOfs+=ret; break;
		PUSH_INT (Source->AttributeId, 16);
		switch (GETPRESENT_c_Air_Multicarrier_Reverse_Traffic_Channel_MAC_Protocol_Attributes_complex (&Source->complex)) {
			EDX_ENCODE (AuxiliaryPilotChannelParameters)
			EDX_ENCODE (CommonPowerParameters)
			EDX_ENCODE (PermittedPayload)
			EDX_ENCODE (PowerParameters128)
			EDX_ENCODE (PowerParameters256)
			EDX_ENCODE (PowerParameters512)
			EDX_ENCODE (PowerParameters768)
			EDX_ENCODE (PowerParameters1024)
			EDX_ENCODE (PowerParameters1536)
			EDX_ENCODE (PowerParameters2048)
			EDX_ENCODE (PowerParameters3072)
			EDX_ENCODE (PowerParameters4096)
			EDX_ENCODE (PowerParameters6144)
			EDX_ENCODE (PowerParameters8192)
			EDX_ENCODE (PowerParameters12288)
			EDX_ENCODE (RequestParameters)
			EDX_ENCODE (RRIChannelPowerParameters)
			EDX_ENCODE (MaxMACFlows)
			EDX_ENCODE (AssociatedFlowsNN)
			EDX_ENCODE (BucketFactorNN)
			EDX_ENCODE (T2PInflowRangeConfigXX)
			EDX_ENCODE (T2PTransitionFunctionConfigXX)
			EDX_ENCODE (AssociatedFlowConfigurationsNC)
			EDX_ENCODE (AssociatedATConfigurationsCC)
			EDX_ENCODE (DataTokenBucketNN)
			EDX_ENCODE (MaxNumSubPacketsCC)
			EDX_ENCODE (PilotStrengthConfigXX)
			EDX_ENCODE (TxT2PmaxConfigXX)
			default:;
		}
		switch (Source->AttributeId) {
			case 0xfd00: valueSize = 8; break;
			case 0xfe00: valueSize = 8; break;
			case 0xfe01: valueSize = 8; break;
			case 0xfff1: valueSize = 8; break;
			case 0xfff2: valueSize = 8; break;
			case 0xfff7: valueSize = 8; break;
			case 0xfff9: valueSize = 8; break;
			case 0xfffa: valueSize = 8; break;
			case 0xfffb: valueSize = 8; break;
			case 0xfffc: valueSize = 8; break;
			case 0xfffd: valueSize = 8; break;
			case 0xfffe: valueSize = 8; break;
			default:;
		}
		if ((Source->AttributeId & 0xff00) == 0xf600) {
			valueSize = 8;
		}
		else if ((Source->AttributeId & 0xff00) == 0xf700) {
			valueSize = 8;
		}
		else if ((Source->AttributeId & 0xff00) == 0xf800) {
			valueSize = 8;
		}
		else if ((Source->AttributeId & 0xff00) == 0xf900) {
			valueSize = 8;
		}
		else if ((Source->AttributeId & 0xff00) == 0xfa00) {
			valueSize = 8;
		}
		else if ((Source->AttributeId & 0xff00) == 0xfc00) {
			valueSize = 8;
		}
		else if ((Source->AttributeId & 0xff00) == 0xfd00) {
			valueSize = 8;
		}
		else if ((Source->AttributeId & 0xff00) == 0xfe00) {
			valueSize = 8;
		}

		if (valueSize > 0) {
			for (i=0; i<Source->Values.items; i++) {
				PUSH_INT (Source->Values.data [i], valueSize);
			}
		}

		return CurrOfs - BitOffset;
#undef EDX_ENCODE

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Multicarrier_Reverse_Traffic_Channel_MAC_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Multicarrier_Reverse_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Multicarrier_Reverse_Traffic_Channel_MAC_Protocol_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Multicarrier_Reverse_Traffic_Channel_MAC_Protocol_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}
		int valueSize = 0;

		Destin->AttributeId = (ED_LONG)SHIFT_INT (16);
		switch (Destin->AttributeId) {
			case 0x0000: {
				EDX_DECODE (AuxiliaryPilotChannelParameters)
				break;
			}
			case 0x0001: {
				EDX_DECODE (CommonPowerParameters)
				break;
			}
			case 0x0003: {
				EDX_DECODE (PermittedPayload)
				break;
			}
			case 0x0005: {
				EDX_DECODE (PowerParameters128)
				break;
			}
			case 0x0006: {
				EDX_DECODE (PowerParameters256)
				break;
			}
			case 0x0007: {
				EDX_DECODE (PowerParameters512)
				break;
			}
			case 0x0008: {
				EDX_DECODE (PowerParameters768)
				break;
			}
			case 0x0009: {
				EDX_DECODE (PowerParameters1024)
				break;
			}
			case 0x000a: {
				EDX_DECODE (PowerParameters1536)
				break;
			}
			case 0x000b: {
				EDX_DECODE (PowerParameters2048)
				break;
			}
			case 0x000c: {
				EDX_DECODE (PowerParameters3072)
				break;
			}
			case 0x000d: {
				EDX_DECODE (PowerParameters4096)
				break;
			}
			case 0x000e: {
				EDX_DECODE (PowerParameters6144)
				break;
			}
			case 0x000f: {
				EDX_DECODE (PowerParameters8192)
				break;
			}
			case 0x0010: {
				EDX_DECODE (PowerParameters12288)
				break;
			}
			case 0x0011: {
				EDX_DECODE (RequestParameters)
				break;
			}
			case 0x0012: {
				EDX_DECODE (RRIChannelPowerParameters)
				break;
			}
			case 0x0014: {
				EDX_DECODE (MaxMACFlows)
				break;
			}
			case 0xfd00: {
				valueSize = 8;
				break;
			}
			case 0xfe00: {
				valueSize = 8;
				break;
			}
			case 0xfe01: {
				valueSize = 8;
				break;
			}
			case 0xfff1: {
				valueSize = 8;
				break;
			}
			case 0xfff2: {
				valueSize = 8;
				break;
			}
			case 0xfff7: {
				valueSize = 8;
				break;
			}
			case 0xfff9: {
				valueSize = 8;
				break;
			}
			case 0xfffa: {
				valueSize = 8;
				break;
			}
			case 0xfffb: {
				valueSize = 8;
				break;
			}
			case 0xfffc: {
				valueSize = 8;
				break;
			}
			case 0xfffd: {
				valueSize = 8;
				break;
			}
			case 0xfffe: {
				valueSize = 8;
				break;
			}
			default:;
		}
		if ((Destin->AttributeId & 0xff00) == 0x0100) {
			EDX_DECODE (AssociatedFlowsNN)
		}
		else if ((Destin->AttributeId & 0xff00) == 0x0300) {
			EDX_DECODE (BucketFactorNN)
		}
		else if ((Destin->AttributeId & 0xff00) == 0x1500) {
			EDX_DECODE (T2PInflowRangeConfigXX)
		}
		else if ((Destin->AttributeId & 0xff00) == 0x1600) {
			EDX_DECODE (T2PTransitionFunctionConfigXX)
		}
		else if ((Destin->AttributeId & 0xff00) == 0x1700) {
			EDX_DECODE (AssociatedFlowConfigurationsNC)
		}
		else if ((Destin->AttributeId & 0xff00) == 0x1800) {
			EDX_DECODE (AssociatedATConfigurationsCC)
		}
		else if ((Destin->AttributeId & 0xff00) == 0x1900) {
			EDX_DECODE (DataTokenBucketNN)
		}
		else if ((Destin->AttributeId & 0xff00) == 0x1a00) {
			EDX_DECODE (MaxNumSubPacketsCC)
		}
		else if ((Destin->AttributeId & 0xff00) == 0x1b00) {
			EDX_DECODE (PilotStrengthConfigXX)
		}
		else if ((Destin->AttributeId & 0xff00) == 0x1c00) {
			EDX_DECODE (TxT2PmaxConfigXX)
		}
		else if ((Destin->AttributeId & 0xff00) == 0xf600) {
			valueSize = 8;
		}
		else if ((Destin->AttributeId & 0xff00) == 0xf700) {
			valueSize = 8;
		}
		else if ((Destin->AttributeId & 0xff00) == 0xf800) {
			valueSize = 8;
		}
		else if ((Destin->AttributeId & 0xff00) == 0xf900) {
			valueSize = 8;
		}
		else if ((Destin->AttributeId & 0xff00) == 0xfa00) {
			valueSize = 8;
		}
		else if ((Destin->AttributeId & 0xff00) == 0xfc00) {
			valueSize = 8;
		}
		else if ((Destin->AttributeId & 0xff00) == 0xfd00) {
			valueSize = 8;
		}
		else if ((Destin->AttributeId & 0xff00) == 0xfe00) {
			valueSize = 8;
		}
		if (valueSize > 0) {
			int noOfItems = (Length - 16) / valueSize;
			int i;
			SETITEMS_c_Air_Multicarrier_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Values (&Destin->Values, noOfItems);
			for (i=0; i<noOfItems; i++) {
				Destin->Values.data [i] = (ED_LONG)SHIFT_INT (valueSize);
			}
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Multicarrier_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Multicarrier_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 16);
		switch (Source->AttributeId) {
			case 0x0000:
			case 0x0001:
			case 0x0003:
			case 0x0005:
			case 0x0006:
			case 0x0007:
			case 0x0008:
			case 0x0009:
			case 0x000a:
			case 0x000b:
			case 0x000c:
			case 0x000d:
			case 0x000e:
			case 0x000f:
			case 0x0010:
			case 0x0011:
			case 0x0012:
			case 0x0014:
			case 0x0100:
			case 0x0300:
			case 0x1500:
			case 0x1600:
			case 0x1700:
			case 0x1800:
			case 0x1900:
			case 0x1a00:
			case 0x1b00:
			case 0x1c00: PUSH_INT (Source->Value, 8); break;
			default: PUSH_INT (Source->Value, 8); break;
		}
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Multicarrier_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Multicarrier_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(16);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Subtype_3_Physical_Layer_Protocol_Instance_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Subtype_3_Physical_Layer_Protocol_Instance_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


		int valueSize = 0;
		int i;

		int ret;
#ifndef ED_EXTRAPARAMS_CALL
#define ED_EXTRAPARAMS_CALL
#endif
#define EDX_ENCODE(TYPNAM) case U_c_Air_Subtype_3_Physical_Layer_Protocol_Instance_Attributes_complex_##TYPNAM: ret = ENCODE_c_Air_Subtype_3_Physical_Layer_Protocol_Instance_Attributes_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); if (ret < 0) return ret; CurrOfs+=ret; break;
		PUSH_INT (Source->AttributeId, 8);
		switch (GETPRESENT_c_Air_Subtype_3_Physical_Layer_Protocol_Instance_Attributes_complex (&Source->complex)) {
			EDX_ENCODE (AdditionalCarriersInitTxPower)
			EDX_ENCODE (ReversePilotTransmitSlots)
			default:;
		}
		switch (Source->AttributeId) {
			case 0xfa: valueSize = 8; break;
			case 0xfb: valueSize = 8; break;
			case 0xfc: valueSize = 8; break;
			case 0xfd: valueSize = 8; break;
			case 0xfe: valueSize = 8; break;
			case 0xff: valueSize = 8; break;
			default:;
		}

		if (valueSize > 0) {
			for (i=0; i<Source->Values.items; i++) {
				PUSH_INT (Source->Values.data [i], valueSize);
			}
		}

		return CurrOfs - BitOffset;
#undef EDX_ENCODE

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Subtype_3_Physical_Layer_Protocol_Instance_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Subtype_3_Physical_Layer_Protocol_Instance_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define EDX_DECODE(TYPNAM) {SETPRESENT_c_Air_Subtype_3_Physical_Layer_Protocol_Instance_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_Air_Subtype_3_Physical_Layer_Protocol_Instance_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}
		int valueSize = 0;

		Destin->AttributeId = (ED_LONG)SHIFT_INT (8);
		switch (Destin->AttributeId) {
			case 0x01: {
				EDX_DECODE (AdditionalCarriersInitTxPower)
				break;
			}
			case 0x02: {
				EDX_DECODE (ReversePilotTransmitSlots)
				break;
			}
			case 0xfa: {
				valueSize = 8;
				break;
			}
			case 0xfb: {
				valueSize = 8;
				break;
			}
			case 0xfc: {
				valueSize = 8;
				break;
			}
			case 0xfd: {
				valueSize = 8;
				break;
			}
			case 0xfe: {
				valueSize = 8;
				break;
			}
			case 0xff: {
				valueSize = 8;
				break;
			}
			default:;
		}
		if (valueSize > 0) {
			int noOfItems = (Length - 8) / valueSize;
			int i;
			SETITEMS_c_Air_Subtype_3_Physical_Layer_Protocol_Instance_Attributes_Values (&Destin->Values, noOfItems);
			for (i=0; i<noOfItems; i++) {
				Destin->Values.data [i] = (ED_LONG)SHIFT_INT (valueSize);
			}
		}

		return Length;

#undef EDX_DECODE
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Subtype_3_Physical_Layer_Protocol_Instance_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Subtype_3_Physical_Layer_Protocol_Instance_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		PUSH_INT (Source->AttributeId, 8);
		switch (Source->AttributeId) {
			case 0x01:
			case 0x02: PUSH_INT (Source->Value, 8); break;
			default: PUSH_INT (Source->Value, 8); break;
		}
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Subtype_3_Physical_Layer_Protocol_Instance_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Subtype_3_Physical_Layer_Protocol_Instance_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int len;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(8);
		len = Length - (CurrOfs-BitOffset);
		Destin->Value = (ED_LONG)SHIFT_INT(len);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Attribute_Response_16 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Attribute_Response_16* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int i;
		
#define ATTRIDLEN 16
		
		PUSH_INT (Source->AttributeId, ATTRIDLEN);
		for (i=0; i<Source->ValueIDs.items; i++) {
			PUSH_INT (Source->ValueIDs.data[i], 8);
		}
		return CurrOfs-BitOffset;
#undef ATTRIDLEN

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Attribute_Response_16 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Attribute_Response_16* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define ATTRIDLEN 16
		int i;
		int items;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(ATTRIDLEN);

		items=(Length - (CurrOfs-BitOffset))/8;
		if (items > 0) {
			SETITEMS_c_Air_Attribute_Response_16_ValueIDs (&Destin->ValueIDs, items);
			for (i=0; i<items; i++) {
				Destin->ValueIDs.data[i] = (ED_LONG)SHIFT_INT(8);
			}
		}
		return CurrOfs-BitOffset;
#undef ATTRIDLEN
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Attribute_Response_8 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Attribute_Response_8* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int i;
		
#define ATTRIDLEN 8
		
		PUSH_INT (Source->AttributeId, ATTRIDLEN);
		for (i=0; i<Source->ValueIDs.items; i++) {
			PUSH_INT (Source->ValueIDs.data[i], 8);
		}
		return CurrOfs-BitOffset;
#undef ATTRIDLEN

	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Attribute_Response_8 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Attribute_Response_8* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

#define ATTRIDLEN 8
		int i;
		int items;
		Destin->AttributeId = (ED_LONG)SHIFT_INT(ATTRIDLEN);

		items=(Length - (CurrOfs-BitOffset))/8;
		if (items > 0) {
			SETITEMS_c_Air_Attribute_Response_8_ValueIDs (&Destin->ValueIDs, items);
			for (i=0; i<items; i++) {
				Destin->ValueIDs.data[i] = (ED_LONG)SHIFT_INT(8);
			}
		}
		return CurrOfs-BitOffset;
#undef ATTRIDLEN
	
	}
}
#undef THIS
#define THIS Source
/* IEEE 802.16 GENERIC TLV ENCODER */
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_GenericTLV_cs0024 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GenericTLV_cs0024* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_EXLONG BinaryDataLength;
	

	
	ED_EXTRAPARAMS_CODE
						
	/* Encode the tag */
	EDIntToBits (Buffer, CurrOfs, Source->TLV_Tag, 8);
	CurrOfs += 8;
	
	/* Calculate the binary length */
	BinaryDataLength = Source->TLV_Data.usedBits;
	
	/* Encode the length rounded up to the nearest octet */
	CurrOfs += EDEncodeDefiniteFormLength (Buffer, CurrOfs, (((unsigned ED_EXLONG)BinaryDataLength)+7)>>3);
	
	/* Encode the bits of the binary data */
	EDCopyBits (Buffer, CurrOfs, Source->TLV_Data.value, 0, BinaryDataLength);
	CurrOfs += BinaryDataLength;
	
	/* Pad the remaining part */
	EDIntToBits (Buffer, CurrOfs, 0, BITS_TO_OCTET_PAD (CurrOfs));
	CurrOfs += BITS_TO_OCTET_PAD (CurrOfs);
	
	return (CurrOfs - BitOffset);
}

#undef THIS
#define THIS Destin
/* IEEE 802.16 GENERIC TLV DECODER */
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_GenericTLV_cs0024 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GenericTLV_cs0024* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	unsigned ED_EXLONG DataLength;
	unsigned ED_EXLONG EffectiveDataLength;
	ED_EXLONG RetLen;

	ED_EXTRAPARAMS_CODE
	
	/* Is there room for tag and length? */
	if (Length < 16) return ED_MESSAGE_TOO_SHORT;

	/* Decode the tag */
	Destin->TLV_Tag = (ED_LONG)EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	
	/* Decode the length */
	RetLen = EDDecodeDefiniteFormLength (Buffer, CurrOfs, &DataLength);
	if (RetLen < 0) return RetLen;
	DataLength = DataLength * 8;
	EffectiveDataLength = DataLength;
	CurrOfs += RetLen;
	if ((BitOffset-CurrOfs) > Length) return ED_MESSAGE_TOO_SHORT;
	if (BitOffset - (CurrOfs + (ED_EXLONG)DataLength) > Length) return ED_MESSAGE_TOO_SHORT;
	
	/* If the expected length is too much for our binary buffer, decode
		 what we can and discard the rest */
	if (DataLength > 64) {
		DataLength = 64;
	}
	
	/* Allocate 'DataLength' bits */
	ALLOC_c_GenericTLV_cs0024_TLV_Data (&(Destin->TLV_Data), DataLength);

	
	/* Save the bits in the binary data */
	EDCopyBits (Destin->TLV_Data.value, 0, Buffer, CurrOfs, DataLength);
	CurrOfs += (ED_EXLONG)EffectiveDataLength;

	return (CurrOfs-BitOffset);
}

#undef THIS
