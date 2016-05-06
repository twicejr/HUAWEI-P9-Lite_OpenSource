/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : WasTimerAsn1.h
  版 本 号   : 初稿
  作    者   : s58750
  生成日期   : 2007年5月14日
  最近修改   :
  功能描述   : Mntn消息
  函数列表   :
  修改历史   :
  1.日    期   : 2007年5月14日
    作    者   : s58750
    修改内容   : 创建文件

******************************************************************************/

#ifndef __WASTIMERASN1_H__
#define __WASTIMERASN1_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "PsTypeDef.h"
#include "product_config.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

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
 Description    : 协议定时器和功能定时器 定义
                  BOUNDARY_START，标识该模块定时器在定时器表中的起始下标;
                  BOUNDARY_END，标识该模块定时器在定时器表中的结束下标;
                  各个模块的定时器定义需要定义在各自响应的区间中.
 Message origin :
*****************************************************************************/
enum WAS_TI_ENUM
{
    /* 协议定时器定义 */

    /* RB 模块定时器 */
    WAS_PTL_TI_RB_BOUNDARY_START                 = 0,                           /* RB 定时器开始边界      */

    WAS_PTL_TI_RB_BOUNDARY_END                   = 4,                           /* RB 定时器结束边界      */

    /* RRC 模块定时器 */
    WAS_PTL_TI_RRC_BOUNDARY_START                = 5,                       /* RRC 定时器开始边界     */
    TI_WAS_IDLE_T300                             = 6,
    TI_WAS_CONN_T304                             = 7,
    TI_WAS_CONN_T308                             = 8,
    TI_WAS_RRC_REJECT_WAIT_TIME                  = 9,                           /* 等待重发RRC CONN REQ定时器 */
    TI_WAS_RRC_CS_INDI_WAIT_RLC_CNF              = 10,                           /* CS域初始直传过程中等待RLC CNF的保护定时器 */
    TI_WAS_RRC_PS_INDI_WAIT_RLC_CNF              = 11,                           /* PS域初始直传过程中等待RLC CNF的保护定时器 */
    TI_WAS_RRC_FIRST_UL_DIRECT_WAIT_RLC_CNF      = 12,                           /* 第1位上行直传消息等待RLC CNF的保护定时器 */
    TI_WAS_RRC_SECOND_UL_DIRECT_WAIT_RLC_CNF     = 13,                           /* 第2位上行直传消息等待RLC CNF的保护定时器 */
    TI_WAS_RRC_THIRD_UL_DIRECT_WAIT_RLC_CNF      = 14,                           /* 第3位上行直传消息等待RLC CNF的保护定时器 */
    TI_WAS_RRC_FOURTH_UL_DIRECT_WAIT_RLC_CNF     = 15,                           /* 第4位上行直传消息等待RLC CNF的保护定时器 */
    TI_WAS_RRC_FIFTH_UL_DIRECT_WAIT_RLC_CNF      = 16,                           /* 第5位上行直传消息等待RLC CNF的保护定时器 */
    TI_WAS_RRC_SIXTH_UL_DIRECT_WAIT_RLC_CNF      = 17,                           /* 第6位上行直传消息等待RLC CNF的保护定时器 */
    TI_WAS_RRC_SEVENTH_UL_DIRECT_WAIT_RLC_CNF    = 18,                           /* 第7位上行直传消息等待RLC CNF的保护定时器 */
    TI_WAS_RRC_EIGHTH_UL_DIRECT_WAIT_RLC_CNF     = 19,                           /* 第8位上行直传消息等待RLC CNF的保护定时器 */
    TI_WAS_RRC_CS_SIGNAL_WAIT_RLC_CNF            = 20,                           /* CS域信令释放过程中等待RLC CNF的保护定时器*/
    TI_WAS_RRC_PS_SIGNAL_WAIT_RLC_CNF            = 21,                           /* PS域信令释放过程中等待RLC CNF的保护定时器*/
    TI_WAS_RRC_WAIT_SIB_CHG_SFN                  = 22,                           /* 等待SIB CHG SFN到达进行系统消息接收的定时器*/
    TI_WAS_RRC_SIGNAL_REL_WAIT_NW_REL            = 23,
    TI_WAS_RRC_FR                                = 24,                           /* 等待FR的定时器 */
    TI_WAS_PS_SUSPEND_PROTECT                    = 26,                              /* 挂起单PS业务保护定时器 */
    TI_WAS_CONN_T320                             = 27,                          /* T320定时器，发cu时停止，收到cu cnf进p或者ura_p,带waittime时启动 */
    WAS_PTL_TI_RRC_BOUNDARY_END                  = 31,                           /* RRC 定时器结束边界     */

    /* SMC 模块定时器 */
    WAS_PTL_TI_SMC_BOUNDARY_START                = 32,                        /* SMC 定时器ID开始边界     */

    WAS_PTL_TI_SMC_BOUNDARY_END                  = 35,                           /* SMC 定时器ID结束边界     */

    /* CU  模块定时器 */
    WAS_PTL_TI_CU_BOUNDARY_START                 = 36,                        /* CU 定时器开始边界      */
    TI_WAS_CONN_T302                             = 37,
    TI_WAS_CONN_T314                             = 38,
    TI_WAS_CONN_T315                             = 39,

    TI_WAS_CU_PROCESS_MSG_DISCARD                = 40,                       /*自定义定时器,丢弃CU流程前的信令*/

    WAS_PTL_TI_CU_BOUNDARY_END                   = 46,                           /* CU 定时器结束边界      */

    /* CSELPC 模块定时器 */
    WAS_PTL_TI_CSELPC_BOUNDARY_START             = 47,                        /* CSELPC 定时器开始边界  */
    TI_WAS_CSELPC_OUT_SERV                       = 48,                           /* 短暂的出服务区周期搜候补小区定时器*/
    TI_WAS_CSELPC_UNRECOVERABLE_WAIT             = 49,                           /* CSELPC在收到L2不可恢复错的时候，需要等3s，当发现不是迁移流程时处理不可恢复的错*/
    TI_WAS_CSELPC_UNRECOVERABLE_RESTART          = 50,                           /* CSELPC在迁移流程后需要再等1分钟再处理不可恢复的错*/
    TI_WAS_CSELPC_IDLE_CAND_SEARCH               = 51,                           /* CSELPC在IDLE态下出服务区后在30s内周期搜索候补小区*/
    TI_WAS_CONN_T317                             = 52,
    TI_WAS_CSELPC_RF_UNAVAILABLE                 = 53,                           /* 资源不可用定时器 */
    TI_WAS_NOISE_DETECT                          = 54,                           /* 流水声检测定时器超时 */
    WAS_PTL_TI_CSELPC_BOUNDARY_END               = 62,                           /* CSELPC 定时器结束边界  */

