/*******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : hids_elf_taf.c
  版 本 号   : 初稿
  作    者   : l00301449
  生成日期   : 2015年11月11日
  功能描述   : TAF的elf文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年11月06日
    作    者   : l00301449
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "Hids_elf_taf.h"

#include "UsimPsInterface.h"

#include "NasStkInterface.h"

#include "NasComm.h"

#include "TafNvInterface.h"

#include "MmaMsccInterface.h"
#include "MmaXsmsInterface.h"
#include "TafMmaTimerMgmt.h"

#include "xcc_aps_pif.h"
#include "xcc_xcall_pif.h"

#include "TafAppMma.h"
#include "TafMmaInterface.h"
#include "TafMmaMntn.h"
#include "TafMmaSndInternalMsg.h"
#include "TafMmaFsmMainTbl.h"
#include "TafMmaFsmPhoneModeTbl.h"
#include "TafMmaFsmSysCfgTbl.h"
#include "TafMmaFsmImsSwitchTbl.h"

#include "Taf_ApsForSndcp.h"
#include "RabmTafInterface.h"
#include "RabmInterface.h"

#include "TafAppXsmsInterface.h"
#include "NasOmInterface.h"
#include "NasOmTrans.h"
#include "NasMsccPifInterface.h"
#include "NasUsimmApiMntn.h"
#include "TafXCallMntn.h"
#include "taf_xcall_xsms_pif.h"
#include "taf_aps_dhcp_pif.h"
#include "taf_aps_ppp_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
 结构名    : TAF_MMA_ELF_TIMER_INFO_STRU
 结构说明  : log出MMA定时器运行情况
 1.日    期   : 2015年11月12日
   作    者   : L00301449
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_TIMER_ID_ENUM_UINT32        enTimerId;
    TAF_MMA_TIMER_STATUS_ENUM_UINT8     enTimerStatus;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulLen;              /* 定时器时长 */
}TAF_MMA_ELF_TIMER_INFO_STRU;

typedef struct
{
    TAF_MMA_MAIN_STA_ENUM_UINT32        enL1Sta;
}TAF_MMA_ELF_LOG_FSM_L1_STATE_STRU;

typedef struct
{
    TAF_MMA_PHONE_MODE_STA_ENUM_UINT32  enPhoneModeSta;
}TAF_MMA_ELF_LOG_FSM_PHONEMODE_STATE_STRU;

typedef struct
{
    TAF_MMA_SYS_CFG_STA_ENUM_UINT32     enSysCfgSta;
}TAF_MMA_ELF_LOG_FSM_SYSCFG_STATE_STRU;

#if (FEATURE_IMS == FEATURE_ON)
typedef struct
{
    TAF_MMA_IMS_SWITCH_STA_ENUM_UINT32  enImsSwitchSta;
}TAF_MMA_ELF_LOG_FSM_IMSSWITCH_STATE_STRU;
#endif

typedef struct
{
    VOS_UINT32                          ulNullSta;
}TAF_MMA_ELF_LOG_FSM_NULL_STATE_STRU;


