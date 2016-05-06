#include "ed_user.h"
#include "C.S0005.h"

/*------------------------------------------------------------------------------
	Calculates the encryption len in octets according to
	C.S0005 2.3.12.2 "Signaling Message Encryption"
------------------------------------------------------------------------------*/

/* x00309227,2015/06/06,加密算法函数实现，更新编解码包时保留 */
/*=================================================================================================
	DUMMY ENCRYPTION FUNCTION

	Parameters:

	encrypt           - 0=decrypt 1=encrypt
	buffer            - memory area to be encrypted
	offsetInBits      - position in bits where the area to be encrypted begins (0=first bit)
	lengthInOctets    - number of octets that have to be encrypted (always >= 2)
	ENCRYPT_MODE      - whatever set in the "n_ENCRYPT_MODE" parameter (1=CMEA, 2=ECMEA)
	DATA_TYPE         - used by ECMEA, set as specified in C.S0005 2.3.12.2
	SYNC0             - used by ECMEA, set as specified in C.S0005 2.3.12.2 (called SYNC[0])
	SYNC1             - used by ECMEA, set as specified in C.S0005 2.3.12.2 (called SYNC[1])

	NOTE: THIS FUNCTION DOES NOT IMPLEMENT REAL S.S0058 ENCRYPTION!
	IT SIMPLY DOES AN XOR!
=================================================================================================*/
void SS0053_ENCRYPTION_FUNC_dummy (int encrypt, void* buffer, unsigned offsetInBits, unsigned lengthInOctets, int ENCRYPT_MODE, int DATA_TYPE, int SYNC0, int SYNC1)
{
	unsigned i;
	ED_WARNING_REMOVER (encrypt);
	ED_WARNING_REMOVER (ENCRYPT_MODE);
	ED_WARNING_REMOVER (DATA_TYPE);
	ED_WARNING_REMOVER (SYNC0);
	ED_WARNING_REMOVER (SYNC1);
	assert (lengthInOctets >= 2);
	for (i=0; i<lengthInOctets; i++) {
		unsigned n = (unsigned)EDBitsToInt (buffer, (long)offsetInBits, 8);
		n ^= n;
		EDIntToBits (buffer, (long)offsetInBits, (int)n, 8);
		offsetInBits += 8;
	}
}

int CS0005_CalcEncryptBytes (int numOfBits) {
	if (numOfBits == 0) return 0;
	if (numOfBits <= 16) return 2;
	return (int)(((unsigned)numOfBits) >> 3) + ((((unsigned)numOfBits) & 7) != 0 ? 1 : 0);
}

/* Given a EXT_CH_IND (see table 2.7.1.3.2.4-11) returns a bitmap of the values above */
unsigned CalcEXT_CH_IND (int EXT_CH_IND)
{
	switch (EXT_CH_IND) {
		case 1: return (F_PDCH | F_CPCCH | R_FCH);
		case 2: return (F_PDCH | F_CPCCH | R_DCCH);
		case 3: return (F_PDCH | F_FCH | R_FCH);
		case 4: return (F_PDCH | F_DCCH | R_DCCH);
		case 5: return (F_PDCH | F_FCH | R_FCH | R_DCCH);
		case 6: return (F_PDCH | F_FCH | R_FCH | F_DCCH | R_DCCH);
		case 8: return (F_PDCH | R_PDCH | F_CPCCH);
		case 9: return (F_PDCH | R_PDCH | F_CPCCH | R_FCH);
		case 10: return (F_PDCH | R_PDCH | F_CPCCH | R_DCCH);
		case 11: return (F_PDCH | R_PDCH | F_FCH | R_FCH);
		case 12: return (F_PDCH | R_PDCH | F_DCCH | R_DCCH);
		case 13: return (F_PDCH | R_PDCH | F_FCH | R_FCH | R_DCCH);
		case 14: return (F_PDCH | R_PDCH | F_FCH | R_FCH | F_DCCH | R_DCCH);
		case 15: return (F_PDCH | F_FCH | F_DCCH | R_DCCH);
		case 16: return (F_PDCH | F_CPCCH | F_DCCH | R_DCCH);
		case 17: return (F_PDCH | F_CPCCH | F_FCH | F_DCCH | R_DCCH);
		case 18: return (F_PDCH | F_CPCCH | F_FCH | R_FCH | F_DCCH | R_DCCH);
		case 19: return (F_PDCH | R_PDCH | F_FCH | F_DCCH | R_DCCH);
		case 20: return (F_PDCH | R_PDCH | F_CPCCH | F_DCCH | R_DCCH);
		case 21: return (F_PDCH | R_PDCH | F_CPCCH | F_FCH | F_DCCH | R_DCCH);
		case 22: return (F_PDCH | R_PDCH | F_CPCCH | F_FCH | R_FCH | F_DCCH | R_DCCH);
		default:;
	}
	return 0;
}

/* Given a value, it returns the number of bits set to 1 */
unsigned CalcNoOfActiveBits (int value)
{
	unsigned noOfActiveBits = 0;
	unsigned uValue = (unsigned)value;
	while (uValue) {
		if (uValue & 1) noOfActiveBits++;
		uValue >>= 1;
	}
	return noOfActiveBits;
}
