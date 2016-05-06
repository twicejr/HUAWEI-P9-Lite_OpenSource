/******************************************************************************


        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : LRrcLNasInterface.h
    Description : 描述RRC与NAS之间的接口
    History     :
      1.  hanlufeng   41410  2008-09-06  Draft Enact
      2.  liutao      38432  2008-09-06  修改
      3.  Wang Yangcai 49178  2008-12-22  BA8D00775
      4.  Wang Yangcai 49178  2009-04-24  BJ9D00479:修改NAS INFO CHANGE结构体
      5.  hanlufeng    41410  2009-04-29  BJ9D00156 增加AC接口
      6.  leili      00132387 2009-06-04  BJ9D00867 增加PLMN ID接口
      7.  zhengjunyan 00148421 2009-06-18 BJ9D00709 修改接口
      8.  xuruimei    49630    2009-09-29 BJ9D02012 明确RRC_MM_REL_IND原语各原因值携带的场景和处理方式
      9.  lidui 00143774      2009-03-12  BJ9D02807:将最大NAS消息长度设置为1024
      10. wangyue 00151278    2011-11-02 DTS2011103103096:SYSCFG特性合入
******************************************************************************/

#ifndef __LRRCLNASINTERFACE_H__
#define __LRRCLNASINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "LPSCommon.h"
#include "ComInterface.h"
#include "LNasNvInterface.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/

/* 等效PLMN最大个数 */
#define LRRC_LNAS_MAX_EQUPLMN_NUM         16

/* EHPLMN最大个数 */
#define LRRC_LNAS_MAX_EHPLMN_NUM          (LRRC_LNAS_MAX_EQUPLMN_NUM + 1)

/* FORBID LA 最大个数 */
#define LRRC_LNAS_MAX_FORBLA_NUM          64

/* lishangfeng bg begin */
/* FORBID LA 最大个数 */
#define LRRC_LNAS_BG_MAX_FORBLA_NUM       16

#define LRRC_LNAS_BG_MAX_SRCH_PLMN_NUM    16

#define LRRC_LNAS_MAX_RAT_NUM             (3)

/* lishangfeng bg end */


/* FORBID TA 最大个数 */
#define LRRC_LNAS_MAX_FORBTA_NUM          64

/* 高质量PLMN 最大个数 */
#define LRRC_LNAS_MAX_HIGH_PLMN_NUM       48

/* 低质量PLMN 最大个数 */
#define LRRC_LNAS_MAX_LOW_PLMN_NUM        48

/* 指定plmn搜索失败后，上报的plmn最大数  */
#define LRRC_LNAS_MAX_SEARCHED_PLMN_NUM   16

/*begin:add by wangmiao00272217 for 漫游搜网优化*/
#define LRRC_LMM_MAX_SEARCHED_TAI_NUM    16
/*end:add by wangmiao00272217 for 漫游搜网优化*/

/* NAS数据最大长度 */
#define LRRC_LNAS_MAX_DATA_LENGTH         1024

/* 从GU切换到L，LRRC上报的安全参数的长度*/
#define LRRC_LNAS_GU2L_HO_SECU_PARA_LEN   6



/* 各种 UE ID 存放的最大字节数目,包括LENTH字节:
   The IMSI shall not exceed 15 digits, ie 7 and a half of bytes;
   the TMSI/P-TMSI is 4 octets long;
   the IMEI is composed of 15 digits;
   the IMEISV is 16 digits;
*/
#define LRRC_LNAS_MAX_UEID_BUF_SIZE       10                  /* UNIT: BYTE  */

#define LRRC_LNAS_MAX_ASME_KEY_LEN        32

#define LRRC_LNAS_MAX_RAB_SETUP_NUM       11                  /* 建立的最大RAB数  */
/* ncell spec search begin */
#define LRRC_LNAS_MAX_ARFCN_NUM          (8)                  /* LTE频点列表最大个数 */
/* ncell spec search end */

#define LRRC_LNAS_LTE_CELL_ID_MAX_NUM    (8)                  /* LTE小区ID最大个数 */

#define LRRC_LNAS_NETSCAN_MAX_FREQ_NUM   (20)

#define LRRC_LMM_BG_HRPD_MAX_SUBNET_NUM   16
#define LRRC_LMM_HRPD_SUBNET_MAX_LEN      16


#define LRRC_LMM_MAX_PLMN_CSG_ID_NUM             (35)
#define LRRC_LMM_MAX_HOME_NODEB_NAME_LEN         (48)


#define LMM_LRRC_MSG_HDR                  (PS_MSG_ID_NAS_TO_RRC_BASE)
#define LRRC_LMM_MSG_HDR                  (PS_MSG_ID_RRC_TO_NAS_BASE)
#define LRABM_LRRC_MSG_HDR                (PS_MSG_ID_NAS_TO_RRC_BASE + 0x40)
#define LRRC_LRABM_MSG_HDR                (PS_MSG_ID_RRC_TO_NAS_BASE + 0x40)

#define LRRC_LRRC_IsGUCRedir_Flow()      ( LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2W_REDIR_FAIL || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2W_START_REDIR || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2G_REDIR_FAIL || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2G_START_REDIR || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2T_START_REDIR || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2C_START_RESEL || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2C_RESEL_FAIL || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2C_START_REDIR || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2C_REDIR_FAIL || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2W_START_HO || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2W_HO_FAIL || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2W_START_RESEL || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2W_RESEL_FAIL || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2G_START_HO || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2G_HO_FAIL || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2G_START_RESEL || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2G_RESEL_FAIL || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2G_START_CCO || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2G_CCO_FAIL || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2T_START_HO || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2T_START_RESEL)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : LRRC_LNAS_MSG_ID_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : NAS与RRC的消息原语类型
*****************************************************************************/
enum LRRC_LNAS_MSG_ID_ENUM
{
    /* MM发给RRC的原语 */
    ID_LRRC_LMM_START_REQ                 = (LMM_LRRC_MSG_HDR + 0x00),   /* _H2ASN_MsgChoice LRRC_LMM_START_REQ_STRU */
    ID_LRRC_LMM_PLMN_SEARCH_REQ           = (LMM_LRRC_MSG_HDR + 0x01),   /* _H2ASN_MsgChoice LRRC_LMM_PLMN_SEARCH_REQ_STRU */
    ID_LRRC_LMM_PLMN_SEARCH_STOP_REQ      = (LMM_LRRC_MSG_HDR + 0x02),   /* _H2ASN_MsgChoice LRRC_LMM_PLMN_SEARCH_STOP_REQ_STRU */
    ID_LRRC_LMM_EQU_PLMN_NOTIFY_REQ       = (LMM_LRRC_MSG_HDR + 0x03),   /* _H2ASN_MsgChoice LRRC_LMM_EQU_PLMN_NOTIFY_REQ_STRU */
    ID_LRRC_LMM_NAS_INFO_CHANGE_REQ       = (LMM_LRRC_MSG_HDR + 0x04),   /* _H2ASN_MsgChoice LRRC_LMM_NAS_INFO_CHANGE_REQ_STRU */
    ID_LRRC_LMM_CELL_SELECTION_CTRL_REQ   = (LMM_LRRC_MSG_HDR + 0x05),   /* _H2ASN_MsgChoice LRRC_LMM_CELL_SELECTION_CTRL_REQ_STRU */
    ID_LRRC_LMM_EST_REQ                   = (LMM_LRRC_MSG_HDR + 0x06),   /* _H2ASN_MsgChoice LRRC_LMM_EST_REQ_STRU */
    ID_LRRC_LMM_REL_REQ                   = (LMM_LRRC_MSG_HDR + 0x07),   /* _H2ASN_MsgChoice LRRC_LMM_REL_REQ_STRU */
    ID_LRRC_LMM_DATA_REQ                  = (LMM_LRRC_MSG_HDR + 0x08),   /* _H2ASN_MsgChoice LRRC_LMM_DATA_REQ_STRU */
    ID_LRRC_LMM_POWER_OFF_REQ             = (LMM_LRRC_MSG_HDR + 0x09),   /* _H2ASN_MsgChoice LRRC_LMM_POWER_OFF_REQ_STRU */
    ID_LRRC_LMM_SUSPEND_RSP               = (LMM_LRRC_MSG_HDR + 0x0a),   /* _H2ASN_MsgChoice LRRC_LMM_SUSPEND_RSP_STRU */
    ID_LRRC_LMM_RESUME_RSP                = (LMM_LRRC_MSG_HDR + 0x0b),   /* _H2ASN_MsgChoice LRRC_LMM_RESUME_RSP_STRU */
    ID_LRRC_LMM_SUSPEND_REQ               = (LMM_LRRC_MSG_HDR + 0x0c),   /* _H2ASN_MsgChoice LRRC_LMM_SUSPEND_REQ_STRU */
    ID_LRRC_LMM_SECU_PARA_RSP             = (LMM_LRRC_MSG_HDR + 0x0d),   /* _H2ASN_MsgChoice LRRC_LMM_SECU_PARA_RSP_STRU */
    ID_LRRC_LMM_SYS_CFG_REQ               = (LMM_LRRC_MSG_HDR + 0x0e),   /* _H2ASN_MsgChoice LRRC_LNAS_SYS_CFG_REQ_STRU */
    ID_LRRC_LMM_MBMS_SESSION_CFG_REQ      = (LMM_LRRC_MSG_HDR + 0x0f),   /* _H2ASN_MsgChoice LRRC_LMM_MBMS_SESSION_CFG_REQ_STRU */
    ID_LRRC_LMM_OOS_STATE_REQ             = (LMM_LRRC_MSG_HDR + 0x10),   /* _H2ASN_MsgChoice LRRC_LMM_OOS_STATE_REQ_STRU */
    ID_LRRC_LMM_CLEAR_BUFF_NOTIFY         = (LMM_LRRC_MSG_HDR + 0x11),   /* _H2ASN_MsgChoice LRRC_LMM_CLEAR_BUFF_NOTIFY_STRU */
    ID_LRRC_LMM_BG_PLMN_SEARCH_REQ        = (LMM_LRRC_MSG_HDR + 0x12),   /* _H2ASN_MsgChoice LRRC_LMM_BG_PLMN_SEARCH_REQ_STRU */
    ID_LRRC_LMM_BG_PLMN_SEARCH_STOP_REQ   = (LMM_LRRC_MSG_HDR + 0x13),   /* _H2ASN_MsgChoice LRRC_LMM_BG_PLMN_SEARCH_REQ_STOP_STRU */
    ID_LRRC_LMM_SUSPEND_REL_REQ           = (LMM_LRRC_MSG_HDR + 0x14),   /* _H2ASN_MsgChoice LRRC_LMM_SUSPEND_REL_REQ_STRU */
    ID_LRRC_LMM_OTHER_MODEM_INFO_NOTIFY   = (LMM_LRRC_MSG_HDR + 0x15),    /* _H2ASN_MsgChoice LMM_LRRC_OTHER_MODEM_INFO_NOTIFY_STRU*/
    ID_LRRC_LMM_BEGIN_SESSION_NOTIFY      = (LMM_LRRC_MSG_HDR + 0x16),    /* _H2ASN_MsgChoice LRRC_LMM_BEGIN_SESSION_NOTIFY_STRU*/
    ID_LRRC_LMM_END_SESSION_NOTIFY        = (LMM_LRRC_MSG_HDR + 0x17),    /* _H2ASN_MsgChoice LRRC_LMM_END_SESSION_NOTIFY_STRU*/
    ID_LMM_LRRC_NETSCAN_REQ               = (LMM_LRRC_MSG_HDR + 0x18),    /* _H2ASN_MsgChoice LRRC_LMM_NETSCAN_REQ_STRU */
    ID_LMM_LRRC_NETSCAN_STOP_REQ          = (LMM_LRRC_MSG_HDR + 0x19),    /* _H2ASN_MsgChoice LRRC_LMM_NETSCAN_STOP_REQ_STRU */
    ID_LRRC_LMM_CELL_SIGN_REPORT_NOTIFY   = (LMM_LRRC_MSG_HDR + 0x1a),    /* _H2ASN_MsgChoice LRRC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU*/
    ID_LRRC_LMM_DETACH_IND                = (LMM_LRRC_MSG_HDR + 0x20),     /* _H2ASN_MsgChoice LRRC_LMM_DETACH_IND_STRU */

    ID_LRRC_LMM_DISABLE_LTE_NOTIFY        = (LMM_LRRC_MSG_HDR + 0x21),     /* _H2ASN_MsgChoice LRRC_LMM_DISABLE_LTE_NOTIFY_STRU*/

    /*LMM发送给RRC的指示，用于体验优化等特殊目的*/
    ID_LRRC_LMM_EXPERIENCE_SPEC_REQ       = (LMM_LRRC_MSG_HDR + 0x22),     /* _H2ASN_MsgChoice LRRC_LMM_EXPERIENCE_SPEC_REQ */
    /* 新增消息,用于通知LRRC CSFB流程启动以及停止,解决CSFB流程收不到网侧REL优化 */
    ID_LRRC_LMM_CSFB_NOTIFY               = (LMM_LRRC_MSG_HDR + 0x23),     /* _H2ASN_MsgChoice LRRC_LMM_CSFB_NOTIFY_STRU */

    ID_LRRC_LMM_BG_SEARCH_HRPD_REQ        = (LMM_LRRC_MSG_HDR + 0x24),     /* _H2ASN_MsgChoice LRRC_LMM_BG_SEARCH_HRPD_REQ_STRU*/
    ID_LRRC_LMM_BG_SEARCH_HRPD_STOP_REQ   = (LMM_LRRC_MSG_HDR + 0x25),     /* _H2ASN_MsgChoice LRRC_LMM_BG_SEARCH_HRPD_STOP_REQ_STRU*/

    ID_LRRC_LMM_CSG_WHITE_LIST_NOTIFY     = (LMM_LRRC_MSG_HDR + 0X26),     /* _H2ASN_MsgChoice LRRC_LMM_CSG_WHITE_LIST_NOTIFY_STRU */
    ID_LRRC_LMM_CSG_LIST_SEARCH_REQ       = (LMM_LRRC_MSG_HDR + 0X27),     /* _H2ASN_MsgChoice LRRC_LMM_CSG_LIST_SEARCH_REQ_STRU */
    ID_LRRC_LMM_CSG_BG_SEARCH_REQ         = (LMM_LRRC_MSG_HDR + 0X28),     /* _H2ASN_MsgChoice LRRC_LMM_CSG_BG_SEARCH_REQ_STRU */

    /* RABM发给RRC的原语 */
    ID_LRRC_LRABM_QOS_UPDATE_REQ          = (LRABM_LRRC_MSG_HDR + 0x0a),   /* _H2ASN_MsgChoice LRRC_LRABM_QOS_UPDATE_REQ_STRU */
    ID_LRRC_LRABM_RAB_RSP                 = (LRABM_LRRC_MSG_HDR + 0x0b),   /* _H2ASN_MsgChoice LRRC_LRABM_RAB_RSP_STRU */
    ID_LRRC_LRABM_STATUS_RSP              = (LRABM_LRRC_MSG_HDR + 0x0c),   /* _H2ASN_MsgChoice LRRC_LRABM_STATUS_RSP_STRU */