/*****************************************************************************
 结构名    : TAF_MMA_ELF_LOG_FSM_INFO_STRU
 结构说明  : TAF_MMA_LOG_FSM_INFO_IND的消息结构
 1.日    期   : 2015年11月13日
   作    者   : l00301449
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MNTN_MSG_ID_ENUM_UINT32                         enMsgId;
    TAF_MMA_FSM_ID_ENUM_UINT32                              enUnionStructSelChoice;
    union
    {
        TAF_MMA_ELF_LOG_FSM_L1_STATE_STRU                   stL1State;
        TAF_MMA_ELF_LOG_FSM_PHONEMODE_STATE_STRU            stPhoneModeState;
#if (FEATURE_IMS == FEATURE_ON)
        TAF_MMA_ELF_LOG_FSM_IMSSWITCH_STATE_STRU            stImsSwitchState;
#else
        TAF_MMA_ELF_LOG_FSM_NULL_STATE_STRU                 stNullState;
#endif
        TAF_MMA_ELF_LOG_FSM_SYSCFG_STATE_STRU               stSysCfgState;
    }uCurFsmState;
}TAF_MMA_ELF_LOG_FSM_INFO_STRU;
/*****************************************************************************
 函 数 名  : ELF_TAF_ENUM_COMMON
 功能描述  : 公共的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_ENUM_COMMON(void)
{
    enum MTC_PS_TRANSFER_ENUM                               enMTC_PS_TRANSFER_ENUM;

}

/*****************************************************************************
 函 数 名  : ELF_TAF_ENUM_NAS_COMMON
 功能描述  : NAS公共的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_ENUM_NAS_COMMON(void)
{
    enum NAS_TIMER_OPERATION_TYPE_ENUM                      enNAS_TIMER_OPERATION_TYPE_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_TAF_ENUM_USIM
 功能描述  : USIM的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : w00351686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_ENUM_USIM(void)
{
    enum USIMM_CARD_TYPE_ENUM                               enUSIMM_CARD_TYPE_ENUM;
    enum USIMM_CARD_SERVIC_ENUM                             enUSIMM_CARD_SERVIC_ENUM;
    enum USIMM_PHYCARD_TYPE_ENUM                            enUSIMM_PHYCARD_TYPE_ENUM;
    enum NAS_USIMM_API_TYPE_ENUM                            enNAS_USIMM_API_TYPE_ENUM;
    enum MNPH_USIM_STATUS_ENUM                              enMNPH_USIM_STATUS_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_TAF_ENUM_NAS_SKT
 功能描述  : NAS和STK之间的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_ENUM_NAS_SKT(void)
{
    enum TAF_CS_SERVICE_ENUM                                 enTAF_CS_SERVICE_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_TAF_ENUM_TAF_SDC
 功能描述  : TAF SDC的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_ENUM_TAF_SDC(void)
{
    enum TAF_SDC_SYS_MODE_ENUM                              enTAF_SDC_SYS_MODE_ENUM;
    enum TAF_SDC_SYS_SUBMODE_ENUM                           enTAF_SDC_SYS_SUBMODE_ENUM;
    enum TAF_SDC_OPER_NAME_TYPE_ENUM                        enTAF_SDC_OPER_NAME_TYPE_ENUM;
    enum TAF_SDC_COPS_FORMAT_TYPE_ENUM                      enTAF_SDC_COPS_FORMAT_TYPE_ENUM;
    enum TAF_SDC_SERVICE_STATUS_ENUM                        enTAF_SDC_SERVICE_STATUS_ENUM;
    enum TAF_SDC_REG_STATUS_ENUM                            enTAF_SDC_REG_STATUS_ENUM;
    enum TAF_SDC_CELL_RESTRICTION_TYPE_ENUM                 enTAF_SDC_CELL_RESTRICTION_TYPE_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_TAF_ENUM_APP_MMA
 功能描述  : TafAppMma.h的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_ENUM_APP_MMA(void)
{
    enum TAF_MMA_MSG_TYPE_ENUM                              enTAF_MMA_MSG_TYPE_ENUM;
    enum TAF_MMA_APP_OPER_RESULT_ENUM                       enTAF_MMA_APP_OPER_RESULT_ENUM;
    enum TAF_MMA_PLMN_PRIORITY_CLASS_ENUM                   enTAF_MMA_PLMN_PRIORITY_CLASS_ENUM;
    enum TAF_MMA_CL_REG_STATUS_ENUM                         enTAF_MMA_CL_REG_STATUS_ENUM;
    enum TAF_MMA_CARD_STATUS_ENUM                           enTAF_MMA_CARD_STATUS_ENUM;
    enum TAF_MMA_USIMM_CARD_TYPE_ENUM                       enTAF_MMA_USIMM_CARD_TYPE_ENUM;
    enum TAF_MMA_SRV_TYPE_ENUM                              enTAF_MMA_SRV_TYPE_ENUM;
    enum TAF_MMA_SRV_ACQ_RESULT_ENUM                        enTAF_MMA_SRV_ACQ_RESULT_ENUM;
    enum TAF_MMA_CDMA_CALL_TYPE_ENUM                        enTAF_MMA_CDMA_CALL_TYPE_ENUM;
    enum TAF_MMA_CDMA_CSQ_MODE_ENUM                         enTAF_MMA_CDMA_CSQ_MODE_ENUM;
    enum TAF_MMA_APP_CFPLMN_OPER_RESULT_ENUM                enTAF_MMA_APP_CFPLMN_OPER_RESULT_ENUM;
    enum TAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM             enTAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM;
    enum TAF_MMA_RAT_TYPE_ENUM                              enTAF_MMA_RAT_TYPE_ENUM;
    enum TAF_MMA_NET_SCAN_RESULT_ENUM                       enTAF_MMA_NET_SCAN_RESULT_ENUM;
    enum TAF_MMA_NET_SCAN_CAUSE_ENUM                        enTAF_MMA_NET_SCAN_CAUSE_ENUM;
    enum TAF_MMA_QRY_REG_STATUS_TYPE_ENUM                   enTAF_MMA_QRY_REG_STATUS_TYPE_ENUM;
    enum TAF_MMA_IMS_SWITCH_SET_ENUM                        enTAF_MMA_IMS_SWITCH_SET_ENUM;
    enum TAF_MMA_VOICE_DOMAIN_ENUM                          enTAF_MMA_VOICE_DOMAIN_ENUM;
    enum TAF_MMA_ATTACH_TYPE_ENUM                           enTAF_MMA_ATTACH_TYPE_ENUM;
    enum TAF_MMA_PS_RAT_TYPE_ENUM                           enTAF_MMA_PS_RAT_TYPE_ENUM;
    enum TAF_MMA_CELL_RESTRICTION_TYPE_ENUM                 enTAF_MMA_CELL_RESTRICTION_TYPE_ENUM;
    enum TAF_MMA_SERVICE_DOMAIN_ENUM                        enTAF_MMA_SERVICE_DOMAIN_ENUM;
    enum TAF_MMA_ROAM_MODE_ENUM                             enTAF_MMA_ROAM_MODE_ENUM;
    enum TAF_MMA_USER_SET_PRIO_RAT_ENUM                     enTAF_MMA_USER_SET_PRIO_RAT_ENUM;
    enum TAF_MMA_ACQ_REASON_ENUM                            enTAF_MMA_ACQ_REASON_ENUM;
    enum TAF_MMA_EPS_ATTACH_REASON_ENUM                     enTAF_MMA_EPS_ATTACH_REASON_ENUM;
    enum TAF_MMA_DETACH_CAUSE_ENUM                          enTAF_MMA_DETACH_CAUSE_ENUM;
    enum TAF_MMA_SRV_ACQ_RAT_TYPE_ENUM                      enTAF_MMA_SRV_ACQ_RAT_TYPE_ENUM;
    enum TAF_MMA_HDR_CSQ_MODE_ENUM                          enTAF_MMA_HDR_CSQ_MODE_ENUM;

    enum MN_PH_PREF_PLMN_TYPE_ENUM                          enMN_PH_PREF_PLMN_TYPE_ENUM;
    enum MN_PH_CSQLVLEXT_RSSILV_VALUE_ENUM                  enMN_PH_CSQLVLEXT_RSSILV_VALUE_ENUM;
    enum MN_PH_CSQLVLEXT_BER_VALUE_ENUM                     enMN_PH_CSQLVLEXT_BER_VALUE_ENUM;
    enum MN_MMA_CPAM_RAT_TYPE_ENUM                          enMN_MMA_CPAM_RAT_TYPE_ENUM;

    enum TAF_PH_ACCESS_TECH_ENUM                            enTAF_PH_ACCESS_TECH_ENUM;
    enum TAF_PH_PLMN_SELECTION_RESULT_ENUM                  enTAF_PH_PLMN_SELECTION_RESULT_ENUM;
    enum TAF_PH_PLMN_SELECTION_START_END_FLAG_ENUM          enTAF_PH_PLMN_SELECTION_START_END_FLAG_ENUM;

    enum TAF_SIM_INSERT_STATE_ENUM                          enTAF_SIM_INSERT_STATE_ENUM;

}

/*****************************************************************************
 函 数 名  : ELF_TAF_ENUM_MMA_MSCC
 功能描述  : MMA和MSCC之间的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : w00351686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_ENUM_MMA_MSCC(void)
{

}


/*****************************************************************************
 函 数 名  : ELF_TAF_ENUM_MSCC_PIF
 功能描述  : MSCC对外接口的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_ENUM_MSCC_PIF(void)
{
    enum NAS_MSCC_PIF_CARD_STATUS_ENUM                      enNAS_MSCC_PIF_CARD_STATUS_ENUM;
    enum NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM               enNAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM;
    enum NAS_MSCC_PIF_REG_CONTROL_ENUM                      enNAS_MSCC_PIF_REG_CONTROL_ENUM;
    enum NAS_MSCC_PIF_CALL_MODE_ENUM                        enNAS_MSCC_PIF_CALL_MODE_ENUM;
    enum NAS_MSCC_PIF_NET_RAT_TYPE_ENUM                     enNAS_MSCC_PIF_NET_RAT_TYPE_ENUM;
    enum NAS_MSCC_PIF_MS_MODE_ENUM                          enNAS_MSCC_PIF_MS_MODE_ENUM;
    enum NAS_MSCC_PIF_ATTACH_TYPE_ENUM                      enNAS_MSCC_PIF_ATTACH_TYPE_ENUM;
    enum NAS_MSCC_PIF_EPS_ATTACH_REASON_ENUM                enNAS_MSCC_PIF_EPS_ATTACH_REASON_ENUM;
    enum NAS_MSCC_PIF_DETACH_TYPE_ENUM                      enNAS_MSCC_PIF_DETACH_TYPE_ENUM;
    enum NAS_MSCC_PIF_DETACH_REASON_ENUM                    enNAS_MSCC_PIF_DETACH_REASON_ENUM;
    enum NAS_MSCC_PIF_PLMN_SEL_MODE_ENUM                    enNAS_MSCC_PIF_PLMN_SEL_MODE_ENUM;
    enum NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM                  enNAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM;
    enum NAS_MSCC_PIF_ROAM_CAPABILITY_ENUM                  enNAS_MSCC_PIF_ROAM_CAPABILITY_ENUM;
    enum NAS_MSCC_PIF_ACQ_REASON_ENUM                       enNAS_MSCC_PIF_ACQ_REASON_ENUM;
    enum NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM              enNAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM;
    enum NAS_MSCC_PIF_SRV_TYPE_ENUM                         enNAS_MSCC_PIF_SRV_TYPE_ENUM;
    enum NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_ENUM                 enNAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_ENUM;
    enum NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM                   enNAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM;
    enum NAS_MSCC_PIF_CDMA_CALL_CAUSE_ENUM                  enNAS_MSCC_PIF_CDMA_CALL_CAUSE_ENUM;
    enum NAS_MSCC_PIF_CFREQ_LOCK_SET_MODE_ENUM              enNAS_MSCC_PIF_CFREQ_LOCK_SET_MODE_ENUM;
    enum NAS_MSCC_PIF_CFPLMN_OPERATE_TYPE_ENUM              enNAS_MSCC_PIF_CFPLMN_OPERATE_TYPE_ENUM;
    enum NAS_MSCC_PIF_PREF_PLMN_TYPE_ENUM                   enNAS_MSCC_PIF_PREF_PLMN_TYPE_ENUM;
    enum NAS_MSCC_PIF_PREFPLMN_OPERATE_TYPE_ENUM            enNAS_MSCC_PIF_PREFPLMN_OPERATE_TYPE_ENUM;
    enum NAS_MSCC_PIF_PARA_TYPE_ENUM                        enNAS_MSCC_PIF_PARA_TYPE_ENUM;
    enum NAS_MSCC_PIF_PREF_PLMN_CMD_TYPE_ENUM               enNAS_MSCC_PIF_PREF_PLMN_CMD_TYPE_ENUM;
    enum NAS_MSCC_PIF_VOICE_DOMAIN_ENUM                     enNAS_MSCC_PIF_VOICE_DOMAIN_ENUM;
    enum MMA_MSCC_HANDSET_INFO_TYPE_ENUM                    enMMA_MSCC_HANDSET_INFO_TYPE_ENUM;
    enum NAS_MSCC_PIF_PS_RAT_TYPE_ENUM                      enNAS_MSCC_PIF_PS_RAT_TYPE_ENUM;

}

/*****************************************************************************
 函 数 名  : ELF_TAF_ENUM_XCC_TAF
 功能描述  : TAF和XCC之间的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : w00351686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_ENUM_XCC_TAF(void)
{
    enum XCC_APS_PIF_MSG_TYPE_ENUM                          enXCC_APS_PIF_MSG_TYPE_ENUM;
    enum TAF_XCC_END_REASON_ENUM                            enTAF_XCC_END_REASON_ENUM;
    enum XCC_APS_RESULT_ENUM                                enXCC_APS_RESULT_ENUM;
    enum XCC_XCALL_PIF_MSG_TYPE_ENUM                        enXCC_XCALL_PIF_MSG_TYPE_ENUM;
    enum XCC_XCALL_DIGIT_MODE_ENUM                          enXCC_XCALL_DIGIT_MODE_ENUM;
    enum XCC_XCALL_RESULT_ENUM                              enXCC_XCALL_RESULT_ENUM;
    enum XCALL_XCC_CONT_DTMF_SWITCH_ENUM                    enXCALL_XCC_CONT_DTMF_SWITCH_ENUM;
    enum XCALL_XCC_PRIVACY_MODE_ENUM                        enXCALL_XCC_PRIVACY_MODE_ENUM;
    enum TAF_XCC_FAIL_LAYER_ENUM                            enTAF_XCC_FAIL_LAYER_ENUM;
    enum XCC_APS_DIGIT_MODE_ENUM                            enXCC_APS_DIGIT_MODE_ENUM;
    enum XCC_XCALL_NUMBER_TYPE_ENUM                         enXCC_XCALL_NUMBER_TYPE_ENUM;
    enum XCC_XCALL_NUMBER_PLAN_ENUM                         enXCC_XCALL_NUMBER_PLAN_ENUM;
    enum XCC_XCALL_SUB_ADDRESS_TYPE_ENUM                    enXCC_XCALL_SUB_ADDRESS_TYPE_ENUM;
    enum XCC_XCALL_SUB_ADDRESS_EO_ENUM                      enXCC_XCALL_SUB_ADDRESS_EO_ENUM;

}

/*****************************************************************************
 函 数 名  : ELF_TAF_ENUM_XSMS_TAF
 功能描述  : XSMS和TAF之间的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年01月25日
    作    者   : w00351686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_ENUM_XSMS_TAF(void)
{
    enum TAF_XCALL_XSMS_PIF_MSG_TYPE_ENUM                   enTAF_XCALL_XSMS_PIF_MSG_TYPE_ENUM;
    enum XSMS_XCALL_SEND_RESULT_ENUM                        enXSMS_XCALL_SEND_RESULT_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_TAF_ENUM_MN_CALL
 功能描述  : MnCall的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月04日
    作    者   : h00360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_ENUM_MN_CALL(void)
{
    enum MN_CALL_EX_STATE_ENUM                              enMN_CALL_EX_STATE_ENUM;
    enum MN_CALL_MPTY_STATE_ENUM                            enMN_CALL_MPTY_STATE_ENUM;
    enum MN_CALL_TYPE_ENUM                                  enMN_CALL_TYPE_ENUM;
    enum MN_CALL_MODE_ENUM                                  enMN_CALL_MODE_ENUM;
    enum MN_CALL_DIR_ENUM                                   enMN_CALL_DIR_ENUM;
    enum TAF_CALL_SUB_STATE_ENUM                            enTAF_CALL_SUB_STATE_ENUM;
    enum MN_CALL_CS_DATA_SPD_SIMPLE_ENUM                    enMN_CALL_CS_DATA_SPD_SIMPLE_ENUM;
    enum MN_CALL_CS_DATA_NAME_ENUM                          enMN_CALL_CS_DATA_NAME_ENUM;
    enum MN_CALL_CS_DATA_CE_ENUM                            enMN_CALL_CS_DATA_CE_ENUM;
    enum MN_CALL_NPI_ENUM                                   enMN_CALL_NPI_ENUM;
    enum MN_CALL_SUPS_CMD_ENUM                              enMN_CALL_SUPS_CMD_ENUM;
    enum MN_CALL_SS_RESULT_ENUM                             enMN_CALL_SS_RESULT_ENUM;
    enum MN_CALL_SS_ERR_CODE_ENUM                           enMN_CALL_SS_ERR_CODE_ENUM;
    enum MN_CALL_NO_CLI_CAUSE_ENUM                          enMN_CALL_NO_CLI_CAUSE_ENUM;
    enum MN_CALL_ALS_LINE_NO_ENUM                           enMN_CALL_ALS_LINE_NO_ENUM;
    enum TAF_CALL_VOICE_DOMAIN_ENUM                         enTAF_CALL_VOICE_DOMAIN_ENUM;
    enum MN_CALL_SS_NOTIFY_CODE_ENUM                        enMN_CALL_SS_NOTIFY_CODE_ENUM;
    enum MN_CALL_ECT_CALL_STATE_ENUM                        enMN_CALL_ECT_CALL_STATE_ENUM;
    enum MN_CALL_ECT_RDN_ENUM                               enMN_CALL_ECT_RDN_ENUM;
    enum TAF_CS_CAUSE_ENUM                                  enTAF_CS_CAUSE_ENUM;
    enum MN_CALL_UUS1_MSG_TYPE_ENUM                         enMN_CALL_UUS1_MSG_TYPE_ENUM;
    enum MN_CALL_EVENT_ENUM                                 enMN_CALL_EVENT_ENUM;
    enum MN_CALL_CODEC_TYPE_ENUM                            enMN_CALL_CODEC_TYPE_ENUM;
    enum TAF_CALL_DTMF_STATE_ENUM                           enTAF_CALL_DTMF_STATE_ENUM;
    enum MN_CALL_MODIFY_STATUS_ENUM                         enMN_CALL_MODIFY_STATUS_ENUM;
    enum TAF_CALL_NUMBER_TYPE_ENUM                          enTAF_CALL_NUMBER_TYPE_ENUM;
    enum TAF_CALL_NUMBER_PLAN_ENUM                          enTAF_CALL_NUMBER_PLAN_ENUM;
    enum TAF_CALL_ECONF_STATE_ENUM                          enTAF_CALL_ECONF_STATE_ENUM;
    enum TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM           enTAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM;
    enum TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM            enTAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM;
    enum TAF_CALL_CONT_DTMF_SWITCH_ENUM                     enTAF_CALL_CONT_DTMF_SWITCH_ENUM;
    enum MN_CALL_CLIR_CFG_ENUM                              enMN_CALL_CLIR_CFG_ENUM;
    enum MN_CALL_CS_DATA_SPEED_ENUM                         enMN_CALL_CS_DATA_SPEED_ENUM;
    enum MN_CALL_SET_UUS1_TYPE_ENUM                         enMN_CALL_SET_UUS1_TYPE_ENUM;
    enum MN_CALL_CUUS1_FLG_ENUM                             enMN_CALL_CUUS1_FLG_ENUM;
    enum TAF_CCA_MSG_TYPE_ENUM                              enTAF_CCA_MSG_TYPE_ENUM;
    enum TAF_CALL_PRIVACY_MODE_ENUM                         enTAF_CALL_PRIVACY_MODE_ENUM;
    enum TAF_CALL_APP_RESULT_TYPE_ENUM                      enTAF_CALL_APP_RESULT_TYPE_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_TAF_ENUM_MN_MSG
 功能描述  : MnMSG的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月04日
    作    者   : h00360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_ENUM_MN_MSG(void)
{
    enum MN_MSG_MO_DOMAIN_CUSTOMIZE_TYPE                    enMN_MSG_MO_DOMAIN_CUSTOMIZE_TYPE;
    enum MN_MSG_DATE_INVALID_TYPE_ENUM                      enMN_MSG_DATE_INVALID_TYPE_ENUM;
    enum MN_MSG_STUB_TYPE_ENUM                              enMN_MSG_STUB_TYPE_ENUM;
    enum MN_MSG_LINK_CTRL                                   enMN_MSG_LINK_CTRL;
    enum MN_MSG_TPDU_TYPE_ENUM                              enMN_MSG_TPDU_TYPE_ENUM;
    enum MN_MSG_RP_CAUSE_ENUM                               enMN_MSG_RP_CAUSE_ENUM;
    enum MN_MSG_TP_CAUSE_ENUM                               enMN_MSG_TP_CAUSE_ENUM;
    enum MN_MSG_IMS_CAUSE_ENUM                              enMN_MSG_IMS_CAUSE_ENUM;
    enum MN_MSG_IMSA_CAUSE_ENUM                             enMN_MSG_IMSA_CAUSE_ENUM;
    enum MN_MSG_TP_PID_TYPE_ENUM                            enMN_MSG_TP_PID_TYPE_ENUM;
    enum MN_MSG_MSG_CLASS_ENUM                              enMN_MSG_MSG_CLASS_ENUM;
    enum MN_MSG_MSG_CODING_ENUM                             enMN_MSG_MSG_CODING_ENUM;
    enum MN_MSG_MSG_WAITING_ENUM                            enMN_MSG_MSG_WAITING_ENUM;
    enum MN_MSG_MSG_WAITING_KIND_ENUM                       enMN_MSG_MSG_WAITING_KIND_ENUM;
    enum MN_MSG_VALIDITY_PERIOD_ENUM                        enMN_MSG_VALIDITY_PERIOD_ENUM;
    enum MN_MSG_TP_STATUS_ENUM                              enMN_MSG_TP_STATUS_ENUM;
    enum MN_MSG_COMMAND_ENUM                                enMN_MSG_COMMAND_ENUM;
    enum MN_MSG_STATUS_TYPE_ENUM                            enMN_MSG_STATUS_TYPE_ENUM;
    enum MN_MSG_MEM_STORE_ENUM                              enMN_MSG_MEM_STORE_ENUM;
    enum MN_MSG_WRITE_MODE_TYPE_ENUM                        enMN_MSG_WRITE_MODE_TYPE_ENUM;
    enum MN_MSG_DELETE_TYPE_ENUM                            enMN_MSG_DELETE_TYPE_ENUM;
    enum MN_MSG_TON_ENUM                                    enMN_MSG_TON_ENUM;
    enum MN_MSG_NPI_ENUM                                    enMN_MSG_NPI_ENUM;
    enum MN_MSG_CNMI_MT_TYPE_ENUM                           enMN_MSG_CNMI_MT_TYPE_ENUM;
    enum MN_MSG_RCVMSG_ACT_ENUM                             enMN_MSG_RCVMSG_ACT_ENUM;
    enum MN_MSG_SEND_DOMAIN_ENUM                            enMN_MSG_SEND_DOMAIN_ENUM;
    enum MN_MSG_RCV_DOMAIN_ENUM                             enMN_MSG_RCV_DOMAIN_ENUM;
    enum MN_MSG_MEM_FLAG_ENUM                               enMN_MSG_MEM_FLAG_ENUM;
    enum MN_MSG_RPT_STATUS_ENUM                             enMN_MSG_RPT_STATUS_ENUM;
    enum MN_MSG_EO_TYPE_ENUM                                enMN_MSG_EO_TYPE_ENUM;
    enum MN_MSG_COMPRESSION_ALGORITHM                       enMN_MSG_COMPRESSION_ALGORITHM;
    enum MN_MSG_CLASS0_TAILOR                               enMN_MSG_CLASS0_TAILOR;
    enum MN_MSG_ACTIVE_MESSAGE_STATUS_ENUM                  enMN_MSG_ACTIVE_MESSAGE_STATUS_ENUM;
    enum MN_MSG_CBLANG_ENUM                                 enMN_MSG_CBLANG_ENUM;
    enum MN_MSG_CBSSTATUS_ENUM                              enMN_MSG_CBSSTATUS_ENUM;
    enum MN_MSG_CBMODE_ENUM                                 enMN_MSG_CBMODE_ENUM;
    enum MN_MSG_CSMS_MSG_VERSION_ENUM                       enMN_MSG_CSMS_MSG_VERSION_ENUM;
    enum TAF_CBA_ETWS_PRIM_NTF_AUTH_RSLT_ENUM               enTAF_CBA_ETWS_PRIM_NTF_AUTH_RSLT_ENUM;
    enum TAF_CBA_CBMI_RANGE_RCV_MODE_ENMU                   enTAF_CBA_CBMI_RANGE_RCV_MODE_ENMU;
    enum TAF_MSG_SIGNALLING_TYPE_ENUM                       enTAF_MSG_SIGNALLING_TYPE_ENUM;
};

/*****************************************************************************
 函 数 名  : ELF_TAF_ENUM_PS
 功能描述  : PS域的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月07日
    作    者   : h00360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_ENUM_PS(void)
{
    enum TAF_PS_MSG_ID_ENUM                                 enTAF_PS_MSG_ID_ENUM;
    enum TAF_PS_EVT_ID_ENUM                                 enTAF_PS_EVT_ID_ENUM;
    enum TAF_PS_CAUSE_ENUM                                  enTAF_PS_CAUSE_ENUM;
    enum TAF_PDP_TYPE_ENUM                                  enTAF_PDP_TYPE_ENUM;
    enum TAF_PDP_AUTH_TYPE_ENUM                             enTAF_PDP_AUTH_TYPE_ENUM;
    enum TAF_AUTH_TYPE_ENUM                                 enTAF_AUTH_TYPE_ENUM;
    enum TAF_PDP_ACTIVE_STATUS_ENUM                         enTAF_PDP_ACTIVE_STATUS_ENUM;
    enum TAF_GPRS_ACTIVE_TYPE_ENUM                          enTAF_GPRS_ACTIVE_TYPE_ENUM;
    enum TAF_L2P_TYPE_ENUM                                  enTAF_L2P_TYPE_ENUM;
    enum TAF_PDP_H_COMP_ENUM                                enTAF_PDP_H_COMP_ENUM;
    enum TAF_PDP_D_COMP_ENUM                                enTAF_PDP_D_COMP_ENUM;
    enum TAF_UMTS_QOS_TRAFFIC_CLASS_ENUM                    enTAF_UMTS_QOS_TRAFFIC_CLASS_ENUM;
    enum TAF_PF_TRANS_DIRECTION_ENUM                        enTAF_PF_TRANS_DIRECTION_ENUM;
    enum TAF_DSFLOW_CLEAR_MODE_ENUM                         enTAF_DSFLOW_CLEAR_MODE_ENUM;
    enum TAF_PDP_EMC_IND_ENUM                               enTAF_PDP_EMC_IND_ENUM;
    enum TAF_PDP_IPV4_ADDR_ALLOC_TYPE_ENUM                  enTAF_PDP_IPV4_ADDR_ALLOC_TYPE_ENUM;
    enum TAF_PDP_PCSCF_DISCOVERY_ENUM                       enTAF_PDP_PCSCF_DISCOVERY_ENUM;
    enum TAF_PDP_IM_CN_SIG_FLAG_ENUM                        enTAF_PDP_IM_CN_SIG_FLAG_ENUM;
    enum TAF_PDP_ANSWER_TYPE_ENUM                           enTAF_PDP_ANSWER_TYPE_ENUM;
    enum TAF_PDP_ANSWER_MODE_ENUM                           enTAF_PDP_ANSWER_MODE_ENUM;
    enum TAF_PDP_REQUEST_TYPE_ENUM                          enTAF_PDP_REQUEST_TYPE_ENUM;
    enum TAF_PS_CDATA_1X_QOS_NON_ASSURED_PRI_ENUM           enTAF_PS_CDATA_1X_QOS_NON_ASSURED_PRI_ENUM;
    enum TAF_PS_CDATA_DIAL_MODE_ENUM                        enTAF_PS_CDATA_DIAL_MODE_ENUM;
}


/*****************************************************************************
 函 数 名  : ELF_TAF_ENUM_TAF_COMMON
 功能描述  : TAF公共的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : w00351686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_ENUM_TAF_COMMON(void)
{
    enum TAF_ERROR_CODE_ENUM                                enTAF_ERROR_CODE_ENUM;
    enum TAF_SYS_SUBMODE_ENUM                               enTAF_SYS_SUBMODE_ENUM;
    enum TAF_CDMA_SO_TYPE_ENUM                              enTAF_CDMA_SO_TYPE_ENUM;
    enum TAF_CS_CAUSE_ENUM                                  enTAF_CS_CAUSE_ENUM;
    enum TAF_CALL_PRIVACY_MODE_ENUM                         enTAF_CALL_PRIVACY_MODE_ENUM;

}

/*****************************************************************************
 函 数 名  : ELF_TAF_ENUM_TAF_XCALL
 功能描述  : TAF(XCALL)的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年01月26日
    作    者   : w00351686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_ENUM_TAF_XCALL(void)
{
    enum TAF_XCALL_MNTN_MSG_ID_ENUM                         enTAF_XCALL_MNTN_MSG_ID_ENUM;
    enum TAF_XCALL_SO_TYPE_ENUM                             enTAF_XCALL_SO_TYPE_ENUM;
    enum TAF_XCALL_WAIT_XCC_CNF_TYPE                        enTAF_XCALL_WAIT_XCC_CNF_TYPE;
    enum TAF_XCALL_SS_PROGRESS_EVT_ENUM                     enTAF_XCALL_SS_PROGRESS_EVT_ENUM;
    enum TAF_XCALL_SS_SUBSEQ_OP_ENUM                        enTAF_XCALL_SS_SUBSEQ_OP_ENUM;
    enum TAF_XCALL_KMC_MSG_TRIGGER_MODE_ENUM                enTAF_XCALL_KMC_MSG_TRIGGER_MODE_ENUM;
    enum TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM                enTAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM;
    enum TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_ENUM               enTAF_XCALL_KMC_MSG_ERR_IND_CAUSE_ENUM;
    enum TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_ENUM        enTAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_ENUM;
    enum TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_ENUM        enTAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_ENUM;
    enum TAF_XCALL_ECC_SRV_STATE_MACHINE_ID_ENUM            enTAF_XCALL_ECC_SRV_STATE_MACHINE_ID_ENUM;
    enum TAF_XCALL_REMOTE_CTRL_MSG_EVENT_TYPE_ENUM          enTAF_XCALL_REMOTE_CTRL_MSG_EVENT_TYPE_ENUM;

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    enum TAF_XCALL_REMOTE_CTRL_STA_ENUM                     enTAF_XCALL_REMOTE_CTRL_STA_ENUM;
    enum TAF_XCALL_K0_UPATE_STA_ENUM                        enTAF_XCALL_K0_UPATE_STA_ENUM;
    enum TAF_XCALL_VOICE_ENCRYPT_STA_ENUM                   enTAF_XCALL_VOICE_ENCRYPT_STA_ENUM;
#endif

    enum TAF_XCALL_PUB_KEY_UPDATE_MSG_EVENT_TYPE_ENUM       enTAF_XCALL_PUB_KEY_UPDATE_MSG_EVENT_TYPE_ENUM;
    enum TAF_XCALL_VOICE_ENC_MSG_EVENT_TYPE_ENUM            enTAF_XCALL_VOICE_ENC_MSG_EVENT_TYPE_ENUM;

    enum TAF_XCALL_TIMER_STATUS_ENUM                        enTAF_XCALL_TIMER_STATUS_ENUM;

}

/*****************************************************************************
 函 数 名  : ELF_TAF_ENUM_MMA
 功能描述  : MMA的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_ENUM_MMA(void)
{
    enum TAF_MMA_MNTN_MSG_ID_ENUM                           enTAF_MMA_MNTN_MSG_ID_ENUM;

    enum TAF_MMA_TIMER_ID_ENUM                              enTAF_MMA_TIMER_ID_ENUM;
    enum TAF_MMA_TIMER_STATUS_ENUM                          enTAF_MMA_TIMER_STATUS_ENUM;

    enum TAF_MMA_FSM_ID_ENUM                                enTAF_MMA_FSM_ID_ENUM;
    enum TAF_MMA_MAIN_STA_ENUM                              enTAF_MMA_MAIN_STA_ENUM;
    enum TAF_MMA_PHONE_MODE_STA_ENUM                        enTAF_MMA_PHONE_MODE_STA_ENUM;
    enum TAF_MMA_SYS_CFG_STA_ENUM                           enTAF_MMA_SYS_CFG_STA_ENUM;

   #if (FEATURE_IMS == FEATURE_ON)
    enum TAF_MMA_IMS_SWITCH_STA_ENUM                        enTAF_MMA_IMS_SWITCH_STA_ENUM;
   #endif

    enum TAF_MMA_OPER_TYPE_ENUM                             enTAF_MMA_OPER_TYPE_ENUM;
    enum TAF_SDC_LOG_OPER_NAME_TYPE_ENUM                    enTAF_SDC_LOG_OPER_NAME_TYPE_ENUM;

    enum TAF_MMA_PHONE_MODE_RESULT_ENUM                     enTAF_MMA_PHONE_MODE_RESULT_ENUM;

    enum TAF_MMA_INTERNAL_MSG_ID_ENUM                       enTAF_MMA_INTERNAL_MSG_ID_ENUM;
    enum TAF_MMA_PID_MSG_TYPE_ENUM                          enTAF_MMA_PID_MSG_TYPE_ENUM;
    enum TAF_MMA_CFREQ_LOCK_MODE_TYPE_ENUM                  enTAF_MMA_CFREQ_LOCK_MODE_TYPE_ENUM;

    enum MMA_TAF_CL_STATUS_ENUM                             enMMA_TAF_CL_STATUS_ENUM;
    enum MMA_TAF_RAT_TYPE_ENUM                              enMMA_TAF_RAT_TYPE_ENUM;
    enum MMA_TAF_HRPD_DATA_CALL_SYS_ACQ_RST_ENUM            enMMA_TAF_HRPD_DATA_CALL_SYS_ACQ_RST_ENUM;
    enum TAF_MMA_LOG_DELAY_REPORT_TYPE_ENUM                 enTAF_MMA_LOG_DELAY_REPORT_TYPE_ENUM;

}

/*****************************************************************************
 函 数 名  : ELF_TAF_ENUM_AT
 功能描述  : AT的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_ENUM_AT(void)
{
    enum AT_IMSA_MSG_TYPE_ENUM                              enAT_IMSA_MSG_TYPE_ENUM;
    enum AT_IMSA_IMS_REG_STATE_REPORT_ENUM                  enAT_IMSA_IMS_REG_STATE_REPORT_ENUM;
    enum AT_IMSA_CIREP_REPORT_ENUM                          enAT_IMSA_CIREP_REPORT_ENUM;

    enum TAF_XSMS_APP_MSG_TYPE_ENUM                         enTAF_XSMS_APP_MSG_TYPE_ENUM;
    enum TAF_XSMS_SEND_OPTION_ENUM                          enTAF_XSMS_SEND_OPTION_ENUM;
    enum TAF_XSMS_DIGITMODE_ENUM                            enTAF_XSMS_DIGITMODE_ENUM;
    enum TAF_XSMS_NUMBERMODE_ENUM                           enTAF_XSMS_NUMBERMODE_ENUM;
    enum TAF_XSMS_NUMBERTYPE_ENUM                           enTAF_XSMS_NUMBERTYPE_ENUM;
    enum TAF_XSMS_NUMBERPLAN_ENUM                           enTAF_XSMS_NUMBERPLAN_ENUM;
    enum TAF_XSMS_SUBADDR_TYPE_ENUM                         enTAF_XSMS_SUBADDR_TYPE_ENUM;
    enum TAF_XSMS_STATUS_ENUM                               enTAF_XSMS_STATUS_ENUM;

    enum MN_MSG_SEND_DOMAIN_ENUM                            enMN_MSG_SEND_DOMAIN_ENUM;
    enum MN_MSG_MEM_STORE_ENUM                              enMN_MSG_MEM_STORE_ENUM;

    enum AT_INTER_MSG_ID_ENUM                               enAT_INTER_MSG_ID_ENUM;
    enum AT_FC_DEVICE_TYPE_ENUM                             enAT_FC_DEVICE_TYPE_ENUM;
    enum AT_FC_POINT_TYPE_ENUM                              enAT_FC_POINT_TYPE_ENUM;
    enum AT_CLIENT_TAB_INDEX_ENUM                           enAT_CLIENT_TAB_INDEX_ENUM;

    enum AT_TIMER_OPERATION_TYPE_ENUM                       enAT_TIMER_OPERATION_TYPE_ENUM;

    enum PPP_AT_CTRL_OPER_TYPE_ENUM                         enPPP_AT_CTRL_OPER_TYPE_ENUM;

    enum USIMM_RESTRIC_CMD_ENUM                             enUSIMM_RESTRIC_CMD_ENUM;

    enum TAF_CCA_MSG_TYPE_ENUM                              enTAF_CCA_MSG_TYPE_ENUM;
    enum TAF_CALL_APP_ENCRYPT_VOICE_TYPE_ENUM               enTAF_CALL_APP_ENCRYPT_VOICE_TYPE_ENUM;
    enum TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM             enTAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM;
    enum TAF_CALL_REMOTE_CTRL_APP_TYPE_ENUM                 enTAF_CALL_REMOTE_CTRL_APP_TYPE_ENUM;
    enum TAF_CALL_REMOTE_CTRL_APP_RESULT_ENUM               enTAF_CALL_REMOTE_CTRL_APP_RESULT_ENUM;
    enum TAF_CALL_REMOTE_CTRL_OPER_RESULT_ENUM              enTAF_CALL_REMOTE_CTRL_OPER_RESULT_ENUM;
    enum TAF_CALL_APP_ECC_SRV_CAP_ENUM                      enTAF_CALL_APP_ECC_SRV_CAP_ENUM;
    enum TAF_CALL_APP_ECC_SRV_STATUS_ENUM                   enTAF_CALL_APP_ECC_SRV_STATUS_ENUM;
    enum TAF_CALL_APP_ECC_SRV_CAP_CFG_RESULT_ENUM           enTAF_CALL_APP_ECC_SRV_CAP_CFG_RESULT_ENUM;
    enum TAF_CALL_APP_SET_EC_TEST_MODE_ENUM                 enTAF_CALL_APP_SET_EC_TEST_MODE_ENUM;
    enum MM_TEST_AT_CMD_ENUM                                enMM_TEST_AT_CMD_ENUM;


}

/*****************************************************************************
 函 数 名  : ELF_TAT_ENUM_AT_DRV_AGENT
 功能描述  : AT和DRV_AGENT间的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月09日
    作    者   : h00360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAT_ENUM_AT_DRV_AGENT(void)
{
    enum DRV_AGENT_PH_PHYNUM_TYPE_ENUM                      enDRV_AGENT_PH_PHYNUM_TYPE_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_TAT_ENUM_AT_RABM
 功能描述  : AT和RABM间的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月09日
    作    者   : h00360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAT_ENUM_AT_RABM(void)
{
    enum AT_RABM_MSG_ID_ENUM                                enAT_RABM_MSG_ID_ENUM;
    enum AT_RABM_PARA_SET_RSLT_ENUM                         enAT_RABM_PARA_SET_RSLT_ENUM;
    enum AT_RABM_FASTDORM_OPERATION_ENUM                    enAT_RABM_FASTDORM_OPERATION_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_TAT_ENUM_AT_DIPC
 功能描述  : AT和DIPC间的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月09日
    作    者   : h00360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAT_ENUM_AT_DIPC(void)
{
    enum AT_DIPC_MSG_TYPE_ENUM                              enAT_DIPC_MSG_TYPE_ENUM;
    enum DIPC_BEARER_TYPE_ENUM                              enDIPC_BEARER_TYPE_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_TAT_ENUM_AT_MTA
 功能描述  : AT和MTA间的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月10日
    作    者   : h00360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAT_ENUM_AT_MTA(void)
{
    enum AT_MTA_MSG_TYPE_ENUM                               enAT_MTA_MSG_TYPE_ENUM;
    enum MTA_AT_RESULT_ENUM                                 enMTA_AT_RESULT_ENUM;
    enum MTA_AT_CGPSCLOCK_ENUM                              enMTA_AT_CGPSCLOCK_ENUM;
    enum MTA_AT_CPOS_OPERATE_TYPE_ENUM                      enMTA_AT_CPOS_OPERATE_TYPE_ENUM;
    enum AT_MTA_PERS_CATEGORY_ENUM                          enAT_MTA_PERS_CATEGORY_ENUM;
    enum AT_MTA_RPT_GENERAL_CTRL_TYPE_ENUM                  enAT_MTA_RPT_GENERAL_CTRL_TYPE_ENUM;
    enum AT_MTA_RPT_SET_TYPE_ENUM                           enAT_MTA_RPT_SET_TYPE_ENUM;
    enum AT_MTA_RPT_QRY_TYPE_ENUM                           enAT_MTA_RPT_QRY_TYPE_ENUM;
    enum AT_MTA_CMD_RPT_FLG_ENUM                            enAT_MTA_CMD_RPT_FLG_ENUM;
    enum AT_MTA_CMD_RATMODE_ENUM                            enAT_MTA_CMD_RATMODE_ENUM;
    enum MTA_AT_JAM_RESULT_ENUM                             enMTA_AT_JAM_RESULT_ENUM;
    enum AT_MTA_FREQLOCK_RATMODE_ENUM                       enAT_MTA_FREQLOCK_RATMODE_ENUM;
    enum AT_MTA_GSM_BAND_ENUM                               enAT_MTA_GSM_BAND_ENUM;
    enum AT_MTA_CFG_ENUM                                    enAT_MTA_CFG_ENUM;
    enum AT_MTA_MBMS_SERVICE_STATE_SET_ENUM                 enAT_MTA_MBMS_SERVICE_STATE_SET_ENUM;
    enum AT_MTA_MBMS_CAST_MODE_ENUM                         enAT_MTA_MBMS_CAST_MODE_ENUM;
    enum MTA_AT_EMBMS_FUNTIONALITY_STATUS_ENUM              enMTA_AT_EMBMS_FUNTIONALITY_STATUS_ENUM;
    enum MTA_AT_MBMS_SERVICE_EVENT_ENUM                     enMTA_AT_MBMS_SERVICE_EVENT_ENUM;
    enum AT_MTA_COEX_BW_TYPE_ENUM                           enAT_MTA_COEX_BW_TYPE_ENUM;
    enum AT_MTA_COEX_CFG_ENUM                               enAT_MTA_COEX_CFG_ENUM;
    enum AT_MTA_LTE_LOW_POWER_ENUM                          enAT_MTA_LTE_LOW_POWER_ENUM;
    enum AT_MTA_MBMS_PRIORITY_ENUM                          enAT_MTA_MBMS_PRIORITY_ENUM;
    enum AT_MTA_UE_CENTER_TYPE_ENUM                         enAT_MTA_UE_CENTER_TYPE_ENUM;
    enum AT_MTA_BODY_SAR_STATE_ENUM                         enAT_MTA_BODY_SAR_STATE_ENUM;
    enum MTA_AT_REFCLOCK_STATUS_ENUM                        enMTA_AT_REFCLOCK_STATUS_ENUM;
    enum MTA_AT_GPHY_XPASS_MODE_ENUM                        enMTA_AT_GPHY_XPASS_MODE_ENUM;
    enum MTA_AT_WPHY_HIGHWAY_MODE_ENUM                      enMTA_AT_WPHY_HIGHWAY_MODE_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_TAT_ENU_MTA_RRC
 功能描述  : RRC和MTA间的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月15日
    作    者   : h00360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAT_ENUM_MTA_RRC(void)
{
    enum MTA_RRC_MSG_TYPE_ENUM                              enMTA_RRC_MSG_TYPE_ENUM;
    enum MTA_RRC_RESULT_ENUM                                enMTA_RRC_RESULT_ENUM;
    enum NMR_UTRAN_MEASURED_TYPE_ENUM                       enNMR_UTRAN_MEASURED_TYPE_ENUM;
    enum GRR_MTA_NCELL_STATE_ENUM                           enGRR_MTA_NCELL_STATE_ENUM;
    enum MTA_RRC_JAM_MODE_ENUM                              enMTA_RRC_JAM_MODE_ENUM;
    enum MTA_RRC_JAM_RESULT_ENUM                            enMTA_RRC_JAM_RESULT_ENUM;
    enum MTA_RRC_GSM_BAND_ENUM                              enMTA_RRC_GSM_BAND_ENUM;
    enum MTA_RRC_FREQLOCK_TYPE_ENUM                         enMTA_RRC_FREQLOCK_TYPE_ENUM;
    enum MTA_NETMON_CELL_TYPE_ENUM                          enMTA_NETMON_CELL_TYPE_ENUM;
    enum MTA_NETMON_UTRAN_TYPE_ENUM                         enMTA_NETMON_UTRAN_TYPE_ENUM;
    enum MTA_NETMON_RESULT_ENUM                             enMTA_NETMON_RESULT_ENUM;
    enum MBMS_SERVICE_OP_ENUM                               enMBMS_SERVICE_OP_ENUM;
    enum MBMS_SERVICE_STATE_SET_ENUM                        enMBMS_SERVICE_STATE_SET_ENUM;
    enum MBMS_CAST_MODE_ENUM                                enMBMS_CAST_MODE_ENUM;
    enum MBMS_FUNTIONALITY_STATUS_ENUM                      enMBMS_FUNTIONALITY_STATUS_ENUM;
    enum MBMS_UNSOLICITED_CFG_ENUM                          enMBMS_UNSOLICITED_CFG_ENUM;
    enum MBMS_SERVICE_EVENT_ENUM                            enMBMS_SERVICE_EVENT_ENUM;
    enum MTA_LRRC_COEX_BW_TYPE_ENUM                         enMTA_LRRC_COEX_BW_TYPE_ENUM;
    enum MTA_LRRC_COEX_CFG_ENUM                             enMTA_LRRC_COEX_CFG_ENUM;
    enum RRC_MTA_BAND_IND_ENUM                              enRRC_MTA_BAND_IND_ENUM;
    enum MTA_RRC_FREQ_QRY_TYPE_ENUM                         enMTA_RRC_FREQ_QRY_TYPE_ENUM;

    enum VOS_RATMODE_ENUM                                   enVOS_RATMODE_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_TAT_ENU_MTA_PHY
 功能描述  : PHY和MTA间的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月15日
    作    者   : h00360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAT_ENUM_MTA_PHY(void)
{
    enum MTA_PHY_GPS_RF_CLOCK_STATE_ENUM                    enMTA_PHY_GPS_RF_CLOCK_STATE_ENUM;
    enum MTA_BODY_SAR_STATE_ENUM                            enMTA_BODY_SAR_STATE_ENUM;
    enum MTA_PHY_RESULT_ENUM                                enMTA_PHY_RESULT_ENUM;
    enum MTA_PHY_EMERGENCY_CALL_STATUS_ENUM                 enMTA_PHY_EMERGENCY_CALL_STATUS_ENUM;
    enum PHY_MTA_REFCLOCK_STATUS_ENUM                       enPHY_MTA_REFCLOCK_STATUS_ENUM;
    enum PHY_MTA_GPHY_XPASS_MODE_ENUM                       enPHY_MTA_GPHY_XPASS_MODE_ENUM;
    enum PHY_MTA_WPHY_HIGHWAY_MODE_ENUM                     enPHY_MTA_WPHY_HIGHWAY_MODE_ENUM;
    enum MTA_PHY_MSG_TYPE_ENUM                              enMTA_PHY_MSG_TYPE_ENUM;
    enum MTA_UPHY_INIT_STATUS_ENUM                          enMTA_UPHY_INIT_STATUS_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_TAT_ENUM_MTA_TIMER
 功能描述  : MTA时钟消息中的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月15日
    作    者   : h00360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAT_ENUM_MTA_TIMER(void)
{
    enum TAF_MTA_TIMER_STATUS_ENUM                          enTAF_MTA_TIMER_STATUS_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_TAT_ENUM_MTC_MMA
 功能描述  : MTC和MMA间的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月15日
    作    者   : h00360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAT_ENUM_MTC_MMA(void)
{
    enum MTC_MMA_MSG_ID_ENUM                                enMTC_MMA_MSG_ID_ENUM;
    enum MTC_MODEM_POWER_STATE_ENUM                         enMTC_MODEM_POWER_STATE_ENUM;
    enum MTC_RATMODE_ENUM                                   enMTC_RATMODE_ENUM;
    enum MTC_MODEM_IMS_VOICE_CAP_ENUM                       enMTC_MODEM_IMS_VOICE_CAP_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_TAT_ENUM_MTC_RRC
 功能描述  : MTC和RRC间的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月17日
    作    者   : h00360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAT_ENUM_MTC_RRC(void)
{
    enum MTC_RRC_MSG_ID_ENUM                                enMTC_RRC_MSG_ID_ENUM;
    enum MTC_RRC_RESULT_ENUM                                enMTC_RRC_RESULT_ENUM;
    enum RRC_MTC_GSM_BANDINDICATOR_ENUM                     enRRC_MTC_GSM_BANDINDICATOR_ENUM;
    enum RRC_MTC_GSM_CELL_STATE_ENUM                        enRRC_MTC_GSM_CELL_STATE_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_TAT_ENUM_MTC_MTA
 功能描述  : MTC和MTA公用模块的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月17日
    作    者   : h00360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAT_ENUM_MTC_MTA(void)
{
    enum MTA_MTC_MSG_ID_ENUM                                enMTA_MTC_MSG_ID_ENUM;
    enum MTA_MTC_RESULT_ENUM                                enMTA_MTC_RESULT_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_TAT_ENUM_MTC_RCM
 功能描述  : MTC和RCM间的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月17日
    作    者   : h00360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAT_ENUM_MTC_RCM(void)
{
    enum MTC_RCM_MSG_ID_ENUM                                enMTC_RCM_MSG_ID_ENUM;
    enum MTC_RCM_MODEM_TYPE_ENUM                            enMTC_RCM_MODEM_TYPE_ENUM;
    enum MTC_RCM_CONN_STATE_ENUM                            enMTC_RCM_CONN_STATE_ENUM;
    enum MTC_RCM_MODEM_POWER_STATE_ENUM                     enMTC_RCM_MODEM_POWER_STATE_ENUM;
    enum MTC_RCM_USIMM_CARD_SERVIC_ENUM                     enMTC_RCM_USIMM_CARD_SERVIC_ENUM;
    enum MTC_RCM_TC_STATUS_ENUM                             enMTC_RCM_TC_STATUS_ENUM;
    enum MTC_RCM_RAT_MODE_ENUM                              enMTC_RCM_RAT_MODE_ENUM;
    enum MTC_RCM_IMS_POWER_STATE_ENUM                       enMTC_RCM_IMS_POWER_STATE_ENUM;
    enum MTC_RCM_IMS_VOICE_CAP_ENUM                         enMTC_RCM_IMS_VOICE_CAP_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_TAT_ENUM_MTC_DEBUG
 功能描述  : MTC DEBUG模块的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月17日
    作    者   : h00360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAT_ENUM_MTC_DEBUG(void)
{
    enum MTC_DEBUG_BAND_ENUM                                enMTC_DEBUG_BAND_ENUM;
    enum MTC_DEBUG_MSG_ID_ENUM                              enMTC_DEBUG_MSG_ID_ENUM;
    enum MTC_DEBUG_CONN_STATE_ENUM                          enMTC_DEBUG_CONN_STATE_ENUM;
    enum MTC_DEBUG_MODEM_POWER_STATE_ENUM                   enMTC_DEBUG_MODEM_POWER_STATE_ENUM;
    enum MTC_DEBUG_USIMM_CARD_SERVIC_ENUM                   enMTC_DEBUG_USIMM_CARD_SERVIC_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_TAT_ENUM_AGPS
 功能描述  : AGPS的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月15日
    作    者   : h00360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAT_ENUM_AGPS(void)
{
    enum AGPS_POSITION_ACTION_TYPE_ENUM                     enAGPS_POSITION_ACTION_TYPE_ENUM;
    enum AGPS_RRLP_METHOD_TYPE_ENUM                         enAGPS_RRLP_METHOD_TYPE_ENUM;
    enum AGPS_POSITION_RESULT_TYPE_ENUM                     enAGPS_POSITION_RESULT_TYPE_ENUM;
    enum AGPS_POSITION_ESTIMAT_ENUM                         enAGPS_POSITION_ESTIMAT_ENUM;
    enum AGPS_ELLIP_POINT_LATITUDE_SIGN_ENUM                enAGPS_ELLIP_POINT_LATITUDE_SIGN_ENUM;
    enum AGPS_ELLIP_POINT_UNCERT_CIRCLE_LATITUDE_SIGN_ENUM  enAGPS_ELLIP_POINT_UNCERT_CIRCLE_LATITUDE_SIGN_ENUM;
    enum AGPS_ELLIP_POINT_UNCERT_ELLIP_LATITUDE_SIGN_ENUM   enAGPS_ELLIP_POINT_UNCERT_ELLIP_LATITUDE_SIGN_ENUM;
    enum AGPS_ELLIP_POINT_ALTI_LATITUDE_SIGN_ENUM           enAGPS_ELLIP_POINT_ALTI_LATITUDE_SIGN_ENUM;
    enum AGPS_ELLIP_POINT_ALTI_DIRECT_ENUM                  enAGPS_ELLIP_POINT_ALTI_DIRECT_ENUM;
    enum AGPS_ELLIP_POINT_ALTI_ELLIP_LATITUDE_SIGN_ENUM     enAGPS_ELLIP_POINT_ALTI_ELLIP_LATITUDE_SIGN_ENUM;
    enum AGPS_ELLIP_POINT_ALTI_ELLIP_ALTI_DIRECT_ENUM       enAGPS_ELLIP_POINT_ALTI_ELLIP_ALTI_DIRECT_ENUM;
    enum AGPS_MULTI_PATH_INDIC_ENUM                         enAGPS_MULTI_PATH_INDIC_ENUM;
    enum AGPS_POSITION_ERROR_REASON_ENUM                    enAGPS_POSITION_ERROR_REASON_ENUM;
    enum AGPS_POS_UDRE_ENUM                                 enAGPS_POS_UDRE_ENUM;
    enum AGPS_POS_SAT_STA_ENUM                              enAGPS_POS_SAT_STA_ENUM;
    enum AGPS_POSITION_TYPE_ENUM                            enAGPS_POSITION_TYPE_ENUM;
    enum AGPS_POS_METHOD_ENUM                               enAGPS_POS_METHOD_ENUM;
    enum AGPS_REP_CRIT_TYPE_ENUM                            enAGPS_REP_CRIT_TYPE_ENUM;
    enum AGPS_UE_POS_EVT_ENUM                               enAGPS_UE_POS_EVT_ENUM;
    enum AGPS_UDRE_GROWTH_RATE_ENUM                         enAGPS_UDRE_GROWTH_RATE_ENUM;
    enum AGPS_UDRE_VALID_TIME_ENUM                          enAGPS_UDRE_VALID_TIME_ENUM;
    enum AGPS_DIFF_CORRECT_STA_ENUM                         enAGPS_DIFF_CORRECT_STA_ENUM;
    enum AGPS_DOPPLER_UNCERTN_ENUM                          enAGPS_DOPPLER_UNCERTN_ENUM;
    enum AGPS_CODE_PHASE_SEARCH_WIN_ENUM                    enAGPS_CODE_PHASE_SEARCH_WIN_ENUM;
    enum AGPS_UE_POS_EVT_INTERVAL_ENUM                      enAGPS_UE_POS_EVT_INTERVAL_ENUM;
    enum AGPS_UE_POS_PERI_INTERVAL_ENUM                     enAGPS_UE_POS_PERI_INTERVAL_ENUM;
    enum AGPS_UE_POS_RPT_MOUNT_ENUM                         enAGPS_UE_POS_RPT_MOUNT_ENUM;
    enum AGPS_THRESHOLD_POSITION_ENUM                       enAGPS_THRESHOLD_POSITION_ENUM;
    enum AGPS_THRESHOLD_SFN_SFN_ENUM                        enAGPS_THRESHOLD_SFN_SFN_ENUM;
    enum AGPS_THRESHOLD_SFN_GPS_TOW_ENUM                    enAGPS_THRESHOLD_SFN_GPS_TOW_ENUM;
    enum AGPS_EPHEM_CLOCK_TYPE_ENUM                         enAGPS_EPHEM_CLOCK_TYPE_ENUM;
    enum AGPS_IONOSPHERIC_MODEL_TYPE_ENUM                   enAGPS_IONOSPHERIC_MODEL_TYPE_ENUM;
    enum AGPS_UTC_MODEL_TYPE_ENUM                           enAGPS_UTC_MODEL_TYPE_ENUM;
    enum AGPS_ALMANAC_SAT_INFO_TYPE_ENUM                    enAGPS_ALMANAC_SAT_INFO_TYPE_ENUM;
    enum AGPS_MULT_SETS_ENUM                                enAGPS_MULT_SETS_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_TAT_ENUM_OM_ERR
 功能描述  : OM ERROR LOG的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月16日
    作    者   : h00360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAT_ENUM_OM_ERR(void)
{
    enum OM_ELF_MTA_MSG_TYPE_ENUM                           enOM_ELF_MTA_MSG_TYPE_ENUM;
    enum OM_ELF_ERR_LOG_ALM_STATUS_ENUM                     enOM_ELF_ERR_LOG_ALM_STATUS_ENUM;
    enum OM_ELF_ERR_LOG_CTRL_LEVEL_ENUM                      enOM_ELF_ERR_LOG_ALM_LEVEL_ENUM;
    enum OM_ELF_FTM_CTRL_STATUS_ENUM                        enOM_ELF_FTM_CTRL_STATUS_ENUM;

    enum OM_ERR_LOG_MSG_TYPE_ENUM                           enOM_ERR_LOG_MSG_TYPE_ENUM;
    enum OM_ERR_LOG_MOUDLE_ID_ENUM                          enOM_ERR_LOG_MOUDLE_ID_ENUM;
    enum OM_APP_SWITCH_MSG_ID_ENUM                          enOM_APP_SWITCH_MSG_ID_ENUM;
    enum OM_APP_SEND_RESULT_ENUM                            enOM_APP_SEND_RESULT_ENUM;
    enum OM_APP_SWITCH_ENUM                                 enOM_APP_SWITCH_ENUM;
    enum OM_INFO_CLT_SCENE_TYPE_ENUM                        enOM_INFO_CLT_SCENE_TYPE_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_TAT_ENUM_OTA
 功能描述  : 开关消息的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月14日
    作    者   : h00360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAT_ENUM_OTA(void)
{
   enum NAS_OM_SM_ACTIVE_REQUEST_TYPE                       enNAS_OM_SM_ACTIVE_REQUEST_TYPE;
   enum NAS_OM_SM_DEACTIVE_REQUEST_TYPE                     enNAS_OM_SM_DEACTIVE_REQUEST_TYPE;
   enum NAS_OM_SM_MODIFY_REQUEST_TYPE                       enNAS_OM_SM_MODIFY_REQUEST_TYPE;
   enum NAS_OM_GMM_ATTACH_TYPE_ENUM                         enNAS_OM_GMM_ATTACH_TYPE_ENUM;
   enum NAS_OM_GMM_RAU_TYPE_ENUM                            enNAS_OM_GMM_RAU_TYPE_ENUM;
   enum NAS_OM_SMS_SAVE_AREA_ENUM                           enNAS_OM_SMS_SAVE_AREA_ENUM;
   enum NAS_OM_MM_LAU_TYPE_ENUM                             enNAS_OM_MM_LAU_TYPE_ENUM;
   enum NAS_OM_MMC_STATE_ENUM                               enNAS_OM_MMC_STATE_ENUM;
   enum OM_NAS_OTA_SWITCH_ENUM                              enOM_NAS_OTA_SWITCH_ENUM;
   enum NAS_OM_OTA_CNF_RESULT_ENUM                          enNAS_OM_OTA_CNF_RESULT_ENUM;
   enum NAS_OTA_CNF_ERRCODE_ENUM                            enNAS_OTA_CNF_ERRCODE_ENUM;

   enum NAS_OM_REGISTER_STATE_ENUM                          enNAS_OM_REGISTER_STATE_ENUM;
   enum NAS_OM_SERVICE_TYPE_ENUM                            enNAS_OM_SERVICE_TYPE_ENUM;

   enum NAS_OM_TRANS_MSG_TYPE_ENUM                          enNAS_OM_TRANS_MSG_TYPE_ENUM;
   enum NAS_OM_MM_STATE_ENUM                                enNAS_OM_MM_STATE_ENUM;
   enum MM_UPDATE_STATUS_ENUM                               enMM_UPDATE_STATUS_ENUM;
   enum NAS_OM_GMM_STATE_ENUM                               enNAS_OM_GMM_STATE_ENUM;
   enum GMM_UPDATE_STATUS_ENUM                              enGMM_UPDATE_STATUS_ENUM;
   enum PLMN_SEL_MODE_ENUM                                  enPLMN_SEL_MODE_ENUM;
   enum UE_OPERATE_MODE_ENUM                                enUE_OPERATE_MODE_ENUM;
   enum NET_OPERATE_MODE_ENUM                               enNET_OPERATE_MODE_ENUM;
   enum NET_TYPE_ENUM                                       enNET_TYPE_ENUM;
   enum NAS_OM_MM_SUB_STATE_ENUM                            enNAS_OM_MM_SUB_STATE_ENUM;
   enum NAS_OM_GMM_SUB_STATE_ENUM                           enNAS_OM_GMM_SUB_STATE_ENUM;
   enum NAS_OM_SERVICE_STATE_ENUM                           enNAS_OM_SERVICE_STATE_ENUM;
   enum NAS_OM_PDP_ACT_TYPE_ENUM                            enNAS_OM_PDP_ACT_TYPE_ENUM;
   enum NAS_OM_CURR_CODEC_TYPE_ENUM                         enNAS_OM_CURR_CODEC_TYPE_ENUM;
   enum NAS_OM_GSM_CODEC_CONFIG_ENUM                        enNAS_OM_GSM_CODEC_CONFIG_ENUM;
   enum NAS_OM_GMM_GPRS_STATE_ENUM                          enNAS_OM_GMM_GPRS_STATE_ENUM;
   enum NAS_OM_REPORT_ACTION_ENUM                           enNAS_OM_REPORT_ACTION_ENUM;
   enum NAS_OM_RESULT_ENUM                                  enNAS_OM_RESULT_ENUM;
   enum NAS_OM_MMA_CDMA_STATUS_REPORT_RESRLT_ENUM           enNAS_OM_MMA_CDMA_STATUS_REPORT_RESRLT_ENUM;
   enum OM_NAS_MMA_CDMA_STATUS_REPORT_CMD_ENUM              enOM_NAS_MMA_CDMA_STATUS_REPORT_CMD_ENUM;
   enum NAS_OM_MMA_SYS_MODE_ENUM                            enNAS_OM_MMA_SYS_MODE_ENUM;
   enum NAS_OM_MMA_PHONE_MODE_ENUM                          enNAS_OM_MMA_PHONE_MODE_ENUM;
   enum MODEM_ID_ASN_ENUM                                   enMODEM_ID_ASN_ENUM;
   enum NAS_OM_MMA_HRPD_SESSION_STATUS_ENUM                 enNAS_OM_MMA_HRPD_SESSION_STATUS_ENUM;
   enum NAS_OM_1X_CALL_STATE_ENUM                           enNAS_OM_1X_CALL_STATE_ENUM;
   enum NAS_OM_MMA_SYS_SUBMODE_ENUM                         enNAS_OM_MMA_SYS_SUBMODE_ENUM;
   enum NAS_OM_FSM_ID_ENUM                                  enNAS_OM_FSM_ID_ENUM;
   enum NAS_OM_TIN_TYPE_ENUM                                enNAS_OM_TIN_TYPE_ENUM;
   enum NAS_OM_DELAY_CLASS_ENUM                             enNAS_OM_DELAY_CLASS_ENUM;
   enum NAS_OM_RELIABILITY_CLASS_ENUM                       enNAS_OM_RELIABILITY_CLASS_ENUM;
   enum NAS_OM_PEAK_THROUGH_PUT_ENUM                        enNAS_OM_PEAK_THROUGH_PUT_ENUM;
   enum NAS_OM_PRECEDENCE_CLASS_ENUM                        enNAS_OM_PRECEDENCE_CLASS_ENUM;
   enum NAS_OM_MEAN_THROUGH_ENUM                            enNAS_OM_MEAN_THROUGH_ENUM;
   enum NAS_OM_TRAFFIC_CLASS_ENUM                           enNAS_OM_TRAFFIC_CLASS_ENUM;
   enum NAS_OM_DELIVERY_ORDER_ENUM                          enNAS_OM_DELIVERY_ORDER_ENUM;
   enum NAS_OM_DELIVERY_ERR_SDU_ENUM                        enNAS_OM_DELIVERY_ERR_SDU_ENUM;
   enum NAS_OM_RESIDUAL_BER_ENUM                            enNAS_OM_RESIDUAL_BER_ENUM;
   enum NAS_OM_SDU_ERROR_RATIO_ENUM                         enNAS_OM_SDU_ERROR_RATIO_ENUM;
   enum NAS_OM_TRAFF_HAND_PRIO_ENUM                         enNAS_OM_TRAFF_HAND_PRIO_ENUM;
   enum NAS_OM_APS_ADDR_ENUM                                enNAS_OM_APS_ADDR_ENUM;
   enum NAS_OM_SM_PDP_STATE_ENUM                            enNAS_OM_SM_PDP_STATE_ENUM;
   enum NAS_OM_SMC_MO_STATE_ENUM                            enNAS_OM_SMC_MO_STATE_ENUM;
   enum NAS_OM_SMC_MT_STATE_ENUM                            enNAS_OM_SMC_MT_STATE_ENUM;
   enum NAS_OM_SMR_STATE_ENUM                               enNAS_OM_SMR_STATE_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_TAT_ENUM_APS_DHCP
 功能描述  : APS_DHCP的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月30日
    作    者   : Y00322978
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAT_ENUM_APS_DHCP(void)
{
    enum TAF_APS_DHCP_PIF_MSG_TYPE_ENUM                               enTAF_APS_DHCP_PIF_MSG_TYPE_ENUM;
    enum TAF_APS_DHCP_ADDR_TYPE_ENUM                                  enTAF_APS_DHCP_ADDR_TYPE_ENUM;

}
/*****************************************************************************
 函 数 名  : ELF_TAT_ENUM_APS_PPP
 功能描述  : APS_PPP的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月30日
    作    者   : Y00322978
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAT_ENUM_APS_PPP(void)
{
    enum TAF_APS_PPP_PIF_MSG_TYPE_ENUM                                enTAF_APS_PPP_PIF_MSG_TYPE_ENUM;
    enum TAF_APS_PPP_RAT_MODE_ENUM                                    enTAF_APS_PPP_RAT_MODE_ENUM;
    enum TAF_APS_PPP_ADDR_TYPE_ENUM                                   enTAF_APS_PPP_ADDR_TYPE_ENUM;
    enum TAF_APS_PPP_AUTH_TYPE_ENUM                                   enTAF_APS_PPP_AUTH_TYPE_ENUM;
    enum TAF_APS_PPP_NAI_FROM_ENUM                                    enTAF_APS_PPP_NAI_FROM_ENUM;
    enum TAF_APS_PPP_CDATA_DIAL_MODE_ENUM                             enTAF_APS_PPP_CDATA_DIAL_MODE_ENUM;
    enum TAF_APS_PPP_LINK_STATUS_ENUM                                 enTAF_APS_PPP_LINK_STATUS_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_TAF_ENUM_LIST
 功能描述  : 枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_ENUM_LIST(void)
{
    ELF_TAF_ENUM_COMMON();

    ELF_TAF_ENUM_NAS_COMMON();

    ELF_TAF_ENUM_USIM();

    ELF_TAF_ENUM_NAS_SKT();

    ELF_TAF_ENUM_TAF_SDC();

    ELF_TAF_ENUM_APP_MMA();

    ELF_TAF_ENUM_MMA_MSCC();

    ELF_TAF_ENUM_MSCC_PIF();

    ELF_TAF_ENUM_XCC_TAF();

    ELF_TAF_ENUM_XSMS_TAF();

    ELF_TAF_ENUM_MN_CALL();

    ELF_TAF_ENUM_MN_MSG();

    ELF_TAF_ENUM_TAF_COMMON();

    ELF_TAF_ENUM_TAF_XCALL();

    ELF_TAF_ENUM_MMA();

    ELF_TAF_ENUM_AT();

    ELF_TAT_ENUM_AT_DRV_AGENT();

    ELF_TAT_ENUM_AT_RABM();

    ELF_TAT_ENUM_AT_DIPC();

    ELF_TAT_ENUM_AT_MTA();

    ELF_TAT_ENUM_APS_DHCP();

    ELF_TAT_ENUM_APS_PPP();
}

/*****************************************************************************
 函 数 名  : ELF_TAF_STRU_TraceTable_MMA
 功能描述  : TraceTable中MMA的消息结构
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_STRU_TraceTable_MMA(void)
{
    /******************* 发送模块：MMA，接收模块：TIMER Begin  ******************/
    NAS_TIMER_OPERATION_STRU                                stNAS_TIMER_OPERATION_STRU;
    TAF_MMA_ELF_TIMER_INFO_STRU                             stTAF_MMA_ELF_TIMER_INFO_STRU;

    /******************* 发送模块：MMA，接收模块：TIMER End  ********************/

    /******************* 发送模块：MMA，接收模块：MMA Begin  ********************/
    TAF_MMA_ELF_LOG_FSM_INFO_STRU                           stTAF_MMA_ELF_LOG_FSM_INFO_STRU;
    TAF_MMA_LOG_BUffER_MSG_INFO_STRU                        stTAF_MMA_LOG_BUffER_MSG_INFO_STRU;
    TAF_MMA_LOG_INTER_MSG_INFO_STRU                         stTAF_MMA_LOG_INTER_MSG_INFO_STRU;
    TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU         stTAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU;
    TAF_MMA_LOG_OPER_CTX_INFO_STRU                          stTAF_MMA_LOG_OPER_CTX_INFO_STRU;
    TAF_MMA_LOG_COPS_RLT_INFO_STRU                          stTAF_MMA_LOG_COPS_RLT_INFO_STRU;

    TAF_MMA_INTER_POWER_INIT_REQ_STRU                       stTAF_MMA_INTER_POWER_INIT_REQ_STRU;
    TAF_MMA_INTER_USIM_STATUS_CHANGE_IND_STRU               stTAF_MMA_INTER_USIM_STATUS_CHANGE_IND_STRU;
    TAF_MMA_PHONE_MODE_RSLT_IND_STRU                        stTAF_MMA_PHONE_MODE_RSLT_IND_STRU;

    TAF_MMA_LOG_READ_NV_INFO_IND_STRU                       stTAF_MMA_LOG_READ_NV_INFO_IND_STRU;
    TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_IND_STRU     stTAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_IND_STRU;
    TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_CTX_STRU     stTAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_CTX_STRU;
    /*******************  发送模块：MMA，接收模块：MMA End   ********************/

    /******************* 发送模块：MMA，接收模块：MSCC Begin  *******************/
    MMA_MSCC_START_REQ_STRU                                 stMMA_MSCC_START_REQ_STRU;
    MMA_MSCC_SIGN_REPORT_REQ_STRU                           stMMA_MSCC_SIGN_REPORT_REQ_STRU;
    MMA_MSCC_MODE_CHANGE_REQ_STRU                           stMMA_MSCC_MODE_CHANGE_REQ_STRU;
    MMA_MSCC_ATTACH_REQ_STRU                                stMMA_MSCC_ATTACH_REQ_STRU;
    MMA_MSCC_DETACH_REQ_STRU                                stMMA_MSCC_DETACH_REQ_STRU;
    MMA_MSCC_PLMN_LIST_REQ_STRU                             stMMA_MSCC_PLMN_LIST_REQ_STRU;
    MMA_MSCC_PLMN_LIST_ABORT_REQ_STRU                       stMMA_MSCC_PLMN_LIST_ABORT_REQ_STRU;
    MMA_MSCC_PLMN_USER_RESEL_REQ_STRU                       stMMA_MSCC_PLMN_USER_RESEL_REQ_STRU;
    MMA_MSCC_PLMN_SPECIAL_REQ_STRU                          stMMA_MSCC_PLMN_SPECIAL_REQ_STRU;
    MMA_MSCC_POWER_OFF_REQ_STRU                             stMMA_MSCC_POWER_OFF_REQ_STRU;
    MMA_MSCC_SYS_CFG_SET_REQ_STRU                           stMMA_MSCC_SYS_CFG_SET_REQ_STRU;
    MMA_MSCC_SYSTEM_ACQUIRE_REQ_STRU                        stMMA_MSCC_SYSTEM_ACQUIRE_REQ_STRU;
    MMA_MSCC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU                stMMA_MSCC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU;
    MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU                      stMMA_MSCC_OM_MAINTAIN_INFO_IND_STRU;
    MMA_MSCC_UPDATE_UPLMN_NTF_STRU                          stMMA_MSCC_UPDATE_UPLMN_NTF_STRU;
    MMA_MSCC_EOPLMN_SET_REQ_STRU                            stMMA_MSCC_EOPLMN_SET_REQ_STRU;
    MMA_MSCC_NET_SCAN_REQ_STRU                              stMMA_MSCC_NET_SCAN_REQ_STRU;
    MMA_MSCC_ABORT_NET_SCAN_REQ_STRU                        stMMA_MSCC_ABORT_NET_SCAN_REQ_STRU;
    MMA_MSCC_OTHER_MODEM_INFO_NOTIFY_STRU                   stMMA_MSCC_OTHER_MODEM_INFO_NOTIFY_STRU;
    MMA_MSCC_NCELL_INFO_NOTIFY_STRU                         stMMA_MSCC_NCELL_INFO_NOTIFY_STRU;
    MMA_MSCC_PS_TRANSFER_NOTIFY_STRU                        stMMA_MSCC_PS_TRANSFER_NOTIFY_STRU;
    MMA_MSCC_ACQ_REQ_STRU                                   stMMA_MSCC_ACQ_REQ_STRU;
    MMA_MSCC_REG_REQ_STRU                                   stMMA_MSCC_REG_REQ_STRU;
    MMA_MSCC_POWER_SAVE_REQ_STRU                            stMMA_MSCC_POWER_SAVE_REQ_STRU;
    MMA_MSCC_SRV_ACQ_REQ_STRU                               stMMA_MSCC_SRV_ACQ_REQ_STRU;
    MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU                      stMMA_MSCC_BEGIN_SESSION_NOTIFY_STRU;
    MMA_MSCC_END_SESSION_NOTIFY_STRU                        stMMA_MSCC_END_SESSION_NOTIFY_STRU;
    MMA_MSCC_IMS_SRV_INFO_NOTIFY_STRU                       stMMA_MSCC_IMS_SRV_INFO_NOTIFY_STRU;
    MMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU       stMMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU;
    MMA_MSCC_CDMA_MO_CALL_START_NTF_STRU                    stMMA_MSCC_CDMA_MO_CALL_START_NTF_STRU;
    MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU           stMMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU;
    MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU                  stMMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU;
    MMA_MSCC_CDMA_MO_CALL_END_NTF_STRU                      stMMA_MSCC_CDMA_MO_CALL_END_NTF_STRU;
    MMA_MSCC_CFREQ_LOCK_NTF_STRU                            stMMA_MSCC_CFREQ_LOCK_NTF_STRU;
    MMA_MSCC_CDMACSQ_SET_REQ_STRU                           stMMA_MSCC_CDMACSQ_SET_REQ_STRU;
    MMA_MSCC_CFPLMN_SET_REQ_STRU                            stMMA_MSCC_CFPLMN_SET_REQ_STRU;
    MMA_MSCC_CFPLMN_QUERY_REQ_STRU                          stMMA_MSCC_CFPLMN_QUERY_REQ_STRU;
    MMCM_OM_MAINTAIN_INFO_IND_STRU                          stMMCM_OM_MAINTAIN_INFO_IND_STRU;
    MMA_MSCC_PREF_PLMN_SET_REQ_STRU                         stMMA_MSCC_PREF_PLMN_SET_REQ_STRU;
    MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU                       stMMA_MSCC_PREF_PLMN_QUERY_REQ_STRU;
    MMA_MSCC_IMS_START_REQ_STRU                             stMMA_MSCC_IMS_START_REQ_STRU;
    MMA_MSCC_IMS_STOP_REQ_STRU                              stMMA_MSCC_IMS_STOP_REQ_STRU;
    MMA_MSCC_VOICE_DOMAIN_CHANGE_IND_STRU                   stMMA_MSCC_VOICE_DOMAIN_CHANGE_IND_STRU;
    MMA_MSCC_AUTO_RESEL_SET_STRU                            stMMA_MSCC_AUTO_RESEL_SET_STRU;
    MMA_MSCC_HANDSET_INFO_QRY_REQ_STRU                      stMMA_MSCC_HANDSET_INFO_QRY_REQ_STRU;
    MMA_MSCC_GET_GEO_REQ_STRU                               stMMA_MSCC_GET_GEO_REQ_STRU;
    MMA_MSCC_STOP_GET_GEO_REQ_STRU                          stMMA_MSCC_STOP_GET_GEO_REQ_STRU;
    MMA_MSCC_PS_RAT_TYPE_NTF_STRU                           stMMA_MSCC_PS_RAT_TYPE_NTF_STRU;
    MMA_MSCC_QUIT_CALL_BACK_NTF_STRU                        stMMA_MSCC_QUIT_CALL_BACK_NTF_STRU;
    MMA_MSCC_SET_CSIDLIST_REQ_STRU                          stMMA_MSCC_SET_CSIDLIST_REQ_STRU;
    MMA_MSCC_DPLMN_SET_REQ_STRU                             stMMA_MSCC_DPLMN_SET_REQ_STRU;
    MMA_MSCC_CSG_LIST_SEARCH_REQ_STRU                       stMMA_MSCC_CSG_LIST_SEARCH_REQ_STRU;
    MMA_MSCC_CSG_LIST_ABORT_REQ_STRU                        stMMA_MSCC_CSG_LIST_ABORT_REQ_STRU;
    MMA_MSCC_HDR_CSQ_SET_REQ_STRU                           stMMA_MSCC_HDR_CSQ_SET_REQ_STRU;
    /*******************  发送模块：MMA，接收模块：MSCC  End   *******************/

    /******************* 发送模块：MMA，接收模块：TAF Begin  ********************/
    MNPH_USIM_STATUS_IND_STRU                               stMNPH_USIM_STATUS_IND_STRU;
    TAF_MMA_POWER_OFF_IND_STRU                              stTAF_MMA_POWER_OFF_IND_STRU;
    MMA_MSG_CS_SERVICE_IND                                  stMMA_MSG_CS_SERVICE_IND;
    MMA_TAF_SERVICE_STATUS_CHANGE_NOTIFY_STRU               stMMA_TAF_SERVICE_STATUS_CHANGE_NOTIFY_STRU;
    MMA_TAF_NETWORK_CAPABILITY_CHANGE_NOTIFY_STRU           stMMA_TAF_NETWORK_CAPABILITY_CHANGE_NOTIFY_STRU;
    MMA_TAF_RAT_CHANGE_NOTIFY_STRU                          stMMA_TAF_RAT_CHANGE_NOTIFY_STRU;
    MMA_TAF_IMS_VOICE_CAP_IND_STRU                          stMMA_TAF_IMS_VOICE_CAP_IND_STRU;
    MMA_TAF_1X_SERVICE_STATUS_IND_STRU                      stMMA_TAF_1X_SERVICE_STATUS_IND_STRU;
    TAF_MMA_POWER_ON_IND_STRU                               stTAF_MMA_POWER_ON_IND_STRU;
    MMA_APS_EPDSZID_INFO_IND_STRU                           stMMA_APS_EPDSZID_INFO_IND_STRU;
    MMA_APS_CL_SERVICE_STATUS_IND_STRU                      stMMA_APS_CL_SERVICE_STATUS_IND_STRU;
    MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND_STRU                 stMMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND_STRU;
    MMA_TAF_SYS_CFG_INFO_IND_STRU                           stMMA_TAF_SYS_CFG_INFO_IND_STRU;
    MMA_TAF_HDR_CSQ_SET_CNF_STRU                            stMMA_TAF_HDR_CSQ_SET_CNF_STRU;
    MMA_TAF_HDR_CSQ_QRY_SETTING_CNF_STRU                    stMMA_TAF_HDR_CSQ_QRY_SETTING_CNF_STRU;
    MMA_TAF_HDR_CSQ_VALUE_IND_STRU                          stMMA_TAF_HDR_CSQ_VALUE_IND_STRU;

    TAF_MMA_CDMA_MO_CALL_START_NTF_STRU                     stTAF_MMA_CDMA_MO_CALL_START_NTF_STRU;
    TAF_MMA_CDMA_MO_CALL_SUCCESS_NTF_STRU                   stTAF_MMA_CDMA_MO_CALL_SUCCESS_NTF_STRU;
    TAF_MMA_CDMA_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU        stTAF_MMA_CDMA_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU;
    TAF_MMA_CDMA_MO_CALL_END_NTF_STRU                       stTAF_MMA_CDMA_MO_CALL_END_NTF_STRU;

    /*******************  发送模块：MMA，接收模块：TAF      End   *******************/

    /*******************  发送模块：MMA，接收模块：XSMS     Begin  *******************/
    MMA_XSMS_SERVICE_STATUS_IND_STRU                        stMMA_XSMS_SERVICE_STATUS_IND_STRU;
    /*******************  发送模块：MMA，接收模块：XSMS     End  *******************/

    /*******************  发送模块：MMA，接收模块：MTC      Begin  *******************/
    MMA_MTC_POWER_STATE_IND_STRU                            stMMA_MTC_POWER_STATE_IND_STRU;
    MMA_MTC_RAT_MODE_IND_STRU                               stMMA_MTC_RAT_MODE_IND_STRU;
    MMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU                    stMMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU;
    /*******************  发送模块：MMA，接收模块：MTC      End  *******************/

    /******************* 发送模块：MMA，接收模块：AT Begin  *******************/
    TAF_MMA_INIT_LOC_INFO_IND_STRU                          stTAF_MMA_INIT_LOC_INFO_IND_STRU;
    TAF_MMA_CLMODE_IND_STRU                                 stTAF_MMA_CLMODE_IND_STRU;
    TAF_MMA_CURR_SID_NID_QRY_REQ_STRU                       stTAF_MMA_CURR_SID_NID_QRY_REQ_STRU;
    TAF_MMA_CURR_SID_NID_QRY_CNF_STRU                       stTAF_MMA_CURR_SID_NID_QRY_CNF_STRU;
    /******************* 发送模块：MMA，接收模块：AT End  *******************/

}

