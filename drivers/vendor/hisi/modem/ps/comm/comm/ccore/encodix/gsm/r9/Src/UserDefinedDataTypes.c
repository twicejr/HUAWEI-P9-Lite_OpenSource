/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.83
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#include "UserDefinedDataTypes.h"
#include "ed_c_known_ie.h"
#include "ed_tlv.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_USERDEFINEDDATATYPES_C
/*lint -e961*/
/*lint -e958*/
/*lint -e539*/
/*lint -e830*/
/*lint -e717*/
/*lint -e574*/
/*lint -e701*/
/*lint -e702*/
/*lint -e525*/
/*lint -e704*/
/*lint -e713*/
/*lint -e732*/
/*lint -e734*/
/*lint -e774*/
/*lint -e737*/

/* Added by y00142674 for GSM编解码单编译, 2015-11-23, begin */
ENCODIX_GSM_SEM_STRU                    gstSemDesc;
/* Added by y00142674 for GSM编解码单编译, 2015-11-23, end */


long ENCODE_c_LocationAreaId (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_LocationAreaId* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 40;
	EDIntToBits (Buffer, CurrOfs, (*Source).MCC2, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:571> Error encoding subfield MCC2\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+4, (*Source).MCC1, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:572> Error encoding subfield MCC1\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+8, (*Source).MNC3, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:573> Error encoding subfield MNC3\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+12, (*Source).MCC3, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:574> Error encoding subfield MCC3\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+16, (*Source).MNC2, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:575> Error encoding subfield MNC2\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+20, (*Source).MNC1, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:576> Error encoding subfield MNC1\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+24, (*Source).LAC, 16);
	Ret = 16;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:577> Error encoding subfield LAC\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_LocationAreaId (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_LocationAreaId* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=0 */
	(*Destin).MCC2 = EDBitsToInt (Buffer, CurrOfs, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:578> Error decoding subfield MCC2\n");
		ED_HANDLE_IE_SYNTAX_ERROR (578)
	} 
#endif
	Len += Ret;
	
	/* FromBit=4 */
	(*Destin).MCC1 = EDBitsToInt (Buffer, CurrOfs+4, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:579> Error decoding subfield MCC1\n");
		ED_HANDLE_IE_SYNTAX_ERROR (579)
	} 
#endif
	Len += Ret;
	
	/* FromBit=8 */
	(*Destin).MNC3 = EDBitsToInt (Buffer, CurrOfs+8, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:580> Error decoding subfield MNC3\n");
		ED_HANDLE_IE_SYNTAX_ERROR (580)
	} 
#endif
	Len += Ret;
	
	/* FromBit=12 */
	(*Destin).MCC3 = EDBitsToInt (Buffer, CurrOfs+12, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:581> Error decoding subfield MCC3\n");
		ED_HANDLE_IE_SYNTAX_ERROR (581)
	} 
#endif
	Len += Ret;
	
	/* FromBit=16 */
	(*Destin).MNC2 = EDBitsToInt (Buffer, CurrOfs+16, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:582> Error decoding subfield MNC2\n");
		ED_HANDLE_IE_SYNTAX_ERROR (582)
	} 
#endif
	Len += Ret;
	
	/* FromBit=20 */
	(*Destin).MNC1 = EDBitsToInt (Buffer, CurrOfs+20, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:583> Error decoding subfield MNC1\n");
		ED_HANDLE_IE_SYNTAX_ERROR (583)
	} 
#endif
	Len += Ret;
	
	/* FromBit=24 */
	(*Destin).LAC = EDBitsToInt (Buffer, CurrOfs+24, 16);
	Ret = 16;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:584> Error decoding subfield LAC\n");
		ED_HANDLE_IE_SYNTAX_ERROR (584)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_MobileStationClassmark2 (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_MobileStationClassmark2* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 24;
	EDIntToBits (Buffer, CurrOfs, 0, 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:585> Error encoding subfield spare1\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+1, (*Source).RevisionLevel, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:586> Error encoding subfield RevisionLevel\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+3, ((*Source).EsInd != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:587> Error encoding subfield EsInd\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+4, ((*Source).A5_1 != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:588> Error encoding subfield A5_1\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+5, (*Source).RFPowerCapability, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:589> Error encoding subfield RFPowerCapability\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+8, 0, 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:590> Error encoding subfield spare2\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+9, ((*Source).PSCapability != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:591> Error encoding subfield PSCapability\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+10, (*Source).SSScreenIndicator, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:592> Error encoding subfield SSScreenIndicator\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+12, ((*Source).SMCapability != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:593> Error encoding subfield SMCapability\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+13, ((*Source).VBS != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:594> Error encoding subfield VBS\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+14, ((*Source).VGCS != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:595> Error encoding subfield VGCS\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+15, ((*Source).FC != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:596> Error encoding subfield FC\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+16, ((*Source).CM3 != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:597> Error encoding subfield CM3\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+17, 0, 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:598> Error encoding subfield spare3\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+18, ((*Source).LCSVA_CAP != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:599> Error encoding subfield LCSVA_CAP\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+19, ((*Source).UCS2 != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:600> Error encoding subfield UCS2\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+20, ((*Source).SoLSA != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:601> Error encoding subfield SoLSA\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+21, ((*Source).CMSP != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:602> Error encoding subfield CMSP\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+22, ((*Source).A5_3 != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:603> Error encoding subfield A5_3\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+23, ((*Source).A5_2 != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:604> Error encoding subfield A5_2\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_MobileStationClassmark2 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_MobileStationClassmark2* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=0 */
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:605> Error decoding subfield spare1\n");
		ED_HANDLE_IE_SYNTAX_ERROR (605)
	} 
#endif
	Len += Ret;
	
	/* FromBit=1 */
	(*Destin).RevisionLevel = EDBitsToInt (Buffer, CurrOfs+1, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:606> Error decoding subfield RevisionLevel\n");
		ED_HANDLE_IE_SYNTAX_ERROR (606)
	} 
#endif
	Len += Ret;
	
	/* FromBit=3 */
	(*Destin).EsInd = (EDBitsToInt (Buffer, CurrOfs+3, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:607> Error decoding subfield EsInd\n");
		ED_HANDLE_IE_SYNTAX_ERROR (607)
	} 
#endif
	Len += Ret;
	
	/* FromBit=4 */
	(*Destin).A5_1 = (EDBitsToInt (Buffer, CurrOfs+4, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:608> Error decoding subfield A5_1\n");
		ED_HANDLE_IE_SYNTAX_ERROR (608)
	} 
#endif
	Len += Ret;
	
	/* FromBit=5 */
	(*Destin).RFPowerCapability = EDBitsToInt (Buffer, CurrOfs+5, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:609> Error decoding subfield RFPowerCapability\n");
		ED_HANDLE_IE_SYNTAX_ERROR (609)
	} 
#endif
	Len += Ret;
	
	/* FromBit=8 */
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:610> Error decoding subfield spare2\n");
		ED_HANDLE_IE_SYNTAX_ERROR (610)
	} 
#endif
	Len += Ret;
	
	/* FromBit=9 */
	(*Destin).PSCapability = (EDBitsToInt (Buffer, CurrOfs+9, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:611> Error decoding subfield PSCapability\n");
		ED_HANDLE_IE_SYNTAX_ERROR (611)
	} 
#endif
	Len += Ret;
	
	/* FromBit=10 */
	(*Destin).SSScreenIndicator = EDBitsToInt (Buffer, CurrOfs+10, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:612> Error decoding subfield SSScreenIndicator\n");
		ED_HANDLE_IE_SYNTAX_ERROR (612)
	} 
#endif
	Len += Ret;
	
	/* FromBit=12 */
	(*Destin).SMCapability = (EDBitsToInt (Buffer, CurrOfs+12, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:613> Error decoding subfield SMCapability\n");
		ED_HANDLE_IE_SYNTAX_ERROR (613)
	} 
#endif
	Len += Ret;
	
	/* FromBit=13 */
	(*Destin).VBS = (EDBitsToInt (Buffer, CurrOfs+13, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:614> Error decoding subfield VBS\n");
		ED_HANDLE_IE_SYNTAX_ERROR (614)
	} 
#endif
	Len += Ret;
	
	/* FromBit=14 */
	(*Destin).VGCS = (EDBitsToInt (Buffer, CurrOfs+14, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:615> Error decoding subfield VGCS\n");
		ED_HANDLE_IE_SYNTAX_ERROR (615)
	} 
#endif
	Len += Ret;
	
	/* FromBit=15 */
	(*Destin).FC = (EDBitsToInt (Buffer, CurrOfs+15, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:616> Error decoding subfield FC\n");
		ED_HANDLE_IE_SYNTAX_ERROR (616)
	} 
#endif
	Len += Ret;
	
	/* FromBit=16 */
	(*Destin).CM3 = (EDBitsToInt (Buffer, CurrOfs+16, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:617> Error decoding subfield CM3\n");
		ED_HANDLE_IE_SYNTAX_ERROR (617)
	} 
#endif
	Len += Ret;
	
	/* FromBit=17 */
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:618> Error decoding subfield spare3\n");
		ED_HANDLE_IE_SYNTAX_ERROR (618)
	} 
#endif
	Len += Ret;
	
	/* FromBit=18 */
	(*Destin).LCSVA_CAP = (EDBitsToInt (Buffer, CurrOfs+18, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:619> Error decoding subfield LCSVA_CAP\n");
		ED_HANDLE_IE_SYNTAX_ERROR (619)
	} 
#endif
	Len += Ret;
	
	/* FromBit=19 */
	(*Destin).UCS2 = (EDBitsToInt (Buffer, CurrOfs+19, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:620> Error decoding subfield UCS2\n");
		ED_HANDLE_IE_SYNTAX_ERROR (620)
	} 
#endif
	Len += Ret;
	
	/* FromBit=20 */
	(*Destin).SoLSA = (EDBitsToInt (Buffer, CurrOfs+20, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:621> Error decoding subfield SoLSA\n");
		ED_HANDLE_IE_SYNTAX_ERROR (621)
	} 
#endif
	Len += Ret;
	
	/* FromBit=21 */
	(*Destin).CMSP = (EDBitsToInt (Buffer, CurrOfs+21, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:622> Error decoding subfield CMSP\n");
		ED_HANDLE_IE_SYNTAX_ERROR (622)
	} 
#endif
	Len += Ret;
	
	/* FromBit=22 */
	(*Destin).A5_3 = (EDBitsToInt (Buffer, CurrOfs+22, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:623> Error decoding subfield A5_3\n");
		ED_HANDLE_IE_SYNTAX_ERROR (623)
	} 
#endif
	Len += Ret;
	
	/* FromBit=23 */
	(*Destin).A5_2 = (EDBitsToInt (Buffer, CurrOfs+23, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:624> Error decoding subfield A5_2\n");
		ED_HANDLE_IE_SYNTAX_ERROR (624)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_RoutingAreaIdenti (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_RoutingAreaIdenti* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 48;
	EDIntToBits (Buffer, CurrOfs, (*Source).MCC2, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:625> Error encoding subfield MCC2\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+4, (*Source).MCC1, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:626> Error encoding subfield MCC1\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+8, (*Source).MNC3, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:627> Error encoding subfield MNC3\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+12, (*Source).MCC3, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:628> Error encoding subfield MCC3\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+16, (*Source).MNC2, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:629> Error encoding subfield MNC2\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+20, (*Source).MNC1, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:630> Error encoding subfield MNC1\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+24, (*Source).LAC, 16);
	Ret = 16;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:631> Error encoding subfield LAC\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+40, (*Source).RAC, 8);
	Ret = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:632> Error encoding subfield RAC\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_RoutingAreaIdenti (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_RoutingAreaIdenti* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=0 */
	(*Destin).MCC2 = EDBitsToInt (Buffer, CurrOfs, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:633> Error decoding subfield MCC2\n");
		ED_HANDLE_IE_SYNTAX_ERROR (633)
	} 
#endif
	Len += Ret;
	
	/* FromBit=4 */
	(*Destin).MCC1 = EDBitsToInt (Buffer, CurrOfs+4, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:634> Error decoding subfield MCC1\n");
		ED_HANDLE_IE_SYNTAX_ERROR (634)
	} 
#endif
	Len += Ret;
	
	/* FromBit=8 */
	(*Destin).MNC3 = EDBitsToInt (Buffer, CurrOfs+8, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:635> Error decoding subfield MNC3\n");
		ED_HANDLE_IE_SYNTAX_ERROR (635)
	} 
#endif
	Len += Ret;
	
	/* FromBit=12 */
	(*Destin).MCC3 = EDBitsToInt (Buffer, CurrOfs+12, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:636> Error decoding subfield MCC3\n");
		ED_HANDLE_IE_SYNTAX_ERROR (636)
	} 
#endif
	Len += Ret;
	
	/* FromBit=16 */
	(*Destin).MNC2 = EDBitsToInt (Buffer, CurrOfs+16, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:637> Error decoding subfield MNC2\n");
		ED_HANDLE_IE_SYNTAX_ERROR (637)
	} 
#endif
	Len += Ret;
	
	/* FromBit=20 */
	(*Destin).MNC1 = EDBitsToInt (Buffer, CurrOfs+20, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:638> Error decoding subfield MNC1\n");
		ED_HANDLE_IE_SYNTAX_ERROR (638)
	} 
#endif
	Len += Ret;
	
	/* FromBit=24 */
	(*Destin).LAC = EDBitsToInt (Buffer, CurrOfs+24, 16);
	Ret = 16;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:639> Error decoding subfield LAC\n");
		ED_HANDLE_IE_SYNTAX_ERROR (639)
	} 
#endif
	Len += Ret;
	
	/* FromBit=40 */
	(*Destin).RAC = EDBitsToInt (Buffer, CurrOfs+40, 8);
	Ret = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:640> Error decoding subfield RAC\n");
		ED_HANDLE_IE_SYNTAX_ERROR (640)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_CipheringKeySequenceNumber (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CipheringKeySequenceNumber* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 4;
	EDIntToBits (Buffer, CurrOfs+1, (*Source).KeySequence, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:641> Error encoding subfield KeySequence\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs, 0, 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:642> Error encoding subfield spare\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_CipheringKeySequenceNumber (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CipheringKeySequenceNumber* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=1 */
	(*Destin).KeySequence = EDBitsToInt (Buffer, CurrOfs+1, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:643> Error decoding subfield KeySequence\n");
		ED_HANDLE_IE_SYNTAX_ERROR (643)
	} 
#endif
	Len += Ret;
	
	/* FromBit=0 */
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:644> Error decoding subfield spare\n");
		ED_HANDLE_IE_SYNTAX_ERROR (644)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_CellDescription (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CellDescription* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 16;
	EDIntToBits (Buffer, CurrOfs, (*Source).BCCHArfcnHi, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:645> Error encoding subfield BCCHArfcnHi\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+2, (*Source).NCC, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:646> Error encoding subfield NCC\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+5, (*Source).BCC, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:647> Error encoding subfield BCC\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+8, (*Source).BCCHArfcnLo, 8);
	Ret = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:648> Error encoding subfield BCCHArfcnLo\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_CellDescription (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CellDescription* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=0 */
	(*Destin).BCCHArfcnHi = EDBitsToInt (Buffer, CurrOfs, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:649> Error decoding subfield BCCHArfcnHi\n");
		ED_HANDLE_IE_SYNTAX_ERROR (649)
	} 
#endif
	Len += Ret;
	
	/* FromBit=2 */
	(*Destin).NCC = EDBitsToInt (Buffer, CurrOfs+2, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:650> Error decoding subfield NCC\n");
		ED_HANDLE_IE_SYNTAX_ERROR (650)
	} 
#endif
	Len += Ret;
	
	/* FromBit=5 */
	(*Destin).BCC = EDBitsToInt (Buffer, CurrOfs+5, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:651> Error decoding subfield BCC\n");
		ED_HANDLE_IE_SYNTAX_ERROR (651)
	} 
#endif
	Len += Ret;
	
	/* FromBit=8 */
	(*Destin).BCCHArfcnLo = EDBitsToInt (Buffer, CurrOfs+8, 8);
	Ret = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:652> Error decoding subfield BCCHArfcnLo\n");
		ED_HANDLE_IE_SYNTAX_ERROR (652)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_CellOptions (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CellOptions* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 8;
	EDIntToBits (Buffer, CurrOfs, 0, 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:653> Error encoding subfield spare\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+1, ((*Source).PWRC != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:654> Error encoding subfield PWRC\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+2, (*Source).DTX, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:655> Error encoding subfield DTX\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+4, (*Source).RadioLinkTimeout, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:656> Error encoding subfield RadioLinkTimeout\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_CellOptions (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CellOptions* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=0 */
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:657> Error decoding subfield spare\n");
		ED_HANDLE_IE_SYNTAX_ERROR (657)
	} 
#endif
	Len += Ret;
	
	/* FromBit=1 */
	(*Destin).PWRC = (EDBitsToInt (Buffer, CurrOfs+1, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:658> Error decoding subfield PWRC\n");
		ED_HANDLE_IE_SYNTAX_ERROR (658)
	} 
#endif
	Len += Ret;
	
	/* FromBit=2 */
	(*Destin).DTX = EDBitsToInt (Buffer, CurrOfs+2, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:659> Error decoding subfield DTX\n");
		ED_HANDLE_IE_SYNTAX_ERROR (659)
	} 
#endif
	Len += Ret;
	
	/* FromBit=4 */
	(*Destin).RadioLinkTimeout = EDBitsToInt (Buffer, CurrOfs+4, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:660> Error decoding subfield RadioLinkTimeout\n");
		ED_HANDLE_IE_SYNTAX_ERROR (660)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_CellOptionsSacch (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CellOptionsSacch* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 8;
	EDIntToBits (Buffer, CurrOfs, (*Source).DTXbit8, 1);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:661> Error encoding subfield DTXbit8\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+1, ((*Source).PWRC != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:662> Error encoding subfield PWRC\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+2, (*Source).DTX, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:663> Error encoding subfield DTX\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+4, (*Source).RadioLinkTimeout, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:664> Error encoding subfield RadioLinkTimeout\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_CellOptionsSacch (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CellOptionsSacch* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=0 */
	(*Destin).DTXbit8 = EDBitsToInt (Buffer, CurrOfs, 1);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:665> Error decoding subfield DTXbit8\n");
		ED_HANDLE_IE_SYNTAX_ERROR (665)
	} 
#endif
	Len += Ret;
	
	/* FromBit=1 */
	(*Destin).PWRC = (EDBitsToInt (Buffer, CurrOfs+1, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:666> Error decoding subfield PWRC\n");
		ED_HANDLE_IE_SYNTAX_ERROR (666)
	} 
#endif
	Len += Ret;
	
	/* FromBit=2 */
	(*Destin).DTX = EDBitsToInt (Buffer, CurrOfs+2, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:667> Error decoding subfield DTX\n");
		ED_HANDLE_IE_SYNTAX_ERROR (667)
	} 
#endif
	Len += Ret;
	
	/* FromBit=4 */
	(*Destin).RadioLinkTimeout = EDBitsToInt (Buffer, CurrOfs+4, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:668> Error decoding subfield RadioLinkTimeout\n");
		ED_HANDLE_IE_SYNTAX_ERROR (668)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_CellSelParam (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CellSelParam* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 16;
	EDIntToBits (Buffer, CurrOfs, (*Source).CellReseHyst, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:669> Error encoding subfield CellReseHyst\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+3, (*Source).MsTxpwrMaxCch, 5);
	Ret = 5;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:670> Error encoding subfield MsTxpwrMaxCch\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+8, ((*Source).ACS != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:671> Error encoding subfield ACS\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+9, ((*Source).NECI != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:672> Error encoding subfield NECI\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+10, (*Source).RxLevAccessMin, 6);
	Ret = 6;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:673> Error encoding subfield RxLevAccessMin\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_CellSelParam (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CellSelParam* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=0 */
	(*Destin).CellReseHyst = EDBitsToInt (Buffer, CurrOfs, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:674> Error decoding subfield CellReseHyst\n");
		ED_HANDLE_IE_SYNTAX_ERROR (674)
	} 
#endif
	Len += Ret;
	
	/* FromBit=3 */
	(*Destin).MsTxpwrMaxCch = EDBitsToInt (Buffer, CurrOfs+3, 5);
	Ret = 5;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:675> Error decoding subfield MsTxpwrMaxCch\n");
		ED_HANDLE_IE_SYNTAX_ERROR (675)
	} 
#endif
	Len += Ret;
	
	/* FromBit=8 */
	(*Destin).ACS = (EDBitsToInt (Buffer, CurrOfs+8, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:676> Error decoding subfield ACS\n");
		ED_HANDLE_IE_SYNTAX_ERROR (676)
	} 
#endif
	Len += Ret;
	
	/* FromBit=9 */
	(*Destin).NECI = (EDBitsToInt (Buffer, CurrOfs+9, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:677> Error decoding subfield NECI\n");
		ED_HANDLE_IE_SYNTAX_ERROR (677)
	} 
#endif
	Len += Ret;
	
	/* FromBit=10 */
	(*Destin).RxLevAccessMin = EDBitsToInt (Buffer, CurrOfs+10, 6);
	Ret = 6;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:678> Error decoding subfield RxLevAccessMin\n");
		ED_HANDLE_IE_SYNTAX_ERROR (678)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_MACModeAndChCodReq (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_MACModeAndChCodReq* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 4;
	EDIntToBits (Buffer, CurrOfs, (*Source).Mac0Mode, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:679> Error encoding subfield Mac0Mode\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+2, (*Source).CS, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:680> Error encoding subfield CS\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_MACModeAndChCodReq (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_MACModeAndChCodReq* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=0 */
	(*Destin).Mac0Mode = EDBitsToInt (Buffer, CurrOfs, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:681> Error decoding subfield Mac0Mode\n");
		ED_HANDLE_IE_SYNTAX_ERROR (681)
	} 
#endif
	Len += Ret;
	
	/* FromBit=2 */
	(*Destin).CS = EDBitsToInt (Buffer, CurrOfs+2, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:682> Error decoding subfield CS\n");
		ED_HANDLE_IE_SYNTAX_ERROR (682)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_TChDesc (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_TChDesc* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 24;
	EDIntToBits (Buffer, CurrOfs, (*Source).ChType, 5);
	Ret = 5;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:683> Error encoding subfield ChType\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+5, (*Source).TN, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:684> Error encoding subfield TN\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+8, (*Source).TSC, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:685> Error encoding subfield TSC\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+11, ((*Source).H != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:686> Error encoding subfield H\n");
		return -1;
	} 
#endif
#define ED_IS_ENCODING
#define DATA ((*Source))
	if (DATA.H) {
#undef DATA
#undef ED_IS_ENCODING
		EDIntToBits (Buffer, CurrOfs+12, (*Source).MAIO, 6);
		Ret = 6;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:687> Error encoding subfield MAIO\n");
			return -1;
		} 
#endif
		EDIntToBits (Buffer, CurrOfs+18, (*Source).HSN, 6);
		Ret = 6;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:688> Error encoding subfield HSN\n");
			return -1;
		} 
#endif
	}
#define ED_IS_ENCODING
#define DATA ((*Source))
	if (!DATA.H) {
#undef DATA
#undef ED_IS_ENCODING
		EDIntToBits (Buffer, CurrOfs+12, 0, 2);Ret = 2;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:689> Error encoding subfield spare\n");
			return -1;
		} 
#endif
		EDIntToBits (Buffer, CurrOfs+14, (*Source).ARFCN, 10);
		Ret = 10;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:690> Error encoding subfield ARFCN\n");
			return -1;
		} 
#endif
	}

	return Len;
}
long DECODE_c_TChDesc (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_TChDesc* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=0 */
	(*Destin).ChType = EDBitsToInt (Buffer, CurrOfs, 5);
	Ret = 5;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:691> Error decoding subfield ChType\n");
		ED_HANDLE_IE_SYNTAX_ERROR (691)
	} 
#endif
	Len += Ret;
	
	/* FromBit=5 */
	(*Destin).TN = EDBitsToInt (Buffer, CurrOfs+5, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:692> Error decoding subfield TN\n");
		ED_HANDLE_IE_SYNTAX_ERROR (692)
	} 
#endif
	Len += Ret;
	
	/* FromBit=8 */
	(*Destin).TSC = EDBitsToInt (Buffer, CurrOfs+8, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:693> Error decoding subfield TSC\n");
		ED_HANDLE_IE_SYNTAX_ERROR (693)
	} 
#endif
	Len += Ret;
	
	/* FromBit=11 */
	(*Destin).H = (EDBitsToInt (Buffer, CurrOfs+11, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:694> Error decoding subfield H\n");
		ED_HANDLE_IE_SYNTAX_ERROR (694)
	} 
#endif
	Len += Ret;
	
	/* FromBit=12 */
	/* isConditional=0 beginOfGroupCondition=1 */
#define ED_IS_DECODING
#define DATA ((*Destin))
	if (DATA.H) {
#undef DATA
#undef ED_IS_DECODING
		SETPRESENT_c_TChDesc_MAIO (&((*Destin)), ED_TRUE);
		(*Destin).MAIO = EDBitsToInt (Buffer, CurrOfs+12, 6);
		Ret = 6;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:695> Error decoding subfield MAIO\n");
			ED_HANDLE_IE_SYNTAX_ERROR (695)
		} 
#endif
		Len += Ret;
	
	/* FromBit=18 */
	SETPRESENT_c_TChDesc_HSN (&((*Destin)), ED_TRUE);
	(*Destin).HSN = EDBitsToInt (Buffer, CurrOfs+18, 6);
	Ret = 6;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:696> Error decoding subfield HSN\n");
		ED_HANDLE_IE_SYNTAX_ERROR (696)
	} 
#endif
	Len += Ret;
	}/* FINE */
	
	/* FromBit=12 */
	/* isConditional=0 beginOfGroupCondition=1 */
#define ED_IS_DECODING
#define DATA ((*Destin))
	if (!DATA.H) {
#undef DATA
#undef ED_IS_DECODING
		SETPRESENT_c_TChDesc_spare (&((*Destin)), ED_TRUE);
		Ret = 2;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:697> Error decoding subfield spare\n");
			ED_HANDLE_IE_SYNTAX_ERROR (697)
		} 
#endif
		Len += Ret;
	
	/* FromBit=14 */
	SETPRESENT_c_TChDesc_ARFCN (&((*Destin)), ED_TRUE);
	(*Destin).ARFCN = EDBitsToInt (Buffer, CurrOfs+14, 10);
	Ret = 10;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:698> Error decoding subfield ARFCN\n");
		ED_HANDLE_IE_SYNTAX_ERROR (698)
	} 
#endif
	Len += Ret;
	}/* FINE */
	

	return Len;
}
long ENCODE_c_ClassmarkEnquiryMask (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_ClassmarkEnquiryMask* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 8;
	EDIntToBits (Buffer, CurrOfs, ((*Source).ClassmarkChange != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:699> Error encoding subfield ClassmarkChange\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+1, (*Source).UTRANClassmarkChange, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:700> Error encoding subfield UTRANClassmarkChange\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+4, ((*Source).CDMAClassmarkChange != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:701> Error encoding subfield CDMAClassmarkChange\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+5, 0, 3);Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:702> Error encoding subfield spare\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_ClassmarkEnquiryMask (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_ClassmarkEnquiryMask* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=0 */
	(*Destin).ClassmarkChange = (EDBitsToInt (Buffer, CurrOfs, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:703> Error decoding subfield ClassmarkChange\n");
		ED_HANDLE_IE_SYNTAX_ERROR (703)
	} 
#endif
	Len += Ret;
	
	/* FromBit=1 */
	(*Destin).UTRANClassmarkChange = EDBitsToInt (Buffer, CurrOfs+1, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:704> Error decoding subfield UTRANClassmarkChange\n");
		ED_HANDLE_IE_SYNTAX_ERROR (704)
	} 
#endif
	Len += Ret;
	
	/* FromBit=4 */
	(*Destin).CDMAClassmarkChange = (EDBitsToInt (Buffer, CurrOfs+4, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:705> Error decoding subfield CDMAClassmarkChange\n");
		ED_HANDLE_IE_SYNTAX_ERROR (705)
	} 
#endif
	Len += Ret;
	
	/* FromBit=5 */
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:706> Error decoding subfield spare\n");
		ED_HANDLE_IE_SYNTAX_ERROR (706)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_ChannelNeeded (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_ChannelNeeded* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 4;
	EDIntToBits (Buffer, CurrOfs+2, (*Source).Channel1, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:707> Error encoding subfield Channel1\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs, (*Source).Channel2, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:708> Error encoding subfield Channel2\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_ChannelNeeded (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_ChannelNeeded* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=2 */
	(*Destin).Channel1 = EDBitsToInt (Buffer, CurrOfs+2, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:709> Error decoding subfield Channel1\n");
		ED_HANDLE_IE_SYNTAX_ERROR (709)
	} 
#endif
	Len += Ret;
	
	/* FromBit=0 */
	(*Destin).Channel2 = EDBitsToInt (Buffer, CurrOfs, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:710> Error decoding subfield Channel2\n");
		ED_HANDLE_IE_SYNTAX_ERROR (710)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_ChannelRequestDesc (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_ChannelRequestDesc* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 40;
	EDIntToBits (Buffer, CurrOfs, ((*Source).MTMO != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:711> Error encoding subfield MTMO\n");
		return -1;
	} 
#endif
#define ED_IS_ENCODING
#define DATA ((*Source))
	if ( !DATA.MTMO ) {
#undef DATA
#undef ED_IS_ENCODING
		EDIntToBits (Buffer, CurrOfs+1, 0, 39);Ret = 39;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:712> Error encoding subfield spare\n");
			return -1;
		} 
#endif
	}
#define ED_IS_ENCODING
#define DATA ((*Source))
	if ( DATA.MTMO ) {
#undef DATA
#undef ED_IS_ENCODING
		EDIntToBits (Buffer, CurrOfs+1, 0, 3);Ret = 3;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:713> Error encoding subfield spare2\n");
			return -1;
		} 
#endif
		EDIntToBits (Buffer, CurrOfs+4, (*Source).Priority, 2);
		Ret = 2;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:714> Error encoding subfield Priority\n");
			return -1;
		} 
#endif
		EDIntToBits (Buffer, CurrOfs+6, ((*Source).RLCMode != 0 ? 1 : 0), 1);Ret = 1;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:715> Error encoding subfield RLCMode\n");
			return -1;
		} 
#endif
		EDIntToBits (Buffer, CurrOfs+7, ((*Source).LLCFramType != 0 ? 1 : 0), 1);Ret = 1;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:716> Error encoding subfield LLCFramType\n");
			return -1;
		} 
#endif
		EDIntToBits (Buffer, CurrOfs+8, (*Source).ReqBandwidth, 16);
		Ret = 16;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:717> Error encoding subfield ReqBandwidth\n");
			return -1;
		} 
#endif
		EDIntToBits (Buffer, CurrOfs+24, (*Source).RLCOctetCount, 16);
		Ret = 16;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:718> Error encoding subfield RLCOctetCount\n");
			return -1;
		} 
#endif
	}

	return Len;
}
long DECODE_c_ChannelRequestDesc (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_ChannelRequestDesc* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=0 */
	(*Destin).MTMO = (EDBitsToInt (Buffer, CurrOfs, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:719> Error decoding subfield MTMO\n");
		ED_HANDLE_IE_SYNTAX_ERROR (719)
	} 
#endif
	Len += Ret;
	
	/* FromBit=1 */
	/* isConditional=0 beginOfGroupCondition=1 */
#define ED_IS_DECODING
#define DATA ((*Destin))
	if ( !DATA.MTMO ) {
#undef DATA
#undef ED_IS_DECODING
		SETPRESENT_c_ChannelRequestDesc_spare (&((*Destin)), ED_TRUE);
		Ret = 39;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:720> Error decoding subfield spare\n");
			ED_HANDLE_IE_SYNTAX_ERROR (720)
		} 
#endif
		Len += Ret;
	}/* FINE */
	
	/* FromBit=1 */
	/* isConditional=0 beginOfGroupCondition=1 */
#define ED_IS_DECODING
#define DATA ((*Destin))
	if ( DATA.MTMO ) {
#undef DATA
#undef ED_IS_DECODING
		SETPRESENT_c_ChannelRequestDesc_spare2 (&((*Destin)), ED_TRUE);
		Ret = 3;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:721> Error decoding subfield spare2\n");
			ED_HANDLE_IE_SYNTAX_ERROR (721)
		} 
#endif
		Len += Ret;
	
	/* FromBit=4 */
	SETPRESENT_c_ChannelRequestDesc_Priority (&((*Destin)), ED_TRUE);
	(*Destin).Priority = EDBitsToInt (Buffer, CurrOfs+4, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:722> Error decoding subfield Priority\n");
		ED_HANDLE_IE_SYNTAX_ERROR (722)
	} 
#endif
	Len += Ret;
	
	/* FromBit=6 */
	SETPRESENT_c_ChannelRequestDesc_RLCMode (&((*Destin)), ED_TRUE);
	(*Destin).RLCMode = (EDBitsToInt (Buffer, CurrOfs+6, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:723> Error decoding subfield RLCMode\n");
		ED_HANDLE_IE_SYNTAX_ERROR (723)
	} 
#endif
	Len += Ret;
	
	/* FromBit=7 */
	SETPRESENT_c_ChannelRequestDesc_LLCFramType (&((*Destin)), ED_TRUE);
	(*Destin).LLCFramType = (EDBitsToInt (Buffer, CurrOfs+7, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:724> Error decoding subfield LLCFramType\n");
		ED_HANDLE_IE_SYNTAX_ERROR (724)
	} 
#endif
	Len += Ret;
	
	/* FromBit=8 */
	SETPRESENT_c_ChannelRequestDesc_ReqBandwidth (&((*Destin)), ED_TRUE);
	(*Destin).ReqBandwidth = EDBitsToInt (Buffer, CurrOfs+8, 16);
	Ret = 16;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:725> Error decoding subfield ReqBandwidth\n");
		ED_HANDLE_IE_SYNTAX_ERROR (725)
	} 
#endif
	Len += Ret;
	
	/* FromBit=24 */
	SETPRESENT_c_ChannelRequestDesc_RLCOctetCount (&((*Destin)), ED_TRUE);
	(*Destin).RLCOctetCount = EDBitsToInt (Buffer, CurrOfs+24, 16);
	Ret = 16;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:726> Error decoding subfield RLCOctetCount\n");
		ED_HANDLE_IE_SYNTAX_ERROR (726)
	} 
#endif
	Len += Ret;
	}/* FINE */
	

	return Len;
}
long ENCODE_c_CipherModeSetting (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CipherModeSetting* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 4;
	EDIntToBits (Buffer, CurrOfs+3, ((*Source).SC != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:727> Error encoding subfield SC\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs, (*Source).AlgIdent, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:728> Error encoding subfield AlgIdent\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_CipherModeSetting (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CipherModeSetting* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=3 */
	(*Destin).SC = (EDBitsToInt (Buffer, CurrOfs+3, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:729> Error decoding subfield SC\n");
		ED_HANDLE_IE_SYNTAX_ERROR (729)
	} 
#endif
	Len += Ret;
	
	/* FromBit=0 */
	(*Destin).AlgIdent = EDBitsToInt (Buffer, CurrOfs, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:730> Error decoding subfield AlgIdent\n");
		ED_HANDLE_IE_SYNTAX_ERROR (730)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_CipherResponse (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CipherResponse* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 4;
	EDIntToBits (Buffer, CurrOfs+3, ((*Source).CR != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:731> Error encoding subfield CR\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs, 0, 3);Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:732> Error encoding subfield spare\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_CipherResponse (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CipherResponse* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=3 */
	(*Destin).CR = (EDBitsToInt (Buffer, CurrOfs+3, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:733> Error decoding subfield CR\n");
		ED_HANDLE_IE_SYNTAX_ERROR (733)
	} 
#endif
	Len += Ret;
	
	/* FromBit=0 */
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:734> Error decoding subfield spare\n");
		ED_HANDLE_IE_SYNTAX_ERROR (734)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_CtrlChannelDesc (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CtrlChannelDesc* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 24;
	EDIntToBits (Buffer, CurrOfs, ((*Source).MSCR != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:735> Error encoding subfield MSCR\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+1, ((*Source).ATT != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:736> Error encoding subfield ATT\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+2, (*Source).BsAgBlksRes, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:737> Error encoding subfield BsAgBlksRes\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+5, (*Source).CCCHConf, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:738> Error encoding subfield CCCHConf\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+8, 0, 5);Ret = 5;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:739> Error encoding subfield spare\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+13, (*Source).BsPaMfrms, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:740> Error encoding subfield BsPaMfrms\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+16, (*Source).T3212TimeOutValue, 8);
	Ret = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:741> Error encoding subfield T3212TimeOutValue\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_CtrlChannelDesc (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CtrlChannelDesc* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=0 */
	(*Destin).MSCR = (EDBitsToInt (Buffer, CurrOfs, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:742> Error decoding subfield MSCR\n");
		ED_HANDLE_IE_SYNTAX_ERROR (742)
	} 
#endif
	Len += Ret;
	
	/* FromBit=1 */
	(*Destin).ATT = (EDBitsToInt (Buffer, CurrOfs+1, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:743> Error decoding subfield ATT\n");
		ED_HANDLE_IE_SYNTAX_ERROR (743)
	} 
#endif
	Len += Ret;
	
	/* FromBit=2 */
	(*Destin).BsAgBlksRes = EDBitsToInt (Buffer, CurrOfs+2, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:744> Error decoding subfield BsAgBlksRes\n");
		ED_HANDLE_IE_SYNTAX_ERROR (744)
	} 
#endif
	Len += Ret;
	
	/* FromBit=5 */
	(*Destin).CCCHConf = EDBitsToInt (Buffer, CurrOfs+5, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:745> Error decoding subfield CCCHConf\n");
		ED_HANDLE_IE_SYNTAX_ERROR (745)
	} 
#endif
	Len += Ret;
	
	/* FromBit=8 */
	Ret = 5;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:746> Error decoding subfield spare\n");
		ED_HANDLE_IE_SYNTAX_ERROR (746)
	} 
#endif
	Len += Ret;
	
	/* FromBit=13 */
	(*Destin).BsPaMfrms = EDBitsToInt (Buffer, CurrOfs+13, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:747> Error decoding subfield BsPaMfrms\n");
		ED_HANDLE_IE_SYNTAX_ERROR (747)
	} 
#endif
	Len += Ret;
	
	/* FromBit=16 */
	(*Destin).T3212TimeOutValue = EDBitsToInt (Buffer, CurrOfs+16, 8);
	Ret = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:748> Error decoding subfield T3212TimeOutValue\n");
		ED_HANDLE_IE_SYNTAX_ERROR (748)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_FreqChannelSeq (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_FreqChannelSeq* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 8;
	EDIntToBits (Buffer, CurrOfs, 0, 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:749> Error encoding subfield spare\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+1, (*Source).LowestARFCN, 7);
	Ret = 7;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:750> Error encoding subfield LowestARFCN\n");
		return -1;
	} 
#endif
	Ret = ENCODE_c_IncSkipOfARFCN (Buffer, CurrOfs+8, &((*Source).IncSkipOfARFCN));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:751> Error encoding subfield IncSkipOfARFCN\n");
		return -1;
	} 
#endif
	Len += Ret;

	return Len;
}
long DECODE_c_FreqChannelSeq (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_FreqChannelSeq* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=0 */
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:752> Error decoding subfield spare\n");
		ED_HANDLE_IE_SYNTAX_ERROR (752)
	} 
#endif
	Len += Ret;
	
	/* FromBit=1 */
	(*Destin).LowestARFCN = EDBitsToInt (Buffer, CurrOfs+1, 7);
	Ret = 7;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:753> Error decoding subfield LowestARFCN\n");
		ED_HANDLE_IE_SYNTAX_ERROR (753)
	} 
#endif
	Len += Ret;
	
	/* FromBit=8 */
	Ret = DECODE_c_IncSkipOfARFCN (Buffer, CurrOfs+8, &((*Destin).IncSkipOfARFCN), (Length - 8));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:754> Error decoding subfield IncSkipOfARFCN\n");
		ED_HANDLE_IE_SYNTAX_ERROR (754)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_GrpChannelDesc (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_GrpChannelDesc* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 24;
	EDIntToBits (Buffer, CurrOfs, (*Source).ChType, 5);
	Ret = 5;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:755> Error encoding subfield ChType\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+5, (*Source).TN, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:756> Error encoding subfield TN\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+8, (*Source).TSC, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:757> Error encoding subfield TSC\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+11, ((*Source).H != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:758> Error encoding subfield H\n");
		return -1;
	} 
#endif
#define ED_IS_ENCODING
#define DATA ((*Source))
	if (DATA.H) {
#undef DATA
#undef ED_IS_ENCODING
		EDIntToBits (Buffer, CurrOfs+12, (*Source).MAIO, 6);
		Ret = 6;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:759> Error encoding subfield MAIO\n");
			return -1;
		} 
#endif
		EDIntToBits (Buffer, CurrOfs+18, (*Source).HSN, 6);
		Ret = 6;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:760> Error encoding subfield HSN\n");
			return -1;
		} 
#endif
	}
#define ED_IS_ENCODING
#define DATA ((*Source))
	if (!DATA.H) {
#undef DATA
#undef ED_IS_ENCODING
		EDIntToBits (Buffer, CurrOfs+12, 0, 2);Ret = 2;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:761> Error encoding subfield spare\n");
			return -1;
		} 
#endif
		EDIntToBits (Buffer, CurrOfs+14, (*Source).ARFCN, 10);
		Ret = 10;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:762> Error encoding subfield ARFCN\n");
			return -1;
		} 
#endif
	}
	Ret = ENCODE_c_GrpChannelMA (Buffer, CurrOfs+24, &((*Source).MA));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:763> Error encoding subfield MA\n");
		return -1;
	} 
#endif
	Len += Ret;

	return Len;
}
long DECODE_c_GrpChannelDesc (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_GrpChannelDesc* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=0 */
	(*Destin).ChType = EDBitsToInt (Buffer, CurrOfs, 5);
	Ret = 5;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:764> Error decoding subfield ChType\n");
		ED_HANDLE_IE_SYNTAX_ERROR (764)
	} 
#endif
	Len += Ret;
	
	/* FromBit=5 */
	(*Destin).TN = EDBitsToInt (Buffer, CurrOfs+5, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:765> Error decoding subfield TN\n");
		ED_HANDLE_IE_SYNTAX_ERROR (765)
	} 
#endif
	Len += Ret;
	
	/* FromBit=8 */
	(*Destin).TSC = EDBitsToInt (Buffer, CurrOfs+8, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:766> Error decoding subfield TSC\n");
		ED_HANDLE_IE_SYNTAX_ERROR (766)
	} 
#endif
	Len += Ret;
	
	/* FromBit=11 */
	(*Destin).H = (EDBitsToInt (Buffer, CurrOfs+11, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:767> Error decoding subfield H\n");
		ED_HANDLE_IE_SYNTAX_ERROR (767)
	} 
#endif
	Len += Ret;
	
	/* FromBit=12 */
	/* isConditional=0 beginOfGroupCondition=1 */
#define ED_IS_DECODING
#define DATA ((*Destin))
	if (DATA.H) {
#undef DATA
#undef ED_IS_DECODING
		SETPRESENT_c_GrpChannelDesc_MAIO (&((*Destin)), ED_TRUE);
		(*Destin).MAIO = EDBitsToInt (Buffer, CurrOfs+12, 6);
		Ret = 6;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:768> Error decoding subfield MAIO\n");
			ED_HANDLE_IE_SYNTAX_ERROR (768)
		} 
#endif
		Len += Ret;
	
	/* FromBit=18 */
	SETPRESENT_c_GrpChannelDesc_HSN (&((*Destin)), ED_TRUE);
	(*Destin).HSN = EDBitsToInt (Buffer, CurrOfs+18, 6);
	Ret = 6;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:769> Error decoding subfield HSN\n");
		ED_HANDLE_IE_SYNTAX_ERROR (769)
	} 
#endif
	Len += Ret;
	}/* FINE */
	
	/* FromBit=12 */
	/* isConditional=0 beginOfGroupCondition=1 */
#define ED_IS_DECODING
#define DATA ((*Destin))
	if (!DATA.H) {
#undef DATA
#undef ED_IS_DECODING
		SETPRESENT_c_GrpChannelDesc_spare (&((*Destin)), ED_TRUE);
		Ret = 2;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:770> Error decoding subfield spare\n");
			ED_HANDLE_IE_SYNTAX_ERROR (770)
		} 
#endif
		Len += Ret;
	
	/* FromBit=14 */
	SETPRESENT_c_GrpChannelDesc_ARFCN (&((*Destin)), ED_TRUE);
	(*Destin).ARFCN = EDBitsToInt (Buffer, CurrOfs+14, 10);
	Ret = 10;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:771> Error decoding subfield ARFCN\n");
		ED_HANDLE_IE_SYNTAX_ERROR (771)
	} 
#endif
	Len += Ret;
	}/* FINE */
	
	/* FromBit=24 */
	Ret = DECODE_c_GrpChannelMA (Buffer, CurrOfs+24, &((*Destin).MA), (Length - 24));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:772> Error decoding subfield MA\n");
		ED_HANDLE_IE_SYNTAX_ERROR (772)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_GPRSResumption (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_GPRSResumption* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 4;
	EDIntToBits (Buffer, CurrOfs+3, ((*Source).ACK != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:773> Error encoding subfield ACK\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs, 0, 3);Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:774> Error encoding subfield spare\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_GPRSResumption (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_GPRSResumption* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=3 */
	(*Destin).ACK = (EDBitsToInt (Buffer, CurrOfs+3, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:775> Error decoding subfield ACK\n");
		ED_HANDLE_IE_SYNTAX_ERROR (775)
	} 
#endif
	Len += Ret;
	
	/* FromBit=0 */
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:776> Error decoding subfield spare\n");
		ED_HANDLE_IE_SYNTAX_ERROR (776)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_MeasurementSingleResult (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_MeasurementSingleResult* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 17;
	EDIntToBits (Buffer, CurrOfs+11, (*Source).BSICNCell, 6);
	Ret = 6;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:777> Error encoding subfield BSICNCell\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+6, (*Source).BCCHFreqNCell, 5);
	Ret = 5;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:778> Error encoding subfield BCCHFreqNCell\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs, (*Source).RXLevNCell, 6);
	Ret = 6;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:779> Error encoding subfield RXLevNCell\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_MeasurementSingleResult (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_MeasurementSingleResult* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=11 */
	(*Destin).BSICNCell = EDBitsToInt (Buffer, CurrOfs+11, 6);
	Ret = 6;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:780> Error decoding subfield BSICNCell\n");
		ED_HANDLE_IE_SYNTAX_ERROR (780)
	} 
#endif
	Len += Ret;
	
	/* FromBit=6 */
	(*Destin).BCCHFreqNCell = EDBitsToInt (Buffer, CurrOfs+6, 5);
	Ret = 5;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:781> Error decoding subfield BCCHFreqNCell\n");
		ED_HANDLE_IE_SYNTAX_ERROR (781)
	} 
#endif
	Len += Ret;
	
	/* FromBit=0 */
	(*Destin).RXLevNCell = EDBitsToInt (Buffer, CurrOfs, 6);
	Ret = 6;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:782> Error decoding subfield RXLevNCell\n");
		ED_HANDLE_IE_SYNTAX_ERROR (782)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_MeasurementResults (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_MeasurementResults* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 26;
	EDIntToBits (Buffer, CurrOfs, ((*Source).BAUsed != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:783> Error encoding subfield BAUsed\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+1, ((*Source).DTXUsed != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:784> Error encoding subfield DTXUsed\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+2, (*Source).RXLevFullServingCell, 6);
	Ret = 6;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:785> Error encoding subfield RXLevFullServingCell\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+8, ((*Source)._3G_BA_USED != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:786> Error encoding subfield _3G_BA_USED\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+9, ((*Source).MeasValid != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:787> Error encoding subfield MeasValid\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+10, (*Source).RXLevSubServingCell, 6);
	Ret = 6;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:788> Error encoding subfield RXLevSubServingCell\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+16, 0, 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:789> Error encoding subfield spare2\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+17, (*Source).RXQualFullServingCell, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:790> Error encoding subfield RXQualFullServingCell\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+20, (*Source).RXQualSubServingCell, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:791> Error encoding subfield RXQualSubServingCell\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+23, (*Source).NoNcellM, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:792> Error encoding subfield NoNcellM\n");
		return -1;
	} 
#endif
	Ret = ENCODE_c_MeasurementResultsList (Buffer, CurrOfs+26, &((*Source).Measurements));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:793> Error encoding subfield Measurements\n");
		return -1;
	} 
#endif
	Len += Ret;

	return Len;
}
long DECODE_c_MeasurementResults (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_MeasurementResults* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=0 */
	(*Destin).BAUsed = (EDBitsToInt (Buffer, CurrOfs, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:794> Error decoding subfield BAUsed\n");
		ED_HANDLE_IE_SYNTAX_ERROR (794)
	} 
#endif
	Len += Ret;
	
	/* FromBit=1 */
	(*Destin).DTXUsed = (EDBitsToInt (Buffer, CurrOfs+1, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:795> Error decoding subfield DTXUsed\n");
		ED_HANDLE_IE_SYNTAX_ERROR (795)
	} 
#endif
	Len += Ret;
	
	/* FromBit=2 */
	(*Destin).RXLevFullServingCell = EDBitsToInt (Buffer, CurrOfs+2, 6);
	Ret = 6;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:796> Error decoding subfield RXLevFullServingCell\n");
		ED_HANDLE_IE_SYNTAX_ERROR (796)
	} 
#endif
	Len += Ret;
	
	/* FromBit=8 */
	(*Destin)._3G_BA_USED = (EDBitsToInt (Buffer, CurrOfs+8, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:797> Error decoding subfield _3G_BA_USED\n");
		ED_HANDLE_IE_SYNTAX_ERROR (797)
	} 
#endif
	Len += Ret;
	
	/* FromBit=9 */
	(*Destin).MeasValid = (EDBitsToInt (Buffer, CurrOfs+9, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:798> Error decoding subfield MeasValid\n");
		ED_HANDLE_IE_SYNTAX_ERROR (798)
	} 
#endif
	Len += Ret;
	
	/* FromBit=10 */
	(*Destin).RXLevSubServingCell = EDBitsToInt (Buffer, CurrOfs+10, 6);
	Ret = 6;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:799> Error decoding subfield RXLevSubServingCell\n");
		ED_HANDLE_IE_SYNTAX_ERROR (799)
	} 
#endif
	Len += Ret;
	
	/* FromBit=16 */
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:800> Error decoding subfield spare2\n");
		ED_HANDLE_IE_SYNTAX_ERROR (800)
	} 
#endif
	Len += Ret;
	
	/* FromBit=17 */
	(*Destin).RXQualFullServingCell = EDBitsToInt (Buffer, CurrOfs+17, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:801> Error decoding subfield RXQualFullServingCell\n");
		ED_HANDLE_IE_SYNTAX_ERROR (801)
	} 
#endif
	Len += Ret;
	
	/* FromBit=20 */
	(*Destin).RXQualSubServingCell = EDBitsToInt (Buffer, CurrOfs+20, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:802> Error decoding subfield RXQualSubServingCell\n");
		ED_HANDLE_IE_SYNTAX_ERROR (802)
	} 
#endif
	Len += Ret;
	
	/* FromBit=23 */
	(*Destin).NoNcellM = EDBitsToInt (Buffer, CurrOfs+23, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:803> Error decoding subfield NoNcellM\n");
		ED_HANDLE_IE_SYNTAX_ERROR (803)
	} 
#endif
	Len += Ret;
	
	/* FromBit=26 */
	Ret = DECODE_c_MeasurementResultsList (Buffer, CurrOfs+26, &((*Destin).Measurements), (Length - 26));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:804> Error decoding subfield Measurements\n");
		ED_HANDLE_IE_SYNTAX_ERROR (804)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_GPRSMeasurementResult (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_GPRSMeasurementResult* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 16;
	EDIntToBits (Buffer, CurrOfs, (*Source).C_VALUE, 6);
	Ret = 6;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:805> Error encoding subfield C_VALUE\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+6, (*Source).RXQUAL, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:806> Error encoding subfield RXQUAL\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+9, 0, 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:807> Error encoding subfield spare\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+10, (*Source).SIGN_VAR, 6);
	Ret = 6;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:808> Error encoding subfield SIGN_VAR\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_GPRSMeasurementResult (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_GPRSMeasurementResult* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=0 */
	(*Destin).C_VALUE = EDBitsToInt (Buffer, CurrOfs, 6);
	Ret = 6;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:809> Error decoding subfield C_VALUE\n");
		ED_HANDLE_IE_SYNTAX_ERROR (809)
	} 
#endif
	Len += Ret;
	
	/* FromBit=6 */
	(*Destin).RXQUAL = EDBitsToInt (Buffer, CurrOfs+6, 3);
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:810> Error decoding subfield RXQUAL\n");
		ED_HANDLE_IE_SYNTAX_ERROR (810)
	} 
#endif
	Len += Ret;
	
	/* FromBit=9 */
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:811> Error decoding subfield spare\n");
		ED_HANDLE_IE_SYNTAX_ERROR (811)
	} 
#endif
	Len += Ret;
	
	/* FromBit=10 */
	(*Destin).SIGN_VAR = EDBitsToInt (Buffer, CurrOfs+10, 6);
	Ret = 6;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:812> Error decoding subfield SIGN_VAR\n");
		ED_HANDLE_IE_SYNTAX_ERROR (812)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_MobileTimeDiff (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_MobileTimeDiff* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 24;
	EDIntToBits (Buffer, CurrOfs, (*Source).MobileTimeDiff, 21);
	Ret = 21;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:813> Error encoding subfield MobileTimeDiff\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+21, 0, 3);Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:814> Error encoding subfield spare\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_MobileTimeDiff (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_MobileTimeDiff* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=0 */
	(*Destin).MobileTimeDiff = EDBitsToInt (Buffer, CurrOfs, 21);
	Ret = 21;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:815> Error decoding subfield MobileTimeDiff\n");
		ED_HANDLE_IE_SYNTAX_ERROR (815)
	} 
#endif
	Len += Ret;
	
	/* FromBit=21 */
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:816> Error decoding subfield spare\n");
		ED_HANDLE_IE_SYNTAX_ERROR (816)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_DedicatedModeOrTBF (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_DedicatedModeOrTBF* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 8;
	EDIntToBits (Buffer, CurrOfs+7, ((*Source).TD != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:817> Error encoding subfield TD\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+6, ((*Source).Downlink != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:818> Error encoding subfield Downlink\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+5, ((*Source).TMA != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:819> Error encoding subfield TMA\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+1, 0, 4);Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:820> Error encoding subfield spare\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs, ((*Source).DedicatedMode != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:821> Error encoding subfield DedicatedMode\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_DedicatedModeOrTBF (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_DedicatedModeOrTBF* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=7 */
	(*Destin).TD = (EDBitsToInt (Buffer, CurrOfs+7, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:822> Error decoding subfield TD\n");
		ED_HANDLE_IE_SYNTAX_ERROR (822)
	} 
#endif
	Len += Ret;
	
	/* FromBit=6 */
	(*Destin).Downlink = (EDBitsToInt (Buffer, CurrOfs+6, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:823> Error decoding subfield Downlink\n");
		ED_HANDLE_IE_SYNTAX_ERROR (823)
	} 
#endif
	Len += Ret;
	
	/* FromBit=5 */
	(*Destin).TMA = (EDBitsToInt (Buffer, CurrOfs+5, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:824> Error decoding subfield TMA\n");
		ED_HANDLE_IE_SYNTAX_ERROR (824)
	} 
#endif
	Len += Ret;
	
	/* FromBit=1 */
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:825> Error decoding subfield spare\n");
		ED_HANDLE_IE_SYNTAX_ERROR (825)
	} 
#endif
	Len += Ret;
	
	/* FromBit=0 */
	(*Destin).DedicatedMode = (EDBitsToInt (Buffer, CurrOfs, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:826> Error decoding subfield DedicatedMode\n");
		ED_HANDLE_IE_SYNTAX_ERROR (826)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_DedicatedModeOrTBF4b (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_DedicatedModeOrTBF4b* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 4;
	EDIntToBits (Buffer, CurrOfs+4, 0, 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:827> Error encoding subfield spare\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+3, ((*Source).TD != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:828> Error encoding subfield TD\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+2, ((*Source).Downlink != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:829> Error encoding subfield Downlink\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+1, ((*Source).TMA != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:830> Error encoding subfield TMA\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_DedicatedModeOrTBF4b (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_DedicatedModeOrTBF4b* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=4 */
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:831> Error decoding subfield spare\n");
		ED_HANDLE_IE_SYNTAX_ERROR (831)
	} 
#endif
	Len += Ret;
	
	/* FromBit=3 */
	(*Destin).TD = (EDBitsToInt (Buffer, CurrOfs+3, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:832> Error decoding subfield TD\n");
		ED_HANDLE_IE_SYNTAX_ERROR (832)
	} 
#endif
	Len += Ret;
	
	/* FromBit=2 */
	(*Destin).Downlink = (EDBitsToInt (Buffer, CurrOfs+2, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:833> Error decoding subfield Downlink\n");
		ED_HANDLE_IE_SYNTAX_ERROR (833)
	} 
#endif
	Len += Ret;
	
	/* FromBit=1 */
	(*Destin).TMA = (EDBitsToInt (Buffer, CurrOfs+1, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:834> Error decoding subfield TMA\n");
		ED_HANDLE_IE_SYNTAX_ERROR (834)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_PageMode (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_PageMode* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 4;
	EDIntToBits (Buffer, CurrOfs+2, (*Source).PM, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:835> Error encoding subfield PM\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs, 0, 2);Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:836> Error encoding subfield spare\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_PageMode (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PageMode* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=2 */
	(*Destin).PM = EDBitsToInt (Buffer, CurrOfs+2, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:837> Error decoding subfield PM\n");
		ED_HANDLE_IE_SYNTAX_ERROR (837)
	} 
#endif
	Len += Ret;
	
	/* FromBit=0 */
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:838> Error decoding subfield spare\n");
		ED_HANDLE_IE_SYNTAX_ERROR (838)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_PowerCommand (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_PowerCommand* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 8;
	EDIntToBits (Buffer, CurrOfs, 0, 3);Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:839> Error encoding subfield spare\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+3, (*Source).PowerLevel, 5);
	Ret = 5;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:840> Error encoding subfield PowerLevel\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_PowerCommand (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PowerCommand* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=0 */
	Ret = 3;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:841> Error decoding subfield spare\n");
		ED_HANDLE_IE_SYNTAX_ERROR (841)
	} 
#endif
	Len += Ret;
	
	/* FromBit=3 */
	(*Destin).PowerLevel = EDBitsToInt (Buffer, CurrOfs+3, 5);
	Ret = 5;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:842> Error decoding subfield PowerLevel\n");
		ED_HANDLE_IE_SYNTAX_ERROR (842)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_PowerCommandAndAccessType (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_PowerCommandAndAccessType* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 8;
	EDIntToBits (Buffer, CurrOfs, ((*Source).ATC != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:843> Error encoding subfield ATC\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+1, 0, 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:844> Error encoding subfield spare\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+2, ((*Source).FPC != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:845> Error encoding subfield FPC\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+3, (*Source).PowerLevel, 5);
	Ret = 5;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:846> Error encoding subfield PowerLevel\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_PowerCommandAndAccessType (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PowerCommandAndAccessType* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=0 */
	(*Destin).ATC = (EDBitsToInt (Buffer, CurrOfs, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:847> Error decoding subfield ATC\n");
		ED_HANDLE_IE_SYNTAX_ERROR (847)
	} 
#endif
	Len += Ret;
	
	/* FromBit=1 */
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:848> Error decoding subfield spare\n");
		ED_HANDLE_IE_SYNTAX_ERROR (848)
	} 
#endif
	Len += Ret;
	
	/* FromBit=2 */
	(*Destin).FPC = (EDBitsToInt (Buffer, CurrOfs+2, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:849> Error decoding subfield FPC\n");
		ED_HANDLE_IE_SYNTAX_ERROR (849)
	} 
#endif
	Len += Ret;
	
	/* FromBit=3 */
	(*Destin).PowerLevel = EDBitsToInt (Buffer, CurrOfs+3, 5);
	Ret = 5;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:850> Error decoding subfield PowerLevel\n");
		ED_HANDLE_IE_SYNTAX_ERROR (850)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_RACHCtrlParam (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_RACHCtrlParam* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 24;
	EDIntToBits (Buffer, CurrOfs, (*Source).MaxRetrans, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:851> Error encoding subfield MaxRetrans\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+2, (*Source).Tx, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:852> Error encoding subfield Tx\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+6, ((*Source).CellBarrAccess != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:853> Error encoding subfield CellBarrAccess\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+7, ((*Source).RE != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:854> Error encoding subfield RE\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+8, ((*Source).AC_C15 != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:855> Error encoding subfield AC_C15\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+9, ((*Source).AC_C14 != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:856> Error encoding subfield AC_C14\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+10, ((*Source).AC_C13 != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:857> Error encoding subfield AC_C13\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+11, ((*Source).AC_C12 != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:858> Error encoding subfield AC_C12\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+12, ((*Source).AC_C11 != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:859> Error encoding subfield AC_C11\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+13, ((*Source).EC_C10 != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:860> Error encoding subfield EC_C10\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+14, ((*Source).AC_C09 != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:861> Error encoding subfield AC_C09\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+15, ((*Source).AC_C08 != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:862> Error encoding subfield AC_C08\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+16, ((*Source).AC_C07 != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:863> Error encoding subfield AC_C07\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+17, ((*Source).AC_C06 != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:864> Error encoding subfield AC_C06\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+18, ((*Source).AC_C05 != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:865> Error encoding subfield AC_C05\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+19, ((*Source).AC_C04 != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:866> Error encoding subfield AC_C04\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+20, ((*Source).AC_C03 != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:867> Error encoding subfield AC_C03\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+21, ((*Source).AC_C02 != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:868> Error encoding subfield AC_C02\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+22, ((*Source).AC_C01 != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:869> Error encoding subfield AC_C01\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+23, ((*Source).AC_C00 != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:870> Error encoding subfield AC_C00\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_RACHCtrlParam (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_RACHCtrlParam* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=0 */
	(*Destin).MaxRetrans = EDBitsToInt (Buffer, CurrOfs, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:871> Error decoding subfield MaxRetrans\n");
		ED_HANDLE_IE_SYNTAX_ERROR (871)
	} 
#endif
	Len += Ret;
	
	/* FromBit=2 */
	(*Destin).Tx = EDBitsToInt (Buffer, CurrOfs+2, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:872> Error decoding subfield Tx\n");
		ED_HANDLE_IE_SYNTAX_ERROR (872)
	} 
#endif
	Len += Ret;
	
	/* FromBit=6 */
	(*Destin).CellBarrAccess = (EDBitsToInt (Buffer, CurrOfs+6, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:873> Error decoding subfield CellBarrAccess\n");
		ED_HANDLE_IE_SYNTAX_ERROR (873)
	} 
#endif
	Len += Ret;
	
	/* FromBit=7 */
	(*Destin).RE = (EDBitsToInt (Buffer, CurrOfs+7, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:874> Error decoding subfield RE\n");
		ED_HANDLE_IE_SYNTAX_ERROR (874)
	} 
#endif
	Len += Ret;
	
	/* FromBit=8 */
	(*Destin).AC_C15 = (EDBitsToInt (Buffer, CurrOfs+8, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:875> Error decoding subfield AC_C15\n");
		ED_HANDLE_IE_SYNTAX_ERROR (875)
	} 
#endif
	Len += Ret;
	
	/* FromBit=9 */
	(*Destin).AC_C14 = (EDBitsToInt (Buffer, CurrOfs+9, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:876> Error decoding subfield AC_C14\n");
		ED_HANDLE_IE_SYNTAX_ERROR (876)
	} 
#endif
	Len += Ret;
	
	/* FromBit=10 */
	(*Destin).AC_C13 = (EDBitsToInt (Buffer, CurrOfs+10, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:877> Error decoding subfield AC_C13\n");
		ED_HANDLE_IE_SYNTAX_ERROR (877)
	} 
#endif
	Len += Ret;
	
	/* FromBit=11 */
	(*Destin).AC_C12 = (EDBitsToInt (Buffer, CurrOfs+11, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:878> Error decoding subfield AC_C12\n");
		ED_HANDLE_IE_SYNTAX_ERROR (878)
	} 
#endif
	Len += Ret;
	
	/* FromBit=12 */
	(*Destin).AC_C11 = (EDBitsToInt (Buffer, CurrOfs+12, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:879> Error decoding subfield AC_C11\n");
		ED_HANDLE_IE_SYNTAX_ERROR (879)
	} 
#endif
	Len += Ret;
	
	/* FromBit=13 */
	(*Destin).EC_C10 = (EDBitsToInt (Buffer, CurrOfs+13, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:880> Error decoding subfield EC_C10\n");
		ED_HANDLE_IE_SYNTAX_ERROR (880)
	} 
#endif
	Len += Ret;
	
	/* FromBit=14 */
	(*Destin).AC_C09 = (EDBitsToInt (Buffer, CurrOfs+14, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:881> Error decoding subfield AC_C09\n");
		ED_HANDLE_IE_SYNTAX_ERROR (881)
	} 
#endif
	Len += Ret;
	
	/* FromBit=15 */
	(*Destin).AC_C08 = (EDBitsToInt (Buffer, CurrOfs+15, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:882> Error decoding subfield AC_C08\n");
		ED_HANDLE_IE_SYNTAX_ERROR (882)
	} 
#endif
	Len += Ret;
	
	/* FromBit=16 */
	(*Destin).AC_C07 = (EDBitsToInt (Buffer, CurrOfs+16, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:883> Error decoding subfield AC_C07\n");
		ED_HANDLE_IE_SYNTAX_ERROR (883)
	} 
#endif
	Len += Ret;
	
	/* FromBit=17 */
	(*Destin).AC_C06 = (EDBitsToInt (Buffer, CurrOfs+17, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:884> Error decoding subfield AC_C06\n");
		ED_HANDLE_IE_SYNTAX_ERROR (884)
	} 
#endif
	Len += Ret;
	
	/* FromBit=18 */
	(*Destin).AC_C05 = (EDBitsToInt (Buffer, CurrOfs+18, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:885> Error decoding subfield AC_C05\n");
		ED_HANDLE_IE_SYNTAX_ERROR (885)
	} 
#endif
	Len += Ret;
	
	/* FromBit=19 */
	(*Destin).AC_C04 = (EDBitsToInt (Buffer, CurrOfs+19, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:886> Error decoding subfield AC_C04\n");
		ED_HANDLE_IE_SYNTAX_ERROR (886)
	} 
#endif
	Len += Ret;
	
	/* FromBit=20 */
	(*Destin).AC_C03 = (EDBitsToInt (Buffer, CurrOfs+20, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:887> Error decoding subfield AC_C03\n");
		ED_HANDLE_IE_SYNTAX_ERROR (887)
	} 
#endif
	Len += Ret;
	
	/* FromBit=21 */
	(*Destin).AC_C02 = (EDBitsToInt (Buffer, CurrOfs+21, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:888> Error decoding subfield AC_C02\n");
		ED_HANDLE_IE_SYNTAX_ERROR (888)
	} 
#endif
	Len += Ret;
	
	/* FromBit=22 */
	(*Destin).AC_C01 = (EDBitsToInt (Buffer, CurrOfs+22, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:889> Error decoding subfield AC_C01\n");
		ED_HANDLE_IE_SYNTAX_ERROR (889)
	} 
#endif
	Len += Ret;
	
	/* FromBit=23 */
	(*Destin).AC_C00 = (EDBitsToInt (Buffer, CurrOfs+23, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:890> Error decoding subfield AC_C00\n");
		ED_HANDLE_IE_SYNTAX_ERROR (890)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_RequestReference (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_RequestReference* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 24;
	EDIntToBits (Buffer, CurrOfs, (*Source).RA, 8);
	Ret = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:891> Error encoding subfield RA\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+8, (*Source).T1, 5);
	Ret = 5;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:892> Error encoding subfield T1\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+13, (*Source).T3, 6);
	Ret = 6;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:893> Error encoding subfield T3\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+19, (*Source).T2, 5);
	Ret = 5;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:894> Error encoding subfield T2\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_RequestReference (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_RequestReference* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=0 */
	(*Destin).RA = EDBitsToInt (Buffer, CurrOfs, 8);
	Ret = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:895> Error decoding subfield RA\n");
		ED_HANDLE_IE_SYNTAX_ERROR (895)
	} 
#endif
	Len += Ret;
	
	/* FromBit=8 */
	(*Destin).T1 = EDBitsToInt (Buffer, CurrOfs+8, 5);
	Ret = 5;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:896> Error decoding subfield T1\n");
		ED_HANDLE_IE_SYNTAX_ERROR (896)
	} 
#endif
	Len += Ret;
	
	/* FromBit=13 */
	(*Destin).T3 = EDBitsToInt (Buffer, CurrOfs+13, 6);
	Ret = 6;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:897> Error decoding subfield T3\n");
		ED_HANDLE_IE_SYNTAX_ERROR (897)
	} 
#endif
	Len += Ret;
	
	/* FromBit=19 */
	(*Destin).T2 = EDBitsToInt (Buffer, CurrOfs+19, 5);
	Ret = 5;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:898> Error decoding subfield T2\n");
		ED_HANDLE_IE_SYNTAX_ERROR (898)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_StartingTime (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_StartingTime* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 16;
	EDIntToBits (Buffer, CurrOfs, (*Source).T1, 5);
	Ret = 5;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:899> Error encoding subfield T1\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+5, (*Source).T3, 6);
	Ret = 6;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:900> Error encoding subfield T3\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+11, (*Source).T2, 5);
	Ret = 5;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:901> Error encoding subfield T2\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_StartingTime (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_StartingTime* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=0 */
	(*Destin).T1 = EDBitsToInt (Buffer, CurrOfs, 5);
	Ret = 5;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:902> Error decoding subfield T1\n");
		ED_HANDLE_IE_SYNTAX_ERROR (902)
	} 
#endif
	Len += Ret;
	
	/* FromBit=5 */
	(*Destin).T3 = EDBitsToInt (Buffer, CurrOfs+5, 6);
	Ret = 6;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:903> Error decoding subfield T3\n");
		ED_HANDLE_IE_SYNTAX_ERROR (903)
	} 
#endif
	Len += Ret;
	
	/* FromBit=11 */
	(*Destin).T2 = EDBitsToInt (Buffer, CurrOfs+11, 5);
	Ret = 5;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:904> Error decoding subfield T2\n");
		ED_HANDLE_IE_SYNTAX_ERROR (904)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_SyncInd (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_SyncInd* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 4;
	EDIntToBits (Buffer, CurrOfs, ((*Source).NCI != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:905> Error encoding subfield NCI\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+1, ((*Source).ROT != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:906> Error encoding subfield ROT\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+2, (*Source).SI, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:907> Error encoding subfield SI\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_SyncInd (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SyncInd* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=0 */
	(*Destin).NCI = (EDBitsToInt (Buffer, CurrOfs, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:908> Error decoding subfield NCI\n");
		ED_HANDLE_IE_SYNTAX_ERROR (908)
	} 
#endif
	Len += Ret;
	
	/* FromBit=1 */
	(*Destin).ROT = (EDBitsToInt (Buffer, CurrOfs+1, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:909> Error decoding subfield ROT\n");
		ED_HANDLE_IE_SYNTAX_ERROR (909)
	} 
#endif
	Len += Ret;
	
	/* FromBit=2 */
	(*Destin).SI = EDBitsToInt (Buffer, CurrOfs+2, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:910> Error decoding subfield SI\n");
		ED_HANDLE_IE_SYNTAX_ERROR (910)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_TimingAdvance (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_TimingAdvance* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 8;
	EDIntToBits (Buffer, CurrOfs, 0, 2);Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:911> Error encoding subfield spare\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+2, (*Source).value, 6);
	Ret = 6;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:912> Error encoding subfield value\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_TimingAdvance (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_TimingAdvance* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=0 */
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:913> Error decoding subfield spare\n");
		ED_HANDLE_IE_SYNTAX_ERROR (913)
	} 
#endif
	Len += Ret;
	
	/* FromBit=2 */
	(*Destin).value = EDBitsToInt (Buffer, CurrOfs+2, 6);
	Ret = 6;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:914> Error decoding subfield value\n");
		ED_HANDLE_IE_SYNTAX_ERROR (914)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_VGCSTargeModeIndication (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_VGCSTargeModeIndication* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 8;
	EDIntToBits (Buffer, CurrOfs, (*Source).TargetMode, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:915> Error encoding subfield TargetMode\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+2, (*Source).GroupCipherKeyNumber, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:916> Error encoding subfield GroupCipherKeyNumber\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs+6, 0, 2);Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:917> Error encoding subfield spare\n");
		return -1;
	} 
#endif

	return Len;
}
long DECODE_c_VGCSTargeModeIndication (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_VGCSTargeModeIndication* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=0 */
	(*Destin).TargetMode = EDBitsToInt (Buffer, CurrOfs, 2);
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:918> Error decoding subfield TargetMode\n");
		ED_HANDLE_IE_SYNTAX_ERROR (918)
	} 
#endif
	Len += Ret;
	
	/* FromBit=2 */
	(*Destin).GroupCipherKeyNumber = EDBitsToInt (Buffer, CurrOfs+2, 4);
	Ret = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:919> Error decoding subfield GroupCipherKeyNumber\n");
		ED_HANDLE_IE_SYNTAX_ERROR (919)
	} 
#endif
	Len += Ret;
	
	/* FromBit=6 */
	Ret = 2;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:920> Error decoding subfield spare\n");
		ED_HANDLE_IE_SYNTAX_ERROR (920)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_ExtMeasurementResults (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_ExtMeasurementResults* ED_CONST Source)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	Len = 2;
	EDIntToBits (Buffer, CurrOfs+1, ((*Source).DTXUsed != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:921> Error encoding subfield DTXUsed\n");
		return -1;
	} 
#endif
	EDIntToBits (Buffer, CurrOfs, ((*Source).SCUsed != 0 ? 1 : 0), 1);Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:922> Error encoding subfield SCUsed\n");
		return -1;
	} 
#endif
	Ret = ENCODE_c_TRXLEVCarriers (Buffer, CurrOfs+2, &((*Source).RXLEVCarriers));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:923> Error encoding subfield RXLEVCarriers\n");
		return -1;
	} 
#endif
	Len += Ret;

	return Len;
}
long DECODE_c_ExtMeasurementResults (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_ExtMeasurementResults* ED_CONST Destin, long Length)
{
	long Len = 0, Ret = 0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	/* FromBit=1 */
	(*Destin).DTXUsed = (EDBitsToInt (Buffer, CurrOfs+1, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:924> Error decoding subfield DTXUsed\n");
		ED_HANDLE_IE_SYNTAX_ERROR (924)
	} 
#endif
	Len += Ret;
	
	/* FromBit=0 */
	(*Destin).SCUsed = (EDBitsToInt (Buffer, CurrOfs, 1) != 0 ? ED_TRUE : ED_FALSE);
	Ret = 1;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:925> Error decoding subfield SCUsed\n");
		ED_HANDLE_IE_SYNTAX_ERROR (925)
	} 
#endif
	Len += Ret;
	
	/* FromBit=2 */
	Ret = DECODE_c_TRXLEVCarriers (Buffer, CurrOfs+2, &((*Destin).RXLEVCarriers), (Length - 2));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Ret < 0) {
		ED_SIGNAL_ERROR ("<ERRID:926> Error decoding subfield RXLEVCarriers\n");
		ED_HANDLE_IE_SYNTAX_ERROR (926)
	} 
#endif
	Len += Ret;
	

	return Len;
}
long ENCODE_c_IncSkipOfARFCN (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_IncSkipOfARFCN* ED_CONST Source)
{
	int i;
	long length = 0, ret=0;
	long CurrOfs = BitOffset;
	for (i=0; i<(*Source).items; i++) {

		EDIntToBits (Buffer, CurrOfs, Source->data[i], 4);
		length = 4;

#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (length < 0) {
			ED_SIGNAL_ERROR ("<ERRID:927> Error encoding sequence IncSkipOfARFCN\n");
			return -1;
		} 
#endif

		CurrOfs += length;
		ret += length;
	}
	return ret;
}
long DECODE_c_IncSkipOfARFCN (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_IncSkipOfARFCN* ED_CONST Destin, long Length)
{
	int i;
	long ret=0, len=0;
	long CurrOfs = BitOffset;
	Destin->items = 0;
	for (i=0; (i<16) && (Length>0); i++) {
		SETITEMS_c_IncSkipOfARFCN (Destin, i+1)
;


		Destin->data[i] = EDBitsToInt (Buffer, CurrOfs, 4);
		ret = 4;

#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:928> Error decoding sequence IncSkipOfARFCN\n");
			ED_HANDLE_IE_SYNTAX_ERROR (928)
		} 
#endif
		len += ret;
		CurrOfs += ret;
		Length -= ret;
	}
	return len;
}
long ENCODE_c_GrpChannelMA (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_GrpChannelMA* ED_CONST Source)
{
	int i;
	long length = 0, ret=0;
	long CurrOfs = BitOffset;
	for (i=0; i<(*Source).items; i++) {

		EDIntToBits (Buffer, CurrOfs, (Source->data[i] != 0 ? 1 : 0), 1);length = 1;

#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (length < 0) {
			ED_SIGNAL_ERROR ("<ERRID:929> Error encoding sequence GrpChannelMA\n");
			return -1;
		} 
#endif

		CurrOfs += length;
		ret += length;
	}
	return ret;
}
long DECODE_c_GrpChannelMA (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_GrpChannelMA* ED_CONST Destin, long Length)
{
	int i;
	long ret=0, len=0;
	long CurrOfs = BitOffset;
	Destin->items = 0;
	for (i=0; (i<72) && (Length>0); i++) {
		SETITEMS_c_GrpChannelMA (Destin, i+1)
;


		Destin->data[i] = (EDBitsToInt (Buffer, CurrOfs, 1) != 0 ? ED_TRUE : ED_FALSE);
		ret = 1;

#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:930> Error decoding sequence GrpChannelMA\n");
			ED_HANDLE_IE_SYNTAX_ERROR (930)
		} 
#endif
		len += ret;
		CurrOfs += ret;
		Length -= ret;
	}
	return len;
}
long ENCODE_c_MeasurementResultsList (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_MeasurementResultsList* ED_CONST Source)
{
	int i;
	long length = 0, ret=0;
	long CurrOfs = BitOffset;
	for (i=0; i<(*Source).items; i++) {

		length = ENCODE_c_MeasurementSingleResult (Buffer, CurrOfs, &(Source->data[i]));

#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (length < 0) {
			ED_SIGNAL_ERROR ("<ERRID:931> Error encoding sequence MeasurementResultsList\n");
			return -1;
		} 
#endif

		CurrOfs += length;
		ret += length;
	}
	return ret;
}
long DECODE_c_MeasurementResultsList (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_MeasurementResultsList* ED_CONST Destin, long Length)
{
	int i;
	long ret=0, len=0;
	long CurrOfs = BitOffset;
	Destin->items = 0;
	for (i=0; (i<6) && (Length>0); i++) {
		SETITEMS_c_MeasurementResultsList (Destin, i+1)
;


		ret = DECODE_c_MeasurementSingleResult (Buffer, CurrOfs, &(Destin->data[i]), Length);

#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:932> Error decoding sequence MeasurementResultsList\n");
			ED_HANDLE_IE_SYNTAX_ERROR (932)
		} 
#endif
		len += ret;
		CurrOfs += ret;
		Length -= ret;
	}
	return len;
}
long ENCODE_c_MobileAllocation (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_MobileAllocation* ED_CONST Source)
{
	int i;
	long length = 0, ret=0;
	long CurrOfs = BitOffset;
	for (i=0; i<(*Source).items; i++) {

		EDIntToBits (Buffer, CurrOfs, (Source->data[i] != 0 ? 1 : 0), 1);length = 1;

#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (length < 0) {
			ED_SIGNAL_ERROR ("<ERRID:933> Error encoding sequence MobileAllocation\n");
			return -1;
		} 
#endif

		CurrOfs += length;
		ret += length;
	}
	return ret;
}
long DECODE_c_MobileAllocation (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_MobileAllocation* ED_CONST Destin, long Length)
{
	int i;
	long ret=0, len=0;
	long CurrOfs = BitOffset;
	Destin->items = 0;
	for (i=0; (i<64) && (Length>0); i++) {
		SETITEMS_c_MobileAllocation (Destin, i+1)
;


		Destin->data[i] = (EDBitsToInt (Buffer, CurrOfs, 1) != 0 ? ED_TRUE : ED_FALSE);
		ret = 1;

#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:934> Error decoding sequence MobileAllocation\n");
			ED_HANDLE_IE_SYNTAX_ERROR (934)
		} 
#endif
		len += ret;
		CurrOfs += ret;
		Length -= ret;
	}
	return len;
}
long ENCODE_c_NeighbourCellDescription (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_NeighbourCellDescription* ED_CONST Source)
{
	int i;
	long length = 0, ret=0;
	long CurrOfs = BitOffset;
	for (i=0; i<128; i++) {

		EDIntToBits (Buffer, CurrOfs, (Source->data[i] != 0 ? 1 : 0), 1);length = 1;

#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (length < 0) {
			ED_SIGNAL_ERROR ("<ERRID:935> Error encoding sequence NeighbourCellDescription\n");
			return -1;
		} 
#endif

		CurrOfs += length;
		ret += length;
	}
	return ret;
}
long DECODE_c_NeighbourCellDescription (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_NeighbourCellDescription* ED_CONST Destin, long Length)
{
	int i;
	long ret=0, len=0;
	long CurrOfs = BitOffset;
	for (i=0; (i<128) && (Length>0); i++) {
;


		Destin->data[i] = (EDBitsToInt (Buffer, CurrOfs, 1) != 0 ? ED_TRUE : ED_FALSE);
		ret = 1;

#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:936> Error decoding sequence NeighbourCellDescription\n");
			ED_HANDLE_IE_SYNTAX_ERROR (936)
		} 
#endif
		len += ret;
		CurrOfs += ret;
		Length -= ret;
	}
	return len;
}
long ENCODE_c_NeighbourCellDescription2 (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_NeighbourCellDescription2* ED_CONST Source)
{
	int i;
	long length = 0, ret=0;
	long CurrOfs = BitOffset;
	for (i=0; i<128; i++) {

		EDIntToBits (Buffer, CurrOfs, (Source->data[i] != 0 ? 1 : 0), 1);length = 1;

#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (length < 0) {
			ED_SIGNAL_ERROR ("<ERRID:937> Error encoding sequence NeighbourCellDescription2\n");
			return -1;
		} 
#endif

		CurrOfs += length;
		ret += length;
	}
	return ret;
}
long DECODE_c_NeighbourCellDescription2 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_NeighbourCellDescription2* ED_CONST Destin, long Length)
{
	int i;
	long ret=0, len=0;
	long CurrOfs = BitOffset;
	for (i=0; (i<128) && (Length>0); i++) {
;


		Destin->data[i] = (EDBitsToInt (Buffer, CurrOfs, 1) != 0 ? ED_TRUE : ED_FALSE);
		ret = 1;

#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:938> Error decoding sequence NeighbourCellDescription2\n");
			ED_HANDLE_IE_SYNTAX_ERROR (938)
		} 
#endif
		len += ret;
		CurrOfs += ret;
		Length -= ret;
	}
	return len;
}
long ENCODE_c_TRXLEVCarriers (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_TRXLEVCarriers* ED_CONST Source)
{
	int i;
	long length = 0, ret=0;
	long CurrOfs = BitOffset;
	for (i=0; i<(*Source).items; i++) {

		EDIntToBits (Buffer, CurrOfs, Source->data[i], 6);
		length = 6;

#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (length < 0) {
			ED_SIGNAL_ERROR ("<ERRID:939> Error encoding sequence TRXLEVCarriers\n");
			return -1;
		} 
#endif

		CurrOfs += length;
		ret += length;
	}
	return ret;
}
long DECODE_c_TRXLEVCarriers (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_TRXLEVCarriers* ED_CONST Destin, long Length)
{
	int i;
	long ret=0, len=0;
	long CurrOfs = BitOffset;
	Destin->items = 0;
	for (i=0; (i<21) && (Length>0); i++) {
		SETITEMS_c_TRXLEVCarriers (Destin, i+1)
;


		Destin->data[i] = EDBitsToInt (Buffer, CurrOfs, 6);
		ret = 6;

#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (ret < 0) {
			ED_SIGNAL_ERROR ("<ERRID:940> Error decoding sequence TRXLEVCarriers\n");
			ED_HANDLE_IE_SYNTAX_ERROR (940)
		} 
#endif
		len += ret;
		CurrOfs += ret;
		Length -= ret;
	}
	return len;
}

long ENCODE_c_MobileId (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_MobileId* ED_CONST Source)
{
	long CurrOfs = BitOffset;

  	int i;

		if (Source->IdentityType == 4) {
	  	/* Push digit 1 */
 			PUSH_INT (0xf4, 8);

 			/* Push the values */
 			for (i=0; i<Source->IdentityDigit.items; i++) {
 				PUSH_INT (Source->IdentityDigit.data [i], 8);
 			}
			return (Source->IdentityDigit.items + 1) << 3;
		} else {

	  	/* Push digit 1 */
	 		PUSH_INT (Source->IdentityDigit.items == 0? 15 : Source->IdentityDigit.data [0], 4);

	 		/* Push odd/even indicator */
	  	PUSH_INT ((Source->IdentityDigit.items & 1) ? 1 : 0, 1);

	  	/* Push identity type */
	  	PUSH_INT (Source->IdentityType, 3);

	  	/* Push remaining digits */
	  	for (i=1; i<Source->IdentityDigit.items; i+=2) {
	  		PUSH_INT (i+1 >= Source->IdentityDigit.items? 15 : Source->IdentityDigit.data [i+1], 4);
	  		PUSH_INT (Source->IdentityDigit.data [i], 4);
	  	}
			return ((Source->IdentityDigit.items >> 1) << 3) + 8;
	  }
  
}

long DECODE_c_MobileId (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_MobileId* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;

  	int i, odd;

  	/* Shift digit 1 (we don't know yet whether it is valid or not) */
  	i = SHIFT_INT (4);

  	/* Shift odd indicator */
  	odd = SHIFT_INT (1);

		/* Now we know exactly how many items to expect */
  	Destin->IdentityDigit.items = (Length >> 2) - (odd ? 1 : 2);

  	/* Now we know whether digit 1 is valid or not */
  	if (Destin->IdentityDigit.items > 0) Destin->IdentityDigit.data [0] = i;

		/* Extract identity type */
		Destin->IdentityType = SHIFT_INT (3);

		/* If decoding a TMSI/P-TMSI, just get the following bytes */
		if (Destin->IdentityType == 4) {
			Destin->IdentityDigit.items = (Length>>3) - 1;
			for (i=0; i < Destin->IdentityDigit.items; i++) {
				Destin->IdentityDigit.data [i] = SHIFT_INT (8);
			}
		}
		else {
	  	/* Get the remaining digits */
	  	for (i=1; i < Destin->IdentityDigit.items; i+=2) {
	  		if (i+1 >= Destin->IdentityDigit.items) {
	  			SHIFT_INT (4); /* Discard it! */
	  		}
	  		else {
	  			Destin->IdentityDigit.data [i+1] = SHIFT_INT (4);
	  		}
	 			Destin->IdentityDigit.data [i] = SHIFT_INT (4);
	  	}
		}
		return Length;
  
}

long ENCODE_c_BaRange (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_BaRange* ED_CONST Source)
{
	long CurrOfs = BitOffset;

  	int i;

  	PUSH_INT (Source->items, 8);

  	/* Write the 10-bits fields */
  	for (i=0; i<Source->items; i++) {
  		PUSH_INT (Source->data [i].Lower, 10);
  		PUSH_INT (Source->data [i].Higher, 10);
  	}

  	/* Calculate how many bits are left to complete an octet */
  	i = 8 - (CURPOS & 7);
  	PUSH_INT (0, i);

		return CURPOS-BitOffset;
  
}

long DECODE_c_BaRange (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_BaRange* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;

  	int i;

  	Destin->items = SHIFT_INT (8);
  	/* Make sure we don't go out of range */
  	if (Destin->items > sizeof (Destin->data)/sizeof (Destin->data[0])) {
  		return ED_SYNTAX_ERROR;
  	}
  	/* Read the 10-bits fields */
  	for (i=0; i<Destin->items; i++) {
  		Destin->data [i].Lower = SHIFT_INT (10);
  		Destin->data [i].Higher = SHIFT_INT (10);
  	}

  	/* Calculate how many bits are left to complete an octet */
  	i = 8 - (CURPOS & 7);

  	CURPOS += i;

		return CURPOS-BitOffset;
  
}

long ENCODE_c_CellChannel (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CellChannel* ED_CONST Source)
{
	long CurrOfs = BitOffset;

  	int i, len;
  	switch (Source->Present) {
	   	/*---------------------------------------------------------
	  		DETECT BITMAP 0 FORMAT (signature 00XXX)
	  	---------------------------------------------------------*/
	  	case U_c_CellChannel_BitMap0: {
	  		PUSH_INT (0, 4); /* Signature */
	  		for (i=0; i<Source->u.BitMap0.items; i++) {
	  			PUSH_INT ((Source->u.BitMap0.data [i]? 1 : 0), 1);
	  		}
	  		break;
	  	}
	  	/*---------------------------------------------------------
	  		DETECT BITMAP 1024 RANGE (signature 10000XX)
	  	---------------------------------------------------------*/
	  	case U_c_CellChannel_Range1024: {
	  		PUSH_INT (0x10, 5); /*  Signature */

	  		PUSH_INT ((Source->u.Range1024.F0? 1 : 0), 1);

	  		for (i=0; i < Source->u.Range1024.W.items; i++) {
	  			if (i==0) len = 10;
	  			else if (i>=1 && i<=2) len = 9;
	  			else if (i>=3 && i<=6) len = 8;
	  			else if (i>=7 && i<=14) len = 7;
	  			else if (i>=15 && i<=30) len = 6;
	  			else if (i>=31 && i<=62) len = 5;
	  			else if (i>=63 && i<=126) len = 4;
	  			else len = 3;
	  			PUSH_INT (Source->u.Range1024.W.data [i], len);
	  		}
	  		break;
	  	}
	  	/*---------------------------------------------------------
	  		DETECT BITMAP 512 RANGE (signature 1000100)
	  	---------------------------------------------------------*/
	  	case U_c_CellChannel_Range512: {
	  		PUSH_INT (0x44, 7); /* Signature */

	  		PUSH_INT (Source->u.Range512.OrigARFCN, 10);

	  		for (i=0; i < Source->u.Range512.W.items; i++) {
	  			if (i==0) len = 9;
	  			else if (i>=1 && i<=2) len = 8;
	  			else if (i>=3 && i<=6) len = 7;
	  			else if (i>=7 && i<=14) len = 6;
	  			else if (i>=15 && i<=30) len = 5;
	  			else if (i>=31 && i<=62) len = 4;
	  			else if (i>=63 && i<=126) len = 3;
	  			else len = 2;
	  			PUSH_INT (Source->u.Range512.W.data [i], len);
	  		}

	  		break;
	  	}
	  	/*---------------------------------------------------------
	  		DETECT BITMAP 256 RANGE (signature 1000101)
	  	---------------------------------------------------------*/
	  	case U_c_CellChannel_Range256: {
	  		PUSH_INT (0x45, 7); /* Signature */

	  		PUSH_INT (Source->u.Range256.OrigARFCN, 10);

	  		for (i=0; i<Source->u.Range256.W.items; i++) {
	  			if (i==0) len = 8;
	  			else if (i>=1 && i<=2) len = 7;
	  			else if (i>=3 && i<=6) len = 6;
	  			else if (i>=7 && i<=14) len = 5;
	  			else if (i>=15 && i<=30) len = 4;
	  			else if (i>=31 && i<=62) len = 3;
	  			else if (i>=63 && i<=126) len = 2;
	  			else len = 1;
	  			PUSH_INT (Source->u.Range256.W.data [i], len);
	  		}

	  		break;
	  	}
	  	/*---------------------------------------------------------
	  		DETECT BITMAP 128 RANGE (signature 1000110)
	  	---------------------------------------------------------*/
	  	case U_c_CellChannel_Range128: {
	  		PUSH_INT (0x46, 7); /* Signature */

	  		PUSH_INT (Source->u.Range128.OrigARFCN, 10);

	  		for (i=0; i<Source->u.Range128.W.items; i++) {
	  			if (i==0) len = 7;
	  			else if (i>=1 && i<=2) len = 6;
	  			else if (i>=3 && i<=6) len = 5;
	  			else if (i>=7 && i<=14) len = 4;
	  			else if (i>=15 && i<=30) len = 3;
	  			else if (i>=31 && i<=62) len = 2;
	  			else len = 1;

	  			PUSH_INT (Source->u.Range128.W.data [i], len);
	  		}

	  		break;
	  	}
	  	/*---------------------------------------------------------
	  		DETECT BITMAP VARIABLE (signature 1000111)
	  	---------------------------------------------------------*/
	  	case U_c_CellChannel_Variable: {
	  		PUSH_INT (0x47, 7); /* Signature */

	  		PUSH_INT (Source->u.Variable.OrigARFCN, 10);

	  		for (i=0; i<Source->u.Variable.RRFCN.items; i++) {
	  			PUSH_INT (Source->u.Variable.RRFCN.data [i], 1);
	  		}

	  		break;
	  	}
	  	/*---------------------------------------------------------
	  		UNKNOWN CODING!
	  	---------------------------------------------------------*/
	  	default: return ED_SYNTAX_ERROR;
	  }

		/* Pad with zeroes */
		len = (8 - (CURPOS & 7)) & 7;
		if (len > 0) PUSH_INT (0, len);

		return CURPOS-BitOffset;
  
}

long DECODE_c_CellChannel (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CellChannel* ED_CONST Destin, long Length)
{
	long CurrOfs = BitOffset;

  	int i, len;

  	/* Determine which type of encoding we have */
  	int Signature = EDBitsToInt (Buffer, CURPOS, 7);

  	/* Make sure spare bits are set to 0 */
  	Signature &= 0x67;

  	/*---------------------------------------------------------
  		DETECT BITMAP 0 FORMAT (signature 00XXX)
  	---------------------------------------------------------*/
  	if ((Signature & 0x78) == 0) {
  		Destin->Present = U_c_CellChannel_BitMap0;
  		CURPOS += 4;
  		for (i=0; i<Length-4 && i < 124; i++) {
  			Destin->u.BitMap0.data [i] = SHIFT_INT (1);
  		}
 			Destin->u.BitMap0.items = i;
  	}
  	/*---------------------------------------------------------
  		DETECT BITMAP 1024 RANGE (signature 10000XX)
  	---------------------------------------------------------*/
  	else if ((Signature & 0x7C) == 0x40) {
  		Destin->Present = U_c_CellChannel_Range1024;
  		CURPOS += 5;
  		Destin->u.Range1024.F0 = SHIFT_INT (1);

  		for (i=0; i<64; i++) {
  			if (i==0) len = 10;
  			else if (i>=1 && i<=2) len = 9;
  			else if (i>=3 && i<=6) len = 8;
  			else if (i>=7 && i<=14) len = 7;
  			else if (i>=15 && i<=30) len = 6;
  			else if (i>=31 && i<=62) len = 5;
  			else if (i>=63 && i<=126) len = 4;
  			else len = 3;
  			if (CURPOS - BitOffset + len > Length) break;
  			Destin->u.Range1024.W.data [i] = SHIFT_INT (len);
  		}
 			Destin->u.Range1024.W.items = i;
  	}
  	/*---------------------------------------------------------
  		DETECT BITMAP 512 RANGE (signature 1000100)
  	---------------------------------------------------------*/
  	else if (Signature == 0x44) {
  		Destin->Present = U_c_CellChannel_Range512;
  		CURPOS += 7;
  		Destin->u.Range512.OrigARFCN = SHIFT_INT (10);

  		for (i=0; i<64; i++) {
  			if (i==0) len = 9;
  			else if (i>=1 && i<=2) len = 8;
  			else if (i>=3 && i<=6) len = 7;
  			else if (i>=7 && i<=14) len = 6;
  			else if (i>=15 && i<=30) len = 5;
  			else if (i>=31 && i<=62) len = 4;
  			else if (i>=63 && i<=126) len = 3;
  			else len = 2;
  			if (CURPOS - BitOffset + len > Length) break;
  			Destin->u.Range512.W.data [i] = SHIFT_INT (len);
  		}
 			Destin->u.Range512.W.items = i;
  	}
  	/*---------------------------------------------------------
  		DETECT BITMAP 256 RANGE (signature 1000101)
  	---------------------------------------------------------*/
  	else if (Signature == 0x45) {
  		Destin->Present = U_c_CellChannel_Range256;
  		CURPOS += 7;
  		Destin->u.Range256.OrigARFCN = SHIFT_INT (10);

  		for (i=0; i<64; i++) {
  			if (i==0) len = 8;
  			else if (i>=1 && i<=2) len = 7;
  			else if (i>=3 && i<=6) len = 6;
  			else if (i>=7 && i<=14) len = 5;
  			else if (i>=15 && i<=30) len = 4;
  			else if (i>=31 && i<=62) len = 3;
  			else if (i>=63 && i<=126) len = 2;
  			else len = 1;
  			if (CURPOS - BitOffset + len > Length) break;
  			Destin->u.Range256.W.data [i] = SHIFT_INT (len);
  		}
 			Destin->u.Range256.W.items = i;
  	}
  	/*---------------------------------------------------------
  		DETECT BITMAP 128 RANGE (signature 1000110)
  	---------------------------------------------------------*/
  	else if (Signature == 0x46) {
  		Destin->Present = U_c_CellChannel_Range128;
  		CURPOS += 7;

  		Destin->u.Range128.OrigARFCN = SHIFT_INT (10);

  		for (i=0; i<64; i++) {
  			if (i==0) len = 7;
  			else if (i>=1 && i<=2) len = 6;
  			else if (i>=3 && i<=6) len = 5;
  			else if (i>=7 && i<=14) len = 4;
  			else if (i>=15 && i<=30) len = 3;
  			else if (i>=31 && i<=62) len = 2;
  			else len = 1;
  			if (CURPOS - BitOffset + len > Length) break;
  			Destin->u.Range128.W.data [i] = SHIFT_INT (len);
  		}
 			Destin->u.Range128.W.items = i;
  	}
  	/*---------------------------------------------------------
  		DETECT BITMAP VARIABLE (signature 1000111)
  	---------------------------------------------------------*/
  	else if (Signature == 0x47) {
  		Destin->Present = U_c_CellChannel_Variable;
  		CURPOS += 7;

  		Destin->u.Variable.OrigARFCN = SHIFT_INT (10);
  		for (i=0; (CURPOS - BitOffset < Length) && i<111; i++) {
  			Destin->u.Variable.RRFCN.data [i] = SHIFT_INT (1);
  		}
  		Destin->u.Variable.RRFCN.items = i;
  	}
  	/*---------------------------------------------------------
  		UNKNOWN CODING!
  	---------------------------------------------------------*/
  	else {
  		return ED_SYNTAX_ERROR;
  	}

		return CURPOS - BitOffset + ((8 - (CURPOS & 7)) & 7);
  
}

/*****************************************************************************
 函 数 名  : GAS_ENCODIX_CheckGprsCellOptionExtVersion
 功能描述  : 该函数用于44.060协议中的12.24 GPRS Cell Options中的Extension Information域
             进行再次解码，以保证该部分解码的正确性
 输入参数  : c_SI13RestOctets_NoPBCCH_GPRS_Cell_Options *pstGprsCellOption
 输出参数  : 无
 返 回 值  : VOS_INT32
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2010年2月8日
    作    者   : f48555
    修改内容   : 新生成函数GSM_R6协议升级Phase2, 2010_02_08

*****************************************************************************/
ED_LONG GAS_ENCODIX_CheckGprsCellOptionExtVersion( c_SI13RestOctets_NoPBCCH_GPRS_Cell_Options *pstGprsCellOption )
{
    int                                             lMinR99Len      = 3;
    int                                             lMinR4Len       = 3;
    int                                             lMinR6Len       = 3;
    c_SI13RestOctets_NoPBCCH_GPRS_Cell_Options_ext  *pstGprsCellExt;
    
    /* 参考44.060 12.24 GPRS Cell Options */    
    /* Extension Information不存在 */
    if ( ED_FALSE == pstGprsCellOption->ext_Present )
    {
        return  ED_TRUE;
    }

    /* Extension Information存在 */
    pstGprsCellExt = &(pstGprsCellOption->ext);
    
    /* 如果存在EGPRS_PACKET_CHANNEL_REQUEST和BEP_PERIOD时，需要增加该部分R99长度 */
    if (( ED_TRUE == pstGprsCellExt->BEP_PERIOD_Present )
     && ( ED_TRUE == pstGprsCellExt->EGPRS_PACKET__CHANNEL_REQUEST_Present ))
    {
        lMinR99Len  +=  5;
    }

    /* 获取必需的最小R4长度 */
    lMinR4Len        =   lMinR99Len + 2;
  
    /* Extension Length小于必需的最小R99长度时，必然不包含R99及之后的部分，返回非法 */
    if ( pstGprsCellExt->Extension_Length < lMinR99Len )
    {
        return  ED_FALSE;
    }
    /* Extension Length小于必需的最小R4长度时，必然不包含R4及之后的部分 */
    else if ( pstGprsCellExt->Extension_Length < lMinR4Len )
    {
        /* 删除R4消息结构内容 */
        pstGprsCellExt->CCN_ACTIVE                                          =   0;
        pstGprsCellExt->NW_EXT_UTBF                                         =   0;

        /* 删除R6消息结构内容 */
        pstGprsCellExt->MULTIPLE_TBF_CAPABILITY                             =   0;
        pstGprsCellExt->EXT_UTBF_NO_DATA                                    =   0;
        pstGprsCellExt->DTM_ENHANCEMENTS_CAPABILITY                         =   0;
        pstGprsCellExt->MNCI_SUPPORT_Present                                =   ED_FALSE;
        pstGprsCellExt->DEDICATED_MODE_MBMS_NOTIFICATION_SUPPORT_Present    =   ED_FALSE;

        return  ED_TRUE;
    }
  
    /* 获取必需的最小R6长度 */
    lMinR6Len       =  lMinR4Len + 4;
    
    /* 如果存在MNCI_SUPPORT和DEDICATED_MODE_MBMS_NOTIFICATION_SUPPORT时，需要增加该部分R6长度 */
    if (( ED_TRUE == pstGprsCellExt->DEDICATED_MODE_MBMS_NOTIFICATION_SUPPORT_Present )
     && ( ED_TRUE == pstGprsCellExt->MNCI_SUPPORT_Present ))
    {
        lMinR6Len   +=  2;
    }
    
    /* Extension Length小于必需的最小R6长度时，必然不包含R6及之后的部分 */
    if ( pstGprsCellExt->Extension_Length < lMinR6Len )
    {
        /* 删除R6消息结构内容 */
        pstGprsCellExt->MULTIPLE_TBF_CAPABILITY                             =   0;
        pstGprsCellExt->EXT_UTBF_NO_DATA                                    =   0;
        pstGprsCellExt->DTM_ENHANCEMENTS_CAPABILITY                         =   0;
        pstGprsCellExt->MNCI_SUPPORT_Present                                =   ED_FALSE;
        pstGprsCellExt->DEDICATED_MODE_MBMS_NOTIFICATION_SUPPORT_Present    =   ED_FALSE;
    }
    
    return  ED_TRUE;
}

/*lint +e958*/
/*lint +e961*/
/*lint +e539*/
/*lint +e830*/
/*lint +e717*/
/*lint +e574*/
/*lint +e701*/
/*lint +e702*/
/*lint +e525*/
/*lint +e704*/
/*lint +e713*/
/*lint +e732*/
/*lint +e734*/
/*lint +e774*/
/*lint +e737*/


