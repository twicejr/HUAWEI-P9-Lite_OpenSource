/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MtaRrcInterface.h
  版 本 号   : 初稿
  作    者   : h44270
  生成日期   : 2012年06月01日
  最近修改   :
  功能描述   : MTA与GU接入层之间的接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年06月01日
    作    者   : h44270
    修改内容   : 创建文件

 ******************************************************************************/

#ifndef __MTARRCINTERFACE_H__
#define __MTARRCINTERFACE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "PsTypeDef.h"
#include "AgpsParaDef.h"
#include "MtaCommInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define  NMR_MAX_FREQ_NUM                       (3)  /* 上报NMR数据的频点最大个数,W最多只支持三个频点，TD开发时扩充 */
#define  NMR_MAX_CELL_FREQ_NUM                  (32) /* 上报NMR数据的小区测量的最大个数 */
#define  RRC_MTA_UTRAN_NMR                      (0)
#define  RRC_MTA_GSM_NMR                        (1)
#define  RRC_MTA_NMR_MAX_GSM_ELEM_NUM           (15) /* 上报NMR数据的GSM元素的最大个数 */

#define  MTA_WRR_AUTOTEST_MAX_PARA_NUM          (10) /* autotest命令下发参数最大个数 */
#define  WRR_MTA_AUTOTEST_MAX_RSULT_NUM         (20) /* autotest命令上报结果最大个数 */
#define  WRR_MTA_MEANRPT_MAX_CELL_NUM           (8)  /* 一次测量报告中小区最大个数 */
#define  WRR_MTA_MAX_MEANRPT_NUM                (10) /* 上报最近测量报告的最大个数 */

#define  WRR_MTA_MAX_NCELL_NUM                  (8)  /* WAS最大临区个数 */

/* Added by l00198894 for 新增+ECID命令, 2013-12-09, begin */
#define  MTA_LRRC_MSG_TYPE_BASE                 (0x1000)            /* MTA模块与LTE接入层消息基数 */
#define  LRRC_MAX_NCELL_NUM                     (8)
/* Added by l00198894 for 新增+ECID命令, 2013-12-09, end */


#define  MBMS_AVL_SERVICE_MAX_NUM               (0x10)              /* LRRC回复MTA MBMS可服务列表的最大个数 */

#define  MTA_LRRC_INTEREST_FREQ_MAX_NUM         (0x05)              /* MTA通知LRRC Interest列表频点的最大个数 */

/* Added by y00142674 for 云端频点收集, 2015-07-07, begin */
#define MTA_RRC_MAX_PLMN_NUM                    (32)    /* PLMN的最大个数 */

#define RRC_MTA_MAX_GSM_PLMN_NUM                (15)    /* GSM PLMN的最大个数 */
#define RRC_MTA_MAX_GSM_FREQ_NUM                (60)    /* GSM 频点的最大个数 */

#define RRC_MTA_MAX_WCDMA_PLMN_NUM              (32)    /* WCDMA PLMN的最大个数 */
#define RRC_MTA_MAX_WCDMA_FREQ_NUM              (16)    /* WCDMA 频点的最大个数 */

#define RRC_MTA_MAX_LTE_PLMN_NUM                (20)    /* LTE PLMN的最大个数 */
#define RRC_MTA_MAX_LTE_FREQ_NUM                (16)    /* LTE 频点的最大个数 */
/* Added by y00142674 for 云端频点收集, 2015-07-07, end */


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : MTA_RRC_MSG_TYPE_ENUM
 结构说明  : 原语的usMsgName
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
 2.日    期   : 2012年11月23日
   作    者   : s46746
   修改内容   : 定义NMR功能MTA与GU接入层之间的消息
 3.日    期   : 2012年12月26日
   作    者   : m00217266
   修改内容   : 添加与WAS相关AT命令的消息ID
 4.日    期   : 2013年5月31日
   作    者   : s00217060
   修改内容   : V9R1_SVLTE:添加与GAS相关AT命令的消息ID
*****************************************************************************/
enum MTA_RRC_MSG_TYPE_ENUM
{
    /* 消息名称 */                              /* 消息ID */                    /* 备注 */
    ID_RRC_MTA_MSG_POSITION_REQ                    = 0x0001,                    /* _H2ASN_MsgChoice MTA_RRC_POSITION_REQ_STRU */

    ID_MTA_RRC_QRY_NMR_REQ                         = 0x0003,                    /* _H2ASN_MsgChoice MTA_RRC_QRY_NMR_REQ_STRU */

    ID_MTA_RRC_RESEL_OFFSET_CFG_NTF                = 0x0005,                    /* _H2ASN_MsgChoice MTA_RRC_RESEL_OFFSET_CFG_NTF_STRU */

    ID_MTA_WRR_AUTOTEST_QRY_REQ                    = 0x0007,                    /* _H2ASN_MsgChoice MTA_WRR_AUTOTEST_QRY_REQ_STRU     */

    ID_MTA_WRR_CELLINFO_QRY_REQ                    = 0x0009,                    /* _H2ASN_MsgChoice MTA_WRR_CELLINFO_QRY_REQ_STRU     */

    ID_MTA_WRR_MEASRPT_QRY_REQ                     = 0x000B,                    /* _H2ASN_MsgChoice MTA_WRR_MEANRPT_QRY_REQ_STRU      */

    ID_MTA_WRR_FREQLOCK_SET_REQ                    = 0x000D,                    /* _H2ASN_MsgChoice MTA_WRR_FREQLOCK_SET_REQ_STRU     */

    ID_MTA_WRR_RRC_VERSION_SET_REQ                 = 0x000F,                    /* _H2ASN_MsgChoice MTA_WRR_RRC_VERSION_SET_REQ_STRU  */

    ID_MTA_WRR_CELLSRH_SET_REQ                     = 0x0011,                    /* _H2ASN_MsgChoice MTA_WRR_CELLSRH_SET_REQ_STRU      */

    ID_MTA_WRR_FREQLOCK_QRY_REQ                    = 0x0013,                    /* _H2ASN_MsgChoice MTA_WRR_FREQLOCK_QRY_REQ_STRU     */

    ID_MTA_WRR_RRC_VERSION_QRY_REQ                 = 0x0015,                    /* _H2ASN_MsgChoice MTA_WRR_RRC_VERSION_QRY_REQ_STRU  */

    ID_MTA_WRR_CELLSRH_QRY_REQ                     = 0x0017,                    /* _H2ASN_MsgChoice MTA_WRR_CELLSRH_QRY_REQ_STRU      */

    ID_MTA_GRR_NCELL_MONITOR_SET_REQ               = 0x0019,                    /* _H2ASN_MsgChoice MTA_GRR_NCELL_MONITOR_SET_REQ_STRU      */

    ID_MTA_GRR_NCELL_MONITOR_QRY_REQ               = 0x001B,                    /* _H2ASN_MsgChoice MTA_GRR_NCELL_MONITOR_QRY_REQ_STRU      */

    ID_MTA_RRC_JAM_DETECT_REQ                      = 0x001D,                    /* _H2ASN_MsgChoice MTA_RRC_JAM_DETECT_REQ_STRU */

    ID_MTA_RRC_CHECK_FREQ_VALIDITY_REQ             = 0x001F,                    /* _H2ASN_MsgChoice MTA_RRC_CHECK_FREQ_VALIDITY_REQ_STRU */

    ID_MTA_GRR_FREQLOCK_SET_REQ                    = 0x0021,                    /* _H2ASN_MsgChoice MTA_GRR_FREQLOCK_SET_REQ_STRU     */

    ID_MTA_RRC_NETMON_CELL_QRY_REQ                 = 0x0023,                    /* _H2ASN_MsgChoice MTA_RRC_NETMON_CELL_QRY_REQ_STRU    */
    ID_MTA_GRR_NETMON_CELL_QRY_REQ                 = 0x0025,                    /* _H2ASN_MsgChoice MTA_RRC_NETMON_CELL_QRY_REQ_STRU    */
    ID_MTA_GRR_NETMON_TA_QRY_REQ                   = 0x0027,                    /* _H2ASN_MsgChoice MTA_GRR_NETMON_TA_QRY_REQ_STRU      */
    ID_MTA_WRR_JAM_DETECT_REQ                      = 0x0029,                    /* _H2ASN_MsgChoice MTA_WRR_JAM_DETECT_REQ_STRU */

    /* Added by y00142674 for 云端频点收集, 2015-07-07, begin */
    ID_MTA_RRC_PLMN_FREQ_QRY_REQ                   = 0x002B,                    /* _H2ASN_MsgChoice MTA_RRC_PLMN_FREQ_QRY_REQ_STRU     */
    /* Added by y00142674 for 云端频点收集, 2015-07-07, end */

    ID_MTA_RRC_MSG_POSITION_CNF                    = 0x0002,                    /* _H2ASN_MsgChoice MTA_RRC_POSITION_CNF_STRU */

    ID_RRC_MTA_QRY_NMR_CNF                         = 0x0004,                    /* _H2ASN_MsgChoice RRC_MTA_QRY_NMR_CNF_STRU */

    ID_WRR_MTA_AUTOTEST_QRY_CNF                    = 0x0008,                    /* _H2ASN_MsgChoice WRR_MTA_AUTOTEST_QRY_CNF_STRU     */

    ID_WRR_MTA_CELLINFO_QRY_CNF                    = 0x000A,                    /* _H2ASN_MsgChoice WRR_MTA_CELLINFO_QRY_CNF_STRU     */

    ID_WRR_MTA_MEASRPT_QRY_CNF                     = 0x000C,                    /* _H2ASN_MsgChoice WRR_MTA_MEANRPT_QRY_CNF_STRU      */

    ID_WRR_MTA_FREQLOCK_SET_CNF                    = 0x000E,                    /* _H2ASN_MsgChoice WRR_MTA_FREQLOCK_SET_CNF_STRU     */

    ID_WRR_MTA_RRC_VERSION_SET_CNF                 = 0x0010,                    /* _H2ASN_MsgChoice WRR_MTA_RRC_VERSION_SET_CNF_STRU  */

    ID_WRR_MTA_CELLSRH_SET_CNF                     = 0x0012,                    /* _H2ASN_MsgChoice WRR_MTA_CELLSRH_SET_CNF_STRU      */

    ID_WRR_MTA_FREQLOCK_QRY_CNF                    = 0x0014,                    /* _H2ASN_MsgChoice WRR_MTA_FREQLOCK_QRY_CNF_STRU     */

    ID_WRR_MTA_RRC_VERSION_QRY_CNF                 = 0x0016,                    /* _H2ASN_MsgChoice WRR_MTA_RRC_VERSION_QRY_CNF_STRU  */

    ID_WRR_MTA_CELLSRH_QRY_CNF                     = 0x0018,                    /* _H2ASN_MsgChoice WRR_MTA_CELLSRH_QRY_CNF_STRU      */


    ID_GRR_MTA_NCELL_MONITOR_SET_CNF              = 0x001A,                    /* _H2ASN_MsgChoice GRR_MTA_NCELL_MONITOR_SET_CNF_STRU      */

    ID_GRR_MTA_NCELL_MONITOR_QRY_CNF              = 0x001C,                    /* _H2ASN_MsgChoice GRR_MTA_NCELL_MONITOR_QRY_CNF_STRU      */

    ID_GRR_MTA_NCELL_MONITOR_IND                  = 0x001E,                    /* _H2ASN_MsgChoice GRR_MTA_NCELL_MONITOR_IND_STRU      */

    ID_RRC_MTA_JAM_DETECT_CNF                      = 0x0020,                    /* _H2ASN_MsgChoice RRC_MTA_JAM_DETECT_CNF_STRU */
    ID_RRC_MTA_JAM_DETECT_IND                      = 0x0022,                    /* _H2ASN_MsgChoice RRC_MTA_JAM_DETECT_IND_STRU */

    ID_RRC_MTA_CHECK_FREQ_VALIDITY_CNF             = 0x0024,                    /* _H2ASN_MsgChoice RRC_MTA_CHECK_FREQ_VALIDITY_CNF_STRU */

    ID_GRR_MTA_FREQLOCK_SET_CNF                    = 0x0026,                    /* _H2ASN_MsgChoice GRR_MTA_FREQLOCK_SET_CNF_STRU     */

    ID_GRR_MTA_NETMON_CELL_QRY_CNF                 = 0x0028,                    /* _H2ASN_MsgChoice GRR_MTA_NETMON_CELL_QRY_CNF_STRU   */
    ID_GRR_MTA_NETMON_TA_QRY_CNF                   = 0x002A,                    /* _H2ASN_MsgChoice GRR_MTA_NETMON_TA_QRY_CNF_STRU   */
    ID_RRC_MTA_NETMON_CELL_QRY_CNF                 = 0x002C,                    /* _H2ASN_MsgChoice RRC_MTA_NETMON_CELL_INFO_QRY_CNF_STRU   */

    /* Added by y00142674 for 云端频点收集, 2015-07-07, begin */
    ID_RRC_MTA_PLMN_FREQ_QRY_CNF                   = 0x002E,                    /* _H2ASN_MsgChoice RRC_MTA_PLMN_FREQ_QRY_CNF_STRU     */
    /* Added by y00142674 for 云端频点收集, 2015-07-07, end */