/*****************************************************************************
 函 数 名  : ELF_TAF_STRU_TraceTable_TAF
 功能描述  : TraceTable中TAF的消息结构
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : w00351686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_STRU_TraceTable_TAF(void)
{
    /*******************  发送模块：TAF，接收模块：MMA  Begin   *******************/
    TAF_MMA_IMS_SRV_INFO_NOTIFY_STRU                        stTAF_MMA_IMS_SRV_INFO_NOTIFY_STRU;
    ATMMA_OM_MAINTAIN_INFO_IND_STRU                         stATMMA_OM_MAINTAIN_INFO_IND_STRU;
    AT_MMA_USIM_STATUS_IND_STRU                             stAT_MMA_USIM_STATUS_IND_STRU;
    AT_MMA_SIMLOCK_STATUS_STRU                              stAT_MMA_SIMLOCK_STATUS_STRU;
    TAF_MMA_PHONE_MODE_SET_REQ_STRU                         stTAF_MMA_PHONE_MODE_SET_REQ_STRU;
    TAF_MMA_PHONE_MODE_SET_CNF_STRU                         stTAF_MMA_PHONE_MODE_SET_CNF_STRU;
    TAF_MMA_SYS_CFG_REQ_STRU                                stTAF_MMA_SYS_CFG_REQ_STRU;
    TAF_MMA_SYS_CFG_CNF_STRU                                stTAF_MMA_SYS_CFG_CNF_STRU;
    TAF_MMA_ACQ_REQ_STRU                                    stTAF_MMA_ACQ_REQ_STRU;
    TAF_MMA_ACQ_CNF_STRU                                    stTAF_MMA_ACQ_CNF_STRU;
    TAF_MMA_REG_REQ_STRU                                    stTAF_MMA_REG_REQ_STRU;
    TAF_MMA_REG_CNF_STRU                                    stTAF_MMA_REG_CNF_STRU;
    TAF_MMA_DETACH_REQ_STRU                                 stTAF_MMA_DETACH_REQ_STRU;
    TAF_MMA_DETACH_CNF_STRU                                 stTAF_MMA_DETACH_CNF_STRU;
    TAF_MMA_POWER_SAVE_REQ_STRU                             stTAF_MMA_POWER_SAVE_REQ_STRU;
    TAF_MMA_POWER_SAVE_CNF_STRU                             stTAF_MMA_POWER_SAVE_CNF_STRU;
    TAF_MMA_SERVICE_STATUS_IND_STRU                         stTAF_MMA_SERVICE_STATUS_IND_STRU;
    TAF_MMA_ACQ_IND_STRU                                    stTAF_MMA_ACQ_IND_STRU;
    TAF_MMA_SYS_INFO_IND_STRU                               stTAF_MMA_SYS_INFO_IND_STRU;
    TAF_MMA_SIM_STATUS_IND_STRU                             stTAF_MMA_SIM_STATUS_IND_STRU;
    TAF_MMA_SRV_ACQ_REQ_STRU                                stTAF_MMA_SRV_ACQ_REQ_STRU;
    TAF_MMA_SRV_ACQ_CNF_STRU                                stTAF_MMA_SRV_ACQ_CNF_STRU;
    TAF_MMA_CDMA_MO_CALL_START_NTF_STRU                     stTAF_MMA_CDMA_MO_CALL_START_NTF_STRU;
    TAF_MMA_CDMA_MO_CALL_SUCCESS_NTF_STRU                   stTAF_MMA_CDMA_MO_CALL_SUCCESS_NTF_STRU;
    TAF_MMA_CDMA_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU        stTAF_MMA_CDMA_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU;
    TAF_MMA_CDMA_MO_CALL_END_NTF_STRU                       stTAF_MMA_CDMA_MO_CALL_END_NTF_STRU;
    TAF_MMA_CFREQ_LOCK_SET_REQ_STRU                         stTAF_MMA_CFREQ_LOCK_SET_REQ_STRU;
    TAF_MMA_CFREQ_LOCK_SET_CNF_STRU                         stTAF_MMA_CFREQ_LOCK_SET_CNF_STRU;
    TAF_MMA_CFREQ_LOCK_QUERY_REQ_STRU                       stTAF_MMA_CFREQ_LOCK_QUERY_REQ_STRU;
    TAF_MMA_CFREQ_LOCK_QUERY_CNF_STRU                       stTAF_MMA_CFREQ_LOCK_QUERY_CNF_STRU;
    TAF_MMA_CDMACSQ_SET_REQ_STRU                            stTAF_MMA_CDMACSQ_SET_REQ_STRU;
    TAF_MMA_CDMACSQ_SET_CNF_STRU                            stTAF_MMA_CDMACSQ_SET_CNF_STRU;
    TAF_MMA_CDMACSQ_QRY_REQ_STRU                            stTAF_MMA_CDMACSQ_QRY_REQ_STRU;
    TAF_MMA_CDMACSQ_QUERY_CNF_STRU                          stTAF_MMA_CDMACSQ_QUERY_CNF_STRU;
    TAF_MMA_CDMACSQ_IND_STRU                                stTAF_MMA_CDMACSQ_IND_STRU;
    TAF_MMA_CTIME_IND_STRU                                  stTAF_MMA_CTIME_IND_STRU;
    TAF_MMA_CFPLMN_SET_REQ_STRU                             stTAF_MMA_CFPLMN_SET_REQ_STRU;
    TAF_MMA_CFPLMN_QUERY_REQ_STRU                           stTAF_MMA_CFPLMN_QUERY_REQ_STRU;
    TAF_MMA_CFPLMN_SET_CNF_STRU                             stTAF_MMA_CFPLMN_SET_CNF_STRU;
    TAF_MMA_CFPLMN_QUERY_CNF_STRU                           stTAF_MMA_CFPLMN_QUERY_CNF_STRU;
    TAF_MMA_PREF_PLMN_SET_REQ_STRU                          stTAF_MMA_PREF_PLMN_SET_REQ_STRU;
    TAF_MMA_PREF_PLMN_SET_CNF_STRU                          stTAF_MMA_PREF_PLMN_SET_CNF_STRU;
    TAF_MMA_PREF_PLMN_QUERY_REQ_STRU                        stTAF_MMA_PREF_PLMN_QUERY_REQ_STRU;
    TAF_MMA_PREF_PLMN_QUERY_CNF_STRU                        stTAF_MMA_PREF_PLMN_QUERY_CNF_STRU;
    TAF_MMA_PREF_PLMN_TEST_REQ_STRU                         stTAF_MMA_PREF_PLMN_TEST_REQ_STRU;
    TAF_MMA_PREF_PLMN_TEST_CNF_STRU                         stTAF_MMA_PREF_PLMN_TEST_CNF_STRU;
    TAF_MMA_PHONE_MODE_QRY_REQ_STRU                         stTAF_MMA_PHONE_MODE_QRY_REQ_STRU;
    TAF_MMA_PHONE_MODE_QRY_CNF_STRU                         stTAF_MMA_PHONE_MODE_QRY_CNF_STRU;
    TAF_MMA_QUICKSTART_SET_REQ_STRU                         stTAF_MMA_QUICKSTART_SET_REQ_STRU;
    TAF_MMA_QUICKSTART_SET_CNF_STRU                         stTAF_MMA_QUICKSTART_SET_CNF_STRU;
    TAF_MMA_QUICKSTART_QRY_REQ_STRU                         stTAF_MMA_QUICKSTART_QRY_REQ_STRU;
    TAF_MMA_QUICKSTART_QRY_CNF_STRU                         stTAF_MMA_QUICKSTART_QRY_CNF_STRU;
    TAF_MMA_AUTO_ATTACH_SET_REQ_STRU                        stTAF_MMA_AUTO_ATTACH_SET_REQ_STRU;
    TAF_MMA_AUTO_ATTACH_SET_CNF_STRU                        stTAF_MMA_AUTO_ATTACH_SET_CNF_STRU;
    TAF_MMA_AUTO_ATTACH_QRY_REQ_STRU                        stTAF_MMA_AUTO_ATTACH_QRY_REQ_STRU;
    TAF_MMA_AUTO_ATTACH_QRY_CNF_STRU                        stTAF_MMA_AUTO_ATTACH_QRY_CNF_STRU;
    TAF_MMA_SYSCFG_QRY_REQ_STRU                             stTAF_MMA_SYSCFG_QRY_REQ_STRU;
    TAF_MMA_SYSCFG_QRY_CNF_STRU                             stTAF_MMA_SYSCFG_QRY_CNF_STRU;
    TAF_MMA_SYSCFG_TEST_REQ_STRU                            stTAF_MMA_SYSCFG_TEST_REQ_STRU;
    TAF_MMA_SYSCFG_TEST_CNF_STRU                            stTAF_MMA_SYSCFG_TEST_CNF_STRU;
    TAF_MMA_CRPN_QRY_REQ_STRU                               stTAF_MMA_CRPN_QRY_REQ_STRU;
    TAF_MMA_CRPN_QRY_CNF_STRU                               stTAF_MMA_CRPN_QRY_CNF_STRU;
    TAF_MMA_CMM_SET_REQ_STRU                                stTAF_MMA_CMM_SET_REQ_STRU;
    TAF_MMA_CMM_SET_CNF_STRU                                stTAF_MMA_CMM_SET_CNF_STRU;
    TAF_MMA_PLMN_AUTO_RESEL_REQ_STRU                        stTAF_MMA_PLMN_AUTO_RESEL_REQ_STRU;
    TAF_MMA_PLMN_AUTO_RESEL_CNF_STRU                        stTAF_MMA_PLMN_AUTO_RESEL_CNF_STRU;
    TAF_MMA_PLMN_SPECIAL_SEL_REQ_STRU                       stTAF_MMA_PLMN_SPECIAL_SEL_REQ_STRU;
    TAF_MMA_PLMN_SPECIAL_SEL_CNF_STRU                       stTAF_MMA_PLMN_SPECIAL_SEL_CNF_STRU;
    TAF_MMA_PLMN_LIST_ABORT_REQ_STRU                        stTAF_MMA_PLMN_LIST_ABORT_REQ_STRU;
    TAF_MMA_PLMN_LIST_ABORT_CNF_STRU                        stTAF_MMA_PLMN_LIST_ABORT_CNF_STRU;
    TAF_MMA_CERSSI_SET_REQ_STRU                             stTAF_MMA_CERSSI_SET_REQ_STRU;
    TAF_MMA_CERSSI_SET_CNF_STRU                             stTAF_MMA_CERSSI_SET_CNF_STRU;
    TAF_MMA_CERSSI_INFO_QRY_REQ_STRU                        stTAF_MMA_CERSSI_INFO_QRY_REQ_STRU;
    TAF_MMA_CERSSI_INFO_QRY_CNF_STRU                        stTAF_MMA_CERSSI_INFO_QRY_CNF_STRU;
    TAF_MMA_RSSI_INFO_IND_STRU                              stTAF_MMA_RSSI_INFO_IND_STRU;
    TAF_MMA_MT_POWER_DOWN_REQ_STRU                          stTAF_MMA_MT_POWER_DOWN_REQ_STRU;
    TAF_MMA_MT_POWER_DOWN_CNF_STRU                          stTAF_MMA_MT_POWER_DOWN_CNF_STRU;
    TAF_MMA_PREF_PLMN_TYPE_SET_REQ_STRU                     stTAF_MMA_PREF_PLMN_TYPE_SET_REQ_STRU;
    TAF_MMA_PREF_PLMN_TYPE_SET_CNF_STRU                     stTAF_MMA_PREF_PLMN_TYPE_SET_CNF_STRU;
    TAF_MMA_CIPHER_QRY_REQ_STRU                             stTAF_MMA_CIPHER_QRY_REQ_STRU;
    TAF_MMA_CIPHER_QRY_CNF_STRU                             stTAF_MMA_CIPHER_QRY_CNF_STRU;
    TAF_MMA_LOCATION_INFO_QRY_REQ_STRU                      stTAF_MMA_LOCATION_INFO_QRY_REQ_STRU;
    TAF_MMA_LOCATION_INFO_QRY_CNF_STRU                      stTAF_MMA_LOCATION_INFO_QRY_CNF_STRU;
    TAF_MMA_CDMA_LOCINFO_QRY_REQ_STRU                       stTAF_MMA_CDMA_LOCINFO_QRY_REQ_STRU;
    TAF_MMA_CDMA_LOCINFO_QRY_CNF_STRU                       stTAF_MMA_CDMA_LOCINFO_QRY_CNF_STRU;
    TAF_MMA_CSID_IND_STRU                                   stTAF_MMA_CSID_IND_STRU;
    TAF_MMA_AC_INFO_QRY_REQ_STRU                            stTAF_MMA_AC_INFO_QRY_REQ_STRU;
    TAF_MMA_AC_INFO_QRY_CNF_STRU                            stTAF_MMA_AC_INFO_QRY_CNF_STRU;
    TAF_MMA_AC_INFO_CHANGE_IND_STRU                         stTAF_MMA_AC_INFO_CHANGE_IND_STRU;
    TAF_MMA_COPN_INFO_QRY_REQ_STRU                          stTAF_MMA_COPN_INFO_QRY_REQ_STRU;
    TAF_MMA_COPN_INFO_QRY_CNF_STRU                          stTAF_MMA_COPN_INFO_QRY_CNF_STRU;
    TAF_MMA_SIM_INSERT_REQ_STRU                             stTAF_MMA_SIM_INSERT_REQ_STRU;
    TAF_MMA_SIM_INSERT_CNF_STRU                             stTAF_MMA_SIM_INSERT_CNF_STRU;
    TAF_MMA_EOPLMN_SET_REQ_STRU                             stTAF_MMA_EOPLMN_SET_REQ_STRU;
    TAF_MMA_EOPLMN_SET_CNF_STRU                             stTAF_MMA_EOPLMN_SET_CNF_STRU;
    TAF_MMA_EOPLMN_QRY_REQ_STRU                             stTAF_MMA_EOPLMN_QRY_REQ_STRU;
    TAF_MMA_EOPLMN_QRY_CNF_STRU                             stTAF_MMA_EOPLMN_QRY_CNF_STRU;
    TAF_MMA_NET_SCAN_REQ_STRU                               stTAF_MMA_NET_SCAN_REQ_STRU;
    TAF_MMA_NET_SCAN_CNF_STRU                               stTAF_MMA_NET_SCAN_CNF_STRU;
    TAF_MMA_NET_SCAN_ABORT_REQ_STRU                         stTAF_MMA_NET_SCAN_ABORT_REQ_STRU;
    TAF_MMA_ACCESS_MODE_QRY_REQ_STRU                        stTAF_MMA_ACCESS_MODE_QRY_REQ_STRU;
    TAF_MMA_ACCESS_MODE_QRY_CNF_STRU                        stTAF_MMA_ACCESS_MODE_QRY_CNF_STRU;
    TAF_MMA_COPS_QRY_REQ_STRU                               stTAF_MMA_COPS_QRY_REQ_STRU;
    TAF_MMA_COPS_QRY_CNF_STRU                               stTAF_MMA_COPS_QRY_CNF_STRU;
    TAF_MMA_REG_STATE_QRY_REQ_STRU                          stTAF_MMA_REG_STATE_QRY_REQ_STRU;
    TAF_MMA_REG_STATE_QRY_CNF_STRU                          stTAF_MMA_REG_STATE_QRY_CNF_STRU;
    TAF_MMA_SYSINFO_QRY_REQ_STRU                            stTAF_MMA_SYSINFO_QRY_REQ_STRU;
    TAF_MMA_SYSINFO_QRY_CNF_STRU                            stTAF_MMA_SYSINFO_QRY_CNF_STRU;
    TAF_MMA_CSNR_QRY_REQ_STRU                               stTAF_MMA_CSNR_QRY_REQ_STRU;
    TAF_MMA_CSNR_QRY_CNF_STRU                               stTAF_MMA_CSNR_QRY_CNF_STRU;
    TAF_MMA_CSQ_QRY_REQ_STRU                                stTAF_MMA_CSQ_QRY_REQ_STRU;
    TAF_MMA_CSQ_QRY_CNF_STRU                                stTAF_MMA_CSQ_QRY_CNF_STRU;
    TAF_MMA_CSQLVL_QRY_REQ_STRU                             stTAF_MMA_CSQLVL_QRY_REQ_STRU;
    TAF_MMA_CSQLVL_QRY_CNF_STRU                             stTAF_MMA_CSQLVL_QRY_CNF_STRU;
    TAF_MMA_ANTENNA_INFO_QRY_REQ_STRU                       stTAF_MMA_ANTENNA_INFO_QRY_REQ_STRU;
    TAF_MMA_ANTENNA_INFO_QRY_CNF_STRU                       stTAF_MMA_ANTENNA_INFO_QRY_CNF_STRU;
    TAF_MMA_HOME_PLMN_QRY_REQ_STRU                          stTAF_MMA_HOME_PLMN_QRY_REQ_STRU;
    TAF_MMA_HOME_PLMN_QRY_CNF_STRU                          stTAF_MMA_HOME_PLMN_QRY_CNF_STRU;
    TAF_MMA_SPN_QRY_REQ_STRU                                stTAF_MMA_SPN_QRY_REQ_STRU;
    TAF_MMA_SPN_QRY_CNF_STRU                                stTAF_MMA_SPN_QRY_CNF_STRU;
    TAF_MMA_MMPLMNINFO_QRY_REQ_STRU                         stTAF_MMA_MMPLMNINFO_QRY_REQ_STRU;
    TAF_MMA_MMPLMNINFO_QRY_CNF_STRU                         stTAF_MMA_MMPLMNINFO_QRY_CNF_STRU;
    TAF_MMA_LAST_CAMP_PLMN_QRY_REQ_STRU                     stTAF_MMA_LAST_CAMP_PLMN_QRY_REQ_STRU;
    TAF_MMA_LAST_CAMP_PLMN_QRY_CNF_STRU                     stTAF_MMA_LAST_CAMP_PLMN_QRY_CNF_STRU;
    TAF_MMA_USER_SRV_STATE_QRY_REQ_STRU                     stTAF_MMA_USER_SRV_STATE_QRY_REQ_STRU;
    TAF_MMA_USER_SRV_STATE_QRY_CNF_STRU                     stTAF_MMA_USER_SRV_STATE_QRY_CNF_STRU;
    TAF_MMA_POWER_ON_AND_REG_TIME_QRY_REQ_STRU              stTAF_MMA_POWER_ON_AND_REG_TIME_QRY_REQ_STRU;
    TAF_MMA_POWER_ON_AND_REG_TIME_QRY_CNF_STRU              stTAF_MMA_POWER_ON_AND_REG_TIME_QRY_CNF_STRU;
    TAF_MMA_BATTERY_CAPACITY_QRY_REQ_STRU                   stTAF_MMA_BATTERY_CAPACITY_QRY_REQ_STRU;
    TAF_MMA_BATTERY_CAPACITY_QRY_CNF_STRU                   stTAF_MMA_BATTERY_CAPACITY_QRY_CNF_STRU;
    TAF_MMA_HAND_SHAKE_QRY_REQ_STRU                         stTAF_MMA_HAND_SHAKE_QRY_REQ_STRU;
    TAF_MMA_HAND_SHAKE_QRY_CNF_STRU                         stTAF_MMA_HAND_SHAKE_QRY_CNF_STRU;
    TAF_MMA_TIME_CHANGE_IND_STRU                            stTAF_MMA_TIME_CHANGE_IND_STRU;
    TAF_MMA_MODE_CHANGE_IND_STRU                            stTAF_MMA_MODE_CHANGE_IND_STRU;
    TAF_MMA_PLMN_CHANGE_IND_STRU                            stTAF_MMA_PLMN_CHANGE_IND_STRU;
    TAF_MMA_SRV_STATUS_IND_STRU                             stTAF_MMA_SRV_STATUS_IND_STRU;
    TAF_MMA_REG_STATUS_IND_STRU                             stTAF_MMA_REG_STATUS_IND_STRU;
    TAF_MMA_REG_REJ_INFO_IND_STRU                           stTAF_MMA_REG_REJ_INFO_IND_STRU;
    TAF_MMA_PLMN_SElECTION_INFO_IND_STRU                    stTAF_MMA_PLMN_SElECTION_INFO_IND_STRU;
    TAF_MMA_PLMN_LIST_REQ_STRU                              stTAF_MMA_PLMN_LIST_REQ_STRU;
    TAF_MMA_PLMN_LIST_CNF_STRU                              stTAF_MMA_PLMN_LIST_CNF_STRU;
    TAF_MMA_EONS_UCS2_REQ_STRU                              stTAF_MMA_EONS_UCS2_REQ_STRU;
    TAF_MMA_EONS_UCS2_CNF_STRU                              stTAF_MMA_EONS_UCS2_CNF_STRU;
    TAF_MMA_IMS_SWITCH_SET_REQ_STRU                         stTAF_MMA_IMS_SWITCH_SET_REQ_STRU;
    TAF_MMA_IMS_SWITCH_SET_CNF_STRU                         stTAF_MMA_IMS_SWITCH_SET_CNF_STRU;
    TAF_MMA_IMS_SWITCH_QRY_REQ_STRU                         stTAF_MMA_IMS_SWITCH_QRY_REQ_STRU;
    TAF_MMA_IMS_SWITCH_QRY_CNF_STRU                         stTAF_MMA_IMS_SWITCH_QRY_CNF_STRU;
    TAF_MMA_VOICE_DOMAIN_SET_REQ_STRU                       stTAF_MMA_VOICE_DOMAIN_SET_REQ_STRU;
    TAF_MMA_VOICE_DOMAIN_SET_CNF_STRU                       stTAF_MMA_VOICE_DOMAIN_SET_CNF_STRU;
    TAF_MMA_VOICE_DOMAIN_QRY_REQ_STRU                       stTAF_MMA_VOICE_DOMAIN_QRY_REQ_STRU;
    TAF_MMA_VOICE_DOMAIN_QRY_CNF_STRU                       stTAF_MMA_VOICE_DOMAIN_QRY_CNF_STRU;
    TAF_MMA_ATTACH_REQ_STRU                                 stTAF_MMA_ATTACH_REQ_STRU;
    TAF_MMA_ATTACH_CNF_STRU                                 stTAF_MMA_ATTACH_CNF_STRU;
    TAF_MMA_PS_RAT_TYPE_NTF_STRU                            stTAF_MMA_PS_RAT_TYPE_NTF_STRU;
    TAF_MMA_1XCHAN_QUERY_REQ_STRU                           stTAF_MMA_1XCHAN_QUERY_REQ_STRU;
    TAF_MMA_CVER_QUERY_REQ_STRU                             stTAF_MMA_CVER_QUERY_REQ_STRU;
    TAF_MMA_STATE_QUERY_REQ_STRU                            stTAF_MMA_STATE_QUERY_REQ_STRU;
    TAF_MMA_CHIGHVER_QUERY_REQ_STRU                         stTAF_MMA_CHIGHVER_QUERY_REQ_STRU;
    TAF_MMA_QUIT_CALLBACK_SET_REQ_STRU                      stTAF_MMA_QUIT_CALLBACK_SET_REQ_STRU;
    TAF_MMA_CSIDLIST_SET_REQ_STRU                           stTAF_MMA_CSIDLIST_SET_REQ_STRU;
    TAF_MMA_1X_EMC_CALL_BACK_QRY_REQ_STRU                   stTAF_MMA_1X_EMC_CALL_BACK_QRY_REQ_STRU;
    TAF_MMA_CSG_LIST_SEARCH_REQ_STRU                        stTAF_MMA_CSG_LIST_SEARCH_REQ_STRU;
    TAF_MMA_CSG_LIST_ABORT_REQ_STRU                         stTAF_MMA_CSG_LIST_ABORT_REQ_STRU;
    TAF_MMA_HDR_CSQ_SET_REQ_STRU                            stTAF_MMA_HDR_CSQ_SET_REQ_STRU;
    TAF_MMA_HDR_CSQ_QRY_SETTING_REQ_STRU                    stTAF_MMA_HDR_CSQ_QRY_SETTING_REQ_STRU;
    /*******************  发送模块：TAF，接收模块：MMA  End   *******************/

    /*******************  发送模块：TAF，接收模块：XCC  Begin   *******************/
    APS_XCC_ORIG_DATA_CALL_REQ_STRU                         stAPS_XCC_ORIG_DATA_CALL_REQ_STRU;
    APS_XCC_HANGUP_DATA_CALL_REQ_STRU                       stAPS_XCC_HANGUP_DATA_CALL_REQ_STRU;
    APS_XCC_INCOMING_CALL_RSP_STRU                          stAPS_XCC_INCOMING_CALL_RSP_STRU;
    APS_XCC_ANSWER_DATA_CALL_REQ_STRU                       stAPS_XCC_ANSWER_DATA_CALL_REQ_STRU;
    APS_XCC_DATA_CALL_SUSPEND_RSP_STRU                      stAPS_XCC_DATA_CALL_SUSPEND_RSP_STRU;
    APS_XCC_PZID_INFO_NTF_STRU                              stAPS_XCC_PZID_INFO_NTF_STRU;
    APS_XCC_RESERVE_SR_ID_NTF_STRU                          stAPS_XCC_RESERVE_SR_ID_NTF_STRU;
    XCALL_XCC_ORIG_CALL_REQ_STRU                            stXCALL_XCC_ORIG_CALL_REQ_STRU;
    XCALL_XCC_HANGUP_CALL_REQ_STRU                          stXCALL_XCC_HANGUP_CALL_REQ_STRU;
    XCALL_XCC_INCOMING_CALL_RSP_STRU                        stXCALL_XCC_INCOMING_CALL_RSP_STRU;
    XCALL_XCC_ANSWER_CALL_REQ_STRU                          stXCALL_XCC_ANSWER_CALL_REQ_STRU;
    XCALL_XCC_BURST_DTMF_REQ_STRU                           stXCALL_XCC_BURST_DTMF_REQ_STRU;
    XCALL_XCC_SEND_FLASH_REQ_STRU                           stXCALL_XCC_SEND_FLASH_REQ_STRU;
    XCALL_XCC_SEND_CONT_DTMF_REQ_STRU                       stXCALL_XCC_SEND_CONT_DTMF_REQ_STRU;
    XCALL_XCC_PRIVACY_MODE_SET_REQ_STRU                     stXCALL_XCC_PRIVACY_MODE_SET_REQ_STRU;
    XCALL_XCC_PRIVACY_MODE_QRY_REQ_STRU                     stXCALL_XCC_PRIVACY_MODE_QRY_REQ_STRU;

    XCALL_XCC_START_DTMF_REQ_STRU                           stXCALL_XCC_START_DTMF_REQ_STRU;
    XCALL_XCC_STOP_DTMF_REQ_STRU                            stXCALL_XCC_STOP_DTMF_REQ_STRU;
    APS_XCC_MOBILE_STATION_REJECT_ORDER_STRU                stAPS_XCC_MOBILE_STATION_REJECT_ORDER_STRU;
    /*******************  发送模块：TAF，接收模块：XCC  End   *******************/

    /*******************  发送模块：TAF，接收模块：SN   Begin   *******************/
    APS_SNDCP_DEACTIVATE_IND_MSG                            stAPS_SNDCP_DEACTIVATE_IND_MSG;
    APS_SNDCP_MODIFY_IND_MSG                                stAPS_SNDCP_MODIFY_IND_MSG;
    /*******************  发送模块：TAF，接收模块：SN   End   *******************/

    /*******************  发送模块：TAF，接收模块：RABM Begin   *******************/
    TAFRABM_PS_DATA_REQ_STRU                                stTAFRABM_PS_DATA_REQ_STRU;
    TAFRABM_CS_DATA_REQ_STRU                                stTAFRABM_CS_DATA_REQ_STRU;
    RABM_APS_SET_TRANSMODE_MSG                              stRABM_APS_SET_TRANSMODE_MSG;
    CALL_RABM_VOICE_PREFER_CS_EXIST_IND_STRU                stCALL_RABM_VOICE_PREFER_CS_EXIST_IND_STRU;
    /*******************  发送模块：TAF，接收模块：RABM End   *******************/

    /*******************  发送模块：TAF，接收模块：AT   Begin   *******************/
    TAF_AT_ELF_MN_CALLBACK_CS_CALL_STRU                     stTAF_AT_ELF_MN_CALLBACK_CS_CALL_STRU;
    TAF_CALL_APP_PRIVACY_MODE_SET_CNF_STRU                  stTAF_CALL_APP_PRIVACY_MODE_SET_CNF_STRU;
    TAF_CALL_APP_PRIVACY_MODE_QRY_CNF_STRU                  stTAF_CALL_APP_PRIVACY_MODE_QRY_CNF_STRU;
    TAF_CALL_APP_PRIVACY_MODE_IND_STRU                      stTAF_CALL_APP_PRIVACY_MODE_IND_STRU;
    TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU                     stTAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU;
    TAF_CALL_APP_ENCRYPT_VOICE_CNF_STRU                     stTAF_CALL_APP_ENCRYPT_VOICE_CNF_STRU;
    TAF_CALL_APP_ENCRYPT_VOICE_IND_STRU                     stTAF_CALL_APP_ENCRYPT_VOICE_IND_STRU;
    TAF_CALL_APP_EC_REMOTE_CTRL_IND_STRU                    stTAF_CALL_APP_EC_REMOTE_CTRL_IND_STRU;
    TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ_STRU                stTAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ_STRU;
    TAF_CALL_APP_REMOTE_CTRL_ANSWER_CNF_STRU                stTAF_CALL_APP_REMOTE_CTRL_ANSWER_CNF_STRU;
    TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ_STRU                   stTAF_CALL_APP_ECC_SRV_CAP_CFG_REQ_STRU;
    TAF_CALL_APP_ECC_SRV_CAP_CFG_CNF_STRU                   stTAF_CALL_APP_ECC_SRV_CAP_CFG_CNF_STRU;
    TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ_STRU                   stTAF_CALL_APP_ECC_SRV_CAP_QRY_REQ_STRU;
    TAF_CALL_APP_ECC_SRV_CAP_QRY_CNF_STRU                   stTAF_CALL_APP_ECC_SRV_CAP_QRY_CNF_STRU;
    TAF_CALL_APP_SET_EC_TEST_MODE_REQ_STRU                  stTAF_CALL_APP_SET_EC_TEST_MODE_REQ_STRU;
    TAF_CALL_APP_SET_EC_TEST_MODE_CNF_STRU                  stTAF_CALL_APP_SET_EC_TEST_MODE_CNF_STRU;
    TAF_CALL_APP_GET_EC_TEST_MODE_REQ_STRU                  stTAF_CALL_APP_GET_EC_TEST_MODE_REQ_STRU;
    TAF_CALL_APP_GET_EC_TEST_MODE_CNF_STRU                  stTAF_CALL_APP_GET_EC_TEST_MODE_CNF_STRU;
    TAF_CALL_APP_GET_EC_RANDOM_REQ_STRU                     stTAF_CALL_APP_GET_EC_RANDOM_REQ_STRU;
    TAF_CALL_APP_GET_EC_RANDOM_CNF_STRU                     stTAF_CALL_APP_GET_EC_RANDOM_CNF_STRU;
    TAF_CALL_APP_GET_EC_KMC_REQ_STRU                        stTAF_CALL_APP_GET_EC_KMC_REQ_STRU;
    TAF_CALL_APP_GET_EC_KMC_CNF_STRU                        stTAF_CALL_APP_GET_EC_KMC_CNF_STRU;
    TAF_CALL_APP_SET_EC_KMC_REQ_STRU                        stTAF_CALL_APP_SET_EC_KMC_REQ_STRU;
    TAF_CALL_APP_SET_EC_KMC_CNF_STRU                        stTAF_CALL_APP_SET_EC_KMC_CNF_STRU;
    TAF_CALL_APP_ENCRYPTED_VOICE_DATA_IND_STRU              stTAF_CALL_APP_ENCRYPTED_VOICE_DATA_IND_STRU;
    /*******************  发送模块：TAF，接收模块：AT   End   *******************/

    /*******************  发送模块：TAF，接收模块：MTC  Begin   *******************/
    TAF_MTC_CS_SERVICE_INFO_IND_STRU                        stTAF_MTC_CS_SERVICE_INFO_IND_STRU;
    /*******************  发送模块：TAF，接收模块：MTC  End   *******************/

    /*******************  发送模块：TAF，接收模块：USIM Begin   *******************/
    NAS_LOG_STK_API_ENVELOP_DOWN_CODE_STRU                  stNAS_LOG_STK_API_ENVELOP_DOWN_CODE_STRU;
    /*******************  发送模块：TAF，接收模块：USIM Begin   *******************/

    /*******************  发送模块：TAF，接收模块：TAF Begin   *******************/
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    TAF_XCALL_MNTN_LOG_CALL_INFO_STRU                                           stTAF_XCALL_MNTN_LOG_CALL_INFO_STRU;
    TAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT_STRU                                       stTAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT_STRU;
    TAF_XCALL_MNTN_LOG_CALL_REDIAL_PERIOD_STRU                                  stTAF_XCALL_MNTN_LOG_CALL_REDIAL_PERIOD_STRU;
    TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL_STRU                   stTAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL_STRU;
    TAF_XCALL_MNTN_LOG_TIME_STAMP_VALIDATION_STRU                               stTAF_XCALL_MNTN_LOG_TIME_STAMP_VALIDATION_STRU;
    TAF_XCALL_MNTN_LOG_VOICEENC_PUB_KEY_AND_VER_STRU                            stTAF_XCALL_MNTN_LOG_VOICEENC_PUB_KEY_AND_VER_STRU;
    TAF_XCALL_MNTN_LOG_VOICEENC_CAP_CFG_PARA_STRU                               stTAF_XCALL_MNTN_LOG_VOICEENC_CAP_CFG_PARA_STRU;
    TAF_XCALL_MNTN_LOG_VOICEENC_LAST_INFO_ERASE_TIME_STRU                       stTAF_XCALL_MNTN_LOG_VOICEENC_LAST_INFO_ERASE_TIME_STRU;
    TAF_XCALL_MNTN_LOG_VOICEENC_LAST_PASSWD_RESET_TIME_STRU                     stTAF_XCALL_MNTN_LOG_VOICEENC_LAST_PASSWD_RESET_TIME_STRU;
    TAF_XCALL_MNTN_LOG_VOICEENC_TIMER_CFG_INFO_STRU                             stTAF_XCALL_MNTN_LOG_VOICEENC_TIMER_CFG_INFO_STRU;
    TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_REQ_STRU                                  stTAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_REQ_STRU;
    TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_RSP_STRU                                  stTAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_RSP_STRU;
    TAF_XCALL_MNTN_LOG_KMC_MSG_MT_ENCRYPT_IND_STRU                              stTAF_XCALL_MNTN_LOG_KMC_MSG_MT_ENCRYPT_IND_STRU;
    TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_REQ_STRU                                  stTAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_REQ_STRU;
    TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_RSP_STRU                                  stTAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_RSP_STRU;
    TAF_XCALL_MNTN_LOG_KMC_MSG_ERR_IND_STRU                                     stTAF_XCALL_MNTN_LOG_KMC_MSG_ERR_IND_STRU;
    TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_IND_STRU                          stTAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_IND_STRU;
    TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_RSP_STRU                          stTAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_RSP_STRU;
    TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_ACK_STRU                          stTAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_ACK_STRU;
    TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU                         stTAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU;
    TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_RSP_STRU                         stTAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_RSP_STRU;
    TAF_XCALL_MNTN_LOG_VOICEENC_REMOTE_CTRL_STATE_INFO_STRU                     stTAF_XCALL_MNTN_LOG_VOICEENC_REMOTE_CTRL_STATE_INFO_STRU;
    TAF_XCALL_MNTN_LOG_VOICEENC_KEY_UPDATE_STATE_INFO_STRU                      stTAF_XCALL_MNTN_LOG_VOICEENC_KEY_UPDATE_STATE_INFO_STRU;
    TAF_XCALL_MNTN_LOG_VOICEENC_VOICE_ENCRYPT_STATE_INFO_STRU                   stTAF_XCALL_MNTN_LOG_VOICEENC_VOICE_ENCRYPT_STATE_INFO_STRU;
    TAF_XCALL_MNTN_LOG_CIPHERTEXT_INFO_STRU                                     stTAF_XCALL_MNTN_LOG_CIPHERTEXT_INFO_STRU;
