/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasRrcInterface.h
  版 本 号   : 继承Hi4121的基础，根据编程规范进行调整，
               枚举的定义由于历史原因，不用en开头，继承原先的代码。
  作    者   : Jinying
  生成日期   : 2006年10月28日
  最近修改   :
  功能描述   : NasRrcInterface.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2006年10月28日
    作    者   : Jinying
    修改内容   : 创建文件
  2.日    期   : 2007年9月27日
    作    者   : s46746
    修改内容   : 将卡无效信息从RRMM_NAS_INFO_CHANGE消息中拿掉
  3.日    期   : 2007年11月16日
    作    者   : l00107747
    修改内容   : 根据问题单号A32D13483
  4.日    期   : 2007年12月04日
    作    者   : s46746
    修改内容   : 1.GMM模块进行ATTACH和RAU时，如果此时接入层进行临区任务，
                   会导致LLC将ATTACH和RAU延迟发送，使得ATTACH和RAU时间过长；
                 2.GMM在进行RAU请求时，如果DRX参数不改变，将不会在消息中
                   带DRX参数，这样跨SGSN的RAU时，可能导致网侧不识别UE的DR
                   X参数，使得RAU不能成功。
  5.日    期   : 2007年12月28日
    作    者   : l00107747
    修改内容   : 根据问题单号A32D13986,修改AT_MsgInd接口，Cell ID为U32类型,
                 来源于SIB3/4
  6.日    期   : 2008年4月9日
    作    者   : s46746
    修改内容   : 根据问题单号AT2D02970,NAS B010版本新增需求实现，对RRMM_SYS_INFO_IND
                 和RRMM_SYNC_IND,GRR_SYNC_IND接口修改
  7.日    期   : 2008年11月26日
    作    者   : o00132663
    修改内容   : AT2D07078, 增加^RSSI主动上报
  8.日    期   : 2009年02月05日
    作    者   : l00130025
    修改内容   : 问题单号:AT2D07529,AT2D07611,AT2D08749,W搜网优化NAS修改
  9.日    期   : 2009年03月19日
    作    者   : l00130025
    修改内容   : 问题单号：AT2D09743/AT2D10328,WAS的 D/F/P态下丢网处理
  10.日    期   : 2009年04月27日
    作    者   : l65478
    修改内容   : 问题单号：AT2D11554,出服务区优化
  11.日    期  : 2010年05月11日
    作    者   : s46746
    修改内容   : 问题单号：DTS2011042004956,提供接入层获取EHPLMN列表接口，删除获取HPLMN接口
 12.日    期   : 2011年04月23日
    作    者   : L00171473
    修改内容   : for V7R1 porting, 去掉枚举成员最后的逗号，避免编译WARNING
 ******************************************************************************/

#ifndef __NASRRCINTERFACE_H__
#define __NASRRCINTERFACE_H__



/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "WUe.h"
#include "PsTypeDef.h"


#include "ComInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define RRC_MAX_FORBLA_NUM              (32)                /* 禁止注册区的最大的个数 */
#define RRC_MAX_HIGH_PLMN_NUM           (48)                /* 高质量的PLMN的最大个数 */
#define RRC_MAX_LOW_PLMN_NUM            (48)                /* 低质量的PLMN的最大个数 */
#define RRC_MAX_EQUPLMN_NUM             (16)                /* 等效PLMN的最大个数     */
#define RRC_MAX_PLMN_NUM                (RRC_MAX_HIGH_PLMN_NUM + RRC_MAX_LOW_PLMN_NUM)
                                                            /* PLMN的最大个数 */
#define RRC_NAS_MAX_RAB_SETUP           (16)                /* 建立的最大RAB数        */
#define RRC_NAS_MAX_RB_PER_RAB          (8)                 /* 每个RAB包含的最大RB数  */
#define RRC_NAS_MAX_CN_DOMAIN           (2)                 /* 最大CN域数目           */
#define RRC_NAS_MAX_SIZE_NAS_GSM_MAP    (8)                 /* 协议值 : 8             */
#define RRC_NAS_MAX_SIZE_NAS_MSG        (256)               /* NAS消息最大长度        */
#define RRC_NAS_CIPHER_KEY_LEN          (16)                /* 加密密钥长度 */
#define RRC_NAS_INTEGRITY_KEY_LEN       (16)                /* 完整性保护密钥长度 */
#define RR_NAS_KC_LEN                   (8)                 /* RR加密密钥长度 */
#define RRC_NAS_TMSI_LEN                (4)                 /* TMSI长度 */
#define RRC_NAS_PTMSI_LEN               (4)                 /* PTMSI长度 */
#define RRC_NAS_IMSI_MAX_LEN            (8)                 /* IMSI最大长度 */
#define RRC_NAS_AT_CELL_MAX_NUM         (8)                 /* 小区ID结构体 */
#define RRC_NAS_AT_MAX_TRCH             (8)                 /* 信道扰码结构体 */
#define RRC_CELL_INFO_MAX_NUM           (8)
#define RRMM_UE_RFPOWER_INVALID         (0x1fff)            /* 无效值 */
#define RRC_NAS_MAX_AMR_RATE_NUM        (10)                /* AMR速率最大个数 */
#define NAS_RRC_MAX_RE_TX_MSG_LENTH     (320)               /* RRMM_EST_REQ_STRU或者RRMM_DATA_REQ_STRU的最大长度 */
#define NAS_RRC_MAX_RE_TX_MSG_NUM       (2)                 /* 最多重发的DT消息个数 */
#define RRC_NAS_INTER_RAT_HANDOVER_INFO_LEN                (250)  /* INTER_RAT_HANDOVER_INFO 长度,最长250字节 */

#define MS_RADIO_ACCESS_CAPABILITY_MIN_SIZE                (6)    /* RAC消息最小长度 */
#define MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE                (52)   /* RAC消息最大长度 */

#define NAS_RRC_MAX_BG_SRCH_PLMN_NUM    (16)                /* BG搜索失败后，上报的最大的PLMN个数 */
#define NAS_RRC_MAX_AVAILPLMN_NUM       (18)                /* RRMM_PLMN_QUERY_CNF结果中可用网络信息的最大个数:HPLMN+EPLMN */
#define RRC_NAS_MEASURE_INVALID_VALUE   (0x5A5A)            /* 通过AT查询测量值，无法获取测量值时上报无效值 */

#define NAS_RRC_MAX_EHPLMN_NUM          (32)                /* 支持的最大EHPLMN个数 */

#define NAS_RRC_MAX_RAT_NUM                             (3)                     /* 当前支持的接入技术个数 */

#define RRC_NAS_NET_SCAN_MAX_FREQ_NUM   (20)

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-13, begin */
#define MS_CLASSMARK2_MAX_LEN                              (4)                  /* R6协议中Classmark2最大长度 */
#define MS_CLASSMARK3_MAX_LEN                              (32)                 /* R8协议中Classmark3最大长度 */
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-13, end */

#define RRC_NAS_NET_SCAN_MAX_FREQ_NUM   (20)

#define RRC_NAS_TDS_ARFCN_MAX_NUM           (9)                                 /* TDS频点列表最大个数 */

#define  RRMM_TDS_ARFCN_MAX_NUM                          (9)                    /* TDS频点列表最大个数，用于GAS根据邻区结构给MTC上报频点信息 */
#define  RRMM_LTE_ARFCN_MAX_NUM                          (8)                    /* LTE频点列表最大个数，用于GAS根据邻区结构给MTC上报频点信息 */
#define  RRMM_GSM_MAX_USING_ARFCN_NUM                    (7)                    /* GSM频点列表最大个数 */
#define  RRMM_GSM_MA_ARFCN_MAX_NUM                       (64)                   /* GSM跳频频点列表最大个数 */
#define  RRMM_WCDMA_MAX_USING_ARFCN_NUM                  (4)                    /* WCDMA频点列表最大个数 */
#define  NAS_SMS_PD                                      (0x09)
#define  NAS_PD_MASK                                     (0x0F)

#define RRC_NAS_MAX_PLMN_CSG_ID_NUM             (35)
#define RRC_NAS_MAX_HOME_NODEB_NAME_LEN         (48)
/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : NAS_RRC_MSG_TYPE_ENUM
 结构说明  : 原语的ulMsgName
*****************************************************************************/
enum NAS_RRC_MSG_TYPE_ENUM
{
    /* 消息名称 */                      /*消息ID*/  /* 备注 */
/* MM发给AS的原语 */
    RRMM_PLMN_SEARCH_REQ                = 0x0000,   /* _H2ASN_MsgChoice RRMM_PLMN_SEARCH_REQ_STRU */
    RRMM_EQU_PLMN_NOTIFY_REQ            = 0x0002,   /* _H2ASN_MsgChoice RRMM_EQU_PLMN_NOTIFY_REQ_STRU */
    RRMM_START_REQ                      = 0x0004,   /* _H2ASN_MsgChoice RRMM_START_REQ_STRU */
    RRMM_CELL_SELECTION_CTRL_REQ        = 0x0006,   /* _H2ASN_MsgChoice RRMM_CELL_SELECTION_CTRL_REQ_STRU */
    RRMM_EST_REQ                        = 0x0008,   /* _H2ASN_MsgChoice RRMM_EST_REQ_STRU */
    RRMM_DATA_REQ                       = 0x000A,   /* _H2ASN_MsgChoice RRMM_DATA_REQ_STRU */
    RRMM_REL_REQ                        = 0x000C,   /* _H2ASN_MsgChoice RRMM_REL_REQ_STRU */
    RRMM_NAS_INFO_CHANGE_REQ            = 0x0010,   /* _H2ASN_MsgChoice RRMM_NAS_INFO_CHANGE_REQ_STRU */
    RRRABM_RAB_RSP                      = 0x0012,   /* _H2ASN_MsgChoice RRRABM_RAB_RSP_STRU */
    RRRABM_QOS_UPDATE_REQ               = 0x0014,   /* _H2ASN_MsgChoice RRRABM_QOS_UPDATE_REQ_STRU */
    RRMM_POWER_OFF_REQ                  = 0x0016,   /* _H2ASN_MsgChoice RRMM_POWER_OFF_REQ_STRU */
    RRMM_PLMN_SEARCH_STOP_REQ           = 0x0018,   /* _H2ASN_MsgChoice RRMM_PLMN_SEARCH_STOP_REQ_ST */
    RRMM_SUSPEND_RSP                    = 0x002A,   /* _H2ASN_MsgChoice RRMM_SUSPEND_RSP_ST */
    RRMM_RESUME_RSP                     = 0x002C,   /* _H2ASN_MsgChoice RRMM_RESUME_RSP_ST */
    GRRMM_NAS_INFO_CHANGE_REQ           = 0x002E,   /* _H2ASN_MsgChoice GRRMM_NAS_INFO_CHANGE_REQ_STRU */
    GRRGMM_ASSIGN_REQ                   = 0x0030,   /* _H2ASN_MsgChoice GRRGMM_ASSIGN_REQ_ST */
    RRMM_SUSPEND_REQ                    = 0x0032,   /* _H2ASN_MsgChoice RRMM_SUSPEND_REQ_ST */
    RRMM_NAS_PARAMS_REQ                 = 0x0034,   /* _H2ASN_MsgChoice RRMM_NAS_PARAMS_REQ_ST */
    RRMM_AT_MSG_REQ                     = 0x0036,   /* _H2ASN_MsgChoice RRMM_AT_MSG_REQ_ST */
    GRRMM_EST_SAPI3_REQ                 = 0x0038,   /* _H2ASN_MsgChoice GRRMM_EST_SAPI3_REQ_ST */
    GRRMM_AT_MSG_REQ                    = 0x003A,   /* _H2ASN_MsgChoice GRRMM_AT_MSG_REQ_ST */

    RRRABM_HANDOVER_RAB_RSP             = 0x003C,   /* _H2ASN_MsgChoice RRRABM_HANDOVER_RAB_RSP_STRU */
    RRMM_UICC_STATUS_CHANGE_IND         = 0x003e,   /* _H2ASN_MsgChoice RRMM_UICC_STATUS_CHANGE_IND_ST */
    RRMM_SET_WCDMA_BAND_REQ             = 0x0042,   /* _H2ASN_MsgChoice RRMM_SET_WCDMA_BAND_REQ_ST */
    RRMM_SET_GSM_BAND_REQ               = 0x0044,   /* _H2ASN_MsgChoice RRMM_SET_GSM_BAND_REQ_ST */

    RRRABM_REL_ALL_REQ                  = 0x0046,   /* _H2ASN_MsgChoice RRRABM_REL_ALL_REQ_STRU */

    RRMM_SUSPEND_REL_REQ                = 0x0048,   /* _H2ASN_MsgChoice RRMM_SUSPEND_REL_REQ_STRU */

    RRMM_NAS_COMM_INFO_CHANGE_REQ       = 0x004A,   /* _H2ASN_MsgChoice RRMM_NAS_COMM_INFO_REQ_STRU */
    RRMM_SYS_CFG_REQ                    = 0x004C,   /* _H2ASN_MsgChoice RRMM_SYS_CFG_REQ_STRU */
    RRMM_PLMN_QUERY_CNF                 = 0x004E,   /* _H2ASN_MsgChoice RRMM_PLMN_QUERY_CNF_STRU */

    RRMM_BG_PLMN_SEARCH_REQ             = 0x0050,   /* _H2ASN_MsgChoice RRMM_BG_PLMN_SEARCH_REQ_ST */
    RRMM_BG_PLMN_STOP_REQ               = 0x0052,   /* _H2ASN_MsgChoice RRMM_BG_PLMN_STOP_REQ_ST */

    RRMM_INTER_RAT_HANDOVER_INFO_REQ    = 0x0064,   /* _H2ASN_MsgChoice RRMM_INTER_RAT_HANDOVER_INFO_REQ_STRU */
    RRMM_EPLMN_QUERY_REQ                = 0x0066,   /* _H2ASN_MsgChoice RRMM_EPLMN_QUERY_REQ_STRU */
    RRRABM_FASTDORM_START_REQ           = 0x0068,   /* _H2ASN_MsgChoice RRRABM_FASTDORM_START_REQ_STRU */
    RRRABM_FASTDORM_STOP_REQ            = 0x006A,   /* _H2ASN_MsgChoice RRRABM_FASTDORM_STOP_REQ_STRU */
    RRMM_AUTH_FAIL_NOTIFY_REQ           = 0x006C,   /* _H2ASN_MsgChoice RRMM_AUTH_FAIL_NOTIFY_REQ_STRU */
    RRMM_TRANSACTION_INFO_ENQ           = 0x006E,   /* _H2ASN_MsgChoice RRMM_TRANSACTION_INFO_ENQ_STRU */
    RRMM_UTRAN_MODE_REQ                 = 0x0070,   /* _H2ASN_MsgChoice RRMM_UTRAN_MODE_REQ_STRU */

    RRMM_NET_SCAN_REQ                   = 0x0072,   /* _H2ASN_MsgChoice RRMM_NET_SCAN_REQ_STRU */
    RRMM_NET_SCAN_STOP_REQ              = 0x0074,   /* _H2ASN_MsgChoice RRMM_NET_SCAN_STOP_REQ_STRU */

    RRMM_CSFB_SERVICE_ABORT_NOTIFY_IND  = 0x0076,   /* _H2ASN_MsgChoice RRMM_CSFB_SERVICE_ABORT_NOTIFY_IND_STRU */
    RRMM_REL_CS_PS_ALL_CONN_REQ         = 0x0078,   /* _H2ASN_MsgChoice RRMM_REL_CS_PS_ALL_CONN_REQ_STRU */

    RRMM_BEGIN_SESSION_NOTIFY           = 0x007E,   /* _H2ASN_MsgChoice RRMM_BEGIN_SESSION_NOTIFY_STRU */
    RRMM_END_SESSION_NOTIFY             = 0x0082,   /* _H2ASN_MsgChoice RRMM_END_SESSION_NOTIFY_STRU */

    RRMM_SERVICE_ABORT_NOTIFY        = 0x0080,  /* _H2ASN_MsgChoice RRMM_SERVICE_ABORT_NOTIFY_STRU */

    RRMM_GMM_PROC_NOTIFY               = 0x007A,   /* _H2ASN_MsgChoice RRMM_GMM_PROC_NOTIFY_STRU */
    RRMM_GMM_PROC_ANS                  = 0X007C,   /* _H2ASN_MsgChoice RRMM_GMM_PROC_ANS_STRU */

    RRRABM_VOICEPREFER_START_REQ       = 0x0084,   /* _H2ASN_MsgChoice RRRABM_VOICEPREFER_START_REQ_STRU */
    RRRABM_VOICEPREFER_STOP_REQ        = 0x0086,   /* _H2ASN_MsgChoice RRRABM_VOICEPREFER_STOP_REQ_STRU */

    RRMM_TRANSACTION_STATUS_NOTIFY     = 0x0088,   /* _H2ASN_MsgChoice RRMM_TRANSACTION_STATUS_NOTIFY_STRU */
    RRMM_CSG_LIST_SEARCH_REQ           = 0x008A,   /* _H2ASN_MsgChoice RRMM_CSG_LIST_SEARCH_REQ_STRU */

    /* AS发给MM的原语 */
    RRMM_PLMN_SEARCH_CNF                = 0x0001,   /* _H2ASN_MsgChoice RRMM_PLMN_SEARCH_CNF_STRU */
    RRMM_PLMN_LIST_IND                  = 0x0003,   /* _H2ASN_MsgChoice RRMM_PLMN_LIST_IND_STRU */
    RRMM_AREA_LOST_IND                  = 0x0005,   /* _H2ASN_MsgChoice RRMM_AREA_LOST_IND_STRU */
    RRMM_SYS_INFO_IND                   = 0x0007,   /* _H2ASN_MsgChoice RRMM_SYS_INFO_IND_STRU  */
    RRMM_PAGING_IND                     = 0x0009,   /* _H2ASN_MsgChoice RRMM_PAGING_IND_STRU    */
    RRMM_EST_CNF                        = 0x000B,   /* _H2ASN_MsgChoice RRMM_EST_CNF_STRU       */
    RRMM_DATA_IND                       = 0x000D,   /* _H2ASN_MsgChoice RRMM_DATA_IND_STRU      */
    RRMM_REL_IND                        = 0x000F,   /* _H2ASN_MsgChoice RRMM_REL_IND_STRU */
    RRMM_SECURITY_IND                   = 0x0011,   /* _H2ASN_MsgChoice RRMM_SECURITY_IND_STRU  */
    RRRABM_RAB_IND                      = 0x0013,   /* _H2ASN_MsgChoice RRRABM_RAB_IND_STRU     */
    RRMM_SYNC_IND                       = 0x0015,   /* _H2ASN_MsgChoice RRMM_SYNC_IND_STRU      */
    RRRABM_STATUS_IND                   = 0x0017,   /* _H2ASN_MsgChoice RRRABM_STATUS_IND_STRU  */
    RRMM_POWER_OFF_CNF                  = 0x0019,   /* _H2ASN_MsgChoice RRMM_POWER_OFF_CNF_STRU */
    RRMM_START_CNF                      = 0x001B,   /* _H2ASN_MsgChoice RRMM_START_CNF_STRU */
    RRMM_AC_INFO_CHANGE_IND             = 0x001D,   /* _H2ASN_MsgChoice RRMM_AC_INFO_CHANGE_IND_STRU   */
    RRMM_PLMN_SEARCH_STOP_CNF           = 0x001F,   /* _H2ASN_MsgChoice RRMM_PLMN_SEARCH_STOP_CNF_ST */
    GRRMM_SYS_INFO_IND                  = 0x0021,   /* _H2ASN_MsgChoice GRRMM_SYS_INFO_IND_ST */
    GRRMM_PAGING_IND                    = 0x0023,   /* _H2ASN_MsgChoice GRRMM_PAGING_IND_ST   */
    GAS_RR_SYNC_IND                     = 0x0025,   /* _H2ASN_MsgChoice GAS_RR_SYNC_IND_ST    */
    RRMM_SUSPEND_IND                    = 0x0027,   /* _H2ASN_MsgChoice RRMM_SUSPEND_IND_ST   */
    RRMM_RESUME_IND                     = 0x0029,   /* _H2ASN_MsgChoice RRMM_RESUME_IND_ST    */
    RRMM_SUSPEND_CNF                    = 0x003B,   /* _H2ASN_MsgChoice RRMM_SUSPEND_CNF_ST   */
    RRMM_GPRS_SUSPENSION_IND            = 0x003D,   /* _H2ASN_MsgChoice RRMM_GPRS_SUSPEND_IND_ST */
    GRRMM_SCELL_MEAS_IND                = 0x003F,   /* _H2ASN_MsgChoice GRRMM_SCELL_MEAS_IND_ST  */
    GRRMM_EST_SAPI3_CNF                 = 0x0041,   /* _H2ASN_MsgChoice GRRMM_EST_SAPI3_CNF_ST   */
    RRMM_GPRS_RESUME_IND                = 0x0047,   /* _H2ASN_MsgChoice RRMM_GPRS_RESUME_IND_ST  */
    RRMM_AT_MSG_IND                     = 0x0049,   /* _H2ASN_MsgChoice RRMM_AT_MSG_IND_ST       */
    RRMM_AT_MSG_CNF                     = 0x004B,   /* _H2ASN_MsgChoice RRMM_AT_MSG_CNF_ST       */

    RRRABM_HANDOVER_RAB_IND             = 0x004D,   /* _H2ASN_MsgChoice RRRABM_HANDOVER_RAB_IND_STRU */
    RRMM_UICC_STATUS_CHANGE_RSP         = 0x004F,   /* _H2ASN_MsgChoice RRMM_UICC_STATUS_CHANGE_RSP_ST */
    RRMM_SET_WCDMA_BAND_CNF             = 0x0051,   /* _H2ASN_MsgChoice RRMM_SET_WCDMA_BAND_CNF_ST */
    RRMM_SET_GSM_BAND_CNF               = 0x0053,   /* _H2ASN_MsgChoice RRMM_SET_GSM_BAND_CNF_ST */
    WRRMM_SCELL_RXLEV_IND               = 0x0055,   /* _H2ASN_MsgChoice WRRMM_SCELL_RXLEV_IND_ST */

    RRMM_SYS_CFG_CNF                    = 0x0057,   /* _H2ASN_MsgChoice RRMM_SYS_CFG_CNF_STRU */
    GAS_RR_CHAN_IND                     = 0x0059,   /* _H2ASN_MsgChoice GAS_RR_CHAN_MOD_IND_ST */
    RRMM_SUSPEND_REL_CNF                = 0x005B,   /* _H2ASN_MsgChoice RRMM_SUSPEND_REL_CNF_STRU */
    RRMM_PLMN_QUERY_REQ                 = 0x005D,   /* _H2ASN_MsgChoice RRMM_PLMN_QUERY_REQ_STRU */
    RRMM_CELL_RESELECT_IND              = 0X005F,   /* _H2ASN_MsgChoice RRMM_CELL_RESELECT_IND_ST */
    RRMM_LIMIT_SERVICE_CAMP_IND         = 0X0061,   /* _H2ASN_MsgChoice RRMM_LIMIT_SERVICE_CAMP_IND_STRU */
    GRRGMM_TBF_REL_IND                  = 0X0063,   /* _H2ASN_MsgChoice GRRGMM_TBF_REL_IND_ST */

    RRMM_BG_PLMN_SEARCH_STATUS_IND      = 0X0065,   /* _H2ASN_MsgChoice RRMM_BG_PLMN_SEARCH_STATUS_IND_ST */
    RRMM_BG_PLMN_SEARCH_CNF             = 0X0067,   /* _H2ASN_MsgChoice RRMM_BG_PLMN_SEARCH_CNF_ST */
    RRMM_BG_PLMN_STOP_CNF               = 0X0069,   /* _H2ASN_MsgChoice RRMM_BG_PLMN_STOP_CNF_ST */

    RRMM_INTER_RAT_HANDOVER_INFO_CNF    = 0x006B,   /* _H2ASN_MsgChoice RRMM_INTER_RAT_HANDOVER_INFO_CNF_STRU */

    GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND  = 0x006D,   /* _H2ASN_MsgChoice GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND_STRU */
    RRMM_NOT_CAMP_ON_IND                = 0x006F,   /* _H2ASN_MsgChoice RRMM_NOT_CAMP_ON_IND_STRU */

    RRMM_EPLMN_QUERY_CNF                = 0x0071,   /* _H2ASN_MsgChoice RRMM_EPLMN_QUERY_CNF_STRU */
    WRRMM_TBAR_EXPIRED_IND              = 0x0073,   /* _H2ASN_MsgChoice WRRMM_TBAR_EXPIRED_IND_STRU */
    GRRGMM_GPRS_ACCESS_RESULT_IND       = 0x0075,   /* _H2ASN_MsgChoice GRRGMM_GPRS_ACCESS_RESULT_IND_STRU */
    RRRABM_FASTDORM_INFO_IND            = 0x0077,   /* _H2ASN_MsgChoice RRRABM_FASTDORM_INFO_IND_STRU */
    RRRABM_FASTDORM_START_CNF           = 0x0079,   /* _H2ASN_MsgChoice RRRABM_FASTDORM_START_CNF_STRU */
    RRRABM_FASTDORM_STOP_CNF            = 0x007B,   /* _H2ASN_MsgChoice RRRABM_FASTDORM_STOP_CNF_STRU */
    RRMM_CIPHER_INFO_IND                = 0x007D,   /* _H2ASN_MsgChoice RRMM_CIPHER_INFO_IND_STRU */

    RRMM_W_AC_INFO_CHANGE_IND           = 0x007F,   /* _H2ASN_MsgChoice RRMM_W_AC_INFO_CHANGE_IND_STRU   */
    RRMM_TRANSACTION_INFO_ANS           = 0x0081,   /* _H2ASN_MsgChoice RRMM_TRANSACTION_INFO_ANS_STRU */
    /* Added by z40661 for 低功耗, 2012/03/30, begin   */
    RRMM_UE_OOC_STATUS_NOTIFY_IND       = 0x0083,   /* _H2ASN_MsgChoice RRMM_UE_OOC_STATUS_NOTIFY_IND_STRU */
    /* Added by z40661 for 低功耗, 2012/03/30, end */

    GRRMM_MS_RADIO_ACCESS_CAPABILITIES_TDS_IND = 0x0085,/* _H2ASN_MsgChoice GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND_STRU */

    RRMM_UTRAN_MODE_CNF                 = 0x0087,   /* _H2ASN_MsgChoice RRMM_UTRAN_MODE_CNF_STRU */

    /* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
    RRMM_NACK_DATA_IND                  = 0x0089,   /* _H2ASN_MsgChoice RRMM_NACK_DATA_IND_STRU */
    /* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-13, begin */
    RRMM_HANDOVER_INFO_IND              = 0x008B,   /* _H2ASN_MsgChoice RRMM_HANDOVER_INFO_IND_STRU */
    RRMM_CLASSMARK_CHANGE_IND           = 0x008D,   /* _H2ASN_MsgChoice RRMM_CLASSMARK_CHANGE_IND_STRU */
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-13, end */

    RRMM_NET_SCAN_CNF                   = 0x0091,   /* _H2ASN_MsgChoice RRMM_NET_SCAN_CNF_STRU */
    RRMM_NET_SCAN_STOP_CNF              = 0x0093,   /* _H2ASN_MsgChoice RRMM_NET_SCAN_STOP_CNF_STRU */

    RRMM_NCELL_MONITOR_IND              = 0x0095,   /* _H2ASN_MsgChoice RRC_NAS_NCELL_MONITOR_IND_STRU */
    RRMM_GMM_PROC_ENQ                   = 0x0097,   /* _H2ASN_MsgChoice RRMM_GMM_PROC_ENQ_STRU */

    /* Added by z00234330 for 搜网优化, 2014/09/30, begin */
    RRMM_SEARCHED_PLMN_INFO_IND         = 0x0099  , /* _H2ASN_MsgChoice RRMM_SEARCHED_PLMN_INFO_IND_STRU */
                                                    /*搜网过程中搜索到PLMN的信息上报*/
    /* Added by z00234330 for 搜网优化, 2014/09/30, end */

    RRMM_USING_FREQ_IND                 = 0x009B,   /* _H2ASN_MsgChoice RRMM_USING_FREQ_IND_STRU */

    RRMM_CONNECTED_LOCATION_INFO_IND    = 0x009D,   /* _H2ASN_MsgChoice RRMM_CONNECTED_LOCATION_INFO_IND_STRU */

    RRMM_LCS_STATE_IND                  = 0x009F,   /* _H2ASN_MsgChoice RRMM_LCS_STATE_IND_STRU */

    RRMM_CSG_LIST_SEARCH_CNF            = 0x00A1,   /* _H2ASN_MsgChoice RRMM_CSG_LIST_SEARCH_CNF_STRU */
    NAS_RRC_MSG_TYPE_BUTT               = 0xFFFF
};
typedef VOS_UINT16 NAS_RRC_MSG_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RRMM_CELL_RESEL_PROC_ENUM
 结构说明  : 原语的ucCellReselProc取值，小区重选过程宏定义
*****************************************************************************/
enum RRMM_CELL_RESEL_PROC_ENUM
{
    RRMM_CELL_RESEL_START           = 0,
    RRMM_CELL_RESEL_FINISH          = 1,
    RRMM_CELL_RESEL_BUTT
};
typedef VOS_UINT8 RRMM_CELL_RESEL_PROC_ENUM_UINT8;

