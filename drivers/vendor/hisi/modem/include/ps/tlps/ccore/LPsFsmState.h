/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : LPsFsmState.h
  Description     : LPsCommFsmState.h header file
  History         :
      1.liutao 38432       2011-5-14   Draft Enact
      2.lidui 143774       2012-4-25   DTS2012040905094:重配置和切换成功的时机理解与标杆不一致
******************************************************************************/

#ifndef __LPSFSMSTATE_H__
#define __LPSFSMSTATE_H__

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


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : RRC_MS_ID_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 状态机主状态枚举定义
*****************************************************************************/
enum ERRC_MS_ID_ENUM
{
    /* ERRC PID状态机主状态 */
    RRC_ERRC_MS_IDLE = 0,

    /* RRC模块的主状态 */
    RRC_RRC_MS_CONN_REQ,                                   /* 发送链接建立请求的主状态 */
    RRC_RRC_MS_CONN_SETUP,                                   /* 等待链接建立、或拒绝的主状态 */
    RRC_RRC_MS_UE_CAPA_ENQUIRY,                                   /* 网络发起UE能力查询的主状态 */
    RRC_RRC_MS_CONN_REL,                                   /* 发起释放过程的主状态:nas发起的，enodeb发起的，release all的 */
    RRC_RRC_MS_POWER_OFF,                                   /* 关机命令的主状态 */
    RRC_RRC_MS_POWER_ON,                                   /* 开机命令的主状态 */
    LRRC_LRRC_MS_SUSPEND_REQ,                            /* 收到LNAS挂起请求的主状态 */
    RRC_RRC_MS_PUCCH_SRS_REL_IND,                          /* CONNECTED态下MAC上报PUCCH/SRS释放的主状态 */
    LRRC_LRRC_MS_RL_FAIL,                                  /* 无线链路失败的主状态 */
    RRC_RRC_MS_UE_INFO_REQ,                            /* UE INFORMATION REQ主状态 */
    LRRC_LRRC_MS_GU2L_IRAT_MOBILITY,                    /* GU->L重选/GU->L重定向/G->L CCO主状态 */
    LRRC_LRRC_MS_L2GU_IRAT_MOBILITY,                    /* L->GU重选/L->GU重定向/L->G CCO主状态 */


    /* END of RRC模块的主状态 */

    /* RB模块的主状态 */
    LRRC_LRB_MS_GU2L_HO,                            /* GU->L切换的主状态 */
    RRC_RB_MS_HO,                                   /* 重配置消息中存在移动性管理配置消息时的主状态 */
    RRC_RB_MS_RBCFG,                                   /* 重配置消息中仅仅存在无线资源配置消息时的主状态 */
    RRC_RB_MS_RECFG,                                   /* 重配置消息中不存在移动性管理和无线资源配置信息的主状态 */
    /* END of RB模块的主状态 */

    /* REEST模块的主状态 */
    RRC_REEST_MS_CONN_REEST_REQ,                                   /* 发送RRC CONNECTION REESTABLISHMENT REQUEST主状态 */
    RRC_REEST_MS_CONN_REEST,                                   /* 接收RRC CONNECTION REESTABLISHMENT主状态 */

    /* END of REEST模块的主状态 */

    /* CSELPC模块的主状态 */
    RRC_CSELPC_MS_SPEC_PLMN_SEARCH,                                   /* 指定PLMN搜索的主状态 */
    RRC_CSELPC_MS_ANY_CELL_SEARCH,                                   /* ANY CELL搜索的主状态 */
    RRC_CSELPC_MS_SUIT_CELL_SEARCH,                                   /* SUITABLE CELL搜索的主状态 */
    RRC_CSELPC_MS_PLMN_LIST_SEARCH,                                   /* PLMN LIST搜索的主状态 */
    RRC_CSELPC_MS_RRC_CELL_RESEL_STOP,                                   /* 传递小区重选停止命令的主状态 */
    RRC_CSELPC_MS_RRC_CELL_RESEL_START,                                   /* 传递小区重选启动命令的主状态 */
    RRC_CSELPC_MS_REEST_CELL_RESEL_STOP,                                   /* 传递小区重选停止命令的主状态 */
    RRC_CSELPC_MS_REEST_CELL_RESEL_START,                                   /* 传递小区重选启动命令的主状态 */
    RRC_CSELPC_MS_RRC_STATE_CHANGE,                                   /* RRC发送的状态变迁命令的主状态 */
    RRC_CSELPC_MS_REEST_STATE_CHANGE,                                   /* REEST发送的状态变迁命令的主状态 */
    RRC_CSELPC_MS_SYS_INFO_UPDATE_IDLE,                                   /* 控制系统消息更新的主状态 */
    RRC_CSELPC_MS_SYS_INFO_UPDATE_CONNECT,
    RRC_CSELPC_MS_HANDOVER_SYS_INFO_UPDATE,                                   /* 切换完成后，通知cselpc进行系统消息更新 */
    RRC_CSELPC_MS_CELL_RESEL_IND,                                   /* CSEL发送过来重选指示 */
    RRC_CSELPC_MS_COVERAGE_AREA_LOST,                                   /* CSEL发送过来重选指示 */
    RRC_CSELPC_MS_STOP_SYS_UPDATE_CONNECT,                                   /* CSELPC停止系统消息更新的主状态 */
    /* MBMS Begin */
    RRC_CSELPC_MS_MBMS_COMM_FLOW,                               /* MBMS的公共流程 */
     RRC_CSELPC_MS_MODE_NTF,                                 /*收到LMM发送的NTF消息的主状态 */
    /* MBMS end */
    /* bgs begin */
    LRRC_LCSELPC_MS_BGS_CTRL,                                                   /* CSELPC背景搜控制的主状态 */
    /* bgs end */