#endif
    /*******************  发送模块：TAF，接收模块：TAF End   *******************/

    /*******************  发送模块：TAF，接收模块：SI_PB Begin   *******************/
    NAS_LOG_PB_API_GET_XECC_NUMBER_STRU                     stNAS_LOG_PB_API_GET_XECC_NUMBER_STRU;
    /*******************  发送模块：TAF，接收模块：SI_PB End   *******************/

    /**************************** TAF <==> XSMS Begin ****************************/
    XCALL_XSMS_KMC_MSG_SEND_REQ_STRU                        stXCALL_XSMS_KMC_MSG_SEND_REQ_STRU;
    XSMS_XCALL_KMC_MSG_SEND_CNF_STRU                        stXSMS_XCALL_KMC_MSG_SEND_CNF_STRU;
    XSMS_XCALL_KMC_MSG_RCV_IND_STRU                         stXSMS_XCALL_KMC_MSG_RCV_IND_STRU;
    /**************************** TAF <==> XSMS End ****************************/

    /*******************  发送模块：TAF，接收模块：TIMER Begin    *******************/
    TAF_XCALL_TIMER_INFO_STRU                               stTAF_XCALL_TIMER_INFO_STRU;
    /*******************  发送模块：TAF，接收模块：TIMER End   *******************/

    /**************************** TAF_APS <==> DHCP Begin ****************************/
    APS_DHCP_DNS_IPV4_REQ_STRU                              stAPS_DHCP_DNS_IPV4_REQ_STRU;
    APS_DHCP_DNS_IPV6_REQ_STRU                              stAPS_DHCP_DNS_IPV6_REQ_STRU;
    DHCP_APS_DNS_IPV4_CNF_STRU                              stDHCP_APS_DNS_IPV4_CNF_STRU;
    DHCP_APS_DNS_IPV6_CNF_STRU                              stDHCP_APS_DNS_IPV6_CNF_STRU;
    APS_DHCP_DEACT_IND_STRU                                 stAPS_DHCP_DEACT_IND_STRU;
    APS_DHCP_DNS_IPV4_STRU                                  stAPS_DHCP_DNS_IPV4_STRU;
    APS_DHCP_DNS_IPV6_STRU                                  stAPS_DHCP_DNS_IPV6_STRU;
    /**************************** TAF_APS <==> DHCP End ****************************/

    /**************************** TAF_APS <==> PPP Begin ****************************/
    APS_PPP_ACT_REQ_STRU                                    stAPS_PPP_ACT_REQ_STRU;
    PPP_APS_ACT_CNF_STRU                                    stPPP_APS_ACT_CNF_STRU;
    APS_PPP_DEACT_REQ_STRU                                  stAPS_PPP_DEACT_REQ_STRU;
    PPP_APS_DEACT_CNF_STRU                                  stPPP_APS_DEACT_CNF_STRU;
    APS_PPP_DEACT_IND_STRU                                  stAPS_PPP_DEACT_IND_STRU;
    PPP_APS_DEACT_NTF_STRU                                  stPPP_APS_DEACT_NTF_STRU;
    PPP_APS_MODIFY_IND_STRU                                 stPPP_APS_MODIFY_IND_STRU;
    APS_PPP_MODE_CHANGE_NTF_STRU                            stAPS_PPP_MODE_CHANGE_NTF_STRU;
    APS_PPP_DIAL_MODE_NTF_STRU                              stAPS_PPP_DIAL_MODE_NTF_STRU;
    APS_PPP_LINK_STATUS_NTF_STRU                            stAPS_PPP_LINK_STATUS_NTF_STRU;
    PPP_APS_RECONN_IND_STRU                                 stPPP_APS_RECONN_IND_STRU;
    PPP_APS_PPP_RENEGO_IND_STRU                             stPPP_APS_PPP_RENEGO_IND_STRU;
    TAF_APS_PPP_IPV4_DNS_STRU                               stTAF_APS_PPP_IPV4_DNS_STRU;
    /**************************** TAF_APS <==> PPP End ****************************/
}

