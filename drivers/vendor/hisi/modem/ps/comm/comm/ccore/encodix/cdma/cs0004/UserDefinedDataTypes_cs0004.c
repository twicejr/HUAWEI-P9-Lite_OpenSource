/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/
/*lint -e959 -e530 -e774 -e572 -e778 -e525 -e539 -e701 -e123 -e438 -e119 -e506 -e529 -e550 -e666 -e713 -e719 -e730 -e734 -e744 -e801 -e801 -e813 -e830 -e40 -e10 -e52 -e63 -e115 -e409 -e118 -e49 -e718 -e746 -e737 -e760 -e830 */
#define ENCODIX_CS0004

#include "UserDefinedDataTypes_cs0004.h"
#include "ed_c_known_ie_cs0004.h"
#include "ed_tlv.h"
#if ED_COMMON_CRC != 0x328E3625 && ED_VERSION != 10152 && ED_VERSION != 10153
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.154
#endif


#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_PDU (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_PDU* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME FCSCH_PDU */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_FCSCH_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int cnt;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* Reset exported tag 27 'ADDR_LEN' */
		pp_CS0004E_Details->userTagPresent[0] = 0;
		pp_CS0004E_Details->userTag[0] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[0], "FCSCH_PDU", "ADDR_LEN");
		pp_CS0004E_Details->userTagBusy[0] = 1;
#endif
		/* Reset exported tag 28 'MSG_ID' */
		pp_CS0004E_Details->userTagPresent[2] = 0;
		pp_CS0004E_Details->userTag[2] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[2], "FCSCH_PDU", "MSG_ID");
		pp_CS0004E_Details->userTagBusy[2] = 1;
#endif
		/* Reset exported tag 33 'PD' */
		pp_CS0004E_Details->userTagPresent[1] = 0;
		pp_CS0004E_Details->userTag[1] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[1], "FCSCH_PDU", "PD");
		pp_CS0004E_Details->userTagBusy[1] = 1;
#endif
		/* Mark the beginning of the PDU, to allow correct padding */
		pp_CS0004E_Details->n_PDU_START_OFFSET = CurrOfs;
		
		/* C.S0004 3.1.2.3.1.1 */
		PUSH_INT (Source->PD, 2);
		/* Set the exported tag */
		pp_CS0004E_Details->userTagPresent[1] = 1;
		pp_CS0004E_Details->userTag[1] = (int)Source->PD;
		PUSH_INT (Source->MSG_ID, 6);
		/* Set the exported tag */
		pp_CS0004E_Details->userTagPresent[2] = 1;
		pp_CS0004E_Details->userTag[2] = (int)Source->MSG_ID;
		/* Multiple SDUs are used by: */
		/* 3.1.2.3.2.2 PDUs transmitted on the Paging Channel which do not contain the Extended-Encryption Fields (i.e. P_REV_IN_USE < 7): */
		/*   == PDUs carrying the Order Message or the Channel Assignment Message (Table 3.1.2.3.1.1.2-1) */
		/*   == PDUs carrying the Extended Channel Assignment Message (Table 3.1.2.3.1.1.2-1) */
		for (cnt=0; cnt<Source->SDUs.items; cnt++) {
			CurrOfs += ENCODE_c_FCSCH_PDU_SDUs_data (Buffer, CurrOfs, Source->SDUs.data [cnt], pp_CS0004E_Details);
		}
		/* 3.1.2.3.1.4.1 */
		/* Some PDUs require padding to be done before their final MACI field, supported in P_REV >= 9. */
		/* For this reason, we specify padding here for P_REV < 7 to support multiple SDUs. */
		/* Higher revisions contain Extended-Encryption fields so they require a single SDU.  */
		/* In this case, padding is specified within the message itself. */
		if (P_REV_IN_USE_NOCSN_04 < 7) CurrOfs = CS0004E_PDU_Padding_plus_2_Encode (Buffer, CurrOfs, pp_CS0004E_Details);
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[0], "FCSCH_PDU", "ADDR_LEN");
		pp_CS0004E_Details->userTagBusy[0] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[2], "FCSCH_PDU", "MSG_ID");
		pp_CS0004E_Details->userTagBusy[2] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[1], "FCSCH_PDU", "PD");
		pp_CS0004E_Details->userTagBusy[1] = 0;
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_PDU (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_PDU* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME FCSCH_PDU */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_FCSCH_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int cnt;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		/* Reset exported tag 27 'ADDR_LEN' */
		pp_CS0004E_Details->userTagPresent[0] = 0;
		pp_CS0004E_Details->userTag[0] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[0], "FCSCH_PDU", "ADDR_LEN");
		pp_CS0004E_Details->userTagBusy[0] = 1;
#endif
		/* Reset exported tag 28 'MSG_ID' */
		pp_CS0004E_Details->userTagPresent[2] = 0;
		pp_CS0004E_Details->userTag[2] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[2], "FCSCH_PDU", "MSG_ID");
		pp_CS0004E_Details->userTagBusy[2] = 1;
#endif
		/* Reset exported tag 33 'PD' */
		pp_CS0004E_Details->userTagPresent[1] = 0;
		pp_CS0004E_Details->userTag[1] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[1], "FCSCH_PDU", "PD");
		pp_CS0004E_Details->userTagBusy[1] = 1;
#endif
		/* Mark the beginning of the PDU, to allow correct padding */
		pp_CS0004E_Details->n_PDU_START_OFFSET = CurrOfs;
		
		/* C.S0004 3.1.2.3.1.1 */
		bts = 2;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->PD___LOCATOR), CurrOfs, bts);
			Destin->PD = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			/* Set the exported tag */
			pp_CS0004E_Details->userTagPresent[1] = 1;
			pp_CS0004E_Details->userTag[1] = (int)Destin->PD;
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 6;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->MSG_ID___LOCATOR), CurrOfs, bts);
			Destin->MSG_ID = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			/* Set the exported tag */
			pp_CS0004E_Details->userTagPresent[2] = 1;
			pp_CS0004E_Details->userTag[2] = (int)Destin->MSG_ID;
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* Multiple SDUs are used by: */
		/* 3.1.2.3.2.2 PDUs transmitted on the Paging Channel which do not contain the Extended-Encryption Fields (i.e. P_REV_IN_USE < 7): */
		/*   == PDUs carrying the Order Message or the Channel Assignment Message (Table 3.1.2.3.1.1.2-1) */
		/*   == PDUs carrying the Extended Channel Assignment Message (Table 3.1.2.3.1.1.2-1) */
		/* Decode field SDUs - sequence */
		/* Decode field SDUs - infinite sequence */
		for (cnt=0; ; cnt++) {
			ADDITEMS_c_FCSCH_PDU_SDUs(&Destin->SDUs, 1);
			bts = DECODE_c_FCSCH_PDU_SDUs_data (Buffer, CurrOfs, Destin->SDUs.data [cnt], LastOfs-CurrOfs , pp_CS0004E_Details);
			if (bts < 0) {
				/* Decoding failed - Remove the unused array items */
				SETITEMS_c_FCSCH_PDU_SDUs (&Destin->SDUs, cnt);
				goto exit_0;
			}
			CurrOfs += bts;
		}
		exit_0:
		/* 3.1.2.3.1.4.1 */
		/* Some PDUs require padding to be done before their final MACI field, supported in P_REV >= 9. */
		/* For this reason, we specify padding here for P_REV < 7 to support multiple SDUs. */
		/* Higher revisions contain Extended-Encryption fields so they require a single SDU.  */
		/* In this case, padding is specified within the message itself. */
		
		if (P_REV_IN_USE_NOCSN_04 < 7) CurrOfs = CS0004E_PDU_Padding_plus_2_Decode (CurrOfs, LastOfs, pp_CS0004E_Details);
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[0], "FCSCH_PDU", "ADDR_LEN");
		pp_CS0004E_Details->userTagBusy[0] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[2], "FCSCH_PDU", "MSG_ID");
		pp_CS0004E_Details->userTagBusy[2] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[1], "FCSCH_PDU", "PD");
		pp_CS0004E_Details->userTagBusy[1] = 0;
#endif
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[0], "FCSCH_PDU", "ADDR_LEN");
		pp_CS0004E_Details->userTagBusy[0] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[2], "FCSCH_PDU", "MSG_ID");
		pp_CS0004E_Details->userTagBusy[2] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[1], "FCSCH_PDU", "PD");
		pp_CS0004E_Details->userTagBusy[1] = 0;
#endif
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_PDU_SDUs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_PDU_SDUs_data* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME FCSCH_PDU_content */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_FCSCH_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* ARQ Fields Section 3.1.2.1.1.1 */
		PUSH_INT (Source->ACK_SEQ, 3);
		PUSH_INT (Source->MSG_SEQ, 3);
		PUSH_INT (Source->ACK_REQ, 1);
		PUSH_INT (Source->VALID_ACK, 1);
		/* Addressing Fields  Section 3.1.2.2.1.3.1 */
		PUSH_INT (Source->ADDR_TYPE, 3);
		PUSH_INT (Source->ADDR_LEN, 4);
		/* Set the exported tag */
		pp_CS0004E_Details->userTagPresent[0] = 1;
		pp_CS0004E_Details->userTag[0] = (int)Source->ADDR_LEN;
		/* BEGIN OF PAD ZONE - ENCODE inclusive=0 bits=4 octet(=0)/bit(=1)=0 */
		{
			ED_EXLONG dataStartOfs0 = CurrOfs;
			int lenInBits0;
			if ((Source->ADDR_TYPE==4)) {
				/* Field 'EXT_ADDR_TYPE' is required */
				ED_ASSERT (GETPRESENT_c_FCSCH_PDU_SDUs_data_EXT_ADDR_TYPE(Source));
				PUSH_INT (Source->EXT_ADDR_TYPE, 3);
			}
			else {
				/* Field 'EXT_ADDR_TYPE' must be absent */
				ED_ASSERT (!GETPRESENT_c_FCSCH_PDU_SDUs_data_EXT_ADDR_TYPE(Source));
			}
			/* Spare bits are optional */
			if ((Source->ADDR_TYPE==4)) {
				/* Encode spare bits */
				PUSH_INT (0, 5);
			}
			/* ADDR_TYPE==b000 */
			if ((Source->ADDR_TYPE==0)) {
				/* Field 'IMSI_S' is required */
				ED_ASSERT (GETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_S(Source));
				CurrOfs += ENCODE_c_FCSCH_PDU_SDUs_data_IMSI_S (Buffer, CurrOfs, Source->IMSI_S, pp_CS0004E_Details);
			}
			else {
				/* Field 'IMSI_S' must be absent */
				ED_ASSERT (!GETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_S(Source));
			}
			/* ADDR_TYPE==b001 */
			if ((Source->ADDR_TYPE==1)) {
				/* Field 'ESN' is required */
				ED_ASSERT (GETPRESENT_c_FCSCH_PDU_SDUs_data_ESN(Source));
				CurrOfs += ENCODE_c_FCSCH_PDU_SDUs_data_ESN (Buffer, CurrOfs, Source->ESN, pp_CS0004E_Details);
			}
			else {
				/* Field 'ESN' must be absent */
				ED_ASSERT (!GETPRESENT_c_FCSCH_PDU_SDUs_data_ESN(Source));
			}
			/* ADDR_TYPE==b010 */
			if ((Source->ADDR_TYPE==2)) {
				/* Field 'IMSI' is required */
				ED_ASSERT (GETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI(Source));
				CurrOfs += ENCODE_c_FCSCH_PDU_SDUs_data_IMSI (Buffer, CurrOfs, Source->IMSI, pp_CS0004E_Details);
			}
			else {
				/* Field 'IMSI' must be absent */
				ED_ASSERT (!GETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI(Source));
			}
			/* ADDR_TYPE==b011 */
			if ((Source->ADDR_TYPE==3)) {
				/* Field 'TMSI' is required */
				ED_ASSERT (GETPRESENT_c_FCSCH_PDU_SDUs_data_TMSI(Source));
				CurrOfs += ENCODE_c_FCSCH_PDU_SDUs_data_TMSI (Buffer, CurrOfs, Source->TMSI, pp_CS0004E_Details);
			}
			else {
				/* Field 'TMSI' must be absent */
				ED_ASSERT (!GETPRESENT_c_FCSCH_PDU_SDUs_data_TMSI(Source));
			}
			/* ADDR_TYPE==b100 */
			if ((Source->ADDR_TYPE==4)) {
				/* Field 'Extended_Address' is required */
				ED_ASSERT (GETPRESENT_c_FCSCH_PDU_SDUs_data_Extended_Address(Source));
				CurrOfs += ENCODE_c_FCSCH_PDU_SDUs_data_Extended_Address (Buffer, CurrOfs, Source->Extended_Address, pp_CS0004E_Details);
			}
			else {
				/* Field 'Extended_Address' must be absent */
				ED_ASSERT (!GETPRESENT_c_FCSCH_PDU_SDUs_data_Extended_Address(Source));
			}
			/* ADDR_TYPE==b101 */
			if ((Source->ADDR_TYPE==5)) {
				/* Field 'BROADCAST' is required */
				ED_ASSERT (GETPRESENT_c_FCSCH_PDU_SDUs_data_BROADCAST(Source));
				CurrOfs += ENCODE_c_FCSCH_PDU_SDUs_data_BROADCAST (Buffer, CurrOfs, Source->BROADCAST, pp_CS0004E_Details);
			}
			else {
				/* Field 'BROADCAST' must be absent */
				ED_ASSERT (!GETPRESENT_c_FCSCH_PDU_SDUs_data_BROADCAST(Source));
			}
			/* Calculate the encoded length in octets */
			lenInBits0 = (CurrOfs-dataStartOfs0);
			
			/* Save the encoded length into the length field */
			EDIntToBits (Buffer, dataStartOfs0-4, ((lenInBits0+7)/8)-0, 4);
			
			/* Pad if required */
			if ((lenInBits0 & 0x07) != 0) {
				PUSH_INT (0, 8-(lenInBits0 & 0x07));
			}
		}
		/* END OF PAD ZONE */
		/* Message Integrity Fields - Section 3.1.2.5.1 */
		/* Available only if P_REV_IN_USE >= 9 and PD=2 */
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&((pp_CS0004E_Details->userTag[1])==2))) {
			/* Field 'MACI_INCL' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_PDU_SDUs_data_MACI_INCL(Source));
			PUSH_INT (Source->MACI_INCL, 1);
		}
		else {
			/* Field 'MACI_INCL' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_PDU_SDUs_data_MACI_INCL(Source));
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Source->MACI_INCL_Present ? Source->MACI_INCL : 0))) {
			/* Field 'SDU_KEY_ID' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_KEY_ID(Source));
			PUSH_INT (Source->SDU_KEY_ID, 2);
		}
		else {
			/* Field 'SDU_KEY_ID' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_KEY_ID(Source));
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Source->MACI_INCL_Present ? Source->MACI_INCL : 0))) {
			/* Field 'SDU_INTEGRITY_ALGO' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_INTEGRITY_ALGO(Source));
			PUSH_INT (Source->SDU_INTEGRITY_ALGO, 3);
		}
		else {
			/* Field 'SDU_INTEGRITY_ALGO' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_INTEGRITY_ALGO(Source));
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Source->MACI_INCL_Present ? Source->MACI_INCL : 0))) {
			/* Field 'SDU_SSEQ_OR_SSEQH' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_SSEQ_OR_SSEQH(Source));
			PUSH_INT (Source->SDU_SSEQ_OR_SSEQH, 1);
		}
		else {
			/* Field 'SDU_SSEQ_OR_SSEQH' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_SSEQ_OR_SSEQH(Source));
		}
		if ((((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Source->MACI_INCL_Present ? Source->MACI_INCL : 0))&&!((Source->SDU_SSEQ_OR_SSEQH_Present ? Source->SDU_SSEQ_OR_SSEQH : 0)))) {
			/* Field 'SDU_SSEQ' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_SSEQ(Source));
			PUSH_INT (Source->SDU_SSEQ, 8);
		}
		else {
			/* Field 'SDU_SSEQ' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_SSEQ(Source));
		}
		if ((((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Source->MACI_INCL_Present ? Source->MACI_INCL : 0))&&(Source->SDU_SSEQ_OR_SSEQH_Present ? Source->SDU_SSEQ_OR_SSEQH : 0))) {
			/* Field 'SDU_SSEQ_H' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_SSEQ_H(Source));
			PUSH_INT (Source->SDU_SSEQ_H, 24);
		}
		else {
			/* Field 'SDU_SSEQ_H' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_SSEQ_H(Source));
		}
		/* Extended Encryption, Section 3.1.2.3.1.3.1 */
		/* Included only if P_REV_IN_USE >= 7 and PD!=0 */
		/* See 3.1.2.3.2.3: "For PDUs transmitted on the Paging Channel when P_REV_IN_USE is greater than or equal */
		/* to  seven, the base station may include the Extended-Encryption Fields." */
		/* Chapter 3.1.2.3.1.3.2 states that a P_REV>=7 can "omit all the Extended-Encryption Fields, in which case the base station */
		/* shall use a PDU format with the PD field set to ‘00’" (AXN0016) */
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=7)&&((pp_CS0004E_Details->userTag[1])!=0))) {
			/* Field 'ENC_FIELDS_INCL' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_PDU_SDUs_data_ENC_FIELDS_INCL(Source));
			PUSH_INT (Source->ENC_FIELDS_INCL, 1);
		}
		else {
			/* Field 'ENC_FIELDS_INCL' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_PDU_SDUs_data_ENC_FIELDS_INCL(Source));
		}
		/* If ENC_FIELDS_INCL is set to '1', the base station shall include the SDU_ENCRYPT_MODE (C.S0004, 3.1.2.3.1.3.2) */
		if ((Source->ENC_FIELDS_INCL_Present ? Source->ENC_FIELDS_INCL : 0)) {
			/* Field 'SDU_ENCRYPT_MODE' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_ENCRYPT_MODE(Source));
			PUSH_INT (Source->SDU_ENCRYPT_MODE, 3);
		}
		else {
			/* Field 'SDU_ENCRYPT_MODE' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_ENCRYPT_MODE(Source));
		}
		/* If the SDU_ENCRYPT_MODE field is included and is set to '001' , the base station shall include the ENC_SEQ (C.S0004, 3.1.2.3.1.3.2) */
		if (((Source->SDU_ENCRYPT_MODE_Present ? Source->SDU_ENCRYPT_MODE : 0)==1)) {
			/* Field 'ENC_SEQ' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_PDU_SDUs_data_ENC_SEQ(Source));
			PUSH_INT (Source->ENC_SEQ, 8);
		}
		else {
			/* Field 'ENC_SEQ' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_PDU_SDUs_data_ENC_SEQ(Source));
		}
		/* --------------------------------------------------------------------- */
		/*  SDU WITH ORDM OR CAM */
		/* --------------------------------------------------------------------- */
		/* SDU containing ORDM (ID=7) */
		/* C.S0005 3.7.2.3.2.7 Order Message format is: */
		/* ORDER            6 bits */
		/* ADD_RECORD_LEN   3 bits */
		/* Order-specific   (8 * ADD_RECORD_LEN) bits */
		/* */
		/* SDU containing CAM (ID=8) */
		/* C.S0005 3.7.2.3.2.8 Channel Assignment format is: */
		/* ASSIGN_MODE      3 bits */
		/* ADD_RECORD_LEN   3 bits */
		/* Order-specific   (8 * ADD_RECORD_LEN) bits */
		{
		
		
			int length = Source->SDU.usedBits;
		
			int SDU_LENGTH = 0;
			int MSG_ID = pp_CS0004E_Details->userTag[2]/*MSG_ID*/;
			/* 0=not processed */
			/* 1=to be processed */
			/* 2=processed */
			int SDU_PROCESSED = 0;
			switch (MSG_ID) {
				/* ORDM */
				case 7: {
					if (length >= 9) {
		
		
						SDU_LENGTH = length;
						assert (EDBitsToInt (Source->SDU.value, 6, 3) * 8 + 9 == SDU_LENGTH);
		
					}
					SDU_PROCESSED = 1;
					break;
				}
				/* CAM */
				case 8: {
					if (length >= 6) {
		
		
						SDU_LENGTH = length;
						assert (EDBitsToInt (Source->SDU.value, 3, 3) * 8 + 6 == SDU_LENGTH);
		
					}
					SDU_PROCESSED = 1;
					break;
				}
			}
			if (SDU_PROCESSED) {
		
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->SDU))->usedBits == (int) (SDU_LENGTH));
		PUSH_BIN ((&(Source->SDU))->value, (&(Source->SDU))->usedBits);
		if (P_REV_IN_USE_NOCSN_04 >= 7) CurrOfs = CS0004E_PDU_Padding_plus_2_Encode (Buffer, CurrOfs, pp_CS0004E_Details);
		
		/* MACI 3.1.2.3.1.8.1 */
		if ((((SDU_LENGTH >= 0))&&(Source->MACI_INCL_Present ? Source->MACI_INCL : 0))) {
			/* Field 'MACI' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_PDU_SDUs_data_MACI(Source));
			PUSH_INT (Source->MACI, 32);
		}
			SDU_PROCESSED=2;
		}
		/* --------------------------------------------------------------------- */
		/*  SDU WITH ECAM OR MECAM */
		/* --------------------------------------------------------------------- */
		/* Try next option: ECAM (ID=21) or MECAM (ID=46) */
		if (SDU_PROCESSED==0 && (MSG_ID == 21 /*ECAM*/ || MSG_ID == 46 /*MECAM*/)) {
			SDU_PROCESSED=1; SDU_LENGTH=0;
		
		/* RESERVED_1  1-bit field set to 0 */
		/* Spare bits are optional */
		if ((SDU_PROCESSED)) {
			/* Encode spare bits */
			PUSH_INT (0, 1);
		}
		/* SDU */
		if ((SDU_PROCESSED==1)) {
			/* Field 'ADD_RECORD_LEN' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_PDU_SDUs_data_ADD_RECORD_LEN(Source));
			PUSH_INT (Source->ADD_RECORD_LEN, 8);
		}
		else {
			/* Field 'ADD_RECORD_LEN' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_PDU_SDUs_data_ADD_RECORD_LEN(Source));
		}
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->SDU))->usedBits == (int) (((SDU_PROCESSED==1)) ? ((8*(Source->ADD_RECORD_LEN_Present ? Source->ADD_RECORD_LEN : 0))) : (0)));
		PUSH_BIN ((&(Source->SDU))->value, (&(Source->SDU))->usedBits);
		if (((SDU_PROCESSED==1)&&(Source->MACI_INCL_Present ? Source->MACI_INCL : 0))) {
			/* Field 'MACI' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_PDU_SDUs_data_MACI(Source));
			PUSH_INT (Source->MACI, 32);
		}
		/* MACI 3.1.2.3.1.8.1 */
			if (P_REV_IN_USE_NOCSN_04 >= 7) CurrOfs = CS0004E_PDU_Padding_plus_2_Encode (Buffer, CurrOfs, pp_CS0004E_Details);
		
			SDU_PROCESSED=2;
		}
		/* --------------------------------------------------------------------- */
		/*  ALL OTHER SDUs */
		/* --------------------------------------------------------------------- */
		if (SDU_PROCESSED==0) {
			SDU_PROCESSED=1;
		
		
			SDU_LENGTH = ED_THIS->SDU.usedBits;
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->SDU))->usedBits == (int) (SDU_LENGTH));
		PUSH_BIN ((&(Source->SDU))->value, (&(Source->SDU))->usedBits);
		/* PADDING */
		if (P_REV_IN_USE_NOCSN_04 >= 7) CurrOfs = CS0004E_PDU_Padding_plus_2_Encode (Buffer, CurrOfs, pp_CS0004E_Details);
		
		/* MACI 3.1.2.3.1.8.1 */
		if ((Source->MACI_INCL_Present ? Source->MACI_INCL : 0)) {
			/* Field 'MACI' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_PDU_SDUs_data_MACI(Source));
			PUSH_INT (Source->MACI, 32);
		}
			SDU_PROCESSED=2;
		}
		
		}
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_PDU_SDUs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_PDU_SDUs_data* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME FCSCH_PDU_content */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_FCSCH_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		/* ARQ Fields Section 3.1.2.1.1.1 */
		bts = 3;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ACK_SEQ___LOCATOR), CurrOfs, bts);
			Destin->ACK_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 3;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->MSG_SEQ___LOCATOR), CurrOfs, bts);
			Destin->MSG_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ACK_REQ___LOCATOR), CurrOfs, bts);
			Destin->ACK_REQ = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->VALID_ACK___LOCATOR), CurrOfs, bts);
			Destin->VALID_ACK = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* Addressing Fields  Section 3.1.2.2.1.3.1 */
		bts = 3;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ADDR_TYPE___LOCATOR), CurrOfs, bts);
			Destin->ADDR_TYPE = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 4;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ADDR_LEN___LOCATOR), CurrOfs, bts);
			Destin->ADDR_LEN = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			/* Set the exported tag */
			pp_CS0004E_Details->userTagPresent[0] = 1;
			pp_CS0004E_Details->userTag[0] = (int)Destin->ADDR_LEN;
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* BEGIN OF PAD ZONE - DECODE inclusive=0 bits=4 octet(=0)/bit(=1)=0 */
		{
			/* Save the current final offset position */
			int LastOfs1 = LastOfs;
			
			/* Calculate the new final offset position */
			int NewLastOfs1 = CurrOfs +
			EDBitsToInt (Buffer, CurrOfs-4, 4) * 8;
			
			/* Temporarely set the new LastOfs value */
			LastOfs = NewLastOfs1;
			
			/* Execute the normal decoding */
			if ((Destin->ADDR_TYPE==4)) {
				SETPRESENT_c_FCSCH_PDU_SDUs_data_EXT_ADDR_TYPE(Destin, ED_TRUE);
				bts = 3;
				if (LastOfs - (int)CurrOfs < bts) {
					bts = ED_MESSAGE_TOO_SHORT;
				} 
				else {
					ED_LOCATOR_SET (&(Destin->EXT_ADDR_TYPE___LOCATOR), CurrOfs, bts);
					Destin->EXT_ADDR_TYPE = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
				}
				if (bts < 0) {
					/* If decoding failed, set the failed field to "not present" */
					SETPRESENT_c_FCSCH_PDU_SDUs_data_EXT_ADDR_TYPE(Destin, ED_FALSE);
					goto exitOnFail;
				}
				CurrOfs += bts;
			}
			/* Spare bits are optional */
			if ((Destin->ADDR_TYPE==4)) {
				/* Decode spare bit(s) */
				bts = 5;
				if (LastOfs-CurrOfs < bts) {
					bts = ED_MESSAGE_TOO_SHORT;
					goto exitOnFail;
				}
				CurrOfs += bts;
			}
			/* ADDR_TYPE==b000 */
			if ((Destin->ADDR_TYPE==0)) {
				SETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_S(Destin, ED_TRUE);
				bts = DECODE_c_FCSCH_PDU_SDUs_data_IMSI_S (Buffer, CurrOfs, Destin->IMSI_S, LastOfs-CurrOfs , pp_CS0004E_Details);
				if (bts < 0) {
					/* If decoding failed, set the failed field to "not present" */
					SETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_S(Destin, ED_FALSE);
					goto exitOnFail;
				}
				CurrOfs += bts;
			}
			/* ADDR_TYPE==b001 */
			if ((Destin->ADDR_TYPE==1)) {
				SETPRESENT_c_FCSCH_PDU_SDUs_data_ESN(Destin, ED_TRUE);
				bts = DECODE_c_FCSCH_PDU_SDUs_data_ESN (Buffer, CurrOfs, Destin->ESN, LastOfs-CurrOfs , pp_CS0004E_Details);
				if (bts < 0) {
					/* If decoding failed, set the failed field to "not present" */
					SETPRESENT_c_FCSCH_PDU_SDUs_data_ESN(Destin, ED_FALSE);
					goto exitOnFail;
				}
				CurrOfs += bts;
			}
			/* ADDR_TYPE==b010 */
			if ((Destin->ADDR_TYPE==2)) {
				SETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI(Destin, ED_TRUE);
				bts = DECODE_c_FCSCH_PDU_SDUs_data_IMSI (Buffer, CurrOfs, Destin->IMSI, LastOfs-CurrOfs , pp_CS0004E_Details);
				if (bts < 0) {
					/* If decoding failed, set the failed field to "not present" */
					SETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI(Destin, ED_FALSE);
					goto exitOnFail;
				}
				CurrOfs += bts;
			}
			/* ADDR_TYPE==b011 */
			if ((Destin->ADDR_TYPE==3)) {
				SETPRESENT_c_FCSCH_PDU_SDUs_data_TMSI(Destin, ED_TRUE);
				bts = DECODE_c_FCSCH_PDU_SDUs_data_TMSI (Buffer, CurrOfs, Destin->TMSI, LastOfs-CurrOfs , pp_CS0004E_Details);
				if (bts < 0) {
					/* If decoding failed, set the failed field to "not present" */
					SETPRESENT_c_FCSCH_PDU_SDUs_data_TMSI(Destin, ED_FALSE);
					goto exitOnFail;
				}
				CurrOfs += bts;
			}
			/* ADDR_TYPE==b100 */
			if ((Destin->ADDR_TYPE==4)) {
				SETPRESENT_c_FCSCH_PDU_SDUs_data_Extended_Address(Destin, ED_TRUE);
				bts = DECODE_c_FCSCH_PDU_SDUs_data_Extended_Address (Buffer, CurrOfs, Destin->Extended_Address, LastOfs-CurrOfs , pp_CS0004E_Details);
				if (bts < 0) {
					/* If decoding failed, set the failed field to "not present" */
					SETPRESENT_c_FCSCH_PDU_SDUs_data_Extended_Address(Destin, ED_FALSE);
					goto exitOnFail;
				}
				CurrOfs += bts;
			}
			/* ADDR_TYPE==b101 */
			if ((Destin->ADDR_TYPE==5)) {
				SETPRESENT_c_FCSCH_PDU_SDUs_data_BROADCAST(Destin, ED_TRUE);
				bts = DECODE_c_FCSCH_PDU_SDUs_data_BROADCAST (Buffer, CurrOfs, Destin->BROADCAST, LastOfs-CurrOfs , pp_CS0004E_Details);
				if (bts < 0) {
					/* If decoding failed, set the failed field to "not present" */
					SETPRESENT_c_FCSCH_PDU_SDUs_data_BROADCAST(Destin, ED_FALSE);
					goto exitOnFail;
				}
				CurrOfs += bts;
			}
			/* The inner data should never overflow the available space by design */
			ED_ASSERT (CurrOfs <= NewLastOfs1);
			
			/* If needed, skip the extra bits and align to the calculated range */
			CurrOfs = NewLastOfs1;
			
			/* If the required data is too long, signal ED_MESSAGE_TOO_SHORT */
			if (NewLastOfs1 > LastOfs1) {
				bts = ED_MESSAGE_TOO_SHORT;
				goto exitOnFail;
			}
			
			/* Set back the LastOfs variable to the stored value */
			LastOfs = LastOfs1;
		}
		/* END OF PAD ZONE */
		/* Message Integrity Fields - Section 3.1.2.5.1 */
		/* Available only if P_REV_IN_USE >= 9 and PD=2 */
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&((pp_CS0004E_Details->userTag[1])==2))) {
			SETPRESENT_c_FCSCH_PDU_SDUs_data_MACI_INCL(Destin, ED_TRUE);
			bts = 1;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->MACI_INCL___LOCATOR), CurrOfs, bts);
				Destin->MACI_INCL = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_PDU_SDUs_data_MACI_INCL(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Destin->MACI_INCL_Present ? Destin->MACI_INCL : 0))) {
			SETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_KEY_ID(Destin, ED_TRUE);
			bts = 2;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_KEY_ID___LOCATOR), CurrOfs, bts);
				Destin->SDU_KEY_ID = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_KEY_ID(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Destin->MACI_INCL_Present ? Destin->MACI_INCL : 0))) {
			SETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_INTEGRITY_ALGO(Destin, ED_TRUE);
			bts = 3;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_INTEGRITY_ALGO___LOCATOR), CurrOfs, bts);
				Destin->SDU_INTEGRITY_ALGO = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_INTEGRITY_ALGO(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Destin->MACI_INCL_Present ? Destin->MACI_INCL : 0))) {
			SETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_SSEQ_OR_SSEQH(Destin, ED_TRUE);
			bts = 1;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_SSEQ_OR_SSEQH___LOCATOR), CurrOfs, bts);
				Destin->SDU_SSEQ_OR_SSEQH = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_SSEQ_OR_SSEQH(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Destin->MACI_INCL_Present ? Destin->MACI_INCL : 0))&&!((Destin->SDU_SSEQ_OR_SSEQH_Present ? Destin->SDU_SSEQ_OR_SSEQH : 0)))) {
			SETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_SSEQ(Destin, ED_TRUE);
			bts = 8;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_SSEQ___LOCATOR), CurrOfs, bts);
				Destin->SDU_SSEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_SSEQ(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Destin->MACI_INCL_Present ? Destin->MACI_INCL : 0))&&(Destin->SDU_SSEQ_OR_SSEQH_Present ? Destin->SDU_SSEQ_OR_SSEQH : 0))) {
			SETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_SSEQ_H(Destin, ED_TRUE);
			bts = 24;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_SSEQ_H___LOCATOR), CurrOfs, bts);
				Destin->SDU_SSEQ_H = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_SSEQ_H(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* Extended Encryption, Section 3.1.2.3.1.3.1 */
		/* Included only if P_REV_IN_USE >= 7 and PD!=0 */
		/* See 3.1.2.3.2.3: "For PDUs transmitted on the Paging Channel when P_REV_IN_USE is greater than or equal */
		/* to  seven, the base station may include the Extended-Encryption Fields." */
		/* Chapter 3.1.2.3.1.3.2 states that a P_REV>=7 can "omit all the Extended-Encryption Fields, in which case the base station */
		/* shall use a PDU format with the PD field set to ‘00’" (AXN0016) */
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=7)&&((pp_CS0004E_Details->userTag[1])!=0))) {
			SETPRESENT_c_FCSCH_PDU_SDUs_data_ENC_FIELDS_INCL(Destin, ED_TRUE);
			bts = 1;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->ENC_FIELDS_INCL___LOCATOR), CurrOfs, bts);
				Destin->ENC_FIELDS_INCL = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_PDU_SDUs_data_ENC_FIELDS_INCL(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* If ENC_FIELDS_INCL is set to '1', the base station shall include the SDU_ENCRYPT_MODE (C.S0004, 3.1.2.3.1.3.2) */
		if ((Destin->ENC_FIELDS_INCL_Present ? Destin->ENC_FIELDS_INCL : 0)) {
			SETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_ENCRYPT_MODE(Destin, ED_TRUE);
			bts = 3;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_ENCRYPT_MODE___LOCATOR), CurrOfs, bts);
				Destin->SDU_ENCRYPT_MODE = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_ENCRYPT_MODE(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* If the SDU_ENCRYPT_MODE field is included and is set to '001' , the base station shall include the ENC_SEQ (C.S0004, 3.1.2.3.1.3.2) */
		if (((Destin->SDU_ENCRYPT_MODE_Present ? Destin->SDU_ENCRYPT_MODE : 0)==1)) {
			SETPRESENT_c_FCSCH_PDU_SDUs_data_ENC_SEQ(Destin, ED_TRUE);
			bts = 8;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->ENC_SEQ___LOCATOR), CurrOfs, bts);
				Destin->ENC_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_PDU_SDUs_data_ENC_SEQ(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* --------------------------------------------------------------------- */
		/*  SDU WITH ORDM OR CAM */
		/* --------------------------------------------------------------------- */
		/* SDU containing ORDM (ID=7) */
		/* C.S0005 3.7.2.3.2.7 Order Message format is: */
		/* ORDER            6 bits */
		/* ADD_RECORD_LEN   3 bits */
		/* Order-specific   (8 * ADD_RECORD_LEN) bits */
		/* */
		/* SDU containing CAM (ID=8) */
		/* C.S0005 3.7.2.3.2.8 Channel Assignment format is: */
		/* ASSIGN_MODE      3 bits */
		/* ADD_RECORD_LEN   3 bits */
		/* Order-specific   (8 * ADD_RECORD_LEN) bits */
		{
		
			int length = LastOfs - CURPOS;
		
		
			int SDU_LENGTH = 0;
			int MSG_ID = pp_CS0004E_Details->userTag[2]/*MSG_ID*/;
			/* 0=not processed */
			/* 1=to be processed */
			/* 2=processed */
			int SDU_PROCESSED = 0;
			switch (MSG_ID) {
				/* ORDM */
				case 7: {
					if (length >= 9) {
		
						SDU_LENGTH = EDBitsToInt (Buffer, CurrOfs+6, 3) * 8 + 9;
		
		
					}
					SDU_PROCESSED = 1;
					break;
				}
				/* CAM */
				case 8: {
					if (length >= 6) {
		
						SDU_LENGTH = EDBitsToInt (Buffer, CurrOfs+3, 3) * 8 + 6;
		
		
					}
					SDU_PROCESSED = 1;
					break;
				}
			}
			if (SDU_PROCESSED) {
		
		bts = (SDU_LENGTH);
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->SDU___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->SDU)))->value), (unsigned)(bts), &(((&(Destin->SDU)))->usedBits));
			EDCopyBits (((&(Destin->SDU))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		
		if (P_REV_IN_USE_NOCSN_04 >= 7) CurrOfs = CS0004E_PDU_Padding_plus_2_Decode (CurrOfs, LastOfs, pp_CS0004E_Details);
		/* MACI 3.1.2.3.1.8.1 */
		if ((((SDU_LENGTH >= 0))&&(Destin->MACI_INCL_Present ? Destin->MACI_INCL : 0))) {
			SETPRESENT_c_FCSCH_PDU_SDUs_data_MACI(Destin, ED_TRUE);
			bts = 32;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->MACI___LOCATOR), CurrOfs, bts);
				Destin->MACI = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_PDU_SDUs_data_MACI(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
			SDU_PROCESSED=2;
		}
		/* --------------------------------------------------------------------- */
		/*  SDU WITH ECAM OR MECAM */
		/* --------------------------------------------------------------------- */
		/* Try next option: ECAM (ID=21) or MECAM (ID=46) */
		if (SDU_PROCESSED==0 && (MSG_ID == 21 /*ECAM*/ || MSG_ID == 46 /*MECAM*/)) {
			SDU_PROCESSED=1; SDU_LENGTH=0;
		
		/* RESERVED_1  1-bit field set to 0 */
		/* Spare bits are optional */
		if ((SDU_PROCESSED)) {
			/* Decode spare bit(s) */
			bts = 1;
			if (LastOfs-CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* SDU */
		if ((SDU_PROCESSED==1)) {
			SETPRESENT_c_FCSCH_PDU_SDUs_data_ADD_RECORD_LEN(Destin, ED_TRUE);
			bts = 8;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->ADD_RECORD_LEN___LOCATOR), CurrOfs, bts);
				Destin->ADD_RECORD_LEN = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_PDU_SDUs_data_ADD_RECORD_LEN(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		bts = (((SDU_PROCESSED==1)) ? ((8*(Destin->ADD_RECORD_LEN_Present ? Destin->ADD_RECORD_LEN : 0))) : (0));
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->SDU___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->SDU)))->value), (unsigned)(bts), &(((&(Destin->SDU)))->usedBits));
			EDCopyBits (((&(Destin->SDU))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		if (((SDU_PROCESSED==1)&&(Destin->MACI_INCL_Present ? Destin->MACI_INCL : 0))) {
			SETPRESENT_c_FCSCH_PDU_SDUs_data_MACI(Destin, ED_TRUE);
			bts = 32;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->MACI___LOCATOR), CurrOfs, bts);
				Destin->MACI = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_PDU_SDUs_data_MACI(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* MACI 3.1.2.3.1.8.1 */
		
			if (P_REV_IN_USE_NOCSN_04 >= 7) CurrOfs = CS0004E_PDU_Padding_plus_2_Decode (CurrOfs, LastOfs, pp_CS0004E_Details);
			SDU_PROCESSED=2;
		}
		/* --------------------------------------------------------------------- */
		/*  ALL OTHER SDUs */
		/* --------------------------------------------------------------------- */
		if (SDU_PROCESSED==0) {
			SDU_PROCESSED=1;
		
			SDU_LENGTH = CS0004E_f_csch_CalcSDUSize ((const char*)Buffer, CurrOfs, LastOfs, P_REV_IN_USE_NOCSN_04, (unsigned)MSG_ID);
		
		bts = (SDU_LENGTH);
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->SDU___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->SDU)))->value), (unsigned)(bts), &(((&(Destin->SDU)))->usedBits));
			EDCopyBits (((&(Destin->SDU))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* PADDING */
		
		if (P_REV_IN_USE_NOCSN_04 >= 7) CurrOfs = CS0004E_PDU_Padding_plus_2_Decode (CurrOfs, LastOfs, pp_CS0004E_Details);
		/* MACI 3.1.2.3.1.8.1 */
		if ((Destin->MACI_INCL_Present ? Destin->MACI_INCL : 0)) {
			SETPRESENT_c_FCSCH_PDU_SDUs_data_MACI(Destin, ED_TRUE);
			bts = 32;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->MACI___LOCATOR), CurrOfs, bts);
				Destin->MACI = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_PDU_SDUs_data_MACI(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
			SDU_PROCESSED=2;
		}
		
		}
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_PDU_SDUs_data_Extended_Address (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_PDU_SDUs_data_Extended_Address* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_Addressing_Extended_Address */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_FCSCH_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->MEID))->usedBits == (int) (8*((pp_CS0004E_Details->userTag[0])-1)));
		PUSH_BIN ((&(Source->MEID))->value, (&(Source->MEID))->usedBits);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_PDU_SDUs_data_Extended_Address (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_PDU_SDUs_data_Extended_Address* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_Addressing_Extended_Address */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_FCSCH_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = (8*((pp_CS0004E_Details->userTag[0])-1));
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->MEID___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->MEID)))->value), (unsigned)(bts), &(((&(Destin->MEID)))->usedBits));
			EDCopyBits (((&(Destin->MEID))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_PDU_SDUs_data_IMSI_S (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_PDU_SDUs_data_IMSI_S* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_Addressing_IMSI_S */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_FCSCH_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* Format discussed in AXN0048 */
		PUSH_INT (Source->IMSI_M_S1, 24);
		PUSH_INT (Source->IMSI_M_S2, 10);
		/* RESERVED */
		/* Encode spare bits */
		PUSH_INT (0, 6);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_PDU_SDUs_data_IMSI_S (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_PDU_SDUs_data_IMSI_S* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_Addressing_IMSI_S */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_FCSCH_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		/* Format discussed in AXN0048 */
		bts = 24;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_M_S1___LOCATOR), CurrOfs, bts);
			Destin->IMSI_M_S1 = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 10;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_M_S2___LOCATOR), CurrOfs, bts);
			Destin->IMSI_M_S2 = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* RESERVED */
		/* Decode spare bit(s) */
		bts = 6;
		if (LastOfs-CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_PDU_SDUs_data_ESN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_PDU_SDUs_data_ESN* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_Addressing_ESN */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_FCSCH_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->ESN))->usedBits == (int) (8*(pp_CS0004E_Details->userTag[0])));
		PUSH_BIN ((&(Source->ESN))->value, (&(Source->ESN))->usedBits);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_PDU_SDUs_data_ESN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_PDU_SDUs_data_ESN* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_Addressing_ESN */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_FCSCH_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = (8*(pp_CS0004E_Details->userTag[0]));
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ESN___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->ESN)))->value), (unsigned)(bts), &(((&(Destin->ESN)))->usedBits));
			EDCopyBits (((&(Destin->ESN))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_PDU_SDUs_data_IMSI (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_PDU_SDUs_data_IMSI* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_Addressing_IMSI */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_FCSCH_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->IMSI_CLASS, 1);
		if ((Source->IMSI_CLASS==0)) {
			/* Field 'IMSI_CLASS_0' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0(Source));
			CurrOfs += ENCODE_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0 (Buffer, CurrOfs, Source->IMSI_CLASS_0, pp_CS0004E_Details);
		}
		else {
			/* Field 'IMSI_CLASS_0' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0(Source));
		}
		if ((Source->IMSI_CLASS==1)) {
			/* Field 'IMSI_CLASS_1' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1(Source));
			CurrOfs += ENCODE_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1 (Buffer, CurrOfs, Source->IMSI_CLASS_1, pp_CS0004E_Details);
		}
		else {
			/* Field 'IMSI_CLASS_1' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1(Source));
		}
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_PDU_SDUs_data_IMSI (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_PDU_SDUs_data_IMSI* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_Addressing_IMSI */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_FCSCH_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_CLASS___LOCATOR), CurrOfs, bts);
			Destin->IMSI_CLASS = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		if ((Destin->IMSI_CLASS==0)) {
			SETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0(Destin, ED_TRUE);
			bts = DECODE_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0 (Buffer, CurrOfs, Destin->IMSI_CLASS_0, LastOfs-CurrOfs , pp_CS0004E_Details);
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((Destin->IMSI_CLASS==1)) {
			SETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1(Destin, ED_TRUE);
			bts = DECODE_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1 (Buffer, CurrOfs, Destin->IMSI_CLASS_1, LastOfs-CurrOfs , pp_CS0004E_Details);
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_Addressing_IMSI_0 */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_FCSCH_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->IMSI_CLASS_0_TYPE, 2);
		/* Encode spare bits */
		PUSH_INT (0, (((Source->IMSI_CLASS_0_TYPE==0)) ? (3) : ((((Source->IMSI_CLASS_0_TYPE==1)) ? (4) : ((((Source->IMSI_CLASS_0_TYPE==2)) ? (1) : (2)))))));
		if (((Source->IMSI_CLASS_0_TYPE==2)||(Source->IMSI_CLASS_0_TYPE==3))) {
			/* Field 'MCC10' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0_MCC10(Source));
			PUSH_INT (Source->MCC10, 10);
		}
		else {
			/* Field 'MCC10' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0_MCC10(Source));
		}
		if (((Source->IMSI_CLASS_0_TYPE==1)||(Source->IMSI_CLASS_0_TYPE==3))) {
			/* Field 'IMSI_11_12' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0_IMSI_11_12(Source));
			PUSH_INT (Source->IMSI_11_12, 7);
		}
		else {
			/* Field 'IMSI_11_12' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0_IMSI_11_12(Source));
		}
		PUSH_BIN (Source->IMSI_S, 34);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_Addressing_IMSI_0 */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_FCSCH_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 2;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_CLASS_0_TYPE___LOCATOR), CurrOfs, bts);
			Destin->IMSI_CLASS_0_TYPE = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* Decode spare bit(s) */
		bts = (((Destin->IMSI_CLASS_0_TYPE==0)) ? (3) : ((((Destin->IMSI_CLASS_0_TYPE==1)) ? (4) : ((((Destin->IMSI_CLASS_0_TYPE==2)) ? (1) : (2))))));
		if (LastOfs-CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
			goto exitOnFail;
		}
		CurrOfs += bts;
		if (((Destin->IMSI_CLASS_0_TYPE==2)||(Destin->IMSI_CLASS_0_TYPE==3))) {
			SETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0_MCC10(Destin, ED_TRUE);
			bts = 10;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->MCC10___LOCATOR), CurrOfs, bts);
				Destin->MCC10 = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0_MCC10(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((Destin->IMSI_CLASS_0_TYPE==1)||(Destin->IMSI_CLASS_0_TYPE==3))) {
			SETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0_IMSI_11_12(Destin, ED_TRUE);
			bts = 7;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->IMSI_11_12___LOCATOR), CurrOfs, bts);
				Destin->IMSI_11_12 = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0_IMSI_11_12(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		bts = 34;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_S___LOCATOR), CurrOfs, bts);
			EDCopyBits (Destin->IMSI_S, 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_Addressing_IMSI_1 */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_FCSCH_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->IMSI_CLASS_1_TYPE, 1);
		/* Spare bits are optional */
		if ((Source->IMSI_CLASS_1_TYPE==0)) {
			/* Encode spare bits */
			PUSH_INT (0, 2);
		}
		/* RESERVED */
		PUSH_INT (Source->IMSI_ADDR_NUM, 3);
		if ((Source->IMSI_CLASS_1_TYPE==1)) {
			/* Field 'MCC' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1_MCC(Source));
			PUSH_INT (Source->MCC, 10);
		}
		else {
			/* Field 'MCC' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1_MCC(Source));
		}
		PUSH_INT (Source->IMSI_11_12, 7);
		PUSH_BIN (Source->IMSI_S, 34);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_Addressing_IMSI_1 */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_FCSCH_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_CLASS_1_TYPE___LOCATOR), CurrOfs, bts);
			Destin->IMSI_CLASS_1_TYPE = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* Spare bits are optional */
		if ((Destin->IMSI_CLASS_1_TYPE==0)) {
			/* Decode spare bit(s) */
			bts = 2;
			if (LastOfs-CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* RESERVED */
		bts = 3;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_ADDR_NUM___LOCATOR), CurrOfs, bts);
			Destin->IMSI_ADDR_NUM = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		if ((Destin->IMSI_CLASS_1_TYPE==1)) {
			SETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1_MCC(Destin, ED_TRUE);
			bts = 10;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->MCC___LOCATOR), CurrOfs, bts);
				Destin->MCC = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1_MCC(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		bts = 7;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_11_12___LOCATOR), CurrOfs, bts);
			Destin->IMSI_11_12 = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 34;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_S___LOCATOR), CurrOfs, bts);
			EDCopyBits (Destin->IMSI_S, 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_PDU_SDUs_data_TMSI (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_PDU_SDUs_data_TMSI* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_Addressing_TMSI */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_FCSCH_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* If ADDR_LEN is greater than four, 8 * (ADDR_LEN - 4); otherwise, 0.		 */
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->TMSI_ZONE))->usedBits == (int) ((((pp_CS0004E_Details->userTag[0])>4)) ? ((8*((pp_CS0004E_Details->userTag[0])-4))) : (0)));
		PUSH_BIN ((&(Source->TMSI_ZONE))->value, (&(Source->TMSI_ZONE))->usedBits);
		/* If ADDR_LEN is greater than four, 32; otherwise, 8 * ADDR_LEN. */
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->TMSI_CODE_ADDR))->usedBits == (int) ((((pp_CS0004E_Details->userTag[0])>4)) ? (32) : ((8*(pp_CS0004E_Details->userTag[0])))));
		PUSH_BIN ((&(Source->TMSI_CODE_ADDR))->value, (&(Source->TMSI_CODE_ADDR))->usedBits);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_PDU_SDUs_data_TMSI (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_PDU_SDUs_data_TMSI* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_Addressing_TMSI */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_FCSCH_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		/* If ADDR_LEN is greater than four, 8 * (ADDR_LEN - 4); otherwise, 0.		 */
		bts = ((((pp_CS0004E_Details->userTag[0])>4)) ? ((8*((pp_CS0004E_Details->userTag[0])-4))) : (0));
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->TMSI_ZONE___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->TMSI_ZONE)))->value), (unsigned)(bts), &(((&(Destin->TMSI_ZONE)))->usedBits));
			EDCopyBits (((&(Destin->TMSI_ZONE))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* If ADDR_LEN is greater than four, 32; otherwise, 8 * ADDR_LEN. */
		bts = ((((pp_CS0004E_Details->userTag[0])>4)) ? (32) : ((8*(pp_CS0004E_Details->userTag[0]))));
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->TMSI_CODE_ADDR___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->TMSI_CODE_ADDR)))->value), (unsigned)(bts), &(((&(Destin->TMSI_CODE_ADDR)))->usedBits));
			EDCopyBits (((&(Destin->TMSI_CODE_ADDR))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_PDU_SDUs_data_BROADCAST (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_PDU_SDUs_data_BROADCAST* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_Addressing_BROADCAST */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_FCSCH_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->BC_ADDR))->usedBits == (int) (8*(pp_CS0004E_Details->userTag[0])));
		PUSH_BIN ((&(Source->BC_ADDR))->value, (&(Source->BC_ADDR))->usedBits);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_PDU_SDUs_data_BROADCAST (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_PDU_SDUs_data_BROADCAST* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_Addressing_BROADCAST */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_FCSCH_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = (8*(pp_CS0004E_Details->userTag[0]));
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->BC_ADDR___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->BC_ADDR)))->value), (unsigned)(bts), &(((&(Destin->BC_ADDR)))->usedBits));
			EDCopyBits (((&(Destin->BC_ADDR))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_SYNC_BROADCAST_PDU (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_SYNC_BROADCAST_PDU* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME FCSCH_SYNC_BROADCAST_PDU */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_FCSCH_SYNC_BROADCAST_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* Mark the beginning of the PDU, to allow correct padding */
		pp_CS0004E_Details->n_PDU_START_OFFSET = CurrOfs;
		
		/* C.S0004 3.1.2.3.1.1 */
		PUSH_INT (Source->PD, 2);
		PUSH_INT (Source->MSG_ID, 6);
		/* SDU */
		PUSH_BIN ((&(Source->SDU))->value, (&(Source->SDU))->usedBits);
		/* PADDING */
		CurrOfs = CS0004E_PDU_Padding_plus_2_Encode (Buffer, CurrOfs, pp_CS0004E_Details);
		
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_SYNC_BROADCAST_PDU (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_SYNC_BROADCAST_PDU* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME FCSCH_SYNC_BROADCAST_PDU */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_FCSCH_SYNC_BROADCAST_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		/* Mark the beginning of the PDU, to allow correct padding */
		pp_CS0004E_Details->n_PDU_START_OFFSET = CurrOfs;
		
		/* C.S0004 3.1.2.3.1.1 */
		bts = 2;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->PD___LOCATOR), CurrOfs, bts);
			Destin->PD = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 6;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->MSG_ID___LOCATOR), CurrOfs, bts);
			Destin->MSG_ID = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* SDU */
		bts = (int)(LastOfs-CurrOfs);
		ED_LOCATOR_SET (&(Destin->SDU___LOCATOR), CurrOfs, bts);
		EDAllocBinary (&(((&(Destin->SDU)))->value), (unsigned)bts, &(((&(Destin->SDU)))->usedBits));
		EDCopyBits (((&(Destin->SDU))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* PADDING */
		
		CurrOfs = CS0004E_PDU_Padding_plus_2_Decode (CurrOfs, LastOfs, pp_CS0004E_Details);
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_NON_PRIMARY_BROADCAST_PDU* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME FCSCH_NON_PRIMARY_BROADCAST_PDU */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_FCSCH_SYNC_NON_PRIMARY_BROADCAST_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* Reset exported tag 27 'ADDR_LEN' */
		pp_CS0004E_Details->userTagPresent[1] = 0;
		pp_CS0004E_Details->userTag[1] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[1], "FCSCH_NON_PRIMARY_BROADCAST_PDU", "ADDR_LEN");
		pp_CS0004E_Details->userTagBusy[1] = 1;
#endif
		/* Reset exported tag 28 'MSG_ID' */
		pp_CS0004E_Details->userTagPresent[0] = 0;
		pp_CS0004E_Details->userTag[0] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[0], "FCSCH_NON_PRIMARY_BROADCAST_PDU", "MSG_ID");
		pp_CS0004E_Details->userTagBusy[0] = 1;
