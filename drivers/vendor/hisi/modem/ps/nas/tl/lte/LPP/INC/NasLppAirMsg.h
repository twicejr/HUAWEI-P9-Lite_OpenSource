/*******************************************************************************
 * File name:    NasLppAirMsg.h
 * Description:  Lpp模块外部接口消息详细数据结构
                 根据LPP协议(3GPP TS 36.355 V10.5.0 (2012-12))制定
 * Histoty:
                    1. sunbing 49683  2012-12-6 create
*******************************************************************************/
/*******************************************************************************
 * 说明:
 *           1. choice 类型使用1字节(或2字节)来判断，并用宏表示其意义，
 *              所用宏名的后缀为_CHOSEN
 *           2. sequence 类型使用位域来记录可选项的存在与否
 *           3. 若可选项为数组，则用数组长度标识该数组可选与否，不再使用位域方法标识
 *              长度为0表示该项不选，长度不为0表示选中
 *           4. 所有的类型名和宏名采用大写字母来表示，相邻两个单词之间用下划线连接
 *           5. 所有的变量名只采用大小写字母，变量名前缀为小写字母的类型标识符，
 *              每个单词首字母大写，其余字母小写
 *           6. 变量名前缀表示类型如下:
 *                  a      -    array
 *                  g      -    global
 *                  c      -    ASN1_INT8
 *                  s      -    ASN1_INT16
 *                  l      -    ASN1_INT32
 *                  uc     -    ASN1_UINT8
 *                  us     -    ASN1_UINT16
 *                  ul     -    ASN1_UINT32
 *                  ull    -    ASN1_UINT64
 *                  en     -    enum
 *                  un     -    union
 *                  b      -    bool
 *
 *
*******************************************************************************/

#ifndef _NASLPPAIRMSG_H_
#define _NASLPPAIRMSG_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*******************************************************************************
 *                          需要包含的头文件.
*******************************************************************************/
#include "vos.h"
#include "LppMtaInterface.h"
#include "NasLppAirMsg.h"

/*根据不同产品分别包含不同的宏定义的文件 */
//#include "eNodeB_UuUserMacro.h"
/*******************************************************************************
 *                      字节对齐方式: 一字节对齐.
*******************************************************************************/
//#pragma pack(1)
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(1)
#else
 #pragma pack(push, 1)
#endif


/*****************************************************************************
  2 Macro
*****************************************************************************/
/*#define LPP_MAX_GNSS_GENERIC_ASSIST_DATA_ELEMENT_LEN    (16)原始长度是16*/
#define LPP_MAX_GNSS_GENERIC_ASSIST_DATA_ELEMENT_LEN    LPP_MAX_VALID_GNSS_POSITION_TECH

/*#define LPP_MAX_GNSS_DATA_BITS_SAT_ELEMENT_LEN          (64)*/
#define LPP_MAX_GNSS_DATA_BITS_SAT_ELEMENT_LEN          LPP_MAX_GNSS_SAT_CNT