/*****************************************************************************
 函 数 名  : ELF_TAF_STRU_TraceTable_AT
 功能描述  : TraceTable中AT的消息结构
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月04日
    作    者   : h0360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_STRU_TraceTable_AT(void)
{
    /*******************  发送模块：AT，接收模块：IMSA   Begin   *******************/
    ID_AT_IMSA_CIREG_SET_REQ_ELF_STRU                       stID_AT_IMSA_CIREG_SET_REQ_ELF_STRU;
    ID_AT_IMSA_CIREG_QRY_REQ_ELF_STRU                       stID_AT_IMSA_CIREG_QRY_REQ_ELF_STRU;
    ID_AT_IMSA_CIREP_SET_REQ_ELF_STRU                       stID_AT_IMSA_CIREP_SET_REQ_ELF_STRU;
    ID_AT_IMSA_CIREP_QRY_REQ_ELF_STRU                       stID_AT_IMSA_CIREP_QRY_REQ_ELF_STRU;
    /*******************  发送模块：AT，接收模块：IMSA   End   *******************/


    /*******************  发送模块：AT，接收模块：XSMS   Begin   *******************/
    TAF_XSMS_ELF_APP_AT_CNF_STRU                            stTAF_XSMS_ELF_APP_AT_CNF_STRU;
    TAF_XSMS_SEND_MSG_REQ_STRU                              stTAF_XSMS_SEND_MSG_REQ_STRU;
    TAF_XSMS_WRITE_MSG_REQ_STRU                             stTAF_XSMS_WRITE_MSG_REQ_STRU;
    TAF_XSMS_DELETE_MSG_REQ_STRU                            stTAF_XSMS_DELETE_MSG_REQ_STRU;
    /*******************  发送模块：AT，接收模块：XSMS   End   *******************/

    /*******************  发送模块：AT，接收模块：TAF    Begin   *******************/
    MN_CALL_ELF_APP_REQ_MSG_STRU                            stMN_CALL_ELF_APP_REQ_MSG_STRU;
    TAF_CALL_APP_SEND_FLASH_REQ_STRU                        stTAF_CALL_APP_SEND_FLASH_REQ_STRU;
    TAF_CALL_BURST_DTMF_REQ_MSG_STRU                        stTAF_CALL_BURST_DTMF_REQ_MSG_STRU;
    TAF_CALL_APP_SEND_CUSTOM_DIAL_REQ_STRU                  stTAF_CALL_APP_SEND_CUSTOM_DIAL_REQ_STRU;
    TAF_CALL_CONT_DTMF_REQ_MSG_STRU                         stTAF_CALL_CONT_DTMF_REQ_MSG_STRU;
    TAF_CALL_SND_CCLPR_REQ_MSG_STRU                         stTAF_CALL_SND_CCLPR_REQ_MSG_STRU;

    MN_ELF_MSG_SEND_PARM_STRU                               stMN_ELF_MSG_SEND_PARM_STRU;
    MN_ELF_MSG_SEND_FROMMEM_PARM_STRU                       stMN_ELF_MSG_SEND_FROMMEM_PARM_STRU;
    MN_ELF_MSG_SEND_ACK_PARM_STRU                           stMN_ELF_MSG_SEND_ACK_PARM_STRU;
    MN_ELF_MSG_WRITE_PARM_STRU                              stMN_ELF_MSG_WRITE_PARM_STRU;
    MN_ELF_MSG_READ_PARM_STRU                               stMN_ELF_MSG_READ_PARM_STRU;
    MN_ELF_MSG_LIST_PARM_STRU                               stMN_ELF_MSG_LIST_PARM_STRU;
    MN_ELF_MSG_DELETE_PARAM_STRU                            stMN_ELF_MSG_DELETE_PARAM_STRU;
    MN_ELF_MSG_DELETE_TEST_STRU                             stMN_ELF_MSG_DELETE_TEST_STRU;
    MN_ELF_MSG_WRITE_SRV_PARAM_STRU                         stMN_ELF_MSG_WRITE_SRV_PARAM_STRU;
    MN_ELF_MSG_READ_COMM_PARAM_STRU                         stMN_ELF_MSG_READ_COMM_PARAM_STRU;
    MN_ELF_MSG_MODIFY_STATUS_PARM_STRU                      stMN_ELF_MSG_MODIFY_STATUS_PARM_STRU;
    MN_ELF_MSG_SET_RCVMSG_PATH_PARM_STRU                    stMN_ELF_MSG_SET_RCVMSG_PATH_PARM_STRU;
    MN_ELF_MSG_GET_RCVMSG_PATH_PARM_STRU                    stMN_ELF_MSG_GET_RCVMSG_PATH_PARM_STRU;
    MN_ELF_MSG_GET_STORAGE_STATUS_PARM_STRU                 stMN_ELF_MSG_GET_STORAGE_STATUS_PARM_STRU;
    MN_ELF_MSG_SET_MEMSTATUS_PARM_STRU                      stMN_ELF_MSG_SET_MEMSTATUS_PARM_STRU;
    MN_ELF_MSG_SET_LINK_CTRL_STRU                           stMN_ELF_MSG_SET_LINK_CTRL_STRU;
    MN_ELF_MSG_APP_REQ_MSG_STRU                             stMN_ELF_MSG_GET_LINK_CTRL_STRU;
    MN_ELF_MSG_STUB_MSG_STRU                                stMN_ELF_MSG_STUB_MSG_STRU;
    TAF_ELF_CBA_CBMI_RANGE_LIST_STRU                        stTAF_ELF_CBA_CBMI_RANGE_LIST_STRU;
    TAF_ELF_SS_REGISTERSS_REQ_STRU                          stTAF_ELF_SS_REGISTERSS_REQ_STRU;
    TAF_ELF_SS_ERASESS_REQ_STRU                             stTAF_ELF_SS_ERASESS_REQ_STRU;
    TAF_ELF_SS_ACTIVATESS_REQ_STRU                          stTAF_ELF_SS_ACTIVATESS_REQ_STRU;
    TAF_ELF_SS_DEACTIVATESS_REQ_STRU                        stTAF_ELF_SS_DEACTIVATESS_REQ_STRU;
    TAF_ELF_SS_INTERROGATESS_REQ_STRU                       stTAF_ELF_SS_INTERROGATESS_REQ_STRU;
    TAF_ELF_SS_REGPWD_REQ_STRU                              stTAF_ELF_SS_REGPWD_REQ_STRU;
    TAF_ELF_SS_PROCESS_USS_REQ_STRU                         stTAF_ELF_SS_PROCESS_USS_REQ_STRU;
    TAF_ELF_SS_ERASECC_ENTRY_REQ_STRU                       stTAF_ELF_SS_ERASECC_ENTRY_REQ_STRU;
    ELF_USSD_TRANS_MODE_STRU                                st_ELF_USSD_TRANS_MODE_STRU;

    TAF_ELF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU           stTAF_ELF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU;
    TAF_ELF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ_STRU           stTAF_ELF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ_STRU;
    TAF_ELF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU            stTAF_ELF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU;
    TAF_ELF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ_STRU            stTAF_ELF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ_STRU;
    TAF_ELF_PS_SET_TFT_INFO_REQ_STRU                        stTAF_ELF_PS_SET_TFT_INFO_REQ_STRU;
    TAF_ELF_PS_GET_TFT_INFO_REQ_STRU                        stTAF_ELF_PS_GET_TFT_INFO_REQ_STRU;
    TAF_ELF_PS_SET_UMTS_QOS_INFO_REQ_STRU                   stTAF_ELF_PS_SET_UMTS_QOS_INFO_REQ_STRU;
    TAF_ELF_PS_GET_UMTS_QOS_INFO_REQ_STRU                   stTAF_ELF_PS_GET_UMTS_QOS_INFO_REQ_STRU;
    TAF_ELF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU               stTAF_ELF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU;
    TAF_ELF_PS_GET_UMTS_QOS_MIN_INFO_REQ_STRU               stTAF_ELF_PS_GET_UMTS_QOS_MIN_INFO_REQ_STRU;
    TAF_ELF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ_STRU           stTAF_ELF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ_STRU;
    TAF_ELF_PS_SET_PDP_STATE_REQ_STRU                       stTAF_ELF_PS_SET_PDP_STATE_REQ_STRU;
    TAF_ELF_PS_GET_PDP_STATE_REQ_STRU                       stTAF_ELF_PS_GET_PDP_STATE_REQ_STRU;
    TAF_ELF_PS_CALL_MODIFY_REQ_STRU                         stTAF_ELF_PS_CALL_MODIFY_REQ_STRU;
    TAF_ELF_PS_CALL_ANSWER_REQ_STRU                         stTAF_ELF_PS_CALL_ANSWER_REQ_STRU;
    TAF_ELF_PS_CALL_HANGUP_REQ_STRU                         stTAF_ELF_PS_CALL_HANGUP_REQ_STRU;
    TAF_ELF_PS_GET_PDP_IP_ADDR_INFO_REQ_STRU                stTAF_ELF_PS_GET_PDP_IP_ADDR_INFO_REQ_STRU;
    TAF_ELF_PS_GET_PDP_CONTEXT_INFO_REQ_STRU                stTAF_ELF_PS_GET_PDP_CONTEXT_INFO_REQ_STRU;
    TAF_ELF_PS_SET_ANSWER_MODE_INFO_REQ_STRU                stTAF_ELF_PS_SET_ANSWER_MODE_INFO_REQ_STRU;
    TAF_ELF_PS_GET_ANSWER_MODE_INFO_REQ_STRU                stTAF_ELF_PS_GET_ANSWER_MODE_INFO_REQ_STRU;
    TAF_ELF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU   stTAF_ELF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU;
    TAF_ELF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ_STRU    stTAF_ELF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ_STRU;
    TAF_ELF_PS_GET_DYNAMIC_TFT_INFO_REQ_STRU                stTAF_ELF_PS_GET_DYNAMIC_TFT_INFO_REQ_STRU;
    TAF_ELF_PS_SET_EPS_QOS_INFO_REQ_STRU                    stTAF_ELF_PS_SET_EPS_QOS_INFO_REQ_STRU;
    TAF_ELF_PS_GET_EPS_QOS_INFO_REQ_STRU                    stTAF_ELF_PS_GET_EPS_QOS_INFO_REQ_STRU;
    TAF_ELF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ_STRU            stTAF_ELF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ_STRU;
    TAF_ELF_PS_CALL_ORIG_REQ_STRU                           stTAF_ELF_PS_CALL_ORIG_REQ_STRU;
    TAF_ELF_PS_CALL_END_REQ_STRU                            stTAF_ELF_PS_CALL_END_REQ_STRU;
    TAF_ELF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU              stTAF_ELF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU;
    TAF_ELF_PS_PPP_DIAL_ORIG_REQ_STRU                       stTAF_ELF_PS_PPP_DIAL_ORIG_REQ_STRU;
    TAF_ELF_PS_GET_DSFLOW_INFO_REQ_STRU                     stTAF_ELF_PS_GET_DSFLOW_INFO_REQ_STRU;
    TAF_ELF_PS_CLEAR_DSFLOW_REQ_STRU                        stTAF_ELF_PS_CLEAR_DSFLOW_REQ_STRU;
    TAF_ELF_PS_CONFIG_DSFLOW_RPT_REQ_STRU                   stTAF_ELF_PS_CONFIG_DSFLOW_RPT_REQ_STRU;
    TAF_ELF_PS_CONFIG_NBNS_FUNCTION_REQ_STRU                stTAF_ELF_PS_CONFIG_NBNS_FUNCTION_REQ_STRU;
    TAF_ELF_PS_SET_AUTHDATA_INFO_REQ_STRU                   stTAF_ELF_PS_SET_AUTHDATA_INFO_REQ_STRU;
    TAF_ELF_PS_GET_AUTHDATA_INFO_REQ_STRU                   stTAF_ELF_PS_GET_AUTHDATA_INFO_REQ_STRU;
    TAF_ELF_PS_GET_NEGOTIATION_DNS_REQ_STRU                 stTAF_ELF_PS_GET_NEGOTIATION_DNS_REQ_STRU;
    TAF_ELF_PS_SET_PDP_AUTH_INFO_REQ_STRU                   stTAF_ELF_PS_SET_PDP_AUTH_INFO_REQ_STRU;
    TAF_ELF_PS_GET_PDP_AUTH_INFO_REQ_STRU                   stTAF_ELF_PS_GET_PDP_AUTH_INFO_REQ_STRU;
    TAF_ELF_PS_SET_PDP_DNS_INFO_REQ_STRU                    stTAF_ELF_PS_SET_PDP_DNS_INFO_REQ_STRU;
    TAF_ELF_PS_GET_PDP_DNS_INFO_REQ_STRU                    stTAF_ELF_PS_GET_PDP_DNS_INFO_REQ_STRU;
    TAF_ELF_PS_TRIG_GPRS_DATA_REQ_STRU                      stTAF_ELF_PS_TRIG_GPRS_DATA_REQ_STRU;
    TAF_ELF_PS_LTECS_REQ_STRU                               stTAF_ELF_PS_LTECS_REQ_STRU;
    TAF_CALL_APP_PRIVACY_MODE_SET_REQ_STRU                  stTAF_CALL_APP_PRIVACY_MODE_SET_REQ_STRU;
    TAF_CALL_APP_PRIVACY_MODE_QRY_REQ_STRU                  stTAF_CALL_APP_PRIVACY_MODE_QRY_REQ_STRU;
    /*******************  发送模块：AT，接收模块：TAF    End   *******************/

    /*******************  发送模块：AT，接收模块：AT     Begin   *******************/
    AT_MSG_STRU                                             stAT_MSG_STRU;
    NAS_AT_SDT_AT_PART_ST                                   stNAS_AT_SDT_AT_PART_ST;
    NAS_AT_SDT_AT_CLIENT_TABLE_STRU                         stNAS_AT_SDT_AT_CLIENT_TABLE_STRU;
    AT_MNTN_MSC_STRU                                        stAT_MNTN_MSC_STRU;
    AT_MNTN_FLOW_CTRL_STRU                                  stAT_MNTN_FLOW_CTRL_STRU;
    AT_MNTN_FC_POINT_STRU                                   stAT_MNTN_FC_POINT_STRU;
    AT_MNTN_RPTPORT_STRU                                    stAT_MNTN_RPTPORT_STRU;
    /*******************  发送模块：AT，接收模块：AT     End   *******************/

    /*******************  发送模块：AT，接收模块：TIMER  Begin   *******************/
    AT_TIMER_OPERATION_STRU                                 stAT_TIMER_OPERATION_STRU;
    /*******************  发送模块：AT，接收模块：TIMER  End   *******************/



    /*******************  发送模块：AT，接收模块：DRV_AGENT Begin   *******************/
    GAS_ELF_AT_CMD_STRU                                     stGAS_ELF_AT_CMD_STRU;
    DRV_ELF_AGENT_GPIOPL_SET_REQ_STRU                       stDRV_ELF_AGENT_GPIOPL_SET_REQ_STRU;
    DRV_ELF_AGENT_DATALOCK_SET_REQ_STRU                     stDRV_ELF_AGENT_DATALOCK_SET_REQ_STRU;
    DRV_ELF_AGENT_TMODE_SET_REQ_STRU                        stDRV_ELF_AGENT_TMODE_SET_REQ_STRU;
    DRV_ELF_AGENT_FCHAN_SET_REQ_STRU                        stDRV_ELF_AGENT_FCHAN_SET_REQ_STRU;
    AT_ELF_DRV_AGENT_RXDIV_SET_STRU                         stAT_ELF_DRV_AGENT_RXDIV_SET_STRU;
    DRV_ELF_AGENT_SIMLOCK_SET_REQ_STRU                      stDRV_ELF_AGENT_SIMLOCK_SET_REQ_STRU;
    SPY_ELF_TEMP_THRESHOLD_PARA_STRU                        stSPY_ELF_TEMP_THRESHOLD_PARA_STRU;
    DRV_ELF_AGENT_TSELRF_SET_REQ_STRU                       stDRV_ELF_AGENT_TSELRF_SET_REQ_STRU;
    TAF_ELF_CUSTOM_CARDLOCK_STATUS_STRU                     stTAF_ELF_CUSTOM_CARDLOCK_STATUS_STRU;
    DRV_ELF_AGENT_SPWORD_SET_REQ_STRU                       stDRV_ELF_AGENT_SPWORD_SET_REQ_STRU;
    DRV_ELF_AGENT_PSTANDBY_REQ_STRU                         stDRV_ELF_AGENT_PSTANDBY_REQ_STRU;
    DRV_ELF_AGENT_HUK_SET_REQ_STRU                          stDRV_ELF_AGENT_HUK_SET_REQ_STRU;
    DRV_ELF_AGENT_FACAUTHPUBKEY_SET_REQ_STRU                stDRV_ELF_AGENT_FACAUTHPUBKEY_SET_REQ_STRU;
    DRV_ELF_AGENT_IDENTIFYEND_SET_REQ_STRU                  stDRV_ELF_AGENT_IDENTIFYEND_SET_REQ_STRU;
    DRV_ELF_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU             stDRV_ELF_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU;
    DRV_ELF_AGENT_PHONEPHYNUM_SET_REQ_STRU                  stDRV_ELF_AGENT_PHONEPHYNUM_SET_REQ_STRU;
    DRV_ELF_AGENT_PORTCTRLTMP_SET_REQ_STRU                  stDRV_ELF_AGENT_PORTCTRLTMP_SET_REQ_STRU;
    DRV_ELF_AGENT_PORTATTRIBSET_SET_REQ_STRU                stDRV_ELF_AGENT_PORTATTRIBSET_SET_REQ_STRU;
    DRV_ELF_AGENT_OPWORD_SET_REQ_STRU                       stDRV_ELF_AGENT_OPWORD_SET_REQ_STRU;
    DRV_ELF_AGENT_SARREDUCTION_SET_REQ_STRU                 stDRV_ELF_AGENT_SARREDUCTION_SET_REQ_STRU;
    TAF_ELF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU                  stTAF_ELF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU;
    DRV_ELF_AGENT_AP_SIMST_SET_REQ_STRU                     stDRV_ELF_AGENT_AP_SIMST_SET_REQ_STRU;
    DRV_ELF_AGENT_HVPDH_REQ_STRU                            stDRV_ELF_AGENT_HVPDH_REQ_STRU;
    DRV_ELF_AGENT_ANTSWITCH_SET_STRU                        stDRV_ELF_AGENT_ANTSWITCH_SET_STRU;
    /*******************  发送模块：AT，接收模块：DRV_AGENT End   *******************/

    /*******************  发送模块：AT，接收模块：RABM      Begin   *******************/
    AT_RABM_SET_FASTDORM_PARA_REQ_STRU                      stAT_RABM_SET_FASTDORM_PARA_REQ_STRU;
    AT_RABM_QRY_FASTDORM_PARA_REQ_STRU                      stAT_RABM_QRY_FASTDORM_PARA_REQ_STRU;
    AT_RABM_RELEASE_RRC_REQ_STRU                            stAT_RABM_RELEASE_RRC_REQ_STRU;
    AT_RABM_SET_VOICEPREFER_PARA_REQ_STRU                   stAT_RABM_SET_VOICEPREFER_PARA_REQ_STRU;
    AT_RABM_QRY_VOICEPREFER_PARA_REQ_STRU                   stAT_RABM_QRY_VOICEPREFER_PARA_REQ_STRU;
    /*******************  发送模块：AT，接收模块：RABM      End   *******************/

    /*******************  发送模块：PPP，接收模块：AT       Begin   *******************/
    AT_PPP_RELEASE_IND_MSG_STRU                             stAT_PPP_RELEASE_IND_MSG_STRU;
    AT_PPP_MODEM_MSC_IND_MSG_STRU                           stAT_PPP_MODEM_MSC_IND_MSG_STRU;
    AT_PPP_PROTOCOL_REL_IND_MSG_STRU                        stAT_PPP_PROTOCOL_REL_IND_MSG_STRU;
    /*******************  发送模块：PPP，接收模块：AT       End   *******************/

    /*******************  发送模块：AT， 接收模块：APP_NDIS Begin   *******************/
    AT_ELF_NDIS_PDNINFO_CFG_REQ_STRU                        stAT_ELF_NDIS_PDNINFO_CFG_REQ_STRU;
    AT_ELF_NDIS_PDNINFO_REL_REQ_STRU                        stAT_ELF_NDIS_PDNINFO_REL_REQ_STRU;
    /*******************  发送模块：AT， 接收模块：APP_NDIS End   *******************/

    /*******************  发送模块：APP_NDIS，接收模块：AT  Begin   *******************/
    AT_ELF_NDIS_PDNINFO_CFG_CNF_STRU                        stAT_ELF_NDIS_PDNINFO_CFG_CNF_STRU;
    AT_ELF_NDIS_PDNINFO_REL_CNF_STRU                        stAT_ELF_NDIS_PDNINFO_REL_CNF_STRU;
    /*******************  发送模块：APP_NDIS，接收模块：AT  End   *******************/

    /*******************  发送模块：AT，接收模块：DIPC      Begin   *******************/
    AT_DIPC_PDP_ACT_STRU                                    stAT_DIPC_PDP_ACT_STRU;
    AT_DIPC_PDP_DEACT_STRU                                  stAT_DIPC_PDP_DEACT_STRU;
    /*******************  发送模块：AT，接收模块：DIPC      End   *******************/

    /*******************  发送模块：AT，接收模块：MMA       Begin   *******************/
    USIMM_ELF_RACCESS_REQ_STRU                              stUSIMM_ELF_RACCESS_REQ_STRU;
    TAF_ELF_MSG_PARA_READ_STRU                              stTAF_ELF_MSG_PARA_READ_STRU;
    TAF_ELF_PH_PIN_DATA_STRU                                stTAF_ELF_PH_PIN_DATA_STRU;
    TAF_ELF_ME_PERSONALISATION_DATA_STRU                    stTAF_ELF_ME_PERSONALISATION_DATA_STRU;
    TAF_ELF_PH_QRY_USIM_INFO_STRU                           stTAF_ELF_PH_QRY_USIM_INFO_STRU;
    TAF_ELF_PH_QRY_CPNN_INFO_STRU                           stTAF_ELF_PH_QRY_CPNN_INFO_STRU;
    MN_ELF_PH_SET_CPIN_REQ_STRU                             stMN_ELF_PH_SET_CPIN_REQ_STRU;
    TAF_ELF_MMA_COPS_FORMAT_TYPE_SET_REQ_STRU               stTAF_ELF_MMA_COPS_FORMAT_TYPE_SET_REQ_STRU;
    TAF_ELF_MMA_USIM_STUB_SET_REQ_STRU                      stTAF_ELF_MMA_USIM_STUB_SET_REQ_STRU;
    TAF_ELF_MMA_REFRESH_STUB_SET_REQ_STRU                   stTAF_ELF_MMA_REFRESH_STUB_SET_REQ_STRU;
    TAF_ELF_MMA_AUTO_RESEL_STUB_SET_REQ_STRU                stTAF_ELF_MMA_AUTO_RESEL_STUB_SET_REQ_STRU;
    /*******************  发送模块：AT，接收模块：MMA       End   *******************/

    /*******************  发送模块：AT，接收模块：MTA       Begin   *******************/
    AT_ELF_MTA_CPOS_REQ_STRU                                stAT_ELF_MTA_CPOS_REQ_STRU;
    AT_ELF_MTA_APSEC_REQ_STRU                               stAT_ELF_MTA_APSEC_REQ_STRU;
    AT_ELF_MTA_SIMLOCKUNLOCK_REQ_STRU                       stAT_ELF_MTA_SIMLOCKUNLOCK_REQ_STRU;
    AT_ELF_MTA_QRY_NMR_REQ_STRU                             stAT_ELF_MTA_QRY_NMR_REQ_STRU;
    AT_ELF_MTA_RESEL_OFFSET_CFG_SET_NTF_STRU                stAT_ELF_MTA_RESEL_OFFSET_CFG_SET_NTF_STRU;
    AT_ELF_MTA_WRR_AUTOTEST_QRY_PARA_STRU                   stAT_ELF_MTA_WRR_AUTOTEST_QRY_PARA_STRU;
    AT_ELF_MTA_WRR_CELLINFO_QRY_REQ_STRU                    stAT_ELF_MTA_WRR_CELLINFO_QRY_REQ_STRU;
    MTA_ELF_AT_WRR_FREQLOCK_CTRL_STRU                       stMTA_ELF_AT_WRR_FREQLOCK_CTRL_STRU;
    AT_ELF_MTA_WRR_RRC_VERSION_SET_REQ_STRU                 stAT_ELF_MTA_WRR_RRC_VERSION_SET_REQ_STRU;
    AT_ELF_MTA_WRR_CELLSRH_SET_REQ_STRU                     stAT_ELF_MTA_WRR_CELLSRH_SET_REQ_STRU;
    AT_ELF_MTA_BODY_SAR_SET_REQ_STRU                        stAT_ELF_MTA_BODY_SAR_SET_REQ_STRU;
    AT_ELF_MTA_CURC_SET_NOTIFY_STRU                         stAT_ELF_MTA_CURC_SET_NOTIFY_STRU;
    AT_ELF_MTA_UNSOLICITED_RPT_SET_REQ_STRU                 stAT_ELF_MTA_UNSOLICITED_RPT_SET_REQ_STRU;
    AT_ELF_MTA_UNSOLICITED_RPT_QRY_REQ_STRU                 stAT_ELF_MTA_UNSOLICITED_RPT_QRY_REQ_STRU;
    AT_ELF_MTA_NCELL_MONITOR_SET_REQ_STRU                   stAT_ELF_MTA_NCELL_MONITOR_SET_REQ_STRU;
    AT_ELF_MTA_REFCLKFREQ_SET_REQ_STRU                      stAT_ELF_MTA_REFCLKFREQ_SET_REQ_STRU;
    AT_ELF_MTA_HANDLEDECT_SET_REQ_STRU                      stAT_ELF_MTA_HANDLEDECT_SET_REQ_STRU;
    AT_ELF_MTA_ECID_SET_REQ_STRU                            stAT_ELF_MTA_ECID_SET_REQ_STRU;
    AT_ELF_MTA_SET_DPDTTEST_FLAG_REQ_STRU                   stAT_ELF_MTA_SET_DPDTTEST_FLAG_REQ_STRU;
    AT_ELF_MTA_SET_DPDT_VALUE_REQ_STRU                      stAT_ELF_MTA_SET_DPDT_VALUE_REQ_STRU;
    AT_ELF_MTA_QRY_DPDT_VALUE_REQ_STRU                      stAT_ELF_MTA_QRY_DPDT_VALUE_REQ_STRU;
    AT_ELF_MTA_RRC_PROTECT_PS_REQ_STRU                      stAT_ELF_MTA_RRC_PROTECT_PS_REQ_STRU;
    AT_ELF_MTA_PHY_INIT_REQ_STRU                            stAT_ELF_MTA_PHY_INIT_REQ_STRU;
    AT_ELF_MTA_MBMS_SERVICE_OPTION_SET_REQ_STRU             stAT_ELF_MTA_MBMS_SERVICE_OPTION_SET_REQ_STRU;
    AT_ELF_MTA_MBMS_PREFERENCE_SET_REQ_STRU                 stAT_ELF_MTA_MBMS_PREFERENCE_SET_REQ_STRU;
    AT_ELF_MTA_MBMS_UNSOLICITED_CFG_SET_REQ_STRU            stAT_ELF_MTA_MBMS_UNSOLICITED_CFG_SET_REQ_STRU;
    AT_ELF_MTA_LOW_POWER_CONSUMPTION_SET_REQ_STRU           stAT_ELF_MTA_LOW_POWER_CONSUMPTION_SET_REQ_STRU;
    AT_ELF_MTA_MBMS_INTERESTLIST_SET_REQ_STRU               stAT_ELF_MTA_MBMS_INTERESTLIST_SET_REQ_STRU;
    AT_ELF_MTA_MBMS_SERVICE_STATE_SET_REQ_STRU              stAT_ELF_MTA_MBMS_SERVICE_STATE_SET_REQ_STRU;
    AT_ELF_MTA_LTE_WIFI_COEX_SET_REQ_STRU                   stAT_ELF_MTA_LTE_WIFI_COEX_SET_REQ_STRU;
    AT_ELF_MTA_SET_UE_CENTER_REQ_STRU                       stAT_ELF_MTA_SET_UE_CENTER_REQ_STRU;
    AT_ELF_MTA_SET_GSM_FREQLOCK_REQ_STRU                    stAT_ELF_MTA_SET_GSM_FREQLOCK_REQ_STRU;
    /*******************  发送模块：AT，接收模块：MTA       End   *******************/
}

