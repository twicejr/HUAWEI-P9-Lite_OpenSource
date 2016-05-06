/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/
/*lint -e959 -e530 -e774 -e572 -e778 -e525 -e539 -e701 -e123 -e438 -e119 -e506 -e529 -e550 -e666 -e713 -e719 -e730 -e734 -e744 -e801 -e801 -e813 -e830 -e40 -e10 -e52 -e63 -e115 -e409 -e118 -e49 -e718 -e746 -e737 -e760 -e830 */
#define ENCODIX_CS0063

#include "UserDefinedDataTypes_cs0063.h"
#include "ed_c_known_ie_cs0063.h"
#include "ed_tlv.h"
#include "CSN1DataTypes_cs0063.h"
#if ED_COMMON_CRC != 0x328E3625 && ED_VERSION != 10152 && ED_VERSION != 10153
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.154
#endif


#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
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
		int normalizedAttributeId;

		int ret;
#ifndef ED_EXTRAPARAMS_CALL
#define ED_EXTRAPARAMS_CALL
#endif
#define EDX_ENCODE(TYPNAM) case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_##TYPNAM: ret = ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); if (ret < 0) return ret; CurrOfs+=ret; break;
		normalizedAttributeId = (Source->AttributeId) & 0xFF00;
		switch (normalizedAttributeId) {
			case 0x0000:
			case 0xea00:
			case 0xeb00:
			case 0xee00:
			case 0xef00:
			case 0xf300:
			case 0xff00: normalizedAttributeId = (int)Source->AttributeId; break;
			default:;
		};

		PUSH_INT (Source->AttributeId, 16);
		switch (GETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex (&Source->complex)) {
			EDX_ENCODE (ANSupportedQoSProfiles)
			EDX_ENCODE (ATSupportedFlowProtocolParametersPP)
			EDX_ENCODE (ATSupportedQoSProfiles)
			EDX_ENCODE (ATSupportedRouteProtocolParametersPP)
			EDX_ENCODE (FlowNNFlowProtocolParametersFwd)
			EDX_ENCODE (FlowNNFlowProtocolParametersRev)
			EDX_ENCODE (FlowNNReservationFwd)
			EDX_ENCODE (FlowNNReservationRev)
			EDX_ENCODE (FlowNNRouteProtocolParametersFwd)
			EDX_ENCODE (FlowNNRouteProtocolParametersRev)
			EDX_ENCODE (FlowNNTimersFwd)
			EDX_ENCODE (FlowNNTimersRev)
			EDX_ENCODE (MaxLinkFlows)
			EDX_ENCODE (MaxReservations)
			EDX_ENCODE (ReservationKKBCMCSFlowIDAssociation)
			EDX_ENCODE (ReservationKKBCMCSProgramIDAssociation)
			EDX_ENCODE (ReservationKKQoSRequestFwd)
			EDX_ENCODE (ReservationKKQoSRequestRev)
			EDX_ENCODE (ReservationKKQoSResponseFwd)
			EDX_ENCODE (ReservationKKQoSResponseRev)
			default: {
				switch (normalizedAttributeId) {
					case 0xf200: valueSize = (Source->AttributeId == 0xf200 || Source->AttributeId == 0xf201 ? 8 : 16); break;
					case 0xf700: valueSize = 16; break;
					default: valueSize = 8;
				}
			}
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

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


#define EDX_DECODE(TYPNAM) {SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}
		int valueSize = 0;
		int normalizedAttributeId;

		Destin->AttributeId = (ED_LONG)SHIFT_INT (16);
		normalizedAttributeId = (Destin->AttributeId) & 0xFF00;
		switch (normalizedAttributeId) {
			case 0x0000:
			case 0xea00:
			case 0xeb00:
			case 0xee00:
			case 0xef00:
			case 0xf300:
			case 0xff00: normalizedAttributeId = (int)Destin->AttributeId; break;
			default:;
		};

		switch (normalizedAttributeId) {
			case 0x0003: EDX_DECODE (ANSupportedQoSProfiles); break;
			case 0x0f00: EDX_DECODE (ATSupportedFlowProtocolParametersPP); break;
			case 0x0002: EDX_DECODE (ATSupportedQoSProfiles); break;
			case 0x1000: EDX_DECODE (ATSupportedRouteProtocolParametersPP); break;
			case 0x0b00: EDX_DECODE (FlowNNFlowProtocolParametersFwd); break;
			case 0x0c00: EDX_DECODE (FlowNNFlowProtocolParametersRev); break;
			case 0x0500: EDX_DECODE (FlowNNReservationFwd); break;
			case 0x0600: EDX_DECODE (FlowNNReservationRev); break;
			case 0x0d00: EDX_DECODE (FlowNNRouteProtocolParametersFwd); break;
			case 0x0e00: EDX_DECODE (FlowNNRouteProtocolParametersRev); break;
			case 0x0300: EDX_DECODE (FlowNNTimersFwd); break;
			case 0x0400: EDX_DECODE (FlowNNTimersRev); break;
			case 0x0004: EDX_DECODE (MaxLinkFlows); break;
			case 0x0005: EDX_DECODE (MaxReservations); break;
			case 0x1100: EDX_DECODE (ReservationKKBCMCSFlowIDAssociation); break;
			case 0x1200: EDX_DECODE (ReservationKKBCMCSProgramIDAssociation); break;
			case 0x0700: EDX_DECODE (ReservationKKQoSRequestFwd); break;
			case 0x0800: EDX_DECODE (ReservationKKQoSRequestRev); break;
			case 0x0900: EDX_DECODE (ReservationKKQoSResponseFwd); break;
			case 0x0a00: EDX_DECODE (ReservationKKQoSResponseRev); break;
			default: {
				switch (normalizedAttributeId) {
					case 0xf200: valueSize = (Destin->AttributeId == 0xf200 || Destin->AttributeId == 0xf201 ? 8 : 16); break;
					case 0xf700: valueSize = 16; break;
					default: valueSize = 8;
				}
			}
		}

		if (valueSize > 0) {
			int noOfItems = (Length - 16) / valueSize;
			int i;
			SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Values (&Destin->Values, noOfItems);
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

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int valueSize;
		PUSH_INT (Source->AttributeId, 16);
		switch (Source->AttributeId & 0xFF00) {
			case 0xf200: valueSize = (Source->AttributeId == 0xf200 || Source->AttributeId == 0xf201 ? 8 : 16); break;
			case 0xf700: valueSize = 16; break;
			default: valueSize = 8;
		}

		PUSH_INT (Source->Value, valueSize);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
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

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
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
		int normalizedAttributeId;

		int ret;
#ifndef ED_EXTRAPARAMS_CALL
#define ED_EXTRAPARAMS_CALL
#endif
#define EDX_ENCODE(TYPNAM) case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_##TYPNAM: ret = ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); if (ret < 0) return ret; CurrOfs+=ret; break;
		normalizedAttributeId = (Source->AttributeId) & 0xFF00;
		switch (normalizedAttributeId) {
			case 0x0000:
			case 0xea00:
			case 0xeb00:
			case 0xee00:
			case 0xef00:
			case 0xf200:
			case 0xf300:
			case 0xff00: normalizedAttributeId = (int)Source->AttributeId; break;
			default:;
		};

		PUSH_INT (Source->AttributeId, 16);
		switch (GETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex (&Source->complex)) {
			EDX_ENCODE (ANSupportedQoSProfiles)
			EDX_ENCODE (ATSupportedFlowProtocolParametersPP)
			EDX_ENCODE (ATSupportedQoSProfiles)
			EDX_ENCODE (ATSupportedRouteProtocolParametersPP)
			EDX_ENCODE (FlowNNFlowProtocolParametersFwd)
			EDX_ENCODE (FlowNNFlowProtocolParametersRev)
			EDX_ENCODE (FlowNNReservationFwd)
			EDX_ENCODE (FlowNNReservationRev)
			EDX_ENCODE (FlowNNRouteProtocolParametersFwd)
			EDX_ENCODE (FlowNNRouteProtocolParametersRev)
			EDX_ENCODE (FlowNNTimersFwd)
			EDX_ENCODE (FlowNNTimersRev)
			EDX_ENCODE (MaxLinkFlows)
			EDX_ENCODE (MaxReservations)
			EDX_ENCODE (ReservationKKBCMCSFlowIDAssociation)
			EDX_ENCODE (ReservationKKBCMCSProgramIDAssociation)
			EDX_ENCODE (ReservationKKQoSRequestFwd)
			EDX_ENCODE (ReservationKKQoSRequestRev)
			EDX_ENCODE (ReservationKKQoSResponseFwd)
			EDX_ENCODE (ReservationKKQoSResponseRev)
			default: {
				switch (normalizedAttributeId) {
					case 0xf700: valueSize = 16; break;
					default: valueSize = 8;
				}
			}
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

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{


#define EDX_DECODE(TYPNAM) {SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}
		int valueSize = 0;
		int normalizedAttributeId;

		Destin->AttributeId = (ED_LONG)SHIFT_INT (16);
		normalizedAttributeId = (Destin->AttributeId) & 0xFF00;
		switch (normalizedAttributeId) {
			case 0x0000:
			case 0xea00:
			case 0xeb00:
			case 0xee00:
			case 0xef00:
			case 0xf200:
			case 0xf300:
			case 0xff00: normalizedAttributeId = (int)Destin->AttributeId; break;
			default:;
		};

		switch (normalizedAttributeId) {
			case 0x0003: EDX_DECODE (ANSupportedQoSProfiles); break;
			case 0x0f00: EDX_DECODE (ATSupportedFlowProtocolParametersPP); break;
			case 0x0002: EDX_DECODE (ATSupportedQoSProfiles); break;
			case 0x1000: EDX_DECODE (ATSupportedRouteProtocolParametersPP); break;
			case 0x0b00: EDX_DECODE (FlowNNFlowProtocolParametersFwd); break;
			case 0x0c00: EDX_DECODE (FlowNNFlowProtocolParametersRev); break;
			case 0x0500: EDX_DECODE (FlowNNReservationFwd); break;
			case 0x0600: EDX_DECODE (FlowNNReservationRev); break;
			case 0x0d00: EDX_DECODE (FlowNNRouteProtocolParametersFwd); break;
			case 0x0e00: EDX_DECODE (FlowNNRouteProtocolParametersRev); break;
			case 0x0300: EDX_DECODE (FlowNNTimersFwd); break;
			case 0x0400: EDX_DECODE (FlowNNTimersRev); break;
			case 0x0004: EDX_DECODE (MaxLinkFlows); break;
			case 0x0005: EDX_DECODE (MaxReservations); break;
			case 0x1100: EDX_DECODE (ReservationKKBCMCSFlowIDAssociation); break;
			case 0x1200: EDX_DECODE (ReservationKKBCMCSProgramIDAssociation); break;
			case 0x0700: EDX_DECODE (ReservationKKQoSRequestFwd); break;
			case 0x0800: EDX_DECODE (ReservationKKQoSRequestRev); break;
			case 0x0900: EDX_DECODE (ReservationKKQoSResponseFwd); break;
			case 0x0a00: EDX_DECODE (ReservationKKQoSResponseRev); break;
			default: {
				switch (normalizedAttributeId) {
					case 0xf700: valueSize = 16; break;
					default: valueSize = 8;
				}
			}
		}

		if (valueSize > 0) {
			int noOfItems = (Length - 16) / valueSize;
			int i;
			SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Values (&Destin->Values, noOfItems);
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

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int valueSize;
		PUSH_INT (Source->AttributeId, 16);
		switch (Source->AttributeId & 0xFF00) {
			case 0xf700: valueSize = 16; break;
			default: valueSize = 8;
		}

		PUSH_INT (Source->Value, valueSize);
		return CurrOfs-BitOffset;
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
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
/* IEEE 802.16 GENERIC TLV ENCODER */
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_GenericTLV_cs0063 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GenericTLV_cs0063* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
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
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_GenericTLV_cs0063 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GenericTLV_cs0063* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
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
	ALLOC_c_GenericTLV_cs0063_TLV_Data (&(Destin->TLV_Data), DataLength);

	
	/* Save the bits in the binary data */
	EDCopyBits (Destin->TLV_Data.value, 0, Buffer, CurrOfs, DataLength);
	CurrOfs += (ED_EXLONG)EffectiveDataLength;

	return (CurrOfs-BitOffset);
}

#undef THIS
