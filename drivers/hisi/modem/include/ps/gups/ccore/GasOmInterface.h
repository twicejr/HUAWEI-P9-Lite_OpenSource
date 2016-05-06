/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : GasOmInterface.h
  版 本 号   : 初稿
  作    者   : 杨龙
  生成日期   : 2008年5月6日
  最近修改   :
  功能描述   : GAS模块和OM之间的接口文件
  函数列表   :
  修改历史   :
  1.日    期   : 2008年05月06日
    作    者   : 杨龙 y58800
    修改内容   : 新生成文件
  2.日    期   : 2013年07月23日
    作    者   : y00142674
    修改内容   : 删除重复定义LOG_MIN_FILE_ID_PS，for code_check_report compile warning

******************************************************************************/

#ifndef __GASOMINTERFACE_H__
#define __GASOMINTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C"{
    #endif
#endif /* __cplusplus */

/* 功能模块编译开关集中控制 */
#include "product_config.h"

#include "Nasrrcinterface.h"
#include "errorlog.h"

#include "PsLogdef.h"
#include "NVIM_Interface.h"

#if (FEATURE_ON == FEATURE_LTE)
#include "LRrcGuRrcCommInterface.h"
#include "LRrcGrrInterface.h"
#endif

#if ( FEATURE_ON == FEATURE_UE_MODE_TDS )
#include "TRrcGrrCommInterface.h"
#endif

#include "PsRrmInterface.h"

#include "PhyGasInterface.h"
#include "CssInterface.h"

#pragma pack(4)

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define GAS_OM_3G_NCELL_NUMBER            12                    /* 3G邻区最大个数 */

#if (FEATURE_ON == FEATURE_LTE)
#define  GAS_OM_INVALID_LTE_RPT_PEROID_LEN         0xffff               /* 配置上报LTE周期长度的无效值 */
#define  GAS_OM_MAX_LTE_NCELL_NUM                  32                   /* GAS上报OM的LTE小区最大个数 */
#endif

/* Added by d00132956 for 内存优化，2011-10-21,begin */
#define GAS_OM_PRINT_MSG_MAX_NUM          40  
#define GAS_OM_PRINT_MSG_MIN_NUM          10        
/* Added by d00132956 for 内存优化，2011-10-21,end */

/* Added by j00178524 for 路测需求, 2012-11-09, begin */
#define GAS_OM_RD_TEST_UINT16_INVALID_VALUE         0xFFFF
#define GAS_OM_RD_TEST_INT16_INVALID_VALUE          (VOS_INT16)0x8000

#define GAS_OM_RD_TEST_UINT32_INVALID_VALUE         0xFFFFFFFF


#define GAS_OM_2G_NCELL_CNT_MAX_NUM                 6
#define GAS_OM_3G_NCELL_CNT_MAX_NUM                 96
#define GAS_OM_HOPPING_REQ_CNT_MAX_NUM              64
/* Added by j00178524 for 路测需求, 2012-11-09, end */

#define GAS_OM_APPLY_TASK_LIST_MAX_NUM           (8)                            /* 申请资源的最大任务个数 */

#define GAS_OM_CSS_INTERFACE_OUPUT_PREF_FREQ_MAX_NUM    (4)
#define GAS_OM_CSS_INTERFACE_OUPUT_PREF_BAND_MAX_NUM    (50)
#define GAS_OM_CSS_INTERFACE_INPUT_PLMN_MAX_NUM         (19)

/*******************************************************************************
  3 枚举定义
*******************************************************************************/

/*****************************************************************************
 枚举名    : OM_GAS_MSG_ID_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : OM <-> GAS 接口消息ID
*****************************************************************************/
/* 说明 */
/* 由于给工具的数据/状态上报通过OM透明通道，OM传给工具的包头无法确定发送者模块，
   经工具定义，需要通过上报的原语指示发送模块，
   即: 原语的高 8 位表示发送模块，有如下定义:
   
   0xA0XX: 表示 GAS 模块发出的数据/状态上报
   0xB0XX: 表示 WAS 模块发出的数据/状态上报
   0xC0XX: 表示 NAS 模块发出的数据/状态上报
   0xD0XX: 表示 TTF 模块发出的数据/状态上报
   0xE0XX: 表示 GHPA 模块发出的数据/状态上报
   0xF0XX: 表示 HPA 模块发出的数据/状态上报

   事件上报不用模块间保证原语的唯一性，因为OM给APP的头包含了发送者模块ID；

 */
enum OM_GAS_MSG_ID_ENUM
{
    /* 指定频点驻留 */
    ID_OM_GAS_SPECIFIC_FREQ_CAMP_REQ             = 0xA000,    /* _H2ASN_MsgChoice  OM_GAS_SPECIFIC_FREQ_CAMP_REQ_ST */        

    /* 数据/状态查询请求 */
    ID_OM_GAS_CELL_INFO_REQ                      = 0xA001,    /* _H2ASN_MsgChoice  OM_GAS_CELL_INFO_REQ_ST */
    ID_OM_GAS_CHANNEL_QUALITY_REQ                = 0xA002,    /* _H2ASN_MsgChoice  OM_GAS_CHANNEL_QUALITY_REQ_ST */    
    ID_OM_GAS_3G_NCELL_MEAS_REQ                  = 0xA003,    /* _H2ASN_MsgChoice  OM_GAS_3G_NCELL_MEAS_REQ_ST */    
    ID_OM_GAS_GSM_INFO_REQ                       = 0xA004,    /* _H2ASN_MsgChoice  OM_GAS_GSM_INFO_REQ_ST */    

    /* 空口消息配置请求 */
    ID_OM_GAS_OTA_REQ                            = 0xA005,    /* _H2ASN_MsgChoice  OM_GAS_OTA_REQ_STRUCT */

    /* 指定频点驻留 */
    ID_GAS_OM_SPECIFIC_FREQ_CAMP_CNF             = 0xA010,    /* _H2ASN_MsgChoice  GAS_OM_SPECIFIC_FREQ_CAMP_CNF_ST */

    /* 数据/状态查询的确认 */
    ID_GAS_OM_CELL_INFO_CNF                      = 0xA011,    /* _H2ASN_MsgChoice  GAS_OM_CELL_INFO_CNF_ST */
    ID_GAS_OM_CHANNEL_QUALITY_CNF                = 0xA012,    /* _H2ASN_MsgChoice  GAS_OM_CHANNEL_QUALITY_CNF_ST */
    ID_GAS_OM_3G_NCELL_MEAS_CNF                  = 0xA013,    /* _H2ASN_MsgChoice  GAS_OM_INFO_CNF_ST */
    ID_GAS_OM_GSM_INFO_CNF                       = 0xA014,    /* _H2ASN_MsgChoice  GAS_OM_INFO_CNF_ST */

    /* 空口消息配置确认 */
    ID_GAS_OM_OTA_CNF                            = 0xA015,    /* _H2ASN_MsgChoice  GAS_OM_OTA_CNF_STRUCT */

    /* Added by d00132956 for 内存优化，2011-10-21,begin */
    /* 打印调试信息 */
    ID_GAS_OM_PRINT_MSG                          = 0xA016,
    /* Added by d00132956 for 内存优化，2011-10-21,end */

    /* 数据/状态上报 */
    ID_GAS_OM_CELL_INFO_IND                      = 0xA021,    /* _H2ASN_MsgChoice GAS_OM_CELL_INFO_IND_ST */
    ID_GAS_OM_CHANNEL_QUALITY_IND                = 0xA022,    /* _H2ASN_MsgChoice GAS_OM_CHANNEL_QUALITY_IND_ST */
    ID_GAS_OM_3G_NCELL_MEAS_IND                  = 0xA023,    /* _H2ASN_MsgChoice GAS_OM_3G_NCELL_MEAS_IND_ST */
    ID_GAS_OM_GSM_INFO_IND                       = 0xA024,    /* _H2ASN_MsgChoice GAS_OM_GSM_INFO_IND_ST */

    /* 空口消息上报 */
    ID_GAS_OM_OTA_IND                            = 0xA025,    /* _H2ASN_MsgChoice GAS_OM_OTA_IND_STRUCT */
    ID_GAS_OM_DEC_FAIL_CELL_IND                  = 0xA026,    /* _H2ASN_MsgChoice GAS_OM_EVENT_PLMN_SEARCH_DEC_CELL_STRU */
    ID_GAS_OM_RXLEV_CELL_IND                     = 0xA027,    /* _H2ASN_MsgChoice GAS_OM_EVENT_PLMN_SEARCH_RXLEV_STRU */
    ID_GAS_OM_PREFER_CELL_IND                    = 0xA028,    /* _H2ASN_MsgChoice GAS_OM_PREFER_CELL_ST */

    ID_GAS_OM_GSM_FORBIDDEN_LIST_IND             = 0xA029,

    ID_GAS_OM_GSM_UNAVAILABLE_LIST_IND           = 0xA02A,

    ID_GAS_OM_MM_INFO_IND                        = 0xA02B,
    /* Added by yangsicong for probe接口新开发, 2012-10-30, begin */
    ID_OM_GAS_ROAD_TEST_INFO_REQ                 = 0xA02C,   /* _H2ASN_MsgChoice GAS_OM_ROAD_TEST_INFO_REQ_STRU */
    ID_GAS_OM_ROAD_TEST_INFO_CNF                 = 0xA02D,   /* _H2ASN_MsgChoice GAS_OM_ROAD_TEST_INFO_CNF_STRU */
    ID_GAS_OM_ROAD_TEST_INFO_IND                 = 0xA02E,   /* _H2ASN_MsgChoice GAS_OM_ROAD_TEST_INFO_IND_STRU */
    /* Added by yangsicong for probe接口新开发, 2012-10-30, end */

    ID_GAS_OM_JAM_DETECT_CTX_IND                 = 0xA030,   /* _H2ASN_MsgChoice GAS_OM_JAM_DETECT_CTX_IND_STRU */

    ID_GAS_OM_GSM_FREQ_LOCKED                     = 0xA031,

    ID_GAS_OM_UNEXPECTED_MSG_RCVED                = 0xA032,

    ID_GAS_OM_NON_CHAN_REL_FR_TYPE                = 0xA033,

    ID_GAS_OM_GAS_GCOM_RF_RES_CTRL                = 0xA034,

    ID_GAS_OM_SCELL_RX_QUAL_INFO                  = 0xA035,

    #if (FEATURE_ON == FEATURE_LTE)
    ID_GAS_OM_LTE_UNSUPPORT_FREQ                  = 0xA036,
    #endif

    ID_GAS_OM_GAS_GCOM_CSS_BAND_SCAN_LIST_INFO    = 0xA037,
    ID_GAS_OM_GAS_GCOM_SAVED_CSS_BAND_SCAN_INFO   = 0xA038,

    ID_GAS_OM_GSM_HISTORY_SI_CTX_IND              = 0xA039,   /* _H2ASN_MsgChoice GAS_OM_GSM_HISTORY_SI_CONTEXT_STRU */

    /* Added by y00142674 for 邻区继承, 2015-07-14, begin */
    ID_GAS_OM_GSM_HISTORY_NCELL_SI_CTX_IND        = 0xA03A,   /* _H2ASN_MsgChoice GAS_OM_GSM_HISTORY_NCELL_SI_CTX_IND_STRU */
    /* Added by y00142674 for 邻区继承, 2015-07-14, end */

    /* Added by p00166345 for DTS2015052601104(伪基站识别), 2015-08-02, begin */
    ID_GAS_OM_PSEUD_BTS_IDENT_INFO                = 0xA03B,   /* _H2ASN_MsgChoice GAS_OM_PSEUD_BTS_IDENT_INFO_STRU */
    /* Added by p00166345 for DTS2015052601104(伪基站识别), 2015-08-02, end */

    ID_GAS_OM_PARALLEL_SRCH_CTX_IND               = 0xA03C,   /* _H2ASN_MsgChoice GAS_OM_PARALLEL_SRCH_CTX_STRU */
    ID_GAS_OM_PARALLEL_SRCH_RULE_IND              = 0xA03D,   /* _H2ASN_MsgChoice GAS_OM_PARALLEL_SRCH_RULE_STRU */

    ID_GAS_OM_PARALLEL_NCELL_NORMAL_CTX_IND       = 0xA03E,     /* _H2ASN_MsgChoice GAS_OM_PARALLEL_NCELL_NORMAL_CTX_STRU */

    ID_GAS_OM_DEDICATED_HO_INFO                   = 0xA040,     /* _H2ASN_MsgChoice GAS_GCOM_DEDICATED_HO_INFO_STRU */

    ID_GAS_OM_ARFCN_CELL_IDENT_INFO_LST           = 0xA041,     /* _H2ASN_MsgChoice GAS_GCOM_GSM_ARFCN_CELL_IDENT_INFO_LST_STRU */

    ID_GAS_OM_INTER_RESEL_EVALUATE_RLT            = 0xA042,     /* _H2ASN_MsgChoice GAS_OM_INTER_RESEL_EVALUATE_RLT_STRU */

    /* 事件上报 */
    ID_GAS_OM_EVENT_GSM_RANDOM_ACCESS_REQUEST    = 0xA0A1,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */ 
    ID_GAS_OM_EVENT_GSM_LINK_FAILURE             = 0xA0A2,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_LINK_FAILURE_ST */
    ID_GAS_OM_EVENT_GSM_DOWNLINK_FAILURE         = 0xA0A3,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_DOWNLINK_FAILURE_ST */
    ID_GAS_OM_EVENT_GSM_RESELECT_START           = 0xA0A4,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_RESELECT_START_ST */
    ID_GAS_OM_EVENT_GSM_RESELECT_END             = 0xA0A5,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_RESELECT_END_ST */
    ID_GAS_OM_EVENT_GSM_CAMP_ATTEMPT_START       = 0xA0A6,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_CAMP_ATTEMPT_START_ST */
    ID_GAS_OM_EVENT_GSM_CAMP_ATTEMPT_END         = 0xA0A7,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_CAMP_ATTEMPT_END_ST */
    ID_GAS_OM_EVENT_GSM_RR_IN_SERVICE            = 0xA0A8,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_GSM_RR_OUT_OF_SERVICE        = 0xA0A9,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_GSM_PAGE_RECEIVED            = 0xA0AA,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */    
    ID_GAS_OM_EVENT_GPRS_PAGE_RECEIVED           = 0xA0AB,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_GPRS_LINK_FAILURE            = 0xA0AC,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_PACKET_RANDOM_ACCESS_REQUEST = 0xA0AD,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_GSM_TO_WCDMA_RESELECT_START  = 0xA0AE,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_WCDMA_RESELECT_START_ST */
    ID_GAS_OM_EVENT_GSM_TO_WCDMA_RESELECT_END    = 0xA0AF,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_WCDMA_RESELECT_END_ST */
    ID_GAS_OM_EVENT_GSM_TO_WCDMA_HANDOVER_START  = 0xA0B0,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_GSM_TO_WCDMA_HANDOVER_END    = 0xA0B1,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_GPRS_ACCESS_REJECT           = 0xA0B2,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_GPRS_TBF_ABNORMAL_RELEASE    = 0xA0B3,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GPRS_TBF_ABNORMAL_RELEASE_ST */
    /* 2008-10-14 */
    ID_GAS_OM_EVENT_GPRS_INVALID_ASSIGN          = 0xA0B4,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GPRS_INVALID_ASSIGN_ST */
    ID_GAS_OM_EVENT_TIMER_ACTION                 = 0xA0B5,      /* _H2ASN_MsgChoice GAS_OM_EVENT_TIMER_ACTION_ST */

    /* 2008-04-02 */
    ID_GAS_OM_EVENT_IMMEDIATE_ASSIGN_UP_ONE      = 0xA0B6,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_IMMEDIATE_ASSIGN_UP_FIRST    = 0xA0B7,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    
    ID_GAS_OM_EVENT_IMMEDIATE_ASSIGN_DOWN_ONE    = 0xA0B8,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_IMMEDIATE_ASSIGN_DOWN_FIRST  = 0xA0B9,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    
    ID_GAS_OM_EVENT_IMMEDIATE_ASSIGN_SECOND      = 0xA0BA,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */ 
    
    ID_GAS_OM_EVENT_OUT_OF_SERVICE               = 0xA0BB,      /* _H2ASN_MsgChoice GAS_OM_EVENT_OUT_OF_SERVICE_ST*/ 

    ID_GAS_OM_EVENT_DSP_LOAD_FAIL                = 0xA0BC,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */ 
    ID_GAS_OM_EVENT_RR_CONNECTION_ABNORMAL       = 0xA0BD,      /* _H2ASN_MsgChoice GAS_OM_EVENT_RR_CONNECTION_ABNORMAL_ST */

    ID_GAS_OM_EVENT_BUFFER_MESSAGE_DELETED       = 0xA0BE,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */   

    ID_GAS_OM_EVENT_2G_NCELL_LIST_CHANGE         = 0xA0BF,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_2G_NCELL_LIST_CHANGE_ST */
    ID_GAS_OM_EVENT_3G_NCELL_LIST_CHANGE         = 0xA0C0,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_3G_NCELL_LIST_CHANGE_ST */

    ID_GAS_OM_EVENT_GSM_TO_WCDMA_AFTER_CHAN_REL_SELECT_START  = 0xA0C1,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_WCDMA_AFTER_CHAN_REL_SELECT_START_ST */
    ID_GAS_OM_EVENT_GSM_TO_WCDMA_AFTER_CHAN_REL_SELECT_END    = 0xA0C2,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_WCDMA_AFTER_CHAN_REL_SELECT_END_ST */

    ID_GAS_OM_EVENT_X_BG_SEARCH_G_FREQ_MEAS_START      = 0xA0C3,    /* _H2ASN_MsgChoice GAS_OM_EVENT_X_BG_SEARCH_G_FREQ_MEAS_START_ST */        
    ID_GAS_OM_EVENT_X_BG_SEARCH_G_FREQ_MEAS_END        = 0xA0C4,    /* _H2ASN_MsgChoice GAS_OM_EVENT_X_BG_SEARCH_G_FREQ_MEAS_END_ST */

    ID_GAS_OM_EVENT_PERIOD_CHECK_WEAK_SIGNAL_T_EXPIRED = 0xA0C5,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_INIT_WEAK_SIGNAL                   = 0xA0C6,    /* _H2ASN_MsgChoice GAS_OM_EVENT_INIT_WEAK_SIGNAL_ST */
    ID_GAS_OM_EVENT_PERIOD_WEAK_SIGNAL                 = 0xA0C7,    /* _H2ASN_MsgChoice GAS_OM_EVENT_PERIOD_WEAK_SIGNAL_ST */
    ID_GAS_OM_EVENT_PERIOD_WEAK_SIGNAL_LIST            = 0xA0C8,    /* _H2ASN_MsgChoice GAS_OM_EVENT_WEAK_SIGNAL_LIST_ST */

    #if (FEATURE_ON == FEATURE_LTE)

    /* 新增 G 和 L 交互的 可维可测消息 */
    ID_GAS_OM_EVENT_GSM_TO_LTE_RESEL_START             = 0xA0C9,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_LTE_RESEL_START_ST */
    ID_GAS_OM_EVENT_GSM_TO_LTE_RESEL_END               = 0xA0CA,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_LTE_RESEL_END_ST */
    ID_GAS_OM_EVENT_LTE_TO_GSM_RESEL_START             = 0xA0CB,    /* _H2ASN_MsgChoice GAS_OM_EVENT_LTE_TO_GSM_RESEL_START_ST */
    ID_GAS_OM_EVENT_LTE_TO_GSM_RESEL_END               = 0xA0CC,    /* _H2ASN_MsgChoice GAS_OM_EVENT_LTE_TO_GSM_RESEL_END_ST */
    ID_GAS_OM_EVENT_GSM_TO_LTE_CCO_START               = 0xA0CD,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_LTE_CCO_START_ST */
    ID_GAS_OM_EVENT_GSM_TO_LTE_CCO_END                 = 0xA0CE,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_LTE_CCO_END_ST */
    ID_GAS_OM_EVENT_LTE_TO_GSM_CCO_START               = 0xA0CF,    /* _H2ASN_MsgChoice GAS_OM_EVENT_LTE_TO_GSM_CCO_START_ST */    
    ID_GAS_OM_EVENT_LTE_TO_GSM_CCO_END                 = 0xA0D0,    /* _H2ASN_MsgChoice GAS_OM_EVENT_LTE_TO_GSM_CCO_END_ST */
    ID_OM_GAS_LTE_NCELL_MEAS_REPORT_REQ                = 0xA0D1,    /* _H2ASN_MsgChoice OM_GAS_INFO_REQ_ST */
    ID_GAS_OM_LTE_NCELL_MEAS_REPORT_CNF                = 0xA0D2,
    ID_GAS_OM_LTE_NCELL_MEAS_IND                       = 0xA0D3,    /* _H2ASN_MsgChoice GAS_OM_LTE_NCELL_MEAS_IND_ST */    
    ID_GAS_OM_EVENT_GSM_TO_LTE_REDIR_START             = 0xA0D4,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_LTE_REDIR_START_ST */
    ID_GAS_OM_EVENT_GSM_TO_LTE_REDIR_END               = 0xA0D5,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_LTE_REDIR_END_ST */
    ID_GAS_OM_EVENT_LTE_TO_GSM_REDIR_START             = 0xA0D6,    /* _H2ASN_MsgChoice GAS_OM_EVENT_LTE_TO_GSM_REDIR_START_ST */
    ID_GAS_OM_EVENT_LTE_TO_GSM_REDIR_END               = 0xA0D7,    /* _H2ASN_MsgChoice GAS_OM_EVENT_LTE_TO_GSM_REDIR_END_ST */