#endif
		/* Mark the beginning of the PDU, to allow correct padding */
		pp_CS0004E_Details->n_PDU_START_OFFSET = CurrOfs;
		
		/* C.S0004 3.1.2.3.1.1 */
		PUSH_INT (Source->PD, 2);
		PUSH_INT (Source->MSG_ID, 6);
		/* Set the exported tag */
		pp_CS0004E_Details->userTagPresent[0] = 1;
		pp_CS0004E_Details->userTag[0] = (int)Source->MSG_ID;
		/* ARQ Fields Section 3.1.2.1.1.1 */
		PUSH_INT (Source->ACK_SEQ, 3);
		PUSH_INT (Source->MSG_SEQ, 3);
		PUSH_INT (Source->ACK_REQ, 1);
		PUSH_INT (Source->VALID_ACK, 1);
		/* Addressing Fields  Section 3.1.2.2.1.3.1 */
		PUSH_INT (Source->ADDR_TYPE, 3);
		PUSH_INT (Source->ADDR_LEN, 4);
		/* Set the exported tag */
		pp_CS0004E_Details->userTagPresent[1] = 1;
		pp_CS0004E_Details->userTag[1] = (int)Source->ADDR_LEN;
		/* BEGIN OF PAD ZONE - ENCODE inclusive=0 bits=4 octet(=0)/bit(=1)=0 */
		{
			ED_EXLONG dataStartOfs0 = CurrOfs;
			int lenInBits0;
			if ((Source->ADDR_TYPE==4)) {
				/* Field 'EXT_ADDR_TYPE' is required */
				ED_ASSERT (GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_EXT_ADDR_TYPE(Source));
				PUSH_INT (Source->EXT_ADDR_TYPE, 3);
			}
			else {
				/* Field 'EXT_ADDR_TYPE' must be absent */
				ED_ASSERT (!GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_EXT_ADDR_TYPE(Source));
			}
			/* Spare bits are optional */
			if ((Source->ADDR_TYPE==4)) {
				/* Encode spare bits */
				PUSH_INT (0, 5);
			}
			/* ADDR_TYPE==b000 */
			if ((Source->ADDR_TYPE==0)) {
				/* Field 'IMSI_S' is required */
				ED_ASSERT (GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S(Source));
				CurrOfs += ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S (Buffer, CurrOfs, Source->IMSI_S, pp_CS0004E_Details);
			}
			else {
				/* Field 'IMSI_S' must be absent */
				ED_ASSERT (!GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S(Source));
			}
			/* ADDR_TYPE==b001 */
			if ((Source->ADDR_TYPE==1)) {
				/* Field 'ESN' is required */
				ED_ASSERT (GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN(Source));
				CurrOfs += ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN (Buffer, CurrOfs, Source->ESN, pp_CS0004E_Details);
			}
			else {
				/* Field 'ESN' must be absent */
				ED_ASSERT (!GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN(Source));
			}
			/* ADDR_TYPE==b010 */
			if ((Source->ADDR_TYPE==2)) {
				/* Field 'IMSI' is required */
				ED_ASSERT (GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI(Source));
				CurrOfs += ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI (Buffer, CurrOfs, Source->IMSI, pp_CS0004E_Details);
			}
			else {
				/* Field 'IMSI' must be absent */
				ED_ASSERT (!GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI(Source));
			}
			/* ADDR_TYPE==b011 */
			if ((Source->ADDR_TYPE==3)) {
				/* Field 'TMSI' is required */
				ED_ASSERT (GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI(Source));
				CurrOfs += ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI (Buffer, CurrOfs, Source->TMSI, pp_CS0004E_Details);
			}
			else {
				/* Field 'TMSI' must be absent */
				ED_ASSERT (!GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI(Source));
			}
			/* ADDR_TYPE==b100 */
			if ((Source->ADDR_TYPE==4)) {
				/* Field 'Extended_Address' is required */
				ED_ASSERT (GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address(Source));
				CurrOfs += ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address (Buffer, CurrOfs, Source->Extended_Address, pp_CS0004E_Details);
			}
			else {
				/* Field 'Extended_Address' must be absent */
				ED_ASSERT (!GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address(Source));
			}
			/* ADDR_TYPE==b101 */
			if ((Source->ADDR_TYPE==5)) {
				/* Field 'BROADCAST' is required */
				ED_ASSERT (GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST(Source));
				CurrOfs += ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST (Buffer, CurrOfs, Source->BROADCAST, pp_CS0004E_Details);
			}
			else {
				/* Field 'BROADCAST' must be absent */
				ED_ASSERT (!GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST(Source));
			}
			/* Calculate the encoded length in octets */
			lenInBits0 = (CurrOfs-dataStartOfs0);
			
			/* Save the encoded length into the length field */
			EDIntToBits (Buffer, dataStartOfs0-4, ((lenInBits0+7)/8)-0, 4);
			
			/* Pad if required */
			if ((lenInBits0 & 0x07) != 0) {
				PUSH_INT (0, 8-(lenInBits0 & 0x07));
			}
		}
		/* END OF PAD ZONE */
		/* Message Integrity Fields - Section 3.1.2.5.1 */
		/* Available only if P_REV_IN_USE >= 9 and PD=2 */
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Source->PD==2))) {
			/* Field 'MACI_INCL' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_MACI_INCL(Source));
			PUSH_INT (Source->MACI_INCL, 1);
		}
		else {
			/* Field 'MACI_INCL' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_MACI_INCL(Source));
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Source->MACI_INCL_Present ? Source->MACI_INCL : 0))) {
			/* Field 'SDU_KEY_ID' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_KEY_ID(Source));
			PUSH_INT (Source->SDU_KEY_ID, 2);
		}
		else {
			/* Field 'SDU_KEY_ID' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_KEY_ID(Source));
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Source->MACI_INCL_Present ? Source->MACI_INCL : 0))) {
			/* Field 'SDU_INTEGRITY_ALGO' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_INTEGRITY_ALGO(Source));
			PUSH_INT (Source->SDU_INTEGRITY_ALGO, 3);
		}
		else {
			/* Field 'SDU_INTEGRITY_ALGO' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_INTEGRITY_ALGO(Source));
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Source->MACI_INCL_Present ? Source->MACI_INCL : 0))) {
			/* Field 'SDU_SSEQ_OR_SSEQH' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_SSEQ_OR_SSEQH(Source));
			PUSH_INT (Source->SDU_SSEQ_OR_SSEQH, 1);
		}
		else {
			/* Field 'SDU_SSEQ_OR_SSEQH' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_SSEQ_OR_SSEQH(Source));
		}
		if ((((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Source->MACI_INCL_Present ? Source->MACI_INCL : 0))&&!((Source->SDU_SSEQ_OR_SSEQH_Present ? Source->SDU_SSEQ_OR_SSEQH : 0)))) {
			/* Field 'SDU_SSEQ' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_SSEQ(Source));
			PUSH_INT (Source->SDU_SSEQ, 8);
		}
		else {
			/* Field 'SDU_SSEQ' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_SSEQ(Source));
		}
		if ((((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Source->MACI_INCL_Present ? Source->MACI_INCL : 0))&&(Source->SDU_SSEQ_OR_SSEQH_Present ? Source->SDU_SSEQ_OR_SSEQH : 0))) {
			/* Field 'SDU_SSEQ_H' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_SSEQ_H(Source));
			PUSH_INT (Source->SDU_SSEQ_H, 24);
		}
		else {
			/* Field 'SDU_SSEQ_H' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_SSEQ_H(Source));
		}
		/* Extended Encryption, Section 3.1.2.3.1.3.1 */
		/* Included only if P_REV_IN_USE >= 7 and PD!=0 */
		/* See 3.1.2.3.2.3: "For PDUs transmitted on the Paging Channel when P_REV_IN_USE is greater than or equal */
		/* to  seven, the base station may include the Extended-Encryption Fields." */
		/* Chapter 3.1.2.3.1.3.2 states that a P_REV>=7 can "omit all the Extended-Encryption Fields, in which case the base station */
		/* shall use a PDU format with the PD field set to ‘00’" (AXN0016) */
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=7)&&(Source->PD!=0))) {
			/* Field 'ENC_FIELDS_INCL' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ENC_FIELDS_INCL(Source));
			PUSH_INT (Source->ENC_FIELDS_INCL, 1);
		}
		else {
			/* Field 'ENC_FIELDS_INCL' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ENC_FIELDS_INCL(Source));
		}
		/* If ENC_FIELDS_INCL is set to '1', the base station shall include the SDU_ENCRYPT_MODE (C.S0004, 3.1.2.3.1.3.2) */
		if ((Source->ENC_FIELDS_INCL_Present ? Source->ENC_FIELDS_INCL : 0)) {
			/* Field 'SDU_ENCRYPT_MODE' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_ENCRYPT_MODE(Source));
			PUSH_INT (Source->SDU_ENCRYPT_MODE, 3);
		}
		else {
			/* Field 'SDU_ENCRYPT_MODE' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_ENCRYPT_MODE(Source));
		}
		/* If the SDU_ENCRYPT_MODE field is included and is set to '001' , the base station shall include the ENC_SEQ (C.S0004, 3.1.2.3.1.3.2) */
		if (((Source->SDU_ENCRYPT_MODE_Present ? Source->SDU_ENCRYPT_MODE : 0)==1)) {
			/* Field 'ENC_SEQ' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ENC_SEQ(Source));
			PUSH_INT (Source->ENC_SEQ, 8);
		}
		else {
			/* Field 'ENC_SEQ' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ENC_SEQ(Source));
		}
		/* SDU */
		{
			int SDU_LENGTH;
		
		
			SDU_LENGTH = ED_THIS->SDU.usedBits;
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->SDU))->usedBits == (int) (SDU_LENGTH));
		PUSH_BIN ((&(Source->SDU))->value, (&(Source->SDU))->usedBits);
		/* PADDING */
		CurrOfs = CS0004E_PDU_Padding_plus_2_Encode (Buffer, CurrOfs, pp_CS0004E_Details);
		SDU_LENGTH = SDU_LENGTH;
		}
		/* MACI 3.1.2.3.1.8.1 */
		if ((Source->MACI_INCL_Present ? Source->MACI_INCL : 0)) {
			/* Field 'MACI' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_MACI(Source));
			PUSH_INT (Source->MACI, 32);
		}
		else {
			/* Field 'MACI' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_MACI(Source));
		}
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[1], "FCSCH_NON_PRIMARY_BROADCAST_PDU", "ADDR_LEN");
		pp_CS0004E_Details->userTagBusy[1] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[0], "FCSCH_NON_PRIMARY_BROADCAST_PDU", "MSG_ID");
		pp_CS0004E_Details->userTagBusy[0] = 0;
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_NON_PRIMARY_BROADCAST_PDU* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME FCSCH_NON_PRIMARY_BROADCAST_PDU */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_FCSCH_SYNC_NON_PRIMARY_BROADCAST_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		/* Reset exported tag 27 'ADDR_LEN' */
		pp_CS0004E_Details->userTagPresent[1] = 0;
		pp_CS0004E_Details->userTag[1] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[1], "FCSCH_NON_PRIMARY_BROADCAST_PDU", "ADDR_LEN");
		pp_CS0004E_Details->userTagBusy[1] = 1;
#endif
		/* Reset exported tag 28 'MSG_ID' */
		pp_CS0004E_Details->userTagPresent[0] = 0;
		pp_CS0004E_Details->userTag[0] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[0], "FCSCH_NON_PRIMARY_BROADCAST_PDU", "MSG_ID");
		pp_CS0004E_Details->userTagBusy[0] = 1;
