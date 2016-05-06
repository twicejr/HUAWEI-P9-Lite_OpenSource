/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __MFPAPP_LUP_INUSE_cs0024_h
#define __MFPAPP_LUP_INUSE_cs0024_h
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
	Encoding/decoding functions for "MFPAPP_LUP_INUSE_LocationRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MFPAPP_LUP_INUSE_LocationRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MFPAPP_LUP_INUSE_LocationRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MFPAPP_LUP_INUSE_LocationRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MFPAPP_LUP_INUSE_LocationRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "MFPAPP_LUP_INUSE_LocationRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MFPAPP_LUP_INUSE_LocationRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MFPAPP_LUP_INUSE_LocationRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MFPAPP_LUP_INUSE_LocationRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MFPAPP_LUP_INUSE_LocationRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MFPAPP_LUP_INUSE_LocationNotification".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MFPAPP_LUP_INUSE_LocationNotification (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MFPAPP_LUP_INUSE_LocationNotification* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MFPAPP_LUP_INUSE_LocationNotification (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MFPAPP_LUP_INUSE_LocationNotification* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "MFPAPP_LUP_INUSE_LocationNotification".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MFPAPP_LUP_INUSE_LocationNotification (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MFPAPP_LUP_INUSE_LocationNotification* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MFPAPP_LUP_INUSE_LocationNotification (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MFPAPP_LUP_INUSE_LocationNotification* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MFPAPP_LUP_INUSE_LocationAssignment".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MFPAPP_LUP_INUSE_LocationAssignment (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MFPAPP_LUP_INUSE_LocationAssignment* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MFPAPP_LUP_INUSE_LocationAssignment (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MFPAPP_LUP_INUSE_LocationAssignment* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "MFPAPP_LUP_INUSE_LocationAssignment".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MFPAPP_LUP_INUSE_LocationAssignment (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MFPAPP_LUP_INUSE_LocationAssignment* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MFPAPP_LUP_INUSE_LocationAssignment (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MFPAPP_LUP_INUSE_LocationAssignment* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MFPAPP_LUP_INUSE_LocationComplete".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MFPAPP_LUP_INUSE_LocationComplete (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MFPAPP_LUP_INUSE_LocationComplete* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MFPAPP_LUP_INUSE_LocationComplete (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MFPAPP_LUP_INUSE_LocationComplete* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "MFPAPP_LUP_INUSE_LocationComplete".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MFPAPP_LUP_INUSE_LocationComplete (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MFPAPP_LUP_INUSE_LocationComplete* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MFPAPP_LUP_INUSE_LocationComplete (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MFPAPP_LUP_INUSE_LocationComplete* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MFPAPP_LUP_INUSE_StorageBLOBRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MFPAPP_LUP_INUSE_StorageBLOBRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MFPAPP_LUP_INUSE_StorageBLOBRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MFPAPP_LUP_INUSE_StorageBLOBRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MFPAPP_LUP_INUSE_StorageBLOBRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "MFPAPP_LUP_INUSE_StorageBLOBRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MFPAPP_LUP_INUSE_StorageBLOBRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MFPAPP_LUP_INUSE_StorageBLOBRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MFPAPP_LUP_INUSE_StorageBLOBRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MFPAPP_LUP_INUSE_StorageBLOBRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MFPAPP_LUP_INUSE_StorageBLOBNotification".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MFPAPP_LUP_INUSE_StorageBLOBNotification (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MFPAPP_LUP_INUSE_StorageBLOBNotification* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MFPAPP_LUP_INUSE_StorageBLOBNotification (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MFPAPP_LUP_INUSE_StorageBLOBNotification* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "MFPAPP_LUP_INUSE_StorageBLOBNotification".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MFPAPP_LUP_INUSE_StorageBLOBNotification (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MFPAPP_LUP_INUSE_StorageBLOBNotification* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MFPAPP_LUP_INUSE_StorageBLOBNotification (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MFPAPP_LUP_INUSE_StorageBLOBNotification* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MFPAPP_LUP_INUSE_StorageBLOBAssignment".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MFPAPP_LUP_INUSE_StorageBLOBAssignment (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MFPAPP_LUP_INUSE_StorageBLOBAssignment* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MFPAPP_LUP_INUSE_StorageBLOBAssignment (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MFPAPP_LUP_INUSE_StorageBLOBAssignment* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "MFPAPP_LUP_INUSE_StorageBLOBAssignment".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MFPAPP_LUP_INUSE_StorageBLOBAssignment (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MFPAPP_LUP_INUSE_StorageBLOBAssignment* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MFPAPP_LUP_INUSE_StorageBLOBAssignment (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MFPAPP_LUP_INUSE_StorageBLOBAssignment* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MFPAPP_LUP_INUSE_StorageBLOBComplete".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MFPAPP_LUP_INUSE_StorageBLOBComplete (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MFPAPP_LUP_INUSE_StorageBLOBComplete* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MFPAPP_LUP_INUSE_StorageBLOBComplete (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MFPAPP_LUP_INUSE_StorageBLOBComplete* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "MFPAPP_LUP_INUSE_StorageBLOBComplete".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MFPAPP_LUP_INUSE_StorageBLOBComplete (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MFPAPP_LUP_INUSE_StorageBLOBComplete* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MFPAPP_LUP_INUSE_StorageBLOBComplete (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MFPAPP_LUP_INUSE_StorageBLOBComplete* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

int Match_c_MFPAPP_LUP_INUSE_LocationRequest (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_MFPAPP_LUP_INUSE_LocationNotification (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_MFPAPP_LUP_INUSE_LocationAssignment (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_MFPAPP_LUP_INUSE_LocationComplete (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_MFPAPP_LUP_INUSE_StorageBLOBRequest (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_MFPAPP_LUP_INUSE_StorageBLOBNotification (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_MFPAPP_LUP_INUSE_StorageBLOBAssignment (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_MFPAPP_LUP_INUSE_StorageBLOBComplete (const char* Buffer, ED_CONST ED_EXLONG BitOffset);

#ifdef __cplusplus
	}
#endif
#endif

