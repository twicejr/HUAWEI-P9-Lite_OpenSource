/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.83
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#include "L3Uplink.h"
#include "ed_c_known_ie.h"
#include "ed_tlv.h"
#include "UserDefinedDataTypes.h"
#include "CSN1DataTypes.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_L3UPLINK_C
/*lint -e961*/
/*lint -e958*/
/*lint -e704*/
/*lint -e713*/
/*lint -e774*/

/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE ASSIGNMENT_COMPLETE
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_ASSIGNMENT_COMPLETE (char* Buffer, long BitOffset, const c_ASSIGNMENT_COMPLETE* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 41, 8);
		CurrOfs += 8;
	}
	
	
	/* Code for RrCause */
	{
		/* Append to buffer value part */
		EDIntToBits (Buffer, CurrOfs, Source->RrCause, 8);
		Len = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:271> Error encoding subfield RrCause\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE ASSIGNMENT_COMPLETE
-----------------------------------------------------------------*/
long ENCODE_c_ASSIGNMENT_COMPLETE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_ASSIGNMENT_COMPLETE* ED_CONST Source)
{
	return L3_ENCODE_c_ASSIGNMENT_COMPLETE (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE ASSIGNMENT_COMPLETE
-----------------------------------------------------------------*/
long ENCODE_BODY_c_ASSIGNMENT_COMPLETE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_ASSIGNMENT_COMPLETE* ED_CONST Source)
{
	return L3_ENCODE_c_ASSIGNMENT_COMPLETE (Buffer, BitOffset, Source, 1);
}

/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE ASSIGNMENT_FAILURE
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_ASSIGNMENT_FAILURE (char* Buffer, long BitOffset, const c_ASSIGNMENT_FAILURE* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 47, 8);
		CurrOfs += 8;
	}
	
	
	/* Code for RrCause */
	{
		/* Append to buffer value part */
		EDIntToBits (Buffer, CurrOfs, Source->RrCause, 8);
		Len = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:272> Error encoding subfield RrCause\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE ASSIGNMENT_FAILURE
-----------------------------------------------------------------*/
long ENCODE_c_ASSIGNMENT_FAILURE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_ASSIGNMENT_FAILURE* ED_CONST Source)
{
	return L3_ENCODE_c_ASSIGNMENT_FAILURE (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE ASSIGNMENT_FAILURE
-----------------------------------------------------------------*/
long ENCODE_BODY_c_ASSIGNMENT_FAILURE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_ASSIGNMENT_FAILURE* ED_CONST Source)
{
	return L3_ENCODE_c_ASSIGNMENT_FAILURE (Buffer, BitOffset, Source, 1);
}

/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CHANNEL_MODE_MODIFY_ACKNOWLEDGE
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE (char* Buffer, long BitOffset, const c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 23, 8);
		CurrOfs += 8;
	}
	
	
	/* Code for ChannelDescription */
	{
		/* Append to buffer value part */
		Len = ENCODE_c_TChDesc (Buffer, CurrOfs, &(Source->ChannelDescription));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:273> Error encoding subfield ChannelDescription\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ChannelMode */
	{
		/* Append to buffer value part */
		EDIntToBits (Buffer, CurrOfs, Source->ChannelMode, 8);
		Len = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:274> Error encoding subfield ChannelMode\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CHANNEL_MODE_MODIFY_ACKNOWLEDGE
-----------------------------------------------------------------*/
long ENCODE_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE* ED_CONST Source)
{
	return L3_ENCODE_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE CHANNEL_MODE_MODIFY_ACKNOWLEDGE
-----------------------------------------------------------------*/
long ENCODE_BODY_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE* ED_CONST Source)
{
	return L3_ENCODE_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE (Buffer, BitOffset, Source, 1);
}

/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CIPHERING_MODE_COMPLETE
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_CIPHERING_MODE_COMPLETE (char* Buffer, long BitOffset, const c_CIPHERING_MODE_COMPLETE* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 50, 8);
		CurrOfs += 8;
	}
	
	
	/* Code for MobileEquipmentId */
	{
		int TLV_Base = CurrOfs;
		if (Source->MobileEquipmentId_Present) {
			/* Append to buffer IEI tag 0x17 */
			EDIntToBits (Buffer, CurrOfs, 0x17, 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part */
			Len = ENCODE_c_MobileId (Buffer, CurrOfs+8, &(Source->MobileEquipmentId));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:275> Error encoding subfield MobileEquipmentId\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, TLV_Base, (CurrOfs - TLV_Base - 8) >> 3, 8);
		}
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CIPHERING_MODE_COMPLETE
-----------------------------------------------------------------*/
long ENCODE_c_CIPHERING_MODE_COMPLETE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CIPHERING_MODE_COMPLETE* ED_CONST Source)
{
	return L3_ENCODE_c_CIPHERING_MODE_COMPLETE (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE CIPHERING_MODE_COMPLETE
-----------------------------------------------------------------*/
long ENCODE_BODY_c_CIPHERING_MODE_COMPLETE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CIPHERING_MODE_COMPLETE* ED_CONST Source)
{
	return L3_ENCODE_c_CIPHERING_MODE_COMPLETE (Buffer, BitOffset, Source, 1);
}

/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CLASSMARK_CHANGE
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_CLASSMARK_CHANGE (char* Buffer, long BitOffset, const c_CLASSMARK_CHANGE* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 22, 8);
		CurrOfs += 8;
	}
	
	
	/* Code for MobileStationClassmark */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part */
		Len = ENCODE_c_MobileStationClassmark2 (Buffer, CurrOfs+8, &(Source->MobileStationClassmark));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:276> Error encoding subfield MobileStationClassmark\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, TLV_Base, (CurrOfs - TLV_Base - 8) >> 3, 8);
	}
	
	/* Code for AdditionalMobileStationClassmarkInfo */
	{
		int TLV_Base = CurrOfs;
		if (Source->AdditionalMobileStationClassmarkInfo_Present) {
			/* Append to buffer IEI tag 0x20 */
			EDIntToBits (Buffer, CurrOfs, 0x20, 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part */
			Len = ENCODE_c_Classmark3Value (Buffer, CurrOfs+8, &(Source->AdditionalMobileStationClassmarkInfo));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:277> Error encoding subfield AdditionalMobileStationClassmarkInfo\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, TLV_Base, (CurrOfs - TLV_Base - 8) >> 3, 8);
		}
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CLASSMARK_CHANGE
-----------------------------------------------------------------*/
long ENCODE_c_CLASSMARK_CHANGE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CLASSMARK_CHANGE* ED_CONST Source)
{
	return L3_ENCODE_c_CLASSMARK_CHANGE (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE CLASSMARK_CHANGE
-----------------------------------------------------------------*/
long ENCODE_BODY_c_CLASSMARK_CHANGE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CLASSMARK_CHANGE* ED_CONST Source)
{
	return L3_ENCODE_c_CLASSMARK_CHANGE (Buffer, BitOffset, Source, 1);
}

/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE GPRS_SUSPENSION_REQUEST
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_GPRS_SUSPENSION_REQUEST (char* Buffer, long BitOffset, const c_GPRS_SUSPENSION_REQUEST* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 52, 8);
		CurrOfs += 8;
	}
	
	
	/* Code for TemporaryLogicalLinkId */
	{
		/* Append to buffer value part */
		EDIntToBits (Buffer, CurrOfs, Source->TemporaryLogicalLinkId, 32);
		Len = 32;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:278> Error encoding subfield TemporaryLogicalLinkId\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for RouteingAreaId */
	{
		/* Append to buffer value part */
		Len = ENCODE_c_RoutingAreaIdenti (Buffer, CurrOfs, &(Source->RouteingAreaId));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:279> Error encoding subfield RouteingAreaId\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for SuspensionCause */
	{
		/* Append to buffer value part */
		EDIntToBits (Buffer, CurrOfs, Source->SuspensionCause, 8);
		Len = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:280> Error encoding subfield SuspensionCause\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE GPRS_SUSPENSION_REQUEST
-----------------------------------------------------------------*/
long ENCODE_c_GPRS_SUSPENSION_REQUEST (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_GPRS_SUSPENSION_REQUEST* ED_CONST Source)
{
	return L3_ENCODE_c_GPRS_SUSPENSION_REQUEST (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE GPRS_SUSPENSION_REQUEST
-----------------------------------------------------------------*/
long ENCODE_BODY_c_GPRS_SUSPENSION_REQUEST (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_GPRS_SUSPENSION_REQUEST* ED_CONST Source)
{
	return L3_ENCODE_c_GPRS_SUSPENSION_REQUEST (Buffer, BitOffset, Source, 1);
}

/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_COMPLETE
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_HANDOVER_COMPLETE (char* Buffer, long BitOffset, const c_HANDOVER_COMPLETE* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 44, 8);
		CurrOfs += 8;
	}
	
	
	/* Code for RrCause */
	{
		/* Append to buffer value part */
		EDIntToBits (Buffer, CurrOfs, Source->RrCause, 8);
		Len = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:281> Error encoding subfield RrCause\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for MobileObservedTimeDifference */
	{
		int TLV_Base = CurrOfs;
		if (Source->MobileObservedTimeDifference_Present) {
			/* Append to buffer IEI tag 0x77 */
			EDIntToBits (Buffer, CurrOfs, 0x77, 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part */
			Len = ENCODE_c_MobileTimeDiff (Buffer, CurrOfs+8, &(Source->MobileObservedTimeDifference));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:282> Error encoding subfield MobileObservedTimeDifference\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, TLV_Base, (CurrOfs - TLV_Base - 8) >> 3, 8);
		}
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_COMPLETE
-----------------------------------------------------------------*/
long ENCODE_c_HANDOVER_COMPLETE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_HANDOVER_COMPLETE* ED_CONST Source)
{
	return L3_ENCODE_c_HANDOVER_COMPLETE (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_COMPLETE
-----------------------------------------------------------------*/
long ENCODE_BODY_c_HANDOVER_COMPLETE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_HANDOVER_COMPLETE* ED_CONST Source)
{
	return L3_ENCODE_c_HANDOVER_COMPLETE (Buffer, BitOffset, Source, 1);
}

/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_FAILURE
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_HANDOVER_FAILURE (char* Buffer, long BitOffset, const c_HANDOVER_FAILURE* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 40, 8);
		CurrOfs += 8;
	}
	
	
	/* Code for RrCause */
	{
		/* Append to buffer value part */
		EDIntToBits (Buffer, CurrOfs, Source->RrCause, 8);
		Len = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:283> Error encoding subfield RrCause\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_FAILURE
-----------------------------------------------------------------*/
long ENCODE_c_HANDOVER_FAILURE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_HANDOVER_FAILURE* ED_CONST Source)
{
	return L3_ENCODE_c_HANDOVER_FAILURE (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_FAILURE
-----------------------------------------------------------------*/
long ENCODE_BODY_c_HANDOVER_FAILURE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_HANDOVER_FAILURE* ED_CONST Source)
{
	return L3_ENCODE_c_HANDOVER_FAILURE (Buffer, BitOffset, Source, 1);
}

/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE MEASUREMENT_REPORT
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_MEASUREMENT_REPORT (char* Buffer, long BitOffset, const c_MEASUREMENT_REPORT* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 21, 8);
		CurrOfs += 8;
	}
	
	
	/* Code for MeasurementResults */
	{
		/* Append to buffer value part */
		Len = ENCODE_c_MeasurementResults (Buffer, CurrOfs, &(Source->MeasurementResults));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:284> Error encoding subfield MeasurementResults\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE MEASUREMENT_REPORT
-----------------------------------------------------------------*/
long ENCODE_c_MEASUREMENT_REPORT (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_MEASUREMENT_REPORT* ED_CONST Source)
{
	return L3_ENCODE_c_MEASUREMENT_REPORT (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE MEASUREMENT_REPORT
-----------------------------------------------------------------*/
long ENCODE_BODY_c_MEASUREMENT_REPORT (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_MEASUREMENT_REPORT* ED_CONST Source)
{
	return L3_ENCODE_c_MEASUREMENT_REPORT (Buffer, BitOffset, Source, 1);
}

/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE PAGING_RESPONSE
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_PAGING_RESPONSE (char* Buffer, long BitOffset, const c_PAGING_RESPONSE* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 39, 8);
		CurrOfs += 8;
	}
	
	
	/* Code for CiphKeySequenceNum */
	{
		/* Append to buffer value part */
		Len = ENCODE_c_CipheringKeySequenceNumber (Buffer, (CurrOfs+4), &(Source->CiphKeySequenceNum));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:285> Error encoding subfield CiphKeySequenceNum\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for SpareHalfOctet */
	{
		/* Append to buffer value part */
		EDIntToBits (Buffer, (CurrOfs-4), 0, 4);Len = 4;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:286> Error encoding subfield SpareHalfOctet\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for MobileStationClassmark */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part */
		Len = ENCODE_c_MobileStationClassmark2 (Buffer, CurrOfs+8, &(Source->MobileStationClassmark));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:287> Error encoding subfield MobileStationClassmark\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, TLV_Base, (CurrOfs - TLV_Base - 8) >> 3, 8);
	}
	
	/* Code for MobileId */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part */
		Len = ENCODE_c_MobileId (Buffer, CurrOfs+8, &(Source->MobileId));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:288> Error encoding subfield MobileId\n");
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
	ENCODING FUNCTION FOR GSM-L3 MESSAGE PAGING_RESPONSE
-----------------------------------------------------------------*/
long ENCODE_c_PAGING_RESPONSE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_PAGING_RESPONSE* ED_CONST Source)
{
	return L3_ENCODE_c_PAGING_RESPONSE (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE PAGING_RESPONSE
-----------------------------------------------------------------*/
long ENCODE_BODY_c_PAGING_RESPONSE (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_PAGING_RESPONSE* ED_CONST Source)
{
	return L3_ENCODE_c_PAGING_RESPONSE (Buffer, BitOffset, Source, 1);
}

/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE RR_INITIALISATION_REQUEST
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_RR_INITIALISATION_REQUEST (char* Buffer, long BitOffset, const c_RR_INITIALISATION_REQUEST* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 60, 8);
		CurrOfs += 8;
	}
	
	
	/* Code for CiphKeySequenceNum */
	{
		/* Append to buffer value part */
		Len = ENCODE_c_CipheringKeySequenceNumber (Buffer, (CurrOfs+4), &(Source->CiphKeySequenceNum));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:289> Error encoding subfield CiphKeySequenceNum\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for MacModeAndChannelCodingReq */
	{
		/* Append to buffer value part */
		Len = ENCODE_c_MACModeAndChCodReq (Buffer, (CurrOfs-4), &(Source->MacModeAndChannelCodingReq));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:290> Error encoding subfield MacModeAndChannelCodingReq\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for MobileStationClassmark */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part */
		Len = ENCODE_c_MobileStationClassmark2 (Buffer, CurrOfs+8, &(Source->MobileStationClassmark));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:291> Error encoding subfield MobileStationClassmark\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, TLV_Base, (CurrOfs - TLV_Base - 8) >> 3, 8);
	}
	
	/* Code for Tlli */
	{
		/* Append to buffer value part */
		EDIntToBits (Buffer, CurrOfs, Source->Tlli, 32);
		Len = 32;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:292> Error encoding subfield Tlli\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ChannelReqDescription */
	{
		/* Append to buffer value part */
		Len = ENCODE_c_ChannelRequestDesc (Buffer, CurrOfs, &(Source->ChannelReqDescription));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:293> Error encoding subfield ChannelReqDescription\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for GprsMeasurementResults */
	{
		/* Append to buffer value part */
		Len = ENCODE_c_GPRSMeasurementResult (Buffer, CurrOfs, &(Source->GprsMeasurementResults));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:294> Error encoding subfield GprsMeasurementResults\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE RR_INITIALISATION_REQUEST
-----------------------------------------------------------------*/
long ENCODE_c_RR_INITIALISATION_REQUEST (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_RR_INITIALISATION_REQUEST* ED_CONST Source)
{
	return L3_ENCODE_c_RR_INITIALISATION_REQUEST (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE RR_INITIALISATION_REQUEST
-----------------------------------------------------------------*/
long ENCODE_BODY_c_RR_INITIALISATION_REQUEST (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_RR_INITIALISATION_REQUEST* ED_CONST Source)
{
	return L3_ENCODE_c_RR_INITIALISATION_REQUEST (Buffer, BitOffset, Source, 1);
}

/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE EXTENDED_MEASUREMENT_REPORT
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
long L3_ENCODE_c_EXTENDED_MEASUREMENT_REPORT (char* Buffer, long BitOffset, const c_EXTENDED_MEASUREMENT_REPORT* Source, int Mode)
{
	int Len=0;
	long CurrOfs = BitOffset ED_WARNING_REMOVER(+Len);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, CurrOfs, 54, 8);
		CurrOfs += 8;
	}
	
	
	/* Code for ExtendedMeasurementResults */
	{
		/* Append to buffer value part */
		Len = ENCODE_c_ExtMeasurementResults (Buffer, CurrOfs, &(Source->ExtendedMeasurementResults));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:295> Error encoding subfield ExtendedMeasurementResults\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE EXTENDED_MEASUREMENT_REPORT
-----------------------------------------------------------------*/
long ENCODE_c_EXTENDED_MEASUREMENT_REPORT (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_EXTENDED_MEASUREMENT_REPORT* ED_CONST Source)
{
	return L3_ENCODE_c_EXTENDED_MEASUREMENT_REPORT (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE EXTENDED_MEASUREMENT_REPORT
-----------------------------------------------------------------*/
long ENCODE_BODY_c_EXTENDED_MEASUREMENT_REPORT (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_EXTENDED_MEASUREMENT_REPORT* ED_CONST Source)
{
	return L3_ENCODE_c_EXTENDED_MEASUREMENT_REPORT (Buffer, BitOffset, Source, 1);
}

int Match_c_ASSIGNMENT_COMPLETE (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 41) /* message type */
	);
}

int Match_c_ASSIGNMENT_FAILURE (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 47) /* message type */
	);
}

int Match_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 23) /* message type */
	);
}

int Match_c_CIPHERING_MODE_COMPLETE (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 50) /* message type */
	);
}

int Match_c_CLASSMARK_CHANGE (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 22) /* message type */
	);
}

int Match_c_GPRS_SUSPENSION_REQUEST (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 52) /* message type */
	);
}

int Match_c_HANDOVER_COMPLETE (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 44) /* message type */
	);
}

int Match_c_HANDOVER_FAILURE (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 40) /* message type */
	);
}

int Match_c_MEASUREMENT_REPORT (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 21) /* message type */
	);
}

int Match_c_PAGING_RESPONSE (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 39) /* message type */
	);
}

int Match_c_RR_INITIALISATION_REQUEST (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 60) /* message type */
	);
}

int Match_c_EXTENDED_MEASUREMENT_REPORT (const char* Buffer, ED_CONST long BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 54) /* message type */
	);
}

/*lint +e958*/
/*lint +e961*/
/*lint +e704*/
/*lint +e713*/
/*lint +e774*/

