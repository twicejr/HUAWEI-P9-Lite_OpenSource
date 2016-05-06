/*******************************************************************************
	C.S0005 include file - by Dafocus 2012
	Include this file in your ed_user.h global include.
*******************************************************************************/
#ifndef ___CS0005E_H
#define ___CS0005E_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef CSN1_ENCODE_ASSERT
#include <stdlib.h>
#include <assert.h>
#define CSN1_ENCODE_ASSERT(a) assert(a)
#endif

/* Maximum number of PILOTS - See 3.7.2.6.2.36, NUM_PILOTS field is 3 bits long */
#define CS0005_UHDM_MAX_PILOTS 7

/* Maximum number of PILOT_INCLs - See 3.7.2.6.2.36: there is one PILOT_INCL per SCH, i.e. MAX_SCH * MAX_PILOTS (NUM_SCH field is 5 bits long) */
#define CS0005_UHDM_MAX_PILOT_INCLS ((CS0005_UHDM_MAX_PILOTS)*31)

/* Maximum number of PILOTs in f-dsch CFSRQM (6 bits field) */
#define CS0005_CFSRQM_MAX_PILOTS 64

/* Maximum number of SCCL_INDEX in f-dsch ESCAM (4 bits field) */
#define CS0005_ESCAM_MAX_SCCL_INDEX 16

/* Maximum number of FSCH_ID in f-csch BSPM (7 bits field) */
#define CS0005_BSPM_MAX_FSCH_ID 128

/* Maximum number of exported user tags */
#define CS0005_USER_TAGS        24

/* Runtime data for CSN.1 operations */

typedef struct {
	/* QUAL_INFO_TYPE - used for internal communication */
	int n_QUAL_INFO_TYPE;
	
	/* Exported user tags */
	int userTag [CS0005_USER_TAGS];

	/* Exported user tags present */
	int userTagPresent [CS0005_USER_TAGS];

	#ifdef NOCSN_DEBUG
	/* Check unwanted nesting */
	int userTagBusy [CS0005_USER_TAGS];
	#endif

	union {
	/* Runtime data for f-dsch UHDM */
	struct {
		/* NUM_SCH per each PILOT */
		unsigned char NUM_SCHs [CS0005_UHDM_MAX_PILOTS];
		
		/* Map of bits - PILOT_INCL per SCH per PILOT */
		unsigned char PILOT_INCLs [(CS0005_UHDM_MAX_PILOT_INCLS + 7)/8];
		
		/* Pilot number counter */
		int pilotCounter;
		
		/* Pilot-incl counter */
		int pilotInclCounter;

	} UHDM;

	/* Runtime data for f-dsch CFSRQM */
	struct {
		/* Map of bits - PILOT_INCL per SCH per PILOT */
		unsigned char CF_SRCH_OFFSET_INCLs [(CS0005_CFSRQM_MAX_PILOTS + 7)/8];

		/* Pilot number counter */
		int pilotCounter;
		
	} CFSRQM;

	/* Runtime data for f-dsch ESCAM */
	struct {
		/* For every SCCL_INDEX, store the related NUM_SUP_SHO+1 */
		unsigned char NUM_SUP_SHOs [CS0005_ESCAM_MAX_SCCL_INDEX];
		
		/* Count the sum of all NUM_SUP_SHO+1 */
		int GLOB_NUM_SUP_SHOs;
		
	} ESCAM;

	/* Runtime data for f-csch BSPM */
	struct {
		/* Counts the FSCH_ID while filling the arrays before. */
		unsigned FSCH_ID;
	
		/* For every FSCH_ID, store the related TDM_STRUCTURE_IND (1 bit packed) */
		unsigned char TDM_STRUCTURE_INDs [(CS0005_BSPM_MAX_FSCH_ID + 7)/8];
		
		/* For every FSCH_ID, store the related FSCH_OUTERCODE_INCL (1 bit packed) */
		unsigned char FSCH_OUTERCODE_INCLs [(CS0005_BSPM_MAX_FSCH_ID + 7)/8];

		/* For every FSCH_ID, store the related TDM_SUPER_PERIOD_MASK_LEN (2 bits packed) */
		unsigned char TDM_SUPER_PERIOD_MASK_LENs [((CS0005_BSPM_MAX_FSCH_ID * 2) + 7)/8];

		/* For every FSCH_ID, store the related TDM_MEGA_PERIOD_MASK_LEN (2 bits packed) */
		unsigned char TDM_MEGA_PERIOD_MASK_LENs [((CS0005_BSPM_MAX_FSCH_ID * 2) + 7)/8];

		/* For every FSCH_ID, store the related FSCH_OUTERCODE_RATE (3 bits packed) */
		unsigned char FSCH_OUTERCODE_RATEs [((CS0005_BSPM_MAX_FSCH_ID * 2) + 7)/8];
		
	} BSPM;
	
	} messageSpecific;	
} CS0005_RuntimeData;

