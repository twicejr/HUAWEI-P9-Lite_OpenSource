/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __RPDSES_SL_cs0087_h
#define __RPDSES_SL_cs0087_h
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
	Encoding/decoding functions for "RPDSES_SL_UATIAssignment".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDSES_SL_UATIAssignment (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDSES_SL_UATIAssignment* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDSES_SL_UATIAssignment (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDSES_SL_UATIAssignment* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RPDSES_SL_UATIAssignment".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDSES_SL_UATIAssignment (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDSES_SL_UATIAssignment* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDSES_SL_UATIAssignment (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDSES_SL_UATIAssignment* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPDSES_SL_InterRATMobilityIndication".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDSES_SL_InterRATMobilityIndication (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDSES_SL_InterRATMobilityIndication* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDSES_SL_InterRATMobilityIndication (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDSES_SL_InterRATMobilityIndication* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RPDSES_SL_InterRATMobilityIndication".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDSES_SL_InterRATMobilityIndication (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDSES_SL_InterRATMobilityIndication* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDSES_SL_InterRATMobilityIndication (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDSES_SL_InterRATMobilityIndication* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPDSES_SL_InterRATMobilityAck".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDSES_SL_InterRATMobilityAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDSES_SL_InterRATMobilityAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDSES_SL_InterRATMobilityAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDSES_SL_InterRATMobilityAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RPDSES_SL_InterRATMobilityAck".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDSES_SL_InterRATMobilityAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDSES_SL_InterRATMobilityAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDSES_SL_InterRATMobilityAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDSES_SL_InterRATMobilityAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

int Match_c_RPDSES_SL_UATIAssignment (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_RPDSES_SL_InterRATMobilityIndication (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_RPDSES_SL_InterRATMobilityAck (const char* Buffer, ED_CONST ED_EXLONG BitOffset);

#ifdef __cplusplus
	}
#endif
#endif

