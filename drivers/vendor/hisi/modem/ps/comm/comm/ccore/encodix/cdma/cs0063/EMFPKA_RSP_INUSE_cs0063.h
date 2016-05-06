/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __EMFPKA_RSP_INUSE_cs0063_h
#define __EMFPKA_RSP_INUSE_cs0063_h
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
	Encoding/decoding functions for "EMFPKA_RSP_INUSE_RouteSelect".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RSP_INUSE_RouteSelect (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RSP_INUSE_RouteSelect* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RSP_INUSE_RouteSelect (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RSP_INUSE_RouteSelect* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EMFPKA_RSP_INUSE_RouteSelect".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EMFPKA_RSP_INUSE_RouteSelect (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RSP_INUSE_RouteSelect* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EMFPKA_RSP_INUSE_RouteSelect (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RSP_INUSE_RouteSelect* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EMFPKA_RSP_INUSE_RouteSelectAck".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RSP_INUSE_RouteSelectAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RSP_INUSE_RouteSelectAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RSP_INUSE_RouteSelectAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RSP_INUSE_RouteSelectAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EMFPKA_RSP_INUSE_RouteSelectAck".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EMFPKA_RSP_INUSE_RouteSelectAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RSP_INUSE_RouteSelectAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EMFPKA_RSP_INUSE_RouteSelectAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RSP_INUSE_RouteSelectAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EMFPKA_RSP_INUSE_ActivateRoute".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RSP_INUSE_ActivateRoute (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RSP_INUSE_ActivateRoute* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RSP_INUSE_ActivateRoute (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RSP_INUSE_ActivateRoute* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EMFPKA_RSP_INUSE_ActivateRoute".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EMFPKA_RSP_INUSE_ActivateRoute (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RSP_INUSE_ActivateRoute* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EMFPKA_RSP_INUSE_ActivateRoute (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RSP_INUSE_ActivateRoute* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EMFPKA_RSP_INUSE_ActivateRouteAck".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RSP_INUSE_ActivateRouteAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RSP_INUSE_ActivateRouteAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RSP_INUSE_ActivateRouteAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RSP_INUSE_ActivateRouteAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EMFPKA_RSP_INUSE_ActivateRouteAck".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EMFPKA_RSP_INUSE_ActivateRouteAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RSP_INUSE_ActivateRouteAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EMFPKA_RSP_INUSE_ActivateRouteAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RSP_INUSE_ActivateRouteAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

int Match_c_EMFPKA_RSP_INUSE_RouteSelect (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_EMFPKA_RSP_INUSE_RouteSelectAck (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_EMFPKA_RSP_INUSE_ActivateRoute (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_EMFPKA_RSP_INUSE_ActivateRouteAck (const char* Buffer, ED_CONST ED_EXLONG BitOffset);

#ifdef __cplusplus
	}
#endif
#endif

