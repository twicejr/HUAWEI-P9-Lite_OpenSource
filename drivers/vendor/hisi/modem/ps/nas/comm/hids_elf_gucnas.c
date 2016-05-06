/*******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : hids_elf_gucnas.c
  版 本 号   : 初稿
  作    者   : l00301449
  生成日期   : 2015年11月06日
  功能描述   : NAS的elf文件
  函数列表   :
  修改历史   :
  1.日    期   : 2016年11月06日
    作    者   : l00301449
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsRrmInterface.h"
#include "UsimPsInterface.h"
#include "MsccMmcInterface.h"
#include "MmaMsccInterface.h"

#include "MmcLmmInterface.h"

#include "xsd_mscc_pif.h"
#include "xsd_xreg_pif.h"
#include "xsd_xcc_pif.h"
#include "xcc_xcall_pif.h"
#include "xcc_aps_pif.h"
#include "xcc_sms_pif.h"
#include "hsm_aps_pif.h"
#include "hsm_hsd_pif.h"
#include "hsm_mma_pif.h"
#include "hsm_hlu_pif.h"
#include "hsd_hlu_pif.h"
#include "ehsm_hsd_pif.h"
#include "hsd_mscc_pif.h"
#include "ehsm_esm_pif.h"

#include "CnasMntn.h"
#include "CnasTimerMgmt.h"

#include "CnasXsdTimer.h"
#include "CnasXsdMntn.h"
#include "CnasPrlMntn.h"
#include "CnasXsdSndInternalMsg.h"
#include "CnasXsdFsmMainTbl.h"
#include "CnasXsdFsmSwitchOnTbl.h"
#include "CnasXsdFsmPowerOffTbl.h"
#include "CnasXsdFsmSysAcqTbl.h"
#include "CnasXsdFsmRedirTbl.h"

#include "CnasXccTimer.h"
#include "CnasXccSndInternalMsg.h"
#include "CnasXccFsmMainTbl.h"
#include "CnasXccFsmMoCallingTbl.h"
#include "CnasXccFsmMtCallingTbl.h"

#include "CnasHsmSndInternalMsg.h"
#include "CnasHsmMntn.h"
#include "CnasHsmTimer.h"

#include "CnasHluComm.h"

#include "NasMsccMntn.h"
#include "NasMsccSndInternalMsg.h"
#include "NasMsccFsmSwitchOnTbl.h"
#include "NasMsccFsmSysAcqTbl.h"
#include "NasDynLoadMntn.h"

#include "CnasEhsmCtx.h"
#include "CnasEhsmMntn.h"
#include "CnasEhsmFsmMainTbl.h"
#include "CnasEhsmFsmActivatingTbl.h"
#include "CnasEhsmFsmDeactivatingTbl.h"
#include "CnasEhsmSndInternalMsg.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/*****************************************************************************
 结构名    : CNAS_MNTN_ELF_LOG_XSD_TIMER_INFO_IND_STRU
 结构说明  : ID_CNAS_MNTN_LOG_TIMER_INFO_IND的消息结构(XSD)
 1.日    期   : 2015年11月09日
   作    者   : l00301449
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    CNAS_MNTN_MSG_ID_ENUM_UINT32        enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT32                          ulModuleId;                             /* Module Id */
    CNAS_XSD_TIMER_ID_ENUM_UINT32       enTimerId;                              /* timer ID */
    VOS_UINT32                          ulParam;                                /* timer ID对应的交易标识 */
    VOS_UINT32                          ulTimerLen;                             /* timer 时长 */
    CNAS_MNTN_TIMER_ACTION_ENUM_UINT32  enTimerAct;                             /* timer 状态: start or stop */
}CNAS_MNTN_ELF_LOG_XSD_TIMER_INFO_IND_STRU;


/*****************************************************************************
 结构名    : CNAS_MNTN_ELF_LOG_XCC_TIMER_INFO_IND_STRU
 结构说明  : ID_CNAS_MNTN_LOG_TIMER_INFO_IND的消息结构(XCC)
 1.日    期   : 2015年11月09日
   作    者   : l00301449
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    CNAS_MNTN_MSG_ID_ENUM_UINT32        enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT32                          ulModuleId;                             /* Module Id */
    CNAS_XCC_TIMER_ID_ENUM_UINT32       enTimerId;                              /* timer ID */
    VOS_UINT32                          ulParam;                                /* timer ID对应的交易标识 */
    VOS_UINT32                          ulTimerLen;                             /* timer 时长 */
    CNAS_MNTN_TIMER_ACTION_ENUM_UINT32  enTimerAct;                             /* timer 状态: start or stop */
}CNAS_MNTN_ELF_LOG_XCC_TIMER_INFO_IND_STRU;

/*****************************************************************************
 结构名    : CNAS_MNTN_ELF_LOG_HSM_TIMER_INFO_IND_STRU
 结构说明  : ID_CNAS_MNTN_LOG_TIMER_INFO_IND的消息结构(HSM)
 1.日    期   : 2015年11月10日
   作    者   : w00351686
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    CNAS_MNTN_MSG_ID_ENUM_UINT32        enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT32                          ulModuleId;                             /* Module Id */
    CNAS_HSM_TIMER_ID_ENUM_UINT32       enTimerId;                              /* timer ID */
    VOS_UINT32                          ulParam;                                /* timer ID对应的交易标识 */
    VOS_UINT32                          ulTimerLen;                             /* timer 时长 */
    CNAS_MNTN_TIMER_ACTION_ENUM_UINT32  enTimerAct;                             /* timer 状态: start or stop */
}CNAS_MNTN_ELF_LOG_HSM_TIMER_INFO_IND_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_MNTN_ELF_LOG_TIMER_INFO_STRU
 结构说明  : MSCC发给定时器的消息结构(MSCC)
 1.日    期   : 2015年12月10日
   作    者   : w00351686
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头*/ /*_H2ASN_Skip*/
    NAS_MSCC_TIMER_ID_ENUM_UINT32       enMsgName;
    NAS_MSCC_TIMER_STATUS_ENUM_UINT8    enTimerStatus;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulLen;                                  /* 定时器时长 */
}NAS_MSCC_MNTN_ELF_LOG_TIMER_INFO_STRU;


/*****************************************************************************
 结构名    : CNAS_MNTN_ELF_LOG_XSD_FSM_INFO_STRU
 结构说明  : ID_CNAS_MNTN_LOG_FSM_INFO_IND的消息结构(XSD)
 1.日    期   : 2015年11月09日
   作    者   : l00301449
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    CNAS_MNTN_MSG_ID_ENUM_UINT32                            enMsgId;            /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT32                                              ulModuleId;         /* Module Id */
    CNAS_XSD_FSM_ID_ENUM_UINT32                             enFsmId;
    union
    {
        CNAS_XSD_L1_STA_ENUM_UINT32                         enL1State;
        CNAS_XSD_SWITCH_ON_STA_ENUM_UINT32                  enSwithcOnState;
        CNAS_XSD_POWER_OFF_STA_ENUM_UINT32                  enPowerOffState;
        CNAS_XSD_SYS_ACQ_STA_ENUM_UINT32                    enSysAcqState;
        CNAS_XSD_REDIR_STA_ENUM_UINT32                      enRedir;
    }uCurFsmState;
    VOS_UINT8                                               ucConnectId;
    VOS_UINT8                                               aucReserved[3];
}CNAS_MNTN_ELF_LOG_XSD_FSM_INFO_STRU;


/*****************************************************************************
 结构名    : CNAS_MNTN_ELF_LOG_XCC_FSM_INFO_STRU
 结构说明  : ID_CNAS_MNTN_LOG_FSM_INFO_IND的消息结构(XCC)
 1.日    期   : 2015年11月09日
   作    者   : l00301449
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    CNAS_MNTN_MSG_ID_ENUM_UINT32                            enMsgId;            /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT32                                              ulModuleId;         /* Module Id */
    CNAS_XCC_FSM_ID_ENUM_UINT32                             enFsmId;
    union
    {
        CNAS_XCC_L1_STA_ENUM_UINT32                         enL1State;
        CNAS_XCC_MO_CALLING_STA_ENUM_UINT32                 enMoCallingState;
        CNAS_XCC_MT_CALLING_STA_ENUM_UINT32                 enMtCallingState;
    }uCurFsmState;
    VOS_UINT8                                               ucConnectId;
    VOS_UINT8                                               aucReserved[3];
}CNAS_MNTN_ELF_LOG_XCC_FSM_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_EHSM_ELF_TIMER_INFO_STRU
 结构说明  : EHSM发给定时器的消息结构(EHSM)
 1.日    期   : 2015年11月09日
   作    者   : l00301449
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CNAS_EHSM_TIMER_ID_ENUM_UINT32      enTimerId;
    CNAS_EHSM_TIMER_STATUS_ENUM_UINT8   enTimerStatus;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulLen;                                  /* 定时器时长 */
}CNAS_EHSM_ELF_TIMER_INFO_STRU;


