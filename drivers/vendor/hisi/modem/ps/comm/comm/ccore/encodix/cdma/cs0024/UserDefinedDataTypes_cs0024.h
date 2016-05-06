/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __UserDefinedDataTypes_cs0024_h
#define __UserDefinedDataTypes_cs0024_h
#include "ed_lib.h"
#include "ed_c_cs0024.h"
#include "ed_user.h"
#include "endec_configs_cs0024.h"
#if ED_COMMON_CRC != 0x328E3625 && ED_VERSION != 10152 && ED_VERSION != 10153
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.154
#endif


#ifdef __cplusplus
	extern "C" {
#endif

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Default_Packet_Application_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Packet_Application_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Packet_Application_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Packet_Application_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Packet_Application_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Default_Packet_Application_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Packet_Application_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Packet_Application_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Packet_Application_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Packet_Application_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Multi_Flow_Packet_Application_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Multi_Flow_Packet_Application_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Multi_Flow_Packet_Application_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Multi_Flow_Packet_Application_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Multi_Flow_Packet_Application_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Multi_Flow_Packet_Application_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Multi_Flow_Packet_Application_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Multi_Flow_Packet_Application_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Multi_Flow_Packet_Application_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Multi_Flow_Packet_Application_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Default_Stream_Protocol_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Stream_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Stream_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Stream_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Stream_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Default_Stream_Protocol_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Stream_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Stream_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Stream_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Stream_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Generic_Virtual_Stream_Protocol_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Generic_Virtual_Stream_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Generic_Virtual_Stream_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Generic_Virtual_Stream_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Generic_Virtual_Stream_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Generic_Virtual_Stream_Protocol_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Generic_Virtual_Stream_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Generic_Virtual_Stream_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Generic_Virtual_Stream_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Generic_Virtual_Stream_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Default_Session_Management_Protocol_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Session_Management_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Session_Management_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Session_Management_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Session_Management_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Default_Session_Management_Protocol_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Session_Management_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Session_Management_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Session_Management_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Session_Management_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Default_Address_Management_Protocol_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Address_Management_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Address_Management_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Address_Management_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Address_Management_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Default_Address_Management_Protocol_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Address_Management_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Address_Management_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Address_Management_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Address_Management_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Default_Session_Configuration_Protocol_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Session_Configuration_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Session_Configuration_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Session_Configuration_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Session_Configuration_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Default_Session_Configuration_Protocol_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Session_Configuration_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Session_Configuration_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Session_Configuration_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Session_Configuration_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Generic_Multimode_Capability_Discovery_Protocol_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Generic_Multimode_Capability_Discovery_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Generic_Multimode_Capability_Discovery_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Generic_Multimode_Capability_Discovery_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Generic_Multimode_Capability_Discovery_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Generic_Multimode_Capability_Discovery_Protocol_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Generic_Multimode_Capability_Discovery_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Generic_Multimode_Capability_Discovery_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Generic_Multimode_Capability_Discovery_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Generic_Multimode_Capability_Discovery_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Default_Air_Link_Management_Protocol_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Air_Link_Management_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Air_Link_Management_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Air_Link_Management_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Air_Link_Management_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Default_Air_Link_Management_Protocol_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Air_Link_Management_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Air_Link_Management_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Air_Link_Management_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Air_Link_Management_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Default_Idle_State_Protocol_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Idle_State_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Idle_State_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Idle_State_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Idle_State_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Default_Idle_State_Protocol_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Idle_State_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Idle_State_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Idle_State_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Idle_State_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Enhanced_Idle_State_Protocol_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Enhanced_Idle_State_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Enhanced_Idle_State_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Enhanced_Idle_State_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Enhanced_Idle_State_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Enhanced_Idle_State_Protocol_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Enhanced_Idle_State_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Enhanced_Idle_State_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Enhanced_Idle_State_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Enhanced_Idle_State_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Quick_Idle_State_Protocol_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Quick_Idle_State_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Quick_Idle_State_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Quick_Idle_State_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Quick_Idle_State_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Quick_Idle_State_Protocol_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Quick_Idle_State_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Quick_Idle_State_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Quick_Idle_State_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Quick_Idle_State_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Default_Route_Update_Protocol_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Route_Update_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Route_Update_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Route_Update_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Route_Update_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Default_Route_Update_Protocol_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Route_Update_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Route_Update_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Route_Update_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Route_Update_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Multicarrier_Route_Update_Protocol_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Multicarrier_Route_Update_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Multicarrier_Route_Update_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Multicarrier_Route_Update_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Multicarrier_Route_Update_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Multicarrier_Route_Update_Protocol_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Multicarrier_Route_Update_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Multicarrier_Route_Update_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Multicarrier_Route_Update_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Multicarrier_Route_Update_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Overhead_Messages_Protocol_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Overhead_Messages_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Overhead_Messages_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Overhead_Messages_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Overhead_Messages_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Overhead_Messages_Protocol_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Overhead_Messages_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Overhead_Messages_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Overhead_Messages_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Overhead_Messages_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_DH_Key_Exchange_Protocol_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_DH_Key_Exchange_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_DH_Key_Exchange_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_DH_Key_Exchange_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_DH_Key_Exchange_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_DH_Key_Exchange_Protocol_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_DH_Key_Exchange_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_DH_Key_Exchange_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_DH_Key_Exchange_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_DH_Key_Exchange_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_SHA_1_Authentication_Protocol_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_SHA_1_Authentication_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_SHA_1_Authentication_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_SHA_1_Authentication_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_SHA_1_Authentication_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_SHA_1_Authentication_Protocol_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_SHA_1_Authentication_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_SHA_1_Authentication_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_SHA_1_Authentication_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_SHA_1_Authentication_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Enhanced_Control_Channel_MAC_Protocol_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Enhanced_Control_Channel_MAC_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Enhanced_Control_Channel_MAC_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Enhanced_Control_Channel_MAC_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Enhanced_Control_Channel_MAC_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Enhanced_Control_Channel_MAC_Protocol_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Enhanced_Control_Channel_MAC_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Enhanced_Control_Channel_MAC_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Enhanced_Control_Channel_MAC_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Enhanced_Control_Channel_MAC_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Default_Access_Channel_MAC_Protocol_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Access_Channel_MAC_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Access_Channel_MAC_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Access_Channel_MAC_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Access_Channel_MAC_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Default_Access_Channel_MAC_Protocol_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Access_Channel_MAC_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Access_Channel_MAC_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Access_Channel_MAC_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Access_Channel_MAC_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Enhanced_Access_Channel_MAC_Protocol_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Enhanced_Access_Channel_MAC_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Enhanced_Access_Channel_MAC_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Enhanced_Access_Channel_MAC_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Enhanced_Access_Channel_MAC_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Enhanced_Access_Channel_MAC_Protocol_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Enhanced_Access_Channel_MAC_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Enhanced_Access_Channel_MAC_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Enhanced_Access_Channel_MAC_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Enhanced_Access_Channel_MAC_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Default_Forward_Traffic_Channel_MAC_Protocol_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Forward_Traffic_Channel_MAC_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Forward_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Forward_Traffic_Channel_MAC_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Forward_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Default_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Enhanced_Forward_Traffic_Channel_MAC_Protocol_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Enhanced_Forward_Traffic_Channel_MAC_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Enhanced_Forward_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Enhanced_Forward_Traffic_Channel_MAC_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Enhanced_Forward_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Enhanced_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Enhanced_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Enhanced_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Enhanced_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Enhanced_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Multicarrier_Forward_Traffic_Channel_MAC_Protocol_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Multicarrier_Forward_Traffic_Channel_MAC_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Multicarrier_Forward_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Multicarrier_Forward_Traffic_Channel_MAC_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Multicarrier_Forward_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Multicarrier_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Multicarrier_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Multicarrier_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Multicarrier_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Multicarrier_Forward_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Default_Reverse_Traffic_Channel_MAC_Protocol_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Reverse_Traffic_Channel_MAC_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Reverse_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Reverse_Traffic_Channel_MAC_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Reverse_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Default_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Default_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Default_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Default_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Default_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Subtype_1_Reverse_Traffic_Channel_MAC_Protocol_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Subtype_1_Reverse_Traffic_Channel_MAC_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Subtype_1_Reverse_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Subtype_1_Reverse_Traffic_Channel_MAC_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Subtype_1_Reverse_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Subtype_1_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Subtype_1_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Subtype_1_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Subtype_1_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Subtype_1_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Subtype_3_Reverse_Traffic_Channel_MAC_Protocol_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Subtype_3_Reverse_Traffic_Channel_MAC_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Subtype_3_Reverse_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Subtype_3_Reverse_Traffic_Channel_MAC_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Subtype_3_Reverse_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Subtype_3_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Subtype_3_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Subtype_3_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Subtype_3_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Subtype_3_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Multicarrier_Reverse_Traffic_Channel_MAC_Protocol_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Multicarrier_Reverse_Traffic_Channel_MAC_Protocol_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Multicarrier_Reverse_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Multicarrier_Reverse_Traffic_Channel_MAC_Protocol_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Multicarrier_Reverse_Traffic_Channel_MAC_Protocol_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Multicarrier_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Multicarrier_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Multicarrier_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Multicarrier_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Multicarrier_Reverse_Traffic_Channel_MAC_Protocol_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Subtype_3_Physical_Layer_Protocol_Instance_Attributes".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Subtype_3_Physical_Layer_Protocol_Instance_Attributes (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Subtype_3_Physical_Layer_Protocol_Instance_Attributes* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Subtype_3_Physical_Layer_Protocol_Instance_Attributes (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Subtype_3_Physical_Layer_Protocol_Instance_Attributes* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Subtype_3_Physical_Layer_Protocol_Instance_Attributes_Response".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Subtype_3_Physical_Layer_Protocol_Instance_Attributes_Response (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Subtype_3_Physical_Layer_Protocol_Instance_Attributes_Response* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Subtype_3_Physical_Layer_Protocol_Instance_Attributes_Response (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Subtype_3_Physical_Layer_Protocol_Instance_Attributes_Response* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Attribute_Response_16".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Attribute_Response_16 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Attribute_Response_16* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Attribute_Response_16 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Attribute_Response_16* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Air_Attribute_Response_8".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Air_Attribute_Response_8 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Air_Attribute_Response_8* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Air_Attribute_Response_8 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Air_Attribute_Response_8* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "GenericTLV_cs0024".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_GenericTLV_cs0024 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GenericTLV_cs0024* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_GenericTLV_cs0024 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GenericTLV_cs0024* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));


#ifdef __cplusplus
	}
#endif
#endif

