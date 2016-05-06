/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : OmCommon.h
  Description     : OmCommon.h header file
  History         :
     1.heliping         2008-10-30  Draft Enact
     2.xiaojun 58160  2009-05-19  BJ9D00828  AppMmInterface.h中关于路测
                                    的公共定义移植到OmCommon.h中，利于各个模块公共使
                                    用、维护
     3.xiaojun 58160  2009-05-22  BJ9D00873  MSP组提供的key event id和air msg id
                                 的取值都超过了原来协议栈定义的8bit，需要做相应的修改
     4.zhangwei 00103912  2009-06-5  BJ9D01039 L2新增关键事件ID定义
     5.linyu    00161178  2009-10-23 BJ9D20173 RRC新增关键事件ID定义

******************************************************************************/

#ifndef __OMCOMMON_H__
#define __OMCOMMON_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include "vos.h"
#include "LPSCommon.h"
#include "AppL2Interface.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

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

/*key event id的取值范围在CP V100是0x10500~0x11099，这个和测试UE的key event id的定义
  typedef VOS_UINT8 OM_PS_KEY_EVENT_ENUM_UINT8  取值长度矛盾。
 解决方法：增加key evnet id 的偏移量*/
/* OM融合，工具EVENT ID只使用16位 */
#define OM_PS_KEY_EVENT_BASE_ID         0x4FF




/*PS 可维可测*/
/* 小区可带的最多PLMN个数 */
#define LPS_RRC_CSEL_MAX_FOUND_PLMN_COUNT           (6)

/* UE支持的同频或异频小区最大数目 */
#define LPS_LRRC_LPHY_MAX_FREQ_CELL_NUM                        33

/* 主模非LTE模时，UE支持的异频的最大数目是4，
   主模为LTE模时，UE支持的异频的最大数目是3 */
#define LPS_LRRC_LPHY_MAX_ADDITIONAL_CARRIER_NUM              4

/*最大承载数*/
#define LPS_NAS_ESM_MAX_EPSB_NUM            (11)
/* TA 列表最大个数 */

#define LPS_NAS_MM_MAX_TA_NUM     64

#define LPS_APP_MAX_IPV4_ADDR_LEN                               4
#define LPS_APP_MAX_IPV6_ADDR_LEN                               16

#define LPS_NAS_MM_MAX_UEID_BUF_SIZE        10                  /* UNIT: BYTE  */

#define MSP_L3_PID_DT  MSP_PID_DIAG_APP_AGENT
#define L3_MSP_PID_DT  MSP_PID_DIAG_APP_AGENT
#define L3_MSP_PID_DT_IND  MSP_PID_DIAG_AGENT



/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/* Msg ID包括4部分:
-----------------------------------------------------------------
  字节高位                                      字节低位
-----------------------------------------------------------------
| BYTE1  |  BYTE2    |   BYTE3    |    BYTE4   |
-----------------------------------------------------------------
BYTE1 消息类型:
                取值参考UE_MSG_TYPE枚举的定义

BYTE2 源模块号:
                取值范围是 UE_FUNC_MODULE_ID_ENUM 和 UE_APP_MODULE_ID_ENUM的定义


BYTE3 目的模块号:
                取值范围同BYTE2

BYTE4  消息号:0~255
*/

/*****************************************************************************
 结构名    : OM_PS_COMM_CMD_ENUM
 结构说明  : OM和协议栈间的公共功能的接口消息定义
*****************************************************************************/
enum OM_PS_COMM_CMD_ENUM
{
    /*------------------- 协议栈和OM间公共功能的接口的命令 -------------------*/
    /*空口消息上报*/
    PS_OMT_AIR_MSG_REPORT_IND       =
            DEF_MSG(ENUM_AIR_MSG, UE_MODULE_PS_ID, UE_APP_SUBSYS_ID, 0x01),

    /*关键事件上报MM(SM/RRC/L2)->OM->OMT */
    PS_OMT_KEY_EVT_REPORT_IND       =
            DEF_MSG(ENUM_KEY_EVENT_MSG, UE_MODULE_PS_ID, UE_APP_SUBSYS_ID, 0x01),

    /*透明命令,OM发送给PS各个模块的统一的透明消息的定义*/
    OM_PS_TRANSPARENT_CMD_REQ       =
            DEF_MSG(ENUM_TRANSPARENT_MSG, UE_APP_SUBSYS_ID, UE_MODULE_PS_ID, 0x01),

    OM_PS_TRANSPARENT_CMD_CNF       =
            DEF_MSG(ENUM_TRANSPARENT_MSG, UE_MODULE_PS_ID, UE_APP_SUBSYS_ID, 0x01)

};
typedef VOS_UINT32 OM_PS_COMM_CMD_ENUM_UINT32;

/*****************************************************************************
 结构名    : OM_CMD_ENUM
 结构说明  : OMT和OM的各个模块间的消息定义
*****************************************************************************/
enum OM_CMD_ENUM
{
    /*---------------------------- OM和OMT的ulMsgId --------------------------*/
    /*OMAGENT 与OM之间的握手消息原语*/
    OMAGENT_OM_HANDSHAKE_REQ        =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_APP_SUBSYS_ID, UE_MODULE_OM_ID, 00),

    OM_OMAGENT_HANDSHAKE_CNF        =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_MODULE_OM_ID, UE_APP_SUBSYS_ID, 00),
    /*OMAGENT 与OM之间的心跳消息原语*/
    OMAGENT_OM_HEART_REQ =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_MODULE_OM_AGENT_ID, UE_MODULE_OM_ID, 0x01),
    OM_OMAGENT_HEART_CNF =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_MODULE_OM_ID, UE_MODULE_OM_AGENT_ID, 0x01),

    /*OMT配置层间消息开启关闭  OMT<->OM 普通命令*/
    OMT_OM_HOOKTRACE_CONFIG_REQ     =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_APP_SUBSYS_ID, UE_MODULE_OM_ID, 01),

    OM_OMT_HOOKTRACE_CONFIG_CNF     =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_MODULE_OM_ID, UE_APP_SUBSYS_ID, 01),

    /*OMT配置所有模块log级别  OMT<->OM 普通命令*/
    OMT_OM_LOG_CONFIG_REQ           =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_APP_SUBSYS_ID, UE_MODULE_OM_ID, 02),

    OM_OMT_LOG_CONFIG_CNF           =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_MODULE_OM_ID, UE_APP_SUBSYS_ID, 02),

    /*OMT对个别模块log级别的配置  OMT<->OM 普通命令*/
    OMT_OM_SET_PS_LOGPRINT_LEV_REQ  =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_APP_SUBSYS_ID, UE_MODULE_OM_ID, 03),

    OM_OMT_SET_PS_LOGPRINT_LEV_CNF  =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_MODULE_OM_ID, UE_APP_SUBSYS_ID, 03),

    /*OMT配置PS具体模块的空口消息跟踪标志 OMT<-> 普通命令*/
    OMT_OM_SET_AIR_MSG_TRACE_REQ    =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_APP_SUBSYS_ID, UE_MODULE_OM_ID, 04),

    OM_OMT_SET_AIR_MSG_TRACE_CNF    =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_MODULE_OM_ID, UE_APP_SUBSYS_ID, 04),


    /*L2 LOG配置接口 OMT->MASTER OM->HPA->L2 OM Agent*/
    OMT_L2_LOG_CONFIG_REQ           =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_MODULE_OM_ID, UE_MODULE_OM_SLAVE_ID, 00),

    /*L2 LOG消息配置结果 L2 OM Agent->HPA->MASTER OM->OMT*/
    L2_OMT_LOG_CONFIG_CNF           =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_MODULE_OM_SLAVE_ID, UE_MODULE_OM_ID, 00)

};
typedef VOS_UINT32 OM_CMD_ENUM_UINT32;


/*****************************************************************************
 结构名    : PS_OM_KEY_EVENT_ENUM
 结构说明  : 关键事件的取值的定义
*****************************************************************************/
enum OM_PS_KEY_EVENT_ENUM
{
    /*--------------------RRC报告的key event--------------------*/
    RRC_OM_KEY_EVENT_CELL_SEARCH_SPEC_PLMN       = 1,
    RRC_OM_KEY_EVENT_CELL_SEARCH_PLMN_LIST,
    RRC_OM_KEY_EVENT_CELL_SEARCH_SUIT,
    RRC_OM_KEY_EVENT_CELL_SEARCH_ANYCELL,
    RRC_OM_KEY_EVENT_SIB_RCV,
    RRC_OM_KEY_EVENT_CELL_CAMPED_ON,
    RRC_OM_KEY_EVENT_CELL_RESEL,
    RRC_OM_KEY_EVENT_RRC_CONN_SETUP,
    RRC_OM_KEY_EVENT_RRC_CONN_RELEASE,
    RRC_OM_KEY_EVENT_RB_SETUP,
    RRC_OM_KEY_EVENT_HANDOVER_START,
    RRC_OM_KEY_EVENT_RRC_CONN_REEST,
    RRC_OM_KEY_EVENT_SMC,
    RRC_OM_KEY_EVENT_RRC_CONN_REQ,
    RRC_OM_KEY_EVENT_RRC_CONN_SETUP_CMPL,
    RRC_OM_KEY_EVENT_HANDOVER_SUCC,
    RRC_OM_KEY_EVENT_RRC_UE_CAP_ENQUIRE,
    RRC_OM_KEY_EVENT_W2L_RESEL_STRAT,
    RRC_OM_KEY_EVENT_W2L_RESEL_SUCC,
    RRC_OM_KEY_EVENT_W2L_RESEL_FAIL,
    RRC_OM_KEY_EVENT_W2L_REDIRECTED_STRAT,
    RRC_OM_KEY_EVENT_W2L_REDIRECTED_SUCC,
    RRC_OM_KEY_EVENT_W2L_REDIRECTED_FAIL,
    RRC_OM_KEY_EVENT_W2L_HANDOVER_STRAT,
    RRC_OM_KEY_EVENT_W2L_HANDOVER_SUCC,
    RRC_OM_KEY_EVENT_W2L_HANDOVER_FAIL,
    RRC_OM_KEY_EVENT_W2L_GETUECAPINFO_STRAT,
    RRC_OM_KEY_EVENT_W2L_GETUECAPINFO_SUCC,
    RRC_OM_KEY_EVENT_W2L_GETUECAPINFO_FAIL,
    RRC_OM_KEY_EVENT_W2L_PLMN_SEARCH_STRAT,
    RRC_OM_KEY_EVENT_W2L_PLMN_SEARCH_SUCC,
    RRC_OM_KEY_EVENT_W2L_PLMN_SEARCH_FAIL,
    RRC_OM_KEY_EVENT_L2W_RESEL_START,
    RRC_OM_KEY_EVENT_L2W_RESEL_SUCC,
    RRC_OM_KEY_EVENT_L2W_RESEL_FAIL,
    RRC_OM_KEY_EVENT_L2W_REDIRECTED_START,
    RRC_OM_KEY_EVENT_L2W_REDIRECTED_SUCC,
    RRC_OM_KEY_EVENT_L2W_REDIRECTED_FAIL,
    RRC_OM_KEY_EVENT_L2W_HANDOVER_START,
    RRC_OM_KEY_EVENT_L2W_HANDOVER_SUCC,
    RRC_OM_KEY_EVENT_L2W_HANDOVER_FAIL,
    RRC_OM_KEY_EVENT_L2W_GETUECAPINFO_START,
    RRC_OM_KEY_EVENT_L2W_GETUECAPINFO_SUCC,
    RRC_OM_KEY_EVENT_L2W_GETUECAPINFO_FAIL,
    RRC_OM_KEY_EVENT_G2L_RESEL_STRAT,
    RRC_OM_KEY_EVENT_G2L_RESEL_SUCC,
    RRC_OM_KEY_EVENT_G2L_RESEL_FAIL,
    RRC_OM_KEY_EVENT_G2L_REDIRECTED_STRAT,
    RRC_OM_KEY_EVENT_G2L_REDIRECTED_SUCC,
    RRC_OM_KEY_EVENT_G2L_REDIRECTED_FAIL,
    RRC_OM_KEY_EVENT_G2L_HANDOVER_STRAT,
    RRC_OM_KEY_EVENT_G2L_HANDOVER_SUCC,
    RRC_OM_KEY_EVENT_G2L_HANDOVER_FAIL,
    RRC_OM_KEY_EVENT_G2L_CCO_STRAT,
    RRC_OM_KEY_EVENT_G2L_CCO_SUCC,
    RRC_OM_KEY_EVENT_G2L_CCO_FAIL,
    RRC_OM_KEY_EVENT_L2G_RESEL_START,
    RRC_OM_KEY_EVENT_L2G_RESEL_SUCC,
    RRC_OM_KEY_EVENT_L2G_RESEL_FAIL,
    RRC_OM_KEY_EVENT_L2G_REDIRECTED_START,
    RRC_OM_KEY_EVENT_L2G_REDIRECTED_SUCC,
    RRC_OM_KEY_EVENT_L2G_REDIRECTED_FAIL,
    RRC_OM_KEY_EVENT_L2G_HANDOVER_START,
    RRC_OM_KEY_EVENT_L2G_HANDOVER_SUCC,
    RRC_OM_KEY_EVENT_L2G_HANDOVER_FAIL,
    RRC_OM_KEY_EVENT_L2G_CCO_START,
    RRC_OM_KEY_EVENT_L2G_CCO_SUCC,
    RRC_OM_KEY_EVENT_L2G_CCO_FAIL,
    RRC_OM_KEY_EVENT_L2G_GETUECAPINFO_START,
    RRC_OM_KEY_EVENT_L2G_GETUECAPINFO_SUCC,
    RRC_OM_KEY_EVENT_L2G_GETUECAPINFO_FAIL,
    RRC_OM_KEY_EVENT_L2C_RESEL_FAIL,
    RRC_OM_KEY_EVENT_L2C_REDIR_FAIL,
    RRC_OM_KEY_EVENT_L2C_RESEL_START,
    RRC_OM_KEY_EVENT_L2C_RESEL_SUCC,
    RRC_OM_KEY_EVENT_C2L_RESEL_STRAT,
    RRC_OM_KEY_EVENT_C2L_RESEL_SUCC,
    RRC_OM_KEY_EVENT_C2L_RESEL_FAIL,

    /*--------------------NAS报告的key event--------------------*/
    MM_KEY_EVENT_PLMN_SPEC_SEARCH_START ,
    MM_KEY_EVENT_PLMN_LIST_SEARCH_START,
    MM_KEY_EVENT_PLMN_SEARCH_SUCC,
    MM_KEY_EVENT_PLMN_SEARCH_FAIL,
    MM_KEY_EVENT_START_AUTO_RESEL,
    MM_KEY_EVENT_START_MANUAL_RESEL,
    MM_KEY_EVENT_PLMN_RESEL_CNF,
    MM_KEY_EVENT_COVERAGE_LOST,

    MM_KEY_EVENT_ATTACH_REQ,
    MM_KEY_EVENT_ATTACH_ACP,
    MM_KEY_EVENT_ATTACH_CMP,
    MM_KEY_EVENT_ATTACH_REJ,

    MM_KEY_EVENT_DETACH_REQ_MT,
    MM_KEY_EVENT_DETACH_ACP_MT,
    MM_KEY_EVENT_DETACH_REQ_MO,
    MM_KEY_EVENT_DETACH_ACP_MO,

    MM_KEY_EVENT_TAU_REQ,
    MM_KEY_EVENT_TAU_ACP,
    MM_KEY_EVENT_TAU_CMP,
    MM_KEY_EVENT_TAU_REJ,

    MM_KEY_EVENT_SER_REQ,
    MM_KEY_EVENT_SER_REJ,
    MM_KEY_EVENT_SER_ACP,

    MM_KEY_EVENT_GUTI_CMD,
    MM_KEY_EVENT_GUTI_CMP,

    MM_KEY_EVENT_IDEN_REQ,
    MM_KEY_EVENT_IDEN_RSP,

    MM_KEY_EVENT_AUTH_REQ,
    MM_KEY_EVENT_AUTH_FAIL,
    MM_KEY_EVENT_AUTH_RSP,
    MM_KEY_EVENT_AUTH_REJ,

    MM_KEY_EVENT_SECU_CMD,
    MM_KEY_EVENT_SECU_CMP,
    MM_KEY_EVENT_SECU_REJ,

    MM_KEY_EVENT_EMM_STATUS,
    MM_KEY_EVENT_EMM_INFO,

    MM_KEY_EVENT_EMM_UPLINK_NAS_TRANSPORT,
    MM_KEY_EVENT_EMM_DOWNLINK_NAS_TRANSPORT,

    MM_KEY_EVENT_EXTENDED_SER_REQ,              /* 2012-02-24 */
    MM_KEY_EVENT_CS_SER_NOTIFICATION,           /* 2012-02-24 */

    ESM_KEY_EVENT_BEARER_5_SETUP,
    ESM_KEY_EVENT_BEARER_5_MODIFY,
    ESM_KEY_EVENT_BEARER_5_RELEASE,

    ESM_KEY_EVENT_BEARER_6_SETUP,
    ESM_KEY_EVENT_BEARER_6_MODIFY,
    ESM_KEY_EVENT_BEARER_6_RELEASE,

    ESM_KEY_EVENT_BEARER_7_SETUP,
    ESM_KEY_EVENT_BEARER_7_MODIFY,
    ESM_KEY_EVENT_BEARER_7_RELEASE,

    ESM_KEY_EVENT_BEARER_8_SETUP,
    ESM_KEY_EVENT_BEARER_8_MODIFY,
    ESM_KEY_EVENT_BEARER_8_RELEASE,

    ESM_KEY_EVENT_BEARER_9_SETUP,
    ESM_KEY_EVENT_BEARER_9_MODIFY,
    ESM_KEY_EVENT_BEARER_9_RELEASE,

    ESM_KEY_EVENT_BEARER_10_SETUP,
    ESM_KEY_EVENT_BEARER_10_MODIFY,
    ESM_KEY_EVENT_BEARER_10_RELEASE,

    ESM_KEY_EVENT_BEARER_11_SETUP,
    ESM_KEY_EVENT_BEARER_11_MODIFY,
    ESM_KEY_EVENT_BEARER_11_RELEASE,

    ESM_KEY_EVENT_BEARER_12_SETUP,
    ESM_KEY_EVENT_BEARER_12_MODIFY,
    ESM_KEY_EVENT_BEARER_12_RELEASE,

    ESM_KEY_EVENT_BEARER_13_SETUP,
    ESM_KEY_EVENT_BEARER_13_MODIFY,
    ESM_KEY_EVENT_BEARER_13_RELEASE,

    ESM_KEY_EVENT_BEARER_14_SETUP,
    ESM_KEY_EVENT_BEARER_14_MODIFY,
    ESM_KEY_EVENT_BEARER_14_RELEASE,

    ESM_KEY_EVENT_BEARER_15_SETUP,
    ESM_KEY_EVENT_BEARER_15_MODIFY,
    ESM_KEY_EVENT_BEARER_15_RELEASE,

    /*--------------------L2报告的key event--------------------*/
    /*L2_KEY_EVENT_XYZ       = 41,*/
    L2_KEY_EVENT_PDCP_SETUP_SUCC,           /* PDCP实体建立成功 */
    L2_KEY_EVENT_PDCP_SETUP_FAIL,           /* PDCP实体建立失败 */
    L2_KEY_EVENT_PDCP_REEST_START,          /* PDCP重建立开始 */
    L2_KEY_EVENT_PDCP_REEST_SUCC,           /* PDCP重建立成功 */
    L2_KEY_EVENT_PDCP_REEST_FAIL,           /* PDCP重建立失败 */
    L2_KEY_EVENT_PDCP_ACTIVE_CIPHER,        /* PDCP激活安全特性 */
    L2_KEY_EVENT_PDCP_ACTIVE_CIPHER_FAIL,   /* PDCP激活安全特性失败 */
    L2_KEY_EVENT_PDCP_CHANGE_KEY,           /* PDCP安全特性更换密钥 */
    L2_KEY_EVENT_PDCP_CHANGE_ALG,           /* PDCP安全特性更换算法 */
    L2_KEY_EVENT_PDCP_RELEASE,              /* PDCP实体释放 */
    L2_KEY_EVENT_PDCP_ULBUF_FULL,           /* PDCP上行缓存满 */
    L2_KEY_EVENT_PDCP_DLBUF_FULL,           /* PDCP下行缓存满 */
    L2_KEY_EVENT_PDCP_INTE_VERIFY_FAIL,     /* PDCP完整性检查失败 */

