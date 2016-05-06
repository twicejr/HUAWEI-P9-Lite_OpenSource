/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.83
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __Downlink_RLC_MAC_h
#define __Downlink_RLC_MAC_h
#include "ed_lib.h"
#include "ed_c.h"
#include "ed_user.h"
#include "endec_configs.h"


#ifdef __cplusplus
	extern "C" {
#endif


/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Cell_Change_Order".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_Packet_Cell_Change_Order (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Cell_Change_Order* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Cell_Change_Order".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Cell_Change_Order (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Cell_Change_Order* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Downlink_Assignment".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_Packet_Downlink_Assignment (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Downlink_Assignment* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Downlink_Assignment".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Downlink_Assignment (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Downlink_Assignment* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Measurement_Order".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_Packet_Measurement_Order (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Measurement_Order* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Measurement_Order".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Measurement_Order (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Measurement_Order* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Polling_Request".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_Packet_Polling_Request (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Polling_Request* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Polling_Request".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Polling_Request (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Polling_Request* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Power_Control_Timing_Advance".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_Packet_Power_Control_Timing_Advance (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Power_Control_Timing_Advance* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Power_Control_Timing_Advance".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Power_Control_Timing_Advance (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Power_Control_Timing_Advance* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Queueing_Notification".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_Packet_Queueing_Notification (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Queueing_Notification* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Queueing_Notification".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Queueing_Notification (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Queueing_Notification* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Timeslot_Reconfigure".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_Packet_Timeslot_Reconfigure (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Timeslot_Reconfigure* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Timeslot_Reconfigure".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Timeslot_Reconfigure (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Timeslot_Reconfigure* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_TBF_Release".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_Packet_TBF_Release (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_TBF_Release* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_TBF_Release".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_Packet_TBF_Release (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_TBF_Release* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Uplink_Ack_Nack".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_Packet_Uplink_Ack_Nack (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Uplink_Ack_Nack* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Uplink_Ack_Nack".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Uplink_Ack_Nack (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Uplink_Ack_Nack* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Uplink_Assignment".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_Packet_Uplink_Assignment (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Uplink_Assignment* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Uplink_Assignment".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Uplink_Assignment (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Uplink_Assignment* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Cell_Change_Continue".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_Packet_Cell_Change_Continue (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Cell_Change_Continue* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Cell_Change_Continue".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Cell_Change_Continue (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Cell_Change_Continue* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Neighbour_Cell_Data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_Packet_Neighbour_Cell_Data (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Neighbour_Cell_Data* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Neighbour_Cell_Data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Neighbour_Cell_Data (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Neighbour_Cell_Data* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Serving_Cell_Data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_Packet_Serving_Cell_Data (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Serving_Cell_Data* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Serving_Cell_Data".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Serving_Cell_Data (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Serving_Cell_Data* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Access_Reject".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_Packet_Access_Reject (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Access_Reject* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Access_Reject".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Access_Reject (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Access_Reject* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Paging_Request".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_Packet_Paging_Request (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Paging_Request* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Paging_Request".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Paging_Request (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Paging_Request* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_PDCH_Release".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_Packet_PDCH_Release (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_PDCH_Release* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_PDCH_Release".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_Packet_PDCH_Release (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_PDCH_Release* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_PRACH_Parameters".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_Packet_PRACH_Parameters (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_PRACH_Parameters* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_PRACH_Parameters".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_Packet_PRACH_Parameters (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_PRACH_Parameters* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Downlink_Dummy_Control_Block".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_Packet_Downlink_Dummy_Control_Block (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Downlink_Dummy_Control_Block* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Downlink_Dummy_Control_Block".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Downlink_Dummy_Control_Block (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Downlink_Dummy_Control_Block* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PSI1".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_PSI1 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI1* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PSI1".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_PSI1 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI1* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PSI2".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_PSI2 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI2* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PSI2".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_PSI2 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI2* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PSI3".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_PSI3 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI3* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PSI3".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_PSI3 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI3* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PSI3_bis".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_PSI3_bis (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI3_bis* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PSI3_bis".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_PSI3_bis (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI3_bis* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PSI4".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_PSI4 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI4* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PSI4".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_PSI4 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI4* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PSI5".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_PSI5 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI5* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PSI5".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_PSI5 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI5* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PSI13".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_PSI13 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI13* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PSI13".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_PSI13 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI13* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PSI14".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_PSI14 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI14* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PSI14".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_PSI14 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI14* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PSI3_ter".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_PSI3_ter (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI3_ter* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PSI3_ter".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_PSI3_ter (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI3_ter* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PSI3_quater".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_PSI3_quater (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI3_quater* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PSI3_quater".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_PSI3_quater (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PSI3_quater* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Serving_Cell_SI".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_Packet_Serving_Cell_SI (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Serving_Cell_SI* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Serving_Cell_SI".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Serving_Cell_SI (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Serving_Cell_SI* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PS_Handover_Command".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_PS_Handover_Command (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PS_Handover_Command* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PS_Handover_Command".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_PS_Handover_Command (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PS_Handover_Command* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Packet_Physical_Information".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_c_Packet_Physical_Information (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Physical_Information* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "Packet_Physical_Information".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long DECODE_BODY_c_Packet_Physical_Information (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_Packet_Physical_Information* ED_CONST Destin, long Length);

int Match_c_Packet_Cell_Change_Order (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_Downlink_Assignment (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_Measurement_Order (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_Polling_Request (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_Power_Control_Timing_Advance (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_Queueing_Notification (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_Timeslot_Reconfigure (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_TBF_Release (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_Uplink_Ack_Nack (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_Uplink_Assignment (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_Cell_Change_Continue (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_Neighbour_Cell_Data (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_Serving_Cell_Data (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_Access_Reject (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_Paging_Request (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_PDCH_Release (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_PRACH_Parameters (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_Downlink_Dummy_Control_Block (const char* Buffer, ED_CONST long BitOffset);
int Match_c_PSI1 (const char* Buffer, ED_CONST long BitOffset);
int Match_c_PSI2 (const char* Buffer, ED_CONST long BitOffset);
int Match_c_PSI3 (const char* Buffer, ED_CONST long BitOffset);
int Match_c_PSI3_bis (const char* Buffer, ED_CONST long BitOffset);
int Match_c_PSI4 (const char* Buffer, ED_CONST long BitOffset);
int Match_c_PSI5 (const char* Buffer, ED_CONST long BitOffset);
int Match_c_PSI13 (const char* Buffer, ED_CONST long BitOffset);
int Match_c_PSI14 (const char* Buffer, ED_CONST long BitOffset);
int Match_c_PSI3_ter (const char* Buffer, ED_CONST long BitOffset);
int Match_c_PSI3_quater (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_Serving_Cell_SI (const char* Buffer, ED_CONST long BitOffset);
int Match_c_PS_Handover_Command (const char* Buffer, ED_CONST long BitOffset);
int Match_c_Packet_Physical_Information (const char* Buffer, ED_CONST long BitOffset);

#ifdef __cplusplus
	};
#endif
#endif

