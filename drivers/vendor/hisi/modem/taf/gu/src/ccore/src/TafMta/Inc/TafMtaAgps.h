/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMtaProcAgps.h
  版 本 号   : 初稿
  作    者   : 闫志吉
  生成日期   : 2012年6月27日
  最近修改   :
  功能描述   : MTA模块与其它模块信息交互处理函数声明
  函数列表   :
  修改历史   :
  1.日    期   : 2012年6月27日
    作    者   : Y00213812
    修改内容   : A-GPS项目新增

******************************************************************************/

#ifndef __TAFMTAPROCAGPS_H__
#define __TAFMTAPROCAGPS_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "AgpsParaDef.h"
#include "MtaRrcInterface.h"
#include "AtMtaInterface.h"
#include "TafMtaCtx.h"
#include "XmlComm.h"

/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
#include "TafSdcCtx.h"
/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

#include "MtaMtcInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* AGPS根节点定义 */
#define MTA_AGPS_LABEL_POS                                  "pos"
#define MTA_AGPS_LABEL_POS_END                              "</pos"

/* <location>的节点名宏定义 */
#define MTA_AGPS_LABEL_LOCATION                             "location"
#define MTA_AGPS_LABEL_LOCATION_PARAMENTERS                 "location_parameters"
#define MTA_AGPS_LABEL_TIME_OF_FIX                          "time_of_fix"
#define MTA_AGPS_LABEL_SHAPE_DATA                           "shape_data"
#define MTA_AGPS_LABEL_TIME                                 "time"
#define MTA_AGPS_LABEL_DIRECTION                            "direction"
#define MTA_AGPS_LABEL_ELLIPSOID_POINT                      "ellipsoid_point"
#define MTA_AGPS_LABEL_ELLIPSOID_POINT_UNCERT_CIRCLE        "ellipsoid_point_uncert_circle"
#define MTA_AGPS_LABEL_ELLIPSOID_POINT_UNCERT_ELLIPSE       "ellipsoid_point_uncert_ellipse"
#define MTA_AGPS_LABEL_POLYGON                              "polygon"
#define MTA_AGPS_LABEL_ELLIPSOID_POINT_ALT                  "ellipsoid_point_alt"
#define MTA_AGPS_LABEL_ELLIPSOID_POINT_ALT_UNCERTELLIPSE    "ellipsoid_point_alt_uncertellipse"
#define MTA_AGPS_LABEL_ELLIPS_ARC                           "ellips_arc"

#define MTA_AGPS_LABEL_COORDINATE                           "coordinate"
#define MTA_AGPS_LABEL_LATITUDE                             "latitude"
#define MTA_AGPS_LABEL_LONGITUDE                            "longitude"
#define MTA_AGPS_LABEL_NORTH                                "north"
#define MTA_AGPS_LABEL_DEGREES                              "degrees"
#define MTA_AGPS_LABEL_UNCERT_CIRCLE                        "uncert_circle"
#define MTA_AGPS_LABEL_UNCERT_ELLIPSE                       "uncert_ellipse"

#define MTA_AGPS_LABEL_UNCERT_SEMI_MAJOR                    "uncert_semi_major"
#define MTA_AGPS_LABEL_UNCERT_SEMI_MINOR                    "uncert_semi_minor"
#define MTA_AGPS_LABEL_ORIENT_MAJOR                         "orient_major"
#define MTA_AGPS_LABEL_CONFIDENCE                           "confidence"

#define MTA_AGPS_LABEL_ALTITUDE                             "altitude"
#define MTA_AGPS_LABEL_HEIGHT_ABOVE_SURFACE                 "height_above_surface"
#define MTA_AGPS_LABEL_HEIGHT                               "height"

#define MTA_AGPS_LABEL_UNCERT_ALT                           "uncert_alt"

#define MTA_AGPS_LABEL_INNER_RAD                            "inner_rad"
#define MTA_AGPS_LABEL_UNCERT_RAD                           "uncert_rad"
#define MTA_AGPS_LABEL_OFFSET_ANGLE                         "offset_angle"
#define MTA_AGPS_LABEL_INCLUDED_ANGLE                       "included_angle"


/* <assist_data>的节点名宏定义 */
#define MTA_AGPS_LABEL_ASSIST_DATA                          "assist_data"
#define MTA_AGPS_LABEL_GPS_ASSIST                           "GPS_assist"
#define MTA_AGPS_LABEL_STATUS_HEALTH                        "status_health"
#define MTA_AGPS_LABEL_BTS_CLOCK_DRIFT                      "BTS_clock_drift"
#define MTA_AGPS_LABEL_REF_TIME                             "ref_time"
#define MTA_AGPS_LABEL_DGPS_CORRECTIONS                     "DGPS_corrections"
#define MTA_AGPS_LABEL_IODE_UPPER_CASE                      "IODE"
#define MTA_AGPS_LABEL_UDRE                                 "UDRE"
#define MTA_AGPS_LABEL_PRC                                  "PRC"
#define MTA_AGPS_LABEL_RRC                                  "RRC"
#define MTA_AGPS_LABEL_DELTA_PRC2                           "delta_PRC2"
#define MTA_AGPS_LABEL_DELTA_RRC2                           "delta_RRC2"
#define MTA_AGPS_LABEL_NAV_MODEL_ELEM                       "nav_model_elem"
#define MTA_AGPS_LABEL_SAT_STATUS                           "sat_status"
#define MTA_AGPS_LABEL_EPHEM_AND_CLOCK                      "ephem_and_clock"
#define MTA_AGPS_LABEL_L2_CODE                              "l2_code"
#define MTA_AGPS_LABEL_URA                                  "ura"
#define MTA_AGPS_LABEL_SV_HEALTH                            "sv_health"
#define MTA_AGPS_LABEL_IODC                                 "iodc"
#define MTA_AGPS_LABEL_L2P_FLAG                             "l2p_flag"
#define MTA_AGPS_LABEL_ESR1                                 "esr1"
#define MTA_AGPS_LABEL_ESR2                                 "esr2"
#define MTA_AGPS_LABEL_ESR3                                 "esr3"
#define MTA_AGPS_LABEL_ESR4                                 "esr4"
#define MTA_AGPS_LABEL_TGD                                  "tgd"
#define MTA_AGPS_LABEL_TOC                                  "toc"
#define MTA_AGPS_LABEL_AF2                                  "af2"
#define MTA_AGPS_LABEL_AF1                                  "af1"
#define MTA_AGPS_LABEL_AF0                                  "af0"
#define MTA_AGPS_LABEL_CRS                                  "crs"
#define MTA_AGPS_LABEL_DELTA_N                              "delta_n"
#define MTA_AGPS_LABEL_M0                                   "m0"
#define MTA_AGPS_LABEL_CUC                                  "cuc"
#define MTA_AGPS_LABEL_ECC                                  "ecc"
#define MTA_AGPS_LABEL_CUS                                  "cus"
#define MTA_AGPS_LABEL_POWER_HALF                           "power_half"
#define MTA_AGPS_LABEL_TOE                                  "toe"
#define MTA_AGPS_LABEL_FIT_FLAG                             "fit_flag"
#define MTA_AGPS_LABEL_AODA                                 "aoda"
#define MTA_AGPS_LABEL_CIC                                  "cic"
#define MTA_AGPS_LABEL_OMEGA0                               "omega0"
#define MTA_AGPS_LABEL_CIS                                  "cis"
#define MTA_AGPS_LABEL_I0                                   "i0"
#define MTA_AGPS_LABEL_CRC                                  "crc"
#define MTA_AGPS_LABEL_OMEGA                                "omega"
#define MTA_AGPS_LABEL_OMEGA_DOT                            "omega_dot"
#define MTA_AGPS_LABEL_IDOT                                 "idot"
#define MTA_AGPS_LABEL_ALFA0                                "alfa0"
#define MTA_AGPS_LABEL_ALFA1                                "alfa1"
#define MTA_AGPS_LABEL_ALFA2                                "alfa2"
#define MTA_AGPS_LABEL_ALFA3                                "alfa3"
#define MTA_AGPS_LABEL_BETA0                                "beta0"
#define MTA_AGPS_LABEL_BETA1                                "beta1"
#define MTA_AGPS_LABEL_BETA2                                "beta2"
#define MTA_AGPS_LABEL_BETA3                                "beta3"