    /* SHO 模块定时器 */
    WAS_PTL_TI_SHO_BOUNDARY_START                = 63,                           /* SHO 定时器开始边界     */

    WAS_PTL_TI_SHO_BOUNDARY_END                  = 66,                           /* SHO 定时器结束边界     */


    /* SYSHO 模块定时器 */
    WAS_PTL_TI_SYSHO_BOUNDARY_START              = 67,                           /* SYSHO 定时器开始边界   */
    TI_WAS_SYSHO_DELAY_FOR_L2ACK                 = 68,                           /* W2G小区变更释放层2前的保护定时器 */
    TI_WAS_SYSHO_W2L_DELAY_FOR_L2ACK             = 69,                           /* W2L小区切换放层2前的保护定时器 */
    WAS_PTL_TI_SYSHO_BOUNDARY_END                = 71,                           /* SYSHO 定时器结束边界   */

    /* RM 模块定时器 */
    WAS_PTL_TI_RM_BOUNDARY_START                 = 72,                           /* RM 定时器开始边界      */
    TI_WAS_RM_INTRA_FREQ_MEAS_EVT_TRIG           = 73,                           /* 同频测量的trigger timer*/
    TI_WAS_RM_INTRA_FREQ_MEAS_PERI_RPT           = 74,                           /* 同频测量的周期报告模式使用的周期定时器   */
    TI_WAS_RM_INTRA_FREQ_MEAS_EVT_PERI_RPT       = 75,                           /* 同频测量的事件触发模式使用的周期定时器   */
    TI_WAS_RM_INTER_FREQ_MEAS_EVT_TRIG           = 76,                           /* 异频测量的trigger timer*/
    TI_WAS_RM_INTER_FREQ_MEAS_PERI_RPT           = 77,                           /* 异频测量的周期定时器   */
    TI_WAS_RM_INTER_FREQ_MEAS_VAS_EVT_TRIG       = 78,                           /* 虚激活集的trigger timer*/
    TI_WAS_RM_INTER_RAT_MEAS_EVT_TRIG            = 79,                           /* 异系统测量的trigger timer*/
    TI_WAS_RM_INTER_RAT_MEAS_PERI_RPT            = 80,                           /* 异系统测量的周期定时器 */
    TI_WAS_RM_UE_INTERNAL_MEAS_EVT_TRIG          = 81,                           /* UE内部测量的trigger timer*/
    TI_WAS_RM_UE_INTERNAL_MEAS_PERI_RPT          = 82,                           /* Ue内部测量的周期定时器 */
    TI_WAS_RM_TRAF_VOL_MEAS_PERI_RPT             = 83,                           /* 业务流量测量的周期定时器*/
    TI_WAS_RM_QUAL_MEAS_PERI_RPT                 = 84,                           /* 质量测量的周期定时器   */
    TI_WAS_RM_POS_MEAS_PERI_RPT                  = 85,                           /* 定位测量的周期定时器 */
    TI_WAS_RM_RPT_BUF                            = 86,                           /* RM发送测量报告时,申请的、存在rpt buf里的动态内存的保护定时器*/
    TI_WAS_RM_EUTRA_MEAS_EVT_TRIG                = 87,                           /* EUTRA测量的trigger timer*/
    TI_WAS_RM_EUTRA_MEAS_PERI_RPT                = 88,                           /* EUTRA测量的周期定时器 */
    TI_WAS_RM_REQ_SAME_ADD_ASSIST_DATA           = 89,                           /* 请求相同的辅助数据的定时器 */
    WAS_PTL_TI_RM_BOUNDARY_END                   = 100,                           /* RM 定时器结束边界      */

    /* SIB 模块定时器 */
    WAS_PTL_TI_SIB_BOUNDARY_START                = 101,                           /* SIB 定时器开始边界     */
    TI_WAS_SIB_REPEAT_SIB7                       = 102,                           /* 接收SIB7周期定时器     */
    TI_WAS_SIB_6HOUR_PERIOD                      = 103,                           /* 6小时周期定时器        */
    WAS_PTL_TI_SIB_BOUNDARY_END                  = 109,                           /* SIB 定时器结束边界     */

    /* CSEL 模块定时器 */
    WAS_PTL_TI_CSEL_BOUNDARY_START               = 110,                           /* CSEL 定时器开始边界    */
    TI_WAS_CSEL_CELL_LIST_VALID                  = 111,                           /* 搜网时存储的小区信息有效的定时器，30s*/
    TI_WAS_CSEL_USER_PLMN_LIST_RSSI_BAND_VALID   = 112,                           /* 用户指定进行PLMN List搜索时，全频段的RSSI排序是否还有效的定时器 */
    TI_WAS_CSEL_TRESELECTION                     = 113,                           /* 重选定时器,单位100ms */
    TI_WAS_CSEL_TEVALUATE                        = 114,                           /* Treselection = 0时,评估时间定时器，单位100ms */
    TI_WAS_CSEL_TN                               = 115,                           /* 使用HCS结构时，为邻区维护的Tn定时器  */
    TI_WAS_CSEL_TBARRED                          = 116,                           /* 阻塞小区定时器 */
    TI_WAS_CSEL_OUT_OF_SERVICE                   = 117,                           /* IDLE，P状态下重选定时器,12s;FACH下出服务区定时器，4s */
    TI_WAS_CSEL_RESEL_BARRED                     = 118,                           /* 禁止重选定时器，1s        */
    TI_WAS_CSEL_GSM_BSIC_VERIFY                  = 119,                           /* BSIC验证的定时器周期:IDLE，P状态下时长30s;FACH下时长10s，*/
    TI_WAS_CSEL_WAIT_GSM_BSIC_VERIFY_IND         = 120,                           /* BSIC验证启动后等待验证结果的保护定时器 */
    TI_WAS_CSEL_DETECT_UE_MOBILITY_STATE         = 121,                           /* 检测UE移动状态的单位定时器，10s*/
    TI_WAS_CSEL_DETECT_EXIT_HIGH_MOBILITY        = 122,                           /* 检测退出高速移动状态的定时器 */
    TI_WAS_CSEL_JAM_DETECTING                    = 123,                           /* 搜网过程中干扰检测定时器 */
    TI_WAS_CSEL_JAM_DETECTED                     = 124,                           /* 搜网过程中干扰存在定时器 */
#if (FEATURE_ON == FEATURE_LTE)
    TI_WAS_CSEL_W2L_RESEL_PENALTY                = 125,                           /* W2L重选惩罚定时器 */
#endif
    WAS_PTL_TI_CSEL_BOUNDARY_END                 = 132,                           /* CSEL 定时器结束边界    */

