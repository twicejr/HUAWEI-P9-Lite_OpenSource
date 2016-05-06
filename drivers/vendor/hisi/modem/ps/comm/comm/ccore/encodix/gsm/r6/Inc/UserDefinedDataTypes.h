/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.83
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __UserDefinedDataTypes_h
#define __UserDefinedDataTypes_h

/* Modified by y00142674 for GSM编解码单编译, 2015-11-23, begin */
#ifdef __cplusplus
    extern "C" {
#endif

/*****************************************************************************
  1 其他头文件包含                            
*****************************************************************************/
#include "vos.h" 
#include "ed_lib.h"
#include "ed_c.h"
#include "ed_user.h"
#include "endec_configs.h"


/*****************************************************************************
  2 STRUCT定义
*****************************************************************************/
/*****************************************************************************
 结构名    : ENCODIX_GSM_SEM_STRU
 结构说明  : Csn1编解码Gsm信号量描述
 修改历史  :
 1.日    期   : 2015年11月23日
   作    者   : y00142674
   修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFlag;             /* 信号量标识 */
    VOS_SEM                             ulID;               /* 信号量ID */
}ENCODIX_GSM_SEM_STRU;


/*****************************************************************************
  3 宏定义 
*****************************************************************************/
#define GAS_GetEncodixSemDesc()         ( &( gstSemDesc ) )
#define GAS_GetEncodixSemId()           ( GAS_GetEncodixSemDesc()->ulID )

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern ENCODIX_GSM_SEM_STRU             gstSemDesc;


/*****************************************************************************
  5 函数声明
*****************************************************************************/

/* Modified by y00142674 for GSM编解码单编译, 2015-11-23, end */

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "LocationAreaId".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_LocationAreaId (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_LocationAreaId* ED_CONST Source);