#endif
		/* Mark the beginning of the PDU, to allow correct padding */
		pp_CS0004E_Details->n_PDU_START_OFFSET = CurrOfs;
		
		/* C.S0004 3.1.2.3.1.1 */
		bts = 2;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->PD___LOCATOR), CurrOfs, bts);
			Destin->PD = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 6;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->MSG_ID___LOCATOR), CurrOfs, bts);
			Destin->MSG_ID = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			/* Set the exported tag */
			pp_CS0004E_Details->userTagPresent[0] = 1;
			pp_CS0004E_Details->userTag[0] = (int)Destin->MSG_ID;
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* ARQ Fields Section 3.1.2.1.1.1 */
		bts = 3;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ACK_SEQ___LOCATOR), CurrOfs, bts);
			Destin->ACK_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 3;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->MSG_SEQ___LOCATOR), CurrOfs, bts);
			Destin->MSG_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ACK_REQ___LOCATOR), CurrOfs, bts);
			Destin->ACK_REQ = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->VALID_ACK___LOCATOR), CurrOfs, bts);
			Destin->VALID_ACK = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* Addressing Fields  Section 3.1.2.2.1.3.1 */
		bts = 3;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ADDR_TYPE___LOCATOR), CurrOfs, bts);
			Destin->ADDR_TYPE = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 4;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ADDR_LEN___LOCATOR), CurrOfs, bts);
			Destin->ADDR_LEN = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			/* Set the exported tag */
			pp_CS0004E_Details->userTagPresent[1] = 1;
			pp_CS0004E_Details->userTag[1] = (int)Destin->ADDR_LEN;
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* BEGIN OF PAD ZONE - DECODE inclusive=0 bits=4 octet(=0)/bit(=1)=0 */
		{
			/* Save the current final offset position */
			int LastOfs1 = LastOfs;
			
			/* Calculate the new final offset position */
			int NewLastOfs1 = CurrOfs +
			EDBitsToInt (Buffer, CurrOfs-4, 4) * 8;
			
			/* Temporarely set the new LastOfs value */
			LastOfs = NewLastOfs1;
			
			/* Execute the normal decoding */
			if ((Destin->ADDR_TYPE==4)) {
				SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_EXT_ADDR_TYPE(Destin, ED_TRUE);
				bts = 3;
				if (LastOfs - (int)CurrOfs < bts) {
					bts = ED_MESSAGE_TOO_SHORT;
				} 
				else {
					ED_LOCATOR_SET (&(Destin->EXT_ADDR_TYPE___LOCATOR), CurrOfs, bts);
					Destin->EXT_ADDR_TYPE = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
				}
				if (bts < 0) {
					/* If decoding failed, set the failed field to "not present" */
					SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_EXT_ADDR_TYPE(Destin, ED_FALSE);
					goto exitOnFail;
				}
				CurrOfs += bts;
			}
			/* Spare bits are optional */
			if ((Destin->ADDR_TYPE==4)) {
				/* Decode spare bit(s) */
				bts = 5;
				if (LastOfs-CurrOfs < bts) {
					bts = ED_MESSAGE_TOO_SHORT;
					goto exitOnFail;
				}
				CurrOfs += bts;
			}
			/* ADDR_TYPE==b000 */
			if ((Destin->ADDR_TYPE==0)) {
				SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S(Destin, ED_TRUE);
				bts = DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S (Buffer, CurrOfs, Destin->IMSI_S, LastOfs-CurrOfs , pp_CS0004E_Details);
				if (bts < 0) {
					/* If decoding failed, set the failed field to "not present" */
					SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S(Destin, ED_FALSE);
					goto exitOnFail;
				}
				CurrOfs += bts;
			}
			/* ADDR_TYPE==b001 */
			if ((Destin->ADDR_TYPE==1)) {
				SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN(Destin, ED_TRUE);
				bts = DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN (Buffer, CurrOfs, Destin->ESN, LastOfs-CurrOfs , pp_CS0004E_Details);
				if (bts < 0) {
					/* If decoding failed, set the failed field to "not present" */
					SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN(Destin, ED_FALSE);
					goto exitOnFail;
				}
				CurrOfs += bts;
			}
			/* ADDR_TYPE==b010 */
			if ((Destin->ADDR_TYPE==2)) {
				SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI(Destin, ED_TRUE);
				bts = DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI (Buffer, CurrOfs, Destin->IMSI, LastOfs-CurrOfs , pp_CS0004E_Details);
				if (bts < 0) {
					/* If decoding failed, set the failed field to "not present" */
					SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI(Destin, ED_FALSE);
					goto exitOnFail;
				}
				CurrOfs += bts;
			}
			/* ADDR_TYPE==b011 */
			if ((Destin->ADDR_TYPE==3)) {
				SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI(Destin, ED_TRUE);
				bts = DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI (Buffer, CurrOfs, Destin->TMSI, LastOfs-CurrOfs , pp_CS0004E_Details);
				if (bts < 0) {
					/* If decoding failed, set the failed field to "not present" */
					SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI(Destin, ED_FALSE);
					goto exitOnFail;
				}
				CurrOfs += bts;
			}
			/* ADDR_TYPE==b100 */
			if ((Destin->ADDR_TYPE==4)) {
				SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address(Destin, ED_TRUE);
				bts = DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address (Buffer, CurrOfs, Destin->Extended_Address, LastOfs-CurrOfs , pp_CS0004E_Details);
				if (bts < 0) {
					/* If decoding failed, set the failed field to "not present" */
					SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address(Destin, ED_FALSE);
					goto exitOnFail;
				}
				CurrOfs += bts;
			}
			/* ADDR_TYPE==b101 */
			if ((Destin->ADDR_TYPE==5)) {
				SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST(Destin, ED_TRUE);
				bts = DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST (Buffer, CurrOfs, Destin->BROADCAST, LastOfs-CurrOfs , pp_CS0004E_Details);
				if (bts < 0) {
					/* If decoding failed, set the failed field to "not present" */
					SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST(Destin, ED_FALSE);
					goto exitOnFail;
				}
				CurrOfs += bts;
			}
			/* The inner data should never overflow the available space by design */
			ED_ASSERT (CurrOfs <= NewLastOfs1);
			
			/* If needed, skip the extra bits and align to the calculated range */
			CurrOfs = NewLastOfs1;
			
			/* If the required data is too long, signal ED_MESSAGE_TOO_SHORT */
			if (NewLastOfs1 > LastOfs1) {
				bts = ED_MESSAGE_TOO_SHORT;
				goto exitOnFail;
			}
			
			/* Set back the LastOfs variable to the stored value */
			LastOfs = LastOfs1;
		}
		/* END OF PAD ZONE */
		/* Message Integrity Fields - Section 3.1.2.5.1 */
		/* Available only if P_REV_IN_USE >= 9 and PD=2 */
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Destin->PD==2))) {
			SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_MACI_INCL(Destin, ED_TRUE);
			bts = 1;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->MACI_INCL___LOCATOR), CurrOfs, bts);
				Destin->MACI_INCL = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_MACI_INCL(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Destin->MACI_INCL_Present ? Destin->MACI_INCL : 0))) {
			SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_KEY_ID(Destin, ED_TRUE);
			bts = 2;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_KEY_ID___LOCATOR), CurrOfs, bts);
				Destin->SDU_KEY_ID = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_KEY_ID(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Destin->MACI_INCL_Present ? Destin->MACI_INCL : 0))) {
			SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_INTEGRITY_ALGO(Destin, ED_TRUE);
			bts = 3;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_INTEGRITY_ALGO___LOCATOR), CurrOfs, bts);
				Destin->SDU_INTEGRITY_ALGO = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_INTEGRITY_ALGO(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Destin->MACI_INCL_Present ? Destin->MACI_INCL : 0))) {
			SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_SSEQ_OR_SSEQH(Destin, ED_TRUE);
			bts = 1;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_SSEQ_OR_SSEQH___LOCATOR), CurrOfs, bts);
				Destin->SDU_SSEQ_OR_SSEQH = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_SSEQ_OR_SSEQH(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Destin->MACI_INCL_Present ? Destin->MACI_INCL : 0))&&!((Destin->SDU_SSEQ_OR_SSEQH_Present ? Destin->SDU_SSEQ_OR_SSEQH : 0)))) {
			SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_SSEQ(Destin, ED_TRUE);
			bts = 8;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_SSEQ___LOCATOR), CurrOfs, bts);
				Destin->SDU_SSEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_SSEQ(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Destin->MACI_INCL_Present ? Destin->MACI_INCL : 0))&&(Destin->SDU_SSEQ_OR_SSEQH_Present ? Destin->SDU_SSEQ_OR_SSEQH : 0))) {
			SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_SSEQ_H(Destin, ED_TRUE);
			bts = 24;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_SSEQ_H___LOCATOR), CurrOfs, bts);
				Destin->SDU_SSEQ_H = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_SSEQ_H(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* Extended Encryption, Section 3.1.2.3.1.3.1 */
		/* Included only if P_REV_IN_USE >= 7 and PD!=0 */
		/* See 3.1.2.3.2.3: "For PDUs transmitted on the Paging Channel when P_REV_IN_USE is greater than or equal */
		/* to  seven, the base station may include the Extended-Encryption Fields." */
		/* Chapter 3.1.2.3.1.3.2 states that a P_REV>=7 can "omit all the Extended-Encryption Fields, in which case the base station */
		/* shall use a PDU format with the PD field set to ‘00’" (AXN0016) */
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=7)&&(Destin->PD!=0))) {
			SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ENC_FIELDS_INCL(Destin, ED_TRUE);
			bts = 1;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->ENC_FIELDS_INCL___LOCATOR), CurrOfs, bts);
				Destin->ENC_FIELDS_INCL = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ENC_FIELDS_INCL(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* If ENC_FIELDS_INCL is set to '1', the base station shall include the SDU_ENCRYPT_MODE (C.S0004, 3.1.2.3.1.3.2) */
		if ((Destin->ENC_FIELDS_INCL_Present ? Destin->ENC_FIELDS_INCL : 0)) {
			SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_ENCRYPT_MODE(Destin, ED_TRUE);
			bts = 3;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_ENCRYPT_MODE___LOCATOR), CurrOfs, bts);
				Destin->SDU_ENCRYPT_MODE = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_ENCRYPT_MODE(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* If the SDU_ENCRYPT_MODE field is included and is set to '001' , the base station shall include the ENC_SEQ (C.S0004, 3.1.2.3.1.3.2) */
		if (((Destin->SDU_ENCRYPT_MODE_Present ? Destin->SDU_ENCRYPT_MODE : 0)==1)) {
			SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ENC_SEQ(Destin, ED_TRUE);
			bts = 8;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->ENC_SEQ___LOCATOR), CurrOfs, bts);
				Destin->ENC_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ENC_SEQ(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* SDU */
		{
			int SDU_LENGTH;
		
			SDU_LENGTH = CS0004E_f_csch_CalcSDUSize ((const char*)Buffer, CurrOfs, LastOfs, P_REV_IN_USE_NOCSN_04, (unsigned)pp_CS0004E_Details->userTag[0]/*MSG_ID*/);
		
		bts = (SDU_LENGTH);
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->SDU___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->SDU)))->value), (unsigned)(bts), &(((&(Destin->SDU)))->usedBits));
			EDCopyBits (((&(Destin->SDU))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* PADDING */
		
		CurrOfs = CS0004E_PDU_Padding_plus_2_Decode (CurrOfs, LastOfs, pp_CS0004E_Details);
		}
		/* MACI 3.1.2.3.1.8.1 */
		if ((Destin->MACI_INCL_Present ? Destin->MACI_INCL : 0)) {
			SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_MACI(Destin, ED_TRUE);
			bts = 32;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->MACI___LOCATOR), CurrOfs, bts);
				Destin->MACI = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_MACI(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[1], "FCSCH_NON_PRIMARY_BROADCAST_PDU", "ADDR_LEN");
		pp_CS0004E_Details->userTagBusy[1] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[0], "FCSCH_NON_PRIMARY_BROADCAST_PDU", "MSG_ID");
		pp_CS0004E_Details->userTagBusy[0] = 0;
#endif
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[1], "FCSCH_NON_PRIMARY_BROADCAST_PDU", "ADDR_LEN");
		pp_CS0004E_Details->userTagBusy[1] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[0], "FCSCH_NON_PRIMARY_BROADCAST_PDU", "MSG_ID");
		pp_CS0004E_Details->userTagBusy[0] = 0;
#endif
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_NPRIM_BC_PDU_Addressing_Extended_Address */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_FCSCH_SYNC_NON_PRIMARY_BROADCAST_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->MEID))->usedBits == (int) (8*((pp_CS0004E_Details->userTag[1])-1)));
		PUSH_BIN ((&(Source->MEID))->value, (&(Source->MEID))->usedBits);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_NPRIM_BC_PDU_Addressing_Extended_Address */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_FCSCH_SYNC_NON_PRIMARY_BROADCAST_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = (8*((pp_CS0004E_Details->userTag[1])-1));
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->MEID___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->MEID)))->value), (unsigned)(bts), &(((&(Destin->MEID)))->usedBits));
			EDCopyBits (((&(Destin->MEID))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_NPRIM_BC_PDU_Addressing_IMSI_S */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_FCSCH_SYNC_NON_PRIMARY_BROADCAST_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* Format discussed in AXN0048 */
		PUSH_INT (Source->IMSI_M_S1, 24);
		PUSH_INT (Source->IMSI_M_S2, 10);
		/* RESERVED */
		/* Encode spare bits */
		PUSH_INT (0, 6);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_NPRIM_BC_PDU_Addressing_IMSI_S */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_FCSCH_SYNC_NON_PRIMARY_BROADCAST_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		/* Format discussed in AXN0048 */
		bts = 24;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_M_S1___LOCATOR), CurrOfs, bts);
			Destin->IMSI_M_S1 = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 10;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_M_S2___LOCATOR), CurrOfs, bts);
			Destin->IMSI_M_S2 = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* RESERVED */
		/* Decode spare bit(s) */
		bts = 6;
		if (LastOfs-CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_NPRIM_BC_PDU_Addressing_ESN */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_FCSCH_SYNC_NON_PRIMARY_BROADCAST_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->ESN))->usedBits == (int) (8*(pp_CS0004E_Details->userTag[1])));
		PUSH_BIN ((&(Source->ESN))->value, (&(Source->ESN))->usedBits);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_NPRIM_BC_PDU_Addressing_ESN */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_FCSCH_SYNC_NON_PRIMARY_BROADCAST_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = (8*(pp_CS0004E_Details->userTag[1]));
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ESN___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->ESN)))->value), (unsigned)(bts), &(((&(Destin->ESN)))->usedBits));
			EDCopyBits (((&(Destin->ESN))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_NPRIM_BC_PDU_Addressing_IMSI */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_FCSCH_SYNC_NON_PRIMARY_BROADCAST_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->IMSI_CLASS, 1);
		if ((Source->IMSI_CLASS==0)) {
			/* Field 'IMSI_CLASS_0' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0(Source));
			CurrOfs += ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0 (Buffer, CurrOfs, Source->IMSI_CLASS_0, pp_CS0004E_Details);
		}
		else {
			/* Field 'IMSI_CLASS_0' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0(Source));
		}
		if ((Source->IMSI_CLASS==1)) {
			/* Field 'IMSI_CLASS_1' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1(Source));
			CurrOfs += ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1 (Buffer, CurrOfs, Source->IMSI_CLASS_1, pp_CS0004E_Details);
		}
		else {
			/* Field 'IMSI_CLASS_1' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1(Source));
		}
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_NPRIM_BC_PDU_Addressing_IMSI */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_FCSCH_SYNC_NON_PRIMARY_BROADCAST_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_CLASS___LOCATOR), CurrOfs, bts);
			Destin->IMSI_CLASS = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		if ((Destin->IMSI_CLASS==0)) {
			SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0(Destin, ED_TRUE);
			bts = DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0 (Buffer, CurrOfs, Destin->IMSI_CLASS_0, LastOfs-CurrOfs , pp_CS0004E_Details);
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((Destin->IMSI_CLASS==1)) {
			SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1(Destin, ED_TRUE);
			bts = DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1 (Buffer, CurrOfs, Destin->IMSI_CLASS_1, LastOfs-CurrOfs , pp_CS0004E_Details);
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_NPRIM_BC_PDU_Addressing_IMSI_0 */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_FCSCH_SYNC_NON_PRIMARY_BROADCAST_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->IMSI_CLASS_0_TYPE, 2);
		/* Encode spare bits */
		PUSH_INT (0, (((Source->IMSI_CLASS_0_TYPE==0)) ? (3) : ((((Source->IMSI_CLASS_0_TYPE==1)) ? (4) : ((((Source->IMSI_CLASS_0_TYPE==2)) ? (1) : (2)))))));
		if (((Source->IMSI_CLASS_0_TYPE==2)||(Source->IMSI_CLASS_0_TYPE==3))) {
			/* Field 'MCC10' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0_MCC10(Source));
			PUSH_INT (Source->MCC10, 10);
		}
		else {
			/* Field 'MCC10' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0_MCC10(Source));
		}
		if (((Source->IMSI_CLASS_0_TYPE==1)||(Source->IMSI_CLASS_0_TYPE==3))) {
			/* Field 'IMSI_11_12' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0_IMSI_11_12(Source));
			PUSH_INT (Source->IMSI_11_12, 7);
		}
		else {
			/* Field 'IMSI_11_12' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0_IMSI_11_12(Source));
		}
		PUSH_BIN (Source->IMSI_S, 34);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_NPRIM_BC_PDU_Addressing_IMSI_0 */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_FCSCH_SYNC_NON_PRIMARY_BROADCAST_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 2;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_CLASS_0_TYPE___LOCATOR), CurrOfs, bts);
			Destin->IMSI_CLASS_0_TYPE = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* Decode spare bit(s) */
		bts = (((Destin->IMSI_CLASS_0_TYPE==0)) ? (3) : ((((Destin->IMSI_CLASS_0_TYPE==1)) ? (4) : ((((Destin->IMSI_CLASS_0_TYPE==2)) ? (1) : (2))))));
		if (LastOfs-CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
			goto exitOnFail;
		}
		CurrOfs += bts;
		if (((Destin->IMSI_CLASS_0_TYPE==2)||(Destin->IMSI_CLASS_0_TYPE==3))) {
			SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0_MCC10(Destin, ED_TRUE);
			bts = 10;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->MCC10___LOCATOR), CurrOfs, bts);
				Destin->MCC10 = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0_MCC10(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((Destin->IMSI_CLASS_0_TYPE==1)||(Destin->IMSI_CLASS_0_TYPE==3))) {
			SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0_IMSI_11_12(Destin, ED_TRUE);
			bts = 7;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->IMSI_11_12___LOCATOR), CurrOfs, bts);
				Destin->IMSI_11_12 = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0_IMSI_11_12(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		bts = 34;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_S___LOCATOR), CurrOfs, bts);
			EDCopyBits (Destin->IMSI_S, 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_NPRIM_BC_PDU_Addressing_IMSI_1 */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_FCSCH_SYNC_NON_PRIMARY_BROADCAST_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->IMSI_CLASS_1_TYPE, 1);
		/* Spare bits are optional */
		if ((Source->IMSI_CLASS_1_TYPE==0)) {
			/* Encode spare bits */
			PUSH_INT (0, 2);
		}
		/* RESERVED */
		PUSH_INT (Source->IMSI_ADDR_NUM, 3);
		if ((Source->IMSI_CLASS_1_TYPE==1)) {
			/* Field 'MCC' is required */
			ED_ASSERT (GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1_MCC(Source));
			PUSH_INT (Source->MCC, 10);
		}
		else {
			/* Field 'MCC' must be absent */
			ED_ASSERT (!GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1_MCC(Source));
		}
		PUSH_INT (Source->IMSI_11_12, 7);
		PUSH_BIN (Source->IMSI_S, 34);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_NPRIM_BC_PDU_Addressing_IMSI_1 */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_FCSCH_SYNC_NON_PRIMARY_BROADCAST_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_CLASS_1_TYPE___LOCATOR), CurrOfs, bts);
			Destin->IMSI_CLASS_1_TYPE = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* Spare bits are optional */
		if ((Destin->IMSI_CLASS_1_TYPE==0)) {
			/* Decode spare bit(s) */
			bts = 2;
			if (LastOfs-CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* RESERVED */
		bts = 3;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_ADDR_NUM___LOCATOR), CurrOfs, bts);
			Destin->IMSI_ADDR_NUM = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		if ((Destin->IMSI_CLASS_1_TYPE==1)) {
			SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1_MCC(Destin, ED_TRUE);
			bts = 10;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->MCC___LOCATOR), CurrOfs, bts);
				Destin->MCC = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1_MCC(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		bts = 7;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_11_12___LOCATOR), CurrOfs, bts);
			Destin->IMSI_11_12 = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 34;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_S___LOCATOR), CurrOfs, bts);
			EDCopyBits (Destin->IMSI_S, 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_NPRIM_BC_PDU_Addressing_TMSI */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_FCSCH_SYNC_NON_PRIMARY_BROADCAST_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* If ADDR_LEN is greater than four, 8 * (ADDR_LEN - 4); otherwise, 0.		 */
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->TMSI_ZONE))->usedBits == (int) ((((pp_CS0004E_Details->userTag[1])>4)) ? ((8*((pp_CS0004E_Details->userTag[1])-4))) : (0)));
		PUSH_BIN ((&(Source->TMSI_ZONE))->value, (&(Source->TMSI_ZONE))->usedBits);
		/* If ADDR_LEN is greater than four, 32; otherwise, 8 * ADDR_LEN. */
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->TMSI_CODE_ADDR))->usedBits == (int) ((((pp_CS0004E_Details->userTag[1])>4)) ? (32) : ((8*(pp_CS0004E_Details->userTag[1])))));
		PUSH_BIN ((&(Source->TMSI_CODE_ADDR))->value, (&(Source->TMSI_CODE_ADDR))->usedBits);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_NPRIM_BC_PDU_Addressing_TMSI */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_FCSCH_SYNC_NON_PRIMARY_BROADCAST_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		/* If ADDR_LEN is greater than four, 8 * (ADDR_LEN - 4); otherwise, 0.		 */
		bts = ((((pp_CS0004E_Details->userTag[1])>4)) ? ((8*((pp_CS0004E_Details->userTag[1])-4))) : (0));
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->TMSI_ZONE___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->TMSI_ZONE)))->value), (unsigned)(bts), &(((&(Destin->TMSI_ZONE)))->usedBits));
			EDCopyBits (((&(Destin->TMSI_ZONE))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* If ADDR_LEN is greater than four, 32; otherwise, 8 * ADDR_LEN. */
		bts = ((((pp_CS0004E_Details->userTag[1])>4)) ? (32) : ((8*(pp_CS0004E_Details->userTag[1]))));
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->TMSI_CODE_ADDR___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->TMSI_CODE_ADDR)))->value), (unsigned)(bts), &(((&(Destin->TMSI_CODE_ADDR)))->usedBits));
			EDCopyBits (((&(Destin->TMSI_CODE_ADDR))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_NPRIM_BC_PDU_Addressing_BROADCAST */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_FCSCH_SYNC_NON_PRIMARY_BROADCAST_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->BC_ADDR))->usedBits == (int) (8*(pp_CS0004E_Details->userTag[1])));
		PUSH_BIN ((&(Source->BC_ADDR))->value, (&(Source->BC_ADDR))->usedBits);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_NPRIM_BC_PDU_Addressing_BROADCAST */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_FCSCH_SYNC_NON_PRIMARY_BROADCAST_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = (8*(pp_CS0004E_Details->userTag[1]));
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->BC_ADDR___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->BC_ADDR)))->value), (unsigned)(bts), &(((&(Destin->BC_ADDR)))->usedBits));
			EDCopyBits (((&(Destin->BC_ADDR))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_GPM_PDU (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GPM_PDU* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME GPM_PDU */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_f_csch_GPM_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int cnt;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* Mark the beginning of the PDU, to allow correct padding */
		pp_CS0004E_Details->n_PDU_START_OFFSET = CurrOfs;
		
		/* C.S0004 3.1.2.3.1.1 */
		PUSH_INT (Source->PD, 2);
		PUSH_INT (Source->MSG_ID, 6);
		/* GPM Common Fields */
		/* C.S0005 3.7.2.3.2.17 */
		PUSH_INT (Source->CONFIG_MSG_SEQ, 6);
		PUSH_INT (Source->ACC_MSG_SEQ, 6);
		PUSH_INT (Source->CLASS_0_DONE, 1);
		PUSH_INT (Source->CLASS_1_DONE, 1);
		PUSH_INT (Source->TMSI_DONE, 1);
		PUSH_INT (Source->ORDERED_TMSIS, 1);
		PUSH_INT (Source->BROADCAST_DONE, 1);
		/* Encode spare bits */
		PUSH_INT (0, 4);
		PUSH_INT (Source->ADD_LENGTH, 3);
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->ADD_PFIELD))->usedBits == (int) (8*Source->ADD_LENGTH));
		PUSH_BIN ((&(Source->ADD_PFIELD))->value, (&(Source->ADD_PFIELD))->usedBits);
		for (cnt=0; cnt<Source->page_records.items; cnt++) {
			CurrOfs += ENCODE_c_GPM_PDU_page_records_data (Buffer, CurrOfs, Source->page_records.data [cnt], pp_CS0004E_Details);
		}
		/* Standard f-csch PDU padding */
		CurrOfs = CS0004E_PDU_Padding_plus_2_Encode (Buffer, CurrOfs, pp_CS0004E_Details);
		
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_GPM_PDU (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GPM_PDU* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME GPM_PDU */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_f_csch_GPM_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int cnt;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		/* Mark the beginning of the PDU, to allow correct padding */
		pp_CS0004E_Details->n_PDU_START_OFFSET = CurrOfs;
		
		/* C.S0004 3.1.2.3.1.1 */
		bts = 2;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->PD___LOCATOR), CurrOfs, bts);
			Destin->PD = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 6;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->MSG_ID___LOCATOR), CurrOfs, bts);
			Destin->MSG_ID = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* GPM Common Fields */
		/* C.S0005 3.7.2.3.2.17 */
		bts = 6;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->CONFIG_MSG_SEQ___LOCATOR), CurrOfs, bts);
			Destin->CONFIG_MSG_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 6;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ACC_MSG_SEQ___LOCATOR), CurrOfs, bts);
			Destin->ACC_MSG_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->CLASS_0_DONE___LOCATOR), CurrOfs, bts);
			Destin->CLASS_0_DONE = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->CLASS_1_DONE___LOCATOR), CurrOfs, bts);
			Destin->CLASS_1_DONE = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->TMSI_DONE___LOCATOR), CurrOfs, bts);
			Destin->TMSI_DONE = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ORDERED_TMSIS___LOCATOR), CurrOfs, bts);
			Destin->ORDERED_TMSIS = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->BROADCAST_DONE___LOCATOR), CurrOfs, bts);
			Destin->BROADCAST_DONE = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* Decode spare bit(s) */
		bts = 4;
		if (LastOfs-CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 3;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ADD_LENGTH___LOCATOR), CurrOfs, bts);
			Destin->ADD_LENGTH = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = (8*Destin->ADD_LENGTH);
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ADD_PFIELD___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->ADD_PFIELD)))->value), (unsigned)(bts), &(((&(Destin->ADD_PFIELD)))->usedBits));
			EDCopyBits (((&(Destin->ADD_PFIELD))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* Decode field page_records - sequence */
		/* Decode field page_records - infinite sequence */
		for (cnt=0; ; cnt++) {
			ADDITEMS_c_GPM_PDU_page_records(&Destin->page_records, 1);
			bts = DECODE_c_GPM_PDU_page_records_data (Buffer, CurrOfs, Destin->page_records.data [cnt], LastOfs-CurrOfs , pp_CS0004E_Details);
			if (bts < 0) {
				/* Decoding failed - Remove the unused array items */
				SETITEMS_c_GPM_PDU_page_records (&Destin->page_records, cnt);
				goto exit_0;
			}
			CurrOfs += bts;
		}
		exit_0:
		/* Standard f-csch PDU padding */
		
		CurrOfs = CS0004E_PDU_Padding_plus_2_Decode (CurrOfs, LastOfs, pp_CS0004E_Details);
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_GPM_PDU_page_records_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GPM_PDU_page_records_data* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_GPM_Page_Record */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_f_csch_GPM_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* 3.1.2.2.1.1.1.1 Definition of Page Class Fields of a General Page Message */
		PUSH_INT (Source->PAGE_CLASS, 2);
		PUSH_INT (Source->PAGE_SUBCLASS, 2);
		/* Optional: see table Table 3.1.2.2.1.1.1.2-1. Added in Rev.7 but backwards compatible */
		if (((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS!=0))) {
			/* Field 'PAGE_SUBCLASS_EXT' is required */
			ED_ASSERT (GETPRESENT_c_GPM_PDU_page_records_data_PAGE_SUBCLASS_EXT(Source));
			PUSH_INT (Source->PAGE_SUBCLASS_EXT, 2);
		}
		else {
			/* Field 'PAGE_SUBCLASS_EXT' must be absent */
			ED_ASSERT (!GETPRESENT_c_GPM_PDU_page_records_data_PAGE_SUBCLASS_EXT(Source));
		}
		/* ARQ Fields, Section 3.1.2.1.1.1, only on mobile addressed fields */
		if ((Source->PAGE_CLASS!=3)) {
			/* Field 'MSG_SEQ' is required */
			ED_ASSERT (GETPRESENT_c_GPM_PDU_page_records_data_MSG_SEQ(Source));
			PUSH_INT (Source->MSG_SEQ, 3);
		}
		else {
			/* Field 'MSG_SEQ' must be absent */
			ED_ASSERT (!GETPRESENT_c_GPM_PDU_page_records_data_MSG_SEQ(Source));
		}
		/* Page Type-specific Fields, Section 3.1.2.2.1.1.2.1 */
		if ((((Source->PAGE_CLASS==1)&&(Source->PAGE_SUBCLASS==0))||((Source->PAGE_CLASS==1)&&(Source->PAGE_SUBCLASS==1)))) {
			/* Field 'IMSI_ADDR_NUM' is required */
			ED_ASSERT (GETPRESENT_c_GPM_PDU_page_records_data_IMSI_ADDR_NUM(Source));
			PUSH_INT (Source->IMSI_ADDR_NUM, 3);
		}
		else {
			/* Field 'IMSI_ADDR_NUM' must be absent */
			ED_ASSERT (!GETPRESENT_c_GPM_PDU_page_records_data_IMSI_ADDR_NUM(Source));
		}
		if (((((Source->PAGE_CLASS==0)&&(Source->PAGE_SUBCLASS==2))||((Source->PAGE_CLASS==0)&&(Source->PAGE_SUBCLASS==3)))||((Source->PAGE_CLASS==1)&&(Source->PAGE_SUBCLASS==1)))) {
			/* Field 'MCC' is required */
			ED_ASSERT (GETPRESENT_c_GPM_PDU_page_records_data_MCC(Source));
			PUSH_INT (Source->MCC, 10);
		}
		else {
			/* Field 'MCC' must be absent */
			ED_ASSERT (!GETPRESENT_c_GPM_PDU_page_records_data_MCC(Source));
		}
		if ((((((Source->PAGE_CLASS==0)&&(Source->PAGE_SUBCLASS==1))||((Source->PAGE_CLASS==0)&&(Source->PAGE_SUBCLASS==3)))||((Source->PAGE_CLASS==1)&&(Source->PAGE_SUBCLASS==0)))||((Source->PAGE_CLASS==1)&&(Source->PAGE_SUBCLASS==1)))) {
			/* Field 'IMSI_11_12' is required */
			ED_ASSERT (GETPRESENT_c_GPM_PDU_page_records_data_IMSI_11_12(Source));
			PUSH_INT (Source->IMSI_11_12, 7);
		}
		else {
			/* Field 'IMSI_11_12' must be absent */
			ED_ASSERT (!GETPRESENT_c_GPM_PDU_page_records_data_IMSI_11_12(Source));
		}
		if ((((((((Source->PAGE_CLASS==0)&&(Source->PAGE_SUBCLASS==0))||((Source->PAGE_CLASS==0)&&(Source->PAGE_SUBCLASS==1)))||((Source->PAGE_CLASS==0)&&(Source->PAGE_SUBCLASS==2)))||((Source->PAGE_CLASS==0)&&(Source->PAGE_SUBCLASS==3)))||((Source->PAGE_CLASS==1)&&(Source->PAGE_SUBCLASS==0)))||((Source->PAGE_CLASS==1)&&(Source->PAGE_SUBCLASS==1)))) {
			/* Field 'IMSI_S' is required */
			ED_ASSERT (GETPRESENT_c_GPM_PDU_page_records_data_IMSI_S(Source));
			PUSH_BIN (Source->IMSI_S, 34);
		}
		else {
			/* Field 'IMSI_S' must be absent */
			ED_ASSERT (!GETPRESENT_c_GPM_PDU_page_records_data_IMSI_S(Source));
		}
		if (((Source->PAGE_CLASS==2)&&(Source->PAGE_SUBCLASS==3))) {
			/* Field 'TMSI_ZONE_LEN' is required */
			ED_ASSERT (GETPRESENT_c_GPM_PDU_page_records_data_TMSI_ZONE_LEN(Source));
			PUSH_INT (Source->TMSI_ZONE_LEN, 4);
		}
		else {
			/* Field 'TMSI_ZONE_LEN' must be absent */
			ED_ASSERT (!GETPRESENT_c_GPM_PDU_page_records_data_TMSI_ZONE_LEN(Source));
		}
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->TMSI_ZONE))->usedBits == (int) ((((Source->PAGE_CLASS==2)&&(Source->PAGE_SUBCLASS==3))) ? ((8*(Source->TMSI_ZONE_LEN_Present ? Source->TMSI_ZONE_LEN : 0))) : (0)));
		PUSH_BIN ((&(Source->TMSI_ZONE))->value, (&(Source->TMSI_ZONE))->usedBits);
		if ((((Source->PAGE_CLASS==2)&&(Source->PAGE_SUBCLASS==0))||((Source->PAGE_CLASS==2)&&(Source->PAGE_SUBCLASS==3)))) {
			/* Field 'TMSI_CODE_ADDR_32' is required */
			ED_ASSERT (GETPRESENT_c_GPM_PDU_page_records_data_TMSI_CODE_ADDR_32(Source));
			PUSH_INT (Source->TMSI_CODE_ADDR_32, 32);
		}
		else {
			/* Field 'TMSI_CODE_ADDR_32' must be absent */
			ED_ASSERT (!GETPRESENT_c_GPM_PDU_page_records_data_TMSI_CODE_ADDR_32(Source));
		}
		if (((Source->PAGE_CLASS==2)&&(Source->PAGE_SUBCLASS==1))) {
			/* Field 'TMSI_CODE_ADDR_24' is required */
			ED_ASSERT (GETPRESENT_c_GPM_PDU_page_records_data_TMSI_CODE_ADDR_24(Source));
			PUSH_INT (Source->TMSI_CODE_ADDR_24, 24);
		}
		else {
			/* Field 'TMSI_CODE_ADDR_24' must be absent */
			ED_ASSERT (!GETPRESENT_c_GPM_PDU_page_records_data_TMSI_CODE_ADDR_24(Source));
		}
		if (((Source->PAGE_CLASS==2)&&(Source->PAGE_SUBCLASS==2))) {
			/* Field 'TMSI_CODE_ADDR_16' is required */
			ED_ASSERT (GETPRESENT_c_GPM_PDU_page_records_data_TMSI_CODE_ADDR_16(Source));
			PUSH_INT (Source->TMSI_CODE_ADDR_16, 16);
		}
		else {
			/* Field 'TMSI_CODE_ADDR_16' must be absent */
			ED_ASSERT (!GETPRESENT_c_GPM_PDU_page_records_data_TMSI_CODE_ADDR_16(Source));
		}
		if ((((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==0))||(((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==3))&&((Source->PAGE_SUBCLASS_EXT_Present ? Source->PAGE_SUBCLASS_EXT : 0)==0)))) {
			/* Field 'BURST_TYPE' is required */
			ED_ASSERT (GETPRESENT_c_GPM_PDU_page_records_data_BURST_TYPE(Source));
			PUSH_INT (Source->BURST_TYPE, 6);
		}
		else {
			/* Field 'BURST_TYPE' must be absent */
			ED_ASSERT (!GETPRESENT_c_GPM_PDU_page_records_data_BURST_TYPE(Source));
		}
		if ((((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==0))||(((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==3))&&((Source->PAGE_SUBCLASS_EXT_Present ? Source->PAGE_SUBCLASS_EXT : 0)==0)))) {
			/* Field 'ADDR_LEN' is required */
			ED_ASSERT (GETPRESENT_c_GPM_PDU_page_records_data_ADDR_LEN(Source));
			PUSH_INT (Source->ADDR_LEN, 4);
		}
		else {
			/* Field 'ADDR_LEN' must be absent */
			ED_ASSERT (!GETPRESENT_c_GPM_PDU_page_records_data_ADDR_LEN(Source));
		}
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->BC_ADDR))->usedBits == (int) (((((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==0))||(((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==3))&&((Source->PAGE_SUBCLASS_EXT_Present ? Source->PAGE_SUBCLASS_EXT : 0)==0)))) ? ((8*(Source->ADDR_LEN_Present ? Source->ADDR_LEN : 0))) : (0)));
		PUSH_BIN ((&(Source->BC_ADDR))->value, (&(Source->BC_ADDR))->usedBits);
		if ((((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==1))&&((Source->PAGE_SUBCLASS_EXT_Present ? Source->PAGE_SUBCLASS_EXT : 0)==3))) {
			/* Field 'LENGTH' is required */
			ED_ASSERT (GETPRESENT_c_GPM_PDU_page_records_data_LENGTH(Source));
			PUSH_INT (Source->LENGTH, 4);
		}
		else {
			/* Field 'LENGTH' must be absent */
			ED_ASSERT (!GETPRESENT_c_GPM_PDU_page_records_data_LENGTH(Source));
		}
		/* RESERVED */
		/* Encode spare bits */
		PUSH_INT (0, (((((((((((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==1))&&((Source->PAGE_SUBCLASS_EXT_Present ? Source->PAGE_SUBCLASS_EXT : 0)==0))) ? (32) : (0))+(((((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==1))&&((Source->PAGE_SUBCLASS_EXT_Present ? Source->PAGE_SUBCLASS_EXT : 0)==1))) ? (24) : (0)))+(((((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==1))&&((Source->PAGE_SUBCLASS_EXT_Present ? Source->PAGE_SUBCLASS_EXT : 0)==2))) ? (16) : (0)))+(((((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==1))&&((Source->PAGE_SUBCLASS_EXT_Present ? Source->PAGE_SUBCLASS_EXT : 0)==3))) ? (((8*(Source->LENGTH_Present ? Source->LENGTH : 0))+32)) : (0)))+(((((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==2))&&((Source->PAGE_SUBCLASS_EXT_Present ? Source->PAGE_SUBCLASS_EXT : 0)==0))) ? (32) : (0)))+(((((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==2))&&((Source->PAGE_SUBCLASS_EXT_Present ? Source->PAGE_SUBCLASS_EXT : 0)==1))) ? (68) : (0)))+(((((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==2))&&((Source->PAGE_SUBCLASS_EXT_Present ? Source->PAGE_SUBCLASS_EXT : 0)==2))) ? (76) : (0))));
		/* 3.1.2.3.1.7 Record-specific Fields */
		if ((Source->PAGE_CLASS!=3)) {
			/* Field 'SDU_INCLUDED' is required */
			ED_ASSERT (GETPRESENT_c_GPM_PDU_page_records_data_SDU_INCLUDED(Source));
			PUSH_INT (Source->SDU_INCLUDED, 1);
		}
		else {
			/* Field 'SDU_INCLUDED' must be absent */
			ED_ASSERT (!GETPRESENT_c_GPM_PDU_page_records_data_SDU_INCLUDED(Source));
		}
		/* Only on Mobile Addressed record */
		/* See Table 3.1.2.3.1.7.2-1, only on  */
		if ((((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==3))&&((Source->PAGE_SUBCLASS_EXT_Present ? Source->PAGE_SUBCLASS_EXT : 0)==0))) {
			/* Field 'EXT_BCAST_SDU_LENGTH_IND' is required */
			ED_ASSERT (GETPRESENT_c_GPM_PDU_page_records_data_EXT_BCAST_SDU_LENGTH_IND(Source));
			PUSH_INT (Source->EXT_BCAST_SDU_LENGTH_IND, 2);
		}
		else {
			/* Field 'EXT_BCAST_SDU_LENGTH_IND' must be absent */
			ED_ASSERT (!GETPRESENT_c_GPM_PDU_page_records_data_EXT_BCAST_SDU_LENGTH_IND(Source));
		}
		if ((Source->EXT_BCAST_SDU_LENGTH_IND_Present&&(((Source->EXT_BCAST_SDU_LENGTH_IND_Present ? Source->EXT_BCAST_SDU_LENGTH_IND : 0)==0)||((Source->EXT_BCAST_SDU_LENGTH_IND_Present ? Source->EXT_BCAST_SDU_LENGTH_IND : 0)==1)))) {
			/* Field 'EXT_BCAST_SDU_LENGTH' is required */
			ED_ASSERT (GETPRESENT_c_GPM_PDU_page_records_data_EXT_BCAST_SDU_LENGTH(Source));
			PUSH_INT (Source->EXT_BCAST_SDU_LENGTH, 4);
		}
		else {
			/* Field 'EXT_BCAST_SDU_LENGTH' must be absent */
			ED_ASSERT (!GETPRESENT_c_GPM_PDU_page_records_data_EXT_BCAST_SDU_LENGTH(Source));
		}
		/* SDU */
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->SDU))->usedBits == (int) (((Source->SDU_INCLUDED_Present&&((Source->SDU_INCLUDED_Present ? Source->SDU_INCLUDED : 0)==0))) ? (0) : ((((Source->SDU_INCLUDED_Present ? Source->SDU_INCLUDED : 0)) ? (16) : (((((Source->EXT_BCAST_SDU_LENGTH_IND_Present ? Source->EXT_BCAST_SDU_LENGTH_IND : 0)==0)) ? (13) : (((((Source->EXT_BCAST_SDU_LENGTH_IND_Present ? Source->EXT_BCAST_SDU_LENGTH_IND : 0)==0)) ? (18) : (((((Source->EXT_BCAST_SDU_LENGTH_IND_Present ? Source->EXT_BCAST_SDU_LENGTH_IND : 0)==0)) ? ((13+(8*(Source->EXT_BCAST_SDU_LENGTH_Present ? Source->EXT_BCAST_SDU_LENGTH : 0)))) : (((((Source->EXT_BCAST_SDU_LENGTH_IND_Present ? Source->EXT_BCAST_SDU_LENGTH_IND : 0)==0)) ? ((18+(8*(Source->EXT_BCAST_SDU_LENGTH_Present ? Source->EXT_BCAST_SDU_LENGTH : 0)))) : (0)))))))))))));
		PUSH_BIN ((&(Source->SDU))->value, (&(Source->SDU))->usedBits);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_GPM_PDU_page_records_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GPM_PDU_page_records_data* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_GPM_Page_Record */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_f_csch_GPM_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		/* 3.1.2.2.1.1.1.1 Definition of Page Class Fields of a General Page Message */
		bts = 2;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->PAGE_CLASS___LOCATOR), CurrOfs, bts);
			Destin->PAGE_CLASS = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 2;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->PAGE_SUBCLASS___LOCATOR), CurrOfs, bts);
			Destin->PAGE_SUBCLASS = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* Optional: see table Table 3.1.2.2.1.1.1.2-1. Added in Rev.7 but backwards compatible */
		if (((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS!=0))) {
			SETPRESENT_c_GPM_PDU_page_records_data_PAGE_SUBCLASS_EXT(Destin, ED_TRUE);
			bts = 2;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->PAGE_SUBCLASS_EXT___LOCATOR), CurrOfs, bts);
				Destin->PAGE_SUBCLASS_EXT = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_GPM_PDU_page_records_data_PAGE_SUBCLASS_EXT(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* ARQ Fields, Section 3.1.2.1.1.1, only on mobile addressed fields */
		if ((Destin->PAGE_CLASS!=3)) {
			SETPRESENT_c_GPM_PDU_page_records_data_MSG_SEQ(Destin, ED_TRUE);
			bts = 3;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->MSG_SEQ___LOCATOR), CurrOfs, bts);
				Destin->MSG_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_GPM_PDU_page_records_data_MSG_SEQ(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* Page Type-specific Fields, Section 3.1.2.2.1.1.2.1 */
		if ((((Destin->PAGE_CLASS==1)&&(Destin->PAGE_SUBCLASS==0))||((Destin->PAGE_CLASS==1)&&(Destin->PAGE_SUBCLASS==1)))) {
			SETPRESENT_c_GPM_PDU_page_records_data_IMSI_ADDR_NUM(Destin, ED_TRUE);
			bts = 3;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->IMSI_ADDR_NUM___LOCATOR), CurrOfs, bts);
				Destin->IMSI_ADDR_NUM = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_GPM_PDU_page_records_data_IMSI_ADDR_NUM(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((((Destin->PAGE_CLASS==0)&&(Destin->PAGE_SUBCLASS==2))||((Destin->PAGE_CLASS==0)&&(Destin->PAGE_SUBCLASS==3)))||((Destin->PAGE_CLASS==1)&&(Destin->PAGE_SUBCLASS==1)))) {
			SETPRESENT_c_GPM_PDU_page_records_data_MCC(Destin, ED_TRUE);
			bts = 10;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->MCC___LOCATOR), CurrOfs, bts);
				Destin->MCC = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_GPM_PDU_page_records_data_MCC(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((((((Destin->PAGE_CLASS==0)&&(Destin->PAGE_SUBCLASS==1))||((Destin->PAGE_CLASS==0)&&(Destin->PAGE_SUBCLASS==3)))||((Destin->PAGE_CLASS==1)&&(Destin->PAGE_SUBCLASS==0)))||((Destin->PAGE_CLASS==1)&&(Destin->PAGE_SUBCLASS==1)))) {
			SETPRESENT_c_GPM_PDU_page_records_data_IMSI_11_12(Destin, ED_TRUE);
			bts = 7;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->IMSI_11_12___LOCATOR), CurrOfs, bts);
				Destin->IMSI_11_12 = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_GPM_PDU_page_records_data_IMSI_11_12(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((((((((Destin->PAGE_CLASS==0)&&(Destin->PAGE_SUBCLASS==0))||((Destin->PAGE_CLASS==0)&&(Destin->PAGE_SUBCLASS==1)))||((Destin->PAGE_CLASS==0)&&(Destin->PAGE_SUBCLASS==2)))||((Destin->PAGE_CLASS==0)&&(Destin->PAGE_SUBCLASS==3)))||((Destin->PAGE_CLASS==1)&&(Destin->PAGE_SUBCLASS==0)))||((Destin->PAGE_CLASS==1)&&(Destin->PAGE_SUBCLASS==1)))) {
			SETPRESENT_c_GPM_PDU_page_records_data_IMSI_S(Destin, ED_TRUE);
			bts = 34;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->IMSI_S___LOCATOR), CurrOfs, bts);
				EDCopyBits (Destin->IMSI_S, 0, Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_GPM_PDU_page_records_data_IMSI_S(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((Destin->PAGE_CLASS==2)&&(Destin->PAGE_SUBCLASS==3))) {
			SETPRESENT_c_GPM_PDU_page_records_data_TMSI_ZONE_LEN(Destin, ED_TRUE);
			bts = 4;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->TMSI_ZONE_LEN___LOCATOR), CurrOfs, bts);
				Destin->TMSI_ZONE_LEN = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_GPM_PDU_page_records_data_TMSI_ZONE_LEN(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		bts = ((((Destin->PAGE_CLASS==2)&&(Destin->PAGE_SUBCLASS==3))) ? ((8*(Destin->TMSI_ZONE_LEN_Present ? Destin->TMSI_ZONE_LEN : 0))) : (0));
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->TMSI_ZONE___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->TMSI_ZONE)))->value), (unsigned)(bts), &(((&(Destin->TMSI_ZONE)))->usedBits));
			EDCopyBits (((&(Destin->TMSI_ZONE))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		if ((((Destin->PAGE_CLASS==2)&&(Destin->PAGE_SUBCLASS==0))||((Destin->PAGE_CLASS==2)&&(Destin->PAGE_SUBCLASS==3)))) {
			SETPRESENT_c_GPM_PDU_page_records_data_TMSI_CODE_ADDR_32(Destin, ED_TRUE);
			bts = 32;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->TMSI_CODE_ADDR_32___LOCATOR), CurrOfs, bts);
				Destin->TMSI_CODE_ADDR_32 = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_GPM_PDU_page_records_data_TMSI_CODE_ADDR_32(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((Destin->PAGE_CLASS==2)&&(Destin->PAGE_SUBCLASS==1))) {
			SETPRESENT_c_GPM_PDU_page_records_data_TMSI_CODE_ADDR_24(Destin, ED_TRUE);
			bts = 24;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->TMSI_CODE_ADDR_24___LOCATOR), CurrOfs, bts);
				Destin->TMSI_CODE_ADDR_24 = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_GPM_PDU_page_records_data_TMSI_CODE_ADDR_24(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((Destin->PAGE_CLASS==2)&&(Destin->PAGE_SUBCLASS==2))) {
			SETPRESENT_c_GPM_PDU_page_records_data_TMSI_CODE_ADDR_16(Destin, ED_TRUE);
			bts = 16;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->TMSI_CODE_ADDR_16___LOCATOR), CurrOfs, bts);
				Destin->TMSI_CODE_ADDR_16 = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_GPM_PDU_page_records_data_TMSI_CODE_ADDR_16(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==0))||(((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==3))&&((Destin->PAGE_SUBCLASS_EXT_Present ? Destin->PAGE_SUBCLASS_EXT : 0)==0)))) {
			SETPRESENT_c_GPM_PDU_page_records_data_BURST_TYPE(Destin, ED_TRUE);
			bts = 6;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->BURST_TYPE___LOCATOR), CurrOfs, bts);
				Destin->BURST_TYPE = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_GPM_PDU_page_records_data_BURST_TYPE(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==0))||(((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==3))&&((Destin->PAGE_SUBCLASS_EXT_Present ? Destin->PAGE_SUBCLASS_EXT : 0)==0)))) {
			SETPRESENT_c_GPM_PDU_page_records_data_ADDR_LEN(Destin, ED_TRUE);
			bts = 4;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->ADDR_LEN___LOCATOR), CurrOfs, bts);
				Destin->ADDR_LEN = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_GPM_PDU_page_records_data_ADDR_LEN(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		bts = (((((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==0))||(((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==3))&&((Destin->PAGE_SUBCLASS_EXT_Present ? Destin->PAGE_SUBCLASS_EXT : 0)==0)))) ? ((8*(Destin->ADDR_LEN_Present ? Destin->ADDR_LEN : 0))) : (0));
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->BC_ADDR___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->BC_ADDR)))->value), (unsigned)(bts), &(((&(Destin->BC_ADDR)))->usedBits));
			EDCopyBits (((&(Destin->BC_ADDR))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		if ((((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==1))&&((Destin->PAGE_SUBCLASS_EXT_Present ? Destin->PAGE_SUBCLASS_EXT : 0)==3))) {
			SETPRESENT_c_GPM_PDU_page_records_data_LENGTH(Destin, ED_TRUE);
			bts = 4;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->LENGTH___LOCATOR), CurrOfs, bts);
				Destin->LENGTH = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_GPM_PDU_page_records_data_LENGTH(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* RESERVED */
		/* Decode spare bit(s) */
		bts = (((((((((((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==1))&&((Destin->PAGE_SUBCLASS_EXT_Present ? Destin->PAGE_SUBCLASS_EXT : 0)==0))) ? (32) : (0))+(((((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==1))&&((Destin->PAGE_SUBCLASS_EXT_Present ? Destin->PAGE_SUBCLASS_EXT : 0)==1))) ? (24) : (0)))+(((((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==1))&&((Destin->PAGE_SUBCLASS_EXT_Present ? Destin->PAGE_SUBCLASS_EXT : 0)==2))) ? (16) : (0)))+(((((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==1))&&((Destin->PAGE_SUBCLASS_EXT_Present ? Destin->PAGE_SUBCLASS_EXT : 0)==3))) ? (((8*(Destin->LENGTH_Present ? Destin->LENGTH : 0))+32)) : (0)))+(((((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==2))&&((Destin->PAGE_SUBCLASS_EXT_Present ? Destin->PAGE_SUBCLASS_EXT : 0)==0))) ? (32) : (0)))+(((((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==2))&&((Destin->PAGE_SUBCLASS_EXT_Present ? Destin->PAGE_SUBCLASS_EXT : 0)==1))) ? (68) : (0)))+(((((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==2))&&((Destin->PAGE_SUBCLASS_EXT_Present ? Destin->PAGE_SUBCLASS_EXT : 0)==2))) ? (76) : (0)));
		if (LastOfs-CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* 3.1.2.3.1.7 Record-specific Fields */
		if ((Destin->PAGE_CLASS!=3)) {
			SETPRESENT_c_GPM_PDU_page_records_data_SDU_INCLUDED(Destin, ED_TRUE);
			bts = 1;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_INCLUDED___LOCATOR), CurrOfs, bts);
				Destin->SDU_INCLUDED = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_GPM_PDU_page_records_data_SDU_INCLUDED(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* Only on Mobile Addressed record */
		/* See Table 3.1.2.3.1.7.2-1, only on  */
		if ((((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==3))&&((Destin->PAGE_SUBCLASS_EXT_Present ? Destin->PAGE_SUBCLASS_EXT : 0)==0))) {
			SETPRESENT_c_GPM_PDU_page_records_data_EXT_BCAST_SDU_LENGTH_IND(Destin, ED_TRUE);
			bts = 2;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->EXT_BCAST_SDU_LENGTH_IND___LOCATOR), CurrOfs, bts);
				Destin->EXT_BCAST_SDU_LENGTH_IND = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_GPM_PDU_page_records_data_EXT_BCAST_SDU_LENGTH_IND(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((Destin->EXT_BCAST_SDU_LENGTH_IND_Present&&(((Destin->EXT_BCAST_SDU_LENGTH_IND_Present ? Destin->EXT_BCAST_SDU_LENGTH_IND : 0)==0)||((Destin->EXT_BCAST_SDU_LENGTH_IND_Present ? Destin->EXT_BCAST_SDU_LENGTH_IND : 0)==1)))) {
			SETPRESENT_c_GPM_PDU_page_records_data_EXT_BCAST_SDU_LENGTH(Destin, ED_TRUE);
			bts = 4;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->EXT_BCAST_SDU_LENGTH___LOCATOR), CurrOfs, bts);
				Destin->EXT_BCAST_SDU_LENGTH = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_GPM_PDU_page_records_data_EXT_BCAST_SDU_LENGTH(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* SDU */
		bts = (((Destin->SDU_INCLUDED_Present&&((Destin->SDU_INCLUDED_Present ? Destin->SDU_INCLUDED : 0)==0))) ? (0) : ((((Destin->SDU_INCLUDED_Present ? Destin->SDU_INCLUDED : 0)) ? (16) : (((((Destin->EXT_BCAST_SDU_LENGTH_IND_Present ? Destin->EXT_BCAST_SDU_LENGTH_IND : 0)==0)) ? (13) : (((((Destin->EXT_BCAST_SDU_LENGTH_IND_Present ? Destin->EXT_BCAST_SDU_LENGTH_IND : 0)==0)) ? (18) : (((((Destin->EXT_BCAST_SDU_LENGTH_IND_Present ? Destin->EXT_BCAST_SDU_LENGTH_IND : 0)==0)) ? ((13+(8*(Destin->EXT_BCAST_SDU_LENGTH_Present ? Destin->EXT_BCAST_SDU_LENGTH : 0)))) : (((((Destin->EXT_BCAST_SDU_LENGTH_IND_Present ? Destin->EXT_BCAST_SDU_LENGTH_IND : 0)==0)) ? ((18+(8*(Destin->EXT_BCAST_SDU_LENGTH_Present ? Destin->EXT_BCAST_SDU_LENGTH : 0)))) : (0))))))))))));
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->SDU___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->SDU)))->value), (unsigned)(bts), &(((&(Destin->SDU)))->usedBits));
			EDCopyBits (((&(Destin->SDU))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_UPM_PDU (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_UPM_PDU* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME UPM_PDU */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_f_csch_UPM_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* Mark the beginning of the PDU, to allow correct padding */
		pp_CS0004E_Details->n_PDU_START_OFFSET = CurrOfs;
		
		/* C.S0004 3.1.2.3.1.1 */
		PUSH_INT (Source->PD, 2);
		PUSH_INT (Source->MSG_ID, 6);
		/* Available only in middle (100101) and final (100110) segmented PDUs */
		if (((Source->MSG_ID==37)||(Source->MSG_ID==38))) {
			/* Field 'UPM_SEGMENT_SEQ' is required */
			ED_ASSERT (GETPRESENT_c_UPM_PDU_UPM_SEGMENT_SEQ(Source));
			PUSH_INT (Source->UPM_SEGMENT_SEQ, 2);
		}
		else {
			/* Field 'UPM_SEGMENT_SEQ' must be absent */
			ED_ASSERT (!GETPRESENT_c_UPM_PDU_UPM_SEGMENT_SEQ(Source));
		}
		PUSH_BIN ((&(Source->Universal_Page_Block))->value, (&(Source->Universal_Page_Block))->usedBits);
		/* Standard f-csch PDU padding */
		CurrOfs = CS0004E_PDU_Padding_plus_2_Encode (Buffer, CurrOfs, pp_CS0004E_Details);
		
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_UPM_PDU (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_UPM_PDU* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME UPM_PDU */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_f_csch_UPM_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		/* Mark the beginning of the PDU, to allow correct padding */
		pp_CS0004E_Details->n_PDU_START_OFFSET = CurrOfs;
		
		/* C.S0004 3.1.2.3.1.1 */
		bts = 2;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->PD___LOCATOR), CurrOfs, bts);
			Destin->PD = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 6;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->MSG_ID___LOCATOR), CurrOfs, bts);
			Destin->MSG_ID = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* Available only in middle (100101) and final (100110) segmented PDUs */
		if (((Destin->MSG_ID==37)||(Destin->MSG_ID==38))) {
			SETPRESENT_c_UPM_PDU_UPM_SEGMENT_SEQ(Destin, ED_TRUE);
			bts = 2;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->UPM_SEGMENT_SEQ___LOCATOR), CurrOfs, bts);
				Destin->UPM_SEGMENT_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_UPM_PDU_UPM_SEGMENT_SEQ(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		bts = (int)(LastOfs-CurrOfs);
		ED_LOCATOR_SET (&(Destin->Universal_Page_Block___LOCATOR), CurrOfs, bts);
		EDAllocBinary (&(((&(Destin->Universal_Page_Block)))->value), (unsigned)bts, &(((&(Destin->Universal_Page_Block)))->usedBits));
		EDCopyBits (((&(Destin->Universal_Page_Block))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* Standard f-csch PDU padding */
		
		CurrOfs = CS0004E_PDU_Padding_plus_2_Decode (CurrOfs, LastOfs, pp_CS0004E_Details);
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_Universal_Page_Block (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_Universal_Page_Block* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_Universal_Page_Block */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_f_csch_Universal_Page_Block
		assert (0); /* Encode excluded */
		return 0;
#else
		int max=0;
		int cnt;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* Reset exported tag 22 'NUM_BCAST' */
		pp_CS0004E_Details->userTagPresent[0] = 0;
		pp_CS0004E_Details->userTag[0] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[0], "f_csch_Universal_Page_Block", "NUM_BCAST");
		pp_CS0004E_Details->userTagBusy[0] = 1;
#endif
		/* Reset exported tag 23 'NUM_IMSI' */
		pp_CS0004E_Details->userTagPresent[1] = 0;
		pp_CS0004E_Details->userTag[1] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[1], "f_csch_Universal_Page_Block", "NUM_IMSI");
		pp_CS0004E_Details->userTagBusy[1] = 1;
#endif
		/* Reset exported tag 24 'NUM_TMSI' */
		pp_CS0004E_Details->userTagPresent[2] = 0;
		pp_CS0004E_Details->userTag[2] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[2], "f_csch_Universal_Page_Block", "NUM_TMSI");
		pp_CS0004E_Details->userTagBusy[2] = 1;
#endif
		/* Reset exported tag 25 'NUM_RESERVED_TYPE' */
		pp_CS0004E_Details->userTagPresent[3] = 0;
		pp_CS0004E_Details->userTag[3] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[3], "f_csch_Universal_Page_Block", "NUM_RESERVED_TYPE");
		pp_CS0004E_Details->userTagBusy[3] = 1;