    L2_KEY_EVENT_RLC_STABLISH_SUCC,  /*92*/
    L2_KEY_EVENT_RLC_STABLISH_FAIL,
    L2_KEY_EVENT_RLC_RECFG_SUCC,
    L2_KEY_EVENT_RLC_RECFG_FAIL,
    L2_KEY_EVENT_RLC_RESTABLISH_SUCC,
    L2_KEY_EVENT_RLC_RESTABLISH_FAIL,
    L2_KEY_EVENT_RLC_RELEASE_SUCC,
    L2_KEY_EVENT_RLC_RELEASE_FAIL,
    L2_KEY_EVENT_RLC_RETX_TIMES_FULL,   /*RLC AM PDU达到最大重传次数*/
    L2_KEY_EVENT_RLC_CTRL_PDU_ERROR,    /*RLC AM 接收到的状态PDU错误*/
    L2_KEY_EVENT_RLC_PDU_LI_ERROR,      /*RLC下行接到的PDU LI字段填写异常*/


    L2_KEY_EVENT_MAC_SETUP_SUCC,
    L2_KEY_EVENT_MAC_SETUP_FAIL,
    L2_KEY_EVENT_MAC_RESET_SUCC,
    L2_KEY_EVENT_MAC_RESET_FAIL,
    L2_KEY_EVENT_MAC_RELEASE_SUCC,
    L2_KEY_EVENT_MAC_RELEASE_FAIL,
    L2_KEY_EVENT_MAC_RA_SUCC,
    L2_KEY_EVENT_MAC_RA_FAIL,
    L2_KEY_EVENT_MAC_RACH_SUCC,
    L2_KEY_EVENT_MAC_RACH_FAIL,
    L2_KEY_EVENT_MAC_RANDOM_ACCESS_SUCC,
    L2_KEY_EVENT_MAC_RANDOM_ACCESS_FAIL,
    L2_KEY_EVENT_HO_MAC_RX_L3_RA_IND,
    L2_KEY_EVENT_HO_MAC_TX_PREAMBLE,
    L2_KEY_EVENT_HO_MAC_RANDACCESS_SUCC,
    L2_KEY_EVENT_HO_MAC_RX_LAST_PDU,
    L2_KEY_EVENT_HO_MAC_RX_FIRST_PDU,
    L2_KEY_EVENT_HO_MAC_TX_LAST_PDU,
    L2_KEY_EVENT_HO_MAC_TX_FIRST_PDU,
    L2_KEY_EVENT_HO_MAC_RX_LAST_ULGRANT,
    L2_KEY_EVENT_HO_MAC_RX_FIRST_ULGRANT,
    L2_KEY_EVENT_HO_RLC_RX_LAST_PDU,
    L2_KEY_EVENT_HO_RLC_RX_FIRST_PDU,
    L2_KEY_EVENT_HO_RLC_TX_LAST_PDU,
    L2_KEY_EVENT_HO_RLC_TX_FIRST_PDU,
    L2_KEY_EVENT_HO_PDCP_DL_STOP_TIME,
    L2_KEY_EVENT_HO_PDCP_DL_CONTINUE_TIME,
    L2_KEY_EVENT_HO_PDCP_UL_STOP_TIME,
    L2_KEY_EVENT_HO_PDCP_UL_CONTINUE_TIME,

    /* 由于影响路测，下面两条关键事件放到最后面*/
    MM_KEY_EVENT_EMM_DOWNLINK_GENERIC_NAS_TRANSPORT,
    MM_KEY_EVENT_EMM_UPLINK_GENERIC_NAS_TRANSPORT,

    /*V7R2-DT增加MCE激活/去激活SCell、DeactivationTimer超时去激活SCell、RRC去激活SCELL事件枚举的代码 q00208938 2014/03/24，begin*/
    L2_MCE_DEACTIVE_SCELL1,
    L2_MCE_DEACTIVE_SCELL2,
    L2_MCE_DEACTIVE_SCELL3,
    L2_MCE_DEACTIVE_SCELL4,
    L2_MCE_DEACTIVE_SCELL5,
    L2_MCE_DEACTIVE_SCELL6,
    L2_MCE_DEACTIVE_SCELL7,

    L2_MCE_ACTIVE_SCELL1,
    L2_MCE_ACTIVE_SCELL2,
    L2_MCE_ACTIVE_SCELL3,
    L2_MCE_ACTIVE_SCELL4,
    L2_MCE_ACTIVE_SCELL5,
    L2_MCE_ACTIVE_SCELL6,
    L2_MCE_ACTIVE_SCELL7,

    L2_DEACTIVATIONTIMER_TIMEOUT_SCELL1,
    L2_DEACTIVATIONTIMER_TIMEOUT_SCELL2,
    L2_DEACTIVATIONTIMER_TIMEOUT_SCELL3,
    L2_DEACTIVATIONTIMER_TIMEOUT_SCELL4,
    L2_DEACTIVATIONTIMER_TIMEOUT_SCELL5,
    L2_DEACTIVATIONTIMER_TIMEOUT_SCELL6,
    L2_DEACTIVATIONTIMER_TIMEOUT_SCELL7,

    RRC_DEACTIVE_SCELL1,
    RRC_DEACTIVE_SCELL2,
    RRC_DEACTIVE_SCELL3,
    RRC_DEACTIVE_SCELL4,
    RRC_DEACTIVE_SCELL5,
    RRC_DEACTIVE_SCELL6,
    RRC_DEACTIVE_SCELL7
    /*V7R2-DT增加MCE激活/去激活SCell、DeactivationTimer超时去激活SCell、RRC去激活SCELL事件枚举的代码 q00208938 2014/03/24，end*/
};
typedef VOS_UINT8 OM_PS_KEY_EVENT_ENUM_UINT8;

/*****************************************************************************
 结构名    : OM_PS_AIR_MSG_ENUM
 结构说明  : 空口消息的取值的定义
*****************************************************************************/
enum OM_PS_AIR_MSG_ENUM
{
    /*RRC的空口消息定义*/
    RRC_OM_CDMA2000_CSFB_PARAM_REQ     = 0,
    RRC_OM_CDMA2000_CSFB_PARAM_RSP     = 1,
    RRC_OM_CNT_CHK                     = 2,
    RRC_OM_CNT_CHK_RSP                 = 3,
    RRC_OM_DL_INFO_TRANSF              = 4,
    RRC_OM_HO_FROM_EUTRA_PREP_REQ      = 5,
    RRC_OM_MASTER_INFO_BLOCK           = 6,
    RRC_OM_MEAS_RPRT                   = 7,
    RRC_OM_MOBIL_FROM_EUTRA_CMD        = 8,
    RRC_OM_PAGING                      = 9,
    RRC_OM_CONN_RECFG                  = 10,
    RRC_OM_CONN_RECFG_CMP              = 11,
    RRC_OM_CONN_REESTAB                = 12,
    RRC_OM_CONN_REESTAB_CMP            = 13,
    RRC_OM_CONN_REESTAB_REJ            = 14,
    RRC_OM_CONN_REESTAB_REQ            = 15,
    RRC_OM_CONN_REJ                    = 16,
    RRC_OM_CONN_REL                    = 17,
    RRC_OM_CONN_REQ                    = 18,
    RRC_OM_CONN_SETUP                  = 19,
    RRC_OM_CONN_SETUP_CMP              = 20,
    RRC_OM_SECUR_MODE_CMD              = 21,
    RRC_OM_SECUR_MODE_CMP              = 22,
    RRC_OM_SECUR_MODE_FAIL             = 23,
    RRC_OM_SYS_INFO                    = 24,
    RRC_OM_SIB_TYPE1                   = 25,
    RRC_OM_UE_CAP_ENQUIRY              = 26,
    RRC_OM_UE_CAP_INFO                 = 27,
    RRC_OM_UL_HO_PREP_TRANSF           = 28,
    RRC_OM_UL_INFO_TRANSF              = 29,

    RRC_OM_INTER_RAT_MSG               = 30,
    RRC_OM_HO_CMD                      = 31,
    RRC_OM_HO_PREP_INFO                = 32,
    RRC_OM_UE_RADIO_ACCESS_CAP_INFO    = 33,
    RRC_OM_CONN_RECFG_MOBILE_CONTROL   = 34,

    RRC_OM_HO_CMD_RECFG                = 35,

    RRC_OM_UE_INFO_REQ               = 36,
    RRC_OM_UE_INFO_RSP               = 37,
    RRC_OM_PROXIMITY_IND             = 38,

    /* MBMS Begin */
    RRC_OM_MCCH_MSG                  = 39,
    /* MBMS End */


    /* v7r2 begin */
    RRC_OM_SIB1_V8h0_IES_MSG         = 40,
    RRC_OM_SIB2_V8h0_IES_MSG         = 41,
    RRC_OM_SIB5_V8h0_IES_MSG         = 42,
    RRC_OM_SIB6_V8h0_IES_MSG         = 43,

    RRC_0M_LOGGED_MEASUREMENT_CFG    = 44,

    /* v7r2 end */
    RRC_OM_EUTRA_CAP                 = 45,

    RRC_OM_MBMS_COUNTING_RSP         = 46,
    RRC_OM_CONN_REL_V9e0_IES_MSG     = 47,
    RRC_OM_UE_ASSIS_INFO             = 48,
    RRC_OM_UE_IDC_IND                = 49,
    RRC_OM_MBMS_INTEREST_IND         = 50,
    RRC_OM_INTER_FREQ_RSTD_MEAS_IND  = 51,
    RRC_AIR_MSG_END                  = 52,

    /*LPP AIR MSG ID*/
    LNAS_LPP_REQ_CAP                 = 80,
    LNAS_LPP_PROV_CAP                = 81,
    LNAS_LPP_REQ_ASSIST_DATA         = 82,
    LNAS_LPP_PROV_ASSIST_DATA        = 83,
    LNAS_LPP_REQ_LOC_INFO            = 84,
    LNAS_LPP_PROV_LOC_INFO           = 85,
    LNAS_LPP_ABORT_UP                = 86,
    LNAS_LPP_ABORT_DN                = 87,
    LNAS_LPP_ERROR_UP                = 88,
    LNAS_LPP_ERROR_DN                = 89,
    LNAS_LPP_ACK_UP                  = 90,
    LNAS_LPP_ACK_DN                  = 91,
    LNAS_LPP_DN_MSG_PARA_ERR         = 92,

    /* NAS组空口消息定义*/
    /* LCS空口消息 */
    LCS_REGISTER                    = 70,
    LCS_FACILITY                    = 71,
    LCS_RELEASE_COMPLTE             = 72,

    /* ESM 空口消息 */
    ESM_ACT_DEFLT_EPS_BEARER_CNTXT_REQ = 100,
    ESM_ACT_DEFLT_EPS_BEARER_CNTXT_ACP,
    ESM_ACT_DEFLT_EPS_BEARER_CNTXT_REJ,

    ESM_ACT_DEDICT_EPS_BEARER_CNTXT_REQ,
    ESM_ACT_DEDICT_EPS_BEARER_CNTXT_ACP,
    ESM_ACT_DEDICT_EPS_BEARER_CNTXT_REJ,

    ESM_MOD_EPS_BEARER_CNTXT_REQ,
    ESM_MOD_EPS_BEARER_CNTXT_ACP,
    ESM_MOD_EPS_BEARER_CNTXT_REJ,

    ESM_DEACT_EPS_BEARER_CNTXT_REQ,
    ESM_DEACT_EPS_BEARER_CNTXT_ACP,

    ESM_PDN_CONNECT_REQ,
    ESM_PDN_CONNECT_REJ,

    ESM_PDN_DISCONNECT_REQ,
    ESM_PDN_DISCONNECT_REJ,

    ESM_BEARER_RESOUCE_ALLOC_REQ,
    ESM_BEARER_RESOUCE_ALLOC_REJ,

    ESM_BEARER_RESOUCE_MOD_REQ,
    ESM_BEARER_RESOUCE_MOD_REJ,

    ESM_INFO_REQ,
    ESM_INFO_RSP,

    ESM_STUS_MT,
    ESM_STUS_MO,

    ESM_NOTIFICATION_MT,

    /* EMM 空口消息 */
    MM_ATTACH_REQ,
    MM_ATTACH_ACP,
    MM_ATTACH_CMP,
    MM_ATTACH_REJ,

    MM_DETACH_REQ_MT,
    MM_DETACH_ACP_MT,
    MM_DETACH_REQ_MO,
    MM_DETACH_ACP_MO,

    MM_TAU_REQ,
    MM_TAU_ACP,
    MM_TAU_CMP,
    MM_TAU_REJ,

    MM_SER_REQ,
    MM_SER_REJ,
    MM_SER_ACP,

    MM_GUTI_CMD,
    MM_GUTI_CMP,

    MM_IDEN_REQ,
    MM_IDEN_RSP,

    MM_AUTH_REQ,
    MM_AUTH_FAIL,
    MM_AUTH_RSP,
    MM_AUTH_REJ,

    MM_SECU_CMD,
    MM_SECU_CMP,
    MM_SECU_REJ,

    MM_EMM_STATUS,

    TC_ACT_TEST_MODE,
    TC_ACT_TEST_MODE_CMP,

    TC_DEACT_TEST_MODE,
    TC_DEACT_TEST_MODE_CMP,

    TC_CLOSE_UE_TEST_LOOP,
    TC_CLOSE_UE_TEST_LOOP_CMP,

    TC_OPEN_UE_TEST_LOOP,
    TC_OPEN_UE_TEST_LOOP_CMP,

    MM_EMM_INFO,

    MM_EMM_DOWNLINK_NAS_TRANSPORT,
    MM_EMM_UPLINK_NAS_TRANSPORT,

    MM_EXTENDED_SER_REQ,                /* 2012-02-24 */
    MM_CS_SER_NOTIFICATION,             /* 2012-02-24 */

    MM_EMM_DOWNLINK_GENERIC_NAS_TRANSPORT,
    MM_EMM_UPLINK_GENERIC_NAS_TRANSPORT,

    TC_RESET_POSITION_INFO

    /*L2组的空口消息定义*/
    /*PDCP_RRC_DATA_REQ      = 200,
    PDCP_RRC_DATA_IND,

    PDCP_RABM_DATA_REQ,
    PDCP_RABM_DATA_IND,

    PDCP_RLC_DATA_REQ,
    PDCP_RLC_DATA_IND,

    MAC_PHY_UL_FEEDBACK_IND,
    MAC_PHY_DCI_IND,
    MAC_PHY_CQI_IND,
    MAC_PHY_LOOP_IND,

    LMAC_DLCOM_PBCH,
    LMAC_DLCOM_PDSCH,
    LMAC_DLCOM_PRNTI,
    LMAC_DLCOM_SIRNTI,*/


};
typedef VOS_UINT8 OM_PS_AIR_MSG_ENUM_UINT8;

/*****************************************************************************
 结构名    : DT_CMD_ENUM
 结构说明  : DT命令枚举
*****************************************************************************/
enum DT_CMD_ENUM
{
    DT_CMD_STOP,        /*停止*/
    DT_CMD_START,       /*启动*/
    DT_CMD_BUTT
};
typedef VOS_UINT8 DT_CMD_ENUM_UINT8;

/*****************************************************************************
 结构名    : DT_RESULT_ENUM
 结构说明  : DT操作结果枚举
*****************************************************************************/
enum DT_RESULT_ENUM
{
    DT_RESULT_SUCC = 0,
    DT_RESULT_FAIL,
    DT_RESULT_NOT_SUPPORT_MEASURE,                /*当前不支持的测量*/

    /**********各自模块分别在下面增加需要的结果值********/
    /*RRC模式的结果值定义Begin*/
    DT_RESULT_RRC_BEGIN = 0x1000,

    /*RRC模式的结果值定义End*/

    /*NAS模式的结果值定义Begin*/
    DT_RESULT_NAS_BEGIN                 = 0x2000,
    DT_RESULT_NAS_PLMN_LOCK             = 0x2001,
    DT_RESULT_NAS_PLMN_UNLOCK           = 0x2002,

    /*NAS模式的结果值定义End*/

    /*L2模式的结果值定义Begin*/
   DT_RESULT_L2_BEGIN = 0x3000,

    /*L2模式的结果值定义End*/

   /*RRU模式的结果值定义Begin*/
   DT_RESULT_RRU_BEGIN = 0x4000,

   /*RRU模式的结果值定义End*/

    DT_RESULT_BUTT
};
typedef VOS_UINT32 DT_RESULT_ENUM_UINT32;

/*****************************************************************************
 结构名    : DT_FLAG_ENUM
 结构说明  : DT有效标识
*****************************************************************************/
enum DT_FLAG_ENUM
{
    DT_FLAG_INVALID,                 /* 无效*/
    DT_FLAG_VALID,                   /* 有效 */
    DT_FLAG_ENUM_BUTT
};
typedef VOS_UINT8 DT_FLAG_ENUM_UINT8;

/*****************************************************************************
 结构名    : APP_PS_MSG_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : 协议栈和APP之间的消息ID定义
*****************************************************************************/

enum APP_PS_MSG_TYPE_ENUM
{

    /*可维可测-camped cell information上报*/
    ID_OM_PS_CAMPEDCELL_INFO_CMD_REQ           = (PS_MSG_ID_APP_TO_PS_BASE + 0x01),/*0x1336*/
    ID_PS_OM_CAMPEDCELL_INFO_CMD_CNF           = (PS_MSG_ID_PS_TO_APP_BASE + 0x01),/*0x1316*/

    /*可维可测-handover上报*/
    ID_OM_PS_HANDOVER_INFO_CMD_REQ             = (PS_MSG_ID_APP_TO_PS_BASE + 0x02),/*0x1337*/
    ID_PS_OM_HANDOVER_INFO_CMD_CNF             = (PS_MSG_ID_PS_TO_APP_BASE + 0x02),/*0x1317*/

    /*可维可测-prach\sr上报*/
    ID_OM_PS_PRACH_SR_INFO_CMD_REQ             = (PS_MSG_ID_APP_TO_PS_BASE + 0x03),/*0x1338*/
    ID_PS_OM_PRACH_SR_INFOCMD_CNF              = (PS_MSG_ID_PS_TO_APP_BASE + 0x03),/*0x1318*/

    /*可维可测-bsr上报*/
    ID_OM_PS_BSR_INFO_CMD_REQ                  = (PS_MSG_ID_APP_TO_PS_BASE + 0x04),/*0x1339*/
    ID_PS_OM_BSR_INFO_CMD_CNF                  = (PS_MSG_ID_PS_TO_APP_BASE + 0x04)/*0x1319*/



};
typedef VOS_UINT32   APP_PS_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : TDS_L2_UP_EVENT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : TL用户面事件枚举定义，用于记录影响TL流量的各种事件
*****************************************************************************/
enum    TL_UP_EVENT_ENUM
{
    /*CDS事件*/
    TL_UP_EVENT_CDS_UL_IPF_ERR                  = 0,
    TL_UP_EVENT_CDS_UL_SOFT_IPF_ERR,
    TL_UP_EVENT_CDS_UL_FLOW_CTRL,
    TL_UP_EVENT_CDS_DL_FLOW_CTRL,
    TL_UP_EVENT_CDS_DL_SDU_QUE_FULL,