long DECODE_c_LocationAreaId (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_LocationAreaId* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MobileStationClassmark2".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_MobileStationClassmark2 (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_MobileStationClassmark2* ED_CONST Source);

long DECODE_c_MobileStationClassmark2 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_MobileStationClassmark2* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RoutingAreaIdenti".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_RoutingAreaIdenti (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_RoutingAreaIdenti* ED_CONST Source);

long DECODE_c_RoutingAreaIdenti (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_RoutingAreaIdenti* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CipheringKeySequenceNumber".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_CipheringKeySequenceNumber (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CipheringKeySequenceNumber* ED_CONST Source);

long DECODE_c_CipheringKeySequenceNumber (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CipheringKeySequenceNumber* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CellDescription".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_CellDescription (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CellDescription* ED_CONST Source);

long DECODE_c_CellDescription (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CellDescription* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CellOptions".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_CellOptions (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CellOptions* ED_CONST Source);

long DECODE_c_CellOptions (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CellOptions* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CellOptionsSacch".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_CellOptionsSacch (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CellOptionsSacch* ED_CONST Source);

long DECODE_c_CellOptionsSacch (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CellOptionsSacch* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CellSelParam".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_CellSelParam (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CellSelParam* ED_CONST Source);

long DECODE_c_CellSelParam (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CellSelParam* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MACModeAndChCodReq".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_MACModeAndChCodReq (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_MACModeAndChCodReq* ED_CONST Source);

long DECODE_c_MACModeAndChCodReq (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_MACModeAndChCodReq* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "TChDesc".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_TChDesc (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_TChDesc* ED_CONST Source);

long DECODE_c_TChDesc (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_TChDesc* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "ClassmarkEnquiryMask".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_ClassmarkEnquiryMask (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_ClassmarkEnquiryMask* ED_CONST Source);

long DECODE_c_ClassmarkEnquiryMask (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_ClassmarkEnquiryMask* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "ChannelNeeded".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_ChannelNeeded (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_ChannelNeeded* ED_CONST Source);

long DECODE_c_ChannelNeeded (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_ChannelNeeded* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "ChannelRequestDesc".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_ChannelRequestDesc (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_ChannelRequestDesc* ED_CONST Source);

long DECODE_c_ChannelRequestDesc (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_ChannelRequestDesc* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CipherModeSetting".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_CipherModeSetting (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CipherModeSetting* ED_CONST Source);

long DECODE_c_CipherModeSetting (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CipherModeSetting* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CipherResponse".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_CipherResponse (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CipherResponse* ED_CONST Source);

long DECODE_c_CipherResponse (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CipherResponse* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CtrlChannelDesc".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_CtrlChannelDesc (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CtrlChannelDesc* ED_CONST Source);

long DECODE_c_CtrlChannelDesc (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CtrlChannelDesc* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FreqChannelSeq".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_FreqChannelSeq (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_FreqChannelSeq* ED_CONST Source);

long DECODE_c_FreqChannelSeq (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_FreqChannelSeq* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "GrpChannelDesc".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_GrpChannelDesc (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_GrpChannelDesc* ED_CONST Source);

long DECODE_c_GrpChannelDesc (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_GrpChannelDesc* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "GPRSResumption".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_GPRSResumption (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_GPRSResumption* ED_CONST Source);

long DECODE_c_GPRSResumption (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_GPRSResumption* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MeasurementSingleResult".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_MeasurementSingleResult (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_MeasurementSingleResult* ED_CONST Source);

long DECODE_c_MeasurementSingleResult (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_MeasurementSingleResult* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MeasurementResults".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_MeasurementResults (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_MeasurementResults* ED_CONST Source);

long DECODE_c_MeasurementResults (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_MeasurementResults* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "GPRSMeasurementResult".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_GPRSMeasurementResult (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_GPRSMeasurementResult* ED_CONST Source);

long DECODE_c_GPRSMeasurementResult (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_GPRSMeasurementResult* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MobileTimeDiff".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_MobileTimeDiff (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_MobileTimeDiff* ED_CONST Source);

long DECODE_c_MobileTimeDiff (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_MobileTimeDiff* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "DedicatedModeOrTBF".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_DedicatedModeOrTBF (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_DedicatedModeOrTBF* ED_CONST Source);

long DECODE_c_DedicatedModeOrTBF (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_DedicatedModeOrTBF* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "DedicatedModeOrTBF4b".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_DedicatedModeOrTBF4b (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_DedicatedModeOrTBF4b* ED_CONST Source);

long DECODE_c_DedicatedModeOrTBF4b (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_DedicatedModeOrTBF4b* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PageMode".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_PageMode (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_PageMode* ED_CONST Source);

long DECODE_c_PageMode (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PageMode* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PowerCommand".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_PowerCommand (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_PowerCommand* ED_CONST Source);

long DECODE_c_PowerCommand (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PowerCommand* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PowerCommandAndAccessType".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_PowerCommandAndAccessType (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_PowerCommandAndAccessType* ED_CONST Source);

long DECODE_c_PowerCommandAndAccessType (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_PowerCommandAndAccessType* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RACHCtrlParam".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_RACHCtrlParam (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_RACHCtrlParam* ED_CONST Source);

long DECODE_c_RACHCtrlParam (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_RACHCtrlParam* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RequestReference".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_RequestReference (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_RequestReference* ED_CONST Source);

long DECODE_c_RequestReference (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_RequestReference* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "StartingTime".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_StartingTime (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_StartingTime* ED_CONST Source);

long DECODE_c_StartingTime (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_StartingTime* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SyncInd".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_SyncInd (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_SyncInd* ED_CONST Source);

long DECODE_c_SyncInd (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_SyncInd* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "TimingAdvance".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_TimingAdvance (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_TimingAdvance* ED_CONST Source);

long DECODE_c_TimingAdvance (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_TimingAdvance* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "VGCSTargeModeIndication".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_VGCSTargeModeIndication (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_VGCSTargeModeIndication* ED_CONST Source);

long DECODE_c_VGCSTargeModeIndication (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_VGCSTargeModeIndication* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "IncSkipOfARFCN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_IncSkipOfARFCN (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_IncSkipOfARFCN* ED_CONST Source);

long DECODE_c_IncSkipOfARFCN (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_IncSkipOfARFCN* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "GrpChannelMA".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_GrpChannelMA (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_GrpChannelMA* ED_CONST Source);

long DECODE_c_GrpChannelMA (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_GrpChannelMA* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MeasurementResultsList".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_MeasurementResultsList (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_MeasurementResultsList* ED_CONST Source);

long DECODE_c_MeasurementResultsList (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_MeasurementResultsList* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MobileAllocation".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_MobileAllocation (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_MobileAllocation* ED_CONST Source);

long DECODE_c_MobileAllocation (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_MobileAllocation* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "NeighbourCellDescription".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_NeighbourCellDescription (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_NeighbourCellDescription* ED_CONST Source);

long DECODE_c_NeighbourCellDescription (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_NeighbourCellDescription* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "NeighbourCellDescription2".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_NeighbourCellDescription2 (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_NeighbourCellDescription2* ED_CONST Source);

long DECODE_c_NeighbourCellDescription2 (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_NeighbourCellDescription2* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MobileId".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_MobileId (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_MobileId* ED_CONST Source);

long DECODE_c_MobileId (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_MobileId* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "BaRange".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_BaRange (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_BaRange* ED_CONST Source);

long DECODE_c_BaRange (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_BaRange* ED_CONST Destin, long Length);

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CellChannel".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
long ENCODE_c_CellChannel (char* ED_CONST Buffer, ED_CONST long BitOffset, const c_CellChannel* ED_CONST Source);

long DECODE_c_CellChannel (const char* ED_CONST Buffer, ED_CONST long BitOffset, c_CellChannel* ED_CONST Destin, long Length);

ED_LONG GAS_ENCODIX_CheckGprsCellOptionExtVersion( c_SI13RestOctets_NoPBCCH_GPRS_Cell_Options *pstGprsCellOption );

#ifdef __cplusplus
	}
#endif
#endif

