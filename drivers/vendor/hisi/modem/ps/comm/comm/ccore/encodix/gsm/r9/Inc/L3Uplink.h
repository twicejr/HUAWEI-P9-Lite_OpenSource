/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.83
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __L3Uplink_h
#define __L3Uplink_h
#include "ed_lib.h"
#include "ed_c.h"
#include "ed_user.h"
#include "endec_configs.h"


#ifdef __cplusplus
	extern "C" {
#endif

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "ASSIGNMENT_COMPLETE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_ASSIGNMENT_COMPLETE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_ASSIGNMENT_COMPLETE* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "ASSIGNMENT_COMPLETE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_ASSIGNMENT_COMPLETE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_ASSIGNMENT_COMPLETE* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "ASSIGNMENT_FAILURE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_ASSIGNMENT_FAILURE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_ASSIGNMENT_FAILURE* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "ASSIGNMENT_FAILURE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_ASSIGNMENT_FAILURE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_ASSIGNMENT_FAILURE* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CHANNEL_MODE_MODIFY_ACKNOWLEDGE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CHANNEL_MODE_MODIFY_ACKNOWLEDGE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CIPHERING_MODE_COMPLETE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_CIPHERING_MODE_COMPLETE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CIPHERING_MODE_COMPLETE* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CIPHERING_MODE_COMPLETE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_CIPHERING_MODE_COMPLETE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CIPHERING_MODE_COMPLETE* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CLASSMARK_CHANGE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_CLASSMARK_CHANGE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CLASSMARK_CHANGE* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CLASSMARK_CHANGE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_CLASSMARK_CHANGE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CLASSMARK_CHANGE* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "GPRS_SUSPENSION_REQUEST".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_GPRS_SUSPENSION_REQUEST (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_GPRS_SUSPENSION_REQUEST* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "GPRS_SUSPENSION_REQUEST".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_GPRS_SUSPENSION_REQUEST (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_GPRS_SUSPENSION_REQUEST* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "HANDOVER_COMPLETE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_HANDOVER_COMPLETE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_HANDOVER_COMPLETE* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "HANDOVER_COMPLETE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_HANDOVER_COMPLETE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_HANDOVER_COMPLETE* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "HANDOVER_FAILURE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_HANDOVER_FAILURE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_HANDOVER_FAILURE* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "HANDOVER_FAILURE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_HANDOVER_FAILURE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_HANDOVER_FAILURE* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MEASUREMENT_REPORT".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_MEASUREMENT_REPORT (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_MEASUREMENT_REPORT* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "MEASUREMENT_REPORT".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_MEASUREMENT_REPORT (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_MEASUREMENT_REPORT* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PAGING_RESPONSE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_PAGING_RESPONSE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_PAGING_RESPONSE* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PAGING_RESPONSE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_PAGING_RESPONSE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_PAGING_RESPONSE* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RR_INITIALISATION_REQUEST".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_RR_INITIALISATION_REQUEST (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_RR_INITIALISATION_REQUEST* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RR_INITIALISATION_REQUEST".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_RR_INITIALISATION_REQUEST (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_RR_INITIALISATION_REQUEST* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EXTENDED_MEASUREMENT_REPORT".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_EXTENDED_MEASUREMENT_REPORT (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_EXTENDED_MEASUREMENT_REPORT* ED_CONST Source);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EXTENDED_MEASUREMENT_REPORT".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_EXTENDED_MEASUREMENT_REPORT (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_EXTENDED_MEASUREMENT_REPORT* ED_CONST Source);

int Match_c_ASSIGNMENT_COMPLETE (const char* Buffer, ED_CONST long BitOffset);
int Match_c_ASSIGNMENT_FAILURE (const char* Buffer, ED_CONST long BitOffset);
int Match_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE (const char* Buffer, ED_CONST long BitOffset);
int Match_c_CIPHERING_MODE_COMPLETE (const char* Buffer, ED_CONST long BitOffset);
int Match_c_CLASSMARK_CHANGE (const char* Buffer, ED_CONST long BitOffset);
int Match_c_GPRS_SUSPENSION_REQUEST (const char* Buffer, ED_CONST long BitOffset);
int Match_c_HANDOVER_COMPLETE (const char* Buffer, ED_CONST long BitOffset);
int Match_c_HANDOVER_FAILURE (const char* Buffer, ED_CONST long BitOffset);
int Match_c_MEASUREMENT_REPORT (const char* Buffer, ED_CONST long BitOffset);
int Match_c_PAGING_RESPONSE (const char* Buffer, ED_CONST long BitOffset);
int Match_c_RR_INITIALISATION_REQUEST (const char* Buffer, ED_CONST long BitOffset);
int Match_c_EXTENDED_MEASUREMENT_REPORT (const char* Buffer, ED_CONST long BitOffset);

#ifdef __cplusplus
	};
#endif
#endif

