/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/
/*lint -e959 -e530 -e774 -e572 -e778 -e525 -e539 -e701 -e123 -e438 -e119 -e506 -e529 -e550 -e666 -e713 -e719 -e730 -e734 -e744 -e801 -e801 -e813 -e830 -e40 */
#define ENCODIX_CS0087

#include "UserDefinedDataTypes_cs0087.h"
#include "ed_c_known_ie_cs0087.h"
#include "ed_tlv.h"
#include "CSN1DataTypes_cs0087.h"
#if ED_COMMON_CRC != 0x328E3625 && ED_VERSION != 10152 && ED_VERSION != 10153
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.154
#endif


#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Session_Layer_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Session_Layer_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int attrId = 0;
		int lenInBits = EDBitsToInt (Buffer, BitOffset-8, 8) * 8;
#define EDX_ENCODE(TYPNAM) case U_c_RPD_Session_Layer_Attributes_complex_##TYPNAM: ENCODE_c_RPD_Session_Layer_Attributes_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); break;


		attrId = (int)Source->AttributeId;
		if (GETPRESENT_c_RPD_Session_Layer_Attributes_NN (Source)) {
			attrId |= (int)Source->NN;
		}
		PUSH_INT (attrId, 8);
		if (GETPRESENT_c_RPD_Session_Layer_Attributes_Value (Source)) {
			PUSH_INT (Source->Value, 8);
		}
		return (ED_EXLONG)lenInBits;
