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
		ED_SIGNAL_ERROR ("<ERRID:296> Error decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 296, (Destin->PageMode));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:297> Message too short decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 296, (Destin->PageMode));
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
		ED_SIGNAL_ERROR ("<ERRID:298> Error decoding subfield DedicatedModeOrTbf\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 298, (Destin->DedicatedModeOrTbf));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:299> Message too short decoding subfield DedicatedModeOrTbf\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 298, (Destin->DedicatedModeOrTbf));
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
			ED_SIGNAL_ERROR ("<ERRID:300> Error decoding subfield ChannelDescription\n");
			ED_HANDLE_CONDITIONAL_IE_SYNTAX_ERROR ((-1), 300, (Destin->ChannelDescription), (Destin->ChannelDescription_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:301> Message too short decoding subfield ChannelDescription\n");
			ED_HANDLE_CONDITIONAL_IE_MSG_TOO_SHORT ((-1), 300, (Destin->ChannelDescription), (Destin->ChannelDescription_Present));
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
			ED_SIGNAL_ERROR ("<ERRID:302> Error decoding subfield PacketChannelDescription\n");
			ED_HANDLE_CONDITIONAL_IE_SYNTAX_ERROR ((-1), 302, (Destin->PacketChannelDescription), (Destin->PacketChannelDescription_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:303> Message too short decoding subfield PacketChannelDescription\n");
			ED_HANDLE_CONDITIONAL_IE_MSG_TOO_SHORT ((-1), 302, (Destin->PacketChannelDescription), (Destin->PacketChannelDescription_Present));
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
		ED_SIGNAL_ERROR ("<ERRID:304> Error decoding subfield ReqRef\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 304, (Destin->ReqRef));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:305> Message too short decoding subfield ReqRef\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 304, (Destin->ReqRef));
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
		ED_SIGNAL_ERROR ("<ERRID:306> Error decoding subfield TimingAdvance\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 306, (Destin->TimingAdvance));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:307> Message too short decoding subfield TimingAdvance\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 306, (Destin->TimingAdvance));
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
		ED_SIGNAL_ERROR ("<ERRID:308> Size error decoding IE MobileAllocation\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 308, (Destin->MobileAllocation), (Destin->MobileAllocation_Present))
	} 
#endif
	/* Read value part */
	RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, &(Destin->MobileAllocation), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:309> Error decoding subfield MobileAllocation\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 309, (Destin->MobileAllocation));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:310> Message too short decoding subfield MobileAllocation\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 309, (Destin->MobileAllocation));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE StartingTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x7C */
	ED_EXPECT_OPTIONAL_IE (0x7C,  8, 311, 7, KnownL3IEs)
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
			ED_SIGNAL_ERROR ("<ERRID:312> Error decoding subfield StartingTime\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x7C, 312, (Destin->StartingTime), (Destin->StartingTime_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:313> Message too short decoding subfield StartingTime\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x7C, 312, (Destin->StartingTime), (Destin->StartingTime_Present));
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
		ED_SIGNAL_ERROR ("<ERRID:314> Error decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 314, (Destin->EndOfL2Length));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:315> Message too short decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 314, (Destin->EndOfL2Length));
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
		ED_SIGNAL_ERROR ("<ERRID:316> Error decoding subfield IaRestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 316, (Destin->IaRestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:317> Message too short decoding subfield IaRestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 316, (Destin->IaRestOctets));
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
		ED_SIGNAL_ERROR ("<ERRID:318> Error decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 318, (Destin->PageMode));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:319> Message too short decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 318, (Destin->PageMode));
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
		ED_SIGNAL_ERROR ("<ERRID:320> Error decoding subfield SpareHalfOctet\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 320, (Destin->SpareHalfOctet));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:321> Message too short decoding subfield SpareHalfOctet\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 320, (Destin->SpareHalfOctet));
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
		ED_SIGNAL_ERROR ("<ERRID:322> Error decoding subfield ChannelDescription1\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 322, (Destin->ChannelDescription1));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:323> Message too short decoding subfield ChannelDescription1\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 322, (Destin->ChannelDescription1));
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
		ED_SIGNAL_ERROR ("<ERRID:324> Error decoding subfield ReqRef1\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 324, (Destin->ReqRef1));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:325> Message too short decoding subfield ReqRef1\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 324, (Destin->ReqRef1));
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
		ED_SIGNAL_ERROR ("<ERRID:326> Error decoding subfield TimingAdvance1\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 326, (Destin->TimingAdvance1));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:327> Message too short decoding subfield TimingAdvance1\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 326, (Destin->TimingAdvance1));
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
		ED_SIGNAL_ERROR ("<ERRID:328> Error decoding subfield ChannelDescription2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 328, (Destin->ChannelDescription2));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:329> Message too short decoding subfield ChannelDescription2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 328, (Destin->ChannelDescription2));
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
		ED_SIGNAL_ERROR ("<ERRID:330> Error decoding subfield ReqRef2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 330, (Destin->ReqRef2));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:331> Message too short decoding subfield ReqRef2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 330, (Destin->ReqRef2));
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
		ED_SIGNAL_ERROR ("<ERRID:332> Error decoding subfield TimingAdvance2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 332, (Destin->TimingAdvance2));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:333> Message too short decoding subfield TimingAdvance2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 332, (Destin->TimingAdvance2));
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
		ED_SIGNAL_ERROR ("<ERRID:334> Size error decoding IE MobileAllocation\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 334, (Destin->MobileAllocation), (Destin->MobileAllocation_Present))
	} 
#endif
	/* Read value part */
	RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, &(Destin->MobileAllocation), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:335> Error decoding subfield MobileAllocation\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 335, (Destin->MobileAllocation));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:336> Message too short decoding subfield MobileAllocation\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 335, (Destin->MobileAllocation));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE StartingTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x7C */
	ED_EXPECT_OPTIONAL_IE (0x7C,  8, 337, 9, KnownL3IEs)
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
			ED_SIGNAL_ERROR ("<ERRID:338> Error decoding subfield StartingTime\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x7C, 338, (Destin->StartingTime), (Destin->StartingTime_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:339> Message too short decoding subfield StartingTime\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x7C, 338, (Destin->StartingTime), (Destin->StartingTime_Present));
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
		ED_SIGNAL_ERROR ("<ERRID:340> Error decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 340, (Destin->EndOfL2Length));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:341> Message too short decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 340, (Destin->EndOfL2Length));
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
		ED_SIGNAL_ERROR ("<ERRID:342> Error decoding subfield IaxRestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 342, (Destin->IaxRestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:343> Message too short decoding subfield IaxRestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 342, (Destin->IaxRestOctets));
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
		ED_SIGNAL_ERROR ("<ERRID:344> Error decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 344, (Destin->PageMode));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:345> Message too short decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 344, (Destin->PageMode));
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
		ED_SIGNAL_ERROR ("<ERRID:346> Error decoding subfield SpareHalfOctet\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 346, (Destin->SpareHalfOctet));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:347> Message too short decoding subfield SpareHalfOctet\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 346, (Destin->SpareHalfOctet));
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
		ED_SIGNAL_ERROR ("<ERRID:348> Error decoding subfield ReqRef1\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 348, (Destin->ReqRef1));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:349> Message too short decoding subfield ReqRef1\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 348, (Destin->ReqRef1));
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
		ED_SIGNAL_ERROR ("<ERRID:350> Error decoding subfield WaitIndication1\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 350, (Destin->WaitIndication1));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:351> Message too short decoding subfield WaitIndication1\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 350, (Destin->WaitIndication1));
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
		ED_SIGNAL_ERROR ("<ERRID:352> Error decoding subfield ReqRef2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 352, (Destin->ReqRef2));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:353> Message too short decoding subfield ReqRef2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 352, (Destin->ReqRef2));
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
		ED_SIGNAL_ERROR ("<ERRID:354> Error decoding subfield WaitIndication2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 354, (Destin->WaitIndication2));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:355> Message too short decoding subfield WaitIndication2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 354, (Destin->WaitIndication2));
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
		ED_SIGNAL_ERROR ("<ERRID:356> Error decoding subfield ReqRef3\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 356, (Destin->ReqRef3));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:357> Message too short decoding subfield ReqRef3\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 356, (Destin->ReqRef3));
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
		ED_SIGNAL_ERROR ("<ERRID:358> Error decoding subfield WaitIndication3\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 358, (Destin->WaitIndication3));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:359> Message too short decoding subfield WaitIndication3\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 358, (Destin->WaitIndication3));
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
		ED_SIGNAL_ERROR ("<ERRID:360> Error decoding subfield ReqRef4\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 360, (Destin->ReqRef4));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:361> Message too short decoding subfield ReqRef4\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 360, (Destin->ReqRef4));
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
		ED_SIGNAL_ERROR ("<ERRID:362> Error decoding subfield WaitIndication4\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 362, (Destin->WaitIndication4));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:363> Message too short decoding subfield WaitIndication4\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 362, (Destin->WaitIndication4));
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
		ED_SIGNAL_ERROR ("<ERRID:364> Error decoding subfield IarRestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 364, (Destin->IarRestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:365> Message too short decoding subfield IarRestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 364, (Destin->IarRestOctets));
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
		ED_SIGNAL_ERROR ("<ERRID:366> Error decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 366, (Destin->PageMode));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:367> Message too short decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 366, (Destin->PageMode));
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
		ED_SIGNAL_ERROR ("<ERRID:368> Error decoding subfield ChannelsNeededForMobiles1And2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 368, (Destin->ChannelsNeededForMobiles1And2));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:369> Message too short decoding subfield ChannelsNeededForMobiles1And2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 368, (Destin->ChannelsNeededForMobiles1And2));
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
		ED_SIGNAL_ERROR ("<ERRID:370> Size error decoding IE MobileId1\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 370, (Destin->MobileId1), (Destin->MobileId1_Present))
	} 
#endif
	/* Read value part */
	RetLen = DECODE_c_MobileId (Buffer, CurrOfs, &(Destin->MobileId1), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:371> Error decoding subfield MobileId1\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 371, (Destin->MobileId1));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:372> Message too short decoding subfield MobileId1\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 371, (Destin->MobileId1));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileId2
	------------------------------------------------------*/
	/* Detect IEI tag 0x17 */
	ED_EXPECT_OPTIONAL_IE (0x17,  8, 373, 3, KnownL3IEs)
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
			ED_SIGNAL_ERROR ("<ERRID:374> Size error decoding IE MobileId2\n");
			ED_HANDLE_IE_SIZE_ERROR (0x17, 374, (Destin->MobileId2), (Destin->MobileId2_Present))
		} 
#endif
		/* Read value part */
		RetLen = DECODE_c_MobileId (Buffer, CurrOfs, &(Destin->MobileId2), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:375> Error decoding subfield MobileId2\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x17, 375, (Destin->MobileId2), (Destin->MobileId2_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:376> Message too short decoding subfield MobileId2\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x17, 375, (Destin->MobileId2), (Destin->MobileId2_Present));
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
		ED_SIGNAL_ERROR ("<ERRID:377> Error decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 377, (Destin->EndOfL2Length));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:378> Message too short decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 377, (Destin->EndOfL2Length));
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
		ED_SIGNAL_ERROR ("<ERRID:379> Error decoding subfield P1RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 379, (Destin->P1RestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:380> Message too short decoding subfield P1RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 379, (Destin->P1RestOctets));
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
		ED_SIGNAL_ERROR ("<ERRID:381> Error decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 381, (Destin->PageMode));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:382> Message too short decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 381, (Destin->PageMode));
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
		ED_SIGNAL_ERROR ("<ERRID:383> Error decoding subfield ChannelsNeededForMobiles1And2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 383, (Destin->ChannelsNeededForMobiles1And2));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:384> Message too short decoding subfield ChannelsNeededForMobiles1And2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 383, (Destin->ChannelsNeededForMobiles1And2));
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
		ED_SIGNAL_ERROR ("<ERRID:385> Error decoding subfield MobileId1\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 385, (Destin->MobileId1));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:386> Message too short decoding subfield MobileId1\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 385, (Destin->MobileId1));
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
		ED_SIGNAL_ERROR ("<ERRID:387> Error decoding subfield MobileId2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 387, (Destin->MobileId2));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:388> Message too short decoding subfield MobileId2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 387, (Destin->MobileId2));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileId3
	------------------------------------------------------*/
	/* Detect IEI tag 0x17 */
	ED_EXPECT_OPTIONAL_IE (0x17,  8, 389, 4, KnownL3IEs)
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
			ED_SIGNAL_ERROR ("<ERRID:390> Size error decoding IE MobileId3\n");
			ED_HANDLE_IE_SIZE_ERROR (0x17, 390, (Destin->MobileId3), (Destin->MobileId3_Present))
		} 
#endif
		/* Read value part */
		RetLen = DECODE_c_MobileId (Buffer, CurrOfs, &(Destin->MobileId3), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:391> Error decoding subfield MobileId3\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x17, 391, (Destin->MobileId3), (Destin->MobileId3_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:392> Message too short decoding subfield MobileId3\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x17, 391, (Destin->MobileId3), (Destin->MobileId3_Present));
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
		ED_SIGNAL_ERROR ("<ERRID:393> Error decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 393, (Destin->EndOfL2Length));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:394> Message too short decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 393, (Destin->EndOfL2Length));
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
		ED_SIGNAL_ERROR ("<ERRID:395> Error decoding subfield P2RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 395, (Destin->P2RestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:396> Message too short decoding subfield P2RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 395, (Destin->P2RestOctets));
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
		ED_SIGNAL_ERROR ("<ERRID:397> Error decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 397, (Destin->PageMode));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:398> Message too short decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 397, (Destin->PageMode));
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
		ED_SIGNAL_ERROR ("<ERRID:399> Error decoding subfield ChannelsNeededForMobiles1And2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 399, (Destin->ChannelsNeededForMobiles1And2));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:400> Message too short decoding subfield ChannelsNeededForMobiles1And2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 399, (Destin->ChannelsNeededForMobiles1And2));
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
		ED_SIGNAL_ERROR ("<ERRID:401> Error decoding subfield MobileId1\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 401, (Destin->MobileId1));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:402> Message too short decoding subfield MobileId1\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 401, (Destin->MobileId1));
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
		ED_SIGNAL_ERROR ("<ERRID:403> Error decoding subfield MobileId2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 403, (Destin->MobileId2));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:404> Message too short decoding subfield MobileId2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 403, (Destin->MobileId2));
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
		ED_SIGNAL_ERROR ("<ERRID:405> Error decoding subfield MobileId3\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 405, (Destin->MobileId3));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:406> Message too short decoding subfield MobileId3\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 405, (Destin->MobileId3));
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
		ED_SIGNAL_ERROR ("<ERRID:407> Error decoding subfield MobileId4\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 407, (Destin->MobileId4));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:408> Message too short decoding subfield MobileId4\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 407, (Destin->MobileId4));
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
		ED_SIGNAL_ERROR ("<ERRID:409> Error decoding subfield P3RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 409, (Destin->P3RestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:410> Message too short decoding subfield P3RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 409, (Destin->P3RestOctets));
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
		ED_SIGNAL_ERROR ("<ERRID:411> Error decoding subfield CellChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 411, (Destin->CellChannelDescription));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:412> Message too short decoding subfield CellChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 411, (Destin->CellChannelDescription));
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
		ED_SIGNAL_ERROR ("<ERRID:413> Error decoding subfield RachControlParam\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 413, (Destin->RachControlParam));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:414> Message too short decoding subfield RachControlParam\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 413, (Destin->RachControlParam));
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
		ED_SIGNAL_ERROR ("<ERRID:415> Error decoding subfield Si1RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 415, (Destin->Si1RestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:416> Message too short decoding subfield Si1RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 415, (Destin->Si1RestOctets));
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
		ED_SIGNAL_ERROR ("<ERRID:417> Error decoding subfield BcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 417, (Destin->BcchFrequencyList));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:418> Message too short decoding subfield BcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 417, (Destin->BcchFrequencyList));
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
		ED_SIGNAL_ERROR ("<ERRID:419> Error decoding subfield NccPermitted\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 419, (Destin->NccPermitted));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:420> Message too short decoding subfield NccPermitted\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 419, (Destin->NccPermitted));
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
		ED_SIGNAL_ERROR ("<ERRID:421> Error decoding subfield RachControlParam\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 421, (Destin->RachControlParam));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:422> Message too short decoding subfield RachControlParam\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 421, (Destin->RachControlParam));
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
		ED_SIGNAL_ERROR ("<ERRID:423> Error decoding subfield ExtendedBcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 423, (Destin->ExtendedBcchFrequencyList));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:424> Message too short decoding subfield ExtendedBcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 423, (Destin->ExtendedBcchFrequencyList));
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
		ED_SIGNAL_ERROR ("<ERRID:425> Error decoding subfield RachControlParameters\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 425, (Destin->RachControlParameters));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:426> Message too short decoding subfield RachControlParameters\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 425, (Destin->RachControlParameters));
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
		ED_SIGNAL_ERROR ("<ERRID:427> Error decoding subfield Si2bisRestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 427, (Destin->Si2bisRestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:428> Message too short decoding subfield Si2bisRestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 427, (Destin->Si2bisRestOctets));
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
		ED_SIGNAL_ERROR ("<ERRID:429> Error decoding subfield ExtendedBcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 429, (Destin->ExtendedBcchFrequencyList));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:430> Message too short decoding subfield ExtendedBcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 429, (Destin->ExtendedBcchFrequencyList));
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
		ED_SIGNAL_ERROR ("<ERRID:431> Error decoding subfield Si2terRestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 431, (Destin->Si2terRestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:432> Message too short decoding subfield Si2terRestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 431, (Destin->Si2terRestOctets));
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
		ED_SIGNAL_ERROR ("<ERRID:433> Error decoding subfield Si2QuaterRestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 433, (Destin->Si2QuaterRestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:434> Message too short decoding subfield Si2QuaterRestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 433, (Destin->Si2QuaterRestOctets));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2N
-----------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_2N (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_2N* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2N (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2N
-----------------------------------------------------------------*/
long DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2N (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_2N* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE Si2nRestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 160;
	/* Read value part */
	RetLen = DECODE_c_SI2nRestOctets (Buffer, CurrOfs, &(Destin->Si2nRestOctets), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:435> Error decoding subfield Si2nRestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 435, (Destin->Si2nRestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:436> Message too short decoding subfield Si2nRestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 435, (Destin->Si2nRestOctets));
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
		ED_SIGNAL_ERROR ("<ERRID:437> Error decoding subfield CellId\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 437, (Destin->CellId));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:438> Message too short decoding subfield CellId\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 437, (Destin->CellId));
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
		ED_SIGNAL_ERROR ("<ERRID:439> Error decoding subfield LocationAreaId\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 439, (Destin->LocationAreaId));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:440> Message too short decoding subfield LocationAreaId\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 439, (Destin->LocationAreaId));
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
		ED_SIGNAL_ERROR ("<ERRID:441> Error decoding subfield ControlChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 441, (Destin->ControlChannelDescription));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:442> Message too short decoding subfield ControlChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 441, (Destin->ControlChannelDescription));
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
		ED_SIGNAL_ERROR ("<ERRID:443> Error decoding subfield CellOpt\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 443, (Destin->CellOpt));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:444> Message too short decoding subfield CellOpt\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 443, (Destin->CellOpt));
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
		ED_SIGNAL_ERROR ("<ERRID:445> Error decoding subfield CellSelectionParameters\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 445, (Destin->CellSelectionParameters));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:446> Message too short decoding subfield CellSelectionParameters\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 445, (Destin->CellSelectionParameters));
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
		ED_SIGNAL_ERROR ("<ERRID:447> Error decoding subfield RachControlParameters\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 447, (Destin->RachControlParameters));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:448> Message too short decoding subfield RachControlParameters\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 447, (Destin->RachControlParameters));
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
		ED_SIGNAL_ERROR ("<ERRID:449> Error decoding subfield Si3RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 449, (Destin->Si3RestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:450> Message too short decoding subfield Si3RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 449, (Destin->Si3RestOctets));
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
		ED_SIGNAL_ERROR ("<ERRID:451> Error decoding subfield LocationAreaId\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 451, (Destin->LocationAreaId));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:452> Message too short decoding subfield LocationAreaId\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 451, (Destin->LocationAreaId));
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
		ED_SIGNAL_ERROR ("<ERRID:453> Error decoding subfield CellSelectionParameters\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 453, (Destin->CellSelectionParameters));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:454> Message too short decoding subfield CellSelectionParameters\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 453, (Destin->CellSelectionParameters));
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
		ED_SIGNAL_ERROR ("<ERRID:455> Error decoding subfield RachControlParameters\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 455, (Destin->RachControlParameters));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:456> Message too short decoding subfield RachControlParameters\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 455, (Destin->RachControlParameters));
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE CbchChannelDescription
	------------------------------------------------------*/
	/* Detect IEI tag 0x64 */
	ED_EXPECT_OPTIONAL_IE (0x64,  8, 457, 3, KnownL3IEs)
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
			ED_SIGNAL_ERROR ("<ERRID:458> Error decoding subfield CbchChannelDescription\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x64, 458, (Destin->CbchChannelDescription), (Destin->CbchChannelDescription_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:459> Message too short decoding subfield CbchChannelDescription\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x64, 458, (Destin->CbchChannelDescription), (Destin->CbchChannelDescription_Present));
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE CbchMobileAllocation
	------------------------------------------------------*/
	/* Detect IEI tag 0x72 */
	ED_EXPECT_OPTIONAL_IE (0x72,  8, 460, 4, KnownL3IEs)
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
			ED_SIGNAL_ERROR ("<ERRID:461> Size error decoding IE CbchMobileAllocation\n");
			ED_HANDLE_IE_SIZE_ERROR (0x72, 461, (Destin->CbchMobileAllocation), (Destin->CbchMobileAllocation_Present))
		} 
#endif
		/* Read value part */
		RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, &(Destin->CbchMobileAllocation), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:462> Error decoding subfield CbchMobileAllocation\n");
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x72, 462, (Destin->CbchMobileAllocation), (Destin->CbchMobileAllocation_Present));
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:463> Message too short decoding subfield CbchMobileAllocation\n");
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x72, 462, (Destin->CbchMobileAllocation), (Destin->CbchMobileAllocation_Present));
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
		ED_SIGNAL_ERROR ("<ERRID:464> Error decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 464, (Destin->EndOfL2Length));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:465> Message too short decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 464, (Destin->EndOfL2Length));
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
		ED_SIGNAL_ERROR ("<ERRID:466> Error decoding subfield Si4RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 466, (Destin->Si4RestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:467> Message too short decoding subfield Si4RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 466, (Destin->Si4RestOctets));
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
		ED_SIGNAL_ERROR ("<ERRID:468> Error decoding subfield BcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 468, (Destin->BcchFrequencyList));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:469> Message too short decoding subfield BcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 468, (Destin->BcchFrequencyList));
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
		ED_SIGNAL_ERROR ("<ERRID:470> Error decoding subfield ExtOfTheBcchFrequencyListDescription\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 470, (Destin->ExtOfTheBcchFrequencyListDescription));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:471> Message too short decoding subfield ExtOfTheBcchFrequencyListDescription\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 470, (Destin->ExtOfTheBcchFrequencyListDescription));
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
		ED_SIGNAL_ERROR ("<ERRID:472> Error decoding subfield ExtendedBcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 472, (Destin->ExtendedBcchFrequencyList));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:473> Message too short decoding subfield ExtendedBcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 472, (Destin->ExtendedBcchFrequencyList));
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
		ED_SIGNAL_ERROR ("<ERRID:474> Error decoding subfield CellId\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 474, (Destin->CellId));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:475> Message too short decoding subfield CellId\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 474, (Destin->CellId));
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
		ED_SIGNAL_ERROR ("<ERRID:476> Error decoding subfield LocationAreaId\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 476, (Destin->LocationAreaId));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:477> Message too short decoding subfield LocationAreaId\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 476, (Destin->LocationAreaId));
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
		ED_SIGNAL_ERROR ("<ERRID:478> Error decoding subfield CellOpt\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 478, (Destin->CellOpt));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:479> Message too short decoding subfield CellOpt\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 478, (Destin->CellOpt));
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
		ED_SIGNAL_ERROR ("<ERRID:480> Error decoding subfield NccPermitted\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 480, (Destin->NccPermitted));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:481> Message too short decoding subfield NccPermitted\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 480, (Destin->NccPermitted));
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
		ED_SIGNAL_ERROR ("<ERRID:482> Error decoding subfield Si6RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 482, (Destin->Si6RestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:483> Message too short decoding subfield Si6RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 482, (Destin->Si6RestOctets));
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
		ED_SIGNAL_ERROR ("<ERRID:484> Error decoding subfield Si7RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 484, (Destin->Si7RestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:485> Message too short decoding subfield Si7RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 484, (Destin->Si7RestOctets));
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
		ED_SIGNAL_ERROR ("<ERRID:486> Error decoding subfield Si8RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 486, (Destin->Si8RestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:487> Message too short decoding subfield Si8RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 486, (Destin->Si8RestOctets));
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
		ED_SIGNAL_ERROR ("<ERRID:488> Error decoding subfield RachControlParam\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 488, (Destin->RachControlParam));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:489> Message too short decoding subfield RachControlParam\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 488, (Destin->RachControlParam));
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
		ED_SIGNAL_ERROR ("<ERRID:490> Error decoding subfield Si9RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 490, (Destin->Si9RestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:491> Message too short decoding subfield Si9RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 490, (Destin->Si9RestOctets));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_13
-----------------------------------------------------------------*/
long DECODE_c_SYSTEM_INFORMATION_TYPE_13 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SYSTEM_INFORMATION_TYPE_13* ED_CONST Destin, long Length)
{
    /* Added by f48555 for GSM_R6协议升级Phase2, 2010_02_08，begin */
    ED_LONG                                         ulRetVal;
    c_SI13RestOctets_NoPBCCH_GPRS_Cell_Options      *pstGprsCellOption;
    /* Added by f48555 for GSM_R6协议升级Phase2, 2010_02_08，end */
    int Len=0;
    
    Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_13 (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
    if (Len < 0) return Len;

    /* Added by f48555 for GSM_R6协议升级Phase2, 2010_02_08，begin */
    pstGprsCellOption   = &Destin->Si13RestOctets.NoPBCCH.GPRS_Cell_Options;
    ulRetVal            = GAS_ENCODIX_CheckGprsCellOptionExtVersion(pstGprsCellOption);
    
    if ( ED_FALSE == ulRetVal )
    {
        return (-1);
    }
    /* Added by f48555 for GSM_R6协议升级Phase2, 2010_02_08，end */
    
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
		ED_SIGNAL_ERROR ("<ERRID:492> Error decoding subfield Si13RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 492, (Destin->Si13RestOctets));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:493> Message too short decoding subfield Si13RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 492, (Destin->Si13RestOctets));
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE EXTENDED_MEASUREMENT_ORDER
-----------------------------------------------------------------*/
long DECODE_c_EXTENDED_MEASUREMENT_ORDER (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_EXTENDED_MEASUREMENT_ORDER* ED_CONST Destin, long Length)
{
	int Len=0;
	
	Len = DECODE_BODY_c_EXTENDED_MEASUREMENT_ORDER (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE EXTENDED_MEASUREMENT_ORDER
-----------------------------------------------------------------*/
long DECODE_BODY_c_EXTENDED_MEASUREMENT_ORDER (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_EXTENDED_MEASUREMENT_ORDER* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;


    /*------------------Code for SEQ-CODE Begin-------------*/
    Destin->SeqCode = (Buffer[BitOffset>>3] >> 4)& 0x01;
    /*----------------- Code for SEQ-CODE End---------------*/

	
	/*----------------------------------------------------- 
		Code for IE ExtendedMeasurementFrequencyList
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 128;
	/* Read value part */
	RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, &(Destin->ExtendedMeasurementFrequencyList), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:494> Error decoding subfield ExtendedMeasurementFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 494, (Destin->ExtendedMeasurementFrequencyList));
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:495> Message too short decoding subfield ExtendedMeasurementFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 494, (Destin->ExtendedMeasurementFrequencyList));
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

int Match_c_SYSTEM_INFORMATION_TYPE_2N (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 69) /* message type */
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

int Match_c_EXTENDED_MEASUREMENT_ORDER (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 55) /* message type */
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