#define LPP_MAX_NAV_MODEL_SAT_ELEMENT_LEN               (35)/* MTA GNSS MSG STRUCT CUT OFF */
#define LPP_MAX_BAD_SIGNAL_ELEMENT_LEN                  (35)/* MTA GNSS MSG STRUCT CUT OFF */
#define LPP_MAX_GNSS_ACQUSITON_ASSIST_ELMENT_LEN        (35)/* MTA GNSS MSG STRUCT CUT OFF */
#define LPP_MAX_GNSS_ALMANAC_ELMENT_LEN                 (35)/* MTA GNSS MSG STRUCT CUT OFF */
#define LPP_MAX_GNSS_ID_GLONASS_SAT_ELEMENT_LEN         (35)/* MTA GNSS MSG STRUCT CUT OFF */
#define LPP_MAX_GNSS_ID_GPS_SAT_ELEMENT_LEN             (35)/* MTA GNSS MSG STRUCT CUT OFF */
#define LPP_MAX_GNSS_MEAS_FOR_ONE_GNSS_LEN              (6)/* MTA GNSS MSG STRUCT CUT OFF */
#define LPP_MAX_GNSS_SAT_MEAS_ELMENT_LEN                (35)/* MTA GNSS MSG STRUCT CUT OFF */
#define LPP_MAX_GEN_ASSIT_DATA_ELEMENT_LEN              (6)/* MTA GNSS MSG STRUCT CUT OFF */
#define LPP_MAX_SAT_LIST_RELATED_DATA_ELEMENT_LEN       (35)/* MTA GNSS MSG STRUCT CUT OFF */
#define LPP_MAX_GNSS_DATA_BITS_REQ_SAT_LIST_LEN         (35)/* MTA GNSS MSG STRUCT CUT OFF */
#define LPP_MAX_GNSS_GENERIC_ASSIST_DATA_SUPPORT_ELMENT_LEN (6)/* MTA GNSS MSG STRUCT CUT OFF */
#define LPP_ELLIPSOID_POINT_LEN                         (6)
#define LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE_LEN (7)
#define LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE_LEN (10)
#define LPP_ELLIPSOID_POINT_WITH_ALTITUD_LEN            (8)
#define LPP_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID_LEN  (13)
#define LPP_ELLIPSOID_ARC_LEND                          (12)
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*以下接口是复用了GNSS相关跟AT相关的接口*/
typedef LPP_MTA_COMMON_PLMN_IDENTITY_STRU   LPP_PLMN_IDENTITY_STRU;
typedef LPP_MTA_COMMON_GNSS_SIGNAL_IDS_STRU LPP_GNSS_SIGNAL_IDS_STRU;
typedef LPP_MTA_COMMON_CELL_IDENTITY_STRU   LPP_CELL_IDENTITY_STRU;
typedef LPP_MTA_COMMON_CELL_GLO_EUTRA_UTRA_STRU LPP_CELL_GLO_EUTRA_UTRA_STRU;
typedef LPP_MTA_COMMON_FDD_STRU LPP_FDD_STRU;
typedef LPP_MTA_COMMON_TDD_STRU LPP_TDD_STRU;
typedef LPP_MTA_COMMON_MODE_SELECT_STRU LPP_MODE_SELECT_STRU;
typedef LPP_MTA_COMMON_CELL_GLO_ID_GERAN_STRU LPP_CELL_GLO_ID_GERAN_STRU;
typedef  LPP_MTA_COMMON_SV_ID_STRU  LPP_SV_ID_STRU;
typedef LPP_MTA_COMMON_GNSS_SIGNAL_ID_STRU LPP_GNSS_SIGNAL_ID_STRU;
typedef LPP_MTA_COMMON_GNSS_ID_BITMAP_STRU LPP_GNSS_ID_BITMAP_STRU;
typedef MTA_LPP_GNSS_LOCATION_SERVER_ERROR_CAUSE_STRU LPP_GNSS_LOCATION_SERVER_ERROR_CAUSE_STRU;
typedef MTA_LPP_GNSS_TARGET_DEVICE_ERROR_CAUSE_STRU LPP_GNSS_TARGET_DEVICE_ERROR_CAUSE_STRU;
typedef LPP_MTA_COMMON_GNSS_ERROR_STRU LPP_GNSS_ERROR_STRU;
typedef LPP_MTA_COMMON_ECGI_STRU LPP_ECGI_STRU;
typedef LOC_COM_ELLIPSOID_POINT_STRU LPP_ELLIPSOID_POINT_STRU;
typedef LOC_COM_ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE_STRU LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE_STRU;
typedef LOC_COM_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE_STRU LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE_STRU;
typedef LOC_COM_POLYGON_POINTS_STRU LPP_POLYGON_POINTS_STRU;
typedef LOC_COM_POLYGON_STRU LPP_POLYGON_STRU;
typedef LOC_COM_ELLIPSOID_POINT_WITH_ALTITUDE_STRU LPP_ELLIPSOID_POINT_WITH_ALTITUDE_STRU;
typedef LOC_COM_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID_STRU LPP_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID_STRU;
typedef LOC_COM_ELLIPSOIDARC_STRU LPP_ELLIPSOIDARC_STRU;
typedef LOC_COM_COORDINATE_STRU LPP_LOCATION_COORDINATE_STRU;
typedef LOC_COM_HORIZONTAL_WITH_VERTICAL_VELOCITY_STRU LPP_HORIZONTAL_WITH_VERTICAL_VELOCITY_STRU;
typedef LOC_COM_HORIZONTAL_VELCCITY_WITH_UNCERTAINTY_STRU LPP_HORIZONTAL_VELCCITY_WITH_UNCERTAINTY_STRU;
typedef LOC_COM_HORIZONTAL_WITH_VERTICAL_VELOCITY_AND_UNCERTAINTY_STRU LPP_HORIZONTAL_WITH_VERTICAL_VELOCITY_AND_UNCERTAINTY_STRU;
typedef LOC_COM_VELOCITY_STRU LPP_VELOCITY_STRU;
typedef LOC_COM_HORIZONTAL_VELCOCTIY_STRU LPP_HORIZONTAL_VELCOCTIY_STRU;
typedef MTA_LPP_LOCATION_ERROR_STRU LPP_LOCATION_ERROR_STRU;
typedef MTA_LPP_COMMON_IES_PROVIDE_LOCATION_INFO_STRU LPP_COMMON_IES_PROVIDE_LOCATION_INFO_STRU;
typedef LPP_MTA_COMMON_GNSS_ID_STRU LPP_GNSS_ID_STRU;
typedef MTA_LPP_MEAS_REF_TIME_EUTRA  LPP_MEAS_REF_TIME_EUTRA;
typedef MTA_LPP_MEAS_REF_TIME_UTRA LPP_MEAS_REF_TIME_UTRA;
typedef MTA_LPP_REF_FRAME_STRU LPP_REF_FRAME_STRU;
typedef MTA_LPP_MEAS_REF_TIME_GSM LPP_MEAS_REF_TIME_GSM;
typedef MTA_LPP_NET_WORK_TIME_MEAS_REF_STRU LPP_NET_WORK_TIME_MEAS_REF_STRU;
typedef MTA_LPP_MEAS_REF_TIME_STRU LPP_MEAS_REF_TIME_STRU;
typedef MTA_LPP_GNSS_SAT_MEAS_ELEMENT_STRU LPP_GNSS_SAT_MEAS_ELEMENT_STRU;
typedef MTA_LPP_GNSS_SGN_MEAS_ELEMENT_STRU LPP_GNSS_SGN_MEAS_ELEMENT_STRU;
typedef MTA_LPP_GNSS_SGN_LIST_STRU LPP_GNSS_SGN_LIST_STRU;
typedef MTA_LPP_GNSS_MEAS_FOR_ONE_GNSS_STRU LPP_GNSS_MEAS_FOR_ONE_GNSS_STRU;
typedef MTA_LPP_GNSS_LOCATION_INFO_STRU LPP_GNSS_LOCATION_INFO_STRU;
typedef LPP_MTA_ARFCN_VALUE_EUTRA_STRU LPP_ARFCN_VALUE_EUTRA_STRU;
typedef LPP_MTA_ARFCN_VALUE_EUTRA_V9A0_STRU LPP_ARFCN_VALUE_EUTRA_V9A0_STRU;
typedef LPP_MTA_EUTRA_STRU LPP_EUTRA_STRU;
typedef LPP_MTA_ARFCN_VALUE_UTRA_STRU LPP_ARFCN_VALUE_UTRA_STRU;
typedef LPP_MTA_UTRA_STRU LPP_UTRA_STRU;
typedef LPP_MTA_GSM_STRU LPP_GSM_STRU;
typedef LPP_MTA_CELL_ID_STRU LPP_CELL_ID_STRU;
typedef LPP_MTA_NET_WORK_TIME_STRU LPP_NET_WORK_TIME_STRU;
typedef LPP_MTA_COMMON_TRIGGER_REPORT_CRITERIA_STRU LPP_TRIGGER_REPORT_CRITERIA_STRU;
typedef LPP_MTA_COMMON_PERIODICAL_REPORT_STRU LPP_PERIODICAL_REPORT_STRU;
typedef LPP_MTA_COMMON_HORIZONTAL_ACCURACY_STRU LPP_HORIZONTAL_ACCURACY_STRU;
typedef LPP_MTA_COMMON_VERTICAL_ACCURACY_STRU LPP_VERTICAL_ACCURACY_STRU;
typedef LPP_MTA_COMMON_RESPONSE_TIME_STRU LPP_RESPONSE_TIME_STRU;
typedef LPP_MTA_COMMON_QOS_STRU LPP_QOS_STRU;
typedef LPP_MTA_COMMON_LOCATION_COORDINATE_TYPE_STRU LPP_LOCATION_COORDINATE_TYPE_STRU;
typedef LPP_MTA_COMMON_VELOCITY_TYPE_STRU LPP_VELOCITY_TYPE_STRU;
typedef LPP_MTA_COMMON_IES_REQ_LOCATION_INFO_STRU LPP_COMMON_IES_REQ_LOCATION_INFO_STRU;
typedef LPP_MTA_GNSS_POSITION_INSTRUCTION_STRU LPP_GNSS_POSITION_INSTRUCTION_STRU;
typedef LPP_MTA_AGNSS_REQ_LOCATION_INFO_STRU LPP_AGNSS_REQ_LOCATION_INFO_STRU;
typedef LPP_MTA_GNSS_TIME_MODEL_ELEMENT_STRU LPP_GNSS_TIME_MODEL_ELEMENT_STRU;
typedef LPP_MTA_GNSS_TIME_MODEL_LIST_STRU LPP_GNSS_TIME_MODEL_LIST_STRU;
typedef LPP_MTA_DGNSS_CORRECT_ELEMENT_STRU LPP_DGNSS_CORRECT_ELEMENT_STRU;
typedef LPP_MTA_DGNSS_SGN_TYPE_ELEMENT_STRU LPP_DGNSS_SGN_TYPE_ELEMENT_STRU;
typedef LPP_MTA_DGNSS_SGN_TYPE_LIST_STRU LPP_DGNSS_SGN_TYPE_LIST_STRU;
typedef LPP_MTA_GNSS_DIFF_CORRECT_STRU LPP_GNSS_DIFF_CORRECT_STRU;
typedef LPP_MTA_STANDARD_CLOCK_MODEL_LIST_ELEMENT_STRU LPP_STANDARD_CLOCK_MODEL_LIST_ELEMENT_STRU;
typedef LPP_MTA_STANDARD_CLOCK_MODEL_LIST_STRU LPP_STANDARD_CLOCK_MODEL_LIST_STRU;
typedef LPP_MTA_NAV_CLOCK_MODEL_STRU LPP_NAV_CLOCK_MODEL_STRU;
typedef LPP_MTA_CNAV_CLOCK_MODEL_STRU LPP_CNAV_CLOCK_MODEL_STRU;
typedef LPP_MTA_GLONASS_CLOCK_MODEL_STRU LPP_GLONASS_CLOCK_MODEL_STRU;
typedef LPP_MTA_SBAS_CLOCK_MODEL_STRU LPP_SBAS_CLOCK_MODEL_STRU;
typedef LPP_MTA_GNSS_CLOCK_MODEL_STRU LPP_GNSS_CLOCK_MODEL_STRU;
typedef LPP_MTA_NAV_MODEL_KEPLERIAN_SET_STRU LPP_NAV_MODEL_KEPLERIAN_SET_STRU;
typedef LPP_MTA_EPHEM_SF1_RSVD_STRU LPP_EPHEM_SF1_RSVD_STRU;
typedef LPP_MTA_ADD_NAV_PARAM_STRU LPP_ADD_NAV_PARAM_STRU;
typedef LPP_MTA_NAV_MODEL_CNAV_KEPLERIAN_SET_STRU LPP_NAV_MODEL_CNAV_KEPLERIAN_SET_STRU;
typedef LPP_MTA_NAV_MODEL_NAV_KEPLERIAN_SET_STRU LPP_NAV_MODEL_NAV_KEPLERIAN_SET_STRU;
typedef LPP_MTA_NAV_MODEL_GLONASS_ECEF_STRU LPP_NAV_MODEL_GLONASS_ECEF_STRU;
typedef LPP_MTA_NAV_MODEL_SBAS_STRU LPP_NAV_MODEL_SBAS_STRU;
typedef LPP_MTA_GNSS_ORBIT_MODEL_STRU LPP_GNSS_ORBIT_MODEL_STRU;
typedef LPP_MTA_GNSS_NAV_MODEL_SATELLITE_LIST_ELEMENT_STRU LPP_GNSS_NAV_MODEL_SATELLITE_LIST_ELEMENT_STRU;
typedef LPP_MTA_GNSS_NAVIGATION_MODEL_STRU LPP_GNSS_NAVIGATION_MODEL_STRU;
typedef LPP_MTA_GNSS_BAD_SIGNAL_ELEMENT_STRU LPP_GNSS_BAD_SIGNAL_ELEMENT_STRU;
typedef LPP_MTA_GNSS_REALTIME_INTERGRITY_STRU LPP_GNSS_REALTIME_INTERGRITY_STRU;
typedef LPP_MTA_GNSS_DATA_BITS_SGN_ELEMENT_STRU LPP_GNSS_DATA_BITS_SGN_ELEMENT_STRU;
typedef LPP_MTA_GNSS_DATA_BITS_SGN_LIST_STRU LPP_GNSS_DATA_BITS_SGN_LIST_STRU;
typedef LPP_MTA_GNSS_DATA_BITS_SAT_ELEMENT_STRU LPP_GNSS_DATA_BITS_SAT_ELEMENT_STRU;
typedef LPP_MTA_GNSS_ACQUISIT_ASSIST_ELEMENT_STRU LPP_GNSS_ACQUISIT_ASSIST_ELEMENT_STRU;
typedef LPP_MTA_GNSS_ACQUISIT_ASSIST_STRU LPP_GNSS_ACQUISIT_ASSIST_STRU;
typedef LPP_MTA_ALMANAC_KEPLERIAN_SET_STRU LPP_ALMANAC_KEPLERIAN_SET_STRU;
typedef LPP_MTA_ALMANAC_NAV_KEPLERIAN_SET_STRU LPP_ALMANAC_NAV_KEPLERIAN_SET_STRU;
typedef LPP_MTA_ALMANAC_REDUCED_KEPLERIAN_SET_STRU LPP_ALMANAC_REDUCED_KEPLERIAN_SET_STRU;
typedef LPP_MTA_ALMANAC_MIDI_ALMANAC_STRU LPP_ALMANAC_MIDI_ALMANAC_STRU;
typedef LPP_MTA_ALMANAC_GLONASS_ALMANAC_SET_STRU LPP_ALMANAC_GLONASS_ALMANAC_SET_STRU;
typedef LPP_MTA_ALMANAC_ECEF_SBAS_ALMANAC_STRU LPP_ALMANAC_ECEF_SBAS_ALMANAC_STRU;
typedef LPP_MTA_GNSS_ALMANAC_ELEMENT_STRU LPP_GNSS_ALMANAC_ELEMENT_STRU;
typedef LPP_MTA_GNSS_ALMANAC_STRU LPP_GNSS_ALMANAC_STRU;
typedef LPP_MTA_UTC_MODEL_SET1_STRU LPP_UTC_MODEL_SET1_STRU;
typedef LPP_MTA_UTC_MODEL_SET2_STRU LPP_UTC_MODEL_SET2_STRU;
typedef LPP_MTA_UTC_MODEL_SET3_STRU LPP_UTC_MODEL_SET3_STRU;
typedef LPP_MTA_UTC_MODEL_SET4_STRU LPP_UTC_MODEL_SET4_STRU;
typedef LPP_MTA_GNSS_UTC_MODEL_STRU LPP_GNSS_UTC_MODEL_STRU;
typedef LPP_MTA_GNSS_ID_GLONASS_SAT_ELEMENT_STRU LPP_GNSS_ID_GLONASS_SAT_ELEMENT_STRU;
typedef LPP_MTA_GNSS_ID_GPS_SAT_ELEMENT_STRU LPP_GNSS_ID_GPS_SAT_ELEMENT_STRU;
typedef LPP_MTA_GNSS_AUX_INFO_STRU LPP_GNSS_AUX_INFO_STRU;
typedef LPP_MTA_COMMON_SBAS_IDS_STRU LPP_SBAS_IDS_STRU;
typedef LPP_MTA_COMMON_SBAS_ID_STRU LPP_SBAS_ID_STRU;
typedef LPP_MTA_GPS_TOW_ASSIST_ELEMENT_STRU LPP_GPS_TOW_ASSIST_ELEMENT_STRU;
typedef LPP_MTA_GPS_TOW_ASSIST_STRU LPP_GPS_TOW_ASSIST_STRU;
typedef LPP_MTA_GNSS_SYSTEM_TIME_STRU LPP_GNSS_SYSTEM_TIME_STRU;
typedef LPP_MTA_GNSS_REFERENCE_TIME_FOR_CELL_STRU LPP_GNSS_REFERENCE_TIME_FOR_CELL_STRU;
typedef LPP_MTA_GNSS_REFERENCE_TIME_STRU LPP_GNSS_REFERENCE_TIME_STRU;
typedef LPP_MTA_ELLIP_POINT_WITH_ALTITUDE_UNCERTAIN_ELLIPSOID_STRU LPP_ELLIP_POINT_WITH_ALTITUDE_UNCERTAIN_ELLIPSOID_STRU;
typedef LPP_MTA_GNSS_REFERENCE_LOCATION_STRU LPP_GNSS_REFERENCE_LOCATION_STRU;
typedef LPP_MTA_KLOBUCHAR_MODEL_PARAMTER_STRU LPP_KLOBUCHAR_MODEL_PARAMTER_STRU;
typedef LPP_MTA_NEQUICK_MODEL_PARAMETER_STRU LPP_NEQUICK_MODEL_PARAMETER_STRU;
typedef LPP_MTA_GNSS_IONOSPHERIC_MODEL_STRU LPP_GNSS_IONOSPHERIC_MODEL_STRU;
typedef LPP_MTA_GNSS_EARTH_ORIENTATION_PARAMETERS_STRU LPP_GNSS_EARTH_ORIENTATION_PARAMETERS_STRU;
typedef LPP_MTA_GNSS_COMMON_ASSIST_DATA_STRU LPP_GNSS_COMMON_ASSIST_DATA_STRU;
typedef MTA_LPP_GNSS_TIME_MODEL_ELEMENT_REQ_STRU LPP_GNSS_TIME_MODEL_ELEMENT_REQ_STRU;
typedef MTA_LPP_GNSS_TIME_MODEL_LIST_REQ_STRU LPP_GNSS_TIME_MODEL_LIST_REQ_STRU;
typedef MTA_LPP_GNSS_DIFF_CORRECT_REQ_STRU LPP_GNSS_DIFF_CORRECT_REQ_STRU;
typedef MTA_LPP_SATLIST_RELATED_DATALIST_ELEMENT_STRU LPP_SATLIST_RELATED_DATALIST_ELEMENT_STRU;
typedef MTA_LPP_STORED_NAVLIST_STRU LPP_STORED_NAVLIST_STRU;
typedef LPP_MTA_COMMON_CLOCK_MODEL_ID_STRU LPP_CLOCK_MODEL_ID_STRU;
typedef LPP_MTA_COMMON_ORBIT_MODEL_ID_STRU LPP_ORBIT_MODEL_ID_STRU;
typedef MTA_LPP_REQ_NAVLIST_STRU LPP_REQ_NAVLIST_STRU;
typedef MTA_LPP_GNSS_NAVIGATION_MODEL_REQ_STRU LPP_GNSS_NAVIGATION_MODEL_REQ_STRU;
typedef MTA_LPP_GNSS_REALTIME_INTERGRITY_REQ_STRU LPP_GNSS_REALTIME_INTERGRITY_REQ_STRU;
typedef MTA_LPP_GNSS_DATA_BIT_REQ_SAT_ELEMENT_STRU LPP_GNSS_DATA_BIT_REQ_SAT_ELEMENT_STRU;
typedef MTA_LPP_GNSS_DATA_BIT_ASSIST_REQ_STRU LPP_GNSS_DATA_BIT_ASSIST_REQ_STRU;
typedef MTA_LPP_GNSS_ACQUISIT_ASSIST_REQ_STRU LPP_GNSS_ACQUISIT_ASSIST_REQ_STRU;
typedef MTA_LPP_GNSS_ALMANAC_REQ_STRU LPP_GNSS_ALMANAC_REQ_STRU;
typedef MTA_LPP_GNSS_UTC_MODEL_REQ_STRU LPP_GNSS_UTC_MODEL_REQ_STRU;
typedef MTA_LPP_GNSS_AUX_INFO_REQ_STRU LPP_GNSS_AUX_INFO_REQ_STRU;
typedef MTA_LPP_GNSS_GENERIC_ASSIST_DATA_REQ_ELEMENT_STRU LPP_GNSS_GENERIC_ASSIST_DATA_REQ_ELEMENT_STRU;
typedef MTA_LPP_GNSS_REFERENCE_TIME_REQ_STRU LPP_GNSS_REFERENCE_TIME_REQ_STRU;
typedef MTA_LPP_GNSS_REFERENCE_LOCATION_REQ_STRU LPP_GNSS_REFERENCE_LOCATION_REQ_STRU;
typedef MTA_LPP_GNSS_IONOSPHERIC_MODEL_REQ_STRU LPP_GNSS_IONOSPHERIC_MODEL_REQ_STRU;
typedef MTA_LPP_GNSS_EARTH_ORIENTATION_PARAMETERS_REQ_STRU LPP_GNSS_EARTH_ORIENTATION_PARAMETERS_REQ_STRU;
typedef MTA_LPP_GNSS_COMMON_ASSIST_DATA_REQ_STRU LPP_GNSS_COMMON_ASSIST_DATA_REQ_STRU;
typedef LPP_MTA_COMMON_ACCESS_TYPES_STRU LPP_ACCESS_TYPES_STRU;
typedef LPP_MTA_COMMON_POSITIONING_MODES_STRU LPP_POSITIONING_MODES_STRU;
typedef MTA_LPP_FTA_MEAS_SUPPORT_STRU LPP_FTA_MEAS_SUPPORT_STRU;
typedef MTA_LPP_GNSS_SUPPORT_ELEMENT_STRU LPP_GNSS_SUPPORT_ELEMENT_STRU;
typedef MTA_LPP_GNSS_REFERENCE_TIME_SUPPORT_STRU LPP_GNSS_REFERENCE_TIME_SUPPORT_STRU;
typedef MTA_LPP_GNSS_REFERENCE_LOCATION_SUPPORT_STRU LPP_GNSS_REFERENCE_LOCATION_SUPPORT_STRU;
typedef MTA_LPP_GNSS_IONOSPHERIC_MODE_SUPPORT_STRU LPP_GNSS_IONOSPHERIC_MODE_SUPPORT_STRU;
typedef MTA_LPP_GNSS_EARTH_ORIENTATION_PARAMETERS_SUPPORT_STRU LPP_GNSS_EARTH_ORIENTATION_PARAMETERS_SUPPORT_STRU;
typedef MTA_LPP_GNSS_COMMON_ASSISTANCE_DATA_SUPPORT_STRU LPP_GNSS_COMMON_ASSISTANCE_DATA_SUPPORT_STRU;
typedef MTA_LPP_GNSS_TIME_MODE_LIST_SUPPORT_STRU LPP_GNSS_TIME_MODE_LIST_SUPPORT_STRU;
typedef MTA_LPP_GNSS_DIFFERENTIAL_CORRECTIONS_SUPPORT_STRU LPP_GNSS_DIFFERENTIAL_CORRECTIONS_SUPPORT_STRU;
typedef MTA_LPP_CLOCK_MODEL_STRU LPP_CLOCK_MODEL_STRU;
typedef MTA_LPP_ORBIT_MODEL_STRU LPP_ORBIT_MODEL_STRU;
typedef MTA_LPP_GNSS_NAVIGATION_MODE_SUPPORT_STRU LPP_GNSS_NAVIGATION_MODE_SUPPORT_STRU;
typedef MTA_LPP_GNSS_REAL_TIME_INTEGRITY_SUPPORT_STRU LPP_GNSS_REAL_TIME_INTEGRITY_SUPPORT_STRU;
typedef MTA_LPP_GNSS_DATA_BIT_ASSISTANCE_SUPPORT_STRU LPP_GNSS_DATA_BIT_ASSISTANCE_SUPPORT_STRU;
typedef MTA_LPP_GNSS_ACQUISITION_ASSISTANCE_SUPPORT_STRU  LPP_GNSS_ACQUISITION_ASSISTANCE_SUPPORT_STRU;
typedef MTA_LPP_ALMANAC_MODEL_STRU LPP_ALMANAC_MODEL_STRU;
typedef MTA_LPP_GNSS_ALMANAC_SUPPORT_STRU LPP_GNSS_ALMANAC_SUPPORT_STRU;
typedef MTA_LPP_UTC_MODEL_STRU LPP_UTC_MODEL_STRU;
typedef MTA_LPP_GNSS_UTC_MODEL_SUPPORT_STRU LPP_GNSS_UTC_MODEL_SUPPORT_STRU;
typedef MTA_LPP_GNSS_AUXILIARY_INFORMATION_SUPPORT_STRU LPP_GNSS_AUXILIARY_INFORMATION_SUPPORT_STRU;
typedef MTA_LPP_GNSS_GENERIC_ASSISTANCE_DATA_SUPPORT_ELEMENT_STRU LPP_GNSS_GENERIC_ASSISTANCE_DATA_SUPPORT_ELEMENT_STRU;
typedef MTA_LPP_ASSISTANCE_DATA_SUPPORT_LIST_STRU LPP_ASSISTANCE_DATA_SUPPORT_LIST_STRU;
typedef MTA_LPP_VELOCITY_TYPES_STRU LPP_VELOCITY_TYPES_STRU;
typedef MTA_LPP_AGNSS_PROVIDE_CAP_STRU LPP_AGNSS_PROVIDE_CAP_STRU;
typedef LPP_MTA_GNSS_CAP_REQ_STRU LPP_AGNSS_REQ_CAP_STRU;
/*********UP interface**********/
typedef LPP_MTA_OTDOA_PROVIDE_CAP_STRU LPP_OTDOA_PROVIDE_CAP_STRU;
typedef LPP_MTA_OTDOA_MODE_STRU LPP_OTDOA_MODE_STRU;
typedef LPP_MTA_SUPPORTED_BAND_LIST_EUTRA_STRU LPP_SUPPORTED_BAND_LIST_EUTRA_STRU;
typedef LPP_MTA_SUPPORTED_BAND_EUTRA_STRU   LPP_SUPPORTED_BAND_EUTRA_STRU;
typedef LPP_MTA_SUPPORTED_BAND_LIST_EUTRA_V9A0_STRU LPP_SUPPORTED_BAND_LIST_EUTRA_V9A0_STRU;
typedef LPP_MTA_SUPPORTED_BAND_EUTRA_V9A0_STRU LPP_SUPPORTED_BAND_EUTRA_V9A0_STRU;
typedef LPP_MTA_ECID_MEAS_SUPPORTED_STRU LPP_ECID_MEAS_SUPPORTED_STRU;
typedef LPP_MTA_ECID_PROVIDE_CAP_STRU LPP_ECID_PROVIDE_CAP_STRU;
typedef LPP_MTA_OTDOA_REQ_ASSIST_DATA_STRU LPP_OTDOA_REQ_ASSIST_DATA_STRU;
typedef MTA_LPP_OTDOA_PROVIDE_ASSIST_DATA_STRU LPP_OTDOA_PROVIDE_ASSIST_DATA_STRU;
typedef MTA_LPP_OTDOA_REF_CELL_INFO_STRU  LPP_OTDOA_REF_CELL_INFO_STRU;
typedef MTA_LPP_OTDOA_NEIGHOUR_CELL_INFO_STRU  LPP_OTDOA_NEIGHOUR_CELL_INFO_STRU;
typedef MTA_LPP_OTDOA_ERROR_STRU LPP_OTDOA_ERROR_STRU;
typedef MTA_LPP_PRS_INFO_STRU LPP_PRS_INFO_STRU;
typedef MTA_LPP_PRS_MUTING_INFO_R9_STRU LPP_PRS_MUTING_INFO_R9_STRU;
typedef MTA_LPP_OTDOA_NEIGHBOUR_FREQ_INFO_STRU  LPP_OTDOA_NEIGHBOUR_FREQ_INFO_STRU;
typedef MTA_LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU  LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU;
typedef MTA_LPP_OTDOA_LOCATION_SERVER_ERROR_CAUSE_STRU  LPP_OTDOA_LOCATION_SERVER_ERROR_CAUSE_STRU;
typedef MTA_LPP_OTDOA_TARGET_DEVICE_ERROR_CAUSE_STRU    LPP_OTDOA_TARGET_DEVICE_ERROR_CAUSE_STRU;
typedef MTA_LPP_OTDOA_REQ_LOCATION_INFO_STRU LPP_OTDOA_REQ_LOCATION_INFO_STRU;
typedef MTA_LPP_ECID_REQ_LOCATION_INFO_STRU LPP_ECID_REQ_LOCATION_INFO_STRU;
typedef MTA_LPP_REQ_MEASUREMENT_STRU LPP_REQ_MEASUREMENT_STRU;
typedef LPP_MTA_ECID_PROVIDE_LOCATION_INFO_STRU  LPP_ECID_PROVIDE_LOCATION_INFO_STRU;
typedef LPP_MTA_ECID_SIGNAL_MEAS_INFO_STRU LPP_ECID_SIGNAL_MEAS_INFO_STRU;
typedef LPP_MTA_ECID_ERROR_STRU LPP_ECID_ERROR_STRU;
typedef LPP_MTA_MEAS_RESULT_ELEMENT_STRU LPP_MEAS_RESULT_ELEMENT_STRU;
typedef LPP_MTA_MEAS_RESULT_LIST_STRU LPP_MEAS_RESULT_LIST_STRU;
typedef LPP_MTA_ECID_LOCATION_SERVER_ERROR_CAUSE_STRU LPP_ECID_LOCATION_SERVER_ERROR_CAUSE_STRU;
typedef LPP_MTA_ECID_TARGET_DEVICE_ERROR_CAUSE_STRU LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_STRU;
typedef LPP_MTA_OTDOA_PROVIDE_LOCATION_INFO_STRU LPP_OTDOA_PROVIDE_LOCATION_INFO_STRU;
typedef LPP_MTA_OTDOA_SIGNAL_MEAS_INFO_STRU LPP_OTDOA_SIGNAL_MEAS_INFO_STRU;
typedef LPP_MTA_OTDOA_MEAS_QUALITY_STRU LPP_OTDOA_MEAS_QUALITY_STRU;
typedef LPP_MTA_NEIGHBOUR_MEAS_LIST_STRU LPP_NEIGHBOUR_MEAS_LIST_STRU;
typedef LPP_MTA_NEIGHBOUR_MEAS_ELEMENT_STRU LPP_NEIGHBOUR_MEAS_ELEMENT_STRU;



