/*******************************************************************************
	C.S0004-E include file - by Dafocus 2012
	Include this file in your ed_user.h global include.
*******************************************************************************/
/*lint -e506 */
#include "ed_lib.h"
#include "C.S0004.h"
#include "ed_c_cs0005.h"
#include "UserDefinedDataTypes_cs0005.h"

/* Recognition function for f-csch PDUs. Returns a combination of CS0004_F_CSCH_x flags */
/* telling which entries are expected. This returns settings up to and including */
/* Extended-Encryption Fields. After that, call CS0004E_f_csch_PDU_calculator_2 to */
/* obtain further details. */
int CS0004E_f_csch_PDU_calculator_1 (int CHANNEL, int PD, int MSGID)
{

	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.4.2.2.1/013
		MESSAGE: Universal Page Message
	----------------------------------------------------------------------*/
	if ((MSGID==35)) {
		return CS0004_F_CSCH_B | CS0004_F_CSCH_E;
	}

	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.4.2.2.1/014
		MESSAGE: Universal Page Message/First segment
	----------------------------------------------------------------------*/
	if ((MSGID==36)) {
		return CS0004_F_CSCH_B | CS0004_F_CSCH_D;
	}

	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.4.2.2.1/015
		MESSAGE: Universal Page Message/Middle segment
	----------------------------------------------------------------------*/
	if ((MSGID==37)) {
		return CS0004_F_CSCH_B | CS0004_F_CSCH_C | CS0004_F_CSCH_D;
	}

	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.4.2.2.1/016
		MESSAGE: Universal Page Message/Last segment
	----------------------------------------------------------------------*/
	if ((MSGID==38)) {
		return CS0004_F_CSCH_B | CS0004_F_CSCH_C | CS0004_F_CSCH_D | CS0004_F_CSCH_E;
	}

	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.1/001
		CHANNELS: Sync Channel, Primary Broadcast Control Channel
	----------------------------------------------------------------------*/
	if ((CHANNEL==CS0004E_CHANNEL_Broadcast || CHANNEL==CS0004E_CHANNEL_Sync)) {
		return CS0004_F_CSCH_7 /*| CS0004_F_CSCH_8*/;
	}

	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.2/002
		CHANNEL: Paging Channel
		MESSAGES: Order Message, Channel Assignment Message
	----------------------------------------------------------------------*/
	if ((CHANNEL==CS0004E_CHANNEL_Paging) && (MSGID==7 || MSGID==8)) {
		return CS0004_F_CSCH_1 | CS0004_F_CSCH_2 | CS0004_F_CSCH_3 | CS0004_F_CSCH_7 | CS0004_F_CSCH_8;
	}

	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.2/003
		PD: 00
		CHANNEL: Paging Channel
		MESSAGE: Extended Channel Assignment Message
	----------------------------------------------------------------------*/
	if ((PD == 0) && (CHANNEL==CS0004E_CHANNEL_Paging) && (MSGID==21)) {
		return CS0004_F_CSCH_1 | CS0004_F_CSCH_2 | CS0004_F_CSCH_3 | CS0004_F_CSCH_6 | CS0004_F_CSCH_7 | CS0004_F_CSCH_8;
	}

	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.2/003
		PD: 01
		CHANNEL: Paging Channel
		MESSAGE: Extended Channel Assignment Message
	----------------------------------------------------------------------*/
	if ((PD == 1) && (CHANNEL==CS0004E_CHANNEL_Paging) && (MSGID==21)) {
		return CS0004_F_CSCH_1 | CS0004_F_CSCH_2 | CS0004_F_CSCH_3 | CS0004_F_CSCH_5 | CS0004_F_CSCH_6 | CS0004_F_CSCH_7 | CS0004_F_CSCH_8;
	}

	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.2/003
		PD: 10
		CHANNEL: Paging Channel
		MESSAGE: Extended Channel Assignment Message
	----------------------------------------------------------------------*/
	if ((PD == 2) && (CHANNEL==CS0004E_CHANNEL_Paging) && (MSGID==21)) {
		return CS0004_F_CSCH_1 | CS0004_F_CSCH_2 | CS0004_F_CSCH_3 | CS0004_F_CSCH_4 | CS0004_F_CSCH_5 | CS0004_F_CSCH_6 | CS0004_F_CSCH_7 | CS0004_F_CSCH_8 | CS0004_F_CSCH_9;
	}

	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.2/004
		PD: 00
		CHANNEL: Paging Channel
		MESSAGE: General Page Message
	----------------------------------------------------------------------*/
	if ((PD == 0) && (CHANNEL==CS0004E_CHANNEL_Paging) && (MSGID==17)) {
		return CS0004_F_CSCH_A | CS0004_F_CSCH_8;
	}

	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.2/005
		PD: 00
		CHANNEL: Paging Channel
		MESSAGES: BROADCAST_SET
	----------------------------------------------------------------------*/
	if ((PD == 0) && (CHANNEL==CS0004E_CHANNEL_Paging) && (MSGID==1 || MSGID==2 || MSGID==3 || MSGID==4 || MSGID==13 || MSGID==14 || MSGID==18 || MSGID==22 || MSGID==23 || MSGID==24 || MSGID==26 || MSGID==27 || MSGID==29 || MSGID==30 || MSGID==31 || MSGID==32 || MSGID==33 || MSGID==40 || MSGID==45 || MSGID==47 || MSGID==48 || MSGID==49 || MSGID==50 || MSGID==51 || MSGID==52 || MSGID==53)) {
		return CS0004_F_CSCH_7 | CS0004_F_CSCH_8;
	}

	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.2/006
		PD: 00
		CHANNEL: Paging Channel
	----------------------------------------------------------------------*/
	if ((PD == 0) && (CHANNEL==CS0004E_CHANNEL_Paging)) {
		return CS0004_F_CSCH_2 | CS0004_F_CSCH_3 | CS0004_F_CSCH_7 | CS0004_F_CSCH_8;
	}

	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.3/007
		PD: 01
		CHANNEL: Paging Channel
	----------------------------------------------------------------------*/
	if ((PD == 1) && (CHANNEL==CS0004E_CHANNEL_Paging)) {
		return CS0004_F_CSCH_2 | CS0004_F_CSCH_3 | CS0004_F_CSCH_5 | CS0004_F_CSCH_7 | CS0004_F_CSCH_8;
	}

	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.3/007
		PD: 10
		CHANNEL: Paging Channel
	----------------------------------------------------------------------*/
	if ((PD == 2) && (CHANNEL==CS0004E_CHANNEL_Paging)) {
		return CS0004_F_CSCH_2 | CS0004_F_CSCH_3 | CS0004_F_CSCH_4 | CS0004_F_CSCH_5 | CS0004_F_CSCH_7 | CS0004_F_CSCH_8 | CS0004_F_CSCH_9;
	}

	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.4.1/008
		PD: 00
		CHANNEL: Forward Common Control Channel
		MESSAGE: Order Message
	----------------------------------------------------------------------*/
	if ((PD == 0) && (CHANNEL==CS0004E_CHANNEL_Forward_Common_Control) && (MSGID==7)) {
		return CS0004_F_CSCH_2 | CS0004_F_CSCH_3 | CS0004_F_CSCH_5;
	}

	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.4.1/008
		PD: 10
		CHANNEL: Forward Common Control Channel
		MESSAGE: Order Message
	----------------------------------------------------------------------*/
	if ((PD == 2) && (CHANNEL==CS0004E_CHANNEL_Forward_Common_Control) && (MSGID==7)) {
		return CS0004_F_CSCH_1 | CS0004_F_CSCH_2 | CS0004_F_CSCH_3 | CS0004_F_CSCH_4 | CS0004_F_CSCH_5 | CS0004_F_CSCH_7 | CS0004_F_CSCH_8;
	}

	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.4.1/009
		PD: 00
		CHANNEL: Forward Common Control Channel
		MESSAGE: Extended Channel Assignment Message
	----------------------------------------------------------------------*/
	if ((PD == 0) && (CHANNEL==CS0004E_CHANNEL_Forward_Common_Control) && (MSGID==21)) {
		return CS0004_F_CSCH_1 | CS0004_F_CSCH_2 | CS0004_F_CSCH_3 | CS0004_F_CSCH_5 | CS0004_F_CSCH_6 | CS0004_F_CSCH_7 | CS0004_F_CSCH_8;
	}

	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.4.1/009
		PD: 10
		CHANNEL: Forward Common Control Channel
		MESSAGE: Extended Channel Assignment Message
	----------------------------------------------------------------------*/
	if ((PD == 2) && (CHANNEL==CS0004E_CHANNEL_Forward_Common_Control) && (MSGID==21)) {
		return CS0004_F_CSCH_1 | CS0004_F_CSCH_2 | CS0004_F_CSCH_3 | CS0004_F_CSCH_4 | CS0004_F_CSCH_5 | CS0004_F_CSCH_6 | CS0004_F_CSCH_7 | CS0004_F_CSCH_8 | CS0004_F_CSCH_9;
	}

	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.4.1/010
		CHANNEL: Forward Common Control Channel
		MESSAGE: General Page Message
	----------------------------------------------------------------------*/
	if ((CHANNEL==CS0004E_CHANNEL_Forward_Common_Control) && (MSGID==17)) {
		return CS0004_F_CSCH_A | CS0004_F_CSCH_8;
	}

	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.4.1/010
		CHANNEL: Forward Common Control Channel
		MESSAGE: General Page Message
	----------------------------------------------------------------------*/
	if ((CHANNEL==CS0004E_CHANNEL_Forward_Common_Control) && (MSGID==17)) {
		return CS0004_F_CSCH_A | CS0004_F_CSCH_8;
	}

	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.4.1/011
		PD: 00
		CHANNEL: Forward Common Control Channel
	----------------------------------------------------------------------*/
	if ((PD == 0) && (CHANNEL==CS0004E_CHANNEL_Forward_Common_Control)) {
		return CS0004_F_CSCH_2 | CS0004_F_CSCH_3 | CS0004_F_CSCH_5 | CS0004_F_CSCH_7 | CS0004_F_CSCH_8;
	}

	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.4.1/012
		PD: 10
		CHANNEL: Forward Common Control Channel
	----------------------------------------------------------------------*/
	if ((PD == 2) && (CHANNEL==CS0004E_CHANNEL_Forward_Common_Control)) {
		return CS0004_F_CSCH_2 | CS0004_F_CSCH_3 | CS0004_F_CSCH_4 | CS0004_F_CSCH_5 | CS0004_F_CSCH_7 | CS0004_F_CSCH_8 | CS0004_F_CSCH_9;
	}

	return 0;
}