typedef struct CS0005E_Details {
	unsigned n_MSG_TAG;
	unsigned n_P_REV_IN_USEs;
	unsigned n_AUTH_MODE;
	
	/* Used by 2.7.3.4 Mobile Station Reject Order */
	/* Specify: */
	#define RORDCH_AUTO        0 /* Assume 'true' to every channel check, as it did on Revs <= 17850  */
	#define RORDCH_ACCESS      1 /* Order is sent on the Access Channel or the Enhanced Access Channel */
	#define RORDCH_REVERSE     2 /* Order is sent on the Reverse Traffic Channel */
	unsigned n_R_ORDERS_CHANNEL;

	/* Set it to 0=NONE, 1=CMEA or 2=ECMEA according to required encryption mode. */
	/* See chapter C.S0005 2.3.12.2 "Signaling Message Encryption" for more details */
	int n_ENCRYPT_MODE;
	
	/* Set to 1 if encryption is required by the service option standard governing use of the Data Burst Message. */
	/* See C.S0005 2.3.12.2 for details. */
	int n_DBM_REQUIRES_ENCRYPTION;
	
	/* Encryption Sequence count (see C.S0005 2.3.12.2) */
	int n_ES_COUNT;
	
	/* Number of bits used in last decode - Valid even in case of decoding failure */
	unsigned decodedBitsCount;
	
	/* Highest decoded bit number - Valid even in case of decoding failure */
	unsigned highestDecodedBit;
	
	/* Runtime data */
	CS0005_RuntimeData runtime;

} CS0005E_Details;

/* Given a EXT_CH_IND (see table 2.7.1.3.2.4-11) returns a bitmap of the values above */
extern unsigned CalcEXT_CH_IND (int EXT_CH_IND);

/* Given a value, it returns the number of bits set to 1 */
extern unsigned CalcNoOfActiveBits (int value);


#define CSN1C_USER_CONTEXT_DATA CS0005E_Details p_CS0005E_Details; CS0005_RuntimeData CS0005_runtime;
#define P_REV_IN_USEs (pp_CS0005E_Details->n_P_REV_IN_USEs)
#define R_ORDERS_CHANNEL (pp_CS0005E_Details->n_R_ORDERS_CHANNEL)
#define AUTH_MODE (pp_CS0005E_Details->n_AUTH_MODE)
#define CSN1C_CS0005E_SETUP_CONTEXT CSN1C_CONTEXT_PTR->p_CS0005E_Details = *(pp_CS0005E_Details); decodedBitsCount = &((CS0005E_Details*)pp_CS0005E_Details)->decodedBitsCount;
#define CS0005_ENCRYPT_MODE (pp_CS0005E_Details->n_ENCRYPT_MODE)
#define CS0005_ES_COUNT (pp_CS0005E_Details->n_ES_COUNT)
#define CS0005_DBM_REQUIRES_ENCRYPTION (pp_CS0005E_Details->n_DBM_REQUIRES_ENCRYPTION)
#define CS0005_QUAL_INFO_TYPE (pp_CS0005E_Details->runtime.n_QUAL_INFO_TYPE)

#ifdef ENCODIX_CS0005
#define ED_SET_DECODE_BITS(n) (pp_CS0005E_Details->decodedBitsCount = ((unsigned)(n)))
#define ED_SET_HIGHEST_DECODE_BIT(n) (pp_CS0005E_Details->highestDecodedBit = ((unsigned)(n)))
#define ED_GET_HIGHEST_DECODE_BIT (pp_CS0005E_Details->highestDecodedBit)
#endif

#ifndef SS0053_ENCRYPTION_FUNC
	/* Set this macro to the function that will be used to do the S.S0053 CMEA/ECMEA */
	/* encryption and decryption. */
	/* Parameters: */
	/* encrypt           - 0=decrypt 1=encrypt */
	/* buffer            - memory area to be encrypted */
	/* offsetInBits      - position in bits where the area to be encrypted begins (0=first bit) */
	/* lengthInOctets    - number of octets that have to be encrypted (always >= 2) */
	/* ENCRYPT_MODE      - whatever set in the "n_ENCRYPT_MODE" parameter (1=CMEA, 2=ECMEA) */
	/* DATA_TYPE         - used by ECMEA, set as specified in C.S0005 2.3.12.2 */
	/* SYNC0             - used by ECMEA, set as specified in C.S0005 2.3.12.2 (called SYNC[0]) */
	/* SYNC1             - used by ECMEA, set as specified in C.S0005 2.3.12.2 (called SYNC[1]) */
	/* void SS0053_ENCRYPTION_FUNC (int encrypt, void* buffer, unsigned offsetInBits, unsigned lengthInOctets, int ENCRYPT_MODE, int DATA_TYPE, int SYNC0, int SYNC1); */
#error SS0053_ENCRYPTION_FUNC not defined
#endif

#define F_CPCCH  0x0001
#define F_DCCH   0x0002
#define F_FCH    0x0004
#define F_PDCH   0x0008
#define R_DCCH   0x0010
#define R_FCH    0x0020
#define R_PDCH   0x0040

/*------------------------------------------------------------------------------
	Calculates the encryption len in octets according to
	C.S0005 2.3.12.2 "Signaling Message Encryption"
------------------------------------------------------------------------------*/
extern int CS0005_CalcEncryptBytes (int numOfBits);

#ifndef SS0053_ENCRYPTION_FUNC_CALL
#define SS0053_ENCRYPTION_FUNC_CALL(encrypt,buffer,offsetInBits,lengthInOctets,ENCRYPT_MODE,DATA_TYPE,SYNC0,SYNC1) SS0053_ENCRYPTION_FUNC ((int)(encrypt), buffer, (unsigned)(offsetInBits), (unsigned)(lengthInOctets), (int)(ENCRYPT_MODE), (int)(DATA_TYPE), (int)(SYNC0), (int)(SYNC1))
#endif

#define ED_ENCODE_CUSTOM_PARAMETER , pp_CS0005E_Details
#define ED_DECODE_CUSTOM_PARAMETER , pp_CS0005E_Details


#ifdef __cplusplus
}
#endif

#endif