    /* RRC发给MM的原语 */
    ID_LRRC_LMM_START_CNF                 = (LRRC_LMM_MSG_HDR + 0x00),     /* _H2ASN_MsgChoice LRRC_LMM_START_CNF_STRU */
    ID_LRRC_LMM_PLMN_SEARCH_CNF           = (LRRC_LMM_MSG_HDR + 0x01),     /* _H2ASN_MsgChoice LRRC_LMM_PLMN_SEARCH_CNF_STRU */
    ID_LRRC_LMM_PLMN_SEARCH_STOP_CNF      = (LRRC_LMM_MSG_HDR + 0x02),     /* _H2ASN_MsgChoice LRRC_LMM_PLMN_SEARCH_STOP_CNF_STRU */
    ID_LRRC_LMM_EST_CNF                   = (LRRC_LMM_MSG_HDR + 0x03),     /* _H2ASN_MsgChoice LRRC_LMM_EST_CNF_STRU */
    ID_LRRC_LMM_REL_CNF                   = (LRRC_LMM_MSG_HDR + 0x04),     /* _H2ASN_MsgChoice LRRC_LMM_REL_CNF_STRU */
    ID_LRRC_LMM_REL_IND                   = (LRRC_LMM_MSG_HDR + 0x05),     /* _H2ASN_MsgChoice LRRC_LMM_REL_IND_STRU */
    ID_LRRC_LMM_ERR_IND                   = (LRRC_LMM_MSG_HDR + 0x06),     /* _H2ASN_MsgChoice LRRC_LMM_ERR_IND_STRU */
    ID_LRRC_LMM_AREA_LOST_IND             = (LRRC_LMM_MSG_HDR + 0x07),     /* _H2ASN_MsgChoice LRRC_LMM_AREA_LOST_IND_STRU */
    ID_LRRC_LMM_SYS_INFO_IND              = (LRRC_LMM_MSG_HDR + 0x08),     /* _H2ASN_MsgChoice LRRC_LMM_SYS_INFO_IND_STRU */
    ID_LRRC_LMM_PAGING_IND                = (LRRC_LMM_MSG_HDR + 0x09),     /* _H2ASN_MsgChoice LRRC_LMM_PAGING_IND_STRU */
    ID_LRRC_LMM_DATA_IND                  = (LRRC_LMM_MSG_HDR + 0x0a),     /* _H2ASN_MsgChoice LRRC_LMM_DATA_IND_STRU */
    ID_LRRC_LMM_SECURITY_IND              = (LRRC_LMM_MSG_HDR + 0x0b),     /* _H2ASN_MsgChoice LRRC_LMM_SECURITY_IND_STRU */
    ID_LRRC_LMM_POWER_OFF_CNF             = (LRRC_LMM_MSG_HDR + 0x0c),     /* _H2ASN_MsgChoice LRRC_LMM_POWER_OFF_CNF_STRU */
    ID_LRRC_LMM_ACCESS_GRANT_IND          = (LRRC_LMM_MSG_HDR + 0x0d),     /* _H2ASN_MsgChoice LRRC_LMM_ACCESS_GRANT_IND_STRU */
    ID_LRRC_LMM_DATA_CNF                  = (LRRC_LMM_MSG_HDR + 0x0e),     /* _H2ASN_MsgChoice LRRC_LMM_DATA_CNF_STRU */
    ID_LRRC_LMM_SUSPEND_IND               = (LRRC_LMM_MSG_HDR + 0x0f),     /* _H2ASN_MsgChoice LRRC_LMM_SUSPEND_IND_STRU */
    ID_LRRC_LMM_RESUME_IND                = (LRRC_LMM_MSG_HDR + 0x10),     /* _H2ASN_MsgChoice LRRC_LMM_RESUME_IND_STRU */
    ID_LRRC_LMM_SUSPEND_CNF               = (LRRC_LMM_MSG_HDR + 0x11),     /* _H2ASN_MsgChoice LRRC_LMM_SUSPEND_CNF_STRU */
    ID_LRRC_LMM_SECU_PARA_IND             = (LRRC_LMM_MSG_HDR + 0x12),     /* _H2ASN_MsgChoice LRRC_LMM_SECU_PARA_IND_STRU */
    ID_LRRC_LMM_SYS_CFG_CNF               = (LRRC_LMM_MSG_HDR + 0x13),     /* _H2ASN_MsgChoice LRRC_LNAS_SYS_CFG_CNF_STRU */
    ID_LRRC_LMM_MBMS_SESSION_CFG_CNF      = (LRRC_LMM_MSG_HDR + 0x14),     /* _H2ASN_MsgChoice LRRC_LMM_MBMS_SESSION_CFG_CNF_STRU */
    ID_LRRC_LMM_MBMS_SESSION_IND          = (LRRC_LMM_MSG_HDR + 0x15),     /* _H2ASN_MsgChoice LRRC_LMM_MBMS_SESSION_IND_STRU */
    ID_LRRC_LMM_BG_PLMN_SEARCH_CNF        = (LRRC_LMM_MSG_HDR + 0x16),     /* _H2ASN_MsgChoice LRRC_LMM_BG_PLMN_SEARCH_CNF_STRU */
    ID_LRRC_LMM_BG_PLMN_SEARCH_STOP_CNF   = (LRRC_LMM_MSG_HDR + 0x17),     /* _H2ASN_MsgChoice LRRC_LMM_BG_PLMN_SEARCH_STOP_CNF_STRU */
    ID_LRRC_LMM_NOT_CAMP_ON_IND           = (LRRC_LMM_MSG_HDR + 0x18),     /* _H2ASN_MsgChoice LRRC_LNAS_NOT_CAMP_ON_IND_STRU */
    ID_LRRC_LMM_UTRAN_MODE_REQ            = (LRRC_LMM_MSG_HDR + 0x19),     /* _H2ASN_MsgChoice LRRC_LMM_UTRAN_MODE_REQ_STRU */
    ID_LRRC_LMM_SUSPEND_REL_CNF           = (LRRC_LMM_MSG_HDR + 0x1b),     /* _H2ASN_MsgChoice LRRC_LMM_SUSPEND_REL_CNF_STRU */
    ID_LRRC_LMM_UTRAN_MODE_CNF            = (LRRC_LMM_MSG_HDR + 0x20),     /* _H2ASN_MsgChoice LRRC_LMM_UTRAN_MODE_CNF_STRU */
    ID_LRRC_LMM_SUSPEND_INFO_CHANGE_IND   = (LRRC_LMM_MSG_HDR + 0x21),     /* _H2ASN_MsgChoice LRRC_LMM_SUSPEND_INFO_CHANGE_IND_STRU */
    ID_LRRC_LMM_NETSCAN_CNF               = (LRRC_LMM_MSG_HDR + 0x22),     /* _H2ASN_MsgChoice LRRC_LMM_NETSCAN_CNF_STRU */
    ID_LRRC_LMM_NETSCAN_STOP_CNF          = (LRRC_LMM_MSG_HDR + 0x23),     /* _H2ASN_MsgChoice LRRC_LMM_NETSCAN_STOP_CNF_STRU */
    ID_LRRC_LMM_CELL_SIGN_REPORT_IND      = (LRRC_LMM_MSG_HDR + 0x24),     /* _H2ASN_MsgChoice LRRC_LMM_CELL_SIGN_REPORT_IND_STRU */
    ID_LRRC_LMM_SEARCHED_PLMN_INFO_IND    = (LRRC_LMM_MSG_HDR + 0x25),     /* _H2ASN_MsgChoice LRRC_LMM_SEARCHED_PLMN_INFO_IND_STRU */
    ID_LRRC_LMM_INTER_OPT_IND             = (LRRC_LMM_MSG_HDR + 0x26),     /* _H2ASN_MsgChoice LRRC_LMM_INTER_OPT_IND */

    /* RRC发给RABM的原语 */
    ID_LRRC_LRABM_RAB_IND                 = (LRRC_LRABM_MSG_HDR + 0x0d),   /* _H2ASN_MsgChoice LRRC_LRABM_RAB_IND_STRU */
    ID_LRRC_LRABM_STATUS_IND              = (LRRC_LRABM_MSG_HDR + 0x0e),   /* _H2ASN_MsgChoice LRRC_LRABM_STATUS_IND_STRU */
    ID_LRRC_LMM_BG_SEARCH_HRPD_CNF        = (LRRC_LMM_MSG_HDR + 0x27),   /* _H2ASN_MsgChoice LRRC_LMM_BG_SEARCH_HRPD_CNF_STRU */
    ID_LRRC_LMM_BG_SEARCH_HRPD_STOP_CNF   = (LRRC_LMM_MSG_HDR + 0x28),   /* _H2ASN_MsgChoice LRRC_LMM_BG_SEARCH_HRPD_STOP_CNF_STRU */
    ID_LRRC_LMM_CSG_LIST_SEARCH_CNF        = (LRRC_LMM_MSG_HDR+0x29),      /* _H2ASN_MsgChoice LRRC_LMM_CSG_LIST_SEARCH_CNF_STRU */
    ID_LRRC_LMM_CSG_BG_SEARCH_CNF          = (LRRC_LMM_MSG_HDR+0x2A),      /* _H2ASN_MsgChoice LRRC_LMM_CSG_BG_SEARCH_CNF_STRU */
    ID_LRRC_LMM_CSG_ID_HOME_NODEB_NAME_IND = (LRRC_LMM_MSG_HDR+0x2B),      /* _H2ASN_MsgChoice LRRC_LMM_CSG_ID_HOME_NODEB_NAME_IND_STRU */
    ID_LRRC_LMM_UE_CAP_CHANGE_IND         = (LRRC_LMM_MSG_HDR + 0x2C),     /* _H2ASN_MsgChoice LRRC_LMM_UE_CAP_CHANGE_IND_STRU */
    ID_LRRC_LNAS_MSG_ID_BUTT
};
typedef VOS_UINT32   LRRC_LNAS_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LNAS_ATTACH_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : NAS_INFO_STRU enAttach取值
*****************************************************************************/
enum LRRC_LNAS_ATTACH_STATUS_ENUM
{
    LRRC_LNAS_ATTACH                      = 0,
    LRRC_LNAS_NOT_ATTACH                  = 1,
    LRRC_LNAS_ATTACH_STATUS_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_ATTACH_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LNAS_SIM_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 卡状态取值
*****************************************************************************/
enum LRRC_LNAS_SIM_STATUS_ENUM
{
    LRRC_LNAS_USIM_ABSENT                 = 0,                /* 卡不存在 */
    LRRC_LNAS_USIM_PRESENT                = 1,                /* 卡存在,卡类型为 USIM 卡 */
    LRRC_LNAS_USIM_PRESENT_INVALID        = 2,                /* 卡存在,但卡无效,卡类型为 USIM 卡 */
    LRRC_LNAS_USIM_STATUS_BUTT
};
typedef VOS_UINT32  LRRC_LNAS_SIM_STATUS_ENUM_UINT32;


/*****************************************************************************
 枚举名    : LRRC_LNAS_START_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : NAS与RRC之间原语执行结果取值
*****************************************************************************/
enum LRRC_LNAS_START_RESULT_ENUM
{
    LRRC_LNAS_START_SUCCESS               = 0,
    LRRC_LNAS_START_FAILURE               = 1,
    LRRC_LNAS_START_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_START_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LNAS_PLMN_SEARCH_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : PLMN搜索类型取值
*****************************************************************************/
enum LRRC_LNAS_PLMN_SEARCH_TYPE_ENUM
{
    LRRC_LNAS_PLMN_SEARCH_SPEC            = 0,                /* 指定的PLMN的搜索 */
    /* lishangfeng bg begin */
    LRRC_LNAS_PLMN_SEARCH_FAST_SPEC       = 1,                /* 快速指定的PLMN的搜索 */
    LRRC_LNAS_PLMN_SEARCH_LIST            = 2,                /* PLMN列表的搜索   */
    LRRC_LNAS_PLMN_SEARCH_ANY             = 3,                /* any cell 搜索 */
    /* lishangfeng bg end*/
    /* ncell spec search begin */
    LRRC_LNAS_PLMN_SEARCH_NCELL_SPEC      = 4,
    /* ncell spec search end */
    /*modified by wangchen 00209181  for 搜网优化,2015-04-28,begin*/
    LRRC_LNAS_PLMN_SRCH_HISTORY             = 5,                /* 历史信息搜索 */
    LRRC_LNAS_PLMN_GET_GEO                  = 6,                /* 获取地理位置信息 */
    /*modified by wangchen 00209181  for 搜网优化,2015-04-28,end*/
    LRRC_LNAS_PLMN_SEARCH_PREF_BAND         = 7,                /* 预置BAND搜 */
    LRRC_LNAS_PLMN_SRCH_USER_CSG_SPEC     = 8,               /* 用户手动CSG搜索 */
    LRRC_LNAS_PLMN_SRCH_FAST_CSG_SPEC     = 9,               /* 快速CSG指定的PLMN的搜索 */
    LRRC_LNAS_PLMN_SEARCH_TYPE_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_PLMN_SEARCH_TYPE_ENUM_UINT32;
/*****************************************************************************
 枚举名    : LRRC_LNAS_FFT_SCAN_TYPE_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  : PLMN搜索结果取值
*****************************************************************************/
enum LRRC_LNAS_FFT_SCAN_TYPE_ENUM
{
    LRRC_LNAS_FFT_SCAN_TYPE_NONE     = 0,                 /* 不从COMM SRCH获取FFT扫频之后的频点 */
    LRRC_LNAS_FFT_SCAN_TYPE_LOW      = 1,                 /* 从COMM SRCH获取FFT扫频之后满足可驻留门限的频点 */
    LRRC_LNAS_FFT_SCAN_TYPE_HIGH     = 2,                 /* 从COMM SRCH获取FFT扫频之后满足高质量门限的频点 */
    LRRC_LNAS_FFT_SCAN_TYPE_BUTT
};
typedef VOS_UINT8  LRRC_LNAS_FFT_SCAN_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : LRRC_LNAS_PLMN_SEARCH_SCENE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LNAS指定的PLMN搜网场景
*****************************************************************************/
enum LRRC_LNAS_PLMN_SEARCH_SCENE_ENUM
{
    LRRC_LNAS_PLMN_SEARCH_SCENE_NORMAL              = 0,                 /* 普通的正常搜网，无特殊要求 */
    LRRC_LNAS_PLMN_SEARCH_SCENE_VIA_CL_BG_SEARCH    = 1,                 /* VIA拼片CL版本上指示CDMA发起LTE的指定PLMN背景搜，用于LRRC按照定制门限上报搜网结果 */

    LRRC_LNAS_PLMN_SEARCH_SCENE_BUTT
};
typedef VOS_UINT8  LRRC_LNAS_PLMN_SEARCH_SCENE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : LRRC_LNAS_PLMN_SEARCH_RLT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : PLMN搜索结果取值
*****************************************************************************/
enum LRRC_LNAS_PLMN_SEARCH_RLT_ENUM
{
    LRRC_LNAS_PLMN_SEARCH_RLT_SPEC_SUCC   = 0,                /* 指定的PLMN ID 搜索成功 */
    LRRC_LNAS_PLMN_SEARCH_RLT_LIST_SUCC   = 1,                /* PLMN List搜索成功      */
    LRRC_LNAS_PLMN_SEARCH_RLT_SPEC_FAIL   = 2,                /* 指定PLMN ID搜索失败    */
    LRRC_LNAS_PLMN_SEARCH_RLT_LIST_FAIL   = 3,                /* PLMN List搜索失败      */
/* lishangfeng bg begin */
    LRRC_LNAS_PLMN_SRCH_RLT_LIST_REJ      = 4,                /* 驻留态下列表搜网被非出服务区流程打断 */
/* lishangfeng bg end */

    LRRC_LNAS_PLMN_SEARCH_RLT_SPEC_NO_RF   = 5,/* 新增 */
    LRRC_LNAS_PLMN_SEARCH_RLT_LIST_NO_RF   = 6,/* 新增 */

    /*modified by wangchen 00209181  for 搜网优化,2015-04-28,begin*/
    LRRC_LNAS_PLMN_SRCH_RLT_HISTORY_FAIL    = 7,
    LRRC_LNAS_PLMN_SRCH_RLT_HISTORY_SUCC    = 8,
    LRRC_LNAS_PLMN_SRCH_RLT_HISTORY_NO_RF   = 9,
    LRRC_LNAS_PLMN_SRCH_RLT_GET_GEO_FAIL    = 10,
    LRRC_LNAS_PLMN_SRCH_RLT_GET_GEO_SUCC    = 11,
    LRRC_LNAS_PLMN_SRCH_RLT_GET_GEO_NO_RF   = 12,
    /*modified by wangchen 00209181  for 搜网优化,2015-04-28,end*/

    LRRC_LNAS_PLMN_SRCH_RLT_PREF_BAND_FAIL  = 13,
    LRRC_LNAS_PLMN_SRCH_RLT_PREF_BAND_SUCC  = 14,
    LRRC_LNAS_PLMN_SRCH_RLT_PREF_BAND_NO_RF = 15,

    LRRC_LNAS_PLMN_SRCH_RLT_SPEC_CSG_SUCC   = 16,
    LRRC_LNAS_PLMN_SRCH_RLT_SPEC_CSG_FAIL   = 17,
    LRRC_LNAS_PLMN_SRCH_RLT_SPEC_CSG_NO_RF  = 18,

    LRRC_LNAS_PLMN_SEARCH_RLT_BUTT
};
typedef VOS_UINT32  LRRC_LNAS_PLMN_SEARCH_RLT_ENUM_UINT32;
/*****************************************************************************
 枚举名    : LRRC_LNAS_BG_SRCH_RLT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : BG搜索结果
*****************************************************************************/
enum LRRC_LNAS_BG_SRCH_RLT_ENUM
{
    LRRC_LNAS_BG_SRCH_RLT_SUCCESS            = 0,                /* 指定的PLMN搜索成功 */
    LRRC_LNAS_BG_SRCH_RLT_FAIL               = 1,                /* 实际发起了搜网，但是搜索失败 */
    LRRC_LNAS_BG_SRCH_RLT_ABORT              = 2,                /* 没有发起搜网，因为当前状态不允许，搜索被终止 */
    LRRC_LNAS_BG_SRCH_RLT_BUTT
};
typedef VOS_UINT32  LRRC_LNAS_BG_SRCH_RLT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LNAS_RAT_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 接入技术的取值
*****************************************************************************/
enum LRRC_LNAS_MSG_WAIT_TYPE_ENUM
{
    LRRC_LNAS_MSG_WAIT_ERR                = 0,                /*函数调用出错*/
    LRRC_LNAS_MSG_NO_WAIT,                                    /*RRC不需要等待NAS的响应消息*/
    LRRC_LNAS_MSG_WAIT,                                       /*RRC需要等待NAS的响应消息  */
    LRRC_LNAS_MSG_BUTT
};
typedef VOS_UINT32  LRRC_LNAS_MSG_WAIT_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LNAS_INFO_TYPE_ENUM_UINT32
 协议表格  :
 ASN.1描述 :
 枚举说明  : NAS信息枚举类型
*****************************************************************************/
enum LRRC_LNAS_INFO_TYPE_ENUM
{
    LRRC_LNAS_INFO_TYPE_UEID              = 0,                /*其他模块获取UEID,目前只有IMSI*/
    LRRC_LNAS_INFO_TYPE_DRX,
    LRRC_LNAS_INFO_TYPE_AC,
    LRRC_LNAS_INFO_TYPE_PLMNID,
    LRRC_LNAS_INFO_TYPE_HO_PRIO_SELECT_PLMNID,
    LRRC_LNAS_INFO_TYPE_RPLMN,
    LRRC_LNAS_INFO_TYPE_GU_PLMN,

