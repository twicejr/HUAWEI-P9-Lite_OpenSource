/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMsccPifInterface.h
  版 本 号   : 初稿
  作    者   : z00161729
  生成日期   : 2013年3月25日
  最近修改   :
  功能描述   : mma,mscc,mmc消息交互的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年3月25日
    作    者   : z00161729
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_MSCC_PIF_INTERFACE_H_
#define _NAS_MSCC_PIF_INTERFACE_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "PsTypeDef.h"
#include "TafTypeDef.h"
#include "TafNvInterface.h"
#include "NasNvInterface.h"
#include "ComInterface.h"

#include "TafAppMma.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NAS_MSCC_PIF_CELL_MAX_NUM            (8)                                /* 小区最大数量 */
#define NAS_MSCC_PIF_MAX_PLMN_CNT            (37)

#if (FEATURE_ON == FEATURE_CSG)
#define NAS_MSCC_PIF_MAX_PLMN_CSG_ID_NUM                    (35)
#else
#define NAS_MSCC_PIF_MAX_PLMN_CSG_ID_NUM                    (1)
#endif

#if (FEATURE_ON == FEATURE_CSG)
#define NAS_MSCC_PIF_MAX_HOME_NODEB_NAME_LEN                (48)
#define NAS_MSCC_PIF_CSG_TYPE_LEN                           (12)
#else
#define NAS_MSCC_PIF_MAX_HOME_NODEB_NAME_LEN                (4)
#define NAS_MSCC_PIF_CSG_TYPE_LEN                           (4)
#endif

#define NAS_MSCC_PIF_MAX_CPOL_PLMN_CNT       (12)

#if (FEATURE_ON == FEATURE_LTE)
#define NAS_MSCC_PIF_MAX_RAT_NUM             (3)                                /* 当前支持的接入技术个数 */
#else
#define NAS_MSCC_PIF_MAX_RAT_NUM             (2)                                /* 当前支持的GU接入技术个数 */
#endif

#define NAS_MSCC_PIF_CAUSE_NULL              (0)

#define NAS_MSCC_PIF_NET_SCAN_MAX_FREQ_NUM   (20)

#define NAS_MSCC_PIF_MAX_EQUPLMN_NUM         (18)                               /* 等效的PLMN的最大个数 */
#define NAS_MSCC_PIF_TDS_ARFCN_MAX_NUM       (9)                                /* TDD频点列表最大个数 */
#define NAS_MSCC_PIF_LTE_ARFCN_MAX_NUM       (8)                                /* LTE频点列表最大个数 */


#define NAS_MSCC_PIF_REG_MAX_PLMN_NUM        (8)
#define NAS_MSCC_PIF_REG_MAX_CELL_NUM        (8)


#define NAS_MSCC_PIF_MAX_CFPLMN_NUM          (20)

#define NAS_MSCC_PIF_MAX_OPER_LONG_NAME_LEN                 (100)               /* spn 采用ucs2编码时需要的长度为32，添加一个\0 对齐到36位,因为最大有39的long name ,调整到40*/
#define NAS_MSCC_PIF_MAX_OPER_SHORT_NAME_LEN                (100)               /* spn 采用ucs2编码时需要的长度为32 ,添加一个\0 对齐到36位 */
#define NAS_MSCC_PIF_MAX_USER_OPLMN_VERSION_LEN             (8)                 /* 用户配置的OPLMN版本号最大长度 */
#define NAS_MSCC_PIF_MAX_GROUP_CFG_OPLMN_DATA_LEN           (250)               /* 单组配置OPLMN的最大字节数*/

#define NAS_MSCC_PIF_SCELL_MEAS_TYPE_NONE                   (0x00)              /* AT查询上报  */
#define NAS_MSCC_PIF_SCELL_MEAS_TYPE_RXLEV                  (0x01)              /* RXLEV变化触发的上报 */
#define NAS_MSCC_PIF_SCELL_MEAS_TYPE_RXQUALITY              (0x02)              /* RXQUALITY变化触发的上报 */
#define NAS_MSCC_PIF_SCELL_MEAS_TYPE_CELLID                 (0x04)              /* CELL ID变化触发的上报 */

#define NAS_MSCC_PIF_MAX_PLMN_NUM                           (256)

#define NAS_MSCC_PIF_MAX_HIGH_QUALITY_PLMN_NUM              (16)
#define NAS_MSCC_PIF_MAX_LOW_QUALITY_PLMN_NUM               (16)

#define NAS_MSCC_PIF_MAX_EHPLMN_NUM                         (16)                    /* EHPLMN最大的个数 */
#define NAS_MSCC_PIF_MAX_USERPLMN_NUM                       (100)                   /* USERPLMN最大的个数 */
#define NAS_MSCC_PIF_MAX_OPERPLMN_NUM                       (256)                   /* OPERPLMN最大的个数 */


#define NAS_MSCC_PIF_SRV_ACQ_RAT_NUM_MAX                    (3)

#define NAS_MSCC_PIF_MAX_WHITE_LOCK_SID_NUM                 (20)

#define NAS_MSCC_PIF_MAX_SRCHED_LAI_NUM                     (18)
#define NAS_MSCC_PIF_MAX_IMSI_LEN                           (9)                     /* 最大IMSI长度 */
#define NAS_MSCC_PIF_MAX_DPLMN_NUM                          (256)
#define NAS_MSCC_PIF_INFO_VERSION_LEN                       (9)

#define NAS_MSCC_PIF_MAX_NUM_MSPL_REC                        (24)
/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/** ****************************************************************************
 * Name        : MSCC_PIF_MSG_TYPE_ENUM_UINT32
 * Description : MSCC和其它模块的消息ID定义
 *******************************************************************************/
enum MSCC_PIF_MSG_TYPE_ENUM
{
    /***************************** MMA <-> MSCC *****************************/
    /* MMA发给MSCC的消息原语 */
    ID_MMA_MSCC_START_REQ                               = 0x0001,               /* _H2ASN_MsgChoice MMA_MSCC_START_REQ_STRU */
    ID_MMA_MSCC_SIGN_REPORT_REQ                         = 0x0002,               /* _H2ASN_MsgChoice MMA_MSCC_SIGN_REPORT_REQ_STRU */
    ID_MMA_MSCC_MODE_CHANGE_REQ                         = 0x0003,               /* _H2ASN_MsgChoice MMA_MSCC_MODE_CHANGE_REQ_STRU */
    ID_MMA_MSCC_ATTACH_REQ                              = 0x0004,               /* _H2ASN_MsgChoice MMA_MSCC_ATTACH_REQ_STRU */
    ID_MMA_MSCC_DETACH_REQ                              = 0x0005,               /* _H2ASN_MsgChoice MMA_MSCC_DETACH_REQ_STRU */
    ID_MMA_MSCC_PLMN_LIST_REQ                           = 0x0006,               /* _H2ASN_MsgChoice MMA_MSCC_PLMN_LIST_REQ_STRU */
    ID_MMA_MSCC_PLMN_LIST_ABORT_REQ                     = 0x0007,               /* _H2ASN_MsgChoice MMA_MSCC_PLMN_LIST_ABORT_REQ_STRU */
    ID_MMA_MSCC_PLMN_USER_RESEL_REQ                     = 0x0008,               /* _H2ASN_MsgChoice MMA_MSCC_PLMN_USER_RESEL_REQ_STRU */
    ID_MMA_MSCC_PLMN_SPECIAL_REQ                        = 0x0009,               /* _H2ASN_MsgChoice MMA_MSCC_PLMN_SPECIAL_REQ_STRU */
    ID_MMA_MSCC_POWER_OFF_REQ                           = 0x000A,               /* _H2ASN_MsgChoice MMA_MSCC_POWER_OFF_REQ_STRU */
    ID_MMA_MSCC_SYS_CFG_SET_REQ                         = 0x000B,               /* _H2ASN_MsgChoice MMA_MSCC_SYS_CFG_SET_REQ_STRU */
    ID_MMA_MSCC_SYSTEM_ACQUIRE_REQ                      = 0x000C,               /* _H2ASN_MsgChoice MMA_MSCC_SYSTEM_ACQUIRE_REQ_STRU */
    ID_MMA_MSCC_SPEC_PLMN_SEARCH_ABORT_REQ              = 0x000D,               /* _H2ASN_MsgChoice MMA_MSCC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU */
    ID_MMA_MSCC_OM_MAINTAIN_INFO_IND                    = 0x000E,               /* _H2ASN_MsgChoice MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU */


    /* 用户通过CPOL命令更新UPLMN信息通知给MSCC */
    ID_MMA_MSCC_UPDATE_UPLMN_NTF                        = 0x000F,               /* _H2ASN_MsgChoice MMA_MSCC_UPDATE_UPLMN_NTF_STRU */

    ID_MMA_MSCC_EOPLMN_SET_REQ                          = 0x0010,               /* _H2ASN_MsgChoice MMA_MSCC_EOPLMN_SET_REQ_STRU */

    ID_MMA_MSCC_NET_SCAN_REQ                            = 0x0011,               /* _H2ASN_MsgChoice MMA_MSCC_NET_SCAN_REQ_STRU */
    ID_MMA_MSCC_ABORT_NET_SCAN_REQ                      = 0x0012,               /* _H2ASN_MsgChoice MMA_MSCC_ABORT_NET_SCAN_REQ_STRU */

    ID_MMA_MSCC_OTHER_MODEM_INFO_NOTIFY                 = 0x0013,               /* _H2ASN_MsgChoice MMA_MSCC_OTHER_MODEM_INFO_NOTIFY_STRU */

    ID_MMA_MSCC_NCELL_INFO_NOTIFY                       = 0x0014,               /* _H2ASN_MsgChoice MMA_MSCC_NCELL_INFO_NOTIFY_STRU */

    ID_MMA_MSCC_PS_TRANSFER_NOTIFY                      = 0x0015,               /* _H2ASN_MsgChoice MMA_MSCC_PS_TRANSFER_NOTIFY_STRU */

    /* Added by s00246516 for L-C互操作项目, 2014-01-26, Begin */
    ID_MMA_MSCC_ACQ_REQ                                 = 0x0016,               /* _H2ASN_MsgChoice MMA_MSCC_ACQ_REQ_STRU */
    ID_MMA_MSCC_REG_REQ                                 = 0x0017,               /* _H2ASN_MsgChoice MMA_MSCC_REG_REQ_STRU */
    ID_MMA_MSCC_POWER_SAVE_REQ                          = 0x0018,               /* _H2ASN_MsgChoice MMA_MSCC_POWER_SAVE_REQ_STRU */
    /* Added by s00246516 for L-C互操作项目, 2014-01-26, End */

    ID_MMA_MSCC_SRV_ACQ_REQ                             = 0x0019,               /* _H2ASN_MsgChoice MMA_MSCC_SRV_ACQ_REQ_STRU */
    ID_MMA_MSCC_BEGIN_SESSION_NOTIFY                    = 0x001A,               /* _H2ASN_MsgChoice MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU */
    ID_MMA_MSCC_END_SESSION_NOTIFY                      = 0x001B,               /* _H2ASN_MsgChoice MMA_MSCC_END_SESSION_NOTIFY_STRU */
    ID_MMA_MSCC_IMS_SRV_INFO_NOTIFY                     = 0x001C,               /* _H2ASN_MsgChoice MMA_MSCC_IMS_SRV_INFO_NOTIFY_STRU */
    ID_MMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY     = 0x001D,               /* _H2ASN_MsgChoice MMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU */

    ID_MMA_MSCC_CDMA_MO_CALL_START_NTF                  = 0x001E,               /* _H2ASN_MsgChoice MMA_MSCC_CDMA_MO_CALL_START_NTF_STRU*/ /**< @sa MMA_MSCC_CDMA_MO_CALL_START_NTF_STRU */
    ID_MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF         = 0x001F,               /* _H2ASN_MsgChoice MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU*/ /**< @sa MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU */
    ID_MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF                = 0x0020,               /* _H2ASN_MsgChoice MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU*/ /**< @sa MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU */
    ID_MMA_MSCC_CDMA_MO_CALL_END_NTF                    = 0x0021,               /* _H2ASN_MsgChoice MMA_MSCC_CDMA_MO_CALL_END_NTF_STRU*/ /**< @sa MMA_MSCC_CDMA_MO_CALL_END_NTF_STRU */
    ID_MMA_MSCC_CFREQ_LOCK_NTF                          = 0x0022,               /* _H2ASN_MsgChoice MMA_MSCC_CFREQ_LOCK_NTF_STRU */
    ID_MMA_MSCC_CDMACSQ_SET_REQ                         = 0x0023,               /* _H2ASN_MsgChoice MMA_MSCC_CDMACSQ_SET_REQ_STRU*/

    ID_MMA_MSCC_CFPLMN_SET_REQ                          = 0x0024,               /* _H2ASN_MsgChoice MMA_MSCC_CFPLMN_SET_REQ_STRU*/
    ID_MMA_MSCC_CFPLMN_QUERY_REQ                        = 0x0025,               /* _H2ASN_MsgChoice MMA_MSCC_CFPLMN_QUERY_REQ_STRU*/
    ID_MMA_MSCC_SDT_CONNECTED_IND                       = 0x0026,               /* _H2ASN_MsgChoice MMCM_OM_MAINTAIN_INFO_IND_STRU*/

    ID_MMA_MSCC_PREF_PLMN_SET_REQ                       = 0x0027,               /* _H2ASN_MsgChoice MMA_MSCC_PREF_PLMN_SET_REQ_STRU*/
    ID_MMA_MSCC_PREF_PLMN_QUERY_REQ                     = 0x0028,               /* _H2ASN_MsgChoice MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU*/

    ID_MMA_MSCC_IMS_START_REQ                           = 0x0029,               /* _H2ASN_MsgChoice MMA_MSCC_IMS_START_REQ_STRU */
    ID_MMA_MSCC_IMS_STOP_REQ                            = 0x002A,               /* _H2ASN_MsgChoice MMA_MSCC_IMS_STOP_REQ_STRU */
    ID_MMA_MSCC_VOICE_DOMAIN_CHANGE_IND                 = 0x002B,               /* _H2ASN_MsgChoice MMA_MSCC_VOICE_DOMAIN_CHANGE_IND_STRU */
    ID_MMA_MSCC_AUTO_RESEL_SET_REQ                      = 0x002C,               /* _H2ASN_MsgChoice MMA_MSCC_AUTO_RESEL_SET_STRU */

    ID_MMA_MSCC_HANDSET_INFO_QRY_REQ                    = 0x002D,               /* _H2ASN_MsgChoice MMA_MSCC_HANDSET_INFO_QRY_REQ_STRU*/

    ID_MMA_MSCC_GET_GEO_REQ                             = 0x002E,               /* _H2ASN_MsgChoice MMA_MSCC_GET_GEO_REQ_STRU */
    ID_MMA_MSCC_STOP_GET_GEO_REQ                        = 0X002F,               /* _H2ASN_MsgChoice MMA_MSCC_STOP_GET_GEO_REQ_STRU */

    ID_MMA_MSCC_PS_RAT_TYPE_NTF                         = 0x0030,               /* _H2ASN_MsgChoice MMA_MSCC_PS_RAT_TYPE_NTF_STRU */
    ID_MMA_MSCC_QUIT_CALL_BACK_NTF                      = 0x0031,               /* _H2ASN_MsgChoice MMA_MSCC_QUIT_CALL_BACK_NTF_STRU */
    ID_MMA_MSCC_SET_CSIDLIST_REQ                        = 0x0032,               /* _H2ASN_MsgChoice MMA_MSCC_SET_CSIDLIST_REQ_STRU */

    ID_MMA_MSCC_DPLMN_SET_REQ                           = 0x0033,               /* _H2ASN_MsgChoice MMA_MSCC_DPLMN_SET_REQ_STRU */

    ID_MMA_MSCC_CSG_LIST_SEARCH_REQ                     = 0x0034,               /* _H2ASN_MsgChoice MMA_MSCC_CSG_LIST_SEARCH_REQ_STRU */
    ID_MMA_MSCC_CSG_LIST_ABORT_REQ                      = 0x0035,               /* _H2ASN_MsgChoice MMA_MSCC_CSG_LIST_ABORT_REQ_STRU */

    /* MSCC发送给MMA的消息原语*/
    ID_MSCC_MMA_START_CNF                               = 0x1001,               /* _H2ASN_MsgChoice MSCC_MMA_START_CNF_STRU */
    ID_MSCC_MMA_3GPP_SYS_INFO_IND                       = 0x1002,               /* _H2ASN_MsgChoice MSCC_MMA_3GPP_SYS_INFO_IND_STRU */
    ID_MSCC_MMA_SERVICE_STATUS_IND                      = 0x1003,               /* _H2ASN_MsgChoice MSCC_MMA_SERVICE_STATUS_IND_STRU */
    ID_MSCC_MMA_MM_INFO_IND                             = 0x1004,               /* _H2ASN_MsgChoice MSCC_MMA_MM_INFO_IND_STRU */
    ID_MSCC_MMA_ATTACH_CNF                              = 0x1005,               /* _H2ASN_MsgChoice MSCC_MMA_ATTACH_CNF_STRU */
    ID_MSCC_MMA_DETACH_CNF                              = 0x1006,               /* _H2ASN_MsgChoice MSCC_MMA_DETACH_CNF_STRU */
    ID_MSCC_MMA_DETACH_IND                              = 0x1007,               /* _H2ASN_MsgChoice MSCC_MMA_DETACH_IND_STRU */
    ID_MSCC_MMA_PLMN_LIST_CNF                           = 0x1008,               /* _H2ASN_MsgChoice MSCC_MMA_PLMN_LIST_CNF_STRU */
    ID_MSCC_MMA_PLMN_LIST_REJ                           = 0x1009,               /* _H2ASN_MsgChoice MSCC_MMA_PLMN_LIST_REJ_STRU */
    ID_MSCC_MMA_COVERAGE_AREA_IND                       = 0x100A,               /* _H2ASN_MsgChoice MSCC_MMA_COVERAGE_AREA_IND_STRU */
    ID_MSCC_MMA_POWER_OFF_CNF                           = 0x100B,               /* _H2ASN_MsgChoice MSCC_MMA_POWER_OFF_CNF_STRU */
    ID_MSCC_MMA_RSSI_IND                                = 0x100C,               /* _H2ASN_MsgChoice MSCC_MMA_RSSI_IND_STRU */
    ID_MSCC_MMA_PLMN_SPECIAL_SEL_CNF                    = 0x100D,               /* _H2ASN_MsgChoice MSCC_MMA_PLMN_SPECIAL_SEL_CNF_STRU */
    ID_MSCC_MMA_DATATRAN_ATTRI_IND                      = 0x100E,               /* _H2ASN_MsgChoice MSCC_MMA_DATATRAN_ATTRI_IND_STRU */
    ID_MSCC_MMA_SYS_CFG_CNF                             = 0x100F,               /* _H2ASN_MsgChoice MSCC_MMA_SYS_CFG_SET_CNF_STRU */
    ID_MSCC_MMA_SYSTEM_ACQUIRE_END_IND                  = 0x1010,               /* _H2ASN_MsgChoice MSCC_MMA_SYSTEM_ACQUIRE_END_IND_STRU */
    ID_MSCC_MMA_PLMN_LIST_ABORT_CNF                     = 0x1011,               /* _H2ASN_MsgChoice MSCC_MMA_PLMN_LIST_ABORT_CNF_STRU */
    ID_MSCC_MMA_SPEC_PLMN_SEARCH_ABORT_CNF              = 0x1012,               /* _H2ASN_MsgChoice MSCC_MMA_SPEC_PLMN_SEARCH_ABORT_CNF_STRU */
    ID_MSCC_MMA_UMTS_CIPHER_INFO_IND                    = 0x1013,               /* _H2ASN_MsgChoice MSCC_MMA_UMTS_CIPHER_INFO_IND_STRU */
    ID_MSCC_MMA_GPRS_CIPHER_INFO_IND                    = 0x1014,               /* _H2ASN_MsgChoice MSCC_MMA_GPRS_CIPHER_INFO_IND_STRU */
    ID_MSCC_MMA_PLMN_SPECIAL_SEL_REJ                    = 0x1015,               /* _H2ASN_MsgChoice MSCC_MMA_PLMN_SPECIAL_SEL_REJ_STRU */
    ID_MSCC_MMA_AC_INFO_CHANGE_IND                      = 0x1016,               /* _H2ASN_MsgChoice MSCC_MMA_AC_INFO_CHANGE_IND_STRU */
    ID_MSCC_MMA_PLMN_RESEL_CNF                          = 0x1017,               /* _H2ASN_MsgChoice MSCC_MMA_PLMN_RESEL_CNF_STRU */
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
    ID_MSCC_MMA_REG_RESULT_IND                          = 0x1018,               /* _H2ASN_MsgChoice MSCC_MMA_REG_RESULT_IND_STRU */
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */

    ID_MSCC_MMA_SYSTEM_ACQUIRE_START_IND                = 0x1019,               /* _H2ASN_MsgChoice MSCC_MMA_SYSTEM_ACQUIRE_START_IND_STRU */

    ID_MSCC_MMA_EOPLMN_SET_CNF                          = 0x101A,               /* _H2ASN_MsgChoice MSCC_MMA_EOPLMN_SET_CNF_STRU */
    ID_MSCC_MMA_USIM_AUTH_FAIL_IND                      = 0x101B,               /* _H2ASN_MsgChoice MSCC_MMA_USIM_AUTH_FAIL_IND_STRU */

    ID_MSCC_MMA_NET_SCAN_CNF                            = 0x101C,               /* _H2ASN_MsgChoice MSCC_MMA_NET_SCAN_CNF_STRU */
    ID_MSCC_MMA_ABORT_NET_SCAN_CNF                      = 0x101D,               /* _H2ASN_MsgChoice MSCC_MMA_ABORT_NET_SCAN_CNF_STRU */

    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-9, begin */
    ID_MSCC_MMA_NETWORK_CAPABILITY_INFO_IND             = 0x101E,               /* _H2ASN_MsgChoice MSCC_MMA_NETWORK_CAPABILITY_INFO_IND_STRU */
    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-9, end */
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
    ID_MSCC_MMA_CAMP_ON_IND                             = 0x101F,               /* _H2ASN_MsgChoice MSCC_MMA_CAMP_ON_IND_STRU_STRU */
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

    ID_MSCC_MMA_EPLMN_INFO_IND                          = 0x1020,               /* _H2ASN_MsgChoice MSCC_MMA_EPLMN_INFO_IND_STRU */

    ID_MSCC_MMA_CS_SERVICE_CONN_STATUS_IND              = 0x1021,               /* _H2ASN_MsgChoice MSCC_MMA_CS_SERVICE_CONN_STATUS_IND_STRU */

    ID_MSCC_MMA_SRV_REJ_IND                             = 0x1022,               /* _H2ASN_MsgChoice MSCC_MMA_SERV_REJ_IND_STRU */
    /* Added by s00246516 for L-C互操作项目, 2014-01-26, Begin */
    ID_MSCC_MMA_ACQ_CNF                                 = 0x1023,               /* _H2ASN_MsgChoice MSCC_MMA_ACQ_CNF_STRU */
    ID_MSCC_MMA_REG_CNF                                 = 0x1024,               /* _H2ASN_MsgChoice MSCC_MMA_REG_CNF_STRU */
    ID_MSCC_MMA_POWER_SAVE_CNF                          = 0x1025,               /* _H2ASN_MsgChoice MSCC_MMA_POWER_SAVE_CNF_STRU */
    ID_MSCC_MMA_ACQ_IND                                 = 0x1026,               /* _H2ASN_MsgChoice MSCC_MMA_ACQ_IND_STRU */
    /* Added by s00246516 for L-C互操作项目, 2014-01-26, End */


    /* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, Begin */
    ID_MSCC_MMA_PS_SERVICE_CONN_STATUS_IND              = 0x1027,               /* _H2ASN_MsgChoice MSCC_MMA_PS_SERVICE_CONN_STATUS_IND_STRU */
    /* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, End */
    ID_MSCC_MMA_RF_AVAILABLE_IND                        = 0x1028,               /* _H2ASN_MsgChoice MSCC_MMA_RF_AVAILABLE_IND_STRU */
    ID_MSCC_MMA_SRV_ACQ_CNF                             = 0x1029,               /* _H2ASN_MsgChoice MSCC_MMA_SRV_ACQ_CNF_STRU */
    ID_MSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND           = 0x102A,               /* _H2ASN_MsgChoice MSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND_STRU */
    ID_MSCC_MMA_IMS_VOICE_CAP_IND                       = 0x102B,               /* _H2ASN_MsgChoice MSCC_MMA_IMS_VOICE_CAP_IND_STRU */

    ID_MSCC_MMA_1X_SYSTEM_SERVICE_INFO_IND              = 0x102C,               /* _H2ASN_MsgChoice MSCC_MMA_1X_SYSTEM_SERVICE_INFO_IND_STRU */
    ID_MSCC_MMA_CDMACSQ_SET_CNF                         = 0x102D,               /* _H2ASN_MsgChoice MSCC_MMA_CDMACSQ_SET_CNF_STRU*/
    ID_MSCC_MMA_CDMACSQ_SIGNAL_QUALITY_IND              = 0x102E,               /* _H2ASN_MsgChoice MSCC_MMA_CDMACSQ_IND_STRU*/

    ID_MSCC_MMA_HRPD_SERVICE_STATUS_IND                 = 0x102F,                /* _H2ASN_MsgChoice MSCC_MMA_HRPD_SERVICE_STATUS_IND_STRU*/

    ID_MSCC_MMA_CFPLMN_SET_CNF                          = 0x1030,               /* _H2ASN_MsgChoice MSCC_MMA_CFPLMN_SET_CNF_STRU*/
    ID_MSCC_MMA_CFPLMN_QUERY_CNF                        = 0x1031,               /* _H2ASN_MsgChoice MSCC_MMA_CFPLMN_QUERY_CNF_STRU*/

    ID_MSCC_MMA_PREF_PLMN_SET_CNF                       = 0x1032,               /* _H2ASN_MsgChoice MSCC_MMA_PREF_PLMN_SET_CNF_STRU*/
    ID_MSCC_MMA_PREF_PLMN_QUERY_CNF                     = 0x1033,               /* _H2ASN_MsgChoice MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU*/

    ID_MSCC_MMA_HRPD_OVERHEAD_MSG_IND                   = 0x1034,                /* _H2ASN_MsgChoice MSCC_MMA_HRPD_OVERHEAD_MSG_IND_STRU*/
    ID_MSCC_MMA_HRPD_SYS_ACQ_CNF                        = 0x1035,                /* _H2ASN_MsgChoice MSCC_MMA_HRPD_SYS_ACQ_CNF_STRU*/

    ID_MSCC_MMA_1X_SYSTEM_TIME_IND                      = 0x1036,               /* _H2ASN_MsgChoice MSCC_MMA_1X_SYSTEM_TIME_IND_STRU */

    ID_MSCC_MMA_IMS_SWITCH_STATE_IND                    = 0x1038,               /* _H2ASN_MsgChoice MSCC_MMA_IMS_SWITCH_STATE_IND_STRU */
    ID_MSCC_MMA_IMS_START_CNF                           = 0x1039,               /* _H2ASN_MsgChoice MSCC_MMA_IMS_START_CNF_STRU */
    ID_MSCC_MMA_IMS_STOP_CNF                            = 0x103A,               /* _H2ASN_MsgChoice MSCC_MMA_IMS_STOP_CNF_STRU */

    ID_MSCC_MMA_INTERSYS_START_IND                      = 0x103B,               /* _H2ASN_MsgChoice MSCC_MMA_INTERSYS_START_IND_STRU */
    ID_MSCC_MMA_INTERSYS_END_IND                        = 0x103C,               /* _H2ASN_MsgChoice MSCC_MMA_INTERSYS_END_IND_STRU */



    ID_MSCC_MMA_HANDSET_INFO_QRY_CNF                    = 0x103D,               /* _H2ASN_MsgChoice MSCC_MMA_HANDSET_INFO_QRY_CNF_STRU */

    ID_MSCC_MMA_GET_GEO_CNF                             = 0x103E,               /* _H2ASN_MsgChoice MSCC_MMA_GET_GEO_CNF_STRU */
    ID_MSCC_MMA_STOP_GET_GEO_CNF                        = 0x103F,               /* _H2ASN_MsgChoice MSCC_MMA_STOP_GET_GEO_CNF_STRU */