/* <!ELEMENT UTC_model (a1,a0,tot,wnt,dtls,wnlsf,dn,dtlsf)>*/
#define MTA_AGPS_LABEL_A1                                   "a1"
#define MTA_AGPS_LABEL_A0                                   "a0"
#define MTA_AGPS_LABEL_TOT                                  "tot"
#define MTA_AGPS_LABEL_WNT                                  "wnt"
#define MTA_AGPS_LABEL_DTLS                                 "dtls"
#define MTA_AGPS_LABEL_WNLSF                                "wnlsf"
#define MTA_AGPS_LABEL_DN                                   "dn"
#define MTA_AGPS_LABEL_DTLSF                                "dtlsf"

#define MTA_AGPS_LABEL_IONOSPHERIC_MODEL                    "ionospheric_model"
#define MTA_AGPS_LABEL_UTC_MODEL                            "UTC_model"
#define MTA_AGPS_LABEL_ALMANAC                              "almanac"
#define MTA_AGPS_LABEL_WNA                                  "wna"
#define MTA_AGPS_LABEL_ALM_ELEM                             "alm_elem"
#define MTA_AGPS_LABEL_DATA_ID                              "data_id"
#define MTA_AGPS_LABEL_ALM_ECC                              "alm_ecc"
#define MTA_AGPS_LABEL_ALM_TOA                              "alm_toa"
#define MTA_AGPS_LABEL_ALM_KSII                             "alm_ksii"
#define MTA_AGPS_LABEL_ALM_OMEGA_DOT                        "alm_omega_dot"
#define MTA_AGPS_LABEL_ALM_SV_HEALTH                        "alm_sv_health"
#define MTA_AGPS_LABEL_ALM_POWER_HALF                       "alm_power_half"
#define MTA_AGPS_LABEL_ALM_OMEGA0                           "alm_omega0"
#define MTA_AGPS_LABEL_ALM_OMEGA                            "alm_omega"
#define MTA_AGPS_LABEL_ALM_M0                               "alm_m0"
#define MTA_AGPS_LABEL_ALM_AF0                              "alm_af0"
#define MTA_AGPS_LABEL_ALM_AF1                              "alm_af1"
#define MTA_AGPS_LABEL_ACPU_ASSIST                          "acqu_assist"
#define MTA_AGPS_LABEL_SAT_INFO                             "sat_info"
#define MTA_AGPS_LABEL_DOPL0                                "dopl0"
#define MTA_AGPS_LABEL_DOPL_EXTRA                           "dopl_extra"
#define MTA_AGPS_LABEL_DOPL1                                "dopl1"
#define MTA_AGPS_LABEL_DOPL1_UNCERT                         "dopl1_uncert"
#define MTA_AGPS_LABEL_CODE_PH                              "code_ph"
#define MTA_AGPS_LABEL_CODE_PH_INT                          "code_ph_int"
#define MTA_AGPS_LABEL_GPS_BITNO                            "GPS_bitno"
#define MTA_AGPS_LABEL_SRCH_W                               "srch_w"
#define MTA_AGPS_LABEL_AZ_EL                                "az_el"
#define MTA_AGPS_LABEL_AZ                                   "az"
#define MTA_AGPS_LABEL_ELEV                                 "elev"
#define MTA_AGPS_LABEL_GPS_RT_INTEGRITY                     "GPS_rt_integrity"
#define MTA_AGPS_LABEL_GPS_TIME                             "GPS_time"
#define MTA_AGPS_LABEL_GPS_TOW_MSEC                         "GPS_TOW_msec"
#define MTA_AGPS_LABEL_GPS_WEEK                             "GPS_week"
#define MTA_AGPS_LABEL_GSM_TIME                             "GSM_time"
#define MTA_AGPS_LABEL_FRAME_NUMBER                         "frame_number"
#define MTA_AGPS_LABEL_TIME_SLOT_NUMBER                     "time_slot_number"
#define MTA_AGPS_LABEL_BIT_NUMBER                           "bit_number"
#define MTA_AGPS_LABEL_BCCH_CARRIER                         "BCCH_carrier"
#define MTA_AGPS_LABEL_BSIC                                 "BSIC"
#define MTA_AGPS_LABEL_GPS_TOW_ASSIST                       "GPS_TOW_assist"
#define MTA_AGPS_LABEL_TLM_WORD                             "tlm_word"
#define MTA_AGPS_LABEL_ANTI_SP                              "anti_sp"
#define MTA_AGPS_LABEL_ALERT                                "alert"
#define MTA_AGPS_LABEL_TLM_RES                              "tlm_res"


/* <GPS_meas>的节点名宏定义 */
#define MTA_AGPS_LABEL_GPS_MEAS                             "GPS_meas"
#define MTA_AGPS_LABEL_REF_TIME_ONLY                        "ref_time_only"
#define MTA_AGPS_LABEL_TOW_MSEC                             "tow_msec"
#define MTA_AGPS_LABEL_MEAS_PARAMS                          "meas_params"
#define MTA_AGPS_LABEL_NAV_ADDL_DATA                        "nav_addl_data"
#define MTA_AGPS_LABEL_SAT_ID                               "sat_id"
#define MTA_AGPS_LABEL_CARR2_NOISE                          "carr2_noise"
#define MTA_AGPS_LABEL_DOP1                                 "dopl"
#define MTA_AGPS_LABEL_WHOLE_CHIPS                          "whole_chips"
#define MTA_AGPS_LABEL_FRACT_CHIPS                          "fract_chips"
#define MTA_AGPS_LABEL_MULTI_PATH                           "multi_path"
#define MTA_AGPS_LABEL_PSR_RMS_ERR                          "psr_rms_err"

