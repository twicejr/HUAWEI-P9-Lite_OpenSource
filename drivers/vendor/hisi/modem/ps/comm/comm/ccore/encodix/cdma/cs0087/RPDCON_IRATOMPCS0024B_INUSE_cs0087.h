/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __RPDCON_IRATOMPCS0024B_INUSE_cs0087_h
#define __RPDCON_IRATOMPCS0024B_INUSE_cs0087_h
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
	Encoding/decoding functions for "RPDCON_IRATOMPCS0024B_INUSE_QuickConfig".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RPDCON_IRATOMPCS0024B_INUSE_QuickConfig".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPDCON_IRATOMPCS0024B_INUSE_SectorParameters".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RPDCON_IRATOMPCS0024B_INUSE_SectorParameters".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

int Match_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText (const char* Buffer, ED_CONST ED_EXLONG BitOffset);

#ifdef __cplusplus
	}
#endif
#endif

