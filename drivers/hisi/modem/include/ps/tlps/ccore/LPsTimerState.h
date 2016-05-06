/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : LPsTimerState.h
  Description     : LPsTimerState.h header file
  History         :
      1.liutao 38432       2011-5-14   Draft Enact
      2.lidui 143774       2012-4-25   DTS2012040905094:重配置和切换成功的时机理解与标杆不一致

******************************************************************************/

#ifndef __LPSTIMERSTATE_H__
#define __LPSTIMERSTATE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"


#pragma pack(4)

/*****************************************************************************
  2 Macro
*****************************************************************************/
#define TI_RRC_PTL_START                ( 0xD000 )


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : RRC_TIME_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 定时器的状态描述
*****************************************************************************/
enum RRC_TIME_STATUS_ENUM
{
    RRC_TIMER_DEBUG_STATUS_START,/*启动定时器*/
    RRC_TIMER_DEBUG_STATUS_STOP,/*定时器已经停止*/
    RRC_TIMER_DEBUG_STATUS_MODIFY,/*修改定时器*/
    RRC_TIMER_DEBUG_STATUS_EXPIRED /*定时器超时*/
};
typedef VOS_UINT32 RRC_TIMER_OPERATE_ENUM_UINT32;
/*****************************************************************************
 枚举名    : RRC_MS_ID_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 状态机主状态枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : RRC_PTL_TI_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 协议定时器和功能定时器 定义
             BOUNDARY_START，标识该模块定时器在定时器表中的起始下标;
             BOUNDARY_END，标识该模块定时器在定时器表中的结束下标;
             各个模块的定时器定义需要定义在各自响应的区间中.
*****************************************************************************/
enum RRC_PTL_TI_ENUM
{
    /* MAIN 模块定时器 */
    TI_RRC_PTL_MAIN_BOUNDARY_START = TI_RRC_PTL_START,       /* MAIN 定时器开始边界 */
    TI_RRC_PTL_T310,

    /* RRC 模块定时器 */
    TI_RRC_PTL_RRC_BOUNDARY_START,       /* RRC 定时器开始边界 */
    TI_RRC_PTL_T300,
    TI_RRC_PTL_T302,       /* 当是MT-CALL时,链接建立请求被限制时，启动此定时器 */
    TI_RRC_PTL_T303,       /* 当MO-CALL时、连接建立请求被限制时，启动此定时器 */
    TI_RRC_PTL_T305,       /* 当MO-SIGNALLING时、连接建立请求被限制时，启动此定时器 */
    /* v7r2 code begin */
    TI_RRC_PTL_T306,       /* 当MO-CSFB时、连接建立请求被限制时，启动此定时器 */
    /* v7r2 code end */

    /* V7R2 MDT BEGIN */
    TI_RRC_PTL_T330,       /* 收到logged MDT配置命令时，启动此定时器 */
    TI_RRC_PTL_T330_DELAY, /* T330超时后启动48小时定时器，启动此定时器 */
    TI_RRC_PTL_RLF_DELAY,  /* RLF记录后启动48小时定时器，启动此定时器 */
    /* V7R2 MDT END */

    TI_RRC_RRC_WAIT_SIB_MP,       /* 等待SIB更新的边界到来定时器 */
    TI_RRC_RRC_CONN_REL_DELAY,        /* 收到UU的RRC CONN RELEASE消息后，启动60ms延迟定时器 */

    /* REEST 模块定时器 */
    TI_RRC_PTL_REEST_BOUNDARY_START,       /* REEST 定时器开始边界 */
    TI_RRC_PTL_REEST_T311,       /* 等待RRC连接重建T311定时器 */
    TI_RRC_PTL_REEST_T301,       /* 等待RRC连接重建T301定时器 */

    /* RB 模块定时器 */
    TI_RRC_PTL_RB_BOUNDARY_START,       /* RB 定时器开始边界 */
    TI_RRC_PTL_T304,

    /* CSELPC 模块定时器 */
    TI_RRC_PTL_CSELPC_BOUNDARY_START,       /* CSEL 定时器开始边界 */