#endif
		/* UPM Common Fields */
		PUSH_INT (Source->CONFIG_MSG_SEQ, 6);
		PUSH_INT (Source->ACC_MSG_SEQ, 6);
		PUSH_INT (Source->READ_NEXT_SLOT, 1);
		PUSH_INT (Source->READ_NEXT_SLOT_BCAST, 1);
		/* 3.1.2.2.1.2.1.1, Interleaved Address Fields */
		PUSH_INT (Source->BCAST_INCLUDED, 1);
		if (Source->BCAST_INCLUDED) {
			/* Field 'NUM_BCAST' is required */
			ED_ASSERT (GETPRESENT_c_f_csch_Universal_Page_Block_NUM_BCAST(Source));
			PUSH_INT (Source->NUM_BCAST, 5);
			/* Set the exported tag */
			pp_CS0004E_Details->userTagPresent[0] = 1;
			pp_CS0004E_Details->userTag[0] = (int)Source->NUM_BCAST;
		}
		else {
			/* Field 'NUM_BCAST' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_csch_Universal_Page_Block_NUM_BCAST(Source));
		}
		PUSH_INT (Source->IMSI_INCLUDED, 1);
		if (Source->IMSI_INCLUDED) {
			/* Field 'NUM_IMSI' is required */
			ED_ASSERT (GETPRESENT_c_f_csch_Universal_Page_Block_NUM_IMSI(Source));
			PUSH_INT (Source->NUM_IMSI, 6);
			/* Set the exported tag */
			pp_CS0004E_Details->userTagPresent[1] = 1;
			pp_CS0004E_Details->userTag[1] = (int)Source->NUM_IMSI;
		}
		else {
			/* Field 'NUM_IMSI' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_csch_Universal_Page_Block_NUM_IMSI(Source));
		}
		PUSH_INT (Source->TMSI_INCLUDED, 1);
		if (Source->TMSI_INCLUDED) {
			/* Field 'NUM_TMSI' is required */
			ED_ASSERT (GETPRESENT_c_f_csch_Universal_Page_Block_NUM_TMSI(Source));
			PUSH_INT (Source->NUM_TMSI, 6);
			/* Set the exported tag */
			pp_CS0004E_Details->userTagPresent[2] = 1;
			pp_CS0004E_Details->userTag[2] = (int)Source->NUM_TMSI;
		}
		else {
			/* Field 'NUM_TMSI' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_csch_Universal_Page_Block_NUM_TMSI(Source));
		}
		PUSH_INT (Source->RESERVED_TYPE_INCLUDED, 1);
		if (Source->RESERVED_TYPE_INCLUDED) {
			/* Field 'NUM_RESERVED_TYPE' is required */
			ED_ASSERT (GETPRESENT_c_f_csch_Universal_Page_Block_NUM_RESERVED_TYPE(Source));
			PUSH_INT (Source->NUM_RESERVED_TYPE, 6);
			/* Set the exported tag */
			pp_CS0004E_Details->userTagPresent[3] = 1;
			pp_CS0004E_Details->userTag[3] = (int)Source->NUM_RESERVED_TYPE;
		}
		else {
			/* Field 'NUM_RESERVED_TYPE' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_csch_Universal_Page_Block_NUM_RESERVED_TYPE(Source));
		}
		/* If NUM_BCAST is included, NUM_BCAST plus one occurrences of the following field are included: */
		max = ((Source->NUM_BCAST_Present) ? (((Source->NUM_BCAST_Present ? Source->NUM_BCAST : 0)+1)) : (0));
		ED_ASSERT (max == Source->BURST_TYPE.items);
		if (Source->BURST_TYPE.items < max) max = Source->BURST_TYPE.items;
		for (cnt=0; cnt<max; cnt++) {
			PUSH_INT (Source->BURST_TYPE.data [cnt], 6);
		}
		max = 16;
		ED_ASSERT (max == Source->SUBRECORD.items);
		if (Source->SUBRECORD.items < max) max = Source->SUBRECORD.items;
		for (cnt=0; cnt<max; cnt++) {
			CurrOfs += ENCODE_c_f_csch_Universal_Page_Block_SUBRECORD_data (Buffer, CurrOfs, Source->SUBRECORD.data [cnt], pp_CS0004E_Details);
		}
		for (cnt=0; cnt<Source->page_records.items; cnt++) {
			CurrOfs += ENCODE_c_f_csch_Universal_Page_Block_page_records_data (Buffer, CurrOfs, Source->page_records.data [cnt], pp_CS0004E_Details);
		}
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[0], "f_csch_Universal_Page_Block", "NUM_BCAST");
		pp_CS0004E_Details->userTagBusy[0] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[1], "f_csch_Universal_Page_Block", "NUM_IMSI");
		pp_CS0004E_Details->userTagBusy[1] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[2], "f_csch_Universal_Page_Block", "NUM_TMSI");
		pp_CS0004E_Details->userTagBusy[2] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[3], "f_csch_Universal_Page_Block", "NUM_RESERVED_TYPE");
		pp_CS0004E_Details->userTagBusy[3] = 0;
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_Universal_Page_Block (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_Universal_Page_Block* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_Universal_Page_Block */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_f_csch_Universal_Page_Block
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int cnt;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		/* Reset exported tag 22 'NUM_BCAST' */
		pp_CS0004E_Details->userTagPresent[0] = 0;
		pp_CS0004E_Details->userTag[0] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[0], "f_csch_Universal_Page_Block", "NUM_BCAST");
		pp_CS0004E_Details->userTagBusy[0] = 1;
#endif
		/* Reset exported tag 23 'NUM_IMSI' */
		pp_CS0004E_Details->userTagPresent[1] = 0;
		pp_CS0004E_Details->userTag[1] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[1], "f_csch_Universal_Page_Block", "NUM_IMSI");
		pp_CS0004E_Details->userTagBusy[1] = 1;
#endif
		/* Reset exported tag 24 'NUM_TMSI' */
		pp_CS0004E_Details->userTagPresent[2] = 0;
		pp_CS0004E_Details->userTag[2] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[2], "f_csch_Universal_Page_Block", "NUM_TMSI");
		pp_CS0004E_Details->userTagBusy[2] = 1;
#endif
		/* Reset exported tag 25 'NUM_RESERVED_TYPE' */
		pp_CS0004E_Details->userTagPresent[3] = 0;
		pp_CS0004E_Details->userTag[3] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[3], "f_csch_Universal_Page_Block", "NUM_RESERVED_TYPE");
		pp_CS0004E_Details->userTagBusy[3] = 1;
#endif
		/* UPM Common Fields */
		bts = 6;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->CONFIG_MSG_SEQ___LOCATOR), CurrOfs, bts);
			Destin->CONFIG_MSG_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 6;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ACC_MSG_SEQ___LOCATOR), CurrOfs, bts);
			Destin->ACC_MSG_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->READ_NEXT_SLOT___LOCATOR), CurrOfs, bts);
			Destin->READ_NEXT_SLOT = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->READ_NEXT_SLOT_BCAST___LOCATOR), CurrOfs, bts);
			Destin->READ_NEXT_SLOT_BCAST = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* 3.1.2.2.1.2.1.1, Interleaved Address Fields */
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->BCAST_INCLUDED___LOCATOR), CurrOfs, bts);
			Destin->BCAST_INCLUDED = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		if (Destin->BCAST_INCLUDED) {
			SETPRESENT_c_f_csch_Universal_Page_Block_NUM_BCAST(Destin, ED_TRUE);
			bts = 5;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->NUM_BCAST___LOCATOR), CurrOfs, bts);
				Destin->NUM_BCAST = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
				/* Set the exported tag */
				pp_CS0004E_Details->userTagPresent[0] = 1;
				pp_CS0004E_Details->userTag[0] = (int)Destin->NUM_BCAST;
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_csch_Universal_Page_Block_NUM_BCAST(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_INCLUDED___LOCATOR), CurrOfs, bts);
			Destin->IMSI_INCLUDED = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		if (Destin->IMSI_INCLUDED) {
			SETPRESENT_c_f_csch_Universal_Page_Block_NUM_IMSI(Destin, ED_TRUE);
			bts = 6;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->NUM_IMSI___LOCATOR), CurrOfs, bts);
				Destin->NUM_IMSI = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
				/* Set the exported tag */
				pp_CS0004E_Details->userTagPresent[1] = 1;
				pp_CS0004E_Details->userTag[1] = (int)Destin->NUM_IMSI;
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_csch_Universal_Page_Block_NUM_IMSI(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->TMSI_INCLUDED___LOCATOR), CurrOfs, bts);
			Destin->TMSI_INCLUDED = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		if (Destin->TMSI_INCLUDED) {
			SETPRESENT_c_f_csch_Universal_Page_Block_NUM_TMSI(Destin, ED_TRUE);
			bts = 6;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->NUM_TMSI___LOCATOR), CurrOfs, bts);
				Destin->NUM_TMSI = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
				/* Set the exported tag */
				pp_CS0004E_Details->userTagPresent[2] = 1;
				pp_CS0004E_Details->userTag[2] = (int)Destin->NUM_TMSI;
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_csch_Universal_Page_Block_NUM_TMSI(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->RESERVED_TYPE_INCLUDED___LOCATOR), CurrOfs, bts);
			Destin->RESERVED_TYPE_INCLUDED = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		if (Destin->RESERVED_TYPE_INCLUDED) {
			SETPRESENT_c_f_csch_Universal_Page_Block_NUM_RESERVED_TYPE(Destin, ED_TRUE);
			bts = 6;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->NUM_RESERVED_TYPE___LOCATOR), CurrOfs, bts);
				Destin->NUM_RESERVED_TYPE = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
				/* Set the exported tag */
				pp_CS0004E_Details->userTagPresent[3] = 1;
				pp_CS0004E_Details->userTag[3] = (int)Destin->NUM_RESERVED_TYPE;
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_csch_Universal_Page_Block_NUM_RESERVED_TYPE(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* If NUM_BCAST is included, NUM_BCAST plus one occurrences of the following field are included: */
		/* Decode field BURST_TYPE - sequence */
		SETITEMS_c_f_csch_Universal_Page_Block_BURST_TYPE(&Destin->BURST_TYPE, ((Destin->NUM_BCAST_Present) ? (((Destin->NUM_BCAST_Present ? Destin->NUM_BCAST : 0)+1)) : (0)));
		for (cnt=0; cnt<Destin->BURST_TYPE.items; cnt++) {
			bts = 6;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->BURST_TYPE.data___LOCATOR[cnt]), CurrOfs, bts);
				Destin->BURST_TYPE.data [cnt] = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* Decoding failed - Remove the unused array items */
				SETITEMS_c_f_csch_Universal_Page_Block_BURST_TYPE (&Destin->BURST_TYPE, cnt);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* Decode field SUBRECORD - sequence */
		SETITEMS_c_f_csch_Universal_Page_Block_SUBRECORD(&Destin->SUBRECORD, 16);
		for (cnt=0; cnt<Destin->SUBRECORD.items; cnt++) {
			bts = DECODE_c_f_csch_Universal_Page_Block_SUBRECORD_data (Buffer, CurrOfs, Destin->SUBRECORD.data [cnt], LastOfs-CurrOfs , pp_CS0004E_Details);
			if (bts < 0) {
				/* Decoding failed - Remove the unused array items */
				SETITEMS_c_f_csch_Universal_Page_Block_SUBRECORD (&Destin->SUBRECORD, cnt);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* Decode field page_records - sequence */
		/* Decode field page_records - infinite sequence */
		for (cnt=0; ; cnt++) {
			ADDITEMS_c_f_csch_Universal_Page_Block_page_records(&Destin->page_records, 1);
			bts = DECODE_c_f_csch_Universal_Page_Block_page_records_data (Buffer, CurrOfs, Destin->page_records.data [cnt], LastOfs-CurrOfs , pp_CS0004E_Details);
			if (bts < 0) {
				/* Decoding failed - Remove the unused array items */
				SETITEMS_c_f_csch_Universal_Page_Block_page_records (&Destin->page_records, cnt);
				goto exit_0;
			}
			CurrOfs += bts;
		}
		exit_0:
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[0], "f_csch_Universal_Page_Block", "NUM_BCAST");
		pp_CS0004E_Details->userTagBusy[0] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[1], "f_csch_Universal_Page_Block", "NUM_IMSI");
		pp_CS0004E_Details->userTagBusy[1] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[2], "f_csch_Universal_Page_Block", "NUM_TMSI");
		pp_CS0004E_Details->userTagBusy[2] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[3], "f_csch_Universal_Page_Block", "NUM_RESERVED_TYPE");
		pp_CS0004E_Details->userTagBusy[3] = 0;
#endif
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[0], "f_csch_Universal_Page_Block", "NUM_BCAST");
		pp_CS0004E_Details->userTagBusy[0] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[1], "f_csch_Universal_Page_Block", "NUM_IMSI");
		pp_CS0004E_Details->userTagBusy[1] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[2], "f_csch_Universal_Page_Block", "NUM_TMSI");
		pp_CS0004E_Details->userTagBusy[2] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[3], "f_csch_Universal_Page_Block", "NUM_RESERVED_TYPE");
		pp_CS0004E_Details->userTagBusy[3] = 0;
