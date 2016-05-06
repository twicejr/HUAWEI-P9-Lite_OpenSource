/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __MAC_DACMACP_INUSE_cs0024_h
#define __MAC_DACMACP_INUSE_cs0024_h
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
	Encoding/decoding functions for "MAC_DACMACP_INUSE_ACAck".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MAC_DACMACP_INUSE_ACAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MAC_DACMACP_INUSE_ACAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MAC_DACMACP_INUSE_ACAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MAC_DACMACP_INUSE_ACAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "MAC_DACMACP_INUSE_ACAck".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MAC_DACMACP_INUSE_ACAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MAC_DACMACP_INUSE_ACAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MAC_DACMACP_INUSE_ACAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MAC_DACMACP_INUSE_ACAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MAC_DACMACP_INUSE_AccessParameters".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MAC_DACMACP_INUSE_AccessParameters (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MAC_DACMACP_INUSE_AccessParameters* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MAC_DACMACP_INUSE_AccessParameters (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MAC_DACMACP_INUSE_AccessParameters* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "MAC_DACMACP_INUSE_AccessParameters".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MAC_DACMACP_INUSE_AccessParameters (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MAC_DACMACP_INUSE_AccessParameters* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MAC_DACMACP_INUSE_AccessParameters (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MAC_DACMACP_INUSE_AccessParameters* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

int Match_c_MAC_DACMACP_INUSE_ACAck (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_MAC_DACMACP_INUSE_AccessParameters (const char* Buffer, ED_CONST ED_EXLONG BitOffset);

#ifdef __cplusplus
	}
#endif
#endif