/*******************************************************************************
 结构名    : LPP_GNSS_GENERIC_ASSISTANCE_DATA_SUPPORT_STRU
 结构说明  : GPS模块提供能力之GenericAssistanceDataSupport
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                                  ulSupportElementNum;
    LPP_GNSS_GENERIC_ASSISTANCE_DATA_SUPPORT_ELEMENT_STRU       astSupportElementArray[LPP_MAX_GNSS_GENERIC_ASSIST_DATA_SUPPORT_ELMENT_LEN];
}LPP_GNSS_GENERIC_ASSISTANCE_DATA_SUPPORT_STRU;

/*******************************************************************************
 结构名    : LPP_GNSS_SUPPORT_LIST_STRU
 结构说明  : GPS模块提供能力之SupportList
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    GNSS-SupportList ::= SEQUENCE (SIZE(1..16)) OF GNSS-SupportElement
    */
    VOS_UINT32                                  ulSupportElementNum;                /* 取值[1,16] */
    MTA_LPP_GNSS_SUPPORT_ELEMENT_STRU           astGnssSupportElementArray[LPP_MAX_GNSS_SUPPORT_ELEMENT_NUM];
}LPP_GNSS_SUPPORT_LIST_STRU;

/*******************************************************************************
 结构名    : LPP_GNSS_DATA_BIT_REQ_SAT_LIST_STRU
 结构说明  : GPS模块提供能力之DataBitsReqSatList
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
/*
GNSS-DataBitsReqSatList ::= SEQUENCE (SIZE(1..64)) OF GNSS-DataBitsReqSatElement
*/
    VOS_UINT32                                  ulGNSSDataBitsReqListCnt;
    LPP_GNSS_DATA_BIT_REQ_SAT_ELEMENT_STRU      astGNSSDataBitReqSatList[LPP_MAX_GNSS_DATA_BITS_REQ_SAT_LIST_LEN];
}LPP_GNSS_DATA_BIT_REQ_SAT_LIST_STRU;

