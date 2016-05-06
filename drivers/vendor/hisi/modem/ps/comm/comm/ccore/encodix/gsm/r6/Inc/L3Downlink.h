/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.83
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __L3Downlink_h
#define __L3Downlink_h
#include "ed_lib.h"
#include "ed_c.h"
#include "ed_user.h"
#include "endec_configs.h"


#ifdef __cplusplus
	extern "C" {
#endif

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "ASSIGNMENT_COMMAND".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_ASSIGNMENT_COMMAND (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_ASSIGNMENT_COMMAND* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "ASSIGNMENT_COMMAND".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_ASSIGNMENT_COMMAND (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_ASSIGNMENT_COMMAND* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CHANNEL_MODE_MODIFY".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_CHANNEL_MODE_MODIFY (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CHANNEL_MODE_MODIFY* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CHANNEL_MODE_MODIFY".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_CHANNEL_MODE_MODIFY (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CHANNEL_MODE_MODIFY* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CHANNEL_RELEASE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_CHANNEL_RELEASE (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CHANNEL_RELEASE* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CHANNEL_RELEASE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_CHANNEL_RELEASE (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CHANNEL_RELEASE* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CIPHERING_MODE_COMMAND".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_CIPHERING_MODE_COMMAND (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CIPHERING_MODE_COMMAND* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CIPHERING_MODE_COMMAND".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_CIPHERING_MODE_COMMAND (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CIPHERING_MODE_COMMAND* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CLASSMARK_ENQUIRY".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_CLASSMARK_ENQUIRY (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CLASSMARK_ENQUIRY* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CLASSMARK_ENQUIRY".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_CLASSMARK_ENQUIRY (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CLASSMARK_ENQUIRY* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FREQUENCY_REDEFINITION".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_FREQUENCY_REDEFINITION (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_FREQUENCY_REDEFINITION* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "FREQUENCY_REDEFINITION".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_FREQUENCY_REDEFINITION (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_FREQUENCY_REDEFINITION* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "HANDOVER_COMMAND".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_HANDOVER_COMMAND (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_HANDOVER_COMMAND* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "HANDOVER_COMMAND".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_HANDOVER_COMMAND (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_HANDOVER_COMMAND* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PHYSICAL_INFORMATION".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_PHYSICAL_INFORMATION (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PHYSICAL_INFORMATION* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PHYSICAL_INFORMATION".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_PHYSICAL_INFORMATION (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PHYSICAL_INFORMATION* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RR_STATUS".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_RR_STATUS (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_RR_STATUS* ED_CONST Source);

long DECODE_c_RR_STATUS (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_RR_STATUS* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RR_STATUS".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_RR_STATUS (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_RR_STATUS* ED_CONST Source);

long DECODE_BODY_c_RR_STATUS (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_RR_STATUS* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "APPLICATION_INFORMATION".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_APPLICATION_INFORMATION (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_APPLICATION_INFORMATION* ED_CONST Source);

long DECODE_c_APPLICATION_INFORMATION (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_APPLICATION_INFORMATION* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "APPLICATION_INFORMATION".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_BODY_c_APPLICATION_INFORMATION (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_APPLICATION_INFORMATION* ED_CONST Source);

long DECODE_BODY_c_APPLICATION_INFORMATION (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_APPLICATION_INFORMATION* ED_CONST Destin, long Length);

int Match_c_ASSIGNMENT_COMMAND (const char* Buffer, ED_CONST long BitOffset);
int Match_c_CHANNEL_MODE_MODIFY (const char* Buffer, ED_CONST long BitOffset);
int Match_c_CHANNEL_RELEASE (const char* Buffer, ED_CONST long BitOffset);
int Match_c_CIPHERING_MODE_COMMAND (const char* Buffer, ED_CONST long BitOffset);
int Match_c_CLASSMARK_ENQUIRY (const char* Buffer, ED_CONST long BitOffset);
int Match_c_FREQUENCY_REDEFINITION (const char* Buffer, ED_CONST long BitOffset);
int Match_c_HANDOVER_COMMAND (const char* Buffer, ED_CONST long BitOffset);
int Match_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND (const char* Buffer, ED_CONST long BitOffset);
int Match_c_PHYSICAL_INFORMATION (const char* Buffer, ED_CONST long BitOffset);
int Match_c_RR_STATUS (const char* Buffer, ED_CONST long BitOffset);
int Match_c_APPLICATION_INFORMATION (const char* Buffer, ED_CONST long BitOffset);

#ifdef __cplusplus
	};
#endif
#endif