    /* CSEL 模块定时器 */
    TI_RRC_PTL_CSEL_BOUNDARY_START,       /* CSEL 定时器开始边界 */
    TI_RRC_PTL_BSIC_VERIFY,                 /* BSIC验证结果有效性定时器 */
    TI_RRC_PTL_CSEL_SUITABLE_CELL_DETECT,       /* CSEL 模块Suitable Cell周期检测定时器 */
    TI_RRC_PTL_LOSTCOVERAGE,                /* 出服务区定时器 */
    TI_RRC_PTL_CAMPSTICK,                   /* 1s 驻留定时器 */
    TI_RRC_PTL_T320,                        /* 使用专有优先级的定时器 */
    TI_RRC_PTL_IDLE_NORMALHYST,             /* 移动性检测定时器  THystNormal */
    TI_RRC_PTL_RESELECTION,                 /* 重选定时器 */
    TI_RRC_PTL_TBARRED,                     /* bar定时器 */
    TI_RRC_PTL_TFORBIDDEN,                  /* forbiden定时器 */
    TI_RRC_PTL_GERAN_TBARRED,               /* G模bar定时器 */
    TI_RRC_PTL_GERAN_TFORBIDDEN,            /* G模forbiden定时器 */
    TI_RRC_PTL_UTRAN_TBARRED,               /* U模bar定时器 */
    TI_RRC_PTL_UTRAN_TFORBIDDEN,            /* U模forbiden定时器 */
    TI_RRC_PTL_G2L_RESEL_PUNISH,        /* G->L重选惩罚定时器 */
    TI_RRC_PTL_W2L_REDIR_PUNISH,        /* W->L重定向惩罚定时器 */
    /* MBMS Begin */
    TI_RRC_PTL_MBMS_MCCH_NOTIFY,        /* MCCH msg变化后，启动的最小定时器 */
    /* MBMS End */

    /* CMM 模块定时器 */
    TI_RRC_PTL_RM_BOUNDARY_START,       /* CMM 定时器开始边界 */
    TI_RRC_CMM_NC_EVT_TRIG,
    TI_RRC_CMM_SC_EVT_TRIG,
    TI_RRC_CMM_MOBILITY_NORMALHYST,
    TI_RRC_CMM_PERIOD_RPT,
    TI_RRC_PTL_T321,                    /* CGI上报定时器 */

    /* SIB 模块定时器 */
    TI_RRC_PTL_SIB_BOUNDARY_START,       /* CMM 定时器开始边界 */
    TI_RRC_PTL_SIB_3HOUR_UPDATE,       /* 3小时更新定时器 */

    TI_RRC_PAGING_VALID_TIMER,  /* PAGING连接态业务寻呼收到后，该定时器启动期间，如果再次收到业务寻呼，进行丢弃 */
    /* ITF 模块定时器 */

    /* ASN1 模块定时器 */
    TI_RRC_PTL_ASN1_BOUNDARY_START,       /* ASN1 定时器开始边界 */

    /* MNTN 模块定时器 */
    TI_RRC_PTL_MNTN_BOUNDARY_START,       /* MNTN 定时器开始边界 */

    /* gaojishan-fast-dorm-cfg-3 */
    TI_FAST_DORM_CFG_DELAY,               /* fast dorm定时器开始边界 */

    /* CMCC-BEGIN */
    TI_IRAT_REDIR_SEARCH_TIMER,           /* 异系统重定向搜网控制定时器 */
    /* CMCC-END */
//#if(FEATURE_MULTI_MODEM == FEATURE_ON)
    /* LRRC MTC AREA LOST Begin */
    TI_MTC_AREA_LOST_TIMER,           /* mtc area lost 控制定时器 */
    /* LRRC MTC AREA LOST End */

    /* LTE PS Transfer begin */
    TI_MTCLOST_PS_TRANSFER_TIMER,     /* LTE->CDMA离网重选定时器 */
    TI_MTCAVAILABLE_PS_TRANSFER_TIMER,     /* CDMA->LTE离网重选定时器 */
    /* LTE PS Transfer end */
//#endif