/* Recognition function for f-csch PDUs, phase 2 */
int CS0004E_f_csch_PDU_calculator_2 (int CHANNEL, int PD, int MSGID, int ENC_FIELDS_INCL, int SDU_ENCRYPT_MODE)
{
	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.4.1/008
		PD: 00
		CHANNEL: Forward Common Control Channel
		MESSAGE: Order Message
		WITHOUT ENCRYPTION (SDU_ENCRYPT_MODE == 0)
	----------------------------------------------------------------------*/
	if ((PD == 0) && (CHANNEL==CS0004E_CHANNEL_Forward_Common_Control) && (MSGID==7) && (SDU_ENCRYPT_MODE == 0)) {
		return CS0004_F_CSCH_1 | CS0004_F_CSCH_2 | CS0004_F_CSCH_3 | CS0004_F_CSCH_5 | CS0004_F_CSCH_7 | CS0004_F_CSCH_8;
	}

	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.4.1/008
		PD: 10
		CHANNEL: Forward Common Control Channel
		MESSAGE: Order Message
		WITHOUT MESSAGE INTEGRITY PROTECTION (ENC_FIELDS_INCL == 0)
	----------------------------------------------------------------------*/
	if ((PD == 2) && (CHANNEL==CS0004E_CHANNEL_Forward_Common_Control) && (MSGID==7) && (ENC_FIELDS_INCL == 0)) {
		return CS0004_F_CSCH_1 | CS0004_F_CSCH_2 | CS0004_F_CSCH_3 | CS0004_F_CSCH_4 | CS0004_F_CSCH_5 | CS0004_F_CSCH_7 | CS0004_F_CSCH_8;
	}

	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.4.1/008
		PD: 00
		CHANNEL: Forward Common Control Channel
		MESSAGE: Order Message
		WITH ENCRYPTION (SDU_ENCRYPT_MODE != 0)
		WITHOUT MESSAGE INTEGRITY PROTECTION (ENC_FIELDS_INCL == 0)
	----------------------------------------------------------------------*/
	if ((PD == 0) && (CHANNEL==CS0004E_CHANNEL_Forward_Common_Control) && (MSGID==7) && (SDU_ENCRYPT_MODE != 0) && (ENC_FIELDS_INCL == 0)) {
		return CS0004_F_CSCH_2 | CS0004_F_CSCH_3 | CS0004_F_CSCH_5 | CS0004_F_CSCH_7 | CS0004_F_CSCH_8;
	}

	/*----------------------------------------------------------------------
		CHAPTER: 3.1.2.3.2.4.1/008
		PD: 10
		CHANNEL: Forward Common Control Channel
		MESSAGE: Order Message
		WITHOUT ENCRYPTION (SDU_ENCRYPT_MODE == 0)
		WITH MESSAGE INTEGRITY PROTECTION (ENC_FIELDS_INCL != 0)
	----------------------------------------------------------------------*/
	if ((PD == 2) && (CHANNEL==CS0004E_CHANNEL_Forward_Common_Control) && (MSGID==7) && (SDU_ENCRYPT_MODE == 0) && (ENC_FIELDS_INCL != 0)) {
		return CS0004_F_CSCH_2 | CS0004_F_CSCH_3 | CS0004_F_CSCH_4 | CS0004_F_CSCH_5 | CS0004_F_CSCH_7 | CS0004_F_CSCH_8 | CS0004_F_CSCH_9;
	}

	return 0;
}