    LRRC_LNAS_INFO_TYPE_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_INFO_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LNAS_RESEL_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 小区控制原语枚举类型
*****************************************************************************/
enum LRRC_LNAS_RESEL_TYPE_ENUM
{
    LRRC_LNAS_CELL_SELECTION              = 0,
    LRRC_LNAS_RESEL_SUITABLE              = 1,
    LRRC_LNAS_FORBLA_CHANGE               = 2,
    LRRC_LNAS_RESEL_ACCEPTABLE            = 3,
    LRRC_LNAS_FORBTA_CHANGE               = 4,
    LRRC_LNAS_RESEL_BUTT
};
typedef VOS_UINT32  LRRC_LNAS_RESEL_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LNAS_EST_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 信令连接结果枚举类型
*****************************************************************************/
enum LRRC_LNAS_EST_RESULT_ENUM
{
    LRRC_EST_SUCCESS                         = 0,                                /* 信令连接建立成功                     */
    LRRC_EST_PRESENT                         = 1,                                /* 该信令连接已经存在                   */
    LRRC_EST_ESTING                          = 2,                                /* 该信令连接正在建立                   */
    LRRC_EST_DELING                          = 3,                                /* 该信令连接正在释放                   */
    LRRC_EST_ACCESS_BARRED_MO_CALL           = 4,                                /* access barred when MO Call  */
    LRRC_EST_ACCESS_BARRED_MO_SIGNAL         = 5,                                /* access barred When MO SIGNAL  */
    LRRC_EST_ACCESS_BARRED_EMERGENCY_CALL    = 6,                                /* access barred When Emergency Call  */
    LRRC_EST_ACCESS_BARRED_ALL               = 7,                                /* access barred When Rrc Con Rej */
    LRRC_EST_EST_CONN_FAIL                   = 8,                                /* RR connection establish failure      */
    LRRC_EST_RJ_INTER_RAT                    = 9,                                /* RR connection Reject: 指示进入异系统 */
    LRRC_EST_IMMEDIATE_ASSIGN_REJECT         = 10,                               /* 正常的接入过程，发送RA脉冲后，收到立即指派拒绝消息，
                                                                                没有收到立即指派消息而导致的接入失败 */
    LRRC_EST_RANDOM_ACCESS_REJECT            = 11,                               /* 正常的接入过程，发送RA脉冲后，没有收到网络侧的立即指派，
                                                                                也没有收到立即指派拒绝，接入失败 */
    LRRC_EST_CELL_SEARCHING                  = 12,                               /* RRC目前不能处理建链请求，NAS收到该原因值，
                                                                                   直到收到RRC_MM_SYS_INFO_IND再发起建链*/

    /* v7r2 lld begin */
    LRRC_EST_ACCESS_BARRED_MT_CALL           = 13,                              /* access barred when MT Call  */
    LRRC_EST_ACCESS_BARRED_MO_CSFB           = 14,                              /* access barred when MO CSFB  */
    LRRC_EST_ACCESS_BARRED_MO_CALL_AND_CSFB  = 15,                              /* access barred when MO Call AND MO CSFB  */
    /* v7r2 lld end */

    LRRC_EST_NO_RF                           = 16, /* DSDS NORF */

    LRRC_EST_RESULT_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_EST_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LNAS_EST_CAUSE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : RRMM_EST_REQ_STRU消息中的enEstCause
              emergency, highPriorityAccess, mt-Access, mo-Signalling, mo-Data,delayTolerantAccess-v1020 ,
*****************************************************************************/
enum LRRC_LNAS_EST_CAUSE_ENUM
{
    LRRC_LNAS_EST_CAUSE_EMERGENCY_CALL          = 0,
    LRRC_LNAS_EST_CAUSE_HIGH_PRIORITY_ACCESS,
    LRRC_LNAS_EST_CAUSE_MT_ACCESS,
    LRRC_LNAS_EST_CAUSE_MO_SIGNALLING,
    LRRC_LNAS_EST_CAUSE_MO_DATA,
    /* v7r2 lld begin */
    LRRC_LNAS_EST_CAUSE_DELAYTOLERANT_ACCESS,
    /* v7r2 lld end */
    LRRC_LNAS_EST_CAUSE_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_EST_CAUSE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LNAS_REL_CAUSE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : NAS删除RRC的原因值枚举类型
*****************************************************************************/
enum LRRC_LNAS_REL_CAUSE_ENUM
{
    /* RRC Connection Release消息中的原因 */
    LRRC_LNAS_REL_CAUSE_CONN_FAIL                  = 0,  /* RR Connection Failure                             */
    LRRC_LNAS_REL_CAUSE_LOAD_BALANCE_REQ           = 1,  /* Rrc Con Release 带有的原因为
                                                          loadBalancingTAUrequired                          */
    LRRC_LNAS_REL_CAUSE_OTHER_REASON               = 2,  /* Rrc Con Release 带有的原因不是
                                                          loadBalancingTAUrequired，或无线链路失败释放原因  */
    LRRC_LNAS_REL_CAUSE_NAS_DATA_ABSENT            = 3,  /* NAS Data Request: Connection Absent               */
/*    RRC_NAS_REL_CAUSE_MSG_TRANS_FAIL             = 4,*/  /* Rrc 发送Nas消息失败*/
    LRRC_LNAS_REL_CAUSE_RRC_ABNORMAL               = 4,  /* RRC或底层系统异常释放原因                         */

    LRRC_LNAS_REL_CAUSE_GU2L_HO_ERR,                    /* GU向L切换失败 */

    LRRC_LNAS_REL_CAUSE_L2GU_REDIRECT,                  /* 异系统重定向 */

    /* v7r2 code begin */
    LRRC_LNAS_REL_CAUSE_CSFB_HIGH_PRIOR,                /* Rrc Con Release 带有的原因 cs-FallbackHighPriority */
    /* v7r2 code end */

    LRRC_LNAS_REL_CAUSE_NO_RF,  /* 新增原因 */

    LRRC_LNAS_REL_CAUSE_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_REL_CAUSE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LNAS_ERR_CAUSE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : RRC与NAS错误类型枚举类型
*****************************************************************************/
enum LRRC_LNAS_ERR_CAUSE_ENUM
{
    LRRC_LNAS_ERR_NORMAL                      = 0,
    LRRC_LNAS_ERR_CAUSE_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_ERR_CAUSE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LNAS_AREA_LOST_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : RRMM_AREA_LOST_IND_STRU消息中的enRptMode
*****************************************************************************/
enum LRRC_LNAS_AREA_LOST_ENUM
{
    LRRC_LNAS_SERVICE_AREA_LOST           = 0,                /* 服务区丢失,LTE暂时不用 */
    LRRC_LNAS_COVERAGE_AREA_LOST          = 1,                /* 覆盖区丢失 */
    LRRC_LNAS_RADIO_RESOURCE_AREA_LOST    = 2,   /*射频资源不可用*/
    LRRC_LNAS_AREA_LOST_BUTT
};
typedef VOS_UINT32  LRRC_LNAS_AREA_LOST_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LNAS_PAGING_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : RRMM_PAGING_IND_STRU enPagingType取值
*****************************************************************************/
enum LRRC_LNAS_PAGING_TYPE_ENUM
{
    LRRC_LNAS_PAGING_TYPE1                = 0,                /* Paging Type 1 */
    LRRC_LNAS_PAGING_TYPE2                = 1,                /* Paging Type 2 */
    LRRC_LNAS_PAGING_TYPE_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_PAGING_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LNAS_PAGING_CAUSE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LRRC_LNAS_PAGING_CAUSE_ENUM enPagingCause取值
*****************************************************************************/
enum LRRC_LNAS_PAGING_CAUSE_ENUM
{
    LRRC_LNAS_PAGING_CAUSE_TERMINAT_CONVERSAT_CALL          = 0,
    LRRC_LNAS_PAGING_CAUSE_TERMINAT_STREAM_CALL             = 1,
    LRRC_LNAS_PAGING_CAUSE_TERMINAT_INTERACT_CALL           = 2,
    LRRC_LNAS_PAGING_CAUSE_TERMINAT_BACKGROUND_CALL         = 3,
    LRRC_LNAS_PAGING_CAUSE_TERMINAT_HIGH_PRIORITY_SIGNAL    = 4,
    LRRC_LNAS_PAGING_CAUSE_TERMINAT_LOW_PRIORITY_SIGNAL     = 5,
    LRRC_LNAS_PAGING_CAUSE_TERMINAT_CAUSE_UNKNOWN           = 6,

    LRRC_LNAS_PAGING_CAUSE_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_PAGING_CAUSE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LNAS_PAGING_UE_ID_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LRRC_LNAS_PAGING_UE_ID_ENUM enPagingUeId取值
*****************************************************************************/
enum LRRC_LNAS_PAGING_UE_ID_ENUM
{
    LRRC_LNAS_IMSI_GSM_MAP                = 0,                /* used for Paging Type 1/2 */
    LRRC_LNAS_TMSI_GSM_MAP_P_TMSI         = 1,                /* used for Paging Type 1   */
    LRRC_LNAS_IMSI_DS41                   = 2,                /* used for Paging Type 1/2 */
    LRRC_LNAS_TMSI_DS41                   = 3,                /* used for Paging Type 1/2 */
    LRRC_LNAS_P_TMSI_GSM_MAP              = 4,                /* used for Paging Type 1   */
    LRRC_LNAS_IMSI_LTE,
    LRRC_LNAS_S_TMSI_LTE,

    LRRC_PAGE_UE_ID_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_PAGING_UE_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LNAS_SECURITY_RPT_MODE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LRRC_LNAS_SECURITY_RPT_MODE_ENUM enRptMode取值
*****************************************************************************/
enum LRRC_LNAS_SECURITY_RPT_MODE_ENUM
{
    LRRC_LNAS_SECURITY_CS_SMC_CMPL        = 0,                /* 一个CS SMC流程结束                       */
    LRRC_LNAS_SECURITY_DEL_CS_KEY         = 1,                /* USIM中CS域CK、IK被删除                   */
    LRRC_LNAS_SECURITY_DEL_PS_KEY         = 2,                /* USIM中PS域CK、IK被删除                   */
    LRRC_LNAS_SECURITY_DEL_CS_PS_KEY      = 3,                /* USIM中CS+PS域CK、IK被删除                */
    LRRC_LNAS_SECURITY_CS_SMC_RCV         = 4,                /* 收到有效的CS SMC消息                     */
    LRRC_LNAS_SECURITY_PS_SMC_RCV         = 5,                /* 收到有效的PS SMC消息                     */
    LRRC_LNAS_SECURITY_PS_SMC_CMPL        = 6,                /* 一个PS SMC流程结束                       */
    LRRC_LNAS_SECURITY_RB_CTRL_MSG        = 7,                /* 收到重配消息修改加密算法                 */
    LRRC_LNAS_SECURITY_MOBI_MSG           = 8,                /* 收到CELL/URA UPDATE CNF消息修改加密算法  */
    LRRC_LNAS_SECURITY_RPT_MODE_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_SECURITY_RPT_MODE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LNAS_RAB_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LRRC_LNAS_RAB_STATUS_ENUM enStatus取值
*****************************************************************************/
enum LRRC_LNAS_RAB_STATUS_ENUM
{
    LRRC_LNAS_RAB_STATUS_STOP             = 0,                /* 停止数据传送 */
    LRRC_LNAS_RAB_STATUS_CONTINUE         = 1,                /* 恢复数据传送 */
    LRRC_LNAS_RAB_STATUS_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_RAB_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LNAS_RAB_CHANGE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : RAB的配置类型
*****************************************************************************/
enum LRRC_LNAS_RAB_CHANGE_ENUM
{
    LRRC_LNAS_RAB_SETUP_REQUEST           = 0,                /* 请求建立新的RAB   */
    LRRC_LNAS_RAB_SETUP_SUCCESS           = 1,                /* 成功建立新的RAB   */
    LRRC_LNAS_RAB_SETUP_FAILURE           = 2,                /* 建立新的RAB失败   */
    LRRC_LNAS_RAB_RECONFIG                = 3,                /* 重配已经建立的RAB */
    LRRC_LNAS_RAB_RELEASE                 = 4,                /* 释放已经建立的RAB */
    LRRC_LNAS_RAB_CHANGE_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_RAB_CHANGE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LNAS_CELL_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 小区驻留状态,RRC通知MM当前驻留小区是AnyCell状态还是Normal状态
*****************************************************************************/
enum LRRC_LNAS_CELL_STATUS_ENUM
{
    LRRC_LNAS_CELL_STATUS_NORMAL          = 0,                                    /* 正常驻留    */
    LRRC_LNAS_CELL_STATUS_ANYCELL         = 1,                                    /* AnyCell驻留 */
    LRRC_LNAS_CELL_STATUS_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_CELL_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LNAS_ACCESS_GRANT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : RRC通知nas当前的access Bar alleviation
*****************************************************************************/
enum LRRC_LNAS_ACCESS_GRANT_ENUM
{
    LRRC_LNAS_ACCESS_GRANT_MT              = 0,                                   /* 可以进行MT */
    LRRC_LNAS_ACCESS_GRANT_MO_CALL         = 1,                                   /* 可以进行MO Call */
    LRRC_LNAS_ACCESS_GRANT_MO_SIGNAL       = 2,                                   /* 可以进行MO Signalling */
    LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MT  = 3,                                   /* 可以进行MO Call和 MT */
    LRRC_LNAS_ACCESS_GRANT_MO_SIGNAL_AND_MT= 4,                                   /* 可以进行MO Signalling 和 MT */
    LRRC_LNAS_ACCESS_GRANT_ALL             = 5,                                   /* 都可以进行 */
    /* v7r2 code begin */
    LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MO_SIGNAL,
    LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MO_SIGNAL_AND_MT,
    LRRC_LNAS_ACCESS_GRANT_MO_CSFB,
    LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MO_CSFB,
    LRRC_LNAS_ACCESS_GRANT_MO_SIGNAL_AND_MO_CSFB,
    LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MO_SIGNAL_AND_MO_CSFB,
    LRRC_LNAS_ACCESS_GRANT_MO_CSFB_AND_MT,
    LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MO_CSFB_AND_MT,
    LRRC_LNAS_ACCESS_GRANT_MO_SIGNAL_AND_MO_CSFB_AND_MT,/* = 14 */
    /* v7r2 code end */
    LRRC_LNAS_ACCESS_GRANT_BUTT
 };
typedef VOS_UINT32 LRRC_LNAS_ACCESS_GRANT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LMM_BARRED_IND_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : nas在发送释放请求时,指示当前使用的小区是否被bar
*****************************************************************************/
enum LRRC_LMM_BARRED_IND_ENUM
{
    LRRC_LMM_NOT_BARRED                   = 0,                                    /* 原小区没有被barred */
    LRRC_LMM_BARRED                       = 1,                                    /* 原小区被barred */
    LRRC_LNAS_BARRED_IND_BUTT
};
typedef VOS_UINT32 LRRC_LMM_BARRED_IND_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LNAS_STATUS_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : RAB的配置RSP信息的结果
*****************************************************************************/
enum LRRC_LNAS_STATUS_RESULT_ENUM
{
    LRRC_LNAS_STATUS_SUCC                 = 0,
    LRRC_LNAS_STATUS_FAIL                    ,
    LRRC_LNAS_STATUS_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_STATUS_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LNAS_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : RAB的配置RSP信息的结果
*****************************************************************************/
enum LRRC_LNAS_RESULT_ENUM
{
    LRRC_LNAS_SUCC                      = 0,
    LRRC_LNAS_FAIL                    ,
    LRRC_LNAS_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LNAS_SMC_CTRL_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : NAS安全功能启动状态
*****************************************************************************/
enum LRRC_LNAS_SMC_CTRL_ENUM
{
    LRRC_LNAS_SMC_OPEN                        = 0,
    LRRC_LNAS_SMC_CLOSE                          ,
    LRRC_LNAS_SMC_CTRL_BUTT
};
typedef VOS_UINT8 LRRC_LNAS_SMC_CTRL_ENUM_UINT8;

/*****************************************************************************
 枚举名    : LRRC_LMM_DATA_CNF_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : MM直传消息确认类型
*****************************************************************************/
enum LRRC_LMM_DATA_CNF_ENUM
{
    LRRC_LMM_DATA_CNF_NOT_NEED       = 0,
    LRRC_LMM_DATA_CNF_NEED              ,
    LRRC_LMM_DATA_CNF_BUTT
};
typedef VOS_UINT32 LRRC_LMM_DATA_CNF_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_MM_DATA_CNF_RSLT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : MM直传消息确认结果
*****************************************************************************/
enum LRRC_LMM_SEND_RSLT_ENUM
{
    LRRC_LMM_SEND_RSLT_SUCCESS    = 0,
    LRRC_LMM_SEND_RSLT_FAILURE_HO          ,
    LRRC_LMM_SEND_RSLT_FAILURE_CONN_REL,
    LRRC_LMM_SEND_RSLT_FAILURE_CTRL_NOT_CONN,
    LRRC_LMM_SEND_RSLT_FAILURE_TXN,
    LRRC_LMM_SEND_RSLT_FAILURE_RLF,
    LRRC_LMM_SEND_RSLT_NO_RF,
    LRRC_LMM_SEND_RSLT_BUTT
};
typedef VOS_UINT32 LRRC_LMM_SEND_RSLT_ENUM_UINT32;

/*****************************************************************************
 结构名称   : LRRC_LMM_SUS_SYS_CHNG_DIR_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : LRRC通知LMM挂起的方向
*****************************************************************************/
enum LRRC_LMM_SUS_SYS_CHNG_DIR_ENUM
{
    LRRC_LMM_SUS_SYS_CHNG_DIR_L2W   = 0,
    LRRC_LMM_SUS_SYS_CHNG_DIR_L2G,