/* <pos_err>的节点名宏定义 */
#define MTA_AGPS_LABEL_POS_ERR                              "pos_err"
#define MTA_AGPS_LABEL_ERR_REASON                           "err_reason"
#define MTA_AGPS_LABEL_GPS_ASSIST_REQ                       "GPS_assist_req"
#define MTA_AGPS_LABEL_GPS_TOE                              "GPS_toe"
#define MTA_AGPS_LABEL_TTOE_LIMIT                           "ttoe_limit"
#define MTA_AGPS_LABEL_ADDL_REQ_SAT                         "addl_req_sat"
#define MTA_AGPS_LABEL_IODE_LOWER_CASE                      "iode"

/* <pos_meas>的节点名宏定义 */
#define MTA_AGPS_LABEL_POS_MEAS                             "pos_meas"
#define MTA_AGPS_LABEL_MEAS_ABORT                           "meas_abort"
#define MTA_AGPS_LABEL_RRLP_MEAS                            "RRLP_meas"
#define MTA_AGPS_LABEL_RRLP_POS_INSTRUCT                    "RRLP_pos_instruct"
#define MTA_AGPS_LABEL_RRLP_METHOD_TYPE                     "RRLP_method_type"
#define MTA_AGPS_LABEL_MS_ASSISTED                          "ms_assisted"
#define MTA_AGPS_LABEL_METHOD_ACCURACY                      "method_accuracy"
#define MTA_AGPS_LABEL_MS_ASSISTED_NO_ACCURACY              "ms_assisted_no_accuracy"
#define MTA_AGPS_LABEL_MS_BASED                             "ms_based"
#define MTA_AGPS_LABEL_MS_BASED_PREF                        "ms_based_pref"
#define MTA_AGPS_LABEL_MS_ASSISTED_PREF                     "ms_assisted_pref"
#define MTA_AGPS_LABEL_RRLP_METHOD                          "RRLP_method"
#define MTA_AGPS_LABEL_RESP_TIME_SECONDS                    "resp_time_seconds"
#define MTA_AGPS_LABEL_MULT_SETS                            "mult_sets"
#define MTA_AGPS_LABEL_RRC_MEAS                             "RRC_meas"
#define MTA_AGPS_LABEL_REP_QUANT                            "rep_quant"
#define MTA_AGPS_LABEL_RRC_METHOD_TYPE                      "RRC_method_type"
#define MTA_AGPS_LABEL_RRC_METHOD                           "RRC_method"
#define MTA_AGPS_LABEL_HOR_ACC                              "hor_acc"
#define MTA_AGPS_LABEL_VERT_ACC                             "vert_acc"
#define MTA_AGPS_LABEL_REP_CRIT                             "rep_crit"
#define MTA_AGPS_LABEL_NO_REP                               "no_rep"
#define MTA_AGPS_LABEL_EVENT_REP_CRIT                       "event_rep_crit"
#define MTA_AGPS_LABEL_EVENT_PAR                            "event_par"
#define MTA_AGPS_LABEL_REP_AMOUNT                           "rep_amount"
#define MTA_AGPS_LABEL_MEAS_INTERVAL                        "meas_interval"
#define MTA_AGPS_LABEL_EVENT_SPECIFIC_INFO                  "event_specific_info"
#define MTA_AGPS_LABEL_TR_POS_CHG                           "tr_pos_chg"
#define MTA_AGPS_LABEL_TR_SFN_SFN_CHG                       "tr_SFN_SFN_chg"
#define MTA_AGPS_LABEL_TR_SFN_GPS_TOW                       "tr_SFN_GPS_TOW"

#define MTA_AGPS_LABEL_PERIOD_REP_CRIT                      "period_rep_crit"


/* 属性名宏定义 */
#define MTA_AGPS_ATTRIB_LITERAL                             "literal"
#define MTA_AGPS_ATTRIB_ALM_REQ                             "alm_req"
#define MTA_AGPS_ATTRIB_UTC_MODEM_REQ                       "UTC_model_req"
#define MTA_AGPS_ATTRIB_ION_REQ                             "ion_req"
#define MTA_AGPS_ATTRIB_NAV_MODEL_REQ                       "nav_model_req"
#define MTA_AGPS_ATTRIB_DGPS_CORR_REQ                       "DGPS_corr_req"
#define MTA_AGPS_ATTRIB_REF_LOC_REQ                         "ref_loc_req"
#define MTA_AGPS_ATTRIB_REF_TIME_REQ                        "ref_time_req"
#define MTA_AGPS_ATTRIB_AQU_ASSIST_REQ                      "aqu_assist_req"
#define MTA_AGPS_ATTRIB_RT_INTEGR_REQ                       "rt_integr_req"

#define MTA_AGPS_ATTRIB_GPS_TIMING_OF_CELL_WANTED           "gps_timing_of_cell_wanted"
#define MTA_AGPS_ATTRIB_ADDL_ASSIST_DATA_REQ                "addl_assist_data_req"

#define MTA_AGPS_ATTRIB_REPORT_FIRST_FIX                    "report_first_fix"

#define MTA_AGPS_ATTRIB_REP_AMOUNT                          "rep_amount"
#define MTA_AGPS_ATTRIB_REP_INTERVAL_LONG                   "rep_interval_long"


/* 属性值宏定义 */
#define MTA_AGPS_ATTRIB_VALUE_NOT_MEASURED                  "not_measured"
#define MTA_AGPS_ATTRIB_VALUE_NOT_LOW                       "low"
#define MTA_AGPS_ATTRIB_VALUE_NOT_MEDIA                     "medium"
#define MTA_AGPS_ATTRIB_VALUE_NOT_HIGH                      "high"

#define MTA_AGPS_ATTRIB_VALUE_UNDEFINED_ERROR               "undefined_error"
#define MTA_AGPS_ATTRIB_VALUE_NOT_ENOUGH_GPS_SATELLITES     "not_enough_gps_satellites"
#define MTA_AGPS_ATTRIB_VALUE_GPS_ASSIST_DATA_MISSING       "gps_assist_data_missing"

#define MTA_AGPS_ATTRIB_VALUE_TRUE                          "true"
#define MTA_AGPS_ATTRIB_VALUE_FALSE                         "false"

#define MTA_AGPS_ATTRIB_VALUE_GPS                           "gps"
#define MTA_AGPS_ATTRIB_VALUE_MULTIPLE                      "multiple"
#define MTA_AGPS_ATTRIB_VALUE_ONE                           "one"

