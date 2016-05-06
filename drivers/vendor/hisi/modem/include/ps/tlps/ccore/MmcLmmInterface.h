
#ifndef __MMCLMMINTERFACE_H__
#define __MMCLMMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "LPSCommon.h"
#include "ComInterface.h"

#include "PsTypeDef.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/
    /* 等效PLMN最大数*/
#define MMC_LMM_MAX_EQUPLMN_NUM         (16)

    /* 指定PLMN上报的共享PLMN最大数 */
#define MMC_LMM_MAX_SRCH_PLMN_NUM       (16)

    /* 背景PLMN搜索上报的PLMN最大数 */
#define MMC_LMM_MAX_BG_SRCH_PLMN_NUM    (16)

    /* 背景搜索GU PLMN时最大的禁止LAI个数 */
#define MMC_LMM_MAX_FORB_ROAM_LAI_NUM   (16)

    /* 高质量PLMN最大数 */
#define MMC_LMM_MAX_HIGH_PLMN_NUM       (48)

    /* 低质量PLMN最大数 */
#define MMC_LMM_MAX_LOW_PLMN_NUM        (48)
#define MMC_LMM_PLMN_ID_LEN             (3)

#define NAS_MAX_SIZE_PTMSI              (4)

#define NAS_MAX_SIZE_MS_IDENTITY        (9)


#define NAS_MAX_SIZE_PTMSI_SIGNATURE    (3)

#define NAS_UMTS_CK_LENGTH              (16)
#define NAS_UMTS_IK_LENGTH              (16)
#define MMC_LMM_MAX_PLMN_NUM            (64)

#define MMC_LMM_MAX_RAT_NUM             (3)

#define MMC_LMM_MAX_FORB_ROAM_TAI_NUM   (64)
#define MMC_LMM_MAX_FORB_RPOS_TAI_NUM   (64)

#define MMC_LMM_MAX_OPER_LONG_NAME_LEN       (100)
#define MMC_LMM_MAX_OPER_SHORT_NAME_LEN      (100)

#define  MMC_LMM_LTE_ARFCN_MAX_NUM      (8)                 /* LTE频点列表最大个数 */

#define  MMC_LMM_LTE_CELL_ID_MAX_NUM      (8)               /* LTE小区ID列表最大个数 */

#define LMM_MMC_EMERGENCY_NUM_MAX_LEN            (46)
#define LMM_MMC_EMERGENCY_NUM_LIST_MAX_RECORDS   (16)

#define LMM_MMC_MAX_SEARCHED_TAI_NUM            (16)

#define MMC_LMM_MAX_EUTRAN_NOT_ALLOW_PLMN_NUM   (16)
#define LMM_MMC_HRPD_SUBNET_MAX_LEN             (16)
#define LMM_MMC_BG_HRPD_MAX_SYS_NUM             (16)