    /*TDS事件*/
    TL_UP_EVENT_TPDCP_UL_DISCARD_SDU            = 50,
    TL_UP_EVENT_TPDCP_DL_DISCARD_SDU,

    TL_UP_EVENT_TRLC_UL_RETX_PDU                = 100,
    TL_UP_EVENT_TRLC_UL_RETX_PDU_MAX_NUM,
    TL_UP_EVENT_TRLC_UL_TX_NACK,
    TL_UP_EVENT_TRLC_UL_TX_RTS_PDU,
    TL_UP_EVENT_TRLC_UL_TX_RTS_ACK_PDU,
    TL_UP_EVENT_TRLC_UL_SDU_QUE_FULL,
    TL_UP_EVENT_TRLC_UL_RL_FAIL,
    TL_UP_EVENT_TRLC_UL_DISCARD_TIMER_EXPIRED,
    TL_UP_EVENT_TRLC_DL_RX_NACK,
    TL_UP_EVENT_TRLC_DL_RX_MRW,
    TL_UP_EVENT_TRLC_DL_RX_MRW_ACK,
    TL_UP_EVENT_TRLC_DL_RX_RTS_PDU,
    TL_UP_EVENT_TRLC_DL_RX_RTS_ACK_PDU,
    TL_UP_EVENT_TRLC_DL_RX_SN_OUT_OF_WIN,

    TL_UP_EVENT_TMAC_UL_HARQ_RETX               = 150,
    TL_UP_EVENT_TMAC_UL_HARQ_RETX_MAX,
    TL_UP_EVENT_TMAC_UL_HARQ_RESET,
    TL_UP_EVENT_TMAC_UL_PDU_FULL,
    TL_UP_EVENT_TMAC_UL_RX_NACK,
    TL_UP_EVENT_TMAC_UL_SFN_ERR,
    TL_UP_EVENT_TMAC_DL_RX_DPCH_CRC_ERR,
    TL_UP_EVENT_TMAC_DL_RX_DPA_CRC_ERR,
    TL_UP_EVENT_TMAC_DL_REORDER_TIMER_EXPIRED,
    TL_UP_EVENT_TMAC_DL_T312_EXPIRED,
    TL_UP_EVENT_TMAC_DL_T313_EXPIRED,
    TL_UP_EVENT_TMAC_DL_T2_EXPIRED,
    TL_UP_EVENT_TMAC_DL_OUT_OF_SYNC,
    TL_UP_EVENT_TMAC_UPA_ACTIVE,
    TL_UP_EVENT_TMAC_UPA_DEACTIVE,
    TL_UP_EVENT_TMAC_DPA_ACTIVE,
    TL_UP_EVENT_TMAC_DPA_DEACTIVE,
    TL_UP_EVENT_TMAC_UL_TTF_MEM_FULL,
    TL_UP_EVENT_TMAC_DL_TTF_MEM_FULL,

    /*LTE事件*/
    TL_UP_EVENT_LPDCP_UL_SDU_BUFFER_FULL            = 200,
    TL_UP_EVENT_LPDCP_UL_DISCARD_SDU_HIGH_PRI,
    TL_UP_EVENT_LPDCP_UL_DISCARD_SDU_LOW_PRI,
    TL_UP_EVENT_LPDCP_UL_FLOW_CTRL_STOP_TX,
    TL_UP_EVENT_LPDCP_DL_SN_NOT_CONSECUTIVE,
    TL_UP_EVENT_LPDCP_DL_SN_OUT_OF_WIN,
    TL_UP_EVENT_LPDCP_DL_CIFIFO_FULL,
    TL_UP_EVENT_LPDCP_DL_SDU_LEN_ERR,
    TL_UP_EVENT_LPDCP_DL_DISCARD_PDU_TOTAL,
    TL_UP_EVENT_LPDCP_STOP,
    TL_UP_EVENT_LPDCP_CONTINUE,
    TL_UP_EVENT_LPDCP_REL,

    TL_UP_EVENT_LRLC_UL_RETX_PDU                = 250,
    TL_UP_EVENT_LRLC_UL_RETX_PDU_SEGMENT,
    TL_UP_EVENT_LRLC_UL_RETX_PDU_MAX_NUM,
    TL_UP_EVENT_LRLC_UL_RX_NACK,
    TL_UP_EVENT_LRLC_UL_SDU_QUE_FULL,
    TL_UP_EVENT_LRLC_UL_DISCARD_TIMER_EXPIRED,
    TL_UP_EVENT_LRLC_DL_DISCARD_PDU_TOTAL,
    TL_UP_EVENT_LRLC_DL_DISCARD_PDU_MEM_FULL,
    TL_UP_EVENT_LRLC_DL_START_REORDER_TIMER,
    TL_UP_EVENT_LRLC_DL_SN_OUT_OF_WIN,
    TL_UP_EVENT_LRLC_DL_DISCARD_SDU_MEM_FULL,
    TL_UP_EVENT_LRLC_DL_FEEDBACK_NACK,
    TL_UP_EVENT_LRLC_REEST,
    TL_UP_EVENT_LRLC_REL,

    TL_UP_EVENT_LMAC_UL_HARQ_RETX               = 300,
    TL_UP_EVENT_LMAC_UL_HARQ_RETX_MAX_NUM,
    TL_UP_EVENT_LMAC_UL_SCHED_INVALID,
    TL_UP_EVENT_LMAC_UL_SCHED_PDU_FAIL,
    TL_UP_EVENT_LMAC_UL_SCHED_TIMEOUT,
    TL_UP_EVENT_LMAC_UL_PDU_ERROR,
    TL_UP_EVENT_LMAC_UL_TWO_SCHED_IND_IN_1MS,
    TL_UP_EVENT_LMAC_UL_SCHED_IND_NOT_CONSECUTIVE,
    TL_UP_EVENT_LMAC_UL_SCHED_ERROR_TOTAL,
    TL_UP_EVENT_LMAC_DL_RX_TB_CRC_ERR,
    TL_UP_EVENT_LMAC_DL_RX_TB_REPEAT,
    TL_UP_EVENT_LMAC_SR,
    TL_UP_EVENT_LMAC_SR_MAX_NUM,
    TL_UP_EVENT_LMAC_RESET,
    TL_UP_EVENT_LMAC_RA_MAC_TRIGGERED,
    TL_UP_EVENT_LMAC_RA_RRC_TRIGGERED,
    TL_UP_EVENT_LMAC_RA_PDCCH_TRIGGERED,
    TL_UP_EVENT_LMAC_REL,

    TL_UP_EVENT_BUTT                            =  350
};
typedef VOS_UINT16 TL_UP_EVENT_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LSCELL_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LTE CA 辅小区状态
*****************************************************************************/
enum    LSCELL_STATUS_ENUM
{
    LSCELL_NOT_CONFIGED                  = 0,
    LSCELL_CONFIGED_NOT_ACTIVE,
    LSCELL_ACTIVE,
    LSCELL_STATUS_BUTT
};
typedef VOS_UINT8 LSCELL_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : LMAC_SCELL_CFG_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LTE CA 辅小区配置状态
*****************************************************************************/
enum    LMAC_SCELL_CFG_STATUS_ENUM
{
    LMAC_SCELL_NOT_CONFIG                  = 0,
    LMAC_SCELL_CONFIG,
    LMAC_SCELL_CFG_STATUS_BUTT
};
typedef VOS_UINT8 LMAC_SCELL_CFG_STATUS_ENUM_UINT8;


/*****************************************************************************
 枚举名    : LSCELL_DEACT_TIMER_VIEW_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LTE CA 去激活定时器OM显示
*****************************************************************************/
enum    LSCELL_DEACT_TIMER_VIEW_ENUM
{
    LSCELL_DEACT_TIMER_INFINITE                  = 0,
    LSCELL_DEACT_TIMER_NOTCONFIG
};
typedef VOS_UINT32 LSCELL_DEACT_TIMER_VIEW_ENUM_UINT32;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/


/*****************************************************************************
 结构名    : APP_OM_MSG_STRU
 结构说明  : APP(后台工具)与OM交互的消息体
*****************************************************************************/
typedef struct
{
     VOS_MSG_HEADER                     /*VOS头
 */
     VOS_UINT32          ulMsgId;
     APP_MSG_HEADER                     /*APP头
 */
     VOS_UINT8           aucPara[4];    /* 参数内容 */
}APP_OM_MSG_STRU;

/*****************************************************************************
 结构名    : PS_MSG_STRU
 结构说明  : 协议栈各模块消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32          ulMsgId;        /* 消息原语ID */
    VOS_UINT8           aucPara[4];     /* 参数内容 */
} PS_MSG_STRU;


/*****************************************************************************
 结构名    : PS_OM_AIR_MSG_REPORT_IND_STRU
 结构说明  : 协议栈所有模块上报空口消息的结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                  ulMsgId;        /*原语类型,*/
    APP_MSG_HEADER

    VOS_UINT8                   ucUpDown;       /*上下行标识：   0-上行，1-下行  */
    OM_PS_AIR_MSG_ENUM_UINT8    enAirMsgId;     /*空中接口消息的Id               */
    VOS_UINT8                   aucReserved[2]; /*保留                           */
    VOS_UINT32                  ulAirLength;    /*空中消息数据长度               */
    VOS_UINT8                   aucData[4];     /*空中消息数据                   */
}PS_OM_AIR_MSG_REPORT_IND_STRU;

/*****************************************************************************
 结构名    : PS_OMT_KEY_EVENT_REPORT_IND_STRU
 结构说明  : PS所有模块->OMT的关键事件结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;        /*原语类型,*/
    APP_MSG_HEADER

    OM_PS_KEY_EVENT_ENUM_UINT8          ucKeyEvent;     /*关键事件类型，为枚举值 */
    VOS_UINT8                           aucReserved[3];
}PS_OMT_KEY_EVENT_REPORT_IND_STRU;


/*****************************************************************************
 结构名    : OM_PS_TRANSPARENT_CMD_REQ_STRU
 结构说明  : OMT->PS所有模块的透明命令下发结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32          ulMsgId;        /*原语类型*/
    APP_MSG_HEADER

    VOS_UINT8           aucTransCmd[4]; /*透明码流，可变*/
}OM_PS_TRANSPARENT_CMD_REQ_STRU;

/*****************************************************************************
 结构名    : PS_OM_TRANSPARENT_CMD_CNF_STRU
 结构说明  : PS->OMT的透明命令执行结果数据结构(
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32          ulMsgId;            /*原语类型*/
    APP_MSG_HEADER

    VOS_UINT8           aucTransCmdCnf[4];  /*透明命令结果码流，可变*/
}PS_OM_TRANSPARENT_CMD_CNF_STRU;
/*****************************************************************************
 结构名    : PS_OM_TRANSPARENT_CMD_IND_STRU
 结构说明  : PS->OMT的透明命令执行IND数据结构(
*****************************************************************************/
typedef  PS_OM_TRANSPARENT_CMD_CNF_STRU PS_OM_TRANSPARENT_CMD_IND_STRU;


/*PS可维可测 BEGIN */

/*****************************************************************************
 结构名    : OM_PS_CAMPEDCELL_INFO_REQ_STRU
 结构说明  : MSP查询驻留小区信息的REQ/CNF命令数据结构
*****************************************************************************/
typedef  APP_OM_MSG_STRU OM_PS_CAMPEDCELL_INFO_REQ_STRU;
typedef  APP_OM_MSG_STRU PS_OM_CAMPEDCELL_INFO_CNF_STRU;

/*****************************************************************************
 结构名    : OM_PS_HANDOVER_INFO_REQ_STRU
 结构说明  : MSP查询小区切换信息的REQ/CNF命令数据结构
*****************************************************************************/
typedef  APP_OM_MSG_STRU OM_PS_HANDOVER_INFO_REQ_STRU;
typedef  APP_OM_MSG_STRU PS_OM_HANDOVER_INFO_CNF_STRU;

/*****************************************************************************
 结构名    : OM_PS_PRACH_SR_INFO_REQ_STRU
 结构说明  : MSP查询小区PRACH\SR的REQ/CNF命令数据结构
*****************************************************************************/
typedef  APP_OM_MSG_STRU OM_PS_PRACH_SR_INFO_REQ_STRU;
typedef  APP_OM_MSG_STRU PS_OM_PRACH_SR_INFO_CNF_STRU;

/*****************************************************************************
 结构名    : OM_PS_BSR_INFO_REQ_STRU
 结构说明  : MSP查询BSR的REQ/CNF命令数据结构
*****************************************************************************/
typedef  APP_OM_MSG_STRU OM_PS_BSR_INFO_REQ_STRU;
typedef  APP_OM_MSG_STRU PS_OM_BSR_INFO_CNF_STRU;

/*****************************************************************************
 结构名    : OM_L2_THROUGHPUT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : APP向L2请求APP层Tx与Rx统计信息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    DT_CMD_ENUM_UINT8                   enCmd;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulRptPeriod;
}OM_L2_THROUGHPUT_REQ_STRU;

/*****************************************************************************
 结构名    : L2_OM_THROUGHPUT_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OM向L2请求APP 层Tx与Rx统计信息的回应结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    DT_RESULT_ENUM_UINT32               enResult;
} L2_OM_THROUGHPUT_CNF_STRU;

/*****************************************************************************
 结构名    : OM_L2_SWITCH_CTRL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : APP向L2请求修改可维可测控制开关
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulTLPduRptFlg;
    VOS_UINT32                          ulCdsUlIpPktRptFlg;
    VOS_UINT32                          ulCdsDlIpPktRptFlg;
    VOS_UINT32                          ulLPdcpUlPduRptFlg;
    VOS_UINT32                          ulLPdcpDlPduRptFlg;
    VOS_UINT32                          ulLPdcpDlSduRptFlg;
    VOS_UINT32                          ulLRlcUlPduRptFlg;
    VOS_UINT32                          ulLRlcDlPduRptFlg;
    VOS_UINT32                          ulLRlcAmCtrlPduRptFlg;
    VOS_UINT32                          ulLMacUlPduRptFlg;
    VOS_UINT32                          ulLMacDlPduRptFlg;
    VOS_UINT32                          ulCdsUlIpHookFlg;
    VOS_UINT32                          ulCdsDlIpHookFlg;
    VOS_UINT32                          ulCdsDlLteDbgHookFlg;
    VOS_UINT32                          ulCdsImsHookFlg;
    VOS_UINT32                          ulCdsBastetHookFlg;
    VOS_UINT32                          ulLteLatencyRptFlg;
    VOS_UINT32                          ulLMacRegBsrandSRInfoFlg;
    VOS_UINT32                          ulLMacBsrRptFlg;
    VOS_UINT32                          ulLteOverviewFlg;
    VOS_UINT8                           ucSwitch[20];
    VOS_UINT32                          ulLMacUlGrantFlg;
    VOS_UINT32                          ulLMacDlAssignFlg;
    VOS_UINT32                          ulLMacSrReqRptFlg;
    VOS_UINT32                          ulLMacLPhyPhrCfgReqRptFlg;
    VOS_UINT32                          ulLMacLPhySrCnfRptFlg;
    VOS_UINT32                          ulLMacLPhyPucchIndRptFlg;
    VOS_UINT32                          ulLMacLPhyTaReqRptFlg;
    VOS_UINT32                          ulLMacLPhyScellActReqRptFlg;


    /*
    L2 开关说明
    ucSwitch[0]:g_ulTlUpEventFlag      TDS&LTE L2事件上报开关
    ucSwitch[1]:g_ulRlcPrintFlag       LTE L2数传打印开关
    ucSwitch[2]:g_ulLMacRebootTmpFlag  LTE RAR接收超时手动触发复位开关
    ucSwitch[3]:g_ulL2UlGrantIndFlag   LTE MAC 上行授权消息上报开关
    ucSwitch[4]:g_ulL2UlSrDataFlag     LTE MAC 上行SR发起消息上报开关
    ucSwitch[5]:g_ulRohcPrintFlag      LTE ROHC 可维可测打印信息上报开关
    ucSwitch[6]:g_ulTcpPrintFlag       LTE TCP 信息打印上报开关,已删除，做占位用
    ucSwitch[7]:g_ulTcpDlFlg           LTE TCP 下行打印上报开关,已删除，做占位用
    ucSwitch[8]:g_ulTcpUlFlg           LTE TCP 上行打印上报开关,已删除，做占位用
    ucSwitch[9]:g_ulTcpRbID            LTE TCP 监测特定rb上数据,已删除，做占位用
    */
}OM_L2_SWITCH_CTRL_REQ_STRU;

/*****************************************************************************
 结构名    : L2_OM_SWITCH_CTRL_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OM向L2请求修改可维可测控制开关的回应结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    DT_RESULT_ENUM_UINT32               enResult;
} L2_OM_SWITCH_CTRL_CNF_STRU;

/*DCM logger*/
/*****************************************************************************
 结构名    : OM_L2_MAC_PDU_RPT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OM向L2指示打开或者关闭MAC PDU信息的上报
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT8                           ucCmd;  /*值为0，表示关闭上报，值为1，表示打开上报*/
    VOS_UINT8                           aucRsv[3]; /*预留字节*/
}OM_L2_MAC_PDU_RPT_REQ_STRU;

/*****************************************************************************
 结构名    : L2_OM_MAC_PDU_RPT_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : L2向OM回复打开或者关闭MAC PDU信息的上报是否成功
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT8                           ucResult;  /*值为0，表示成功，其他值，表示失败*/
    VOS_UINT8                           aucRsv[3]; /*预留字节*/
} L2_OM_MAC_PDU_RPT_CNF_STRU;

/*****************************************************************************
 结构名    : OM_L2_BSR_RPT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OM向L2指示打开或者关闭BSR信息的上报
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT8                           ucCmd;  /*值为0，表示关闭上报，值为1，表示打开上报*/
    VOS_UINT8                           aucRsv[3]; /*预留字节*/
}OM_L2_BSR_RPT_REQ_STRU;

/*****************************************************************************
 结构名    : L2_OM_BSR_RPT_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : L2向OM回复打开或者关闭BSR信息的上报是否成功
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT8                           ucResult;  /*值为0，表示成功，其他值，表示失败*/
    VOS_UINT8                           aucRsv[3]; /*预留字节*/
} L2_OM_BSR_RPT_CNF_STRU;
/*end DCM*/
/*****************************************************************************
 结构名    : OM_L2_SDU_COUNT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : APP向L2请求各层SDU统计信息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    DT_CMD_ENUM_UINT8                   enCmd;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulRptPeriod;
}OM_L2_SDU_COUNT_REQ_STRU;

/*****************************************************************************
 结构名    : L2_OM_APP_THROUGHPUT_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : APP向L2请求各层SDU统计信息的回应结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    DT_RESULT_ENUM_UINT32               enResult;
} L2_OM_SDU_COUNT_CNF_STRU;


/*****************************************************************************
 结构名    : APP_LPS_PRACH_SR_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PS向MSP上报PRACH/SR相关信息结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTotalPblNum;         /*Preamble Number*/
    VOS_UINT32                          ulGrpAPblNum;          /*Group A Preamble Number*/
    VOS_UINT32                          ulGrpBPblNum;          /*Group B Preamble Number*/
    VOS_UINT32                          ulContentionPblNum;    /*Contention Preamble Number*/
    VOS_UINT32                          ulNoneContentionPblNum;/*None Contention Preamble Number*/
    VOS_UINT32                          ulRarNum;              /*RAR Number*/
    VOS_UINT32                          ulCompetitionNum;      /*Competition Number*/
    VOS_UINT32                          ulSrNum;               /*SR Number*/
}APP_LPS_PRACH_SR_INFO_STRU;