#endif
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_Universal_Page_Block_SUBRECORD_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_Universal_Page_Block_SUBRECORD_data* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_Interleaved_Address_Fields_SubRecord */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_f_csch_Universal_Page_Block
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->BC_ADDR_BLOCK))->usedBits == (int) (((pp_CS0004E_Details->userTagPresent[0])) ? (((pp_CS0004E_Details->userTag[0])+1)) : (0)));
		PUSH_BIN ((&(Source->BC_ADDR_BLOCK))->value, (&(Source->BC_ADDR_BLOCK))->usedBits);
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->IMSI_ADDR_BLOCK))->usedBits == (int) (((pp_CS0004E_Details->userTagPresent[1])) ? (((pp_CS0004E_Details->userTag[1])+1)) : (0)));
		PUSH_BIN ((&(Source->IMSI_ADDR_BLOCK))->value, (&(Source->IMSI_ADDR_BLOCK))->usedBits);
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->TMSI_ADDR_BLOCK))->usedBits == (int) (((pp_CS0004E_Details->userTagPresent[2])) ? (((pp_CS0004E_Details->userTag[2])+1)) : (0)));
		PUSH_BIN ((&(Source->TMSI_ADDR_BLOCK))->value, (&(Source->TMSI_ADDR_BLOCK))->usedBits);
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->RESERVED_ADDR_BLOCK))->usedBits == (int) (((pp_CS0004E_Details->userTagPresent[3])) ? (((pp_CS0004E_Details->userTag[3])+1)) : (0)));
		PUSH_BIN ((&(Source->RESERVED_ADDR_BLOCK))->value, (&(Source->RESERVED_ADDR_BLOCK))->usedBits);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_Universal_Page_Block_SUBRECORD_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_Universal_Page_Block_SUBRECORD_data* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_Interleaved_Address_Fields_SubRecord */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_f_csch_Universal_Page_Block
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = (((pp_CS0004E_Details->userTagPresent[0])) ? (((pp_CS0004E_Details->userTag[0])+1)) : (0));
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->BC_ADDR_BLOCK___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->BC_ADDR_BLOCK)))->value), (unsigned)(bts), &(((&(Destin->BC_ADDR_BLOCK)))->usedBits));
			EDCopyBits (((&(Destin->BC_ADDR_BLOCK))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = (((pp_CS0004E_Details->userTagPresent[1])) ? (((pp_CS0004E_Details->userTag[1])+1)) : (0));
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_ADDR_BLOCK___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->IMSI_ADDR_BLOCK)))->value), (unsigned)(bts), &(((&(Destin->IMSI_ADDR_BLOCK)))->usedBits));
			EDCopyBits (((&(Destin->IMSI_ADDR_BLOCK))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = (((pp_CS0004E_Details->userTagPresent[2])) ? (((pp_CS0004E_Details->userTag[2])+1)) : (0));
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->TMSI_ADDR_BLOCK___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->TMSI_ADDR_BLOCK)))->value), (unsigned)(bts), &(((&(Destin->TMSI_ADDR_BLOCK)))->usedBits));
			EDCopyBits (((&(Destin->TMSI_ADDR_BLOCK))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = (((pp_CS0004E_Details->userTagPresent[3])) ? (((pp_CS0004E_Details->userTag[3])+1)) : (0));
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->RESERVED_ADDR_BLOCK___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->RESERVED_ADDR_BLOCK)))->value), (unsigned)(bts), &(((&(Destin->RESERVED_ADDR_BLOCK)))->usedBits));
			EDCopyBits (((&(Destin->RESERVED_ADDR_BLOCK))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_Universal_Page_Block_page_records_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_Universal_Page_Block_page_records_data* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_UPM_Page_Record */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_f_csch_Universal_Page_Block
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* Page Class Fields 3.1.2.2.1.2.2.1 */
		PUSH_INT (Source->PAGE_CLASS, 2);
		PUSH_INT (Source->PAGE_SUBCLASS, 2);
		/* Optional: see table Table 3.1.2.2.1.1.1.2-1 */
		if (((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS!=0))) {
			/* Field 'PAGE_SUBCLASS_EXT' is required */
			ED_ASSERT (GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_PAGE_SUBCLASS_EXT(Source));
			PUSH_INT (Source->PAGE_SUBCLASS_EXT, 2);
		}
		else {
			/* Field 'PAGE_SUBCLASS_EXT' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_PAGE_SUBCLASS_EXT(Source));
		}
		/* ARQ Fields, Section 3.1.2.1.1.1, only on mobile addressed fields */
		if ((Source->PAGE_CLASS!=3)) {
			/* Field 'MSG_SEQ' is required */
			ED_ASSERT (GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_MSG_SEQ(Source));
			PUSH_INT (Source->MSG_SEQ, 3);
		}
		else {
			/* Field 'MSG_SEQ' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_MSG_SEQ(Source));
		}
		/* Page Type-specific Fields, Section 3.1.2.2.1.2.3.1 */
		if ((((Source->PAGE_CLASS==1)&&(Source->PAGE_SUBCLASS==0))||((Source->PAGE_CLASS==1)&&(Source->PAGE_SUBCLASS==1)))) {
			/* Field 'IMSI_ADDR_NUM' is required */
			ED_ASSERT (GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_IMSI_ADDR_NUM(Source));
			PUSH_INT (Source->IMSI_ADDR_NUM, 3);
		}
		else {
			/* Field 'IMSI_ADDR_NUM' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_IMSI_ADDR_NUM(Source));
		}
		if (((((Source->PAGE_CLASS==0)&&(Source->PAGE_SUBCLASS==2))||((Source->PAGE_CLASS==0)&&(Source->PAGE_SUBCLASS==3)))||((Source->PAGE_CLASS==1)&&(Source->PAGE_SUBCLASS==1)))) {
			/* Field 'MCC' is required */
			ED_ASSERT (GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_MCC(Source));
			PUSH_INT (Source->MCC, 10);
		}
		else {
			/* Field 'MCC' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_MCC(Source));
		}
		if ((((Source->PAGE_CLASS==0)&&(Source->PAGE_SUBCLASS==1))||((((Source->PAGE_CLASS==0)&&(Source->PAGE_SUBCLASS==3))||((Source->PAGE_CLASS==1)&&(Source->PAGE_SUBCLASS==0)))||((Source->PAGE_CLASS==1)&&(Source->PAGE_SUBCLASS==1))))) {
			/* Field 'IMSI_11_12' is required */
			ED_ASSERT (GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_IMSI_11_12(Source));
			PUSH_INT (Source->IMSI_11_12, 7);
		}
		else {
			/* Field 'IMSI_11_12' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_IMSI_11_12(Source));
		}
		if ((((((((Source->PAGE_CLASS==0)&&(Source->PAGE_SUBCLASS==0))||((Source->PAGE_CLASS==0)&&(Source->PAGE_SUBCLASS==1)))||((Source->PAGE_CLASS==0)&&(Source->PAGE_SUBCLASS==2)))||((Source->PAGE_CLASS==0)&&(Source->PAGE_SUBCLASS==3)))||((Source->PAGE_CLASS==1)&&(Source->PAGE_SUBCLASS==0)))||((Source->PAGE_CLASS==1)&&(Source->PAGE_SUBCLASS==1)))) {
			/* Field 'IMSI_S_33_16' is required */
			ED_ASSERT (GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_IMSI_S_33_16(Source));
			PUSH_INT (Source->IMSI_S_33_16, 18);
		}
		else {
			/* Field 'IMSI_S_33_16' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_IMSI_S_33_16(Source));
		}
		if (((Source->PAGE_CLASS==2)&&(Source->PAGE_SUBCLASS==3))) {
			/* Field 'TMSI_ZONE_LEN' is required */
			ED_ASSERT (GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_TMSI_ZONE_LEN(Source));
			PUSH_INT (Source->TMSI_ZONE_LEN, 4);
		}
		else {
			/* Field 'TMSI_ZONE_LEN' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_TMSI_ZONE_LEN(Source));
		}
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->TMSI_ZONE))->usedBits == (int) ((((Source->PAGE_CLASS==2)&&(Source->PAGE_SUBCLASS==3))) ? ((8*(Source->TMSI_ZONE_LEN_Present ? Source->TMSI_ZONE_LEN : 0))) : (0)));
		PUSH_BIN ((&(Source->TMSI_ZONE))->value, (&(Source->TMSI_ZONE))->usedBits);
		if ((((Source->PAGE_CLASS==2)&&(Source->PAGE_SUBCLASS==0))||((Source->PAGE_CLASS==2)&&(Source->PAGE_SUBCLASS==3)))) {
			/* Field 'TMSI_CODE_ADDR_31_16' is required */
			ED_ASSERT (GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_TMSI_CODE_ADDR_31_16(Source));
			PUSH_INT (Source->TMSI_CODE_ADDR_31_16, 16);
		}
		else {
			/* Field 'TMSI_CODE_ADDR_31_16' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_TMSI_CODE_ADDR_31_16(Source));
		}
		if (((Source->PAGE_CLASS==2)&&(Source->PAGE_SUBCLASS==1))) {
			/* Field 'TMSI_CODE_ADDR_23_16' is required */
			ED_ASSERT (GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_TMSI_CODE_ADDR_23_16(Source));
			PUSH_INT (Source->TMSI_CODE_ADDR_23_16, 8);
		}
		else {
			/* Field 'TMSI_CODE_ADDR_23_16' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_TMSI_CODE_ADDR_23_16(Source));
		}
		if ((((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==3))&&((Source->PAGE_SUBCLASS_EXT_Present ? Source->PAGE_SUBCLASS_EXT : 0)==0))) {
			/* Field 'ADDR_LEN' is required */
			ED_ASSERT (GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_ADDR_LEN(Source));
			PUSH_INT (Source->ADDR_LEN, 4);
		}
		else {
			/* Field 'ADDR_LEN' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_ADDR_LEN(Source));
		}
		if ((((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==3))&&((Source->PAGE_SUBCLASS_EXT_Present ? Source->PAGE_SUBCLASS_EXT : 0)==0))) {
			/* Field 'BC_ADDR_REMAINDER' is required */
			ED_ASSERT (GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_BC_ADDR_REMAINDER(Source));
			/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=1 */
			ED_ASSERT (Source->BC_ADDR_REMAINDER->usedBits == (int) (8*((Source->ADDR_LEN_Present ? Source->ADDR_LEN : 0)-2)));
			PUSH_BIN (Source->BC_ADDR_REMAINDER->value, Source->BC_ADDR_REMAINDER->usedBits);
		}
		else {
			/* Field 'BC_ADDR_REMAINDER' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_BC_ADDR_REMAINDER(Source));
		}
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->RESERVED_LEN))->usedBits == (int) (((((((Source->PAGE_CLASS==1)&&(Source->PAGE_SUBCLASS==2))||((Source->PAGE_CLASS==1)&&(Source->PAGE_SUBCLASS==3)))||(((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==2))&&((Source->PAGE_SUBCLASS_EXT_Present ? Source->PAGE_SUBCLASS_EXT : 0)==3)))||(((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==3))&&((Source->PAGE_SUBCLASS_EXT_Present ? Source->PAGE_SUBCLASS_EXT : 0)==3)))) ? (5) : ((((((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==1))&&((Source->PAGE_SUBCLASS_EXT_Present ? Source->PAGE_SUBCLASS_EXT : 0)==3))) ? (4) : (0)))));
		PUSH_BIN ((&(Source->RESERVED_LEN))->value, (&(Source->RESERVED_LEN))->usedBits);
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->RESERVED))->usedBits == (int) (((((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==1))&&((Source->PAGE_SUBCLASS_EXT_Present ? Source->PAGE_SUBCLASS_EXT : 0)==1))) ? (8) : (((((((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==2))&&((Source->PAGE_SUBCLASS_EXT_Present ? Source->PAGE_SUBCLASS_EXT : 0)==0))||(((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==1))&&((Source->PAGE_SUBCLASS_EXT_Present ? Source->PAGE_SUBCLASS_EXT : 0)==0)))) ? (16) : ((((((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==2))&&((Source->PAGE_SUBCLASS_EXT_Present ? Source->PAGE_SUBCLASS_EXT : 0)==1))) ? (52) : ((((((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==2))&&((Source->PAGE_SUBCLASS_EXT_Present ? Source->PAGE_SUBCLASS_EXT : 0)==2))) ? (60) : ((((((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==1))&&((Source->PAGE_SUBCLASS_EXT_Present ? Source->PAGE_SUBCLASS_EXT : 0)==3))) ? (((8*EDBitsToInt (Source->RESERVED_LEN.value, 0, Source->RESERVED_LEN.usedBits) /*ISPOINTER=0*/)+16)) : ((((((((Source->PAGE_CLASS==1)&&(Source->PAGE_SUBCLASS==2))||((Source->PAGE_CLASS==1)&&(Source->PAGE_SUBCLASS==3)))||(((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==2))&&((Source->PAGE_SUBCLASS_EXT_Present ? Source->PAGE_SUBCLASS_EXT : 0)==3)))||(((Source->PAGE_CLASS==3)&&(Source->PAGE_SUBCLASS==3))&&((Source->PAGE_SUBCLASS_EXT_Present ? Source->PAGE_SUBCLASS_EXT : 0)==3)))) ? ((8*EDBitsToInt (Source->RESERVED_LEN.value, 0, Source->RESERVED_LEN.usedBits) /*ISPOINTER=0*/)) : (0)))))))))))));
		PUSH_BIN ((&(Source->RESERVED))->value, (&(Source->RESERVED))->usedBits);
		/* Record-specific Fields 3.1.2.3.1.7.1 - for Mobile Station-addressed records */
		if ((Source->PAGE_CLASS!=3)) {
			/* Field 'EXT_MS_SDU_LENGTH_INCL' is required */
			ED_ASSERT (GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_EXT_MS_SDU_LENGTH_INCL(Source));
			PUSH_INT (Source->EXT_MS_SDU_LENGTH_INCL, 1);
		}
		else {
			/* Field 'EXT_MS_SDU_LENGTH_INCL' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_EXT_MS_SDU_LENGTH_INCL(Source));
		}
		if ((Source->EXT_MS_SDU_LENGTH_INCL_Present ? Source->EXT_MS_SDU_LENGTH_INCL : 0)) {
			/* Field 'EXT_MS_SDU_LENGTH' is required */
			ED_ASSERT (GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_EXT_MS_SDU_LENGTH(Source));
			PUSH_INT (Source->EXT_MS_SDU_LENGTH, 4);
		}
		else {
			/* Field 'EXT_MS_SDU_LENGTH' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_EXT_MS_SDU_LENGTH(Source));
		}
		/* Record-specific Fields 3.1.2.3.1.7.1 - for Enhanced Broadcast records */
		/* See table 3.1.2.3.1.7.2-1. */
		if ((Source->PAGE_CLASS==3)) {
			/* Field 'EXT_BCAST_SDU_LENGTH_IND' is required */
			ED_ASSERT (GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_EXT_BCAST_SDU_LENGTH_IND(Source));
			PUSH_INT (Source->EXT_BCAST_SDU_LENGTH_IND, 2);
		}
		else {
			/* Field 'EXT_BCAST_SDU_LENGTH_IND' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_EXT_BCAST_SDU_LENGTH_IND(Source));
		}
		if ((((Source->EXT_BCAST_SDU_LENGTH_IND_Present ? Source->EXT_BCAST_SDU_LENGTH_IND : 0)&2)==2)) {
			/* Field 'EXT_BCAST_SDU_LENGTH' is required */
			ED_ASSERT (GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_EXT_BCAST_SDU_LENGTH(Source));
			PUSH_INT (Source->EXT_BCAST_SDU_LENGTH, 4);
		}
		else {
			/* Field 'EXT_BCAST_SDU_LENGTH' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_EXT_BCAST_SDU_LENGTH(Source));
		}
		/* SDU */
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->SDU))->usedBits == (int) (((Source->PAGE_CLASS!=3)) ? (((((Source->EXT_MS_SDU_LENGTH_INCL_Present ? Source->EXT_MS_SDU_LENGTH_INCL : 0)==0)) ? (16) : ((((Source->EXT_MS_SDU_LENGTH_Present ? Source->EXT_MS_SDU_LENGTH : 0)*8)+16)))) : (((((Source->EXT_BCAST_SDU_LENGTH_IND_Present ? Source->EXT_BCAST_SDU_LENGTH_IND : 0)==0)) ? (13) : (((((Source->EXT_BCAST_SDU_LENGTH_IND_Present ? Source->EXT_BCAST_SDU_LENGTH_IND : 0)==1)) ? (18) : (((((Source->EXT_BCAST_SDU_LENGTH_IND_Present ? Source->EXT_BCAST_SDU_LENGTH_IND : 0)==2)) ? ((13+(8*(Source->EXT_BCAST_SDU_LENGTH_Present ? Source->EXT_BCAST_SDU_LENGTH : 0)))) : (((((Source->EXT_BCAST_SDU_LENGTH_IND_Present ? Source->EXT_BCAST_SDU_LENGTH_IND : 0)==3)) ? ((18+(8*(Source->EXT_BCAST_SDU_LENGTH_Present ? Source->EXT_BCAST_SDU_LENGTH : 0)))) : (0)))))))))));
		PUSH_BIN ((&(Source->SDU))->value, (&(Source->SDU))->usedBits);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_Universal_Page_Block_page_records_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_Universal_Page_Block_page_records_data* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_UPM_Page_Record */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_f_csch_Universal_Page_Block
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		/* Page Class Fields 3.1.2.2.1.2.2.1 */
		bts = 2;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->PAGE_CLASS___LOCATOR), CurrOfs, bts);
			Destin->PAGE_CLASS = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 2;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->PAGE_SUBCLASS___LOCATOR), CurrOfs, bts);
			Destin->PAGE_SUBCLASS = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* Optional: see table Table 3.1.2.2.1.1.1.2-1 */
		if (((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS!=0))) {
			SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_PAGE_SUBCLASS_EXT(Destin, ED_TRUE);
			bts = 2;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->PAGE_SUBCLASS_EXT___LOCATOR), CurrOfs, bts);
				Destin->PAGE_SUBCLASS_EXT = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_PAGE_SUBCLASS_EXT(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* ARQ Fields, Section 3.1.2.1.1.1, only on mobile addressed fields */
		if ((Destin->PAGE_CLASS!=3)) {
			SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_MSG_SEQ(Destin, ED_TRUE);
			bts = 3;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->MSG_SEQ___LOCATOR), CurrOfs, bts);
				Destin->MSG_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_MSG_SEQ(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* Page Type-specific Fields, Section 3.1.2.2.1.2.3.1 */
		if ((((Destin->PAGE_CLASS==1)&&(Destin->PAGE_SUBCLASS==0))||((Destin->PAGE_CLASS==1)&&(Destin->PAGE_SUBCLASS==1)))) {
			SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_IMSI_ADDR_NUM(Destin, ED_TRUE);
			bts = 3;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->IMSI_ADDR_NUM___LOCATOR), CurrOfs, bts);
				Destin->IMSI_ADDR_NUM = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_IMSI_ADDR_NUM(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((((Destin->PAGE_CLASS==0)&&(Destin->PAGE_SUBCLASS==2))||((Destin->PAGE_CLASS==0)&&(Destin->PAGE_SUBCLASS==3)))||((Destin->PAGE_CLASS==1)&&(Destin->PAGE_SUBCLASS==1)))) {
			SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_MCC(Destin, ED_TRUE);
			bts = 10;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->MCC___LOCATOR), CurrOfs, bts);
				Destin->MCC = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_MCC(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((((Destin->PAGE_CLASS==0)&&(Destin->PAGE_SUBCLASS==1))||((((Destin->PAGE_CLASS==0)&&(Destin->PAGE_SUBCLASS==3))||((Destin->PAGE_CLASS==1)&&(Destin->PAGE_SUBCLASS==0)))||((Destin->PAGE_CLASS==1)&&(Destin->PAGE_SUBCLASS==1))))) {
			SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_IMSI_11_12(Destin, ED_TRUE);
			bts = 7;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->IMSI_11_12___LOCATOR), CurrOfs, bts);
				Destin->IMSI_11_12 = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_IMSI_11_12(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((((((((Destin->PAGE_CLASS==0)&&(Destin->PAGE_SUBCLASS==0))||((Destin->PAGE_CLASS==0)&&(Destin->PAGE_SUBCLASS==1)))||((Destin->PAGE_CLASS==0)&&(Destin->PAGE_SUBCLASS==2)))||((Destin->PAGE_CLASS==0)&&(Destin->PAGE_SUBCLASS==3)))||((Destin->PAGE_CLASS==1)&&(Destin->PAGE_SUBCLASS==0)))||((Destin->PAGE_CLASS==1)&&(Destin->PAGE_SUBCLASS==1)))) {
			SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_IMSI_S_33_16(Destin, ED_TRUE);
			bts = 18;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->IMSI_S_33_16___LOCATOR), CurrOfs, bts);
				Destin->IMSI_S_33_16 = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_IMSI_S_33_16(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((Destin->PAGE_CLASS==2)&&(Destin->PAGE_SUBCLASS==3))) {
			SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_TMSI_ZONE_LEN(Destin, ED_TRUE);
			bts = 4;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->TMSI_ZONE_LEN___LOCATOR), CurrOfs, bts);
				Destin->TMSI_ZONE_LEN = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_TMSI_ZONE_LEN(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		bts = ((((Destin->PAGE_CLASS==2)&&(Destin->PAGE_SUBCLASS==3))) ? ((8*(Destin->TMSI_ZONE_LEN_Present ? Destin->TMSI_ZONE_LEN : 0))) : (0));
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->TMSI_ZONE___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->TMSI_ZONE)))->value), (unsigned)(bts), &(((&(Destin->TMSI_ZONE)))->usedBits));
			EDCopyBits (((&(Destin->TMSI_ZONE))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		if ((((Destin->PAGE_CLASS==2)&&(Destin->PAGE_SUBCLASS==0))||((Destin->PAGE_CLASS==2)&&(Destin->PAGE_SUBCLASS==3)))) {
			SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_TMSI_CODE_ADDR_31_16(Destin, ED_TRUE);
			bts = 16;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->TMSI_CODE_ADDR_31_16___LOCATOR), CurrOfs, bts);
				Destin->TMSI_CODE_ADDR_31_16 = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_TMSI_CODE_ADDR_31_16(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((Destin->PAGE_CLASS==2)&&(Destin->PAGE_SUBCLASS==1))) {
			SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_TMSI_CODE_ADDR_23_16(Destin, ED_TRUE);
			bts = 8;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->TMSI_CODE_ADDR_23_16___LOCATOR), CurrOfs, bts);
				Destin->TMSI_CODE_ADDR_23_16 = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_TMSI_CODE_ADDR_23_16(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==3))&&((Destin->PAGE_SUBCLASS_EXT_Present ? Destin->PAGE_SUBCLASS_EXT : 0)==0))) {
			SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_ADDR_LEN(Destin, ED_TRUE);
			bts = 4;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->ADDR_LEN___LOCATOR), CurrOfs, bts);
				Destin->ADDR_LEN = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_ADDR_LEN(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==3))&&((Destin->PAGE_SUBCLASS_EXT_Present ? Destin->PAGE_SUBCLASS_EXT : 0)==0))) {
			SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_BC_ADDR_REMAINDER(Destin, ED_TRUE);
			bts = (8*((Destin->ADDR_LEN_Present ? Destin->ADDR_LEN : 0)-2));
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->BC_ADDR_REMAINDER___LOCATOR), CurrOfs, bts);
				EDAllocBinary (&((Destin->BC_ADDR_REMAINDER)->value), (unsigned)(bts), &((Destin->BC_ADDR_REMAINDER)->usedBits));
				EDCopyBits ((Destin->BC_ADDR_REMAINDER->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_BC_ADDR_REMAINDER(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		bts = (((((((Destin->PAGE_CLASS==1)&&(Destin->PAGE_SUBCLASS==2))||((Destin->PAGE_CLASS==1)&&(Destin->PAGE_SUBCLASS==3)))||(((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==2))&&((Destin->PAGE_SUBCLASS_EXT_Present ? Destin->PAGE_SUBCLASS_EXT : 0)==3)))||(((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==3))&&((Destin->PAGE_SUBCLASS_EXT_Present ? Destin->PAGE_SUBCLASS_EXT : 0)==3)))) ? (5) : ((((((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==1))&&((Destin->PAGE_SUBCLASS_EXT_Present ? Destin->PAGE_SUBCLASS_EXT : 0)==3))) ? (4) : (0))));
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->RESERVED_LEN___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->RESERVED_LEN)))->value), (unsigned)(bts), &(((&(Destin->RESERVED_LEN)))->usedBits));
			EDCopyBits (((&(Destin->RESERVED_LEN))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = (((((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==1))&&((Destin->PAGE_SUBCLASS_EXT_Present ? Destin->PAGE_SUBCLASS_EXT : 0)==1))) ? (8) : (((((((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==2))&&((Destin->PAGE_SUBCLASS_EXT_Present ? Destin->PAGE_SUBCLASS_EXT : 0)==0))||(((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==1))&&((Destin->PAGE_SUBCLASS_EXT_Present ? Destin->PAGE_SUBCLASS_EXT : 0)==0)))) ? (16) : ((((((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==2))&&((Destin->PAGE_SUBCLASS_EXT_Present ? Destin->PAGE_SUBCLASS_EXT : 0)==1))) ? (52) : ((((((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==2))&&((Destin->PAGE_SUBCLASS_EXT_Present ? Destin->PAGE_SUBCLASS_EXT : 0)==2))) ? (60) : ((((((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==1))&&((Destin->PAGE_SUBCLASS_EXT_Present ? Destin->PAGE_SUBCLASS_EXT : 0)==3))) ? (((8*EDBitsToInt (Destin->RESERVED_LEN.value, 0, Destin->RESERVED_LEN.usedBits) /*ISPOINTER=0*/)+16)) : ((((((((Destin->PAGE_CLASS==1)&&(Destin->PAGE_SUBCLASS==2))||((Destin->PAGE_CLASS==1)&&(Destin->PAGE_SUBCLASS==3)))||(((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==2))&&((Destin->PAGE_SUBCLASS_EXT_Present ? Destin->PAGE_SUBCLASS_EXT : 0)==3)))||(((Destin->PAGE_CLASS==3)&&(Destin->PAGE_SUBCLASS==3))&&((Destin->PAGE_SUBCLASS_EXT_Present ? Destin->PAGE_SUBCLASS_EXT : 0)==3)))) ? ((8*EDBitsToInt (Destin->RESERVED_LEN.value, 0, Destin->RESERVED_LEN.usedBits) /*ISPOINTER=0*/)) : (0))))))))))));
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->RESERVED___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->RESERVED)))->value), (unsigned)(bts), &(((&(Destin->RESERVED)))->usedBits));
			EDCopyBits (((&(Destin->RESERVED))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* Record-specific Fields 3.1.2.3.1.7.1 - for Mobile Station-addressed records */
		if ((Destin->PAGE_CLASS!=3)) {
			SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_EXT_MS_SDU_LENGTH_INCL(Destin, ED_TRUE);
			bts = 1;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->EXT_MS_SDU_LENGTH_INCL___LOCATOR), CurrOfs, bts);
				Destin->EXT_MS_SDU_LENGTH_INCL = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_EXT_MS_SDU_LENGTH_INCL(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((Destin->EXT_MS_SDU_LENGTH_INCL_Present ? Destin->EXT_MS_SDU_LENGTH_INCL : 0)) {
			SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_EXT_MS_SDU_LENGTH(Destin, ED_TRUE);
			bts = 4;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->EXT_MS_SDU_LENGTH___LOCATOR), CurrOfs, bts);
				Destin->EXT_MS_SDU_LENGTH = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_EXT_MS_SDU_LENGTH(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* Record-specific Fields 3.1.2.3.1.7.1 - for Enhanced Broadcast records */
		/* See table 3.1.2.3.1.7.2-1. */
		if ((Destin->PAGE_CLASS==3)) {
			SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_EXT_BCAST_SDU_LENGTH_IND(Destin, ED_TRUE);
			bts = 2;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->EXT_BCAST_SDU_LENGTH_IND___LOCATOR), CurrOfs, bts);
				Destin->EXT_BCAST_SDU_LENGTH_IND = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_EXT_BCAST_SDU_LENGTH_IND(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((((Destin->EXT_BCAST_SDU_LENGTH_IND_Present ? Destin->EXT_BCAST_SDU_LENGTH_IND : 0)&2)==2)) {
			SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_EXT_BCAST_SDU_LENGTH(Destin, ED_TRUE);
			bts = 4;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->EXT_BCAST_SDU_LENGTH___LOCATOR), CurrOfs, bts);
				Destin->EXT_BCAST_SDU_LENGTH = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_EXT_BCAST_SDU_LENGTH(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* SDU */
		bts = (((Destin->PAGE_CLASS!=3)) ? (((((Destin->EXT_MS_SDU_LENGTH_INCL_Present ? Destin->EXT_MS_SDU_LENGTH_INCL : 0)==0)) ? (16) : ((((Destin->EXT_MS_SDU_LENGTH_Present ? Destin->EXT_MS_SDU_LENGTH : 0)*8)+16)))) : (((((Destin->EXT_BCAST_SDU_LENGTH_IND_Present ? Destin->EXT_BCAST_SDU_LENGTH_IND : 0)==0)) ? (13) : (((((Destin->EXT_BCAST_SDU_LENGTH_IND_Present ? Destin->EXT_BCAST_SDU_LENGTH_IND : 0)==1)) ? (18) : (((((Destin->EXT_BCAST_SDU_LENGTH_IND_Present ? Destin->EXT_BCAST_SDU_LENGTH_IND : 0)==2)) ? ((13+(8*(Destin->EXT_BCAST_SDU_LENGTH_Present ? Destin->EXT_BCAST_SDU_LENGTH : 0)))) : (((((Destin->EXT_BCAST_SDU_LENGTH_IND_Present ? Destin->EXT_BCAST_SDU_LENGTH_IND : 0)==3)) ? ((18+(8*(Destin->EXT_BCAST_SDU_LENGTH_Present ? Destin->EXT_BCAST_SDU_LENGTH : 0)))) : (0))))))))));
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->SDU___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->SDU)))->value), (unsigned)(bts), &(((&(Destin->SDU)))->usedBits));
			EDCopyBits (((&(Destin->SDU))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_PDU */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* Reset exported tag 5 'MACI_INCL' */
		pp_CS0004E_Details->userTagPresent[2] = 0;
		pp_CS0004E_Details->userTag[2] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[2], "r_csch_PDU", "MACI_INCL");
		pp_CS0004E_Details->userTagBusy[2] = 1;
#endif
		/* Reset exported tag 11 'PILOT_REC_TYPE' */
		pp_CS0004E_Details->userTagPresent[4] = 0;
		pp_CS0004E_Details->userTag[4] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[4], "r_csch_PDU", "PILOT_REC_TYPE");
		pp_CS0004E_Details->userTagBusy[4] = 1;
#endif
		/* Reset exported tag 14 'LAC_LENGTH_OFFSET' */
		pp_CS0004E_Details->userTagPresent[0] = 0;
		pp_CS0004E_Details->userTag[0] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[0], "r_csch_PDU", "LAC_LENGTH_OFFSET");
		pp_CS0004E_Details->userTagBusy[0] = 1;
#endif
		/* Reset exported tag 28 'MSG_ID' */
		pp_CS0004E_Details->userTagPresent[1] = 0;
		pp_CS0004E_Details->userTag[1] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[1], "r_csch_PDU", "MSG_ID");
		pp_CS0004E_Details->userTagBusy[1] = 1;
#endif
		/* Reset exported tag 29 'IMSI_CLASS' */
		pp_CS0004E_Details->userTagPresent[3] = 0;
		pp_CS0004E_Details->userTag[3] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[3], "r_csch_PDU", "IMSI_CLASS");
		pp_CS0004E_Details->userTagBusy[3] = 1;
#endif
		CurrOfs += ENCODE_c_r_csch_PDU_Message_Type (Buffer, CurrOfs, (&(Source->Message_Type)), pp_CS0004E_Details);
		if ((pp_CS0004E_Details->n_P_REV_IN_USEs==6)) {
			/* Field 'LAC_Length' is required */
			ED_ASSERT (GETPRESENT_c_r_csch_PDU_LAC_Length(Source));
			CurrOfs += ENCODE_c_r_csch_PDU_LAC_Length (Buffer, CurrOfs, Source->LAC_Length, pp_CS0004E_Details);
		}
		else {
			/* Field 'LAC_Length' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_csch_PDU_LAC_Length(Source));
		}
		CurrOfs += ENCODE_c_r_csch_PDU_ARQ (Buffer, CurrOfs, (&(Source->ARQ)), pp_CS0004E_Details);
		CurrOfs += ENCODE_c_r_csch_PDU_Addressing (Buffer, CurrOfs, (&(Source->Addressing)), pp_CS0004E_Details);
		CurrOfs += ENCODE_c_r_csch_PDU_Authentication (Buffer, CurrOfs, (&(Source->Authentication)), pp_CS0004E_Details);
		/* Missing on P_REV<=6, see 2.1.1.4.1.3.2 */
		if ((pp_CS0004E_Details->n_P_REV_IN_USEs>=7)) {
			/* Field 'Extended_Encryption' is required */
			ED_ASSERT (GETPRESENT_c_r_csch_PDU_Extended_Encryption(Source));
			CurrOfs += ENCODE_c_r_csch_PDU_Extended_Encryption (Buffer, CurrOfs, Source->Extended_Encryption, pp_CS0004E_Details);
		}
		else {
			/* Field 'Extended_Encryption' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Extended_Encryption(Source));
		}
		/* LAC Padding 2.1.1.4.1.4 */
		/* Encode the correct LENGTH value only in P_REV=6 */
		if (P_REV_IN_USE_NOCSN_04 == 6) {
		
		EDIntToBits (BUFFER, pp_CS0004E_Details->userTag[0]/*LAC_LENGTH_OFFSET*/, (CURPOS + ((8 - (CURPOS & 7)) & 7) - pp_CS0004E_Details->userTag[0]/*LAC_LENGTH_OFFSET*/)/8, 5);
		/* Encode spare bits */
		PUSH_INT (0, ((int)CurrOfs < EDBitsToInt (Buffer, pp_CS0004E_Details->userTag[0]/*LAC_LENGTH_OFFSET*/, 5)*8+pp_CS0004E_Details->userTag[0]/*LAC_LENGTH_OFFSET*/ ? EDBitsToInt (Buffer, pp_CS0004E_Details->userTag[0]/*LAC_LENGTH_OFFSET*/, 5)*8+pp_CS0004E_Details->userTag[0]/*LAC_LENGTH_OFFSET*/ - CurrOfs : 0));
		}
		{
			int SDU_LENGTH = 0;
		/* REVISION <=3: */
		/* * SDU */
		/* * MACI */
		/* REVISION 4 and 5: */
		/* * SDU */
		/* * Radio_Environment_Report */
		/* REVISION >= 6: */
		/* * Radio_Environment_Report */
		/* * SDU */
		/* * MACI */
		if ((pp_CS0004E_Details->n_P_REV_IN_USEs>=6)) {
			/* Field 'Radio_Environment_Report' is required */
			ED_ASSERT (GETPRESENT_c_r_csch_PDU_Radio_Environment_Report(Source));
			CurrOfs += ENCODE_c_r_csch_Radio_Environment_Report (Buffer, CurrOfs, Source->Radio_Environment_Report, pp_CS0004E_Details);
		}
		
			SDU_LENGTH = ED_THIS->SDU.usedBits;
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->SDU))->usedBits == (int) (SDU_LENGTH));
        SDU_LENGTH = SDU_LENGTH;
		PUSH_BIN ((&(Source->SDU))->value, (&(Source->SDU))->usedBits);
		if (((pp_CS0004E_Details->userTag[2])&&((pp_CS0004E_Details->n_P_REV_IN_USEs<=3)||(pp_CS0004E_Details->n_P_REV_IN_USEs>=6)))) {
			/* Field 'MACI' is required */
			ED_ASSERT (GETPRESENT_c_r_csch_PDU_MACI(Source));
			PUSH_INT (Source->MACI, 32);
		}
		else {
			/* Field 'MACI' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_csch_PDU_MACI(Source));
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs==4)||(pp_CS0004E_Details->n_P_REV_IN_USEs==5))) {
			/* Field 'Radio_Environment_Report' is required */
			ED_ASSERT (GETPRESENT_c_r_csch_PDU_Radio_Environment_Report(Source));
			CurrOfs += ENCODE_c_r_csch_Radio_Environment_Report (Buffer, CurrOfs, Source->Radio_Environment_Report, pp_CS0004E_Details);
		}
		}
		/* Standard r-csch/f-csch PDU padding */
		CurrOfs = CS0004E_PDU_Padding_plus_2_Encode (Buffer, CurrOfs, pp_CS0004E_Details);
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[2], "r_csch_PDU", "MACI_INCL");
		pp_CS0004E_Details->userTagBusy[2] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[4], "r_csch_PDU", "PILOT_REC_TYPE");
		pp_CS0004E_Details->userTagBusy[4] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[0], "r_csch_PDU", "LAC_LENGTH_OFFSET");
		pp_CS0004E_Details->userTagBusy[0] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[1], "r_csch_PDU", "MSG_ID");
		pp_CS0004E_Details->userTagBusy[1] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[3], "r_csch_PDU", "IMSI_CLASS");
		pp_CS0004E_Details->userTagBusy[3] = 0;
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_PDU */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		/* Reset exported tag 5 'MACI_INCL' */
		pp_CS0004E_Details->userTagPresent[2] = 0;
		pp_CS0004E_Details->userTag[2] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[2], "r_csch_PDU", "MACI_INCL");
		pp_CS0004E_Details->userTagBusy[2] = 1;