    LRRC_LMM_SUS_SYS_CHNG_DIR_L2C,

    LRRC_LMM_SUS_SYS_CHNG_DIR_BUTT
};
typedef VOS_UINT32 LRRC_LMM_SUS_SYS_CHNG_DIR_ENUM_UINT32;

/*****************************************************************************
 结构名称   : LRRC_LMM_SYS_CHNG_TYPE_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : 系统变更的类型
*****************************************************************************/
enum LRRC_LMM_SYS_CHNG_TYPE_ENUM
{
    LRRC_LMM_SYS_CHNG_TYPE_RESEL    = 0,
    LRRC_LMM_SYS_CHNG_TYPE_HO,
    LRRC_LMM_SYS_CHNG_TYPE_CCO,
    LRRC_LMM_SYS_CHNG_TYPE_REDIR,

    LRRC_LMM_SYS_CHNG_TYPE_RESEL_REVERSE,
    LRRC_LMM_SYS_CHNG_TYPE_HO_REVERSE,
    LRRC_LMM_SYS_CHNG_TYPE_CCO_REVERSE,
    LRRC_LMM_SYS_CHNG_TYPE_REDIR_REVERSE,

    LRRC_LMM_SYS_CHNG_TYPE_BUTT
};
typedef VOS_UINT32 LRRC_LMM_SYS_CHNG_TYPE_ENUM_UINT32;

/*****************************************************************************
 结构名称   : LRRC_LMM_SUS_CAUSE_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : LRRC通知LMM挂起的原因
*****************************************************************************/
enum LRRC_LMM_SUS_CAUSE_ENUM
{
    LRRC_LMM_SUS_CAUSE_CSFB          = 0,

    /* 若非CSFB导致的挂起，则填此BUTT值 */
    LRRC_LMM_SUS_CAUSE_BUTT
};
typedef VOS_UINT32 LRRC_LMM_SUS_CAUSE_ENUM_UINT32;

/*****************************************************************************
 结构名称   : LRRC_LMM_RSM_SYS_CHNG_DIR_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : LRRC通知LMM恢复的方向
*****************************************************************************/
enum LRRC_LMM_RSM_SYS_CHNG_DIR_ENUM
{

    LRRC_LMM_RSM_SYS_CHNG_DIR_W2L    = 0,
    LRRC_LMM_RSM_SYS_CHNG_DIR_G2L,
    LRRC_LMM_RSM_SYS_CHNG_DIR_C2L,
    LRRC_LMM_RSM_SYS_CHNG_DIR_BUTT
};
typedef VOS_UINT32 LRRC_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32;

/*****************************************************************************
 结构名称   : LRRC_LMM_CSFB_RESULT_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : LRRC通知LMM CSFB失败结果
*****************************************************************************/
enum LRRC_LMM_CSFB_RESULT_ENUM
{
    LRRC_LMM_CSFB_RESULT_FAIL          = 0,

    /* 如果CSFB不存在，则填LRRC_LMM_CSFB_RESULT_BUTT */
    LRRC_LMM_CSFB_RESULT_BUTT
};
typedef VOS_UINT32 LRRC_LMM_CSFB_RESULT_ENUM_UINT32;

/*****************************************************************************
 结构名称   : LRRC_LNAS_SUSPEND_NOTIFY_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : LRRC通知LMM 此次是否需要LMM挂起LRRC，以及挂起的原因
*****************************************************************************/
enum LRRC_LNAS_SUSPEND_NOTIFY_ENUM
{
    LRRC_LNAS_NOT_SUSPEND   = 0,
    LRRC_LNAS_SUSPEND_LTE_RAT_NOT_ACTIVE,
    LRRC_LNAS_SUSPEND_LTE_BAND_NOT_SUPPORT,

    LRRC_LNAS_SUSPEND_NOTIFY_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_SUSPEND_NOTIFY_ENUM_UINT32;

/*****************************************************************************
枚举名    : LRRC_LNAS_RAT_PRIO_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 制式优先级类型
*****************************************************************************/
enum LRRC_LNAS_RAT_PRIO_ENUM
{
    LRRC_LNAS_RAT_PRIO_NULL                = 0,          /* 该接入技术不存在*/
    LRRC_LNAS_RAT_PRIO_LOW                 = 1,          /* 优先级较低   */
    LRRC_LNAS_RAT_PRIO_MIDDLE              = 2,          /* 优先级中间   */
    LRRC_LNAS_RAT_PRIO_HIGH                = 3,          /* 优先级较高   */
    LRRC_LNAS_RAT_PRIO_BUTT
};
typedef VOS_UINT8  LRRC_LNAS_RAT_PRIO_ENUM_UINT8;

/*****************************************************************************
枚举名    : LRRC_LNAS_RAT_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 制式类型
*****************************************************************************/
enum LRRC_LNAS_RAT_TYPE_ENUM
{
    LRRC_LNAS_RAT_TYPE_GSM = 0,                         /* GSM接入技术 */
    LRRC_LNAS_RAT_TYPE_WCDMA,                           /* WCDMA接入技术 */
    LRRC_LNAS_RAT_TYPE_LTE,                             /* LTE接入技术 */
    LRRC_LNAS_RAT_TYPE_CDMA1X,                          /* 1x*/
    LRRC_LNAS_RAT_TYPE_HRPD,                            /* HRPD*/
    LRRC_LNAS_RAT_TYPE_BUTT
};

/* 为了合入SYSCFG PHASE I 打桩 ,待GU SYSCFG特性合入后，以下代码删除----begin*/
typedef VOS_UINT8 LRRC_LNAS_RAT_TYPE_ENUM_UINT8;
/*****************************************************************************
 枚举名    : LRRC_LNAS_ATTACH_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : NAS_INFO_STRU enAttach取值
*****************************************************************************/
enum LRRC_LNAS_MBMS_SESSION_CFG_ENUM
{
    LRRC_LNAS_MBMS_CFG_STOP                = 0,
    LRRC_LNAS_MBMS_CFG_START               = 1,
    LRRC_LNAS_MBMS_CFG_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_MBMS_SESSION_CFG_ENUM_UINT32;



/*****************************************************************************
 枚举名    : LRRC_LMM_BG_SRCH_RLT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : BG搜索结果
*****************************************************************************/
enum LRRC_LMM_BG_SRCH_RLT_ENUM
{
    LRRC_LMM_BG_SRCH_RLT_SUCC               = 0,                /* 指定的PLMN搜索成功 */
    LRRC_LMM_BG_SRCH_RLT_FAIL               = 1,                /* 实际发起了搜网，但是搜索失败 */
    LRRC_LMM_BG_SRCH_RLT_ABORT              = 2,                /* 没有发起搜网，因为当前状态不允许，搜索被终止 */
    LRRC_LMM_BG_SRCH_RLT_BUTT
};
typedef VOS_UINT32  LRRC_LMM_BG_SRCH_RLT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LMM_RAT_LIST_SEARCH_RSLT_ENUM
 结构说明  : LRRC_LNAS_LIST_SEARCH_RAT_INFO_STRU消息中的LIST搜索完成情况
*****************************************************************************/
enum LRRC_LMM_RAT_LIST_SEARCH_RSLT_ENUM
{
    LRRC_LMM_RAT_LIST_SEARCH_NOT_START      = 0,                /* LIST搜索未启动        */
    LRRC_LMM_RAT_LIST_SEARCH_PARTIAL_CMPL   = 1,                /* LIST搜索已启动,部分完成 */
    LRRC_LMM_RAT_LIST_SEARCH_CMPL           = 2,                /* LIST搜索完成          */
    LRRC_LMM_RAT_LIST_SEARCH_BUTT
};
typedef VOS_UINT8  LRRC_LMM_RAT_LIST_SEARCH_RSLT_ENUM_UINT8;

enum LRRC_LNAS_UTRAN_MODE_ENUM
{
    LRRC_LNAS_UTRAN_MODE_WCDMA         = 0x00,     /* 当前工作模式为WCDMA */
    LRRC_LNAS_UTRAN_MODE_TDSCDMA       = 0x01,     /* 当前工作模式为TDSCDMA */
    LRRC_LNAS_UTRAN_MODE_NULL          = 0x02,     /* CL模式下的工作模式 */
    LRRC_LNAS_UTRAN_MODE_BUTT
};
typedef VOS_UINT8  LRRC_LNAS_UTRAN_MODE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : LRRC_LNAS_GUMMEI_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : GUMMEI type枚举
*****************************************************************************/
enum LRRC_LNAS_GUMMEI_TYPE_ENUM
{
    LRRC_LNAS_GUMMEI_TYPE_NATIVE             = 0,                /* NATIVE GUMMEI */
    LRRC_LNAS_GUMMEI_TYPE_MAPPED             = 1,                /* MAPPED GUMMEI */

    LRRC_LNAS_GUMMEI_TYPE_BUTT
};
typedef VOS_UINT8  LRRC_LNAS_GUMMEI_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : LRRC_LNAS_ACCESS_MODE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : SysInfoInd消息中的accessMode
*****************************************************************************/
enum LRRC_LNAS_ACCESS_MODE_ENUM
{
    LRRC_LNAS_ACCESS_MODE_TDD           = 0,                /* TDD模式*/
    LRRC_LNAS_ACCESS_MODE_FDD           = 1,                /* FDD模式 */
    LRRC_LNAS_ACCESS_MODE_BUTT
};
typedef VOS_UINT8  LRRC_LNAS_ACCESS_MODE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : RRC_NAS_CAPABILITY_CHANGE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : NAS与RRC之间原语执行结果取值
*****************************************************************************/
enum LRRC_LNAS_CAPABILITY_CHANGE_ENUM
{
    LRRC_LNAS_UE_CAPABILITY_NOT_CHANGE         = 0,         /* UE能力不发生改变*/
    LRRC_LNAS_UE_CAPABILITY_CHANGE             = 1,         /* UE能力发生改变 */
    LRRC_LNAS_UE_CAPABILITY_BUTT
};
typedef VOS_UINT32  LRRC_LNAS_CAPABILITY_CHANGE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LNAS_RAT_CHANGE_CAUSE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum LRRC_LNAS_SUSPEND_INFO_CHANGE_TYPE_ENUM
{
    LRRC_LNAS_SUSPEND_RAT_INFO_CHANGE   = 0,     /* CSFB的重定向过程中RAT发生改变*/
    LRRC_LNAS_SUSPEND_INFO_CHANGE_BUTT
};
typedef VOS_UINT32  LRRC_LNAS_SUSPEND_INFO_CHANGE_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_LNAS_RAT_CHANGE_CAUSE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum LRRC_LNAS_RAT_CHANGE_TYPE_ENUM
{
    LRRC_LNAS_RAT_CHANGE_G2W   = 0,
    LRRC_LNAS_RAT_CHANGE_W2G   = 1,
    LRRC_LNAS_RAT_CHANGE_TYPE_BUTT
};
typedef VOS_UINT32  LRRC_LNAS_RAT_CHANGE_TYPE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : LRRC_LNAS_CALL_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : CALL type枚举
*****************************************************************************/
enum LRRC_LNAS_CALL_TYPE_ENUM
{
    LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING       = 0,            /* MO signalling */
    LRRC_LNAS_CALL_TYPE_ORIGINATING_CALL             = 1,            /* MO call */
    LRRC_LNAS_CALL_TYPE_TERMINATING_CALL             = 2,            /* MT call */
    LRRC_LNAS_CALL_TYPE_EMERGENCY_CALL               = 3,            /* EMERGENCY call */
    LRRC_LNAS_CALL_TYPE_MO_CSFB                      = 4,            /* MO CSFB */

    LRRC_LNAS_CALL_TYPE_BUTT
};
typedef VOS_UINT32  LRRC_LNAS_CALL_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名: LRRC_LNAS_PLMN_SRCH_RLT_ENUM
 协议格式:
 ASN.1描述:
 枚举说明:
*****************************************************************************/
enum LRRC_LNAS_COVERAGE_TYPE_ENUM
{
    LRRC_LNAS_COVERAGE_TYPE_NONE      = 0,                /* 无网络覆盖 */
    LRRC_LNAS_COVERAGE_TYPE_LOW       = 1,                 /* 有质量网络覆盖   */
    LRRC_LNAS_COVERAGE_TYPE_HIGH      = 2,                /* 有高质量网络覆盖 */
    LRRC_LNAS_COVERAGE_TYPE_BUTT
};
typedef VOS_UINT32  LRRC_LNAS_COVERAGE_TYPE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : LRRC_LNAS_SESSION_TYPE_ENUM_UINT8
 枚举说明  : SESSION类型
 1.日    期   : 2014年5月22日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
enum LRRC_LNAS_SESSION_TYPE_ENUM
{
    LRRC_LNAS_SESSION_TYPE_MO_NORMAL_CALL           =0,
    LRRC_LNAS_SESSION_TYPE_MT_NORMAL_CALL           =1,
    LRRC_LNAS_SESSION_TYPE_MO_EMERGENCY_CALL        =2,
    LRRC_LNAS_SESSION_TYPE_MO_SS                    =3,
    LRRC_LNAS_SESSION_TYPE_MT_SS                    =4,
    LRRC_LNAS_SESSION_TYPE_MO_SMS                   =5,
    LRRC_LNAS_SESSION_TYPE_MT_SMS                   =6,
    LRRC_LNAS_SESSION_TYPE_MO_NORMAL_CSFB           =7,
    LRRC_LNAS_SESSION_TYPE_MO_EMERGENCY_CSFB        =8,
    LRRC_LNAS_SESSION_TYPE_MT_CSFB                  =9,
    LRRC_LNAS_SESSION_TYPE_PS_CONVERSAT_CALL        =10,
    LRRC_LNAS_SESSION_TYPE_PS_STREAM_CALL           =11,
    LRRC_LNAS_SESSION_TYPE_PS_INTERACT_CALL         =12,
    LRRC_LNAS_SESSION_TYPE_PS_BACKGROUND_CALL       =13,
    LRRC_LNAS_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL =14,
    LRRC_LNAS_SESSION_TYPE_PS_ATTACH                =15,
    LRRC_LNAS_SESSION_TYPE_PS_LOW_TAU               =16,
    LRRC_LNAS_SESSION_TYPE_PS_HIGH_TAU              =17,
    LRRC_LNAS_SESSION_TYPE_PS_DETACH                =18,
    LRRC_LNAS_SESSION_TYPE_PS_ESM                   =19,
    LRRC_LNAS_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 LRRC_LNAS_SESSION_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : LRRCL_NAS_NETSCAN_RESULT_ENUM
 结构说明  : 接入层回复NAS扫描结果
*****************************************************************************/
enum LRRC_LNAS_NETSCAN_RESULT_ENUM
{
    LRRC_LNAS_NETSCAN_RESULT_SUCCESS        = 0,
    LRRC_LNAS_NETSCAN_RESULT_FAILURE        = 1,

    LRRC_LNAS_NETSCAN_RESULT_BUTT
};
typedef   VOS_UINT8    LRRC_LNAS_NETSCAN_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : LRRC_LNAS_BOOL_ENUM
 结构说明  : 接入层NETSCAN BOOL值
*****************************************************************************/
enum LRRC_LNAS_BOOL_ENUM
{
    LRRC_LNAS_FALSE                                  = 0,
    LRRC_LNAS_FALSE_TRUE                             = 1,

    LRRC_LNAS_FALSE_BOOL_BUTT
};
typedef   VOS_UINT8    LRRC_LNAS_BOOL_ENUM_UINT8;


/*****************************************************************************
 枚举名    : LRRC_LNAS_NETSCAN_CAUSE_ENUM
 结构说明  : 接入层回复NAS扫描失败原因，如果当前没有任何模式驻留，NAS直接回复AT失败
*****************************************************************************/
enum LRRC_LNAS_NETSCAN_CAUSE_ENUM
{
    LRRC_LNAS_NETSCAN_CAUSE_SIGNAL_EXIST = 0,                /* 存在信令连接，NAS回复AT稍后再尝试 */
    LRRC_LNAS_NETSCAN_CAUSE_STATE_NOT_ALLOWED,               /* 当前状态不允许，NAS回复AT稍后再尝试 */
    LRRC_LNAS_NETSCAN_CAUSE_FREQ_LOCK,                       /* 当前锁频状态，NAS回复AT失败 */
    LRRC_LNAS_NETSCAN_CAUSE_PARA_ERROR,                      /* 参数错误，包含接入技术不支持，频段不支持，频点个数错误，门限错误，NAS回复AT失败 */

    LRRC_LNAS_NETSCAN_CAUSE_BUTT
};
typedef   VOS_UINT8    LRRC_LNAS_NETSCAN_CAUSE_ENUM_UINT8;

/*****************************************************************************
 结构名称   : LRRC_INTER_OPT_TYPE_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : LRRC通知LMM发生X->L互操作的类型
*****************************************************************************/
enum LRRC_LNAS_INTER_OPT_TYPE_ENUM
{
    LRRC_LNAS_INTER_OPT_TYPE_U2L_RESEL,
    LRRC_LNAS_INTER_OPT_TYPE_U2L_REDIR,
    LRRC_LNAS_INTER_OPT_TYPE_U2L_HO,

