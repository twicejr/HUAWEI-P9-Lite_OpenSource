/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __UserDefinedDataTypes_cs0005_h
#define __UserDefinedDataTypes_cs0005_h
#include "ed_lib.h"
#include "ed_c_cs0005.h"
#include "ed_user.h"
#include "endec_configs_cs0005.h"
#if ED_COMMON_CRC != 0x328E3625 && ED_VERSION != 10152 && ED_VERSION != 10153
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.154
#endif


#ifdef __cplusplus
	extern "C" {
#endif

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "R_Orders".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_R_Orders (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_R_Orders* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_R_Orders (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_R_Orders* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "R_Base_Station_Challenge_Order".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_R_Base_Station_Challenge_Order (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_R_Base_Station_Challenge_Order* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_R_Base_Station_Challenge_Order (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_R_Base_Station_Challenge_Order* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "R_Service_Option_Request_Order".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_R_Service_Option_Request_Order (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_R_Service_Option_Request_Order* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_R_Service_Option_Request_Order (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_R_Service_Option_Request_Order* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "R_Service_Option_Response_Order".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_R_Service_Option_Response_Order (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_R_Service_Option_Response_Order* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_R_Service_Option_Response_Order (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_R_Service_Option_Response_Order* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "R_Mobile_Station_Reject_Order".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_R_Mobile_Station_Reject_Order (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_R_Mobile_Station_Reject_Order* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_R_Mobile_Station_Reject_Order (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_R_Mobile_Station_Reject_Order* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "R_Release_Order".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_R_Release_Order (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_R_Release_Order* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_R_Release_Order (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_R_Release_Order* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "R_Fast_Call_Setup_Order".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_R_Fast_Call_Setup_Order (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_R_Fast_Call_Setup_Order* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_R_Fast_Call_Setup_Order (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_R_Fast_Call_Setup_Order* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_2_7_4".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_2_7_4 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_2_7_4* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_2_7_4 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_2_7_4* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_2_7_4_encrypted".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_2_7_4_encrypted (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_2_7_4_encrypted* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_2_7_4_encrypted (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_2_7_4_encrypted* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Keypad_Facility".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Keypad_Facility (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Keypad_Facility* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Keypad_Facility (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Keypad_Facility* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Called_Party_Number".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Called_Party_Number (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Called_Party_Number* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Called_Party_Number (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Called_Party_Number* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Calling_Party_Number".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Calling_Party_Number (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Calling_Party_Number* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Calling_Party_Number (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Calling_Party_Number* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Call_Mode".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Call_Mode (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Call_Mode* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Call_Mode (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Call_Mode* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Terminal_Information".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Terminal_Information (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Terminal_Information* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Terminal_Information (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Terminal_Information* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Roaming_Information".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Roaming_Information (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Roaming_Information* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Roaming_Information (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Roaming_Information* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Roaming_Information_SID_NID_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Roaming_Information_SID_NID_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Roaming_Information_SID_NID_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Roaming_Information_SID_NID_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Roaming_Information_SID_NID_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Security_Status".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Security_Status (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Security_Status* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Security_Status (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Security_Status* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Connected_Number".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Connected_Number (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Connected_Number* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Connected_Number (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Connected_Number* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_IMSI".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_IMSI (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_IMSI* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_IMSI (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_IMSI* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_ESN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_ESN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_ESN* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_ESN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_ESN* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Band_Class_Information".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Band_Class_Information (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Band_Class_Information* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Band_Class_Information (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Band_Class_Information* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Power_Class_Information".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Power_Class_Information (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Power_Class_Information* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Power_Class_Information (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Power_Class_Information* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Operating_Mode_Information".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Operating_Mode_Information (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Operating_Mode_Information* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Operating_Mode_Information (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Operating_Mode_Information* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Service_Option_Information".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Service_Option_Information (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Service_Option_Information* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Service_Option_Information (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Service_Option_Information* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Service_Option_Information_Data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Service_Option_Information_Data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Service_Option_Information_Data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Service_Option_Information_Data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Service_Option_Information_Data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Multiplex_Option_Information".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Multiplex_Option_Information (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Multiplex_Option_Information* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Multiplex_Option_Information (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Multiplex_Option_Information* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Multiplex_Option_Information_Data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Multiplex_Option_Information_Data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Multiplex_Option_Information_Data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Multiplex_Option_Information_Data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Multiplex_Option_Information_Data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Service_Configuration_Information".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Service_Configuration_Information (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Service_Configuration_Information* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Service_Configuration_Information (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Service_Configuration_Information* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Service_Configuration_Information_CON_RECs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Service_Configuration_Information_CON_RECs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Service_Configuration_Information_CON_RECs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Service_Configuration_Information_CON_RECs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Service_Configuration_Information_CON_RECs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Service_Configuration_Information_FOR_SCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Service_Configuration_Information_FOR_SCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Service_Configuration_Information_FOR_SCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Service_Configuration_Information_FOR_SCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Service_Configuration_Information_FOR_SCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Service_Configuration_Information_REV_SCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Service_Configuration_Information_REV_SCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Service_Configuration_Information_REV_SCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Service_Configuration_Information_REV_SCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Service_Configuration_Information_REV_SCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Channel_Configuration_for_the_Supplemental_Channel".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Channel_Configuration_for_the_Supplemental_Channel (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Channel_Configuration_for_the_Supplemental_Channel* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Channel_Configuration_for_the_Supplemental_Channel (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Channel_Configuration_for_the_Supplemental_Channel* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Called_Party_Subaddress".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Called_Party_Subaddress (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Called_Party_Subaddress* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Called_Party_Subaddress (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Called_Party_Subaddress* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Calling_Party_Subaddress".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Calling_Party_Subaddress (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Calling_Party_Subaddress* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Calling_Party_Subaddress (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Calling_Party_Subaddress* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Connected_Subaddress".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Connected_Subaddress (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Connected_Subaddress* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Connected_Subaddress (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Connected_Subaddress* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Power_Control_Information".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Power_Control_Information (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Power_Control_Information* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Power_Control_Information (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Power_Control_Information* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_IMSI_M".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_IMSI_M (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_IMSI_M* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_IMSI_M (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_IMSI_M* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_IMSI_T".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_IMSI_T (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_IMSI_T* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_IMSI_T (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_IMSI_T* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Capability_Information".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Capability_Information (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Capability_Information* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Capability_Information (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Capability_Information* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Capability_Information_Blob_Rel6".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Capability_Information_Blob_Rel6 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Capability_Information_Blob_Rel6* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Capability_Information_Blob_Rel6 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Capability_Information_Blob_Rel6* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Capability_Information_Blob".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Capability_Information_Blob (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Capability_Information_Blob* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Capability_Information_Blob (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Capability_Information_Blob* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Extended_Record_Type_International".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Extended_Record_Type_International (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Extended_Record_Type_International* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Extended_Record_Type_International (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Extended_Record_Type_International* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Channel_Configuration_Capability_Information".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Channel_Configuration_Capability_Information (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Channel_Configuration_Capability_Information* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Channel_Configuration_Capability_Information (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Channel_Configuration_Capability_Information* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FCH_Type_Specific_Fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FCH_Type_Specific_Fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FCH_Type_Specific_Fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FCH_Type_Specific_Fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FCH_Type_Specific_Fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "DCCH_Type_Specific_Fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_DCCH_Type_Specific_Fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DCCH_Type_Specific_Fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_DCCH_Type_Specific_Fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DCCH_Type_Specific_Fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Channel_Configuration_Capability_Information_FOR_SCH_Type_specific_fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Channel_Configuration_Capability_Information_FOR_SCH_Type_specific_fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Channel_Configuration_Capability_Information_FOR_SCH_Type_specific_fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Channel_Configuration_Capability_Information_FOR_SCH_Type_specific_fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Channel_Configuration_Capability_Information_FOR_SCH_Type_specific_fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Channel_Configuration_Capability_Information_FOR_SCH_Type_specific_fields_FOR_SCH_Type_Specific_Fields_data_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Channel_Configuration_Capability_Information_FOR_SCH_Type_specific_fields_FOR_SCH_Type_Specific_Fields_data_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Channel_Configuration_Capability_Information_FOR_SCH_Type_specific_fields_FOR_SCH_Type_Specific_Fields_data_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Channel_Configuration_Capability_Information_FOR_SCH_Type_specific_fields_FOR_SCH_Type_Specific_Fields_data_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Channel_Configuration_Capability_Information_FOR_SCH_Type_specific_fields_FOR_SCH_Type_Specific_Fields_data_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Channel_Configuration_Capability_Information_REV_SCH_Type_specific_fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Channel_Configuration_Capability_Information_REV_SCH_Type_specific_fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Channel_Configuration_Capability_Information_REV_SCH_Type_specific_fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Channel_Configuration_Capability_Information_REV_SCH_Type_specific_fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Channel_Configuration_Capability_Information_REV_SCH_Type_specific_fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Channel_Configuration_Capability_Information_REV_SCH_Type_specific_fields_REV_SCH_Type_Specific_Fields_data_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Channel_Configuration_Capability_Information_REV_SCH_Type_specific_fields_REV_SCH_Type_Specific_Fields_data_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Channel_Configuration_Capability_Information_REV_SCH_Type_specific_fields_REV_SCH_Type_Specific_Fields_data_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Channel_Configuration_Capability_Information_REV_SCH_Type_specific_fields_REV_SCH_Type_Specific_Fields_data_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Channel_Configuration_Capability_Information_REV_SCH_Type_specific_fields_REV_SCH_Type_Specific_Fields_data_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FOR_PDCH_Type_Specific_Fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FOR_PDCH_Type_Specific_Fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FOR_PDCH_Type_Specific_Fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FOR_PDCH_Type_Specific_Fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FOR_PDCH_Type_Specific_Fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "REV_PDCH_Type_Specific_Fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_REV_PDCH_Type_Specific_Fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_REV_PDCH_Type_Specific_Fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_REV_PDCH_Type_Specific_Fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_REV_PDCH_Type_Specific_Fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FUNDICATED_BCMC_Type_Specific_Fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FUNDICATED_BCMC_Type_Specific_Fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FUNDICATED_BCMC_Type_Specific_Fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FUNDICATED_BCMC_Type_Specific_Fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FUNDICATED_BCMC_Type_Specific_Fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Extended_Multiplex_Option_Information".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Extended_Multiplex_Option_Information (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Extended_Multiplex_Option_Information* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Extended_Multiplex_Option_Information (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Extended_Multiplex_Option_Information* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Extended_Multiplex_Option_Information_MO_FOR_FCH_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Extended_Multiplex_Option_Information_MO_FOR_FCH_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Extended_Multiplex_Option_Information_MO_FOR_FCH_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Extended_Multiplex_Option_Information_MO_FOR_FCH_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Extended_Multiplex_Option_Information_MO_FOR_FCH_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Extended_Multiplex_Option_Information_MO_REV_FCH_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Extended_Multiplex_Option_Information_MO_REV_FCH_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Extended_Multiplex_Option_Information_MO_REV_FCH_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Extended_Multiplex_Option_Information_MO_REV_FCH_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Extended_Multiplex_Option_Information_MO_REV_FCH_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Extended_Multiplex_Option_Information_MO_FOR_SCH_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Extended_Multiplex_Option_Information_MO_FOR_SCH_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Extended_Multiplex_Option_Information_MO_FOR_SCH_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Extended_Multiplex_Option_Information_MO_FOR_SCH_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Extended_Multiplex_Option_Information_MO_FOR_SCH_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Extended_Multiplex_Option_Information_MO_REV_SCH_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Extended_Multiplex_Option_Information_MO_REV_SCH_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Extended_Multiplex_Option_Information_MO_REV_SCH_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Extended_Multiplex_Option_Information_MO_REV_SCH_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Extended_Multiplex_Option_Information_MO_REV_SCH_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Geo_Location_Capability".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Geo_Location_Capability (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Geo_Location_Capability* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Geo_Location_Capability (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Geo_Location_Capability* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Band_Subclass_Information".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Band_Subclass_Information (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Band_Subclass_Information* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Band_Subclass_Information (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Band_Subclass_Information* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Global_Emergency_Call".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Global_Emergency_Call (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Global_Emergency_Call* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Global_Emergency_Call (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Global_Emergency_Call* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Hook_Status".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Hook_Status (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Hook_Status* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Hook_Status (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Hook_Status* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_QoS_Parameters".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_QoS_Parameters (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_QoS_Parameters* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_QoS_Parameters (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_QoS_Parameters* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Encryption_Capability".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Encryption_Capability (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Encryption_Capability* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Encryption_Capability (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Encryption_Capability* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Signaling_Message_Integrity_Capability".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Signaling_Message_Integrity_Capability (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Signaling_Message_Integrity_Capability* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Signaling_Message_Integrity_Capability (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Signaling_Message_Integrity_Capability* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_UIM_ID".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_UIM_ID (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_UIM_ID* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_UIM_ID (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_UIM_ID* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_ESN_ME".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_ESN_ME (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_ESN_ME* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_ESN_ME (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_ESN_ME* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_MEID".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_MEID (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_MEID* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_MEID (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_MEID* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Extended_Keypad_Facility".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Extended_Keypad_Facility (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Extended_Keypad_Facility* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Extended_Keypad_Facility (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Extended_Keypad_Facility* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_SYNC_ID".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_SYNC_ID (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_SYNC_ID* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_SYNC_ID (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_SYNC_ID* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_SYNC_ID_SYNC_IDs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_SYNC_ID_SYNC_IDs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_SYNC_ID_SYNC_IDs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_SYNC_ID_SYNC_IDs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_SYNC_ID_SYNC_IDs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Extended_Terminal_Information".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Extended_Terminal_Information (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Extended_Terminal_Information* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Extended_Terminal_Information (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Extended_Terminal_Information* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Extended_Terminal_Information_SO_GROUP_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Extended_Terminal_Information_SO_GROUP_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Extended_Terminal_Information_SO_GROUP_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Extended_Terminal_Information_SO_GROUP_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Extended_Terminal_Information_SO_GROUP_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Extended_Service_Option_Information".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Extended_Service_Option_Information (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Extended_Service_Option_Information* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Extended_Service_Option_Information (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Extended_Service_Option_Information* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Extended_Service_Option_Information_supports_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Extended_Service_Option_Information_supports_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Extended_Service_Option_Information_supports_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Extended_Service_Option_Information_supports_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Extended_Service_Option_Information_supports_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Extended_Service_Option_Information_SO_GROUP_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Extended_Service_Option_Information_SO_GROUP_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Extended_Service_Option_Information_SO_GROUP_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Extended_Service_Option_Information_SO_GROUP_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Extended_Service_Option_Information_SO_GROUP_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Band_Class_and_Band_Subclass_Information".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Band_Class_and_Band_Subclass_Information (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Band_Class_and_Band_Subclass_Information* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Band_Class_and_Band_Subclass_Information (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Band_Class_and_Band_Subclass_Information* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Band_Class_and_Band_Subclass_Information_BAND_CLASS_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Band_Class_and_Band_Subclass_Information_BAND_CLASS_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Band_Class_and_Band_Subclass_Information_BAND_CLASS_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Band_Class_and_Band_Subclass_Information_BAND_CLASS_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Band_Class_and_Band_Subclass_Information_BAND_CLASS_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_EXT_UIM_ID".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_EXT_UIM_ID (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_EXT_UIM_ID* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_EXT_UIM_ID (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_EXT_UIM_ID* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_MEID_ME".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_MEID_ME (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_MEID_ME* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_MEID_ME (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_MEID_ME* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_Additional_Geo_Location_Capability".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_Additional_Geo_Location_Capability (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_Additional_Geo_Location_Capability* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_Additional_Geo_Location_Capability (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_Additional_Geo_Location_Capability* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RIR_MEID_SIG".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RIR_MEID_SIG (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RIR_MEID_SIG* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RIR_MEID_SIG (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RIR_MEID_SIG* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "R_InformationRecords".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_R_InformationRecords (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_R_InformationRecords* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_R_InformationRecords (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_R_InformationRecords* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "F_Orders".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_F_Orders (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_F_Orders* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_F_Orders (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_F_Orders* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "F_Base_Station_Challenge_Confirmation_Order".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_F_Base_Station_Challenge_Confirmation_Order (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_F_Base_Station_Challenge_Confirmation_Order* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_F_Base_Station_Challenge_Confirmation_Order (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_F_Base_Station_Challenge_Confirmation_Order* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "F_Service_Option_Request_Order".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_F_Service_Option_Request_Order (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_F_Service_Option_Request_Order* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_F_Service_Option_Request_Order (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_F_Service_Option_Request_Order* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "F_Service_Option_Response_Order".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_F_Service_Option_Response_Order (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_F_Service_Option_Response_Order* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_F_Service_Option_Response_Order (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_F_Service_Option_Response_Order* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "F_Status_Request_Order".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_F_Status_Request_Order (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_F_Status_Request_Order* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_F_Status_Request_Order (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_F_Status_Request_Order* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "F_Registration_Accepted_Order".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_F_Registration_Accepted_Order (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_F_Registration_Accepted_Order* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_F_Registration_Accepted_Order (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_F_Registration_Accepted_Order* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "F_Periodic_Pilot_Measurement_Request_Order".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_F_Periodic_Pilot_Measurement_Request_Order (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_F_Periodic_Pilot_Measurement_Request_Order* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_F_Periodic_Pilot_Measurement_Request_Order (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_F_Periodic_Pilot_Measurement_Request_Order* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "F_Retry_Order".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_F_Retry_Order (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_F_Retry_Order* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_F_Retry_Order (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_F_Retry_Order* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "F_Base_Station_Reject_Order".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_F_Base_Station_Reject_Order (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_F_Base_Station_Reject_Order* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_F_Base_Station_Reject_Order (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_F_Base_Station_Reject_Order* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "F_BCMC_Order".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_F_BCMC_Order (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_F_BCMC_Order* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_F_BCMC_Order (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_F_BCMC_Order* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "F_BCMC_Order_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_F_BCMC_Order_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_F_BCMC_Order_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_F_BCMC_Order_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_F_BCMC_Order_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "F_BCMC_Order_BCMC_PROGRAMSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_F_BCMC_Order_BCMC_PROGRAMSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_F_BCMC_Order_BCMC_PROGRAMSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_F_BCMC_Order_BCMC_PROGRAMSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_F_BCMC_Order_BCMC_PROGRAMSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "F_Fast_Call_Setup_Order".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_F_Fast_Call_Setup_Order (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_F_Fast_Call_Setup_Order* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_F_Fast_Call_Setup_Order (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_F_Fast_Call_Setup_Order* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "F_Service_Status_Order".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_F_Service_Status_Order (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_F_Service_Status_Order* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_F_Service_Status_Order (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_F_Service_Status_Order* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "F_Service_Status_Order_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_F_Service_Status_Order_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_F_Service_Status_Order_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_F_Service_Status_Order_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_F_Service_Status_Order_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "F_Location_Services_Order".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_F_Location_Services_Order (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_F_Location_Services_Order* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_F_Location_Services_Order (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_F_Location_Services_Order* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "F_EACH_Selective_Acknowledgment_Order".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_F_EACH_Selective_Acknowledgment_Order (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_F_EACH_Selective_Acknowledgment_Order* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_F_EACH_Selective_Acknowledgment_Order (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_F_EACH_Selective_Acknowledgment_Order* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_3_7_5".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_3_7_5 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_3_7_5* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_3_7_5 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_3_7_5* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_3_7_5_encrypted".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_3_7_5_encrypted (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_3_7_5_encrypted* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_3_7_5_encrypted (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_3_7_5_encrypted* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "F_InformationRecords".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_F_InformationRecords (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_F_InformationRecords* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_F_InformationRecords (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_F_InformationRecords* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PilotRecord_Pilot_Record_Type_Specific_Fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PilotRecord_Pilot_Record_Type_Specific_Fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PilotRecord_Pilot_Record_Type_Specific_Fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PilotRecord_Pilot_Record_Type_Specific_Fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PilotRecord_Pilot_Record_Type_Specific_Fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields_c01".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields_c01 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields_c01* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields_c01 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields_c01* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields_c02".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields_c02 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields_c02* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields_c02 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields_c02* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields_c03".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields_c03 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields_c03* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields_c03 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields_c03* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields_c04".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields_c04 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields_c04* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields_c04 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields_c04* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields_c05".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields_c05 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields_c05* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields_c05 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields_c05* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PilotRecord_Pilot_Record_Type_Specific_Fields_Type_specific_fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Display".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Display (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Display* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Display (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Display* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Called_Party_Number".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Called_Party_Number (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Called_Party_Number* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Called_Party_Number (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Called_Party_Number* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Calling_Party_Number".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Calling_Party_Number (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Calling_Party_Number* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Calling_Party_Number (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Calling_Party_Number* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Connected_Number".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Connected_Number (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Connected_Number* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Connected_Number (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Connected_Number* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Connected_Number_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Connected_Number_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Connected_Number_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Connected_Number_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Connected_Number_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Signal".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Signal (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Signal* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Signal (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Signal* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Message_Waiting".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Message_Waiting (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Message_Waiting* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Message_Waiting (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Message_Waiting* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Service_Configuration".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Service_Configuration (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Service_Configuration* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Service_Configuration (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Service_Configuration* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Service_Configuration_CON_RECs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Service_Configuration_CON_RECs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Service_Configuration_CON_RECs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Service_Configuration_CON_RECs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Service_Configuration_CON_RECs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Service_Configuration_FOR_SCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Service_Configuration_FOR_SCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Service_Configuration_FOR_SCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Service_Configuration_FOR_SCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Service_Configuration_FOR_SCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Service_Configuration_REV_SCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Service_Configuration_REV_SCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Service_Configuration_REV_SCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Service_Configuration_REV_SCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Service_Configuration_REV_SCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Channel_Configuration_for_the_Supplemental_Channel".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Channel_Configuration_for_the_Supplemental_Channel (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Channel_Configuration_for_the_Supplemental_Channel* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Channel_Configuration_for_the_Supplemental_Channel (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Channel_Configuration_for_the_Supplemental_Channel* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Called_Party_Subaddress".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Called_Party_Subaddress (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Called_Party_Subaddress* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Called_Party_Subaddress (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Called_Party_Subaddress* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Called_Party_Subaddress_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Called_Party_Subaddress_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Called_Party_Subaddress_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Called_Party_Subaddress_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Called_Party_Subaddress_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Calling_Party_Subaddress".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Calling_Party_Subaddress (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Calling_Party_Subaddress* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Calling_Party_Subaddress (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Calling_Party_Subaddress* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Calling_Party_Subaddress_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Calling_Party_Subaddress_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Calling_Party_Subaddress_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Calling_Party_Subaddress_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Calling_Party_Subaddress_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Connected_Subaddress".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Connected_Subaddress (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Connected_Subaddress* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Connected_Subaddress (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Connected_Subaddress* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Connected_Subaddress_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Connected_Subaddress_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Connected_Subaddress_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Connected_Subaddress_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Connected_Subaddress_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Redirecting_Number".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Redirecting_Number (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Redirecting_Number* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Redirecting_Number (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Redirecting_Number* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Redirecting_Number_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Redirecting_Number_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Redirecting_Number_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Redirecting_Number_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Redirecting_Number_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Redirecting_Subaddress".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Redirecting_Subaddress (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Redirecting_Subaddress* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Redirecting_Subaddress (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Redirecting_Subaddress* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Redirecting_Subaddress_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Redirecting_Subaddress_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Redirecting_Subaddress_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Redirecting_Subaddress_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Redirecting_Subaddress_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Meter_Pulses".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Meter_Pulses (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Meter_Pulses* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Meter_Pulses (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Meter_Pulses* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Parametric_Alerting".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Parametric_Alerting (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Parametric_Alerting* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Parametric_Alerting (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Parametric_Alerting* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Parametric_Alerting_GROUPSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Parametric_Alerting_GROUPSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Parametric_Alerting_GROUPSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Parametric_Alerting_GROUPSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Parametric_Alerting_GROUPSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Line_Control".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Line_Control (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Line_Control* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Line_Control (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Line_Control* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Extended_Display".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Extended_Display (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Extended_Display* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Extended_Display (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Extended_Display* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Extended_Display_data_01_data_data_02_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Extended_Display_data_01_data_data_02_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Extended_Display_data_01_data_data_02_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Extended_Display_data_01_data_data_02_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Extended_Display_data_01_data_data_02_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Extended_Display_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Extended_Display_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Extended_Display_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Extended_Display_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Extended_Display_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Extended_Record_Type_International".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Extended_Record_Type_International (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Extended_Record_Type_International* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Extended_Record_Type_International (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Extended_Record_Type_International* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_data_02_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_data_02_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_data_02_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_data_02_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_data_02_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_data_03_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_data_03_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_data_03_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_data_03_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_data_03_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_RECs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_RECs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_RECs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_RECs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_RECs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_data_04_data_data_05_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_data_04_data_data_05_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_data_04_data_data_05_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_data_04_data_data_05_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_data_04_data_data_05_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_data_04_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_data_04_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_data_04_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_data_04_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_data_04_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_data_06_data_data_07_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_data_06_data_data_07_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_data_06_data_data_07_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_data_06_data_data_07_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_data_06_data_data_07_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_data_06_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_data_06_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_data_06_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_data_06_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_data_06_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_data_10_data_ROWSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_data_10_data_ROWSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_data_10_data_ROWSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_data_10_data_ROWSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_data_10_data_ROWSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_data_10_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_data_10_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_data_10_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_data_10_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_data_10_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_PARTITION_TABLESs_data_ROWS_data_PARTITIONSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_PARTITION_TABLESs_data_ROWS_data_PARTITIONSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_PARTITION_TABLESs_data_ROWS_data_PARTITIONSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_PARTITION_TABLESs_data_ROWS_data_PARTITIONSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_PARTITION_TABLESs_data_ROWS_data_PARTITIONSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_PARTITION_TABLESs_data_ROWS_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_PARTITION_TABLESs_data_ROWS_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_PARTITION_TABLESs_data_ROWS_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_PARTITION_TABLESs_data_ROWS_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_PARTITION_TABLESs_data_ROWS_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_PARTITION_TABLESs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_PARTITION_TABLESs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_PARTITION_TABLESs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_PARTITION_TABLESs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_PARTITION_TABLESs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_BCMC_PROGRAMSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_BCMC_PROGRAMSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_BCMC_PROGRAMSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_BCMC_PROGRAMSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_BCMC_PROGRAMSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_data_12_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_data_12_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_data_12_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_data_12_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_data_12_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_data_13_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_data_13_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_data_13_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_data_13_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_data_13_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_data_14_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_data_14_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_data_14_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_data_14_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_data_14_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2_Type_specific_fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2_Type_specific_fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2_Type_specific_fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2_Type_specific_fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2_Type_specific_fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2_Type_specific_fields_field_0".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2_Type_specific_fields_field_0 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2_Type_specific_fields_field_0* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2_Type_specific_fields_field_0 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2_Type_specific_fields_field_0* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2_Type_specific_fields_field_1".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2_Type_specific_fields_field_1 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2_Type_specific_fields_field_1* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2_Type_specific_fields_field_1 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2_Type_specific_fields_field_1* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2_Type_specific_fields_field_2".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2_Type_specific_fields_field_2 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2_Type_specific_fields_field_2* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2_Type_specific_fields_field_2 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2_Type_specific_fields_field_2* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2_Type_specific_fields_field_3".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2_Type_specific_fields_field_3 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2_Type_specific_fields_field_3* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2_Type_specific_fields_field_3 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec2_Type_specific_fields_field_3* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCCH_EP_SIZE_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCCH_EP_SIZE_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCCH_EP_SIZE_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCCH_EP_SIZE_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCCH_EP_SIZE_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCCH_EP_SIZE_1_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCCH_EP_SIZE_1_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCCH_EP_SIZE_1_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCCH_EP_SIZE_1_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCCH_EP_SIZE_1_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCH_EP_SIZE_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCH_EP_SIZE_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCH_EP_SIZE_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCH_EP_SIZE_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCH_EP_SIZE_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCH_RETRX_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCH_RETRX_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCH_RETRX_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCH_RETRX_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCH_RETRX_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCH_EP_SIZE_1_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCH_EP_SIZE_1_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCH_EP_SIZE_1_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCH_EP_SIZE_1_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCH_EP_SIZE_1_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCH_EP_SIZE_1_data_REV_PDCH_RETRX_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCH_EP_SIZE_1_data_REV_PDCH_RETRX_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCH_EP_SIZE_1_data_REV_PDCH_RETRX_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCH_EP_SIZE_1_data_REV_PDCH_RETRX_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_rec_data_11_data_infoRec1_Type_specific_fields_REV_PDCH_EP_SIZE_1_data_REV_PDCH_RETRX_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Non_Negotiable_Service_Configuration_Record".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Non_Negotiable_Service_Configuration_Record (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Non_Negotiable_Service_Configuration_Record* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Non_Negotiable_Service_Configuration_Record (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Non_Negotiable_Service_Configuration_Record* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Multiple_Character_Extended_Display".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Multiple_Character_Extended_Display (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Multiple_Character_Extended_Display* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Multiple_Character_Extended_Display (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Multiple_Character_Extended_Display* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Multiple_Character_Extended_Display_data_01_data_RECORDs_data_FIELDSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Multiple_Character_Extended_Display_data_01_data_RECORDs_data_FIELDSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Multiple_Character_Extended_Display_data_01_data_RECORDs_data_FIELDSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Multiple_Character_Extended_Display_data_01_data_RECORDs_data_FIELDSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Multiple_Character_Extended_Display_data_01_data_RECORDs_data_FIELDSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Multiple_Character_Extended_Display_data_01_data_RECORDs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Multiple_Character_Extended_Display_data_01_data_RECORDs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Multiple_Character_Extended_Display_data_01_data_RECORDs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Multiple_Character_Extended_Display_data_01_data_RECORDs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Multiple_Character_Extended_Display_data_01_data_RECORDs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Multiple_Character_Extended_Display_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Multiple_Character_Extended_Display_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Multiple_Character_Extended_Display_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Multiple_Character_Extended_Display_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Multiple_Character_Extended_Display_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Call_Waiting_Indicator".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Call_Waiting_Indicator (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Call_Waiting_Indicator* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Call_Waiting_Indicator (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Call_Waiting_Indicator* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Enhanced_Multiple_Character_Extended_Display".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Enhanced_Multiple_Character_Extended_Display (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Enhanced_Multiple_Character_Extended_Display* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Enhanced_Multiple_Character_Extended_Display (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Enhanced_Multiple_Character_Extended_Display* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Enhanced_Multiple_Character_Extended_Display_DISPLAYSs_data_RECORDs_data_FIELDSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Enhanced_Multiple_Character_Extended_Display_DISPLAYSs_data_RECORDs_data_FIELDSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Enhanced_Multiple_Character_Extended_Display_DISPLAYSs_data_RECORDs_data_FIELDSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Enhanced_Multiple_Character_Extended_Display_DISPLAYSs_data_RECORDs_data_FIELDSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Enhanced_Multiple_Character_Extended_Display_DISPLAYSs_data_RECORDs_data_FIELDSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Enhanced_Multiple_Character_Extended_Display_DISPLAYSs_data_RECORDs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Enhanced_Multiple_Character_Extended_Display_DISPLAYSs_data_RECORDs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Enhanced_Multiple_Character_Extended_Display_DISPLAYSs_data_RECORDs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Enhanced_Multiple_Character_Extended_Display_DISPLAYSs_data_RECORDs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Enhanced_Multiple_Character_Extended_Display_DISPLAYSs_data_RECORDs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "InfoRec_Enhanced_Multiple_Character_Extended_Display_DISPLAYSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_InfoRec_Enhanced_Multiple_Character_Extended_Display_DISPLAYSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_InfoRec_Enhanced_Multiple_Character_Extended_Display_DISPLAYSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_InfoRec_Enhanced_Multiple_Character_Extended_Display_DISPLAYSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_InfoRec_Enhanced_Multiple_Character_Extended_Display_DISPLAYSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "STR_Type_specific_fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_STR_Type_specific_fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_STR_Type_specific_fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_STR_Type_specific_fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_STR_Type_specific_fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "STR_Type_specific_fields_BAND_CLASS".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_STR_Type_specific_fields_BAND_CLASS (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_STR_Type_specific_fields_BAND_CLASS* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_STR_Type_specific_fields_BAND_CLASS (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_STR_Type_specific_fields_BAND_CLASS* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "STR_Type_specific_fields_BAND_CLASS_and_OP_MODE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_STR_Type_specific_fields_BAND_CLASS_and_OP_MODE (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_STR_Type_specific_fields_BAND_CLASS_and_OP_MODE* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_STR_Type_specific_fields_BAND_CLASS_and_OP_MODE (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_STR_Type_specific_fields_BAND_CLASS_and_OP_MODE* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_SPM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_SPM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_SPM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_SPM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_SPM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_APM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_APM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_APM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_APM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_APM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_APM_ACCT_SOs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_APM_ACCT_SOs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_APM_ACCT_SOs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_APM_ACCT_SOs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_APM_ACCT_SOs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_APM_ACCT_SO_GRPs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_APM_ACCT_SO_GRPs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_APM_ACCT_SO_GRPs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_APM_ACCT_SO_GRPs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_APM_ACCT_SO_GRPs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_NLM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_NLM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_NLM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_NLM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_NLM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_NLM_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_NLM_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_NLM_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_NLM_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_NLM_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_CCLM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_CCLM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_CCLM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_CCLM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_CCLM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_CCLM_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_CCLM_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_CCLM_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_CCLM_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_CCLM_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ORDM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ORDM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ORDM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ORDM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ORDM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_CAM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_CAM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_CAM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_CAM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_CAM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_CAM_Additional_record_fields_c01".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_CAM_Additional_record_fields_c01 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_CAM_Additional_record_fields_c01* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_CAM_Additional_record_fields_c01 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_CAM_Additional_record_fields_c01* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_CAM_Additional_record_fields_c02_data_03_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_CAM_Additional_record_fields_c02_data_03_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_CAM_Additional_record_fields_c02_data_03_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_CAM_Additional_record_fields_c02_data_03_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_CAM_Additional_record_fields_c02_data_03_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_CAM_Additional_record_fields_c02".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_CAM_Additional_record_fields_c02 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_CAM_Additional_record_fields_c02* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_CAM_Additional_record_fields_c02 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_CAM_Additional_record_fields_c02* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_CAM_Additional_record_fields_c05".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_CAM_Additional_record_fields_c05 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_CAM_Additional_record_fields_c05* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_CAM_Additional_record_fields_c05 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_CAM_Additional_record_fields_c05* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_CAM_Additional_record_fields_c06".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_CAM_Additional_record_fields_c06 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_CAM_Additional_record_fields_c06* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_CAM_Additional_record_fields_c06 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_CAM_Additional_record_fields_c06* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_CAM_Additional_record_fields_c03".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_CAM_Additional_record_fields_c03 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_CAM_Additional_record_fields_c03* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_CAM_Additional_record_fields_c03 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_CAM_Additional_record_fields_c03* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_CAM_Additional_record_fields_c04_data_06_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_CAM_Additional_record_fields_c04_data_06_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_CAM_Additional_record_fields_c04_data_06_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_CAM_Additional_record_fields_c04_data_06_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_CAM_Additional_record_fields_c04_data_06_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_CAM_Additional_record_fields_c04".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_CAM_Additional_record_fields_c04 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_CAM_Additional_record_fields_c04* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_CAM_Additional_record_fields_c04 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_CAM_Additional_record_fields_c04* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_CAM_Additional_record_fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_CAM_Additional_record_fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_CAM_Additional_record_fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_CAM_Additional_record_fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_CAM_Additional_record_fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_DBM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_DBM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_DBM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_DBM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_DBM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_DBM_FIELDSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_DBM_FIELDSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_DBM_FIELDSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_DBM_FIELDSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_DBM_FIELDSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_AUCM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_AUCM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_AUCM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_AUCM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_AUCM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_SSDUM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_SSDUM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_SSDUM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_SSDUM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_SSDUM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_FNM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_FNM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_FNM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_FNM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_FNM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ESPM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ESPM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ESPM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ESPM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ESPM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ESPM_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ESPM_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ESPM_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ESPM_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ESPM_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ESPM_data_02_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ESPM_data_02_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ESPM_data_02_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ESPM_data_02_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ESPM_data_02_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ESPM_PDCCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ESPM_PDCCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ESPM_PDCCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ESPM_PDCCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ESPM_PDCCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ESPM_CAND_BAND_CLASSs_data_data_03_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ESPM_CAND_BAND_CLASSs_data_data_03_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ESPM_CAND_BAND_CLASSs_data_data_03_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ESPM_CAND_BAND_CLASSs_data_data_03_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ESPM_CAND_BAND_CLASSs_data_data_03_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ESPM_CAND_BAND_CLASSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ESPM_CAND_BAND_CLASSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ESPM_CAND_BAND_CLASSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ESPM_CAND_BAND_CLASSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ESPM_CAND_BAND_CLASSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ENLM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ENLM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ENLM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ENLM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ENLM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ENLM_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ENLM_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ENLM_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ENLM_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ENLM_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_STRQM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_STRQM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_STRQM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_STRQM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_STRQM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_STRQM_FIELDSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_STRQM_FIELDSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_STRQM_FIELDSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_STRQM_FIELDSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_STRQM_FIELDSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_SRDM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_SRDM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_SRDM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_SRDM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_SRDM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_SRDM_Type_specific_fields_1".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_SRDM_Type_specific_fields_1 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_SRDM_Type_specific_fields_1* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_SRDM_Type_specific_fields_1 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_SRDM_Type_specific_fields_1* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_SRDM_Type_specific_fields_2_CHANSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_SRDM_Type_specific_fields_2_CHANSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_SRDM_Type_specific_fields_2_CHANSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_SRDM_Type_specific_fields_2_CHANSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_SRDM_Type_specific_fields_2_CHANSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_SRDM_Type_specific_fields_2".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_SRDM_Type_specific_fields_2 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_SRDM_Type_specific_fields_2* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_SRDM_Type_specific_fields_2 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_SRDM_Type_specific_fields_2* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "GPM_Common_Fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_GPM_Common_Fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GPM_Common_Fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_GPM_Common_Fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GPM_Common_Fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GPM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GPM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GPM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GPM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GPM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GPM_enhanced".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GPM_enhanced (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GPM_enhanced* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GPM_enhanced (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GPM_enhanced* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GSRDM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GSRDM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GSRDM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GSRDM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GSRDM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GSRDM_Type_specific_fields_1".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GSRDM_Type_specific_fields_1 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GSRDM_Type_specific_fields_1* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GSRDM_Type_specific_fields_1 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GSRDM_Type_specific_fields_1* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GSRDM_Type_specific_fields_2_CHANSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GSRDM_Type_specific_fields_2_CHANSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GSRDM_Type_specific_fields_2_CHANSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GSRDM_Type_specific_fields_2_CHANSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GSRDM_Type_specific_fields_2_CHANSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GSRDM_Type_specific_fields_2".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GSRDM_Type_specific_fields_2 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GSRDM_Type_specific_fields_2* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GSRDM_Type_specific_fields_2 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GSRDM_Type_specific_fields_2* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_TASM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_TASM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_TASM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_TASM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_TASM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_PACAM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_PACAM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_PACAM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_PACAM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_PACAM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM_Additional_record_fields_c000_PILOTSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM_Additional_record_fields_c000_PILOTSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM_Additional_record_fields_c000_PILOTSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM_Additional_record_fields_c000_PILOTSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM_Additional_record_fields_c000_PILOTSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM_Additional_record_fields_c000".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM_Additional_record_fields_c000 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM_Additional_record_fields_c000* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM_Additional_record_fields_c000 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM_Additional_record_fields_c000* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM_Additional_record_fields_c001_PILOTSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM_Additional_record_fields_c001_PILOTSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM_Additional_record_fields_c001_PILOTSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM_Additional_record_fields_c001_PILOTSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM_Additional_record_fields_c001_PILOTSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM_Additional_record_fields_c001".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM_Additional_record_fields_c001 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM_Additional_record_fields_c001* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM_Additional_record_fields_c001 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM_Additional_record_fields_c001* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01_PILOTSs_1_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01_PILOTSs_1_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01_PILOTSs_1_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01_PILOTSs_1_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01_PILOTSs_1_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01_PILOTSs_2_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01_PILOTSs_2_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01_PILOTSs_2_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01_PILOTSs_2_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01_PILOTSs_2_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_1_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_1_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_1_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_1_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_1_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_2_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_2_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_2_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_2_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_2_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_3_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_3_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_3_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_3_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_3_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_1_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_1_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_1_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_1_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_1_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_2_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_2_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_2_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_2_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_2_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_3_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_3_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_3_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_3_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_3_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_4_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_4_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_4_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_4_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_4_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM_Additional_record_fields_c100_CH_RECORD_FIELDS* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM_Additional_record_fields_c100".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM_Additional_record_fields_c100 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM_Additional_record_fields_c100* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM_Additional_record_fields_c100 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM_Additional_record_fields_c100* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM_Additional_record_fields_c101_PILOTSs_data_PDCCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM_Additional_record_fields_c101_PILOTSs_data_PDCCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM_Additional_record_fields_c101_PILOTSs_data_PDCCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM_Additional_record_fields_c101_PILOTSs_data_PDCCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM_Additional_record_fields_c101_PILOTSs_data_PDCCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM_Additional_record_fields_c101_PILOTSs_data_FOR_GCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM_Additional_record_fields_c101_PILOTSs_data_FOR_GCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM_Additional_record_fields_c101_PILOTSs_data_FOR_GCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM_Additional_record_fields_c101_PILOTSs_data_FOR_GCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM_Additional_record_fields_c101_PILOTSs_data_FOR_GCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM_Additional_record_fields_c010".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM_Additional_record_fields_c010 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM_Additional_record_fields_c010* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM_Additional_record_fields_c010 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM_Additional_record_fields_c010* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM_Additional_record_fields_c011".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM_Additional_record_fields_c011 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM_Additional_record_fields_c011* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM_Additional_record_fields_c011 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM_Additional_record_fields_c011* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM_Additional_record_fields_c101_PILOTSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM_Additional_record_fields_c101_PILOTSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM_Additional_record_fields_c101_PILOTSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM_Additional_record_fields_c101_PILOTSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM_Additional_record_fields_c101_PILOTSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM_Additional_record_fields_c101".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM_Additional_record_fields_c101 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM_Additional_record_fields_c101* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM_Additional_record_fields_c101 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM_Additional_record_fields_c101* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECAM_Additional_record_fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECAM_Additional_record_fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECAM_Additional_record_fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECAM_Additional_record_fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECAM_Additional_record_fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GNLM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GNLM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GNLM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GNLM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GNLM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GNLM_NGHBRs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GNLM_NGHBRs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GNLM_NGHBRs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GNLM_NGHBRs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GNLM_NGHBRs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GNLM_ANALOG_NGHBRs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GNLM_ANALOG_NGHBRs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GNLM_ANALOG_NGHBRs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GNLM_ANALOG_NGHBRs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GNLM_ANALOG_NGHBRs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields_c01".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields_c01 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields_c01* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields_c01 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields_c01* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields_c02".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields_c02 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields_c02* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields_c02 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields_c02* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields_c03".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields_c03 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields_c03* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields_c03 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields_c03* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields_c04".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields_c04 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields_c04* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields_c04 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields_c04* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields_c05".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields_c05 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields_c05* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields_c05 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields_c05* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GNLM_NGHBRs_01_data_records_Type_specific_fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GNLM_NGHBRs_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GNLM_NGHBRs_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GNLM_NGHBRs_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GNLM_NGHBRs_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GNLM_NGHBRs_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GNLM_NGHBRs_01_data_records".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GNLM_NGHBRs_01_data_records (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GNLM_NGHBRs_01_data_records* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GNLM_NGHBRs_01_data_records (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GNLM_NGHBRs_01_data_records* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GNLM_NGHBRs_02_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GNLM_NGHBRs_02_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GNLM_NGHBRs_02_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GNLM_NGHBRs_02_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GNLM_NGHBRs_02_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GNLM_NGHBRs_03_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GNLM_NGHBRs_03_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GNLM_NGHBRs_03_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GNLM_NGHBRs_03_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GNLM_NGHBRs_03_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GNLM_NGHBRs_04_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GNLM_NGHBRs_04_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GNLM_NGHBRs_04_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GNLM_NGHBRs_04_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GNLM_NGHBRs_04_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GNLM_HRPD_NGHBRs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GNLM_HRPD_NGHBRs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GNLM_HRPD_NGHBRs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GNLM_HRPD_NGHBRs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GNLM_HRPD_NGHBRs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_UZIM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UZIM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UZIM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UZIM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UZIM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_UZIM_UZIDs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UZIM_UZIDs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UZIM_UZIDs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UZIM_UZIDs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UZIM_UZIDs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_PNLM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_PNLM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_PNLM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_PNLM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_PNLM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields_c01".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields_c01 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields_c01* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields_c01 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields_c01* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields_c02".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields_c02 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields_c02* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields_c02 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields_c02* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields_c03".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields_c03 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields_c03* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields_c03 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields_c03* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields_c04".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields_c04 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields_c04* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields_c04 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields_c04* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields_c05".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields_c05 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields_c05* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields_c05 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields_c05* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records_Type_specific_fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_UZIDs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_UZIDs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_UZIDs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_UZIDs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_UZIDs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_PRI_NGHBRs_data_records* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_PNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_PNLM_RADIO_INTERFACEs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_PNLM_RADIO_INTERFACEs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_PNLM_RADIO_INTERFACEs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_PNLM_RADIO_INTERFACEs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_PNLM_RADIO_INTERFACEs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_SCHM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_SCHM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_SCHM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_SCHM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_SCHM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_EGSRDM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_EGSRDM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_EGSRDM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_EGSRDM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_EGSRDM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_EGSRDM_Type_specific_fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_EGSRDM_Type_specific_fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_EGSRDM_Type_specific_fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_EGSRDM_Type_specific_fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_EGSRDM_Type_specific_fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_EGSRDM_ADD_RECORDs_data_typeSpecificFields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_EGSRDM_ADD_RECORDs_data_typeSpecificFields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_EGSRDM_ADD_RECORDs_data_typeSpecificFields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_EGSRDM_ADD_RECORDs_data_typeSpecificFields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_EGSRDM_ADD_RECORDs_data_typeSpecificFields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_EGSRDM_Type_Specific_Fields_1".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_EGSRDM_Type_Specific_Fields_1 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_EGSRDM_Type_Specific_Fields_1* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_EGSRDM_Type_Specific_Fields_1 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_EGSRDM_Type_Specific_Fields_1* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_EGSRDM_Type_specific_fields_field_2_CHANSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_EGSRDM_Type_specific_fields_field_2_CHANSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_EGSRDM_Type_specific_fields_field_2_CHANSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_EGSRDM_Type_specific_fields_field_2_CHANSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_EGSRDM_Type_specific_fields_field_2_CHANSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_EGSRDM_Type_specific_fields_field_2_data_02_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_EGSRDM_Type_specific_fields_field_2_data_02_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_EGSRDM_Type_specific_fields_field_2_data_02_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_EGSRDM_Type_specific_fields_field_2_data_02_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_EGSRDM_Type_specific_fields_field_2_data_02_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_EGSRDM_Type_Specific_Fields_2".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_EGSRDM_Type_Specific_Fields_2 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_EGSRDM_Type_Specific_Fields_2* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_EGSRDM_Type_Specific_Fields_2 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_EGSRDM_Type_Specific_Fields_2* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_EGSRDM_ADD_RECORDs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_EGSRDM_ADD_RECORDs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_EGSRDM_ADD_RECORDs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_EGSRDM_ADD_RECORDs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_EGSRDM_ADD_RECORDs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECCLM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECCLM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECCLM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECCLM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECCLM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECCLM_FREQs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECCLM_FREQs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECCLM_FREQs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECCLM_FREQs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECCLM_FREQs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECCLM_FREQs_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECCLM_FREQs_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECCLM_FREQs_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECCLM_FREQs_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECCLM_FREQs_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECCLM_FREQs_02_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECCLM_FREQs_02_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECCLM_FREQs_02_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECCLM_FREQs_02_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECCLM_FREQs_02_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECCLM_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECCLM_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECCLM_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECCLM_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECCLM_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECCLM_FREQs_03_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECCLM_FREQs_03_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECCLM_FREQs_03_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECCLM_FREQs_03_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECCLM_FREQs_03_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECCLM_BANDs_data_data_02_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECCLM_BANDs_data_data_02_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECCLM_BANDs_data_data_02_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECCLM_BANDs_data_data_02_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECCLM_BANDs_data_data_02_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECCLM_BANDs_data_ADD_FREQs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECCLM_BANDs_data_ADD_FREQs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECCLM_BANDs_data_ADD_FREQs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECCLM_BANDs_data_ADD_FREQs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECCLM_BANDs_data_ADD_FREQs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ECCLM_BANDs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ECCLM_BANDs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ECCLM_BANDs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ECCLM_BANDs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ECCLM_BANDs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_UZRM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UZRM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UZRM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UZRM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UZRM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_A41SPM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_A41SPM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_A41SPM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_A41SPM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_A41SPM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_MCRRPM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_MCRRPM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_MCRRPM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_MCRRPM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_MCRRPM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_MCRRPM_FCCCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_MCRRPM_FCCCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_MCRRPM_FCCCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_MCRRPM_FCCCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_MCRRPM_FCCCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_MCRRPM_BCCH_BCASTs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_MCRRPM_BCCH_BCASTs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_MCRRPM_BCCH_BCASTs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_MCRRPM_BCCH_BCASTs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_MCRRPM_BCCH_BCASTs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_MCRRPM_QPCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_MCRRPM_QPCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_MCRRPM_QPCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_MCRRPM_QPCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_MCRRPM_QPCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_MCRRPM_PDCCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_MCRRPM_PDCCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_MCRRPM_PDCCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_MCRRPM_PDCCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_MCRRPM_PDCCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_MCRRPM_CAND_BAND_CLASSs_data_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_MCRRPM_CAND_BAND_CLASSs_data_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_MCRRPM_CAND_BAND_CLASSs_data_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_MCRRPM_CAND_BAND_CLASSs_data_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_MCRRPM_CAND_BAND_CLASSs_data_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_MCRRPM_CAND_BAND_CLASSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_MCRRPM_CAND_BAND_CLASSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_MCRRPM_CAND_BAND_CLASSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_MCRRPM_CAND_BAND_CLASSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_MCRRPM_CAND_BAND_CLASSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_A41RANDM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_A41RANDM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_A41RANDM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_A41RANDM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_A41RANDM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_EAPM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_EAPM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_EAPM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_EAPM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_EAPM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_EAPM_MODE_SELECTION_ENTRIESs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_EAPM_MODE_SELECTION_ENTRIESs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_EAPM_MODE_SELECTION_ENTRIESs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_EAPM_MODE_SELECTION_ENTRIESs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_EAPM_MODE_SELECTION_ENTRIESs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_EAPM_MODE_PARM_RECs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_EAPM_MODE_PARM_RECs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_EAPM_MODE_PARM_RECs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_EAPM_MODE_PARM_RECs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_EAPM_MODE_PARM_RECs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_EAPM_CACHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_EAPM_CACHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_EAPM_CACHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_EAPM_CACHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_EAPM_CACHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_EAPM_CPCCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_EAPM_CPCCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_EAPM_CPCCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_EAPM_CPCCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_EAPM_CPCCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_EAPM_ACCT_SOs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_EAPM_ACCT_SOs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_EAPM_ACCT_SOs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_EAPM_ACCT_SOs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_EAPM_ACCT_SOs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_EAPM_ACCT_SO_GRPs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_EAPM_ACCT_SO_GRPs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_EAPM_ACCT_SO_GRPs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_EAPM_ACCT_SO_GRPs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_EAPM_ACCT_SO_GRPs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_UNLM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UNLM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UNLM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UNLM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UNLM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c01".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c01 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c01* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c01 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c01* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c02".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c02 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c02* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c02 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c02* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c03".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c03 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c03* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c03 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c03* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c04".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c04 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c04* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c04 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c04* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c05".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c05 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c05* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c05 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c05* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c06_HRPD_NGHBRs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c06_HRPD_NGHBRs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c06_HRPD_NGHBRs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c06_HRPD_NGHBRs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c06_HRPD_NGHBRs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c06".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c06 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c06* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c06 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields_c06* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records_Type_specific_fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_data_records* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_NGHBRs_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_data_02_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_data_02_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_data_02_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_data_02_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_data_02_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_analog".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_analog (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_analog* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_analog (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_analog* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_analog_ANALOG_NGHBR_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_analog_ANALOG_NGHBR_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_analog_ANALOG_NGHBR_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_analog_ANALOG_NGHBR_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_analog_ANALOG_NGHBR_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_HRPD".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_HRPD (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_HRPD* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_HRPD (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_HRPD* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_HRPD_HRPD_NGHBR_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_HRPD_HRPD_NGHBR_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_HRPD_HRPD_NGHBR_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_HRPD_HRPD_NGHBR_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UNLM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_HRPD_HRPD_NGHBR_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_UNLM_RADIO_INTERFACEs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_UNLM_RADIO_INTERFACEs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_UNLM_RADIO_INTERFACEs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_UNLM_RADIO_INTERFACEs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_UNLM_RADIO_INTERFACEs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_SMCM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_SMCM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_SMCM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_SMCM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_SMCM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_AUREQM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_AUREQM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_AUREQM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_AUREQM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_AUREQM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_BSPM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_BSPM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_BSPM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_BSPM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_BSPM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_BSPM_FSCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_BSPM_FSCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_BSPM_FSCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_BSPM_FSCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_BSPM_FSCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_BSPM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data_LPM_ENTRIESs_data_NGHBRs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_BSPM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data_LPM_ENTRIESs_data_NGHBRs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_BSPM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data_LPM_ENTRIESs_data_NGHBRs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_BSPM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data_LPM_ENTRIESs_data_NGHBRs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_BSPM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data_LPM_ENTRIESs_data_NGHBRs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_BSPM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data_LPM_ENTRIESs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_BSPM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data_LPM_ENTRIESs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_BSPM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data_LPM_ENTRIESs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_BSPM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data_LPM_ENTRIESs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_BSPM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data_LPM_ENTRIESs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_BSPM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_BSPM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_BSPM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_BSPM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_BSPM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_BSPM_BCMC_PROGRAMSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_BSPM_BCMC_PROGRAMSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_BSPM_BCMC_PROGRAMSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_BSPM_BCMC_PROGRAMSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_BSPM_BCMC_PROGRAMSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_BSPM_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_BSPM_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_BSPM_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_BSPM_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_BSPM_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_APIDM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_APIDM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_APIDM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_APIDM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_APIDM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_APIDM_LOC_REC_0001".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_APIDM_LOC_REC_0001 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_APIDM_LOC_REC_0001* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_APIDM_LOC_REC_0001 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_APIDM_LOC_REC_0001* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_APIDM_data_01_data_HO_INFO_VALUE_c01".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_APIDM_data_01_data_HO_INFO_VALUE_c01 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_APIDM_data_01_data_HO_INFO_VALUE_c01* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_APIDM_data_01_data_HO_INFO_VALUE_c01 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_APIDM_data_01_data_HO_INFO_VALUE_c01* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_APIDM_data_01_data_HO_INFO_VALUE_c02_data_06_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_APIDM_data_01_data_HO_INFO_VALUE_c02_data_06_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_APIDM_data_01_data_HO_INFO_VALUE_c02_data_06_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_APIDM_data_01_data_HO_INFO_VALUE_c02_data_06_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_APIDM_data_01_data_HO_INFO_VALUE_c02_data_06_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_APIDM_data_01_data_HO_INFO_VALUE_c02".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_APIDM_data_01_data_HO_INFO_VALUE_c02 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_APIDM_data_01_data_HO_INFO_VALUE_c02* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_APIDM_data_01_data_HO_INFO_VALUE_c02 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_APIDM_data_01_data_HO_INFO_VALUE_c02* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_APIDM_data_01_data_HO_INFO_VALUE_c03_data_08_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_APIDM_data_01_data_HO_INFO_VALUE_c03_data_08_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_APIDM_data_01_data_HO_INFO_VALUE_c03_data_08_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_APIDM_data_01_data_HO_INFO_VALUE_c03_data_08_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_APIDM_data_01_data_HO_INFO_VALUE_c03_data_08_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_APIDM_data_01_data_HO_INFO_VALUE_c03".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_APIDM_data_01_data_HO_INFO_VALUE_c03 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_APIDM_data_01_data_HO_INFO_VALUE_c03* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_APIDM_data_01_data_HO_INFO_VALUE_c03 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_APIDM_data_01_data_HO_INFO_VALUE_c03* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_APIDM_data_01_data_HO_INFO_VALUE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_APIDM_data_01_data_HO_INFO_VALUE (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_APIDM_data_01_data_HO_INFO_VALUE* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_APIDM_data_01_data_HO_INFO_VALUE (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_APIDM_data_01_data_HO_INFO_VALUE* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_APIDM_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_APIDM_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_APIDM_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_APIDM_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_APIDM_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_APIDTM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_APIDTM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_APIDTM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_APIDTM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_APIDTM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_APIDTM_FIELDSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_APIDTM_FIELDSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_APIDTM_FIELDSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_APIDTM_FIELDSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_APIDTM_FIELDSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_APPIM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_APPIM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_APPIM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_APPIM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_APPIM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_APPIM_APPI_RECs_data_AP_PN_REC_c01_data_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_APPIM_APPI_RECs_data_AP_PN_REC_c01_data_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_APPIM_APPI_RECs_data_AP_PN_REC_c01_data_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_APPIM_APPI_RECs_data_AP_PN_REC_c01_data_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_APPIM_APPI_RECs_data_AP_PN_REC_c01_data_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_APPIM_APPI_RECs_data_AP_PN_REC_c01".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_APPIM_APPI_RECs_data_AP_PN_REC_c01 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_APPIM_APPI_RECs_data_AP_PN_REC_c01* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_APPIM_APPI_RECs_data_AP_PN_REC_c01 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_APPIM_APPI_RECs_data_AP_PN_REC_c01* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_APPIM_APPI_RECs_data_AP_PN_REC_c02".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_APPIM_APPI_RECs_data_AP_PN_REC_c02 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_APPIM_APPI_RECs_data_AP_PN_REC_c02* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_APPIM_APPI_RECs_data_AP_PN_REC_c02 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_APPIM_APPI_RECs_data_AP_PN_REC_c02* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_APPIM_APPI_RECs_data_AP_PN_REC".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_APPIM_APPI_RECs_data_AP_PN_REC (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_APPIM_APPI_RECs_data_AP_PN_REC* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_APPIM_APPI_RECs_data_AP_PN_REC (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_APPIM_APPI_RECs_data_AP_PN_REC* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_APPIM_APPI_RECs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_APPIM_APPI_RECs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_APPIM_APPI_RECs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_APPIM_APPI_RECs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_APPIM_APPI_RECs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GOIM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GOIM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GOIM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GOIM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GOIM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GOIM_GOI_RECs_data_GOI_REC_c01_FIELDSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GOIM_GOI_RECs_data_GOI_REC_c01_FIELDSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GOIM_GOI_RECs_data_GOI_REC_c01_FIELDSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GOIM_GOI_RECs_data_GOI_REC_c01_FIELDSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GOIM_GOI_RECs_data_GOI_REC_c01_FIELDSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GOIM_GOI_RECs_data_GOI_REC_c01".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GOIM_GOI_RECs_data_GOI_REC_c01 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GOIM_GOI_RECs_data_GOI_REC_c01* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GOIM_GOI_RECs_data_GOI_REC_c01 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GOIM_GOI_RECs_data_GOI_REC_c01* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GOIM_GOI_RECs_data_GOI_REC_c02_NETWORKSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GOIM_GOI_RECs_data_GOI_REC_c02_NETWORKSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GOIM_GOI_RECs_data_GOI_REC_c02_NETWORKSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GOIM_GOI_RECs_data_GOI_REC_c02_NETWORKSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GOIM_GOI_RECs_data_GOI_REC_c02_NETWORKSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GOIM_GOI_RECs_data_GOI_REC_c02".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GOIM_GOI_RECs_data_GOI_REC_c02 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GOIM_GOI_RECs_data_GOI_REC_c02* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GOIM_GOI_RECs_data_GOI_REC_c02 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GOIM_GOI_RECs_data_GOI_REC_c02* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GOIM_GOI_RECs_data_GOI_REC".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GOIM_GOI_RECs_data_GOI_REC (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GOIM_GOI_RECs_data_GOI_REC* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GOIM_GOI_RECs_data_GOI_REC (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GOIM_GOI_RECs_data_GOI_REC* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GOIM_GOI_RECs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GOIM_GOI_RECs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GOIM_GOI_RECs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GOIM_GOI_RECs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GOIM_GOI_RECs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_FDCCLM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_FDCCLM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_FDCCLM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_FDCCLM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_FDCCLM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_FDCCLM_CAND_BAND_CLASSs_data_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_FDCCLM_CAND_BAND_CLASSs_data_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_FDCCLM_CAND_BAND_CLASSs_data_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_FDCCLM_CAND_BAND_CLASSs_data_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_FDCCLM_CAND_BAND_CLASSs_data_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_FDCCLM_CAND_BAND_CLASSs_data_FREQs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_FDCCLM_CAND_BAND_CLASSs_data_FREQs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_FDCCLM_CAND_BAND_CLASSs_data_FREQs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_FDCCLM_CAND_BAND_CLASSs_data_FREQs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_FDCCLM_CAND_BAND_CLASSs_data_FREQs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_FDCCLM_CAND_BAND_CLASSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_FDCCLM_CAND_BAND_CLASSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_FDCCLM_CAND_BAND_CLASSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_FDCCLM_CAND_BAND_CLASSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_FDCCLM_CAND_BAND_CLASSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GEM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GEM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GEM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GEM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GEM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GEM_GE_RECs_data_GE_REC_c00".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GEM_GE_RECs_data_GE_REC_c00 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GEM_GE_RECs_data_GE_REC_c00* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GEM_GE_RECs_data_GE_REC_c00 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GEM_GE_RECs_data_GE_REC_c00* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GEM_GE_RECs_data_GE_REC_c02".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GEM_GE_RECs_data_GE_REC_c02 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GEM_GE_RECs_data_GE_REC_c02* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GEM_GE_RECs_data_GE_REC_c02 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GEM_GE_RECs_data_GE_REC_c02* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GEM_GE_RECs_data_GE_REC".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GEM_GE_RECs_data_GE_REC (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GEM_GE_RECs_data_GE_REC* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GEM_GE_RECs_data_GE_REC (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GEM_GE_RECs_data_GE_REC* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GEM_GE_RECs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GEM_GE_RECs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GEM_GE_RECs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GEM_GE_RECs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GEM_GE_RECs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GEM_GE_RECs_data_GE_REC_c01".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GEM_GE_RECs_data_GE_REC_c01 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GEM_GE_RECs_data_GE_REC_c01* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GEM_GE_RECs_data_GE_REC_c01 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GEM_GE_RECs_data_GE_REC_c01* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GEM_GE_RECs_data_GE_REC_c01_RC_PARAMS_RECORDSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GEM_GE_RECs_data_GE_REC_c01_RC_PARAMS_RECORDSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GEM_GE_RECs_data_GE_REC_c01_RC_PARAMS_RECORDSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GEM_GE_RECs_data_GE_REC_c01_RC_PARAMS_RECORDSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GEM_GE_RECs_data_GE_REC_c01_RC_PARAMS_RECORDSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ATIM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ATIM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ATIM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ATIM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ATIM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ATIM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_010_HRPD_NGHBRs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ATIM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_010_HRPD_NGHBRs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ATIM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_010_HRPD_NGHBRs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ATIM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_010_HRPD_NGHBRs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ATIM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_010_HRPD_NGHBRs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ATIM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_010".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ATIM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_010 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ATIM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_010* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ATIM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_010 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ATIM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_010* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_ATIM_RADIO_INTERFACEs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_ATIM_RADIO_INTERFACEs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_ATIM_RADIO_INTERFACEs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_ATIM_RADIO_INTERFACEs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_ATIM_RADIO_INTERFACEs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_FGOIM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_FGOIM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_FGOIM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_FGOIM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_FGOIM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_FGOIM_GOI_RECs_data_GOI_REC_c01_FIELDSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_FGOIM_GOI_RECs_data_GOI_REC_c01_FIELDSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_FGOIM_GOI_RECs_data_GOI_REC_c01_FIELDSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_FGOIM_GOI_RECs_data_GOI_REC_c01_FIELDSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_FGOIM_GOI_RECs_data_GOI_REC_c01_FIELDSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_FGOIM_GOI_RECs_data_GOI_REC_c01".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_FGOIM_GOI_RECs_data_GOI_REC_c01 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_FGOIM_GOI_RECs_data_GOI_REC_c01* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_FGOIM_GOI_RECs_data_GOI_REC_c01 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_FGOIM_GOI_RECs_data_GOI_REC_c01* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_FGOIM_GOI_RECs_data_GOI_REC_c02_NETWORKSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_FGOIM_GOI_RECs_data_GOI_REC_c02_NETWORKSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_FGOIM_GOI_RECs_data_GOI_REC_c02_NETWORKSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_FGOIM_GOI_RECs_data_GOI_REC_c02_NETWORKSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_FGOIM_GOI_RECs_data_GOI_REC_c02_NETWORKSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_FGOIM_GOI_RECs_data_GOI_REC_c02".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_FGOIM_GOI_RECs_data_GOI_REC_c02 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_FGOIM_GOI_RECs_data_GOI_REC_c02* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_FGOIM_GOI_RECs_data_GOI_REC_c02 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_FGOIM_GOI_RECs_data_GOI_REC_c02* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_FGOIM_GOI_RECs_data_GOI_REC".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_FGOIM_GOI_RECs_data_GOI_REC (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_FGOIM_GOI_RECs_data_GOI_REC* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_FGOIM_GOI_RECs_data_GOI_REC (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_FGOIM_GOI_RECs_data_GOI_REC* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_FGOIM_GOI_RECs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_FGOIM_GOI_RECs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_FGOIM_GOI_RECs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_FGOIM_GOI_RECs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_FGOIM_GOI_RECs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_GAPM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_GAPM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_GAPM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_GAPM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_GAPM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_HDPPM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_HDPPM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_HDPPM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_HDPPM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_HDPPM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_HDPPM_records_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_HDPPM_records_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_HDPPM_records_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_HDPPM_records_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_HDPPM_records_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_MECAM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_MECAM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_MECAM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_MECAM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_MECAM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01_PILOTSs_1_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01_PILOTSs_1_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01_PILOTSs_1_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01_PILOTSs_1_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01_PILOTSs_1_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01_PILOTSs_2_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01_PILOTSs_2_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01_PILOTSs_2_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01_PILOTSs_2_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01_PILOTSs_2_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c01* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_1_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_1_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_1_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_1_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_1_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_2_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_2_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_2_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_2_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_2_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_3_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_3_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_3_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_3_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02_PILOTSs_3_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c02* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_1_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_1_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_1_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_1_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_1_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_2_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_2_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_2_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_2_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_2_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_3_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_3_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_3_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_3_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_3_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_4_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_4_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_4_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_4_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03_PILOTSs_4_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS_c03* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_MECAM_Additional_record_fields_c100_CH_RECORD_FIELDS* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_MECAM_Additional_record_fields_c100".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_MECAM_Additional_record_fields_c100 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_MECAM_Additional_record_fields_c100* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_MECAM_Additional_record_fields_c100 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_MECAM_Additional_record_fields_c100* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_MECAM_Additional_record_fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_MECAM_Additional_record_fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_MECAM_Additional_record_fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_MECAM_Additional_record_fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_MECAM_Additional_record_fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_mini6".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_mini6 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_mini6* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_mini6 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_mini6* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_csch_mini6_sync".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_csch_mini6_sync (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_csch_mini6_sync* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_csch_mini6_sync (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_csch_mini6_sync* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ORDRM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ORDRM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ORDRM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ORDRM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ORDRM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_AUCM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_AUCM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_AUCM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_AUCM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_AUCM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_AWIM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_AWIM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_AWIM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_AWIM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_AWIM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_DBM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_DBM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_DBM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_DBM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_DBM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_DBM_FIELDSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_DBM_FIELDSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_DBM_FIELDSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_DBM_FIELDSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_DBM_FIELDSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_AHDM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_AHDM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_AHDM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_AHDM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_AHDM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ITSPM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ITSPM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ITSPM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ITSPM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ITSPM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_NLUM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_NLUM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_NLUM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_NLUM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_NLUM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_NLUM_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_NLUM_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_NLUM_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_NLUM_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_NLUM_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_BDTMFM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_BDTMFM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_BDTMFM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_BDTMFM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_BDTMFM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_BDTMFM_DIGITSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_BDTMFM_DIGITSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_BDTMFM_DIGITSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_BDTMFM_DIGITSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_BDTMFM_DIGITSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_PCNPM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_PCNPM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_PCNPM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_PCNPM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_PCNPM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_RTPM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_RTPM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_RTPM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_RTPM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_RTPM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_RTPM_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_RTPM_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_RTPM_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_RTPM_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_RTPM_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_STPM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_STPM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_STPM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_STPM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_STPM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_STPM_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_STPM_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_STPM_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_STPM_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_STPM_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_SSDUM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_SSDUM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_SSDUM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_SSDUM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_SSDUM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_FWIM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_FWIM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_FWIM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_FWIM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_FWIM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MSRM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MSRM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MSRM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MSRM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MSRM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_STRQM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_STRQM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_STRQM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_STRQM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_STRQM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_STRQM_FIELDSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_STRQM_FIELDSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_STRQM_FIELDSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_STRQM_FIELDSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_STRQM_FIELDSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_EHDM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_EHDM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_EHDM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_EHDM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_EHDM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_EHDM_Additional_fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_EHDM_Additional_fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_EHDM_Additional_fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_EHDM_Additional_fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_EHDM_Additional_fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_EHDM_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_EHDM_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_EHDM_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_EHDM_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_EHDM_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_SRQM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_SRQM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_SRQM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_SRQM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_SRQM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_SRPM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_SRPM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_SRPM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_SRPM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_SRPM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_SCM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_SCM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_SCM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_SCM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_SCM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_SCM_CALLS_ASSIGNs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_SCM_CALLS_ASSIGNs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_SCM_CALLS_ASSIGNs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_SCM_CALLS_ASSIGNs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_SCM_CALLS_ASSIGNs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_SOCM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_SOCM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_SOCM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_SOCM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_SOCM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_TASM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_TASM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_TASM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_TASM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_TASM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_SRDM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_SRDM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_SRDM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_SRDM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_SRDM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_SRDM_Type_specific_fields_2_CHANSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_SRDM_Type_specific_fields_2_CHANSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_SRDM_Type_specific_fields_2_CHANSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_SRDM_Type_specific_fields_2_CHANSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_SRDM_Type_specific_fields_2_CHANSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_SRDM_Type_specific_fields_1".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_SRDM_Type_specific_fields_1 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_SRDM_Type_specific_fields_1* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_SRDM_Type_specific_fields_1 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_SRDM_Type_specific_fields_1* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_SRDM_Type_specific_fields_2".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_SRDM_Type_specific_fields_2 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_SRDM_Type_specific_fields_2* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_SRDM_Type_specific_fields_2 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_SRDM_Type_specific_fields_2* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_SCAM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_SCAM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_SCAM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_SCAM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_SCAM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_SCAM_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_SCAM_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_SCAM_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_SCAM_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_SCAM_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_SCAM_data_02_data_SUP_PILOTSs_data_FOR_SUPs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_SCAM_data_02_data_SUP_PILOTSs_data_FOR_SUPs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_SCAM_data_02_data_SUP_PILOTSs_data_FOR_SUPs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_SCAM_data_02_data_SUP_PILOTSs_data_FOR_SUPs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_SCAM_data_02_data_SUP_PILOTSs_data_FOR_SUPs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_SCAM_data_02_data_SUP_PILOTSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_SCAM_data_02_data_SUP_PILOTSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_SCAM_data_02_data_SUP_PILOTSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_SCAM_data_02_data_SUP_PILOTSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_SCAM_data_02_data_SUP_PILOTSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_SCAM_data_02_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_SCAM_data_02_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_SCAM_data_02_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_SCAM_data_02_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_SCAM_data_02_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_PCNM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_PCNM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_PCNM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_PCNM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_PCNM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_PCNM_SUPs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_PCNM_SUPs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_PCNM_SUPs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_PCNM_SUPs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_PCNM_SUPs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ENLUM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ENLUM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ENLUM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ENLUM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ENLUM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ENLUM_NGHBRs_02_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ENLUM_NGHBRs_02_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ENLUM_NGHBRs_02_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ENLUM_NGHBRs_02_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ENLUM_NGHBRs_02_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ENLUM_NGHBRs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ENLUM_NGHBRs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ENLUM_NGHBRs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ENLUM_NGHBRs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ENLUM_NGHBRs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields_c01".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields_c01 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields_c01* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields_c01 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields_c01* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields_c02".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields_c02 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields_c02* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields_c02 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields_c02* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields_c03".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields_c03 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields_c03* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields_c03 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields_c03* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields_c04".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields_c04 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields_c04* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields_c04 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields_c04* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields_c05".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields_c05 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields_c05* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields_c05 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields_c05* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ENLUM_NGHBRs_01_data_records_Type_specific_fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ENLUM_NGHBRs_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ENLUM_NGHBRs_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ENLUM_NGHBRs_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ENLUM_NGHBRs_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ENLUM_NGHBRs_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ENLUM_NGHBRs_01_data_records".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ENLUM_NGHBRs_01_data_records (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ENLUM_NGHBRs_01_data_records* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ENLUM_NGHBRs_01_data_records (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ENLUM_NGHBRs_01_data_records* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_CFSRQM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_CFSRQM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_CFSRQM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_CFSRQM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_CFSRQM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_CFSRQM_Mode_specific_fields_1".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_CFSRQM_Mode_specific_fields_1 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_CFSRQM_Mode_specific_fields_1* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_CFSRQM_Mode_specific_fields_1 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_CFSRQM_Mode_specific_fields_1* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_CFSRQM_Mode_specific_fields_1_ANALOG_FREQs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_CFSRQM_Mode_specific_fields_1_ANALOG_FREQs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_CFSRQM_Mode_specific_fields_1_ANALOG_FREQs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_CFSRQM_Mode_specific_fields_1_ANALOG_FREQs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_CFSRQM_Mode_specific_fields_1_ANALOG_FREQs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields_c00".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields_c00 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields_c00* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields_c00 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields_c00* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields_c01".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields_c01 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields_c01* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields_c01 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields_c01* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields_c02".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields_c02 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields_c02* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields_c02 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields_c02* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields_c03".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields_c03 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields_c03* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields_c03 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields_c03* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields_c04".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields_c04 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields_c04* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields_c04 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields_c04* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records_Type_specific_fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_CFSRQM_Mode_specific_fields_0_PILOTSs_02_data_records* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_CFSRQM_Mode_specific_fields_0".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_CFSRQM_Mode_specific_fields_0 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_CFSRQM_Mode_specific_fields_0* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_CFSRQM_Mode_specific_fields_0 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_CFSRQM_Mode_specific_fields_0* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_CFSRQM_Mode_specific_fields_0_CF_SRCH_OFFSET_INCLs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_CFSRQM_Mode_specific_fields_0_CF_SRCH_OFFSET_INCLs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_CFSRQM_Mode_specific_fields_0_CF_SRCH_OFFSET_INCLs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_CFSRQM_Mode_specific_fields_0_CF_SRCH_OFFSET_INCLs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_CFSRQM_Mode_specific_fields_0_CF_SRCH_OFFSET_INCLs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_CFSCNM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_CFSCNM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_CFSCNM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_CFSCNM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_CFSCNM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_PUFM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_PUFM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_PUFM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_PUFM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_PUFM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_PUFCM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_PUFCM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_PUFCM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_PUFCM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_PUFCM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_GHDM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_GHDM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_GHDM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_GHDM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_GHDM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_GHDM_PILOTSs_data_FOR_SUP_CHAN_REC_Record_FOR_SUPs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_GHDM_PILOTSs_data_FOR_SUP_CHAN_REC_Record_FOR_SUPs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_GHDM_PILOTSs_data_FOR_SUP_CHAN_REC_Record_FOR_SUPs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_GHDM_PILOTSs_data_FOR_SUP_CHAN_REC_Record_FOR_SUPs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_GHDM_PILOTSs_data_FOR_SUP_CHAN_REC_Record_FOR_SUPs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_GHDM_PILOTSs_data_FOR_SUP_CHAN_REC_Record".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_GHDM_PILOTSs_data_FOR_SUP_CHAN_REC_Record (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_GHDM_PILOTSs_data_FOR_SUP_CHAN_REC_Record* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_GHDM_PILOTSs_data_FOR_SUP_CHAN_REC_Record (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_GHDM_PILOTSs_data_FOR_SUP_CHAN_REC_Record* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_GHDM_PILOTSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_GHDM_PILOTSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_GHDM_PILOTSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_GHDM_PILOTSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_GHDM_PILOTSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_RAM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_RAM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_RAM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_RAM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_RAM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_RAMM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_RAMM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_RAMM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_RAMM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_RAMM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ERM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ERM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ERM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ERM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ERM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ERM_data_01_data_PILOTS_D2Is_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ERM_data_01_data_PILOTS_D2Is_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ERM_data_01_data_PILOTS_D2Is_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ERM_data_01_data_PILOTS_D2Is_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ERM_data_01_data_PILOTS_D2Is_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ERM_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ERM_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ERM_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ERM_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ERM_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ERM_FSCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ERM_FSCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ERM_FSCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ERM_FSCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ERM_FSCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ERM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data_LPM_ENTRIESs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ERM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data_LPM_ENTRIESs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ERM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data_LPM_ENTRIESs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ERM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data_LPM_ENTRIESs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ERM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data_LPM_ENTRIESs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ERM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ERM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ERM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ERM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ERM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ERM_BCMC_PROGRAMSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ERM_BCMC_PROGRAMSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ERM_BCMC_PROGRAMSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ERM_BCMC_PROGRAMSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ERM_BCMC_PROGRAMSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ERMM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ERMM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ERMM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ERMM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ERMM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_FOR_ASSIGNs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_FOR_ASSIGNs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_FOR_ASSIGNs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_FOR_ASSIGNs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_FOR_ASSIGNs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_REV_ASSIGNs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_REV_ASSIGNs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_REV_ASSIGNs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_REV_ASSIGNs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_REV_ASSIGNs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_FOR_SCHs".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_FOR_SCHs (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_FOR_SCHs* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_FOR_SCHs (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_FOR_SCHs* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_REV_SCHs".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_REV_SCHs (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_REV_SCHs* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_REV_SCHs (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_REV_SCHs* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs1_data_SCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs1_data_SCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs1_data_SCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs1_data_SCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs1_data_SCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs1_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs1_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs1_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs1_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs1_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_SCHs".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_SCHs (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_SCHs* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_SCHs (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_SCHs* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs2_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs2_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs2_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs2_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs2_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c01_CCSH_ENCODER_TYPEs_data_SCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c01_CCSH_ENCODER_TYPEs_data_SCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c01_CCSH_ENCODER_TYPEs_data_SCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c01_CCSH_ENCODER_TYPEs_data_SCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c01_CCSH_ENCODER_TYPEs_data_SCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CCSH_ENCODER_TYPE_BY_PILOT".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CCSH_ENCODER_TYPE_BY_PILOT (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CCSH_ENCODER_TYPE_BY_PILOT* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CCSH_ENCODER_TYPE_BY_PILOT (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CCSH_ENCODER_TYPE_BY_PILOT* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c01".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c01 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c01* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c01 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c01* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_02_data_SCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_02_data_SCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_02_data_SCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_02_data_SCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_02_data_SCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_02_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_02_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_02_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_02_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_02_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTS3_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTS3_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTS3_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTS3_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTS3_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c02".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c02 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c02* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c02 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c02* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03_FOR_SCHs_02_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03_FOR_SCHs_02_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03_FOR_SCHs_02_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03_FOR_SCHs_02_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03_FOR_SCHs_02_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_04_data_data_06_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_04_data_data_06_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_04_data_data_06_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_04_data_data_06_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_04_data_data_06_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_04_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_04_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_04_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_04_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_04_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_05_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_05_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_05_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_05_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_05_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTS3_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTS3_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTS3_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTS3_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTS3_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c03* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04_PDCCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04_PDCCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04_PDCCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04_PDCCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04_PDCCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data_FOR_PDCCH_WALSHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data_FOR_PDCCH_WALSHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data_FOR_PDCCH_WALSHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data_FOR_PDCCH_WALSHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data_FOR_PDCCH_WALSHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data_FOR_GCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data_FOR_GCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data_FOR_GCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data_FOR_GCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data_FOR_GCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data_SCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data_SCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data_SCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data_SCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data_SCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS_c04* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_ACTIVE_SET_REC_FIELDS".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_ACTIVE_SET_REC_FIELDS* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_CALLS_ASSIGNs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_CALLS_ASSIGNs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_CALLS_ASSIGNs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_CALLS_ASSIGNs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_CALLS_ASSIGNs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UHDM_FOR_ASSIGNs_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UHDM_FOR_ASSIGNs_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UHDM_FOR_ASSIGNs_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UHDM_FOR_ASSIGNs_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UHDM_FOR_ASSIGNs_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ESCAM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ESCAM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ESCAM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ESCAM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ESCAM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ESCAM_REV_CFG_RECSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ESCAM_REV_CFG_RECSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ESCAM_REV_CFG_RECSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ESCAM_REV_CFG_RECSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ESCAM_REV_CFG_RECSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ESCAM_REV_SCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ESCAM_REV_SCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ESCAM_REV_SCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ESCAM_REV_SCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ESCAM_REV_SCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ESCAM_FOR_CFG_RECSs_data_SUP_SHOs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ESCAM_FOR_CFG_RECSs_data_SUP_SHOs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ESCAM_FOR_CFG_RECSs_data_SUP_SHOs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ESCAM_FOR_CFG_RECSs_data_SUP_SHOs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ESCAM_FOR_CFG_RECSs_data_SUP_SHOs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ESCAM_FOR_CFG_RECSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ESCAM_FOR_CFG_RECSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ESCAM_FOR_CFG_RECSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ESCAM_FOR_CFG_RECSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ESCAM_FOR_CFG_RECSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ESCAM_FOR_SCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ESCAM_FOR_SCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ESCAM_FOR_SCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ESCAM_FOR_SCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ESCAM_FOR_SCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ESCAM_SUPs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ESCAM_SUPs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ESCAM_SUPs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ESCAM_SUPs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ESCAM_SUPs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ESCAM_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ESCAM_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ESCAM_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ESCAM_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ESCAM_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ESCAM_P3X_CFGs_data_P3X_RECs_data_SUP_SHOs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ESCAM_P3X_CFGs_data_P3X_RECs_data_SUP_SHOs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ESCAM_P3X_CFGs_data_P3X_RECs_data_SUP_SHOs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ESCAM_P3X_CFGs_data_P3X_RECs_data_SUP_SHOs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ESCAM_P3X_CFGs_data_P3X_RECs_data_SUP_SHOs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ESCAM_P3X_CFGs_data_P3X_RECs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ESCAM_P3X_CFGs_data_P3X_RECs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ESCAM_P3X_CFGs_data_P3X_RECs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ESCAM_P3X_CFGs_data_P3X_RECs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ESCAM_P3X_CFGs_data_P3X_RECs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ESCAM_P3X_CFGs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ESCAM_P3X_CFGs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ESCAM_P3X_CFGs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ESCAM_P3X_CFGs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ESCAM_P3X_CFGs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ESCAM_data_02_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ESCAM_data_02_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ESCAM_data_02_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ESCAM_data_02_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ESCAM_data_02_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ESCAM_FOR_SCHs_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ESCAM_FOR_SCHs_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ESCAM_FOR_SCHs_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ESCAM_FOR_SCHs_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ESCAM_FOR_SCHs_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ESCAM_REV_SCHs_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ESCAM_REV_SCHs_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ESCAM_REV_SCHs_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ESCAM_REV_SCHs_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ESCAM_REV_SCHs_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ESCAM_FOR_SCHs_02_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ESCAM_FOR_SCHs_02_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ESCAM_FOR_SCHs_02_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ESCAM_FOR_SCHs_02_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ESCAM_FOR_SCHs_02_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_FSCAMM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_FSCAMM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_FSCAMM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_FSCAMM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_FSCAMM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_RSCAMM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_RSCAMM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_RSCAMM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_RSCAMM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_RSCAMM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MABOPM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MABOPM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MABOPM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MABOPM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MABOPM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MABOPM_data_01".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MABOPM_data_01 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MABOPM_data_01* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MABOPM_data_01 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MABOPM_data_01* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MABOPM_data_02".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MABOPM_data_02 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MABOPM_data_02* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MABOPM_data_02 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MABOPM_data_02* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MABOPM_data_03".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MABOPM_data_03 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MABOPM_data_03* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MABOPM_data_03 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MABOPM_data_03* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UZRM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UZRM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UZRM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UZRM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UZRM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_UZUM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_UZUM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_UZUM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_UZUM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_UZUM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_CLAM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_CLAM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_CLAM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_CLAM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_CLAM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_CLAM_ADD_CALL_RECORDSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_CLAM_ADD_CALL_RECORDSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_CLAM_ADD_CALL_RECORDSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_CLAM_ADD_CALL_RECORDSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_CLAM_ADD_CALL_RECORDSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_EAWIM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_EAWIM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_EAWIM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_EAWIM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_EAWIM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_EFWIM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_EFWIM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_EFWIM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_EFWIM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_EFWIM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_SMCM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_SMCM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_SMCM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_SMCM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_SMCM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_SMCM_RECSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_SMCM_RECSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_SMCM_RECSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_SMCM_RECSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_SMCM_RECSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_BSSRSPM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_BSSRSPM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_BSSRSPM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_BSSRSPM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_BSSRSPM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_BSSRSPM_RECORDSs_data_Record_type_specific_fields_PILOTSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_BSSRSPM_RECORDSs_data_Record_type_specific_fields_PILOTSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_BSSRSPM_RECORDSs_data_Record_type_specific_fields_PILOTSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_BSSRSPM_RECORDSs_data_Record_type_specific_fields_PILOTSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_BSSRSPM_RECORDSs_data_Record_type_specific_fields_PILOTSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_BSSRSPM_RECORDSs_data_Record_type_specific_fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_BSSRSPM_RECORDSs_data_Record_type_specific_fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_BSSRSPM_RECORDSs_data_Record_type_specific_fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_BSSRSPM_RECORDSs_data_Record_type_specific_fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_BSSRSPM_RECORDSs_data_Record_type_specific_fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_BSSRSPM_RECORDSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_BSSRSPM_RECORDSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_BSSRSPM_RECORDSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_BSSRSPM_RECORDSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_BSSRSPM_RECORDSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_AUREQM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_AUREQM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_AUREQM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_AUREQM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_AUREQM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_RATCHGM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_RATCHGM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_RATCHGM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_RATCHGM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_RATCHGM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_RATCHGM_RECSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_RATCHGM_RECSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_RATCHGM_RECSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_RATCHGM_RECSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_RATCHGM_RECSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ITBSPM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ITBSPM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ITBSPM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ITBSPM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ITBSPM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ITBSPM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ITBSPM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ITBSPM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ITBSPM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ITBSPM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ITBSPM_BCMC_PROGRAMSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ITBSPM_BCMC_PROGRAMSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ITBSPM_BCMC_PROGRAMSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ITBSPM_BCMC_PROGRAMSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ITBSPM_BCMC_PROGRAMSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_RCPM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_RCPM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_RCPM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_RCPM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_RCPM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_RCPM_RC_PARAMS_RECORDSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_RCPM_RC_PARAMS_RECORDSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_RCPM_RC_PARAMS_RECORDSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_RCPM_RC_PARAMS_RECORDSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_RCPM_RC_PARAMS_RECORDSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_HOSISM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_HOSISM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_HOSISM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_HOSISM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_HOSISM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_HOSISM_PILOT_PNs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_HOSISM_PILOT_PNs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_HOSISM_PILOT_PNs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_HOSISM_PILOT_PNs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_HOSISM_PILOT_PNs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_GEM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_GEM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_GEM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_GEM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_GEM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_GEM_GE_RECs_data_GE_REC_c00".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_GEM_GE_RECs_data_GE_REC_c00 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_GEM_GE_RECs_data_GE_REC_c00* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_GEM_GE_RECs_data_GE_REC_c00 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_GEM_GE_RECs_data_GE_REC_c00* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_GEM_GE_RECs_data_GE_REC_c02".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_GEM_GE_RECs_data_GE_REC_c02 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_GEM_GE_RECs_data_GE_REC_c02* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_GEM_GE_RECs_data_GE_REC_c02 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_GEM_GE_RECs_data_GE_REC_c02* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_GEM_GE_RECs_data_GE_REC".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_GEM_GE_RECs_data_GE_REC (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_GEM_GE_RECs_data_GE_REC* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_GEM_GE_RECs_data_GE_REC (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_GEM_GE_RECs_data_GE_REC* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_GEM_GE_RECs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_GEM_GE_RECs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_GEM_GE_RECs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_GEM_GE_RECs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_GEM_GE_RECs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_GEM_GE_RECs_data_GE_REC_c01".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_GEM_GE_RECs_data_GE_REC_c01 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_GEM_GE_RECs_data_GE_REC_c01* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_GEM_GE_RECs_data_GE_REC_c01 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_GEM_GE_RECs_data_GE_REC_c01* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_GEM_GE_RECs_data_GE_REC_c01_RC_PARAMS_RECORDSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_GEM_GE_RECs_data_GE_REC_c01_RC_PARAMS_RECORDSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_GEM_GE_RECs_data_GE_REC_c01_RC_PARAMS_RECORDSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_GEM_GE_RECs_data_GE_REC_c01_RC_PARAMS_RECORDSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_GEM_GE_RECs_data_GE_REC_c01_RC_PARAMS_RECORDSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ATIM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ATIM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ATIM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ATIM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ATIM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ATIM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_010_HRPD_NGHBRs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ATIM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_010_HRPD_NGHBRs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ATIM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_010_HRPD_NGHBRs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ATIM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_010_HRPD_NGHBRs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ATIM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_010_HRPD_NGHBRs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ATIM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_010".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ATIM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_010 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ATIM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_010* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ATIM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_010 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ATIM_RADIO_INTERFACEs_data_Radio_Interface_Type_Specific_Fields_010* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_ATIM_RADIO_INTERFACEs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_ATIM_RADIO_INTERFACEs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_ATIM_RADIO_INTERFACEs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_ATIM_RADIO_INTERFACEs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_ATIM_RADIO_INTERFACEs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_FOR_ASSIGNs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_FOR_ASSIGNs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_FOR_ASSIGNs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_FOR_ASSIGNs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_FOR_ASSIGNs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_REV_ASSIGNs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_REV_ASSIGNs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_REV_ASSIGNs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_REV_ASSIGNs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_REV_ASSIGNs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_FOR_SCHs".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_FOR_SCHs (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_FOR_SCHs* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_FOR_SCHs (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_FOR_SCHs* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_REV_SCHs".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_REV_SCHs (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_REV_SCHs* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_REV_SCHs (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_REV_SCHs* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs1_data_SCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs1_data_SCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs1_data_SCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs1_data_SCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs1_data_SCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs1_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs1_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs1_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs1_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs1_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_SCHs".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_SCHs (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_SCHs* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_SCHs (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_SCHs* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs2_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs2_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs2_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs2_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c01_PILOTSs2_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c01_CCSH_ENCODER_TYPEs_data_SCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c01_CCSH_ENCODER_TYPEs_data_SCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c01_CCSH_ENCODER_TYPEs_data_SCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c01_CCSH_ENCODER_TYPEs_data_SCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c01_CCSH_ENCODER_TYPEs_data_SCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CCSH_ENCODER_TYPE_BY_PILOT_MUHDM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CCSH_ENCODER_TYPE_BY_PILOT_MUHDM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CCSH_ENCODER_TYPE_BY_PILOT_MUHDM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CCSH_ENCODER_TYPE_BY_PILOT_MUHDM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CCSH_ENCODER_TYPE_BY_PILOT_MUHDM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c01".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c01 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c01* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c01 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c01* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_02_data_SCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_02_data_SCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_02_data_SCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_02_data_SCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_02_data_SCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_02_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_02_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_02_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_02_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_02_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c02_PILOTSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c02".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c02 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c02* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c02 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c02* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c03_FOR_SCHs_02_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c03_FOR_SCHs_02_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c03_FOR_SCHs_02_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c03_FOR_SCHs_02_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c03_FOR_SCHs_02_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_04_data_data_06_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_04_data_data_06_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_04_data_data_06_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_04_data_data_06_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_04_data_data_06_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_04_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_04_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_04_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_04_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_04_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_05_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_05_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_05_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_05_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c03_PILOTSs_05_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c03".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c03 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c03* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c03 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c03* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c04_PDCCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c04_PDCCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c04_PDCCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c04_PDCCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c04_PDCCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data_FOR_PDCCH_WALSHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data_FOR_PDCCH_WALSHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data_FOR_PDCCH_WALSHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data_FOR_PDCCH_WALSHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data_FOR_PDCCH_WALSHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data_SCHs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data_SCHs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data_SCHs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data_SCHs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data_SCHs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c04_PILOTS1_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c04".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c04 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c04* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c04 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS_c04* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_ACTIVE_SET_REC_FIELDS* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_MUHDM_CALLS_ASSIGNs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_MUHDM_CALLS_ASSIGNs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_MUHDM_CALLS_ASSIGNs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_MUHDM_CALLS_ASSIGNs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_MUHDM_CALLS_ASSIGNs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "f_dsch_mini3".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_f_dsch_mini3 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_f_dsch_mini3* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_f_dsch_mini3 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_f_dsch_mini3* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_RGM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_RGM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_RGM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_RGM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_RGM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_RGM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_RGM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_RGM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_RGM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_RGM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_RGM_BCMC_PROGRAMSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_RGM_BCMC_PROGRAMSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_RGM_BCMC_PROGRAMSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_RGM_BCMC_PROGRAMSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_RGM_BCMC_PROGRAMSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_RGM_BAND_SUBCLASSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_RGM_BAND_SUBCLASSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_RGM_BAND_SUBCLASSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_RGM_BAND_SUBCLASSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_RGM_BAND_SUBCLASSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_ORDM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_ORDM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_ORDM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_ORDM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_ORDM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_DBM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_DBM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_DBM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_DBM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_DBM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_DBM_FIELDSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_DBM_FIELDSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_DBM_FIELDSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_DBM_FIELDSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_DBM_FIELDSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_ORM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_ORM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_ORM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_ORM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_ORM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_ORM_FIELDSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_ORM_FIELDSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_ORM_FIELDSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_ORM_FIELDSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_ORM_FIELDSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_ORM_ALT_SOs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_ORM_ALT_SOs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_ORM_ALT_SOs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_ORM_ALT_SOs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_ORM_ALT_SOs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_ORM_ADD_SERV_INSTANCEs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_ORM_ADD_SERV_INSTANCEs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_ORM_ADD_SERV_INSTANCEs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_ORM_ADD_SERV_INSTANCEs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_ORM_ADD_SERV_INSTANCEs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_ORM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_ORM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_ORM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_ORM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_ORM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_ORM_BCMC_PROGRAMSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_ORM_BCMC_PROGRAMSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_ORM_BCMC_PROGRAMSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_ORM_BCMC_PROGRAMSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_ORM_BCMC_PROGRAMSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_ORM_BAND_SUBCLASSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_ORM_BAND_SUBCLASSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_ORM_BAND_SUBCLASSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_ORM_BAND_SUBCLASSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_ORM_BAND_SUBCLASSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_PRM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PRM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PRM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PRM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PRM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_PRM_ALT_SOs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PRM_ALT_SOs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PRM_ALT_SOs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PRM_ALT_SOs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PRM_ALT_SOs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_PRM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PRM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PRM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PRM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PRM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_PRM_BCMC_PROGRAMSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PRM_BCMC_PROGRAMSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PRM_BCMC_PROGRAMSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PRM_BCMC_PROGRAMSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PRM_BCMC_PROGRAMSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_PRM_BAND_SUBCLASSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PRM_BAND_SUBCLASSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PRM_BAND_SUBCLASSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PRM_BAND_SUBCLASSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PRM_BAND_SUBCLASSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_AUCRM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_AUCRM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_AUCRM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_AUCRM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_AUCRM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_TACM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_TACM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_TACM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_TACM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_TACM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_PACNM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_PACNM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_PACNM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_PACNM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_PACNM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_STRPM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_STRPM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_STRPM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_STRPM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_STRPM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_ESTRPM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_ESTRPM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_ESTRPM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_ESTRPM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_ESTRPM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_DIM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_DIM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_DIM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_DIM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_DIM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_SMRM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_SMRM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_SMRM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_SMRM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_SMRM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_AURSPM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_AURSPM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_AURSPM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_AURSPM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_AURSPM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_AURSYNM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_AURSYNM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_AURSYNM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_AURSYNM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_AURSYNM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_RCNM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_RCNM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_RCNM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_RCNM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_RCNM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_RCNM_ADD_SERV_INSTANCEs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_RCNM_ADD_SERV_INSTANCEs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_RCNM_ADD_SERV_INSTANCEs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_RCNM_ADD_SERV_INSTANCEs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_RCNM_ADD_SERV_INSTANCEs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_RCNM_FIELDSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_RCNM_FIELDSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_RCNM_FIELDSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_RCNM_FIELDSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_RCNM_FIELDSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_REM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_REM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_REM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_REM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_REM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_CRRM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_CRRM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_CRRM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_CRRM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_CRRM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_GEM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_GEM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_GEM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_GEM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_GEM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_GEM_GE_RECs_data_GE_REC_c01_BAND_SUBCLASSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_GEM_GE_RECs_data_GE_REC_c01_BAND_SUBCLASSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_GEM_GE_RECs_data_GE_REC_c01_BAND_SUBCLASSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_GEM_GE_RECs_data_GE_REC_c01_BAND_SUBCLASSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_GEM_GE_RECs_data_GE_REC_c01_BAND_SUBCLASSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_GEM_GE_RECs_data_GE_REC_c01".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_GEM_GE_RECs_data_GE_REC_c01 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_GEM_GE_RECs_data_GE_REC_c01* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_GEM_GE_RECs_data_GE_REC_c01 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_GEM_GE_RECs_data_GE_REC_c01* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_GEM_GE_RECs_data_GE_REC_c02".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_GEM_GE_RECs_data_GE_REC_c02 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_GEM_GE_RECs_data_GE_REC_c02* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_GEM_GE_RECs_data_GE_REC_c02 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_GEM_GE_RECs_data_GE_REC_c02* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_GEM_GE_RECs_data_GE_REC_c03".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_GEM_GE_RECs_data_GE_REC_c03 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_GEM_GE_RECs_data_GE_REC_c03* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_GEM_GE_RECs_data_GE_REC_c03 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_GEM_GE_RECs_data_GE_REC_c03* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_GEM_GE_RECs_data_GE_REC_c04".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_GEM_GE_RECs_data_GE_REC_c04 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_GEM_GE_RECs_data_GE_REC_c04* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_GEM_GE_RECs_data_GE_REC_c04 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_GEM_GE_RECs_data_GE_REC_c04* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_GEM_GE_RECs_data_GE_REC".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_GEM_GE_RECs_data_GE_REC (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_GEM_GE_RECs_data_GE_REC* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_GEM_GE_RECs_data_GE_REC (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_GEM_GE_RECs_data_GE_REC* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_GEM_GE_RECs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_GEM_GE_RECs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_GEM_GE_RECs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_GEM_GE_RECs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_GEM_GE_RECs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_csch_mini6".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_csch_mini6 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_csch_mini6* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_csch_mini6 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_csch_mini6* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_ORDM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_ORDM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_ORDM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_ORDM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_ORDM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_AUCRM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_AUCRM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_AUCRM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_AUCRM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_AUCRM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_FWIM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_FWIM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_FWIM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_FWIM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_FWIM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_DBM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_DBM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_DBM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_DBM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_DBM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_DBM_FIELDSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_DBM_FIELDSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_DBM_FIELDSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_DBM_FIELDSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_DBM_FIELDSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_PSMM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PSMM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PSMM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PSMM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PSMM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_PSMM_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PSMM_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PSMM_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PSMM_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PSMM_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_PMRM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PMRM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PMRM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PMRM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PMRM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_PMRM_PILOTSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PMRM_PILOTSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PMRM_PILOTSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PMRM_PILOTSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PMRM_PILOTSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_BDTMFM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_BDTMFM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_BDTMFM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_BDTMFM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_BDTMFM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_BDTMFM_DIGITSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_BDTMFM_DIGITSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_BDTMFM_DIGITSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_BDTMFM_DIGITSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_BDTMFM_DIGITSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_STM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_STM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_STM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_STM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_STM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_ORCM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_ORCM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_ORCM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_ORCM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_ORCM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_ORCM_FIELDSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_ORCM_FIELDSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_ORCM_FIELDSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_ORCM_FIELDSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_ORCM_FIELDSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_HOCM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_HOCM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_HOCM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_HOCM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_HOCM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_HOCM_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_HOCM_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_HOCM_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_HOCM_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_HOCM_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_PRSM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PRSM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PRSM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PRSM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PRSM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_PRSM_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PRSM_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PRSM_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PRSM_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PRSM_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_SRQM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_SRQM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_SRQM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_SRQM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_SRQM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_SRPM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_SRPM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_SRPM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_SRPM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_SRPM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_SCCM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_SCCM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_SCCM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_SCCM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_SCCM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_SOCM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_SOCM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_SOCM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_SOCM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_SOCM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_STRPM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_STRPM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_STRPM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_STRPM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_STRPM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_TACM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_TACM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_TACM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_TACM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_TACM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_SCRM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_SCRM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_SCRM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_SCRM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_SCRM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_SCRM_records".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_SCRM_records (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_SCRM_records* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_SCRM_records (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_SCRM_records* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_SCRM_ACT_PNs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_SCRM_ACT_PNs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_SCRM_ACT_PNs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_SCRM_ACT_PNs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_SCRM_ACT_PNs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_SCRM_NGHBR_PNs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_SCRM_NGHBR_PNs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_SCRM_NGHBR_PNs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_SCRM_NGHBR_PNs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_SCRM_NGHBR_PNs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_SCRM_records_Type_specific_fields_000".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_SCRM_records_Type_specific_fields_000 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_SCRM_records_Type_specific_fields_000* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_SCRM_records_Type_specific_fields_000 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_SCRM_records_Type_specific_fields_000* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_SCRM_ACT_PNs_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_SCRM_ACT_PNs_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_SCRM_ACT_PNs_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_SCRM_ACT_PNs_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_SCRM_ACT_PNs_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_CFSRSM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_CFSRSM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_CFSRSM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_CFSRSM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_CFSRSM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_CFSRPM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_CFSRPM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_CFSRPM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_CFSRPM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_CFSRPM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_CFSRPM_Mode_specific_fields_0000_PILOTSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_CFSRPM_Mode_specific_fields_0000_PILOTSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_CFSRPM_Mode_specific_fields_0000_PILOTSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_CFSRPM_Mode_specific_fields_0000_PILOTSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_CFSRPM_Mode_specific_fields_0000_PILOTSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_CFSRPM_Mode_specific_fields_0000_PILOTSs_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_CFSRPM_Mode_specific_fields_0000_PILOTSs_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_CFSRPM_Mode_specific_fields_0000_PILOTSs_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_CFSRPM_Mode_specific_fields_0000_PILOTSs_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_CFSRPM_Mode_specific_fields_0000_PILOTSs_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_CFSRPM_Mode_specific_fields_0000".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_CFSRPM_Mode_specific_fields_0000 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_CFSRPM_Mode_specific_fields_0000* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_CFSRPM_Mode_specific_fields_0000 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_CFSRPM_Mode_specific_fields_0000* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_CFSRPM_Mode_specific_fields_0001".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_CFSRPM_Mode_specific_fields_0001 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_CFSRPM_Mode_specific_fields_0001* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_CFSRPM_Mode_specific_fields_0001 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_CFSRPM_Mode_specific_fields_0001* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_CFSRPM_Mode_specific_fields_0001_ANALOG_FREQS_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_CFSRPM_Mode_specific_fields_0001_ANALOG_FREQS_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_CFSRPM_Mode_specific_fields_0001_ANALOG_FREQS_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_CFSRPM_Mode_specific_fields_0001_ANALOG_FREQS_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_CFSRPM_Mode_specific_fields_0001_ANALOG_FREQS_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_PPSMM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PPSMM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PPSMM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PPSMM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PPSMM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_PPSMM_PILOTs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PPSMM_PILOTs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PPSMM_PILOTs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PPSMM_PILOTs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PPSMM_PILOTs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_PPSMM_PILOTs_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PPSMM_PILOTs_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PPSMM_PILOTs_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PPSMM_PILOTs_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PPSMM_PILOTs_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_PPSMM_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PPSMM_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PPSMM_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PPSMM_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PPSMM_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_PPSMM_PILOTs_01_data_records".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PPSMM_PILOTs_01_data_records (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PPSMM_PILOTs_01_data_records* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PPSMM_PILOTs_01_data_records (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PPSMM_PILOTs_01_data_records* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_PPSMM_PILOTs_01_data_records_Type_specific_fields_000".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PPSMM_PILOTs_01_data_records_Type_specific_fields_000 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PPSMM_PILOTs_01_data_records_Type_specific_fields_000* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PPSMM_PILOTs_01_data_records_Type_specific_fields_000 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PPSMM_PILOTs_01_data_records_Type_specific_fields_000* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_OLRM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_OLRM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_OLRM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_OLRM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_OLRM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_OLRM_data_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_OLRM_data_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_OLRM_data_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_OLRM_data_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_OLRM_data_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_RRM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_RRM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_RRM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_RRM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_RRM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_RRMM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_RRMM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_RRMM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_RRMM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_RRMM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_ERRM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_ERRM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_ERRM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_ERRM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_ERRM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_ERRMM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_ERRMM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_ERRMM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_ERRMM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_ERRMM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_PSMMM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_PSMMM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_PSMMM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_PSMMM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_PSMMM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_SCRMM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_SCRMM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_SCRMM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_SCRMM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_SCRMM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_RRRM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_RRRM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_RRRM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_RRRM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_RRRM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_RRRM_ADD_CON_REFs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_RRRM_ADD_CON_REFs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_RRRM_ADD_CON_REFs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_RRRM_ADD_CON_REFs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_RRRM_ADD_CON_REFs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_RRRM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_RRRM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_RRRM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_RRRM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_RRRM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_RRRM_BCMC_PROGRAMSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_RRRM_BCMC_PROGRAMSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_RRRM_BCMC_PROGRAMSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_RRRM_BCMC_PROGRAMSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_RRRM_BCMC_PROGRAMSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_RRRMM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_RRRMM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_RRRMM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_RRRMM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_RRRMM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_UZURM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_UZURM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_UZURM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_UZURM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_UZURM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_EOM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_EOM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_EOM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_EOM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_EOM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_EOM_ALT_SOs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_EOM_ALT_SOs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_EOM_ALT_SOs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_EOM_ALT_SOs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_EOM_ALT_SOs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_EOM_FIELDSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_EOM_FIELDSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_EOM_FIELDSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_EOM_FIELDSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_EOM_FIELDSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_EOM_ADD_SERV_INSTANCEs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_EOM_ADD_SERV_INSTANCEs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_EOM_ADD_SERV_INSTANCEs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_EOM_ADD_SERV_INSTANCEs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_EOM_ADD_SERV_INSTANCEs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_EOM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_EOM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_EOM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_EOM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_EOM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_EOM_BCMC_PROGRAMSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_EOM_BCMC_PROGRAMSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_EOM_BCMC_PROGRAMSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_EOM_BCMC_PROGRAMSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_EOM_BCMC_PROGRAMSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_EFWIM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_EFWIM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_EFWIM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_EFWIM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_EFWIM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_EPSMM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_EPSMM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_EPSMM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_EPSMM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_EPSMM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_EPSMM_records".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_EPSMM_records (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_EPSMM_records* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_EPSMM_records (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_EPSMM_records* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_EPSMM_records_Type_specific_fields_000".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_EPSMM_records_Type_specific_fields_000 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_EPSMM_records_Type_specific_fields_000* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_EPSMM_records_Type_specific_fields_000 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_EPSMM_records_Type_specific_fields_000* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_EPSMM_PILOTSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_EPSMM_PILOTSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_EPSMM_PILOTSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_EPSMM_PILOTSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_EPSMM_PILOTSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_EPSMM_PILOTSs_01_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_EPSMM_PILOTSs_01_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_EPSMM_PILOTSs_01_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_EPSMM_PILOTSs_01_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_EPSMM_PILOTSs_01_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_EHOCM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_EHOCM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_EHOCM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_EHOCM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_EHOCM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_EHOCM_PILOTSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_EHOCM_PILOTSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_EHOCM_PILOTSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_EHOCM_PILOTSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_EHOCM_PILOTSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_EHOCM_PILOTSs_data_records".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_EHOCM_PILOTSs_data_records (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_EHOCM_PILOTSs_data_records* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_EHOCM_PILOTSs_data_records (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_EHOCM_PILOTSs_data_records* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_EHOCM_PILOTSs_data_records_Type_specific_fields_000".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_EHOCM_PILOTSs_data_records_Type_specific_fields_000 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_EHOCM_PILOTSs_data_records_Type_specific_fields_000* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_EHOCM_PILOTSs_data_records_Type_specific_fields_000 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_EHOCM_PILOTSs_data_records_Type_specific_fields_000* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_SMRM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_SMRM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_SMRM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_SMRM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_SMRM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_SMRM_RECSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_SMRM_RECSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_SMRM_RECSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_SMRM_RECSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_SMRM_RECSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_CLCM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_CLCM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_CLCM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_CLCM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_CLCM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_CLCM_ADD_TAGs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_CLCM_ADD_TAGs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_CLCM_ADD_TAGs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_CLCM_ADD_TAGs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_CLCM_ADD_TAGs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_DIM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_DIM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_DIM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_DIM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_DIM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_BSSREQM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_BSSREQM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_BSSREQM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_BSSREQM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_BSSREQM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_BSSREQM_RECORDs_data_Record_Type_Specific_Fields_PILOTSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_BSSREQM_RECORDs_data_Record_Type_Specific_Fields_PILOTSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_BSSREQM_RECORDs_data_Record_Type_Specific_Fields_PILOTSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_BSSREQM_RECORDs_data_Record_Type_Specific_Fields_PILOTSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_BSSREQM_RECORDs_data_Record_Type_Specific_Fields_PILOTSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_BSSREQM_RECORDs_data_Record_Type_Specific_Fields".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_BSSREQM_RECORDs_data_Record_Type_Specific_Fields (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_BSSREQM_RECORDs_data_Record_Type_Specific_Fields* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_BSSREQM_RECORDs_data_Record_Type_Specific_Fields (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_BSSREQM_RECORDs_data_Record_Type_Specific_Fields* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_BSSREQM_RECORDs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_BSSREQM_RECORDs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_BSSREQM_RECORDs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_BSSREQM_RECORDs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_BSSREQM_RECORDs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_COTRM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_COTRM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_COTRM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_COTRM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_COTRM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_AURSPM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_AURSPM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_AURSPM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_AURSPM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_AURSPM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_AURSYNM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_AURSYNM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_AURSYNM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_AURSYNM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_AURSYNM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_ITBSPMRM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_ITBSPMRM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_ITBSPMRM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_ITBSPMRM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_ITBSPMRM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_ITBSPMRM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_ITBSPMRM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_ITBSPMRM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_ITBSPMRM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_ITBSPMRM_BCMC_PROGRAMSs_data_FLOW_DISCRIMINATORs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_ITBSPMRM_BCMC_PROGRAMSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_ITBSPMRM_BCMC_PROGRAMSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_ITBSPMRM_BCMC_PROGRAMSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_ITBSPMRM_BCMC_PROGRAMSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_ITBSPMRM_BCMC_PROGRAMSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_HOSINM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_HOSINM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_HOSINM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_HOSINM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_HOSINM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_HOSINM_HO_SUP_RECs_data_HO_SUP_REC".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_HOSINM_HO_SUP_RECs_data_HO_SUP_REC (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_HOSINM_HO_SUP_RECs_data_HO_SUP_REC* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_HOSINM_HO_SUP_RECs_data_HO_SUP_REC (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_HOSINM_HO_SUP_RECs_data_HO_SUP_REC* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_HOSINM_HO_SUP_RECs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_HOSINM_HO_SUP_RECs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_HOSINM_HO_SUP_RECs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_HOSINM_HO_SUP_RECs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_HOSINM_HO_SUP_RECs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_GEM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_GEM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_GEM* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_GEM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_GEM* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_GEM_GE_RECs_data_GE_REC_c01_BAND_SUBCLASSs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_GEM_GE_RECs_data_GE_REC_c01_BAND_SUBCLASSs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_GEM_GE_RECs_data_GE_REC_c01_BAND_SUBCLASSs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_GEM_GE_RECs_data_GE_REC_c01_BAND_SUBCLASSs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_GEM_GE_RECs_data_GE_REC_c01_BAND_SUBCLASSs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_GEM_GE_RECs_data_GE_REC_c01".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_GEM_GE_RECs_data_GE_REC_c01 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_GEM_GE_RECs_data_GE_REC_c01* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_GEM_GE_RECs_data_GE_REC_c01 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_GEM_GE_RECs_data_GE_REC_c01* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_GEM_GE_RECs_data_GE_REC_c02".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_GEM_GE_RECs_data_GE_REC_c02 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_GEM_GE_RECs_data_GE_REC_c02* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_GEM_GE_RECs_data_GE_REC_c02 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_GEM_GE_RECs_data_GE_REC_c02* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_GEM_GE_RECs_data_GE_REC_c03".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_GEM_GE_RECs_data_GE_REC_c03 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_GEM_GE_RECs_data_GE_REC_c03* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_GEM_GE_RECs_data_GE_REC_c03 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_GEM_GE_RECs_data_GE_REC_c03* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_GEM_GE_RECs_data_GE_REC_c04".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_GEM_GE_RECs_data_GE_REC_c04 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_GEM_GE_RECs_data_GE_REC_c04* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_GEM_GE_RECs_data_GE_REC_c04 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_GEM_GE_RECs_data_GE_REC_c04* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_GEM_GE_RECs_data_GE_REC".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_GEM_GE_RECs_data_GE_REC (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_GEM_GE_RECs_data_GE_REC* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_GEM_GE_RECs_data_GE_REC (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_GEM_GE_RECs_data_GE_REC* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_GEM_GE_RECs_data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_GEM_GE_RECs_data (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_GEM_GE_RECs_data* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_GEM_GE_RECs_data (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_GEM_GE_RECs_data* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_mini3".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_mini3 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_mini3* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_mini3 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_mini3* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "r_dsch_mini6".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_r_dsch_mini6 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_r_dsch_mini6* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_r_dsch_mini6 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_r_dsch_mini6* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "GenericTLV_cs0005".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_GenericTLV_cs0005 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GenericTLV_cs0005* ED_CONST Source, CS0005E_Details* pp_CS0005E_Details));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_GenericTLV_cs0005 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GenericTLV_cs0005* ED_CONST Destin, ED_EXLONG Length, CS0005E_Details* pp_CS0005E_Details));


#ifdef __cplusplus
	}
#endif
#endif