#undef EDX_ENCODE
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Session_Layer_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Session_Layer_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int attrId;
#define EDX_DECODE(TYPNAM) {SETPRESENT_c_RPD_Session_Layer_Attributes_complex_##TYPNAM (&Destin->complex); DECODE_c_RPD_Session_Layer_Attributes_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}

		attrId = SHIFT_INT (8);
		switch (attrId) {
			case 0xfa: {
				Destin->AttributeId = 0xfa;
				SETPRESENT_c_RPD_Session_Layer_Attributes_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
				break;
			}
			case 0xfb: {
				Destin->AttributeId = 0xfb;
				SETPRESENT_c_RPD_Session_Layer_Attributes_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
				break;
			}
			case 0xfc: {
				Destin->AttributeId = 0xfc;
				SETPRESENT_c_RPD_Session_Layer_Attributes_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
				break;
			}
			case 0xfd: {
				Destin->AttributeId = 0xfd;
				SETPRESENT_c_RPD_Session_Layer_Attributes_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
				break;
			}
			case 0xfe: {
				Destin->AttributeId = 0xfe;
				SETPRESENT_c_RPD_Session_Layer_Attributes_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
				break;
			}
			case 0xff: {
				Destin->AttributeId = 0xff;
				SETPRESENT_c_RPD_Session_Layer_Attributes_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
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

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Inter_RAT_Idle_State (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Inter_RAT_Idle_State* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int attrId = 0;
		int lenInBits = EDBitsToInt (Buffer, BitOffset-8, 8) * 8;
#define EDX_ENCODE(TYPNAM) case U_c_RPD_Inter_RAT_Idle_State_complex_##TYPNAM: ENCODE_c_RPD_Inter_RAT_Idle_State_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); break;


		attrId = (int)Source->AttributeId;
		if (GETPRESENT_c_RPD_Inter_RAT_Idle_State_NN (Source)) {
			attrId |= (int)Source->NN;
		}
		PUSH_INT (attrId, 8);
		if (GETPRESENT_c_RPD_Inter_RAT_Idle_State_Value (Source)) {
			PUSH_INT (Source->Value, 8);
		}
		switch (GETPRESENT_c_RPD_Inter_RAT_Idle_State_complex (&Source->complex)) {
			EDX_ENCODE (PreferredControlChannelCycle)
			EDX_ENCODE (SlottedMode)
			EDX_ENCODE (PagingMask)
			default:;
		};
		return (ED_EXLONG)lenInBits;
#undef EDX_ENCODE
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Inter_RAT_Idle_State (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Inter_RAT_Idle_State* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int attrId;
#define EDX_DECODE(TYPNAM) {SETPRESENT_c_RPD_Inter_RAT_Idle_State_complex_##TYPNAM (&Destin->complex); DECODE_c_RPD_Inter_RAT_Idle_State_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}

		attrId = SHIFT_INT (8);
		switch (attrId) {
			case 0x00: {
				Destin->AttributeId = 0x00;
				EDX_DECODE (PreferredControlChannelCycle)
				break;
			}
			case 0x01: {
				Destin->AttributeId = 0x01;
				EDX_DECODE (SlottedMode)
				break;
			}
			case 0x02: {
				Destin->AttributeId = 0x02;
				EDX_DECODE (PagingMask)
				break;
			}
			case 0xfe: {
				Destin->AttributeId = 0xfe;
				SETPRESENT_c_RPD_Inter_RAT_Idle_State_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
				break;
			}
			case 0xff: {
				Destin->AttributeId = 0xff;
				SETPRESENT_c_RPD_Inter_RAT_Idle_State_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
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

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Inter_RAT_Route_Update (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Inter_RAT_Route_Update* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int attrId = 0;
		int lenInBits = EDBitsToInt (Buffer, BitOffset-8, 8) * 8;
#define EDX_ENCODE(TYPNAM) case U_c_RPD_Inter_RAT_Route_Update_complex_##TYPNAM: ENCODE_c_RPD_Inter_RAT_Route_Update_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); break;


		attrId = (int)Source->AttributeId;
		if (GETPRESENT_c_RPD_Inter_RAT_Route_Update_NN (Source)) {
			attrId |= (int)Source->NN;
		}
		PUSH_INT (attrId, 8);
		if (GETPRESENT_c_RPD_Inter_RAT_Route_Update_Value (Source)) {
			PUSH_INT (Source->Value, 8);
		}
		switch (GETPRESENT_c_RPD_Inter_RAT_Route_Update_complex (&Source->complex)) {
			EDX_ENCODE (SearchParameters)
			EDX_ENCODE (SetManagementSameChannelParameters)
			EDX_ENCODE (SetManagementDifferentChannelParameters)
			EDX_ENCODE (SupportedCDMAChannels)
			default:;
		};
		return (ED_EXLONG)lenInBits;
#undef EDX_ENCODE
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Inter_RAT_Route_Update (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Inter_RAT_Route_Update* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int attrId;
#define EDX_DECODE(TYPNAM) {SETPRESENT_c_RPD_Inter_RAT_Route_Update_complex_##TYPNAM (&Destin->complex); DECODE_c_RPD_Inter_RAT_Route_Update_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}

		attrId = SHIFT_INT (8);
		switch (attrId) {
			case 0x00: {
				Destin->AttributeId = 0x00;
				EDX_DECODE (SearchParameters)
				break;
			}
			case 0x01: {
				Destin->AttributeId = 0x01;
				EDX_DECODE (SetManagementSameChannelParameters)
				break;
			}
			case 0x02: {
				Destin->AttributeId = 0x02;
				EDX_DECODE (SetManagementDifferentChannelParameters)
				break;
			}
			case 0x03: {
				Destin->AttributeId = 0x03;
				SETPRESENT_c_RPD_Inter_RAT_Route_Update_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
				break;
			}
			case 0x04: {
				Destin->AttributeId = 0x04;
				EDX_DECODE (SupportedCDMAChannels)
				break;
			}
			case 0xfd: {
				Destin->AttributeId = 0xfd;
				SETPRESENT_c_RPD_Inter_RAT_Route_Update_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
				break;
			}
			case 0xfe: {
				Destin->AttributeId = 0xfe;
				SETPRESENT_c_RPD_Inter_RAT_Route_Update_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
				break;
			}
			case 0xff: {
				Destin->AttributeId = 0xff;
				SETPRESENT_c_RPD_Inter_RAT_Route_Update_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
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

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Inter_RAT_Overhead_Messages (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Inter_RAT_Overhead_Messages* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int attrId = 0;
		int lenInBits = EDBitsToInt (Buffer, BitOffset-8, 8) * 8;
#define EDX_ENCODE(TYPNAM) case U_c_RPD_Inter_RAT_Overhead_Messages_complex_##TYPNAM: ENCODE_c_RPD_Inter_RAT_Overhead_Messages_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); break;


		attrId = (int)Source->AttributeId;
		if (GETPRESENT_c_RPD_Inter_RAT_Overhead_Messages_NN (Source)) {
			attrId |= (int)Source->NN;
		}
		PUSH_INT (attrId, 8);
		if (GETPRESENT_c_RPD_Inter_RAT_Overhead_Messages_Value (Source)) {
			PUSH_INT (Source->Value, 8);
		}
		return (ED_EXLONG)lenInBits;
#undef EDX_ENCODE
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Inter_RAT_Overhead_Messages (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Inter_RAT_Overhead_Messages* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int attrId;
#define EDX_DECODE(TYPNAM) {SETPRESENT_c_RPD_Inter_RAT_Overhead_Messages_complex_##TYPNAM (&Destin->complex); DECODE_c_RPD_Inter_RAT_Overhead_Messages_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}

		attrId = SHIFT_INT (8);
		switch (attrId) {
			case 0xfe: {
				Destin->AttributeId = 0xfe;
				SETPRESENT_c_RPD_Inter_RAT_Overhead_Messages_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
				break;
			}
			case 0xff: {
				Destin->AttributeId = 0xff;
				SETPRESENT_c_RPD_Inter_RAT_Overhead_Messages_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
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

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Inter_RAT_Quick_Idle_State (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Inter_RAT_Quick_Idle_State* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int attrId = 0;
		int lenInBits = EDBitsToInt (Buffer, BitOffset-8, 8) * 8;
#define EDX_ENCODE(TYPNAM) case U_c_RPD_Inter_RAT_Quick_Idle_State_complex_##TYPNAM: ENCODE_c_RPD_Inter_RAT_Quick_Idle_State_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); break;


		attrId = (int)Source->AttributeId;
		if (GETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_NN (Source)) {
			attrId |= (int)Source->NN;
		}
		PUSH_INT (attrId, 8);
		if (GETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_Value (Source)) {
			PUSH_INT (Source->Value, 8);
		}
		switch (GETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_complex (&Source->complex)) {
			EDX_ENCODE (PreferredControlChannelCycle)
			EDX_ENCODE (SlottedMode)
			EDX_ENCODE (PagingMask)
			default:;
		};
		return (ED_EXLONG)lenInBits;
#undef EDX_ENCODE
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Inter_RAT_Quick_Idle_State (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Inter_RAT_Quick_Idle_State* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int attrId;
#define EDX_DECODE(TYPNAM) {SETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_complex_##TYPNAM (&Destin->complex); DECODE_c_RPD_Inter_RAT_Quick_Idle_State_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}

		attrId = SHIFT_INT (8);
		switch (attrId) {
			case 0x00: {
				Destin->AttributeId = 0x00;
				EDX_DECODE (PreferredControlChannelCycle)
				break;
			}
			case 0x01: {
				Destin->AttributeId = 0x01;
				EDX_DECODE (SlottedMode)
				break;
			}
			case 0x02: {
				Destin->AttributeId = 0x02;
				EDX_DECODE (PagingMask)
				break;
			}
			case 0xfc: {
				Destin->AttributeId = 0xfc;
				SETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
				break;
			}
			case 0xfd: {
				Destin->AttributeId = 0xfd;
				SETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
				break;
			}
			case 0xfe: {
				Destin->AttributeId = 0xfe;
				SETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
				break;
			}
			case 0xff: {
				Destin->AttributeId = 0xff;
				SETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
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

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Subtype1_based_Inter_RAT_Route_Update (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Subtype1_based_Inter_RAT_Route_Update* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int attrId = 0;
		int lenInBits = EDBitsToInt (Buffer, BitOffset-8, 8) * 8;
#define EDX_ENCODE(TYPNAM) case U_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_##TYPNAM: ENCODE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); break;


		attrId = (int)Source->AttributeId;
		if (GETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_NN (Source)) {
			attrId |= (int)Source->NN;
		}
		PUSH_INT (attrId, 8);
		if (GETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_Value (Source)) {
			PUSH_INT (Source->Value, 8);
		}
		switch (GETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex (&Source->complex)) {
			EDX_ENCODE (SearchParameters)
			EDX_ENCODE (SetManagementParameters)
			EDX_ENCODE (SupportedCDMAChannels)
			EDX_ENCODE (SupportedDRXPatterns)
			default:;
		};
		return (ED_EXLONG)lenInBits;
#undef EDX_ENCODE
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Subtype1_based_Inter_RAT_Route_Update (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Subtype1_based_Inter_RAT_Route_Update* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int attrId;
#define EDX_DECODE(TYPNAM) {SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_##TYPNAM (&Destin->complex); DECODE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}

		attrId = SHIFT_INT (8);
		switch (attrId) {
			case 0x00: {
				Destin->AttributeId = 0x00;
				EDX_DECODE (SearchParameters)
				break;
			}
			case 0x01: {
				Destin->AttributeId = 0x01;
				EDX_DECODE (SetManagementParameters)
				break;
			}
			case 0x04: {
				Destin->AttributeId = 0x04;
				EDX_DECODE (SupportedCDMAChannels)
				break;
			}
			case 0x05: {
				Destin->AttributeId = 0x05;
				EDX_DECODE (SupportedDRXPatterns)
				break;
			}
			case 0xf6: {
				Destin->AttributeId = 0xf6;
				SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
				break;
			}
			case 0xf7: {
				Destin->AttributeId = 0xf7;
				SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
				break;
			}
			case 0xf8: {
				Destin->AttributeId = 0xf8;
				SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
				break;
			}
			case 0xf9: {
				Destin->AttributeId = 0xf9;
				SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
				break;
			}
			case 0xfa: {
				Destin->AttributeId = 0xfa;
				SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
				break;
			}
			case 0xfb: {
				Destin->AttributeId = 0xfb;
				SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
				break;
			}
			case 0xfc: {
				Destin->AttributeId = 0xfc;
				SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
				break;
			}
			case 0xfd: {
				Destin->AttributeId = 0xfd;
				SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
				break;
			}
			case 0xfe: {
				Destin->AttributeId = 0xfe;
				SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
				break;
			}
			case 0xff: {
				Destin->AttributeId = 0xff;
				SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
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

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Inter_RAT_Overhead_Messages_CS0024B* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int attrId = 0;
		int lenInBits = EDBitsToInt (Buffer, BitOffset-8, 8) * 8;
#define EDX_ENCODE(TYPNAM) case U_c_RPD_Inter_RAT_Overhead_Messages_CS0024B_complex_##TYPNAM: ENCODE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B_##TYPNAM (Buffer, CurrOfs , ED_AMP(Source->complex.u.TYPNAM) ED_EXTRAPARAMS_CALL); break;


		attrId = (int)Source->AttributeId;
		if (GETPRESENT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B_NN (Source)) {
			attrId |= (int)Source->NN;
		}
		PUSH_INT (attrId, 8);
		if (GETPRESENT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B_Value (Source)) {
			PUSH_INT (Source->Value, 8);
		}
		return (ED_EXLONG)lenInBits;
#undef EDX_ENCODE
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Inter_RAT_Overhead_Messages_CS0024B* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	
	{

		int attrId;
#define EDX_DECODE(TYPNAM) {SETPRESENT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B_complex_##TYPNAM (&Destin->complex); DECODE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B_##TYPNAM (Buffer, CurrOfs, ED_AMP(Destin->complex.u.TYPNAM), Length-(CurrOfs-BitOffset) ED_EXTRAPARAMS_CALL);}

		attrId = SHIFT_INT (8);
		switch (attrId) {
			case 0xfc: {
				Destin->AttributeId = 0xfc;
				SETPRESENT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
				break;
			}
			case 0xfd: {
				Destin->AttributeId = 0xfd;
				SETPRESENT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
				break;
			}
			case 0xfe: {
				Destin->AttributeId = 0xfe;
				SETPRESENT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
				break;
			}
			case 0xff: {
				Destin->AttributeId = 0xff;
				SETPRESENT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B_Value (Destin, ED_TRUE);
				Destin->Value = (ED_LONG)SHIFT_INT (8);
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
/* IEEE 802.16 GENERIC TLV ENCODER */
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_GenericTLV_cs0087 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GenericTLV_cs0087* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))
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
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_GenericTLV_cs0087 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GenericTLV_cs0087* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))
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
	ALLOC_c_GenericTLV_cs0087_TLV_Data (&(Destin->TLV_Data), DataLength);

	
	/* Save the bits in the binary data */
	EDCopyBits (Destin->TLV_Data.value, 0, Buffer, CurrOfs, DataLength);
	CurrOfs += (ED_EXLONG)EffectiveDataLength;

	return (CurrOfs-BitOffset);
}

#undef THIS