/*******************************************************************************
 结构名    : LPP_SATLIST_RELATED_DATALIST_STRU
 结构说明  : GPS模块提供能力之SatListRelatedDataList
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*SatListRelatedDataList ::= SEQUENCE (SIZE (1..64)) OF SatListRelatedDataElement*/
    VOS_UINT32                                      ulSatListRelatedDataListCnt;
    LPP_SATLIST_RELATED_DATALIST_ELEMENT_STRU       astSatListRelatedDataListElementArray[LPP_MAX_SAT_LIST_RELATED_DATA_ELEMENT_LEN];
}LPP_SATLIST_RELATED_DATALIST_STRU;

/*******************************************************************************
 结构名    : LPP_GNSS_GENERIC_ASSIST_DATA_REQ_STRU
 结构说明  : GPS模块提供能力之GenericAssistDataReq
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    GNSS-GenericAssistDataReq ::= SEQUENCE (SIZE (1..16)) OF GNSS-GenericAssistDataReqElement
    */
    VOS_UINT32                                              ulGNSSGenericAssistDataReqCnt;
    LPP_GNSS_GENERIC_ASSIST_DATA_REQ_ELEMENT_STRU           astGNSSGenericAssistDataReqElement[LPP_MAX_GEN_ASSIT_DATA_ELEMENT_LEN];
}LPP_GNSS_GENERIC_ASSIST_DATA_REQ_STRU;

/*******************************************************************************
 结构名    : LPP_GNSS_SAT_MEAS_LIST_STRU
 结构说明  : GPS提供位置信息SatMeasList
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    GNSS-SatMeasList ::= SEQUENCE (SIZE(1..64)) OF GNSS-SatMeasElement
    */
    VOS_UINT32                              ulGNSSSatMeasListCnt;
    LPP_GNSS_SAT_MEAS_ELEMENT_STRU          astGNSSSatMeasListArray[LPP_MAX_GNSS_SAT_MEAS_ELMENT_LEN];
}LPP_GNSS_SAT_MEAS_LIST_STRU;

/*******************************************************************************
 结构名    : LPP_GNSS_MEAS_LIST_STRU
 结构说明  : GPS提供位置信息measurementList
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    GNSS-MeasurementList  ::= SEQUENCE (SIZE(1..16)) OF GNSS-MeasurementForOneGNSS
    */
    VOS_UINT32                              ulGNSSMeasListCnt;
    LPP_GNSS_MEAS_FOR_ONE_GNSS_STRU         astGNSSMeasListArray[LPP_MAX_GNSS_MEAS_FOR_ONE_GNSS_LEN];
}LPP_GNSS_MEAS_LIST_STRU;

/*******************************************************************************
 结构名    : LPP_DGNSS_SAT_LIST_STRU
 结构说明  : 网侧下发GPS模块辅助数据之DGNSS-SatList
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*DGNSS-SatList ::= SEQUENCE (SIZE (1..64)) OF DGNSS-CorrectionsElement*/
    VOS_UINT32                              ulDGNSSSatListcnt;
    LPP_DGNSS_CORRECT_ELEMENT_STRU          astDGNSSCorrectElementArray[LPP_MAX_DGNSS_CORRECT_ELEMENT_LEN];
}LPP_DGNSS_SAT_LIST_STRU;

/*******************************************************************************
 结构名    : LPP_GNSS_ID_GPS_STRU
 结构说明  : 网侧下发GPS模块辅助数据之GNSS-ID-GPS
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    GNSS-ID-GPS ::= SEQUENCE    (SIZE(1..64)) OF GNSS-ID-GPS-SatElement
    */
    VOS_UINT32                              ulGNSSIdGpsCnt;
    LPP_GNSS_ID_GPS_SAT_ELEMENT_STRU        astGNSSIdGpsArray[LPP_MAX_GNSS_ID_GPS_SAT_ELEMENT_LEN];
}LPP_GNSS_ID_GPS_STRU;

/*******************************************************************************
 结构名    : LPP_GNSS_ID_GLONASS_STRU
 结构说明  : 网侧下发GPS模块辅助数据之GNSS-ID-GLONASS
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    GNSS-ID-GLONASS ::= SEQUENCE (SIZE(1..64)) OF GNSS-ID-GLONASS-SatElement
    */
    VOS_UINT32                                  ulGNSSIdGlonassCnt;
    LPP_GNSS_ID_GLONASS_SAT_ELEMENT_STRU        astGNSSIdGlonassArray[LPP_MAX_GNSS_ID_GLONASS_SAT_ELEMENT_LEN];
}LPP_GNSS_ID_GLONASS_STRU;

/*******************************************************************************
 结构名    : LPP_GNSS_ALMANAC_LIST_STRU
 结构说明  : 网侧下发GPS模块辅助数据之AlmanacList
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    GNSS-AlmanacList ::= SEQUENCE (SIZE(1..64)) OF GNSS-AlmanacElement
    */
    VOS_UINT32                          ulGNSSAlmanacListCnt;
    LPP_GNSS_ALMANAC_ELEMENT_STRU       astGNSSAlmanacListArray[LPP_MAX_GNSS_ALMANAC_ELMENT_LEN];
}LPP_GNSS_ALMANAC_LIST_STRU;

/*******************************************************************************
 结构名    : LPP_GNSS_ACQUISIT_ASSIST_LIST_STRU
 结构说明  : 网侧下发GPS模块辅助数据之AcquisitionAssistList
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    GNSS-AcquisitionAssistList ::= SEQUENCE (SIZE(1..64)) OF GNSS-AcquisitionAssistElement
    */
    VOS_UINT32                                  ulGNSSAcquisitAssitListCnt;
    LPP_GNSS_ACQUISIT_ASSIST_ELEMENT_STRU       astGNSSAcquisitAssistListArray[LPP_MAX_GNSS_ACQUSITON_ASSIST_ELMENT_LEN];
}LPP_GNSS_ACQUISIT_ASSIST_LIST_STRU;

/*******************************************************************************
 结构名    : LPP_GNSS_BAD_SIGNAL_LIST_STRU
 结构说明  : 网侧下发GPS模块辅助数据之BadSignalList
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    GNSS-BadSignalList ::= SEQUENCE (SIZE(1..64)) OF BadSignalElement
    */
    VOS_UINT32                                  ulGNSSBadSignalListCnt;
    LPP_GNSS_BAD_SIGNAL_ELEMENT_STRU            stGNSSBadSignalListArray[LPP_MAX_BAD_SIGNAL_ELEMENT_LEN];
}LPP_GNSS_BAD_SIGNAL_LIST_STRU;

/*******************************************************************************
 结构名    : LPP_GNSS_NAV_MODEL_SATELLITE_LIST_STRU
 结构说明  : 网侧下发GPS模块辅助数据之NavModelSatelliteList
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    GNSS-NavModelSatelliteList ::= SEQUENCE (SIZE(1..64)) OF GNSS-NavModelSatelliteElement
    */
    VOS_UINT32                                              ulGNSSNavModelSatelliteListCnt;
    LPP_GNSS_NAV_MODEL_SATELLITE_LIST_ELEMENT_STRU          astGNSSNavModelSatelliteListArray[LPP_MAX_NAV_MODEL_SAT_ELEMENT_LEN];
}LPP_GNSS_NAV_MODEL_SATELLITE_LIST_STRU;

/*******************************************************************************
 结构名    : LPP_GNSS_DATA_BITS_SATLIST_STRU
 结构说明  : 网侧下发GPS模块辅助数据之DataBitsSatList
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    GNSS-DataBitsSatList ::= SEQUENCE (SIZE(1..64))OF GNSS-DataBitsSatElement
    */
    VOS_UINT32                                      ulGNSSDataBitsSatListCnt;
    LPP_GNSS_DATA_BITS_SAT_ELEMENT_STRU             astGNSSDataBitsSatListArray[LPP_MAX_GNSS_DATA_BITS_SAT_ELEMENT_LEN];
}LPP_GNSS_DATA_BITS_SATLIST_STRU;

/*******************************************************************************
 结构名    : LPP_GNSS_DATA_BIT_ASSIST_STRU
 结构说明  : 网侧下发GPS模块辅助数据之DataBitAssistance
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    GNSS-DataBitAssistance ::= SEQUENCE {
        gnss-TOD                INTEGER (0..3599),
        gnss-TODfrac            INTEGER (0..999)        OPTIONAL,   -- Need ON
        gnss-DataBitsSatList    GNSS-DataBitsSatList,
        ...
    }
    */
    VOS_UINT32                          bitOpGNSSDataBitAssistExt:1;
    VOS_UINT32                          bitOpGNSSTodFrac         :1;
    VOS_UINT32                          bitOpSpare               :30;

    VOS_UINT16                          usGNSSTod;
    VOS_UINT16                          usGNSSTodFrac;
    LPP_GNSS_DATA_BITS_SATLIST_STRU     stGNSSDataBitsSatlist;
}LPP_GNSS_DATA_BIT_ASSIST_STRU;

/*******************************************************************************
 结构名    : LPP_GNSS_GENERIC_ASSIST_DATA_ELEMENT_STRU
 结构说明  : 网侧下发GPS模块辅助数据之GenericAssistDataElement
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    GNSS-GenericAssistDataElement ::= SEQUENCE {
        gnss-ID                         GNSS-ID,
        sbas-ID                         SBAS-ID                         OPTIONAL, -- Cond GNSS-ID-SBAS
        gnss-TimeModels                 GNSS-TimeModelList              OPTIONAL,   -- Need ON
        gnss-DifferentialCorrections    GNSS-DifferentialCorrections    OPTIONAL,   -- Need ON
        gnss-NavigationModel            GNSS-NavigationModel            OPTIONAL,   -- Need ON
        gnss-RealTimeIntegrity          GNSS-RealTimeIntegrity          OPTIONAL,   -- Need ON
        gnss-DataBitAssistance          GNSS-DataBitAssistance          OPTIONAL,   -- Need ON
        gnss-AcquisitionAssistance      GNSS-AcquisitionAssistance      OPTIONAL,   -- Need ON
        gnss-Almanac                    GNSS-Almanac                    OPTIONAL,   -- Need ON
        gnss-UTC-Model                  GNSS-UTC-Model                  OPTIONAL,   -- Need ON
        gnss-AuxiliaryInformation       GNSS-AuxiliaryInformation       OPTIONAL,   -- Need ON
        ...
    }
    */
    VOS_UINT32                              bitOpGNSSGenericAssistDataElementExt:1;
    VOS_UINT32                              bitOpSbasId                         :1;
    VOS_UINT32                              bitOpGNSSTimeModelIs                :1;
    VOS_UINT32                              bitOpGNSSDiffCorrection             :1;
    VOS_UINT32                              bitOpGNSSNavigationModel            :1;
    VOS_UINT32                              bitOpGNSSRealTimeIntegrity          :1;
    VOS_UINT32                              bitOpGNSSDataBitAssit               :1;
    VOS_UINT32                              bitOpGNSSAcqAssit                   :1;
    VOS_UINT32                              bitOpGNSSAlmanac                    :1;
    VOS_UINT32                              bitOpGNSSUtcModel                   :1;
    VOS_UINT32                              bitOpGNSSAuxInfo                    :1;
    VOS_UINT32                              bitOpSpare                          :21;

    LPP_GNSS_ID_STRU                        stGNSSId;
    LPP_SBAS_ID_STRU                        stSbasId;
    LPP_GNSS_TIME_MODEL_LIST_STRU           stGNSSTimeModels;
    LPP_GNSS_DIFF_CORRECT_STRU              stGNSSDiffCorrect;
    LPP_GNSS_NAVIGATION_MODEL_STRU          stGNSSNavigationModel;
    LPP_GNSS_REALTIME_INTERGRITY_STRU       stGNSSRealTimeIntergrity;
    LPP_GNSS_DATA_BIT_ASSIST_STRU           stGNSSDataBitAssistance;
    LPP_GNSS_ACQUISIT_ASSIST_STRU           stGNSSAcquisitAssit;
    LPP_GNSS_ALMANAC_STRU                   stGNSSAlmanac;/*ATCPOS_GNSS_ALMANAC_STRU*/
    LPP_GNSS_UTC_MODEL_STRU                 stGNSSUtcModel;/*ATCPOS_UTCMODEL5_R12_STRU*/
    LPP_GNSS_AUX_INFO_STRU                  stGNSSAuxInfo;/*ATCPOS_GNSS_ID_GLONASS_STRU*/
}LPP_GNSS_GENERIC_ASSIST_DATA_ELEMENT_STRU;