/*****************************************************************************
 函 数 名  : ELF_TAF_STRU_TraceTable_MTA
 功能描述  : TraceTable中MTA的消息结构
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月04日
    作    者   : h0360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_STRU_TraceTable_MTA(void)
{
    /*******************  发送模块：MTA，接收模块：AT       Begin   *******************/
    MTA_ELF_AT_CPOS_CNF_STRU                                stMTA_ELF_AT_CPOS_CNF_STRU;
    MTA_ELF_AT_CGPSCLOCK_CNF_STRU                           stMTA_ELF_AT_CGPSCLOCK_CNF_STRU;
    MTA_ELF_AT_CPOSR_IND_STRU                               stMTA_ELF_AT_CPOSR_IND_STRU;
    MTA_ELF_AT_XCPOSRRPT_IND_STRU                           stMTA_ELF_AT_XCPOSRRPT_IND_STRU;
    MTA_ELF_AT_APSEC_CNF_STRU                               stMTA_ELF_AT_APSEC_CNF_STRU;
    MTA_ELF_AT_SIMLOCKUNLOCK_CNF_STRU                       stMTA_ELF_AT_SIMLOCKUNLOCK_CNF_STRU;
    MTA_ELF_AT_QRY_NMR_CNF_STRU                             stMTA_ELF_AT_QRY_NMR_CNF_STRU;
    MTA_ELF_AT_WRR_AUTOTEST_QRY_CNF_STRU                    stMTA_ELF_AT_WRR_AUTOTEST_QRY_CNF_STRU;
    MTA_ELF_AT_WRR_CELLINFO_QRY_CNF_STRU                    stMTA_ELF_AT_WRR_CELLINFO_QRY_CNF_STRU;
    MTA_ELF_AT_WRR_MEANRPT_QRY_CNF_STRU                     stMTA_ELF_AT_WRR_MEANRPT_QRY_CNF_STRU;
    MTA_ELF_AT_WRR_FREQLOCK_SET_CNF_STRU                    stMTA_ELF_AT_WRR_FREQLOCK_SET_CNF_STRU;
    MTA_ELF_AT_WRR_RRC_VERSION_SET_CNF_STRU                 stMTA_ELF_AT_WRR_RRC_VERSION_SET_CNF_STRU;
    MTA_ELF_AT_WRR_CELLSRH_SET_CNF_STRU                     stMTA_ELF_AT_WRR_CELLSRH_SET_CNF_STRU;
    MTA_ELF_AT_WRR_FREQLOCK_QRY_CNF_STRU                    stMTA_ELF_AT_WRR_FREQLOCK_QRY_CNF_STRU;
    MTA_ELF_AT_WRR_RRC_VERSION_QRY_CNF_STRU                 stMTA_ELF_AT_WRR_RRC_VERSION_QRY_CNF_STRU;
    MTA_ELF_AT_WRR_CELLSRH_QRY_CNF_STRU                     stMTA_ELF_AT_WRR_CELLSRH_QRY_CNF_STRU;
    MTA_ELF_AT_RESULT_CNF_STRU                              stMTA_ELF_AT_RESULT_CNF_STRU;
    MTA_ELF_AT_CURC_QRY_CNF_STRU                            stMTA_ELF_AT_CURC_QRY_CNF_STRU;
    MTA_ELF_AT_UNSOLICITED_RPT_SET_CNF_STRU                 stMTA_ELF_AT_UNSOLICITED_RPT_SET_CNF_STRU;
    MTA_ELF_AT_UNSOLICITED_RPT_QRY_CNF_STRU                 stMTA_ELF_AT_UNSOLICITED_RPT_QRY_CNF_STRU;
    MTA_ELF_AT_IMEI_VERIFY_QRY_CNF_STRU                     stMTA_ELF_AT_IMEI_VERIFY_QRY_CNF_STRU;
    MTA_ELF_AT_CGSN_QRY_CNF_STRU                            stMTA_ELF_AT_CGSN_QRY_CNF_STRU;
    MTA_ELF_AT_NCELL_MONITOR_QRY_CNF_STRU                   stMTA_ELF_AT_NCELL_MONITOR_QRY_CNF_STRU;
    MTA_ELF_AT_NCELL_MONITOR_IND_STRU                       stMTA_ELF_AT_NCELL_MONITOR_IND_STRU;
    MTA_ELF_AT_REFCLKFREQ_QRY_CNF_STRU                      stMTA_ELF_AT_REFCLKFREQ_QRY_CNF_STRU;
    MTA_ELF_AT_REFCLKFREQ_IND_STRU                          stMTA_ELF_AT_REFCLKFREQ_IND_STRU;
    MTA_ELF_AT_HANDLEDECT_SET_CNF_STRU                      stMTA_ELF_AT_HANDLEDECT_SET_CNF_STRU;
    MTA_ELF_AT_HANDLEDECT_QRY_CNF_STRU                      stMTA_ELF_AT_HANDLEDECT_QRY_CNF_STRU;
    MTA_ELF_AT_PS_TRANSFER_IND_STRU                         stMTA_ELF_AT_PS_TRANSFER_IND_STRU;
    MTA_ELF_AT_ECID_SET_CNF_STRU                            stMTA_ELF_AT_ECID_SET_CNF_STRU;
    MTA_ELF_AT_RF_LCD_MIPICLK_CNF_STRU                      stMTA_ELF_AT_RF_LCD_MIPICLK_CNF_STRU;
    MTA_ELF_AT_RF_LCD_MIPICLK_IND_STRU                      stMTA_ELF_AT_RF_LCD_MIPICLK_IND_STRU;
    MTA_ELF_AT_SET_DPDTTEST_FLAG_CNF_STRU                   stMTA_ELF_AT_SET_DPDTTEST_FLAG_CNF_STRU;
    MTA_ELF_AT_SET_DPDT_VALUE_CNF_STRU                      stMTA_ELF_AT_SET_DPDT_VALUE_CNF_STRU;
    MTA_ELF_AT_QRY_DPDT_VALUE_CNF_STRU                      stMTA_ELF_AT_QRY_DPDT_VALUE_CNF_STRU;
    MTA_ELF_AT_RRC_PROTECT_PS_CNF_STRU                      stMTA_ELF_AT_RRC_PROTECT_PS_CNF_STRU;
    MTA_ELF_AT_PHY_INIT_CNF_STRU                            stMTA_ELF_AT_PHY_INIT_CNF_STRU;
    MTA_ELF_AT_SET_GSM_FREQLOCK_CNF_STRU                    stMTA_ELF_AT_SET_GSM_FREQLOCK_CNF_STRU;
    MTA_ELF_AT_SET_FEMCTRL_CNF_STRU                         stMTA_ELF_AT_SET_FEMCTRL_CNF_STRU;
    MTA_ELF_AT_XPASS_INFO_IND_STRU                          stMTA_ELF_AT_XPASS_INFO_IND_STRU;
    MTA_ELF_AT_MBMS_SIB16_NETWORK_TIME_QRY_CNF_STRU         stMTA_ELF_AT_MBMS_SIB16_NETWORK_TIME_QRY_CNF_STRU;
    MTA_ELF_AT_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU          stMTA_ELF_AT_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU;
    MTA_ELF_AT_MBMS_NETWORK_INFO_QRY_CNF_STRU               stMTA_ELF_AT_MBMS_NETWORK_INFO_QRY_CNF_STRU;
    MTA_ELF_AT_EMBMS_STATUS_QRY_CNF_STRU                    stMTA_ELF_AT_EMBMS_STATUS_QRY_CNF_STRU;
    MTA_ELF_AT_MBMS_SERVICE_EVENT_IND_STRU                  stMTA_ELF_AT_MBMS_SERVICE_EVENT_IND_STRU;
    MTA_ELF_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU           stMTA_ELF_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU;
    MTA_ELF_AT_LTE_WIFI_COEX_QRY_CNF_STRU                   stMTA_ELF_AT_LTE_WIFI_COEX_QRY_CNF_STRU;
    MTA_ELF_AT_SET_FR_CNF_STRU                              stMTA_ELF_AT_SET_FR_CNF_STRU;
    MTA_ELF_AT_TRANSMODE_QRY_CNF_STRU                       stMTA_ELF_AT_TRANSMODE_QRY_CNF_STRU;
    MTA_ELF_AT_SET_UE_CENTER_CNF_STRU                       stMTA_ELF_AT_SET_UE_CENTER_CNF_STRU;
    MTA_ELF_AT_QRY_UE_CENTER_CNF_STRU                       stMTA_ELF_AT_QRY_UE_CENTER_CNF_STRU;
    /*******************  发送模块：MTA，接收模块：AT       End   *******************/

    /*******************  发送模块：MTA，接收模块：GAS      Begin   *******************/
    MTA_RRC_QRY_NMR_REQ_STRU                                stMTA_RRC_QRY_NMR_REQ_STRU;
    MTA_GRR_NCELL_MONITOR_SET_REQ_STRU                      stMTA_GRR_NCELL_MONITOR_SET_REQ_STRU;
    MTA_GRR_NCELL_MONITOR_QRY_REQ_STRU                      stMTA_GRR_NCELL_MONITOR_QRY_REQ_STRU;
    MTA_ELF_RRC_POSITION_CNF_STRU                           stMTA_ELF_RRC_POSITION_CNF_STRU;
    MTA_GRR_FREQLOCK_SET_REQ_STRU                           stMTA_GRR_FREQLOCK_SET_REQ_STRU;
    /*******************  发送模块：MTA，接收模块：GAS      End   *******************/

    /*******************  发送模块：MTA，接收模块：PHY      Begin   *******************/
    MTA_PHY_SET_GPS_RF_CLOCK_REQ_STRU                       stMTA_PHY_SET_GPS_RF_CLOCK_REQ_STRU;
    MTA_GUPHY_SET_DPDTTEST_FLAG_NTF_STRU                    stMTA_GUPHY_SET_DPDTTEST_FLAG_NTF_STRU;
    MTA_GUPHY_SET_DPDT_VALUE_NTF_STRU                       stMTA_GUPHY_SET_DPDT_VALUE_NTF_STRU;
    MTA_GUPHY_QRY_DPDT_VALUE_REQ_STRU                       stMTA_GUPHY_QRY_DPDT_VALUE_REQ_STRU;
    /*******************  发送模块：MTA，接收模块：PHY      End   *******************/

    /*******************  发送模块：MTA，接收模块：RTTAGENT Begin   *******************/
    MTA_AGENT_AFCLOCK_AFCSTATUS_NTF_STRU                    stMTA_AGENT_AFCLOCK_AFCSTATUS_NTF_STRU;
    /*******************  发送模块：MTA，接收模块：RTTAGENT End   *******************/

    /*******************  发送模块：MTA，接收模块：STARTUP  Begin   *******************/
    MTA_UPHY_START_UPHY_REQ_STRU                            stMTA_UPHY_START_UPHY_REQ_STRU;
    /*******************  发送模块：MTA，接收模块：STARTUP  End   *******************/

    /*******************  发送模块：MTA，接收模块：WRR      Begin   *******************/
    MTA_RRC_RESEL_OFFSET_CFG_NTF_STRU                       stMTA_RRC_RESEL_OFFSET_CFG_NTF_STRU;
    MTA_WRR_AUTOTEST_QRY_REQ_STRU                           stMTA_WRR_AUTOTEST_QRY_REQ_STRU;
    MTA_WRR_CELLINFO_QRY_REQ_STRU                           stMTA_WRR_CELLINFO_QRY_REQ_STRU;
    MTA_WRR_MEANRPT_QRY_REQ_STRU                            stMTA_WRR_MEANRPT_QRY_REQ_STRU;
    MTA_WRR_FREQLOCK_SET_REQ_STRU                           stMTA_WRR_FREQLOCK_SET_REQ_STRU;
    MTA_WRR_RRC_VERSION_SET_REQ_STRU                        stMTA_WRR_RRC_VERSION_SET_REQ_STRU;
    MTA_WRR_CELLSRH_SET_REQ_STRU                            stMTA_WRR_CELLSRH_SET_REQ_STRU;
    MTA_WRR_FREQLOCK_QRY_REQ_STRU                           stMTA_WRR_FREQLOCK_QRY_REQ_STRU;
    MTA_WRR_RRC_VERSION_QRY_REQ_STRU                        stMTA_WRR_RRC_VERSION_QRY_REQ_STRU;
    MTA_WRR_CELLSRH_QRY_REQ_STRU                            stMTA_WRR_CELLSRH_QRY_REQ_STRU;
    MTA_RRC_PLMN_FREQ_QRY_REQ_STRU                          stMTA_RRC_PLMN_FREQ_QRY_REQ_STRU;
    MTA_WRR_JAM_DETECT_REQ_STRU                             stMTA_WRR_JAM_DETECT_REQ_STRU;
    /*******************  发送模块：MTA，接收模块：WRR      End   *******************/

    /*******************  发送模块：MTA，接收模块：ERRC     Begin   *******************/
    MTA_LRRC_CELLINFO_QRY_REQ_STRU                          stMTA_LRRC_CELLINFO_QRY_REQ_STRU;
    MTA_RRC_PROTECT_PS_IND_STRU                             stMTA_RRC_PROTECT_PS_IND_STRU;
    MTA_TLRRC_SET_DPDTTEST_FLAG_NTF_STRU                    stMTA_TLRRC_SET_DPDTTEST_FLAG_NTF_STRU;
    MTA_TLRRC_SET_DPDT_VALUE_NTF_STRU                       stMTA_TLRRC_SET_DPDT_VALUE_NTF_STRU;
    MTA_TLRRC_QRY_DPDT_VALUE_REQ_STRU                       stMTA_TLRRC_QRY_DPDT_VALUE_REQ_STRU;
    MTA_LRRC_MBMS_SERVICE_OPTION_REQ_STRU                   stMTA_LRRC_MBMS_SERVICE_OPTION_REQ_STRU;
    MTA_LRRC_MBMS_SERVICE_STATE_SET_REQ_STRU                stMTA_LRRC_MBMS_SERVICE_STATE_SET_REQ_STRU;
    MTA_LRRC_MBMS_AVL_SERVICE_LIST_QRY_REQ_STRU             stMTA_LRRC_MBMS_AVL_SERVICE_LIST_QRY_REQ_STRU;
    MTA_LRRC_MBMS_PREFERENCE_SET_REQ_STRU                   stMTA_LRRC_MBMS_PREFERENCE_SET_REQ_STRU;
    MTA_LRRC_SIB16_NETWORK_TIME_QRY_REQ_STRU                stMTA_LRRC_SIB16_NETWORK_TIME_QRY_REQ_STRU;
    MTA_LRRC_BSSI_SIGNAL_LEVEL_QRY_REQ_STRU                 stMTA_LRRC_BSSI_SIGNAL_LEVEL_QRY_REQ_STRU;
    MTA_LRRC_NETWORK_INFO_QRY_REQ_STRU                      stMTA_LRRC_NETWORK_INFO_QRY_REQ_STRU;
    MTA_LRRC_EMBMS_STATUS_QRY_REQ_STRU                      stMTA_LRRC_EMBMS_STATUS_QRY_REQ_STRU;
    MTA_LRRC_MBMS_UNSOLICITED_CFG_SET_REQ_STRU              stMTA_LRRC_MBMS_UNSOLICITED_CFG_SET_REQ_STRU;
    MTA_LRRC_LTE_WIFI_COEX_SET_REQ_STRU                     stMTA_LRRC_LTE_WIFI_COEX_SET_REQ_STRU;
    MTA_LRRC_LOW_POWER_CONSUMPTION_SET_REQ_STRU             stMTA_LRRC_LOW_POWER_CONSUMPTION_SET_REQ_STRU;
    MTA_LRRC_INTEREST_LIST_SET_REQ_STRU                     stMTA_LRRC_INTEREST_LIST_SET_REQ_STRU;
    MTA_LRRC_TRANSMODE_QRY_REQ_STRU                         stMTA_LRRC_TRANSMODE_QRY_REQ_STRU;
    MTA_LRRC_SET_FR_REQ_STRU                                stMTA_LRRC_SET_FR_REQ_STRU;
    /*******************  发送模块：MTA，接收模块：ERRC     End   *******************/

    /*******************  发送模块：MTA，接收模块：APM      Begin   *******************/
    MTA_APM_BODY_SAR_SET_REQ_STRU                           stMTA_APM_BODY_SAR_SET_REQ_STRU;
    MTA_PHY_EMERGENCY_CALL_STATUS_NOTIFY_STRU               stMTA_PHY_EMERGENCY_CALL_STATUS_NOTIFY_STRU;
    /*******************  发送模块：MTA，接收模块：APM      End   *******************/

    /*******************  发送模块：MTA，接收模块：DIAG_APP_AGENT  Begin ******************/
    OM_NAS_ELF_ERR_LOG_REPORT_CNF_STRU                      stOM_NAS_ELF_ERR_LOG_REPORT_CNF_STRU;
    OM_NAS_ELF_FTM_REPROT_IND_STRU                          stOM_NAS_ELF_FTM_REPROT_IND_STRU;
    NAS_ELF_ERR_LOG_ALM_MNTN_STRU                           stNAS_ELF_ERR_LOG_ALM_MNTN_STRU;
    /*******************  发送模块：MTA，接收模块：DIAG_APP_AGENT  End ******************/

    /*******************  发送模块：MTA，接收模块：RRM      Begin   *******************/
    PS_RRM_PROTECT_PS_IND_STRU                              stPS_RRM_PROTECT_PS_IND_STRU;
    PS_RRM_DEPROTECT_PS_IND_STRU                            stPS_RRM_DEPROTECT_PS_IND_STRU;
    /*******************  发送模块：MTA，接收模块：RRM      End   *******************/

    /*******************  发送模块：MTA，接收模块：MTC      Begin   *******************/
    MTA_MTC_RESERVE_STRU                                    stMTA_MTC_RESERVE_STRU;
    /*******************  发送模块：MTA，接收模块：MTC      End   *******************/

    /*******************  发送模块：MTA，接收模块：TIMER    Begin   *******************/
    TAF_MTA_TIMER_INFO_STRU                                 stTAF_MTA_TIMER_INFO_STRU;
    /*******************  发送模块：MTA，接收模块：TIMER    End   *******************/
}