#define MTA_AGPS_ATTRIB_VALUE_UE_ASSISTED                   "ue_assisted"
#define MTA_AGPS_ATTRIB_VALUE_UE_BASED                      "ue_based"
#define MTA_AGPS_ATTRIB_VALUE_UE_BASED_PREF                 "ue_based_pref"
#define MTA_AGPS_ATTRIB_VALUE_UE_ASSISTED_PREF              "ue_assisted_pref"
#define MTA_AGPS_ATTRIB_VALUE_OTDOA                         "otdoa"
#define MTA_AGPS_ATTRIB_VALUE_OTDOAORGPS                    "otdoaOrGPS"
#define MTA_AGPS_ATTRIB_VALUE_CELLID                        "cellID"

#define MTA_AGPS_ATTRIB_VALUE_NS_NN_U                       "NS_NN-U"
#define MTA_AGPS_ATTRIB_VALUE_ES_NN_U                       "ES_NN-U"
#define MTA_AGPS_ATTRIB_VALUE_NS_NN                         "NS_NN"
#define MTA_AGPS_ATTRIB_VALUE_ES_SN                         "ES_SN"
#define MTA_AGPS_ATTRIB_VALUE_REVD                          "REVD"

#define MTA_AGPS_ATTRIB_VALUE_RA1                           "ra1"
#define MTA_AGPS_ATTRIB_VALUE_RA2                           "ra2"
#define MTA_AGPS_ATTRIB_VALUE_RA4                           "ra4"
#define MTA_AGPS_ATTRIB_VALUE_RA8                           "ra8"
#define MTA_AGPS_ATTRIB_VALUE_RA16                          "ra16"
#define MTA_AGPS_ATTRIB_VALUE_RA32                          "ra32"
#define MTA_AGPS_ATTRIB_VALUE_RA64                          "ra64"
#define MTA_AGPS_ATTRIB_VALUE_RA_INFINITY                   "ra-Infinity"

#define MTA_AGPS_ATTRIB_VALUE_E5                            "e5"
#define MTA_AGPS_ATTRIB_VALUE_E15                           "e15"
#define MTA_AGPS_ATTRIB_VALUE_E60                           "e60"
#define MTA_AGPS_ATTRIB_VALUE_E300                          "e300"
#define MTA_AGPS_ATTRIB_VALUE_E900                          "e900"
#define MTA_AGPS_ATTRIB_VALUE_E1800                         "e1800"
#define MTA_AGPS_ATTRIB_VALUE_E3600                         "e3600"
#define MTA_AGPS_ATTRIB_VALUE_E7200                         "e7200"

#define MTA_AGPS_ATTRIB_VALUE_PC10                          "pc10"
#define MTA_AGPS_ATTRIB_VALUE_PC20                          "pc20"
#define MTA_AGPS_ATTRIB_VALUE_PC30                          "pc30"
#define MTA_AGPS_ATTRIB_VALUE_PC40                          "pc40"
#define MTA_AGPS_ATTRIB_VALUE_PC50                          "pc50"
#define MTA_AGPS_ATTRIB_VALUE_PC100                         "pc100"
#define MTA_AGPS_ATTRIB_VALUE_PC200                         "pc200"
#define MTA_AGPS_ATTRIB_VALUE_PC300                         "pc300"
#define MTA_AGPS_ATTRIB_VALUE_PC500                         "pc500"
#define MTA_AGPS_ATTRIB_VALUE_PC1000                        "pc1000"
#define MTA_AGPS_ATTRIB_VALUE_PC2000                        "pc2000"
#define MTA_AGPS_ATTRIB_VALUE_PC5000                        "pc5000"
#define MTA_AGPS_ATTRIB_VALUE_PC10000                       "pc10000"
#define MTA_AGPS_ATTRIB_VALUE_PC20000                       "pc20000"
#define MTA_AGPS_ATTRIB_VALUE_PC50000                       "pc50000"
#define MTA_AGPS_ATTRIB_VALUE_PC100000                      "pc100000"

#define MTA_AGPS_ATTRIB_VALUE_C0_25                         "c0-25"
#define MTA_AGPS_ATTRIB_VALUE_C0_5                          "c0-5"
#define MTA_AGPS_ATTRIB_VALUE_C1                            "c1"
#define MTA_AGPS_ATTRIB_VALUE_C2                            "c2"
#define MTA_AGPS_ATTRIB_VALUE_C3                            "c3"
#define MTA_AGPS_ATTRIB_VALUE_C4                            "c4"
#define MTA_AGPS_ATTRIB_VALUE_C5                            "c5"
#define MTA_AGPS_ATTRIB_VALUE_C10                           "c10"
#define MTA_AGPS_ATTRIB_VALUE_C20                           "c20"
#define MTA_AGPS_ATTRIB_VALUE_C50                           "c50"
#define MTA_AGPS_ATTRIB_VALUE_C100                          "c100"
#define MTA_AGPS_ATTRIB_VALUE_C200                          "c200"
#define MTA_AGPS_ATTRIB_VALUE_C500                          "c500"
#define MTA_AGPS_ATTRIB_VALUE_C1000                         "c1000"
#define MTA_AGPS_ATTRIB_VALUE_C2000                         "c2000"
#define MTA_AGPS_ATTRIB_VALUE_C5000                         "c5000"

#define MTA_AGPS_ATTRIB_VALUE_MS1                           "ms1"
#define MTA_AGPS_ATTRIB_VALUE_MS2                           "ms2"
#define MTA_AGPS_ATTRIB_VALUE_MS3                           "ms3"
#define MTA_AGPS_ATTRIB_VALUE_MS5                           "ms5"
#define MTA_AGPS_ATTRIB_VALUE_MS10                          "ms10"
#define MTA_AGPS_ATTRIB_VALUE_MS20                          "ms20"
#define MTA_AGPS_ATTRIB_VALUE_MS50                          "ms50"
#define MTA_AGPS_ATTRIB_VALUE_MS100                         "ms100"

#define MTA_AGPS_ATTRIB_VALUE_RIL0                          "ril0"
#define MTA_AGPS_ATTRIB_VALUE_RIL0_25                       "ril0-25"
#define MTA_AGPS_ATTRIB_VALUE_RIL0_5                        "ril0-5"
#define MTA_AGPS_ATTRIB_VALUE_RIL1                          "ril1"
#define MTA_AGPS_ATTRIB_VALUE_RIL2                          "ril2"
#define MTA_AGPS_ATTRIB_VALUE_RIL3                          "ril3"
#define MTA_AGPS_ATTRIB_VALUE_RIL4                          "ril4"
#define MTA_AGPS_ATTRIB_VALUE_RIL6                          "ril6"
#define MTA_AGPS_ATTRIB_VALUE_RIL8                          "ril8"
#define MTA_AGPS_ATTRIB_VALUE_RIL12                         "ril12"
#define MTA_AGPS_ATTRIB_VALUE_RIL16                         "ril16"
#define MTA_AGPS_ATTRIB_VALUE_RIL20                         "ril20"
#define MTA_AGPS_ATTRIB_VALUE_RIL24                         "ril24"
#define MTA_AGPS_ATTRIB_VALUE_RIL28                         "ril28"
#define MTA_AGPS_ATTRIB_VALUE_RIL32                         "ril32"
#define MTA_AGPS_ATTRIB_VALUE_RIL64                         "ril64"