    /* MAIN 模块定时器 */
    WAS_PTL_TI_MAIN_BOUNDARY_START               = 133,                           /* MAIN 定时器开始边界    */
    TI_WAS_MAIN_INTERRAT_RESEL_WAIT_EST_REQ      = 134,                           /* l2w或者g2w重选结束的时候等待注册消息 */
    WAS_PTL_TI_MAIN_BOUNDARY_END                 = 136,                           /* MAIN 定时器结束边界    */

    /* COMM 模块定时器 */
    WAS_PTL_TI_COMM_BOUNDARY_START               = 137,                           /* COMM 定时器开始边界    */

    WAS_PTL_TI_COMM_BOUNDARY_END                 = 139,                           /* COMM 定时器结束边界    */

    /* NASITF 模块定时器 */
    WAS_PTL_TI_NASITF_BOUNDARY_START             = 140,                           /* NASITF 定时器开始边界  */

    WAS_PTL_TI_NASITF_BOUNDARY_END               = 142,                           /* NASITF 定时器结束边界  */

    /* TAFITF 模块定时器 */
    WAS_PTL_TI_TAFITF_BOUNDARY_START             = 143,                           /* TAFITF 定时器开始边界  */

    WAS_PTL_TI_TAFITF_BOUNDARY_END               = 145,                           /* TAFITF 定时器结束边界  */

    /* PHYITF 模块定时器 */
    WAS_PTL_TI_PHYITF_BOUNDARY_START             = 146,                           /* PHYITF 定时器开始边界  */
    TI_WAS_CONN_T312                             = 147,
    TI_WAS_IDLE_T312                             = 148,
    TI_WAS_CONN_T313                             = 149,
    TI_WAS_SYNC_DETECT                           = 150,                           /* 同步预检测定时器 */
    TI_WAS_JUDGE_DISABLE_UL_TX                   = 151,                           /* 失步时，上行不再发数   */
    WAS_PTL_TI_PHYITF_BOUNDARY_END               = 152,                           /* PHYITF 定时器结束边界  */

    /* L2ITF 模块定时器 */
    WAS_PTL_TI_L2ITF_BOUNDARY_START              = 153,                         /* L2ITF 定时器开始边界   */

    WAS_PTL_TI_L2ITF_BOUNDARY_END                = 159,                           /* L2ITF 定时器结束边界   */

    /* ASN1 模块定时器 */
    WAS_PTL_TI_ASN1_BOUNDARY_START               = 160,                           /* ASN1 定时器开始边界    */

    WAS_PTL_TI_ASN1_BOUNDARY_END                 = 162,                           /* ASN1 定时器结束边界    */

    /* MNTN 模块定时器 */
    WAS_PTL_TI_MNTN_BOUNDARY_START               = 163,                           /* MNTN 定时器开始边界    */

    TI_WAS_MNTN_ACT_OR_SERV_CELL_INFO_PERI_RPT   = 164,                           /* 周期上报主小区或激活集小区定时器 */
    TI_WAS_MNTN_W_NEIGH_CELL_INFO_PERI_RPT       = 165,                           /* 周期W邻小区定时器                */
    TI_WAS_MNTN_G_NEIGH_CELL_INFO_PERI_RPT       = 166,                           /* 周期G邻小区定时器                */
    TI_WAS_MNTN_SECOND_CELL_INFO_PERI_RPT        = 167,                           /* SECOND CELL上报主小区或激活集小区，以及SECOND CELL邻区定时器 */
    TI_WAS_MNTN_L_NEIGH_CELL_INFO_PERI_RPT       = 168,                           /* 周期LTE邻小区定时器  */
    TI_WAS_MNTN_ERROR_LOG_SAMPLE_IND             = 169,                           /* error log采样定时器，时间长度为1分钟*/
    TI_WAS_MNTN_GET_TAF_SRV_STATUS_FLAG          = 170,                         /* 连接态下,延迟获取TAF服务状态定时器 */
#if (FEATURE_ON == FEATURE_PTM)
    TI_WAS_MNTN_ERRORLOG_3G_NOT_TO_LTE_TIMER     = 171,                           /* 在W模下驻留的时间定时器 */
#endif    

    WAS_PTL_TI_MNTN_BOUNDARY_END                 = 180,                           /* MNTN 定时器结束边界    */


    /* 其他定时器定义,包括保留定时和公共定时器 */
    WAS_PTL_TI_OTHERS                            = 181,                           /* 其他定时器开始边界 */
    TI_WAS_CONN_T305                             = 182,                           /*RB 和 CSELPC*/
    TI_WAS_CONN_T309                             = 183,
    TI_WAS_CONN_T310                             = 184,
    TI_WAS_CONN_T311                             = 185,
    TI_WAS_CONN_T316                             = 186,                           /*RB 和 CSELPC */
    TI_WAS_CONN_T307                             = 187,                           /*RB 和 CSELPC */
    TI_WAS_SRB_DELAY                             = 188,                           /* 建DCH的模块都需要 */
    TI_WAS_RESEL_DELAY                           = 189,       /* 延时等待重选上报，规避gcf用例 */