/*****************************************************************************
 结构名    : APP_LPS_BSR_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PS向MSP上报BSR相关信息结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulShortBsrGrpId;          /*short bsr对应的GROUP ID*/
    VOS_UINT32                          ulShortBsrValue;          /*Short BSR*/
    VOS_UINT32                          ulLongBsr0Value;          /*Long BSR 0*/
    VOS_UINT32                          ulLongBsr1Value;          /*Long BSR 1*/
    VOS_UINT32                          ulLongBsr2Value;          /*Long BSR 2*/
    VOS_UINT32                          ulLongBsr3Value;          /*Long BSR 3*/
}APP_LPS_BSR_INFO_STRU;

/*****************************************************************************
 结构名    : LPS_PLMN_ITEM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PLMN条目
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPlmnId[3];
    VOS_UINT8                           ucReserved;
} LPS_PLMN_ITEM_STRU;

/*****************************************************************************
 结构名    : LPS_PLMN_ITEM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PLMN LIST
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPlmnCount;
    VOS_UINT8                           aucReservered[2];
    LPS_PLMN_ITEM_STRU                  astPlmnItems[LPS_RRC_CSEL_MAX_FOUND_PLMN_COUNT];
} LPS_CSEL_PLMN_LIST_CTX_STRU;

/*****************************************************************************
 结构名    : LPS_NAS_MM_TAC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TAC 信息
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTac;
    VOS_UINT8                           ucTacCnt;
    VOS_UINT8                           aucRsv[2];
}LPS_NAS_MM_TAC_STRU;

/*****************************************************************************
 结构名    : LPS_NAS_MM_TA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TA 信息
*****************************************************************************/
typedef struct
{
    LPS_PLMN_ITEM_STRU                 stPlmnId;
    LPS_NAS_MM_TAC_STRU                stTac;
}LPS_NAS_MM_TA_STRU;

/*****************************************************************************
 结构名    : LPS_NAS_MM_TA_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TA LIST
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTaNum;            /* TA的个数:为0表示无相关信息*/
    LPS_NAS_MM_TA_STRU                  astTa[LPS_NAS_MM_MAX_TA_NUM];
}LPS_NAS_MM_TA_LIST_STRU;

/*****************************************************************************
 结构名    : LPS_NAS_MM_GUTI_HEAD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GUTI Head
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLenth;
    VOS_UINT8                           ucOeToi;
    VOS_UINT8                           aucRsv[2];
}LPS_NAS_MM_GUTI_HEAD_STRU;

/*****************************************************************************
 结构名    : LPS_NAS_MM_GUTI_HEAD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GUTI Head
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucGroupId;
    VOS_UINT8                           ucGroupIdCnt;
    VOS_UINT8                           aucRsv[2];
}LPS_NAS_MM_MME_GROUPID_STRU;

/*****************************************************************************
 结构名    : LPS_NAS_MM_MME_CODE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MME code
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMmeCode;
    VOS_UINT8                           aucRsv[3];
}LPS_NAS_MM_MME_CODE_STRU;

/*****************************************************************************
 结构名    : LPS_NAS_MM_MME_CODE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MTIMSI
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMTmsi;
    VOS_UINT8                           ucMTmsiCnt1;
    VOS_UINT8                           ucMTmsiCnt2;
    VOS_UINT8                           ucMTmsiCnt3;
}LPS_NAS_MM_MTMSI_STRU;

/*****************************************************************************
 结构名    : LPS_NAS_MM_MME_CODE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GUTI 信息
*****************************************************************************/
typedef struct
{
    LPS_NAS_MM_GUTI_HEAD_STRU               stGutiHead;
    LPS_PLMN_ITEM_STRU                      stPlmnId;
    LPS_NAS_MM_MME_GROUPID_STRU             stMmeGroupId;
    LPS_NAS_MM_MME_CODE_STRU                stMmeCode;
    LPS_NAS_MM_MTMSI_STRU                   stMTmsi;
}LPS_NAS_MM_GUTI_STRU;

/*****************************************************************************
 结构名    : LPS_NAS_ESM_IP_ADDR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IP地址信息
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIpType;
    VOS_UINT8                           ucReserved[3];
    VOS_UINT8                           aucIpV4Addr[LPS_APP_MAX_IPV4_ADDR_LEN];
    VOS_UINT8                           aucIpV6Addr[LPS_APP_MAX_IPV6_ADDR_LEN];
}LPS_NAS_ESM_IP_ADDR_STRU;

/*****************************************************************************
 结构名    : LPS_NAS_ESM_EPSB_CNTXT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 每个EPS承载对应的IP 地址
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEpsbId;           /*对应EPS承载ID*/
    LPS_NAS_ESM_IP_ADDR_STRU            stPdnAddrInfo;
}LPS_NAS_ESM_EPSB_CNTXT_INFO_STRU;


/*****************************************************************************
 结构名    : LPS_NAS_IMSI_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSI信息
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucImsi[LPS_NAS_MM_MAX_UEID_BUF_SIZE];    /*IMSI*/
    VOS_UINT8                           ucResvd[2];
}LPS_NAS_IMSI_STRU;


/*****************************************************************************
 结构名    : APP_LPS_CAMPED_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PS向MSP上报驻留小区的相关信息结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPhyCellId;          /*servering cell id*/
    VOS_UINT16                          usSyncFlag;           /*1:同步 0:失步 显示"Sync"or"Out of Sync"*/
    LPS_CSEL_PLMN_LIST_CTX_STRU         stPlmnListInfo;      /*PLMN LIST*/
    LPS_NAS_MM_TA_LIST_STRU             stRegPlmnTaList;     /*TA LIST*/

    LPS_NAS_IMSI_STRU                   stImsiInfo;          /*IMSI*/
    LPS_NAS_MM_GUTI_STRU                stGutiInfo;          /*GUTI*/


    LPS_NAS_ESM_EPSB_CNTXT_INFO_STRU    astEpsbCntxtInfo[LPS_NAS_ESM_MAX_EPSB_NUM]; /* EPS承载IP地址信息  */

    VOS_UINT16                          usUlEarfcn;          /*UL EARFCN */
    VOS_UINT16                          usDlEarfcn;          /*DL EARFCN*/
    VOS_UINT16                          usUlFreq;            /*UL Frequency 单位:Mhz*/
    VOS_UINT16                          usDlFreq;            /*DL Frequency 单位:Mhz*/
    VOS_UINT16                          usUlBandwidth;       /*单位:RB个数 */
    VOS_UINT16                          usDlBandwidth;       /*单位:RB个数 */
    VOS_UINT32                          ulBand;              /*BAND ID*/

    VOS_UINT16                          usCRnti;             /*C-RNTI*/
    VOS_UINT16                          usSpsRnti;           /*SPS-RNTI*/
    VOS_UINT16                          usPucchRnti;         /*TPC-PUCCH-RNTI*/
    VOS_UINT16                          usPuschRnti;         /*TPC-PUSCH-RNTI*/

    VOS_UINT8                           ucSbuFrmAssignmentType;
    VOS_UINT8                           ucSpecialSubFrmPatterns;
    VOS_UINT8                           ucUlCpLength;
    VOS_UINT8                           ucDlCpLength;

    VOS_UINT8                           ucEnbTxAntennaNum;
    VOS_UINT8                           ucTransmissionMode;
    VOS_UINT8                           aucResv[2];


}APP_LPS_CAMPED_CELL_INFO_STRU;
/*****************************************************************************
 结构名    : APP_PS_HO_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 切换次数统计
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulHOTotalCnt;      /*切换总次数*/
    VOS_UINT32                          ulHOSuccCnt;       /*切换成功的次数*/
    VOS_UINT32                          ulHOFailCnt;       /*切换失败的次数*/
}LPS_HO_STAT_INFO_STRU;


/*****************************************************************************
 结构名    : APP_PS_HANDOVER_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PS向MSP上报切换的相关信息结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usLatestHOLatency;      /*最近一次切换时延*/
    VOS_UINT16                          usAverageHOLatency;     /*平均切换时延*/
    LPS_HO_STAT_INFO_STRU                astIntraFreqHO;
    LPS_HO_STAT_INFO_STRU                astInterFreqHO;        /*异频切换统计*/
    LPS_HO_STAT_INFO_STRU                astInterRatHO;         /*异系统切换次数统计*/
}APP_LPS_HANDOVER_INFO_STRU;

/*PS可维可测 END */

/* gaojishan */
typedef DT_CMD_ENUM_UINT8       APP_CMD_ENUM_UINT8;
typedef DT_RESULT_ENUM_UINT32   APP_RESULT_ENUM_UINT32;


/*****************************************************************************
 结构名    :TL_OM_COMM_HEAD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :TDS L2单个事件上报结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPid;
    VOS_UINT16                          usRbId;
    VOS_UINT16                          usFrameNum;
    VOS_UINT16                          usSubFrameNum;
} TL_OM_COMM_HEAD_STRU;

/*****************************************************************************
 结构名    :TDS_L2_SINGLE_EVENT_RPT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :TDS L2单个事件上报结构体
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;
    TL_UP_EVENT_ENUM_UINT16             usEvent;
    VOS_UINT16                          usRsv;
} TL_OM_SINGLE_UP_EVENT_RPT_STRU;

/*****************************************************************************
 结构名    :TDS_L2_AlL_EVENT_RPT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :TDS L2所有事件上报结构体
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;
    VOS_UINT32                          aulEventStat[TL_UP_EVENT_BUTT];
} TL_OM_AlL_UP_EVENT_RPT_STRU;

/*****************************************************************************
 结构名    : TL_OM_CDS_IPF_PROC_STAT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS IPF相关处理统计量
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU    stCommHead;

    /*IPF事件*/
    VOS_UINT32              ulIpfULIntNum;
    VOS_UINT32              ulULProcIpfIntNum;
    VOS_UINT32              ulUlAdqEmtypIntNum;
    VOS_UINT32              ulUlProcAdqEmptyIntNum;

    /*上行RD统计信息*/
    VOS_UINT32              ulULIpfRxRDNum;
    VOS_UINT32              ulULIpfTransMemFailNum;
    VOS_UINT32              ulULIpfModemIdErrNum;
    VOS_UINT32              ulULIpfFreePktInLB;
    VOS_UINT32              ulULIpfRxNdisPktNum;
    VOS_UINT32              ulULIpfRxIpPktNum;
    VOS_UINT32              ulULIpfRxIpSegNum;
    VOS_UINT32              ulULIpfFilterErrNum;

    /*上行AD信息*/
    VOS_UINT32              ulULADQCfgAdNum;
    VOS_UINT32              ulULADQCfgAd0Num;
    VOS_UINT32              ulULADQCfgAd1Num;
    VOS_UINT32              ulULADQAllocMemNum;
    VOS_UINT32              ulULADQFreeMemNum;
    VOS_UINT32              ulULADQCfgAdSucc;
    VOS_UINT32              ulULADQCfgAdFail;
    VOS_UINT32              ulULADQStartEmptyTmrNum;
    VOS_UINT32              ulULADQStopEmptyTmrNum;
    VOS_UINT32              ulULADQEmptyTmrTimeoutNum;
    VOS_UINT32              ulULADQAd0EmptyIntNum;
    VOS_UINT32              ulULADQAd1EmptyIntNum;


    /*下行IPF信息*/
    VOS_UINT32              ulDLIpfSaveSrcMemFail;
    VOS_UINT32              ulDLIpfSaveSrcMemSucc;
    VOS_UINT32              ulDLIpfFreeSrcMemNum;
    VOS_UINT32              ulDLIpfFreeSrcMemErr;

    VOS_UINT32              ulDLIpfCfgHaveNoBD;
    VOS_UINT32              ulDLIpfCfgHaveNoCD;
    VOS_UINT32              ulDLIpfCfgCDNotEnough;
    VOS_UINT32              ulDLIpfCfgBDSucc;
    VOS_UINT32              ulDLIpfCfgBDFail;
    VOS_UINT32              ulDLIpfCfgBDAllocMemFail;
    VOS_UINT32              ulDLIpfCfgBDSduLenErr;
}TL_OM_CDS_IPF_PROC_STAT_IND_STRU;

/*****************************************************************************
 结构名    : TL_OM_CDS_UL_IP_PKT_STAT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS 上行IP包相关处理统计量
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU    stCommHead;

    /*上行IP包处理*/
    VOS_UINT32              ulULRecvNdPktNum;
    VOS_UINT32              ulULASRxIpPktNum;
    VOS_UINT32              ulULDirectFreePktNum;
    VOS_UINT32              ulULLTERxPktNum;
    VOS_UINT32              ulULGURxPktNum;
    VOS_UINT32              ulULNULLRxPktNum;
    VOS_UINT32              ulULRanModeErrFreeNum;

    VOS_UINT32              ulULLTEFcFreePktNum;
    VOS_UINT32              ulULLTEProcIpSegFail;
    VOS_UINT32              ulULLTESendToLPdcpNum;
    VOS_UINT32              ulULLTESavePktNum;
    VOS_UINT32              ulULLTEERabmStateErr;

    VOS_UINT32              ulULGUFcFreePktNum;
    VOS_UINT32              ulULGUSendToRabmNum;
    VOS_UINT32              ulULGUSavePktNum;
    VOS_UINT32              ulULGURabmStateErr;

    VOS_UINT32              ulULBuffEnQueSucc;
    VOS_UINT32              ulULBuffEnQueFail;
    VOS_UINT32              ulULBuffSoftFilterFail;
    VOS_UINT32              ulULBuffSendPktSuccNum;
    VOS_UINT32              ulULBuffFreePktNum;

    /*软过滤相关统计量*/
    VOS_UINT32              ulULSoftFilterPktNum;
    VOS_UINT32              ulULSoftFilterIPv4Num;
    VOS_UINT32              ulULSoftFilterIPv6Num;
    VOS_UINT32              ulULSoftFilterFailNum;
    VOS_UINT32              ulULSoftFilterIPSegNum;
    VOS_UINT32              ulULSoftFilterIPSegSucc;
    VOS_UINT32              ulULSoftFilterIPSegFail;
}TL_OM_CDS_UL_IP_PKT_STAT_IND_STRU;

/*****************************************************************************
 结构名    : TL_OM_CDS_DL_SDU_STAT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS 下行SDU相关处理统计量
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU    stCommHead;

    /*下行事件统计*/
    VOS_UINT32              ulDL10msTmrTrigEvent;
    VOS_UINT32              ulDL1msIntTrigEvent;
    VOS_UINT32              ulDLUmtsIntTrigEvent;
    VOS_UINT32              ulDLProcEventNum;

    /*下行SDU信息*/
    VOS_UINT32              ulDLGSMRxSduNum;
    VOS_UINT32              ulDLGSMRxImsNum;
    VOS_UINT32              ulDLGSMFcFreeSduNum;
    VOS_UINT32              ulDLGSMGetDeftRabIdFail;
    VOS_UINT32              ulDLGSMEnQueSucc;
    VOS_UINT32              ulDLGSMEnQueFail;

    VOS_UINT32              ulDLUMTSRxSduNum;
    VOS_UINT32              ulDLUMTSRxImsNum;
    VOS_UINT32              ulDLUMTSFcFreeSduNum;
    VOS_UINT32              ulDLUMTSDirectFreeSduNum;
    VOS_UINT32              ulDLUMTSGetDeftRabIdFail;
    VOS_UINT32              ulDLUMTSEnQueSucc;
    VOS_UINT32              ulDLUMTSEnQueFail;

    VOS_UINT32              ulDLLteRxSduNum;
    VOS_UINT32              ulDLLteRxDbgPkt;
    VOS_UINT32              ulDLLteRxMbmsSdu;
    VOS_UINT32              ulDLLteRxImsNum;
    VOS_UINT32              ulDLLteFcFreeSduNum;
    VOS_UINT32              ulDLLteDirectFreeSduNum;
    VOS_UINT32              ulDLLteGetEpsbIDFail;
    VOS_UINT32              ulDLLteGetDeftEpsbIDFail;
    VOS_UINT32              ulDLLteEnQueSucc;
    VOS_UINT32              ulDLLteEnQueFail;

    VOS_UINT32              ulDLEnSduQueSucc;
    VOS_UINT32              ulDLEnSduQueFail;
    VOS_UINT32              ulDLSduTrigEvent;
    VOS_UINT32              ulDLLteRxSduLenErrNum;
}TL_OM_CDS_DL_SDU_STAT_IND_STRU;