#define MTA_AGPS_ATTRIB_VALUE_HZ12_5                        "hz12-5"
#define MTA_AGPS_ATTRIB_VALUE_HZ25                          "hz25"
#define MTA_AGPS_ATTRIB_VALUE_HZ50                          "hz50"
#define MTA_AGPS_ATTRIB_VALUE_HZ100                         "hz100"
#define MTA_AGPS_ATTRIB_VALUE_HZ200                         "hz200"

/* AGPS子节点的个数的公共定义 */
#define MTA_AGPS_XML_NODE_COUNT_1       (1)                 /* 结点个数为1 */
#define MTA_AGPS_XML_NODE_COUNT_2       (2)                 /* 结点个数为2 */
#define MTA_AGPS_XML_NODE_COUNT_3       (3)                 /* 结点个数为3 */

/* AGPS子节点的索引的公共定义 */
#define MTA_AGPS_XML_NODE_INDEX_0       (0)                 /* 索引为0 */

#define MTA_XML_TEXT_MAX_BUFF_SIZE      (8192)              /* XML码流允许接收的最大值 */

/* 填充<GPS_assist>节点中的<DGPS_corrections>和<GPS_rt_integrity>子节点时，所用的偏移*/
#define MTA_AGPS_CVRT_EXTRA_ASSI_DATA_OFFSET                (1)

/* Added by l00198894 for 新增+ECID命令, 2013-12-10, begin */
#define MTA_ECID_CELLINFO_MAX_STRLEN    (2000)              /* 字符串可能最大长度6836，但由于AT通道的限制暂定 */
#define MTA_ECID_CELLINFO_MIN_STRLEN    (10)                /* 单个参数字符串可能最大长度10 */
#define MTA_ECID_UNDEFINED_VALUE        (-1)                /* 该参数不支持时默认填写-1 */
#define MTA_ECID_RSCP_UNDEFINED_VALUE   (-127)              /* WAS查询的CPICH_RSCP参数不支持时默认填写-127 */
#define MTA_ECID_NONE_RAT_STR           "0,NONE:,"
#define MTA_ECID_LRRC_TA_TRANSPARA      (4)                 /* LRRC回复的TA参数转换系数 */
#define MTA_ECID_PLMN_MAX_STR_LEN       (8)                 /* MCC\MNC及结束符字符串最大长度 */
/* Added by l00198894 for 新增+ECID命令, 2013-12-10, end */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
/*****************************************************************************
  5 消息头定义
*****************************************************************************/
/*****************************************************************************
  6 消息定义
*****************************************************************************/
/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/*****************************************************************************
  8 UNION定义
*****************************************************************************/
/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if(FEATURE_ON == FEATURE_AGPS)
extern VOS_UINT32 TAF_MTA_AGPS_FillAddlReqSat(
    XML_COMM_NODE_STRU                 *pstXmlAdditionReqSat,
    AGPS_ADDITION_REQ_SAT_STRU         *pstAdditionReqSat
);
extern VOS_UINT32 TAF_MTA_AGPS_FillAltitude(
    XML_COMM_NODE_STRU                 *pstXmlpstAltitude,
    AGPS_ALTITUDE_STRU                 *pstAltitude
);
extern VOS_UINT32 TAF_MTA_AGPS_FillCoordinate(
    XML_COMM_NODE_STRU                 *pstXmlCoordinate,
    AGPS_COORDINATE_STRU               *pstCoordinate
);
extern VOS_UINT32 TAF_MTA_AGPS_FillEllipPoint(
    XML_COMM_NODE_STRU                 *pstXmlElliPoint,
    AGPS_ELLIP_POINT_STRU              *pstElliPoint
);
extern VOS_UINT32 TAF_MTA_AGPS_FillEllipPointAlt(
    XML_COMM_NODE_STRU                 *pstXmlElliPointAlti,
    AGPS_ELLIP_POINT_ALTI_STRU         *pstElliPointAlti
);
extern VOS_UINT32 TAF_MTA_AGPS_FillEllipPointAltUncertellipse(
    XML_COMM_NODE_STRU                 *pstXmlElliPointAltiEllip,
    AGPS_ELLIP_POINT_ALTI_ELLIP_STRU   *pstElliPointAltiEllip
);
extern VOS_UINT32 TAF_MTA_AGPS_FillEllipPointUncertCircle(
    XML_COMM_NODE_STRU                                    *pstXmlElliPointUncertCircle,
    AGPS_ELLIP_POINT_UNCERT_CIRCLE_STRU                   *pstElliPointUncertCircle
);
extern VOS_UINT32 TAF_MTA_AGPS_FillEllipPointUncertEllipse(
    XML_COMM_NODE_STRU                 *pstXmlElliPointUncertEllip,
    AGPS_ELLIP_POINT_UNCERT_ELLIP_STRU *pstElliPointUncertEllip
);
extern VOS_UINT32 TAF_MTA_AGPS_FillEllipsArc(
    XML_COMM_NODE_STRU                 *pstXmlElliPArc,
    AGPS_ELLIP_ARC_STRU                *pstElliPArc
);
extern VOS_UINT32 TAF_MTA_AGPS_FillGpsAssistReq(
    XML_COMM_NODE_STRU                                     *pstXmlAssistReq,
    AGPS_POSITION_GPS_ADDITION_ASSIST_REQ_STRU             *pstAgpsAssistReq
);
extern VOS_UINT32 TAF_MTA_AGPS_FillGpsMeas(
    XML_COMM_NODE_STRU                 *pstXmlGpsMeasureInfo,
    AGPS_GPS_MEASURE_INFO_STRU         *pstGpsMeasureInfo
);
extern VOS_UINT32 TAF_MTA_AGPS_FillAttributeTrueOrFalse(
    XML_COMM_NODE_ATTRIBUTE_STRU        *pstXmlAttrib,
    VOS_UINT8                           *pucElement
);
extern VOS_UINT32 TAF_MTA_AGPS_FillAlmReqOfGpsAssistReq(
    XML_COMM_NODE_STRU                 *pstXmlAssistReq,
    VOS_UINT8                          *pucAlmReq
);
extern VOS_UINT32 TAF_MTA_AGPS_FillUtcModelReqOfGpsAssistReq(
    XML_COMM_NODE_STRU                 *pstXmlAssistReq,
    VOS_UINT8                          *pucUtcModelReq
);
extern VOS_UINT32 TAF_MTA_AGPS_FillIonReqOfGpsAssistReq(
    XML_COMM_NODE_STRU                 *pstXmlAssistReq,
    VOS_UINT8                          *pucIonReq
);
extern VOS_UINT32 TAF_MTA_AGPS_FillNavModelReqOfGpsAssistReq(
    XML_COMM_NODE_STRU                 *pstXmlAssistReq,
    VOS_UINT8                          *pucNavModelReq
);
extern VOS_UINT32 TAF_MTA_AGPS_FillDgpsCorrReqOfGpsAssistReq(
    XML_COMM_NODE_STRU                 *pstXmlAssistReq,
    VOS_UINT8                          *pucDgpsCorrReq
);
extern VOS_UINT32 TAF_MTA_AGPS_FillRefLocReqOfGpsAssistReq(
    XML_COMM_NODE_STRU                 *pstXmlAssistReq,
    VOS_UINT8                          *pucRefLocReq
);
extern VOS_UINT32 TAF_MTA_AGPS_FillRefTimeReqOfGpsAssistReq(
    XML_COMM_NODE_STRU                 *pstXmlAssistReq,
    VOS_UINT8                          *pucRefTimeReq
);
extern VOS_UINT32 TAF_MTA_AGPS_FillAquAssistReqOfGpsAssistReq(
    XML_COMM_NODE_STRU                 *pstXmlAssistReq,
    VOS_UINT8                          *pucAquAssistReq
);
extern VOS_UINT32 TAF_MTA_AGPS_FillRtIntegrReqOfGpsAssistReq(
    XML_COMM_NODE_STRU                 *pstXmlAssistReq,
    VOS_UINT8                          *pucRtIntegrReq
);
extern VOS_UINT32 TAF_MTA_AGPS_FillLatitude(
    XML_COMM_NODE_STRU                 *pstXmlLatitude,
    AGPS_LATITUDE_STRU                 *pstLatitude
);
extern VOS_UINT32 TAF_MTA_AGPS_FillLocationInfo(
    XML_COMM_NODE_STRU                 *pstXmlLocationInfo,
    AGPS_LOCATION_INFO_STRU            *pstLocationInfo
);
extern VOS_UINT32 TAF_MTA_AGPS_FillLocationPara(
    XML_COMM_NODE_STRU                 *pstXmlLocationPara,
    AGPS_LOCATION_PARA_STRU            *pstLocationPara
);
extern VOS_UINT32 TAF_MTA_AGPS_FillMultiPathOfMeasParams(
    XML_COMM_NODE_STRU                 *pstXmlGpsMeasurePara,
    AGPS_MULTI_PATH_INDIC_ENUM_UINT8   *penMultipathIndic
);
extern VOS_UINT32 TAF_MTA_AGPS_FillMeasParams(
    XML_COMM_NODE_STRU                 *pstXmlGpsMeasurePara,
    AGPS_GPS_MEASURE_PARA_STRU         *pstGpsMeasurePara
);
extern VOS_UINT32 TAF_MTA_AGPS_FillNavAddlData(
    XML_COMM_NODE_STRU                 *pstXmlNavAddData,
    AGPS_NAV_ADD_DATA_STRU             *pstNavAddData
);
extern VOS_UINT32 TAF_MTA_AGPS_FillPosErr(
    XML_COMM_NODE_STRU                 *pstXmlPositionErr,
    AGPS_POSITION_ERR_STRU             *pstPositionErr
);
extern VOS_UINT32 TAF_MTA_AGPS_FillRefTimeOnly(
    XML_COMM_NODE_STRU                 *pstXmlRefTimeOnly,
    AGPS_REF_TIME_ONLY_STRU            *pstRefTimeOnly
);
extern VOS_UINT32 TAF_MTA_AGPS_FillShapData(
    XML_COMM_NODE_STRU                 *pstXmlShapeData,
    AGPS_SHAPE_DATA_STRU               *pstShapeData
);
extern VOS_UINT32 TAF_MTA_AGPS_FillUncertEllipse(
    XML_COMM_NODE_STRU                 *pstXmlUncertEllipse,
    AGPS_UNCERT_ELLIPSE_STRU           *pstUncertEllipse
);