/*****************************************************************************
 枚举名    : RRC_NAS_CN_DOMAIN_TYPE_ENUM
 结构说明  : 原语的enCnDomainId取值,CN域标识
*****************************************************************************/
enum RRC_NAS_CN_DOMAIN_TYPE_ENUM
{
    RRC_NAS_CS_DOMAIN                   = 0,
    RRC_NAS_PS_DOMAIN                   = 1,
    RRC_NAS_INVALID_DOMAIN              = 3,
    RRC_NAS_CN_DOMAIN_TYPE_BUTT
};
typedef VOS_UINT32 RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_NAS_PPP_VALID_ENUM
 结构说明  : RRRABM_RAB_INFO_STRU,PPP是否合法。
*****************************************************************************/
enum RRC_NAS_PPP_VALID_ENUM
{
    RRC_NAS_PPP_VALID                   = 0,
    RRC_NAS_PPP_INVALID                 = 1
};
typedef VOS_UINT32 RRC_NAS_PPP_VALID_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_PLMN_SEARCH_TYPE_ENUM
 结构说明  : RRMM_PLMN_SEARCH_REQ_STRU消息中的enSearchType
*****************************************************************************/
enum RRC_PLMN_SEARCH_TYPE_ENUM
{
    RRC_PLMN_SEARCH_SPEC                = 0,                /* 指定的PLMN的搜索 */
    RRC_PLMN_SEARCH_LIST                = 1,                /* PLMN列表的搜索   */
    RRC_PLMN_SEARCH_SPEC_FAST           = 2,                /* 指定的PLMN搜索搜索所有的BAND */

    RRC_PLMN_SEARCH_NCELL_SPEC          = 3,                /* SVLTE特性开启时根据modem1 g上报的TDS邻区频点信息搜网类型 */

    RRC_PLMN_SEARCH_HISTORY             = 4,                /*历史信息搜索*/
    RRC_PLMN_SEARCH_GET_GEO             = 5,                /*获取地理信息 */

    /*搜索预置band，接入层不需要进行全band搜索，仅需要搜索预置band,但如果预置band
    和硬件支持的band完全重叠，接入层需要在搜网结果中将进行过全band扫频的标志位置位*/
    RRC_PLMN_SEARCH_PREF_BAND           = 6,

    RRC_PLMN_SEARCH_TYPE_BUTT
};
typedef VOS_UINT32 RRC_PLMN_SEARCH_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_PLMN_SEARCH_RLT_ENUM
 结构说明  : RRMM_PLMN_SEARCH_CNF_STRU消息中的enSearchRlt
*****************************************************************************/
enum RRC_PLMN_SEARCH_RLT_ENUM
{
    RRC_PLMN_SEARCH_RLT_SPEC            = 0,                /* 指定的PLMN ID 搜索成功 */
    RRC_PLMN_SEARCH_RLT_LIST            = 1,                /* PLMN List搜索成功      */
    RRC_PLMN_SEARCH_RLT_SPEC_FAIL       = 2,                /* 指定PLMN ID搜索失败    */
    RRC_PLMN_SEARCH_RLT_LIST_REJ        = 3,
    RRC_PLMN_SEARCH_RLT_LIST_FAIL       = 4,                /* 处在D态和F态发生plmn list搜回的原因值 */

    RRC_PLMN_SEARCH_RLT_SPEC_NO_RF      = 5,                /* 指定搜资源申请失败 */
    RRC_PLMN_SEARCH_RLT_LIST_NO_RF      = 6,                /* list搜资源申请失败 */
    RRC_PLMN_SEARCH_RLT_HISTORY_SUCC    = 7,
    RRC_PLMN_SEARCH_RLT_HISTORY_FAIL    = 8,
    RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF   = 9,
    RRC_PLMN_SEARCH_RLT_GET_GEO_SUCC    = 10,
    RRC_PLMN_SEARCH_RLT_GET_GEO_FAIL    = 11,
    RRC_PLMN_SEARCH_RLT_GET_GEO_NO_RF   = 12,

    RRC_PLMN_SEARCH_RLT_PREF_BAND_SUCC  = 13,
    RRC_PLMN_SEARCH_RLT_PREF_BAND_FAIL  = 14,
    RRC_PLMN_SEARCH_RLT_PREF_BAND_NO_RF = 15,

    RRC_PLMN_SEARCH_RLT_BUTT
};
typedef VOS_UINT32  RRC_PLMN_SEARCH_RLT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_NAS_CSG_SEARCH_RLT_ENUM
 结构说明  : RRMM_CSG_SEARCH_CNF_STRU消息中的enSearchRlt
*****************************************************************************/
enum RRC_NAS_CSG_SEARCH_RLT_ENUM
{
    RRC_NAS_CSG_SEARCH_RLT_SUCC   = 0,
    RRC_NAS_CSG_SEARCH_RLT_REJ    = 1,
    RRC_NAS_CSG_SEARCH_RLT_FAIL   = 2,
    RRC_NAS_CSG_SEARCH_RLT_NO_RF  = 3,
    RRC_NAS_CSG_SEARCH_RLT_BUTT
};
typedef VOS_UINT8  RRC_NAS_CSG_SEARCH_RLT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : RRC_NAS_AREA_LOST_ENUM
 结构说明  : RRMM_AREA_LOST_IND_STRU消息中的enRptMode
*****************************************************************************/
enum RRC_NAS_AREA_LOST_ENUM
{
    RRC_NAS_SERVICE_AREA_LOST           = 0,                /* 服务区丢失 */
    RRC_NAS_COVERAGE_AREA_LOST          = 1,                /* 覆盖区丢失 */
    RRC_NAS_NO_RF_AREA_LOST    = 2,                /* 由于NO RF导致的掉网 */
    RRC_NAS_AREA_LOST_BUTT
};
typedef VOS_UINT32  RRC_NAS_AREA_LOST_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_NAS_SIM_STATUS_ENUM
 结构说明  : RRMM_START_REQ_STRU消息中的enSimStatus
             RRMM_UICC_STATUS_CHANGE_IND_ST
*****************************************************************************/
enum RRC_NAS_SIM_STATUS_ENUM
{
    RRC_NAS_UICC_ABSENT                 = 0,                /* 卡不存在 */
    RRC_NAS_USIM_PRESENT                = 1,                /* 卡存在,卡类型为 USIM 卡 */
    RRC_NAS_SIM_PRESENT                 = 2,                /* 卡存在,卡类型为 SIM 卡  */
    RRC_NAS_SIM_STATUS_BUTT
};
typedef VOS_UINT32  RRC_NAS_SIM_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_NAS_SIM_STATUS_ENUM
 结构说明  : RRMM_START_REQ_STRU消息中的enRat
*****************************************************************************/
enum RRC_NAS_RAT_TYPE_ENUM
{
    RRC_NAS_RAT_WCDMA_FDD               = 0,                /* only WCDMA    */
    RRC_NAS_RAT_WCDMA_GSM               = 1,                /* WCDMA and GSM */
    RRC_NAS_RAT_GSM                     = 2,                /* only GSM      */
    RRC_NAS_RAT_LTE                     = 3,
    RRC_NAS_RAT_TD_SCDMA                = 4,                /* only TD-SCDMA */
    RRC_NAS_RAT_TYPE_BUTT
};
typedef VOS_UINT32  RRC_NAS_RAT_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_NAS_RAT_LIST_SEARCH_RSLT_ENUM
 结构说明  : RRMM_PLMN_SEARCH_CNF_STRU消息中的LIST搜索完成情况
*****************************************************************************/
enum RRC_NAS_RAT_LIST_SEARCH_RSLT_ENUM
{
    RRC_NAS_RAT_LIST_SEARCH_NOT_START      = 0,                /* LIST搜索未启动        */
    RRC_NAS_RAT_LIST_SEARCH_PARTIAL_CMPL   = 1,                /* LIST搜索已启动,部分完成 */
    RRC_NAS_RAT_LIST_SEARCH_CMPL           = 2,                /* LIST搜索完成          */
    RRC_NAS_RAT_LIST_SEARCH_BUTT
};
typedef VOS_UINT32  RRC_NAS_RAT_LIST_SEARCH_RSLT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRMM_SYS_CFG_RESULT_ENUM
 结构说明  : RRMM_SYS_CFG_CNF消息中的ulResult;
*****************************************************************************/
enum RRMM_SYS_CFG_RESULT_ENUM
{
    RRMM_SYS_CFG_RESULT_SUCCESS         = 0,
    RRMM_SYS_CFG_RESULT_FAILURE         = 1,
    RRMM_SYS_CFG_RESULT_BUTT
};
typedef VOS_UINT32  RRMM_SYS_CFG_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MMC_START_RESULT_ENUM
 结构说明  : RRMM_START_CNF_STRU消息中的enResult
*****************************************************************************/
enum MMC_START_RESULT_ENUM
{
    MMC_START_SUCCESS                   = 0,
    MMC_START_FAILURE                   = 1,
    MMC_START_BUTT
};
typedef VOS_UINT32 MMC_START_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MMC_START_RESULT_ENUM
 结构说明  : RRMM_CELL_SELECTION_CTRL_REQ_STRU消息中的enReselectInd
  1 .日    期   : 2007年07月24日
     作    者   : l57356
     修改内容   : 问题单号 A32D012582 LAU失败小区选择
  2 .日    期   : 2012年10月27日
     作    者   : j00178524
     修改内容   : DTS2012102601822, 经NAS组孙习波, 删除不再使用的枚举
                  RRC_NAS_RESEL_ACCEPTABLE
*****************************************************************************/
enum RRC_NAS_RESEL_TYPE_ENUM
{
    RRC_NAS_CELL_SELECTION              = 0,
    RRC_NAS_RESEL_SUITABLE              = 1,
    RRC_NAS_FORBLA_CHANGE               = 2,
    RRC_NAS_RESEL_BUTT
};
typedef VOS_UINT32  RRC_NAS_RESEL_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_NAS_CALL_TYPE_ENUM
 结构说明  : RRMM_EST_REQ_STRU enEstCause
*****************************************************************************/
enum RRC_NAS_CALL_TYPE_ENUM
{
    RRC_NAS_CALL_TYPE_SPEECH            = 0,
    RRC_NAS_CALL_TYPE_VIDEO             = 1,
    RRC_NAS_CALL_TYPE_OTHER             = 2,
    RRC_NAS_CALL_TYPE_BUTT
};
typedef VOS_UINT32 RRC_NAS_CALL_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_NAS_EST_CAUSE_ENUM
 结构说明  : RRMM_EST_REQ_STRU消息中的enEstCause
*****************************************************************************/
enum RRC_NAS_EST_CAUSE_ENUM
{
    RRC_EST_CAUSE_ORIGIN_CONVERSAT_CALL             = 0,
    RRC_EST_CAUSE_ORIGIN_STREAM_CALL                = 1,
    RRC_EST_CAUSE_ORIGIN_INTERACT_CALL              = 2,
    RRC_EST_CAUSE_ORIGIN_BACKGROUND_CALL            = 3,
    RRC_EST_CAUSE_ORIGIN_SUBSCRIB_TRAFFIC_CALL      = 4,
    RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL           = 5,
    RRC_EST_CAUSE_TERMINAT_STREAM_CALL              = 6,
    RRC_EST_CAUSE_TERMINAT_INTERACT_CALL            = 7,
    RRC_EST_CAUSE_TERMINAT_BACKGROUND_CALL          = 8,
    RRC_EST_CAUSE_EMERGENCY_CALL                    = 9,
    RRC_EST_CAUSE_INTER_RAT_CELL_RESELECT           = 10,
    RRC_EST_CAUSE_INTER_RAT_CELL_CHANGE_ORDER       = 11,
    RRC_EST_CAUSE_REGISTRATION                      = 12,
    RRC_EST_CAUSE_DETACH                            = 13,
    RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL       = 14,
    RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL        = 15,
    RRC_EST_CAUSE_CALL_RE_ESTABLISH                 = 16,
    RRC_EST_CAUSE_TERMINAT_HIGH_PRIORITY_SIGNAL     = 17,
    RRC_EST_CAUSE_TERMINAT_LOW_PRIORITY_SIGNAL      = 18,
    RRC_EST_CAUSE_TERMINAT_CAUSE_UNKNOWN            = 19,
	RRC_EST_CAUSE_EMERGENCY_CALL_RE_ESTABLISH       = 20,
    RRC_EST_CAUSE_BUTT
};
typedef VOS_UINT32 RRC_NAS_EST_CAUSE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_NAS_IDNNS_TYPE_ENUM
 结构说明  : RRMM_EST_REQ_STRU enIdnns 取值
*****************************************************************************/
enum RRC_NAS_IDNNS_TYPE_ENUM
{
    RRC_IDNNS_LOCAL_TMSI                = 0,
    RRC_IDNNS_TMSI_DIFFER_LA            = 1,
    RRC_IDNNS_TMSI_DIFFER_PLMN          = 2,
    RRC_IDNNS_IMSI_PAGE_RSP             = 3,
    RRC_IDNNS_IMSI_UE_INIT              = 4,
    RRC_IDNNS_IMEI                      = 5,

    RRC_IDNNS_CSFB_LOCAL_TMSI           = 6,        /* mt csfb到G时使用，paging request消息中指示mobile identity type为s-tmsi或者
                                                       cs service notification消息中指示mobile identity type为tmsi */
    RRC_IDNNS_CSFB_LOCAL_IMSI           = 7,        /* mt csfb到G时使用，paging request消息或cs service notification消息中指示mobile identity type为imsi*/

	RRC_NAS_IDNNS_BUTT
};
typedef VOS_UINT32 RRC_NAS_IDNNS_TYPE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : NAS_RRC_SPLMN_SAME_RPLMN_ENUM
 结构说明  : RRMM_EST_REQ_STRU enSplmnSameRplmn 取值
*****************************************************************************/
enum NAS_RRC_SPLMN_SAME_RPLMN_ENUM
{
    NAS_RRC_SPLMN_SAME_RPLMN                       = 0,     /* 选择的PLMN和RPLMN一致 */
    NAS_RRC_SPLMN_DIFF_RPLMN                       = 1,     /* 选择的PLMN和RPLMN不一致 */
    NAS_RRC_SPLMN_RPLMN_BUTT
};
typedef VOS_UINT32 NAS_RRC_SPLMN_SAME_RPLMN_ENUM_UINT32;


/*****************************************************************************
 枚举名    : RRC_NAS_EST_RESULT_ENUM
 结构说明  : RRMM_EST_CNF_STRU enResult取值
*****************************************************************************/
enum RRC_NAS_EST_RESULT_ENUM
{
    RRC_EST_SUCCESS                     = 0,                /* 信令连接建立成功                     */
    RRC_EST_PRESENT                     = 1,                /* 该信令连接已经存在                   */
    RRC_EST_ESTING                      = 2,                /* 该信令连接正在建立                   */
    RRC_EST_DELING                      = 3,                /* 该信令连接正在释放                   */
    RRC_EST_RJ_CONGEST                  = 4,                /* RRC Connection Reject: Congestion    */
    RRC_EST_RJ_UNSPEC                   = 5,                /* RRC Connection Reject: Unspecified   */
    RRC_EST_ACCESS_BARRED               = 6,                /* access barred because of AC control  */
    RRC_EST_EST_CONN_FAIL               = 7,                /* RR connection establish failure      */
    RRC_EST_RJ_INTER_RAT                = 8,                /* RR connection Reject: 指示进入异系统 */
    RRC_EST_IMMEDIATE_ASSIGN_REJECT     = 9,                /* 正常的接入过程，发送RA脉冲后，收到立即指派拒绝消息，
                                                               没有收到立即指派消息而导致的接入失败 */
    RRC_EST_RANDOM_ACCESS_REJECT        = 10,               /* 正常的接入过程，发送RA脉冲后，没有收到网络侧的立即指派，
                                                               也没有收到立即指派拒绝，接入失败 */
    RRC_EST_PAGING_ACCESS_BARRED        = 11,               /*Paging Restriction(PPAC引入)*/
    RRC_EST_REGISTER_ACCESS_BARRED      = 12,                /*Location/Registration Restriction(PPAC引入)*/
    RRC_EST_OTHER_ACCESS_BARRED         = 13,

    RRC_EST_RJ_T3122_RUNNING            = 14,               /* G下立即指派被拒启动T3122，在T3122运行期间回复建联请求 */

    RRC_EST_RJ_NO_RF                       = 15,               /* 由于RF不可用导致的RRC建立失败 */

    RRC_EST_RJ_SNW                       = 16,               /* AS搜网状态RRC回复建链失败 */

    RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO        = 17,   /* 仅G下使用，未同步完成邻区 */

    RRC_EST_RJ_RA_FAIL                      = 18,           /* GAS发起RA达到最大次数，GPHY一直没有回复发送成功, */
    RRC_EST_RJ_NOT_ALLOW                    = 19,           /* MM层发起的建立连接请求不允许,例如收到立即指派，保护定时器期间不允许再次发起接入 */
    RRC_EST_RJ_TIME_OUT                     = 20,           /* 建立CS连接过程中的模块间的保护定时器超时,GAS,TDRRC都会使用 */
    RRC_EST_RJ_RA_RESOURCE_FAIL             = 21,           /* 申请随机接入资源失败; */
    RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID     = 22,           /* 收到的立即指派非法 */
    RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL = 23,           /* 信道指派过程中激活物理信道失败*/
    RRC_EST_RJ_AIRMSG_DECODE_ERR            = 24,           /* 空口消息解码错误 */
    RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT    = 25,           /* 当前未驻留 */
    RRC_EST_RJ_INVALID_UE_STATE             = 26,           /* 错误的UE状态  */
    RRC_EST_RJ_CELL_BAR                     = 27,           /* 小区被bar */
    RRC_EST_RJ_FASTRETURN_LTE               = 28,           /* FASTRETURN_LTE */
    RRC_EST_RJ_RA_FAIL_NO_VALID_INFO        = 29,           /* 仅G下使用,GAS发起RA达到最大次数，GPHY一直没有回复发送成功,未同步完成邻区 */

    RRC_NAS_EST_RESULT_BUTT
};
typedef VOS_UINT32 RRC_NAS_EST_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_NAS_EST_RESULT_ENUM
 结构说明  : RRMM_DATA_REQ_STRU enPriorityInd取值
*****************************************************************************/
enum RRC_NAS_MSG_PRIORTY_ENUM
{
    RRC_NAS_MSG_PRIORTY_LOW             = 0,                /* 消息优先级：Low  */
    RRC_NAS_MSG_PRIORTY_HIGH            = 1,                /* 消息优先级：High */
    RRC_NAS_MSG_PRIORTY_BUTT
};
typedef VOS_UINT32 RRC_NAS_MSG_PRIORTY_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_CELL_BAR_ENUM
 结构说明  : RRMM_ABORT_REQ_STRU enBarValidFlg取值
*****************************************************************************/
enum RRC_CELL_BAR_ENUM
{
    RRC_CELL_BARRED                     = 0,                /* 原定义WUEPS_TRUE */
    RRC_CELL_UNBARRED                   = 1,                /* 原定义WUEPS_FALSE */
    RRC_CELL_BAR_BUTT
};
typedef VOS_UINT32 RRC_CELL_BAR_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_NAS_EST_RESULT_ENUM
 结构说明  : RRMM_REL_IND_STRU enRrcConnStatus取值
*****************************************************************************/
enum RRC_RRC_CONN_STATUS_ENUM
{
    RRC_RRC_CONN_STATUS_PRESENT         = 0,                /* 原先接口WUEPS_TRUE，RRC Connection存在    */
    RRC_RRC_CONN_STATUS_ABSENT          = 1,                /* 原先接口WUEPS_FALSE，RRC Connection不存在 */
    RRC_RRC_CONN_STATUS_BUTT
};
typedef VOS_UINT32 RRC_RRC_CONN_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_LIMIT_CAMP_ACTION_ENUM
 结构说明  : RRMM_LIMIT_SERVICE_CAMP_IND_STRU enLimitCampAction的取值
*****************************************************************************/
enum RRC_LIMIT_CAMP_ACTION_ENUM
{
    RRC_LIMIT_CAMP_ACTION_START         = 0,                /* 限制服务开始 */
    RRC_LIMIT_CAMP_ACTION_END           = 1,                /* 限制服务结束 */
    RRC_LIMIT_CAMP_ACTION_BUTT
};
typedef VOS_UINT32 RRC_LIMIT_CAMP_ACTION_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_NAS_EST_RESULT_ENUM
 结构说明  : RRMM_REL_IND_STRU enRelCause取值
*****************************************************************************/
enum RRC_REL_CAUSE_ENUM
{
    /* RRC Connection Release消息中的原因 */
    RRC_REL_CAUSE_RR_NORM_EVENT                 = 0,        /* Normal event                             */
    RRC_REL_CAUSE_RR_UNSPEC                     = 1,        /* Unspecified                              */
    RRC_REL_CAUSE_RR_PRE_EMPT_REL               = 2,        /* Pre-emptive release                      */
    RRC_REL_CAUSE_RR_CONGEST                    = 3,        /* Congedtion                               */
    RRC_REL_CAUSE_RR_RE_EST_REJ                 = 4,        /* Re-establishment reject                  */
    RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST       = 5,        /* Directed signal conn re-establish        */
    RRC_REL_CAUSE_RR_USER_INACT                 = 6,        /* User inactive                            */
    RRC_REL_CAUSE_UTRAN_RELEASE                 = 7,        /* Signaling Connection Release,RRC收到Signaling Connection Release消息 */
    /* NAS指示释放 */
    RRC_REL_CAUSE_NAS_REL_SUCCESS               = 8,        /* NAS Release Connection：Successful       */
    RRC_REL_CAUSE_NAS_REL_ABSENT                = 9,        /* NAS Release Connection: Absent           */
    RRC_REL_CAUSE_NAS_ABORT                     = 10,       /* NAS : Abort                              */
    RRC_REL_CAUSE_NAS_STOP_SETUP                = 11,       /* NAS Stop connection setup                */
    /* 其它 */
    RRC_REL_CAUSE_CONN_FAIL                     = 12,       /* RR Connection Failure                    */
    RRC_REL_CAUSE_NAS_DATA_ABSENT               = 13,       /* NAS Data Request: Connection Absent      */
    RRC_REL_CAUSE_RRC_ERROR                     = 14,       /* RRC处理异常: RRC ERROR                   */
    RRC_REL_CAUSE_RL_FAILURE                    = 15,       /* Radio Link Failure                       */
    RRC_REL_CAUSE_GAS_TIMEOUT                   = 16,       /* GAS 新增，超时引起 RR 连接释放           */
    RRC_REL_CAUSE_OTHER_REASON                  = 17,       /* 其它原因                                 */
    RRC_REL_CAUSE_NO_RF                         = 18,       /* 没有射频资源,DSDS新增 */

    RRC_REL_CAUSE_RLC_ERROR                     = 19,       /* RLC不可恢复错误 */
    RRC_REL_CAUSE_CELL_UPDATE_FAIL              = 20,       /* CELL Update失败,TD使用 */
    RRC_REL_CAUSE_T314_EXPIRED                  = 21,       /* CS域链路存在，连接态下失步搜网失败，T314超时 */
    RRC_REL_CAUSE_T315_EXPIRED                  = 22,       /* PS域链路存在，连接态下失步搜网失败，T315超时 */
    RRC_REL_CAUSE_W_RL_FAIL                     = 23,       /* 仅W下使用，Radio link失败，不触发呼叫重建 */

    RRC_REL_CAUSE_G_RL_FAIL                     = 24,       /* 仅G下使用，Radio link失败，不触发呼叫重建 */


    RRC_REL_CAUSE_BUTT
};
typedef VOS_UINT32 RRC_REL_CAUSE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_NAS_AC_TYPE_ENUM
 结构说明  : RRMM_AC_INFO_CHANGE_IND_STRU enAcChangeInd取值
*****************************************************************************/
enum RRC_NAS_AC_TYPE_ENUM
{
    RRC_NAS_AC_NOT_BAR                  = 0,                /* 至少一个AC现在不阻塞 */
    RRC_NAS_T3122_EXPIRE                = 1,
    RRC_NAS_AC_TYPE_BUTT
};
typedef VOS_UINT32 RRC_NAS_AC_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_NAS_AC_TYPE_ENUM
 结构说明  : RRMM_SUSPEND_IND_ST enSuspendCause 取值
 1.日    期   : 2011年07月13日
   作    者   : w00176964
   修改内容   : GUNAS V7R1 PhaseII 阶段调整:增加CCO回退类型
*****************************************************************************/
enum MMC_SUSPEND_CAUSE_ENUM
{
    MMC_SUSPEND_CAUSE_HANDOVER              = 0x00,
    MMC_SUSPEND_CAUSE_CELLRESELECT          = 0x01,
    MMC_SUSPEND_CAUSE_CELLCHANGE            = 0x02,
    MMC_SUSPEND_CAUSE_PLMNSEARCH            = 0x03,  /* 新增原因值，当WAS需要GAS进行PLMN搜索时，挂起NAS的原因原因值 */
    MMC_SUSPEND_CAUSE_CELLCHANGE_FALLBACK   = 0x04,  /* 新增原因值，用于异系统CCO过程失败回退向NAS指示的挂起类型    */
    MMC_SUSPEND_CAUSE_REDIRECTION           = 0x05,  /* 新增原因值, 用于异系统重定向时,GU接入层挂起NAS指示的挂起类型 */
    MMC_SUSPEND_CAUSE_BUTT
};

typedef VOS_UINT8 MMC_SUSPEND_CAUSE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : RRC_NAS_AC_TYPE_ENUM
 结构说明  : RRMM_SUSPEND_IND_ST enSuspendOrigen
*****************************************************************************/
enum MMC_SUSPEND_ORIGEN_ENUM
{
    MMC_SUSPEND_ORIGEN_GSM              = 0x00,
    MMC_SUSPEND_ORIGEN_WCDMA            = 0x01,
    MMC_SUSPEND_ORIGEN_LTE              = 0x02,
    MMC_SUSPEND_ORIGEN_BUTT
};
typedef VOS_UINT8 MMC_SUSPEND_ORIGEN_UINT8;


/*****************************************************************************
 枚举名    : MMC_SUSPEND_DESTINATION_UINT8
 结构说明  : MMC_SUSPEND_DESTINATION_UINT8 enSuspendDest
*****************************************************************************/
enum MMC_SUSPEND_DESTINATION
{
    MMC_SUSPEND_DESTINATION_GSM              = 0x00,
    MMC_SUSPEND_DESTINATION_WCDMA            = 0x01,
    MMC_SUSPEND_DESTINATION_LTE              = 0x02,
    /* Added by s00246516 for L-C互操作项目, 2014-01-26, Begin */
    MMC_SUSPEND_DESTINATION_HRPD             = 0x03,
    /* Added by s00246516 for L-C互操作项目, 2014-01-26, End */
    MMC_SUSPEND_DESTINATION_BUTT
};
typedef VOS_UINT8 MMC_SUSPEND_DESTINATION_UINT8;

/*****************************************************************************
 枚举名    : MMC_RE_TRANS_MSG_TYPE_ENUM
 结构说明  : 发生切换的情况下，L3通知NAS需要重发的直传消息的类型
*****************************************************************************/
enum NAS_RRC_RE_TX_MSGTYPE_ENUM
{
    NAS_RRC_NULL_RE_TX_MSG              = 0,                /* 没有消息需要重传 */
    NAS_RRC_RE_TX_EST_REQ_MSG           = 1,                /* EST_REQ消息 */
    NAS_RRC_RE_TX_DATA_REQ_MSG          = 2,                /* DATA_REQ消息 */
    NAS_RRC_RE_TX_MSGTYPE_BUTT
};
typedef VOS_UINT32 NAS_RRC_RE_TX_MSGTYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_NAS_AC_TYPE_ENUM
 结构说明  : RRMM_SUSPEND_RSP_ST enResult 取值
*****************************************************************************/
enum RRC_NAS_SUSPEND_RESULT_ENUM
{
    RRC_NAS_SUSPEND_SUCCESS             = 0x00,
    RRC_NAS_SUSPEND_FAILURE             = 0x01
};
typedef VOS_UINT8 RRC_NAS_SUSPEND_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MMC_RESUME_RESULT_ENUM
 结构说明  : RRMM_RESUME_IND_ST enResult 取值
*****************************************************************************/
enum MMC_RESUME_RESULT_ENUM
{
    MMC_RESUME_RESULT_SUCCESS           = 0x00,
    MMC_RESUME_RESULT_FAILURE           = 0x01,
    MMC_RESUME_GPRS_SUSPENSION          = 0x02,
    MMC_RESUME_RESULT_BUTT
};
typedef VOS_UINT8 MMC_RESUME_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MMC_RESUME_RESULT_ENUM
 结构说明  : RRMM_RESUME_IND_ST  enCsResumeResult,enPsResumeResult
*****************************************************************************/
enum MMC_RESUME_ORIGEN_ENUM
{
    MMC_RESUME_ORIGEN_GSM               = 0x00,
    MMC_RESUME_ORIGEN_WCDMA             = 0x01,
    MMC_RESUME_ORIGEN_LTE               = 0x02,

    /* Added by s00246516 for L-C互操作项目, 2014-01-26, Begin */
    MMC_RESUME_ORIGEN_HRPD              = 0x03,
    /* Added by s00246516 for L-C互操作项目, 2014-01-26, End */

    MMC_RESUME_ORIGEN_BUTT
};
typedef VOS_UINT8 MMC_RESUME_ORIGEN_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MMC_AS_SUSPEND_STOP_ENUM
 结构说明  : 挂起停止方式参数值
             RRMM_SUSPEND_REQ_ST enStopCause