/* Calculates the size in bits of the given message, if known. Otherwise, it returns */
/* the estimated value */
int CS0004E_f_csch_SDU_size (int MSGID, const unsigned char* Buffer, int Offset, int AlternativeSize)
{
	int octets;
	switch (MSGID) {
		/* Order Message */
		/* Contains 6 bit ORDER followed by 3 bit ADD_RECORD_LEN, telling the number of following octets */
		case 0x07: {
			octets = EDBitsToInt (Buffer, Offset+6, 3);
			return 6 + 3 + octets * 8;
		}

		/* Channel Assignment Message (C.S0005-E, 3.7.2.3.2.8) */
		/* Contains 3 bit ASSIGNE_MODE followed by 3 bit ADD_RECORD_LEN, telling the number of following octets */
		case 0x08: {
			octets = EDBitsToInt (Buffer, Offset+3, 3);
			return 3 + 3 + octets * 8;
		}
		
		/* General Page Message (C.S0005-E, 3.7.2.3.2.17) */		
		/* Contains 3 bit followed by 3 bit ADD_RECORD_LEN, telling the number of following octets */
		case 0x11: {
			octets = EDBitsToInt (Buffer, Offset+3, 3);
			return 3 + 3 + octets * 8;
		}
		/* Default */
		default:;
	}
	return AlternativeSize;
}