    TI_WAS_TIMER_OUT_OF_SERVICE                  = 190,       /*出服务区协议定时器,TimerOutOfService time (default value 30 seconds)*/
    TI_WAS_OUT_OF_SERVICE_PERIOD_SEARCH_SUITABLE = 191,
    TI_WAS_CONN_T319                             = 192,                         /* CSELPC T319双DRX定时器超时定时器 */
    TI_WAS_CONN_T322                             = 193,                         /* 优先级定时器 */
    TI_WAS_CONN_T323                             = 194,                         /* FastDormancy 定时器 */

    WAS_PTL_TI_NAS_SESSION_BOUNDARY_START        = 200,                         /* NAS_SESSION 定时器开始边界   */

    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_MO_NORMAL_CALL        = 201,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_MO_EMERGENCY_CALL     = 202,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_MO_SS                 = 203,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_MO_SMS                = 204,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_MT_NORMAL_CALL        = 205,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_MT_EMERGENCY_CALLBACK = 206,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_MT_SS                 = 207,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_MT_SMS                = 208,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_LAU                   = 209,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_DETACH                = 210,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_MO_NORMAL_CSFB        = 211,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_MO_EMERGENCY_CSFB     = 212,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_MT_CSFB               = 213,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_PS_CONVERSAT_CALL        = 214,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_PS_STREAM_CALL           = 215,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_PS_INTERACT_CALL         = 216,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_PS_BACKGROUND_CALL       = 217,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_PS_SUBSCRIB_TRAFFIC_CALL = 218,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_PS_MO_SMS                = 219,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_PS_MT_SMS                = 220,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_PS_ATTACH                = 221,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_PS_RAU                   = 222,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_PS_DETACH                = 223,

    WAS_PTL_TI_NAS_SESSION_BOUNDARY_END             = 229,                      /* NAS_SESSION 定时器结束边界   */

    WAS_PTL_TI_BUTT                                 = 230,

    /* 状态保护定时器定义 */
    /* RB 模块定时器 */
    WAS_STATE_TI_RB_BOUNDARY_START                 = 0xF000 ,                   /* RB 定时器开始边界      */
    TI_WAS_RB_WAIT_WCOM_CNF                                 ,                   /* 在给WCOMM发消息后启该定时器
                                                                                    等待WCOMM的响应消息 */
    TI_WAS_RB_WAIT_NAS_RSP                                  ,                   /* 等待NAS RSP的状态保护定时器 */
    TI_WAS_RB_WAIT_ACTIVE_IND                               ,                   /* 配置后等待激活时间到ind保护定时器 */
    TI_WAS_RB_WAIT_AM_DATA_CNF                              ,                   /* 等待AM Data 确认保护定时器 */
    TI_WAS_RB_WAIT_DLSYNC_CNF                               ,                   /* 等待DL SYNC CNF保护定时器 */
    TI_WAS_RB_WAIT_TI_SRBDELAY                              ,                   /* 对等待SRB Delay定时器超时的子状态进行保护 */
    TI_WAS_RB_WAIT_CELL_SEARCH_CNF                          ,                   /* 等待小区搜索保护定时器 */
    TI_WAS_RB_WAIT_CELL_CHANGE_RPT                          ,                   /* 等待小区重选结果的定时器时长，9s*/
    WAS_STATE_TI_RB_BOUNDARY_END                            ,                   /* RB 定时器结束边界      */

    /* RRC 模块定时器 */
    WAS_STATE_TI_RRC_BOUNDARY_START                         ,                   /* RRC 定时器开始边界     */
    TI_WAS_RRC_CONN_SETUP_CMP_CNF                           ,                   /* 等待RLC对RRC CONN SETUP CMP的发送确认*/
    TI_WAS_RRC_WAIT_PHY_CAMPED_CNF                          ,                   /* 等待PHY CAMPED CNF的定时器_*/
    TI_WAS_RRC_WAIT_WCOMM_CNF                               ,                   /* 等待WCOMM回复的保护定时器*/
    TI_WAS_RRC_WAIT_SIB_CNF                                 ,                   /* 等待SIB回复的保护定时器*/
    TI_WAS_RRC_WAIT_RM_CNF                                  ,                   /* 等待RM回复的保护定时器*/
    TI_WAS_RRC_WAIT_CSEL_CNF                                ,                   /* 等待CSEL回复的保护定时器*/
    TI_WAS_RRC_WAIT_SIB_CHG_CNF                             ,                   /* 等待SIB系统消息变更接收回复的保护定时器*/
    TI_WAS_RRC_WAIT_CSEL_SEARCH_CNF                         ,                   /* 等待CSEL小区搜索回复的保护定时器*/
    TI_WAS_RRC_REL_STATE                                    ,                   /* RRC RELEASE流程处理中的状态保护定时器 */
    TI_WAS_MAC_STATUS_IND                                   ,                   /* 等待MAC STATUS IND定时器*/
    TI_WAS_PHY_DL_SYNC_IND                                  ,                   /* 等待DL SYNC IND 的定时器*/
    TI_WAS_RRC_WAIT_GAS_RESEL_CNF                           ,                   /* 等待GAS回复WRRCRR_CELL_RESEL_TIMER_EXPIRED_CNF的定时器 */
    TI_WAS_RRC_WAIT_CELL_CHANGE_RPT                         ,                   /* 等待小区重选结果的定时器时长，9s*/
    TI_WAS_RRC_WAIT_REDIRECTION_CNF                         ,
    TI_WAS_RRC_WAIT_BG_SEARCH_STOP_CNF                      ,                   /* 停止背景搜结果的定时器，5s     */

#if (FEATURE_ON == FEATURE_DSDS)
    TI_WAS_RRC_WAIT_RRM_RF_RES_APPLY_CNF                    ,                   /* 等待RF资源申请响应的定时器 */
    TI_WAS_RRC_SEARCH_WAIT_RRM_RF_RES_APPLY_CNF             ,                   /* RRC中搜网资源申请，等待RF资源申请响应的定时器 */
    TI_WAS_RRC_REL_WAIT_RRM_RF_RES_APPLY_CNF                ,                   /* RRC REL 流程中资源申请 */
#endif

