/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __RPDCON_IRATSAP_INUSE_cs0087_h
#define __RPDCON_IRATSAP_INUSE_cs0087_h
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
	Encoding/decoding functions for "RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPDCON_IRATSAP_INUSE_AlternateLinkPageReq".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RPDCON_IRATSAP_INUSE_AlternateLinkPageReq".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

int Match_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete (const char* Buffer, ED_CONST ED_EXLONG BitOffset);

#ifdef __cplusplus
	}
#endif
#endif