/* Calculates the size in bits of the given R-CSCH SDU; returns always >=0 */
int CS0004E_r_csch_CalcSDUSize (const char* Buffer, long BitOffset, long Length, unsigned par_P_REV_IN_USE, unsigned par_MSG_TAG)
{
	int ret;
	c_r_csch_mini6 tempContainer;
	CS0005E_Details p_CS0005E_Details;
	ED_WARNING_REMOVER(par_MSG_TAG);
	INIT_c_r_csch_mini6 (&tempContainer);
	memset (&p_CS0005E_Details, 0, sizeof (p_CS0005E_Details));
	p_CS0005E_Details.n_P_REV_IN_USEs = par_P_REV_IN_USE;
	p_CS0005E_Details.n_MSG_TAG = par_MSG_TAG;
	ret = DECODE_c_r_csch_mini6 (Buffer, BitOffset, &tempContainer, Length-BitOffset, &p_CS0005E_Details);
	if (ret < 0) ret = 0;
	FREE_c_r_csch_mini6 (&tempContainer);
	
	return ret;
}

/* Calculates the size in bits of the given F-CSCH SDU; returns always >=0 */
int CS0004E_f_csch_CalcSDUSize (const char* Buffer, long BitOffset, long Length, unsigned par_P_REV_IN_USE, unsigned par_MSG_TAG)
{
	int ret;
	c_f_csch_mini6 tempContainer;
	CS0005E_Details p_CS0005E_Details;
	ED_WARNING_REMOVER(par_MSG_TAG);
	INIT_c_f_csch_mini6 (&tempContainer);
	memset (&p_CS0005E_Details, 0, sizeof (p_CS0005E_Details));
	p_CS0005E_Details.n_P_REV_IN_USEs = par_P_REV_IN_USE;
	p_CS0005E_Details.n_MSG_TAG = par_MSG_TAG;
	ret = DECODE_c_f_csch_mini6 (Buffer, BitOffset, &tempContainer, Length-BitOffset, &p_CS0005E_Details);
	if (ret < 0) ret = 0;
	FREE_c_f_csch_mini6 (&tempContainer);
	
	return ret;
}