    WAS_STATE_TI_RRC_BOUNDARY_END                           ,                   /* RRC 定时器结束边界     */

    /* CBS 模块定时器 */
    WAS_STATE_TI_CBS_BOUNDARY_START                         ,
    TI_WAS_CBS_STATE_PROTECT                                ,                   /* CBS 状态保护定时器 */
    TI_WAS_CBS_NO_USE                                       ,                   /* 不使用 */
    WAS_STATE_TI_CBS_BOUNDARY_END,

    /* SMC 模块定时器 */
    WAS_STATE_TI_SMC_BOUNDARY_START                         ,
    TI_WAS_SMC_WAIT_RLC_CNF                                 ,                   /* */
    TI_WAS_SMC_CELL_CHG_WAIT_RLC_CNF                        ,                   /* 发送SMC cmpl发生重选后等待RLC CNF的保护定时器*/
    WAS_STATE_TI_SMC_BOUNDARY_END                           ,

    /* CU  模块定时器 */
    WAS_STATE_TI_CU_BOUNDARY_START                          ,                   /* CU 定时器开始边界      */
    TI_WAS_CU_WAIT_CNF                                      ,
    TI_WAS_CU_WAIT_DLSYNC_CNF                               ,                   /* 等待DL SYNC CNF保护定时器 */
    TI_WAS_CU_WAIT_TI_SRBDELAY                              ,                   /* 对等待SRB Delay定时器超时的子状态进行保护 */
    TI_WAS_CU_WAIT_CELL_SEARCH_CNF                          ,                   /* CU中搜小区保护状态定时器*/
    TI_WAS_CU_WAIT_PLMN_SEARCH_CNF                          ,                   /* CU等待W全频搜索状态保护定时器*/
    TI_WAS_CU_WAIT_ANY_CELL_SEARCH_CNF                      ,
    TI_WAS_CU_WAIT_GSM_SEARCH_CNF                           ,                   /* 等待GSM小区搜索超时定时器,1分钟*/
    TI_WAS_CU_WAIT_LTE_SEARCH_CNF                           ,
    TI_WAS_CU_WAIT_CELL_CHANGE_RPT                          ,                   /* 等待小区重选结果的定时器时长，9s*/
    TI_WAS_CU_WAIT_BG_SEARCH_STOP_CNF                       ,                   /* 等待停止背景搜结果的定时器时长，5s */
    TI_WAS_CU_WAIT_WCOM_CNF                                 ,                   /* CU在给WCOMM发消息后启该定时器，等待WCOMM的响应消息 */
    WAS_STATE_TI_CU_BOUNDARY_END                            ,                   /* CU 定时器结束边界      */

    /* CSELPC 模块定时器 */
    WAS_STATE_TI_CSELPC_BOUNDARY_START                      ,                   /* CSELPC 定时器开始边界  */
    TI_WAS_CSELPC_WAIT_CNF                                  ,
    TI_WAS_CSELPC_WAIT_GAS_RESEL_CNF                        ,                   /* CSELPC W2G异系统重选时等待GAS响应的保护定时器*/
    TI_WAS_CSELPC_WAIT_LRRC_RESEL_CNF                        ,                  /* CSELPC W2L异系统重选时等待GAS响应的保护定时器*/
    TI_WAS_CSELPC_WAIT_LOAD_AMR_CODEC                       ,                   /* CSELPC 等待加载声码器的保护定时器*/
    TI_WAS_CSELPC_WAIT_PLMN_SEARCH_CNF                      ,
    TI_WAS_CSELPC_WAIT_CAND_CELL_SEARCH_CNF                 ,
    TI_WAS_CSELPC_WAIT_SPEC_FREQ_SEARCH_CNF                 ,                   /* CSELPC 等待指定频点搜网结果的保护定时器*/
    TI_WAS_CSELPC_WAIT_ANY_CELL_SEARCH_CNF                  ,
    TI_WAS_CSELPC_WAIT_G_PLMN_SEARCH_TIMER                  ,
    TI_WAS_CSELPC_WAIT_L_PLMN_SEARCH_TIMER                  ,
    TI_WAS_CSELPC_DEACTIVE_WAIT_RESUME_REQ                  ,                   /* cselpc挂起后等待gas恢复背景搜 */
    TI_WAS_CSELPC_DEACTIVE_WAIT_STOP_CNF                    ,                   /* cselpc等待csel回复stop cnf */
    TI_WAS_CSELPC_DEACTIVE_WAIT_SUSPEND_OR_RESUME_CNF       ,                   /* 从模背景搜下cselpc等待csel回复BG SUSPEND或者RESUME CNF的定时器 */
    TI_WAS_CSELPC_WAIT_PLMN_LIST_SEARCH_CNF                 ,                   /* cselpc等待csel回复PLMN LIST CNF的定时器 */
    TI_WAS_CSELPC_WAIT_BG_SEARCH_STOP_CNF                   ,                   /* cselpc等待csel回复BG STOP CNF的定时器 */
    TI_WAS_CSELPC_GET_CGI_INFO_WAIT_STOP_CNF                ,                   /* cselpc等待csel回复stop cnf */
    WAS_STATE_TI_CSELPC_BOUNDARY_END                        ,                   /* CSELPC 定时器结束边界  */

    /* SHO 模块定时器 */
    WAS_STATE_TI_SHO_BOUNDARY_START                         ,                   /* SHO 定时器开始边界     */
    TI_WAS_SHO_WAIT_RM_SHO_RSP                              ,                   /* SHO等待ID_WAS_RM_SHO_RSP时的保护定时器 */
    TI_WAS_SHO_WAIT_ACTIVE_IND                              ,                   /* SHO等待L2和PHY的ACTIVE IND的保护定时器*/
    TI_WAS_SHO_WAIT_RM_DC_CHG_RSP                           ,                   /* SHO等待ID_WAS_RM_DC_CHANGE_RSP的保护定时器*/
    TI_WAS_SHO_WAIT_WCOM_CNF                                ,                   /* SHO在给WCOMM发消息后启该定时器，等待WCOMM的响应消息 */
    WAS_STATE_TI_SHO_BOUNDARY_END                           ,                   /* SHO 定时器结束边界     */