#endif
		/* Reset exported tag 11 'PILOT_REC_TYPE' */
		pp_CS0004E_Details->userTagPresent[4] = 0;
		pp_CS0004E_Details->userTag[4] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[4], "r_csch_PDU", "PILOT_REC_TYPE");
		pp_CS0004E_Details->userTagBusy[4] = 1;
#endif
		/* Reset exported tag 14 'LAC_LENGTH_OFFSET' */
		pp_CS0004E_Details->userTagPresent[0] = 0;
		pp_CS0004E_Details->userTag[0] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[0], "r_csch_PDU", "LAC_LENGTH_OFFSET");
		pp_CS0004E_Details->userTagBusy[0] = 1;
#endif
		/* Reset exported tag 28 'MSG_ID' */
		pp_CS0004E_Details->userTagPresent[1] = 0;
		pp_CS0004E_Details->userTag[1] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[1], "r_csch_PDU", "MSG_ID");
		pp_CS0004E_Details->userTagBusy[1] = 1;
#endif
		/* Reset exported tag 29 'IMSI_CLASS' */
		pp_CS0004E_Details->userTagPresent[3] = 0;
		pp_CS0004E_Details->userTag[3] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[3], "r_csch_PDU", "IMSI_CLASS");
		pp_CS0004E_Details->userTagBusy[3] = 1;
#endif
		bts = DECODE_c_r_csch_PDU_Message_Type (Buffer, CurrOfs, (&(Destin->Message_Type)), LastOfs-CurrOfs , pp_CS0004E_Details);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		if ((pp_CS0004E_Details->n_P_REV_IN_USEs==6)) {
			SETPRESENT_c_r_csch_PDU_LAC_Length(Destin, ED_TRUE);
			bts = DECODE_c_r_csch_PDU_LAC_Length (Buffer, CurrOfs, Destin->LAC_Length, LastOfs-CurrOfs , pp_CS0004E_Details);
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_csch_PDU_LAC_Length(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		bts = DECODE_c_r_csch_PDU_ARQ (Buffer, CurrOfs, (&(Destin->ARQ)), LastOfs-CurrOfs , pp_CS0004E_Details);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = DECODE_c_r_csch_PDU_Addressing (Buffer, CurrOfs, (&(Destin->Addressing)), LastOfs-CurrOfs , pp_CS0004E_Details);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = DECODE_c_r_csch_PDU_Authentication (Buffer, CurrOfs, (&(Destin->Authentication)), LastOfs-CurrOfs , pp_CS0004E_Details);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* Missing on P_REV<=6, see 2.1.1.4.1.3.2 */
		if ((pp_CS0004E_Details->n_P_REV_IN_USEs>=7)) {
			SETPRESENT_c_r_csch_PDU_Extended_Encryption(Destin, ED_TRUE);
			bts = DECODE_c_r_csch_PDU_Extended_Encryption (Buffer, CurrOfs, Destin->Extended_Encryption, LastOfs-CurrOfs , pp_CS0004E_Details);
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_csch_PDU_Extended_Encryption(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* LAC Padding 2.1.1.4.1.4 */
		/* Encode the correct LENGTH value only in P_REV=6 */
		if (P_REV_IN_USE_NOCSN_04 == 6) {
		
		
		/* Decode spare bit(s) */
		bts = ((int)CurrOfs < EDBitsToInt (Buffer, pp_CS0004E_Details->userTag[0]/*LAC_LENGTH_OFFSET*/, 5)*8+pp_CS0004E_Details->userTag[0]/*LAC_LENGTH_OFFSET*/ ? EDBitsToInt (Buffer, pp_CS0004E_Details->userTag[0]/*LAC_LENGTH_OFFSET*/, 5)*8+pp_CS0004E_Details->userTag[0]/*LAC_LENGTH_OFFSET*/ - CurrOfs : 0);
		if (LastOfs-CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
			goto exitOnFail;
		}
		CurrOfs += bts;
		}
		{
			int SDU_LENGTH = 0;
		/* REVISION <=3: */
		/* * SDU */
		/* * MACI */
		/* REVISION 4 and 5: */
		/* * SDU */
		/* * Radio_Environment_Report */
		/* REVISION >= 6: */
		/* * Radio_Environment_Report */
		/* * SDU */
		/* * MACI */
		if ((pp_CS0004E_Details->n_P_REV_IN_USEs>=6)) {
			SETPRESENT_c_r_csch_PDU_Radio_Environment_Report(Destin, ED_TRUE);
			bts = DECODE_c_r_csch_Radio_Environment_Report (Buffer, CurrOfs, Destin->Radio_Environment_Report, LastOfs-CurrOfs , pp_CS0004E_Details);
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_csch_PDU_Radio_Environment_Report(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
			/* Calculate the SDU size when decoding */
			SDU_LENGTH = CS0004E_r_csch_CalcSDUSize ((const char*)Buffer, CurrOfs, LastOfs, P_REV_IN_USE_NOCSN_04, (unsigned)pp_CS0004E_Details->userTag[1]/*MSG_ID*/);
		
		
		bts = (SDU_LENGTH);
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->SDU___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->SDU)))->value), (unsigned)(bts), &(((&(Destin->SDU)))->usedBits));
			EDCopyBits (((&(Destin->SDU))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		if (((pp_CS0004E_Details->userTag[2])&&((pp_CS0004E_Details->n_P_REV_IN_USEs<=3)||(pp_CS0004E_Details->n_P_REV_IN_USEs>=6)))) {
			SETPRESENT_c_r_csch_PDU_MACI(Destin, ED_TRUE);
			bts = 32;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->MACI___LOCATOR), CurrOfs, bts);
				Destin->MACI = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_csch_PDU_MACI(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs==4)||(pp_CS0004E_Details->n_P_REV_IN_USEs==5))) {
			SETPRESENT_c_r_csch_PDU_Radio_Environment_Report(Destin, ED_TRUE);
			bts = DECODE_c_r_csch_Radio_Environment_Report (Buffer, CurrOfs, Destin->Radio_Environment_Report, LastOfs-CurrOfs , pp_CS0004E_Details);
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_csch_PDU_Radio_Environment_Report(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		}
		/* Standard r-csch/f-csch PDU padding */
		
		CurrOfs = CS0004E_PDU_Padding_plus_2_Decode (CurrOfs, LastOfs, pp_CS0004E_Details);
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[2], "r_csch_PDU", "MACI_INCL");
		pp_CS0004E_Details->userTagBusy[2] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[4], "r_csch_PDU", "PILOT_REC_TYPE");
		pp_CS0004E_Details->userTagBusy[4] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[0], "r_csch_PDU", "LAC_LENGTH_OFFSET");
		pp_CS0004E_Details->userTagBusy[0] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[1], "r_csch_PDU", "MSG_ID");
		pp_CS0004E_Details->userTagBusy[1] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[3], "r_csch_PDU", "IMSI_CLASS");
		pp_CS0004E_Details->userTagBusy[3] = 0;
#endif
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[2], "r_csch_PDU", "MACI_INCL");
		pp_CS0004E_Details->userTagBusy[2] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[4], "r_csch_PDU", "PILOT_REC_TYPE");
		pp_CS0004E_Details->userTagBusy[4] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[0], "r_csch_PDU", "LAC_LENGTH_OFFSET");
		pp_CS0004E_Details->userTagBusy[0] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[1], "r_csch_PDU", "MSG_ID");
		pp_CS0004E_Details->userTagBusy[1] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[3], "r_csch_PDU", "IMSI_CLASS");
		pp_CS0004E_Details->userTagBusy[3] = 0;
#endif
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_LAC_Length (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_LAC_Length* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_LAC_Length */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* The mobile station shall set the LAC_LENGTH field to the combined length in octets of the */
		/* LAC_LENGTH field, the Authentication fields (see 2.1.1.1.1.1), the ARQ fields (see */
		/* 2.1.1.2.1.1), the Addressing fields (see 2.1.1.3.1.1) and the LAC Padding field (see */
		/* 2.1.1.4.1.4). */
		pp_CS0004E_Details->userTag[0]/*LAC_LENGTH_OFFSET*/ = CurrOfs;
		PUSH_INT (Source->LAC_LENGTH, 5);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_LAC_Length (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_LAC_Length* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_LAC_Length */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		/* The mobile station shall set the LAC_LENGTH field to the combined length in octets of the */
		/* LAC_LENGTH field, the Authentication fields (see 2.1.1.1.1.1), the ARQ fields (see */
		/* 2.1.1.2.1.1), the Addressing fields (see 2.1.1.3.1.1) and the LAC Padding field (see */
		/* 2.1.1.4.1.4). */
		pp_CS0004E_Details->userTag[0]/*LAC_LENGTH_OFFSET*/ = CurrOfs;
		bts = 5;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->LAC_LENGTH___LOCATOR), CurrOfs, bts);
			Destin->LAC_LENGTH = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_Message_Type (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_Message_Type* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Message_Type */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* Mark the beginning of the PDU, to allow correct padding */
		pp_CS0004E_Details->n_PDU_START_OFFSET = CurrOfs;
		
		PUSH_INT (Source->PD, 2);
		PUSH_INT (Source->MSG_ID, 6);
		/* Set the exported tag */
		pp_CS0004E_Details->userTagPresent[1] = 1;
		pp_CS0004E_Details->userTag[1] = (int)Source->MSG_ID;
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_Message_Type (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_Message_Type* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Message_Type */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		/* Mark the beginning of the PDU, to allow correct padding */
		pp_CS0004E_Details->n_PDU_START_OFFSET = CurrOfs;
		
		bts = 2;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->PD___LOCATOR), CurrOfs, bts);
			Destin->PD = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 6;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->MSG_ID___LOCATOR), CurrOfs, bts);
			Destin->MSG_ID = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			/* Set the exported tag */
			pp_CS0004E_Details->userTagPresent[1] = 1;
			pp_CS0004E_Details->userTag[1] = (int)Destin->MSG_ID;
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_ARQ (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_ARQ* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_ARQ */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->ACK_SEQ, 3);
		PUSH_INT (Source->MSG_SEQ, 3);
		PUSH_INT (Source->ACK_REQ, 1);
		PUSH_INT (Source->VALID_ACK, 1);
		PUSH_INT (Source->ACK_TYPE, 3);
		/* Revision 11 additions. Note that ACK_TYPE==4 is not expected on previous versions */
		if ((Source->ACK_TYPE==4)) {
			/* Field 'EXT_ACK_TYPE' is required */
			ED_ASSERT (GETPRESENT_c_r_csch_PDU_ARQ_EXT_ACK_TYPE(Source));
			PUSH_INT (Source->EXT_ACK_TYPE, 3);
		}
		else {
			/* Field 'EXT_ACK_TYPE' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_csch_PDU_ARQ_EXT_ACK_TYPE(Source));
		}
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_ARQ (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_ARQ* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_ARQ */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 3;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ACK_SEQ___LOCATOR), CurrOfs, bts);
			Destin->ACK_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 3;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->MSG_SEQ___LOCATOR), CurrOfs, bts);
			Destin->MSG_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ACK_REQ___LOCATOR), CurrOfs, bts);
			Destin->ACK_REQ = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->VALID_ACK___LOCATOR), CurrOfs, bts);
			Destin->VALID_ACK = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 3;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ACK_TYPE___LOCATOR), CurrOfs, bts);
			Destin->ACK_TYPE = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* Revision 11 additions. Note that ACK_TYPE==4 is not expected on previous versions */
		if ((Destin->ACK_TYPE==4)) {
			SETPRESENT_c_r_csch_PDU_ARQ_EXT_ACK_TYPE(Destin, ED_TRUE);
			bts = 3;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->EXT_ACK_TYPE___LOCATOR), CurrOfs, bts);
				Destin->EXT_ACK_TYPE = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_csch_PDU_ARQ_EXT_ACK_TYPE(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_Addressing (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_Addressing* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Addressing */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->MSID_TYPE, 3);
		/* The EXT_MSID_TYPE field appeared in Rev.11; it is activated by MSID_TYPE==4 */
		if ((Source->MSID_TYPE==4)) {
			/* Field 'EXT_MSID_TYPE' is required */
			ED_ASSERT (GETPRESENT_c_r_csch_PDU_Addressing_EXT_MSID_TYPE(Source));
			PUSH_INT (Source->EXT_MSID_TYPE, 3);
		}
		else {
			/* Field 'EXT_MSID_TYPE' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Addressing_EXT_MSID_TYPE(Source));
		}
		PUSH_INT (Source->MSID_LEN, 4);
		/* BEGIN OF PAD ZONE - ENCODE inclusive=0 bits=4 octet(=0)/bit(=1)=0 */
		{
			ED_EXLONG dataStartOfs0 = CurrOfs;
			int lenInBits0;
			if ((Source->MSID_TYPE==0)) {
				/* Field 'IMSI_M_S1' is required */
				ED_ASSERT (GETPRESENT_c_r_csch_PDU_Addressing_IMSI_M_S1(Source));
				PUSH_INT (Source->IMSI_M_S1, 24);
			}
			else {
				/* Field 'IMSI_M_S1' must be absent */
				ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Addressing_IMSI_M_S1(Source));
			}
			/* Up to REV 8 it was called MIN1 */
			if ((Source->MSID_TYPE==0)) {
				/* Field 'IMSI_M_S2' is required */
				ED_ASSERT (GETPRESENT_c_r_csch_PDU_Addressing_IMSI_M_S2(Source));
				PUSH_INT (Source->IMSI_M_S2, 10);
			}
			else {
				/* Field 'IMSI_M_S2' must be absent */
				ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Addressing_IMSI_M_S2(Source));
			}
			/* Up to REV 8 it was called MIN2 */
			if (((((Source->MSID_TYPE==0)||(Source->MSID_TYPE==1))||(Source->MSID_TYPE==3))||((Source->MSID_TYPE==4)&&((Source->EXT_MSID_TYPE_Present ? Source->EXT_MSID_TYPE : 0)==2)))) {
				/* Field 'ESN' is required */
				ED_ASSERT (GETPRESENT_c_r_csch_PDU_Addressing_ESN(Source));
				PUSH_INT (Source->ESN, 32);
			}
			else {
				/* Field 'ESN' must be absent */
				ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Addressing_ESN(Source));
			}
			if (((((Source->MSID_TYPE==4)&&((Source->EXT_MSID_TYPE_Present ? Source->EXT_MSID_TYPE : 0)==0))||((Source->MSID_TYPE==4)&&((Source->EXT_MSID_TYPE_Present ? Source->EXT_MSID_TYPE : 0)==1)))||((Source->MSID_TYPE==4)&&((Source->EXT_MSID_TYPE_Present ? Source->EXT_MSID_TYPE : 0)==2)))) {
				/* Field 'MEID' is required */
				ED_ASSERT (GETPRESENT_c_r_csch_PDU_Addressing_MEID(Source));
				PUSH_BIN (Source->MEID, 56);
			}
			else {
				/* Field 'MEID' must be absent */
				ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Addressing_MEID(Source));
			}
			if (((((Source->MSID_TYPE==2)||(Source->MSID_TYPE==3))||((Source->MSID_TYPE==4)&&((Source->EXT_MSID_TYPE_Present ? Source->EXT_MSID_TYPE : 0)==1)))||((Source->MSID_TYPE==4)&&((Source->EXT_MSID_TYPE_Present ? Source->EXT_MSID_TYPE : 0)==2)))) {
				/* Field 'IMSI_CLASS' is required */
				ED_ASSERT (GETPRESENT_c_r_csch_PDU_Addressing_IMSI_CLASS(Source));
				PUSH_INT (Source->IMSI_CLASS, 1);
				/* Set the exported tag */
				pp_CS0004E_Details->userTagPresent[3] = 1;
				pp_CS0004E_Details->userTag[3] = (int)Source->IMSI_CLASS;
			}
			else {
				/* Field 'IMSI_CLASS' must be absent */
				ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Addressing_IMSI_CLASS(Source));
			}
			if (((((Source->MSID_TYPE==2)||(Source->MSID_TYPE==3))||((Source->MSID_TYPE==4)&&((Source->EXT_MSID_TYPE_Present ? Source->EXT_MSID_TYPE : 0)==1)))||((Source->MSID_TYPE==4)&&((Source->EXT_MSID_TYPE_Present ? Source->EXT_MSID_TYPE : 0)==2)))) {
				/* Field 'IMSI_class_specific_subfields' is required */
				ED_ASSERT (GETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields(Source));
				CurrOfs += ENCODE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields (Buffer, CurrOfs, Source->IMSI_class_specific_subfields, pp_CS0004E_Details);
			}
			else {
				/* Field 'IMSI_class_specific_subfields' must be absent */
				ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields(Source));
			}
			if ((Source->MSID_TYPE==5)) {
				/* Field 'TMSI_ZONE' is required */
				ED_ASSERT (GETPRESENT_c_r_csch_PDU_Addressing_TMSI_ZONE(Source));
				/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=1 */
				ED_ASSERT (Source->TMSI_ZONE->usedBits == (int) (((Source->MSID_LEN>4)) ? ((8*(Source->MSID_LEN-4))) : (0)));
				PUSH_BIN (Source->TMSI_ZONE->value, Source->TMSI_ZONE->usedBits);
			}
			else {
				/* Field 'TMSI_ZONE' must be absent */
				ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Addressing_TMSI_ZONE(Source));
			}
			if ((Source->MSID_TYPE==5)) {
				/* Field 'TMSI_CODE_ADDR' is required */
				ED_ASSERT (GETPRESENT_c_r_csch_PDU_Addressing_TMSI_CODE_ADDR(Source));
				/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=1 */
				ED_ASSERT (Source->TMSI_CODE_ADDR->usedBits == (int) (((Source->MSID_LEN>4)) ? (32) : ((8*Source->MSID_LEN))));
				PUSH_BIN (Source->TMSI_CODE_ADDR->value, Source->TMSI_CODE_ADDR->usedBits);
			}
			else {
				/* Field 'TMSI_CODE_ADDR' must be absent */
				ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Addressing_TMSI_CODE_ADDR(Source));
			}
			/* RESERVED */
			/* Spare bits are optional */
			if ((Source->MSID_TYPE==0)) {
				/* Encode spare bits */
				PUSH_INT (0, 6);
			}
			/* Calculate the encoded length in octets */
			lenInBits0 = (CurrOfs-dataStartOfs0);
			
			/* Save the encoded length into the length field */
			EDIntToBits (Buffer, dataStartOfs0-4, ((lenInBits0+7)/8)-0, 4);
			
			/* Pad if required */
			if ((lenInBits0 & 0x07) != 0) {
				PUSH_INT (0, 8-(lenInBits0 & 0x07));
			}
		}
		/* END OF PAD ZONE */
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_Addressing (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_Addressing* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Addressing */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 3;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->MSID_TYPE___LOCATOR), CurrOfs, bts);
			Destin->MSID_TYPE = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* The EXT_MSID_TYPE field appeared in Rev.11; it is activated by MSID_TYPE==4 */
		if ((Destin->MSID_TYPE==4)) {
			SETPRESENT_c_r_csch_PDU_Addressing_EXT_MSID_TYPE(Destin, ED_TRUE);
			bts = 3;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->EXT_MSID_TYPE___LOCATOR), CurrOfs, bts);
				Destin->EXT_MSID_TYPE = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_csch_PDU_Addressing_EXT_MSID_TYPE(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		bts = 4;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->MSID_LEN___LOCATOR), CurrOfs, bts);
			Destin->MSID_LEN = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* BEGIN OF PAD ZONE - DECODE inclusive=0 bits=4 octet(=0)/bit(=1)=0 */
		{
			/* Save the current final offset position */
			int LastOfs1 = LastOfs;
			
			/* Calculate the new final offset position */
			int NewLastOfs1 = CurrOfs +
			EDBitsToInt (Buffer, CurrOfs-4, 4) * 8;
			
			/* Temporarely set the new LastOfs value */
			LastOfs = NewLastOfs1;
			
			/* Execute the normal decoding */
			if ((Destin->MSID_TYPE==0)) {
				SETPRESENT_c_r_csch_PDU_Addressing_IMSI_M_S1(Destin, ED_TRUE);
				bts = 24;
				if (LastOfs - (int)CurrOfs < bts) {
					bts = ED_MESSAGE_TOO_SHORT;
				} 
				else {
					ED_LOCATOR_SET (&(Destin->IMSI_M_S1___LOCATOR), CurrOfs, bts);
					Destin->IMSI_M_S1 = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
				}
				if (bts < 0) {
					/* If decoding failed, set the failed field to "not present" */
					SETPRESENT_c_r_csch_PDU_Addressing_IMSI_M_S1(Destin, ED_FALSE);
					goto exitOnFail;
				}
				CurrOfs += bts;
			}
			/* Up to REV 8 it was called MIN1 */
			if ((Destin->MSID_TYPE==0)) {
				SETPRESENT_c_r_csch_PDU_Addressing_IMSI_M_S2(Destin, ED_TRUE);
				bts = 10;
				if (LastOfs - (int)CurrOfs < bts) {
					bts = ED_MESSAGE_TOO_SHORT;
				} 
				else {
					ED_LOCATOR_SET (&(Destin->IMSI_M_S2___LOCATOR), CurrOfs, bts);
					Destin->IMSI_M_S2 = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
				}
				if (bts < 0) {
					/* If decoding failed, set the failed field to "not present" */
					SETPRESENT_c_r_csch_PDU_Addressing_IMSI_M_S2(Destin, ED_FALSE);
					goto exitOnFail;
				}
				CurrOfs += bts;
			}
			/* Up to REV 8 it was called MIN2 */
			if (((((Destin->MSID_TYPE==0)||(Destin->MSID_TYPE==1))||(Destin->MSID_TYPE==3))||((Destin->MSID_TYPE==4)&&((Destin->EXT_MSID_TYPE_Present ? Destin->EXT_MSID_TYPE : 0)==2)))) {
				SETPRESENT_c_r_csch_PDU_Addressing_ESN(Destin, ED_TRUE);
				bts = 32;
				if (LastOfs - (int)CurrOfs < bts) {
					bts = ED_MESSAGE_TOO_SHORT;
				} 
				else {
					ED_LOCATOR_SET (&(Destin->ESN___LOCATOR), CurrOfs, bts);
					Destin->ESN = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
				}
				if (bts < 0) {
					/* If decoding failed, set the failed field to "not present" */
					SETPRESENT_c_r_csch_PDU_Addressing_ESN(Destin, ED_FALSE);
					goto exitOnFail;
				}
				CurrOfs += bts;
			}
			if (((((Destin->MSID_TYPE==4)&&((Destin->EXT_MSID_TYPE_Present ? Destin->EXT_MSID_TYPE : 0)==0))||((Destin->MSID_TYPE==4)&&((Destin->EXT_MSID_TYPE_Present ? Destin->EXT_MSID_TYPE : 0)==1)))||((Destin->MSID_TYPE==4)&&((Destin->EXT_MSID_TYPE_Present ? Destin->EXT_MSID_TYPE : 0)==2)))) {
				SETPRESENT_c_r_csch_PDU_Addressing_MEID(Destin, ED_TRUE);
				bts = 56;
				if (LastOfs - (int)CurrOfs < bts) {
					bts = ED_MESSAGE_TOO_SHORT;
				} 
				else {
					ED_LOCATOR_SET (&(Destin->MEID___LOCATOR), CurrOfs, bts);
					EDCopyBits (Destin->MEID, 0, Buffer, CURPOS, (ED_EXLONG)bts);
				}
				if (bts < 0) {
					/* If decoding failed, set the failed field to "not present" */
					SETPRESENT_c_r_csch_PDU_Addressing_MEID(Destin, ED_FALSE);
					goto exitOnFail;
				}
				CurrOfs += bts;
			}
			if (((((Destin->MSID_TYPE==2)||(Destin->MSID_TYPE==3))||((Destin->MSID_TYPE==4)&&((Destin->EXT_MSID_TYPE_Present ? Destin->EXT_MSID_TYPE : 0)==1)))||((Destin->MSID_TYPE==4)&&((Destin->EXT_MSID_TYPE_Present ? Destin->EXT_MSID_TYPE : 0)==2)))) {
				SETPRESENT_c_r_csch_PDU_Addressing_IMSI_CLASS(Destin, ED_TRUE);
				bts = 1;
				if (LastOfs - (int)CurrOfs < bts) {
					bts = ED_MESSAGE_TOO_SHORT;
				} 
				else {
					ED_LOCATOR_SET (&(Destin->IMSI_CLASS___LOCATOR), CurrOfs, bts);
					Destin->IMSI_CLASS = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
					/* Set the exported tag */
					pp_CS0004E_Details->userTagPresent[3] = 1;
					pp_CS0004E_Details->userTag[3] = (int)Destin->IMSI_CLASS;
				}
				if (bts < 0) {
					/* If decoding failed, set the failed field to "not present" */
					SETPRESENT_c_r_csch_PDU_Addressing_IMSI_CLASS(Destin, ED_FALSE);
					goto exitOnFail;
				}
				CurrOfs += bts;
			}
			if (((((Destin->MSID_TYPE==2)||(Destin->MSID_TYPE==3))||((Destin->MSID_TYPE==4)&&((Destin->EXT_MSID_TYPE_Present ? Destin->EXT_MSID_TYPE : 0)==1)))||((Destin->MSID_TYPE==4)&&((Destin->EXT_MSID_TYPE_Present ? Destin->EXT_MSID_TYPE : 0)==2)))) {
				SETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields(Destin, ED_TRUE);
				bts = DECODE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields (Buffer, CurrOfs, Destin->IMSI_class_specific_subfields, LastOfs-CurrOfs , pp_CS0004E_Details);
				if (bts < 0) {
					/* If decoding failed, set the failed field to "not present" */
					SETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields(Destin, ED_FALSE);
					goto exitOnFail;
				}
				CurrOfs += bts;
			}
			if ((Destin->MSID_TYPE==5)) {
				SETPRESENT_c_r_csch_PDU_Addressing_TMSI_ZONE(Destin, ED_TRUE);
				bts = (((Destin->MSID_LEN>4)) ? ((8*(Destin->MSID_LEN-4))) : (0));
				if (LastOfs - (int)CurrOfs < bts) {
					bts = ED_MESSAGE_TOO_SHORT;
				} 
				else {
					ED_LOCATOR_SET (&(Destin->TMSI_ZONE___LOCATOR), CurrOfs, bts);
					EDAllocBinary (&((Destin->TMSI_ZONE)->value), (unsigned)(bts), &((Destin->TMSI_ZONE)->usedBits));
					EDCopyBits ((Destin->TMSI_ZONE->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
				}
				if (bts < 0) {
					/* If decoding failed, set the failed field to "not present" */
					SETPRESENT_c_r_csch_PDU_Addressing_TMSI_ZONE(Destin, ED_FALSE);
					goto exitOnFail;
				}
				CurrOfs += bts;
			}
			if ((Destin->MSID_TYPE==5)) {
				SETPRESENT_c_r_csch_PDU_Addressing_TMSI_CODE_ADDR(Destin, ED_TRUE);
				bts = (((Destin->MSID_LEN>4)) ? (32) : ((8*Destin->MSID_LEN)));
				if (LastOfs - (int)CurrOfs < bts) {
					bts = ED_MESSAGE_TOO_SHORT;
				} 
				else {
					ED_LOCATOR_SET (&(Destin->TMSI_CODE_ADDR___LOCATOR), CurrOfs, bts);
					EDAllocBinary (&((Destin->TMSI_CODE_ADDR)->value), (unsigned)(bts), &((Destin->TMSI_CODE_ADDR)->usedBits));
					EDCopyBits ((Destin->TMSI_CODE_ADDR->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
				}
				if (bts < 0) {
					/* If decoding failed, set the failed field to "not present" */
					SETPRESENT_c_r_csch_PDU_Addressing_TMSI_CODE_ADDR(Destin, ED_FALSE);
					goto exitOnFail;
				}
				CurrOfs += bts;
			}
			/* RESERVED */
			/* Spare bits are optional */
			if ((Destin->MSID_TYPE==0)) {
				/* Decode spare bit(s) */
				bts = 6;
				if (LastOfs-CurrOfs < bts) {
					bts = ED_MESSAGE_TOO_SHORT;
					goto exitOnFail;
				}
				CurrOfs += bts;
			}
			/* The inner data should never overflow the available space by design */
			ED_ASSERT (CurrOfs <= NewLastOfs1);
			
			/* If needed, skip the extra bits and align to the calculated range */
			CurrOfs = NewLastOfs1;
			
			/* If the required data is too long, signal ED_MESSAGE_TOO_SHORT */
			if (NewLastOfs1 > LastOfs1) {
				bts = ED_MESSAGE_TOO_SHORT;
				goto exitOnFail;
			}
			
			/* Set back the LastOfs variable to the stored value */
			LastOfs = LastOfs1;
		}
		/* END OF PAD ZONE */
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_Addressing_IMSI_class_specific_subfields* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Addressing_IMSI */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		if (((pp_CS0004E_Details->userTag[3])==0)) {
			/* Field 'IMSI_CLASS_0' is required */
			ED_ASSERT (GETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0(Source));
			CurrOfs += ENCODE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0 (Buffer, CurrOfs, Source->IMSI_CLASS_0, pp_CS0004E_Details);
		}
		else {
			/* Field 'IMSI_CLASS_0' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0(Source));
		}
		if (((pp_CS0004E_Details->userTag[3])==1)) {
			/* Field 'IMSI_CLASS_1' is required */
			ED_ASSERT (GETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1(Source));
			CurrOfs += ENCODE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1 (Buffer, CurrOfs, Source->IMSI_CLASS_1, pp_CS0004E_Details);
		}
		else {
			/* Field 'IMSI_CLASS_1' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1(Source));
		}
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_Addressing_IMSI_class_specific_subfields* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Addressing_IMSI */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		if (((pp_CS0004E_Details->userTag[3])==0)) {
			SETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0(Destin, ED_TRUE);
			bts = DECODE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0 (Buffer, CurrOfs, Destin->IMSI_CLASS_0, LastOfs-CurrOfs , pp_CS0004E_Details);
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((pp_CS0004E_Details->userTag[3])==1)) {
			SETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1(Destin, ED_TRUE);
			bts = DECODE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1 (Buffer, CurrOfs, Destin->IMSI_CLASS_1, LastOfs-CurrOfs , pp_CS0004E_Details);
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Addressing_IMSI_0 */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->IMSI_CLASS_0_TYPE, 2);
		/* Encode spare bits */
		PUSH_INT (0, (((Source->IMSI_CLASS_0_TYPE==0)) ? (3) : ((((Source->IMSI_CLASS_0_TYPE==1)) ? (4) : ((((Source->IMSI_CLASS_0_TYPE==2)) ? (1) : (2)))))));
		if (((Source->IMSI_CLASS_0_TYPE==2)||(Source->IMSI_CLASS_0_TYPE==3))) {
			/* Field 'MCC10' is required */
			ED_ASSERT (GETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0_MCC10(Source));
			PUSH_INT (Source->MCC10, 10);
		}
		else {
			/* Field 'MCC10' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0_MCC10(Source));
		}
		if (((Source->IMSI_CLASS_0_TYPE==1)||(Source->IMSI_CLASS_0_TYPE==3))) {
			/* Field 'IMSI_11_12' is required */
			ED_ASSERT (GETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0_IMSI_11_12(Source));
			PUSH_INT (Source->IMSI_11_12, 7);
		}
		else {
			/* Field 'IMSI_11_12' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0_IMSI_11_12(Source));
		}
		PUSH_BIN (Source->IMSI_S, 34);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Addressing_IMSI_0 */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 2;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_CLASS_0_TYPE___LOCATOR), CurrOfs, bts);
			Destin->IMSI_CLASS_0_TYPE = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* Decode spare bit(s) */
		bts = (((Destin->IMSI_CLASS_0_TYPE==0)) ? (3) : ((((Destin->IMSI_CLASS_0_TYPE==1)) ? (4) : ((((Destin->IMSI_CLASS_0_TYPE==2)) ? (1) : (2))))));
		if (LastOfs-CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
			goto exitOnFail;
		}
		CurrOfs += bts;
		if (((Destin->IMSI_CLASS_0_TYPE==2)||(Destin->IMSI_CLASS_0_TYPE==3))) {
			SETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0_MCC10(Destin, ED_TRUE);
			bts = 10;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->MCC10___LOCATOR), CurrOfs, bts);
				Destin->MCC10 = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0_MCC10(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((Destin->IMSI_CLASS_0_TYPE==1)||(Destin->IMSI_CLASS_0_TYPE==3))) {
			SETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0_IMSI_11_12(Destin, ED_TRUE);
			bts = 7;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->IMSI_11_12___LOCATOR), CurrOfs, bts);
				Destin->IMSI_11_12 = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0_IMSI_11_12(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		bts = 34;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_S___LOCATOR), CurrOfs, bts);
			EDCopyBits (Destin->IMSI_S, 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Addressing_IMSI_1 */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->IMSI_CLASS_1_TYPE, 1);
		/* Spare bits are optional */
		if ((Source->IMSI_CLASS_1_TYPE==0)) {
			/* Encode spare bits */
			PUSH_INT (0, 2);
		}
		PUSH_INT (Source->IMSI_ADDR_NUM, 3);
		if ((Source->IMSI_CLASS_1_TYPE==1)) {
			/* Field 'MCC' is required */
			ED_ASSERT (GETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1_MCC(Source));
			PUSH_INT (Source->MCC, 10);
		}
		else {
			/* Field 'MCC' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1_MCC(Source));
		}
		PUSH_INT (Source->IMSI_11_12, 7);
		PUSH_BIN (Source->IMSI_S, 34);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Addressing_IMSI_1 */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_CLASS_1_TYPE___LOCATOR), CurrOfs, bts);
			Destin->IMSI_CLASS_1_TYPE = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* Spare bits are optional */
		if ((Destin->IMSI_CLASS_1_TYPE==0)) {
			/* Decode spare bit(s) */
			bts = 2;
			if (LastOfs-CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		bts = 3;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_ADDR_NUM___LOCATOR), CurrOfs, bts);
			Destin->IMSI_ADDR_NUM = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		if ((Destin->IMSI_CLASS_1_TYPE==1)) {
			SETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1_MCC(Destin, ED_TRUE);
			bts = 10;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->MCC___LOCATOR), CurrOfs, bts);
				Destin->MCC = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1_MCC(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		bts = 7;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_11_12___LOCATOR), CurrOfs, bts);
			Destin->IMSI_11_12 = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 34;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->IMSI_S___LOCATOR), CurrOfs, bts);
			EDCopyBits (Destin->IMSI_S, 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_Authentication (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_Authentication* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Authentication_And_Message_Integrity_Fields */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->MACI_INCL, 1);
		/* Set the exported tag */
		pp_CS0004E_Details->userTagPresent[2] = 1;
		pp_CS0004E_Details->userTag[2] = (int)Source->MACI_INCL;
		/* On REV<9, this is always zero */
		PUSH_INT (Source->AUTH_MODE_INCL, 1);
		/* This field is AUTH_MODE on REV<9, AUTH_INCL otherwise */
		if ((Source->AUTH_MODE_INCL==1)) {
			/* Field 'AUTHR' is required */
			ED_ASSERT (GETPRESENT_c_r_csch_PDU_Authentication_AUTHR(Source));
			PUSH_INT (Source->AUTHR, 18);
		}
		else {
			/* Field 'AUTHR' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Authentication_AUTHR(Source));
		}
		if ((Source->AUTH_MODE_INCL==1)) {
			/* Field 'RANDC' is required */
			ED_ASSERT (GETPRESENT_c_r_csch_PDU_Authentication_RANDC(Source));
			PUSH_INT (Source->RANDC, 8);
		}
		else {
			/* Field 'RANDC' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Authentication_RANDC(Source));
		}
		if ((Source->AUTH_MODE_INCL==1)) {
			/* Field 'COUNT' is required */
			ED_ASSERT (GETPRESENT_c_r_csch_PDU_Authentication_COUNT(Source));
			PUSH_INT (Source->COUNT, 6);
		}
		else {
			/* Field 'COUNT' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Authentication_COUNT(Source));
		}
		/* Revision 9 additions */
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&Source->MACI_INCL)) {
			/* Field 'SDU_KEY_ID' is required */
			ED_ASSERT (GETPRESENT_c_r_csch_PDU_Authentication_SDU_KEY_ID(Source));
			PUSH_INT (Source->SDU_KEY_ID, 2);
		}
		else {
			/* Field 'SDU_KEY_ID' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Authentication_SDU_KEY_ID(Source));
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&Source->MACI_INCL)) {
			/* Field 'SDU_INTEGRITY_ALGO' is required */
			ED_ASSERT (GETPRESENT_c_r_csch_PDU_Authentication_SDU_INTEGRITY_ALGO(Source));
			PUSH_INT (Source->SDU_INTEGRITY_ALGO, 3);
		}
		else {
			/* Field 'SDU_INTEGRITY_ALGO' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Authentication_SDU_INTEGRITY_ALGO(Source));
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&Source->MACI_INCL)) {
			/* Field 'SDU_SSEQ_OR_SSEQH' is required */
			ED_ASSERT (GETPRESENT_c_r_csch_PDU_Authentication_SDU_SSEQ_OR_SSEQH(Source));
			PUSH_INT (Source->SDU_SSEQ_OR_SSEQH, 1);
		}
		else {
			/* Field 'SDU_SSEQ_OR_SSEQH' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Authentication_SDU_SSEQ_OR_SSEQH(Source));
		}
		if ((((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&Source->MACI_INCL)&&!((Source->SDU_SSEQ_OR_SSEQH_Present ? Source->SDU_SSEQ_OR_SSEQH : 0)))) {
			/* Field 'SDU_SSEQ' is required */
			ED_ASSERT (GETPRESENT_c_r_csch_PDU_Authentication_SDU_SSEQ(Source));
			PUSH_INT (Source->SDU_SSEQ, 8);
		}
		else {
			/* Field 'SDU_SSEQ' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Authentication_SDU_SSEQ(Source));
		}
		if ((((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&Source->MACI_INCL)&&(Source->SDU_SSEQ_OR_SSEQH_Present ? Source->SDU_SSEQ_OR_SSEQH : 0))) {
			/* Field 'SDU_SSEQ_H' is required */
			ED_ASSERT (GETPRESENT_c_r_csch_PDU_Authentication_SDU_SSEQ_H(Source));
			PUSH_INT (Source->SDU_SSEQ_H, 24);
		}
		else {
			/* Field 'SDU_SSEQ_H' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Authentication_SDU_SSEQ_H(Source));
		}
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_Authentication (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_Authentication* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Authentication_And_Message_Integrity_Fields */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->MACI_INCL___LOCATOR), CurrOfs, bts);
			Destin->MACI_INCL = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			/* Set the exported tag */
			pp_CS0004E_Details->userTagPresent[2] = 1;
			pp_CS0004E_Details->userTag[2] = (int)Destin->MACI_INCL;
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* On REV<9, this is always zero */
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->AUTH_MODE_INCL___LOCATOR), CurrOfs, bts);
			Destin->AUTH_MODE_INCL = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* This field is AUTH_MODE on REV<9, AUTH_INCL otherwise */
		if ((Destin->AUTH_MODE_INCL==1)) {
			SETPRESENT_c_r_csch_PDU_Authentication_AUTHR(Destin, ED_TRUE);
			bts = 18;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->AUTHR___LOCATOR), CurrOfs, bts);
				Destin->AUTHR = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_csch_PDU_Authentication_AUTHR(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((Destin->AUTH_MODE_INCL==1)) {
			SETPRESENT_c_r_csch_PDU_Authentication_RANDC(Destin, ED_TRUE);
			bts = 8;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->RANDC___LOCATOR), CurrOfs, bts);
				Destin->RANDC = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_csch_PDU_Authentication_RANDC(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((Destin->AUTH_MODE_INCL==1)) {
			SETPRESENT_c_r_csch_PDU_Authentication_COUNT(Destin, ED_TRUE);
			bts = 6;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->COUNT___LOCATOR), CurrOfs, bts);
				Destin->COUNT = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_csch_PDU_Authentication_COUNT(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		/* Revision 9 additions */
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&Destin->MACI_INCL)) {
			SETPRESENT_c_r_csch_PDU_Authentication_SDU_KEY_ID(Destin, ED_TRUE);
			bts = 2;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_KEY_ID___LOCATOR), CurrOfs, bts);
				Destin->SDU_KEY_ID = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_csch_PDU_Authentication_SDU_KEY_ID(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&Destin->MACI_INCL)) {
			SETPRESENT_c_r_csch_PDU_Authentication_SDU_INTEGRITY_ALGO(Destin, ED_TRUE);
			bts = 3;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_INTEGRITY_ALGO___LOCATOR), CurrOfs, bts);
				Destin->SDU_INTEGRITY_ALGO = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_csch_PDU_Authentication_SDU_INTEGRITY_ALGO(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&Destin->MACI_INCL)) {
			SETPRESENT_c_r_csch_PDU_Authentication_SDU_SSEQ_OR_SSEQH(Destin, ED_TRUE);
			bts = 1;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_SSEQ_OR_SSEQH___LOCATOR), CurrOfs, bts);
				Destin->SDU_SSEQ_OR_SSEQH = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_csch_PDU_Authentication_SDU_SSEQ_OR_SSEQH(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&Destin->MACI_INCL)&&!((Destin->SDU_SSEQ_OR_SSEQH_Present ? Destin->SDU_SSEQ_OR_SSEQH : 0)))) {
			SETPRESENT_c_r_csch_PDU_Authentication_SDU_SSEQ(Destin, ED_TRUE);
			bts = 8;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_SSEQ___LOCATOR), CurrOfs, bts);
				Destin->SDU_SSEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_csch_PDU_Authentication_SDU_SSEQ(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&Destin->MACI_INCL)&&(Destin->SDU_SSEQ_OR_SSEQH_Present ? Destin->SDU_SSEQ_OR_SSEQH : 0))) {
			SETPRESENT_c_r_csch_PDU_Authentication_SDU_SSEQ_H(Destin, ED_TRUE);
			bts = 24;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_SSEQ_H___LOCATOR), CurrOfs, bts);
				Destin->SDU_SSEQ_H = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_csch_PDU_Authentication_SDU_SSEQ_H(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_Extended_Encryption (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_Extended_Encryption* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Extended_Encryption */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->ENC_FIELDS_INCL, 1);
		if (Source->ENC_FIELDS_INCL) {
			/* Field 'SDU_ENCRYPT_MODE' is required */
			ED_ASSERT (GETPRESENT_c_r_csch_PDU_Extended_Encryption_SDU_ENCRYPT_MODE(Source));
			PUSH_INT (Source->SDU_ENCRYPT_MODE, 3);
		}
		else {
			/* Field 'SDU_ENCRYPT_MODE' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Extended_Encryption_SDU_ENCRYPT_MODE(Source));
		}
		if ((((Source->SDU_ENCRYPT_MODE_Present ? Source->SDU_ENCRYPT_MODE : 0)==1)||((Source->SDU_ENCRYPT_MODE_Present ? Source->SDU_ENCRYPT_MODE : 0)==2))) {
			/* Field 'ENC_SEQ' is required */
			ED_ASSERT (GETPRESENT_c_r_csch_PDU_Extended_Encryption_ENC_SEQ(Source));
			PUSH_INT (Source->ENC_SEQ, 8);
		}
		else {
			/* Field 'ENC_SEQ' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Extended_Encryption_ENC_SEQ(Source));
		}
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_Extended_Encryption (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_Extended_Encryption* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Extended_Encryption */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ENC_FIELDS_INCL___LOCATOR), CurrOfs, bts);
			Destin->ENC_FIELDS_INCL = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		if (Destin->ENC_FIELDS_INCL) {
			SETPRESENT_c_r_csch_PDU_Extended_Encryption_SDU_ENCRYPT_MODE(Destin, ED_TRUE);
			bts = 3;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_ENCRYPT_MODE___LOCATOR), CurrOfs, bts);
				Destin->SDU_ENCRYPT_MODE = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_csch_PDU_Extended_Encryption_SDU_ENCRYPT_MODE(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((((Destin->SDU_ENCRYPT_MODE_Present ? Destin->SDU_ENCRYPT_MODE : 0)==1)||((Destin->SDU_ENCRYPT_MODE_Present ? Destin->SDU_ENCRYPT_MODE : 0)==2))) {
			SETPRESENT_c_r_csch_PDU_Extended_Encryption_ENC_SEQ(Destin, ED_TRUE);
			bts = 8;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->ENC_SEQ___LOCATOR), CurrOfs, bts);
				Destin->ENC_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_csch_PDU_Extended_Encryption_ENC_SEQ(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_Radio_Environment_Report (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_Radio_Environment_Report* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Radio_Environment_Report */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int max=0;
		int cnt;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->ACTIVE_PILOT_STRENGTH, 6);
		PUSH_INT (Source->FIRST_IS_ACTIVE, 1);
		PUSH_INT (Source->FIRST_IS_PTA, 1);
		PUSH_INT (Source->NUM_ADD_PILOTS, 3);
		/* NUM_ADD_PILOTS occurrences of the following record: */
		max = Source->NUM_ADD_PILOTS;
		ED_ASSERT (max == Source->ADD_PILOTS.items);
		if (Source->ADD_PILOTS.items < max) max = Source->ADD_PILOTS.items;
		for (cnt=0; cnt<max; cnt++) {
			CurrOfs += ENCODE_c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data (Buffer, CurrOfs, Source->ADD_PILOTS.data [cnt], pp_CS0004E_Details);
		}
		if ((pp_CS0004E_Details->n_P_REV_IN_USEs>=7)) {
			/* Field 'Aux_Radio_Environment_Report' is required */
			ED_ASSERT (GETPRESENT_c_r_csch_Radio_Environment_Report_Aux_Radio_Environment_Report(Source));
			CurrOfs += ENCODE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report (Buffer, CurrOfs, Source->Aux_Radio_Environment_Report, pp_CS0004E_Details);
		}
		else {
			/* Field 'Aux_Radio_Environment_Report' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_csch_Radio_Environment_Report_Aux_Radio_Environment_Report(Source));
		}
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_Radio_Environment_Report (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_Radio_Environment_Report* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Radio_Environment_Report */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int cnt;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 6;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ACTIVE_PILOT_STRENGTH___LOCATOR), CurrOfs, bts);
			Destin->ACTIVE_PILOT_STRENGTH = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->FIRST_IS_ACTIVE___LOCATOR), CurrOfs, bts);
			Destin->FIRST_IS_ACTIVE = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->FIRST_IS_PTA___LOCATOR), CurrOfs, bts);
			Destin->FIRST_IS_PTA = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 3;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->NUM_ADD_PILOTS___LOCATOR), CurrOfs, bts);
			Destin->NUM_ADD_PILOTS = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* NUM_ADD_PILOTS occurrences of the following record: */
		/* Decode field ADD_PILOTS - sequence */
		SETITEMS_c_r_csch_Radio_Environment_Report_ADD_PILOTS(&Destin->ADD_PILOTS, Destin->NUM_ADD_PILOTS);
		for (cnt=0; cnt<Destin->ADD_PILOTS.items; cnt++) {
			bts = DECODE_c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data (Buffer, CurrOfs, Destin->ADD_PILOTS.data [cnt], LastOfs-CurrOfs , pp_CS0004E_Details);
			if (bts < 0) {
				/* Decoding failed - Remove the unused array items */
				SETITEMS_c_r_csch_Radio_Environment_Report_ADD_PILOTS (&Destin->ADD_PILOTS, cnt);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((pp_CS0004E_Details->n_P_REV_IN_USEs>=7)) {
			SETPRESENT_c_r_csch_Radio_Environment_Report_Aux_Radio_Environment_Report(Destin, ED_TRUE);
			bts = DECODE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report (Buffer, CurrOfs, Destin->Aux_Radio_Environment_Report, LastOfs-CurrOfs , pp_CS0004E_Details);
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_csch_Radio_Environment_Report_Aux_Radio_Environment_Report(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Radio_Environment_Report_Rev7 */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* NUM_AUX_PILOTS occurrences of the following record, P_REV_IN_USE_NOCSN_04 >= 7: */
		PUSH_INT (Source->NUM_AUX_PILOTS, 3);
		if (Source->NUM_AUX_PILOTS) {
			/* Field 'AUX_PILOTS' is required */
			ED_ASSERT (GETPRESENT_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS(Source));
			CurrOfs += ENCODE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS (Buffer, CurrOfs, Source->AUX_PILOTS, pp_CS0004E_Details);
		}
		else {
			/* Field 'AUX_PILOTS' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS(Source));
		}
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Radio_Environment_Report_Rev7 */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		/* NUM_AUX_PILOTS occurrences of the following record, P_REV_IN_USE_NOCSN_04 >= 7: */
		bts = 3;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->NUM_AUX_PILOTS___LOCATOR), CurrOfs, bts);
			Destin->NUM_AUX_PILOTS = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		if (Destin->NUM_AUX_PILOTS) {
			SETPRESENT_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS(Destin, ED_TRUE);
			bts = DECODE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS (Buffer, CurrOfs, Destin->AUX_PILOTS, LastOfs-CurrOfs , pp_CS0004E_Details);
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Radio_Environment_Report_ADD_PILOTS */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->PILOT_PN_PHASE, 15);
		PUSH_INT (Source->PILOT_STRENGTH, 6);
		PUSH_INT (Source->ACCESS_HO_EN, 1);
		PUSH_INT (Source->ACCESS_ATTEMPTED, 1);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Radio_Environment_Report_ADD_PILOTS */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 15;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->PILOT_PN_PHASE___LOCATOR), CurrOfs, bts);
			Destin->PILOT_PN_PHASE = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 6;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->PILOT_STRENGTH___LOCATOR), CurrOfs, bts);
			Destin->PILOT_STRENGTH = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ACCESS_HO_EN___LOCATOR), CurrOfs, bts);
			Destin->ACCESS_HO_EN = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ACCESS_ATTEMPTED___LOCATOR), CurrOfs, bts);
			Destin->ACCESS_ATTEMPTED = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Radio_Environment_Report_AUX_PILOTS */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->PILOT_PN_PHASE, 15);
		PUSH_INT (Source->PILOT_STRENGTH, 6);
		PUSH_INT (Source->PILOT_REC_TYPE, 3);
		/* Set the exported tag */
		pp_CS0004E_Details->userTagPresent[4] = 1;
		pp_CS0004E_Details->userTag[4] = (int)Source->PILOT_REC_TYPE;
		PUSH_INT (Source->RECORD_LEN, 3);
		/* BEGIN OF PAD ZONE - ENCODE inclusive=0 bits=3 octet(=0)/bit(=1)=0 */
		{
			ED_EXLONG dataStartOfs0 = CurrOfs;
			int lenInBits0;
			/* Type-specific fields */
			CurrOfs += ENCODE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields (Buffer, CurrOfs, (&(Source->Type_specific_fields)), pp_CS0004E_Details);
			/* Calculate the encoded length in octets */
			lenInBits0 = (CurrOfs-dataStartOfs0);
			
			/* Save the encoded length into the length field */
			EDIntToBits (Buffer, dataStartOfs0-3, ((lenInBits0+7)/8)-0, 3);
			
			/* Pad if required */
			if ((lenInBits0 & 0x07) != 0) {
				PUSH_INT (0, 8-(lenInBits0 & 0x07));
			}
		}
		/* END OF PAD ZONE */
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Radio_Environment_Report_AUX_PILOTS */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 15;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->PILOT_PN_PHASE___LOCATOR), CurrOfs, bts);
			Destin->PILOT_PN_PHASE = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 6;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->PILOT_STRENGTH___LOCATOR), CurrOfs, bts);
			Destin->PILOT_STRENGTH = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 3;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->PILOT_REC_TYPE___LOCATOR), CurrOfs, bts);
			Destin->PILOT_REC_TYPE = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			/* Set the exported tag */
			pp_CS0004E_Details->userTagPresent[4] = 1;
			pp_CS0004E_Details->userTag[4] = (int)Destin->PILOT_REC_TYPE;
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 3;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->RECORD_LEN___LOCATOR), CurrOfs, bts);
			Destin->RECORD_LEN = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* BEGIN OF PAD ZONE - DECODE inclusive=0 bits=3 octet(=0)/bit(=1)=0 */
		{
			/* Save the current final offset position */
			int LastOfs1 = LastOfs;
			
			/* Calculate the new final offset position */
			int NewLastOfs1 = CurrOfs +
			EDBitsToInt (Buffer, CurrOfs-3, 3) * 8;
			
			/* Temporarely set the new LastOfs value */
			LastOfs = NewLastOfs1;
			
			/* Execute the normal decoding */
			/* Type-specific fields */
			bts = DECODE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields (Buffer, CurrOfs, (&(Destin->Type_specific_fields)), LastOfs-CurrOfs , pp_CS0004E_Details);
			if (bts < 0) {
				/* Decoding failed - Go to the exit point */
				goto exitOnFail;
			}
			CurrOfs += bts;
			/* The inner data should never overflow the available space by design */
			ED_ASSERT (CurrOfs <= NewLastOfs1);
			
			/* If needed, skip the extra bits and align to the calculated range */
			CurrOfs = NewLastOfs1;
			
			/* If the required data is too long, signal ED_MESSAGE_TOO_SHORT */
			if (NewLastOfs1 > LastOfs1) {
				bts = ED_MESSAGE_TOO_SHORT;
				goto exitOnFail;
			}
			
			/* Set back the LastOfs variable to the stored value */
			LastOfs = LastOfs1;
		}
		/* END OF PAD ZONE */
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Radio_Environment_Report_Fields */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		if (((pp_CS0004E_Details->userTag[4])==0)) {
			/* Field 'Walsh' is required */
			ED_ASSERT (GETPRESENT_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh(Source));
			CurrOfs += ENCODE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh (Buffer, CurrOfs, Source->Walsh, pp_CS0004E_Details);
		}
		else {
			/* Field 'Walsh' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh(Source));
		}
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Radio_Environment_Report_Fields */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		if (((pp_CS0004E_Details->userTag[4])==0)) {
			SETPRESENT_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh(Destin, ED_TRUE);
			bts = DECODE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh (Buffer, CurrOfs, Destin->Walsh, LastOfs-CurrOfs , pp_CS0004E_Details);
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Radio_Environment_Report_Fields_Walsh */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->QOF, 2);
		PUSH_INT (Source->WALSH_LENGTH, 3);
		/* Number of bits prepared in the binary field must match the calculated expression below isArray=0 isOptional=0 */
		ED_ASSERT ((&(Source->PILOT_WALSH))->usedBits == (int) (Source->WALSH_LENGTH+6));
		PUSH_BIN ((&(Source->PILOT_WALSH))->value, (&(Source->PILOT_WALSH))->usedBits);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_csch_Radio_Environment_Report_Fields_Walsh */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_r_csch_PDU
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 2;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->QOF___LOCATOR), CurrOfs, bts);
			Destin->QOF = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 3;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->WALSH_LENGTH___LOCATOR), CurrOfs, bts);
			Destin->WALSH_LENGTH = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = (Destin->WALSH_LENGTH+6);
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->PILOT_WALSH___LOCATOR), CurrOfs, bts);
			EDAllocBinary (&(((&(Destin->PILOT_WALSH)))->value), (unsigned)(bts), &(((&(Destin->PILOT_WALSH)))->usedBits));
			EDCopyBits (((&(Destin->PILOT_WALSH))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_PDU_Regular (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_PDU_Regular* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_dsch_PDU_Regular */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_f_dsch_PDU_Regular
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* Reset exported tag 5 'MACI_INCL' */
		pp_CS0004E_Details->userTagPresent[0] = 0;
		pp_CS0004E_Details->userTag[0] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[0], "f_dsch_PDU_Regular", "MACI_INCL");
		pp_CS0004E_Details->userTagBusy[0] = 1;
#endif
		/* Reset exported tag 32 'ENCRYPTION' */
		pp_CS0004E_Details->userTagPresent[1] = 0;
		pp_CS0004E_Details->userTag[1] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[1], "f_dsch_PDU_Regular", "ENCRYPTION");
		pp_CS0004E_Details->userTagBusy[1] = 1;
#endif
		/* Mark the beginning of the PDU, to allow correct padding */
		pp_CS0004E_Details->n_PDU_START_OFFSET = CurrOfs;
		
		CurrOfs += ENCODE_c_f_dsch_PDU_Regular_Message_Type (Buffer, CurrOfs, (&(Source->Message_Type)), pp_CS0004E_Details);
		CurrOfs += ENCODE_c_f_dsch_PDU_Regular_ARQ (Buffer, CurrOfs, (&(Source->ARQ)), pp_CS0004E_Details);
		CurrOfs += ENCODE_c_f_dsch_PDU_Regular_Encryption (Buffer, CurrOfs, (&(Source->Encryption)), pp_CS0004E_Details);
		CurrOfs += ENCODE_c_f_dsch_PDU_Regular_Integrity_Fields (Buffer, CurrOfs, (&(Source->Integrity_Fields)), pp_CS0004E_Details);
		/* Available from P_REV_IN_USE >= 9 */
		CurrOfs += ENCODE_c_f_dsch_PDU_Regular_Extended_Encryption (Buffer, CurrOfs, (&(Source->Extended_Encryption)), pp_CS0004E_Details);
		
		PUSH_BIN ((&(Source->SDU))->value, (&(Source->SDU))->usedBits);
		
		/* PADDING */
		CurrOfs = CS0004E_PDU_Padding_Encode (Buffer, CurrOfs, pp_CS0004E_Details);
		
		if ((pp_CS0004E_Details->userTag[0])) {
			/* Field 'MACI' is required */
			ED_ASSERT (GETPRESENT_c_f_dsch_PDU_Regular_MACI(Source));
			PUSH_INT (Source->MACI, 32);
		}
		else {
			/* Field 'MACI' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_dsch_PDU_Regular_MACI(Source));
		}
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[0], "f_dsch_PDU_Regular", "MACI_INCL");
		pp_CS0004E_Details->userTagBusy[0] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[1], "f_dsch_PDU_Regular", "ENCRYPTION");
		pp_CS0004E_Details->userTagBusy[1] = 0;
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_PDU_Regular (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_PDU_Regular* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_dsch_PDU_Regular */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_f_dsch_PDU_Regular
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		/* Reset exported tag 5 'MACI_INCL' */
		pp_CS0004E_Details->userTagPresent[0] = 0;
		pp_CS0004E_Details->userTag[0] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[0], "f_dsch_PDU_Regular", "MACI_INCL");
		pp_CS0004E_Details->userTagBusy[0] = 1;
#endif
		/* Reset exported tag 32 'ENCRYPTION' */
		pp_CS0004E_Details->userTagPresent[1] = 0;
		pp_CS0004E_Details->userTag[1] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[1], "f_dsch_PDU_Regular", "ENCRYPTION");
		pp_CS0004E_Details->userTagBusy[1] = 1;