    #endif

    ID_GAS_OM_EVENT_RESEL_EVALUATE_ADD_CELL            = 0xA0D8,    /* _H2ASN_MsgChoice  GAS_OM_EVENT_RESEL_EVALUATE_ADD_CELL_ST */
    ID_GAS_OM_EVENT_RESEL_EVALUATE_RMV_CELL            = 0xA0D9,    /* _H2ASN_MsgChoice  GAS_OM_EVENT_RESEL_EVALUATE_RMV_CELL_ST */

    ID_GAS_OM_EVENT_RCV_SI_ON_PCH                      = 0xA0DA,    /* _H2ASN_MsgChoice GAS_OM_EVENT_RCV_SI_ON_PCH_STRU */

    ID_GAS_OM_EVENT_CLEAR_FORBIDDEN_LIST               = 0xA0DB,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */            
    ID_GAS_OM_EVENT_RESET_FORBIDDEN_LIST_FAIL_TIMES    = 0xA0DC,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */

    ID_GAS_OM_EVENT_GSM_TO_UTRAN_TDD_RESEL_START       = 0xA0DD,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_UTRAN_TDD_RESEL_START_ST */
    ID_GAS_OM_EVENT_GSM_TO_UTRAN_TDD_RESEL_END         = 0xA0DE,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_UTRAN_TDD_RESEL_END_ST */
    ID_GAS_OM_EVENT_UTRAN_TDD_TO_GSM_RESEL_START       = 0xA0DF,    /* _H2ASN_MsgChoice GAS_OM_EVENT_UTRAN_TDD_TO_GSM_RESEL_START_ST */
    ID_GAS_OM_EVENT_UTRAN_TDD_TO_GSM_RESEL_END         = 0xA0E0,    /* _H2ASN_MsgChoice GAS_OM_EVENT_UTRAN_TDD_TO_GSM_RESEL_END_ST */
    ID_GAS_OM_EVENT_RESEL_EVALUATE_START               = 0xA0E1,    /* _H2ASN_MsgChoice GAS_OM_EVENT_INTER_RESEL_EVALUATE_START_ST */
    ID_GAS_OM_EVENT_RESEL_EVALUATE_TIMER_START         = 0xA0E2,    /* _H2ASN_MsgChoice GAS_OM_EVENT_INTER_RESEL_EVALUATE_TIMER_START_ST */
    ID_GAS_OM_EVENT_RESEL_EVALUATE_TIMER_EXPIRED       = 0xA0E3,    /* _H2ASN_MsgChoice GAS_OM_EVENT_INTER_RESEL_EVALUATE_TIMER_EXPIRED_ST */

    ID_GAS_OM_EVENT_WCDMA_TO_GSM_RESEL_CCO_RESULT      = 0xA0E6,    /* _H2ASN_MsgChoice GAS_OM_EVENT_WCDMA_TO_GSM_RESEL_CCO_END_ST */   
    ID_GAS_OM_EVENT_BG_PLMN_LIST_SEARCH_END            = 0xA0E7,    /* _H2ASN_MsgChoice  GAS_OM_EVENT_BG_PLMN_LIST_SEARCH_END_ST */        

#if (FEATURE_ON == FEATURE_LTE)
    ID_GAS_OM_EVENT_LTE_TO_GSM_ANR_END                 = 0xA0E8,   /* _H2ASN_MsgChoice  GAS_OM_EVENT_LTE_TO_GSM_ANR_END_ST */

#endif
    
    ID_GAS_OM_EVENT_BG_PLMN_SEARCH_LTE_END             = 0xA0E9,    /* _H2ASN_MsgChoice GAS_OM_ABNORMAL_EVENT_BG_PLMN_SEARCH_LTE_ST */
    ID_GAS_OM_EVENT_DSP_INIT_FAILED                    = 0xA0EA,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */

    ID_GAS_OM_EVENT_DISCARD_REASSEMBLED_APDU           = 0xA0EB,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_RRLP_MESSAGE_OVER_MAX_LENGTH       = 0xA0EC,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_RRLP_MESSAGE_REQ                   = 0xA0ED,
    ID_GAS_OM_EVENT_RRLP_MESSAGE_RSP                   = 0xA0EE,

    ID_GAS_OM_EVENT_GSM_TO_UTRAN_TDD_CCO_START         = 0xA0EF,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_UTRAN_TDD_CCO_START_ST */
    ID_GAS_OM_EVENT_GSM_TO_UTRAN_TDD_CCO_END           = 0xA0F0,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_UTRAN_TDD_CCO_END_ST */
    ID_GAS_OM_EVENT_UTRAN_TDD_TO_GSM_CCO_START         = 0xA0F1,    /* _H2ASN_MsgChoice GAS_OM_EVENT_UTRAN_TDD_TO_GSM_CCO_START_ST */
    ID_GAS_OM_EVENT_UTRAN_TDD_TO_GSM_CCO_END           = 0xA0F2,    /* _H2ASN_MsgChoice GAS_OM_EVENT_UTRAN_TDD_TO_GSM_CCO_END_ST */

    ID_GAS_OM_EVENT_GSM_TO_UTRAN_FDD_RESEL_START       = 0xA0F3,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_UTRAN_FDD_RESEL_START_ST */
    ID_GAS_OM_EVENT_GSM_TO_UTRAN_FDD_RESEL_END         = 0xA0F4,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_UTRAN_FDD_RESEL_END_ST */
    ID_GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_START         = 0xA0F5,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_START_ST */
    ID_GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_END           = 0xA0F6,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_END_ST */

    ID_GAS_OM_EVENT_UTRAN_TDD_TO_GSM_HO_START          = 0xA0F7,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_UTRAN_TDD_TO_GSM_HO_END            = 0xA0F8,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */

    ID_GAS_OM_EVENT_GCOM_CACHED_MSG_OVERFLOW           = 0xA0F9,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GCOM_CACHED_MSG_OVERFLOW_ST */

    ID_GAS_OM_EVENT_CS_PS_TRANSACTION_INFO             = 0xA0FA,    
    
    ID_GAS_OM_EVENT_RR_POOR_RXQUAL                     = 0xA0FB,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */

    ID_GAS_OM_EVENT_GSM_TO_UTRAN_TDD_FAST_RETURN_VALID = 0xA0FC,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_GSM_TO_UTRAN_TDD_FAST_RETURN_INVALID = 0xA0FD,  /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */

    ID_GAS_OM_EVENT_GSM_TO_UTRAN_TDD_REDIR_START       = 0xA0FE,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_UTRAN_TDD_REDIR_START_ST */
    ID_GAS_OM_EVENT_GSM_TO_UTRAN_TDD_REDIR_END         = 0xA0FF,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_UTRAN_TDD_REDIR_END_ST */

    /* Added by y00142674 for GSM自主重定向到LTE, 2013-06-21, begin */
    ID_GAS_OM_EVENT_GSM_TO_LTE_AUTO_FAST_RETURN_VALID   = 0xA100,   /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_GSM_TO_LTE_AUTO_FAST_RETURN_INVALID = 0xA101,   /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */

    ID_GAS_OM_EVENT_GAS_INTERNAL_MSG_LENGTH_TOO_LONG    = 0xA102,   /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_GAS_INTERNAL_MSG_QUEUE_IS_FULL      = 0xA103,   /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    /* Added by y00142674 for GSM自主重定向到LTE, 2013-06-21, end */

#if (FEATURE_ON == FEATURE_LTE)
    ID_GAS_OM_EVENT_LTE_TO_GSM_HO_START                 = 0xA104,    /* _H2ASN_MsgChoice GAS_OM_EVENT_LTE_TO_GSM_HANDOVER_START_ST */
    ID_GAS_OM_EVENT_LTE_TO_GSM_HO_END                   = 0xA105,    /* _H2ASN_MsgChoice GAS_OM_EVENT_LTE_TO_GSM_HANDOVER_END_ST */
#endif /* end of (FEATURE_ON == FEATURE_LTE) */    

    ID_GAS_OM_EVENT_W_NON_NCELL_MEAS_START              = 0xA106,    /* _H2ASN_MsgChoice GAS_OM_EVENT_W_NON_NCELL_MEAS_START_ST */

#if ( FEATURE_ON == FEATURE_DSDS )
    ID_GAS_OM_EVENT_RF_RESOURCE_TASK_LIST               = 0xA107,     /* _H2ASN_MsgChoice GAS_OM_EVENT_RF_RESOURCE_TASK_LIST_STRU */
#endif

    ID_GAS_OM_EVENT_PLMN_SEARCH_CELL_SATISFACTION_LIST_IND  = 0xA108,    /* _H2ASN_MsgChoice GAS_OM_PLMN_SRCH_CELL_SATISFACTION_RESULT_ST */

    ID_GAS_OM_EVENT_C1_CUSTOMIZE_VALID                  = 0xA109,

    ID_GAS_OM_EVENT_C1_CUSTOMIZE_INVALID                = 0xA10A,

    ID_GAS_OM_EVENT_C1_RESEL_CANCELED_FOR_C1_CUSTOMIZE  = 0xA10B,
    

    ID_GAS_OM_EVENT_UTRAN_FDD_TO_GSM_CCO_START         = 0xA10C,    /* _H2ASN_MsgChoice GAS_OM_EVENT_UTRAN_FDD_TO_GSM_CCO_START_ST */
    ID_GAS_OM_EVENT_UTRAN_FDD_TO_GSM_CCO_END           = 0xA10D,    /* _H2ASN_MsgChoice GAS_OM_EVENT_UTRAN_FDD_TO_GSM_CCO_END_ST */
    ID_GAS_OM_EVENT_UTRAN_FDD_TO_GSM_RESEL_START         = 0xA10E,    /* _H2ASN_MsgChoice GAS_OM_EVENT_UTRAN_FDD_TO_GSM_RESEL_START_ST */

    ID_GAS_OM_EVENT_RA_CNF_FAIL_NO_RF                    = 0xA10F,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */

    ID_GAS_OM_AFC_INFO_IND                              = 0xA110,    /* _H2ASN_MsgChoice GAS_OM_AFC_INFO_IND_ST */

    /* Added by y00142674 for 漫游搜网优化, 2015-04-30, begin */
    ID_GAS_OM_EVENT_SB_IND_FAIL_NO_RF                   = 0xA111,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    /* Added by y00142674 for 漫游搜网优化, 2015-04-30, end */

    ID_GAS_OM_EVENT_LAU_REQ_INFO                        = 0xA112,     /* _H2ASN_MsgChoice GAS_OM_EVENT_LAU_REQ_INFO_STRU */

    ID_GAS_OM_EVENT_UTRAN_CELL_BAR                      = 0xA113,

    ID_GAS_OM_SEARCH_PROC_INFO                          = 0xA114,   /* _H2ASN_MsgChoice GAS_OM_SEARCH_PROC_INFO_STRU */
    ID_GAS_OM_SEARCHED_FREQ_LIST                        = 0xA115,   /* _H2ASN_MsgChoice GAS_OM_SEARCHED_FREQ_LIST_STRU */

    ID_GAS_OM_EVENT_START_TIMER_FAIL                    = 0xA116,

    ID_GAS_OM_EVENT_CSS_CLOUD_INTERFACE                 = 0xA117,   /* _H2ASN_MsgChoice GAS_OM_CSS_CLOUD_INTERFACE_STRU */

    ID_OM_GAS_WRITE_NV_REQ                             = 0xAAA7,    /* _H2ASN_MsgChoice GAS_OM_WRITE_NV_REQ_ST */
    ID_GAS_OM_WRITE_NV_CNF                             = 0xAAA8,

    ID_SDT_GAS_CONNECTED_IND                           = 0xAAAA,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_SDT_CONNECTED_CNF                           = 0xAAAB,

    ID_GAS_OM_MSG_BUTT
};
typedef VOS_UINT16  OM_GAS_MSG_ID_ENUM_UINT16;

/*****************************************************************************
 枚举名    : OM_GAS_REPORT_ACTION_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : OM -> GAS 的消息动作
*****************************************************************************/
enum OM_GAS_REPORT_ACTION_ENUM
{
    OM_GAS_REPORT_STOP            = 0,
    OM_GAS_REPORT_START           = 1,
    
    OM_GAS_REPORT_BUTT
};
typedef VOS_UINT16 OM_GAS_REPORT_ACTION_ENUM_UINT16;

/*****************************************************************************
 枚举名    : OM_GAS_REPORT_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : OM -> GAS 的消息上报类型
*****************************************************************************/
/* 消息上报的类型 */
enum OM_GAS_REPORT_TYPE_ENUM
{
    OM_GAS_REPORT_TYPE_NULL       = 0,
    OM_GAS_REPORT_TYPE_ONCE       = 1,
    OM_GAS_REPORT_TYPE_PERIODIC   = 2,
    /*OM_GAS_REPORT_TYPE_CHANGED    = 4,*/          /*上报参数太多，不提供有改变上报的类型*/

    OM_GAS_REPORT_TYPE_BUTT
};
typedef VOS_UINT16 OM_GAS_REPORT_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : GAS_OM_STATE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : GAS -> OM GAS状态上报
*****************************************************************************/
enum GAS_OM_STATE_ENUM
{
    GAS_OM_STATE_IDLE             = 0,        /* 空闲态 */
    GAS_OM_STATE_DEDICATED        = 1,        /* CS专用态 */
    GAS_OM_STATE_TRANSFER         = 2,        /*  PS传输态 */

    GAS_STATE_BUTT
};
typedef VOS_UINT16 GAS_OM_STATE_ENUM_UINT16; 


/*****************************************************************************
 枚举名    : GAS_DCH_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : GAS -> OM 当前专用信道类型
*****************************************************************************/
enum GAS_DCH_TYPE_ENUM
{
    GAS_DCH_TYPE_NONE            = 0,          /* 当前没有专用信道 */
    GAS_DCH_TYPE_DCH             = 1,          /* CS域的专用信道: SDCCH或TCH */
    GAS_DCH_TYPE_PDTCH           = 2,          /* PS域的专用信道: PDTCH */
    
    GAS_DCH_TYPE_BUTT
};
typedef VOS_UINT16 GAS_DCH_TYPE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : GAS_OM_GSM_BAND_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : GAS -> OM GSM 的频段类型
*****************************************************************************/
enum GAS_OM_GSM_BAND_ENUM
{
    GAS_BAND_GSM850               = 0,         /* GSM850频段 */
    GAS_BAND_GSM900               = 1,         /* GSM900频段 */
    GAS_BAND_DCS                  = 2,         /* DCS1800频段 */
    GAS_BAND_PCS                  = 3,         /* PCS1900频段 */

    GAS_BAND_BUTT                 = 65535
};
typedef VOS_UINT16  GAS_OM_GSM_BAND_ENUM_UINT16;


/*****************************************************************************
 枚举名    : GAS_OM_RRC_RR_CNF_ENUM_UINT32
 协议表格  :
 ASN.1描述 :
 枚举说明  : GAS -> OM   RRC回复RR的结果
*****************************************************************************/
enum GAS_OM_RRC_RR_CNF_ENUM
{
    GAS_OM_RRC_RR_CNF_SUCCESS                    = 0,
    GAS_OM_RRC_RR_CNF_FAILURE                    = 1,
    GAS_OM_RRC_RR_CNF_MESSAGE_INVALID            = 2,
    GAS_OM_RRC_RR_CNF_PROTOCOL_ERROR             = 3,
    GAS_OM_RRC_RR_CNF_UNSUPORTED_CONFIGURATION   = 4,
    GAS_OM_RRC_RR_CNF_PHY_CHANNEL_FAILURE        = 5,

    GAS_OM_RRC_RR_CNF_BUTT
};
typedef VOS_UINT32 GAS_OM_RRC_RR_CNF_ENUM_UINT32;

/*****************************************************************************
 枚举名    : GAS_OM_RLC_MODE_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  : GAS -> OM   RLC模式
*****************************************************************************/
enum GAS_OM_RLC_MODE_ENUM
{
    GAS_OM_RLC_MODE_AM                      = 0,            /* 确认模式 */
    GAS_OM_RLC_MODE_UM                      = 1,            /* 非确认模式 */

    GAS_OM_RLC_MODE_BUTT
};
typedef VOS_UINT8 GAS_OM_RLC_MODE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : GAS_OM_MAC_MODE_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  : GAS -> OM   MAC模式
*****************************************************************************/
enum GAS_OM_MAC_MODE_ENUM
{
    GAS_OM_MAC_MODE_FIXED_ALLOC             = 0,            /* 固定分配 */         
    GAS_OM_MAC_MODE_DYN_ALLOC               = 1,            /* 动态分配 */
    GAS_OM_MAC_MODE_EXT_DYN_ALLOC           = 2,            /* 扩展动态分配 */
    GAS_OM_MAC_MODE_SINGLE_BLOCK_ALLOC      = 3,            /* 单块 */
    GAS_OM_MAC_MODE_MULTI_BLOCK_ALLOC       = 4,            /* 多个单块 */
    
    GAS_OM_MAC_MODE_BUTT
};
typedef VOS_UINT8 GAS_OM_MAC_MODE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : GAS_OM_CS_TYPE_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  : GAS -> OM   编码方式
*****************************************************************************/
enum GAS_OM_CS_TYPE_ENUM
{
    GAS_OM_CS_TYPE_CS1                      = 0,            /* 编码方式 CS1 */
    GAS_OM_CS_TYPE_CS2                      = 1,            /* 编码方式 CS2 */
    GAS_OM_CS_TYPE_CS3                      = 2,            /* 编码方式 CS3 */
    GAS_OM_CS_TYPE_CS4                      = 3,            /* 编码方式 CS4 */

    GAS_OM_CS_TYPE_BUTT
};
typedef VOS_UINT8 GAS_OM_CS_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : GAS_OM_RESEL_TYPE_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  : GAS -> OM   小区重选类型
*****************************************************************************/
enum GAS_OM_RESEL_TYPE_ENUM
{
    GAS_OM_RESEL_TYPE_NONE                  = 0,            /* 不用 */
    GAS_OM_RESEL_TYPE_ACTIVE                = 1,            /* 主动重选 */
    GAS_OM_RESEL_TYPE_PASSIVE               = 2,            /* 被动重选 */

    GAS_OM_RESEL_TYPE_BUTT
};
typedef VOS_UINT8 GAS_OM_RESEL_TYPE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : GAS_OM_RESEL_CAUSE_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  : GAS -> OM   小区重选原因
  1.日    期   : 2015年12月21日
    作    者   : x00220225
    修改内容   : 增加重选原因的类型和GasGcomcPublicCellReselection.h一致，for DTS20151219018810 
*****************************************************************************/
enum GAS_OM_RESEL_CAUSE_ENUM
{
    GAS_OM_RESEL_CAUSE_ACTIVE_C2                    = 0,   /* 小区重选原因:主动的重选 */
    GAS_OM_RESEL_CAUSE_PASSIVE_PATH_LOSS            = 1,   /* 小区重选原因:服务小区路径损耗太大 */
    GAS_OM_RESEL_CAUSE_PASSIVE_NETWORK_CONTROL      = 2,   /* 小区重选原因:网络控制小区重选 */
    GAS_OM_RESEL_CAUSE_PASSIVE_NAS_REQUEST          = 3,   /* 小区重选原因:NAS发指示进行小区重选 */
    GAS_OM_RESEL_CAUSE_PASSIVE_DOWNLINK_FAILURE     = 4,   /* 小区重选原因:下行链路失败 */
    GAS_OM_RESEL_CAUSE_PASSIVE_SI_FAILURE           = 5,   /* 小区重选原因:系统消息接收失败 */
    GAS_OM_RESEL_CAUSE_PASSIVE_GRR_N3102            = 6,   /* 小区重选原因:N3102引起 */
    GAS_OM_RESEL_CAUSE_PASSIVE_RR_ACCESS_FAILURE    = 7,   /* 小区重选原因:随机接入失败 */
    GAS_OM_RESEL_CAUSE_PASSIVE_RADIOLINK_FAILURE    = 8,   /* 小区重选原因:无线链路失效(reserved) */
    GAS_OM_RESEL_CAUSE_PASSIVE_RR_NAS_ABORT         = 9,   /* 小区重选原因:RR接收到NAS发来的原语RRMM_ABORT_REQ */
    GAS_OM_RESEL_CAUSE_PASSIVE_RR_CAMP_FAILURE      = 10,  /* 小区重选原因:RR离开专用态后，驻留失败导致*/
    GAS_OM_RESEL_CAUSE_PASSIVE_CELL_BARRED          = 11,  /* 小区重选原因:小区Barred*/
    GAS_OM_RESEL_CAUSE_PASSIVE_NOT_SUITABLE         = 12,  /* 小区重选原因:小区不满足合适得小区条件*/
    GAS_OM_RESEL_CAUSE_PASSIVE_GRR_ACCESS_FAILURE   = 13,  /* 小区重选原因:GRR随机接入失败 */
    GAS_OM_RESEL_CAUSE_PASSIVE_BAND_NOT_SUPPORT     = 14,  /* 小区重选原因:频段不支持 */
    GAS_OM_RESEL_CAUSE_PASSIVE_SCELL_TIMING_ERR     = 15,  /* 小区重选原因:服务小区时序错误 */
    GAS_OM_RESEL_CAUSE_PASSIVE_ROAD_TEST_FORCE_RESEL= 16,  /* 小区重选原因:路测强制重选 */