#define MMC_LMM_MAX_PLMN_CSG_ID_NUM             (35)
#define MMC_LMM_MAX_HOME_NODEB_NAME_LEN         (48)
#define MMC_LMM_MAX_CSG_LIST_SRCH_RSLT_NUM      (20)


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum    MMC_LMM_MSG_ID_ENUM
{
    /* MMC发给LMM的消息原语 */
    ID_MMC_LMM_START_REQ                = (PS_MSG_ID_MMC_TO_LMM_BASE+0x01),     /* _H2ASN_MsgChoice MMC_LMM_START_REQ_STRU */
    ID_MMC_LMM_STOP_REQ                 = (PS_MSG_ID_MMC_TO_LMM_BASE+0x02),     /* _H2ASN_MsgChoice MMC_LMM_STOP_REQ_STRU */
    ID_MMC_LMM_PLMN_SRCH_REQ            = (PS_MSG_ID_MMC_TO_LMM_BASE+0x03),     /* _H2ASN_MsgChoice MMC_LMM_PLMN_SRCH_REQ_STRU */
    ID_MMC_LMM_STOP_PLMN_SRCH_REQ       = (PS_MSG_ID_MMC_TO_LMM_BASE+0x04),     /* _H2ASN_MsgChoice MMC_LMM_STOP_PLMN_SRCH_REQ_STRU */
    ID_MMC_LMM_EPLMN_NOTIFY_REQ         = (PS_MSG_ID_MMC_TO_LMM_BASE+0x05),     /* _H2ASN_MsgChoice MMC_LMM_EPLMN_NOTIFY_REQ_STRU */
    ID_MMC_LMM_CELL_SELECTION_CTRL_REQ  = (PS_MSG_ID_MMC_TO_LMM_BASE+0x06),     /* _H2ASN_MsgChoice MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU */
    ID_MMC_LMM_ACTION_RESULT_REQ        = (PS_MSG_ID_MMC_TO_LMM_BASE+0x07),     /* _H2ASN_MsgChoice MMC_LMM_ACTION_RESULT_REQ_STRU */
    ID_MMC_LMM_REL_REQ                  = (PS_MSG_ID_MMC_TO_LMM_BASE+0x08),     /* _H2ASN_MsgChoice MMC_LMM_REL_REQ_STRU */
    ID_MMC_LMM_SUSPEND_REQ              = (PS_MSG_ID_MMC_TO_LMM_BASE+0x09),     /* _H2ASN_MsgChoice MMC_LMM_SUSPEND_REQ_STRU */
    ID_MMC_LMM_CSFB_REQ                 = (PS_MSG_ID_MMC_TO_LMM_BASE+0x0A),     /* _H2ASN_MsgChoice MMC_LMM_CSFB_REQ_STRU */
    ID_MMC_LMM_SYS_CFG_REQ              = (PS_MSG_ID_MMC_TO_LMM_BASE+0x0B),     /* _H2ASN_MsgChoice MMC_LMM_SYS_CFG_REQ_STRU */
    ID_MMC_LMM_USIM_STATUS_REQ          = (PS_MSG_ID_MMC_TO_LMM_BASE+0x0C),     /* _H2ASN_MsgChoice MMC_LMM_USIM_STATUS_REQ_STRU */
    ID_MMC_LMM_ATTACH_REQ               = (PS_MSG_ID_MMC_TO_LMM_BASE+0x0D),     /* _H2ASN_MsgChoice MMC_LMM_ATTACH_REQ_STRU */
    ID_MMC_LMM_DETACH_REQ               = (PS_MSG_ID_MMC_TO_LMM_BASE+0x0E),     /* _H2ASN_MsgChoice MMC_LMM_DETACH_REQ_STRU */
    ID_MMC_LMM_RESUME_NOTIFY            = (PS_MSG_ID_MMC_TO_LMM_BASE+0x0F),     /* _H2ASN_MsgChoice MMC_LMM_RESUME_NOTIFY_STRU */
    ID_MMC_LMM_SUSPEND_RSP              = (PS_MSG_ID_MMC_TO_LMM_BASE+0x10),     /* _H2ASN_MsgChoice MMC_LMM_SUSPEND_RSP_STRU*/
    ID_MMC_LMM_DISABLE_LTE_NOTIFY       = (PS_MSG_ID_MMC_TO_LMM_BASE+0x11),     /* _H2ASN_MsgChoice MMC_LMM_DISABLE_LTE_NOTIFY_STRU*/
    ID_MMC_LMM_ENABLE_LTE_NOTIFY        = (PS_MSG_ID_MMC_TO_LMM_BASE+0x12),     /* _H2ASN_MsgChoice MMC_LMM_ENABLE_LTE_NOTIFY_STRU*/
    ID_MMC_LMM_USER_PLMN_END_NOTIFY     = (PS_MSG_ID_MMC_TO_LMM_BASE+0x13),     /* _H2ASN_MsgChoice MMC_LMM_USER_PLMN_END_NOTIFY_STRU*/
    ID_MMC_LMM_UE_OOC_STATUS_NOTIFY     = (PS_MSG_ID_MMC_TO_LMM_BASE+0x14),     /* _H2ASN_MsgChoice MMC_LMM_UE_OOC_STATUS_NOTIFY_STRU*/
    ID_MMC_LMM_WCDMA_SYS_INFO_IND       = (PS_MSG_ID_MMC_TO_LMM_BASE+0x15),     /* _H2ASN_MsgChoice MMC_LMM_WCDMA_SYS_INFO_IND_STRU*/
    ID_MMC_LMM_GSM_SYS_INFO_IND         = (PS_MSG_ID_MMC_TO_LMM_BASE+0x16),     /* _H2ASN_MsgChoice MMC_LMM_GSM_SYS_INFO_IND_STRU*/
    ID_MMC_LMM_BG_PLMN_SEARCH_REQ       = (PS_MSG_ID_MMC_TO_LMM_BASE+0x17),     /* _H2ASN_MsgChoice MMC_LMM_BG_PLMN_SEARCH_REQ_STRU*/
    ID_MMC_LMM_STOP_BG_PLMN_SEARCH_REQ  = (PS_MSG_ID_MMC_TO_LMM_BASE+0x18),     /* _H2ASN_MsgChoice MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU*/
    ID_MMC_LMM_UTRAN_MODE_REQ           = (PS_MSG_ID_MMC_TO_LMM_BASE+0x19),     /* _H2ASN_MsgChoice MMC_LMM_UTRAN_MODE_REQ_STRU */

    ID_MMC_LMM_SUSPEND_REL_REQ          = (PS_MSG_ID_MMC_TO_LMM_BASE+0x1A),     /* _H2ASN_MsgChoice MMC_LMM_SUSPEND_REL_REQ_STRU */
    ID_MMC_LMM_LTE_SYS_INFO_IND         = (PS_MSG_ID_MMC_TO_LMM_BASE+0x1B),     /* _H2ASN_MsgChoice MMC_LMM_LTE_SYS_INFO_IND_STRU */
    /*ID_SM_ESM_PDP_CONTEXT_INFO_IND                 ,*/       /* _H2ASN_MsgChoice SM_ESM_PDP_CONTEXT_INFO_IND_STRU */

    ID_MMC_LMM_OTHER_MODEM_INFO_NOTIFY  = (PS_MSG_ID_MMC_TO_LMM_BASE+0x1C),     /* _H2ASN_MsgChoice MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU*/

    ID_MMC_LMM_IMS_VOICE_CAP_CHANGE_NOTIFY = (PS_MSG_ID_MMC_TO_LMM_BASE+0x1D),     /* _H2ASN_MsgChoice MMC_LMM_IMS_VOICE_CAP_CHANGE_NOTIFY_STRU*/

    ID_MMC_LMM_BEGIN_SESSION_NOTIFY       = (PS_MSG_ID_MMC_TO_LMM_BASE+0x1E),     /* _H2ASN_MsgChoice MMC_LMM_BEGIN_SESSION_NOTIFY_STRU*/
    ID_MMC_LMM_END_SESSION_NOTIFY         = (PS_MSG_ID_MMC_TO_LMM_BASE+0x1F),     /* _H2ASN_MsgChoice MMC_LMM_END_SESSION_NOTIFY_STRU*/
    ID_MMC_LMM_CELL_SIGN_REPORT_NOTIFY  = (PS_MSG_ID_MMC_TO_LMM_BASE+0x20),     /* _H2ASN_MsgChoice MMC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU*/

    ID_MMC_LMM_VOICE_DOMAIN_CHANGE_IND  = (PS_MSG_ID_MMC_TO_LMM_BASE+0x21),     /* _H2ASN_MsgChoice MMC_LMM_VOICE_DOMAIN_CHANGE_IND_STRU*/
    ID_MMC_LMM_CS_CONN_STATUS_NOTIFY    = (PS_MSG_ID_MMC_TO_LMM_BASE+0x23),     /* _H2ASN_MsgChoice MMC_LMM_CS_CONN_STATUS_NOTIFY_STRU*/

    ID_MMC_LMM_BG_SEARCH_HRPD_REQ       = (PS_MSG_ID_MMC_TO_LMM_BASE+0X24),     /* _H2ASN_MsgChoice MMC_LMM_BG_SEARCH_HRPD_REQ_STRU */
    ID_MMC_LMM_STOP_BG_SEARCH_HRPD_REQ  = (PS_MSG_ID_MMC_TO_LMM_BASE+0x25),     /* _H2ASN_MsgChoice MMC_LMM_STOP_BG_SEARCH_HRPD_REQ_STRU */

    ID_MMC_LMM_CSG_WHITE_LIST_NOTIFY    = (PS_MSG_ID_MMC_TO_LMM_BASE+0X26),     /* _H2ASN_MsgChoice MMC_LMM_CSG_WHITE_LIST_NOTIFY_STRU */
    ID_MMC_LMM_CSG_LIST_SEARCH_REQ      = (PS_MSG_ID_MMC_TO_LMM_BASE+0X27),     /* _H2ASN_MsgChoice MMC_LMM_CSG_LIST_SEARCH_REQ_STRU */
    ID_MMC_LMM_CSG_BG_SEARCH_REQ        = (PS_MSG_ID_MMC_TO_LMM_BASE+0X28),     /* _H2ASN_MsgChoice MMC_LMM_CSG_BG_SEARCH_REQ_STRU */

    ID_MMC_LMM_CL_INTERSYS_START_NTF    = (PS_MSG_ID_MMC_TO_LMM_BASE+0X29),     /* _H2ASN_MsgChoice MMC_LMM_CL_INTERSYS_START_NTF_STRU */

    /* LMM发送给MMC的消息原语*/
    ID_LMM_MMC_START_CNF                = (PS_MSG_ID_LMM_TO_MMC_BASE+0x01),     /* _H2ASN_MsgChoice LMM_MMC_START_CNF_STRU */
    ID_LMM_MMC_STOP_CNF                 = (PS_MSG_ID_LMM_TO_MMC_BASE+0x02),     /* _H2ASN_MsgChoice LMM_MMC_STOP_CNF_STRU */
    ID_LMM_MMC_PLMN_SRCH_CNF            = (PS_MSG_ID_LMM_TO_MMC_BASE+0x03),     /* _H2ASN_MsgChoice LMM_MMC_PLMN_SRCH_CNF_STRU */
    ID_LMM_MMC_STOP_PLMN_SRCH_CNF       = (PS_MSG_ID_LMM_TO_MMC_BASE+0x04),     /* _H2ASN_MsgChoice LMM_MMC_STOP_PLMN_SRCH_CNF_STRU */
    ID_LMM_MMC_AREA_LOST_IND            = (PS_MSG_ID_LMM_TO_MMC_BASE+0x05),     /* _H2ASN_MsgChoice LMM_MMC_AREA_LOST_IND_STRU */
    ID_LMM_MMC_SYS_INFO_IND             = (PS_MSG_ID_LMM_TO_MMC_BASE+0x06),     /* _H2ASN_MsgChoice LMM_MMC_SYS_INFO_IND_STRU */
    ID_LMM_MMC_EMM_INFO_IND             = (PS_MSG_ID_LMM_TO_MMC_BASE+0x07),     /* _H2ASN_MsgChoice LMM_MMC_EMM_INFO_IND_STRU */
    ID_LMM_MMC_ERR_IND                  = (PS_MSG_ID_LMM_TO_MMC_BASE+0x08),     /* _H2ASN_MsgChoice LMM_MMC_ERR_IND_STRU */
    ID_LMM_MMC_EPS_SERVICE_IND          = (PS_MSG_ID_LMM_TO_MMC_BASE+0x09),     /* _H2ASN_MsgChoice LMM_MMC_EPS_SERVICE_IND_STRU */
    ID_LMM_MMC_SUSPEND_IND              = (PS_MSG_ID_LMM_TO_MMC_BASE+0x0A),     /* _H2ASN_MsgChoice LMM_MMC_SUSPEND_IND_STRU */
    ID_LMM_MMC_SUSPEND_CNF              = (PS_MSG_ID_LMM_TO_MMC_BASE+0x0B),     /* _H2ASN_MsgChoice LMM_MMC_SUSPEND_CNF_STRU */
    ID_LMM_MMC_RESUME_IND               = (PS_MSG_ID_LMM_TO_MMC_BASE+0x0C),     /* _H2ASN_MsgChoice LMM_MMC_RESUME_IND_STRU */
    ID_LMM_MMC_STATUS_IND               = (PS_MSG_ID_LMM_TO_MMC_BASE+0x0D),     /* _H2ASN_MsgChoice LMM_MMC_STATUS_IND_STRU */
    ID_LMM_MMC_SYS_CFG_CNF              = (PS_MSG_ID_LMM_TO_MMC_BASE+0x0E),     /* _H2ASN_MsgChoice LMM_MMC_SYS_CFG_CNF_STRU */
    ID_LMM_MMC_USIM_STATUS_CNF          = (PS_MSG_ID_LMM_TO_MMC_BASE+0x0F),     /* _H2ASN_MsgChoice LMM_MMC_USIM_STATUS_CNF_STRU */
    ID_LMM_MMC_ATTACH_CNF               = (PS_MSG_ID_LMM_TO_MMC_BASE+0x10),     /* _H2ASN_MsgChoice LMM_MMC_ATTACH_CNF_STRU */
    ID_LMM_MMC_ATTACH_IND               = (PS_MSG_ID_LMM_TO_MMC_BASE+0x11),     /* _H2ASN_MsgChoice LMM_MMC_ATTACH_IND_STRU */
    ID_LMM_MMC_DETACH_CNF               = (PS_MSG_ID_LMM_TO_MMC_BASE+0x12),     /* _H2ASN_MsgChoice LMM_MMC_DETACH_CNF_STRU */
    ID_LMM_MMC_DETACH_IND               = (PS_MSG_ID_LMM_TO_MMC_BASE+0x13),     /* _H2ASN_MsgChoice LMM_MMC_DETACH_IND_STRU */
    ID_LMM_MMC_TAU_RESULT_IND           = (PS_MSG_ID_LMM_TO_MMC_BASE+0x14),     /* _H2ASN_MsgChoice LMM_MMC_TAU_RESULT_IND_STRU */
    ID_LMM_MMC_SERVICE_RESULT_IND       = (PS_MSG_ID_LMM_TO_MMC_BASE+0x15),     /* _H2ASN_MsgChoice LMM_MMC_SERVICE_RESULT_IND_STRU */
    ID_LMM_MMC_TIN_TYPE_IND             = (PS_MSG_ID_LMM_TO_MMC_BASE+0x16),     /* _H2ASN_MsgChoice LMM_MMC_TIN_TYPE_IND_STRU */

    /* 删除LTE上报服务状态和注册状态的接口,  ID_LMM_MMC_SERVICE_STATUS_IND/ID_LMM_MMC_REGISTER_STATUS_IND*/

    ID_LMM_MMC_TIMER_STATE_NOTIFY       = (PS_MSG_ID_LMM_TO_MMC_BASE+0x19),     /* _H2ASN_MsgChoice LMM_MMC_TIMER_STATE_NOTIFY_STRU */
    ID_LMM_MMC_BG_PLMN_SEARCH_CNF       = (PS_MSG_ID_LMM_TO_MMC_BASE+0x1A),     /* _H2ASN_MsgChoice LMM_MMC_BG_PLMN_SEARCH_CNF_STRU*/
    ID_LMM_MMC_STOP_BG_PLMN_SEARCH_CNF  = (PS_MSG_ID_LMM_TO_MMC_BASE+0x1B),     /* _H2ASN_MsgChoice LMM_MMC_STOP_BG_PLMN_SEARCH_CNF_STRU*/
    ID_LMM_MMC_NOT_CAMP_ON_IND          = (PS_MSG_ID_LMM_TO_MMC_BASE+0x1C),     /* _H2ASN_MsgChoice LMM_MMC_NOT_CAMP_ON_IND_STRU*/
    ID_LMM_MMC_UTRAN_MODE_CNF           = (PS_MSG_ID_LMM_TO_MMC_BASE+0x1D),     /* _H2ASN_MsgChoice LMM_MMC_UTRAN_MODE_CNF_STRU*/
    ID_LMM_MMC_SUSPEND_REL_CNF          = (PS_MSG_ID_LMM_TO_MMC_BASE+0x1E),     /* _H2ASN_MsgChoice LMM_MMC_SUSPEND_REL_CNF_STRU*/
    /*ID_ESM_SM_EPS_BEARER_INFO_IND                   ,    */   /* _H2ASN_MsgChoice ESM_SM_EPS_BEARER_INFO_IND_STRU */
    ID_LMM_MMC_EMC_PDP_STATUS_NOTIFY    = (PS_MSG_ID_LMM_TO_MMC_BASE+0x1F),     /* _H2ASN_MsgChoice LMM_MMC_EMC_PDP_STATUS_NOTIFY_STRU*/
    ID_LMM_MMC_SUSPEND_INFO_CHANGE_NOTIFY  = (PS_MSG_ID_LMM_TO_MMC_BASE+0x20),      /* _H2ASN_MsgChoice LMM_MMC_SUSPEND_INFO_CHANGE_NOTIFY_STRU */
    ID_LMM_MMC_INFO_CHANGE_NOTIFY        = (PS_MSG_ID_LMM_TO_MMC_BASE+0x21),    /* _H2ASN_MsgChoice LMM_MMC_INFO_CHANGE_NOTIFY_STRU*/
    ID_LMM_MMC_SIM_AUTH_FAIL_IND           =  (PS_MSG_ID_LMM_TO_MMC_BASE+0x22),  /* _H2ASN_MsgChoice LMM_MMC_SIM_AUTH_FAIL_IND_STRU */
    ID_LMM_MMC_SEARCHED_PLMN_INFO_IND    = (PS_MSG_ID_LMM_TO_MMC_BASE+0x23),  /* _H2ASN_MsgChoice LMM_MMC_SEARCHED_PLMN_INFO_IND_STRU*/

    ID_LMM_MMC_CELL_SIGN_REPORT_IND     = (PS_MSG_ID_LMM_TO_MMC_BASE+0x24),     /* _H2ASN_MsgChoice LMM_MMC_CELL_SIGN_REPORT_IND_STRU */

    ID_LMM_MMC_T3402_LEN_NOTIFY         = (PS_MSG_ID_LMM_TO_MMC_BASE+0x25),  /* _H2ASN_MsgChoice LMM_MMC_T3402_LEN_NOTIFY_STRU */

    ID_LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY   = (PS_MSG_ID_LMM_TO_MMC_BASE+0x26),   /* _H2ASN_MsgChoice LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY_STRU*/

    ID_LMM_MMC_BG_SEARCH_HRPD_CNF       = (PS_MSG_ID_LMM_TO_MMC_BASE+0x27),     /* _H2ASN_MsgChoice LMM_MMC_BG_SEARCH_HRPD_CNF_STRU */
    ID_LMM_MMC_STOP_BG_SEARCH_HRPD_CNF  = (PS_MSG_ID_LMM_TO_MMC_BASE+0x28),     /* _H2ASN_MsgChoice LMM_MMC_STOP_BG_SEARCH_HRPD_CNF_STRU */

    ID_LMM_MMC_CSG_LIST_SEARCH_CNF     = (PS_MSG_ID_LMM_TO_MMC_BASE+0x29),      /* _H2ASN_MsgChoice LMM_MMC_CSG_LIST_SEARCH_CNF_STRU */
    ID_LMM_MMC_CSG_BG_SEARCH_CNF       = (PS_MSG_ID_LMM_TO_MMC_BASE+0x2A),      /* _H2ASN_MsgChoice LMM_MMC_CSG_BG_SEARCH_CNF_STRU */
    ID_LMM_MMC_CSG_ID_HOME_NODEB_NAME_IND = (PS_MSG_ID_LMM_TO_MMC_BASE+0x2B),    /* _H2ASN_MsgChoice LMM_MMC_CSG_ID_HOME_NODEB_NAME_IND_STRU */

    ID_MMC_LMM_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 MMC_LMM_MSG_ID_ENUM_UINT32;

/*****************************************************************************
枚举名  : MMC_LMM_CELL_SEL_TYPE_ENUM_UINT32
协议格式:
ASN.1描述:
枚举说明:小区控制原语枚举类型
*****************************************************************************/
enum MMC_LMM_CELL_SEL_TYPE_ENUM
{
    MMC_LMM_RESEL_SUITABLE              = 0,

    MMC_LMM_CELL_SEL_BUTT
};
typedef VOS_UINT32  MMC_LMM_CELL_SEL_TYPE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : MMC_LMM_DISABLE_LTE_REASON_ENUM
 枚举说明  : Disable Lte原因枚举定义
*****************************************************************************/
enum MMC_LMM_DISABLE_LTE_REASON_ENUM
{
    MMC_LMM_DISABLE_LTE_REASON_PS_DETACH                            =0,
    MMC_LMM_DISABLE_LTE_REASON_PS_USIM_INVALID                      =1,
    MMC_LMM_DISABLE_LTE_REASON_LTE_ROAMING_NOT_ALLOWED              =2,
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-18, begin */
    MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE              =3,
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-18, end */
    MMC_LMM_DISABLE_LTE_REASON_EMERGENCY_CALL                       =4,
    MMC_LMM_DISABLE_LTE_REASON_SIM_CARD_SWITCH_ON                   =5,
    MMC_LMM_DISABLE_LTE_REASON_IMSI_IN_FORBIDDEN_LIST               =6,
    MMC_LMM_DISABLE_LTE_REASON_LTE_REJ_CAUSE_14                     =7,
    MMC_LMM_DISABLE_LTE_REASON_LMM_NOTIFY_EUTRAN_NOT_ALLOW          =8,
    MMC_LMM_DISABLE_LTE_REASON_BUTT
};
typedef VOS_UINT32  MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32;

/*****************************************************************************
 枚举名: MMC_LMM_TRANSCEIVER_TYPE_ENUM
 协议格式:
 ASN.1描述:
 枚举说明:待机类型取值
*****************************************************************************/
enum MMC_LMM_TRANSCEIVER_TYPE_ENUM
{
    MMC_LMM_TRANSCEIVER_TYPE_SINGLE     = 0,                                    /* 多模单待 */
    MMC_LMM_TRANSCEIVER_TYPE_DUAL          ,                                    /* 多模双待,L和G ,L和W */
    MMC_LMM_TRANSCEIVER_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_TRANSCEIVER_TYPE_ENUM_UINT32;


/*****************************************************************************
 枚举名: MMC_LMM_RESULT_ID_ENUM
 协议格式:
 ASN.1描述:
 枚举说明:
*****************************************************************************/
enum    MMC_LMM_RESULT_ID_ENUM
{
    MMC_LMM_SUCC                        = 0x00000000,
    MMC_LMM_FAIL                        ,
    MMC_LMM_ERR_ID_BUTT
};
typedef VOS_UINT32 MMC_LMM_RESULT_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名: MMC_LMM_PLMN_SRCH_TYPE_ENUM
 协议格式:
 ASN.1描述:
 枚举说明:
*****************************************************************************/
enum MMC_LMM_PLMN_SRCH_TYPE_ENUM
{
    MMC_LMM_PLMN_SRCH_SPEC              = 0,                /* 指定的PLMN的搜索 */
    MMC_LMM_PLMN_SRCH_LIST              = 1,                /* PLMN列表的搜索   */
    MMC_LMM_PLMN_SRCH_ANY               = 2,                /* any cell 搜索 */
    MMC_LMM_PLMN_SRCH_USER_SPEC         = 3,                /* user指定搜网*/
    MMC_LMM_PLMN_SRCH_FAST_SPEC         = 4,                /* 快速指定的PLMN的搜索 */

    MMC_LMM_PLMN_SRCH_NCELL_SPEC        = 5,               /* SVLTE特性开启时根据modem1 g上报的L邻区频点信息搜网类型 */

    /*modified by z00234330 for 搜网优化,2015-02-05,begin*/
    MMC_LMM_PLMN_SRCH_HISTORY           = 6,               /*历史信息搜索*/
    MMC_LMM_PLMN_SRCH_GET_GEO           = 7,               /*获取地理信息*/
    /*modified by z00234330 for 搜网优化,2015-02-05,begin*/

    /*搜索预置band，接入层不需要进行全band搜索，仅需要搜索预置band,但如果预置band
    和硬件支持的band完全重叠，接入层需要在搜网结果中将进行过全band扫频的标志位置位*/
    MMC_LMM_PLMN_SRCH_PREF_BAND         = 8,
	
    MMC_LMM_PLMN_SRCH_USER_CSG_SPEC     = 9,               /* 用户手动CSG搜索 */
    MMC_LMM_PLMN_SRCH_FAST_CSG_SPEC     = 10,               /* 快速CSG指定的PLMN的搜索 */

    MMC_LMM_PLMN_SRCH_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_PLMN_SRCH_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名: MMC_LMM_PLMN_SRCH_RLT_ENUM
 协议格式:
 ASN.1描述:
 枚举说明:
*****************************************************************************/
enum MMC_LMM_PLMN_SRCH_RLT_ENUM
{
    MMC_LMM_PLMN_SRCH_RLT_SPEC_SUCC     = 0,                /* 指定的PLMN ID 搜索成功 */
    MMC_LMM_PLMN_SRCH_RLT_LIST_SUCC     = 1,                /* PLMN List搜索成功      */
    MMC_LMM_PLMN_SRCH_RLT_SPEC_FAIL     = 2,                /* 指定PLMN ID搜索失败    */
    MMC_LMM_PLMN_SRCH_RLT_LIST_REJ      = 3,                /* 驻留态下列表搜网被非出服务区流程打断 */

    MMC_LMM_PLMN_SRCH_RLT_SPEC_NO_RF    = 4,
    MMC_LMM_PLMN_SRCH_RLT_LIST_NO_RF    = 5,

    /*modified by z00234330 for 搜网优化,2015-02-05,begin*/
    MMC_LMM_PLMN_SRCH_RLT_HISTORY_FAIL  = 6,
    MMC_LMM_PLMN_SRCH_RLT_HISTORY_SUCC  = 7,
    MMC_LMM_PLMN_SRCH_RLT_HISTORY_NO_RF = 8,

    MMC_LMM_PLMN_SRCH_RLT_GET_GEO_FAIL  = 9,
    MMC_LMM_PLMN_SRCH_RLT_GET_GEO_SUCC  = 10,
    MMC_LMM_PLMN_SRCH_RLT_GET_GEO_NO_RF = 11,
    /*modified by z00234330 for 搜网优化,2015-02-05,end*/

    MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_FAIL    = 12,
    MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_SUCC    = 13,
    MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_NO_RF   = 14,
	
    MMC_LMM_PLMN_SRCH_RLT_SPEC_CSG_SUCC = 15,
    MMC_LMM_PLMN_SRCH_RLT_SPEC_CSG_FAIL = 16,
    MMC_LMM_PLMN_SRCH_RLT_SPEC_CSG_NO_RF = 17,

    MMC_LMM_PLMN_SRCH_RLT_BUTT
};
typedef VOS_UINT32  MMC_LMM_PLMN_SRCH_RLT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MMC_LMM_BG_SRCH_RLT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : BG搜索结果
*****************************************************************************/
enum MMC_LMM_BG_SRCH_RLT_ENUM
{
    MMC_LMM_BG_SRCH_RLT_SUCCESS            = 0,                /* 指定的PLMN搜索成功 */
    MMC_LMM_BG_SRCH_RLT_FAIL               = 1,                /* 实际发起了搜网，但是搜索失败 */
    MMC_LMM_BG_SRCH_RLT_ABORT              = 2,                /* 没有发起搜网，因为当前状态不允许，搜索被终止 */
    MMC_LMM_BG_SRCH_RLT_BUTT
};
typedef VOS_UINT32  MMC_LMM_BG_SRCH_RLT_ENUM_UINT32;


/*****************************************************************************
 枚举名: MMC_LMM_FFT_SCAN_TYPE_ENUM_UINT8
 协议格式:
 ASN.1描述:
 枚举说明:
*****************************************************************************/
enum MMC_LMM_FFT_SCAN_TYPE_ENUM
{
    MMC_LMM_FFT_SCAN_TYPE_NONE     = 0,                 /* 不从COMM SRCH获取FFT扫频之后的频点 */
    MMC_LMM_FFT_SCAN_TYPE_LOW      = 1,                 /* 从COMM SRCH获取FFT扫频之后满足可驻留门限的频点 */
    MMC_LMM_FFT_SCAN_TYPE_HIGH     = 2,                 /* 从COMM SRCH获取FFT扫频之后满足高质量门限的频点 */
    MMC_LMM_FFT_SCAN_TYPE_BUTT
};
typedef VOS_UINT8  MMC_LMM_FFT_SCAN_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名: MMC_LMM_PLMN_SEARCH_SCENE_ENUM
 协议格式:
 ASN.1描述:
 枚举说明: MMC指定的PLMN搜网场景
*****************************************************************************/
enum MMC_LMM_PLMN_SEARCH_SCENE_ENUM
{
    MMC_LMM_PLMN_SEARCH_SCENE_NORMAL            = 0,        /* 普通的正常搜网，无特殊要求 */
    MMC_LMM_PLMN_SEARCH_SCENE_VIA_CL_BG_SEARCH  = 1,        /* VIA CL多模形态下的带门限要求的背景搜网，目前仅用于指定背景搜 */

    MMC_LMM_PLMN_SEARCH_SCENE_BUTT
};
typedef VOS_UINT8 MMC_LMM_PLMN_SEARCH_SCENE_ENUM_UINT8;



/*****************************************************************************
 枚举名: MMC_LMM_CELL_STATUS_ENUM
 协议格式:
 ASN.1描述:
 枚举说明:
*****************************************************************************/
enum MMC_LMM_CELL_STATUS_ENUM
{
    MMC_LMM_CELL_STATUS_NORMAL          = 0,               /* 正常驻留    */
    MMC_LMM_CELL_STATUS_ANYCELL         = 1,               /* AnyCell驻留 */
    MMC_LMM_CELL_STATUS_BUTT
};
typedef VOS_UINT32 MMC_LMM_CELL_STATUS_ENUM_UINT32;


/*****************************************************************************
 枚举名: MMC_LMM_ACTION_TYPE_ENUM
 协议格式:
 ASN.1描述:
 枚举说明:
*****************************************************************************/
enum MMC_LMM_ACTION_TYPE_ENUM
{
    MMC_LMM_ACTION_ATTACH              = 0x00000000,
    MMC_LMM_ACTION_RAU                  ,
    MMC_LMM_ACTION_LAU                  ,
    MMC_LMM_ACTION_PS_SERVICE_REQ       ,

    MMC_LMM_ACTION_MT_DETACH            ,
    MMC_LMM_ACTION_LOCAL_DETACH         ,
    MMC_LMM_ACTION_MO_DETACH            ,

    MMC_LMM_ACTION_CM_REQ               ,
    MMC_LMM_ACTION_MM_ABORT             ,
    MMC_LMM_ACTION_PERIODC_RAU          ,
    MMC_LMM_ACTION_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_ACTION_TYPE_ENUM_UINT32;


/*****************************************************************************
 枚举名: NAS_LMM_CN_CAUSE_ENUM
 枚举说明:24301 9.9.3.9 EMM cause
*****************************************************************************/
enum    NAS_LMM_CN_CAUSE_ENUM
{
    NAS_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS                                                                  = 0x00000002,    /* IMSI unknown in HSS          */
    NAS_EMM_CAUSE_ILLEGAL_UE                                                                                          = 0x00000003,    /* Illegal UE          */
    NAS_EMM_CAUSE_IMSI_UNKNOWN_IN_VLR                                   = 0x00000004, /*IMSI unknown in VLR*/
    NAS_EMM_CAUSE_IMEI_NOT_ACCEPTED                                     = 0x00000005, /*IMEI not accepted*/
    NAS_EMM_CAUSE_ILLEGAL_ME                                                                                          = 0x00000006,    /* Illegal ME              */
    NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW                                                                  = 0x00000007,    /* EPS services not allowed                */
    NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW                    = 0x00000008,    /* EPS services and non-EPSservices not allowed                     */
    NAS_EMM_CAUSE_MS_ID_CANNOT_BE_DERIVED_BY_NW                                       = 0x00000009,    /* MS identity cannot be derived by the network             */
    NAS_EMM_CAUSE_EPS_IMPLICITLY_DETACHED                                                          = 0x0000000a,    /* Implicitly detached  */
    NAS_EMM_CAUSE_PLMN_NOT_ALLOW                                                                             = 0x0000000b,    /* PLMN not allowed                         */
    NAS_EMM_CAUSE_TA_NOT_ALLOW                                                                                   = 0x0000000c,    /* Tracking  area not allowed                */
    NAS_EMM_CAUSE_ROAM_NOT_ALLOW                                                                            = 0x0000000d,     /* Roaming not allowed in this tracking area                      */
    NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN                                              = 0x0000000e,    /* EPS services not allowed in this PLMN   */
    NAS_EMM_CAUSE_NO_SUITABL_CELL                                                                             = 0x0000000f,     /* No Suitable Cells In Location Area       */
    NAS_EMM_CAUSE_MSC_TEMPORARILY_NOT_REACHABLE                                                              = 0x00000010,    /* MSC temporarily not reachable     */
    NAS_EMM_CAUSE_NETWORKFAILURE                                                                             = 0x00000011,    /* Network failure     */
    NAS_EMM_CAUSE_CS_DOMAIN_NOT_AVAILABLE                                                        = 0x00000012,    /* CS domain not available       */
    NAS_EMM_CAUSE_ESM_FAILURE                                                                                       = 0x00000013,    /* ESM failure       */
    NAS_EMM_CAUSE_CONGESTION                                                                                        = 0x00000016,    /* Congestion     */
    NAS_EMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG                                             = 0x00000019,    /*  Not authorized for this CSG        */
    NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN                           = 0x00000023, /*Requested service option not authorized in this PLMN*/
    NAS_EMM_CAUSE_CS_DOMAIN_TEMP_NOT_AVAILABLE                                          = 0x00000027,    /*  CS domain temporarily not available       */
    NAS_EMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED                                = 0x00000028,    /*  No EPS bearer context activated        */
    NAS_EMM_CAUSE_SERVER_NETWORK_FAILURE                                         = 0x0000002a,    /*  Server Network Failure  */
    NAS_EMM_CAUSE_SEMANTICALLY_INCORRECT_MSG                                              = 0x0000005f,    /* Semantically incorrect message    */
    NAS_EMM_CAUSE_INVALID_MANDATORY_INFORMATION                                         = 0x00000060,    /* Invalid mandatory information    */
    NAS_EMM_CAUSE_MSG_TYPE_NON_EXIST_OR_IMPLEMENT                                  = 0x00000061,    /* Message type non-existent or not implemented    */
    NAS_EMM_CAUSE_INFO_ELEMENT_NON_EXIST_OR_NOT_IMPLEMENT              = 0x00000063,    /*  Information element non-existent or not implemented    */
    NAS_EMM_CAUSE_MSG_NOT_COMPATIBLE_WITH_PROTOCOL_STATE              = 0x00000065,    /*Message not compatible with protocol state    */
    NAS_EMM_CAUSE_BUTT
};

typedef VOS_UINT8 NAS_LMM_CN_CAUSE_ENUM_UINT8;


/*****************************************************************************
 枚举名: MMC_LMM_DOMAIN_ENUM
 协议格式:
 ASN.1描述:
 枚举说明:   ATTACH, RAU, DETACH的 发起和结果类型   详见: 24301  9.9.3.10 / 24008  10.5.5.1
*****************************************************************************/
enum MMC_LMM_DOMAIN_ENUM
{
    MMC_LMM_PS_ONLY                     = 0x00000000,                           /*当前RAU/Attach类型为PS only  */
    MMC_LMM_IMSI_ONLY,                                                          /*当前 类型为CS only  */
    MMC_LMM_COMBINED_PS_IMSI ,                                                  /*当前 类型为联合处理  */

    MMC_LMM_DOMAIN_BUTT
};
typedef VOS_UINT32 MMC_LMM_DOMAIN_ENUM_UINT32;



/*****************************************************************************
 结构名称:
 协议表格:
 ASN.1 描述:
 结构说明:   CN_ACCEPT, CN_REJECT：各流程网络响应的结果；
*****************************************************************************/
enum MMC_LMM_RSLT_TYPE_ENUM
{
    MMC_LMM_RSLT_TYPE_SUCCESS                     = 0,
    MMC_LMM_RSLT_TYPE_FAILURE,                                                  /*失败包含网侧拒绝和无响应*/
    MMC_LMM_RSLT_TYPE_CN_REJ,
    MMC_LMM_RSLT_TYPE_AUTH_REJ,                                                 /* 鉴权被拒 */
    MMC_LMM_RSLT_TYPE_ACCESS_BARRED,
    MMC_LMM_RSLT_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_RSLT_TYPE_ENUM_UINT32;


/*****************************************************************************
 结构名称:MMC_LMM_SYS_CHNG_TYPE_ENUM
 协议表格:
 ASN.1 描述:
 结构说明:LMM通知MMC挂起的方向
*****************************************************************************/
enum    MMC_LMM_SYS_CHNG_DIR_ENUM
{

    MMC_LMM_SYS_CHNG_DIR_L2W            = 0x00000000,
    MMC_LMM_SYS_CHNG_DIR_L2G,
    MMC_LMM_SYS_CHNG_DIR_G2L,
    MMC_LMM_SYS_CHNG_DIR_W2L,

    MMC_LMM_SYS_CHNG_DIR_L2C,

    MMC_LMM_SYS_CHNG_DIR_BUTT
};
typedef VOS_UINT32 MMC_LMM_SYS_CHNG_DIR_ENUM_UINT32;


/*****************************************************************************
 结构名称:MMC_LMM_SYS_CHNG_TYPE_ENUM
 协议表格:
 ASN.1 描述:
 结构说明:系统变更的类型
*****************************************************************************/
enum MMC_LMM_SYS_CHNG_TYPE_ENUM
{
    MMC_LMM_SUS_TYPE_RSL                = 0x00000000,                           /* 重选 */
    MMC_LMM_SUS_TYPE_HO ,                                                       /* HandOver */
    MMC_LMM_SUS_TYPE_CCO ,                                                      /* Cell Change Order */
    MMC_LMM_SUS_TYPE_REDIR ,                                                    /* 网侧重定向 */
    MMC_LMM_SUS_TYPE_CCO_REVERSE ,      /* G->L的CCO失败，向G回退时，LMM向MMC指示此类型的挂起 */

    MMC_LMM_SUS_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_SYS_CHNG_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LMM_MMC_CONN_STATE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LMM连接类型枚举
*****************************************************************************/
enum MMC_LMM_CONN_STATE_ENUM
{
    MMC_LMM_CONN_IDLE                   = 0x00000000,       /* 无连接存在 */
    MMC_LMM_CONN_ESTING ,                                   /* 建链过程中 */
    MMC_LMM_CONNECTED_SIG ,                                 /* 只有信令连接 */
    MMC_LMM_CONNECTED_DATA,                                 /* 有数传连接 */

    MMC_LMM_CONN_BUTT
};
typedef VOS_UINT32 MMC_LMM_CONN_STATE_ENUM_UINT32;



/*****************************************************************************
 枚举名    : MMC_LMM_STATUS_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :状态报告的类型
*****************************************************************************/
enum MMC_LMM_STATUS_TYPE_ENUM
{

    MMC_LMM_STATUS_TYPE_CONN_STATE      = 0x00000000,                           /* 指示连接状态 */
    MMC_LMM_STATUS_TYPE_T3412_EXP,                                              /* T3412超时 */
    MMC_LMM_STATUS_TYPE_T3423_EXP,                                              /* T3423超时 */
    MMC_LMM_STATUS_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_STATUS_TYPE_ENUM_UINT32;

/* 频带号，取值范围从1至40，分别对应 36.101  5.5 的 band 取值 */
typedef VOS_UINT32 MMC_LMM_LTE_BAND_UINT32;

/*****************************************************************************
 枚举名    : SMS_LMM_REG_STATE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum MMC_LMM_USIM_STATUS_ENUM
{
    MMC_LMM_USIM_VALID                  = 0x00000000,                           /* 有效卡 */
    MMC_LMM_USIM_INVALID,                                                       /* 无卡或卡无效 */

    MMC_LMM_USIM_STATUS_BUTT
};
typedef VOS_UINT32 MMC_LMM_USIM_STATUS_ENUM_UINT32;


/*****************************************************************************
 枚举名称: NAS_GUMM_INFO_TYPE_ENUM_UINT32
 协议表格:
 ASN.1 描述:
 枚举说明:MMC供给LTE模的信息，包括GU模的参数，和GUL公用的参数
*****************************************************************************/
enum NAS_GUMM_INFO_TYPE_ENUM
{
    NAS_GUMM_PTMSI                      = 0x00000000,
    NAS_GUMM_PTMSI_SIGNATURE,
    NAS_GUMM_LAI,
    NAS_GUMM_RAI,
    NAS_GUMM_UMTS_SECU_PARA,
    NAS_GUMM_TMSI_STATUS,

    NAS_GUMM_INFO_TYPE_BUTT
};
typedef VOS_UINT32 NAS_GUMM_INFO_TYPE_ENUM_UINT32;

/****************************************************************************
 枚举名称: NAS_LMM_INFO_TYPE_ENUM_UINT32
 协议表格:
 ASN.1 描述:
 枚举说明:   LTE模提供给GU模的信息枚举
*****************************************************************************/
enum NAS_LMM_INFO_TYPE_ENUM
{
    NAS_LMM_GUTI                        = 0x00000000,
    NAS_LMM_RPLMN,
    NAS_LMM_FORB_TAI_ROAM_LIST,
    NAS_LMM_FORB_TAI_RPOS_LIST,

    NAS_LMM_CS_DOMAIN_UNAVAILABLE_PLMN_LIST,

    NAS_LMM_INFO_TYPE_BUTT
};
typedef VOS_UINT32 NAS_LMM_INFO_TYPE_ENUM_UINT32;


/****************************************************************************
 枚举名称: MMC_LMM_EPS_UPDATE_STATUS_ENUM
 协议表格:
 ASN.1 描述:
 枚举说明:   LTE的EU值枚举
*****************************************************************************/
enum MMC_LMM_EPS_UPDATE_STATUS_ENUM
{
    MMC_LMM_EPS_UPDATE_STATUS_UPDATED               = 0x00,             /* UPDATED */
    MMC_LMM_EPS_UPDATE_STATUS_NOT_UPDATED           = 0x01,             /* NOT UPDATED */
    MMC_LMM_EPS_UPDATE_STATUS_ROAMING_NOT_ALLOWED   = 0x02,             /* ROAMING NOT ALLOWED */

    MMC_LMM_EPS_UPDATE_STATUS_BUTT
};
typedef VOS_UINT8  MMC_LMM_EPS_UPDATE_STATUS_ENUM_UINT8;

/****************************************************************************
 枚举名称: MMC_LMM_TAI_IN_LIST_FLAG_ENUM
 协议表格:
 ASN.1 描述:
 枚举说明: TAI是否在TAI LIST中标识枚举
*****************************************************************************/
enum MMC_LMM_TAI_IN_LIST_FLAG_ENUM
{
    MMC_LMM_TAI_IN_TAI_LIST             = 0x00,                         /* TAI IN TAI LIST */
    MMC_LMM_TAI_NOT_IN_TAI_LIST         = 0x01,                         /* TAI NOT IN TAI LIST */

    MMC_LMM_TAI_IN_LIST_FLAG_BUTT
};
typedef VOS_UINT8 MMC_LMM_TAI_IN_LIST_FLAG_ENUM_UINT8;



/*****************************************************************************
 枚举名称: MMC_LMM_TMSI_STATUS_TYPE_ENUM_UINT32
 协议表格:
 ASN.1 描述:
 枚举说明:GU提供给LTE模的信息枚举
*****************************************************************************/
enum MMC_LMM_TMSI_STATUS_TYPE_ENUM
{
    MMC_LMM_TMSI_STATUS_VALID           = 0x00000000,
    MMC_LMM_TMSI_STATUS_INVALID        ,

    MMC_LMM_TMSI_STATUS_BUTT
};
typedef VOS_UINT32 MMC_LMM_TMSI_STATUS_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名称: MMC_LMM_INFO_TYPE_ENUM_UINT32
 协议表格:
 ASN.1 描述:
 枚举说明:MMC模提供给GU或LTE模的信息枚举
*****************************************************************************/
enum MMC_LMM_INFO_TYPE_ENUM
{
    MMC_LMM_TIN_TYPE                    = 0x00000000,                           /* Tin 类型*/
    MMC_LMM_EPLMN                       ,                                       /* 等效Plmn */
    MMC_LMM_FPLMN                       ,                                       /* 禁止Plmn */
    MMC_LMM_FPLMN_FOR_GPRS              ,                                       /* 禁止Plmn for gprs */
    MMC_LMM_EHPLMN                      ,
    MMC_LMM_HPLMN                       ,

    MMC_LMM_INFO_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_INFO_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名称: MMC_LMM_TIN_TYPE_ENUM
 协议表格:
 ASN.1 描述:
 枚举说明:  Tin的类型
*****************************************************************************/
enum MMC_LMM_TIN_TYPE_ENUM
{
    MMC_LMM_TIN_P_TMSI                  = 0x00000000,
    MMC_LMM_TIN_GUTI                    ,
    MMC_LMM_TIN_RAT_RELATED_TMSI        ,
    MMC_LMM_TIN_INVALID                 ,

    MMC_LMM_TIN_BUTT
};
typedef VOS_UINT32 MMC_LMM_TIN_TYPE_ENUM_UINT32;



/*****************************************************************************
 枚举名称: MMC_LMM_RADIO_CAP_UPD_NEED_TYPE_ENUM
 协议表格:
 ASN.1 描述:
 枚举说明:
*****************************************************************************/
enum MMC_LMM_RADIO_CAP_UPD_NEED_TYPE_ENUM
{
    MMC_LMM_RADIO_CAP_UPD_NO_NEED    = 0x00000000,
    MMC_LMM_RADIO_CAP_UPD_NEED ,

    MMC_LMM_RADIO_CAP_UPD_BUTT
};
typedef VOS_UINT32 MMC_LMM_RADIO_CAP_UPD_NEED_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MMC_LMM_PLMN_CTRL_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : PLMN是否禁止标识
*****************************************************************************/
enum MMC_LMM_PLMN_CTRL_ENUM
{
    MMC_LMM_PLMN_ALLOW_REG              = 0,                                    /* 允许注册 */
    MMC_LMM_PLMN_NOT_ALLOW_REG          ,                                        /*不允许注册 */
    MMC_LMM_PLMN_CTRL_BUTT
};
typedef VOS_UINT32 MMC_LMM_PLMN_CTRL_ENUM_UINT32;
/*****************************************************************************
 枚举名    : MMC_LMM_ATT__REQ_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : UE触发的ATTACH TYPE
*****************************************************************************/
enum MMC_LMM_ATT_REQ_TYPE_ENUM
{
    MMC_LMM_ATT_REQ_TYPE_CS_ONLY                      = 0,
    MMC_LMM_ATT_REQ_TYPE_PS_ONLY                      = 1,
    MMC_LMM_ATT_REQ_TYPE_CS_PS                        = 2,
    MMC_LMM_ATT_REQ_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_ATT_REQ_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MMC_LMM_ATT_REASON_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 触发的ATTACH原因
*****************************************************************************/
enum MMC_LMM_ATT_REASON_ENUM
{
    MMC_LMM_ATT_REASON_INITIAL,
    MMC_LMM_ATT_REASON_HANDOVER,
    MMC_LMM_ATT_REASON_BUTT
};
typedef VOS_UINT32 MMC_LMM_ATT_REASON_ENUM_UINT32;


/*****************************************************************************
 枚举名    : MMC_LMM_ATTACH_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : UE触发的ATTACH TYPE
*****************************************************************************/
enum MMC_LMM_ATTACH_TYPE_ENUM
{
    MMC_LMM_ATT_TYPE_EPS_ONLY                     = 1,
    MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI            = 2,
    MMC_LMM_ATT_TYPE_EPS_EMERGENCY                = 6,
    MMC_LMM_ATT_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_ATTACH_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MMC_LMM_ATTACH_CN_RSLT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 网侧响应的ATTACH结果类型
*****************************************************************************/
enum MMC_LMM_ATTACH_CN_RSLT_ENUM
{
    MMC_LMM_ATT_CN_RSLT_EPS_ONLY                     = 1,
    MMC_LMM_ATT_CN_RSLT_COMBINED_EPS_IMSI            = 2,
    MMC_LMM_ATT_CN_RSLT_BUTT
};
typedef VOS_UINT32 MMC_LMM_ATTACH_CN_RSLT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MMC_LMM_CL_REG_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : CL的VIA形态使用的ATTACH注册结果上报时所处的阶段
*****************************************************************************/
enum MMC_LMM_CL_REG_STATUS_ENUM
{
    MMC_LMM_CL_REG_STATUS_ATTACH_NOT_SEND            = 0x00,
    MMC_LMM_CL_REG_STATUS_ATTACH_SEND_WAIT_CN_RSP    = 0x01,
    MMC_LMM_CL_REG_STATUS_ATTACH_RCV_CN_REJ          = 0x02,
    MMC_LMM_CL_REG_STATUS_ATTACH_RCV_CN_ACP          = 0x03,
    MMC_LMM_CL_REG_STATUS_ATTACH_T3410_EXP           = 0x04,
    MMC_LMM_CL_REG_STATUS_ATTACH_CMP_SEND            = 0x05,

    MMC_LMM_CL_REG_STATUS_BUTT
};
typedef VOS_UINT8 MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8;

/*****************************************************************************
 枚举名    : MMC_LMM_ATTACH_RSLT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : ATTACH的结果类型
*****************************************************************************/
enum MMC_LMM_ATTACH_RSLT_ENUM
{

    MMC_LMM_ATT_RSLT_SUCCESS                     = 0x00000000,
    MMC_LMM_ATT_RSLT_FAILURE,                                                   /*其他ATTACH未指定原因的失败 */
    MMC_LMM_ATT_RSLT_ACCESS_BAR,                                                /* 接入被 Barred */
    MMC_LMM_ATT_RSLT_TIMER_EXP,                                                 /* 网侧无响应 */
    MMC_LMM_ATT_RSLT_CN_REJ,                                                    /* 网侧明确拒绝 */
    MMC_LMM_ATT_RSLT_AUTH_REJ,                                                  /* 鉴权被拒 */
    MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW,                                          /* ps注册标记不允许注册*/
    MMC_LMM_ATT_RSLT_FORBID_PLMN,                                               /* PLMN被禁*/
    MMC_LMM_ATT_RSLT_FORBID_PLMN_FOR_GPRS,                                      /* PLMN FOR GRPS被禁*/
    MMC_LMM_ATT_RSLT_FORBID_TA_FOR_ROAMING,                                     /* TA FOR ROAM被禁*/
    MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS,                                        /* TA FOR RPOS被禁*/
    MMC_LMM_ATT_RSLT_ESM_FAILURE,
    MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE,
    MMC_LMM_ATT_RSLT_MT_DETACH_FAILURE,
    MMC_LMM_ATT_RSLT_T3402_RUNNING,
    MMC_LMM_ATT_RSLT_BUTT
};
typedef VOS_UINT32 MMC_LMM_ATTACH_RSLT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MMC_LMM_MO_DETACH_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : UE触发的DETACH TYPE
*****************************************************************************/
enum MMC_LMM_MO_DETACH_TYPE_ENUM
{
    MMC_LMM_MO_DET_PS_ONLY                        = 1,
    MMC_LMM_MO_DET_CS_ONLY                        = 2,
    MMC_LMM_MO_DET_CS_PS                          = 3,
    MMC_LMM_MO_DETACH_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MMC_LMM_DETACH_RESEAON_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : DETACH发起的原因
*****************************************************************************/
enum MMC_LMM_DETACH_RESEAON_ENUM
{
    MMC_LMM_DETACH_RESEAON_NULL,                  /*无特殊原因*/
    MMC_LMM_DETACH_RESEAON_NON_3GPP_ATTACH,       /*non-3GPP接入技术下终端已注册，LTE下需要去注册*/
    MMC_LMM_DETACH_RESEAON_BUTT
};
typedef VOS_UINT32 MMC_LMM_DETACH_RESEAON_ENUM_UINT32;


/*****************************************************************************
 枚举名    : MMC_LMM_MT_DETACH_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 网侧触发的DETACH TYPE
*****************************************************************************/
enum MMC_LMM_MT_DETACH_TYPE_ENUM
{
    MMC_LMM_MT_DET_REATTACH_REQUIRED                = 1,
    MMC_LMM_MT_DET_REATTACH_NOT_REQUIRED            = 2,
    MMC_LMM_MT_DET_IMSI                             = 3,

    MMC_LMM_MT_DETACH_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_MT_DETACH_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MMC_LMM_DETACH_RSLT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : DETACH的结果类型
*****************************************************************************/
enum MMC_LMM_DETACH_RSLT_ENUM
{
    MMC_LMM_DETACH_RSLT_SUCCESS         = 0,
    MMC_LMM_DETACH_RSLT_ACCESS_BARED    ,
    MMC_LMM_DETACH_RSLT_FAILURE         ,
    MMC_LMM_DETACH_RSLT_AUTH_REJ        ,

    MMC_LMM_DETACH_RSLT_BUTT
};
typedef VOS_UINT32 MMC_LMM_DETACH_RSLT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MMC_LMM_DETACH_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 网侧触发的DETACH或本地DETACH
*****************************************************************************/
enum MMC_LMM_DETACH_TYPE_ENUM
{
    MMC_LMM_DETACH_LOCAL                            = 1,
    MMC_LMM_DETACH_MT                               = 2,

    MMC_LMM_DETACH_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_DETACH_TYPE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : MMC_LMM_TAU_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : UE触发的TAU类型
*****************************************************************************/
enum MMC_LMM_TAU_TYPE_ENUM
{
    MMC_LMM_TA_UPDATING                     = 0,
    MMC_LMM_COMBINED_TA_LA_UPDATING         = 1,
    MMC_LMM_COMBINED_TA_LA_WITH_IMSI        = 2,
    MMC_LMM_PS_PERIODIC_UPDATING            = 3,
    MMC_LMM_CS_PS_PERIODIC_UPDATING         = 4,
    MMC_LMM_TAU_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_TAU_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MMC_LMM_TAU_CN_RSLT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 网侧响应的TAU结果类型
*****************************************************************************/
enum MMC_LMM_TAU_CN_RSLT_ENUM
{
    MMC_LMM_TA_UPDATED                     = 0,
    MMC_LMM_COMBINED_TA_LA_UPDATED         = 1,
    MMC_LMM_TA_UPDATED_ISR_ACTIVATED       = 4,
    MMC_LMM_COMBINED_TA_LA_UPDATED_ISR_ACTIVATED              = 5,
    MMC_LMM_TAU_CN_RSLT_BUTT
};
typedef VOS_UINT32 MMC_LMM_TAU_CN_RSLT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MMC_LMM_TAU_RSLT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : TAU的结果类型
*****************************************************************************/
enum MMC_LMM_TAU_RSLT_ENUM
{

    MMC_LMM_TAU_RSLT_SUCCESS                     = 0,
    MMC_LMM_TAU_RSLT_FAILURE,                           /*其他未指定原因的失败*/
    MMC_LMM_TAU_RSLT_ACCESS_BARED,                      /*TAU接入被bar*/
    MMC_LMM_TAU_RSLT_TIMER_EXP,                         /*TAU定时器超时*/
    MMC_LMM_TAU_RSLT_CN_REJ,                            /*TAU网侧拒绝*/
    MMC_LMM_TAU_RSLT_AUTH_REJ,                          /*鉴权拒绝*/
    MMC_LMM_TAU_RSLT_FORBID_PLMN,                       /* PLMN被禁*/
    MMC_LMM_TAU_RSLT_FORBID_PLMN_FOR_GPRS,              /* PLMN FOR GRPS被禁*/
    MMC_LMM_TAU_RSLT_FORBID_TA_FOR_ROAMING,             /* TA FOR ROAM被禁*/
    MMC_LMM_TAU_RSLT_FORBID_TA_FOR_RPOS,                /* TA FOR RPOS被禁*/
    MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE,
    MMC_LMM_TAU_RSLT_MT_DETACH_FAILURE,
    MMC_LMM_TAU_RSLT_T3402_RUNNING,

    MMC_LMM_TAU_RSLT_T3402_RUNNING_EPS_ONLY_SUCC,

    MMC_LMM_TAU_RSLT_BUTT
};
typedef VOS_UINT32 MMC_LMM_TAU_RSLT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MMC_LMM_SERVICE_RSLT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : SERVICE的结果类型
*****************************************************************************/
enum MMC_LMM_SERVICE_RSLT_ENUM
{

    MMC_LMM_SERVICE_RSLT_FAILURE        = 0,                                    /*除网侧拒绝外的失败*/
    MMC_LMM_SERVICE_RSLT_ACCESS_BARED   ,                                       /*接入被bar*/
    MMC_LMM_SERVICE_RSLT_CN_REJ         ,                                       /*网侧拒绝*/
    MMC_LMM_SERVICE_RSLT_AUTH_REJ       ,                                       /*鉴权拒绝*/
    MMC_LMM_SERVICE_RSLT_TIMER_EXP      ,                                       /*定时器超时，PS和CSFB都填这个*/

    MMC_LMM_SERVICE_RSLT_BUTT
};
typedef VOS_UINT32 MMC_LMM_SERVICE_RSLT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MMC_LMM_SERVICE_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : UE触发的EXTENDED SERVICE的类型，暂时保留
*****************************************************************************/
enum MMC_LMM_SERVICE_TYPE_ENUM
{
    MMC_LMM_SERVICE_MO_CSFB_1XCSFB              = 0,
    MMC_LMM_SERVICR_MT_CSFB_1XCSFB,
    MMC_LMM_SERVICR_MO_CSFB_1XCSFB_EMERGENCY,
    MMC_LMM_SERVICE_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_SERVICE_TYPE_ENUM_UINT32;
/* 注册/服务状态上报上移MMC，删除注册/服务状态相关代码 */
/*****************************************************************************
 枚举名    : MMC_LMM_SYS_MODE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LMM上报的sys mode
*****************************************************************************/
enum MMC_LMM_SYS_MODE_ENUM
{
    MMC_LMM_SERVICE_MODE_NO_SERVICE             = 0,
    MMC_LMM_SERVICE_MODE_GSM,
    MMC_LMM_SERVICE_MODE_CDMA,
    MMC_LMM_SERVICE_MODE_WCDMA,
    MMC_LMM_SERVICE_MODE_TDSCDMA,
    MMC_LMM_SERVICE_MODE_WIMAX,
    MMC_LMM_SERVICE_MODE_LTE,
    MMC_LMM_SERVICE_MODE_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_SYS_MODE_ENUM_UINT32;
/* 注册/服务状态上报上移MMC，删除注册/服务状态相关代码 */


/*****************************************************************************
 枚举名    : MMC_LMM_L_LOCAL_DETACH_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 本地DETACH类型
*****************************************************************************/
enum MMC_LMM_L_LOCAL_DETACH_TYPE_ENUM
{
    MMC_LMM_L_LOCAL_DETACH_IMSI_PAGING          = 0,
    MMC_LMM_L_LOCAL_DETACH_OTHERS               = 1,

    MMC_LMM_L_LOCAL_DETACH_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_L_LOCAL_DETACH_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MMC_LMM_GPRS_UPDATE_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : GPRS update status枚举
*****************************************************************************/
enum MMC_LMM_GPRS_UPDATE_STATUS_ENUM
{
    MMC_LMM_GPRS_UPDATE_STATUS_UPDATED,
    MMC_LMM_GPRS_UPDATE_STATUS_NOT_UPDATED,
    MMC_LMM_GPRS_UPDATE_STATUS_PLMN_NOT_ALLOWED,
    MMC_LMM_GPRS_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED,
    MMC_LMM_GPRS_UPDATE_STATUS_BUTT
};
typedef VOS_UINT8 MMC_LMM_GPRS_UPDATE_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MMC_LMM_CS_UPDATE_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : MM update status枚举
*****************************************************************************/
enum MMC_LMM_CS_UPDATE_STATUS_ENUM
{
    MMC_LMM_CS_UPDATE_STATUS_UPDATED,
    MMC_LMM_CS_UPDATE_STATUS_NOT_UPDATED,
    MMC_LMM_CS_UPDATE_STATUS_PLMN_NOT_ALLOWED,
    MMC_LMM_CS_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED,
    MMC_LMM_CS_UPDATE_STATUS_UPDATING_DISABLED,
    MMC_LMM_CS_UPDATE_STATUS_BUTT
};
typedef VOS_UINT8 MMC_LMM_CS_UPDATE_STATUS_ENUM_UINT8;


/*****************************************************************************
 枚举名    : MMC_LMM_GU_LOCAL_DETACH_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : UE本地detach type
*****************************************************************************/
enum MMC_LMM_GU_LOCAL_DETACH_TYPE_ENUM
{
    MMC_LMM_GU_LOCAL_DET_IMSI_PAGING,
    MMC_LMM_GU_LOCAL_DET_OTHERS,
    MMC_LMM_GU_LOCAL_DET_BUTT
};
typedef VOS_UINT32 MMC_LMM_GU_LOCAL_DETACH_TYPE_ENUM_UINT32;



enum LMM_MMC_TIMER_STATE_ENUM
{
    LMM_MMC_TIMER_STOP         = 0,
    LMM_MMC_TIMER_START,
    LMM_MMC_TIMER_EXP,

    LMM_MMC_TIMER_BUTT
};
typedef VOS_UINT32 LMM_MMC_TIMER_STATE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MMC_LMM_RAT_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 接入技术枚举定义
*****************************************************************************/
enum MMC_LMM_RAT_TYPE_ENUM
{
    MMC_LMM_RAT_GSM                     = 0,
    MMC_LMM_RAT_WCDMA_FDD               = 1,
    MMC_LMM_RAT_LTE                     = 2,
    MMC_LMM_RAT_TYPE_BUTT
};
typedef VOS_UINT8  MMC_LMM_RAT_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MMC_LMM_RAT_LIST_SEARCH_RSLT_ENUM
 结构说明  : LMM_MMC_PLMN_SRCH_CNF_STRU消息中的LIST搜索完成情况
*****************************************************************************/
enum MMC_LMM_RAT_LIST_SEARCH_RSLT_ENUM
{
    MMC_LMM_RAT_LIST_SEARCH_NOT_START      = 0,                /* LIST搜索未启动        */
    MMC_LMM_RAT_LIST_SEARCH_PARTIAL_CMPL   = 1,                /* LIST搜索已启动,部分完成 */
    MMC_LMM_RAT_LIST_SEARCH_CMPL           = 2,                /* LIST搜索完成          */
    MMC_LMM_RAT_LIST_SEARCH_BUTT
};
typedef VOS_UINT8  MMC_LMM_RAT_LIST_SEARCH_RSLT_ENUM_UINT8;


/*****************************************************************************
 枚举名: MMC_LMM_PLMN_SRCH_RLT_ENUM
 协议格式:
 ASN.1描述:
 枚举说明:
*****************************************************************************/
enum MMC_LMM_COVERAGE_TYPE_ENUM
{
    MMC_LMM_COVERAGE_TYPE_NONE     = 0,                /* 无网络覆盖 */
    MMC_LMM_COVERAGE_TYPE_LOW      = 1,                 /* 有质量网络覆盖   */
    MMC_LMM_COVERAGE_TYPE_HIGH     = 2,                /* 有高质量网络覆盖 */
    MMC_LMM_COVERAGE_TYPE_BUTT
};
typedef VOS_UINT32  MMC_LMM_COVERAGE_TYPE_ENUM_UINT32;



/*****************************************************************************
 枚举名    : NASUTRANCTRL_UTRAN_MODE_ENUM
 结构说明  : MS当前具体的UTRAN模式:WCDMA/TD-SCAMA
 1.日    期   : 2012年7月27日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
enum MMC_LMM_UTRAN_MODE_ENUM
{
    MMC_LMM_UTRAN_MODE_FDD          = 0,     /* 当前工作模式为WCDMA */
    MMC_LMM_UTRAN_MODE_TDD          = 1,     /* 当前工作模式为TDSCDMA */
    MMC_LMM_UTRAN_MODE_NULL         = 2,     /* CL模式下的工作模式 */
    MMC_LMM_UTRAN_MODE_BUTT
};
typedef VOS_UINT8  MMC_LMM_UTRAN_MODE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : MMC_LMM_SESSION_TYPE_ENUM_UINT8
 枚举说明  : SESSION类型
 1.日    期   : 2014年5月22日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
enum MMC_LMM_SESSION_TYPE_ENUM
{
    MMC_LMM_SESSION_TYPE_CS_MO_NORMAL_CALL,
    MMC_LMM_SESSION_TYPE_CS_MO_EMERGENCY_CALL,
    MMC_LMM_SESSION_TYPE_CS_MO_SS,
    MMC_LMM_SESSION_TYPE_CS_MO_SMS,
    MMC_LMM_SESSION_TYPE_PS_CONVERSAT_CALL,
    MMC_LMM_SESSION_TYPE_PS_STREAM_CALL,
    MMC_LMM_SESSION_TYPE_PS_INTERACT_CALL,
    MMC_LMM_SESSION_TYPE_PS_BACKGROUND_CALL,
    MMC_LMM_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL,
    MMC_LMM_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 MMC_LMM_SESSION_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MMC_LMM_AREA_LOST_REASON_UINT32
 枚举说明  : 丢网原因
 1.日    期   : 2014年5月22日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
enum MMC_LMM_AREA_LOST_REASON_ENUM
{
    MMC_LMM_AREA_LOST_REASON_NO_COVERAGE,
    MMC_LMM_AREA_LOST_REASON_NO_RF,
    MMC_LMM_AREA_LOST_REASON_BUTT
};
typedef  VOS_UINT32 MMC_LMM_AREA_LOST_REASON_UINT32;




/*****************************************************************************
 枚举名    : MMC_LMM_IMS_VOICE_CAP_CHANGE_ENUM_UINT8
 结构说明  : IMS VOICE CAP是否改变
 1.日    期   : 2013年12月13日
   作    者   : l00132387
   修改内容   : 新建
*****************************************************************************/
enum MMC_LMM_IMS_VOICE_CAP_ENUM
{
    MMC_LMM_IMS_VOICE_CAP_UNAVAILABLE             = 0,
    MMC_LMM_IMS_VOICE_CAP_AVAILABLE                 = 1,

    MMC_LMM_IMS_VOICE_CAP_CHANGE_BUTT
};
typedef VOS_UINT8  MMC_LMM_IMS_VOICE_CAP_ENUM_UINT8;


/*****************************************************************************
 枚举名    : LMM_MMC_NW_IMS_VOICE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 网侧支持的IMS VOICE枚举
*****************************************************************************/
enum LMM_MMC_NW_IMS_VOICE_ENUM
{
    LMM_MMC_NW_IMS_VOICE_NOT_SUPPORTED   = 0,
    LMM_MMC_NW_IMS_VOICE_SUPPORTED        = 1,

    LMM_MMC_NW_IMS_VOICE_BUTT
};
typedef VOS_UINT32 LMM_MMC_NW_IMS_VOICE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LMM_MMC_NW_EMC_BS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 网侧支持的EMC BEARER SERVICEE枚举
*****************************************************************************/
enum LMM_MMC_NW_EMC_BS_ENUM
{
    LMM_MMC_NW_EMC_BS_NOT_SUPPORTED      = 0,
    LMM_MMC_NW_EMC_BS_SUPPORTED           = 1,

    LMM_MMC_NW_EMC_BS_BUTT
};
typedef VOS_UINT32 LMM_MMC_NW_EMC_BS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LMM_MMC_LTE_CS_CAPBILITY_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LTE的CS域能力
*****************************************************************************/
enum LMM_MMC_LTE_CS_CAPBILITY_ENUM
{
    LMM_MMC_LTE_CS_CAPBILITY_NO_ADDITION_INFO  = 0,  /* NO_ADDITION_INFO表示CS支持全功能 */
    LMM_MMC_LTE_CS_CAPBILITY_CSFB_NOT_PREFER   = 1,
    LMM_MMC_LTE_CS_CAPBILITY_SMS_ONLY          = 2,
    LMM_MMC_LTE_CS_CAPBILITY_NOT_ATTACHED      = 3,
    LMM_MMC_LTE_CS_CAPBILITY_BUTT
};
typedef VOS_UINT32 LMM_MMC_LTE_CS_CAPBILITY_ENUM_UINT32;

/*****************************************************************************
 结构名称: MMC_LMM_ACCESS_TYPE_ENUM
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
enum MMC_LMM_ACCESS_TYPE_ENUM
{
    MMC_LMM_ACCESS_TYPE_EUTRAN_TDD      = 0,
    MMC_LMM_ACCESS_TYPE_EUTRAN_FDD         ,
    MMC_LMM_ACCESS_TYPE_BUTT
};
typedef VOS_UINT8  MMC_LMM_ACCESS_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名称: MMC_LMM_CELL_TYPE_ENUM_UINT8
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
enum MMC_LMM_CELL_TYPE_ENUM
{
    MMC_LMM_CELL_TYPE_MACRO      = 0,          /* 小区类型是宏小区 */
    MMC_LMM_CELL_TYPE_HYBRID     = 1,          /* 小区类型为混合小区 */
    MMC_LMM_CELL_TYPE_CSG        = 2,          /* 小区类型为CSG小区 */
    MMC_LMM_CELL_TYPE_BUTT
};
typedef VOS_UINT8 MMC_LMM_CELL_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名称: MMC_LMM_CSG_LIST_SRCH_RLT_ENUM_UINT8
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
enum MMC_LMM_CSG_LIST_SRCH_RLT_ENUM
{
    MMC_LMM_CSG_LIST_SRCH_RLT_SUCC  = 0,
    MMC_LMM_CSG_LIST_SRCH_RLT_FAIL  = 1,
    MMC_LMM_CSG_LIST_SRCH_RLT_REJ   = 2,
    MMC_LMM_CSG_LIST_SRCH_RLT_NO_RF = 3,
    MMC_LMM_CSG_LIST_SRCH_RLT_BUTT
};
typedef VOS_UINT8 MMC_LMM_CSG_LIST_SRCH_RLT_ENUM_UINT8;



/*****************************************************************************
 结构名称: LMM_MMC_SIM_AUTH_FAIL_ENUM
 协议表格:
 ASN.1 描述:
 结构说明: 卡鉴权失败原因值LMM通知MMC接口 20141103add
*****************************************************************************/
enum LMM_MMC_SIM_AUTH_FAIL_ENUM
{
    LMM_MMC_SIM_AUTH_FAIL_NULL                      = 0,
    LMM_MMC_SIM_AUTH_FAIL_MAC_FAILURE               = 1,
    LMM_MMC_SIM_AUTH_FAIL_SYNC_FAILURE              = 2,
    LMM_MMC_SIM_AUTH_FAIL_OTHER                     = 3,
    LMM_MMC_SIM_AUTH_FAIL_BUTT
};
typedef VOS_UINT16  LMM_MMC_SIM_AUTH_FAIL_ENUM_UINT16;

/*****************************************************************************
 结构名称: LMM_MMC_SRV_DOMAIN_ENUM
 协议表格:
 ASN.1 描述:
 结构说明: 卡鉴权失败服务域LMM通知MMC接口 20141103add
*****************************************************************************/
enum LMM_MMC_SRV_DOMAIN_ENUM
{
    LMM_MMC_SRV_DOMAIN_CS                           = 1,
    LMM_MMC_SRV_DOMAIN_PS                           = 2,
    LMM_MMC_SRV_DOMAIN_CS_PS                        = 3,
    LMM_MMC_SRV_DOMAIN_BUTT
};
typedef VOS_UINT8  LMM_MMC_SRV_DOMAIN_ENUM_UINT8;

/*****************************************************************************
 结构名    : MMC_LMM_VOICE_DOMAIN_ENUM_UINT8
 结构说明  : MMC上报的VOIDE DOMAIN类型
  1.日    期   : 2015年01月21日
    作    者   : f00179208
    修改内容   : 新建
 *****************************************************************************/
enum MMC_LMM_VOICE_DOMAIN_ENUM
{
    MMC_LMM_VOICE_DOMAIN_CS_ONLY            = 0,    /* CS voice only */
    MMC_LMM_VOICE_DOMAIN_IMS_PS_ONLY        = 1,    /* IMS PS voice only */
    MMC_LMM_VOICE_DOMAIN_CS_PREFERRED       = 2,    /* CS vocie preferred, IMS PS voice as secondary */
    MMC_LMM_VOICE_DOMAIN_IMS_PS_PREFERRED   = 3,    /* IMS PS voice preferred, CS vocie as secondary */

    MMC_LMM_VOICE_DOMAIN_BUTT
};
typedef VOS_UINT8  MMC_LMM_VOICE_DOMAIN_ENUM_UINT32;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
结构名    :MMC_LMM_PLMN_ID_STRU中
协议表格  :
ASN.1描述 :
结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPlmnId[MMC_LMM_PLMN_ID_LEN];
    VOS_UINT8                           ucRsv;
}MMC_LMM_PLMN_ID_STRU;

/*****************************************************************************
结构名    :MMC_LMM_PLMN_ID_WITH_RAT_STRU中
协议表格  :
ASN.1描述 :
结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPlmnId[MMC_LMM_PLMN_ID_LEN];
    MMC_LMM_RAT_TYPE_ENUM_UINT8         enPlmnRat;
}MMC_LMM_PLMN_ID_WITH_RAT_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_EPLMN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 等效PLMN数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPlmnNum;                              /* 等效 PLMN 个数   */
    MMC_LMM_PLMN_ID_STRU                astEplmnList[MMC_LMM_MAX_EQUPLMN_NUM];
}MMC_LMM_EPLMN_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_SUIT_PLMN_ID_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MMC_LMM_SUIT_PLMN_ID_LIST_STRU数据结构
*****************************************************************************/
typedef struct
{
    /* 当前小区系统消息中包含的共享 plmn id的个数 */
    VOS_UINT32                          ulSuitPlmnNum;

    /* 小区系统消息中包含的最大 共享plmn id的个数   */
    MMC_LMM_PLMN_ID_STRU                astSuitPlmnList[MMC_LMM_MAX_SRCH_PLMN_NUM];
} MMC_LMM_SUIT_PLMN_ID_LIST_STRU;


/*****************************************************************************
 结构名    : MMC_LMM_LOW_PLMN_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MMC_LMM_LOW_PLMN_INFO_STRU数据结构
*****************************************************************************/
typedef struct
{
    MMC_LMM_PLMN_ID_STRU                stPlmnId;                               /* PLMN ID    */
    VOS_INT32                           lRscp;                                  /* RSCP测量值 */
}MMC_LMM_LOW_PLMN_INFO_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_LOW_PLMN_WITH_RAT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MMC_LMM_LOW_PLMN_WITH_RAT_STRU数据结构
*****************************************************************************/
typedef struct
{
    MMC_LMM_PLMN_ID_WITH_RAT_STRU       stPlmnIdWithRat;                        /* PLMN ID    */
    VOS_INT32                           lRscp;                                  /* RSCP测量值 */
}MMC_LMM_LOW_PLMN_WITH_RAT_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_PLMN_ID_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MMC_LMM_PLMN_ID_LIST_STRU数据结构
*****************************************************************************/
typedef struct
{
    /* 高质量PLMN的个数 */
    VOS_UINT32                          ulHighPlmnNum;

    /* 高质量PLMN列表   */
    MMC_LMM_PLMN_ID_WITH_RAT_STRU       astHighPlmnWithRatList[MMC_LMM_MAX_HIGH_PLMN_NUM];


    /* 低质量PLMN的个数 */
    VOS_UINT32                          ulLowPlmnNum;

    /* 低质量PLMN列表   */
    MMC_LMM_LOW_PLMN_WITH_RAT_STRU      astLowPlmnWithRatList[MMC_LMM_MAX_LOW_PLMN_NUM];
}MMC_LMM_PLMN_ID_LIST_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_LIST_SEARCH_RAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MMC_LMM_LIST_SEARCH_RAT_INFO_STRU数据结构
*****************************************************************************/
typedef struct
{
    MMC_LMM_RAT_TYPE_ENUM_UINT8              enRat;                            /* 搜索的接入技术 */
    MMC_LMM_RAT_LIST_SEARCH_RSLT_ENUM_UINT8  enListSearchRlt;                  /* 接入技术LIST搜索完成结果 */
    VOS_UINT8                                aucReserve[2];
}MMC_LMM_LIST_SEARCH_RAT_INFO_STRU;

/*****************************************************************************
结构名称    :MMC_LMM_LAC_STRU
使用说明    :TAC信息  24.301  9.9.3.26
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLac;
    VOS_UINT8                           ucLacCnt;
    VOS_UINT8                           aucRsv[2];
}MMC_LMM_LAC_STRU;

/*****************************************************************************
结构名称    :NAS_LMM_TAC_STRU
使用说明    :TAC信息  24.301  9.9.3.26
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTac;
    VOS_UINT8                           ucTacCnt;
    VOS_UINT8                           aucRsv[2];
}NAS_LMM_TAC_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_PLMN_CSG_ID_WITH_RAT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PLMN和CSG ID信息结构
*****************************************************************************/
typedef struct
{
    MMC_LMM_PLMN_ID_STRU                stPlmnId;
    VOS_UINT32                          ulCsgId;
}MMC_LMM_PLMN_WITH_CSG_ID_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_PLMN_CSG_ID_WITH_RAT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 带接入技术的CSG ID信息结构
*****************************************************************************/
typedef struct
{
    MMC_LMM_PLMN_ID_WITH_RAT_STRU       stPlmnWithRat;
    VOS_UINT32                          ulCsgId;
}MMC_LMM_PLMN_CSG_ID_WITH_RAT_STRU;


/*****************************************************************************
 结构名    : MMC_LMM_PLMN_WITH_CSG_ID_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSG白名单列表信息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPlmnWithCsgIdListNum;
    MMC_LMM_PLMN_WITH_CSG_ID_STRU       astPlmnWithCsgIdInfo[MMC_LMM_MAX_PLMN_CSG_ID_NUM];
}MMC_LMM_PLMN_WITH_CSG_ID_LIST_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_CSG_ID_HOME_NODEB_NAME_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSG ID对应HOME NODEB名称结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHomeNodeBNameLen;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucHomeNodeBName[MMC_LMM_MAX_HOME_NODEB_NAME_LEN];
}MMC_LMM_CSG_ID_HOME_NODEB_NAME_STRU;


/*****************************************************************************
 结构名    : MMC_LMM_CSG_WHITE_LIST_NOTIFY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSG白名单指示消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
    MMC_LMM_PLMN_WITH_CSG_ID_LIST_STRU  stPlmnWithCsgIdList;
}MMC_LMM_CSG_WHITE_LIST_NOTIFY_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_CSG_BG_SEARCH_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSG背景搜网请求消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* 指定PLMN CSG ID及接入技术 */
    MMC_LMM_PLMN_ID_WITH_RAT_STRU       stPlmnWithRat;
    VOS_UINT32                          ulCsgIdNum;
    VOS_UINT32                          aulCsgId[MMC_LMM_MAX_PLMN_CSG_ID_NUM];
}MMC_LMM_CSG_BG_SEARCH_REQ_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_CL_INTERSYS_START_NTF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :CL异系统开始指示
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
    MMC_LMM_SYS_CHNG_TYPE_ENUM_UINT32   enSuspendCause;
}MMC_LMM_CL_INTERSYS_START_NTF_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_CSG_LIST_SEARCH_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSG列表搜网请求消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
}MMC_LMM_CSG_LIST_SEARCH_REQ_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_CSG_LIST_SEARCHED_PLMN_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSG列表搜网回复的高低质量网络信息数据结构
*****************************************************************************/
typedef struct
{
    MMC_LMM_PLMN_CSG_ID_WITH_RAT_STRU   stPlmnCsgIdWithRat;
    MMC_LMM_CSG_ID_HOME_NODEB_NAME_STRU stHomeNodeBName;
    VOS_INT32                           lRscp;                   /* RSCP测量值 */
}MMC_LMM_CSG_LIST_SEARCHED_PLMN_INFO_STRU;


/*****************************************************************************
 结构名    : MMC_LMM_CSG_LIST_SEARCHED_RESULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSG列表搜网结果高低质量网络列表信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                 ulTotalPlmnNum; /* 高低质量PLMN总个数 */
    VOS_UINT32                                 ulHighPlmnNum;  /* 高质量PLMN的个数 */

    /* 高低质量PLMN列表   */
    MMC_LMM_CSG_LIST_SEARCHED_PLMN_INFO_STRU   astCsgListSearchedPlmnInfoList[MMC_LMM_MAX_CSG_LIST_SRCH_RSLT_NUM];
}MMC_LMM_CSG_LIST_SEARCHED_RESULT_STRU;


/*****************************************************************************
 结构名称: LMM_MMC_CSG_LIST_SEARCH_CNF_STRU
 协议表格:
 ASN.1 描述:
 结构说明:LTE通知CSG列表搜网结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32             ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                             ulOpId;

    /* 搜索结果 */
    MMC_LMM_CSG_LIST_SRCH_RLT_ENUM_UINT8   enRlst;

    /* 由于CSG LIST搜网结果消息LMM_MMC_CSG_LIST_SEARCH_CNF_STRU大小是2280个字节，
       超过了内部消息队列最大长度1500字节，LNAS需要分两条消息上报，增加标识指示
       是否是最后一条消息 */
    VOS_UINT8                              ucCsgListResultCompleteFlag;
    VOS_UINT8                              aucReserved[2];

    /* CSG LIST PLMN搜索结果 */
    MMC_LMM_CSG_LIST_SEARCHED_RESULT_STRU  stCsgListSearchedResult;
}LMM_MMC_CSG_LIST_SEARCH_CNF_STRU;

/*****************************************************************************
 结构名称: LMM_MMC_CSG_BG_SEARCH_CNF_STRU
 协议表格:
 ASN.1 描述:
 结构说明:LTE通知CSG背景搜网结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* 搜索结果 */
    MMC_LMM_BG_SRCH_RLT_ENUM_UINT32     enRlst;

    /* CSG BG搜索失败时，该项有效,只携带CSG ID网络 */
    VOS_UINT32                          ulPlmnCsgIdNum;
    MMC_LMM_PLMN_CSG_ID_WITH_RAT_STRU   astPlmnCsgIdWithRat[MMC_LMM_MAX_PLMN_CSG_ID_NUM];
}LMM_MMC_CSG_BG_SEARCH_CNF_STRU;

/*****************************************************************************
 结构名称: LMM_MMC_CSG_ID_HOME_NODEB_NAME_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明:LTE通知CSG ID对应的HOME NODEB名称
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    MMC_LMM_PLMN_WITH_CSG_ID_STRU       stPlmnWithCsgId;
    MMC_LMM_CSG_ID_HOME_NODEB_NAME_STRU stHomeNodeBName;
}LMM_MMC_CSG_ID_HOME_NODEB_NAME_IND_STRU;





/*****************************************************************************
 结构名称: NAS_LMM_SYS_INFO_STRU
 协议表格:
 ASN.1 描述:
 结构说明:LTE模的小区系统消息
*****************************************************************************/
typedef struct
{
    MMC_LMM_SUIT_PLMN_ID_LIST_STRU      stSpecPlmnIdList;                       /* 当前小区的共享网络列表 */
    NAS_LMM_TAC_STRU                    stTac;                                  /* TrackingAreaCode */
    VOS_UINT32                          ulCellId;                               /* Cell Identity */
    MMC_LMM_CELL_STATUS_ENUM_UINT32     enCellStatusInd;                        /* 小区状态指示 */

    LTE_BAND_STRU                       stLteBand;                              /* L模当前驻留的频段信息 */

    VOS_UINT32                          ulArfcn;                                /* 驻留频点信息 */
    VOS_UINT8                           ucBandWidth;                            /* 带宽信息 */
    MMC_LMM_ACCESS_TYPE_ENUM_UINT8      enAccessType;                           /* 接入类型:TDD/FDD */
    MMC_LMM_CELL_TYPE_ENUM_UINT8        enCellType;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulCsgId;

}MMC_LMM_SYS_INFO_STRU;


/*****************************************************************************
 结构名    : MMC_LMM_LAI_STRU
 结构说明  : LA信息数据结构
*****************************************************************************/
typedef struct
{
    MMC_LMM_PLMN_ID_STRU                stPlmnId;
    MMC_LMM_LAC_STRU                    stLac;
}MMC_LMM_LAI_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_RAI_STRU
 结构说明  : RAI信息数据结构
*****************************************************************************/
typedef struct
{
    MMC_LMM_LAI_STRU                    stLai;
    VOS_UINT8                           ucRac;
    VOS_UINT8                           aucReserve[3];
}MMC_LMM_RAI_STRU;

/*****************************************************************************
 结构名称: MMC_LMM_MS_IDNETITY_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucMsIdentity[NAS_MAX_SIZE_MS_IDENTITY];
    VOS_UINT8                           aucRsv[3];
} MMC_LMM_MS_IDNETITY_STRU;


/*****************************************************************************
 结构名称: NAS_GUMM_PTMSI_STRU
 协议表格:
 ASN.1 描述:
 结构说明: 见 24.008 10.5.1.4
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPtmsi[NAS_MAX_SIZE_PTMSI];
} NAS_GUMM_PTMSI_STRU;


/*****************************************************************************
 结构名称: NAS_GUMM_PTMSI_SIGNATURE_STRU
 协议表格:
 ASN.1 描述:
 结构说明:见24.008 10.5.5.8
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPtmsiSign[NAS_MAX_SIZE_PTMSI_SIGNATURE];
    VOS_UINT8                           ucRsv;
} NAS_GUMM_PTMSI_SIGNATURE_STRU;

/*****************************************************************************
 结构名称: NAS_GUMM_SECU_CONTEXT_STRU
 协议表格:
 ASN.1 描述:
 结构说明:需要LMM清楚：从哪个RAT向LTE变换；
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucKSI;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT8                           aucCK[NAS_UMTS_CK_LENGTH];
    VOS_UINT8                           aucIK[NAS_UMTS_IK_LENGTH];

} NAS_GUMM_UMTS_CONTEXT_STRU;

/****************************************************************************
结构名称    : NAS_LMM_GUTI_HEAD_STRU
结构说明    : 24.301 9.9.3.10  EPS mobile identity
****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLenth;
    VOS_UINT8                           ucOeToi;
    VOS_UINT8                           aucRsv[2];
}NAS_LMM_GUTI_HEAD_STRU;



/****************************************************************************
结构名称    :NAS_LMM_MME_GROUPID_STRU
使用说明    :NAS_LMM_MME_GROUPID_STRU的相关参数
协议描述的 各DIGIT与字节/位的关系如下:
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucGroupId;
    VOS_UINT8                           ucGroupIdCnt;
    VOS_UINT8                           aucRsv[2];
}NAS_LMM_MME_GROUPID_STRU;

/****************************************************************************
结构名称    :NAS_LMM_MME_CODE_STRU
使用说明    :NAS_LMM_MME_CODE_STRU的相关参数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMmeCode;
    VOS_UINT8                           aucRsv[3];
}NAS_LMM_MME_CODE_STRU;

/****************************************************************************
结构名称    :NAS_LMM_MTMSI_STRU
使用说明    :NAS_LMM_MTMSI_STRU的相关参数
协议描述的 各DIGIT与字节/位的关系如下:
*************************************************************/
typedef struct
{
    VOS_UINT8                           ucMTmsi;
    VOS_UINT8                           ucMTmsiCnt1;
    VOS_UINT8                           ucMTmsiCnt2;
    VOS_UINT8                           ucMTmsiCnt3;
}NAS_LMM_MTMSI_STRU;

/*****************************************************************************
结构名称    :NAS_MM_GUTI_STRU
使用说明    :NAS_MM_GUTI_STRU的相关参数
*****************************************************************************/
typedef struct
{
    NAS_LMM_GUTI_HEAD_STRU               stGutiHead;
    MMC_LMM_PLMN_ID_STRU                 stPlmnId;
    NAS_LMM_MME_GROUPID_STRU             stMmeGroupId;
    NAS_LMM_MME_CODE_STRU                stMmeCode;
    NAS_LMM_MTMSI_STRU                   stMTmsi;
}NAS_LMM_GUTI_STRU;

/*****************************************************************************
结构名称    :NAS_MM_PLMN_LIST_STRU
使用说明    :10.5.13/3GPP TS 24.008 PLMN List information element
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPlmnNum;
    MMC_LMM_PLMN_ID_STRU                astPlmnId[MMC_LMM_MAX_PLMN_NUM];
}MMC_LMM_PLMN_LIST_STRU;

/*****************************************************************************
 结构名    : NAS_LMM_TAI_STRU
 结构说明  : TA信息数据结构
*****************************************************************************/
typedef struct
{
    MMC_LMM_PLMN_ID_STRU                 stPlmnId;
    NAS_LMM_TAC_STRU                     stTac;
}NAS_LMM_TAI_STRU;


/*****************************************************************************
 结构名    : NAS_LMM_TAI_LIST_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulTaNum;
    NAS_LMM_TAI_STRU                     astTa[MMC_LMM_MAX_FORB_ROAM_TAI_NUM];
}NAS_LMM_TAI_LIST_STRU;


/*****************************************************************************
 结构名称: MMC_LMM_START_REQ_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    MMC_LMM_TRANSCEIVER_TYPE_ENUM_UINT32 ulTransceiverType;
    MMC_LMM_USIM_STATUS_ENUM_UINT32      ulUsimState;
    RRMM_RAT_PRIO_ENUM_UINT8             aucRatPrioList[RRMM_RAT_TYPE_BUTT];     /* 各模的优先级 */
    MMC_LMM_UTRAN_MODE_ENUM_UINT8       enUtranMode;                            /* 当前UTRAN的工作模式:0---FDD 1---TDD */
    VOS_UINT8                           aucRsv[2];
} MMC_LMM_START_REQ_STRU;

/*****************************************************************************
 结构名称: LMM_MMC_START_CNF_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* 执行结果 */
    MMC_LMM_RESULT_ID_ENUM_UINT32          ulRst;
} LMM_MMC_START_CNF_STRU;

/*****************************************************************************
 结构名称: MMC_LMM_STOP_REQ_STRU
 协议表格:
 ASN.1 描述:
 结构说明:MMC_LMM_STOP_REQ_STRU结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
}MMC_LMM_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : LMM_MMC_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
}LMM_MMC_STOP_CNF_STRU;


/*****************************************************************************
 结构名    : MMC_LMM_ATTACH_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MMC_LMM_ATTACH_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    MMC_LMM_ATT_REQ_TYPE_ENUM_UINT32    ulAttachType;
    MMC_LMM_ATT_REASON_ENUM_UINT32      ulAttachReason;
}MMC_LMM_ATTACH_REQ_STRU;


/*****************************************************************************
 结构名    : LMM_MMC_ATTACH_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LMM_MMC_ATTACH_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    MMC_LMM_ATTACH_RSLT_ENUM_UINT32     ulAttachRslt;       /* ATTACH结果 */
    MMC_LMM_ATT_REQ_TYPE_ENUM_UINT32    ulReqType;          /* 用户发起的ATTACH类型 */

}LMM_MMC_ATTACH_CNF_STRU;


/*****************************************************************************
 结构名    : LMM_MMC_ATTACH_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LMM_MMC_ATTACH_IND_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT32                          bitOpCnRslt     : 1;
    VOS_UINT32                          bitOpCnCause    : 1;
    VOS_UINT32                          bitOpAtmpCnt    : 1;
    VOS_UINT32                          bitOpEplmn      : 1;
    VOS_UINT32                          bitOpLai        : 1;
    VOS_UINT32                          bitOpMsIdentity : 1;
    VOS_UINT32                          bitSpare        : 26;

    MMC_LMM_ATTACH_RSLT_ENUM_UINT32     ulAttachRslt;
    MMC_LMM_ATTACH_TYPE_ENUM_UINT32     ulReqType;
    MMC_LMM_ATTACH_CN_RSLT_ENUM_UINT32  ulCnRslt;
    NAS_LMM_CN_CAUSE_ENUM_UINT8         ucCnCause;        /* 网侧下发的原因值*/
    /* VIA CL多模使用的ATTACH流程阶段上报，此状态LMM不区分形态均填写，MMC只在VIA CL多模时使用 */
    MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8  enClAttRegStatus;
    VOS_UINT8                           aucRsv[2];
    VOS_UINT32                          ulAttemptCount;   /* ATTACH尝试次数 */
    MMC_LMM_EPLMN_STRU                  stEplmnList;      /*等效PLMN LIST, CN消息中的EPLMN */
    MMC_LMM_LAI_STRU                    stLai;
    MMC_LMM_MS_IDNETITY_STRU            stMsIdentity;

}LMM_MMC_ATTACH_IND_STRU;


/*****************************************************************************
 结构名称: MMC_LMM_DETACH_REQ_STRU
 协议表格:
 ASN.1 描述:
 结构说明:MMC_LMM_DETACH_REQ_STRU结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32  ulDetachType;
    MMC_LMM_DETACH_RESEAON_ENUM_UINT32  ulDetachReason;
}MMC_LMM_DETACH_REQ_STRU;


/*****************************************************************************
 结构名称: LMM_MMC_DETACH_CNF_STRU
 协议表格:
 ASN.1 描述:
 结构说明:LMM_MMC_DETACH_CNF_STRU结构,若ATTACH过程中收到MMC发送的DETACH REQ消息，
 LMM 通过此消息响应，不会再发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /*UE触发的DETACH响应结果*/
    MMC_LMM_DETACH_RSLT_ENUM_UINT32     ulDetachRslt;

    /*UE触发的DETACH类型*/
    MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32  ulReqType;

}LMM_MMC_DETACH_CNF_STRU;


/*****************************************************************************
 结构名称: LMM_MMC_DETACH_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明:LMM_MMC_DETACH_IND_STRU结构,若ATTACH过程中收到CN发送的MT DETACH消息，
 LMM 通过此消息响应，不会再发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT32                          bitOpCnReqType  : 1;
    VOS_UINT32                          bitOpCnCause    : 1;
    VOS_UINT32                          bitOpLocDetType : 1;
    VOS_UINT32                          bitSpare        : 29;

    /*DETACH的响应结果:网侧触发的DETACH或本地DETACH*/
    MMC_LMM_DETACH_TYPE_ENUM_UINT32     ulDetachType;

    /* 本地DETACH类型 */
    MMC_LMM_L_LOCAL_DETACH_TYPE_ENUM_UINT32 ulLocDetType;
    /*网侧触发的DETACH类型*/
    MMC_LMM_MT_DETACH_TYPE_ENUM_UINT32  ulCnReqType;/*接口文档中需说明*/

    /* 网侧下发的原因值*/
    NAS_LMM_CN_CAUSE_ENUM_UINT8         ucCnCause;
    VOS_UINT8                           aucRsv[3];


}LMM_MMC_DETACH_IND_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    MMC_LMM_CELL_SEL_TYPE_ENUM_UINT32   ulSelecType;

} MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU;


