/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __UserDefinedDataTypes_cs0063_h
#define __UserDefinedDataTypes_cs0063_h
#include "ed_lib.h"
#include "ed_c_cs0063.h"
#include "ed_user.h"
#include "endec_configs_cs0063.h"
#if ED_COMMON_CRC != 0x328E3625 && ED_VERSION != 10152 && ED_VERSION != 10153
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.154
#endif


#ifdef __cplusplus
	extern "C" {
#endif

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPD_Enhanced_Multi_Flow_Packet_Application_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPD_Multi_link_Multi_Flow_Packet_Application_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "GenericTLV_cs0063".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_GenericTLV_cs0063 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GenericTLV_cs0063* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_GenericTLV_cs0063 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GenericTLV_cs0063* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));


#ifdef __cplusplus
	}
#endif
#endif