*****************************************************************************/
enum MMC_AS_SUSPEND_STOP_ENUM
{
    MMC_AS_SUSPEND_STOP                 = 0x00,             /* 挂起停止当前接入层，但不移除DSP */
    MMC_AS_SUSPEND_STOP_DSP             = 0x01,             /* 挂起停止当前接入层，移除DSP */
    MMC_AS_SUSPEND_STOP_BUTT
};
typedef VOS_UINT8 MMC_AS_SUSPEND_STOP_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MMC_AS_SUSPEND_STOP_ENUM
 结构说明  : 接入层挂起结果参数值
             RRMM_SUSPEND_CNF_ST enResult
*****************************************************************************/
enum MMC_AS_SUSPEND_RESULT_ENUM
{
    MMC_AS_SUSPEND_SUCCESS              = 0x00,             /* 当前接入层挂起成功，接入层功能将转到新的接入层处理 */
    MMC_AS_SUSPEND_FAILURE              = 0x01,             /* 当前接入层挂起失败，当前接入层仍提供接入层功能 */
    MMC_AS_SUSPEND_RESULT_BUTT
};
typedef VOS_UINT8 MMC_AS_SUSPEND_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AS_UICC_STATUS_IND_RESULT_ENUM
 结构说明  : 接入层挂起结果参数值
             RRMM_UICC_STATUS_CHANGE_RSP_ST enResult
*****************************************************************************/
enum AS_UICC_STATUS_IND_RESULT_ENUM
{
    AS_UICC_STATUS_IND_SUCCESS          = 0,
    AS_UICC_STATUS_IND_FAIL             = 1,
    AS_UICC_STATUS_IND_BUTT
};
typedef VOS_UINT32 AS_UICC_STATUS_IND_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_SECURITY_RPT_MODE_ENUM
 结构说明  : RRMM_SECURITY_IND_STRU enRptMode取值
*****************************************************************************/
enum RRC_SECURITY_RPT_MODE_ENUM
{
    RRC_SECURITY_CS_SMC_CMPL            = 0,                /* 一个CS SMC流程结束                       */
    RRC_SECURITY_DEL_CS_KEY             = 1,                /* USIM中CS域CK、IK被删除                   */
    RRC_SECURITY_DEL_PS_KEY             = 2,                /* USIM中PS域CK、IK被删除                   */
    RRC_SECURITY_DEL_CS_PS_KEY          = 3,                /* USIM中CS+PS域CK、IK被删除                */
    RRC_SECURITY_CS_SMC_RCV             = 4,                /* 收到有效的CS SMC消息                     */
    RRC_SECURITY_PS_SMC_RCV             = 5,                /* 收到有效的PS SMC消息                     */
    RRC_SECURITY_PS_SMC_CMPL            = 6,                /* 一个PS SMC流程结束                       */
    RRC_SECURITY_RB_CTRL_MSG            = 7,                /* 收到重配消息修改加密算法                 */
    RRC_SECURITY_MOBI_MSG               = 8,                /* 收到CELL/URA UPDATE CNF消息修改加密算法  */
    RRC_SECURITY_RPT_MODE_BUTT
};
typedef VOS_UINT32 RRC_SECURITY_RPT_MODE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_NAS_PDCP_EXIST_FLAG_ENUM
 结构说明  : RAB_INFO_STRU 消息的 enPdcpFlg
             标识对应的RAB PDCP是否存在
*****************************************************************************/
enum RRC_NAS_PDCP_EXIST_FLAG_ENUM
{
    RRC_NAS_PDCP_NOT_EXIST              = 0,
    RRC_NAS_PDCP_EXIST                  = 1,
    RRC_NAS_PDCP_EXIST_FLAG_BUTT
};
typedef VOS_UINT32 RRC_NAS_PDCP_EXIST_FLAG_ENUM_UINT32;



/*****************************************************************************
 枚举名    : RRC_NAS_PAGING_TYPE_ENUM
 结构说明  : RRMM_PAGING_IND_STRU enPagingType取值
*****************************************************************************/
enum RRC_NAS_PAGING_TYPE_ENUM
{
    RRC_NAS_PAGING_TYPE1                = 0,                /* Paging Type 1 */
    RRC_NAS_PAGING_TYPE2                = 1,                /* Paging Type 2 */
    RRC_NAS_PAGING_TYPE_BUTT
};
typedef VOS_UINT32 RRC_NAS_PAGING_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_PAGE_CAUSE_ENUM
 结构说明  : RRMM_PAGING_IND_STRU enPagingCause取值
*****************************************************************************/
enum RRC_PAGE_CAUSE_ENUM
{
    RRC_PAGE_CAUSE_TERMINAT_CONVERSAT_CALL          = 0,
    RRC_PAGE_CAUSE_TERMINAT_STREAM_CALL             = 1,
    RRC_PAGE_CAUSE_TERMINAT_INTERACT_CALL           = 2,
    RRC_PAGE_CAUSE_TERMINAT_BACKGROUND_CALL         = 3,
    RRC_PAGE_CAUSE_TERMINAT_HIGH_PRIORITY_SIGNAL    = 4,
    RRC_PAGE_CAUSE_TERMINAT_LOW_PRIORITY_SIGNAL     = 5,
    RRC_PAGE_CAUSE_TERMINAT_CAUSE_UNKNOWN           = 6,
    RRC_PAGE_CAUSE_BUTT
};
typedef VOS_UINT32 RRC_PAGE_CAUSE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_PAGE_UE_ID_ENUM
 结构说明  : RRMM_PAGING_IND_STRU enPagingUeId取值
*****************************************************************************/
enum RRC_PAGE_UE_ID_ENUM
{
    RRC_IMSI_GSM_MAP                    = 0,                /* used for Paging Type 1/2 */
    RRC_TMSI_GSM_MAP_P_TMSI             = 1,                /* used for Paging Type 1   */
    RRC_IMSI_DS41                       = 2,                /* used for Paging Type 1/2 */
    RRC_TMSI_DS41                       = 3,                /* used for Paging Type 1/2 */
    RRC_P_TMSI_GSM_MAP                  = 4,                /* used for Paging Type 1   */
    RRC_PAGE_UE_ID_BUTT
};
typedef VOS_UINT32 RRC_PAGE_UE_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_PAGE_UE_ID_ENUM
 结构说明  : RRRABM_RAB_IND_STRU enRabChangeType取值
             RRRABM_HANDOVER_RAB_IND_STRU
*****************************************************************************/
enum NAS_RRC_RAB_CHANGE_ENUM
{
    NAS_RRC_RAB_SETUP_REQUEST           = 0,                /* 请求建立新的RAB   */
    NAS_RRC_RAB_SETUP_SUCCESS           = 1,                /* 成功建立新的RAB   */
    NAS_RRC_RAB_SETUP_FAILURE           = 2,                /* 建立新的RAB失败   */
    NAS_RRC_RAB_RECONFIG                = 3,                /* 重配已经建立的RAB */
    NAS_RRC_RAB_RELEASE                 = 4,                /* 释放已经建立的RAB */
    NAS_RRC_RAB_CHANGE_BUTT
};
typedef VOS_UINT32 NAS_RRC_RAB_CHANGE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_RAB_STATUS_ENUM
 结构说明  : RRRABM_STATUS_IND_STRU enStatus取值
*****************************************************************************/
enum RRC_RAB_STATUS_ENUM
{
    RRC_RAB_STATUS_STOP                 = 0,                /* 停止数据传送 */
    RRC_RAB_STATUS_CONTINUE             = 1,                /* 恢复数据传送 */
    RRC_RAB_STATUS_BUTT
};
typedef VOS_UINT32 RRC_RAB_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_NAS_ATTACH_STATUS_ENUM
 结构说明  : NAS_INFO_STRU enAttach取值
*****************************************************************************/
enum RRC_NAS_ATTACH_STATUS_ENUM
{
    RRC_NAS_ATTACH                      = 0,
    RRC_NAS_NOT_ATTACH                  = 1,
    RRC_NAS_ATTACH_STATUS_BUTT
};
typedef VOS_UINT32 RRC_NAS_ATTACH_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_NAS_USIM_STATUS_ENUM
 结构说明  : NAS_INFO_STRU enUsimValid取值
*****************************************************************************/
enum RRC_NAS_USIM_STATUS_ENUM
{
    RRC_NAS_USIM_VALID                  = 0,
    RRC_NAS_USIM_INVALID                = 1,
    RRC_NAS_USIM_STATUS_BUTT
};
typedef VOS_UINT32 RRC_NAS_USIM_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_NAS_AT_ACTION_ENUM
 结构说明  : RRMM_AT_MSG_REQ_ST enActionType的取值
*****************************************************************************/
enum RRC_NAS_AT_ACTION_ENUM
{
    RRC_NAS_AT_START_FOREVER            = 0,                /* 指示WRRC永久启动 */
    RRC_NAS_AT_START_ONCE               = 1,                /* 指示WRRC永久启动一次 */
    RRC_NAS_AT_STOP                     = 2,                /* 指示WRRC停止 */
    RRC_NAS_AT_ACTION_BUTT
};
typedef VOS_UINT8 RRC_NAS_AT_ACTION_ENUM_UINT8;


/*****************************************************************************
 枚举名    : RRC_NAS_AT_MSG_TYPE_ENUM
 结构说明  : RRMM_AT_MSG_REQ_ST enMsgType的取值
 4.日    期   : 2011年12月25日
   作    者   : s46746
   修改内容   : 枚举值定义不是按位新增的

  2.日    期   : 2012年6月2日
    作    者   : z40661
    修改内容   : DTS2012053006110 与WAS修改接口,将当前模式接口单独独立处理
*****************************************************************************/
enum RRC_NAS_AT_MSG_TYPE_ENUM
{
    RRC_NAS_AT_CELL_SIGN                = 1,                /* 表示获取小区信息强度 */
    RRC_NAS_AT_CELL_ID                  = 2,                /* 表示获取小区ID */
    RRC_NAS_AT_CELL_BLER                = 4,                /* 表示获取信道误码率 */
    RRC_NAS_AT_CELL_SUBMODE             = 8,
    RRC_NAS_AT_MSG_TYPE_BUTT
};
typedef VOS_UINT8 RRC_NAS_AT_MSG_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : RRC_NAS_AT_MSG_SUBMODE_ENUM
  1.日    期   : 2012年6月2日
    作    者   : z40661
    修改内容   : DTS2012053006110 与WAS修改接口,将当前模式接口单独独立处理
*****************************************************************************/
enum RRC_NAS_AT_MSG_SUBMODE_ENUM
{
   RRC_NAS_AT_R99_ONLY                 ,             /* 表示只有R99相关配置  */
   RRC_NAS_AT_HSDPA_ONLY               ,             /* 表示有HSDPA数传存在 */
   RRC_NAS_AT_HSUPA_ONLY               ,             /* 表示有HSUPA数传存在 */
   RRC_NAS_AT_HSDPA_AND_HSUPA          ,              /* 表示同时存在HSDPA和HSUPA*/
   RRC_NAS_AT_HSPA_PLUS                ,              /* 表示存在HSPA+*/
   RRC_NAS_AT_DC_HSPA_PLUS             ,              /* 表示存在DC+HSPA+*/
   RRC_NAS_AT_DC_MIMO                  ,              /* 表示存在DC+MIMO*/
   RRC_NAS_AT_MSG_RAT_BUTT
};
typedef VOS_UINT8 RRC_NAS_AT_MSG_SUBMODE_ENUM_UINT8;



/*****************************************************************************
 枚举名    : RRC_NAS_AT_MSG_FLAG_ENUM
 结构说明  : RRMM_AT_MSG_CNF_ST enMsgFlg的取值
*****************************************************************************/
enum RRC_NAS_AT_MSG_FLAG_ENUM
{
    RRC_NAS_AT_VALID                    = 0,
    RRC_NAS_AT_INVALID                  = 1,
    RRC_NAS_AT_MSG_FLAG_BUTT
};
typedef VOS_UINT8 RRC_NAS_AT_MSG_FLAG_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_WCDMA_BAND_TYPE_ENUM
 结构说明  : RRMM_SET_WCDMA_BAND_REQ_ST enWasDlFreqInfo
*****************************************************************************/
enum NAS_WCDMA_BAND_TYPE_ENUM
{
    NAS_WCDMA_BAND_TYPE_NULL            = 0x0,
    NAS_WCDMA_BAND_TYPE_800             = 0x0001,
    NAS_WCDMA_BAND_TYPE_850             = 0x0002,
    NAS_WCDMA_BAND_TYPE_900             = 0x0004,
    NAS_WCDMA_BAND_TYPE_1800            = 0x0010,
    NAS_WCDMA_BAND_TYPE_1900            = 0x0020,
    NAS_WCDMA_BAND_TYPE_2100            = 0x0100,
    NAS_WCDMA_BAND_TYPE_ANY             = 0x01ff,
    NAS_WCDMA_BAND_TYPE_BUTT
};
typedef VOS_UINT32 NAS_WCDMA_BAND_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : WAS_CHANGE_BAND_RESULT_ENUM
 结构说明  : RRMM_SET_WCDMA_BAND_CNF_ST enResult
*****************************************************************************/
enum WAS_CHANGE_BAND_RESULT_ENUM
{
    WAS_CHANGE_BAND_SUCCESS             = 0,
    WAS_CHANGE_BAND_FAIL                = 1,
    WAS_CHANGE_BAND_RESULT_BUTT
};
typedef VOS_UINT32 WAS_CHANGE_BAND_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : GRRMM_MSG_REL_VER_ENUM
 结构说明  : GRRMM_SYS_INFO_IND_ST enMsrRelease
*****************************************************************************/
enum GRRMM_MSG_REL_VER_ENUM
{
    GRRMM_MSC_RELEASE98_OR_OLDER        = 0,
    GRRMM_MSC_RELEASE99_ONWARDS         = 1,
    GRRMM_MSG_REL_VER_BUTT
};
typedef VOS_UINT8   GRRMM_MSG_REL_VER_ENUM_UINT8;

/* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
/*****************************************************************************
 枚举名    : RRC_NAS_RESTRICTION_ENUM
 结构说明  : GRRMM_SYS_INFO_IND_ST ulAcInfo
1.日    期 : 2012年12月12日
  作    者 : w00176964
  修改内容 : 新建
*****************************************************************************/
enum RRC_NAS_RESTRICTION_ENUM
{
    RRC_NAS_ACCESS_NO_RESTRICTION                                   = 0,     /* 不阻塞业务 */
    RRC_NAS_ACCESS_RESTRICTION_NORMAL_SERVICE                       = 1,     /* 阻塞正常业务 */
    RRC_NAS_ACCESS_RESTRICTION_EMERGENCY_SERVICE                    = 2,     /* 阻塞紧急业务 */
    RRC_NAS_ACCESS_RESTRICTION_ALL_SERVICE                          = 3,     /* 阻塞正常业务和紧急业务 */
    RRC_NAS_ACCESS_BUTT
};
typedef VOS_UINT8 RRC_NAS_RESTRICTION_ENUM_UINT8;

/*******************************************************************************
 结构名    :RRC_NAS_RESTRICTION_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : union RRC_NAS_RESTRICTION_UN成员stBitRestrictType定义
             bit位置1表示该类型有效
1.日    期 : 2012年12月12日
  作    者 : w00176964
  修改内容 : 新建
*******************************************************************************/
typedef struct
{
    VOS_UINT8                          ucRestrictNormalService          :1;         /* 阻塞正常业务 */
    VOS_UINT8                          ucRestrictEmergencyService       :1;         /* 阻塞紧急业务 */
    VOS_UINT8                          ucRestrictSpare6                 :6;
}RRC_NAS_RESTRICTION_STRU;

/*****************************************************************************
 枚举名    : RRC_NAS_RESTRICTION_UN
 结构说明  : RRC_NAS_RESTRICTION_UN ulAcInfo
1. 日    期: 2012年12月08日
   作    者: w00176964
   修改内容: 新建
*****************************************************************************/
typedef union
{
    VOS_UINT8                           ucRestrictType;

    RRC_NAS_RESTRICTION_STRU            stBitRestrictType;
}RRC_NAS_RESTRICTION_UN;
/* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */



/*****************************************************************************
 枚举名    : NAS_GAS_BAND_INDICATOR_ENUM
 结构说明  : GRRMM_SYS_INFO_IND_ST ucBandIndicator
*****************************************************************************/
enum GRRMM_BAND_INDICATOR_ENUM
{
    GRRMM_BAND_INDICATOR_1800             = 0,
    GRRMM_BAND_INDICATOR_1900             = 1,
    GRRMM_BAND_INDICATOR_BUTT
};
typedef VOS_UINT8 GRRMM_BAND_INDICATOR_ENUM_UINT8;


/*****************************************************************************
 枚举名    : GRRMM_SGSN_REL_VER_ENUM
 结构说明  : GRRMM_SYS_INFO_IND_ST ucSgsnRelease
*****************************************************************************/
enum GRRMM_SGSN_REL_VER_ENUM
{
    GRRMM_SGSN_RELEASE98_OR_OLDER        = 0,
    GRRMM_SGSN_RELEASE99_ONWARDS         = 1,
    GRRMM_SGSN_REL_VER_BUTT
};
typedef VOS_UINT8   GRRMM_SGSN_REL_VER_ENUM_UINT8;

/*****************************************************************************
 枚举名    : GRRMM_NW_OP_MODE_ENUM
 结构说明  : GRRMM_SYS_INFO_IND_ST enNetworkOperationMode
*****************************************************************************/
enum GRRMM_NW_OP_MODE_ENUM
{
    GRRMM_NW_OP_MODE_INVALID            = 0,
    GRRMM_NW_OP_MODE_I                  = 1,
    GRRMM_NW_OP_MODE_II                 = 2,
    GRRMM_NW_OP_MODE_III                = 3,
    GRRMM_NW_OP_MODE_BUTT
};
typedef VOS_UINT8   GRRMM_NW_OP_MODE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : GAS_MS_IE_TYPE_ENUM
 结构说明  : GRRMM_PAGING_IND_ST enMSIDType取值
*****************************************************************************/
enum GAS_MS_IE_TYPE_ENUM
{
    GAS_IMSI                            = 0,                /* IMSI     */
    GAS_TMSI                            = 1,                /* TMSI     */
    GAS_PTMSI                           = 2,                /* PTMSI    */
    GAS_MS_ID_TYPE_BUTT
};
typedef VOS_UINT8   GAS_MS_IE_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : GAS_PAGING_TYPE_ENUM
 结构说明  : GRRMM_PAGING_IND_ST enPagingType取值
*****************************************************************************/
enum GAS_PAGING_TYPE_ENUM
{
    GAS_PAGING_CS                       = 0,                /* CS       */
    GAS_PAGING_PS                       = 1,                /* PS       */
    GAS_PAGING_TYPE_BUTT
};
typedef VOS_UINT8   GAS_PAGING_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : GRR_GMM_GPRS_RESUME_RESULT_ENUM
 结构说明  : RRMM_GPRS_RESUME_IND_ST enResult 取值
*****************************************************************************/
enum GRR_GMM_GPRS_RESUME_RESULT_ENUM
{
    GRR_GMM_GPRS_RESUME_SUCCESS         = 0,
    GRR_GMM_GPRS_RESUME_FAILURE         = 1,
    GRR_GMM_GPRS_RESUME_RESULT_BUTT
};
typedef VOS_UINT8 GRR_GMM_GPRS_RESUME_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_GSM_MASK_ENUM
 结构说明  : GAS_NAS_INFO_ST enMask取值
*****************************************************************************/
enum NAS_GSM_MASK_ENUM
{
    NAS_GSM_MASK_ATTACH                 = 0x0001,
    NAS_GSM_MASK_USIM_INVALID           = 0x0002,
    NAS_GSM_MASK_SECURITY_KEY           = 0x0004,
    NAS_GSM_MASK_DRX                    = 0x0008,
    NAS_GSM_MASK_TMSI_LAI               = 0x0010,
    NAS_GSM_MASK_PTMSI_RAI              = 0x0020,
    NAS_GSM_MASK_DEL_KC                 = 0x0040,           /* 指示GAS删除指定域的KC       */
    NAS_GSM_MASK_GSM_GMM_STATE          = 0x0080,           /* GSM网络下GMM状态信息有效标志 */
    NAS_GSM_MASK_READY_TIMER            = 0x0100,           /* READY TIMER值有效标志        */
    NAS_GSM_MASK_MS_GPRS_MODE           = 0x0200,           /* MS GPRS模式值有效标志 */
    NAS_GSM_MASK_MAPPED_SECURITY_KEY    = 0x0400,           /* LTE下映射过来的安全上下文有效标志 */
    NAS_GSM_MASK_BUTT
};
typedef VOS_UINT32 NAS_GSM_MASK_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_GSM_ATTACH_TYPE_ENUM
 结构说明  : NAS_INFO_STRU enAttach取值
*****************************************************************************/
enum NAS_GSM_ATTACH_TYPE_ENUM
{
    NAS_GSM_ATTACH                      = 0,
    NAS_GSM_NOT_ATTACH                  = 1,
    NAS_GSM_ATTACH_TYPE_BUTT
};
typedef VOS_UINT32 NAS_GSM_ATTACH_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_GSM_USIM_ENUM
 结构说明  : NAS_INFO_STRU enUsimValid取值
*****************************************************************************/
enum NAS_GSM_USIM_ENUM
{
    NAS_GSM_USIM_VALID                  = 0,
    NAS_GSM_USIM_INVALID                = 1,
    NAS_GSM_USIM_BUTT
};
typedef VOS_UINT32 NAS_GSM_USIM_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_GMM_STATE_ENUM
 结构说明  : NAS_INFO_STRU enGsmGmmState取值
*****************************************************************************/
enum NAS_GMM_STATE_ENUM
{
    NAS_GMM_STATE_IDLE                  = 0,                /* GMM状态:idle */
    NAS_GMM_STATE_STANDYBY              = 1,                /* GMM状态:standby */
    NAS_GMM_STATE_READY                 = 2,                /* GMM状态:ready */
    NAS_GMM_STATE_BUTT
};
typedef VOS_UINT8 NAS_GMM_STATE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_GSM_GPRS_MODE_ENUM
 结构说明  : NAS_INFO_STRU enMsGprsMode取值
*****************************************************************************/
enum NAS_GSM_GPRS_MODE_ENUM
{
    NAS_GSM_GPRS_MODE_A                 = 0,                /* MS GPRS模式A:可以同时进行GSM和GPRS业务 */
    NAS_GSM_GPRS_MODE_B                 = 1,                /* MS GPRS模式B:可用于GSM和GPRS业务,但两者不能同时工作 */
    NAS_GSM_GPRS_MODE_C_GSM             = 2,                /* MS GPRS模式C:可以工作GSM模式 */
    NAS_GSM_GPRS_MODE_C_GPRS            = 3,                /* MS GPRS模式C:可以工作GPRS模式 */
    NAS_GSM_GPRS_MODE_BUTT
};
typedef VOS_UINT8 NAS_GSM_GPRS_MODE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : GMM_GRR_TLLI_CAUSE_ENUM
 结构说明  : GRRGMM_ASSIGN_REQ_ST enTlliCause取值
*****************************************************************************/
enum GMM_GRR_TLLI_CAUSE_ENUM
{
    GMM_GRR_NEW_TLLI                    = 1,                /* 产生新的TLLI,通知GRR更新 */
    GMM_GRR_OLD_TLLI                    = 2,                /* 已有的TLLI无效，通知GRR释放 */
    GMM_GRR_TLLI_CAUSE_BUTT
};
typedef VOS_UINT32 GMM_GRR_TLLI_CAUSE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MMC_CM_BAND_ENUM
 结构说明  : RRMM_NAS_PARAMS_REQ_ST ulBand 取值
*****************************************************************************/
enum MMC_CM_BAND_ENUM
{
    MMC_CM_BAND_PREF_GSM_DCS_1800       = 0x00000080,
    MMC_CM_BAND_PREF_GSM_EGSM_900       = 0x00000100,
    MMC_CM_BAND_PREF_GSM_PGSM_900       = 0x00000200,
    MMC_CM_BAND_PREF_GSM_450            = 0x00010000,
    MMC_CM_BAND_PREF_GSM_480            = 0x00020000,
    MMC_CM_BAND_PREF_GSM_750            = 0x00040000,
    MMC_CM_BAND_PREF_GSM_850            = 0x00080000,
    MMC_CM_BAND_PREF_GSM_RGSM_900       = 0x00100000,
    MMC_CM_BAND_PREF_GSM_PCS_1900       = 0x00200000,
    MMC_CM_BAND_PREF_WCDMA_I_IMT_2000   = 0x00400000,
    MMC_CM_BAND_PREF_WCDMA_II_PCS_1900  = 0x00800000,
    MMC_CM_BAND_PREF_WCDMA_III_1700     = 0x01000000,
    MMC_CM_BAND_PREF_ANY                = 0x3FFFFFFF,
    MMC_CM_BAND_PREF_NO_CHANGE          = 0x40000000,
    MMC_CM_BAND_BUTT
};
typedef VOS_UINT32 MMC_CM_BAND_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MM_EST_RESULT_ENUM
 结构说明  : GRRMM_EST_SAPI3_CNF_ST enResult 取值
*****************************************************************************/
enum MM_EST_RESULT_ENUM
{
    MM_EST_SAPI3_SUCCESS                = 0,
    MM_EST_SAPI3_FAILURE                = 1,
    MM_EST_RESULT_BUTT
};
typedef VOS_UINT8 MM_EST_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : GAS_NAS_AT_ACTION_TYPE_ENUM
 结构说明  : GRRMM_AT_MSG_REQ_ST enActionType的取值
*****************************************************************************/
enum GAS_NAS_AT_ACTION_TYPE_ENUM
{
    GAS_NAS_AT_START_FOREVER            = 0,                /* 指示GAS永久启动 */
    GAS_NAS_AT_START_ONCE               = 1,                /* 指示GAS上报一次 */
    GAS_NAS_AT_STOP                     = 2,                /* 指示GAS停止 */

    GAS_NAS_AT_ACTION_TYPE_BUTT
};
typedef VOS_UINT8 GAS_NAS_AT_ACTION_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_GSM_BAND_TYPE_ENUM
 结构说明  : RRMM_SET_GSM_BAND_REQ_ST enGsmBandInfo
*****************************************************************************/
enum NAS_GSM_BAND_TYPE_ENUM
{
    NAS_GSM_BAND_TYPE_NULL              = 0x0000,
    NAS_GSM_BAND_TYPE_450               = 0x0001,           /* ARFCN所代表的频段:GSM 450 */
    NAS_GSM_BAND_TYPE_480               = 0x0002,           /* ARFCN所代表的频段:GSM 480 */
    NAS_GSM_BAND_TYPE_850               = 0x0004,           /* ARFCN所代表的频段:GSM 850 */
    NAS_GSM_BAND_TYPE_P900              = 0x0008,           /* ARFCN所代表的频段:P-GSM 900 */
    NAS_GSM_BAND_TYPE_R900              = 0x0010,           /* ARFCN所代表的频段:R-GSM 900 */
    NAS_GSM_BAND_TYPE_E900              = 0x0020,           /* ARFCN所代表的频段:E-GSM 900 */
    NAS_GSM_BAND_TYPE_1800              = 0x0040,           /* ARFCN所代表的频段:DCS 1800 */
    NAS_GSM_BAND_TYPE_1900              = 0x0080,           /* ARFCN所代表的频段:PCS 1900 */
    NAS_GSM_BAND_TYPE_700               = 0x0100,           /* ARFCN所代表的频段:GSM 700 */
    NAS_GSM_BAND_TYPE_ANY               = 0x01ff,           /*任意频段*/
    NAS_GSM_BAND_TYPE_BUTT
};
typedef VOS_UINT32 NAS_GSM_BAND_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : GAS_CHANGE_BAND_RESULT_ENUM
 结构说明  : RRMM_SET_GSM_BAND_CNF_ST enResult
*****************************************************************************/
enum GAS_CHANGE_BAND_RESULT_ENUM
{
    GAS_CHANGE_BAND_SUCCESS             = 0,
    GAS_CHANGE_BAND_FAIL                = 1,
    GAS_CHANGE_BAND_RESULT_BUTT
};
typedef VOS_UINT32 GAS_CHANGE_BAND_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : GAS_CHANGE_BAND_RESULT_ENUM
 结构说明  : RRMM_SET_GSM_BAND_CNF_ST enResult
*****************************************************************************/
enum RRC_WORK_MODE_ENUM
{
    RRC_WORK_NULL          = 0,     /*NULL状态，开机后未收到过NAS的START_REQ消息时的状态*/
    RRC_WORK_STANDBY       = 1,     /*待命状态，收到PLMN_SEARCH_REQ或者另外一摸的切换命令后可以马上进入工作状态*/
    RRC_WORK_READY         = 2,     /*工作状态，当前不处于切换过程 */
    RRC_WORK_HANDOVER_OUT  = 3,     /*工作状态，同时正处在切出状态 */
    RRC_WORK_HANDOVER_IN   = 4      /*工作状态，同时正处在切入状态 */
};
typedef VOS_UINT8 RRC_WORK_MODE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : MM_SECURITY_MASK_ENUM
 结构说明  : MM_CSPS_INFO_ST enInfoMask
*****************************************************************************/
enum MM_SECURITY_MASK_ENUM
{
    MM_SECURITY_CK_MASK                 = 0x01,             /* CK 有效标志 */
    MM_SECURITY_IK_MASK                 = 0x02,             /* IK 有效标志 */
    MM_SECURITY_KC_MASK                 = 0x04,             /* Kc 有效标志 */
    MM_SECURITY_IMSI_MASK               = 0x08,             /* IMSI 有效标志 */
    MM_SECURITY_CKSN_MASK               = 0x10,             /* CKSN 有效标志 */
    MM_SECURITY_P_TMSI_MASK             = 0x20,             /* P/TMSI 有效标志 */
    MM_SECURITY_MASK_BUTT
};
typedef VOS_UINT8 MM_SECURITY_MASK_ENUM_UINT8;