/*******************************************************************************
 结构名    : LPP_GNSS_GENERIC_ASSIST_DATA_STRU
 结构说明  : 网侧下发GPS模块辅助数据之GenericAssistData
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    GNSS-GenericAssistData ::= SEQUENCE (SIZE (1..16)) OF GNSS-GenericAssistDataElement
    */
    VOS_UINT32                                      ulGNSSGenericAssitDataCnt;
    LPP_GNSS_GENERIC_ASSIST_DATA_ELEMENT_STRU       astGNSSGenericAssistDataArray[LPP_MAX_GNSS_GENERIC_ASSIST_DATA_ELEMENT_LEN];
}LPP_GNSS_GENERIC_ASSIST_DATA_STRU;

/*******************************************************************************
 结构名    : LPP_AGNSS_PROVIDE_ASSIST_DATA_STRU
 结构说明  : 网侧下发GPS模块辅助数据之A-GNSS-ProvideAssistanceData
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    A-GNSS-ProvideAssistanceData ::= SEQUENCE {
        gnss-CommonAssistData           GNSS-CommonAssistData               OPTIONAL,   -- Need ON
        gnss-GenericAssistData          GNSS-GenericAssistData              OPTIONAL,   -- Need ON
        gnss-Error                      A-GNSS-Error                        OPTIONAL,   -- Need ON
        ...
    }
    */
    VOS_UINT32                                  bitOpAGnssProvideAssistDataExt  :1;
    VOS_UINT32                                  bitOpGNSSCommonAssitData        :1;
    VOS_UINT32                                  bitOpGNSSGenericAssitData       :1;
    VOS_UINT32                                  bitOpGNSSError                  :1;
    VOS_UINT32                                  bitOpSpare                      :28;

    LPP_GNSS_COMMON_ASSIST_DATA_STRU            stGNSSCommonAssistData;
    LPP_GNSS_GENERIC_ASSIST_DATA_STRU           stGNSSGenericAssitData;
    LPP_GNSS_ERROR_STRU                         stGNSSError;
}LPP_AGNSS_PROVIDE_ASSIST_DATA_STRU;

/*******************************************************************************
 结构名    : LPP_EPDU_IDENTIFIER_STRU
 结构说明  : epdu identifier
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    EPDU-ID ::= INTEGER (1..256)

    EPDU-Name ::= VisibleString (SIZE (1..32))
    */
    VOS_UINT32                          bitOpEpduIdentifierExt   : 1;
    VOS_UINT32                          bitOpEpduName   : 1;
    VOS_UINT32                          bitOpSpare      : 30;

    VOS_UINT32                          ulEpduId;
    VOS_UINT32                          ulEpduNameLength;
    VOS_UINT8                           acEpduName[LPP_MAX_EPDU_NAME_LEN];
}LPP_EPDU_IDENTIFIER_STRU;

/*******************************************************************************
 结构名    : LPP_EPDU_BODY_STRU
 结构说明  : EPDU-Body
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*EPDU-Body ::= OCTET STRING*/
    VOS_UINT32                          ulBodyLen;
    VOS_UINT8                           aucBodyData[LPP_MAX_EPDU_BODY_LEN];
}LPP_EPDU_BODY_STRU;

/*******************************************************************************
 结构名    : LPP_EPDU_STRU
 结构说明  : EPDU
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    EPDU ::= SEQUENCE {
        ePDU-Identifier         EPDU-Identifier,
        ePDU-Body               EPDU-Body
    }
    */
    LPP_EPDU_IDENTIFIER_STRU            stEpduIdentifier;
    LPP_EPDU_BODY_STRU                  stEpduBody;
}LPP_EPDU_STRU;

/*******************************************************************************
 结构名    : LPP_EPDU_SEQUENCE_STRU
 结构说明  : EPDU_SEQUENCE
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEpduNum;
    LPP_EPDU_STRU                       astEpduArray[LPP_MAX_EPDU_NUM];
}LPP_EPDU_SEQUENCE_STRU;

/*******************************************************************************
 结构名    : LPP_TRANSACTION_ID_STRU
 结构说明  : LPP-TransactionID
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    LPP-TransactionID ::= SEQUENCE {
        initiator               Initiator,
        transactionNumber       TransactionNumber,
        ...
    }
    */

    VOS_UINT32                      bitOpTransactionIDExt:1;
    VOS_UINT32                      bitOpSpare:31;

    LPP_INITIATOR_TYPE_ENUM_UINT8       enInitiator;
    VOS_UINT8                           ucTransactionNumber;
    VOS_UINT8                           aucRes[2];
}LPP_TRANSACTION_ID_STRU;

/*******************************************************************************
 结构名    : LPP_SEQUENCE_NUMBER_STRU
 结构说明  : SequenceNumber
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    SequenceNumber ::= INTEGER (0..255)
    */
    VOS_UINT8                           ucSequenceNumber;
    VOS_UINT8                           aucRes[3];
}LPP_SEQUENCE_NUMBER_STRU;

/*******************************************************************************
 结构名    : LPP_ACKNOWLEDGEMENT_STRU
 结构说明  : Acknowledgement
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    Acknowledgement ::= SEQUENCE {
        ackRequested    BOOLEAN,
        ackIndicator    SequenceNumber      OPTIONAL
    }
    */
    VOS_UINT32                          bitOpAckIndicator:1;
    VOS_UINT32                          bitOpSpare:31;

    VOS_BOOL                            bAckRequested;
    LPP_SEQUENCE_NUMBER_STRU            stAckIndicator;
}LPP_ACKNOWLEDGEMENT_STRU;

/*******************************************************************************
 结构名    : LPP_COMMON_IES_ERROR_STRU
 结构说明  : CommonIEsError
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    CommonIEsError ::= SEQUENCE {
        errorCause      ENUMERATED {
            undefined,
            lppMessageHeaderError,
            lppMessageBodyError,
            epduError,
            incorrectDataValue,
            ...
        }
    }
    */
    VOS_UINT32                          bitOpCommonIEsErrorExt:1;
    VOS_UINT32                          bitOpSpare:31;

    LPP_COMMON_IES_ERROR_ENUM_UINT8     enCommonIesErrorCasue;
    VOS_UINT8                           aucRsv[3];
}LPP_COMMON_IES_ERROR_STRU;

/*******************************************************************************
 结构名    : LPP_ERROR_R9_STRU
 结构说明  : Error-r9-IEs
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    Error-r9-IEs ::= SEQUENCE {
        commonIEsError      CommonIEsError          OPTIONAL,   -- Need ON
        ...,
        epdu-Error          EPDU-Sequence           OPTIONAL    -- Need ON
    }
    */
    VOS_UINT32                      bitOpErrorR9IEsExt:1;
    VOS_UINT32                      bitOpCommonIesError:1;
    VOS_UINT32                      bitOpEpduError:1;
    VOS_UINT32                      bitOpSpare:29;

    LPP_COMMON_IES_ERROR_STRU       stCommonIesError;
    LPP_EPDU_SEQUENCE_STRU          stEpduError;
}LPP_ERROR_R9_STRU;

/*******************************************************************************
 结构名    : LPP_MESSAGE_ERROR_STRU
 结构说明  : Error
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    Error ::= CHOICE {
        error-r9                    Error-r9-IEs,
        criticalExtensionsFuture    SEQUENCE {}
    }
    */
    VOS_UINT32                                          ulChoice;

    #define           LPP_ERROR_R9_IES_CHOSEN                0
    #define           LPP_ERROR_EXT_FUTURE_CHOSEN            1

     union
     {
        LPP_ERROR_R9_STRU                               stErrorR9;
        VOS_UINT8                                       ucCritiExtFuture;
     }u;
}LPP_MESSAGE_ERROR_STRU;


/*******************************************************************************
 结构名    : LPP_COMMON_IES_ABORT_STRU
 结构说明  : CommonIEsAbort
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    CommonIEsAbort ::= SEQUENCE {
        abortCause          ENUMERATED {
            undefined,
            stopPeriodicReporting,
            targetDeviceAbort,
            networkAbort,
            ...
        }
    }
    */
    VOS_UINT32                              bitOpCommonIEsAbortExt:1;
    VOS_UINT32                              bitOpSpare:31;

    LPP_COMMON_IES_ABORT_ENUM_UINT8         enCommonIesAbortCasue;
    VOS_UINT8                               aucRsv[3];
}LPP_COMMON_IES_ABORT_STRU;

/*******************************************************************************
 结构名    : LPP_ABORT_R9_IES_STRU
 结构说明  : Abort-r9-IEs
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/

typedef struct
{
    /*
    Abort-r9-IEs ::= SEQUENCE {
        commonIEsAbort      CommonIEsAbort          OPTIONAL,   -- Need ON
        ...,
        epdu-Abort          EPDU-Sequence           OPTIONAL    -- Need ON
    }
    */
    VOS_UINT32                  bitOpAbortR9IEsExt:1;
    VOS_UINT32                  bitOpCommonIesAbort:1;
    VOS_UINT32                  bitOpEpduAbort:1;
    VOS_UINT32                  bitOpSpare:29;

    LPP_COMMON_IES_ABORT_STRU   stCommonIesAbort;
    LPP_EPDU_SEQUENCE_STRU      stEpduAbort;
}LPP_ABORT_R9_IES_STRU;

/*******************************************************************************
 结构名    : LPP_C1_EXT_ABORT_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/

typedef struct
{
    VOS_UINT32                                          ulChoice;

    #define         LPP_C1_CRITI_EXT_ABORT_R9_CHOSEN              0
    #define         LPP_SPARE3_C1_CRITI_EXT_ABORT_CHOSEN          1
    #define         LPP_SPARE2_C1_CRITI_EXT_ABORT_CHOSEN          2
    #define         LPP_SPARE1_C1_CRITI_EXT_ABORT_CHOSEN          3

    union
    {
        LPP_ABORT_R9_IES_STRU                               stAbortR9;
        VOS_UINT8                                           ucSpare3;
        VOS_UINT8                                           ucSpare2;
        VOS_UINT8                                           ucSpare1;
    }u;
}LPP_C1_EXT_ABORT_STRU;

/*******************************************************************************
 结构名    : LPP_CRIT_EXT_ABORT_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct

{
    VOS_UINT32                                          ulChoice;

    #define         LPP_CRITI_EXT_ABORT_CHOSEN                      0
    #define         LPP_CRITI_EXT_ABORT_FUTURE_CHOSEN                1


    union
    {
        LPP_C1_EXT_ABORT_STRU                               stAbortExtC1;
        VOS_UINT8                                           ucCritiExtFutue;
    }u;
}LPP_CRIT_EXT_ABORT_STRU;

/*******************************************************************************
 结构名    : LPP_MESSAGE_ABORT_STRU
 结构说明  : Abort
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    Abort ::= SEQUENCE {
        criticalExtensions      CHOICE {
            c1                      CHOICE {
                abort-r9        Abort-r9-IEs,
                spare3 NULL, spare2 NULL, spare1 NULL
            },
            criticalExtensionsFuture    SEQUENCE {}
        }
    }
    */

        LPP_CRIT_EXT_ABORT_STRU                        stC1;

}LPP_MESSAGE_ABORT_STRU;