extern VOS_UINT32 TAF_MTA_AGPS_AddNewSignedIntLeafNode(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    XML_COMM_NODE_STRU                 *pstParentNode,
    VOS_CHAR                           *pcLeafNodeLabel,
    VOS_INT32                           lLeafNodeValue);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_CreateANodeAndSetLabel(
    XML_COMM_CTX_STRU                  *pstXmlCtx,
    VOS_CHAR                           *pcNodeLabel);
extern VOS_UINT32 TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    XML_COMM_NODE_STRU                 *pstParentNode,
    VOS_CHAR                           *pcLeafNodeLabel,
    VOS_UINT32                          ulLeafNodeValue );
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertAcquAssist(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_ACQU_ASSIST_STRU              *pstAcquAssist);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertAcquSatInfo(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_ACQU_SAT_INFO_STRU            *pstAcquSatInfo);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertAlmanac(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_ALMANAC_STRU                  *pstAlmanac);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertAltitude(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_ALTITUDE_STRU                 *pstAltitude);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertAssistData(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_ASSIST_DATA_STRU              *pstAssistData);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertAzimuthAndEleva(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_AZIMUTH_AND_ELEVA_STRU        *pstAzimuthAndEleva);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertCoordinate(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_COORDINATE_STRU               *pstCoordinate);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertEllipArc(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_ELLIP_ARC_STRU                *pstEllipArc);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertEllipPoint(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_ELLIP_POINT_STRU              *pstEllipPoint);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertEllipPointAlti(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_ELLIP_POINT_ALTI_STRU         *pstEllipPointAlti);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertEllipPointAltiEllip(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_ELLIP_POINT_ALTI_ELLIP_STRU   *pstEllipPointAltiEllip);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertEllipPointUncertCircle(
    XML_COMM_CTX_STRU                      *pstXmlCommCtx,
    AGPS_ELLIP_POINT_UNCERT_CIRCLE_STRU    *pstEllipPointUncertCircle);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertEllipPointUncertEllip(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_ELLIP_POINT_UNCERT_ELLIP_STRU *pstEllipPointUncertEllip);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertEventPar(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_UE_POS_EVT_PARAM_STRU         *pstUePosEvtParam);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertEventRepCrit(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_UE_POS_EVT_PARAM_LIST_STRU    *pstUePosEvtParamList);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertEventSpecificInfo(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_UE_POS_EVT_SPEC_INFO_STRU     *pstUePosEvtSpecInfo);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertExtraDopplerInfo(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_EXTRA_DOPPLER_INFO_STRU       *pstExtraDopplerInfo);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertGpsAssist(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_GPS_ASSIST_STRU               *pstGpsAssist);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertGpsRealTimeIntegrity(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_BAD_SAT_LIST_STRU             *pstBadSatList);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertGpsTime(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_GPS_TIME_STRU                 *pstGpsTime);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertGpsTowAssist(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_GPS_TOW_ASSIST_STRU           *pstTowAssist);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertGsmTime(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_GSM_TIME_STRU                 *pstGsmTime);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertLatitude(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_LATITUDE_STRU                 *pstLatitude);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertLocationPara(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_LOCATION_PARA_STRU            *pstLocationPara);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertMeasInterval(
    XML_COMM_CTX_STRU                      *pstXmlCommCtx,
    AGPS_UE_POS_EVT_INTERVAL_ENUM_UINT8    *penMeasInterval);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertMeasureReq(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_MEASURE_REQ_STRU              *pstMeasureReq);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertMsAssisted(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    VOS_UINT8                          *pucAccuracy);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertMsAssistedPref(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    VOS_UINT8                          *pucAccuracy);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertMsBased(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    VOS_UINT8                          *pucAccuracy);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertMsBasedPref(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    VOS_UINT8                          *pucAccuracy);
