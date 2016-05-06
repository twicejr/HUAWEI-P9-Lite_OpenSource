/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.83
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __PLENDownlink_h
#define __PLENDownlink_h
#include "ed_lib.h"
#include "ed_c.h"
#include "ed_user.h"
#include "endec_configs.h"


#ifdef __cplusplus
	extern "C" {
#endif

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "IMMEDIATE_ASSIGNMENT".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_IMMEDIATE_ASSIGNMENT (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_IMMEDIATE_ASSIGNMENT* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "IMMEDIATE_ASSIGNMENT".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_IMMEDIATE_ASSIGNMENT (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_IMMEDIATE_ASSIGNMENT* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "IMMEDIATE_ASSIGNMENT_EXTENDED".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_IMMEDIATE_ASSIGNMENT_EXTENDED (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_IMMEDIATE_ASSIGNMENT_EXTENDED* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "IMMEDIATE_ASSIGNMENT_EXTENDED".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_IMMEDIATE_ASSIGNMENT_EXTENDED (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_IMMEDIATE_ASSIGNMENT_EXTENDED* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "IMMEDIATE_ASSIGNMENT_REJECT".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_IMMEDIATE_ASSIGNMENT_REJECT (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_IMMEDIATE_ASSIGNMENT_REJECT* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "IMMEDIATE_ASSIGNMENT_REJECT".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_IMMEDIATE_ASSIGNMENT_REJECT (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_IMMEDIATE_ASSIGNMENT_REJECT* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PAGING_REQUEST_TYPE_1".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_PAGING_REQUEST_TYPE_1 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PAGING_REQUEST_TYPE_1* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PAGING_REQUEST_TYPE_1".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_PAGING_REQUEST_TYPE_1 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PAGING_REQUEST_TYPE_1* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PAGING_REQUEST_TYPE_2".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_PAGING_REQUEST_TYPE_2 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PAGING_REQUEST_TYPE_2* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PAGING_REQUEST_TYPE_2".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_PAGING_REQUEST_TYPE_2 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PAGING_REQUEST_TYPE_2* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PAGING_REQUEST_TYPE_3".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_PAGING_REQUEST_TYPE_3 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PAGING_REQUEST_TYPE_3* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PAGING_REQUEST_TYPE_3".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_PAGING_REQUEST_TYPE_3 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PAGING_REQUEST_TYPE_3* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_1".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_1 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_1* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_1".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_1 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_1* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_2".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_2 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_2* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_2".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_2* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_2BIS".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_2BIS (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_2BIS* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_2BIS".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2BIS (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_2BIS* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_2TER".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_2TER (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_2TER* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_2TER".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2TER (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_2TER* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_2QUATER".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_2QUATER (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_2QUATER* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_2QUATER".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2QUATER (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_2QUATER* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_2N".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_2N (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_2N* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_2N".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2N (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_2N* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_3".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_3 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_3* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_3".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_3 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_3* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_4".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_4 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_4* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_4".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_4 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_4* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_5".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_5 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_5* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_5".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_5 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_5* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_5BIS".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_5BIS (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_5BIS* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_5BIS".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_5BIS (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_5BIS* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_5TER".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_5TER (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_5TER* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_5TER".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_5TER (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_5TER* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_6".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_6 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_6* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_6".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_6 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_6* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_7".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_7 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_7* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_7".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_7 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_7* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_8".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_8 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_8* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_8".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_8 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_8* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_9".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_9 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_9* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_9".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_9 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_9* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_13".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_13 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_13* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_13".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_13 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_13* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EXTENDED_MEASUREMENT_ORDER".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_EXTENDED_MEASUREMENT_ORDER (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_EXTENDED_MEASUREMENT_ORDER* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EXTENDED_MEASUREMENT_ORDER".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_EXTENDED_MEASUREMENT_ORDER (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_EXTENDED_MEASUREMENT_ORDER* ED_CONST Destin, long Length);

int Match_c_IMMEDIATE_ASSIGNMENT (const char* Buffer, ED_CONST long BitOffset);
int Match_c_IMMEDIATE_ASSIGNMENT_EXTENDED (const char* Buffer, ED_CONST long BitOffset);
int Match_c_IMMEDIATE_ASSIGNMENT_REJECT (const char* Buffer, ED_CONST long BitOffset);
int Match_c_PAGING_REQUEST_TYPE_1 (const char* Buffer, ED_CONST long BitOffset);
int Match_c_PAGING_REQUEST_TYPE_2 (const char* Buffer, ED_CONST long BitOffset);
int Match_c_PAGING_REQUEST_TYPE_3 (const char* Buffer, ED_CONST long BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_1 (const char* Buffer, ED_CONST long BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_2 (const char* Buffer, ED_CONST long BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_2BIS (const char* Buffer, ED_CONST long BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_2TER (const char* Buffer, ED_CONST long BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_2QUATER (const char* Buffer, ED_CONST long BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_2N (const char* Buffer, ED_CONST long BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_3 (const char* Buffer, ED_CONST long BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_4 (const char* Buffer, ED_CONST long BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_5 (const char* Buffer, ED_CONST long BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_5BIS (const char* Buffer, ED_CONST long BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_5TER (const char* Buffer, ED_CONST long BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_6 (const char* Buffer, ED_CONST long BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_7 (const char* Buffer, ED_CONST long BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_8 (const char* Buffer, ED_CONST long BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_9 (const char* Buffer, ED_CONST long BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_13 (const char* Buffer, ED_CONST long BitOffset);
int Match_c_EXTENDED_MEASUREMENT_ORDER (const char* Buffer, ED_CONST long BitOffset);

#ifdef __cplusplus
	};
#endif
#endif