/*****************************************************************************
 枚举名    : RRC_NAS_AMR_MODE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : AMR模式
*****************************************************************************/
enum RRC_NAS_AMR_MODE_ENUM
{
    RRC_NAS_AMR_SILENCE_FRAME_NO_EXIT   = 0,
    RRC_NAS_AMR_SILENCE_FRAME_EXIT      = 1,
    RRC_NAS_AMR_SILENCE_FRAME_INDEX     = 8,
    RRC_NAS_AMR_NODATA_INDEX            = 9,
    RRC_NAS_AMR_MODE_BUTT
};
typedef VOS_UINT8 RRC_NAS_AMR_MODE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : RRC_NAS_AMR_RATE_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : AMR速率
*****************************************************************************/
enum RRC_NAS_AMR_RATE_TYPE_ENUM
{
    RRC_NAS_AMR_RATE_NULL               = 0x00,             /* 用于ASN.1解码，代码不使用 */
    RRC_NAS_AMR_RATE_4P75               = 0x01,             /* 4.75k */
    RRC_NAS_AMR_RATE_5P15               = 0x02,             /* 5.15k */
    RRC_NAS_AMR_RATE_5P9                = 0x04,             /* 5.90k */
    RRC_NAS_AMR_RATE_6P7                = 0x08,             /* 6.70k */
    RRC_NAS_AMR_RATE_7P4                = 0x10,             /* 7.40k */
    RRC_NAS_AMR_RATE_7P95               = 0x20,             /* 7.95k */
    RRC_NAS_AMR_RATE_10P2               = 0x40,             /* 10.2k */
    RRC_NAS_AMR_RATE_12P2               = 0x80,             /* 12.2k */
    RRC_NAS_AMR_RATE_BUTT

};
typedef VOS_UINT8 RRC_NAS_AMR_RATE_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : RRC_NAS_AMR_MODE_CFG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : AMR模式配置
*****************************************************************************/
enum RRC_NAS_AMR_MODE_CFG_ENUM
{
    RRC_NAS_AMR_MODE_SETUP              = 0,                /* 业务建立时配置 */
    RRC_NAS_AMR_MODE_MODIFY             = 1,                /* AMR模式修改时 */
    RRC_NAS_AMR_MODE_RESOURCE_IND       = 2,                /*SYSHO*/
    RRC_NAS_AMR_MODE_NO_CHANGE          = 3,                /* AMR模式未变化 */
    RRC_NAS_AMR_MODE_CFG_BUTT
};
typedef VOS_UINT8   RRC_NAS_AMR_MODE_CFG_ENUM_UINT8;

/*****************************************************************************
 枚举名    : GAS_RR_CHANNEL_MODE
 协议表格  :
 ASN.1描述 :
 枚举说明  : AMR信道模式
*****************************************************************************/
enum GAS_RR_CHANNEL_MODE
{
    RR_CHAN_MOD_SINGAL_ONLY,    /* 仅信令模式*/
    RR_CHAN_MOD_FR,             /* Full Rate */
    RR_CHAN_MOD_EFR,            /* Enhanced Full Rate  */
    RR_CHAN_MOD_AFS,            /* Enhanced Full Rate  */
    RR_CHAN_MOD_CSD_2400,
    RR_CHAN_MOD_CSD_4800,
    RR_CHAN_MOD_CSD_9600,
    RR_NAS_DATA_CSD_14400,
    RR_CHAN_MOD_HR,             /* half Rate */
    RR_CHAN_MOD_AHR,             /* half Rate */
    RR_CHAN_MOD_H24,            /* Adaptive Multi-Rate */
    RR_CHAN_MOD_H48,            /* Adaptive Multi-Rate */
    RR_CHAN_MOD_WFS,            /* Adaptive Multi-Rate,WFS业务 */
    RR_CHAN_MOD_BUF
};
typedef VOS_UINT8  NAS_RR_CHANNEL_MODE_ENUM_U8;

/*****************************************************************************
 枚举名    : RRMM_GMM_PROC_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : GMM启动过程描述
*****************************************************************************/
enum RRMM_GMM_PROC_TYPE_ENUM
{
    RRMM_GMM_PROC_TYPE_ATTACH        = 0, /*注册, 包括单独PS注册和组合注册*/
    RRMM_GMM_PROC_TYPE_NORMAL_RAU    = 1, /*正常路由区更新,包含单独PS路由区更新和组合路由区更新*/
    RRMM_GMM_PROC_TYPE_PERIOD_RAU    = 2, /*周期性路由区更新,包含单独PS路由区更新和组合路由区更新*/
    RRMM_GMM_PROC_TYPE_INVALID       = 3  /*无效的类型*/
};

typedef VOS_UINT16 RRMM_GMM_PROC_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RRMM_GMM_PROC_FLAG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : GMM过程类型描述
*****************************************************************************/
enum RRMM_GMM_PROC_FLAG_ENUM
{
    RRMM_GMM_PROC_FLAG_START       = 0, /*注册, 包括单独PS注册和组合注册*/
    RRMM_GMM_PROC_FLAG_FINISH      = 1, /*正常路由区更新,包含单独PS路由区更新和组合路由区更新*/
    RRMM_GMM_PROC_FLAG_INVALID     = 2  /*无效值*/
};
typedef VOS_UINT16 RRMM_GMM_PROC_FLAG_ENUM_UINT16;

/*****************************************************************************
 结构名    : RRMM_GMM_PROC_CONN_TYPE_ENUM
 结构说明  : GPRS连接类型
 1.日    期   : 2014年5月22日
   作    者   : w00242748
   修改内容   : 新建
*****************************************************************************/
enum RRMM_GMM_PROC_CONN_TYPE_ENUM
{
    RRMM_GMM_PROC_CONN_TYPE_NO_CONN               = 0, /* no conn */
    RRMM_GMM_PROC_CONN_TYPE_ATTACH_SIG_CONN       = 1, /* attach sig conn */
    RRMM_GMM_PROC_CONN_TYPE_RAU_SIG_CONN          = 2, /* rau sig conn */
    RRMM_GMM_PROC_CONN_TYPE_PS_SERVICE_CONN       = 3, /* ps service conn */
    RRMM_GMM_PROC_CONN_TYPE_BUTT                  = 4  /*无效值*/
};
typedef VOS_UINT16 RRMM_GMM_PROC_CONN_TYPE_ENUM_UINT16;




/*****************************************************************************
 枚举名    : GRR_NAS_SYNC_CHANNAL_MODE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : GSM信道模式描述
*****************************************************************************/
enum GRR_NAS_SYNC_CHANNAL_MODE_ENUM
{
    RR_NAS_SIGNALLING_ONLY,
    RR_NAS_SPEECH_V1,
    RR_NAS_SPEECH_V2,
    RR_NAS_SPEECH_V3,
    RR_NAS_DATA_9600,
    RR_NAS_DATA_4800,
    RR_NAS_DATA_2400,
    RR_NAS_DATA_14400
};
typedef VOS_UINT8 GRR_NAS_SYNC_CHANNAL_MODE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : GRR_NAS_SYNC_TCH_RATE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : GSM信道数率描述
*****************************************************************************/
enum GRR_NAS_SYNC_TCH_RATE_ENUM
{
    RR_NAS_TCH_FULL_RATE,
    RR_NAS_TCH_HALF_RATE
};
typedef VOS_UINT8 GRR_NAS_SYNC_TCH_RATE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : RR_NAS_SYNC_REASON_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 信道变化原因
*****************************************************************************/
enum RR_NAS_SYNC_REASON_ENUM
{
    /*  reasons mapped from rr_sync_ind */
    RR_NAS_GSM_RES_ASSIGNED,
    RR_NAS_GSM_CHANNEL_MODE_MODIFIED,
    RR_NAS_GSM_GSM_HANDOVER,
    RR_NAS_WCDMA_GSM_HANDOVER,

    /*  reasons mapped from rrc_sync_ind */
    RR_NAS_WCDMA_RAB_ESTABLISHED,
    RR_NAS_WCDMA_RAB_RELEASED,
    RR_NAS_WCDMA_RAB_RECONFIGURED,
    RR_NAS_GSM_WCDMA_HANDOVER
};
typedef VOS_UINT8 RR_NAS_SYNC_REASON_ENUM_UINT8;

/*****************************************************************************
 枚举名    : RRC_BG_PLMN_SEARCH_RLT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : BG搜索结果
*****************************************************************************/
enum RRC_BG_PLMN_SEARCH_RLT_ENUM
{
    RRC_BG_PLMN_SEARCH_RLT_SUCCESS            = 0,                /* 指定的PLMN搜索成功 */
    RRC_BG_PLMN_SEARCH_RLT_FAIL               = 1,                /* 接入层实际给DSP发起了搜网，但是搜索失败 */
    RRC_BG_PLMN_SEARCH_RLT_ABORT              = 2,                /* PLMN没有给DSP发起搜网，因为接入层当前状态不允许，搜索被终止 */
    RRC_BG_PLMN_SEARCH_RLT_BUTT
};
typedef VOS_UINT8  RRC_BG_PLMN_SEARCH_RLT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : RRC_NAS_SYS_SUBMODE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 驻留网络的接入技术枚举
*****************************************************************************/
/* 与WAS组贾长青确认,子模式发生变化时,必定会通过AT_MSG_IND消息上报 */
enum RRC_NAS_SYS_SUBMODE_ENUM
{
    RRC_NAS_SYS_SUBMODE_NULL                  = 0,                /* 无服务 */
    RRC_NAS_SYS_SUBMODE_GSM                   = 1,                /* GSM模式 */
    RRC_NAS_SYS_SUBMODE_GPRS                  = 2,                /* GPRS模式 */
    RRC_NAS_SYS_SUBMODE_EDGE                  = 3,                /* EDGE模式 */
    RRC_NAS_SYS_SUBMODE_WCDMA                 = 4,                /* WCDMA模式 */
    RRC_NAS_SYS_SUBMODE_HSDPA                 = 5,                /* HSDPA模式 */
    RRC_NAS_SYS_SUBMODE_HSUPA                 = 6,                /* HSUPA模式 */
    RRC_NAS_SYS_SUBMODE_HSDPA_HSUPA           = 7,                /* HSDPA+HSUPA模式 */
    RRC_NAS_SYS_SUBMODE_LTE                   = 8,                /* LTE模式 */
    RRC_NAS_SYS_SUBMODE_BUTT
};
typedef VOS_UINT8  RRC_NAS_SYS_SUBMODE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : RRC_NAS_SYS_INFO_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : sys info 的类型
*****************************************************************************/
enum RRC_NAS_SYS_INFO_TYPE_ENUM
{
    RRC_NAS_SYS_INFO_TYPE_OTA                 = 0,                /* 当前是ota */
    RRC_NAS_SYS_INFO_TYPE_SYS                 = 1,                /* 当前是系统消息 */
    RRC_NAS_SYS_INFO_TYPE_BUTT
};
typedef VOS_UINT8  RRC_NAS_SYS_INFO_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : RRC_NAS_LTE_CAPABILITY_STATUS_ENUM
 结构说明  : NAS_COMM_INFO_STRU enLCapabilityStatus取值
 1.日    期: 2011年10月25日
   作    者: w00176964
   修改内容: 增加信元标识LTE特性是否可用
*****************************************************************************/
enum RRC_NAS_LTE_CAPABILITY_STATUS_ENUM
{
    RRC_NAS_LTE_CAPABILITY_STATUS_DISABLE                   = 0,                        /* LTE特性不可用,例如L下联合注册被拒#7 */
    RRC_NAS_LTE_CAPABILITY_STATUS_REENABLE                  = 1,                        /* LTE特性恢复可用 */
    RRC_NAS_LTE_CAPABILITY_STATUS_BUTT
};
typedef VOS_UINT32 RRC_NAS_LTE_CAPABILITY_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_NAS_RAT_CAPABILITY_STATUS_ENUM
 结构说明  : NAS_COMM_INFO_STRU 的网络制式能力
 1.日    期: 2013年11月01日
   作    者: l00208543
   修改内容: 新增
*****************************************************************************/
enum RRC_NAS_RAT_CAPABILITY_STATUS_ENUM
{
    RRC_NAS_RAT_CAPABILITY_STATUS_DISABLE                   = 0,                        /* RAT特性不可用 */
    RRC_NAS_RAT_CAPABILITY_STATUS_REENABLE                  = 1,                        /* RAT特性恢复可用 */
    RRC_NAS_RAT_CAPABILITY_STATUS_BUTT
};
typedef VOS_UINT8 RRC_NAS_RAT_CAPABILITY_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : RRC_NAS_CS_TRANSACTION_ENUM
 结构说明  : RRC_NAS_CS_TRANSACTION_ENUM_UINT8 enCsTransactionType取值
 1.日    期: 2012年02月06日
   作    者: g00166634
   修改内容: 增加CSFB特性，WAS在重定向过程中，向NAS查询是否当前为CSFB流程
 2.日    期: 2012年11月12日
   作    者: s46746
   修改内容: 修改为查询cs业务类型
*****************************************************************************/
enum RRC_NAS_CS_TRANSACTION_ENUM
{
    RRC_NAS_CS_TRANSACTION_NO_EXIST                   = 0,                         /* 不存在CSFB 流程 */
    RRC_NAS_CS_TRANSACTION_MO_NORMAL_EXIST            = 1,                         /* 存在CSFB 正常业务(CC/SS)流程 */
    RRC_NAS_CS_TRANSACTION_EMERGENCY_EXIST            = 2,                         /* 存在CSFB 紧急呼叫流程 */
    RRC_NAS_CS_TRANSACTION_MT_EXIST                   = 3,                         /* 存在CSFB 被叫流程 */
    RRC_NAS_CS_TRANSACTION_BUTT
};
typedef VOS_UINT8 RRC_NAS_CS_TRANSACTION_ENUM_UINT8;

/*****************************************************************************
 枚举名    : RRC_NAS_UTRAN_MODE_ENUM_UINT8
 结构说明  : MS当前具体的UTRAN模式:WCDMA/TD-SCAMA
 1.日    期   : 2012年7月27日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
enum RRC_NAS_UTRAN_MODE_ENUM
{
    RRC_NAS_UTRAN_MODE_FDD          = 0,     /* 当前工作模式为WCDMA */
    RRC_NAS_UTRAN_MODE_TDD          = 1,     /* 当前工作模式为TDSCDMA */
    RRC_NAS_UTRAN_MODE_NULL         = 2,     /* CL模式下工作模式 */
    RRC_NAS_UTRAN_MODE_BUTT
};
typedef VOS_UINT8  RRC_NAS_UTRAN_MODE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : RRC_NAS_COVERAGE_TYPE_ENUM
 结构说明  : RRMM_PLMN_SEARCH_CNF_STRU消息中的enCoverageType
*****************************************************************************/
enum RRC_NAS_COVERAGE_TYPE_ENUM
{
    RRC_NAS_COVERAGE_TYPE_NONE              = 0,                                /* 无网络覆盖 */
    RRC_NAS_COVERAGE_TYPE_LOW               = 1,                                /* 有低质量网络覆盖*/
    RRC_NAS_COVERAGE_TYPE_HIGH              = 2,                                /* 有高质量网络覆盖 */
    RRC_NAS_COVERAGE_TYPE_BUTT
};
typedef VOS_UINT32  RRC_NAS_COVERAGE_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_NAS_NET_SCAN_RESULT_ENUM
 结构说明  : RRC_NAS_NET_SCAN_CNF消息中的enResult;
*****************************************************************************/
enum RRC_NAS_NET_SCAN_RESULT_ENUM
{
    RRC_NAS_NET_SCAN_RESULT_SUCCESS        = 0,
    RRC_NAS_NET_SCAN_RESULT_FAILURE        = 1,
    RRC_NAS_NET_SCAN_RESULT_BUTT
};
typedef VOS_UINT8  RRC_NAS_NET_SCAN_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : RRC_NAS_NET_SCAN_CAUSE_ENUM
 结构说明  : 接入层回复NAS扫描失败原因，如果当前没有任何模式驻留，NAS直接回复AT失败
 1.日    期   : 2013年8月24日
   作    者   : sunxibo
   修改内容   : 新建结构体
*****************************************************************************/
enum RRC_NAS_NET_SCAN_CAUSE_ENUM
{
    RRC_NAS_NET_SCAN_CAUSE_SIGNAL_EXIST = 0,                /* 存在信令连接，NAS回复AT稍后再尝试 */
    RRC_NAS_NET_SCAN_CAUSE_STATE_NOT_ALLOWED,               /* 当前状态不允许，NAS回复AT稍后再尝试 */
    RRC_NAS_NET_SCAN_CAUSE_FREQ_LOCK,                       /* 当前锁频状态，NAS回复AT失败 */
    RRC_NAS_NET_SCAN_CAUSE_PARA_ERROR,                      /* 参数错误，包含接入技术不支持，频段不支持，频点个数错误，门限错误，NAS回复AT失败 */

    RRC_NAS_NET_SCAN_CAUSE_BUTT
};
typedef VOS_UINT8 RRC_NAS_NET_SCAN_CAUSE_ENUM_UINT8;

/*******************************************************************************
 枚举名    : RRC_NAS_NCELL_STATE_ENUM
 结构说明  : 邻区状态枚举
 1.日    期   : 2014年01月02日
   作    者   : y00142674
   修改内容   : 创建，for V9R1_SVLTE
*******************************************************************************/
enum RRC_NAS_NCELL_STATE_ENUM
{
    RRC_NAS_NCELL_STATE_NULL    = 0x00,                                         /* 既没有TD的邻区，也没有4G邻区 */
    RRC_NAS_NCELL_STATE_3G      = 0x01,                                         /* 只有TD的邻区 */
    RRC_NAS_NCELL_STATE_4G      = 0x02,                                         /* 只有4G的邻区 */
    RRC_NAS_NCELL_STATE_3G4G    = 0x03,                                         /* 既有TD的邻区，也有4G邻区 */
    RRC_NAS_NCELL_STATE_BUTT

};
typedef VOS_UINT8 RRC_NAS_NCELL_STATE_ENUM_UINT8;

/*******************************************************************************
 枚举名    : NAS_GAS_MS_CAP_TYPE_ENUM_UINT8
 结构说明  : MS能力类型枚举
 1.日    期   : 2014年01月02日
   作    者   : w00146666
   修改内容   : 创建，for Disable lte fdd in china
*******************************************************************************/
enum NAS_GAS_MS_CAP_TYPE_ENUM
{
    NAS_GAS_MS_CAP_TYPE_UTRAN_FDD_RAC = 0x00,           /* UTRAN FDD下获取MS G模RAC */
    NAS_GAS_MS_CAP_TYPE_UTRAN_TDD_RAC,                  /* UTRAN TDD下获取MS G模RAC */
    NAS_GAS_MS_CAP_TYPE_CLASSMARK,                      /* 获取MS CLASSMARK */
    NAS_GAS_MS_CAP_TYPE_BUTT
};
typedef VOS_UINT8 NAS_GAS_MS_CAP_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名: RRMM_FFT_SCAN_TYPE_ENUM_UINT8
 协议格式:
 ASN.1描述:
 枚举说明:
*****************************************************************************/
enum RRMM_FFT_SCAN_TYPE_ENUM
{
    RRMM_FFT_SCAN_TYPE_NONE     = 0,                 /* 无网络覆盖 */
    RRMM_FFT_SCAN_TYPE_LOW      = 1,                 /* 有质量网络覆盖   */
    RRMM_FFT_SCAN_TYPE_HIGH     = 2,                 /* 有高质量网络覆盖 */
    RRMM_FFT_SCAN_TYPE_BUTT
};
typedef VOS_UINT8  RRMM_FFT_SCAN_TYPE_ENUM_UINT8;

/*******************************************************************************
 枚举名    : NAS_LAU_TYPE_ENUM
 结构说明  : LAU类型
 1.日    期   : 2015年05月12日
   作    者   : j00174725
   修改内容   : DTS2015040705043
*******************************************************************************/
enum NAS_LAU_TYPE_ENUM
{
    NAS_LAU_TYPE_NORMAL_LAU             = 0,
    NAS_LAU_TYPE_PERIOD_LAU,
    NAS_LAU_TYPE_IMSI_ATTACH,

    NAS_LAU_TYPE_BUTT

};
typedef VOS_UINT8 NAS_LAU_TYPE_ENUM_UINT8;

/*******************************************************************************
 枚举名    : NAS_ADDITION_UPDATE_PARA_ENUM
 结构说明  : LAU参数类型
 1.日    期   : 2015年05月12日
   作    者   : j00174725
   修改内容   : DTS2015040705043
*******************************************************************************/
enum NAS_ADDITION_UPDATE_PARA_ENUM
{
    NAS_ADDITION_UPDATE_PARA_NONE       = 0,
    NAS_ADDITION_UPDATE_PARA_MO,
    NAS_ADDITION_UPDATE_PARA_MT,
    NAS_ADDITION_UPDATE_PARA_MO_MT,

    NAS_ADDITION_UPDATE_PARA_BUTT

};
typedef VOS_UINT8 NAS_ADDITION_UPDATE_PARA_ENUM_UINT8;

/*******************************************************************************
 枚举名    : RRMM_TRANSACTION_STATUS_ENUM
 结构说明  : LAU参数类型
 1.日    期   : 2015年06月01日
   作    者   : j00174725
   修改内容   : DTS2015053000044
*******************************************************************************/
enum RRMM_TRANSACTION_STATUS_ENUM
{
    RRMM_TRANSACTION_CONNECTION_EST_SUCC       = 0,
    RRMM_TRANSACTION_FAIL,

    RRMM_TRANSACTION_BUTT

};
typedef VOS_UINT8 RRMM_TRANSACTION_STATUS_ENUM_UINT8;

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
/* 7.1.1 消息 RRMM_PLMN_SEARCH_REQ 的结构体 */
typedef struct
{
    VOS_UINT32                          ulMcc;              /* MCC,3 bytes      */
    VOS_UINT32                          ulMnc;              /* MNC,2 or 3 bytes */
}RRC_PLMN_ID_STRU;

typedef struct
{
    RRC_PLMN_ID_STRU                    PlmnId;             /* PlMN标识       */
    VOS_UINT32                          ulForbLac;          /* 禁止注册区信息 */
}RRC_FORB_LA_STRU;

/*******************************************************************************
 结构名    : RRMM_NCELL_INFO_STRU
 结构说明  : GSM下TDS邻区的频点列表和G驻留网络等效plmn信息

 1.日    期   : 2013年12月16日
   作    者   : z00161729
   修改内容   : 新生成结构

*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTdsArfcnNum;                          /* 0表示TDD频点不存在 */
    VOS_UINT8                           ucEplmnIdNum;                           /* PLMN ID个数 */

    VOS_UINT16                          ausTdsArfcnList[RRC_NAS_TDS_ARFCN_MAX_NUM];
    RRC_PLMN_ID_STRU                    astEplmnIdList[RRC_MAX_EQUPLMN_NUM];    /* 邻区相关等效PlMN标识 */
}RRMM_NCELL_INFO_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头    */     /*_H2ASN_Skip*/
    RRC_PLMN_SEARCH_TYPE_ENUM_UINT32    ulSearchType;       /* 搜索类型  */

    VOS_UINT32                          ulPlmnIdNum;        /* PLMN ID个数 */
    RRC_PLMN_ID_STRU                    aPlmnIdList[RRC_MAX_EQUPLMN_NUM];       /* PlMN标识 */
    VOS_UINT32                          ulForbLaNum;        /* 禁止注册区的个数 */
    RRC_FORB_LA_STRU                    aForbLaList[RRC_MAX_FORBLA_NUM];        /* 禁止注册区列表                           */

    RRMM_NCELL_INFO_STRU                stNcellInfo;
    /* Added by b00269685 for 自主FR优化, 2014-10-15, begin */
    PS_BOOL_ENUM_UINT8                  enCsfbFlg;          /* 本次搜网流程是否CSFB发起的 */
    RRMM_FFT_SCAN_TYPE_ENUM_UINT8       enFftScanType;      /* FFT搜网类型,目前仅在spec搜网和获取地理信息中有用 */
    PS_BOOL_ENUM_UINT8                  enPlmnInfoCampFlg;  /* 只是上报plmn是否需要满足驻留准则,目前仅在获取地理信息中可能会填写PS_FALSE,默认是PS_TRUE */

    VOS_UINT8                           aucReserve[1];
    /* Added by b00269685 for 自主FR优化, 2014-10-15, end */

}RRMM_PLMN_SEARCH_REQ_STRU;

/* 7.1.2 消息 RRMM_PLMN_SEARCH_CNF 的结构体 */
typedef struct
{
    RRC_PLMN_ID_STRU                stPlmnId;
    RRC_NAS_RAT_TYPE_ENUM_UINT32    ulRat;    /* 支持的接入技术 */
}RRMM_PLMN_WITH_RAT_STRU;

/* ulSearchRlt取值 */
typedef struct
{
    RRMM_PLMN_WITH_RAT_STRU             PlmnId;             /* PLMN ID    */
    VOS_INT32                           lRscp;              /* RSCP测量值 */
}RRC_LOW_PLMN_INFO_STRU;

typedef struct
{
    RRC_NAS_RAT_TYPE_ENUM_UINT32             enRat;                            /* 搜索的接入技术 */
    RRC_NAS_RAT_LIST_SEARCH_RSLT_ENUM_UINT32 enListSearchRlt;                  /* 接入技术LIST搜索完成结果 */
}RRC_LIST_SEARCH_RAT_INFO_STRU;

typedef struct
{
    VOS_UINT32                          ulHighPlmnNum;                          /* 高质量PLMN的个数 */
    RRMM_PLMN_WITH_RAT_STRU             aHighPlmnList[RRC_MAX_HIGH_PLMN_NUM];   /* 高质量PLMN列表   */
    VOS_UINT32                          ulLowPlmnNum;                           /* 低质量PLMN的个数 */
    RRC_LOW_PLMN_INFO_STRU              aLowPlmnList[RRC_MAX_LOW_PLMN_NUM];     /* 低质量PLMN列表   */
}RRC_PLMN_ID_LIST_STRU;

/*******************************************************************************
 结构名    : RRMM_PLMN_CSG_ID_WITH_RAT_STRU
 结构说明  :

*******************************************************************************/
typedef struct
{
    RRMM_PLMN_WITH_RAT_STRU             stPlmnWithRat;
    VOS_UINT32                          ulCsgId;
}RRMM_PLMN_CSG_ID_WITH_RAT_STRU;

/*******************************************************************************
 结构名    : RRMM_CSG_ID_HOME_NODEB_NAME_STRU
 结构说明  :

*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHomeNodeBNameLen;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucHomeNodeBName[RRC_NAS_MAX_HOME_NODEB_NAME_LEN];
}RRMM_CSG_ID_HOME_NODEB_NAME_STRU;


/*****************************************************************************
 结构名    : RRMM_CSG_LIST_SEARCHED_PLMN_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : csg list搜网结果中高低质量网络信息数据结构
*****************************************************************************/
typedef struct
{
    RRMM_PLMN_CSG_ID_WITH_RAT_STRU      stPlmnCsgIdWithRat;
    RRMM_CSG_ID_HOME_NODEB_NAME_STRU    stHomeNodeBName;
    VOS_INT32                           lRscp;                   /* RSCP测量值 */
}RRMM_CSG_LIST_SEARCHED_PLMN_INFO_STRU;


/*****************************************************************************
 结构名    : RRMM_CSG_LIST_SEARCHED_RESULT_STRU
 结构说明  : csg列表搜网结果信息
 1.日    期   : 2015年9月2日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                 ulTotalPlmnNum; /* 高低质量PLMN总个数 */
    VOS_UINT32                                 ulHighPlmnNum;  /* 高质量PLMN的个数 */

    /* 高低质量PLMN列表   */
    RRMM_CSG_LIST_SEARCHED_PLMN_INFO_STRU     astCsgListSearchedPlmnInfoList[RRC_NAS_MAX_PLMN_CSG_ID_NUM];
}RRMM_CSG_LIST_SEARCHED_RESULT_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头   */      /*_H2ASN_Skip*/
    RRC_PLMN_SEARCH_RLT_ENUM_UINT32     ulSearchRlt;        /* 搜索结果 */
    RRC_NAS_COVERAGE_TYPE_ENUM_UINT32   enCoverageType;     /* RRC在当前接入技术下的网络覆盖类型 */
    RRC_LIST_SEARCH_RAT_INFO_STRU       astSearchRatInfo[NAS_RRC_MAX_RAT_NUM];     /* 记录接入层本次已经搜索的接入技术信息，仅在列表搜索时有效 */
    RRC_PLMN_ID_LIST_STRU               PlmnIdList;         /* 上报的PLMN ID列表 */
}RRMM_PLMN_SEARCH_CNF_STRU;

/* 7.1.3 消息 RRMM_PLMN_LIST_IND 的结构体 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头        */ /*_H2ASN_Skip*/
    RRC_PLMN_ID_LIST_STRU               PlmnIdList;         /* 上报的PLMN ID列表 */
}RRMM_PLMN_LIST_IND_STRU;

/* 7.1.4 消息 RRMM_EQU_PLMN_NOTIFY_REQ 的结构体 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头         */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulEquPlmnNum;                           /* 等效的PLMN的个数 */
    RRC_PLMN_ID_STRU                    aEquPlmnIdList[RRC_MAX_EQUPLMN_NUM];    /* 等效的PLMNID列表 */
} RRMM_EQU_PLMN_NOTIFY_REQ_STRU;