    /* SYSHO 模块定时器 */
    WAS_STATE_TI_SYSHO_BOUNDARY_START                       ,                   /* SYSHO 定时器开始边界   */
    TI_WAS_SYSHO_WAIT_LOAD_VOCODEC_CNF                      ,                   /* 等待LOAD DSP回复CNF消息状态保护定时器超时    */
    TI_WAS_SYSHO_WAIT_CSEL_SEARCH_CNF                       ,                   /* 等待CSEL回复搜网CNF时消息状态保护定时器超时      */
    TI_WAS_SYSHO_WAIT_PLMN_SEARCH_CNF                       ,
    TI_WAS_SYSHO_WAIT_NAS_RSP                               ,                   /* 等待NAS回复RSP时消息状态保护定时器超时       */
    TI_WAS_SYSHO_WAIT_RM_RSP                                ,                   /* 等待RM回复RSP时消息状态保护定时器超时        */
    TI_WAS_SYSHO_WAIT_GAS_RSP                               ,                   /* 等待GAS回复消息状态保护定时器超时            */
    TI_WAS_SYSHO_WAIT_GAS_CNF                               ,                   /* 等待GAS回复CNF的状态保护定时器超时,用于HHO   */
    TI_WAS_SYSHO_WAIT_SIB_CNF                               ,                   /* 等待SIB回复CNF时消息状态保护定时器超时       */
    TI_WAS_SYSHO_WAIT_CSEL_CNF                              ,                   /* 等待CSEL回复CNF时消息状态保护定时器超时      */
    TI_WAS_SYSHO_WAIT_LRRC_CNF                              ,
    TI_WAS_SYSHO_WAIT_LRRC_HO_CNF                           ,
    TI_WAS_SYSHO_WAIT_LRRC_HO_STOP_CNF                      ,
    TI_WAS_SYSHO_WAIT_GAS_STOP_CNF                          ,                   /* 等待GAS回复HO_STOP_CNF时消息状态保护定时器超时      */
    WAS_STATE_TI_SYSHO_BOUNDARY_END                         ,                   /* SYSHO 定时器结束边界   */

    /* RM 模块定时器 */
    WAS_STATE_TI_RM_BOUNDARY_START                          ,                   /* RM 定时器开始边界      */
    TI_WAS_RM_WAIT_PHY_CNF                                  ,                   /* RM 建立或释放物理层测量对象保护定时器 */
    TI_WAS_RM_WAIT_L2_CNF                                   ,                   /* RM 建立或释放L2测量对象保护定时器 */
    TI_WAS_RM_INTER_RAT_BSIC_VERIFIED                       ,                   /* 异系统测量中发送Bsic验证的定时器 */

    TI_WAS_RM_WAIT_GSM_BSIC_VERIFIED_CNF                  ,                   /* 等待GSM BSIC CNF, 时长1s */

    TI_WAS_RM_INTER_RAT_WAIT_BSIC_IND                       ,                   /* 异系统测量等待物理层BSIC_IND保护定时器 */
    WAS_STATE_TI_RM_BOUNDARY_END                            ,                   /* RM 定时器结束边界      */

    /* SIB 模块定时器 */
    WAS_STATE_TI_SIB_BOUNDARY_START                         ,                   /* SIB 定时器开始边界     */
    TI_WAS_SIB_WAIT_PCCPCH_SETUP_CNF                        ,                   /* 建立PCCPCH保护定时器   */
    TI_WAS_SIB_WAIT_RCV_SYSINFO                             ,                   /* 接收系统信息保护定时器 */
    TI_WAS_SIB_WAIT_RCV_SIB7                                ,                   /* 接收sib7流程保护定时器 */
    TI_WAS_SIB_WAIT_PCCPCH_RELEASE_CNF                      ,                   /* 释放PCCPCH保护定时器   */
    TI_WAS_SIB_WAIT_ACT_TIME                                ,                   /* 等待激活时间定时器     */
    TI_WAS_SIB_WAIT_CHG_CMPL_RSP                            ,                   /* 等待SysInfo Chg Rsp保护定时器 */
    TI_WAS_SIB_WAIT_COUNT_BCCH_DATA                         ,                   /* 收到第一个BCCH DATA IND的1s保护定时器 */
    TI_WAS_SIB_WAIT_POS_NOTIFY_CNF                          ,                   /* 等待位置信息配置响应保护定时器，时长1s */
    TI_WAS_SIB_WAIT_RCV_DCH_SYSINFO                         ,                   /* 接收DCH系统信息流程保护定时器 */
    WAS_STATE_TI_SIB_BOUNDARY_END                           ,                   /* SIB 定时器结束边界     */

    /* CSEL 模块定时器 */
    WAS_STATE_TI_CSEL_BOUNDARY_START                        ,                   /* CSEL 定时器开始边界    */
    TI_WAS_CSEL_WAIT_PHY_CELL_SEARCH_CNF                    ,                   /* 单个频点搜索时的定时器*/
    TI_WAS_CSEL_FREQ_BAND_WAIT_PHY_CELL_SEARCH_CNF          ,                   /* 频带搜索时的定时器*/
    TI_WAS_CSEL_WAIT_PHY_CAMPED_MAINCELL_CNF                ,
    TI_WAS_CSEL_WAIT_PHY_MEASUREMENT_CNF                    ,
    TI_WAS_CSEL_WAIT_PHY_BSIC_VERIFIED_CNF                  ,
    TI_WAS_CSEL_WAIT_GSM_BSIC_VERIFIED_CNF                  ,                   /* 等待GSM BSIC CNF, 时长1s */
    TI_WAS_CSEL_WAIT_SIB_GET_SYSINFO_CNF                    ,
    TI_WAS_CSEL_WAIT_SIB_REL_SYSINFO_CNF                    ,
    TI_WAS_CSEL_WAIT_CELL_CHANGE_RSP                        ,
    TI_WAS_CSEL_WAIT_PHY_MEAS_SND_CNF                       ,                   /* CSEL IDLE/CONN态等待测量请求CNF消息定时器 */
    TI_WAS_CSEL_WAIT_PHY_FREQ_MEASURE_IND                   ,                   /* 等待PHY上报粗扫结果 */
    TI_WAS_CSEL_WAIT_BG_SUSPEND_CNF                         ,                   /* 等待BG暂停背景搜或者手动搜网的响应 */
    TI_WAS_CSEL_WAIT_BG_RESUME_CNF                          ,                   /* 等待BG重启背景搜或者手动搜网的响应 */
    WAS_STATE_TI_CSEL_BOUNDARY_END                          ,                   /* CSEL 定时器结束边界 */