/*****************************************************************************
 结构名    : TL_OM_CDS_LOOP_BACK_STAT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS 环回相关处理统计量
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU    stCommHead;

    VOS_UINT32              ulLBDLRxSduInGSM;
    VOS_UINT32              ulLBDLRxSduInUMTS;
    VOS_UINT32              ulLBDLRxSduInLte;
    VOS_UINT32              ulLBDLRxSduInNonModeB;
    VOS_UINT32              ulLBDLAllocMemFail;
    VOS_UINT32              ulLBDDLEnQueSucc;
    VOS_UINT32              ulLBDLEnQueFail;
    VOS_UINT32              ulLBULSoftFilterFail;
    VOS_UINT32              ulLBUlSendPktNum;
    VOS_UINT32              ulLBUlClearPktNum;

}TL_OM_CDS_LOOP_BACK_STAT_IND_STRU;

/*****************************************************************************
 结构名    : TL_OM_CDS_IMS_PROC_STAT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS IMS相关处理统计量
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU    stCommHead;

    VOS_UINT32              ulImsULRxFunCallNum;
    VOS_UINT32              ulImsULRxFunParaErr;
    VOS_UINT32              ulImsULRxNicPktNum;
    VOS_UINT32              ulImsULAllocMemFail;
    VOS_UINT32              ulImsULEnQueFail;
    VOS_UINT32              ulImsULEnQueSucc;
    VOS_UINT32              ulImsULTrigImsEvent;
    VOS_UINT32              ulImsULProcImsEvent;
    VOS_UINT32              ulImsULSoftFilterFail;
    VOS_UINT32              ulImsULSendToRan;

    VOS_UINT32              ulImsDLRxImsPkt;
    VOS_UINT32              ulImsDLNdPktNum;
    VOS_UINT32              ulImsDLAllocMemFail;
    VOS_UINT32              ulImsDLSendToNicFail;
    VOS_UINT32              ulImsDLSendToNicSucc;

}TL_OM_CDS_IMS_PROC_STAT_IND_STRU;



/*****************************************************************************
 结构名    : TL_OM_LTE_ROHC_UL_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE  ROHC 上行统计信息上报结构体
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;

    VOS_UINT32                          ulCidNo;
    VOS_UINT32                          ulUlCompTotalStat;
    VOS_UINT32                          ulUlCompSuccStat;
    VOS_UINT32                          ulUlCompFailStat;

    VOS_UINT32                          ulUlRecvFeedbackCnt;
    VOS_UINT32                          ulUlRecvFeedbackSuccCnt;
    VOS_UINT32                          ulUlRecvFeedbackeErrCnt;

    VOS_UINT32                          ulUlProfile0Stat;
    VOS_UINT32                          ulUlProfile1Stat;
    VOS_UINT32                          ulUlProfile2Stat;
    VOS_UINT32                          ulUlProfile3Stat;
    VOS_UINT32                          ulUlProfile4Stat;

    VOS_UINT32                          ulUlIRStatePktsCnt;
    VOS_UINT32                          ulUlFOStatePktsCnt;
    VOS_UINT32                          ulUlSOStatePktsCnt;

    VOS_UINT32                          ulUlUModePktsCnt;
    VOS_UINT32                          ulUlOModePktsCnt;
    VOS_UINT32                          ulUlRModePktsCnt;

    VOS_UINT32                          ulUlIRPktsCnt;
    VOS_UINT32                          ulUlIRDynPktsCnt;
    VOS_UINT32                          ulUlUO0PktsCnt;
    VOS_UINT32                          ulUlUO1PktsCnt;

    VOS_UINT32                          ulUlUO1_IdPktsCnt;
    VOS_UINT32                          ulUlUO1_TsPktsCnt;
    VOS_UINT32                          ulUlR0PktsCnt;
    VOS_UINT32                          ulUlR0CrcPktsCnt;

    VOS_UINT32                          ulUlUO1_Id_Ex0PktsCnt;
    VOS_UINT32                          ulUlUO1_Id_Ex1PktsCnt;
    VOS_UINT32                          ulUlUO1_Id_Ex2PktsCnt;
    VOS_UINT32                          ulUlUO1_Id_Ex3PktsCnt;

    VOS_UINT32                          ulUlR1PktsCnt;
    VOS_UINT32                          ulUlR1_Ex0PktsCnt;
    VOS_UINT32                          ulUlR1_Ex1PktsCnt;
    VOS_UINT32                          ulUlR1_Ex2PktsCnt;
    VOS_UINT32                          ulUlR1_Ex3PktsCnt;

    VOS_UINT32                          ulUlR1_IdPktsCnt;
    VOS_UINT32                          ulUlR1_Id_Ex0PktsCnt;
    VOS_UINT32                          ulUlR1_Id_Ex1PktsCnt;
    VOS_UINT32                          ulUlR1_Id_Ex2PktsCnt;
    VOS_UINT32                          ulUlR1_Id_Ex3PktsCnt;

    VOS_UINT32                          ulUlR1_TsPktsCnt;
    VOS_UINT32                          ulUlR1_Ts_Ex0PktsCnt;
    VOS_UINT32                          ulUlR1_Ts_Ex1PktsCnt;
    VOS_UINT32                          ulUlR1_Ts_Ex2PktsCnt;
    VOS_UINT32                          ulUlR1_Ts_Ex3PktsCnt;

    VOS_UINT32                          ulUlUOR2PktsCnt;
    VOS_UINT32                          ulUlUOR2_Ex0PktsCnt;
    VOS_UINT32                          ulUlUOR2_Ex1PktsCnt;
    VOS_UINT32                          ulUlUOR2_Ex2PktsCnt;
    VOS_UINT32                          ulUlUOR2_Ex3PktsCnt;

    VOS_UINT32                          ulUlUOR2_IdPktsCnt;
    VOS_UINT32                          ulUlUOR2_Id_Ex0PktsCnt;
    VOS_UINT32                          ulUlUOR2_Id_Ex1PktsCnt;
    VOS_UINT32                          ulUlUOR2_Id_Ex2PktsCnt;
    VOS_UINT32                          ulUlUOR2_Id_Ex3PktsCnt;

    VOS_UINT32                          ulUlUOR2_Ts_PktsCnt;
    VOS_UINT32                          ulUlUOR2_Ts_Ex0PktsCnt;
    VOS_UINT32                          ulUlUOR2_Ts_Ex1PktsCnt;
    VOS_UINT32                          ulUlUOR2_Ts_Ex2PktsCnt;
    VOS_UINT32                          ulUlUOR2_Ts_Ex3PktsCnt;

    VOS_UINT32                          ulUlPrf0IRPktsCnt;
    VOS_UINT32                          ulUlNormalPktsCnt;

    VOS_UINT32                          ulUlIR2FOCnt       ;                /* 上行状态迁移:IR2FO计数:压缩, 类型: ROHC实例统计项 | 分组: ROHC_ENTITY. */
    VOS_UINT32                          ulUlIR2SOCnt         ;              /* 上行状态迁移:IR2SO计数:压缩, 类型: ROHC实例统计项 | 分组: ROHC_ENTITY. */
    VOS_UINT32                          ulUlFO2SOCnt       ;                /* 上行状态迁移:FO2SO计数:压缩, 类型: ROHC实例统计项 | 分组: ROHC_ENTITY. */
    VOS_UINT32                          ulUlFO2IRCnt         ;               /* 上行状态迁移:FO2IR计数:压缩, 类型: ROHC实例统计项 | 分组: ROHC_ENTITY. */
    VOS_UINT32                          ulUlSO2IRCnt           ;           /* 上行状态迁移:SO2IR计数:压缩, 类型: ROHC实例统计项 | 分组: ROHC_ENTITY. */
    VOS_UINT32                          ulUlSO2FOCnt         ;              /* 上行状态迁移:SO2FO计数:压缩, 类型: ROHC实例统计项 | 分组: ROHC_ENTITY. */

}TL_OM_LTE_ROHC_UL_STAT_INFO_STRU;


/*****************************************************************************
 结构名    : TL_OM_LTE_ROHC_DL_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE  ROHC 下行统计信息上报结构体
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;

    VOS_UINT32                          ulCidNo;
    VOS_UINT32                          ulDlProfile0Stat;
    VOS_UINT32                          ulDlProfile1Stat;
    VOS_UINT32                          ulDlProfile2Stat;
    VOS_UINT32                          ulDlProfile3Stat;
    VOS_UINT32                          ulDlProfile4Stat;

    VOS_UINT32                          ulDlRcvPktsCnt;
    VOS_UINT32                          ulDlRcvCrcOkPktsCnt;
    VOS_UINT32                          ulDlRcvCrcErrPktTypeCnt;
    VOS_UINT32                          ulDlRcvPktTypeErrCnt;

    VOS_UINT32                          ulDlNCStatePktsCnt;
    VOS_UINT32                          ulDlSCStatePktsCnt;
    VOS_UINT32                          ulDlFCStatePktsCnt;

    VOS_UINT32                          ulDlUModePktsCnt;
    VOS_UINT32                          ulDlOModePktsCnt;
    VOS_UINT32                          ulDlRModePktsCnt;

    VOS_UINT32                          ulDlSendFeedbackCnt;
    VOS_UINT32                          ulDlUMOdeAckCnt;
    VOS_UINT32                          ulDlUMOdeNackCnt;
    VOS_UINT32                          ulDlUMOdeStcNackCnt;
    VOS_UINT32                          ulDlOMOdeAckCnt;
    VOS_UINT32                          ulDlOMOdeNackCnt;


    VOS_UINT32                          ulDlOMOdeStcNackCnt;
    VOS_UINT32                          ulDlRMOdeAckCnt;
    VOS_UINT32                          ulDlRMOdeNackCnt;
    VOS_UINT32                          ulDlRMOdeStcNackCnt;
    VOS_UINT32                          ulDlFdbk1Cnt;

    VOS_UINT32                          ulDlPkt0Cnt;
    VOS_UINT32                          ulDlPkt1Cnt;
    VOS_UINT32                          ulDlPkt2Cnt;

    VOS_UINT32                          ulDlIRPktsCnt;
    VOS_UINT32                          ulDlIRDynPktsCnt;


    VOS_UINT32                          ulDlUO0PktsCnt;
    VOS_UINT32                          ulDlUO1PktsCnt;
    VOS_UINT32                          ulDlUO1_IDPktsCnt;


    VOS_UINT32                          ulDlUO1_TsPktsCnt;
    VOS_UINT32                          ulDlR0PktsCnt;
    VOS_UINT32                          ulDlR0CrcPktsCnt;

    VOS_UINT32                          ulDlUO1_Id_Ex0PktsCnt;
    VOS_UINT32                          ulDlUO1_Id_Ex1PktsCnt;
    VOS_UINT32                          ulDlUO1_Id_Ex2PktsCnt;
    VOS_UINT32                          ulDlUO1_Id_Ex3PktsCnt;

    VOS_UINT32                          ulDlR1PktsCnt;
    VOS_UINT32                          ulDlR1_Ex0PktsCnt;
    VOS_UINT32                          ulDlR1_Ex1PktsCnt;
    VOS_UINT32                          ulDlR1_Ex2PktsCnt;
    VOS_UINT32                          ulDlR1_Ex3PktsCnt;

    VOS_UINT32                          ulDlR1_IdPktsCnt;
    VOS_UINT32                          ulDlR1_Id_Ex0PktsCnt;
    VOS_UINT32                          ulDlR1_Id_Ex1PktsCnt;
    VOS_UINT32                          ulDlR1_Id_Ex2PktsCnt;
    VOS_UINT32                          ulDlR1_Id_Ex3PktsCnt;

    VOS_UINT32                          ulDlR1_TsPktsCnt;
    VOS_UINT32                          ulDlR1_Ts_Ex0PktsCnt;
    VOS_UINT32                          ulDlR1_Ts_Ex1PktsCnt;
    VOS_UINT32                          ulDlR1_Ts_Ex2PktsCnt;
    VOS_UINT32                          ulDlR1_Ts_Ex3PktsCnt;

    VOS_UINT32                          ulDlUOR2PktsCnt;
    VOS_UINT32                          ulDlUOR2_Ex0PktsCnt;
    VOS_UINT32                          ulDlUOR2_Ex1PktsCnt;
    VOS_UINT32                          ulDlUOR2_Ex2PktsCnt;
    VOS_UINT32                          ulDlUOR2_Ex3PktsCnt;

    VOS_UINT32                          ulDlUOR2_IdPktsCnt;
    VOS_UINT32                          ulDlUOR2_Id_Ex0PktsCnt;
    VOS_UINT32                          ulDlUOR2_Id_Ex1PktsCnt;
    VOS_UINT32                          ulDlUOR2_Id_Ex2PktsCnt;
    VOS_UINT32                          ulDlUOR2_Id_Ex3PktsCnt;

    VOS_UINT32                          ulDlUOR2_Ts_PktsCnt;
    VOS_UINT32                          ulDlUOR2_Ts_Ex0PktsCnt;
    VOS_UINT32                          ulDlUOR2_Ts_Ex1PktsCnt;
    VOS_UINT32                          ulDlUOR2_Ts_Ex2PktsCnt;
    VOS_UINT32                          ulDlUOR2_Ts_Ex3PktsCnt;

}TL_OM_LTE_ROHC_DL_STAT_INFO_STRU;



/*****************************************************************************
 结构名    : TL_OM_LTE_ROHC_COMPRESS_CONTEXT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE  ROHC 上行上下文信息上报结构体
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;

    VOS_UINT8                          ucCidNo;
    VOS_UINT8                          ucCMode;
    VOS_UINT8                          ucState;
    VOS_UINT8                          ucRsv;

    VOS_UINT8                          ucCTrans;
    VOS_UINT8                          ucHdrChainType;
    VOS_UINT8                          ucProfileVal;
    VOS_UINT8                          ucPktType;

    VOS_UINT8                          ucIPIDRndFlag;
    VOS_UINT8                          ucIPIDRnd2Flag;
    VOS_UINT8                          ucIPIDNboFlag;
    VOS_UINT8                          ucIPIDNbo2Flag;

    VOS_UINT8                           ucKforSn;
    VOS_UINT8                           ucKforIPID;
    VOS_UINT8                           ucKforIPID2;
    VOS_UINT8                           ucKforTS;

    VOS_UINT8                           ucRmodePktWithoutCRC;
    VOS_UINT8                           ucXM;                    /* 最低位表M，第四位表X */
    VOS_UINT8                           ucIrSntPktCount;  /*IR状态下连续发包的个数，初始化为0*/
    VOS_UINT8                           ucSntDynPktCount;  /*动态信息变化后连续发包的个数，初始化为0*/

    VOS_UINT16                          usIpIdOffset;
    VOS_UINT16                          usIpIdOffset2;
    VOS_UINT16                          usUdpSnValue;

    VOS_UINT32                          ulEspSnValue;
    VOS_UINT32                          ulLastOperTime;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulTS_Stride;
    VOS_UINT32                          ulTS_Scaled;
    VOS_UINT32                          ulLastAckSn;

    VOS_UINT32                          ufCompressRatio;



}TL_OM_LTE_ROHC_COMPRESS_CONTEXT_INFO_STRU;


/*****************************************************************************
 结构名    : TL_OM_LTE_ROHC_DECOMPRESS_CONTEXT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE  ROHC 下行上下文信息上报结构体
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;

    VOS_UINT8                          ucCidNo;
    VOS_UINT8                          ucDMode;
    VOS_UINT8                          ucState;

    VOS_UINT8                          ucDf1Flag;
    VOS_UINT8                          ucDf2Flag;
    VOS_UINT8                          ucProfileVal;
    VOS_UINT8                          ucRtpM;

    VOS_UINT8                          ucPktType;
    VOS_UINT8                           ucFcToScPacketNum;    /* FC->SC最近发送的N1个包，个数代表后面窗口使用的位数，解压成功对应位置为1，失败置为0，先低位，后高位 */
    VOS_UINT8                           ucScToNcPacketNum;    /* SC->NC最近发送的N2个包 */
    VOS_UINT8                           ucFcToScErrPacketNum; /* FC->SC错包个数，如果最近N1个包中错包达到此值，则状态向下迁移 */

    VOS_UINT8                           ucScToNcErrPacketNum; /* SC->NC错包个数 */
    VOS_UINT8                           ucSendUToOPktCnt;     /* 用来发送U2O模式迁移的反馈包的计数器 */
    VOS_UINT8                           ucRtpPt;
    VOS_UINT8                           ucRtpV;

    VOS_UINT8                           ucRtpP;
    VOS_UINT8                           ucRtpX;
    VOS_UINT8                           ucRtpCC;
    VOS_UINT8                           ucIPIDRndFlag;

    VOS_UINT8                          ucIPIDRnd2Flag;
    VOS_UINT8                          ucIPIDNboFlag;
    VOS_UINT8                          ucIPIDNbo2Flag;
    VOS_UINT8                          ucRsv[2];

    VOS_UINT8                           ucUdpChksumFlg;
    VOS_UINT8                           ucDTrans;
    VOS_UINT16                          usSN;

    VOS_UINT32                          ufCompressRatio;

    VOS_UINT8                           ucCtxtDyn[40];


}TL_OM_LTE_ROHC_DECOMPRESS_CONTEXT_INFO_STRU;


/*****************************************************************************
 结构名    : TL_OM_LTE_ROHC_COMPRESS_PKT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE  ROHC 上行压缩报文头部内容上报
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;

    VOS_UINT8                          ucCidNo;
    VOS_UINT8                          ucLen;
    VOS_UINT8                          ucType; /*0-上行压缩后的压缩包;1-下行恢复前的压缩包;2-上行发送的反馈包;3-下行接收的反馈包*/
    VOS_UINT8                          ucRealLen;


    VOS_UINT8                          ucState;
    VOS_UINT8                          ucMode;
    VOS_UINT8                          ucProfile;
    VOS_UINT8                          ucRohcPktType;/*压缩报文包类型*/

    VOS_UINT8                          ucData[64];

}TL_OM_LTE_ROHC_CAPTURE_PKT_INFO_STRU;


/*****************************************************************************
 结构名    : TL_OM_TDS_PDCP_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TDS PDCP统计信息上报结构体
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;

    VOS_UINT32                          ulPdcpUlRecvSduNum;         /*PDCP上行从RABM接收到的SDU数目*/
    VOS_UINT32                          ulPdcpUlDiscardSduNum;      /*PDCP上行丢弃的SDU数目*/
    VOS_UINT32                          ulPdcpUlSendPduToRlcNum;    /*PDCP上行发送给RLC 的PDU数目*/
    VOS_UINT32                          ulPdcpDlRecvPduNum;         /*PDCP下行从RLC接收到的PDU数目*/
    VOS_UINT32                          ulPdcpDlDiscardPduNum;      /*PDCP下行丢弃的PDU数目*/
    VOS_UINT32                          ulPdcpDlSendSduToRabmNum;   /*PDCP下行发送给RABM的SDU数目*/
}TL_OM_TDS_PDCP_STAT_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_TDS_RLC_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TDS RLC统计信息上报结构体
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;

    VOS_UINT32                          ulRlcRbSetupNum;            /*RLC实体建立数目*/
    VOS_UINT32                          ulRlcRbReleaseNum;          /*RLC实体释放数目*/
    VOS_UINT32                          ulRlcRbReCfgNum;            /*RLC实体重配数目*/
    VOS_UINT32                          ulRlcRbResetNum;            /*RLC实体Reset操作数目*/

    VOS_UINT32                          ulRlcUlRecvSduNum;          /*RLC上行从PDCP处接收到的SDU数目*/
    VOS_UINT32                          ulRlcUlDiscardSduNum;       /*RLC上行丢弃的PDCP SDU数目*/
    VOS_UINT32                          ulRlcUlSendPduToMacNum;     /*RLC上行发送给MAC的PDU数目*/
    VOS_UINT32                          ulRlcUlNewTxPduNum;         /*RLC上行发送新传PDU数目*/
    VOS_UINT32                          ulRlcUlReTxPduNum;          /*RLC上行发送重传PDU数目*/
    VOS_UINT32                          ulRlcUlReTxMaxCntNum;       /*RLC上行发送重传达到最大次数的数目*/
    VOS_UINT32                          ulRlcUlSendPollNum;         /*RLC上行发送Poll数目*/
    VOS_UINT32                          ulRlcUlSendResetNum;        /*RLC上行发送Reset数目*/
    VOS_UINT32                          ulRlcUlSendPiggybackPduNum;          /*RLC下行向网侧反馈ACK数目*/

    VOS_UINT32                          ulRlcDlRecvPduNum;          /*RLC下行从MAC收到的 PDU数目*/
    VOS_UINT32                          ulRlcDlDiscardPdu;          /*RLC下行丢弃的PDU数目*/
    VOS_UINT32                          ulRlcDlSendSduToPdcpNum;    /*RLC下行发送给PDCP的SDU数目*/
    VOS_UINT32                          ulRlcDlRecvPollNum;         /*RLC下行收到Poll数目*/

    VOS_UINT32                          ulRlcDlRcvResetPduNum;         /*RLC下行向网侧反馈NACK数目*/
    VOS_UINT32                          ulRlcDlRcvResetAckPduNum;         /*RLC下行收到Poll数目*/
    VOS_UINT32                          ulRlcDlRcvErrPduNum;        /*RLC下行收到Reset数目*/

    VOS_UINT32                          ulRlcDlRcvCtrlPduNum;        /*RLC下行收到Reset数目*/
}TL_OM_TDS_RLC_STAT_INFO_STRU;

#define TDS_MAC_LOSS_MSG_MAX_NUM 10
/*****************************************************************************
 结构名    : TL_OM_TDS_MAC_STAT_INFO_STRU
 ASN.1描述 :
 结构说明  : TDS MAC统计信息上报结构体
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;

    VOS_UINT32                          ulMacUlRecvSduNum;          /*MAC上行接收到的RLC PDU数目*/
    VOS_UINT32                          ulMacUlSendPduToPhyNum;     /*MAC上行发送给PHY的PDU数目*/
    VOS_UINT32                          ulMacDlRecvPduNum;          /*MAC下行从PHY接收到的PDU数目*/
    VOS_UINT32                          ulMacDlSendSduToRlcNum;     /*MAC下行发送给RLC 的PDU数目*/
    VOS_UINT32                          ulStatusIndNum;          /*MAC上报status ind给RRC的次数*/

    VOS_UINT32                          ulUlSendToDspMsgTotal;
    VOS_UINT32                          ulUlSendToDspMsgSuccess;
    VOS_UINT32                          ulUlSendToDspMsgFail;
    VOS_UINT32                          ulUlSendToDspImmediateMsgTotal;
    VOS_UINT32                          ulUlSendToDspImmediateMsgSuccess;
    VOS_UINT32                          ulUlSendToDspImmediateMsgFail;
    VOS_UINT32                          ulUlSendToDspImmediateMsgError;
    VOS_UINT32                          ulUlSendDpchTotal;
    VOS_UINT32                          ulUlSendPrachTotal;
    VOS_UINT32                          ulUlSendSi;
    VOS_UINT32                          ulUlRecvGrant;
    VOS_UINT32                          ulUlSendEpuchTotal;
    VOS_UINT32                          ulUlSendEpuchNewTx;
    VOS_UINT32                          ulUlSendEpuchReTx;
    VOS_UINT32                          ulDlRecvFpachTotal;
    VOS_UINT32                          ulDlRecvFpachCrcOk;
    VOS_UINT32                          ulDlRecvFpachCrcError;
    VOS_UINT32                          ulDlRecvSccpchTotal;
    VOS_UINT32                          ulDlRecvSccpchCrcOk;
    VOS_UINT32                          ulDlRecvSccpchCrcError;
    VOS_UINT32                          ulDlRecvPccpchTotal;
    VOS_UINT32                          ulDlRecvPccpchCrcOk;
    VOS_UINT32                          ulDlRecvPccpchCrcError;
    VOS_UINT32                          ulDlRecvDpchTotal;
    VOS_UINT32                          ulDlRecvDpchCrcOk;
    VOS_UINT32                          ulDlRecvDpchCrcError;
    VOS_UINT32                          ulDlRecvHspdschTotal;
    VOS_UINT32                          ulDlRecvHspdschCrcOk;
    VOS_UINT32                          ulDlRecvHspdschCrcError;
    VOS_UINT32                          ulDlRecvHiSichNum;

    VOS_UINT32                          ulSyncLoss;
    VOS_UINT32                          ulLossMsgID[TDS_MAC_LOSS_MSG_MAX_NUM];
    VOS_UINT32                          ulLossMsgIndex;

/*added by z00275692 for TDS L2 可维可测特性开发2015-8-4*/
   VOS_UINT32                          ulAsSearchRfReqNum;
   VOS_UINT32                          ulAsSearchRfRelNum;
   VOS_UINT32                          ulAsSearchRfCnfNum;
   VOS_UINT32                          ulSndSigProIndNum;
   VOS_UINT32                          ulSndSigDeProIndNum;
   VOS_UINT32                          ulFchNoRfIndNum;
   VOS_UINT32                          ulFchHaveRfIndNum;
   VOS_UINT32                          ulDchNoRfIndNum;
   VOS_UINT32                          ulDchHaveRfIndNum;
}TL_OM_TDS_MAC_STAT_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_TDS_L2_OVERVIEW_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TDS L2概略统计信息上报结构体
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;

    /*More to add*/

}TL_OM_TDS_L2_OVERVIEW_STAT_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_LTE_PDCP_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE PDCP统计信息上报结构体
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;

    /*More to add*/
    /*APP*/
    VOS_UINT32                          ulAppRxIpPktCnt;
    VOS_UINT32                          ulAppRxIpPktLen;
    VOS_UINT32                          ulMemTransFailNum;
    VOS_UINT32                          ulEnAppReqQueSucc;
    VOS_UINT32                          ulEnAppReqQueFail;
    VOS_UINT32                          ulDeAppReqQueSucc;
    VOS_UINT32                          ulRelAppReqQueNum;

    /*UL*/
    VOS_UINT32                          ulULTotlRxDrbSduCnt;
    VOS_UINT32                          ulULTotlTxDrbPduCnt;
    VOS_UINT32                          ulULTotlRxSrbSduCnt;
    VOS_UINT32                          ulULTotlTxSrbPduCnt;
    VOS_UINT32                          usULTotlFreeSduCnt;
    VOS_UINT32                          ulULTotlRbidErrCnt;

    VOS_UINT32                          ulULTotlRxDrbSduLen;
    VOS_UINT32                          ulULTotlTxDrbPduLen;
    VOS_UINT32                          ulULTotlRxSrbSduLen;
    VOS_UINT32                          ulULTotlTxSrbPduLen;

    /*DL*/
    VOS_UINT32                          ulDLTotlRxDrbPduCnt;
    VOS_UINT32                          ulDLTotlTxDrbSduCnt;
    VOS_UINT32                          ulDLTotlRxSrbPduCnt;
    VOS_UINT32                          ulDLTotlTxSrbSduCnt;
    VOS_UINT32                          ulDLTotlRbidErrCnt;

    VOS_UINT32                          ulDLTotlRxDrbPduLen;
    VOS_UINT32                          ulDLTotlTxDrbSduLen;
    VOS_UINT32                          ulDLTotlRxSrbPduLen;
    VOS_UINT32                          ulDLTotlTxSrbSduLen;

    /*Secu Stat*/
    VOS_UINT32                          ulCh1ChkErrIntCnt;
    VOS_UINT32                          ulCh1CmpIntCnt;
    VOS_UINT32                          ulCh1ChkErrEventCnt;
    VOS_UINT32                          ulCh1CmpEventCnt;
    VOS_UINT32                          ulCh2OneCmpIntCnt;
    VOS_UINT32                          ulCh2CmpEventCnt;
    VOS_UINT32                          ulCh3OneCmpIntCnt;
    VOS_UINT32                          ulCh3CmpEventCnt;
    VOS_UINT32                          ulCh3BdFullCnt;

}TL_OM_LTE_PDCP_ALL_RB_STAT_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_LTE_PDCP_UL_RB_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE PDCP 上行RB统计信息上报结构体
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;

    /*新增*/
    VOS_UINT32                          ulRxSduNum;
    VOS_UINT32                          ulRxSduLen;
    VOS_UINT32                          ulDiscardSduNum;
    VOS_UINT32                          ulDiscardSduLEn;
    VOS_UINT32                          ulAckedSduNum;
    VOS_UINT32                          ulEnSduQueFailNum;
    VOS_UINT32                          ulPduFullDiscardNum;

    VOS_UINT32                          ulTxDataPduNum;
    VOS_UINT32                          ulTxDataPduLen;
    VOS_UINT32                          ulTxCtrlPduNum;
    VOS_UINT32                          ulTxCtrlPduLen;
    VOS_UINT32                          ulHoRetxPduNum;
    VOS_UINT32                          ulHoRetxPduLen;
    VOS_UINT32                          ulRxEnbCtrlPduNum;
    VOS_UINT32                          ulTxRohcFeedBackNum;

    VOS_UINT32                          ulRohcSduNum;
    VOS_UINT32                          ulRohcFailNum;
    VOS_UINT32                          ulRohcSduLen;
    VOS_UINT32                          ulRohcComredSduLen;

    /*More to add,根据新增情况进行删除*/
    VOS_UINT32                          ulUlRxSduCnt;
    VOS_UINT32                          ulUlTxPduCnt;
    VOS_UINT32                          ulUlAckedSduCnt;

    VOS_UINT32                          ulUlDiscardMaxCnt;
    VOS_UINT32                          ulUlDisSduCnt;
    VOS_UINT32                          ulUlBufFullDisSduCnt;
    VOS_UINT32                          ulUlReestDiscardCnt;

    VOS_UINT32                          ulUlInvalidSduCnt;
    VOS_UINT32                          ulUlTxCtrlPduNum;
    VOS_UINT32                          ulUlAckEndSnError;

    VOS_UINT32                          ulCompSuccCnt;
    VOS_UINT32                          ulCompFailCnt;
    VOS_UINT32                          ulRohcCompCnt;

    VOS_UINT32                          ulSduEnQueFailCnt;
    VOS_UINT32                          ulUlDisFirstSduCnt;
    VOS_UINT32                          ulHighSduEnQueCnt;
    VOS_UINT32                          ulLowSduEnQueCnt;

}TL_OM_LTE_PDCP_UL_RB_STAT_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_LTE_PDCP_DL_RB_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE PDCP下行RB统计信息上报结构体
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;

    /*新增*/
    VOS_UINT32                          ulRxDataPduNum;
    VOS_UINT32                          ulRxDataPduLen;
    VOS_UINT32                          ulRxStatusPduNum;
    VOS_UINT32                          ulRxRohcCtrlPduNum;

    VOS_UINT32                          ulTxSduNum;
    VOS_UINT32                          ulTxSduLen;
    VOS_UINT32                          ulTxCtrlPduNum;
    VOS_UINT32                          ulTxCtrlPduLen;

    VOS_UINT32                          ulPduDupNum;
    VOS_UINT32                          ulPduOutOfWinNum;
    VOS_UINT32                          ulPduInvalidNum;
    VOS_UINT32                          ulPduExceptFreeNum;
    VOS_UINT32                          ulPduDeCipherErr;
    VOS_UINT32                          ulRohcFailNum;


    /*More to add,根据新增情况进行删除*/
    VOS_UINT32                          ulDlRxPduCnt;
    VOS_UINT32                          ulDlRxCtlPduCnt;
    VOS_UINT32                          ulDlTxStrpPduCnt;
    VOS_UINT32                          ulDlTxRohcPduCnt;
    VOS_UINT32                          ulDlErrPduRlcIndCnt;

    VOS_UINT32                          ulDlExecReordCnt;
    VOS_UINT32                          ulDlCipherBufFullCnt;
    VOS_UINT32                          ulDlAmRlcDataErrCnt;
    VOS_UINT32                          ulDlRlcDataErrCnt;

    VOS_UINT32                          ulDlUnCompFailCnt;
    VOS_UINT32                          ulHoUnCompFailCnt;
    VOS_UINT32                          ulDeCompSuccCnt;
    VOS_UINT32                          ulDeCompFailCnt;
    VOS_UINT32                          ulRohcDeCompCnt;
    VOS_UINT32                          ulDlRecvFeedbackCnt;
    VOS_UINT32                          ulDlRecvFeedbackSuccCnt;
    VOS_UINT32                          ulDecompFdbkUnkown;

}TL_OM_LTE_PDCP_DL_RB_STAT_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_LPDCP_CIPHER_CH_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE PDCP Cipher通道统计信息
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;

    VOS_UINT32                          ulRxSduCnt;
    VOS_UINT32                          ulRxLenErrSdu;

    /*直通通道*/
    VOS_UINT32                          ulThrChRxSduCnt;
    VOS_UINT32                          ulThrChDirDiscard;
    VOS_UINT32                          ulThrChGetDeftEpsFail;
    VOS_UINT32                          ulThrChEnQueFail;
    VOS_UINT32                          ulThrChEnQueSucc;
    VOS_UINT32                          ulThrChHaveNoBDCnt;

    VOS_UINT32                          ulThrChCfgBdFailCnt;
    VOS_UINT32                          ulThrChCfgBdSuccCnt;
    VOS_UINT32                          ulThrChCfgBdNum;
    VOS_UINT32                          ulThrChFreeBdNum;

    VOS_UINT32                          ulThrChSrcMemSaveSucc;
    VOS_UINT32                          ulThrChSrcMemSaveFail;
    VOS_UINT32                          ulThrChSrcMemFreeCnt;
    VOS_UINT32                          ulThrChFreeDeCipherSdu;

    /*非直通通道*/
    VOS_UINT32                          ulNonThrChRxSduCnt;
    VOS_UINT32                          ulNonThrChEnQueFail;
    VOS_UINT32                          ulNonThrChEnQueSucc;

    VOS_UINT32                          ulNonThrChHaveNOBdCnt;
    VOS_UINT32                          ulNonThrChCfgBdFailCnt;
    VOS_UINT32                          ulNonThrChCfgBdSuccCnt;
    VOS_UINT32                          ulNonThrChCfgBdNum;
    VOS_UINT32                          ulNonThrChFreeBdNum;

    VOS_UINT32                          ulNonThrChSrcMemSaveSucc;
    VOS_UINT32                          ulNonThrChSrcMemSaveFail;
    VOS_UINT32                          ulNonThrChSrcMemFreeCnt;
    VOS_UINT32                          ulNonThrChFreeDeCipherSdu;

}TL_OM_LPDCP_CIPHER_CH_STAT_INFO_STRU;


/*****************************************************************************
 结构名    : TL_OM_LTE_RLC_UL_RB_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE RLC上行统计信息上报结构体
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU    stCommHead;

    /*新增*/
    VOS_UINT32              ulRxSduNum;
    VOS_UINT32              ulRxSduLen;
    VOS_UINT32              ulDiscardSduNum;
    VOS_UINT32              ulDiscardSduLen;
    VOS_UINT32              ulTxSduSuccNum;
    VOS_UINT32              ulTxSduFailNum;

    VOS_UINT32              ulLMacNtfSchedNum;
    VOS_UINT32              ulTxNullPduNum;
    VOS_UINT32              ulRlcNoSduNum;
    VOS_UINT32              ulTxRlcPduNum;
    VOS_UINT32              ulTxRlcPduLen;

    VOS_UINT32              ulTxNewDataPduNum;
    VOS_UINT32              ulTxNewDataPduLen;
    VOS_UINT32              ulTxCtrlPduNum;
    VOS_UINT32              ulTxCtrlPduLen;
    VOS_UINT32              ulRetxPduNum;
    VOS_UINT32              ulRetxPduLen;
    VOS_UINT32              ulRetxSegNum;
    VOS_UINT32              ulTxPollPduNum;
    VOS_UINT32              ulPollRetxTMrExpiry;

    VOS_UINT32              ulEnbCtrlPduNum;                /*收到ENB状态报告个数*/
    VOS_UINT32              ulInvalidEnbCtrlPduNum;         /*无效状态报告个数*/
    VOS_UINT32              ulNackIndPduNum;                /*NACK指示重传PDU个数*/
    VOS_UINT32              ulNackIndSegNum;                /*NACK指示重传Segment PDU个数*/


    /*More to add,根据新增内容进行删除*/
    VOS_UINT32              ulRlcDropSdu;
    VOS_UINT32              ulQueFullDropSdu;
    VOS_UINT32              ulDropSduNoRsn;
    VOS_UINT32              ulResNotEnough;
}TL_OM_LTE_RLC_UL_RB_STAT_INFO_STRU;


/*****************************************************************************
 结构名    : TL_OM_LTE_RLC_DL_RB_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE RLC 下行统计信息上报结构体
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU    stCommHead;

    /*新增*/
    VOS_UINT32              ulRxPduNum;
    VOS_UINT32              ulRxPduLen;
    VOS_UINT32              ulRxDataPduNum;
    VOS_UINT32              ulRxDataPduLen;
    VOS_UINT32              ulRxCtrlPduNum;
    VOS_UINT32              ulRxCtrlPduLen;
    VOS_UINT32              ulMissedUmPduNum;
    VOS_UINT32              ulInvalidPduNum;
    VOS_UINT32              ulDiscardPduNum;
    VOS_UINT32              ulDupPduNum;
    VOS_UINT32              ulProcPduFail;

    VOS_UINT32              ulTxSduNum;
    VOS_UINT32              ulTxSduLen;
    VOS_UINT32              ulTxDlCtrlPduNum;
    VOS_UINT32              ulReorderTmrStartNum;
    VOS_UINT32              ulReorderTmrExpiryNum;

    VOS_UINT32              ulDiscardHeadSgmnt;
    VOS_UINT32              ulDiscardTailSgmnt;
    VOS_UINT32              ulResmPduFail;

    /*More to add,根据新增内容进行删除*/
    VOS_UINT32              ulReRecvSnDrop;
    VOS_UINT32              ulRecePduSeg;

}TL_OM_LTE_RLC_DL_RB_STAT_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_LTE_MAC_RA_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE MAC 随机接入统计信息上报结构体
*****************************************************************************/
typedef struct
{

    TL_OM_COMM_HEAD_STRU                      stCommHead;

    /*More to add*/
    VOS_UINT32                                ulMacRaReq;
    VOS_UINT32                                ulPdcchNonContentRaReq;
    VOS_UINT32                                ulPdcchContentRaReq;
    VOS_UINT32                                ulRrcNonContentRaReq;
    VOS_UINT32                                ulRrcContentRaReq;
    VOS_UINT32                                ulSelectGroupA;
    VOS_UINT32                                ulSelectGroupB;

    VOS_UINT32                                ulRecvPhyRaCnf;
    VOS_UINT32                                ulRepeatRaReq;
    VOS_UINT32                                ulMaxRaReq;

    VOS_UINT32                                ulRarTimerOut;
    VOS_UINT32                                ulContentTimerOut;
    VOS_UINT32                                ulRaCnfTimerOut;

    VOS_UINT32                                ulRaCauseFail;
    VOS_UINT32                                ulSelectGroupABFail;

    VOS_UINT32                                ulRecvRarNum;
    VOS_UINT32                                ulRecvRarSucc;
    VOS_UINT32                                ulRecvRarFail;
    VOS_UINT32                                ulRarBiNum;
    VOS_UINT32                                ulRarProcSucc;
    VOS_UINT32                                ulNonContentSucc;

    VOS_UINT32                                ulRecvContentionNum;
    VOS_UINT32                                ulWaitContentionProcFail;

    VOS_UINT32                                ulContentTcrntiSucc;
    VOS_UINT32                                ulContentCrntiSucc;
    VOS_UINT32                                ulContentNoMatch;

    VOS_UINT32                                ulSchMsg3Num;
    VOS_UINT32                                ulSchMsg3ReTransNum;
    VOS_UINT32                                ulGetMsg3FromRlcFail;

    VOS_UINT32                                ulMacNewMsg3Rrctrig;
    VOS_UINT32                                ulMacNewMsg3Mactrig;
    VOS_UINT32                                ulMacNewMsg3MacPdu;
    VOS_UINT32                                ulHoMsg3NoRecvCmp;
    VOS_UINT32                                ulMacRetranMsg3Num;
    VOS_UINT32                                ulMacActiveRetranMsg3Num;
    VOS_UINT32                                ulMacOverMsg3MaxRetran;

    VOS_UINT32                                ulStateErrorDrop;
    VOS_UINT32                                ulSendRlcSetupOkNum;
    VOS_UINT32                                ulRarSchedNotFinishNum;
    VOS_UINT32                                ulNoRarCfgCnfNum;

} TL_OM_LTE_MAC_RA_STAT_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_LTE_MAC_UL_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE MAC 上行统计信息上报结构体
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                      stCommHead;
    /*新增*/
    VOS_UINT32                                ulRxSduNum;
    VOS_UINT32                                ulRxSduLen;
    VOS_UINT32                                ulRxSchFrmInd;
    VOS_UINT32                                ulRxUlGrantNum;
    VOS_UINT32                                ulUlGrantNotSchNum;

    VOS_UINT32                                ulSchedPduNum;
    VOS_UINT32                                ulSchedPduLen;
    VOS_UINT32                                ulSchNotFinishNum;
    VOS_UINT32                                ulStartAccNum;

    VOS_UINT32                                ulTxPreambleNum;
    VOS_UINT32                                ulTxCRntiNum;
    VOS_UINT32                                ulTxCcchNum;
    VOS_UINT32                                ulTxSrNum;
    VOS_UINT32                                ulPhyCancelSrNum;
    VOS_UINT32                                ulMacCancelSrNum;
    VOS_UINT32                                ulTxPhrNum;
    VOS_UINT32                                ulTxShortBsrNum;
    VOS_UINT32                                ulTxLongBsrNum;
    VOS_UINT32                                ulTxTruncatedBsrNum;
    VOS_UINT32                                ulTxPadShortBsrNum;
    VOS_UINT32                                ulTxPadLongBsrNum;
    VOS_UINT32                                ulCancelBsrNum;
    VOS_UINT32                                ulTxPaddingNum;

    VOS_UINT32                                ulTaTmrExpiryNum;
    VOS_UINT32                                ulScellDeactTmrExpiryNum;
    VOS_UINT32                                ulMacRelUlSpsNum;
    VOS_UINT32                                ulPhyRelUlSpsNum;
    VOS_UINT32                                ulForbidDspSleepErrNum;
    VOS_UINT32                                ulWriteDeiMailErrNum;

    /*More to add,根据情况进行删除*/
    VOS_UINT32                                ulGetRlcNuLLBuffNum;
    VOS_UINT32                                ulGetCcchInActiveNum;
    VOS_UINT32                                ulGetLchPriFromRlcFail;
    VOS_UINT32                                ulSendAbnormBsr;

    /*上行ACC统计量*/
    VOS_UINT32                                  ulAccEnableNoIdleCh;            /*使能ACC时刻发现通道不空闲*/
    VOS_UINT32                                  ulAccEnableSucc;                /*使能ACC成功统计*/
    VOS_UINT32                                  ulAccEnableFail;                /*使能ACC失败统计*/
    VOS_UINT32                                  ulAccEnableMissTime;            /*错过发送时机的统计*/
    VOS_UINT32                                  ulAccNotEnable;                 /*ACC没有使能统计*/
    VOS_UINT32                                  ulAccNotFinish;                 /*ACC没有搬移完成统计*/

    VOS_UINT32                                  ulAccCfgGetBdQFail;             /*ACC配置获取BDQ失败次数*/
    VOS_UINT32                                  ulAccCfgCipherNodeSucc;         /*ACC配置Cipher节点成功次数*/
    VOS_UINT32                                  ulAccCfgCipherNodeFail;         /*ACC配置Cipher节点失败次数*/
    VOS_UINT32                                  ulAccCfgDmaNodeSucc;            /*ACC配置DMA节点成功次数*/
    VOS_UINT32                                  ulAccCfgDmaNodeFail;            /*ACC配置DMA节点失败次数*/
    VOS_UINT32                                  ulAccCfgDataTypeErr;            /*ACC配置类型错误统计*/
    VOS_UINT32                                  ulAccCfgOffsetErr;              /*ACC配置偏移错误*/
    VOS_UINT32                                  ulAccCfgOverMaxNode;            /*ACC超过最大搬移的节点数统计*/
    VOS_UINT32                                  ulBbpMacPduValidFlgNotClr;      /*BBP MAC PDU有效标志未及时清除次数*/

    /*L2投票状态记录，最后一次投票的状态*/
    VOS_UINT32                                  ulLHpaState;
    VOS_UINT32                                  ulTotalBuffSize;
    VOS_UINT32                                  ulAmBuffSize;
    VOS_UINT32                                  ulLRlcUlSleepFlg;
    VOS_UINT32                                  ulLRlcDlSleepFlg;
    VOS_UINT32                                  ulLPsSleepFlg;

}TL_OM_LTE_MAC_UL_STAT_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_LTE_MAC_DL_STAT_INFO_STRUE
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE MAC 下行统计信息上报结构体
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                      stCommHead;

    /*新增*/
    VOS_UINT32                                ulRxDlTbIntNum;
    VOS_UINT32                                ulAllocDlTbNum;
    VOS_UINT32                                ulGetDlTbNum;

    VOS_UINT32                                ulRxBcchTbNum;
    VOS_UINT32                                ulRxPbchTbNum;
    VOS_UINT32                                ulRxPchTbNum;
    VOS_UINT32                                ulRxPduNum;
    VOS_UINT32                                ulRxPduLen;
    VOS_UINT32                                ulPduDemutiSuccNum;
    VOS_UINT32                                ulPduDemutiFailNum;
    VOS_UINT32                                ulRxTaMceNum;
    VOS_UINT32                                ulRxScellMceNum;
    VOS_UINT32                                ulRxDrxMceNum;
    VOS_UINT32                                ulRxPaddingNum;
    VOS_UINT32                                ulTxSduToRlcNum;
    VOS_UINT32                                ulTxSduToRlcLen;

    /*More to add，根据情况进行删除*/

    VOS_UINT32                                ulDlTbRecvIntErr;                 /*V7R2*/
    VOS_UINT32                                ulDlForbidDspSleepFail;           /*V7R2*/

    VOS_UINT32                                ulActSendRlcErrorNum;
    VOS_UINT32                                ulActDemulOneLchErr;
    VOS_UINT32                                ulActRecvErrPkt;


    VOS_UINT32                                ulDlTbCheckErr;

    VOS_UINT32                                ulRadnomStateRecvTb;
    VOS_UINT32                                ulRadnomStateRecvTbErr;

    VOS_UINT32                                ulMacPdcchRecvTb;

    VOS_UINT32                                ulDlTbIntAllocMemFail;
    VOS_UINT32                                ulDlLteMasterGetMemFail;
    VOS_UINT32                                ulDlLteSlaveGetMemFail;
    VOS_UINT32                                ulDlTbRecvQueFull;
    VOS_UINT32                                ulDlTbAllocMemNum;
    VOS_UINT32                                ulDlTbMemMacFreeNum;
    VOS_UINT32                                ulDlMacGetDlTbNum;
    VOS_UINT32                                ulDlTbAddrNull;
    VOS_UINT32                                ulDlTbMemCheckErr;
    VOS_UINT32                                ulDlTbCtrlInfoErr;
    VOS_UINT32                                ulDlRecvTbSegErr;
    VOS_UINT32                                ulDlRecvTbSegOk;

}TL_OM_LTE_MAC_DL_STAT_INFO_STRU;