/* 7.1.5 消息 RRMM_AREA_LOST_IND 的结构体,NAS在任何情况下都会响应这条丢网指示 */
typedef struct
{
    VOS_UINT8                           ucHistorySearchedFlg;                       /* 是否进行过history搜 */
    VOS_UINT8                           ucPrefBandSearchedFlg;                      /* 是否进行过pref band搜 */
    VOS_UINT8                           ucSpecSearchedFlg;                          /* 是否进行过spec搜 */
    VOS_UINT8                           ucReserve;
}RRMM_SEARCHED_TYPE_STRU;

/* ulRptMode取值 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头   */      /*_H2ASN_Skip*/
    RRC_NAS_AREA_LOST_ENUM_UINT32       ulRptMode;          /* 报告模式 */
    RRC_PLMN_ID_LIST_STRU               PlmnIdList;         /* 上报的PLMN ID列表 */ /* 新增，带有PLMN 信息时，需要到G去搜网；没有则按以前的流程处理 */
    RRMM_SEARCHED_TYPE_STRU             stSearchedType;     /* AS上报丢网时已经搜索过类型 */
}RRMM_AREA_LOST_IND_STRU;



typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头         */      /*_H2ASN_Skip*/
    RRC_LIMIT_CAMP_ACTION_ENUM_UINT32   enLimitCampAction;  /* 限制服务的过程:开始或者结束  */
    VOS_UINT32                          ulServiceAvailFlag; /* 当前是否服务可用 VOS_TRUE 服务可用 VOS_FALSE 服务不可用   */
    RRC_RRC_CONN_STATUS_ENUM_UINT32     enRrcConnStatus;    /* RRC_RRC_CONN_STATUS_PRESENT:连接态;RRC_RRC_CONN_STATUS_ABSENT:非连接态 */
    RRC_PLMN_ID_LIST_STRU               stPlmnIdList;    /* 上报的W/G/L PLMN ID列表 */
}RRMM_LIMIT_SERVICE_CAMP_IND_STRU;


/***********************新增接口MMC－>AS**************************/
/* 7.1.6 消息RRMM_PLMN_SEARCH_STOP_REQ的结构体 */
/******************************************************************************
    说明：AS接收到此消息后,如果正在进行PLMN搜索,则停止进行PLMN搜索,
    并向MMC发送停止确认消息,如果没有进行,直接向MMC发送停止确认消息。
******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* 保留   */
}RRMM_PLMN_SEARCH_STOP_REQ_ST;

/***********************新增接口AS－>MMC**************************/
/* 7.1.7 消息 RRMM_PLMN_SEARCH_STOP_CNF的结构体 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* 保留 */
}RRMM_PLMN_SEARCH_STOP_CNF_ST;

/***********************修改接口MMC－>AS**************************/
/* 7.1.8 消息 RRMM_START_REQ 的结构体 */
/******************************************************************************
    说明：
    如果是双模，NAS向WRRC和RR同时发送这条消息，WRRC和RR判断其中的ulRat为双模，
    可以执行异系统测量、切换、异系统小区重选等操作。
    如果是单模，NAS只向其中一方发送这条消息，接收方判断ulRat为单模，
    则不再执行异系统相关的操作，作为一个单模AS层运行。
    AS层收到这条消息后，完成自身的初始化，之后处于待命状态，
    等待NAS的第一条消息为：RRMM_PLMN_SEARCH_REQ，
    只有接收这条消息后才能处理其他的NAS的消息。
    RRMM_PLMN_SEARCH_REQ这条消息NAS将视为将AS由待命状态调度到工作状态的一条消息。

 1.日    期   : 2011年7月17日
   作    者   : w00167002
   修改内容   : 修改结构体: 开机消息结构体的更改,通知接入层的接入技术更改为数组形式通知
 2.日    期   : 2012年8月30日
   作    者   : w00176964
   修改内容   : 修改结构体: GUTL PhaseII修改:增加UTRAN MODE通知
******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头     */    /*_H2ASN_Skip*/
    RRC_NAS_SIM_STATUS_ENUM_UINT32      ulSimStatus;        /* SIM卡状态              */
    RRMM_RAT_PRIO_ENUM_UINT8            aucRatPrioList[RRMM_RAT_TYPE_BUTT];     /* 各模的优先级 */
    RRC_NAS_UTRAN_MODE_ENUM_UINT8       enUtranMode;                            /* 当前UTRAN的工作模式:0---FDD 1---TDD */

    /* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
    VOS_UINT8                           aucReserve1[2];     /* 保留 */
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, End */
}RRMM_START_REQ_STRU;

/* 7.1.9 消息 RRMM_START_CNF 的结构体 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头   */      /*_H2ASN_Skip*/
    MMC_START_RESULT_ENUM_UINT32        ulResult;           /* 启动结果 */
}RRMM_START_CNF_STRU;

/* 7.1.10 消息 RRMM_CELL_SELECTION_CTRL_REQ 的结构体 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头       */  /*_H2ASN_Skip*/
    RRC_NAS_RESEL_TYPE_ENUM_UINT32      ulReselectInd;      /* 重选控制指示 */
    VOS_UINT32                          ulForbLaNum;        /* 禁止注册区的个数 */
    RRC_FORB_LA_STRU                    aForbLaList[RRC_MAX_FORBLA_NUM];        /* 禁止注册区列表 */
}RRMM_CELL_SELECTION_CTRL_REQ_STRU;

typedef struct
{
    VOS_UINT32                          ulNasMsgSize;       /* [1,RRC_NAS_MAX_SIZE_NAS_MSG],Byte */
    VOS_UINT8                           aucNasMsg[4];       /*_H2ASN_Replace   L3Message aucNasMsg; */
}NAS_MSG_STRU;


typedef struct
{
    MSG_HEADER_STRU                      MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT32                           ulOpId;             /* 操作标识                                 */
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32   ulCnDomainId;       /* CN Domain ID                             */
    RRC_NAS_EST_CAUSE_ENUM_UINT32        ulEstCause;         /* RRC Connection Req原因，取值见枚举定义 */
    RRC_NAS_CALL_TYPE_ENUM_UINT32        enCallType;         /* RRC Connection Req 业务类型 */
    RRC_NAS_IDNNS_TYPE_ENUM_UINT32       ulIdnnsType;        /* Intra domain nas node selector类型，取值见枚举定义 */
    NAS_RRC_SPLMN_SAME_RPLMN_ENUM_UINT32 enSplmnSameRplmn;   /* NAS指示接入层选择的plmn和Rplmn是否相同   */
    RRC_PLMN_ID_STRU                     stPlmnId;           /* 本小区PLMN ID              */
    NAS_MSG_STRU                         FisrtNasMsg;        /* 该CN Domain的第一个NAS消息               */
}RRMM_EST_REQ_STRU;

/* 7.1.12 消息 RRMM_EST_CNF 的结构体 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头   */      /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;             /* 操作标识 */
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  ulCnDomainId;       /* CN Domain ID    */
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult;           /* 该信令连接建立结果，取值见枚举定义 */
}RRMM_EST_CNF_STRU;

/* 7.1.13 消息 RRMM_DATA_REQ 的结构体 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  ulCnDomainId;       /* CN Domain ID                             */
    RRC_NAS_MSG_PRIORTY_ENUM_UINT32     ulPriorityInd;      /* 消息优先级指示，取值见枚举定义 */
    NAS_MSG_STRU                        SendNasMsg;         /* 该域需要发送的NAS消息          */
}RRMM_DATA_REQ_STRU;

/* 7.1.14 消息 RRMM_DATA_IND 的结构体 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  ulCnDomainId;       /* CN Domain ID                             */
    NAS_MSG_STRU                        RcvNasMsg;
}RRMM_DATA_IND_STRU;

/* 7.1.15 消息 RRMM_REL_REQ 的结构体 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  ulCnDomainId;       /* CN Domain ID                             */
    RRC_CELL_BAR_ENUM_UINT32            enBarValidFlg;      /* 当前小区或激活集小区是否被阻塞，取值见枚举定义 */
}RRMM_REL_REQ_STRU;

/*****************************************************************************
 结构名    : RRMM_REL_CS_PS_ALL_CONN_REQ_STRU
 结构说明  : svlte特性开启，ps detach时如果存在连接通过该原语通知tds释放所有cs ps连接
 1.日    期   : 2014年3月22日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;          /* 消息头    */   /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve[4];
}RRMM_REL_CS_PS_ALL_CONN_REQ_STRU;



/*****************************************************************************
 结构名    : RRMM_SERVICE_ABORT_NOTIFY_STRU
 结构说明  : cs业务终止指示
 1.日    期   : 2014年5月22日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;          /* 消息头    */   /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve[4];
}RRMM_SERVICE_ABORT_NOTIFY_STRU;




/* 7.1.16 消息 RRMM_REL_IND 的结构体,NAS在任何情况下都会响应这条释放指示 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  ulCnDomainId;       /* CN Domain ID                             */
    RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus;    /* 释放信令连接后RRC连接是否存在，取值见枚举定义 */
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause;         /* 信令释放原因，取值见枚举定义                  */
}RRMM_REL_IND_STRU;

/* 7.1.17 消息 RRMM_ABORT_REQ 的结构体，删除与RRMM_REL_REQ_STRU合并 */

/* 7.1.18消息 RRMM_POWER_OFF_REQ 的结构体 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* 保留 */
}RRMM_POWER_OFF_REQ_STRU;

/* 7.1.19消息 RRMM_POWER_OFF_CNF 的结构体 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* 保留 */
}RRMM_POWER_OFF_CNF_STRU;

/* 7.1.20消息 RRMM_AC_INFO_CHANGE_IND 结构体 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_NAS_AC_TYPE_ENUM_UINT32         ulAcChangeInd;      /* AC阻塞状态发生改变 */
} RRMM_AC_INFO_CHANGE_IND_STRU;

/***********************新增接口AS－>MMC***************************/
/* 7.1.21 消息 RRMM_SUSPEND_IND 结构体 */
/******************************************************************************
1. 日    期: 2012年12月08日
   作    者: w00176964
   修改内容: 增加紧急业务限制信元以及修改变量名
******************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                 enRestrictPagingRsp;          /* 是否限制响应寻呼 */
    PS_BOOL_ENUM_UINT8                 enRestrictRegister;           /* 是否限制注册 */
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-10, begin */
    PS_BOOL_ENUM_UINT8                 enRestrictNormalService;      /* 是否限制正常业务 */
    PS_BOOL_ENUM_UINT8                 enRestrictEmergencyService;   /* 是否限制紧急业务 */
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-10, end */
}RRC_NAS_RESTRICTION_TYPE_STRU;

/* 7.1.20_1 消息 RRMM_W_AC_INFO_CHANGE_IND_STRU 结构体 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */    /*_H2ASN_Skip*/
    RRC_NAS_RESTRICTION_TYPE_STRU       stCsRestriction;    /* CS域接入是否受限 */
    RRC_NAS_RESTRICTION_TYPE_STRU       stPsRestriction;    /* PS域接入是否受限 */
} RRMM_W_AC_INFO_CHANGE_IND_STRU;

/***********************新增接口AS－>MMC***************************/
/* 7.1.21 消息 RRMM_SUSPEND_IND 结构体 */
typedef struct
{
    NAS_RRC_RE_TX_MSGTYPE_ENUM_UINT32   enReTxMsgType;
    VOS_UINT8                           aucNasReTxMsg[NAS_RRC_MAX_RE_TX_MSG_LENTH];
}NAS_RRC_RE_TX_MSG_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /*_H2ASN_Skip*/
    MMC_SUSPEND_CAUSE_ENUM_UINT8        ucSuspendCause;     /* 挂起原因 */
    MMC_SUSPEND_ORIGEN_UINT8            ucSuspendOrigen;    /* 消息发起方，RRMM_ORIGEN_GSM:GSM，RRMM_ORIGEN_WCDMA:WCDMA*/
    MMC_SUSPEND_DESTINATION_UINT8       ucSuspendDestination;/* 挂起的目的方 */
    VOS_UINT8                           aucReserve1[1];     /* 保留 */
    NAS_RRC_RE_TX_MSG_STRU              astReTxMsg[NAS_RRC_MAX_RE_TX_MSG_NUM];
}RRMM_SUSPEND_IND_ST;

/***********************新增接口MMC－>AS***************************/
/* 7.1.22 消息 RRMM_SUSPEND_RSP 结构体 */
/* 说明：如果NAS挂起失败，则NAS回到正常工作状态。*/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /*_H2ASN_Skip*/
    RRC_NAS_SUSPEND_RESULT_ENUM_UINT8   ucResult;           /*WRRC/RR需要处理挂起失败的情况，NAS在有些情况下挂起会失败*/
    VOS_UINT8                           aucReserve1[3];     /* 保留 */
} RRMM_SUSPEND_RSP_ST;

/***********************新增接口AS－>MMC***************************/
/* 7.1.23 消息 RRMM_RESUME_IND 结构体 */
/******************************************************************************
 1、对AS层要求:异系统间切换完成后，无论:(系统1->系统2)还是(系统1->系统2->系统1)，无论最终切换结果如何，
 AS层首先向MM子层发送恢复消息，然后后续处理为非切换状态时的正常流程处理，不能用恢复消息替代其他应该发送
 消息，否则导致NAS与AS状态不一致，恢复消息的含义仅仅是表明切换过程结束。

 2、对NAS层需求:NAS层根据切换结果做不同操作，见下面的取值说明

 ucCsResumeResult:
   存在Cs域业务时:
   MMC_RESUME_RESULT_SUCCESS--NAS认为CS域RR连接状态正常，能发送NAS CS直传消息
   MMC_RESUME_RESULT_FAILURE--NAS认为CS域RR连接失败，不能发送NAS CS直传消息，清空缓存的直传消息；
   不存在Cs域业务时:
   MMC_RESUME_RESULT_SUCCESS--NAS认为接入层驻留小区成功
   MMC_RESUME_RESULT_FAILURE--NAS认为接入层没有找到小区驻留；

 ucPsResumeResult:
   MMC_RESUME_RESULT_SUCCESS--2G->3G时，表示WRRC驻留成功，当前没有RR连接，GMM如果需要发送直传消息，
                                        使用RRMM_EST_REQ首先建立WRRC PS信令连接
                              3G->2G->3G时，表示WRRC驻留成功，GMM可以发送直传消息

                              3G->2G时，表示GRR驻留GPRS小区成功，GMM如果需要发送直传消息，
                                        TLLI，加密信息等传递给GRR、LLC后做完RA后发送直传消息
                              2G->3G->2G时，表示GRR驻留GPRS小区成功，GMM可以通过LLC发送GMM直传消息，
                                        TLLI，加密信息等无需传递给GRR、LLC，因为GRR、LLC有这些信息

   MMC_RESUME_RESULT_FAILURE--驻留失败，GMM挂起状态恢复，清空缓存的消息

   MMC_RESUME_GPRS_SUSPENSION-仅存在于异系统改变到2G,表示GPRS悬挂。
******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /*_H2ASN_Skip*/
    MMC_RESUME_RESULT_ENUM_UINT8        ucCsResumeResult;   /* CS域切换结果 */
    MMC_RESUME_RESULT_ENUM_UINT8        ucPsResumeResult;   /* PS域切换结果 */
    MMC_RESUME_ORIGEN_ENUM_UINT8        ucResumeOrigen;     /* 消息发起方，RRMM_ORIGEN_GSM:GSM，RRMM_ORIGEN_WCDMA:WCDMA */
    VOS_UINT8                           aucReserve1[1];     /* 保留 */
}RRMM_RESUME_IND_ST;


/***********************新增接口MMC－>AS***************************/
/* 7.1.24 消息 RRMM_RESUME_RSP 结构体 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* 保留 */
}RRMM_RESUME_RSP_ST;

/***********************新增接口MMC－>AS***************************/
/* 7.1.25 消息RRMM_SUSPEND_REQ 结构体 */
/******************************************************************************
说明：该消息功能是MMC发起挂起AS(GAS或WAS)层的操作请求。
   1）向谁发送消息，表示挂起哪个接入层实体；
   2）如果接入层接受挂起请求后，接入层不管处于何种状态，都将终止接入层所有
      的过程，转到接入层初始化后，等待PLMN搜索命令的状态。根据挂起
      类型，决定是否将当前接入层移出DSP，目的是保证不同接入模式的
      转换完成。目前MMC只使用了挂起时移出DSP的情况
   3）如果当前接入层拒绝挂起请求，MMC将保持当前的接入层，切换到不同接入层
      的操作失败，当前MMC状态不改变，可继续其他允许过程。
   4）从接入层挂起状态恢复，使用RRMM_PLMN_SEARCH_REQ消息，开始接入层的功能。
******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    MMC_AS_SUSPEND_STOP_ENUM_UINT8      ucStopCause;        /* 挂起停止方式         */
    VOS_UINT8                           aucReserve1[3];     /* 保留 */
}RRMM_SUSPEND_REQ_ST;

/***********************新增接口AS－>MMC***************************/
/* 7.1.26 消息 RRMM_SUSPEND_CNF 结构体 */
/******************************************************************************
说明：该消息是接入层（GAS或WAS）对RRMM_SUSPEND_REQ的回应确认。
   1）如果当前接入层接收NAS的挂起请求，ulResult值返回MMC_AS_SUSPEND_SUCCESS，
      接入层将终止当前的所有过程，回到接入层初始状态，等待NAS层唤醒。
   2）如果当前接入层拒绝NAS的挂起请求，ulResult值返回MMC_AS_SUSPEND_FAILURE，
      接入层保持现有状态，继续接收其他NAS层其他命令。
   3）NAS层在发出RRMM_SUSPEND_REQ后，是等待接入层的RRMM_SUSPEND_CNF消息的。
      如果收不到接入层的确认消息，NAS层MMC实体将一直等待。
******************************************************************************/

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    MMC_AS_SUSPEND_RESULT_ENUM_UINT8    ucResult;           /* 接入层挂起结果 */
    VOS_UINT8                           aucReserve1[3];     /* 保留 */
}RRMM_SUSPEND_CNF_ST;

/***********************新增接口MMC－>AS***************************/
/* 7.1.27 消息 RRMM_UICC_STATUS_CHANGE_IND 结构体 */
/******************************************************************************
说明：该消息是NAS层通知AS层（GAS或WAS）UICC状态，AS层根据该状态
      更新AS层与UICC相关的信息，ulSimStatus取值与7.1.8 消息 RRMM_START_REQ
      中SIM卡状态的枚举值相同
******************************************************************************/

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_NAS_SIM_STATUS_ENUM_UINT32      ulSimStatus;        /* SIM卡状态   */
}RRMM_UICC_STATUS_CHANGE_IND_ST;

/***********************新增接口AS－>MMC***************************/
/* 7.1.28 消息 RRMM_UICC_STATUS_CHANGE_RSP 结构体 */
/* 说明：该消息是AS层通知NAS层已经收到sim卡状态指示*/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    AS_UICC_STATUS_IND_RESULT_ENUM_UINT32   ulResult;       /* 收到SIM卡状态处理结果   */
}RRMM_UICC_STATUS_CHANGE_RSP_ST;


/* 7.2 WAS专用消息 */
/* 7.2.1 消息 RRMM_SYS_INFO_IND 的结构体 */


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/

    VOS_UINT32                          bitOpPlmnId     : 1;
    VOS_UINT32                          bitOpCsDrx      : 1;
    VOS_UINT32                          bitOpPsDrx      : 1;
    VOS_UINT32                          bitOpCellId     : 1;
    VOS_UINT32                          bitSpare        : 28;

    RRC_NAS_SYS_INFO_TYPE_ENUM_UINT8    enSysInfoType;
    VOS_UINT8                           aucReserve[3];

    RRC_PLMN_ID_STRU                    PlmnId;             /* 本小区PLMN ID              */

    VOS_UINT32                          ulCsDrxLength;      /* CS域DRX长度系数 */
    VOS_UINT32                          ulPsDrxLength;      /* PS域DRX长度系数 */
    VOS_UINT32                          ulCellId;           /* 当前驻留小区ID  */
    WCDMA_BAND_SET_UN                   unWcdmaBand;        /*_H2ASN_Replace WCDMA_BAND_STRU                     stWcdmaBitBand; */
    VOS_UINT8                           ucCnCommonSize;     /* CN Common信息的字节长度    */
    VOS_UINT8                           aucCnCommonInfo[RRC_NAS_MAX_SIZE_NAS_GSM_MAP];
    VOS_UINT8                           ucCsInfoSize;       /* CS域相关信息的字节长度     */
    VOS_UINT8                           aucCsInfo[RRC_NAS_MAX_SIZE_NAS_GSM_MAP];

    VOS_UINT8                           ucPsInfoSize;       /* PS域相关信息的字节长度     */
    VOS_UINT8                           aucPsInfo[RRC_NAS_MAX_SIZE_NAS_GSM_MAP];
    RRC_NAS_RESTRICTION_TYPE_STRU       stCsRestriction;    /* 对应PLMN ID CS域接入是否受限 */
    RRC_NAS_RESTRICTION_TYPE_STRU       stPsRestriction;    /* 对应PLMN ID PS域接入是否受限 */
    RRC_NAS_SYS_SUBMODE_ENUM_UINT8      enSysSubMode;       /* 当前小区的系统子模式 */
}RRMM_SYS_INFO_IND_STRU;


/* 7.2.2 消息 RRMM_PAGING_IND 的结构体 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  ulCnDomainId;       /* CN Domain ID                             */
    RRC_NAS_PAGING_TYPE_ENUM_UINT32     ulPagingType;       /* 寻呼消息类型，               */
    RRC_PAGE_CAUSE_ENUM_UINT32          ulPagingCause;      /* Paging Cause，               */
    RRC_PAGE_UE_ID_ENUM_UINT32          ulPagingUeId;       /* Paging Recorder Id，         */
}RRMM_PAGING_IND_STRU;

/* 7.2.3 消息 RRMM_SECURITY_IND 的结构体 */
typedef struct
{
     MSG_HEADER_STRU                    MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
     RRC_SECURITY_RPT_MODE_ENUM_UINT32  ulRptMode;          /* 报告模式                                 */
}RRMM_SECURITY_IND_STRU;

/* 7.2.4 消息 RRRABM_RAB_IND 的结构体 */
typedef struct
{
    VOS_UINT32                          ulRabId;            /* RAB ID             */
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  ulCnDomainId;       /* CN Domain ID                             */
    RRC_NAS_PDCP_EXIST_FLAG_ENUM_UINT32 enPdcpFlg;          /* 该RAB是否存在PDCP */
    VOS_UINT32                          ulRbNum;            /* 该RAB包含RB数量    */
    VOS_UINT32                          aulRbId[RRC_NAS_MAX_RB_PER_RAB];        /* 该RAB包含RB ID                           */
    WUE_RLC_MODE_ENUM_UINT8             aenUlRlcMode[RRC_NAS_MAX_RB_PER_RAB];    /* RB对应的RLC的UL模式，用于RABM环回时，给WTTF发送数据时判断 */
}RAB_INFO_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
    NAS_RRC_RAB_CHANGE_ENUM_UINT32      ulRabChangeType;    /* RAB的操作类型 */
    VOS_UINT32                          ulRabCnt;           /* 本次RAB操作的数量 */
    RAB_INFO_STRU                       aRabInfo[RRC_NAS_MAX_RAB_SETUP];
}RRRABM_RAB_IND_STRU;

typedef RRRABM_RAB_IND_STRU             RRRABM_HANDOVER_RAB_IND_STRU;

/* 7.2.5 消息 RRRABM_RAB_RSP 的结构体 */
typedef struct
{
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  enCnDomainId;       /* CN Domain ID                             */
    VOS_UINT32                          ulRabId;            /* RAB ID          */
    RRC_NAS_PPP_VALID_ENUM_UINT32       ulPppValid;         /* 是否采用PPP协议 */
    VOS_UINT32                          ulDeliveryErrSdu;
}RRRABM_RAB_INFO_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;             /* 与建立RAB的IND原语相同                   */
    VOS_UINT32                          ulRabCnt;           /* 建立RAB数量                              */
    RRRABM_RAB_INFO_STRU                aRabInfo[RRC_NAS_MAX_RAB_SETUP];
}RRRABM_RAB_RSP_STRU;

typedef RRRABM_RAB_RSP_STRU             RRRABM_HANDOVER_RAB_RSP_STRU;

/* 7.2.6 消息 RRMM_SYNC_IND 的结构体 */
/*****************************************************************************
 结构名    : RRC_NAS_AMR_MODE_IND_STRU
 结构说明  : AMR的速率配置，在速率修改时配置给NAS，
             并且通过enAmrModeCfgType通知NAS，
             AMR建立，AMR修改，AMR速率不变。
*****************************************************************************/
typedef struct
{
    RRC_NAS_AMR_MODE_ENUM_UINT8         enUlAmrMode;
    RRC_NAS_AMR_MODE_ENUM_UINT8         enDlAmrMode;
    VOS_UINT8                           ucUlAmrRateCnt;
    RRC_NAS_AMR_RATE_TYPE_ENUM_UINT8    aenUlAmrRate[RRC_NAS_MAX_AMR_RATE_NUM];
    VOS_UINT8                           ucDlAmrRateCnt;
    RRC_NAS_AMR_RATE_TYPE_ENUM_UINT8    aenDlAmrRate[RRC_NAS_MAX_AMR_RATE_NUM];
}RRC_NAS_AMR_MODE_IND_STRU;

/*****************************************************************************
 结构名    : RRMM_SYNC_INFO_STRU
 结构说明  : NAS同步指示，RRC在空口携带了SYNC信元时配置NAS。
             如果空口没有携带，则不配置NAS。
             ulRabCnt = 0表示没有携带。
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRabId;            /* RAB ID          */
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  ulCnDomainId;       /* CN Domain ID    */
    VOS_UINT8                           ucRabSyncInfo;      /* 该RAB的同步指示 */

    VOS_UINT8                           aucReserve1[3];     /* 保留 */
}RRMM_SYNC_INFO_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/

    VOS_UINT32                          ulRabCnt;           /* 需要同步RAB数量，0表示不配置 */
    RRMM_SYNC_INFO_STRU                 NasSyncInfo[RRC_NAS_MAX_RAB_SETUP];

    VOS_UINT8                           aucReserve1[3];     /* 保留 */
    RRC_NAS_AMR_MODE_CFG_ENUM_UINT8     enAmrModeCfgType;   /* AMR模式配置类型 */
    RRC_NAS_AMR_MODE_IND_STRU           stAmrModeInd;
}RRMM_SYNC_IND_STRU;

/* 7.2.7 消息 RRRABM_STATUS_IND 的结构体 */
typedef struct
{
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  enCnDomainId;       /* CN Domain ID    */
    VOS_UINT32                          ulRabId;            /* RAB ID        */
}RRRABM_STATUS_RAB_INFO_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT32                          ulRabCnt;           /* RAB数量 */
    RRRABM_STATUS_RAB_INFO_STRU         aRab[RRC_NAS_MAX_RAB_SETUP];
    RRC_RAB_STATUS_ENUM_UINT32          ulStatus;           /* RAB对应操作类型 */
}RRRABM_STATUS_IND_STRU;


/* 7.2.8 消息 RRRABM_QOS_UPDATE_REQ 的结构体 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT32                          ulRabCnt;           /* RAB数量                                  */
    RRRABM_RAB_INFO_STRU                aRab[RRC_NAS_MAX_RAB_SETUP];
}RRRABM_QOS_UPDATE_REQ_STRU;

/* 7.2.9 消息 RRMM_NAS_INFO_CHANGE_REQ 的结构体 */
typedef struct
{
    VOS_UINT8                           aucCk[RRC_NAS_CIPHER_KEY_LEN];          /* Cipher Key,存储格式参见31.102            */
    VOS_UINT8                           aucIk[RRC_NAS_INTEGRITY_KEY_LEN];       /* Integrity Key,存储格式参见31.102         */
}SECURITY_KEY_STRU;

typedef struct
{
    VOS_UINT8                           aucTmsi[RRC_NAS_TMSI_LEN];              /* 存储顺序参见24.008 10.5.1.4中的规定      */
    RRC_PLMN_ID_STRU                    stPlmnId;                               /* 存储顺序参见24.008 10.5.1.3中的规定，前3
                                                                                   个字节有效                               */
    VOS_UINT16                          usLac;                                  /* 存储顺序参见24.008 10.5.1.3中的规定，前2
                                                                                   个字节有效                               */
    VOS_UINT8                           aucReserve1[2];     /* 保留 */
}NAS_INFO_TMSI_LAI_STRU;

typedef struct
{
    VOS_UINT8                           aucPtmsi[RRC_NAS_PTMSI_LEN];            /* 存储顺序参见24.008 10.5.1.4中的规定      */
    RRC_PLMN_ID_STRU                    stPlmnId;                               /* 存储顺序参见24.008 10.5.5.15中的规定，前
                                                                                   3个字节有效                              */
    VOS_UINT16                          usLac;
    VOS_UINT8                           ucRac;

    VOS_UINT8                           aucReserve1[1];     /* 保留 */
}NAS_INFO_PTMSI_RAI_STRU;

typedef struct
{
    VOS_UINT8                           ucEHPlmnNum;
    VOS_UINT8                           aucReserve[3];
    RRC_PLMN_ID_STRU                    astEHPlmnList[NAS_RRC_MAX_EHPLMN_NUM];
}NAS_INFO_EHPLMN_STRU;