    RRC_CSELPC_MS_MBMS_CONN_TO_IDLE,                              /* 存在MBMS业务，空口主动发起REL流程，UE为了保证MBMS连续性，发起直接驻留 */
    /* END of CSELPC模块的主状态 */

    /* SMC 模块的主状态 */
    RRC_SMC_MS_ACTIVE,                                                          /* 收到eNB的安全模式激活命令 */
    RRC_SMC_MS_CONN,                                                            /* 收到RB或者REEST发来的要求重新配置L2 */
    RRC_SMC_MS_CNT_CHK,
    /* END of SMC 模块的主状态 */

    /* ITF模块的主状态 */
    RRC_ITF_MS_WAIT_CNF,

    /* END OF ITF模块的主状态 */

    /* bgs begin */
    /* CSELBG模块的主状态 */
    LRRC_LCSELBG_MS_IDLE,
    LRRC_LCSELBG_MS_RUN_BGS,
    LRRC_LCSELBG_MS_SUSPEND_BGS,
    LRRC_LCSELBG_MS_RESUME_BGS,
    LRRC_LCSELBG_MS_STOP_BGS,
    /* END of CSELBG模块的主状态 */
    /* bgs end */

    /* CSEL模块的主状态 */
    RRC_CSEL_MS_IDLE,
    RRC_CSEL_MS_CELL_SEARCH,    /* 小区搜索主状态 */
    RRC_CSEL_MS_PLMN_LIST_SEARCH,    /* PLMN List搜索主状态 */
    RRC_CSEL_MS_PLMN_LIST_SEARCH_STOP,    /* 停止PLMN List搜索主状态 */
    RRC_CSEL_MS_RUN_RESEL                   ,    /* 正在进行小区重选 */
    RRC_CSEL_MS_STOP_RESEL                  ,    /* 正在停止小区重选 */
    RRC_CSEL_MS_DONE_RESEL                  ,    /* 小区重选已经拥有结果,正在结束 */

    LRRC_LCSEL_MS_IRAT_MEAS_IN_IDLE,      /* L从模时配置测量状态 */
    /* END of CSEL模块的主状态 */

    /* CMM模块的主状态 */
    RRC_CMM_MS_IDLE,
    RRC_CMM_MS_MEAS_CTRL,
    LRRC_LCMM_MS_IRAT_MEAS_IN_CONN,
    LRRC_LCMM_MS_BSIC_VERIFY,         /* 连接态BSIC验证主状态 */
     LRRC_LCMM_MS_MODE_NTF,                                 /*收到LMM发送的NTF消息的主状态 */
    /* END of CMM模块的主状态 */

    /* SIB模块的主状态 */
    RRC_SIB_MS_IDLE,
    RRC_SIB_MS_GET_SEARCH_INFO,   /* PLMN搜索下的主状态 */
    RRC_SIB_MS_GET_NEW_SI,   /* 获取新的系统消息的主状态 */
    RRC_SIB_MS_UPDATE_SI,   /* 更新系统消息的主状态 */
    RRC_SIB_MS_CSEL_STOP,   /* CSEL通知停止的主状态 */
    RRC_SIB_MS_CSELPC_STOP,   /* CSELPC通知停止的主状态 */
    /* END of SIB模块的主状态 */