    /* DSDS-BEGIN */
    TI_RRC_DSDS_REL_PS_PAGING_TIMER,      /* 释放dsds的ps paging type的资源的定时器 */
    TI_RRC_DSDS_NORF_LOST_COVERAGE,       /* lphy的idle meas ind没有dsds的资源时，走丢网的定时器 */
    TI_RRC_DSDS_SHORT_OCCUPY_RF_RECOVER,  /* lte的连接态，资源被短抢后，恢复RF资源的最晚时间，如果超时，就要释放了 */
    TI_RRC_DSDS_DELAY_REL_REDIR_RF_RESOURCE_TIME,                   /* 1s 驻留定时器 */
    TI_RRC_DSDS_OCCUPY_PROTECT_TIMER,     /*收到非紧急抢的保护定时器，防止状态问题，导致一直不回复抢占成功*/
    /* DSDS-END */
    TI_RRC_PTL_T325,
    TI_RRC_PTL_PWRPREF_IND_TIME,
    TI_RRC_DAM_CELL_BAR_TIMER,    /* DAM功能中bar小区定时器 */

    TI_RRC_PRINT_BUFFER_TIMER,
    TI_RRC_CSFB_OPTIMIZE_PROTECT_TIMER,

    TI_RRC_CHR_PUSH_NOTIFY_TIMER,   /* 8小时推送消息 */

    TI_RRC_CSG_CELL_BAR_TIMER,

    /* begin: add by f00295098,DTS2015112703260 DSDS时系统消息更新失败定时器 */
    TI_RRC_PTL_SIB_DSDS_UPDATE,
    /* end: add by f00295098,DTS2015112703260 DSDS时系统消息更新失败定时器 */

    TI_RRC_PTL_BUTT
};
typedef VOS_UINT16 RRC_PTL_TI_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RRC_STATE_TI_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 状态保护定时器定义
             BOUNDARY_START，标识该模块定时器在定时器表中的起始下标;
             BOUNDARY_END，标识该模块定时器在定时器表中的结束下标;
             各个模块的定时器定义需要定义在各自响应的区间中.
*****************************************************************************/
enum RRC_STATE_TI_ENUM
{
    /* MAIN 模块定时器 */
    TI_RRC_STATE_MAIN_BOUNDARY_START = (TI_RRC_PTL_START + 0x100),    /* MAIN 定时器开始边界 */

    /* RRC 模块定时器 */
    TI_RRC_STATE_RRC_BOUNDARY_START,    /* RRC 定时器开始边界 */

    TI_RRC_CSELPC_CELL_RESEL_STOP_CNF,    /* 等待CSLPC控制小区重选停止响应的定时器 */
    TI_RRC_CSELPC_CELL_RESEL_START_CNF,    /* 等待CSLPC控制小区重选启动响应的定时器 */
    TI_RRC_RRC_WAIT_ITFL2_CFG_CNF,    /* 等待ITFL2配置响应的定时器 */
    TI_RRC_RRC_WAIT_ITFL2_REL_CNF,    /* 等待ITFL2释放响应的定时器 */
    TI_RRC_RRC_WAIT_ITFPHY_CFG_CNF,    /* 等待ITFPHY配置响应的定时器 */
    TI_RRC_RRC_WAIT_ITFPHY_REL_CNF,    /* 等待ITFPHY释放响应的定时器 */
    TI_RRC_RRC_WAIT_MAC_RA_CNF,    /* 等待MAC随机接入响应的定时器 */
    TI_RRC_RRC_WAIT_DATA_CNF,    /* 等待PDCP的DATA发送响应的定时器 */
    TI_RRC_RRC_CSELPC_STATE_CHANGE_CNF,    /* 等待CSELPC处理的状态变迁响应的定时器 */
    TI_RRC_RRC_CMM_STATE_CHANGE_CNF,    /* 等待CMM处理的状态变迁响应的定时器 */
    TI_RRC_RRC_WAIT_DATA_CNF_OF_UL_TRANS,    /* 等待上行直传消息的层2发送响应的保护定时器 */
    TI_RRC_RRC_WAIT_RRC_CONN_EST_OR_REJECT,    /* 等待空口RRC连接建立或拒绝 */
    TI_LRRC_LRRC_SS_WAIT_ITFL2_RESET_L2_CNF,   /* 等待ITFL2复位MAC、STOP PDCP、REEST RLC的响应定时器 */
    TI_LRRC_LRRC_WAIT_GURRC_UE_CAP_CNF,   /* 等待获取GURRC UE能力信息的定时器 */
    TI_LRRC_LRRC_WAIT_LPHY_SET_WORK_MODE_CNF,   /* 等待PHY模式切换的响应定时器 */
    TI_LRRC_LRRC_WAIT_LCSELPC_CELL_SEARCH_CNF,   /* 等待LCSELPC小区搜索的响应定时器 */
    TI_LRRC_LRRC_WAIT_LMM_RESUME_RSP,   /* 等待LMM解挂响应定时器 */
    TI_LRRC_LRRC_WAIT_LMM_SUSPEND_RSP,   /* 等待LMM挂起响应定时器 */
    TI_LRRC_LRRC_WAIT_GURRC_CNF,        /* 等待GU RRC重定向/重选/切换/CCO响应的定时器 */
    TI_LRRC_LRRC_WAIT_LOAD_WDSP_CNF,   /* 等待WRRC加载WDSP响应的定时器 */
    TI_LRRC_LRRC_WAIT_GURRC_STOP_CNF,  /* 等待GU RRC停止重定向/重选/切换/CCO响应的定时器 */
    TI_LRRC_LRRC_WAIT_GURRC_REL_ALL_CNF,  /* 等待GURRC REL ALL响应的定时器 */
    /* TDS begin */
    TI_LRRC_LRRC_WAIT_TRRC_UE_CAP_CNF,   /* 等待获取TRRC UE能力信息的定时器 */
    TI_LRRC_LRRC_WAIT_TRRC_CNF,        /* 等待TRRC重定向/重选/切换/CCO响应的定时器 */
    TI_LRRC_LRRC_WAIT_TRRC_STOP_CNF,  /* 等待TRRC停止重定向/重选/切换/CCO响应的定时器 */
    TI_LRRC_LRRC_WAIT_TRRC_REL_ALL_CNF,  /* 等待TRRC REL ALL响应的定时器 */
    /* TDS end */