typedef struct
{
    VOS_UINT32                          bitOpAttach     : 1;
    VOS_UINT32                          bitOpSecurityKey: 1;
    VOS_UINT32                          bitOpDrxLength  : 1;
    VOS_UINT32                          bitOpTmsiLai    : 1;
    VOS_UINT32                          bitOpPTmsiRai   : 1;
    VOS_UINT32                          bitDelKey       : 1;
    VOS_UINT32                          bitOpIdleMappedLSecurity    : 1;
    VOS_UINT32                          bitSpare        : 25;

    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  ulCnDomainId;       /* CN Domain ID    */
    RRC_NAS_ATTACH_STATUS_ENUM_UINT32   ulAttach;           /* Attach、Deattach标志 */
    SECURITY_KEY_STRU                   SecurityKey;
    VOS_UINT32                          ulDrxLength;        /* PS域协商后的DRX参数  */
    NAS_INFO_TMSI_LAI_STRU              TmsiLai;
    NAS_INFO_PTMSI_RAI_STRU             PTmsiRai;
}NAS_INFO_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT32                          ulCnDomainCnt;      /* CN Domain数量 */
    NAS_INFO_STRU                       aNasInfo[RRC_NAS_MAX_CN_DOMAIN];
}RRMM_NAS_INFO_CHANGE_REQ_STRU;

/*****************************************************************************
 结构名    : RRMM_CSFB_SERVICE_ABORT_NOTIFY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : NAS通知AS当前CSFB中断
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头         */ /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve[4];      /* 保留   */
} RRMM_CSFB_SERVICE_ABORT_NOTIFY_IND_STRU;

/***********************WAS新增接口WAS－>MMC***********************************/
/*****************************************************************************
 Structure      : WRRMM_SCELL_RXLEV_IND_ST
 Description    : 通知NAS服务小区信号强度。
                  MsgHeader －－消息头
                  WRR-->NAS的MMC实体
*****************************************************************************/
/* 7.2.10 消息 WRRMM_SCELL_RXLEV_IND_ST 的结构体 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_INT16                           sRxlev;             /* 服务小区信号强度上报RSCP，范围-111~-24DB */
    VOS_UINT8                           aucReserve1[2];     /* 保留   */
}WRRMM_SCELL_RXLEV_IND_ST;

/***********************WAS新增接口WAS－>MMC********************************/
/* 7.2.11 消息 WRRMM_CHANNEL_QUAL_IND 的结构体 */
/*****************************************************************************
Structure      : WRRMM_CHANNEL_QUAL_IND_ST
Description    : 在专用模式下，周期性地向NAS上报服务小区信号质量
                 WRR-->NAS
                 MsgHeader －－消息头
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT8                           ucChannelQual;      /* 误码率级别,0xFF表示没有,分0~6，7个等级 */
    VOS_UINT8                           aucReserve1[3];     /* 保留   */
}WRRMM_CHANNEL_QUAL_IND_ST;

/***********************WAS新增接口MMC－>WAS********************************/
/* 7.2.12 消息 RRMM_AT_MSG_REQ 的结构体 */
/*****************************************************************************
Structure      : RRMM_AT_MSG_REQ_ST
Description    : MMC启动WAS AT相关信息上报消息
                 NAS-->WRR
                 MsgHeader －－消息头
*****************************************************************************/
/* 消息RRMM_AT_MSG_REQ的结构体 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_NAS_AT_ACTION_ENUM_UINT8        ucActionType;
    VOS_UINT8                           ucMsgType;          /* 多种上报类型或 */
    VOS_UINT8                           ucSignThreshold;    /* 信号变化门限,当RSCP变化超过该值，
                                                               接入层需要主动上报信号质量，取值0表示接入层按默认值处理 */
    VOS_UINT8                           ucMinRptTimerInterval;     /* 间隔上报的时间(0-20)S   */
}RRMM_AT_MSG_REQ_ST;

/***********************WAS新增接口WAS－>MMC********************************/
/* 7.2.13 消息 RRMM_AT_MSG_CNF 的结构体 */
/*****************************************************************************
Structure      : RRMM_AT_MSG_CNF_ST
Description    : WAS 向MMC上报REQ查询的结果
                 WRR-->NAS
                 MsgHeader －－消息头
*****************************************************************************/
/* 消息RRMM_AT_MSG_CNF的结构体 */
typedef struct
{
    VOS_UINT8                           aucReserve1[2];     /* 保留   */
    RRC_NAS_SYS_SUBMODE_ENUM_UINT8      enSysSubMode;       /* aulCellId[0]小区能力 */
    VOS_UINT8                           ucIDNum;            /* 小区ID数 */
    VOS_UINT32                          aulCellId[RRC_NAS_AT_CELL_MAX_NUM];
}RRC_NAS_CELL_ID_ST;

/* 小区信号强度结构体 */
typedef struct
{
    VOS_UINT32                          ulCellId;
    VOS_INT16                           sCellRSCP;
    VOS_INT16                           sRSSI;     /* RSSI  */
}RRC_NAS_CELL_RSCP_ST;

/* 小区信号强度结构列表 */
typedef struct
{
    VOS_UINT8                           aucReserve1[2];     /* 保留   */
    VOS_UINT16                          usCellNum;          /* 小区个数 */
    RRC_NAS_CELL_RSCP_ST                stCellRscp[RRC_NAS_AT_CELL_MAX_NUM];
    VOS_UINT16                          usCellDlFreq;       /*小区频点(下行)*/
    VOS_UINT16                          usCellUlFreq;       /*当前频点(上行)*/
    VOS_INT16                           sUeRfPower;         /*发射功率*/
    PS_BOOL_ENUM_UINT8                  enCritSValid;       /* S准则标志是否生效，PS_TRUE表示enNotFullfilCritS有效,D态，F态下不看这个标志 */
    PS_BOOL_ENUM_UINT8                  enNotFullfilCritS;  /* 是否不满足S准则,PS_TRUE表示不满足 */
}RRC_NAS_CELL_RSCP_STRU_LIST;


typedef struct
{
    VOS_UINT8                           ucDlTrChBler;       /* BLER */
    VOS_UINT8                           ucTrChId;           /* 传输信道ID */
    VOS_UINT8                           aucReserve1[2];     /* 保留   */
}RRC_NAS_CELL_TRCH_BLER_ST;

/* 信道扰码结构体列表 */
typedef struct
{
    VOS_UINT8                           aucReserve1[3];     /* 保留   */
    VOS_UINT8                           ucTrchNum;          /* 传输信道个数 */
    RRC_NAS_CELL_TRCH_BLER_ST           stTrchBlerInfo[RRC_NAS_AT_MAX_TRCH];
}RRC_NAS_CELL_TRCH_BLER_STRU_LIST;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_NAS_AT_ACTION_ENUM_UINT8        ucActionType;
    VOS_UINT8                           ucMsgType;          /* 多种结果的相应消息 */
    RRC_NAS_AT_MSG_FLAG_ENUM_UINT8      ucMsgFlg;           /* 发送的CNF中的消息是否有效;如果AS当前没有此消息的数据，填写无效；永久启动方式，当有数据时，通过IND方式来上报 */
    VOS_UINT8                           ucDataLen;          /* 数据长度 */
    VOS_UINT8                           aucData[4];         /* 数据内容 */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/

}RRMM_AT_MSG_CNF_ST;

/***********************WAS新增接口WAS－>MMC********************************/
/* 7.2.14 消息RRMM_AT_MSG_IND的结构体 */
/*****************************************************************************
Structure      : RRMM_AT_MSG_IND_ST
Description    : WAS 向MMC主动上报REQ查询的结果
                 WRR-->NAS
                 MsgHeader －－消息头
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[2];     /* 保留   */
    RRC_NAS_AT_MSG_TYPE_ENUM_UINT8      ucMsgType;
    VOS_UINT8                           ucDataLen;          /* 数据长度 */
    VOS_UINT8                           aucData[4];         /* 数据内容 */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/

}RRMM_AT_MSG_IND_ST;

/* 7.2.15 OM与WAS消息结构定义，消息名宏定义不在本文件中                    */
/***********************************BEGIN***********************************/
#define   OM_RRCF_CELLPARA_REQ                0x3201        /*OM向RRCF发来的小区参数查询请求的MsgID*/

typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgID;
}RRCF_CELLPARA_REQ_ST;

#define   RRCF_OM_CELLPARA_CNF                0x3202        /*RRCF回复小区参数的MsgID*/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgID;
    VOS_UINT32                          ulDataLen;          /* 数据长度  */
    VOS_UINT8                           aucData[4];         /* 数据内容 */
} RRCF_CELLPARA_CNF_ST;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
}RRC_GET_CELL_INFO_REQ_ST;

typedef struct
{
    RRC_PLMN_ID_STRU                    PlmnId;
    VOS_UINT32                          ulPrimCode;         /* 小区主扰码 */
    VOS_UINT32                          ulFreq;             /* 小区频点 */
    VOS_INT16                           sCpichRscp;
    VOS_INT16                           sCpichEcN0;
    VOS_UINT8                           ucCellID;           /* 小区ID */
    VOS_UINT8                           ucPlmnFlag;         /* PLMN 是否有效，０表示无效，１表示有效 */
    VOS_UINT8                           ucRscpFlg;          /* ０表示无效，１表示RSCP有效 */
    VOS_UINT8                           ucEcN0Flg;          /* ０表示无效，１表示EcN0有效 */
}WAS_OM_CELL_INFO_ST;

typedef struct
{
    VOS_UINT8                           aucReserve1[3];     /* 保留   */
    VOS_UINT8                           ucCellNum;          /* 上报小区数 */
    WAS_OM_CELL_INFO_ST                 stCellInfo[RRC_CELL_INFO_MAX_NUM];
} WAS_CELL_INFO_CNF_ST;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT32                          ulDataLen;          /* 数据长度  */
    VOS_UINT8                           aucData[4];         /* 数据内容 ,具体内容为WAS_CELL_INFO_CNF_ST */
}RRC_GET_CELL_INFO_CNF_ST;

#if 0

/* 移至WasMntn模块 */

#define CONSOLE_WAS_TRANSPORT_REQ         0x5000
#define WAS_CONSOLE_TRANSPORT_CNF         0x5001
#define PSTAS_RRCF_SERVICECELLINFO_REQ    0x5200
#define PSTAS_RRCF_SERVICECELLINFO_CNF    0x5201

typedef struct
{
    VOS_MSG_HEADER                             /* 调试信息消息头，这里的len从usMsgType开始计算 */
    VOS_UINT16 usMsgType;                      /* 调试消息，从0x5001～0x5FFF，各模块划分规则待定 */
    VOS_UINT16 usTransId;                      /* 子进程标识,用于定位子进程 */
    VOS_UINT8  astMsg[4];                      /* 消息结构指针，指向真正携带的消息内容 */
}WAS_DEBUG_MSG_ST;

typedef struct
{
    VOS_MSG_HEADER                             /* 透明通道消息头，这里的len从usMsgID开始计算 */
    VOS_UINT16      usMsgID;                   /* 透明通道消息类型，固定为0x5000 */
    VOS_UINT16      usSubId;                   /* 子进程标识,用于定位子进程，固定为0 */
    WAS_DEBUG_MSG_ST    stDebug;               /* 调试信息消息*/
}WAS_TRANS_COMM_MSG_ST;

#endif



/***********************新增接口MMC－>WAS***************************/
/* 7.2.16 消息 RRMM_SET_WCDMA_BAND_REQ 结构体 */
/* 说明：该消息是MMC发给WAS层设置频段原语，*/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    NAS_WCDMA_BAND_TYPE_ENUM_UINT32     ulWasDlFreqInfo;    /* WAS下行频段  */
}RRMM_SET_WCDMA_BAND_REQ_ST;

/***********************新增接口WAS－>MMC***************************/
/* 7.2.17 消息 RRMM_SET_WCDMA_BAND_CNF 结构体 */
/*******************************************************************************
说明：该消息是AS层通知NAS层已经收到设置频段请求并可以正常响应，AS
      在最新的频段上发起小区搜索，成功后，上报系统信息，若不成功，则上报丢网
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    WAS_CHANGE_BAND_RESULT_ENUM_UINT32  ulResult;           /* 收到WCDMA频段设置结果  */
}RRMM_SET_WCDMA_BAND_CNF_ST;


/***********************************END************************************/


/* 7.3 GAS专用消息 */
/***********************GAS新增接口GAS－>MMC***************************/
/* 7.3.1 消息 GRRMM_SYS_INFO_IND 的结构体 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_PLMN_ID_STRU                    PlmnId;             /* 本小区PLMN ID */
    GSM_BAND_SET_UN                     unGsmBand;          /*_H2ASN_Replace GSM_BAND_STRU                       stGsmBitBand; */
    VOS_UINT16                          usCellId;           /* 本小区 ID  */
    VOS_UINT16                          usLac;              /* [0x0001－0xFFFE] 位置区码  */
    VOS_UINT8                           ucAttachDetach;     /* [0-1] 用于通知MS，在本小区内是否需要进行IMSI结合和分离允许过程:
                                                               0表示不需要手机启动IMSI附着和分离过程，
                                                               1则表示手机必须启动附着和分离过程，message origin:SI3,PSI2 */
    VOS_UINT8                           ucLRTimerT3212;     /* [0-255] 周期位置更新定时器,确定了手机进行周期位置更新的频度,
                                                               每1个单位表示6分钟的时间，为0则表示不进行位置更新，message origin:SI3,PSI2 */
    VOS_UINT8                           ucGprsSupportInd;   /* [0-1] GPRS支持指示:0-不支持;1-支持*/
    VOS_UINT8                           ucRac;              /* 路由区域码*/
    GRRMM_NW_OP_MODE_ENUM_UINT8         ucNetworkOperationMode;       /*   网络运行模式 */
    VOS_UINT8                           ucDrxTimerMax;      /* [0,1,2,4,8,16,32,64]s   */
    GRRMM_MSG_REL_VER_ENUM_UINT8        ucMsrRelease;       /* [0-1] 0 MSC is Release '98 or older
                                                               1 MSC is Release '99 onwards */
    GRRMM_SGSN_REL_VER_ENUM_UINT8       ucSgsnRelease;       /* [0-1] 0 SGSN is Release '98 or older
                                                               1 SGSN is Release '99 onwards */
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    RRC_NAS_RESTRICTION_UN              unAcInfo;	     /*_H2ASN_Replace RRC_NAS_RESTRICTION_ENUM_UINT8            unAcInfo; */
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */
    GRRMM_BAND_INDICATOR_ENUM_UINT8     ucBandIndicator;     /* 当前的组网指示:1800或1900  0表示1800，1表示1900*/
    VOS_UINT8                           aucReserve[2];
}GRRMM_SYS_INFO_IND_ST;


/***********************GAS新增接口GAS－>MM/GMM*************************/
/* 7.3.2 消息 GRRMM_PAGING_IND 的结构体 */
/* 当RR或GRR从网络侧接收到寻呼消息，RR或GRR应该检查MS identity，若与MS本身的匹配，
   并建立RR连接成功后，发送GRRMM_PAGING _IND原语指示NAS */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    GAS_MS_IE_TYPE_ENUM_UINT8           ucMSIDType;         /* TMSI or IMSI or PTMSI */
    GAS_PAGING_TYPE_ENUM_UINT8          ucPagingType;       /* CS or PS */
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
}GRRMM_PAGING_IND_ST;

/***********************GAS新增接口GAS－>GMM*************************/
/* 当UL&UL TBF释放时，GAS通知GMM,GMM收到后，如果需要发起ATTACH，立刻发起ATTACH过程 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve[4];      /* 4字节对齐，保留 */
}GRRGMM_TBF_REL_IND_ST;

/***********************GAS新增接口GAS－>MM***************************/
/*********************************************************************
 Structure      : GAS_RR_SYNC_IND_ST
 Description    : 这个结构描述对MO或MT建立RR连接后同步的数据接口；
                  MsgHeader －－消息头
                  RR-->NAS
                  RR_SYNC_IND
                  使用这个结构 参见  24.007
***********************************************************************/
/* 7.3.3 消息 GAS_RR_SYNC_IND 的结构体 */
/* uiSynCause取值 */
#define   RR_SYN_CIPH                   0   /*加密启动*/
#define   RR_SYN_TCH                    1   /*信道指配完成*/
#define   RR_SYN_TCH_MODIFY             2   /*信道模式修改*/
#define   RR_SYN_GSM_GSM_HANDOVER       3
#define   RR_SYN_WCDMA_GSM_HANDOVER     4

/* uiSynCause取值为RR_SYN_CIPH时ucSynValue的取值 */
#define   RR_CIPHER_ALGORITHM_A51       0   /* 加密算法A5/1,见协议R4,44018,10.5.2.9 */
#define   RR_CIPHER_ALGORITHM_A52       1   /* 加密算法A5/2,见协议R4,44018,10.5.2.9 */
#define   RR_CIPHER_ALGORITHM_A53       2   /* 加密算法A5/3,见协议R4,44018,10.5.2.9 */
#define   RR_CIPHER_ALGORITHM_A54       3   /* 加密算法A5/4,见协议R4,44018,10.5.2.9 */
#define   RR_CIPHER_ALGORITHM_A55       4   /* 加密算法A5/5,见协议R4,44018,10.5.2.9 */
#define   RR_CIPHER_ALGORITHM_A56       5   /* 加密算法A5/6,见协议R4,44018,10.5.2.9 */
#define   RR_CIPHER_ALGORITHM_A57       6   /* 加密算法A5/7,见协议R4,44018,10.5.2.9 */
#define   RR_NO_CIPHER                  8   /* 加密停止 */

/* uiSynCause取值为RR_SYN_TCH和RR_SYN_TCH_MODIFY时ucSynValue的取值 */
#if 0
#define   RR_CHAN_MOD_SINGAL_ONLY       0   /* 仅信令模式*/
#define   RR_CHAN_MOD_FR                1   /* Full Rate */
#define   RR_CHAN_MOD_EFR               2   /* Enhanced Full Rate  */
#endif

#define   RR_CHAN_MOD_AMR               3   /* Adaptive Multi-Rate */

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT8                           ucSynCause;
    VOS_UINT8                           ucSynValue;
    GRR_NAS_SYNC_TCH_RATE_ENUM_UINT8    ucTchRate;
    VOS_UINT8                           aucReserve1[1];     /* 保留   */
}GAS_RR_SYNC_IND_ST;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    NAS_RR_CHANNEL_MODE_ENUM_U8         enChanMod;          /* 信道模式   */
    VOS_UINT8                           aucReserve1[3];     /* 保留   */
}GAS_RR_CHAN_MOD_IND_ST;

/***********************GAS新增接口GAS－>GMM***********************************/
/*****************************************************************************
 Structure      : RRMM_GPRS_SUSPEND_IND_ST
 Description    : 通知NAS挂起GPRS。
                  MsgHeader －－消息头
                  RR-->NAS的GMM实体
                  RRMM_GPRS_SUSPEND_IND
                  使用这个结构 参见  24.007
*****************************************************************************/
/* 7.3.4 消息 RRMM_GPRS_SUSPENSION_IND_ST 的结构体 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
}RRMM_GPRS_SUSPEND_IND_ST;

/***********************GAS新增接口GAS－>GMM***********************************/
/*****************************************************************************
 Structure      : RRMM_GPRS_RESUME_IND_ST
 Description    : 通知NAS恢复GPRS。
                  MsgHeader －－消息头
                  RR-->NAS的GMM实体
                  RRMM_GPRS_RESUME_IND
                  使用这个结构 参见  24.007
*****************************************************************************/
/* 7.3.4 消息 RRMM_GPRS_RESUME_IND_ST 的结构体 */

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    GRR_GMM_GPRS_RESUME_RESULT_ENUM_UINT8   ucResult;
    VOS_UINT8                           aucReserve1[3];     /* 保留   */
}RRMM_GPRS_RESUME_IND_ST;

/***********************GAS新增接口GAS－>MMC***********************************/

#define GRRMM_SCELL_MEAS_TYPE_NONE                              0x00               /* AT查询上报  */
#define GRRMM_SCELL_MEAS_TYPE_RXLEV                             0x01               /* RXLEV变化触发的上报 */
#define GRRMM_SCELL_MEAS_TYPE_RXQUALITY                         0x02               /* RXQUALITY变化触发的上报 */
#define GRRMM_SCELL_MEAS_TYPE_CELLID                            0x04               /* CELL ID变化触发的上报 */


/*******************************************************************************
 结构名    :GRRMM_SCELL_MEAS_TYPE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : union GRRMM_SCELL_MEAS_REPORT_TYPE_UN成员stMeasReportType定义
             bit位置1表示该类型有效
1.日    期 : 2012年12月27日
  作    者 : w00176595
  修改内容 : 新建
*******************************************************************************/
typedef struct
{
    VOS_UINT8                          ucMeasRxlevType          :1;             /* Rxlev改变触发的测量上报 */
    VOS_UINT8                          ucMeasRxqualityType      :1;             /* Rxquality改变触发的测量上报 */
    VOS_UINT8                          ucMeasCellIdType         :1;             /* Rxquality改变触发的测量上报 */
    VOS_UINT8                          ucMeasTypeSpare5         :5;
}GRRMM_SCELL_MEAS_TYPE_STRU;

/*****************************************************************************
 枚举名    : GRRMM_SCELL_MEAS_REPORT_TYPE_UN
 结构说明  : GRRMM_SCELL_MEAS_REPORT_TYPE_UN unMeasType GAS上报测量的类型
1. 日    期: 2012年12月27日
   作    者: w00176595
   修改内容: 新建
*****************************************************************************/
typedef union
{
    VOS_UINT8                             ucMeasReportType;

    GRRMM_SCELL_MEAS_TYPE_STRU            stMeasReportType;
}GRRMM_SCELL_MEAS_REPORT_TYPE_UN;
/*****************************************************************************
Structure      : GRRMM_SCELL_MEAS_IND_ST
Description    : GCOM周期性地向NAS上报服务小区信号强度
                  RR-->NAS
                  MsgHeader －－消息头

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_INT16                           sRxlev;             /* 服务小区信号强度 */
    VOS_UINT8                           ucChannelQual;      /*误码率级别,99标识没有 */

    GRRMM_SCELL_MEAS_REPORT_TYPE_UN     unMeasReportType;   /* 本次上报的类型   */ /*_H2ASN_Replace GRRMM_SCELL_MEAS_TYPE_STRU            stMeasReportType; */

    VOS_UINT16                          usCellId;
    VOS_UINT16                          usCellDlFreq;       /*小区频点(下行)*/
    VOS_UINT16                          usCellUlFreq;       /*当前频点(上行)*/
    VOS_INT16                           sUeRfPower;         /*发射功率,RRMM_UE_RFPOWER_INVALID无效值*/
}GRRMM_SCELL_MEAS_IND_ST ;

/***********************GAS新增接口MM/GMM－>GAS********************************/
/*****************************************************************************
 Structure      : GRRMM_NAS_INFO_CHANGE_REQ_STRU
 Description    : 在GSM网络下NAS信息改变通知接入层
*****************************************************************************/
/* 7.3.6 消息 GRRMM_NAS_INFO_CHANGE_REQ 的结构体 */
typedef struct
{
    VOS_UINT8                           aucKc[RR_NAS_KC_LEN];                   /* GPRS Ciphering key,存储格式参见TS31.102-4.4.3.2*/
}GAS_SECURITY_KEY_ST;

typedef struct
{
    VOS_UINT32                          bitOpAttach     : 1;
    VOS_UINT32                          bitOpSecurityKey: 1;
    VOS_UINT32                          bitOpDrxLength  : 1;
    VOS_UINT32                          bitOpTmsiLai    : 1;
    VOS_UINT32                          bitOpPTmsiRai   : 1;
    VOS_UINT32                          bitOpDelKey     : 1;
    VOS_UINT32                          bitOpGmmState   : 1;
    VOS_UINT32                          bitOpReadyTime  : 1;
    VOS_UINT32                          bitOpGprsMode   : 1;
    VOS_UINT32                          bitOpIdleMappedLSecurity   : 1;
    VOS_UINT32                          bitSpare        : 22;
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  ulCnDomainId;       /* CN Domain ID    */
    NAS_GSM_ATTACH_TYPE_ENUM_UINT32     ulAttach;           /* Attach、Deattach标志，   */
    GAS_SECURITY_KEY_ST                 stSecurityKey;
    VOS_UINT32                          ulDrxLength;        /* PS域协商后的DRX参数      */
    VOS_UINT32                          ulSplitPgCycle;     /* DRX参数中Split PG Cycle数值 */
    NAS_INFO_TMSI_LAI_STRU              stTmsiLai;
    NAS_INFO_PTMSI_RAI_STRU             stPtmsiRai;
    VOS_UINT32                          ulReadyTimerValue;  /* READY TIMER 当前大小 */
    NAS_GMM_STATE_ENUM_UINT8            ucGsmGmmState;      /* GMM状态  */
    NAS_GSM_GPRS_MODE_ENUM_UINT8        ucMsGprsMode;       /* MS GPRS 模式 */
    VOS_UINT8                           aucReserve1[2];     /* 保留   */
}GAS_NAS_INFO_ST;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    GAS_NAS_INFO_ST                     stNasInfo;
}GRRMM_NAS_INFO_CHANGE_REQ_STRU;

/***********************GAS新增接口GMM－>GRR***************************/
/* 7.3.7 消息 GRRGMM_ASSIGN_REQ 的结构体 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT32                          ulTlli;             /* 当前有效的TLLI值 */
    VOS_UINT32                          ulOldTlli;          /* 准备去指配的TLLI值 */
    GMM_GRR_TLLI_CAUSE_ENUM_UINT32      ulTlliCause;        /* 操作TLLI的原因值 */
}GRRGMM_ASSIGN_REQ_ST;

/***********************GAS新增接口MMC－>GAS********************************/
/* 7.3.8 消息 RRMM_NAS_PARAMS_REQ 的结构体 */
/*Description   : MMC向RR发送用户选择的频段信息
                  NAS（MMC） GGCOM
                  MsgHeader －－消息头

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    MMC_CM_BAND_ENUM_UINT32             ulBand;             /* 用户选择的频段 */
}RRMM_NAS_PARAMS_REQ_ST;

/***********************GAS新增接口MM－>GAS********************************/
/* 7.3.9 消息 GRRMM_EST_SAPI3_REQ 的结构体 */
/*Description   : MM请求GAS建立SAPI3
                  NAS（MM）GGCOM
                  MsgHeader －－消息头

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
}GRRMM_EST_SAPI3_REQ_ST;

/***********************GAS新增接口GAS－>MM********************************/
/* 7.3.10 消息 GRRMM_EST_SAPI3_CNF 的结构体 */
/*Description   : GAS对MM请求建立SAPI3的回应
                  GGCOM NAS（MM)
                  MsgHeader －－消息头

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    MM_EST_RESULT_ENUM_UINT8            ucResult;           /* 建立结果  */
    VOS_UINT8                           aucReserve1[3];     /* 保留   */
}GRRMM_EST_SAPI3_CNF_ST;

/***********************GAS新增接口MM－>GAS********************************/
/* 7.3.11 消息 GRRMM_AT_MSG_REQ 的结构体 */
/*Description   : MM对GAS请求启动主动上报的消息结构
                  GGCOM NAS（MM)
                  MsgHeader －－消息头

*****************************************************************************/
/* 消息RRMM_AT_MSG_REQ的结构体 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    GAS_NAS_AT_ACTION_TYPE_ENUM_UINT8   ucActionType;       /* 只控制RSSI和BER */
    VOS_UINT8                           ucSignThreshold;    /* 信号变化门限,当RSSI变化超过该值，
                                                               接入层需要主动上报信号质量，取值0表示接入层按默认值处理 */
    VOS_UINT8                           ucMinRptTimerInterval;     /* 间隔上报的时间(0-20)S   */
    VOS_UINT8                           aucReserve1[1];     /* 保留   */
}GRRMM_AT_MSG_REQ_ST;

/***********************AS接口GMM－>GAS********************************/
/* 7.3.12 消息 RRMM_GMM_PROC_NOTIFY_STRU 的结构体 */
/*Description   : GMM指示GMM ATTACH或RAU过程完成
                  NAS（GMM）
                  MsgHeader －－消息头

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    RRMM_GMM_PROC_TYPE_ENUM_UINT16      usGmmProcType;        /* GMM过程类型 */
    RRMM_GMM_PROC_FLAG_ENUM_UINT16      usGmmProcFlag;        /* GMM过程标志 */
}RRMM_GMM_PROC_NOTIFY_STRU;

/*****************************************************************************
 结构名    : RRMM_GMM_PROC_ENQ_STRU
 结构说明  : AS查询当前GMM当前连接状态
 1.日    期   : 2014年5月22日
   作    者   : w00242748
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve[4];
}RRMM_GMM_PROC_ENQ_STRU;

/*****************************************************************************
 结构名    : RRMM_GMM_PROC_ANS_STRU
 结构说明  : AS查询当前GMM当前连接状态
 1.日    期   : 2014年5月22日
   作    者   : w00242748
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    RRMM_GMM_PROC_CONN_TYPE_ENUM_UINT16                     enGmmConnType;
    VOS_UINT8                                               aucReserve[2];
}RRMM_GMM_PROC_ANS_STRU;


/***********************新增接口GMM－>GAS********************************
 结构名    : RRMM_AUTH_FAIL_NOTIFY_REQ_STRU
 结构说明  : GMM指示鉴权被拒,Bar掉当前小区
 修改历史     :
 1.日    期   : 2012年4月20日
   作    者   : l00130025
   修改内容   : DTS2012032004389，Netork连续3次被Ms Auth Rej或T3318/T3320超时时，没有通知GAS Bar掉当前小区,
                相关协议TS 24.008 4.3.2.6.1 & 4.7.7.6,Ts43.022 3.5.5
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT32                          ulT3302TimerLen;    /* Timer时长(单位：毫秒) */
}RRMM_AUTH_FAIL_NOTIFY_REQ_STRU;


/*******************************************************************************
 结构名    : NAS_GPRS_ACCESS_RESULT_ENUM
 结构说明  : NAS当前GPRS的接入结果
 修改历史     :
 1.日    期   : 2011年7月13日
   作    者   : w00176964
   修改内容   : 新增
*******************************************************************************/
enum NAS_GPRS_ACCESS_RESULT_ENUM
{
    NAS_GPRS_ACCESS_SUCCESS             = 0,                                    /* GPRS接入成功 */
    NAS_GPRS_ACCESS_FAIL                = 1                                  /* GPRS接入失败 */
};
typedef VOS_UINT32 NAS_GPRS_ACCESS_RESULT_ENUM_UINT32;

/*******************************************************************************
 结构名    : GRRGMM_GPRS_ACCESS_RESULT_IND_STRU
 结构说明  : 消息 GRRGMM_GPRS_ACCESS_RESULT_IND的结构
             该消息为GAS通知GMM当前GPRS的接入结果
 修改历史     :
 1.日    期   : 2011年7月13日
   作    者   : w00176964
   修改内容   : 新增
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */ /*_H2ASN_Skip*/
    NAS_GPRS_ACCESS_RESULT_ENUM_UINT32  enResult;                               /* GPRS接入结果 */
}GRRGMM_GPRS_ACCESS_RESULT_IND_STRU;

/***********************新增接口MMC－>GAS***************************/
/* 7.3.12 消息 RRMM_SET_GSM_BAND_REQ 结构体 */
/* 说明：该消息是MMC发给AS层设置频段原语，*/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    NAS_GSM_BAND_TYPE_ENUM_UINT32       ulGsmBandInfo;      /* GSM频段信息  */
}RRMM_SET_GSM_BAND_REQ_ST;

/***********************新增接口AS－>MMC***************************/
/* 7.1.29 消息 RRMM_SET_GSM_BAND_CNF 结构体 */
/* 说明：该消息是GAS层通知NAS层已经收到设置频段请求并可以正常响应，GAS
在最新的频段上发起小区搜索，成功后，上报系统信息，若不成功，则上报丢网
*/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    GAS_CHANGE_BAND_RESULT_ENUM_UINT32  ulResult;           /* 收到GSM频段设置结果  */
}RRMM_SET_GSM_BAND_CNF_ST;

/***********************新增接口GAS－>MMC***************************/
/* 7.3.30 消息 GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND 结构体 */
/* 说明：该消息是GAS发给NAS上报MS RADIO ACCESS CAPABILITIES*/
typedef struct
{
    MSG_HEADER_STRU    MsgHeader;                                       /* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT8          aucData[MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE];    /* RAC消息具体内容 */
}GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND_STRU;

/* 9.2 AS 获取 MM/GMM 安全信息接口 （新增接口） */
typedef struct
{
    MM_SECURITY_MASK_ENUM_UINT8         ucInfoMask;         /* 信息参数有效标志 */
    VOS_UINT8                           aucCk[RRC_NAS_CIPHER_KEY_LEN];          /* Cipher Key        */
    VOS_UINT8                           aucIk[RRC_NAS_INTEGRITY_KEY_LEN];       /* Integrity Key     */
    VOS_UINT8                           aucKc[RR_NAS_KC_LEN];                   /* GSM cipher key Kc */
    VOS_UINT8                           aucImsi[RRC_NAS_IMSI_MAX_LEN];          /* 15 digits */
    VOS_UINT8                           ucCksn;             /* Ciphering Key Sequence Number */
    VOS_UINT8                           aucPTMSI[RRC_NAS_PTMSI_LEN];            /* P/TMSI */
    VOS_UINT8                           aucReserve1[2];     /* 保留   */

}MM_CSPS_INFO_ST;

/* 9.3 NAS 获取 BAND 信息接口 （新增接口） */
#define AS_NAS_BAND_INVALID_FLAG    0xFFFFFFFF      /* BAND信息无效指示，当RR发送此结构时，需要将WRR频段信息设为无效*/
typedef struct
{

    VOS_UINT32                          ulRrBandInfo;       /* (32bit) RR当前服务小区band信息 */
    VOS_UINT32                          ulWrrBandInfo;      /* (32bit) WRR当前服务小区band信息 */

}AS_NAS_SCELL_BAND_INFO_ST;

/* 9.4 AS 获取 通过调用此接口来获取NAS的相关信息。比如说PLMN的信息等。（新增接口） */
/*****************************************************************************
 结构名    : RRC_EPLMN_INFO_STRU
 结构说明  : 等效plmn信息，手动搜网模式只带用户指定网络及指定网络等效plmn
 1.日    期   : 2013年10月17日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpCurPlmn: 1;                        /* 指示stCurCampedPlmnId字段是否有效，手动搜网模式下
                                                                                如果当前驻留网络不是用户指定plmn则该值为0，当前驻留网络无效 */
    VOS_UINT32                          bitSpare     : 31;
    RRC_PLMN_ID_STRU                    stCurCampedPlmnId;

    VOS_UINT32                          ulPlmnIdNum;                            /* 等效plmn个数 */
    RRC_PLMN_ID_STRU                    aPlmnIdList[RRC_MAX_EQUPLMN_NUM];       /* 等效plmn信息*/
}RRC_EPLMN_INFO_STRU;


typedef struct
{
    RRC_EPLMN_INFO_STRU                 stEplmnInfo;

    VOS_UINT32                          ulForbLaNum;        /* 禁止注册区的个数 */
    RRC_FORB_LA_STRU                    aForbLaList[RRC_MAX_FORBLA_NUM];
}PLMN_INFO_LIST_ST;

typedef struct
{
    RRC_NAS_SIM_STATUS_ENUM_UINT32      ulSimStatus;
}MM_SIM_INFO_ST;

typedef struct
{
    PLMN_INFO_LIST_ST                   stPlmnInfo;
    MM_SIM_INFO_ST                      stSimInfo;
    RRC_PLMN_ID_STRU                    stCurPlmnId;
    VOS_UINT16                          usCurLac;
    VOS_UINT8                           ucCurRac;
    VOS_UINT8                           ucUeOperMode;
}MM_INFO_ST;


/*  9.5 WAS通过这条原语通知RABM释放所有资源，该消息与状态无关，
    RABM在任何时候都应该正确响应这条原语，使得在异常时，RABM可以完全释放 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* 字节对齐 */
}RRRABM_REL_ALL_REQ_STRU;

/********************************************************************************
  9.6 异系统切换或者重选过程中NAS保护定时器超时，向GAS或者WAS发送释放请求
********************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* 字节对齐 */
}RRMM_SUSPEND_REL_REQ_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* 字节对齐 */
}RRMM_SUSPEND_REL_CNF_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    PS_BOOL_ENUM_UINT8                  enQueryWPlmn;       /* PS_TRUE 表示查询W 下的PLMN,NAS上报HPLMN和RPLMN,PS_FALSE 查询G下PLMN*/
    VOS_UINT8                           aucReserve1[3];     /* 字节对齐 */
}RRMM_PLMN_QUERY_REQ_STRU;

/*******************************************************************************
 结构名    : RRMM_EPLMN_QUERY_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 接入层查询等效PLMN信息的接口
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/

    VOS_UINT8                           aucReserve1[4];     /* 字节对齐 */
}RRMM_EPLMN_QUERY_REQ_STRU;


/*******************************************************************************
 结构名    : RRMM_EPLMN_QUERY_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : NAS回复接入层RRMM_EPLMN_QUERY_REQ查询消息的接口
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/

    VOS_UINT32                          bitOpCurPlmn: 1;                        /* 指示stCurCampedPlmnId字段是否有效，手动搜网模式下
                                                                                   如果当前驻留网络不是用户指定plmn则该值为0，当前驻留网络无效 */
    VOS_UINT32                          bitSpare     : 31;
    RRC_PLMN_ID_STRU                    stCurCampedPlmnId;

    VOS_UINT32                          ulEPlmnIdNum;        /* PLMN ID个数 */
    RRC_PLMN_ID_STRU                    astEPlmnIdList[RRC_MAX_EQUPLMN_NUM];       /* PlMN标识 */
}RRMM_EPLMN_QUERY_CNF_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* 字节对齐 */
}WRRMM_TBAR_EXPIRED_IND_STRU;
/********************************************************************************
  9.7 TC向RRCF发送TC_RRCF_TEST_CONTROL消息，用于TC环回时规避BBP功控问题
********************************************************************************/
/*原语ID*/
#define     TC_RRCF_TEST_CONTROL            0x100
/*模式信息*/
#define     TC_RRCF_ACT_TEST_MODE           0         /*启动环回测试模式*/
#define     TC_RRCF_DEACT_TEST_MODE         1         /*停止环回测试模式*/

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32      ulMsgName;
    VOS_UINT32      ulMode;
}TC_RRCF_TEST_CONTROL_MSG;


/*******************************************************************************
 结构名    : NAS_COMM_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 和域无关的公共参数:
                1.USIM卡状态，对热插拔USIM卡的支持
 1.日    期: 2011年10月25日
   作    者: w00176964
   修改内容: 增加信元,作用如下:
             1)用于L下联合注册被拒导致需要DISABLE LTE(具体场景可参考TS24301)时
               通知GAS/WAS当前L不可用(WAS/GAS在DEACTIVE时也要处理)，在L回到可用之前
               GAS/WAS不能通过异系统改变回到L下；
             2)在NAS主动Disable LTE后，如果需要Re-enable LTE(具体场景可参考TS24301)
               时通知GAS/WAS当前L可用(WAS/GAS在DEACTIVE时也要处理)
 2.日    期   : 2012年6月11日
   作    者   : w00166186
   修改内容   : AT&T&DCM项目
 3.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpUsimValid      :1;
    VOS_UINT32                          bitOpLTECapability  :1;                   /* LTE能力是否发生改变的OP项,表征enLCapabilityStatus是否有效 */
    VOS_UINT32                          bitOpUTRANCapability : 1;
    VOS_UINT32                          bitOpGSMCapability  : 1;

    VOS_UINT32                          bitOpHPlmn          : 1;
    VOS_UINT32                          bitOpEHPlmn         : 1;
    VOS_UINT32                          bitSpare            : 26;

    RRC_NAS_USIM_STATUS_ENUM_UINT32                         enUsimStatus;       /* 标志USIM卡的状态 */
    RRC_NAS_RAT_CAPABILITY_STATUS_ENUM_UINT8                enLCapabilityStatus;/* 标志LTE特性使能的状态 */
    RRC_NAS_RAT_CAPABILITY_STATUS_ENUM_UINT8                enUCapabilityStatus;/* 标志UTRAN特性使能的状态 */
    RRC_NAS_RAT_CAPABILITY_STATUS_ENUM_UINT8                enGCapabilityStatus;/* 标志GSM特性使能的状态 */
    VOS_UINT8                                               aucReserve[1];

    RRC_PLMN_ID_STRU                    stHPlmn;
    NAS_INFO_EHPLMN_STRU                stEHPlmn;

} NAS_COMM_INFO_STRU;

/*******************************************************************************
 结构名    : RRMM_NAS_COMM_INFO_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息 RRMM_NAS_COMM_INFO_CHANGE_REQ 的结构
             该消息为WAS和GAS同NAS共用消息，由MMC发出，
             主要是向接入层下发和域无关的参数:如USIM卡状态等。
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    NAS_COMM_INFO_STRU                  stNasCommInfo;
} RRMM_NAS_COMM_INFO_REQ_STRU;



/*******************************************************************************
 结构名    : USER_SET_FREQ_BAND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 频段定义
*******************************************************************************/
typedef struct
{
    WCDMA_BAND_SET_UN                   unWcdmaBand;        /*_H2ASN_Replace WCDMA_BAND_STRU                     stWcdmaBitBand; */
    GSM_BAND_SET_UN                     unGsmBand;          /*_H2ASN_Replace GSM_BAND_STRU                       stGsmBitBand; */
}USER_SET_FREQ_BAND_STRU;


/*******************************************************************************
 结构名    : RRMM_SYS_CFG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息 RRMM_SYS_CFG_REQ的结构
             该消息为WAS和GAS同NAS共用消息，由MMC发出，
             当用户改变接入模式或频带参数时下发
修改历史      :
 1.日    期   : 2011年7月2日
   作    者   : w00167002
   修改内容   : V3到V7需要更改SYSCFG请求原语接口中的接入模式
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_NAS_SIM_STATUS_ENUM_UINT32      ulSimStatus;        /* SIM卡状态 */
    VOS_UINT32                          bitOpRat:1;
    VOS_UINT32                          bitOpBand:1;
    VOS_UINT32                          bitSpare:30;
    NAS_RRC_USER_SET_FREQ_BAND_STRU     stBand;                                 /* 频带 */

    RRMM_RAT_PRIO_ENUM_UINT8            aucRatPrioList[RRMM_RAT_TYPE_BUTT];     /* 各模的优先级 */
    RRC_NAS_UTRAN_MODE_ENUM_UINT8       enUtranMode;
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
    VOS_UINT8                           aucReserved[2];
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, End */
}RRMM_SYS_CFG_REQ_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/

    VOS_UINT32                          ulAvailPlmnIdNum;        /* PLMN ID个数 */
    RRC_PLMN_ID_STRU                    astAvailPlmnIdList[NAS_RRC_MAX_AVAILPLMN_NUM];      /* PlMN标识 */
}RRMM_PLMN_QUERY_CNF_STRU;

/*******************************************************************************
 结构名    : RRMM_SYS_CFG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息 RRMM_SYS_CFG_CNF的结构
             该消息为WAS和GAS处理完RRMM_SYS_CFG_REQ消息后的回复确认消息
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    RRMM_SYS_CFG_RESULT_ENUM_UINT32     ulResult;
}RRMM_SYS_CFG_CNF_STRU;

/*******************************************************************************
 结构名    : RRMM_CELL_RESELECT_IND_ST
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息 RRMM_CELL_RESELECT_IND的结构
             该消息用于通知NAS开始或完成小区重选过程
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    RRMM_CELL_RESEL_PROC_ENUM_UINT8     ucCellReselProc;
    VOS_UINT8                           aucReserve1[3];     /* 保留   */
}RRMM_CELL_RESELECT_IND_ST;

/*******************************************************************************
 结构名    : RRMM_INTER_RAT_HANDOVER_INFO_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息 RRMM_INTER_RAT_HANDOVER_INFO_REQ 的结构
             该消息用于向接入层获取inter rat hand over info。
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* 保留字段,便于将来扩展 */
}RRMM_INTER_RAT_HANDOVER_INFO_REQ_STRU;

/*******************************************************************************
 结构名    : RRMM_INTER_RAT_HANDOVER_INFO_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息 RRMM_INTER_RAT_HANDOVER_INFO_CNF 的结构
             该消息用于向NAS回复 inter rat hand over info。
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                    MsgHeader;          /* 消息头 */         /*_H2ASN_Skip*/
    VOS_UINT16                         usDataLen;
    VOS_UINT8                          aucData[RRC_NAS_INTER_RAT_HANDOVER_INFO_LEN];
}RRMM_INTER_RAT_HANDOVER_INFO_CNF_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* 保留   */
}RRMM_NOT_CAMP_ON_IND_STRU;

/*******************************************************************************
 结构名    : RRMM_BG_PLMN_SEARCH_STATUS_IND_ST
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息 RRMM_BG_PLMN_SEARCH_STATUS_IND的结构
             该消息用于通知NAS是否允许发起BG搜索
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* 保留   */
}RRMM_BG_PLMN_SEARCH_STATUS_IND_ST;

/*******************************************************************************
 结构名    : RRMM_BG_PLMN_SEARCH_REQ_ST
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息 RRMM_BG_PLMN_SEARCH_REQ的结构
             该消息用于通知接入层发起BG搜索
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    RRMM_PLMN_WITH_RAT_STRU             stPlmnId;           /* PlMN标识 */

    VOS_UINT32                          ulForbLaNum;        /* 禁止注册区的个数 */
    RRC_FORB_LA_STRU                    aForbLaList[RRC_MAX_FORBLA_NUM];   /* 禁止LAI信息 */

}RRMM_BG_PLMN_SEARCH_REQ_ST;

/*******************************************************************************
 结构名    : RRMM_BG_PLMN_SEARCH_CNF_ST
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息 RRMM_BG_PLMN_SEARCH_CNF的结构
             该消息用于通知NAS BG搜索结果
*******************************************************************************/

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_BG_PLMN_SEARCH_RLT_ENUM_UINT8   enSearchRlt;        /* 搜索结果 */
    VOS_UINT8                           aucReserve[2];      /* 保留   */
    VOS_UINT8                           ucPlmnNum ;
    RRMM_PLMN_WITH_RAT_STRU             astPlmnId[NAS_RRC_MAX_BG_SRCH_PLMN_NUM];           /* PlMN标识 */
}RRMM_BG_PLMN_SEARCH_CNF_ST;

/*******************************************************************************
 结构名    : RRMM_BG_PLMN_STOP_REQ_ST
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息 RRMM_BG_PLMN_STOP_REQ的结构
             该消息用于通知NAS BG搜索结果
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* 保留   */
}RRMM_BG_PLMN_STOP_REQ_ST;

/*******************************************************************************
 结构名    : RRMM_BG_PLMN_STOP_CNF_ST
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息 RRMM_BG_PLMN_STOP_CNF的结构
             该消息用于通知NAS BG搜索结果
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4];     /* 保留   */
}RRMM_BG_PLMN_STOP_CNF_ST;

/*****************************************************************************
 枚举名    : RRC_FASTDORM_START_TYPE_ENUM_UINT32
 结构说明  : FASTDORM启动操作类型?
*****************************************************************************/
enum RRC_FASTDORM_START_TYPE_ENUM
{
    RRC_FASTDORM_START_TYPE_FD                 = 0,        /* 仅允许FD */
    RRC_FASTDORM_START_TYPE_ASCR               = 1,        /* 仅允许ASCR，预留 */
    RRC_FASTDORM_START_TYPE_FD_ASCR            = 2,        /* 允许FD和ASCR */
    RRC_FASTDORM_START_TYPE_BUTT
};
typedef VOS_UINT32 RRC_FASTDORM_START_TYPE_ENUM_UINT32;

/*****************************************************************************
 结构名    : RRRABM_FASTDORM_START_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :请求AS启动FASTDORM
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                       MsgHeader;      /* 消息头  */    /*_H2ASN_Skip*/
    RRC_FASTDORM_START_TYPE_ENUM_UINT32   enStartType;    /* FD启动类型 */
}RRRABM_FASTDORM_START_REQ_STRU;

/*****************************************************************************
 结构名    : RRRABM_FASTDORM_START_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : AS收到启动FASTDORM请求的回复
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                       MsgHeader;      /* 消息头  */    /*_H2ASN_Skip*/
    VOS_UINT8                             aucReserve1[4]; /* 保留 */
}RRRABM_FASTDORM_START_CNF_STRU;

/*****************************************************************************
 结构名    : RRRABM_FASTDORM_STOP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :请求AS停止FASTDORM
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                       MsgHeader;      /* 消息头  */    /*_H2ASN_Skip*/
    VOS_UINT8                             aucReserve1[4]; /* 保留 */
}RRRABM_FASTDORM_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : RRMM_TRANSACTION_INFO_ENQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :向NAS查询当前业务信息
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                       MsgHeader;      /* 消息头  */    /*_H2ASN_Skip*/
}RRMM_TRANSACTION_INFO_ENQ_STRU;

/*****************************************************************************
 结构名    : RRRABM_FASTDORM_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : AS收到停止FASTDORM请求的回复
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                       MsgHeader;      /* 消息头  */    /*_H2ASN_Skip*/
    VOS_UINT8                             aucReserve1[4]; /* 保留 */
}RRRABM_FASTDORM_STOP_CNF_STRU;

/*****************************************************************************
 结构名    : RRC_NAS_CS_TRANSACTION_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CS业务信息结构体
*****************************************************************************/
typedef struct
{
    RRC_NAS_CS_TRANSACTION_ENUM_UINT8     enCsTransactionType;
    /* Added by n00355355 for 呼叫重建, 2015-9-17, begin */
    VOS_UINT8                             ucIsCallActive;
    /* Added by n00355355 for 呼叫重建, 2015-9-17, end */
    VOS_UINT8                             aucReserve1[2]; /* 保留 */
}RRC_NAS_CS_TRANSACTION_INFO_STRU;

/*****************************************************************************
 结构名    : RRC_NAS_PS_TRANSACTION_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PS业务信息结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT8                             aucReserve1[4]; /* 保留 */
}RRC_NAS_PS_TRANSACTION_INFO_STRU;

/*****************************************************************************
 结构名    : RRMM_TRANSACTION_INFO_ANS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 查询当前业务信息的回复
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                       MsgHeader;        /* 消息头  */    /*_H2ASN_Skip*/
    RRC_NAS_CS_TRANSACTION_INFO_STRU      stCsTransactInfo; /* CS业务信息 */
    RRC_NAS_PS_TRANSACTION_INFO_STRU      stPsTransactInfo; /* PS业务信息 */
}RRMM_TRANSACTION_INFO_ANS_STRU;
/*****************************************************************************
 枚举名    : RRRABM_FASTDORM_INFO_ENUM_UINT32
 协议表格  :
 ASN.1描述 :
 枚举说明  : FASTDORM操作结果
*****************************************************************************/
enum RRRABM_FASTDORM_INFO_ENUM
{
    RRRABM_FASTDORM_INFO_NEED_RETRY       = 0,      /* AS需要NAS重试FD */
    RRRABM_FASTDORM_INFO_EXEC_SUCC        = 1,      /* AS执行最新FD命令成功 */
    RRRABM_FASTDORM_INFO_EXEC_FAIL        = 2,      /* 处理异常、发送失败、命令不支持等 */
    RRRABM_FASTDORM_INFO_RRC_IDLE         = 3,      /* 当前处于协议Idle状态 */
    RRRABM_FASTDORM_INFO_PCH_MAX          = 4,      /* 在P下已超过最大发送次数 */
    RRRABM_FASTDORM_INFO_BUTT
};
typedef VOS_UINT32  RRRABM_FASTDORM_INFO_ENUM_UINT32;

/*****************************************************************************
 结构名    : RRRABM_FASTDORM_INFO_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :AS主动上报NAS，请求中止FASTDORM
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      MsgHeader;      /* 消息头  */    /*_H2ASN_Skip*/
    RRRABM_FASTDORM_INFO_ENUM_UINT32     enInfoType;     /* 主动上报的信息类型 */
}RRRABM_FASTDORM_INFO_IND_STRU;

/*****************************************************************************
 枚举名    : RRC_NAS_CIPHER_ALGOR_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 当前W下加密算法枚举
*****************************************************************************/
enum RRC_NAS_CIPHER_ALGOR_ENUM
{
    RRC_NAS_CIPHER_ALGOR_UEA0                 = 0,                /* 加密未打开 */
    RRC_NAS_CIPHER_ALGOR_UEA1                 = 1,
    RRC_NAS_CIPHER_ALGOR_UEA2                 = 2,
    RRC_NAS_CIPHER_ALGOR_BUTT
};
typedef VOS_UINT8  RRC_NAS_CIPHER_ALGOR_ENUM_UINT8;

/*****************************************************************************
 结构名    : RRMM_CIPHER_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : AS主动上报NAS，加密算法更新
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      MsgHeader;      /* 消息头  */    /*_H2ASN_Skip*/
    RRC_NAS_CIPHER_ALGOR_ENUM_UINT8      enCipherAlgorForCSDomain;  /* CS域加密算法  0:uea0; 1:uea1; 2:uea2 */
    RRC_NAS_CIPHER_ALGOR_ENUM_UINT8      enCipherAlgorForPSDomain;  /* PS域加密算法  0:uea0; 1:uea1; 2:uea2 */
    VOS_UINT8                            aucReserved[2];            /* 预留位 */
}RRMM_CIPHER_INFO_IND_STRU;


/*****************************************************************************
 结构名    : RRMM_UE_OOC_STATUS_NOTIFY_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : NAS通知AS当前已经进入出服务区流程。
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头         */ /*_H2ASN_Skip*/
} RRMM_UE_OOC_STATUS_NOTIFY_IND_STRU;

/*****************************************************************************
 结构名    : RRMM_UTRAN_MODE_REQ_STRU
 结构说明  : UTRAN的工作模式信息
 1.日    期   : 2012年7月14日
   作    者   : w00176964
   修改内容   : 新建
 2.日    期   : 2012年8月8日
   作    者   : w00167002
   修改内容   : V7R1C50_GUTL_PhaseII:接口消息调整为RRMM_UTRAN_MODE_REQ，调整结构名
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头            */ /*_H2ASN_Skip*/
    RRC_NAS_UTRAN_MODE_ENUM_UINT8       enUtranMode;        /* UTRAN的工作模式*/
    VOS_UINT8                           aucReserved[3];     /* 预留位 */
}RRMM_UTRAN_MODE_REQ_STRU;

/*****************************************************************************
 结构名    : RRMM_UTRAN_MODE_CNF_STRU
 结构说明  : UTRAN的工作模式信息
 1.日    期   : 2012年8月8日
   作    者   : w00167002
   修改内容   : V7R1C50_GUTL_PhaseII:新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;        /* 消息头          */ /*_H2ASN_Skip*/
}RRMM_UTRAN_MODE_CNF_STRU;


/*****************************************************************************
 结构名    : RRMM_NET_SCAN_INFO_STRU
 结构说明  : 扫描某个频点的网络信息
 1.日    期   : 2013年8月24日
   作    者   : sunxibo
   修改内容   : 新建
 2.日    期   : 2014年11月04日
   作    者   : j00204253
   修改内容   : 新增PSC数据
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;
    VOS_UINT16                          usC1;
    VOS_UINT16                          usC2;
    VOS_UINT16                          usLac;
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
    VOS_UINT16                          usBsic;
    VOS_INT16                           sRxlev;             /* TD-SCDMA:填写rscp, 负值 */
    VOS_INT16                           sRssi;              /* TD-SCDMA:不用填写，该项仅GSM需填写 */
    VOS_UINT16                          usPSC;              /* WCDMA:该值是主扰码; TD-SCDMA:该值是4 * syncId(下行导频码) + basicMidamble，
                                                               因为TD-SCDMA中接入层使用该值 + 频点锁定一个小区 */
    VOS_UINT32                          ulCellId;
    VOS_UINT32                          ulPhyId;            /* L需要使用physical cell id和频点来确定一个小区，NetScan给锁频/锁小区单独使用，TDS下填为全1 */
    VOS_UINT32                          aulBand[2];         /* 具体取值同接口RRMM_SYS_CFG_REQ_STRU中频段参数 */
}RRMM_NET_SCAN_INFO_STRU;


/*****************************************************************************
 结构名    : RRC_NAS_NETSCAN_TDD_SEARCH_REQ_ENUM
 结构说明  : NetScan扫描完成后，接入层是否自发搜网驻留的标志位
 1.日    期   : 2015年1月248日
   作    者   : m00278711
   修改内容   : 新建
*****************************************************************************/
enum RRC_NAS_NETSCAN_TDD_SEARCH_REQ_ENUM
{
    RRC_NAS_NETSCAN_TDD_SEARCH_NONE     = 0,                /* TDSCDMA结束NETSCAN流程后，不进行自主搜网 */
    RRC_NAS_NETSCAN_TDD_SEARCH_REQ,                         /* TDSCDMA结束NETSCAN流程后，进行自主搜网 */
    RRC_NAS_NETSCAN_TDD_SEARCH_BUTT
};
typedef VOS_UINT8 RRC_NAS_NETSCAN_TDD_SEARCH_REQ_ENUM_UINT8;

/*****************************************************************************
 结构名    : RRMM_NET_SCAN_REQ_STRU
 结构说明  : MMC请求接入层进行网络扫描消息结构体
 1.日    期   : 2013年8月24日
   作    者   : sunxibo
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;    /* 消息头    */         /*_H2ASN_Skip*/
    RRC_NAS_RAT_TYPE_ENUM_UINT32        enRat;
    VOS_UINT16                          usFreqNum;
    VOS_INT16                           sPower;
    NAS_RRC_USER_SET_FREQ_BAND_STRU     stBand;        /* 根据enRat取值确定表征哪个接入技术下的频段，具体取值同接口RRMM_SYS_CFG_REQ_STRU中频段参数 */
    RRC_NAS_NETSCAN_TDD_SEARCH_REQ_ENUM_UINT8 usSearchReq;
    VOS_UINT8                           aucReserve[3];
}RRMM_NET_SCAN_REQ_STRU;

/*****************************************************************************
 结构名    : RRMM_NET_SCAN_CNF_STRU
 结构说明  : 接入层扫描结果回复消息结构体
 1.日    期   : 2013年8月24日
   作    者   : sunxibo
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;          /* 消息头    */   /*_H2ASN_Skip*/
    RRC_NAS_NET_SCAN_RESULT_ENUM_UINT8  enResult;
    RRC_NAS_NET_SCAN_CAUSE_ENUM_UINT8   enCause;
    VOS_UINT8                           ucFreqNum;
    VOS_UINT8                           aucReserve[1];
    RRMM_NET_SCAN_INFO_STRU             astNetScanInfo[RRC_NAS_NET_SCAN_MAX_FREQ_NUM];
}RRMM_NET_SCAN_CNF_STRU;

/*****************************************************************************
 结构名    : RRMM_NET_SCAN_STOP_REQ_STRU
 结构说明  : MMC请求接入层停止进行网络扫描消息结构体
 1.日    期   : 2013年8月24日
   作    者   : sunxibo
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;          /* 消息头    */   /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve[4];
}RRMM_NET_SCAN_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : RRMM_NET_SCAN_STOP_CNF_STRU
 结构说明  : 接入层停止扫描结果回复消息结构体
 1.日    期   : 2013年8月24日
   作    者   : sunxibo
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;          /* 消息头    */   /*_H2ASN_Skip*/
    VOS_UINT8                           ucFreqNum;
    VOS_UINT8                           aucReserve[3];
    RRMM_NET_SCAN_INFO_STRU             astNetScanInfo[RRC_NAS_NET_SCAN_MAX_FREQ_NUM];
}RRMM_NET_SCAN_STOP_CNF_STRU;