/*****************************************************************************
 结构名    : LMM_MMC_TAU_RESULT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LMM_MMC_TAU_RESULT_IND_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT32                          bitOpCnCause    : 1;
    VOS_UINT32                          bitOpAtmpCnt    : 1;
    VOS_UINT32                          bitOpEplmn      : 1;
    VOS_UINT32                          bitOpLai        : 1;
    VOS_UINT32                          bitOpMsIdentity : 1;
    VOS_UINT32                          bitOpCnRst      : 1;
    VOS_UINT32                          bitOpEpsUpdateStuts : 1;
    VOS_UINT32                          bitOpTaiInListFlag  : 1;
    VOS_UINT32                          bitSpare        : 24;


    /* TAU响应结果*/
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRst;

    /* TAU发起业务时的类型*/
    MMC_LMM_TAU_TYPE_ENUM_UINT32        ulReqType;

    /*网侧响应的TAU结果域类型*/
    MMC_LMM_TAU_CN_RSLT_ENUM_UINT32     ulCnRst;

    /* 网侧下发的原因值*/
    NAS_LMM_CN_CAUSE_ENUM_UINT8         ucCnCause;
    VOS_UINT8                           aucRsv1[3];

    /* TAU尝试失败次数 */
    VOS_UINT32                          ulAttemptCount;

    /*网侧分配的等效PLMN LIST */
    MMC_LMM_EPLMN_STRU                  stEplmnList;
    MMC_LMM_LAI_STRU                    stLai;

    MMC_LMM_MS_IDNETITY_STRU            stMsIdentity;

    /* EPS UPDATE STATUS */
    MMC_LMM_EPS_UPDATE_STATUS_ENUM_UINT8 enEmmUpStat;

    /* 标识TAI是否在TAI LIST中 */
    MMC_LMM_TAI_IN_LIST_FLAG_ENUM_UINT8 enTaiInListFlag;

    VOS_UINT8                           aucReserved[2];
} LMM_MMC_TAU_RESULT_IND_STRU;