    /* REEST 模块定时器 */
    TI_RRC_STATE_REEST_BOUNDARY_START,     /* REEST 定时器开始边界 */
    TI_RRC_REEST_WAIT_NAS_SUSPEND_RABM_RSP,     /* 等待NAS停止数传响应定时器 */
    TI_RRC_REEST_WAIT_CMM_STATE_CHANGE_CNF,     /* 等待CMM状态改变响应定时器 */
    TI_RRC_REEST_WAIT_ITFL2_CONFIG_L2_CNF,     /* 等待配置L2响应定时器 */
    TI_RRC_REEST_WAIT_ITFPHY_CONFIG_PHY_CNF,     /* 等待配置PHY响应定时器 */
    TI_LRRC_LREEST_WAIT_GURRC_REL_ALL_CNF,  /* 等待GURRC REL ALL响应的定时器 */
    /* TDS begin */
    TI_LRRC_LREEST_WAIT_TRRC_REL_ALL_CNF,   /* 等待TRRC REL ALL响应的定时器 */
    /* TDS end */
    TI_RRC_REEST_WAIT_CSELPC_STATE_CHANGE_CNF,     /* 等待CSELPC状态改变定时器 */
    TI_RRC_REEST_WAIT_MAC_RA_CNF,     /* 等待MAC随机接入响应定时器 */
    TI_RRC_REEST_WAIT_PDCP_DATA_CNF,     /* 等待PDCP发送空口数据响应定时器 */
    TI_RRC_REEST_CONN_REEST_T301,     /* 等待RRC连接重建重发T301定时器 */
    TI_RRC_REEST_WAIT_RRC_CONN_REEST_OR_REJECT,     /* 等待空口RRC连接重建或拒绝 */
    TI_RRC_REEST_WAIT_SMC_SECU_CONFIG_CNF,     /* 等待安全配置响应 */
    TI_RRC_REEST_WAIT_DSDS_RADIO_RESOURCE_CNF,

