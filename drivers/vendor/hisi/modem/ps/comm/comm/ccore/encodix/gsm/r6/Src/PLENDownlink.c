/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.83
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#include "PLENDownlink.h"
#include "ed_c_known_ie.h"
#include "ed_tlv.h"
#include "UserDefinedDataTypes.h"
#include "CSN1DataTypes.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_PLENDOWNLINK_C
/*lint -e961*/
/*lint -e958*/
/*lint -e527*/
/*lint -e701*/
/*lint -e702*/
/*lint -e704*/
/*lint -e732*/
/*lint -e734*/
/*lint -e774*/


/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_ASSIGNMENT
-----------------------------------------------------------------*/
long DECODE_c_IMMEDIATE_ASSIGNMENT (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_IMMEDIATE_ASSIGNMENT* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_IMMEDIATE_ASSIGNMENT (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_ASSIGNMENT
-----------------------------------------------------------------*/
long DECODE_BODY_c_IMMEDIATE_ASSIGNMENT (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_IMMEDIATE_ASSIGNMENT* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Table containing the expected sequence of IEIs */
	const TEDTLVSkipItem TLVSkipItems [] = {
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_OPTIONAL}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_OPTIONAL}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{124, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	/* Stores condition result */
	int CondTrue;
	
	/*----------------------------------------------------- 
		Code for IE PageMode
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part */
	RetLen = DECODE_c_PageMode (Buffer, (CurrOfs+4), &(Destin->PageMode), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:291> Error decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 291, (Destin->PageMode));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:292> Message too short decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 291, (Destin->PageMode));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE DedicatedModeOrTbf
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part */
	RetLen = DECODE_c_DedicatedModeOrTBF4b (Buffer, (CurrOfs-4), &(Destin->DedicatedModeOrTbf), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:293> Error decoding subfield DedicatedModeOrTbf\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 293, (Destin->DedicatedModeOrTbf));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:294> Message too short decoding subfield DedicatedModeOrTbf\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 293, (Destin->DedicatedModeOrTbf));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ChannelDescription
	------------------------------------------------------*/
	
	/* This is a conditional untagged field */
#define ED_IS_DECODING
#define DATA (*Destin)
	CondTrue = (!DATA.DedicatedModeOrTbf.TD);
#undef DATA
	if (CondTrue) {
		SETPRESENT_c_IMMEDIATE_ASSIGNMENT_ChannelDescription (Destin, ED_TRUE);
		CurrOfs += 0;
		Len = 24;
		/* Read value part */
		RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, &(Destin->ChannelDescription), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:295> Error decoding subfield ChannelDescription\n");
			ED_HANDLE_CONDITIONAL_IE_SYNTAX_ERROR ((-1), 295, (Destin->ChannelDescription), (Destin->ChannelDescription_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:296> Message too short decoding subfield ChannelDescription\n");
			ED_HANDLE_CONDITIONAL_IE_MSG_TOO_SHORT ((-1), 295, (Destin->ChannelDescription), (Destin->ChannelDescription_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE PacketChannelDescription
	------------------------------------------------------*/
	
	/* This is a conditional untagged field */
#define ED_IS_DECODING
#define DATA (*Destin)
	CondTrue = (DATA.DedicatedModeOrTbf.TD);
#undef DATA
	if (CondTrue) {
		SETPRESENT_c_IMMEDIATE_ASSIGNMENT_PacketChannelDescription (Destin, ED_TRUE);
		CurrOfs += 0;
		Len = 24;
		/* Read value part */
		RetLen = DECODE_c_PacketChannelDescription (Buffer, CurrOfs, &(Destin->PacketChannelDescription), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:297> Error decoding subfield PacketChannelDescription\n");
			ED_HANDLE_CONDITIONAL_IE_SYNTAX_ERROR ((-1), 297, (Destin->PacketChannelDescription), (Destin->PacketChannelDescription_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:298> Message too short decoding subfield PacketChannelDescription\n");
			ED_HANDLE_CONDITIONAL_IE_MSG_TOO_SHORT ((-1), 297, (Destin->PacketChannelDescription), (Destin->PacketChannelDescription_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ReqRef
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part */
	RetLen = DECODE_c_RequestReference (Buffer, CurrOfs, &(Destin->ReqRef), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:299> Error decoding subfield ReqRef\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 299, (Destin->ReqRef));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:300> Message too short decoding subfield ReqRef\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 299, (Destin->ReqRef));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE TimingAdvance
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part */
	RetLen = DECODE_c_TimingAdvance (Buffer, CurrOfs, &(Destin->TimingAdvance), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:301> Error decoding subfield TimingAdvance\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 301, (Destin->TimingAdvance));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:302> Message too short decoding subfield TimingAdvance\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 301, (Destin->TimingAdvance));
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
		ED_SIGNAL_ERROR ("<ERRID:303> Size error decoding IE MobileAllocation\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 303, (Destin->MobileAllocation), (Destin->MobileAllocation_Present))
	} 
#endif
	/* Read value part */
	RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, &(Destin->MobileAllocation), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:304> Error decoding subfield MobileAllocation\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 304, (Destin->MobileAllocation));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:305> Message too short decoding subfield MobileAllocation\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 304, (Destin->MobileAllocation));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE StartingTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x7C */
	ED_EXPECT_OPTIONAL_IE (0x7C,  8, 306, 7, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x7C) {
		SETPRESENT_c_IMMEDIATE_ASSIGNMENT_StartingTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 16;
		/* Read value part */
		RetLen = DECODE_c_StartingTime (Buffer, CurrOfs, &(Destin->StartingTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:307> Error decoding subfield StartingTime\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x7C, 307, (Destin->StartingTime), (Destin->StartingTime_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:308> Message too short decoding subfield StartingTime\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x7C, 307, (Destin->StartingTime), (Destin->StartingTime_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE EndOfL2Length
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 0;
	/* Read value part */
	RetLen = 0;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:309> Error decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 309, (Destin->EndOfL2Length));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:310> Message too short decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 309, (Destin->EndOfL2Length));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE IaRestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_IARestOctets (Buffer, CurrOfs, &(Destin->IaRestOctets), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:311> Error decoding subfield IaRestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 311, (Destin->IaRestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:312> Message too short decoding subfield IaRestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 311, (Destin->IaRestOctets));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_ASSIGNMENT_EXTENDED
-----------------------------------------------------------------*/
long DECODE_c_IMMEDIATE_ASSIGNMENT_EXTENDED (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_IMMEDIATE_ASSIGNMENT_EXTENDED* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_IMMEDIATE_ASSIGNMENT_EXTENDED (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_ASSIGNMENT_EXTENDED
-----------------------------------------------------------------*/
long DECODE_BODY_c_IMMEDIATE_ASSIGNMENT_EXTENDED (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_IMMEDIATE_ASSIGNMENT_EXTENDED* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Table containing the expected sequence of IEIs */
	const TEDTLVSkipItem TLVSkipItems [] = {
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{124, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE PageMode
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part */
	RetLen = DECODE_c_PageMode (Buffer, (CurrOfs+4), &(Destin->PageMode), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:313> Error decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 313, (Destin->PageMode));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:314> Message too short decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 313, (Destin->PageMode));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE SpareHalfOctet
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part */
	RetLen = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:315> Error decoding subfield SpareHalfOctet\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 315, (Destin->SpareHalfOctet));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:316> Message too short decoding subfield SpareHalfOctet\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 315, (Destin->SpareHalfOctet));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ChannelDescription1
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part */
	RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, &(Destin->ChannelDescription1), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:317> Error decoding subfield ChannelDescription1\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 317, (Destin->ChannelDescription1));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:318> Message too short decoding subfield ChannelDescription1\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 317, (Destin->ChannelDescription1));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ReqRef1
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part */
	RetLen = DECODE_c_RequestReference (Buffer, CurrOfs, &(Destin->ReqRef1), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:319> Error decoding subfield ReqRef1\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 319, (Destin->ReqRef1));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:320> Message too short decoding subfield ReqRef1\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 319, (Destin->ReqRef1));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE TimingAdvance1
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part */
	RetLen = DECODE_c_TimingAdvance (Buffer, CurrOfs, &(Destin->TimingAdvance1), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:321> Error decoding subfield TimingAdvance1\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 321, (Destin->TimingAdvance1));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:322> Message too short decoding subfield TimingAdvance1\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 321, (Destin->TimingAdvance1));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ChannelDescription2
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part */
	RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, &(Destin->ChannelDescription2), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:323> Error decoding subfield ChannelDescription2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 323, (Destin->ChannelDescription2));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:324> Message too short decoding subfield ChannelDescription2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 323, (Destin->ChannelDescription2));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ReqRef2
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part */
	RetLen = DECODE_c_RequestReference (Buffer, CurrOfs, &(Destin->ReqRef2), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:325> Error decoding subfield ReqRef2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 325, (Destin->ReqRef2));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:326> Message too short decoding subfield ReqRef2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 325, (Destin->ReqRef2));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE TimingAdvance2
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part */
	RetLen = DECODE_c_TimingAdvance (Buffer, CurrOfs, &(Destin->TimingAdvance2), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:327> Error decoding subfield TimingAdvance2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 327, (Destin->TimingAdvance2));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:328> Message too short decoding subfield TimingAdvance2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 327, (Destin->TimingAdvance2));
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
	if (Len > 32) {
		ED_SIGNAL_ERROR ("<ERRID:329> Size error decoding IE MobileAllocation\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 329, (Destin->MobileAllocation), (Destin->MobileAllocation_Present))
	} 
#endif
	/* Read value part */
	RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, &(Destin->MobileAllocation), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:330> Error decoding subfield MobileAllocation\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 330, (Destin->MobileAllocation));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:331> Message too short decoding subfield MobileAllocation\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 330, (Destin->MobileAllocation));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE StartingTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x7C */
	ED_EXPECT_OPTIONAL_IE (0x7C,  8, 332, 9, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x7C) {
		SETPRESENT_c_IMMEDIATE_ASSIGNMENT_EXTENDED_StartingTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 16;
		/* Read value part */
		RetLen = DECODE_c_StartingTime (Buffer, CurrOfs, &(Destin->StartingTime), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:333> Error decoding subfield StartingTime\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x7C, 333, (Destin->StartingTime), (Destin->StartingTime_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:334> Message too short decoding subfield StartingTime\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x7C, 333, (Destin->StartingTime), (Destin->StartingTime_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE EndOfL2Length
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 0;
	/* Read value part */
	RetLen = 0;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:335> Error decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 335, (Destin->EndOfL2Length));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:336> Message too short decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 335, (Destin->EndOfL2Length));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE IaxRestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_IAXRestOctets (Buffer, CurrOfs, &(Destin->IaxRestOctets), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:337> Error decoding subfield IaxRestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 337, (Destin->IaxRestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:338> Message too short decoding subfield IaxRestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 337, (Destin->IaxRestOctets));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_ASSIGNMENT_REJECT
-----------------------------------------------------------------*/
long DECODE_c_IMMEDIATE_ASSIGNMENT_REJECT (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_IMMEDIATE_ASSIGNMENT_REJECT* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_IMMEDIATE_ASSIGNMENT_REJECT (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_ASSIGNMENT_REJECT
-----------------------------------------------------------------*/
long DECODE_BODY_c_IMMEDIATE_ASSIGNMENT_REJECT (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_IMMEDIATE_ASSIGNMENT_REJECT* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE PageMode
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part */
	RetLen = DECODE_c_PageMode (Buffer, (CurrOfs+4), &(Destin->PageMode), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:339> Error decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 339, (Destin->PageMode));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:340> Message too short decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 339, (Destin->PageMode));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE SpareHalfOctet
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part */
	RetLen = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:341> Error decoding subfield SpareHalfOctet\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 341, (Destin->SpareHalfOctet));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:342> Message too short decoding subfield SpareHalfOctet\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 341, (Destin->SpareHalfOctet));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ReqRef1
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part */
	RetLen = DECODE_c_RequestReference (Buffer, CurrOfs, &(Destin->ReqRef1), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:343> Error decoding subfield ReqRef1\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 343, (Destin->ReqRef1));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:344> Message too short decoding subfield ReqRef1\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 343, (Destin->ReqRef1));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE WaitIndication1
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part */
	Destin->WaitIndication1 = EDBitsToInt (Buffer, CurrOfs, 8);
	RetLen = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:345> Error decoding subfield WaitIndication1\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 345, (Destin->WaitIndication1));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:346> Message too short decoding subfield WaitIndication1\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 345, (Destin->WaitIndication1));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ReqRef2
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part */
	RetLen = DECODE_c_RequestReference (Buffer, CurrOfs, &(Destin->ReqRef2), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:347> Error decoding subfield ReqRef2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 347, (Destin->ReqRef2));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:348> Message too short decoding subfield ReqRef2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 347, (Destin->ReqRef2));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE WaitIndication2
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part */
	Destin->WaitIndication2 = EDBitsToInt (Buffer, CurrOfs, 8);
	RetLen = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:349> Error decoding subfield WaitIndication2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 349, (Destin->WaitIndication2));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:350> Message too short decoding subfield WaitIndication2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 349, (Destin->WaitIndication2));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ReqRef3
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part */
	RetLen = DECODE_c_RequestReference (Buffer, CurrOfs, &(Destin->ReqRef3), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:351> Error decoding subfield ReqRef3\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 351, (Destin->ReqRef3));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:352> Message too short decoding subfield ReqRef3\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 351, (Destin->ReqRef3));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE WaitIndication3
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part */
	Destin->WaitIndication3 = EDBitsToInt (Buffer, CurrOfs, 8);
	RetLen = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:353> Error decoding subfield WaitIndication3\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 353, (Destin->WaitIndication3));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:354> Message too short decoding subfield WaitIndication3\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 353, (Destin->WaitIndication3));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ReqRef4
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part */
	RetLen = DECODE_c_RequestReference (Buffer, CurrOfs, &(Destin->ReqRef4), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:355> Error decoding subfield ReqRef4\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 355, (Destin->ReqRef4));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:356> Message too short decoding subfield ReqRef4\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 355, (Destin->ReqRef4));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE WaitIndication4
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part */
	Destin->WaitIndication4 = EDBitsToInt (Buffer, CurrOfs, 8);
	RetLen = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:357> Error decoding subfield WaitIndication4\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 357, (Destin->WaitIndication4));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:358> Message too short decoding subfield WaitIndication4\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 357, (Destin->WaitIndication4));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE IarRestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part */
	RetLen = DECODE_c_IARRestOctets (Buffer, CurrOfs, &(Destin->IarRestOctets), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:359> Error decoding subfield IarRestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 359, (Destin->IarRestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:360> Message too short decoding subfield IarRestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 359, (Destin->IarRestOctets));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PAGING_REQUEST_TYPE_1
-----------------------------------------------------------------*/
long DECODE_c_PAGING_REQUEST_TYPE_1 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PAGING_REQUEST_TYPE_1* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_PAGING_REQUEST_TYPE_1 (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PAGING_REQUEST_TYPE_1
-----------------------------------------------------------------*/
long DECODE_BODY_c_PAGING_REQUEST_TYPE_1 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PAGING_REQUEST_TYPE_1* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Table containing the expected sequence of IEIs */
	const TEDTLVSkipItem TLVSkipItems [] = {
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{23, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE PageMode
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part */
	RetLen = DECODE_c_PageMode (Buffer, (CurrOfs+4), &(Destin->PageMode), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:361> Error decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 361, (Destin->PageMode));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:362> Message too short decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 361, (Destin->PageMode));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ChannelsNeededForMobiles1And2
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part */
	RetLen = DECODE_c_ChannelNeeded (Buffer, (CurrOfs-4), &(Destin->ChannelsNeededForMobiles1And2), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:363> Error decoding subfield ChannelsNeededForMobiles1And2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 363, (Destin->ChannelsNeededForMobiles1And2));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:364> Message too short decoding subfield ChannelsNeededForMobiles1And2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 363, (Destin->ChannelsNeededForMobiles1And2));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileId1
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if ((Len < 8) || (Len > 64)) {
		ED_SIGNAL_ERROR ("<ERRID:365> Size error decoding IE MobileId1\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 365, (Destin->MobileId1), (Destin->MobileId1_Present))
	} 
#endif
	/* Read value part */
	RetLen = DECODE_c_MobileId (Buffer, CurrOfs, &(Destin->MobileId1), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:366> Error decoding subfield MobileId1\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 366, (Destin->MobileId1));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:367> Message too short decoding subfield MobileId1\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 366, (Destin->MobileId1));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileId2
	------------------------------------------------------*/
	/* Detect IEI tag 0x17 */
	ED_EXPECT_OPTIONAL_IE (0x17,  8, 368, 3, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x17) {
		SETPRESENT_c_PAGING_REQUEST_TYPE_1_MobileId2 (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 64)) {
			ED_SIGNAL_ERROR ("<ERRID:369> Size error decoding IE MobileId2\n");
			ED_HANDLE_IE_SIZE_ERROR (0x17, 369, (Destin->MobileId2), (Destin->MobileId2_Present))
		} 
#endif
		/* Read value part */
		RetLen = DECODE_c_MobileId (Buffer, CurrOfs, &(Destin->MobileId2), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:370> Error decoding subfield MobileId2\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x17, 370, (Destin->MobileId2), (Destin->MobileId2_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:371> Message too short decoding subfield MobileId2\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x17, 370, (Destin->MobileId2), (Destin->MobileId2_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE EndOfL2Length
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 0;
	/* Read value part */
	RetLen = 0;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:372> Error decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 372, (Destin->EndOfL2Length));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:373> Message too short decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 372, (Destin->EndOfL2Length));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE P1RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_P1RestOctets (Buffer, CurrOfs, &(Destin->P1RestOctets), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:374> Error decoding subfield P1RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 374, (Destin->P1RestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:375> Message too short decoding subfield P1RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 374, (Destin->P1RestOctets));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PAGING_REQUEST_TYPE_2
-----------------------------------------------------------------*/
long DECODE_c_PAGING_REQUEST_TYPE_2 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PAGING_REQUEST_TYPE_2* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_PAGING_REQUEST_TYPE_2 (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PAGING_REQUEST_TYPE_2
-----------------------------------------------------------------*/
long DECODE_BODY_c_PAGING_REQUEST_TYPE_2 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PAGING_REQUEST_TYPE_2* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Table containing the expected sequence of IEIs */
	const TEDTLVSkipItem TLVSkipItems [] = {
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{23, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE PageMode
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part */
	RetLen = DECODE_c_PageMode (Buffer, (CurrOfs+4), &(Destin->PageMode), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:376> Error decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 376, (Destin->PageMode));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:377> Message too short decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 376, (Destin->PageMode));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ChannelsNeededForMobiles1And2
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part */
	RetLen = DECODE_c_ChannelNeeded (Buffer, (CurrOfs-4), &(Destin->ChannelsNeededForMobiles1And2), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:378> Error decoding subfield ChannelsNeededForMobiles1And2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 378, (Destin->ChannelsNeededForMobiles1And2));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:379> Message too short decoding subfield ChannelsNeededForMobiles1And2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 378, (Destin->ChannelsNeededForMobiles1And2));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileId1
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 32;
	/* Read value part */
	Destin->MobileId1 = EDBitsToInt (Buffer, CurrOfs, 32);
	RetLen = 32;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:380> Error decoding subfield MobileId1\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 380, (Destin->MobileId1));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:381> Message too short decoding subfield MobileId1\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 380, (Destin->MobileId1));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileId2
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 32;
	/* Read value part */
	Destin->MobileId2 = EDBitsToInt (Buffer, CurrOfs, 32);
	RetLen = 32;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:382> Error decoding subfield MobileId2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 382, (Destin->MobileId2));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:383> Message too short decoding subfield MobileId2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 382, (Destin->MobileId2));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileId3
	------------------------------------------------------*/
	/* Detect IEI tag 0x17 */
	ED_EXPECT_OPTIONAL_IE (0x17,  8, 384, 4, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x17) {
		SETPRESENT_c_PAGING_REQUEST_TYPE_2_MobileId3 (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 64)) {
			ED_SIGNAL_ERROR ("<ERRID:385> Size error decoding IE MobileId3\n");
			ED_HANDLE_IE_SIZE_ERROR (0x17, 385, (Destin->MobileId3), (Destin->MobileId3_Present))
		} 
#endif
		/* Read value part */
		RetLen = DECODE_c_MobileId (Buffer, CurrOfs, &(Destin->MobileId3), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:386> Error decoding subfield MobileId3\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x17, 386, (Destin->MobileId3), (Destin->MobileId3_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:387> Message too short decoding subfield MobileId3\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x17, 386, (Destin->MobileId3), (Destin->MobileId3_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE EndOfL2Length
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 0;
	/* Read value part */
	RetLen = 0;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:388> Error decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 388, (Destin->EndOfL2Length));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:389> Message too short decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 388, (Destin->EndOfL2Length));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE P2RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_P2RestOctets (Buffer, CurrOfs, &(Destin->P2RestOctets), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:390> Error decoding subfield P2RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 390, (Destin->P2RestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:391> Message too short decoding subfield P2RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 390, (Destin->P2RestOctets));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PAGING_REQUEST_TYPE_3
-----------------------------------------------------------------*/
long DECODE_c_PAGING_REQUEST_TYPE_3 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PAGING_REQUEST_TYPE_3* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_PAGING_REQUEST_TYPE_3 (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PAGING_REQUEST_TYPE_3
-----------------------------------------------------------------*/
long DECODE_BODY_c_PAGING_REQUEST_TYPE_3 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PAGING_REQUEST_TYPE_3* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE PageMode
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part */
	RetLen = DECODE_c_PageMode (Buffer, (CurrOfs+4), &(Destin->PageMode), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:392> Error decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 392, (Destin->PageMode));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:393> Message too short decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 392, (Destin->PageMode));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ChannelsNeededForMobiles1And2
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part */
	RetLen = DECODE_c_ChannelNeeded (Buffer, (CurrOfs-4), &(Destin->ChannelsNeededForMobiles1And2), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:394> Error decoding subfield ChannelsNeededForMobiles1And2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 394, (Destin->ChannelsNeededForMobiles1And2));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:395> Message too short decoding subfield ChannelsNeededForMobiles1And2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 394, (Destin->ChannelsNeededForMobiles1And2));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileId1
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 32;
	/* Read value part */
	Destin->MobileId1 = EDBitsToInt (Buffer, CurrOfs, 32);
	RetLen = 32;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:396> Error decoding subfield MobileId1\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 396, (Destin->MobileId1));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:397> Message too short decoding subfield MobileId1\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 396, (Destin->MobileId1));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileId2
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 32;
	/* Read value part */
	Destin->MobileId2 = EDBitsToInt (Buffer, CurrOfs, 32);
	RetLen = 32;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:398> Error decoding subfield MobileId2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 398, (Destin->MobileId2));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:399> Message too short decoding subfield MobileId2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 398, (Destin->MobileId2));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileId3
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 32;
	/* Read value part */
	Destin->MobileId3 = EDBitsToInt (Buffer, CurrOfs, 32);
	RetLen = 32;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:400> Error decoding subfield MobileId3\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 400, (Destin->MobileId3));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:401> Message too short decoding subfield MobileId3\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 400, (Destin->MobileId3));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileId4
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 32;
	/* Read value part */
	Destin->MobileId4 = EDBitsToInt (Buffer, CurrOfs, 32);
	RetLen = 32;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:402> Error decoding subfield MobileId4\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 402, (Destin->MobileId4));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:403> Message too short decoding subfield MobileId4\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 402, (Destin->MobileId4));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE P3RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part */
	RetLen = DECODE_c_P3RestOctets (Buffer, CurrOfs, &(Destin->P3RestOctets), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:404> Error decoding subfield P3RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 404, (Destin->P3RestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:405> Message too short decoding subfield P3RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 404, (Destin->P3RestOctets));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_1
-----------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_1 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_1* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_1 (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_1
-----------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_1 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_1* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE CellChannelDescription
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 128;
	/* Read value part */
	RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, &(Destin->CellChannelDescription), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:406> Error decoding subfield CellChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 406, (Destin->CellChannelDescription));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:407> Message too short decoding subfield CellChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 406, (Destin->CellChannelDescription));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE RachControlParam
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part */
	RetLen = DECODE_c_RACHCtrlParam (Buffer, CurrOfs, &(Destin->RachControlParam), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:408> Error decoding subfield RachControlParam\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 408, (Destin->RachControlParam));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:409> Message too short decoding subfield RachControlParam\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 408, (Destin->RachControlParam));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE Si1RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part */
	RetLen = DECODE_c_SI1RestOctets (Buffer, CurrOfs, &(Destin->Si1RestOctets), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:410> Error decoding subfield Si1RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 410, (Destin->Si1RestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:411> Message too short decoding subfield Si1RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 410, (Destin->Si1RestOctets));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2
-----------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_2 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_2* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2 (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2
-----------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_2* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE BcchFrequencyList
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 128;
	/* Read value part */
	RetLen = DECODE_c_NeighbourCellDescription (Buffer, CurrOfs, &(Destin->BcchFrequencyList), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:412> Error decoding subfield BcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 412, (Destin->BcchFrequencyList));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:413> Message too short decoding subfield BcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 412, (Destin->BcchFrequencyList));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE NccPermitted
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part */
	Destin->NccPermitted = EDBitsToInt (Buffer, CurrOfs, 8);
	RetLen = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:414> Error decoding subfield NccPermitted\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 414, (Destin->NccPermitted));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:415> Message too short decoding subfield NccPermitted\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 414, (Destin->NccPermitted));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE RachControlParam
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part */
	RetLen = DECODE_c_RACHCtrlParam (Buffer, CurrOfs, &(Destin->RachControlParam), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:416> Error decoding subfield RachControlParam\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 416, (Destin->RachControlParam));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:417> Message too short decoding subfield RachControlParam\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 416, (Destin->RachControlParam));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2BIS
