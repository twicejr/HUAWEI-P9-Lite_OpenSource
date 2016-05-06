/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : phytoolinterface.h
  版 本 号   : 初稿
  作    者   : luoqingquan
  生成日期   : 2012年8月14日
  最近修改   :
  功能描述   : phytoolinterface.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年8月14日
    作    者   : luoqingquan
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#ifndef __PHYTOOLINTERFACE_H__
#define __PHYTOOLINTERFACE_H__


#include "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  2.2 宏定义,W/G宏定义
*****************************************************************************/

/* 打印携带参数个数 */
#define UPHY_TOOL_MNTN_ERROR_RPT_VAR_NUM        ( 5 )
#define UPHY_TOOL_INTER_REG_MAX_NUM             ( 300 )

/* 可维可测的func type为4,intra msg类型需要找TOOL确认 */
#define UPHY_TOOL_MODEM2_FUNC_TYPE_OM_MSG       ( 0x84 )
#define UPHY_TOOL_MODEM2_FUNC_TYPE_INTRA_MSG    ( 0x94 )

#define UPHY_TOOL_MODEM1_FUNC_TYPE_OM_MSG       ( 0x44 )
#define UPHY_TOOL_MODEM1_FUNC_TYPE_INTRA_MSG    ( 0x54 )

#define UPHY_TOOL_MODEM0_FUNC_TYPE_OM_MSG       ( 0x04 )
#define UPHY_TOOL_MODEM0_FUNC_TYPE_INTRA_MSG    ( 0x1A )


/* 大小必须保持和phyoaminterface.h中UPHY_OAM_SLEEP_INFO_NUM一致 */
#define UPHY_TOOL_SLEEP_INFO_NUM                ( 16 )

/*****************************************************************************
  2.2 宏定义,GPHY宏定义
*****************************************************************************/

#if defined(INSTANCE_1)
#define GPHY_RF_CAL_NO_SIG_FUNC_TYPE            ( 0x48 )
#define WPHY_RF_CAL_NO_SIG_FUNC_TYPE            ( 0x07 )
#elif defined (INSTANCE_2)
#define GPHY_RF_CAL_NO_SIG_FUNC_TYPE            ( 0x88 )
#define WPHY_RF_CAL_NO_SIG_FUNC_TYPE            ( 0x07 )
#else
#define GPHY_RF_CAL_NO_SIG_FUNC_TYPE            ( 0x08 )
#define WPHY_RF_CAL_NO_SIG_FUNC_TYPE            ( 0x07 )
#endif

#define CPHY_RF_CAL_NO_SIG_FUNC_TYPE            ( 0x12 )


/* PS数传时下行最大的时隙个数 */
#define GPHY_PS_MAX_RX_TSN_NUM                  ( 5 )

/* PS数传时上行最大的时隙个数 */
#define GPHY_PS_MAX_TX_TSN_NUM                  ( 4 )

#define GPHY_TOOL_SLAVE_BSIC_MAX_NUM            ( 8 )

/*****************************************************************************
 原语GPHY_TOOL_FUNC_BIT_CTRL_REQ_STRU中ulFuncBitMask每个bit位的含义;
 如果对应bit位置1:则对应功能失效;
 如果对应bit位置0:则恢复对应功能;
*****************************************************************************/

#define GPHY_FUNC_DRX_USE_DISABLE_FLG           ( BIT0 )
#define GPHY_FUNC_DRX_SIMPLIFY_DISABLE_FLG      ( BIT1 )
#define GPHY_FUNC_BA_MEA_DISABLE_FLG            ( BIT2 )
#define GPHY_FUNC_INTERFERE_MEA_DISABLE_FLG     ( BIT3 )
#define GPHY_FUNC_C1_RESEL_DISABLE_FLG          ( BIT4 )
#define GPHY_FUNC_C2_RESEL_DISABLE_FLG          ( BIT5 )
#define GPHY_FUNC_NCELL_FBSB_DISABLE_FLG        ( BIT6 )
#define GPHY_FUNC_NCELL_SB_DISABLE_FLG          ( BIT7 )
#define GPHY_FUNC_NCELL_TASK_DISABLE_FLG        ( BIT8 )
#define GPHY_FUNC_RF_FRONT_DISPLAY_MNTN_FLG     ( BIT9 )



/* 可维可测数据块最大上报个数 */
#define GPHY_TOOL_RPT_BLK_MAX_NUM               ( 10 )

/* 打印携带参数个数 */
#define GPHY_TOOL_MNTN_ERROR_RPT_VAR_NUM        ( 5 )                           /* 错误上报时，界定的上报变量个数 */


/*****************************************************************************
  2.3 宏定义,WPHY宏定义
*****************************************************************************/

#define WPHY_TOOL_PA_SWITCH_COMP_SLOT           ( 4 )                           /* W pa切换补偿4个slot */
/* 打印携带参数个数 */
#define WPHY_TOOL_MNTN_ERROR_RPT_VAR_NUM        ( 5 )                           /* 错误上报时，界定的上报变量个数 */

/* 激活小区最大个数 */
#define WPHY_MNTN_MAX_ACT_CELL_NUM              ( 7 )                           /* 激活集小区最大数目 */


/* 可维可测数据块最大上报个数 */
#define WPHY_TOOL_RPT_BLK_MAX_NUM               ( 10 )

#define WPHY_MNTN_TRCH_NUM                      ( 8 )

#define WPHY_MNTN_SLAVE_REPORTFREQ_NUM          ( 3 )                           /* 从模可谓可测上报频点个数 */
#define GPHY_TOOL_MA_FREQ_NUM                   ( 64 )                          /* 跳频序列的个数 */

#define GPHY_TOOL_BA_LIST_MAX_NUM               ( 32 )                          /* GSM BA LIST最大的个数 */

#define GPHY_TOOL_AMR_MAX_ACS_NUM               ( 4 )                           /* 最大激活集个数 */

#define GPHY_TOOL_RPT_MAX_LEN                   ( 100 )

#define GPHY_TOOL_AMR_CODEC_MAX_NUM             ( 8 )                           /* AMR最大编码个数 */

/* 物理层每帧最大时隙个数 */
#define GPHY_TOOL_TN_NUM_IN_FRAME               ( 8 )

#define GPHY_TOOL_MAX_UL_SLOT_NUM               ( 4 )                           /* Gsm上行最大的时隙个数 */

#define GPHY_TOOL_MAX_IDLE_FRAME_NUM            ( 84 )                          /* 专用态5S内空闲帧的最大数目 */

#define GPHY_TOOL_MAX_SYNC_TASK_NUM             ( 5 )                           /* 专用态空闲帧能做的最大同步任务个数 */

#define GPHY_TOOL_MAX_NCELL_NUM                 ( 32 )                          /* 上报的邻区异系统最大数目 */

#define GPHY_TOOL_NCELL_RPT_PREDICT_TASK_INFO_NUM  ( 5 )                        /* 专用态打印的预测任务的个数 */

/* G回读的内存地址最大规格 */
#define GPHY_MNTN_READ_ADDR_MAX_NUM             ( 300 )


#define WPHY_MNTN_HSUPA_SUB_FRM_NUM             ( 5 )                           /* HSUPA子帧数 */

#define WPHY_MNTN_HSUPA_OM_CARERIER_NUM         ( 2 )                           /* UPA 可维可测使用，包括主副载波 */

#define WPHY_MNTN_HSUPA_RPT_VALUE_MAX_NUM       ( 100 )

#define WPHY_MNTN_RL_SCRAM_MAX_NUM              ( 7 )

#define WPHY_MNTN_DEMOD_FINGER_MAX_NUM          ( 13 )

#define WPHY_MNTN_EQ_FINGER_RPT_MAX_NUM         ( 2 )

#define WPHY_MNTN_BLER_RPT_MAX_NUM              ( 5 )

#define WPHY_MNTN_DPA_ERROR_CODE_RPT_MAX_NUM    ( 2 )

#define WPHY_MNTN_MP_WIN_MAX_NUM                ( 3 )

/* BCCH队列最大任务个数 */
#define WPHY_MNTN_BCCH_QUEUE_LENGTH              ( 4 )

/* ademod队列最大任务个数 */
#define WPHY_MNTN_ADMOD_QUEUE_LENGTH             ( 5 )

/* 跟踪均衡模板的帧数 */
#define WPHY_MNTN_CPC_DRX_PATTERN_FRAME_NUM      ( 5 )

/* CPC DRX均衡控制的类型数 */
#define WPHY_MNTN_CPC_DRX_EQUA_CTRL_TYPE_NUM     ( 2 )

/* CQI PATTERN个数 */
#define WPHY_MNTN_CPC_DRX_CQI_PATTERN_NUM        ( 3 )

/* CPC DRX RF 控制类型数 */
#define WPHY_MNTN_CPC_DRX_RF_CTRL_TYPE_NUM       ( 6 )

#define WPHY_MNTN_SLAVE_STEP23_CELL_NUM          ( 6 )

/* 最大IC小区个数 */
#define WPHY_MNTN_IC_MAX_CELL_NUM                ( 2 )

/* DPA的P值数目+1，直接使用P值当下标 */
#define WPHY_MNTN_P_VALUE_NUM                    ( 16 )

/* 各子帧上报RAM偏移 */
#define WPHY_MNTN_SUB_FRAME_ADDR_OFFSET          ( 0x30 )

/* 子帧数 */
#define WPHY_MNTN_SUB_FRAME_NUM                  ( 5 )

#define WPHY_MNTN_MAX_CNT                        ( 0xFFFFFFFF )

#define WPHY_MNTN_MAX_UINT16_VALUE               ( 0xFFFF )

#define WPHY_MNTN_MAX_CARRIER_NUM                ( 2 )

/* HSDSCH按照区间统计，最大分10个区间 */
#define WPHY_MNTN_MAX_REGION_NUM                 ( 10 )

/*W Rx FAST CAL 最大次数:SC/DC BLK/NBLK 最大8档，每档测试2个功率能量 */
#define WPHY_CAL_RX_FAST_CAL_MAX_VAILD_NUM       ( 64 )

/* HSUPA可维可测上报中激活集小区最大数量 */
#define WPHY_MNTN_HSUPA_ACTIVE_SET_MAX_NUM       ( 6 )

/* WBBP 支持的最大天线个数 */
#define WPHY_MNTN_WBBP_MAX_ANT_NUM               ( 2 )

#define WPHY_MNTN_INVALID_UINT16                 ( 0xffff )

/* 无效值 */
#define WPHY_MNTN_INVALID_VALUE                  ( -1 )

/* WPHY每个帧中的时隙数 */
#define WPHY_MNTN_SLOT_NUM_BY_FRAME              ( 15 )

/* 主小区Hsdpa SCCH的信道数量 */
#define WPHY_MAIN_CELL_HSDPA_SCCH_MAX_NUM        ( 4 )

/* 十六位整数最大值，定义为非法值 */
#define WPHY_MNTN_UINT16_INVALID_NUM             ( 0xFFFF )

/* 寄存器默认边界值保护 */
#define WPHY_MNTN_REG_INVALID                    ( 0x5A5A )

/* HsScch No的无效值 */
#define WPHY_MNTN_INVALID_HSSCCH_NO              ( 0xFF )

/* ovsf的无效值 */
#define WPHY_MNTN_INVALID_OVSF                   ( 0xFF )

/* 上报天线口RSSI参数值 */
#define WPHY_MNTN_RSSI_PARA                      ( 0x400 )

/*发射功率无效值 */
#define WPHY_MNTN_POWER_VAL_INVALID              ( 0xFF )

/* 天线1接收功率无效值 */
#define WPHY_MNTN_POWER_ANT1_VAL_INVALID         ( 0xFF )

/* 天线2接收功率无效值 */
#define WPHY_MNTN_POWER_ANT2_VAL_INVALID         ( 0xFF )

/* Hs Pdsch信道时间偏移无效值 */
#define WPHY_MNTN_DL_DPCCH_OFFSET_INVALID        ( 0xFF )

/* BBP_DBG 用 */
#define UPHY_TOOL_BBP_DBG_SAMPLE_REG_LIST_NUM       ( 3 )
#define UPHY_TOOL_BBP_DBG_OTHER_REG_LIST_NUM        ( 2 )
#define UPHY_TOOL_BBP_DBG_SAMPLE_REG_NUM            ( 50 )



#define UPHY_TOOL_MAX_SSI_READ_ALL_NUM           ( 256 )                        /* 全回读支持256个寄存器 */
#define UPHY_TOOL_MAX_SSI_READ_BACK_NUM          ( 64 )                         /* 最多支持64个寄存器的回读 */
#define UPHY_TOOL_MAX_MIPI_READ_BACK_NUM         ( 64 )                         /* 最多支持64个寄存器的回读 */

/* 回读的内存地址最大规格 */
#define WPHY_MNTN_READ_ADDR_MAX_NUM              ( 300 )


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  3.1 枚举定义,GPHY枚举定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 UPHY回复CNF时,携带的处理结果枚举
*****************************************************************************/
enum UPHY_TOOL_RTC_DEBUG_ENUM
{
    UPHY_MNTN_RTC_DEBUG_CLOSE                   = 0,
    UPHY_MNTN_RTC_DEBUG_OPEN                    = 1,

    UPHY_MNTN_RTC_DEBUG_BUTT
};
typedef VOS_UINT16 UPHY_TOOL_RTC_DEBUG_ENUM_UINT16;



/*****************************************************************************
 UPHY<-->TOOL原语列表
*****************************************************************************/
enum UPHY_TOOL_MNTN_MSG_ID_ENUM
{
    ID_TOOL_UPHY_REQ                            = 0x0,                          /* _H2ASN_MsgChoice  TOOL_UPHY_REQ_STRU */

    ID_TOOL_UPHY_QUERY_SHARE_ADDR_REQ           = 0xFE01,                       /* _H2ASN_MsgChoice  UPHY_TOOL_QUERY_SHARE_ADDR_REQ_STRU */
    ID_UPHY_TOOL_QUERY_SHARE_ADDR_IND           = 0xFE02,                       /* _H2ASN_MsgChoice  UPHY_TOOL_QUERY_SHARE_ADDR_IND_STRU */

    ID_TOOL_UPHY_SDT_LINK_STATUS_REQ            = 0xFE03,                       /* _H2ASN_MsgChoice  UPHY_TOOL_SDT_LINK_STATUS_REQ_STRU */
    ID_UPHY_TOOL_SDT_LINK_STATUS_CNF            = 0xFE04,                       /* _H2ASN_MsgChoice  UPHY_TOOL_COMMON_CNF_STRU */

    ID_TOOL_UPHY_ERROR_REPORT_REQ               = 0xFE05,                       /* _H2ASN_MsgChoice  UPHY_TOOL_ERROR_REPORT_REQ_STRU */
    ID_UPHY_TOOL_ERROR_REPORT_CNF               = 0xFE06,                       /* _H2ASN_MsgChoice  UPHY_TOOL_COMMON_CNF_STRU */

    ID_TOOL_UPHY_WPHY_BLER_RPT_REQ              = 0xFE07,
    ID_TOOL_UPHY_WPHY_INTRA_MSG_RPT_CTRL_REQ    = 0xFE08,
    ID_TOOL_UPHY_GPHY_INTRA_MSG_RPT_CTRL_REQ    = 0xFE09,


    ID_TOOL_UPHY_WPHY_INTER_GREG_REPORT_REQ     = 0xFE0A,                       /* _H2ASN_MsgChoice  UPHY_TOOL_WPHY_INTER_GREG_REPORT_REQ_STRU */
    ID_UPHY_TOOL_WPHY_INTER_GREG_REPORT_CNF     = 0xFE0B,                       /* _H2ASN_MsgChoice  UPHY_TOOL_WPHY_INTER_GREG_REPORT_CNF_STRU */
    ID_UPHY_TOOL_WPHY_INTER_GREG_REPORT_IND     = 0xFE0C,                       /* _H2ASN_MsgChoice  UPHY_TOOL_WPHY_INTER_GREG_REPORT_IND_STRU */
    ID_TOOL_UPHY_WPHY_INTER_GREG_STOP_REQ       = 0xFE0D,                       /* _H2ASN_MsgChoice  UPHY_TOOL_WPHY_INTER_GREG_STOP_REQ_STRU */
    ID_UPHY_TOOL_WPHY_INTER_GREG_STOP_CNF       = 0xFE0E,                       /* _H2ASN_MsgChoice  UPHY_TOOL_COMMON_CNF_STRU */

    ID_TOOL_UPHY_GPHY_INTER_WREG_REPORT_REQ     = 0xFE0F,                       /* _H2ASN_MsgChoice  UPHY_TOOL_GPHY_INTER_WREG_REPORT_REQ_STRU */
    ID_UPHY_TOOL_GPHY_INTER_WREG_REPORT_CNF     = 0xFE10,                       /* _H2ASN_MsgChoice  UPHY_TOOL_GPHY_INTER_WREG_REPORT_CNF_STRU */
    ID_UPHY_TOOL_GPHY_INTER_WREG_REPORT_IND     = 0xFE11,                       /* _H2ASN_MsgChoice  UPHY_TOOL_GPHY_INTER_WREG_REPORT_IND_STRU */
    ID_TOOL_UPHY_GPHY_INTER_WREG_STOP_REQ       = 0xFE12,                       /* _H2ASN_MsgChoice  UPHY_TOOL_GPHY_INTER_WREG_STOP_REQ_STRU */
    ID_UPHY_TOOL_GPHY_INTER_WREG_STOP_CNF       = 0xFE13,                       /* _H2ASN_MsgChoice  UPHY_TOOL_COMMON_CNF_STRU */

    ID_UPHY_TOOL_DRX_LATE_INFO_IND              = 0xFE14,                       /* _H2ASN_MsgChoice  UPHY_TOOL_DRX_LATE_INFO_IND_STRU */
    ID_UPHY_TOOL_KEY_INFORMATION_REPORT         = 0xFE15,                       /* _H2ASN_MsgChoice  UPHY_COM_KEY_INFORMATION_STRU */

    ID_UPHY_TOOL_UPHY_INIT_REPORT_IND           = 0xFE18,                       /* _H2ASN_MsgChoice  ** */

    ID_RCM_TOOL_MNTN_MSG_SCHDL_MAIN_INFO        = 0xFE19,                       /* _H2ASN_MsgChoice  RCM_SCHDL_MAIN_PARA_STRU */
    ID_RCM_TOOL_MNTN_MSG_MSGLIST_INFO           = 0xFE1A,                       /* _H2ASN_MsgChoice  RCM_PHY_MSG_LIST_STRU */
    ID_RCM_TOOL_MNTN_MSG_CHAINLIST_INFO         = 0xFE1B,                       /* _H2ASN_MsgChoice  RCM_TASK_NODE_STRU */

    /* diag 寄存器结构配置及消息上报 */
    ID_TOOL_COM_DIAG_PHY_SAMPLE_CFG_REQ         = 0xFE1C,                       /* _H2ASN_MsgChoice  COM_TOOL_DIAG_PHY_SAMPLE_CFG_STRU */
    ID_TOOL_COM_DIAG_PHY_SAMPLE_IND             = 0xFE1D,                       /* _H2ASN_MsgChoice  COM_TOOL_DIAG_PHY_SAMPLE_REG_IND_STRU */
    ID_TOOL_COM_DIAG_SAMPLE_REG_IND             = 0xFE1E,                       /* _H2ASN_MsgChoice  COM_TOOL_DIAG_PHY_REG_IND_STRU */

    ID_TOOL_UPHY_SOCP_VOTE_WAKE_CNF             = 0xFE20,                       /* _H2ASN_MsgChoice  UPHY_DRV_SOCP_VOTE_WAKE_CNF_STRU */

    ID_TOOL_UPHY_SSI_READ_RPT_REQ               = 0xFE21,
    ID_UPHY_TOOL_SSI_READ_RPT_CNF               = 0xFE22,
    ID_UPHY_TOOL_SSI_READ_RPT_IND               = 0xFE23,

    ID_TOOL_UPHY_MIPI_READ_RPT_REQ              = 0xFE24,
    ID_UPHY_TOOL_MIPI_READ_RPT_CNF              = 0xFE25,
    ID_UPHY_TOOL_MIPI_READ_RPT_IND              = 0xFE26,


    ID_UPHY_TOOL_INFO_REPORT_IND                = 0xFEF7,                       /* _H2ASN_MsgChoice  UPHY_TOOL_ERROR_REPORT_IND_STRU */
    ID_UPHY_TOOL_WARNING_REPORT_IND             = 0xFEF8,                       /* _H2ASN_MsgChoice  UPHY_TOOL_ERROR_REPORT_IND_STRU */
    ID_UPHY_TOOL_ERROR_REPORT_IND               = 0xFEF9,                       /* _H2ASN_MsgChoice  UPHY_TOOL_ERROR_REPORT_IND_STRU */

    ID_UPHY_TOOL_TAS_STATUS_REPORT_REQ          = 0xFEFA,                       /* _H2ASN_MsgChoice  UPHY_TOOL_TAS_STATUS_REPORT_REQ_STRU */
    ID_UPHY_TOOL_TAS_STATUS_REPORT_CNF          = 0xFEFB,                       /* _H2ASN_MsgChoice  UPHY_TOOL_COMMON_CNF_STRU */
    ID_UPHY_TOOL_AGENTC_ESTIMATE_STATE_IND      = 0xFEFC,                       /* _H2ASN_MsgChoice UPHY_TOOL_AGENTC_ESTIMATE_IND_STRU */
    ID_UPHY_TOOL_AGENTC_COMPARE_STATE_IND       = 0xFEFD,                       /* _H2ASN_MsgChoice UPHY_TOOL_AGENTC_COMPARE_IND_STRU */
    ID_UPHY_TOOL_AGENTC_PROTECT_STATE_IND       = 0xFEFE,                       /* _H2ASN_MsgChoice UPHY_TOOL_AGENTC_PROTECT_IND_STRU */
    ID_UPHY_TOOL_MSG_ID_BUTT
};
typedef VOS_UINT16 UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16;


/*****************************************************************************
 UPHY回复CNF时,携带的处理结果枚举
*****************************************************************************/
enum UPHY_TOOL_MNTN_RSLT_ENUM
{
    UPHY_MNTN_RSLT_SUCC                         = 0,
    UPHY_MNTN_RSLT_FAIL                         = 1,

    UPHY_MNTN_RSLT_BUTT
};
typedef VOS_UINT16 UPHY_TOOL_MNTN_RSLT_ENUM_UINT16;



/*****************************************************************************
 枚举名    : UPHY_TOOL_MNTN_RPT_LEVEL_ENUM
 协议表格  :
 枚举说明  : UPHY错误上报级别
*****************************************************************************/
enum UPHY_TOOL_MNTN_RPT_LEVEL_ENUM
{
    UPHY_MNTN_RPT_LEVEL_DEBUG                   = 0,
    UPHY_MNTN_RPT_LEVEL_INFO                    = 1,
    UPHY_MNTN_RPT_LEVEL_WARNING                 = 2,
    UPHY_MNTN_RPT_LEVEL_ERROR                   = 3,

    UPHY_MNTN_RPT_LEVEL_BUTT
};
typedef VOS_UINT16 UPHY_TOOL_MNTN_RPT_LEVEL_ENUM_UINT16;





/*****************************************************************************
 GPHY<-->TOOL原语列表
*****************************************************************************/
enum GPHY_TOOL_MNTN_MSG_ID_ENUM
{
    /* 下发REQ消息因为带VOS消息，上报的IND或CNF消息不带VOS消息头，应对REQ另外解析，这里指示为了ASN生成方便 */
    ID_TOOL_GPHY_REQ                            = 0x0,                          /* _H2ASN_MsgChoice  TOOL_GPHY_REQ_STRU */

    ID_TOOL_GPHY_BLER_REPORT_REQ                = 0xE001,                       /* _H2ASN_MsgChoice  GPHY_TOOL_BLER_REPORT_REQ_STRU */
    ID_GPHY_TOOL_BLER_REPORT_CNF                = 0xE010,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU */
    ID_GPHY_TOOL_BLER_REPORT_IND                = 0xE011,                       /* _H2ASN_MsgChoice  GPHY_TOOL_BLER_REPORT_IND_STRU */

    ID_TOOL_GPHY_SNR_REPORT_REQ                 = 0xE002,                       /* _H2ASN_MsgChoice  GPHY_TOOL_SNR_REPORT_REQ_STRU */
    ID_GPHY_TOOL_SNR_REPORT_CNF                 = 0xE020,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU */
    ID_GPHY_TOOL_SNR_REPORT_IND                 = 0xE021,                       /* _H2ASN_MsgChoice  GPHY_TOOL_SNR_REPORT_IND_STRU */

    ID_TOOL_GPHY_AFC_REPORT_REQ                 = 0xE003,                       /* _H2ASN_MsgChoice  GPHY_TOOL_AFC_REPORT_REQ_STRU */
    ID_GPHY_TOOL_AFC_REPORT_CNF                 = 0xE030,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU */
    ID_GPHY_TOOL_AFC_REPORT_IND                 = 0xE031,                       /* _H2ASN_MsgChoice  GPHY_TOOL_AFC_REPORT_IND_STRU */

    ID_TOOL_GPHY_POWER_CTRL_REPORT_REQ          = 0xE004,                       /* _H2ASN_MsgChoice  GPHY_TOOL_POWER_CTRL_REPORT_REQ_STRU */
    ID_GPHY_TOOL_POWER_CTRL_REPORT_CNF          = 0xE040,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU */
    ID_GPHY_TOOL_POWER_CTRL_REPORT_IND          = 0xE041,                       /* _H2ASN_MsgChoice  GPHY_TOOL_POWER_CTRL_REPORT_IND_STRU */

    /* TAS状态上报请求*/
    ID_GPHY_TOOL_REQUEST_TAS_STATUS_IND         = 0xE043,                       /* _H2ASN_MsgChoice GPHY_TOOL_TAS_STATUS_REPORT_IND_STRU*/

    ID_GPHY_TOOL_PSRCH_NCELL_FB_SB_READ_REQ     = 0xE044,                       /* _H2ASN_MsgChoice  GPHY_TOOL_PSRCH_NCELL_FB_SB_READ_REQ_STRU */
    ID_GPHY_TOOL_PSRCH_NCELL_BCCH_READ_REQ      = 0xE045,                       /* _H2ASN_MsgChoice  GPHY_TOOL_PSRCH_NCELL_BCCH_READ_REQ_STRU */

    ID_GPHY_TOOL_PSRCH_SEARCH_CELL_LIST_IND     = 0xE046,                       /* _H2ASN_MsgChoice  GPHY_TOOL_PSRCH_SEARCH_CELL_LIST_IND_STRU */
    ID_GPHY_TOOL_PSRCH_SEARCH_CAND_INFO_IND     = 0xE047,                       /* _H2ASN_MsgChoice  GPHY_TOOL_PSRCH_SEARCH_CAND_INFO_IND_STRU */
    ID_GPHY_TOOL_PSRCH_SEARCH_CELL_INFO_IND     = 0xE048,                       /* _H2ASN_MsgChoice  GPHY_TOOL_PSRCH_SEARCH_CELL_INFO_IND_STRU */

    ID_GPHY_TOOL_PSRCH_IDLE_CELL_LIST_IND       = 0xE049,                       /* _H2ASN_MsgChoice  GPHY_TOOL_PSRCH_IDLE_CELL_LIST_IND_STRU */

    ID_TOOL_GPHY_READ_MEM_REQ                   = 0xE04A,                       /* _H2ASN_MsgChoice GPHY_TOOL_READ_MEM_REQ_STRU */
    ID_GPHY_TOOL_READ_MEM_CNF                   = 0xE04B,                       /* _H2ASN_MsgChoice GPHY_TOOL_COMMON_CNF_STRU */
    ID_GPHY_TOOL_READ_MEM_IND                   = 0xE04C,                       /* _H2ASN_MsgChoice GPHY_TOOL_READ_MEM_IND_STRU */

    /* 干扰特性 消息上报 */
    ID_GPHY_TOOL_INTERFE_TX_BLANKING_IND        = 0xE04D,                       /* _H2ASN_MsgChoice  COM_GPHY_INTERFE_INFO_STRU *//* G配置GTC把别一个modem的TX关闭 */
    ID_GPHY_TOOL_INTERFE_RX_BLANKING_IND        = 0xE04E,                       /* _H2ASN_MsgChoice  COM_GPHY_INTERFE_INFO_STRU *//* G配置GTC把别一个modem的RX恢复 */
    ID_GPHY_TOOL_INTERFE_STOP_G_TX_IND          = 0xE04F,                       /* _H2ASN_MsgChoice  COM_GPHY_INTERFE_INFO_STRU *//* G关闭自己的TX发送 */

    ID_TOOL_GPHY_POWER_CTRL_SET_REQ             = 0xE005,                       /* _H2ASN_MsgChoice  GPHY_TOOL_POWER_CTRL_SET_REQ_STRU */
    ID_GPHY_TOOL_POWER_CTRL_SET_CNF             = 0xE050,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU */

    ID_GPHY_TOOL_CHANNEL_QUALITY_IND            = 0xE080,                       /* _H2ASN_MsgChoice  GPHY_TOOL_CHANNEL_QUALITY_IND_STRU */

    ID_TOOL_GPHY_FUNC_BIT_CONTROL_REQ           = 0xE00A,                       /* _H2ASN_MsgChoice  GPHY_TOOL_FUNC_BIT_CTRL_REQ_STRU */
    ID_GPHY_TOOL_FUNC_BIT_CONTROL_CNF           = 0xE0A0,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU */

    ID_TOOL_GPHY_PARA_CONTROL_REQ               = 0xE00B,                       /* _H2ASN_MsgChoice  GPHY_TOOL_PARA_CONTROL_REQ_STRU */
    ID_GPHY_TOOL_PARA_CONTROL_CNF               = 0xE0B0,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU */

    ID_TOOL_GPHY_RF_FRONT_STATIC_REQ            = 0xE052,                       /* _H2ASN_MsgChoice  GPHY_TOOL_RF_FRONT_STATIC_REQ_STRU */
    ID_GPHY_TOOL_RF_FRONT_STATIC_IND            = 0xE053,                       /* _H2ASN_MsgChoice  GPHY_TOOL_RF_FRONT_STATIC_IND_STRU */

    ID_TOOL_GPHY_INTRA_MSG_RPT_CTRL_REQ         = 0xE054,                       /* _H2ASN_MsgChoice  GPHY_TOOL_INTRA_MSG_RPT_CTRL_REQ_STRU */
    ID_GPHY_TOOL_INTRA_MSG_RPT_CTRL_CNF         = 0xE055,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU */

    ID_TOOL_GPHY_AMR_REPORT_REQ                 = 0xE057,                       /* _H2ASN_MsgChoice  GPHY_TOOL_AMR_REPORT_REQ_STRU */
    ID_GPHY_TOOL_AMR_REPORT_CNF                 = 0xE058,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU */
    ID_GPHY_TOOL_AMR_REPORT_IND                 = 0xE059,                       /* _H2ASN_MsgChoice  GPHY_TOOL_AMR_REPORT_IND_STRU */

    ID_TOOL_GPHY_BLK_REPORT_LIST_REQ            = 0xE05A,                       /* _H2ASN_MsgChoice  GPHY_TOOL_BLK_REPORT_LIST_REQ_STRU */
    ID_GPHY_TOOL_BLK_REPORT_LIST_CNF            = 0xE05B,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU */
    ID_GPHY_TOOL_BLK_REPORT_LIST_IND            = 0xE05C,                       /* _H2ASN_MsgChoice  GPHY_TOOL_BLK_REPORT_LIST_IND_STRU */

    ID_GPHY_TOOL_GTC_TASK_INFO_IND              = 0xE061,                       /* _H2ASN_MsgChoice GPHY_GTC_CONTEXT_STRU */
    ID_GPHY_TOOL_RCV_SINGAL_INFO_IND            = 0xE062,                       /* _H2ASN_MsgChoice GPHY_TOOL_RCV_SINGAL_INFO_REQ_STRU */
    ID_GPHY_TOOL_CS_UL_INFO_IND                 = 0xE064,                       /* _H2ASN_MsgChoice GSM_CHN_UL_INFO_RPT_STRU */
    ID_GPHY_TOOL_CS_DL_INFO_IND                 = 0xE065,                       /* _H2ASN_MsgChoice COM_CS_DECODE_CTRL_INFO_STRU */

    ID_UPHY_TOOL_DCXO_TEMP_COMP_INFO_IND        = 0xE066,                       /* _H2ASN_MsgChoice UPHY_TOOL_DCXO_TEMP_COMP_INFO_IND_STRU */

    ID_GPHY_TOOL_RF_RESOURCE_ERR_IND            = 0xE067,                       /* _H2ASN_MsgChoice  GPHY_DRV_CPU_CFG_RF_FLG_STRU*/
    ID_GPHY_TOOL_RF_DSDS_WAKE_REPORT            = 0xE068,                       /* _H2ASN_MsgChoice  GPHY_DRV_CPU_CFG_RF_FLG_STRU*/
    ID_GPHY_TOOL_RF_DSDS_SLEEP_REPORT           = 0xE069,                       /* _H2ASN_MsgChoice  GPHY_DRV_CPU_CFG_RF_FLG_STRU*/
    ID_GPHY_TOOL_GRA_TASK_INFO_IND              = 0xE06A,                       /* _H2ASN_MsgChoice */

    /* GmeasW GBGW分沟信息上报 */
    ID_GPHY_TOOL_GMEASW_SCHEDULE_INT7_IND       = 0xE06B,                       /* _H2ASN_MsgChoice GPHY_GMEASW_SCHEDULE_INFO_STRU */
    ID_GPHY_TOOL_GBGW_SCHEDULE_INT7_IND         = 0xE06C,                       /* _H2ASN_MsgChoice GPHY_BGW_SCHEDULE_INFO_STRU */

    ID_GPHY_TOOL_MASTER_WAKE_INFO_IND           = 0xE06D,                       /* _H2ASN_MsgChoice  UPHY_GDRX_MASTER_MNTN_STRU */
    ID_GPHY_TOOL_SLAVE_WAKE_INFO_IND            = 0xE06E,                       /* _H2ASN_MsgChoice  UPHY_GDRX_SLAVE_MNTN_STRU */
    ID_GPHY_TOOL_DCOFFSET_UPDATE_IND            = 0xE06F,                       /* _H2ASN_MsgChoice  GPHY_TOOL_DC_OFFSET_REPORT_STRU */

    /* G从模测量信息打印 */
    ID_GPHY_TOOL_SLAVE_MEAS_INFO_IND            = 0xE073,                       /* _H2ASN_MsgChoice  GPHY_TOOL_DUAL_ANT_DELAY_IND_STRU *//* 上报G从模测量信息 */

    ID_GPHY_TOOL_DCH_OCCASION_USE_RPT_IND       = 0xE074,
    ID_GPHY_TOOL_NCELL_BSIC_SEARCH_STATE_IND    = 0xE075,
    ID_GPHY_TOOL_NCELL_BSIC_VERIFY_STATE_IND    = 0xE076,
    ID_GPHY_TOOL_NCELL_INTERRAT_RANK_IND        = 0xE077,
    ID_GPHY_TOOL_NCELL_PREDICT_TASK_IND         = 0xE078,
    ID_GPHY_TOOL_CHN_DUMMY_PCH_RPT_IND          = 0xE079,

    /* 时间平均SAR消息上报 */
    ID_GPHY_TOOL_TIME_AVG_SAR_PERIOD_IND        = 0xE097,                       /* _H2ASN_MsgChoice  GPHY_TOOL_TIME_AVG_SAR_PERIOD_IND_STRU */
    ID_GPHY_TOOL_TIME_AVG_SAR_DPR_ON_IND        = 0xE098,                       /* _H2ASN_MsgChoice  GPHY_TOOL_TIME_AVG_SAR_DPR_STATE_IND_STRU */
    ID_GPHY_TOOL_TIME_AVG_SAR_DPR_OFF_IND       = 0xE099,                       /* _H2ASN_MsgChoice  GPHY_TOOL_TIME_AVG_SAR_DPR_STATE_IND_STRU */

    /* G从模SRVCC场景调度信息打印 */
    ID_GPHY_TOOL_SLAVE_BSIC_SYNC_RSLT_IND       = 0xE09A,                       /* _H2ASN_MsgChoice  GPHY_SLAVE_BSIC_SYNC_RSLT_STRU */
    ID_GPHY_TOOL_SLAVE_SRVCC_SCHDL_INFO_IND     = 0xE09B,                       /* _H2ASN_MsgChoice  GPHY_TOOL_DUAL_ANT_DELAY_IND_STRU *//* 上报G从模测量信息 */
    ID_GPHY_TOOL_INTERFE_STOP_G_BLANKING_IND    = 0xE09C,                       /* _H2ASN_MsgChoice  COM_GPHY_INTERFE_INFO_STRU *//* G关闭TX/RX操作 */
    ID_GPHY_TOOL_REPORT_INFO_IND                = 0xE0F7,                       /* _H2ASN_MsgChoice  GPHY_TOOL_REPORT_ERROR_IND_STRU */
    ID_GPHY_TOOL_REPORT_WARNING_IND             = 0xE0F8,                       /* _H2ASN_MsgChoice  GPHY_TOOL_REPORT_ERROR_IND_STRU */
    ID_GPHY_TOOL_REPORT_ERROR_IND               = 0xE0F9,                       /* _H2ASN_MsgChoice  GPHY_TOOL_REPORT_ERROR_IND_STRU */

    ID_TOOL_GPHY_BBP_RTC_REQ                    = 0xE0FA,                       /* _H2ASN_MsgChoice GPHY_TOOL_BBP_RTC_REQ_STRU  */
    ID_GPHY_TOOL_BBP_RTC_CNF                    = 0xE0FB,                       /* _H2ASN_MsgChoice GPHY_TOOL_COMMON_CNF_STRU  */

    /* DSP-PROBE */
    ID_TOOL_GPHY_GSM_CELL_SNR_REQ               = 0xE600,                       /* _H2ASN_MsgChoice  GPHY_TOOL_GSM_CELL_SNR_REQ_STRU *//* 该命令用于请求上报服务小区和6强邻区的信噪比，测量值 */
    ID_GPHY_TOOL_GSM_CELL_SNR_CNF               = 0xE601,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU *//* 回复确认消息 */
    ID_GPHY_TOOL_GSM_CELL_SNR_IND               = 0xE602,                       /* _H2ASN_MsgChoice  GPHY_TOOL_GSM_CELL_SNR_IND_STRU *//* 上报服务小区和6强邻区的信噪比，测量值 */

    ID_TOOL_GPHY_BA_LIST_MEAS_REQ               = 0xE603,                       /* _H2ASN_MsgChoice  GPHY_TOOL_BA_LIST_MEAS_REQ_STRU *//* 该命令用于请求上报服务区和32个邻区的信号强度，bsic值 */
    ID_GPHY_TOOL_BA_LIST_MEAS_CNF               = 0xE604,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU *//* 回复确认消息 */
    ID_GPHY_TOOL_BA_LIST_MEAS_IND               = 0xE605,                       /* _H2ASN_MsgChoice  GPHY_TOOL_BA_LIST_MEAS_IND_STRU *//* 上报服务区和32个邻区的信号强度，bsic值 */

    ID_TOOL_GPHY_AMR_SETTING_REQ                = 0xE606,                       /* _H2ASN_MsgChoice  GPHY_TOOL_AMR_SETTING_REQ_STRU *//* 该命令用于请求上报AMR配置信息 */
    ID_GPHY_TOOL_AMR_SETTING_CNF                = 0xE607,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU *//* 回复确认消息 */
    ID_GPHY_TOOL_AMR_SETTING_IND                = 0xE608,                       /* _H2ASN_MsgChoice  GPHY_TOOL_AMR_SETTING_IND_STRU *//* 上报AMR配置信息 */

    ID_TOOL_GPHY_AMR_CODEC_USAGE_REQ            = 0XE609,                       /* _H2ASN_MsgChoice  GPHY_TOOL_AMR_CODEC_USAGE_REQ_STRU *//* 该命令用于请求上报激活集中每个语音速率的使用率 */
    ID_GPHY_TOOL_AMR_CODEC_USAGE_CNF            = 0XE60A,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU *//* 回复确认消息 */
    ID_GPHY_TOOL_AMR_CODEC_USAGE_IND            = 0XE60B,                       /* _H2ASN_MsgChoice  GPHY_TOOL_AMR_CODEC_USAGE_IND_STRU *//* 上报激活集中每个语音速率的使用率上 */

    ID_TOOL_GPHY_AMR_CODEC_STAT_REQ             = 0xE60C,                       /* _H2ASN_MsgChoice  GPHY_TOOL_AMR_CODEC_STAT_REQ_STRU *//* 该命令用于请求各个编码速率的使用率 */
    ID_GPHY_TOOL_AMR_CODEC_STAT_CNF             = 0xE60D,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU *//* 回复确认消息 */
    ID_GPHY_TOOL_AMR_CODEC_STAT_IND             = 0xE60E,                       /* _H2ASN_MsgChoice  GPHY_TOOL_AMR_CODEC_STAT_IND_STRU *//* 上报各个编码速率的使用率 */

    ID_TOOL_GPHY_CS_PS_TX_INFO_REQ              = 0xE60F,                       /* _H2ASN_MsgChoice  GPHY_TOOL_CS_TX_INFO_REQ_STRU *//* 该命令用于请求上报CS域上行信息 */
    ID_GPHY_TOOL_CS_PS_TX_INFO_CNF              = 0xE610,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU *//* 回复确认消息 */
    ID_GPHY_TOOL_CS_PS_TX_INFO_IND              = 0xE611,                       /* _H2ASN_MsgChoice  GPHY_TOOL_CS_TX_INFO_IND_STRU *//* 上报CS域上行信息 */

    ID_TOOL_GPHY_CS_FER_REQ                     = 0xE612,                       /* _H2ASN_MsgChoice  GPHY_TOOL_CS_FER_REQ_STRU *//* 该命令请求上报CS域的FER */
    ID_GPHY_TOOL_CS_FER_CNF                     = 0xE613,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU *//* 回复确认消息 */
    ID_GPHY_TOOL_CS_FER_IND                     = 0xE614,                       /* _H2ASN_MsgChoice  GPHY_TOOL_CS_FER_IND_STRU *//* 上报CS域的FER */

    ID_TOOL_GPHY_GET_CURRENT_DSC_REQ            = 0xE615,                       /* _H2ASN_MsgChoice  GPHY_TOOL_GET_CURRENT_DSC_REQ_STRU *//* 该命令请求上报DSC计数值 */
    ID_GPHY_TOOL_GET_CURRENT_DSC_CNF            = 0xE616,                       /* _H2ASN_MsgChoice  GPHY_TOOL_COMMON_CNF_STRU *//* 回复确认消息 */
    ID_GPHY_TOOL_GET_CURRENT_DSC_IND            = 0xE617,                       /* _H2ASN_MsgChoice  GPHY_TOOL_GET_CURRENT_DSC_IND_STRU *//* 上报DSC计数值 */

    ID_GPHY_TOOL_MASTER_WAKE_LTE_IND            = 0xE620,
    ID_GPHY_TOOL_MASTER_START_LTE_MEAS_IND      = 0xE621,
    ID_GPHY_TOOL_MASTER_REPORT_LTE_MEAS_IND     = 0xE622,
    ID_GPHY_TOOL_MASTER_STOP_LTE_MEAS_IND       = 0xE623,
    ID_GPHY_TOOL_SET_LTE_MEAS_FLAG_IND          = 0xE624,
    ID_GPHY_TOOL_CLEAR_LTE_MEAS_FLAG_IND        = 0xE625,

    ID_GPHY_TOOL_MASTER_WAKE_TDS_IND            = 0xE630,
    ID_GPHY_TOOL_MASTER_START_TDS_MEAS_IND      = 0xE631,
    ID_GPHY_TOOL_MASTER_REPORT_TDS_MEAS_IND     = 0xE632,
    ID_GPHY_TOOL_MASTER_STOP_TDS_MEAS_IND       = 0xE633,
    ID_GPHY_TOOL_SET_TDS_MEAS_FLAG_IND          = 0xE634,
    ID_GPHY_TOOL_CLEAR_TDS_MEAS_FLAG_IND        = 0xE635,

    /* 双天线判决结果消息上报 */
    ID_GPHY_TOOL_DUAL_ANT_ESTIMATE_IND          = 0xE640,                       /* _H2ASN_MsgChoice  GPHY_TOOL_DUAL_ANT_ESTIMATE_IND_STRU *//* 上报主天线能量评估阶段判决信息 */
    ID_GPHY_TOOL_DUAL_ANT_COMPARE_IND           = 0xE641,                       /* _H2ASN_MsgChoice  GPHY_TOOL_DUAL_ANT_COMPARE_IND_STRU *//* 上报主辅天线能量比较阶段每个调度状态的判决信息 */
    ID_GPHY_TOOL_DUAL_ANT_DELAY_IND             = 0xE642,                       /* _H2ASN_MsgChoice  GPHY_TOOL_DUAL_ANT_DELAY_IND_STRU *//* 上报天线切换迟滞信息 */
    ID_GPHY_TOOL_DUAL_ANT_CPMPARE_SUB_IND       = 0xE643,                       /* _H2ASN_MsgChoice  GPHY_TOOL_DUAL_ANT_COMPARE_SUB_IND_STRU *//* 二阶并行算法每个上报周期主辅天线能量比较阶段判决信息 */
    ID_GPHY_TOOL_MAS_CHANGE_ANT_IND             = 0xE644,                       /* _H2ASN_MsgChoice  GPHY_TOOL_MAS_CHANGE_ANT_IND_STRU *//* MAS切换天线信息 */

    ID_GPHY_TOOL_MSG_ID_BUTT
};
typedef VOS_UINT16 GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16;


/*****************************************************************************
 GPHY回复CNF时,携带的处理结果枚举
*****************************************************************************/
enum GPHY_TOOL_MNTN_RSLT_ENUM
{
    GPHY_MNTN_RSLT_SUCC                         = 0,
    GPHY_MNTN_RSLT_FAIL                         = 1,

    GPHY_MNTN_RSLT_BUTT
};
typedef VOS_UINT16 GPHY_TOOL_MNTN_RSLT_ENUM_UINT16;



/*****************************************************************************
 TOOL下发参数控制，主要是功率控制和BEP控制
*****************************************************************************/
enum GPHY_TOOL_PARA_CTRL_ENUM
{
    GPHY_TOOL_PARA_PWC_CTRL                     = 0x01,                         /* 下发控制功率参数 */
    GPHY_TOOL_PARA_BEP_CTRL                     = 0x02,                         /* 下发控制BEP参数 */

    GPHY_TOOL_PARA_CTRL_BUTT
};
typedef VOS_UINT16 GPHY_TOOL_PARA_CTRL_ENUM_UINT16;



/*****************************************************************************
 枚举名    : GPHY_TOOL_MNTN_ERROR_RPT_LEVEL_ENUM_UINT16
 协议表格  :
 枚举说明  : GPHY错误上报级别
*****************************************************************************/
enum GPHY_TOOL_ERROR_RPT_LEVEL_ENUM
{
    GPHY_TOOL_ERROR_LEVEL_INFO                  = 1,
    GPHY_TOOL_ERROR_LEVEL_WARNING               = 2,
    GPHY_TOOL_ERROR_LEVEL_ERROR                 = 3,

    GPHY_TOOL_ERROR_LEVEL_BUTT
};
typedef VOS_UINT16 GPHY_TOOL_ERROR_RPT_LEVEL_ENUM_UINT16;






/*****************************************************************************
 GPHY模块定义
*****************************************************************************/

enum GPHY_TOOL_MODULE_ENUM
{
    GPHY_MODULE_DRV                             = 0x5501,                       /* DRIVER模块名编号 */
    GPHY_MODULE_MEA                             = 0x5502,                       /* 测量模块名编号 */
    GPHY_MODULE_NCE_TSK                         = 0x5503,                       /* 邻区任务模块名编号 */
    GPHY_MODULE_NCE_RES                         = 0x5504,                       /* 邻区重选模块名编号 */
    GPHY_MODULE_CHN_CCH                         = 0x5505,                       /* 公共信道模块名编号 */
    GPHY_MODULE_CHN_CSDCH                       = 0x5506,                       /* CS专用信道模块名编号 */
    GPHY_MODULE_CHN_PSDCH                       = 0x5507,                       /* PS专用信道模块名编号 */
    GPHY_MODULE_CHN_AMRDTX                      = 0x5508,                       /* 信道AMRDTX模块名编号 */
    GPHY_MODULE_COM                             = 0x5509,                       /* 公共模块名编号 */
    GPHY_MODULE_COM_MAIL                        = 0x550A,                       /* 公共邮箱模块名编号 */
    GPHY_MODULE_COM_TOA                         = 0x550B,                       /* 公共TOA模块名编号 */
    GPHY_MODULE_DRX                             = 0x550C,                       /* DRX模块名编号 */
    GPHY_MODULE_OM                              = 0x550D,                       /* OM模块名编号 */
    GPHY_MODULE_WMEAS                           = 0x550E,                       /* WMEAS模块名编号 */
    GPHY_MODULE_CAL                             = 0x550F,                       /* CAL模块名编号 */
    GPHY_MODULE_LMEAS                           = 0x5510,                       /* LTE测量模块名编号 */
    GPHY_MODULE_PD_INTERFACE                    = 0x5511,                       /* 下电部分代码接口函数模块 */
    GPHY_MODULE_TMEAS                           = 0x5512,                       /* TD测量模块名编号 */
    GPHY_MODULE_BUTT

};
typedef VOS_UINT16 GPHY_TOOL_MODULE_ENUM_UINT16;


/*****************************************************************************
  3.2 枚举定义,WPHY枚举定义
*****************************************************************************/


/*****************************************************************************
 WPHY<-->TOOL原语列表
*****************************************************************************/

enum WPHY_TOOL_MNTN_MSG_ID_ENUM
{
    /* 下发REQ消息因为带VOS消息，上报的IND或CNF消息不带VOS消息头，应对REQ另外解析，这里指示为了ASN生成方便 */
    ID_TOOL_WPHY_REQ                            = 0x0,                          /* _H2ASN_MsgChoice TOOL_WPHY_REQ_STRU */

    /* 信令模式下实时修改PA增益切换点补偿的请求和回复原语 */
    ID_TOOL_WPHY_RF_PA_GAIN_SWITCH_COMP_REQ     = 0xC801,                       /* _H2ASN_MsgChoice WPHY_TOOL_PA_GAIN_SWITCH_COMP_REQ_STRU */
    ID_WPHY_TOOL_RF_PA_GAIN_SWITCH_COMP_CNF     = 0xC802,                       /* _H2ASN_MsgChoice WPHY_TOOL_PA_GAIN_SWITCH_COMP_CNF_STRU */

    /* 信令模式下PD使能控制 */
    ID_TOOL_WPHY_PD_ENABLE_REQ                  = 0xC803,                       /* _H2ASN_MsgChoice WPHY_TOOL_POW_DET_ENABLE_REQ_STRU */
    ID_WPHY_TOOL_PD_ENABLE_CNF                  = 0xC804,                       /* _H2ASN_MsgChoice WPHY_TOOL_POW_DET_ENABLE_CNF_STRU */

    /* 激活集小区上报  */
    ID_TOOL_WPHY_ACT_CELL_REQ                   = 0xF001,                       /* _H2ASN_MsgChoice WPHY_TOOL_ACT_CELL_REQ_STRU */
    ID_WPHY_TOOL_ACT_CELL_CNF                   = 0xF002,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_ACT_CELL_IND                   = 0xF003,                       /* _H2ASN_MsgChoice WPHY_TOOL_ACT_CELL_INFO_IND_STRU */

    /* 小区搜索列表上报 */
    ID_TOOL_WPHY_CELL_SEARCH_LIST_REQ           = 0xF004,                       /* _H2ASN_MsgChoice WPHY_TOOL_CELL_SEARCH_LIST_REQ_STRU  */
    ID_WPHY_TOOL_CELL_SEARCH_LIST_CNF           = 0xF005,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_CELL_SEARCH_LIST_IND           = 0xF006,                       /* _H2ASN_MsgChoice WPHY_TOOL_CELL_SEARCH_LIST_IND_STRU */


    /* 功控开关控制 */
    ID_TOOL_WPHY_PWR_SWITCH_CTRL_REQ            = 0xF00A,                       /* _H2ASN_MsgChoice WPHY_TOOL_PWR_SWITCH_CTRL_REQ_STRU */
    ID_WPHY_TOOL_PWR_SWITCH_CTRL_CNF            = 0xF00B,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */

    /* 功控参数控制 */
    ID_TOOL_WPHY_PWR_PARA_SET_REQ               = 0xF010,                       /* _H2ASN_MsgChoice WPHY_TOOL_PWR_PARA_SET_REQ_STRU */
    ID_WPHY_TOOL_PWR_PARA_SET_CNF               = 0xF011,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */


    /* 误块率上报 */
    ID_TOOL_WPHY_BLER_REPORT_REQ                = 0xF020,                       /* _H2ASN_MsgChoice WPHY_TOOL_BLER_REPORT_REQ_STRU */
    ID_WPHY_TOOL_BLER_REPORT_CNF                = 0xF021,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_BLER_REPORT_IND                = 0xF022,                       /* _H2ASN_MsgChoice WPHY_TOOL_BLER_REPORT_IND_STRU */


    /* 事件上报 */
    ID_TOOL_WPHY_EVENT_REPORT_REQ               = 0xF02A,                       /* _H2ASN_MsgChoice WPHY_TOOL_EVENT_REPORT_REQ_STRU */
    ID_WPHY_TOOL_EVENT_REPORT_CNF               = 0xF02B,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */

    /* 事件上报:同失步上报 */
    ID_WPHY_TOOL_SYNC_STATUS_IND                = 0xF02C,                       /* _H2ASN_MsgChoice WPHY_TOOL_SYNC_STATUS_IND_STRU */

    /* 事件上报:AFC状态 */
    ID_WPHY_TOOL_VCTCXO_STATUS_IND              = 0xF02E,                       /* _H2ASN_MsgChoice WPHY_TOOL_AFC_STATUS_IND_STRU */

    /* 事件上报:中断任务异常报告 */
    ID_WPHY_TOOL_INTERRUPT_EXCEPTIION_IND       = 0xF030,                       /* _H2ASN_MsgChoice WPHY_TOOL_INTERRUPT_EXCEPTIION_IND_STRU */

    /* 事件上报:L1状态上报 */
    ID_WPHY_TOOL_WCDMA_L1_STATUS_IND            = 0xF031,                       /* _H2ASN_MsgChoice WPHY_TOOL_WCDMA_L1_STATUS_IND_STRU */

    /* DRX控制 */
    ID_TOOL_WPHY_DRX_SWITCH_REQ                 = 0xF032,                       /* _H2ASN_MsgChoice WPHY_TOOL_DRX_SWITCH_REQ_STRU */
    ID_WPHY_TOOL_DRX_SWITCH_CNF                 = 0xF033,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */

    /* 门限设置 */
    ID_TOOL_WPHY_THRESHOLD_SET_REQ              = 0xF034,                       /* _H2ASN_MsgChoice WPHY_TOOL_THRESHOLD_SET_REQ_STRU */
    ID_WPHY_TOOL_THRESHOLD_SET_CNF              = 0xF035,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */

    /* 门限查询 */
    ID_TOOL_WPHY_THRESHOLD_QUERY_REQ            = 0xF036,                       /* _H2ASN_MsgChoice WPHY_TOOL_THRESHOLD_QUERY_REQ_STRU */
    ID_WPHY_TOOL_THRESHOLD_QUERY_IND            = 0xF037,                       /* _H2ASN_MsgChoice WPHY_TOOL_THRESHOLD_QUERY_IND_STRU */

    /* 错误上报 */
    ID_TOOL_WPHY_ERROR_REPORT_REQ               = 0xF038,                       /* _H2ASN_MsgChoice WPHY_TOOL_ERROR_REPORT_REQ_STRU */
    ID_WPHY_TOOL_ERROR_REPORT_CNF               = 0xF039,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_ERROR_REPORT_IND               = 0xF03A,                       /* _H2ASN_MsgChoice WPHY_TOOL_ERROR_REPORT_IND_STRU  */
    ID_WPHY_TOOL_WARNING_REPORT_IND             = 0xF03B,                       /* _H2ASN_MsgChoice WPHY_TOOL_ERROR_REPORT_IND_STRU  */
    ID_WPHY_TOOL_INFO_REPORT_IND                = 0xF03C,                       /* _H2ASN_MsgChoice WPHY_TOOL_ERROR_REPORT_IND_STRU  */


    ID_TOOL_WPHY_RF_FRONT_END_PARA_REQ          = 0xF03D,                       /* _H2ASN_MsgChoice WPHY_TOOL_RF_FRONT_END_PARA_REQ_STRU  */
    ID_WPHY_TOOL_RF_FRONT_END_PARA_CNF          = 0xF03E,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU  */
    ID_WPHY_TOOL_RF_FRONT_END_PARA_IND          = 0xF03F,                       /* _H2ASN_MsgChoice WPHY_TOOL_RF_FRONT_END_PARA_IND_STRU  */

    ID_WPHY_TOOL_PI_INT_RESULT_IND              = 0xF040,                       /* _H2ASN_MsgChoice WPHY_TOOL_PI_INT_RESULT_IND_STRU  */
    ID_WPHY_TOOL_AI_INT_RESULT_IND              = 0xF041,                       /* _H2ASN_MsgChoice WPHY_TOOL_AI_INT_RESULT_IND_STRU  */

    /* T313 状态上报 */
    ID_WPHY_TOOL_T313_STATUS_IND                = 0xF042,                       /* _H2ASN_MsgChoice WPHY_TOOL_T313_STATUS_IND_STRU  */
    /* T312 状态上报 */
    ID_WPHY_TOOL_T312_STATUS_IND                = 0xF043,                       /* _H2ASN_MsgChoice WPHY_TOOL_T312_STATUS_IND_STRU */

    /* PA状态上报 */
    ID_TOOL_WPHY_PA_STATUS_REPORT_REQ           = 0xF046,                       /* _H2ASN_MsgChoice WPHY_TOOL_PA_STATUS_REPORT_REQ_STRU */
    ID_WPHY_TOOL_PA_STATUS_REPORT_CNF           = 0xF047,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_PA_STATUS_REPORT_IND           = 0xF048,                       /* _H2ASN_MsgChoice WPHY_TOOL_PA_STATUS_REPORT_IND_STRU */

    ID_TOOL_WPHY_INTRA_MSG_RPT_CTRL_REQ         = 0xF049,                       /* _H2ASN_MsgChoice WPHY_TOOL_INTRA_MSG_RPT_CTRL_REQ_STRU */
    ID_WPHY_TOOL_INTRA_MSG_RPT_CTRL_CNF         = 0xF04A,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */

    /* 维测消息bitmap开关 */
    ID_WPHY_TOOL_FUNC_BIT_CONTROL_REQ           = 0xF050,                       /* _H2ASN_MsgChoice  WPHY_TOOL_FUNC_BIT_CONTROL_REQ_STRU */
    ID_WPHY_TOOL_FUNC_BIT_CONTROL_CNF           = 0xF051,                       /* _H2ASN_MsgChoice  WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_FET_OPEN_RPT_IND               = 0xF052,                       /* _H2ASN_MsgChoice WPHY_TOOL_FET_OPEN_IND_STRU */
    ID_WPHY_TOOL_FET_CLOSE_RPT_IND              = 0xF053,                       /* _H2ASN_MsgChoice WPHY_TOOL_FET_CLOSE_IND_STRU */
    ID_WPHY_TOOL_FREE_MNTN_RPT_IND              = 0xF054,                       /* _H2ASN_MsgChoice WPHY_TOOL_FREE_MNTN_RPT_STRU */

    ID_WPHY_TOOL_SAR_TIME_AVG_DPR_ON_IND        = 0xF055,                       /* _H2ASN_MsgChoice WPHY_TOOL_SAR_TIME_AVG_DPR_EVENT_IND_STRU */
    ID_WPHY_TOOL_SAR_TIME_AVG_DPR_OFF_IND       = 0xF056,                       /* _H2ASN_MsgChoice WPHY_TOOL_SAR_TIME_AVG_DPR_EVENT_IND_STRU */
    ID_WPHY_TOOL_SAR_TIME_AVG_PARA_INFO_IND     = 0xF057,                       /* _H2ASN_MsgChoice WPHY_TOOL_SAR_TIME_AVG_PARA_INFO_STRU */

    ID_TOOL_WPHY_READ_MEM_REQ                   = 0xF058,                       /* _H2ASN_MsgChoice WPHY_TOOL_READ_MEM_REQ_STRU */
    ID_WPHY_TOOL_READ_MEM_CNF                   = 0xF059,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_READ_MEM_IND                   = 0xF05A,                       /* _H2ASN_MsgChoice WPHY_TOOL_READ_MEM_IND_STRU */

    /* 前端可维可测 */
    ID_TOOL_WPHY_RF_FRONT_STATIC_REQUIRE_REQ    = 0xF070,                       /* _H2ASN_MsgChoice WPHY_TOOL_RF_FRONT_END_STATIC_REQUIRE_REQ_STRU  */
    ID_WPHY_TOOL_RF_FRONT_STATIC_REQUIRE_IND    = 0xF071,                       /* _H2ASN_MsgChoice WPHY_TOOL_RF_FRONT_END_STATIC_REQUIRE_IND_STRU  */

    ID_TOOL_WPHY_BBP_RTC_REQ                    = 0xF072,                       /* _H2ASN_MsgChoice WPHY_TOOL_BBP_RTC_REQ_STRU  */
    ID_WPHY_TOOL_BBP_RTC_CNF                    = 0xF073,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU  */

    ID_TOOL_WPHY_RF_FRONT_DISPLAY_REQ           = 0xF075,                       /* _H2ASN_MsgChoice WPHY_TOOL_RF_FRONT_END_DISPLAY_REQ_STRU  */
    ID_WPHY_TOOL_RF_FRONT_DISPLAY_CNF           = 0xF077,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */


    ID_TOOL_WPHY_RAM_REPORT_REQ                 = 0xF078,                       /* _H2ASN_MsgChoice WPHY_TOOL_RAM_REPORT_REQ_STRU  */
    ID_WPHY_TOOL_RAM_REPORT_CNF                 = 0xF079,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU  */
    ID_WPHY_TOOL_RAM_REPORT_IND                 = 0xF07A,                       /* _H2ASN_MsgChoice WPHY_TOOL_RAM_REPORT_IND_STRU  */

    ID_TOOL_WPHY_BLK_REPORT_LIST_REQ            = 0xF07B,                       /* _H2ASN_MsgChoice WPHY_TOOL_BLK_REPORT_LIST_REQ_STRU  */
    ID_WPHY_TOOL_BLK_REPORT_LIST_CNF            = 0xF07C,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU  */
    ID_WPHY_TOOL_BLK_REPORT_LIST_IND            = 0xF07D,                       /* _H2ASN_MsgChoice WPHY_TOOL_BLK_REPORT_LIST_IND_STRU  */

    ID_TOOL_WPHY_RA_MNTN_CTRL_REQ               = 0xF07E,                       /* _H2ASN_MsgChoice WPHY_TOOL_RA_MNTN_CTRL_REQ_STRU */
    ID_WPHY_TOOL_RA_MNTN_CTRL_CNF               = 0xF07F,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU  */

    ID_TOOL_WPHY_ARM_0MS_MNTN_CTRL_REQ          = 0xF080,                       /* _H2ASN_MsgChoice WPHY_TOOL_ARM_0MS_MNTN_CTRL_REQ_STRU */
    ID_WPHY_TOOL_ARM_0MS_MNTN_CTRL_CNF          = 0xF081,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU  */

    ID_WPHY_TOOL_SLAVE_CDRX_START_IND           = 0xF082,                       /* _H2ASN_MsgChoice WPHY_TOOL_SLAVE_CDRX_START_IND_STRU  */
    ID_WPHY_TOOL_SLAVE_CDRX_STOP_IND            = 0xF083,                       /* _H2ASN_MsgChoice WPHY_TOOL_SLAVE_CDRX_STOP_IND_STRU  */
    ID_WPHY_TOOL_SLAVE_W_FINISH_IND             = 0xF084,                       /* _H2ASN_MsgChoice WPHY_TOOL_SLAVE_W_FINISH_IND_STRU */
    ID_WPHY_TOOL_SLAVE_GRSSI_FINISH_IND         = 0xF085,                       /* _H2ASN_MsgChoice WPHY_TOOL_SLAVE_GRSSI_FINISH_IND_STRU */
    ID_WPHY_TOOL_SLAVE_GBSIC_FINISH_IND         = 0xF086,                       /* _H2ASN_MsgChoice WPHY_TOOL_SLAVE_GBSIC_FINISH_IND_STRU */
    ID_WPHY_TOOL_SLAVE_SCHEDULE_TIMEOUT_IND     = 0xF087,                       /* _H2ASN_MsgChoice WPHY_TOOL_SLAVE_SCHEDULE_TIMEOUT_IND_STRU */
    ID_WPHY_TOOL_SLAVE_SCHEDULE_STATUS_IND      = 0xF088,                       /* _H2ASN_MsgChoice WPHY_TOOL_SLAVE_SCHEDULE_STATUS_IND_STRU */

    ID_WPHY_TOOL_MASTER_WAKE_LTE_IND            = 0xF090,                       /* _H2ASN_MsgChoice WPHY_TOOL_MASTER_WAKE_LTE_IND_STRU */
    ID_WPHY_TOOL_MASTER_START_LTE_MEAS_IND      = 0xF091,                       /* _H2ASN_MsgChoice WPHY_TOOL_MASTER_START_LTE_MEAS_IND_STRU */
    ID_WPHY_TOOL_MASTER_REPORT_LTE_MEAS_IND     = 0xF092,                       /* _H2ASN_MsgChoice WPHY_TOOL_MASTER_REPORT_LTE_MEAS_IND_STRU */
    ID_WPHY_TOOL_MASTER_STOP_LTE_MEAS_IND       = 0xF093,                       /* _H2ASN_MsgChoice WPHY_TOOL_MASTER_STOP_LTE_MEAS_IND_STRU */
    ID_WPHY_TOOL_SET_LTE_MEAS_FLAG_IND          = 0xF094,                       /* _H2ASN_MsgChoice WPHY_TOOL_SET_LTE_MEAS_FLAG_IND_STRU */
    ID_WPHY_TOOL_MASTER_RF_CONFIG_IND           = 0xF095,                       /* _H2ASN_MsgChoice WPHY_TOOL_SET_LTE_MEAS_FLAG_IND_STRU */
    ID_WPHY_TOOL_UPA_INFO_RPT_IND               = 0xF096,                       /* _H2ASN_MsgChoice WPHY_TOOL_UPA_RPT_INFO_STRU */

    ID_WPHY_TOOL_QPC_OPEN_UL_IND                = 0xF0A0,                       /* _H2ASN_MsgChoice WPHY_TOOL_QPC_OPEN_UL_IND_STRU */
    ID_WPHY_TOOL_QPC_CLOSE_UL_IND               = 0xF0A1,                       /* _H2ASN_MsgChoice WPHY_TOOL_QPC_CLOSE_UL_IND_STRU */
    ID_WPHY_TOOL_QPC_RRC_STATE_IND              = 0xF0A2,                       /* _H2ASN_MsgChoice WPHY_TOOL_QPC_RRC_STATE_IND_STRU */
    ID_WPHY_TOOL_QPC_RB_TYPE_IND                = 0xF0A3,                       /* _H2ASN_MsgChoice WPHY_TOOL_QPC_RB_TYPE_IND_STRU */


    ID_WPHY_TOOL_MAS_MNTN_STATEI_IND            = 0xF0B0,                       /* _H2ASN_MsgChoice WPHY_TOOL_MAS_MNTN_STATEI_IND_STRU */
    ID_WPHY_TOOL_MAS_MNTN_STATEIAIB_IND         = 0xF0B1,                       /* _H2ASN_MsgChoice WPHY_TOOL_MAS_MNTN_STATEIAIB_IND_STRU */
    ID_WPHY_TOOL_MAS_MNTN_STATEII_IND           = 0xF0B2,                       /* _H2ASN_MsgChoice WPHY_TOOL_MAS_MNTN_STATEII_IND_STRU */

    ID_WPHY_TOOL_IDLE_MNTN_RPT_IND              = 0xF0B3,                       /* _H2ASN_MsgChoice WPHY_TOOL_IDLE_MNTN_RPT_STRU */
    ID_WPHY_TOOL_FACH_MNTN_RPT_IND              = 0xF0B4,                       /* _H2ASN_MsgChoice WPHY_TOOL_FACH_MNTN_RPT_STRU */
    ID_WPHY_TOOL_DCH_MNTN_RPT_IND               = 0xF0B5,                       /* _H2ASN_MsgChoice WPHY_TOOL_DCH_MNTN_RPT_STRU */

    ID_WPHY_TOOL_TAS_STATUS_STATE_REPORT_IND    = 0xF0B6,                       /* _H2ASN_MsgChoice WPHY_TOOL_TAS_STATUS_REPORT_IND_STRU */

    ID_WPHY_TOOL_PCCPCH_SCHEDULE_IND            = 0xF0B7,                       /* _H2ASN_MsgChoice WPHY_TOOL_RAKE_PCCPCH_SCHDL_INFO_STRU */
    ID_WPHY_TOOL_BCCH_QUEUE_IND                 = 0xF0B8,                       /* _H2ASN_MsgChoice WPHY_TOOL_RAKE_BCCH_QUEUE_INFO_STRU */
    ID_WPHY_TOOL_ADEMOD_QUEUE_IND               = 0xF0B9,                       /* _H2ASN_MsgChoice WPHY_TOOL_RAKE_ADEMOD_QUEUE_IND_STRU */
    ID_WPHY_TOOL_CPC_MNTN_RPT_IND               = 0xF0BA,                       /* _H2ASN_MsgChoice WPHY_TOOL_CPC_MNTN_RPT_STRU */

    ID_WPHY_TOOL_IC_CELL_LIST_RPT_REQ           = 0xF0BB,                       /* _H2ASN_MsgChoice WPHY_TOOL_IC_CELL_REPORT_REQ_STRU */
    ID_WPHY_TOOL_IC_CELL_LIST_RPT_CNF           = 0xF0BC,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_IC_CELL_LIST_RPT_IND           = 0xF0BD,                       /* _H2ASN_MsgChoice WPHY_TOOL_IC_CELL_REPORT_IND_STRU */

    ID_WPHY_TOOL_RTT_STATUS_RPT_REQ             = 0xF0BE,                       /* _H2ASN_MsgChoice WPHY_TOOL_RTT_STATUS_REPORT_REQ_STRU */
    ID_WPHY_TOOL_RTT_STATUS_RPT_CNF             = 0xF0BF,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_RTT_STATUS_RPT_IND             = 0xF0C0,                       /* _H2ASN_MsgChoice WPHY_TOOL_RTT_STATUS_REPORT_IND_STRU */

    ID_WPHY_TOOL_DPA_INFO_RPT_REQ               = 0xF0C1,                       /* _H2ASN_MsgChoice WPHY_TOOL_DPA_INFO_REQ_STRU */
    ID_WPHY_TOOL_DPA_INFO_RPT_CNF               = 0xF0C2,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_DPA_INFO_RPT_IND               = 0xF0C3,                       /* _H2ASN_MsgChoice WPHY_TOOL_DPA_INFO_IND_STRU */

    ID_WPHY_TOOL_HSSCCH_STATISTIC_RPT_REQ       = 0xF0C4,                       /* _H2ASN_MsgChoice WPHY_TOOL_HSSCCH_STATISTIC_REPORT_REQ_STRU */
    ID_WPHY_TOOL_HSSCCH_STATISTIC_RPT_CNF       = 0xF0C5,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_HSSCCH_STATISTIC_RPT_IND       = 0xF0C6,                       /* _H2ASN_MsgChoice WPHY_TOOL_HSSCCH_STATISTIC_REPORT_IND_STRU */

    ID_WPHY_TOOL_HSDSCH_STATISTIC_RPT_REQ       = 0xF0C7,                       /* _H2ASN_MsgChoice WPHY_TOOL_HSDSCH_STATISTIC_REPORT_REQ_STRU */
    ID_WPHY_TOOL_HSDSCH_STATISTIC_RPT_CNF       = 0xF0C8,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_HSDSCH_STATISTIC_RPT_IND       = 0xF0C9,                       /* _H2ASN_MsgChoice WPHY_TOOL_HSDSCH_STATISTIC_REPORT_IND_STRU */
    ID_WPHY_TOOL_RX_FAST_CAL_MNTN_RPT_IND       = 0xF0CA,                       /* _H2ASN_MsgChoice WPHY_TOOL_RX_FAST_CAL_MNTN_RPT_STRU */
    ID_WPHY_TOOL_MAS_MNTN_STATEIII_IND          = 0xF0E1,                       /* _H2ASN_MsgChoice WPHY_TOOL_MAS_MNTN_STATEIII_IND_STRU */
    ID_WPHY_TOOL_MAS_MNTN_NONBLINDINFO_IND      = 0xF0E2,                       /* _H2ASN_MsgChoice WPHY_TOOL_MAS_MNTN_NONBLINDINFO_IND_STRU */
    ID_WPHY_TOOL_MAS_MNTN_MAS_SWITCH_IND        = 0xF0E3,                       /* _H2ASN_MsgChoice WPHY_TOOL_MAS_MNTN_NONBLINDINFO_IND_STRU */

    ID_WPHY_TOOL_PILOT_BER_RPT_REQ              = 0xF0E4,                       /* _H2ASN_MsgChoice WPHY_TOOL_PILOT_BER_REPORT_REQ_STRU */
    ID_WPHY_TOOL_PILOT_BER_RPT_CNF              = 0xF0E5,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_PILOT_BER_RPT_IND              = 0xF0E6,                       /* _H2ASN_MsgChoice WPHY_TOOL_PILOT_BER_REPORT_IND_STRU*/

    ID_WPHY_TOOL_TPC_AND_SIR_RPT_REQ            = 0xF0E7,                       /* _H2ASN_MsgChoice WPHY_TOOL_TPC_AND_SIR_REPORT_REQ_STRU */
    ID_WPHY_TOOL_TPC_AND_SIR_RPT_CNF            = 0xF0E8,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_TPC_AND_SIR_RPT_IND            = 0xF0E9,                       /* _H2ASN_MsgChoice WPHY_TOOL_TPC_AND_SIR_REPORT_IND_STRU */

    ID_WPHY_TOOL_POWER_RPT_REQ                  = 0xF0EA,                       /* _H2ASN_MsgChoice WPHY_TOOL_POWER_REPORT_REQ_STRU */
    ID_WPHY_TOOL_POWER_RPT_CNF                  = 0xF0EB,                       /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_POWER_RPT_IND                  = 0xF0EC,                       /* _H2ASN_MsgChoice WPHY_TOOL_POWER_REPORT_IND_STRU */

    ID_WPHY_TOOL_HSDPA_LINK_STATISTICS_RPT_REQ              = 0xF0ED,           /* _H2ASN_MsgChoice WPHY_TOOL_HSDPA_LINK_STATISTICS_REPORT_REQ_STRU */
    ID_WPHY_TOOL_HSDPA_LINK_STATISTICS_RPT_CNF              = 0xF0EE,           /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_HSDPA_LINK_STATISTICS_RPT_IND              = 0xF0EF,           /* _H2ASN_MsgChoice WPHY_TOOL_HSDPA_LINK_STATISTICS_REPORT_IND_STRU */

    ID_WPHY_TOOL_DUAL_ANTENNA_STATISTICS_RPT_REQ            = 0xF0F0,           /* _H2ASN_MsgChoice WPHY_TOOL_DUAL_ANTENNA_STATISTICS_REPORT_REQ_STRU */
    ID_WPHY_TOOL_DUAL_ANTENNA_STATISTICS_RPT_CNF            = 0xF0F1,           /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_DUAL_ANTENNA_STATISTICS_RPT_IND            = 0xF0F2,           /* _H2ASN_MsgChoice WPHY_TOOL_DUAL_ANTENNA_STATISTICS_REPORT_IND_STRU */

    ID_WPHY_TOOL_HSUPA_EDCH_ACTIVE_SET_RPT_REQ              = 0xF0F3,           /* _H2ASN_MsgChoice WPHY_TOOL_HSUPA_EDCH_ACTIVE_SET_REPORT_REQ_STRU */
    ID_WPHY_TOOL_HSUPA_EDCH_ACTIVE_SET_RPT_CNF              = 0xF0F4,           /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_CNF_STRU */
    ID_WPHY_TOOL_HSUPA_EDCH_ACTIVE_SET_RPT_IND              = 0xF0F5,           /* _H2ASN_MsgChoice WPHY_TOOL_HSUPA_EDCH_ACTIVE_SET_REPORT_IND_STRU */

    /* 干扰特性新增 */
    ID_WPHY_TOOL_INTERFE_TX_BLANKING_IND                    = 0xF0F6,

    ID_WPHY_TOOL_DRIVE_TEST_RPT_CNF                         = 0xF100,           /* _H2ASN_MsgChoice WPHY_TOOL_COMMON_DT_CNF_STRU */

    ID_WPHY_TOOL_RADIO_PARA_CELL_SNR_RPT_REQ                = 0xF101,           /* _H2ASN_MsgChoice WPHY_TOOL_RADIO_PARA_CELL_SNR_REQ_STRU */
    ID_WPHY_TOOL_RADIO_PARA_CELL_SNR_RPT_IND                = 0xF102,           /* _H2ASN_MsgChoice WPHY_TOOL_RADIO_PARA_CELL_SNR_IND_STRU */

    ID_WPHY_TOOL_HSPDSCH_CFG_RPT_REQ                        = 0xF103,           /* _H2ASN_MsgChoice WPHY_TOOL_HSPDSCH_CFG_REQ_STRU */
    ID_WPHY_TOOL_HSPDSCH_CFG_RPT_IND                        = 0xF104,           /* _H2ASN_MsgChoice WPHY_TOOL_HSPDSCH_CFG_IND_STRU */

    ID_WPHY_TOOL_HSSCCH_CFG_RPT_REQ                         = 0xF105,           /* _H2ASN_MsgChoice WPHY_TOOL_HSSCCH_CFG_REQ_STRU */
    ID_WPHY_TOOL_HSSCCH_CFG_RPT_IND                         = 0xF106,           /* _H2ASN_MsgChoice WPHY_TOOL_HSSCCH_CFG_IND_STRU */

    ID_WPHY_TOOL_HSDPCCH_CFG_RPT_REQ                        = 0xF107,           /* _H2ASN_MsgChoice WPHY_TOOL_HSDPCCH_CFG_REQ_STRU */
    ID_WPHY_TOOL_HSDPCCH_CFG_RPT_IND                        = 0xF108,           /* _H2ASN_MsgChoice WPHY_TOOL_HSDPCCH_CFG_IND_STRU */

    ID_WPHY_TOOL_HSDPA_CQI_RPT_REQ                          = 0xF109,           /* _H2ASN_MsgChoice WPHY_TOOL_HS_HSDPA_CQI_REQ_STRU */
    ID_WPHY_TOOL_HSDPA_CQI_RPT_IND                          = 0xF10A,           /* _H2ASN_MsgChoice WPHY_TOOL_HS_HSDPA_CQI_IND_STRU */

    ID_WPHY_TOOL_HSDPA_LINK_STAT_RPT_REQ                    = 0xF10B,           /* _H2ASN_MsgChoice WPHY_TOOL_HSDPA_LINK_STAT_REQ_STRU */
    ID_WPHY_TOOL_HSDPA_LINK_STAT_RPT_IND                    = 0xF10C,           /* _H2ASN_MsgChoice WPHY_TOOL_HSDPA_LINK_STAT_IND_STRU */

    ID_WPHY_TOOL_HSDPA_DECOD_STAT_RPT_REQ                   = 0xF10D,           /* _H2ASN_MsgChoice WPHY_TOOL_HSDPA_DECOD_STAT_REQ_STRU */
    ID_WPHY_TOOL_HSDPA_DECOD_STAT_RPT_IND                   = 0xF10E,           /* _H2ASN_MsgChoice WPHY_TOOL_HSDPA_DEC_STAT_IND_STRU */

    ID_WPHY_TOOL_HSDPA_DECOD_TBS_RPT_REQ                    = 0xF10F,           /* _H2ASN_MsgChoice WPHY_TOOL_HSDPA_DEC_TBS_REQ_STRU */
    ID_WPHY_TOOL_HSDPA_DECOD_TBS_RPT_IND                    = 0xF110,           /* _H2ASN_MsgChoice WPHY_TOOL_HSDPA_DEC_TBS_IND_STRU */

    ID_WPHY_TOOL_HSUPA_LINK_THROUGHPUT_RPT_REQ              = 0xF111,           /* _H2ASN_MsgChoice WPHY_TOOL_HSUPA_LINK_THROUGHPUT_RPT_REQ_STRU */
    ID_WPHY_TOOL_HSUPA_LINK_THROUGHPUT_RPT_IND              = 0xF112,           /* _H2ASN_MsgChoice WPHY_TOOL_HSUPA_LINK_THROUGHPUT_RPT_IND_STRU */

    ID_WPHY_TOOL_HSUPA_LINK_QUALITY_RPT_REQ                 = 0xF113,           /* _H2ASN_MsgChoice WPHY_TOOL_HSUPA_LINK_QUALITY_REQ_STRU */
    ID_WPHY_TOOL_HSUPA_LINK_QUALITY_RPT_IND                 = 0xF114,           /* _H2ASN_MsgChoice WPHY_TOOL_HSUPA_LINK_QUALITY_RPT_IND_STRU */

    ID_WPHY_TOOL_HSUPA_GRANT_RPT_REQ                        = 0xF115,           /* _H2ASN_MsgChoice WPHY_TOOL_HSUPA_GRANT_RPT_REQ_STRU */
    ID_WPHY_TOOL_HSUPA_GRANT_RPT_IND                        = 0xF116,           /* _H2ASN_MsgChoice WPHY_TOOL_HSUPA_GRANT_RPT_IND_STRU */

    ID_WPHY_TOOL_PWR_CTRL_PWR_RPT_REQ                       = 0xF117,           /* _H2ASN_MsgChoice WPHY_TOOL_PWR_CTRL_PWR_RPT_REQ_STRU */
    ID_WPHY_TOOL_PWR_CTRL_PWR_RPT_IND                       = 0xF118,           /* _H2ASN_MsgChoice WPHY_TOOL_PWR_CTRL_PWR_RPT_IND_STRU */

    ID_WPHY_TOOL_PWR_CTRL_TPC_RPT_REQ                       = 0xF119,           /* _H2ASN_MsgChoice WPHY_TOOL_PWR_CTRL_TPC_RPT_REQ_STRU */
    ID_WPHY_TOOL_PWR_CTRL_TPC_RPT_IND                       = 0xF11A,           /* _H2ASN_MsgChoice WPHY_TOOL_PWR_CTRL_TPC_RPT_IND_STRU */

    ID_WPHY_TOOL_MSG_ID_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16;


/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_RSLT_ENUM_UINT16
 协议表格  :
 枚举说明  : 各种回复消息的结果值:成功或者失败等
*****************************************************************************/
enum WPHY_TOOL_MNTN_RSLT_ENUM
{
    WPHY_MNTN_RSLT_SUCC                         = 0,                            /* 成功 */
    WPHY_MNTN_RSLT_FAIL                         = 1,                            /* 失败 */
    WPHY_MNTN_RSLT_PERIOD_NOT_SUPPORT           = 2,                            /* 配置周期不支持 */
    WPHY_MNTN_RSLT_PARA_INVALID                 = 3,                            /* 设置参数无效 */
    WPHY_MNTN_RSLT_PARA_TYPE_OVERFLOW           = 4,                            /* 设置参数类型不正确 */

    WPHY_MNTN_RSLT_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_RSLT_ENUM_UINT16;





/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_REPORT_TYPE_ENUM_UINT16
 协议表格  :
 枚举说明  : 各种测量报告上报周期
*****************************************************************************/
enum WPHY_TOOL_MNTN_REPORT_TYPE_ENUM
{
    WPHY_MNTN_REPORT_TYPE_NO_RPT                = 0,                            /* 不上报: */
    WPHY_MNTN_REPORT_TYPE_ONE_TIME              = 1,                            /* 上报1次: */
    WPHY_MNTN_REPORT_TYPE_PER_FRAME             = 2,                            /* 每帧上报: */
    WPHY_MNTN_REPORT_TYPE_ASSIGNED_PERIOD       = 3,                            /* 指定周期:以帧为单位。如果选择此项，则必须填写下一个变量来指定周期。 */
    WPHY_MNTN_REPORT_TYPE_EVENT_TRIGER          = 4,                            /* 事件触发: */

    WPHY_MNTN_REPORT_TYPE_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_REPORT_TYPE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : WPHY_MNTN_PWR_SWITCH_TYPE_ENUM_UINT16
 协议表格  :
 枚举说明  : 开关控制的枚举值
*****************************************************************************/
enum WPHY_TOOL_MNTN_PWR_SWITCH_TYPE_ENUM
{
    WPHY_MNTN_PWR_SWITCH_TYPE_UL_PC             = 0,                            /* 上行功率控制:固定上行发射东率 */
    WPHY_MNTN_PWR_SWITCH_TYPE_OLPC              = 1,                            /* 外环功控 */
    WPHY_MNTN_PWR_SWITCH_TYPE_WINUP             = 2,                            /* winup控制 */
    WPHY_MNTN_PWR_SWITCH_TYPE_WINDOWN           = 3,                            /* windown控制 */
    WPHY_MNTN_PWR_SWITCH_TYPE_FIX_DL_PWR        = 4,                            /* 固定下行发射功率 */

    WPHY_MNTN_PWR_SWITCH_TYPE_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_PWR_SWITCH_TYPE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_SWITCH_CTRL_ENUM_UINT16
 协议表格  :
 枚举说明  : 开关控制的枚举值
*****************************************************************************/
enum WPHY_TOOL_MNTN_SWITCH_CTRL_ENUM
{
    WPHY_MNTN_SWITCH_CTRL_CLOSE                 = 0,                            /* 关闭 */
    WPHY_MNTN_SWITCH_CTRL_OPEN                  = 1,                            /* 打开 */

    WPHY_MNTN_SWITCH_CTRL_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_SWITCH_CTRL_ENUM_UINT16;


/*****************************************************************************
 枚举名    : WPHY_TOOL_SYNC_STATUS_ENUM_UINT16
 协议表格  :
 枚举说明  : 开关控制的枚举值
*****************************************************************************/
enum WPHY_TOOL_SYNC_STATUS_ENUM
{
    WPHY_MNTN_SYNC_STATUS_FIX                   = 0,                            /* 锁定 */
    WPHY_MNTN_SYNC_STATUS_LOST                  = 1,                            /* 失锁 */

    WPHY_MNTN_SYNC_STATUS_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_SYNC_STATUS_ENUM_UINT16;


/*****************************************************************************
 枚举名    : WPHY_TOOL_TCXO_STATUS_ENUM_UINT16
 协议表格  :
 枚举说明  : 开关控制的枚举值
*****************************************************************************/
enum WPHY_TOOL_TCXO_STATUS_ENUM
{
    WPHY_MNTN_TCXO_STATUS_FREEZE                = 0,                            /* 锁定 */
    WPHY_MNTN_TCXO_STATUS_UNFREEZE              = 1,                            /* 失锁 */

    WPHY_MNTN_TCXO_STATUS_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_TCXO_STATUS_ENUM_UINT16;



/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_PWR_PARA_ENUM_UINT32
 协议表格  :
 枚举说明  : 功率参数类型，查询和设置公用
*****************************************************************************/
enum WPHY_TOOL_MNTN_PWR_PARA_ENUM
{
    WPHY_MNTN_PWR_PARA_SIR_TARGET               = 0x00000001,                   /* SirTarget */
    WPHY_MNTN_PWR_PARA_CURR_TRCH_ID_SELECTED    = 0x00000002,                   /* 当前选择的TrchId */
    WPHY_MNTN_PWR_PARA_DL_TPC                   = 0x00000004,                   /* DL TPC */
    WPHY_MNTN_PWR_PARA_CURR_SIR                 = 0x00000008,                   /* 当前的SIR */
    WPHY_MNTN_PWR_PARA_CURR_BLER                = 0x00000010,                   /* 当前的BLER */
    WPHY_MNTN_PWR_PARA_UL_TPC                   = 0x00000020,                   /* UL TPC */
    WPHY_MNTN_PWR_PARA_BD                       = 0x00000040,                   /* Bd */
    WPHY_MNTN_PWR_PARA_BEC                      = 0x00000080,                   /* Bec */
    WPHY_MNTN_PWR_PARA_BED                      = 0x00000100,                   /* Bed */
    WPHY_MNTN_PWR_PARA_BHS_NACK                 = 0x00000200,                   /* BhsNack */
    WPHY_MNTN_PWR_PARA_BHS_ACK                  = 0x00000400,                   /* BhsAck */
    WPHY_MNTN_PWR_PARA_BHS_CQI                  = 0x00000800,                   /* BhsCQI */
    WPHY_MNTN_PWR_PARA_BHS_TFCI                 = 0x00001000,                   /* TFCI */
    WPHY_MNTN_PWR_PARA_SLOT_FORMAT              = 0x00002000,                   /* SlotFormat */
    WPHY_MNTN_PWR_PARA_MAX_PWR                  = 0x00004000,                   /* 最大发射功率 */
    WPHY_MNTN_PWR_PARA_MIN_PWR                  = 0x00008000,                   /* 最小发射功率 */
    WPHY_MNTN_PWR_PARA_INIT_PWR                 = 0x00010000,                   /* lint !e575 初始发射功率 */
    WPHY_MNTN_PWR_PARA_LIST_MODE_SET_PWR        = 0x00020000,                   /* lint !e575 LIST MODE下关闭内环功控直接设置的发射功率 */
    WPHY_MNTN_PWR_PARA_LIST_MODE_OPEN_ILPC      = 0x00040000,                   /* lint !e575 LIST MODE下重新打开内环功控 */

    WPHY_MNTN_PWR_PARA_BUTT
};
typedef VOS_UINT32 WPHY_TOOL_MNTN_PWR_PARA_ENUM_UINT32;



/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_EVENT_TYPE_ENUM_UINT32
 协议表格  :
 枚举说明  : 上报事件类型
*****************************************************************************/
enum WPHY_TOOL_MNTN_EVENT_TYPE_ENUM
{
    WPHY_MNTN_EVENT_TYPE_AFC_STATUS             = 0x00000001,                   /* 6ms 任务超时 */
    WPHY_MNTN_EVENT_TYPE_SYNC_STATUS            = 0x00000002,                   /* 9ms 任务超时 */
    WPHY_MNTN_EVENT_TYPE_L1_STATUS              = 0x00000004,                   /* L1状态 */
    WPHY_MNTN_EVENT_TYPE_INT_EXCEPT             = 0x00000008,                   /* 中断异常 */

    WPHY_MNTN_EVENT_TYPE_BUTT
};
typedef VOS_UINT32 WPHY_TOOL_MNTN_EVENT_TYPE_ENUM_UINT32;




/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_INT_EXCEPT_ENUM_UINT16
 协议表格  :
 枚举说明  : 中断异常类型
*****************************************************************************/
enum WPHY_TOOL_MNTN_INT_EXCEPT_ENUM
{
    WPHY_MNTN_INT_EXCEPT_TYPE_6MS_TASK_EXPIRED  = 0,                            /* 6ms 任务超时 */
    WPHY_MNTN_INT_EXCEPT_TYPE_9MS_TASK_EXPIRED  = 1,                            /* 9ms 任务超时 */

    WPHY_MNTN_INT_EXCEPT_TYPE_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_INT_EXCEPT_ENUM_UINT16;



/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_SYS_STATUS_ENUM_UINT16
 协议表格  :
 枚举说明  : 系统状态
*****************************************************************************/
enum WPHY_TOOL_MNTN_SYS_STATUS_ENUM
{
    WPHY_MNTN_SYS_STATUS_FREE                   = 0,
    WPHY_MNTN_SYS_STATUS_CPICH                  = 1,
    WPHY_MNTN_SYS_STATUS_FACH                   = 2,
    WPHY_MNTN_SYS_STATUS_DPCH                   = 3,

    WPHY_MNTN_SYS_STATUS_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_SYS_STATUS_ENUM_UINT16;



/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_THRESHOLD_TYPE_ENUM_UINT32
 协议表格  :
 枚举说明  : 可配置门限类型
*****************************************************************************/
enum WPHY_TOOL_MNTN_THRESHOLD_TYPE_ENUM
{
    /* 小区搜索门限 */
    WPHY_MNTN_THRESHOLD_TYPE_STEP1_NOISE                    = 0,
    WPHY_MNTN_THRESHOLD_TYPE_STEP2_NOISE                       ,
    WPHY_MNTN_THRESHOLD_TYPE_STEP3_NOISE_AFC_UNLOCK            ,
    WPHY_MNTN_THRESHOLD_TYPE_STEP3_NOISE_AFC_LOCK              ,
    WPHY_MNTN_THRESHOLD_TYPE_STEPB_NOISE                       ,

    WPHY_MNTN_THRESHOLD_TYPE_STEP1_FAIL_FOR_SPEC_FREQ          ,
    WPHY_MNTN_THRESHOLD_TYPE_STEP1_FAIL_FOR_BAND               ,

    WPHY_MNTN_THRESHOLD_TYPE_STEP1_CORRELEN_FOR_INIT_CS        ,

    WPHY_MNTN_THRESHOLD_TYPE_STEP2_RSDEC_LEN                   ,
    WPHY_MNTN_THRESHOLD_TYPE_STEP3_CORRELEN_AFC_UNLOCK         ,
    WPHY_MNTN_THRESHOLD_TYPE_STEP3_CORRELEN_AFC_LOCK           ,
    WPHY_MNTN_THRESHOLD_TYPE_STEP3_NCORRELEN_AFC_UNLOCK        ,
    WPHY_MNTN_THRESHOLD_TYPE_STEP3_NCORRELEN_AFC_LOCK          ,

    WPHY_MNTN_THRESHOLD_TYPE_STEPB_CORRELEN                    ,

    /*  多径搜索门限 */
    WPHY_MNTN_THRESHOLD_TYPE_CORRE_LENTH_LOCK                  ,
    WPHY_MNTN_THRESHOLD_TYPE_INCORRE_LENTH_LOCK                ,
    WPHY_MNTN_THRESHOLD_TYPE_CORRE_LENTH_UNLOCK                ,
    WPHY_MNTN_THRESHOLD_TYPE_INCORRE_LENTH_UNLOCK              ,

    /* 测量门限 */
    WPHY_MNTN_THRESHOLD_TYPE_MEAS_AVERAGE_NOISE                ,
    WPHY_MNTN_THRESHOLD_TYPE_MP_RELATIVE_FACTOR                ,

    WPHY_MNTN_THRESHOLD_TYPE_MEAS_TIMING_ECNO_THRESHOLD        ,
    WPHY_MNTN_THRESHOLD_TYPE_MEAS_TIMING_RSCP_THRESHOLD        ,

    WPHY_MNTN_THRESHOLD_TYPE_MAX_TIMING_MEAS_FRAME_NUMBER      ,

    /* 功控门限 */
    WPHY_MNTN_THRESHOLD_TYPE_SIR_THRESHOLD_PILOT1              ,
    WPHY_MNTN_THRESHOLD_TYPE_SIR_THRESHOLD_PILOT2              ,

    WPHY_MNTN_THRESHOLD_TYPE_TPC_THRESHOLD_TTI1OR2             ,
    WPHY_MNTN_THRESHOLD_TYPE_TPC_THRESHOLD_TTI4                ,
    WPHY_MNTN_THRESHOLD_TYPE_TPC_THRESHOLD_TTI8                ,

    WPHY_MNTN_THRESHOLD_TYPE_INCORRE_CPU_QIN                   ,
    WPHY_MNTN_THRESHOLD_TYPE_INCORRE_CPU_QOUT                  ,
    WPHY_MNTN_THRESHOLD_TYPE_INCORRE_SS_THRESHOLD              ,
    WPHY_MNTN_THRESHOLD_TYPE_INCORRE_MRC_THRESHOLD             ,
    WPHY_MNTN_THRESHOLD_TYPE_INCORRE_INT_THRESHOLD             ,
    WPHY_MNTN_THRESHOLD_TYPE_INCORRE_ML_THRESHOLD              ,

    /* DRX功能门限 */
    WPHY_MNTN_THRESHOLD_TYPE_32K_CLOCK_MSR_WAIT_SFN_NUM        ,
    WPHY_MNTN_THRESHOLD_TYPE_SLEEP_LENTH                       ,
    WPHY_MNTN_THRESHOLD_TYPE_TIME_ADJUST                       ,

    WPHY_MNTN_THRESHOLD_TYPE_BUTT
};
typedef VOS_UINT32 WPHY_TOOL_MNTN_THRESHOLD_TYPE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_PA_STATUS_ENUM
 协议表格  :
 枚举说明  : 开关控制的枚举值
*****************************************************************************/
enum WPHY_TOOL_MNTN_PA_STATUS_ENUM
{
    WPHY_MNTN_PA_STATUS_CLOSE                       = 0,                        /* 关闭 */
    WPHY_MNTN_PA_STATUS_OPEN                        = 1,                        /* 打开 */

    WPHY_MNTN_PA_STATUS_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_PA_STATUS_ENUM_UINT16;


/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_RPT_ADDR_ENUM_UINT16
 协议表格  :
 枚举说明  : WPHY可维可测固定抓取的几块数据枚举
*****************************************************************************/
enum WPHY_TOOL_MNTN_RAM_RPT_ENUM
{
    WPHY_MNTN_RPT_HSUPA_SHARE_CTRL                  = 0,                        /* UPA控制 */
    WPHY_MNTN_RPT_DSP_MODE                          = 1,                        /* DSP模式 */
    WPHY_MNTN_RPT_HSUPA_RPT                         = 2,
    WPHY_MNTN_RPT_HSUPA_TTI                         = 3,
    WPHY_MNTN_RPT_CPC_DRX_RPT                       = 4,
    WPHY_MNTN_RPT_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_RAM_RPT_ENUM_UINT16;


/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_ERROR_RPT_LEVEL_ENUM_UINT16
 协议表格  :
 枚举说明  : WPHY错误上报级别
*****************************************************************************/
enum WPHY_TOOL_MNTN_ERROR_RPT_LEVEL_ENUM
{
    WPHY_MNTN_ERROR_LEVEL_INFO                      = 1,
    WPHY_MNTN_ERROR_LEVEL_WARNING                   = 2,
    WPHY_MNTN_ERROR_LEVEL_ERROR                     = 3,

    WPHY_MNTN_ERROR_LEVEL_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_ERROR_RPT_LEVEL_ENUM_UINT16;


/*****************************************************************************
 枚举名    : UPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16
 协议表格  :
 枚举说明  : 开关控制的枚举值
*****************************************************************************/
enum UPHY_TOOL_MNTN_RPT_STATUS_ENUM
{
    UPHY_MNTN_RPT_STATUS_CLOSE                      = 0,                        /* 关闭 */
    UPHY_MNTN_RPT_STATUS_OPEN                       = 1,                        /* 打开 */
    UPHY_MNTN_RPT_STATUS_BUTT
};
typedef VOS_UINT16 UPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16;


/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16
 协议表格  :
 枚举说明  : 开关控制的枚举值
*****************************************************************************/
enum WPHY_TOOL_MNTN_RPT_STATUS_ENUM
{
    WPHY_MNTN_RPT_STATUS_CLOSE                      = 0,                        /* 关闭 */
    WPHY_MNTN_RPT_STATUS_OPEN                       = 1,                        /* 打开 */

    WPHY_MNTN_RPT_STATUS_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16;

/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_RSLT_ENUM_UINT16
 协议表格  :
 枚举说明  : T313 Status
ASN.1描述 :
 枚举说明  : T313定时器 状态
*****************************************************************************/
enum WPHY_TOOL_MNTN_T313_STATUS_ENUM
{
    WPHY_MNTN_T313_START                        = 0,
    WPHY_MNTN_T313_STOP                         = 1,
    WPHY_MNTN_T313_TIMEOUT                      = 2,

    WPHY_MNTN_T313_STATUS_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_T313_STATUS_ENUM_UINT16;

/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_RSLT_ENUM_UINT16
 协议表格  :
 枚举说明  : T312 Status
ASN.1描述 :
 枚举说明  : T312定时器 状态
*****************************************************************************/
enum WPHY_TOOL_MNTN_T312_STATUS_ENUM
{
    WPHY_MNTN_T312_START                        = 0,
    WPHY_MNTN_T312_STOP                         = 1,
    WPHY_MNTN_T312_TIMEOUT                      = 2,

    WPHY_MNTN_T312_STATUS_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_T312_STATUS_ENUM_UINT16;

/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_MASTER_STOP_LTE_REASION_ENUM
 协议表格  :
 枚举说明  : 强停LTE原因
ASN.1描述 :
 枚举说明  : 强停LTE原因

*****************************************************************************/
enum WPHY_TOOL_MNTN_MASTER_STOP_LTE_REASION_ENUM
{
    WPHY_TOOL_MNTN_MASTER_STOP_LTE_REASION_BG               = 0,
    WPHY_TOOL_MNTN_MASTER_STOP_LTE_REASION_MEAS_TIMEOUT     = 1,
    WPHY_TOOL_MNTN_MASTER_STOP_LTE_REASION_BG_TIMEOUT       = 2,
    WPHY_TOOL_MNTN_MASTER_STOP_LTE_REASION_HIGH_TASK        = 3,
    WPHY_TOOL_MNTN_MASTER_STOP_LTE_REASION_INIT             = 4,

    WPHY_TOOL_MNTN_MASTER_STOP_LTE_REASION_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_MASTER_STOP_LTE_REASION_ENUM_UINT16;

/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_SLAVE_CURRENT_STATUS_ENUM_UINT16
 协议表格  :
 枚举说明  : 从模状态
ASN.1描述 :
 枚举说明  : 从模状态
*****************************************************************************/
enum WPHY_TOOL_MNTN_SLAVE_CURRENT_STATUS_ENUM
{
    WPHY_MNTN_SLAVE_PRE                         = 0,
    WPHY_MNTN_SLAVE_ENTERGAP                    = 1,
    WPHY_MNTN_SLAVE_EXITRGAP                    = 2,
    WPHY_MNTN_SLAVE_FREQCHANGE                  = 3,
    WPHY_MNTN_SLAVE_MEAS_FINISH                 = 4,
    WPHY_MNTN_SLAVE_CS_FINISH                   = 5,
    WPHY_MNTN_SLAVE_STATUS_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_SLAVE_CURRENT_STATUS_ENUM_UINT16;

/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_CPC_DRX_EQUA_STATUS_ENUM_UINT16
 协议表格  :
 枚举说明  : 当前均衡工作状态
ASN.1描述 :
 枚举说明  : 从模状态
*****************************************************************************/
enum WPHY_TOOL_MNTN_CPC_DRX_EQUA_STATUS_ENUM
{
    WPHY_MNTN_CPC_DRX_EQUA_STATUS_ALWAYS_OPEN    = 0,                                /* 均衡长开状态 */
    WPHY_MNTN_CPC_DRX_EQUA_STATUS_DRX_OPEN,                                          /* 均衡打开状态 */
    WPHY_MNTN_CPC_DRX_EQUA_STATUS_DRX_CLOSE,                                         /* 均衡关闭状态 */
    WPHY_MNTN_CPC_DRX_EQUA_STATUS_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_CPC_DRX_EQUA_STATUS_ENUM_UINT16;

/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_BOOL_ENUM_UINT16
 协议表格  :
 枚举说明  : 物理层枚举类型
*****************************************************************************/
enum WPHY_TOOL_MNTN_BOOL_ENUM
{
    WPHY_MNTN_BOOL_FALSE                        = 0,
    WPHY_MNTN_BOOL_TRUE                         = 1,
    WPHY_MNTN_BOOL_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_BOOL_ENUM_UINT16;

/*****************************************************************************
 枚举名    : UPHY_TOOL_MNTN_BOOL_ENUM_UINT16
 协议表格  :
 枚举说明  : 物理层枚举类型
*****************************************************************************/
enum UPHY_TOOL_MNTN_BOOL_ENUM
{
    UPHY_MNTN_BOOL_FALSE                        = 0,
    UPHY_MNTN_BOOL_TRUE                         = 1,
    UPHY_MNTN_BOOL_BUTT
};
typedef VOS_UINT16 UPHY_TOOL_MNTN_BOOL_ENUM_UINT16;

/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_CPC_DRX_CQI_PRIORITY_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : CQI 优先级类型定义
*****************************************************************************/
enum  WPHY_TOOL_MNTN_CPC_DRX_CQI_PRI_ENUM
{
    WPHY_MNTN_CPC_DRX_CQI_PRIORITY_0            = 0,                                /* CQI优先级为0 */
    WPHY_MNTN_CPC_DRX_CQI_PRIORITY_1               ,                                /* CQI优先级为1 */
    WPHY_MNTN_CPC_DRX_CQI_PRIORITY_BUTT
};
typedef VOS_UINT16  WPHY_TOOL_MNTN_CPC_DRX_CQI_PRI_ENUM_UINT16;

/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_CPC_ULDPCCH_CYCLE_STATE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 综合主辅载波的状态后的出的cycle状态的最大集合
*****************************************************************************/
enum  WPHY_TOOL_MNTN_CPC_ULDPCCH_CYCLE_STATE_ENUM
{
    WPHY_MNTN_CPC_ULDPCCH_CYCLE1                = 0,
    WPHY_MNTN_CPC_ULDPCCH_CYCLE2,
    WPHY_MNTN_CPC_ULDPCCH_CYCLE1AND2,
    WPHY_MNTN_CPC_ULDPCCH_CYCLE_BUTT
};
typedef VOS_UINT16  WPHY_TOOL_MNTN_CPC_ULDPCCH_CYCLE_STATE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_CPC_DRX_RF_STATUS_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :CPC DRX
*****************************************************************************/
enum  WPHY_TOOL_MNTN_CPC_DRX_RF_STATUS_ENUM
{
    WPHY_MNTN_CPC_DRX_RF_STATUS_ALWAYS_OPEN    = 0,                                  /* RF一直打开 */
    WPHY_MNTN_CPC_DRX_RF_STATUS_DRX_OPEN,                                            /* RF处于DRX的打开状态 */
    WPHY_MNTN_CPC_DRX_RF_STATUS_DRX_CLOSE,                                           /* RF处于DRX的关闭状态 */
    WPHY_MNTN_CPC_DRX_RF_STATUS_BUTT
};
typedef VOS_UINT16  WPHY_TOOL_MNTN_CPC_DRX_RF_STATUS_ENUM_UINT16;

/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_MAS_STATE_ENUM_UINT16
 协议表格  :
 枚举说明  : MAS状态枚举
*****************************************************************************/
enum WPHY_TOOL_MNTN_MAS_STATE_ENUM
{
    WPHY_MNTN_MAS_STATEI                               = 0,
    WPHY_MNTN_MAS_STATEIAIB                            = 1,
    WPHY_MNTN_MAS_STATEII                              = 2,
    WPHY_MNTN_MAS_STATEIII                             = 3,
    WPHY_MNTN_MAS_STATE_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_MAS_STATE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_CTRL_MODE_ENUM_UINT16
 协议表格  :
 枚举说明  : MAS 主被控模式枚举
*****************************************************************************/
enum WPHY_TOOL_MNTN_CTRL_MODE_ENUM
{
    WPHY_MNTN_CTRL_MODE_ACTIVE                       = 0,
    WPHY_MNTN_CTRL_MODE_PASSIVE                      = 1,
    WPHY_MNTN_CTRL_MODE_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_CTRL_MODE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : WPHY_MAS_ANTTASSTATUS_ENUM_UINT16
 协议表格  :
 枚举说明  : 天线TAS状态枚举
*****************************************************************************/
enum WPHY_TOOL_MNTN_MAS_ANTTASSTATUS_ENUM
{
    WPHY_MNTN_MAS_TASDPDT0                             = 0,                          /* TAS直通态 */
    WPHY_MNTN_MAS_TASDPDT1                             = 1,                          /* TAS交叉态 */
    WPHY_MNTN_MAS_TAS_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_MAS_ANTTASSTATUS_ENUM_UINT16;


/*****************************************************************************
 枚举名    : WPHY_MAS_ANTMASSTATUS_ENUM_UINT16
 协议表格  :
 枚举说明  : 天线MAS状态枚举
*****************************************************************************/
enum WPHY_TOOL_MNTN_MAS_ANTMASSTATUS_ENUM
{
    WPHY_MNTN_MAS_MASDPDT0                             = 0,                          /* MAS默认态:天线在右边 */
    WPHY_MNTN_MAS_MASDPDT1                             = 1,                          /* MAS非默认态:天线在左边 */
    WPHY_MNTN_MAS_MAS_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_MAS_ANTMASSTATUS_ENUM_UINT16;
/*****************************************************************************
 枚举名    : WPHY_TOOL_RAKE_MP_STATUS_ENUM_UINT16
 协议表格  :
 枚举说明  : 当前rake多径运行的状态
*****************************************************************************/
enum WPHY_TOOL_RAKE_MP_STATUS_ENUM
{
    WPHY_TOOL_RAKE_MP_STATUS_NONE        = 0 ,                                   /* 多径搜索没有运行 */
    WPHY_TOOL_RAKE_MP_STATUS_RAKE            ,                                   /* 运行的是RAKE多径 */
    WPHY_TOOL_RAKE_MP_STATUS_RAKE_TYPE1      ,                                   /* 运行的是RAKE TYPE1多径 */

    WPHY_TOOL_RAKE_MP_STATUS_RAKE_BUTT,
};
typedef VOS_UINT16 WPHY_TOOL_RAKE_MP_STATUS_ENUM_UINT16;

/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_DL_TPC_CMD_ENUM
 协议表格  :
 枚举说明  : 下行TPC命令字
*****************************************************************************/
enum WPHY_TOOL_MNTN_DL_TPC_CMD_ENUM
{
    WPHY_MNTN_DL_TPC_CMD_DOWN            = 0,                                   /* 降功率 */
    WPHY_MNTN_DL_TPC_CMD_UP              = 1,                                   /* 升功率 */
    WPHY_MNTN_DL_TPC_CMD_HOLD            = 2                                    /* 保持功率 */
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_DL_TPC_CMD_ENUM_UINT16;

/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_UL_TPC_CMD_ENUM
 协议表格  :
 枚举说明  : 下行TPC命令字
*****************************************************************************/
enum WPHY_TOOL_MNTN_UL_TPC_CMD_ENUM
{
    WPHY_MNTN_UL_TPC_CMD_DOWN            = 0,                                   /* 降功率 */
    WPHY_MNTN_UL_TPC_CMD_UP              = 1                                    /* 升功率 */
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_UL_TPC_CMD_ENUM_UINT16;

/*****************************************************************************
 枚举名    : GPHY_TOOL_TIMESLOT_MEAS_TYPE_ENUM_UINT16
 协议表格  :
 枚举说明  : 时隙测量任务
*****************************************************************************/
enum GPHY_TOOL_TIMESLOT_MEAS_TYPE_ENUM
{
    GPHY_TOOL_TS_NO_MEAS                  = 0,                                  /* 0 当前时隙无测量任务 */
    GPHY_TOOL_TS_BA_MEAS                     ,                                  /* 1 当前时隙为BA测量 */
    GPHY_TOOL_TS_CELLSELECT_MEAS             ,                                  /* 2 当前时隙为小区选择测量 */
    GPHY_TOOL_TS_FULLLIST_MEAS               ,                                  /* 3 当前时隙为全频点测量 */
    GPHY_TOOL_TS_INTERFERE_MEAS              ,                                  /* 4 当前时隙为干扰测量 */
    GPHY_TOOL_TS_SCELL_BCCH_SLOW_GAIN_MEAS   ,                                  /* 5 服务区BCCH接收增益测量 */
    GPHY_TOOL_TS_SCELL_CCCH_SLOW_GAIN_MEAS   ,                                  /* 6 服务区CCCH接收增益测量 */
    GPHY_TOOL_TS_SCELL_PBCCH_SLOW_GAIN_MEAS  ,                                  /* 7 服务区PBCCH接收增益测量 */
    GPHY_TOOL_TS_SCELL_PCCCH_SLOW_GAIN_MEAS  ,                                  /* 8 服务区PCCCH接收增益测量 */
    GPHY_TOOL_TS_SCELL_CBCH_SLOW_GAIN_MEAS   ,                                  /* 9 服务区CBCH接收增益测量 */
    GPHY_TOOL_TS_SCELL_TCH_GAIN_MEAS         ,                                  /* 10 服务区CS专用态接收增益测量 */
    GPHY_TOOL_TS_SCELL_PDTCH_GAIN_MEAS       ,                                  /* 11 服务区PS专用态pdtch接收增益测量 */
    GPHY_TOOL_TS_SCELL_PTCCH_GAIN_MEAS       ,                                  /* 12 服务区PS专用态ptcch接收增益测量 */
    GPHY_TOOL_TS_SCELL_SYNC_SLOW_GAIN_MEAS   ,                                  /* 13 服务区同步慢速增益测量*/
    GPHY_TOOL_TS_SCELL_BCCH_FAST_GAIN_MEAS   ,                                  /* 14 服务区BCCH接收前快速增益获得测量 */
    GPHY_TOOL_TS_SCELL_CCCH_FAST_GAIN_MEAS   ,                                  /* 15 服务区CCCH接收前快速增益获得测量 */
    GPHY_TOOL_TS_SCELL_PBCCH_FAST_GAIN_MEAS  ,                                  /* 16 服务区PBCCH接收前快速增益获得测量 */
    GPHY_TOOL_TS_SCELL_PCCCH_FAST_GAIN_MEAS  ,                                  /* 17 服务区BCCH接收前快速增益获得测量 */
    GPHY_TOOL_TS_SCELL_CBCH_FAST_GAIN_MEAS   ,                                  /* 18 服务区CBCH接收前快速增益获得测量 */
    GPHY_TOOL_TS_SCELL_SYNC_FAST_GAIN_MEAS   ,                                  /* 19 服务区同步速增益测量*/
    GPHY_TOOL_TS_NCELL_BCCH_FAST_GAIN_MEAS   ,                                  /* 20 邻区接收前快速增益获得测量 */
    GPHY_TOOL_TS_NCELL_BCCH_SLOW_GAIN_MEAS   ,                                  /* 21 邻区接收慢速测量 */
    GPHY_TOOL_TS_NCELL_SYNC_FAST_GAIN_MEAS   ,                                  /* 22 邻区同步前快速增益获得测量 */
    GPHY_TOOL_TS_NCELL_SYNC_SLOW_GAIN_MEAS   ,                                  /* 23 邻区同步慢速测量 */
    GPHY_TOOL_TS_BA_MEAS_SBCCH_MEAS          ,                                  /* 24 存在PB时BA测量模块的服务区BCCH测量 */
    GPHY_TOOL_TS_CAL_MEAS                    ,                                  /* 25 校准测量 */
    GPHY_TOOL_TS_WCDMA_MEAS                  ,                                  /* 26 当前时隙为异系统测量 */
    GPHY_TOOL_TS_BG_TASK                     ,                                  /* 27 G背景搜索测量 */
    GPHY_TOOL_TS_DCXO_TASK                   ,                                  /* 28 DCXO RA delay期间的测量类型 */
    GPHY_TOOL_TS_DUAL_ANT_PRI_ANT_MEAS       ,                                  /* 29 双天线切换主天线测量 */
    GPHY_TOOL_TS_DUAL_ANT_SEC_ANT_MEAS       ,                                  /* 30 双天线切换辅天线测量 */
    GPHY_TOOL_TS_NOISE_TOOL_MEAS             ,                                  /* 31 噪声工具测量 */
    GPHY_TOOL_TS_PSRCH_PCH_FAST_GAIN_MEAS    ,                                  /* 32 并行搜寻呼接收前快速增益获得测量 */
    GPHY_TOOL_TS_PSRCH_PCH_SLOW_GAIN_MEAS    ,                                  /* 33 并行搜寻呼接收慢速测量 */

    GPHY_TOOL_TIMESLOT_MEAS_TYPE_BUTT
};
typedef VOS_UINT16 GPHY_TOOL_TIMESLOT_MEAS_TYPE_ENUM_UINT16;

/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/

/*****************************************************************************
  6.0 STRUCT定义,WG公共定义
*****************************************************************************/

/*****************************************************************************
 结构名    : UPHY_TOOL_TYPE_HEADER_STRU
 枚举说明  : 工具解析结构头
*****************************************************************************/

typedef struct
{
    VOS_UINT16                                  usFuncType;                     /* 可维可测是0x4,内部消息抓取是0x */
    VOS_UINT16                                  usLength;                       /* 之后的长度,单位为byte */
    VOS_UINT32                                  ulSn;
    VOS_UINT32                                  ulTimeSlice;
}UPHY_TOOL_TYPE_HEADER_STRU;



/*****************************************************************************
 结构名    : UPHY_TOOL_OM_MSG_HEADER_STRU
 枚举说明  : 消息头结构定义
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usMsgId;
    VOS_UINT16                                  usReserved;
    VOS_UINT16                                  ausData[4];
}UPHY_TOOL_OM_MSG_HEADER_STRU;




/*****************************************************************************
 结构名    : UPHY_TOOL_INTRA_MSG_HEADER_STRU
 枚举说明  : 消息头结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                                  usMsgId;
    VOS_UINT16                                  usReserved;
}UPHY_TOOL_INTRA_MSG_HEADER_STRU;



/*****************************************************************************
  6.1 STRUCT定义,UPHY定义
*****************************************************************************/



/*****************************************************************************
 结构名    : GPHY_TOOL_SDT_LINK_STATUS_REQ
 结构说明  : TOOL告诉GPHY,SDT连接状态
*****************************************************************************/


/*****************************************************************************
 结构名    : GPHY_TOOL_COMMON_CNF_STRU
 结构说明  : GPHY可维可测公共回复消息结构
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip *//* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    UPHY_TOOL_MNTN_RSLT_ENUM_UINT16             enResult;                       /* 接收原语的处理结果ID */
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
}UPHY_TOOL_COMMON_CNF_STRU;


/*****************************************************************************
 结构名    : UPHY_TOOL_QUERY_SHARE_ADDR_REQ_STRU
 结构说明  : 共享地址查询请求原语
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT32                                  ulParaValue;                    /* 是否控制该参数 */
}UPHY_TOOL_QUERY_SHARE_ADDR_REQ_STRU;



/*****************************************************************************
 结构名    : UPHY_TOOL_QUERY_SHARE_ADDR_IND_STRU
 结构说明  : UPHY共享地址查询请求回复
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT32                                  ulShareAddr;                    /* 共享首地址 */

}UPHY_TOOL_QUERY_SHARE_ADDR_IND_STRU;


/*****************************************************************************
 结构名    : UPHY_TOOL_SDT_LINK_STATUS_REQ_STRU
 结构说明  : TOOL告诉UPHY,SDT连接状态
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usSdtStatus;
    VOS_UINT16                                  usRsv;
}UPHY_TOOL_SDT_LINK_STATUS_REQ_STRU;

/*****************************************************************************
 结构名    : UPHY_TOOL_ERROR_REPORT_REQ_STRU
 结构说明  : 错误上报
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    UPHY_TOOL_MNTN_RPT_LEVEL_ENUM_UINT16        enErrorRptLevel;                /* 控制上报错误级别 */
    VOS_UINT16                                  usRsv;
}UPHY_TOOL_ERROR_REPORT_REQ_STRU;



/*****************************************************************************
 结构名    : UPHY_TOOL_ERROR_REPORT_IND_STRU
 结构说明  : 错误上报
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usFileNo;                       /* 文件名编码 */
    VOS_UINT16                                  usLineNo;                       /* 出错的行号 */
    VOS_UINT32                                  ulTimeSlice;
    VOS_UINT32                                  ulLogId;                        /* PHY软件内统一编号LOG ID */
    VOS_UINT16                                  usReserved;                     /* 保留字段 */
    VOS_UINT16                                  usVarCnt;                       /* 上报变量个数 */
    VOS_UINT32                                  aulVarValue[UPHY_TOOL_MNTN_ERROR_RPT_VAR_NUM]; /* 上报变量值 */

}UPHY_TOOL_ERROR_REPORT_IND_STRU;



/*****************************************************************************
 结构名    : UPHY_TOOL_WPHY_INTER_GREG_REPORT_REQ_STRU
 结构说明  : WPHY下异系统G寄存器列表下发
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usRsv;                         /* 控制上报错误级别 */
    VOS_UINT16                                  usRegNum;                       /* 控制上报错误级别 */
    VOS_UINT32                                  aulRegAddr[UPHY_TOOL_INTER_REG_MAX_NUM];
}UPHY_TOOL_WPHY_INTER_GREG_REPORT_REQ_STRU;



/*****************************************************************************
 结构名    : UPHY_TOOL_WPHY_INTER_GREG_REPORT_CNF_STRU
 结构说明  : WPHY下异系统G寄存器收到回复
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    UPHY_TOOL_MNTN_RSLT_ENUM_UINT16             enResult;                       /* 接收原语的处理结果ID */
    VOS_UINT16                                  usRegNum;                       /* 控制上报错误级别 */
    VOS_UINT32                                  aulRegAddr[UPHY_TOOL_INTER_REG_MAX_NUM];
}UPHY_TOOL_WPHY_INTER_GREG_REPORT_CNF_STRU;


/*****************************************************************************
 结构名    : UPHY_TOOL_WPHY_INTER_GREG_REPORT_IND_STRU
 结构说明  : WPHY下异系统G寄存器值上报
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usRsv;                         /* 控制上报错误级别 */
    VOS_UINT16                                  usRegNum;                       /* 控制上报错误级别 */
    VOS_UINT32                                  aulRegData[UPHY_TOOL_INTER_REG_MAX_NUM];
}UPHY_TOOL_WPHY_INTER_GREG_REPORT_IND_STRU;



/*****************************************************************************
 结构名    : UPHY_TOOL_WPHY_INTER_GREG_STOP_REQ_STRU
 结构说明  : 停止WPHY下异系统G寄存器上报请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT32                                  ulRsv;                          /* 控制上报错误级别 */
}UPHY_TOOL_WPHY_INTER_GREG_STOP_REQ_STRU;




/*****************************************************************************
 结构名    : UPHY_TOOL_GPHY_INTER_WREG_REPORT_REQ_STRU
 结构说明  : GPHY下异系统W寄存器列表下发
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usRsv;                         /* 控制上报错误级别 */
    VOS_UINT16                                  usRegNum;                       /* 控制上报错误级别 */
    VOS_UINT32                                  aulRegAddr[UPHY_TOOL_INTER_REG_MAX_NUM];
}UPHY_TOOL_GPHY_INTER_WREG_REPORT_REQ_STRU;



/*****************************************************************************
 结构名    : UPHY_TOOL_WPHY_INTER_GREG_REPORT_CNF_STRU
 结构说明  : GPHY下异系统W寄存器收到回复
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    UPHY_TOOL_MNTN_RSLT_ENUM_UINT16             enResult;                       /* 接收原语的处理结果ID */
    VOS_UINT16                                  usRegNum;                       /* 控制上报错误级别 */
    VOS_UINT32                                  aulRegAddr[UPHY_TOOL_INTER_REG_MAX_NUM];
}UPHY_TOOL_GPHY_INTER_WREG_REPORT_CNF_STRU;


/*****************************************************************************
 结构名    : UPHY_TOOL_WPHY_INTER_GREG_REPORT_IND_STRU
 结构说明  : GPHY下异系统W寄存器值上报
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usRsv;                         /* 控制上报错误级别 */
    VOS_UINT16                                  usRegNum;                       /* 控制上报错误级别 */
    VOS_UINT32                                  aulRegData[UPHY_TOOL_INTER_REG_MAX_NUM];
}UPHY_TOOL_GPHY_INTER_WREG_REPORT_IND_STRU;



/*****************************************************************************
 结构名    : UPHY_TOOL_GPHY_INTER_WREG_STOP_REQ_STRU
 结构说明  : 停止GPHY下异系统W寄存器上报请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT32                                  ulRsv;                          /* 控制上报错误级别 */
}UPHY_TOOL_GPHY_INTER_WREG_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_TIMING_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 定时信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwSfn;                                 /* 系统定时SFN值 */
    VOS_UINT16                          uhwCfn;                                 /* 系统定时CFN值 */
    VOS_UINT16                          uhwSlot;                                /* 系统定时SLOT值 */
    VOS_UINT16                          uhwChip;                                /* 系统定时CHIP值 */
} WPHY_TOOL_TIMING_INFO_STRU;

/*****************************************************************************
 结构名    : UPHY_TOOL_WPHY_DRX_MNTN_INFO_STRU
 结构说明  : WPHY DRX可维可测信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      uwForbidSleepReason;        /* 禁止睡眠原因 */
    VOS_UINT32                                      uwSndSleepReqCnt;           /* WPHY 发送睡眠消息计数 */
    VOS_UINT32                                      uwSndSleepReqSlice;         /* WPHY 发送睡眠消息slice */
    VOS_UINT32                                      uwDrxRcvSleepSlice;         /* DRX  收到睡眠消息slice */
    VOS_UINT32                                      uwDrxSendSleepSlice;        /* DRX  发送睡眠消息slice */
    VOS_UINT32                                      uwDrxNeedWakeSlice;         /* DRX  预期唤醒slice */
    VOS_UINT32                                      uwDrxRcvWakeSlice;          /* DRX  收到唤醒消息slice */
    VOS_UINT32                                      uwDrxSendWakeSlice;         /* DRX  发送唤醒消息slice */
    VOS_UINT32                                      uwRcvWakeMsgCnt;            /* WPHY 接收到唤醒消息计数 */
    VOS_UINT32                                      uwRcvWakeMsgSlice;          /* WPHY 接收到唤醒消息slice*/
    VOS_UINT32                                      uwDcStartSlice;             /* WPHY 启动DC稳定延时定时器slice */
    VOS_UINT32                                      uwDcEndSlice;               /* WPHY DC稳定定时器超时slice */
    VOS_UINT32                                      uwMpStartSlice;             /* WPHY 第一次多径搜索启动slice */
    VOS_UINT32                                      uwRcvMpSrchIntCnt;          /* WPHY 接收到多径搜索中断计数 */
    VOS_UINT32                                      uwRcvMpSrchIntSlice;        /* WPHY 接收到多径搜索slice */
    VOS_UINT32                                      uwOpenSlotIntCnt;           /* WPHY 打开时隙中断计数 */
    VOS_UINT32                                      uwOpenSlotIntSlice;         /* WPHY 打开时隙中断slice */
    VOS_UINT32                                      uwPichSetupSlice;           /* WPHY PICH建立slice */
    VOS_UINT32                                      uwPiIntSlice;               /* WPHY PI中断slice */
    WPHY_TOOL_TIMING_INFO_STRU                      stPiRealTime;               /* WPHY PI位置时间 */
    WPHY_TOOL_TIMING_INFO_STRU                      stPichSetupTime;            /* WPHY PICH建立时间 */
}UPHY_TOOL_WPHY_DRX_MNTN_INFO_STRU;


/*****************************************************************************
 结构名    : UPHY_TOOL_DRX_LATE_INFO_IND_STRU
 结构说明  : 唤醒晚时的打点信息
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usRsv;                                          /* 保留字段 */
    VOS_UINT32                                  ulAwakeTime;                                    /* 需要唤醒的时间，W下为SFN，G下为Slice */
    VOS_UINT32                                  ulCurTime;                                      /* 实际唤醒的时间，W下为SFN，G下为Slice */
    VOS_UINT32                                  aulAwakeHWInfo[UPHY_TOOL_SLEEP_INFO_NUM];       /* OAM可维可测消息 */
    UPHY_TOOL_WPHY_DRX_MNTN_INFO_STRU           stWphyDrxMntn;                                  /* WPHY可维可测消息 */
}UPHY_TOOL_DRX_LATE_INFO_IND_STRU;

/*****************************************************************************
 结构名    : UPHY_TOOL_AGENTC_ESTIMATE_IND_STRU
 结构说明  : 代理模块盲切换评估阶段可维可测上报
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_INT16                                   sRxAGCValue;                    /* 外挂模上报滤波后的结果,单位为1dbm */
    VOS_UINT16                                  usNextState;                    /* 下一双天线状态 */
    VOS_UINT16                                  usAntStatus;                    /* 当前天线状态,0为直通，1为交叉 */
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
}UPHY_TOOL_AGENTC_ESTIMATE_IND_STRU;

/*****************************************************************************
 结构名    : UPHY_TOOL_AGENTC_COMPARE_IND_STRU
 结构说明  : 代理模块盲切换比较阶段可维可测上报
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_INT16                                   sDeltaRxAGCValue;               /* 外挂模上报滤波后的平均差值结果,单位为1dB */
    VOS_UINT16                                  usNextState;                    /* 下一双天线状态 */
    VOS_UINT16                                  usPhase;                        /* 比较阶段当前阶段 */
    VOS_UINT16                                  usAntStatus;                    /* 当前天线状态,0为直通，1为交叉 */
}UPHY_TOOL_AGENTC_COMPARE_IND_STRU;

/*****************************************************************************
 结构名    : UPHY_TOOL_AGENTC_PROTECT_IND_STRU
 结构说明  : 代理模块盲切换迟滞阶段可维可测上报
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usFrozenTime;                   /* 保护时间长度，1ms */
    VOS_UINT16                                  usNextState;                    /* 下一双天线状态 */
    VOS_UINT16                                  usAntStatus;                    /* 当前天线状态,0为直通，1为交叉 */
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
}UPHY_TOOL_AGENTC_PROTECT_IND_STRU;

/*****************************************************************************
  6.2 STRUCT定义,GPHY定义
*****************************************************************************/

/*****************************************************************************
 结构名    : GPHY_TOOL_COMMON_CNF_STRU
 结构说明  : GPHY可维可测公共回复消息结构
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip *//* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    GPHY_TOOL_MNTN_RSLT_ENUM_UINT16             enResult;                       /* 接收原语的处理结果ID */
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
}GPHY_TOOL_COMMON_CNF_STRU;


/*****************************************************************************
 结构名    : GPHY_TOOL_BLER_REPORT_REQ_STRU
 结构说明  : GPHY GPRS信道的误码率上报请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usBlerFlag;                     /* 是否上报BLER */
    VOS_UINT16                                  usRptPeriod;                    /* BLER上报的周期,单位:块数 */
}GPHY_TOOL_BLER_REPORT_REQ_STRU;


/*****************************************************************************
 结构名    : GPHY_TOOL_BLER_REPROT_IND_STRU
 结构说明  : GPHY上报BLER的结构和子结构
*****************************************************************************/

typedef struct
{
    VOS_UINT32                                  ulBlkCnt;
    VOS_UINT32                                  ulErrBlkCnt;
}GPHY_BLER_PARA_STRU;

typedef struct
{
    VOS_UINT32                                  ulRcvBlkCnt;
    VOS_UINT32                                  ulDummyCnt;
    GPHY_BLER_PARA_STRU                         stBlerPara[GPHY_PS_MAX_RX_TSN_NUM];
}GPHY_GPRS_BLER_RECORD_STRU;



typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;
    VOS_UINT16                                  usToolsId;
    GPHY_GPRS_BLER_RECORD_STRU                  stGprsBlerRecord;
}GPHY_TOOL_BLER_REPORT_IND_STRU;



/*****************************************************************************
 结构名    : GPHY_TOOL_SNR_REPORT_REQ_STRU
 结构说明  : GPHY GPRS信道的SNR上报请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usSNRFlag;                      /* 是否上报SNR */
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
}GPHY_TOOL_SNR_REPORT_REQ_STRU;


/*****************************************************************************
 结构名    : GPHY_TOOL_SNR_REPROT_IND_STRU
 结构说明  : GPHY上报SNR的结构和子结构
*****************************************************************************/

typedef struct
{
    VOS_UINT16                                  usRptValidNum;
    VOS_UINT16                                  usRsv;
    VOS_INT16                                   sSNR[GPHY_PS_MAX_RX_TSN_NUM];
    VOS_UINT16                                  usRsv2;
}GPHY_GPRS_SNR_RECORD_STRU;

/* 可维可测:SNR上报结构 */
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;
    VOS_UINT16                                  usToolsId;
    GPHY_GPRS_SNR_RECORD_STRU                   stGprsSNRRecord;
}GPHY_TOOL_SNR_REPORT_IND_STRU;



/*****************************************************************************
 结构名    : GPHY_TOOL_AFC_REPORT_REQ_STRU
 结构说明  : GPHY AFC积分值信息上报请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usAFCFlag;                      /* 是否上报AFC值 */
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
}GPHY_TOOL_AFC_REPORT_REQ_STRU;



/*****************************************************************************
 结构名    : GPHY_TOOL_AFC_REPROT_IND_STRU
 结构说明  : GPHY上报AFC的结构
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;
    VOS_UINT16                                  usToolsId;
    VOS_INT16                                   sAFCOffset;
    VOS_UINT16                                  usRsv;
}GPHY_TOOL_AFC_REPORT_IND_STRU;




/*****************************************************************************
 结构名    : GPHY_TOOL_POWER_CTRL_REPORT_REQ_STRU
 结构说明  : GPHY 数传下功控信息上报请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usPwrCtrlFlag;                  /* 是否上报功率控制 */
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
}GPHY_TOOL_POWER_CTRL_REPORT_REQ_STRU;



/*****************************************************************************
 结构名    : GPHY_GPRS_POWER_CTRL_REPROT_IND_STRU
 结构说明  : GPHY上报功率控制参数的结构和子结构
*****************************************************************************/

typedef struct
{
    VOS_UINT16                                  usTxChannel;
    VOS_UINT16                                  usTxTn;
    VOS_INT16                                   sTxPwr;
    VOS_UINT16                                  usGammaTn;
    VOS_UINT16                                  usGammaBand;
    VOS_UINT16                                  usAlpha;
    VOS_UINT16                                  usPMax;
    VOS_UINT16                                  usRsv;
}GPHY_PWR_CTRL_PARA_STRU;

typedef struct
{
    VOS_UINT16                                  usTxCnt;
    VOS_UINT16                                  usRsv;
    GPHY_PWR_CTRL_PARA_STRU                     stPwrCtrlPara[GPHY_PS_MAX_TX_TSN_NUM];
}GPHY_POWER_CONTROL_RECORD_STRU;


typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;
    VOS_UINT16                                  usToolsId;
    GPHY_POWER_CONTROL_RECORD_STRU              stPwrCtrlRecord;
}GPHY_TOOL_POWER_CTRL_REPORT_IND_STRU;




/*****************************************************************************
 结构名    : GPHY_TOOL_POWER_CTRL_SET_REQ_STRU
 结构说明  : GPHY 数传下指定功率发射设置请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usPwrCtrlFlag;                  /* 是否按照指定功率发射 */
    VOS_UINT16                                  usTxPwr;                        /* 指定功率,单位:0.1dB */
}GPHY_TOOL_POWER_CTRL_SET_REQ_STRU;



/*****************************************************************************
 结构名    : GPHY_GPRS_POWER_CTRL_REPROT_IND_STRU
 结构说明  : GPHY上报EGPRS信道质量上报结构
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usGmskMeanBep;                  /* 0-31,0xff为无效值 */
    VOS_UINT16                                  us8PSKMeanBep;                  /* 0-31,0xff为无效值 */
    VOS_UINT16                                  usGmskCvBep;                    /* 0-7,0xff为无效值 */
    VOS_UINT16                                  us8PSKCvBep;                    /* 0-7,0xff为无效值 */
}GPHY_TOOL_CHANNEL_QUALITY_IND_STRU;


/*****************************************************************************
 结构名    : GPHY_TOOL_FUNC_BIT_CTRL_REQ_STRU
 结构说明  : GPHY 可维可测功能控制下发的结构原语:用来控制功能设置请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT32                                  ulFuncBitMask;                  /* 对应Bit位置位,则控制该功能生效 */
}GPHY_TOOL_FUNC_BIT_CTRL_REQ_STRU;



/*****************************************************************************
 结构名    : GPHY_TOOL_PARA_CONTROL_REQ_STRU
 结构说明  : GPHY可维可测参数控制下发的结构原语:用来控制参数设置请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    GPHY_TOOL_PARA_CTRL_ENUM_UINT16             enParaId;                       /* 参数的ID,控制参数的列表 */
    VOS_UINT16                                  usParaCtrlFlg;                  /* 是否控制该参数 */
    VOS_UINT32                                  ulParaValue1;                   /* 控制参数的值 */
    VOS_UINT32                                  ulParaValue2;                   /* 目前保留,便于扩展 */
}GPHY_TOOL_PARA_CONTROL_REQ_STRU;




/*****************************************************************************
 结构名    : GPHY_TOOL_RF_FRONT_STATIC_REQ_STRU
 结构说明  : GPHY 上报前端动态信息上报请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usMsgRptFlag;                   /* 指示消息监控的上报内容是否有变更 */
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
}GPHY_TOOL_RF_FRONT_STATIC_REQ_STRU;


/*****************************************************************************
 结构名    : GPHY_TOOL_BBP_RTC_REQ_STRU
 结构说明  : RTC功能打开和关闭设置
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    UPHY_TOOL_RTC_DEBUG_ENUM_UINT16             enRtcCtrl;                      /* RTC打开或者关闭 */
    VOS_UINT16                                  usRsv;

}GPHY_TOOL_BBP_RTC_REQ_STRU;



/*****************************************************************************
 结构名    : GPHY_TOOL_RF_FRONT_STATIC_IND_STRU
 结构说明  : GPHY上报前端动态信息上报
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */

    VOS_UINT16                                  usRfTrcvOnState;                /* RF总开关，1为打开，0为关闭 */
    VOS_UINT16                                  usRfRxOnOrOff;                  /* 04h[1:0] = 3为开 */
    VOS_UINT16                                  usRxPathselect;                 /* 04h[4:3] = 3为主分集都开，2开主集 */
    VOS_UINT16                                  usAbbRxConfig;                  /* 7为主分集都开，3开主集 */

    VOS_UINT16                                  usRfTxOnOrOff;                  /* 02h[1:0] = 3为开 */
    VOS_UINT16                                  usRfTxSHDN;                     /* RF上行打开控制，0由BBP控制 */

    VOS_UINT16                                  usGpioFuncOn;                   /* 硬件支持GPIO */
    VOS_UINT16                                  usGpioPaMode;                   /* GPIO PA mode */

    VOS_UINT16                                  usMipiFuncOn;                   /* 硬件支持MIPI */
    VOS_UINT16                                  usMipiPaMode;                   /* MIPI PA mode */

    VOS_UINT16                                  usAptFuncOn;                    /* 硬件支持APT */
    VOS_UINT16                                  usAptPaMode;                    /* APT电压mode */
}GPHY_TOOL_RF_FRONT_STATIC_IND_STRU;





/*****************************************************************************
 结构名    : GPHY_TOOL_INTRA_MSG_RPT_CTRL_REQ_STRU
 结构说明  : PHY 内部消息上报控制请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usMsgRptFlag;                   /* 指示内部消息是否上报 */
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
}GPHY_TOOL_INTRA_MSG_RPT_CTRL_REQ_STRU;




/*****************************************************************************
 结构名    : GPHY_TOOL_AMR_REPORT_REQ_STRU
 结构说明  : GPHY 语音下AMR信道编译码速率上报请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usAmrRptFlag;                   /* 是否上报AMR信息 */
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
}GPHY_TOOL_AMR_REPORT_REQ_STRU;


/*****************************************************************************
 结构名    : GPHY_TOOL_AMR_REPORT_IND_STRU
 结构说明  : GPHY上报AMR信息参数
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usCrcErrFlg;                    /* 译码结果0-正确;1-错误 */
    VOS_UINT16                                  usDecodeMode;                   /* 下行编码方式 */
    VOS_UINT16                                  usDecodeRate;                   /* 下行编码速率 */
    VOS_UINT16                                  usEncodeMode;                   /* 上行编码方式 */
    VOS_UINT16                                  usEncodeRate;                   /* 上行编码速率 */
    VOS_UINT16                                  usRsv;
}GPHY_TOOL_AMR_REPORT_IND_STRU;




/*****************************************************************************
 结构名    : GPHY_TOOL_BLK_REPORT_LIST_REQ_STRU
 结构说明  : GPHY抓取非固定地址的数据
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulBlkAddr;                      /* 抓取数据块的首地址 */
    VOS_UINT32                                  ulBlkLen;                       /* 抓取数据块的长度,单位:32bit */
}GPHY_TOOL_BLK_REPORT_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usRptFlag;
    VOS_UINT16                                  usRsv;
    GPHY_TOOL_BLK_REPORT_STRU                   astRptBlk[GPHY_TOOL_RPT_BLK_MAX_NUM];
}GPHY_TOOL_BLK_REPORT_LIST_REQ_STRU;



/*****************************************************************************
 结构名    : GPHY_TOOL_BLK_REPORT_LIST_IND_STRU
 结构说明  : GPHY抓取非固定地址的数据
*****************************************************************************/

typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    GPHY_TOOL_BLK_REPORT_STRU                   astRptBlk[GPHY_TOOL_RPT_BLK_MAX_NUM];
    VOS_UINT32                                  aulData[2];
}GPHY_TOOL_BLK_REPORT_LIST_IND_STRU;


/*****************************************************************************
 结构名    : GPHY_TOOL_RCV_BURST_INFO_STRU
 结构说明  : 单时隙接收信息的结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulMeaFn;                            /* 上报测量中断时的帧号 */
    VOS_UINT16                              usMeaArfcn;                         /* 上报测量的频点 */
    GPHY_TOOL_TIMESLOT_MEAS_TYPE_ENUM_UINT16  usTsMeasType;                     /* 测量类型 */
    VOS_UINT16                              usNextAgcGain;                      /* AGC档位 */
    VOS_INT16                               sAgcRssi;                           /* 测量值:0.125dB */
    VOS_UINT32                              ulDrssi;                            /* DRSSI求对数运算前数值上报 */
    VOS_UINT32                              ulLsDcValue;
    VOS_UINT32                              ulGrossCarrierEn;
    VOS_UINT32                              ulGrossInterfereEn;
    VOS_UINT32                              ulValppCarrierEn;
    VOS_UINT32                              ulValppInterfereEn;
    VOS_UINT16                              usNbPosAdj;
    VOS_UINT16                              usToaSelResult;
}GPHY_TOOL_RCV_BURST_INFO_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_RCV_SINGAL_INFO_REQ_STRU
 结构说明  : 单帧接收信息的结构
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT32                                  ulCurFn;
    VOS_UINT16                                  usAfcValue;
    VOS_INT16                                   sAfcTempComp;
    VOS_UINT32                                  ulReserved[2];
    GPHY_TOOL_RCV_BURST_INFO_STRU               astBurstInfo[GPHY_TOOL_TN_NUM_IN_FRAME];
    VOS_UINT32                                  ulBBPCOMMC0TxPriModeAddr;         /* 对应寄存器BBPCOMM_C0_PRIMARY_MODE_IND_ADDR的值  */
    VOS_UINT32                                  ulBBPCOMMC0RxPriModeAddr;         /* BBPCOMM_C1_PRIMARY_MODE_IND_ADDR  */
    VOS_UINT32                                  ulBBPCOMMC1TxPriModeAddr;         /* 对应寄存器BBPCOMM_C0_PRIMARY_MODE_IND_ADDR的值  */
    VOS_UINT32                                  ulBBPCOMMC1RxPriModeAddr;         /* BBPCOMM_C1_PRIMARY_MODE_IND_ADDR  */
    VOS_UINT32                                  ulBBPCOMMC2TxPriModeAddr;         /* 对应寄存器BBPCOMM_C0_PRIMARY_MODE_IND_ADDR的值  */
    VOS_UINT32                                  ulBBPCOMMC2RxPriModeAddr;         /* BBPCOMM_C1_PRIMARY_MODE_IND_ADDR  */
    VOS_UINT32                                  ulBBPCOMMC3TxPriModeAddr;         /* 对应寄存器BBPCOMM_C0_PRIMARY_MODE_IND_ADDR的值  */
    VOS_UINT32                                  ulBBPCOMMC3RxPriModeAddr;         /* BBPCOMM_C1_PRIMARY_MODE_IND_ADDR  */
    VOS_UINT32                                  ulBBPCOMMGsChSwAddr;            /* BBPCOMM_GS_CH_SW_ADDR  */
    VOS_UINT32                                  ulBBPCOMMPmuChSel0Addr;         /* BBPCOMM_PMU_CH_SEL0_ADDR */
    VOS_UINT32                                  ulBBPCOMMDbgReg20CpuAddr;       /* BBPCOMM_DBG_REG20_CPU_ADDR */
    VOS_UINT16                                  usReserved1;                    /* 保留字段 */
    VOS_UINT16                                  usReserved2;                    /* 保留字段 */
}GPHY_TOOL_RCV_SINGAL_INFO_REQ_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_REPORT_ERROR_IND_STRU
 结构说明  : GPHY信息,告警,error上报结构
*****************************************************************************/

typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usFileNo;                       /* 文件名编码 */
    VOS_UINT16                                  usLineNo;                       /* 出错的行号 */
    VOS_UINT32                                  ulTimeSlice;
    VOS_UINT32                                  ulLogId;                        /* PHY软件内统一编号LOG ID */
    VOS_UINT16                                  usReserved;                     /* 保留字段 */
    VOS_UINT16                                  usVarCnt;                       /* 上报变量个数 */
    VOS_UINT32                                  aulVarValue[GPHY_TOOL_MNTN_ERROR_RPT_VAR_NUM]; /* 上报变量值 */
}GPHY_TOOL_REPORT_ERROR_IND_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_RCV_SINGAL_INFO_REQ_STRU
 结构说明  : 单帧接收信息的结构
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_INT16                                   shwCurrTemp;                    /* 当前温度 */
    VOS_INT16                                   shwXoInitTemp;                  /* 校准温度 */
    VOS_INT32                                   swTempCompValue;                /* 本次计算的温度补偿结果 */
    VOS_UINT32                                  auwMantissa[4];  /* DCXO多项式系数 */
    VOS_UINT16                                  auhwExponent[4]; /* DCXO多项式系数 */
}UPHY_TOOL_DCXO_TEMP_COMP_INFO_IND_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_DCH_OCCASION_USE_INFO_STRU
 结构说明  : 空闲帧任务信息的结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  uwTaskFn;
    VOS_UINT16                                  enTaskType;
    VOS_UINT16                                  uhwFreqNum;                     /* 专用态IDLE帧做邻区任务的频点数目 */
    VOS_UINT16                                  enOccasionUseMode;              /* 当前是哪个模式在使用 */
    VOS_UINT16                                  auhwFreqInfo[GPHY_TOOL_MAX_SYNC_TASK_NUM]; /* 专用态IDLE帧最多可以做5个BSIC验证 */
}GPHY_TOOL_DCH_OCCASION_USE_INFO_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_DCH_OCCASION_USE_RPT_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT32                                  ulCurFn;
    VOS_UINT16                                  uhwTimeOutCnt;
    VOS_UINT16                                  uhwOccasionNum;
    GPHY_TOOL_DCH_OCCASION_USE_INFO_STRU        astOccasionUseInfo[ GPHY_TOOL_MAX_IDLE_FRAME_NUM ];
}GPHY_TOOL_DCH_OCCASION_USE_RPT_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_BSIC_SEARCH_INFO_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  enBsicSrchState;
    VOS_UINT16                                  uhwFreq;
    VOS_UINT16                                  uhwRank;
    VOS_UINT16                                  enNStrongIndex;
    VOS_INT16                                   shwRxlev;
    VOS_UINT16                                  uhwReserved;
}GPHY_TOOL_BSIC_SEARCH_INFO_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_BSIC_VERIFY_INFO_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT32                                  uwCurFn;
    VOS_UINT16                                  enBsicVerifyState;
    VOS_UINT16                                  uhwFreq;
    VOS_UINT16                                  uhwRank;
    VOS_UINT16                                  enNStrongIndex;
    VOS_INT16                                   shwRxlev;
    VOS_INT16                                   shwDCOffsetI;
    VOS_INT16                                   shwDCOffsetQ;
    VOS_UINT16                                  uhwAgcGain;
    VOS_UINT32                                  uwSNR;
    VOS_UINT16                                  uhwBsic;
    VOS_UINT16                                  uhwNCC;
    VOS_UINT16                                  uhwBCC;
    VOS_UINT16                                  uhwReserved;
}GPHY_TOOL_BSIC_VERIFY_INFO_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_NCELL_RANK_INFO_STRU
 结构说明  : GSM 邻区优先级信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usBaListIndex;
    VOS_UINT16                                  usFreq;
    VOS_UINT16                                  usRank;
    VOS_INT16                                   sRxlev;
    VOS_UINT16                                  usNStrongIndex;
    VOS_UINT16                                  usBsicKnownFlag;
    VOS_UINT16                                  usBsic;
    VOS_UINT16                                  usNCC;
    VOS_UINT16                                  usBCC;
    VOS_UINT16                                  usInMRFlag;
}GPHY_TOOL_NCELL_RANK_INFO_STRU;


/*****************************************************************************
 结构名    : GPHY_TOOL_INTERRAT_RANK_INFO_STRU
 结构说明  : 异系统优先级信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usRank;
    VOS_UINT16                                  usMaxGapNum;                    /* 最大可分配的沟的数目 */
    VOS_UINT16                                  usAssignedGapNum;               /* 已分配的沟的数目 */
    VOS_UINT16                                  usResv;
}GPHY_TOOL_INTERRAT_RANK_INFO_STRU;


/*****************************************************************************
 结构名    : GPHY_TOOL_NCELL_INTERRAT_RANK_RPT_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    GPHY_TOOL_NCELL_RANK_INFO_STRU              astNcellRankInfo[GPHY_TOOL_MAX_NCELL_NUM];
    GPHY_TOOL_INTERRAT_RANK_INFO_STRU           stInterratRankInfo;
}GPHY_TOOL_NCELL_INTERRAT_RANK_RPT_STRU;


/*****************************************************************************
 结构名    : GPHY_TOOL_DCH_OCCASION_USE_RPT_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwCurFn;
    VOS_UINT16                          uhwCurFnT2;
    VOS_UINT16                          uhwPredictTask;
}GPHY_TOOL_NCELL_RECORD_PREDICT_TASK_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_DCH_OCCASION_USE_RPT_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  uhwNcellBcchOccupy;             /* 是否被邻区读系统广播消息占据 */
    VOS_UINT16                                  uhwSrchRank;                    /* 搜索频点的最高优先级*/
    VOS_UINT16                                  uhwInterRatRank;                /* 异系统频点的最高优先级*/
    VOS_UINT16                                  uhwVerifyRank;                  /* 验证频点的最高优先级 */
    GPHY_TOOL_NCELL_RECORD_PREDICT_TASK_STRU    astRecordPredictTask[ GPHY_TOOL_NCELL_RPT_PREDICT_TASK_INFO_NUM ];
}GPHY_TOOL_NCELL_PREDICT_TASK_RPT_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_CHN_DUMMY_BURST_RPT_IND
 结构说明  :
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  uhwDummyPchFlag;                /* 单帧解寻呼的检测结果 */
    VOS_UINT16                                  uhwAverageValue;                /* 根据绝对值求和后的值取平均(根据算法链路扩大了16倍) */
    VOS_UINT32                                  uwFN;                           /* 当前帧号 */
    VOS_INT32                                   swJudgeDataC;                   /* 计算出的中间值 */
    VOS_INT32                                   swJudgeDataD;                   /* 计算出的中间值 */
    VOS_INT32                                   swJudgeDataE;                   /* 计算出的中间值 */
    VOS_INT32                                   swJudgeDataF;                   /* 计算出的中间值 */
}GPHY_TOOL_CHN_DUMMY_PCH_RPT_STRU;



/*****************************************************************************
 结构名    : GPHY_TOOL_SRVCC_BSIC_RSLT_INFO_STRU
 协议表格  :
 结构说明  : SRVCC BSIC小区信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usArfcn;                        /* 频点 */
    VOS_UINT16                                  usRssiOrder;                    /* 当前小区按照能量排序,在LRRC给出的列表中的能量排序. */
    VOS_UINT16                                  usInitSrchFailCnt;              /* 周期内初始确认失败次数. */
    VOS_UINT16                                  usLRRCReCfgFlag;                /* 失败小区如果LRRC重配 */
    VOS_UINT16                                  usSbVerifiedFlag;               /* 在SB重确认周期内,小区是否已经完成验证标志 */
    VOS_UINT16                                  usSbVerifyFailCount;            /* 重确认小区重确认失败次数 */
    VOS_UINT16                                  usBsicSucORFailFlag;            /* 同步是否成功 */
    VOS_UINT16                                  usBsicCellType;                 /* 同步类型 */
    VOS_UINT32                                  ulFbSearchLength;               /* FB搜索总长度 */
    VOS_UINT32                                  ulGSlaveOffsetFn;               /* 上一次搜索时得到的W/L/TD和G偏差的Fn */
    VOS_UINT16                                  usGSlaveOffsetQb;               /* 上一次搜索时得到的W/L/TD和G偏差的Qb */
    VOS_UINT16                                  usNcellTOAOffset;               /* 相对于Timebase的偏差,由G FB搜索时提供该值,在SB搜索时使用 */
    VOS_UINT32                                  ulNcellFrameNum;                /* GSM 邻小区的帧号信息，邻区使用低16bitTDMA帧号低位0~26x51-1循环计数 */

}GPHY_TOOL_SRVCC_BSIC_RSLT_INFO_STRU;


/*****************************************************************************
 结构名    : GPHY_TOOL_SRVCC_SCHEDULE_INFO_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usGSlaveGapTask;                /* 一级任务:当前GAP分配的任务类型. */
    VOS_UINT16                                  usGSlaveCfgType;                /* 二级任务:当前需要配置的类型. */
    VOS_UINT16                                  usGRssiPeriodStartFlag;         /* GSM从模开始新一轮测量,测量完成后清除. */
    VOS_UINT16                                  usSrvccFbSrchIndex;             /* 执行初始确认的索引,在完成一个后索引置为无效.在下发任务时无效. */
    VOS_UINT16                                  usPeriodFbCnt;                  /* 周期性GAP周期性搜索FB次数 */
    VOS_UINT16                                  usPeriodGapFlag;                /* 周期性GAP周期性搜索FB次数 */
    VOS_UINT16                                  usSrvccSbCellIndex;             /* 执行SB任务小区的索引,完成一个小区的SB验证后,设置为无效值 */
    VOS_UINT16                                  usCurBsicTaskType;              /* 当前是那种类型的任务优先. */
    VOS_UINT16                                  usSbVerifyPeriorFlag;           /* SB验证优先级是否高 */
    VOS_UINT16                                  usOffLineSaveIndex;             /* 离线译码当前存储的索引. */
    VOS_UINT16                                  usOffLineValidIndex;            /* 有效索引的Index,存储多个间隔不一致,大于245ms的索引置为无效,无需在计算. */
    VOS_UINT16                                  usBsicNum;                      /* 原语下发的小区个数，初始确认重确认都在同一个表中，BSIC小区个数包括初始确认和重确认 */
    VOS_UINT16                                  usCalFreqNum;                   /* 配置RSSI测量小区个数 */
    VOS_UINT16                                  usFreqIndex;                    /* RSSI小区索引 */
    VOS_UINT32                                  ulSbVerifyFbSrchTotalTime;      /* 在SB验证期间,可能执行FB SRCH,在计算SB验证时间超时时,需要扣除SB SRCH的时间, */
    VOS_UINT32                                  ulSbVerifyFbSrchStartTime;      /* 在SB验证期间,可能执行FB SRCH,FB SRCH起始时间点. */
    VOS_UINT32                                  ulSbPeriodStartSlice;           /* SB验证周期的起始时间点. */

    GPHY_TOOL_SRVCC_BSIC_RSLT_INFO_STRU         astCellBSICInfo[GPHY_TOOL_SLAVE_BSIC_MAX_NUM];

}GPHY_TOOL_SRVCC_SCHEDULE_INFO_STRU;





/*****************************************************************************
  6.2 STRUCT定义,WPHY定义
*****************************************************************************/
/*****************************************************************************
 结构名    : WPHY_TOOL_PA_GAIN_SWITCH_COMP_INFO_STRU
 协议表格  :
 结构说明  : W TX PA增益切换时功率补偿值
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwH2MComp;                             /* PA增益从高切到中的门限补偿,单位0.1db */
    VOS_INT16                           shwM2HComp;                             /* PA增益从中切到高的门限补偿,单位0.1db */
    VOS_INT16                           shwM2LComp;                             /* PA增益从中切到低的门限补偿,单位0.1db */
    VOS_INT16                           shwL2MComp;                             /* PA增益从低切到中的门限补偿,单位0.1db */
}WPHY_TOOL_PA_GAIN_SWITCH_COMP_INFO_STRU;


/*****************************************************************************
 结构名    : WPHY_MNTN_TX_PA_GAIN_SWITCH_COMP_STRU
 协议表格  :
 结构说明  : W TX 4个时隙的PA增益切换时功率补偿值
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_PA_GAIN_SWITCH_COMP_INFO_STRU  astSlotComp[WPHY_TOOL_PA_SWITCH_COMP_SLOT];
}WPHY_TOOL_TX_PA_GAIN_SWITCH_COMP_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_PA_GAIN_SWITCH_COMP_REQ_STRU
 结构说明  : PA益切换补偿原语
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                              uhwMsgID;                           /* Msg ID */
    VOS_UINT16                              uhwRsv1;                            /* 保留 */

    WPHY_TOOL_TX_PA_GAIN_SWITCH_COMP_STRU   stPaGainSwitchComp;

}WPHY_TOOL_PA_GAIN_SWITCH_COMP_REQ_STRU;



/*****************************************************************************
 结构名    : WPHY_TOOL_SIG_PA_GAIN_SWITCH_COMP_IND_STRU
 结构说明  : PA益切换补偿原语的结果
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwH2M;                                 /* 高到中增益补偿 */
    VOS_INT16                           shwM2H;                                 /* 中到高增益补偿 */
    VOS_INT16                           shwM2L;                                 /* 中到低增益补偿 */
    VOS_INT16                           shwL2M;                                 /* 低到中增益补偿 */
}WPHY_TOOL_SIG_PA_GAIN_SWITCH_COMP_IND_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_PA_GAIN_SWITCH_COMP_CNF_STRU
 结构说明  : PA益切换补偿原语的回复
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          uhwTransId;                              /* 原语ID,固定值:0x5001 */
    VOS_UINT16                          uhwReserved1;                            /* 保留字段 */
    VOS_UINT16                          uhwFuncType;                            /* 固定值:0x04 */
    VOS_UINT16                          uhwLength;                              /* 从uwSn至结尾的长度 */
    VOS_UINT32                          uwSn;                                   /* 固定值:0 */
    VOS_UINT32                          uwTimeStamp;                            /* 上报CNF或者SFN */
    VOS_UINT16                          uhwPrimId;                              /* WDSP_MNTN_MSG_ID_ENUM_UINT16,消息ID  */
    VOS_UINT16                          uhwReserved2;                           /* */
    VOS_UINT32                          uwResult;                               /* 消息内容起始地址 */
    WPHY_TOOL_SIG_PA_GAIN_SWITCH_COMP_IND_STRU    stRfPaGainSwitchCompInd;       /* 当前增益补偿上报*/
}WPHY_TOOL_PA_GAIN_SWITCH_COMP_CNF_STRU;



/*****************************************************************************
 结构名    : WPHY_TOOL_POW_DET_ENABLE_REQ_STRU
 结构说明  : 该项是测试通过SDT实时打开关闭PD的函数的请求原语
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          uhwMsgID;                               /* Msg ID */
    VOS_UINT16                          uhwRsv1;                                /* 保留 */
    VOS_UINT32                          uwPdEnFlg;                              /* PD使能标记，0:去使能，1:使能*/
}WPHY_TOOL_POW_DET_ENABLE_REQ_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_POW_DET_ENABLE_CNF_STRU
 结构说明  : 该项是测试通过LMT实时打开关闭PD的函数的回复原语
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          uhwTransId;                              /* 原语ID,固定值:0x5001 */
    VOS_UINT16                          uhwReserved1;                            /* 保留字段 */
    VOS_UINT16                          uhwFuncType;                            /* 固定值:0x04 */
    VOS_UINT16                          uhwLength;                              /* 从ulSn至结尾的长度 */
    VOS_UINT32                          uwSn;                                   /* 固定值:0 */
    VOS_UINT32                          uwTimeStamp;                            /* 上报CNF或者SFN */
    VOS_UINT16                          uhwPrimId;                              /* WDSP_MNTN_MSG_ID_ENUM_UINT16，消息ID  */
    VOS_UINT16                          uhwReserved2;                           /* */
    VOS_UINT32                          uwErrCode;                              /* 结果 */
}WPHY_TOOL_POW_DET_ENABLE_CNF_STRU;



/*****************************************************************************
 结构名    : WPHY_TOOL_COMMON_CNF_STRU
 结构说明  : WPHY可维可测公共回复消息结构
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MNTN_RSLT_ENUM_UINT16             enResult;                       /* 接收原语的处理结果ID */
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
}WPHY_TOOL_COMMON_CNF_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_ACT_CELL_REQ_STRU
 结构说明  : 激活集小区信息
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_REPORT_TYPE_ENUM_UINT16      enReportType;
    VOS_UINT16                                  usReportPeriod;                /* 默认0，标识无效，当上报周期为指定周期时，该IE有效。*/
}WPHY_MNTN_REPORT_TYPE_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_MNTN_REPORT_TYPE_STRU                  stReportType;                   /* 默认每帧上报  */
}WPHY_TOOL_ACT_CELL_REQ_STRU;



/*****************************************************************************
 结构名    : WPHY_TOOL_ACT_CELL_INFO_IND_STRU
 结构说明  : 激活集小区信息
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usSfn;
    VOS_UINT16                                  usCfn;
    VOS_UINT16                                  ausScramble[WPHY_MNTN_MAX_ACT_CELL_NUM]; /* 激活集小区的扰码 */
    VOS_UINT16                                  usServingCellScramble;                   /* 主小区扰码 */
}WPHY_TOOL_ACT_CELL_INFO_IND_STRU;



/*****************************************************************************
 结构名    : WPHY_TOOL_CELL_SEARCH_LIST_REQ_STRU
 结构说明  : 小区搜索列表信息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_MNTN_REPORT_TYPE_STRU                  stReportType;                   /* 默认事件触发上报，每次小区搜索上报  */
}WPHY_TOOL_CELL_SEARCH_LIST_REQ_STRU;



/*****************************************************************************
 结构名    : WPHY_TOOL_CELL_SEARCH_LIST_IND_STRU
 结构说明  : 小区搜索列表信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usScramble;
    VOS_UINT16                                  usEnergy;
    VOS_UINT32                                  ulPhase;                        /* 需要转换为Chip级别 */
    VOS_UINT16                                  usLifeCycle;                    /* 生命周期 */
    VOS_UINT16                                  usRsv;
}WPHY_MNTN_CS_LIST_CELL_INFO_STRU;

typedef struct
{
    VOS_UINT16                                  usFreq;
    VOS_UINT16                                  usCnt;
    WPHY_MNTN_CS_LIST_CELL_INFO_STRU            astCellInfo[32];

}WPHY_MNTN_CS_LIST_INFO_STRU;


typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usSfn;
    VOS_UINT16                                  usCfn;
    VOS_UINT16                                  usFreqCnt;
    VOS_UINT16                                  usRsv;
    WPHY_MNTN_CS_LIST_INFO_STRU                 astCsList[3];
}WPHY_TOOL_CELL_SEARCH_LIST_IND_STRU;





/*****************************************************************************
 结构名    : WPHY_TOOL_PWR_SWITCH_CTRL_REQ_STRU
 结构说明  : 功控功能控制，指定打开或关闭如下的功控功能:
               1.下行功控开关(如果此开关关闭，则标识所有的功控功能全部失效,
                  包括内环功控，外环功控，Winup,Windown等，
                  此时可以再通过功率设置参数来设置上行TPC,SirTarget等。)
               2.外环功控(如果此功能关闭，仅标识外环功能关闭，此时可以通过
                  功率参数设置功能来设置SirTarget。)
               3.Windown
               4.Winup
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MNTN_PWR_SWITCH_TYPE_ENUM_UINT16  enPCType;
    WPHY_TOOL_MNTN_SWITCH_CTRL_ENUM_UINT16      enStatus;

}WPHY_TOOL_PWR_SWITCH_CTRL_REQ_STRU;



/*****************************************************************************
 结构名    : WPHY_TOOL_PWR_PARA_SET_REQ_STRU
 结构说明  : 功率参数设置，以Mask标识有效标记
               1.SirTarget
               2.初始发射功率
               3.Hold上行发射功率(设置最大最小发射功率)
               4.设置指定发送的上行TPC.
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MNTN_PWR_PARA_ENUM_UINT32         enPwrParaMask;
    VOS_UINT32                                  ulSirTarget;                    /* SirTarget */
    VOS_INT16                                   sInitTxPwr;                     /* 初始功率 */
    VOS_INT16                                   sUlTpc;                         /* 上行TPC */
    VOS_INT16                                   sMaxTxPwr;                      /* 最大发射功率 */
    VOS_INT16                                   sMinTxPwr;                      /* 最小发射功率 */

}WPHY_TOOL_PWR_PARA_SET_REQ_STRU;





/*****************************************************************************
 结构名    : WPHY_TOOL_MNTN_BLER_REQ_STRU
 结构说明  : 误块率上报
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_MNTN_REPORT_TYPE_STRU                  stReportType;                   /* 默认每帧上报  */

}WPHY_TOOL_BLER_REPORT_REQ_STRU;


/*****************************************************************************
 结构名    : WPHY_MNTN_TRCH_BLER_STRU
 结构说明  : 误块率上报功能
             误块率 = ulErrorBlocks/ulTotalBlocks
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usTrchId;
    VOS_UINT16                                  usTti;                          /* 每个传输信道的TTI */
    VOS_UINT32                                  ulErrorBlocks;                  /* 错块数  */
    VOS_UINT32                                  ulTotalBlocks;                  /* 总块数 */

}WPHY_MNTN_TRCH_BLER_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_MNTN_BLER_IND_STRU
 结构说明  : 误块率上报功能
             每次上报的传输信道个数不固定，个数多少根据CNT确定。
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usSfn;
    VOS_UINT16                                  usCfn;
    VOS_UINT16                                  usCnt;
    VOS_UINT16                                  usRsv;
    WPHY_MNTN_TRCH_BLER_STRU                    astTrchBler[WPHY_MNTN_TRCH_NUM];

}WPHY_TOOL_BLER_REPORT_IND_STRU;







/*****************************************************************************
 结构名    : WPHY_MNTN_EVENT_REPORT_REQ_STRU
 结构说明  : 事件上报控制
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MNTN_EVENT_TYPE_ENUM_UINT32       enEventTypeMask;

}WPHY_TOOL_EVENT_REPORT_REQ_STRU;



/*****************************************************************************
 结构名    : WPHY_TOOL_SYNC_STATUS_IND_STRU
 结构说明  : W下同步失步状态上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usSfn;
    VOS_UINT16                                  usCfn;
    WPHY_TOOL_SYNC_STATUS_ENUM_UINT16           enSyncStatus;
    VOS_UINT16                                  usRsv;
}WPHY_TOOL_SYNC_STATUS_IND_STRU;




/*****************************************************************************
 结构名    : WPHY_TOOL_AFC_STATUS_IND_STRU
 结构说明  : AFC锁定
   EVENT_VCTCXO_FREEZE ,EVENT_VCTCXO_UNFREEZE
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usSfn;
    VOS_UINT16                                  usCfn;
    WPHY_TOOL_TCXO_STATUS_ENUM_UINT16           enTcxoStatus;
    VOS_UINT16                                  usRsv;
    VOS_UINT32                                  ulAfcStatusValue;

}WPHY_TOOL_AFC_STATUS_IND_STRU;



/*****************************************************************************
 结构名    : WPHY_TOOL_MNTN_INTERRUPT_EXCEPTIION_IND_STRU
 结构说明  : 中断异常事件上报，
               1.在6ms任务结束时，读取9ms任务已经到达。
               2.在9ms任务结束时，读取SFN判断该任务是否已经跨帧。
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usSfn;
    VOS_UINT16                                  usCfn;

    WPHY_TOOL_MNTN_INT_EXCEPT_ENUM_UINT16       enIntExceptType;                /* 中断异常类型 */
    VOS_UINT16                                  usRsv;
}WPHY_TOOL_INTERRUPT_EXCEPTIION_IND_STRU;



/*****************************************************************************
 结构名    : WPHY_TOOL_WCDMA_L1_STATUS_IND_STRU
 结构说明  : 上报L1状态
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usSfn;
    VOS_UINT16                                  usCfn;

    VOS_UINT32                                  ulChannelStatus;                /* 信道状态 */
    WPHY_TOOL_MNTN_SYS_STATUS_ENUM_UINT16       enSysStatus;                    /* 系统状态 */
    VOS_UINT16                                  usRsv;
}WPHY_TOOL_WCDMA_L1_STATUS_IND_STRU;





/*****************************************************************************
 结构名    : WPHY_TOOL_DRX_SWITCH_REQ_STRU
 结构说明  : DRX功能打开和关闭设置
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MNTN_SWITCH_CTRL_ENUM_UINT16      enDrxCtrl;
    VOS_UINT16                                  usRsv;

}WPHY_TOOL_DRX_SWITCH_REQ_STRU;



/*****************************************************************************
 结构名    : WPHY_TOOL_THRESHOLD_SET_REQ_STRU
 结构说明  : 门限设置
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MNTN_THRESHOLD_TYPE_ENUM_UINT32   enThresholdType;
    VOS_INT32                                   lValue;

}WPHY_TOOL_THRESHOLD_SET_REQ_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_THRESHOLD_QUERY_REQ_STRU
 结构说明  : 查询
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MNTN_THRESHOLD_TYPE_ENUM_UINT32   enThresholdType;

}WPHY_TOOL_THRESHOLD_QUERY_REQ_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_THRESHOLD_QUERY_CNF_STRU
 结构说明  : 查询
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usSfn;
    VOS_UINT16                                  usCfn;
    WPHY_TOOL_MNTN_THRESHOLD_TYPE_ENUM_UINT32   enThresholdType;
    VOS_INT32                                   lValue;

}WPHY_TOOL_THRESHOLD_QUERY_IND_STRU;



/*****************************************************************************
 结构名    : WPHY_TOOL_ERROR_REPORT_REQ_STRU
 结构说明  : 错误上报
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MNTN_ERROR_RPT_LEVEL_ENUM_UINT16  enErrorRptLevel;                /* 控制上报错误级别 */
    VOS_UINT16                                  usRsv;
}WPHY_TOOL_ERROR_REPORT_REQ_STRU;




/*****************************************************************************
 结构名    : WPHY_TOOL_ERROR_REPORT_IND_STRU
 结构说明  : 错误上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usFileNo;                       /* 文件名编码 */
    VOS_UINT16                                  usLineNo;                       /* 出错的行号 */
    VOS_UINT32                                  ulTimeSlice;
    VOS_UINT32                                  ulLogId;                        /* PHY软件内统一编号LOG ID */
    VOS_UINT16                                  usReserved;                     /* 保留字段 */
    VOS_UINT16                                  usVarCnt;                       /* 上报变量个数 */
    VOS_UINT32                                  aulVarValue[WPHY_TOOL_MNTN_ERROR_RPT_VAR_NUM]; /* 上报变量值 */

}WPHY_TOOL_ERROR_REPORT_IND_STRU;




/*****************************************************************************
 结构名    : WPHY_TOOL_RF_FRONT_END_PARA_REQ_STRU
 结构说明  : RF前端参数上报
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */

    WPHY_MNTN_REPORT_TYPE_STRU                  stReportType;                   /* 默认每帧上报  */

}WPHY_TOOL_RF_FRONT_END_PARA_REQ_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_RF_FRONT_END_PARA_IND_STRU
 结构说明  : 上报TX Temp Comp,Freq Comp,AFC,LNA,HDET
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usSfn;
    VOS_UINT16                                  usCfn;
    VOS_INT16                                   sPaHighTempComp;                /* PA高增益时温度补偿 */
    VOS_INT16                                   sPaMidTempComp;                 /* PA中增益时温度补偿 */
    VOS_INT16                                   sPaLowTempComp;                 /* PA低增益时温度补偿 */

    VOS_INT16                                   sPaHighFreqComp;                /* PA高增益时频率补偿 */
    VOS_INT16                                   sPaMidFreqComp;                 /* PA中增益时频率补偿 */
    VOS_INT16                                   sPaLowFreqComp;                 /* PA低增益时频率补偿 */

    VOS_UINT16                                  usAfcStatus;                    /* AFC值 */
    VOS_UINT16                                  usAnt1AgcStatus;                /* 天线1的AGC增益状态 */
    VOS_UINT16                                  usAnt2AgcStatus;                /* 天线2的AGC增益状态 */
    VOS_UINT16                                  usHdet;                         /* HDET值 */
    VOS_UINT16                                  usPaStatus;                     /* PA状态:上报的是PA的模式控制字 */
    VOS_UINT16                                  usDbbAtten;                     /* DBB衰减 */
    VOS_UINT16                                  usRfAtten;                      /* RF衰减 */
    VOS_UINT16                                  usReserved;

}WPHY_TOOL_RF_FRONT_END_PARA_IND_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_PI_INT_RESULT_IND_STRU
 结构说明  : WPHY的PI中断结果上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_INT16                                   sPiResult;
    VOS_UINT16                                  usPiSoftValue;
    UPHY_TOOL_WPHY_DRX_MNTN_INFO_STRU           stWphyDrxMntn;                  /* DRX可维可测信息 */
}WPHY_TOOL_PI_INT_RESULT_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_AI_INT_RESULT_IND_STRU
 结构说明  : WPHY的AI中断结果上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_INT16                                   sAiResult;                      /* AI结果,+1；-1；0 */
    VOS_UINT16                                  usReTranNum;                    /* 重传次数 */
    VOS_INT16                                   sInitPower;                     /* 初始功率,单位 0.1dBm */
    VOS_INT16                                   sCurrentPower;                  /* 当前功率,单位 0.1dBm */
    VOS_UINT32                                  uwMaxTxPower;                   /* 最大发射功率,单位0.1dBm */
}WPHY_TOOL_AI_INT_RESULT_IND_STRU;

/*****************************************************************************
 结构名    : T313 Timer Status
 结构说明  : T313定时器状态上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MNTN_T313_STATUS_ENUM_UINT16      enT313Status;                   /* T313状态*/
    VOS_UINT16                                  usRsv;
}WPHY_TOOL_T313_STATUS_IND_STRU;

/*****************************************************************************
 结构名    : T312 Timer Status
 结构说明  : T312定时器状态上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MNTN_T312_STATUS_ENUM_UINT16      enT312Status;                   /* T313状态*/
    VOS_UINT16                                  usRsv;
}WPHY_TOOL_T312_STATUS_IND_STRU;

/*****************************************************************************
 结构名    : 从模CDRX配置启动
 结构说明  :
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
}WPHY_TOOL_SLAVE_CDRX_START_IND_STRU;

/*****************************************************************************
 结构名    : 从模CDRX配置停止
 结构说明  :
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
}WPHY_TOOL_SLAVE_CDRX_STOP_IND_STRU;


/*****************************************************************************
 结构名    :WPHY_TOOL_AMP_PATH_INFO_STRU
 协议表格  :
 结构说明  :多径消息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwPathEnergy;                          /* 径能量 */
    VOS_UINT16                          uhwPathPos;                             /* 径相位 */
} WPHY_TOOL_AMP_PATH_INFO_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_WSLAVE_MEAS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : W SLAVE MEAS信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                uwUnitBitMap;                     /* CS status */
    WPHY_TOOL_AMP_PATH_INFO_STRU              stUnitFirstFingerInfo;            /* Strongest finger info */
} WPHY_TOOL_WSLAVE_MEAS_INFO_STRU;



/*****************************************************************************
 结构名    : WPHY_TOOL_ACS_STEP1_RAM_CFG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : WPHY_TOOL_ACS_STEP1_RAM_CFG_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwSlotEnergy;                          /* bit[14:0]，小区能量 */
    VOS_UINT16                          uhwSlotPhase;                           /* bit[28:16]，时隙相位 */
} WPHY_TOOL_ACS_STEP1_RAM_CFG_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_STPEAB_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : WPHY_TOOL_STPEAB_INFO_STRU信息
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16     uhwStepABSucFlag;
    VOS_UINT16                          uhwReserve;
    WPHY_TOOL_ACS_STEP1_RAM_CFG_STRU    stStep1Info;
    WPHY_TOOL_TIMING_INFO_STRU          stStepAbStartTime;
    WPHY_TOOL_TIMING_INFO_STRU          stStepAbEndTime;
} WPHY_TOOL_STPEAB_INFO_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_ACS_CELL_INFO_STRU
 协议表格  :
 结构说明  :  每个小区信息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwCellEnergy;                          /* bit[15:0] ，Step3/setpB搜索得到的小区能量 */
    VOS_UINT16                          uhwScramble;                            /* bit[24:16]，Step3/setpB搜索得到的扰码号 */
    VOS_UINT16                          uhwSlotNo;                              /* bit[35:32]，时隙号*/
    VOS_UINT16                          uhwSlotPhase;                           /* bit[60:48]，时隙相位*/
} WPHY_TOOL_ACS_CELL_INFO_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_STPE23_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : WPHY_TOOL_STPE23_INFO_STRU信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwStep23SucFlag;
    VOS_UINT16                          uhwCS3RsltNum;
    WPHY_TOOL_TIMING_INFO_STRU          stStep23StartTime;
    WPHY_TOOL_TIMING_INFO_STRU          stStep23EndTime;
    WPHY_TOOL_ACS_CELL_INFO_STRU        stCS3SucInfo[WPHY_MNTN_SLAVE_STEP23_CELL_NUM];
} WPHY_TOOL_STPE23_INFO_STRU;


/*****************************************************************************
 枚举名    : WPHY_TOOL_MNTN_SLAVE_CS_STATUS_ENUM_UINT16
 协议表格  :
 枚举说明  : 从模CS状态
ASN.1描述 :
 枚举说明  : 从模CS状态
*****************************************************************************/
enum WPHY_TOOL_MNTN_SLAVE_CS_STATUS_ENUM
{
    WPHY_MNTN_SLAVE_CS_STATUS_INVALID               = 0x0,
    WPHY_MNTN_SLAVE_CS_STATUS_STEPAB_RUNNING        = 0x1,                      /* 从模两步法运行标记 */
    WPHY_MNTN_SLAVE_CS_STEPAEB_RUNNING              = 0x2,                      /* 从模step1+Eb运行标记 */
    WPHY_MNTN_SLAVE_CS_STATUS_STEP23_RUNNING        = 0x4,                      /* 从模stepEB或者step23运行标记 */
    WPHY_MNTN_SLAVE_CS_STATUS_FINISH                = 0x8,                      /* 从模小区搜索完成标记 */
    WPHY_MNTN_SLAVE_CS_STATUS_BUTT
};
typedef VOS_UINT16 WPHY_TOOL_MNTN_SLAVE_CS_STATUS_ENUM_UINT16;

/*****************************************************************************
 结构名    : WPHY_TOOL_WSLAVE_CS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : W SLAVE CS信息
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_SLAVE_CS_STATUS_ENUM_UINT16    enCsStatus;                   /* CS status */
    VOS_UINT16                          uhwReserve;                             /* Reserve */
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16     uhwIntraStepAbEn;                       /* IntraStepAbEn */
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16     uhwIntraStep23En;                       /* IntraStep23En */
    WPHY_TOOL_STPEAB_INFO_STRU          stStepAbInfo;                           /* only save one slot info */
    WPHY_TOOL_STPE23_INFO_STRU          stStep23Info;                           /* if success, save scram code, energy etc. */
} WPHY_TOOL_WSLAVE_CS_INFO_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_AFC_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 单时钟下当前ppm，scpll配置值，温度值，AFC值
*****************************************************************************/
typedef struct
{
    VOS_INT32                           swPpmValue;                             /* ppm */
    VOS_UINT32                          uwPllFracValue;                         /* Scpll 小数部分调整值 */
    VOS_UINT32                          uwPllInterValue;                        /* Scpll 整数部分调整值 */
    VOS_UINT32                          uwAfcValue4518;                         /* AFC 4518 */
    VOS_UINT32                          uwAfcValue452C;                         /* AFC 452C */
    VOS_UINT32                          uwAfcValue4500;                         /* AFC 4500 */
    VOS_UINT32                          uwAfcValue450C;                         /* AFC 450C */
    VOS_INT16                           shwTemperatureValue;                    /* 温度 */
    VOS_UINT16                          uhwReserved;
} WPHY_TOOL_AFC_INFO_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_WSLAVE_FE_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : W SLAVE 前端信息
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_AFC_INFO_STRU             stAfcInfo;                              /* 单时钟下当前ppm，scpll配置值，温度值，AFC值 */
    VOS_UINT32                          uwFeRssi;                               /* RSSI 1414 */
    VOS_UINT32                          uwFeRssiDiv;                            /* RSSI 1418 */
    VOS_UINT32                          uwDcOffset[8];                          /* DC OFFSET */
    VOS_UINT32                          uwTcvrOnRx[4];                          /* TRANSVER ON */
    VOS_UINT32                          uwTcvrOnTx[2];                          /* TRANSVER ON */
    VOS_UINT32                          uwChnMasterModeRx[4];                   /* Channel master mode */
    VOS_UINT32                          uwChnMasterModeTx[4];                   /* Channel master mode */
    VOS_UINT32                          uwChnSlaveMode[4];                      /* Channel slave mode */
    VOS_UINT32                          uwSsiEn[2];                             /* SSI EN */
    VOS_UINT32                          uwRfPllStatus;                          /* rfic锁定或失锁状态 */
    VOS_UINT16                          uhwTasAntStatusInfo;                    /* TasAntStatus */
    VOS_UINT16                          uhwReserve;
} WPHY_TOOL_WSLAVE_FE_INFO_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_WBBP_GAP_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : W SLAVE BBP enter exit gap 信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uw3F34To3F40[4];                        /* enter exit gap, measure status */
    VOS_UINT32                          uwMaterMeasWen;                         /*  10E8 */
    VOS_UINT32                          uwMipiSsiBusy;                          /*  F80A34 */
} WPHY_TOOL_WBBP_GAP_INFO_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_WSLAVE_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : W slave mode mntn info
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_TIMING_INFO_STRU                  stWslaveTimingInfo;             /* 定时上报信息(公共携带SFN CFN SLOT SLICE信息) */
    VOS_UINT16                                  uhwCurrFreq;                    /* CurrFreq */
    VOS_UINT16                                  uhwCurrBand;                    /* CurrBand */
    WPHY_TOOL_WSLAVE_CS_INFO_STRU               stWslaveCSInfo;                 /* WslaveCSInfo */
    WPHY_TOOL_WSLAVE_MEAS_INFO_STRU             stWslaveMeasInfo;               /* WslaveMeasInfo */
    WPHY_TOOL_WSLAVE_FE_INFO_STRU               stWslaveFeInfo;                 /* 前端信息 */
    WPHY_TOOL_WBBP_GAP_INFO_STRU                stWbbpEnterExitGapInfo;         /* EnterExitGapInfo */
}WPHY_TOOL_WSLAVE_MNTN_INFO_STRU;

/*****************************************************************************
 结构名    : 从模STATUS
 结构说明  :
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16                   enMsgId;                /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                          uhwToolId;              /* tools id */
    WPHY_TOOL_MNTN_SLAVE_CURRENT_STATUS_ENUM_UINT16     enCurrentStatus;
    VOS_UINT16                                          usCurrentFreqIndex;
    VOS_UINT16                                          ausMeasStatus[WPHY_MNTN_SLAVE_REPORTFREQ_NUM];
    VOS_UINT16                                          ausCSStatus[WPHY_MNTN_SLAVE_REPORTFREQ_NUM];
    VOS_UINT16                                          usMeasCellNumb;
    VOS_UINT16                                          usMeasCellIndex;
    WPHY_TOOL_WSLAVE_MNTN_INFO_STRU                     stWslaveInfo;
}WPHY_TOOL_SLAVE_SCHEDULE_STATUS_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_PA_STATUS_REPORT_REQ_STRU
 结构说明  : PA状态上报请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */

    WPHY_MNTN_REPORT_TYPE_STRU                  stReportType;                   /* 默认每帧上报  */

}WPHY_TOOL_PA_STATUS_REPORT_REQ_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_MASTER_WAKE_LTE_IND_STRU
 结构说明  : 唤醒LTE的指示
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usSfn;                          /* 唤醒时刻的sfn */
    VOS_UINT16                                  usSlot;                         /* 唤醒时刻的slot */
    VOS_UINT32                                  ulWakeReason;                   /* 唤醒目的 */
}WPHY_TOOL_MASTER_WAKE_LTE_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_MASTER_START_LTE_MEAS_IND_STRU
 结构说明  : 启动LTE测量的指示
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usSfn;                          /* 启动时刻的sfn */
    VOS_UINT16                                  usSlot;                         /* 启动时刻的slot */
    VOS_UINT32                                  ulStartReason;                  /* 启动原因 */
    VOS_UINT32                                  ulMeasTime;                     /* 测量时间 us */
    VOS_UINT32                                  ulInt0Int1Time;                 /* int0 int1间隔 us */
    VOS_UINT32                                  ulAfcLockFlag;
    VOS_INT32                                   slAfcValue;
}WPHY_TOOL_MASTER_START_LTE_MEAS_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_MASTER_REPORT_LTE_MEAS_IND_STRU
 结构说明  : 启动LTE测量的指示
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usSfn;                          /* 上报时刻的sfn */
    VOS_UINT16                                  usSlot;                         /* 上报时刻的slot */
}WPHY_TOOL_MASTER_REPORT_LTE_MEAS_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_MASTER_STOP_LTE_MEAS_IND_STRU
 结构说明  : 强停LTE测量的指示
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16                   enMsgId;                /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                          usToolsId;              /* 保留字段 */
    WPHY_TOOL_MNTN_MASTER_STOP_LTE_REASION_ENUM_UINT16  enReason;               /* 强停原因 */
    VOS_UINT16                                          usSfn;                  /* 强停时刻的sfn */
    VOS_UINT16                                          usSlot;                 /* 强停时刻的slot */
    VOS_UINT16                                          usRsv;
}WPHY_TOOL_MASTER_STOP_LTE_MEAS_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_SET_LTE_MEAS_FLAG_IND_STRU
 结构说明  : 设置LTE测量标记的指示
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usValue;
    VOS_UINT16                                  usRsv;
}WPHY_TOOL_SET_LTE_MEAS_FLAG_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_CFG_TIME_INFO_STRU
 结构说明  : 配置的时刻
*****************************************************************************/
typedef struct
{

    VOS_UINT16                                  usSfn;                          /* 配置时刻的sfn */
    VOS_UINT16                                  usCfn;                          /* 配置时刻的cfn */
    VOS_UINT16                                  usSlot;                         /* 配置时刻的slot */
    VOS_UINT16                                  usChip;                         /* 配置时刻的chip */
}WPHY_TOOL_CFG_TIME_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_CFG_TIME_INFO_STRU
 结构说明  : 配置的时刻
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usRfCfgOpSc;                    /* RF配置的目的 */
    VOS_UINT16                                  usAntMode;                      /* RF天线模式 */
    VOS_UINT16                                  usIntraBand;                    /* 本频BAND */
    VOS_UINT16                                  usIntraFreq;                    /* 本频频点 */
    VOS_UINT16                                  usAdjFreq;                      /* 邻频频点 */
    VOS_UINT16                                  usInterBand;                    /* 异频BAND */
    VOS_UINT16                                  usInterFreq;                    /* 异频频点 */
    VOS_UINT16                                  usRxRficMode;                   /* RX RFIC模式 */
    VOS_UINT16                                  usTxRficMode;                   /* TX RFIC模式 */
    VOS_UINT16                                  usReserve;
}WPHY_TOOL_RF_CFG_INFO_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_MASTER_RF_CONFIG_IND_STRU
 结构说明  : 设置LTE测量标记的指示
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_CFG_TIME_INFO_STRU                stCfgTime;                      /* RF配置时刻 */
    WPHY_TOOL_RF_CFG_INFO_STRU                  stCfgInfo;                      /* RF配置信息 */
}WPHY_TOOL_MASTER_RF_CONFIG_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_FET_FRAME_PATTERN_INFO_STRU
 结构说明  : FET帧级开关模板信息结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              ustartFrameCfn;                     /* 模板的起始帧的CFN号 */
    VOS_UINT16                              usPatternBitMap;                    /* 帧开关模板,bit0指示起始帧的开关,1为开,0为关;
                                                                                   以此类推bitn指起始帧后第n帧,每个bit代表一帧的开关 */
} WPHY_TOOL_FET_FRAME_PATTERN_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_FET_OPEN_IND_STRU
 结构说明  : FET打开信息
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16       enMsgId;                            /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usToolsId;                          /* 保留字段 */
    VOS_UINT16                              usFetEnable;                        /* FET使能开关,开:UPHY_TRUE,关:UPHY_FALSE */
    VOS_UINT16                              usCurrDpchSf;                       /* 保存当前使用的DPCH信道 */
    VOS_UINT16                              usUlTpcAlgorithm;                   /* 保存当前使用的功控算法 */
    VOS_UINT16                              usTrchTti;                          /* 语音传输信道TTI */
    WPHY_TOOL_FET_FRAME_PATTERN_INFO_STRU   stFramePatternInfo;                 /* FET帧级开关模板信息 */
}WPHY_TOOL_FET_OPEN_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_FET_CLOSE_IND_STRU
 结构说明  : FET关闭信息
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16       enMsgId;                            /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usToolsId;                          /* 保留字段 */
    VOS_UINT16                              usFetStatus;                        /* FET使能开关,开:UPHY_TRUE,关:UPHY_FALSE */
    VOS_UINT16                              usReserved;
    VOS_UINT32                              ulFetCloseVote;                     /* FET开关投票,每个bit代表1票,为1指示投关的票,为0指示投开的票 */
    VOS_UINT32                              ulFetRxOpenVote;                    /* FET帧级下行接收开关投票,每个bit代表1票,为1指示投开的票,为0指示投关的票 */
    WPHY_TOOL_FET_FRAME_PATTERN_INFO_STRU   stFramePatternInfo;                 /* FET帧级开关模板信息 */
}WPHY_TOOL_FET_CLOSE_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_QPC_OPEN_UL_IND_STRU
 结构说明  : QPC打开上行链路的指示
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usSfn;                          /* 唤醒时刻的sfn */
    VOS_UINT16                                  usSlot;                         /* 唤醒时刻的slot */
    VOS_UINT32                                  ulOpenReason;                   /* 打开原因 */
}WPHY_TOOL_QPC_OPEN_UL_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_QPC_CLOSE_UL_IND_STRU
 结构说明  : QPC关闭上行链路的指示
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usSfn;                          /* 唤醒时刻的sfn */
    VOS_UINT16                                  usSlot;                         /* 唤醒时刻的slot */
    VOS_UINT32                                  ulCloseReason;                  /* 关闭原因 */
}WPHY_TOOL_QPC_CLOSE_UL_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_QPC_RRC_STATE_IND_STRU
 结构说明  : QPC当前RRC状态的指示
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usSfn;                          /* 唤醒时刻的sfn */
    VOS_UINT16                                  usSlot;                         /* 唤醒时刻的slot */
    VOS_UINT32                                  ulRrcState;                     /* RRC状态 */
}WPHY_TOOL_QPC_RRC_STATE_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_QPC_RB_TYPE_IND_STRU
 结构说明  : QPC当前业务类型的指示 CS/PS
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usSfn;                          /* 唤醒时刻的sfn */
    VOS_UINT16                                  usSlot;                         /* 唤醒时刻的slot */
    VOS_UINT32                                  ulRbType;                       /* RB TYPE */
}WPHY_TOOL_QPC_RB_TYPE_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_NONBLIND_ESTIMATE_STATE_IND_STRU
 结构说明  : TAS明切换评估阶段可维可测上报
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usNextState;                    /* 下一双天线状态 */
    VOS_INT16                                   sRssi;                          /* 主天线的RSSI,滤波后的结果,单位为0.125dbm */
    VOS_INT16                                   sRscp;                          /* 主天线的RSCP,滤波后的结果,单位为0.125dbm */
    VOS_UINT16                                  usAntStatus;                    /* 当前天线状态,0为主天线1为分集 */
}WPHY_TOOL_NONBLIND_ESTIMATE_STATE_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_BLIND_ESTIMATE_STATE_IND_STRU
 结构说明  : TAS盲切换评估阶段可维可测上报
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usNextState;                    /* 下一状态 */
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_INT16                                   sDeltaRscp;                     /* T1时间内信号处于中间值前后能量差 */
    VOS_INT16                                   sRscpAveCurr;                   /* 当前T1时间单个激活集小区能量,单位为0.125dbm */
    VOS_INT16                                   sRscpAvePre;                    /* 前一个T1时间单个激活集小区能量,单位为0.125dbm */
    VOS_UINT16                                  usAntStatus;                    /* 当前天线状态,0为主天线1为分集 */
}WPHY_TOOL_BLIND_ESTIMATE_STATE_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_TAS_ESTIMATE_STATE_IND_STRU
 结构说明  : TAS评估阶段可维可测上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_NONBLIND_ESTIMATE_STATE_IND_STRU  stNonBlindInfo;                 /* 明切换评估状态信息 */
    WPHY_TOOL_BLIND_ESTIMATE_STATE_IND_STRU     stBlindInfo;                    /* 盲切换评估状态信息 */
}WPHY_TOOL_TAS_ESTIMATE_STATE_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_NONBLIND_COMPARE_STATE_IND_STRU
 结构说明  : TAS明切换比较阶段可维可测上报
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usNextState;                    /* 下一双天线状态 */
    VOS_UINT16                                  usPhase;                        /* 比较阶段下一阶段 */
    VOS_INT16                                   sDeltaRscp;                     /* 主分集天线滤波后的RSCP差值,单位为0.125dbm */
    VOS_UINT16                                  usAntStatus;                    /* 当前天线状态,0为主天线1为分集 */
}WPHY_TOOL_NONBLIND_COMPARE_STATE_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_BLIND_COMPARE_STATE_IND_STRU
 结构说明  : TAS盲切换比较阶段可维可测上报
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usNextState;                    /* 下一双天线状态 */
    VOS_UINT16                                  usRsv;
    VOS_UINT16                                  usPhase;                        /* 比较阶段下一阶段 */
    VOS_INT16                                   sRscpAveCurr;                   /* 主分集天线滤波后的RSCP差值,单位为0.125dbm */
    VOS_INT16                                   sRscpAvePre;                    /* 主分集天线滤波后的RSCP差值,单位为0.125dbm */
    VOS_UINT16                                  usAntStatus;                    /* 当前天线状态,0为主天线1为分集 */
}WPHY_TOOL_BLIND_COMPARE_STATE_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_TAS_COMPARE_STATE_IND_STRU
 结构说明  : TAS比较阶段可维可测上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_NONBLIND_COMPARE_STATE_IND_STRU   stNonBlindInfo;                    /* 下一双天线状态 */
    WPHY_TOOL_BLIND_COMPARE_STATE_IND_STRU      stBlindInfo;                        /* 比较阶段下一阶段 */
}WPHY_TOOL_TAS_COMPARE_STATE_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_MAS_FROZEN_STATE_IND_STRU
 结构说明  : TAS迟滞阶段可维可测上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usAntStatus;                    /* 当前天线状态 */
    VOS_UINT16                                  usRsv;                          /* 四字节对齐 */
}WPHY_TOOL_MAS_FROZEN_STATE_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_SLAVE_W_FINISH_IND_STRU
 结构说明  : 从模W任务完成指示
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT32                                  ulRsv;
}WPHY_TOOL_SLAVE_W_FINISH_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_SLAVE_GRSSI_FINISH_IND_STRU
 结构说明  : 从模W任务完成指示
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT32                                  ulRsv;
}WPHY_TOOL_SLAVE_GRSSI_FINISH_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_SLAVE_GBSIC_FINISH_IND_STRU
 结构说明  : 从模G BSIC任务完成指示
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT32                                  ulRsv;
}WPHY_TOOL_SLAVE_GBSIC_FINISH_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_SLAVE_SCHEDULE_TIMEOUT_IND_STRU
 结构说明  : 从模调度超时指示
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usStartChip;
    VOS_UINT16                                  usStartSlot;
    VOS_UINT16                                  usEndChip;
    VOS_UINT16                                  usEndSlot;
    VOS_UINT16                                  usScheduleTime;                 /* 调度时间，单位us */
    VOS_UINT16                                  usRsv;
}WPHY_TOOL_SLAVE_SCHEDULE_TIMEOUT_IND_STRU;
/*****************************************************************************
 结构名    : WPHY_TOOL_PA_STATUS_REPORT_IND_STRU
 结构说明  : PA状态上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usSfn;
    VOS_UINT16                                  usCfn;
    WPHY_TOOL_MNTN_PA_STATUS_ENUM_UINT16        enPaStatus;
    VOS_UINT16                                  usRsv;
}WPHY_TOOL_PA_STATUS_REPORT_IND_STRU;





/*****************************************************************************
 结构名    : WPHY_TOOL_INTRA_MSG_RPT_CTRL_REQ_STRU
 结构说明  : PHY 内部消息上报控制请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usMsgRptFlag;                   /* 指示内部消息是否上报 */
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
}WPHY_TOOL_INTRA_MSG_RPT_CTRL_REQ_STRU;



/*****************************************************************************
 结构名    : WPHY_TOOL_RF_FRONT_END_STATIC_REQUIRE_REQ_STRU
 结构说明  : 静态查询前端状态请求原语
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
}WPHY_TOOL_RF_FRONT_END_STATIC_REQUIRE_REQ_STRU;




/*****************************************************************************
 结构名    : WPHY_TOOL_RF_FRONT_END_STATIC_REQUIRE_IND_STRU
 结构说明  : 静态查询前端状态回复原语
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usRfTrcvOnState;                /* RF总开关，1为打开，0为关闭 */
    VOS_UINT16                                  usRfRxOnOrOff;                  /* 04h[1:0] = 3为开 */
    VOS_UINT16                                  usRxPathselect;                 /* 04h[4:3] = 3为主分集都开，2开主集 */
    VOS_UINT16                                  usWagcSwitch;                   /* WBBP 主分集开关 */

    VOS_UINT16                                  usAbbRxConfig;                  /* 3为主分集都开，1开主集 */
    VOS_UINT16                                  usAbbTxCh01LineCtrlMode;        /* CH1:[15:8],CH0:[7:0] = 0:IDLE 1:G模 2:W模 3:LTE模 4:TDS模 5:ET模式 6:APT模式 7:CA模式 */
    VOS_UINT16                                  usAbbTxCh23LineCtrlMode;        /* CH1:[15:8],CH0:[7:0] = 0:IDLE 1:G模 2:W模 3:LTE模 4:TDS模 5:ET模式 6:APT模式 7:CA模式 */
    VOS_UINT16                                  usAbbRxCh01LineCtrlMode;        /* CH1:[15:8],CH0:[7:0] = 0:IDLE 1:G模 2:W模 3:LTE模 4:TDS模 5:ET模式 6:APT模式 7:CA模式 */
    VOS_UINT16                                  usAbbRxCh23LineCtrlMode;        /* CH1:[15:8],CH0:[7:0] = 0:IDLE 1:G模 2:W模 3:LTE模 4:TDS模 5:ET模式 6:APT模式 7:CA模式 */
    VOS_UINT16                                  usAbbRxCh01Mode;                /* CH1:[15:8],CH0:[7:0] = 0:2G 1:3G_SC 2:4G 3: 3G_DC 4:TDS */
    VOS_UINT16                                  usAbbRxCh23Mode;                /* CH1:[15:8],CH0:[7:0] = 0:2G 1:3G_SC 2:4G 3: 3G_DC 4:TDS */
    VOS_UINT16                                  usAbbCh01VoiceData;             /* CH1:[15:8],CH0:[7:0] = 1:voice mode 2: data mode */
    VOS_UINT16                                  usAbbCh23VoiceData;             /* CH1:[15:8],CH0:[7:0] = 1:voice mode 2: data mode */

    VOS_UINT16                                  usRfTxOnOrOff;                  /* 02h[1:0] = 3为开 */
    VOS_UINT16                                  usRfTxSHDN;                     /* RF上行打开控制，0由BBP控制 */
    VOS_UINT16                                  usTxPathselect;                 /* RFIC TX Patch */
    VOS_UINT16                                  usRfTxAgc;                      /* RFIC TXAGC */

    VOS_UINT16                                  usCpcDrxFuncOn;                 /* 当前工作在CPC DRX的标志 */
    VOS_UINT16                                  usCpcDrxStartCfn;               /* CPC DRX开始工作的CFN */
    VOS_UINT16                                  usCpcSleepBitMap;               /* 低16bit，1为醒来时隙，0为睡眠时隙 */

    VOS_UINT16                                  usGpioFuncOn;                   /* 硬件支持GPIO */
    VOS_UINT16                                  usGpioPaMode;                   /* GPIO PA mode */

    VOS_UINT16                                  usMipiFuncOn;                   /* 硬件支持MIPI */
    VOS_UINT16                                  usMipiPaMode;                   /* MIPI PA mode */

    VOS_UINT16                                  usAptFuncOn;                    /* 硬件支持APT */
    VOS_UINT16                                  usAptPaMode;                    /* APT电压mode */
    VOS_UINT16                                  uhwAptVcc;                          /* 保留 */
}WPHY_TOOL_RF_FRONT_END_STATIC_REQUIRE_IND_STRU;




/*****************************************************************************
 结构名    : WPHY_TOOL_RF_FRONT_END_DISPLAY_REQ_STRU
 结构说明  : 是否实时输出前端信息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MNTN_SWITCH_CTRL_ENUM_UINT16      enDisplayCtrl;
    VOS_UINT16                                  usReserved;
}WPHY_TOOL_RF_FRONT_END_DISPLAY_REQ_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_BBP_RTC_REQ_STRU
 结构说明  : RTC功能打开和关闭设置
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    UPHY_TOOL_RTC_DEBUG_ENUM_UINT16             enRtcCtrl;                      /* RTC打开或者关闭 */
    VOS_UINT16                                  usRsv;

}WPHY_TOOL_BBP_RTC_REQ_STRU;



/*****************************************************************************
 结构名    : WPHY_TOOL_RAM_REPORT_REQ_STRU
 结构说明  : WPHY抓取固定块画图的RAM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MNTN_RAM_RPT_ENUM_UINT16          enRptRam;
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptStatus;
}WPHY_TOOL_RAM_REPORT_REQ_STRU;





/*****************************************************************************
 结构名    : WPHY_TOOL_RAM_REPORT_IND_STRU
 结构说明  : WPHY抓取固定块画图的RAM
*****************************************************************************/

typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usSfn;
    VOS_UINT16                                  usCfn;
    WPHY_TOOL_MNTN_RAM_RPT_ENUM_UINT16          enRptRam;
    VOS_UINT16                                  usRsv;
    VOS_UINT32                                  aulData[2];
}WPHY_TOOL_RAM_REPORT_IND_STRU;



/*****************************************************************************
 结构名    : WPHY_TOOL_BLK_REPORT_LIST_REQ_STRU
 结构说明  : WPHY抓取非固定地址的数据
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulBlkAddr;                      /* 抓取数据块的首地址 */
    VOS_UINT32                                  ulBlkLen;                       /* 抓取数据块的长度,单位:32bit */
}WPHY_TOOL_BLK_REPORT_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;
    VOS_UINT16                                  usRsv;
    WPHY_TOOL_BLK_REPORT_STRU                   astRptBlk[WPHY_TOOL_RPT_BLK_MAX_NUM];
}WPHY_TOOL_BLK_REPORT_LIST_REQ_STRU;




/*****************************************************************************
 结构名    : WPHY_TOOL_BLK_REPORT_LIST_IND_STRU
 结构说明  : WPHY抓取非固定地址的数据
*****************************************************************************/

typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usSfn;
    VOS_UINT16                                  usCfn;
    WPHY_TOOL_BLK_REPORT_STRU                   astRptBlk[WPHY_TOOL_RPT_BLK_MAX_NUM];
    VOS_UINT32                                  aulData[2];
}WPHY_TOOL_BLK_REPORT_LIST_IND_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_RA_MNTN_CTRL_REQ_STRU
 结构说明  : 随机接入可维可测上报设置消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MNTN_SWITCH_CTRL_ENUM_UINT16      enRaMntnCtrl;                   /* 随机接入可维可测打开或关闭 */
    VOS_UINT16                                  usReserve;                      /* 保留字段 */
}WPHY_TOOL_RA_MNTN_CTRL_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_ARM_0MS_MNTN_CTRL_REQ_STRU
 结构说明  : ARM 0MS可维可测上报设置消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MNTN_SWITCH_CTRL_ENUM_UINT16      enArm0msMntnCtrl;               /* ARM 0MS打开或关闭 */
    VOS_UINT16                                  usReserve;                      /* 保留字段 */
}WPHY_TOOL_ARM_0MS_MNTN_CTRL_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_UPA_SUBFRAME_RPT_INFO_STRU
 结构说明  : UPA子帧可维可测信息上报结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  auhwRptValue[WPHY_MNTN_HSUPA_RPT_VALUE_MAX_NUM][WPHY_MNTN_HSUPA_OM_CARERIER_NUM];
}WPHY_TOOL_UPA_SUBFRAME_RPT_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_UPA_RPT_INFO_STRU
 结构说明  : UPA可维可测信息上报结构体
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_UPA_SUBFRAME_RPT_INFO_STRU        astRptValue[WPHY_MNTN_HSUPA_SUB_FRM_NUM];
}WPHY_TOOL_UPA_RPT_INFO_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_GSM_CELL_SNR_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 该命令用于请求上报服务小区和邻区的信噪比,测量值等信息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT16                              uhwMsgId;                           /* _H2ASN_Skip */    /* 原语ID */
    VOS_UINT16                              uhwToolId;                              /* 保留字段 */
    VOS_UINT16                              uhwCommand;                             /* 命令。0:停止，1：启动 */
    VOS_UINT16                              uhwResvered;                            /* 保留字段 */
}GPHY_TOOL_GSM_CELL_SNR_REQ_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_GSM_CELL_SNR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 每个小区的信噪比,测量值等信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwFreqInfo;                            /* 频点信息上报，高12bit表示频段，0:850,1:900,2:1800,3:1900，低12bit表示频点号，0-1023。*/
    VOS_INT16                           shwRxLev;                               /* 信号强度值，[-110,-15],单位为dbm */
    VOS_UINT16                          uhwCellSnr;                             /* 信噪比，[0,99],单位为db */
    VOS_UINT16                          uhwResvered;                            /* 保留字段 */
}GPHY_TOOL_GSM_CELL_SNR_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_GSM_CELL_SNR_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 用于上报服务小区和邻区的信噪比,测量值等信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* 原语ID */
    VOS_UINT16                          uhwToolId;                              /* 保留字段 */
    VOS_UINT16                          uhwCellNum;                             /* 频点数 */
    GPHY_TOOL_GSM_CELL_SNR_STRU         astCellInfo[GPHY_TOOL_MA_FREQ_NUM];       /* 小区信息 */
    VOS_UINT16                          uhwResvered;                            /* 保留字段 */
}GPHY_TOOL_GSM_CELL_SNR_IND_STRU;


/*****************************************************************************
 结构名    : GPHY_TOOL_BA_LIST_MEAS_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 请求上报BA LIST的信号强度，bsic信息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* 原语ID */
    VOS_UINT16                          uhwToolId;                              /* 保留字段 */
    VOS_UINT16                          uhwCommand;                             /* 命令。0:停止，1：启动 */
    VOS_UINT16                          uhwResvered;                            /* 保留字段 */
}GPHY_TOOL_BA_LIST_MEAS_REQ_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_CELL_MEAS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 每个小区的信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwFreqInfo;                            /* 频点信息上报，高12bit表示频段，0:850,1:900,2:1800,3:1900，低12bit表示频点号，0-1023。*/
    VOS_INT16                           shwRxLev;                               /* 信号强度值，[-110,-15],单位为dbm */
    VOS_UINT16                          uhwBsic;                                /* 基站标识码，0-77，无效0xffff */
    VOS_UINT16                          uhwResvered;                            /* 保留字段 */
}GPHY_TOOL_CELL_MEAS_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_BA_LIST_MEAS_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上报BA LIST的信号强度，bsic信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* 原语ID */
    VOS_UINT16                          uhwToolId;                              /* 保留字段 */
    VOS_UINT16                          uhwScellFreqInfo;                       /* 频点信息上报，高12bit表示频段，0:850,1:900,2:1800,3:1900，低12bit表示频点号，0-1023。*/
    VOS_INT16                           shwScellRxLev;                          /* 信号强度值，[-110,-15],单位为dbm */
    VOS_UINT16                          uhwHoppingInd;                          /* 跳频指示,1:表示跳频,0表示不跳频 */
    VOS_UINT16                          uhwResvered1;                           /* 保留字段 */
    VOS_UINT16                          uhwCellNum;                             /* 邻区的个数 */
    VOS_UINT16                          uhwResvered2;                           /* 保留字段 */
    GPHY_TOOL_CELL_MEAS_STRU            astNeighbourCell[GPHY_TOOL_BA_LIST_MAX_NUM]; /* 邻区的测量信息 */
}GPHY_TOOL_BA_LIST_MEAS_IND_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_AMR_SETTING_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 请求上报AMR配置信息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* 原语ID */
    VOS_UINT16                          uhwToolId;                              /* 保留字段 */
    VOS_UINT16                          uhwCommand;                             /* 命令。0:停止，1：启动 */
    VOS_UINT16                          uhwResvered;                            /* 保留字段 */
}GPHY_TOOL_AMR_SETTING_REQ_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_AMR_SETTING_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上报AMR配置信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* 原语ID */
    VOS_UINT16                          uhwToolId;                              /* 保留字段 */
    VOS_UINT16                          uhwAcsNum;                              /* 激活集个数,范围为0-4 */
    VOS_UINT16                          uhwResvered;                            /* 保留字段 */
    VOS_UINT16                          auhwAcs[GPHY_TOOL_AMR_MAX_ACS_NUM];       /* 激活集集合，范围0-7 */
    VOS_UINT16                          auhwHyst[GPHY_TOOL_AMR_MAX_ACS_NUM-1];    /* 切换迟滞大小，范围0-15，单位为0.5db */
    VOS_UINT16                          auhwThd[GPHY_TOOL_AMR_MAX_ACS_NUM-1];     /* 切换门限大小，范围为0-63，单位为0.5db */
}GPHY_TOOL_AMR_SETTING_IND_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_AMR_CODEC_USAGE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 请求上报激活集中每个语音速率的使用率
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* 原语ID */
    VOS_UINT16                          uhwToolId;                              /* 保留字段 */
    VOS_UINT16                          uhwCommand;                             /* 命令。0:停止，1：启动 */
    VOS_UINT16                          uhwResvered;                            /* 保留字段 */
}GPHY_TOOL_AMR_CODEC_USAGE_REQ_STRU;


/*****************************************************************************
 结构名    : GPHY_TOOL_AMR_CODEC_USAGE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上报激活集中每个语音速率的使用率
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* 原语ID */
    VOS_UINT16                          uhwToolId;                              /* 保留字段 */
    VOS_UINT16                          uhwAcsNum;                              /* 激活集个数,范围为0-4 */
    VOS_UINT16                          uhwResvered;                            /* 保留字段 */
    VOS_UINT16                          auhwAcs[GPHY_TOOL_AMR_MAX_ACS_NUM];       /* 激活集集合，范围0-7 */
    VOS_UINT32                          auwUplink[GPHY_TOOL_AMR_MAX_ACS_NUM];     /* 上行链路激活集的每个速率的块数，范围0-2^32-1，单位为块 */
    VOS_UINT32                          auwDownlink[GPHY_TOOL_AMR_MAX_ACS_NUM];   /* 下行链路激活集的每个速率的块数，范围0-2^32-1，单位为块 */
}GPHY_TOOL_AMR_CODEC_USAGE_IND_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_AMR_CODEC_STAT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 请求各个编码速率的使用率
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* 原语ID */
    VOS_UINT16                          uhwToolId;                              /* 保留字段 */
    VOS_UINT16                          uhwCommand;                             /* 命令。0:停止，1：启动 */
    VOS_UINT16                          uhwResvered;                            /* 保留字段 */
}GPHY_TOOL_AMR_CODEC_STAT_REQ_STRU;

/*****************************************************************************
 结构名    : GPHY_AMR_CODEC_AVG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 每个编码速率的使用率
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          auhwUplink[GPHY_TOOL_AMR_CODEC_MAX_NUM];  /* 上行链路激活集的每个速率的块数，范围0-2^32-1，单位为块 */
    VOS_UINT32                          auhwDownlink[GPHY_TOOL_AMR_CODEC_MAX_NUM];/* 下行链路激活集的每个速率的块数，范围0-2^32-1，单位为块 */
}GPHY_AMR_CODEC_AVG_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_AMR_CODEC_STAT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 小区，呼叫的统计信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* 原语ID */
    VOS_UINT16                          uhwToolId;                              /* 保留字段 */
    GPHY_AMR_CODEC_AVG_STRU             stCell;                                 /* 小区的统计信息 */
    GPHY_AMR_CODEC_AVG_STRU             stCall;                                 /* 每个呼叫的统计信息 */
}GPHY_TOOL_AMR_CODEC_STAT_IND_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_CS_PS_TX_INFO_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 请求上报CS/PS域上行信息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* 原语ID */
    VOS_UINT16                          uhwToolId;                              /* 保留字段 */
    VOS_UINT16                          uhwCommand;                             /* 命令。0:停止，1：启动 */
    VOS_UINT16                          uhwResvered;                            /* 保留字段 */
}GPHY_TOOL_CS_PS_TX_INFO_REQ_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_CS_PS_TX_INFO_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上报CS/PS域上行信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* 原语ID */
    VOS_UINT16                          uhwToolId;                              /* 保留字段 */
    VOS_UINT16                          uhwTa;                                  /* 时间提前量，范围为0-63，单位为符号 */
    VOS_UINT16                          uhwSlotNumber;                          /* 时隙个数 */
    VOS_UINT16                          uhwTxPower[4];                          /* 上行发射功率，范围为0-99，单位为dbm */
    VOS_UINT16                          uhwPcl;                                 /* 基站指定的功率等级，范围为0-31 */
    VOS_UINT16                          uhwResvered;
}GPHY_TOOL_CS_PS_TX_INFO_IND_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_CS_FER_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 请求上报CS FER信息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* 原语ID */
    VOS_UINT16                          uhwToolId;                              /* 保留字段 */
    VOS_UINT16                          uhwCommand;                             /* 命令。0:停止，1：启动 */
    VOS_UINT16                          uhwResvered;                            /* 保留字段 */
}GPHY_TOOL_CS_FER_REQ_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_CS_FER_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上报CS FER信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* 原语ID */
    VOS_UINT16                          uhwToolId;                              /* 保留字段 */
    VOS_UINT32                          uwErrorFrameFull;                       /* full块的错误帧数 */
    VOS_UINT32                          uwTotalFrameFull;                       /* full总帧数 */
    VOS_UINT32                          uwErrorFrameSub;                        /* sub块的错误帧数 */
    VOS_UINT32                          uwTotalFrameSub;                        /* sub总帧数 */
}GPHY_TOOL_CS_FER_IND_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_CS_GET_CURRENT_DSC_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 请求上报下行链路计数值
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* 原语ID */
    VOS_UINT16                          uhwToolId;                              /* 保留字段 */
    VOS_UINT16                          uhwCommand;                             /* 命令。0:停止，1：启动 */
    VOS_UINT16                          uhwResvered;                            /* 保留字段 */
}GPHY_TOOL_GET_CURRENT_DSC_REQ_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_GET_CURRENT_DSC_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上报下行链路计数值
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip *//* 原语ID */
    VOS_UINT16                          uhwToolId;                              /* 保留字段 */
    VOS_UINT16                          uhwDsc;                                 /* 下行链路计数值 */
    VOS_UINT16                          uhwResvered;
}GPHY_TOOL_GET_CURRENT_DSC_IND_STRU;


/*****************************************************************************
 结构名    : GPHY_TOOL_DUAL_ANT_ESTIMATE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 主天线能量评估阶段判决结果上报
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgID;                               /* _H2ASN_Skip */ /* 原语ID */
    VOS_UINT16                          uhwToolId;                                  /* tools id */
    VOS_UINT16                          uhwDualAntCurId;                        /* 天线id */
    VOS_UINT16                          uhwDualAntNextState;                    /* 下一个跳转阶段 */
    VOS_UINT16                          uhwRxlevAvgSub;                         /* 主天线平均每个统计周期SUB块的能量值 */
    VOS_UINT16                          uhwReserved;                                /* reserved  */
}GPHY_TOOL_DUAL_ANT_ESTIMATE_IND_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_DUAL_ANT_COMPARE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 当前和目标天线能量比较阶段判决结果上报，每个调度状态上报一次
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      uhwMsgID;                                   /* _H2ASN_Skip */ /* 原语ID */
    VOS_UINT16                      uhwToolId;                                  /* tools id */
    VOS_UINT16                      uhwRoundNum;                                /* round计数 */
    VOS_UINT16                      uhwCompareFinishFlag;                       /* 双天线比较是否结束，包括Ia Ib II IIa  */
    VOS_UINT16                      uhwDualAntCurState;                         /* 当前的调度状态 */
    VOS_UINT16                      uhwDualAntNextState;                        /* 下一个调度状态 */
    VOS_UINT16                      uhwAntChangeFlag;                           /* 当前state是否切天线标志 */
    VOS_UINT16                      uhwDualAntCurId;                            /* 切换前的天线id */
    VOS_UINT16                      uhwDualAntSecId;                            /* 当前比较的的天线id */
    VOS_UINT16                      uhwDualAntNextId;                           /* 切换后的天线id */
    VOS_INT16                       shwRxlevFilterPriAnt;                       /* 当前天线平均每个统计周期的能量滤波值 */
    VOS_INT16                       shwRxlevFilterSecAnt;                       /* 目标天线平均每个统计周期的能量滤波值 */
    VOS_INT16                       shwDeltaRxlev;                              /* 目标天线与当前天线平均每个统计周期的能量滤波差值 */
    VOS_UINT16                      uhwGoodEnoughFlag;                          /* 本次上报周期是否有足够好天线 */
}GPHY_TOOL_DUAL_ANT_COMPARE_IND_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_DUAL_ANT_COMPARE_SUB_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 当前和目标天线能量比较阶段判决结果上报，改为二阶并行算法后每个上报周期都上报一次
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      uhwMsgID;                                   /* _H2ASN_Skip */ /* 原语ID */
    VOS_UINT16                      uhwToolId;                                  /* tools id */
    VOS_UINT16                      uhwCountTotal;                              /* 上报周期计数 */
    VOS_UINT16                      uhwCountHigh;                               /* delta值大于高门限的上报周期计数  */
    VOS_UINT16                      uhwCountLow;                                /* delta值小于低门限的上报周期计数 */
    VOS_UINT16                      uhwDualAntCurId;                            /* 当前天线id */
    VOS_UINT16                      uhwDualAntSecId;                            /* 目标天线id */
    VOS_INT16                       shwRxlevFilterPriAnt;                       /* 当前天线平均每个统计周期的能量滤波值 */
    VOS_INT16                       shwRxlevFilterSecAnt;                       /* 目标天线平均每个统计周期的能量滤波值 */
    VOS_INT16                       shwDeltaRxlev;                              /* 目标天线与当前天线平均每个统计周期的能量滤波差值 */
}GPHY_TOOL_DUAL_ANT_COMPARE_SUB_IND_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_MAS_CHANGE_ANT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAS切天线消息上报
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  uhwMsgID;                       /* _H2ASN_Skip */ /* 原语ID */
    VOS_UINT16                                  uhwToolId;                      /* tools id */
    VOS_UINT16                                  uhwMasDpdtStatus;               /* 切换后MAS dpdt的状态 */
    VOS_UINT16                                  uhwMasChangeAntType;            /* 切换类型: Probe or Switch */
}GPHY_TOOL_MAS_CHANGE_ANT_IND_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_DUAL_ANT_DELAY_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 天线切换停滞阶段判决结果上报
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      uhwMsgID;                                   /* _H2ASN_Skip */ /* 原语ID */
    VOS_UINT16                      uhwToolId;                                  /* tools id */
    VOS_UINT16                      uhwDualAntCurId;                            /* 天线id */
    VOS_UINT16                      uhwDualAntNextState;                        /* 下一个跳转阶段 */
    VOS_UINT16                      uhwHandAntEn;                               /* 停滞阶段启动或结束标志 */
    VOS_UINT16                      uhwReserved;                                /* reserved  */
}GPHY_TOOL_DUAL_ANT_DELAY_IND_STRU;


/*****************************************************************************
 结构名    : GPHY_TOOL_DUAL_ANT_ESTIMATE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 主天线能量评估阶段判决结果上报
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgID;                               /* _H2ASN_Skip */ /* 原语ID */
    VOS_UINT16                          uhwToolID;                              /* TOOL ID，保留 */
    VOS_UINT16                          uhwSarDprEn;                            /* DPR状态 */
    VOS_UINT16                          uhwRsv;                                 /* 保留 */
}GPHY_TOOL_TIME_AVG_SAR_DPR_STATE_IND_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_DUAL_ANT_ESTIMATE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 主天线能量评估阶段判决结果上报
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgID;                               /* _H2ASN_Skip */ /* 原语ID */
    VOS_UINT16                          uhwToolID;                              /* TOOL ID，保留 */
    VOS_INT16                           ashuwGmskSarLimitedMaxPwr[GPHY_PS_MAX_TX_TSN_NUM];           /* GMSK的时间平均SAR最大限制功率，0.1 dBm */
    VOS_INT16                           ashuw8pskSarLimitedMaxPwr[GPHY_PS_MAX_TX_TSN_NUM];           /* 8PSK的时间平均SAR最大限制功率，0.1 dBm */
    VOS_UINT16                          uhwDprState;                            /* DPR状态 ON/OFF */
    VOS_UINT16                          uhwCurPeirodAvgPwrIndex;                /* 当前统计周期索引值,满400会清零 */
    VOS_INT32                           swCurPeirodAvgPwr;                      /* 当前统计周期的平均功率辐射量，0.125 dBm */
    VOS_INT32                           swTimeAvgSarAdjudgeSum;                 /* 当前判决周期平均功率总和,单位0.125dbm */
    VOS_INT32                           swAveragePower;                         /* 判决周期的平均功率辐射量，0.125 dBm */
    VOS_INT32                           swCurPeirodAvgPwrLine;                  /* 当前统计周期的平均功率线性值 */
    VOS_INT32                           swAdjudgeSumLine;                       /* 当前判决周期平均功率线性值总和 */
    VOS_INT32                           swAveragePowerLine;                     /* 判决周期的平均功率线性值 */
    VOS_UINT32                          uwCurSlice;                             /* 当前的slice */

}GPHY_TOOL_TIME_AVG_SAR_PERIOD_IND_STRU;



/*****************************************************************************
 DC维护类型枚举
*****************************************************************************/
enum UPHY_TOOL_DCOFFSET_ENUM
{
    UPHY_TOOL_DCOFFSET_UPDATE_INIT      = 0,
    UPHY_TOOL_DCOFFSET_UPDATE_REMAIN    = 1,

    UPHY_TOOL_DCOFFSET_UPDATE_BUTT
};
typedef VOS_UINT16 UPHY_TOOL_DCOFFSET_ENUM_UINT16;


/*****************************************************************************
 结构名    : UCOM_NV_GSM_DC_OFFSET_REPORT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GSM DC Offset Report
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgID;                                   /* _H2ASN_Skip */ /* 原语ID */
    VOS_UINT16                          uhwToolId;                                  /* tools id */
    VOS_UINT16                          uhwReserved;                                /* reserved  */
    UPHY_TOOL_DCOFFSET_ENUM_UINT16      enUpdateType;
    VOS_UINT16                          uhwFreqInfo;
    VOS_UINT16                          uhwGain;
    VOS_INT16                           shwRemainI;
    VOS_INT16                           shwRemainQ;

    VOS_INT16                           shwInitDcoci;                           /* 初始值,RFIC控制值为0x80对应的I路DC值 */
    VOS_INT16                           shwInitDcocq;                           /* 初始值,RFIC控制值为0x80对应的Q路DC值 */
    VOS_INT16                           shwRfDci;                               /* 校准后,RFIC I路DC控制值 */
    VOS_INT16                           shwRfDcq;                               /* 校准后,RFIC Q路DC控制值 */
    VOS_INT16                           shwRemainDcoci;                         /* 校准后,I路残余DC值 */
    VOS_INT16                           shwRemainDcocq;                         /* 校准后,Q路残余DC值 */
}GPHY_TOOL_DC_OFFSET_REPORT_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_SINGLE_XO_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 单时钟下当前ppm，scpll配置值，温度值，AFC值
*****************************************************************************/
typedef struct
{
    VOS_INT32                           swPpmValue;                             /* ppm */
    VOS_UINT32                          uwPllFracValue;                         /* Scpll 小数部分调整值 */
    VOS_UINT32                          uwPllInterValue;                        /* Scpll 整数部分调整值 */
    VOS_UINT32                          uwAfcValue;                             /* AFC */
    VOS_INT16                           shwTemperatureValue;                    /* 温度 */
    VOS_UINT16                          uhwReserved;
} WPHY_TOOL_SINGLE_XO_INFO_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_RSSI_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 前端RSSI信息
*****************************************************************************/
typedef struct
{

    VOS_UINT32                          uwAnt1Rssi;                               /* RSSI 1414 */
    VOS_UINT32                          uwAnt2Rssi;                               /* RSSI 1414 */
} WPHY_TOOL_RSSI_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_FE_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 前端信息
*****************************************************************************/
typedef struct
{

    /* SSI_EN开关/RSSI/AGC档位/DCOFFSET/AFC/BLOCK、NOBLOCK状态天线开关/ABB线控/TRCV_ON状态/单双天线状态  */
    WPHY_TOOL_SINGLE_XO_INFO_STRU       stSingleXoInfo;                         /* 单时钟下当前ppm，scpll配置值，温度值，AFC值 */
    WPHY_TOOL_RSSI_STRU                 stFeRssi;                               /* RSSI 1414 */
    VOS_UINT32                          uwWagcSwitch;                           /* WAGC_SWITCH 1400 */
    VOS_UINT32                          uwIntrasysValid;                        /* BBPCOMM_W_INTRASYS_VALID_ADDR */
    VOS_UINT32                          uwIntMaskLteRcvW;                       /* BBPCOMM_INT_MASK_LTE_RCV_W_ADDR */
    VOS_UINT32                          uwRfPllStatus;                          /* rfic锁定或失锁状态 */
    VOS_UINT32                          uwTcvrOnRx[4];                          /* TRANSVER ON */
    VOS_UINT32                          uwTcvrOnTx[2];                          /* TRANSVER ON */
    VOS_UINT32                          uwChnMasterModeRx[4];                   /* Channel master mode */
    VOS_UINT32                          uwChnMasterModeTx[4];                   /* Channel master mode */
    VOS_UINT32                          uwChnSlaveMode[4];                      /* Channel slave mode */
} WPHY_TOOL_FE_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_LOWPOWER_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 低功耗相关信息
*****************************************************************************/
typedef struct
{
    /* RF/PA/BBP/ABB上下电状态，不睡原因  */
    VOS_UINT16                          uhwGuBbpTopMemOffFlg;                   /* GuBbp MEM是否下电判断 */
    VOS_UINT16                          uhwGuBbpTopMemStatus;                   /* 存储当前的上电状态 */
    VOS_UINT32                          uwGuBbpLPPurposeBitmap;                 /* TOP1B2B上下电操作目的,是因为TURBO还是DPA */
    VOS_UINT16                          uhwBbpMasterOffFlg;                     /* BBP MASTER是否下电判断 */
    VOS_UINT16                          uhwBbpMasterStatus;                     /* 存储当前BBP MASTER的上电状态 */
    VOS_INT16                           shwAnt2CtrlFlag;                        /* 分集开关 */
    VOS_UINT16                          uhwReserved;
} WPHY_TOOL_LOWPOWER_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_MULTIPUTH_UNIT1_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 多径搜索单元1相关信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwEn;                                   /* 单元1使能信息 0xFD902020 */
    VOS_UINT32                          uwMode;                                 /* 单元1模式 0xFD902024 */
    VOS_UINT32                          uwScram;                                /* 扰码 0xFD902028 */
    VOS_UINT32                          uwCpichSync;                            /* 帧头信息 0xFD90202C */
    VOS_UINT32                          uwWinOffset;                            /* 窗位置 0xFD902030 */
} WPHY_TOOL_MULTIPUTH_UNIT1_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_FINGER_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 多径搜索结果信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwFingerEnergy;                           /* 径能量 */
    VOS_UINT32                          uwFingerPos;                              /* 径相位 */
} WPHY_TOOL_FINGER_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_FINGER_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 单元0 1 2的 F0最强径信息
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_FINGER_INFO_STRU          astAnt1FingerInfo[WPHY_MNTN_MP_WIN_MAX_NUM];
    WPHY_TOOL_FINGER_INFO_STRU          stAnt2FingerInfo;
} WPHY_TOOL_MP_FINGER_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_TWO_ANT_MP_FINGER_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 双天线 单元0 1 2的 F0最强径信息
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_FINGER_INFO_STRU          astAnt1FingerInfo[WPHY_MNTN_MP_WIN_MAX_NUM];
    WPHY_TOOL_FINGER_INFO_STRU          astAnt2FingerInfo[WPHY_MNTN_MP_WIN_MAX_NUM];
} WPHY_TOOL_TWO_ANT_MP_FINGER_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_DEMOD_FINGER_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 解调径相关信息
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_FINGER_INFO_STRU          astDemodFingerInfo[WPHY_MNTN_DEMOD_FINGER_MAX_NUM];
    VOS_UINT32                          uwFingerEn;
    VOS_UINT32                          uwFingerAntInd;
} WPHY_TOOL_DEMOD_FINGER_INFO_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_PRI_WIN_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 主小区窗头尾信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwPriWinTop;                            /* 窗头信息 0xFD9040C0 */
    VOS_UINT32                          uwPriWinEnd;                            /* 窗尾信息 0xFD9040C4 */
} WPHY_TOOL_PRI_WIN_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_SOFT_WIN_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 软窗头尾信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwSoftWinTop;                           /* 软窗头信息 0xFD9040C8 */
    VOS_UINT32                          uwSoftWinEnd;                           /* 软窗尾信息 0xFD9040CC */
} WPHY_TOOL_SOFT_WIN_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_RL_SCRAM_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 链路扰码初相
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwRlScram[WPHY_MNTN_RL_SCRAM_MAX_NUM];
    VOS_UINT16                          uhwReserved;
} WPHY_TOOL_RL_SCRAM_INFO_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_MEASURE_CTRL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 测量调度状态
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwIntraMeasureStatus;                  /*本频测量状态*/
    VOS_UINT16                          uhwInterMeasureStatus;                  /*异频测量状态  */
    VOS_UINT16                          uhwInterRATMeasureStatus;               /*异系统测量状态*/
    VOS_UINT16                          uhwInterRATBSICStatus;                  /*异系统BSIC验证状态*/
    #if FEATURE_LTE                                                             /* _H2ASN_Skip */
    VOS_UINT16                          uhwInterRATLteMeasureStatus;            /*异系统LTE测量状态*/
    #endif /* FEATURE_LTE */                                                    /* _H2ASN_Skip */
    VOS_UINT16                          uhwReserved;
}WPHY_TOOL_MEASURE_CTRL_INFO_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_CS_CTRL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 小区搜索调度状态
*****************************************************************************/
typedef struct
{

        VOS_UINT16                                      uhwIntraStatusFlg;
        VOS_UINT16                                      uhwInterStatusFlg;
        VOS_UINT16                                      uhwIntraStep23TypeFlg;  /* 0:step23   1:stepEb */
        VOS_UINT16                                      uhwStepBEnState;
        VOS_UINT16                                      uhwStepBScramType;      /* 0:软件配置扰码 1: 无扰码 */
        VOS_UINT16                                      uhwStep23EnState;
        VOS_UINT16                                      uhwIntraStepABEn;
        VOS_UINT16                                      uhwInterStepABEn;
        VOS_UINT16                                      uhwStep1EnState;
        VOS_UINT16                                      uhwInitCsEn;
}WPHY_TOOL_CS_CTRL_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_SYS_TIME_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 系统定时信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwSysTime;                              /* 系统定时 */
    VOS_UINT32                          uwCpichPathPos;                         /* 跟踪小区CPICH最早径在绝对时标上的位置 */
    VOS_UINT32                          uwDpchPathPos;                          /* 跟踪小区SCCPCH/DPCH最早径在绝对时标上的位置 */
}WPHY_TOOL_SYS_TIME_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_ERROR_CODE_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 误码信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwErrorBlocks;                          /* 错块数  */
    VOS_UINT32                          uwTotalBlocks;                          /* 总块数 */
}WPHY_TOOL_ERROR_CODE_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_R99_BLER_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : R99下行信道误码统计
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_ERROR_CODE_INFO_STRU      astBlerInfo[WPHY_MNTN_BLER_RPT_MAX_NUM];
}WPHY_TOOL_R99_BLER_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_DPA_ERROR_CODE_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DPA译码误码统计
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_ERROR_CODE_INFO_STRU      astErrorCode[WPHY_MNTN_DPA_ERROR_CODE_RPT_MAX_NUM];
}WPHY_TOOL_DPA_ERROR_CODE_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_DPA_EQ_FINGER_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DPA 均衡解调径信息
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_FINGER_INFO_STRU          astEqFingerInfo[WPHY_MNTN_EQ_FINGER_RPT_MAX_NUM];
}WPHY_TOOL_DPA_EQ_FINGER_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_RA_STATUS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 随机接入状态信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwAccessStatus;
    VOS_UINT16                          uhwAccessProcess;                       /*随机接入上报状态*/
}WPHY_TOOL_RA_STATUS_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_PI_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PI可维可测信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwSfn;                                 /* PI SFN值 */
    VOS_UINT16                          uhwSlot;                                /* PI SLOT值 */
    VOS_UINT16                          uhwChip;                                /* PI CHIP值 */
    VOS_UINT16                          uhwPiAckNum;                            /* 解到PI为ACK的个数 */
    VOS_UINT16                          uhwPiTotalNum;                          /* 解到PI总个数 */
    VOS_UINT16                          uhwReserved;
} WPHY_TOOL_PI_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_TX_POW_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上行发射功率信息
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwTxAvrgPwr;
    VOS_INT16                           shwTxMaxPwr;
    VOS_INT16                           shwTxMinPwr;
    VOS_INT16                           shwFilterDpcchPwr;
    VOS_INT16                           shwAllowUlMaxPower;
    VOS_UINT16                          uhwReserved;
}WPHY_TOOL_TX_POW_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_TPC_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 当前帧TPC统计值
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwDlTpcS0To7;
    VOS_UINT32                          uwDlTpcS8To15;
    VOS_UINT32                          uwUlTpc;
}WPHY_TOOL_TPC_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_GAIN_FACTOR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 各信道功率因子
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwBc;
    VOS_UINT16                          uhwBd;
    VOS_UINT16                          uhwBhs;
    VOS_UINT16                          uhwReserved;
}WPHY_TOOL_GAIN_FACTOR_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_CM_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 压模信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwDlGapPara;
    VOS_UINT32                          uwUlGapPara;
}WPHY_TOOL_CM_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_TIME_MEA_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 时间测量信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwSfncfnMeasFlag;
    VOS_INT16                           shwScramCodeNum;
}WPHY_TOOL_TIME_MEA_INFO_STRU;


/*****************************************************************************
 结构名    : WPHY_FET_CTRL_INFO_STRU
 结构说明  : FET特性控制全局信息结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usFetStatus;                        /* FET使能开关,开:UPHY_TRUE,关:UPHY_FALSE */
    VOS_UINT16                              usStartProtectCnt;                  /* 启动保护计数,单位帧 */
    VOS_UINT32                              ulFetCloseVote;                     /* FET开关投票,每个bit代表1票,为1指示投关的票,为0指示投开的票 */
    VOS_UINT32                              ulFetRxOpenVote;                    /* FET帧级下行接收开关投票,每个bit代表1票,为1指示投开的票,为0指示投关的票 */
    VOS_UINT32                              ulDecodeInfo;                       /* FET提前译码信息上报 */
    WPHY_TOOL_FET_FRAME_PATTERN_INFO_STRU   stFramePatternInfo;                 /* FET帧级开关模板信息 */
} WPHY_FET_CTRL_INFO_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_COMM_BUSINESS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : WPHY各状态公共可维可测信息上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_TIMING_INFO_STRU          stTimingInfo;                           /* 定时上报信息(公共携带SFN CFN SLOT SLICE信息) */
    VOS_UINT16                          uhwCurrentFreq;                         /* 当前主小区频点 */
    VOS_UINT16                          uhwSysSramcode;                         /* 当前主小区扰码 */
    WPHY_TOOL_RL_SCRAM_INFO_STRU        stRlScramInfo;                          /* 链路0、6扰码初相 */
    WPHY_TOOL_DEMOD_FINGER_INFO_STRU    stDemodFingerInfo;                      /* 所有有效解调径能量径位置 */
    WPHY_TOOL_MULTIPUTH_UNIT1_INFO_STRU stUnit1Info;                            /* 多径搜索单元1相关信息 */
    WPHY_TOOL_MP_FINGER_INFO_STRU       stMpFingerInfo;                         /* 单元0,1,2 f0多径能量及相位，通过多径中断获取，不另外读 */
    WPHY_TOOL_PRI_WIN_INFO_STRU         stPriWinInfo;                           /* 主小区窗头尾 */
    WPHY_TOOL_MEASURE_CTRL_INFO_STRU    stMeasureCtrlInfo;                      /* 测量任务调度状态 */
    WPHY_TOOL_CS_CTRL_INFO_STRU         stCsCtrlInfo;                           /* 小区搜索调度状态 */
    WPHY_TOOL_R99_BLER_INFO_STRU        stR99BlerInfo;                          /* 下行信道误码统计 */
    VOS_UINT32                          uwDemEn;                                /* 0-15bit为解调信道使能，16bit为传输信道使能 */
    VOS_UINT16                          uhwDsdsResourceFlag;                    /* bit0:当前帧slot0的资源情况
                                                                                   bit3:上一帧slot3的资源情况
                                                                                   bit6:上一帧slot6的资源情况
                                                                                   bit9:上一帧slot9的资源情况
                                                                                   bit12:上一帧slot12的资源情况
                                                                                   */
    VOS_UINT16                          uhwDsdsOpenFlag;
}WPHY_TOOL_COMM_BUSINESS_INFO_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_IDLE_MNTN_RPT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IDLE态可维可测信息上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16   enMsgId;                                /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                          usToolsId;                              /* 保留字段 */
    WPHY_TOOL_FE_INFO_STRU              stFeInfo;                               /* 前端信息 */
    WPHY_TOOL_COMM_BUSINESS_INFO_STRU   stCommBusinessInfo;                     /* 公共业务信息 */
}WPHY_TOOL_FREE_MNTN_RPT_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_IDLE_MNTN_RPT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IDLE态可维可测信息上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16   enMsgId;                                /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                          usToolsId;                              /* 保留字段 */

    WPHY_TOOL_FE_INFO_STRU              stFeInfo;                               /* 前端信息 */
    WPHY_TOOL_COMM_BUSINESS_INFO_STRU   stCommBusinessInfo;                     /* 公共业务信息 */
    WPHY_TOOL_LOWPOWER_INFO_STRU        stLowPowerInfo;                         /* 低功耗相关 */
    WPHY_TOOL_PI_INFO_STRU              stPiInfo;
}WPHY_TOOL_IDLE_MNTN_RPT_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_FACH_MNTN_RPT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : FACH态可维可测信息上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16   enMsgId;                                /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                          usToolsId;                              /* 保留字段 */

    WPHY_TOOL_FE_INFO_STRU              stFeInfo;                               /* 前端信息 */
    WPHY_TOOL_COMM_BUSINESS_INFO_STRU   stCommBusinessInfo;                     /* 公共业务信息 */
    WPHY_TOOL_RA_STATUS_INFO_STRU       stRaStatus;
    WPHY_TOOL_SYS_TIME_INFO_STRU        stSysTimeInfo;                          /* 系统定时，最早径信息 */
    VOS_UINT32                          uwMaxAndMinTxPow;                       /* 最大最小功率值 0xFD90C0A4*/
    VOS_UINT32                          uwDpchSccpchDataPow;                    /* DPCH/SCCPCH信道子域能量值 */
    VOS_UINT32                          uwPaStatus;                             /* PA上下电状态 */
}WPHY_TOOL_FACH_MNTN_RPT_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_DCH_MNTN_RPT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DCH态可维可测信息上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16       enMsgId;                            /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usToolsId;                          /* 保留字段 */

    WPHY_TOOL_FE_INFO_STRU                  stFeInfo;                           /* 前端信息 */
    WPHY_TOOL_COMM_BUSINESS_INFO_STRU       stCommBusinessInfo;                 /* 公共业务信息 */
    WPHY_TOOL_SOFT_WIN_INFO_STRU            stSoftWinInfo;
    WPHY_TOOL_TX_POW_INFO_STRU              stTxPow;                            /* 上行发射功率 */
    WPHY_TOOL_TPC_INFO_STRU                 stTpcInfo;                          /* 当前帧TPC统计值 */
    WPHY_TOOL_DPA_ERROR_CODE_INFO_STRU      stDpaErrorCode;                     /* DPA译码误码统计 */
    WPHY_TOOL_DPA_EQ_FINGER_INFO_STRU       stDpaEqFinger;                      /* 均衡解调径信息 */
    WPHY_TOOL_GAIN_FACTOR_STRU              stGainFactor;                       /* 各信道功率因子 */
    WPHY_TOOL_SYS_TIME_INFO_STRU            stSysTimeInfo;                      /* 系统定时，最早径信息 */
    WPHY_TOOL_CM_INFO_STRU                  stCmInfo;                           /* 压模情况 */
    WPHY_TOOL_TIME_MEA_INFO_STRU            stTimeMeaInfo;                      /* 时间测量情况 */
    VOS_UINT32                              uwDmodeSyncInd;                     /* 当前帧解调同失步状态 */
    VOS_UINT32                              uwFrameSyncInd;                     /* 当前帧同失步状态 */
    VOS_INT16                               shwSirTarget;                       /* 外环功控值 */
    VOS_UINT16                              uhwOlpcCtrlMode;                    /* 外环功控控制模式BLER或者BER */
    VOS_UINT32                              uwDpchSccpchDataPow;                /* DPCH/SCCPCH信道子域能量值 */
    VOS_UINT32                              uwBerError;                         /* BER误码统计 */
    VOS_UINT32                              uwMaxAndMinTxPow;                   /* 最大最小功率值 0xFD90C0A4*/
    VOS_UINT32                              uwPcUlChanEn;                       /* bit由低到高分别表示上行E-DCH、DCH、RACH、HSUPA、功控使能信息 */
    VOS_UINT32                              uwPaStatus;                         /* PA上下电状态 */
    VOS_UINT32                              uwPdDetectRslt;                     /* 实际发射功率-理论发射功率，单位0.1dBm。 */
    WPHY_FET_CTRL_INFO_STRU                 stFetCtrlInfo;                      /* FET信息 */
}WPHY_TOOL_DCH_MNTN_RPT_STRU;

/*****************************************************************************
 结构名    : UPHY_TOOL_TAS_STATUS_REPORT_REQ_STRU
 结构说明  : TAS_STATUS report功能打开和关闭设置
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT32                                  uwTasCtrl0;                     /* 控制字 */
    VOS_UINT32                                  uwTasCtrl1;
    VOS_UINT32                                  uwTasCtrl2;
    VOS_UINT32                                  uwTasCtrl3;
}UPHY_TOOL_TAS_STATUS_REPORT_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_TAS_STATUS_REPORT_IND_STRU
 结构说明  : TAS_STATUS report 上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  uhwToolId;                      /* 保留字段 */
    VOS_UINT16                                  uhwBand;                        /* 当前频段  */
    VOS_UINT16                                  uhwAthorizeStatus;              /* TASMAS授权状态 */
    VOS_UINT16                                  uhwDpdtStateSteady;             /* 稳态天线位置 */
    VOS_UINT16                                  uhwDpdtStateTemp;               /* 暂态天线位置 */
    VOS_INT16                                   ashwAntRscp[4];                 /* 天线0到3信号强度  */

}WPHY_TOOL_TAS_STATUS_REPORT_IND_STRU;


/*****************************************************************************
 结构名    : GPHY_TOOL_TAS_STATUS_REPORT_IND_STRU
 结构说明  : TAS_STATUS report 上报
*****************************************************************************/
typedef struct
{
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  uhwCurrentBand;                 /* 当前切换频段 */
    VOS_UINT16                                  uhwAuthorizeFlag;               /* 最新TAS授权状态 TAS=0,MAS=0/TAS=1,MAS=0/TAS=0,MAS=1/TAS=1,MAS=1 */
    VOS_UINT16                                  uhwWholeSwitchDpdtStatus;       /* 整轮切换后DPDT状态 */
    VOS_UINT16                                  uhwSingleSwitchDpdtStatus;      /* 单次切换后DPDT状态 */
    VOS_INT16                                   shwAntRssi[4];                  /* 天线0到3信号强度  */
}GPHY_TOOL_TAS_STATUS_REPORT_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_RAKE_PCCPCH_SCHL_INFO_STRU
 结构说明  : 配置的时刻
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  uhwCurrentQueueType;             /* 当前任务是否为广播类任务,1:任务队列选择广播队列;0:任务队列选择A解调队列 */
    VOS_UINT16                                  uhwCurrentTaskFreqIndex;         /* 当前任务所属载波 */
    VOS_UINT16                                  uhwQueueIndex;                   /* 当前任务对应任务队列的索引*/
    VOS_UINT16                                  uhwBand;                        /* 频段 */
    VOS_UINT16                                  uhwFreq;                        /* 频点 */
    VOS_UINT16                                  uhwScramCode;                   /* 扰码 */
    VOS_UINT16                                  uhwTDIndicator;                  /* 广播任务的分集类型 */
    VOS_UINT16                                  uhwPccpchTaskType;               /* 广播任务类型 */
    VOS_UINT16                                  uhwPccpchTaskStatus;             /* 广播任务状态 */
    VOS_UINT16                                  uhwSchdlPriority;                /* 调度优先级 */
}WPHY_TOOL_RAKE_PCCPCH_SCHDL_INFO_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_RAKE_PCCPCH_SCHDL_INFO_STRU
 结构说明  : 设置LTE测量标记的指示
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_CFG_TIME_INFO_STRU                stCfgTime;                      /* Pcpch配置时刻 */
    WPHY_TOOL_RAKE_PCCPCH_SCHDL_INFO_STRU        stCfgInfo;                      /* Pcccpch配置信息 */
}WPHY_TOOL_RAKE_PCCPCH_SCHDL_IND_STRU;



/*****************************************************************************
 结构名    : WPHY_TOOL_RAKE_BCCH_QUEUE_INFO_STRU
 结构说明  : 配置的时刻
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                   uhwBand;                       /* 频段 */
    VOS_UINT16                                   uhwFreq;                       /* 频点 */
    VOS_UINT16                                   uhwScramCode;                  /* 扰码 */
    VOS_UINT16                                   uhwTDIndicator;                 /* 广播任务的分集类型 */
    VOS_UINT16                                   uhwPccpchTaskType;              /* 广播任务类型 */
    VOS_UINT16                                   uhwPccpchTaskStatus;            /* 广播任务状态 */
    VOS_UINT16                                   uhwSchdlPriority;               /* 调度优先级 */
    VOS_UINT16                                   uhwRsv;
}WPHY_TOOL_RAKE_BCCH_QUEUE_INFO_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_RAKE_BCCH_QUEUE_IND_STRU
 结构说明  : BCH广播队列信息
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_CFG_TIME_INFO_STRU                stCfgTime;                      /* Pcpch配置时刻 */
    WPHY_TOOL_RAKE_BCCH_QUEUE_INFO_STRU         astQueueInfo[WPHY_MNTN_BCCH_QUEUE_LENGTH];                      /* BCCH队列信息 */
}WPHY_TOOL_RAKE_BCCH_QUEUE_IND_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_RAKE_ADEMOD_QUEUE_INFO_STRU
 结构说明  : 配置的时刻
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                   uhwBand;                       /* 频段 */
    VOS_UINT16                                   uhwFreq;                       /* 频点 */
    VOS_UINT16                                   uhwScramCode;                  /* 扰码 */
    VOS_UINT16                                   uhwTDIndicator;                /* 广播任务的分集类型 */
    VOS_UINT16                                   uhwPccpchTaskType;             /* 广播任务类型 */
    VOS_UINT16                                   uhwPccpchTaskStatus;           /* 广播任务状态 */
    VOS_UINT16                                   uhwSchdlPriority;              /* 调度优先级 */
    VOS_UINT16                                   uhwRsv;
}WPHY_TOOL_RAKE_ADEMOD_QUEUE_INFO_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_RAKE_ADEMOD_QUEUE_IND_STRU
 结构说明  : ADEMOD队列信息
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_CFG_TIME_INFO_STRU                stCfgTime;                      /* ADEMOD配置时刻 */
    WPHY_TOOL_RAKE_ADEMOD_QUEUE_INFO_STRU       astQueueInfo[WPHY_MNTN_ADMOD_QUEUE_LENGTH];                      /* BCCH队列信息 */
}WPHY_TOOL_RAKE_ADEMOD_QUEUE_IND_STRU;
/*****************************************************************************
  7 UNION定义
*****************************************************************************/
/*****************************************************************************
 联合体名   : WPHY_TOOL_MNTN_RPT_UNION
 协议表格   :
 ASN.1描述  :
 联合体说明 : WPHY可维可测信息上报
*****************************************************************************/
typedef union
{
    WPHY_TOOL_FREE_MNTN_RPT_STRU        stFreeMntnRpt;                          /* FREE态可维可测信息上报 */
    WPHY_TOOL_IDLE_MNTN_RPT_STRU        stIdleMntnRpt;                          /* IDLE态可维可测信息上报 */
    WPHY_TOOL_FACH_MNTN_RPT_STRU        stFachMntnRpt;                          /* FACH态可维可测信息上报 */
    WPHY_TOOL_DCH_MNTN_RPT_STRU         stDchMntnRpt;                           /* DCH态可维可测信息上报 */
}WPHY_TOOL_MNTN_RPT_UNION;

/*****************************************************************************
 结构名    : WPHY_TOOL_SAR_TIME_AVG_DPR_EVENT_IND_STRU
 结构说明  : SAR DPR ON事件可维可测上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16             enSarDprEn;                    /* DPR状态 */
    VOS_UINT16                                  uhwRsv;                         /* 保留 */
}WPHY_TOOL_SAR_TIME_AVG_DPR_EVENT_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_SAR_TIME_AVG_PARA_INFO_STRU
 结构说明  :时间平均 SAR参数可维可测上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16             enTimeAvgSarLimitPowerFlag;     /* 时间平均SAR限制功率标记 */
    VOS_INT16                                   shwTimeAvgSarMaxTxPowerLimit;   /* 时间平均SAR限制功率标记有效时最大限制功率,单位0.1dbm */
    VOS_INT16                                   shwTimeAvgSarStaticPrdPwrAvg;   /* 当前统计周期内的平均功率,单位0.125dbm */
    VOS_INT16                                   shwTimeAvgSarAdjudgePrdPwrAvg;  /* 当前判决周期内的平均功率,单位0.125dbm */
    VOS_INT32                                   swTimeAvgSarAdjudgeSum;         /* 当前判决周期平均功率总和,单位0.125dbm */
    VOS_UINT16                                  uhwTimeAvgSarStaticPrdIndex;    /* 当前统计周期个数满400会清零 */
    VOS_UINT16                                  uhwReserved;
    VOS_UINT32                                  uwStaticPrdPwrLineAvg;          /* 当前统计周期内的平均功率线性值 */
    VOS_UINT32                                  uwAdjudgePrdPwrLineAvg;         /* 当前判决周期内的平均功率线性值 */
    VOS_UINT32                                  uwAdjudgeLineSum;               /* 当前判决周期平均功率总和线性值 */

}WPHY_TOOL_SAR_TIME_AVG_PARA_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_CPC_DRX_PATTERN_INFO_STRU
 结构说明  : 合并后的均衡模板
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwStartCfn;
    VOS_UINT16                          auhwPattBitMap[WPHY_MNTN_CPC_DRX_PATTERN_FRAME_NUM];        /* 从低到高共15位有效，每个BIT表示对应时隙的操作是打开(值为1)还是关闭(值为0) */

}WPHY_TOOL_CPC_DRX_PATTERN_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_CPC_DRX_CQI_STATIC_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HS-DPCCH信道CQI上报DRX控制静态参数信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwNpre[WPHY_MNTN_HSUPA_OM_CARERIER_NUM];          /* 提前判断的子帧数 */

} WPHY_TOOL_CPC_DRX_CQI_STATIC_INFO_STRU;

/*****************************************************************************
 结构名    : PHYITF_DTX_E_DCH_TTI_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : edch dtx参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  usUeDtxCyc1;                                  /*  Units of subframes*/
    VOS_UINT16                  usUeDtxCyc2;                                  /*  Units of subframes*/
    VOS_UINT16                  usMacDtxCyc;                                  /*  Units of subframes*/
    VOS_UINT16                  usReserved;
} WPHY_TOOL_DTX_E_DCH_TTI_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_CPC_DRX_HSSCCH_DRX_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HS-SCCH和HS_PDSCH信道接收控制信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      uhwHsscchSchedSlot;                 /* HS-SCCH和HS_PDSCH信道接收评估时隙 */
    VOS_UINT16                                      uhwHsscchEquaRfSlotNum;             /* 均衡打开和RF打开的持续时间，以时隙为单位*/
    VOS_UINT16                                      uhwHsscchInactiveEquaRfSlotCnt;     /* 译码数据有效时，用于Inactivity_Threshold_for_UE_DRX_cycle的计数器*/
    VOS_UINT16                                      uhwHsscchInactiveEquaRfSlotNum;     /* 译码数据有效时，用于Inactivity_Threshold_for_UE_DRX_cycle的门限*/
} WPHY_TOOL_CPC_DRX_HSSCCH_DRX_CTRL_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_CPC_DRX_HSDPCCH_ACK_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HS-SCCH和HS_PDSCH信道ACK发送控制信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwPost;                                /* 发送ACK时,可能需要发送POST*/
    VOS_UINT16                          uhwRfSlotNum;                           /* HSPDSCH查询到译码时，到ACK发送之间，RF打开的持续时间，以时隙为单位 */
} WPHY_TOOL_CPC_DRX_HSDPCCH_ACK_CTRL_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_CPC_DRX_CQI_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HS-DPCCH信道CQI上报DRX控制信息
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16                 enCqiSchedFlag;                     /* TRUE:需要CQI DRX控制调度,否则不需要 */
    WPHY_TOOL_MNTN_CPC_DRX_CQI_PRI_ENUM_UINT16      enCqiDtxPri;                        /* 综合考虑BBP和软件维护得出的CQI优先级 */
    WPHY_TOOL_CPC_DRX_CQI_STATIC_INFO_STRU          stCqiStaticNpreInfo;                /* HS-DPCCH信道CQI上报DRX控制静态参数信息提前判断的子帧数 */
    WPHY_TOOL_CPC_DRX_PATTERN_INFO_STRU             astCqiEquaPattInfo[WPHY_MNTN_CPC_DRX_CQI_PATTERN_NUM];           /* CQI DRX调度控制的均衡PATTERN信息 */
    WPHY_TOOL_CPC_DRX_PATTERN_INFO_STRU             astCqiRfPattern[WPHY_MNTN_CPC_DRX_CQI_PATTERN_NUM];         /* RF PATTERN */
} WPHY_TOOL_CPC_DRX_CQI_CTRL_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_CPC_DRX_EQUA_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CPC DRX info
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_CPC_DRX_EQUA_STATUS_ENUM_UINT16  enCpcEquaWorkState;                 /* 当前均衡工作状态 */
    VOS_UINT16                                      uhwReserve;
    WPHY_TOOL_CPC_DRX_PATTERN_INFO_STRU             stCpcEquaCombPatt;                  /* 合并后的均衡模板 */
    WPHY_TOOL_CPC_DRX_PATTERN_INFO_STRU             astCpcEquaPattInfo[WPHY_MNTN_CPC_DRX_EQUA_CTRL_TYPE_NUM];       /* 均衡PATTERN信息 */
} WPHY_TOOL_CPC_DRX_EQUA_CTRL_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_CPC_DRX_RF_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CPC DRX info
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_CPC_DRX_RF_STATUS_ENUM_UINT16    enRfWorkState;                /* 当前RF工作状态 */
    VOS_UINT16                                      uhwReserve;
    VOS_UINT32                                      uwPhySubTaskStaBitMap;              /* 影响RF的子任务状态bitmap */
    WPHY_TOOL_CPC_DRX_PATTERN_INFO_STRU             astRfPattInfo[WPHY_MNTN_CPC_DRX_RF_CTRL_TYPE_NUM];                     /* RF PATTERN信息 */
    WPHY_TOOL_CPC_DRX_PATTERN_INFO_STRU             stCombRfPatt;                 /* 合并后的RF模板 */
} WPHY_TOOL_CPC_DRX_RF_CTRL_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_DCH_MNTN_RPT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DCH态可维可测信息上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                            /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                      usToolsId;                          /* 保留字段 */
    WPHY_TOOL_MNTN_CPC_ULDPCCH_CYCLE_STATE_ENUM_UINT16  enUlDpcchPattCycleState;        /* 综合主辅载波的状态后的出的cycle状态的最大集合 */
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16                 enAgchRgchSchedFlag;                /* 是否进行AGCH/RGCH调度标志, TRUE:要, FALSE:不要 */
    WPHY_TOOL_CPC_DRX_EQUA_CTRL_STRU                stEquaCtrl;                         /* 均衡模板 */
    WPHY_TOOL_CPC_DRX_CQI_CTRL_STRU                 stCqiDrxCtrl;                       /* CQI DRX调度控制 */
    WPHY_TOOL_CPC_DRX_RF_CTRL_STRU                  stRfCtrl;                           /* RF模板 */
    WPHY_TOOL_DTX_E_DCH_TTI_STRU                    stDtxEdchTti;                       /* edch dtx参数 */
    WPHY_TOOL_CPC_DRX_PATTERN_INFO_STRU             stUlDpcchC1RfPatt;                  /* UL Dpcch cycle1 RF PATTERN */
    WPHY_TOOL_CPC_DRX_PATTERN_INFO_STRU             stUlDpcchC2RfPatt;                  /* UL Dpcch cycle2 RF PATTERN */
    WPHY_TOOL_CPC_DRX_HSSCCH_DRX_CTRL_STRU          stHsscchDrxCtrl;                    /* HsscchDrx控制结构*/
    WPHY_TOOL_CPC_DRX_HSDPCCH_ACK_CTRL_STRU         stHsdpcchAckCtrl;                   /* HsscchAck控制结构*/
    WPHY_TOOL_CPC_DRX_PATTERN_INFO_STRU             astDrxEdchCtrlRfPatt[WPHY_MNTN_HSUPA_OM_CARERIER_NUM];  /* EDCH发送 一个载波上的 RF PATTERN，主辅载波的pattern分别刷新 */

}WPHY_TOOL_CPC_MNTN_RPT_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_IC_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 小区信息上报
*****************************************************************************/
typedef struct
{
    VOS_INT16                                       shwScramCodeNum;            /* 扰码 */
    VOS_INT16                                       shwFreqInfo;                /* 频点 */
}WPHY_TOOL_IC_CELL_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_IC_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 各个载波下IC小区信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      uhwCellNum;                                     /* 小区数量 */
    VOS_UINT16                                      uhwReserved;                                    /* 保留位 */
    WPHY_TOOL_IC_CELL_INFO_STRU                     astIcCellInfo[WPHY_MNTN_IC_MAX_CELL_NUM];       /* 原语类型 */
}WPHY_TOOL_IC_CELL_LIST_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_IC_CELL_REPORT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IC小区信息上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                    /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                      usToolsId;                  /* 保留字段 */
    WPHY_TOOL_IC_CELL_LIST_STRU                     astIcCellList[WPHY_MNTN_MAX_CARRIER_NUM];    /* 原语类型 */
}WPHY_TOOL_IC_CELL_REPORT_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_IC_CELL_REPORT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 各个载波下IC小区信息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;
    VOS_UINT16                                  usRptPeriod;
}WPHY_TOOL_IC_CELL_REPORT_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_UL_DTX_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DTX信息上报
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      uhwUlDtxStatus;             /* 原语类型,0--disable 1--enable */
    VOS_UINT16                                      uhwMainCarrierEnable;       /* 原语类型,0--disable 1--enable */
    VOS_UINT16                                      uhwSecondCarrierEnable;     /* 原语类型,0--disable 1--enable */
    VOS_UINT16                                      uhwMainCarrierActive;       /* 原语类型,0--Inactive 1--active */
    VOS_UINT16                                      uhwSecondCarrierActive;     /* 原语类型,0--Inactive 1--active */
    VOS_UINT16                                      uhwMainCarrierOrder;        /* 原语类型,0--Inactive 1--active */
    VOS_UINT16                                      uhwSecondCarrierOrder;      /* 原语类型,0--Inactive 1--active */
    VOS_UINT16                                      uhwMainCarrierPattern;      /* 原语类型 */
    VOS_UINT16                                      uhwSecondCarrierPattern;    /* 原语类型 */
    VOS_UINT16                                      uhwCQIDtxPriority;          /* 原语类型,0--low 1--high */
    VOS_UINT16                                      uhwMainCarrierMacDtx;       /* 原语类型,0--continue 1--MAC DTX */
    VOS_UINT16                                      uhwSecondCarrierMacDtx;     /* 原语类型,0--continue 1--MAC DTX */
}WPHY_TOOL_UL_DTX_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_DL_DRX_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DRX信息上报
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      uhwDrxActiveStatus;         /* 原语类型,0--Inactive 1--active */
    VOS_UINT16                                      uhwReserved;                /* 保留为 */
}WPHY_TOOL_DL_DRX_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_CPC_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CPC信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      uhwEnableStatus;            /* 原语类型,0--disable 1--enable */
    VOS_UINT16                                      uhwActiveStatus;            /* 原语类型,0--Inactive 1--active */
    VOS_UINT16                                      uhwMainCarrierOrder;        /* 原语类型,0--Inactive 1--active */
    VOS_UINT16                                      uhwSecondCarrierOrder;      /* 原语类型,0--Inactive 1--active */
}WPHY_TOOL_CPC_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_RTT_STATUS_REPORT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RTT状态上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                    /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                      usToolsId;                  /* 保留字段 */
    WPHY_TOOL_UL_DTX_INFO_STRU                      stUlDtxInfo;                /* 原语类型 */
    WPHY_TOOL_DL_DRX_INFO_STRU                      stDlDRxInfo;                /* 原语类型 */
    WPHY_TOOL_CPC_INFO_STRU                         stHsScchLessInfo;           /* 原语类型 */
}WPHY_TOOL_RTT_STATUS_REPORT_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_RTT_STATUS_REPORT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 各个载波下IC小区信息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;
    VOS_UINT16                                  usRptPeriod;
}WPHY_TOOL_RTT_STATUS_REPORT_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_DPA_INFO_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DPA信息
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                    /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                      usToolsId;                  /* 保留字段 */
    VOS_UINT16                                      uhwEnableStatus;            /* 原语类型,0--disable 1--enable */
    VOS_UINT16                                      uhwActiveStatus;            /* 原语类型,0--Inactive 1--active */
    VOS_UINT16                                      uhwMainCarrierOrder;        /* 原语类型,0--Inactive 1--active */
    VOS_UINT16                                      uhwSecondCarrierOrder;      /* 原语类型,0--Inactive 1--active */
}WPHY_TOOL_DPA_INFO_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_DPA_INFO_REPORT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DPA 上报请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;
    VOS_UINT16                                  uhwRptPeriod;
}WPHY_TOOL_DPA_INFO_REPORT_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_P_VALUE_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : P值信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      auwPValueTotalCnt[WPHY_MNTN_P_VALUE_NUM];   /* 原语类型,0--disable 1--enable */
}WPHY_TOOL_P_VALUE_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSSCCH_DECODE_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HS-SCCH译码信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      uwSubFrameNum;              /* 原语类型,0--disable 1--enable */
    VOS_UINT32                                      uwHsScchAttempt;            /* 原语类型,0--Inactive 1--active */
    VOS_UINT32                                      uwHsScchSucc;               /* 原语类型,0--Inactive 1--active */
    VOS_UINT32                                      uwHsScchSuccRate;           /* 原语类型,0--Inactive 1--active */
    WPHY_TOOL_P_VALUE_INFO_STRU                     stPValueInfo;
}WPHY_TOOL_HSSCCH_DECODE_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSSCCH_STATISTIC_REPORT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HS-SCCH译码信息上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                      usToolsId;                      /* 保留字段 */
    WPHY_TOOL_HSSCCH_DECODE_INFO_STRU               astHsScchDecodeInfo[WPHY_MNTN_MAX_CARRIER_NUM];    /* 原语类型 */
}WPHY_TOOL_HSSCCH_STATISTIC_REPORT_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSSCCH_STATISTIC_REPORT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSSCCH译码上报请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;
    VOS_UINT16                                  uhwRptPeriod;
}WPHY_TOOL_HSSCCH_STATISTIC_REPORT_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSDSCH_TBS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HS-DSCH译码信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      uwQpskNum;                  /* 原语类型,0--disable 1--enable */
    VOS_UINT32                                      uw16QamNum;                 /* 原语类型,0--disable 1--enable */
    VOS_UINT32                                      uw64QamNum;                 /* 原语类型,0--Inactive 1--active */
    VOS_UINT32                                      uwSupport64QamFlag;         /* 原语类型,0--Inactive 1--active */
    VOS_UINT32                                      uwSBSub;                    /* 原语类型,0--Inactive 1--active */
    VOS_UINT32                                      uwSBPlus;                   /* 原语类型,0--Inactive 1--active */
    VOS_UINT32                                      uwFirstSuccNum;             /* 原语类型,0--Inactive 1--active */
    VOS_UINT32                                      uwSecondSuccNum;            /* 原语类型,0--Inactive 1--active */
    VOS_UINT32                                      uwThirdSuccNum;             /* 原语类型,0--Inactive 1--active */
    VOS_UINT32                                      uwFourthSuccNum;            /* 原语类型,0--Inactive 1--active */
    VOS_UINT32                                      uwFifthSuccNum;             /* 原语类型,0--Inactive 1--active */
    VOS_UINT32                                      uwSixthSuccNum;             /* 原语类型,0--Inactive 1--active */
}WPHY_TOOL_HSDSCH_TBS_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSDSCH_TBS_THREHOLD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HS-DSCH译码信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      uhwTbsLowThredhold;         /* 原语类型,0--disable 1--enable */
    VOS_UINT16                                      uhwTbsHighThredhold;        /* 原语类型,0--disable 1--enable */
}WPHY_TOOL_HSDSCH_TBS_THREHOLD_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSDSCH_DECODE_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HS-DSCH译码信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      uhwRegionNum;                                   /* 原语类型,0--disable 1--enable */
    VOS_UINT16                                      uhwReserved;                                    /* 原语类型,0--disable 1--enable */
    WPHY_TOOL_HSDSCH_TBS_THREHOLD_STRU              astTbsThredholdInfo[WPHY_MNTN_MAX_REGION_NUM];  /* 原语类型,0--Inactive 1--active */
    WPHY_TOOL_HSDSCH_TBS_INFO_STRU                  astTbsInfo[WPHY_MNTN_MAX_REGION_NUM];           /* 原语类型,0--Inactive 1--active */
}WPHY_TOOL_HSDSCH_DECODE_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSDSCH_STATISTIC_REPORT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSDSCH译码上报请求
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                      usToolsId;                                      /* 保留字段 */
    WPHY_TOOL_HSDSCH_DECODE_INFO_STRU               astHsDschDecodeInfo[WPHY_MNTN_MAX_CARRIER_NUM]; /* 原语类型 */
}WPHY_TOOL_HSDSCH_STATISTIC_REPORT_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSDSCH_STATISTIC_REPORT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSDSCH译码上报请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;
    VOS_UINT16                                  uhwRptPeriod;
    VOS_UINT16                                  uhwReserved;
    VOS_UINT16                                  uhwRegionNum;                    /* 配置为0-9，必须与ausThredhold中的数目匹配 */
    VOS_UINT16                                  auhwThredhold[WPHY_MNTN_MAX_REGION_NUM];
}WPHY_TOOL_HSDSCH_STATISTIC_REPORT_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_PILOT_BER_REPORT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PILOT BER上报请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  uhwToolsId;                     /* 保留字段 */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;                      /* 上报允许标志 */
    VOS_UINT16                                  uhwRptPeriod;                   /* 上报周期 */
}WPHY_TOOL_PILOT_BER_REPORT_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_PILOT_BER_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PILOT 16帧滑窗总比特和误比特信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      uhwPilotTotalBitNum;        /* Pilot总比特数，16帧滑窗 */
    VOS_UINT16                                      uhwPilotErrorBitNum;        /* Pilot误比特数，16帧滑窗 */
}WPHY_TOOL_PILOT_BER_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_PILOT_BER_RPT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PILOT BER上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                    /* _H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                      uhwToolsId;                 /* 保留字段 */
    WPHY_TOOL_PILOT_BER_INFO_STRU                   stPilotBerInfo;             /* 误码率 *//* 原语类型 */
}WPHY_TOOL_PILOT_BER_REPORT_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_TPC_AND_SIR_REPORT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 传输功控和信噪比上报请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  uhwToolsId;                     /* 保留字段 */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;                      /* 上报允许标志 */
    VOS_UINT16                                  uhwRptPeriod;                   /* 上报周期 */
}WPHY_TOOL_TPC_AND_SIR_REPORT_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_TPC_AND_SIR_REPORT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 传输功控和误码率上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                    /* _H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                      uhwToolsId;                 /* 保留字段 */
    VOS_INT16                                       shwDlTpcCnt;                /* 传输功控 */ /* 原语类型 */
}WPHY_TOOL_TPC_AND_SIR_REPORT_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_POWER_REPORT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上行发射功率和主载波上报请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  uhwToolsId;                     /* 保留字段 */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;                      /* 上报允许标志 */
    VOS_UINT16                                  uhwRptPeriod;                   /* 上报周期 */
}WPHY_TOOL_POWER_REPORT_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_POWER_REPORT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上行发射功率和主载波上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                    /* _H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                      uhwToolsId;                 /* 保留字段 */
    VOS_INT16                                       shwTxAvrgPwr;               /* 平均传输功率 */
    VOS_INT16                                       shwFilterDpcchPwr;          /* 滤波结果 */ /* 原语类型 */

}WPHY_TOOL_POWER_REPORT_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSDPA_LINK_STATISTICS_REPORT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 主辅载波均衡调节可维可测统计上报请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  uhwToolsId;                     /* 保留字段 */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;                      /* 上报允许标志 */
    VOS_UINT16                                  uhwRptPeriod;                   /* 上报周期 */
}WPHY_TOOL_HSDPA_LINK_STATISTICS_REPORT_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSDPA_LINK_STATISTICS_REPORT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 主辅载波均衡调节可维可测统计上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                    /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                      uhwToolsId;                 /* 保留字段 */
    VOS_UINT16                                      uhwCqiRpt[WPHY_MNTN_MAX_CARRIER_NUM][WPHY_MNTN_SUB_FRAME_NUM];  /* 第1行保存主载波每个子帧的CQI，第2行保存辅载波每个子帧的CQI */
}WPHY_TOOL_HSDPA_LINK_STATISTICS_REPORT_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_DUAL_ANTENNA_STATISTICS_REPORT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 天线相关信息上报格式
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      uhwAntennaEnable;           /* 天线前端开关。1，表示打开；0，表示关闭。W、TDS和C共用。 */
    VOS_UINT16                                      uhwDspRptRssiRf;            /* BBP上报天线口RSSI值（双载波之和），0.125dB精度。说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。 */
    VOS_UINT16                                      uhwDspRptAgcState;          /* BBP上报用于控制RF增益的状态机。0，表示S1；1，表示S2；2，表示S3；3，表示S4；4，表示S5；5，表示S6；6，表示S7；7，表示S8。说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。 */
}WPHY_DUAL_ANTENNA_STATISTICS_REPORT_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_DUAL_ANTENNA_STATISTICS_REPORT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 双天线相关信息统计上报请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  uhwToolsId;                     /* 保留字段 */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;                      /* 上报允许标志 */
    VOS_UINT16                                  uhwRptPeriod;                   /* 上报周期 */
}WPHY_TOOL_DUAL_ANTENNA_STATISTICS_REPORT_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSDPA_LINK_STATISTICS_S_REPORT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 双天线相关信息统计上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                    /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                      uhwToolsId;                 /* 保留字段 */
    WPHY_DUAL_ANTENNA_STATISTICS_REPORT_STRU        astDualAntennaStatistics[WPHY_MNTN_WBBP_MAX_ANT_NUM];    /* 主天线和辅天线 */
}WPHY_TOOL_DUAL_ANTENNA_STATISTICS_REPORT_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSUPA_EDCH_ACTIVE_SET_REPORT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA EDCH激活集信息上报请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  uhwToolsId;                     /* 保留字段 */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;                      /* 上报允许标志 */
    VOS_UINT16                                  uhwRptPeriod;                   /* 上报周期 */
}WPHY_TOOL_HSUPA_EDCH_ACTIVE_SET_REPORT_REQ_STRU;

/*****************************************************************************

*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      uhwRlScram;                 /* HSUPA激活集小区主扰码初相 */
    VOS_UINT16                                      uhwRgServRlFlag;         /* 标识是否在RGCH服务的无线链路集中，0表示该RL不在RGCH服务RLS中，1表示该RL在RGCH服务RLS中 */
    VOS_UINT16                                      uhwTpcIndex;                /* HICH无线链路的无线链路集号，正常取值范围0~5，7为无效号，表示不属于任何一个HICH无线链路集。 */
    VOS_UINT16                                      uhwServingEdchFlag;         /* 标识小区是否E-DCH信道服务小区，0表示小区不是E-DCH的服务小区，1表示小区是E-DCH的服务小区*/
    VOS_UINT16                                      uhwHsupaFlag;               /* 标识小区是否支持HICH，0为不支持，1表示支持*/
}WPHY_HSUPA_EDCH_ACTIVE_SET_INFO_REPORT_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSUPA_EDCH_ACTIVE_SET_REPORT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA EDCH激活集信息上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                    /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                      uhwToolsId;                 /* 保留字段 */
    WPHY_HSUPA_EDCH_ACTIVE_SET_INFO_REPORT_STRU     astActiveSetInfo[WPHY_MNTN_HSUPA_ACTIVE_SET_MAX_NUM];
}WPHY_TOOL_HSUPA_EDCH_ACTIVE_SET_REPORT_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_RADIO_PARA_CELL_SNR_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 小区载干比信息上报请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  uhwToolsId;                     /* 保留字段 */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;                      /* 上报允许标志 */
    VOS_UINT16                                  uhwRptPeriod;                   /* 上报周期 */
}WPHY_TOOL_RADIO_PARA_CELL_SNR_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_RADIO_PARA_CELL_SNR_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 载干比信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      uwSignalPower;              /* 信号功率 */
    VOS_UINT32                                      uwNoisePower;               /* 噪声功率 */
}WPHY_MNTN_CELL_SNR_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_RADIO_PARA_CELL_SNR_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 小区载干比信息上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                    /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                      uhwToolsId;                 /* 保留字段 */
    WPHY_MNTN_CELL_SNR_INFO_STRU                    astCellSnrInfo[WPHY_MNTN_SLOT_NUM_BY_FRAME];    /* DPCH 15个时隙载干比信息 */
}WPHY_TOOL_RADIO_PARA_CELL_SNR_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSPDSCH_CFG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DPA参数上报请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  uhwToolsId;                     /* 保留字段 */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;                      /* 上报允许标志 */
    VOS_UINT16                                  uhwRptPeriod;                   /* 上报周期 */
}WPHY_TOOL_HSPDSCH_CFG_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSPDSCH_CFG_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DPA参数的消息上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                    /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                      uhwToolsId;                 /* 保留字段 */
    VOS_INT32                                       swDLDpchOffset;             /* DPCH相对于HSSCCH的时间偏移 */
    VOS_UINT16                                      uhwHarqProcesses;           /* DPA支持的线程数 */
    VOS_UINT16                                      uhwReserved;                /* 保留字段 */
}WPHY_TOOL_HSPDSCH_CFG_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSSCCH_CFG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HS-SCCH参数上报请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  uhwToolsId;                     /* 保留字段 */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;                      /* 上报允许标志 */
    VOS_UINT16                                  uhwRptPeriod;                   /* 上报周期 */
}WPHY_TOOL_HSSCCH_CFG_REQ_STRU;

/*****************************************************************************
 结构名    : HS_SCCH_CONFIGURATION_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HS-SCCH参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  uhwHsScchNo;                    /* 使用HS-SCCH编号表示其有效性 */
    VOS_UINT16                                  uhwOvsf;                        /* 主小区HS-SCCH的ovsf码号 */
}HS_SCCH_CONFIGURATION_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSSCCH_CFG_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HS-SCCH参数上报的消息结构
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                    /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                      uhwToolsId;                 /* 保留字段 */
    VOS_UINT16                                      uhwHsscchNum;
    VOS_UINT16                                      uhwReserved;
    HS_SCCH_CONFIGURATION_STRU                      astHsscchValue[WPHY_MAIN_CELL_HSDPA_SCCH_MAX_NUM];
}WPHY_TOOL_HSSCCH_CFG_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSDPCCH_CFG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HS-DPCCH信道配置参数上报请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  uhwToolsId;                     /* 保留字段 */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;                      /* 上报允许标志 */
    VOS_UINT16                                  uhwRptPeriod;                   /* 上报周期 */
}WPHY_TOOL_HSDPCCH_CFG_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSDPCCH_CFG_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HS-DPCCH信道配置参数上报消息格式
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                    /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                      uhwToolsId;                 /* 保留字段 */
    VOS_UINT16                                      uhwCqiCycle;                /* CQI发送周期 */
    VOS_UINT16                                      uhwCqiRpt;                  /* CQI连续发射次数，取值范围1~4 */
    VOS_UINT16                                      uhwCqiAck;                  /* ACK/NACK连续发射次数，取值范围1~4 */
    VOS_UINT16                                      uhwHsDpcchChipOffset;         /* HS-DPCCH第一个子帧帧头与上行DPCH帧头偏移chip数 */
    VOS_UINT16                                      uhwPoAck;                   /* HS-DPCCH信道调制增益因子，最大值38 */
    VOS_UINT16                                      uhwPoNack;                  /* HS-DPCCH信道调制增益因子，最大值38 */
    VOS_UINT16                                      uhwPoCqi;                   /* HS-DPCCH信道调制增益因子，最大值38 */
    VOS_UINT16                                      uhwReserved;                /* 保留字段 */
}WPHY_TOOL_HSDPCCH_CFG_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HS_HSDPA_CQI_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSDPA信道CQI消息上报请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  uhwToolsId;                     /* 保留字段 */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;                      /* 上报允许标志 */
    VOS_UINT16                                  uhwRptPeriod;                   /* 上报周期 */
}WPHY_TOOL_HS_HSDPA_CQI_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HS_HSDPA_CQI_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSDPA信道CQI消息上报格式
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                    /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  uhwToolsId;                 /* 保留字段 */
    VOS_UINT16                                  uhwCarrierNum;              /* 上报的载波数量 */
    VOS_UINT16                                  uhwReserved;                /* 保留字段 */
    VOS_UINT16                                  auhwCqi[WPHY_MNTN_MAX_CARRIER_NUM];     /* channel quality indicator */
}WPHY_TOOL_HS_HSDPA_CQI_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSDPA_LINK_STAT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 主辅载波均衡调节可维可测统计上报的消息结构请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  uhwToolsId;                     /* 保留字段 */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;                      /* 上报允许标志 */
    VOS_UINT16                                  uhwRptPeriod;                   /* 上报周期 */
}WPHY_TOOL_HSDPA_LINK_STAT_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSDPA_LINK_STAT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 主辅载波均衡调节可维可测统计上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                    /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                      uhwToolsId;                 /* 保留字段 */
    VOS_UINT16                                      uhwCqiRpt[WPHY_MNTN_MAX_CARRIER_NUM][WPHY_MNTN_SUB_FRAME_NUM];  /* 第1行保存主载波每个子帧的CQI，第2行保存辅载波每个子帧的CQI */
}WPHY_TOOL_HSDPA_LINK_STAT_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSDPA_DECOD_STAT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上报HS-DSCH译码信息的请求消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  uhwToolsId;                     /* 保留字段 */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;                      /* 上报允许标志 */
    VOS_UINT16                                  uhwRptPeriod;                   /* 上报周期 */
}WPHY_TOOL_HSDPA_DECOD_STAT_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSDPA_DEC_STAT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上报HS-DSCH译码信息
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                    /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                      uhwToolsId;                 /* 保留字段 */
    WPHY_TOOL_HSSCCH_DECODE_INFO_STRU               astHsScchDecodeInfo[WPHY_MNTN_MAX_CARRIER_NUM];    /* 原语类型 */
}WPHY_TOOL_HSDPA_DEC_STAT_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSDPA_DEC_TBS_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上报HS-DSCH译码信息请求的消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  uhwToolsId;                     /* 保留字段 */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;                      /* 上报允许标志 */
    VOS_UINT16                                  uhwRptPeriod;
    VOS_UINT16                                  uhwReserved;
    VOS_UINT16                                  uhwRegionNum;                    /* 配置为0-9，必须与ausThredhold中的数目匹配 */
    VOS_UINT16                                  auhwThredhold[WPHY_MNTN_MAX_REGION_NUM];
}WPHY_TOOL_HSDPA_DEC_TBS_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSDPA_DEC_TBS_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上报HS-DSCH译码信息
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                    /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                      uhwToolsId;                 /* 保留字段 */
    WPHY_TOOL_HSDSCH_DECODE_INFO_STRU               astHsDschDecodeInfo[WPHY_MNTN_MAX_CARRIER_NUM]; /* 原语类型 */
}WPHY_TOOL_HSDPA_DEC_TBS_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_MNTN_HSUPA_LINK_THROUGHPUT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上报HS-DSCH译码信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwSchedDataRate;                        /* 链路可调度传输的数据比特率 */
    VOS_UINT32                          uwNonSchedDataRate;                     /* 链路不可调度传输的数据比特率 */
}WPHY_MNTN_HSUPA_LINK_THROUGHPUT_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_MNTN_RPT_HSUPA_CTRL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上报路测功能控制
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16           enReportFlag;               /*_H2ASN_Skip */ /* 是否需要上报 */
    VOS_UINT16                                      uhwPeriod;                  /*_H2ASN_Skip */ /* 上报周期 */
    VOS_UINT16                                      uhwPeriodCnt;               /*_H2ASN_Skip */ /* 上报周期计数 */
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16                 enRptStatus;                /*_H2ASN_Skip */ /* 上报状态，TRUE表示在上报 */
    WPHY_MNTN_HSUPA_LINK_THROUGHPUT_INFO_STRU       astThroughputInfo[WPHY_MNTN_MAX_CARRIER_NUM];  /* 主辅载波upa链路吞吐量信息统计 */
}WPHY_MNTN_RPT_HSUPA_CTRL_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSUPA_LINK_THROUGHPUT_RPT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA链路吞吐量统计上报请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  uhwToolsId;                     /* 保留字段 */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;                      /* 上报允许标志 */
    VOS_UINT16                                  uhwRptPeriod;                   /* 上报周期 */
}WPHY_TOOL_HSUPA_LINK_THROUGHPUT_RPT_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSUPA_LINK_THROUGHPUT_RPT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA链路吞吐量统计上报的信息结构
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                    /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                      uhwToolsId;                 /* 保留字段 */
    VOS_UINT16                                      uhwCarrierNum;
    VOS_UINT16                                      uhwReversed;
    WPHY_MNTN_HSUPA_LINK_THROUGHPUT_INFO_STRU       astThroughputInfo[WPHY_MNTN_MAX_CARRIER_NUM];  /* 主辅载波upa链路吞吐量信息统计 */
}WPHY_TOOL_HSUPA_LINK_THROUGHPUT_RPT_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_MNTN_HSUPA_LINK_QUALITY_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA链路质量信息统计
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      uhwSendDataCnt;             /* 总调度块数 */
    VOS_UINT16                                      uhwSblerCnt;                /* 调度错误块数 */
    VOS_UINT16                                      uhw1stSblerCnt;             /* 初传调度块总数 */
    VOS_UINT16                                      uhw1stSendDataCnt;          /* 初传调度错误块数 */
    VOS_UINT16                                      uhwPowerLimitedCnt;         /* power受限统计 */
    VOS_UINT16                                      uhwSGLimitedCnt;            /* SG受限统计 */
    VOS_UINT16                                      uhwBufferLimitedCnt;        /* buffer受限统计 */
    VOS_UINT16                                      uhwLimitedTotalCnt;         /* 功率受限总块数 */
    VOS_UINT16                                      uhwHappyCnt;                /* happy统计 */
    VOS_UINT16                                      uhwReserved;                /* 调度的总块数 */
}WPHY_MNTN_HSUPA_LINK_QUALITY_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_MNTN_RPT_HSUPA_LINK_QUALITY_CTRL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上报路测功能控制信息
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16           enReportFlag;               /*_H2ASN_Skip */ /* 是否需要上报 */
    VOS_UINT16                                      uhwPeriod;                  /*_H2ASN_Skip */ /* 上报周期 */
    VOS_UINT16                                      uhwPeriodCnt;               /*_H2ASN_Skip */ /* 上报周期计数 */
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16                 enRptStatus;                /*_H2ASN_Skip */ /* 上报状态，TRUE表示在上报 */
    WPHY_MNTN_HSUPA_LINK_QUALITY_INFO_STRU          astQualityInfo[WPHY_MNTN_MAX_CARRIER_NUM];  /* 主辅载波的upa链路质量信息 */
}WPHY_MNTN_RPT_HSUPA_LINK_QUALITY_CTRL_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSUPA_LINK_QUALITY_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA链路质量参数上报请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  uhwToolsId;                     /* 保留字段 */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;                      /* 上报允许标志 */
    VOS_UINT16                                  uhwRptPeriod;                   /* 上报周期 */
}WPHY_TOOL_HSUPA_LINK_QUALITY_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSUPA_LINK_QUALITY_RPT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA链路质量参数上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                    /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                      uhwToolsId;                 /* 保留字段 */
    WPHY_MNTN_HSUPA_LINK_QUALITY_INFO_STRU          astQualityInfo[WPHY_MNTN_MAX_CARRIER_NUM];  /* 主辅载波的upa链路质量信息 */
}WPHY_TOOL_HSUPA_LINK_QUALITY_RPT_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSUPA_GRANT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA授权信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwAgValue;                              /* AG统计累加值 */
    VOS_UINT32                          uwSgCnt;                                /* SG统计值 */
    VOS_UINT32                          uwSgValue;                              /* SG统计值 */
    VOS_UINT16                          uhwAgCnt;                               /* AG计数, 计算AG平均值 */
    VOS_UINT16                          uhwRgUpCnt;                             /* RG up统计 */
    VOS_UINT16                          uhwRgHoldCnt;                           /* RG hold统计 */
    VOS_UINT16                          uhwRgDownCnt;                           /* RG down统计 */
    VOS_UINT16                          uhwRgTotalCnt;                          /* RG 总数统计, 用于计算RG比率 */
    VOS_UINT16                          uhwTotalCnt;                            /* 总的统计次数 */
}WPHY_MNTN_HSUPA_GRANT_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_MNTN_RPT_HSUPA_GRANT_CTRL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上报upa grant路测功能控制
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16           enReportFlag;               /*_H2ASN_Skip */ /* 是否需要上报 */
    VOS_UINT16                                      uhwPeriod;                  /*_H2ASN_Skip */ /* 上报周期 */
    VOS_UINT16                                      uhwPeriodCnt;               /*_H2ASN_Skip */ /* 上报周期计数 */
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16                 enRptStatus;                /*_H2ASN_Skip */ /* 上报状态，TRUE表示在上报 */
    WPHY_MNTN_HSUPA_GRANT_INFO_STRU                 astGrantInfo[WPHY_MNTN_MAX_CARRIER_NUM];        /* 主辅载波的授权消息统计 */
}WPHY_MNTN_RPT_HSUPA_GRANT_CTRL_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSUPA_GRANT_RPT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA GRANT统计上报请求消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  uhwToolsId;                     /* 保留字段 */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;                      /* 上报允许标志 */
    VOS_UINT16                                  uhwRptPeriod;                   /* 上报周期 */
}WPHY_TOOL_HSUPA_GRANT_RPT_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_HSUPA_GRANT_RPT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA GRANT统计上报消息结构
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                    /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                      uhwToolsId;                 /* 保留字段 */
    WPHY_MNTN_HSUPA_GRANT_INFO_STRU                 astGrantInfo[WPHY_MNTN_MAX_CARRIER_NUM];    /* 主辅载波授权信息 */
}WPHY_TOOL_HSUPA_GRANT_RPT_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_PWR_CTRL_PWR_RPT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 传输功率上报请求消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  uhwToolsId;                     /* 保留字段 */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;                      /* 上报允许标志 */
    VOS_UINT16                                  uhwRptPeriod;                   /* 上报周期 */
}WPHY_TOOL_PWR_CTRL_PWR_RPT_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_PWR_CTRL_PWR_RPT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 传输功率上报消息结构
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16   enMsgId;                                /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                          uhwToolsId;                             /* 保留字段 */
    VOS_INT16                           shwTxPwrVal;                            /* 传输功率 */
    VOS_INT16                           shwRxPwrAnt1Val;                        /* 天线1的接收功率 */
    VOS_INT16                           shwRxPwrAnt2Val;                        /* 天线2的接收功率 */
    VOS_UINT16                          ushReserved;                            /* 保留 */
}WPHY_TOOL_PWR_CTRL_PWR_RPT_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_PWR_CTRL_TPC_RPT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 传输功率控制TPC上报消息结构
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_DL_TPC_CMD_ENUM_UINT16   enDlTpcCmd;                         /* 下行传输功率控制字 */
    WPHY_TOOL_MNTN_UL_TPC_CMD_ENUM_UINT16   enUlTpcCmd;                         /* 上行传输功率控制字 */
}WPHY_MNTN_TPC_INFO_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_PWR_CTRL_TPC_RPT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 传输功率控制TPC上报请求消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  uhwToolsId;                     /* 保留字段 */
    WPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16       enRptFlag;                      /* 上报允许标志 */
    VOS_UINT16                                  uhwRptPeriod;                   /* 上报周期 */
}WPHY_TOOL_PWR_CTRL_TPC_RPT_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_PWR_CTRL_TPC_RPT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 传输功率控制TPC上报消息结构
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                    /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                      uhwToolsId;                 /* 保留字段 */
    WPHY_MNTN_TPC_INFO_STRU                         astTpcInfo[WPHY_MNTN_SLOT_NUM_BY_FRAME];    /* 传输功率控制信息 */
}WPHY_TOOL_PWR_CTRL_TPC_RPT_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_CAL_RX_MNTN_UNIT_STRU
 结构说明  : W RX校准轨迹打印, 一次所有流程为一个打印单元
*****************************************************************************/
typedef struct
{
    /* 配置 */
    VOS_UINT16                          uhwRxConfigTimeSfn;
    VOS_UINT16                          uhwRxConfigTimeSlot;
    VOS_UINT16                          uhwRxConfigTimeChip;
    VOS_UINT16                          uhwBand;
    VOS_UINT16                          uhwFreq;
    VOS_UINT16                          uhwAgcCfg;

    /* 结果 */
    VOS_UINT16                          uhwRSSIStartTimeSfn;
    VOS_UINT16                          uhwRSSIStartTimeSlot;
    VOS_UINT16                          uhwRSSIStartTimeChip;
    VOS_UINT16                          uhwRSSIRsltTimeSfn;
    VOS_UINT16                          uhwRSSIRsltTimeSlot;
    VOS_UINT16                          uhwRSSIRsltTimeChip;
    VOS_INT32                           swRssiAnt1Rslt;
    VOS_INT32                           swRssiAnt2Rslt;
    VOS_INT16                           shwRSSIAnt1FirstRslt;
    VOS_INT16                           shwRSSIAnt2FirstRslt;
    VOS_INT16                           shwRSSIAnt1EndRslt;
    VOS_INT16                           shwRSSIAnt2EndRslt;
}WPHY_TOOL_CAL_RX_MNTN_UNIT_STRU;
/*****************************************************************************
 结构名    : WPHY_TOOL_CAL_RX_FAST_MNTN_UNIT_STRU
 结构说明  : W RX校准轨迹打印, 一次所有流程为一个打印单元
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwRxValidNum;                          /* 记录的有效个数 */
    VOS_UINT16                          uhwReserved;                            /* 保留 */
    WPHY_TOOL_CAL_RX_MNTN_UNIT_STRU     astWphyRxFastCalMntn[WPHY_CAL_RX_FAST_CAL_MAX_VAILD_NUM];
}WPHY_TOOL_CAL_RX_FAST_MNTN_UNIT_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_RX_FAST_CAL_MNTN_RPT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Rx Fast Cal可维可测信息上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16               enMsgId;                            /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                      usToolsId;                          /* 保留字段 */
    WPHY_TOOL_CAL_RX_FAST_MNTN_UNIT_STRU            stWphyToolRxFastCal;
}WPHY_TOOL_RX_FAST_CAL_MNTN_RPT_STRU;

/*****************************************************************************
 结构名    : WPHY_MAS_ANTENNA_STATUS_STRU
 结构说明  : MAS 天线TAS/MAS状态结构体
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MAS_ANTTASSTATUS_ENUM_UINT16       enTasStatus;                        /* 天线TAS状态 */
    WPHY_TOOL_MNTN_MAS_ANTMASSTATUS_ENUM_UINT16       enMasStatus;                        /* 天线MAS状态 */
}WPHY_TOOL_MAS_ANTENNA_STATUS_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_MAS_BLIND_STATE_MEAS_PARA_STRU
 结构说明  : 记录盲切换状态测量信息
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16         enSampleInd;                        /* 样点指示( 0:表示第一个样点,1:表示非第一个样点 )*/
    VOS_UINT16                              uhwCalCount;                        /* 计算平均值累加次数 */
    VOS_UINT32                              uwMeasSlice;                        /* 第一次测量时的slice */
    VOS_UINT32                              uwEcSumPre;                         /* 激活集内小区径能量和 */
    VOS_UINT32                              uwEcSumCurr;                        /* 激活集内小区径能量和 */
    VOS_UINT32                              uwEcAvePre;                         /* 激活集内单小区平均径能量和 */
    VOS_UINT32                              uwEcAveCurr;                        /* 激活集内单小区平均径能量和 */
    VOS_INT16                               shwGainRfPre;                       /* 激活集内前一5ms的rf增益和误差 */
    VOS_INT16                               shwGainRfCurr;                      /* 激活集内当前5ms内rf增益和误差 */
    VOS_UINT32                              uwEcAveAccPre;                      /* 激活集内单小区平均值累加径能量和 */
    VOS_UINT32                              uwEcAveAccCurr;                     /* 激活集内单小区平均累加径能量和 */
    VOS_INT16                               shwRscpRfAvePre;                    /* T1时间内激活集小区天线口能量平均值 */
    VOS_INT16                               shwRscpRfAveCurr;                   /* T1时间内激活集小区天线口能量平均值 */
}WPHY_TOOL_MAS_BLIND_STATE_MEAS_PARA_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_MAS_NONBLIND_MEAS_PARA_STRU
 结构说明  : MAS 天线明切能量信息结构体
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16         enSampleInd;                        /* 样点指示( FALSE:表示第一个样点,TRUE:表示非第一个样点 )*/
    VOS_UINT16                              uhwReserve;                         /* 4字节对齐 */
    VOS_UINT32                              uwMeasSlice;                        /* 第一次测量时间点*/
    VOS_INT16                               shwRscp;                            /* 天线RSCP */
    VOS_INT16                               shwRssi;                            /* 天线RSSI */

}WPHY_TOOL_MAS_NONBLIND_MEAS_PARA_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_MAS_ANT_INFO_IND_STRU
 结构说明  : MAS算法天线资讯可维可测上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16                  enEvaFinishFlag;           /* 当前State是哪个State */
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16                  enEvaInherit;              /* 当前State当前天线评估能量是否可以继承 */
    WPHY_TOOL_MAS_ANTENNA_STATUS_STRU                stAntStatus;               /* 当前State当前天线TAS/MAS状态 */
    WPHY_TOOL_MAS_BLIND_STATE_MEAS_PARA_STRU         stBlindEnergy;             /* 当前State当前天线盲切采集的激活集所有小区能量信息 */
    WPHY_TOOL_MAS_NONBLIND_MEAS_PARA_STRU            stNonBlindEnergy;          /* 当前State当前天线明切采集的跟踪单小区能量信息 */
}WPHY_TOOL_MAS_ANT_INFO_IND_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_MAS_MNTN_STATEI_IND_STRU
 结构说明  : MAS StateI 可维可测上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16             enLeaveStateI;                  /* 是否离开StateI */
    WPHY_TOOL_MNTN_CTRL_MODE_ENUM_UINT16        enCtrlMode;                     /* 控制模式 */
    WPHY_TOOL_MNTN_MAS_STATE_ENUM_UINT16        enNextState;                    /* 下一State是哪个State */
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16             enIaEnable;                     /* Ia是否使能 */
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16             enIbEnable;                     /* Ib是否使能 */
    VOS_UINT16                                  usRsv;                          /* 四字节对齐 */
    WPHY_TOOL_MAS_ANT_INFO_IND_STRU             stAntInfo;                      /* 当前天线信息 */
}WPHY_TOOL_MAS_MNTN_STATEI_IND_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_MAS_MNTN_STATEIAIB_IND_STRU
 结构说明  : MAS StateIaIb 可维可测上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  uhwRoundCount;                  /* 当前比较轮数 */
    WPHY_TOOL_MNTN_CTRL_MODE_ENUM_UINT16        enCtrlMode;                     /* 控制模式 */
    WPHY_TOOL_MNTN_MAS_STATE_ENUM_UINT16        enNextState;                    /* 下一State是哪个State */
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16             enEarlyExit;                    /* 是否足够好而已可以提早冻结 */
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16             enDestAntBetter;                /* 目标天线是否较好, 相当於是否切换天线*/
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16             enIaEnable;                     /* Ia是否使能 */
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16             enIbEnable;                     /* Ib是否使能 */
    VOS_UINT16                                  usRsv;                          /* 四字节对齐 */
    WPHY_TOOL_MAS_ANT_INFO_IND_STRU             stSrcAntInfo;                   /* 源天线信息 */
    WPHY_TOOL_MAS_ANT_INFO_IND_STRU             stDestAntInfo;                  /* 目标天线信息 */
}WPHY_TOOL_MAS_MNTN_STATEIAIB_IND_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_MAS_MNTN_STATEII_IND_STRU
 结构说明  : MAS StateII 可维可测上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  uhwRoundCount;                  /* 当前比较轮数 */
    WPHY_TOOL_MNTN_CTRL_MODE_ENUM_UINT16        enCtrlMode;                     /* 控制模式 */
    WPHY_TOOL_MNTN_MAS_STATE_ENUM_UINT16        enNextState;                    /* 下一State是哪个State */
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16             enEarlyExit;                    /* 是否足够好而已可以提早冻结 */
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16             enDestAntBetter;                /* 目标天线是否较好, 相当於是否切换天线*/
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16             enIaEnable;                     /* Ia是否使能 */
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16             enIbEnable;                     /* Ib是否使能 */
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16             enHoldBlind;                    /* 盲切维持标记 */
    WPHY_TOOL_MAS_ANT_INFO_IND_STRU             stSrcAntInfo;                   /* 源天线信息 */
    WPHY_TOOL_MAS_ANT_INFO_IND_STRU             stDestAntInfo;                  /* 目标天线信息 */
}WPHY_TOOL_MAS_MNTN_STATEII_IND_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_MAS_MNTN_STATEIII_IND_STRU
 结构说明  : MAS StateIII 可维可测上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MNTN_CTRL_MODE_ENUM_UINT16        enCtrlMode;                     /* 控制模式 */
    WPHY_TOOL_MNTN_MAS_STATE_ENUM_UINT16        enNextState;                    /* 下一State是哪个State */
}WPHY_TOOL_MAS_MNTN_STATEIII_IND_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_MAS_MNTN_NONBLINDINFO_IND_STRU
 结构说明  : MAS 明切算法可维可测上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16       enMsgId;                            /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usToolsId;                          /* 保留字段 */
    VOS_INT16                               shwRscpSrc;                         /* 主集天线测量结果 */
    VOS_INT16                               shwRscpDest;                        /* 分集天线测量结果 */
    VOS_UINT16                              uhwCountLow;                        /* Low Count 计数 */
    VOS_UINT16                              uhwCountHigh;                       /* High Count 计数 */
    VOS_UINT16                              uhwCountTotal;                      /* Total Count 计数 */
    VOS_UINT16                              usRsv;                              /* 四字节对齐 */
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16         enDualAntEvaFinish;                 /* 双天线采样评估结束标记  */
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16         enNewAntBetter;                     /* 新天线较好标记 */
}WPHY_TOOL_MAS_MNTN_NONBLINDINFO_IND_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_MAS_MNTN_MAS_SWITCH_IND_STRU
 结构说明  : MAS 左右旋 可维可测上报
*****************************************************************************/
typedef struct
{
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MAS_ANTENNA_STATUS_STRU           stAntStatus;                    /* 当前State当前天线TAS/MAS状态 */
}WPHY_TOOL_MAS_MNTN_MAS_SWITCH_IND_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_FUNC_BIT_CONTROL_REQ_STRU
 结构说明  : WPHY 可维可测功能控制下发的结构原语:用来控制功能设置请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT32                                  ulFuncBitMask;                  /* 对应Bit位置位,则控制该功能生效 */
}WPHY_TOOL_FUNC_BIT_CONTROL_REQ_STRU;


/*****************************************************************************
 结构名    : UPHY_TOOL_BBP_DBG_REG_RD_STRU
 协议表格  :
 结构说明  : 状态查询回复CNF消息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwAddr;                             /* 寄存器地址 */
    VOS_UINT32                              uwValue;                            /* 寄存器值 */
} UPHY_TOOL_BBP_DBG_REG_RD_STRU;

/*****************************************************************************
 结构名    : UPHY_TOOL_BBP_DBG_REG_RD_LIST_STRU
 协议表格  :
 结构说明  : 状态查询回复CNF消息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwRegRdNum;                                     /* RegList个数 */
    UPHY_TOOL_BBP_DBG_REG_RD_STRU           astRegList[UPHY_TOOL_BBP_DBG_SAMPLE_REG_NUM];   /* REG_RD_STATUS_STRU */
}UPHY_TOOL_BBP_DBG_REG_RD_LIST_STRU;

/*****************************************************************************
 结构名    : UPHY_TOOL_BBP_DBG_REG_RD_REPORT_STRU
 协议表格  :
 结构说明  : 状态查询回复CNF消息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwOmDrxSampleId;                    /* 默认值0 */
    VOS_UINT16                              uhwOpid;                            /* 默认值1 */
    VOS_UINT16                              uhwStatus;                          /* 默认值0 */
    UPHY_TOOL_BBP_DBG_REG_RD_LIST_STRU      astDrxRegData;                      /* 一个 REG_CONFIG_LIST_STRU */
}UPHY_TOOL_BBP_DBG_REG_RD_REPORT_STRU;


/*****************************************************************************
 结构名    : UPHY_TOOL_BBP_DBG_REG_RD_REPORT_IND_STRU
 协议表格  :
 结构说明  : 工具寄存器配置消息上报结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  uhwMsgId;                           /*_H2ASN_Skip*/
    VOS_UINT16                                  uhwToolsId;
    UPHY_TOOL_BBP_DBG_REG_RD_REPORT_STRU        astSampleReg;                       /* UPHY_TOOL_BBP_DBG_REG_RD_REPORT_STRU */
}UPHY_TOOL_BBP_DBG_REG_RD_REPORT_IND_STRU;


/*****************************************************************************
 结构名    : UPHY_TOOL_BBP_DBG_REG_WR_STRU
 协议表格  :
 结构说明  : 工具寄存器配置消息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwAddr;                             /* 寄存器地址 */
    VOS_UINT32                              uwMask;                             /* 掩码 */
    VOS_UINT32                              uwValue;                            /* 寄存器值 */
} UPHY_TOOL_BBP_DBG_REG_WR_STRU;


/*****************************************************************************
 结构名    : UPHY_TOOL_BBP_DBG_REG_WR_LIST_STRU
 协议表格  :
 结构说明  : 工具寄存器配置消息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwRegNum;                                       /* RegList个数 */
    UPHY_TOOL_BBP_DBG_REG_WR_STRU           astRegList[UPHY_TOOL_BBP_DBG_SAMPLE_REG_NUM];   /* 结构:REG_CONFIG_WR_STRU */
} UPHY_TOOL_BBP_DBG_REG_WR_LIST_STRU;

/*****************************************************************************
 结构名    : UPHY_TOOL_BBP_DBG_REG_WR_MSG_STRU
 协议表格  :
 结构说明  : 工具寄存器配置消息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwOmDrxSampleId;                                            /* 默认值0,取值分别为BUS/DATA */
    VOS_UINT16                              uhwOpid;                                                    /* 开始采数=4，停止采数=2，查询状态=1 */
    VOS_UINT16                              uhwPowrDomainBitmap;                                        /* 默认值0xFFFF */
    UPHY_TOOL_BBP_DBG_REG_WR_LIST_STRU      astDrxSampleRegData[UPHY_TOOL_BBP_DBG_SAMPLE_REG_LIST_NUM]; /* 1,2,3部门，采数寄存器，每组结构为REG_CONFIG_LIST_STRU */
    UPHY_TOOL_BBP_DBG_REG_WR_LIST_STRU      stDrxReportRegData;                                         /* 寄存器上报 */
    UPHY_TOOL_BBP_DBG_REG_WR_LIST_STRU      stDrxStopRegData;                                           /* 停止寄存器 */
    UPHY_TOOL_BBP_DBG_REG_WR_LIST_STRU      astDrxOtherRegData[UPHY_TOOL_BBP_DBG_OTHER_REG_LIST_NUM];   /* other ,暂时不用 */
}UPHY_TOOL_BBP_DBG_REG_WR_MSG_STRU;

/*****************************************************************************
 结构名    : UPHY_TOOL_BBP_DBG_REG_CFG_STRU
 协议表格  :
 结构说明  : 工具寄存器配置消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                              uhwMsgId;                           /*_H2ASN_Skip*/
    VOS_UINT16                              uhwToolsId;
    UPHY_TOOL_BBP_DBG_REG_WR_MSG_STRU       stSampleReg;
}UPHY_TOOL_BBP_DBG_REG_CFG_STRU;


/*****************************************************************************
 结构名    : UPHY_TOOL_BBP_DBG_REG_WR_LIST_INFO_STRU
 协议表格  :
 结构说明  : 工具寄存器配置消息上下文
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_BOOL_ENUM_UINT16         enDataFlag;                                                 /* 采数寄存器的开关标志 */
    VOS_UINT16                              uhwRsv;
    UPHY_TOOL_BBP_DBG_REG_WR_LIST_STRU      astDrxSampleRegData[UPHY_TOOL_BBP_DBG_SAMPLE_REG_LIST_NUM]; /* 1,2,3部门，采数寄存器，每组结构为REG_CONFIG_LIST_STRU */
    UPHY_TOOL_BBP_DBG_REG_WR_LIST_STRU      stDrxReportRegData;                                         /* 寄存器上报 */
    UPHY_TOOL_BBP_DBG_REG_WR_LIST_STRU      stDrxStopRegData;                                           /* 停止寄存器 */
    UPHY_TOOL_BBP_DBG_REG_WR_LIST_STRU      astDrxOtherRegData[UPHY_TOOL_BBP_DBG_OTHER_REG_LIST_NUM];   /* other ,暂时不用 */
} UPHY_TOOL_BBP_DBG_REG_WR_LIST_INFO_STRU;


/*****************************************************************************
 结构名    : UPHY_TOOL_BBP_DBG_REG_WR_IND_STRU
 协议表格  :
 结构说明  : 工具寄存器配置消息上报结构,仅用于可维可测，观测采数寄存器是否正确配置
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                              uhwMsgId;                           /*_H2ASN_Skip*/
    VOS_UINT16                              uhwToolsId;
    VOS_UINT32                              uwOmDrxSampleId;                    /* 默认值0,取值分别为BUS/DATA */
    VOS_UINT16                              uhwOpid;                            /* 开始采数=4，停止采数=2，查询状态=1 */
    VOS_UINT16                              uhwPowrDomainBitmap;                /* 默认值0xFFFF */
    UPHY_TOOL_BBP_DBG_REG_WR_LIST_STRU      stDrxSampleRegData;                 /* 1,2,3部门，采数寄存器，每组结构为REG_CONFIG_LIST_STRU */
}UPHY_TOOL_BBP_DBG_REG_WR_IND_STRU;


/*****************************************************************************
 结构名    : UPHY_TOOL_MIPI_READ_SINGLE_REG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 回读单个寄存器的配置
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwNumber;                               /* 回读寄存器的个数 */
    VOS_UINT32                          auwSlaveAddr[UPHY_TOOL_MAX_MIPI_READ_BACK_NUM];  /* 最多回读32个寄存器 */
    VOS_UINT16                          auhwChanNo[UPHY_TOOL_MAX_MIPI_READ_BACK_NUM];    /* 0-3:表示CH0-CH3 */
    VOS_UINT16                          auhwRegAddr[UPHY_TOOL_MAX_MIPI_READ_BACK_NUM];   /* 地址 */
}UPHY_TOOL_MIPI_READ_SINGLE_REG_STRU;


/*****************************************************************************
 结构名    : UPHY_TOOL_SSI_READ_SINGLE_REG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : SSI回读的寄存器格式
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwNumber;                               /* 回读寄存器的个数 */
    VOS_UINT16                          auhwChanNo[UPHY_TOOL_MAX_SSI_READ_BACK_NUM];/* 地址 */
    VOS_UINT16                          auhwRegAddr[UPHY_TOOL_MAX_SSI_READ_BACK_NUM];/* 寄存器 */
}UPHY_TOOL_SSI_READ_SINGLE_REG_STRU;



/*****************************************************************************
 结构名    : UPHY_TOOL_SSI_READ_FUNCTION_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : SSI回读功能
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16 enRptFlag;
    VOS_UINT16                          uhwRptPeriod;
    VOS_UINT16                          uhwRptSlot;                             /* 回读时刻(默认时隙0) */
    VOS_UINT16                          uhwReserved;
    VOS_UINT32                          uwReadType;                             /* 0:指定个数的寄存器回读 1:全部(256个)寄存器回读 */
    VOS_UINT32                          uwReadAllRegChanNumber;                 /* 0-3:表示CH0-CH3。只支持1个通道的回读 */
    UPHY_TOOL_SSI_READ_SINGLE_REG_STRU  stReadSingleReg;                        /* W回读周期2ms */
}UPHY_TOOL_SSI_READ_FUNCTION_STRU;


/*****************************************************************************
 结构名    : UPHY_TOOL_MIPI_READ_FUNCTION_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MIPI回读功能
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_RPT_STATUS_ENUM_UINT16 enRptFlag;
    VOS_UINT16                          uhwRptPeriod;
    VOS_UINT16                          uhwRptSlot;                             /* 回读时刻(默认时隙0) */
    VOS_UINT16                          uhwReserved;
    VOS_UINT32                          uwReadType;                             /* 0:指定个数的寄存器回读,其他值预留 */
    UPHY_TOOL_MIPI_READ_SINGLE_REG_STRU stReadSingleReg;                        /* W回读周期2ms,G回读周期2.3ms */
}UPHY_TOOL_MIPI_READ_FUNCTION_STRU;




/*****************************************************************************
 结构名    : UPHY_TOOL_SSI_MIPI_READ_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 请求回读SSI/MIPI寄存器
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16   enMsgId;                                /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                          usToolsId;                              /* 保留字段 */
    UPHY_TOOL_SSI_READ_FUNCTION_STRU    stSsiFunction;                          /* SSI回读功能 */
}UPHY_TOOL_SSI_READ_RPT_REQ_STRU;


/*****************************************************************************
 结构名    : UPHY_TOOL_SSI_MIPI_READ_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 请求回读SSI/MIPI寄存器
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16   enMsgId;                                /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                          usToolsId;                              /* 保留字段 */
    UPHY_TOOL_MIPI_READ_FUNCTION_STRU   stMipiFunction;                         /* MIPI回读功能 */
}UPHY_TOOL_MIPI_READ_RPT_REQ_STRU;



/*****************************************************************************
 结构名    : UPHY_TOOL_SSI_READ_RPT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上报回读SSI寄存器
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16   enMsgId;                                /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                          usToolsId;                              /* 保留字段 */
    VOS_UINT32                          uwErrorInd;                             /* 回读超时指示 */
    VOS_UINT32                          uwSsiNumber;                            /* 回读寄存器的个数 */
    VOS_UINT32                          auwSsiRegValue[UPHY_TOOL_MAX_SSI_READ_ALL_NUM]; /* SSI寄存器回读值 */
}UPHY_TOOL_SSI_READ_RPT_IND_STRU;


/*****************************************************************************
 结构名    : UPHY_TOOL_MIPI_READ_RPT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上报回读MIPI寄存器
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16   enMsgId;                                /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                          usToolsId;                              /* 保留字段 */
    VOS_UINT32                          uwErrorInd;                             /* 回读超时指示 */
    VOS_UINT32                          uwMipiNumber;                           /* 回读寄存器的个数 */
    VOS_UINT32                          auwMipiRegValue[UPHY_TOOL_MAX_MIPI_READ_BACK_NUM]; /* MIPI寄存器回读值 */
}UPHY_TOOL_MIPI_READ_RPT_IND_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_SSI_MIPI_READ_FUNCTION_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : SSI/MIPI回读功能
*****************************************************************************/
typedef struct
{
    UPHY_TOOL_SSI_READ_FUNCTION_STRU    stSsiFunction;                          /* SSI回读功能 */
    UPHY_TOOL_MIPI_READ_FUNCTION_STRU   stMipiFunction;                         /* MIPI回读功能 */
    UPHY_TOOL_SSI_READ_RPT_IND_STRU     stSsiReportInd;                         /* SSI上报 */
    UPHY_TOOL_MIPI_READ_RPT_IND_STRU    stMipiReportInd;                        /* MIPI上报 */
}WPHY_TOOL_SSI_MIPI_READ_FUNCTION_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_MEM_INFO_STRU
 结构说明  : PHY 内部消息上报控制请求
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  uwAddr;                         /* 内存地址 */
    VOS_UINT32                                  uwValue;                        /* 内存地址的值 */
}WPHY_TOOL_MEM_INFO_STRU;


/*****************************************************************************
 结构名    : WPHY_TOOL_READ_MEM_REQ_STRU
 结构说明  : TOOL给物理层下发的读取内存请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    WPHY_TOOL_MNTN_BOOL_ENUM_UINT16             enEnableFlag;                   /* 使能标记，0表示去使能，1表示使能 */
    VOS_UINT16                                  usReadPeriod;                   /* 回读周期，单位为10ms */
    VOS_UINT16                                  usAddrNum;                      /* 地址数目 */
    VOS_UINT16                                  usReserved;
    VOS_UINT32                                  auwAddrList[WPHY_MNTN_READ_ADDR_MAX_NUM];  /* 内存地址列表 */
}WPHY_TOOL_READ_MEM_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_TOOL_READ_MEM_IND_STRU
 结构说明  : PHY 内部消息上报内存信息
*****************************************************************************/
typedef struct
{

    WPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usAddrNum;                      /* 地址数目 */
    VOS_UINT16                                  usReserved;
    WPHY_TOOL_MEM_INFO_STRU                     astAddrList[WPHY_MNTN_READ_ADDR_MAX_NUM];  /* 内存地址列表 */
}WPHY_TOOL_READ_MEM_IND_STRU;

/*****************************************************************************
 结构名    : GPHY_TOOL_MEM_INFO_STRU
 结构说明  : PHY 内部消息上报信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  uwAddr;                         /* 内存地址 */
    VOS_UINT32                                  uwValue;                        /* 内存地址的值 */
}GPHY_TOOL_MEM_INFO_STRU;


/*****************************************************************************
 结构名    : GPHY_TOOL_READ_MEM_REQ_STRU
 结构说明  : TOOL给物理层下发的读取内存请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  uhwCommand;                     /* 命令。0:停止，1：启动 */
    VOS_UINT16                                  usReadPeriod;                   /* 回读周期，单位为10ms */
    VOS_UINT16                                  usAddrNum;                      /* 地址数目 */
    VOS_UINT16                                  usReserved;
    VOS_UINT32                                  auwAddrList[GPHY_MNTN_READ_ADDR_MAX_NUM];  /* 内存地址列表 */
}GPHY_TOOL_READ_MEM_REQ_STRU;


/*****************************************************************************
 结构名    : GPHY_TOOL_READ_MEM_IND_STRU
 结构说明  : PHY 内部消息上报内存信息
*****************************************************************************/
typedef struct
{

    GPHY_TOOL_MNTN_MSG_ID_ENUM_UINT16           enMsgId;                        /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                                  usToolsId;                      /* 保留字段 */
    VOS_UINT16                                  usAddrNum;                      /* 地址数目 */
    VOS_UINT16                                  usReserved;
    GPHY_TOOL_MEM_INFO_STRU                     astAddrList[GPHY_MNTN_READ_ADDR_MAX_NUM];  /* 内存地址列表 */
}GPHY_TOOL_READ_MEM_IND_STRU;


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
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

#endif /* end of phytoolinterface.h */