    /* RB 模块定时器 */
    TI_RRC_STATE_TI_RB_BOUNDARY_START,     /* RB 定时器开始边界 */
    TI_RRC_RB_WAIT_RABM_STATUS_RSP,     /* 有切换消息时，向NAS发送挂起请求后，等待挂起NAS响应超时 */
    TI_RRC_RB_WAIT_CMM_HO_CNF,     /* 有切换消息时，向CMM发送切换开始后，等待CMM响应超时 */
    TI_RRC_RB_WAIT_ITFPHY_CFG_CNF,     /* 有切换消息时，向PHY发送切换开始后，等待PHY响应超时 */
    TI_RRC_RB_WAIT_PHY_SYNC_CNF,     /* 有切换消息时，等待PHY同步CNF超时 */
    TI_RRC_RB_WAIT_ITFL2_CFG_CNF,     /* 有切换消息时，发送L2配置超时*/
    TI_RRC_RB_WAIT_SMC_SECU_CFG_CNF,     /* 有切换消息时，向SMC发送安全激活配置请求定时器超时 */
    TI_RRC_RB_WAIT_RABM_STATUS_CNF,     /* 有切换消息时，向NAS发送解除挂起请求后，等待NAS响应超时 */
    TI_RRC_RB_WAIT_CMM_MEAS_CTRL_CNF,     /* 无HO和RB消息时，RRC CONNECTION RECONFIGURATION消息中含有measurement消息的处理超时 */
    TI_RRC_RB_WAIT_PDCP_DATA_CNF,     /* 发送AM数据后，等待PDCP响应定时器超时 */
    TI_RRC_RB_WAIT_REL_NEW_RB_CNF,     /* 释放RB后，等待L2响应定时器超时 */
    TI_LRRC_LRB_WAIT_LPHY_SET_WORK_MODE_CNF,   /* 等待PHY模式切换的响应定时器 */
    TI_LRRC_LRB_WAIT_MM_SECU_PARA_RSP,           /* 等待LNAS安全参数的响应定时器 */
    TI_LRRC_LRB_WAIT_MM_RESUME_RSP,           /* 等待LNAS解挂的响应定时器 */
    TI_LRRC_LRB_WAIT_GURRC_REL_ALL_CNF,  /* 等待GURRC REL ALL响应的定时器 */

    /* CSELPC 模块定时器  */
    TI_RRC_STATE_CSELPC_BOUNDARY_START,     /* CSELPC 定时器开始边界 */
    TI_RRC_CSELPC_WAIT_CONFIG_PHY_CNF,     /* 等待物理层配置响应的定时器 */
    TI_RRC_CSELPC_WAIT_PHY_CAMPED_CELL_CNF,     /* 等待物理层驻留响应的定时器 */
    TI_RRC_CSELPC_WAIT_CONFIG_L2_CNF,
    TI_RRC_CSELPC_WAIT_CSEL_SPEC_PLMN_SEARCH_CNF,     /* 等待csel模块SPEC PLMN搜索响应的定时器 */
    TI_RRC_CSELPC_WAIT_CSEL_PLMN_LIST_SEARCH_CNF,     /* 等待CSEL PLMN LIST搜索响应的定时器 */
    TI_RRC_CSELPC_WAIT_CSEL_STOP_PLMN_LIST_CNF,     /* 等待CSEL停止PLMN LIST响应的定时器 */

    TI_RRC_CSELPC_WAIT_CSEL_CELL_SEARCH_CNF,     /* 等待csel模块搜索响应的定时器 */

    TI_RRC_CSELPC_WAIT_CELL_RESEL_STOP_REQ,     /* 等待RRC/REEST小区重选停止请求的定时器 */
    TI_RRC_CSELPC_WAIT_CELL_RESEL_START_REQ,     /* 等待RRC/REEST小区重选开始请求的定时器 */

    TI_RRC_CSELPC_WAIT_CSEL_RESEL_START_CNF,     /* 等待CSEL小区重选开始响应的定时器 */
    TI_RRC_CSELPC_WAIT_CSEL_RESEL_STOP_CNF,     /* 等待CSEL小区重选停止响应的定时器 */

    TI_RRC_CSELPC_WAIT_STATE_CHANGE_REQ,     /* 等待RRC/REEST状态切换请求的定时器 */
    TI_RRC_CSELPC_WAIT_CSEL_STATE_CHANGE_CNF,     /* 等待CSEL状态切换响应的定时器 */
    TI_RRC_CSELPC_WAIT_SIB_UPDATE_SYSINFO_CNF,     /* 等待SIB更新系统信息响应的定时器 */
    TI_RRC_CSELPC_WAIT_SIB_REL_CNF,                 /* 等待SIB释放的定时器 */
    TI_RRC_CSELPC_WAIT_CSEL_SYS_INFO_CHANGE_CNF,     /* 等待CSEL系统消息改变响应的定时器*/
    TI_RRC_CSELPC_WAIT_CMM_SYSINFO_CHANGE_CNF,     /* 等待CMM系统消息改变响应的定时器*/
    TI_LRRC_LCSELPC_WAIT_LPHY_SET_WORK_MODE_CNF,   /* 等待PHY模式切换的响应定时器 */