#define TL_OM_LMAC_CA_MAX_RPT_CELL_NUM      (8)
/*****************************************************************************
 结构名    : TL_OM_LTE_MAC_CA_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE MAC CA 统计信息上报结构体.Index =0 为主小区.
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                      stCommHead;

    /*More to add*/
    LSCELL_STATUS_ENUM_UINT8                  ucScellStatusType[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];
    LSCELL_DEACT_TIMER_VIEW_ENUM_UINT32       ulScellDeactTimer[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];
    VOS_UINT32                                ulConfigedNum[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];           /*配置对应SCell个数*/
    VOS_UINT32                                ulDeletedNum[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];            /*删除对应SCell个数*/
    VOS_UINT32                                ulRecvActiveMceNum[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];      /*接收到对应SCell激活控制元个数*/
    VOS_UINT32                                ulSendActiveToPhyNum[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];    /*发送对应SCell的激活命令给DSP的个数*/
    VOS_UINT32                                ulRecvDeactiveMceNum[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];    /*接收到对应SCell去激活控制元个数*/
    VOS_UINT32                                ulSendDeactiveToPhyNum[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];  /*发送对应SCell的去激活命令给DSP的个数*/
    VOS_UINT32                                ulRecvDlAssignmentNum[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];   /*接收到对应SCell的下行指派的个数*/
    VOS_UINT32                                ulDeactiveTimerOutNum[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];   /*对应SCell去激活定时器超时的次数*/
    VOS_UINT32                                ulRecvDlTbNum[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];           /*对应SCell接收到下行TB块的个数*/
    VOS_UINT32                                ulRecvDlTbByte[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];          /*对应SCell接收到下行TB字节数*/
    LMAC_SCELL_CFG_STATUS_ENUM_UINT8          ucUlCaCfgStatus[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];         /*配置对应上行CA的状态*/
    LMAC_SCELL_CFG_STATUS_ENUM_UINT8          ucDlCaCfgStatus[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];         /*配置对应下行CA的状态*/

}TL_OM_LTE_MAC_CA_STAT_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_LTE_MAC_MBMS_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE MAC MBMS 统计信息上报结构体
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                      stCommHead;

    /*More to add*/
    VOS_UINT32                                ulMchRecvSucc;                    /*MCH解析成功个数*/
    VOS_UINT32                                ulMchRecvFail;                    /*MCH解析失败个数*/
    VOS_UINT32                                ulMchRecvPadding;
    VOS_UINT32                                ulMchMsiNum;
    VOS_UINT32                                ulPmchInValidCnt;
    VOS_UINT32                                ulMcchRecvCnt;
    VOS_UINT32                                ulMtchRecvCnt;

}TL_OM_LTE_MAC_MBMS_STAT_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_LTE_L2_OVERVIEW_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE L2概略统计信息上报结构体
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;

    /*More to add*/

}TL_OM_LTE_L2_OVERVIEW_STAT_INFO_STRU;


/*需要总和考虑性能和LOG量*/
#define TL_OM_LTE_MAX_RPT_NUM                   (200)
#define TL_OM_LTE_IP_RPT_MAX_NUM                (200)
#define TL_OM_LTE_UL_PDU_RPT_MAX_NUM            (100)
#define TL_OM_LTE_DL_PDU_RPT_MAX_NUM            (160)
#define TL_OM_LTE_PDCP_DL_SDU_RPT_MAX_NUM       (140)
#define TL_OM_LTE_RLC_AM_CTRL_PDU_RPT_MAX_NUM   (50)
#define TL_OM_LTE_RLC_MAX_NACK_RPT_NUM          (4)
#define TL_OM_LTE_MAC_UL_PDU_DATA_LEN           (16)
#define TL_OM_LTE_MAC_DL_PDU_DATA_LEN           (8)

/*最大逻辑信道个数*/
#define TL_OM_LTE_MAC_MAX_LCH_NUM               (11)
/*上报BUFFER状态的个数*/
#define TL_OM_LTE_MAC_BUF_STATUS_RPT_NUM        (10)

/*****************************************************************************
 枚举名    : TL_OM_LTE_MAC_PDU_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LTE MAC PDU类型
*****************************************************************************/
typedef enum
{
    TL_OM_LTE_MAC_PDU_TYPE_DATA                     = 0x01,
    TL_OM_LTE_MAC_PDU_TYPE_SR_TX                    = 0x02,
    TL_OM_LTE_MAC_PDU_TYPE_PREAMBLE                 = 0x03,
    TL_OM_LTE_MAC_PDU_TYPE_SR_REQ                   = 0x04,
    TL_OM_LTE_MAC_PDU_TYPE_MAC_CANCEL_SR            = 0x05,
    TL_OM_LTE_MAC_PDU_TYPE_PHY_CANCEL_SR            = 0x06,
    TL_OM_LTE_MAC_PDU_TYPE_SCHED_FAIL               = 0x07,/*调度失败*/
    TL_OM_LTE_MAC_PDU_TYPE_MSG3_RETX                = 0x08,
    TL_OM_LTE_MAC_PDU_TYPE_LMAC_SPS_REL             = 0x09,
    TL_OM_LTE_MAC_PDU_TYPE_PDCCH_ULSPS_REL          = 0x0A,
    TL_OM_LTE_MAC_PDU_TYPE_RETX_BSR_TMROUT          = 0x0B,
    TL_OM_LTE_MAC_PDU_TYPE_PERI_BSR_TMROUT          = 0x0C,
    TL_OM_LTE_MAC_PDU_TYPE_PERI_PHR_TMROUT          = 0x0D,
    TL_OM_LTE_MAC_PDU_TYPE_SCELL_DEACTTIMER_TMROUT  = 0x0E,
    TL_OM_LTE_MAC_PDU_TYPE_TAG_TMROUT               = 0x0F,
    TL_OM_LTE_MAC_PDU_TYPE_BUTT
} TL_OM_LTE_MAC_PDU_TYPE_ENUM;

/*****************************************************************************
 枚举名    : TL_OM_LTE_PDCP_PDU_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LTE PDCP PDU类型
*****************************************************************************/
typedef enum
{
    TL_OM_LTE_PDCP_PDU_TYPE_DATA                    = 0x00,
    TL_OM_LTE_PDCP_PDU_TYPE_CTRL                    = 0x01,
    TL_OM_LTE_PDCP_PDU_TYPE_PDU_DISCARD             = 0x02,
    TL_OM_LTE_PDCP_PDU_TYPE_BUTT
} TL_OM_LTE_PDCP_PDU_TYPE_ENUM;

/*****************************************************************************
 枚举名    : TL_OM_LTE_RLC_TIMER_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LTE RLC PDU类型
*****************************************************************************/
typedef enum
{
    TL_OM_LTE_RLC_UM_PDU_TYPE_DISCARD            = 0x01,
    TL_OM_LTE_RLC_PDU_TYPE_BUTT
} TL_OM_LTE_RLC_PDU_TYPE_ENUM;

/*****************************************************************************
 枚举名    : TL_OM_LTE_RLC_TIMER_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LTE RLC TIMER相关定时器类型
*****************************************************************************/
typedef enum
{
    TL_OM_LTE_RLC_TIMER_TYPE_DL_REORDER             = 0x00,
    TL_OM_LTE_RLC_TIMER_TYPE_AM_DL_STATUS_PROHIBIT  = 0x01,
    TL_OM_LTE_RLC_TIMER_TYPE_BUTT
} TL_OM_LTE_RLC_TIMER_TYPE_ENUM;


/*****************************************************************************
 结构名    : TL_OM_IP_PKT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 保存IP关键信息
*****************************************************************************/
typedef struct
{
    VOS_UINT8                   ucIpVer;
    VOS_UINT8                   ucProtocol;
    VOS_UINT16                  usIpId;

    VOS_UINT32                  ulTcpSn;
    VOS_UINT32                  ulTcpAckSn;
} TL_OM_IP_PKT_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_CDS_IP_PKT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 保存CDS IP关键信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulTimeStamp;
    VOS_UINT8                   ucDir;/*0-上行,1-下行*/
    VOS_UINT8                   ucType;
    VOS_UINT8                   ucRabId;
    VOS_UINT8                   ucModemId;
    TL_OM_IP_PKT_INFO_STRU      stIpPktInfo;
} TL_OM_CDS_IP_PKT_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_CDS_IP_PKT_INFO_ARRAY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS IP信息数组
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulRptNum;
    TL_OM_CDS_IP_PKT_INFO_STRU      astCdsIpPktInfo[TL_OM_LTE_IP_RPT_MAX_NUM];
} TL_OM_CDS_IP_PKT_INFO_ARRAY_STRU;

/*****************************************************************************
 结构名    : TL_OM_LPDCP_UL_PDU_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 保存LPDCP UL PDU&IP关键信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                usFrame       :10;
    VOS_UINT16                usSubFrame    :6;
    VOS_UINT16                usPdcpSn;

    VOS_UINT8                 ucRbId;
    VOS_UINT8                 ucRlcMode     :2;
    VOS_UINT8                 ucPduType     :2;
    VOS_UINT8                 ucSnBitNum    :4;
    VOS_UINT16                usStampH16Bit;

    VOS_UINT32                ulStampL32Bit;

    VOS_UINT16                usNextAckSn;
    VOS_UINT16                usPduLen;

    VOS_UINT32                ulCount;
    VOS_UINT32                ulBuffTime;   /*在PDCP缓存的时间*/
    TL_OM_IP_PKT_INFO_STRU    stIpPktInfo;
} TL_OM_LPDCP_UL_PDU_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_LPDCP_UL_PDU_INFO_ARRAY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LPDCP UL PDU信息缓存数组
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulRptNum;
    TL_OM_LPDCP_UL_PDU_INFO_STRU    astLPdcpUlPduInfo[TL_OM_LTE_UL_PDU_RPT_MAX_NUM];
} TL_OM_LPDCP_UL_PDU_INFO_ARRAY_STRU;

/*****************************************************************************
 结构名    : TL_OM_LPDCP_DL_PDU_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 保存LPDCP DL PDU&LRLC DL PDU SN关键信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  bitSysFrame     :10;
    VOS_UINT32                  bitSubFrame     :4;
    VOS_UINT32                  bitRbId         :8;
    VOS_UINT32                  bitRlcMode      :4;
    VOS_UINT32                  bitSnBitNum     :4;
    VOS_UINT32                  ulPduType       :2;

    VOS_UINT16                  usPdcpSn;
    VOS_UINT16                  usStampH16Bit;

    VOS_UINT32                  ulStampL32Bit;

    VOS_UINT16                  usPduLen;
    VOS_UINT16                  usRlcSn;

    VOS_UINT16                  usNextRxSn;
    VOS_UINT16                  usLastSubmitSn;

    VOS_UINT32                  ulRxHfn;
} TL_OM_LPDCP_DL_PDU_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_LPDCP_DL_PDU_INFO_ARRAY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LPDCP DL PDU上报结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulRptNum;
    TL_OM_LPDCP_DL_PDU_INFO_STRU    astLPdcpDlPduInfo[TL_OM_LTE_DL_PDU_RPT_MAX_NUM];
} TL_OM_LPDCP_DL_PDU_INFO_ARRAY_STRU;

/*****************************************************************************
 结构名    : TL_OM_LPDCP_DL_SDU_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 保存LPDCP DL SDU&IP关键信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  bitSysFrame     :10;
    VOS_UINT32                  bitSubFrame     :4;
    VOS_UINT32                  bitRbId         :8;
    VOS_UINT32                  bitDiscardFlg   :1;
    VOS_UINT32                  bitResv         :9;

    VOS_UINT32                  ulStampL32Bit;
    VOS_UINT16                  usStampH16Bit;
    VOS_UINT16                  usPdcpSn;

    VOS_UINT16                  usSduLen;
    VOS_UINT16                  usRlcSn;
    VOS_UINT32                  ulCount;

    TL_OM_IP_PKT_INFO_STRU      stIpPktInfo;
} TL_OM_LPDCP_DL_SDU_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_LPDCP_DL_SDU_INFO_ARRAY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LPDCP DL SDU信息数组
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulRptNum;
    TL_OM_LPDCP_DL_SDU_INFO_STRU    astLPdcpDlSduInfo[TL_OM_LTE_PDCP_DL_SDU_RPT_MAX_NUM];
} TL_OM_LPDCP_DL_SDU_INFO_ARRAY_STRU;

/*****************************************************************************
 结构名    : TL_OM_LRLC_UL_PDU_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 保存LRLC UL PDU&LPDCP UL PDU SN关键信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  usProcFrame     :10;/*处理时刻*/
    VOS_UINT16                  usProcSubFrame  :6;
    VOS_UINT16                  usAirFrame      :10;/*空口发送时刻*/
    VOS_UINT16                  usAirSubFrame   :6;

    VOS_UINT16                  usRlcSn;
    VOS_UINT8                   ucRbId;
    VOS_UINT8                   ucRetxNum;

    VOS_UINT16                  usPduLen;
    VOS_UINT16                  usPduType       :1;
    VOS_UINT16                  usRF            :1;
    VOS_UINT16                  usPolling       :1;
    VOS_UINT16                  usFi            :2;
    VOS_UINT16                  usAckSn         :10;
    VOS_UINT16                  usRptType       :1;

    VOS_UINT16                  usEndPdcpSn;
    VOS_UINT16                  usVTs_VTus;

    VOS_UINT16                  usVTa;
    VOS_UINT16                  usVTms;
} TL_OM_LRLC_UL_PDU_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_LRLC_UL_PDU_INFO_ARRAY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRLC UL PDU上报结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulRptNum;
    TL_OM_LRLC_UL_PDU_INFO_STRU     astLRlcUlPduInfo[TL_OM_LTE_DL_PDU_RPT_MAX_NUM];
} TL_OM_LRLC_UL_PDU_INFO_ARRAY_STRU;

/*****************************************************************************
 结构名    : TL_OM_LRLC_DL_PDU_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 保存LRLC DL PDU关键信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                usProcFrame       :10; /*处理时刻*/
    VOS_UINT16                usProcSubFrame    :6;
    VOS_UINT16                usAirFrame        :10; /*空口时刻*/
    VOS_UINT16                usAirSubFrame     :6;

    VOS_UINT16                usRlcSn;
    VOS_UINT8                 ucRbId;
    VOS_UINT8                 ucPduType       : 1;
    VOS_UINT8                 ucPolling       : 1;
    VOS_UINT8                 ucFi            : 2;
    VOS_UINT8                 ucRf            : 2;
    VOS_UINT8                 ucTmrType       : 2;

    VOS_UINT16                usAckSn;
    VOS_UINT16                usPduLen;
    VOS_UINT16                usVRr_VRur;
    VOS_UINT16                usVRh_VRuh;

    VOS_UINT16                usVRx_VRux;
    VOS_UINT16                usVRms;
} TL_OM_LRLC_DL_PDU_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_LRLC_DL_PDU_INFO_ARRAY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRLC DL PDU上报结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulRptNum;
    TL_OM_LRLC_DL_PDU_INFO_STRU     astLRlcDlPduInfo[TL_OM_LTE_DL_PDU_RPT_MAX_NUM];
} TL_OM_LRLC_DL_PDU_INFO_ARRAY_STRU;