/*****************************************************************************
 结构名    : LMM_MMC_SERVICE_RESULT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LMM_MMC_SERVICE_RESULT_IND_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT32                          bitOpCnCause    : 1;
    VOS_UINT32                          bitSpare        : 31;


    /* SERVICE响应结果:网侧拒绝*/
    MMC_LMM_SERVICE_RSLT_ENUM_UINT32    ulServiceRst;


    /* 网侧下发的原因值*/
    NAS_LMM_CN_CAUSE_ENUM_UINT8         ucCnCause;
    VOS_UINT8                           ucIsReachMaxTimes;  /* 1有效，0无效，仅ATT的PLMN可用 */
    VOS_UINT8                           aucRsv[2];

} LMM_MMC_SERVICE_RESULT_IND_STRU;

/*******************************************************************************
 结构名    : MMC_LMM_NCELL_INFO_STRU
 结构说明  : GSM下LTE邻区的频点列表

 1.日    期   : 2013年12月16日
   作    者   : z00161729
   修改内容   : 新生成结构
 2.日    期   : 2015年7月20日
   作    者   : w000316404
   修改内容   : R11协议升级(LTE频点配置值扩展)

*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLteArfcnNum;                          /* 0表示LTE频点不存在 */
    VOS_UINT8                           aucRsv[3];                              /* 保留位 */
    VOS_UINT32                          aulLteArfcnList[MMC_LMM_LTE_ARFCN_MAX_NUM];
    MMC_LMM_EPLMN_STRU                  stEplmnList;                            /* 邻区相关等效plmn信息*/

    VOS_UINT8                           ucLteCellIdNum;                         /* 0表示LTE小区ID不存在 */
    VOS_UINT8                           aucRsv1[3];                              /* 保留位 */
    VOS_UINT16                          ausLteCellIdList[MMC_LMM_LTE_CELL_ID_MAX_NUM];
}MMC_LMM_NCELL_INFO_STRU;