    /* MBMS Begin */
    TI_LRRC_LCSELPC_SS_WAIT_MBMS_FLOW_CMP,
    TI_LRRC_LCSELPC_SS_WAIT_MBMS_MCCH_CFG_CNF,
    TI_LRRC_LCSELPC_SS_WAIT_MBMS_MCCH_MSG_IND,
    TI_LRRC_LCSELPC_SS_WAIT_MBMS_MCCH_RECFG_CNF,
    TI_LRRC_LCSELPC_SS_WAIT_MBMS_L2_CFG_CNF,
    TI_LRRC_LCSELPC_SS_WAIT_MBMS_PHY_CFG_CNF,
    TI_LRRC_LCSELPC_SS_WAIT_MBMS_L2_REL_CNF,
    TI_LRRC_LCSELPC_SS_WAIT_MBMS_PHY_REL_CNF,

     /* MBMS end */


    /* SMC 模块定时器 */
    TI_RRC_STATE_SMC_BOUNDARY_START,        /* SMC 定时器开始边界 */
    TI_RRC_SMC_WAIT_CNF,                    /* PDCP配置保护定时器 */

    /* CSEL 模块定时器 */
    TI_RRC_STATE_CSEL_BOUNDARY_START,     /* CSEL 定时器开始边界 */
    TI_RRC_CSEL_WAIT_PHY_IND,     /* CSEL模块等待PHY回复小区搜索结果的保护定时器 */
    TI_RRC_CSEL_WAIT_PHY_CNF,      /* CSEL模块等待phy的测量建立cnf */
    TI_RRC_CSEL_WAIT_SIB_CNF,     /* CSEL模块等待SIB回复系统消息接收保护定时器 */
    TI_RRC_CSEL_WAIT_GU_MEAS_CNF, /* 等待配置GU模测量回复消息保护定时器 */
    /* TDS begin */
    TI_RRC_CSEL_WAIT_TDS_MEAS_CNF, /* 等待配置TDS模测量回复消息保护定时器 */
    /* TDS end */
    TI_LRRC_LCSEL_WAIT_WRRC_BSIC_VERIFY_CNF,   /* 等待WRRC BSIC验证响应的保护定时器 */
    TI_LRRC_LCSEL_WAIT_LPHY_BSIC_VERIFY_CNF,   /* 等待物理层 BSIC验证响应的保护定时器 */

    /* bgs begin */
    TI_LRRC_LCSELPC_WAIT_LCSELBG_CNF,   /* LCSELPC等待GURRC背景搜CNF的保护定时器 */
    TI_LRRC_LCSEL_WAIT_LCSELPC_CNF,   /* LCSEL等待LCSELPC背景搜CNF的保护定时器 */
    TI_LRRC_LCSELBG_WAIT_GURRC_CNF,   /* 等待GURRC背景搜CNF的保护定时器 */
    TI_LRRC_LCSELBG_WAIT_GURRC_IND,   /* 等待GURRC背景搜IND的保护定时器 */
    /* bgs end */
    TI_RRC_CSEL_WAIT_RSSI_SORT_IND,   /*等待物理层频点排序消息*/
    TI_RRC_CSEL_WAIT_BGSRESEL_PREWORK_IND,   /*等待背景搜重选方式PREWORK*/
    TI_RRC_CSEL_WAIT_BGSRESEL_SIBACQIRE_CNF,   /*等待背景搜重选方式超时*/

    /* SIB模块定时器 */
    TI_RRC_SIB_WAIT_RL_SETUP_CNF,     /* 物理信道建立定时器 */
    TI_RRC_SIB_WAIT_MIB_IND,     /* MIB接收保护定时器 */
    TI_RRC_SIB_WAIT_RL_REL_CNF,     /* 物理信道释放定时器 */
    TI_RRC_SIB_WAIT_SIB1_IND,     /* SIB1接收保护定时器 */
    TI_RRC_SIB_WAIT_PHY_CNF,      /* SI 配置保护定时器 */
    TI_RRC_SIB_WAIT_SIB_IND,     /* SIBn接收保护定时器 */