    ID_MSCC_MMA_1X_SID_NID_IND                          = 0x1042,               /* _H2ASN_MsgChoice MSCC_MMA_1X_SID_NID_IND_STRU */
    ID_MSCC_MMA_SET_CSIDLIST_CNF                        = 0x1043,               /* _H2ASN_MsgChoice MSCC_MMA_SET_CSIDLIST_CNF_STRU */
    ID_MSCC_MMA_1X_EMC_CALL_BACK_IND                    = 0x1044,               /* _H2ASN_MsgChoice MSCC_MMA_1X_EMC_CALL_BACK_IND_STRU */
    ID_MSCC_MMA_SYNC_SERVICE_AVAIL_IND                  = 0x1045,               /* _H2ASN_MsgChoice MSCC_MMA_SYNC_SERVICE_AVAIL_IND_STRU */

    ID_MSCC_MMA_SRCHED_PLMN_INFO_IND                    = 0x1046,

    ID_MSCC_MMA_1X_UE_STATUS_IND                        = 0x1047,               /* _H2ASN_MsgChoice MSCC_MMA_UE_STATE_IND_STRU */
    ID_MMA_MSCC_HDR_CSQ_SET_REQ                         = 0x1048,               /* _H2ASN_MsgChoice MMA_MSCC_HDR_CSQ_SET_REQ_STRU*/
    ID_MSCC_MMA_HDR_CSQ_SET_CNF                         = 0x1049,               /* _H2ASN_MsgChoice MSCC_MMA_HDR_CSQ_SET_CNF_STRU*/
    ID_MSCC_MMA_HDR_CSQ_QUALITY_IND                     = 0x104A,               /* _H2ASN_MsgChoice MSCC_MMA_HDR_CSQ_IND_STRU*/

    ID_MSCC_MMA_DPLMN_SET_CNF                           = 0x104B,               /* _H2ASN_MsgChoice MSCC_MMA_DPLMN_SET_CNF_STRU */

    ID_MSCC_MMA_CSG_LIST_SEARCH_CNF                     = 0x104C,               /* _H2ASN_MsgChoice MSCC_MMA_CSG_LIST_SEARCH_CFN_STRU */
    ID_MSCC_MMA_CSG_LIST_ABORT_CNF                      = 0x104D,               /* _H2ASN_MsgChoice MSCC_MMA_CSG_LIST_ABORT_CNF_STRU */
    ID_MSCC_MMA_CSG_LIST_REJ                            = 0x104E,               /* _H2ASN_MsgChoice MSCC_MMA_CSG_LIST_REJ_STRU */

    ID_MSCC_MMA_DATA_CALL_REDIAL_SYS_ACQ_IND            = 0x104F,               /* _H2ASN_MsgChoice MSCC_MMA_DATA_CALL_REDIAL_SYS_ACQ_IND_STRU*/

    /***************************** MSCC <-> XSD *****************************/
    ID_MSCC_XSD_MSG_BASE                                = 0x2000,

    ID_MSCC_XSD_START_REQ                               = ID_MSCC_XSD_MSG_BASE + 0x0000,    /* _H2ASN_MsgChoice MSCC_XSD_START_REQ_STRU*/ /**< @sa MSCC_XSD_START_REQ_STRU */
    ID_XSD_MSCC_START_CNF                               = ID_MSCC_XSD_MSG_BASE + 0x0001,    /* _H2ASN_MsgChoice XSD_MSCC_START_CNF_STRU*/ /**< @sa XSD_MSCC_START_CNF_STRU */
    ID_MSCC_XSD_POWER_OFF_REQ                           = ID_MSCC_XSD_MSG_BASE + 0x0002,    /* _H2ASN_MsgChoice MSCC_XSD_POWER_OFF_REQ_STRU*/ /**< @sa MSCC_XSD_POWER_OFF_REQ_STRU */
    ID_XSD_MSCC_POWER_OFF_CNF                           = ID_MSCC_XSD_MSG_BASE + 0x0003,    /* _H2ASN_MsgChoice XSD_MSCC_POWER_OFF_CNF_STRU*/ /**< @sa XSD_MSCC_POWER_OFF_CNF_STRU */
    ID_MSCC_XSD_MO_CALL_START_NTF                       = ID_MSCC_XSD_MSG_BASE + 0x0004,    /* _H2ASN_MsgChoice MSCC_XSD_MO_CALL_START_NTF_STRU*/ /**< @sa MSCC_XSD_MO_CALL_START_NTF_STRU */
    ID_MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF          = ID_MSCC_XSD_MSG_BASE + 0x0005,    /* _H2ASN_MsgChoice MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU*/ /**< @sa MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU */
    ID_MSCC_XSD_MO_CALL_SUCCESS_NTF                     = ID_MSCC_XSD_MSG_BASE + 0x0006,    /* _H2ASN_MsgChoice MSCC_XSD_MO_CALL_SUCCESS_NTF_STRU*/ /**< @sa MSCC_XSD_CALL_SUCCESS_NTF_STRU */
    ID_MSCC_XSD_MO_CALL_END_NTF                         = ID_MSCC_XSD_MSG_BASE + 0x0007,    /* _H2ASN_MsgChoice MSCC_XSD_1X_MO_CALL_END_NTF_STRU*/ /**< @sa MSCC_XSD_CALL_END_NTF_STRU */
    ID_MSCC_XSD_SYSTEM_ACQUIRE_REQ                      = ID_MSCC_XSD_MSG_BASE + 0x0008,    /* _H2ASN_MsgChoice MSCC_XSD_SYSTEM_ACQUIRE_REQ_STRU*/ /**< @sa MSCC_XSD_SYSTEM_ACQUIRE_REQ_STRU */
    ID_XSD_MSCC_SYSTEM_ACQUIRE_CNF                      = ID_MSCC_XSD_MSG_BASE + 0x0009,    /* _H2ASN_MsgChoice XSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU*/ /**< @sa XSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU */
    ID_XSD_MSCC_SYSTEM_ACQUIRE_IND                      = ID_MSCC_XSD_MSG_BASE + 0x000A,    /* _H2ASN_MsgChoice XSD_MSCC_SYSTEM_ACQUIRE_IND_STRU*/ /**< @sa XSD_MSCC_SYSTEM_ACQUIRE_IND_STRU */
    ID_XSD_MSCC_SYSTEM_ACQUIRE_START_IND                = ID_MSCC_XSD_MSG_BASE + 0x000B,    /* _H2ASN_MsgChoice XSD_MSCC_SYSTEM_ACQUIRE_START_IND_STRU*/ /**< @sa XSD_MSCC_SYSTEM_ACQUIRE_START_IND_STRU */
    ID_XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND              = ID_MSCC_XSD_MSG_BASE + 0x000C,    /* _H2ASN_MsgChoice XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU */
    ID_MSCC_XSD_CFREQLOCK_NTF                           = ID_MSCC_XSD_MSG_BASE + 0x000D,    /* _H2ASN_MsgChoice MSCC_XSD_CFREQ_LOCK_NTF_STRU */
    ID_MSCC_XSD_CDMACSQ_SET_REQ                         = ID_MSCC_XSD_MSG_BASE + 0x000E,    /* _H2ASN_MsgChoice MSCC_XSD_CDMACSQ_SET_REQ_STRU*/
    ID_XSD_MSCC_CDMACSQ_SET_CNF                         = ID_MSCC_XSD_MSG_BASE + 0x000F,    /* _H2ASN_MsgChoice XSD_MSCC_CDMACSQ_SET_CNF_STRU*/
    ID_XSD_MSCC_CDMACSQ_SIGNAL_QUALITY_IND              = ID_MSCC_XSD_MSG_BASE + 0x0010,    /* _H2ASN_MsgChoice XSD_MSCC_CDMACSQ_IND_STRU*/
    ID_XSD_MSCC_1X_SYSTEM_TIME_IND                      = ID_MSCC_XSD_MSG_BASE + 0x0011,    /* _H2ASN_MsgChoice XSD_MSCC_1X_SYSTEM_TIME_IND_STRU*/

    ID_MSCC_XSD_POWER_SAVE_REQ                          = ID_MSCC_XSD_MSG_BASE + 0x0012,    /* _H2ASN_MsgChoice MSCC_XSD_POWER_SAVE_REQ_STRU */
    ID_XSD_MSCC_POWER_SAVE_CNF                          = ID_MSCC_XSD_MSG_BASE + 0x0013,    /* _H2ASN_MsgChoice XSD_MSCC_POWER_SAVE_CNF_STRU */
    ID_MSCC_XSD_CAS_STATUS_IND                          = ID_MSCC_XSD_MSG_BASE + 0x0014,    /* _H2ASN_MsgChoice MSCC_XSD_CAS_STATUS_IND_STRU */
    ID_MSCC_XSD_SYS_CFG_REQ                             = ID_MSCC_XSD_MSG_BASE + 0x0015,    /* _H2ASN_MsgChoice MSCC_XSD_SYS_CFG_REQ_STRU */
    ID_XSD_MSCC_SYS_CFG_CNF                             = ID_MSCC_XSD_MSG_BASE + 0x0016,    /* _H2ASN_MsgChoice XSD_MSCC_SYS_CFG_CNF_STRU */

    ID_XSD_MSCC_RF_AVAILABLE_IND                        = ID_MSCC_XSD_MSG_BASE + 0x0017,    /* _H2ASN_MsgChoice NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU */

    ID_MSCC_XSD_SRV_ACQ_REQ                             = ID_MSCC_XSD_MSG_BASE + 0x0018,    /* _H2ASN_MsgChoice MSCC_XSD_SRV_ACQ_REQ_STRU */
    ID_XSD_MSCC_SRV_ACQ_CNF                             = ID_MSCC_XSD_MSG_BASE + 0x0019,    /* _H2ASN_MsgChoice XSD_MSCC_SRV_ACQ_CNF_STRU */
    ID_MSCC_XSD_BEGIN_SESSION_NOTIFY                    = ID_MSCC_XSD_MSG_BASE + 0x001A,    /* _H2ASN_MsgChoice MSCC_XSD_BEGIN_SESSION_NOTIFY_STRU */
    ID_MSCC_XSD_END_SESSION_NOTIFY                      = ID_MSCC_XSD_MSG_BASE + 0x001B,    /* _H2ASN_MsgChoice MSCC_XSD_END_SESSION_NOTIFY_STRU */

    ID_MSCC_XSD_HANDSET_INFO_QRY_REQ                    = ID_MSCC_XSD_MSG_BASE + 0x001C,    /* _H2ASN_MsgChoice MSCC_XSD_HANDSET_INFO_QRY_STRU*/
    ID_XSD_MSCC_HANDSET_INFO_QRY_CNF                    = ID_MSCC_XSD_MSG_BASE + 0x001D,    /* _H2ASN_MsgChoice XSD_MSCC_HANDSET_INFO_QRY_CNF_STRU*/

    ID_XSD_MSCC_EMC_CALLBACK_IND                        = ID_MSCC_XSD_MSG_BASE + 0x001E,    /* _H2ASN_MsgChoice XSD_MSCC_EMC_CALLBACK_IND_STRU */
    ID_MSCC_XSD_END_EMC_CALLBACK_NTF                    = ID_MSCC_XSD_MSG_BASE + 0x001F,    /* _H2ASN_MsgChoice MSCC_XSD_END_EMC_CALLBACK_NTF_STRU */

    ID_XSD_MSCC_SID_NID_IND                             = ID_MSCC_XSD_MSG_BASE + 0x0020,    /* _H2ASN_MsgChoice MSCC_XSD_SID_IND_STRU*/

    ID_MSCC_XSD_SET_CSIDLIST_REQ                        = ID_MSCC_XSD_MSG_BASE + 0x0021,    /* _H2ASN_MsgChoice MSCC_XSD_SET_CSIDLIST_REQ_STRU*/
    ID_XSD_MSCC_SET_CSIDLIST_CNF                        = ID_MSCC_XSD_MSG_BASE + 0x0022,    /* _H2ASN_MsgChoice XSD_MSCC_SET_CSIDLIST_CNF_STRU*/
    ID_XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND              = ID_MSCC_XSD_MSG_BASE + 0x0023,    /* _H2ASN_MsgChoice XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND_STRU*/

    ID_XSD_MSCC_CDMA_UE_STATUS_IND                      = ID_MSCC_XSD_MSG_BASE + 0x0024,    /* _H2ASN_MsgChoice XSD_MSCC_UE_STATE_IND_STRU*/

    ID_XSD_MSCC_1X_NO_SERVICE_IND                       = ID_MSCC_XSD_MSG_BASE + 0x0025,    /* _H2ASN_MsgChoice XSD_MSCC_1X_NO_SERVICE_IND_STRU*/

    /***************************** MSCC <-> HSD *****************************/
    ID_MSCC_HSD_MSG_BASE                                = 0x3000,
    ID_MSCC_HSD_START_REQ                               = ID_MSCC_HSD_MSG_BASE + 0x0000,    /*_H2ASN_MsgChoice MSCC_HSD_START_REQ_STRU */
    ID_HSD_MSCC_START_CNF                               = ID_MSCC_HSD_MSG_BASE + 0x0001,    /*_H2ASN_MsgChoice HSD_MSCC_START_CNF_STRU */
    ID_MSCC_HSD_POWER_OFF_REQ                           = ID_MSCC_HSD_MSG_BASE + 0x0002,    /*_H2ASN_MsgChoice MSCC_HSD_POWER_OFF_REQ_STRU */
    ID_HSD_MSCC_POWER_OFF_CNF                           = ID_MSCC_HSD_MSG_BASE + 0x0003,    /*_H2ASN_MsgChoice HSD_MSCC_POWER_OFF_CNF_STRU */
    ID_MSCC_HSD_SYSTEM_ACQUIRE_REQ                      = ID_MSCC_HSD_MSG_BASE + 0x0004,    /*_H2ASN_MsgChoice MSCC_HSD_SYSTEM_ACQUIRE_REQ_STRU */
    ID_HSD_MSCC_SYSTEM_ACQUIRE_START_IND                = ID_MSCC_HSD_MSG_BASE + 0x0005,    /*_H2ASN_MsgChoice HSD_MSCC_SYSTEM_ACQUIRE_START_IND_STRU */
    ID_HSD_MSCC_SYSTEM_ACQUIRE_CNF                      = ID_MSCC_HSD_MSG_BASE + 0x0006,    /*_H2ASN_MsgChoice HSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU */
    ID_HSD_MSCC_SYSTEM_ACQUIRE_END_IND                  = ID_MSCC_HSD_MSG_BASE + 0x0007,    /*_H2ASN_MsgChoice HSD_MSCC_SYSTEM_ACQUIRE_END_IND_STRU */
    ID_MSCC_HSD_DATA_CALL_START_NTF                     = ID_MSCC_HSD_MSG_BASE + 0x0008,    /*_H2ASN_MsgChoice MSCC_HSD_DATA_CALL_START_NTF_STRU */
    ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ            = ID_MSCC_HSD_MSG_BASE + 0x0009,    /*_H2ASN_MsgChoice MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ_STRU */
    ID_HSD_MSCC_DATA_CALL_REDIAL_SYS_ACQ_CNF            = ID_MSCC_HSD_MSG_BASE + 0x000A,    /*_H2ASN_MsgChoice HSD_MSCC_DATA_CALL_REDIAL_SYS_ACQ_CNF_STRU */
    ID_MSCC_HSD_DATA_CALL_SUCC_NTF                      = ID_MSCC_HSD_MSG_BASE + 0x000B,    /*_H2ASN_MsgChoice MSCC_HSD_DATA_CALL_SUCC_NTF_STRU */
    ID_MSCC_HSD_DATA_CALL_END_NTF                       = ID_MSCC_HSD_MSG_BASE + 0x000C,    /*_H2ASN_MsgChoice MSCC_HSD_DATA_CALL_END_NTF_STRU */
    ID_HSD_MSCC_HRPD_IRAT_TO_LTE_NTF                    = ID_MSCC_HSD_MSG_BASE + 0x000D,    /*_H2ASN_MsgChoice HSD_MSCC_HRPD_IRAT_TO_LTE_NTF_STRU */

    ID_HSD_MSCC_SESSION_NEG_RSLT_IND                    = ID_MSCC_HSD_MSG_BASE + 0x000E,    /*_H2ASN_MsgChoice HSD_MSCC_SESSION_NEG_RSLT_IND_STRU */
    ID_HSD_MSCC_OVERHEAD_MSG_IND                        = ID_MSCC_HSD_MSG_BASE + 0x000F,    /*_H2ASN_MsgChoice HSD_MSCC_OVERHEAD_MSG_IND_STRU */

    ID_MSCC_HSD_1X_SYS_CHANGE_IND                       = ID_MSCC_HSD_MSG_BASE + 0x0010,    /* _H2ASN_MsgChoice MSCC_HSD_1X_SYS_CHANGE_IND_STRU */
    ID_MSCC_HSD_DISABLE_LTE_NTF                         = ID_MSCC_HSD_MSG_BASE + 0x0011,    /* _H2ASN_MsgChoice MSCC_HSD_DISABLE_LTE_NTF_STRU */
    ID_HSD_MSCC_INTERSYS_START_IND                      = ID_MSCC_HSD_MSG_BASE + 0x0012,    /* _H2ASN_MsgChoice HSD_MSCC_INTERSYS_START_IND_STRU */
    ID_HSD_MSCC_INTERSYS_END_IND                        = ID_MSCC_HSD_MSG_BASE + 0x0013,    /* _H2ASN_MsgChoice HSD_MSCC_INTERSYS_END_IND_STRU */

    ID_MSCC_HSD_QRY_HRPD_SYS_INFO_REQ                   = ID_MSCC_HSD_MSG_BASE + 0x0014,    /* _H2ASN_MsgChoice MSCC_HSD_QRY_HRPD_SYS_INFO_REQ_STRU */
    ID_HSD_MSCC_QRY_HRPD_SYS_INFO_CNF                   = ID_MSCC_HSD_MSG_BASE + 0x0015,    /* _H2ASN_MsgChoice HSD_MSCC_QRY_HRPD_SYS_INFO_CNF_STRU */
    ID_MSCC_HSD_BG_SEARCH_REQ                           = ID_MSCC_HSD_MSG_BASE + 0x0016,    /* _H2ASN_MsgChoice MSCC_HSD_BG_SEARCH_REQ_STRU */
    ID_HSD_MSCC_BG_SEARCH_CNF                           = ID_MSCC_HSD_MSG_BASE + 0x0017,    /* _H2ASN_MsgChoice HSD_MSCC_BG_SEARCH_CNF_STRU */
    ID_MSCC_HSD_SYS_CFG_REQ                             = ID_MSCC_HSD_MSG_BASE + 0x0018,    /* _H2ASN_MsgChoice MSCC_HSD_SYS_CFG_REQ_STRU */
    ID_HSD_MSCC_SYS_CFG_CNF                             = ID_MSCC_HSD_MSG_BASE + 0x0019,    /* _H2ASN_MsgChoice HSD_MSCC_SYS_CFG_CNF_STRU */
    ID_HSD_MSCC_SYSTEM_SYNC_IND                         = ID_MSCC_HSD_MSG_BASE + 0x001A,    /* _H2ASN_MsgChoice HSD_MSCC_SYSTEM_SYNC_IND_STRU */
    ID_HSD_MSCC_SESSION_INFO_IND                        = ID_MSCC_HSD_MSG_BASE + 0x001B,    /* _H2ASN_MsgChoice HSD_MSCC_SESSION_INFO_IND_STRU */
    ID_MSCC_HSD_POWER_SAVE_REQ                          = ID_MSCC_HSD_MSG_BASE + 0x001C,    /* _H2ASN_MsgChoice MSCC_HSD_POWER_SAVE_REQ_STRU */
    ID_HSD_MSCC_POWER_SAVE_CNF                          = ID_MSCC_HSD_MSG_BASE + 0x001D,    /* _H2ASN_MsgChoice HSD_MSCC_POWER_SAVE_CNF_STRU */
    ID_HSD_MSCC_CAS_STATUS_IND                          = ID_MSCC_HSD_MSG_BASE + 0x001E,    /* _H2ASN_MsgChoice HSD_MSCC_CAS_STATUS_IND_STRU */
    ID_MSCC_HSD_STOP_BG_SEARCH_REQ                      = ID_MSCC_HSD_MSG_BASE + 0x001F,    /* _H2ASN_MsgChoice MSCC_HSD_STOP_BG_SEARCH_REQ_STRU */
    ID_HSD_MSCC_STOP_BG_SEARCH_CNF                      = ID_MSCC_HSD_MSG_BASE + 0x0020,    /* _H2ASN_MsgChoice HSD_MSCC_STOP_BG_SEARCH_CNF_STRU */

    ID_HSD_MSCC_RF_AVAILABLE_IND                        = ID_MSCC_HSD_MSG_BASE + 0x0021,    /* _H2ASN_MsgChoice NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU */

    ID_MSCC_HSD_SRV_ACQ_REQ                             = ID_MSCC_HSD_MSG_BASE + 0x0022,    /* _H2ASN_MsgChoice MSCC_HSD_SRV_ACQ_REQ_STRU */
    ID_HSD_MSCC_SRV_ACQ_CNF                             = ID_MSCC_HSD_MSG_BASE + 0x0023,    /* _H2ASN_MsgChoice HSD_MSCC_SRV_ACQ_CNF_STRU */
    ID_MSCC_HSD_BEGIN_SESSION_NOTIFY                    = ID_MSCC_HSD_MSG_BASE + 0x0024,    /* _H2ASN_MsgChoice MSCC_HSD_BEGIN_SESSION_NOTIFY_STRU */
    ID_MSCC_HSD_END_SESSION_NOTIFY                      = ID_MSCC_HSD_MSG_BASE + 0x0025,    /* _H2ASN_MsgChoice MSCC_HSD_END_SESSION_NOTIFY_STRU */

    ID_MSCC_HSD_CFREQLOCK_NTF                           = ID_MSCC_HSD_MSG_BASE + 0x0026,    /* _H2ASN_MsgChoice NAS_MSCC_SndHsdCfreqLockNtf */

    ID_HSD_MSCC_HRPD_NO_SERVICE_IND                     = ID_MSCC_HSD_MSG_BASE + 0x0027,    /* _H2ASN_MsgChoice HSD_MSCC_HRPD_NO_SERVICE_IND_STRU */
    ID_MSCC_HSD_HDR_CSQ_SET_REQ                         = ID_MSCC_HSD_MSG_BASE + 0x0028,    /* _H2ASN_MsgChoice MSCC_HSD_HDR_CSQ_SET_REQ_STRU */
    ID_HSD_MSCC_HDR_CSQ_SET_CNF                         = ID_MSCC_HSD_MSG_BASE + 0x0029,    /* _H2ASN_MsgChoice HSD_MSCC_HDR_CSQ_SET_CNF_STRU */
    ID_HSD_MSCC_HDR_CSQ_IND                             = ID_MSCC_HSD_MSG_BASE + 0x002A,    /* _H2ASN_MsgChoice HSD_MSCC_HDR_CSQ_IND_STRU */


    /***************************** MSCC <-> MMC *****************************/
    ID_MSCC_MMC_MSG_BASE                                = 0x4000,
    /* MSCC发给MMC的消息原语 */
    ID_MSCC_MMC_START_REQ                               = ID_MSCC_MMC_MSG_BASE + 0,     /* _H2ASN_MsgChoice MSCC_MMC_START_REQ_STRU */
    ID_MSCC_MMC_SIGN_REPORT_REQ                         = ID_MSCC_MMC_MSG_BASE + 2,     /* _H2ASN_MsgChoice MSCC_MMC_SIGN_REPORT_REQ_STRU */
    ID_MSCC_MMC_MODE_CHANGE_REQ                         = ID_MSCC_MMC_MSG_BASE + 4,     /* _H2ASN_MsgChoice MSCC_MMC_MODE_CHANGE_REQ_STRU */
    ID_MSCC_MMC_ATTACH_REQ                              = ID_MSCC_MMC_MSG_BASE + 6,     /* _H2ASN_MsgChoice MSCC_MMC_ATTACH_REQ_STRU */
    ID_MSCC_MMC_DETACH_REQ                              = ID_MSCC_MMC_MSG_BASE + 8,     /* _H2ASN_MsgChoice MSCC_MMC_DETACH_REQ_STRU */
    ID_MSCC_MMC_PLMN_LIST_REQ                           = ID_MSCC_MMC_MSG_BASE + 10,    /* _H2ASN_MsgChoice MSCC_MMC_PLMN_LIST_REQ_STRU */
    ID_MSCC_MMC_PLMN_LIST_ABORT_REQ                     = ID_MSCC_MMC_MSG_BASE + 12,    /* _H2ASN_MsgChoice MSCC_MMC_PLMN_LIST_ABORT_REQ_STRU */
    ID_MSCC_MMC_PLMN_USER_RESEL_REQ                     = ID_MSCC_MMC_MSG_BASE + 14,    /* _H2ASN_MsgChoice MSCC_MMC_PLMN_USER_RESEL_REQ_STRU */
    ID_MSCC_MMC_PLMN_SPECIAL_REQ                        = ID_MSCC_MMC_MSG_BASE + 16,    /* _H2ASN_MsgChoice MSCC_MMC_PLMN_SPECIAL_REQ_STRU */
    ID_MSCC_MMC_POWER_OFF_REQ                           = ID_MSCC_MMC_MSG_BASE + 18,    /* _H2ASN_MsgChoice MSCC_MMC_POWER_OFF_REQ_STRU */
    ID_MSCC_MMC_SYS_CFG_SET_REQ                         = ID_MSCC_MMC_MSG_BASE + 20,    /* _H2ASN_MsgChoice MSCC_MMC_SYS_CFG_SET_REQ_STRU */
    ID_MSCC_MMC_PLMN_SEARCH_REQ                         = ID_MSCC_MMC_MSG_BASE + 22,    /* _H2ASN_MsgChoice MSCC_MMC_PLMN_SEARCH_REQ_STRU */
    ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ              = ID_MSCC_MMC_MSG_BASE + 24,    /* _H2ASN_MsgChoice MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU */
    ID_MSCC_MMC_OM_MAINTAIN_INFO_IND                    = ID_MSCC_MMC_MSG_BASE + 26,    /* _H2ASN_MsgChoice MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU */


    /* 用户通过CPOL命令更新UPLMN信息通知给MMC */
    ID_MSCC_MMC_UPDATE_UPLMN_NTF                        = ID_MSCC_MMC_MSG_BASE + 28,    /* _H2ASN_MsgChoice MSCC_MMC_UPDATE_UPLMN_NTF_STRU */

    ID_MSCC_MMC_EOPLMN_SET_REQ                          = ID_MSCC_MMC_MSG_BASE + 30,    /* _H2ASN_MsgChoice MSCC_MMC_EOPLMN_SET_REQ_STRU */

    ID_MSCC_MMC_NET_SCAN_REQ                            = ID_MSCC_MMC_MSG_BASE + 32,    /* _H2ASN_MsgChoice MSCC_MMC_NET_SCAN_REQ_STRU */
    ID_MSCC_MMC_ABORT_NET_SCAN_REQ                      = ID_MSCC_MMC_MSG_BASE + 34,    /* _H2ASN_MsgChoice MSCC_MMC_ABORT_NET_SCAN_REQ_STRU */

    ID_MSCC_MMC_OTHER_MODEM_INFO_NOTIFY                 = ID_MSCC_MMC_MSG_BASE + 36,    /* _H2ASN_MsgChoice MSCC_MMC_OTHER_MODEM_INFO_NOTIFY_STRU */

    ID_MSCC_MMC_NCELL_INFO_NOTIFY                       = ID_MSCC_MMC_MSG_BASE + 38,    /* _H2ASN_MsgChoice MSCC_MMC_NCELL_INFO_NOTIFY_STRU */

    ID_MSCC_MMC_PS_TRANSFER_NOTIFY                      = ID_MSCC_MMC_MSG_BASE + 40,    /* _H2ASN_MsgChoice MSCC_MMC_PS_TRANSFER_NOTIFY_STRU */
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-2, begin */
    ID_MSCC_MMC_IMS_VOICE_CAP_NOTIFY                    = ID_MSCC_MMC_MSG_BASE + 42,    /* _H2ASN_MsgChoice MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU */
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-2, end */