/*modified by z00234330 for 搜网优化,2015-02-05,begin*/
/*****************************************************************************
 结构名    : MMC_LMM_PLMN_SRCH_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MMC_LMM_PLMN_SRCH_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT32                          bitOpSpecPlmn: 1;
    VOS_UINT32                          bitOpEqlPlmn : 1;

    VOS_UINT32                          bitOpNcellInfo : 1;
    VOS_UINT32                          bitOpPlmnInfoCampFlg:1;                 /*底层上报的PLMN是否需要满足驻留条件,目前仅在获取地理信息接口中使用*/

    VOS_UINT32                          bitOpCsgIdListInfo:1;
    VOS_UINT32                          bitSpare     : 27;


    /* 搜索类型 */
    MMC_LMM_PLMN_SRCH_TYPE_ENUM_UINT32  enSrchType;
    MMC_LMM_FFT_SCAN_TYPE_ENUM_UINT8    enFftScanType;                          /* 通知LMM搜网时是否需要从COMM SRCH获取FFT扫频之后的频点，目前仅在获取地理信息中有用 */

    MMC_LMM_PLMN_SEARCH_SCENE_ENUM_UINT8 enPlmnSrchScene;                     /* MMC指定的PLMN搜网场景 */
    VOS_UINT8                            aucReserve[2];

    /* 指定PLMN ID */
    MMC_LMM_PLMN_ID_STRU                stSpecPlmnId;

    /* 等效PLMN LIST */
    MMC_LMM_EPLMN_STRU                  stEplmnList;                            /* 当前驻留网络等效plmn */

    MMC_LMM_NCELL_INFO_STRU             stNcellInfo;

    MMC_LMM_PLMN_WITH_CSG_ID_LIST_STRU  stPlmnWithCsgIdList;
}MMC_LMM_PLMN_SRCH_REQ_STRU;

