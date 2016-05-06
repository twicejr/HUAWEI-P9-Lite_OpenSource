/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __EMFPKA_RLP_INUSE_cs0063_h
#define __EMFPKA_RLP_INUSE_cs0063_h
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
	Encoding/decoding functions for "EMFPKA_RLP_INUSE_ResetTxIndication".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_ResetTxIndication (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ResetTxIndication* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_ResetTxIndication (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ResetTxIndication* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EMFPKA_RLP_INUSE_ResetTxIndication".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EMFPKA_RLP_INUSE_ResetTxIndication (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ResetTxIndication* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EMFPKA_RLP_INUSE_ResetTxIndication (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ResetTxIndication* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EMFPKA_RLP_INUSE_ResetRxIndication".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_ResetRxIndication (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ResetRxIndication* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_ResetRxIndication (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ResetRxIndication* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EMFPKA_RLP_INUSE_ResetRxIndication".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EMFPKA_RLP_INUSE_ResetRxIndication (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ResetRxIndication* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EMFPKA_RLP_INUSE_ResetRxIndication (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ResetRxIndication* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EMFPKA_RLP_INUSE_ResetTxIndicationAck".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ResetTxIndicationAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ResetTxIndicationAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EMFPKA_RLP_INUSE_ResetTxIndicationAck".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ResetTxIndicationAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ResetTxIndicationAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EMFPKA_RLP_INUSE_ResetTxComplete".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_ResetTxComplete (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ResetTxComplete* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_ResetTxComplete (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ResetTxComplete* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EMFPKA_RLP_INUSE_ResetTxComplete".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EMFPKA_RLP_INUSE_ResetTxComplete (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ResetTxComplete* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EMFPKA_RLP_INUSE_ResetTxComplete (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ResetTxComplete* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EMFPKA_RLP_INUSE_ResetRxComplete".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_ResetRxComplete (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ResetRxComplete* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_ResetRxComplete (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ResetRxComplete* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EMFPKA_RLP_INUSE_ResetRxComplete".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EMFPKA_RLP_INUSE_ResetRxComplete (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ResetRxComplete* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EMFPKA_RLP_INUSE_ResetRxComplete (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ResetRxComplete* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EMFPKA_RLP_INUSE_Nak".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_Nak (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_Nak* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_Nak (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_Nak* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EMFPKA_RLP_INUSE_Nak".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EMFPKA_RLP_INUSE_Nak (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_Nak* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EMFPKA_RLP_INUSE_Nak (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_Nak* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EMFPKA_RLP_INUSE_ReservationOnRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_ReservationOnRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ReservationOnRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_ReservationOnRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ReservationOnRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EMFPKA_RLP_INUSE_ReservationOnRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EMFPKA_RLP_INUSE_ReservationOnRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ReservationOnRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EMFPKA_RLP_INUSE_ReservationOnRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ReservationOnRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EMFPKA_RLP_INUSE_ReservationOffRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_ReservationOffRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ReservationOffRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_ReservationOffRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ReservationOffRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EMFPKA_RLP_INUSE_ReservationOffRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EMFPKA_RLP_INUSE_ReservationOffRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ReservationOffRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EMFPKA_RLP_INUSE_ReservationOffRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ReservationOffRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EMFPKA_RLP_INUSE_ReservationAccept".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_ReservationAccept (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ReservationAccept* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_ReservationAccept (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ReservationAccept* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EMFPKA_RLP_INUSE_ReservationAccept".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EMFPKA_RLP_INUSE_ReservationAccept (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ReservationAccept* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EMFPKA_RLP_INUSE_ReservationAccept (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ReservationAccept* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EMFPKA_RLP_INUSE_ReservationReject".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_ReservationReject (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ReservationReject* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_ReservationReject (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ReservationReject* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EMFPKA_RLP_INUSE_ReservationReject".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EMFPKA_RLP_INUSE_ReservationReject (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ReservationReject* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EMFPKA_RLP_INUSE_ReservationReject (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ReservationReject* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EMFPKA_RLP_INUSE_RevReservationOn".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_RevReservationOn (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_RevReservationOn* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_RevReservationOn (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_RevReservationOn* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EMFPKA_RLP_INUSE_RevReservationOn".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EMFPKA_RLP_INUSE_RevReservationOn (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_RevReservationOn* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EMFPKA_RLP_INUSE_RevReservationOn (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_RevReservationOn* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EMFPKA_RLP_INUSE_RevReservationOff".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_RevReservationOff (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_RevReservationOff* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_RevReservationOff (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_RevReservationOff* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EMFPKA_RLP_INUSE_RevReservationOff".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EMFPKA_RLP_INUSE_RevReservationOff (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_RevReservationOff* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EMFPKA_RLP_INUSE_RevReservationOff (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_RevReservationOff* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EMFPKA_RLP_INUSE_FwdReservationOff".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_FwdReservationOff (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_FwdReservationOff* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_FwdReservationOff (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_FwdReservationOff* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EMFPKA_RLP_INUSE_FwdReservationOff".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EMFPKA_RLP_INUSE_FwdReservationOff (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_FwdReservationOff* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EMFPKA_RLP_INUSE_FwdReservationOff (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_FwdReservationOff* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EMFPKA_RLP_INUSE_FwdReservationOn".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_FwdReservationOn (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_FwdReservationOn* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_FwdReservationOn (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_FwdReservationOn* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EMFPKA_RLP_INUSE_FwdReservationOn".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EMFPKA_RLP_INUSE_FwdReservationOn (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_FwdReservationOn* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EMFPKA_RLP_INUSE_FwdReservationOn (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_FwdReservationOn* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EMFPKA_RLP_INUSE_FwdReservationAck".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_FwdReservationAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_FwdReservationAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_FwdReservationAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_FwdReservationAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EMFPKA_RLP_INUSE_FwdReservationAck".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EMFPKA_RLP_INUSE_FwdReservationAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_FwdReservationAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EMFPKA_RLP_INUSE_FwdReservationAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_FwdReservationAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EMFPKA_RLP_INUSE_AttributeUpdateRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_AttributeUpdateRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_AttributeUpdateRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EMFPKA_RLP_INUSE_AttributeUpdateRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_AttributeUpdateRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_AttributeUpdateRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EMFPKA_RLP_INUSE_AttributeUpdateAccept".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_AttributeUpdateAccept* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_AttributeUpdateAccept* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EMFPKA_RLP_INUSE_AttributeUpdateAccept".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_AttributeUpdateAccept* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_AttributeUpdateAccept* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EMFPKA_RLP_INUSE_AttributeUpdateReject".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_AttributeUpdateReject (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_AttributeUpdateReject* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_AttributeUpdateReject (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_AttributeUpdateReject* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EMFPKA_RLP_INUSE_AttributeUpdateReject".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EMFPKA_RLP_INUSE_AttributeUpdateReject (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_AttributeUpdateReject* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EMFPKA_RLP_INUSE_AttributeUpdateReject (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_AttributeUpdateReject* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

int Match_c_EMFPKA_RLP_INUSE_ResetTxIndication (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_EMFPKA_RLP_INUSE_ResetRxIndication (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_EMFPKA_RLP_INUSE_ResetTxComplete (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_EMFPKA_RLP_INUSE_ResetRxComplete (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_EMFPKA_RLP_INUSE_Nak (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_EMFPKA_RLP_INUSE_ReservationOnRequest (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_EMFPKA_RLP_INUSE_ReservationOffRequest (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_EMFPKA_RLP_INUSE_ReservationAccept (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_EMFPKA_RLP_INUSE_ReservationReject (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_EMFPKA_RLP_INUSE_RevReservationOn (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_EMFPKA_RLP_INUSE_RevReservationOff (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_EMFPKA_RLP_INUSE_FwdReservationOff (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_EMFPKA_RLP_INUSE_FwdReservationOn (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_EMFPKA_RLP_INUSE_FwdReservationAck (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_EMFPKA_RLP_INUSE_AttributeUpdateReject (const char* Buffer, ED_CONST ED_EXLONG BitOffset);

#ifdef __cplusplus
	}
#endif
#endif