#endif
		/* Mark the beginning of the PDU, to allow correct padding */
		pp_CS0004E_Details->n_PDU_START_OFFSET = CurrOfs;
		
		bts = DECODE_c_f_dsch_PDU_Regular_Message_Type (Buffer, CurrOfs, (&(Destin->Message_Type)), LastOfs-CurrOfs , pp_CS0004E_Details);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = DECODE_c_f_dsch_PDU_Regular_ARQ (Buffer, CurrOfs, (&(Destin->ARQ)), LastOfs-CurrOfs , pp_CS0004E_Details);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = DECODE_c_f_dsch_PDU_Regular_Encryption (Buffer, CurrOfs, (&(Destin->Encryption)), LastOfs-CurrOfs , pp_CS0004E_Details);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = DECODE_c_f_dsch_PDU_Regular_Integrity_Fields (Buffer, CurrOfs, (&(Destin->Integrity_Fields)), LastOfs-CurrOfs , pp_CS0004E_Details);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* Available from P_REV_IN_USE >= 9 */
		bts = DECODE_c_f_dsch_PDU_Regular_Extended_Encryption (Buffer, CurrOfs, (&(Destin->Extended_Encryption)), LastOfs-CurrOfs , pp_CS0004E_Details);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* In case MACI is included, reduce the size of 32 bits */
		{
			int OldLastOfs = LastOfs;
			if (pp_CS0004E_Details->userTag[0]/*MACI_INCL*/) {
				ED_ASSERT (LastOfs >= 32);
				LastOfs -= 32;
			}
		bts = (int)(LastOfs-CurrOfs);
		ED_LOCATOR_SET (&(Destin->SDU___LOCATOR), CurrOfs, bts);
		EDAllocBinary (&(((&(Destin->SDU)))->value), (unsigned)bts, &(((&(Destin->SDU)))->usedBits));
		EDCopyBits (((&(Destin->SDU))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
			LastOfs = OldLastOfs;
		}
		/* PADDING */
		
		CurrOfs = CS0004E_PDU_Padding_Decode (CurrOfs, LastOfs, pp_CS0004E_Details);
		if ((pp_CS0004E_Details->userTag[0])) {
			SETPRESENT_c_f_dsch_PDU_Regular_MACI(Destin, ED_TRUE);
			bts = 32;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->MACI___LOCATOR), CurrOfs, bts);
				Destin->MACI = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_dsch_PDU_Regular_MACI(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[0], "f_dsch_PDU_Regular", "MACI_INCL");
		pp_CS0004E_Details->userTagBusy[0] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[1], "f_dsch_PDU_Regular", "ENCRYPTION");
		pp_CS0004E_Details->userTagBusy[1] = 0;
#endif
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[0], "f_dsch_PDU_Regular", "MACI_INCL");
		pp_CS0004E_Details->userTagBusy[0] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[1], "f_dsch_PDU_Regular", "ENCRYPTION");
		pp_CS0004E_Details->userTagBusy[1] = 0;
#endif
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_PDU_Regular_Message_Type (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_PDU_Regular_Message_Type* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_dsch_Regular_Message_Type */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_f_dsch_PDU_Regular
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->MSG_TYPE, 8);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_PDU_Regular_Message_Type (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_PDU_Regular_Message_Type* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_dsch_Regular_Message_Type */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_f_dsch_PDU_Regular
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 8;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->MSG_TYPE___LOCATOR), CurrOfs, bts);
			Destin->MSG_TYPE = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_PDU_Regular_ARQ (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_PDU_Regular_ARQ* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_dsch_Regular_ARQ_Regular */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_f_dsch_PDU_Regular
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->ACK_SEQ, 3);
		PUSH_INT (Source->MSG_SEQ, 3);
		PUSH_INT (Source->ACK_REQ, 1);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_PDU_Regular_ARQ (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_PDU_Regular_ARQ* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_dsch_Regular_ARQ_Regular */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_f_dsch_PDU_Regular
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 3;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ACK_SEQ___LOCATOR), CurrOfs, bts);
			Destin->ACK_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 3;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->MSG_SEQ___LOCATOR), CurrOfs, bts);
			Destin->MSG_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ACK_REQ___LOCATOR), CurrOfs, bts);
			Destin->ACK_REQ = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_PDU_Regular_Encryption (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_PDU_Regular_Encryption* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_dsch_Regular_Encryption */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_f_dsch_PDU_Regular
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->ENCRYPTION, 2);
		/* Set the exported tag */
		pp_CS0004E_Details->userTagPresent[1] = 1;
		pp_CS0004E_Details->userTag[1] = (int)Source->ENCRYPTION;
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_PDU_Regular_Encryption (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_PDU_Regular_Encryption* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_dsch_Regular_Encryption */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_f_dsch_PDU_Regular
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 2;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ENCRYPTION___LOCATOR), CurrOfs, bts);
			Destin->ENCRYPTION = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			/* Set the exported tag */
			pp_CS0004E_Details->userTagPresent[1] = 1;
			pp_CS0004E_Details->userTag[1] = (int)Destin->ENCRYPTION;
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_PDU_Regular_Integrity_Fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_PDU_Regular_Integrity_Fields* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_dsch_Regular_Integrity_Fields */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_f_dsch_PDU_Regular
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		if ((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)) {
			/* Field 'MACI_INCL' is required */
			ED_ASSERT (GETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_MACI_INCL(Source));
			PUSH_INT (Source->MACI_INCL, 1);
			/* Set the exported tag */
			pp_CS0004E_Details->userTagPresent[0] = 1;
			pp_CS0004E_Details->userTag[0] = (int)Source->MACI_INCL;
		}
		else {
			/* Field 'MACI_INCL' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_MACI_INCL(Source));
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Source->MACI_INCL_Present ? Source->MACI_INCL : 0))) {
			/* Field 'SDU_KEY_ID' is required */
			ED_ASSERT (GETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_KEY_ID(Source));
			PUSH_INT (Source->SDU_KEY_ID, 2);
		}
		else {
			/* Field 'SDU_KEY_ID' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_KEY_ID(Source));
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Source->MACI_INCL_Present ? Source->MACI_INCL : 0))) {
			/* Field 'SDU_INTEGRITY_ALGO' is required */
			ED_ASSERT (GETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_INTEGRITY_ALGO(Source));
			PUSH_INT (Source->SDU_INTEGRITY_ALGO, 3);
		}
		else {
			/* Field 'SDU_INTEGRITY_ALGO' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_INTEGRITY_ALGO(Source));
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Source->MACI_INCL_Present ? Source->MACI_INCL : 0))) {
			/* Field 'SDU_SSEQ_OR_SSEQH' is required */
			ED_ASSERT (GETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_OR_SSEQH(Source));
			PUSH_INT (Source->SDU_SSEQ_OR_SSEQH, 1);
		}
		else {
			/* Field 'SDU_SSEQ_OR_SSEQH' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_OR_SSEQH(Source));
		}
		if ((((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Source->MACI_INCL_Present ? Source->MACI_INCL : 0))&&!((Source->SDU_SSEQ_OR_SSEQH_Present ? Source->SDU_SSEQ_OR_SSEQH : 0)))) {
			/* Field 'SDU_SSEQ' is required */
			ED_ASSERT (GETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ(Source));
			PUSH_INT (Source->SDU_SSEQ, 8);
		}
		else {
			/* Field 'SDU_SSEQ' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ(Source));
		}
		if ((((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Source->MACI_INCL_Present ? Source->MACI_INCL : 0))&&(Source->SDU_SSEQ_OR_SSEQH_Present ? Source->SDU_SSEQ_OR_SSEQH : 0))) {
			/* Field 'SDU_SSEQ_H' is required */
			ED_ASSERT (GETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_H(Source));
			PUSH_INT (Source->SDU_SSEQ_H, 24);
		}
		else {
			/* Field 'SDU_SSEQ_H' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_H(Source));
		}
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_PDU_Regular_Integrity_Fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_PDU_Regular_Integrity_Fields* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_dsch_Regular_Integrity_Fields */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_f_dsch_PDU_Regular
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		if ((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)) {
			SETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_MACI_INCL(Destin, ED_TRUE);
			bts = 1;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->MACI_INCL___LOCATOR), CurrOfs, bts);
				Destin->MACI_INCL = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
				/* Set the exported tag */
				pp_CS0004E_Details->userTagPresent[0] = 1;
				pp_CS0004E_Details->userTag[0] = (int)Destin->MACI_INCL;
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_MACI_INCL(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Destin->MACI_INCL_Present ? Destin->MACI_INCL : 0))) {
			SETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_KEY_ID(Destin, ED_TRUE);
			bts = 2;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_KEY_ID___LOCATOR), CurrOfs, bts);
				Destin->SDU_KEY_ID = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_KEY_ID(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Destin->MACI_INCL_Present ? Destin->MACI_INCL : 0))) {
			SETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_INTEGRITY_ALGO(Destin, ED_TRUE);
			bts = 3;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_INTEGRITY_ALGO___LOCATOR), CurrOfs, bts);
				Destin->SDU_INTEGRITY_ALGO = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_INTEGRITY_ALGO(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Destin->MACI_INCL_Present ? Destin->MACI_INCL : 0))) {
			SETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_OR_SSEQH(Destin, ED_TRUE);
			bts = 1;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_SSEQ_OR_SSEQH___LOCATOR), CurrOfs, bts);
				Destin->SDU_SSEQ_OR_SSEQH = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_OR_SSEQH(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Destin->MACI_INCL_Present ? Destin->MACI_INCL : 0))&&!((Destin->SDU_SSEQ_OR_SSEQH_Present ? Destin->SDU_SSEQ_OR_SSEQH : 0)))) {
			SETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ(Destin, ED_TRUE);
			bts = 8;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_SSEQ___LOCATOR), CurrOfs, bts);
				Destin->SDU_SSEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Destin->MACI_INCL_Present ? Destin->MACI_INCL : 0))&&(Destin->SDU_SSEQ_OR_SSEQH_Present ? Destin->SDU_SSEQ_OR_SSEQH : 0))) {
			SETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_H(Destin, ED_TRUE);
			bts = 24;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_SSEQ_H___LOCATOR), CurrOfs, bts);
				Destin->SDU_SSEQ_H = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_H(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_PDU_Regular_Extended_Encryption (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_PDU_Regular_Extended_Encryption* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_dsch_Regular_Extended_Encryption */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_f_dsch_PDU_Regular
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=7)&&((pp_CS0004E_Details->userTag[1])==3))) {
			/* Field 'SDU_ENCRYPT_MODE' is required */
			ED_ASSERT (GETPRESENT_c_f_dsch_PDU_Regular_Extended_Encryption_SDU_ENCRYPT_MODE(Source));
			PUSH_INT (Source->SDU_ENCRYPT_MODE, 3);
		}
		else {
			/* Field 'SDU_ENCRYPT_MODE' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_dsch_PDU_Regular_Extended_Encryption_SDU_ENCRYPT_MODE(Source));
		}
		if ((Source->SDU_ENCRYPT_MODE_Present&&(((Source->SDU_ENCRYPT_MODE_Present ? Source->SDU_ENCRYPT_MODE : 0)==1)||((Source->SDU_ENCRYPT_MODE_Present ? Source->SDU_ENCRYPT_MODE : 0)==2)))) {
			/* Field 'ENC_SEQ' is required */
			ED_ASSERT (GETPRESENT_c_f_dsch_PDU_Regular_Extended_Encryption_ENC_SEQ(Source));
			PUSH_INT (Source->ENC_SEQ, 8);
		}
		else {
			/* Field 'ENC_SEQ' must be absent */
			ED_ASSERT (!GETPRESENT_c_f_dsch_PDU_Regular_Extended_Encryption_ENC_SEQ(Source));
		}
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_PDU_Regular_Extended_Encryption (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_PDU_Regular_Extended_Encryption* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_dsch_Regular_Extended_Encryption */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_f_dsch_PDU_Regular
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=7)&&((pp_CS0004E_Details->userTag[1])==3))) {
			SETPRESENT_c_f_dsch_PDU_Regular_Extended_Encryption_SDU_ENCRYPT_MODE(Destin, ED_TRUE);
			bts = 3;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_ENCRYPT_MODE___LOCATOR), CurrOfs, bts);
				Destin->SDU_ENCRYPT_MODE = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_dsch_PDU_Regular_Extended_Encryption_SDU_ENCRYPT_MODE(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((Destin->SDU_ENCRYPT_MODE_Present&&(((Destin->SDU_ENCRYPT_MODE_Present ? Destin->SDU_ENCRYPT_MODE : 0)==1)||((Destin->SDU_ENCRYPT_MODE_Present ? Destin->SDU_ENCRYPT_MODE : 0)==2)))) {
			SETPRESENT_c_f_dsch_PDU_Regular_Extended_Encryption_ENC_SEQ(Destin, ED_TRUE);
			bts = 8;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->ENC_SEQ___LOCATOR), CurrOfs, bts);
				Destin->ENC_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_f_dsch_PDU_Regular_Extended_Encryption_ENC_SEQ(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_PDU_Mini (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_PDU_Mini* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_dsch_PDU_Mini */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_f_dsch_PDU_Mini
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* Mark the beginning of the PDU, to allow correct padding */
		pp_CS0004E_Details->n_PDU_START_OFFSET = CurrOfs;
		
		CurrOfs += ENCODE_c_f_dsch_PDU_Mini_ARQ (Buffer, CurrOfs, (&(Source->ARQ)), pp_CS0004E_Details);
		CurrOfs += ENCODE_c_f_dsch_PDU_Mini_Message_Type (Buffer, CurrOfs, (&(Source->Message_Type)), pp_CS0004E_Details);
		PUSH_BIN ((&(Source->SDU))->value, (&(Source->SDU))->usedBits);
		/* PADDING */
		CurrOfs = CS0004E_PDU_Padding_Encode (Buffer, CurrOfs, pp_CS0004E_Details);
		
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_PDU_Mini (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_PDU_Mini* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_dsch_PDU_Mini */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_f_dsch_PDU_Mini
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		/* Mark the beginning of the PDU, to allow correct padding */
		pp_CS0004E_Details->n_PDU_START_OFFSET = CurrOfs;
		
		bts = DECODE_c_f_dsch_PDU_Mini_ARQ (Buffer, CurrOfs, (&(Destin->ARQ)), LastOfs-CurrOfs , pp_CS0004E_Details);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = DECODE_c_f_dsch_PDU_Mini_Message_Type (Buffer, CurrOfs, (&(Destin->Message_Type)), LastOfs-CurrOfs , pp_CS0004E_Details);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = (int)(LastOfs-CurrOfs);
		ED_LOCATOR_SET (&(Destin->SDU___LOCATOR), CurrOfs, bts);
		EDAllocBinary (&(((&(Destin->SDU)))->value), (unsigned)bts, &(((&(Destin->SDU)))->usedBits));
		EDCopyBits (((&(Destin->SDU))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* PADDING */
		
		CurrOfs = CS0004E_PDU_Padding_Decode (CurrOfs, LastOfs, pp_CS0004E_Details);
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_PDU_Mini_ARQ (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_PDU_Mini_ARQ* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_dsch_ARQ_Mini */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_f_dsch_PDU_Mini
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->ACK_SEQ, 2);
		PUSH_INT (Source->MSG_SEQ, 2);
		PUSH_INT (Source->ACK_REQ, 1);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_PDU_Mini_ARQ (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_PDU_Mini_ARQ* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_dsch_ARQ_Mini */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_f_dsch_PDU_Mini
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 2;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ACK_SEQ___LOCATOR), CurrOfs, bts);
			Destin->ACK_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 2;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->MSG_SEQ___LOCATOR), CurrOfs, bts);
			Destin->MSG_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ACK_REQ___LOCATOR), CurrOfs, bts);
			Destin->ACK_REQ = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_PDU_Mini_Message_Type (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_PDU_Mini_Message_Type* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_dsch_Message_Type_Mini */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_f_dsch_PDU_Mini
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* If first bit is 0, the MSG_TYPE is three bits long (see table 3.2.2.2.1.2-2) */
		/* If first bit is 1, the MSG_TYPE is six bits long (see table 3.2.2.2.1.2-2) */
		{
		
			int MSG_TYPE_LEN = (ED_THIS->MSG_TYPE <= 7 ? 3 : 6);
		
		
			EDIntToBits (Buffer, CurrOfs, ED_THIS->MSG_TYPE, MSG_TYPE_LEN);
			CurrOfs += MSG_TYPE_LEN;
		}
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_PDU_Mini_Message_Type (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_PDU_Mini_Message_Type* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_dsch_Message_Type_Mini */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_f_dsch_PDU_Mini
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		/* If first bit is 0, the MSG_TYPE is three bits long (see table 3.2.2.2.1.2-2) */
		/* If first bit is 1, the MSG_TYPE is six bits long (see table 3.2.2.2.1.2-2) */
		{
		
		
			int MSG_TYPE_LEN = (EDBitsToInt (Buffer, CurrOfs, 1) ? 6 : 3);
		bts = 0;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->MSG_TYPE___LOCATOR), CurrOfs, bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
			ED_THIS->MSG_TYPE = EDBitsToInt (Buffer, CurrOfs, MSG_TYPE_LEN);
		
			CurrOfs += MSG_TYPE_LEN;
		}
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PDU_Regular (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PDU_Regular* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_dsch_PDU_Regular */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_r_dsch_PDU_Regular
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* Reset exported tag 5 'MACI_INCL' */
		pp_CS0004E_Details->userTagPresent[0] = 0;
		pp_CS0004E_Details->userTag[0] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[0], "r_dsch_PDU_Regular", "MACI_INCL");
		pp_CS0004E_Details->userTagBusy[0] = 1;
#endif
		/* Reset exported tag 32 'ENCRYPTION' */
		pp_CS0004E_Details->userTagPresent[1] = 0;
		pp_CS0004E_Details->userTag[1] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[1], "r_dsch_PDU_Regular", "ENCRYPTION");
		pp_CS0004E_Details->userTagBusy[1] = 1;