    WAS_STATE_TI_BG_BOUNDARY_START                          ,
    TI_WAS_BG_WAIT_PHY_BG_SEARCH_STOP_CNF                   ,
    TI_WAS_BG_WAIT_PHY_BG_SEARCH_SUSPEND_CNF                ,
    TI_WAS_BG_WAIT_CSEL_BG_SEARCH_RESUEM_REQ                ,
    TI_WAS_BG_WAIT_PHY_BG_SEARCH_RESUEM_CNF                 ,

    TI_WAS_BG_WAIT_GSM_PHY_BG_SEARCH_CNF                    ,
    TI_WAS_BG_WAIT_GSM_BG_SEARCH_IND                        ,

    TI_WAS_BG_WAIT_GSM_BG_SEARCH_CNF                        ,
    TI_WAS_BG_WAIT_GSM_BG_SEARCH_STOP_CNF                   ,
    TI_WAS_BG_WAIT_GSM_BG_SEARCH_SUSPEND_CNF                ,
    TI_WAS_BG_WAIT_GSM_BG_SEARCH_RESUME_CNF                 ,
    TI_WAS_BG_WAIT_LTE_BG_SEARCH_CNF                  ,
    TI_WAS_BG_WAIT_LTE_BG_SEARCH_IND                        ,
    TI_WAS_BG_WAIT_LTE_BG_SEARCH_STOP_CNF                   ,
    TI_WAS_BG_WAIT_LTE_PHY_BG_SEARCH_CNF              ,
    TI_WAS_BG_WAIT_LTE_BG_SEARCH_SUSPEND_CNF                ,
    TI_WAS_BG_WAIT_LTE_BG_SEARCH_RESUME_CNF                 ,
    TI_WAS_BG_DEACTIVE_WAIT_RESUME_REQ                      ,                   /* cselpc挂起后等待gas恢复背景搜 */
    WAS_STATE_TI_BG_BOUNDARY_END                            ,

    /* MAIN 模块定时器 */
    WAS_STATE_TI_MAIN_BOUNDARY_START                        ,                   /* MAIN 定时器开始边界    */
    TI_WAS_MAIN_WAIT_USIM_RSP                               ,                   /* 等待USIM回复定时器 */
    TI_WAS_MAIN_WAIT_L2_RSP                                 ,
    TI_WAS_MAIN_WAIT_PHY_RSP                                ,
    TI_WAS_MAIN_WAIT_WCOMM_CNF                              ,
#if (FEATURE_ON == FEATURE_DSDS)
    TI_WAS_MAIN_WAIT_CONN_RES_APPLY_CNF                     ,                   /* 连接态下等待资源申请成功定时器, 统一5s */
    TI_WAS_MAIN_WAIT_GAS_RESEL_TIMER_EXP_CNF                ,                   /* 等待 GAS 回复 停止重选响应的定时器 */
#endif
    WAS_STATE_TI_MAIN_BOUNDARY_END                          ,                   /* MAIN 定时器结束边界    */

    /* COMM 模块定时器 */
    WAS_STATE_TI_COMM_BOUNDARY_START                        ,                   /* COMM 定时器开始边界    */
    WAS_STATE_TI_COMM_BOUNDARY_END                          ,                   /* COMM 定时器结束边界    */

    /* NASITF 模块定时器 */
    WAS_STATE_TI_NASITF_BOUNDARY_START                      ,                   /* NASITF 定时器开始边界  */
    WAS_STATE_TI_NASITF_BOUNDARY_END                        ,                   /* NASITF 定时器结束边界  */

    /* TAFITF 模块定时器 */
    WAS_STATE_TI_TAFITF_BOUNDARY_START                      ,                   /* TAFITF 定时器开始边界  */
    WAS_STATE_TI_TAFITF_BOUNDARY_END                        ,                   /* TAFITF 定时器结束边界  */

    /* PHYITF 模块定时器 */
    WAS_STATE_TI_PHYITF_BOUNDARY_START                      ,                   /* PHYITF 定时器开始边界  */
    TI_WAS_PHYITF_WRR_WAIT_PHY_CNF                          ,                   /* WRR PhyItf 等待物理层应答超时定时器*/
    WAS_STATE_TI_PHYITF_BOUNDARY_END                        ,                   /* PHYITF 定时器结束边界  */

    /* L2ITF 模块定时器 */
    WAS_STATE_TI_L2ITF_BOUNDARY_START                       ,                   /* L2ITF 定时器开始边界   */
    TI_WAS_L2ITF_WAIT_CNF                                   ,                   /* 等待L2应答超时处理 */
    WAS_STATE_TI_L2ITF_BOUNDARY_END                         ,                   /* L2ITF 定时器结束边界   */

    /* ASN1 模块定时器 */
    WAS_STATE_TI_ASN1_BOUNDARY_START                        ,                   /* ASN1 定时器开始边界    */
    WAS_STATE_TI_ASN1_BOUNDARY_END                          ,                   /* ASN1 定时器结束边界    */

    /* MNTN 模块定时器 */
    WAS_STATE_TI_MNTN_BOUNDARY_START                        ,                   /* MNTN 定时器开始边界    */
    WAS_STATE_TI_MNTN_BOUNDARY_END                          ,                   /* MNTN 定时器结束边界    */

    /* PFC 定时器 */
    WAS_STATE_TI_PFC_BOUNDARY_START                         ,                   /* PFC 定时器开始边界    */
    TI_WAS_PFC_WAIT_MEAS_CTRL_CNF                           ,                   /* 等待RM回复ID_WAS_RM_MEAS_CTRL_CNF定时器 */
    TI_WAS_PFC_WAIT_ASSIST_DATA_RSP                         ,                   /* 等待RM回复ID_WAS_RM_ASSIST_DATA_RSP定时器 */
    WAS_STATE_TI_PFC_BOUNDARY_END                           ,                   /* PFC 定时器结束边界    */

