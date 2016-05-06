/*******************************************************************************
	C.S0004-A include file - by Dafocus 2012
	Include this file in your ed_user.h global include.
*******************************************************************************/
#ifndef ___CS0004E_H
#define ___CS0004E_H
#include <assert.h>
#ifdef __cplusplus
extern "C" {
#endif

#define CS0004_USER_TAGS 16

typedef struct {
	/* Protocol revision in use */
	unsigned n_P_REV_IN_USEs;

	/* Mobile protocol in use */
	unsigned n_MOB_P_REV;
	
	/* Channel - see 2.1.1.5.1.2 */
	unsigned n_CHANNEL;
	#define CS0004E_CHANNEL_Reverse_Common_Control 0x0001 /* on r-csch */
	#define CS0004E_CHANNEL_Enhanced_Access        0x0002 /* on r-csch */
	#define CS0004E_CHANNEL_Access                 0x0003 /* on r-csch */
	#define CS0004E_CHANNEL_Forward_Common_Control 0x0004 /* on f-csch */
	#define CS0004E_CHANNEL_Broadcast              0x0005 /* on f-csch */
	#define CS0004E_CHANNEL_Paging                 0x0006 /* on f-csch */
	#define CS0004E_CHANNEL_Sync                   0x0007 /* on f-csch */
	
	/* Used internally - PDU start offset */
	int n_PDU_START_OFFSET; 
	
	/* Used internally - Exported user tags */
	int userTag [CS0004_USER_TAGS];

	/* Used internally - Exported user tags present */
	int userTagPresent [CS0004_USER_TAGS];
	
	/* Number of bits used in last decode - Valid even in case of decoding failure */
	unsigned decodedBitsCount;
	
	/* Highest decoded bit number - Valid even in case of decoding failure */
	unsigned highestDecodedBit;
	
} CS0004E_Details;

#define P_REV_IN_USE_NOCSN_04 (pp_CS0004E_Details->n_P_REV_IN_USEs)
#define P_CHANNEL_NOCSN_04 (pp_CS0004E_Details->n_CHANNEL)
#define MOB_P_REV_NOCSN_04 (pp_CS0004E_Details->n_MOB_P_REV)

#ifdef ENCODIX_CS0004
#define ED_SET_DECODE_BITS(n) (pp_CS0004E_Details->decodedBitsCount = ((unsigned)(n)))
#define ED_SET_HIGHEST_DECODE_BIT(n) (pp_CS0004E_Details->highestDecodedBit = ((unsigned)(n)))
#define ED_GET_HIGHEST_DECODE_BIT (pp_CS0004E_Details->highestDecodedBit)
#endif

/*
	f-csch PDU building rules
----------------------------------------------------------------
      Message Type Fields                  Section 3.1.2.3.1.1.1
[A]   GPM Common Fields                    Section 3.1.2.3.1.2.1
[A]   Zero or more occurrences of the Page Record
[1]   One or more occurrences of the following record:
[2]   ARQ Fields                           Section 3.1.2.1.1.1
[3]   Addressing Fields                    Section 3.1.2.2.1.3.1
[4]   Message Integrity Fields             Section 3.1.2.5.1
[5]   Extended-Encryption Fields           Section 3.1.2.3.1.3.1
[6]   RESERVED_1                           1-bit field set to ,,0
[6]   ADD_RECORD_LEN                       8-bit field set to the number of octets in the SDU
[7]   SDU                                  [5]
[B]   Universal Page Block                 Section 3.1.2.3.2.4.2.1
[C]   UPM_SEGMENT_SEQ                      Section 3.1.2.3.1.6.1
[D]   Segment of the Universal Page Block  Section 3.1.2.3.2.4.2.1
[8]   PDU_PADDING                          Section 3.1.2.3.1.4.1
[9]   MACI                                 Section 3.1.2.3.1.8.1
*/
#define CS0004_F_CSCH_1 0x0001
#define CS0004_F_CSCH_2 0x0002
#define CS0004_F_CSCH_3 0x0004
#define CS0004_F_CSCH_4 0x0008
#define CS0004_F_CSCH_5 0x0010
#define CS0004_F_CSCH_6 0x0020
#define CS0004_F_CSCH_7 0x0040
#define CS0004_F_CSCH_8 0x0080
#define CS0004_F_CSCH_9 0x0100
#define CS0004_F_CSCH_A 0x0200
#define CS0004_F_CSCH_B 0x0400
#define CS0004_F_CSCH_C 0x0800
#define CS0004_F_CSCH_D 0x1000
#define CS0004_F_CSCH_E 0x2000

#define CS0004_F_CSCH_PDU_GROUP (CS0004_F_CSCH_2|CS0004_F_CSCH_3|CS0004_F_CSCH_4|CS0004_F_CSCH_5|CS0004_F_CSCH_6|CS0004_F_CSCH_7|CS0004_F_CSCH_8|CS0004_F_CSCH_9)

/* Recognition function for f-csch PDUs. Returns a combination of CS0004_F_CSCH_x flags */
/* telling which entries are expected. This returns settings up to and including */
/* Extended-Encryption Fields. After that, call CS0004E_f_csch_PDU_calculator_2 to */
/* obtain further details. */
extern int CS0004E_f_csch_PDU_calculator_1 (int CHANNEL, int PD, int MSGID);

/* Recognition function for f-csch PDUs, phase 2. Return value must be or-ed with the return */
/* value of 'CS0004E_f_csch_PDU_calculator_1' */
extern int CS0004E_f_csch_PDU_calculator_2 (int CHANNEL, int PD, int MSGID, int ENC_FIELDS_INCL, int SDU_ENCRYPT_MODE);

/* Calculates the size in bits of the given message, if known. Otherwise, it returns */
/* the estimated value */
extern int CS0004E_f_csch_SDU_size (int MSGID, unsigned const char* Buffer, int Offset, int AlternativeSize);

/* Calculates the size in bits of the given R-CSCH SDU; returns always >=0 */
extern int CS0004E_r_csch_CalcSDUSize (const char* Buffer, long BitOffset, long Length, unsigned par_P_REV_IN_USE, unsigned par_MSG_TAG);

/* Calculates the size in bits of the given F-CSCH SDU; returns always >=0 */
extern int CS0004E_f_csch_CalcSDUSize (const char* Buffer, long BitOffset, long Length, unsigned par_P_REV_IN_USE, unsigned par_MSG_TAG);

/* Encodes the padding to a full octet. Returns CurrOfs */
extern int CS0004E_PDU_Padding_Encode (char* Buffer, int CurrOfs, const CS0004E_Details* pp_CS0004E_Details);

/* Decodes the padding to a full octet. Returns CurrOfs */
extern int CS0004E_PDU_Padding_Decode (int CurrOfs, int MaxOffset, const CS0004E_Details* pp_CS0004E_Details);

/* Encodes the padding to a full octet plus two bits. Returns CurrOfs */
extern int CS0004E_PDU_Padding_plus_2_Encode (char* Buffer, int CurrOfs, const CS0004E_Details* pp_CS0004E_Details);

/* Decodes the padding to a full octet plus two bits. Returns CurrOfs */
extern int CS0004E_PDU_Padding_plus_2_Decode (int CurrOfs, int MaxOffset, const CS0004E_Details* pp_CS0004E_Details);

#ifdef __cplusplus
}
#endif
#endif