    RRC_RRC_MS_MBMS_CONN_TO_IDLE,                              /* 存在MBMS业务，空口主动发起REL流程，UE为了保证MBMS连续性，发起直接驻留 */
    RRC_CSELPC_MS_MBMS_ENABLE_WITH_MCCH_FLOW,                     /*在IDLE态或连接态但没有更新系统信息，MBMS相关SI有效时，使用该流程*/
    RRC_CSELPC_MS_MBMS_DISABLE_FLOW,                              /* 去使能MBMS功能状态机 */
    RRC_CSELPC_MS_MBMS_SERVICE_STATE_SET_FLOW,                    /*服务状态设置流程，激活或去激活流程使用*/
    RRC_CSELPC_MS_MBMS_NOTIFY_IND_FLOW,                           /* 处理收到LPHY的NOTIFY IND配置流程 */

    LRRC_LCMM_MS_LPP_OTDOA_MEAS_FLOW,
    LRRC_LRRC_MS_LPP_OTDOA_MEAS_FLOW,

    /* 状态机预处状态，主要用于不进状态机的消息的处理 */
    RRC_MS_PRE_PROCESS,

    RRC_MS_ID_BUTT
};
typedef VOS_UINT16 RRC_MS_ID_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RRC_SS_ID_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 状态机子状态枚举定义
*****************************************************************************/
enum RRC_SS_ID_ENUM
{
    /* ERRC PID状态机子状态 */
    RRC_ERRC_SS_IDLE = 0,

    /* RRC模块的子状态 */
    RRC_RRC_SS_WAIT_ITFL2_CFG_CNF,                            /* 配置层2，等待ITFL2响应的子状态 */
    RRC_RRC_SS_WAIT_ITFL2_REL_CNF,                            /* 释放层2，等待ITFL2响应的子状态 */
    RRC_RRC_SS_WAIT_ITFPHY_CFG_CNF,                            /* 配置物理层，等待ITFPHY响应的子状态 */
    RRC_RRC_SS_WAIT_ITFPHY_REL_CNF,                            /* 释放物理层层，等待ITFPHY响应的子状态 */
    RRC_RRC_SS_WAIT_CSELPC_STATE_CHANGE_CNF,                            /* 通知CSELPC有协议状态跃迁，等待CSELPC响应的子状态 */
    RRC_RRC_SS_WAIT_CMM_STATE_CHANGE_CNF,                            /* 通知CMM有协议状态跃迁，等待CMM响应的子状态 */
    RRC_RRC_SS_WAIT_AM_DATA_CNF,                            /* 发送AM数据给PDCP，等待PDCP响应的子状态 */
    RRC_RRC_SS_WAIT_CONN_SETUP,                            /* 等待空口CONN SETUP消息的子状态 */
    RRC_RRC_SS_WAIT_MAC_RA_CNF,                            /* 向MAC发送随机接入请求后，等待随机接入响应的子状态 */
    RRC_RRC_SS_WAIT_CSELPC_STOP_RESEL_CNF,                            /* 向CSELPC发送停止重选后，等待重选停止响应的子状态 */
    LRRC_LRRC_SS_WAIT_ITFL2_RESET_L2_CNF,                   /* 等待ITFL2复位MAC、STOP PDCP、REEST RLC的子状态 */
    LRRC_LRRC_SS_WAIT_GRR_UE_CAP_INFO_CNF,                   /* 等待GRR UE能力响应的子状态 */
    LRRC_LRRC_SS_WAIT_WRRC_UE_CAP_INFO_CNF,                   /* 等待WRRC UE能力响应的子状态 */
    LRRC_LRRC_SS_WAIT_SET_WORK_MODE_CNF,                    /* 等待物理层切模的子状态 */
    LRRC_LRRC_SS_WAIT_CSELPC_CELL_SEARCH_CNF,                    /* 等待CSELPC小区搜索响应的子状态 */
    LRRC_LRRC_SS_WAIT_LMM_RESUME_RSP,                    /* 等待LNAS解挂响应的子状态 */
    LRRC_LRRC_SS_WAIT_LMM_SUSPEND_RSP,                    /* 等待LNAS挂起响应的子状态 */
    LRRC_LRRC_SS_WAIT_GURRC_CNF,                      /* 等待GURRC重定向/重选/CCO/切换响应的子状态 */
    LRRC_LRRC_SS_WAIT_WRRC_LOAD_DSP_CNF,                /* 等待WRRC加载WDSP响应的子状态 */
    LRRC_LRRC_SS_WAIT_GURRC_STOP_CNF,            /* 等待GURRC停止重定向/重选/CCO/切换响应的子状态 */
    LRRC_LRRC_SS_WAIT_GURRC_REL_ALL_CNF,            /* 等待GURRC REL ALL响应的子状态 */
    LRRC_LRRC_SS_WAIT_GURRC_CELL_SRCH_CNF,          /* 等待GURRC 小区搜索响应的子状态 */
    LRRC_LRRC_SS_WAIT_GURRC_CELL_SRCH_STOP_CNF,     /* 等待GURRC 停止小区搜索响应的子状态 */
    /* TDS begin */
    LRRC_LRRC_SS_WAIT_TRRC_REL_ALL_CNF,            /* 等待TRRC REL ALL响应的子状态 */
    /* TDS end */
    /* END of RRC模块的子状态 */