extern VOS_UINT32 TAF_MTA_AGPS_ConvertSatStatusOfNavModelElem(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_NAV_MODEL_ELEM_STRU           *pstNavModelElem,
    XML_COMM_NODE_STRU                 *pstNodeNavModelElem);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertNavModelElem(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_NAV_MODEL_ELEM_STRU           *pstNavModelElem);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertPeriodRepCrit(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_PERIOD_RPTNG_CRTR_STRU        *pstPeriodRptngCrtr);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertPos(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx);
extern VOS_UINT32 TAF_MTA_AGPS_ConvertRrlpMethodOfPositionInstruct(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    XML_COMM_NODE_STRU                 *pstNodePositionInstruct);
extern VOS_UINT32 TAF_MTA_AGPS_ConvertMultSetsOfPositionInstruct(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    XML_COMM_NODE_STRU                 *pstNodePositionInstruct,
    AGPS_MULT_SETS_ENUM_UINT8           enUseMultipleSets);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertPositionInstruct(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_POSITION_INSTRUCT_STRU        *pstPositionInstruct);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRefTime(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_REFERENCE_TIME_STRU           *pstRefTime);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRepAmount(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_UE_POS_RPT_MOUNT_ENUM_UINT8   *penReportAmount);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRepCrit(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_REP_CRIT_STRU                 *pstRepCrit);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRepQuant(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_REP_QUANT_STRU                *pstRepQuant);
extern VOS_UINT32 TAF_MTA_AGPS_ConvertDataIdOfRrcAlmanacSatInfo(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRC_ALMANAC_SAT_INFO_STRU     *pstRrcAlmanacSatInfo,
    XML_COMM_NODE_STRU                 *pstNodeRrcAlmanacSatInfo);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrcAlmanacSatInfo(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRC_ALMANAC_SAT_INFO_STRU     *pstRrcAlmanacSatInfo);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrcEphemClockParam(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRC_EPHEM_CLOCK_PARAM_STRU    *pstRrcEphemClockParam);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrcIonosphericModel(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRC_IONOSPHERIC_MODEL_STRU    *pstRrcIonosphericModel);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrcMeasReq(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRC_MEAS_REQ_STRU             *pstRrcMeaseReq);
extern VOS_UINT32 TAF_MTA_AGPS_AddRepQuantAttribs(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    XML_COMM_NODE_STRU                 *pstNodeRepQuant,
    AGPS_REP_QUANT_STRU                *pstRepQuant);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrcMethod(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_POS_METHOD_ENUM_UINT8         *penPosMethod);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrcMethodType(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_POSITION_TYPE_ENUM_UINT8      *penMethodType);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrcUtcModel(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRC_UTC_MODEL_STRU            *pstRrcUtcModel);
extern VOS_UINT32 TAF_MTA_AGPS_ConvertDataIdOfRrlpAlmanacSatInfo(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRLP_ALMANAC_SAT_INFO_STRU    *pstRrlpAlmanacSatInfo,
    XML_COMM_NODE_STRU                 *pstNodeRrlpAlmanacSatInfo);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrlpAlmanacSatInfo(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRLP_ALMANAC_SAT_INFO_STRU    *pstRrlpAlmanacSatInfo);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrlpEphemClockParam(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRLP_EPHEM_CLOCK_PARAM_STRU   *pstRrlpEphemClockParam);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrlpIonosphericModel(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRLP_IONOSPHERIC_MODEL_STRU   *pstRrlpIonosphericModel);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrlpMeasReq(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRLP_MEAS_REQ_STRU            *pstRrlpMeasReq);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrlpMethodType(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRLP_METHOD_TYPE_STRU         *pstRrlpMethodType);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrlpUtcModel(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRLP_UTC_MODEL_STRU           *pstRrlpUtcModel);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertShapeData(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_SHAPE_DATA_STRU               *pstShapeData);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertTrPosChg(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_THRESHOLD_POSITION_ENUM_UINT8 *penE7a);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertTrSfnGpsTow(
    XML_COMM_CTX_STRU                      *pstXmlCommCtx,
    AGPS_THRESHOLD_SFN_GPS_TOW_ENUM_UINT8  *penE7c);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertTrSfnSfnChg(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_THRESHOLD_SFN_SFN_ENUM_UINT8  *penE7b);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertUncertEllipse(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_UNCERT_ELLIPSE_STRU           *pstUncertEllipse);
extern XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertUpDgpsCorrection(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_UP_DGPS_CORRECTION_STRU       *pstUpDgpsCorrection);

extern VOS_UINT32 TAF_MTA_CheckXmlEnd(
    TAF_MTA_AGPS_CTX_STRU              *pstAgpsCtx);
extern VOS_UINT32 TAF_MTA_MgmtCposTimer(
    VOS_UINT32                          ulTimerFlg);
extern VOS_UINT32 TAF_MTA_FillXmlStru(
    XML_COMM_NODE_STRU                 *pstXmlNode,
    MTA_RRC_POSITION_CNF_STRU          *pstPositionCnf );
extern VOS_UINT32 TAF_MTA_ProcAssistData(
    AGPS_ASSIST_DATA_STRU              *pstAssistData);
extern VOS_VOID TAF_MTA_GetRemainDgpsCorrectionsNodeNum(
    AGPS_GPS_ASSIST_STRU               *pstGpsAssist,
    VOS_UINT32                         *pulRemainDgpsCorrectionNum);
extern VOS_VOID TAF_MTA_GetRemainGpsRtIntegrityNodeNum(
    AGPS_GPS_ASSIST_STRU               *pstGpsAssist,
    VOS_UINT32                         *pulRemainBadSatListBadSatListNum);
extern VOS_UINT32 TAF_MTA_ProcExtraAssistData(
    AGPS_ASSIST_DATA_STRU              *pstAssistData);
extern VOS_UINT32 TAF_MTA_SndAtCposrInd(
    XML_COMM_NODE_STRU                 *pstNode,
    XML_COMM_CTX_STRU                  *pstXmlCommCtx);