    /* Added by l00198894 for 新增+ECID命令, 2013-12-09, begin */
    /* 消息方向MTA->LRRC/GAS/WRR/TDRRC */
    ID_MTA_LRRC_CELLINFO_QRY_REQ                = MTA_LRRC_MSG_TYPE_BASE + 1,   /* _H2ASN_MsgChoice MTA_LRRC_CELLINFO_QRY_REQ_STRU      */

    ID_MTA_TLRRC_SET_DPDTTEST_FLAG_NTF          = MTA_LRRC_MSG_TYPE_BASE + 3,   /* _H2ASN_MsgChoice MTA_TLRRC_SET_DPDTTEST_FLAG_NTF_STRU      */

    ID_MTA_TLRRC_SET_DPDT_VALUE_NTF             = MTA_LRRC_MSG_TYPE_BASE + 5,   /* _H2ASN_MsgChoice MTA_TLRRC_SET_DPDT_VALUE_NTF_STRU      */

    ID_MTA_TLRRC_QRY_DPDT_VALUE_REQ             = MTA_LRRC_MSG_TYPE_BASE + 7,   /* _H2ASN_MsgChoice MTA_TLRRC_QRY_DPDT_VALUE_REQ_STRU      */

    ID_MTA_LRRC_NETMON_CELL_QRY_REQ             = MTA_LRRC_MSG_TYPE_BASE +11,   /* _H2ASN_MsgChoice MTA_LRRC_NETMON_CELL_QRY_REQ_STRU      */

    ID_MTA_RRC_PROTECT_PS_IND                   = MTA_LRRC_MSG_TYPE_BASE + 9,   /* _H2ASN_MsgChoice MTA_RRC_PROTECT_PS_IND_STRU      */

    /*T模FREQLOCK锁频REQ消息*/
    ID_MTA_TDS_FREQLOCK_SET_REQ                 = MTA_LRRC_MSG_TYPE_BASE + 13,  /* _H2ASN_MsgChoice MTA_TDS_FREQLOCK_SET_REQ_STRU      */

    /*L模FREQLOCK锁频REQ消息*/
    ID_MTA_LRRC_FREQLOCK_SET_REQ                = MTA_LRRC_MSG_TYPE_BASE + 15,  /* _H2ASN_MsgChoice MTA_TDS_FREQLOCK_SET_REQ_STRU      */

    ID_MTA_LRRC_MBMS_SERVICE_OPTION_REQ         = MTA_LRRC_MSG_TYPE_BASE + 17,  /* _H2ASN_MsgChoice MTA_LRRC_MBMS_SERVICE_OPTION_REQ_STRU      */

    ID_MTA_LRRC_MBMS_SERVICE_STATE_SET_REQ      = MTA_LRRC_MSG_TYPE_BASE + 19,  /* _H2ASN_MsgChoice MTA_LRRC_MBMS_SERVICE_STATE_SET_REQ_STRU      */

    ID_MTA_LRRC_MBMS_AVL_SERVICE_LIST_QRY_REQ   = MTA_LRRC_MSG_TYPE_BASE + 21,  /* _H2ASN_MsgChoice MTA_LRRC_MBMS_AVL_SERVICE_LIST_QRY_REQ_STRU      */

    ID_MTA_LRRC_MBMS_PREFERENCE_SET_REQ         = MTA_LRRC_MSG_TYPE_BASE + 23,  /* _H2ASN_MsgChoice MTA_LRRC_MBMS_PREFERENCE_SET_REQ_STRU      */

    ID_MTA_LRRC_SIB16_NETWORK_TIME_QRY_REQ      = MTA_LRRC_MSG_TYPE_BASE + 25,  /* _H2ASN_MsgChoice MTA_LRRC_SIB16_NETWORK_TIME_QRY_REQ_STRU      */

    ID_MTA_LRRC_BSSI_SIGNAL_LEVEL_QRY_REQ       = MTA_LRRC_MSG_TYPE_BASE + 27,  /* _H2ASN_MsgChoice MTA_LRRC_BSSI_SIGNAL_LEVEL_QRY_REQ_STRU      */

    ID_MTA_LRRC_NETWORK_INFO_QRY_REQ            = MTA_LRRC_MSG_TYPE_BASE + 29,  /* _H2ASN_MsgChoice MTA_LRRC_NETWORK_INFO_QRY_REQ_STRU      */

    ID_MTA_LRRC_EMBMS_STATUS_QRY_REQ            = MTA_LRRC_MSG_TYPE_BASE + 31,  /* _H2ASN_MsgChoice MTA_LRRC_EMBMS_STATUS_QRY_REQ_STRU      */

    ID_MTA_LRRC_MBMS_UNSOLICITED_CFG_SET_REQ    = MTA_LRRC_MSG_TYPE_BASE + 33,  /* _H2ASN_MsgChoice MTA_LRRC_MBMS_UNSOLICITED_CFG_SET_REQ_STRU      */

    ID_MTA_LRRC_LTE_WIFI_COEX_SET_REQ           = MTA_LRRC_MSG_TYPE_BASE + 36,  /* _H2ASN_MsgChoice MTA_LRRC_LTE_WIFI_COEX_SET_REQ_STRU      */

    ID_MTA_LRRC_LOW_POWER_CONSUMPTION_SET_REQ   = MTA_LRRC_MSG_TYPE_BASE + 38,  /* _H2ASN_MsgChoice MTA_LRRC_LOW_POWER_CONSUMPTION_SET_REQ_STRU      */

    ID_MTA_LRRC_INTEREST_LIST_SET_REQ           = MTA_LRRC_MSG_TYPE_BASE + 40,  /* _H2ASN_MsgChoice MTA_LRRC_INTEREST_LIST_SET_REQ_STRU      */

    ID_MTA_LRRC_TRANSMODE_QRY_REQ               = MTA_LRRC_MSG_TYPE_BASE + 49,   /* _H2ASN_MsgChoice MTA_LRRC_TRANSMODE_QRY_REQ_STRU      */

    /************无线发射功率tx power (4G)**********************************/
    ID_MTA_LRRC_QRY_TXPOWER_REQ                = MTA_LRRC_MSG_TYPE_BASE + 51,  /* _H2ASN_MsgChoice MTA_LRRC_TX_PWR_QRY_REQ      */
    /***********************************************************************/
    /************MCS *******************************************************/
    ID_MTA_LRRC_QRY_MCS_REQ                    = MTA_LRRC_MSG_TYPE_BASE + 53,  /* _H2ASN_MsgChoice MTA_LRRC_MCS_QRY_REQ      */
    /***********************************************************************/
    /************EARFCN*****************************************************/
    ID_MTA_LRRC_QRY_EARFCN_REQ                 = MTA_LRRC_MSG_TYPE_BASE + 55,  /* _H2ASN_MsgChoice MTA_LRRC_EARFCN_QRY_REQ      */
    /***********************************************************************/
    /************TDD时隙配比************************************************/
    ID_MTA_LRRC_QRY_LFRAMERATIO_REQ            = MTA_LRRC_MSG_TYPE_BASE + 57,  /* _H2ASN_MsgChoice MTA_LRRC_LFRAMERATIO_QRY_REQ      */
    /***********************************************************************/
    /************RRC status*************************************************/
    ID_MTA_LRRC_QRY_RRCSTATUS_REQ              = MTA_LRRC_MSG_TYPE_BASE + 59,  /* _H2ASN_MsgChoice MTA_LRRC_RRC_STATUS_QRY_REQ      */
    /***********************************************************************/

    ID_MTA_LRRC_CLEAR_HISTORY_FREQ_REQ          = MTA_LRRC_MSG_TYPE_BASE + 61,   /* _H2ASN_MsgChoice MTA_LRRC_CLEAR_HISTORY_FREQ_REQ_STRU */


    /* 消息方向LRRC/GAS/WRR/TDRRC->MTA */
    ID_LRRC_MTA_CELLINFO_QRY_CNF                = MTA_LRRC_MSG_TYPE_BASE + 2,   /* _H2ASN_MsgChoice LRRC_MTA_CELLINFO_QRY_CNF_STRU      */

    ID_TLRRC_MTA_QRY_DPDT_VALUE_CNF              = MTA_LRRC_MSG_TYPE_BASE + 8,   /* _H2ASN_MsgChoice TLRRC_MTA_QRY_DPDT_VALUE_CNF_STRU      */

    /* Added by l00198894 for 新增+ECID命令, 2013-12-09, end */

    ID_LRRC_MTA_NETMON_CELL_QRY_CNF             = MTA_LRRC_MSG_TYPE_BASE + 12,  /* _H2ASN_MsgChoice LRRC_MTA_NETMON_CELL_INFO_QRY_CNF_STRU      */

    /*T模FREQLOCK锁频CNF消息*/
    ID_TDS_MTA_FREQLOCK_SET_CNF                 = MTA_LRRC_MSG_TYPE_BASE + 14,

    /*L模FREQLOCK锁频CNF消息*/
    ID_LRRC_MTA_FREQLOCK_SET_CNF                = MTA_LRRC_MSG_TYPE_BASE + 16,

    ID_LRRC_MTA_MBMS_SERVICE_OPTION_CNF         = MTA_LRRC_MSG_TYPE_BASE + 18,  /* _H2ASN_MsgChoice LRRC_MTA_MBMS_SERVICE_OPTION_CNF_STRU      */

    ID_LRRC_MTA_MBMS_SERVICE_STATE_SET_CNF      = MTA_LRRC_MSG_TYPE_BASE + 20,  /* _H2ASN_MsgChoice LRRC_MTA_MBMS_SERVICE_STATE_SET_CNF_STRU      */

    ID_LRRC_MTA_MBMS_AVL_SERVICE_LIST_QRY_CNF   = MTA_LRRC_MSG_TYPE_BASE + 22,  /* _H2ASN_MsgChoice LRRC_MTA_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU      */

    ID_LRRC_MTA_MBMS_PREFERENCE_SET_CNF         = MTA_LRRC_MSG_TYPE_BASE + 24,  /* _H2ASN_MsgChoice LRRC_MTA_MBMS_PREFERENCE_SET_CNF_STRU      */

    ID_LRRC_MTA_SIB16_NETWORK_TIME_QRY_CNF      = MTA_LRRC_MSG_TYPE_BASE + 26,  /* _H2ASN_MsgChoice LRRC_MTA_SIB16_NETWORK_TIME_QRY_CNF_STRU      */

    ID_LRRC_MTA_BSSI_SIGNAL_LEVEL_QRY_CNF       = MTA_LRRC_MSG_TYPE_BASE + 28,  /* _H2ASN_MsgChoice LRRC_MTA_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU      */

    ID_LRRC_MTA_NETWORK_INFO_QRY_CNF            = MTA_LRRC_MSG_TYPE_BASE + 30,  /* _H2ASN_MsgChoice LRRC_MTA_NETWORK_INFO_QRY_CNF_STRU      */

    ID_LRRC_MTA_EMBMS_STATUS_QRY_CNF            = MTA_LRRC_MSG_TYPE_BASE + 32,  /* _H2ASN_MsgChoice LRRC_MTA_EMBMS_STATUS_QRY_CNF_STRU      */

    ID_LRRC_MTA_MBMS_UNSOLICITED_CFG_SET_CNF    = MTA_LRRC_MSG_TYPE_BASE + 34,  /* _H2ASN_MsgChoice LRRC_MTA_MBMS_UNSOLICITED_CFG_SET_CNF_STRU      */

    ID_LRRC_MTA_MBMS_SERVICE_EVENT_IND          = MTA_LRRC_MSG_TYPE_BASE + 35,  /* _H2ASN_MsgChoice LRRC_MTA_MBMS_SERVICE_EVENT_IND_STRU      */

    ID_LRRC_MTA_LTE_WIFI_COEX_SET_CNF           = MTA_LRRC_MSG_TYPE_BASE + 37,  /* _H2ASN_MsgChoice LRRC_MTA_LTE_WIFI_COEX_SET_CNF_STRU      */

    ID_LRRC_MTA_LOW_POWER_CONSUMPTION_SET_CNF   = MTA_LRRC_MSG_TYPE_BASE + 39,  /* _H2ASN_MsgChoice LRRC_MTA_LOW_POWER_CONSUMPTION_SET_CNF_STRU      */

    ID_LRRC_MTA_INTEREST_LIST_SET_CNF           = MTA_LRRC_MSG_TYPE_BASE + 41,  /* _H2ASN_MsgChoice LRRC_MTA_INTEREST_LIST_SET_CNF_STRU      */
    ID_MTA_LRRC_SET_FR_REQ                      = MTA_LRRC_MSG_TYPE_BASE + 47,  /* _H2ASN_MsgChoice MTA_LRRC_SET_FR_REQ_STRU      */
    ID_LRRC_MTA_SET_FR_CNF                      = MTA_LRRC_MSG_TYPE_BASE + 48,  /* _H2ASN_MsgChoice LRRC_MTA_SET_FR_CNF_STRU      */

	ID_LRRC_MTA_TRANSMODE_QRY_CNF               = MTA_LRRC_MSG_TYPE_BASE + 50,   /* _H2ASN_MsgChoice LRRC_MTA_TRANSMODE_QRY_CNF_STRU      */

    /************无线发射功率tx power (4G)**********************************/
    ID_LRRC_MTA_QRY_TXPOWER_CNF                = MTA_LRRC_MSG_TYPE_BASE + 52,  /* _H2ASN_MsgChoice LRRC_MTA_TX_PWR_QRY_CNF      */
    /***********************************************************************/
    /************MCS *******************************************************/
    ID_LRRC_MTA_QRY_MCS_CNF                    = MTA_LRRC_MSG_TYPE_BASE + 54,  /* _H2ASN_MsgChoice LRRC_MTA_MCS_QRY_CNF      */
    /***********************************************************************/
    /************EARFCN*****************************************************/
    ID_LRRC_MTA_QRY_EARFCN_CNF                 = MTA_LRRC_MSG_TYPE_BASE + 56,  /* _H2ASN_MsgChoice LRRC_MTA_EARFCN_QRY_CNF      */
    /***********************************************************************/
    /************TDD时隙配比************************************************/
    ID_LRRC_MTA_QRY_LFRAMERATIO_CNF            = MTA_LRRC_MSG_TYPE_BASE + 58,  /* _H2ASN_MsgChoice LRRC_MTA_LFRAMERATIO_QRY_CNF      */
    /***********************************************************************/
    /************RRC status*************************************************/
    ID_LRRC_MTA_QRY_RRCSTATUS_CNF              = MTA_LRRC_MSG_TYPE_BASE + 60,  /* _H2ASN_MsgChoice LRRC_MTA_RRC_STATUS_QRY_CNF      */
    /***********************************************************************/

    ID_LRRC_MTA_CLEAR_HISTORY_FREQ_CNF         = MTA_LRRC_MSG_TYPE_BASE + 62,   /* _H2ASN_MsgChoice LRRC_MTA_CLEAR_HISTORY_FREQ_CNF_STRU */

    ID_MTA_RRC_MSG_TYPE_BUTT
};
typedef VOS_UINT32 MTA_RRC_MSG_TYPE_ENUM_UINT32;

/* Added by l00198894 for 新增+ECID命令, 2013-12-09, begin */
/*****************************************************************************
 枚举名    : MTA_RRC_RESULT_ENUM
 结构说明  : MTA模块与接入层间的结果码枚举

  1.日    期   : 2013年12月09日
    作    者   : l00198894
    修改内容   : 新增
*****************************************************************************/
enum MTA_RRC_RESULT_ENUM
{
    MTA_RRC_RESULT_NO_ERROR                     = 0x000000,                     /* 消息处理正常 */
    MTA_RRC_RESULT_ERROR,                                                       /* 消息处理出错 */

    MTA_RRC_RESULT_BUTT
};
typedef VOS_UINT32 MTA_RRC_RESULT_ENUM_UINT32;
/* Added by l00198894 for 新增+ECID命令, 2013-12-09, end */

/*******************************************************************************
 枚举名    : NMR_UTRAN_MEASURED_TYPE_ENUM
 结构说明  : NMR测量信息类型选择:FDD TDD
 1.日    期   : 2012年11月23日
   作    者   : w00134354
   修改内容   : Added for NMR
*******************************************************************************/
enum NMR_UTRAN_MEASURED_TYPE_ENUM
{
    NMR_UTRAN_MEASURED_TYPE_FDD = 0,
    NMR_UTRAN_MEASURED_TYPE_TDD,
    NMR_UTRAN_MEASURED_TYPE_BUTT
};
typedef VOS_UINT32 NMR_UTRAN_MEASURED_TYPE_ENUM_UINT32;

/*******************************************************************************
 枚举名    : GRR_MTA_NCELL_STATE_ENUM
 结构说明  : 邻区状态枚举
 1.日    期   : 2013年06月04日
   作    者   : s00217060
   修改内容   : for V9R1_SVLTE
*******************************************************************************/
enum GRR_MTA_NCELL_STATE_ENUM
{
    GRR_MTA_NCELL_STATE_NULL    = 0x00,                                         /* 既没有TD的邻区，也没有4G邻区 */
    GRR_MTA_NCELL_STATE_3G      = 0x01,                                         /* 只有TD的邻区 */
    GRR_MTA_NCELL_STATE_4G      = 0x02,                                         /* 只有4G的邻区 */
    GRR_MTA_NCELL_STATE_3G4G    = 0x03,                                         /* 既有TD的邻区，也有4G邻区 */
    GRR_MTA_NCELL_STATE_BUTT

};
typedef VOS_UINT8 GRR_MTA_NCELL_STATE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MTA_RRC_JAM_MODE_ENUM
 结构说明  : MTA模块与接入层间的JAM模式的枚举

  1.日    期   : 2014年04月25日
    作    者   : y00142674
    修改内容   : 新增
*****************************************************************************/
enum MTA_RRC_JAM_MODE_ENUM
{
    MTA_RRC_JAM_MODE_STOP               = 0x00,                                 /* 停止JAM检测 */
    MTA_RRC_JAM_MODE_START,                                                     /* 启动JAM检测 */

    MTA_RRC_JAM_MODE_BUTT
};
typedef VOS_UINT8 MTA_RRC_JAM_MODE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : MTA_RRC_JAM_RESULT_ENUM
 结构说明  : MTA模块与接入层间的JAM结果的枚举

  1.日    期   : 2014年04月25日
    作    者   : y00142674
    修改内容   : 新增
*****************************************************************************/
enum MTA_RRC_JAM_RESULT_ENUM
{
    MTA_RRC_JAM_RESULT_JAM_DISAPPEARED  = 0x00,                                 /* 干扰不存在 */
    MTA_RRC_JAM_RESULT_JAM_DISCOVERED,                                          /* 干扰存在 */

    MTA_RRC_JAM_RESULT_BUTT
};
typedef VOS_UINT8 MTA_RRC_JAM_RESULT_ENUM_UINT8;


/*****************************************************************************
 枚举名    : MTA_RRC_FREQLOCK_TYPE_ENUM
 结构说明  : FREQLOCK锁频类型枚举
1.日    期  : 2014年10月21日
  作    者  : z00214637
  修改内容  : 新增结构
*****************************************************************************/
enum MTA_RRC_FREQLOCK_TYPE_ENUM
{
    MTA_RRC_FREQLOCK_TYPE_ENUM_FREQ_ONLY     = 1,                               /* 锁频ONLY类型 */
    MTA_RRC_FREQLOCK_TYPE_ENUM_FREQ_COMBINED = 2,                               /* 锁频+主扰码/扰码/物理小区ID */
    MTA_RRC_FREQLOCK_TYPE_ENUM_BUTT
};
typedef VOS_UINT8 MTA_RRC_FREQLOCK_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MTA_LRRC_CLEAR_HISTORY_FREQ_TYPE_ENUM
 结构说明  : 清除历史频点类型枚举
1.日    期   : 2015年9月11日
  作    者   : z00161729
  修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
enum MTA_LRRC_CLEAR_HISTORY_FREQ_TYPE_ENUM
{
    MTA_LRRC_CLEAR_HISTORY_FREQ_TYPE_NONE_CSG         = 0,    /* 清除非CSG历史频点信息 */
    MTA_LRRC_CLEAR_HISTORY_FREQ_TYPE_CSG              = 1,    /* 清除CSG历史频点信息 */
    MTA_LRRC_CLEAR_HISTORY_FREQ_TYPE_NONE_CSG_AND_CSG = 2,    /* 清除所有（包括非CSG和CSG）
                                                                 历史频点信息 */
    MTA_LRRC_CLEAR_HISTORY_FREQ_TYPE_BUTT
};
typedef VOS_UINT8 MTA_LRRC_CLEAR_HISTORY_FREQ_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MBMS_SERVICE_OP_ENUM
 结构说明  : MBMS Service特性是使能/去使能枚举

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
enum MBMS_SERVICE_OP_ENUM
{
    MBMS_SERVICE_OP_DISABLE             = 0,
    MBMS_SERVICE_OP_ENABLE              = 1,
    MBMS_SERVICE_OP_BUTT
};
typedef VOS_UINT8 MBMS_SERVICE_OP_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MBMS_SERVICE_STATE_SET_ENUM
 结构说明  : MBMS Service状态设置枚举

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
enum MBMS_SERVICE_STATE_SET_ENUM
{
    MBMS_SERVICE_STATE_SET_ACTIVE       = 0,
    MBMS_SERVICE_STATE_SET_DEACTIVE     = 1,
    MBMS_SERVICE_STATE_SET_DEACTIVE_ALL = 2,
    MBMS_SERVICE_STATE_SET_BUTT
};
typedef VOS_UINT8 MBMS_SERVICE_STATE_SET_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MBMS_CAST_MODE_ENUM
 结构说明  : MBMS 广播模式枚举

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
enum MBMS_CAST_MODE_ENUM
{
    MBMS_CAST_MODE_UNICAST              = 0,
    MBMS_CAST_MODE_MULTICAST            = 1,
    MBMS_CAST_MODE_BUTT
};
typedef VOS_UINT8 MBMS_CAST_MODE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MBMS_FUNTIONALITY_STATUS_ENUM
 结构说明  : MBMS 功能状态枚举

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
enum MBMS_FUNTIONALITY_STATUS_ENUM
{
    MBMS_FUNTIONALITY_OFF               = 0,
    MBMS_FUNTIONALITY_ON                = 1,
    MBMS_FUNTIONALITY_STATUS_BUTT
};
typedef VOS_UINT8 MBMS_FUNTIONALITY_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MBMS_UNSOLICITED_CFG_ENUM
 结构说明  : MBMS 主动上报配置枚举

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
enum MBMS_UNSOLICITED_CFG_ENUM
{
    MBMS_UNSOLICITED_DISABLE            = 0,
    MBMS_UNSOLICITED_ENABLE             = 1,
    MBMS_UNSOLICITED_CFG_BUTT
};
typedef VOS_UINT8 MBMS_UNSOLICITED_CFG_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MBMS_SERVICE_EVENT_ENUM
 结构说明  : MBMS 服务状态事件枚举

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
enum MBMS_SERVICE_EVENT_ENUM
{
    MBMS_SERVICE_EVENT_SERVICE_CHANGE       = 0,
    MBMS_SERVICE_EVENT_NO_SERVICE           = 1,
    MBMS_SERVICE_EVENT_ONLY_UNICAST         = 2,
    MBMS_SERVICE_EVENT_SERVICE_AVAILABLE    = 3,
    MBMS_SERVICE_EVENT_BUTT
};
typedef VOS_UINT8 MBMS_SERVICE_EVENT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MTA_LRRC_COEX_BW_TYPE_ENUM
 枚举说明  : LTE&WIFI宽带类型枚举

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
enum MTA_LRRC_COEX_BW_TYPE_ENUM
{
    MTA_LRRC_COEX_BAND_WIDTH_6RB        = 0,                                    /* 宽带1.4M */
    MTA_LRRC_COEX_BAND_WIDTH_15RB       = 1,                                    /* 宽带3M */
    MTA_LRRC_COEX_BAND_WIDTH_25RB       = 2,                                    /* 宽带5M */
    MTA_LRRC_COEX_BAND_WIDTH_50RB       = 3,                                    /* 宽带10M */
    MTA_LRRC_COEX_BAND_WIDTH_75RB       = 4,                                    /* 宽带15M */
    MTA_LRRC_COEX_BAND_WIDTH_100RB      = 5,                                    /* 宽带20M */
    MTA_LRRC_COEX_BAND_WIDTH_BUTT
};
typedef VOS_UINT16 MTA_LRRC_COEX_BW_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : MTA_LRRC_COEX_CFG_ENUM
 枚举说明  : LTE&WIFI共存方案配置枚举

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
enum MTA_LRRC_COEX_CFG_ENUM
{
    MTA_LRRC_COEX_CFG_DISABLE           = 0,
    MTA_LRRC_COEX_CFG_ENABLE            = 1,
    MTA_LRRC_COEX_CFG_BUTT
};
typedef VOS_UINT16 MTA_LRRC_COEX_CFG_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RRC_MTA_BAND_IND_ENUM
 结构说明  : MTA模块与接入层间的频段的枚举

  1.日    期   : 2015年07月07日
    作    者   : y00142674
    修改内容   : 新增, for 云端频点收集
*****************************************************************************/
enum RRC_MTA_BAND_IND_ENUM
{
    RRC_MTA_BAND_IND_NONE               = 0,
    RRC_MTA_BAND_IND_1,
    RRC_MTA_BAND_IND_2,
    RRC_MTA_BAND_IND_3,
    RRC_MTA_BAND_IND_4,
    RRC_MTA_BAND_IND_5,
    RRC_MTA_BAND_IND_6,
    RRC_MTA_BAND_IND_7,
    RRC_MTA_BAND_IND_8,
    RRC_MTA_BAND_IND_9,
    RRC_MTA_BAND_IND_10,
    RRC_MTA_BAND_IND_11,
    RRC_MTA_BAND_IND_12,
    RRC_MTA_BAND_IND_13,
    RRC_MTA_BAND_IND_14,
    RRC_MTA_BAND_IND_15,
    RRC_MTA_BAND_IND_16,
    RRC_MTA_BAND_IND_17,
    RRC_MTA_BAND_IND_18,
    RRC_MTA_BAND_IND_19,
    RRC_MTA_BAND_IND_20,
    RRC_MTA_BAND_IND_21,
    RRC_MTA_BAND_IND_22,
    RRC_MTA_BAND_IND_23,
    RRC_MTA_BAND_IND_24,
    RRC_MTA_BAND_IND_25,
    RRC_MTA_BAND_IND_26,
    RRC_MTA_BAND_IND_27,
    RRC_MTA_BAND_IND_28,
    RRC_MTA_BAND_IND_29,
    RRC_MTA_BAND_IND_30,
    RRC_MTA_BAND_IND_31,
    RRC_MTA_BAND_IND_32,
    RRC_MTA_BAND_IND_33,
    RRC_MTA_BAND_IND_34,
    RRC_MTA_BAND_IND_35,
    RRC_MTA_BAND_IND_36,
    RRC_MTA_BAND_IND_37,
    RRC_MTA_BAND_IND_38,
    RRC_MTA_BAND_IND_39,
    RRC_MTA_BAND_IND_40,
    RRC_MTA_BAND_IND_41,
    RRC_MTA_BAND_IND_42,
    RRC_MTA_BAND_IND_43,
    RRC_MTA_BAND_IND_44,

    RRC_MTA_BAND_IND_BUTT
};
typedef VOS_UINT16 RRC_MTA_BAND_IND_ENUM_UINT16;


/*****************************************************************************
 枚举名    : MTA_RRC_FREQ_QRY_TYPE_ENUM
 枚举说明  : 频点频段查询的类型

  1.日    期   : 2015年7月22日
    作    者   : f00179208
    修改内容   : 新增
*****************************************************************************/
enum MTA_RRC_FREQ_QRY_TYPE_ENUM
{
    MTA_RRC_FREQ_QRY_TYPE_SPEC_PLMN           = 0,
    MTA_RRC_FREQ_QRY_TYPE_ALL_PLMN            = 1,
    MTA_RRC_FREQ_QRY_TYPE_BUTT
};
typedef VOS_UINT8 MTA_RRC_FREQ_QRY_TYPE_UINT8;


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
 结构名    : MTA_RRC_PLMN_ID_STRU
 结构说明  : PLMN ID结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;                                  /* MCC, 3 bytes, 无效值: 0xFFFFFFFF */
    VOS_UINT32                          ulMnc;                                  /* MNC, 2 or 3 bytes, 无效值: 0xFFFFFFFF */
} MTA_RRC_PLMN_ID_STRU;

/*******************************************************************************
 结构名    : MTA_RRC_POSITION_REQ_STRU
 结构说明  : 接入层发送给GPS芯片的定位请求的参数
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;                    /*_H2ASN_Skip*/

    VOS_UINT32                                  bitOpAssistData   : 1;
    VOS_UINT32                                  bitOpPosMeas      : 1;
    VOS_UINT32                                  bitOpSpare        : 30;

    PS_BOOL_ENUM_UINT8                          enDeleteAssistDataFlag;         /* 是否需要清除辅助数据的标记 */
    VOS_UINT8                                   aucRsv[3];                      /* 保留位 */
    AGPS_ASSIST_DATA_STRU                       stAssistData;                   /* assist_data,辅助数据 */
    AGPS_MEASURE_REQ_STRU                       stPosMeas;                      /* pos_meas,位置测量请求 */
}MTA_RRC_POSITION_REQ_STRU;

/*******************************************************************************
 结构名    : MTA_RRC_POSITION_CNF_STRU
 结构说明  : GPS的定位回复
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                     stMsgHeader;            /*_H2ASN_Skip*/

    VOS_UINT8                                           aucRsv[3];              /* 保留位 */
    AGPS_POSITION_RESULT_TYPE_ENUM_UINT8                enResultTypeChoice;     /* 结果信息类型 */
    union
    {
        AGPS_LOCATION_INFO_STRU                         stLocationInfo;         /* location,位置信息 */
        AGPS_GPS_MEASURE_INFO_STRU                      stGpsMeasInfo;          /* GPS_meas,GPS测量信息 */
        AGPS_POSITION_GPS_ADDITION_ASSIST_REQ_STRU      stAssistDataReq;        /* GPS_assist_req,辅助数据请求 */
        AGPS_POSITION_ERR_STRU                          stPosErr;               /* pos_err,位置错误信息 */
    }u;
}MTA_RRC_POSITION_CNF_STRU;

/*******************************************************************************
 结构名    : MTA_RRC_RESEL_OFFSET_CFG_NTF
 结构说明  : W往L重选迟滞参数配置
 1.日    期   : 2012年12月07日
   作    者   : l00128652 h44270
   修改内容   : 新增结构

*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;                    /*_H2ASN_Skip*/
    PS_BOOL_ENUM_UINT8                          enOffsetEnable;                 /* 0:灭屏；1:亮屏*/
    VOS_UINT8                                   aucRsv[3];                      /* 保留位*/
}MTA_RRC_RESEL_OFFSET_CFG_NTF_STRU;


/*******************************************************************************
 结构名    : NMR_UTRAN_FREQUENCY_INFO_FDD_STRU
 结构说明  : NMR 频点信息

 1.日    期   : 2012年11月23日
   作    者   : w00134354
   修改内容   : Added for NMR

   FrequencyInfoFDD ::= SEQUENCE {uarfcn-UL UARFCN OPTIONAL,
                                  uarfcn-DL UARFCN,...}
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  bitOpUarfcn_UL        : 1;
    VOS_UINT32                                  bitOpSpare            : 31;
    VOS_UINT16                                  usUlUarfcn;           /* 上行频点 */
    VOS_UINT16                                  usDlUarfcn;           /* 下行频点 */
}NMR_UTRAN_FREQUENCY_INFO_FDD_STRU;

/*******************************************************************************
 结构名    : NMR_UTRAN_FREQUENCY_INFO_STRU
 结构说明  : NMR FrequencyInfo结构
 1.日    期   : 2012年11月23日
   作    者   : w00134354
   修改内容   : Added for NMR
*******************************************************************************/
typedef struct
{
    NMR_UTRAN_MEASURED_TYPE_ENUM_UINT32           enFreqInfoChoice;     /* NMR频率信息类型:0:FDD,1:TDD */
    union
    {
        NMR_UTRAN_FREQUENCY_INFO_FDD_STRU         stFreqInfoFDD;         /* fdd */
        VOS_UINT32                                ulFreqInfoTDD;          /*  TDD */
    }u;

}NMR_UTRAN_FREQUENCY_INFO_STRU;
/*******************************************************************************
 结构名    : NMR_UTRAN_CELL_MEAS_RESULTS_FDD_STRU
 结构说明  : NMR Cell Measured Results FDD
 1.日    期   : 2012年11月23日
   作    者   : w00134354
   修改内容   : Added for NMR
*******************************************************************************/

typedef struct
{
    VOS_UINT32                                  bitOpEcn0      : 1;
    VOS_UINT32                                  bitOpRscp      : 1;
    VOS_UINT32                                  bitOpPathloss  : 1;
    VOS_UINT32                                  bitOpSpare     : 29;

    VOS_UINT16                                  usCellPSC;
    VOS_UINT8                                   ucEcn0;              /* INTEGER(0..63) */
    VOS_UINT8                                   ucRscp;              /*  INTEGER(0..127)*/
    VOS_UINT8                                   ucPathloss;           /* INTEGER(46..173)  */
    VOS_UINT8                                   aucRsv[3];


}NMR_UTRAN_CELL_MEAS_RESULTS_FDD_STRU;

/*******************************************************************************
 结构名    : NMR_UTRAN_MEAS_RESULTS_STRU
 结构说明  : NMR Cell Measured Results TDD
 1.日    期   : 2012年11月23日
   作    者   : w00134354
   修改内容   : Added for NMR
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  bitOpProposedTGSN  : 1;
    VOS_UINT32                                  bitOpRscp          : 1;
    VOS_UINT32                                  bitOpPathloss      : 1;
    VOS_UINT32                                  bitOpTimeslotISCP  : 1;
    VOS_UINT32                                  bitOpSpare         : 28;

    VOS_UINT8                                   ucCellParaID;         /* INTEGER(0..127) */
    VOS_UINT8                                   ucProposedTGSN;       /* INTEGER(0..14)  */
    VOS_UINT8                                   ucRscp;               /* INTEGER(0..127) */
    VOS_UINT8                                   ucPathloss;           /* INTEGER(46..173) */
    VOS_UINT8                                   ucTimeslotISCP;       /* INTEGER(46..173) */
    VOS_UINT8                                   aucRsv[3];

}NMR_UTRAN_CELL_MEAS_RESULTS_TDD_STRU;

/*******************************************************************************
 结构名    : NMR_UTRAN_CELL_MEAS_RESULTS_STRU
 结构说明  : NMR Cell Measured Results
 1.日    期   : 2012年11月23日
   作    者   : w00134354
   修改内容   : Added for NMR
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  bitOpCellID               : 1;
    VOS_UINT32                                  bitOpSpare                : 31;

    VOS_UINT32                                  ulCellID;                 /*  */
    NMR_UTRAN_MEASURED_TYPE_ENUM_UINT32         enCellMeasTypeChoice;     /* NMR频率信息类型:FDD,TDD */
    union
    {
        NMR_UTRAN_CELL_MEAS_RESULTS_FDD_STRU    stCellMeasResultsFDD;         /* FDD */
        NMR_UTRAN_CELL_MEAS_RESULTS_TDD_STRU    stCellMeasResultsTDD;         /*  TDD */
    }u;

}NMR_UTRAN_CELL_MEAS_RESULTS_STRU;

/*******************************************************************************
 结构名    : NMR_MEASURED_RESULTS_LIST_STRU
 结构说明  : NMR Cell Measured Results List
 1.日    期   : 2012年11月23日
   作    者   : w00134354
   修改内容   : Added for NMR
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulMeasCellNum;            /* (0,32) */
    NMR_UTRAN_CELL_MEAS_RESULTS_STRU            astCellMeasResults[NMR_MAX_CELL_FREQ_NUM];
}NMR_UTRAN_CELL_MEAS_RESULTS_LIST_STRU;

/*******************************************************************************
 结构名    : NMR_UTRAN_MEASURED_RESULTS_STRU
 结构说明  : 3G模式下测量结果
 1.日    期   : 2012年11月23日
   作    者   : w00134354
   修改内容   : Added for NMR
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  bitOpFrequencyInfo        : 1;
    VOS_UINT32                                  bitOpUTRA_CarrierRSSI     : 1;
    VOS_UINT32                                  bitOpCellMeasResultsList  : 1;
    VOS_UINT32                                  bitOpSpare                : 29;

    NMR_UTRAN_FREQUENCY_INFO_STRU               stFrequencyInfo;
    VOS_UINT32                                  ulUTRA_CarrierRSSI; /* 频点的RSSI */
    NMR_UTRAN_CELL_MEAS_RESULTS_LIST_STRU       stCellMeasResultsList;
}NMR_UTRAN_MEASURED_RESULTS_STRU;

/*******************************************************************************
 结构名    : RRC_MTA_UTRAN_NMR_STRU
 结构说明  : 3G模式下NMR数据信息
 1.日    期   : 2012年11月23日
   作    者   : w00134354
   修改内容   : Added for NMR
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                ulFreqNum;            /* (0,8) */
    NMR_UTRAN_MEASURED_RESULTS_STRU           astMeasResults[NMR_MAX_FREQ_NUM];
}RRC_MTA_UTRAN_NMR_STRU;

/*******************************************************************************
 结构名    : RRC_MTA_GSM_NMR_ELEMENT_STRU
 结构说明  : 2G模式下NMR ELEMENT数据信息
 1.日    期   : 2012年11月26日
   作    者   : j00178524
   修改内容   : Added for NMR
*******************************************************************************/
typedef struct
{
    VOS_UINT16                                usArfcn;            /* 小区绝对频点号, 取值范围[0,1023] */
    VOS_UINT8                                 ucBsic;             /* 小区BSIC, [0,63] */
    VOS_UINT8                                 ucRxlev;            /* 小区测量电平, 已经映射为[0,63]的取值范围的取值 */
}RRC_MTA_GSM_NMR_ELEMENT_STRU;


/*******************************************************************************
 结构名    : RRC_MTA_GSM_NMR_STRU
 结构说明  : 2G模式下NMR数据信息
 1.日    期   : 2012年11月26日
   作    者   : j00178524
   修改内容   : Added for NMR
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                ulElemNum;                        /* GSM NMR元素个数 [0,15] */

    /* GSM NMR元素数组, 第一个元素服务小区, 之后的元素是GSM邻区, GSM邻区按照信号强度由高到低排序 */
    RRC_MTA_GSM_NMR_ELEMENT_STRU              astNmrElem[RRC_MTA_NMR_MAX_GSM_ELEM_NUM];
}RRC_MTA_GSM_NMR_STRU;

/*****************************************************************************
 结构名    : MTA_RRC_QRY_NMR_REQ_STRU
 结构说明  : ID_MTA_RRC_QRY_NMR_REQ消息结构
 1.日    期   : 2012年11月23日
   作    者   : s46746
   修改内容   : 创建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头    */     /*_H2ASN_Skip*/
    /* MTA_RRC_MSG_TYPE_ENUM_UINT32        enMsgId; */

    VOS_UINT8                           aucReserve[4];                          /* 预留后续使用 */
} MTA_RRC_QRY_NMR_REQ_STRU;

/*****************************************************************************
 结构名    : RRC_MTA_QRY_NMR_CNF_STRU
 结构说明  : ID_RRC_MTA_QRY_NMR_CNF消息结构
 1.日    期   : 2012年11月23日
   作    者   : s46746
   修改内容   : 创建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头    */     /*_H2ASN_Skip*/

    /* ulChoice 的宏定义 */
    VOS_UINT32                          ulChoice;
    union
    {
        RRC_MTA_UTRAN_NMR_STRU          stUtranNMRData;
        RRC_MTA_GSM_NMR_STRU            stGsmNMRData;
    }u;
} RRC_MTA_QRY_NMR_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_WRR_AUTOTEST_PARA_STRU
 结构说明  : AS测试命令参数

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCmd;                                  /* 自动化测试命令 */
    VOS_UINT8                           ucParaNum;                              /* 命令参数个数 */
    VOS_UINT16                          usReserve;                              /* 四字节对齐 */
    VOS_UINT32                          aulPara[MTA_WRR_AUTOTEST_MAX_PARA_NUM]; /* 命令参数 */
}MTA_WRR_AUTOTEST_PARA_STRU;

/*****************************************************************************
 结构名    : MTA_WRR_AUTOTEST_QRY_REQ_STRU
 结构说明  : AS测试命令结构

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    MTA_WRR_AUTOTEST_PARA_STRU          stWrrAutotestPara;
}MTA_WRR_AUTOTEST_QRY_REQ_STRU;

/*****************************************************************************
 结构名    : WRR_MTA_AUTOTEST_QRY_RSLT_STRU
 结构说明  : WAS测试命令返回结果

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRsltNum;                              /* 查询结果个数 */
    VOS_UINT32                          aulRslt[WRR_MTA_AUTOTEST_MAX_RSULT_NUM];/* 查询结果 */
}WRR_MTA_AUTOTEST_QRY_RSLT_STRU;

/*****************************************************************************
 结构名    : WRR_MTA_AUTOTEST_QRY_CNF_STRU
 结构说明  : WAS测试命令返回结果消息结构

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulResult;
    WRR_MTA_AUTOTEST_QRY_RSLT_STRU      stWrrAutoTestRslt;
} WRR_MTA_AUTOTEST_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_WRR_CELLINFO_SET_REQ_STRU
 结构说明  : MTA设置WAS cellinfo消息结构

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulSetCellInfo;                          /* 0:查询主小区信息 1:查询W邻区信息 */
} MTA_WRR_CELLINFO_QRY_REQ_STRU;

/*****************************************************************************
 结构名    : WRR_MTA_WCDMA_CELLINFO_STRU
 结构说明  : 小区信息结构

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      usCellFreq;                                 /* 频点 */
    VOS_UINT16                      usPrimaryScramCode;                         /* 扰码 */
    VOS_INT16                       sCpichRscp;                                 /* RSCP值 */
    VOS_INT16                       sCpichEcN0;                                 /* ECN0值 */

}WRR_MTA_WCDMA_CELLINFO_STRU;

/*****************************************************************************
 结构名    : WRR_MTA_WCDMA_CELLINFO_RSLT_STRU
 结构说明  : WRR回复MTA小区信息查询结构

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
     VOS_UINT32                     ulCellNum;
     WRR_MTA_WCDMA_CELLINFO_STRU    astWCellInfo[WRR_MTA_MAX_NCELL_NUM];         /*最多支持W 8个邻区的查询*/

} WRR_MTA_WCDMA_CELLINFO_RSLT_STRU;
/*****************************************************************************
 结构名    : WRR_MTA_CELLINFO_QRY_CNF_STRU
 结构说明  : WRR回复MTA小区信息查询结构

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                              ulMsgName;                          /*_H2ASN_Skip*/
    VOS_UINT32                              ulResult;
    WRR_MTA_WCDMA_CELLINFO_RSLT_STRU        stWrrCellInfo;
} WRR_MTA_CELLINFO_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_WRR_MEANRPT_QRY_REQ_STRU
 结构说明  : MTA下发MEANRPT QRY消息结构

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;
} MTA_WRR_MEANRPT_QRY_REQ_STRU;

/*****************************************************************************
 结构名    : WRR_MTA_MEANRPT_STRU
 结构说明  : 测量报告中的事件+小区

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      usEventId;                                  /* 对应的事件类型 */
    VOS_UINT16                      usCellNum;                                  /* 一次测量报告上报小区个数*/
    VOS_UINT16                      ausPrimaryScramCode[WRR_MTA_MEANRPT_MAX_CELL_NUM];/* 扰码 */
}WRR_MTA_MEANRPT_STRU;

/*****************************************************************************
 结构名    : WRR_MTA_MEANRPT_RSLT_STRU
 结构说明  : 自动化测试AT^MEANRPT,
             查询最近最多10次测量报告中的事件+小区

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulRptNum;                                   /* 最近的测量报告次数 */
    WRR_MTA_MEANRPT_STRU            astMeanRptInfo[WRR_MTA_MAX_MEANRPT_NUM];    /* 测量报告上报的小区 */
}WRR_MTA_MEANRPT_RSLT_STRU;


/*****************************************************************************
 结构名    : WRR_MTA_MEANRPT_QRY_CNF_STRU
 结构说明  : WRR给MTA回复^MEANRPT请求的消息结构

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulResult;
    WRR_MTA_MEANRPT_RSLT_STRU           stMeanRptRslt;
} WRR_MTA_MEANRPT_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_WRR_FREQLOCK_CTRL_STRU
 结构说明  : WAS锁频控制结构

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucFreqLockEnable;                       /* 是否锁频 0:未锁频 1:锁频 */
    VOS_UINT8                           aucReserved[1];
    VOS_UINT16                          usLockedFreq;                           /* 锁定的频点 */
} MTA_WRR_FREQLOCK_CTRL_STRU;

/*****************************************************************************
 结构名    : MTA_WRR_FREQLOCK_SET_REQ_STRU
 结构说明  : MTA下发MEANRPT QRY消息结构

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    MTA_WRR_FREQLOCK_CTRL_STRU          stFrelock;
} MTA_WRR_FREQLOCK_SET_REQ_STRU;

/*****************************************************************************
 结构名    : WRR_MTA_FREQLOCK_SET_CNF_STRU
 结构说明  : MTA给AT回的锁频设置结果

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulResult;
} WRR_MTA_FREQLOCK_SET_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_WRR_FREQLOCK_QRY_REQ_STRU
 结构说明  : MTA下发MEANRPT QRY消息结构

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;
} MTA_WRR_FREQLOCK_QRY_REQ_STRU;

/*****************************************************************************
 结构名    : WRR_MTA_FREQLOCK_QRY_CNF_STRU
 结构说明  : MTA给AT回的锁频控制结构

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulResult;
    MTA_WRR_FREQLOCK_CTRL_STRU          stFreqLockInfo;
} WRR_MTA_FREQLOCK_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_WRR_RRC_VERSION_SET_REQ_STRU
 结构说明  : MTA设置WRR version

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT8                           ucRRCVersion;                           /* RRC版本 */
    VOS_UINT8                           aucReserv[3];
} MTA_WRR_RRC_VERSION_SET_REQ_STRU;

/*****************************************************************************
 结构名    : MTA_WRR_RRC_VERSION_QRY_REQ_STRU
 结构说明  : MTA查询WRR version

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;
} MTA_WRR_RRC_VERSION_QRY_REQ_STRU;

/*****************************************************************************
 结构名    : WRR_MTA_RRC_VERSION_SET_CNF_STRU
 结构说明  : WRR给MTA上报version设置结果

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulResult;
} WRR_MTA_RRC_VERSION_SET_CNF_STRU;

/*****************************************************************************
 结构名    : WRR_MTA_RRC_VERSION_QRY_CNF_STRU
 结构说明  : WRR给MTA上报version查询结果

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucRrcVersion;                           /* RRC版本 */
    VOS_UINT8                           aucReserved[3];
} WRR_MTA_RRC_VERSION_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_WRR_CELLSRH_SET_REQ_STRU
 结构说明  : MTA下发WRR cellsrh设置请求

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT8                           ucCellSrh;                              /* 搜网模式 0:正常模式 1:不使用先验信息模式 */
    VOS_UINT8                           aucReserve[3];
} MTA_WRR_CELLSRH_SET_REQ_STRU;

/*****************************************************************************
 结构名    : WRR_MTA_CELLSRH_SET_CNF_STRU
 结构说明  : WRR给MTA上报cellsrh设置结果

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulResult;
} WRR_MTA_CELLSRH_SET_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_WRR_CELLSRH_QRY_REQ_STRU
 结构说明  : MTA下发查询WRR cellsrh 消息

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;
} MTA_WRR_CELLSRH_QRY_REQ_STRU;

/*****************************************************************************
 结构名    : WRR_MTA_CELLSRH_QRY_CNF_STRU
 结构说明  : WRR给MTA上报cellsrh查询结果

  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucCellSearchType;                       /* 搜网模式 0:正常模式 1:不使用先验信息模式 */
    VOS_UINT8                           aucReserve[3];
} WRR_MTA_CELLSRH_QRY_CNF_STRU;


/*****************************************************************************
 结构名    : MTA_GRR_NCELL_MONITOR_SET_REQ_STRU
 结构说明  : MTA发给GRRC的异系统小区变化信息控制请求消息

  1.日    期   : 2013年5月31日
    作    者   : s00217060
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT8                           ucSwitch;
    VOS_UINT8                           aucReserved[3];
} MTA_GRR_NCELL_MONITOR_SET_REQ_STRU;

/*****************************************************************************
 结构名    : MTA_GRR_NCELL_MONITOR_QRY_REQ_STRU
 结构说明  : MTA发给GRRC的查询异系统小区变化信息控制请求消息

  1.日    期   : 2013年5月31日
    作    者   : s00217060
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;
} MTA_GRR_NCELL_MONITOR_QRY_REQ_STRU;

/*****************************************************************************
 结构名    : GRR_MTA_NCELL_MONITOR_SET_CNF_STRU
 结构说明  : GRRC发给MTA的异系统小区变化信息控制请求消息的回复

  1.日    期   : 2013年5月31日
    作    者   : s00217060
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulResult;
} GRR_MTA_NCELL_MONITOR_SET_CNF_STRU;

/*****************************************************************************
 结构名    : GRR_MTA_NCELL_MONITOR_QRY_CNF_STRU
 结构说明  : GRRC发给MTA的查询异系统小区变化信息控制请求消息的回复

  1.日    期   : 2013年5月31日
    作    者   : s00217060
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucSwitch;
    GRR_MTA_NCELL_STATE_ENUM_UINT8      enNcellState;
    VOS_UINT8                           aucReserved[2];
} GRR_MTA_NCELL_MONITOR_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : GRR_MTA_NCELL_MONITOR_IND_STRU
 结构说明  : GRRC发给MTA的异系统小区变化信息主动上报

  1.日    期   : 2013年5月31日
    作    者   : s00217060
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    GRR_MTA_NCELL_STATE_ENUM_UINT8      enNcellState;
    VOS_UINT8                           aucReserved[3];
} GRR_MTA_NCELL_MONITOR_IND_STRU;

/* Added by l00198894 for 新增+ECID命令, 2013-12-09, begin */
/*****************************************************************************
 结构名    : MTA_LRRC_CELLINFO_QRY_REQ_STRU
 结构说明  : MTA发送给LRRC查询LTE增强型小区信息

  1.日    期   : 2013年12月09日
    作    者   : l00198894
    修改内容   : 新增+ECID命令
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserved[4];             /* 保留位 */
}MTA_LRRC_CELLINFO_QRY_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_CELLINFO_STRU
 结构说明  : LTE增强型小区信息结构

  1.日    期   : 2013年12月09日
    作    者   : l00198894
    修改内容   : 新增+ECID命令

  2.日    期   : 2015年12月2日
    作    者   : l00198894
    修改内容   : DTS2015120206389: LRRC接口变更，TA的偏移由物理层完成
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpEarfcn   :1;
    VOS_UINT32                          bitOpRsrp     :1;
    VOS_UINT32                          bitOpRsrq     :1;
    VOS_UINT32                          bitOpTa       :1;
    VOS_UINT32                          bitSpare      :28;
    VOS_UINT32                          ulPhyCellCode;
    VOS_UINT32                          ulEarfcn;
    VOS_UINT32                          ulRsrp;
    VOS_UINT32                          ulRsrq;
    VOS_UINT32                          ulTa;                                   /* 时间提前量，取值范围0~1282 */
}LRRC_CELLINFO_STRU;

/*****************************************************************************
 结构名    : LRRC_CELLINFO_RSLT_STRU
 结构说明  : LTE增强型小区信息结果结构

  1.日    期   : 2013年12月09日
    作    者   : l00198894
    修改内容   : 新增+ECID命令
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTac;
    VOS_UINT32                          ulCellNum;
    LRRC_CELLINFO_STRU                  astCellInfo[LRRC_MAX_NCELL_NUM];
}LRRC_CELLINFO_RSLT_STRU;

/*****************************************************************************
 结构名    : LRRC_MTA_CELLINFO_QRY_CNF_STRU
 结构说明  : LRRC回复MTA模块增强型小区信息查询结果结构

  1.日    期   : 2013年12月09日
    作    者   : l00198894
    修改内容   : 新增+ECID命令
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                /*_H2ASN_Skip*/
    MTA_RRC_RESULT_ENUM_UINT32          enResult;
    LRRC_CELLINFO_RSLT_STRU             stCellInfoRslt;
}LRRC_MTA_CELLINFO_QRY_CNF_STRU;
/* Added by l00198894 for 新增+ECID命令, 2013-12-09, end */

/*****************************************************************************
 结构名    : MTA_RRC_PROTECT_PS_IND_STRU
 结构说明  : MTA发送给rrc和lrrc模块PS保护消息的结构

  1.日    期   : 2014年3月25日
    作    者   : y00176023
    修改内容   : 新增^PSPROTECTMODE命令
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;               /*_H2ASN_Skip*/
    PS_BOOL_ENUM_UINT8                  enProtectFlg;              /* ps 保护标志 */
    VOS_UINT8                           aucRsv[3];                 /* 保留位 */
} MTA_RRC_PROTECT_PS_IND_STRU;

/*****************************************************************************
结构名    : MTA_TLRRC_SET_DPDTTEST_FLAG_NTF_STRU
结构说明  : 设置天线算法打开、关闭消息结构

  1.日    期  : 2014年04月01日
    作    者  : g00261581
    创建内容  : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT8                           ucFlag;
    VOS_UINT8                           aucReserved[3];
} MTA_TLRRC_SET_DPDTTEST_FLAG_NTF_STRU;

/*****************************************************************************
结构名    : MTA_TLRRC_SET_DPDT_VALUE_NTF_STRU
结构说明  : 设置天线当前DPDT Value值

  1.日    期  : 2014年04月01日
    作    者  : g00261581
    创建内容  : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulDpdtValue;
} MTA_TLRRC_SET_DPDT_VALUE_NTF_STRU;

/*****************************************************************************
结构名    : MTA_TLRRC_QRY_DPDT_VALUE_REQ_STRU
结构说明  : 查询当前天线状态消息结构

  1.日    期  : 2014年04月01日
    作    者  : g00261581
    创建内容  : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserved[4];
} MTA_TLRRC_QRY_DPDT_VALUE_REQ_STRU;

/*****************************************************************************
结构名    : TLRRC_MTA_QRY_DPDT_VALUE_CNF_STRU
结构说明  : 查询响应结果，显示当前天线DPDT Value值

  1.日    期  : 2014年04月01日
    作    者  : g00261581
    创建内容  : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulDpdtValue;
    MTA_RRC_RESULT_ENUM_UINT32          enResult;
} TLRRC_MTA_QRY_DPDT_VALUE_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_RRC_JAM_DETECT_REQ_STRU
 结构说明  : MTA发给RRC的JAM检测的请求

  1.日    期   : 2014年4月25日
    作    者   : y00142674
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    MTA_RRC_JAM_MODE_ENUM_UINT8         enMode;                                 /* JAM设置的模式 */
    VOS_UINT8                           ucMethod;                               /* JAM使用的方法，取值范围[0,1]*/
    VOS_UINT8                           ucThreshold;                            /* 检测需要达到的频点测量值，取值范围:[0,30] */
    VOS_UINT8                           ucFreqNum;                              /* 检测需要达到的频点个数，取值范围:[0,255] */
} MTA_RRC_JAM_DETECT_REQ_STRU;
/*****************************************************************************
 结构名    : MTA_WRR_JAM_DETECT_REQ_STRU
 结构说明  : MTA发给WAS的JAM检测的请求

  1.日    期   : 2015年2月17日
    作    者   : y00142674
    修改内容   : 创建

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    MTA_RRC_JAM_MODE_ENUM_UINT8         enMode;                                 /* JAM设置的模式 */
    VOS_UINT8                           ucMethod;                               /* JAM使用的方法，取值范围[0,1]*/
    VOS_UINT8                           ucRssiSrhThreshold;                     /* 测量RSSI时检测需要达到的频点测量值，取值范围:[0,70]，实际用的时候减70使用 */
    VOS_UINT8                           ucRssiSrhFreqPercent;                   /* 测量RSSI时检测需要达到的频点个数占频点总数(BAND和干扰信号取交集)的百分比，取值范围:[0,100]
                                                                                   干扰带宽按照NV配置默认30M，RSSI百分比默认70%，假设BAND带宽大于30M，则频点个数需要达到(30M/3M)*70% = 7个 */
    VOS_UINT16                          usPschSrhThreshold;                     /* 测量PSCH时检测需要小于等于的频点测量值，取值范围:[0,65535] */
    VOS_UINT8                           ucPschSrhFreqPercent;                   /* 测量PSCH时检测需要达到的频点个数占频点总数(BAND和干扰信号取交集)的百分比，取值范围:[0,100]
                                                                                   干扰信号按照NV配置默认30M，RSSI百分比默认70%，PSCH百分比默认80%，
                                                                                   假设BAND带宽大于30M，则频点个数需要达到((30M*70%)/200K)*80% = 84个 */
    VOS_UINT8                           aucRsv[1];
} MTA_WRR_JAM_DETECT_REQ_STRU;
/*****************************************************************************
 结构名    : RRC_MTA_JAM_DETECT_CNF_STRU
 结构说明  : RRC发给MTA的JAM检测功能设置的回复

  1.日    期   : 2014年4月25日
    作    者   : y00142674
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    MTA_RRC_RESULT_ENUM_UINT32          enResult;                               /* JAM设置的结果 */
} RRC_MTA_JAM_DETECT_CNF_STRU;

/*****************************************************************************
 结构名    : RRC_MTA_JAM_DETECT_IND_STRU
 结构说明  : RRC发给MTA的JAM检测结果的回复

  1.日    期   : 2014年4月25日
    作    者   : y00142674
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    MTA_RRC_JAM_RESULT_ENUM_UINT8       enResult;                               /* JAM检测的结果 */
    VOS_UINT8                           aucReserved[3];
} RRC_MTA_JAM_DETECT_IND_STRU;

/*****************************************************************************
 结构名    : MTA_RRC_CHECK_FREQ_VALIDITY_REQ_STRU
 结构说明  : MTA发给各接入层，检查频点有效性的请求

  1.日    期   : 2014年6月3日
    作    者   : g00261581
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    VOS_UINT16                          usFreq;                                 /* 频点值 */
    MTA_RRC_GSM_BAND_ENUM_UINT16        enBand;                                 /* GSM模式下需要带频带 */
} MTA_RRC_CHECK_FREQ_VALIDITY_REQ_STRU;

/*****************************************************************************
 结构名    : RRC_MTA_CHECK_FREQ_VALIDITY_CNF_STRU
 结构说明  : 各接入层发给MTA的频点检测结果的回复

  1.日    期   : 2014年6月3日
    作    者   : g00261581
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    MTA_RRC_RESULT_ENUM_UINT32          enResult;                               /* MTA_RRC_RESULT_NO_ERROR:频点有效； MTA_RRC_RESULT_ERROR:频点无效*/
} RRC_MTA_CHECK_FREQ_VALIDITY_CNF_STRU;
/*****************************************************************************
 结构名    : MTA_GRR_FREQLOCK_SET_REQ_STRU
 结构说明  : MTA给GAS下发锁频消息结构

  1.日    期   : 2014年07月28日
    作    者   : y00142674
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    PS_BOOL_ENUM_UINT8                  enLockFlg;                              /* PS_TRUE:锁定，PS_FALSE:去锁定 */
    VOS_UINT8                           aucReserved[3];                         /* 保留位 */
    VOS_UINT16                          usFreq;                                 /* 频点值 */
    MTA_RRC_GSM_BAND_ENUM_UINT16        enBand;                                 /* GSM频段 */
} MTA_GRR_FREQLOCK_SET_REQ_STRU;

/*****************************************************************************
 结构名    : GRR_MTA_FREQLOCK_SET_CNF_STRU
 结构说明  : GAS给MTA回的锁频设置结果

  1.日    期   : 2014年07月28日
    作    者   : y00142674
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    MTA_RRC_RESULT_ENUM_UINT32          enResult;                               /* MTA_RRC_RESULT_NO_ERROR:锁频成功； MTA_RRC_RESULT_ERROR:锁频失败*/
} GRR_MTA_FREQLOCK_SET_CNF_STRU;


/*****************************************************************************
 结构名    : MTA_RRC_PLMN_FREQ_QRY_REQ_STRU
 结构说明  : MTA发给RRC的频点查询请求

  1.日    期   : 2015年07月07日
    作    者   : y00142674
    修改内容   : 创建, for 云端频点收集
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    MTA_RRC_FREQ_QRY_TYPE_UINT8         enQueryType;                            /* 查询类型 */
    VOS_UINT8                           aucRsv[2];                              /* 保留位 */
    VOS_UINT8                           ucPlmnIdNum;                            /* 查询指定PLMN的个数，仅在enPlmnCheckFlag为TRUE时使用 */
    MTA_RRC_PLMN_ID_STRU                astPlmnIdList[MTA_RRC_MAX_PLMN_NUM];    /* PLMN的列表，仅在enPlmnCheckFlag为TRUE时使用 */
} MTA_RRC_PLMN_FREQ_QRY_REQ_STRU;

/*****************************************************************************
 结构名    : RRC_MTA_FREQ_INFO_STRU
 结构说明  : RRC发给MTA的频点信息

  1.日    期   : 2015年07月07日
    作    者   : y00142674
    修改内容   : 创建, for 云端频点收集
*****************************************************************************/
typedef struct
{
    RRC_MTA_BAND_IND_ENUM_UINT16        enBandInd;                              /* 频段指示 */
    VOS_UINT16                          usFreq;                                 /* 频点信息 */
}RRC_MTA_FREQ_INFO_STRU;

/*****************************************************************************
 结构名    : RRC_MTA_LTE_FREQ_INFO_STRU
 结构说明  : LRRC发给MTA的频点信息

  1.日    期   : 2015年07月07日
    作    者   : y00142674
    修改内容   : 创建, for 云端频点收集
*****************************************************************************/
typedef struct
{
    RRC_MTA_BAND_IND_ENUM_UINT16        enBandInd;                              /* 频段指示 */
    VOS_UINT8                           aucRsv[2];                              /* 保留位 */
    VOS_UINT32                          ulFreq;                                 /* 频点信息 */
}RRC_MTA_LTE_FREQ_INFO_STRU;

/*****************************************************************************
 结构名    : RRC_MTA_GSM_FREQ_LIST_STRU
 结构说明  : RRC发给MTA的GSM频点列表

  1.日    期   : 2015年07月07日
    作    者   : y00142674
    修改内容   : 创建, for 云端频点收集
*****************************************************************************/
typedef struct
{
    MTA_RRC_PLMN_ID_STRU                stPlmnId;                               /* 查询到的PLMN */
    VOS_UINT16                          usFreqNum;                              /* 频点数目 */
    VOS_UINT8                           aucRsv[2];                              /* 保留位 */
    RRC_MTA_FREQ_INFO_STRU              astFreqList[RRC_MTA_MAX_GSM_FREQ_NUM];  /* 频点列表 */
}RRC_MTA_GSM_FREQ_LIST_STRU;

/*****************************************************************************
 结构名    : RRC_MTA_WCDMA_FREQ_LIST_STRU
 结构说明  : RRC发给MTA的WCDMA频点列表

  1.日    期   : 2015年07月07日
    作    者   : y00142674
    修改内容   : 创建, for 云端频点收集
*****************************************************************************/
typedef struct
{
    MTA_RRC_PLMN_ID_STRU                stPlmnId;                               /* 查询到的PLMN */
    VOS_UINT16                          usFreqNum;                              /* 频点数目 */
    VOS_UINT8                           aucRsv[2];                              /* 保留位 */
    RRC_MTA_FREQ_INFO_STRU              astFreqList[RRC_MTA_MAX_WCDMA_FREQ_NUM];  /* 频点列表 */
}RRC_MTA_WCDMA_FREQ_LIST_STRU;

/*****************************************************************************
 结构名    : RRC_MTA_LTE_FREQ_LIST_STRU
 结构说明  : RRC发给MTA的LTE频点列表

  1.日    期   : 2015年07月07日
    作    者   : y00142674
    修改内容   : 创建, for 云端频点收集
*****************************************************************************/
typedef struct
{
    MTA_RRC_PLMN_ID_STRU                stPlmnId;                               /* 查询到的PLMN */
    VOS_UINT16                          usFreqNum;                              /* 频点数目 */
    VOS_UINT8                           aucRsv[2];                              /* 保留位 */
    RRC_MTA_LTE_FREQ_INFO_STRU          astFreqList[RRC_MTA_MAX_LTE_FREQ_NUM];  /* 频点列表 */
}RRC_MTA_LTE_FREQ_LIST_STRU;

/*****************************************************************************
 结构名    : RRC_MTA_GSM_PLMN_FREQ_LIST_STRU
 结构说明  : GSM发给MTA的频点查询结果

  1.日    期   : 2015年07月07日
    作    者   : y00142674
    修改内容   : 创建, for 云端频点收集
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPlmnNum;                              /* 查询到的PLMN的个数 */
    VOS_UINT8                           aucRsv[3];                              /* 保留位 */
    RRC_MTA_GSM_FREQ_LIST_STRU          astPlmnFreqList[RRC_MTA_MAX_GSM_PLMN_NUM];  /* 查询到的频点列表 */
} RRC_MTA_GSM_PLMN_FREQ_LIST_STRU;

/*****************************************************************************
 结构名    : RRC_MTA_WCDMA_PLMN_FREQ_LIST_STRU
 结构说明  : WCDMA发给MTA的频点查询结果

  1.日    期   : 2015年07月07日
    作    者   : y00142674
    修改内容   : 创建, for 云端频点收集
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPlmnNum;                              /* 查询到的PLMN的个数 */
    VOS_UINT8                           aucRsv[3];                              /* 保留位 */
    RRC_MTA_WCDMA_FREQ_LIST_STRU        astPlmnFreqList[RRC_MTA_MAX_WCDMA_PLMN_NUM];  /* 查询到的频点列表 */
} RRC_MTA_WCDMA_PLMN_FREQ_LIST_STRU;

/*****************************************************************************
 结构名    : RRC_MTA_LTE_PLMN_FREQ_LIST_STRU
 结构说明  : LTE发给MTA的频点查询结果

  1.日    期   : 2015年07月07日
    作    者   : y00142674
    修改内容   : 创建, for 云端频点收集
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPlmnNum;                              /* 查询到的PLMN的个数 */
    VOS_UINT8                           aucRsv[3];                              /* 保留位 */
    RRC_MTA_LTE_FREQ_LIST_STRU          astPlmnFreqList[RRC_MTA_MAX_LTE_PLMN_NUM];  /* 查询到的频点列表 */
} RRC_MTA_LTE_PLMN_FREQ_LIST_STRU;


/*****************************************************************************
 结构名    : RRC_MTA_PLMN_FREQ_QRY_CNF_STRU
 结构说明  : RRC发给MTA的频点查询结果，区分不同模式

  1.日    期   : 2015年07月07日
    作    者   : y00142674
    修改内容   : 创建, for 云端频点收集
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    VOS_RATMODE_ENUM_UINT32             enRatType;                              /* 模式类型 *//* _H2ASN_Replace VOS_UINT32 enRatType; */
    union
    {
        RRC_MTA_GSM_PLMN_FREQ_LIST_STRU     stGsmFreqList;                      /* GSM的频点列表 */
        RRC_MTA_WCDMA_PLMN_FREQ_LIST_STRU   stWcdmaFreqList;                    /* WCDMA的频点列表 */
        RRC_MTA_LTE_PLMN_FREQ_LIST_STRU     stLteFreqList;                      /* LTE的频点列表 */
    }u;
} RRC_MTA_PLMN_FREQ_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_TDS_FREQLOCK_SET_REQ_STRU
 结构说明  : MTA给TDS下发的锁频消息结构

  1.日    期   : 2014年10月21日
    作    者   : z00214637
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    PS_BOOL_ENUM_UINT8                  enLockFlg;                              /* PS_TRUE:锁定，PS_FALSE:去锁定 */
    MTA_RRC_FREQLOCK_TYPE_ENUM_UINT8    ucFreqType;                             /* 1: 锁频,2:频点+扰码 */
    VOS_UINT16                          usFreq;                                 /* 频点值 */
    VOS_UINT32                          ulSc;                                   /* 扰码 */
} MTA_TDS_FREQLOCK_SET_REQ_STRU;

/*****************************************************************************
 结构名    : TDS_MTA_FREQLOCK_SET_CNF_STRU
 结构说明  : TDS给MTA回的锁频设置结果

  1.日    期   : 2014年10月21日
    作    者   : z00214637
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                                    /*_H2ASN_Skip*/
    MTA_RRC_RESULT_ENUM_UINT32          enResult;                                       /* MTA_RRC_RESULT_NO_ERROR:锁频成功；MTA_RRC_RESULT_RRC:锁频失败 */
} TDS_MTA_FREQLOCK_SET_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_LRRC_CLEAR_HISTORY_FREQ_REQ_STRU
 结构说明  : MTA给LTE AS下发清除历史频点消息结构

  1.日    期   : 2015年9月11日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;               /*_H2ASN_Skip*/
    MTA_LRRC_CLEAR_HISTORY_FREQ_TYPE_ENUM_UINT8             enClearHistoryFreqType;
    VOS_UINT8                                               aucReserved[3];
} MTA_LRRC_CLEAR_HISTORY_FREQ_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_MTA_CLEAR_HISTORY_FREQ_CNF_STRU
 结构说明  : LRRC给MTA回复清除历史频点消息结构

  1.日    期   : 2015年9月11日
     作    者   : z00161729
     修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                  /*_H2ASN_Skip*/
    MTA_RRC_RESULT_ENUM_UINT32          enResult;
} LRRC_MTA_CLEAR_HISTORY_FREQ_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_TDRR_FREQLOCK_SET_REQ_STRU
 结构说明  : MTA给LTE AS下发的锁频消息结构

  1.日    期   : 2014年10月21日
    作    者   : z00214637
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    PS_BOOL_ENUM_UINT8                  enLockFlg;                              /* PS_TRUE:锁定，PS_FALSE:去锁定 */
    MTA_RRC_FREQLOCK_TYPE_ENUM_UINT8    ucFreqType;                             /* 1: 锁频,2:频点+物理小区ID */
    VOS_UINT16                          usFreq;                                 /* 频点值 */
    VOS_UINT32                          ulPhyCellId;                            /* 物理小区ID */
} MTA_LRRC_FREQLOCK_SET_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_MTA_FREQLOCK_SET_CNF_STRU
 结构说明  : LRRC给MTA回的锁频设置结果

  1.日    期   : 2014年10月21日
    作    者   : z00214637
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                  /*_H2ASN_Skip*/
    MTA_RRC_RESULT_ENUM_UINT32          enResult;                     /* MTA_RRC_RESULT_NO_ERROR:锁频成功；MTA_RRC_RESULT_RRC:锁频失败 */
} LRRC_MTA_FREQLOCK_SET_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_LRRC_MBMS_SERVICE_OPTION_REQ_STRU
 结构说明  : MTA通知LRRC MBMS服务特性操作请求结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                            /*_H2ASN_Skip*/
    MBMS_SERVICE_OP_ENUM_UINT8          enOption;                               /* 0:去使能，1:使能 */
    VOS_UINT8                           aucReserved[3];                         /* 保留位 */
} MTA_LRRC_MBMS_SERVICE_OPTION_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_MTA_MBMS_SERVICE_OPTION_CNF_STRU
 结构说明  : LRRC回复MTA MBMS服务特性操作结果结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                            /*_H2ASN_Skip*/
    MTA_RRC_RESULT_ENUM_UINT32          enResult;                               /* 操作结果 */
} LRRC_MTA_MBMS_SERVICE_OPTION_CNF_STRU;

/*****************************************************************************
 结构名    : MBMS_TMGI_STRU
 结构说明  : TMGI结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMbmsSerId;                            /* Service ID */
    MTA_RRC_PLMN_ID_STRU                stPlmnId;                               /* PLMN ID */
} MBMS_TMGI_STRU;

/*****************************************************************************
 结构名    : MTA_LRRC_MBMS_SERVICE_STATE_SET_REQ_STRU
 结构说明  : MTA通知LRRC MBMS服务状态设置请求结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                            /*_H2ASN_Skip*/
    MBMS_SERVICE_STATE_SET_ENUM_UINT8   enStateSet;                             /* 状态设置 */
    VOS_UINT8                           aucReserved[3];                         /* 保留位 */
    VOS_UINT32                          ulAreaId;                               /* Area ID */
    MBMS_TMGI_STRU                      stTMGI;                                 /* TMGI */
} MTA_LRRC_MBMS_SERVICE_STATE_SET_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_MTA_MBMS_SERVICE_STATE_SET_CNF_STRU
 结构说明  : LRRC回复MTA MBMS服务状态设置结果结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                            /*_H2ASN_Skip*/
    MTA_RRC_RESULT_ENUM_UINT32          enResult;                               /* 状态设置结果 */
} LRRC_MTA_MBMS_SERVICE_STATE_SET_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_LRRC_MBMS_AVL_SERVICE_LIST_QRY_REQ_STRU
 结构说明  : MTA通知LRRC MBMS可用服务列表查询请求结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                            /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserved[4];                         /* 保留位 */
} MTA_LRRC_MBMS_AVL_SERVICE_LIST_QRY_REQ_STRU;

/*****************************************************************************
 结构名    : MTA_LRRC_MBMS_AVL_SERVICE_STRU
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
    MBMS_TMGI_STRU                      stTMGI;                                 /* TMGI */
    VOS_UINT32                          ulSessionId;                            /* Session ID */
} MTA_LRRC_MBMS_AVL_SERVICE_STRU;

/*****************************************************************************
 结构名    : LRRC_MTA_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU
 结构说明  : LRRC回复MTA MBMS可用服务列表查询结果结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                                /*_H2ASN_Skip*/
    MTA_RRC_RESULT_ENUM_UINT32          enResult;                                   /* 状态设置结果 */
    VOS_UINT32                          ulAvlServiceNum;                            /* 可用服务数,0:表示没有可用服务 */
    MTA_LRRC_MBMS_AVL_SERVICE_STRU      astAvlServices[MBMS_AVL_SERVICE_MAX_NUM];   /* 可用服务列表 */
} LRRC_MTA_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_LRRC_MBMS_PREFERENCE_SET_REQ_STRU
 结构说明  : MTA通知LRRC MBMS广播模式请求结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                            /*_H2ASN_Skip*/
    MBMS_CAST_MODE_ENUM_UINT8           enCastMode;                             /* 0:单播,1:组播 */
    VOS_UINT8                           aucReserved[3];                         /* 保留位 */
} MTA_LRRC_MBMS_PREFERENCE_SET_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_MTA_MBMS_PREFERENCE_SET_CNF_STRU
 结构说明  : LRRC回复MTA MBMS广播模式设置结果结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                                /*_H2ASN_Skip*/
    MTA_RRC_RESULT_ENUM_UINT32          enResult;                                   /* 广播模式设置结果 */
} LRRC_MTA_MBMS_PREFERENCE_SET_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_LRRC_SIB16_NETWORK_TIME_QRY_REQ_STRU
 结构说明  : MTA通知LRRC SIB16网络时间的查询请求结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                            /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserved[4];                         /* 保留位 */
} MTA_LRRC_SIB16_NETWORK_TIME_QRY_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_MTA_SIB16_NETWORK_TIME_QRY_CNF_STRU
 结构说明  : LRRC回复MTA SIB16网络时间的查询结果结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                                /*_H2ASN_Skip*/
    MTA_RRC_RESULT_ENUM_UINT32          enResult;                                   /* 查询操作结果 */
    VOS_UINT32                          ulReserved;                                 /* 保留位 */
    VOS_UINT64                          ullUTC;                                     /* (0..549755813887) */
} LRRC_MTA_SIB16_NETWORK_TIME_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_LRRC_BSSI_SIGNAL_LEVEL_QRY_REQ_STRU
 结构说明  : MTA通知LRRC BSSI信号强度查询请求结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                            /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserved[4];                         /* 保留位 */
} MTA_LRRC_BSSI_SIGNAL_LEVEL_QRY_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_MTA_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU
 结构说明  : LRRC回复MTA BSSI信号强度查询结果结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                            /*_H2ASN_Skip*/
    MTA_RRC_RESULT_ENUM_UINT32          enResult;                               /* 查询操作结果 */
    VOS_UINT8                           ucBSSILevel;                            /* BSSI信号强度,0xFF:表示BSSI信号强度无效 */
    VOS_UINT8                           aucReserved[3];                         /* 保留位 */
} LRRC_MTA_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_LRRC_NETWORK_INFO_QRY_REQ_STRU
 结构说明  : MTA通知LRRC 查询网络信息请求结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                            /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserved[4];                         /* 保留位 */
} MTA_LRRC_NETWORK_INFO_QRY_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_MTA_NETWORK_INFO_QRY_CNF_STRU
 结构说明  : LRRC回复MTA网络信息查询结果结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                            /*_H2ASN_Skip*/
    MTA_RRC_RESULT_ENUM_UINT32          enResult;                               /* 查询操作结果，如果没有网络信息，结果也设置为失败 */
    VOS_UINT32                          ulCellId;                               /* 小区ID */
} LRRC_MTA_NETWORK_INFO_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_LRRC_EMBMS_STATUS_QRY_REQ_STRU
 结构说明  : MTA通知LRRC 查询eMBMS功能状态请求结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                            /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserved[4];                         /* 保留位 */
} MTA_LRRC_EMBMS_STATUS_QRY_REQ_STRU;


/*****************************************************************************
 结构名    : LRRC_MTA_EMBMS_STATUS_QRY_CNF_STRU
 结构说明  : LRRC回复MTA eMBMS功能状态结果结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                            /*_H2ASN_Skip*/
    MTA_RRC_RESULT_ENUM_UINT32          enResult;                               /* 查询操作结果 */
    MBMS_FUNTIONALITY_STATUS_ENUM_UINT8 enStatus;                               /* 功能状态 */
    VOS_UINT8                           aucReserved[3];                         /* 保留位 */
} LRRC_MTA_EMBMS_STATUS_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_LRRC_MBMS_UNSOLICITED_CFG_SET_REQ_STRU
 结构说明  : MTA通知LRRC 设置MBMS主动上报配置请求结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                            /*_H2ASN_Skip*/
    MBMS_UNSOLICITED_CFG_ENUM_UINT8     enCfg;                                  /* 0:关闭,1:打开 */
    VOS_UINT8                           aucReserved[3];                         /* 保留位 */
} MTA_LRRC_MBMS_UNSOLICITED_CFG_SET_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_MTA_MBMS_UNSOLICITED_CFG_SET_CNF_STRU
 结构说明  : LRRC回复MTA MBMS主动上报配置设置结果结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                            /*_H2ASN_Skip*/
    MTA_RRC_RESULT_ENUM_UINT32          enResult;                               /* 设置操作结果 */
} LRRC_MTA_MBMS_UNSOLICITED_CFG_SET_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_MTA_MBMS_SERVICE_EVENT_IND_STRU
 结构说明  : LRRC给MTA发送MBMS服务事件主动上报结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                            /*_H2ASN_Skip*/
    MBMS_SERVICE_EVENT_ENUM_UINT8       enEvent;                                /* 服务事件 */
    VOS_UINT8                           aucReserved[3];                         /* 保留位 */
} LRRC_MTA_MBMS_SERVICE_EVENT_IND_STRU;

/*****************************************************************************
 结构名    : MTA_LRRC_COEX_PARA_STRU
 结构说明  : LTE&WIFI共存参数结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MTA_LRRC_COEX_BW_TYPE_ENUM_UINT16           enCoexBWType;
    MTA_LRRC_COEX_CFG_ENUM_UINT16               enCfg;
    VOS_UINT16                                  usTxBegin;
    VOS_UINT16                                  usTxEnd;
    VOS_INT16                                   sTxPower;
    VOS_UINT16                                  usRxBegin;
    VOS_UINT16                                  usRxEnd;
    VOS_UINT16                                  usReserved;                 /* 保留位 */
} MTA_LRRC_COEX_PARA_STRU;

/*****************************************************************************
 结构名    : MTA_LRRC_LTE_WIFI_COEX_SET_REQ_STRU
 结构说明  : MTA通知LRRC 设置LTE&WIFI共存配置请求结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                            /*_H2ASN_Skip*/
    VOS_UINT16                          usCoexParaNum;
    VOS_UINT16                          usCoexParaSize;
    VOS_UINT8                           aucCoexPara[4];
} MTA_LRRC_LTE_WIFI_COEX_SET_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_MTA_LTE_WIFI_COEX_SET_CNF_STRU
 结构说明  : LRRC回复MTA LTE&WIFI共存配置设置结果结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                            /*_H2ASN_Skip*/
    MTA_RRC_RESULT_ENUM_UINT32          enResult;                               /* 设置结果 */
} LRRC_MTA_LTE_WIFI_COEX_SET_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_LRRC_LOW_POWER_CONSUMPTION_SET_REQ_STRU
 结构说明  : MTA通知LRRC设置低功耗请求结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                            /*_H2ASN_Skip*/
    VOS_BOOL                            bLowPowerFlg;                           /* VOS_FALSE: Normal;VOS_TRUE: Low Power Consumption */
} MTA_LRRC_LOW_POWER_CONSUMPTION_SET_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_MTA_LOW_POWER_CONSUMPTION_SET_CNF_STRU
 结构说明  : LRRC回复MTA低功耗设置结果结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                            /*_H2ASN_Skip*/
    MTA_RRC_RESULT_ENUM_UINT32          enResult;                               /* 设置操作结果 */
} LRRC_MTA_LOW_POWER_CONSUMPTION_SET_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_LRRC_INTEREST_LIST_SET_REQ_STRU
 结构说明  : MTA通知LRRC设置Interest请求结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                                    /*_H2ASN_Skip*/
    VOS_UINT32                          aulFreqList[MTA_LRRC_INTEREST_FREQ_MAX_NUM];    /* 频点列表 */
    VOS_BOOL                            bMbmsPriority;                                  /* VOS_FALSE: Normal;VOS_TRUE: Low Power Consumption */
} MTA_LRRC_INTEREST_LIST_SET_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_MTA_INTEREST_LIST_SET_CNF_STRU
 结构说明  : LRRC回复MTA Interest设置结果结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                                    /*_H2ASN_Skip*/
    MTA_RRC_RESULT_ENUM_UINT32          enResult;                                       /* 设置操作结果 */
} LRRC_MTA_INTEREST_LIST_SET_CNF_STRU;
/*******************************************************************************
 结构名    : MTA_LRRC_SET_FR_REQ_STRU
 结构说明  : 发给LRRC设置FR请求
 1.日    期   : 2015年05月25日
   作    者   : z00301431
   修改内容   : FR动态控制添加
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;                    /*_H2ASN_Skip*/

    PS_BOOL_ENUM_UINT8                          enActFrFlag;                    /* 激活FR标志，0:不激活  1:激活 */
    VOS_UINT8                                   aucRsv[3];                      /* 保留位 */
}MTA_LRRC_SET_FR_REQ_STRU;

/*******************************************************************************
 结构名    : LRRC_MTA_SET_FR_CNF_STRU
 结构说明  : LRRC回复的FR设置响应
 1.日    期   : 2015年05月25日
   作    者   : z00301431
   修改内容   : FR动态控制添加
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;                    /*_H2ASN_Skip*/

    MTA_RRC_RESULT_ENUM_UINT32                  enRslt;                         /* FR设置及结果 */
}LRRC_MTA_SET_FR_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_LRRC_TRANSMODE_QRY_REQ_STRU
 结构说明  : MTA向LRRC查询传输模式请求ID_MTA_LRRC_TRANSMODE_QRY_REQ结构体

  1.日    期   : 2015年7月30日
    作    者   : lwx277467
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                            /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserved[4];                         /* 保留位 */
} MTA_LRRC_TRANSMODE_QRY_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_MTA_TRANSMODE_QRY_CNF_STRU
 结构说明  : LRR回复MTA传输模式查询结果ID_LRRC_MTA_TRANSMODE_QRY_CNF结构体

  1.日    期   : 2015年7月30日
    作    者   : lwx277467
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    PS_MSG_HEADER_STRU                  stMsgHeader;                            /*_H2ASN_Skip*/
    MTA_RRC_RESULT_ENUM_UINT32          enResult;                               /*查询操作结果*/
    VOS_UINT8                           ucTransMode;                            /*传输模式*/
    VOS_UINT8                           aucReserved[3];                         /* 保留位 */
} LRRC_MTA_TRANSMODE_QRY_CNF_STRU;

/************无线发射功率tx power (4G) begin*********************************/
/*****************************************************************************
 结构名    : TX_PWR_INFO_STRU
 结构说明  : TXPower 内容结构体

  1.日    期   : 2015年5月21日
    作    者   : l00277962
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_INT16     sPuschPwr;
    VOS_INT16     sPucchPwr;
    VOS_INT16     sSrsPwr;
    VOS_INT16     sPrachPwr;
}TX_PWR_INFO_STRU;
/*****************************************************************************
 结构名    : MTA_LRRC_TX_PWR_QRY_REQ
 结构说明  : MTA向LRRC查询TXPower

  1.日    期   : 2015年5月21日
    作    者   : l00277962
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    VOS_UINT8                           aucReserved[4];
}MTA_LRRC_TX_PWR_QRY_REQ;
/*****************************************************************************
 结构名    : TX_PWR_INFO_STRU
 结构说明  : LRRC向MTA回复TXPower

  1.日    期   : 2015年5月21日
    作    者   : l00277962
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    MTA_RRC_RESULT_ENUM_UINT32          enResult;
    TX_PWR_INFO_STRU                    stTxPwrInfo;
}LRRC_MTA_TX_PWR_QRY_CNF;
/************无线发射功率tx power (4G) end***********************************/

/************MCS 上下行调制解调方式 *****************************************/
/*****************************************************************************
 结构名    : TX_PWR_INFO_STRU
 结构说明  : MCS 内容结构体

  1.日    期   : 2015年5月21日
    作    者   : l00277962
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16     usUlMcs;
    VOS_UINT16     usDlMcs[2];
    VOS_UINT8      aucReserved[2];
}MCS_INFO_STRU;
/*****************************************************************************
 结构名    : TX_PWR_INFO_STRU
 结构说明  : MTA向LRRC查询MCS

  1.日    期   : 2015年5月21日
    作    者   : l00277962
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    VOS_UINT8                           aucReserved[4];
}MTA_LRRC_MCS_QRY_REQ;
/*****************************************************************************
 结构名    : TX_PWR_INFO_STRU
 结构说明  : LRRC向MTA回复MCS

  1.日    期   : 2015年5月21日
    作    者   : l00277962
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    MTA_RRC_RESULT_ENUM_UINT32          enResult;
    MCS_INFO_STRU                       stMCSInfo;
}LRRC_MTA_MCS_QRY_CNF;
/****************************************************************************/

/************EARFCN**********************************************************/
/*****************************************************************************
 结构名    : TX_PWR_INFO_STRU
 结构说明  : EARFCN 内容结构体

  1.日    期   : 2015年5月21日
    作    者   : l00277962
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16    usUlEarfcn;
    VOS_UINT16    usDlEarfcn;
}EARFCN_INFO_STRU;
/*****************************************************************************
 结构名    : TX_PWR_INFO_STRU
 结构说明  : MTA向LRRC查询EARFCN

  1.日    期   : 2015年5月21日
    作    者   : l00277962
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    VOS_UINT8                           aucReserved[4];
}MTA_LRRC_EARFCN_QRY_REQ;
/*****************************************************************************
 结构名    : TX_PWR_INFO_STRU
 结构说明  : LRRC向MTA回复EARFCN

  1.日    期   : 2015年5月21日
    作    者   : l00277962
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    MTA_RRC_RESULT_ENUM_UINT32          enResult;
    EARFCN_INFO_STRU                    stEarfcnInfo;
}LRRC_MTA_EARFCN_QRY_CNF;
/****************************************************************************/

/************TDD时隙配比*****************************************************/
/*****************************************************************************
 结构名    : TX_PWR_INFO_STRU
 结构说明  : TDD时隙配比内容结构体

  1.日    期   : 2015年5月21日
    作    者   : l00277962
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucSubframeAssign;
    VOS_UINT8   ucSubframePatterns;
}LFRAMERATIO_INFO_STRU;
/*****************************************************************************
 结构名    : TX_PWR_INFO_STRU
 结构说明  : MTA向LRRC查询TDD时隙配比

  1.日    期   : 2015年5月21日
    作    者   : l00277962
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    VOS_UINT8                           aucReserved[4];
}MTA_LRRC_LFRAMERATIO_QRY_REQ;
/*****************************************************************************
 结构名    : TX_PWR_INFO_STRU
 结构说明  : LRRC向MTA回复TDD时隙配比

  1.日    期   : 2015年5月21日
    作    者   : l00277962
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    MTA_RRC_RESULT_ENUM_UINT32          enResult;
    LFRAMERATIO_INFO_STRU               stTddConfig;
}LRRC_MTA_LFRAMERATIO_QRY_CNF;
/****************************************************************************/

/************RRC status******************************************************/
/*****************************************************************************
 结构名    : TX_PWR_INFO_STRU
 结构说明  : MTA向LRRC查询RRC status

  1.日    期   : 2015年5月21日
    作    者   : l00277962
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    VOS_UINT8                           aucReserved[4];
}MTA_LRRC_RRC_STATUS_QRY_REQ;
/*****************************************************************************
 结构名    : TX_PWR_INFO_STRU
 结构说明  : LRRC向MTA回复RRC status

  1.日    期   : 2015年5月21日
    作    者   : l00277962
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    MTA_RRC_RESULT_ENUM_UINT32          enResult;
    VOS_UINT8                           ulRRCStatus;
}LRRC_MTA_RRC_STATUS_QRY_CNF;
/****************************************************************************/

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
    MTA_RRC_MSG_TYPE_ENUM_UINT32        enMsgID;                                /*_H2ASN_MsgChoice_Export MTA_RRC_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MTA_RRC_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}MTA_RRC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    MTA_RRC_MSG_DATA                    stMsgData;
}MtaRrcInterface_MSG;

/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
extern VOS_UINT32 CAS_GetpEsnByMeid(VOS_UINT8 *pucMeid, VOS_UINT32 *pulEsn);
#endif

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

#endif /* end of MtaRrcInterface.h */