/*modified by z00234330 for 搜网优化,2015-02-05,end*/

/*****************************************************************************
 结构名    : LMM_MMC_PLMN_SRCH_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LMM_MMC_PLMN_SRCH_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* 搜索结果 */
    MMC_LMM_PLMN_SRCH_RLT_ENUM_UINT32   enRlst;

    /* 当前接入技术下的网络覆盖类型 */
    MMC_LMM_COVERAGE_TYPE_ENUM_UINT32   enCoverageType;
    /* 指定PLMN搜网成功时,搜到的PLMN ID,当enRslt为指定搜网成功时有效 */
    MMC_LMM_SUIT_PLMN_ID_LIST_STRU      stSpecPlmnIdList;

    /* 记录L主模下本次已经搜索的接入技术，仅在列表搜索时有效 */
    MMC_LMM_LIST_SEARCH_RAT_INFO_STRU   astSearchRatInfo[MMC_LMM_MAX_RAT_NUM];

    /* LIST PLMN搜索时,或spec plmn搜索失败时，该项有效 */
    MMC_LMM_PLMN_ID_LIST_STRU           stPlmnIdList;
} LMM_MMC_PLMN_SRCH_CNF_STRU;


/*****************************************************************************
结构名    : MMC_LMM_STOP_PLMN_SRCH_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
} MMC_LMM_STOP_PLMN_SRCH_REQ_STRU;

/*****************************************************************************
 结构名    : LMM_MMC_STOP_PLMN_SRCH_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LMM_MMC_STOP_PLMN_SRCH_CNF_STRU 的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
} LMM_MMC_STOP_PLMN_SRCH_CNF_STRU;


/*****************************************************************************
 结构名    : MMC_LMM_BG_PLMN_SEARCH_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MMC_LMM_BG_PLMN_SEARCH_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* 指定PLMN ID及接入技术 */
    MMC_LMM_PLMN_ID_WITH_RAT_STRU       stSpecPlmnWithRat;

    /* 禁止注册区的个数,在搜索LTE网络时无效 */
    VOS_UINT32                          ulForbRoamLaiNum;

    /* 禁止LAI信息,在搜索LTE网络时无效 */
    MMC_LMM_LAI_STRU                    astForbRoamLaiList[MMC_LMM_MAX_FORB_ROAM_LAI_NUM];

}MMC_LMM_BG_PLMN_SEARCH_REQ_STRU;

