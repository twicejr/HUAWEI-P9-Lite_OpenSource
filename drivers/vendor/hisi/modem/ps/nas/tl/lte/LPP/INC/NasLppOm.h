/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasLppOm.h
  Description     : NasLppOm.c header file
  History         :
     1.XiaoJun       2015-8-14     Draft Enact
     2.
******************************************************************************/

#ifndef __NASLPPOM_H__
#define __NASLPPOM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "NasLppPublic.h"
#include    "NasFileId.h"
#include    "LPPLRrcInterface.h"
#include    "NasLppAirMsg.h"
#include    "PsCommonDef.h"
#include    "EmmLppInterface.h"
#include    "NasLppEncodeDecodePublic.h"
#include    "NasCommPrint.h"
#include    "PsLogdef.h"
#include    "LppMtaInterface.h"
#include    "NasFileId.h"
#include    "NasLppIntraInterface.h"



/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/
#define    PS_MSG_ID_NAS_LPP_OM_BASE   100 /*后续统一定义???*/

#define NAS_LPP_WRITE_OM_MSG_HEAD(pstMsg, ulLppOmMsgID)\
                    (pstMsg)->ulMsgId   = (ulLppOmMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_LPP;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_OM;

#define NAS_LPP_OM_MAX_PARA_NUM         (3)

/*****************************************************************************
  4 Enum
*****************************************************************************/

enum    NAS_LPP_OMT_AIR_MSG_UP_DOWN_ENUM
{
    NAS_LPP_OMT_AIR_MSG_UP              = 0x00,            /* UPWARD */
    NAS_LPP_OMT_AIR_MSG_DOWN            = 0x01,             /* DOWNWARD */

    NAS_LPP_OMT_AIR_MSG_BUTT
};
typedef VOS_UINT8   NAS_LPP_OM_AIR_MSG_UP_DOWN_ENUM_UINT8;

enum NAS_LPP_OM_MSG_ENUM
{
    /* 定时器使用区间，需保留 */
    ID_NAS_LPP_OM_FSM_STATE                 = PS_MSG_ID_NAS_LPP_OM_BASE,    /* _H2ASN_MsgChoice NAS_LPP_OM_FSM_STATE_STRU */
    ID_NAS_LPP_OM_TIMER_START,                                                /* _H2ASN_MsgChoice NAS_LPP_OM_TIMER_START_STRU */
    ID_NAS_LPP_OM_TIMER_STOP,                                                /* _H2ASN_MsgChoice NAS_LPP_OM_TIMER_STOP_STRU  */
    ID_NAS_LPP_OM_TIMER_EXPIRE,                                                /* _H2ASN_MsgChoice NAS_LPP_OM_TIMER_EXPIRE_STRU */
    ID_NAS_LPP_OM_NV,                                                /* _H2ASN_MsgChoice NAS_LPP_OM_NV_STRU */
    ID_NAS_LPP_OM_CONN_MANAGE,                                                /* _H2ASN_MsgChoice NAS_LPP_OM_CONN_MANAGE_STRU */
    ID_NAS_LPP_OM_SESSION_MALLOC_SUCC,                                                /* _H2ASN_MsgChoice NAS_LPP_OM_SESSION_MALLOC_SUCC_STRU */
    ID_NAS_LPP_OM_SESSION_MALLOC_FAIL,                                                /* _H2ASN_MsgChoice NAS_LPP_OM_SESSION_MALLOC_FAIL_STRU */
    ID_NAS_LPP_OM_SESSION_RELEASE,                                                /* _H2ASN_MsgChoice NAS_LPP_OM_SESSION_RELEASE_STRU */
    ID_NAS_LPP_OM_TRANS_MALLOC_SUCC,                                                /* _H2ASN_MsgChoice NAS_LPP_OM_TRANS_MALLOC_SUCC_STRU */
    ID_NAS_LPP_OM_TRANS_MALLOC_FAIL,                                                /* _H2ASN_MsgChoice NAS_LPP_OM_TRANS_MALLOC_FAIL_STRU */
    ID_NAS_LPP_OM_TRANS_RELEASE,                                                /* _H2ASN_MsgChoice NAS_LPP_OM_TRANS_RELEASE_STRU */
    ID_NAS_LPP_OM_ADD_TRANS_TO_SESSION,                                                /* _H2ASN_MsgChoice NAS_LPP_OM_ADD_TRANS_TO_SESSION_STRU */
    ID_NAS_LPP_OM_COMM_CFG_MALLOC_SUCC,                                                /* _H2ASN_MsgChoice NAS_LPP_OM_COMM_CFG_MALLOC_SUCC_STRU */
    ID_NAS_LPP_OM_COMM_CFG_MALLOC_FAIL,                                                /* _H2ASN_MsgChoice NAS_LPP_OM_COMM_CFG_MALLOC_FAIL_STRU */
    ID_NAS_LPP_OM_COMM_CFG_RELEASE,                                                /* _H2ASN_MsgChoice NAS_LPP_OM_COMM_CFG_RELEASE_STRU */
    ID_NAS_LPP_OM_UP_MSG_BUFF_MALLOC_SUCC,                                                /* _H2ASN_MsgChoice NAS_LPP_OM_UP_MSG_BUFF_MALLOC_SUCC_STRU */
    ID_NAS_LPP_OM_UP_MSG_BUFF_MALLOC_FAIL,                                                /* _H2ASN_MsgChoice NAS_LPP_OM_UP_MSG_BUFF_MALLOC_FAIL_STRU */
    ID_NAS_LPP_OM_UP_MSG_BUFF_RELEASE,                                                /* _H2ASN_MsgChoice NAS_LPP_OM_UP_MSG_BUFF_REL_STRU */
    ID_NAS_LPP_OM_ADD_LOC_TECH,                                                /* _H2ASN_MsgChoice NAS_LPP_OM_ADD_LOC_TECH_STRU */
    ID_NAS_LPP_OM_DEL_LOC_TECH,                                                /* _H2ASN_MsgChoice NAS_LPP_OM_DEL_LOC_TECH_STRU */
    ID_NAS_LPP_OM_SEND_MTA_ASSIST_DATA,                                                /* _H2ASN_MsgChoice NAS_LPP_OM_MTA_ASSIST_DATA_STRU */
    ID_NAS_LPP_OM_SEND_MTA_LOC_INFO_REQ,                                                /* _H2ASN_MsgChoice NAS_LPP_OM_MTA_LOC_INFO_REQ_STRU */
    ID_NAS_LPP_OM_INTRA_DATA_CNF,                                               /* _H2ASN_MsgChoice NAS_LPP_OM_INTRA_DATA_CNF_STRU */
    ID_NAS_LPP_OM_MSG_BUTT
};
typedef VOS_UINT32  NAS_LPP_OM_MSG_ENUM_UINT32;

enum NAS_LPP_ASN_MSG_IE_TYPE_ENUM
{
    NAS_LPP_EPDU_SEQUENCE,
    NAS_LPP_NORMAL_VALUE,
    NAS_LPP_SEQUENCE_OF,
    NAS_LPP_EXT_OBJECT,
    NAS_LPP_BIT_STRING,
    NAS_LPP_SEQUENCE,
    NAS_LPP_INTEGER,
    NAS_LPP_CHOICE,
    NAS_LPP_ENUM,
    NAS_LPP_CHAR,
    NAS_LPP_DECODE_TRANSACTIONID_ERROR,
    NAS_LPP_DECODE_REQCAPAGNSS_ERROR,
    NAS_LPP_DECODE_REQCAPCOMMONIES_ERROR,
    NAS_LPP_DECODE_REQCAPOTDOA_ERROR,
    NAS_LPP_DECODE_EPDUIDENTIFIER_ERROR,
    NAS_LPP_DECODE_EPDUBODY_ERROR,
    NAS_LPP_DECODE_REQCAPR9IES_ERROR,
    NAS_LPP_DECODE_PROASSISTCOMIES_ERROR,
    NAS_LPP_DECODE_PROASSISTAGNSS_ERROR,
    NAS_LPP_DECODE_GNSSCOMMONASSISTDATA_ERROR,
    NAS_LPP_DECODE_GNSSREFTIME_ERROR,
    NAS_LPP_DECODE_GNSSSYSTIME_ERROR,
    NAS_LPP_DECODE_GNSSTIMEIDSTR_ERROR,
    NAS_LPP_DECODE_GPSTOWASSISELEMENT_ERROR,
    NAS_LPP_DECODE_GNSSREFTIMEFORCELL_ERROR,
    NAS_LPP_DECODE_NETTIME_ERROR,
    NAS_LPP_DECODE_EUTRA_ERROR,
    NAS_LPP_DECODE_CELLEUTRANANDUTRA_ERROR,
    NAS_LPP_DECODE_PLMNIDENTITY_ERROR,
    NAS_LPP_DECODE_UTRA_ERROR,
    NAS_LPP_DECODE_FDD_ERROR,
    NAS_LPP_DECODE_TDD_ERROR,
    NAS_LPP_DECODE_GSM_ERROR,
    NAS_LPP_DECODE_CELLGLOBALGERAN_ERROR,
    NAS_LPP_DECODE_GNSSREFLOCATION_ERROR,
    NAS_LPP_DECODE_ELLIPSOIDPOINTWITHALTIANDUNCERTELLIPSOID_ERROR,
    NAS_LPP_DECODE_GNSSIONOMODEL_ERROR,
    NAS_LPP_DECODE_KLOBUCHARMODEL_ERROR,
    NAS_LPP_DECODE_NEQUICKMODEL_ERROR,
    NAS_LPP_DECODE_GNSSEARTHPARAM_ERROR,
    NAS_LPP_DECODE_GNSSGENERICASSISTDATAELEMENT_ERROR,
    NAS_LPP_DECODE_GNSSID_ERROR,
    NAS_LPP_GNSSIDWITHEXTNOCHOICE_ERROR,
    NAS_LPP_SABSIDWITHEXTNOCHOICE_ERROR,
    NAS_LPP_DECODE_SBASID_ERROR,
    NAS_LPP_DECODE_GNSSTIMEMODELREQELEMENT_ERROR,
    NAS_LPP_DECODE_GNSSTIMEMODEL_ERROR,
    NAS_LPP_DECODE_GNSSDIFFCORRECTION_ERROR,
    NAS_LPP_DECODE_DGNSSREFTIME_ERROR,
    NAS_LPP_DECODE_GNSSNAVIGATIONMODEL_ERROR,
    NAS_LPP_DECODE_GNSSNAVMODELLISTELEMENT_ERROR,
    NAS_LPP_DECODE_GNSSSATLITELIST_ERROR,
    NAS_LPP_DECODE_SVID_ERROR,
    NAS_LPP_DECODE_STANDARDCLOCKMODELLISTELEMENT_ERROR,
    NAS_LPP_DECODE_NAVCLOCKMODEL_ERROR,
    NAS_LPP_DECODE_CNAVCLOCKMODEL_ERROR,
    NAS_LPP_DECODE_GLONASSCLOCKMODEL_ERROR,
    NAS_LPP_DECODE_SBASCLOCKMODEL_ERROR,
    NAS_LPP_DECODE_KEPLERSET_ERROR,
    NAS_LPP_DECODE_NAVKEPLERSET_ERROR,
    NAS_LPP_DECODE_CNAVKEPLERSET_ERROR,
    NAS_LPP_DECODE_GLONASSECEF_ERROR,
    NAS_LPP_DECODE_SBASECEF_ERROR,
    NAS_LPP_DECODE_GNSSREALTIMEINTEGRITY_ERROR,
    NAS_LPP_DECODE_GNSSBADSIGNALLISTELEMENT_ERROR,
    NAS_LPP_DECODE_GNSSBADSIGNALLIST_ERROR,
    NAS_LPP_DECODE_GNSSSIGNALIDS_ERROR,
    NAS_LPP_DECODE_GNSSBADBITSSATLISTELEMENT_ERROR,
    NAS_LPP_DECODE_DATABITSSATLIST_ERROR,
    NAS_LPP_DECODE_GNSSSIGNALID_ERROR,
    NAS_LPP_DECODE_GNSSBADBITSSGNLISTELEMENT_ERROR,
    NAS_LPP_DECODE_DATABITSASSIT_ERROR,
    NAS_LPP_DECODE_GNSSACQUISITIONASSIT_ERROR,
    NAS_LPP_DECODE_GNSSACQUISITIONASSITLISTELEMENT_ERROR,
    NAS_LPP_DECODE_GNSSACQUISITONASSITLIST_ERROR,
    NAS_LPP_DECODE_GNSSALMANAC_ERROR,
    NAS_LPP_DECODE_KEPLERIANALMANACSET_ERROR,
    NAS_LPP_DECODE_KEPLERIANNAVALMANAC_ERROR,
    NAS_LPP_DECODE_KEPLERIANREDUCEDALMANAC_ERROR,
    NAS_LPP_DECODE_KEPLERIANMIDIALMANAC_ERROR,
    NAS_LPP_DECODE_KEPLERIANGLONASS_ERROR,
    NAS_LPP_DECODE_ECEFSBASALMANAC_ERROR,
    NAS_LPP_ECELLIDERROR_ERROR,
    NAS_LPP_GNSSUTCMODEL_ERROR,
    NAS_LPP_DECODE_UTCMODEL1_ERROR,
    NAS_LPP_DECODE_UTCMODEL2_ERROR,
    NAS_LPP_DECODE_UTCMODEL3_ERROR,
    NAS_LPP_DECODE_UTCMODEL4_ERROR,
    NAS_LPP_GNSSAUXILIARYINFO_ERROR,
    NAS_LPP_DECODE_GNSSIDGPSELEMENT_ERROR,
    NAS_LPP_DECODE_GNSSIDGPS_ERROR,
    NAS_LPP_DECODE_GNSSIDGLONASSELEMENT_ERROR,
    NAS_LPP_DECODE_GNSSIDGLONASS_ERROR,
    NAS_LPP_GNSSERROR_ERROR,
    NAS_LPP_DECODE_GNSSERRORLOCATIONSERVER_ERROR,
    NAS_LPP_DECODE_GNSSTARGETDEVICE_ERROR,
    NAS_LPP_GNSSTARGETDEVICEERRORCAUSE_ERROR,
    NAS_LPP_DECODE_PROASSISTDATAR9IES_ERROR,
    NAS_LPP_DECODE_PROASSISTDATAOTDOA_ERROR,
    NAS_LPP_DECODE_OTDOAREFCELLINFO_ERROR,
    NAS_LPP_ARFCNEUTRANV9A0_ERROR,
    NAS_LPP_DECODE_PRSINFO_ERROR,
    NAS_LPP_PRSMUTINGINFOR9_ERROR,
    NAS_LPP_CPLENGTH_ERROR,
    NAS_LPP_DECODE_OTDOANEIGHBOURCELLINFOELEMENT_ERROR,
    NAS_LPP_ANTENNAPORTCONFIG_ERROR,
    NAS_LPP_PRSBANDWIDTH_ERROR,
    NAS_LPP_OTDOANEIGHBOURCELLINFOLIST_ERROR,
    NAS_LPP_OTDOANEIGHBOURCELLINFO_ERROR,
    NAS_LPP_DECODE_OTDOATARGETDEVICE_ERROR,
    NAS_LPP_OTDOATARGETDEVICEERRORCAUSE_ERROR,
    NAS_LPP_DECODE_OTDOAERRORLOCATIONSERVER_ERROR,
    NAS_LPP_OTDOAERROR_ERROR,
    NAS_LPP_MESSAGE_ERROR,
    NAS_LPP_DECODE_LOCATIONADDITONINFO_ERROR,
    NAS_LPP_ERRORCAUSE_ERROR,
    NAS_LPP_ABORTCAUSE_ERROR,
    NAS_LPP_LOCATIONINFOTYPE_ERROR,
    NAS_LPP_LOCATIONENVIRONMENT_ERROR,
    NAS_LPP_OTDOALOCATIONSERVERERRORCAUSE_ERROR,
    NAS_LPP_NUMDIFRAMES_ERROR,
    NAS_LPP_GNSSLOCATIONSERVERERRORCAUSE_ERROR,
    NAS_LPP_GNSSTIMEID_ERROR,
    NAS_LPP_DOPPLERUNCERTEXTR10_ERROR,
    NAS_LPP_EPDUERROR_ERROR,
    NAS_LPP_DGNSSSGNTYPELIST_ERROR,
    NAS_LPP_DECODE_CRITEXTABORTR9_ERROR,
    NAS_LPP_DECODE_OTDOAREQLOCATIONINFO_ERROR,
    NAS_LPP_DECODE_VERTICALACCURACY_ERROR,
    NAS_LPP_DECODE_HORIAZONTALACCURACY_ERROR,
    NAS_LPP_DECODE_ERRORIESR9_ERROR,
    NAS_LPP_DECODE_MESSAGE_ERROR,
    NAS_LPP_DECODE_ECELLIDREQLOCATIONINFO_ERROR,
    NAS_LPP_DECODE_AGNSSREQLOCATIONINFO_ERROR,
    NAS_LPP_DECODE_GNSSPOSITIONINGINSTRUCT_ERROR,
    NAS_LPP_DECODE_LOCATIONVELOCITYTYPES_ERROR,
    NAS_LPP_REPORTINGINTERVAL_ERROR,
    NAS_LPP_INTIATOR_ERROR,
    NAS_LPP_DECODE_DGNSSSGNTYPELISTELEMENT_ERROR,
    NAS_LPP_DECODE_RESPONSETIME_ERROR,
    NAS_LPP_CLOCKMODEL_ERROR,
    NAS_LPP_DECODE_LOCATIONQOS_ERROR,
    NAS_LPP_DECODE_LOCATIONCOORDINATETYPE_ERROR,
    NAS_LPP_DECODE_DGNSATLISTELEMENT_ERROR,
    NAS_LPP_DECODE_DGNSSSATLIST_ERROR,
    NAS_LPP_MUTINGINFO_ERROR,
    NAS_LPP_DECODE_COMMONIESREQLOCATIONINFO_ERROR,
    NAS_LPP_DECODE_REQLOCINFOR9IES_ERROR,
    NAS_LPP_DECODE_LOCATIONTRIGGEREDREPORTING_ERROR,
    NAS_LPP_CELLID_ERROR,
    NAS_LPP_DECODE_GNSSMETHODS_ERROR,
    NAS_LPP_GNSSALMANACLISTELEMENT_ERROR,
    NAS_LPP_DECODE_GNSSGENASSISTDATA_ERROR,
    NAS_LPP_DECODE_GNSSALMANACLIST_ERROR,

    /* ENCODE IE */
    NAS_LPP_ENCODE_EPDUBODY_ERROR,
    NAS_LPP_EPDUIDENTIFIER_ERROR,
    NAS_LPP_EPDUSEQUENCE_ERROR,
    NAS_LPP_INITIATOR_ERROR,
    NAS_LPP_GNSSID_ERROR,
    NAS_LPP_SBASIDS_ERROR,
    NAS_LPP_ACCESSTYPES_ERROR,
    NAS_LPP_POSITIONMODE_ERROR,
    NAS_LPP_AGNSSIESPROVIDECAPABILITIESGNSSSUPPORTLIST_ERROR,
    NAS_LPP_GNSSSYSTEMTIME_ERROR,
    NAS_LPP_GNSSCOMMONASSISTANCEDATASUPPORTINONMODELSUPPORT_ERROR,
    NAS_LPP_SBASID_ERROR,
    NAS_LPP_GNSSNAVIGATIONMODELSUPPORT_ERROR,
    NAS_LPP_UTCMODELSUPPORT_ERROR,
    NAS_LPP_ALMANACSUPPORT_ERROR,
    NAS_LPP_OTDOAMODE_ERROR,
    NAS_LPP_GNSSGENERICASSISTANCEDATASUPPORT_ERROR,
    NAS_LPP_SUPBANDEUTRA_ERROR,
    NAS_LPP_SUPBANDLISTEUTRA_ERROR,
    NAS_LPP_SUPBANDLISTEUTRAV9A0_ERROR,
    NAS_LPP_SUPBANDEUTRAV9A0_ERROR,
    NAS_LPP_ADNEIGHBOURCELLINFOLISTR10_ERROR,
    NAS_LPP_FREQRSTDMEASUREMENTR10_ERROR,
    NAS_LPP_ECIDMEASSUPPORTED_ERROR,
    NAS_LPP_PROVIDECAPABILITYC1_ERROR,
    NAS_LPP_PROVIDECAPABILITY_ERROR,
    NAS_LPP_OTDOAREQASSISTDATA_ERROR,
    NAS_LPP_GNSSREFTIMEREQ_ERROR,
    NAS_LPP_GNSSTIMEMODELELEMENTREQ_ERROR,
    NAS_LPP_GNSSTIMEMODELLISTREQ_ERROR,
    NAS_LPP_SVID_ERROR,
    NAS_LPP_SATLISTRELATEDDATALISTELEMENT_ERROR,
    NAS_LPP_STORENAVLISTINFO_ERROR,
    NAS_LPP_ORBITMODELID_ERROR,
    NAS_LPP_CLOCKMODELID_ERROR,
    NAS_LPP_GNSSNAVMODELREQ_ERROR,
    NAS_LPP_GNSSDATABITASSISTREQ_ERROR,
    NAS_LPP_SATLISTRELATEDDATALIST_ERROR,
    NAS_LPP_GNSSDATABITREQSATLIST_ERROR,
    NAS_LPP_GNSSSSIGNALID_ERROR,
    NAS_LPP_PRIMARYCELLID_ERROR,
    NAS_LPP_GNSSUTCMODELREQ_ERROR,
    NAS_LPP_GNSSALMANACREQ_ERROR,
    NAS_LPP_GNSSGENREQASSISTDATA_ERROR,
    NAS_LPP_EXTREQUESTASSISTDATA_ERROR,
    NAS_LPP_ELLIPSOIDPOINTWITHALTITUDE_ERROR,
    NAS_LPP_ELLIPSOIDARC_ERROR,
    NAS_LPP_POLYGONPOINTS_ERROR,
    NAS_LPP_LOCTIONESTIMATE_ERROR,
    NAS_LPP_POLYGON_ERROR,
    NAS_LPP_ELLIPSOIDPOINTWITHALTITUDEANDELLIPOID_ERROR,
    NAS_LPP_REQUESTASSISTDATA_ERROR,
    NAS_LPP_HORIZONTALWITHVERTICALVELOCITY_ERROR,
    NAS_LPP_HORIZONTALVELCOCTIY_ERROR,
    NAS_LPP_ELLIPSOIDPOINTWITHUNCERTAINTYELLIPSE_ERROR,
    NAS_LPP_HORIZONTALWITHUNCERITANITY_ERROR,
    NAS_LPP_HORIZONTALWITHVELOCTIYANDUNCERTAAINTY_ERROR,
    NAS_LPP_VELOCITYESTIMATE_ERROR,
    NAS_LPP_LOCATONFAILURECAUSE_ERROR,
    NAS_LPP_PLMNIDENTITY_ERROR,
    NAS_LPP_CELLIDENTITYETRANANDUTRAN_ERROR,
    NAS_LPP_UTRANMODE_ERROR,
    NAS_LPP_EUTRA_ERROR,
    NAS_LPP_GSM_ERROR,
    NAS_LPP_REFFRAME_ERROR,
    NAS_LPP_GNSSSATMEASELMENT_ERROR,
    NAS_LPP_MEASREFTIME_ERROR,
    NAS_LPP_GNSSSATMEASLIST_ERROR,
    NAS_LPP_GNSSSGNMEASLIST_ERROR,
    NAS_LPP_GNSSSGNMEASELEMENT_ERROR,
    NAS_LPP_AGNSSLIST_ERROR,
    NAS_LPP_ENCODE_GNSSLOCATIONSERVERERRORCAUSE_ERROR,
    NAS_LPP_ENCODE_GNSSTARGETDEVICEERRORCAUSE_ERROR,
    NAS_LPP_ENCODE_OTDOALOCATIONSERVERERRORCAUSE_ERROR,
    NAS_LPP_ENCODE_OTDOATARGETDEVICEERRORCAUSE_ERROR,
    NAS_LPP_MEASLIST_ERROR,
    NAS_LPP_AGNSSERROR_ERROR,
    NAS_LPP_ARFCNVALUEEUTRAN_ERROR,
    NAS_LPP_OTDOASIGNALMEASINFO_ERROR,
    NAS_LPP_EARFCNREFV9A0_ERROR,
    NAS_LPP_ENCODE_OTDOAERROR_ERROR,
    NAS_LPP_PRIMARYCELLMEASUREDRSLT_ERROR,
    NAS_LPP_MEASRSLTLIST_ERROR,
    NAS_LPP_ECELLIDLOCATIONSERVERERRORCAUSE_ERROR,
    NAS_LPP_NEIGHBOURMEASELEMENT_ERROR,
    NAS_LPP_ECELLIDTARGETDEVICEERRORCAUSE_ERROR,
    NAS_LPP_ENCODE_MESSAGE_ERROR,
    NAS_LPP_LPPMSGBODY_ERROR,
    NAS_LPP_LPPMSGC1_ERROR,
    NAS_LPP_ERRORMESSAGE_ERROR,
    NAS_LPP_ERRORR9IES_ERROR,
    NAS_LPP_COMMONIESERROR_ERROR,
    NAS_LPP_EXTABORTMESSAGE_ERROR,
    NAS_LPP_COMMONIESABORT_ERROR,
    NAS_LPP_C1EXTABORTMESSAGE_ERROR,
    NAS_LPP_NEIGHBOURMEASLIST_ERROR
};
typedef VOS_UINT32  NAS_LPP_ASN_MSG_IE_TYPE_ENUM_UINT32;
enum NAS_LPP_ASN_MSG_ERR_CAUSE_ENUM
{
    NAS_LPP_EXT_OBJECT_BIT_WARNING,
    NAS_LPP_EXT_OBJECT_BIT_ERROR,
    NAS_LPP_CHOICE_EXT_OBJECT_WARNING,
    NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
    NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
    NAS_LPP_EPDU_SEQUENCE_LEN_ERROR,
    NAS_LPP_NORMAL_VALUE_BIT_ERROR,
    NAS_LPP_BIT_STRING_LEN_ERROR,
    NAS_LPP_CHOICE_OUT_OF_RANGE,
    NAS_LPP_ENUM_OUT_OF_RANGE_WARNING,
    NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
    NAS_LPP_EMPTY_POINT,
    NAS_LPP_CHAR_LEN_ERROR,
    NAS_LPP_CHOICE_EXT_OBJECT_ERROR,
    NAS_LPP_NORMAL_VALUE_LARGE_WARNING,
    NAS_LPP_NORMAL_VALUE_LARGE_ERROR,
    NAS_LPP_OCTET_LEN_OUT_OF_RANGE
};
typedef VOS_UINT32  NAS_LPP_ASN_MSG_ERR_CAUSE_ENUM_UINT32;

typedef struct
{
    PS_HEADER_STRU                                          stMsgHeader;     /*_H2ASN_Skip*/
    NAS_LPP_ASN_MSG_IE_TYPE_ENUM_UINT32                     enIeType;
    NAS_LPP_ASN_MSG_ERR_CAUSE_ENUM_UINT32                 enCause;
    VOS_UINT32                                              ulBitPosValue;
    VOS_UINT32                                              ulLineNum;
    VOS_UINT32                                              ulRsvData;
}NAS_LPP_ASN_FAIL_STRU;


/*****************************************************************************
   5 STRUCT
*****************************************************************************/

/*******************************************************************************
 结构名    : NAS_LPP_OM_FSM_STATE_STRU
 结构说明  : 状态机的om信息
 1.日    期   : 2015年8月14日
   作    者   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;                /*_H2ASN_Skip*/

    VOS_UINT8                           ucSessionIndex;
    VOS_UINT8                           ucSessionTransIndex;
    VOS_UINT8                           ucTransIndex;
    VOS_UINT8                           ucRsv;

    NAS_LPP_MAIN_STATE_ENUM_UINT32      enOldMainState;
    NAS_LPP_SUB_STATE_ENUM_UINT32       enOldSubState;

    NAS_LPP_MAIN_STATE_ENUM_UINT32      enNewMainState;
    NAS_LPP_SUB_STATE_ENUM_UINT32       enNewSubState;
}NAS_LPP_OM_FSM_STATE_STRU;


