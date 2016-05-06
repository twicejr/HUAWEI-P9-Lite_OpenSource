/*******************************************************************************
	C.S0005-E include file - by Dafocus 2012
	Include this file in your ed_user.h global include.
*******************************************************************************/
#ifndef ___CS0005E_H
#define ___CS0005E_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	unsigned n_MSG_TAG;
	unsigned n_P_REV_IN_USEs;
	unsigned n_AUTH_MODE;
} CS0005E_Details;

/* Given a EXT_CH_IND (see table 2.7.1.3.2.4-11) returns a bitmap of the values above */
extern unsigned CalcEXT_CH_IND (unsigned EXT_CH_IND);

/* Given a value, it returns the number of bits set to 1 */
extern unsigned CalcNoOfActiveBits (unsigned value);

#define CSN1C_USER_CONTEXT_DATA CS0005E_Details p_CS0005E_Details;
#define P_REV_IN_USEs (Context->p_CS0005E_Details.n_P_REV_IN_USEs)
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