    LRRC_LNAS_INTER_OPT_TYPE_G2L_RESEL,
    LRRC_LNAS_INTER_OPT_TYPE_G2L_REDIR,
    LRRC_LNAS_INTER_OPT_TYPE_G2L_HO,
    LRRC_LNAS_INTER_OPT_TYPE_G2L_CCO,

    LRRC_LNAS_INTER_OPT_TYPE_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_INTER_OPT_TYPE_ENUM_UINT32;

/*****************************************************************************
 结构名称   : LRRC_INTER_OPT_INFO_TYPE_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : LRRC通知LMM发生X->L互操作的类型
*****************************************************************************/
enum LRRC_INTER_OPT_INFO_TYPE_ENUM
{
    LRRC_LNAS_INTER_OPT_INFO_TAILIST,

    LRRC_LNAS_INTER_OPT_INFO_BUTT
};
typedef VOS_UINT32 LRRC_INTER_OPT_INFO_TYPE_ENUM_UINT32;


/*****************************************************************************
 结构名称   : LRRC_INTER_OPT_TYPE_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : LRRC通知LMM发生X->L互操作的类型
*****************************************************************************/
enum LRRC_LMM_EXPERIENCE_SPEC_REQ_TYPE_ENUM
{
    LRRC_LMM_EXPERIENCE_SPEC_REQ_STOP_SLAVEMEAS,
    LRRC_LMM_EXPERIENCE_SPEC_REQ_RESTART_SLAVEMEAS,

    LRRC_LMM_EXPERIENCE_SPEC_REQ_BUTT
};
typedef VOS_UINT32 LRRC_LMM_EXPERIENCE_SPEC_REQ_TYPE_ENUM_UINT32;
/*****************************************************************************
 结构名称   : lRRC_LNAS_CSFB_STATUS_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : LMM通知LRRC CSFB操作的类型
*****************************************************************************/
enum lRRC_LNAS_CSFB_STATUS_ENUM
{
    LRRC_LNAS_CSFB_STATUS_INIT,
    LRRC_LNAS_CSFB_STATUS_START,
    LRRC_LNAS_CSFB_STATUS_END,

    LRRC_LNAS_CSFB_STATUS_BUTT
};
typedef VOS_UINT16  LRRC_LNAS_CSFB_STATUS_ENUM_UINT16;

/*****************************************************************************
 结构名称: LRRC_LNAS_CELL_TYPE_ENUM_UINT8
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
enum LRRC_LNAS_CELL_TYPE_ENUM
{
    LRRC_LNAS_CELL_TYPE_MACRO      = 0,          /* 小区类型是宏小区，或者混合小区宏驻留的时候用此类型 */
    LRRC_LNAS_CELL_TYPE_HYBRID     = 1,          /* 小区类型为混合小区且是CSG驻留的时候用此类型 */
    LRRC_LNAS_CELL_TYPE_CSG        = 2,          /* 小区类型为CSG小区 */
    LRRC_LNAS_CELL_TYPE_BUTT
};
typedef VOS_UINT8 LRRC_LNAS_CELL_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名称: LRRC_LNAS_CSG_LIST_SRCH_RLT_ENUM_UINT8
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
enum LRRC_LNAS_CSG_LIST_SRCH_RLT_ENUM
{
    LRRC_LNAS_CSG_LIST_SRCH_RLT_SUCC  = 0,
    LRRC_LNAS_CSG_LIST_SRCH_RLT_FAIL  = 1,
    LRRC_LNAS_CSG_LIST_SRCH_RLT_REJ   = 2,
    LRRC_LNAS_CSG_LIST_SRCH_RLT_NO_RF = 3,
    LRRC_LNAS_CSG_LIST_SRCH_RLT_BUTT
};
typedef VOS_UINT8 LRRC_LNAS_CSG_LIST_SRCH_RLT_ENUM_UINT8;



/*****************************************************************************
 结构名    : LRRC_LMM_BEGIN_SESSION_NOTIFY_STRU
 结构说明  : SESSION开始指示
 1.日    期   : 2014年5月22日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/
    LRRC_LNAS_SESSION_TYPE_ENUM_UINT8                 enSessionType;
    VOS_UINT8                                       aucReserved[3];
}LRRC_LMM_BEGIN_SESSION_NOTIFY_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_END_SESSION_NOTIFY_STRU
 结构说明  : SESSION终止指示
 1.日    期   : 2014年5月22日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/
    LRRC_LNAS_SESSION_TYPE_ENUM_UINT8                 enSessionType;
    VOS_UINT8                                       aucReserved[3];
}LRRC_LMM_END_SESSION_NOTIFY_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_DETACH_IND_STRU
 结构说明  : DETACH指示
 1.日    期   : 2014年11月14日
   作    者   : w00209181
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/
 }LRRC_LMM_DETACH_IND_STRU;

/*****************************************************************************
 结构名称   : LRRC_LMM_HO_SECU_PARA_STRU
 协议表格   : L->GU切换时安全参数
 ASN.1 描述 :
 结构说明   : LRRC_LMM_HO_SECU_PARA_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHoSecuPara;
    VOS_UINT8                           aucRsv[3];
} LRRC_LMM_HO_SECU_PARA_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_START_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_MM_START_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/
    LRRC_LNAS_SIM_STATUS_ENUM_UINT32      enSimStatus;        /* SIM卡状态*/

    /* 各模的优先级
        -------------------------------------------------------------
        aucRatPrioList [0]      |     LRRC_LNAS_RAT_TYPE_GSM
        -------------------------------------------------------------
        aucRatPrioList [1]      |     LRRC_LNAS_RAT_TYPE_WCDMA
        -------------------------------------------------------------
        aucRatPrioList [2]      |     LRRC_LNAS_RAT_TYPE_LTE
        -------------------------------------------------------------
    */

    LRRC_LNAS_RAT_PRIO_ENUM_UINT8        aucRatPrioList[LRRC_LNAS_RAT_TYPE_BUTT];

    /* 主要用于指示同时存在LTE_TDD和LTE_FDD制式，优先使用那种制式
    1:表示先启动FDD模式；2:表示先启动TDD模式 */
    VOS_UINT8                            enLteRatPrio;
    LRRC_LNAS_UTRAN_MODE_ENUM_UINT8      enUtranMode;
    VOS_UINT8                            aucReserved[1];
}LRRC_LMM_START_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_START_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_MM_START_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/

    LRRC_LNAS_START_RESULT_ENUM_UINT32    enResult;           /* 启动结果 */
}LRRC_LMM_START_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LNAS_PLMN_WITH_RAT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPlmnId[3];
    LRRC_LNAS_RAT_TYPE_ENUM_UINT8       enPlmnRat;
}LRRC_LNAS_PLMN_WITH_RAT_STRU;

/*****************************************************************************
 结构名    : LRRC_LNAS_LAC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : AC信息 可参考24.008 10.5.1.3
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLac;
    VOS_UINT8                           ucLacCont;
    VOS_UINT8                           aucReserved[2];
}LRRC_LNAS_LAC_STRU;

/*****************************************************************************
 结构名    : RRC_NAS_RAC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RAC信息 可参考24.008 10.5.5.15
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRac;
    VOS_UINT8                           aucReserved[3];
}RRC_NAS_RAC_STRU;

/*****************************************************************************
 结构名    : RRC_NAS_RAC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TAC信息  24.301  9.9.3.28
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTac;
    VOS_UINT8                           ucTacCont;
    VOS_UINT8                           aucReserved[2];
}LRRC_LNAS_TAC_STRU;


/*****************************************************************************
 结构名    : LRRC_LNAS_LA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LA信息数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LNAS_PLMN_ID_STRU                stPlmnId;
    LRRC_LNAS_LAC_STRU                    stLac;
}LRRC_LNAS_LA_STRU;

/*****************************************************************************
 结构名    : LRRC_LNAS_RA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RA信息数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LNAS_PLMN_ID_STRU                stPlmnId;
    LRRC_LNAS_LAC_STRU                    stLac;
    RRC_NAS_RAC_STRU                      stRac;
}LRRC_LNAS_RA_STRU;

/*****************************************************************************
 结构名    : LRRC_LNAS_TA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TA信息数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LNAS_PLMN_ID_STRU                stPlmnId;
    LRRC_LNAS_TAC_STRU                    stTac;
}LRRC_LNAS_TA_STRU;

/*****************************************************************************
 结构名    : LRRC_LNAS_EPLMN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 等效PLMN数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                            ulPlmnIdNum;        /* PLMN ID个数   */
    LRRC_LNAS_PLMN_ID_STRU                astEplmnIdList[LRRC_LNAS_MAX_EQUPLMN_NUM];
}LRRC_LNAS_EPLMN_STRU;

/*****************************************************************************
 结构名    : LRRC_LNAS_EPLMN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 等效PLMN数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                            ulForbLaNum;        /* 禁止注册区的个数 */
    LRRC_LNAS_LA_STRU                     astForbLacList[LRRC_LNAS_MAX_FORBLA_NUM];
}LRRC_LNAS_FORB_LA_LIST_STRU;

/*****************************************************************************
 结构名    : LRRC_LNAS_FORB_TA_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : forbid ta 列表数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                            ulTaNum;            /* TA的个数    */
    LRRC_LNAS_TA_STRU                     astForbTa[LRRC_LNAS_MAX_FORBTA_NUM];
}LRRC_LNAS_FORB_TA_LIST_STRU;
/* ncell spec search begin */
/*****************************************************************************
 结构名    : LRRC_LNAS_NCELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : NCELL 搜索数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLteArfcnNum;         /* 0表示LTE频点不存在 */
    VOS_UINT8                           aucRsv[3];             /* 保留位 */
    VOS_UINT32                          aulLteArfcnList[LRRC_LNAS_MAX_ARFCN_NUM];
    LRRC_LNAS_EPLMN_STRU                stEplmnList;           /* 临区相关等效PLMN信息*/

    VOS_UINT8                           ucLteCellIdNum;                         /*0表示LTE小区ID不存在*/
    VOS_UINT8                           aucRsv1[3];
    VOS_UINT16                          ausLteCellIdList[LRRC_LNAS_LTE_CELL_ID_MAX_NUM];
}LRRC_LNAS_NCELL_INFO_STRU;
/* ncell spec search end */

/*****************************************************************************
 结构名    : LRRC_LNAS_PLMN_WITH_CSG_ID_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PLMN和CSG ID信息结构
*****************************************************************************/
typedef struct
{
    LRRC_LNAS_PLMN_ID_STRU              stPlmnId;
    VOS_UINT32                          ulCsgId;
}LRRC_LNAS_PLMN_WITH_CSG_ID_STRU;

/*****************************************************************************
 结构名    : LRRC_LNAS_PLMN_WITH_CSG_ID_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSG白名单列表信息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                            ulPlmnWithCsgIdListNum;
    LRRC_LNAS_PLMN_WITH_CSG_ID_STRU       astPlmnWithCsgIdInfo[LRRC_LMM_MAX_PLMN_CSG_ID_NUM];
}LRRC_LNAS_PLMN_WITH_CSG_ID_LIST_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_PLMN_SEARCH_REQ_STRU
 协议表格  :
 ASN.1描述 : bitOpCsgIdListInfo；
                LRRC_LNAS_PLMN_SEARCH_SPEC: bitOpCsgIdListInfo = 1； stPlmnWithCsgIdList num = 0(白名单为空)
                LRRC_LNAS_PLMN_SRCH_HISTORY:bitOpCsgIdListInfo = 1；
                LRRC_LNAS_PLMN_SRCH_USER_CSG_SPEC: bitOpCsgIdListInfo = 1；
                LRRC_LNAS_PLMN_SRCH_FAST_CSG_SPEC: bitOpCsgIdListInfo = 1；
                其他类型bitOpCsgIdListInfo = 0；

 结构说明  : RRC_MM_PLMN_SEARCH_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32              enMsgId;        /*_H2ASN_Skip*/

    VOS_UINT32                              bitOpSpecPlmn: 1;
    VOS_UINT32                              bitOpEqlPlmn : 1;
    VOS_UINT32                              bitOpForbLa  : 1;
    VOS_UINT32                              bitOpForbTa  : 1;
    /* ncell spec search begin */
    VOS_UINT32                              bitOpNcellInfo: 1;
    VOS_UINT32                              bitOpPlmnInfoCampFlg:1; /* 底层上报的PLMN是否需要满足驻留条件，目前仅在获取地理信息接口中使用 */
    VOS_UINT32                              bitOpCsgIdListInfo:1;
    VOS_UINT32                              bitSpare     : 25;

    /* 搜索类型 */
    LRRC_LNAS_PLMN_SEARCH_TYPE_ENUM_UINT32    enSearchType;
    /*modified by wangchen 00209181  for 搜网优化,2015-04-28,begin*/
    LRRC_LNAS_FFT_SCAN_TYPE_ENUM_UINT8        enFftScanType;
    /*modified by wangchen 00209181  for 搜网优化,2015-04-28,end*/

    LRRC_LNAS_PLMN_SEARCH_SCENE_ENUM_UINT8    enPlmnSrchScene;
    VOS_UINT8                                 aucReserve[2];

    /* 指定PLMN ID */
    LRRC_LNAS_PLMN_ID_STRU                    stSpecPlmnId;

    /* 等效PLMN LIST */
    LRRC_LNAS_EPLMN_STRU                      stEplmn;

    /* 禁止LA列表  */
    LRRC_LNAS_FORB_LA_LIST_STRU               stForbLaList;

    /* 禁止TA列表  */
    LRRC_LNAS_FORB_TA_LIST_STRU               stForbTaList;
    /* ncell spec search begin */
    LRRC_LNAS_NCELL_INFO_STRU                 stNcellInfo;
    /* ncell spec search end */
    LRRC_LNAS_PLMN_WITH_CSG_ID_LIST_STRU      stPlmnWithCsgIdList;
}LRRC_LMM_PLMN_SEARCH_REQ_STRU;


/*****************************************************************************
 结构名    : LRRC_LNAS_LOW_PLMN_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_NAS_LOW_PLMN_INFO_STRU数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LNAS_PLMN_ID_STRU                stPlmnId;           /* PLMN ID    */
    VOS_INT32                             lRscp;              /* RSCP测量值 */
}LRRC_LNAS_LOW_PLMN_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LNAS_LOW_PLMN_WITH_RAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LNAS_LOW_PLMN_WITH_RAT_INFO_STRU数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LNAS_PLMN_WITH_RAT_STRU          stPlmnId;           /* PLMN ID    */
    VOS_INT32                             lRscp;              /* RSCP测量值 */
}LRRC_LNAS_LOW_PLMN_WITH_RAT_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LNAS_PLMN_ID_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_NAS_PLMN_ID_LIST_STRU数据结构
*****************************************************************************/
typedef struct
{
    /* 高质量PLMN的个数 */
    VOS_UINT32                            ulHighPlmnNum;

    /* 高质量PLMN列表   */
    LRRC_LNAS_PLMN_WITH_RAT_STRU          astHighPlmnWithRatList[LRRC_LNAS_MAX_HIGH_PLMN_NUM];


    /* 低质量PLMN的个数 */
    VOS_UINT32                            ulLowPlmnNum;

    /* 低质量PLMN列表   */
    LRRC_LNAS_LOW_PLMN_WITH_RAT_INFO_STRU astLowPlmnWithRatList[LRRC_LNAS_MAX_LOW_PLMN_NUM];
}LRRC_LNAS_PLMN_ID_LIST_STRU;


/*****************************************************************************
 结构名    : LRRC_LNAS_SUIT_PLMN_ID_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_NAS_SUIT_PLMN_ID_LIST_STRU数据结构
*****************************************************************************/
typedef struct
{
    /* 当前小区系统消息中包含的等效plmn id的个数 */
    VOS_UINT32                            ulSuitPlmnNum;

    /* 等效的plmn id的信息   */
    LRRC_LNAS_PLMN_ID_STRU                astSuitPlmnList[LRRC_LNAS_MAX_SEARCHED_PLMN_NUM];
} LRRC_LNAS_SUIT_PLMN_ID_LIST_STRU;

/*****************************************************************************
 结构名    : LRRC_LNAS_LIST_SEARCH_RAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LNAS_LIST_SEARCH_RAT_INFO_STRU数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LNAS_RAT_TYPE_ENUM_UINT8             senRat;                            /* 搜索的接入技术 */
    LRRC_LMM_RAT_LIST_SEARCH_RSLT_ENUM_UINT8  enListSearchRlt;                  /* 接入技术LIST搜索完成结果 */
    VOS_UINT8                                 aucReserved[2];
}LRRC_LNAS_LIST_SEARCH_RAT_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_PLMN_SEARCH_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_MM_PLMN_SEARCH_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/

    /* 搜索结果 */
    LRRC_LNAS_PLMN_SEARCH_RLT_ENUM_UINT32 enRlst;

    LRRC_LNAS_COVERAGE_TYPE_ENUM_UINT32   enCoverageType;     /* 当前接入技术下的网络覆盖类型 */