/*******************************************************************************
 结构名    : NAS_LPP_OM_TIMER_START_STRU
 结构说明  : 状态机的om信息
 1.日    期   : 2015年8月14日
   作    者   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           ucSessionIndex;
    VOS_UINT8                           ucSessionTransIndex;
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName;
    VOS_UINT8                           aucRsv[1];
    VOS_UINT32                          ulLen;
}NAS_LPP_OM_TIMER_START_STRU;
/*******************************************************************************
 结构名    : NAS_LPP_OM_TIMER_STOP_STRU
 结构说明  : 状态机的om信息
 1.日    期   : 2015年8月14日
   作    者   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           ucSessionIndex;
    VOS_UINT8                           ucSessionTransIndex;
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName;
    VOS_UINT8                           aucRsv[1];
    VOS_UINT32                          ulRemainTime;
}NAS_LPP_OM_TIMER_STOP_STRU;
/*******************************************************************************
 结构名    : NAS_LPP_OM_TIMER_EXPIRE_STRU
 结构说明  : 状态机的om信息
 1.日    期   : 2015年8月14日
   作    者   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           ucSessionIndex;
    VOS_UINT8                           ucSessionTransIndex;
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName;
    VOS_UINT8                           aucRsv[1];
}NAS_LPP_OM_TIMER_EXPIRE_STRU;
/*******************************************************************************
 结构名    : NAS_LPP_OM_NV_STRU
 结构说明  :
 1.日    期   : 2015年8月14日
   作    者   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    NAS_LPP_NV_CONFIG_STRU              stNVRead;
}NAS_LPP_OM_NV_STRU;
/*******************************************************************************
 结构名    : NAS_LPP_OM_SESSION_MALLOC_SUCC_STRU
 结构说明  :
 1.日    期   : 2015年8月14日
   作    者   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           ucSessionIndex;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulSessionId;
    VOS_UINT32                          ulSessionPoolBitmap;  /*申请成功后的*/
}NAS_LPP_OM_SESSION_MALLOC_SUCC_STRU;
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    LPP_MTA_MSG_TYPE_ENUM_UINT32        enGnssAssistData;  /*Gnss assistance data*/
}NAS_LPP_OM_MTA_ASSIST_DATA_STRU;
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    LPP_MTA_MSG_TYPE_ENUM_UINT32        enLocInfoReq;  /*LOC INFO REQ*/
}NAS_LPP_OM_MTA_LOC_INFO_REQ_STRU;
/*******************************************************************************
 结构名    : NAS_LPP_OM_INTRA_DATA_CNF_STRU
 结构说明  :
 1.日    期   : 2015年8月14日
   作    者   :WANGENSHENG
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    NAS_LPP_MSG_IDENTITY_STRU           stLppMsgIdentity;
    NAS_LPP_ERROR_CODE_ENUM_UINT32      enRslt;
    VOS_UINT32                          ulOpId;

}NAS_LPP_OM_INTRA_DATA_CNF_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_OM_SESSION_MALLOC_FAIL_STRU
 结构说明  :
 1.日    期   : 2015年8月14日
   作    者   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT32                          ulSessionId;
    VOS_UINT32                          ulSessionPoolBitmap;
}NAS_LPP_OM_SESSION_MALLOC_FAIL_STRU;
/*******************************************************************************
 结构名    : NAS_LPP_OM_SESSION_RELEASE_STRU
 结构说明  :
 1.日    期   : 2015年8月14日
   作    者   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           ucSessionIndex;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulSessionId;
    VOS_UINT32                          ulSessionPoolBitmap; /*释放成功后的*/
}NAS_LPP_OM_SESSION_RELEASE_STRU;
/*******************************************************************************
 结构名    : NAS_LPP_OM_TRANS_MALLOC_SUCC_STRU
 结构说明  :
 1.日    期   : 2015年8月14日
   作    者   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    LPP_INITIATOR_TYPE_ENUM_UINT8       enInitiator;
    VOS_UINT8                           ucTransactionNumber;
    VOS_UINT8                           ucTransIndex;
    VOS_UINT8                           ucRsv;
    VOS_UINT32                          ulTransPoolBitmap;  /*申请成功后的*/
//    NAS_LPP_TRANSACTION_STRU            stLppTran;          /*申请成功后，session包含的trans idnex的情况*/
}NAS_LPP_OM_TRANS_MALLOC_SUCC_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_OM_TRANS_MALLOC_FAIL_STRU
 结构说明  :
 1.日    期   : 2015年8月14日
   作    者   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    LPP_INITIATOR_TYPE_ENUM_UINT8       enInitiator;
    VOS_UINT8                           ucTransactionNumber;
    VOS_UINT8                           aucRsv[1];
    VOS_UINT32                          ulTransPoolBitmap;  /*当前的*/
//    NAS_LPP_TRANSACTION_STRU            stLppTran;          /*当前的，session包含的trans idnex的情况*/
}NAS_LPP_OM_TRANS_MALLOC_FAIL_STRU;
/*******************************************************************************
 结构名    : NAS_LPP_OM_TRANS_RELEASE_STRU
 结构说明  :
 1.日    期   : 2015年8月14日
   作    者   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           ucSessionIndex;
    VOS_UINT8                           ucTransIndex;       /*被释放的*/
    VOS_UINT8                           aucRsv[2];
    VOS_UINT32                          ulTransPoolBitmap;  /*释放后的*/
    NAS_LPP_TRANSACTION_STRU            stLppTran;          /*释放后的，session包含的trans idnex的情况*/
}NAS_LPP_OM_TRANS_RELEASE_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_OM_ADD_TRANS_TO_SESSION_STRU
 结构说明  :
 1.日    期   : 2015年8月14日
   作    者   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           ucSessionIndex;
    VOS_UINT8                           ucTransIndex;       /*被加入session的transaction index*/
    VOS_UINT8                           aucRsv[2];
    NAS_LPP_TRANSACTION_STRU            stLppTran;          /*增加后的，session包含的trans idnex的情况*/
}NAS_LPP_OM_ADD_TRANS_TO_SESSION_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_OM_COMM_CFG_MALLOC_SUCC_STRU
 结构说明  :
 1.日    期   : 2015年8月14日
   作    者   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           ucTransIndex;
    VOS_UINT8                           ucCfgIndex;
    VOS_UINT8                           aucRsv[2];
    VOS_UINT32                          ulCfgPoolBitmap;    /*申请成功后的*/
}NAS_LPP_OM_COMM_CFG_MALLOC_SUCC_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_OM_COMM_CFG_MALLOC_FAIL_STRU
 结构说明  :
 1.日    期   : 2015年8月14日
   作    者   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           ucTransIndex;
    VOS_UINT8                           ucCfgIndex;
    VOS_UINT8                           aucRsv[2];
    VOS_UINT32                          ulCfgPoolBitmap;    /* 当前的*/
}NAS_LPP_OM_COMM_CFG_MALLOC_FAIL_STRU;
/*******************************************************************************
 结构名    : NAS_LPP_OM_COMM_CFG_RELEASE_STRU
 结构说明  :
 1.日    期   : 2015年8月14日
   作    者   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           ucTransIndex;
    VOS_UINT8                           ucCfgIndex;         /*被释放的*/
    VOS_UINT8                           aucRsv[2];
    VOS_UINT32                          ulCfgPoolBitmap;    /*释放后的*/
}NAS_LPP_OM_COMM_CFG_RELEASE_STRU;


/*******************************************************************************
 结构名    : NAS_LPP_OM_UP_MSG_BUFF_MALLOC_SUCC_STRU
 结构说明  :
 1.日    期   : 2015年8月14日
   作    者   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           ucUpLinkBuffIndex;/*申请到的*/
    VOS_UINT8                           aucRsv[3];
    NAS_LPP_UP_MSG_SEQUENCE_STRU        astUpmsgSeq[NAS_LPP_MAX_BUFF_MSG_COUNT]; /*申请后的*/
    VOS_UINT32                          ulBitMap;       /*申请后的*/
}NAS_LPP_OM_UP_MSG_BUFF_MALLOC_SUCC_STRU;


/*******************************************************************************
 结构名    : NAS_LPP_OM_UP_MSG_BUFF_MALLOC_FAIL_STRU
 结构说明  :
 1.日    期   : 2015年8月14日
   作    者   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    NAS_LPP_UP_MSG_SEQUENCE_STRU        astUpmsgSeq[NAS_LPP_MAX_BUFF_MSG_COUNT]; /*申请时的*/
    VOS_UINT32                          ulBitMap;       /*申请时的*/
}NAS_LPP_OM_UP_MSG_BUFF_MALLOC_FAIL_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_OM_UP_MSG_BUFF_REL_STRU
 结构说明  :
 1.日    期   : 2015年8月14日
   作    者   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           ucUpLinkBuffIndex;/*被释放的*/
    VOS_UINT8                           aucRsv[3];
    NAS_LPP_UP_MSG_SEQUENCE_STRU        astUpmsgSeq[NAS_LPP_MAX_BUFF_MSG_COUNT]; /*释放后的*/
    VOS_UINT32                          ulBitMap;       /*释放后的*/
}NAS_LPP_OM_UP_MSG_BUFF_REL_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_OM_ADD_LOC_TECH_STRU
 结构说明  :
 1.日    期   : 2015年8月14日
   作    者   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    NAS_LPP_POSITION_TECH_ENUM_UINT8    enPositionTech;  /*增加的loc tech*/
    VOS_UINT8                           aucRsv[3];
    NAS_LPP_LOC_TECH_RUNING_STRU        stLocTechRunning; /*增加后的*/
}NAS_LPP_OM_ADD_LOC_TECH_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_OM_DEL_LOC_TECH_STRU
 结构说明  :
 1.日    期   : 2015年8月14日
   作    者   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    NAS_LPP_POSITION_TECH_ENUM_UINT8    enPositionTech;  /*被删的loc tech*/
    VOS_UINT8                           aucRsv[3];
    NAS_LPP_LOC_TECH_RUNING_STRU        stLocTechRunning; /*删除后的*/
}NAS_LPP_OM_DEL_LOC_TECH_STRU;
/*******************************************************************************
 结构名    : NAS_LPP_OM_CONN_MANAGE_STRU
 结构说明  :
 1.日    期   : 2015年8月14日
   作    者   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    NAS_LPP_CONN_STATUS_ENUM_UINT32     enConnStatus;  /* CONNECT STATUS */
}NAS_LPP_OM_CONN_MANAGE_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_OM_LOG_ERROR_STRU
 结构说明  :
 1.日    期   : 2015年8月14日
   作    者   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    NAS_FILE_ID_DEFINE_ENUM_UINT32      enNasFileName;
    VOS_UINT32                          ulLine;
    NAS_LPP_ERROR_CODE_ENUM_UINT32      enErrorCode;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT8                           ucParaNum;
    VOS_UINT32                          aulPara[NAS_LPP_OM_MAX_PARA_NUM];
}NAS_LPP_OM_LOG_STRU;
typedef struct
{
    NAS_LPP_OM_MSG_ENUM_UINT32        enMsgID;            /*_H2ASN_MsgChoice_Export NAS_LPP_OM_MSG_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_LPP_OM_MSG_ENUM_UINT32
    ****************************************************************************/
}NAS_LPP_OM_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    NAS_LPP_OM_MSG_DATA                     stMsgData;
}NasLppOm_MSG;



/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID  NAS_LPP_OmAddTransToSessionInd
       (
           VOS_UINT8                           ucSessionIndex,
           VOS_UINT8                           ucTransIndex,
           NAS_LPP_TRANSACTION_STRU           *pstLppTrans
       );
extern VOS_VOID  NAS_LPP_OmSessionMallocInd
       (
           VOS_UINT8                           ucSessionIndex,
           VOS_UINT32                          ulSessionId,
           VOS_UINT32                          ulSessionPoolBitmap
       );
extern VOS_VOID  NAS_LPP_OmSessionRelInd
       (
           VOS_UINT8                           ucSessionIndex,
           VOS_UINT32                          ulSessionId,
           VOS_UINT32                          ulSessionPoolBitmap
       );
extern VOS_VOID  NAS_LPP_OmStateChgInd
       (
           VOS_UINT8                           ucSessionIndex,
           VOS_UINT8                           ucSessionTransIndex,
           VOS_UINT8                           ucTransIndex,
           NAS_LPP_MAIN_STATE_ENUM_UINT32      enOldMsState,
           NAS_LPP_SUB_STATE_ENUM_UINT32       enOldSubState,
           NAS_LPP_MAIN_STATE_ENUM_UINT32      enNewMsState,
           NAS_LPP_SUB_STATE_ENUM_UINT32       enNewSubState
       );
extern VOS_VOID  NAS_LPP_OmTimerExpireInd
       (
           VOS_UINT8                           ucSessionIndex,
           VOS_UINT8                           ucSessionTransIndex,
           NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName
       );
extern VOS_VOID  NAS_LPP_OmTimerStartInd
       (
           VOS_UINT8                           ucSessionIndex,
           VOS_UINT8                           ucSessionTransIndex,
           NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
           VOS_UINT32                          ulLen
       );
extern VOS_VOID  NAS_LPP_OmTimerStopInd
       (
            VOS_UINT8                           ucSessionIndex,
            VOS_UINT8                           ucSessionTransIndex,
            NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
            VOS_UINT32                          ulRemainTime
        );
extern VOS_VOID  NAS_LPP_OmTransMallocInd
       (
           VOS_UINT8                           ucTransIndex,
           VOS_UINT32                          ulTransPoolBitmap,
           NAS_LPP_TRANS_ID_STRU              *pstTransId
       );
extern VOS_VOID    NAS_LPP_ASN_FAIL_Message(
                                    VOS_UINT32          ulIEType,
                                    VOS_UINT32          ulIEErrorType,
                                    VOS_UINT32          ulBitPos,
                                    VOS_UINT32          ulLineNum,
                                    VOS_UINT32          ulRsv);
extern VOS_VOID  NAS_LPP_OmTransRelInd
       (
           VOS_UINT8                           ucSessionIndex,
           VOS_UINT8                           ucTransIndex,
           NAS_LPP_TRANSACTION_STRU           *pstLppTrans
       );
extern VOS_VOID  NAS_LPP_OmIntraDataCnf
(
    NAS_LPP_INTRA_DATA_CNF_STRU *pRcvMsg
);
extern VOS_VOID  NAS_LPP_OmAddTransToSessionInd
(
    VOS_UINT8                           ucSessionIndex,
    VOS_UINT8                           ucTransIndex,
    NAS_LPP_TRANSACTION_STRU           *pstLppTrans
);
extern VOS_VOID  NAS_LPP_OmCommCfgPoolMallocInd
(
    VOS_UINT8                           ucTransIndex,
    VOS_UINT8                           ucCommCfgIndex,
    VOS_UINT32                          ulCfgPoolBitmap
);
extern VOS_VOID  NAS_LPP_OmCommCfgPoolRelInd
(
    VOS_UINT8                           ucTransIndex,
    VOS_UINT8                           ucCommCfgIndex,
    VOS_UINT32                          ulCfgPoolBitmap
);
extern VOS_VOID  NAS_LPP_OmUpMsgBuffMallocSuccInd
(
    VOS_UINT8                           ucUpLinkBuffIndex,
    NAS_LPP_UP_MSG_SEQUENCE_STRU       *pstUpmsgSeq,
    VOS_UINT32                          ulBitMap
);
extern VOS_VOID  NAS_LPP_OmUpMsgBuffMallocFailInd
(
    NAS_LPP_UP_MSG_SEQUENCE_STRU       *pstUpmsgSeq,
    VOS_UINT32                          ulBitMap
);
extern VOS_VOID  NAS_LPP_OmUpMsgBuffRelInd
(
    VOS_UINT8                           ucUpLinkBuffIndex,
    NAS_LPP_UP_MSG_SEQUENCE_STRU       *pstUpmsgSeq,
    VOS_UINT32                          ulBitMap
);

extern VOS_VOID  NAS_LPP_OmAddLocTechInd
(
    NAS_LPP_POSITION_TECH_ENUM_UINT8    enPositionTech,
    NAS_LPP_LOC_TECH_RUNING_STRU       *pstLocTechRunning
);
extern VOS_VOID  NAS_LPP_OmDelLocTechInd
(
    NAS_LPP_POSITION_TECH_ENUM_UINT8    enPositionTech,
    NAS_LPP_LOC_TECH_RUNING_STRU       *pstLocTechRunning
);
extern VOS_VOID NAS_LPP_SendOmtAirMsg
(
    NAS_LPP_OM_AIR_MSG_UP_DOWN_ENUM_UINT8                   ucDir,
    OM_PS_AIR_MSG_ENUM_UINT8                                ucAirMsgId,
    VOS_UINT32                                              ulMsgLength,
    VOS_UINT8                                              *pucLppMsg
);
extern VOS_VOID  NAS_LPP_OmNVRead
(
    NAS_LPP_NV_CONFIG_STRU             *pstLppNvParaConfig
);
extern VOS_VOID  NAS_LPP_OmSetConnStatus
(
    NAS_LPP_CONN_STATUS_ENUM_UINT32     enConnStatus
);
extern OM_PS_AIR_MSG_ENUM_UINT8  NAS_LPP_OmGetMsgType
(
 NAS_LPP_OM_AIR_MSG_UP_DOWN_ENUM_UINT8   ucLppAirMsgType
 );
extern VOS_VOID  NAS_LPP_OM_LOG
(
    NAS_LPP_OM_MSG_ENUM_UINT32          enLppOmMsg,
    NAS_FILE_ID_DEFINE_ENUM_UINT32      enNasFileName,
    VOS_UINT32                          ulLine,
    NAS_LPP_ERROR_CODE_ENUM_UINT32      enErrorCode,
    VOS_UINT8                           ucParaNum,
    VOS_UINT32                          ulPara1,
    VOS_UINT32                          ulPara2,
    VOS_UINT32                          ulPara3
);

/*****************************************************************************
  9 OTHERS
*****************************************************************************/










#if (VOS_OS_VER != VOS_WIN32)
 #pragma pack()
#else
 #pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasLppOm.h */