#endif
		/* Mark the beginning of the PDU, to allow correct padding */
		pp_CS0004E_Details->n_PDU_START_OFFSET = CurrOfs;
		
		CurrOfs += ENCODE_c_r_dsch_PDU_Regular_Message_Type (Buffer, CurrOfs, (&(Source->Message_Type)), pp_CS0004E_Details);
		CurrOfs += ENCODE_c_r_dsch_PDU_Regular_ARQ (Buffer, CurrOfs, (&(Source->ARQ)), pp_CS0004E_Details);
		CurrOfs += ENCODE_c_r_dsch_PDU_Regular_Encryption (Buffer, CurrOfs, (&(Source->Encryption)), pp_CS0004E_Details);
		CurrOfs += ENCODE_c_r_dsch_PDU_Regular_Integrity_Fields (Buffer, CurrOfs, (&(Source->Integrity_Fields)), pp_CS0004E_Details);
		/* Available from P_REV_IN_USE >= 9 */
		CurrOfs += ENCODE_c_r_dsch_PDU_Regular_Extended_Encryption (Buffer, CurrOfs, (&(Source->Extended_Encryption)), pp_CS0004E_Details);
		
		PUSH_BIN ((&(Source->SDU))->value, (&(Source->SDU))->usedBits);
		
		/* PADDING */
		CurrOfs = CS0004E_PDU_Padding_Encode (Buffer, CurrOfs, pp_CS0004E_Details);
		
		/* Rev.9 addition */
		if ((pp_CS0004E_Details->userTag[0])) {
			/* Field 'MACI' is required */
			ED_ASSERT (GETPRESENT_c_r_dsch_PDU_Regular_MACI(Source));
			PUSH_INT (Source->MACI, 32);
		}
		else {
			/* Field 'MACI' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_dsch_PDU_Regular_MACI(Source));
		}
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[0], "r_dsch_PDU_Regular", "MACI_INCL");
		pp_CS0004E_Details->userTagBusy[0] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[1], "r_dsch_PDU_Regular", "ENCRYPTION");
		pp_CS0004E_Details->userTagBusy[1] = 0;
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PDU_Regular (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PDU_Regular* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_dsch_PDU_Regular */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_r_dsch_PDU_Regular
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		/* Reset exported tag 5 'MACI_INCL' */
		pp_CS0004E_Details->userTagPresent[0] = 0;
		pp_CS0004E_Details->userTag[0] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[0], "r_dsch_PDU_Regular", "MACI_INCL");
		pp_CS0004E_Details->userTagBusy[0] = 1;
#endif
		/* Reset exported tag 32 'ENCRYPTION' */
		pp_CS0004E_Details->userTagPresent[1] = 0;
		pp_CS0004E_Details->userTag[1] = 0;
		
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_ZERO (pp_CS0004E_Details->userTagBusy[1], "r_dsch_PDU_Regular", "ENCRYPTION");
		pp_CS0004E_Details->userTagBusy[1] = 1;
#endif
		/* Mark the beginning of the PDU, to allow correct padding */
		pp_CS0004E_Details->n_PDU_START_OFFSET = CurrOfs;
		
		bts = DECODE_c_r_dsch_PDU_Regular_Message_Type (Buffer, CurrOfs, (&(Destin->Message_Type)), LastOfs-CurrOfs , pp_CS0004E_Details);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = DECODE_c_r_dsch_PDU_Regular_ARQ (Buffer, CurrOfs, (&(Destin->ARQ)), LastOfs-CurrOfs , pp_CS0004E_Details);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = DECODE_c_r_dsch_PDU_Regular_Encryption (Buffer, CurrOfs, (&(Destin->Encryption)), LastOfs-CurrOfs , pp_CS0004E_Details);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = DECODE_c_r_dsch_PDU_Regular_Integrity_Fields (Buffer, CurrOfs, (&(Destin->Integrity_Fields)), LastOfs-CurrOfs , pp_CS0004E_Details);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* Available from P_REV_IN_USE >= 9 */
		bts = DECODE_c_r_dsch_PDU_Regular_Extended_Encryption (Buffer, CurrOfs, (&(Destin->Extended_Encryption)), LastOfs-CurrOfs , pp_CS0004E_Details);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* In case MACI is included, reduce the size of 32 bits */
		{
			int OldLastOfs = LastOfs;
			if (pp_CS0004E_Details->userTag[0]/*MACI_INCL*/) {
				ED_ASSERT (LastOfs >= 32);
				LastOfs -= 32;
			}
		bts = (int)(LastOfs-CurrOfs);
		ED_LOCATOR_SET (&(Destin->SDU___LOCATOR), CurrOfs, bts);
		EDAllocBinary (&(((&(Destin->SDU)))->value), (unsigned)bts, &(((&(Destin->SDU)))->usedBits));
		EDCopyBits (((&(Destin->SDU))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
			LastOfs = OldLastOfs;
		}
		/* PADDING */
		
		CurrOfs = CS0004E_PDU_Padding_Decode (CurrOfs, LastOfs, pp_CS0004E_Details);
		/* Rev.9 addition */
		if ((pp_CS0004E_Details->userTag[0])) {
			SETPRESENT_c_r_dsch_PDU_Regular_MACI(Destin, ED_TRUE);
			bts = 32;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->MACI___LOCATOR), CurrOfs, bts);
				Destin->MACI = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_dsch_PDU_Regular_MACI(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[0], "r_dsch_PDU_Regular", "MACI_INCL");
		pp_CS0004E_Details->userTagBusy[0] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[1], "r_dsch_PDU_Regular", "ENCRYPTION");
		pp_CS0004E_Details->userTagBusy[1] = 0;
#endif
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[0], "r_dsch_PDU_Regular", "MACI_INCL");
		pp_CS0004E_Details->userTagBusy[0] = 0;
#endif
#ifdef NOCSN_DEBUG
		NOCSN_CHECK_SET (pp_CS0004E_Details->userTagBusy[1], "r_dsch_PDU_Regular", "ENCRYPTION");
		pp_CS0004E_Details->userTagBusy[1] = 0;
#endif
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PDU_Regular_Message_Type (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PDU_Regular_Message_Type* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_dsch_Message_Type_Regular */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_r_dsch_PDU_Regular
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->MSG_TYPE, 8);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PDU_Regular_Message_Type (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PDU_Regular_Message_Type* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_dsch_Message_Type_Regular */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_r_dsch_PDU_Regular
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 8;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->MSG_TYPE___LOCATOR), CurrOfs, bts);
			Destin->MSG_TYPE = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PDU_Regular_ARQ (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PDU_Regular_ARQ* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_dsch_ARQ_Regular */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_r_dsch_PDU_Regular
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->ACK_SEQ, 3);
		PUSH_INT (Source->MSG_SEQ, 3);
		PUSH_INT (Source->ACK_REQ, 1);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PDU_Regular_ARQ (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PDU_Regular_ARQ* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_dsch_ARQ_Regular */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_r_dsch_PDU_Regular
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 3;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ACK_SEQ___LOCATOR), CurrOfs, bts);
			Destin->ACK_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 3;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->MSG_SEQ___LOCATOR), CurrOfs, bts);
			Destin->MSG_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ACK_REQ___LOCATOR), CurrOfs, bts);
			Destin->ACK_REQ = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PDU_Regular_Encryption (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PDU_Regular_Encryption* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_dsch_Encryption */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_r_dsch_PDU_Regular
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->ENCRYPTION, 2);
		/* Set the exported tag */
		pp_CS0004E_Details->userTagPresent[1] = 1;
		pp_CS0004E_Details->userTag[1] = (int)Source->ENCRYPTION;
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PDU_Regular_Encryption (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PDU_Regular_Encryption* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_dsch_Encryption */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_r_dsch_PDU_Regular
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 2;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ENCRYPTION___LOCATOR), CurrOfs, bts);
			Destin->ENCRYPTION = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			/* Set the exported tag */
			pp_CS0004E_Details->userTagPresent[1] = 1;
			pp_CS0004E_Details->userTag[1] = (int)Destin->ENCRYPTION;
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PDU_Regular_Integrity_Fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PDU_Regular_Integrity_Fields* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_dsch_Common_Message_Integrity_Fields */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_r_dsch_PDU_Regular
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		if ((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)) {
			/* Field 'MACI_INCL' is required */
			ED_ASSERT (GETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_MACI_INCL(Source));
			PUSH_INT (Source->MACI_INCL, 1);
			/* Set the exported tag */
			pp_CS0004E_Details->userTagPresent[0] = 1;
			pp_CS0004E_Details->userTag[0] = (int)Source->MACI_INCL;
		}
		else {
			/* Field 'MACI_INCL' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_MACI_INCL(Source));
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Source->MACI_INCL_Present ? Source->MACI_INCL : 0))) {
			/* Field 'SDU_KEY_ID' is required */
			ED_ASSERT (GETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_KEY_ID(Source));
			PUSH_INT (Source->SDU_KEY_ID, 2);
		}
		else {
			/* Field 'SDU_KEY_ID' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_KEY_ID(Source));
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Source->MACI_INCL_Present ? Source->MACI_INCL : 0))) {
			/* Field 'SDU_INTEGRITY_ALGO' is required */
			ED_ASSERT (GETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_INTEGRITY_ALGO(Source));
			PUSH_INT (Source->SDU_INTEGRITY_ALGO, 3);
		}
		else {
			/* Field 'SDU_INTEGRITY_ALGO' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_INTEGRITY_ALGO(Source));
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Source->MACI_INCL_Present ? Source->MACI_INCL : 0))) {
			/* Field 'SDU_SSEQ_OR_SSEQH' is required */
			ED_ASSERT (GETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_OR_SSEQH(Source));
			PUSH_INT (Source->SDU_SSEQ_OR_SSEQH, 1);
		}
		else {
			/* Field 'SDU_SSEQ_OR_SSEQH' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_OR_SSEQH(Source));
		}
		if ((((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Source->MACI_INCL_Present ? Source->MACI_INCL : 0))&&!((Source->SDU_SSEQ_OR_SSEQH_Present ? Source->SDU_SSEQ_OR_SSEQH : 0)))) {
			/* Field 'SDU_SSEQ' is required */
			ED_ASSERT (GETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ(Source));
			PUSH_INT (Source->SDU_SSEQ, 8);
		}
		else {
			/* Field 'SDU_SSEQ' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ(Source));
		}
		if ((((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Source->MACI_INCL_Present ? Source->MACI_INCL : 0))&&(Source->SDU_SSEQ_OR_SSEQH_Present ? Source->SDU_SSEQ_OR_SSEQH : 0))) {
			/* Field 'SDU_SSEQ_H' is required */
			ED_ASSERT (GETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_H(Source));
			PUSH_INT (Source->SDU_SSEQ_H, 24);
		}
		else {
			/* Field 'SDU_SSEQ_H' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_H(Source));
		}
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PDU_Regular_Integrity_Fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PDU_Regular_Integrity_Fields* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_dsch_Common_Message_Integrity_Fields */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_r_dsch_PDU_Regular
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		if ((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)) {
			SETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_MACI_INCL(Destin, ED_TRUE);
			bts = 1;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->MACI_INCL___LOCATOR), CurrOfs, bts);
				Destin->MACI_INCL = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
				/* Set the exported tag */
				pp_CS0004E_Details->userTagPresent[0] = 1;
				pp_CS0004E_Details->userTag[0] = (int)Destin->MACI_INCL;
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_MACI_INCL(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Destin->MACI_INCL_Present ? Destin->MACI_INCL : 0))) {
			SETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_KEY_ID(Destin, ED_TRUE);
			bts = 2;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_KEY_ID___LOCATOR), CurrOfs, bts);
				Destin->SDU_KEY_ID = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_KEY_ID(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Destin->MACI_INCL_Present ? Destin->MACI_INCL : 0))) {
			SETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_INTEGRITY_ALGO(Destin, ED_TRUE);
			bts = 3;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_INTEGRITY_ALGO___LOCATOR), CurrOfs, bts);
				Destin->SDU_INTEGRITY_ALGO = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_INTEGRITY_ALGO(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Destin->MACI_INCL_Present ? Destin->MACI_INCL : 0))) {
			SETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_OR_SSEQH(Destin, ED_TRUE);
			bts = 1;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_SSEQ_OR_SSEQH___LOCATOR), CurrOfs, bts);
				Destin->SDU_SSEQ_OR_SSEQH = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_OR_SSEQH(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Destin->MACI_INCL_Present ? Destin->MACI_INCL : 0))&&!((Destin->SDU_SSEQ_OR_SSEQH_Present ? Destin->SDU_SSEQ_OR_SSEQH : 0)))) {
			SETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ(Destin, ED_TRUE);
			bts = 8;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_SSEQ___LOCATOR), CurrOfs, bts);
				Destin->SDU_SSEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((((pp_CS0004E_Details->n_P_REV_IN_USEs>=9)&&(Destin->MACI_INCL_Present ? Destin->MACI_INCL : 0))&&(Destin->SDU_SSEQ_OR_SSEQH_Present ? Destin->SDU_SSEQ_OR_SSEQH : 0))) {
			SETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_H(Destin, ED_TRUE);
			bts = 24;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_SSEQ_H___LOCATOR), CurrOfs, bts);
				Destin->SDU_SSEQ_H = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_H(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PDU_Regular_Extended_Encryption (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PDU_Regular_Extended_Encryption* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_dsch_Extended_Encryption */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_r_dsch_PDU_Regular
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* See 2.2.1.2.1.2 (available from Rev.7) */
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=7)&&((pp_CS0004E_Details->userTag[1])==3))) {
			/* Field 'SDU_ENCRYPT_MODE' is required */
			ED_ASSERT (GETPRESENT_c_r_dsch_PDU_Regular_Extended_Encryption_SDU_ENCRYPT_MODE(Source));
			PUSH_INT (Source->SDU_ENCRYPT_MODE, 3);
		}
		else {
			/* Field 'SDU_ENCRYPT_MODE' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_dsch_PDU_Regular_Extended_Encryption_SDU_ENCRYPT_MODE(Source));
		}
		if ((Source->SDU_ENCRYPT_MODE_Present&&(((Source->SDU_ENCRYPT_MODE_Present ? Source->SDU_ENCRYPT_MODE : 0)==1)||((Source->SDU_ENCRYPT_MODE_Present ? Source->SDU_ENCRYPT_MODE : 0)==2)))) {
			/* Field 'ENC_SEQ' is required */
			ED_ASSERT (GETPRESENT_c_r_dsch_PDU_Regular_Extended_Encryption_ENC_SEQ(Source));
			PUSH_INT (Source->ENC_SEQ, 8);
		}
		else {
			/* Field 'ENC_SEQ' must be absent */
			ED_ASSERT (!GETPRESENT_c_r_dsch_PDU_Regular_Extended_Encryption_ENC_SEQ(Source));
		}
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PDU_Regular_Extended_Encryption (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PDU_Regular_Extended_Encryption* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_dsch_Extended_Encryption */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_r_dsch_PDU_Regular
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		/* See 2.2.1.2.1.2 (available from Rev.7) */
		if (((pp_CS0004E_Details->n_P_REV_IN_USEs>=7)&&((pp_CS0004E_Details->userTag[1])==3))) {
			SETPRESENT_c_r_dsch_PDU_Regular_Extended_Encryption_SDU_ENCRYPT_MODE(Destin, ED_TRUE);
			bts = 3;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->SDU_ENCRYPT_MODE___LOCATOR), CurrOfs, bts);
				Destin->SDU_ENCRYPT_MODE = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_dsch_PDU_Regular_Extended_Encryption_SDU_ENCRYPT_MODE(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
		if ((Destin->SDU_ENCRYPT_MODE_Present&&(((Destin->SDU_ENCRYPT_MODE_Present ? Destin->SDU_ENCRYPT_MODE : 0)==1)||((Destin->SDU_ENCRYPT_MODE_Present ? Destin->SDU_ENCRYPT_MODE : 0)==2)))) {
			SETPRESENT_c_r_dsch_PDU_Regular_Extended_Encryption_ENC_SEQ(Destin, ED_TRUE);
			bts = 8;
			if (LastOfs - (int)CurrOfs < bts) {
				bts = ED_MESSAGE_TOO_SHORT;
			} 
			else {
				ED_LOCATOR_SET (&(Destin->ENC_SEQ___LOCATOR), CurrOfs, bts);
				Destin->ENC_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
			}
			if (bts < 0) {
				/* If decoding failed, set the failed field to "not present" */
				SETPRESENT_c_r_dsch_PDU_Regular_Extended_Encryption_ENC_SEQ(Destin, ED_FALSE);
				goto exitOnFail;
			}
			CurrOfs += bts;
		}
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PDU_Mini (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PDU_Mini* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_dsch_PDU_Mini */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_r_dsch_PDU_Mini
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* Mark the beginning of the PDU, to allow correct padding */
		pp_CS0004E_Details->n_PDU_START_OFFSET = CurrOfs;
		
		CurrOfs += ENCODE_c_r_dsch_PDU_Mini_ARQ (Buffer, CurrOfs, (&(Source->ARQ)), pp_CS0004E_Details);
		CurrOfs += ENCODE_c_r_dsch_PDU_Mini_Message_Type (Buffer, CurrOfs, (&(Source->Message_Type)), pp_CS0004E_Details);
		PUSH_BIN ((&(Source->SDU))->value, (&(Source->SDU))->usedBits);
		/* PADDING */
		CurrOfs = CS0004E_PDU_Padding_Encode (Buffer, CurrOfs, pp_CS0004E_Details);
		
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PDU_Mini (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PDU_Mini* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_dsch_PDU_Mini */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_r_dsch_PDU_Mini
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		/* Mark the beginning of the PDU, to allow correct padding */
		pp_CS0004E_Details->n_PDU_START_OFFSET = CurrOfs;
		
		bts = DECODE_c_r_dsch_PDU_Mini_ARQ (Buffer, CurrOfs, (&(Destin->ARQ)), LastOfs-CurrOfs , pp_CS0004E_Details);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = DECODE_c_r_dsch_PDU_Mini_Message_Type (Buffer, CurrOfs, (&(Destin->Message_Type)), LastOfs-CurrOfs , pp_CS0004E_Details);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = (int)(LastOfs-CurrOfs);
		ED_LOCATOR_SET (&(Destin->SDU___LOCATOR), CurrOfs, bts);
		EDAllocBinary (&(((&(Destin->SDU)))->value), (unsigned)bts, &(((&(Destin->SDU)))->usedBits));
		EDCopyBits (((&(Destin->SDU))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		/* PADDING */
		
		CurrOfs = CS0004E_PDU_Padding_Decode (CurrOfs, LastOfs, pp_CS0004E_Details);
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PDU_Mini_ARQ (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PDU_Mini_ARQ* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_dsch_ARQ_Mini */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_r_dsch_PDU_Mini
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->ACK_SEQ, 2);
		PUSH_INT (Source->MSG_SEQ, 2);
		PUSH_INT (Source->ACK_REQ, 1);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PDU_Mini_ARQ (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PDU_Mini_ARQ* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_dsch_ARQ_Mini */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_r_dsch_PDU_Mini
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 2;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ACK_SEQ___LOCATOR), CurrOfs, bts);
			Destin->ACK_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 2;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->MSG_SEQ___LOCATOR), CurrOfs, bts);
			Destin->MSG_SEQ = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 1;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->ACK_REQ___LOCATOR), CurrOfs, bts);
			Destin->ACK_REQ = (ED_BOOLEAN)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PDU_Mini_Message_Type (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PDU_Mini_Message_Type* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_dsch_Message_Type_Mini */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_r_dsch_PDU_Mini
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		/* If first bit is 0, the MSG_TYPE is three bits long (see table 2.2.1.2.1.2-2) */
		/* If first bit is 1, the MSG_TYPE is six bits long (see table 2.2.1.2.1.2-3) */
		{
		
			int MSG_TYPE_LEN = (ED_THIS->MSG_TYPE <= 7 ? 3 : 6);
		
		
			EDIntToBits (Buffer, CurrOfs, ED_THIS->MSG_TYPE, MSG_TYPE_LEN);
			CurrOfs += MSG_TYPE_LEN;
		}
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PDU_Mini_Message_Type (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PDU_Mini_Message_Type* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME r_dsch_Message_Type_Mini */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_r_dsch_PDU_Mini
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		/* If first bit is 0, the MSG_TYPE is three bits long (see table 2.2.1.2.1.2-2) */
		/* If first bit is 1, the MSG_TYPE is six bits long (see table 2.2.1.2.1.2-3) */
		{
		
		
			int MSG_TYPE_LEN = (EDBitsToInt (Buffer, CurrOfs, 1) ? 6 : 3);
		bts = 0;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->MSG_TYPE___LOCATOR), CurrOfs, bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
			ED_THIS->MSG_TYPE = EDBitsToInt (Buffer, CurrOfs, MSG_TYPE_LEN);
		
			CurrOfs += MSG_TYPE_LEN;
		}
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UPM_Mobile_Station_Addressed (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UPM_Mobile_Station_Addressed* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_UPM_Mobile_Station_Addressed */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_f_csch_UPM
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->SERVICE_OPTION, 16);
		PUSH_BIN ((&(Source->ADD_MS_RECORD))->value, (&(Source->ADD_MS_RECORD))->usedBits);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UPM_Mobile_Station_Addressed (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UPM_Mobile_Station_Addressed* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_UPM_Mobile_Station_Addressed */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_f_csch_UPM
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 16;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->SERVICE_OPTION___LOCATOR), CurrOfs, bts);
			Destin->SERVICE_OPTION = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = (int)(LastOfs-CurrOfs);
		ED_LOCATOR_SET (&(Destin->ADD_MS_RECORD___LOCATOR), CurrOfs, bts);
		EDAllocBinary (&(((&(Destin->ADD_MS_RECORD)))->value), (unsigned)bts, &(((&(Destin->ADD_MS_RECORD)))->usedBits));
		EDCopyBits (((&(Destin->ADD_MS_RECORD))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UPM_Enhanced_Broadcast_with_time_offset (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UPM_Enhanced_Broadcast_with_time_offset* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_UPM_Enhanced_Broadcast_with_time_offset */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_f_csch_UPM
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->BCN, 3);
		PUSH_INT (Source->TIME_OFFSET, 10);
		PUSH_INT (Source->REPEAT_TIME_OFFSET, 5);
		PUSH_BIN ((&(Source->ADD_BCAST_RECORD))->value, (&(Source->ADD_BCAST_RECORD))->usedBits);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UPM_Enhanced_Broadcast_with_time_offset (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UPM_Enhanced_Broadcast_with_time_offset* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_UPM_Enhanced_Broadcast_with_time_offset */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_f_csch_UPM
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 3;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->BCN___LOCATOR), CurrOfs, bts);
			Destin->BCN = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 10;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->TIME_OFFSET___LOCATOR), CurrOfs, bts);
			Destin->TIME_OFFSET = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 5;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->REPEAT_TIME_OFFSET___LOCATOR), CurrOfs, bts);
			Destin->REPEAT_TIME_OFFSET = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = (int)(LastOfs-CurrOfs);
		ED_LOCATOR_SET (&(Destin->ADD_BCAST_RECORD___LOCATOR), CurrOfs, bts);
		EDAllocBinary (&(((&(Destin->ADD_BCAST_RECORD)))->value), (unsigned)bts, &(((&(Destin->ADD_BCAST_RECORD)))->usedBits));
		EDCopyBits (((&(Destin->ADD_BCAST_RECORD))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UPM_Enhanced_Broadcast_without_time_offset (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UPM_Enhanced_Broadcast_without_time_offset* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(Source);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_UPM_Enhanced_Broadcast_without_time_offset */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_ENCODE_f_csch_UPM
		assert (0); /* Encode excluded */
		return 0;
#else
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Source
		PUSH_INT (Source->BCN, 3);
		PUSH_INT (Source->TIME_OFFSET, 10);
		PUSH_BIN ((&(Source->ADD_BCAST_RECORD))->value, (&(Source->ADD_BCAST_RECORD))->usedBits);
		return (ED_EXLONG)(CurrOfs-BitOffset);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UPM_Enhanced_Broadcast_without_time_offset (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UPM_Enhanced_Broadcast_without_time_offset* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER(CurrOfs);
	ED_WARNING_REMOVER(Length);
	ED_WARNING_REMOVER(Destin);
	ED_WARNING_REMOVER(Buffer);
	ED_WARNING_REMOVER(BitOffset);
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	{

		/* DEFINITION NAME f_csch_UPM_Enhanced_Broadcast_without_time_offset */
#ifndef ED_ASSERT
#define ED_ASSERT(a)
#endif
		/* CSN.1 macro compatibility */
#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER Buffer
#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS CurrOfs
#ifdef ED_EXCLUDE_DECODE_f_csch_UPM
		assert (0); /* Encode excluded */
		return 0;
#else
		int bts=0;
		int LastOfs = (int)BitOffset + (int)Length;
#ifdef ED_THIS
#undef ED_THIS
#endif
#define ED_THIS Destin
		bts = 3;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->BCN___LOCATOR), CurrOfs, bts);
			Destin->BCN = (ED_OCTET)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = 10;
		if (LastOfs - (int)CurrOfs < bts) {
			bts = ED_MESSAGE_TOO_SHORT;
		} 
		else {
			ED_LOCATOR_SET (&(Destin->TIME_OFFSET___LOCATOR), CurrOfs, bts);
			Destin->TIME_OFFSET = (ED_LONG)EDBitsToInt (Buffer, CURPOS, (ED_EXLONG)bts);
		}
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
		bts = (int)(LastOfs-CurrOfs);
		ED_LOCATOR_SET (&(Destin->ADD_BCAST_RECORD___LOCATOR), CurrOfs, bts);
		EDAllocBinary (&(((&(Destin->ADD_BCAST_RECORD)))->value), (unsigned)bts, &(((&(Destin->ADD_BCAST_RECORD)))->usedBits));
		EDCopyBits (((&(Destin->ADD_BCAST_RECORD))->value), 0, Buffer, CURPOS, (ED_EXLONG)bts);
		if (bts < 0) {
			/* Decoding failed - Go to the exit point */
			goto exitOnFail;
		}
		CurrOfs += bts;
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		return (ED_EXLONG)(CurrOfs-BitOffset);
		
		/* Goes here only in case of failed decoding */
		exitOnFail:
#ifdef ED_SET_DECODE_BITS
		if (CurrOfs > (ED_EXLONG)(ED_GET_HIGHEST_DECODE_BIT)) ED_SET_HIGHEST_DECODE_BIT (CurrOfs);
		if ((ED_EXLONG)((ED_GET_HIGHEST_DECODE_BIT)-BitOffset) < Length) ED_SET_DECODE_BITS ((ED_GET_HIGHEST_DECODE_BIT)-BitOffset);
		else ED_SET_DECODE_BITS (Length);
#endif
		ED_ASSERT (bts<0);
		return (ED_EXLONG)(bts);
#undef ED_THIS
#endif
	
	}
}
#undef THIS
#define THIS Source
/* IEEE 802.16 GENERIC TLV ENCODER */
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_GenericTLV_cs0004 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GenericTLV_cs0004* ED_CONST Source, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_EXLONG BinaryDataLength;
	

	
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);
					
	/* Encode the tag */
	EDIntToBits (Buffer, CurrOfs, Source->TLV_Tag, 8);
	CurrOfs += 8;
	
	/* Calculate the binary length */
	BinaryDataLength = Source->TLV_Data.usedBits;
	
	/* Encode the length rounded up to the nearest octet */
	CurrOfs += EDEncodeDefiniteFormLength (Buffer, CurrOfs, (((unsigned ED_EXLONG)BinaryDataLength)+7)>>3);
	
	/* Encode the bits of the binary data */
	EDCopyBits (Buffer, CurrOfs, Source->TLV_Data.value, 0, BinaryDataLength);
	CurrOfs += BinaryDataLength;
	
	/* Pad the remaining part */
	EDIntToBits (Buffer, CurrOfs, 0, BITS_TO_OCTET_PAD (CurrOfs));
	CurrOfs += BITS_TO_OCTET_PAD (CurrOfs);
	
	return (CurrOfs - BitOffset);
}

#undef THIS
#define THIS Destin
/* IEEE 802.16 GENERIC TLV DECODER */
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_GenericTLV_cs0004 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GenericTLV_cs0004* ED_CONST Destin, ED_EXLONG Length, CS0004E_Details* pp_CS0004E_Details))
{
	ED_EXLONG CurrOfs = BitOffset;
	unsigned ED_EXLONG DataLength;
	unsigned ED_EXLONG EffectiveDataLength;
	ED_EXLONG RetLen;

	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER(pp_CS0004E_Details);

	/* Is there room for tag and length? */
	if (Length < 16) return ED_MESSAGE_TOO_SHORT;

	/* Decode the tag */
	Destin->TLV_Tag = (ED_LONG)EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	
	/* Decode the length */
	RetLen = EDDecodeDefiniteFormLength (Buffer, CurrOfs, &DataLength);
	if (RetLen < 0) return RetLen;
	DataLength = DataLength * 8;
	EffectiveDataLength = DataLength;
	CurrOfs += RetLen;
	if ((BitOffset-CurrOfs) > Length) return ED_MESSAGE_TOO_SHORT;
	if (BitOffset - (CurrOfs + (ED_EXLONG)DataLength) > Length) return ED_MESSAGE_TOO_SHORT;
	
	/* If the expected length is too much for our binary buffer, decode
		 what we can and discard the rest */
	if (DataLength > 64) {
		DataLength = 64;
	}
	
	/* Allocate 'DataLength' bits */
	ALLOC_c_GenericTLV_cs0004_TLV_Data (&(Destin->TLV_Data), DataLength);

	
	/* Save the bits in the binary data */
	EDCopyBits (Destin->TLV_Data.value, 0, Buffer, CurrOfs, DataLength);
	CurrOfs += (ED_EXLONG)EffectiveDataLength;

	return (CurrOfs-BitOffset);
}

#undef THIS