    /* 指定PLMN搜网成功时,搜到的PLMN ID,当ulSeaRlt为指定搜网成功时有效 */
    LRRC_LNAS_SUIT_PLMN_ID_LIST_STRU      stSpecPlmnIdList;

    /* 记录L主模下本次已经搜索的接入技术，仅在列表搜索时有效 */
    LRRC_LNAS_LIST_SEARCH_RAT_INFO_STRU   astSearchRatInfo[LRRC_LNAS_MAX_RAT_NUM];

    /* LIST PLMN搜索时,或spec plmn搜索失败时，该项有效 */
    LRRC_LNAS_PLMN_ID_LIST_STRU           stPlmnIdList;
}LRRC_LMM_PLMN_SEARCH_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_SEARCHED_PLMN_LIST_INFO_IND_STRU
 协议表格  : 用以plmn list和plmn spec搜索过程中向nas上报当前搜网结果
 ASN.1描述 :
 结构说明  : LRRC_LMM_SEARCHED_PLMN_LIST_INFO_IND_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                            /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/

    VOS_UINT32                            ulTaiNum;            /* Plmn的个数    */

    LRRC_LNAS_TA_STRU                     stTaiList[LRRC_LMM_MAX_SEARCHED_TAI_NUM];
}LRRC_LMM_SEARCHED_PLMN_INFO_IND_STRU;


/*****************************************************************************
 结构名    : LRRC_LMM_PLMN_SEARCH_STOP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : NAS只在NAS显式的使用RRC_MM_PLMN_SEARCH_REQ消息发起的SPEC PLMN和
              PLMN LIST、CSG LIST过程中，使用此消息通知RRC停止PLMN搜索；
              其他情况，如果NAS要发起PLMN搜索，则先给RRC 发送RRC_MM_REL_REQ
              消息， 然后再发送PLMN搜索消息，以确保RRC能进行后续的PLMN搜索;
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/
}LRRC_LMM_PLMN_SEARCH_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_PLMN_SEARCH_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC用该原语对RRC_GMM_PLMN_SEARCH_STOP_REQ确认。
              若RRC当前正在进行SPEC PLMN或者PLMN LIST搜索，需要停止相关操作，
              回复该消息，等待NAS发起RRC_MM_PLMN_SEARCH_REQ消息；
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/
}LRRC_LMM_PLMN_SEARCH_STOP_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_EQU_PLMN_NOTIFY_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_MM_EQU_PLMN_NOTIFY_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/

    /* RPLMN */
    LRRC_LNAS_PLMN_ID_STRU                stRPlmnId;          /* 当前注册上的PLMN，
                                                               若没有注册成功，填为0xFFFFFF*/

    /* EPLMN的个数,包含RPLMN */
    VOS_UINT32                            ulEquPlmnNum;

    /* 此EPLMN LIST可能更新的场景:
       注册成功时，表中包含包含网侧下发的EPLMN LIST和刚注册成功的RPLMN；
       注册失败时更新，1) 删除EPLMN列表，此列表为空；
                       2) 当前无注册的PLMN，但保留 EPLMNLIST，并且表中仍包含刚才
                          的RPLMN，即仍允许搜索刚才的RPLMN */
    LRRC_LNAS_PLMN_ID_STRU                aEquPlmnIdList[LRRC_LNAS_MAX_EQUPLMN_NUM];
} LRRC_LMM_EQU_PLMN_NOTIFY_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LNAS_S_TMSI_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : S-TMSI数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMmec;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulMTmsi;
}LRRC_LNAS_S_TMSI_STRU;

/*****************************************************************************
 结构名    : LRRC_LNAS_GUMMEI_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : globally unique MME identifier 数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMmec;
    LRRC_LNAS_GUMMEI_TYPE_ENUM_UINT8     enGummeiType;
    VOS_UINT16                          usMmeGi;
    LRRC_LNAS_PLMN_ID_STRU              stPlmnId;
}LRRC_LNAS_GUMMEI_STRU;

/*****************************************************************************
 结构名    : LRRC_LNAS_EST_INFO_STRU
 结构说明  : NAS在请求建链时，通过该信息携带S-TMSI，或者GUMMEI,以此来通知ENB，
 使用哪种方式选择MME
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ucBitOpSTmsi    :1;
    VOS_UINT32                          ucBitOpRegGummei:1;
    VOS_UINT32                          ucBitSpare      :30;

    LRRC_LNAS_S_TMSI_STRU               stStmsi;
    LRRC_LNAS_GUMMEI_STRU               stRegGummei;
}LRRC_LNAS_EST_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LNAS_EPLMN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 等效PLMN数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEHplmnIdNum;        /* PLMN ID个数   */
    LRRC_LNAS_PLMN_ID_STRU              astEHplmnIdList[LRRC_LNAS_MAX_EHPLMN_NUM];
}LRRC_LNAS_EHPLMN_LIST_STRU;

/*****************************************************************************
结构名    :LRRC_NAS_UEID_STRU
协议表格  :
ASN.1描述 :
结构说明  : IMSI, IMEI, IMEISV, TMSI, PTMSI的存放格式按照 31.102 4.2.2执行

    digit n 与 24.008 10.5.4  Mobile Identity information element 的对应关系:

    One digit occupies half of a byte.

    协议描述的 各DIGIT与字节/位的关系如下:
    ----------------------------------------------------------------------------------
    (BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    ----------------------------------------------------------------------------------
        Length of mobile identity contents, UNIT is byte
    ----------------------------------------------------------------------------------
        Identity digit 1       | OorE |  Type of identity
    ----------------------------------------------------------------------------------
        Identity digit 3       |           Identity digit 2
    ----------------------------------------------------------------------------------
        Identity digit i + 1   |           Identity digit i
    ----------------------------------------------------------------------------------
        ......                 |           ......
    ----------------------------------------------------------------------------------
        Identity digit P + 1   |           Identity digit P
    ----------------------------------------------------------------------------------

    即, 接口数组中各 DIGIT与字节位置对应关系如下:
    -----------------------------------------------------------------------------------------------
    (digit 15) | (digit 14) |.....| (digit  2) | (digit  1) |OorE|TypeOfId|Length of mobile identity contents, UNIT is byte
    -----------------------------------------------------------------------------------------------
    aucImsi[7] | aucImsi [7]|.....| aucImsi[2] | aucImsi[1] | aucImsi[1]  | aucImsi[0] | aucImsi[0]
    -----------------------------------------------------------------------------------------------
    aucImei[7] | aucImei [7]|.....| aucImei[2] | aucImei[1] | aucImei[1]  | aucImei[0] | aucImei[0]
    -----------------------------------------------------------------------------------------------
    aucTmsi[7] | aucTmsi [7]|.....| aucTmsi[2] | aucTmsi[1] | aucTmsi[1]  | aucTmsi[0] | aucTmsi[0]
    -----------------------------------------------------------------------------------------------
    aucPTmsi[7]|aucPTmsi [7]|.....| aucPTmsi[2]| aucPTmsi[1]| aucPTmsi[1] | aucPTmsi[0]| aucPTmsi[0]
    -----------------------------------------------------------------------------------------------
    aucImeisv[7]|aucImeisv[7]|....|aucImeisv[2]|aucImeisv[1]|aucImeisv[1] |aucImeisv[0]| aucImeisv[0]
    -----------------------------------------------------------------------------------------------


    e.g.          IMSI = 230 040 680000079
    在RRC_NAS的接口数组 aucImsi[] 中存放位置如下:

    协议描述的存放位置如下:
    ----------------------------------------------------------------------------------
                           (BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    ------------------------------------------------------------------------------------------------------------
    aucImsi[0] | aucImsi[0]                           8
    --------------------------------------------------------------------------------------------------------------------------------------
    aucImsi[1] | aucImsi[1]               2           |           9
    --------------------------------------------------------------------------------------------------------------------------------------
    aucImsi[2] | aucImsi[2]               0           |           3
    --------------------------------------------------------------------------------------------------------------------------------------
    aucImsi[3] | aucImsi[3]               4           |           0
    -------------------------- ------------------------------------------------------------------------------------------------------------
    aucImsi[4] | aucImsi[4]               6           |           0
    ---------------------------------------------------- ----------------------------------------------------------------------------------
    aucImsi[5] | aucImsi[5]               0           |           8
    ---------------------------------------------------- ----------------------------------------------------------------------------------
    aucImsi[6] | aucImsi[6]               0           |           0
    --------------------------------------------------------------------------------------------------------------------------------------
    aucImsi[7] | aucImsi[7]               0           |           0
    --------------------------------------------------------------------------------------------------------------------------------------
    aucImsi[8] | aucImsi[8]               9           |           7
    ------------------------------------------------------------------------------------------------------------

    即, 接口数组中各 DIGIT与字节位置对应关系如下:
    -----------------------------------------------------------------------------------------------
    aucImsi[7] | aucImsi [7]|.....| aucImsi[2] | aucImsi[1] | aucImsi[1]|aucImsi[0] | aucImsi[0]
    -----------------------------------------------------------------------------------------------
    (   9    ) | (    7   ) |.....| (    3   ) | (    2   ) | (   9   ) |           8
    -----------------------------------------------------------------------------------------------
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ucBitOpImsi     :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitOpHplmn    :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitOpEHplmn   :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitOpSTmsi    :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitShare      :28;


    VOS_UINT8                           aucImsi[LRRC_LNAS_MAX_UEID_BUF_SIZE];
    VOS_UINT8                           aucReserved1[2];
    LRRC_LNAS_S_TMSI_STRU               stStmsi;
    LRRC_LNAS_PLMN_ID_STRU              stHplmnId;
    LRRC_LNAS_EHPLMN_LIST_STRU          stEHplmn;
}LRRC_NAS_UEID_STRU;

/*****************************************************************************
 结构名    : LRRC_LNAS_SECURITY_KEY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_NAS_SECURITY_KEY_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulNasCount;
    VOS_UINT8                           aucKasme[LRRC_LNAS_MAX_ASME_KEY_LEN];
}LRRC_LNAS_SECURITY_KEY_STRU;


/*****************************************************************************
 结构名    : LRRC_LNAS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_NAS_INFO_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpAttach     : 1;
    VOS_UINT32                          bitOpSecurityKey: 1;
    VOS_UINT32                          bitOpDrxLength  : 1;
    /* gaojishan-anycamp-normal-camp */
    VOS_UINT32                          bitOpUsimStatus : 1;
    VOS_UINT32                          bitSpare        : 28;

    LRRC_LNAS_ATTACH_STATUS_ENUM_UINT32   enAttach;           /* Attach、Deattach标志 */
    LRRC_LNAS_SECURITY_KEY_STRU           stSecurityKey;
    VOS_UINT32                            ulDrxLength;        /* PS域协商后的DRX参数  */
    /* gaojishan-anycamp-normal-camp */
    LRRC_LNAS_SIM_STATUS_ENUM_UINT32      enUsimStatus;
}LRRC_LNAS_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_NAS_INFO_CHANGE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_MM_NAS_INFO_CHANGE_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/
    LRRC_LNAS_INFO_STRU                   stNasInfo;
}LRRC_LMM_NAS_INFO_CHANGE_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_CELL_SELECTION_CTRL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_MM_CELL_SELECTION_CTRL_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/

    LRRC_LNAS_RESEL_TYPE_ENUM_UINT32      enReselectInd;      /* 重选控制指示 */

    /* 禁止注册区列表 */
    LRRC_LNAS_FORB_LA_LIST_STRU           stForbLaList;
    /* 禁止TA列表  */
    LRRC_LNAS_FORB_TA_LIST_STRU           stForbTaList;

} LRRC_LMM_CELL_SELECTION_CTRL_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LNAS_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LNAS_MSG_STRU数据结构
*****************************************************************************/
typedef struct
{
    /* [1,LRRC_LNAS_MAX_DATA_LENGTH],Byte */
    VOS_UINT32                          ulNasMsgSize;

    /* 消息的前四个字节内容  */
    VOS_UINT8                           aucNasMsg[4];
    /*************************************************************************
        _H2ASN_Array2String
    *************************************************************************/
}LRRC_LNAS_MSG_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_EST_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_MM_EST_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/
    LRRC_LNAS_EST_CAUSE_ENUM_UINT32       enEstCause;         /* RRC Connection Req原因 */
    LRRC_LNAS_CALL_TYPE_ENUM_UINT32       enCallType;
    LRRC_LNAS_EST_INFO_STRU               stEstInfo ;         /* NAS请求建链时携带的信息，eNB根据该信息选择MME*/
    LRRC_LNAS_MSG_STRU                    stFirstNasMsg;      /* 发往CN的第一个NAS消息 */
}LRRC_LMM_EST_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_EST_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_MM_EST_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/
    LRRC_LNAS_EST_RESULT_ENUM_UINT32      enResult;           /* 连接建立结果 */
    /* v7r2 code begin */
    /* extendedWaitTime [1,1800][s]，不存在时默认为0 */
    VOS_UINT16                            usExtendedWaitTime;
    VOS_UINT8                             aucReserved[2];
    /* v7r2 code end */
}LRRC_LMM_EST_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_REL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : NAS通过此消息通知RRC释放RRC链接；释放时告知 RRC当前小区是否被barred
              NAS异常，也通过此消息通知RRC释放RRC链接，即通知RRC释放资源；
              严重错误要通过RRC_MM_START_REQ来通知RRC释放资源；
              RRC收到此消息后，释放RRC连接，以准备接收NAS后续可能进行的搜
              网和注册；
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/

    LRRC_LMM_BARRED_IND_ENUM_UINT32       enBarInd;
}LRRC_LMM_REL_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_REL_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_MM_REL_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/
}LRRC_LMM_REL_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_REL_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 正常的或异常的RRC主动发起的RRC连接释放，通过此消息通知NAS；
              或者NAS在RRC没有RRC连接的情况下，要求RRC转发NAS消息，RRC通过
              此消息通知NAS，发送失败，当前没有RRC连接
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/

    LRRC_LNAS_REL_CAUSE_ENUM_UINT32       enRelCause;       /* 信令释放原因 */
    /* v7r2 code begin */
    /* extendedWaitTime [1,1800][s]，不存在时默认为0 */
    VOS_UINT16                            usExtendedWaitTime;
    VOS_UINT8                             aucReserved[2];
    /* v7r2 code end */
}LRRC_LMM_REL_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_ERR_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC或L1发生严重异常，使用RRC_MM_ERR_IND通知NAS；
              NAS收到此消息的处理，和NAS收到APP_START_REQ消息的处理流程相同
              即，NAS收到后会清除NAS当前的资源，进入初始化后的状态，NAS读卡
              完成，然后给RRC发送START_REQ消息，再发起搜网和注册；
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/

    LRRC_LNAS_ERR_CAUSE_ENUM_UINT32       enErrCause;
}LRRC_LMM_ERR_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_SEARCHED_TYPE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 在丢网时进行过哪些搜索
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHistorySearchedFlg;                   /* 是否进行过history搜 */
    VOS_UINT8                           ucPrefBandSearchedFlg;                  /* 是否进行过pref band搜 */
    VOS_UINT8                           ucSpecSearchedFlg;                      /* 是否进行过spec搜 */
    VOS_UINT8                           ucReserve;
}LRRC_LMM_SEARCHED_TYPE_STRU;


/*****************************************************************************
 结构名    : LRRC_LMM_SYS_INFO_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_MM_SYS_INFO_IND_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/

    LRRC_LNAS_PLMN_ID_LIST_STRU           stPlmnIdList;

    LRRC_LNAS_AREA_LOST_ENUM_UINT32       enRptMode;        /* 报告模式 */
    LRRC_LMM_SEARCHED_TYPE_STRU           stSearchedType;   /* 在丢网时进行过哪些搜索 */
}LRRC_LMM_AREA_LOST_IND_STRU;