/*****************************************************************************
 结构名    : LMM_MMC_BG_PLMN_SEARCH_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LMM_MMC_BG_PLMN_SEARCH_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* 搜索结果 */
    MMC_LMM_BG_SRCH_RLT_ENUM_UINT32     enRlst;

    /* spec plmn搜索失败时，该项有效 */
    VOS_UINT32                          ulPlmnNum;
    MMC_LMM_PLMN_ID_WITH_RAT_STRU       astPlmnIdWithRatList[MMC_LMM_MAX_BG_SRCH_PLMN_NUM];

} LMM_MMC_BG_PLMN_SEARCH_CNF_STRU;


/*****************************************************************************
结构名    : MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
} MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU;

/*****************************************************************************
 结构名    : LMM_MMC_STOP_BG_PLMN_SEARCH_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LMM_MMC_STOP_BG_PLMN_SEARCH_CNF_STRU 的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
} LMM_MMC_STOP_BG_PLMN_SEARCH_CNF_STRU;

/*****************************************************************************
 结构名    : LMM_MMC_NOT_CAMP_ON_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LMM_MMC_NOT_CAMP_ON_IND_STRU 的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
} LMM_MMC_NOT_CAMP_ON_IND_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_EPLMN_NOTIFY_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
        MMC只在以下三个场景中用原语MMC_LMM_EPLMN_NOTIFY_REQ通知LMM：
        （1）收到LMM的系统消息；
        （2）LMM的EPLMN发生变更；
        （3）异系统变换中，GU发生挂起，目标系统为LTE时；
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* EPLMN的个数,包含RPLMN */
    VOS_UINT32                          ulEplmnNum;

    /* 此EPLMN LIST可能更新的场景:
       注册成功时: 表中包含包含网侧下发的EPLMN LIST和刚
                        注册成功的RPLMN，为aEplmnList的最后一个有效PLMNID；
       注册失败时更新: 1) 删除EPLMN列表，此列表只包含当前驻留网络，ulEplmnNum为1；
                       2) 当前无注册的PLMN，但保留 EPLMNLIST，并
                       且表中仍包含刚才的RPLMN，即仍允许搜索
                       刚才的RPLMN */
    MMC_LMM_PLMN_ID_STRU                astEplmnList[MMC_LMM_MAX_EQUPLMN_NUM];

} MMC_LMM_EPLMN_NOTIFY_REQ_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_SEARCHED_TYPE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MMC_LMM_SEARCHED_TYPE_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHistorySearchedFlg;                   /* 是否进行过history搜 */
    VOS_UINT8                           ucPrefBandSearchedFlg;                  /* 是否进行过pref band搜 */
    VOS_UINT8                           ucSpecSearchedFlg;                      /* 是否进行过spec搜 */
    VOS_UINT8                           ucReserve;
}MMC_LMM_SEARCHED_TYPE_STRU;

/*****************************************************************************
 结构名    : LMM_MMC_AREA_LOST_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LMM_MMC_AREA_LOST_IND_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /*上报的PLMN ID列表*/
    MMC_LMM_PLMN_ID_LIST_STRU           stPlmnIdList;

    MMC_LMM_AREA_LOST_REASON_UINT32     enAreaLostReason;
    MMC_LMM_SEARCHED_TYPE_STRU          stSearchedType;                         /* AS上报丢网时已经搜索过类型 */
} LMM_MMC_AREA_LOST_IND_STRU;


/*****************************************************************************
 结构名称: LMM_MMC_SYS_INFO_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* 当前小区的系统消息: PLMN_LIST, TAC, CELLID, 小区状态等 */
    MMC_LMM_SYS_INFO_STRU               stLteSysInfo;

} LMM_MMC_SYS_INFO_IND_STRU;

/*****************************************************************************
 结构名称: MMC_EMM_INFO_UT_LTZ_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_UINT8                             ucYear;
    VOS_UINT8                             ucMonth;
    VOS_UINT8                             ucDay;
    VOS_UINT8                             ucHour;
    VOS_UINT8                             ucMinute;
    VOS_UINT8                             ucSecond;
    VOS_INT8                              cTimeZone;
    VOS_UINT8                             aucRsv[1];
} MMC_EMM_INFO_UT_LTZ_STRU;

/*****************************************************************************
 结构名称: MMC_EMM_INFO_DST_ENUM
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
enum MMC_EMM_INFO_DST_ENUM
{
    MMC_EMM_INFO_DST_NO_ADJUST                         = 0,
    MMC_EMM_INFO_DST_1_HOUR_ADJUST                        ,
    MMC_EMM_INFO_DST_2_HOUR_ADJUST                        ,
    MMC_EMM_INFO_DST_BUTT
};
typedef VOS_UINT8  MMC_EMM_INFO_DST_UINT8;

/*****************************************************************************
 结构名称: MMC_EMM_INFO_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_UINT32                            bitOpLocTimeZone           :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                            bitOpUniTimeLocTimeZone    :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                            bitOpDaylightTime          :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                            bitOpLongName              :1;
    VOS_UINT32                            bitOpShortName             :1;
    VOS_UINT32                            bitReserved                :27;

    VOS_INT8                              cLocTimeZone;
    MMC_EMM_INFO_UT_LTZ_STRU              stTimeZoneAndTime;
    MMC_EMM_INFO_DST_UINT8                enDaylightSavingTime;
    VOS_UINT8                             aucOperatorNameLong[MMC_LMM_MAX_OPER_LONG_NAME_LEN];
    VOS_UINT8                             aucOperatorNameShort[MMC_LMM_MAX_OPER_SHORT_NAME_LEN];

    VOS_UINT8                             aucRsv[2];
} MMC_EMM_INFO_STRU;

/*****************************************************************************
 结构名称: LMM_MMC_EMM_INFO_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* LTE EMM Information数据结构 */
    MMC_EMM_INFO_STRU                   stLteEmmInfo;

} LMM_MMC_EMM_INFO_IND_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_ACTION_RESULT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MMC_LMM_ACTION_RESULT_REQ_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT32                          bitOpReqDomain          : 1;
    VOS_UINT32                          bitOpRstDomain          : 1;
    VOS_UINT32                          bitOpMtDetachType       : 1;
    VOS_UINT32                          bitOpLocalDetachType    : 1;
    VOS_UINT32                          bitOpMoDetachType       : 1;
    VOS_UINT32                          bitOpCnCause            : 1;
    VOS_UINT32                          bitOpGprsUpdateStatus   : 1;
    VOS_UINT32                          bitOpRaiChangFlg        : 1;
    VOS_UINT32                          bitOpAtmpCnt            : 1;
    VOS_UINT32                          bitOpCsUpdateStatus     : 1;
    VOS_UINT32                          bitOpLaiChangFlg        : 1;
    VOS_UINT32                          bitSpare                : 21;


    /* 服务类型*/
    MMC_LMM_ACTION_TYPE_ENUM_UINT32     enActionType;

    /* CN_ACCEPT, CN_REJECT：各流程网络响应的结果 */
    MMC_LMM_RSLT_TYPE_ENUM_UINT32       ulActRst;


    /* 发起业务时的类型:仅ATTACH, RAU, DETACH时有效 */
    MMC_LMM_DOMAIN_ENUM_UINT32          ulReqDomain;

    /* 结果域类型，仅ATTACH, TAU, DETACH时有效，网络响应的结果 */
    MMC_LMM_DOMAIN_ENUM_UINT32          ulRstDomain;

    /*  仅 MT DETACH时有效 */
    MMC_LMM_MT_DETACH_TYPE_ENUM_UINT32  ulMtDetachType;


    /* local detach类型，仅本地detach时有效 */
    MMC_LMM_GU_LOCAL_DETACH_TYPE_ENUM_UINT32   ulLocalDetachType;

    /* UE主动detach 类型*/
    MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32  ulMoDetachType;


    /* 网络下发的原因 */
    NAS_LMM_CN_CAUSE_ENUM_UINT8         ucCnCause;

    /* GPRS update status */
    MMC_LMM_GPRS_UPDATE_STATUS_ENUM_UINT8 ucGprsUpdateStatus;

    /* RAI 是否改变 */
    VOS_UINT8                           ucRaiChangFlg;

    /* MM update status */
    MMC_LMM_CS_UPDATE_STATUS_ENUM_UINT8    ucCsUpdateStatus;

    /* LAI 是否改变 */
    VOS_UINT8                           ucLaiChangFlg;

    VOS_UINT8                           aucRsv[3];

    /* ATTACH或RAU失败尝试次数 */
    VOS_UINT32                          ulAttemptCount;

} MMC_LMM_ACTION_RESULT_REQ_STRU;


/*****************************************************************************
 结构名    : LMM_MMC_ERR_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LMM_MMC_ERR_IND_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];

} LMM_MMC_ERR_IND_STRU;



/*****************************************************************************
 结构名    : MMC_LMM_REL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MMC_LMM_REL_REQ_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
}MMC_LMM_REL_REQ_STRU;


/*****************************************************************************
 结构名    : LMM_MMC_SERVICE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LMM_MMC_SERVICE_IND_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
} LMM_MMC_EPS_SERVICE_IND_STRU;

/*****************************************************************************
 结构名称: LMM_MMC_SUSPEND_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明:LMM->MMC
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    MMC_LMM_SYS_CHNG_DIR_ENUM_UINT32    ulSysChngDir;                           /* 异系统方向 */
    MMC_LMM_SYS_CHNG_TYPE_ENUM_UINT32   ulSysChngType;                          /* 异系统变更类型 */

} LMM_MMC_SUSPEND_IND_STRU;

/*****************************************************************************
 结构名称: MMC_LMM_DEACT_REQ_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
} MMC_LMM_SUSPEND_REQ_STRU;

/*****************************************************************************
 结构名称: MMC_LMM_RESUME_NOTIFY_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
} MMC_LMM_RESUME_NOTIFY_STRU;

/*****************************************************************************
 结构名称: MMC_LMM_SUSPEND_RSP_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* 执行结果*/
    MMC_LMM_RESULT_ID_ENUM_UINT32          ulRst;

} MMC_LMM_SUSPEND_RSP_STRU;


/*****************************************************************************
 结构名称: LMM_MMC_SUSPEND_CNF_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;               /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* 执行结果*/
    MMC_LMM_RESULT_ID_ENUM_UINT32          ulRst;

} LMM_MMC_SUSPEND_CNF_STRU;


/*****************************************************************************
 结构名称: LMM_MMC_RESUME_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
} LMM_MMC_RESUME_IND_STRU;


/*****************************************************************************
 结构名称: LMM_MMC_STATUS_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT32                          bitOpConnState  : 1;
    VOS_UINT32                          bitSpare        : 31;

    /* 状态报告的类型 */
    MMC_LMM_STATUS_TYPE_ENUM_UINT32     ulStatusType;
    MMC_LMM_CONN_STATE_ENUM_UINT32      ulConnState;

} LMM_MMC_STATUS_IND_STRU;



/*****************************************************************************
 结构名称: MMC_LMM_SYS_CFG_REQ_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* 既然此AT命令必然同时包含RAT和BAND，则此处的bitop必然同时填1。 */
    VOS_UINT32                          bitOpRat:1;
    VOS_UINT32                          bitOpBand:1;
    VOS_UINT32                          bitSpare:30;

    NAS_RRC_USER_SET_FREQ_BAND_STRU     stBand;                                 /* 频段 */
    RRMM_RAT_PRIO_ENUM_UINT8            aucRatPrioList[RRMM_RAT_TYPE_BUTT];     /* 各模的优先级 */

    MMC_LMM_UTRAN_MODE_ENUM_UINT8       enUtranMode;                            /* 当前UTRAN的工作模式:0---FDD 1---TDD */

    VOS_UINT8                           aucReserved[2];                         /* 字节对齐 */
} MMC_LMM_SYS_CFG_REQ_STRU;



/*****************************************************************************
 结构名    :  MMC_LMM_SYS_CFG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    MMC_LMM_RESULT_ID_ENUM_UINT32          ulRst;
}LMM_MMC_SYS_CFG_CNF_STRU;


/*****************************************************************************
 结构名称: MMC_LMM_USIM_STATUS_REQ_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    MMC_LMM_USIM_STATUS_ENUM_UINT32     ulUsimState;

} MMC_LMM_USIM_STATUS_REQ_STRU;


/*****************************************************************************
 结构名称: LMM_MMC_USIM_STATUS_CNF_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];

} LMM_MMC_USIM_STATUS_CNF_STRU;

/*****************************************************************************
 结构名称: LMM_MMC_TIN_TYPE_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
    MMC_LMM_TIN_TYPE_ENUM_UINT32        ulTinType;
} LMM_MMC_TIN_TYPE_IND_STRU;
/* 注册/服务状态上报上移MMC，删除注册/服务状态相关代码 */
/*****************************************************************************
 结构名称: MMC_LMM_USER_PLMN_END_NOTIFY_STRU
 协议表格:
 ASN.1 描述:
 结构说明:  注册状态上报消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
} MMC_LMM_USER_PLMN_END_NOTIFY_STRU;
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          bitOpT3412  :1;
    VOS_UINT32                          bitOpT3423  :1;

    VOS_UINT32                          bitOpT3402  :1;
    VOS_UINT32                          bitOpRsv    :29;

    LMM_MMC_TIMER_STATE_ENUM_UINT32     enT3412State;
    LMM_MMC_TIMER_STATE_ENUM_UINT32     enT3423State;

    LMM_MMC_TIMER_STATE_ENUM_UINT32     enT3402State;
}LMM_MMC_TIMER_STATE_NOTIFY_STRU;


/*****************************************************************************
 结构名称: MMC_LMM_UE_OOC_STATUS_NOTIFY_STRU
 协议表格:
 ASN.1 描述:
 结构说明:  MMC通过此消息通知LMM进入出服务区流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
}MMC_LMM_UE_OOC_STATUS_NOTIFY_STRU;

/*****************************************************************************
 结构名称: NAS_GUMM_INFO_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    union
    {
        NAS_GUMM_PTMSI_STRU             stPtmsi;
        NAS_GUMM_PTMSI_SIGNATURE_STRU   stPtmsiSignature;
        NAS_GUMM_UMTS_CONTEXT_STRU      stSecuContext;
        MMC_LMM_LAI_STRU                stLai;
        MMC_LMM_RAI_STRU                stRAI;
        MMC_LMM_TMSI_STATUS_TYPE_ENUM_UINT32             ulTmsiStatus;
    }u;

} NAS_GUMM_INFO_STRU;


/****************************************************************************
 结构名称: NAS_LMM_INFO_STRU
 协议表格:
 ASN.1描述 :
 结构说明:
 *****************************************************************************/
typedef struct
{
    union
    {
        NAS_LMM_GUTI_STRU               stGuti;
        MMC_LMM_PLMN_ID_STRU            stPlmn;
        NAS_LMM_TAI_LIST_STRU           stForbRoamTaiList;
        NAS_LMM_TAI_LIST_STRU           stForbRposTaiList;
        MMC_LMM_PLMN_LIST_STRU          stCsDomainUnAvailPlmnList;
    }u;

} NAS_LMM_INFO_STRU;




/*****************************************************************************
 结构名称: MMC_LMM_PUB_INFO_STRU
 ????:
 ASN.1??:
 ????:
*****************************************************************************/
typedef struct
{
    union
    {
        MMC_LMM_TIN_TYPE_ENUM_UINT32    ulTinType;
        MMC_LMM_EPLMN_STRU              stEplmnList;
        MMC_LMM_PLMN_ID_STRU            stHplmn;
        MMC_LMM_PLMN_LIST_STRU          stForbiddenPlmnList;
        MMC_LMM_PLMN_LIST_STRU          stForbiddenPlmnListForGPRS;
        MMC_LMM_PLMN_LIST_STRU          stEHplmnList;
    }u;

} MMC_LMM_PUB_INFO_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_DISABLE_LTE_NOTIFY_STRU
 结构说明  : 通知L disable LTE
  1.日    期   : 2011年11月7日
    作    者   : z00161729
    修改内容   : 新建
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32                ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                                ulOpId;
    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32    enDisableLteReason;
} MMC_LMM_DISABLE_LTE_NOTIFY_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_ENABLE_LTE_NOTIFY_STRU
 结构说明  : 通知L enable LTE
  1.日    期   : 2011年11月7日
    作    者   : z00161729
    修改内容   : 新建
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32                ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                                ulOpId;
} MMC_LMM_ENABLE_LTE_NOTIFY_STRU;

/*****************************************************************************
 结构名称: MMC_LMM_CS_CONN_STATUS_NOTIFY_STRU
 协议表格:
 ASN.1 描述:
 结构说明:ID_MM_LMM_CONN_STATUS_NOTIFY_STRU
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
    VOS_UINT8                           ucCsRrConnStatusFlg;                    /* CS域RR连接是否存在,VOS_FALSE:不存在,VOS_TRUE:存在 */
    VOS_UINT8                           ucCsEmergencyConnStatusFlg;             /* 紧急呼叫链路是否存在,VOS_TRUE:存在，VOS_FALSE不存在 */
    VOS_UINT8                           aucReserved[2];
} MMC_LMM_CS_CONN_STATUS_NOTIFY_STRU;


/*****************************************************************************
 结构名    : MMC_LMM_SUSPEND_REL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MMC_LMM_SUSPEND_REL_REQ_STRU 的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
} MMC_LMM_SUSPEND_REL_REQ_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_UTRAN_MODE_REQ_STRU
 结构说明  : UTRAN的工作模式信息
 1.日    期   : 2012年7月14日
   作    者   : w00176964
   修改内容   : 新建

  2.日    期   : 2012年8月8日
    作    者   : w00167002
    修改内容   : 接口命名调整
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                         /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;           /*_H2ASN_Skip*/
    MMC_LMM_UTRAN_MODE_ENUM_UINT8       enUtranMode;       /* UTRAN的工作模式*/
    VOS_UINT8                           aucRsv[3];
} MMC_LMM_UTRAN_MODE_REQ_STRU;

