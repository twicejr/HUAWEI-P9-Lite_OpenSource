/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __CONN_DRUP_INUSE_cs0024_h
#define __CONN_DRUP_INUSE_cs0024_h
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
	Encoding/decoding functions for "CONN_DRUP_INUSE_RouteUpdate".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CONN_DRUP_INUSE_RouteUpdate (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONN_DRUP_INUSE_RouteUpdate* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CONN_DRUP_INUSE_RouteUpdate (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONN_DRUP_INUSE_RouteUpdate* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CONN_DRUP_INUSE_RouteUpdate".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CONN_DRUP_INUSE_RouteUpdate (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONN_DRUP_INUSE_RouteUpdate* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CONN_DRUP_INUSE_RouteUpdate (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONN_DRUP_INUSE_RouteUpdate* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CONN_DRUP_INUSE_TrafficChannelAssignment".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CONN_DRUP_INUSE_TrafficChannelAssignment (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONN_DRUP_INUSE_TrafficChannelAssignment* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CONN_DRUP_INUSE_TrafficChannelAssignment (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONN_DRUP_INUSE_TrafficChannelAssignment* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CONN_DRUP_INUSE_TrafficChannelAssignment".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CONN_DRUP_INUSE_TrafficChannelAssignment (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONN_DRUP_INUSE_TrafficChannelAssignment* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CONN_DRUP_INUSE_TrafficChannelAssignment (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONN_DRUP_INUSE_TrafficChannelAssignment* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CONN_DRUP_INUSE_TrafficChannelComplete".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CONN_DRUP_INUSE_TrafficChannelComplete (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONN_DRUP_INUSE_TrafficChannelComplete* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CONN_DRUP_INUSE_TrafficChannelComplete (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONN_DRUP_INUSE_TrafficChannelComplete* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CONN_DRUP_INUSE_TrafficChannelComplete".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CONN_DRUP_INUSE_TrafficChannelComplete (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONN_DRUP_INUSE_TrafficChannelComplete* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CONN_DRUP_INUSE_TrafficChannelComplete (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONN_DRUP_INUSE_TrafficChannelComplete* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CONN_DRUP_INUSE_ResetReport".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CONN_DRUP_INUSE_ResetReport (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONN_DRUP_INUSE_ResetReport* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CONN_DRUP_INUSE_ResetReport (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONN_DRUP_INUSE_ResetReport* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CONN_DRUP_INUSE_ResetReport".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CONN_DRUP_INUSE_ResetReport (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONN_DRUP_INUSE_ResetReport* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CONN_DRUP_INUSE_ResetReport (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONN_DRUP_INUSE_ResetReport* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CONN_DRUP_INUSE_NeighborList".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CONN_DRUP_INUSE_NeighborList (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONN_DRUP_INUSE_NeighborList* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CONN_DRUP_INUSE_NeighborList (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONN_DRUP_INUSE_NeighborList* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CONN_DRUP_INUSE_NeighborList".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CONN_DRUP_INUSE_NeighborList (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONN_DRUP_INUSE_NeighborList* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CONN_DRUP_INUSE_NeighborList (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONN_DRUP_INUSE_NeighborList* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CONN_DRUP_INUSE_AttributeOverride".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CONN_DRUP_INUSE_AttributeOverride (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONN_DRUP_INUSE_AttributeOverride* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CONN_DRUP_INUSE_AttributeOverride (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONN_DRUP_INUSE_AttributeOverride* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CONN_DRUP_INUSE_AttributeOverride".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CONN_DRUP_INUSE_AttributeOverride (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONN_DRUP_INUSE_AttributeOverride* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CONN_DRUP_INUSE_AttributeOverride (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONN_DRUP_INUSE_AttributeOverride* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CONN_DRUP_INUSE_AttributeOverrideResponse".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CONN_DRUP_INUSE_AttributeOverrideResponse (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONN_DRUP_INUSE_AttributeOverrideResponse* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CONN_DRUP_INUSE_AttributeOverrideResponse (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONN_DRUP_INUSE_AttributeOverrideResponse* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CONN_DRUP_INUSE_AttributeOverrideResponse".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CONN_DRUP_INUSE_AttributeOverrideResponse (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONN_DRUP_INUSE_AttributeOverrideResponse* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CONN_DRUP_INUSE_AttributeOverrideResponse (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONN_DRUP_INUSE_AttributeOverrideResponse* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CONN_DRUP_INUSE_RouteUpdateRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CONN_DRUP_INUSE_RouteUpdateRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONN_DRUP_INUSE_RouteUpdateRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CONN_DRUP_INUSE_RouteUpdateRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONN_DRUP_INUSE_RouteUpdateRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CONN_DRUP_INUSE_RouteUpdateRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CONN_DRUP_INUSE_RouteUpdateRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONN_DRUP_INUSE_RouteUpdateRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CONN_DRUP_INUSE_RouteUpdateRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONN_DRUP_INUSE_RouteUpdateRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CONN_DRUP_INUSE_AttributeUpdateRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CONN_DRUP_INUSE_AttributeUpdateRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONN_DRUP_INUSE_AttributeUpdateRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CONN_DRUP_INUSE_AttributeUpdateRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONN_DRUP_INUSE_AttributeUpdateRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CONN_DRUP_INUSE_AttributeUpdateRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CONN_DRUP_INUSE_AttributeUpdateRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONN_DRUP_INUSE_AttributeUpdateRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CONN_DRUP_INUSE_AttributeUpdateRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONN_DRUP_INUSE_AttributeUpdateRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CONN_DRUP_INUSE_AttributeUpdateAccept".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CONN_DRUP_INUSE_AttributeUpdateAccept (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONN_DRUP_INUSE_AttributeUpdateAccept* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CONN_DRUP_INUSE_AttributeUpdateAccept (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONN_DRUP_INUSE_AttributeUpdateAccept* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CONN_DRUP_INUSE_AttributeUpdateAccept".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CONN_DRUP_INUSE_AttributeUpdateAccept (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONN_DRUP_INUSE_AttributeUpdateAccept* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CONN_DRUP_INUSE_AttributeUpdateAccept (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONN_DRUP_INUSE_AttributeUpdateAccept* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CONN_DRUP_INUSE_AttributeUpdateReject".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CONN_DRUP_INUSE_AttributeUpdateReject (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONN_DRUP_INUSE_AttributeUpdateReject* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CONN_DRUP_INUSE_AttributeUpdateReject (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONN_DRUP_INUSE_AttributeUpdateReject* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CONN_DRUP_INUSE_AttributeUpdateReject".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CONN_DRUP_INUSE_AttributeUpdateReject (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONN_DRUP_INUSE_AttributeUpdateReject* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CONN_DRUP_INUSE_AttributeUpdateReject (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONN_DRUP_INUSE_AttributeUpdateReject* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

int Match_c_CONN_DRUP_INUSE_RouteUpdate (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_CONN_DRUP_INUSE_TrafficChannelAssignment (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_CONN_DRUP_INUSE_TrafficChannelComplete (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_CONN_DRUP_INUSE_ResetReport (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_CONN_DRUP_INUSE_NeighborList (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_CONN_DRUP_INUSE_AttributeOverride (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_CONN_DRUP_INUSE_AttributeOverrideResponse (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_CONN_DRUP_INUSE_RouteUpdateRequest (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_CONN_DRUP_INUSE_AttributeUpdateRequest (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_CONN_DRUP_INUSE_AttributeUpdateAccept (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_CONN_DRUP_INUSE_AttributeUpdateReject (const char* Buffer, ED_CONST ED_EXLONG BitOffset);

#ifdef __cplusplus
	}
#endif
#endif