/*****************************************************************************
 结构名    : LRRC_LMM_SYS_INFO_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_MM_SYS_INFO_IND_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/

    LRRC_LNAS_SUIT_PLMN_ID_LIST_STRU      stSpecPlmnIdList;
    LRRC_LNAS_TAC_STRU                    stTac;              /* Tracking Area Code */
    VOS_UINT32                            ulCellId;           /* Cell Identity */
    VOS_UINT16                            usPhysCellId;       /* physCellId 0-503 */
    VOS_UINT8                             aucResverd[2];
    LRRC_LNAS_CELL_STATUS_ENUM_UINT32     enCellStatusInd;    /* 小区状态指示 */

    /* LTE当前驻留的频段，LTE的频段定义,aulLteBand[0]代表低32,
        aulLteBand[1]代表高32个Band, 例如 用户设置Band1,Band3,
        则aulLteBand[0]=0x05,aulLteBand[1]=0x00 */
    VOS_UINT32                            aulLteBand[2];

    VOS_UINT32                           ulArfcn;            /* 驻留频点信息 */
    VOS_UINT8                             ucBandWidth;        /* 带宽信息 */

    LRRC_LNAS_ACCESS_MODE_ENUM_UINT8    enAccessType;
    LRRC_LNAS_CELL_TYPE_ENUM_UINT8      enCellType;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulCsgId;         /* 0xFFFFFFFF为无效值 */
}LRRC_LMM_SYS_INFO_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_PAGING_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_MM_PAGING_IND_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/

    LRRC_LNAS_PAGING_TYPE_ENUM_UINT32     enPagingType;     /* 寻呼消息类型     */
    LRRC_LNAS_PAGING_CAUSE_ENUM_UINT32    enPagingCause;    /* Paging Cause,     */
    LRRC_LNAS_PAGING_UE_ID_ENUM_UINT32    enPagingUeId;     /* Paging Recorder Id*/
}LRRC_LMM_PAGING_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_DATA_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_MM_DATA_REQ_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/
    VOS_UINT32                            ulOpId;
    LRRC_LMM_DATA_CNF_ENUM_UINT32         enDataCnf;

    LRRC_LNAS_MSG_STRU                    stNasMsg;         /* 要发送的NAS消息*/
}LRRC_LMM_DATA_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_DATA_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_MM_DATA_CNF_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/
    VOS_UINT32                            ulOpId;
    LRRC_LMM_SEND_RSLT_ENUM_UINT32        enSendRslt;
}LRRC_LMM_DATA_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_DATA_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_MM_DATA_IND_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_STRU                    stNasMsg;
}LRRC_LMM_DATA_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_SECURITY_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_MM_SECURITY_IND_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32               enMsgId;     /*_H2ASN_Skip*/

    LRRC_LNAS_SECURITY_RPT_MODE_ENUM_UINT32    enRptMode;   /* 报告模式  */
}LRRC_LMM_SECURITY_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_POWER_OFF_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_MM_POWER_OFF_REQ_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/
    VOS_UINT8                             aucRsv[4];
}LRRC_LMM_POWER_OFF_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_POWER_OFF_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_MM_POWER_OFF_CNF_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/
    VOS_UINT8                             aucReserved[4];
}LRRC_LMM_POWER_OFF_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LRABM_QOS_UPDATE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_RABM_QOS_UPDATE_REQ_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/
}LRRC_LRABM_QOS_UPDATE_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LNAS_RAB_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_NAS_RAB_INFO_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                            ulRabId;            /* RAB ID, 即 LTE中的 EPS ID */
    VOS_UINT32                            ulRbId;             /* 该RAB 对应的RB ID */
    LRRC_LNAS_RAB_CHANGE_ENUM_UINT32      enRabChangeType;    /* RAB的操作类型 */
}LRRC_LNAS_RAB_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LRABM_RAB_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_RABM_RAB_IND_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/

    VOS_UINT32                            ulRabCnt;         /* 本次RAB操作的数量 */
    LRRC_LNAS_RAB_INFO_STRU               astRabInfo[LRRC_LNAS_MAX_RAB_SETUP_NUM];
}LRRC_LRABM_RAB_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LRABM_RAB_RSP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_RABM_RAB_RSP_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/

    VOS_UINT32                            ulRabCnt;         /* 建立RAB数量 */
    VOS_UINT32                            aulRabId[LRRC_LNAS_MAX_RAB_SETUP_NUM];
}LRRC_LRABM_RAB_RSP_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_ACCESS_GRANT_IND_STRU
 协议表格  : 当RRC的Access Barred解除或重选后，RRC使用该原语通知MM
 ASN.1描述 :
 结构说明  : RRC_MM_CELL_STATUS_IND_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32           enMsgId;         /*_H2ASN_Skip*/

    LRRC_LNAS_ACCESS_GRANT_ENUM_UINT32     enAccessGrantType;
} LRRC_LMM_ACCESS_GRANT_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LRABM_STATUS_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_RABM_STATUS_IND_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/

    /* RAB的状态类型 */
    LRRC_LNAS_RAB_STATUS_ENUM_UINT32      enStatus;

    /* RAB数量 */
    VOS_UINT32                          ulRabCnt;
    VOS_UINT32                          aulRabId[LRRC_LNAS_MAX_RAB_SETUP_NUM];
}LRRC_LRABM_STATUS_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LRABM_STATUS_RSP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_RABM_STATUS_RSP_STRU的数据结构，用于对RRC_RABM_STATUS_IND_STRU
            响应
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/
    LRRC_LNAS_STATUS_RESULT_ENUM_UINT32   enResult;
}LRRC_LRABM_STATUS_RSP_STRU;


/*****************************************************************************
 结构名    : LRRC_LMM_SUSPEND_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LMM_SUSPEND_IND_STRU用于通知LMM挂起的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    VOS_UINT32                              bitOpHoSecuPara : 1;
    VOS_UINT32                              bitSpare        : 31;

    LRRC_LMM_SUS_SYS_CHNG_DIR_ENUM_UINT32   enSysChngDir;
    LRRC_LMM_SYS_CHNG_TYPE_ENUM_UINT32      enSysChngType;
    LRRC_LMM_SUS_CAUSE_ENUM_UINT32          enSusCause;

    LRRC_LMM_HO_SECU_PARA_STRU              stHoSecuPara;
} LRRC_LMM_SUSPEND_IND_STRU;

/*****************************************************************************
 结构名称   : LRRC_LMM_SUSPEND_RSP_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LMM对LRRC_LMM_SUSPEND_IND_STRU的响应
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    LRRC_LNAS_RESULT_ENUM_UINT32            enRslt;
} LRRC_LMM_SUSPEND_RSP_STRU;

/*****************************************************************************
 结构名称   : LRRC_LMM_RESUME_IND_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LRRC_LMM_RESUME_IND_STRU用于通知LMM解挂的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/
    LRRC_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32   enRsmDir;
    LRRC_LMM_SYS_CHNG_TYPE_ENUM_UINT32      enResumeType;
    LRRC_LMM_CSFB_RESULT_ENUM_UINT32        enCsfbRslt;
} LRRC_LMM_RESUME_IND_STRU;

/*****************************************************************************
 结构名称   : LRRC_LMM_RESUME_RSP_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LMM对LRRC_LMM_RESUME_RSP_STRU的响应
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    VOS_UINT32                              ulRsv;
} LRRC_LMM_RESUME_RSP_STRU;

/*****************************************************************************
 结构名称   : LRRC_LMM_SUSPEND_REQ_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LRRC_LMM_SUSPEND_REQ_STRU用于通知LRRC子系统挂起
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    VOS_UINT32                              ulRsv;
} LRRC_LMM_SUSPEND_REQ_STRU;

/*****************************************************************************
 结构名称   : LRRC_LMM_SUSPEND_CNF_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LRRC对LRRC_LMM_SUSPEND_CNF_STRU的响应
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    VOS_UINT32                              ulRsv;
} LRRC_LMM_SUSPEND_CNF_STRU;

/* MBMS Begin */
/*****************************************************************************
 结构名称   : LRRC_LMM_MBMS_SESSION_CFG_REQ_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LRRC_LMM_MBMS_SESSION_CFG_REQ_STRU用于通知LRRC MBMS启动或停止
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    LRRC_LNAS_MBMS_SESSION_CFG_ENUM_UINT32  enSessionCfg;
} LRRC_LMM_MBMS_SESSION_CFG_REQ_STRU;

/*****************************************************************************
 结构名称   : LRRC_LMM_SUSPEND_CNF_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LRRC对LRRC_LMM_SUSPEND_CNF_STRU的响应
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    VOS_UINT32                              ulRsv;
} LRRC_LMM_MBMS_SESSION_CFG_CNF_STRU;

/*****************************************************************************
 结构名称   : LRRC_LMM_SUSPEND_CNF_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LRRC对LRRC_LMM_SUSPEND_CNF_STRU的响应
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    VOS_UINT32                              ulRsv;
} LRRC_LMM_MBMS_SESSION_IND_STRU;

/* MBMS End */

/*****************************************************************************
 结构名称   : LRRC_LMM_SECU_PARA_IND_STRU
 协议表格   : 从GU切换到L,LRRC给LNAS上报安全参数
 ASN.1 描述 :
 结构说明   : 24301 9.9.2.7 NAS security parameters to E-UTRA
                8 |  7 |  6 |  5 |  4 |  3 |  2 |  1 |
              ----------------------------------------------
                          NonceMME value                      octet 1-4
              ----------------------------------------------
                0 |              |  0 |
             spare|    EEA       |spare|    EIA       |       octet 5
              ----------------------------------------------
               |0 |  0 |  0 |  0 |TSC |NAS key set identifier octet 6
              ----------------------------------------------
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    VOS_UINT8                               aucSecuPara[LRRC_LNAS_GU2L_HO_SECU_PARA_LEN];
    VOS_UINT8                               aucRsv[2];
} LRRC_LMM_SECU_PARA_IND_STRU;

/*****************************************************************************
 结构名称   : LRRC_LMM_SECU_PARA_RSP_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : 异系统HO场景下，LNAS通过该消息通知LRRC, Kasme和 UP_NASCOUNT
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    LRRC_LNAS_SECURITY_KEY_STRU             stSecuKey;
} LRRC_LMM_SECU_PARA_RSP_STRU;

/*****************************************************************************
 结构名称: LRRC_LNAS_SYS_CFG_REQ_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* 此AT命令必然同时包含RAT和BAND，此处的bitop必然同时填1。 */
    VOS_UINT32                          bitOpRat:1;
    VOS_UINT32                          bitOpBand:1;
    VOS_UINT32                          bitSpare:30;

    NAS_RRC_USER_SET_FREQ_BAND_STRU     stBand;                                 /* 频段 */
    LRRC_LNAS_RAT_PRIO_ENUM_UINT8       aucRatPrioList[LRRC_LNAS_RAT_TYPE_BUTT];/* 各模的优先级 */
    LRRC_LNAS_UTRAN_MODE_ENUM_UINT8     enUtranMode;
    VOS_UINT8                           aucReserved[2];                         /* 字节对齐 */
} LRRC_LNAS_SYS_CFG_REQ_STRU;

/*****************************************************************************
 结构名    :  LRRC_LNAS_SYS_CFG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    LRRC_LNAS_RESULT_ENUM_UINT32         enRslt;            /* 目前的接口，只许成功 */
    LRRC_LNAS_SUSPEND_NOTIFY_ENUM_UINT32 enSusNotify;       /* 是否挂起LTE */
    /* gaojishan-2011-12-01-for-SYSCFG-Begin  */
    /* 指示EUTRAN、UTRAN和GERAN无线接入能力是否有变化，
            当enSusNotify指示需要挂起LTE时该字段无效。
           bit0、bit1、bit2分别标识EUTRAN、UTRAN和GERAN三模接入能力是否有变,高位预留
           '0'bit:标识无变化，'1'bit标识有变化
           eg. ucRadioAccCapChgInd = 6(dec)，表示 UTRAN和GERAN有变化，EUTRAN无变化 */

    VOS_UINT8                           ucRadioAccCapChgInd;
    VOS_UINT8                           aucRsvd[3];
    /* gaojishan-2011-12-01-for-SYSCFG-End  */
}LRRC_LNAS_SYS_CFG_CNF_STRU;


/*****************************************************************************
 结构名称   : LRRC_LMM_OOS_STATE_REQ_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : 丢网情况下用于通知LRRC 切换到从模
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    VOS_UINT8                               aucReservered[4];
} LRRC_LMM_OOS_STATE_REQ_STRU;
/*****************************************************************************
 结构名称   : LRRC_LMM_CLEAR_BUFF_NOTIFY_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : ATTACH_COMPLETE发送失败，TA发送变化，通知LRRC清缓存
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    VOS_UINT8                               aucReservered[4];
} LRRC_LMM_CLEAR_BUFF_NOTIFY_STRU;

/* lishangfeng bg begin */

/*****************************************************************************
 结构名    :  LRRC_LNAS_NOT_CAMP_ON_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           aucReservered[4];
}LRRC_LNAS_NOT_CAMP_ON_IND_STRU;

/*****************************************************************************
结构名    :LRRC_LMM_PLMN_ID_WITH_RAT_STRU
协议表格  :
ASN.1描述 :
结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPlmnId[3];
    LRRC_LNAS_RAT_TYPE_ENUM_UINT8       enPlmnRat;
}LRRC_LMM_PLMN_ID_WITH_RAT_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_BG_PLMN_SEARCH_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LMM_BG_PLMN_SEARCH_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* 指定PLMN ID及接入技术 */
    LRRC_LMM_PLMN_ID_WITH_RAT_STRU      stSpecPlmnWithRat;

    /* 禁止注册区的个数,在搜索LTE网络时无效 */
    VOS_UINT32                          ulForbRoamLaiNum;

    /* 禁止LAI信息,在搜索LTE网络时无效 */
    LRRC_LNAS_LA_STRU                   astForbRoamLaiList[LRRC_LNAS_BG_MAX_FORBLA_NUM];
}LRRC_LMM_BG_PLMN_SEARCH_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_BG_PLMN_SEARCH_CNF_STRU
 协议表格  :
 ASN.1描述 : 普通背景搜成功的场景下，RRC不上报不在白名单中的CSG ID的PLMN(假如当前PLMN只有CSG的情况)，
              因此MMC在后续下发FASE SPEC搜的时候不用携带白名单。
 结构说明  : LRRC_LMM_BG_PLMN_SEARCH_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* 搜索结果 */
    LRRC_LMM_BG_SRCH_RLT_ENUM_UINT32    enRlst;

    /* spec plmn搜索失败时，该项有效 */
    VOS_UINT32                          ulPlmnNum;
    LRRC_LMM_PLMN_ID_WITH_RAT_STRU      astPlmnIdWithRatList[LRRC_LNAS_BG_MAX_SRCH_PLMN_NUM];
} LRRC_LMM_BG_PLMN_SEARCH_CNF_STRU;

/*****************************************************************************
结构名    : LRRC_LMM_BG_PLMN_SEARCH_REQ_STOP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :LRRC_LMM_BG_PLMN_SEARCH_REQ_STOP_STRU
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
} LRRC_LMM_BG_PLMN_SEARCH_REQ_STOP_STRU;
/*****************************************************************************
 结构名称   : LRRC_LMM_SUSPEND_REL_REQ_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LRRC_LMM_SUSPEND_REL_REQ用于通知LRRC停止L到GU的重定向流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    VOS_UINT8                               aucRsv[4];
} LRRC_LMM_SUSPEND_REL_REQ_STRU;


/*****************************************************************************
 结构名    : LRRC_LMM_BG_PLMN_SEARCH_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_MMC_BG_PLMN_SEARCH_STOP_CNF_STRU 的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
} LRRC_LMM_BG_PLMN_SEARCH_STOP_CNF_STRU;

/* lishangfeng bg end */

/*****************************************************************************
 结构名    : LRRC_NAS_AC_CLASS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : AC参数
*****************************************************************************/
typedef struct
{
    /* Access control class，从低位到高位，分别代表 0~15 个接入级别,An AC is "allocated"
       if the corresponding bit is set to 1 and "not allocated" if this bit is set to 0. */
    VOS_UINT16                          usAccClassMask;
    VOS_UINT8                           aucRsvd[2];
}LRRC_NAS_AC_CLASS_STRU;


typedef struct
{
    VOS_MSG_HEADER                                             /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;           /*_H2ASN_Skip*/
    LRRC_LNAS_UTRAN_MODE_ENUM_UINT8         enUtranMode;       /* UTRAN的工作模式*/
    VOS_UINT8                               aucRsv[3];
} LRRC_LMM_UTRAN_MODE_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                             /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32               enMsgId;        /*_H2ASN_Skip*/
    LRRC_LNAS_CAPABILITY_CHANGE_ENUM_UINT32    enCapChangeInd;     /* 指示UE能力是否发送改变*/
}LRRC_LMM_UTRAN_MODE_CNF_STRU;

/*****************************************************************************
 结构名称   : LRRC_LMM_SUSPEND_REL_CNF_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LRRC_LMM_SYSPEND_REL_CNF用于通知LMM停止L到GU的重定向流程成功
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    VOS_UINT8                               aucRsv[4];
} LRRC_LMM_SUSPEND_REL_CNF_STRU;



/*****************************************************************************
 结构名称   : LRRC_LMM_RAT_CHANGE_IND_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LRRC_LMM_RAT_CHANGE_IND_STRU用于通知LMM底层的接入技术发生变化
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    LRRC_LNAS_SUSPEND_INFO_CHANGE_TYPE_ENUM_UINT32  ulInfoType;/*信息变更类型 : CSFB_REDIR_RAT_CHANGE;*/
    LRRC_LNAS_RAT_CHANGE_TYPE_ENUM_UINT32   ulRatChangeType;/* 枚举，两个值：U2G, G2U*/
    VOS_UINT8                               aucRsv[4];      /* 预留 */
}LRRC_LMM_SUSPEND_INFO_CHANGE_IND_STRU;

/*****************************************************************************
 结构名称: LMM_LRRC_OTHER_MODEM_INFO_NOTIFY_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                         /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32    ulMsgId;               /*_H2ASN_Skip*/
    VOS_UINT32                      bitOpCurrCampPlmnId:1;
    VOS_UINT32                      bitSpare:31;
    LRRC_LNAS_PLMN_ID_STRU        stCurrCampPlmnId;
}LMM_LRRC_OTHER_MODEM_INFO_NOTIFY_STRU;

/*****************************************************************************
 结构名称  : LRRC_LMM_NETSCAN_REQ_STRU;
 结构说明  : LTE LRRC_LMM_NETSCAN_REQ_STRU结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                        /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32      enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                        aulLteBand[2];      /* 具体取值同接口RRMM_SYS_CFG_REQ_STRU中频段参数一样，LTE_BAND_STRU*/
    VOS_UINT16                        usCellNum;          /* 需要扫描出超过门限的小区最大个数，最大个数为20*/
    VOS_INT16                         sCellPow;           /* 小区门限值:接入层收到后以RSRP来排序*/
    LRRC_LNAS_BOOL_ENUM_UINT8         enLteRat;           /* 0:接入模式不是LTE，1: 接入模式是LTE */
    VOS_UINT8                         aucReserve[3];
}LRRC_LMM_NETSCAN_REQ_STRU;


/*****************************************************************************
 结构名    : LRRC_LMM_NETSCAN_INFO_STRU;
 结构说明  : LTE LRRC_LMM_NETSCAN_INFO_STRU CNF结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                       usArfcn;/*Frequency Channel Number（EARFCN）*/
    VOS_UINT16                       usTac;  /*Tracking Area Code,跟踪区域码*/
    VOS_UINT32                       ulMcc;
    VOS_UINT32                       ulMnc;
    VOS_UINT32                       ulCI;   /*string type; four byte GERAN/UTRAN/E-UTRAN cell ID in hexadecimal format,RRC_SIB_TYPE1: cell identity，用作业务层面锁服务使用*/
    VOS_UINT32                       aulBand[2]; /* 具体取值同接口RRMM_SYS_CFG_REQ_STRU中频段参数一样，LTE_BAND_STRU*/
    VOS_UINT32                       ulPci;  /*L需要使用physical cell id和频点结合来确定一个小区*/
    VOS_INT16                        sRxlev;/*receive signal level (dBm)*/
    VOS_INT16                        sRsrp; /*RSRP:Parameter determines the received signal code power level of the cell that was scanned, range from -140 dBm to -44 dBm*/
}LRRC_LMM_NETSCAN_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_NETSCAN_CNF_STRU;
 结构说明  : LTE LRRC_LMM_NETSCAN_CNF_STRU CNF结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                           /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32             enMsgId;        /*_H2ASN_Skip*/
    LRRC_LNAS_NETSCAN_RESULT_ENUM_UINT8      enResult;
    LRRC_LNAS_NETSCAN_CAUSE_ENUM_UINT8       enCause;
    VOS_UINT8                                ucFreqNum;
    VOS_UINT8                                aucReserve[1];
    LRRC_LMM_NETSCAN_INFO_STRU               astNetScanInfo[LRRC_LNAS_NETSCAN_MAX_FREQ_NUM];
}LRRC_LMM_NETSCAN_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_NETSCAN_STOP_REQ_STRU
 结构说明  : LMM请求接入层停止进行网络扫描消息结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgId;            /*_H2ASN_Skip*/
}LRRC_LMM_NETSCAN_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_NETSCAN_STOP_CNF_STRU
 结构说明  : LRRC接入层停止扫描结果回复消息结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                           ucFreqNum;
    VOS_UINT8                           aucReserve[3];
    LRRC_LMM_NETSCAN_INFO_STRU          astNetScanInfo[LRRC_LNAS_NETSCAN_MAX_FREQ_NUM];
}LRRC_LMM_NETSCAN_STOP_CNF_STRU;

/*****************************************************************************
 结构名称: LRRC_LMM_DISABLE_LTE_NOTIFY_STRU
 协议表格: 美国AT&T定制需求，通知LRRC LTE被disable
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                        /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32    ulMsgId;              /*_H2ASN_Skip*/

    VOS_UINT32                      ulRsv;
}LRRC_LMM_DISABLE_LTE_NOTIFY_STRU;


/*****************************************************************************
 结构名称   : LRRC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : ID_LRRC_LMM_CELL_SIGN_REPORT_NOTIFY对应结构体，用于通知LRRC信号质量上报的门限值和时间间隔
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32    ulMsgId;                /*_H2ASN_Skip*/
    VOS_UINT8                       ucMinRptTimerInterval;  /*时间间隔，为0时:RSSI变化达到门限值时立即上报，门限取值如下*/
    VOS_UINT8                       ucSignThreshold;        /*门限值，为0时:如果之前没有给接入层通知过有效值(1-5db),接入层用
                                                              NV配置值；如果之前给接入层通知过有效值，接入层仍然用上次的有效值*/
    VOS_UINT8                       aucRsv[2];
}LRRC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU;

/*****************************************************************************
 结构名称   : LRRC_LMM_CQI_INFO_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LTE下的信道质量，两个码字分别代表子带CQI和宽带CQI
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      usRI;                   /*RI值，1时仅ausCQI[0]有效；2时ausCQI[0]和ausCQI[1]均有效*/
    VOS_UINT8                       aucRes[2];
    VOS_UINT16                      ausCQI[2];
}LRRC_LMM_CQI_INFO_STRU;

/*****************************************************************************
 结构名称   : LRRC_LMM_CELL_SIGN_REPORT_IND_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : ID_LRRC_LMM_CELL_SIGN_REPORT_IND对应结构体，LTE下的Rssi、Rsrp、Rsrq和CQI
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                            /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        ulMsgId;              /*_H2ASN_Skip*/
    VOS_INT16                           sRssi;                /**/
    VOS_INT16                           sRsd;                 /*填充字段*/
    VOS_INT16                           sRsrp;                /*范围(-141,-44),99为无效*/
    VOS_INT16                           sRsrq;                /*范围(-40,-6),99为无效*/
    VOS_INT32                           lSinr;
    LRRC_LMM_CQI_INFO_STRU              stCQI;
}LRRC_LMM_CELL_SIGN_REPORT_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_EXPERIENCE_SPEC_REQ
 结构说明  : LMM下发给RRC的涉及用户体验的指示
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32         enMsgId;           /*_H2ASN_Skip*/
    LRRC_LMM_EXPERIENCE_SPEC_REQ_TYPE_ENUM_UINT32  enSpecReq;
    VOS_UINT16                           usRsv0;
    VOS_UINT16                           usRsv1;
    VOS_UINT8                            ausData[4];
}LRRC_LMM_EXPERIENCE_SPEC_REQ;

/*****************************************************************************
 结构名    : LRRC_LMM_BG_SEARCH_HRPD_REQ_STRU
 结构说明  : LMM向LRRC下发的背景搜EHRPD请求的消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           ausData[4];
}LRRC_LMM_BG_SEARCH_HRPD_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_BG_SEARCH_HRPD_STOP_REQ_STRU
 结构说明  : LMM向LRRC下发的停止背景搜EHRPD请求的消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           ausData[4];
}LRRC_LMM_BG_SEARCH_HRPD_STOP_REQ_STRU;


typedef struct
{
    VOS_UINT32                            ulTaiNum;            /* Plmn的个数    */
    LRRC_LNAS_TA_STRU                     stTaiList[LRRC_LMM_MAX_SEARCHED_TAI_NUM];
}LRRC_LNAS_OPT_INFO_TAILIST_STRU;


/*****************************************************************************
 结构名    : LRRC_LMM_INTER_OPT_IND
 结构说明  : LRRC向LMM指示发生互操作流程的成功或失败
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                            /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/
    LRRC_LNAS_INTER_OPT_TYPE_ENUM_UINT32  enInterOptType;
    VOS_UINT32                            ulBitOpTaList :1;
    VOS_UINT32                            ulBitRsv :1;
    VOS_UINT32                            ulBitRsv1:1;
    VOS_UINT32                            ulBitRsv2:1;
    VOS_UINT32                            ulBitRsv3:28;

    VOS_UINT32                            ulRsv;
    VOS_UINT16                            usRsv0;
    VOS_UINT16                            usRsv1;

    LRRC_LNAS_OPT_INFO_TAILIST_STRU       stOptInfoTaiList;
}LRRC_LMM_INTER_OPT_IND;

typedef struct
{
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgID;            /*_H2ASN_MsgChoice_Export LRRC_LNAS_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LRRC_LNAS_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}LRRC_LNAS_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    LRRC_LNAS_MSG_DATA                    stMsgData;
} RrcNasInterface_MSG;
/*****************************************************************************
 结构名    : LRRC_LMM_CSFB_NOTIFY_STRU
 结构说明  : LMM通知LRRC CSFB流程启动以及结束
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                            /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/
    LRRC_LNAS_CSFB_STATUS_ENUM_UINT16     enCsfbStatus;
    VOS_UINT16                            usRsv;
}LRRC_LMM_CSFB_NOTIFY_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_HRPD_SYS_STRU
 结构说明  : EHRPD的网络参数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucSubnetId[LRRC_LMM_HRPD_SUBNET_MAX_LEN];
    VOS_UINT16                          usBandClass;
    VOS_UINT16                          usFreq;
}LRRC_LMM_HRPD_SYS_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_BG_SEARCH_HRPD_CNF_STRU
 结构说明  : LRRC向LMM回复的背景搜EHRPD结果消息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    LRRC_LMM_BG_SRCH_RLT_ENUM_UINT32    enRslt;

    VOS_UINT8                           ucHrpdSysNum;
    VOS_UINT8                           aucRsv[3];
    LRRC_LMM_HRPD_SYS_STRU              astHrpdSysList[LRRC_LMM_BG_HRPD_MAX_SUBNET_NUM];

}LRRC_LMM_BG_SEARCH_HRPD_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_BG_SEARCH_HRPD_STOP_CNF_STRU
 结构说明  : LRRC向LMM回复的停止背景搜EHRPD确认消息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
}LRRC_LMM_BG_SEARCH_HRPD_STOP_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LNAS_PLMN_CSG_ID_WITH_RAT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 带接入技术的CSG ID信息结构
*****************************************************************************/
typedef struct
{
    LRRC_LMM_PLMN_ID_WITH_RAT_STRU      stPlmnWithRat;
    VOS_UINT32                          ulCsgId;
}LRRC_LNAS_PLMN_CSG_ID_WITH_RAT_STRU;

/*****************************************************************************
 结构名    : LRRC_LNAS_CSG_ID_HOME_NODEB_NAME_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSG ID对应HOME NODEB名称结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHomeNodeBNameLen;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucHomeNodeBName[LRRC_LMM_MAX_HOME_NODEB_NAME_LEN];
}LRRC_LNAS_CSG_ID_HOME_NODEB_NAME_STRU;

/*****************************************************************************
 结构名    : LRRC_LNAS_CSG_WHITE_LIST_NOTIFY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSG白名单指示消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                            /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                            ulOpId;
    LRRC_LNAS_PLMN_WITH_CSG_ID_LIST_STRU  stPlmnWithCsgIdList;
}LRRC_LMM_CSG_WHITE_LIST_NOTIFY_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_CSG_BG_SEARCH_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSG背景搜网请求消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/
    VOS_UINT32                            ulOpId;

    /* 指定PLMN CSG ID及接入技术 */
    LRRC_LMM_PLMN_ID_WITH_RAT_STRU        stSpecPlmnWithRat;
    VOS_UINT32                            ulCsgIdNum;
    VOS_UINT32                            aulCsgId[LRRC_LMM_MAX_PLMN_CSG_ID_NUM];
}LRRC_LMM_CSG_BG_SEARCH_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LMM_CSG_LIST_SEARCH_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSG列表搜网请求消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                            /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                            ulOpId;
}LRRC_LMM_CSG_LIST_SEARCH_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LNAS_PLMN_WITH_CSG_ID_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSG列表搜网回复的高质量网络信息数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LNAS_PLMN_CSG_ID_WITH_RAT_STRU   stPlmnCsgIdWithRat;
    LRRC_LNAS_CSG_ID_HOME_NODEB_NAME_STRU stHomeNodeBName;
}LRRC_LNAS_HIGH_PLMN_WITH_CSG_ID_STRU;

/*****************************************************************************
 结构名    : LRRC_LNAS_CSG_LIST_SEARCHED_PLMN_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSG列表搜网回复的高低质量网络信息数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LNAS_PLMN_CSG_ID_WITH_RAT_STRU   stPlmnCsgIdWithRat;
    LRRC_LNAS_CSG_ID_HOME_NODEB_NAME_STRU stHomeNodeBName;
    VOS_INT32                             lRscp;                   /* RSCP测量值 */
}LRRC_LNAS_CSG_LIST_SEARCHED_PLMN_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LNAS_CSG_LIST_SEARCHED_RESULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSG列表搜网结果高低质量网络列表信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                 ulTotalPlmnNum; /* 高低质量PLMN总个数 */
    VOS_UINT32                                 ulHighPlmnNum;  /* 高质量PLMN的个数 */

    /* 高低质量PLMN列表   */
    LRRC_LNAS_CSG_LIST_SEARCHED_PLMN_INFO_STRU  astCsgListSearchedPlmnInfoList[LRRC_LMM_MAX_PLMN_CSG_ID_NUM];
}LRRC_LNAS_CSG_LIST_SEARCHED_RESULT_STRU;

/*****************************************************************************
 结构名称: LRRC_LMM_CSG_LIST_SEARCH_CNF_STRU
 协议表格:
 ASN.1 描述: RRC上报的列表按高低优先级顺序，假如列表满了，保证CSG ID优先上报(即如果有宏的会替换掉宏的)
 结构说明:LTE通知CSG列表搜网结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                             /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32           ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                             ulOpId;

    /* 搜索结果，1、在非驻留态搜到的PLMN数目大于0，为SUCC，否非如果是NO RF上报NO RF原因值
       否则上报FAIL;
       2、在驻留态搜索正常结束(无论搜到的PLMN数目是否为0)，为SUCC，NO RF 或被抢则为NO RF，
       除了SUCC和NO RF的情况皆为REJ */
    LRRC_LNAS_CSG_LIST_SRCH_RLT_ENUM_UINT8 enRlst;
    VOS_UINT8                              aucReserved[3];

    /* CSG LIST PLMN搜索结果 */
    LRRC_LNAS_CSG_LIST_SEARCHED_RESULT_STRU stCsgListSearchedResult;
}LRRC_LMM_CSG_LIST_SEARCH_CNF_STRU;

/*****************************************************************************
 结构名称: LRRC_LMM_CSG_BG_SEARCH_CNF_STRU
 协议表格:
 ASN.1 描述:
 结构说明:LTE通知CSG背景搜网结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                            /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                            ulOpId;

    /* 搜索结果 */
    LRRC_LNAS_BG_SRCH_RLT_ENUM_UINT32     enRlst;

    /* 搜索成功的时候只报1个，CSG BG搜索失败时，可能携带多个, 但是只携带CSG ID网络，PLMN也可能不同 */
    VOS_UINT32                            ulPlmnCsgIdNum;
    LRRC_LNAS_PLMN_CSG_ID_WITH_RAT_STRU   astPlmnCsgIdWithRat[LRRC_LMM_MAX_PLMN_CSG_ID_NUM];
}LRRC_LMM_CSG_BG_SEARCH_CNF_STRU;

/*****************************************************************************
 结构名称: LRRC_LMM_CSG_ID_HOME_NODEB_NAME_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明:LTE通知CSG ID对应的HOME NODEB名称
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          ulMsgId;          /*_H2ASN_Skip*/
    VOS_UINT32                            ulOpId;

    LRRC_LNAS_PLMN_WITH_CSG_ID_STRU       stPlmnWithCsgId;
    LRRC_LNAS_CSG_ID_HOME_NODEB_NAME_STRU stHomeNodeBName;
}LRRC_LMM_CSG_ID_HOME_NODEB_NAME_IND_STRU;
/*****************************************************************************
 结构名称: LRRC_LMM_UE_CAP_CHANGE_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明:LRRC通知LNAS UE能力改变
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          ulMsgId;          /*_H2ASN_Skip*/
}LRRC_LMM_UE_CAP_CHANGE_IND_STRU;



/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

/*****************************************************************************
 Function Name  : LRRC_LNAS_GetMmInfo
 Discription    : 向其他模块提供接口，使得其他模块能获取UE 的ID信息，C03版本
                  目前只有IMSI信息；
 Input          : LRRC_LNAS_INFO_TYPE_ENUM_UINT32  ulInfoType
 Output         : None
 Return         : VOS_NULL:  获取失败
                  否则    :  LRRC_NAS_UEID_STRU * ,指向IMSI数据,
                             g_stGmmStaticPara.stGmmUeId,首地址的指针
 History:
*****************************************************************************/
VOS_VOID*  LRRC_LNAS_GetMmInfo( LRRC_LNAS_INFO_TYPE_ENUM_UINT32  enInfoType );
extern LRRC_LNAS_SMC_CTRL_ENUM_UINT8 LRRC_LNAS_GetSmcState( VOS_VOID );

extern LRRC_LNAS_RESULT_ENUM_UINT32  LRRC_GetEutraUeCap(
        const LRRC_LNAS_PLMN_ID_STRU stPlmnId, VOS_UINT16 *pusDataLen, VOS_UINT8 *pucEncData );

/*****************************************************************************
 Function Name   : LRRC_LNAS_GetPowerOffFlag
 Description     : LRRC通过该接口获取EMM关机标识，用于判断LRRC收到的空口是否是关机detach
                   该标志在LMM收到MMC关机请求置上，在收到LRRC power off cnf、收到开机请求
                   或者等待LRRC power off cnf超时时清除
 Input           : None
 Output          : None
 Return          : 1 表示标识有效，即LMM正在关机过程中
                   0 表示标识无效
 History         :
    1.leixiantiao 00258641      2014-07-14  Draft Enact

*****************************************************************************/

extern VOS_UINT8 LRRC_LNAS_GetPowerOffFlag(VOS_VOID);

extern VOS_UINT8 LRRC_LNAS_IsDamConfitionSatisfied(VOS_VOID);

extern VOS_UINT8 LRRC_LNAS_IsMsgContainsSMS(VOS_UINT32 ulMsgSize, VOS_UINT8 *pstMsg);

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

#endif /* end of 发送模块+接收模块+Interface.h */