    GAS_OM_RESEL_CAUSE_BUTT
};
typedef VOS_UINT8 GAS_OM_RESEL_CAUSE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : GAS_OM_RESULT_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  : GAS -> OM   执行结果
*****************************************************************************/
enum GAS_OM_RESULT_ENUM
{
    GAS_OM_RESULT_FAILURE                           = 0,   /* 失败 */
    GAS_OM_RESULT_SUCCESS                           = 1,   /* 成功 */

    GAS_OM_RESULT_BUTT
};
typedef VOS_UINT8 GAS_OM_RESULT_ENUM_UINT8;


/*****************************************************************************
 枚举名    : GAS_OM_TBF_ABNORMAL_REL_CAUSE_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  : GAS -> OM   TBF异常释放原因
*****************************************************************************/
enum GAS_OM_TBF_ABNORMAL_REL_CAUSE_ENUM
{
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_OTHERS                    = 0,   /* 待定 */
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_T3162_TIMEOUT             = 1,   /* T3162超时 */  
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_T3164_TIMEOUT             = 2,   /* T3164超时 */  
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_T3166_TIMEOUT             = 3,   /* T3166超时 */ 
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_T3168_TIMEOUT             = 4,   /* T3168超时 */
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_T3146_OR_T3170_TIMEOUT    = 5,   /* T3146/T3170超时 */    
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_T3186_TIMEOUT             = 6,   /* T3186超时 */ 
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_UL_ACK_TIMEOUT            = 7,   /* EVT_GAS_GRR_PT_WAIT_PKT_UL_ACK超时 */
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_SINGLE_BLOCK_TIMEOUT      = 8,   /* T3168超时 */
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_ACTIVE_PHY_FAIL           = 9,   /* 激活物理层失败 */
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_GRR_PT_MPHP_PDCH_REL      = 10,  /* PDCH保护定时器超时 */
    GAS_OM_PKT_TBF_RELEASE_ABNORMAL                         = 11,  /* packet tbf release */
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_BUTT
};
typedef VOS_UINT8 GAS_OM_TBF_ABNORMAL_REL_CAUSE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : GAS_OM_RR_CONNECTION_ABNORMAL_TYPE_ENUM_UINT32
 协议表格  :
 ASN.1描述 :
 枚举说明  : GAS -> OM   RR连接异常类型
*****************************************************************************/
enum GAS_OM_RR_CONNECTION_ABNORMAL_TYPE_ENUM
{
    GAS_OM_RR_CONNECTION_ABNORMAL_TYPE_EST   = 0,      /* 链路建立失败 */
    GAS_OM_RR_CONNECTION_ABNORMAL_TYPE_REL   = 1,      /* 链路异常释放 */
    
    GAS_OM_RR_CONNECTION_ABNORMAL_TYPE_BUTT
};
typedef VOS_UINT32 GAS_OM_RR_CONNECTION_ABNORMAL_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_ENUM_UINT32
 协议表格  :
 ASN.1描述 :
 枚举说明  : GAS -> OM   RR连接异常原因
*****************************************************************************/
enum GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_ENUM
{
    GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_OTHERS                   = 0, /* 待定 */                        
    GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_APPLY_RESOURCE_FAIL      = 1, /* 申请资源失败 */                
    GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_PT_TIMEOUT               = 2, /* 保护定时器超时 */              
    GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_IMMASS_INVALID           = 3, /* 立即指派非法 */                
    GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_CHANNEL_REQ_INVALID      = 4, /* 构造CHANNEL REQUEST失败 */     
    GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_RA_SEND_FAIL             = 5, /* RA发送失败 */                  
    GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_REL_BY_NETWORK           = 6, /* 网侧主动释放链路 */            
    GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_REL_RRMM_ABORT_EXCEPTION = 7, /* 异常释放链路 */                                 
    GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_REL_HANDOVER_EXCEPTION   = 8, /* 异常释放链路 */                                   
    GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_REL_RADIO_LINK_FAILURE   = 9, /* 异常释放链路 */                             
    GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_BUTT                                      
};
typedef VOS_UINT32 GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : OM_GAS_OTA_SWITCH_ENUM_UINT32
 协议表格  :
 ASN.1描述 :
 枚举说明  : OM -> GAS 空口消息配置开关
*****************************************************************************/
enum OM_GAS_OTA_SWITCH_ENUM
{
    GSM_OTA_SWITCH_OFF   = 0,     /* 停止上报空口消息 */
    GSM_OTA_SWITCH_ON    = 1      /* 开始上报空口消息 */
};
typedef VOS_UINT32   GSM_OTA_SWITCH_ENUM_UINT32;
/*****************************************************************************
 枚举名    : GSM_OTA_CNF_ERRCODE_ENUM_UINT32
 协议表格  :
 ASN.1描述 :
 枚举说明  : GAS -> OM 空口消息配置结果
*****************************************************************************/
enum GSM_OTA_CNF_ERRCODE_ENUM
{
    GSM_OTA_CNF_ERRCODE_NO    = 0,     /* 空口配置成功 */
    GSM_OTA_CNF_ERRCODE_YES   = 1      /* 空口配置失败 */
};
typedef VOS_UINT32   GSM_OTA_CNF_ERRCODE_ENUM_UINT32;
/*****************************************************************************
 枚举名    : GSM_OTA_DIRECTION_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  : GAS -> OM 空口消息方向
*****************************************************************************/
enum GAS_OM_OTA_CNF_RESULT_ENUM
{
    GSM_OTA_DIRECTION_UP     = 0,     /* 空口配置方向: 上行(MS-->Network) */
    GSM_OTA_DIRECTION_DOWN   = 1      /* 空口配置方向: 下行(Network-->MS) */
};
typedef VOS_UINT8   GSM_OTA_DIRECTION_ENUM_UINT8;

/*****************************************************************************
 枚举名    : GAS_OM_NCELL_LIST_CHANGE_CAUSE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 邻区改变原因枚举
*****************************************************************************/
enum GAS_OM_NCELL_LIST_CHANGE_CAUSE_ENUM
{
    GAS_NCELL_LIST_CHANGE_CAUSE_INDIVIDUAL_NET_CTRL       = 0, /*邻区改变是由网络侧单独下发的PMO, PCCO引起的*/
    GAS_NCELL_LIST_CHANGE_CAUSE_SYSTEM_INFORMATION_UPDATE = 1  /*邻区改变是由系统消息更新引起的*/
};
typedef VOS_UINT8 GAS_OM_NCELL_LIST_CHANGE_CAUSE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : GAS_OM_REDIR_L2G_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 重定向 L2G的失败原因值
*****************************************************************************/
enum GAS_OM_REDIR_L2G_RESULT_ENUM
{
    GAS_OM_REDIR_L2G_RESULT_SUCC                        = 0 ,   /* 重定向成功 */
    GAS_OM_REDIR_L2G_RESULT_FAIL_UE_NOT_SUPPORT             ,   /* UE不支持 GSM或者频段 */
    GAS_OM_REDIR_L2G_RESULT_FAIL_LOAD_DSP                   ,   /* 加载DSP失败 */
    GAS_OM_REDIR_L2G_RESULT_NO_SUITABLE_CELL                ,   /* 全频搜网读系统消息后依然没有满足条件的小区，重定向失败 */
    GAS_OM_REDIR_L2G_RESULT_LRRC_STOP_REDIR                 ,   /* LRRC要求停止重定向 */

    GAS_OM_REDIR_L2G_RESULT_BUTT
};
typedef VOS_UINT8 GAS_OM_REDIR_L2G_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : GAS_OM_ANR_L2G_RESULT_ENUM
 枚举说明  : ANR L2G的退出原因值
 修改历史  : 
 1.日    期    : 2012-04-19
   作    者    : w00176595
   修改内容    : 新建枚举类型
*****************************************************************************/
enum GAS_OM_ANR_L2G_RESULT_ENUM
{
    GAS_OM_ANR_L2G_RESULT_SUCC                        = 0 ,   /* ANR成功 */
    GAS_OM_ANR_L2G_RESULT_ABNORMAL                        ,   /* G模不支持或者频点不支持 */
    GAS_OM_ANR_L2G_PHY_START_FAIL                         ,   /* 物理层启动ANR失败 */
    GAS_OM_ANR_L2G_PHY_START_TIMEOUT                      ,   /* 物理层启动ANR超时 */
    GAS_OM_ANR_L2G_MEAS_RESULT_INVALID                    ,   /* 物理层测量结果无效 */
    GAS_OM_ANR_L2G_BCCH_READ_FAIL                         ,   /* 系统消息读取失败  */
    GAS_OM_ANR_L2G_BCCH_READ_TIMEOUT                      ,   /* 读系统消息超时  */
    GAS_OM_ANR_L2G_MEAS_TIMEOUT                           ,   /* 物理层测量超时 */
    GAS_OM_ANR_L2G_STOP_MEAS_TIMEOUT                      ,   /* 物理层停止测量超时 */
    GAS_OM_ANR_L2G_STOP_BCCH_READING_TIMEOUT              ,   /* 物理层停止读系统消息超时 */

    GAS_OM_ANR_L2G_RESULT_BUTT
};
typedef VOS_UINT8 GAS_OM_ANR_L2G_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : GAS_OM_RESEL_CCO_W2G_RESULT_ENUM
 枚举说明  : W2G Resel/CCO的退出原因值
 修改历史  : 
 1.日    期    : 2012-04-19
   作    者    : w00176595
   修改内容    : 新建枚举类型
*****************************************************************************/
enum GAS_OM_RESEL_CCO_W2G_RESULT_ENUM
{
    GAS_OM_RESEL_CCO_W2G_RESULT_SUCC                        = 0 ,   /* Resel/CCO成功 */
    GAS_OM_RESEL_CCO_W2G_RESULT_FAIL                            ,   /* Resel/CCO流程中失败 */
    GAS_OM_RESEL_CCO_W2G_RESULT_NOT_EPLMN                       ,   /* 非等效PLMN */
    GAS_OM_RESEL_CCO_W2G_RESULT_FORBIDDEN_LAI                   ,   /* LAI被禁 */
    GAS_OM_RESEL_CCO_W2G_RESULT_CELL_BARRED                     ,   /* 小区被BAR */
    GAS_OM_RESEL_CCO_W2G_RESULT_ACCESS_NOT_PERMIT               ,   /* 小区接入禁止  */
    GAS_OM_RESEL_CCO_W2G_RESULT_C1                              ,   /* C1小于0  */

    GAS_OM_RESEL_CCO_W2G_RESULT_BUTT
};
typedef VOS_UINT8 GAS_OM_RESEL_CCO_W2G_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_ENUM
 枚举说明  : 背景方式列表搜结果值
 修改历史  : 
  1.日    期   : 2012-05-07
    作    者   : s00184266
    修改内容   : 新建枚举类型
  2.日    期   : 2014年3月15日
    作    者   : s00184266
    修改原因   : multi-mode evolution phase I, 新增WRRC相关的列表搜结果值
*****************************************************************************/
enum GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_ENUM
{
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_SUCC                        = 0x0 ,       /* 列表搜成功 */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_MPH_FULL_LIST_CNF_ERROR           ,       /* 列表搜 GSM扫频错误 */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_MPH_FULL_LIST_CNF_TIMEOUT         ,       /* 列表搜 GSM扫频回复超时 */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_WRRC_START_FAIL                   ,       /* 列表搜 WCDMA启动WRRC失败 */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_WRRC_START_TIMEOUT                ,       /* 列表搜 WCDMA启动WRRC超时 */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_WRRC_IND_TIMEOUT                  ,       /* 列表搜 WCDMA等待结果超时 */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_WRRC_STOP_TIMEOUT                 ,       /* 列表搜 WCDMA停WRRC超时 */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_LRRC_START_FAIL                   ,       /* 列表搜 LTE启动LRRC失败 */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_LRRC_START_TIMEOUT                ,       /* 列表搜 LTE启动LRRC超时 */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_MPH_START_FAIL                    ,       /* 列表搜 WCDMA/LTE启动GPHY失败 */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_MPH_START_TIMEOUT                 ,       /* 列表搜 WCDMA/LTE启动GPHY超时 */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_LRRC_IND_TIMEOUT                  ,       /* 列表搜 LTE等待结果超时 */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_MPH_STOP_TIMEOUT                  ,       /* 列表搜 WCDMA/LTE停GPHY超时 */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_LRRC_STOP_TIMEOUT                 ,       /* 列表搜 LTE停LRRC超时 */

    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_FREQ_SEARCH_TIMEOUT               ,       /* 列表搜 GSM扫频超时 */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_MPH_FULL_LIST_STOP_TIMEOUT        ,       /* 列表搜 GSM停止扫频超时 */

    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_NO_RF,

    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_BUTT
};
typedef VOS_UINT8 GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : GAS_OM_BG_PLMN_SEARCH_LTE_EVENT_ENUM
 枚举说明  : 背景搜LTE结果值
 修改历史  : 
 1.日    期    : 2012-05-14
   作    者    : w00146666
   修改内容    : 新建枚举类型
*****************************************************************************/
enum GAS_OM_BG_PLMN_SEARCH_LTE_ABNORMAL_EVENT_ENUM
{
    GAS_OM_BG_PLMN_SEARCH_LTE_ABNORMAL_EVENT_LRRC_START_TIMEOUT     = 0x0 ,       /* 背景搜LTE */
    GAS_OM_BG_PLMN_SEARCH_LTE_ABNORMAL_EVENT_LRRC_RESUME_TIMEOUT,
    GAS_OM_BG_PLMN_SEARCH_LTE_ABNORMAL_EVENT_GPHY_START_TIMEOUT,
    GAS_OM_BG_PLMN_SEARCH_LTE_ABNORMAL_EVENT_LRRC_SEARCH_IND_TIMEOUT,
    GAS_OM_BG_PLMN_SEARCH_LTE_ABNORMAL_EVENT_GPHY_STOP_TIMEOUT,
    GAS_OM_BG_PLMN_SEARCH_LTE_ABNORMAL_EVENT_LRRC_STOP_TIMEOUT,
    GAS_OM_BG_PLMN_SEARCH_LTE_ABNORMAL_EVENT_LRRC_SUSPEND_TIMEOUT,
    GAS_OM_BG_PLMN_SEARCH_LTE_ABNORMAL_EVENT_GPHY_CNF_TYPE_DISMATCH,
    
    GAS_OM_BG_PLMN_SEARCH_LTE_ABNORMAL_EVENT_BUTT
};

typedef VOS_UINT8 GAS_OM_BG_PLMN_SEARCH_LTE_ABNORMAL_EVENT_ENUM_UINT8;


/*****************************************************************************
 枚举名    : GAS_OM_RESEL_EVALUATE_RMV_CELL_CAUSE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 重选评估失败的原因值，失败的小区要从重选评估列表中删除
*****************************************************************************/
enum GAS_OM_RESEL_EVALUATE_RMV_CELL_CAUSE_ENUM
{
    GAS_OM_RESEL_EVALUATE_RMV_CELL_CAUSE_RAT_NOT_SUPPORTED                      = 0 ,   /* 接入技术不支持 */
    GAS_OM_RESEL_EVALUATE_RMV_CELL_CAUSE_ARFCN_NOT_SUPPORTED                    ,       /* 频点不支持 */
    GAS_OM_RESEL_EVALUATE_RMV_CELL_CAUSE_ARFCN_DELETED                          ,       /* 频点被删除 */
    GAS_OM_RESEL_EVALUATE_RMV_CELL_CAUSE_NCELL_DELETED                          ,       /* 小区被删除 */
    GAS_OM_RESEL_EVALUATE_RMV_CELL_CAUSE_NOT_PASS_EVALUATION                    ,       /* 不满足重选条件 */

    GAS_OM_RESEL_EVALUATE_RMV_CELL_CAUSE_BUTT
};
typedef VOS_UINT8 GAS_OM_RESEL_EVALUATE_RMV_CELL_CAUSE_ENUM_UINT8;

/* Added by yangsicong for probe接口新开发, 2012-10-30, begin */
/*****************************************************************************
 枚举名    : GAS_ROAD_TEST_INFO_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 为路测软件PROBE提供的信息类型
*****************************************************************************/
enum GAS_ROAD_TEST_INFO_TYPE_ENUM
{
    GAS_ROAD_TEST_INFO_TYPE_MEAS_RESULT         =   0x00,   /* 测量结果 */
    GAS_ROAD_TEST_INFO_TYPE_SCELL_PARA                  ,   /* 服务小区参数 */
    GAS_ROAD_TEST_INFO_TYPE_SCELL_DCH_CHAN_PARA         ,   /* DCH参数 */
    GAS_ROAD_TEST_INFO_TYPE_BUTT  
};
typedef VOS_UINT16 GAS_ROAD_TEST_INFO_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : GAS_OM_GSM_RUNNING_MODE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 为路测软件PROBE提供的当前的GSM运行状态( 空闲或语音 )类型
*****************************************************************************/
enum GAS_OM_GSM_RUNNING_MODE_ENUM
{
    GAS_OM_GSM_RUNNING_MODE_IDLE              =   0x01,   /* GSM 空闲模式 */
    GAS_OM_GSM_RUNNING_MODE_DEDICATE                  ,   /* GSM 专用模式 */
    GAS_OM_GSM_RUNNING_MODE_BUTT  
};
typedef VOS_UINT16 GAS_OM_GSM_RUNNING_MODE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : GAS_OM_GPRS_RUNNING_MODE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 为路测软件PROBE提供的当前的GPRS运行状态( 空闲或数传 )类型
*****************************************************************************/
enum GAS_OM_GPRS_RUNNING_MODE_ENUM
{
    GAS_OM_GPRS_RUNNING_MODE_IDLE              =   0x01,  /* GPRS 空闲模式 */
    GAS_OM_GPRS_RUNNING_MODE_DATA_TRANSFER             ,  /* GPRS 数传模式 */
    GAS_OM_GPRS_RUNNING_MODE_BUTT  
};
typedef VOS_UINT16 GAS_OM_GPRS_RUNNING_MODE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : GAS_OM_RR_CIPHER_ALGORITHM_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : CS域加密算法枚举
*****************************************************************************/
enum GAS_OM_RR_CIPHER_ALGORITHM_ENUM
{
    GAS_OM_RR_CIPHER_ALGORITHM_NONE             =   0,
    GAS_OM_RR_CIPHER_ALGORITHM_A51              =   1,
    GAS_OM_RR_CIPHER_ALGORITHM_A52              =   2,
    GAS_OM_RR_CIPHER_ALGORITHM_A53              =   3,
    GAS_OM_RR_CIPHER_ALGORITHM_A54              =   4,
    GAS_OM_RR_CIPHER_ALGORITHM_A55              =   5,
    GAS_OM_RR_CIPHER_ALGORITHM_A56              =   6,
    GAS_OM_RR_CIPHER_ALGORITHM_A57              =   7,

    GAS_OM_RR_CIPHER_ALGORITHM_BUTT
};
typedef VOS_UINT16 GAS_OM_RR_CIPHER_ALGORITHM_ENUM_UINT16;

/*****************************************************************************
 枚举名    : GAS_OM_NETWORK_CONTROL_ORDER_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 网络控制模式枚举
*****************************************************************************/
enum GAS_OM_NETWORK_CONTROL_ORDER_ENUM
{
    GAS_OM_NETWORK_CONTROL_ORDER_NC0              =   0,
    GAS_OM_NETWORK_CONTROL_ORDER_NC1              =   1,
    GAS_OM_NETWORK_CONTROL_ORDER_NC2              =   2,

    GAS_OM_NETWORK_CONTROL_ORDER_BUTT
};
typedef VOS_UINT16 GAS_OM_NETWORK_CONTROL_ORDER_ENUM_UINT16;

/*****************************************************************************
 枚举名    : GAS_OM_VOICE_CHANNEL_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 语音编码器使用的信道类型
*****************************************************************************/
enum GAS_OM_VOICE_CHANNEL_TYPE_ENUM
{
    GAS_OM_VOICE_CHANNEL_TYPE_TCH_F         = 1,             /* TCH_F */
    GAS_OM_VOICE_CHANNEL_TYPE_TCH_H            ,             /* TCH_H  */
    GAS_OM_VOICE_CHANNEL_TYPE_SDCCH_4          ,             /* SDCCH_4  */
    GAS_OM_VOICE_CHANNEL_TYPE_SDCCH_8          ,             /* SDCCH_8 */
    
