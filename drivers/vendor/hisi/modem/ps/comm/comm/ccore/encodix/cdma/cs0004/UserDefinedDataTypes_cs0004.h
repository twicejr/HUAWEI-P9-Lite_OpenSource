/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __UserDefinedDataTypes_cs0004_h
#define __UserDefinedDataTypes_cs0004_h
#include "ed_lib.h"
#include "ed_c_cs0004.h"
#include "ed_user.h"
#include "endec_configs_cs0004.h"
#if ED_COMMON_CRC != 0x328E3625 && ED_VERSION != 10152 && ED_VERSION != 10153
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.154
#endif


#ifdef __cplusplus
	extern "C" {
#endif

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FCSCH_PDU".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_PDU (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_PDU* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_PDU (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_PDU* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FCSCH_PDU_SDUs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_PDU_SDUs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_PDU_SDUs_data* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_PDU_SDUs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_PDU_SDUs_data* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FCSCH_PDU_SDUs_data_Extended_Address".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_PDU_SDUs_data_Extended_Address (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_PDU_SDUs_data_Extended_Address* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_PDU_SDUs_data_Extended_Address (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_PDU_SDUs_data_Extended_Address* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FCSCH_PDU_SDUs_data_IMSI_S".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_PDU_SDUs_data_IMSI_S (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_PDU_SDUs_data_IMSI_S* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_PDU_SDUs_data_IMSI_S (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_PDU_SDUs_data_IMSI_S* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FCSCH_PDU_SDUs_data_ESN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_PDU_SDUs_data_ESN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_PDU_SDUs_data_ESN* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_PDU_SDUs_data_ESN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_PDU_SDUs_data_ESN* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FCSCH_PDU_SDUs_data_IMSI".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_PDU_SDUs_data_IMSI (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_PDU_SDUs_data_IMSI* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_PDU_SDUs_data_IMSI (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_PDU_SDUs_data_IMSI* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FCSCH_PDU_SDUs_data_TMSI".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_PDU_SDUs_data_TMSI (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_PDU_SDUs_data_TMSI* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_PDU_SDUs_data_TMSI (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_PDU_SDUs_data_TMSI* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FCSCH_PDU_SDUs_data_BROADCAST".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_PDU_SDUs_data_BROADCAST (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_PDU_SDUs_data_BROADCAST* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_PDU_SDUs_data_BROADCAST (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_PDU_SDUs_data_BROADCAST* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FCSCH_SYNC_BROADCAST_PDU".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_SYNC_BROADCAST_PDU (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_SYNC_BROADCAST_PDU* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_SYNC_BROADCAST_PDU (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_SYNC_BROADCAST_PDU* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FCSCH_NON_PRIMARY_BROADCAST_PDU".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_NON_PRIMARY_BROADCAST_PDU* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_NON_PRIMARY_BROADCAST_PDU* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "GPM_PDU".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_GPM_PDU (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GPM_PDU* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_GPM_PDU (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GPM_PDU* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "GPM_PDU_page_records_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_GPM_PDU_page_records_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GPM_PDU_page_records_data* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_GPM_PDU_page_records_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GPM_PDU_page_records_data* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "UPM_PDU".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_UPM_PDU (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_UPM_PDU* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_UPM_PDU (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_UPM_PDU* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_Universal_Page_Block".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_Universal_Page_Block (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_Universal_Page_Block* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_Universal_Page_Block (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_Universal_Page_Block* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_Universal_Page_Block_SUBRECORD_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_Universal_Page_Block_SUBRECORD_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_Universal_Page_Block_SUBRECORD_data* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_Universal_Page_Block_SUBRECORD_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_Universal_Page_Block_SUBRECORD_data* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_Universal_Page_Block_page_records_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_Universal_Page_Block_page_records_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_Universal_Page_Block_page_records_data* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_Universal_Page_Block_page_records_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_Universal_Page_Block_page_records_data* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_PDU".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_PDU_LAC_Length".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_LAC_Length (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_LAC_Length* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_LAC_Length (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_LAC_Length* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_PDU_Message_Type".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_Message_Type (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_Message_Type* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_Message_Type (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_Message_Type* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_PDU_ARQ".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_ARQ (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_ARQ* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_ARQ (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_ARQ* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_PDU_Addressing".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_Addressing (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_Addressing* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_Addressing (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_Addressing* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_PDU_Addressing_IMSI_class_specific_subfields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_Addressing_IMSI_class_specific_subfields* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_Addressing_IMSI_class_specific_subfields* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_PDU_Authentication".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_Authentication (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_Authentication* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_Authentication (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_Authentication* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_PDU_Extended_Encryption".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_Extended_Encryption (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_Extended_Encryption* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_Extended_Encryption (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_Extended_Encryption* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_Radio_Environment_Report".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_Radio_Environment_Report (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_Radio_Environment_Report* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_Radio_Environment_Report (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_Radio_Environment_Report* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_PDU_Regular".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_PDU_Regular (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_PDU_Regular* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_PDU_Regular (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_PDU_Regular* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_PDU_Regular_Message_Type".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_PDU_Regular_Message_Type (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_PDU_Regular_Message_Type* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_PDU_Regular_Message_Type (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_PDU_Regular_Message_Type* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_PDU_Regular_ARQ".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_PDU_Regular_ARQ (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_PDU_Regular_ARQ* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_PDU_Regular_ARQ (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_PDU_Regular_ARQ* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_PDU_Regular_Encryption".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_PDU_Regular_Encryption (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_PDU_Regular_Encryption* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_PDU_Regular_Encryption (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_PDU_Regular_Encryption* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_PDU_Regular_Integrity_Fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_PDU_Regular_Integrity_Fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_PDU_Regular_Integrity_Fields* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_PDU_Regular_Integrity_Fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_PDU_Regular_Integrity_Fields* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_PDU_Regular_Extended_Encryption".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_PDU_Regular_Extended_Encryption (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_PDU_Regular_Extended_Encryption* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_PDU_Regular_Extended_Encryption (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_PDU_Regular_Extended_Encryption* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_PDU_Mini".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_PDU_Mini (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_PDU_Mini* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_PDU_Mini (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_PDU_Mini* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_PDU_Mini_ARQ".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_PDU_Mini_ARQ (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_PDU_Mini_ARQ* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_PDU_Mini_ARQ (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_PDU_Mini_ARQ* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_PDU_Mini_Message_Type".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_PDU_Mini_Message_Type (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_PDU_Mini_Message_Type* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_PDU_Mini_Message_Type (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_PDU_Mini_Message_Type* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_PDU_Regular".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PDU_Regular (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PDU_Regular* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PDU_Regular (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PDU_Regular* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_PDU_Regular_Message_Type".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PDU_Regular_Message_Type (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PDU_Regular_Message_Type* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PDU_Regular_Message_Type (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PDU_Regular_Message_Type* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_PDU_Regular_ARQ".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PDU_Regular_ARQ (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PDU_Regular_ARQ* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PDU_Regular_ARQ (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PDU_Regular_ARQ* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_PDU_Regular_Encryption".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PDU_Regular_Encryption (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PDU_Regular_Encryption* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PDU_Regular_Encryption (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PDU_Regular_Encryption* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_PDU_Regular_Integrity_Fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PDU_Regular_Integrity_Fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PDU_Regular_Integrity_Fields* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PDU_Regular_Integrity_Fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PDU_Regular_Integrity_Fields* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_PDU_Regular_Extended_Encryption".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PDU_Regular_Extended_Encryption (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PDU_Regular_Extended_Encryption* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PDU_Regular_Extended_Encryption (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PDU_Regular_Extended_Encryption* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_PDU_Mini".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PDU_Mini (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PDU_Mini* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PDU_Mini (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PDU_Mini* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_PDU_Mini_ARQ".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PDU_Mini_ARQ (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PDU_Mini_ARQ* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PDU_Mini_ARQ (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PDU_Mini_ARQ* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_PDU_Mini_Message_Type".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PDU_Mini_Message_Type (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PDU_Mini_Message_Type* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PDU_Mini_Message_Type (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PDU_Mini_Message_Type* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_UPM_Mobile_Station_Addressed".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UPM_Mobile_Station_Addressed (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UPM_Mobile_Station_Addressed* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UPM_Mobile_Station_Addressed (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UPM_Mobile_Station_Addressed* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_UPM_Enhanced_Broadcast_with_time_offset".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UPM_Enhanced_Broadcast_with_time_offset (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UPM_Enhanced_Broadcast_with_time_offset* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UPM_Enhanced_Broadcast_with_time_offset (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UPM_Enhanced_Broadcast_with_time_offset* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_UPM_Enhanced_Broadcast_without_time_offset".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UPM_Enhanced_Broadcast_without_time_offset (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UPM_Enhanced_Broadcast_without_time_offset* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UPM_Enhanced_Broadcast_without_time_offset (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UPM_Enhanced_Broadcast_without_time_offset* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "GenericTLV_cs0004".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_GenericTLV_cs0004 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GenericTLV_cs0004* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_GenericTLV_cs0004 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GenericTLV_cs0004* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details));


#ifdef __cplusplus
	}
#endif
#endif

