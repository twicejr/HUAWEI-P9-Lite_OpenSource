/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.83
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#include "L3Downlink.h"
#include "ed_c_known_ie.h"
#include "ed_tlv.h"
#include "UserDefinedDataTypes.h"
#include "CSN1DataTypes.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_L3DOWNLINK_C
/*lint -e961*/
/*lint -e958*/
/*lint -e527*/
/*lint -e701*/
/*lint -e704*/
/*lint -e734*/
/*lint -e774*/

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE ASSIGNMENT_COMMAND
-----------------------------------------------------------------*/
long DECODE_c_ASSIGNMENT_COMMAND (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_ASSIGNMENT_COMMAND* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_ASSIGNMENT_COMMAND (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE ASSIGNMENT_COMMAND
-----------------------------------------------------------------*/
long DECODE_BODY_c_ASSIGNMENT_COMMAND (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_ASSIGNMENT_COMMAND* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Table containing the expected sequence of IEIs */
	const TEDTLVSkipItem TLVSkipItems [] = {
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{5, 255, ED_SKIPLIST_OPTIONAL},
		{98, 255, ED_SKIPLIST_OPTIONAL},
		{16, 255, ED_SKIPLIST_OPTIONAL},
		{99, 255, ED_SKIPLIST_OPTIONAL},
		{17, 255, ED_SKIPLIST_OPTIONAL},
		{19, 255, ED_SKIPLIST_OPTIONAL},
		{20, 255, ED_SKIPLIST_OPTIONAL},
		{21, 255, ED_SKIPLIST_OPTIONAL},
		{22, 255, ED_SKIPLIST_OPTIONAL},
		{23, 255, ED_SKIPLIST_OPTIONAL},
		{24, 255, ED_SKIPLIST_OPTIONAL},
		{100, 255, ED_SKIPLIST_OPTIONAL},
		{102, 255, ED_SKIPLIST_OPTIONAL},
		{114, 255, ED_SKIPLIST_OPTIONAL},
		{124, 255, ED_SKIPLIST_OPTIONAL},
		{25, 255, ED_SKIPLIST_OPTIONAL},
		{28, 255, ED_SKIPLIST_OPTIONAL},
		{29, 255, ED_SKIPLIST_OPTIONAL},
		{30, 255, ED_SKIPLIST_OPTIONAL},
		{33, 255, ED_SKIPLIST_OPTIONAL},
		{144, 240, ED_SKIPLIST_OPTIONAL},
		{1, 255, ED_SKIPLIST_OPTIONAL},
		{3, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/*Known IEI LIST*/
    const TEDKnownIE Tmp_KnownL3IEs [] = {
		{0x01, 255, ED_SKIPLIST_OPTIONAL},
        {0x03, 255, ED_SKIPLIST_OPTIONAL},
        {0x05, 255, -8},
        {0x10, 255, -8},
        {0x11, 255, 2*8},
        {0x13, 255, 2*8},
        {0x14, 255, 2*8},
        {0x15, 255, 2*8},
        {0x16, 255, 2*8},
        {0x17, 255, 2*8},
        {0x18, 255, 2*8},
		{0x19, 255, -8},
        {0x1c, 255, 4*8},
        {0x1d, 255, 4*8},
        {0x1e, 255, 10*8},
        {0x21, 255, -8},
		{0x62, 255, 17*8},
		{0x63, 255, 2*8},
        {0x64, 255, 4*8},
        {0x66, 255, 2*8},
        {0x72, 255, -8},
        {0x7c, 255, 3*8},
        {0x90, 240, 1*8}, 
        {0xff, 0, 0},
		{0xff, 0, 0},
		{0xff, 0, 0},
		{0xff, 0, 0},
		{0xff, 0, 0},
        {0xff, 0, 0},
		{0xff, 0, 0},
		{0xff, 0, 0},
		{0xff, 0, 0},
		{0xff, 0, 0},
		{0xff, 0, 0},
		{0xff, 0, 0},
		{0xff, 0, 0},
		{0xff, 0, 0},
		{0xff, 0, 0},
		{0xff, 0, 0},
        {0x00, 0, 0}
    };
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE DescOfTheFirstChannelAfterTime
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part */
	RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, &(Destin->DescOfTheFirstChannelAfterTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1> Error decoding subfield DescOfTheFirstChannelAfterTime\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1, (Destin->DescOfTheFirstChannelAfterTime));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:2> Message too short decoding subfield DescOfTheFirstChannelAfterTime\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1, (Destin->DescOfTheFirstChannelAfterTime));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE PowerCommand
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part */
	RetLen = DECODE_c_PowerCommand (Buffer, CurrOfs, &(Destin->PowerCommand), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:3> Error decoding subfield PowerCommand\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 3, (Destin->PowerCommand));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:4> Message too short decoding subfield PowerCommand\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 3, (Destin->PowerCommand));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE FrequencyListAfterTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x05 */
	ED_EXPECT_OPTIONAL_IE (0x05,  8, 5, 2, Tmp_KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x05) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_FrequencyListAfterTime (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 16) || (Len > 1040)) {
			ED_SIGNAL_ERROR ("<ERRID:6> Size error decoding IE FrequencyListAfterTime\n");
			ED_HANDLE_IE_SIZE_ERROR (0x05, 6, (Destin->FrequencyListAfterTime), (Destin->FrequencyListAfterTime_Present))
		} 
#endif
		/* Read value part */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, &(Destin->FrequencyListAfterTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:7> Error decoding subfield FrequencyListAfterTime\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x05, 7, (Destin->FrequencyListAfterTime), (Destin->FrequencyListAfterTime_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:8> Message too short decoding subfield FrequencyListAfterTime\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x05, 7, (Destin->FrequencyListAfterTime), (Destin->FrequencyListAfterTime_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE CellChannelDescription
	------------------------------------------------------*/
	/* Detect IEI tag 0x62 */
	ED_EXPECT_OPTIONAL_IE (0x62,  8, 9, 3, Tmp_KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x62) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_CellChannelDescription (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 128;
		/* Read value part */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, &(Destin->CellChannelDescription), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:10> Error decoding subfield CellChannelDescription\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x62, 10, (Destin->CellChannelDescription), (Destin->CellChannelDescription_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:11> Message too short decoding subfield CellChannelDescription\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x62, 10, (Destin->CellChannelDescription), (Destin->CellChannelDescription_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE DescriptionOfTheMultislotCfg
	------------------------------------------------------*/
	/* Detect IEI tag 0x10 */
    ED_EXPECT_OPTIONAL_IE (0x10,  8, 12, 4, Tmp_KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x10) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DescriptionOfTheMultislotCfg (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 80)) {
			ED_SIGNAL_ERROR ("<ERRID:13> Size error decoding IE DescriptionOfTheMultislotCfg\n");
			ED_HANDLE_IE_SIZE_ERROR (0x10, 13, (Destin->DescriptionOfTheMultislotCfg), (Destin->DescriptionOfTheMultislotCfg_Present))
		} 
#endif
		/* Read value part */
		ALLOC_c_ASSIGNMENT_COMMAND_DescriptionOfTheMultislotCfg (&(Destin->DescriptionOfTheMultislotCfg), Len);
		EDCopyBits (Destin->DescriptionOfTheMultislotCfg.value, 0, Buffer, CurrOfs, Len);
		Destin->DescriptionOfTheMultislotCfg.usedBits = Len;RetLen = Len;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:14> Error decoding subfield DescriptionOfTheMultislotCfg\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x10, 14, (Destin->DescriptionOfTheMultislotCfg), (Destin->DescriptionOfTheMultislotCfg_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:15> Message too short decoding subfield DescriptionOfTheMultislotCfg\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x10, 14, (Destin->DescriptionOfTheMultislotCfg), (Destin->DescriptionOfTheMultislotCfg_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfTheFirstChannelChannelSet1
	------------------------------------------------------*/
	/* Detect IEI tag 0x63 */
    ED_EXPECT_OPTIONAL_IE (0x63,  8, 16, 5, Tmp_KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x63) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_ModeOfTheFirstChannelChannelSet1 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part */
		Destin->ModeOfTheFirstChannelChannelSet1 = EDBitsToInt (Buffer, CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:17> Error decoding subfield ModeOfTheFirstChannelChannelSet1\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x63, 17, (Destin->ModeOfTheFirstChannelChannelSet1), (Destin->ModeOfTheFirstChannelChannelSet1_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:18> Message too short decoding subfield ModeOfTheFirstChannelChannelSet1\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x63, 17, (Destin->ModeOfTheFirstChannelChannelSet1), (Destin->ModeOfTheFirstChannelChannelSet1_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet2
	------------------------------------------------------*/
	/* Detect IEI tag 0x11 */
    ED_EXPECT_OPTIONAL_IE (0x11,  8, 19, 6, Tmp_KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x11) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_ModeOfChannelSet2 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part */
		Destin->ModeOfChannelSet2 = EDBitsToInt (Buffer, CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:20> Error decoding subfield ModeOfChannelSet2\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x11, 20, (Destin->ModeOfChannelSet2), (Destin->ModeOfChannelSet2_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:21> Message too short decoding subfield ModeOfChannelSet2\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x11, 20, (Destin->ModeOfChannelSet2), (Destin->ModeOfChannelSet2_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet3
	------------------------------------------------------*/
	/* Detect IEI tag 0x13 */
    ED_EXPECT_OPTIONAL_IE (0x13,  8, 22, 7, Tmp_KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x13) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_ModeOfChannelSet3 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part */
		Destin->ModeOfChannelSet3 = EDBitsToInt (Buffer, CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:23> Error decoding subfield ModeOfChannelSet3\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x13, 23, (Destin->ModeOfChannelSet3), (Destin->ModeOfChannelSet3_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:24> Message too short decoding subfield ModeOfChannelSet3\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x13, 23, (Destin->ModeOfChannelSet3), (Destin->ModeOfChannelSet3_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet4
	------------------------------------------------------*/
	/* Detect IEI tag 0x14 */
    ED_EXPECT_OPTIONAL_IE (0x14,  8, 25, 8, Tmp_KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x14) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_ModeOfChannelSet4 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part */
		Destin->ModeOfChannelSet4 = EDBitsToInt (Buffer, CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:26> Error decoding subfield ModeOfChannelSet4\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x14, 26, (Destin->ModeOfChannelSet4), (Destin->ModeOfChannelSet4_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:27> Message too short decoding subfield ModeOfChannelSet4\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x14, 26, (Destin->ModeOfChannelSet4), (Destin->ModeOfChannelSet4_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet5
	------------------------------------------------------*/
	/* Detect IEI tag 0x15 */
    ED_EXPECT_OPTIONAL_IE (0x15,  8, 28, 9, Tmp_KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x15) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_ModeOfChannelSet5 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part */
		Destin->ModeOfChannelSet5 = EDBitsToInt (Buffer, CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:29> Error decoding subfield ModeOfChannelSet5\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x15, 29, (Destin->ModeOfChannelSet5), (Destin->ModeOfChannelSet5_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:30> Message too short decoding subfield ModeOfChannelSet5\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x15, 29, (Destin->ModeOfChannelSet5), (Destin->ModeOfChannelSet5_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet6
	------------------------------------------------------*/
	/* Detect IEI tag 0x16 */
    ED_EXPECT_OPTIONAL_IE (0x16,  8, 31, 10, Tmp_KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x16) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_ModeOfChannelSet6 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part */
		Destin->ModeOfChannelSet6 = EDBitsToInt (Buffer, CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:32> Error decoding subfield ModeOfChannelSet6\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x16, 32, (Destin->ModeOfChannelSet6), (Destin->ModeOfChannelSet6_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:33> Message too short decoding subfield ModeOfChannelSet6\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x16, 32, (Destin->ModeOfChannelSet6), (Destin->ModeOfChannelSet6_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet7
	------------------------------------------------------*/
	/* Detect IEI tag 0x17 */
    ED_EXPECT_OPTIONAL_IE (0x17,  8, 34, 11, Tmp_KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x17) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_ModeOfChannelSet7 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part */
		Destin->ModeOfChannelSet7 = EDBitsToInt (Buffer, CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:35> Error decoding subfield ModeOfChannelSet7\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x17, 35, (Destin->ModeOfChannelSet7), (Destin->ModeOfChannelSet7_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:36> Message too short decoding subfield ModeOfChannelSet7\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x17, 35, (Destin->ModeOfChannelSet7), (Destin->ModeOfChannelSet7_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet8
	------------------------------------------------------*/
	/* Detect IEI tag 0x18 */
    ED_EXPECT_OPTIONAL_IE (0x18,  8, 37, 12, Tmp_KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x18) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_ModeOfChannelSet8 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part */
		Destin->ModeOfChannelSet8 = EDBitsToInt (Buffer, CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:38> Error decoding subfield ModeOfChannelSet8\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x18, 38, (Destin->ModeOfChannelSet8), (Destin->ModeOfChannelSet8_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:39> Message too short decoding subfield ModeOfChannelSet8\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x18, 38, (Destin->ModeOfChannelSet8), (Destin->ModeOfChannelSet8_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE DescOfTheSecondChannelAfterTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x64 */
    ED_EXPECT_OPTIONAL_IE (0x64,  8, 40, 13, Tmp_KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x64) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DescOfTheSecondChannelAfterTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 24;
		/* Read value part */
		RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, &(Destin->DescOfTheSecondChannelAfterTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:41> Error decoding subfield DescOfTheSecondChannelAfterTime\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x64, 41, (Destin->DescOfTheSecondChannelAfterTime), (Destin->DescOfTheSecondChannelAfterTime_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:42> Message too short decoding subfield DescOfTheSecondChannelAfterTime\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x64, 41, (Destin->DescOfTheSecondChannelAfterTime), (Destin->DescOfTheSecondChannelAfterTime_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfTheSecondChannel
	------------------------------------------------------*/
	/* Detect IEI tag 0x66 */
    ED_EXPECT_OPTIONAL_IE (0x66,  8, 43, 14, Tmp_KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x66) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_ModeOfTheSecondChannel (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part */
		Destin->ModeOfTheSecondChannel = EDBitsToInt (Buffer, CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:44> Error decoding subfield ModeOfTheSecondChannel\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x66, 44, (Destin->ModeOfTheSecondChannel), (Destin->ModeOfTheSecondChannel_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:45> Message too short decoding subfield ModeOfTheSecondChannel\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x66, 44, (Destin->ModeOfTheSecondChannel), (Destin->ModeOfTheSecondChannel_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE MobileAllocationAfterTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x72 */
    ED_EXPECT_OPTIONAL_IE (0x72,  8, 46, 15, Tmp_KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x72) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_MobileAllocationAfterTime (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 64)) {
			ED_SIGNAL_ERROR ("<ERRID:47> Size error decoding IE MobileAllocationAfterTime\n");
			ED_HANDLE_IE_SIZE_ERROR (0x72, 47, (Destin->MobileAllocationAfterTime), (Destin->MobileAllocationAfterTime_Present))
		} 
#endif
		/* Read value part */
		RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, &(Destin->MobileAllocationAfterTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:48> Error decoding subfield MobileAllocationAfterTime\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x72, 48, (Destin->MobileAllocationAfterTime), (Destin->MobileAllocationAfterTime_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:49> Message too short decoding subfield MobileAllocationAfterTime\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x72, 48, (Destin->MobileAllocationAfterTime), (Destin->MobileAllocationAfterTime_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE StartingTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x7C */
    ED_EXPECT_OPTIONAL_IE (0x7C,  8, 50, 16, Tmp_KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x7C) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_StartingTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 16;
		/* Read value part */
		RetLen = DECODE_c_StartingTime (Buffer, CurrOfs, &(Destin->StartingTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:51> Error decoding subfield StartingTime\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x7C, 51, (Destin->StartingTime), (Destin->StartingTime_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:52> Message too short decoding subfield StartingTime\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x7C, 51, (Destin->StartingTime), (Destin->StartingTime_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE FrequencyListBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x19 */
    ED_EXPECT_OPTIONAL_IE (0x19,  8, 53, 17, Tmp_KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x19) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_FrequencyListBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 16) || (Len > 1040)) {
			ED_SIGNAL_ERROR ("<ERRID:54> Size error decoding IE FrequencyListBeforeTime\n");
			ED_HANDLE_IE_SIZE_ERROR (0x19, 54, (Destin->FrequencyListBeforeTime), (Destin->FrequencyListBeforeTime_Present))
		} 
#endif
		/* Read value part */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, &(Destin->FrequencyListBeforeTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:55> Error decoding subfield FrequencyListBeforeTime\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x19, 55, (Destin->FrequencyListBeforeTime), (Destin->FrequencyListBeforeTime_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:56> Message too short decoding subfield FrequencyListBeforeTime\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x19, 55, (Destin->FrequencyListBeforeTime), (Destin->FrequencyListBeforeTime_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE DescOfTheFirstChannelBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x1C */
    ED_EXPECT_OPTIONAL_IE (0x1C,  8, 57, 18, Tmp_KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x1C) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DescOfTheFirstChannelBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 24;
		/* Read value part */
		RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, &(Destin->DescOfTheFirstChannelBeforeTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:58> Error decoding subfield DescOfTheFirstChannelBeforeTime\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x1C, 58, (Destin->DescOfTheFirstChannelBeforeTime), (Destin->DescOfTheFirstChannelBeforeTime_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:59> Message too short decoding subfield DescOfTheFirstChannelBeforeTime\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x1C, 58, (Destin->DescOfTheFirstChannelBeforeTime), (Destin->DescOfTheFirstChannelBeforeTime_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE DescOfTheSecondChannelBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x1D */
    ED_EXPECT_OPTIONAL_IE (0x1D,  8, 60, 19, Tmp_KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x1D) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DescOfTheSecondChannelBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 24;
		/* Read value part */
		RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, &(Destin->DescOfTheSecondChannelBeforeTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:61> Error decoding subfield DescOfTheSecondChannelBeforeTime\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x1D, 61, (Destin->DescOfTheSecondChannelBeforeTime), (Destin->DescOfTheSecondChannelBeforeTime_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:62> Message too short decoding subfield DescOfTheSecondChannelBeforeTime\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x1D, 61, (Destin->DescOfTheSecondChannelBeforeTime), (Destin->DescOfTheSecondChannelBeforeTime_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE FrequencyChannelSequenceBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x1E */
    ED_EXPECT_OPTIONAL_IE (0x1E,  8, 63, 20, Tmp_KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x1E) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_FrequencyChannelSequenceBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 72;
		/* Read value part */
		RetLen = DECODE_c_FreqChannelSeq (Buffer, CurrOfs, &(Destin->FrequencyChannelSequenceBeforeTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:64> Error decoding subfield FrequencyChannelSequenceBeforeTime\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x1E, 64, (Destin->FrequencyChannelSequenceBeforeTime), (Destin->FrequencyChannelSequenceBeforeTime_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:65> Message too short decoding subfield FrequencyChannelSequenceBeforeTime\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x1E, 64, (Destin->FrequencyChannelSequenceBeforeTime), (Destin->FrequencyChannelSequenceBeforeTime_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE MobileAllocationBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x21 */
    ED_EXPECT_OPTIONAL_IE (0x21,  8, 66, 21, Tmp_KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x21) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_MobileAllocationBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 64)) {
			ED_SIGNAL_ERROR ("<ERRID:67> Size error decoding IE MobileAllocationBeforeTime\n");
			ED_HANDLE_IE_SIZE_ERROR (0x21, 67, (Destin->MobileAllocationBeforeTime), (Destin->MobileAllocationBeforeTime_Present))
		} 
#endif
		/* Read value part */
		RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, &(Destin->MobileAllocationBeforeTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:68> Error decoding subfield MobileAllocationBeforeTime\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x21, 68, (Destin->MobileAllocationBeforeTime), (Destin->MobileAllocationBeforeTime_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:69> Message too short decoding subfield MobileAllocationBeforeTime\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x21, 68, (Destin->MobileAllocationBeforeTime), (Destin->MobileAllocationBeforeTime_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE CipherModeSetting
	------------------------------------------------------*/
	/* Detect IEI tag 0x09 */
    ED_EXPECT_OPTIONAL_IE (0x09,  4, 70, 22, Tmp_KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 4); */
	
	/* This is an optional field */
	if (Tag == 0x09) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_CipherModeSetting (Destin, ED_TRUE);
		CurrOfs += 4;
		Len = 4;
		/* Read value part */
		RetLen = DECODE_c_CipherModeSetting (Buffer, CurrOfs, &(Destin->CipherModeSetting), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:71> Error decoding subfield CipherModeSetting\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x09, 71, (Destin->CipherModeSetting), (Destin->CipherModeSetting_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:72> Message too short decoding subfield CipherModeSetting\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x09, 71, (Destin->CipherModeSetting), (Destin->CipherModeSetting_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE VgcsTargetModeIndication
	------------------------------------------------------*/
	/* Detect IEI tag 0x01 */
    ED_EXPECT_OPTIONAL_IE (0x01,  8, 73, 23, Tmp_KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x01) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_VgcsTargetModeIndication (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len != 8) {
			ED_SIGNAL_ERROR ("<ERRID:74> Size error decoding IE VgcsTargetModeIndication\n");
			ED_HANDLE_IE_SIZE_ERROR (0x01, 74, (Destin->VgcsTargetModeIndication), (Destin->VgcsTargetModeIndication_Present))
		} 
#endif
		/* Read value part */
		Destin->VgcsTargetModeIndication = EDBitsToInt (Buffer, CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:75> Error decoding subfield VgcsTargetModeIndication\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x01, 75, (Destin->VgcsTargetModeIndication), (Destin->VgcsTargetModeIndication_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:76> Message too short decoding subfield VgcsTargetModeIndication\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x01, 75, (Destin->VgcsTargetModeIndication), (Destin->VgcsTargetModeIndication_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE MultiRateCfg
	------------------------------------------------------*/
	/* Detect IEI tag 0x03 */
    ED_EXPECT_OPTIONAL_IE (0x03,  8, 77, 24, Tmp_KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x03) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_MultiRateCfg (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 16) || (Len > 48)) {
			ED_SIGNAL_ERROR ("<ERRID:78> Size error decoding IE MultiRateCfg\n");
			ED_HANDLE_IE_SIZE_ERROR (0x03, 78, (Destin->MultiRateCfg), (Destin->MultiRateCfg_Present))
		} 
#endif
		/* Read value part */
		ALLOC_c_ASSIGNMENT_COMMAND_MultiRateCfg (&(Destin->MultiRateCfg), Len);
		EDCopyBits (Destin->MultiRateCfg.value, 0, Buffer, CurrOfs, Len);
		Destin->MultiRateCfg.usedBits = Len;RetLen = Len;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:79> Error decoding subfield MultiRateCfg\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x03, 79, (Destin->MultiRateCfg), (Destin->MultiRateCfg_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:80> Message too short decoding subfield MultiRateCfg\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x03, 79, (Destin->MultiRateCfg), (Destin->MultiRateCfg_Present));
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CHANNEL_MODE_MODIFY
-----------------------------------------------------------------*/
long DECODE_c_CHANNEL_MODE_MODIFY (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CHANNEL_MODE_MODIFY* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_CHANNEL_MODE_MODIFY (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CHANNEL_MODE_MODIFY
-----------------------------------------------------------------*/
long DECODE_BODY_c_CHANNEL_MODE_MODIFY (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CHANNEL_MODE_MODIFY* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Table containing the expected sequence of IEIs */
	const TEDTLVSkipItem TLVSkipItems [] = {
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{1, 255, ED_SKIPLIST_OPTIONAL},
		{3, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE ChannelDescription
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part */
	RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, &(Destin->ChannelDescription), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:81> Error decoding subfield ChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 81, (Destin->ChannelDescription));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:82> Message too short decoding subfield ChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 81, (Destin->ChannelDescription));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ChannelMode
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part */
	Destin->ChannelMode = EDBitsToInt (Buffer, CurrOfs, 8);
	RetLen = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:83> Error decoding subfield ChannelMode\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 83, (Destin->ChannelMode));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:84> Message too short decoding subfield ChannelMode\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 83, (Destin->ChannelMode));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE VgcsTargetModeIndication
	------------------------------------------------------*/
	/* Detect IEI tag 0x01 */
	ED_EXPECT_OPTIONAL_IE (0x01,  8, 85, 2, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x01) {
		SETPRESENT_c_CHANNEL_MODE_MODIFY_VgcsTargetModeIndication (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len != 8) {
			ED_SIGNAL_ERROR ("<ERRID:86> Size error decoding IE VgcsTargetModeIndication\n");
			ED_HANDLE_IE_SIZE_ERROR (0x01, 86, (Destin->VgcsTargetModeIndication), (Destin->VgcsTargetModeIndication_Present))
		} 
#endif
		/* Read value part */
		Destin->VgcsTargetModeIndication = EDBitsToInt (Buffer, CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:87> Error decoding subfield VgcsTargetModeIndication\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x01, 87, (Destin->VgcsTargetModeIndication), (Destin->VgcsTargetModeIndication_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:88> Message too short decoding subfield VgcsTargetModeIndication\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x01, 87, (Destin->VgcsTargetModeIndication), (Destin->VgcsTargetModeIndication_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE MultiRateCfg
	------------------------------------------------------*/
	/* Detect IEI tag 0x03 */
	ED_EXPECT_OPTIONAL_IE (0x03,  8, 89, 3, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x03) {
		SETPRESENT_c_CHANNEL_MODE_MODIFY_MultiRateCfg (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 16) || (Len > 48)) {
			ED_SIGNAL_ERROR ("<ERRID:90> Size error decoding IE MultiRateCfg\n");
			ED_HANDLE_IE_SIZE_ERROR (0x03, 90, (Destin->MultiRateCfg), (Destin->MultiRateCfg_Present))
		} 
#endif
		/* Read value part */
		ALLOC_c_CHANNEL_MODE_MODIFY_MultiRateCfg (&(Destin->MultiRateCfg), Len);
		EDCopyBits (Destin->MultiRateCfg.value, 0, Buffer, CurrOfs, Len);
		Destin->MultiRateCfg.usedBits = Len;RetLen = Len;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:91> Error decoding subfield MultiRateCfg\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x03, 91, (Destin->MultiRateCfg), (Destin->MultiRateCfg_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:92> Message too short decoding subfield MultiRateCfg\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x03, 91, (Destin->MultiRateCfg), (Destin->MultiRateCfg_Present));
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CHANNEL_RELEASE
-----------------------------------------------------------------*/
long DECODE_c_CHANNEL_RELEASE (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CHANNEL_RELEASE* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_CHANNEL_RELEASE (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CHANNEL_RELEASE
-----------------------------------------------------------------*/
long DECODE_BODY_c_CHANNEL_RELEASE (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CHANNEL_RELEASE* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Table containing the expected sequence of IEIs */
	const TEDTLVSkipItem TLVSkipItems [] = {
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{115, 255, ED_SKIPLIST_OPTIONAL},
		{116, 255, ED_SKIPLIST_OPTIONAL},
		{128, 240, ED_SKIPLIST_OPTIONAL},
		{192, 240, ED_SKIPLIST_OPTIONAL},
		{117, 255, ED_SKIPLIST_OPTIONAL},
		{118, 255, ED_SKIPLIST_OPTIONAL},
		{98, 255, ED_SKIPLIST_OPTIONAL},
		{119, 255, ED_SKIPLIST_OPTIONAL},
		{124, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE RrCause
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part */
	Destin->RrCause = EDBitsToInt (Buffer, CurrOfs, 8);
	RetLen = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:93> Error decoding subfield RrCause\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 93, (Destin->RrCause));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:94> Message too short decoding subfield RrCause\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 93, (Destin->RrCause));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE BaRange
	------------------------------------------------------*/
	/* Detect IEI tag 0x73 */
	ED_EXPECT_OPTIONAL_IE (0x73,  8, 95, 1, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x73) {
		SETPRESENT_c_CHANNEL_RELEASE_BaRange (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 32) || (Len > 4784)) {
			ED_SIGNAL_ERROR ("<ERRID:96> Size error decoding IE BaRange\n");
			ED_HANDLE_IE_SIZE_ERROR (0x73, 96, (Destin->BaRange), (Destin->BaRange_Present))
		} 
#endif
		/* Read value part */
		RetLen = DECODE_c_BaRange (Buffer, CurrOfs, &(Destin->BaRange), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:97> Error decoding subfield BaRange\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x73, 97, (Destin->BaRange), (Destin->BaRange_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:98> Message too short decoding subfield BaRange\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x73, 97, (Destin->BaRange), (Destin->BaRange_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE GroupChannelDescription
	------------------------------------------------------*/
	/* Detect IEI tag 0x74 */
	ED_EXPECT_OPTIONAL_IE (0x74,  8, 99, 2, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x74) {
		SETPRESENT_c_CHANNEL_RELEASE_GroupChannelDescription (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 24) || (Len > 88)) {
			ED_SIGNAL_ERROR ("<ERRID:100> Size error decoding IE GroupChannelDescription\n");
			ED_HANDLE_IE_SIZE_ERROR (0x74, 100, (Destin->GroupChannelDescription), (Destin->GroupChannelDescription_Present))
		} 
#endif
		/* Read value part */
		RetLen = DECODE_c_GrpChannelDesc (Buffer, CurrOfs, &(Destin->GroupChannelDescription), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:101> Error decoding subfield GroupChannelDescription\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x74, 101, (Destin->GroupChannelDescription), (Destin->GroupChannelDescription_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:102> Message too short decoding subfield GroupChannelDescription\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x74, 101, (Destin->GroupChannelDescription), (Destin->GroupChannelDescription_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE GroupCipherKeyNum
	------------------------------------------------------*/
	/* Detect IEI tag 0x08 */
	ED_EXPECT_OPTIONAL_IE (0x08,  4, 103, 3, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 4); */
	
	/* This is an optional field */
	if (Tag == 0x08) {
		SETPRESENT_c_CHANNEL_RELEASE_GroupCipherKeyNum (Destin, ED_TRUE);
		CurrOfs += 4;
		Len = 4;
		/* Read value part */
		Destin->GroupCipherKeyNum = EDBitsToInt (Buffer, CurrOfs, 4);
		RetLen = 4;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:104> Error decoding subfield GroupCipherKeyNum\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x08, 104, (Destin->GroupCipherKeyNum), (Destin->GroupCipherKeyNum_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:105> Message too short decoding subfield GroupCipherKeyNum\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x08, 104, (Destin->GroupCipherKeyNum), (Destin->GroupCipherKeyNum_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE GprsResumption
	------------------------------------------------------*/
	/* Detect IEI tag 0x0C */
	ED_EXPECT_OPTIONAL_IE (0x0C,  4, 106, 4, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 4); */
	
	/* This is an optional field */
	if (Tag == 0x0C) {
		SETPRESENT_c_CHANNEL_RELEASE_GprsResumption (Destin, ED_TRUE);
		CurrOfs += 4;
		Len = 4;
		/* Read value part */
		RetLen = DECODE_c_GPRSResumption (Buffer, CurrOfs, &(Destin->GprsResumption), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:107> Error decoding subfield GprsResumption\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x0C, 107, (Destin->GprsResumption), (Destin->GprsResumption_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:108> Message too short decoding subfield GprsResumption\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x0C, 107, (Destin->GprsResumption), (Destin->GprsResumption_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE BaListPref
	------------------------------------------------------*/
	/* Detect IEI tag 0x75 */
	ED_EXPECT_OPTIONAL_IE (0x75,  8, 109, 5, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x75) {
		SETPRESENT_c_CHANNEL_RELEASE_BaListPref (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 4784)) {
			ED_SIGNAL_ERROR ("<ERRID:110> Size error decoding IE BaListPref\n");
			ED_HANDLE_IE_SIZE_ERROR (0x75, 110, (Destin->BaListPref), (Destin->BaListPref_Present))
		} 
#endif
		/* Read value part */
		RetLen = DECODE_c_BA_List_Pref (Buffer, CurrOfs, &(Destin->BaListPref), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:111> Error decoding subfield BaListPref\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x75, 111, (Destin->BaListPref), (Destin->BaListPref_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:112> Message too short decoding subfield BaListPref\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x75, 111, (Destin->BaListPref), (Destin->BaListPref_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE UTRANFreqList
	------------------------------------------------------*/
	/* Detect IEI tag 0x76 */
	ED_EXPECT_OPTIONAL_IE (0x76,  8, 113, 6, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x76) {
		SETPRESENT_c_CHANNEL_RELEASE_UTRANFreqList (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 4784)) {
			ED_SIGNAL_ERROR ("<ERRID:114> Size error decoding IE UTRANFreqList\n");
			ED_HANDLE_IE_SIZE_ERROR (0x76, 114, (Destin->UTRANFreqList), (Destin->UTRANFreqList_Present))
		} 
#endif
		/* Read value part */
		RetLen = DECODE_c_UTRANFreqList (Buffer, CurrOfs, &(Destin->UTRANFreqList), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:115> Error decoding subfield UTRANFreqList\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x76, 115, (Destin->UTRANFreqList), (Destin->UTRANFreqList_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:116> Message too short decoding subfield UTRANFreqList\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x76, 115, (Destin->UTRANFreqList), (Destin->UTRANFreqList_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE CellChannelDescription
	------------------------------------------------------*/
	/* Detect IEI tag 0x62 */
	ED_EXPECT_OPTIONAL_IE (0x62,  8, 117, 7, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x62) {
		SETPRESENT_c_CHANNEL_RELEASE_CellChannelDescription (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 128;
		/* Read value part */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, &(Destin->CellChannelDescription), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:118> Error decoding subfield CellChannelDescription\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x62, 118, (Destin->CellChannelDescription), (Destin->CellChannelDescription_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:119> Message too short decoding subfield CellChannelDescription\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x62, 118, (Destin->CellChannelDescription), (Destin->CellChannelDescription_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE CellSelectionIndicatorAfterRel
	------------------------------------------------------*/
	/* Detect IEI tag 0x77 */
	ED_EXPECT_OPTIONAL_IE (0x77,  8, 120, 8, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x77) {
		SETPRESENT_c_CHANNEL_RELEASE_CellSelectionIndicatorAfterRel (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 16) || (Len > 4784)) {
			ED_SIGNAL_ERROR ("<ERRID:121> Size error decoding IE CellSelectionIndicatorAfterRel\n");
			ED_HANDLE_IE_SIZE_ERROR (0x77, 121, (Destin->CellSelectionIndicatorAfterRel), (Destin->CellSelectionIndicatorAfterRel_Present))
		} 
#endif
		/* Read value part */
		RetLen = DECODE_c_CellSelectionIndicator (Buffer, CurrOfs, &(Destin->CellSelectionIndicatorAfterRel), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:122> Error decoding subfield CellSelectionIndicatorAfterRel\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x77, 122, (Destin->CellSelectionIndicatorAfterRel), (Destin->CellSelectionIndicatorAfterRel_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:123> Message too short decoding subfield CellSelectionIndicatorAfterRel\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x77, 122, (Destin->CellSelectionIndicatorAfterRel), (Destin->CellSelectionIndicatorAfterRel_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE Individualpriorities
	------------------------------------------------------*/
	/* Detect IEI tag 0x7C */
	ED_EXPECT_OPTIONAL_IE (0x7C,  8, 124, 9, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x7C) {
		SETPRESENT_c_CHANNEL_RELEASE_Individualpriorities (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 4784)) {
			ED_SIGNAL_ERROR ("<ERRID:125> Size error decoding IE Individualpriorities\n");
			ED_HANDLE_IE_SIZE_ERROR (0x7C, 125, (Destin->Individualpriorities), (Destin->Individualpriorities_Present))
		} 
#endif
		/* Read value part */
		RetLen = DECODE_c_Individualpriorities (Buffer, CurrOfs, &(Destin->Individualpriorities), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:126> Error decoding subfield Individualpriorities\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x7C, 126, (Destin->Individualpriorities), (Destin->Individualpriorities_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:127> Message too short decoding subfield Individualpriorities\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x7C, 126, (Destin->Individualpriorities), (Destin->Individualpriorities_Present));
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CIPHERING_MODE_COMMAND
-----------------------------------------------------------------*/
long DECODE_c_CIPHERING_MODE_COMMAND (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CIPHERING_MODE_COMMAND* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_CIPHERING_MODE_COMMAND (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CIPHERING_MODE_COMMAND
-----------------------------------------------------------------*/
long DECODE_BODY_c_CIPHERING_MODE_COMMAND (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CIPHERING_MODE_COMMAND* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE CiphModeSetting
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part */
	RetLen = DECODE_c_CipherModeSetting (Buffer, (CurrOfs+4), &(Destin->CiphModeSetting), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:128> Error decoding subfield CiphModeSetting\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 128, (Destin->CiphModeSetting));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:129> Message too short decoding subfield CiphModeSetting\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 128, (Destin->CiphModeSetting));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE CipherResp
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part */
	RetLen = DECODE_c_CipherResponse (Buffer, (CurrOfs-4), &(Destin->CipherResp), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:130> Error decoding subfield CipherResp\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 130, (Destin->CipherResp));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:131> Message too short decoding subfield CipherResp\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 130, (Destin->CipherResp));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CLASSMARK_ENQUIRY
-----------------------------------------------------------------*/
long DECODE_c_CLASSMARK_ENQUIRY (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CLASSMARK_ENQUIRY* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_CLASSMARK_ENQUIRY (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CLASSMARK_ENQUIRY
-----------------------------------------------------------------*/
long DECODE_BODY_c_CLASSMARK_ENQUIRY (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CLASSMARK_ENQUIRY* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Table containing the expected sequence of IEIs */
	const TEDTLVSkipItem TLVSkipItems [] = {
		{16, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE ClassmarkEnquiryMask
	------------------------------------------------------*/
	/* Detect IEI tag 0x10 */
	ED_EXPECT_OPTIONAL_IE (0x10,  8, 132, 0, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x10) {
		SETPRESENT_c_CLASSMARK_ENQUIRY_ClassmarkEnquiryMask (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len != 8) {
			ED_SIGNAL_ERROR ("<ERRID:133> Size error decoding IE ClassmarkEnquiryMask\n");
			ED_HANDLE_IE_SIZE_ERROR (0x10, 133, (Destin->ClassmarkEnquiryMask), (Destin->ClassmarkEnquiryMask_Present))
		} 
#endif
		/* Read value part */
		RetLen = DECODE_c_ClassmarkEnquiryMask (Buffer, CurrOfs, &(Destin->ClassmarkEnquiryMask), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:134> Error decoding subfield ClassmarkEnquiryMask\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x10, 134, (Destin->ClassmarkEnquiryMask), (Destin->ClassmarkEnquiryMask_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:135> Message too short decoding subfield ClassmarkEnquiryMask\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x10, 134, (Destin->ClassmarkEnquiryMask), (Destin->ClassmarkEnquiryMask_Present));
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE FREQUENCY_REDEFINITION
-----------------------------------------------------------------*/
long DECODE_c_FREQUENCY_REDEFINITION (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_FREQUENCY_REDEFINITION* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_FREQUENCY_REDEFINITION (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE FREQUENCY_REDEFINITION
-----------------------------------------------------------------*/
long DECODE_BODY_c_FREQUENCY_REDEFINITION (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_FREQUENCY_REDEFINITION* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Table containing the expected sequence of IEIs */
	const TEDTLVSkipItem TLVSkipItems [] = {
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{98, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE ChannelDescription
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part */
	RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, &(Destin->ChannelDescription), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:136> Error decoding subfield ChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 136, (Destin->ChannelDescription));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:137> Message too short decoding subfield ChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 136, (Destin->ChannelDescription));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileAllocation
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Len > 64) {
		ED_SIGNAL_ERROR ("<ERRID:138> Size error decoding IE MobileAllocation\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 138, (Destin->MobileAllocation), (Destin->MobileAllocation_Present))
	} 
#endif
	/* Read value part */
	RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, &(Destin->MobileAllocation), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:139> Error decoding subfield MobileAllocation\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 139, (Destin->MobileAllocation));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:140> Message too short decoding subfield MobileAllocation\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 139, (Destin->MobileAllocation));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE StartingTime
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 16;
	/* Read value part */
	RetLen = DECODE_c_StartingTime (Buffer, CurrOfs, &(Destin->StartingTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:141> Error decoding subfield StartingTime\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 141, (Destin->StartingTime));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:142> Message too short decoding subfield StartingTime\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 141, (Destin->StartingTime));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE CellChannelDescription
	------------------------------------------------------*/
	/* Detect IEI tag 0x62 */
	ED_EXPECT_OPTIONAL_IE (0x62,  8, 143, 3, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x62) {
		SETPRESENT_c_FREQUENCY_REDEFINITION_CellChannelDescription (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 128;
		/* Read value part */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, &(Destin->CellChannelDescription), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:144> Error decoding subfield CellChannelDescription\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x62, 144, (Destin->CellChannelDescription), (Destin->CellChannelDescription_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:145> Message too short decoding subfield CellChannelDescription\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x62, 144, (Destin->CellChannelDescription), (Destin->CellChannelDescription_Present));
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_COMMAND
-----------------------------------------------------------------*/
long DECODE_c_HANDOVER_COMMAND (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_HANDOVER_COMMAND* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_HANDOVER_COMMAND (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_COMMAND
-----------------------------------------------------------------*/
long DECODE_BODY_c_HANDOVER_COMMAND (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_HANDOVER_COMMAND* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Table containing the expected sequence of IEIs */
	const TEDTLVSkipItem TLVSkipItems [] = {
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{208, 240, ED_SKIPLIST_OPTIONAL},
		{2, 255, ED_SKIPLIST_OPTIONAL},
		{5, 255, ED_SKIPLIST_OPTIONAL},
		{98, 255, ED_SKIPLIST_OPTIONAL},
		{16, 255, ED_SKIPLIST_OPTIONAL},
		{99, 255, ED_SKIPLIST_OPTIONAL},
		{17, 255, ED_SKIPLIST_OPTIONAL},
		{19, 255, ED_SKIPLIST_OPTIONAL},
		{20, 255, ED_SKIPLIST_OPTIONAL},
		{21, 255, ED_SKIPLIST_OPTIONAL},
		{22, 255, ED_SKIPLIST_OPTIONAL},
		{23, 255, ED_SKIPLIST_OPTIONAL},
		{24, 255, ED_SKIPLIST_OPTIONAL},
		{100, 255, ED_SKIPLIST_OPTIONAL},
		{102, 255, ED_SKIPLIST_OPTIONAL},
		{105, 255, ED_SKIPLIST_OPTIONAL},
		{114, 255, ED_SKIPLIST_OPTIONAL},
		{124, 255, ED_SKIPLIST_OPTIONAL},
		{123, 255, ED_SKIPLIST_OPTIONAL},
		{125, 255, ED_SKIPLIST_OPTIONAL},
		{18, 255, ED_SKIPLIST_OPTIONAL},
		{25, 255, ED_SKIPLIST_OPTIONAL},
		{28, 255, ED_SKIPLIST_OPTIONAL},
		{29, 255, ED_SKIPLIST_OPTIONAL},
		{30, 255, ED_SKIPLIST_OPTIONAL},
		{33, 255, ED_SKIPLIST_OPTIONAL},
		{144, 240, ED_SKIPLIST_OPTIONAL},
		{1, 255, ED_SKIPLIST_OPTIONAL},
		{3, 255, ED_SKIPLIST_OPTIONAL},
		{118, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE CellDescription
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 16;
	/* Read value part */
	RetLen = DECODE_c_CellDescription (Buffer, CurrOfs, &(Destin->CellDescription), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:146> Error decoding subfield CellDescription\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 146, (Destin->CellDescription));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:147> Message too short decoding subfield CellDescription\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 146, (Destin->CellDescription));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE DescriptionOfTheFirstChannelAfterTime
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part */
	RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, &(Destin->DescriptionOfTheFirstChannelAfterTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:148> Error decoding subfield DescriptionOfTheFirstChannelAfterTime\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 148, (Destin->DescriptionOfTheFirstChannelAfterTime));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:149> Message too short decoding subfield DescriptionOfTheFirstChannelAfterTime\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 148, (Destin->DescriptionOfTheFirstChannelAfterTime));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE HandoverRef
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part */
	Destin->HandoverRef = EDBitsToInt (Buffer, CurrOfs, 8);
	RetLen = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:150> Error decoding subfield HandoverRef\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 150, (Destin->HandoverRef));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:151> Message too short decoding subfield HandoverRef\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 150, (Destin->HandoverRef));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE PowerCommandAndAccessType
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part */
	RetLen = DECODE_c_PowerCommandAndAccessType (Buffer, CurrOfs, &(Destin->PowerCommandAndAccessType), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:152> Error decoding subfield PowerCommandAndAccessType\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 152, (Destin->PowerCommandAndAccessType));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:153> Message too short decoding subfield PowerCommandAndAccessType\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 152, (Destin->PowerCommandAndAccessType));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE SynchronizationIndication
	------------------------------------------------------*/
	/* Detect IEI tag 0x0D */
	ED_EXPECT_OPTIONAL_IE (0x0D,  4, 154, 4, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 4); */
	
	/* This is an optional field */
	if (Tag == 0x0D) {
		SETPRESENT_c_HANDOVER_COMMAND_SynchronizationIndication (Destin, ED_TRUE);
		CurrOfs += 4;
		Len = 4;
		/* Read value part */
		RetLen = DECODE_c_SyncInd (Buffer, CurrOfs, &(Destin->SynchronizationIndication), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:155> Error decoding subfield SynchronizationIndication\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x0D, 155, (Destin->SynchronizationIndication), (Destin->SynchronizationIndication_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:156> Message too short decoding subfield SynchronizationIndication\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x0D, 155, (Destin->SynchronizationIndication), (Destin->SynchronizationIndication_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE FrequencyShortListAfterTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x02 */
	ED_EXPECT_OPTIONAL_IE (0x02,  8, 157, 5, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x02) {
		SETPRESENT_c_HANDOVER_COMMAND_FrequencyShortListAfterTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 72;
		/* Read value part */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, &(Destin->FrequencyShortListAfterTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:158> Error decoding subfield FrequencyShortListAfterTime\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x02, 158, (Destin->FrequencyShortListAfterTime), (Destin->FrequencyShortListAfterTime_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:159> Message too short decoding subfield FrequencyShortListAfterTime\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x02, 158, (Destin->FrequencyShortListAfterTime), (Destin->FrequencyShortListAfterTime_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE FrequencyListAfterTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x05 */
	ED_EXPECT_OPTIONAL_IE (0x05,  8, 160, 6, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x05) {
		SETPRESENT_c_HANDOVER_COMMAND_FrequencyListAfterTime (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 16) || (Len > 1032)) {
			ED_SIGNAL_ERROR ("<ERRID:161> Size error decoding IE FrequencyListAfterTime\n");
			ED_HANDLE_IE_SIZE_ERROR (0x05, 161, (Destin->FrequencyListAfterTime), (Destin->FrequencyListAfterTime_Present))
		} 
#endif
		/* Read value part */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, &(Destin->FrequencyListAfterTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:162> Error decoding subfield FrequencyListAfterTime\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x05, 162, (Destin->FrequencyListAfterTime), (Destin->FrequencyListAfterTime_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:163> Message too short decoding subfield FrequencyListAfterTime\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x05, 162, (Destin->FrequencyListAfterTime), (Destin->FrequencyListAfterTime_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE CellChannelDescription
	------------------------------------------------------*/
	/* Detect IEI tag 0x62 */
	ED_EXPECT_OPTIONAL_IE (0x62,  8, 164, 7, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x62) {
		SETPRESENT_c_HANDOVER_COMMAND_CellChannelDescription (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 128;
		/* Read value part */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, &(Destin->CellChannelDescription), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:165> Error decoding subfield CellChannelDescription\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x62, 165, (Destin->CellChannelDescription), (Destin->CellChannelDescription_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:166> Message too short decoding subfield CellChannelDescription\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x62, 165, (Destin->CellChannelDescription), (Destin->CellChannelDescription_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE DescriptionOfTheMultislotCfg
	------------------------------------------------------*/
	/* Detect IEI tag 0x10 */
	ED_EXPECT_OPTIONAL_IE (0x10,  8, 167, 8, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x10) {
		SETPRESENT_c_HANDOVER_COMMAND_DescriptionOfTheMultislotCfg (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 80)) {
			ED_SIGNAL_ERROR ("<ERRID:168> Size error decoding IE DescriptionOfTheMultislotCfg\n");
			ED_HANDLE_IE_SIZE_ERROR (0x10, 168, (Destin->DescriptionOfTheMultislotCfg), (Destin->DescriptionOfTheMultislotCfg_Present))
		} 
#endif
		/* Read value part */
		ALLOC_c_HANDOVER_COMMAND_DescriptionOfTheMultislotCfg (&(Destin->DescriptionOfTheMultislotCfg), Len);
		EDCopyBits (Destin->DescriptionOfTheMultislotCfg.value, 0, Buffer, CurrOfs, Len);
		Destin->DescriptionOfTheMultislotCfg.usedBits = Len;RetLen = Len;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:169> Error decoding subfield DescriptionOfTheMultislotCfg\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x10, 169, (Destin->DescriptionOfTheMultislotCfg), (Destin->DescriptionOfTheMultislotCfg_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:170> Message too short decoding subfield DescriptionOfTheMultislotCfg\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x10, 169, (Destin->DescriptionOfTheMultislotCfg), (Destin->DescriptionOfTheMultislotCfg_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfTheFirstChannelChannelSet1
	------------------------------------------------------*/
	/* Detect IEI tag 0x63 */
	ED_EXPECT_OPTIONAL_IE (0x63,  8, 171, 9, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x63) {
		SETPRESENT_c_HANDOVER_COMMAND_ModeOfTheFirstChannelChannelSet1 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part */
		Destin->ModeOfTheFirstChannelChannelSet1 = EDBitsToInt (Buffer, CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:172> Error decoding subfield ModeOfTheFirstChannelChannelSet1\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x63, 172, (Destin->ModeOfTheFirstChannelChannelSet1), (Destin->ModeOfTheFirstChannelChannelSet1_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:173> Message too short decoding subfield ModeOfTheFirstChannelChannelSet1\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x63, 172, (Destin->ModeOfTheFirstChannelChannelSet1), (Destin->ModeOfTheFirstChannelChannelSet1_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet2
	------------------------------------------------------*/
	/* Detect IEI tag 0x11 */
	ED_EXPECT_OPTIONAL_IE (0x11,  8, 174, 10, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x11) {
		SETPRESENT_c_HANDOVER_COMMAND_ModeOfChannelSet2 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part */
		Destin->ModeOfChannelSet2 = EDBitsToInt (Buffer, CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:175> Error decoding subfield ModeOfChannelSet2\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x11, 175, (Destin->ModeOfChannelSet2), (Destin->ModeOfChannelSet2_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:176> Message too short decoding subfield ModeOfChannelSet2\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x11, 175, (Destin->ModeOfChannelSet2), (Destin->ModeOfChannelSet2_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet3
	------------------------------------------------------*/
	/* Detect IEI tag 0x13 */
	ED_EXPECT_OPTIONAL_IE (0x13,  8, 177, 11, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x13) {
		SETPRESENT_c_HANDOVER_COMMAND_ModeOfChannelSet3 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part */
		Destin->ModeOfChannelSet3 = EDBitsToInt (Buffer, CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:178> Error decoding subfield ModeOfChannelSet3\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x13, 178, (Destin->ModeOfChannelSet3), (Destin->ModeOfChannelSet3_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:179> Message too short decoding subfield ModeOfChannelSet3\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x13, 178, (Destin->ModeOfChannelSet3), (Destin->ModeOfChannelSet3_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet4
	------------------------------------------------------*/
	/* Detect IEI tag 0x14 */
	ED_EXPECT_OPTIONAL_IE (0x14,  8, 180, 12, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x14) {
		SETPRESENT_c_HANDOVER_COMMAND_ModeOfChannelSet4 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part */
		Destin->ModeOfChannelSet4 = EDBitsToInt (Buffer, CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:181> Error decoding subfield ModeOfChannelSet4\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x14, 181, (Destin->ModeOfChannelSet4), (Destin->ModeOfChannelSet4_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:182> Message too short decoding subfield ModeOfChannelSet4\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x14, 181, (Destin->ModeOfChannelSet4), (Destin->ModeOfChannelSet4_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet5
	------------------------------------------------------*/
	/* Detect IEI tag 0x15 */
	ED_EXPECT_OPTIONAL_IE (0x15,  8, 183, 13, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x15) {
		SETPRESENT_c_HANDOVER_COMMAND_ModeOfChannelSet5 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part */
		Destin->ModeOfChannelSet5 = EDBitsToInt (Buffer, CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:184> Error decoding subfield ModeOfChannelSet5\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x15, 184, (Destin->ModeOfChannelSet5), (Destin->ModeOfChannelSet5_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:185> Message too short decoding subfield ModeOfChannelSet5\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x15, 184, (Destin->ModeOfChannelSet5), (Destin->ModeOfChannelSet5_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet6
	------------------------------------------------------*/
	/* Detect IEI tag 0x16 */
	ED_EXPECT_OPTIONAL_IE (0x16,  8, 186, 14, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x16) {
		SETPRESENT_c_HANDOVER_COMMAND_ModeOfChannelSet6 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part */
		Destin->ModeOfChannelSet6 = EDBitsToInt (Buffer, CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:187> Error decoding subfield ModeOfChannelSet6\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x16, 187, (Destin->ModeOfChannelSet6), (Destin->ModeOfChannelSet6_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:188> Message too short decoding subfield ModeOfChannelSet6\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x16, 187, (Destin->ModeOfChannelSet6), (Destin->ModeOfChannelSet6_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet7
	------------------------------------------------------*/
	/* Detect IEI tag 0x17 */
	ED_EXPECT_OPTIONAL_IE (0x17,  8, 189, 15, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x17) {
		SETPRESENT_c_HANDOVER_COMMAND_ModeOfChannelSet7 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part */
		Destin->ModeOfChannelSet7 = EDBitsToInt (Buffer, CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:190> Error decoding subfield ModeOfChannelSet7\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x17, 190, (Destin->ModeOfChannelSet7), (Destin->ModeOfChannelSet7_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:191> Message too short decoding subfield ModeOfChannelSet7\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x17, 190, (Destin->ModeOfChannelSet7), (Destin->ModeOfChannelSet7_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet8
	------------------------------------------------------*/
	/* Detect IEI tag 0x18 */
	ED_EXPECT_OPTIONAL_IE (0x18,  8, 192, 16, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x18) {
		SETPRESENT_c_HANDOVER_COMMAND_ModeOfChannelSet8 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part */
		Destin->ModeOfChannelSet8 = EDBitsToInt (Buffer, CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:193> Error decoding subfield ModeOfChannelSet8\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x18, 193, (Destin->ModeOfChannelSet8), (Destin->ModeOfChannelSet8_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:194> Message too short decoding subfield ModeOfChannelSet8\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x18, 193, (Destin->ModeOfChannelSet8), (Destin->ModeOfChannelSet8_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE DescriptionOfTheSecondChannelAfterTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x64 */
	ED_EXPECT_OPTIONAL_IE (0x64,  8, 195, 17, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x64) {
		SETPRESENT_c_HANDOVER_COMMAND_DescriptionOfTheSecondChannelAfterTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 24;
		/* Read value part */
		RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, &(Destin->DescriptionOfTheSecondChannelAfterTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:196> Error decoding subfield DescriptionOfTheSecondChannelAfterTime\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x64, 196, (Destin->DescriptionOfTheSecondChannelAfterTime), (Destin->DescriptionOfTheSecondChannelAfterTime_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:197> Message too short decoding subfield DescriptionOfTheSecondChannelAfterTime\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x64, 196, (Destin->DescriptionOfTheSecondChannelAfterTime), (Destin->DescriptionOfTheSecondChannelAfterTime_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfTheSecondChannel
	------------------------------------------------------*/
	/* Detect IEI tag 0x66 */
	ED_EXPECT_OPTIONAL_IE (0x66,  8, 198, 18, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x66) {
		SETPRESENT_c_HANDOVER_COMMAND_ModeOfTheSecondChannel (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part */
		Destin->ModeOfTheSecondChannel = EDBitsToInt (Buffer, CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:199> Error decoding subfield ModeOfTheSecondChannel\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x66, 199, (Destin->ModeOfTheSecondChannel), (Destin->ModeOfTheSecondChannel_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:200> Message too short decoding subfield ModeOfTheSecondChannel\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x66, 199, (Destin->ModeOfTheSecondChannel), (Destin->ModeOfTheSecondChannel_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE FrequencyChannelSequenceAfterTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x69 */
	ED_EXPECT_OPTIONAL_IE (0x69,  8, 201, 19, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x69) {
		SETPRESENT_c_HANDOVER_COMMAND_FrequencyChannelSequenceAfterTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 72;
		/* Read value part */
		RetLen = DECODE_c_FreqChannelSeq (Buffer, CurrOfs, &(Destin->FrequencyChannelSequenceAfterTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:202> Error decoding subfield FrequencyChannelSequenceAfterTime\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x69, 202, (Destin->FrequencyChannelSequenceAfterTime), (Destin->FrequencyChannelSequenceAfterTime_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:203> Message too short decoding subfield FrequencyChannelSequenceAfterTime\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x69, 202, (Destin->FrequencyChannelSequenceAfterTime), (Destin->FrequencyChannelSequenceAfterTime_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE MobileAllocationAfterTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x72 */
	ED_EXPECT_OPTIONAL_IE (0x72,  8, 204, 20, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x72) {
		SETPRESENT_c_HANDOVER_COMMAND_MobileAllocationAfterTime (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 64)) {
			ED_SIGNAL_ERROR ("<ERRID:205> Size error decoding IE MobileAllocationAfterTime\n");
			ED_HANDLE_IE_SIZE_ERROR (0x72, 205, (Destin->MobileAllocationAfterTime), (Destin->MobileAllocationAfterTime_Present))
		} 
#endif
		/* Read value part */
		RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, &(Destin->MobileAllocationAfterTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:206> Error decoding subfield MobileAllocationAfterTime\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x72, 206, (Destin->MobileAllocationAfterTime), (Destin->MobileAllocationAfterTime_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:207> Message too short decoding subfield MobileAllocationAfterTime\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x72, 206, (Destin->MobileAllocationAfterTime), (Destin->MobileAllocationAfterTime_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE StartingTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x7C */
	ED_EXPECT_OPTIONAL_IE (0x7C,  8, 208, 21, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x7C) {
		SETPRESENT_c_HANDOVER_COMMAND_StartingTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 16;
		/* Read value part */
		RetLen = DECODE_c_StartingTime (Buffer, CurrOfs, &(Destin->StartingTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:209> Error decoding subfield StartingTime\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x7C, 209, (Destin->StartingTime), (Destin->StartingTime_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:210> Message too short decoding subfield StartingTime\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x7C, 209, (Destin->StartingTime), (Destin->StartingTime_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE RealTimeDifference
	------------------------------------------------------*/
	/* Detect IEI tag 0x7B */
	ED_EXPECT_OPTIONAL_IE (0x7B,  8, 211, 22, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x7B) {
		SETPRESENT_c_HANDOVER_COMMAND_RealTimeDifference (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len != 8) {
			ED_SIGNAL_ERROR ("<ERRID:212> Size error decoding IE RealTimeDifference\n");
			ED_HANDLE_IE_SIZE_ERROR (0x7B, 212, (Destin->RealTimeDifference), (Destin->RealTimeDifference_Present))
		} 
#endif
		/* Read value part */
		Destin->RealTimeDifference = EDBitsToInt (Buffer, CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:213> Error decoding subfield RealTimeDifference\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x7B, 213, (Destin->RealTimeDifference), (Destin->RealTimeDifference_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:214> Message too short decoding subfield RealTimeDifference\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x7B, 213, (Destin->RealTimeDifference), (Destin->RealTimeDifference_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE TimingAdvance
	------------------------------------------------------*/
	/* Detect IEI tag 0x7D */
	ED_EXPECT_OPTIONAL_IE (0x7D,  8, 215, 23, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x7D) {
		SETPRESENT_c_HANDOVER_COMMAND_TimingAdvance (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part */
		RetLen = DECODE_c_TimingAdvance (Buffer, CurrOfs, &(Destin->TimingAdvance), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:216> Error decoding subfield TimingAdvance\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x7D, 216, (Destin->TimingAdvance), (Destin->TimingAdvance_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:217> Message too short decoding subfield TimingAdvance\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x7D, 216, (Destin->TimingAdvance), (Destin->TimingAdvance_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE FrequencyShortListBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x12 */
	ED_EXPECT_OPTIONAL_IE (0x12,  8, 218, 24, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x12) {
		SETPRESENT_c_HANDOVER_COMMAND_FrequencyShortListBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 72;
		/* Read value part */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, &(Destin->FrequencyShortListBeforeTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:219> Error decoding subfield FrequencyShortListBeforeTime\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x12, 219, (Destin->FrequencyShortListBeforeTime), (Destin->FrequencyShortListBeforeTime_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:220> Message too short decoding subfield FrequencyShortListBeforeTime\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x12, 219, (Destin->FrequencyShortListBeforeTime), (Destin->FrequencyShortListBeforeTime_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE FrequencyListBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x19 */
	ED_EXPECT_OPTIONAL_IE (0x19,  8, 221, 25, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x19) {
		SETPRESENT_c_HANDOVER_COMMAND_FrequencyListBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 16) || (Len > 1032)) {
			ED_SIGNAL_ERROR ("<ERRID:222> Size error decoding IE FrequencyListBeforeTime\n");
			ED_HANDLE_IE_SIZE_ERROR (0x19, 222, (Destin->FrequencyListBeforeTime), (Destin->FrequencyListBeforeTime_Present))
		} 
#endif
		/* Read value part */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, &(Destin->FrequencyListBeforeTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:223> Error decoding subfield FrequencyListBeforeTime\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x19, 223, (Destin->FrequencyListBeforeTime), (Destin->FrequencyListBeforeTime_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:224> Message too short decoding subfield FrequencyListBeforeTime\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x19, 223, (Destin->FrequencyListBeforeTime), (Destin->FrequencyListBeforeTime_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE DescriptionOfTheFirstChannelBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x1C */
	ED_EXPECT_OPTIONAL_IE (0x1C,  8, 225, 26, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x1C) {
		SETPRESENT_c_HANDOVER_COMMAND_DescriptionOfTheFirstChannelBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 24;
		/* Read value part */
		RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, &(Destin->DescriptionOfTheFirstChannelBeforeTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:226> Error decoding subfield DescriptionOfTheFirstChannelBeforeTime\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x1C, 226, (Destin->DescriptionOfTheFirstChannelBeforeTime), (Destin->DescriptionOfTheFirstChannelBeforeTime_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:227> Message too short decoding subfield DescriptionOfTheFirstChannelBeforeTime\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x1C, 226, (Destin->DescriptionOfTheFirstChannelBeforeTime), (Destin->DescriptionOfTheFirstChannelBeforeTime_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE DescriptionOfTheSecondChannelBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x1D */
	ED_EXPECT_OPTIONAL_IE (0x1D,  8, 228, 27, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x1D) {
		SETPRESENT_c_HANDOVER_COMMAND_DescriptionOfTheSecondChannelBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 24;
		/* Read value part */
		RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, &(Destin->DescriptionOfTheSecondChannelBeforeTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:229> Error decoding subfield DescriptionOfTheSecondChannelBeforeTime\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x1D, 229, (Destin->DescriptionOfTheSecondChannelBeforeTime), (Destin->DescriptionOfTheSecondChannelBeforeTime_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:230> Message too short decoding subfield DescriptionOfTheSecondChannelBeforeTime\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x1D, 229, (Destin->DescriptionOfTheSecondChannelBeforeTime), (Destin->DescriptionOfTheSecondChannelBeforeTime_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE FrequencyChannelSequenceBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x1E */
	ED_EXPECT_OPTIONAL_IE (0x1E,  8, 231, 28, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x1E) {
		SETPRESENT_c_HANDOVER_COMMAND_FrequencyChannelSequenceBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 72;
		/* Read value part */
		RetLen = DECODE_c_FreqChannelSeq (Buffer, CurrOfs, &(Destin->FrequencyChannelSequenceBeforeTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:232> Error decoding subfield FrequencyChannelSequenceBeforeTime\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x1E, 232, (Destin->FrequencyChannelSequenceBeforeTime), (Destin->FrequencyChannelSequenceBeforeTime_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:233> Message too short decoding subfield FrequencyChannelSequenceBeforeTime\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x1E, 232, (Destin->FrequencyChannelSequenceBeforeTime), (Destin->FrequencyChannelSequenceBeforeTime_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE MobileAllocationBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x21 */
	ED_EXPECT_OPTIONAL_IE (0x21,  8, 234, 29, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x21) {
		SETPRESENT_c_HANDOVER_COMMAND_MobileAllocationBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 64)) {
			ED_SIGNAL_ERROR ("<ERRID:235> Size error decoding IE MobileAllocationBeforeTime\n");
			ED_HANDLE_IE_SIZE_ERROR (0x21, 235, (Destin->MobileAllocationBeforeTime), (Destin->MobileAllocationBeforeTime_Present))
		} 
#endif
		/* Read value part */
		RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, &(Destin->MobileAllocationBeforeTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:236> Error decoding subfield MobileAllocationBeforeTime\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x21, 236, (Destin->MobileAllocationBeforeTime), (Destin->MobileAllocationBeforeTime_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:237> Message too short decoding subfield MobileAllocationBeforeTime\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x21, 236, (Destin->MobileAllocationBeforeTime), (Destin->MobileAllocationBeforeTime_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE CipherModeSetting
	------------------------------------------------------*/
	/* Detect IEI tag 0x09 */
	ED_EXPECT_OPTIONAL_IE (0x09,  4, 238, 30, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 4); */
	
	/* This is an optional field */
	if (Tag == 0x09) {
		SETPRESENT_c_HANDOVER_COMMAND_CipherModeSetting (Destin, ED_TRUE);
		CurrOfs += 4;
		Len = 4;
		/* Read value part */
		RetLen = DECODE_c_CipherModeSetting (Buffer, CurrOfs, &(Destin->CipherModeSetting), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:239> Error decoding subfield CipherModeSetting\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x09, 239, (Destin->CipherModeSetting), (Destin->CipherModeSetting_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:240> Message too short decoding subfield CipherModeSetting\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x09, 239, (Destin->CipherModeSetting), (Destin->CipherModeSetting_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE VgcsTargetModeIndication
	------------------------------------------------------*/
	/* Detect IEI tag 0x01 */
	ED_EXPECT_OPTIONAL_IE (0x01,  8, 241, 31, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x01) {
		SETPRESENT_c_HANDOVER_COMMAND_VgcsTargetModeIndication (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len != 8) {
			ED_SIGNAL_ERROR ("<ERRID:242> Size error decoding IE VgcsTargetModeIndication\n");
			ED_HANDLE_IE_SIZE_ERROR (0x01, 242, (Destin->VgcsTargetModeIndication), (Destin->VgcsTargetModeIndication_Present))
		} 
#endif
		/* Read value part */
		Destin->VgcsTargetModeIndication = EDBitsToInt (Buffer, CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:243> Error decoding subfield VgcsTargetModeIndication\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x01, 243, (Destin->VgcsTargetModeIndication), (Destin->VgcsTargetModeIndication_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:244> Message too short decoding subfield VgcsTargetModeIndication\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x01, 243, (Destin->VgcsTargetModeIndication), (Destin->VgcsTargetModeIndication_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE MultiRateCfg
	------------------------------------------------------*/
	/* Detect IEI tag 0x03 */
	ED_EXPECT_OPTIONAL_IE (0x03,  8, 245, 32, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x03) {
		SETPRESENT_c_HANDOVER_COMMAND_MultiRateCfg (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 16) || (Len > 48)) {
			ED_SIGNAL_ERROR ("<ERRID:246> Size error decoding IE MultiRateCfg\n");
			ED_HANDLE_IE_SIZE_ERROR (0x03, 246, (Destin->MultiRateCfg), (Destin->MultiRateCfg_Present))
		} 
#endif
		/* Read value part */
		ALLOC_c_HANDOVER_COMMAND_MultiRateCfg (&(Destin->MultiRateCfg), Len);
		EDCopyBits (Destin->MultiRateCfg.value, 0, Buffer, CurrOfs, Len);
		Destin->MultiRateCfg.usedBits = Len;RetLen = Len;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:247> Error decoding subfield MultiRateCfg\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x03, 247, (Destin->MultiRateCfg), (Destin->MultiRateCfg_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:248> Message too short decoding subfield MultiRateCfg\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x03, 247, (Destin->MultiRateCfg), (Destin->MultiRateCfg_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE DynamicARFCNMapping
	------------------------------------------------------*/
	/* Detect IEI tag 0x76 */
	ED_EXPECT_OPTIONAL_IE (0x76,  8, 249, 33, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x76) {
		SETPRESENT_c_HANDOVER_COMMAND_DynamicARFCNMapping (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 32) || (Len > 256)) {
			ED_SIGNAL_ERROR ("<ERRID:250> Size error decoding IE DynamicARFCNMapping\n");
			ED_HANDLE_IE_SIZE_ERROR (0x76, 250, (Destin->DynamicARFCNMapping), (Destin->DynamicARFCNMapping_Present))
		} 
#endif
		/* Read value part */
		RetLen = DECODE_c_Dynamic_ARFCN_Mapping_X (Buffer, CurrOfs, &(Destin->DynamicARFCNMapping), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:251> Error decoding subfield DynamicARFCNMapping\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x76, 251, (Destin->DynamicARFCNMapping), (Destin->DynamicARFCNMapping_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:252> Message too short decoding subfield DynamicARFCNMapping\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x76, 251, (Destin->DynamicARFCNMapping), (Destin->DynamicARFCNMapping_Present));
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND
-----------------------------------------------------------------*/
long DECODE_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND
-----------------------------------------------------------------*/
long DECODE_BODY_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE HandoverToUtranCommand
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if ((Len < 8) || (Len > 4792)) {
		ED_SIGNAL_ERROR ("<ERRID:253> Size error decoding IE HandoverToUtranCommand\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 253, (Destin->HandoverToUtranCommand), (Destin->HandoverToUtranCommand_Present))
	} 
#endif
	/* Read value part */
	ALLOC_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_HandoverToUtranCommand (&(Destin->HandoverToUtranCommand), Len);
	EDCopyBits (Destin->HandoverToUtranCommand.value, 0, Buffer, CurrOfs, Len);
	Destin->HandoverToUtranCommand.usedBits = Len;RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:254> Error decoding subfield HandoverToUtranCommand\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 254, (Destin->HandoverToUtranCommand));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:255> Message too short decoding subfield HandoverToUtranCommand\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 254, (Destin->HandoverToUtranCommand));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PHYSICAL_INFORMATION
-----------------------------------------------------------------*/
long DECODE_c_PHYSICAL_INFORMATION (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PHYSICAL_INFORMATION* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_PHYSICAL_INFORMATION (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PHYSICAL_INFORMATION
-----------------------------------------------------------------*/
long DECODE_BODY_c_PHYSICAL_INFORMATION (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PHYSICAL_INFORMATION* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE TimingAdvance
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part */
	RetLen = DECODE_c_TimingAdvance (Buffer, CurrOfs, &(Destin->TimingAdvance), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:256> Error decoding subfield TimingAdvance\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 256, (Destin->TimingAdvance));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:257> Message too short decoding subfield TimingAdvance\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 256, (Destin->TimingAdvance));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE RR_STATUS
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_RR_STATUS (char* Buffer, long BitOffset, const c_RR_STATUS* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 18, 8);
		CurrOfs += 8;
	}
	
	
	/* Code for RrCause */
	{
		/* Append to buffer value part */
		EDIntToBits (Buffer, CurrOfs, Source->RrCause, 8);
		Len = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:258> Error encoding subfield RrCause\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE RR_STATUS
-----------------------------------------------------------------*/
long ENCODE_c_RR_STATUS (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_RR_STATUS* ED_CONST Source)
{
	return L3_ENCODE_c_RR_STATUS (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE RR_STATUS
-----------------------------------------------------------------*/
long ENCODE_BODY_c_RR_STATUS (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_RR_STATUS* ED_CONST Source)
{
	return L3_ENCODE_c_RR_STATUS (Buffer, BitOffset, Source, 1);
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE RR_STATUS
-----------------------------------------------------------------*/
long DECODE_c_RR_STATUS (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_RR_STATUS* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_RR_STATUS (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE RR_STATUS
-----------------------------------------------------------------*/
long DECODE_BODY_c_RR_STATUS (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_RR_STATUS* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE RrCause
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part */
	Destin->RrCause = EDBitsToInt (Buffer, CurrOfs, 8);
	RetLen = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:259> Error decoding subfield RrCause\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 259, (Destin->RrCause));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:260> Message too short decoding subfield RrCause\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 259, (Destin->RrCause));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE APPLICATION_INFORMATION
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_APPLICATION_INFORMATION (char* Buffer, long BitOffset, const c_APPLICATION_INFORMATION* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 56, 8);
		CurrOfs += 8;
	}
	
	
	/* Code for ApduId */
	{
		/* Append to buffer value part */
		EDIntToBits (Buffer, (CurrOfs+4), Source->ApduId, 4);
		Len = 4;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:261> Error encoding subfield ApduId\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ApduFlags */
	{
		/* Append to buffer value part */
		EDIntToBits (Buffer, (CurrOfs-4), Source->ApduFlags, 4);
		Len = 4;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:262> Error encoding subfield ApduFlags\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ApduData */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part */
		EDCopyBits (Buffer, CurrOfs+8, Source->ApduData.value, 0, Source->ApduData.usedBits);
		Len = Source->ApduData.usedBits;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:263> Error encoding subfield ApduData\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, TLV_Base, (CurrOfs - TLV_Base - 8) >> 3, 8);
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE APPLICATION_INFORMATION
-----------------------------------------------------------------*/
long ENCODE_c_APPLICATION_INFORMATION (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_APPLICATION_INFORMATION* ED_CONST Source)
{
	return L3_ENCODE_c_APPLICATION_INFORMATION (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE APPLICATION_INFORMATION
-----------------------------------------------------------------*/
long ENCODE_BODY_c_APPLICATION_INFORMATION (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_APPLICATION_INFORMATION* ED_CONST Source)
{
	return L3_ENCODE_c_APPLICATION_INFORMATION (Buffer, BitOffset, Source, 1);
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE APPLICATION_INFORMATION
-----------------------------------------------------------------*/
long DECODE_c_APPLICATION_INFORMATION (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_APPLICATION_INFORMATION* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_APPLICATION_INFORMATION (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE APPLICATION_INFORMATION
-----------------------------------------------------------------*/
long DECODE_BODY_c_APPLICATION_INFORMATION (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_APPLICATION_INFORMATION* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE ApduId
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part */
	Destin->ApduId = EDBitsToInt (Buffer, (CurrOfs+4), 4);
	RetLen = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:264> Error decoding subfield ApduId\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 264, (Destin->ApduId));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:265> Message too short decoding subfield ApduId\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 264, (Destin->ApduId));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ApduFlags
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part */
	Destin->ApduFlags = EDBitsToInt (Buffer, (CurrOfs-4), 4);
	RetLen = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:266> Error decoding subfield ApduFlags\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 266, (Destin->ApduFlags));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:267> Message too short decoding subfield ApduFlags\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 266, (Destin->ApduFlags));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ApduData
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if ((Len < 8) || (Len > 1976)) {
		ED_SIGNAL_ERROR ("<ERRID:268> Size error decoding IE ApduData\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 268, (Destin->ApduData), (Destin->ApduData_Present))
	} 
#endif
	/* Read value part */
	ALLOC_c_APPLICATION_INFORMATION_ApduData (&(Destin->ApduData), Len);
	EDCopyBits (Destin->ApduData.value, 0, Buffer, CurrOfs, Len);
	Destin->ApduData.usedBits = Len;RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:269> Error decoding subfield ApduData\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 269, (Destin->ApduData));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:270> Message too short decoding subfield ApduData\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 269, (Destin->ApduData));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
int Match_c_ASSIGNMENT_COMMAND (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 46) /* message type */
	);
}

int Match_c_CHANNEL_MODE_MODIFY (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 16) /* message type */
	);
}

int Match_c_CHANNEL_RELEASE (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 13) /* message type */
	);
}

int Match_c_CIPHERING_MODE_COMMAND (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 53) /* message type */
	);
}

int Match_c_CLASSMARK_ENQUIRY (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 19) /* message type */
	);
}

int Match_c_FREQUENCY_REDEFINITION (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 20) /* message type */
	);
}

int Match_c_HANDOVER_COMMAND (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 43) /* message type */
	);
}

int Match_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 99) /* message type */
	);
}

int Match_c_PHYSICAL_INFORMATION (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 45) /* message type */
	);
}

int Match_c_RR_STATUS (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 18) /* message type */
	);
}

int Match_c_APPLICATION_INFORMATION (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 56) /* message type */
	);
}

/*lint +e958*/
/*lint +e961*/
/*lint +e527*/
/*lint +e701*/
/*lint +e704*/
/*lint +e734*/
/*lint +e774*/