    /* CMM 模块定时器 */
    TI_RRC_STATE_CMM_BOUNDARY_START,     /* CMM 定时器开始边界 */
    TI_RRC_CMM_WAIT_PHY_CNF,     /* 物理层配置保护定时器 */
    TI_LRRC_LCMM_WAIT_WRRC_BSIC_VERIFY_CNF,   /* 等待WRRC BSIC验证响应的保护定时器 */
    TI_LRRC_LCMM_WAIT_LPHY_BSIC_VERIFY_CNF,   /* 等待物理层 BSIC验证响应的保护定时器 */
    TI_RRC_CMM_WAIT_GU_MEAS_CNF, /* 等待配置GU模测量回复消息保护定时器 */
    /* TDS begin */
    TI_RRC_CMM_WAIT_UTRA_TDD_MEAS_CNF, /* 等待配置TDS模测量回复消息保护定时器 */
    /* TDS end */

    /* ITF 模块定时器 */
    TI_RRC_ITF_WAIT_CNF,

    /* ASN1 模块定时器 */
    TI_RRC_STATE_ASN1_BOUNDARY_START,     /* ASN1 定时器开始边界 */

    /* MNTN 模块定时器 */

    /* 其它 定时器 */
    TI_RRC_STATE_FSM_PROTECT_ERRC,     /* ERRC状态机吊死保护定时器 */
    TI_RRC_STATE_FSM_PROTECT_CSEL,     /* CSEL状态机吊死保护定时器 */
    TI_RRC_STATE_FSM_PROTECT_CMM,     /* CMM状态机吊死保护定时器 */
    TI_RRC_STATE_FSM_PROTECT_SIB,     /* SIB状态机吊死保护定时器 */
    /* bgs begin */
    TI_RRC_STATE_FSM_PROTECT_CSELBG,  /* CSELBG状态机吊死保护定时器 */
    TI_LRRC_LCSELBG_PROTECT_SLAVE_SUSPEND,   /* L从模状态下挂起态保护定时器 xrm todo */
    /* bgs end */

    TI_RRC_APP_RSSI_REPORT,           /* RSSI周期上报定时器 */
    TI_LRRC_LRRC_WAIT_CDMA_CNF,
    TI_LRRC_LRRC_WAIT_CDMA_STOP_CNF,

    /* DSDS BEGIN */
	TI_LRRC_WAIT_RRM_RADIO_RESOURCE_CNF,
	/* DSDS END */

    TI_RRC_PTL_CONNESTFAIL_DELAY,  /* connestfail记录后启动48小时定时器，启动此定时器 */
    TI_LRRC_LRRC_WAIT_CONN_TO_IDLE_CNF,
    TI_RRC_CSELPC_WAIT_CONN_TO_IDLE_REQ,

    TI_LRRC_LRRC_WAIT_CAS_REL_ALL_CNF,
    TI_LRRC_LRRC_WAIT_CAS_RESEL_CNF,
    TI_LRRC_LRRC_WAIT_CAS_REDIRECT_CNF,
    TI_RRC_CSEL_WAIT_CDMA_HRPD_MEAS_CNF,    /* 等待配置CDMA HRPD测量回复消息保护定时器 */
    TI_RRC_CMM_WAIT_HRPD_MEAS_CNF,

    TI_LRRC_LCSELPC_SS_WAIT_MBMS_PHY_ENABLE_CNF,
    TI_LRRC_LCSELPC_SS_WAIT_MBMS_PHY_DISABLE_CNF,
    TI_LRRC_LCSELPC_SS_WAIT_MBMS_NOTIFY_CFG_CNF,
    TI_LRRC_LCSELPC_SS_WAIT_MBMS_PMCH_CFG_CNF,
    TI_LRRC_LCSELPC_SS_WAIT_MBMS_PMCH_ACTIVE_CNF,

    TI_LRRC_LCMM_WAIT_LPP_LPHY_OTDOA_CNF,
    TI_LRRC_LRRC_WAIT_LPP_LCMM_OTDOA_CNF,

    /* begin: add for Austin搜网优化 PhaseII , l00277963*/
    TI_RRC_CSEL_WAIT_CSS_CURR_GEO_RSP,/*CSEL模块等待CSS获取国家频点频段保护定时器*/
    /* end: add for Austin搜网优化 PhaseII , l00277963*/

    TI_RRC_STATE_BUTT
};
typedef VOS_UINT16 RRC_STATE_TI_ENUM_UINT16;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/


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










#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of LPsTimerState.h */