    /* RB模块的子状态 */
    LRRC_LRB_SS_WAIT_SET_WORK_MODE_CNF,                    /* 等待物理层切模的子状态 */
    RRC_RB_SS_WAIT_RABM_STATUS_RSP_SUSPEND,                            /* 向RABM发送停止数据传输请求后，等待RABM响应 */
    RRC_RB_SS_WAIT_ITFL2_STOP_PDCP_CNF,                            /* 向L2发送停止PDCP后，等待ITFL2响应 */
    RRC_RB_SS_WAIT_ITFL2_CFG_RLC_AND_MAC_CNF,                            /* 向L2发送重建RLC、复位MAC、配置MAC、配置RACH信息后，等待ITFL2响应 */
    RRC_RB_SS_WAIT_ITFPHY_HO_CNF,                            /* 向PHY发送切换开始后，等待PHY响应 */
    LRRC_LRB_SS_WAIT_GURRC_REL_ALL_CNF,            /* 等待GURRC REL ALL响应的子状态 */
    RRC_RB_SS_WAIT_ITFPHY_CFG_CNF,                            /* 配置PHY后，等待响应 */
    /* v7r2 ca begin */
    RRC_RB_SS_WAIT_ITFPHY_SCELL_SETUP_CNF,                            /* 配置PHY后，等待响应 */
    RRC_RB_SS_WAIT_ITFPHY_SCELL_REL_CNF,                            /* 配置PHY后，等待响应 */
    /* v7r2 ca end */
    RRC_RB_SS_WAIT_ITFL2_CFG_CNF,                            /* 配置L2后，等待响应 */
    RRC_RB_SS_WAIT_ITFL2_CFG_PDCP_AND_RLC_CNF,                            /* 向PDCP和RLC发送配置RB实体请求后，等待PDCP和RLC响应 */
    /* v7r2 ca begin */
    RRC_RB_SS_WAIT_ITFL2_SCELL_SETUP_CNF,                       /* 配置L2 scell SETUP后，等待响应 */
    RRC_RB_SS_WAIT_ITFL2_SCELL_REL_CNF,                         /* 配置L2 scell rel后，等待响应 */
    /* v7r2 ca end */
    LRRC_LRB_SS_WAIT_MM_SECU_PARA_RSP,                    /* 等待LNAS安全参数的子状态 */
    RRC_RB_SS_WAIT_SMC_SECU_CFG_CNF,                            /* 向SMC发送安全激活配置请求后，等待SMC响应 */
    RRC_RB_SS_WAIT_PDCP_AM_DATA_CNF,                            /* 向PDCP发送RRC CONNECTION RECONFIGURATION CMPL后，等待PDCP响应 */
    LRRC_LRB_SS_WAIT_MM_RESUME_RSP,                    /* 等待LNAS解挂的子状态 */
    RRC_RB_SS_WAIT_PDCP_CONTINUE_CNF,                            /* 向PDCP发送启动数据传输请求后，等待PDCP响应 */
    RRC_RB_SS_WAIT_RABM_STATUS_RSP_RESUME,                            /* 向RABM发送解除挂起请求后，等待RABM响应 */
    RRC_RB_SS_WAIT_CMM_HO_CMPL_CNF,                            /* 向CMM发送切换完成后，等待CMM响应 */
    RRC_RB_SS_WAIT_PHY_SYNC_CNF,                                /* 向PHY发送上报同步请求，等待响应 */
    RRC_RB_SS_WAIT_CMM_MEAS_CTRL_CNF,                            /* 向CMM发送测量配置时，等待CMM响应*/
    RRC_RB_SS_WAIT_ITF_REL_NEW_RB_CNF,                            /* 重配置失败后，需要把新建的RB删除 */
    /* END of RB模块的子状态 */