/*****************************************************************************
 结构名    : RRC_NAS_NCELL_MONITOR_IND_STRU
 结构说明  : 在邻区监控功能打开时，GAS发给MMC上报异系统小区信息

 1.日    期   : 2014年01月02日
   作    者   : y00142674
   修改内容   : 创建，for V9R1_SVLTE
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;          /* 消息头    */   /*_H2ASN_Skip*/
    RRC_NAS_NCELL_STATE_ENUM_UINT8      enNcellState;
    VOS_UINT8                           aucReserved[3];
} RRC_NAS_NCELL_MONITOR_IND_STRU;

typedef struct
{
    RRC_PLMN_ID_STRU                stPlmnId;
    RRC_NAS_RAT_TYPE_ENUM_UINT32    ulRat;    /* 支持的接入技术 */
    VOS_UINT16                      usLac;    /* 位置区信息,如果没有位置信息，填0xffff*/
    VOS_UINT16                      usReserved;
}RRMM_PLMN_RAT_WITH_LAC_STRU;


/*****************************************************************************
 结构名    : RRMM_SERACHED_PLMN_INFO_IND_STRU
 结构说明  : 搜网过程中搜网到的pLMN上报，该plmn必须满足驻留准则才能上报

 1.日    期   : 2014年09月30日
   作    者   : z00234330
   修改内容   : 创建，for 漫游搜网优化
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;          /* 消息头    */   /*_H2ASN_Skip*/
    VOS_UINT32                          ulAvailPlmnNum;       /* 上报PLMN个数 */

    /* 上报plmn 接入技术和位置区信息 */
    RRMM_PLMN_RAT_WITH_LAC_STRU         astPlmnWithLacList[NAS_RRC_MAX_AVAILPLMN_NUM];
}RRMM_SEARCHED_PLMN_INFO_IND_STRU;



/*****************************************************************************
 结构名    : RRRABM_VOICEPREFER_START_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :指示VOICEPREFER激活
*****************************************************************************/


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;      /* 消息头  */    /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4]; /* 保留 */
}RRRABM_VOICEPREFER_START_REQ_STRU;

/*****************************************************************************
 结构名    : RRRABM_VOICEPREFER_STOP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :指示VOICEPREFER去激活
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;      /* 消息头  */    /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4]; /* 保留 */
}RRRABM_VOICEPREFER_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : RRMM_CSG_LIST_SEARCH_REQ_STRU
 结构说明  : RRMM_CSG_LIST_SEARCH_REQ_STRU的消息结构体

 1.日    期   : 2015年09月02日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                            /* 消息头  */    /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[4]; /* 保留 */
}RRMM_CSG_LIST_SEARCH_REQ_STRU;
/*****************************************************************************
 结构名    : RRMM_CSG_LIST_SEARCH_CNF_STRU
 结构说明  : RRMM_CSG_LIST_SEARCH_CNF_STRU的消息结构体

 1.日    期   : 2015年09月02日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头   */      /*_H2ASN_Skip*/
    RRC_NAS_CSG_SEARCH_RLT_ENUM_UINT8   enSearchRlt;        /* 搜索结果 */
    VOS_UINT8                           aucReserved[3];

    /* CSG LIST PLMN搜索结果 */
    RRMM_CSG_LIST_SEARCHED_RESULT_STRU  stCsgListSearchedResult;
}RRMM_CSG_LIST_SEARCH_CNF_STRU;
/*****************************************************************************
 结构名    : RRMM_TRANSACTION_STATUS_NOTIFY_STRU
 结构说明  : RRMM_TRANSACTION_STATUS_NOTIFY的消息结构体

 1.日    期   : 2015年06月01日
   作    者   : j00174725
   修改内容   : DTS2015053000044
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头  */    /*_H2ASN_Skip*/
    RRMM_TRANSACTION_STATUS_ENUM_UINT8  enTransActionStatus;
    VOS_UINT8                           aucRsv[3];                              /* 保留 */
}RRMM_TRANSACTION_STATUS_NOTIFY_STRU;


/*****************************************************************************
 结构名    : RRMM_LCS_STATE_ENUM
 结构说明  : RRLP procedure、LCS procedure over RRC流程的状态
 1.日    期   : 2015年11月9日
   作    者   : l00198894
   修改内容   : 新建
*****************************************************************************/
enum RRMM_LCS_STATE_ENUM
{
    RRMM_LCS_STATE_FINISH               = 0,                                    /* RRLP procedure、LCS procedure over RRC流程结束 */
    RRMM_LCS_STATE_START,                                                       /* RRLP procedure、LCS procedure over RRC流程启动 */
    RRMM_LCS_STATE_BUTT
};
typedef VOS_UINT8 RRMM_LCS_STATE_ENUM_UINT8;

/*******************************************************************************
 结构名    : RRMM_LCS_STATE_IND_STRU
 结构说明  : RRMM_LCS_STATE_IND的消息对应的结构，
             RRLP procedure、LCS procedure over RRC流程的状态

  1.日    期   : 2015年11月9日
    作    者   : l00198894
    修改内容   : 新增结构
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    RRMM_LCS_STATE_ENUM_UINT8           enState;
    VOS_UINT8                           aucReserved[3];
}RRMM_LCS_STATE_IND_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/* 9.2 AS 获取 MM/GMM 安全信息接口 （新增接口） */
/*****************************************************************************
 Prototype      : MM_GetSecurityInfo
 Description    : AS 通过此接口函数获取 CS 域安全信息和 IMSI

 Input          : pCsInfo AS 层提供的信息结构指针
 Output         : pCsInfo MM 填充结构中各成员,包含安全信息和 IMSI
 Return Value   : ---
 Calls          : ---
 Called By      : WAS/GAS

 History        : ---
  1.Date        : 2005-09-09
    Author      : sxbo
    Modification: Creation
*****************************************************************************/
extern VOS_VOID MM_GetSecurityInfo(MM_CSPS_INFO_ST *pCsInfo);

/*****************************************************************************
 Prototype      :  GMM_GetSecurityInfo
 Description    :  查询GMM的安全上下文信息函数
 Input          :
 Output         : ---
 Return Value   : 1     返回成功
                  0     返回失败
 Calls          : ---
 Called By      :

 History        : ---
  1.Date        : ---
    Author      : ---
    Modification: ---
*****************************************************************************/
extern VOS_VOID GMM_GetSecurityInfo(MM_CSPS_INFO_ST *pPsInfo);

/*****************************************************************************
 Prototype      :  GMM_GetTlliInfo
 Description    :  获取当前的TLLI
 Input          :
 Output         : ---
 Return Value   : void
 Calls          : ---
 Called By      :

 History        : ---
  1.Date        : ---
    Author      : ---
    Modification: ---
*****************************************************************************/
extern VOS_VOID GMM_GetTlliInfo(VOS_UINT32 *pulNewTlli, VOS_UINT32 *pulOldTlli);

/* 9.3 NAS 获取 BAND 信息接口 （新增接口） */
/*****************************************************************************
 Prototype      : GAS_SCELL_BAND_INFO
 Description    : NAS 通过此接口函数获取 GAS BAND 信息

 Input          : pstBandInfo NAS 层提供的 BAND 信息结构指针
 Output         : pstBandInfo AS 填充结构中对应成员
 Return Value   : ---
 Calls          : ---
 Called By      : NAS

 History        : ---
  1.Date        :  GAS_GetSCellBandInfo
    Author      :
    Modification: Creation
*****************************************************************************/
extern VOS_VOID GAS_SCELL_BAND_INFO( AS_NAS_SCELL_BAND_INFO_ST *pstBandInfo );
extern VOS_VOID GAS_GetSCellBandInfo( AS_NAS_SCELL_BAND_INFO_ST *pstBandInfo );

extern VOS_UINT32 MMC_ComJudgeLai(RRC_PLMN_ID_STRU stPlmn,
                                    VOS_UINT16 usLac,PS_BOOL_ENUM_UINT8 *penLaiValidFlg);


/* 9.4 AS 获取 通过调用此接口来获取NAS的相关信息。比如说PLMN的信息等。（新增接口） */
/*****************************************************************************
 Prototype      : MM_GetSecurityInfo
 Description    : AS 获取 通过调用此接口来获取NAS的相关信息。比如说PLMN的信息等。
                  pMmInfo AS 层提供的信息结构指针, 根据ucType的不同，获取不同的
                  数据结构。
 Input          : ucType -- 0：    表示获取PLMN信息与卡状态信息。
 Output         : pMmInfo -- MM层填充结构中各成员,包含PLMN的信息
 Return Value   : ---
 Calls          : ---
 Called By      : WAS/GAS

 History        : ---
  1.Date        : 2005-09-09
    Author      : sxbo
    Modification: Creation
*****************************************************************************/
extern VOS_VOID MM_GetNasInfo(MM_INFO_ST *pstMmInfo);

/*****************************************************************************
 函 数 名  : NAS_MMC_GetEHPlmn
 功能描述  : 提供给接入层获取EHPLMN的API接口函数
 输入参数  : 无
 输出参数  : RRC_PLMN_ID_STRU *pstEHPlmn:EHPLMN列表，需要能存储32个PLMNID
             VOS_UINT32 *pulEHPlmnNum:EHPLMN个数
 返 回 值  : VOS_OK :获取成功，返回EHPLMN或者home plmn(不支持EHPLMN或者EHPLMN列表为空)
             VOS_ERR:获取失败，参数检查失败或者无卡或者卡被锁定
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月11日
    作    者   : s46746
    修改内容   : 新生成函数

*****************************************************************************/
extern VOS_UINT32 NAS_MMC_GetEHPlmn(RRC_PLMN_ID_STRU *pstEHPlmn, VOS_UINT8 *pucEHPlmnNum);

/*****************************************************************************
 函 数 名  : NAS_GetTransactionInfo
 功能描述  : 提供给接入层获取业务信息函数
 输入参数  : 无
 输出参数  : RRC_NAS_CS_TRANSACTION_INFO_STRU *pstCsTransactInfo:CS业务信息
             RRC_NAS_PS_TRANSACTION_INFO_STRU *pstPsTransactInfo:PS业务信息
 返 回 值  : VOS_OK :获取成功
             VOS_ERR:获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月12日
    作    者   : s46746
    修改内容   : 新生成函数

*****************************************************************************/
extern VOS_UINT32 NAS_GetTransactionInfo(RRC_NAS_CS_TRANSACTION_INFO_STRU *pstCsTransactInfo,
                                         RRC_NAS_PS_TRANSACTION_INFO_STRU *pstPsTransactInfo);

enum CSPS_REG_STATE_ENUM
{
    NAS_RRC_CSPS_ATTACH,
    NAS_RRC_CS_DETACH,
    NAS_RRC_PS_DETACH,
    NAS_RRC_CSPS_DETACH
};
typedef VOS_UINT32 CSPS_REG_STATE_ENUM_UINT32;
/*****************************************************************************
 AS查询CS,PS的注册状态API接口
*****************************************************************************/
extern VOS_VOID NVIM_Read_DrxFlag (VOS_VOID);


/*****************************************************************************
 PPP拨号后的速率气泡显示，分两种情况处理:
 1.2G模式下，则根据当前驻留的小区模式是GSM/GPRS/EDGE来决定速率气泡的显示,对应如下:
     GSM  - 9600
     GPRS - 85600
     EDGE - 296000
     默认 -
 2.3g模式下，则根据RRC版本和HSDPA的category信息来决定速率气泡的显示，对应如下:
     RRC版本为R99   - 384000
     RRC版本为非R99 - 判断HSDPA的category信息
                   6  - 3600000
                   8  - 7200000
                   9  - 10200000
                   10 - 14400000
                   12 - 1800000
                   14 - 21600000
                   18 - 28800000
                   24 - 43200000
                   26 - 57600000
                   28 - 86400000
     有扩展的category的话，默认 - 21600000
     无扩展的category的话，默认 - 7200000
*****************************************************************************/
enum PPP_DIAL_RATE_DISPLAY_ENUM
{
    PPP_DIAL_RATE_DISPLAY_GSM = 0,
    PPP_DIAL_RATE_DISPLAY_GPRS,
    PPP_DIAL_RATE_DISPLAY_EDGE,

    PPP_DIAL_RATE_DISPLAY_R99,
    PPP_DIAL_RATE_DISPLAY_DPA_CATEGORY_6,
    PPP_DIAL_RATE_DISPLAY_DPA_CATEGORY_8,
    PPP_DIAL_RATE_DISPLAY_DPA_CATEGORY_9,
    PPP_DIAL_RATE_DISPLAY_DPA_CATEGORY_10,
    PPP_DIAL_RATE_DISPLAY_DPA_CATEGORY_12,
    PPP_DIAL_RATE_DISPLAY_DPA_CATEGORY_14,
    PPP_DIAL_RATE_DISPLAY_DPA_CATEGORY_18,
    PPP_DIAL_RATE_DISPLAY_DPA_CATEGORY_24,
    PPP_DIAL_RATE_DISPLAY_DPA_CATEGORY_26,
    PPP_DIAL_RATE_DISPLAY_DPA_CATEGORY_28,

    PPP_DIAL_RATE_DISPLAY_BUTT
};

typedef VOS_UINT32 PPP_DIAL_RATE_DISPLAY_ENUM_UINT32;

/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
/*****************************************************************************
 结构名    : RRMM_NACK_DATA_IND_STRU
 结构说明  : 消息在底层发送失败指示消息的结构

  1.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级，DTS20121809369
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    NAS_MSG_STRU                        stNackMsg;
}RRMM_NACK_DATA_IND_STRU;
/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

/*****************************************************************************
 枚举名    : RRC_NAS_SESSION_TYPE_ENUM_UINT8
 枚举说明  : SESSION类型
 1.日    期   : 2014年5月22日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
enum RRC_NAS_SESSION_TYPE_ENUM
{
    RRC_NAS_SESSION_TYPE_NONE                           = 0,

    RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CALL,
    RRC_NAS_SESSION_TYPE_CS_MO_EMERGENCY_CALL,
    RRC_NAS_SESSION_TYPE_CS_MO_SS,
    RRC_NAS_SESSION_TYPE_CS_MO_SMS,
    RRC_NAS_SESSION_TYPE_CS_MT_NORMAL_CALL,
    RRC_NAS_SESSION_TYPE_CS_MT_EMERGENCY_CALLBACK,      /* 待定，eCall的回呼场景 */
    RRC_NAS_SESSION_TYPE_CS_MT_SS,
    RRC_NAS_SESSION_TYPE_CS_MT_SMS,
    RRC_NAS_SESSION_TYPE_CS_LAU,
    RRC_NAS_SESSION_TYPE_CS_DETACH,
    RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CSFB,
    RRC_NAS_SESSION_TYPE_CS_MO_EMERGENCY_CSFB,
    RRC_NAS_SESSION_TYPE_CS_MT_CSFB,
    RRC_NAS_SESSION_TYPE_PS_CONVERSAT_CALL,
    RRC_NAS_SESSION_TYPE_PS_STREAM_CALL,
    RRC_NAS_SESSION_TYPE_PS_INTERACT_CALL,
    RRC_NAS_SESSION_TYPE_PS_BACKGROUND_CALL,
    RRC_NAS_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL,
    RRC_NAS_SESSION_TYPE_PS_MO_SMS,
    RRC_NAS_SESSION_TYPE_PS_MT_SMS,
    RRC_NAS_SESSION_TYPE_PS_ATTACH,
    RRC_NAS_SESSION_TYPE_PS_RAU,
    RRC_NAS_SESSION_TYPE_PS_DETACH,

    RRC_NAS_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 RRC_NAS_SESSION_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名    : RRMM_BEGIN_SESSION_NOTIFY_STRU
 结构说明  : SESSION开始指示
 1.日    期   : 2014年5月22日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enSessionType;
    VOS_UINT8                           aucReserved[3];
}RRMM_BEGIN_SESSION_NOTIFY_STRU;

/*****************************************************************************
 结构名    : RRMM_END_SESSION_NOTIFY_STRU
 结构说明  : SESSION终止指示
 1.日    期   : 2014年5月22日
   作    者   : h00246512
   修改内容   : 新建
 2.日    期   : 2014年7月17日
   作    者   : b00269685
   修改内容   : 增加delay时长
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    PS_BOOL_ENUM_UINT8                  enCsRelAll;
    PS_BOOL_ENUM_UINT8                  enPsRelAll;
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enSessionType;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulDelayTime;
}RRMM_END_SESSION_NOTIFY_STRU;


/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-13, begin */
/*****************************************************************************
 枚举名     :RRC_NAS_SIGNAL_INFO_ENUM
 协议表格  :
 ASN.1描述   :
 枚举说明 : 异系统互操作时携带的连接类型
*****************************************************************************/
typedef enum
{
    RRC_NAS_NO_SIG_INF0                              = 0,                            /* 无信令连接 */
    RRC_NAS_SIG_CS,                                                                  /* 只存在CS连接 */
    RRC_NAS_SIG_PS,                                                                  /* 只存在PS连接 */
    RRC_NAS_SIG_CSANDPS,                                                             /* 同时存在CS和PS连接 */
    RRC_NAS_SIG_BUTT
}RRC_NAS_SIGNAL_INFO_ENUM;
typedef VOS_UINT8  RRC_NAS_SIGNAL_INFO_ENUM_UINT8;

/*****************************************************************************
 结构名    : RRMM_HANDOVER_INFO_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : AS通知NAS的MMC模块当前切换信息
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头         */ /*_H2ASN_Skip*/
    VOS_UINT8                           ucSrvccFlag;                            /* 当前是否为SRVCC流程 */
    RRC_NAS_SIGNAL_INFO_ENUM_UINT8      enSignalInfo;                           /* 信令连接的类型 */
    VOS_UINT8                           aucRsv[2];
} RRMM_HANDOVER_INFO_IND_STRU;

/*****************************************************************************
 结构名    : RRMM_CLASSMARK_CHANGE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GAS上报CLASSMARK能力
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */

    VOS_UINT8                           ucClassmark2Len;                        /* Classmark2 长度，该长度为0代表CLASSMARK2无效 */
    VOS_UINT8                           aucClassmark2[MS_CLASSMARK2_MAX_LEN];   /* Classmark2 内容 */

    VOS_UINT8                           ucClassmark3FddLen;                     /* Fdd Classmark3 长度，该长度为0代表Fdd CLASSMARK3无效 */
    VOS_UINT8                           aucClassmark3Fdd[MS_CLASSMARK3_MAX_LEN];/* Fdd Classmark3 内容 */

    VOS_UINT8                           ucClassmark3TddLen;                     /* Tdd Classmark3 长度，该长度为0代表Tdd CLASSMARK3无效 */
    VOS_UINT8                           aucClassmark3Tdd[MS_CLASSMARK3_MAX_LEN];/* Tdd Classmark3 内容 */

    VOS_UINT8                           aucReserved[1];                         /* 4字节对齐，保留 */
} RRMM_CLASSMARK_CHANGE_IND_STRU;
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-13, end */

/*******************************************************************************
 结构名    : RRMM_TDS_NCELL_INFO_STRU
 结构说明  : GSM下的TDS频点列表

 1.日    期   : 2015年01月06日
   作    者   : h00166210
   修改内容   : 新生成结构

*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTdsArfcnNum;                              /* TDS频点个数，0表示TDS频点不存在 */
    VOS_UINT8                           aucRsv[1];                                  /* 保留位*/
    VOS_UINT16                          ausTdsArfcnList[RRMM_TDS_ARFCN_MAX_NUM]; /* 频点列表 */
}RRMM_TDS_NCELL_INFO_STRU;

/*******************************************************************************
 结构名    : RRMM_LTE_NCELL_INFO_STRU
 结构说明  : GSM下的LTE频点列表

 1.日    期   : 2015年01月06日
   作    者   : h00166210
   修改内容   : 新生成结构
 2.日    期   : 2015年7月20日
   作    者   : w000316404
   修改内容   : R11协议升级(LTE频点配置值扩展)
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLteArfcnNum;                              /* LTE频点个数，0表示LTE频点不存在 */
    VOS_UINT8                           aucRsv[3];                                  /* 保留位*/
    VOS_UINT32                          aulLteArfcnList[RRMM_LTE_ARFCN_MAX_NUM]; /* 频点列表 */
}RRMM_LTE_NCELL_INFO_STRU;

/*****************************************************************************
 枚举名     :RRMM_GSM_BANDINDICATOR_ENUM
 协议表格   :
 ASN.1描述  :
 枚举说明   :2G小区频带指示
*****************************************************************************/
enum RRMM_GSM_BANDINDICATOR_ENUM
{
    RRMM_GSM_BANDINDICATOR_DCS1800                          = 0,
    RRMM_GSM_BANDINDICATOR_PCS1900                             ,

    RRMM_GSM_BANDINDICATOR_BUTT
};
typedef VOS_UINT16  RRMM_GSM_BANDINDICATOR_ENUM_UINT16;

/*******************************************************************************
 结构名    : RRMM_GSM_FREQ_INFO_STRU
 结构说明  : GSM频点信息

 1.日    期   : 2015年01月06日
   作    者   : h00166210
   修改内容   : 新生成结构

*******************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmArfcn;     /* 绝对频点号 */
    RRMM_GSM_BANDINDICATOR_ENUM_UINT16  enBandInd;      /* Band指示, 指示当前频点是 1800 系统 或 1900 系统 */
}RRMM_GSM_FREQ_INFO_STRU;

/*******************************************************************************
 结构名    : RRMM_GSM_FREQ_INFO_STRU
 结构说明  : GSM频点列表

 1.日    期   : 2015年01月06日
   作    者   : h00166210
   修改内容   : 新生成结构

*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucGsmArfcnNum;                                      /* GSM频点个数，0表示GSM频点不存在 */
    VOS_UINT8                           ucGsmMaArfcnNum;                                    /* 业务频点个数, 如当前不是G主模,则为0 */
    VOS_UINT8                           aucRsv[2];
    RRMM_GSM_FREQ_INFO_STRU             astGsmArfcnList[RRMM_GSM_MAX_USING_ARFCN_NUM];   /* 服务小区及邻区频点列表, 服务小区频点在第一位 */
    RRMM_GSM_FREQ_INFO_STRU             astGsmMaArfcnList[RRMM_GSM_MA_ARFCN_MAX_NUM];    /* 业务频点信息，此信息只在G主模下有效 */
}RRMM_GSM_FREQ_INFO_LIST_STRU;

/*******************************************************************************
 结构名    : RRMM_WCDMA_FREQ_INFO_STRU
 结构说明  : WCDMA频点列表

 1.日    期   : 2015年01月06日
   作    者   : h00166210
   修改内容   : 新生成结构

*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucWcdmaArfcnNum;                                        /* W频点个数，0表示WCDMA频点不存在 */
    VOS_UINT8                           aucRsv[3];                                              /* 保留位*/
    VOS_UINT16                          ausWcdmaArfcnList[RRMM_WCDMA_MAX_USING_ARFCN_NUM];   /* 频点列表 */
}RRMM_WCDMA_FREQ_INFO_LIST_STRU;

/*******************************************************************************
 结构名    : RRMM_USING_FREQ_IND_STRU
 结构说明  : RRMM_USING_FREQ_IND的消息对应的结构，
             包括GUTL主模下驻留以及正在测量的本系统以及异系统频点信息，服务小区所在频点放在第一个位置，
             其余频点按照能量排序

 1.日    期   : 2015年01月06日
   作    者   : h00166210
   修改内容   : 新生成结构

*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                       /*_H2ASN_Skip*/

    RRMM_GSM_FREQ_INFO_LIST_STRU        stGsmFreqInfo;                     /* GSM频点列表信息 */

    RRMM_WCDMA_FREQ_INFO_LIST_STRU      stWcdmaFreqInfo;                   /* WCDMA频点列表信息 */

    RRMM_TDS_NCELL_INFO_STRU            stTdsFreqInfo;                     /* TDS频点列表信息 */

    RRMM_LTE_NCELL_INFO_STRU            stLteFreqInfo;                     /* LTE频点列表信息 */

    PS_BOOL_ENUM_UINT8                  enCsExistFlag;                     /* PS_FALSE 表示不存在CS连接 */
    PS_BOOL_ENUM_UINT8                  enPsExistFlag;                     /* PS_FALSE 表示不存在PS连接 */
    VOS_UINT8                           aucRsv[2];
}RRMM_USING_FREQ_IND_STRU;

/*****************************************************************************
 结构名    : RRMM_CONNECTED_LOCATION_INFO_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 给NAS上报位置信息结构原语
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_PLMN_ID_STRU                    PlmnId;             /* 本小区PLMN ID  */
    VOS_UINT32                          ulCellId;           /* 当前驻留小区ID */
    VOS_UINT16                          usLac;
    VOS_UINT8                           ucRac;
    VOS_UINT8                           aucReserve1;     /* 保留 */
}RRMM_CONNECTED_LOCATION_INFO_IND_STRU;

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
    NAS_RRC_MSG_TYPE_ENUM_UINT16        enMsgID;    /*_H2ASN_MsgChoice_Export NAS_RRC_MSG_TYPE_ENUM_UINT32*/
                                                    /* 为了兼容NAS的消息头定义，所以转换ASN.1使用NAS_RRC_MSG_TYPE_ENUM_UINT32 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_RRC_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}NAS_RRC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    NAS_RRC_MSG_DATA                    stMsgData;
}NasRrcInterface_MSG;

/*****************************************************************************
  10 函数声明
*****************************************************************************/
/*
extern VOS_BOOL  RRC_GET_DrxFlag (VOS_VOID);
*/

extern VOS_UINT32 GASGCOM_GetDisplayRate(PPP_DIAL_RATE_DISPLAY_ENUM_UINT32 *penRateDisplay);

extern VOS_VOID GASGCOM_UpdateCustomizeNv(VOS_VOID);

#if (FEATURE_ON == FEATURE_LTE)
/* API约束1: 禁止LTE FDD NV项必须是打开的，
   API约束2: 必须给G模发过开机
   API约束3: G模是从模
   不满足其中的任何一个条件，都属于无效调用
*/
extern VOS_UINT32 GASGCOM_GetMsCapability(RRC_PLMN_ID_STRU *pstPlmn,
                                               NAS_GAS_MS_CAP_TYPE_ENUM_UINT8 enCapType,
                                               VOS_UINT16 usSize,
                                               VOS_UINT8 *pucData);
#endif

extern VOS_UINT32  TAF_IsNormalSrvStatus(VOS_VOID);

/*****************************************************************************
 函 数 名  : NAS_MM_GetLauRequestInfo
 功能描述  : 提供给接入层获取LAU相关信息
 输入参数  : pstLauReqMsg: LAU消息内容，是 LAU 消息内容中，是NAS_EST_REQ中的NAS_MSG_STRU结构
 输出参数  : penLauType:LAU类型
             pucFollowOnFlg:是否有 follow on标志
             penAdditionUpdatePara: Additionupdate参数类型
 返 回 值  : VOS_OK:获取成功
             VOS_ERR:获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月12日
    作    者   : j00174725
    修改内容   : 新生成函数DTS2015040705043

  注:输出参数  : penLauType pucFollowOnFlg penAdditionUpdatePara有效性由调用都保证
*****************************************************************************/
extern VOS_UINT32 NAS_MM_GetLauRequestInfo(
    NAS_MSG_STRU                           *pstLauReqMsg,
    NAS_LAU_TYPE_ENUM_UINT8                *penLauType,
    VOS_UINT8                              *pucFollowOnFlg,
    NAS_ADDITION_UPDATE_PARA_ENUM_UINT8    *penAdditionUpdatePara
);

/*****************************************************************************
 函 数 名  : NAS_MM_GetL3ReqMsgPd
 功能描述  : 提供给接入层获取Req消息中的PD信息
 输入参数  : pstSendMsg: Data Req消息内容 RRMM_DATA_REQ_STRU结构
 输出参数  : ucPd:VOS_UINT8类型

 返 回 值  : VOS_OK:获取成功
             VOS_ERR:获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
extern VOS_UINT32 NAS_MM_GetL3ReqMsgPd(
    RRMM_DATA_REQ_STRU                     *pstSendMsg,
    VOS_UINT8                              *pucPd
);

/*****************************************************************************
 函 数 名  : NAS_MM_GetL3RcvMsgPd
 功能描述  : 提供给接入层获取Ind消息中的PD信息
 输入参数  : pstSendMsg: Data Ind消息内容 RRMM_DATA_IND_STRU结构
 输出参数  : ucPd:VOS_UINT8类型

 返 回 值  : VOS_OK:获取成功
             VOS_ERR:获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
extern VOS_UINT32 NAS_MM_GetL3RcvMsgPd(
    RRMM_DATA_IND_STRU                     *pstRcvMsg,
    VOS_UINT8                              *pucPd
);

/*****************************************************************************
 函 数 名  : NAS_MM_GetSmsFilterFlg
 功能描述  : 提供给接入层获取过滤功能是否打开的Nv
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: 需要进行过滤
             VOS_FALSE:不需要进行过滤
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
extern VOS_UINT32 NAS_MM_GetSmsFilterFlg( VOS_VOID );

/*****************************************************************************
 函 数 名  : NAS_GetT3212Len
 功能描述  : 提供给TRC获取T3212长度
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月16日
    作    者   : h00360002
    修改内容   : 新生成函数
*****************************************************************************/
extern VOS_UINT32 NAS_GetT3212Len( VOS_VOID );

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

#endif /* end of NasRrcInterface.h */