/*****************************************************************************
 函 数 名  : ELF_TAF_STRU_TraceTable_MTC
 功能描述  : TraceTable中MTC的消息结构
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月16日
    作    者   : h0360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_STRU_TraceTable_MTC(void)
{
    /*******************  发送模块：MTC，接收模块：MMA      Begin   *******************/
    MTC_MMA_OTHER_MODEM_INFO_NOTIFY_STRU                    stMTC_MMA_OTHER_MODEM_INFO_NOTIFY_STRU;
    MTC_MMA_NCELL_INFO_IND_STRU                             stMTC_MMA_NCELL_INFO_IND_STRU;
    MTC_MMA_PS_TRANSFER_IND_STRU                            stMTC_MMA_PS_TRANSFER_IND_STRU;
    MTC_MMA_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU        stMTC_MMA_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU;
    /*******************  发送模块：MTC，接收模块：MMA      End   *******************/

    /*******************  发送模块：MTC，接收模块：TPS_PID_RRC Begin   *******************/
    MTC_RRC_INTRUSION_ACTION_SET_REQ_STRU                   stMTC_RRC_INTRUSION_ACTION_SET_REQ_STRU;
    MTC_RRC_INTRUSION_BAND_SET_REQ_STRU                     stMTC_RRC_INTRUSION_BAND_SET_REQ_STRU;
    MTC_RRC_NOTCH_CHANNEL_IND_STRU                          stMTC_RRC_NOTCH_CHANNEL_IND_STRU;
    MTC_RRC_GSM_CELL_INFO_IND_STRU                          stMTC_RRC_GSM_CELL_INFO_IND_STRU;
    /*******************  发送模块：MTC，接收模块：TPS_PID_RRC End   *******************/

    /*******************  发送模块：MTC，接收模块：GMM      Begin   *******************/
    MTC_GMM_RRC_AREA_LOST_IND_STRU                          stMTC_GMM_RRC_AREA_LOST_IND_STRU;
    /*******************  发送模块：MTC，接收模块：GMM      End   *******************/

    /*******************  发送模块：MTC，接收模块：MTA      Begin   *******************/
    MTC_MTA_PS_TRANSFER_IND_STRU                            stMTC_MTA_PS_TRANSFER_IND_STRU;
    MTC_MTA_MIPICLK_INFO_IND_STRU                           stMTC_MTA_MIPICLK_INFO_IND_STRU;
    MTC_MTA_GSM_CELLINFO_QRY_CNF_STRU                       stMTC_MTA_GSM_CELLINFO_QRY_CNF_STRU;
    /*******************  发送模块：MTC，接收模块：MTA      End   *******************/

    /*******************  发送模块：MTC，接收模块：MTC      Begin   *******************/
    MTC_CONTEXT_DEBUG_STRU                                  stMTC_CONTEXT_DEBUG_STRU;
    MTC_DEBUG_RF_USING_FREQ_LIST_STRU                       stMTC_DEBUG_RF_USING_FREQ_LIST_STRU;
    MTC_DEBUG_ALL_MODEM_STATE_INFO                          stMTC_DEBUG_ALL_MODEM_STATE_INFO;
    TAF_ELF_MTC_CDMA_STATE_IND_STRU                         stTAF_ELF_MTC_CDMA_STATE_IND_STRU;
    TAF_ELF_MTC_MODEM_CONN_STATUS_IND_STRU                  stTAF_ELF_MTC_MODEM_CONN_STATUS_IND_STRU;
    TAF_ELF_MTC_USIMM_STATUS_IND_STRU                       stTAF_ELF_MTC_USIMM_STATUS_IND_STRU;
    MTC_ELF_BEGIN_SESSION_IND_STRU                          stMTC_ELF_BEGIN_SESSION_IND_STRU;
    MTC_ELF_END_SESSION_IND_STRU                            stMTC_ELF_END_SESSION_IND_STRU;
    /*******************  发送模块：MTC，接收模块：MTC      End   *******************/

    /*******************  发送模块：MTC，接收模块：RCM      Begin   *******************/
    MTC_RCM_MODEM_STATE_NOTIFY_STRU                         stMTC_RCM_MODEM_STATE_NOTIFY_STRU;
    MTC_RCM_TC_STATUS_NOTIFY_STRU                           stMTC_RCM_TC_STATUS_NOTIFY_STRU;
    /*******************  发送模块：MTC，接收模块：RCM      Begin   *******************/
}