    /* REEST模块的子状态 */
    RRC_REEST_SS_WAIT_NAS_SUSPEND_RABM_RSP,                            /* 等待挂起NAS响应(停止数据传输) */
    RRC_REEST_SS_WAIT_CMM_STATE_CHANGE_CNF,                            /* 向CMM发送状态改变请求后，等待CMM响应 */
    RRC_REEST_SS_WAIT_ITFL2_STOP_PDCP_CNF,                            /* 向L2发送停止PDCP配置请求后，等待L2响应 */
    RRC_REEST_SS_WAIT_ITFL2_REEST_AND_RESET_L2_CNF,                            /* 向L2发送重建RLC和复位MAC配置请求后，等待L2响应 */
    RRC_REEST_SS_WAIT_ITFPHY_RELALL_CNF,                            /* 向物理层发送配置请求后，等待PHY响应 */
    LRRC_LREEST_SS_WAIT_GURRC_REL_ALL_CNF,                  /* 等待GURRC REL ALL响应的子状态 */
    /* TDS begin */
    LRRC_LREEST_SS_WAIT_TRRC_REL_ALL_CNF,                  /* 等待TRRC REL ALL响应的子状态 */
    /* TDS end */
    RRC_REEST_SS_WAIT_CSELPC_STATE_CHANGE_CNF,                            /* 向CSELPC发送状态请求后，等待CSELPC响应 */
    RRC_REEST_SS_WAIT_ITFL2_CONFIG_CNF,                            /* 向L2发送配置请求后，等待L2响应 */
    RRC_REEST_SS_WAIT_SMC_SECU_CONFIG_CNF,                            /* 向SMC发送配置请求后，等待SMC响应 */
    RRC_REEST_SS_WAIT_ITFPHY_CONFIG_CNF,                            /* 向物理层发送配置请求后，等待PHY响应 */
    RRC_REEST_SS_WAIT_MAC_RA_CNF,                            /* 向MAC发送随机接入请求后，等待MAC响应 */
    RRC_REEST_SS_WAIT_CONNECTION_REESTABLISHMENT,                            /* 等待空口消息 */
    RRC_REEST_SS_WAIT_PDCP_AM_DATA_CNF,                            /* 发送AM Data Req，等待PDCP响应 */
    RRC_REEST_SS_WAIT_DSDS_RADIO_RESOURCE_CNF,
    /* END of REEST模块的子状态 */

    /* CSELPC模块的子状态 */
    RRC_CSELPC_SS_WAIT_PHY_REL_ALL_CNF,                         /* 等待PHY REL ALL响应的子状态 */
    RRC_CSELPC_SS_WAIT_PCH_RELEASE_CNF,
    RRC_CSELPC_SS_WAIT_CSEL_SPEC_PLMN_SEARCH_CNF,                            /* 等待指定PLMN搜索的响应的子状态 */
    RRC_CSELPC_SS_WAIT_CONFIG_PCH,                            /* 等待配置物理层pch的子状态 */
    RRC_CSELPC_SS_WAIT_CONFIG_PHY_CNF,                            /* 等待配置物理层的响应的子状态 */
    RRC_CSELPC_SS_WAIT_PHY_CAMP_CNF,                            /* 等待物理层驻留响应的子状态 */
    RRC_CSELPC_SS_WAIT_CONFIG_L2_CNF,
    RRC_CSELPC_SS_WAIT_CSEL_ANY_CELL_SEARCH_CNF,                            /* 等待CSEL模块ANY CELL搜索结果的子状态 */
    RRC_CSELPC_SS_WAIT_CSEL_SUIT_CELL_SEARCH_CNF,                            /* 等待CSEL模块SUITABLE CELL搜索结果的子状态 */
    RRC_CSELPC_SS_WAIT_CSEL_PLMN_LIST_SEARCH_CNF,                            /* 等待CSEL模块PLMN LIST搜索结果的子状态 */
    RRC_CSELPC_SS_WAIT_CSEL_STOP_PLMN_LIST_CNF,                            /* 等待CSEL模块停止PLMN LIST搜索响应的子状态 */
    RRC_CSELPC_SS_WAIT_CSEL_CELL_SEARCH_CNF,                            /* 等待CSEL模块指定cell信息搜索响应的子状态 */
    RRC_CSELPC_SS_WAIT_CELL_RESEL_STOP,                            /* 接收RRC和REEST小区重选停止命令的子状态 */
    RRC_CSELPC_SS_WAIT_CELL_RESEL_STOP_CNF,                            /* 等待CSEL模块停止小区重选响应的子状态 */
    RRC_CSELPC_SS_WAIT_CELL_RESEL_START,                            /* 接收RRC和REEST小区重选开始的子状态 */
    RRC_CSELPC_SS_WAIT_CELL_RESEL_START_CNF,                            /* 等待CSEL模块启动小区重选响应的子状态 */
    RRC_CSELPC_SS_WAIT_SIB_SYS_REL_CNF,                            /* 等待sib删除的子状态 */
    RRC_CSELPC_SS_WAIT_SIB_SYS_INFO_UPDATE_CNF,                            /* 等待SIB模块系统消息更新的子状态 */
    RRC_CSELPC_SS_WAIT_CSEL_SYS_INFO_CNF,                            /* 通知CSEL系统消息更新，等待CSEL模块响应的子状态 */
    RRC_CSELPC_SS_WAIT_CMM_SYS_INFO_CNF,                            /* 通知CMM系统消息更新，等待CMM模块响应的子状态 */
    RRC_CSELPC_SS_WAIT_STATE_CHANGE,                            /* 透传RRC和REEST的状态变更通知时，等待状态变更通知的子状态 */
    RRC_CSELPC_SS_WAIT_STATE_CHANGE_CNF,                            /* 等待CSEL状态变更响应的子状态 */
    LRRC_LCSELPC_SS_WAIT_SET_WORK_MODE_CNF,                    /* 等待物理层切模的子状态 */
    LRRC_LCSELPC_SS_WAIT_CMM_RELALL_CNF,                           /*等待CMM回复NTF状态下释放PHY异系统测量之后响应CSELPC的子状态*/
    /* MBMS Begin */
    LRRC_LCSELPC_SS_WAIT_MBMS_FLOW_CMPLETE,
    LRRC_LCSELPC_SS_WAIT_MBMS_MCCH_CFG_CNF,
    LRRC_LCSELPC_SS_WAIT_MBMS_MCCH_MSG_IND,
    LRRC_LCSELPC_SS_WAIT_MBMS_MCCH_RECFG_CNF,
    LRRC_LCSELPC_SS_WAIT_MBMS_L2_CFG_CNF,
    LRRC_LCSELPC_SS_WAIT_MBMS_PHY_CFG_CNF,
    LRRC_LCSELPC_SS_WAIT_MBMS_L2_REL_CNF,
    LRRC_LCSELPC_SS_WAIT_MBMS_PHY_REL_CNF,
    /* MBMS end */
    /* bgs begin */
    LRRC_LCSELPC_SS_WAIT_BGS_SUSPEND_CNF,                                         /* 等待背景搜挂起响应的子状态 */
    LRRC_LCSELPC_SS_WAIT_BGS_RESUME_CNF,                                          /* 等待背景搜恢复响应的子状态 */
    LRRC_LCSELPC_SS_WAIT_BGS_STOP_CNF,                                            /* 等待背景搜停止响应的子状态 */
    /* bgs end */
    LRRC_CSELPC_SS_WAIT_CONN_TO_IDLE_REQ,            /* 等待phy 直接驻留响应的子状态 */