    /* Added by s00246516 for L-C互操作项目, 2014-01-26, Begin */
    ID_MSCC_MMC_ACQ_REQ                                 = ID_MSCC_MMC_MSG_BASE + 44,    /* _H2ASN_MsgChoice MSCC_MMC_ACQ_REQ_STRU */
    ID_MSCC_MMC_REG_REQ                                 = ID_MSCC_MMC_MSG_BASE + 46,    /* _H2ASN_MsgChoice MSCC_MMC_REG_REQ_STRU */
    ID_MSCC_MMC_POWER_SAVE_REQ                          = ID_MSCC_MMC_MSG_BASE + 48,    /* _H2ASN_MsgChoice MSCC_MMC_POWER_SAVE_REQ_STRU */
    /* Added by s00246516 for L-C互操作项目, 2014-01-26, End */

    ID_MSCC_MMC_SRV_ACQ_REQ                             = ID_MSCC_MMC_MSG_BASE + 50,    /* _H2ASN_MsgChoice MSCC_MMC_SRV_ACQ_REQ_STRU */
    ID_MSCC_MMC_BEGIN_SESSION_NOTIFY                    = ID_MSCC_MMC_MSG_BASE + 52,    /* _H2ASN_MsgChoice MSCC_MMC_BEGIN_SESSION_NOTIFY_STRU */
    ID_MSCC_MMC_END_SESSION_NOTIFY                      = ID_MSCC_MMC_MSG_BASE + 54,    /* _H2ASN_MsgChoice MSCC_MMC_END_SESSION_NOTIFY_STRU */
    ID_MSCC_MMC_IMS_SRV_INFO_NOTIFY                     = ID_MSCC_MMC_MSG_BASE + 56,    /* _H2ASN_MsgChoice MSCC_MMC_IMS_SRV_INFO_NOTIFY_STRU */
    ID_MSCC_MMC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY     = ID_MSCC_MMC_MSG_BASE + 58,    /* _H2ASN_MsgChoice MSCC_MMC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU */

    ID_MSCC_MMC_CFPLMN_SET_REQ                          = ID_MSCC_MMC_MSG_BASE + 60,    /* _H2ASN_MsgChoice MSCC_MMC_PREF_PLMN_SET_REQ_STRU */
    ID_MSCC_MMC_CFPLMN_QUERY_REQ                        = ID_MSCC_MMC_MSG_BASE + 62,    /* _H2ASN_MsgChoice MSCC_MMC_PREF_PLMN_SET_REQ_STRU */
    ID_MSCC_MMC_SDT_CONNECTED_IND                       = ID_MSCC_MMC_MSG_BASE + 64,    /* _H2ASN_MsgChoice MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU */

    ID_MSCC_MMC_PREF_PLMN_SET_REQ                       = ID_MSCC_MMC_MSG_BASE + 66,    /* _H2ASN_MsgChoice MSCC_MMC_PREF_PLMN_SET_REQ_STRU */
    ID_MSCC_MMC_PREF_PLMN_QUERY_REQ                     = ID_MSCC_MMC_MSG_BASE + 68,    /* _H2ASN_MsgChoice MSCC_MMC_PREF_PLMN_QUERY_REQ_STRU */

    ID_MSCC_MMC_IMS_SWITCH_STATE_IND                    = ID_MSCC_MMC_MSG_BASE + 70,    /* _H2ASN_MsgChoice MSCC_MMC_IMS_SWITCH_STATE_IND_STRU */
    ID_MSCC_MMC_VOICE_DOMAIN_CHANGE_IND                 = ID_MSCC_MMC_MSG_BASE + 72,    /* _H2ASN_MsgChoice MSCC_MMC_VOICE_DOMAIN_CHANGE_IND_STRU */

    ID_MSCC_MMC_BG_SEARCH_REQ                           = ID_MSCC_MMC_MSG_BASE + 74,    /* _H2ASN_MsgChoice MSCC_MMC_BG_SEARCH_REQ_STRU */
    ID_MSCC_MMC_INTERSYS_HRPD_NTF                       = ID_MSCC_MMC_MSG_BASE + 76,    /* _H2ASN_MsgChoice MSCC_MMC_INTERSYS_HRPD_NTF_STRU */
    ID_MSCC_MMC_MMSS_INFO_NTF                           = ID_MSCC_MMC_MSG_BASE + 78,    /* _H2ASN_MsgChoice MSCC_MMC_MMSS_INFO_NTF_STRU */
    ID_MSCC_MMC_STOP_BG_SEARCH_REQ                      = ID_MSCC_MMC_MSG_BASE + 80,    /* _H2ASN_MsgChoice MSCC_MMC_STOP_BG_SEARCH_REQ_STRU */
    ID_MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ                = ID_MSCC_MMC_MSG_BASE + 82,    /* _H2ASN_MsgChoice MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ_STRU */
    ID_MSCC_MMC_AUTO_RESEL_SET_REQ                      = ID_MSCC_MMC_MSG_BASE + 84,    /* _H2ASN_MsgChoice MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ_STRU */

    ID_MSCC_MMC_GET_GEO_REQ                             = ID_MSCC_MMC_MSG_BASE + 86,    /* _H2ASN_MsgChoice MSCC_MMC_GET_GEO_REQ_STRU */
    ID_MSCC_MMC_STOP_GET_GEO_REQ                        = ID_MSCC_MMC_MSG_BASE + 88,    /* _H2ASN_MsgChoice MSCC_MMC_STOP_GET_GEO_REQ_STRU */

    ID_MSCC_MMC_CL_ASSOCIATED_INFO_NTF                  = ID_MSCC_MMC_MSG_BASE + 90,    /* _H2ASN_MsgChoice MSCC_MMC_CL_ASSOCIATED_INFO_NTF_STRU */

    ID_MSCC_MMC_DPLMN_SET_REQ                           = ID_MSCC_MMC_MSG_BASE + 92,    /* _H2ASN_MsgChoice MSCC_MMC_DPLMN_SET_REQ_STRU */

    ID_MSCC_MMC_CSG_LIST_SEARCH_REQ                     = ID_MSCC_MMC_MSG_BASE + 94,    /* _H2ASN_MsgChoice MSCC_MMC_CSG_LIST_SEARCH_REQ_STRU */
    ID_MSCC_MMC_CSG_LIST_ABORT_REQ                      = ID_MSCC_MMC_MSG_BASE + 96,    /* _H2ASN_MsgChoice MSCC_MMC_CSG_LIST_ABORT_REQ_STRU */

    ID_MSCC_MMC_CL_INTERSYS_START_NTF                  = ID_MSCC_MMC_MSG_BASE + 98,    /* _H2ASN_MsgChoice MSCC_MMC_CL_INTERSYS_START_NTF_STRU */

    /* MMC发送给MSCC的消息原语*/
    ID_MMC_MSCC_START_CNF                               = ID_MSCC_MMC_MSG_BASE + 1,     /* _H2ASN_MsgChoice MMC_MSCC_START_CNF_STRU */
    ID_MMC_MSCC_SYS_INFO_IND                            = ID_MSCC_MMC_MSG_BASE + 3,     /* _H2ASN_MsgChoice MMC_MSCC_SYS_INFO_IND_STRU */
    ID_MMC_MSCC_SERVICE_STATUS_IND                      = ID_MSCC_MMC_MSG_BASE + 5,     /* _H2ASN_MsgChoice MMC_MSCC_SERVICE_STATUS_IND_STRU */
    ID_MMC_MSCC_MM_INFO_IND                             = ID_MSCC_MMC_MSG_BASE + 7,     /* _H2ASN_MsgChoice MMC_MSCC_MM_INFO_IND_STRU */
    ID_MMC_MSCC_ATTACH_CNF                              = ID_MSCC_MMC_MSG_BASE + 9,     /* _H2ASN_MsgChoice MMC_MSCC_ATTACH_CNF_STRU */
    ID_MMC_MSCC_DETACH_CNF                              = ID_MSCC_MMC_MSG_BASE + 11,    /* _H2ASN_MsgChoice MMC_MSCC_DETACH_CNF_STRU */
    ID_MMC_MSCC_DETACH_IND                              = ID_MSCC_MMC_MSG_BASE + 13,    /* _H2ASN_MsgChoice MMC_MSCC_DETACH_IND_STRU */
    ID_MMC_MSCC_PLMN_LIST_CNF                           = ID_MSCC_MMC_MSG_BASE + 15,    /* _H2ASN_MsgChoice MMC_MSCC_PLMN_LIST_CNF_STRU */
    ID_MMC_MSCC_PLMN_LIST_REJ                           = ID_MSCC_MMC_MSG_BASE + 17,    /* _H2ASN_MsgChoice MMC_MSCC_PLMN_LIST_REJ_STRU */
    ID_MMC_MSCC_COVERAGE_AREA_IND                       = ID_MSCC_MMC_MSG_BASE + 19,    /* _H2ASN_MsgChoice MMC_MSCC_COVERAGE_AREA_IND_STRU */
    ID_MMC_MSCC_POWER_OFF_CNF                           = ID_MSCC_MMC_MSG_BASE + 21,    /* _H2ASN_MsgChoice MMC_MSCC_POWER_OFF_CNF_STRU */
    ID_MMC_MSCC_RSSI_IND                                = ID_MSCC_MMC_MSG_BASE + 23,    /* _H2ASN_MsgChoice MMC_MSCC_RSSI_IND_STRU */
    ID_MMC_MSCC_PLMN_SPECIAL_SEL_CNF                    = ID_MSCC_MMC_MSG_BASE + 25,    /* _H2ASN_MsgChoice MMC_MSCC_PLMN_SPECIAL_SEL_CNF_STRU */
    ID_MMC_MSCC_DATATRAN_ATTRI_IND                      = ID_MSCC_MMC_MSG_BASE + 27,    /* _H2ASN_MsgChoice MMC_MSCC_DATATRAN_ATTRI_IND_STRU */
    ID_MMC_MSCC_SYS_CFG_CNF                             = ID_MSCC_MMC_MSG_BASE + 29,    /* _H2ASN_MsgChoice MMC_MSCC_SYS_CFG_SET_CNF_STRU */
    ID_MMC_MSCC_PLMN_SELECTION_RLST_IND                 = ID_MSCC_MMC_MSG_BASE + 31,    /* _H2ASN_MsgChoice MMC_MSCC_PLMN_SELECTION_RLST_IND_STRU */
    ID_MMC_MSCC_PLMN_LIST_ABORT_CNF                     = ID_MSCC_MMC_MSG_BASE + 33,    /* _H2ASN_MsgChoice MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU */
    ID_MMC_MSCC_SPEC_PLMN_SEARCH_ABORT_CNF              = ID_MSCC_MMC_MSG_BASE + 35,    /* _H2ASN_MsgChoice MMC_MSCC_SPEC_PLMN_SEARCH_ABORT_CNF_STRU */
    ID_MMC_MSCC_UMTS_CIPHER_INFO_IND                    = ID_MSCC_MMC_MSG_BASE + 37,    /* _H2ASN_MsgChoice MMC_MSCC_UMTS_CIPHER_INFO_IND_STRU */
    ID_MMC_MSCC_GPRS_CIPHER_INFO_IND                    = ID_MSCC_MMC_MSG_BASE + 39,    /* _H2ASN_MsgChoice MMC_MSCC_GPRS_CIPHER_INFO_IND_STRU */
    ID_MMC_MSCC_PLMN_SPECIAL_SEL_REJ                    = ID_MSCC_MMC_MSG_BASE + 41,    /* _H2ASN_MsgChoice MMC_MSCC_PLMN_SPECIAL_SEL_REJ_STRU */
    ID_MMC_MSCC_AC_INFO_CHANGE_IND                      = ID_MSCC_MMC_MSG_BASE + 43,    /* _H2ASN_MsgChoice MMC_MSCC_AC_INFO_CHANGE_IND_STRU */
    ID_MMC_MSCC_PLMN_RESEL_CNF                          = ID_MSCC_MMC_MSG_BASE + 45,    /* _H2ASN_MsgChoice MMC_MSCC_PLMN_RESEL_CNF_STRU */
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
    ID_MMC_MSCC_REG_RESULT_IND                          = ID_MSCC_MMC_MSG_BASE + 47,    /* _H2ASN_MsgChoice  MMC_MSCC_REG_RESULT_IND_STRU */
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */

    ID_MMC_MSCC_PLMN_SELE_START_IND                     = ID_MSCC_MMC_MSG_BASE + 49,    /* _H2ASN_MsgChoice  MMC_MSCC_PLMN_SELECTION_START_IND_STRU */

    ID_MMC_MSCC_EOPLMN_SET_CNF                          = ID_MSCC_MMC_MSG_BASE + 51,    /* _H2ASN_MsgChoice  MMC_MSCC_EOPLMN_SET_CNF_STRU */
    ID_MMC_MSCC_USIM_AUTH_FAIL_IND                      = ID_MSCC_MMC_MSG_BASE + 53,    /* _H2ASN_MsgChoice  MMC_MSCC_USIM_AUTH_FAIL_IND_STRU */

    ID_MMC_MSCC_NET_SCAN_CNF                            = ID_MSCC_MMC_MSG_BASE + 55,    /* _H2ASN_MsgChoice  MMC_MSCC_NET_SCAN_CNF_STRU */
    ID_MMC_MSCC_ABORT_NET_SCAN_CNF                      = ID_MSCC_MMC_MSG_BASE + 57,    /* _H2ASN_MsgChoice  MMC_MSCC_ABORT_NET_SCAN_CNF_STRU */

    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-9, begin */
    ID_MMC_MSCC_NETWORK_CAPABILITY_INFO_IND             = ID_MSCC_MMC_MSG_BASE + 59,    /* _H2ASN_MsgChoice MMC_MSCC_NETWORK_CAPABILITY_INFO_IND_STRU */
    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-9, end */
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
    ID_MMC_MSCC_CAMP_ON_IND                             = ID_MSCC_MMC_MSG_BASE + 61,    /* _H2ASN_MsgChoice MMC_MSCC_CAMP_ON_IND_STRU_STRU */
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

    ID_MMC_MSCC_EPLMN_INFO_IND                          = ID_MSCC_MMC_MSG_BASE + 63,    /* _H2ASN_MsgChoice MMC_MSCC_EPLMN_INFO_IND_STRU */

    ID_MMC_MSCC_CS_SERVICE_CONN_STATUS_IND              = ID_MSCC_MMC_MSG_BASE + 65,    /* _H2ASN_MsgChoice MMC_MSCC_CS_SERVICE_CONN_STATUS_IND_STRU */

    ID_MMC_MSCC_SRV_REJ_IND                             = ID_MSCC_MMC_MSG_BASE + 67,    /* _H2ASN_MsgChoice MMC_MSCC_SERV_REJ_IND_STRU */
    /* Added by s00246516 for L-C互操作项目, 2014-01-26, Begin */
    ID_MMC_MSCC_ACQ_CNF                                 = ID_MSCC_MMC_MSG_BASE + 69,    /* _H2ASN_MsgChoice MMC_MSCC_ACQ_CNF_STRU */
    ID_MMC_MSCC_REG_CNF                                 = ID_MSCC_MMC_MSG_BASE + 71,    /* _H2ASN_MsgChoice MMC_MSCC_REG_CNF_STRU */
    ID_MMC_MSCC_POWER_SAVE_CNF                          = ID_MSCC_MMC_MSG_BASE + 73,    /* _H2ASN_MsgChoice MMC_MSCC_POWER_SAVE_CNF_STRU */
    ID_MMC_MSCC_ACQ_IND                                 = ID_MSCC_MMC_MSG_BASE + 75,    /* _H2ASN_MsgChoice MMC_MSCC_ACQ_IND_STRU */
    /* Added by s00246516 for L-C互操作项目, 2014-01-26, End */


    /* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, Begin */
    ID_MMC_MSCC_PS_SERVICE_CONN_STATUS_IND              = ID_MSCC_MMC_MSG_BASE + 77,    /* _H2ASN_MsgChoice MMC_MSCC_PS_SERVICE_CONN_STATUS_IND_STRU */
    /* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, End */
    ID_MMC_MSCC_RF_AVAILABLE_IND                        = ID_MSCC_MMC_MSG_BASE + 79,    /* _H2ASN_MsgChoice MMC_MSCC_RF_AVAILABLE_IND_STRU */
    ID_MMC_MSCC_SRV_ACQ_CNF                             = ID_MSCC_MMC_MSG_BASE + 81,    /* _H2ASN_MsgChoice MMC_MSCC_SRV_ACQ_CNF_STRU */
    ID_MMC_MSCC_LMM_CELL_SIGN_INFO_REPORT_IND           = ID_MSCC_MMC_MSG_BASE + 83,    /* _H2ASN_MsgChoice MMC_MSCC_LMM_CELL_SIGN_INFO_REPORT_IND_STRU */

    ID_MMC_MSCC_CFPLMN_SET_CNF                          = ID_MSCC_MMC_MSG_BASE + 87,    /* _H2ASN_MsgChoice MMC_MSCC_PREF_PLMN_SET_CNF_STRU */
    ID_MMC_MSCC_CFPLMN_QUERY_CNF                        = ID_MSCC_MMC_MSG_BASE + 89,    /* _H2ASN_MsgChoice MMC_MSCC_PREF_PLMN_SET_CNF_STRU */
    ID_MMC_MSCC_PREF_PLMN_SET_CNF                       = ID_MSCC_MMC_MSG_BASE + 91,    /* _H2ASN_MsgChoice MMC_MSCC_PREF_PLMN_SET_CNF_STRU */
    ID_MMC_MSCC_PREF_PLMN_QUERY_CNF                     = ID_MSCC_MMC_MSG_BASE + 93,    /* _H2ASN_MsgChoice MMC_MSCC_PREF_PLMN_QUERY_CNF_STRU */

    ID_MMC_MSCC_BG_SEARCH_CNF                           = ID_MSCC_MMC_MSG_BASE + 95,    /* _H2ASN_MsgChoice MMC_MSCC_BG_SEARCH_CNF_STRU */
    ID_MMC_MSCC_STOP_BG_SEARCH_CNF                      = ID_MSCC_MMC_MSG_BASE + 97,    /* _H2ASN_MsgChoice MMC_MSCC_STOP_BG_SEARCH_CNF_STRU */
    ID_MMC_MSCC_PREF_PLMN_INFO_IND                      = ID_MSCC_MMC_MSG_BASE + 99,    /* _H2ASN_MsgChoice MMC_MSCC_PREF_PLMN_INFO_IND_STRU */
    ID_MMC_MSCC_MMSS_LTE_UNAVAILABLE_IND                = ID_MSCC_MMC_MSG_BASE + 101,   /* _H2ASN_MsgChoice MMC_MSCC_MMSS_LTE_UNAVAILABLE_IND_STRU */
    ID_MMC_MSCC_PLMN_PRI_CLASS_QUERY_CNF                = ID_MSCC_MMC_MSG_BASE + 103,   /* _H2ASN_MsgChoice MMC_MSCC_PLMN_PRI_CLASS_QUERY_CNF_STRU */
    ID_MMC_MSCC_GET_GEO_CNF                             = ID_MSCC_MMC_MSG_BASE + 105,   /* _H2ASN_MsgChoice MMC_MSCC_GET_GEO_CNF_STRU */
    ID_MMC_MSCC_STOP_GET_GEO_CNF                        = ID_MSCC_MMC_MSG_BASE + 107,   /* _H2ASN_MsgChoice MMC_MSCC_STOP_GET_GEO_CNF_STRU */
    ID_MMC_MSCC_SRCHED_PLMN_INFO_IND                    = ID_MSCC_MMC_MSG_BASE + 109,   /* MMC_MSCC_SRCHED_PLMN_INFO_IND_STRU */

    ID_MMC_MSCC_DPLMN_SET_CNF                           = ID_MSCC_MMC_MSG_BASE + 111,   /* _H2ASN_MsgChoice MMC_MSCC_DPLMN_SET_CNF_STRU */

    ID_MMC_MSCC_INTERSYS_START_IND                      = ID_MSCC_MMC_MSG_BASE + 113,   /* MMC_MSCC_INTERSYS_START_IND_STRU */
    ID_MMC_MSCC_INTERSYS_END_IND                        = ID_MSCC_MMC_MSG_BASE + 115,   /* MMC_MSCC_INTERSYS_END_IND_STRU */

    ID_MMC_MSCC_CSG_LIST_SEARCH_CNF                     = ID_MSCC_MMC_MSG_BASE + 117,   /* _H2ASN_MsgChoice MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU */
    ID_MMC_MSCC_CSG_LIST_ABORT_CNF                      = ID_MSCC_MMC_MSG_BASE + 119,   /* _H2ASN_MsgChoice MMC_MSCC_CSG_LIST_ABORT_CNF_STRU */
    ID_MMC_MSCC_CSG_LIST_REJ                            = ID_MSCC_MMC_MSG_BASE + 121,   /* _H2ASN_MsgChoice MMC_MSCC_CSG_LIST_REJ_STRU */

    ID_MSCC_PIF_MSG_TYPE_BUTT
};

typedef VOS_UINT32 MSCC_PIF_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8
 枚举说明  : NAS_MSCC_PIF_START_REQ_STRU消息中的 ulCardStatus
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_CARD_STATUS_ENUM
{
    NAS_MSCC_PIF_CARD_STATUS_SIM_PRESENT      = 0,                              /* sim present */
    NAS_MSCC_PIF_CARD_STATUS_USIM_PRESENT     = 1,                              /* usim present */
    NAS_MSCC_PIF_CARD_STATUS_UIM_PRESENT      = 2,
    NAS_MSCC_PIF_CARD_STATUS_CSIM_PRESENT     = 3,
    NAS_MSCC_PIF_CARD_STATUS_ABSENT           = 4,                              /* card absent */
    NAS_MSCC_PIF_CARD_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_BAND_CLASS_ENUM
 结构说明  : List of Band Classes (参考3GPP2 C.S0057-E中Table 1.5-1: )

 1.日    期   : 2015年05月16日
   作    者   : W00176964
   修改内容   : 新增

*****************************************************************************/
enum NAS_MSCC_PIF_BAND_CLASS_ENUM
{
    NAS_MSCC_PIF_BAND_CLASS_TYPE_0                              = 0,    /* 800 MHz cellular band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_1                              = 1,    /* 1.8 to 2.0 GHz PCS band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_2                              = 2,    /* 872 to 960 MHz TACS band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_3                              = 3,    /* 832 to 925 MHz JTACS band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_4                              = 4,    /* 1.75 to 1.87 GHz Korean PCS band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_5                              = 5,    /* 450 MHz NMT band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_6                              = 6,    /* 2 GHz IMT-2000 band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_7                              = 7,    /* 700 MHz band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_8                              = 8,    /* 1800 MHz band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_9                              = 9,    /* 900 MHz band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_10                             = 10,   /* Secondary 800 MHz band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_11                             = 11,   /* 400 MHz European PAMR band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_12                             = 12,   /* 800 MHz PAMR band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_13                             = 13,   /* 2.5 GHz IMT-2000 Extension Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_14                             = 14,   /* US PCS 1.9GHz Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_15                             = 15,   /* AWS Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_16                             = 16,   /* US 2.5GHz Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_17                             = 17,   /* US 2.5GHz Forward Link Only Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_18                             = 18,   /* 700 MHz Public Safety Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_19                             = 19,   /* Lower 700 MHz Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_20                             = 20,   /* L-Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_21                             = 21,   /* S-Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_31                             = 31,   /* Wildcard Band Class */

    NAS_MSCC_PIF_BAND_CLASS_BUTT
};
typedef VOS_UINT16 NAS_MSCC_PIF_BAND_CLASS_ENUM_UINT16;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_PREF_NEG_SYS_ENUM
 结构说明  : Preferred/negative system

 1.日    期   : 2015年05月16日
   作    者   : W00176964
   修改内容   : 新增

*****************************************************************************/
enum NAS_MSCC_PIF_PREF_NEG_SYS_ENUM
{
    NAS_MSCC_PIF_PREF_NEG_SYS_NEG                               = 0, /* This field is set to '0' if the mobile station is
                                                                                    not allowed to operate on the system associated
                                                                                    with this record */
    NAS_MSCC_PIF_PREF_NEG_SYS_PREF                              = 1, /* This field is set to ‘1’ if the mobile station
                                                                                    is allowed to operate on the system associated with
                                                                                    this record */
    NAS_MSCC_PIF_PREF_NEG_SYS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_PREF_NEG_SYS_ENUM_UINT8;


/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_PLMN_STATUS_ENUM
 结构说明  : PLMN 状态 用于AT的上报网络状态
 1.日    期   : 2012年4月7日
   作    者   : z00161729
   修改内容   : 新增
*****************************************************************************/
enum NAS_MSCC_PIF_PLMN_STATUS_ENUM
{
    NAS_MSCC_PIF_PLMN_STATUS_UNKNOW           = 0,                                    /* 当前网络状态未知 */
    NAS_MSCC_PIF_PLMN_STATUS_AVAILIBLE        = 1,                                    /* 当前网络可用 */
    NAS_MSCC_PIF_PLMN_STATUS_CURRENT          = 2,                                    /* 当前网络已注册 */
    NAS_MSCC_PIF_PLMN_STATUS_FORBIDDEN        = 3,                                    /* 当前网络禁止 */
    NAS_MSCC_PIF_PLMN_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_PLMN_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8
 结构说明  : 当前的接入技术
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_NET_RAT_TYPE_ENUM
{
    NAS_MSCC_PIF_NET_RAT_TYPE_GSM,           /* GSM接入技术 */
    NAS_MSCC_PIF_NET_RAT_TYPE_WCDMA,         /* WCDMA接入技术 */
    NAS_MSCC_PIF_NET_RAT_TYPE_LTE,           /* LTE接入技术 */
    NAS_MSCC_PIF_NET_RAT_TYPE_1X,            /* 1X接入技术 */
    NAS_MSCC_PIF_NET_RAT_TYPE_HRPD,          /* 1X接入技术 */
    NAS_MSCC_PIF_NET_RAT_TYPE_BUTT           /* 无效的接入技术 */
};
typedef VOS_UINT8 NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_REG_STATE_ENUM_UINT8
 结构说明  : 注册结果
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_REG_STATE_ENUM
{
    NAS_MSCC_PIF_REG_NOT_REGISTERED_NOT_SEARCH,      /* 未注册未搜索 */
    NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK,        /* 注册，注册在 HOME PLMN */
    NAS_MSCC_PIF_REG_NOT_REGISTERED_SEARCHING,       /* 未注册，正在搜索PLMN或者正在附着过程 */
    NAS_MSCC_PIF_REG_REGISTERED_DENIED,              /* 注册被拒绝，当前用户不可以启动注册，启动服务被禁止 */
    NAS_MSCC_PIF_REG_UNKNOWN,                        /* 其余情况 */
    NAS_MSCC_PIF_REG_REGISTERED_ROAM,                /* 注册，注册在非 HOME PLMN */
    NAS_MSCC_PIF_REG_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_REG_STATE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM_UINT32
 结构说明  : 关机原因值
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM
{
    NAS_MSCC_PIF_POWER_OFF_CAUSE_SIM_REMOVE,
    NAS_MSCC_PIF_POWER_OFF_CAUSE_NORMAL,
    NAS_MSCC_PIF_POWER_OFF_CAUSE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_ROAM_CAPABILITY_ENUM_UINT8
 结构说明  : 漫游能力
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_ROAM_CAPABILITY_ENUM
{
    NAS_MSCC_PIF_ROAM_NATION_ON_INTERNATION_ON                 = 0,
    NAS_MSCC_PIF_ROAM_NATION_ON_INTERNATION_OFF                = 1,
    NAS_MSCC_PIF_ROAM_NATION_OFF_INTERNATION_ON                = 2,
    NAS_MSCC_PIF_ROAM_NATION_OFF_INTERNATION_OFF               = 3,
    NAS_MSCC_PIF_ROAM_UNCHANGE                                 = 4,
    NAS_MSCC_PIF_ROAM_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_ROAM_CAPABILITY_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_ROAM_FEATURE_ENUM_U8
 结构说明  : 漫游能力
 1.日    期   : 2014年4月7日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_ROAM_FEATURE_ENUM
{
    NAS_MSCC_PIF_ROAM_FEATURE_OFF                = 0,
    NAS_MSCC_PIF_ROAM_FEATURE_ON                 = 1,
    NAS_MSCC_PIF_ROAM_FEATURE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_ROAM_FEATURE_ENUM_U8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_PLMN_SELECTION_RESULT_ENUM
 结构说明  : 搜网结果
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新增
 2.日    期   : 2015年08月25日
   作    者   : m00312079
   修改内容   : DTS2015082004682:增加L2C原因值
*****************************************************************************/
enum NAS_MSCC_PIF_PLMN_SELECTION_RESULT_ENUM
{
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NORMAL_SERVICE    = 0,                        /* 正常服务 */
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_LIMITED_SERVICE   = 1,                        /* 限制服务 */
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NO_SERVICE        = 2,                        /* 无服务 */
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_INTERRUPT         = 3,                        /* 搜网被中断 */
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NO_RF             = 4,
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_L2C               = 5,                        /* CL互操作L2C */
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_PLMN_SELECTION_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_PLMN_SELECTION_START_FLAG_ENUM
 结构说明  : 搜网开始或搜网结束标示
 1.日    期   : 2013年10月09日
   作    者   : l00208543
   修改内容   : 新增 DTS2013100904573
*****************************************************************************/
enum NAS_MSCC_PIF_PLMN_SELECTION_START_FLAG_ENUM
{
    NAS_MSCC_PIF_PLMN_SELECTION_START    = 0,                        /* 搜网开始 */
    NAS_MSCC_PIF_PLMN_SELECTION_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_PLMN_SELECTION_START_FLAG_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_SYS_CFG_SET_RESULT_ENUM_UINT32
 结构说明  : syscfg设置结果信息
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
enum NAS_MSCC_PIF_SYS_CFG_SET_RESULT_ENUM
{
    NAS_MSCC_PIF_SYS_CFG_SET_SUCCESS                  = 0,
    NAS_MSCC_PIF_SYS_CFG_SET_FAILURE_OTHER            = 1,
    NAS_MSCC_PIF_SYS_CFG_SET_FAILURE_CS_SERV_EXIST    = 2,
    NAS_MSCC_PIF_SYS_CFG_SET_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_SYS_CFG_SET_RESULT_ENUM_UINT32;

/******************************************************************************
结构名    : NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_ENUM_UINT8
结构说明  : 小区接入禁止信息枚举类型
1.日    期: 2013年3月25日
  作    者: z00161729
  修改内容: 新增
******************************************************************************/
enum  NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_ENUM
{
    NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_NONE                   = 0,                   /* 当前小区不限制任何业务 */
    NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_NORMAL_SERVICE         = 1,                   /* 当前小区限制正常业务 */
    NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_EMERGENCY_SERVICE      = 2,                   /* 当前小区限制紧急业务 */
    NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_ALL_SERVICE            = 3,                   /* 当前小区限制正常业务和紧急业务 */
    NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_BUTT
};
typedef VOS_UINT8   NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_ATTACH_TYPE_ENUM_UINT32
 结构说明  : attach类型
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
enum NAS_MSCC_PIF_ATTACH_TYPE_ENUM
{
    NAS_MSCC_PIF_ATTACH_TYPE_GPRS          = 1,
    NAS_MSCC_PIF_ATTACH_TYPE_IMSI          = 2,
    NAS_MSCC_PIF_ATTACH_TYPE_GPRS_IMSI     = 3,
    NAS_MSCC_PIF_ATTACH_TYPE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_ATTACH_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_DETACH_TYPE_ENUM_UINT32
 结构说明  : detach类型
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
enum NAS_MSCC_PIF_DETACH_TYPE_ENUM
{
    NAS_MSCC_PIF_DETACH_NULL               = 0,
    NAS_MSCC_PIF_DETACH_TYPE_GPRS          = 1,
    NAS_MSCC_PIF_DETACH_TYPE_IMSI          = 2,
    NAS_MSCC_PIF_DETACH_TYPE_GPRS_IMSI     = 3,
    NAS_MSCC_PIF_DETACH_TYPE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_DETACH_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_PLMN_CFG_MODE_ENUM_UINT32
 结构说明  : NAS_MSCC_PIF_PLMN_USER_SEL_REQ_STRU中ulMode取值
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
enum NAS_MSCC_PIF_PLMN_CFG_MODE_ENUM
{
    NAS_MSCC_PIF_PLMN_CFG_MODE_USER_SEL           = 1,                               /* 通知用户选定的PLMN信息 */
    NAS_MSCC_PIF_PLMN_CFG_MODE_USER_RESEL         = 2,                               /* 触发PLMN的User reselection */
    NAS_MSCC_PIF_PLMN_CFG_MODE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_PLMN_CFG_MODE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_PLMN_SEL_MODE_ENUM_UINT32
 结构说明  : 搜网模式
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
enum NAS_MSCC_PIF_PLMN_SEL_MODE_ENUM
{
    NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO           = 0,                                   /* 自动搜网模式 */
    NAS_MSCC_PIF_PLMN_SEL_MODE_MANUAL         = 1,                                   /* 手动搜网模式 */
    NAS_MSCC_PIF_PLMN_SEL_MODE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_PLMN_SEL_MODE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_ENUM_UINT32
 结构说明  : 覆盖区改变模式：丢失、进入
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
enum NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_ENUM
{
    NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST          = 0,                        /* 出覆盖区 */
    NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_ENTER         = 1,                        /* 进覆盖区 */
    NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_MS_MODE_ENUM_UINT32
 结构说明  : 手机模式
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
enum NAS_MSCC_PIF_MS_MODE_ENUM
{
    NAS_MSCC_PIF_MS_MODE_CC                  = 0,                                    /* cs mode */
    NAS_MSCC_PIF_MS_MODE_CG                  = 1,                                    /* ps mode */
    NAS_MSCC_PIF_MS_MODE_A                   = 2,                                    /* cs ps mode */
    NAS_MSCC_PIF_MS_MODE_B                   = 4,                                    /* mode B */
    NAS_MSCC_PIF_MS_MODE_NULL                = 5,                                    /* mode null */
    NAS_MSCC_PIF_MS_MODE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_MS_MODE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32
 结构说明  : 服务状态
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
enum NAS_MSCC_PIF_SERVICE_STATUS_ENUM
{
    NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE           = 0,                        /* 正常服务 */
    NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE          = 1,                        /* 限制服务 */
    NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE_REGION   = 2,                        /* 有限制区域服务 */
    NAS_MSCC_PIF_SERVICE_STATUS_NO_IMSI                  = 3,                        /* 无imsi */
    NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE               = 4,                        /* 无服务 */
    NAS_MSCC_PIF_SERVICE_STATUS_NO_CHANGE                = 5,
    NAS_MSCC_PIF_SERVICE_STATUS_DEEP_SLEEP               = 6,
    NAS_MSCC_PIF_SERVICE_STATUS_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_OPERATION_STATUS_ENUM_UINT32
 结构说明  : 操作是否允许
 1.日    期: 2015年12月23日
   作    者: j00174725
   修改内容: 新增
*****************************************************************************/
enum NAS_MSCC_PIF_OPER_RESULT_ENUM
{
    NAS_MSCC_PIF_OPER_RESULT_SUCCESS               = 0,                         /* 操作成功 */
    NAS_MSCC_PIF_OPER_RESULT_FAILURE               = 1,                         /* 操作失败 */
    NAS_MSCC_PIF_OPER_RESULT_REJECT                = 2,                         /* 不允许进行该操作 */
    NAS_MSCC_PIF_OPER_RESULT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_OPER_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32
 结构说明  : 服务域
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
enum NAS_MSCC_PIF_SRVDOMAIN_ENUM
{
    NAS_MSCC_PIF_SRVDOMAIN_NO_DOMAIN               = 0,
    NAS_MSCC_PIF_SRVDOMAIN_CS                      = 1,
    NAS_MSCC_PIF_SRVDOMAIN_PS                      = 2,
    NAS_MSCC_PIF_SRVDOMAIN_CS_PS                   = 3,
    NAS_MSCC_PIF_SRVDOMAIN_NO_CHANGE               = 4,
    NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING  = 5,
    NAS_MSCC_PIF_SRVDOMAIN_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32;


/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_DATATRAN_ATTRI_ENUM_UINT8
 结构说明  : pdp激活情况
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
enum NAS_MSCC_PIF_DATATRAN_ATTRI_ENUM
{
    NAS_MSCC_PIF_DATATRAN_ATTRI_PDP_ACT          = 0,
    NAS_MSCC_PIF_DATATRAN_ATTRI_PDP_DEACT        = 1,
    NAS_MSCC_PIF_DATATRAN_ATTRI_R99_ONLY         = 2,
    NAS_MSCC_PIF_DATATRAN_ATTRI_HSDPA            = 3,
    NAS_MSCC_PIF_DATATRAN_ATTRI_HSUPA            = 4,
    NAS_MSCC_PIF_DATATRAN_ATTRI_HSDPA_AND_HSUPA  = 5,
    NAS_MSCC_PIF_DATATRAN_ATTRI_HSPA_PLUS        = 6,
    NAS_MSCC_PIF_DATATRAN_ATTRI_LTE_DATA         = 7,
    NAS_MSCC_PIF_DATATRAN_ATTRI_LTE_IDLE         = 8,
    NAS_MSCC_PIF_DATATRAN_ATTRI_DC_HSPA_PLUS     = 9,
    NAS_MSCC_PIF_DATATRAN_ATTRI_DC_MIMO          = 10,
    NAS_MSCC_PIF_DATATRAN_ATTRI_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_DATATRAN_ATTRI_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM_UINT8
 结构说明  : 开机请求中允许注册的服务域
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
enum NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM
{
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_NULL     = 0,                                    /* 不注册cs和ps */
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_PS       = 1,                                    /* 只注册PS */
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_CS       = 2,                                    /* 只注册CS */
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_CS_PS    = 3,                                    /* 注册CS+PS */
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_ENUM_UINT8
 结构说明  : 用户指定搜网结果
 1.日    期: 2013年4月7日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
enum NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_ENUM
{
    NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_SUCCESS = 0,                                /* 成功 */
    NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL    = 1,                                /* 失败 */
    NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_REJ     = 2,
    NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_PLMN_WITH_CSG_ID_TYPE_ENUM_UINT8
 结构说明  : CSG ID类型
1.日    期   : 2015年9月6日
  作    者   : z00161729
  修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
enum NAS_MSCC_PIF_PLMN_WITH_CSG_ID_TYPE_ENUM
{
    NAS_MSCC_PIF_CSG_ID_TYPE_IN_ALLOWED_CSG_LIST                  = 1,  /* CSG ID在Allowed CSG List中*/
    NAS_MSCC_PIF_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN    = 2,  /* CSG ID在Operator CSG List中不在禁止CSG ID列表中 */
    NAS_MSCC_PIF_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_FOBIDDEN        = 3,  /* CSG ID在Operator CSG List中并且在禁止CSG ID列表中*/
    NAS_MSCC_PIF_CSG_ID_TYPE_NOT_IN_ALLOWED_AND_OPERATOR_CSG_LIST = 4,  /* CSG ID不在Allowed CSG List和Operator CSG List中*/
    NAS_MSCC_PIF_CSG_ID_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_PLMN_WITH_CSG_ID_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_NW_IMS_VOICE_CAP_ENUM
 结构说明  : 网络的IMS voice支持能力
 1.日    期: 2013年7月9日
   作    者: y00245242
   修改内容: 新增
*****************************************************************************/
enum NAS_MSCC_PIF_NW_IMS_VOICE_CAP_ENUM
{
    NAS_MSCC_PIF_NW_IMS_VOICE_NOT_SUPPORTED    = 0,
    NAS_MSCC_PIF_NW_IMS_VOICE_SUPPORTED        = 1,

    NAS_MSCC_PIF_NW_IMS_VOICE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_NW_IMS_VOICE_CAP_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_NW_EMC_BS_CAP_ENUM
 结构说明  : 网络的EMC BS支持能力
 1.日    期: 2013年7月9日
   作    者: y00245242
   修改内容: 新增
*****************************************************************************/
enum NAS_MSCC_PIF_NW_EMC_BS_CAP_ENUM
{
    NAS_MSCC_PIF_NW_EMC_BS_NOT_SUPPORTED       = 0,
    NAS_MSCC_PIF_NW_EMC_BS_SUPPORTED           = 1,

    NAS_MSCC_PIF_NW_EMC_BS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_NW_EMC_BS_CAP_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_LTE_CS_CAPBILITY_ENUM
 结构说明  : LTE CS能力
 1.日    期: 2013年7月9日
   作    者: y00245242
   修改内容: 新增
*****************************************************************************/
enum NAS_MSCC_PIF_LTE_CS_CAPBILITY_ENUM
{
    NAS_MSCC_PIF_LTE_CS_CAPBILITY_NO_ADDITION_INFO  = 0,
    NAS_MSCC_PIF_LTE_CS_CAPBILITY_CSFB_NOT_PREFER   = 1,
    NAS_MSCC_PIF_LTE_CS_CAPBILITY_SMS_ONLY          = 2,
    NAS_MSCC_PIF_LTE_CS_CAPBILITY_NOT_SUPPORTED     = 3,

    NAS_MSCC_PIF_LTE_CS_CAPBILITY_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_LTE_CS_CAPBILITY_ENUM_UINT8;

/*****************************************************************************
    枚举名    : NAS_MSCC_PIF_IMS_NORMAL_REG_STATUS_ENUM
    枚举说明  : ims的普通注册状态
  1.日    期: 2013年12月16日
    作    者: w00176964
    修改内容: 新增
*****************************************************************************/
enum NAS_MSCC_PIF_IMS_NORMAL_REG_STATUS_ENUM
{
    NAS_MSCC_PIF_IMS_NORMAL_REG_STATUS_DEREG        = 0x00,
    NAS_MSCC_PIF_IMS_NORMAL_REG_STATUS_DEREGING     = 0x01,
    NAS_MSCC_PIF_IMS_NORMAL_REG_STATUS_REGING       = 0x02,
    NAS_MSCC_PIF_IMS_NORMAL_REG_STATUS_REG          = 0x03,

    NAS_MSCC_PIF_IMS_NORMAL_REG_STATUS_BUTT         = 0xFF
};
typedef VOS_UINT8 NAS_MSCC_PIF_IMS_NORMAL_REG_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_U8
 结构说明  : 当前的接入技术
 1.日    期   : 2014年1月2日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_REG_CONTROL_ENUM
{
    NAS_MSCC_PIF_REG_CONTROL_BY_3GPP_MMC = 0,                 /* 搜索到网络后，是否注册按目前3GPP协议模块MMC控制 */
    NAS_MSCC_PIF_REG_CONTROL_BY_3GPP2_CBP,                    /*搜索到网络后，是否注册由3GPP2协议CDMA Baseband Protocol控制 */
    NAS_MSCC_PIF_REG_CONTROL_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_REG_CONTROL_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_3GPP2_RAT_TYPE_ENUM_UINT8
 结构说明  : 当前的接入技术
 1.日    期   : 2014年1月2日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_3GPP2_RAT_TYPE_ENUM
{
    NAS_MSCC_PIF_3GPP2_RAT_TYPE_CDMA1X = 0,
    NAS_MSCC_PIF_3GPP2_RAT_TYPE_HRPD,
    NAS_MSCC_PIF_3GPP2_RAT_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_3GPP2_RAT_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_EPS_ATTACH_REASON_ENUM
 结构说明  : 发起EPS注册的原因枚举
 1.日    期   : 2014年1月2日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_EPS_ATTACH_REASON_ENUM
{
    NAS_MSCC_PIF_EPS_ATTACH_REASON_INITIAL          = 0,
    NAS_MSCC_PIF_EPS_ATTACH_REASON_HANDOVER         = 1,
    NAS_MSCC_PIF_EPS_ATTACH_REASON_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_EPS_ATTACH_REASON_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_DETACH_REASON_ENUM
 结构说明  : 发起EPS去注册的原因枚举
 1.日    期   : 2014年1月2日
   作    者   : s00246516
   修改内容   : 新建
 2.日    期   : 2015年4月11日
   作    者   : y00245242
   修改内容   : iteration 13开发
*****************************************************************************/
enum NAS_MSCC_PIF_DETACH_REASON_ENUM
{
    NAS_MSCC_PIF_DETACH_REASON_USER_DETACH          = 0,/* 用户触发的detach操作 */
    NAS_MSCC_PIF_DETACH_REASON_RAT_OR_BAND_DETACH   = 1,/* system configure中RAT或band触发的detach */
    NAS_MSCC_PIF_DETACH_REASON_SRV_DOMAIN_DETACH    = 2,/* system configure中服务域触发的detach */
    NAS_MSCC_PIF_DETACH_REASON_3GPP2_ATTACHED       = 3,/* 3GPP2触发的attach */
    NAS_MSCC_PIF_DETACH_REASON_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_DETACH_REASON_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM
 结构说明  : PLMN的优先级类别
 1.日    期   : 2014年1月2日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM
{
    NAS_MSCC_PIF_PLMN_PRIORITY_HOME               = 0,    /* home or ehome plmn */
    NAS_MSCC_PIF_PLMN_PRIORITY_PREF               = 1,    /* UPLMN or OPLMN */
    NAS_MSCC_PIF_PLMN_PRIORITY_ANY                = 2,    /* Acceptable PLMN */
    NAS_MSCC_PIF_PLMN_PRIORITY_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_ACQ_REASON_ENUM
 结构说明  : 获取原因
 1.日    期   : 2014年1月2日
   作    者   : s00246516
   修改内容   : 新建
 2.日    期   : 2015年5月12日
   作    者   : w00176964
   修改内容   : CDMA 1X Iteration 10调整
*****************************************************************************/
enum NAS_MSCC_PIF_ACQ_REASON_ENUM
{
    NAS_MSCC_PIF_ACQ_REASON_POWER_UP        = 0,
    NAS_MSCC_PIF_ACQ_REASON_HIGH_PRIORITY   = 1,
    NAS_MSCC_PIF_ACQ_REASON_OTHER           = 2,
    NAS_MSCC_PIF_ACQ_REASON_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_ACQ_REASON_ENUM_UINT32;


/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_ACQ_RESULT_ENUM
 结构说明  : 获取结果枚举
 1.日    期   : 2014年1月2日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_ACQ_RESULT_ENUM
{
    NAS_MSCC_PIF_ACQ_RESULT_SUCCESS          = 0,
    NAS_MSCC_PIF_ACQ_RESULT_FAILURE          = 1,
    NAS_MSCC_PIF_ACQ_RESULT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_ACQ_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_REG_RESULT_ENUM
 结构说明  : 注册结果枚举
 1.日    期   : 2014年1月2日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_REG_RESULT_ENUM
{
    NAS_MSCC_PIF_REG_RESULT_SUCCESS          = 0,
    NAS_MSCC_PIF_REG_RESULT_ACQ_FAILURE      = 1,
    NAS_MSCC_PIF_REG_RESULT_REG_FAILURE      = 2,
    NAS_MSCC_PIF_REG_RESULT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_REG_RESULT_ENUM_UINT32;


/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_CALL_MODE_ENUM
 结构说明  : 呼叫模式枚举
 1.日    期   : 2014年4月1日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_CALL_MODE_ENUM
{
    NAS_MSCC_PIF_ECALL_ONLY            = 0,
    NAS_MSCC_PIF_ECALL_AND_NORMAL_CALL = 1,
    NAS_MSCC_PIF_ECALL_MODE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_CALL_MODE_ENUM_UINT8;

/*****************************************************************************
 结构名称: NAS_MSCC_PIF_LMM_ACCESS_TYPE_ENUM
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
enum NAS_MSCC_PIF_LMM_ACCESS_TYPE_ENUM
{
    NAS_MSCC_PIF_LMM_ACCESS_TYPE_EUTRAN_TDD      = 0,
    NAS_MSCC_PIF_LMM_ACCESS_TYPE_EUTRAN_FDD         ,
    NAS_MSCC_PIF_LMM_ACCESS_TYPE_BUTT
};
typedef VOS_UINT8  NAS_MSCC_PIF_LMM_ACCESS_TYPE_ENUM_UINT8;


/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM_UINT8
 * Description : Call type
 *******************************************************************************/
enum NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM
{
    NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_EMC_VOICE_CALL      = 0x00,
    NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_NORMAL_VOICE_CALL   = 0x01,
    NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_NORMAL_DATA_CALL    = 0x02,
    NAS_MSCC_PIF_CDMA_CALL_TYPE_DO_NORMAL_DATA_CALL    = 0x03,
    NAS_MSCC_PIF_CDMA_CALL_TYPE_BUTT                   = 0x04
};
typedef VOS_UINT8 NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMA_CALL_CAUSE_ENUM_UINT8
 * Description : Call cause
 *******************************************************************************/
enum NAS_MSCC_PIF_CDMA_CALL_CAUSE_ENUM
{
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_NO_SERVICE                           = 0x01, /**<  No Service\x{ff0c}Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_MAX_ACCESS_PROBES                    = 0x02, /**<  Max Access Probes, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_REORDER_NORMAL                       = 0x03, /**<  Reorder Order, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_REORDER_LOW_RSSI                     = 0x04, /**<  Reorder Order, Call Redial, RSSI<=-100dB */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_ACCESS_DENYIED                       = 0x05, /**<  Access Denied, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_SIGNAL_FADE_NORMAL                   = 0x06, /**<  Signal Fade, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_SIGNAL_FADE_LOW_RSSI                 = 0x07, /**<  Signal Fade, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_CHANNEL_ASSIGN_TIMEOUT_NORMAL        = 0x08, /**<  Access Time Out, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_CHANNEL_ASSIGN_TIMEOUT_LOW_RSSI      = 0x09, /**<  Access Time Out, Call Redial, RSSI<=-100dB */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_ACCT_BLOCK                           = 0x0A, /**<  Acct Block, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_NDSS                                 = 0x0B, /**<  Access Control based on Call Type, redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_REDIRECTION                          = 0x0C, /**<  Redirection, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_ABORT                                = 0x0D, /**<  State can not Process Call, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_INTERNAL_NO_SERVICE                  = 0x0E, /* Internal No Service\x{ff0c}Call Redial */

    NAS_MSCC_PIF_CDMA_CALL_CAUSE_ACCESS_IN_PROGRESS                   = 0x0F, /* Access In Progress, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_ACCESS_FAIL                          = 0x10, /* Access fail, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_SIGNAL_FADE                          = 0x11, /* Signal Fade, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_BS_RELEASE                           = 0x12, /* BS, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_CCS_NOT_SUPPORT                      = 0x13, /* Concurrent Service not Support, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_RTC_RTCACK_FAILURE                   = 0x14, /* RTC ACK FAIL, Call Redial */

    NAS_MSCC_PIF_CDMA_CALL_CAUSE_BUTT                                 = 0xFF
};
typedef VOS_UINT8 NAS_MSCC_PIF_CDMA_CALL_CAUSE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMACSQ_SET_RESULT_ENUM_UINT8
 * Description : Service status
 *******************************************************************************/
enum NAS_MSCC_PIF_CDMACSQ_SET_RESULT_ENUM
{
    NAS_MSCC_PIF_CDMACSQ_SET_RESULT_SUCC                         = 0x00,
    NAS_MSCC_PIF_CDMACSQ_SET_RESULT_FAIL                         = 0x01,
    NAS_MSCC_PIF_CDMACSQ_SET_RESULT_BUTT                         = 0x02
};
typedef VOS_UINT8 NAS_MSCC_PIF_CDMACSQ_SET_RESULT_ENUM_UINT8;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_HDR_CSQ_SET_RESULT_ENUM_UINT8
 * Description : Service status
 *******************************************************************************/
enum NAS_MSCC_PIF_HDR_CSQ_SET_RESULT_ENUM
{
    NAS_MSCC_PIF_HDR_CSQ_SET_RESULT_SUCC                         = 0x00,
    NAS_MSCC_PIF_HDR_CSQ_SET_RESULT_FAIL                         = 0x01,
    NAS_MSCC_PIF_HDR_CSQ_SET_RESULT_BUTT                         = 0x02
};
typedef VOS_UINT8 NAS_MSCC_PIF_HDR_CSQ_SET_RESULT_ENUM_UINT8;


/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMACSQ_SET_RESULT_ENUM_UINT8
 * Description : Service status
 *******************************************************************************/
enum NAS_MSCC_PIF_CFREQ_LOCK_SET_MODE_ENUM
{
    NAS_MSCC_PIF_CFREQ_LOCK_SET_MODE_DISABLE                          = 0x00,
    NAS_MSCC_PIF_CFREQ_LOCK_SET_MODE_ENABLE                           = 0x01,
    NAS_MSCC_PIF_CFREQ_LOCK_SET_MODE_BUTT                             = 0x02
};

typedef VOS_UINT8 NAS_MSCC_PIF_CFREQ_LOCK_SET_MODE_ENUM_UINT8;


/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_START_RESULT_ENUM_UINT32
 * Description : start result
 *******************************************************************************/
enum	NAS_MSCC_PIF_START_RESULT_ENUM
{
    NAS_MSCC_PIF_START_RESULT_SUCC,
    NAS_MSCC_PIF_START_RESULT_FAIL
};

typedef VOS_UINT32 NAS_MSCC_PIF_START_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_CFPLMN_OPER_RESULT_ENUM
 结构说明  : NAS_MSCC_PIF_CFPLMN_OPER_RESULT_ENUM消息中的RESULT;
*****************************************************************************/

enum NAS_MSCC_PIF_CFPLMN_OPER_RESULT_ENUM
{
    NAS_MSCC_PIF_CFPLMN_OPER_RESULT_SUCCESS          = 0,
    NAS_MSCC_PIF_CFPLMN_OPER_RESULT_FAILURE          = 1,
    NAS_MSCC_PIF_CFPLMN_OPER_RESULT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_CFPLMN_OPER_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_CFPLMN_OPERATE_TYPE_ENUM
 结构说明  : NAS_MSCC_PIF_CFPLMN_SET_STRU消息中的cmdtype;
*****************************************************************************/
enum NAS_MSCC_PIF_CFPLMN_OPERATE_TYPE_ENUM
{
    NAS_MSCC_PIF_CFPLMN_TYPE_QUERY     = 0,
    NAS_MSCC_PIF_CFPLMN_TYPE_DEL_ALL   = 1,
    NAS_MSCC_PIF_CFPLMN_TYPE_DEL_ONE   = 2,
    NAS_MSCC_PIF_CFPLMN_TYPE_ADD_ONE   = 3,
    NAS_MSCC_PIF_CFPLMN_TYPE_BUTT
};
typedef VOS_UINT8  NAS_MSCC_PIF_CFPLMN_OPERATE_TYPE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_ENUM
 结构说明  : NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_ENUM消息中的RESULT;
*****************************************************************************/

enum NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_ENUM
{
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_SUCCESS             = 0,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_FAILURE             = 1,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_TIMEOUT             = 2,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_MEM_ALLOC_FAIL      = 3,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_GET_PLMNINFO_FAIL   = 4,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_PLMN_INDEX_ERR      = 5,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_UPDATA_USIM_PLMN    = 6,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_PLMNID_INVAILD      = 7,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_SAME_PLMNID         = 8,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_PREF_PLMN_CMD_TYPE_ENUM
 结构说明  : PREFPLMN查询测试类型枚举
 1.日    期   : 2015年02月06日
   作    者   : y00307564
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_PREF_PLMN_CMD_TYPE_ENUM
{
    NAS_MSCC_PIF_PREF_PLMN_QUERY      = 0,  /* PREFPLMN查询命令 */
    NAS_MSCC_PIF_PREF_PLMN_TEST       = 1,  /* PREFPLMN测试命令 */
    NAS_MSCC_PIF_PREF_PLMN_BUTT
};

typedef VOS_UINT8 NAS_MSCC_PIF_PREF_PLMN_CMD_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_PARA_TYPE_ENUM
 结构说明  : PREFPLMN查询测试类型枚举
 1.日    期   : 2015年02月06日
   作    者   : y00307564
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_PARA_TYPE_ENUM
{
    NAS_MSCC_PLMN_LIST_INFO,           /*获取完整的PLMN列表*/
    NAS_MSCC_OPLMN_INFO,
    NAS_MSCC_UPLMN_INFO,
    NAS_MSCC_HPLMN_INFO,
    NAS_MSCC_PLMNSEL_INFO,

    /*设置MMC全局变量参数*/
    NAS_MSCC_BEGIN_SET_MMC_PARA,
    NAS_MSCC_SET_PLMNSEL_INFO,
    NAS_MSCC_SET_OPLMN_INFO,
    NAS_MSCC_SET_UPLMN_INFO,
    NAS_MSCC_END_SET_MMC_PARA,
    NAS_MSCC_PARA_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_PREF_PLMN_ID_ENUM
 结构说明  : PREFPLMN类型枚举
 1.日    期   : 2015年02月06日
   作    者   : y00307564
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_PREF_PLMN_TYPE_ENUM
{
    NAS_MSCC_PREF_PLMN_UPLMN,
    NAS_MSCC_PREF_PLMN_OPLMN,
    NAS_MSCC_PREF_PLMN_HPLMN,
    NAS_MSCC_PREF_PLMN_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_PREF_PLMN_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_PREFPLMN_OPERATE_TYPE_ENUM
 结构说明  : PREFPLMN增删改操作类型枚举
 1.日    期   : 2015年02月06日
   作    者   : y00307564
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_PREFPLMN_OPERATE_TYPE_ENUM
{
    NAS_MSCC_PREF_PLMN_QUREY,
    NAS_MSCC_PREF_PLMN_DEL_ONE,
    NAS_MSCC_PREF_PLMN_ADD_ONE,
    NAS_MSCC_PREF_PLMN_MODIFY_ONE,
    NAS_MSCC_PREF_PLMN_OPERATE_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_PREFPLMN_OPERATE_TYPE_ENUM_UINT8;

typedef enum
{
    EN_MMC_PLMN_LIST_INFO,           /*获取完整的PLMN列表*/
    EN_MMC_OPLMN_INFO,
    EN_MMC_UPLMN_INFO,
    EN_MMC_HPLMN_INFO,
    EN_MMC_PLMNSEL_INFO,

    /*设置MMC全局变量参数*/
    EN_MMC_BEGIN_SET_MMC_PARA,
    EN_MMC_SET_PLMNSEL_INFO,
    EN_MMC_SET_OPLMN_INFO,
    EN_MMC_SET_UPLMN_INFO,
    EN_MMC_END_SET_MMC_PARA,
    MMC_MMA_PARA_TYPE_BUTT
}MMC_MMA_PARA_TYPE_ENUM;

/** ****************************************************************************
 枚举名    : NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM
 结构说明  : 系统捕获结果
 1.日    期   : 2015年02月06日
   作    者   : y00307564
   修改内容   : 新建
 *******************************************************************************/
enum NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM
{
    NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC        = 0x00000000,
    NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL        = 0x00000001,
    NAS_MSCC_PIF_ACQUIRED_RESULT_ABORTED     = 0x00000002,
    NAS_MSCC_PIF_ACQUIRED_RESULT_NO_RF       = 0x00000003,
    NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_BUTT   = 0x00000004
};
typedef VOS_UINT32 NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_UINT32;

typedef VOS_UINT16 NAS_MSCC_USIM_RAT;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_NETWORK_DETACH_TYPE_ENUM_UINT8
 结构说明  : 网络detach ind里指示的detach类型
 1.日    期: 2014年4月1日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
enum NAS_MSCC_PIF_NETWORK_DETACH_TYPE_ENUM
{
    NAS_MSCC_PIF_NETWORK_DETACH_TYPE_REATTACH      = 1,
    NAS_MSCC_PIF_NETWORK_DETACH_TYPE_NOATTACH      = 2,
    NAS_MSCC_PIF_NETWORK_DETACH_TYPE_IMSI          = 3,
    NAS_MSCC_PIF_NETWORK_DETACH_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_NETWORK_DETACH_TYPE_ENUM_UINT8;


enum MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM
{
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NORMAL_SERVICE    = 0,                        /* Normal service*/
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_LIMITED_SERVICE   = 1,                        /* Limited service */
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NO_SERVICE        = 2,                        /* No service */
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_INTERRUPT         = 3,                        /* sevice interrupted */
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NO_RF             = 4,
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_BUTT
};
typedef VOS_UINT32 MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32;


/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_NET_SCAN_RESULT_ENUM
 结构说明  : NAS_MSCC_PIF_NET_SCAN_CNF_STRU消息中的enResult;
*****************************************************************************/
enum NAS_MSCC_PIF_NET_SCAN_RESULT_ENUM
{
    NAS_MSCC_PIF_NET_SCAN_RESULT_SUCCESS     = 0,
    NAS_MSCC_PIF_NET_SCAN_RESULT_FAILURE     = 1,
    NAS_MSCC_PIF_NET_SCAN_RESULT_BUTT
};
typedef VOS_UINT8  NAS_MSCC_PIF_NET_SCAN_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_NET_SCAN_CAUSE_ENUM
 结构说明  : 扫描失败原因
 1.日    期   : 2013年10月10日
   作    者   : w00242748
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_NET_SCAN_CAUSE_ENUM
{
    NAS_MSCC_PIF_NET_SCAN_CAUSE_SIGNAL_EXIST        = 0,                /* 存在信令连接 */
    NAS_MSCC_PIF_NET_SCAN_CAUSE_STATE_NOT_ALLOWED   = 1,                /* 当前未驻留 */
    NAS_MSCC_PIF_NET_SCAN_CAUSE_FREQ_LOCK           = 2,                /* 当前锁频状态 */
    NAS_MSCC_PIF_NET_SCAN_CAUSE_PARA_ERROR          = 3,                /* 参数错误，包含接入技术不支持，频段不支持，频点个数错误，门限错误 */
    NAS_MSCC_PIF_NET_SCAN_CAUSE_CONFLICT            = 4,                /* 错误原因值冲突 */
    NAS_MSCC_PIF_NET_SCAN_CAUSE_SERVICE_EXIST,
    NAS_MSCC_PIF_NET_SCAN_CAUSE_NOT_CAMPED,
    NAS_MSCC_PIF_NET_SCAN_CAUSE_RAT_TYPE_ERROR,
    NAS_MSCC_PIF_NET_SCAN_CAUSE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_NET_SCAN_CAUSE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_REJ_TYPE_ENUM
 结构说明  : 拒绝类型
 1.日    期   : 2014年4月1日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_REJ_TYPE_ENUM
{
    NAS_MSCC_PIF_REJ_TYPE_REG        = 0,
    NAS_MSCC_PIF_REJ_TYPE_USIM_AUTH  = 1,
    NAS_MSCC_PIF_REJ_TYPE_SERV_REQ   = 2,
    NAS_MSCC_PIF_REJ_TYPE_NETWORK_DETACH_IND = 3,
    NAS_MSCC_PIF_REJ_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_REJ_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8
 枚举说明  : CS域和PS域SESSION类型
 1.日    期   : 2014年5月22日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_SRV_TYPE_ENUM
{
    NAS_MSCC_PIF_SRV_TYPE_CS_MO_NORMAL_CALL,
    NAS_MSCC_PIF_SRV_TYPE_CS_MO_EMERGENCY_CALL,
    NAS_MSCC_PIF_SRV_TYPE_CS_MO_SS,
    NAS_MSCC_PIF_SRV_TYPE_CS_MO_SMS,
    NAS_MSCC_PIF_SRV_TYPE_PS_CONVERSAT_CALL,
    NAS_MSCC_PIF_SRV_TYPE_PS_STREAM_CALL,
    NAS_MSCC_PIF_SRV_TYPE_PS_INTERACT_CALL,
    NAS_MSCC_PIF_SRV_TYPE_PS_BACKGROUND_CALL,
    NAS_MSCC_PIF_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL,
    NAS_MSCC_PIF_SRV_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_SRV_ACQ_RESULT_ENUM_UINT8
 枚举说明  : 业务触发搜网结果
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_SRV_ACQ_RESULT_ENUM
{
    NAS_MSCC_PIF_SRV_ACQ_RESULT_SUCCESS = 0,                                /* 成功 */
    NAS_MSCC_PIF_SRV_ACQ_RESULT_FAIL    = 1,                                /* 失败 */
    NAS_MSCC_PIF_SRV_ACQ_RESULT_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_SRV_ACQ_RESULT_ENUM_UINT8;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_VOICE_DOMAIN_ENUM_UINT32
 结构说明  : VOIDE DOMAIN类型
  1.日    期   : 2015年04月13日
    作    者   : f00179208
    修改内容   : 新建
 *****************************************************************************/
enum NAS_MSCC_PIF_VOICE_DOMAIN_ENUM
{
    NAS_MSCC_PIF_VOICE_DOMAIN_CS_ONLY            = 0,    /* CS voice only */
    NAS_MSCC_PIF_VOICE_DOMAIN_IMS_PS_ONLY        = 1,    /* IMS PS voice only */
    NAS_MSCC_PIF_VOICE_DOMAIN_CS_PREFERRED       = 2,    /* CS vocie preferred, IMS PS voice as secondary */
    NAS_MSCC_PIF_VOICE_DOMAIN_IMS_PS_PREFERRED   = 3,    /* IMS PS voice preferred, CS vocie as secondary */

    NAS_MSCC_PIF_VOICE_DOMAIN_BUTT
};
typedef VOS_UINT32  NAS_MSCC_PIF_VOICE_DOMAIN_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_IMS_SWITCH_STATE_ENUM_UINT8
 结构说明  : IMS协议栈开关机状态枚举类型
 1.日    期   : 2015年04月13日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_IMS_SWITCH_STATE_ENUM
{
    NAS_MSCC_PIF_IMS_SWITCH_STATE_OFF        = 0,
    NAS_MSCC_PIF_IMS_SWITCH_STATE_ON         = 1,
    NAS_MSCC_PIF_IMS_SWITCH_STATE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_IMS_SWITCH_STATE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_IMS_START_RESULT_ENUM_UINT32
 结构说明  : IMS协议栈开机结果枚举类型
 1.日    期   : 2015年04月13日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_IMS_START_RESULT_ENUM
{
    NAS_MSCC_PIF_IMS_START_RESULT_SUCC       = 0,
    NAS_MSCC_PIF_IMS_START_RESULT_TIMEOUT    = 1,

    NAS_MSCC_PIF_IMS_START_RESULT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_IMS_START_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_IMS_STOP_RESULT_ENUM_UINT32
 结构说明  : IMS协议栈关机结果枚举类型
 1.日    期   : 2015年04月13日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_IMS_STOP_RESULT_ENUM
{
    NAS_MSCC_PIF_IMS_STOP_RESULT_SUCC       = 0,
    NAS_MSCC_PIF_IMS_STOP_RESULT_TIMEOUT    = 1,

    NAS_MSCC_PIF_IMS_STOP_RESULT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_IMS_STOP_RESULT_ENUM_UINT32;


/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32
 *
 * Description :
 *******************************************************************************/
enum NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM
{
    NAS_MSCC_PIF_INTERSYS_CAUSE_RESELECT    = 0x00000000,
    NAS_MSCC_PIF_INTERSYS_CAUSE_REDIR       = 0x00000001,
    NAS_MSCC_PIF_INTERSYS_CAUSE_HO          = 0x00000002,
    NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_BUTT   = 0x00000003
};
typedef VOS_UINT32 NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CL_ACQUIRED_RESULT_ENUM_UINT32
 *
 * Description :
 *******************************************************************************/
enum MSCC_MMC_CL_ACQUIRED_RESULT_ENUM
{
    NAS_MSCC_PIF_CL_ACQUIRED_RESULT_SUCC    = 0x00000000,
    NAS_MSCC_PIF_CL_ACQUIRED_RESULT_FAIL    = 0x00000001,
    NAS_MSCC_PIF_CL_ACQUIRED_RESULT_ABORTED = 0x00000002,
    NAS_MSCC_PIF_CL_ACQUIRED_RESULT_ENUM_BUTT= 0x00000003
};
typedef VOS_UINT32 NAS_MSCC_PIF_CL_ACQUIRED_RESULT_ENUM_UINT32;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_PRI_CLASS_ENUM
 *
 * Description :
 *******************************************************************************/
enum NAS_MSCC_PIF_PRI_CLASS_ENUM
{
    NAS_MSCC_PIF_PRI_CLASS_HOME             = 0x00,
    NAS_MSCC_PIF_PRI_CLASS_PREF             = 0x01,
    NAS_MSCC_PIF_PRI_CLASS_ANY              = 0x0F,
    NAS_MSCC_PIF_PRI_CLASS_ENUM_BUTT        = 0xF0
};
typedef VOS_UINT8 NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_ENUM_UINT8
 枚举说明  : 业务触发搜网的RAT类型
 1.日    期   : 2014年5月15日
   作    者   : l00301449
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_ENUM
{
    NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_GUL,
    NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_1X,
    NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_HRPD,
    NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_BUTT
};

typedef VOS_UINT8 NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_ENUM_UINT8;





/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_ENUM_UINT8
 枚举说明  : RF AVAILABLE的RAT类型
 1.日    期   : 2014年5月15日
   作    者   : l00301449
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_ENUM
{
    NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_3GPP,
    NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_1X,
    NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_HRPD,
    NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_BUTT
};

typedef VOS_UINT8 NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_PS_RATTYPE_ENUM_UINT32
 结构说明  : CDMA PS RATTYPE 枚举类型
 1.日    期   : 2015年05月11日
   作    者   : y00322978
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_PS_RAT_TYPE_ENUM
{
    NAS_MSCC_PIF_PS_RATTYPE_NULL   = 0,
    NAS_MSCC_PIF_PS_RATTYPE_1X     = 1,
    NAS_MSCC_PIF_PS_RATTYPE_HRPD   = 2,
    NAS_MSCC_PIF_PS_RATTYPE_EHRPD  = 3,
    NAS_MSCC_PIF_PS_RATTYPE_LTE    = 4,
    NAS_MSCC_PIF_PS_RATTYPE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_PS_RAT_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_EMC_CALLBACK_MODE_ENUM_UINT32
 结构说明  : EMC_CALLBACK_MODE枚举类型
 1.日    期   : 2015年07月16日
   作    者   : h00313353
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PIF_EMC_CALLBACK_MODE_ENUM
{
    NAS_MSCC_PIF_EMC_CALLBACK_MODE_DISABLE  = 0,
    NAS_MSCC_PIF_EMC_CALLBACK_MODE_ENABLE   = 1,

    NAS_MSCC_PIF_EMC_CALLBACK_MODE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_EMC_CALLBACK_MODE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MMC_MSCC_CL_REG_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : CL的VIA形态使用的ATTACH注册结果上报时所处的阶段
*****************************************************************************/
enum MMC_MSCC_ATTACH_CL_REG_STATUS_ENUM
{
    MMC_MSCC_CL_REG_STATUS_ATTACH_NOT_SEND            = 0x00,
    MMC_MSCC_CL_REG_STATUS_ATTACH_SEND_WAIT_CN_RSP    = 0x01,
    MMC_MSCC_CL_REG_STATUS_ATTACH_RCV_CN_REJ          = 0x02,
    MMC_MSCC_CL_REG_STATUS_ATTACH_RCV_CN_ACP          = 0x03,
    MMC_MSCC_CL_REG_STATUS_ATTACH_T3410_EXP           = 0x04,
    MMC_MSCC_CL_REG_STATUS_ATTACH_CMP_SEND            = 0x05,

    MMC_MSCC_CL_REG_STATUS_BUTT
};
typedef VOS_UINT8 MMC_MSCC_ATTACH_CL_REG_STATUS_ENUM8;

/*****************************************************************************
枚举名    : MSCC_MMC_PS_SIGNALING_TYPE_ENUM_UINT8
枚举说明  : PS信息类型
1.日    期   : 2015年10月14日
  作    者   : j00174725
  修改内容   : DTS2015093005685
*****************************************************************************/
enum MSCC_MMC_PS_SIGNALING_TYPE_ENUM
{
    MSCC_MMC_PS_SIGNALING_TYPE_GU           = 0,                                /* GU的PS信令 */
    MSCC_MMC_PS_SIGNALING_TYPE_LTE          = 1,                                /* LTE的PS信令 */

    MSCC_MMC_PS_SIGNALING_TYPE_BUTT
};
typedef VOS_UINT8 MSCC_MMC_PS_SIGNALING_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_PLMN_SEARCH_TYPE_ENUM
 结构说明  : PLMN搜索类型
 1.日    期   : 2015年12月10日
   作    者   : w00176964
   修改内容   : CL_MUTIMODE_OPTIMIZE新增
*****************************************************************************/
enum NAS_MSCC_PIF_PLMN_SEARCH_TYPE_ENUM
{
    NAS_MSCC_PIF_PLMN_SEARCH_SPEC        = 0,       /* 指定搜索,默认安装全频段的方式搜索 */
    NAS_MSCC_PIF_PLMN_SEARCH_HISTORY     = 1,       /* 历史频点搜索 */
    NAS_MSCC_PIF_PLMN_SEARCH_PERF_BAND   = 2,       /*搜索预置band，接入层不需要进行全band搜索，仅需要搜索预置band,但如果预置band
                                                    和硬件支持的band完全重叠，接入层需要在搜网结果中将进行过全band扫频的标志位置位*/
    NAS_MSCC_PIF_PLMN_SEARCH_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_PLMN_SEARCH_TYPE_ENUM_UINT32;


/*****************************************************************************
枚举名    : NAS_MSCC_PIF_POWER_SAVE_TYPE_ENUM_UINT8
枚举说明  : MSCC下发POWER SAVE请求携带的原因值
1.日    期   : 2016年02月02日
  作    者   : h00313353
  修改内容   : DTS2016013000558
*****************************************************************************/
enum NAS_MSCC_PIF_POWER_SAVE_TYPE_ENUM
{
    NAS_MSCC_PIF_POWER_SAVE_TYPE_UNKNOWN = 0,                                /* 导致POWERSAVE的原因值未知 */
    NAS_MSCC_PIF_POWER_SAVE_TYPE_SLEEP   = 1,                                /* SLEEP导致POWERSAVE */
    NAS_MSCC_PIF_POWER_SAVE_TYPE_SYSCFG  = 2,                                /* SYSCFG导致POWERSAVE */

    NAS_MSCC_PIF_POWER_SAVE_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_POWER_SAVE_TYPE_ENUM_UINT8;

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
/*******************************************************************************
 * Name        : MSCC_MSG_HEADER_STRU
 *
 * Description : MSCC与其它模块消息头结构
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MSCC_PIF_MSG_TYPE_ENUM_UINT32       ulMsgName;
}MSCC_MSG_HEADER_STRU;


/*******************************************************************************
 * Name        : NAS_MSCC_PIF_CDMA_BAND_STRU
 *
 * Description : CDMA的频点
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpBC0_A:1;
    VOS_UINT32                          bitOpBC0_B:1;
    VOS_UINT32                          bitOpBC1:1;
    VOS_UINT32                          bitOpBC2:1;
    VOS_UINT32                          bitOpBC3:1;
    VOS_UINT32                          bitOpBC4:1;
    VOS_UINT32                          bitOpBC5:1;
    VOS_UINT32                          bitOpBC6:1;
    VOS_UINT32                          bitOpBC7:1;
    VOS_UINT32                          bitOpBC8:1;
    VOS_UINT32                          bitOpBC9:1;
    VOS_UINT32                          bitOpBC10:1;
    VOS_UINT32                          bitOpBC11:1;
    VOS_UINT32                          bitOpBC12:1;
    VOS_UINT32                          bitOpBC14:1;
    VOS_UINT32                          bitOpBC15:1;
    VOS_UINT32                          bitOpSpare:16;
}NAS_MSCC_PIF_CDMA_BAND_STRU;

/*******************************************************************************
 结构名    : CDMA_BAND_SET_UN
 协议表格  :
 ASN.1描述 :
 结构说明  : CDMA频段union定义
1.日    期 : 2015年4月15日
  作    者 : y00245242
  修改内容 : 修改WCDMA的频段为32位的,支持W下band19
*******************************************************************************/
typedef union
{
    VOS_UINT32                          ulCdmaBand;

    NAS_MSCC_PIF_CDMA_BAND_STRU         stCdmaBitBand;
}NAS_MSCC_CDMA_BAND_SET_UN;


/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PLMN_ID_STRU
 结构说明  : plmn id的信息
 1.日    期   : 2015年2月25日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes */
    VOS_UINT32                          ulMnc;                                  /* MNC,2 or 3 bytes */
}NAS_MSCC_PIF_PLMN_ID_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_FREQENCY_CHANNEL_STRU
 结构说明  : 频段和频点信息
   1.日    期   : 2015年5月16日
    作    者   : W00176964
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_BAND_CLASS_ENUM_UINT16                     enBandClass;
    VOS_UINT16                                              usChannel;
}NAS_MSCC_PIF_FREQENCY_CHANNEL_STRU;


typedef struct
{
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enRat;
    VOS_UINT8                                               aucReserve[3];
    NAS_MSCC_PIF_PLMN_ID_STRU                               stInitAcqPlmnId;
}NAS_MSCC_PIF_INIT_ACQ_PLMN_INFO_STRU;


typedef struct
{
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enRat;                                  /* plmn rat in the plmn list */
    VOS_UINT8                                               ucHighPlmnNum;
    VOS_UINT8                                               ucLowPlmnNum;
    VOS_UINT8                                               aucReserve[1];
    NAS_MSCC_PIF_PLMN_ID_STRU                               astHighPlmnID[NAS_MSCC_PIF_MAX_HIGH_QUALITY_PLMN_NUM];
    NAS_MSCC_PIF_PLMN_ID_STRU                               astLowPlmnID[NAS_MSCC_PIF_MAX_LOW_QUALITY_PLMN_NUM];
}NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU;


/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PLMN_PRI_CLASS_INFO_STRU
 结构说明  : plmn id with pri class type的信息
 1.日    期   : 2015年5月4日
   作    者   : W00176964
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enPriClass;
    VOS_UINT8                                               ucIsForbidden;
    VOS_UINT8                                               aucRsv[2];
}NAS_MSCC_PIF_PLMN_PRI_CLASS_INFO_STRU;


typedef struct
{
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enRat;                                  /* plmn rat in the plmn list */
    VOS_UINT8                                               ucHighPlmnNum;
    VOS_UINT8                                               ucLowPlmnNum;
    VOS_UINT8                                               aucReserve[1];
    NAS_MSCC_PIF_PLMN_PRI_CLASS_INFO_STRU                   astHighPlmnPriClassInfo[NAS_MSCC_PIF_MAX_HIGH_QUALITY_PLMN_NUM];
    NAS_MSCC_PIF_PLMN_PRI_CLASS_INFO_STRU                   astLowPlmnPriClassInfo[NAS_MSCC_PIF_MAX_LOW_QUALITY_PLMN_NUM];
}NAS_MSCC_PIF_PLMN_PRI_CLASS_LIST_INFO_STRU;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_PREF_PLMN_OPERATE_STRU
 结构说明  : PREFPLMN操作类型
 1.日    期   : 2015年02月06日
   作    者   : y00307564
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_PREF_PLMN_TYPE_ENUM_UINT8                  enPrefPLMNType;
    NAS_MSCC_PIF_PREFPLMN_OPERATE_TYPE_ENUM_UINT8           enPrefPlmnOperType;
    NAS_MSCC_USIM_RAT                                       usRat;              /* USIM格式的 接入技术 */
    VOS_UINT32                                              ulIndex;
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmn;
} NAS_MSCC_PIF_PREF_PLMN_OPERATE_STRU;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_PREF_PLMN_OPERATE_STRU
 结构说明  : PREFPLMN操作类型
 1.日    期   : 2015年02月06日
   作    者   : y00307564
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPlmnNum;
    VOS_UINT8                           aucReserved[2];
    NAS_MSCC_PIF_PLMN_ID_STRU           Plmn[NAS_MSCC_PIF_MAX_PLMN_NUM];
    NAS_MSCC_USIM_RAT                   ausPlmnRat[NAS_MSCC_PIF_MAX_PLMN_NUM];
}NAS_MSCC_PIF_USER_PLMN_LIST_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_RAT_PRIO_STRU
 结构说明  : MS band的能力
 1.日    期   : 2011年6月28日
   作    者   : zhoujun 40661
   修改内容   : 新建
 2.日    期   : 2014年5月22日
   作    者   : W00176964
   修改内容   : ECALL调整:LTE宏关闭时字节不对齐
 3.日    期   : 2015年5月12日
   作    者   : W00176964
   修改内容   : CDMA iteration 10 modified
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucRatNum;                                   /* 当前支持的接入技术个数  */
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8    aucRatPrio[NAS_MSCC_PIF_MAX_RAT_NUM];       /* 接入优先级里列表 index表示优先级次序,0最高，2最低 */
#if (FEATURE_OFF == FEATURE_LTE)
    VOS_UINT8                               aucRsv[1];
#endif
}NAS_MSCC_PIF_RAT_PRIO_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_3GPP2_RAT_STRU
 结构说明  : MS 3GPP2的接入技术能力
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucRatNum;                                   /* 当前支持的接入技术个数  */
    NAS_MSCC_PIF_3GPP2_RAT_TYPE_ENUM_UINT8                  auc3GPP2Rat[NAS_MSCC_PIF_3GPP2_RAT_TYPE_BUTT];
    VOS_UINT8                                               aucReserve[1];
}NAS_MSCC_PIF_3GPP2_RAT_STRU;
/* Added by s00246516 for L-C互操作项目, 2014-01-26, End */

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_EPLMN_INFO_STRU
 结构说明  : MSCC当前EQUPLMN信息
 1.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEquPlmnNum;                           /* 当前EquPLMN的个数 */                                                                                /* EPLMN被删除或EPLMN个数为0时无效,其它情况都有效 */
    VOS_UINT8                           aucReserved[3];
    NAS_MSCC_PIF_PLMN_ID_STRU           astEquPlmnAddr[NAS_MSCC_PIF_MAX_EQUPLMN_NUM];/* 当前EquPLMN列表 */
}NAS_MSCC_PIF_EPLMN_INFO_STRU;


/*****************************************************************************
 结构名    : NAS_MSCC_PIF_CAMP_CELL_INFO_STRU
 结构说明  : 当前驻留小区的信息
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCellNum;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          aulCellId[NAS_MSCC_PIF_CELL_MAX_NUM];
}NAS_MSCC_PIF_CAMP_CELL_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_OPERATOR_NAME_INFO_STRU
 结构说明  : plmn id和运营商长短名信息
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_PLMN_ID_STRU           stOperatorPlmnId;
    VOS_UINT8                           aucOperatorNameShort[NAS_MSCC_PIF_MAX_OPER_SHORT_NAME_LEN];/* 当前驻留网络运营商的短名称 */
    VOS_UINT8                           aucOperatorNameLong[NAS_MSCC_PIF_MAX_OPER_LONG_NAME_LEN];  /* 当前驻留网络运营商的长名称 */
}NAS_MSCC_PIF_OPERATOR_NAME_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_UE_SUPPORT_FREQ_BAND_STRU
 结构说明  : ue 支持band能力
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
 2.日    期   : 2015年4月15日
   作    者   : y00245242
   修改内容   : iteration 13开发
*****************************************************************************/
typedef struct
{
    WCDMA_BAND_SET_UN                   unWcdmaBand;                            /* wcdma当前设置支持的频段 */
    GSM_BAND_SET_UN                     unGsmBand;                              /* gsm当前设置支持的频段 */
    LTE_BAND_STRU                       stLteBand;                              /* lte当前设置支持的频段 */
    NAS_MSCC_CDMA_BAND_SET_UN           unCdmaBand;                             /* cdma当前设置支持的频段 */
}NAS_MSCC_PIF_UE_SUPPORT_FREQ_BAND_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_RSSI_VALUE_STRU
 结构说明  : rssi值
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sRssiValue;
    VOS_INT16                           sRscpValue;
    VOS_UINT8                           ucBer;
    VOS_UINT8                           aucReserved[3];
}NAS_MSCC_PIF_RSSI_VALUE_STRU;

/*******************************************************************************
 结构名    :NAS_MSCC_PIF_SCELL_MEAS_TYPE_STRU
 结构说明  : union NAS_MSCC_PIF_SCELL_MEAS_TYPE_STRU成员stMeasReportType定义
             bit位置1表示该类型有效
1.日    期 : 2014年6月5日
  作    者 : b00269685
  修改内容 : 新建
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMeasRxlevType          :1;             /* Rxlev改变触发的测量上报 */
    VOS_UINT8                           ucMeasRxqualityType      :1;             /* Rxquality改变触发的测量上报 */
    VOS_UINT8                           ucMeasCellIdType         :1;             /* Rxquality改变触发的测量上报 */
    VOS_UINT8                           ucMeasTypeSpare5         :5;
}NAS_MSCC_PIF_SCELL_MEAS_TYPE_STRU;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_SCELL_MEAS_REPORT_TYPE_UN
 结构说明  : NAS_MSCC_PIF_SCELL_MEAS_REPORT_TYPE_UN unMeasType上报测量的类型
1. 日    期: 2014年6月5日
   作    者: b00269685
   修改内容: 新建
*****************************************************************************/
typedef union
{
    VOS_UINT8                           ucMeasReportType;

    NAS_MSCC_PIF_SCELL_MEAS_TYPE_STRU   stMeasReportType;
    VOS_UINT8                           aucReserved1[4];
}NAS_MSCC_PIF_SCELL_MEAS_REPORT_TYPE_UN;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_RSSI_INFO_STRU
 结构说明  : rssi信息
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
 2.日    期: 2014年6月4日
   作    者: b00269685
   修改内容: 增加上报类型
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT8                                               ucRssiNum;
    VOS_UINT8                                               ucReserved;
    VOS_UINT16                                              usCellDlFreq;                           /*小区频点(下行)*/
    VOS_UINT16                                              usCellUlFreq;                           /*当前频点(上行)*/
    VOS_INT16                                               sUeRfPower;                             /*发射功率*/
    NAS_MSCC_PIF_RSSI_VALUE_STRU                            astRssi[NAS_MSCC_PIF_CELL_MAX_NUM];
    NAS_MSCC_PIF_SCELL_MEAS_REPORT_TYPE_UN                  unMeasReportType;                       /* 本次上报类型 */
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8     enRat;                                  /*当前上报信号的制式*/
    VOS_UINT8                           aucReserved1[3];
}NAS_MSCC_PIF_RSSI_IND_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_CQI_INFO_STRU
 结构说明  : LTE下的信道质量,两个码字分别代表子带CQI和宽带CQI
 1.日    期: 2014年11月28日
   作    者: w00281933
   修改内容: 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usRI;                                   /* RI */
    VOS_UINT8                           aucRes[2];
    VOS_UINT16                          ausCQI[2];                              /* CQI两个码字 */

}NAS_MSCC_PIF_CQI_INFO_STRU;

/*****************************************************************************
 结构名    : MMA_MMC_LMM_CELL_SIGN_INFO_STRU
 结构说明  : LTE下的信道质量,包括LTE下的Rssi及Rsrp，Rsrq,SINR,CQI
 1.日    期: 2014年11月28日
   作    者: w00281933
   修改内容: 新增
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sRssi;                                  /* Rssi*/
    VOS_INT16                           sRsd;                                   /* 填充字段*/
    VOS_INT16                           sRsrp;                                  /* 范围：(-141,-44), 99为无效 */
    VOS_INT16                           sRsrq;                                  /* 范围：(-40, -6) , 99为无效 */
    VOS_INT32                           lSINR;                                  /* SINR RS_SNR */
    NAS_MSCC_PIF_CQI_INFO_STRU          stCQI;                                  /* Channle Quality Indicator*/
}NAS_MSCC_PIF_LMM_CELL_SIGN_INFO_STRU;

/*****************************************************************************
 结构名    : MMA_MMC_LMM_CELL_SIGN_INFO_STRU
 结构说明  : ID_MMC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND对应的结构体
 1.日    期: 2014年11月28日
   作    者: w00281933
   修改内容: 新增
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                          MsgHeader;                    /* _H2ASN_Skip */

    NAS_MSCC_PIF_SCELL_MEAS_REPORT_TYPE_UN        unMeasReportType;             /* 本次上报类型 */
    NAS_MSCC_PIF_LMM_CELL_SIGN_INFO_STRU          stLteRssi;                    /* LTE cell Signal INFO */
}NAS_MSCC_PIF_LMM_CELL_SIGN_INFO_REPORT_IND_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_START_CNF_STRU
 结构说明  : mmc给mma发送开机结果的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_START_RESULT_ENUM_UINT32                   ulResult;
}NAS_MSCC_PIF_START_CNF_STRU;


/*****************************************************************************
 结构名    : NAS_MSCC_PIF_3GPP_SYS_INFO_IND_STRU
 结构说明  : mmc给mma发送系统消息的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2013年11月25日
   作    者   : z00161729
   修改内容   : SVLTE优化G-TL ps切换性能修改
 3.日    期   : 2013年10月16日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseII 项目:增加漫游信息参数
 4.日    期   : 2014年01月17日
   作    者   : l00198894
   修改内容   : V9R1C53 C+L 离网重选项目
 5.日    期   : 2014年2月20日
   作    者   : z00161729
   修改内容   : DTS2014022100125:单待驻留g的网络，切双待后tl无网络限制驻留g的网络，
               available超时做list搜网构造搜网列表把last rplmn rat排在最前面导致g排在第一个
               无法回l或tds的网络
 6.日    期   : 2014年2月8日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加异系统到HRPD的处理
 7.日    期   : 2015年7月20日
   作    者   : w000316404
   修改内容   : R11协议升级(LTE频点配置值扩展)

*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;                              /* _H2ASN_Skip */
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enCurNetWork;                           /* 当前网络类型 */
    VOS_UINT8                                               ucRac;
    VOS_UINT8                                               ucSysSubMode;                           /* 驻留网络的系统子模式，取值与RRC_NAS_SYS_SUBMODE_ENUM相同 */
    VOS_UINT8                                               ucIsFobbiddenPlmnFlag;
    VOS_UINT16                                              usLac;                                  /* 位置码信息 */
    VOS_UINT8                                               ucRoamFlag;                             /* 当前是否处于漫游 */
    VOS_UINT8                                               ucPsSupportFlg;                         /* 当前是否支持PS域 */
    NAS_MSCC_PIF_CAMP_CELL_INFO_STRU                        stCellId;                               /* 小区信息 */
    VOS_UINT8                                               ucPsAttachAllowFlag;
    VOS_UINT8                                               ucCsAttachAllowFlag;
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enPrioClass;
    NAS_MSCC_PIF_LMM_ACCESS_TYPE_ENUM_UINT8                 enLmmAccessType;
    VOS_UINT32                                              ulArfcn;
}NAS_MSCC_PIF_3GPP_SYS_INFO_IND_STRU;

typedef VOS_UINT16 NAS_MSCC_PIF_REG_FAIL_CAUSE_UINT16;
/*****************************************************************************
 结构名    : NAS_MSCC_PIF_REG_RESULT_IND_STRU
 结构说明  : mmc给mma发送拒绝原因值消息的消息结构
 1.日    期   : 2013年8月15日
   作    者   : l00208543
   修改内容   : 新建
 2.日    期   : 2013年12月13日
   作    者   : w00176964
   修改内容   : Volte_PhaseIII 项目:修改结构名
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                     MsgHeader;                              /*_H2ASN_Skip*/
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32       enCnDomainId;
    VOS_UINT8                                ucRegRslt;                              /* VOS_TRUE:指定域注册成功; 反之注册失败 */
    VOS_UINT8                                ucReportCauseCtrl;                      /* 是否需要上报原因值 */
    NAS_MSCC_PIF_REG_FAIL_CAUSE_UINT16       enRejCause;
    VOS_UINT8                                ucOriginalRejCause;
    VOS_UINT8                                aucReserve[3];
}NAS_MSCC_PIF_REG_RESULT_IND_STRU;

typedef VOS_UINT16 NAS_MSCC_PIF_SIM_AUTH_FAIL_UINT16;
/*****************************************************************************
 结构名    : NAS_MSCC_PIF_USIM_AUTH_FAIL_IND_STRU
 结构说明  : mmc给mma发送USIM鉴权失败原因值消息的消息结构
 1.日    期   : 2013年11月15日
   作    者   : m00217266
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        MsgHeader;                      /* _H2ASN_Skip */
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32          enCnDomainId;
    NAS_MSCC_PIF_SIM_AUTH_FAIL_UINT16           enRejCause;
    VOS_UINT8                                   aucReserve[2];
}NAS_MSCC_PIF_USIM_AUTH_FAIL_IND_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_SERVICE_STATUS_IND_STRU
 结构说明  : mmc给mma发送注册状态和服务状态的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2013年11月20日
   作    者   : w00176964
   修改内容   : Volte PhaseII项目修改:增加CSPS的SIM卡状态
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                         MsgHeader;                     /* _H2ASN_Skip */
    VOS_UINT32                                   bitOpSrvSta     : 1;
    VOS_UINT32                                   bitOpRegSta     : 1;
    VOS_UINT32                                   bitSpare        : 30;

    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32           enCnDomainId;
    VOS_UINT8                                    ucSimCsRegStatus;
    VOS_UINT8                                    ucSimPsRegStatus;
    VOS_UINT8                                    aucReserved[1];
    NAS_MSCC_PIF_REG_STATE_ENUM_UINT8            enRegState;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32      enServiceStatus;
    VOS_UINT32                                   ulOosCause;
}NAS_MSCC_PIF_SERVICE_STATUS_IND_STRU;


/*****************************************************************************
 结构名    : NAS_MSCC_PIF_MM_INFO_IND_STRU
 结构说明  : mmc给mma发送MM INFORMATION的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    VOS_UINT8                                               ucIeFlg;
    VOS_INT8                                                cLocalTimeZone;
    VOS_UINT8                                               ucDST;
    VOS_UINT8                                               aucLSAID[3];
    VOS_UINT8                                               aucReserve[2];
    TIME_ZONE_TIME_STRU                                     stUniversalTimeandLocalTimeZone;
    NAS_MSCC_PIF_OPERATOR_NAME_INFO_STRU                    stName;
}NAS_MSCC_PIF_MM_INFO_IND_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_SIGN_REPORT_REQ_STRU
 结构说明  : mma给mmc发送信号上报配置的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT8                           ucActionType;
    VOS_UINT8                           ucRrcMsgType;
    VOS_UINT8                           ucSignThreshold;                        /* 信号质量改变门限值 */
    VOS_UINT8                           ucMinRptTimerInterval;                  /* 间隔上报的时间   */
}NAS_MSCC_PIF_SIGN_REPORT_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_MODE_CHANGE_REQ_STRU
 结构说明  : mma给mmc发送模式变更的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    NAS_MSCC_PIF_MS_MODE_ENUM_UINT32    enMsMode;
}NAS_MSCC_PIF_MODE_CHANGE_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_ATTACH_REQ_STRU
 结构说明  : mma给mmc发送attach 请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2014年2月8日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加异系统到HRPD的处理
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    VOS_UINT32                                              ulOpID;
    NAS_MSCC_PIF_ATTACH_TYPE_ENUM_UINT32                    enAttachType;
    NAS_MSCC_PIF_EPS_ATTACH_REASON_ENUM_UINT32              enEpsAttachReason;
}NAS_MSCC_PIF_ATTACH_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_ATTACH_CNF_STRU
 结构说明  : mmc给mma发送attach 结果的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    VOS_UINT32                                              ulOpID;
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32                      enCnDomainId;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 enServiceStatus;
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
}NAS_MSCC_PIF_ATTACH_CNF_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_DETACH_REQ_STRU
 结构说明  : mma给mmc发送detach请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2014年2月8日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加异系统到HRPD的处理
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    VOS_UINT32                                              ulOpID;
    NAS_MSCC_PIF_DETACH_TYPE_ENUM_UINT32                    enDetachType;
    NAS_MSCC_PIF_DETACH_REASON_ENUM_UINT32                  enDetachReason;
}NAS_MSCC_PIF_DETACH_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_DETACH_CNF_STRU
 结构说明  : mmc给mma发送detach结果的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    VOS_UINT32                                              ulOpID;
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32                      enCnDomainId;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 enServiceStatus;
    NAS_MSCC_PIF_OPER_RESULT_ENUM_UINT32                    enOperRslt;       /* 操作结果 */
}NAS_MSCC_PIF_DETACH_CNF_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_DETACH_IND_STRU
 结构说明  : mmc给mma发送网络detach结果的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2014年4月1日
   作    者   : z00161729
   修改内容   : DTS2014040300125:service 被拒和网络detach ind被拒需要上报^rejinfo
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32                      enCnDomainId;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 enServiceStatus;
    VOS_UINT32                                              ulDetachCause;
    NAS_MSCC_PIF_NETWORK_DETACH_TYPE_ENUM_UINT8             enNetworkDetachType;
    VOS_UINT8                                               ucOriginalDetachCause;
    VOS_UINT8                                               aucReserved[2];

}NAS_MSCC_PIF_DETACH_IND_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PLMN_LIST_REQ_STRU
 结构说明  : mma给mmc发送list请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_PLMN_LIST_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PLMN_LIST_CNF_STRU
 结构说明  : mmc给mma发送list搜网结果的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulCnt;
    NAS_MSCC_PIF_PLMN_ID_STRU           aPlmnList[NAS_MSCC_PIF_MAX_PLMN_CNT];
    VOS_UINT8                           aucPlmnStatus[NAS_MSCC_PIF_MAX_PLMN_CNT];
    VOS_UINT8                           aucRaMode[NAS_MSCC_PIF_MAX_PLMN_CNT];
    VOS_UINT8                           aucReserve[2];
}NAS_MSCC_PIF_PLMN_LIST_CNF_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PLMN_LIST_REJ_STRU
 结构说明  : mmc给mma发送list搜网被接入层reject的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_PLMN_LIST_REJ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PLMN_LIST_ABORT_REQ_STRU
 结构说明  : mma给mmc发送list搜网中止的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_PLMN_LIST_ABORT_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PLMN_USER_RESEL_REQ_STRU
 结构说明  : mma给mmc发送用户重选搜网请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_PLMN_SEL_MODE_ENUM_UINT32                  enPlmnSelMode;
}NAS_MSCC_PIF_PLMN_USER_RESEL_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PLMN_SPECIAL_REQ_STRU
 结构说明  : mma给mmc发送用户指定搜网请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enAccessMode;
    VOS_UINT8                                               aucReserved[3];
}NAS_MSCC_PIF_PLMN_SPECIAL_REQ_STRU;


/*****************************************************************************
 结构名    : NAS_MSCC_PIF_COVERAGE_AREA_IND_STRU
 结构说明  : mmc给mma发送进覆盖区还是离开覆盖区指示的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_ENUM_UINT32      enCoverageChgMode;
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 enCsSvcSta;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 enPsSvcSta;
    VOS_UINT32                                              ulTimMaxFlg;
}NAS_MSCC_PIF_COVERAGE_AREA_IND_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_POWER_OFF_REQ_STRU
 结构说明  : mma给mmc发送关机请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM_UINT32                enCause;
}NAS_MSCC_PIF_POWER_OFF_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_POWER_OFF_CNF_STRU
 结构说明  : mmc给mma发送关机回复的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_POWER_OFF_CNF_STRU;


typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32              enResult;
}NAS_MSCC_PIF_SYSTEM_ACQUIRE_CNF_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PLMN_SPECIAL_SEL_CNF_STRU
 结构说明  : mmc给mma发送用户指定搜网回复的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                            MsgHeader;                  /* _H2ASN_Skip */
    NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_ENUM_UINT8 enResult;
    VOS_UINT8                                       aucReserved[3];
}NAS_MSCC_PIF_PLMN_SPECIAL_SEL_CNF_STRU;


/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PLMN_RESEL_CNF_STRU
 结构说明  : mmc给mma发送at+cops=0回复的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_ENUM_UINT8         enResult;
    VOS_UINT8                                               aucReserved[3];
}NAS_MSCC_PIF_PLMN_RESEL_CNF_STRU;


/*****************************************************************************
 结构名    : NAS_MSCC_PIF_DATATRAN_ATTRI_IND_STRU
 结构说明  : mmc给mma发送pdp激活情况的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_DATATRAN_ATTRI_ENUM_UINT8                  enDataTranAttri;
    VOS_UINT8                                               aucReserved[3];
}NAS_MSCC_PIF_DATATRAN_ATTRI_IND_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_SYS_CFG_SET_REQ_STRU
 结构说明  : mma给mmc发送syscfg设置请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_RAT_PRIO_STRU                              stRatPrioList;
    NAS_MSCC_PIF_UE_SUPPORT_FREQ_BAND_STRU                  stBand;
    NAS_MSCC_PIF_ROAM_CAPABILITY_ENUM_UINT8                 enRoamCapability;
    VOS_UINT8                                               ucOnlyRoamParaChanged;
    VOS_UINT8                                               ucIsNeedAttachPs;
    VOS_UINT8                                               aucReserved[1];
}NAS_MSCC_PIF_SYS_CFG_SET_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_CL_ASSOCIATED_INFO_NTF_STRU
 结构说明  : MSCC收到1x系统服务信息后给MMC发的CL_ASSOCIATED_INFO
 1.日    期   : 2015年9月11日
   作    者   : y00346957
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enLteSysPriClass;
    VOS_UINT8                                               ucAllowSrchLteFlg;
    VOS_UINT8                                               aucRsv[2];
}NAS_MSCC_PIF_CL_ASSOCIATED_INFO_NTF_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_SYS_CFG_SET_CNF_STRU
 结构说明  : mmc给mma发送syscfg设置结果的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_SYS_CFG_SET_RESULT_ENUM_UINT32             enRst;
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
}NAS_MSCC_PIF_SYS_CFG_SET_CNF_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_CDMA_INIT_LOC_INFO_STRU
 结构说明  : cdma的位置信息
 1.日    期   : 2015年12月10日
   作    者   : l00324781
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32      ulMcc;
    VOS_INT32       lSid;
    VOS_INT32       lNid;
} NAS_MSCC_PIF_CDMA_INIT_LOC_INFO_STRU;
/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PLMN_SEARCH_REQ_STRU
 结构说明  : mscc给mmc发送搜网请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2/4/2015
   作    者   : w00176964
   修改内容   : CDMA Iteraiton 10 Modified
 3.日    期   : 30/5/2015
   作    者   : w00176964
   修改内容   : CDMA Iteration 12
 4.日    期   : 10/12/2015
   作    者   : l00324781
   修改内容   : CL_MUTIMODE_OPTIMIZE 增加stCdmaInitLocInfo
 5.日    期   : 2015/12/10
   作    者   : w00176964
   修改内容   : CL_MUTIMODE_OPTIMIZE新增搜索类型
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;                              /* _H2ASN_Skip */
    NAS_MSCC_PIF_ACQ_REASON_ENUM_UINT32                     enAcqReason;
    NAS_MSCC_PIF_PLMN_SEARCH_TYPE_ENUM_UINT32               enSrchType;
    NAS_MSCC_PIF_INIT_ACQ_PLMN_INFO_STRU                    stInitAcqPlmnInfo;
    NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU               stHighPrioPlmnList;

    NAS_MSCC_PIF_CDMA_INIT_LOC_INFO_STRU                    stCdmaInitLocInfo;
}NAS_MSCC_PIF_PLMN_SEARCH_REQ_STRU;


typedef NAS_MSCC_PIF_PLMN_SEARCH_REQ_STRU MMA_MSCC_SYSTEM_ACQUIRE_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PLMN_SELECTION_RLST_IND_STRU
 结构说明  : mmc给mma发送搜网结果的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2015年4月14日
   作    者   : w00176964
   修改内容   : CDMA 1X Iteration Modified:add coverage flag
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_ENUM_UINT32          enResult;
    VOS_UINT8                                               ucLteCoverageFlg;   /* VOS_TRUE:lte exist coverage; VOS_FALSE:LTE exist no coverage */
    VOS_UINT8                                               aucRsv[3];
}NAS_MSCC_PIF_PLMN_SELECTION_RLST_IND_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PLMN_SELECTION_START_IND_STRU
 结构说明  : mmc给mma发送搜网开始标示的结构
 1.日    期   : 2013年10月09日
   作    者   : l00208543
   修改内容   : 新建,DTS2013100904573
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_PLMN_SELECTION_START_FLAG_ENUM_UINT32      enPlmnSeleStartFlag;
}NAS_MSCC_PIF_PLMN_SELECTION_START_IND_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PLMN_LIST_ABORT_CNF_STRU
 结构说明  : mmc给mma发送list搜网中止回复的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulCnt;
    NAS_MSCC_PIF_PLMN_ID_STRU           aPlmnList[NAS_MSCC_PIF_MAX_PLMN_CNT];
    VOS_UINT8                           aucPlmnStatus[NAS_MSCC_PIF_MAX_PLMN_CNT];
    VOS_UINT8                           aucReserved1[3];
    VOS_UINT8                           aucRaMode[NAS_MSCC_PIF_MAX_PLMN_CNT];
    VOS_UINT8                           aucReserved2[3];
}NAS_MSCC_PIF_PLMN_LIST_ABORT_CNF_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_SPEC_PLMN_SEARCH_ABORT_REQ_STRU
 结构说明  : mma给mmc发送指定搜网中止请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_SPEC_PLMN_SEARCH_ABORT_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_SPEC_PLMN_SEARCH_ABORT_CNF_STRU
 结构说明  : mmc给mma发送中止指定搜网回复的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_SPEC_PLMN_SEARCH_ABORT_CNF_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_UMTS_CIPHER_INFO_IND_STRU
 结构说明  : mmc给mma上报W的cipher信息的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT8                           ucCipherAlgorForCSDomain;
    VOS_UINT8                           ucCipherAlgorForPSDomain;
    VOS_UINT8                           aucRcv[2];
}NAS_MSCC_PIF_UMTS_CIPHER_INFO_IND_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_GPRS_CIPHER_INFO_IND_STRU
 结构说明  : mmc给mma上报G的cipher信息的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT8                           ucGprsCipherAlg;
    VOS_UINT8                           ucGprsCipher;
    VOS_UINT8                           aucRcv[2];
}NAS_MSCC_PIF_GPRS_CIPHER_INFO_IND_STRU;


/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PLMN_SPECIAL_SEL_REJ_STRU
 结构说明  : MMC给MMA发送用户指定搜拒绝结果的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_PLMN_SPECIAL_SEL_REJ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_AC_INFO_CHANGE_IND_STRU
 结构说明  : MMC给MMA发送小区接入信息变化指示的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_ENUM_UINT8           enCellAcType;
    VOS_UINT8                                               ucRestrictRegister;
    VOS_UINT8                                               ucRestrictPagingRsp;
    VOS_UINT8                                               ucReserved;
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32                      enCnDomainId;
}NAS_MSCC_PIF_AC_INFO_CHANGE_IND_STRU;


/*******************************************************************************
 结构名    : NAS_MSCC_PIF_OM_MAINTAIN_INFO_IND_STRU
 结构说明  : NAS_MSCC_PIF_OM_MAINTAIN_INFO_IND_STRU消息结构
 1.日    期  : 2013年04月16日
   作    者  : z00161729
   修改内容  : 新增结构
*******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */

    VOS_UINT8                           ucOmConnectFlg;                         /* UE与PC工具的连接标志, VOS_TRUE: 已连接; VOS_FALSE: 未连接 */
    VOS_UINT8                           ucOmPcRecurEnableFlg;                   /* OM配置的发送NAS PC回放消息的使能标志 */
    VOS_UINT8                           aucRsv2[2];                             /* 保留   */
} NAS_MSCC_PIF_OM_MAINTAIN_INFO_IND_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_UPDATE_UPLMN_NTF_STRU
 结构说明  : mma给mmc发送UPLMN更新通知的消息结构
 1.日    期   : 2013年7月31日
   作    者   : w00167002
   修改内容   : 新建结构体
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT8                           aucRsv4[4];                             /* 保留   */
}NAS_MSCC_PIF_UPDATE_UPLMN_NTF_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_EOPLMN_SET_REQ_STRU
 结构说明  : AT和MMA的EOPLMN设置接口
 1.日    期  : 2013年10月15日
   作    者  : s00190137
   修改内容  : 新增结构
 2.日    期  : 2013年11月26日
   作    者  : s00190137
   修改内容  : 添加分组机制，单组允许最大设置50个OPLMN
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    TAF_UINT8                           aucVersion[NAS_MSCC_PIF_MAX_USER_OPLMN_VERSION_LEN];        /* OPLMN List版本号 */
    TAF_UINT8                           ucIndex;                                /* 当前设置的组Index */
    TAF_UINT8                           ucOPlmnCount;                           /* 单组实际设置OPLMN的个数 */
    TAF_UINT8                           aucOPlmnWithRat[NAS_MSCC_PIF_MAX_GROUP_CFG_OPLMN_DATA_LEN];  /* OPLMN的PDU数据，和EFOplmn文件一致 */
}NAS_MSCC_PIF_EOPLMN_SET_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_EOPLMN_SET_CNF_STRU
 结构说明  : mmc给mma发送AT^EOPLMN设置回复的消息结构
 1.日    期   : 2013年10月15日
   作    者   : x65241
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulResult;                               /* OPLMN的nv保存结果*/
}NAS_MSCC_PIF_EOPLMN_SET_CNF_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_EOPLMN_SET_ABORT_STRU
 结构说明  : AT^EOPLMN设置超时通知MMC中断消息处理的结构
 1.日    期   : 2013年10月15日
   作    者   : x65241
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_EOPLMN_SET_ABORT_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_NET_SCAN_REQ_STRU
 结构说明  : MMA和MMC的NETSCAN设置接口
 1.日    期  : 2013年10月10日
   作    者  : w00242748
   修改内容  : 新增结构
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */

    VOS_UINT16                                              usCellNum;          /* 需要扫描出超过门限的小区个数 */
    VOS_INT16                                               sCellPow;           /* 小区门限值 */
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    ucRat;              /* 需要扫描的接入模式 */
    VOS_UINT8                                               aucReserve[3];
    NAS_MSCC_PIF_UE_SUPPORT_FREQ_BAND_STRU                  stBand;             /* 记录GU频段*/
}NAS_MSCC_PIF_NET_SCAN_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_NET_SCAN_INFO_STRU
 结构说明  : 扫描某个频点的网络信息
 1.日    期   : 2013年8月24日
   作    者   : w00242748
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;                                /* 频点 */
    VOS_UINT16                                              usC1;                                   /* 用于GSM小区重选的C1值(暂不支持) */
    VOS_UINT16                                              usC2;                                   /* 用于GSM小区重选的C2值(暂不支持) */
    VOS_UINT16                                              usLac;                                  /* 位置区码 */
    VOS_UINT32                                              ulMcc;                                  /* PLMN国家码 */
    VOS_UINT32                                              ulMnc;                                  /* PLMN网络码 */
    VOS_UINT16                                              usBsic;                                 /* GSM小区基站码 */
    VOS_INT16                                               sRxlev;                                 /* 接收到的信号强度 */
    VOS_INT16                                               sRssi;                                  /* GSM是BCCH信道的RSSI，WCDMA是RSCP */
    VOS_UINT8                                               aucReserve[2];
    VOS_UINT32                                              ulCellId;                               /* 小区ID */
    NAS_MSCC_PIF_UE_SUPPORT_FREQ_BAND_STRU                  stBand;                               /* 具体取值同接口RRMM_SYS_CFG_REQ_STRU中频段参数 */
}NAS_MSCC_PIF_NET_SCAN_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_NET_SCAN_CNF_STRU
 结构说明  : MMC上报给MMA的NETSCAN CNF接口
 1.日    期  : 2013年10月10日
   作    者  : w00242748
   修改内容  : 新增结构
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */

    NAS_MSCC_PIF_NET_SCAN_RESULT_ENUM_UINT8                 enResult;
    NAS_MSCC_PIF_NET_SCAN_CAUSE_ENUM_UINT8                  enCause;
    VOS_UINT8                                               ucFreqNum;          /* 上报的频点个数 */
    VOS_UINT8                                               aucReserve[1];
    NAS_MSCC_PIF_NET_SCAN_INFO_STRU                         astNetScanInfo[NAS_MSCC_PIF_NET_SCAN_MAX_FREQ_NUM];
}NAS_MSCC_PIF_NET_SCAN_CNF_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_SERV_REJ_IND_STRU
 结构说明  : mmc给mma发送服务被拒的消息结构
 1.日    期   : 2014年4月1日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId;
    VOS_UINT16                          usRejCause;
    VOS_UINT8                           ucOriginalRejCause;
    VOS_UINT8                           aucReserve[1];
}NAS_MSCC_PIF_SERV_REJ_IND_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_ABORT_NET_SCAN_REQ_STRU
 结构说明  : MMA和MMC的NETSCAN设置接口
 1.日    期  : 2013年10月10日
   作    者  : w00242748
   修改内容  : 新增结构
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_ABORT_NET_SCAN_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_ABORT_NET_SCAN_CNF_STRU
 结构说明  : MMC上报给MMA的NETSCAN CNF接口
 1.日    期  : 2013年10月10日
   作    者  : w00242748
   修改内容  : 新增结构
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */

    VOS_UINT8                           ucFreqNum;                                      /* 上报的频点个数 */
    VOS_UINT8                           aucReserve[3];
    NAS_MSCC_PIF_NET_SCAN_INFO_STRU     astNetScanInfo[NAS_MSCC_PIF_NET_SCAN_MAX_FREQ_NUM];
}NAS_MSCC_PIF_ABORT_NET_SCAN_CNF_STRU;

/*******************************************************************************
 结构名    : NAS_MSCC_PIF_NETWORK_CAPABILITY_INFO_IND_STRU
 结构说明  : 通知网络业务信息能力消息
 1.日    期  : 2013年7月9日
   作    者  : y00245242
   修改内容  : 新增结构
*******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_NW_IMS_VOICE_CAP_ENUM_UINT8                enNwImsVoCap ;
    NAS_MSCC_PIF_NW_EMC_BS_CAP_ENUM_UINT8                   enNwEmcBsCap ;
    NAS_MSCC_PIF_LTE_CS_CAPBILITY_ENUM_UINT8                enLteCsCap ;
    VOS_UINT8                                               aucReserve[1];
}NAS_MSCC_PIF_NETWORK_CAPABILITY_INFO_IND_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_CAMP_ON_IND_STRU
 结构说明  : MMC发给MMA的驻留消息结构
 1.日    期   : 2013年10月12日
   作    者   : w00176964
   修改内容   : 新建结构体
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT8                           ucCampOnFlg;                            /* VOS_TRUE:驻留;VOS_FALSE:未驻留 */
    VOS_UINT8                           aucRsv[3];                              /* 保留   */
}NAS_MSCC_PIF_CAMP_ON_IND_STRU_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_OTHER_MODEM_INFO_NOTIFY_STRU
 结构说明  : modem1的信息目前只有驻留信息
 1.日    期   : 2013年11月23日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU         stMsgHeader;                                   /*_H2ASN_Skip*/
    VOS_UINT32                   bitOpCurrCampPlmnId:1;

    VOS_UINT32                   bitOpEplmnInfo:1;
    VOS_UINT32                   bitSpare:30;

    NAS_MSCC_PIF_PLMN_ID_STRU    stCurrCampPlmnId;                              /* 用于填写当前驻留小区的PLMN，如果丢网或者关机等非驻留状态，统一填写全0xff */
    NAS_MSCC_PIF_EPLMN_INFO_STRU stEplmnInfo;
} NAS_MSCC_PIF_OTHER_MODEM_INFO_NOTIFY_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU
 结构说明  : modem1的dplmn/nplmn信息
 1.日    期   : 2014年11月3日
   作    者   : z00161729
   修改内容   : 开机漫游搜网项目修改

*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                   stMsgHeader;         /*_H2ASN_Skip*/

    VOS_UINT8                                               ucEHplmnNum;
    VOS_UINT8                                               aucReserved[3];
    VOS_UINT8                                               aucEHplmnList[NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM];
    NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU                  stSelfLearnDplmnNplmnInfo;
} NAS_MSCC_PIF_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU;

/*******************************************************************************
 结构名    : NAS_MSCC_PIF_TDS_NCELL_INFO_STRU
 结构说明  : GSM下的TDS频点列表

 1.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网

*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTdsArfcnNum;                          /* 0表示TDD频点不存在 */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          ausTdsArfcnList[NAS_MSCC_PIF_TDS_ARFCN_MAX_NUM];
}NAS_MSCC_PIF_TDS_NCELL_INFO_STRU;

/*******************************************************************************
 结构名    : NAS_MSCC_PIF_LTE_NCELL_INFO_STRU
 结构说明  : GSM下的LTE频点列表

 1.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
 2.日    期   : 2015年7月20日
   作    者   : w000316404
   修改内容   : R11协议升级(LTE频点配置值扩展)

*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLteArfcnNum;                          /* 0表示LTE频点不存在 */
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          aulLteArfcnList[NAS_MSCC_PIF_LTE_ARFCN_MAX_NUM];
}NAS_MSCC_PIF_LTE_NCELL_INFO_STRU;


/*******************************************************************************
 结构名    : NAS_MSCC_PIF_NCELL_INFO_NOTIFY_STRU
 结构说明  : ID_NAS_MSCC_PIF_NCELL_INFO_NOTIFY消息对应的结构，
             包括GSM下的TDS/LTE邻区结构中的TDS/LTE的频点列表

 1.日    期   : 2013年12月23日
   作    者   : z00161729
   修改内容   : 新生成结构

*******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;                            /*_H2ASN_Skip*/
    NAS_MSCC_PIF_TDS_NCELL_INFO_STRU    stTdsNcellInfo;
    NAS_MSCC_PIF_LTE_NCELL_INFO_STRU    stLteNcellInfo;
}NAS_MSCC_PIF_NCELL_INFO_NOTIFY_STRU;



/*****************************************************************************
 结构名    : NAS_MSCC_PIF_EPLMN_INFO_IND_STRU
 结构说明  : 等效plmn信息
 1.日    期   : 2013年12月23日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;                            /*_H2ASN_Skip*/
    NAS_MSCC_PIF_EPLMN_INFO_STRU        stEplmnInfo;
}NAS_MSCC_PIF_EPLMN_INFO_IND_STRU;


/*****************************************************************************
 结构名    : NAS_MSCC_PIF_CS_SERVICE_CONN_STATUS_IND_STRU
 结构说明  : mmc上报cs业务信令连接状态指示消息结构
 1.日    期   : 2014年3月4日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;                            /*_H2ASN_Skip*/
    VOS_UINT8                           ucCsServiceConnStatusFlag;
    VOS_UINT8                           aucReserved[3];
}NAS_MSCC_PIF_CS_SERVICE_CONN_STATUS_IND_STRU;

/*******************************************************************************
结构名    : NAS_MSCC_PIF_PS_TRANSFER_NOTIFY_STRU
结构说明  : ID_NAS_MSCC_PIF_PS_TRANSFER_NOTIFY消息结构
1.日    期   : 2014年1月5日
  作    者   : z00161729
  修改内容   : 新建
2.日    期   : 2014年01月17日
  作    者   : l00198894
  修改内容   : V9R1C53 C+L 离网重选项目
*******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;                            /*_H2ASN_Skip*/
    MTC_PS_TRANSFER_ENUM_UINT8          enSolutionCfg;                          /* PS域迁移方案 */
    VOS_UINT8                           ucCause;                                /* PS域切换原因值 */
    VOS_UINT8                           aucReserved[2];                         /*保留位*/
} NAS_MSCC_PIF_PS_TRANSFER_NOTIFY_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_IMS_VOICE_CAP_NOTIFY_STRU
 结构说明  : MMA通知MMC当前IMS VOICE是否可用的消息
 1.日    期   : 2013年12月10日
   作    者   : w00176964
   修改内容   : 新建
 2.日    期   : 2015年4月24日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */

    VOS_UINT8                                               ucAvail;            /* IMS VOICE是否可用 */

    VOS_UINT8                                               ucIsExistPersistentBearer;  /* 0:不存在；1：存在*/
    VOS_UINT8                                               aucRsv[2];
}NAS_MSCC_PIF_IMS_VOICE_CAP_NOTIFY_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_ACQ_REQ_STRU
 结构说明  : 获取消息的结构体
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
 2.日    期   : 2015年4月24日
   作    者   : w00176964
   修改内容   : CDMA 1x Iteration 10 Modified
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;                            /* _H2ASN_Skip */
    NAS_MSCC_PIF_ACQ_REASON_ENUM_UINT32 enAcqReason;
    VOS_UINT8                           ucNotRegAfterAcqSucc;                  /* 搜网成功后是否发起注册:
                                                                                   VOS_FALSE:搜网成功后发起注册(default)
                                                                                   VOS_TRUE:搜网成功后不发起注册 */
    VOS_UINT8                           aucRsv[3];
}NAS_MSCC_PIF_ACQ_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_ACQ_CNF_STRU
 结构说明  : 获取结果的结构体
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
 2.日    期   : 2015年7月20日
   作    者   : w000316404
   修改内容   : R11协议升级(LTE频点配置值扩展)
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_PIF_ACQ_RESULT_ENUM_UINT32                     enAcqRslt;
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
    VOS_UINT32                                              ulArfcn;
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enPrioClass;
    VOS_UINT8                                               aucReserve[3];
}NAS_MSCC_PIF_ACQ_CNF_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_REG_CELL_INFO_STRU
 结构说明  : 注册消息中Cell Info的结构体
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
 2.日    期   : 2015年7月20日
   作    者   : w000316404
   修改内容   : R11协议升级(LTE频点配置值扩展)
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8       ucRat;
    VOS_UINT8                                  ucPlmnNum;
    VOS_UINT8                                  ucCellNum;
    VOS_UINT8                                  aucReserved[1];
    VOS_UINT32                                 ulArfcn;
    NAS_MSCC_PIF_PLMN_ID_STRU                  astPlmnId[NAS_MSCC_PIF_REG_MAX_PLMN_NUM];
    VOS_UINT16                                 ausCellId[NAS_MSCC_PIF_REG_MAX_CELL_NUM];
} NAS_MSCC_PIF_REG_CELL_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_REG_REQ_STRU
 结构说明  : 注册消息的结构体
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT32                                              bitOpPrioClass  : 1;
    VOS_UINT32                                              bitOpCellInfo   : 1;
    VOS_UINT32                                              bitSpare        : 30;
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enPrioClass;
    VOS_UINT8                                               aucReserve[3];
    NAS_MSCC_PIF_REG_CELL_INFO_STRU                         stCellInfo;
}NAS_MSCC_PIF_REG_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_REG_CNF_STRU
 结构说明  : 注册结果的结构体
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
 2.日    期   : 2015年7月20日
   作    者   : w000316404
   修改内容   : R11协议升级(LTE频点配置值扩展)
 3.日    期   : 2015年8月20日
   作    者   : wx270776
   修改内容   : VIA CL DTS2015031602665
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_PIF_REG_RESULT_ENUM_UINT32                     enRegRslt;
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
    VOS_UINT32                                              ulArfcn;
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enPrioClass;
    MMC_MSCC_ATTACH_CL_REG_STATUS_ENUM8                     enLmmAttachClRegStatus;
    VOS_UINT8                                               aucReserve[2];
}NAS_MSCC_PIF_REG_CNF_STRU;


enum NAS_MSCC_PIF_POWER_SAVE_RESULT_ENUM
{
    NAS_MSCC_PIF_POWER_SAVE_SUCCESS             = 0 ,
    NAS_MSCC_PIF_POWER_SAVE_FAILURE             = 1 ,
    NAS_MSCC_PIF_POWER_SAVE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_POWER_SAVE_RESULT_ENUM_UINT8;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_POWER_SAVE_REQ_STRU
 结构说明  : Power save消息的结构体
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                       stMsgHeader;                     /* _H2ASN_Skip */
    NAS_MSCC_PIF_POWER_SAVE_TYPE_ENUM_UINT8    enPowerSaveReason;               /* POWER SAVE原因值 */
    VOS_UINT8                                  aucReserve[3];
}NAS_MSCC_PIF_POWER_SAVE_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_POWER_SAVE_CNF_STRU
 结构说明  : Power save结果的结构体
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
 2.日    期   : 2015年4月07日
   作    者   : m00270891
   修改内容   : Added the result Enum.
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;                     /* _H2ASN_Skip */
    NAS_MSCC_PIF_POWER_SAVE_RESULT_ENUM_UINT8               enResult;
    VOS_UINT8                                               aucReserve[3];
}NAS_MSCC_PIF_POWER_SAVE_CNF_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_ACQ_IND_STRU
 结构说明  : 获取指示的结构体
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
typedef  NAS_MSCC_PIF_ACQ_CNF_STRU NAS_MSCC_PIF_ACQ_IND_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PS_SERVICE_CONN_STATUS_IND_STRU
 结构说明  : mmc上报ps业务信令连接状态指示消息结构
 1.日    期   : 2014年6月27日
   作    者   : s00217060
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                            stMsgHeader;                            /*_H2ASN_Skip*/
    VOS_UINT8                                       ucPsServiceConnStatusFlag;
    MSCC_MMC_PS_SIGNALING_TYPE_ENUM_UINT8           enPsSigType;
    VOS_UINT8                                       aucReserved[2];
}NAS_MSCC_PIF_PS_SERVICE_CONN_STATUS_IND_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU
 结构说明  : MMC通知MMA当前是否有RF资源可用
 1.日    期   : 2014年6月30日
   作    者   : W00176964
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /*_H2ASN_Skip*/
    NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_ENUM_UINT8           enRatType;
    VOS_UINT8                                               ucRfAvailFlg;       /* VOS_TRUE:射频资源可用;VOS_FALSE:RF资源不可用 */
    VOS_UINT8                                               aucReserved[2];
}NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU
 结构说明  : 业务触发搜网的网络模式列表
 1.日    期   : 2015年5月15日
   作    者   : L00301449
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucRatNum;
    NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_ENUM_UINT8                aenRatType[NAS_MSCC_PIF_SRV_ACQ_RAT_NUM_MAX];
}NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_SRV_ACQ_REQ_STRU
 结构说明  : 业务触发搜网指示
 1.日    期   : 2014年5月28日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;                            /*_H2ASN_Skip*/
    NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8    enSrvType;
    VOS_UINT8                           aucReserved[3];
    NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU  stRatList;
} NAS_MSCC_PIF_SRV_ACQ_REQ_STRU;


/*****************************************************************************
 结构名    : NAS_MSCC_PIF_SRV_ACQ_CNF_STRU
 结构说明  : 业务触发搜网结果
 1.日    期   : 2014年5月28日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                            stMsgHeader;                /*_H2ASN_Skip*/
    NAS_MSCC_PIF_SRV_ACQ_RESULT_ENUM_UINT8          enResult;
    VOS_UINT8                                       aucReserved[3];
} NAS_MSCC_PIF_SRV_ACQ_CNF_STRU;



/*****************************************************************************
 结构名    : NAS_MSCC_PIF_BEGIN_SESSION_NOTIFY_STRU
 结构说明  : 业务触发搜网开始指示
 1.日    期   : 2014年5月28日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;                            /*_H2ASN_Skip*/
    NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8    enSrvType;
    VOS_UINT8                           aucReserved[3];
    NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU  stRatList;
}NAS_MSCC_PIF_BEGIN_SESSION_NOTIFY_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_END_SESSION_NOTIFY_STRU
 结构说明  : 业务触发搜网结束指示
 1.日    期   : 2014年5月28日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;                            /*_H2ASN_Skip*/
    NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8    enSrvType;
    VOS_UINT8                           aucReserved[3];
    NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU  stRatList;
}NAS_MSCC_PIF_END_SESSION_NOTIFY_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_IMS_SRV_INFO_NOTIFY_STRU
 结构说明  : ID_NAS_MSCC_PIF_IMS_SRV_INFO_NOTIFY的结构体
 1.日    期   : 2014年11月06日
   作    者   : s00217060
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                       stMsgHeader;                     /* _H2ASN_Skip */
    VOS_UINT8                                  ucImsCallFlg;
    VOS_UINT8                                  aucReserve[3];
}NAS_MSCC_PIF_IMS_SRV_INFO_NOTIFY_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMA_MO_CALL_START_NTF_STRU
 * Description : Mo Call start notification
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;                    /* _H2ASN_Skip */
    NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM_UINT8      enCallType;
    VOS_UINT8                                   aucReserve[3];
}NAS_MSCC_PIF_CDMA_MO_CALL_START_NTF_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU
 * Description : Call redial notification
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;                    /* _H2ASN_Skip */
    NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM_UINT8      enCallType;
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_ENUM_UINT8     enCause;
    VOS_UINT8                                   aucReserve[2];
}NAS_MSCC_PIF_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMA_MO_CALL_SUCCESS_NTF_STRU
 * Description : Mo Call success notification
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;                    /* _H2ASN_Skip */
    NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM_UINT8      enCallType;
    VOS_UINT8                                   aucReserve[3];
}NAS_MSCC_PIF_CDMA_MO_CALL_SUCCESS_NTF_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMA_MO_CALL_END_NTF_STRU
 * Description : Mo Call end notification
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;                    /* _H2ASN_Skip */
    NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM_UINT8      enCallType;
    VOS_UINT8                                   aucReserve[3];
}NAS_MSCC_PIF_CDMA_MO_CALL_END_NTF_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CFREQ_LOCK_NTF_STRU
 * Description : Start confirm
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;                    /* _H2ASN_Skip */
    NAS_MSCC_PIF_CFREQ_LOCK_SET_MODE_ENUM_UINT8 enFreqLockMode;
    VOS_UINT8                                   aucReserve[1];
    VOS_UINT16                                  usCdmaBandClass;
    VOS_UINT16                                  usSid;
    VOS_UINT16                                  usNid;
    VOS_UINT16                                  usCdmaFreq;
    VOS_UINT16                                  usCdmaPn;
    VOS_UINT16                                  usHrpdBandClass;
    VOS_UINT16                                  usHrpdFreq;
    VOS_UINT16                                  usHrpdPn;
    VOS_UINT8                                   aucReserve1[2];
}NAS_MSCC_PIF_CFREQ_LOCK_NTF_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMACSQ_SET_PARA_STRU
 * Description : CdmaCsq set parameters
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRssiRptThreshold;
    VOS_UINT8                           ucEcIoRptThreshold;
    VOS_UINT8                           ucTimeInterval;
    VOS_UINT8                           aucReserve[1];
}NAS_MSCC_PIF_CDMACSQ_SET_PARA_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMACSQ_SET_REQ_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;                            /* _H2ASN_Skip */
    NAS_MSCC_PIF_CDMACSQ_SET_PARA_STRU  stCdmaCsq;
}NAS_MSCC_PIF_CDMACSQ_SET_REQ_STRU;


/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMACSQ_SET_CNF_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                            stMsgHeader;                /* _H2ASN_Skip */
    NAS_MSCC_PIF_CDMACSQ_SET_RESULT_ENUM_UINT8      enRslt;
    VOS_UINT8                                       auReserved[3];
}NAS_MSCC_PIF_CDMACSQ_SET_CNF_STRU;


/** ****************************************************************************
 * Name        : XSD_MMA_CDMACSQ_IND_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                    stMsgHeader;                        /* _H2ASN_Skip */
    VOS_INT16                               sCdmaRssi;
    VOS_INT16                               sCdmaEcIo;
}NAS_MSCC_PIF_CDMACSQ_IND_STRU;


/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_HDR_CSQ_SET_PARA_STRU
 * Description : HDRCsq set parameters
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTimeInterval;
    VOS_UINT8                           ucRssiThreshold;
    VOS_UINT8                           ucSnrThreshold;
    VOS_UINT8                           ucEcioThreshold;
}NAS_MSCC_PIF_HDR_CSQ_SET_PARA_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_HDR_CSQ_SET_REQ_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;                            /* _H2ASN_Skip */
    NAS_MSCC_PIF_HDR_CSQ_SET_PARA_STRU  stHdrCsq;
}NAS_MSCC_PIF_HDR_CSQ_SET_REQ_STRU;


/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_HDR_CSQ_SET_CNF_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                            stMsgHeader;                /* _H2ASN_Skip */
    NAS_MSCC_PIF_HDR_CSQ_SET_RESULT_ENUM_UINT8      enRslt;
    VOS_UINT8                                       auReserved[3];
}NAS_MSCC_PIF_HDR_CSQ_SET_CNF_STRU;


/** ****************************************************************************
 * Name        : XSD_MMA_HDR_CSQ_IND_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                    stMsgHeader;                        /* _H2ASN_Skip */
    VOS_INT16                               sHrpdRssi;
    VOS_INT16                               sHrpdSnr;
    VOS_INT16                               sHrpdEcio;
    VOS_UINT8                               aucRsv[2];
}NAS_MSCC_PIF_HDR_CSQ_IND_STRU;

/** ****************************************************************************
 * Name        : XSD_MMA_OHM_REG_INFO_STRU
 * Description : Register info of Overhead Message
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usRegZone;      /**<  Registration zone */
    VOS_UINT8                           ucRegZoneNum;   /**<  Number of registration zones to be retained */

    /* for reg */
    VOS_UINT8                           ucZoneTimer;    /**<  Zone timer length */

    /* for reg */
    VOS_UINT8                           ucMultiSidFlg;  /**<  Multiple SID storage indicator */

    /* for reg */
    VOS_UINT8                           ucMultiNidFlg;  /**<  Multiple NID storage indicator */

    /* for reg */
    VOS_UINT16                          usRegDistance;  /**<  Registration distance */

    /* for reg */
    VOS_UINT8                           ucRegPeriod;    /**<  Registration period */

    /* for reg */
    VOS_UINT8                           ucHomeReg;      /**<  Home registration indicator */

    /* for roam */
    VOS_UINT8                           ucSidRoamReg;   /**<  SID roamer registration indicator */

    /* for roam */
    VOS_UINT8                           ucNidRoamReg;   /**<  NID roamer registration indicator */

    /* for reg */
    VOS_UINT8                           ucPowerUpReg;   /**<  Power-up registration indicator */

    /* for reg */
    VOS_UINT8                           ucPowerDownReg; /**<  Power-down registration indicator */

    /* for reg */
    VOS_UINT8                           ucParameterReg; /**<  Parameter-change registration indicator */

    /* for reg */
    VOS_UINT8                           aucReserve[1];
}NAS_MSCC_PIF_OHM_REG_INFO_STRU;

/** ****************************************************************************
 * Name        : XSD_MMA_OHM_SERVICE_INFO_STRU
 * Description : Service info of Overhead Message
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMaxAltSo;            /**<  Max. Num. of alternative service options,for Origination or Page Response Message */
    VOS_UINT8                           ucSDBSupported;        /**<  Short Data Burst supported indicator */
    VOS_UINT8                           ucMoQos;               /**<  permission indicator for QoS in Origination message */
    VOS_UINT8                           ucConcurrentSupported; /**<  concurrent service supported */
    VOS_UINT8                           ucMoPosSupported;      /**<  MS initiated position location supported */
    VOS_UINT8                           ucReserve;
    VOS_UINT16                          usImsi11_12;           /**<  11th and 12th digits of the IMSI */
    VOS_UINT32                          ulMcc;                 /**<  Mobile country code */
    VOS_UINT16                          usMnc;                 /**<  Mobile network code */
    VOS_UINT8                           aucReserve[2];
}NAS_MSCC_PIF_OHM_SERVICE_INFO_STRU;

/** ****************************************************************************
 * Name        : XSD_MMA_OHM_BASE_STATION_INFO_STRU
 * Description : Base station info of Overhead Message
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usBaseId;        /**<  Base station identification */

    /* for user zone */
    VOS_UINT8                           ucBaseClass;     /**<  Base station class */
    VOS_UINT8                           aucReserve[1];
    VOS_INT32                           lBaseLatitude;  /**<  Base station latitude */

    /* reg & zone */
    VOS_INT32                           lBaseLongitude; /**<  Base station longitude */

    /* reg & zone */
}NAS_MSCC_PIF_OHM_BASE_STATION_INFO_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_1X_SYS_TIME_STRU
 *
 * Description : System time info
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucSysTime[5];
    VOS_UINT8                           ucLpSec;
    VOS_INT8                            cLtmOff;
    VOS_UINT8                           ucDaylt;
} NAS_MSCC_PIF_1X_SYS_TIME_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_SYSTEM_TIME_IND_STRU
 * Description : System service Info indication
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                    stMsgHeader;                        /* _H2ASN_Skip */
    NAS_MSCC_PIF_1X_SYS_TIME_STRU           stSysTime;
}NAS_MSCC_PIF_1X_SYSTEM_TIME_IND_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU
 * Description : System info
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                                  usBandClass;
    VOS_UINT16                                  usFreq;
    VOS_UINT16                                  usSid;             /**<  System identification */
    VOS_UINT16                                  usNid;             /**<  Network identification */
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32     enServiceStatus;
    VOS_UINT8                                   ucRoamingInd;
    VOS_UINT8                                   ucPrevInUse;
    VOS_UINT8                                   ucPzid;    /* Packet Zone Id */
    NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8           en1xPriClass;         /* 1x priority class */
    NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8           enAIPriClass;         /* AI priority class */
    PS_BOOL_ENUM_UINT8                          enRegInfoIncl;
    PS_BOOL_ENUM_UINT8                          enBaseStationInfoIncl;
    PS_BOOL_ENUM_UINT8                          enServiceInfoIncl;
    NAS_MSCC_PIF_OHM_REG_INFO_STRU              stRegInfo;
    NAS_MSCC_PIF_OHM_BASE_STATION_INFO_STRU     stBaseStationInfo;
    NAS_MSCC_PIF_OHM_SERVICE_INFO_STRU          stServiceInfo;
}NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_SERVICE_INFO_IND_STRU
 * Description : System service Info indication
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                    stMsgHeader;                        /* _H2ASN_Skip */
    NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU       stSysSrvInfo;
}NAS_MSCC_PIF_1X_SYSTEM_SERVICE_INFO_IND_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_CFPLMN_SET_REQ_STRU
 结构说明  : MMA给MMC的SET CFPLMN REQ接口
 1.日    期  : 2015年2月4日
   作    者  : f00279542
   修改内容  : 新增结构
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_PIF_CFPLMN_OPERATE_TYPE_ENUM_UINT8             enCmdType;
    VOS_UINT8                                               aucReserve[3];
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnInfo;
}NAS_MSCC_PIF_CFPLMN_SET_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_CFPLMN_QUERY_REQ_STRU
 结构说明  : MMA给MMC的SET CFPLMN QRY REQ接口
 1.日    期  : 2015年2月4日
   作    者  : f00279542
   修改内容  : 新增结构
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT8                                               aucReserve[4];
}NAS_MSCC_PIF_CFPLMN_QUERY_REQ_STRU;

/*****************************************************************************
 枚举名    : NAS_MSCC_PIF_AP_PRESET_DPLMN_SCENE_ENUM_UINT8
 结构说明  : Ap预置Dplmn的场景
 1.日    期 : 2015年11月02日
   作    者 : l00289540
   修改内容 : 新增结构
*****************************************************************************/
enum NAS_MSCC_PIF_AP_PRESET_DPLMN_SCENE_ENUM
{
    NAS_MSCC_PIF_AP_PRESET_DPLMN_SCENE_SWITCH_ON,                                     /* 上电开机预置DPLMN场景 */
    NAS_MSCC_PIF_AP_PRESET_DPLMN_SCENE_DPLMN_UPDATE,                                  /* Ap Dplmn数据库有更新触发的重新设置DPLMN的场景 */
    NAS_MSCC_PIF_AP_PRESET_DPLMN_SCENE_IMSI_CHANGE,                                   /* 换卡触发的更新DPLMN的场景 */
    NAS_MSCC_PIF_AP_PRESET_DPLMN_SCENE_BUTT
};

typedef VOS_UINT8 NAS_MSCC_PIF_AP_PRESET_DPLMN_SCENE_ENUM_UINT8;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_DPLMN_QRY_REQ_STRU
 结构说明  : MMA给MSCC的DPLMN QRY接口
  1.日    期   : 2015年10月8日
    作    者   : n00355355
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /* _H2ASN_Skip */
    TAF_MMA_CTRL_STRU                                       stCtrl;
    VOS_UINT8                                               aucReserve[4];
}NAS_MSCC_PIF_DPLMN_QRY_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PLMN_WITH_RAT_STRU
 结构说明  : MMA给MSCC的DPLMN SET REQ接口
  1.日    期   : 2015年10月12日
    作    者   : n00355355
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmn;
    VOS_UINT16                                              usRat;
    VOS_UINT8                                               aucReserve[2];
}NAS_MSCC_PIF_PLMN_WITH_RAT_STRU;

/*****************************************************************************
 结构名    : TAF_MMA_DPLMN_INFO_SET_STRU
 结构说明  : set dplmnlist命令中dplmn列表信息、ehplmn列表信息结构体
  1.日    期   : 2015年10月13日
    作    者   : n00355355
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usDplmnNum;                                     /* 预置DPLMN列表的个数 */
    VOS_UINT8                           ucEhPlmnNum;                                    /* EHPLMN的个数*/
    VOS_UINT8                           ucReserve;
    NAS_MSCC_PIF_PLMN_ID_STRU           astEhPlmnInfo[TAF_MMA_MAX_EHPLMN_NUM];          /* EHPLMN ID列表 */
    NAS_MSCC_PIF_PLMN_WITH_RAT_STRU     astDplmnList[TAF_MMA_MAX_DPLMN_NUM];            /* DPLMN列表 */
}NAS_MSCC_PIF_DPLMN_INFO_SET_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_DPLMN_SET_REQ_STRU
 结构说明  : MMA给MSCC的DPLMN SET REQ接口
  1.日    期   : 2015年10月12日
    作    者   : n00355355
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    TAF_MMA_CTRL_STRU                                       stCtrl;
    VOS_UINT8                                               ucSeq;                                          /* 流水号 */
    NAS_MSCC_PIF_AP_PRESET_DPLMN_SCENE_ENUM_UINT8           enApPresetDplmnScene;
    VOS_UINT8                                               aucVersionId[NAS_MSCC_PIF_INFO_VERSION_LEN];     /* 版本号，固定为xx.xx.xxx */
    VOS_UINT8                                               ucReserved;
    NAS_MSCC_PIF_DPLMN_INFO_SET_STRU                        stDplmnInfo;
}NAS_MSCC_PIF_DPLMN_SET_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_CFPLMN_LIST_STRU
 结构说明  : MMC给MSCC 上报的信息
 1.日    期  : 2015年2月4日
   作    者  : f00279542
   修改内容  : 新增结构
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_CFPLMN_OPERATE_TYPE_ENUM_UINT8             ulCmdType;
    VOS_UINT8                                               ucPlmnNum;          /* plmnnum和astplmn用于存放查询的结果 */
    VOS_UINT8                                               aucReserve[2];
    NAS_MSCC_PIF_PLMN_ID_STRU                               astPlmn[NAS_MSCC_PIF_MAX_CFPLMN_NUM];
}NAS_MSCC_PIF_CFPLMN_LIST_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_CFPLMN_SET_CNF_STRU
 结构说明  : MMA给MMC的 CFPLMN CNF接口
 1.日    期  : 2015年2月4日
   作    者  : f00279542
   修改内容  : 新增结构
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_PIF_CFPLMN_OPER_RESULT_ENUM_UINT32             enResult;
}NAS_MSCC_PIF_CFPLMN_SET_CNF_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_CFPLMN_QUERY_CNF_STRU
 结构说明  : MMA给MMC的 CFPLMN CNF接口
 1.日    期  : 2015年2月4日
   作    者  : f00279542
   修改内容  : 新增结构
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_PIF_CFPLMN_OPER_RESULT_ENUM_UINT32             enResult;
    VOS_UINT8                                               aucReserve[3];
    VOS_UINT8                                               ucPlmnNum;                         /* plmnnum和astplmn用于存放查询的结果 */
    NAS_MSCC_PIF_PLMN_ID_STRU                               astPlmn[NAS_MSCC_PIF_MAX_CFPLMN_NUM];
}NAS_MSCC_PIF_CFPLMN_QUERY_CNF_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_CTRL_STRU
 结构说明  : NAS_MSCC控制结构体

 修改历史      :
  1.日    期   : 2015年02月04日
    作    者   : y00307564
    修改内容   : Iteration 8 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulModuleId;         /* 填入PID */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
}NAS_MSCC_CTRL_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_CTRL_STRU
 结构说明  : NAS_MSCC_PLMN_NAME_LIST_STRU

 修改历史      :
  1.日    期   : 2015年02月04日
    作    者   : y00307564
    修改内容   : Iteration 8 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulPlmnNum;
    VOS_BOOL                                                bPlmnSelFlg;
    NAS_MSCC_PIF_OPERATOR_NAME_INFO_STRU                    astPlmnName[NAS_MSCC_PIF_MAX_PLMN_CNT];
    VOS_UINT16                                              ausPlmnRat[NAS_MSCC_PIF_MAX_PLMN_CNT];
    VOS_UINT8                                               aucReserved[2];
}NAS_MSCC_PLMN_NAME_LIST_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_CTRL_STRU
 结构说明  : NAS_MSCC_PLMN_NAME_LIST_STRU

 修改历史      :
  1.日    期   : 2015年02月04日
    作    者   : B00269685
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulPlmnNum;
    VOS_BOOL                                                bPlmnSelFlg;
    NAS_MSCC_PIF_OPERATOR_NAME_INFO_STRU                    astPlmnName[NAS_MSCC_PIF_MAX_CPOL_PLMN_CNT];
    VOS_UINT16                                              ausPlmnRat[NAS_MSCC_PIF_MAX_CPOL_PLMN_CNT];
}NAS_MSCC_CPOL_PLMN_NAME_LIST_STRU;

/*****************************************************************************
结构名    : NAS_MSCC_CPOL_INFO_QUERY_REQ_STRU
结构说明  : AT+CPOL查询请求结构

修改历史      :
  1.日    期   : 2015年02月04日
    作    者   : y00307564
    修改内容   : Iteration 8 新建
*******************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8                       enPrefPLMNType;                         /* 查询运营商名称的类型 */
    VOS_UINT8                                               aucReserved1[3];
    VOS_UINT32                                              ulFromIndex;                            /* 查询运营商名称的起始位置 */
    VOS_UINT32                                              ulPlmnNum;                              /* 查询运营商名称的个数，由于A核和C核通讯，消息大小有限制，因此一次最多查询50条记录 */
    VOS_UINT32                                              ulValidPlmnNum;                         /* 有效输出的运营商名称个数 */
}NAS_MSCC_CPOL_INFO_QUERY_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PREF_PLMN_QUERY_REQ_STRU
 结构说明  : 查询测试PREFPLMN请求接口
 1.日    期   : 2015年02月03日
   作    者   : y00307564
   修改内容   : Iteration 8 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_PIF_PREF_PLMN_CMD_TYPE_ENUM_UINT8              enCmdType;
    VOS_UINT8                                               aucReserve[3];
    VOS_BOOL                                                bPlmnSelFlg;
    NAS_MSCC_CPOL_INFO_QUERY_REQ_STRU                       stCpolInfo;
}NAS_MSCC_PIF_PREF_PLMN_QUERY_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PREF_PLMN_QUERY_CNF_STRU
 结构说明  : 查询测试PREFPLMN请求回复接口
 1.日    期   : 2015年02月03日
   作    者   : y00307564
   修改内容   : Iteration 8 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_PIF_PREF_PLMN_CMD_TYPE_ENUM_UINT8              enCmdType;
    VOS_UINT8                                               aucReserve[1];
    VOS_UINT16                                              usPlmnNum;          /* 用于测试命令输出 */
    VOS_UINT32                                              ulFromIndex;
    VOS_UINT32                                              ulValidPlmnNum;     /* 有效输出的运营商名称个数 */
    NAS_MSCC_CPOL_PLMN_NAME_LIST_STRU                       stPlmnName;
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_ENUM_UINT32          enRslt;
}NAS_MSCC_PIF_PREF_PLMN_QUERY_CNF_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PREF_PLMN_SET_REQ_STRU
 结构说明  : 设置PREFPLMN请求接口
 1.日    期   : 2015年2月3日
   作    者   : y00307564
   修改内容   : Iteration 8 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_CTRL_STRU                                      stCtrl;
    NAS_MSCC_PIF_PREF_PLMN_OPERATE_STRU                     stPrefPlmnOpt;
    NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8                       enPrefPlmnParaType;
    VOS_UINT8                                               aucReserve[3];
}NAS_MSCC_PIF_PREF_PLMN_SET_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PREF_PLMN_SET_CNF_STRU
 结构说明  : 设置PREFPLMN请求回复接口
 1.日    期   : 2015年2月3日
   作    者   : y00307564
   修改内容   : Iteration 8 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_ENUM_UINT32          enRslt;
}NAS_MSCC_PIF_PREF_PLMN_SET_CNF_STRU;


/*****************************************************************************
 结构名    : MMC_TAF_PLMN_INFO_ST
 结构说明  : 记录PLMN信息
 1.日    期   : 2011年7月20日
   作    者   : z00161729
   修改内容   : 原MMC_PLMN_ID_STRU删除替换为TAFMMC_PLMN_ID_STRU
 2.日    期   : 2013年4月7日
   作    者   : z00161729
   修改内容   : 主动上报AT命令控制下移至C核及mma和mmc接口调整
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_PLMN_ID_STRU           stPlmn;
    VOS_UINT16                          usRaMode;
    VOS_UINT8                           ucStatus;
    VOS_UINT8                           aucReserve1[1];
}MMC_TAF_PLMN_INFO_ST;

typedef struct
{
    MMC_TAF_PLMN_INFO_ST    astPlmnInfo[NAS_MSCC_PIF_MAX_PLMN_NUM];
    VOS_UINT16              usCurPlmnNum;
    VOS_UINT8               aucReserve1[2];
}MMC_TAF_PLMN_LIST_INFO_ST;

/*****************************************************************************
 结构名    : MMC_MMA_SHARE_PARA_ST
 结构说明  : 记录MMA和MMC公用的全局变量
 1.日    期   : 2011年7月20日
   作    者   : z00161729
   修改内容   : 原MMC_PLMN_ID_STRU删除替换为TAFMMC_PLMN_ID_STRU
 2.日    期   : 2011年12月5日
   作    者   : z00161729
   修改内容   : 支持CEREG修改，将ucGmmRegStatus改为ucPsRegStatus
 3.日    期   : 2013年4月7日
   作    者   : z00161729
   修改内容   : 主动上报AT命令控制下移至C核及mma和mmc接口调整
*****************************************************************************/
typedef struct
{
    MMC_MMA_PARA_TYPE_ENUM    enMmaParaType;
    union
    {
        MMC_TAF_PLMN_LIST_INFO_ST           stHPlmn;            /*获取HPLMN列表*/
        MMC_TAF_PLMN_LIST_INFO_ST           stUPlmnInfo;
        MMC_TAF_PLMN_LIST_INFO_ST           stOPlmnInfo;
        MMC_TAF_PLMN_LIST_INFO_ST           stHPlmnInfo;
    }u;
}MMC_MMA_SHARE_PARA_ST;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_IMS_SWITCH_STATE_IND_STRU
 结构说明  : 指示IMS关闭状态的接口
 1.日    期   : 2015年04月13日
   作    者   : f0017928
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;
    NAS_MSCC_PIF_IMS_SWITCH_STATE_ENUM_UINT8    enImsSwitch;                    /* IMS能力开关,1:打开,0:关闭 */
    VOS_UINT8                                   aucReserved[3];
}NAS_MSCC_PIF_IMS_SWITCH_STATE_IND_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_VOICE_DOMAIN_CHANGE_IND_STRU
 结构说明  : 指示VOICE DOMAIN变化的接口
 1.日    期   : 2015年04月13日
   作    者   : f0017928
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;
    NAS_MSCC_PIF_VOICE_DOMAIN_ENUM_UINT32       enVoiceDomain;                  /* 语音优选域 */
}NAS_MSCC_PIF_VOICE_DOMAIN_CHANGE_IND_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_IMS_START_REQ_STRU
 结构说明  : 请求IMS开启的接口
 1.日    期   : 2015年04月13日
   作    者   : f0017928
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;
    VOS_UINT8                           aucReserve[4];
}NAS_MSCC_PIF_IMS_START_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_IMS_START_CNF_STRU
 结构说明  : IMS开启请求的回复接口
 1.日    期   : 2015年04月13日
   作    者   : f0017928
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;
    NAS_MSCC_PIF_IMS_START_RESULT_ENUM_UINT32   enResult;
}NAS_MSCC_PIF_IMS_START_CNF_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_IMS_STOP_REQ_STRU
 结构说明  : 请求IMS关闭的接口
 1.日    期   : 2015年04月13日
   作    者   : f0017928
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;
    VOS_UINT8                           aucReserve[4];
}NAS_MSCC_PIF_IMS_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_IMS_STOP_CNF_STRU
 结构说明  : IMS关闭请求的回复接口
 1.日    期   : 2015年04月13日
   作    者   : f0017928
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;
    NAS_MSCC_PIF_IMS_STOP_RESULT_ENUM_UINT32    enResult;
}NAS_MSCC_PIF_IMS_STOP_CNF_STRU;

/*****************************************************************************
 结构名    : MMC_MMA_LAI_STRU
 结构说明  : ID_MMC_MMA_SRCHED_PLMN_INFO_IND消息中lai的结构体
 1.日    期   : 2015年01月15日
   作    者   : h00285180
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_PLMN_ID_STRU                  stPlmnId;

    VOS_UINT16                                 usLac;
    VOS_UINT8                                  aucReserve[2];
}NAS_MSCC_PIF_LAI_STRU;

/*****************************************************************************
 结构名    : MMC_MMA_SRCHED_PLMN_INFO_IND_STRU
 结构说明  : ID_MMC_MMA_SRCHED_PLMN_INFO_IND的结构体
 1.日    期   : 2015年01月15日
   作    者   : h00285180
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                       stMsgHeader;

    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8       enRat;
    VOS_UINT8                                  aucReserved[3];

    VOS_UINT32                                 ulLaiNum;
    NAS_MSCC_PIF_LAI_STRU                      astLai[NAS_MSCC_PIF_MAX_SRCHED_LAI_NUM];
}NAS_MSCC_PIF_SRCHED_PLMN_INFO_IND_STRU;






/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CL_SYSTEM_ACQUIRE_START_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /*_H2ASN_Skip*//* 消息头                                   */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucReserve[2];
}NAS_MSCC_PIF_CL_SYSTEM_ACQUIRE_START_IND_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CL_SYSTEM_ACQUIRE_END_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /*_H2ASN_Skip*//* 消息头                                   */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucRsv[2];
    NAS_MSCC_PIF_CL_ACQUIRED_RESULT_ENUM_UINT32             enRslt;
}NAS_MSCC_PIF_CL_SYSTEM_ACQUIRE_END_IND_STRU;


typedef struct
{
    NAS_MSCC_PIF_PLMN_ID_STRU           stPlmnId;                               /* PLMN ID */
    VOS_UINT16                          usSimRat;                               /* SIM卡中支持的接入技术 */
    VOS_UINT8                           aucReserve[2];
}NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU;


typedef struct
{
    VOS_UINT8                           ucEhPlmnNum;                        /* EHPLMN的个数*/
    VOS_UINT8                           aucRsv[3];
    NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU astEhPlmnInfo[NAS_MSCC_PIF_MAX_EHPLMN_NUM];/* EHPLMN ID列表 */
}NAS_MSCC_PIF_SIM_EHPLMN_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_SIM_USERPLMN_INFO_STRU
 结构说明  : SIM卡中的当前USERPLMN信息
 1.日    期   : 2015年4月14日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUserPlmnNum;                          /* UPLMN的个数*/
    VOS_UINT8                           aucReserve3[3];
    NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU astUserPlmnInfo[NAS_MSCC_PIF_MAX_USERPLMN_NUM];/* UPLMN的列表*/
}NAS_MSCC_PIF_SIM_USERPLMN_INFO_STRU;


/*****************************************************************************
 结构名    : NAS_MSCC_PIF_SIM_OPERPLMN_INFO_STRU
 结构说明  : 保存当前OPERPLMN信息
 1.日    期   : 2015年4月14日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usOperPlmnNum;                          /* OPLMN的个数*/
    VOS_UINT8                           aucReserve2[2];
    NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU astOperPlmnInfo[NAS_MSCC_PIF_MAX_OPERPLMN_NUM];/* OPLMN的列表*/
}NAS_MSCC_PIF_SIM_OPERPLMN_INFO_STRU;


/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PS_RAT_TYPE_NTF_STRU
 结构说明  :  PS RATTYPE
 1.日    期   : 2015年04月13日
   作    者   : f0017928
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;
    NAS_MSCC_PIF_PS_RAT_TYPE_ENUM_UINT32        enPsRatType;
}NAS_MSCC_PIF_PS_RAT_TYPE_NTF_STRU;


/*****************************************************************************
 结构名    : NAS_MSCC_PIF_AUTO_RESEL_SET_STRU
 结构说明  : 设置auto resel
 1.日    期   : 2015年6月3日
   作    者   : b00269685
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;
    VOS_UINT8                           ucActiveFlg;                            /* 是否开启 */
    VOS_UINT8                           aucReserved[3];
}NAS_MSCC_PIF_AUTO_RESEL_SET_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_DPLMN_QRY_CNF_STRU
 结构说明  : DPLMN QRY CNF对应的结构体
  1.日    期   : 2015年10月9日
    作    者   : n00355355
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;
    TAF_MMA_CTRL_STRU                           stCtrl;
    VOS_UINT16                                  ulRslt;
    VOS_UINT8                                   aucVersionId[NAS_MSCC_PIF_INFO_VERSION_LEN];
    VOS_UINT8                                   ucRererse;
}NAS_MSCC_PIF_DPLMN_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_DPLMN_SET_CNF_STRU
 结构说明  : DPLMN SET CNF对应的结构体
  1.日    期   : 2015年10月12日
    作    者   : n00355355
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;
    TAF_MMA_CTRL_STRU                           stCtrl;
    VOS_UINT32                                  ulRslt;
    VOS_UINT8                                   aucReserve[4];
}NAS_MSCC_PIF_DPLMN_SET_CNF_STRU;


/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PLMN_ID_WITH_RAT_STRU
 结构说明  : 带接入技术plmn id信息
 1.日    期   : 2015年9月10日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enRatType;
    VOS_UINT8                                               aucReserved[3];
}NAS_MSCC_PIF_PLMN_ID_WITH_RAT_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_CSG_LIST_SEARCH_REQ_STRU
 结构说明  : CSG 列表搜网请求结构
 1.日    期   : 2015年9月6日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_CSG_LIST_SEARCH_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_CSG_LIST_REJ_STRU
 结构说明  : mmc给mma发送CSG list搜网reject的消息结构
 1.日    期   : 2015年9月6日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_CSG_LIST_REJ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PLMN_WITH_CSG_ID_STRU
 结构说明  : mscc给mma发送CSG list搜网结果信息
 1.日    期   : 2015年9月6日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
    VOS_UINT32                                              ulCsgId;
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enRatType;
    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_TYPE_ENUM_UINT8           enPlmnWithCsgIdType;
    VOS_UINT8                                               ucCsgTypeLen;
    VOS_UINT8                                               ucReserved;
    VOS_UINT8                                               aucCsgType[NAS_MSCC_PIF_CSG_TYPE_LEN];
    VOS_UINT8                                               ucHomeNodeBNameLen;
    VOS_UINT8                                               aucReserved2[3];
    VOS_UINT8                                               aucHomeNodeBName[NAS_MSCC_PIF_MAX_HOME_NODEB_NAME_LEN];
}NAS_MSCC_PIF_PLMN_WITH_CSG_ID_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU
 结构说明  : mmc给mma发送CSG list搜网结果信息
 1.日    期   : 2015年9月6日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPlmnWithCsgIdNum;

    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_STRU  astPlmnWithCsgIdList[NAS_MSCC_PIF_MAX_PLMN_CSG_ID_NUM];
}NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_CSG_LIST_SEARCH_CNF_STRU
 结构说明  : mscc给mma发送CSG list搜网结果的消息结构
 1.日    期   : 2015年9月6日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                    MsgHeader;                              /* _H2ASN_Skip */
    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU stCsgIdInfo;
}NAS_MSCC_PIF_CSG_LIST_SEARCH_CNF_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_CSG_LIST_ABORT_CNF_STRU
 结构说明  : mmc给mma发送CSG list搜网中止回复的消息结构
 1.日    期   : 2015年9月6日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                    MsgHeader;                              /* _H2ASN_Skip */
    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU stCsgIdInfo;
}NAS_MSCC_PIF_CSG_LIST_ABORT_CNF_STRU;



/*****************************************************************************
 结构名    : NAS_MSCC_PIF_CSG_LIST_ABORT_REQ_STRU
 结构说明  : 发送CSG list搜网中止的消息结构
 1.日    期   : 2015年9月6日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_CSG_LIST_ABORT_REQ_STRU;


/*****************************************************************************
 结构名    : NAS_MSCC_PIF_GET_GEO_REQ_STRU
 结构说明  : 获取地理信息请求对应的结构体
 1.日    期   : 2015年05月13日
   作    者   : s00217060
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;
    VOS_UINT8                                   aucReserve[4];
}NAS_MSCC_PIF_GET_GEO_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_GET_GEO_CNF_STRU
 结构说明  : 获取地理信息回复对应的结构体
 1.日    期   : 2015年05月13日
   作    者   : s00217060
   修改内容   : 新建
 2.日    期   : 2015年12月10日
   作    者   : l00324781
   修改内容   : CL_MUTIMODE_OPTIMIZE 修改，增加sid和nid
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;
    NAS_MSCC_PIF_PLMN_ID_STRU                   stPlmnId;
    VOS_INT32                                   lSid; /* 携带X模初搜获得的Sid，如果初搜未能获取Sid,填写-1 */
    VOS_INT32                                   lNid; /* 携带X模初搜获得的Nid，如果初搜未能获取Nid,填写-1 */
}NAS_MSCC_PIF_GET_GEO_CNF_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_STOP_GET_GEO_REQ_STRU
 结构说明  : 停止获取地理信息请求对应的结构体
 1.日    期   : 2015年06月01日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;
    VOS_UINT8                                   aucReserve[4];
}NAS_MSCC_PIF_STOP_GET_GEO_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_STOP_GET_GEO_CNF_STRU
 结构说明  : 停止获取地理信息回复对应的结构体
 1.日    期   : 2015年06月01日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;
    VOS_UINT8                                   aucReserve[4];
}NAS_MSCC_PIF_STOP_GET_GEO_CNF_STRU;


/*****************************************************************************
 结构名    : NAS_MSCC_PIF_SID_NID_IND_STRU
 结构说明  : SID指示
 1.日    期   : 2015年7月2日
   作    者   : y00245242
   修改内容   : 新建
 2.日    期   : 2015年12月15日
   作    者   : l00324781
   修改内容   : CL_MUTIMODE_OPTIMIZE 增加Nid，消息名字改为SID_NID
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;                            /*_H2ASN_Skip*//* 消息头    */
    VOS_UINT16                          usSid;                                  /* SID */
    VOS_UINT16                          usNid;                                  /* NID */
}NAS_MSCC_PIF_SID_NID_IND_STRU;

/*****************************************************************************
 结构名    : XSD_MSCC_EMC_CALLBACK_IND_STRU
 结构说明  : 紧急呼CALLBACK模式状态的消息结构
 1.日    期   : 2015年07月02日
   作    者   : h00313353
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;        /*_H2ASN_Skip*//* 消息头    */
    NAS_MSCC_PIF_EMC_CALLBACK_MODE_ENUM_UINT32  enCallBackState;    /* 是否处于CallBack模式中 */
} NAS_MSCC_PIF_EMC_CALLBACK_IND_STRU;
/*****************************************************************************
 结构名    : NAS_MSCC_PIF_END_EMC_CALLBACK_IND_STRU
 结构说明  : 回复退出紧急呼CallBack请求的消息结构
 1.日    期   : 2015年07月02日
   作    者   : y00322978
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;        /*_H2ASN_Skip*//* 消息头    */
} NAS_MSCC_PIF_END_EMC_CALLBACK_IND_STRU;
/*****************************************************************************
 结构名    : NAS_MSCC_PIF_SID_WHITE_LIST_STRU
 结构说明  : 保存的SID和MCC信息

 1.日    期   : 2015年7月2日
   作    者   : y00322978
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usStartSid;
    VOS_UINT16                          usEndSid;
    VOS_UINT32                          ulMcc;
}NAS_MSCC_PIF_SID_WHITE_LIST_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_OPER_LOCK_WHITE_SID_STRU
 结构说明  : 保存的SID白名单信息
  1.日    期   : 2015年7月2日
    作    者   : y00322978
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnable;                          /* 白名单是否使能 */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usWhiteSysNum;                     /* 支持白名单的个数,个数为0时表示不支持白名单 */
    NAS_MSCC_PIF_SID_WHITE_LIST_STRU    astSysInfo[NAS_MSCC_PIF_MAX_WHITE_LOCK_SID_NUM];
}NAS_MSCC_PIF_OPER_LOCK_SYS_WHITE_STRU;
/*****************************************************************************
 结构名    : NAS_MSCC_PIF_SET_CSIDLIST_REQ_STRU
 结构说明  : sid white list 设置请求结构体
 1.日    期   : 2015年07月02日
   作    者   : y00322978
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                    stMsgHeader;        /*_H2ASN_Skip*//* 消息头    */
    NAS_MSCC_PIF_OPER_LOCK_SYS_WHITE_STRU   stSidWhiteList;
}NAS_MSCC_PIF_SET_CSIDLIST_REQ_STRU;
/*****************************************************************************
 结构名    : NAS_MSCC_PIF_SET_CSIDLIST_CNF_STRU
 结构说明  : sid white list 设置回复结构体
 1.日    期   : 2015年07月02日
   作    者   : y00322978
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;        /*_H2ASN_Skip*//* 消息头    */
    VOS_UINT32                          ulRslt;
}NAS_MSCC_PIF_SET_CSIDLIST_CNF_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_SERVICE_AVAILABLE_IND_STRU
 结构说明  : 服务可用消息结构
 1.日    期   : 2015年07月25日
   作    者   : w00242748
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /*_H2ASN_Skip*//* 消息头    */
    VOS_UINT16                                              usBandClass;
    VOS_UINT16                                              usFreq;
    VOS_UINT16                                              usSid;             /**<  System identification */
    VOS_UINT16                                              usNid;             /**<  Network identification */
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 enServiceStatus;
    VOS_UINT8                                               ucRoamingInd;
    VOS_UINT8                                               aucReserved[3];
}NAS_MSCC_PIF_SYNC_SERVICE_AVAILABLE_IND_STRU;


/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_DATA_CALL_REDIAL_SYS_ACQ_IND_STRU
 *
 * Description : 数据业务触发搜网结果
 1.日    期   : 2015年12月16日
   作    者   : y00314741
   修改内容   : 新建
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;         /*_H2ASN_Skip*//* 消息头                                   */
    NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_UINT32                enRslt;
    NAS_MSCC_PIF_PS_RAT_TYPE_ENUM_UINT32                    enRatType;
} NAS_MSCC_PIF_DATA_CALL_REDIAL_SYS_ACQ_IND_STRU;

typedef NAS_MSCC_PIF_DATA_CALL_REDIAL_SYS_ACQ_IND_STRU    MSCC_MMA_DATA_CALL_REDIAL_SYS_ACQ_IND_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_HDR_CSQ_SET_REQ_STRU
 结构说明  : ID_MMA_MSCC_HDR_CSQ_SET_REQ_STRU消息结构
 1.日    期   : 2015年10月21日
   作    者   : C00299064
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_HDR_CSQ_SET_REQ_STRU    MMA_MSCC_HDR_CSQ_SET_REQ_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_HDR_CSQ_SET_CNF_STRU
 结构说明  : ID_MMA_MSCC_HDR_CSQ_SET_CNF_STRU消息结构
 1.日    期   : 2015年10月21日
   作    者   : C00299064
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_HDR_CSQ_SET_CNF_STRU    MSCC_MMA_HDR_CSQ_SET_CNF_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_HDR_CSQ_IND_STRU
 结构说明  : ID_NAS_MSCC_PIF_HDR_CSQ_IND消息结构
 1.日    期   : 2015年10月21日
   作    者   : C00299064
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_HDR_CSQ_IND_STRU       MSCC_MMA_HDR_CSQ_IND_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/


#if (VOS_OS_VER == VOS_WIN32)
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