    GAS_OM_VOICE_CHANNEL_TYPE_BUTT
};
typedef VOS_UINT16  GAS_OM_VOICE_CHANNEL_TYPE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : GAS_OM_SPECCH_CODEC_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 语音编码方式
*****************************************************************************/
enum GAS_OM_SPECCH_CODEC_ENUM
{
    GAS_OM_SPECCH_CODEC_ONLY,            /* 仅信令模式*/
    GAS_OM_SPECCH_CODEC_FR,             /* Full Rate */
    GAS_OM_SPECCH_CODEC_EFR,            /* Enhanced Full Rate  */
    GAS_OM_SPECCH_CODEC_AFS,            /* Enhanced Full Rate  */
    GAS_OM_SPECCH_CODEC_CSD_2400,
    GAS_OM_SPECCH_CODEC_CSD_4800,
    GAS_OM_SPECCH_CODEC_CSD_9600,
    GAS_OM_SPECCH_CODEC_CSD_14400,
    GAS_OM_SPECCH_CODEC_HR,             /* half Rate */
    GAS_OM_SPECCH_CODEC_AHR,            /* half Rate */
    GAS_OM_SPECCH_CODEC_H24,            /* Adaptive Multi-Rate */
    GAS_OM_SPECCH_CODEC_H48,            /* Adaptive Multi-Rate */
    GAS_OM_SPECCH_CODEC_WFS,            /* Adaptive Multi-Rate,WFS业务 */
    
    GAS_OM_SPECCH_CODEC_BUTT
};
typedef VOS_UINT16  GAS_OM_SPECCH_CODEC_ENUM_UINT16;


/* Added by yangsicong for probe接口新开发, 2012-10-30, end */


#if ( FEATURE_ON == FEATURE_DSDS )
/*******************************************************************************
 枚举名    : GAS_OM_TASK_STATUS_ENUM_UINT16
 结构说明  : OM申请任务的资源状态
 1.日    期   : 2014年02月12日
   作    者   : l67237
   修改内容   : Added for GAS DSDS
*******************************************************************************/
enum GAS_OM_TASK_STATUS_ENUM
{
    GAS_OM_TASK_STATUS_NONE                             = 0,                    /* 无状态 */
    GAS_OM_TASK_STATUS_APPLYING                         = 1,                    /* 任务资源正在申请中 */
    GAS_OM_TASK_STATUS_USING                            = 2,                    /* 任务资源申请完成，使用中 */
    GAS_OM_TASK_STATUS_BUTT
};
typedef VOS_UINT16 GAS_OM_TASK_STATUS_ENUM_UINT16;
#endif

/*****************************************************************************
 枚 举 名  : GAS_OM_SEARCH_PROC_ENUM
 枚举说明  : 搜网流程枚举
 修改历史  :
  1.日  期   : 2015年9月10日
    作  者   : s00184266
    修改内容 : 新生成枚举

*****************************************************************************/
enum GAS_OM_SEARCH_PROC_ENUM
{
    GAS_OM_SEARCH_PROC_L_REDIR_G_SPEC_SRCH              = 0,
    GAS_OM_SEARCH_PROC_L_REDIR_G_HISTORY_SRCH              ,
    GAS_OM_SEARCH_PROC_L_REDIR_G_CLOUD_FREQ_SRCH           ,
    GAS_OM_SEARCH_PROC_L_REDIR_G_OPERATE_CUSTOM_FREQ_SRCH  ,
    GAS_OM_SEARCH_PROC_L_REDIR_G_HISTORY_FREQ_BAND_SRCH    ,
    GAS_OM_SEARCH_PROC_L_REDIR_G_PRESET_FREQ_BAND_SRCH     ,
    GAS_OM_SEARCH_PROC_L_REDIR_G_PRESET_BAND_SRCH          ,
    GAS_OM_SEARCH_PROC_L_REDIR_G_FULL_LIST_SRCH            ,

    GAS_OM_SEARCH_PROC_SPEC_SRCH_HISOTRY_FREQ_SRCH         ,
    GAS_OM_SEARCH_PROC_SPEC_SRCH_CLOUD_FREQ_SRCH           ,
    GAS_OM_SEARCH_PROC_SPEC_SRCH_OPERATE_CUSTOM_FREQ_SRCH  ,
    GAS_OM_SEARCH_PROC_SPEC_SRCH_HISTORY_FREQ_BAND_SRCH    ,
    GAS_OM_SEARCH_PROC_SPEC_SRCH_PRESET_FREQ_BAND_SRCH     ,
    GAS_OM_SEARCH_PROC_SPEC_SRCH_PRESET_BAND_SRCH          ,
    GAS_OM_SEARCH_PROC_SPEC_SRCH_FULL_LIST_SRCH            ,

    GAS_OM_SEARCH_PROC_GOOS_SRCH_HISTORY_FREQ_SRCH         ,
    GAS_OM_SEARCH_PROC_GOOS_SRCH_CLOUD_FREQ_SRCH           ,
    GAS_OM_SEARCH_PROC_GOOS_SRCH_OPERATE_CUSTOM_FREQ_SRCH  ,
    GAS_OM_SEARCH_PROC_GOOS_SRCH_HISTORY_FREQ_BAND_SRCH    ,
    GAS_OM_SEARCH_PROC_GOOS_SRCH_PRESET_FREQ_BAND_SRCH     ,
    GAS_OM_SEARCH_PROC_GOOS_SRCH_PRESET_BAND_SRCH          ,
    GAS_OM_SEARCH_PROC_GOOS_SRCH_FULL_LIST_SRCH            ,

    GAS_OM_SEARCH_PROC_BUTT
};
typedef VOS_UINT8 GAS_OM_SEARCH_PROC_ENUM_UINT8;

/*****************************************************************************
 枚 举 名  : GAS_OM_SEARCH_PROC_BUILD_RESULT_ENUM
 枚举说明  : 流程构建频点列表结果
 修改历史  :
  1.日  期   : 2015年9月10日
    作  者   : s00184266
    修改内容 : 新生成枚举
  2.日    期   : 2015年12月16日
    作    者   : s00184266
    修改原因   : dts2015121505454, 新增获取CSS频段信息失败的枚举

*****************************************************************************/
enum GAS_OM_SEARCH_PROC_BUILD_RESULT_ENUM
{
    GAS_OM_SEARCH_PROC_BUILD_RESULT_SUCC                = 0,
    GAS_OM_SEARCH_PROC_BUILD_RESULT_NV_DISABLE             ,
    GAS_OM_SEARCH_PROC_BUILD_RESULT_BUILD_NULL_FREQ_LIST   ,
    GAS_OM_SEARCH_PROC_BUILD_RESULT_FILTER_ALL_FREQ_LIST   ,
    GAS_OM_SEARCH_PROC_BUILD_RESULT_BUILD_NULL_BAND_LIST   ,
    GAS_OM_SEARCH_PROC_BUILD_RESULT_NULL_FREQ_IN_BAND      ,
    GAS_OM_SEARCH_PROC_BUILD_RESULT_ALL_BAND_HAD_SRCHED    ,
    GAS_OM_SEARCH_PROC_BUILD_RESULT_ERROR_DURING_GET_CSS_BAND,

    GAS_OM_SEARCH_PROC_BUILD_RESULT_BUTT
};
typedef VOS_UINT8 GAS_OM_SEARCH_PROC_BUILD_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚 举 名  : GAS_OM_CSS_INTERFACE_NAME_ENUM
 枚举说明  : GAS调用CSS提供的云端函数名枚举
 修改历史  :
  1.日  期   : 2015年11月5日
    作  者   : s00184266
    修改内容 : 新生成枚举

*****************************************************************************/
enum GAS_OM_CSS_INTERFACE_NAME_ENUM
{
    GAS_OM_CSS_INTERFACE_NAME_IS_MCC_FREQ_EXIST         = 0,
    GAS_OM_CSS_INTERFACE_NAME_GET_PREFER_FREQ_INFO         ,
    GAS_OM_CSS_INTERFACE_NAME_GET_PREFER_BAND_INFO         ,
    GAS_OM_CSS_INTERFACE_NAME_INPUT_PLMN_INFO              ,
    
    GAS_OM_CSS_INTERFACE_NAME_BUTT
};
typedef VOS_UINT32 GAS_OM_CSS_INTERFACE_NAME_ENUM_UINT32;


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
 结 构 名  : DIAG_GAS_MSG_COMM_HEAD_ST
 结构描述  : DIAG消息公共头
 修改历史      :
  1.日    期   : 2016年6月23日
    作    者   : 华宏 h00166210
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */

    VOS_UINT32                          ulMsgId;

    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;
} DIAG_GAS_MSG_COMM_HEAD_ST;

/*****************************************************************************
 结 构 名  : OM_GAS_INFO_REQ_ST
 结构描述  : OM消息查询的结构。

 修改历史      :
  1.日    期   : 2008年4月19日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    DIAG_GAS_MSG_COMM_HEAD_ST           stMsgCommHead;

    OM_GAS_REPORT_ACTION_ENUM_UINT16    enStartOrStop;
    OM_GAS_REPORT_TYPE_ENUM_UINT16      enReportType;
    VOS_UINT16                          usReportPeriod;   /* 单位: s */
    VOS_UINT16                          usReserved;
} OM_GAS_INFO_REQ_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_INFO_CNF_ST
 结构描述  : GAS回复消息确认的结构。

 修改历史      :
  1.日    期   : 2008年4月19日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    DIAG_GAS_MSG_COMM_HEAD_ST           stMsgCommHead;

    VOS_UINT16                          usResult;
    VOS_UINT16                          usReserved;
    OM_GAS_REPORT_ACTION_ENUM_UINT16    enStartOrStop;
    OM_GAS_REPORT_TYPE_ENUM_UINT16      enReportType;
} GAS_OM_INFO_CNF_ST;

/*****************************************************************************
 结构名    : GAS_OM_EVENT_IND_STRUCT
 协议表格  :
 ASN.1描述 :
 结构说明  :协议栈和OM事件上报结构
*****************************************************************************/
typedef struct
{
    OM_GAS_MSG_ID_ENUM_UINT16           usEventId;          /*_H2ASN_MsgChoice_Export OM_GAS_MSG_ID_ENUM_UINT16*/
    VOS_UINT16                          usReserved;
    VOS_UINT32                          ulModuleId;         /*发送模块PID ，工具根据PID可以屏蔽消息*/
    VOS_UINT8                           aucData[4];

    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          OM_GAS_MSG_ID_ENUM_UINT16
    ****************************************************************************/
}GAS_OM_EVENT_IND_ST;
/*****************************************************************************
 结 构 名  : GAS_OM_CELL_BASIC_INFO_ST
 结构描述  : 小区基本信息的结构体。

 修改历史      :
  1.日    期   : 2008年4月19日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT16                       usArfcn;
    VOS_UINT8                        ucNcc;
    VOS_UINT8                        ucBcc;
    GAS_OM_GSM_BAND_ENUM_UINT16      enBand;
    VOS_INT16                        sRxLev;
    VOS_INT16                        sC1;
    VOS_INT16                        sC2;
    VOS_INT16                        sC31;
    VOS_INT16                        sC32;
    VOS_UINT16                       usLac;
    VOS_UINT8                        ucRac; 
    VOS_UINT8                        ucPriorityClass; 
    VOS_UINT16                       usTimerStatus;          /* 定时器状态,0为未启动，1为启动 */
    VOS_UINT16                       usRsv;
} GAS_OM_CELL_BASIC_INFO_ST;

/*****************************************************************************
 结 构 名  : OM_GAS_CELL_INFO_REQ_ST
 结构描述  : OM 发出的 小区信息查询请求

 修改历史      :
  1.日    期   : 2008年4月19日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef OM_GAS_INFO_REQ_ST  OM_GAS_CELL_INFO_REQ_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_CELL_INFO_CNF_ST
 结构描述  : GAS对小区信息查询请求的确认

 修改历史      :
  1.日    期   : 2008年4月19日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef GAS_OM_INFO_CNF_ST  GAS_OM_CELL_INFO_CNF_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_CELL_COMM_INFO_ST
 结构描述  : GAS向OM上报服务小区的一般信息。

 修改历史      :
  1.日    期   : 2008年10月13日
    作    者   : 刘德国  00126771
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    NAS_GMM_STATE_ENUM_UINT8                enGmmState;
    VOS_UINT8                               ucCRH;
    VOS_UINT8                               ucRecentReselection;
    VOS_UINT8                               ucPbcchFlag;
    VOS_UINT8                               ucEgprsFlag;
    VOS_UINT8                               astRsv[3];    /*保留位*/
}GAS_OM_CELL_COMM_INFO_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_CELL_INFO_IND_ST
 结构描述  : GAS向OM上报服务小区和最强邻区信息。

 修改历史      :
  1.日    期   : 2008年4月19日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    OM_GAS_REPORT_TYPE_ENUM_UINT16          enReportType;
    VOS_UINT16                              us2GNCellNum;
    GAS_OM_CELL_COMM_INFO_ST                stCommInfo;
    GAS_OM_CELL_BASIC_INFO_ST               stSCellInfo;
    GAS_OM_CELL_BASIC_INFO_ST               astNCellInfo[6];
} GAS_OM_CELL_INFO_IND_ST;

/*****************************************************************************
 结 构 名  : GAS_MSP_CELL_INFO_IND_ST
 结构描述  : GAS向MSP上报服务小区和最强邻区信息。

 修改历史      :
  1.日    期   : 2015年9月18日
    作    者   : 华宏 h00166210
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPrimId;
    VOS_UINT16                          usReserved;

    OM_GAS_REPORT_TYPE_ENUM_UINT16      enReportType;
    VOS_UINT16                          us2GNCellNum;
    GAS_OM_CELL_COMM_INFO_ST            stCommInfo;
    GAS_OM_CELL_BASIC_INFO_ST           stSCellInfo;
    GAS_OM_CELL_BASIC_INFO_ST           astNCellInfo[6];
} GAS_MSP_CELL_INFO_IND_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_DCH_QUALITY_ST
 结构描述  : GAS向OM上报DCH信道的信道质量

 修改历史      :
  1.日    期   : 2008年4月19日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_INT16         sRxlevFull;
    VOS_INT16         sRxlevSub;
    VOS_UINT16        usNumBitMeasFull;
    VOS_UINT16        usNumBitMeasSub;
    VOS_UINT16        usNumErrBitFull;
    VOS_UINT16        usNumErrBitSub;
    VOS_UINT16        usBERFull;
    VOS_UINT16        usBERSub;
    VOS_UINT16        usRxqualFull;
    VOS_UINT16        usRxqualSub;
} GAS_OM_DCH_QUALITY_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_PDTCH_QUALITY_ST
 结构描述  : GAS向OM上报PDTCH信道的信道质量

 修改历史      :
  1.日    期   : 2008年4月19日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT16         usBitsErrNum;
    VOS_UINT16         usBitsTotalNum;
    VOS_UINT16         usBER;
    VOS_UINT16         usRxqual;
    VOS_UINT16         usSCellC;
    VOS_UINT16         usSignalVar;
    VOS_UINT16         ausInLevelTn[8];
} GAS_OM_PDTCH_QUALITY_ST;

/*****************************************************************************
 结 构 名  : OM_GAS_CHANNEL_QUALITY_REQ_ST
 结构描述  : OM 发出的 信道质量查询请求

 修改历史      :
  1.日    期   : 2008年4月19日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef OM_GAS_INFO_REQ_ST  OM_GAS_CHANNEL_QUALITY_REQ_ST;


/*****************************************************************************
 结 构 名  : GAS_OM_CHANNEL_QUALITY_CNF_ST
 结构描述  : GAS对信道质量查询请求的确认

 修改历史      :
  1.日    期   : 2008年4月19日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef GAS_OM_INFO_CNF_ST  GAS_OM_CHANNEL_QUALITY_CNF_ST;


/*****************************************************************************
 结 构 名  : GAS_OM_CHANNEL_QUALITY_IND_ST
 结构描述  : GAS向OM上报信道质量

 修改历史      :
  1.日    期   : 2008年4月19日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    OM_GAS_REPORT_TYPE_ENUM_UINT16      enReportType;
    GAS_DCH_TYPE_ENUM_UINT16            enDchType;
    GAS_OM_DCH_QUALITY_ST               stDchQuality;
    GAS_OM_PDTCH_QUALITY_ST             stPdtchQuality;
} GAS_OM_CHANNEL_QUALITY_IND_ST;


/*****************************************************************************
 结 构 名  : GAS_OM_3G_NCELL_INFO_ST
 结构描述  : GAS向OM上报3G(WCDMA)邻区的信息

 修改历史      :
  1.日    期   : 2008年4月19日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT16                     usUARFCN;          /* 频点 */
    VOS_UINT16                     usPSC;             /* 主扰码 */

    VOS_INT16                      sRSCP;             /* RSCP值 */
    VOS_INT16                      sEcNo;             /* EcNo值 */
    VOS_INT16                        s3GNcellRSSI;
    VOS_INT16                        sReserved;

} GAS_OM_3G_NCELL_INFO_ST;

/*****************************************************************************
 结 构 名  : OM_GAS_3G_NCELL_MEAS_REQ_ST
 结构描述  : OM 发出的 3G邻小区测量信息查询请求

 修改历史      :
  1.日    期   : 2008年4月19日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef OM_GAS_INFO_REQ_ST  OM_GAS_3G_NCELL_MEAS_REQ_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_3G_NCELL_MEAS_CNF_ST
 结构描述  : GAS对3G邻小区测量查询请求的确认

 修改历史      :
  1.日    期   : 2008年4月19日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef GAS_OM_INFO_CNF_ST  GAS_OM_3G_NCELL_MEAS_CNF_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_3G_SETTINGS_ST
 结构描述  : GAS上报3G邻区的配置信息

 修改历史      :
  1.日    期   : 2008年10月13日
    作    者   : 刘德国  00126771
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucQsearch_I;
    VOS_UINT8                               ucQsearch_C;
    VOS_UINT8                               ucQsearch_P;
    VOS_INT8                                cFDD_Qmin;
    VOS_INT16                               sFDD_Qoffset;
    VOS_UINT16                              usRsv;
}GAS_OM_3G_SETTINGS_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_3G_NCELL_MEAS_IND_ST
 结构描述  : GAS上报3G邻小区测量信息

 修改历史      :
  1.日    期   : 2008年4月19日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    OM_GAS_REPORT_TYPE_ENUM_UINT16      enReportType;
    VOS_UINT16                          us3GNcellNum;
    GAS_OM_3G_SETTINGS_ST               st3GSettings;
    GAS_OM_3G_NCELL_INFO_ST             ast3GNcellInfo[GAS_OM_3G_NCELL_NUMBER];
} GAS_OM_3G_NCELL_MEAS_IND_ST;

/*****************************************************************************
 结 构 名  : GAS_MSP_3G_NCELL_MEAS_IND_ST
 结构描述  : GAS上报3G邻小区测量信息

 修改历史      :
  1.日    期   : 2015年9月18日
    作    者   : 华宏 h00166210
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPrimId;
    VOS_UINT16                          usReserved;

    OM_GAS_REPORT_TYPE_ENUM_UINT16      enReportType;
    VOS_UINT16                          us3GNcellNum;
    GAS_OM_3G_SETTINGS_ST               st3GSettings;
    GAS_OM_3G_NCELL_INFO_ST             ast3GNcellInfo[GAS_OM_3G_NCELL_NUMBER];
} GAS_MSP_3G_NCELL_MEAS_IND_ST;

/*****************************************************************************
 结 构 名  : OM_GAS_GSM_INFO_REQ_ST
 结构描述  : OM 发出的 GSM 信息查询请求

 修改历史      :
  1.日    期   : 2008年4月19日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef OM_GAS_INFO_REQ_ST  OM_GAS_GSM_INFO_REQ_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_GSM_INFO_CNF_ST
 结构描述  : GAS对 GSM 信息查询请求的确认

 修改历史      :
  1.日    期   : 2008年4月19日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef GAS_OM_INFO_CNF_ST  GAS_OM_GSM_INFO_CNF_ST;

/*****************************************************************************
 结 构 名  : GAS_GSM_INFO_ST
 结构描述  : GSM基本信息

 修改历史      :
  1.日    期   : 2008年4月19日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT32                             ulMcc;           /* 移动国家码 */
    VOS_UINT32                             ulMnc;           /* 移动网络码 */
    VOS_UINT16                             usLAC;           /* 位置区码 */
    VOS_UINT16                             usCellId;        /* 小区 ID */
    VOS_UINT16                             usBcchArfcn;     /* 广播频点号 */
    GAS_OM_STATE_ENUM_UINT16               enGasState;      /* GAS状态 */
}GAS_GSM_INFO_ST;

/*****************************************************************************
 结 构 名  : GAS_TBF_INFO_ST
 结构描述  : GRPS的 TBF 信息

 修改历史      :
  1.日    期   : 2008年4月19日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    GAS_OM_RLC_MODE_ENUM_UINT8             enRlcMode;       /* RLC模式 */
    GAS_OM_MAC_MODE_ENUM_UINT8             enMacMode;       /* MAC模式 */
    VOS_UINT8                              ucTsNum;         /* TBF分配时隙数: [0,8] */
    VOS_UINT8                              ucTsMask;        /* 时隙掩码 */
                                                            /* 0xf0表示分配时隙 0~3 */
    
    GAS_OM_CS_TYPE_ENUM_UINT8              enCS;            /* 编码方式 */
    VOS_UINT8                              ucRsv[3];        /* 保留 */
}GAS_TBF_INFO_ST;