    /* END of CSELPC模块的子状态 */
    /* SMC模块的子状态 */
    RRC_SMC_SS_WAIT_PDCP_SECU_CONFIG_CNF,                                       /* 等待配置PDCP安全密钥的子状态 */
    RRC_SMC_SS_WAIT_PDCP_DATA_CNF,                                              /* 安全模式激活成功发送cmpl的子状态 */
    RRC_SMC_SS_WAIT_PDCP_FAIL_ACT_SECU_CNF,                                     /* 安全模式激活失败配置PDCP安全的子状态 */
    RRC_SMC_SS_WAIT_PDCP_CNT_CHK_CNF,
    /* END of SMC模块的子状态 */

    /* ITF模块的子状态 */

    /* RRC_ITFL2_SS_WAIT_CFG_CNF                      ,
     RRC_ITFPHY_SS_WAIT_CFG_CNF                     ,*/
    RRC_ITF_SS_WAIT_CFG_CNF,

    /* END of ITF模块的子状态 */

    /* bgs begin */
    /* CSELBG模块的子状态 */
    LRRC_LCSELBG_SS_IDLE,
    LRRC_LCSELBG_SS_WAIT_LPHY_BGS_CNF,
    LRRC_LCSELBG_SS_WAIT_GURRC_BGS_CNF,
    LRRC_LCSELBG_SS_WAIT_CELLSEARCHING_IND,
    LRRC_LCSELBG_SS_WAIT_GET_SYSINFO_CNF,
    LRRC_LCSELBG_SS_WAIT_REL_SYSINFO_CNF,

    LRRC_LCSELBG_SS_WAIT_LPHY_SUSPEND_BGS_CNF,
    LRRC_LCSELBG_SS_WAIT_LPHY_RESUME_BGS_CNF,
    /* END of CSELBG模块的子状态 */
    /* bgs end */