/*******************************************************************************
 结构名    : LPP_EPDU_PROVIDE_LOCATION_INFO_STRU
 结构说明  : EPDU-Sequence
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    EPDU-Sequence ::= SEQUENCE (SIZE (1..maxEPDU)) OF EPDU
    */
    VOS_UINT32                          ulEpduSequenceCnt;
    LPP_EPDU_STRU                       astEpduSequenceArray[LPP_MAX_EPDU_NUM];
}LPP_EPDU_PROVIDE_LOCATION_INFO_STRU;

/*******************************************************************************
 结构名    : LPP_GNSS_SIGNAL_MEAS_INFO_STRU
 结构说明  : GPS提供位置信息之SignalMeasurementInformation
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    GNSS-SignalMeasurementInformation ::= SEQUENCE {
        measurementReferenceTime        MeasurementReferenceTime,
        gnss-MeasurementList            GNSS-MeasurementList,
        ...
    }
    */
    VOS_UINT32                          bitOpGNSSSignalMeasInfoExt:1;
    VOS_UINT32                          bitOpSpare                :31;

    LPP_MEAS_REF_TIME_STRU              stMeasRefTime;
    LPP_GNSS_MEAS_LIST_STRU             stGNSSMeasList;
}LPP_GNSS_SIGNAL_MEAS_INFO_STRU;

/*******************************************************************************
 结构名    : LPP_AGNSS_PROVIDE_LOCATION_INFO_STRU
 结构说明  : GPS提供位置信息之A-GNSS-ProvideLocationInformation
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    A-GNSS-ProvideLocationInformation ::= SEQUENCE {
        gnss-SignalMeasurementInformation   GNSS-SignalMeasurementInformation       OPTIONAL,
        gnss-LocationInformation            GNSS-LocationInformation                OPTIONAL,
        gnss-Error                          A-GNSS-Error                            OPTIONAL,
        ...
    }
    */
    VOS_UINT32                              bitOpAGNSSProvideLocationInfoExt:1;
    VOS_UINT32                              bitOpGNSSSignalMeasInfo         :1;
    VOS_UINT32                              bitOpGNSSLocationInfo           :1;
    VOS_UINT32                              bitOpGNSSError                  :1;
    VOS_UINT32                              bitOpSpare                      :28;

    LPP_GNSS_SIGNAL_MEAS_INFO_STRU          stGNSSsignalMeasInfo;
    LPP_GNSS_LOCATION_INFO_STRU             stGNSSLocationInfo;
    LPP_GNSS_ERROR_STRU                     stGNSSError;
}LPP_AGNSS_PROVIDE_LOCATION_INFO_STRU;

/*******************************************************************************
 结构名    : LPP_PROVIDE_LOCATION_INFO_R9_IES_STRU
 结构说明  : ProvideLocationInformation-r9-IEs
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    ProvideLocationInformation-r9-IEs ::= SEQUENCE {
        commonIEsProvideLocationInformation
                                        CommonIEsProvideLocationInformation     OPTIONAL,
        a-gnss-ProvideLocationInformation   A-GNSS-ProvideLocationInformation   OPTIONAL,
        otdoa-ProvideLocationInformation    OTDOA-ProvideLocationInformation    OPTIONAL,
        ecid-ProvideLocationInformation     ECID-ProvideLocationInformation     OPTIONAL,
        epdu-ProvideLocationInformation     EPDU-Sequence                       OPTIONAL,
        ...
    }
    */
    VOS_UINT32                          bitOpLPPProvideLocationInfoExt:1;
    VOS_UINT32                          bitOpCommonIEsPRovideLocationInfo:1;
    VOS_UINT32                          bitOpAGNSSPRovideLocationInfo:1;
    VOS_UINT32                          bitOpOtdoaPRovideLocationInfo:1;
    VOS_UINT32                          bitOpEcidPRovideLocationInfo:1;
    VOS_UINT32                          bitOpEpduSequence:1;
    VOS_UINT32                          bitOpSpare:26;

    LPP_COMMON_IES_PROVIDE_LOCATION_INFO_STRU           stCommonIEsPRovideLocationInfo;
    LPP_AGNSS_PROVIDE_LOCATION_INFO_STRU                stAGNSSPRovideLocationInfo;
    LPP_OTDOA_PROVIDE_LOCATION_INFO_STRU                stOtdoaPRovideLocationInfo;
    LPP_ECID_PROVIDE_LOCATION_INFO_STRU                 stEcidPRovideLocationInfo;
    LPP_EPDU_PROVIDE_LOCATION_INFO_STRU                 stEpduPRovideLocationInfo;
}LPP_PROVIDE_LOCATION_INFO_R9_IES_STRU;

/*******************************************************************************
 结构名    : LPP_CRITI_EXT_PROVIDE_LOCATION_INFO_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                          ulChoice;

    #define         LPP_C1_CRITI_EXT_PROVIDE_LOCATION_INFO_R9_CHOSEN              0
    #define         LPP_SPARE3_C1_CRITI_EXT_PROVIDE_LOCATION_INFO_CHOSEN          1
    #define         LPP_SPARE2_C1_CRITI_EXT_PROVIDE_LOCATION_INFO_CHOSEN          2
    #define         LPP_SPARE1_C1_CRITI_EXT_PROVIDE_LOCATION_INFO_CHOSEN          3

        union
        {
            LPP_PROVIDE_LOCATION_INFO_R9_IES_STRU               stProLocationInfoR9;
            VOS_UINT8                                           ucSpare3;
            VOS_UINT8                                           ucSpare2;
            VOS_UINT8                                           ucSpare1;
        }u;
}LPP_CRITI_EXT_PROVIDE_LOCATION_INFO_STRU;

/*******************************************************************************
 结构名    : LPP_MESSAGE_PROVIDE_LOCATION_INFO_STRU
 结构说明  :ProvideLocationInformation
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    ProvideLocationInformation ::= SEQUENCE {
        criticalExtensions      CHOICE {
            c1                      CHOICE {
                provideLocationInformation-r9   ProvideLocationInformation-r9-IEs,
                spare3 NULL, spare2 NULL, spare1 NULL
            },
            criticalExtensionsFuture    SEQUENCE {}
        }
    }
    */
    VOS_UINT32                                          ulChoice;

    #define           LPP_C1_CRITI_EXT_PROVIDE_LOCATION_INFO_CHOSEN                0
    #define           LPP_CRITI_EXT_FUTURE_PROVIDE_LOCATION_INFO_CHOSEN            1

     union
     {
        LPP_CRITI_EXT_PROVIDE_LOCATION_INFO_STRU            stC1;
        VOS_UINT8                                       ucCritiExtFuture;
     }u;
}LPP_MESSAGE_PROVIDE_LOCATION_INFO_STRU;

/*******************************************************************************
 结构名    : LPP_EPDU_REQ_LOCATION_INFO_STRU
 结构说明  :EPDU-Sequence
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    EPDU-Sequence ::= SEQUENCE (SIZE (1..maxEPDU)) OF EPDU
    */
    VOS_UINT32              ulEpduSequence;
    LPP_EPDU_STRU           astEpduSequence[LPP_MAX_EPDU_NUM];
}LPP_EPDU_REQ_LOCATION_INFO_STRU;

/*******************************************************************************
 结构名    : LPP_REQ_LOCATION_INFO_R9_IES_STRU
 结构说明  :RequestLocationInformation-r9-IEs
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    RequestLocationInformation-r9-IEs ::= SEQUENCE {
        commonIEsRequestLocationInformation
                                        CommonIEsRequestLocationInformation     OPTIONAL,   -- Need ON
        a-gnss-RequestLocationInformation   A-GNSS-RequestLocationInformation   OPTIONAL,   -- Need ON
        otdoa-RequestLocationInformation    OTDOA-RequestLocationInformation    OPTIONAL,   -- Need ON
        ecid-RequestLocationInformation     ECID-RequestLocationInformation     OPTIONAL,   -- Need ON
        epdu-RequestLocationInformation     EPDU-Sequence                       OPTIONAL,   -- Need ON
        ...
    }
    */
    VOS_UINT32                          bitOpLPPReqLocationInfoExt:1;
    VOS_UINT32                          bitOpCommonIEsReqLocationInfo:1;
    VOS_UINT32                          bitOpAGNSSReqLocationInfo:1;
    VOS_UINT32                          bitOpOtdoaReqLocationInfo:1;
    VOS_UINT32                          bitOpEcidReqLocationInfo:1;
    VOS_UINT32                          bitOpEpduSequence:1;
    VOS_UINT32                          bitOpSpare:26;

    LPP_COMMON_IES_REQ_LOCATION_INFO_STRU           stCommonIEsReqLocationInfo;
    LPP_AGNSS_REQ_LOCATION_INFO_STRU                stAGNSSReqLocationInfo;
    LPP_OTDOA_REQ_LOCATION_INFO_STRU                stOtdoaReqLocationInfo;
    LPP_ECID_REQ_LOCATION_INFO_STRU                 stEcidReqLocationInfo;
    LPP_EPDU_REQ_LOCATION_INFO_STRU                 stEpduReqLocationInfo;
}LPP_REQ_LOCATION_INFO_R9_IES_STRU;

/*******************************************************************************
 结构名    : LPP_CRITI_EXT_REQ_LOCATION_INFO_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                          ulChoice;

    #define         LPP_C1_CRITI_EXT_REQ_LOCATION_INFO_R9_CHOSEN              0
    #define         LPP_SPARE3_C1_CRITI_EXT_REQ_LOCATION_INFO_CHOSEN          1
    #define         LPP_SPARE2_C1_CRITI_EXT_REQ_LOCATION_INFO_CHOSEN          2
    #define         LPP_SPARE1_C1_CRITI_EXT_REQ_LOCATION_INFO_CHOSEN          3

        union
        {
            LPP_REQ_LOCATION_INFO_R9_IES_STRU               stReqLocationInfoR9;
            VOS_UINT8                                       ucSpare3;
            VOS_UINT8                                       ucSpare2;
            VOS_UINT8                                       ucSpare1;
        }u;
}LPP_CRITI_EXT_REQ_LOCATION_INFO_STRU;

/*******************************************************************************
 结构名    : LPP_MESSAGE_REQUEST_LOCATION_INFO_STRU
 结构说明  :RequestLocationInformation
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    RequestLocationInformation ::= SEQUENCE {
        criticalExtensions      CHOICE {
            c1                      CHOICE {
                requestLocationInformation-r9   RequestLocationInformation-r9-IEs,
                spare3 NULL, spare2 NULL, spare1 NULL
            },
            criticalExtensionsFuture    SEQUENCE {}
        }
    }
    */
    VOS_UINT32                                          ulChoice;

    #define           LPP_C1_CRITI_EXT_REQ_LOCATION_INFO_CHOSEN                0
    #define           LPP_CRITI_EXT_FUTURE_REQ_LOCATION_INFO_CHOSEN            1

     union
     {
        LPP_CRITI_EXT_REQ_LOCATION_INFO_STRU            stC1;
        VOS_UINT8                                       ucCritiExtFuture;
     }u;
}LPP_MESSAGE_REQUEST_LOCATION_INFO_STRU;

/*******************************************************************************
 结构名    : LPP_COMMON_IES_PROVIDE_ASSIST_DATA_STRU
 结构说明  :    协议为空
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*协议为空*/
    VOS_UINT32              bitOpCommonIEsProvideAssistDataExt:1;
    VOS_UINT32              bitOpSpare:31;
}LPP_COMMON_IES_PROVIDE_ASSIST_DATA_STRU;

/*******************************************************************************
 结构名    : LPP_EPDU_PROVIDE_ASSIST_DATA_STRU
 结构说明  :EPDU-Sequence
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    EPDU-Sequence ::= SEQUENCE (SIZE (1..maxEPDU)) OF EPDU
    */
    VOS_UINT32              ulEpduCnt;
    LPP_EPDU_STRU           astEpduSequenceArray[LPP_MAX_EPDU_NUM];
}LPP_EPDU_PROVIDE_ASSIST_DATA_STRU;

