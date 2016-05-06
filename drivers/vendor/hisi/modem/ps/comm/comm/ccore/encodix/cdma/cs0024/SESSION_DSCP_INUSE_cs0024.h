/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __SESSION_DSCP_INUSE_cs0024_h
#define __SESSION_DSCP_INUSE_cs0024_h
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
	Encoding/decoding functions for "SESSION_DSCP_INUSE_ConfigurationComplete".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SESSION_DSCP_INUSE_ConfigurationComplete (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_ConfigurationComplete* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SESSION_DSCP_INUSE_ConfigurationComplete (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_ConfigurationComplete* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SESSION_DSCP_INUSE_ConfigurationComplete".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SESSION_DSCP_INUSE_ConfigurationComplete (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_ConfigurationComplete* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SESSION_DSCP_INUSE_ConfigurationComplete (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_ConfigurationComplete* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SESSION_DSCP_INUSE_ConfigurationStart".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SESSION_DSCP_INUSE_ConfigurationStart (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_ConfigurationStart* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SESSION_DSCP_INUSE_ConfigurationStart (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_ConfigurationStart* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SESSION_DSCP_INUSE_ConfigurationStart".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SESSION_DSCP_INUSE_ConfigurationStart (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_ConfigurationStart* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SESSION_DSCP_INUSE_ConfigurationStart (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_ConfigurationStart* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SESSION_DSCP_INUSE_ConfigurationRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SESSION_DSCP_INUSE_ConfigurationRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_ConfigurationRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SESSION_DSCP_INUSE_ConfigurationRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_ConfigurationRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SESSION_DSCP_INUSE_ConfigurationRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SESSION_DSCP_INUSE_ConfigurationRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_ConfigurationRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SESSION_DSCP_INUSE_ConfigurationRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_ConfigurationRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SESSION_DSCP_INUSE_ConfigurationResponse".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SESSION_DSCP_INUSE_ConfigurationResponse (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_ConfigurationResponse* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SESSION_DSCP_INUSE_ConfigurationResponse (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_ConfigurationResponse* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SESSION_DSCP_INUSE_ConfigurationResponse".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SESSION_DSCP_INUSE_ConfigurationResponse (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_ConfigurationResponse* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SESSION_DSCP_INUSE_ConfigurationResponse (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_ConfigurationResponse* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SESSION_DSCP_INUSE_SoftConfigurationComplete".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SESSION_DSCP_INUSE_SoftConfigurationComplete (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_SoftConfigurationComplete* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SESSION_DSCP_INUSE_SoftConfigurationComplete (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_SoftConfigurationComplete* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SESSION_DSCP_INUSE_SoftConfigurationComplete".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SESSION_DSCP_INUSE_SoftConfigurationComplete (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_SoftConfigurationComplete* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SESSION_DSCP_INUSE_SoftConfigurationComplete (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_SoftConfigurationComplete* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SESSION_DSCP_INUSE_LockConfiguration".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SESSION_DSCP_INUSE_LockConfiguration (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_LockConfiguration* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SESSION_DSCP_INUSE_LockConfiguration (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_LockConfiguration* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SESSION_DSCP_INUSE_LockConfiguration".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SESSION_DSCP_INUSE_LockConfiguration (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_LockConfiguration* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SESSION_DSCP_INUSE_LockConfiguration (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_LockConfiguration* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SESSION_DSCP_INUSE_LockConfigurationAck".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SESSION_DSCP_INUSE_LockConfigurationAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_LockConfigurationAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SESSION_DSCP_INUSE_LockConfigurationAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_LockConfigurationAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SESSION_DSCP_INUSE_LockConfigurationAck".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SESSION_DSCP_INUSE_LockConfigurationAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_LockConfigurationAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SESSION_DSCP_INUSE_LockConfigurationAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_LockConfigurationAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SESSION_DSCP_INUSE_UnLockConfiguration".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SESSION_DSCP_INUSE_UnLockConfiguration (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_UnLockConfiguration* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SESSION_DSCP_INUSE_UnLockConfiguration (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_UnLockConfiguration* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SESSION_DSCP_INUSE_UnLockConfiguration".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SESSION_DSCP_INUSE_UnLockConfiguration (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_UnLockConfiguration* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SESSION_DSCP_INUSE_UnLockConfiguration (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_UnLockConfiguration* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SESSION_DSCP_INUSE_UnLockConfigurationAck".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SESSION_DSCP_INUSE_UnLockConfigurationAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_UnLockConfigurationAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SESSION_DSCP_INUSE_UnLockConfigurationAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_UnLockConfigurationAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SESSION_DSCP_INUSE_UnLockConfigurationAck".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SESSION_DSCP_INUSE_UnLockConfigurationAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_UnLockConfigurationAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SESSION_DSCP_INUSE_UnLockConfigurationAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_UnLockConfigurationAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SESSION_DSCP_INUSE_DeletePersonality".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SESSION_DSCP_INUSE_DeletePersonality (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_DeletePersonality* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SESSION_DSCP_INUSE_DeletePersonality (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_DeletePersonality* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SESSION_DSCP_INUSE_DeletePersonality".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SESSION_DSCP_INUSE_DeletePersonality (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_DeletePersonality* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SESSION_DSCP_INUSE_DeletePersonality (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_DeletePersonality* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SESSION_DSCP_INUSE_DeletePersonalityAck".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SESSION_DSCP_INUSE_DeletePersonalityAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_DeletePersonalityAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SESSION_DSCP_INUSE_DeletePersonalityAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_DeletePersonalityAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SESSION_DSCP_INUSE_DeletePersonalityAck".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SESSION_DSCP_INUSE_DeletePersonalityAck (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_DeletePersonalityAck* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SESSION_DSCP_INUSE_DeletePersonalityAck (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_DeletePersonalityAck* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SESSION_DSCP_INUSE_AttributeUpdateRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SESSION_DSCP_INUSE_AttributeUpdateRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_AttributeUpdateRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SESSION_DSCP_INUSE_AttributeUpdateRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_AttributeUpdateRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SESSION_DSCP_INUSE_AttributeUpdateRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SESSION_DSCP_INUSE_AttributeUpdateRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_AttributeUpdateRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SESSION_DSCP_INUSE_AttributeUpdateRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_AttributeUpdateRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SESSION_DSCP_INUSE_AttributeUpdateAccept".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SESSION_DSCP_INUSE_AttributeUpdateAccept (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_AttributeUpdateAccept* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SESSION_DSCP_INUSE_AttributeUpdateAccept (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_AttributeUpdateAccept* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SESSION_DSCP_INUSE_AttributeUpdateAccept".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SESSION_DSCP_INUSE_AttributeUpdateAccept (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_AttributeUpdateAccept* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SESSION_DSCP_INUSE_AttributeUpdateAccept (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_AttributeUpdateAccept* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SESSION_DSCP_INUSE_AttributeUpdateReject".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SESSION_DSCP_INUSE_AttributeUpdateReject (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_AttributeUpdateReject* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SESSION_DSCP_INUSE_AttributeUpdateReject (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_AttributeUpdateReject* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SESSION_DSCP_INUSE_AttributeUpdateReject".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SESSION_DSCP_INUSE_AttributeUpdateReject (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SESSION_DSCP_INUSE_AttributeUpdateReject* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SESSION_DSCP_INUSE_AttributeUpdateReject (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SESSION_DSCP_INUSE_AttributeUpdateReject* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

int Match_c_SESSION_DSCP_INUSE_ConfigurationComplete (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SESSION_DSCP_INUSE_ConfigurationStart (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SESSION_DSCP_INUSE_ConfigurationRequest (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SESSION_DSCP_INUSE_ConfigurationResponse (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SESSION_DSCP_INUSE_SoftConfigurationComplete (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SESSION_DSCP_INUSE_LockConfiguration (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SESSION_DSCP_INUSE_LockConfigurationAck (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SESSION_DSCP_INUSE_UnLockConfiguration (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SESSION_DSCP_INUSE_UnLockConfigurationAck (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SESSION_DSCP_INUSE_DeletePersonality (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SESSION_DSCP_INUSE_DeletePersonalityAck (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SESSION_DSCP_INUSE_AttributeUpdateRequest (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SESSION_DSCP_INUSE_AttributeUpdateAccept (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SESSION_DSCP_INUSE_AttributeUpdateReject (const char* Buffer, ED_CONST ED_EXLONG BitOffset);

#ifdef __cplusplus
	}
#endif
#endif

