/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __MLMFPA_FCP_INUSE_cs0063_h
#define __MLMFPA_FCP_INUSE_cs0063_h
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
	Encoding/decoding functions for "MLMFPA_FCP_INUSE_XonRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_FCP_INUSE_XonRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_FCP_INUSE_XonRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_FCP_INUSE_XonRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_FCP_INUSE_XonRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "MLMFPA_FCP_INUSE_XonRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MLMFPA_FCP_INUSE_XonRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_FCP_INUSE_XonRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MLMFPA_FCP_INUSE_XonRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_FCP_INUSE_XonRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MLMFPA_FCP_INUSE_XonResponse".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_FCP_INUSE_XonResponse (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_FCP_INUSE_XonResponse* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_FCP_INUSE_XonResponse (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_FCP_INUSE_XonResponse* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "MLMFPA_FCP_INUSE_XonResponse".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MLMFPA_FCP_INUSE_XonResponse (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_FCP_INUSE_XonResponse* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MLMFPA_FCP_INUSE_XonResponse (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_FCP_INUSE_XonResponse* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MLMFPA_FCP_INUSE_XoffRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_FCP_INUSE_XoffRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_FCP_INUSE_XoffRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_FCP_INUSE_XoffRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_FCP_INUSE_XoffRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "MLMFPA_FCP_INUSE_XoffRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MLMFPA_FCP_INUSE_XoffRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_FCP_INUSE_XoffRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MLMFPA_FCP_INUSE_XoffRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_FCP_INUSE_XoffRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MLMFPA_FCP_INUSE_XoffResponse".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_FCP_INUSE_XoffResponse (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_FCP_INUSE_XoffResponse* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_FCP_INUSE_XoffResponse (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_FCP_INUSE_XoffResponse* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "MLMFPA_FCP_INUSE_XoffResponse".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MLMFPA_FCP_INUSE_XoffResponse (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_FCP_INUSE_XoffResponse* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MLMFPA_FCP_INUSE_XoffResponse (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_FCP_INUSE_XoffResponse* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MLMFPA_FCP_INUSE_DataReady".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_FCP_INUSE_DataReady (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_FCP_INUSE_DataReady* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_FCP_INUSE_DataReady (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_FCP_INUSE_DataReady* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "MLMFPA_FCP_INUSE_DataReady".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MLMFPA_FCP_INUSE_DataReady (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_FCP_INUSE_DataReady* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MLMFPA_FCP_INUSE_DataReady (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_FCP_INUSE_DataReady* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MLMFPA_FCP_INUSE_DataReadyAck".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_FCP_INUSE_DataReadyAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_FCP_INUSE_DataReadyAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_FCP_INUSE_DataReadyAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_FCP_INUSE_DataReadyAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "MLMFPA_FCP_INUSE_DataReadyAck".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MLMFPA_FCP_INUSE_DataReadyAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_FCP_INUSE_DataReadyAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MLMFPA_FCP_INUSE_DataReadyAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_FCP_INUSE_DataReadyAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MLMFPA_FCP_INUSE_RestartNetworkInterface".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_FCP_INUSE_RestartNetworkInterface (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_FCP_INUSE_RestartNetworkInterface* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_FCP_INUSE_RestartNetworkInterface (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_FCP_INUSE_RestartNetworkInterface* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "MLMFPA_FCP_INUSE_RestartNetworkInterface".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MLMFPA_FCP_INUSE_RestartNetworkInterface (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_FCP_INUSE_RestartNetworkInterface* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MLMFPA_FCP_INUSE_RestartNetworkInterface (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_FCP_INUSE_RestartNetworkInterface* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

int Match_c_MLMFPA_FCP_INUSE_XonRequest (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_MLMFPA_FCP_INUSE_XonResponse (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_MLMFPA_FCP_INUSE_XoffRequest (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_MLMFPA_FCP_INUSE_XoffResponse (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_MLMFPA_FCP_INUSE_DataReady (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_MLMFPA_FCP_INUSE_DataReadyAck (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_MLMFPA_FCP_INUSE_RestartNetworkInterface (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck (const char* Buffer, ED_CONST ED_EXLONG BitOffset);

#ifdef __cplusplus
	}
#endif
#endif