/* Executes the padding to a full octet. Returns CurrOfs */
int CS0004E_PDU_Padding_Encode (char* Buffer, int CurrOfs, const CS0004E_Details* pp_CS0004E_Details)
{
	int PaddingBits = ((8 - ((CurrOfs - pp_CS0004E_Details->n_PDU_START_OFFSET) & 7)) & 7);
	assert (PaddingBits >= 0);
	assert (PaddingBits < 8);
	if (PaddingBits > 0) {
		EDIntToBits (Buffer, CurrOfs, 0, PaddingBits);
	}
	return CurrOfs + PaddingBits;
}

/* Decodes the padding to a full octet. Returns CurrOfs */
int CS0004E_PDU_Padding_Decode (int CurrOfs, int MaxOffset, const CS0004E_Details* pp_CS0004E_Details)
{
	int PaddingBits = ((8 - ((CurrOfs - pp_CS0004E_Details->n_PDU_START_OFFSET) & 7)) & 7);
	int Ret = 0;
	assert (PaddingBits >= 0);
	assert (PaddingBits < 8);
	Ret = CurrOfs + PaddingBits;
	if (Ret > MaxOffset) Ret = MaxOffset;
	return Ret;
}

/* Executes the padding to a full octet plus two bits. Returns CurrOfs */
int CS0004E_PDU_Padding_plus_2_Encode (char* Buffer, int CurrOfs, const CS0004E_Details* pp_CS0004E_Details)
{
	int PaddingBits = ((8 - ((CurrOfs - pp_CS0004E_Details->n_PDU_START_OFFSET - 2) & 7)) & 7);
	assert (PaddingBits >= 0);
	assert (PaddingBits < 8);
	if (PaddingBits > 0) {
		EDIntToBits (Buffer, CurrOfs, 0, PaddingBits);
	}
	return CurrOfs + PaddingBits;
}

/* Decodes the padding to a full octet plus two bits. Returns CurrOfs */
int CS0004E_PDU_Padding_plus_2_Decode (int CurrOfs, int MaxOffset, const CS0004E_Details* pp_CS0004E_Details)
{
	int PaddingBits = ((8 - ((CurrOfs - pp_CS0004E_Details->n_PDU_START_OFFSET - 2) & 7)) & 7);
	int Ret = 0;
	assert (PaddingBits >= 0);
	assert (PaddingBits < 8);
	Ret = CurrOfs + PaddingBits;
	if (Ret > MaxOffset) Ret = MaxOffset;
	return Ret;
}