extern VOS_UINT32 TAF_MTA_ProcMeasureReq(
    AGPS_MEASURE_REQ_STRU              *pstMeasureReq);
extern VOS_UINT32 TAF_MTA_SndAtXcposrRptInd(
    VOS_UINT32      ulClearFlg);
extern VOS_VOID TAF_MTA_SndAsPosCnf(
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enPhRatType,
    MTA_RRC_POSITION_CNF_STRU          *pstPosCnf);
extern VOS_UINT32 TAF_MTA_SndPhySetGpsRfClockReq(
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enPhRatType,
    MTA_AT_CGPSCLOCK_ENUM_UINT32        enCgpsClock);
extern VOS_UINT32 TAF_MTA_SaveXmlText(
    TAF_MTA_AGPS_CTX_STRU              *pstAgpsCtx,
    VOS_CHAR                           *pcXml,
    VOS_UINT32                          ulXmlLen);
extern VOS_UINT32 TAF_MTA_FreeAgpsXmlCtx(
    TAF_MTA_AGPS_CTX_STRU              *pstAgpsCtx);
extern VOS_UINT32 TAF_MTA_DealCposSetReqAbnormal(
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg,
    XML_COMM_CTX_STRU                  *pstXmlCtx,
    TAF_MTA_AGPS_CTX_STRU              *pstAgpsCtx);

#endif /* FEATURE_AGPS */
extern VOS_VOID TAF_MTA_SndAtCgpsClockSetCnf(
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg,
    AT_MTA_MSG_TYPE_ENUM_UINT32         enErr);
extern VOS_VOID TAF_MTA_SndAtCposSetCnf (
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg,
    MTA_AT_RESULT_ENUM_UINT32           enErr);
extern VOS_VOID TAF_MTA_RcvAtCgpsClockSetReq(VOS_VOID *pMsg);
extern VOS_VOID TAF_MTA_RcvAtCposSetReq(VOS_VOID *pMsg);
extern VOS_VOID TAF_MTA_RcvPhyCgpsClockSetCnf(VOS_VOID *pMsg);
extern VOS_VOID TAF_MTA_RcvRrcMsgPositionReq(VOS_VOID *pMsg);
extern VOS_VOID TAF_MTA_RcvTcResetUePosStoredInfoInd(VOS_VOID *pMsg);
extern VOS_VOID TAF_MTA_RcvTiCgpsClockSetReqExpired(VOS_VOID *pMsg);
extern VOS_VOID TAF_MTA_RcvTiCposSetReqExpired(VOS_VOID *pMsg);

extern VOS_VOID TAF_MTA_RcvRrcQryNmrCnf(VOS_VOID *pMsg);
extern VOS_VOID TAF_MTA_RcvQryNmrReq(VOS_VOID *pMsg);
extern VOS_UINT32 TAF_MTA_SndAsQryNmrReqMsg(
    VOS_UINT32                          ulReceiverPid
);
extern VOS_VOID TAF_MTA_RcvTiWaitAsQryNmrCnfExpired(VOS_VOID *pMsg);

extern VOS_VOID TAF_MTA_RcvReselOffsetCfgSetReq(VOS_VOID *pMsg);

VOS_VOID TAF_MTA_RcvAtRefclkfreqSetReq(VOS_VOID *pMsg);

VOS_VOID TAF_MTA_SndAtRefclkfreqSetCnf(
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg,
    MTA_AT_RESULT_ENUM_UINT32           enResult
);

VOS_VOID TAF_MTA_RcvAtRefclkfreqQryReq(VOS_VOID *pMsg);

VOS_VOID TAF_MTA_SndAtRefclkfreqInd(VOS_VOID);

VOS_VOID TAF_MTA_RcvPhyRefClockStatusInd(VOS_VOID *pMsg);

/* Added by l00198894 for 新增+ECID命令, 2013-12-10, begin */
VOS_VOID TAF_MTA_RcvAtEcidSetReq(VOS_VOID *pMsg);

VOS_VOID TAF_MTA_SndAtEcidSetCnf (
    AT_APPCTRL_STRU                    *pAppCtrl,
    MTA_AT_RESULT_ENUM_UINT32           enResult,
    VOS_UINT8                          *pucCellInfoStr);

VOS_VOID TAF_MTA_RcvGUAsEcellInfoQryCnf(VOS_VOID *pMsg);

VOS_VOID TAF_MTA_GetPlmnStr(
    VOS_UINT8                          *pucPlmnStr,
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId
);

MTA_AT_RESULT_ENUM_UINT32 TAF_MTA_CodeGasEcidStr(
    RRC_MTA_GSM_NMR_STRU               *pstGsmNmr,
    VOS_UINT8                          *pucCellinfoStr);

MTA_AT_RESULT_ENUM_UINT32 TAF_MTA_CodeWasEcidStr(
    RRC_MTA_UTRAN_NMR_STRU             *pstUtranNmr,
    VOS_UINT8                          *pucCellinfoStr);

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
VOS_UINT32 TAF_MTA_ProcTdsEcidSetReq(
    AT_APPCTRL_STRU                    *pstAppCtrl,
    VOS_UINT32                         *pulResult
);
#endif

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 TAF_MTA_SndLrrcCellinfoQryReq(VOS_VOID);

VOS_VOID TAF_MTA_RcvLrrcCellinfoQryCnf(VOS_VOID *pMsg);

MTA_AT_RESULT_ENUM_UINT32 TAF_MTA_CodeLteEcidStr(
    LRRC_CELLINFO_RSLT_STRU            *pstCellinfoRslt,
    VOS_UINT8                          *pucCellinfoStr);
#endif

VOS_VOID TAF_MTA_RcvTiEcidSetExpired(VOS_VOID *pMsg);
/* Added by l00198894 for 新增+ECID命令, 2013-12-10, end */

VOS_UINT32 TAF_MTA_ProcEcidCustProgress(
    VOS_UINT32                         *pulResult
);

MTA_AT_RESULT_ENUM_UINT32 TAF_MTA_CodeGasEcidStrEx(
    MTC_GSM_CELLINFO_EX_STRU           *pstGsmCellInfoEx,
    VOS_UINT8                          *pucCellinfoStr
);

VOS_VOID TAF_MTA_RcvMtcGsmCellInfoQryCnf(VOS_VOID *pMsg);

VOS_VOID TAF_MTA_SndTlphyAfclockStatusNtf(
    VOS_UINT16                          enRptFlg,
    VOS_UINT16                          usReportCount
);
VOS_VOID TAF_MTA_RcvTlPhyAfclockStatusInd(VOS_VOID *pMsg);
VOS_VOID TAF_MTA_RcvTiWaitAgentQryAfclockExpired(VOS_VOID *pMsg);
VOS_VOID TAF_MTA_RcvTiWaitAgentRefclockIndExpired(VOS_VOID *pMsg);
VOS_UINT32 TAF_MTA_CheckTLMode(VOS_VOID);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif


