/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __UserDefinedDataTypes_cs0087_h
#define __UserDefinedDataTypes_cs0087_h
#include "ed_lib.h"
#include "ed_c_cs0087.h"
#include "ed_user.h"
#include "endec_configs_cs0087.h"
#if ED_COMMON_CRC != 0x328E3625 && ED_VERSION != 10152 && ED_VERSION != 10153
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.154
#endif


#ifdef __cplusplus
	extern "C" {
#endif

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPD_Session_Layer_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Session_Layer_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Session_Layer_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Session_Layer_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Session_Layer_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPD_Inter_RAT_Idle_State".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Inter_RAT_Idle_State (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Inter_RAT_Idle_State* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Inter_RAT_Idle_State (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Inter_RAT_Idle_State* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPD_Inter_RAT_Route_Update".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Inter_RAT_Route_Update (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Inter_RAT_Route_Update* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Inter_RAT_Route_Update (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Inter_RAT_Route_Update* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPD_Inter_RAT_Overhead_Messages".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Inter_RAT_Overhead_Messages (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Inter_RAT_Overhead_Messages* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Inter_RAT_Overhead_Messages (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Inter_RAT_Overhead_Messages* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPD_Inter_RAT_Quick_Idle_State".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Inter_RAT_Quick_Idle_State (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Inter_RAT_Quick_Idle_State* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Inter_RAT_Quick_Idle_State (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Inter_RAT_Quick_Idle_State* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPD_Subtype1_based_Inter_RAT_Route_Update".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Subtype1_based_Inter_RAT_Route_Update (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Subtype1_based_Inter_RAT_Route_Update* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Subtype1_based_Inter_RAT_Route_Update (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Subtype1_based_Inter_RAT_Route_Update* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPD_Inter_RAT_Overhead_Messages_CS0024B".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Inter_RAT_Overhead_Messages_CS0024B* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Inter_RAT_Overhead_Messages_CS0024B* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "GenericTLV_cs0087".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_GenericTLV_cs0087 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GenericTLV_cs0087* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_GenericTLV_cs0087 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GenericTLV_cs0087* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));


#ifdef __cplusplus
	}
#endif
#endif