-----------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_2BIS (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_2BIS* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2BIS (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2BIS
-----------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2BIS (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_2BIS* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE ExtendedBcchFrequencyList
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 128;
	/* Read value part */
	RetLen = DECODE_c_NeighbourCellDescription (Buffer, CurrOfs, &(Destin->ExtendedBcchFrequencyList), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:418> Error decoding subfield ExtendedBcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 418, (Destin->ExtendedBcchFrequencyList));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:419> Message too short decoding subfield ExtendedBcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 418, (Destin->ExtendedBcchFrequencyList));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE RachControlParameters
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part */
	RetLen = DECODE_c_RACHCtrlParam (Buffer, CurrOfs, &(Destin->RachControlParameters), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:420> Error decoding subfield RachControlParameters\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 420, (Destin->RachControlParameters));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:421> Message too short decoding subfield RachControlParameters\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 420, (Destin->RachControlParameters));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE Si2bisRestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part */
	RetLen = DECODE_c_SI2bisRestOctets (Buffer, CurrOfs, &(Destin->Si2bisRestOctets), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:422> Error decoding subfield Si2bisRestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 422, (Destin->Si2bisRestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:423> Message too short decoding subfield Si2bisRestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 422, (Destin->Si2bisRestOctets));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2TER
-----------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_2TER (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_2TER* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2TER (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2TER
-----------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2TER (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_2TER* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE ExtendedBcchFrequencyList
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 128;
	/* Read value part */
	RetLen = DECODE_c_NeighbourCellDescription2 (Buffer, CurrOfs, &(Destin->ExtendedBcchFrequencyList), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:424> Error decoding subfield ExtendedBcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 424, (Destin->ExtendedBcchFrequencyList));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:425> Message too short decoding subfield ExtendedBcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 424, (Destin->ExtendedBcchFrequencyList));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE Si2terRestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 32;
	/* Read value part */
	RetLen = DECODE_c_SI2terRestOctets (Buffer, CurrOfs, &(Destin->Si2terRestOctets), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:426> Error decoding subfield Si2terRestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 426, (Destin->Si2terRestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:427> Message too short decoding subfield Si2terRestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 426, (Destin->Si2terRestOctets));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2QUATER
-----------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_2QUATER (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_2QUATER* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2QUATER (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2QUATER
-----------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2QUATER (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_2QUATER* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE Si2QuaterRestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 160;
	/* Read value part */
	RetLen = DECODE_c_SI2quaterRestOctets (Buffer, CurrOfs, &(Destin->Si2QuaterRestOctets), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:428> Error decoding subfield Si2QuaterRestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 428, (Destin->Si2QuaterRestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:429> Message too short decoding subfield Si2QuaterRestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 428, (Destin->Si2QuaterRestOctets));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_3
-----------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_3 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_3* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_3 (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_3
-----------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_3 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_3* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE CellId
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 16;
	/* Read value part */
	Destin->CellId = EDBitsToInt (Buffer, CurrOfs, 16);
	RetLen = 16;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:430> Error decoding subfield CellId\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 430, (Destin->CellId));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:431> Message too short decoding subfield CellId\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 430, (Destin->CellId));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE LocationAreaId
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 40;
	/* Read value part */
	RetLen = DECODE_c_LocationAreaId (Buffer, CurrOfs, &(Destin->LocationAreaId), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:432> Error decoding subfield LocationAreaId\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 432, (Destin->LocationAreaId));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:433> Message too short decoding subfield LocationAreaId\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 432, (Destin->LocationAreaId));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ControlChannelDescription
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part */
	RetLen = DECODE_c_CtrlChannelDesc (Buffer, CurrOfs, &(Destin->ControlChannelDescription), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:434> Error decoding subfield ControlChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 434, (Destin->ControlChannelDescription));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:435> Message too short decoding subfield ControlChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 434, (Destin->ControlChannelDescription));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE CellOpt
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part */
	RetLen = DECODE_c_CellOptions (Buffer, CurrOfs, &(Destin->CellOpt), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:436> Error decoding subfield CellOpt\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 436, (Destin->CellOpt));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:437> Message too short decoding subfield CellOpt\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 436, (Destin->CellOpt));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE CellSelectionParameters
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 16;
	/* Read value part */
	RetLen = DECODE_c_CellSelParam (Buffer, CurrOfs, &(Destin->CellSelectionParameters), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:438> Error decoding subfield CellSelectionParameters\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 438, (Destin->CellSelectionParameters));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:439> Message too short decoding subfield CellSelectionParameters\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 438, (Destin->CellSelectionParameters));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE RachControlParameters
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part */
	RetLen = DECODE_c_RACHCtrlParam (Buffer, CurrOfs, &(Destin->RachControlParameters), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:440> Error decoding subfield RachControlParameters\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 440, (Destin->RachControlParameters));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:441> Message too short decoding subfield RachControlParameters\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 440, (Destin->RachControlParameters));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE Si3RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 32;
	/* Read value part */
	RetLen = DECODE_c_SI3RestOctet (Buffer, CurrOfs, &(Destin->Si3RestOctets), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:442> Error decoding subfield Si3RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 442, (Destin->Si3RestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:443> Message too short decoding subfield Si3RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 442, (Destin->Si3RestOctets));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_4
-----------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_4 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_4* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_4 (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_4
-----------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_4 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_4* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Table containing the expected sequence of IEIs */
	const TEDTLVSkipItem TLVSkipItems [] = {
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{100, 255, ED_SKIPLIST_OPTIONAL},
		{114, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE LocationAreaId
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 40;
	/* Read value part */
	RetLen = DECODE_c_LocationAreaId (Buffer, CurrOfs, &(Destin->LocationAreaId), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:444> Error decoding subfield LocationAreaId\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 444, (Destin->LocationAreaId));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:445> Message too short decoding subfield LocationAreaId\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 444, (Destin->LocationAreaId));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE CellSelectionParameters
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 16;
	/* Read value part */
	RetLen = DECODE_c_CellSelParam (Buffer, CurrOfs, &(Destin->CellSelectionParameters), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:446> Error decoding subfield CellSelectionParameters\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 446, (Destin->CellSelectionParameters));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:447> Message too short decoding subfield CellSelectionParameters\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 446, (Destin->CellSelectionParameters));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE RachControlParameters
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part */
	RetLen = DECODE_c_RACHCtrlParam (Buffer, CurrOfs, &(Destin->RachControlParameters), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:448> Error decoding subfield RachControlParameters\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 448, (Destin->RachControlParameters));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:449> Message too short decoding subfield RachControlParameters\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 448, (Destin->RachControlParameters));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE CbchChannelDescription
	------------------------------------------------------*/
	/* Detect IEI tag 0x64 */
	ED_EXPECT_OPTIONAL_IE (0x64,  8, 450, 3, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x64) {
		SETPRESENT_c_SYSTEM_INFORMATION_TYPE_4_CbchChannelDescription (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 24;
		/* Read value part */
		RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, &(Destin->CbchChannelDescription), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:451> Error decoding subfield CbchChannelDescription\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x64, 451, (Destin->CbchChannelDescription), (Destin->CbchChannelDescription_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:452> Message too short decoding subfield CbchChannelDescription\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x64, 451, (Destin->CbchChannelDescription), (Destin->CbchChannelDescription_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE CbchMobileAllocation
	------------------------------------------------------*/
	/* Detect IEI tag 0x72 */
	ED_EXPECT_OPTIONAL_IE (0x72,  8, 453, 4, KnownL3IEs)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x72) {
		SETPRESENT_c_SYSTEM_INFORMATION_TYPE_4_CbchMobileAllocation (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 32)) {
			ED_SIGNAL_ERROR ("<ERRID:454> Size error decoding IE CbchMobileAllocation\n");
			ED_HANDLE_IE_SIZE_ERROR (0x72, 454, (Destin->CbchMobileAllocation), (Destin->CbchMobileAllocation_Present))
		} 
#endif
		/* Read value part */
		RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, &(Destin->CbchMobileAllocation), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:455> Error decoding subfield CbchMobileAllocation\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x72, 455, (Destin->CbchMobileAllocation), (Destin->CbchMobileAllocation_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:456> Message too short decoding subfield CbchMobileAllocation\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x72, 455, (Destin->CbchMobileAllocation), (Destin->CbchMobileAllocation_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE EndOfL2Length
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 0;
	/* Read value part */
	RetLen = 0;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:457> Error decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 457, (Destin->EndOfL2Length));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:458> Message too short decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 457, (Destin->EndOfL2Length));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE Si4RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part */
	RetLen = DECODE_c_SI4RestOctet (Buffer, CurrOfs, &(Destin->Si4RestOctets), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:459> Error decoding subfield Si4RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 459, (Destin->Si4RestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:460> Message too short decoding subfield Si4RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 459, (Destin->Si4RestOctets));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_5
-----------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_5 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_5* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_5 (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_5
-----------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_5 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_5* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE BcchFrequencyList
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 128;
	/* Read value part */
	RetLen = DECODE_c_NeighbourCellDescription (Buffer, CurrOfs, &(Destin->BcchFrequencyList), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:461> Error decoding subfield BcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 461, (Destin->BcchFrequencyList));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:462> Message too short decoding subfield BcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 461, (Destin->BcchFrequencyList));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_5BIS
-----------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_5BIS (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_5BIS* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_5BIS (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_5BIS
-----------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_5BIS (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_5BIS* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE ExtOfTheBcchFrequencyListDescription
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 128;
	/* Read value part */
	RetLen = DECODE_c_NeighbourCellDescription (Buffer, CurrOfs, &(Destin->ExtOfTheBcchFrequencyListDescription), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:463> Error decoding subfield ExtOfTheBcchFrequencyListDescription\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 463, (Destin->ExtOfTheBcchFrequencyListDescription));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:464> Message too short decoding subfield ExtOfTheBcchFrequencyListDescription\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 463, (Destin->ExtOfTheBcchFrequencyListDescription));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_5TER
-----------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_5TER (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_5TER* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_5TER (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_5TER
-----------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_5TER (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_5TER* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE ExtendedBcchFrequencyList
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 128;
	/* Read value part */
	RetLen = DECODE_c_NeighbourCellDescription2 (Buffer, CurrOfs, &(Destin->ExtendedBcchFrequencyList), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:465> Error decoding subfield ExtendedBcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 465, (Destin->ExtendedBcchFrequencyList));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:466> Message too short decoding subfield ExtendedBcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 465, (Destin->ExtendedBcchFrequencyList));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_6
-----------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_6 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_6* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_6 (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_6
-----------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_6 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_6* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE CellId
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 16;
	/* Read value part */
	Destin->CellId = EDBitsToInt (Buffer, CurrOfs, 16);
	RetLen = 16;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:467> Error decoding subfield CellId\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 467, (Destin->CellId));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:468> Message too short decoding subfield CellId\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 467, (Destin->CellId));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE LocationAreaId
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 40;
	/* Read value part */
	RetLen = DECODE_c_LocationAreaId (Buffer, CurrOfs, &(Destin->LocationAreaId), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:469> Error decoding subfield LocationAreaId\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 469, (Destin->LocationAreaId));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:470> Message too short decoding subfield LocationAreaId\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 469, (Destin->LocationAreaId));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE CellOpt
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part */
	RetLen = DECODE_c_CellOptionsSacch (Buffer, CurrOfs, &(Destin->CellOpt), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:471> Error decoding subfield CellOpt\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 471, (Destin->CellOpt));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:472> Message too short decoding subfield CellOpt\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 471, (Destin->CellOpt));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE NccPermitted
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part */
	Destin->NccPermitted = EDBitsToInt (Buffer, CurrOfs, 8);
	RetLen = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:473> Error decoding subfield NccPermitted\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 473, (Destin->NccPermitted));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:474> Message too short decoding subfield NccPermitted\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 473, (Destin->NccPermitted));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE Si6RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 56;
	/* Read value part */
	RetLen = DECODE_c_SI6RestOctet (Buffer, CurrOfs, &(Destin->Si6RestOctets), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:475> Error decoding subfield Si6RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 475, (Destin->Si6RestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:476> Message too short decoding subfield Si6RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 475, (Destin->Si6RestOctets));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_7
-----------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_7 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_7* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_7 (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_7
-----------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_7 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_7* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE Si7RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 160;
	/* Read value part */
	RetLen = DECODE_c_SI4RestOctet (Buffer, CurrOfs, &(Destin->Si7RestOctets), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:477> Error decoding subfield Si7RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 477, (Destin->Si7RestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:478> Message too short decoding subfield Si7RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 477, (Destin->Si7RestOctets));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_8
-----------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_8 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_8* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_8 (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_8
-----------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_8 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_8* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE Si8RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 160;
	/* Read value part */
	RetLen = DECODE_c_SI4RestOctet (Buffer, CurrOfs, &(Destin->Si8RestOctets), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:479> Error decoding subfield Si8RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 479, (Destin->Si8RestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:480> Message too short decoding subfield Si8RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 479, (Destin->Si8RestOctets));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_9
-----------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_9 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_9* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_9 (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_9
-----------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_9 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_9* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE RachControlParam
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part */
	RetLen = DECODE_c_RACHCtrlParam (Buffer, CurrOfs, &(Destin->RachControlParam), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:481> Error decoding subfield RachControlParam\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 481, (Destin->RachControlParam));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:482> Message too short decoding subfield RachControlParam\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 481, (Destin->RachControlParam));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE Si9RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 136;
	/* Read value part */
	RetLen = DECODE_c_SI9RestOctet (Buffer, CurrOfs, &(Destin->Si9RestOctets), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:483> Error decoding subfield Si9RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 483, (Destin->Si9RestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:484> Message too short decoding subfield Si9RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 483, (Destin->Si9RestOctets));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_13
-----------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_13 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_13* ED_CONST Destin, long Length)
{
    /* Added by f48555 for GSM_R6D-òééy??Phase2, 2010_02_08￡?begin */
    ED_LONG                                         ulRetVal;
    c_SI13RestOctets_NoPBCCH_GPRS_Cell_Options      *pstGprsCellOption;
    /* Added by f48555 for GSM_R6D-òééy??Phase2, 2010_02_08￡?end */
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_13 (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
    /* Added by f48555 for GSM_R6D-òééy??Phase2, 2010_02_08￡?begin */
    pstGprsCellOption   = &Destin->Si13RestOctets.NoPBCCH.GPRS_Cell_Options;
    ulRetVal            = GAS_ENCODIX_CheckGprsCellOptionExtVersion(pstGprsCellOption);
    
    if ( ED_FALSE == ulRetVal )
    {
        return (-1);
    }
    /* Added by f48555 for GSM_R6D-òééy??Phase2, 2010_02_08￡?end */
    
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_13
-----------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_13 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_13* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE Si13RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 160;
	/* Read value part */
	RetLen = DECODE_c_SI13RestOctets (Buffer, CurrOfs, &(Destin->Si13RestOctets), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:485> Error decoding subfield Si13RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 485, (Destin->Si13RestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:486> Message too short decoding subfield Si13RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 485, (Destin->Si13RestOctets));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
int Match_c_IMMEDIATE_ASSIGNMENT (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 63) /* message type */
	);
}

int Match_c_IMMEDIATE_ASSIGNMENT_EXTENDED (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 57) /* message type */
	);
}

int Match_c_IMMEDIATE_ASSIGNMENT_REJECT (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 58) /* message type */
	);
}

int Match_c_PAGING_REQUEST_TYPE_1 (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 33) /* message type */
	);
}

int Match_c_PAGING_REQUEST_TYPE_2 (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 34) /* message type */
	);
}

int Match_c_PAGING_REQUEST_TYPE_3 (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 36) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_1 (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 25) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_2 (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 26) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_2BIS (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 2) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_2TER (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 3) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_2QUATER (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 7) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_3 (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 27) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_4 (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 28) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_5 (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 29) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_5BIS (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 5) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_5TER (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 6) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_6 (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 30) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_7 (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 31) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_8 (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 24) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_9 (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 4) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_13 (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 0) /* message type */
	);
}

/*lint +e958*/
/*lint +e961*/
/*lint +e527*/
/*lint +e701*/
/*lint +e702*/
/*lint +e704*/
/*lint +e732*/
/*lint +e734*/
/*lint +e774*/