/*****************************************************************************
 函 数 名  : ELF_TAF_STRU_TraceTable_GAS
 功能描述  : TraceTable中的GAS的消息结构
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月14日
    作    者   : h0360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_STRU_TraceTable_GAS(void)
{
    /*******************  发送模块：GAS，接收模块：MTA      Begin   *******************/
    MTA_RRC_POSITION_REQ_STRU                               stMTA_RRC_POSITION_REQ_STRU;
    RRC_ELF_MTA_QRY_NMR_CNF_STRU                            stRRC_ELF_MTA_QRY_NMR_CNF_STRU;
    GRR_MTA_NCELL_MONITOR_SET_CNF_STRU                      stGRR_MTA_NCELL_MONITOR_SET_CNF_STRU;
    GRR_MTA_NCELL_MONITOR_QRY_CNF_STRU                      stGRR_MTA_NCELL_MONITOR_QRY_CNF_STRU;
    GRR_MTA_NCELL_MONITOR_IND_STRU                          stGRR_MTA_NCELL_MONITOR_IND_STRU;
    GRR_MTA_FREQLOCK_SET_CNF_STRU                           stGRR_MTA_FREQLOCK_SET_CNF_STRU;
    RRC_ELF_MTA_PLMN_FREQ_QRY_CNF_STRU                      stRRC_ELF_MTA_PLMN_FREQ_QRY_CNF_STRU;
    /*******************  发送模块：GAS，接收模块：MTA      End   *******************/

    /*******************  发送模块：GAS，接收模块：MTC      Begin  *******************/
    RRC_MTC_NCELL_INFO_IND_STRU                             stRRC_MTC_NCELL_INFO_IND_STRU;
    /*******************  发送模块：GAS，接收模块：MTC      End  *******************/
}

/*****************************************************************************
 函 数 名  : ELF_TAF_STRU_TraceTable_WCOM
 功能描述  : TraceTable中的WCOM的消息结构
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月14日
    作    者   : h0360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_STRU_TraceTable_WCOM(void)
{
    /*******************  发送模块：WCOM，接收模块：MTA     Begin   *******************/
    MTA_RRC_POSITION_REQ_STRU                               stMTA_RRC_POSITION_REQ_STRU;
    /*******************  发送模块：WCOM，接收模块：MTA     End   *******************/
}

/*****************************************************************************
 函 数 名  : ELF_TAF_STRU_TraceTable_GPHY
 功能描述  : TraceTable中的PHY的结构
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月14日
    作    者   : h0360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_STRU_TraceTable_PHY(void)
{
    /*******************  发送模块：PHY，接收模块：MTA     Begin   *******************/
    GUPHY_MTA_QRY_DPDT_VALUE_CNF_STRU                       stGUPHY_MTA_QRY_DPDT_VALUE_CNF_STRU;
    MTA_PHY_SET_GPS_RF_CLOCK_CNF_STRU                       stMTA_PHY_SET_GPS_RF_CLOCK_CNF_STRU;
    GPHY_MTA_XPASS_INFO_IND_STRU                            stGPHY_MTA_XPASS_INFO_IND_STRU;
    /*******************  发送模块：PHY，接收模块：MTA     End   *******************/
}

/*****************************************************************************
 函 数 名  : ELF_TAF_STRU_TraceTable_STARTUP
 功能描述  : TraceTable中的STARTUP的结构
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月14日
    作    者   : h0360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_STRU_TraceTable_STARTUP(void)
{
    /*******************  发送模块：STARTUP，接收模块：MTA  Begin   *******************/
    UPHY_MTA_START_UPHY_CNF_STRU                            stUPHY_MTA_START_UPHY_CNF_STRU;
    /*******************  发送模块：STARTUP，接收模块：MTA  End   *******************/
}

/*****************************************************************************
 函 数 名  : ELF_TAF_STRU_TraceTable_WRR
 功能描述  : TraceTable中的WRR的结构
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月14日
    作    者   : h0360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_STRU_TraceTable_WRR(void)
{
    /*******************  发送模块：STARTUP，接收模块：MTA  Begin   *******************/
    WRR_MTA_AUTOTEST_QRY_CNF_STRU                           stWRR_MTA_AUTOTEST_QRY_CNF_STRU;
    WRR_MTA_CELLINFO_QRY_CNF_STRU                           stWRR_MTA_CELLINFO_QRY_CNF_STRU;
    WRR_MTA_MEANRPT_QRY_CNF_STRU                            stWRR_MTA_MEANRPT_QRY_CNF_STRU;
    WRR_MTA_FREQLOCK_SET_CNF_STRU                           stWRR_MTA_FREQLOCK_SET_CNF_STRU;
    WRR_MTA_RRC_VERSION_SET_CNF_STRU                        stWRR_MTA_RRC_VERSION_SET_CNF_STRU;
    WRR_MTA_CELLSRH_SET_CNF_STRU                            stWRR_MTA_CELLSRH_SET_CNF_STRU;
    WRR_MTA_FREQLOCK_QRY_CNF_STRU                           stWRR_MTA_FREQLOCK_QRY_CNF_STRU;
    WRR_MTA_RRC_VERSION_QRY_CNF_STRU                        stWRR_MTA_RRC_VERSION_QRY_CNF_STRU;
    WRR_MTA_CELLSRH_QRY_CNF_STRU                            stWRR_MTA_CELLSRH_QRY_CNF_STRU;
    /*******************  发送模块：STARTUP，接收模块：MTA  End   *******************/
}


/*****************************************************************************
 函 数 名  : ELF_TAF_STRU_TraceTable_ERRC
 功能描述  : TraceTable中的ERRC的结构
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月14日
    作    者   : h0360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_STRU_TraceTable_ERRC(void)
{
    /*******************  发送模块：ERRC，接收模块：MTA     Begin   *******************/
    LRRC_MTA_CELLINFO_QRY_CNF_STRU                          stLRRC_MTA_CELLINFO_QRY_CNF_STRU;
    TLRRC_MTA_QRY_DPDT_VALUE_CNF_STRU                       stTLRRC_MTA_QRY_DPDT_VALUE_CNF_STRU;
    LRRC_MTA_MBMS_SERVICE_OPTION_CNF_STRU                   stLRRC_MTA_MBMS_SERVICE_OPTION_CNF_STRU;
    LRRC_MTA_MBMS_SERVICE_STATE_SET_CNF_STRU                stLRRC_MTA_MBMS_SERVICE_STATE_SET_CNF_STRU;
    LRRC_MTA_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU             stLRRC_MTA_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU;
    LRRC_MTA_MBMS_PREFERENCE_SET_CNF_STRU                   stLRRC_MTA_MBMS_PREFERENCE_SET_CNF_STRU;
    LRRC_MTA_SIB16_NETWORK_TIME_QRY_CNF_STRU                stLRRC_MTA_SIB16_NETWORK_TIME_QRY_CNF_STRU;
    LRRC_MTA_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU                 stLRRC_MTA_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU;
    LRRC_MTA_NETWORK_INFO_QRY_CNF_STRU                      stLRRC_MTA_NETWORK_INFO_QRY_CNF_STRU;
    LRRC_MTA_EMBMS_STATUS_QRY_CNF_STRU                      stLRRC_MTA_EMBMS_STATUS_QRY_CNF_STRU;
    LRRC_MTA_MBMS_UNSOLICITED_CFG_SET_CNF_STRU              stLRRC_MTA_MBMS_UNSOLICITED_CFG_SET_CNF_STRU;
    LRRC_MTA_MBMS_SERVICE_EVENT_IND_STRU                    stLRRC_MTA_MBMS_SERVICE_EVENT_IND_STRU;
    LRRC_MTA_LTE_WIFI_COEX_SET_CNF_STRU                     stLRRC_MTA_LTE_WIFI_COEX_SET_CNF_STRU;
    LRRC_MTA_LOW_POWER_CONSUMPTION_SET_CNF_STRU             stLRRC_MTA_LOW_POWER_CONSUMPTION_SET_CNF_STRU;
    LRRC_MTA_INTEREST_LIST_SET_CNF_STRU                     stLRRC_MTA_INTEREST_LIST_SET_CNF_STRU;
    LRRC_MTA_SET_FR_CNF_STRU                                stLRRC_MTA_SET_FR_CNF_STRU;
    LRRC_MTA_TRANSMODE_QRY_CNF_STRU                         stLRRC_MTA_TRANSMODE_QRY_CNF_STRU;
    /*******************  发送模块：ERRC，接收模块：MTA     End   *******************/
}

/*****************************************************************************
 函 数 名  : ELF_TAF_STRU_TraceTable_APM
 功能描述  : TraceTable中的APM的结构
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月14日
    作    者   : h0360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_STRU_TraceTable_APM(void)
{
    /*******************  发送模块：APM，接收模块：MTA      Begin   *******************/
    APM_MTA_BODY_SAR_SET_CNF_STRU                           stAPM_MTA_BODY_SAR_SET_CNF_STRU;
    APM_MTA_REFCLOCK_STATUS_IND_STRU                        stAPM_MTA_REFCLOCK_STATUS_IND_STRU;
    /*******************  发送模块：APM，接收模块：MTA      End   *******************/
}

/*****************************************************************************
 函 数 名  : ELF_TAF_STRU_TraceTable_TC
 功能描述  : TraceTable中的TC的结构
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月17日
    作    者   : h0360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_STRU_TraceTable_TC(void)
{
    /*******************  发送模块：TC，接收模块：MTC       Begin   *******************/
    NAS_MTC_TC_STATUS_INFO_IND_STRU                         stNAS_MTC_TC_STATUS_INFO_IND_STRU;
    /*******************  发送模块：TC，接收模块：MTC       End   *******************/
}

/*****************************************************************************
 函 数 名  : ELF_TAF_STRU_TraceTable_DIAG_APP_AGENT
 功能描述  : TraceTable中的DIAG_APP_AGENT的结构
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月14日
    作    者   : h0360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_STRU_TraceTable_DIAG_APP_AGENT(void)
{
    /*******************  发送模块：DIAG_APP_AGENT，接收模块：MTA      Begin   *******************/
    OM_NAS_ELF_ERROR_LOG_CTRL_IND_STRU                      stOM_NAS_ELF_ERROR_LOG_CTRL_IND_STRU;
    OM_NAS_ELF_ERR_LOG_REPORT_REQ_STRU                      stOM_NAS_ELF_ERR_LOG_REPORT_REQ_STRU;
    OM_NAS_ELF_FTM_CTRL_IND_STRU                            stOM_NAS_ELF_FTM_CTRL_IND_STRU;
    OM_NAS_ELF_INFO_CLT_REPORT_REQ_STRU                     stOM_NAS_ELF_INFO_CLT_REPORT_REQ_STRU;
    OM_NAS_ELF_INFO_CLT_REPORT_CNF_STRU                     stOM_NAS_ELF_INFO_CLT_REPORT_CNF_STRU;
    /*******************  发送模块：DIAG_APP_AGENT，接收模块：MTA      End   *******************/
}

/*****************************************************************************
 函 数 名  : ELF_TAF_STRU_TraceTable_TPS_PID_RRC
 功能描述  : TraceTable中的DIAG_APP_AGENT的结构
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月14日
    作    者   : h0360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_STRU_TraceTable_TPS_PID_RRC(void)
{
    /*******************  发送模块：TPS_PID_RRC，接收模块：MTC     Begin   *******************/
    RRC_MTC_RESULT_CNF_STRU                                 stRRC_MTC_RESULT_CNF_STRU;
    RRC_MTC_INTRUSION_BAND_INFO_IND_STRU                    stRRC_MTC_INTRUSION_BAND_INFO_IND_STRU;
    RRC_MTC_AREA_LOST_IND_STRU                              stRRC_MTC_AREA_LOST_IND_STRU;
    RRC_MTC_AREA_AVALIABLE_IND_STRU                         stRRC_MTC_AREA_AVALIABLE_IND_STRU;
    RRC_MTC_USING_FREQ_IND_STRU                             stRRC_MTC_USING_FREQ_IND_STRU;
    /*******************  发送模块：TPS_PID_RRC，接收模块：MTC     End   *******************/
}

/*****************************************************************************
 函 数 名  : ELF_TAF_STRU_TraceTable_OTA
 功能描述  : 开关消息结构
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月14日
    作    者   : h0360002
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_STRU_TraceTable_OTA(void)
{
    OM_NAS_OTA_REQ_STRUCT                                   stOM_NAS_OTA_REQ_STRUCT;
    NAS_OM_OTA_CNF_STRUCT                                   stNAS_OM_OTA_CNF_STRUCT;
    NAS_OM_OTA_IND_STRUCT                                   stNAS_OM_OTA_IND_STRUCT;

    ID_NAS_OM_INQUIRE_STRU                                  stID_NAS_OM_INQUIRE_STRU;
    NAS_OM_MM_IND_STRU                                      stNAS_OM_MM_IND_STRU;
    NAS_QOS_IND_STRUCT                                      stNAS_QOS_IND_STRUCT;
    NAS_OM_PDP_CONTEXT_IND_STRU                             stNAS_OM_PDP_CONTEXT_IND_STRU;
    NAS_OM_SET_GSM_CODEC_CONFIG_REQ_STRU                    stNAS_OM_SET_GSM_CODEC_CONFIG_REQ_STRU;
    NAS_OM_SET_GSM_CODEC_CONFIG_CNF_STRU                    stNAS_OM_SET_GSM_CODEC_CONFIG_CNF_STRU;
    NAS_OM_CODEC_TYPE_CNF_STRU                              stNAS_OM_CODEC_TYPE_CNF_STRU;
    NAS_OM_SET_DSFLOW_RPT_REQ_STRU                          stNAS_OM_SET_DSFLOW_RPT_REQ_STRU;
    NAS_OM_SET_DSFLOW_RPT_CNF_STRU                          stNAS_OM_SET_DSFLOW_RPT_CNF_STRU;
    NAS_OM_SMS_IND_STRU                                     stNAS_OM_SMS_IND_STRU;
    NAS_OM_CONFIG_TIMER_REPORT_REQ_STRU                     stNAS_OM_CONFIG_TIMER_REPORT_REQ_STRU;
    NAS_OM_CONFIG_TIMER_REPORT_CNF_STRU                     stNAS_OM_CONFIG_TIMER_REPORT_CNF_STRU;
    OM_NAS_MMA_CDMA_STATUS_INFO_REPORT_REQ_STRU             stOM_NAS_MMA_CDMA_STATUS_INFO_REPORT_REQ_STRU;
    NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_CNF_STRU             stNAS_OM_MMA_CDMA_STATUS_INFO_REPORT_CNF_STRU;
    NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_IND_STRU             stNAS_OM_MMA_CDMA_STATUS_INFO_REPORT_IND_STRU;
}

/*****************************************************************************
 函 数 名  : ELF_TAF_STRU_TraceTable
 功能描述  : TraceTable中定义的消息结构
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_TAF_STRU_TraceTable(void)
{
    ELF_TAF_STRU_TraceTable_MMA();

    ELF_TAF_STRU_TraceTable_TAF();

    ELF_TAF_STRU_TraceTable_AT();

    ELF_TAF_STRU_TraceTable_MTA();

    ELF_TAF_STRU_TraceTable_GAS();

    ELF_TAF_STRU_TraceTable_WCOM();

    ELF_TAF_STRU_TraceTable_OTA();
}

void ELF_TAF_MAIN()
{
    /*****************************************************************************
    ##############################  枚举定义 Begin  ##############################
    *****************************************************************************/
    ELF_TAF_ENUM_LIST();
    /*****************************************************************************
    ##############################   枚举定义 End   ##############################
    *****************************************************************************/

    /*****************************************************************************
    #############################  结构体定义 Begin  #############################
    *****************************************************************************/
    ELF_TAF_STRU_TraceTable();
    /*****************************************************************************
    #############################   结构体定义 End   #############################
    *****************************************************************************/

}


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