/*****************************************************************************
 结 构 名  : GAS_GPRS_INFO_ST
 结构描述  : 上报给OM的GRPS信息

 修改历史      :
  1.日    期   : 2008年4月19日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT8                              ucGprsSupport;   /* GRPS 是否支持: 0-不支持, 1-支持 */
    VOS_UINT8                              ucEgprsSupport;  /* EGPRS 是否支持: 0-不支持, 1-支持 */
    VOS_UINT8                              ucRAC;           /* 路由区码 */
    VOS_UINT8                              ucPbcchPresent;  /* PBCCH是否存在: 0-不存在, 1-存在*/

    VOS_UINT8                              ucUlTbfPresent;  /* 上行TBF是否存在: 0-不存在, 1-存在*/
    VOS_UINT8                              ucDlTbfPresent;  /* 下行TBF是否存在: 0-不存在, 1-存在*/
    VOS_UINT16                             usReserved;      /* 保留 */
    
    GAS_TBF_INFO_ST                        stUlTbfInfo;     /* 上行TBF信息 */
    GAS_TBF_INFO_ST                        stDlTbfInfo;     /* 下行TBF信息 */
}GAS_GPRS_INFO_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_GSM_INFO_IND_ST
 结构描述  : GAS上报 GSM/GPRS 信息

 修改历史      :
  1.日    期   : 2008年4月19日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    OM_GAS_REPORT_TYPE_ENUM_UINT16         enReportType;
    VOS_UINT16                             usReserved;
    GAS_GSM_INFO_ST                        stGsmInfo;       /* GSM信息 */
    GAS_GPRS_INFO_ST                       stGprsInfo;      /* GPRS信息 */
}GAS_OM_GSM_INFO_IND_ST;





/*****************************************************************************
 结 构 名  : GAS_OM_EVENT_GSM_LINK_FAILURE_ST
 结构描述  : GAS向OM上报事件的描述

 修改历史      :
  1.日    期   : 2008年4月21日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT8              ucLinkInitVaule;     /* 无线链路初始值，范围[4,64] */
    VOS_UINT8              aucReserved[3];      /* 保留 */
} GAS_OM_EVENT_GSM_LINK_FAILURE_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_EVENT_GSM_DOWNLINK_FAILURE_ST
 结构描述  : GAS向OM上报事件的描述

 修改历史      :
  1.日    期   : 2008年4月21日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT8              ucDscInitValue;       /* 下行链路计数器初始值，范围[10,45] */
    VOS_UINT8              aucReserved[3];
} GAS_OM_EVENT_GSM_DOWNLINK_FAILURE_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_EVENT_GSM_RESELECT_START_ST
 结构描述  : GAS向OM上报事件的描述

 修改历史      :
  1.日    期   : 2008年4月21日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    GAS_OM_RESEL_TYPE_ENUM_UINT8      enReselType;    /* 重选类型 */
    GAS_OM_RESEL_CAUSE_ENUM_UINT8     enReselCause;   /* 重选原因 */
    VOS_UINT8                         aucRsv[2];      /* 保留 */
    VOS_UINT16                        usTargetArfcn;  /* 目标频点 */
    VOS_UINT8                         ucNcc;          /* 网络色码 */
    VOS_UINT8                         ucBcc;          /* 基站色码 */
} GAS_OM_EVENT_GSM_RESELECT_START_ST;


/*****************************************************************************
 结 构 名  : GAS_OM_EVENT_GSM_RESELECT_END_ST
 结构描述  : GAS向OM上报事件的描述

 修改历史      :
  1.日    期   : 2008年4月21日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucResult;        /* 执行结果 */
    VOS_UINT8                           aucReserved[3];  /* 保留 */
} GAS_OM_EVENT_GSM_RESELECT_END_ST;


/*****************************************************************************
 结 构 名  : GAS_OM_EVENT_GSM_CAMP_ATTEMPT_START_ST
 结构描述  : GAS向OM上报事件的描述

 修改历史      :
  1.日    期   : 2008年4月21日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT16                        usTargetArfcn;  /* 目标频点 */
    VOS_UINT8                         ucNcc;          /* 网络色码 */
    VOS_UINT8                         ucBcc;          /* 基站色码 */
} GAS_OM_EVENT_GSM_CAMP_ATTEMPT_START_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_EVENT_GSM_CAMP_ATTEMPT_END_ST
 结构描述  : GAS向OM上报事件的描述

 修改历史      :
  1.日    期   : 2008年4月21日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    GAS_OM_RESULT_ENUM_UINT8          enResult;        /* 执行结果，0-失败，1-成功 */
    VOS_UINT8                         aucReserved[3];  /* 保留 */
} GAS_OM_EVENT_GSM_CAMP_ATTEMPT_END_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_EVENT_GSM_TO_WCDMA_RESELECT_START_ST
 结构描述  : GAS向OM上报事件的描述

 修改历史      :
  1.日    期   : 2008年4月21日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    GAS_OM_RESEL_TYPE_ENUM_UINT8      enReselType;   /* 重选类型 */  
    VOS_UINT8                         aucRsv[3];     /* 保留 */
    VOS_UINT16                        usUArfcn;      /* 频点号 */
    VOS_UINT16                        usPSC;         /* 主扰码 */
} GAS_OM_EVENT_GSM_TO_WCDMA_RESELECT_START_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_EVENT_GSM_TO_WCDMA_RESELECT_END_ST
 结构描述  : GAS向OM上报事件的描述

 修改历史      :
  1.日    期   : 2008年4月21日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    GAS_OM_RESULT_ENUM_UINT8          enResult;        /* 执行结果，0-失败，1-成功 */
    VOS_UINT8                         aucReserved[3];  /* 保留 */
} GAS_OM_EVENT_GSM_TO_WCDMA_RESELECT_END_ST;


/*****************************************************************************
 结 构 名  : GAS_OM_EVENT_GSM_TO_WCDMA_AFTER_CHAN_REL_SELECT_START_ST
 结构描述  : GAS向OM上报事件的描述

 修改历史      :
  1.日    期   : 2010年4月15日
    作    者   : h00129908
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT8                         aucReserve1[4];                         /* 4字节对齐，保留 */
} GAS_OM_EVENT_GSM_TO_WCDMA_AFTER_CHAN_REL_SELECT_START_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_EVENT_GSM_TO_WCDMA_AFTER_CHAN_REL_SELECT_END_ST
 结构描述  : GAS向OM上报事件的描述

 修改历史      :
  1.日    期   : 2010年4月15日
    作    者   : h00129908
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    GAS_OM_RESULT_ENUM_UINT8          enResult;        /* 执行结果，0-失败，1-成功 */
    VOS_UINT8                         aucReserved[3];  /* 保留 */
} GAS_OM_EVENT_GSM_TO_WCDMA_AFTER_CHAN_REL_SELECT_END_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_EVENT_GPRS_TBF_ABNORMAL_RELEASE_ST
 结构描述  : GAS向OM上报事件的描述

 修改历史      :
  1.日    期   : 2008年4月21日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_ENUM_UINT8    enReleaseCause;  /* TBF异常释放原因 */
    VOS_UINT8                                   aucReserved[3];  /* 保留 */
} GAS_OM_EVENT_GPRS_TBF_ABNORMAL_RELEASE_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_EVENT_RR_CONNECTION_ABNORMAL_ST
 结构描述  : GAS向OM上报事件的描述

 修改历史      :
  1.日    期   : 2009年4月21日
    作    者   : yaoqinbo
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    GAS_OM_RR_CONNECTION_ABNORMAL_TYPE_ENUM_UINT32     enAbnormalType;  /* RR连接异常类型 */
    GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_ENUM_UINT32    enAbnormlCause;  /* RR连接异常原因 */
} GAS_OM_EVENT_RR_CONNECTION_ABNORMAL_ST;


/*****************************************************************************
 结 构 名  : GAS_OM_EVENT_GPRS_INVALID_ASSIGN_ST
 结构描述  : GAS向OM上报事件的描述

 修改历史      :
  1.日    期   : 2008年4月21日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT32    ulInvalidCause;  /* 异常原因 */
} GAS_OM_EVENT_GPRS_INVALID_ASSIGN_ST;

/*****************************************************************************
 结 构 名  : OM_GAS_OTA_REQ_STRUCT
 结构描述  : OM向GAS发送的空口配置消息

 修改历史      :
  1.日    期   : 2008年4月21日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    DIAG_GAS_MSG_COMM_HEAD_ST           stMsgCommHead;

    VOS_UINT32                          ulOnOff;                                /* 0 - 停止上报 1 - 开始上报 */
}OM_GAS_OTA_REQ_STRUCT;

/*****************************************************************************
 结 构 名  : GAS_OM_OTA_CNF_STRUCT
 结构描述  : GAS向OM发送的空口配置确认消息

 修改历史      :
  1.日    期   : 2008年4月21日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    DIAG_GAS_MSG_COMM_HEAD_ST           stMsgCommHead;

    VOS_UINT32                          ulErrCode;
}GAS_OM_OTA_CNF_STRUCT;

/*****************************************************************************
 结 构 名  : OM_GAS_SPECIFIC_FREQ_CAMP_REQ_ST
 结构描述  : OM向GAS发送的指定频点请求消息

 修改历史      :
  1.日    期   : 2008年4月21日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    DIAG_GAS_MSG_COMM_HEAD_ST           stMsgCommHead;

    VOS_UINT16                          usFreqInfo;                             /* 频点信息 */
    VOS_UINT16                          usReserved;                             /* 保留 */
}OM_GAS_SPECIFIC_FREQ_CAMP_REQ_ST;

typedef GAS_OM_OTA_CNF_STRUCT  GAS_OM_SPECIFIC_FREQ_CAMP_CNF_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_TIMER_ACTION_ST
 Description    : GAS定时器事件上报
 Message origin :
 修改历史 :
  1.日    期    : 2008年11月05日
    作    者    :  刘德国 00126771
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTimerName;
    VOS_UINT32                          ulStartOrStop;
    VOS_UINT32                          ulLength;
}GAS_OM_EVENT_TIMER_ACTION_ST;

typedef struct
{
    VOS_UINT32    ulOutofServiceCause;  /* out_of_service原因 */
}GAS_OM_EVENT_OUT_OF_SERVICE_ST;


/*****************************************************************************
 Structure      : GAS_OM_EVENT_GSM_2G_NCELL_LIST_CHANGE_ST
 Description    : 2G 邻区改变通知结构体
 Message origin :
 修改历史 :
  1.日    期    : 2010年02月21日
    作    者    : 王畅 00146666
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    GAS_OM_NCELL_LIST_CHANGE_CAUSE_ENUM_UINT8 en2GNCellListChangeCause;  /*2G邻区改变原因*/
    VOS_UINT8                                 aucReserved[3];           /* 保留 */
}GAS_OM_EVENT_GSM_2G_NCELL_LIST_CHANGE_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_GSM_3G_NCELL_LIST_CHANGE_ST
 Description    : 2G 邻区改变通知结构体
 Message origin :
 修改历史 :
  1.日    期    : 2010年02月21日
    作    者    : 王畅 00146666
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    GAS_OM_NCELL_LIST_CHANGE_CAUSE_ENUM_UINT8 en3GNCellListChangeCause;     /*3G邻区改变原因*/
    VOS_UINT8                                 aucReserved[3];               /* 保留 */
}GAS_OM_EVENT_GSM_3G_NCELL_LIST_CHANGE_ST;


/*****************************************************************************
 枚举名    : OM_GAS_FREQ_MEAS_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : GAS测量频点类型
*****************************************************************************/
enum OM_GAS_FREQ_MEAS_TYPE_ENUM
{
    GAS_OM_FREQ_MEAS_TYPE_STORE_LIST   = 0,
    GAS_OM_FREQ_MEAS_TYPE_FULL_LIST    = 1,
    GAS_OM_FREQ_MEAS_TYPE_BUTT
};
typedef VOS_UINT8 OM_GAS_FREQ_MEAS_TYPE_ENUM_UINT8;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_X_BG_SEARCH_G_FREQ_MEAS_START_STs
 Description    :
 Message origin :
 修改历史 :
  1.日    期    : 2010年12月21日
    作    者    : 王畅 00146666
    修改内容    : 新增结构体
  2.日    期    : 2014年05月16日
    作    者    : q00261930
    修改内容    : 改名为GAS_OM_EVENT_X_BG_SEARCH_G_FREQ_MEAS_START_ST

*****************************************************************************/
typedef struct
{
    OM_GAS_FREQ_MEAS_TYPE_ENUM_UINT8       enFreqMeasType;       /* 频点测量类型(历史频点搜，全频段搜)*/
    VOS_UINT8                              aucReserved;          /* 保留 */
    VOS_UINT16                             usFreqNum;            /* 频点测量的总个数 */
}GAS_OM_EVENT_X_BG_SEARCH_G_FREQ_MEAS_START_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_X_BG_SEARCH_G_FREQ_MEAS_END_ST
 Description    :
 Message origin :
 修改历史 :
  1.日    期    : 2010年12月21日
    作    者    : 王畅 00146666
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                             usQualFreqNum;           /* 符合条件的频点个数 */
    VOS_UINT8                              aucReserved[2];          /* 保留 */
}GAS_OM_EVENT_X_BG_SEARCH_G_FREQ_MEAS_END_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_INIT_WEAK_SIGNAL_ST
 Description    : 开机初始化后弱信号事件发生时上报OM事件的结构
 Message origin :
 修改历史 :
  1.日    期    : 2011年02月25日
    作    者    : L00167020
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    GAS_MNTN_INIT_WEAK_SIGNAL_EVT_STRU         stInitWeakSignal;   /*开机后最多上报3次弱信号事件及相关信息*/
    
}GAS_OM_EVENT_INIT_WEAK_SIGNAL_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_PERIOD_WEAK_SIGNAL_ST
 Description    : 当前分钟发生的弱信号信息上报OM事件的结构
 Message origin :
 修改历史 :
  1.日    期    : 2011年02月25日
    作    者    : L00167020
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    GAS_MNTN_WEAK_SIGNAL_INFO_STRU      stCurWeakSignalInfo;    /*每分钟发生弱信号及相关信息*/
    
}GAS_OM_EVENT_PERIOD_WEAK_SIGNAL_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_WEAK_SIGNAL_LIST_ST
 Description    : 每30分钟周期性上报弱信号时上报OM的事件结构
 Message origin :
 修改历史 :
  1.日    期    : 2011年02月25日
    作    者    : L00167020
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    GAS_MNTN_PERIOD_WEAK_SIGNAL_LIST_EVT_STRU    stPeriodWeakSignalList;  /*30分钟每分钟发生的弱信号及相关信息*/

}GAS_OM_EVENT_WEAK_SIGNAL_LIST_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_RCV_SI_ON_PCH_STRU
 Description    : 在PCH信道上收到系统消息
 Message origin :
 修改历史 :
  1.日    期    : 2011年02月25日
    作    者    : L00167020
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16 usSiType;        /* 系统消息类型 */
    VOS_UINT16 usChanType;      /* 逻辑信道类型 */
}GAS_OM_EVENT_RCV_SI_ON_PCH_STRU;

/*****************************************************************************
 结 构 名  : OM_GAS_LTE_NCELL_MEAS_REQ_ST
 结构描述  : OM 发出的 LTE邻小区测量信息查询请求

 修改历史      :
  1.日    期   : 2011年03月21日
    作    者   : g00149376
    修改内容   : 新生成结构
*****************************************************************************/
typedef OM_GAS_INFO_REQ_ST  OM_GAS_LTE_NCELL_MEAS_REQ_ST;

/*****************************************************************************
 结 构 名  : OM_GAS_LTE_NCELL_MEAS_CNF_ST
 结构描述  : GAS对LTE邻小区测量查询请求的确认

 修改历史      :
  1.日    期   : 2011年03月21日
    作    者   : g00149376
    修改内容   : 新生成结构
*****************************************************************************/
typedef GAS_OM_INFO_CNF_ST  GAS_OM_LTE_NCELL_MEAS_CNF_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_LTE_SETTINGS_ST
 结构描述  : GAS上报LTE邻区的配置信息

 修改历史      :
  1.日    期   : 2011年03月21日
    作    者   : g00149376
    修改内容   : 新生成函数,for V7R1
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucLteQsearchP;      /* QSearchP */
    VOS_UINT8                               ucLteQsearchC;      /* QSearchC */
    VOS_UINT8                               ucThreshPriSearch;  /* 优先级门限 */
    VOS_UINT8                               aucRsv[1];          /* 保留位 */
}GAS_OM_LTE_SETTINGS_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_LTE_NCELL_INFO_ST
 结构描述  : GAS向OM上报LTE邻区的信息

 修改历史      :
  1.日    期   : 2011年03月21日
    作    者   : g00149376
    修改内容   : 新生成函数,for V7R1
*****************************************************************************/
typedef struct
{
    VOS_UINT16                     usArfcn;            /* 频点 */
    VOS_UINT16                     usArfcnPri;         /* 频点优先级 */
    VOS_UINT16                     usCellId;           /* 小区id */
    VOS_INT16                      sRsrp;              /* RSRP测量值,取值范围[-141*8,-44*8]， 单位:dBm，精度 1/8  */
    VOS_INT16                      sRsrq;              /* RSRQ测量值 ,取值范围[-40*4，-6*4]， 单位:dB， 精度 1/8  */
    VOS_INT16                      sRssi;              /* RSSI测量值 ,取值范围[-110*8,-20*8], 单位:dBm，精度 1/8  */
} GAS_OM_LTE_NCELL_INFO_ST;


/*****************************************************************************
 结 构 名  : GAS_OM_LTE_NCELL_MEAS_IND_ST
 结构描述  : GAS上报LTE邻小区测量信息

 修改历史      :
 1.日    期   : 2011年03月21日
    作    者   : g00149376
    修改内容   : 新生成函数,for V7R1
*****************************************************************************/
typedef struct
{
    OM_GAS_REPORT_TYPE_ENUM_UINT16      enReportType;
    VOS_UINT16                          usLteNcellNum;
    GAS_OM_LTE_SETTINGS_ST              stLteSettings;
    GAS_OM_LTE_NCELL_INFO_ST            astLteNcellInfo[GAS_OM_MAX_LTE_NCELL_NUM];
} GAS_OM_LTE_NCELL_MEAS_IND_ST;

/*****************************************************************************
 结 构 名  : GAS_MSP_LTE_NCELL_MEAS_IND_ST
 结构描述  : GAS上报LTE邻小区测量信息

 修改历史      :
 1.日    期    : 2015年09月18日
    作    者   : h00166210
    修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPrimId;
    VOS_UINT16                          usReserved;

    OM_GAS_REPORT_TYPE_ENUM_UINT16      enReportType;
    VOS_UINT16                          usLteNcellNum;
    GAS_OM_LTE_SETTINGS_ST              stLteSettings;
    GAS_OM_LTE_NCELL_INFO_ST            astLteNcellInfo[GAS_OM_MAX_LTE_NCELL_NUM];
} GAS_MSP_LTE_NCELL_MEAS_IND_ST;

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 Structure      : GAS_OM_EVENT_GSM_TO_LTE_RESEL_START_ST
 Description    : GAS 向 OM 上报 G 到 L 重选开始, 携带目标小区信息
 Message origin :
 修改历史 :
  1.日    期    : 2011年03月10日
    作    者    : p00166345
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    /* 目标小区 频点 */
    VOS_UINT16  usEArfcn;

    /* 目标小区 小区 ID */    
    VOS_UINT16  usCellId;

    /* 目标小区的 测量结果 */
    VOS_INT16   sRsrp;
    VOS_INT16   sRsrq;
    VOS_INT16   sRssi;
    VOS_UINT8   aucRsv[2];
}GAS_OM_EVENT_GSM_TO_LTE_RESEL_START_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_GSM_TO_LTE_RESEL_END_ST
 Description    : GAS 向 OM 上报 G 到 L 重选结束
 Message origin :
 修改历史 :
  1.日    期    : 2011年03月10日
    作    者    : p00166345
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    LRRC_GURRC_CELL_RESEL_RESULT_ENUM_UINT32   ulGLReselRlt;
}GAS_OM_EVENT_GSM_TO_LTE_RESEL_END_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_LTE_TO_GSM_RESEL_START_ST
 Description    : GAS 向 OM 上报 L 到 G 重选开始
 Message origin :
 修改历史 :
  1.日    期    : 2011年03月10日
    作    者    : p00166345
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;
    VOS_UINT8                           ucNcc;                                  /* (3bit) PLMN色码  */
    VOS_UINT8                           ucBcc;                                  /* (3bit) 基站色码  */
}GAS_OM_EVENT_LTE_TO_GSM_RESEL_START_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_LTE_TO_GSM_RESEL_END_ST
 Description    : GAS 向 OM 上报 L 到 G 重选结束
 Message origin :
 修改历史 :
  1.日    期    : 2011年03月10日
    作    者    : p00166345
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    LRRC_GURRC_CELL_RESEL_RESULT_ENUM_UINT32   ulLGReselRlt;
}GAS_OM_EVENT_LTE_TO_GSM_RESEL_END_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_GSM_TO_LTE_CCO_START_ST
 Description    : GAS 向 OM 上报 G 到 L CCO 开始
 Message origin :
 修改历史 :
  1.日    期    : 2011年03月10日
    作    者    : p00166345
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16  usEArfcn;
    VOS_UINT16  usCellId;
}GAS_OM_EVENT_GSM_TO_LTE_CCO_START_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_GSM_TO_LTE_CCO_END_ST
 Description    : GAS 向 OM 上报 G 到 L CCO 结束
 Message origin :
 修改历史 :
  1.日    期    : 2011年03月10日
    作    者    : p00166345
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    LRRC_GURRC_CELL_RESEL_RESULT_ENUM_UINT32   ulGLCCORlt;
}GAS_OM_EVENT_GSM_TO_LTE_CCO_END_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_LTE_TO_GSM_CCO_START_ST
 Description    : GAS 向 OM 上报 L 到 G CCO 开始
 Message origin :
 修改历史 :
  1.日    期    : 2011年03月10日
    作    者    : p00166345
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;
    VOS_UINT8                           ucNcc;                                  /* (3bit) PLMN色码  */
    VOS_UINT8                           ucBcc;                                  /* (3bit) 基站色码  */
}GAS_OM_EVENT_LTE_TO_GSM_CCO_START_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_LTE_TO_GSM_CCO_END_ST
 Description    : GAS 向 OM 上报 L 到 G CCO 结束
 Message origin :
 修改历史 :
  1.日    期    : 2011年03月10日
    作    者    : p00166345
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    LRRC_GURRC_CELL_RESEL_RESULT_ENUM_UINT32   ulLGCCORlt;
}GAS_OM_EVENT_LTE_TO_GSM_CCO_END_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_GSM_TO_LTE_REDIR_START_ST
 Description    : GAS向 OM上报 LRRC重定向请求的 GSM小区
 Message origin :
 修改历史 :
  1.日    期    : 2011年07月15日
    作    者    : s00184266
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;
    LRRC_GRR_BANDINDICATOR_ENUM_UINT16  enBandInd;
    VOS_UINT16                          usSysInfoPres;
    VOS_UINT8                           aucData[2];
}GAS_OM_REDIRECTED_INFO_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_GSM_TO_LTE_REDIR_START_ST
 Description    : GAS 向 OM 上报 G 到 L 重定向 开始
 Message origin :
 修改历史 :
  1.日    期    : 2011年07月15日
    作    者    : s00184266
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                   	ulRedirInfoNum;
    GRR_LRRC_REDIRECTED_INFO_STRU   astGrrRedirInfo[LRRC_GURRC_LTE_ARFCN_MAX_NUM];
}GAS_OM_EVENT_GSM_TO_LTE_REDIR_START_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_GSM_TO_LTE_REDIR_END_ST
 Description    : GAS 向 OM 上报 G 到 L 重定向 结束
 Message origin :
 修改历史 :
  1.日    期    : 2011年07月15日
    作    者    : s00184266
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    LRRC_GURRC_REDIRECTED_RESULT_ENUM_UINT32  enLrrcGrrRedirRlt;
}GAS_OM_EVENT_GSM_TO_LTE_REDIR_END_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_LTE_TO_GSM_REDIR_START_ST
 Description    : GAS 向 OM 上报 L 到 G 重定向 开始
 Message origin :
 修改历史 :
  1.日    期    : 2011年07月15日
    作    者    : s00184266
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM_UINT8    enCellCampedType;
    VOS_UINT8                                   aucData[1];

    VOS_UINT16                                  ulGsmCellCount;
    GAS_OM_REDIRECTED_INFO_ST                   astGsmCellInfo[LRRC_GURRC_GERAN_ARFCN_MAX_NUM];
}GAS_OM_EVENT_LTE_TO_GSM_REDIR_START_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_LTE_TO_GSM_REDIR_END_ST
 Description    : GAS 向 OM 上报 L 到 G 重定向 结束
 Message origin :
 修改历史 :
  1.日    期    : 2011年07月15日
    作    者    : s00184266
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    GAS_OM_REDIR_L2G_RESULT_ENUM_UINT8  enGrrLrrcRedirRlt;
    VOS_UINT8                           aucData[3];
}GAS_OM_EVENT_LTE_TO_GSM_REDIR_END_ST;

/*****************************************************************************
 结构名    : GAS_OM_EVENT_LTE_TO_GSM_ANR_END_ST
 结构说明  : 给OM上报L到G ANR的结果
 修改历史 :
 1.日    期    : 2012年04月19日
   作    者    : w00176595
   修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    GAS_OM_ANR_L2G_RESULT_ENUM_UINT8    enGrrLrrcAnrRlt;
    VOS_UINT8                           aucData[3];
}GAS_OM_EVENT_LTE_TO_GSM_ANR_END_ST;
#endif /* #if (FEATURE_ON == FEATURE_LTE) */

/*****************************************************************************
 消息名称  : GAS_OM_EVENT_BG_PLMN_LIST_SEARCH_END_ST
 功能描述  : GAS 向 OM 上报 列表搜结果
 修改历史  : 
  1.日    期   : 2011年06月27日
    作    者   : s00184266
    修改内容   : 新生成结构
    
*****************************************************************************/
typedef struct
{
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_ENUM_UINT8            enBgPlmnListSearchRlt;
    VOS_UINT8                                               aucData[3];
} GAS_OM_EVENT_BG_PLMN_LIST_SEARCH_END_ST;

/*****************************************************************************
 消息名称  : GAS_OM_EVENT_BG_PLMN_SEARCH_ST
 功能描述  : GAS向OM报背景搜LTE过程中的结果
 修改历史  : 
  1.日    期   : 20112年05月07日
    作    者   : w00146666
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    GAS_OM_BG_PLMN_SEARCH_LTE_ABNORMAL_EVENT_ENUM_UINT8           enBgPlmnSearchLEvent;
    VOS_UINT8                                                     aucData[3];
} GAS_OM_ABNORMAL_EVENT_BG_PLMN_SEARCH_LTE_ST;

#if ( FEATURE_ON == FEATURE_UE_MODE_TDS )
/*****************************************************************************
 消息名称  : GAS_OM_EVENT_GSM_TO_UTRAN_TDD_RESEL_START_ST
 功能描述  : GAS 向 OM 上报 GSM 到 UTRAN TDD 重选开始, 携带目标小区信息
 修改历史  :
  1.日    期    : 2011年11月20日
    作    者    : W00176595
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    /* 目标小区 频点 */
    VOS_UINT16  usTddArfcn;

    /* 目标小区 小区 ID */
    VOS_UINT16  usCellParaId;

    /* 目标小区的 测量结果 */
    VOS_INT16   sRsrp;

    /* 小区重选类型 :
        0:GAS_GCOMC_CELL_RESEL_TYPE_NON
        1:GAS_GCOMC_CELL_RESEL_TYPE_ACTIVE
        2:GAS_GCOMC_CELL_RESEL_TYPE_PASSIVE
                                   */
    VOS_UINT8   ucCellReselType;

    VOS_UINT8   aucRsv;   /* 填充字段  */
}GAS_OM_EVENT_GSM_TO_UTRAN_TDD_RESEL_START_ST;

/*****************************************************************************
消息名称  : GAS_OM_EVENT_GSM_TO_UTRAN_TDD_RESEL_END_ST
功能描述  : GAS 向 OM 上报 G 到 UTRAN TDD 重选结束
修改历史  :
  1.日    期    : 2011年11月20日
    作    者    : w00176595
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    TRRC_GRR_CELL_RESEL_CCO_RESULT_ENUM_UINT32   ulGTReselRlt;
}GAS_OM_EVENT_GSM_TO_UTRAN_TDD_RESEL_END_ST;

/*****************************************************************************
消息名称  : GAS_OM_EVENT_UTRAN_TDD_TO_GSM_RESEL_START_ST
功能描述  : GAS 向 OM 上报 UTRAN TDD 到 G 重选开始
修改历史  :
  1.日    期    : 2011年11月20日
    作    者    : w00176595
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;
    VOS_UINT8                           ucNcc;                                  /* (3bit) PLMN色码  */
    VOS_UINT8                           ucBcc;                                  /* (3bit) 基站色码  */
}GAS_OM_EVENT_UTRAN_TDD_TO_GSM_RESEL_START_ST;

/*****************************************************************************
 消息名称  : GAS_OM_EVENT_UTRAN_TDD_TO_GSM_RESEL_END_ST
 功能描述  : GAS 向 OM 上报 UTRAN TDD 到 G 重选结束
 修改历史  :
  1.日    期    : 2011年11月20日
    作    者    : w00176595
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    TRRC_GRR_CELL_RESEL_CCO_RESULT_ENUM_UINT32   ulTGReselRlt;
}GAS_OM_EVENT_UTRAN_TDD_TO_GSM_RESEL_END_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_GSM_TO_UTRAN_TDD_CCO_START_ST
 Description    : GAS 向 OM 上报 G 到 UTRAN_TDD CCO 开始
 Message origin :
 修改历史 :
  1.日    期    : 2012年02月21日
    作    者    : w00176595
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16  usTddArfcn;      /* 目标小区 频点 */
    VOS_UINT16  usCellParaId;    /* 目标小区 小区 ID */
}GAS_OM_EVENT_GSM_TO_UTRAN_TDD_CCO_START_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_GSM_TO_UTRAN_TDD_CCO_END_ST
 Description    : GAS 向 OM 上报 G 到 UTRAN_TDD CCO 结束
 Message origin :
 修改历史 :
  1.日    期    : 2012年02月21日
    作    者    : w00176595
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    TRRC_GRR_CELL_RESEL_CCO_RESULT_ENUM_UINT32   ulGTCCORlt;
}GAS_OM_EVENT_GSM_TO_UTRAN_TDD_CCO_END_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_UTRAN_TDD_TO_GSM_CCO_START_ST
 Description    : GAS 向 OM 上报 UTRAN_TDD 到 G CCO 开始
 Message origin :
 修改历史 :
  1.日    期    : 2012年02月21日
    作    者    : w00176595
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;
    VOS_UINT8                           ucNcc;                                  /* (3bit) PLMN色码  */
    VOS_UINT8                           ucBcc;                                  /* (3bit) 基站色码  */
}GAS_OM_EVENT_UTRAN_TDD_TO_GSM_CCO_START_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_UTRAN_TDD_TO_GSM_CCO_END_ST
 Description    : GAS 向 OM 上报 UTRAN_TDD 到 G CCO 结束
 Message origin :
 修改历史 :
  1.日    期    : 2012年02月21日
    作    者    : w00176595
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    TRRC_GRR_CELL_RESEL_CCO_RESULT_ENUM_UINT32   ulTGCCORlt;
}GAS_OM_EVENT_UTRAN_TDD_TO_GSM_CCO_END_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_UTRAN_TDD_TO_GSM_HANDOVER_END_ST
 Description    : GAS 向 OM 上报 UTRAN_TDD 到 G HANDOVER 结束
 Message origin :
 修改历史 :
  1.日    期    : 2012年02月21日
    作    者    : L00167020
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    TRRC_GRR_HANDOVER_RESULT_ENUM_UINT32   ulT2gHoRlt;

}GAS_OM_EVENT_UTRAN_TDD_TO_GSM_HANDOVER_END_ST;

/*****************************************************************************
 消息名称   : GAS_OM_EVENT_GSM_TO_UTRAN_TDD_REDIR_START_ST
 功能描述   : GAS 向 OM 上报 G 到 UTRAN TDD 重定向 开始

 修改历史 :
  1.日    期    : 2013年05月16日
    作    者    : y00142674
    修改内容    : 新增结构体，GUTL 准FR
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulUtranTddCellCnt;
    RRC_CELL_SEL_UTRAN_TDD_CELL_STRU        astUtranTddCell[RR_TRRC_MAX_UTRAN_TDD_CELL_NUM];
}GAS_OM_EVENT_GSM_TO_UTRAN_TDD_REDIR_START_ST;

/*****************************************************************************
 消息名称   : GAS_OM_EVENT_GSM_TO_UTRAN_TDD_REDIR_END_ST
 功能描述   : GAS 向 OM 上报 G 到 UTRAN TDD 重定向 结束

 修改历史 :
  1.日    期    : 2013年05月16日
    作    者    : y00142674
    修改内容    : 新增结构体，GUTL 准FR
*****************************************************************************/
typedef struct
{
    TRRC_GRR_REDIRECTED_RESULT_ENUM_UINT32  enTrrcGrrRedirRlt;
}GAS_OM_EVENT_GSM_TO_UTRAN_TDD_REDIR_END_ST;

#endif

/*****************************************************************************
 消息名称  : GAS_OM_EVENT_GSM_TO_UTRAN_FDD_RESEL_START_ST
 功能描述  : GAS 向 OM 上报 GSM 到 UTRAN FDD 重选开始, 携带目标小区信息
 修改历史  :
  1.日    期    : 2012年02月25日
    作    者    : j00178524
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    /* 目标小区 频点 */
    VOS_UINT16  usFddArfcn;

    /* 目标小区 小区 扰码 */
    VOS_UINT16  usScramblingCode;

    /* 目标小区的 测量结果 */
    VOS_INT16   sRsrp;
    VOS_INT16   sEcno;

    /* 小区重选类型 :
        0:GAS_GCOMC_CELL_RESEL_TYPE_NON
        1:GAS_GCOMC_CELL_RESEL_TYPE_ACTIVE
        2:GAS_GCOMC_CELL_RESEL_TYPE_PASSIVE
                                   */
    VOS_UINT8   ucCellReselType;

    VOS_UINT8   aucRsv[3];   /* 填充字段  */
}GAS_OM_EVENT_GSM_TO_UTRAN_FDD_RESEL_START_ST;

/*****************************************************************************
 消息名称  : GAS_OM_EVENT_GSM_TO_UTRAN_FDD_RESEL_END_ST
 功能描述  : GAS 向 OM 上报 GSM 到 UTRAN FDD 重选开始, 携带目标小区信息
 修改历史  :
  1.日    期    : 2012年02月25日
    作    者    : j00178524
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    /* 重选结果 */
    VOS_UINT32              ulResult;
}GAS_OM_EVENT_GSM_TO_UTRAN_FDD_RESEL_END_ST;

/*****************************************************************************
 消息名称  : GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_START_ST
 功能描述  : GAS 向 OM 上报 GSM 到 UTRAN FDD CCO开始, 携带目标小区信息
 修改历史  :
  1.日    期    : 2012年02月25日
    作    者    : j00178524
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    /* 目标小区 频点 */
    VOS_UINT16  usFddArfcn;

    /* 目标小区 小区 扰码 */
    VOS_UINT16  usScramblingCode;

}GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_START_ST;

/*****************************************************************************
 枚举名    : GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_RESULT_ENUM
 枚举说明  : 向 OM上报 GAS CCO 到 UTRAN FDD 小区的结果
 修改历史  :
 1.日    期    : 2012年03月06日
   作    者    : j00178524
   修改内容    : 新建枚举类型, for V7R1 GTL PhaseII
*****************************************************************************/
enum GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_RESULT_ENUM
{
    GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_RESULT_SUCC                               = 0x1,        /* 成功 */
    GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_RESULT_FAIL_TIMER_EXPIRE                  = 0x2,        /* CCO 流程超时 */
    GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_RESULT_FAIL_CONNECTION_REJECT             = 0x3,        /* 目标小区接入被拒 */
    GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_RESULT_FAIL_OTHER                         = 0x4,        /* 其它失败原因 */

    GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_RESULT_BUTT
};

typedef VOS_UINT32 GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_RESULT_ENUM32;

/**********************************************************************************************************************************************************
 消息名称  : GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_END_ST
 功能描述  : GAS 向 OM 上报 GSM 到 UTRAN FDD CCO开始, 携带目标小区信息
 修改历史  :
  1.日    期    : 2012年02月25日
    作    者    : j00178524
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    /* 重选结果 */
    VOS_UINT32              ulResult;
}GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_END_ST;

#define GAS_OM_INTER_RESEL_CELL_EVALUATE_INFO_LST_SIZE          (32)

/*****************************************************************************
 消息名称  : GAS_OM_INTER_RESEL_CELL_EVALUATE_INFO_STRU
 功能描述  : GAS 向 OM 上报的系统评估结果
 修改历史  :
  1.日    期    : 2016-01-06
    作    者    : p00166345
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;
    VOS_UINT16                                              usCellId;

    VOS_INT16                                               sThreshXXXhigh;
    VOS_INT16                                               sThreshXXXLow;

    VOS_INT16                                               sSValue;
    VOS_UINT8                                               ucPrio;
    VOS_UINT8                                               ucEvaluateRlt;
}GAS_OM_INTER_RESEL_CELL_EVALUATE_INFO_STRU;

/*****************************************************************************
 消息名称  : GAS_OM_INTER_RESEL_CELL_EVALUATE_INFO_STRU
 功能描述  : GAS 向 OM 上报的系统评估结果
 修改历史  :
  1.日    期    : 2016-01-06
    作    者    : p00166345
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   sQoffset;
    VOS_INT16                                   sFddQmin;
    VOS_INT16                                   sFddQminOffset;
    VOS_INT16                                   sFddRscpmin;
}GAS_OM_INTER_RESEL_RANKING_PARA_STRU;

typedef struct
{
    VOS_UINT8                                   ucScellPrio;
    VOS_UINT8                                   ucGsmLowFlg;
    VOS_UINT16                                  usThreshGsmLow;

    VOS_INT16                                   sSCellC1;
    VOS_UINT8                                   aucRsv[1];
    VOS_UINT8                                   ucInterCellCnt;

    GAS_OM_INTER_RESEL_CELL_EVALUATE_INFO_STRU  astInterCellLst[GAS_OM_INTER_RESEL_CELL_EVALUATE_INFO_LST_SIZE];

    GAS_OM_INTER_RESEL_RANKING_PARA_STRU        stRankingBasedParas;
}GAS_OM_INTER_RESEL_EVALUATE_RLT_STRU;

/*****************************************************************************
 消息名称  : GAS_OM_EVENT_INTER_RESEL_EVALUATE_START_ST
 功能描述  : GAS 向 OM 上报异系统重选评估开始的事件
 修改历史  :
  1.日    期    : 2011年11月20日
    作    者    : w00176595
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT8          ucReselType;                           /*  主动重选或被动重选 */
    VOS_UINT8          ucBaseOnPrior;                         /*  是否基于优先级重选 */
    VOS_UINT8          aucResv[2];                            /* 保留位 */
}GAS_OM_EVENT_INTER_RESEL_EVALUATE_START_ST;

/*****************************************************************************
 消息名称  : GAS_OM_EVENT_INTER_RESEL_EVALUATE_TIMER_START_ST
 功能描述  : GAS 向 OM 上报异系统重选评估定时器启动的事件
 修改历史  :
  1.日    期    : 2011年11月20日
    作    者    : w00176595
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulTimerId;                            /*  定时器的ID */
    VOS_UINT32          ulTimerLen;                           /*  定时器的长度 */
}GAS_OM_EVENT_INTER_RESEL_EVALUATE_TIMER_START_ST;

/*****************************************************************************
 消息名称  : GAS_OM_EVENT_INTER_RESEL_EVALUATE_TIMER_EXPIRED_ST
 功能描述  : GAS 向 OM 上报异系统重选评估定时器超时的事件
 修改历史  :
  1.日    期    : 2011年11月20日
    作    者    : w00176595
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulTimerId;                            /*  定时器的ID */
}GAS_OM_EVENT_INTER_RESEL_EVALUATE_TIMER_EXPIRED_ST;


/*****************************************************************************
 Structure      : GAS_OM_EVENT_RESEL_EVALUATE_ADD_CELL_ST
 Description    : GAS 向 OM 上报 异系统重选评估新小区入围
 Message origin :
 修改历史 :
  1.日    期    : 2011年07月22日
    作    者    : j00178524
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCellType;                             /* 小区类型 */
    VOS_UINT8                           aucResv[3];                             /* 保留位 */
    VOS_UINT16                          usArfcn;                                /* 小区频点 */
    VOS_UINT16                          usCellData;                             /* 小区标识，扰码或小区ID */
}GAS_OM_EVENT_RESEL_EVALUATE_ADD_CELL_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_RESEL_EVALUATE_RMV_CELL_ST
 Description    : GAS 向 OM 上报 异系统重选评估小区从候选列表中删除
 Message origin :
 修改历史 :
  1.日    期    : 2011年07月22日
    作    者    : j00178524
    修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCause;                                /* 小区从候选列表中删除的原因 */
    VOS_UINT8                           ucCellType;                             /* 小区类型 */
    VOS_UINT8                           aucResv[2];                             /* 保留位 */
    VOS_UINT16                          usArfcn;                                /* 小区频点 */
    VOS_UINT16                          usCellData;                             /* 小区标识，扰码或小区ID */
}GAS_OM_EVENT_RESEL_EVALUATE_RMV_CELL_ST;


#define GAS_OM_PLMN_LIST_SEARCHED_FREQ_MAX_NUM           (60)
#define GAS_OM_FREQ_SEARCHING_USED_MAX_NUM               (150)
#define GAS_OM_MAX_PREFER_CELL_NUM                     (15)

/*****************************************************************************
 结构名    : GAS_OM_DEC_FAIL_ARFCN_ST
 结构说明  : 每次LIST搜网的时候, 记录解码未成功的小区
 修改历史 :
 1.日    期    : 2011年08月04日
   作    者    : w00176595
   修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16    usArfcn;
    VOS_INT16     sRxlev;
}GAS_OM_DEC_FAIL_ARFCN_ST;

/*****************************************************************************
 Structure      : GAS_OM_FREQUENCY_RXLEV_MEAS_RESULT_ST
 Description    : 频点测量时，接收到L1发来的测量结果，GCOM进行BCCH信息的接收和监听，
                  保存的有关验证小区是否为合适的小区信息，方便下次检验时使用。
 Message origin :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usArfcn;                /* 绝对射频号 */
    VOS_INT16                               sPower;                 /* 信号强度 */
} GAS_OM_FREQUENCY_RXLEV_MEAS_RESULT_ST;


/*****************************************************************************
 Structure      : GAS_OM_EVENT_PLMN_SEARCH_DEC_CELL_STRU
 Description    : 搜网过程中使用的黑名单数据
 Message origin :
 修改历史 :
 1.日    期    : 2011年08月04日
   作    者    : w00176595
   修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                usCount;
    VOS_UINT8                 ucRsv[2];
    GAS_OM_DEC_FAIL_ARFCN_ST  astDecFailArfcn[GAS_OM_PLMN_LIST_SEARCHED_FREQ_MAX_NUM];
}GAS_OM_EVENT_PLMN_SEARCH_DEC_CELL_STRU;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_PLMN_SEARCH_RXLEV_STRU
 Description    : 搜网过程中电平过滤后剩余的排序后的电平数据
 Message origin :
 修改历史 :
 1.日    期    : 2011年08月04日
   作    者    : w00176595
   修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                usCount;
    VOS_UINT8                 ucRsv[2];
    GAS_OM_FREQUENCY_RXLEV_MEAS_RESULT_ST  astArfcnRxlev[GAS_OM_FREQ_SEARCHING_USED_MAX_NUM];
}GAS_OM_EVENT_PLMN_SEARCH_RXLEV_STRU;

typedef struct
{
    VOS_UINT32    ulMcc;
    VOS_UINT32    ulMnc;
    VOS_UINT16    usArfcnCount;
    VOS_UINT16    usRsv;
    VOS_UINT16    ausArfcn[GAS_OM_PLMN_LIST_SEARCHED_FREQ_MAX_NUM];
}GAS_OM_PREFER_PLMN_CELL_ST;

/*****************************************************************************
 结构名       : GAS_OM_PREFER_CELL_ST
 结构说明  : 每次LIST搜网结束后, 保存的优选小区信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                     usPreferCellCount;
    VOS_UINT16                     usRsv;
    GAS_OM_PREFER_PLMN_CELL_ST     astPreferCell[GAS_OM_MAX_PREFER_CELL_NUM];
} GAS_OM_PREFER_CELL_ST;


/*****************************************************************************
 结构名    : GAS_OM_EVENT_WCDMA_TO_GSM_RESEL_CCO_END_ST
 结构说明  : 给OM上报W到G Resel/CCO的结果
 修改历史 :
 1.日    期    : 2012年04月19日
   作    者    : w00176595
   修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    GAS_OM_RESEL_CCO_W2G_RESULT_ENUM_UINT8    enReselCCORst;
    VOS_UINT8                                 aucData[3];
}GAS_OM_EVENT_WCDMA_TO_GSM_RESEL_CCO_END_ST;

/*****************************************************************************
 结构名    : GAS_OM_LOG_RECORD_STRU
 协议表格  :
 ASN.1描述 : GAS打印信息上报
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTimeStamp; /* 上报消息的时间戳 */
    VOS_UINT32                          enLevel;     /* 上报消息的打印级别 */
    PS_FILE_ID_DEFINE_ENUM_UINT32       enFile;      /* 上报消息的文件名 */
    VOS_UINT32                          ulLine;      /* 上报消息的行号 */
    VOS_INT32                           alPara[4];
}GAS_OM_LOG_RECORD_STRU;

/*****************************************************************************
 结构名    : GAS_OM_LOG_INFO_STRU
 协议表格  :
 ASN.1描述 : GAS打印信息上报
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSavedMsgCnt;
    GAS_OM_LOG_RECORD_STRU              astData[GAS_OM_PRINT_MSG_MAX_NUM];
}GAS_OM_LOG_INFO_STRU;

/*****************************************************************************
 结构名    : Gas_WRITE_PREFER_CELL_SWITCH_TO_NV_MSG
 结构说明  : 
 修改历史  : 
 1.日    期    : 2012年09月26日
   作    者    : z00206003
   修改内容    : 新建结构体 DTS2012092601774
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSwitch;
}Gas_WRITE_PREFER_CELL_SWITCH_TO_NV_MSG;

/*****************************************************************************
 结构名    : Gas_WRITE_PREFER_PLMN_NUM_TO_NV_MSG
 结构说明  : 
 修改历史  : 
 1.日    期    : 2012年09月26日
   作    者    : z00206003
   修改内容    : 新建结构体 DTS2012092601774
*****************************************************************************/
typedef struct
{
   VOS_UINT16                           usPlmnCnt;          
}Gas_WRITE_PREFER_PLMN_NUM_TO_NV_MSG;

/*****************************************************************************
 结构名    : Gas_PREFER_CELL_PLMN_LIST_STRU
 结构说明  : 优选小区NV项中plmn list结构
 修改历史  : 
 1.日    期    : 2012年09月26日
   作    者    : z00206003
   修改内容    : 新建结构体 DTS2012092601774
*****************************************************************************/
typedef struct 
{
    VOS_UINT32                          ulMcc;            
    VOS_UINT32                          ulMnc;        
    VOS_UINT16                          usArfCnt;         
    VOS_UINT16                          aArfs[60];          
}Gas_PREFER_CELL_PLMN_LIST_STRU;

/*****************************************************************************
 结构名    : Gas_WRITE_PREFER_CELL_TO_NV_MSG
 结构说明  : 
 修改历史  : 
 1.日    期    : 2012年09月26日
   作    者    : z00206003
   修改内容    : 新建结构体 DTS2012092601774
*****************************************************************************/
typedef struct
{
    Gas_PREFER_CELL_PLMN_LIST_STRU      aPlmnlist[5];     
}Gas_WRITE_PREFER_CELL_TO_NV_MSG;

/*****************************************************************************
 结构名    : GAS_OM_WRITE_NV_REQ_ST
 结构说明  : 
 修改历史  : 
 1.日    期    : 2012年09月26日
   作    者    : z00206003
   修改内容    : 新建结构体 DTS2012092601774
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                           /* _H2ASN_Skip */        
    VOS_UINT16                          usMsgID;             /* _H2ASN_Skip */
    VOS_UINT8                           aucRsv[2];           /* _H2ASN_Skip */
    VOS_UINT16                          usNvItem;
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucData[4];    
    /*********************************************************************
        _H2ASN_Array2String
    **********************************************************************/
}GAS_OM_WRITE_NV_REQ_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_UTRAN_CELL_BAR_INFO_STRU
 Description    : 发送UTRAN小区被惩罚的可维可测结构体信息
 Message origin :
 修改历史 :
 1.日    期    : 2015年07月24日
   作    者    : w00146666
   修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16 usArfcn;      /* UTRAN小区频点 */

    VOS_UINT16 usCellData;  /* FDD小区此参数表示扰码,TDD小区此参数表示CellParaID */

    VOS_UINT32 ulTimerLen;  /* 惩罚的时长, 单位ms */
}GAS_OM_EVENT_UTRAN_CELL_BAR_INFO_STRU;

/*****************************************************************************
 结构名    : GAS_OM_EVENT_IND_COMMON_ST
 结构说明  : 对应GAS_OM_EVENT_IND_ST中aucData[4]
 修改历史  : 
 1.日    期    : 2012年09月26日
   作    者    : z00206003
   修改内容    : 新建结构体 DTS2012092601774
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserved[4];      
}GAS_OM_EVENT_IND_COMMON_ST;

/*****************************************************************************
 结构名    : GAS_OM_AFC_INFO_IND_ST
 协议表格  :
 ASN.1描述 :
 结构说明  : AFC信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulAfcLockFlag;    /* AFC是否锁定标志    */
    VOS_UINT32                          ulWrittenTcxoCount;   /* 写afc的次数 */
    VOS_UINT16                          usAfcCurrVal;     /* 当前AFC值          */
    VOS_UINT16                          usInitFreqency;   /* 出厂时的AFC值 */
    VOS_UINT16                          usDynFreqency;    /* 上次NV中保存的AFC值         */
    VOS_UINT16                          usResereved;   
} GAS_OM_AFC_INFO_IND_ST;

#if ( FEATURE_ON == FEATURE_DSDS )
/*****************************************************************************
 结构名    : GAS_OM_APPLY_TASK_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DSDS GAS申请的资源任务结构
*****************************************************************************/
typedef struct
{
    RRM_PS_TASK_TYPE_ENUM_UINT16            enOmApplyTaskType;                  /* 申请的任务类型 */
    GAS_OM_TASK_STATUS_ENUM_UINT16          enOmApplyTaskStatus;                /* 申请的任务状态 */
}GAS_OM_APPLY_TASK_INFO_STRU;

/*****************************************************************************
 结构名    : GAS_OM_APPLY_TASK_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DSDS GAS申请的资源任务列表
*****************************************************************************/
typedef struct
{
    GAS_OM_APPLY_TASK_INFO_STRU              astOmApplyTaskInfo[GAS_OM_APPLY_TASK_LIST_MAX_NUM]; /* 申请的任务列表 */
}GAS_OM_APPLY_TASK_LIST_STRU;

/*****************************************************************************
 结构名    : GAS_OM_EVENT_RF_RESOURCE_TASK_LIST_STRU
 结构说明  : 上报整个资源任务列表
 修改历史  : 
 1.日    期    : 2014年02月25日
   作    者    : l67237
   修改内容    : 新建结构体 GAS DSDS
*****************************************************************************/
typedef struct
{
    GAS_OM_APPLY_TASK_LIST_STRU                stGasRfResTaskList;
}GAS_OM_EVENT_RF_RESOURCE_TASK_LIST_STRU;
#endif


/*****************************************************************************
 结构名    : GAS_OM_MSG_DATA
 结构说明  : 
 修改历史  : 
 1.日    期    : 2012年09月26日
   作    者    : z00206003
   修改内容    : 新建结构体 DTS2012092601774
*****************************************************************************/
typedef struct
{
    OM_GAS_MSG_ID_ENUM_UINT16           usMsgID;          /*_H2ASN_MsgChoice_Export OM_GAS_MSG_ID_ENUM_UINT16*/
    VOS_UINT16                          usReserved1;
    VOS_UINT8                           aucData[4];

    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          OM_GAS_MSG_ID_ENUM_UINT16
    ****************************************************************************/
}GAS_OM_MSG_DATA;
/*_H2ASN_Length UINT32*/

/*****************************************************************************
 结构名    : GasOmInterface_MSG
 结构说明  : GasOmInterface 根节点
 修改历史  : 
 1.日    期    : 2012年09月26日
   作    者    : z00206003
   修改内容    : 新建结构体 DTS2012092601774
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER             

    GAS_OM_MSG_DATA                     stMsgData;
}GasOmInterface_MSG;

/*****************************************************************************
 结构名    : GasEvent_MSG
 结构说明  : GASEvent 根节点
 修改历史  : 
 1.日    期    : 2012年09月26日
   作    者    : z00206003
   修改内容    : 新建结构体 DTS2012092601774
*****************************************************************************/
typedef struct   
{
    GAS_OM_EVENT_IND_ST                 stMsgData;
}GasEvent_MSG;

/*****************************************************************************
 结构名    : GAS_OM_EVENT_GCOM_CACHED_MSG_OVERFLOW_ST
 结构说明  : 消息队列溢出时上报给OM事件的结构
 修改历史  : 
 1.日    期    : 2012年09月29日
   作    者    : w00176595
   修改内容    : 新建结构体 DTS2012092900233
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMsgId;        /* 丢弃的消息的MSG ID */
    VOS_UINT8                           ucModule;       /* 消息队列溢出的GCOM模块  */
    VOS_UINT8                           ucRsv;          /* 保留位  */
}GAS_OM_EVENT_GCOM_CACHED_MSG_OVERFLOW_ST;

/*****************************************************************************
 结构名    : GAS_OM_EVENT_TRANSACTION_INFO_ST
 结构说明  : 查询NAS呼叫状态结果的打印
 修改历史  : 
 1.日    期    : 2012年11月16日
   作    者    : w00176595
   修改内容    : 新建结构体
*****************************************************************************/
typedef struct   
{
    VOS_UINT8                           ucCsTransactInfo;   /* CS的呼叫状态 */
    VOS_UINT8                           ucIsCallActive;     /* 业务状态 */
    VOS_UINT8                           aucRsv[2];          /* 保留位  */
}GAS_OM_EVENT_TRANSACTION_INFO_ST;

#if (FEATURE_ON == FEATURE_AGPS)
#define GAS_OM_RRLP_MESSAGE_MAX_LENGTH (1024) /* 每条APDU中RRLP消息最长为247，这里假定最大为4条 */
#define GAS_OM_RRLP_MESSAGE_HEAD       (4) /* 每条RRLP消息头长度 usMsgID + usLength */

/*****************************************************************************
 结构名    : GAS_OM_EVENT_RRLP_MSG_STRU
 结构说明  : RR与LCS之间交互的定位相关的消息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMsgID;                                /* REQ or RSP */
    VOS_UINT16                          usLength;                               /* RRLP长度 */
    VOS_UINT8                           aucData[GAS_OM_RRLP_MESSAGE_MAX_LENGTH];/* RRLP码流 */
}GAS_OM_EVENT_RRLP_MSG_STRU;

#endif


/* Added by yangsicong for probe接口新开发, 2012-10-30, begin */
/*****************************************************************************
 结构名    : GAS_OM_ROAD_TEST_INFO_REQ_STRU
 结构说明  : 路测需求 OM向GAS请求上报信息的原语结构
 修改历史  : 
 1.日    期    : 2012年11月07日
   作    者    : y49634
   修改内容    : 新建结构体 
*****************************************************************************/
typedef struct
{
    DIAG_GAS_MSG_COMM_HEAD_ST           stMsgCommHead;

    OM_GAS_REPORT_ACTION_ENUM_UINT16    enStartOrStop;
    OM_GAS_REPORT_TYPE_ENUM_UINT16        enReportType;
    VOS_UINT16                            usReportPeriod;   /* 单位: ms */
    GAS_ROAD_TEST_INFO_TYPE_ENUM_UINT16   enRtInfoType;
}GAS_OM_ROAD_TEST_INFO_REQ_STRU;

/*****************************************************************************
 结构名    : GAS_OM_ROAD_TEST_INFO_CNF_STRU
 结构说明  : 路测需求 GAS向OM回复的请求上报信息确认的原语结构
 修改历史  : 
 1.日    期    : 2012年11月07日
   作    者    : y49634
   修改内容    : 新建结构体 
*****************************************************************************/
typedef struct
{
    DIAG_GAS_MSG_COMM_HEAD_ST           stMsgCommHead;

    GAS_OM_RESULT_ENUM_UINT8            enResult;
    VOS_UINT8                           ausResv[3];
    OM_GAS_REPORT_ACTION_ENUM_UINT16    enStartOrStop;
    OM_GAS_REPORT_TYPE_ENUM_UINT16      enReportType;
}GAS_OM_ROAD_TEST_INFO_CNF_STRU;

/*****************************************************************************
 结构名    : GAS_OM_ROAD_TEST_MEAS_RESULT_STRU
 结构说明  : 路测需求 GAS向OM上报的服务小区测量结果信息结构
 修改历史  : 
 1.日    期    : 2012年11月07日
   作    者    : y49634
   修改内容    : 新建结构体 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      usArfcn;           /* 取值范围[0,1023],无效值=65535 */
    GAS_OM_GSM_BAND_ENUM_UINT16     enBand;            /* 取值范围[0, 3],无效值=65535 */
    VOS_UINT16                      usBsic;            /* 取值范围[0, 77],无效值=65535 */
    VOS_INT16                       sRxlevFull;        /* 取值范围[-110, 47],无效值=-32768 */
    VOS_INT16                       sRxlevSub;         /* 取值范围[-110, 47],无效值=-32768 */
    VOS_INT16                       sRxlevIdle;        /* 取值范围[-110, 47],无效值=-32768 */
    VOS_UINT16                      usRxQualFull;      /* 取值范围[0, 7],无效值=65535 */
    VOS_UINT16                      usRxQualSub;       /* 取值范围[0, 7],无效值=65535 */
    VOS_UINT16                      usRltMax;          /* 取值范围[0, 64],无效值=65535 */
    VOS_UINT16                      usRltAct;          /* 取值范围[0, 64],无效值=65535 */
    VOS_UINT16                      usErrBitNumFull;   /* 取值范围[0, 65535],无效值=0 */
    VOS_UINT16                      usBitNumFull;      /* 取值范围[0, 65535],无效值=0 */
    VOS_UINT16                      usErrBitNumSub;    /* 取值范围[0, 65535],无效值=0 */
    VOS_UINT16                      usBitNumSub;       /* 取值范围[0, 65535],无效值=0 */
    VOS_INT16                       sC1;               /* 取值范围[-127, 127],无效值=-32768 */
    VOS_INT16                       sC2;               /* 取值范围[-127, 127],无效值=-32768 */
    VOS_INT16                       sC31;              /* 取值范围[-127, 127],无效值=-32768 */
    VOS_INT16                       sC32;              /* 取值范围[-127, 127],无效值=-32768 */
    VOS_UINT16                      usMeanBep;          /* 取值范围[0, 31],无效值=65535 */
    VOS_UINT16                      usCvBep;            /* 取值范围[0, 7],无效值=-32768 */
}GAS_OM_ROAD_TEST_SCELL_MEAS_RESULT_STRU;

/*****************************************************************************
 结构名    : GAS_OM_ROAD_TEST_GNCELL_MEAS_RESULT_STRU
 结构说明  : 路测需求 GAS向OM上报的G邻小区测量结果信息结构
 修改历史  : 
 1.日    期    : 2012年11月07日
   作    者    : y49634
   修改内容    : 新建结构体 
*****************************************************************************/
typedef struct
{
    VOS_UINT16  usArfcn;                               /* 取值范围[0,1023],无效值=65535 */
    GAS_OM_GSM_BAND_ENUM_UINT16     enBand;            /* 取值范围[0, 3],无效值=65535 */
    VOS_UINT16  usBsic;                                /* 取值范围[0, 77],无效值=65535 */
    VOS_INT16   sRxlev;                                /* 取值范围[-110, 47],无效值=-32768 */
    VOS_INT16   sC1;                                   /* 取值范围[-127, 127],无效值=-32768 */
    VOS_INT16   sC2;                                   /* 取值范围[-127, 127],无效值=-32768 */
    VOS_INT16   sC31;                                  /* 取值范围[-127, 127],无效值=-32768 */
    VOS_INT16   sC32;                                  /* 取值范围[-127, 127],无效值=-32768 */
}GAS_OM_ROAD_TEST_GNCELL_MEAS_RESULT_STRU;

/*****************************************************************************
 结构名    : GAS_OM_ROAD_TEST_3G_FCELL_MEAS_RESULT_STRU
 结构说明  : 路测需求 GAS向OM上报的3G邻小区测量结果信息结构
 修改历史  : 
 1.日    期    : 2012年11月07日
   作    者    : y49634
   修改内容    : 新建结构体 
*****************************************************************************/
typedef struct
{
    VOS_UINT16 usUArfcn;            /* 取值范围[0, 16383],无效值=65535 */
    VOS_UINT16 usPsc;               /* 取值范围[0, 511],无效值=65535 */
    VOS_UINT16 usDiversity;         /* 取值范围[0, 1],无效值=65535 */
    VOS_INT16  sRscp;               /* 取值范围[-115 -25],无效值=-32768 */
    VOS_INT16  sEcn0;               /* 取值范围[-48, 2],无效值=-32768 , 1/2精度 */
    VOS_UINT8   aucResv[2];
}GAS_OM_ROAD_TEST_3G_FCELL_MEAS_RESULT_STRU;

/*****************************************************************************
 结构名    : GAS_OM_ROAD_TEST_MEAS_RESULT_STRU
 结构说明  : 路测需求 GAS向OM上报的测量结果信息结构
 修改历史  : 
 1.日    期    : 2012年11月07日
   作    者    : y49634
   修改内容    : 新建结构体 
*****************************************************************************/
typedef struct
{
    GAS_OM_ROAD_TEST_SCELL_MEAS_RESULT_STRU     stScellMeasResult;              
    VOS_UINT16                                  usGNCellNum;                    /* 取值范围[0, 6],无效值=65535 */
    VOS_UINT16                                  us3GFCellNum;                   /* 取值范围[0, 96],无效值=65535 */
    GAS_OM_ROAD_TEST_GNCELL_MEAS_RESULT_STRU    astNcellMeasResult[GAS_OM_2G_NCELL_CNT_MAX_NUM];          
    GAS_OM_ROAD_TEST_3G_FCELL_MEAS_RESULT_STRU  ast3GFCellMeasResult[GAS_OM_3G_NCELL_CNT_MAX_NUM];       
}GAS_OM_ROAD_TEST_MEAS_RESULT_STRU;

/*****************************************************************************
 结构名    : GAS_OM_ROAD_TEST_CELL_FULL_ID_STRU
 结构说明  : 路测需求 GAS向OM上报的服务小区标识结构
 修改历史  : 
 1.日    期    : 2012年11月07日
   作    者    : y49634
   修改内容    : 新建结构体 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;           	/* 取值范围[0, 1023],无效值=65535 */
    VOS_UINT16                          usBsic;            	/* 取值范围[0, 77],无效值=65535 */
    GAS_OM_GSM_BAND_ENUM_UINT16         enBand;            	/* 取值范围[0, 3],无效值=65535 */
    VOS_UINT16                          usCi;              	/* 取值范围[0, 65535],无效值=65535 */
    VOS_UINT32                          ulMcc;             	/* 取值范围[000, 999],无效值=65535 */
    VOS_UINT32                          ulMnc;             	/* 取值范围[000, 999],无效值=65535 */
    VOS_UINT16                          usLac;             	/* 取值范围[0, 65535],无效值=65535 */
    VOS_UINT16                          usRac;              /* 取值范围[0,255],无效值=65535 */   // TODO: 待确认
}GAS_OM_ROAD_TEST_CELL_FULL_ID_STRU;

/*****************************************************************************
 结构名    : GAS_OM_ROAD_TEST_CCCH_PARA_STRU
 结构说明  : 路测需求 GAS向OM上报的服务小区CCCH参数结构
 修改历史  : 
 1.日    期    : 2012年11月07日
   作    者    : y49634
   修改内容    : 新建结构体 
*****************************************************************************/
typedef struct
{
    VOS_UINT16  usAttachAllowed;    /* 取值范围[0,1],无效值=65535 */
    VOS_UINT16  usAgBlk;            /* 取值范围[0,7],无效值=65535 */
    VOS_UINT16  usT3212;            /* 取值范围[0,63],无效值=65535 */
    VOS_UINT16  usMfrms;            /* 取值范围[2,9],无效值=65535 */
}GAS_OM_ROAD_TEST_CCCH_PARA_STRU;

/*****************************************************************************
 结构名    : GAS_OM_ROAD_TEST_CCCH_PARA_STRU
 结构说明  : 路测需求 GAS向OM上报的服务小区RACH参数结构
 修改历史  : 
 1.日    期    : 2012年11月07日
   作    者    : y49634
   修改内容    : 新建结构体 
*****************************************************************************/
typedef struct
{
    VOS_UINT16  usTxInt;            /* 取值范围[3,50],无效值=65535 */
    VOS_UINT16  usMaxRetrans;       /* 取值范围[1,7],无效值=65535 */
    VOS_UINT16  usCba;              /* 取值范围[0,1],无效值=65535 */
    VOS_UINT16  usReestablishment;  /* 取值范围[0,1],无效值=65535 */
}GAS_OM_ROAD_TEST_RACH_PARA_STRU;

/*****************************************************************************
 结构名    : GAS_OM_ROAD_TEST_CELL_SEL_RESEL_PARA_STRU
 结构说明  : 路测需求 GAS向OM上报的服务小区重选参数结构
 修改历史  : 
 1.日    期    : 2012年11月07日
   作    者    : y49634
   修改内容    : 新建结构体 
*****************************************************************************/
typedef struct
{
    VOS_UINT16  usMsTxPwrMaxCch;        /* 取值范围[0,31],无效值=65535 */
    VOS_INT16   sRxlevAccessMin;        /* 取值范围[-110,-47],无效值=-32768 */
    VOS_UINT16  usPowerOffsetValid;     /* 取值范围[0,1],无效值=65535 */
    VOS_UINT16  usPowerOffset;          /* 取值范围[0,3],无效值=65535 */
    VOS_UINT16  usCellReselHysteresis;  /* 取值范围[0,14],无效值=65535 */
    VOS_UINT16  usCellReselOffset;      /* 取值范围[0,63],无效值=65535 */
    VOS_UINT16  usTmpOffset;            /* 取值范围[0,7],无效值=65535 */
    VOS_UINT16  usPenaltyTime;          /* 取值范围[0,31],无效值=65535 */ 
    VOS_UINT16  usCbq;                  /* 取值范围[0,1],无效值=65535 */
    VOS_UINT16  usCellPri;              /* 取值范围[0,1],无效值=65535 */
}GAS_OM_ROAD_TEST_CELL_SEL_RESEL_PARA_STRU;

/*****************************************************************************
 结构名    : GAS_OM_ROAD_TEST_SCELL_CELL_PARA_STRU
 结构说明  : 路测需求 GAS向OM上报的服务小区信息结构
 修改历史  : 
 1.日    期    : 2012年11月07日
   作    者    : y49634
   修改内容    : 新建结构体 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usGprsSupported;    /* 取值范围[0,1],无效值=65535 */
    VOS_UINT16                                      usEGprsSupported;   /* 取值范围[0,1],无效值=65535 */
    GAS_OM_NETWORK_CONTROL_ORDER_ENUM_UINT16        enNcMode;           /* 取值范围[0,2],无效值=65535 */
    VOS_UINT16                                      usPbcchTs;          /* 取值范围[0,7],无效值=65535 */ 
    GAS_OM_ROAD_TEST_CELL_FULL_ID_STRU              stCellFullID;
    GAS_OM_ROAD_TEST_CCCH_PARA_STRU                 stCcchPara;
    GAS_OM_ROAD_TEST_RACH_PARA_STRU                 stRachPara;
    GAS_OM_ROAD_TEST_CELL_SEL_RESEL_PARA_STRU       stSelReselPara;
}GAS_OM_ROAD_TEST_SCELL_CELL_PARA_STRU;


/*****************************************************************************
 结构名    : GAS_OM_ROAD_TEST_DCH_CHAN_PARA_STRU
 结构说明  : 路测需求 GAS向OM上报的DCH信息结构
 修改历史  : 
 1.日    期    : 2012年11月07日
   作    者    : y49634
   修改内容    : 新建结构体 
*****************************************************************************/
typedef struct
{

    VOS_UINT16                                  usTSC;              /* 取值范围[0,7],无效值=65535 */
    VOS_UINT16                                  usMsDtx;            /* 取值范围[0,1],无效值=65535 */
    GAS_OM_VOICE_CHANNEL_TYPE_ENUM_UINT16       enChanType;         /* 取值范围[1,4],无效值=65535 */
    VOS_UINT16                                  usTchArfcn;         /* 取值范围[0,1023],无效值=65535 */
    VOS_UINT16                                  usTsNum;            /* 取值范围[0,7],无效值=65535 */
    GAS_OM_SPECCH_CODEC_ENUM_UINT16             enSpeechCodec;      /* 取值范围[0,8],无效值=65535 */
    GAS_OM_RR_CIPHER_ALGORITHM_ENUM_UINT16      enCipherAlgorithm;   /* 取值范围[0,8],无效值=65535 */
    VOS_UINT16                                  usSubChanNum;       /* 取值范围[0,7],无效值=65535 */
    VOS_UINT16                                  usHoppingState;     /* 取值范围[0,1],无效值=65535 */
    VOS_UINT16                                  usHoppingFreqCnt;   /* 取值范围[0,64],无效值=65535 */    
    VOS_UINT16                                  ausHoppingFreq[GAS_OM_HOPPING_REQ_CNT_MAX_NUM]; /* 取值范围[0,1023],无效值=65535 */
    VOS_UINT16                                  usMaio;             /* 取值范围[0,63],无效值=65535 */
    VOS_UINT16                                  usHsn;              /* 取值范围[0,63],无效值=65535 */

}GAS_OM_ROAD_TEST_DCH_CHAN_PARA_STRU;

/*****************************************************************************
 结构名    : GAS_OM_ROAD_TEST_RUN_MODE_STRU
 结构说明  : 路测需求 GAS向OM上报的GAS当前的运行状态信息结构
 修改历史  : 
 1.日    期    : 2012年11月07日
   作    者    : y49634
   修改内容    : 新建结构体 
*****************************************************************************/
typedef struct
{
    GAS_OM_GSM_RUNNING_MODE_ENUM_UINT16  enGsmMode;          /* 取值范围[0,1],无效值=65535 */
    GAS_OM_GPRS_RUNNING_MODE_ENUM_UINT16  enGprsMode;         /* 取值范围[0,1],无效值=65535 */
}GAS_OM_ROAD_TEST_RUN_MODE_STRU;

/*****************************************************************************
 结构名    : GAS_OM_ROAD_TEST_INFO_IND_STRU
 结构说明  : 路测需求 GAS向OM上报信息原语结构
 修改历史  : 
 1.日    期    : 2012年11月07日
   作    者    : y49634
   修改内容    : 新建结构体 
*****************************************************************************/
typedef struct
{
    OM_GAS_REPORT_TYPE_ENUM_UINT16          enReportType;                       /* 上报方式 */
    GAS_ROAD_TEST_INFO_TYPE_ENUM_UINT16     enRtInfoTypeChoice;                 /* 上报信息类型 */
    
    union
    {
        GAS_OM_ROAD_TEST_MEAS_RESULT_STRU        stRtMeasResult;                /* 测量结果数据 */
        GAS_OM_ROAD_TEST_SCELL_CELL_PARA_STRU    stRtScellPara;                 /* 服务小区参数数据 */
        GAS_OM_ROAD_TEST_DCH_CHAN_PARA_STRU      stRtDchChan;                   /* DCH参数数据 */
    }u;
    
    GAS_OM_ROAD_TEST_RUN_MODE_STRU          stRtRunMode;                        /* GSM/GPRS状态 */
    
}GAS_OM_ROAD_TEST_INFO_IND_STRU;
/* Added by yangsicong for probe接口新开发, 2012-10-30, end */


/*****************************************************************************
 结构名      : GAS_OM_JAM_DETECT_CTX_IND_STRU
 描述        : GAS给OM上报的Jamming Detection 上下文
 
 修改历史 :
 1.日    期   : 2015年2月17日
   作    者   : y00142674
   修改内容   : 新增结构, for W Jamming Detection

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usHighRxlevArfcnNum;                    /* 全部强信号频点 */
    VOS_UINT16                          usJammingArfcnNum;                      /* 同步失败的干扰频点个数 */
    VOS_UINT8                           ucRptedJamRlt;                          /* 已上报的干扰检测结果，0:无干扰, 1:有干扰 */

    VOS_UINT8                           ucMode;                                 /* JAM设置的模式，0:关闭, 1:打开 */
    VOS_UINT8                           ucMethod;                               /* JAM检测使用的方案，1:方案1；2:方案2,目前只支持2 */
    VOS_UINT8                           ucFreqNum;                              /* 检测需要达到的频点个数，取值范围:[0,255] */
    VOS_INT8                            cThreshold;                             /* 检测需要达到的频点测量值，取值范围:[-70,0] */
    VOS_UINT8                           ucJamDetectingTmrLen;                   /* 强信号频点个数满足门限后，检查同步结果的定时器时长(s) */
    VOS_UINT8                           ucJamDetectedTmrLen;                    /* 检测到干扰后，等待搜网结果的最长时间(s) */
    VOS_UINT8                           ucFastReportFlag;                       /* 搜网过程中是否需要快速上报 */  
}GAS_OM_JAM_DETECT_CTX_IND_STRU;

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 结构名    : GAS_OM_EVENT_LTE_TO_GSM_HANDOVER_START_ST
 结构说明  : GAS 向 OM 上报 获取LTE切换到GSM指令的SLICE值
 修改历史  : 
 1.日    期    : 2013年12月18日
   作    者    : s00184266
   修改内容    : 新建结构体 
*****************************************************************************/
typedef struct
{
    VOS_UINT32      ulCurSlice;
}GAS_OM_EVENT_LTE_TO_GSM_HANDOVER_START_ST;

/*****************************************************************************
 结构名    : GAS_OM_EVENT_LTE_TO_GSM_HANDOVER_END_ST
 结构说明  : GAS 向 OM 上报 Lte 到 Geran HANDOVER 结束
 修改历史  : 
 1.日    期    : 2013年9月13日
   作    者    : s00184266
   修改内容    : 新建结构体 
*****************************************************************************/
typedef struct
{
    LRRC_GURRC_HANDOVER_RESULT_ENUM_UINT32   enL2gHoRlt;
}GAS_OM_EVENT_LTE_TO_GSM_HANDOVER_END_ST;
#endif /* end of (FEATURE_ON == FEATURE_LTE) */

/*****************************************************************************
 结构名    : GAS_OM_EVENT_LAU_REQ_INFO_STRU
 结构说明  : GAS 向 OM 上报 LAU 的相关信息
 修改历史  : 
 1.日    期    : 2015年05月11日
   作    者    : p00166345
   修改内容    : 新建结构体 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRlt;
    NAS_LAU_TYPE_ENUM_UINT8             enLauType;
    VOS_UINT8                           ucFollowOnFlg;
    NAS_ADDITION_UPDATE_PARA_ENUM_UINT8 enAdditionUpdatePara;

    VOS_UINT8                           aucRsv[1];
}GAS_OM_EVENT_LAU_REQ_INFO_STRU;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_W_NON_NCELL_MEAS_START_ST
 Description    : W 非邻区测量启动事件
 Message origin :
*****************************************************************************/
typedef struct
{
    /* 保护定时器时长 */
    VOS_UINT32                          ulTimerLen;
}GAS_OM_EVENT_W_NON_NCELL_MEAS_START_ST;

#define GAS_OM_PLMN_SEARCH_CELL_SATISFACTION_RESULT_MAX_NUM           (60)

/*****************************************************************************
 结构名    : GAS_OM_CELL_SATISFACTION_RESULT_ST
 结构说明  : 小区的判决结果
 修改历史 :
  1.日    期   : 2014年04月01日
    作    者   : w00176595
    修改内容   : 新增结构体
  2.日    期   : 2015年8月19日
    作    者   : y00142674
    修改内容   : 上报区分结果和优先级，for ParallelSrch

*****************************************************************************/
typedef struct
{
    VOS_UINT16      usArfcn;                                        /* 频点 */
    VOS_UINT8       ucSatisfactionResult;                           /* 判决结果 */
    VOS_UINT8       ucCellPriorityFlag;                             /* 优先级 */                                         
}GAS_OM_CELL_SATISFACTION_RESULT_ST;

/*****************************************************************************
 结构名    : GAS_OM_PLMN_SRCH_CELL_SATISFACTION_RESULT_ST
 结构说明  : 小区的判决结果
 修改历史 :
 1.日    期    : 2014年04月01日
   作    者    : w00176595
   修改内容    : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                               usCellCount;
    VOS_UINT16                               usRsv;        
    GAS_OM_CELL_SATISFACTION_RESULT_ST       astCellSatisfaction[GAS_OM_PLMN_SEARCH_CELL_SATISFACTION_RESULT_MAX_NUM];
}GAS_OM_PLMN_SRCH_CELL_SATISFACTION_RESULT_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_EVENT_UTRAN_FDD_TO_GSM_CCO_START_ST
 结构说明  : GAS 向 OM 上报 UTRAN_FDD 到 G CCO 开始
 修改历史  :
  1.日  期   : 2014年5月5日
    作  者   : s00184266
    修改内容 : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;
    VOS_UINT8                           ucNcc;                                  /* (3bit) PLMN色码  */
    VOS_UINT8                           ucBcc;                                  /* (3bit) 基站色码  */
}GAS_OM_EVENT_UTRAN_FDD_TO_GSM_CCO_START_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_EVENT_UTRAN_FDD_TO_GSM_CCO_END_ST
 结构说明  : GAS 向 OM 上报 UTRAN_FDD 到 G CCO 结束
 修改历史  :
  1.日  期   : 2014年5月5日
    作  者   : s00184266
    修改内容 : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulW2GCcoRlt;
}GAS_OM_EVENT_UTRAN_FDD_TO_GSM_CCO_END_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_EVENT_UTRAN_FDD_TO_GSM_RESEL_START_ST
 结构说明  : GAS 向 OM 上报 UTRAN_FDD 到 G RESEL 开始
 修改历史  :
  1.日  期   : 2014年5月20日
    作  者   : s00186226
    修改内容 : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulArfcn;
    VOS_UINT32                          ulNcc;                                  /* (3bit) PLMN色码  */
    VOS_UINT32                          ulBcc;                                  /* (3bit) 基站色码  */
}GAS_OM_EVENT_UTRAN_FDD_TO_GSM_RESEL_START_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_FREQ_INFO_LIST_STRU
 结构说明  : OM上报频点列表
 修改历史  :
  1.日  期   : 2015年9月10日
    作  者   : s00184266
    修改内容 : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqNum; 
    VOS_UINT8                           aucRsv[2];
    VOS_UINT16                          ausFreqInfo[SEARCH_FREQ_BA_MAX_NUM];  
}GAS_OM_FREQ_INFO_LIST_STRU;

/*****************************************************************************
 结 构 名  : GAS_OM_SEARCH_PROC_INFO_STRU
 结构说明  : GAS搜网流程相关信息上报
 修改历史  :
  1.日  期   : 2015年9月10日
    作  者   : s00184266
    修改内容 : 新生成结构

*****************************************************************************/
typedef struct
{
    GAS_OM_SEARCH_PROC_ENUM_UINT8               enSrchProc;
    GAS_OM_SEARCH_PROC_BUILD_RESULT_ENUM_UINT8  enBuildResult;
    VOS_UINT16                                  usBandInfo;
    GAS_OM_FREQ_INFO_LIST_STRU                  stFreqInfoList;
}GAS_OM_SEARCH_PROC_INFO_STRU;

/*****************************************************************************
 结 构 名  : GAS_OM_SEARCHED_FREQ_LIST_STRU
 结构说明  : GAS已搜索列表上报
 修改历史  :
  1.日  期   : 2015年9月10日
    作  者   : s00184266
    修改内容 : 新生成结构

*****************************************************************************/
typedef struct
{
    GAS_OM_FREQ_INFO_LIST_STRU                  stFreqInfoList;
}GAS_OM_SEARCHED_FREQ_LIST_STRU;

/*****************************************************************************
 结 构 名  : GAS_OM_CSS_CLOUD_INTERFACE_STRU
 结构说明  :
 修改历史  :
  1.日  期   : 2015年11月5日
    作  者   : s00184266
    修改内容 : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulReturnValue;
    GAS_OM_CSS_INTERFACE_NAME_ENUM_UINT32       enCssInterfaceName;
    VOS_UINT32                                  ulPlmnNum;
    union
    {
        CSS_PREF_FREQ_INFO_STRU                 astPrefFreq[GAS_OM_CSS_INTERFACE_OUPUT_PREF_FREQ_MAX_NUM];

        CSS_PREF_BAND_INFO_STRU                 astPrefBand[GAS_OM_CSS_INTERFACE_OUPUT_PREF_BAND_MAX_NUM];
        
        CSS_PLMN_ID_STRU                        astPlmn[GAS_OM_CSS_INTERFACE_INPUT_PLMN_MAX_NUM];
    }u;
}GAS_OM_CSS_CLOUD_INTERFACE_STRU;

/*****************************************************************************
 Structure      : OM_GAS_NV_WRITE_REQ_STRU
 Description    : CI NV修改模块结构体
 Message origin :
*****************************************************************************/
typedef struct
{
    DIAG_GAS_MSG_COMM_HEAD_ST           stMsgCommHead;
    VOS_UINT8                           aucRsv[2];
    VOS_UINT16                          usNvItem;
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucData[4];
}OM_GAS_NV_WRITE_REQ_STRU;

typedef GAS_OM_OTA_CNF_STRUCT  GAS_OM_NV_WRITE_CNF_STRU;

/*****************************************************************************
 结 构 名  : SDT_GAS_CONNECTED_IND_STRU
 结构描述  : OM向GAS发送的HiDS连接消息

 修改历史      :
  1.日    期   : 2015年6月24日
    作    者   : 华宏 h00166210
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    DIAG_GAS_MSG_COMM_HEAD_ST           stMsgCommHead;
}SDT_GAS_CONNECTED_IND_STRU;

typedef GAS_OM_OTA_CNF_STRUCT  GAS_SDT_CONNECTED_CNF_STRU;

/*****************************************************************************
 结构名    : GAS_OM_TRANS_IND_ST
 协议表格  :
 ASN.1描述 : 透传消息上报公共结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16  usPrimId;
    VOS_UINT16  usReserved;
    VOS_UINT8   aucData[4];
}GAS_OM_TRANS_IND_ST;

/*****************************************************************************
 结 构 名  : GAS_OM_OTA_IND_STRUCT
 结构描述  : GAS向OM上报空口消息

 修改历史      :
  1.日    期   : 2008年4月21日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT16    usOtaMsgID;
    VOS_UINT8     ucUpDown;
    VOS_UINT8     ucRsv;
    VOS_UINT32    ulLengthASN;
    VOS_UINT8     aucData[4];
}GAS_OM_OTA_IND_STRUCT;

/******************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 函数申明
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
#endif /* __cplusplus */


#endif /* __GASOMINTERFACE_H__ */


