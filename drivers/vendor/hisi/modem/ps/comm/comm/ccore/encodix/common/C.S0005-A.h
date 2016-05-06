/*******************************************************************************
	C.S0005-A include file - by Dafocus 2012
	Include this file in your ed_user.h global include.
*******************************************************************************/
#ifndef ___CS0005E_H
#define ___CS0005E_H
#ifdef __cplusplus
extern "C" {
#endif

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

} CS0005E_Details;


/* Maximum number of PILOTS - See 3.7.2.6.2.36, NUM_PILOTS field is 3 bits long */
#define CS0005_UHDM_MAX_PILOTS 7

/* Maximum number of PILOT_INCLs - See 3.7.2.6.2.36: there is one PILOT_INCL per SCH, i.e. MAX_SCH * MAX_PILOTS (NUM_SCH field is 5 bits long) */
#define CS0005_UHDM_MAX_PILOT_INCLS ((CS0005_UHDM_MAX_PILOTS)*31)


/* Runtime data for CSN.1 operations */
typedef union {
	/* Data for UHDM */
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
} CS0005_RuntimeData;


/* Given a EXT_CH_IND (see table 2.7.1.3.2.4-11) returns a bitmap of the values above */
extern unsigned CalcEXT_CH_IND (unsigned EXT_CH_IND);

/* Given a value, it returns the number of bits set to 1 */
extern unsigned CalcNoOfActiveBits (unsigned value);

#define CSN1C_USER_CONTEXT_DATA CS0005E_Details p_CS0005E_Details; CS0005_RuntimeData CS0005_runtime;
#define P_REV_IN_USEs (Context->p_CS0005E_Details.n_P_REV_IN_USEs)
#define R_ORDERS_CHANNEL (Context->p_CS0005E_Details.n_R_ORDERS_CHANNEL)
#define AUTH_MODE (Context->p_CS0005E_Details.n_AUTH_MODE)
#define CSN1C_CS0005E_SETUP_CONTEXT CSN1C_CONTEXT_PTR->p_CS0005E_Details = *(pp_CS0005E_Details);

#define F_CPCCH  0x0001
#define F_DCCH   0x0002
#define F_FCH    0x0004
#define F_PDCH   0x0008
#define R_DCCH   0x0010
#define R_FCH    0x0020
#define R_PDCH   0x0040

#ifdef __cplusplus
}
#endif
#endif