/*****************************************************************************
 结构名    : CNAS_EHSM_MNTN_ELF_LOG_FSM_INFO_STRU
 结构说明  : ID_CNAS_EHSM_MNTN_LOG_FSM_INFO_IND的消息结构对应代码的CNAS_EHSM_MNTN_LOG_FSM_INFO_STRU结构
 1.日    期   : 2015年11月09日
   作    者   : l00301449
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_EHSM_MNTN_MSG_ID_ENUM_UINT32                       enMsgId;            /* _H2ASN_Skip */
    CNAS_EHSM_FSM_ID_ENUM_UINT32                            enFsmId;
    union
    {
        CNAS_EHSM_L1_STA_ENUM_UINT32                        enL1State;
        CNAS_EHSM_ACTIVATING_STA_ENUM_UINT32                enActingState;
        CNAS_EHSM_DEACTIVATING_STA_ENUM_UINT32              enDeactingState;
    }uCurFsmState;

}CNAS_EHSM_MNTN_ELF_LOG_FSM_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_HSM_MNTN_ELF_LOG_SUB_FSM_INFO_STRU
 结构说明  : HSM主状态机打印消息对应的消息结构
 1.日    期   : 2015年11月11日
   作    者   : w00351686
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32                        enMsgId;            /* _H2ASN_Skip */
    CNAS_HSM_L1_STA_ENUM_UINT32                             enOldState;
    CNAS_HSM_L1_STA_ENUM_UINT32                             enNewState;
}CNAS_HSM_MNTN_ELF_LOG_MAIN_FSM_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_HSM_MNTN_ELF_LOG_FSM_INFO_STRU
 结构说明  : HSM子状态机打印消息对应的消息结构
 1.日    期   : 2015年11月11日
   作    者   : w00351686
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32                        enMsgId;            /* _H2ASN_Skip */
    CNAS_HSM_SS_ID_ENUM_UINT32                              enOldState;
    CNAS_HSM_SS_ID_ENUM_UINT32                              enNewState;
}CNAS_HSM_MNTN_ELF_LOG_SUB_FSM_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_MNTN_ELF_LOG_FSM_INFO_STRU
 结构说明  : MSCC状态机打印消息对应的消息结构
 1.日    期   : 2015年11月11日
   作    者   : w00351686
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    NAS_MSCC_MNTN_MSG_ID_ENUM_UINT32                        enMsgId;            /* _H2ASN_Skip */
    NAS_MSCC_FSM_ID_ENUM_UINT32                             enFsmId;
    union
    {
        NAS_MSCC_SWITCH_ON_STA_ENUM_UINT32                  enSwitchOnState;
        NAS_MSCC_SYSACQ_STA_ENUM_UINT32                     enSysAcqState;
    }uCurFsmState;

}NAS_MSCC_MNTN_ELF_LOG_FSM_INFO_STRU;

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_COMMON
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
void ELF_NAS_ENUM_COMMON(void)
{
    enum PS_BOOL_ENUM                                       enPS_BOOL_ENUM;
    enum PS_RRM_RAT_COMBINED_MODE_ENUM                      enPS_RRM_RAT_COMBINED_MODE_ENUM;

    enum MODEM_ID_ENUM                                      enMODEM_ID_ENUM;

    enum VOS_RATMODE_ENUM                                   enVOS_RATMODE_ENUM;

    /* enum PS_FILE_ID_DEFINE_ENUM                             enPS_FILE_ID_DEFINE_ENUM; */

    enum USIMM_CMDTYPE_REQ_ENUM                             enUSIMM_CMDTYPE_REQ_ENUM;
    enum USIMM_CARDAPP_ENUM                                 enUSIMM_CARDAPP_ENUM;

    enum RRM_PS_TASK_TYPE_ENUM                              enRRM_PS_TASK_TYPE_ENUM;
    enum MTC_PS_TRANSFER_ENUM                               enMTC_PS_TRANSFER_ENUM;

    enum NAS_NVIM_LC_RAT_COMBINED_ENUM                      enNAS_NVIM_LC_RAT_COMBINED_ENUM;

    enum NAS_DYNLOAD_MNTN_MSG_ID_ENUM                       enNAS_DYNLOAD_MNTN_MSG_ID_ENUM;


}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_CNAS_COMMON
 功能描述  : CNAS的公共枚举定义
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
void ELF_NAS_ENUM_CNAS_COMMON(void)
{
    enum CNAS_MNTN_MSG_ID_ENUM                              enCNAS_MNTN_MSG_ID_ENUM;
    enum CNAS_MNTN_TIMER_ACTION_ENUM                        enCNAS_MNTN_TIMER_ACTION_ENUM;

    enum CNAS_CCB_1X_CALL_STATE_ENUM                        enCNAS_CCB_1X_CALL_STATE_ENUM;

}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_CAS_CNAS
 功能描述  : CAS和CNAS之间的枚举定义
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
void ELF_NAS_ENUM_CAS_CNAS(void)
{
    enum CAS_CNAS_1X_CAS_STATE_ENUM                         enCAS_CNAS_1X_CAS_STATE_ENUM;
    enum CAS_CNAS_1X_CAS_SUB_STATE_ENUM                     enCAS_CNAS_1X_CAS_SUB_STATE_ENUM;
    enum CAS_CNAS_1X_TX_TCH_MSG_TYPE_ENUM                   enCAS_CNAS_1X_TX_TCH_MSG_TYPE_ENUM;
    enum CAS_CNAS_1X_RX_TCH_MSG_TYPE_ENUM                   enCAS_CNAS_1X_RX_TCH_MSG_TYPE_ENUM;

}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_TAF_XCC
 功能描述  : TAF与XCC之间的枚举定义
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
void ELF_NAS_ENUM_TAF_XCC(void)
{
    enum TAF_CDMA_SO_TYPE_ENUM                              enTAF_CDMA_SO_TYPE_ENUM;
    enum TAF_XCC_CAUSE_ENUM                                 enTAF_XCC_CAUSE_ENUM;
    enum TAF_XCC_FAIL_LAYER_ENUM                            enTAF_XCC_FAIL_LAYER_ENUM;
    enum TAF_XCC_END_REASON_ENUM                            enTAF_XCC_END_REASON_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_TAF_XCALL_XCC
 功能描述  : TAF(XCALL)与XCC之间的枚举定义
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
void ELF_NAS_ENUM_TAF_XCALL_XCC(void)
{
    enum XCC_XCALL_PIF_MSG_TYPE_ENUM                        enXCC_XCALL_PIF_MSG_TYPE_ENUM;
    enum XCC_XCALL_NUMBER_TYPE_ENUM                         enXCC_XCALL_NUMBER_TYPE_ENUM;
    enum XCC_XCALL_NUMBER_PLAN_ENUM                         enXCC_XCALL_NUMBER_PLAN_ENUM;
    enum XCC_XCALL_SUB_ADDRESS_TYPE_ENUM                    enXCC_XCALL_SUB_ADDRESS_TYPE_ENUM;
    enum XCC_XCALL_SUB_ADDRESS_EO_ENUM                      enXCC_XCALL_SUB_ADDRESS_EO_ENUM;
    enum XCC_XCALL_DISPLAY_TYPE_ENUM                        enXCC_XCALL_DISPLAY_TYPE_ENUM;
    enum XCC_XCALL_DISPLAY_TAG_ENUM                         enXCC_XCALL_DISPLAY_TAG_ENUM;
    enum XCC_XCALL_REDIR_REASON_ENUM                        enXCC_XCALL_REDIR_REASON_ENUM;
    enum XCC_XCALL_NDSS_RESULT_ENUM                         enXCC_XCALL_NDSS_RESULT_ENUM;
    enum XCALL_XCC_CONT_DTMF_SWITCH_ENUM                    enXCALL_XCC_CONT_DTMF_SWITCH_ENUM;
    enum XCC_XCALL_ECC_SERVICE_RESULT_ENUM                  enXCC_XCALL_ECC_SERVICE_RESULT_ENUM;
    enum XCALL_XCC_PRIVACY_MODE_ENUM                        enXCALL_XCC_PRIVACY_MODE_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_TAF_APS_XCC
 功能描述  : TAF(APS)与XCC之间的枚举定义
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
void ELF_NAS_ENUM_TAF_APS_XCC(void)
{
    enum XCC_APS_PIF_MSG_TYPE_ENUM                          enXCC_APS_PIF_MSG_TYPE_ENUM;
    enum XCC_APS_SERVICE_TYPE_ENUM                          enXCC_APS_SERVICE_TYPE_ENUM;
    enum XCC_APS_SO_CTRL_FIELD_ENUM                         enXCC_APS_SO_CTRL_FIELD_ENUM;

}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_TAF_APS_EHSM
 功能描述  : TAF(APS)和EHSM之间的枚举定义
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
void ELF_NAS_ENUM_TAF_APS_EHSM(void)
{
    enum EHSM_APS_PIF_MSG_TYPE_ENUM                         enEHSM_APS_PIF_MSG_TYPE_ENUM;
    enum EHSM_APS_CAUSE_ENUM                                enEHSM_APS_CAUSE_ENUM;
    enum EHSM_APS_PDN_TYPE_ENUM                             enEHSM_APS_PDN_TYPE_ENUM;
    enum EHSM_APS_PDN_OPTION_ENUM                           enEHSM_APS_PDN_OPTION_ENUM;
    enum APS_EHSM_PS_RATTYPE_ENUM                           enAPS_EHSM_PS_RATTYPE_ENUM;

}


/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_TAF_XSMS_XCC
 功能描述  : TAF(XSMS)与XCC之间的枚举定义
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
void ELF_NAS_ENUM_TAF_XSMS_XCC(void)
{
    enum XCC_SMS_PIF_MSG_TYPE_ENUM                          enXCC_SMS_PIF_MSG_TYPE_ENUM;
    enum XCC_CSMS_RESULT_ENUM                               enXCC_CSMS_RESULT_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_TAF_HSM
 功能描述  : TAF和HSM之间的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : w00351686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_NAS_ENUM_TAF_HSM(void)
{
    enum HSM_APS_PIF_MSG_TYPE_ENUM                          enHSM_APS_PIF_MSG_TYPE_ENUM;
    enum HSM_APS_CAUSE_ENUM                                 enHSM_APS_CAUSE_ENUM;

}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_MMA_XCC
 功能描述  : MMA和XCC之间的枚举定义
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
void ELF_NAS_ENUM_MMA_XCC(void)
{
    enum XCC_MMA_PIF_MSG_TYPE_ENUM                          enXCC_MMA_PIF_MSG_TYPE_ENUM;
    enum XCC_MMA_1X_CALL_STATE_ENUM                         enXCC_MMA_1X_CALL_STATE_ENUM;

}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_MMA_MSCC
 功能描述  : MMA和MSCC之间的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : w00351686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_NAS_ENUM_MMA_MSCC(void)
{
    enum MSCC_MMA_ACQ_SYS_TYPE_ENUM                         enMSCC_MMA_ACQ_SYS_TYPE_ENUM;
    enum MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM                enMSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM;
    enum MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_ENUM        enMSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_ENUM;
    enum MSCC_MMA_HRPD_SERVICE_STATUS_ENUM                  enMSCC_MMA_HRPD_SERVICE_STATUS_ENUM;
    enum MSCC_MMA_HRPD_SESSION_RELEASE_TYPE_ENUM            enMSCC_MMA_HRPD_SESSION_RELEASE_TYPE_ENUM;
    enum MSCC_MMA_HRPD_SYS_ACQ_RSLT_ENUM                    enMSCC_MMA_HRPD_SYS_ACQ_RSLT_ENUM;
    enum MSCC_MMA_1X_CAS_P_REV_ENUM                         enMSCC_MMA_1X_CAS_P_REV_ENUM;

    enum MMA_MSCC_HANDSET_INFO_TYPE_ENUM                    enMMA_MSCC_HANDSET_INFO_TYPE_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_XCC_XSD
 功能描述  : XCC和XSD之间的枚举定义
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
void ELF_NAS_ENUM_XCC_XSD(void)
{
    enum XSD_XCC_PIF_MSG_TYPE_ENUM                          enXSD_XCC_PIF_MSG_TYPE_ENUM;
    enum XSD_XCC_NDSS_RESULT_ENUM                           enXSD_XCC_NDSS_RESULT_ENUM;
    enum XCC_XSD_START_RESULT_ENUM                          enXCC_XSD_START_RESULT_ENUM;
    enum XCC_XSD_POWER_OFF_RESULT_ENUM                      enXCC_XSD_POWER_OFF_RESULT_ENUM;
    enum XCC_XSD_POWER_OFF_REASON_ENUM                      enXCC_XSD_POWER_OFF_REASON_ENUM;
    enum XSD_XCC_DEREGISTER_REASON_ENUM                     enXSD_XCC_DEREGISTER_REASON_ENUM;

}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_XSD_XREG
 功能描述  : XSD和XREG之间的枚举定义
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
void ELF_NAS_ENUM_XSD_XREG(void)
{
    enum XSD_XREG_PIF_MSG_TYPE_ENUM                         enXSD_XREG_PIF_MSG_TYPE_ENUM;
    enum XSD_XREG_SERVICE_STATUS_ENUM                       enXSD_XREG_SERVICE_STATUS_ENUM;
    enum XSD_XREG_DEREGISTER_REASON_ENUM                    enXSD_XREG_DEREGISTER_REASON_ENUM;

}


/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_HSM_MMA
 功能描述  : HSM和MMA之间的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : w00351686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_NAS_ENUM_HSM_MMA(void)
{
    enum HSM_MMA_PIF_MSG_TYPE_ENUM                          enHSM_MMA_PIF_MSG_TYPE_ENUM;
    enum HSM_MMA_SESSION_STATUS_ENUM                        enHSM_MMA_SESSION_STATUS_ENUM;

}


/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_HSM_HLU
 功能描述  : HSM和HLU之间的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : w00351686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_NAS_ENUM_HSM_HLU(void)
{
    enum HSM_HLU_PIF_MSG_TYPE_ENUM                          enHSM_HLU_PIF_MSG_TYPE_ENUM;
    enum HSM_HLU_SESSION_RAT_MODE_ENUM                      enHSM_HLU_SESSION_RAT_MODE_ENUM;

}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_HSM_HSD
 功能描述  : HSM和HSD之间的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : w00351686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_NAS_ENUM_HSM_HSD(void)
{
    enum HSM_HSD_PIF_MSG_TYPE_ENUM                          enHSM_HSD_PIF_MSG_TYPE_ENUM;
    enum HSM_HSD_SESSION_NEG_RSLT_ENUM                      enHSM_HSD_SESSION_NEG_RSLT_ENUM;
    enum HSM_HSD_SESSION_RELEASE_TYPE_ENUM                  enHSM_HSD_SESSION_RELEASE_TYPE_ENUM;
    enum HSM_HSD_HRPD_CAS_STATUS_ENUM                       enHSM_HSD_HRPD_CAS_STATUS_ENUM;
    enum HSM_HSD_HRPD_CONN_OPEN_RSLT_ENUM                   enHSM_HSD_HRPD_CONN_OPEN_RSLT_ENUM;

}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_HSD_MSCC
 功能描述  : HSD和MSCC之间的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : w00361686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_NAS_ENUM_HSD_MSCC(void)
{
    enum MSCC_HSD_POWER_OFF_CAUSE_ENUM                      enMSCC_HSD_POWER_OFF_CAUSE_ENUM;
    enum MSCC_HSD_ACQUIRE_REASON_ENUM                       enMSCC_HSD_ACQUIRE_REASON_ENUM;
    enum MSCC_HSD_SYS_TYPE_ENUM                             enMSCC_HSD_SYS_TYPE_ENUM;
    enum MSCC_HSD_PRI_CLASS_ENUM                            enMSCC_HSD_PRI_CLASS_ENUM;

    enum HSD_MSCC_START_RESULT_ENUM                         enHSD_MSCC_START_RESULT_ENUM;
    enum HSD_MSCC_SESSION_NEG_RSLT_ENUM                     enHSD_MSCC_SESSION_NEG_RSLT_ENUM;
    enum HSD_MSCC_SESSION_RELEASE_TYPE_ENUM                 enHSD_MSCC_SESSION_RELEASE_TYPE_ENUM;
    enum HSD_MSCC_HRPD_BSR_RSLT_ENUM                        enHSD_MSCC_HRPD_BSR_RSLT_ENUM;
    enum HSD_MSCC_HRPD_CAS_STATUS_ENUM                      enHSD_MSCC_HRPD_CAS_STATUS_ENUM;

}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_HSD_HLU
 功能描述  : HSD和HLU之间的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月14日
    作    者   : L00301449
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_NAS_ENUM_HSD_HLU(void)
{
    enum HSD_HLU_PIF_MSG_TYPE_ENUM                          enHSD_HLU_PIF_MSG_TYPE_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_EHSM_HSM
 功能描述  : EHSM和HSM之间的枚举定义
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
void ELF_NAS_ENUM_EHSM_HSM(void)
{
    enum EHSM_HSM_PIF_MSG_TYPE_ENUM                         enEHSM_HSM_PIF_MSG_TYPE_ENUM;
    enum EHSM_HSM_RSLT_ENUM                                 enEHSM_HSM_RSLT_ENUM;
    enum EHSM_HSM_SESSION_TYPE_ENUM                         enEHSM_HSM_SESSION_TYPE_ENUM;

}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_EHSM_HSD
 功能描述  : EHSM和HSD之间的枚举定义
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
void ELF_NAS_ENUM_EHSM_HSD(void)
{
    enum EHSM_HSD_PIF_MSG_TYPE_ENUM                         enEHSM_HSD_PIF_MSG_TYPE_ENUM;
    enum EHSM_HSD_START_RESULT_ENUM                         enEHSM_HSD_START_RESULT_ENUM;
    enum EHSM_HSD_POWER_OFF_CAUSE_ENUM                      enEHSM_HSD_POWER_OFF_CAUSE_ENUM;

}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_EHSM_ESM
 功能描述  : EHSM和ESM之间的枚举定义
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
void ELF_NAS_ENUM_EHSM_ESM(void)
{
    enum EHSM_ESM_PIF_MSG_TYPE_ENUM                         enEHSM_ESM_PIF_MSG_TYPE_ENUM;
    enum EHSM_ESM_PDN_OPTION_ENUM                           enEHSM_ESM_PDN_OPTION_ENUM;
    enum EHSM_ESM_PDN_TYPE_ENUM                             enEHSM_ESM_PDN_TYPE_ENUM;

}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_EHSM_CTTF
 功能描述  : EHSM和CTTF之间的枚举定义
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
void ELF_NAS_ENUM_EHSM_CTTF(void)
{
    enum CNAS_CTTF_EHRPD_PIF_MSG_TYPE_ENUM                  enCNAS_CTTF_EHRPD_PIF_MSG_TYPE_ENUM;
    enum CNAS_CTTF_EHRPD_RSLT_ENUM                          enCNAS_CTTF_EHRPD_RSLT_ENUM;
    enum CNAS_CTTF_EHRPD_ERROR_CODE_ENUM                    enCNAS_CTTF_EHRPD_ERROR_CODE_ENUM;
    enum CNAS_CTTF_EHRPD_ATTACH_TYPE_ENUM                   enCNAS_CTTF_EHRPD_ATTACH_TYPE_ENUM;
    enum CNAS_CTTF_EHRPD_PDN_TYPE_ENUM                      enCNAS_CTTF_EHRPD_PDN_TYPE_ENUM;

}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_IMSA_MSCC
 功能描述  : IMAS和MSCC之间的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : w00351686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_NAS_ENUM_IMSA_MSCC(void)
{
    enum MSCC_IMSA_MSG_ID_ENUM                              enMSCC_IMSA_MSG_ID_ENUM;
    enum MSCC_IMSA_START_TYPE_ENUM                          enMSCC_IMSA_START_TYPE_ENUM;
    enum MSCC_IMSA_STOP_TYPE_ENUM                           enMSCC_IMSA_STOP_TYPE_ENUM;
    enum MSCC_IMSA_IMS_VOPS_INDICATOR_ENUM                  enMSCC_IMSA_IMS_VOPS_INDICATOR_ENUM;
    enum MSCC_IMSA_EMS_INDICATOR_ENUM                       enMSCC_IMSA_EMS_INDICATOR_ENUM;
    enum MSCC_IMSA_SERVICE_STATUS_ENUM                      enMSCC_IMSA_SERVICE_STATUS_ENUM;
    enum MSCC_IMSA_RAT_TYPE_ENUM                            enMSCC_IMSA_RAT_TYPE_ENUM;
    enum MSCC_IMSA_ACCESS_TYPE_ENUM                         enMSCC_IMSA_ACCESS_TYPE_ENUM;
    enum MSCC_IMSA_VOICE_DOMAIN_ENUM                        enMSCC_IMSA_VOICE_DOMAIN_ENUM;

}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_MSCC_XSD
 功能描述  : MSCC和XSD之间的枚举定义
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
void ELF_NAS_ENUM_MSCC_XSD(void)
{
    enum XSD_MSCC_START_RESULT_ENUM                         enXSD_MSCC_START_RESULT_ENUM;
    enum MSCC_XSD_HRPD_CAS_STATUS_ENUM                      enMSCC_XSD_HRPD_CAS_STATUS_ENUM;
    enum MSCC_XSD_SYS_ACQ_TYPE_ENUM                         enMSCC_XSD_SYS_ACQ_TYPE_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_MSCC_MMC
 功能描述  : MSCC和MMC之间的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月17日
    作    者   : w00351686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_NAS_ENUM_MSCC_MMC(void)
{
    enum MSCC_MMC_BG_SRCH_RESULT_ENUM                       enMSCC_MMC_BG_SRCH_RESULT_ENUM;
    enum MMC_MSCC_ATTACH_CL_REG_STATUS_ENUM                 enMMC_MSCC_ATTACH_CL_REG_STATUS_ENUM;
    enum MSCC_MMC_PS_SIGNALING_TYPE_ENUM                    enMSCC_MMC_PS_SIGNALING_TYPE_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_MSCC_PIF
 功能描述  : MSCC对外接口的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : w00351686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_NAS_ENUM_MSCC_PIF(void)
{
    enum NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM                  enNAS_MSCC_PIF_ACQUIRED_RESULT_ENUM;
    enum NAS_MSCC_PIF_PRI_CLASS_ENUM                        enNAS_MSCC_PIF_PRI_CLASS_ENUM;
    enum NAS_MSCC_PIF_CDMACSQ_SET_RESULT_ENUM               enNAS_MSCC_PIF_CDMACSQ_SET_RESULT_ENUM;
    enum NAS_MSCC_PIF_POWER_SAVE_RESULT_ENUM                enNAS_MSCC_PIF_POWER_SAVE_RESULT_ENUM;
    enum NAS_MSCC_PIF_SYS_CFG_SET_RESULT_ENUM               enNAS_MSCC_PIF_SYS_CFG_SET_RESULT_ENUM;
    enum NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_ENUM            enNAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_ENUM;
    enum NAS_MSCC_PIF_SRV_ACQ_RESULT_ENUM                   enNAS_MSCC_PIF_SRV_ACQ_RESULT_ENUM;
    enum NAS_MSCC_PIF_EMC_CALLBACK_MODE_ENUM                enNAS_MSCC_PIF_EMC_CALLBACK_MODE_ENUM;
    enum NAS_MSCC_PIF_CARD_STATUS_ENUM                      enNAS_MSCC_PIF_CARD_STATUS_ENUM;
    enum NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM                   enNAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM;
    enum NAS_MSCC_PIF_CDMA_CALL_CAUSE_ENUM                  enNAS_MSCC_PIF_CDMA_CALL_CAUSE_ENUM;
    enum NAS_MSCC_PIF_SRV_TYPE_ENUM                         enNAS_MSCC_PIF_SRV_TYPE_ENUM;
    enum NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM               enNAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM;
    enum NAS_MSCC_PIF_REG_CONTROL_ENUM                      enNAS_MSCC_PIF_REG_CONTROL_ENUM;
    enum NAS_MSCC_PIF_CALL_MODE_ENUM                        enNAS_MSCC_PIF_CALL_MODE_ENUM;
    enum NAS_MSCC_PIF_MS_MODE_ENUM                          enNAS_MSCC_PIF_MS_MODE_ENUM;
    enum NAS_MSCC_PIF_ATTACH_TYPE_ENUM                      enNAS_MSCC_PIF_ATTACH_TYPE_ENUM;
    enum NAS_MSCC_PIF_EPS_ATTACH_REASON_ENUM                enNAS_MSCC_PIF_EPS_ATTACH_REASON_ENUM;
    enum NAS_MSCC_PIF_DETACH_TYPE_ENUM                      enNAS_MSCC_PIF_DETACH_TYPE_ENUM;
    enum NAS_MSCC_PIF_DETACH_REASON_ENUM                    enNAS_MSCC_PIF_DETACH_REASON_ENUM;
    enum NAS_MSCC_PIF_PLMN_SEL_MODE_ENUM                    enNAS_MSCC_PIF_PLMN_SEL_MODE_ENUM;
    enum NAS_MSCC_PIF_NET_RAT_TYPE_ENUM                     enNAS_MSCC_PIF_NET_RAT_TYPE_ENUM;
    enum NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM                  enNAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM;
    enum NAS_MSCC_PIF_ROAM_CAPABILITY_ENUM                  enNAS_MSCC_PIF_ROAM_CAPABILITY_ENUM;
    enum NAS_MSCC_PIF_ACQ_REASON_ENUM                       enNAS_MSCC_PIF_ACQ_REASON_ENUM;
    enum NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM              enNAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM;
    enum NAS_MSCC_PIF_CFPLMN_OPERATE_TYPE_ENUM              enNAS_MSCC_PIF_CFPLMN_OPERATE_TYPE_ENUM;
    enum NAS_MSCC_PIF_PARA_TYPE_ENUM                        enNAS_MSCC_PIF_PARA_TYPE_ENUM;
    enum NAS_MSCC_PIF_PREF_PLMN_CMD_TYPE_ENUM               enNAS_MSCC_PIF_PREF_PLMN_CMD_TYPE_ENUM;
    enum NAS_MSCC_PIF_IMS_SWITCH_STATE_ENUM                 enNAS_MSCC_PIF_IMS_SWITCH_STATE_ENUM;
    enum NAS_MSCC_PIF_VOICE_DOMAIN_ENUM                     enNAS_MSCC_PIF_VOICE_DOMAIN_ENUM;
    enum NAS_MSCC_PIF_START_RESULT_ENUM                     enNAS_MSCC_PIF_START_RESULT_ENUM;
    enum NAS_MSCC_PIF_LMM_ACCESS_TYPE_ENUM                  enNAS_MSCC_PIF_LMM_ACCESS_TYPE_ENUM;
    enum NAS_MSCC_PIF_SRVDOMAIN_ENUM                        enNAS_MSCC_PIF_SRVDOMAIN_ENUM;
    enum NAS_MSCC_PIF_REG_STATE_ENUM                        enNAS_MSCC_PIF_REG_STATE_ENUM;
    enum NAS_MSCC_PIF_SERVICE_STATUS_ENUM                   enNAS_MSCC_PIF_SERVICE_STATUS_ENUM;
    enum NAS_MSCC_PIF_NETWORK_DETACH_TYPE_ENUM              enNAS_MSCC_PIF_NETWORK_DETACH_TYPE_ENUM;
    enum NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_ENUM        enNAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_ENUM;
    enum NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_ENUM          enNAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_ENUM;
    enum NAS_MSCC_PIF_DATATRAN_ATTRI_ENUM                   enNAS_MSCC_PIF_DATATRAN_ATTRI_ENUM;
    enum NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_ENUM            enNAS_MSCC_PIF_CELL_RESTRICTION_TYPE_ENUM;
    enum NAS_MSCC_PIF_NET_SCAN_RESULT_ENUM                  enNAS_MSCC_PIF_NET_SCAN_RESULT_ENUM;
    enum NAS_MSCC_PIF_NET_SCAN_CAUSE_ENUM                   enNAS_MSCC_PIF_NET_SCAN_CAUSE_ENUM;
    enum NAS_MSCC_PIF_NW_IMS_VOICE_CAP_ENUM                 enNAS_MSCC_PIF_NW_IMS_VOICE_CAP_ENUM;
    enum NAS_MSCC_PIF_NW_EMC_BS_CAP_ENUM                    enNAS_MSCC_PIF_NW_EMC_BS_CAP_ENUM;
    enum NAS_MSCC_PIF_LTE_CS_CAPBILITY_ENUM                 enNAS_MSCC_PIF_LTE_CS_CAPBILITY_ENUM;
    enum NAS_MSCC_PIF_ACQ_RESULT_ENUM                       enNAS_MSCC_PIF_ACQ_RESULT_ENUM;
    enum NAS_MSCC_PIF_REG_RESULT_ENUM                       enNAS_MSCC_PIF_REG_RESULT_ENUM;
    enum NAS_MSCC_PIF_CFPLMN_OPER_RESULT_ENUM               enNAS_MSCC_PIF_CFPLMN_OPER_RESULT_ENUM;
    enum NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_ENUM            enNAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_ENUM;
    enum NAS_MSCC_PIF_IMS_START_RESULT_ENUM                 enNAS_MSCC_PIF_IMS_START_RESULT_ENUM;
    enum NAS_MSCC_PIF_IMS_STOP_RESULT_ENUM                  enNAS_MSCC_PIF_IMS_STOP_RESULT_ENUM;
    enum NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM                   enNAS_MSCC_PIF_INTERSYS_CAUSE_ENUM;
    enum NAS_MSCC_PIF_CFREQ_LOCK_SET_MODE_ENUM              enNAS_MSCC_PIF_CFREQ_LOCK_SET_MODE_ENUM;
    enum NAS_MSCC_PIF_PLMN_SELECTION_RESULT_ENUM            enNAS_MSCC_PIF_PLMN_SELECTION_RESULT_ENUM;
    enum NAS_MSCC_PIF_PLMN_SELECTION_START_FLAG_ENUM        enNAS_MSCC_PIF_PLMN_SELECTION_START_FLAG_ENUM;
    enum NAS_MSCC_PIF_PREF_PLMN_TYPE_ENUM                   enNAS_MSCC_PIF_PREF_PLMN_TYPE_ENUM;
    enum NAS_MSCC_PIF_BAND_CLASS_ENUM                       enNAS_MSCC_PIF_BAND_CLASS_ENUM;
    enum NAS_MSCC_PIF_PREF_NEG_SYS_ENUM                     enNAS_MSCC_PIF_PREF_NEG_SYS_ENUM;
    enum MSCC_PIF_MSG_TYPE_ENUM                             enMSCC_PIF_MSG_TYPE_ENUM;
    enum NAS_MSCC_PIF_AP_PRESET_DPLMN_SCENE_ENUM            enNAS_MSCC_PIF_AP_PRESET_DPLMN_SCENE_ENUM;
    enum NAS_MSCC_PIF_HDR_CSQ_SET_RESULT_ENUM               enNAS_MSCC_PIF_HDR_CSQ_SET_RESULT_ENUM;
    enum NAS_MSCC_PIF_PLMN_WITH_CSG_ID_TYPE_ENUM            enNAS_MSCC_PIF_PLMN_WITH_CSG_ID_TYPE_ENUM;
    enum NAS_MSCC_PIF_PS_RAT_TYPE_ENUM                      enNAS_MSCC_PIF_PS_RAT_TYPE_ENUM;
    enum NAS_MSCC_PIF_PLMN_SEARCH_TYPE_ENUM                 enNAS_MSCC_PIF_PLMN_SEARCH_TYPE_ENUM;
    enum NAS_MSCC_PIF_POWER_SAVE_TYPE_ENUM                  enNAS_MSCC_PIF_POWER_SAVE_TYPE_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_MMC_LMM
 功能描述  : MMC与LMM的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年2月1日
    作    者   : y00346957
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_NAS_ENUM_MMC_LMM(void)
{
    enum MMC_LMM_MSG_ID_ENUM                                enMMC_LMM_MSG_ID_ENUM;
    enum MMC_LMM_SYS_CHNG_TYPE_ENUM                         enMMC_LMM_SYS_CHNG_TYPE_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_MSCC
 功能描述  : MSCC模块的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : w00351686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_NAS_ENUM_MSCC(void)
{
    enum NAS_MSCC_INTERNAL_MSG_TYPE_ENUM                    enNAS_MSCC_INTERNAL_MSG_TYPE_ENUM;
    enum NAS_MSCC_SWITCH_ON_RESULT_ENUM                     enNAS_MSCC_SWITCH_ON_RESULT_ENUM;
    enum NAS_MSCC_POWEROFF_RSLT_ENUM                        enNAS_MSCC_POWEROFF_RSLT_ENUM;
    enum NAS_MSCC_SYS_ACQ_SCENE_ENUM                        enNAS_MSCC_SYS_ACQ_SCENE_ENUM;
    enum NAS_MSCC_SYSTEM_ACQUIRED_RESULT_ENUM               enNAS_MSCC_SYSTEM_ACQUIRED_RESULT_ENUM;
    enum NAS_MSCC_BSR_RESULT_ENUM                           enNAS_MSCC_BSR_RESULT_ENUM;
    enum NAS_MSCC_BSR_ACQ_SYS_ENUM                          enNAS_MSCC_BSR_ACQ_SYS_ENUM;
    enum NAS_MSCC_BSR_RETRY_TIMER_ENUM                      enNAS_MSCC_BSR_RETRY_TIMER_ENUM;
    enum NAS_MSCC_SYS_CFG_RESULT_ENUM                       enNAS_MSCC_SYS_CFG_RESULT_ENUM;
    enum NAS_MSCC_MNTN_MSG_ID_ENUM                          enNAS_MSCC_MNTN_MSG_ID_ENUM;
    enum NAS_MSCC_MLPL_MSPL_SOURCE_ENUM                     enNAS_MSCC_MLPL_MSPL_SOURCE_ENUM;
    enum NAS_MSCC_PARSE_MLPL_RSLT_ENUM                      enNAS_MSCC_PARSE_MLPL_RSLT_ENUM;
    enum NAS_MSCC_PARSE_MSPL_RSLT_ENUM                      enNAS_MSCC_PARSE_MSPL_RSLT_ENUM;
    enum NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_ENUM              enNAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_ENUM;
    enum NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_ENUM        enNAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_ENUM;
    enum NAS_MSCC_MLPL_MATCH_LEVEL_ENUM                     enNAS_MSCC_MLPL_MATCH_LEVEL_ENUM;
    enum NAS_MSCC_PARSE_CRC_RSLT_ENUM                       enNAS_MSCC_PARSE_CRC_RSLT_ENUM;
    enum NAS_MSCC_DISCARD_SERV_STA_ENUM                     enNAS_MSCC_DISCARD_SERV_STA_ENUM;
    enum NAS_MSCC_TIMER_STATUS_ENUM                         enNAS_MSCC_TIMER_STATUS_ENUM;
    enum NAS_MSCC_SWITCH_ON_STA_ENUM                        enNAS_MSCC_SWITCH_ON_STA_ENUM;
    enum NAS_MSCC_SYSACQ_STA_ENUM                           enNAS_MSCC_SYSACQ_STA_ENUM;
    enum NAS_MSCC_NVIM_SYS_PRIORITY_CLASS_ENUM              enNAS_MSCC_NVIM_SYS_PRIORITY_CLASS_ENUM;
    enum NAS_MSCC_TIMER_ID_ENUM                             enNAS_MSCC_TIMER_ID_ENUM;
    enum NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM                   enNAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM;
    enum NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM                   enNAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM;
    enum NAS_MSCC_MSPL_SYS_PRI_ENUM                         enNAS_MSCC_MSPL_SYS_PRI_ENUM;
    enum NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_ENUM            enNAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_ENUM;
    enum NAS_MSCC_MSPL_NETWORK_CAP_ENUM                     enNAS_MSCC_MSPL_NETWORK_CAP_ENUM;
    enum NAS_MSCC_FSM_ID_ENUM                               enNAS_MSCC_FSM_ID_ENUM;
    enum NAS_MSCC_SERVICE_STATUS_ENUM                       enNAS_MSCC_SERVICE_STATUS_ENUM;
    enum NAS_MSCC_CL_INTERSYS_RESULT_ENUM                   enNAS_MSCC_CL_INTERSYS_RESULT_ENUM;
    enum NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ENUM   enNAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ENUM;
}


/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_XSD
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
void ELF_NAS_ENUM_XSD(void)
{
    enum CNAS_XSD_MNTN_MSG_ID_ENUM                          enCNAS_XSD_MNTN_MSG_ID_ENUM;
    enum CNAS_XSD_INTERNAL_MSG_TYPE_ENUM                    enCNAS_XSD_INTERNAL_MSG_TYPE_ENUM;
    enum CNAS_XSD_ABORT_TYPE_ENUM                           enCNAS_XSD_ABORT_TYPE_ENUM;
    enum CNAS_XSD_SWITCH_ON_RESULT_ENUM                     enCNAS_XSD_SWITCH_ON_RESULT_ENUM;
    enum CNAS_XSD_BSR_RESULT_ENUM                           enCNAS_XSD_BSR_RESULT_ENUM;
    enum CNAS_XSD_POWEROFF_RSLT_ENUM                        enCNAS_XSD_POWEROFF_RSLT_ENUM;
    enum CNAS_XSD_POWEROFF_REASON_ENUM                      enCNAS_XSD_POWEROFF_REASON_ENUM;
    enum CNAS_XSD_SCAN_CHAN_STATUS_ENUM                     enCNAS_XSD_SCAN_CHAN_STATUS_ENUM;
    enum CNAS_XSD_REDIRECTION_RESULT_ENUM                   enCNAS_XSD_REDIRECTION_RESULT_ENUM;
    enum CNAS_XSD_SYS_ACQ_SCENE_ENUM                        enCNAS_XSD_SYS_ACQ_SCENE_ENUM;
    enum CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ENUM               enCNAS_XSD_SYSTEM_ACQUIRED_RESULT_ENUM;
    enum CNAS_XSD_PRL_SOURCE_TYPE_ENUM                      enCNAS_XSD_PRL_SOURCE_TYPE_ENUM;

    enum CNAS_PRL_BAND_CLASS_ENUM                           enCNAS_PRL_BAND_CLASS_ENUM;
    enum CNAS_PRL_MNTN_MSG_ID_ENUM                          enCNAS_PRL_MNTN_MSG_ID_ENUM;
    enum CNAS_PRL_SSPR_P_REV_ENUM                           enCNAS_PRL_SSPR_P_REV_ENUM;
    enum CNAS_PRL_SYS_ROAMING_IND_ENUM                      enCNAS_PRL_SYS_ROAMING_IND_ENUM;
    enum CNAS_PRL_ACQ_TYPE_ENUM                             enCNAS_PRL_ACQ_TYPE_ENUM;
    enum CNAS_PRL_SYS_SEL_TYPE_ENUM                         enCNAS_PRL_SYS_SEL_TYPE_ENUM;
    enum CNAS_PRL_STANDARD_CHAN_SEL_TYPE_ENUM               enCNAS_PRL_STANDARD_CHAN_SEL_TYPE_ENUM;
    enum CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_ENUM             enCNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_ENUM;

    enum CNAS_PRL_SYS_RECORD_TYPE_ENUM                      enCNAS_PRL_SYS_RECORD_TYPE_ENUM;
    enum CNAS_PRL_PREF_NEG_SYS_ENUM                         enCNAS_PRL_PREF_NEG_SYS_ENUM;
    enum CNAS_PRL_GEO_REGION_IND_ENUM                       enCNAS_PRL_GEO_REGION_IND_ENUM;
    enum CNAS_PRL_RELATIVE_PRI_IND_ENUM                     enCNAS_PRL_RELATIVE_PRI_IND_ENUM;
    enum CNAS_PRL_NID_INCL_TYPE_ENUM                        enCNAS_PRL_NID_INCL_TYPE_ENUM;
    enum CNAS_PRL_MCC_MNC_SUBTYPE_ENUM                      enCNAS_PRL_MCC_MNC_SUBTYPE_ENUM;

    enum CNAS_XSD_TIMER_ID_ENUM                             enCNAS_XSD_TIMER_ID_ENUM;
    enum CNAS_XSD_FSM_ID_ENUM                               enCNAS_XSD_FSM_ID_ENUM;
    enum CNAS_XSD_L1_STA_ENUM                               enCNAS_XSD_L1_STA_ENUM;
    enum CNAS_XSD_SWITCH_ON_STA_ENUM                        enCNAS_XSD_SWITCH_ON_STA_ENUM;
    enum CNAS_XSD_POWER_OFF_STA_ENUM                        enCNAS_XSD_POWER_OFF_STA_ENUM;
    enum CNAS_XSD_SYS_ACQ_STA_ENUM                          enCNAS_XSD_SYS_ACQ_STA_ENUM;
    enum CNAS_XSD_REDIR_STA_ENUM                            enCNAS_XSD_REDIR_STA_ENUM;

}


/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_XCC
 功能描述  : XCC模块的枚举定义
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
void ELF_NAS_ENUM_XCC(void)
{
    enum CNAS_XCC_INTERNAL_MSG_TYPE_ENUM                    enCNAS_XCC_INTERNAL_MSG_TYPE_ENUM;

    enum CNAS_XCC_MO_CALLING_RESULT_ENUM                    enCNAS_XCC_MO_CALLING_RESULT_ENUM;
    enum CNAS_XCC_MO_CALLING_END_REASON_ENUM                enCNAS_XCC_MO_CALLING_END_REASON_ENUM;
    enum CNAS_XCC_MT_CALLING_RESULT_ENUM                    enCNAS_XCC_MT_CALLING_RESULT_ENUM;
    enum CNAS_XCC_MT_CALLING_END_REASON_ENUM                enCNAS_XCC_MT_CALLING_END_REASON_ENUM;

    enum CNAS_XCC_TIMER_ID_ENUM                             enCNAS_XCC_TIMER_ID_ENUM;
    enum CNAS_XCC_FSM_ID_ENUM                               enCNAS_XCC_FSM_ID_ENUM;
    enum CNAS_XCC_L1_STA_ENUM                               enCNAS_XCC_L1_STA_ENUM;
    enum CNAS_XCC_MO_CALLING_STA_ENUM                       enCNAS_XCC_MO_CALLING_STA_ENUM;
    enum CNAS_XCC_MT_CALLING_STA_ENUM                       enCNAS_XCC_MT_CALLING_STA_ENUM;

}


/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_HLU
 功能描述  : HLU模块的枚举定义
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
void ELF_NAS_ENUM_HLU(void)
{
    enum CNAS_HLU_LOC_MSG_ID_ENUM                           enCNAS_HLU_LOC_MSG_ID_ENUM;
}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_HSM
 功能描述  : HSM模块的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : w00351686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_NAS_ENUM_HSM(void)
{
    enum CNAS_HSM_INTERNAL_MSG_TYPE_ENUM                    enCNAS_HSM_INTERNAL_MSG_TYPE_ENUM;
    enum CNAS_HSM_UATI_REQ_TRIGGER_ENUM                     enCNAS_HSM_UATI_REQ_TRIGGER_ENUM;
    enum CNAS_HSM_SESSION_ACTIVE_REASON_ENUM                enCNAS_HSM_SESSION_ACTIVE_REASON_ENUM;
    enum CNAS_HSM_SESSION_DEACT_REASON_ENUM                 enCNAS_HSM_SESSION_DEACT_REASON_ENUM;
    enum CNAS_HSM_UATI_REQUEST_RESULT_ENUM                  enCNAS_HSM_UATI_REQUEST_RESULT_ENUM;
    enum CNAS_HSM_UATI_REQUEST_FAIL_REASON_ENUM             enCNAS_HSM_UATI_REQUEST_FAIL_REASON_ENUM;
    enum CNAS_HSM_SESSION_ACTIVE_RESULT_ENUM                enCNAS_HSM_SESSION_ACTIVE_RESULT_ENUM;
    enum CNAS_HSM_SESSION_ACT_FAIL_REASON_ENUM              enCNAS_HSM_SESSION_ACT_FAIL_REASON_ENUM;
    enum CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_ENUM     enCNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_ENUM;
    enum CNAS_HSM_CONN_MNMT_TRIGGER_ENUM                    enCNAS_HSM_CONN_MNMT_TRIGGER_ENUM;
    enum CNAS_HSM_CONN_MNMT_RESULT_ENUM                     enCNAS_HSM_CONN_MNMT_RESULT_ENUM;
    enum CNAS_HRPD_SESSION_TYPE_ENUM                        enCNAS_HRPD_SESSION_TYPE_ENUM;
    enum CNAS_HSM_MNTN_MSG_ID_ENUM                          enCNAS_HSM_MNTN_MSG_ID_ENUM;
    enum CNAS_HSM_HARDWARE_ID_TYPE_ENUM                     enCNAS_HSM_HARDWARE_ID_TYPE_ENUM;
    enum CNAS_HSM_HARDWARE_ID_SRC_TYPE_ENUM                 enCNAS_HSM_HARDWARE_ID_SRC_TYPE_ENUM;
    enum CNAS_HSM_BUFFER_MSG_OPERATE_TYPE_ENUM              enCNAS_HSM_BUFFER_MSG_OPERATE_TYPE_ENUM;
    enum CNAS_HSM_UATI_ASSIGN_CATE_ENUM                     enCNAS_HSM_UATI_ASSIGN_CATE_ENUM;
    enum CNAS_HSM_KEEP_ALIVE_TIMER_SCENE_ENUM               enCNAS_HSM_KEEP_ALIVE_TIMER_SCENE_ENUM;
    enum CNAS_HSM_SESSION_STATUS_ENUM                       enCNAS_HSM_SESSION_STATUS_ENUM;
    enum CNAS_HSM_L1_STA_ENUM                               enCNAS_HSM_L1_STA_ENUM;
    enum CNAS_HSM_SS_ID_ENUM                                enCNAS_HSM_SS_ID_ENUM;
    enum CNAS_HSM_HRPD_CAS_STATUS_ENUM                      enCNAS_HSM_HRPD_CAS_STATUS_ENUM;
    enum CNAS_HSM_CONN_STATUS_ENUM                          enCNAS_HSM_CONN_STATUS_ENUM;
    enum CNAS_HSM_MNTN_LOG_DISCARD_MSG_SCENE_ENUM           enCNAS_HSM_MNTN_LOG_DISCARD_MSG_SCENE_ENUM;
    enum CNAS_HSM_TIMER_ID_ENUM                             enCNAS_HSM_TIMER_ID_ENUM;
    enum CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_ENUM        enCNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_ENUM;
    enum CNAS_HSM_MSG_PRI_ENUM                              enCNAS_HSM_MSG_PRI_ENUM;

}


/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_EHSM
 功能描述  : EHSM模块的枚举定义
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
void ELF_NAS_ENUM_EHSM(void)
{
    enum CNAS_EHSM_TIMER_ID_ENUM                            enCNAS_EHSM_TIMER_ID_ENUM;

    enum CNAS_EHSM_INTERNAL_MSG_TYPE_ENUM                   enCNAS_EHSM_INTERNAL_MSG_TYPE_ENUM;
    enum CNAS_EHSM_ATTACH_REASON_ENUM                       enCNAS_EHSM_ATTACH_REASON_ENUM;
    enum CNAS_EHSM_ACTIVATING_RESULT_ENUM                   enCNAS_EHSM_ACTIVATING_RESULT_ENUM;

    enum CNAS_EHSM_EHRPD_STA_ENUM                           enCNAS_EHSM_EHRPD_STA_ENUM;
    enum CNAS_EHSM_ATTACH_TYPE_ENUM                         enCNAS_EHSM_ATTACH_TYPE_ENUM;
    enum CNAS_EHSM_PDN_TYPE_ENUM                            enCNAS_EHSM_PDN_TYPE_ENUM;

    enum CNAS_EHSM_MNTN_MSG_ID_ENUM                         enCNAS_EHSM_MNTN_MSG_ID_ENUM;

    enum CNAS_EHSM_TIMER_STATUS_ENUM                        enCNAS_EHSM_TIMER_STATUS_ENUM;

    enum CNAS_EHSM_FSM_ID_ENUM                              enCNAS_EHSM_FSM_ID_ENUM;

    enum CNAS_EHSM_L1_STA_ENUM                              enCNAS_EHSM_L1_STA_ENUM;
    enum CNAS_EHSM_ACTIVATING_STA_ENUM                      enCNAS_EHSM_ACTIVATING_STA_ENUM;
    enum CNAS_EHSM_DEACTIVATING_STA_ENUM                    enCNAS_EHSM_DEACTIVATING_STA_ENUM;

}


/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_LIST
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
void ELF_NAS_ENUM_LIST(void)
{
    ELF_NAS_ENUM_COMMON();

    ELF_NAS_ENUM_CNAS_COMMON();

    ELF_NAS_ENUM_CAS_CNAS();

    ELF_NAS_ENUM_TAF_XCC();

    ELF_NAS_ENUM_TAF_XCALL_XCC();

    ELF_NAS_ENUM_TAF_APS_XCC();

    ELF_NAS_ENUM_TAF_APS_EHSM();

    ELF_NAS_ENUM_TAF_XSMS_XCC();

    ELF_NAS_ENUM_TAF_HSM();

    ELF_NAS_ENUM_MMA_XCC();

    ELF_NAS_ENUM_MMA_MSCC();

    ELF_NAS_ENUM_XCC_XSD();

    ELF_NAS_ENUM_XSD_XREG();

    ELF_NAS_ENUM_MSCC_XSD();

    ELF_NAS_ENUM_HSM_MMA();

    ELF_NAS_ENUM_HSM_HLU();

    ELF_NAS_ENUM_HSM_HSD();

    ELF_NAS_ENUM_HSD_MSCC();

    ELF_NAS_ENUM_EHSM_HSD();

    ELF_NAS_ENUM_EHSM_HSM();

    ELF_NAS_ENUM_EHSM_ESM();

    ELF_NAS_ENUM_EHSM_CTTF();

    ELF_NAS_ENUM_HSD_MSCC();

    ELF_NAS_ENUM_HSD_HLU();

    ELF_NAS_ENUM_IMSA_MSCC();

    ELF_NAS_ENUM_MSCC_MMC();

    ELF_NAS_ENUM_MSCC_PIF();

    ELF_NAS_ENUM_MMC_LMM();

    ELF_NAS_ENUM_MSCC();

    ELF_NAS_ENUM_XSD();

    ELF_NAS_ENUM_XCC();

    ELF_NAS_ENUM_HLU();

    ELF_NAS_ENUM_HSM();

    ELF_NAS_ENUM_EHSM();

}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_GU_TRANS_Config_GU_NAS
 功能描述  : HiStudio_Cmd_GU_TRANS_Config中GU_NAS的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月18日
    作    者   : w00351686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_NAS_ENUM_GU_TRANS_Config_GU_NAS(void)
{
    enum MODEM_ID_ASN_ENUM                                  enMODEM_ID_ASN_ENUM;
    enum OM_NAS_MMA_CDMA_STATUS_REPORT_CMD_ENUM             enOM_NAS_MMA_CDMA_STATUS_REPORT_CMD_ENUM;
    enum NAS_OM_MMA_CDMA_STATUS_REPORT_RESRLT_ENUM          enNAS_OM_MMA_CDMA_STATUS_REPORT_RESRLT_ENUM;
    enum NAS_OM_MMA_PHONE_MODE_ENUM                         enNAS_OM_MMA_PHONE_MODE_ENUM;
    enum NAS_OM_1X_CALL_STATE_ENUM                          enNAS_OM_1X_CALL_STATE_ENUM;
    enum NAS_OM_MMA_HRPD_SESSION_STATUS_ENUM                enNAS_OM_MMA_HRPD_SESSION_STATUS_ENUM;
    enum NAS_OM_MMA_SYS_SUBMODE_ENUM                        enNAS_OM_MMA_SYS_SUBMODE_ENUM;
    enum NAS_OM_MMA_PPP_STATUS_ENUM                         enNAS_OM_MMA_PPP_STATUS_ENUM;

}

/*****************************************************************************
 函 数 名  : ELF_NAS_ENUM_GU_NAS
 功能描述  : HiStudio_Cmd_GU_TRANS_Config中各模块的枚举定义
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月18日
    作    者   : w00351686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_NAS_ENUM_GU_TRANS_Config(void)
{
    ELF_NAS_ENUM_GU_TRANS_Config_GU_NAS();
}

/*****************************************************************************
 函 数 名  : ELF_NAS_STRU_TraceTable_XSD
 功能描述  : TraceTable中XSD的消息结构
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
void ELF_NAS_STRU_TraceTable_XSD(void)
{
    /******************* 发送模块：XSD，接收模块：MSCC Begin  *******************/
    XSD_MSCC_START_CNF_STRU                                 stXSD_MSCC_START_CNF_STRU;
    XSD_MSCC_POWER_OFF_CNF_STRU                             stXSD_MSCC_POWER_OFF_CNF_STRU;
    XSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU                        stXSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU;
    XSD_MSCC_SYSTEM_ACQUIRE_IND_STRU                        stXSD_MSCC_SYSTEM_ACQUIRE_IND_STRU;
    XSD_MSCC_SYSTEM_ACQUIRE_START_IND_STRU                  stXSD_MSCC_SYSTEM_ACQUIRE_START_IND_STRU;
    XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU                stXSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU;
    XSD_MSCC_CDMACSQ_SET_CNF_STRU                           stXSD_MSCC_CDMACSQ_SET_CNF_STRU;
    XSD_MSCC_CDMACSQ_IND_STRU                               stXSD_MSCC_CDMACSQ_IND_STRU;
    XSD_MSCC_1X_SYSTEM_TIME_IND_STRU                        stXSD_MSCC_1X_SYSTEM_TIME_IND_STRU;
    XSD_MSCC_POWER_SAVE_CNF_STRU                            stXSD_MSCC_POWER_SAVE_CNF_STRU;
    XSD_MSCC_SYS_CFG_CNF_STRU                               stXSD_MSCC_SYS_CFG_CNF_STRU;
    XSD_MSCC_SRV_ACQ_CNF_STRU                               stXSD_MSCC_SRV_ACQ_CNF_STRU;
    XSD_MSCC_HANDSET_INFO_QRY_CNF_STRU                      stXSD_MSCC_HANDSET_INFO_QRY_CNF_STRU;
    XSD_MSCC_EMC_CALLBACK_IND_STRU                          stXSD_MSCC_EMC_CALLBACK_IND_STRU;
    XSD_MSCC_SET_CSIDLIST_CNF_STRU                          stXSD_MSCC_SET_CSIDLIST_CNF_STRU;
    XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND_STRU                stXSD_MSCC_SYNC_SERVICE_AVAILABLE_IND_STRU;
    XSD_MSCC_UE_STATE_IND_STRU                              stXSD_MSCC_UE_STATE_IND_STRU;
    XSD_MSCC_1X_NO_SERVICE_IND_STRU                         stXSD_MSCC_1X_NO_SERVICE_IND_STRU;
    /******************* 发送模块：XSD，接收模块：MSCC End  *******************/

    /******************* 发送模块：XSD，接收模块：XREG Begin  *******************/
    XSD_XREG_START_REQ_STRU                                 stXSD_XREG_START_REQ_STRU;
    XSD_XREG_POWER_OFF_REQ_STRU                             stXSD_XREG_POWER_OFF_REQ_STRU;
    XSD_XREG_SYS_INFO_IND_STRU                              stXSD_XREG_SYS_INFO_IND_STRU;
    XSD_XREG_REDIRECTION_IND_STRU                           stXSD_XREG_REDIRECTION_IND_STRU;
    XSD_XREG_DEREGISTER_IND_STRU                            stXSD_XREG_DEREGISTER_IND_STRU;
    XSD_XREG_UE_STATE_IND_STRU                              stXSD_XREG_UE_STATE_IND_STRU;
    /******************* 发送模块：XSD，接收模块：XREG End  *******************/

    /******************* 发送模块：XSD，接收模块：XCC Begin  *******************/
    XSD_XCC_START_REQ_STRU                                  stXSD_XCC_START_REQ_STRU;
    XSD_XCC_POWER_OFF_REQ_STRU                              stXSD_XCC_POWER_OFF_REQ_STRU;
    XSD_XCC_NDSS_RESULT_IND_STRU                            stXSD_XCC_NDSS_RESULT_IND_STRU;
    /******************* 发送模块：XSD，接收模块：XCC End  *******************/

    /******************* 发送模块：XSD，接收模块：XSD Begin  *******************/
    CNAS_XSD_XSD_ABORT_REQ_STRU                             stCNAS_XSD_XSD_ABORT_REQ_STRU;
    CNAS_XSD_XSD_SWITCH_ON_RSLT_CNF_STRU                    stCNAS_XSD_XSD_SWITCH_ON_RSLT_CNF_STRU;
    CNAS_XSD_XSD_BSR_RSLT_CNF_STRU                          stCNAS_XSD_XSD_BSR_RSLT_CNF_STRU;
    CNAS_XSD_XSD_POWER_OFF_RSLT_CNF_STRU                    stCNAS_XSD_XSD_POWER_OFF_RSLT_CNF_STRU;
    CNAS_XSD_XSD_REDIRECTION_IND_STRU                       stCNAS_XSD_XSD_REDIRECTION_IND_STRU;
    CNAS_XSD_XSD_REDIRECTION_RSLT_CNF_STRU                  stCNAS_XSD_XSD_REDIRECTION_RSLT_CNF_STRU;
    CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU                   stCNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU;
    CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU              stCNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU;

    CNAS_MNTN_LOG_MSG_INFO_IND_STRU                         stCNAS_MNTN_LOG_MSG_INFO_IND_STRU;
    CNAS_DIAG_LOG_NV_INFO_IND_STRU                          stCNAS_DIAG_LOG_NV_INFO_IND_STRU;
    CNAS_MNTN_LOG_COMMON_STATUS_INFO_IND_STRU               stCNAS_MNTN_LOG_COMMON_STATUS_INFO_IND_STRU;

    CNAS_XSD_LOG_SCAN_CHNNEL_LIST_MSG_STRU                  stCNAS_XSD_LOG_SCAN_CHNNEL_LIST_MSG_STRU;
    CNAS_XSD_LOG_ACQ_SYSTEM_LIST_MSG_STRU                   stCNAS_XSD_LOG_ACQ_SYSTEM_LIST_MSG_STRU;
    CNAS_XSD_LOG_AVAIL_SYSTEM_LIST_MSG_STRU                 stCNAS_XSD_LOG_AVAIL_SYSTEM_LIST_MSG_STRU;
    CNAS_XSD_LOG_MRU_LIST_MSG_STRU                          stCNAS_XSD_LOG_MRU_LIST_MSG_STRU;
    CNAS_XSD_LOG_AVOID_FREQ_LIST_MSG_STRU                   stCNAS_XSD_LOG_AVOID_FREQ_LIST_MSG_STRU;
    CNAS_XSD_LOG_PRL_SOURCE_TYPE_MSG_STRU                   stCNAS_XSD_LOG_PRL_SOURCE_TYPE_MSG_STRU;
    CNAS_XSD_LOG_BUffER_MSG_INFO_STRU                       stCNAS_XSD_LOG_BUffER_MSG_INFO_STRU;
    CNAS_XSD_LOG_BANDCLASS_LIST_MSG_STRU                    stCNAS_XSD_LOG_BANDCLASS_LIST_MSG_STRU;
    CNAS_XSD_LOG_HOME_SID_NID_LIST_MSG_STRU                 stCNAS_XSD_LOG_HOME_SID_NID_LIST_MSG_STRU;
    CNAS_XSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU           stCNAS_XSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU;
    CNAS_XSD_LOG_OOC_CTX_INFO_MSG_STRU                      stCNAS_XSD_LOG_OOC_CTX_INFO_MSG_STRU;
    CNAS_XSD_LOG_HOME_SID_NID_MOST_PRI_FLG_STRU             stCNAS_XSD_LOG_HOME_SID_NID_MOST_PRI_FlG_STRU;
    CNAS_XSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU              stCNAS_XSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU;
    CNAS_XSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU              stCNAS_XSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU;
    CNAS_XSD_LOG_GEO_LIST_SRCH_STATUS_STRU                  stCNAS_XSD_LOG_GEO_LIST_SRCH_STATUS_STRU;
    CNAS_XSD_LOG_CDMA_STANDARD_CHANNELS_STRU                stCNAS_XSD_LOG_CDMA_STANDARD_CHANNELS_STRU;
    CNAS_XSD_LOG_CALLBACK_CFG_STRU                          stCNAS_XSD_LOG_CALLBACK_CFG_STRU;
    CNAS_XSD_LOG_CALLBACK_STATUS_STRU                       stCNAS_XSD_LOG_CALLBACK_STATUS_STRU;
    CNAS_XSD_LOG_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU          stCNAS_XSD_LOG_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU;

    CNAS_PRL_MNTN_HEADER_INFO_IND_STRU                      stCNAS_PRL_MNTN_HEADER_INFO_IND_STRU;
    CNAS_PRL_MNTN_ACQ_REC_INFO_IND_STRU                     stCNAS_PRL_MNTN_ACQ_REC_INFO_IND_STRU;
    CNAS_PRL_MNTN_SYS_REC_INFO_IND_STRU                     stCNAS_PRL_MNTN_SYS_REC_INFO_IND_STRU;

    CNAS_MNTN_ELF_LOG_XSD_FSM_INFO_STRU                     stCNAS_MNTN_ELF_LOG_XSD_FSM_INFO_STRU;

    /******************* 发送模块：XSD，接收模块：XSD End  *******************/

    /******************* 发送模块：XSD，接收模块：TIMER End  *******************/
    CNAS_MNTN_ELF_LOG_XSD_TIMER_INFO_IND_STRU               stCNAS_MNTN_ELF_LOG_XSD_TIMER_INFO_IND_STRU;
    /******************* 发送模块：XSD，接收模块：TIMER End  *******************/

    /******************* 发送模块：XSD，接收模块：USIM Begin  *******************/
    CNAS_MNTN_LOG_USIMM_API_GET_FILE_REQ_STRU               stCNAS_MNTN_LOG_USIMM_API_GET_FILE_REQ_STRU;
    USIMM_READFILE_REQ_STRU                                 stUSIMM_READFILE_REQ_STRU;
    /******************* 发送模块：XSD，接收模块：USIM End  *******************/

    /******************* 发送模块：XSD，接收模块：RRM Begin  *******************/
    PS_RRM_REGISTER_IND_STRU                                stPS_RRM_REGISTER_IND_STRU;
    PS_RRM_DEREGISTER_IND_STRU                              stPS_RRM_DEREGISTER_IND_STRU;
    /******************* 发送模块：XSD，接收模块：RRM End  *******************/

}

/*****************************************************************************
 函 数 名  : ELF_NAS_STRU_TraceTable_XCC
 功能描述  : TraceTable中XCC的消息结构
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
void ELF_NAS_STRU_TraceTable_XCC(void)
{
    /******************* 发送模块：XCC，接收模块：XSD Begin  *******************/
    XCC_XSD_START_CNF_STRU                                  stXCC_XSD_START_CNF_STRU;
    XCC_XSD_POWER_OFF_CNF_STRU                              stXCC_XSD_POWER_OFF_CNF_STRU;
    XCC_XSD_DEREGISTER_IND_STRU                             stXCC_XSD_DEREGISTER_IND_STRU;
    /******************* 发送模块：XCC，接收模块：XSD End  *******************/

    /******************* 发送模块：XCC，接收模块：XCC Begin  *******************/
    CNAS_MNTN_LOG_ENCODE_ABNORMAL_INFO_IND_STRU             stCNAS_MNTN_LOG_ENCODE_ABNORMAL_INFO_IND_STRU;
    CNAS_MNTN_LOG_DECODE_ABNORMAL_INFO_IND_STRU             stCNAS_MNTN_LOG_DECODE_ABNORMAL_INFO_IND_STRU;
    CNAS_XCC_XCC_ABORT_REQ_STRU                             stCNAS_XCC_XCC_ABORT_REQ_STRU;
    CNAS_XCC_XCC_MO_CALLING_RSLT_CNF_STRU                   stCNAS_XCC_XCC_MO_CALLING_RSLT_CNF_STRU;
    CNAS_XCC_XCC_MT_CALLING_RSLT_CNF_STRU                   stCNAS_XCC_XCC_MT_CALLING_RSLT_CNF_STRU;
    CNAS_XCC_XCC_POWER_DOWN_IND_STRU                        stCNAS_XCC_XCC_POWER_DOWN_IND_STRU;
    CNAS_XCC_XCC_NDSS_REDIAL_IND_STRU                       stCNAS_XCC_XCC_NDSS_REDIAL_IND_STRU;
    CNAS_XCC_XCC_CALL_STATE_IND_STRU                        stCNAS_XCC_XCC_CALL_STATE_IND_STRU;

    CNAS_MNTN_ELF_LOG_XCC_FSM_INFO_STRU                     stCNAS_MNTN_ELF_LOG_XCC_FSM_INFO_STRU;
    /******************* 发送模块：XCC，接收模块：XCC End  *******************/

    /******************* 发送模块：XCC，接收模块：TAF Begin  *******************/
    XCC_XCALL_CODEC_CLOSE_IND_STRU                          stXCC_XCALL_CODEC_CLOSE_IND_STRU;
    XCC_XCALL_CODEC_OPEN_IND_STRU                           stXCC_XCALL_CODEC_OPEN_IND_STRU;
    XCC_XCALL_CODEC_CHANGED_IND_STRU                        stXCC_XCALL_CODEC_CHANGED_IND_STRU;
    XCC_XCALL_SO_CTRL_MSG_IND_STRU                          stXCC_XCALL_SO_CTRL_MSG_IND_STRU;
    XCC_XCALL_SO_CTRL_ORDER_IND_STRU                        stXCC_XCALL_SO_CTRL_ORDER_IND_STRU;
    XCC_XCALL_ORIG_CALL_CNF_STRU                            stXCC_XCALL_ORIG_CALL_CNF_STRU;
    XCC_XCALL_HANGUP_CALL_CNF_STRU                          stXCC_XCALL_HANGUP_CALL_CNF_STRU;
    XCC_XCALL_CALL_DISC_IND_STRU                            stXCC_XCALL_CALL_DISC_IND_STRU;
    XCC_XCALL_INCOMING_CALL_IND_STRU                        stXCC_XCALL_INCOMING_CALL_IND_STRU;
    XCC_XCALL_ANSWER_CALL_CNF_STRU                          stXCC_XCALL_ANSWER_CALL_CNF_STRU;
    XCC_XCALL_CALL_CONNECT_IND_STRU                         stXCC_XCALL_CALL_CONNECT_IND_STRU;
    XCC_XCALL_START_DTMF_CNF_STRU                           stXCC_XCALL_START_DTMF_CNF_STRU;
    XCC_XCALL_STOP_DTMF_CNF_STRU                            stXCC_XCALL_STOP_DTMF_CNF_STRU;
    XCC_XCALL_BURST_DTMF_CNF_STRU                           stXCC_XCALL_BURST_DTMF_CNF_STRU;
    XCC_XCALL_SEND_FLASH_CNF_STRU                           stXCC_XCALL_SEND_FLASH_CNF_STRU;
    XCC_XCALL_INFO_REC_IND_STRU                             stXCC_XCALL_INFO_REC_IND_STRU;
    XCC_XCALL_NDSS_RESULT_IND_STRU                          stXCC_XCALL_NDSS_RESULT_IND_STRU;
    XCC_XCALL_SEND_CONT_DTMF_CNF_STRU                       stXCC_XCALL_SEND_CONT_DTMF_CNF_STRU;
    XCC_XCALL_CONT_DTMF_IND_STRU                            stXCC_XCALL_CONT_DTMF_IND_STRU;
    XCC_XCALL_BURST_DTMF_IND_STRU                           stXCC_XCALL_BURST_DTMF_IND_STRU;
    XCC_XCALL_ECC_SERVICE_CNF_STRU                          stXCC_XCALL_ECC_SERVICE_CNF_STRU;
    XCC_XCALL_TCH_ASSIGN_CMPL_IND_STRU                      stXCC_XCALL_TCH_ASSIGN_CMPL_IND_STRU;

    XCC_APS_ORIG_DATA_CALL_CNF_STRU                         stXCC_APS_ORIG_DATA_CALL_CNF_STRU;
    XCC_APS_HANGUP_DATA_CALL_CNF_STRU                       stXCC_APS_HANGUP_DATA_CALL_CNF_STRU;
    XCC_APS_DATA_CALL_DISC_IND_STRU                         stXCC_APS_DATA_CALL_DISC_IND_STRU;
    XCC_APS_INCOMING_CALL_IND_STRU                          stXCC_APS_INCOMING_CALL_IND_STRU;
    XCC_APS_DATA_CALL_CONN_IND_STRU                         stXCC_APS_DATA_CALL_CONN_IND_STRU;
    XCC_APS_DATA_SERVICE_CONNECT_IND_STRU                   stXCC_APS_DATA_SERVICE_CONNECT_IND_STRU;
    XCC_APS_ANSWER_DATA_CALL_CNF_STRU                       stXCC_APS_ANSWER_DATA_CALL_CNF_STRU;
    XCC_APS_DATA_CALL_SUSPEND_IND_STRU                      stXCC_APS_DATA_CALL_SUSPEND_IND_STRU;
    XCC_APS_DATA_CALL_RESUME_IND_STRU                       stXCC_APS_DATA_CALL_RESUME_IND_STRU;
    XCC_APS_SO_CTRL_MSG_IND_STRU                            stXCC_APS_SO_CTRL_MSG_IND_STRU;
    XCC_APS_UPDATE_DATA_CALL_INFO_IND_STRU                  stXCC_APS_UPDATE_DATA_CALL_INFO_IND_STRU;
    XCC_XCALL_PRIVACY_MODE_SET_CNF_STRU                     stXCC_XCALL_PRIVACY_MODE_SET_CNF_STRU;
    XCC_XCALL_PRIVACY_MODE_QRY_CNF_STRU                     stXCC_XCALL_PRIVACY_MODE_QRY_CNF_STRU;
    XCC_XCALL_PRIVACY_MODE_IND_STRU                         stXCC_XCALL_PRIVACY_MODE_IND_STRU;

    /******************* 发送模块：XCC，接收模块：TAF End  *******************/

    /******************* 发送模块：XCC，接收模块：MMA Begin  *******************/
    XCC_MMA_1X_CALL_STATE_IND_STRU                          stXCC_MMA_1X_CALL_STATE_IND_STRU;
    /******************* 发送模块：XCC，接收模块：MMA End  *******************/

    /******************* 发送模块：XCC，接收模块：TIMER End  *******************/
    CNAS_MNTN_ELF_LOG_XCC_TIMER_INFO_IND_STRU               stCNAS_MNTN_ELF_LOG_XCC_TIMER_INFO_IND_STRU;
    /******************* 发送模块：XCC，接收模块：TIMER End  *******************/

    /******************* 发送模块：XCC，接收模块：XSMS Begin  *******************/
    XCC_CSMS_ORIG_SMS_CALL_CNF_STRU                         stXCC_CSMS_ORIG_SMS_CALL_CNF_STRU;
    XCC_CSMS_END_SMS_CALL_CNF_STRU                          stXCC_CSMS_END_SMS_CALL_CNF_STRU;
    XCC_CSMS_INCOMING_CALL_IND_STRU                         stXCC_CSMS_INCOMING_CALL_IND_STRU;
    XCC_CSMS_CALL_CONN_IND_STRU                             stXCC_CSMS_CALL_CONN_IND_STRU;
    XCC_CSMS_ANSWER_CALL_CNF_STRU                           stXCC_CSMS_ANSWER_CALL_CNF_STRU;
    XCC_CSMS_MESSAGE_WAITING_IND_STRU                       stXCC_CSMS_MESSAGE_WAITING_IND_STRU;
    XCC_CSMS_SERVICE_CONNECT_IND_STRU                       stXCC_CSMS_SERVICE_CONNECT_IND_STRU;
    XCC_CSMS_MSG_WATING_IND_STRU                            stXCC_CSMS_MSG_WATING_IND_STRU;
    CSMS_XCC_ORIG_SMS_CALL_REQ_STRU                         stCSMS_XCC_ORIG_SMS_CALL_REQ_STRU;
    CSMS_XCC_INCOMING_CALL_RSP_STRU                         stCSMS_XCC_INCOMING_CALL_RSP_STRU;
    CSMS_XCC_ANSWER_CALL_REQ_STRU                           stCSMS_XCC_ANSWER_CALL_REQ_STRU;
    CSMS_XCC_END_SMS_CALL_REQ_STRU                          stCSMS_XCC_END_SMS_CALL_REQ_STRU;
    /******************* 发送模块：XCC，接收模块：XSMS End  *******************/

}

/*****************************************************************************
 函 数 名  : ELF_NAS_STRU_TraceTable_HLU
 功能描述  : TraceTable中HLU的消息结构
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
void ELF_NAS_STRU_TraceTable_HLU(void)
{
    /**************************** HLU <====>HSM Begin ***************************/
    HSM_HLU_1X_TO_HRPD_HANDOFF_REQ_STRU                     stHSM_HLU_1X_TO_HRPD_HANDOFF_REQ_STRU;
    HLU_HSM_1X_TO_HRPD_HANDOFF_CNF_STRU                     stHLU_HSM_1X_TO_HRPD_HANDOFF_CNF_STRU;
    HSM_HLU_SESSION_CHANGED_IND_STRU                        stHSM_HLU_SESSION_CHANGED_IND_STRU;
    HLU_HSM_LOC_CHANGED_IND_STRU                            stHLU_HSM_LOC_CHANGED_IND_STRU;
    /****************************  HLU <====> HSM End  ***************************/

    /**************************** HLU <====>HSD Begin ***************************/
    HSD_HLU_START_REQ_STRU                                  stHSD_HLU_START_REQ_STRU;
    HLU_HSD_START_CNF_STRU                                  stHLU_HSD_START_CNF_STRU;
    HSD_HLU_POWER_OFF_REQ_STRU                              stHSD_HLU_POWER_OFF_REQ_STRU;
    HLU_HSD_POWER_OFF_CNF_STRU                              stHLU_HSD_POWER_OFF_CNF_STRU;
    /****************************  HLU <====> HSD End  ***************************/

    /**************************** HLU <====>HLU Begin ***************************/
    CNAS_HLU_HRPD_MSG_TYPE_STRU                             stCNAS_HLU_HRPD_MSG_TYPE_STRU;
    CNAS_HLU_HRPD_LOC_NOTF_STRU                             stCNAS_HLU_HRPD_LOC_NOTF_STRU;
    CNAS_HLU_HRPD_LOC_ASSG_STRU                             stCNAS_HLU_HRPD_LOC_ASSG_STRU;

    CNAS_HLU_HRPD_BLOB_NOTF_STRU                            stCNAS_HLU_HRPD_BLOB_NOTF_STRU;
    CNAS_HLU_HRPD_BLOB_ASSG_STRU                            stCNAS_HLU_HRPD_BLOB_ASSG_STRU;
    /****************************  HLU <====> HLU End  ***************************/

}

/*****************************************************************************
 函 数 名  : ELF_NAS_STRU_TraceTable_EHSM
 功能描述  : TraceTable中EHSM的消息结构
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
void ELF_NAS_STRU_TraceTable_EHSM(void)
{
    /*************************  EHSM <====> EHSM Begin  *************************/
    CNAS_EHSM_EHSM_ATTACH_REQ_STRU                          stCNAS_EHSM_EHSM_ATTACH_REQ_STRU;
    CNAS_EHSM_EHSM_ACTIVATING_RSLT_CNF_STRU                 stCNAS_EHSM_EHSM_ACTIVATING_RSLT_CNF_STRU;
    CNAS_EHSM_EHSM_DEACTIVATING_RSLT_CNF_STRU               stCNAS_EHSM_EHSM_DEACTIVATING_RSLT_CNF_STRU;
    CNAS_EHSM_EHSM_PDN_RE_ESTABLISH_REQ_STRU                stCNAS_EHSM_EHSM_PDN_RE_ESTABLISH_REQ_STRU;
    CNAS_EHSM_EHSM_ABORT_REQ_STRU                           stCNAS_EHSM_EHSM_ABORT_REQ_STRU;
    CNAS_EHSM_EHSM_LOCAL_DETACH_ALL_REQ_STRU                stCNAS_EHSM_EHSM_LOCAL_DETACH_ALL_REQ_STRU;

    CNAS_EHSM_MNTN_ELF_LOG_FSM_INFO_STRU                    stCNAS_EHSM_MNTN_ELF_LOG_FSM_INFO_STRU;

    CNAS_EHSM_MNTN_LOG_BUFFER_MSG_INFO_STRU                 stCNAS_EHSM_MNTN_LOG_BUFFER_MSG_INFO_STRU;
    CNAS_EHSM_MNTN_LOG_CTX_INFO_STRU                        stCNAS_EHSM_MNTN_LOG_CTX_INFO_STRU;

    /**************************  EHSM <====> EHSM End  **************************/

    /*************************  EHSM <====> TIMER Begin  ************************/
    CNAS_EHSM_ELF_TIMER_INFO_STRU                           stCNAS_EHSM_ELF_TIMER_INFO_STRU;
    /**************************  EHSM <====> TIMER End  *************************/

    /*************************  EHSM <====> TAF Begin  **************************/
    APS_EHSM_PDN_ACTIVATE_REQ_STRU                          stAPS_EHSM_PDN_ACTIVATE_REQ_STRU;
    EHSM_APS_PDN_ACTIVATE_CNF_STRU                          stEHSM_APS_PDN_ACTIVATE_CNF_STRU;
    EHSM_APS_PDN_ACTIVATE_IND_STRU                          stEHSM_APS_PDN_ACTIVATE_IND_STRU;
    APS_EHSM_PDN_DEACTIVATE_REQ_STRU                        stAPS_EHSM_PDN_DEACTIVATE_REQ_STRU;
    EHSM_APS_PDN_DEACTIVATE_CNF_STRU                        stEHSM_APS_PDN_DEACTIVATE_CNF_STRU;
    EHSM_APS_PDN_DEACTIVATE_IND_STRU                        stEHSM_APS_PDN_DEACTIVATE_IND_STRU;
    EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU                 stEHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU;
    APS_EHSM_RECONN_REQ_STRU                                stAPS_EHSM_RECONN_REQ_STRU;
    EHSM_APS_RECONN_CNF_STRU                                stEHSM_APS_RECONN_CNF_STRU;
    EHSM_APS_PDN_INFO_CHANGE_IND_STRU                       stEHSM_APS_PDN_INFO_CHANGE_IND_STRU;
    EHSM_APS_APN_AMBR_STRU                                  stEHSM_APS_APN_AMBR_STRU;
    EHSM_APS_PDN_CHANGE_INFO_STRU                           stEHSM_APS_PDN_CHANGE_INFO_STRU;
    APS_EHSM_PS_RAT_TYPE_NOTIFY_STRU                        stAPS_EHSM_PS_RAT_TYPE_NOTIFY_STRU;
    APS_EHSM_PDN_CONTEXT_INFO_NOTIFY_STRU                   stAPS_EHSM_PDN_CONTEXT_INFO_NOTIFY_STRU;
    APS_EHSM_LOC_DETACH_NOTIFY_STRU                         stAPS_EHSM_LOC_DETACH_NOTIFY_STRU;
    APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU                     stAPS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU;
    APS_EHSM_DISC_NOTIFY_STRU                               stAPS_EHSM_DISC_NOTIFY_STRU;
    /**************************  EHSM <====> TAF End  ***************************/

    /*************************  EHSM <====> PPPC Begin  *************************/
    CNAS_CTTF_EHRPD_ATTACH_REQ_STRU                         stCNAS_CTTF_EHRPD_ATTACH_REQ_STRU;
    CTTF_CNAS_EHRPD_ATTACH_CNF_STRU                         stCTTF_CNAS_EHRPD_ATTACH_CNF_STRU;
    CNAS_CTTF_EHRPD_DETACH_REQ_STRU                         stCNAS_CTTF_EHRPD_DETACH_REQ_STRU;
    CTTF_CNAS_EHRPD_DETACH_CNF_STRU                         stCTTF_CNAS_EHRPD_DETACH_CNF_STRU;
    CTTF_CNAS_EHRPD_DETACH_IND_STRU                         stCTTF_CNAS_EHRPD_DETACH_IND_STRU;
    CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU                       stCNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU;
    CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU                       stCTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU;
    CNAS_CTTF_EHRPD_PDN_DISC_REQ_STRU                       stCNAS_CTTF_EHRPD_PDN_DISC_REQ_STRU;
    CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU                       stCTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU;
    CTTF_CNAS_EHRPD_PDN_DISC_IND_STRU                       stCTTF_CNAS_EHRPD_PDN_DISC_IND_STRU;
    CNAS_CTTF_EHRPD_PDN_LOC_DISC_IND_STRU                   stCNAS_CTTF_EHRPD_PDN_LOC_DISC_IND_STRU;
    CNAS_CTTF_EHRPD_LOC_DETACH_IND_STRU                     stCNAS_CTTF_EHRPD_LOC_DETACH_IND_STRU;
    CTTF_CNAS_EHRPD_MODIFY_IND_STRU                         stCTTF_CNAS_EHRPD_MODIFY_IND_STRU;

    /**************************  EHSM <====> PPPC End  **************************/

    /*************************  EHSM <====> ESM Begin  **************************/
    EHSM_ESM_CLEAR_ALL_BEARER_NOTIFY_STRU                   stEHSM_ESM_CLEAR_ALL_BEARER_NOTIFY_STRU;
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU                         stEHSM_ESM_SYNC_PDN_INFO_IND_STRU;
    ESM_EHSM_CLEAR_ALL_BEARER_NOTIFY_STRU                   stESM_EHSM_CLEAR_ALL_BEARER_NOTIFY_STRU;
    ESM_EHSM_SYNC_PDN_INFO_IND_STRU                         stESM_EHSM_SYNC_PDN_INFO_IND_STRU;
    /**************************  EHSM <====> ESM End  ***************************/

    /*************************  EHSM <====> HSM Begin  **************************/
    EHSM_HSM_CONN_EST_REQ_STRU                              stEHSM_HSM_CONN_EST_REQ_STRU;
    HSM_EHSM_CONN_EST_CNF_STRU                              stHSM_EHSM_CONN_EST_CNF_STRU;
    EHSM_HSM_DISC_REQ_STRU                                  stEHSM_HSM_DISC_REQ_STRU;
    HSM_EHSM_DISC_CNF_STRU                                  stHSM_EHSM_DISC_CNF_STRU;
    HSM_EHSM_DISC_IND_STRU                                  stHSM_EHSM_DISC_IND_STRU;
    HSM_EHSM_IRAT_LTE_IND_STRU                              stHSM_EHSM_IRAT_LTE_IND_STRU;
    HSM_EHSM_SESSION_INFO_IND_STRU                          stHSM_EHSM_SESSION_INFO_IND_STRU;
    EHSM_HSM_EHRPD_NOT_AVAILABLE_IND_STRU                   stEHSM_HSM_EHRPD_NOT_AVAILABLE_IND_STRU;
    HSM_EHSM_SUSPEND_IND_STRU                               stHSM_EHSM_SUSPEND_IND_STRU;
    EHSM_HSM_LTE_REG_SUCCESS_IND_STRU                       stEHSM_HSM_LTE_REG_SUCCESS_IND_STRU;
    HSM_EHSM_CONNECT_IND_STRU                               stHSM_EHSM_CONNECT_IND_STRU;
    /**************************  EHSM <====> HSM End  ***************************/

    /*************************  EHSM <====> HSD Begin  **************************/
    HSD_EHSM_START_REQ_STRU                                 stHSD_EHSM_START_REQ_STRU;
    EHSM_HSD_START_CNF_STRU                                 stEHSM_HSD_START_CNF_STRU;
    HSD_EHSM_POWER_OFF_REQ_STRU                             stHSD_EHSM_POWER_OFF_REQ_STRU;
    EHSM_HSD_POWER_OFF_CNF_STRU                             stEHSM_HSD_POWER_OFF_CNF_STRU;
    HSD_EHSM_POWER_SAVE_REQ_STRU                            stHSD_EHSM_POWER_SAVE_REQ_STRU;
    EHSM_HSD_POWER_SAVE_CNF_STRU                            stEHSM_HSD_POWER_SAVE_CNF_STRU;
    /**************************  EHSM <====> HSD End  ***************************/
}

/*****************************************************************************
 函 数 名  : ELF_NAS_STRU_TraceTable_HSM
 功能描述  : TraceTable中HSM的消息结构
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : w00351686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_NAS_STRU_TraceTable_HSM(void)
{
    /************************** HSM <====> TAF Begin  **************************/
    APS_HSM_ORIG_REQ_STRU                                   stAPS_HSM_ORIG_REQ_STRU;
    HSM_APS_ORIG_CNF_STRU                                   stHSM_APS_ORIG_CNF_STRU;
    HSM_APS_CONNECT_IND_STRU                                stHSM_APS_CONNECT_IND_STRU;
    APS_HSM_CONNECT_RSP_STRU                                stAPS_HSM_CONNECT_RSP_STRU;
    APS_HSM_DISC_REQ_STRU                                   stAPS_HSM_DISC_REQ_STRU;
    HSM_APS_DISC_CNF_STRU                                   stHSM_APS_DISC_CNF_STRU;
    HSM_APS_DISC_IND_STRU                                   stHSM_APS_DISC_IND_STRU;
    HSM_APS_LOC_CHANGED_IND_STRU                            stHSM_APS_LOC_CHANGED_IND_STRU;
    APS_HSM_1X_TO_HRPD_HANDOFF_REQ_STRU                     stAPS_HSM_1X_TO_HRPD_HANDOFF_REQ_STRU;
    HSM_APS_1X_TO_HRPD_HANDOFF_CNF_STRU                     stHSM_APS_1X_TO_HRPD_HANDOFF_CNF_STRU;
    HSM_APS_HRPD_AVAILABLE_IND_STRU                         stHSM_APS_HRPD_AVAILABLE_IND_STRU;
    /************************** HSM <====> TAF End  **************************/

    /************************** HSM <====> HSD Begin  **************************/
    HSD_HSM_START_REQ_STRU                                  stHSD_HSM_START_REQ_STRU;
    HSM_HSD_START_CNF_STRU                                  stHSM_HSD_START_CNF_STRU;
    HSD_HSM_POWEROFF_REQ_STRU                               stHSD_HSM_POWEROFF_REQ_STRU;
    HSM_HSD_POWEROFF_CNF_STRU                               stHSM_HSD_POWEROFF_CNF_STRU;
    HSD_HSM_POWER_SAVE_REQ_STRU                             stHSD_HSM_POWER_SAVE_REQ_STRU;
    HSM_HSD_POWER_SAVE_CNF_STRU                             stHSM_HSD_POWER_SAVE_CNF_STRU;
    HSD_HSM_SYSTEM_ACQUIRED_IND_STRU                        stHSD_HSM_SYSTEM_ACQUIRED_IND_STRU;
    HSD_HSM_OVERHEAD_MSG_IND_STRU                           stHSD_HSM_OVERHEAD_MSG_IND_STRU;
    HSD_HSM_OHM_NOT_CURRENT_IND_STRU                        stHSD_HSM_OHM_NOT_CURRENT_IND_STRU;
    HSM_HSD_SESSION_NEG_RESULT_IND_STRU                     stHSM_HSD_SESSION_NEG_RESULT_IND_STRU;
    HSM_HSD_SESSION_OPEN_OR_NEG_END_IND_STRU                stHSM_HSD_SESSION_OPEN_OR_NEG_END_IND_STRU;
    HSM_HSD_SESSION_OPEN_OR_NEG_START_IND_STRU              stHSM_HSD_SESSION_OPEN_OR_NEG_START_IND_STRU;
    HSM_HSD_CAS_STATUS_IND_STRU                             stHSM_HSD_CAS_STATUS_IND_STRU;
    HSM_HSD_CONN_OPEN_IND_STRU                              stHSM_HSD_CONN_OPEN_IND_STRU;
    HSD_HSM_SUSPEND_IND_STRU                                stHSD_HSM_SUSPEND_IND_STRU;
    HSD_HSM_RESUME_IND_STRU                                 stHSD_HSM_RESUME_IND_STRU;
    HSD_HSM_IRAT_FROM_LTE_IND_STRU                          stHSD_HSM_IRAT_FROM_LTE_IND_STRU;
    HSD_HSM_IRAT_TO_LTE_IND_STRU                            stHSD_HSM_IRAT_TO_LTE_IND_STRU;
    HSD_HSM_PILOT_SEARCH_FAIL_NTF_STRU                      stHSD_HSM_PILOT_SEARCH_FAIL_NTF_STRU;
    /************************** HSM <====> HSD End  **************************/

    /************************** HSM <====> HSM Begin  **************************/
    CNAS_HSM_HSM_UATI_REQ_STRU                              stCNAS_HSM_HSM_UATI_REQ_STRU;
    CNAS_HSM_HSM_SESSION_ACTIVE_REQ_STRU                    stCNAS_HSM_HSM_SESSION_ACTIVE_REQ_STRU;
    CNAS_HSM_HSM_SESSION_DEACTIVE_REQ_STRU                  stCNAS_HSM_HSM_SESSION_DEACTIVE_REQ_STRU;
    CNAS_HSM_HSM_UATI_REQUEST_RESULT_IND_STRU               stCNAS_HSM_HSM_UATI_REQUEST_RESULT_IND_STRU;
    CNAS_HSM_HSM_SESSION_ACTIVE_RESULT_IND_STRU             stCNAS_HSM_HSM_SESSION_ACTIVE_RESULT_IND_STRU;
    CNAS_HSM_HSM_SESSION_DEACTIVE_RESULT_IND_STRU           stCNAS_HSM_HSM_SESSION_DEACTIVE_RESULT_IND_STRU;
    CNAS_HSM_HSM_READ_SWITCH_ON_STRU                        stCNAS_HSM_HSM_READ_SWITCH_ON_STRU;
    CNAS_HSM_HSM_SWITCH_ON_RESULT_IND_STRU                  stCNAS_HSM_HSM_SWITCH_ON_RESULT_IND_STRU;
    CNAS_HSM_HSM_SESSION_CLOSE_IND_STRU                     stCNAS_HSM_HSM_SESSION_CLOSE_IND_STRU;
    CNAS_HSM_HSM_CONN_MNMT_REQ_STRU                         stCNAS_HSM_HSM_CONN_MNMT_REQ_STRU;
    CNAS_HSM_HSM_CONN_MNMT_RESULT_IND_STRU                  stCNAS_HSM_HSM_CONN_MNMT_RESULT_IND_STRU;
    CNAS_HSM_HSM_HRPD_PA_RAT_MODE_NTF_STRU                  stCNAS_HSM_HSM_HRPD_PA_RAT_MODE_NTF_STRU;
    CNAS_HSM_LOG_HWID_INFO_STRU                             stCNAS_HSM_LOG_HWID_INFO_STRU;
    CNAS_HSM_LOG_BUFFER_MSG_INFO_STRU                       stCNAS_HSM_LOG_BUFFER_MSG_INFO_STRU;
    CNAS_HSM_MNTN_ELF_LOG_MAIN_FSM_INFO_STRU                stCNAS_HSM_MNTN_ELF_LOG_MAIN_FSM_INFO_STRU;
    CNAS_HSM_MNTN_ELF_LOG_SUB_FSM_INFO_STRU                 stCNAS_HSM_MNTN_ELF_LOG_SUB_FSM_INFO_STRU;
    CNAS_HSM_LOG_CODEC_RESULT_IND_STRU                      stCNAS_HSM_LOG_CODEC_RESULT_IND_STRU;
    CNAS_HSM_LOG_MNTN_UATI_REQ_STRU                         stCNAS_HSM_LOG_MNTN_UATI_REQ_STRU;
    CNAS_HSM_LOG_MNTN_UATI_ASSIGN_STRU                      stCNAS_HSM_LOG_MNTN_UATI_ASSIGN_STRU;
    CNAS_HSM_LOG_MNTN_UATI_COMP_STRU                        stCNAS_HSM_LOG_MNTN_UATI_COMP_STRU;
    CNAS_HSM_LOG_MNTN_HARDWARE_ID_REQ_STRU                  stCNAS_HSM_LOG_MNTN_HARDWARE_ID_REQ_STRU;
    CNAS_HSM_LOG_MNTN_HARDWARE_ID_RESP_STRU                 stCNAS_HSM_LOG_MNTN_HARDWARE_ID_RESP_STRU;
    CNAS_HSM_LOG_MNTN_SESSION_CLOSE_STRU                    stCNAS_HSM_LOG_MNTN_SESSION_CLOSE_STRU;
    CNAS_HSM_LOG_MNTN_KEEP_ALIVE_REQ_MSG_STRU               stCNAS_HSM_LOG_MNTN_KEEP_ALIVE_REQ_MSG_STRU;
    CNAS_HSM_LOG_MNTN_KEEP_ALIVE_RESP_MSG_STRU              stCNAS_HSM_LOG_MNTN_KEEP_ALIVE_RESP_MSG_STRU;
    CNAS_HSM_LOG_MNTN_AMP_SMP_NEG_ATTRIB_IND_STRU           stCNAS_HSM_LOG_MNTN_AMP_SMP_NEG_ATTRIB_IND_STRU;
    CNAS_HSM_MNTN_LOG_SESSION_DEACT_INFO_STRU               stCNAS_HSM_MNTN_LOG_SESSION_DEACT_INFO_STRU;
    CNAS_HSM_LOG_MNTN_RCV_ATI_LIST_INFO_STRU                stCNAS_HSM_LOG_MNTN_RCV_ATI_LIST_INFO_STRU;
    CNAS_HSM_MNTN_LOG_SESSION_KEEP_ALIVE_INFO_IND_STRU      stCNAS_HSM_MNTN_LOG_SESSION_KEEP_ALIVE_INFO_IND_STRU;
    CNAS_HSM_MNTN_LOG_READ_CARD_INFO_IND_STRU               stCNAS_HSM_MNTN_LOG_READ_CARD_INFO_IND_STRU;
    CNAS_HSM_MNTN_LOG_QUIT_SLAVE_STATE_INFO_IND_STRU        stCNAS_HSM_MNTN_LOG_QUIT_SLAVE_STATE_INFO_IND_STRU;
    CNAS_HSM_MNTN_LOG_BUFF_MSG_QUEUE_FULL_IND_STRU          stCNAS_HSM_MNTN_LOG_BUFF_MSG_QUEUE_FULL_IND_STRU;
    CNAS_HSM_MNTN_LOG_SESSION_RECOVERY_JUDGE_INFO_IND_STRU  stCNAS_HSM_MNTN_LOG_SESSION_RECOVERY_JUDGE_INFO_IND_STRU;
    CNAS_HSM_MNTN_LOG_SESSION_OPERATE_CTRL_INFO_IND_STRU    stCNAS_HSM_MNTN_LOG_SESSION_OPERATE_CTRL_INFO_IND_STRU;
    CNAS_HSM_MNTN_LOG_CONN_MNMT_STATUS_INFO_IND_STRU        stCNAS_HSM_MNTN_LOG_CONN_MNMT_STATUS_INFO_IND_STRU;
    CNAS_HSM_MNTN_LOG_DISCARD_MSG_INFO_IND_STRU             stCNAS_HSM_MNTN_LOG_DISCARD_MSG_INFO_IND_STRU;
    /************************** HSM <====> HSM End  **************************/

    /************************** HSM <====> TIMER Begin  **************************/
    CNAS_MNTN_ELF_LOG_HSM_TIMER_INFO_IND_STRU               stCNAS_MNTN_ELF_LOG_HSM_TIMER_INFO_IND_STRU;
    /************************** HSM <====> TIMER Begin  **************************/

    /************************** HSM <====> MMA Begin  **************************/
    HSM_MMA_HRPD_SYS_INFO_IND_STRU                          stHSM_MMA_HRPD_SYS_INFO_IND_STRU;
    HSM_MMA_HARDWARE_SYS_INFO_IND_STRU                      stHSM_MMA_HARDWARE_SYS_INFO_IND_STRU;
    /************************** HSM <====> MMA Begin  **************************/
}

/*****************************************************************************
 函 数 名  : ELF_NAS_STRU_TraceTable_MSCC
 功能描述  : TraceTable中MSCC的消息结构
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : w00351686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_NAS_STRU_TraceTable_MSCC(void)
{

    /******************* 发送模块：MSCC，接收模块：HSD Begin  *******************/
    MSCC_HSD_START_REQ_STRU                                 stMSCC_HSD_START_REQ_STRU;
    MSCC_HSD_POWER_OFF_REQ_STRU                             stMSCC_HSD_POWER_OFF_REQ_STRU;
    MSCC_HSD_SYSTEM_ACQUIRE_REQ_STRU                        stMSCC_HSD_SYSTEM_ACQUIRE_REQ_STRU;
    MSCC_HSD_DATA_CALL_START_NTF_STRU                       stMSCC_HSD_DATA_CALL_START_NTF_STRU;
    MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ_STRU              stMSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ_STRU;
    MSCC_HSD_DATA_CALL_SUCC_NTF_STRU                        stMSCC_HSD_DATA_CALL_SUCC_NTF_STRU;
    MSCC_HSD_DATA_CALL_END_NTF_STRU                         stMSCC_HSD_DATA_CALL_END_NTF_STRU;
    MSCC_HSD_1X_SYS_CHANGE_IND_STRU                         stMSCC_HSD_1X_SYS_CHANGE_IND_STRU;
    MSCC_HSD_DISABLE_LTE_NTF_STRU                           stMSCC_HSD_DISABLE_LTE_NTF_STRU;
    MSCC_HSD_QRY_HRPD_SYS_INFO_REQ_STRU                     stMSCC_HSD_QRY_HRPD_SYS_INFO_REQ_STRU;
    MSCC_HSD_BG_SEARCH_REQ_STRU                             stMSCC_HSD_BG_SEARCH_REQ_STRU;
    MSCC_HSD_SYS_CFG_REQ_STRU                               stMSCC_HSD_SYS_CFG_REQ_STRU;
    MSCC_HSD_POWER_SAVE_REQ_STRU                            stMSCC_HSD_POWER_SAVE_REQ_STRU;
    MSCC_HSD_STOP_BG_SEARCH_REQ_STRU                        stMSCC_HSD_STOP_BG_SEARCH_REQ_STRU;
    MSCC_HSD_SRV_ACQ_REQ_STRU                               stMSCC_HSD_SRV_ACQ_REQ_STRU;
    MSCC_HSD_BEGIN_SESSION_NOTIFY_STRU                      stMSCC_HSD_BEGIN_SESSION_NOTIFY_STRU;
    MSCC_HSD_END_SESSION_NOTIFY_STRU                        stMSCC_HSD_END_SESSION_NOTIFY_STRU;
    MSCC_HSD_HDR_CSQ_SET_REQ_STRU                           stMSCC_HSD_HDR_CSQ_SET_REQ_STRU;
    MSCC_HSD_CFREQ_LOCK_NTF_STRU                            stMSCC_HSD_CFREQ_LOCK_NTF_STRU;
    /******************* 发送模块：MSCC，接收模块：HSD End  *******************/

    /******************* 发送模块：MSCC，接收模块：MMC Begin  *******************/
    MSCC_MMC_START_REQ_STRU                                 stMSCC_MMC_START_REQ_STRU;
    MSCC_MMC_SIGN_REPORT_REQ_STRU                           stMSCC_MMC_SIGN_REPORT_REQ_STRU;
    MSCC_MMC_MODE_CHANGE_REQ_STRU                           stMSCC_MMC_MODE_CHANGE_REQ_STRU;
    MSCC_MMC_ATTACH_REQ_STRU                                stMSCC_MMC_ATTACH_REQ_STRU;
    MSCC_MMC_DETACH_REQ_STRU                                stMSCC_MMC_DETACH_REQ_STRU;
    MSCC_MMC_PLMN_LIST_REQ_STRU                             stMSCC_MMC_PLMN_LIST_REQ_STRU;
    MSCC_MMC_PLMN_LIST_ABORT_REQ_STRU                       stMSCC_MMC_PLMN_LIST_ABORT_REQ_STRU;
    MSCC_MMC_PLMN_USER_RESEL_REQ_STRU                       stMSCC_MMC_PLMN_USER_RESEL_REQ_STRU;
    MSCC_MMC_PLMN_SPECIAL_REQ_STRU                          stMSCC_MMC_PLMN_SPECIAL_REQ_STRU;
    MSCC_MMC_POWER_OFF_REQ_STRU                             stMSCC_MMC_POWER_OFF_REQ_STRU;
    MSCC_MMC_SYS_CFG_SET_REQ_STRU                           stMSCC_MMC_SYS_CFG_SET_REQ_STRU;
    MSCC_MMC_PLMN_SEARCH_REQ_STRU                           stMSCC_MMC_PLMN_SEARCH_REQ_STRU;
    MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU                stMSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU;
    MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU                      stMSCC_MMC_OM_MAINTAIN_INFO_IND_STRU;
    MSCC_MMC_UPDATE_UPLMN_NTF_STRU                          stMSCC_MMC_UPDATE_UPLMN_NTF_STRU;
    MSCC_MMC_EOPLMN_SET_REQ_STRU                            stMSCC_MMC_EOPLMN_SET_REQ_STRU;
    MSCC_MMC_NET_SCAN_REQ_STRU                              stMSCC_MMC_NET_SCAN_REQ_STRU;
    MSCC_MMC_ABORT_NET_SCAN_REQ_STRU                        stMSCC_MMC_ABORT_NET_SCAN_REQ_STRU;
    MSCC_MMC_OTHER_MODEM_INFO_NOTIFY_STRU                   stMSCC_MMC_OTHER_MODEM_INFO_NOTIFY_STRU;
    MSCC_MMC_NCELL_INFO_NOTIFY_STRU                         stMSCC_MMC_NCELL_INFO_NOTIFY_STRU;
    MSCC_MMC_PS_TRANSFER_NOTIFY_STRU                        stMSCC_MMC_PS_TRANSFER_NOTIFY_STRU;
    MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU                      stMSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU;
    MSCC_MMC_ACQ_REQ_STRU                                   stMSCC_MMC_ACQ_REQ_STRU;
    MSCC_MMC_REG_REQ_STRU                                   stMSCC_MMC_REG_REQ_STRU;
    MSCC_MMC_POWER_SAVE_REQ_STRU                            stMSCC_MMC_POWER_SAVE_REQ_STRU;
    MSCC_MMC_SRV_ACQ_REQ_STRU                               stMSCC_MMC_SRV_ACQ_REQ_STRU;
    MSCC_MMC_BEGIN_SESSION_NOTIFY_STRU                      stMSCC_MMC_BEGIN_SESSION_NOTIFY_STRU;
    MSCC_MMC_END_SESSION_NOTIFY_STRU                        stMSCC_MMC_END_SESSION_NOTIFY_STRU;
    MSCC_MMC_IMS_SRV_INFO_NOTIFY_STRU                       stMSCC_MMC_IMS_SRV_INFO_NOTIFY_STRU;
    MSCC_MMC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU       stMSCC_MMC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU;
    MSCC_MMC_CFPLMN_SET_REQ_STRU                            stMSCC_MMC_CFPLMN_SET_REQ_STRU;
    MSCC_MMC_CFPLMN_QUERY_REQ_STRU                          stMSCC_MMC_CFPLMN_QUERY_REQ_STRU;
    MSCC_MMC_PREF_PLMN_SET_REQ_STRU                         stMSCC_MMC_PREF_PLMN_SET_REQ_STRU;
    MSCC_MMC_PREF_PLMN_QUERY_REQ_STRU                       stMSCC_MMC_PREF_PLMN_QUERY_REQ_STRU;
    MSCC_MMC_IMS_SWITCH_STATE_IND_STRU                      stMSCC_MMC_IMS_SWITCH_STATE_IND_STRU;
    MSCC_MMC_VOICE_DOMAIN_CHANGE_IND_STRU                   stMSCC_MMC_VOICE_DOMAIN_CHANGE_IND_STRU;
    MSCC_MMC_BG_SEARCH_REQ_STRU                             stMSCC_MMC_BG_SEARCH_REQ_STRU;
    MSCC_MMC_INTERSYS_HRPD_NTF_STRU                         stMSCC_MMC_INTERSYS_HRPD_NTF_STRU;
    MSCC_MMC_STOP_BG_SEARCH_REQ_STRU                        stMSCC_MMC_STOP_BG_SEARCH_REQ_STRU;
    MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ_STRU                  stMSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ_STRU;
    MSCC_MMC_AUTO_RESEL_SET_REQ_STRU                        stMSCC_MMC_AUTO_RESEL_SET_REQ_STRU;
    MSCC_MMC_GET_GEO_REQ_STRU                               stMSCC_MMC_GET_GEO_REQ_STRU;
    MSCC_MMC_STOP_GET_GEO_REQ_STRU                          stMSCC_MMC_STOP_GET_GEO_REQ_STRU;
    MSCC_MMC_DPLMN_SET_REQ_STRU                             stMSCC_MMC_DPLMN_SET_REQ_STRU;
    MSCC_MMC_CSG_LIST_SEARCH_REQ_STRU                       stMSCC_MMC_CSG_LIST_SEARCH_REQ_STRU;
    MSCC_MMC_CSG_LIST_ABORT_REQ_STRU                        stMSCC_MMC_CSG_LIST_ABORT_REQ_STRU;
    MSCC_MMC_CL_ASSOCIATED_INFO_NTF_STRU                    stMSCC_MMC_CL_ASSOCIATED_INFO_NTF_STRU;
    MSCC_MMC_MMSS_INFO_NTF_STRU                             stMSCC_MMC_MMSS_INFO_NTF_STRU;
    MSCC_MMC_CL_INTERSYS_START_NTF_STRU                    stMSCC_MMC_CL_INTERSYS_START_NTF_STRU;
    /******************* 发送模块：MSCC，接收模块：MMC End  *******************/

    /******************* 发送模块：MSCC，接收模块：MMA Begin  *******************/
    MSCC_MMA_START_CNF_STRU                                 stMSCC_MMA_START_CNF_STRU;
    MSCC_MMA_3GPP_SYS_INFO_IND_STRU                         stMSCC_MMA_3GPP_SYS_INFO_IND_STRU;
    MSCC_MMA_SERVICE_STATUS_IND_STRU                        stMSCC_MMA_SERVICE_STATUS_IND_STRU;
    MSCC_MMA_MM_INFO_IND_STRU                               stMSCC_MMA_MM_INFO_IND_STRU;
    MSCC_MMA_ATTACH_CNF_STRU                                stMSCC_MMA_ATTACH_CNF_STRU;
    MSCC_MMA_DETACH_CNF_STRU                                stMSCC_MMA_DETACH_CNF_STRU;
    MSCC_MMA_DETACH_IND_STRU                                stMSCC_MMA_DETACH_IND_STRU;
    MSCC_MMA_PLMN_LIST_CNF_STRU                             stMSCC_MMA_PLMN_LIST_CNF_STRU;
    MSCC_MMA_PLMN_LIST_REJ_STRU                             stMSCC_MMA_PLMN_LIST_REJ_STRU;
    MSCC_MMA_COVERAGE_AREA_IND_STRU                         stMSCC_MMA_COVERAGE_AREA_IND_STRU;
    MSCC_MMA_POWER_OFF_CNF_STRU                             stMSCC_MMA_POWER_OFF_CNF_STRU;
    MSCC_MMA_RSSI_IND_STRU                                  stMSCC_MMA_RSSI_IND_STRU;
    MSCC_MMA_PLMN_SPECIAL_SEL_CNF_STRU                      stMSCC_MMA_PLMN_SPECIAL_SEL_CNF_STRU;
    MSCC_MMA_DATATRAN_ATTRI_IND_STRU                        stMSCC_MMA_DATATRAN_ATTRI_IND_STRU;
    MSCC_MMA_SYS_CFG_SET_CNF_STRU                           stMSCC_MMA_SYS_CFG_SET_CNF_STRU;
    MSCC_MMA_SYSTEM_ACQUIRE_END_IND_STRU                    stMSCC_MMA_SYSTEM_ACQUIRE_END_IND_STRU;
    MSCC_MMA_PLMN_LIST_ABORT_CNF_STRU                       stMSCC_MMA_PLMN_LIST_ABORT_CNF_STRU;
    MSCC_MMA_SPEC_PLMN_SEARCH_ABORT_CNF_STRU                stMSCC_MMA_SPEC_PLMN_SEARCH_ABORT_CNF_STRU;
    MSCC_MMA_UMTS_CIPHER_INFO_IND_STRU                      stMSCC_MMA_UMTS_CIPHER_INFO_IND_STRU;
    MSCC_MMA_GPRS_CIPHER_INFO_IND_STRU                      stMSCC_MMA_GPRS_CIPHER_INFO_IND_STRU;
    MSCC_MMA_PLMN_SPECIAL_SEL_REJ_STRU                      stMSCC_MMA_PLMN_SPECIAL_SEL_REJ_STRU;
    MSCC_MMA_AC_INFO_CHANGE_IND_STRU                        stMSCC_MMA_AC_INFO_CHANGE_IND_STRU;
    MSCC_MMA_PLMN_RESEL_CNF_STRU                            stMSCC_MMA_PLMN_RESEL_CNF_STRU;
    MSCC_MMA_REG_RESULT_IND_STRU                            stMSCC_MMA_REG_RESULT_IND_STRU;
    MSCC_MMA_SYSTEM_ACQUIRE_START_IND_STRU                  stMSCC_MMA_SYSTEM_ACQUIRE_START_IND_STRU;
    MSCC_MMA_EOPLMN_SET_CNF_STRU                            stMSCC_MMA_EOPLMN_SET_CNF_STRU;
    MSCC_MMA_USIM_AUTH_FAIL_IND_STRU                        stMSCC_MMA_USIM_AUTH_FAIL_IND_STRU;
    MSCC_MMA_NET_SCAN_CNF_STRU                              stMSCC_MMA_NET_SCAN_CNF_STRU;
    MSCC_MMA_ABORT_NET_SCAN_CNF_STRU                        stMSCC_MMA_ABORT_NET_SCAN_CNF_STRU;
    MSCC_MMA_NETWORK_CAPABILITY_INFO_IND_STRU               stMSCC_MMA_NETWORK_CAPABILITY_INFO_IND_STRU;
    MSCC_MMA_CAMP_ON_IND_STRU_STRU                          stMSCC_MMA_CAMP_ON_IND_STRU_STRU;
    MSCC_MMA_EPLMN_INFO_IND_STRU                            stMSCC_MMA_EPLMN_INFO_IND_STRU;
    MSCC_MMA_CS_SERVICE_CONN_STATUS_IND_STRU                stMSCC_MMA_CS_SERVICE_CONN_STATUS_IND_STRU;
    MSCC_MMA_SERV_REJ_IND_STRU                              stMSCC_MMA_SERV_REJ_IND_STRU;
    MSCC_MMA_ACQ_CNF_STRU                                   stMSCC_MMA_ACQ_CNF_STRU;
    MSCC_MMA_REG_CNF_STRU                                   stMSCC_MMA_REG_CNF_STRU;
    MSCC_MMA_POWER_SAVE_CNF_STRU                            stMSCC_MMA_POWER_SAVE_CNF_STRU;
    MSCC_MMA_ACQ_IND_STRU                                   stMSCC_MMA_ACQ_IND_STRU;
    MSCC_MMA_PS_SERVICE_CONN_STATUS_IND_STRU                stMSCC_MMA_PS_SERVICE_CONN_STATUS_IND_STRU;
    MSCC_MMA_RF_AVAILABLE_IND_STRU                          stMSCC_MMA_RF_AVAILABLE_IND_STRU;
    MSCC_MMA_SRV_ACQ_CNF_STRU                               stMSCC_MMA_SRV_ACQ_CNF_STRU;
    MSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND_STRU             stMSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND_STRU;
    MSCC_MMA_IMS_VOICE_CAP_IND_STRU                         stMSCC_MMA_IMS_VOICE_CAP_IND_STRU;
    MSCC_MMA_1X_SYSTEM_SERVICE_INFO_IND_STRU                stMSCC_MMA_1X_SYSTEM_SERVICE_INFO_IND_STRU;
    MSCC_MMA_CDMACSQ_SET_CNF_STRU                           stMSCC_MMA_CDMACSQ_SET_CNF_STRU;
    MSCC_MMA_CDMACSQ_IND_STRU                               stMSCC_MMA_CDMACSQ_IND_STRU;
    MSCC_MMA_HRPD_SERVICE_STATUS_IND_STRU                   stMSCC_MMA_HRPD_SERVICE_STATUS_IND_STRU;
    MSCC_MMA_CFPLMN_SET_CNF_STRU                            stMSCC_MMA_CFPLMN_SET_CNF_STRU;
    MSCC_MMA_CFPLMN_QUERY_CNF_STRU                          stMSCC_MMA_CFPLMN_QUERY_CNF_STRU;
    MSCC_MMA_PREF_PLMN_SET_CNF_STRU                         stMSCC_MMA_PREF_PLMN_SET_CNF_STRU;
    MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU                       stMSCC_MMA_PREF_PLMN_QUERY_CNF_STRU;
    MSCC_MMA_HRPD_OVERHEAD_MSG_IND_STRU                     stMSCC_MMA_HRPD_OVERHEAD_MSG_IND_STRU;
    MSCC_MMA_HRPD_SYS_ACQ_CNF_STRU                          stMSCC_MMA_HRPD_SYS_ACQ_CNF_STRU;
    MSCC_MMA_1X_SYSTEM_TIME_IND_STRU                        stMSCC_MMA_1X_SYSTEM_TIME_IND_STRU;
    MSCC_MMA_IMS_SWITCH_STATE_IND_STRU                      stMSCC_MMA_IMS_SWITCH_STATE_IND_STRU;
    MSCC_MMA_IMS_START_CNF_STRU                             stMSCC_MMA_IMS_START_CNF_STRU;
    MSCC_MMA_IMS_STOP_CNF_STRU                              stMSCC_MMA_IMS_STOP_CNF_STRU;
    MSCC_MMA_HANDSET_INFO_QRY_CNF_STRU                      stMSCC_MMA_HANDSET_INFO_QRY_CNF_STRU;
    MSCC_MMA_GET_GEO_CNF_STRU                               stMSCC_MMA_GET_GEO_CNF_STRU;
    MSCC_MMA_STOP_GET_GEO_CNF_STRU                          stMSCC_MMA_STOP_GET_GEO_CNF_STRU;
    MSCC_MMA_1X_SID_NID_IND_STRU                            stMSCC_MMA_1X_SID_NID_IND_STRU;
    MSCC_MMA_SET_CSIDLIST_CNF_STRU                          stMSCC_MMA_SET_CSIDLIST_CNF_STRU;
    MSCC_MMA_1X_EMC_CALL_BACK_IND_STRU                      stMSCC_MMA_1X_EMC_CALL_BACK_IND_STRU;
    MSCC_MMA_SRCHED_PLMN_INFO_IND_STRU                      stMSCC_MMA_SRCHED_PLMN_INFO_IND_STRU;
    MSCC_MMA_UE_STATE_IND_STRU                              stMSCC_MMA_UE_STATE_IND_STRU;
    MSCC_MMA_SYNC_SERVICE_AVAIL_IND_STRU                    stMSCC_MMA_SYNC_SERVICE_AVAIL_IND_STRU;
    MSCC_MMA_HDR_CSQ_SET_CNF_STRU                           stMSCC_MMA_HDR_CSQ_SET_CNF_STRU;
    MSCC_MMA_HDR_CSQ_IND_STRU                               stMSCC_MMA_HDR_CSQ_IND_STRU;
    MSCC_MMA_DPLMN_SET_CNF_STRU                             stMSCC_MMA_DPLMN_SET_CNF_STRU;
    MSCC_MMA_CSG_LIST_SEARCH_CFN_STRU                       stMSCC_MMA_CSG_LIST_SEARCH_CFN_STRU;
    MSCC_MMA_CSG_LIST_ABORT_CNF_STRU                        stMSCC_MMA_CSG_LIST_ABORT_CNF_STRU;
    MSCC_MMA_CSG_LIST_REJ_STRU                              stMSCC_MMA_CSG_LIST_REJ_STRU;
    MSCC_MMA_DATA_CALL_REDIAL_SYS_ACQ_IND_STRU              stMSCC_MMA_DATA_CALL_REDIAL_SYS_ACQ_IND_STRU;
    /******************* 发送模块：MSCC，接收模块：MMA End  *******************/

    /******************* 发送模块：MSCC，接收模块：XSD Begin  *******************/
    MSCC_XSD_START_REQ_STRU                                 stMSCC_XSD_START_REQ_STRU;
    MSCC_XSD_POWER_OFF_REQ_STRU                             stMSCC_XSD_POWER_OFF_REQ_STRU;
    MSCC_XSD_MO_CALL_START_NTF_STRU                         stMSCC_XSD_MO_CALL_START_NTF_STRU;
    MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU            stMSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU;
    MSCC_XSD_MO_CALL_SUCCESS_NTF_STRU                       stMSCC_XSD_MO_CALL_SUCCESS_NTF_STRU;
    MSCC_XSD_1X_MO_CALL_END_NTF_STRU                        stMSCC_XSD_1X_MO_CALL_END_NTF_STRU;
    MSCC_XSD_SYSTEM_ACQUIRE_REQ_STRU                        stMSCC_XSD_SYSTEM_ACQUIRE_REQ_STRU;
    MSCC_XSD_CFREQ_LOCK_NTF_STRU                            stMSCC_XSD_CFREQ_LOCK_NTF_STRU;
    MSCC_XSD_CDMACSQ_SET_REQ_STRU                           stMSCC_XSD_CDMACSQ_SET_REQ_STRU;
    MSCC_XSD_POWER_SAVE_REQ_STRU                            stMSCC_XSD_POWER_SAVE_REQ_STRU;
    MSCC_XSD_CAS_STATUS_IND_STRU                            stMSCC_XSD_CAS_STATUS_IND_STRU;
    MSCC_XSD_SYS_CFG_REQ_STRU                               stMSCC_XSD_SYS_CFG_REQ_STRU;
    MSCC_XSD_SRV_ACQ_REQ_STRU                               stMSCC_XSD_SRV_ACQ_REQ_STRU;
    MSCC_XSD_BEGIN_SESSION_NOTIFY_STRU                      stMSCC_XSD_BEGIN_SESSION_NOTIFY_STRU;
    MSCC_XSD_END_SESSION_NOTIFY_STRU                        stMSCC_XSD_END_SESSION_NOTIFY_STRU;
    MSCC_XSD_HANDSET_INFO_QRY_STRU                          stMSCC_XSD_HANDSET_INFO_QRY_STRU;
    MSCC_XSD_END_EMC_CALLBACK_NTF_STRU                      stMSCC_XSD_END_EMC_CALLBACK_NTF_STRU;
    MSCC_XSD_SET_CSIDLIST_REQ_STRU                          stMSCC_XSD_SET_CSIDLIST_REQ_STRU;
    MSCC_XSD_SID_NID_IND_STRU                               stMSCC_XSD_SID_NID_IND_STRU;
    /******************* 发送模块：MSCC，接收模块：XSD End  *******************/

    /******************* 发送模块：MSCC，接收模块：MSCC Begin  *******************/
    NAS_MSCC_MSCC_SWITCH_ON_RSLT_CNF_STRU                   stNAS_MSCC_MSCC_SWITCH_ON_RSLT_CNF_STRU;
    NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF_STRU                   stNAS_MSCC_MSCC_POWER_OFF_RSLT_CNF_STRU;
    NAS_MSCC_MSCC_SYS_ACQ_STRU                              stNAS_MSCC_MSCC_SYS_ACQ_STRU;
    NAS_MSCC_MSCC_SYS_ACQ_RSLT_CNF_STRU                     stNAS_MSCC_MSCC_SYS_ACQ_RSLT_CNF_STRU;
    NAS_MSCC_MSCC_ABORT_FSM_REQ_STRU                        stNAS_MSCC_MSCC_ABORT_FSM_REQ_STRU;
    NAS_MSCC_MSCC_BSR_RSLT_CNF_STRU                         stNAS_MSCC_MSCC_BSR_RSLT_CNF_STRU;
    NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF_STRU                     stNAS_MSCC_MSCC_SYS_CFG_RSLT_CNF_STRU;
    NAS_MSCC_MNTN_ELF_LOG_FSM_INFO_STRU                     stNAS_MSCC_MNTN_ELF_LOG_FSM_INFO_STRU;
    NAS_MSCC_MNTN_LOG_BUFFER_MSG_INFO_STRU                  stNAS_MSCC_MNTN_LOG_BUFFER_MSG_INFO_STRU;
    NAS_MSCC_MNTN_LOG_MLPL_PARSE_RSLT_STRU                  stNAS_MSCC_MNTN_LOG_MLPL_PARSE_RSLT_STRU;
    NAS_MSCC_MNTN_LOG_MSPL_PARSE_RSLT_STRU                  stNAS_MSCC_MNTN_LOG_MSPL_PARSE_RSLT_STRU;
    NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_STRU             stNAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_STRU;
    NAS_MSCC_MNTN_MSPL_HEADER_STRU                          stNAS_MSCC_MNTN_MSPL_HEADER_STRU;
    NAS_MSCC_MNTN_MSPL_ID_LIST_STRU                         stNAS_MSCC_MNTN_MSPL_ID_LIST_STRU;
    NAS_MSCC_MNTN_MLPL_MSPL_CRC_RSLT_STRU                   stNAS_MSCC_MNTN_MLPL_MSPL_CRC_RSLT_STRU;
    NAS_MSCC_MNTN_MLPL_HEADER_STRU                          stNAS_MSCC_MNTN_MLPL_HEADER_STRU;
    NAS_MSCC_MNTN_MLPL_RECORD_LIST_STRU                     stNAS_MSCC_MNTN_MLPL_RECORD_LIST_STRU;
    NAS_MSCC_MNTN_LOG_DISCARD_SERV_STA_INFO_STRU            stNAS_MSCC_MNTN_LOG_DISCARD_SERV_STA_INFO_STRU;
    NAS_MSCC_MNTN_LOG_BSR_CTRL_INFO_STRU                    stNAS_MSCC_MNTN_LOG_BSR_CTRL_INFO_STRU;
    NAS_MSCC_MNTN_LOG_MMSS_NVIM_CFG_STRU                    stNAS_MSCC_MNTN_LOG_MMSS_NVIM_CFG_STRU;
    NAS_MSCC_MNTN_LOG_MMSS_NVIM_LAST_LOC_INFO_STRU          stNAS_MSCC_MNTN_LOG_MMSS_NVIM_LAST_LOC_INFO_STRU;
    NAS_MSCC_MNTN_LOG_READ_NV_INFO_IND_STRU                 stNAS_MSCC_MNTN_LOG_READ_NV_INFO_IND_STRU;
    NAS_MSCC_MNTN_ELF_LOG_TIMER_INFO_STRU                   stNAS_MSCC_MNTN_ELF_LOG_TIMER_INFO_STRU;
    NAS_MSCC_MSCC_CL_INTERSYS_RSLT_CNF_STRU                 stNAS_MSCC_MSCC_CL_INTERSYS_RSLT_CNF_STRU;
    NAS_DYNLOAD_MNTN_MSG_REGISTER_STRU                      stNAS_DYNLOAD_MNTN_MSG_REGISTER_STRU;
    NAS_DYNLOAD_MNTN_MSG_DEREGISTER_STRU                    stNAS_DYNLOAD_MNTN_MSG_DEREGISTER_STRU;
    NAS_DYNLOAD_MNTN_MSG_EXCUTE_INIT_STRU                   stNAS_DYNLOAD_MNTN_MSG_EXCUTE_INIT_STRU;
    NAS_DYNLOAD_MNTN_MSG_EXCUTE_UNLOAD_STRU                 stNAS_DYNLOAD_MNTN_MSG_EXCUTE_UNLOAD_STRU;
    NAS_DYNLOAD_MNTN_MSG_START_DRV_LOAD_STRU                stNAS_DYNLOAD_MNTN_MSG_START_DRV_LOAD_STRU;
    NAS_DYNLOAD_MNTN_MSG_FINISH_DRV_LOAD_STRU               stNAS_DYNLOAD_MNTN_MSG_FINISH_DRV_LOAD_STRU;
    NAS_MSCC_LOG_FSM_L1_MAIN_CTX_RELATED_INFO_STRU          stNAS_MSCC_LOG_FSM_L1_MAIN_CTX_RELATED_INFO_STRU;

    NAS_MSCC_LOG_CL_SYSTEM_ACQUIRE_STRATEGY_RELATED_INFO_STRU                   stNAS_MSCC_LOG_CL_SYSTEM_ACQUIRE_STRATEGY_RELATED_INFO_STRU;
    /******************* 发送模块：MSCC，接收模块：MSCC End  *******************/

    /******************* 发送模块：MSCC，接收模块：IMSA Begin  *******************/
    MSCC_IMSA_START_REQ_STRU                                stMSCC_IMSA_START_REQ_STRU;
    MSCC_IMSA_STOP_REQ_STRU                                 stMSCC_IMSA_STOP_REQ_STRU;
    MSCC_IMSA_SERVICE_CHANGE_IND_STRU                       stMSCC_IMSA_SERVICE_CHANGE_IND_STRU;
    MSCC_IMSA_CAMP_INFO_CHANGE_IND_STRU                     stMSCC_IMSA_CAMP_INFO_CHANGE_IND_STRU;
    MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND_STRU                  stMSCC_IMSA_VOICE_DOMAIN_CHANGE_IND_STRU;
    /******************* 发送模块：MSCC，接收模块：IMSA End  *******************/

    /******************* 发送模块：MSCC，接收模块：RRM Begin  *******************/
    PS_RRM_RAT_COMBINED_MODE_IND_STRU                       stPS_RRM_RAT_COMBINED_MODE_IND_STRU;
    /******************* 发送模块：MSCC，接收模块：RRM End  *******************/

    /******************* 发送模块：MSCC，接收模块：TIMER Begin  *******************/
    NAS_MSCC_TIMER_INFO_STRU                                stNAS_MSCC_TIMER_INFO_STRU;
    /******************* 发送模块：MSCC，接收模块：TIMER End  *******************/

}

/*****************************************************************************
 函 数 名  : ELF_NAS_STRU_TraceTable_MMC
 功能描述  : TraceTable中MMC的消息结构
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月16日
    作    者   : w00351686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_NAS_STRU_TraceTable_MMC(void)
{
    /******************* 发送模块：MMC，接收模块：MSCC Begin  *******************/
    MMC_MSCC_START_CNF_STRU                                 stMMC_MSCC_START_CNF_STRU;
    MMC_MSCC_SYS_INFO_IND_STRU                              stMMC_MSCC_SYS_INFO_IND_STRU;
    MMC_MSCC_SERVICE_STATUS_IND_STRU                        stMMC_MSCC_SERVICE_STATUS_IND_STRU;
    MMC_MSCC_MM_INFO_IND_STRU                               stMMC_MSCC_MM_INFO_IND_STRU;
    MMC_MSCC_ATTACH_CNF_STRU                                stMMC_MSCC_ATTACH_CNF_STRU;
    MMC_MSCC_DETACH_CNF_STRU                                stMMC_MSCC_DETACH_CNF_STRU;
    MMC_MSCC_DETACH_IND_STRU                                stMMC_MSCC_DETACH_IND_STRU;
    MMC_MSCC_PLMN_LIST_CNF_STRU                             stMMC_MSCC_PLMN_LIST_CNF_STRU;
    MMC_MSCC_PLMN_LIST_REJ_STRU                             stMMC_MSCC_PLMN_LIST_REJ_STRU;
    MMC_MSCC_COVERAGE_AREA_IND_STRU                         stMMC_MSCC_COVERAGE_AREA_IND_STRU;
    MMC_MSCC_POWER_OFF_CNF_STRU                             stMMC_MSCC_POWER_OFF_CNF_STRU;
    MMC_MSCC_RSSI_IND_STRU                                  stMMC_MSCC_RSSI_IND_STRU;
    MMC_MSCC_PLMN_SPECIAL_SEL_CNF_STRU                      stMMC_MSCC_PLMN_SPECIAL_SEL_CNF_STRU;
    MMC_MSCC_DATATRAN_ATTRI_IND_STRU                        stMMC_MSCC_DATATRAN_ATTRI_IND_STRU;
    MMC_MSCC_SYS_CFG_SET_CNF_STRU                           stMMC_MSCC_SYS_CFG_SET_CNF_STRU;
    MMC_MSCC_PLMN_SELECTION_RLST_IND_STRU                   stMMC_MSCC_PLMN_SELECTION_RLST_IND_STRU;
    MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU                       stMMC_MSCC_PLMN_LIST_ABORT_CNF_STRU;
    MMC_MSCC_SPEC_PLMN_SEARCH_ABORT_CNF_STRU                stMMC_MSCC_SPEC_PLMN_SEARCH_ABORT_CNF_STRU;
    MMC_MSCC_UMTS_CIPHER_INFO_IND_STRU                      stMMC_MSCC_UMTS_CIPHER_INFO_IND_STRU;
    MMC_MSCC_GPRS_CIPHER_INFO_IND_STRU                      stMMC_MSCC_GPRS_CIPHER_INFO_IND_STRU;
    MMC_MSCC_PLMN_SPECIAL_SEL_REJ_STRU                      stMMC_MSCC_PLMN_SPECIAL_SEL_REJ_STRU;
    MMC_MSCC_AC_INFO_CHANGE_IND_STRU                        stMMC_MSCC_AC_INFO_CHANGE_IND_STRU;
    MMC_MSCC_PLMN_RESEL_CNF_STRU                            stMMC_MSCC_PLMN_RESEL_CNF_STRU;
    MMC_MSCC_REG_RESULT_IND_STRU                            stMMC_MSCC_REG_RESULT_IND_STRU;
    MMC_MSCC_PLMN_SELECTION_START_IND_STRU                  stMMC_MSCC_PLMN_SELECTION_START_IND_STRU;
    MMC_MSCC_EOPLMN_SET_CNF_STRU                            stMMC_MSCC_EOPLMN_SET_CNF_STRU;
    MMC_MSCC_USIM_AUTH_FAIL_IND_STRU                        stMMC_MSCC_USIM_AUTH_FAIL_IND_STRU;
    MMC_MSCC_NET_SCAN_CNF_STRU                              stMMC_MSCC_NET_SCAN_CNF_STRU;
    MMC_MSCC_ABORT_NET_SCAN_CNF_STRU                        stMMC_MSCC_ABORT_NET_SCAN_CNF_STRU;
    MMC_MSCC_NETWORK_CAPABILITY_INFO_IND_STRU               stMMC_MSCC_NETWORK_CAPABILITY_INFO_IND_STRU;
    MMC_MSCC_CAMP_ON_IND_STRU_STRU                          stMMC_MSCC_CAMP_ON_IND_STRU_STRU;
    MMC_MSCC_EPLMN_INFO_IND_STRU                            stMMC_MSCC_EPLMN_INFO_IND_STRU;
    MMC_MSCC_CS_SERVICE_CONN_STATUS_IND_STRU                stMMC_MSCC_CS_SERVICE_CONN_STATUS_IND_STRU;
    MMC_MSCC_SERV_REJ_IND_STRU                              stMMC_MSCC_SERV_REJ_IND_STRU;
    MMC_MSCC_ACQ_CNF_STRU                                   stMMC_MSCC_ACQ_CNF_STRU;
    MMC_MSCC_REG_CNF_STRU                                   stMMC_MSCC_REG_CNF_STRU;
    MMC_MSCC_POWER_SAVE_CNF_STRU                            stMMC_MSCC_POWER_SAVE_CNF_STRU;
    MMC_MSCC_ACQ_IND_STRU                                   stMMC_MSCC_ACQ_IND_STRU;
    MMC_MSCC_PS_SERVICE_CONN_STATUS_IND_STRU                stMMC_MSCC_PS_SERVICE_CONN_STATUS_IND_STRU;
    MMC_MSCC_RF_AVAILABLE_IND_STRU                          stMMC_MSCC_RF_AVAILABLE_IND_STRU;
    MMC_MSCC_SRV_ACQ_CNF_STRU                               stMMC_MSCC_SRV_ACQ_CNF_STRU;
    MMC_MSCC_LMM_CELL_SIGN_INFO_REPORT_IND_STRU             stMMC_MSCC_LMM_CELL_SIGN_INFO_REPORT_IND_STRU;
    MMC_MSCC_PREF_PLMN_SET_CNF_STRU                         stMMC_MSCC_PREF_PLMN_SET_CNF_STRU;
    MMC_MSCC_PREF_PLMN_QUERY_CNF_STRU                       stMMC_MSCC_PREF_PLMN_QUERY_CNF_STRU;
    MMC_MSCC_BG_SEARCH_CNF_STRU                             stMMC_MSCC_BG_SEARCH_CNF_STRU;
    MMC_MSCC_STOP_BG_SEARCH_CNF_STRU                        stMMC_MSCC_STOP_BG_SEARCH_CNF_STRU;
    MMC_MSCC_PREF_PLMN_INFO_IND_STRU                        stMMC_MSCC_PREF_PLMN_INFO_IND_STRU;
    MMC_MSCC_MMSS_LTE_UNAVAILABLE_IND_STRU                  stMMC_MSCC_MMSS_LTE_UNAVAILABLE_IND_STRU;
    MMC_MSCC_PLMN_PRI_CLASS_QUERY_CNF_STRU                  stMMC_MSCC_PLMN_PRI_CLASS_QUERY_CNF_STRU;
    MMC_MSCC_GET_GEO_CNF_STRU                               stMMC_MSCC_GET_GEO_CNF_STRU;
    MMC_MSCC_STOP_GET_GEO_CNF_STRU                          stMMC_MSCC_STOP_GET_GEO_CNF_STRU;
    MMC_MSCC_SRCHED_PLMN_INFO_IND_STRU                      stMMC_MSCC_SRCHED_PLMN_INFO_IND_STRU;
    MMC_MSCC_DPLMN_SET_CNF_STRU                             stMMC_MSCC_DPLMN_SET_CNF_STRU;
    MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU                       stMMC_MSCC_CSG_LIST_SEARCH_CNF_STRU;
    MMC_MSCC_CSG_LIST_ABORT_CNF_STRU                        stMMC_MSCC_CSG_LIST_ABORT_CNF_STRU;
    MMC_MSCC_CSG_LIST_REJ_STRU                              stMMC_MSCC_CSG_LIST_REJ_STRU;
    MMC_MSCC_INTERSYS_START_IND_STRU                        stMMC_MSCC_INTERSYS_START_IND_STRU;
    MMC_MSCC_INTERSYS_END_IND_STRU                          stMMC_MSCC_INTERSYS_END_IND_STRU;
    /******************* 发送模块：MMC，接收模块：MSCC End  *******************/

    /******************* 发送模块：MMC，接收模块：LMM Begin  *******************/
    MMC_LMM_CL_INTERSYS_START_NTF_STRU                      stMMC_LMM_CL_INTERSYS_START_NTF_STRU;
    /******************* 发送模块：MMC，接收模块：LMM End  *******************/
}

/*****************************************************************************
 函 数 名  : ELF_NAS_STRU_TraceTable_HSD
 功能描述  : TraceTable中HSD的消息结构
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月16日
    作    者   : w00351686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_NAS_STRU_TraceTable_HSD(void)
{
    /******************* 发送模块：HSD，接收模块：MSCC Begin  *******************/
    HSD_MSCC_START_CNF_STRU                                 stHSD_MSCC_START_CNF_STRU;
    HSD_MSCC_POWER_OFF_CNF_STRU                             stHSD_MSCC_POWER_OFF_CNF_STRU;
    HSD_MSCC_SYSTEM_ACQUIRE_START_IND_STRU                  stHSD_MSCC_SYSTEM_ACQUIRE_START_IND_STRU;
    HSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU                        stHSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU;
    HSD_MSCC_SYSTEM_ACQUIRE_END_IND_STRU                    stHSD_MSCC_SYSTEM_ACQUIRE_END_IND_STRU;
    HSD_MSCC_DATA_CALL_REDIAL_SYS_ACQ_CNF_STRU              stHSD_MSCC_DATA_CALL_REDIAL_SYS_ACQ_CNF_STRU;
    HSD_MSCC_HRPD_IRAT_TO_LTE_NTF_STRU                      stHSD_MSCC_HRPD_IRAT_TO_LTE_NTF_STRU;
    HSD_MSCC_SESSION_NEG_RSLT_IND_STRU                      stHSD_MSCC_SESSION_NEG_RSLT_IND_STRU;
    HSD_MSCC_OVERHEAD_MSG_IND_STRU                          stHSD_MSCC_OVERHEAD_MSG_IND_STRU;
    HSD_MSCC_INTERSYS_START_IND_STRU                        stHSD_MSCC_INTERSYS_START_IND_STRU;
    HSD_MSCC_INTERSYS_END_IND_STRU                          stHSD_MSCC_INTERSYS_END_IND_STRU;
    HSD_MSCC_QRY_HRPD_SYS_INFO_CNF_STRU                     stHSD_MSCC_QRY_HRPD_SYS_INFO_CNF_STRU;
    HSD_MSCC_BG_SEARCH_CNF_STRU                             stHSD_MSCC_BG_SEARCH_CNF_STRU;
    HSD_MSCC_SYS_CFG_CNF_STRU                               stHSD_MSCC_SYS_CFG_CNF_STRU;
    HSD_MSCC_SYSTEM_SYNC_IND_STRU                           stHSD_MSCC_SYSTEM_SYNC_IND_STRU;
    HSD_MSCC_SESSION_INFO_IND_STRU                          stHSD_MSCC_SESSION_INFO_IND_STRU;
    HSD_MSCC_POWER_SAVE_CNF_STRU                            stHSD_MSCC_POWER_SAVE_CNF_STRU;
    HSD_MSCC_CAS_STATUS_IND_STRU                            stHSD_MSCC_CAS_STATUS_IND_STRU;
    HSD_MSCC_STOP_BG_SEARCH_CNF_STRU                        stHSD_MSCC_STOP_BG_SEARCH_CNF_STRU;
    NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU                      stNAS_MSCC_PIF_RF_AVAILABLE_IND_STRU;
    HSD_MSCC_SRV_ACQ_CNF_STRU                               stHSD_MSCC_SRV_ACQ_CNF_STRU;
    HSD_MSCC_HDR_CSQ_SET_CNF_STRU                           stHSD_MSCC_HDR_CSQ_SET_CNF_STRU;
    HSD_MSCC_HDR_CSQ_IND_STRU                               stHSD_MSCC_HDR_CSQ_IND_STRU;
    HSD_MSCC_HRPD_NO_SERVICE_IND_STRU                       stHSD_MSCC_HRPD_NO_SERVICE_IND_STRU;
    /******************* 发送模块：HSD，接收模块：MSCC End  *******************/

}
/*****************************************************************************
 函 数 名  : ELF_NAS_STRU_TraceTable
 功能描述  : TraceTable中各模块的消息结构
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
void ELF_NAS_STRU_TraceTable(void)
{

    ELF_NAS_STRU_TraceTable_XSD();

    ELF_NAS_STRU_TraceTable_XCC();

    ELF_NAS_STRU_TraceTable_HLU();

    ELF_NAS_STRU_TraceTable_EHSM();

    ELF_NAS_STRU_TraceTable_HSM();

    ELF_NAS_STRU_TraceTable_MSCC();

    ELF_NAS_STRU_TraceTable_MMC();

    ELF_NAS_STRU_TraceTable_HSD();

}

/*****************************************************************************
 函 数 名  : ELF_NAS_STRU_GU_TRANS_Config
 功能描述  : HiStudio_Cmd_GU_TRANS_Config中GU_NAS的消息结构
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月18日
    作    者   : w00351686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_NAS_STRU_GU_TRANS_Config_GU_NAS(void)
{
    OM_NAS_MMA_CDMA_STATUS_INFO_REPORT_REQ_STRU             stOM_NAS_MMA_CDMA_STATUS_INFO_REPORT_REQ_STRU;
    NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_CNF_STRU             stNAS_OM_MMA_CDMA_STATUS_INFO_REPORT_CNF_STRU;
    NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_IND_STRU             stNAS_OM_MMA_CDMA_STATUS_INFO_REPORT_IND_STRU;
    OM_NAS_MMA_CDMA_STATUS_INFO_REPORT_REQ_ASN_STRU         stOM_NAS_MMA_CDMA_STATUS_INFO_REPORT_REQ_ASN_STRU;
    NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_CNF_ASN_STRU         stNAS_OM_MMA_CDMA_STATUS_INFO_REPORT_CNF_ASN_STRU;
    NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_IND_ASN_STRU         stNAS_OM_MMA_CDMA_STATUS_INFO_REPORT_IND_ASN_STRU;
}

/*****************************************************************************
 函 数 名  : ELF_NAS_STRU_GU_TRANS_Config
 功能描述  : HiStudio_Cmd_GU_TRANS_Config中各模块的消息结构
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月18日
    作    者   : w00351686
    修改内容   : 新生成函数

*****************************************************************************/
void ELF_NAS_STRU_GU_TRANS_Config(void)
{
    ELF_NAS_STRU_GU_TRANS_Config_GU_NAS();
}

void ELF_NAS_MAIN()
{
    /*****************************************************************************
    ##############################  枚举定义 Begin  ##############################
    *****************************************************************************/
    ELF_NAS_ENUM_LIST();
    /*****************************************************************************
    ##############################   枚举定义 End   ##############################
    *****************************************************************************/

    /*****************************************************************************
    #############################  结构体定义 Begin  #############################
    *****************************************************************************/
    ELF_NAS_STRU_TraceTable();
    /*****************************************************************************
    #############################   结构体定义 End   #############################
    *****************************************************************************/

    /*****************************************************************************
    ##############################  枚举定义 Begin  ##############################
    *****************************************************************************/
    ELF_NAS_ENUM_GU_TRANS_Config();
    /*****************************************************************************
    ##############################   枚举定义 End   ##############################
    *****************************************************************************/

   /*****************************************************************************
    #############################  结构体定义 Begin  #############################
    *****************************************************************************/
    ELF_NAS_STRU_GU_TRANS_Config();
   /*****************************************************************************
    #############################   结构体定义 End   #############################
    *****************************************************************************/


}
#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