/*****************************************************************************
 结构名    : TL_OM_LRLC_AM_CTRL_PDU_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 保存LRLC AM状态报告
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  usFrame;
    VOS_UINT8                   ucSubFrame;
    VOS_UINT8                   ucDirection     :4;
    VOS_UINT8                   ucNackNum       :4;

    VOS_UINT8                   ucRbId;
    VOS_UINT8                   ucLchId;
    VOS_UINT16                  usAckSn;

    VOS_UINT16                  ausNackSn[TL_OM_LTE_RLC_MAX_NACK_RPT_NUM];
} TL_OM_LRLC_AM_CTRL_PDU_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_LRLC_AM_CTRL_PDU_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 保存LRLC AM状态报告
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulRptNum;
    TL_OM_LRLC_AM_CTRL_PDU_INFO_STRU        astLRlcAmCtrlPduInfo[TL_OM_LTE_RLC_AM_CTRL_PDU_RPT_MAX_NUM];
} TL_OM_LRLC_AM_CTRL_PDU_INFO_ARRAY_STRU;

/*****************************************************************************
 结构名    : TL_OM_LMAC_UL_PDU_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 保存LMAC UL PDU关键信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulStampL32Bit;

    VOS_UINT32                  bitStampH16Bit  :16;
    VOS_UINT32                  bitAirFrame     :10;
    VOS_UINT32                  bitAirSubFrame  :4;
    VOS_UINT32                  bitTbIndex      :2;

    VOS_UINT32                  bitPduType      :4;
    VOS_UINT32                  bitHarqId       :4;
    VOS_UINT32                  bitCellIndex    :4;
    VOS_UINT32                  bitUlGrantType  :4;
    VOS_UINT32                  bitTbSize       :16;

    VOS_UINT8                   aucMacPdu[TL_OM_LTE_MAC_UL_PDU_DATA_LEN];
} TL_OM_LMAC_UL_PDU_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_LMAC_UL_PDU_INFO_ARRAY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LMAC UL PDU上报结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulRptNum;
    TL_OM_LMAC_UL_PDU_INFO_STRU     astLMacUlPduInfo[TL_OM_LTE_UL_PDU_RPT_MAX_NUM];
} TL_OM_LMAC_UL_PDU_INFO_ARRAY_STRU;

/*****************************************************************************
 结构名    : TL_OM_LMAC_DL_PDU_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 保存LMAC DL PDU关键信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  bitProcFrame    :10;  /*处理时刻*/
    VOS_UINT32                  bitProcSubFrame :4;
    VOS_UINT32                  bitAirFrame     :10;  /*空口时刻*/
    VOS_UINT32                  bitAirSubFrame  :4;
    VOS_UINT32                  bitFrameType    :4;

    VOS_UINT32                  ulStampL32Bit;        /*处理完PDU子帧对应的时间戳*/
    VOS_UINT16                  usStampH16Bit;
    VOS_UINT16                  bitRntiType     :4;
    VOS_UINT16                  bitHarqId       :4;
    VOS_UINT16                  bitCellIndex    :4;
    VOS_UINT16                  bitErrIndFlg    :2;
    VOS_UINT16                  bitCrcFlg       :2;

    VOS_UINT32                  bitAreaId       :8;
    VOS_UINT32                  bitPmchIndex    :6;
    VOS_UINT32                  bitTbSize       :18;

    VOS_UINT8                   aucMacPdu[TL_OM_LTE_MAC_DL_PDU_DATA_LEN];
} TL_OM_LMAC_DL_PDU_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_LMAC_DL_PDU_INFO_ARRAY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LMAC DL PDU上报结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulRptNum;
    TL_OM_LMAC_DL_PDU_INFO_STRU     astLMacDlPduInfo[TL_OM_LTE_DL_PDU_RPT_MAX_NUM];
} TL_OM_LMAC_DL_PDU_INFO_ARRAY_STRU;

/*****************************************************************************
 结构名    : TL_OM_LTE_UP_LATENCY_RPT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE用户面时延上报
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulLatencyType;      /*上报时延类型*/
    VOS_UINT32                  ulResult;           /*当前操作处理结果*/
    VOS_UINT32                  ulLatencyTime;      /*时延长度*/
    VOS_UINT32                  ulStartTime;        /*起始时间*/
    VOS_UINT32                  ulEndTime;          /*结束时间*/
} TL_OM_LTE_UP_LATENCY_RPT_STRU;

/*****************************************************************************
 结构名    : TL_OM_LMAC_REG_BSR_SR_INFO_RPT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE MAC 规则BSR和SR情况上报
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  usCurSysFrame;
    VOS_UINT16                  usCurSubFrame;
    VOS_UINT8                   ucSrState;              /*SR状态*/
    VOS_UINT8                   ucSpsGrantValid;        /*SPS授权有效标志*/
    VOS_UINT8                   ucSrMaskLchTrigFlg;     /*srMask逻辑信道触发规则BSR*/
    VOS_UINT8                   ucHigherLchTrigFlg;     /*高优先级逻辑信道触发规则BSR*/

    VOS_UINT8                   ucNewLcgTrigFlg;        /*新逻辑信道组触发规则BSR*/
    VOS_UINT8                   ucSrProhibitTmrFlg;     /*SR禁止定时器状态*/
    VOS_UINT8                   ucLchMaxPri;            /*有数据要发的逻辑信道的最高优先级*/
    VOS_UINT8                   ucMaxPriLcgId;          /*具有最高优先级的逻辑信道组ID*/
} TL_OM_LMAC_REG_BSR_SR_INFO_RPT_STRU;

/*****************************************************************************
 结构名    : TL_OM_LMAC_SR_TX_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE MAC SR发送信息上报
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  usCurSysFrame;
    VOS_UINT8                   ucCurSubFrame;
    VOS_UINT8                   ucSrTxResult;           /*SR发送结果,0-发送，1-取消*/

    VOS_UINT16                  usSrReqFrame;           /*SR请求帧号*/
    VOS_UINT16                  usSrReqSubFrame;
    VOS_UINT16                  usSrReqCount;           /*SR请求计数*/
    VOS_UINT16                  usSrReqNotCnfCnt;       /*SR请求没有收到CNF计数*/

    VOS_UINT8                   ucPhyCancelSrFlg;       /*SR发送结果为取消时有效，PS_TRUE为LPHY取消，PS_FALSE为LMAC取消*/
    VOS_UINT8                   ucSrTxSubFrame;         /*SR发送子帧号*/
    VOS_UINT16                  usSrTxFrame;

    VOS_UINT8                   ucSrPeriod;
    VOS_UINT8                   ucSrOffset;
    VOS_UINT16                  usSrMaxTxNum;

} TL_OM_LMAC_SR_TX_INFO_STRU;

/*****************************************************************************
 枚举名    : TL_OM_LMAC_PHY_TRIG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LTE MAC PHR触发类型
*****************************************************************************/
enum TL_OM_LMAC_PHR_TRIG_ENUM
{
    TL_OM_LMAC_PHR_TRIG_PATHLOSS        = 0x00,
    TL_OM_LMAC_PHR_TRIG_PERIODIC        = 0x01,
    TL_OM_LMAC_PHR_TRIG_CFG             = 0x02,
    TL_OM_LMAC_PHR_TRIG_ULSCELL_ACT     = 0x03,
    TL_OM_LMAC_PHR_TRIG_PWR_BACKOFF     = 0x04,
    TL_OM_LMAC_PHR_TRIG_BUTT
} ;

typedef VOS_UINT32  TL_OM_LMAC_PHR_TRIG_ENUM_UINT32;

/*****************************************************************************
 结构名    : TL_OM_LMAC_PHR_TRIGGER_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE MAC PHR触发条件信息
*****************************************************************************/
typedef struct
{
    TL_OM_LMAC_PHR_TRIG_ENUM_UINT32     enTrigType;

    VOS_UINT16                          usTrigSysFrame;
    VOS_UINT8                           ucTrigSubFrame;
    VOS_UINT8                           ucDlPathLossChange;

    VOS_UINT8                           ucSimulPUCCH_PUSCH;
    VOS_UINT8                           ucExtPhrEnable;
    VOS_UINT8                           ucPeriPhrFlag;
    VOS_UINT8                           ucProhibitPhrFlag;

    VOS_UINT16                          usCurPCellPathLoss;
    VOS_UINT16                          usLastPCellPathLoss;
    VOS_UINT16                          usCurSCellPathLoss;
    VOS_UINT16                          usLastSCellPathLoss;
    VOS_UINT16                          usCurPCellPwrBackOff;
    VOS_UINT16                          usLastPCellPwrBackOff;
    VOS_UINT16                          usCurSCellPwrBackOff;
    VOS_UINT16                          usLastSCellPwrBackOff;
} TL_OM_LMAC_PHR_TRIGGER_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_LMAC_UL_GRANT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE MAC 上行授权信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  usCurSysFrame   : 10;
    VOS_UINT16                  usCurSubFrame   : 6;
    VOS_UINT16                  usStampH16Bit;
    VOS_UINT32                  ulStampL32Bit;

    VOS_UINT16                  usTxSysFrame    :10;
    VOS_UINT16                  usTxSubFrame    :6;
    VOS_UINT8                   bitSchedMode    :4;
    VOS_UINT8                   bitHarqId       :4;
    VOS_UINT8                   bitCellIndex    :4;
    VOS_UINT8                   bitTbIndex      :4;

    VOS_UINT8                   bitUlGrantInd   :4;
    VOS_UINT8                   bitHarqFeedInd  :4;
    VOS_UINT8                   bitNewDataInd   :4;
    VOS_UINT8                   bitGapInd       :4;
    VOS_UINT16                  usRnti;

    VOS_UINT32                  ulTbSize;
} TL_OM_LMAC_UL_GRANT_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_LMAC_UL_GRANT_INFO_ARRAY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE MAC 上行授权上报结构信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulRptNum;
    TL_OM_LMAC_UL_GRANT_INFO_STRU   astUlGrant[TL_OM_LTE_MAX_RPT_NUM];
} TL_OM_LMAC_UL_GRANT_INFO_ARRAY_STRU;

/*****************************************************************************
 结构名    : TL_OM_LMAC_DL_ASSIGNMENT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE MAC下行指派信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  usCurFrame          :10;
    VOS_UINT16                  usCurSubFrame       :6;
    VOS_UINT16                  usTimeStampH16Bit;
    VOS_UINT32                  ulTimeStampL32Bit;

    VOS_UINT16                  usRxFrame           :10;
    VOS_UINT16                  usRxSubFrame        :6;
    VOS_UINT8                   ucCellIndex;
    VOS_UINT8                   ucTb0Valid          :1;
    VOS_UINT8                   ucTb0NewDataInd     :1;
    VOS_UINT8                   ucTb1Valid          :1;
    VOS_UINT8                   ucTb1NewDataInd     :1;
    VOS_UINT8                   ucRsv               :4;

} TL_OM_LMAC_DL_ASSIGNMENT_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_LMAC_DL_ASSIGNMENT_INFO_ARRAY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE MAC 下行指派上报结构信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRptNum;
    TL_OM_LMAC_DL_ASSIGNMENT_INFO_STRU  astDlAssign[TL_OM_LTE_MAX_RPT_NUM];
} TL_OM_LMAC_DL_ASSIGNMENT_INFO_ARRAY_STRU;

/*****************************************************************************
 结构名    : TL_OM_LMAC_ONE_LCH_BUFFER_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE MAC逻辑信道缓存情况
*****************************************************************************/
typedef struct
{
    VOS_UINT8                   ucLchId;
    VOS_UINT8                   ucLcgId;
    VOS_UINT8                   ucRbId;
    VOS_UINT8                   ucLchPrio;

    VOS_UINT32                  ulSduLen;
    VOS_UINT32                  ulRetxPduLen;
    VOS_UINT32                  ulCtrlPduLen;
    VOS_UINT32                  ulPdcpBuf;

} TL_OM_LMAC_LCH_BUFF_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_LMAC_BUFFER_STATUS_INFO_RPT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE MAC 缓存情况上报
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usFrame;
    VOS_UINT8                               ucSubFrame;
    VOS_UINT8                               ucLchNum;   /*激活逻辑信道个数*/
    TL_OM_LMAC_LCH_BUFF_INFO_STRU           astLchBuff[TL_OM_LTE_MAC_MAX_LCH_NUM];
} TL_OM_LMAC_BUFFER_STATUS_INFO_STRU;

/*****************************************************************************
 结构名    : TL_OM_LMAC_BUFFER_STATUS_INFO_RPT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE MAC 缓存情况上报
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulRptNum;
    TL_OM_LMAC_BUFFER_STATUS_INFO_STRU      astLMacBuff[TL_OM_LTE_MAC_BUF_STATUS_RPT_NUM];
} TL_OM_LMAC_BUFFER_STATUS_RPT_STRU;

/*****************************************************************************
 结构名    : TL_OM_LTE_L2_OVERVIEW_STAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE MAC逻辑信道缓存情况
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulAppUlRate;
    VOS_UINT32                          ulAppDlRate;
    VOS_UINT32                          ulPdcpUlRate;
    VOS_UINT32                          ulPdcpDlRate;
    VOS_UINT32                          ulRlcUlRate;
    VOS_UINT32                          ulRlcDlRate;
    VOS_UINT32                          ulMacUlRate;
    VOS_UINT32                          ulMacDlRate;

    VOS_UINT32                          ulCpuProfile;
    VOS_UINT32                          ulDdrProfile;

} TL_OM_LTE_L2_THROUGHPUT_STAT_STRU;


/*****************************************************************************
 结构名    : TL_OM_LTE_USER_PLANE_OVERVIEW_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE 用户面整体数传情况
*****************************************************************************/
typedef struct
{
    /*速率统计*/
    VOS_UINT32                          ulAppUlRate;
    VOS_UINT32                          ulAppDlRate;
    VOS_UINT32                          ulLPdcpUlRate;
    VOS_UINT32                          ulLPdcpDlRate;
    VOS_UINT32                          ulLRlcUlRate;
    VOS_UINT32                          ulLRlcDlRate;
    VOS_UINT32                          ulLMacUlRate;
    VOS_UINT32                          ulLMacDlRate;

    /*DFS*/
    //VOS_UINT32                          ulCpuProfile;
    //VOS_UINT32                          ulDdrProfile;
    VOS_UINT32                          ulDfsProfile;
    /*内存统计*/
    VOS_UINT32                          ulTtfUlIpMemFree;           /*下行TTF 上行*/
    VOS_UINT32                          ulTtfDlIpMemFree;           /*下行TTF DL PDU池空闲块数*/
    VOS_UINT32                          ulDlTbFreeNum;              /*下行TB内存空闲块数*/

    /*队列缓存情况*/
    VOS_UINT32                          ulUlAppQueCnt;              /*上行APP队列缓存IP包个数*/
    VOS_UINT32                          ulUlLPdcpBuffHighSdu;       /*上行PDCP缓存SDU个数*/
    VOS_UINT32                          ulUlLPdcpBuffLowSdu;       /*上行PDCP缓存SDU个数*/
    VOS_UINT32                          ulDlLMacTbQueCnt;           /*下行缓存TB个数*/
    VOS_UINT32                          ulDlNonThrSduQueCnt;        /*下行非直通通道缓存SDU个数*/
    VOS_UINT32                          ulDlThrSduQueCnt;           /*下行直通通道缓存SDU个数*/
    VOS_UINT32                          ulDlCdsSduQueCnt;           /*CDS缓存SDU个数*/

    /*上行统计量*/
    VOS_UINT32                          ulUlCdsRxRd;
    VOS_UINT32                          ulUlFcDiscardPkt;
    VOS_UINT32                          ulUlCdsTxtoLte;
    VOS_UINT32                          ulUlLPdcpRxSdu;
    VOS_UINT32                          ulUlLPdcpTxPdu;
    VOS_UINT32                          ulUlLRlcRxSdu;
    VOS_UINT32                          ulUlLRlcDropSdu;
    VOS_UINT32                          ulUlLRlcTxSduSucc;
    VOS_UINT32                          ulUlLRlcTxSduFail;
    VOS_UINT32                          ulUlLRlcRxCtrlPdu;
    VOS_UINT32                          ulUlLRlcTxPdu;
    VOS_UINT32                          ulUlLMacUlGrant;
    VOS_UINT32                          ulUlLMacSchedRlcPdu;
    VOS_UINT32                          ulUlLMacTxPdu;

    /*下行统计量*/
    VOS_UINT32                          ulDlLMacAllocTbMem;
    VOS_UINT32                          ulDlLMacGetTbMem;
    VOS_UINT32                          ulDlLRlcRxPdu;
    VOS_UINT32                          ulDlLRlcDropPdu;
    VOS_UINT32                          ulDlLRlcTxSduSucc;
    VOS_UINT32                          ulDlLRlcTxSduFail;
    VOS_UINT32                          ulDlLPdcpRxPdu;
    VOS_UINT32                          ulDlLPdcpTxSdu;
    VOS_UINT32                          ulDlCdsRxLteSdu;
    VOS_UINT32                          ulDlFcDiscardPkt;
    VOS_UINT32                          ulDlCdsTxImsNic;
    VOS_UINT32                          ulDlCdsCfgBd;

} TL_OM_LTE_USER_PLANE_OVERVIEW_INFO_STRU;



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
extern VOS_VOID LPS_OM_LOG( const VOS_CHAR  *pcFileName,  VOS_UINT32  ulLineNum,
                                  VOS_UINT32      ulModuleId,   VOS_UINT32 ulLevel,
                                  const VOS_CHAR  *pcString );
extern VOS_VOID LPS_OM_LOG1( const VOS_CHAR   *pcFileName, VOS_UINT32  ulLineNum,
                                   VOS_UINT32  ulModuleId,       VOS_UINT32 ulLevel,
                                   const VOS_CHAR    *pcString,  VOS_INT32  lPara1);
extern VOS_VOID LPS_OM_LOG2( const VOS_CHAR   *pcFileName, VOS_UINT32  ulLineNum,
                                   VOS_UINT32 ulModuleId,        VOS_UINT32 ulLevel,
                                   const VOS_CHAR   *pcString,   VOS_INT32  lPara1,
                                   VOS_INT32  lPara2);
extern VOS_VOID LPS_OM_LOG3( const VOS_CHAR  *pcFileName,  VOS_UINT32  ulLineNum,
                                   VOS_UINT32 ulModuleId,        VOS_UINT32 ulLevel,
                                   const VOS_CHAR   *pcString,   VOS_INT32  lPara1,
                                   VOS_INT32  lPara2,            VOS_INT32  lPara3);
extern VOS_VOID LPS_OM_LOG4( const VOS_CHAR   *pcFileName, VOS_UINT32  ulLineNum,
                                   VOS_UINT32 ulModuleId,        VOS_UINT32 ulLevel,
                                   const VOS_CHAR   *pcString,   VOS_INT32  lPara1,
                                   VOS_INT32  lPara2,            VOS_INT32  lPara3,
                                   VOS_INT32  lPara4);
extern VOS_UINT32  OM_GetTimeStamp(void);/*获取精度为0.1毫秒的时间戳*/

/*z00282933，多模OM融合添加 - BEGIN*/
extern VOS_VOID TL_OM_ReportSingleUpEvent(
                                                TL_UP_EVENT_ENUM_UINT16 usEvent,
                                                VOS_UINT16 usPid,
                                                VOS_UINT16 usRbId,
                                                VOS_UINT16 usFrameNum,
                                                VOS_UINT16 usSubFrameNum,
                                                VOS_UINT32 ulModeType);

extern VOS_VOID TL_OM_ReportAllUpEvent(VOS_UINT32 ulModeType);
/*z00282933, 多模OM融合添加 - END*/

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

#endif /* end of OmCommon.h */