    /* CSEL模块的子状态 */
    RRC_CSEL_SS_IDLE,
    RRC_CSEL_SS_WAIT_CELL_SEARCHING_IND,/* 向PHY发送小区搜索请求后，等待PHY响应 */
    RRC_CSEL_SS_WAIT_GET_SYSINFO_CNF,/* 向SIB发送系统消息接收请求后，等待SIB响应 */
    RRC_CSEL_SS_WAIT_STOP_CELL_SEARCHING_CNF,/* 向PHY发送停止小区搜索请求后，等待PHY响应 */
    RRC_CSEL_SS_WAIT_REL_SYSINFO_CNF,/* 向SIB发送系统消息接收请求后，等待SIB响应 */
    RRC_CSEL_SS_MEAS_SETUP                          ,    /* 正在配置测量 */
    RRC_CSEL_SS_MEAS_RELEASE                        ,    /* 正在释放测量 */
    RRC_CSEL_SS_SIB_ACQUIRE                         ,    /* 正在收取邻区 SIB */
    RRC_CSEL_SS_SIB_CANCEL                          ,    /* 正在因为停止重选而取消邻区 SIB */
    RRC_CSEL_SS_RESEL_RSP                           ,    /* 正在等待重选指示的应答 */
    LRRC_LCSEL_SS_GU_MEAS_SETUP                     ,    /* 正在配置GU模建立测量 */
    LRRC_LCSEL_SS_GU_MEAS_RELEASE                   ,    /* 正在配置GU模建立测量 */
    LRRC_LCSEL_SS_WAIT_LPHY_MEAS_CNF                ,    /* L从模时配置物理层测量 */
    LRRC_LCSEL_SS_WAIT_WRRC_BSIC_VERITY_CNF         ,    /* 等待WRRC BSIC验证的子状态 */
    LRRC_LCSEL_SS_WAIT_LPHY_BSIC_VERITY_CNF         ,    /* 等待LPHY BSIC验证的子状态 */
    /* TDS begin */
    LRRC_LCSEL_SS_UTRA_TDD_MEAS_SETUP               ,    /* 正在配置UTRA_TDD模建立测量 */
    LRRC_LCSEL_SS_UTRA_TDD_MEAS_RELEASE             ,    /* 正在配置UTRA_TDD模释放测量 */
    /* TDS end */
    /* bgs begin */
    LRRC_LCSEL_SS_WAIT_BGS_SUSPEND_CNF,               /* 等待LCSELPC 背景搜挂起的子状态 */
    LRRC_LCSEL_SS_WAIT_BGS_RESUME_CNF,                /* 等待LCSELPC 背景搜恢复的子状态 */
    /* bgs end */

    /*DSDS begin: 2014-07-23*/
    RRC_CSEL_SS_WAIT_LPHY_BGS_START_CNF,              /* 等待PHY回复背景搜开始响应的子状态*/
    /*DSDS begin: 2014-07-23*/
    RRC_CSEL_SS_WAIT_LPHY_FREQ_RSSI_SORT_CNF,         /*等待物理层频点排序的结果*/

    RRC_CSEL_SS_WAIT_LPHY_BGS_RESEL_PREWORK_CNF,      /*BGS重选准备工作，等待物理层回复确认*/

    RRC_CSEL_SS_WAIT_LPHY_BGS_STOP_CNF,               /*BGS重选STOP背景搜后等待回复确认*/

    RRC_CSEL_SS_SIB_ACQUIRE_BGSRESEL,                 /*BGS重选等待系统消息的确认状态*/

    /* END of CSEL模块的子状态 */

    /* CMM模块的子状态 */
    RRC_CMM_SS_IDLE,
    RRC_CMM_SS_WAIT_SETUP_INTRA_FREQ_CNF,
    RRC_CMM_SS_WAIT_REL_INTRA_FREQ_CNF,
    RRC_CMM_SS_WAIT_SETUP_INTER_FREQ_CNF,
    RRC_CMM_SS_WAIT_REL_INTER_FREQ_CNF,
    RRC_CMM_SS_WAIT_CFG_MEAS_GAP_CNF,
    LRRC_LCMM_SS_WAIT_LPHY_MEAS_CNF,                     /* L从模时配置物理层测量 */
    LRRC_LCMM_SS_WAIT_WRRC_BSIC_VERITY_CNF,           /* 等待WRRC BSIC验证的子状态 */
    LRRC_LCMM_SS_WAIT_LPHY_BSIC_VERITY_CNF,          /* 等待LPHY BSIC验证的子状态 */
    LRRC_LCMM_SS_WAIT_GURRC_MEAS_SETUP_CNF,              /* L主模时配置建立GU模测量 */
    LRRC_LCMM_SS_WAIT_GURRC_MEAS_REL_CNF,                /* L主模时配置释放GU模测量 */
    LRRC_LCMM_SS_WAIT_LPHY_GURRC_MEAS_SETUP_CNF,         /* L主模时配置LPHY建立GU模测量 */
    LRRC_LCMM_SS_WAIT_LPHY_GURRC_MEAS_REL_CNF,           /* L主模时配置LPHY释放GU模测量 */
    /* TDS begin */
    LRRC_LCMM_SS_WAIT_UTRA_TDD_MEAS_SETUP_CNF,              /* L主模时配置建立UTRA_TDD模测量 */
    LRRC_LCMM_SS_WAIT_UTRA_TDD_MEAS_REL_CNF,                /* L主模时配置释放UTRA_TDD模测量 */
    /* TDS end */
    /* anr begin */
    LRRC_LCMM_SS_WAIT_LPHY_ANR_START_CNF,
    LRRC_LCMM_SS_WAIT_LPHY_ANR_STOP_CNF,
    LRRC_LCMM_SS_WAIT_GURRC_ANR_START_CNF,
    LRRC_LCMM_SS_WAIT_GURRC_ANR_STOP_CNF,
    /* anr end */