/*******************************************************************************
 结构名    : LPP_PROVIDE_ASSIST_DATA_R9_IES_STRU
 结构说明  :ProvideAssistanceData-r9-IEs
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    ProvideAssistanceData-r9-IEs ::= SEQUENCE {
        commonIEsProvideAssistanceData      CommonIEsProvideAssistanceData      OPTIONAL,   -- Need ON
        a-gnss-ProvideAssistanceData        A-GNSS-ProvideAssistanceData        OPTIONAL,   -- Need ON
        otdoa-ProvideAssistanceData         OTDOA-ProvideAssistanceData         OPTIONAL,   -- Need ON
        epdu-Provide-Assistance-Data        EPDU-Sequence                       OPTIONAL,   -- Need ON
        ...
    }
    */
    VOS_UINT32                          bitOpLPPProvideAssistDataExt:1;
    VOS_UINT32                          bitOpCommonIEsProvideAssitData:1;
    VOS_UINT32                          bitOpAGNSSProvideAssistData:1;
    VOS_UINT32                          bitOpOTDOAProvideAssistData:1;
    VOS_UINT32                          bitOpEPDUSequence:1;
    VOS_UINT32                          bitOpSpare:27;

    LPP_COMMON_IES_PROVIDE_ASSIST_DATA_STRU         stCommonIEsProvideAssistanceData;
    LPP_AGNSS_PROVIDE_ASSIST_DATA_STRU              stAGNSSProvideAssistanceData;
    LPP_OTDOA_PROVIDE_ASSIST_DATA_STRU              stOTDOAProvideAssistanceData;
    LPP_EPDU_PROVIDE_ASSIST_DATA_STRU               stEPDUProvideAssistanceData;
}LPP_PROVIDE_ASSIST_DATA_R9_IES_STRU;

/*******************************************************************************
 结构名    : LPP_CRITI_EXT_PROVIDE_ASSIST_DATA_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                          ulChoice;

    #define         LPP_C1_CRITI_EXT_PROVIDE_ASSIST_DATA_R9_CHOSEN              0
    #define         LPP_SPARE3_C1_CRITI_EXT_PROVIDE_ASSIST_DATA_CHOSEN          1
    #define         LPP_SPARE2_C1_CRITI_EXT_PROVIDE_ASSIST_DATA_CHOSEN          2
    #define         LPP_SPARE1_C1_CRITI_EXT_PROVIDE_ASSIST_DATA_CHOSEN          3

    union
    {
        LPP_PROVIDE_ASSIST_DATA_R9_IES_STRU             stProvideAssitDataR9;
        VOS_UINT8                                       ucSpare3;
        VOS_UINT8                                       ucSpare2;
        VOS_UINT8                                       ucSpare1;
    }u;
}LPP_CRITI_EXT_PROVIDE_ASSIST_DATA_STRU;

/*******************************************************************************
 结构名    : LPP_MESSAGE_PROVIDE_ASSIST_DATA_STRU
 结构说明  :ProvideAssisData
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    ProvideAssisData ::= SEQUENCE {
        criticalExtensions      CHOICE {
            c1                      CHOICE {
                ProvideAssisData-r9      ProvideAssisData-r9-IEs,
                spare3 NULL, spare2 NULL, spare1 NULL
            },
            criticalExtensionsFuture    SEQUENCE {}
        }
    }

   ProvideAssisData-r9-IEs ::= SEQUENCE {
        commonIEsProvideAssisData        CommonIEsProvideAssisData       	OPTIONAL,
        a-gnss-ProvideAssisData         A-GNSS-ProvideAssisData          		OPTIONAL,
        otdoa-ProvideAssisData          OTDOA-ProvideAssisData       			OPTIONAL,
        epdu-ProvideAssisData            EPDU-Sequence                      		OPTIONAL,
        ...
    }
    */
    VOS_UINT32                                          ulChoice;

    #define           LPP_C1_CRITI_EXT_PROVIDE_ASSIST_DATA_CHOSEN        0
    #define           LPP_CRITI_EXT_FUTURE_PROVIDE_ASSIST_DATA_CHOSEN    1

    union
    {
        LPP_CRITI_EXT_PROVIDE_ASSIST_DATA_STRU           stC1;
        VOS_UINT8                                        ucCritiExtFuture;
    }u;
}LPP_MESSAGE_PROVIDE_ASSIST_DATA_STRU;

/*******************************************************************************
 结构名    : LPP_EPDU_REQ_ASSIST_DATA_STRU
 结构说明  :EPDU-Sequence
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*EPDU-Sequence ::= SEQUENCE (SIZE (1..maxEPDU)) OF EPDU*/
    LPP_EPDU_SEQUENCE_STRU      astReqAssistDataEpduSeq;
}LPP_EPDU_REQ_ASSIST_DATA_STRU;

/*******************************************************************************
 结构名    : LPP_COMMON_IES_REQ_ASSIST_DATA_STRU
 结构说明  :CommonIEsRequestAssistanceData
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    CommonIEsRequestAssistanceData ::= SEQUENCE {
        primaryCellID       ECGI        OPTIONAL,   -- Cond EUTRA
        ...
    }
    */
    VOS_UINT32      bitOpCommonIEsReqAssistDataExt:1;
    VOS_UINT32      bitOpPrimaryCellID:1;
    VOS_UINT32      bitOpSpare:30;

    LPP_ECGI_STRU   stPrimaryCellID;

}LPP_COMMON_IES_REQ_ASSIST_DATA_STRU;

/*******************************************************************************
 结构名    : LPP_AGNSS_REQ_ASSIST_DATA_STRU
 结构说明  : GPS模块提供能力之RequestAssistanceData
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    A-GNSS-RequestAssistanceData ::= SEQUENCE {
        gnss-CommonAssistDataReq        GNSS-CommonAssistDataReq        OPTIONAL, -- Cond CommonADReq
        gnss-GenericAssistDataReq       GNSS-GenericAssistDataReq       OPTIONAL, -- Cond GenADReq
        ...
    }
    */
    VOS_UINT32                                  bitOpAGNSSReqAssistDataExt  :1;
    VOS_UINT32                                  bitOpGNSSCommAssistData     :1;
    VOS_UINT32                                  bitOpGNSSGenericAssistData  :1;
    VOS_UINT32                                  bitOpSpare                  :29;

    LPP_GNSS_COMMON_ASSIST_DATA_REQ_STRU        stGNSSCommonAssistDataReq;
    LPP_GNSS_GENERIC_ASSIST_DATA_REQ_STRU       stGNSSGenericAssistDataReq;
}LPP_AGNSS_REQ_ASSIST_DATA_STRU;

/*******************************************************************************
 结构名    : LPP_REQUEST_ASSIST_DATA_R9_IES_STRU
 结构说明  :RequestAssistanceData-r9-IEs
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    RequestAssistanceData ::= SEQUENCE {
        criticalExtensions      CHOICE {
            c1                      CHOICE {
                requestAssistanceData-r9    RequestAssistanceData-r9-IEs,
                spare3 NULL, spare2 NULL, spare1 NULL
            },
            criticalExtensionsFuture    SEQUENCE {}
        }
    }

    RequestAssistanceData-r9-IEs ::= SEQUENCE {
        commonIEsRequestAssistanceData      CommonIEsRequestAssistanceData      OPTIONAL,
        a-gnss-RequestAssistanceData        A-GNSS-RequestAssistanceData        OPTIONAL,
        otdoa-RequestAssistanceData         OTDOA-RequestAssistanceData         OPTIONAL,
        epdu-RequestAssistanceData          EPDU-Sequence                       OPTIONAL,
        ...
    }
    */
    VOS_UINT32                          bitOpLPPRequestAssistDataExt:1;
    VOS_UINT32                          bitOpCommonIEsRequestAssitData:1;
    VOS_UINT32                          bitOpAGNSSRequestAssistData:1;
    VOS_UINT32                          bitOpOTDOARequestAssistData:1;
    VOS_UINT32                          bitOpEPDUSequence:1;
    VOS_UINT32                          bitOpSpare:27;

    LPP_COMMON_IES_REQ_ASSIST_DATA_STRU         stCommonIEsRequestAssistanceData;
    LPP_AGNSS_REQ_ASSIST_DATA_STRU              stAGNSSRequestAssistanceData;
    LPP_OTDOA_REQ_ASSIST_DATA_STRU              stOTDOARequestAssistanceData;
    LPP_EPDU_REQ_ASSIST_DATA_STRU               stEPDURequestAssistanceData;
}LPP_REQUEST_ASSIST_DATA_R9_IES_STRU;

/*******************************************************************************
 结构名    : LPP_CRITI_EXT_REQUEST_ASSIST_DATA_STRU
 结构说明  :RequestAssistanceData
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                          ulChoice;

    #define         LPP_C1_CRITI_EXT_REQUEST_ASSIST_DATA_R9_CHOSEN              0
    #define         LPP_SPARE3_C1_CRITI_EXT_REQUEST_ASSIST_DATA_CHOSEN          1
    #define         LPP_SPARE2_C1_CRITI_EXT_REQUEST_ASSIST_DATA_CHOSEN          2
    #define         LPP_SPARE1_C1_CRITI_EXT_REQUEST_ASSIST_DATA_CHOSEN          3

    union
    {
        LPP_REQUEST_ASSIST_DATA_R9_IES_STRU             stRequestAssitDataR9;
        VOS_UINT8                                       ucSpare3;
        VOS_UINT8                                       ucSpare2;
        VOS_UINT8                                       ucSpare1;
    }u;
}LPP_CRITI_EXT_REQUEST_ASSIST_DATA_STRU;

/*******************************************************************************
 结构名    : LPP_MESSAGE_REQUEST_ASSIST_DATA_STRU
 结构说明  :RequestAssistanceData
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                          ulChoice;

    #define           LPP_C1_CRITI_EXT_REQUEST_ASSIST_DATA_CHOSEN        0
    #define           LPP_CRITI_EXT_FUTURE_REQUEST_ASSIST_DATA_CHOSEN    1

     union
     {
        LPP_CRITI_EXT_REQUEST_ASSIST_DATA_STRU           stC1;
        VOS_UINT8                                        ucCritiExtFuture;
     }u;
}LPP_MESSAGE_REQUEST_ASSIST_DATA_STRU;

/*******************************************************************************
 结构名    : LPP_COMMON_IES_PROVIDE_CAP_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*协议为空*/
    VOS_UINT32          bitOpCommonIEsProvideCapExt:1;
    VOS_UINT32          bitOpSpare:31;
}LPP_COMMON_IES_PROVIDE_CAP_STRU;

/*******************************************************************************
 结构名    : LPP_PROVIDE_CAPABILITIES_R9_IES_STRU
 结构说明  :ProvideCapabilities-r9-IEs
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    ProvideCapabilities-r9-IEs ::= SEQUENCE {
        commonIEsProvideCapabilities        CommonIEsProvideCapabilities        OPTIONAL,
        a-gnss-ProvideCapabilities          A-GNSS-ProvideCapabilities          OPTIONAL,
        otdoa-ProvideCapabilities           OTDOA-ProvideCapabilities           OPTIONAL,
        ecid-ProvideCapabilities            ECID-ProvideCapabilities            OPTIONAL,
        epdu-ProvideCapabilities            EPDU-Sequence                       OPTIONAL,
        ...
    }
    */
    VOS_UINT32                              bitOpLPPProvideCapabilitiesExt:1;
    VOS_UINT32                              bitOpCommonIEsProvideCapabilities:1;
    VOS_UINT32                              bitOpAGNSSProvideCapabilities:1;
    VOS_UINT32                              bitOpOTDOAProvideCapabilities:1;
    VOS_UINT32                              bitOpECIDProvideCapabilities:1;
    VOS_UINT32                              bitOpEPDUProvideCapabilities:1;
    VOS_UINT32                              bitOpSpare:26;

    LPP_COMMON_IES_PROVIDE_CAP_STRU         stCommonIEsProvideCapabilities;
    LPP_AGNSS_PROVIDE_CAP_STRU              stAGNSSProvideCapabilities;
    LPP_OTDOA_PROVIDE_CAP_STRU              stOTDOAProvideCapabilities;
    LPP_ECID_PROVIDE_CAP_STRU               stECIDProvideCapabilities;
    LPP_EPDU_SEQUENCE_STRU                  stEPDURequestCapabilities;
}LPP_PROVIDE_CAPABILITIES_R9_IES_STRU;