/*****************************************************************************
 结构名    : MMC_UTRAN_MODE_CNF_STRU
 结构说明  : UTRAN的工作模式回复信息
 1.日    期   : 2012年8月8日
   作    者   : w00167002
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
}LMM_MMC_UTRAN_MODE_CNF_STRU;

/*****************************************************************************
 结构名    : LMM_MMC_SUSPEND_REL_CNF_STRU
 结构说明  :
 1.日    期   : 2012年11月21日
   作    者   : w00209181
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
} LMM_MMC_SUSPEND_REL_CNF_STRU;



/*****************************************************************************
 枚举名    : LMM_MMC_RAT_CHANGE_CAUSE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum LMM_MMC_SUSPEND_INFO_CHANGE_TYPE_ENUM
{
    LMM_MMC_SUSPEND_RAT_INFO_CHANGE   = 0,     /* CSFB的重定向过程中RAT发生改变*/
    LMM_MMC_SUSPEND_INFO_CHANGE_BUTT
};
typedef VOS_UINT32  LMM_MMC_SUSPEND_INFO_CHANGE_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LMM_MMC_RAT_CHANGE_CAUSE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum LMM_MMC_RAT_CHANGE_TYPE_ENUM
{
    LMM_MMC_RAT_CHANGE_G2W   = 0,
    LMM_MMC_RAT_CHANGE_W2G   = 1,
    LMM_MMC_RAT_CHANGE_TYPE_BUTT
};
typedef VOS_UINT32  LMM_MMC_RAT_CHANGE_TYPE_ENUM_UINT32;


/*****************************************************************************
 结构名称   : LMM_MMC_RAT_CHANGE_IND_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LMM_MMC_RAT_CHANGE_IND_STRU用于通知LMM底层的接入技术发生变化
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;


    LMM_MMC_SUSPEND_INFO_CHANGE_TYPE_ENUM_UINT32  ulInfoType;/*信息变更类型 : CSFB_REDIR_RAT_CHANGE;*/
    LMM_MMC_RAT_CHANGE_TYPE_ENUM_UINT32 ulRatChangeType;/* 枚举，两个值：U2G, G2U*/
    VOS_UINT8                           aucRsv[4];      /* 预留 */
}LMM_MMC_SUSPEND_INFO_CHANGE_NOTIFY_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_WCDMA_SYS_INFO_IND_STRU
 结构说明  : 通知L WCDMA系统消息
  1.日    期   : 2012年6月15日
    作    者   : n00181501
    修改内容   : 新建
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32                ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                                bitOpRac   :1;
    VOS_UINT32                                bitSpare   :31;

    MMC_LMM_PLMN_ID_STRU                      stPlmnId;
    VOS_UINT32                                ulCellId;
    VOS_UINT16                                usLac;
    VOS_UINT8                                 ucRac;
    VOS_UINT8                                 ucRsv1;
} MMC_LMM_WCDMA_SYS_INFO_IND_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_GSM_SYS_INFO_IND_STRU
 结构说明  : 通知L GSM系统消息
  1.日    期   : 2012年6月15日
    作    者   : n00181501
    修改内容   : 新建
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32                ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                                bitOpRac   :1;
    VOS_UINT32                                bitSpare   :31;

    MMC_LMM_PLMN_ID_STRU                      stPlmnId;
    VOS_UINT32                                ulCellId;
    VOS_UINT16                                usLac;
    VOS_UINT8                                 ucRac;
    VOS_UINT8                                 ucRsv1;
} MMC_LMM_GSM_SYS_INFO_IND_STRU;

/*****************************************************************************
 结构名    : LMM_MMC_EMC_PDP_STATUS_NOTIFY_STRU
 结构说明  : 通知MMC紧急承载的状态
  1.日    期   : 2013年12月03日
    作    者   : lihong00150010
    修改内容   : 新建
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32                ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                                 ucIsEmcPdpActive;   /* VOS_TRUE:表示紧急承载激活；VOS_FALSE:表示紧急承载未激活 */
    VOS_UINT8                                 aucRsv[3];
} LMM_MMC_EMC_PDP_STATUS_NOTIFY_STRU;

/*****************************************************************************
 结构名称: MMC_LMM_LTE_SYS_INFO_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* 当前小区的系统消息: PLMN_LIST, TAC, CELLID, 小区状态等 */
    MMC_LMM_SYS_INFO_STRU               stLteSysInfo;

} MMC_LMM_LTE_SYS_INFO_IND_STRU;

/*****************************************************************************
 结构名称: MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MMC_LMM_MSG_ID_ENUM_UINT32  ulMsgId;
    VOS_UINT32                  bitOpCurrCampPlmnId:1;
    VOS_UINT32                  bitSpare:31;
    MMC_LMM_PLMN_ID_STRU        stCurrCampPlmnId;
}MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_BEGIN_SESSION_NOTIFY_STRU
 结构说明  : SESSION开始指示
 1.日    期   : 2014年5月22日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;                /*_H2ASN_Skip*/
    MMC_LMM_SESSION_TYPE_ENUM_UINT8                 enSessionType;
    VOS_UINT8                                       aucReserved[3];
}MMC_LMM_BEGIN_SESSION_NOTIFY_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_END_SESSION_NOTIFY_STRU
 结构说明  : SESSION开结束指示
 1.日    期   : 2014年5月22日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;                /*_H2ASN_Skip*/
    MMC_LMM_SESSION_TYPE_ENUM_UINT8                 enSessionType;
    VOS_UINT8                                       aucReserved[3];
}MMC_LMM_END_SESSION_NOTIFY_STRU;


/*****************************************************************************
 结构名称: MMC_LMM_IMS_VOICE_CAP_NOTIFY_REQ_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    MMC_LMM_IMS_VOICE_CAP_ENUM_UINT8    enImsVoiceCap;
    VOS_UINT8                           aucRsv[3];
} MMC_LMM_IMS_VOICE_CAP_CHANGE_NOTIFY_STRU;


/*****************************************************************************
 结构名    : LMM_MMC_EMERGENCY_NUM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCategory;
    VOS_UINT8                           ucEmcNumLen;    /*紧急呼号码长度，即aucEmcNum的有效长度*/
    VOS_UINT8                           aucEmcNum[LMM_MMC_EMERGENCY_NUM_MAX_LEN];
} LMM_MMC_EMERGENCY_NUM_STRU;

/*****************************************************************************
 结构名    : LMM_MMC_INFO_CHANGE_NOTIFY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32              ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                              ulOpId;
    /*VOS_UINT32                              bitOpEmcNumList : 1;
    VOS_UINT32                              bitOpImsVoPS    : 1;
    VOS_UINT32                              bitOpEmcBS      : 1;
    VOS_UINT32                              bitOpLteCsCap   : 1;
    VOS_UINT32                              bitSpare        : 29;*/

    VOS_UINT8                               ucEmergencyNumAmount;
    VOS_UINT8                               aucReserved[3];
    LMM_MMC_EMERGENCY_NUM_STRU              astEmergencyNumList[LMM_MMC_EMERGENCY_NUM_LIST_MAX_RECORDS];

    LMM_MMC_NW_IMS_VOICE_ENUM_UINT32        enNwImsVoPS;
    LMM_MMC_NW_EMC_BS_ENUM_UINT32           enNwEmcBS;
    LMM_MMC_LTE_CS_CAPBILITY_ENUM_UINT32    enLteCsCap ;
} LMM_MMC_INFO_CHANGE_NOTIFY_STRU;

/*****************************************************************************
 结构名    : LMM_MMC_SIM_AUTH_FAIL_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 卡鉴权失败LMM通知MMC接口 20141103add
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MMC_LMM_MSG_ID_ENUM_UINT32              ulMsgId;

    LMM_MMC_SIM_AUTH_FAIL_ENUM_UINT16       enSimAuthFailValue;  /*卡鉴权失败返回的失败原因值*/
    LMM_MMC_SRV_DOMAIN_ENUM_UINT8           enSrvDomain;         /*服务域*/
    VOS_UINT8                               ucRsv;
} LMM_MMC_SIM_AUTH_FAIL_IND_STRU;

/*****************************************************************************
 结构名    : LMM_MMC_SEARCHED_PLMN_INFO_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32              ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                              ulTaiNum;           /*LRRC上报TAI个数*/
    NAS_LMM_TAI_STRU                        stTaiList[LMM_MMC_MAX_SEARCHED_TAI_NUM];    /*LRRC上报TAI列表*/
} LMM_MMC_SEARCHED_PLMN_INFO_IND_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ID_MMC_LMM_CELL_SIGN_REPORT_NOTIFY对应的结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MMC_LMM_MSG_ID_ENUM_UINT32              ulMsgId;
    VOS_UINT8                               ucMinRptTimerInterval;              /* 时间间隔，为0时:RSSI变化达到门限值时立即上报，门限的取值如下 */
    VOS_UINT8                               ucSignThreshold;                    /* 门限值，为0时:如果之前没有给接入层通知过有效值(1-5dB)，接入层用NV配置值；
                                                                                   如果之前给接入层通知过有效值，接入层仍然用上次的有效值 */
    VOS_UINT8                               aucReserve[2];
} MMC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU;

/*****************************************************************************
 结构名    : LMM_MMC_CQI_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE下的信道质量,两个码字分别代表子带CQI和宽带CQI
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usRI;                               /* RI值,1时仅ausCQI[0]有效；2时ausCQI[0]和ausCQI[1]均有效 */
    VOS_UINT8                               aucRes[2];
    VOS_UINT16                              ausCQI[2];                          /* channel quality indicator */
} LMM_MMC_CQI_INFO_STRU;

/*****************************************************************************
 结构名    : LMM_MMC_CELL_SIGN_REPORT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ID_LMM_MMC_CELL_SIGN_REPORT_IND对应的结构体，LTE下的Rssi及Rsrp，Rsrq,CQI
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MMC_LMM_MSG_ID_ENUM_UINT32              ulMsgId;
    VOS_INT16                               sRssi;                              /* received signal strength indicator */
    VOS_INT16                               sRsd;                               /* 填充字段*/
    VOS_INT16                               sRsrp;                              /* reference signal receive power   范围：(-141,-44), 99为无效 */
    VOS_INT16                               sRsrq;                              /* reference signal receive quality 范围：(-40, -6) , 99为无效 */
    VOS_INT32                               lSinr;                              /* signal to interference plus noise ratio */
    LMM_MMC_CQI_INFO_STRU                   stCQI;                              /* channel quality indicator */
} LMM_MMC_CELL_SIGN_REPORT_IND_STRU;

/*****************************************************************************
 结构名    : LMM_MMC_T3402_LEN_NOTIFY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : AT&T定制需求新增消息，通知MMC3402定时器时长
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MMC_LMM_MSG_ID_ENUM_UINT32              ulMsgId;

    VOS_UINT32                              ulOpId;
    VOS_UINT32                              ulT3402Len;   /* 3402定时器时长，单位:毫秒 */
} LMM_MMC_T3402_LEN_NOTIFY_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_VOICE_DOMAIN_CHANGE_IND_STRU
 结构说明  : ID_MMC_LMM_VOICE_DOMAIN_CHANGE_IND的结构体
  1.日    期   : 2015年01月21日
    作    者   : f00179208
    修改内容   : 新建
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32              ulMsgId;                            /*_H2ASN_Skip*/
    MMC_LMM_VOICE_DOMAIN_ENUM_UINT32        enVoiceDomain;                      /* 语音优选域 */
} MMC_LMM_VOICE_DOMAIN_CHANGE_IND_STRU;

/*****************************************************************************
 函数名称: LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY_STRU
 协议表格:
 ASN.1 描述:
 函数说明: 4G未开户定制需求新增消息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MMC_LMM_MSG_ID_ENUM_UINT32  ulMsgId;

    VOS_UINT32                  ulOpId;
    VOS_UINT32                  ulTimerLen;/*LTE不可用的时长，单位秒*/
    VOS_UINT8                   ucNetWorkTriggerFlag; /*0 网络没有带extCause，1网络带有extCause*/
    VOS_UINT8                   ucPlmnNum;  /*携带PLMN个数*/
    VOS_UINT8                   aucReserved[2];
    MMC_LMM_PLMN_ID_STRU        astPlmnIdList[MMC_LMM_MAX_EUTRAN_NOT_ALLOW_PLMN_NUM];
}LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_BG_SEARCH_HRPD_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ID_MMC_LMM_BG_SEARCH_HRPD_REQ对应的结构体，LTE下背景搜索HRPD
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32              ulMsgId;        /*_H2ASN_Skip*/

    VOS_UINT32                              ulOpId;
    VOS_UINT8                               aucRsv[4];
}MMC_LMM_BG_SEARCH_HRPD_REQ_STRU;

/*****************************************************************************
 结构名    : LMM_MMC_HRPD_SUBNET_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HRPD下SubnetID
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               aucSubnetId[LMM_MMC_HRPD_SUBNET_MAX_LEN];
    VOS_UINT16                              usBandClass;
    VOS_UINT16                              usFreq;
}LMM_MMC_HRPD_SYS_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_BG_SEARCH_HRPD_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ID_LMM_MMC_BG_SEARCH_HRPD_CNF对应的结构体，LTE下背景搜索HRPD的回复消息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32              ulMsgId;    /*_H2ASN_Skip*/
    VOS_UINT32                              ulOpId;

    MMC_LMM_BG_SRCH_RLT_ENUM_UINT32         enRlst;
    VOS_UINT8                               ucHrpdSysNum;
    VOS_UINT8                               aucRsv[3];
    LMM_MMC_HRPD_SYS_STRU                   astHrpdSysList[LMM_MMC_BG_HRPD_MAX_SYS_NUM];
}LMM_MMC_BG_SEARCH_HRPD_CNF_STRU;

/*****************************************************************************
 结构名    : MMC_LMM_STOP_BG_SEARCH_HRPD_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ID_MMC_LMM_STOP_BG_SEARCH_HRPD_REQ对应的结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32              ulMsgId;    /*_H2ASN_Skip*/

    VOS_UINT32                              ulOpId;
    VOS_UINT8                               aucRsv[4];
}MMC_LMM_STOP_BG_SEARCH_HRPD_REQ_STRU;

/*****************************************************************************
 结构名    : LMM_MMC_STOP_BG_SEARCH_HRPD_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ID_LMM_MMC_STOP_BG_SEARCH_HRPD_CNF对应的结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32              ulMsgId;    /*_H2ASN_Skip*/

    VOS_UINT32                              ulOpId;
    VOS_UINT8                               aucRsv[4];
}LMM_MMC_STOP_BG_SEARCH_HRPD_CNF_STRU;

/*****************************************************************************
 函数名称: Nas_GetGuInfo
 协议表格:
 ASN.1 描述:
 函数说明:
*****************************************************************************/
extern MMC_LMM_RESULT_ID_ENUM_UINT32  Nas_GetGuInfo
(
    NAS_GUMM_INFO_TYPE_ENUM_UINT32  ulInfoType,
    NAS_GUMM_INFO_STRU *            pstGuInfo
);



/*****************************************************************************
 函数名称: Nas_GetLteInfo
 协议表格:
 ASN.1 描述:
 函数说明:
*****************************************************************************/

extern MMC_LMM_RESULT_ID_ENUM_UINT32  Nas_GetLteInfo
(
    NAS_LMM_INFO_TYPE_ENUM_UINT32  ulInfoType,
    NAS_LMM_INFO_STRU             *pstLmmInfo
);

/*****************************************************************************
 函数名称: Nas_GetPubInfo
 协议表格:
 ASN.1 描述:
 函数说明:
*****************************************************************************/
extern MMC_LMM_RESULT_ID_ENUM_UINT32 Nas_GetPubInfo
(
    MMC_LMM_INFO_TYPE_ENUM_UINT32    ulInfoType,
    MMC_LMM_PUB_INFO_STRU           *pPubInfo
);


/*****************************************************************************
 函数名称: Nas_PlmnIdIsForbid
 函数说明:
*****************************************************************************/
MMC_LMM_PLMN_CTRL_ENUM_UINT32  Nas_PlmnIdIsForbid
(
    MMC_LMM_PLMN_ID_STRU     *pstPlmn
);


/*****************************************************************************
 函数名称: NAS_MM_PidInit
 函数说明: LMM PID初始化函数，用于MM FID初始化时调用
*****************************************************************************/
VOS_UINT32  NAS_MM_PidInit (    enum VOS_INIT_PHASE_DEFINE ip );

/*****************************************************************************
 函数名称: NAS_MM_PidMsgEntry
 函数说明: LMM消息入口函数，用于MM FID初始化时调用
*****************************************************************************/
extern void        NAS_MM_PidMsgEntry( MsgBlock *pMsg);

/*****************************************************************************
 函数名称: LTE_MsgHook
 函数说明: LTE消息勾取函数
*****************************************************************************/
extern VOS_UINT32 LTE_MsgHook( VOS_VOID *pMsg );

/*****************************************************************************
 函数名称: Nas_GetEutraUeCap
 协议表格:
 ASN.1 描述:
 函数说明:
*****************************************************************************/
extern MMC_LMM_RESULT_ID_ENUM_UINT32  Nas_GetEutraUeCap
(
    MMC_LMM_PLMN_ID_STRU stPlmnId,
    VOS_UINT16 *pusEUeCapDataLen,
    VOS_UINT8 *pucEUeCapData
);

typedef struct
{
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_MsgChoice_Export MMC_LMM_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MMC_LMM_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}MMC_LMM_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    MMC_LMM_INTERFACE_MSG_DATA           stMsgData;
} MmcLmmInterface_MSG;







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

#endif /* end of MmcLmmInterface.h */

