    /* v7r2 ca begin */
    LRRC_LCMM_SS_WAIT_GU_MEAS_CNF,
    LRRC_LCMM_SS_WAIT_PHY_MEAS_CNF,
    /* v7r2 ca end */

    /* END of CMM模块的子状态 */

    /* SIB模块的子状态 */
    RRC_SIB_SS_IDLE,
    RRC_SIB_SS_WAIT_PBCH_SETUP_CNF,
    RRC_SIB_SS_WAIT_MIB_IND,
    RRC_SIB_SS_WAIT_PBCH_REL_CNF,
    RRC_SIB_SS_WAIT_RL_SETUP_CNF,
    RRC_SIB_SS_WAIT_SIB1_IND,
    RRC_SIB_SS_WAIT_SI_CFG_CNF,
    RRC_SIB_SS_WAIT_SIB_IND,
    RRC_SIB_SS_WAIT_RL_REL_CNF,
    RRC_SIB_SS_CSEL_WAIT_SETUP_CNF,
    RRC_SIB_SS_CSEL_WAIT_REL_CNF,
    /* END of SIB模块的子状态 */

    LRRC_LRRC_SS_WAIT_CDMA_CNF,                      /* 等待CDMA重定向/重选响应的子状态 */
    LRRC_LRRC_SS_WAIT_CDMA_STOP_CNF,                 /* 等待CDMA重定向/重选停止响应的子状态 */

    LRRC_DSDS_SS_WAIT_RRM_RADIO_RESOURCE_CNF,       /* 等待dsds的RRM资源申请响应的子状态 */

    LRRC_LCSEL_SS_CDMA_HRPD_MEAS_SETUP               ,    /* 正在配置CDMA_HRPD模建立测量 */
    LRRC_LCSEL_SS_CDMA_HRPD_MEAS_RELEASE             ,    /* 正在配置CDMA_HRPD模释放测量 */
    LRRC_LRRC_SS_WAIT_CAS_REL_ALL_CNF                ,    /* 等待CAS REL ALL CNF的子状态 */
    LRRC_LCMM_SS_WAIT_HRPD_MEAS_CNF,

    LRRC_LRRC_SS_WAIT_CONN_TO_IDLE_CNF,            /* 等待phy 直接驻留响应的子状态 */
    LRRC_LCSELPC_SS_WAIT_MBMS_PHY_ENABLE_CNF,                 /*等待PHY MBMS使能确认消息*/
    LRRC_LCSELPC_SS_WAIT_MBMS_PHY_DISABLE_CNF,
    LRRC_LCSELPC_SS_WAIT_MBMS_NOTIFY_CFG_CNF,
    LRRC_LCSELPC_SS_WAIT_MBMS_PMCH_CFG_CNF,
    LRRC_LCSELPC_SS_WAIT_MBMS_PMCH_ACTIVE_CNF,

    LRRC_LCMM_SS_WAIT_LPHY_OTDOA_CNF,
    LRRC_LRRC_SS_WAIT_LCMM_OTDOA_CNF,

    /* 状态机预处状态，子要用于不进状态机的消息的处理 */
    RRC_SS_PRE_PROCESS,

    /* begin: add for Austin搜网优化 PhaseII , l00277963*/
    RRC_CSEL_SS_WAIT_CSS_CURR_GEO_RSP,
    /* end:   add for Austin搜网优化 PhaseII , l00277963*/

    RRC_SS_ID_BUTT
};
typedef VOS_UINT16 RRC_SS_ID_ENUM_UINT16;

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

#endif /* end of LPsFsmState.h */