/*******************************************************************************
 结构名    : LPP_CRITI_EXT_PROVIDE_CAPABILITIES_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                      ulChoice;

    #define         LPP_PROVIDE_CAPABILITIES_R9_CHOSEN              0
    #define         LPP_PROVIDE_CAPABILITIES_SPARE3_CHOSEN          1
    #define         LPP_PROVIDE_CAPABILITIES_SPARE2_CHOSEN          2
    #define         LPP_PROVIDE_CAPABILITIES_SPARE1_CHOSEN          3

    union
    {
        LPP_PROVIDE_CAPABILITIES_R9_IES_STRU        stProvideCapabilitiesR9;
        VOS_UINT8                                   ucSpare3;
        VOS_UINT8                                   ucSpare2;
        VOS_UINT8                                   ucSpare1;
    }u;
}LPP_CRITI_EXT_PROVIDE_CAPABILITIES_STRU;

/*******************************************************************************
 结构名    : LPP_MESSAGE_PROVIDE_CAPABILITIES_STRU
 结构说明  :ProvideCapabilities
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    ProvideCapabilities ::= SEQUENCE {
        criticalExtensions      CHOICE {
            c1                      CHOICE {
                provideCapabilities-r9      ProvideCapabilities-r9-IEs,
                spare3 NULL, spare2 NULL, spare1 NULL
            },
            criticalExtensionsFuture    SEQUENCE {}
        }
    }
    */
    VOS_UINT32                                          ulChoice;

    #define           LPP_C1_CRITI_EXT_PROVIDE_CAPABILITIES_CHOSEN        0
    #define           LPP_CRITI_EXT_FUTURE_PROVIDE_CAPABILITIES_CHOSEN    1

    union
    {
       LPP_CRITI_EXT_PROVIDE_CAPABILITIES_STRU          stC1;
       VOS_UINT8                                        ucCritiExtFuture;
    }u;
}LPP_MESSAGE_PROVIDE_CAPABILITIES_STRU;

/*******************************************************************************
 结构名    : LPP_EPDU_REQ_CAP_STRU
 结构说明  :EPDU-Sequence
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*EPDU-Sequence ::= SEQUENCE (SIZE (1..maxEPDU)) OF EPDU*/
    VOS_UINT32                      ulEpduSequenceCnt;
    LPP_EPDU_STRU                   astEpduArray[LPP_MAX_EPDU_NUM];
}LPP_EPDU_REQ_CAP_STRU;

/*******************************************************************************
 结构名    : LPP_ECID_REQ_CAP_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
/*协议里此结构为空*/
        VOS_UINT32      bitOpEcidReqCapExt:1;
        VOS_UINT32      bitOpSpare:31;
}LPP_ECID_REQ_CAP_STRU;

/*******************************************************************************
 结构名    : LPP_OTDOA_REQ_CAP_STRU
 结构说明  :协议里此结构为空
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
/*协议里此结构为空*/
        VOS_UINT32      bitOpOtdoaReqCapExt:1;
        VOS_UINT32      bitOpSpare:31;

        VOS_UINT32      ulRes;
}LPP_OTDOA_REQ_CAP_STRU;

/*******************************************************************************
 结构名    : LPP_COMMON_IES_REQ_CAP_STRU
 结构说明  :协议里此结构为空
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
/*协议里此结构为空*/
    VOS_UINT32          bitOpCommonIEsReqCapabilitiesExt:1;
    VOS_UINT32          bitOpSpare:31;
}LPP_COMMON_IES_REQ_CAP_STRU;

/*******************************************************************************
 结构名    : LPP_REQUEST_CAPABILITIES_R9_IES_STRU
 结构说明  :RequestCapabilities-r9-IEs
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    RequestCapabilities-r9-IEs ::= SEQUENCE {
        commonIEsRequestCapabilities        CommonIEsRequestCapabilities        OPTIONAL,   -- Need ON
        a-gnss-RequestCapabilities          A-GNSS-RequestCapabilities          OPTIONAL,   -- Need ON
        otdoa-RequestCapabilities           OTDOA-RequestCapabilities           OPTIONAL,   -- Need ON
        ecid-RequestCapabilities            ECID-RequestCapabilities            OPTIONAL,   -- Need ON
        epdu-RequestCapabilities            EPDU-Sequence                       OPTIONAL,   -- Need ON
        ...
    }
    */
    VOS_UINT32                          bitOpLPPReqCapaabilitiesExt:1;
    VOS_UINT32                          bitOpCommonIEsRequestCapabilities:1;
    VOS_UINT32                          bitOpAGNSSRequestCapabilities:1;
    VOS_UINT32                          bitOpOTDOARequestCapabilities:1;
    VOS_UINT32                          bitOpECIDRequestCapabilities:1;
    VOS_UINT32                          bitOpEPDUSequence:1;
    VOS_UINT32                          bitOpSpare:26;

    LPP_COMMON_IES_REQ_CAP_STRU         stCommonIEsRequestCapabilities;
    LPP_AGNSS_REQ_CAP_STRU              stAGNSSRequestCapabilities;
    LPP_OTDOA_REQ_CAP_STRU              stOTDOARequestCapabilities;
    LPP_ECID_REQ_CAP_STRU               stECIDRequestCapabilities;
    LPP_EPDU_REQ_CAP_STRU               stEPDURequestCapabilities;
}LPP_REQUEST_CAPABILITIES_R9_IES_STRU;

/*******************************************************************************
 结构名    : LPP_CRITI_EXT_REQUEST_CAPABILITIES_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                          ulChoice;

    #define         LPP_C1_CRITI_EXT_REQUEST_CAPABILITIES_R9_CHOSEN              0
    #define         LPP_SPARE3_C1_CRITI_EXT_REQUEST_CAPABILITIES_CHOSEN          1
    #define         LPP_SPARE2_C1_CRITI_EXT_REQUEST_CAPABILITIES_CHOSEN          2
    #define         LPP_SPARE1_C1_CRITI_EXT_REQUEST_CAPABILITIES_CHOSEN          3

    union
    {
        LPP_REQUEST_CAPABILITIES_R9_IES_STRU            stRequestCapabilitiesR9;
        VOS_UINT8                                       ucSpare3;
        VOS_UINT8                                       ucSpare2;
        VOS_UINT8                                       ucSpare1;
    }u;
}LPP_CRITI_EXT_REQUEST_CAPABILITIES_STRU;

/*******************************************************************************
 结构名    : LPP_MESSAGE_REQUEST_CAPABILITIES_STRU
 结构说明  :RequestCapabilities
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    RequestCapabilities ::= SEQUENCE {
        criticalExtensions      CHOICE {
            c1                      CHOICE {
                requestCapabilities-r9      RequestCapabilities-r9-IEs,
                spare3 NULL, spare2 NULL, spare1 NULL
            },
            criticalExtensionsFuture    SEQUENCE {}
        }
    }
    */
    VOS_UINT32                                          ulChoice;

    #define           LPP_C1_CRITI_EXT_REQUEST_CAPABILITIES_CHOSEN        0
    #define           LPP_CRITI_EXT_FUTURE_REQUEST_CAPABILITIES_CHOSEN    1

    union
    {
       LPP_CRITI_EXT_REQUEST_CAPABILITIES_STRU          stC1;
       VOS_UINT8                                        ucCritiExtFuture;
    }u;
}LPP_MESSAGE_REQUEST_CAPABILITIES_STRU;

/*******************************************************************************
 结构名    : LPP_SUPPORT_MESSAGE_BODY_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                      ulChoice;

    #define         LPP_SUPPORT_MESSAGE_BODY_REQUEST_CAPABILITIES_CHOSEN                0
    #define         LPP_SUPPORT_MESSAGE_BODY_PROVIDE_CAPABILITIES_CHOSEN                1
    #define         LPP_SUPPORT_MESSAGE_BODY_PEQUEST_ASSISTANCE_DATA_CHOSEN             2
    #define         LPP_SUPPORT_MESSAGE_BODY_PROVIDE_ASSISTANCE_DATA_CHOSEN             3
    #define         LPP_SUPPORT_MESSAGE_BODY_REQUEST_LOCATION_INFO_CHOSEN               4
    #define         LPP_SUPPORT_MESSAGE_BODY_PROVIDE_LOCATION_INFO_CHOSEN               5
    #define         LPP_SUPPORT_MESSAGE_BODY_ABORT_CHOSEN                               6
    #define         LPP_SUPPORT_MESSAGE_BODY_ERROR_CHOSEN                               7
    #define         LPP_SUPPORT_MESSAGE_BODY_SPARE7_CHOSEN                              8
    #define         LPP_SUPPORT_MESSAGE_BODY_SPARE6_CHOSEN                              9
    #define         LPP_SUPPORT_MESSAGE_BODY_SPARE5_CHOSEN                              10
    #define         LPP_SUPPORT_MESSAGE_BODY_SPARE4_CHOSEN                              11
    #define         LPP_SUPPORT_MESSAGE_BODY_SPARE3_CHOSEN                              12
    #define         LPP_SUPPORT_MESSAGE_BODY_SPARE2_CHOSEN                              13
    #define         LPP_SUPPORT_MESSAGE_BODY_SPARE1_CHOSEN                              14
    #define         LPP_SUPPORT_MESSAGE_BODY_SPARE0_CHOSEN                              15

    union
    {
        LPP_MESSAGE_REQUEST_CAPABILITIES_STRU       stRequestCapabilities;
        LPP_MESSAGE_PROVIDE_CAPABILITIES_STRU       stProvideCapabilities;
        LPP_MESSAGE_REQUEST_ASSIST_DATA_STRU        stRequestAssistanceData;
        LPP_MESSAGE_PROVIDE_ASSIST_DATA_STRU        stProvideAssistanceData;
        LPP_MESSAGE_REQUEST_LOCATION_INFO_STRU      stRequestLocationInformation;
        LPP_MESSAGE_PROVIDE_LOCATION_INFO_STRU      stProvideLocationInformation;
        LPP_MESSAGE_ABORT_STRU                      stAbort;
        LPP_MESSAGE_ERROR_STRU                      stError;
        VOS_UINT8                                   ucSpare7;
        VOS_UINT8                                   ucSpare6;
        VOS_UINT8                                   ucSpare5;
        VOS_UINT8                                   ucSpare4;
        VOS_UINT8                                   ucSpare3;
        VOS_UINT8                                   ucSpare2;
        VOS_UINT8                                   ucSpare1;
        VOS_UINT8                                   ucSpare0;
    }u;
}LPP_SUPPORT_MESSAGE_BODY_STRU;

/*******************************************************************************
 结构名    : LPP_MESSAGE_BODY_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                              ulChoice;

    #define             LPP_C1_MESSAGE_BODY_CHOSEN            0
    #define             LPP_C1_MESSAGE_CLASS_EXTENSION        1

    union
    {
        LPP_SUPPORT_MESSAGE_BODY_STRU       stC1;
        VOS_UINT8                           ucMessageClassExtension;
    }u;

}LPP_MESSAGE_BODY_STRU;


/*******************************************************************************
 结构名    : LPP_MESSAGE_BODY_STRU
 结构说明  :LPP_MESSAGE_STRU
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                              bitOpLppTransactionId:1;
    VOS_UINT32                              bitOpSequenceNumber:1;
    VOS_UINT32                              bitOpAcknowledgement:1;
    VOS_UINT32                              bitOpLppMessageBody:1;
    VOS_UINT32                              bitOpSpare:28;

    LPP_TRANSACTION_ID_STRU                 stTransactionId;
    VOS_BOOL                                bEndTransaction;
    LPP_SEQUENCE_NUMBER_STRU                stSequenceNumber;
    LPP_ACKNOWLEDGEMENT_STRU                stAcknowledgement;
    LPP_MESSAGE_BODY_STRU                   stLppMessageBody;
} LPP_MESSAGE_STRU;


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
 #pragma pack(pop)
#endif


#ifdef __cplusplus
#if __cplusplus

}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif

