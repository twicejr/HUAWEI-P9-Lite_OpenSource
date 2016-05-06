

#ifndef __ATMTAINTERFACE_H__
#define __ATMTAINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "PsTypeDef.h"
#include "AtMnInterface.h"
/* Modified by s00217060 for VoLTE_PhaseI  项目, 2013-07-27, begin */
#include "NasNvInterface.h"
/* Modified by s00217060 for VoLTE_PhaseI  项目, 2013-07-27, end */
#include "TafNvInterface.h"
#include "MtaCommInterface.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define MTA_CPOS_XML_MAX_LEN            (1024)              /* MTA接收AT下发的XML码流最大长度 */
#define MTA_CPOSR_XML_MAX_LEN           (1024)              /* MTA向AT上报的XML码流最大长度为1024 */
#define MTA_SEC_PACKET_MAX_LEN          (272)               /* AP安全封包的最大长度 */
#define MTA_SIMLOCK_PASSWORD_LEN        (16)                /* 锁网锁卡解锁密码的长度 */

#define MTA_CLIENTID_BROADCAST          (0xFFFF)
#define MTA_INVALID_TAB_INDEX           (0x00)


#define AT_MTA_WRR_AUTOTEST_MAX_PARA_NUM          (10) /* autotest命令下发参数最大个数 */
#define MTA_AT_WRR_AUTOTEST_MAX_RSULT_NUM         (20) /* autotest命令上报结果最大个数 */
#define MTA_AT_WRR_ONE_MEANRPT_MAX_CELL_NUM       (8)  /* 一次测量报告中小区最大个数 */
#define MTA_AT_WRR_MAX_MEANRPT_NUM                (10) /* 上报最近测量报告的最大个数 */

#define MTA_AT_WRR_MAX_NCELL_NUM                  (8)

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-3-25, begin */
#define AT_MTA_RPT_CFG_MAX_SIZE                   (8)
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-3-25, end */

#define AT_MTA_HANDLEDECT_MIN_TYPE                (0)
#define AT_MTA_HANDLEDECT_MAX_TYPE                (4)

#define AT_RSA_CIPHERTEXT_LEN           (128)

#define  AT_MTA_INTEREST_FREQ_MAX_NUM         (0x05)
#define  AT_MTA_MBMS_AVL_SERVICE_MAX_NUM      (0x10)
#define  AT_MTA_ISMCOEX_BANDWIDTH_NUM         (0x06)

#define AT_MTA_MEID_DATA_LEN                         (7)

#define MTA_AT_EFRUIMID_OCTET_LEN_EIGHT                   (8)
#define MTA_AT_EFRUIMID_OCTET_LEN_FIVE                    (5)

#define MTA_AT_UIMID_OCTET_LEN                            (4)

#define AT_MTA_GPS_XO_COEF_NUM                       (4)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : AT_MTA_MSG_TYPE_ENUM
 结构说明  : AT与MTA消息接口枚举
1.日    期  : 2012年06月28日
  作    者  : y00213812
  修改内容  : V7R1C50 A_GPS项目新增结构
2.日    期   : 2012年11月21日
  作    者   : z00161729
  修改内容  : 支持cerssi和nmr
3.日    期   : 2012年12月26日
  作    者   : m00217266
  修改内容   :  添加WAS接口的消息ID
4.日    期  : 2013年03月13日
  作    者  : z00214637
  修改内容  : BodySAR项目
5.日    期   : 2013年3月25日
  作    者   : s00217060
  修改内容   : 添加主动上报下移至C核的消息ID
*****************************************************************************/
enum AT_MTA_MSG_TYPE_ENUM
{
    /* 消息名称 */                      /* 消息ID */        /* 备注, 生成ASN */
    /* AT发给MTA的消息 */
    ID_AT_MTA_CPOS_SET_REQ              = 0x0000,           /* _H2ASN_MsgChoice AT_MTA_CPOS_REQ_STRU        */
    ID_AT_MTA_CGPSCLOCK_SET_REQ         = 0x0001,           /* _H2ASN_MsgChoice AT_MTA_CGPSCLOCK_REQ_STRU   */
    ID_AT_MTA_APSEC_SET_REQ             = 0x0002,           /* _H2ASN_MsgChoice AT_MTA_APSEC_REQ_STRU       */
    ID_AT_MTA_SIMLOCKUNLOCK_SET_REQ     = 0x0003,           /* _H2ASN_MsgChoice AT_MTA_SIMLOCKUNLOCK_REQ_STRU */

    ID_AT_MTA_QRY_NMR_REQ               = 0x0004,           /* _H2ASN_MsgChoice AT_MTA_QRY_NMR_REQ_STRU */

    ID_AT_MTA_RESEL_OFFSET_CFG_SET_NTF  = 0x0005,           /* _H2ASN_MsgChoice AT_MTA_RESEL_OFFSET_CFG_SET_NTF_STRU */
    ID_AT_MTA_WRR_AUTOTEST_QRY_REQ      = 0x0006,           /* _H2ASN_MsgChoice AT_MTA_WRR_AUTOTEST_QRY_PARA_STRU */
    ID_AT_MTA_WRR_CELLINFO_QRY_REQ      = 0x0007,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_WRR_MEANRPT_QRY_REQ       = 0x0008,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_WRR_FREQLOCK_SET_REQ      = 0x0009,           /* _H2ASN_MsgChoice MTA_AT_WRR_FREQLOCK_CTRL_STRU     */
    ID_AT_MTA_WRR_RRC_VERSION_SET_REQ   = 0x000A,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU*/
    ID_AT_MTA_WRR_CELLSRH_SET_REQ       = 0x000B,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU*/
    ID_AT_MTA_WRR_FREQLOCK_QRY_REQ      = 0x000C,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_WRR_RRC_VERSION_QRY_REQ   = 0x000D,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_WRR_CELLSRH_QRY_REQ       = 0x000E,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    ID_AT_MTA_BODY_SAR_SET_REQ          = 0x000F,           /* _H2ASN_MsgChoice AT_MTA_BODY_SAR_SET_REQ_STRU */
    /* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-3-25, begin */
    ID_AT_MTA_CURC_SET_NOTIFY           = 0x0010,           /* _H2ASN_MsgChoice AT_MTA_CURC_SET_NOTIFY_STRU */
    ID_AT_MTA_CURC_QRY_REQ              = 0x0011,           /* _H2ASN_MsgChoice AT_MTA_CURC_QRY_REQ_STRU */
    ID_AT_MTA_UNSOLICITED_RPT_SET_REQ   = 0x0012,           /* _H2ASN_MsgChoice AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU */
    ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ   = 0x0013,           /* _H2ASN_MsgChoice AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU */
    /* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-3-25, end */

    ID_AT_MTA_IMEI_VERIFY_QRY_REQ       = 0x0014,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_CGSN_QRY_REQ              = 0x0015,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_NCELL_MONITOR_SET_REQ     = 0x0016,           /* _H2ASN_MsgChoice AT_MTA_NCELL_MONITOR_SET_REQ_STRU */
    ID_AT_MTA_NCELL_MONITOR_QRY_REQ     = 0x0017,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    ID_AT_MTA_REFCLKFREQ_SET_REQ        = 0x0018,           /* _H2ASN_MsgChoice AT_MTA_REFCLKFREQ_SET_REQ_STRU */
    ID_AT_MTA_REFCLKFREQ_QRY_REQ        = 0x0019,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    ID_AT_MTA_HANDLEDECT_SET_REQ        = 0x001A,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_HANDLEDECT_QRY_REQ        = 0x001B,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    /* Added by l00198894 for 新增+ECID命令, 2013-12-09, begin */
    ID_AT_MTA_ECID_SET_REQ              = 0x001C,           /* _H2ASN_MsgChoice AT_MTA_ECID_SET_REQ_STRU */
    /* Added by l00198894 for 新增+ECID命令, 2013-12-09, end */

    ID_AT_MTA_MIPICLK_QRY_REQ           = 0x001D,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    ID_AT_MTA_SET_DPDTTEST_FLAG_REQ     = 0x001E,           /* _H2ASN_MsgChoice AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU */
    ID_AT_MTA_SET_DPDT_VALUE_REQ        = 0x001F,           /* _H2ASN_MsgChoice AT_MTA_SET_DPDT_VALUE_REQ_STRU */
    ID_AT_MTA_QRY_DPDT_VALUE_REQ        = 0x0020,           /* _H2ASN_MsgChoice AT_MTA_QRY_DPDT_VALUE_REQ_STRU */

    ID_AT_MTA_RRC_PROTECT_PS_REQ        = 0x0021,
    ID_AT_MTA_PHY_INIT_REQ              = 0x0022,

    ID_AT_MTA_SET_JAM_DETECT_REQ        = 0x0023,           /* _H2ASN_MsgChoice AT_MTA_SET_JAM_DETECT_REQ_STRU */

    ID_AT_MTA_SET_FREQ_LOCK_REQ         = 0x0024,           /* _H2ASN_MsgChoice AT_MTA_SET_FREQ_LOCK_REQ_STRU */

    ID_AT_MTA_SET_GSM_FREQLOCK_REQ      = 0x0025,          /* _H2ASN_MsgChoice AT_MTA_SET_GSM_FREQLOCK_REQ_STRU */
    ID_AT_MTA_SET_FEMCTRL_REQ           = 0x0026,

    ID_AT_MTA_NVWRSECCTRL_SET_REQ       = 0x0027,

    ID_AT_MTA_MBMS_SERVICE_OPTION_SET_REQ   = 0x0028,      /* _H2ASN_MsgChoice AT_MTA_MBMS_SERVICE_OPTION_SET_REQ_STRU */
    ID_AT_MTA_MBMS_PREFERENCE_SET_REQ       = 0x0029,      /* _H2ASN_MsgChoice AT_MTA_MBMS_PREFERENCE_SET_REQ_STRU */
    ID_AT_MTA_SIB16_NETWORK_TIME_QRY_REQ    = 0x002A,      /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_BSSI_SIGNAL_LEVEL_QRY_REQ     = 0x002B,      /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_NETWORK_INFO_QRY_REQ          = 0x002C,      /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_EMBMS_STATUS_QRY_REQ          = 0x002D,      /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_MBMS_UNSOLICITED_CFG_SET_REQ  = 0x002E,      /* _H2ASN_MsgChoice AT_MTA_MBMS_UNSOLICITED_CFG_SET_REQ_STRU */
    ID_AT_MTA_LTE_LOW_POWER_SET_REQ         = 0x002F,      /* _H2ASN_MsgChoice AT_MTA_LOW_POWER_CONSUMPTION_SET_REQ_STRU */
    ID_AT_MTA_INTEREST_LIST_SET_REQ         = 0x0030,      /* _H2ASN_MsgChoice AT_MTA_MBMS_INTERESTLIST_SET_REQ_STRU */
    ID_AT_MTA_MBMS_SERVICE_STATE_SET_REQ    = 0x0031,      /* _H2ASN_MsgChoice AT_MTA_MBMS_SERVICE_STATE_SET_REQ_STRU */
    ID_AT_MTA_MBMS_AVL_SERVICE_LIST_QRY_REQ = 0x0032,      /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_LTE_WIFI_COEX_SET_REQ         = 0x0033,      /* _H2ASN_MsgChoice AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU */
    ID_AT_MTA_LTE_WIFI_COEX_QRY_REQ         = 0x0034,      /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    ID_AT_MTA_SET_FR_REQ                = 0x0035,

    ID_AT_MTA_MEID_SET_REQ              = 0x0036,     /* _H2ASN_MsgChoice AT_MTA_MEID_SET_REQ_STRU */
    ID_AT_MTA_MEID_QRY_REQ              = 0x0037,
    ID_AT_MTA_TRANSMODE_QRY_REQ         = 0x0044,

    ID_AT_MTA_UE_CENTER_SET_REQ         = 0x0045,     /* _H2ASN_MsgChoice AT_MTA_SET_UE_CENTER_REQ_STRU */
    ID_AT_MTA_UE_CENTER_QRY_REQ         = 0x0046,

    ID_AT_MTA_SET_NETMON_SCELL_REQ      = 0x0047,
    ID_AT_MTA_SET_NETMON_NCELL_REQ      = 0x0048,

    ID_AT_MTA_RFICSSIRD_QRY_REQ         = 0x0049,

    /* MTA发给AT的消息 */
    ID_MTA_AT_CPOS_SET_CNF              = 0x1000,           /* _H2ASN_MsgChoice MTA_AT_CPOS_CNF_STRU        */
    ID_MTA_AT_CGPSCLOCK_SET_CNF         = 0x1001,           /* _H2ASN_MsgChoice MTA_AT_CGPSCLOCK_CNF_STRU   */
    ID_MTA_AT_CPOSR_IND                 = 0x1002,           /* _H2ASN_MsgChoice MTA_AT_CPOSR_IND_STRU       */
    ID_MTA_AT_XCPOSRRPT_IND             = 0x1003,           /* _H2ASN_MsgChoice MTA_AT_XCPOSRRPT_IND_STRU   */
    ID_MTA_AT_APSEC_SET_CNF             = 0x1004,           /* _H2ASN_MsgChoice MTA_AT_APSEC_CNF_STRU       */
    ID_MTA_AT_SIMLOCKUNLOCK_SET_CNF     = 0x1005,           /* _H2ASN_MsgChoice MTA_AT_SIMLOCKUNLOCK_CNF_STRU */

    ID_MTA_AT_QRY_NMR_CNF               = 0x1006,           /* _H2ASN_MsgChoice MTA_AT_QRY_NMR_CNF_STRU */

    ID_MTA_AT_WRR_AUTOTEST_QRY_CNF      = 0x1007,           /* _H2ASN_MsgChoice MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU       */
    ID_MTA_AT_WRR_CELLINFO_QRY_CNF      = 0x1008,           /* _H2ASN_MsgChoice MTA_AT_WRR_CELLINFO_QRY_CNF_STRU       */
    ID_MTA_AT_WRR_MEANRPT_QRY_CNF       = 0x1009,           /* _H2ASN_MsgChoice MTA_AT_WRR_MEANRPT_QRY_CNF_STRU        */
    ID_MTA_AT_WRR_FREQLOCK_SET_CNF      = 0x100A,           /* _H2ASN_MsgChoice MTA_AT_WRR_FREQLOCK_SET_CNF_STRU       */
    ID_MTA_AT_WRR_RRC_VERSION_SET_CNF   = 0x100B,           /* _H2ASN_MsgChoice MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU    */
    ID_MTA_AT_WRR_CELLSRH_SET_CNF       = 0x100C,           /* _H2ASN_MsgChoice MTA_AT_WRR_CELLSRH_SET_CNF_STRU        */
    ID_MTA_AT_WRR_FREQLOCK_QRY_CNF      = 0x100D,           /* _H2ASN_MsgChoice MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU       */
    ID_MTA_AT_WRR_RRC_VERSION_QRY_CNF   = 0x100E,           /* _H2ASN_MsgChoice MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU    */
    ID_MTA_AT_WRR_CELLSRH_QRY_CNF       = 0x100F,           /* _H2ASN_MsgChoice MTA_AT_WRR_CELLSRH_QRY_CNF_STRU        */

    ID_MTA_AT_BODY_SAR_SET_CNF          = 0x1010,           /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */

    /* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-3-25, begin */
    ID_MTA_AT_CURC_QRY_CNF              = 0x1011,           /* _H2ASN_MsgChoice MTA_AT_CURC_QRY_CNF_STRU */
    ID_MTA_AT_UNSOLICITED_RPT_SET_CNF   = 0x1012,           /* _H2ASN_MsgChoice MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU */
    ID_MTA_AT_UNSOLICITED_RPT_QRY_CNF   = 0x1013,           /* _H2ASN_MsgChoice MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU */
    /* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-3-25, end */

    ID_MTA_AT_IMEI_VERIFY_QRY_CNF       = 0x1014,            /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_MTA_AT_CGSN_QRY_CNF              = 0x1015,            /* _H2ASN_MsgChoice MTA_AT_CGSN_QRY_CNF_STRU */
    ID_MTA_AT_NCELL_MONITOR_SET_CNF     = 0x1016,           /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU        */
    ID_MTA_AT_NCELL_MONITOR_QRY_CNF     = 0x1017,           /* _H2ASN_MsgChoice MTA_AT_NCELL_MONITOR_QRY_CNF_STRU        */
    ID_MTA_AT_NCELL_MONITOR_IND         = 0x1018,           /* _H2ASN_MsgChoice MTA_AT_NCELL_MONITOR_IND_STRU        */

    ID_MTA_AT_REFCLKFREQ_SET_CNF        = 0x1019,           /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_REFCLKFREQ_QRY_CNF        = 0x101A,           /* _H2ASN_MsgChoice MTA_AT_REFCLKFREQ_QRY_CNF_STRU */
    ID_MTA_AT_REFCLKFREQ_IND            = 0x101B,           /* _H2ASN_MsgChoice MTA_AT_REFCLKFREQ_IND_STRU */

    ID_MTA_AT_HANDLEDECT_SET_CNF        = 0x101C,           /* _H2ASN_MsgChoice MTA_AT_HANDLEDECT_SET_CNF_STRU */
    ID_MTA_AT_HANDLEDECT_QRY_CNF        = 0x101D,           /* _H2ASN_MsgChoice MTA_AT_HANDLEDECT_QRY_CNF_STRU */

    ID_MTA_AT_PS_TRANSFER_IND           = 0x101E,           /* _H2ASN_MsgChoice MTA_AT_PS_TRANSFER_IND_STRU */

    /* Added by l00198894 for 新增+ECID命令, 2013-12-09, begin */
    ID_MTA_AT_ECID_SET_CNF              = 0x101F,           /* _H2ASN_MsgChoice MTA_AT_ECID_SET_CNF_STRU */
    /* Added by l00198894 for 新增+ECID命令, 2013-12-09, end */

    ID_MTA_AT_MIPICLK_QRY_CNF           = 0x1020,           /* _H2ASN_MsgChoice MTA_AT_RF_LCD_MIPICLK_CNF_STRU */
    ID_MTA_AT_MIPICLK_INFO_IND          = 0x1021,           /* _H2ASN_MsgChoice MTA_AT_RF_LCD_MIPICLK_IND_STRU */

    ID_MTA_AT_SET_DPDTTEST_FLAG_CNF     = 0x1022,           /* _H2ASN_MsgChoice MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU */
    ID_MTA_AT_SET_DPDT_VALUE_CNF        = 0x1023,           /* _H2ASN_MsgChoice MTA_AT_SET_DPDT_VALUE_CNF_STRU */
    ID_MTA_AT_QRY_DPDT_VALUE_CNF        = 0x1024,           /* _H2ASN_MsgChoice MTA_AT_QRY_DPDT_VALUE_CNF_STRU */

    ID_MTA_AT_RRC_PROTECT_PS_CNF        = 0x1025,
    ID_MTA_AT_PHY_INIT_CNF              = 0x1026,

    ID_MTA_AT_SET_JAM_DETECT_CNF        = 0x1027,           /* _H2ASN_MsgChoice MTA_AT_SET_JAM_DETECT_CNF_STRU */
    ID_MTA_AT_JAM_DETECT_IND            = 0x1028,           /* _H2ASN_MsgChoice MTA_AT_JAM_DETECT_IND_STRU */

    ID_MTA_AT_SET_FREQ_LOCK_CNF         = 0x1029,           /* _H2ASN_MsgChoice MTA_AT_SET_FREQ_LOCK_CNF_STRU */

    ID_MTA_AT_SET_GSM_FREQLOCK_CNF      = 0x102A,           /* _H2ASN_MsgChoice MTA_AT_SET_GSM_FREQLOCK_CNF_STRU */

    ID_AT_MTA_SET_FEMCTRL_CNF           = 0x102B,

    ID_MTA_AT_XPASS_INFO_IND            = 0x102C,

    ID_MTA_AT_NVWRSECCTRL_SET_CNF       = 0x102D,

    ID_MTA_AT_MBMS_SERVICE_OPTION_SET_CNF   = 0x102E,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_MBMS_PREFERENCE_SET_CNF       = 0x102F,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_SIB16_NETWORK_TIME_QRY_CNF    = 0x1030,       /* _H2ASN_MsgChoice MTA_AT_MBMS_SIB16_NETWORK_TIME_QRY_CNF_STRU */
    ID_MTA_AT_BSSI_SIGNAL_LEVEL_QRY_CNF     = 0x1031,       /* _H2ASN_MsgChoice MTA_AT_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU */
    ID_MTA_AT_NETWORK_INFO_QRY_CNF          = 0x1032,       /* _H2ASN_MsgChoice MTA_AT_MBMS_NETWORK_INFO_QRY_CNF_STRU */
    ID_MTA_AT_EMBMS_STATUS_QRY_CNF          = 0x1033,       /* _H2ASN_MsgChoice MTA_AT_EMBMS_STATUS_QRY_CNF_STRU */
    ID_MTA_AT_MBMS_UNSOLICITED_CFG_SET_CNF  = 0x1034,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_MBMS_SERVICE_EVENT_IND        = 0x1035,       /* _H2ASN_MsgChoice MTA_AT_MBMS_SERVICE_EVENT_IND_STRU */
    ID_MTA_AT_LTE_LOW_POWER_SET_CNF         = 0x1036,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_INTEREST_LIST_SET_CNF         = 0x1037,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_MBMS_SERVICE_STATE_SET_CNF    = 0x1038,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF = 0x1039,       /* _H2ASN_MsgChoice MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU */
    ID_MTA_AT_LTE_WIFI_COEX_SET_CNF         = 0x103A,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_LTE_WIFI_COEX_QRY_CNF         = 0x103B,       /* _H2ASN_MsgChoice MTA_AT_LTE_WIFI_COEX_QRY_CNF_STRU */

    ID_MTA_AT_SET_FR_CNF                = 0x103C,

    ID_MTA_AT_MEID_SET_CNF              = 0x103d,     /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */

    ID_MTA_AT_RFICSSIRD_QRY_CNF         = 0x103e,

    ID_MTA_AT_MEID_QRY_CNF              = 0x103f,     /* _H2ASN_MsgChoice MTA_AT_MEID_QRY_CNF_STRU */

    ID_MTA_AT_TRANSMODE_QRY_CNF         = 0x1052,

    ID_MTA_AT_UE_CENTER_SET_CNF         = 0x1053,
    ID_MTA_AT_UE_CENTER_QRY_CNF         = 0x1054,     /* _H2ASN_MsgChoice MTA_AT_QRY_UE_CENTER_CNF_STRU */

    ID_MTA_AT_SET_NETMON_SCELL_CNF      = 0x1055,     /* _H2ASN_MsgChoice MTA_AT_NETMON_CELL_INFO_STRU */
    ID_MTA_AT_SET_NETMON_NCELL_CNF      = 0x1056,     /* _H2ASN_MsgChoice MTA_AT_NETMON_CELL_INFO_STRU */

    ID_AT_MTA_QRY_AFC_CLK_FREQ_XOCOEF_REQ = 0x1057, /* _H2ASN_MsgChoice AT_MTA_QRY_AFC_CLK_FREQ_XOCOEF_REQ_STRU */
    ID_MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF = 0x1058, /* _H2ASN_MsgChoice MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU */

    /* 最后一条消息 */
    ID_AT_MTA_MSG_TYPE_BUTT

};
typedef VOS_UINT32 AT_MTA_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MTA_AT_RESULT_ENUM
 结构说明  : MTA向AT回复的结果码枚举
1.日    期  : 2012年06月28日
  作    者  : y00213812
  修改内容  : V7R1C50 A_GPS项目新增结构
*****************************************************************************/
enum MTA_AT_RESULT_ENUM
{
    /* 与AT模块对应的标准错误码 */
    MTA_AT_RESULT_NO_ERROR                      = 0x000000,                     /* 消息处理正常 */
    MTA_AT_RESULT_ERROR,                                                        /* 消息处理出错 */
    MTA_AT_RESULT_INCORRECT_PARAMETERS,
    MTA_AT_RESULT_OPTION_TIMEOUT,

    /* 预留对应AT标准命令错误码 */

    /* 装备命令特有错误码 */
    MTA_AT_RESULT_DEVICE_ERROR_BASE             = 0x100000,
    MTA_AT_RESULT_DEVICE_SEC_IDENTIFY_FAIL,                                     /* 产线鉴权失败 */
    MTA_AT_RESULT_DEVICE_SEC_SIGNATURE_FAIL,                                    /* 签名校验失败 */
    MTA_AT_RESULT_DEVICE_SEC_DK_INCORRECT,                                      /* 端口密码错误 */
    MTA_AT_RESULT_DEVICE_SEC_UNLOCK_KEY_INCORRECT,                              /* 解锁密码错误 */
    MTA_AT_RESULT_DEVICE_SEC_PH_PHYNUM_LEN_ERROR,                               /* 物理号长度错误 */
    MTA_AT_RESULT_DEVICE_SEC_PH_PHYNUM_VALUE_ERROR,                             /* 物理号码错误 */
    MTA_AT_RESULT_DEVICE_SEC_PH_PHYNUM_TYPE_ERROR,                              /* 物理号类型错误 */
    MTA_AT_RESULT_DEVICE_SEC_RSA_ENCRYPT_FAIL,                                  /* RSA加密失败 */
    MTA_AT_RESULT_DEVICE_SEC_RSA_DECRYPT_FAIL,                                  /* RSA解密失败 */
    MTA_AT_RESULT_DEVICE_SEC_GET_RAND_NUMBER_FAIL,                              /* 获取随机数失败(crypto_rand) */
    MTA_AT_RESULT_DEVICE_SEC_WRITE_HUK_FAIL,                                    /* HUK写入错误 */
    MTA_AT_RESULT_DEVICE_SEC_FLASH_ERROR,                                       /* Flash错误 */
    MTA_AT_RESULT_DEVICE_SEC_NV_ERROR,                                          /* NV读写错误 */
    MTA_AT_RESULT_DEVICE_SEC_OTHER_ERROR,                                       /* 其它错误 */


    /* 私有命令特有错误码 */
    MTA_AT_RESULT_PRICMD_ERROR_BASE             = 0x200000,

    MTA_AT_RESULT_BUTT
};
typedef VOS_UINT32 MTA_AT_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MTA_AT_CGPSCLOCK_ENUM
 结构说明  : RF芯片GPS时钟状态枚举
 1.日    期   : 2012年06月25日
   作    者   : h44270
   修改内容   : Added for AGPS
*****************************************************************************/
enum MTA_AT_CGPSCLOCK_ENUM
{
    MTA_AT_CGPSCLOCK_STOP           = 0,
    MTA_AT_CGPSCLOCK_START,
    MTA_AT_CGPSCLOCK_BUTT
};
typedef VOS_UINT32 MTA_AT_CGPSCLOCK_ENUM_UINT32;


/*****************************************************************************
 枚举名    : MTA_AT_CPOS_OPERATE_TYPE_ENUM
 结构说明  : +CPOS XML码流输入操作类型枚举
 1.日    期   : 2012年06月25日
   作    者   : h44270
   修改内容   : Added for AGPS
*****************************************************************************/
enum MTA_AT_CPOS_OPERATE_TYPE_ENUM
{
    MTA_AT_CPOS_SEND                = 0,
    MTA_AT_CPOS_CANCEL,
    MTA_AT_CPOS_BUTT
};
typedef VOS_UINT32 MTA_AT_CPOS_OPERATE_TYPE_ENUM_UINT32;

/*****************************************************************************
枚举名    : AT_MTA_PERS_CATEGORY_ENUM
枚举说明  : 锁网锁卡的Category类型

  1.日    期   : 2012年9月18日
    作    者   : l00198894
    修改内容   : STK补充特性及DCM需求开发项目新增枚举
*****************************************************************************/
enum AT_MTA_PERS_CATEGORY_ENUM
{
    AT_MTA_PERS_CATEGORY_NETWORK                    = 0x00,                     /* Category: 锁网 */
    AT_MTA_PERS_CATEGORY_NETWORK_SUBSET             = 0x01,                     /* Category: 锁子网 */
    AT_MTA_PERS_CATEGORY_SERVICE_PROVIDER           = 0x02,                     /* Category: 锁SP */
    AT_MTA_PERS_CATEGORY_CORPORATE                  = 0x03,                     /* Category: 锁团体 */
    AT_MTA_PERS_CATEGORY_SIM_USIM                   = 0x04,                     /* Category: 锁(U)SIM卡 */

    AT_MTA_PERS_CATEGORY_BUTT
};
typedef VOS_UINT8 AT_MTA_PERS_CATEGORY_ENUM_UINT8;

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-3-25, begin */
/*****************************************************************************
枚举名    : AT_MTA_RPT_GENERAL_CTRL_TYPE_ENUM
枚举说明  : 主动上报请求类型

  1.日    期   : 2013年3月25日
    作    者   : s00217060
    修改内容   : 新增枚举
*****************************************************************************/
enum AT_MTA_RPT_GENERAL_CTRL_TYPE_ENUM
{
    AT_MTA_RPT_GENERAL_CONTROL_NO_REPORT      = 0x00,                           /* 禁止所有的主动上报 */
    AT_MTA_RPT_GENERAL_CONTROL_REPORT         = 0x01,                           /* 打开所有的主动上报 */
    AT_MTA_RPT_GENERAL_CONTROL_CUSTOM         = 0x02,                           /* 按BIT位控制对应命令的主动上报 */

    AT_MTA_RPT_GENERAL_CONTROL_BUTT
};
typedef VOS_UINT8 AT_MTA_RPT_GENERAL_CTRL_TYPE_ENUM_UINT8;

/*****************************************************************************
枚举名    : AT_MTA_RPT_SET_TYPE_ENUM
枚举说明  : 主动上报请求类型

  1.日    期   : 2013年3月25日
    作    者   : s00217060
    修改内容   : 新增枚举
*****************************************************************************/
enum AT_MTA_RPT_SET_TYPE_ENUM
{
    AT_MTA_SET_MODE_RPT_TYPE            = 0,                                 /* Category: 设置模式变化是否主动上报 */
    AT_MTA_SET_SRVST_RPT_TYPE,
    AT_MTA_SET_RSSI_RPT_TYPE,
    AT_MTA_SET_TIME_RPT_TYPE,
    AT_MTA_SET_CTZR_RPT_TYPE,
    AT_MTA_SET_DSFLOWRPT_RPT_TYPE,
    AT_MTA_SET_SIMST_RPT_TYPE,
    AT_MTA_SET_CREG_RPT_TYPE,
    AT_MTA_SET_CGREG_RPT_TYPE,
    AT_MTA_SET_CEREG_RPT_TYPE,
    AT_MTA_SET_CSID_RPT_TYPE,
    AT_MTA_SET_CLOCINFO_RPT_TYPE,
    AT_MTA_SET_RPT_TYPE_BUTT
};
typedef VOS_UINT32 AT_MTA_RPT_SET_TYPE_ENUM_UINT32;

/*****************************************************************************
枚举名    : AT_MTA_RPT_QRY_TYPE_ENUM
枚举说明  : 主动上报请求类型

  1.日    期   : 2013年4月10日
    作    者   : l00167671
    修改内容   : 新增枚举
*****************************************************************************/
enum AT_MTA_RPT_QRY_TYPE_ENUM
{
    AT_MTA_QRY_TIME_RPT_TYPE = 0,
    AT_MTA_QRY_CTZR_RPT_TYPE,
    AT_MTA_QRY_CSSN_RPT_TYPE,
    AT_MTA_QRY_CUSD_RPT_TYPE,
    AT_MTA_QRY_RPT_TYPE_BUTT
};
typedef VOS_UINT32 AT_MTA_RPT_QRY_TYPE_ENUM_UINT32;

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-3-25, end */

/*****************************************************************************
 枚举名    : AT_MTA_CMD_RPT_FLG_ENUM
 结构说明  : AT命令上报开关标志枚举

  1.日    期   : 2013年07月22日
    作    者   : l00198894
    修改内容   : V9R1 AGPS
*****************************************************************************/
enum AT_MTA_CMD_RPT_FLG_ENUM
{
    AT_MTA_CMD_RPT_FLG_OFF              = 0,                        /* AT命令不主动上报 */
    AT_MTA_CMD_RPT_FLG_ON,                                          /* AT命令主动上报 */
    AT_MTA_CMD_RPT_FLG_BUTT
};
typedef VOS_UINT8 AT_MTA_CMD_RPT_FLG_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AT_MTA_CMD_RATMODE_ENUM
 结构说明  : AT命令带接入模式RatMode枚举

  1.日    期   : 2014年04月8日
    作    者   : g00261581
    修改内容   : 新建
*****************************************************************************/
enum AT_MTA_CMD_RATMODE_ENUM
{
    AT_MTA_CMD_RATMODE_GSM              = 0,
    AT_MTA_CMD_RATMODE_WCDMA,
    AT_MTA_CMD_RATMODE_LTE,
    AT_MTA_CMD_RATMODE_TD,
    AT_MTA_CMD_RATMODE_CDMA,
    AT_MTA_CMD_RATMODE_BUTT
};
typedef VOS_UINT8 AT_MTA_CMD_RATMODE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MTA_AT_JAM_RESULT_ENUM
 结构说明  : JAM DETECT REPORT上报结果枚举

  1.日    期   : 2014年05月5日
    作    者   : g00261581
    修改内容   : 新建
*****************************************************************************/
enum MTA_AT_JAM_RESULT_ENUM
{
    MTA_AT_JAM_RESULT_JAM_DISAPPEARED        = 0x00,                            /* 状态正常无干扰 */
    MTA_AT_JAM_RESULT_JAM_DISCOVERED,                                           /* 干扰存在 */

    MTA_AT_JAM_RESULT_BUTT
};
typedef VOS_UINT32 MTA_AT_JAM_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : AT_MTA_FREQLOCK_RATMODE_ENUM
 结构说明  : AT模块与MTA之间的接入模式枚举

  1.日    期   : 2014年06月11日
    作    者   : g00261581
    修改内容   : 新增
*****************************************************************************/
enum AT_MTA_FREQLOCK_RATMODE_ENUM
{
    AT_MTA_FREQLOCK_RATMODE_GSM         = 0x01,
    AT_MTA_FREQLOCK_RATMODE_WCDMA,
    AT_MTA_FREQLOCK_RATMODE_LTE,
    AT_MTA_FREQLOCK_RATMODE_CDMA1X,
    AT_MTA_FREQLOCK_RATMODE_TD,
    AT_MTA_FREQLOCK_RATMODE_WIMAX,
    AT_MTA_FREQLOCK_RATMODE_EVDO,

    AT_MTA_FREQLOCK_RATMODE_BUTT
};
typedef VOS_UINT8 AT_MTA_FREQLOCK_RATMODE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AT_MTA_GSM_BAND_ENUM
 结构说明  : AT模块与MTA之间的BAND值枚举

  1.日    期   : 2014年06月11日
    作    者   : g00261581
    修改内容   : 新增
*****************************************************************************/
enum AT_MTA_GSM_BAND_ENUM
{
    AT_MTA_GSM_BAND_850                 = 0x00,
    AT_MTA_GSM_BAND_900,
    AT_MTA_GSM_BAND_1800,
    AT_MTA_GSM_BAND_1900,

    AT_MTA_GSM_BAND_BUTT
};
typedef VOS_UINT16 AT_MTA_GSM_BAND_ENUM_UINT16;

/*****************************************************************************
 枚举名    : AT_MTA_CFG_ENUM
 结构说明  : 使能/去使能枚举

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
enum AT_MTA_CFG_ENUM
{
    AT_MTA_CFG_DISABLE                  = 0,
    AT_MTA_CFG_ENABLE                   = 1,
    AT_MTA_CFG_BUTT
};
typedef VOS_UINT8 AT_MTA_CFG_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AT_MTA_MBMS_SERVICE_STATE_SET_ENUM
 结构说明  : MBMS Service状态设置枚举

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
enum AT_MTA_MBMS_SERVICE_STATE_SET_ENUM
{
    AT_MTA_MBMS_SERVICE_STATE_SET_ACTIVE       = 0,
    AT_MTA_MBMS_SERVICE_STATE_SET_DEACTIVE     = 1,
    AT_MTA_MBMS_SERVICE_STATE_SET_DEACTIVE_ALL = 2,
    AT_MTA_MBMS_SERVICE_STATE_SET_BUTT
};
typedef VOS_UINT8 AT_MTA_MBMS_SERVICE_STATE_SET_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AT_MTA_MBMS_CAST_MODE_ENUM
 结构说明  : MBMS广播模式是单播/组播枚举

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
enum AT_MTA_MBMS_CAST_MODE_ENUM
{
    AT_MTA_MBMS_CAST_MODE_UNICAST       = 0,
    AT_MTA_MBMS_CAST_MODE_MULTICAST     = 1,
    AT_MTA_MBMS_CAST_MODE_BUTT
};
typedef VOS_UINT8 AT_MTA_MBMS_CAST_MODE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MTA_AT_EMBMS_FUNTIONALITY_STATUS_ENUM
 结构说明  : EMBMS 功能状态枚举

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
enum MTA_AT_EMBMS_FUNTIONALITY_STATUS_ENUM
{
    MTA_AT_EMBMS_FUNTIONALITY_OFF       = 0,
    MTA_AT_EMBMS_FUNTIONALITY_ON        = 1,
    MTA_AT_EMBMS_FUNTIONALITY_STATUS_BUTT
};
typedef VOS_UINT8 MTA_AT_EMBMS_FUNTIONALITY_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MTA_AT_MBMS_SERVICE_EVENT_ENUM
 结构说明  : MBMS 服务状态事件枚举

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
enum MTA_AT_MBMS_SERVICE_EVENT_ENUM
{
    MTA_AT_MBMS_SERVICE_EVENT_SERVICE_CHANGE       = 0,
    MTA_AT_MBMS_SERVICE_EVENT_NO_SERVICE           = 1,
    MTA_AT_MBMS_SERVICE_EVENT_ONLY_UNICAST         = 2,
    MTA_AT_MBMS_SERVICE_EVENT_SERVICE_AVAILABLE    = 3,
    MTA_AT_MBMS_SERVICE_EVENT_BUTT
};
typedef VOS_UINT8 MTA_AT_MBMS_SERVICE_EVENT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AT_MTA_COEX_BW_TYPE_ENUM
 枚举说明  : LTE&WIFI宽带类型枚举

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
enum AT_MTA_COEX_BW_TYPE_ENUM
{
    AT_MTA_COEX_BAND_WIDTH_6RB          = 0,                                    /* 宽带1.4M */
    AT_MTA_COEX_BAND_WIDTH_15RB         = 1,                                    /* 宽带3M */
    AT_MTA_COEX_BAND_WIDTH_25RB         = 2,                                    /* 宽带5M */
    AT_MTA_COEX_BAND_WIDTH_50RB         = 3,                                    /* 宽带10M */
    AT_MTA_COEX_BAND_WIDTH_75RB         = 4,                                    /* 宽带15M */
    AT_MTA_COEX_BAND_WIDTH_100RB        = 5,                                    /* 宽带20M */
    AT_MTA_COEX_BAND_WIDTH_BUTT
};
typedef VOS_UINT16 AT_MTA_COEX_BW_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : AT_MTA_COEX_CFG_ENUM
 枚举说明  : LTE&WIFI共存方案配置枚举

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增

*****************************************************************************/
enum AT_MTA_COEX_CFG_ENUM
{
    AT_MTA_COEX_CFG_DISABLE             = 0,
    AT_MTA_COEX_CFG_ENABLE              = 1,
    AT_MTA_COEX_CFG_BUTT
};
typedef VOS_UINT16 AT_MTA_COEX_CFG_ENUM_UINT16;

/*****************************************************************************
 枚举名    : AT_MTA_LTE_LOW_POWER_ENUM
 枚举说明  : 低功耗枚举

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增

*****************************************************************************/
enum AT_MTA_LTE_LOW_POWER_ENUM
{
    AT_MTA_LTE_LOW_POWER_NORMAL         = 0,
    AT_MTA_LTE_LOW_POWER_LOW            = 1,
    AT_MTA_LTE_LOW_POWER_BUTT
};
typedef VOS_UINT8 AT_MTA_LTE_LOW_POWER_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AT_MTA_MBMS_PRIORITY_ENUM
 枚举说明  : 服务优先枚举

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增

*****************************************************************************/
enum AT_MTA_MBMS_PRIORITY_ENUM
{
    AT_MTA_MBMS_PRIORITY_UNICAST        = 0,
    AT_MTA_MBMS_PRIORITY_MBMS           = 1,
    AT_MTA_MBMS_PRIORITY_BUTT
};
typedef VOS_UINT8 AT_MTA_MBMS_PRIORITY_ENUM_UINT8;


enum AT_MTA_UE_CENTER_TYPE_ENUM
{
    AT_MTA_UE_CENTER_VOICE_CENTRIC                          = 0,
    AT_MTA_UE_CENTER_DATA_CENTRIC                           = 1,
    AT_MTA_UE_CENTER_BUTT
};
typedef VOS_UINT32 AT_MTA_UE_CENTER_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : AT_MTA_BODY_SAR_STATE_ENUM
 结构说明  : Body SAR 状态枚举
 1.日    期   : 2015年10月30日
   作    者   : w00316404
   修改内容   : 新增枚举(开源整改A、C核解耦)
*****************************************************************************/
enum AT_MTA_BODY_SAR_STATE_ENUM
{
    AT_MTA_BODY_SAR_OFF                 = 0,                                    /* Body SAR功能关闭 */
    AT_MTA_BODY_SAR_ON,                                                         /* Body SAR功能开启 */
    AT_MTA_BODY_SAR_STATE_BUTT
};
typedef VOS_UINT16 AT_MTA_BODY_SAR_STATE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : MTA_AT_REFCLOCK_STATUS_ENUM
 枚举说明  : GPS参考时钟锁定状态枚举

 1.日    期   : 2015年10月30日
   作    者   : w00316404
   修改内容   : 新增枚举(开源整改A、C核解耦)
*****************************************************************************/
enum MTA_AT_REFCLOCK_STATUS_ENUM
{
    MTA_AT_REFCLOCK_UNLOCKED            = 0,                                    /* GPS参考时钟频率非锁定状态 */
    MTA_AT_REFCLOCK_LOCKED,                                                     /* GPS参考时钟频率锁定状态 */
    MTA_AT_REFCLOCK_STATUS_BUTT
};
typedef VOS_UINT16 MTA_AT_REFCLOCK_STATUS_ENUM_UINT16;

/*****************************************************************************
 枚举名    : MTA_AT_GPHY_XPASS_MODE_ENUM
 枚举说明  : G XPASS模式

 1.日    期   : 2015年10月30日
   作    者   : w00316404
   修改内容   : 新增枚举(开源整改A、C核解耦)
*****************************************************************************/
enum MTA_AT_GPHY_XPASS_MODE_ENUM
{
    MTA_AT_GPHY_XPASS_MODE_DISABLE      = 0,                                    /* 非XPASS模式，类似高铁 */
    MTA_AT_GPHY_XPASS_MODE_ENABLE,                                              /* XPASS模式，类似高铁 */
    MTA_AT_GPHY_XPASS_MODE_BUTT
};
typedef VOS_UINT16 MTA_AT_GPHY_XPASS_MODE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : MTA_AT_WPHY_HIGHWAY_MODE_ENUM
 枚举说明  : W高铁模式

 1.日    期   : 2015年10月30日
   作    者   : w00316404
   修改内容   : 新增枚举(开源整改A、C核解耦)
*****************************************************************************/
enum MTA_AT_WPHY_HIGHWAY_MODE_ENUM
{
    MTA_AT_WPHY_HIGHWAY_MODE_DISABLE    = 0,                                    /* W非高铁模式 */
    MTA_AT_WPHY_HIGHWAY_MODE_ENABLE,                                            /* W高铁模式 */
    MTA_AT_WPHY_HIGHWAY_MODE_BUTT
};
typedef VOS_UINT16 MTA_AT_WPHY_HIGHWAY_MODE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : MTA_AT_NETMON_GSM_STATE_ENUM
 结构说明  : network monitor 获取GSMf小区信息状态枚举

  1.日    期   : 2015年10月19日
    作    者   : zwx247453
    修改内容   : 新建
*****************************************************************************/
enum MTA_AT_NETMON_GSM_STATE_ENUM
{
   MTA_AT_NETMON_GSM_STATE_INIT   = 0,
   MTA_AT_NETMON_GSM_STATTE_WAIT_CELL_INFO  = 1,
   MTA_AT_NETMON_GSM_STATTE_WAIT_TA  = 2,
   MTA_AT_NETMON_GSM_STATTE_BUTT
};

typedef VOS_UINT32 MTA_AT_NETMON_GSM_STATE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MTA_AT_NETMON_CELL_INFO_RESULT_ENUM
 结构说明  : network monitor 小区信息查询制式枚举

  1.日    期   : 2015年10月19日
    作    者   : zwx247453
    修改内容   : 新建
*****************************************************************************/

enum MTA_AT_NETMON_CELL_INFO_RAT_ENUM
{
    MTA_AT_NETMON_CELL_INFO_GSM         = 0,
    MTA_AT_NETMON_CELL_INFO_UTRAN_FDD   = 1,
    MTA_AT_NETMON_CELL_INFO_UTRAN_TDD   = 2,
    MTA_AT_NETMON_CELL_INFO_LTE         = 3,
    MTA_AT_NETMON_CELL_INFO_RAT_BUTT
};
typedef VOS_UINT32 MTA_AT_NETMON_CELL_INFO_RAT_ENUM_UINT32;


/*****************************************************************************
 枚举名    : MTA_TAF_CTZR_TYPE
 结构说明  : CTZR上报方式枚举

  1.日    期   : 2015年11月17日
    作    者   : h00360002
    修改内容   : 新建
*****************************************************************************/

enum MTA_TAF_CTZR_TYPE
{
    MTA_TAF_CTZR_OFF            = 0x00,            /* CTZR去使能 */
    MTA_TAF_CTZR_CTZV           = 0x01,            /* CTZR:CTZV */
    MTA_TAF_CTZR_CTZE           = 0x02,            /* CTZR:CTZE */
    MTA_TAF_CTZR_BUTT
};
typedef VOS_UINT32 MTA_TAF_CTZR_TYPE_ENUM_UINT32;

/*****************************************************************************
枚举名    : AT_MTA_TYPE_ENUM
枚举说明  : 数据上报通道类型

  1.日    期   : 2015年12月25日
    作    者   : C00299064
    修改内容   : 新增枚举
*****************************************************************************/
enum AT_MTA_AFC_CLK_STATUS_ENUM
{
    AT_MTA_AFC_CLK_UNLOCKED           = 0,                                     /* AFC UNLOCKED */
    AT_MTA_AFC_CLK_LOCKED,                                                     /* AFC LOCKED */

    AT_MTA_AFC_CLK_STATUS_BUTT
};
typedef VOS_UINT32 AT_MTA_AFC_CLK_STATUS_ENUM_UINT32;


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
/*****************************************************************************
  5 消息头定义
*******************************s**********************************************/
/*****************************************************************************
  6 消息定义
*****************************************************************************/
/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
结构名    : AT_MTA_MSG_STRU
结构说明  : AT模块与MTA模块间的消息结构
1.日    期  : 2012年06月28日
  作    者  : y00213812
  修改内容  : V7R1C50 A_GPS项目新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;                                /* 消息名 */
    AT_APPCTRL_STRU                     stAppCtrl;
    VOS_UINT8                           aucContent[4];                          /* 消息内容 */
} AT_MTA_MSG_STRU;

/*****************************************************************************
结构名    : MTA_AT_CPOS_REQ_MSG_STRU
结构说明  : 来自AT的+CPOS请求消息子结构
1.日    期  : 2012年06月28日
  作    者  : y00213812
  修改内容  : V7R1C50 A_GPS项目新增结构
*****************************************************************************/
typedef struct
{
    MTA_AT_CPOS_OPERATE_TYPE_ENUM_UINT32    enCposOpType;
    VOS_UINT32                              ulXmlLength;
    VOS_CHAR                                acXmlText[MTA_CPOS_XML_MAX_LEN];
} AT_MTA_CPOS_REQ_STRU;

/*****************************************************************************
结构名    : MTA_AT_CPOS_CNF_STRU
结构说明  : 发往AT的+CPOS回复消息子结构
1.日    期  : 2012年06月28日
  作    者  : y00213812
  修改内容  : V7R1C50 A_GPS项目新增结构
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* 命令执行结果 */
} MTA_AT_CPOS_CNF_STRU;

/*****************************************************************************
结构名    : MTA_AT_CPOSR_IND_STRU
结构说明  : +CPOSR主动上报的消息结构
1.日    期  : 2012年06月28日
  作    者  : y00213812
  修改内容  : V7R1C50 A_GPS项目新增结构
*****************************************************************************/
typedef struct
{
    /* AT向MTA上报的XML码流最大长度为1024，同时还需预留一个字节存放字符串结尾的空字符 */
    VOS_CHAR                            acXmlText[MTA_CPOSR_XML_MAX_LEN + 1];
    VOS_UINT8                           aucRsv[3];
} MTA_AT_CPOSR_IND_STRU;

/*****************************************************************************
结构名    : MTA_AT_XCPOSRRPT_IND_STRU
结构说明  : ^XCPOSRRPT主动上报的消息结构
1.日    期  : 2012年06月28日
  作    者  : y00213812
  修改内容  : V7R1C50 A_GPS项目新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulClearFlg;
} MTA_AT_XCPOSRRPT_IND_STRU;

/*****************************************************************************
结构名    : AT_MTA_CGPSCLOCK_REQ_STRU
结构说明  : AT^CGPSCLOCK的回复消息结构
1.日    期  : 2012年06月28日
  作    者  : y00213812
  修改内容  : V7R1C50 A_GPS项目新增结构
*****************************************************************************/
typedef struct
{
    MTA_AT_CGPSCLOCK_ENUM_UINT32        enGpsClockState;                        /* RF芯片GPS时钟状态 */
} AT_MTA_CGPSCLOCK_REQ_STRU;

/*****************************************************************************
结构名    : MTA_AT_CGPSCLOCK_CNF_STRU
结构说明  : AT^CGPSCLOCK的回复消息结构
1.日    期  : 2012年06月28日
  作    者  : y00213812
  修改内容  : V7R1C50 A_GPS项目新增结构
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* 命令执行结果 */
} MTA_AT_CGPSCLOCK_CNF_STRU;

/*****************************************************************************
结构名    : AT_MTA_APSEC_REQ_STRU
结构说明  : AT^APSEC的请求消息结构
1.日    期  : 2012年08月28日
  作    者  : l00198894
  修改内容  : ISDB 安全存储项目新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSPLen;
    VOS_UINT8                           aucSecPacket[MTA_SEC_PACKET_MAX_LEN];
} AT_MTA_APSEC_REQ_STRU;

/*****************************************************************************
结构名    : MTA_AT_APSEC_CNF_STRU
结构说明  : AT^APSEC的回复消息结构
1.日    期  : 2012年08月28日
  作    者  : l00198894
  修改内容  : ISDB 安全存储项目新增结构
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* 命令执行结果 */
    VOS_UINT32                          ulSPLen;
    VOS_UINT8                           aucSecPacket[MTA_SEC_PACKET_MAX_LEN];
} MTA_AT_APSEC_CNF_STRU;

/*****************************************************************************
结构名    : AT_MTA_SIMLOCKUNLOCK_REQ_STRU
结构说明  : AT^SIMLOCKUNLOCK的请求消息结构
1.日    期  : 2012年09月18日
  作    者  : l00198894
  修改内容  : STK补充特性及DCM需求开发项目新增结构
*****************************************************************************/
typedef struct
{
    AT_MTA_PERS_CATEGORY_ENUM_UINT8     enCategory;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucPassword[MTA_SIMLOCK_PASSWORD_LEN];
} AT_MTA_SIMLOCKUNLOCK_REQ_STRU;

/*****************************************************************************
结构名    : MTA_AT_SIMLOCKUNLOCK_CNF_STRU
结构说明  : AT^SIMLOCKUNLOCK的回复消息结构
1.日    期  : 2012年09月18日
  作    者  : l00198894
  修改内容  : STK补充特性及DCM需求开发项目新增结构
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* 命令执行结果 */
} MTA_AT_SIMLOCKUNLOCK_CNF_STRU;


/*****************************************************************************
 结构名    : AT_MTA_QRY_NMR_REQ_STRU
 结构说明  : AT获取NMR的消息请求结构

  1.日    期   : 2012年11月23日
    作    者   : z00161729
    修改内容   : NMR新增结构

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRatType;
    VOS_UINT8                           aucReserve[3];                          /* 预留后续使用 */
}AT_MTA_QRY_NMR_REQ_STRU;

/*****************************************************************************
 结构名    : MTA_AT_QRY_NMR_CNF_STRU
 结构说明  : mta回复at模块nmr查询结果接口结构

  1.日    期   : 2012年11月23日
    作    者   : z00161729
    修改内容   : NMR新增结构

*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32         enResult;
    VOS_UINT8                         ucTotalIndex;
    VOS_UINT8                         ucCurrIndex;
    VOS_UINT16                        usNMRLen;                                 /* NMR数据长度 */
    VOS_UINT8                         aucNMRData[4];                            /* NMR数据首地址 */
}MTA_AT_QRY_NMR_CNF_STRU;



/*****************************************************************************
 结构名    : AT_MTA_RESEL_OFFSET_CFG_SET_REQ_STRU
 结构说明  : AT向MTA发送WLTHRESHOLDCFG的重选参数
  1.日    期   : 2012年12月10日
    作    者   : t00212959
    修改内容   : WLTHRESHOLDCFG新增结构

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucOffsetFlg;                    /* 0:灭屏；1:亮屏*/
    VOS_UINT8                                   aucReserve[3];                  /* 预留后续使用 */
}AT_MTA_RESEL_OFFSET_CFG_SET_NTF_STRU;

/*****************************************************************************
 结构名    : AT_MTA_WRR_AUTOTEST_QRY_PARA_STRU
 结构说明  : AS测试命令参数

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCmd;
    VOS_UINT8                           ucParaNum;
    VOS_UINT16                          usReserve;
    VOS_UINT32                          aulPara[AT_MTA_WRR_AUTOTEST_MAX_PARA_NUM];
}AT_MTA_WRR_AUTOTEST_QRY_PARA_STRU;

/*****************************************************************************
 结构名    : MTA_AT_WRR_AUTOTEST_QRY_RSLT_STRU
 结构说明  : WAS测试命令返回结果

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRsltNum;
    VOS_UINT32                          aulRslt[MTA_AT_WRR_AUTOTEST_MAX_RSULT_NUM];
}MTA_AT_WRR_AUTOTEST_QRY_RSLT_STRU;

/*****************************************************************************
 结构名    : MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU
 结构说明  : WAS测试命令返回结果消息结构

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
    MTA_AT_WRR_AUTOTEST_QRY_RSLT_STRU   stWrrAutoTestRslt;
} MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_AT_WRR_CELLINFO_STRU
 结构说明  : 小区信息结构

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      usCellFreq;
    VOS_UINT16                      usPrimaryScramCode;
    VOS_INT16                       sCpichRscp;
    VOS_INT16                       sCpichEcN0;

}MTA_AT_WRR_CELLINFO_STRU;

/*****************************************************************************
 结构名    : MTA_AT_WRR_CELLINFO_RSLT_STRU
 结构说明  : WRR回复MTA小区信息查询结构

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
     VOS_UINT32                     ulCellNum;
     MTA_AT_WRR_CELLINFO_STRU       astWCellInfo[MTA_AT_WRR_MAX_NCELL_NUM];         /*最多支持W 8个邻区的查询*/

} MTA_AT_WRR_CELLINFO_RSLT_STRU;
/*****************************************************************************
 结构名    : MTA_AT_WRR_CELLINFO_QRY_CNF_STRU
 结构说明  : WRR回复MTA小区信息查询结构

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
    MTA_AT_WRR_CELLINFO_RSLT_STRU       stWrrCellInfo;
} MTA_AT_WRR_CELLINFO_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_AT_WRR_MEANRPT_STRU
 结构说明  : 测量报告中的事件+小区

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      usEventId;                                  /*对应的事件类型*/
    VOS_UINT16                      usCellNum;
    VOS_UINT16                      ausPrimaryScramCode[MTA_AT_WRR_ONE_MEANRPT_MAX_CELL_NUM];
}MTA_AT_WRR_MEANRPT_STRU;

/*****************************************************************************
 结构名    : MTA_AT_WRR_MEANRPT_RSLT_STRU
 结构说明  : 自动化测试AT^MEANRPT,
             查询最近最多10次测量报告中的事件+小区

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulRptNum;
    MTA_AT_WRR_MEANRPT_STRU         astMeanRptInfo[MTA_AT_WRR_MAX_MEANRPT_NUM];
}MTA_AT_WRR_MEANRPT_RSLT_STRU;

/*****************************************************************************
 结构名    : MTA_AT_WRR_MEANRPT_QRY_CNF_STRU
 结构说明  : WRR给MTA回复^MEANRPT请求的消息结构

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
    MTA_AT_WRR_MEANRPT_RSLT_STRU        stMeanRptRslt;
} MTA_AT_WRR_MEANRPT_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_AT_WRR_FREQLOCK_CTRL_STRU
 结构说明  : WAS锁频控制结构

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucFreqLockEnable;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT16                          usLockedFreq;
} MTA_AT_WRR_FREQLOCK_CTRL_STRU;

/*****************************************************************************
 结构名    : MTA_AT_WRR_FREQLOCK_SET_CNF_STRU
 结构说明  : MTA给AT回的锁频控制结构

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
} MTA_AT_WRR_FREQLOCK_SET_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU
 结构说明  : MTA给AT回的锁频控制结构

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
    MTA_AT_WRR_FREQLOCK_CTRL_STRU       stFreqLockInfo;
} MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU
 结构说明  : WRR给MTA上报version设置结果

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
} MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU
 结构说明  : WRR给MTA上报version查询结果

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucRrcVersion;
    VOS_UINT8                           aucReserved[3];
} MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_AT_WRR_CELLSRH_SET_CNF_STRU
 结构说明  : WRR给MTA上报cellsrh设置结果

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
} MTA_AT_WRR_CELLSRH_SET_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_AT_WRR_CELLSRH_QRY_CNF_STRU
 结构说明  : WRR给MTA上报cellsrh查询结果

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucCellSearchType;
    VOS_UINT8                           aucReserve[3];
} MTA_AT_WRR_CELLSRH_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : AT_MTA_BODY_SAR_SET_REQ_STRU
 结构说明  : AT向MTA发送BODYSAR门限设置参数
  1.日    期   : 2013年03月11日
    作    者   : z00214637
    修改内容   : ^BODYSARON新增结构
*****************************************************************************/
typedef struct
{
    AT_MTA_BODY_SAR_STATE_ENUM_UINT16   enState;       /* Body SAR状态 */
    VOS_UINT16                          usRsv;         /* 保留位 */
    MTA_BODY_SAR_PARA_STRU              stBodySARPara; /* Body SAR功率门限参数 */
}AT_MTA_BODY_SAR_SET_REQ_STRU;

/*******************************************************************************
 结构名    : MTA_AT_RESULT_CNF_STRU
 结构说明  : AT设置消息操作结果的回复消息结构体
 1.日    期   : 2013年03月11日
   作    者   : z00214637
   修改内容   : 新增结构体
*******************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;      /* 操作结果 */
}MTA_AT_RESULT_CNF_STRU;

/*******************************************************************************
 结构名    : AT_MTA_RESERVE_STRU
 结构说明  : AT与MTA消息保留结构体
 1.日    期   : 2013年03月11日
   作    者   : z00214637
   修改内容   : 新增结构体
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserved[4]; /* 保留位 */
}AT_MTA_RESERVE_STRU;

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-3-25, begin */
/*****************************************************************************
 结构名    : AT_MTA_CSSN_RPT_FLG_STRU
 结构说明  : CSSN是否主动上报标识结构体，包括CSSI是否主动上报和CSSU是否主动上报

  1.日    期   : 2013年3月25日
    作    者   : s00217060
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCssiRptFlg;                           /* 禁止或使能+CSSI的补充业务通知 0:不上报;1:上报 */
    VOS_UINT8                           ucCssuRptFlg;                           /* 禁止或使能+CSSU的补充业务通知 0:不上报;1:上报 */
} AT_MTA_CSSN_RPT_FLG_STRU;

/*****************************************************************************
 结构名    : AT_MTA_CURC_SET_NOTIFY_STRU
 结构说明  : AT给MTA发送设置CURC请求

  1.日    期   : 2013年3月25日
    作    者   : s00217060
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    AT_MTA_RPT_GENERAL_CTRL_TYPE_ENUM_UINT8     enCurcRptType;                  /* 主动上报模式，0:关闭所有的主动上报；1:打开所有的主动上报；2:根据RptCfg参数决定对应的bit位是否主动上报 */
    VOS_UINT8                                   aucReserve[3];                  /* 保留字段 */
    VOS_UINT8                                   aucRptCfg[AT_MTA_RPT_CFG_MAX_SIZE];                   /* 64bit主动上报标识 */
} AT_MTA_CURC_SET_NOTIFY_STRU;

/*****************************************************************************
 结构名    : AT_MTA_CURC_QRY_REQ_STRU
 结构说明  : AT给MTA发送查询CURC请求

  1.日    期   : 2013年3月25日
    作    者   : s00217060
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve[4];
} AT_MTA_CURC_QRY_REQ_STRU;

/*****************************************************************************
 结构名    : AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU
 结构说明  : AT给MTA发送单个命令设置主动上报请求

  1.日    期   : 2013年3月25日
    作    者   : s00217060
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    AT_MTA_RPT_SET_TYPE_ENUM_UINT32     enReqType;                              /* 请求类型 */

    union
    {
        VOS_UINT8                       ucModeRptFlg;                           /* mode是否主动上报标识 0:不上报，1:上报 */
        VOS_UINT8                       ucSrvstRptFlg;                          /* service status是否主动上报标识 */
        VOS_UINT8                       ucRssiRptFlg;                           /* rssi是否主动上报标识 */
        VOS_UINT8                       ucTimeRptFlg;                           /* time是否主动上报标识 */
        VOS_UINT8                       ucCtzrRptFlg;                           /* ctzr是否主动上报标识 */
        VOS_UINT8                       ucDsFlowRptFlg;                         /* 流量是否主动上报标识 */
        VOS_UINT8                       ucSimstRptFlg;                          /* sim卡状态是否主动上报标识 */
        VOS_UINT8                       ucCregRptFlg;                           /* cs域注册状态是否主动上报标识 */
        VOS_UINT8                       ucCgregRptFlg;                          /* ps域注册状态是否主动上报标识 */
        VOS_UINT8                       ucCeregRptFlg;                          /* L注册状态是否主动上报标识 */
        VOS_UINT8                       ucCsidRptFlg;                           /* CSID是否主动上报标识 */
        VOS_UINT8                       ucClocinfoRptFlg;                       /* CLOCINFO是否主动上报标识 */
    }u;

    VOS_UINT8                           aucReserve[3];

 } AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU;

/*****************************************************************************
 结构名    : AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU
 结构说明  : AT给MTA发送查询单个命令主动上报请求

  1.日    期   : 2013年3月25日
    作    者   : s00217060
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    AT_MTA_RPT_QRY_TYPE_ENUM_UINT32     enReqType;
} AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU;

/*****************************************************************************
 结构名    : AT_MTA_NCELL_MONITOR_SET_REQ_STRU
 结构说明  : AT给MTA发送NCELLMONITOR设置请求

  1.日    期   : 2013年3月25日
    作    者   : s00217060
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSwitch;
    VOS_UINT8                           aucReserve[3];
} AT_MTA_NCELL_MONITOR_SET_REQ_STRU;


/*****************************************************************************
 结构名    : MTA_AT_CURC_QRY_CNF_STRU
 结构说明  : MTA给AT发送查询CURC回复

  1.日    期   : 2013年3月25日
    作    者   : s00217060
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32                   enResult;
    AT_MTA_RPT_GENERAL_CTRL_TYPE_ENUM_UINT8     enCurcRptType;                          /* 主动上报模式，0:关闭所有的主动上报；1:打开所有的主动上报；2:根据ReportCfg参数决定对应的bit位是否主动上报 */
    VOS_UINT8                                   aucReserve[3];
    VOS_UINT8                                   aucRptCfg[AT_MTA_RPT_CFG_MAX_SIZE];  /* 主动上报标识 */
} MTA_AT_CURC_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU
 结构说明  : MTA给AT发送单个命令设置主动上报回复

  1.日    期   : 2013年3月25日
    作    者   : s00217060
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU
 结构说明  : MTA给AT发送查询单个命令主动上报回复

  1.日    期   : 2013年3月25日
    作    者   : s00217060
    修改内容   : 创建
  2.日    期   : 2015年11月19日
    作    者   : h00360002
    修改内容   : ctzr添加ctze上报
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    AT_MTA_RPT_QRY_TYPE_ENUM_UINT32     enReqType;

    union
    {
        VOS_UINT8                       ucTimeRptFlg;                           /* time是否主动上报标识 */
        MTA_TAF_CTZR_TYPE_ENUM_UINT32   ucCtzrRptFlg;                           /* ctzr是否主动上报标识 */
        AT_MTA_CSSN_RPT_FLG_STRU        stCssnRptFlg;                           /* cssn是否主动上报标识结构体 */
        VOS_UINT8                       ucCusdRptFlg;                           /* cusd是否主动上报标识结构体 */
    }u;

} MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU;

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-3-25, end */


/*******************************************************************************
 结构名    : MTA_AT_CGSN_QRY_CNF_STRU
 结构说明  : ID_MTA_AT_CGSN_QRY_CNF消息
 1.日    期   : 2013年05月25日
   作    者   : Y00213812
   修改内容   : 新增结构体
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucImei[NV_ITEM_IMEI_SIZE]; /* IMEI号码 */
}MTA_AT_CGSN_QRY_CNF_STRU;
/*****************************************************************************
 结构名    : MTA_AT_NCELL_MONITOR_QRY_CNF_STRU
 结构说明  : MTA发给AT的查询异系统小区变化信息控制请求消息的回复

  1.日    期   : 2013年5月31日
    作    者   : s00217060
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT8                           ucSwitch;
    VOS_UINT8                           ucNcellState;
    VOS_UINT8                           aucReserved[2];
} MTA_AT_NCELL_MONITOR_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_AT_NCELL_MONITOR_IND_STRU
 结构说明  : MTA发给AT的异系统小区变化主动上报信息

  1.日    期   : 2013年5月31日
    作    者   : s00217060
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNcellState;
    VOS_UINT8                           aucReserved[3];
} MTA_AT_NCELL_MONITOR_IND_STRU;


/*****************************************************************************
结构名    : AT_MTA_REFCLKFREQ_SET_REQ_STRU
结构说明  : AT^REFCLKFREQ设置命令的请求消息结构

1.日    期   : 2013年07月22日
  作    者   : l00198894
  修改内容   : V9R1 AGPS
*****************************************************************************/
typedef struct
{
    AT_MTA_CMD_RPT_FLG_ENUM_UINT8       enRptFlg;                               /* 命令上报开关标志 */
    VOS_UINT8                           aucReserved1[3];                        /* 保留位 */
} AT_MTA_REFCLKFREQ_SET_REQ_STRU;

/*****************************************************************************
结构名    : MTA_AT_REFCLKFREQ_QRY_CNF_STRU
结构说明  : AT^REFCLKFREQ查询命令的回复消息结构

1.日    期   : 2013年07月22日
  作    者   : l00198894
  修改内容   : V9R1 AGPS
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT32                          ulFreq;                                 /* GPS参考时钟的频率值，单位Hz */
    VOS_UINT32                          ulPrecision;                            /* 当前GPS参考时钟的精度，单位ppb */
    MTA_AT_REFCLOCK_STATUS_ENUM_UINT16  enStatus;                               /* 时钟频率锁定状态 */
    VOS_UINT8                           aucReserved1[2];                        /* 保留位 */
} MTA_AT_REFCLKFREQ_QRY_CNF_STRU;


/*****************************************************************************
 结构名    : AT_MTA_RFICSSIRD_REQ_STRU
 结构说明  :
 1.日    期   : 2015年10月29日
   作    者   : x00316382
   修改内容   : Added for tool
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usChannelNo;                            /* 接收端地址 */
    VOS_UINT16                          usRficReg;
}AT_MTA_RFICSSIRD_REQ_STRU;

/*****************************************************************************
结构名    : MTA_AT_RFICSSIRD_CNF_STRU
结构说明  : AT^SSIRD查询命令的回复消息结构

1.日    期   : 2015年10月29日
  作    者   : x00316382
  修改内容   : Rfic SSI Rd
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRegValue;                             /* 回复的寄存器的值 */
} MTA_AT_RFICSSIRD_CNF_STRU;

/*****************************************************************************
结构名    : MTA_AT_REFCLKFREQ_IND_STRU
结构说明  : GPS参考时钟状态信息主动上报消息结构

1.日    期   : 2013年07月22日
  作    者   : l00198894
  修改内容   : V9R1 AGPS
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFreq;                                 /* GPS参考时钟的频率值，单位Hz */
    VOS_UINT32                          ulPrecision;                            /* 当前GPS参考时钟的精度，单位ppb */
    MTA_AT_REFCLOCK_STATUS_ENUM_UINT16  enStatus;                               /* 时钟频率锁定状态 */
    VOS_UINT8                           aucReserved1[2];                        /* 保留位 */
} MTA_AT_REFCLKFREQ_IND_STRU;


/*****************************************************************************
结构名    : MTA_AT_HANDLEDECT_SET_CNF_STRU
结构说明  : 设置物理层左右手手持状态信息cnf消息

1.日    期   : 2013年08月08日
  作    者   : m00217266
  修改内容   : AP Sensor
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* 操作结果 */
} MTA_AT_HANDLEDECT_SET_CNF_STRU;

/*****************************************************************************
结构名    : MTA_AT_HANDLEDECT_QRY_CNF_STRU
结构说明  : 查询物理层左右手手持状态信息cnf消息

1.日    期   : 2013年08月08日
  作    者   : m00217266
  修改内容   : AP Sensor
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usHandle;                               /* 左右手类型 */
    VOS_UINT16                          aucReserved1[1];
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* 操作结果 */
} MTA_AT_HANDLEDECT_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_AT_PS_TRANSFER_IND_STRU
 结构说明  : 上报PS域迁移指示结构体

  1.日    期   : 2013年10月21日
    作    者   : l00198894
    修改内容   : V9R1C50 SVLTE离网重选项目新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCause;                                /* PS域迁移原因值 */
    VOS_UINT8                           aucReserved1[3];                        /* 保留位 */
} MTA_AT_PS_TRANSFER_IND_STRU;

/*****************************************************************************
 结构名    : MTA_AT_RF_LCD_MIPICLK_IND_STRU
 结构说明  : 上报MIPICLK结构体

  1.日    期   : 2014年03月04日
    作    者   : j00174725
    修改内容   : RF&LCD INTRUSION项目新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMipiClk;                              /* 主动上报MIPICLK值 */
    VOS_UINT8                           aucReserved1[2];                        /* 保留位 */
} MTA_AT_RF_LCD_MIPICLK_IND_STRU;

/*****************************************************************************
 结构名    : MTA_AT_RF_LCD_MIPICLK_CNF_STRU
 结构说明  : 上报MIPICLK结构体

  1.日    期   : 2014年03月04日
    作    者   : j00174725
    修改内容   : RF&LCD INTRUSION项目新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMipiClk;                              /* 主动上报MIPICLK值 */
    VOS_UINT16                          usResult;
} MTA_AT_RF_LCD_MIPICLK_CNF_STRU;

/* Added by l00198894 for 新增+ECID命令, 2013-12-09, begin */
/*******************************************************************************
 结构名    : AT_MTA_ECID_SET_REQ_STRU
 结构说明  : AT与MTA命令+ECID设置请求消息结构体

  1.日    期   : 2013年12月10日
    作    者   : l00198894
    修改内容   : 新增结构体
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulVersion;                              /* 命令版本号 */
}AT_MTA_ECID_SET_REQ_STRU;

/*******************************************************************************
 结构名    : MTA_AT_ECID_SET_CNF_STRU
 结构说明  : AT与MTA命令+ECID设置回复消息结构体

  1.日    期   : 2013年12月10日
    作    者   : l00198894
    修改内容   : 新增结构体
*******************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT8                           aucCellInfoStr[4];                      /* 增强型小区信息字符串 */
}MTA_AT_ECID_SET_CNF_STRU;
/* Added by l00198894 for 新增+ECID命令, 2013-12-09, end */

/*****************************************************************************
 结构名    : AT_MTA_RRC_PROTECT_PS_REQ_STRU
 结构说明  : AT获取PSPROTECTMODE的消息请求结构

  1.日    期   : 2014年3月25日
    作    者   : y00176023
    修改内容   : PSPROTECTMODE新增结构

*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enPsProtectFlg;
    VOS_UINT8                           aucReserve[3];                          /* 预留后续使用 */
}AT_MTA_RRC_PROTECT_PS_REQ_STRU;

/*****************************************************************************
 结构名    : MTA_AT_RRC_PROTECT_PS_CNF_STRU
 结构说明  : AT获取PSPROTECTMODE的消息请求结构

  1.日    期   : 2014年3月25日
    作    者   : y00176023
    修改内容   : PSPROTECTMODE新增结构

*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                          /* 返回给AT的结果 */
}MTA_AT_RRC_PROTECT_PS_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_AT_PHY_INIT_CNF_STRU
 结构说明  : AT获取PHYINIT的消息请求结构

  1.日    期   : 2014年3月25日
    作    者   : y00176023
    修改内容   : PHYINIT新增结构

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve[4];                          /* 预留后续使用 */
}AT_MTA_PHY_INIT_REQ_STRU;

/*****************************************************************************
 结构名    : MTA_AT_PHY_INIT_CNF_STRU
 结构说明  : AT请求物理层初始化物理层回复的消息结构

  1.日    期   : 2014年3月26日
    作    者   : y00176023
    修改内容   : PHYINIT新增结构
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                          /* 返回给AT的结果 */
}MTA_AT_PHY_INIT_CNF_STRU;


/*****************************************************************************
 结构名    : AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU
 结构说明  : AT发给MTA的设置DPDT TEST FLAG的消息结构

  1.日    期   : 2014年4月04日
    作    者   : g00261581
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    AT_MTA_CMD_RATMODE_ENUM_UINT8       enRatMode;
    VOS_UINT8                           ucFlag;
    VOS_UINT8                           aucReserved[2];
} AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU;

/*****************************************************************************
 结构名    : AT_MTA_SET_DPDT_VALUE_REQ_STRU
 结构说明  : AT发给MTA的设置DPDT当前天线使用状态的消息结构

  1.日    期   : 2014年4月04日
    作    者   : g00261581
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    AT_MTA_CMD_RATMODE_ENUM_UINT8       enRatMode;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulDpdtValue;
} AT_MTA_SET_DPDT_VALUE_REQ_STRU;

/*****************************************************************************
 结构名    : AT_MTA_QRY_DPDT_VALUE_PARA_STRU
 结构说明  : AT发给MTA的查询DPDT VAlUE的消息结构

  1.日    期   : 2014年4月04日
    作    者   : g00261581
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    AT_MTA_CMD_RATMODE_ENUM_UINT8       enRatMode;
    VOS_UINT8                           aucReserved[3];
} AT_MTA_QRY_DPDT_VALUE_REQ_STRU;

/*****************************************************************************
 结构名    : MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU
 结构说明  : MTA发往AT的设置DPDTTEST Flag开关回复消息结构

  1.日    期   : 2014年4月04日
    作    者   : g00261581
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_AT_SET_DPDT_VALUE_CNF_STRU
 结构说明  : MTA发往AT的设置DPDT Value回复消息结构

  1.日    期   : 2014年4月04日
    作    者   : g00261581
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_DPDT_VALUE_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_AT_QRY_DPDT_VALUE_CNF_STRU
 结构说明  : MTA发往AT的回复查询DPDT VAlUE的消息结构

  1.日    期   : 2014年4月04日
    作    者   : g00261581
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDpdtValue;
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_QRY_DPDT_VALUE_CNF_STRU;

/*****************************************************************************
 结构名    : AT_MTA_SET_JAM_DETECT_REQ_STRU
 结构说明  : AT发给MTA的设置Jamming Dectection Report的消息结构

  1.日    期   : 2014年5月04日
    作    者   : g00261581
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucFlag;
    VOS_UINT8                           ucMethod;
    VOS_UINT8                           ucThreshold;
    VOS_UINT8                           ucFreqNum;
} AT_MTA_SET_JAM_DETECT_REQ_STRU;

/*****************************************************************************
 结构名    : MTA_AT_SET_JAM_DETECT_CNF_STRU
 结构说明  : MTA发给AT的设置Jamming Dectection Report的Cnf消息结构

  1.日    期   : 2014年5月04日
    作    者   : g00261581
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_JAM_DETECT_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_AT_JAM_DETECT_IND_STRU
 结构说明  : MTA发给AT的Jamming Dectection Report的Ind上报消息结构

  1.日    期   : 2014年5月04日
    作    者   : g00261581
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    MTA_AT_JAM_RESULT_ENUM_UINT32       enJamResult;
} MTA_AT_JAM_DETECT_IND_STRU;

/*****************************************************************************
 结构名    : AT_MTA_SET_FREQ_LOCK_REQ_STRU
 结构说明  : AT发给MTA的设置锁频请求的消息结构

  1.日    期   : 2014年6月11日
    作    者   : g00261581
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /* 1:锁频功能打开，0:功能关闭 */
    AT_MTA_FREQLOCK_RATMODE_ENUM_UINT8  enRatMode;
    VOS_UINT16                          usLockedFreq;
    AT_MTA_GSM_BAND_ENUM_UINT16         enBand;
    VOS_UINT8                           aucReserved[2];
} AT_MTA_SET_FREQ_LOCK_REQ_STRU;

/*****************************************************************************
 结构名    : MTA_AT_SET_FREQ_LOCK_CNF_STRU
 结构说明  : MTA回复给AT设置锁频回复结果的消息结构

  1.日    期   : 2014年6月11日
    作    者   : g00261581
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_FREQ_LOCK_CNF_STRU;

/*****************************************************************************
 结构名    : AT_MTA_SET_GSM_FREQLOCK_REQ_STRU
 结构说明  : AT发给MTA的设置G模锁频请求的消息结构

  1.日    期   : 2014年08月05日
    作    者   : j00174725
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enableFlag;                             /* PS_TRUE:锁定，PS_FALSE:去锁定 */
    VOS_UINT8                           aucReserved[3];                         /* 保留位 */
    VOS_UINT16                          usFreq;                                 /* 频点值 */
    AT_MTA_GSM_BAND_ENUM_UINT16         enBand;                                 /* GSM频段 */
} AT_MTA_SET_GSM_FREQLOCK_REQ_STRU;

/*****************************************************************************
 结构名    : MTA_AT_SET_GSM_FREQLOCK_CNF_STRU
 结构说明  : MTA回复给AT设置G模锁频回复结果的消息结构

  1.日    期   : 2014年08月05日
    作    者   : j00174725
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_GSM_FREQLOCK_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_AT_XPASS_INFO_IND_STRU
 结构说明  : MTA主动上报的XPASS信息的消息结构

  1.日    期   : 2014年12月25日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    MTA_AT_GPHY_XPASS_MODE_ENUM_UINT16            enGphyXpassMode;
    VOS_UINT16                                    usResev1;
    MTA_AT_WPHY_HIGHWAY_MODE_ENUM_UINT16          enWphyXpassMode;
    VOS_UINT16                                    usResev2;
} MTA_AT_XPASS_INFO_IND_STRU;
/*****************************************************************************
 结构名    : AT_MTA_SET_FEMCTRL_REQ_STRU
 结构说明  : AT发给MTA的设置底软gpio、mipi口的消息结构

  1.日    期   : 2014年12月11日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32      ulCtrlType;
    VOS_UINT32      ulPara1;
    VOS_UINT32      ulPara2;
    VOS_UINT32      ulPara3;
} AT_MTA_SET_FEMCTRL_REQ_STRU;

/*****************************************************************************
 结构名    : MTA_AT_SET_FEMCTRL_CNF_STRU
 结构说明  : MTA回复给AT设置底软gpio、mipi口的消息结构

  1.日    期   : 2014年12月11日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_FEMCTRL_CNF_STRU;

/*****************************************************************************
 结构名    : AT_MTA_NVWRSECCTRL_SET_REQ_STRU
 结构说明  : AT发给MTA的设置NVWR命令安全控制的消息结构

  1.日    期   : 2015年04月04日
    作    者   : l00198894
    修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSecType;                              /* 安全控制类型 */
    VOS_UINT8                           ucSecStrFlg;                            /* 是否携带安全校验密文 */
    VOS_UINT8                           aucReserved[2];
    VOS_UINT8                           aucSecString[AT_RSA_CIPHERTEXT_LEN];    /* 安全校验密文 */
} AT_MTA_NVWRSECCTRL_SET_REQ_STRU;

/*******************************************************************************
 结构名    : AT_MTA_SET_FR_REQ_STRU
 结构说明  : AT发给MTA设置FR请求
 1.日    期   : 2015年06月01日
   作    者   : wx270776
   修改内容   : FR动态控制添加
*******************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                          enActFrFlag;                    /* 激活FR标志，0:不激活  1:激活 */
    VOS_UINT8                                   aucRsv[3];                      /* 保留位 */
}AT_MTA_SET_FR_REQ_STRU;

/*******************************************************************************
 结构名    : MTA_AT_SET_FR_CNF_STRU
 结构说明  : MTA回复AT的FR设置响应
 1.日    期   : 2015年06月01日
   作    者   : wx270776
   修改内容   : FR动态控制添加
*******************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32                   enRslt;                         /* FR设置及结果 */
}MTA_AT_SET_FR_CNF_STRU;

/*****************************************************************************
 结构名    : AT_MTA_MBMS_SERVICE_OPTION_SET_REQ_STRU
 结构说明  : AT发给MTA的设置MBMS服务特性操作请求结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    AT_MTA_CFG_ENUM_UINT8               enCfg;                                  /* 0:去使能，1:使能 */
    VOS_UINT8                           aucReserved[3];                         /* 保留位 */
} AT_MTA_MBMS_SERVICE_OPTION_SET_REQ_STRU;


/*****************************************************************************
 结构名    : AT_MTA_PLMN_ID_STRU
 结构说明  : PLMN ID结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;                                  /* MCC, 3 bytes */
    VOS_UINT32                          ulMnc;                                  /* MNC, 2 or 3 bytes */
} AT_MTA_PLMN_ID_STRU;

/*****************************************************************************
 结构名    : AT_MTA_MBMS_TMGI_STRU
 结构说明  : TMGI结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMbmsSerId;                            /* Service ID */
    AT_MTA_PLMN_ID_STRU                 stPlmnId;                               /* PLMN ID */
} AT_MTA_MBMS_TMGI_STRU;

/*****************************************************************************
 结构名    : AT_MTA_MBMS_SERVICE_STATE_SET_REQ_STRU
 结构说明  : AT通知MTA MBMS服务状态设置请求结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    AT_MTA_MBMS_SERVICE_STATE_SET_ENUM_UINT8    enStateSet;                     /* 状态设置 */
    VOS_UINT8                                   aucReserved[3];                 /* 保留位 */
    VOS_UINT32                                  ulAreaId;                       /* Area ID */
    AT_MTA_MBMS_TMGI_STRU                       stTMGI;                         /* TMGI */
} AT_MTA_MBMS_SERVICE_STATE_SET_REQ_STRU;

/*****************************************************************************
 结构名    : AT_MTA_MBMS_PREFERENCE_SET_REQ_STRU
 结构说明  : AT发给MTA的设置MBMS广播模式为单播或组播操作请求结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    AT_MTA_MBMS_CAST_MODE_ENUM_UINT8    enCastMode;                             /* 0:单播,1:组播 */
    VOS_UINT8                           aucReserved[3];                         /* 保留位 */
} AT_MTA_MBMS_PREFERENCE_SET_REQ_STRU;

/*****************************************************************************
 结构名    : MTA_AT_MBMS_SIB16_NETWORK_TIME_QRY_CNF_STRU
 结构说明  : MTA回复给AT查询SIB16网络时间结果

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT32                          aulUTC[2];                              /* (0..549755813887) */
} MTA_AT_MBMS_SIB16_NETWORK_TIME_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_AT_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU
 结构说明  : MTA回复给AT查询BSSI信号强度结果

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT8                           ucBSSILevel;                            /* BSSI信号强度,0xFF:表示BSSI信号强度无效 */
    VOS_UINT8                           aucReserved[3];                         /* 保留位 */
} MTA_AT_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_AT_MBMS_NETWORK_INFO_QRY_CNF_STRU
 结构说明  : MTA回复给AT查询网络信息结果

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT32                          ulCellId;                               /* 小区ID */
} MTA_AT_MBMS_NETWORK_INFO_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_AT_EMBMS_STATUS_QRY_CNF_STRU
 结构说明  : MTA回复给AT查询EMBMS功能状态结果

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32                   enResult;
    MTA_AT_EMBMS_FUNTIONALITY_STATUS_ENUM_UINT8 enStatus;                       /* 功能状态 */
    VOS_UINT8                                   aucReserved[3];                 /* 保留位 */
} MTA_AT_EMBMS_STATUS_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : AT_MTA_MBMS_UNSOLICITED_CFG_SET_REQ_STRU
 结构说明  : AT发给MTA的设置MBMS主动上报配置操作请求结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    AT_MTA_CFG_ENUM_UINT8                       enCfg;                          /* 0:关闭,1:打开 */
    VOS_UINT8                                   aucReserved[3];                 /* 保留位 */
} AT_MTA_MBMS_UNSOLICITED_CFG_SET_REQ_STRU;

/*****************************************************************************
 结构名    : MTA_AT_MBMS_SERVICE_EVENT_IND_STRU
 结构说明  : MTA发给AT的MBMS服务事件主动上报信息

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MTA_AT_MBMS_SERVICE_EVENT_ENUM_UINT8    enEvent;                            /* 服务事件 */
    VOS_UINT8                               aucReserved[3];                     /* 保留位 */
} MTA_AT_MBMS_SERVICE_EVENT_IND_STRU;

/*****************************************************************************
 结构名    : AT_MTA_LOW_POWER_CONSUMPTION_SET_REQ_STRU
 结构说明  : AT发给MTA的设置低功耗操作请求结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    AT_MTA_LTE_LOW_POWER_ENUM_UINT8         enLteLowPowerFlg;                   /* 0: Normal;1: Low Power Consumption */
    VOS_UINT8                               aucReserved[3];                     /* 保留位 */
} AT_MTA_LOW_POWER_CONSUMPTION_SET_REQ_STRU;

/*****************************************************************************
 结构名    : AT_MTA_MBMS_INTERESTLIST_SET_REQ_STRU
 结构说明  : AT发给MTA的设置Interest列表操作请求结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          aulFreqList[AT_MTA_INTEREST_FREQ_MAX_NUM];  /* 频点列表 */
    AT_MTA_MBMS_PRIORITY_ENUM_UINT8     enMbmsPriority;                             /* VOS_FALSE: 单播优先;VOS_TRUE: MBMS优先 */
    VOS_UINT8                           aucReserved[3];                             /* 保留位 */
} AT_MTA_MBMS_INTERESTLIST_SET_REQ_STRU;

/*****************************************************************************
 结构名    : MTA_AT_MBMS_AVL_SERVICE_STRU
 结构说明  : MBMS可用服务结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpSessionId  : 1;
    VOS_UINT32                          bitSpare        : 31;
    VOS_UINT32                          ulAreaId;                               /* Area ID */
    AT_MTA_MBMS_TMGI_STRU               stTMGI;                                 /* TMGI */
    VOS_UINT32                          ulSessionId;                            /* Session ID */
} MTA_AT_MBMS_AVL_SERVICE_STRU;

/*****************************************************************************
 结构名    : MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU
 结构说明  : MTA回复给AT查询可用服务列表操作结果

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT32                          ulAvlServiceNum;                                    /* 可用服务数,0:表示没有可用服务 */
    MTA_AT_MBMS_AVL_SERVICE_STRU        astAvlServices[AT_MTA_MBMS_AVL_SERVICE_MAX_NUM];    /* 可用服务列表 */
} MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_LRRC_COEX_PARA_STRU
 结构说明  : LTE&WIFI共存参数结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    AT_MTA_COEX_BW_TYPE_ENUM_UINT16             enCoexBWType;
    AT_MTA_COEX_CFG_ENUM_UINT16                 enCfg;
    VOS_UINT16                                  usTxBegin;
    VOS_UINT16                                  usTxEnd;
    VOS_INT16                                   sTxPower;
    VOS_UINT16                                  usRxBegin;
    VOS_UINT16                                  usRxEnd;
    VOS_UINT8                                   aucReserved[2];                 /* 保留位 */
} AT_MTA_COEX_PARA_STRU;

/*****************************************************************************
 结构名    : AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU
 结构说明  : AT发给MTA的设置LTE&WIFI共存配置请求结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCoexParaNum;
    VOS_UINT16                          usCoexParaSize;
    AT_MTA_COEX_PARA_STRU               astCoexPara[AT_MTA_ISMCOEX_BANDWIDTH_NUM];
} AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU;

/*****************************************************************************
 结构名    : MTA_AT_LTE_WIFI_COEX_QRY_CNF_STRU
 结构说明  : MTA发给AT的查询LTE&WIFI共存配置请求结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    AT_MTA_COEX_PARA_STRU               astCoexPara[AT_MTA_ISMCOEX_BANDWIDTH_NUM];
} MTA_AT_LTE_WIFI_COEX_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : AT_MTA_MEID_SET_REQ_STRU
 结构说明  : AT^MEID设置请求结构

 修改历史      :
  1.日    期   : 2015年07月23日
    作    者   : z00316370
    修改内容   : 新增加
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucMeid[AT_MTA_MEID_DATA_LEN];
    VOS_UINT8                           aucRsv[1];
}AT_MTA_MEID_SET_REQ_STRU;

/*****************************************************************************
 结构名    : MTA_AT_MEID_QRY_CNF_STRU
 结构说明  : AT^MEID查询请求结构

 修改历史      :
  1.日    期   : 2015年12月18日
    作    者   : z00316370
    修改内容   : 新增加
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* 查询操作结果*/
    VOS_UINT8                           aucEFRUIMID[MTA_AT_EFRUIMID_OCTET_LEN_EIGHT];
}MTA_AT_MEID_QRY_CNF_STRU;




/*****************************************************************************
 结构名    : MTA_AT_TRANSMODE_QRY_CNF_STRU
 结构说明  : MTA发给AT查询传输模式结果的消息结构

  1.日    期   : 2015年07月30日
    作    者   : lwx277467
    修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* 查询操作结果*/
    VOS_UINT8                           ucTransMode;                            /* 传输模式*/
    VOS_UINT8                           aucReserved[3];                         /*保留位*/
} MTA_AT_TRANSMODE_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : AT_MTA_SET_UE_CENTER_REQ_STRU
 结构说明  : AT发给MTA设置UE Mode的消息结构

  1.日    期   : 2015年09月07日
    作    者   : lwx277467
    修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_MTA_UE_CENTER_TYPE_ENUM_UINT32   enUeCenter;                             /*UE模式*/
} AT_MTA_SET_UE_CENTER_REQ_STRU;

/*****************************************************************************
 结构名    : MTA_AT_SET_UE_CENTER_CNF_STRU
 结构说明  : MTA发给AT设置UE Mode结果的消息结构

  1.日    期   : 2015年09月07日
    作    者   : lwx277467
    修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* 查询操作结果*/
} MTA_AT_SET_UE_CENTER_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_AT_QRY_UE_CENTER_CNF_STRU
 结构说明  : MTA发给AT查询UE模式结果的消息结构

  1.日    期   : 2015年09月07日
    作    者   : lwx277467
    修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* 查询操作结果*/
    AT_MTA_UE_CENTER_TYPE_ENUM_UINT32   enUeCenter;                             /*UE模式*/
} MTA_AT_QRY_UE_CENTER_CNF_STRU;


/*****************************************************************************
 结构名    : MTA_AT_NETMON_GSM_SCELL_INFO_STRU
 结构说明  : MTA回复给AT network monitor小区查询结果

  1.日    期   : 2015年10月19日
    作    者   : zwx247453
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpTa     :1;
    VOS_UINT32                          bitOpSpare  :31;
    GRR_MTA_NETMON_SCELL_INFO_STRU      stSCellInfo;
    VOS_UINT16                          usTa;
    VOS_UINT8                           aucReserved[2];
}MTA_AT_NETMON_GSM_SCELL_INFO_STRU;

/*****************************************************************************
 结构名    : MTA_AT_NETMON_SCELLL_INFO_UN
 结构说明  : MTA 服务小区联合体结构

  1.日    期   : 2015年10月19日
    作    者   : zwx247453
    修改内容   : 新增
*****************************************************************************/
typedef union
{
    MTA_AT_NETMON_GSM_SCELL_INFO_STRU       stGsmSCellInfo;    /* GSM服务小区信息 */
    RRC_MTA_NETMON_UTRAN_SCELL_INFO_STRU    stUtranSCellInfo;  /* WCDMA服务小区信息 */
    MTA_NETMON_EUTRAN_SCELL_INFO_STRU       stLteSCellInfo;    /* LTE服务小区信息*/
}MTA_AT_NETMON_SCELL_INFO_UN;

/*****************************************************************************
 结构名    : MTA_AT_NETMON_GSM_SCELL_INFO_STRU
 结构说明  : MTA回复给AT network monitor小区查询结果

  1.日    期   : 2015年10月19日
    作    者   : zwx247453
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32                   enResult;               /* 查询结果是否成功 */
    MTA_NETMON_CELL_TYPE_ENUM_UINT32            enCellType;             /* 0:查询服务小区，1:查询临区 */
    RRC_MTA_NETMON_NCELL_INFO_STRU              stNCellInfo;            /*临区信息*/
    MTA_AT_NETMON_CELL_INFO_RAT_ENUM_UINT32     enRatType;              /* 服务小区的接入技术类型 */
    MTA_AT_NETMON_SCELL_INFO_UN                 unSCellInfo;
} MTA_AT_NETMON_CELL_INFO_STRU;



/*****************************************************************************
 结构名    : AT_MTA_QRY_AFC_CLK_FREQ_XOCOEF_REQ_STRU
 结构说明  :

  1.日    期   : 2015年12月25日
    作    者   : C00299064
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulReserveValue;
} AT_MTA_QRY_AFC_CLK_FREQ_XOCOEF_REQ_STRU;

/*****************************************************************************
 结构名    : MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU
 结构说明  :

  1.日    期   : 2015年12月25日
    作    者   : C00299064
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;

    AT_MTA_AFC_CLK_STATUS_ENUM_UINT32   enStatus;
    VOS_INT32                           lDeviation;                                 /* 频偏 */

    /* 温度范围 */
    VOS_INT16                           sCoeffStartTemp;
    VOS_INT16                           sCoeffEndTemp;

    /* 多项式系数 */
    VOS_UINT32                          aulCoeffMantissa[AT_MTA_GPS_XO_COEF_NUM];  /* a0,a1,a2,a3尾数 */
    VOS_UINT16                          ausCoeffExponent[AT_MTA_GPS_XO_COEF_NUM];  /* a0,a1,a2,a3指数 */

} MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU;



/*****************************************************************************
  8 UNION定义
*****************************************************************************/
/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    AT_MTA_MSG_TYPE_ENUM_UINT32         ulMsgId;                                /*_H2ASN_MsgChoice_Export AT_MTA_MSG_TYPE_ENUM_UINT32*/
    AT_APPCTRL_STRU                     stAppCtrl;
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          AT_MTA_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}AT_MTA_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_DATA                     stMsgData;
}AtMtaInterface_MSG;

/*****************************************************************************
  10 函数声明
*****************************************************************************/


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