    WAS_STATE_TI_FSM_PROTECT_WRR                            ,                   /* WRR状态机吊死保护定时器 */
    WAS_STATE_TI_FSM_PROTECT_SIB                            ,                   /* SIB状态机吊死保护定时器 */
    WAS_STATE_TI_FSM_PROTECT_CSEL                           ,                   /* CSEL状态机吊死保护定时器 */
    WAS_STATE_TI_FSM_PROTECT_RM                             ,                   /* RM状态机吊死保护定时器 */
    WAS_STATE_TI_FSM_PROTECT_BG                             ,                   /* BG状态机吊死保护定时器 */
    TI_WAS_RRC_WAIT_NAS_SUSPEND_CNF                         ,                   /* 等待NAS回复SUSPEND RSP的定时器 */

    TI_WAS_SYSHO_WAIT_DLSYNC_CNF                            ,                   /* 等待DL SYNC CNF保护定时器 */

    TI_WAS_CSELPC_BG_WAIT_NAS_CNF                           ,                   /* BG过程中发起W2G重选 */

    TI_WAS_SYSHO_PCCO_WAIT_RRMM_EST_REQ                     ,                   /* G2W PCCO 等待NAS发送RRMM_EST_REQ保护定时器 */
    TI_WAS_CU_WAIT_NAS_SUSPEND_RSP                          ,                   /* 等待nas回复rrmm suspend rsp的定时器时长，10s */
    TI_WAS_CU_WAIT_NAS_RESUME_RSP                           ,                   /* 等待nas回复RRMM RESUME RSP消息的定时器 */
    TI_WAS_CSELPC_WAIT_NAS_SUSPEND_RSP                      ,                   /* cselpc等待nas回复RRMM SUSPEND RSP消息的定时器 */
    TI_WAS_CSELPC_WAIT_NAS_RESUME_RSP                       ,                   /* cselpc等待nas回复RRMM RESUME RSP消息的定时器 */
    TI_WAS_SYSHO_WAIT_NAS_SUSPEND_RSP                       ,                   /* 等待nas回复RRMM SUSPEND RSP消息的定时器 */

#if (FEATURE_ON == FEATURE_DSDS)
    TI_WAS_SYSHO_WAIT_RRM_RF_RES_APPLY_CNF                  ,                   /* 等待RRM回复资源申请CNF消息的定时器 */

    TI_WAS_CSELPC_WAIT_PLMN_ID_SRCH_RES_APPLY_CNF           ,                   /* 等待指定搜资源申请消息超时时长60s */
    TI_WAS_CSELPC_WAIT_PLMN_LIST_SRCH_RES_APPLY_CNF         ,                   /* 等待lIST搜资源申请消息超时时长5S */
    TI_WAS_CSELPC_WAIT_AS_SRCH_RES_APPLY_CNF                ,                   /* 等待AS类型资源申请超市时长10s */
    TI_WAS_CSELPC_WAIT_G_OR_L_RES_APPLY_CNF                 ,                   /* 异系统重选等待G或L的AS类型资源申请超时时长5s */
#endif
    TI_WAS_CSELPC_WAIT_GAS_RESEL_TIMER_EXP_CNF              ,                   /* 等待 GAS 回复 停止重选响应的定时器 */

    TI_WAS_SYSHO_WAIT_NAS_RESUME_RSP                        ,                   /* 等待nas回复RRMM RESUME RSP消息的定时器 */
    TI_WAS_RRC_WAIT_NAS_SUSPEND_RSP                         ,                   /* 等待nas回复rrmm suspend rsp的定时器时长，10s */
    TI_WAS_RRC_WAIT_NAS_RESUME_RSP                          ,                   /* 待nas回复RRMM RESUME RSP消息的定时器 */
    TI_WAS_CSELPC_OOS_REL_WAIT_NAS_MSG                      ,                   /* 连接态出服务区，收到nas的rel req消息后，rel all，结束状态机后的保护定时器 */
    TI_WAS_CSELPC_WAIT_NETSCAN_CNF                          ,                   /*  CSELPC等待csel搜网结果的定时器 */
    TI_WAS_CSEL_WAIT_GAS_MEAS_CNF                           ,                   /* CSEL IDLE/CONN态等待测量请求CNF消息定时器 */

    TI_WAS_MAIN_WAIT_BG_SEARCH_STOP_CNF                     ,
    TI_WAS_CSELPC_OOS_SBM_DUAL_IMSI                        ,                   /* CSELPC出服务区软银双imsi起的定时器60s */

    TI_WAS_CSEL_WAIT_CSS_PRE_FREQ_RSP                       ,                   /* CSEL等CSS模块从云端获取频点的RSP的定时器1100s */
    TI_WAS_CSEL_WAIT_CSS_PRE_BAND_RSP                       ,                   /* CSEL等CSS模块从云端获取pre band的RSP的定时器1100s */

    WAS_STATE_TI_BUTT
};
typedef VOS_UINT16 WAS_TI_ENUM_UINT16;

/*lint -e958 修改人: shiweizhou 检视人：陈功 原因简述：定时器消息，暂无法修改消息结构 */
typedef struct
{
   VOS_UINT8            ucType;
   VOS_UINT8            ucValid;
   VOS_UINT16           usRsv;
   WAS_TI_ENUM_UINT16   enName;
   VOS_UINT32           ulPara;
   VOS_UINT32           pNext;
   VOS_UINT32           pPrev;
   VOS_UINT8            aucData[24];
}WAS_TI_MSG_DATA;
/*_H2ASN_Length UINT32*/
/*lint +e958 修改人: shiweizhou 检视人：陈功 原因简述：定时器消息，暂无法修改消息结构 */

/*用于ASN.1解析头*/

typedef struct
{
    VOS_MSG_HEADER
    WAS_TI_MSG_DATA   stMsgData;
}WasTimer_MSG;




/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


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

#endif /* end of WasMntnMsg.h */
