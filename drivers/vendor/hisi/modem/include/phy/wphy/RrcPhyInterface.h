/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : RrcPhyInterface.h
  版 本 号   : 初稿
  作    者   : chengong
  生成日期   : 2006年08月29日
  最近修改   : 按照新的编程规范制定Hi4131的物理层接口数据结构
               并加入HSDPA/HSUPA 的数据结构
  功能描述   : RrcPhyInterface.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2006年10月31日
    作    者   : Jinying
    修改内容   : 创建文件

******************************************************************************/

#ifndef __RRCPHYINTERFACE_H__
#define __RRCPHYINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "Hi_Config.h"
#include "product_config.h"
#include "wasphycomminterface.h"
#include "WUeSpec.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/**************一些功能支持开关********************/
#define RRC_PHY_CBS_SWITCH                      (FEATURE_WCBS)     /*开关为1表示支持,为0表示不支持*/

/*************物理信道相关的宏*********************/

/*6720最大支持的物理信道数*/
#define  RRC_PHY_MAX_PHYCHAN_NUM                (10)     /*nDLDPCH(FDPCH)+1ULDPCH(ULDPCCH)+1HSDPA+1 UL HSUPA + 1 DL HSUPA，n=6为活动集中最大的链路数*/

/*6720最大支持的RL 数目*/
#define  RRC_PHY_MAX_RL_NUM                     (6)

/* 测量停止门限最小值 */
#define  RRC_PHY_MEAS_STOP_TRESH_MIN            (0)

/* 测量停止门限最大值 */
#define  RRC_PHY_MEAS_STOP_TRESH_MAX            (20)

#define  RRC_PHY_MAX_SLOT_PLUS1_NUM             (16)


/*物理信道多码个数*/
#define  RRC_PHY_MAX_DLDPCH_CHAN_NUM            (1)

#define  RRC_PHY_MAX_SIGNATURE_NUM              (16)

#define  RRC_PHY_MAX_SUBCHANNEL_NUM             (12)

#define  RRC_PHY_MAX_ASC_NUM                    (8)

/**************码组合传输信道相关的宏***************/

#define  RRC_PHY_MAX_TRCH_NUM                   (8)

#define  RRC_PHY_CCTRCH_NUM                     (1)     /*要配置的最大的码组合传输信道数，HSDPA和HSUPA不需要配置码组合传输信道*/

#define  RRC_PHY_CCTRCH_PARA_LEN                (4096)  /*CCTRCH 信道参数的长度*/

#define  RRC_PHY_MAX_AMR_TRCH_NUM               (3)     /*AMR子流最大个数，用于映射关系配置 */

/*************小区选择重选和测量相关的宏************/
#define  RRC_PHY_MAX_CANDIDATE_SRCD             (8)     /*这个值不知道做什么使用，没有见到引用的地方*/

#define  RRC_PHY_MAX_ADDITIONAL_CARRIER_NUM     (2)     /* Used Freq频点除外，支持的最多异频数 */


#define  RRC_PHY_MAX_EACH_FREQ_CELL_NUM         (64)    /*异频测量请求，每个载频携带的最多小区个数*/

#define  RRC_PHY_MAX_INTRA_FREQ_CELL_NUM        (64)    /*同频测量请求，携带的最多小区个数*/

#define  RRC_PHY_MAX_INTER_FREQ_CELL_NUM        (64)    /*异频测量结果中，携带的最多小区个数*/
#define RRC_PHY_MAX_INTER_RAT_LTE_FREQ           (8)    /* W下测量LTE频点个数 */
#define RRC_PHY_MAX_SLAVE_WCDMA_CARRIER_NUM      (3)    /* w为从模时，WCDMA的频点个数 */

#define RRC_PHY_MAX_SLAVE_WCDMA_CELL_PER_FREQ_NUM (32)


#define  RRC_PHY_MAX_POS_CELL_NUM               (64)   /*定位要测量的最大小区数*/

#define  RRC_PHY_MAX_SEC_UL_FREQ_CELL_NUM       (32)    /*本频测量需要测量Second UL Freq的最多小区个数*/

#define  RRC_PHY_MAX_ADJACENT_FREQ_CELL_NUM     (RRC_PHY_MAX_SEC_UL_FREQ_CELL_NUM+RRC_PHY_MAX_INTER_FREQ_CELL_NUM)    /*邻频测量请求，携带的最多小区个数*/

#define  PHY_RRC_MAX_REPORT_EACH_FREQ_CELL_NUM         (32) /*异频测量上报时，携带的每个载频的最多小区个数*/

#define  PHY_RRC_MAX_REPORT_INTRA_FREQ_CELL_NUM        (32) /*同频测量上报时，携带的最多小区个数*/

#define  PHY_RRC_MAX_REPORT_SEC_UL_FREQ_CELL_NUM       (32) /*同频测量上报时，携带的Second UL Freq小区最多个数*/

/**************小区搜有相关的宏***********************/

#define  RRC_PHY_FREQ_BAND_MAX_NUM              (6)    /*搜索的最大频段数为6个,和UE支持的频段数保持一致*/

#define  RRC_PHY_MAX_RSSI_FREQ_GROUP_NUM        (10)    /*初始搜上报的最大的频点组数*/

#define  RRC_PHY_MAX_RSSI_FREQ_RPT_NUM          (8)    /*初始搜上报的每组最大的频点个数*/

#define  RRC_PHY_RSSI_Threshold                 (-960)  /* 初始搜 RSSI门限，物理层对于某频点RSSI测量值小于该门限的不上报*/

#define RRC_PHY_HISTORY_FREQS_MAX_NUM           (6)

#define  RRC_PHY_BG_SEARCH_Threshold_Invalid    (0x7FFF)
/**************压缩模式相关的宏***********************/
#define  RRC_PHY_MAX_TGPS                       (6)


/**************HSDPA相关的宏***************************/
#define  RRC_PHY_MAX_HSSCCH_NUM                 (4)     /*最大的HSSCCH数为4个*/
#define  RRC_PHY_MAX_HSDPA_PROCESSES            (16)    /*最大的HSDPA进程数为 16个*/
#define  RRC_PHY_MAX_QUEUE_NUM                  (8)     /*最大的HSDPA队列数为8个*/
#define  RRC_PHY_MAX_MAC_D_PDU_SIZES_NUM        (8)     /*最大的HSDPA Mad_D PDU Size数为8个*/

/**************HSUPA相关的宏***************************/
#define  RRC_PHY_MAX_EDCH_REFTFCI_NUM           (8)     /*最大的EDCH_参考TFCI数为8个*/
#define  RRC_PHY_MAC_EDCH_MAX_MACD_FLOW_NUM     (8)     /*最大的EDCH MAC_d流数目为8个*/
#define  RRC_PHY_MAX_RLC_PDU_SIZE_NUM_PER_LOCH  (32)    /*每个逻辑信道可以配置的最大的RLC PDU数目*/

#define  RRC_PHY_ACTIVE_NOW                     (-1)    /*立即激活*/


/**************CBS相关的宏****************************/
#define  RRC_PHY_MAX_DRXBS_OFFSETLSTLEN         (255)

/********************支持的打印寄存器的最大数目***************/
#define  RRC_PHY_MAX_RTT_REG_NUM                (32)


/* 一个频带最多有的频点个数 */
#define  RRC_PHY_MAX_FREQ_NUM_PER_BAND          (292)    /*RSSI搜上报的每个BAND最大的频点个数*/

/*V3 R7_7C1 Start */
/* UE支持最大逻辑信道个数 */
#define  RRC_PHY_MAX_LOCH_NUM                   (16)
/* V3 R7_7C1 End */

#define RR_PHY_MAX_MSG_SIZE                     (230)
#define PHY_RR_MAX_MSG_SIZE                     (80)


#define RRC_PHY_MAX_TB_SIZE_NUM                 (2)
#define RRC_PHY_MAX_HSSCCH_LESS_TB_NUM          (4)

#define RRC_PHY_INVALID_MSG_OPID                        (0XFFFF)
#define PHYITF_EDCH_TRANS_CONTINU_BACK_OFF_INFINITY     (0XFFFF)

/* 设置需要释放的测量类型的MASK */
#define RRC_PHY_REL_MEAS_TYPE_INTRA_FREQ                      0x0001
#define RRC_PHY_REL_MEAS_TYPE_INTER_FREQ                      0x0002
#define RRC_PHY_REL_MEAS_TYPE_INTER_RAT_GSM                   0x0004
#define RRC_PHY_REL_MEAS_TYPE_INTER_RAT_LTE                   0x0008
#define RRC_PHY_REL_MEAS_TYPE_ALL                             0x0040


/*****************************************************************************
  6 消息定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : PHYITF_IDLE_MEAS_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : IDLE态测量请求类型枚举
*****************************************************************************/
enum    PHYITF_IDLE_MEAS_TYPE_ENUM
{
    PHYITF_IDLE_MEAS_TYPE_INTRA_FREQ      = 0,    /* 同频测量信息 */    /* _H2ASN_MsgChoice PHYITF_INTRA_FREQ_CELL_INFO_STRU */
    PHYITF_IDLE_MEAS_TYPE_INTER_FREQ      = 1,    /* 异频测量信息 */    /* _H2ASN_MsgChoice PHYITF_INTER_FREQ_CELL_INFO_STRU */
    PHYITF_IDLE_MEAS_TYPE_INTER_RAT       = 2,    /* 异系统GSM测量信息 */  /* _H2ASN_MsgChoice PHYITF_INTER_RAT_CELL_INFO_STRU */
    PHYITF_IDLE_MEAS_TYPE_INTER_RAT_LTE   = 3,    /* 异系统LTE测量信息 */  /* _H2ASN_MsgChoice PHYITF_INTER_RAT_LTE_CELL_INFO_STRU */
    PHYITF_IDLE_MEAS_TYPE_BUTT

};
typedef VOS_UINT16  PHYITF_IDLE_MEAS_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_CONN_MEAS_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : CONN态测量请求类型枚举
*****************************************************************************/
enum    PHYITF_CONN_MEAS_TYPE_ENUM
{
    PHYITF_CONN_MEAS_TYPE_INTRA_FREQ      = 0,    /* 同频测量信息 */    /* _H2ASN_MsgChoice PHYITF_INTRA_FREQ_CELL_INFO_STRU */
    PHYITF_CONN_MEAS_TYPE_INTER_FREQ      = 1,    /* 异频测量信息 */    /* _H2ASN_MsgChoice PHYITF_INTER_FREQ_CELL_INFO_STRU */
    PHYITF_CONN_MEAS_TYPE_INTER_RAT       = 2,    /* 异系统GSM测量信息 */  /* _H2ASN_MsgChoice PHYITF_INTER_RAT_CELL_INFO_STRU */
    PHYITF_CONN_MEAS_TYPE_INTER_RAT_LTE   = 3,    /* 异系统LTE测量信息 */  /* _H2ASN_MsgChoice PHYITF_INTER_RAT_LTE_CELL_INFO_STRU*/
    PHYITF_CONN_MEAS_TYPE_BUTT

};
typedef VOS_UINT16  PHYITF_CONN_MEAS_TYPE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHYITF_IDLE_MEAS_REQ_END_FLAG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 测量请求结束标志枚举
*****************************************************************************/
enum    PHYITF_MEAS_REQ_END_FLAG_ENUM
{
    PHYITF_MEAS_REQ_END_FLAG_FALSE = 0,    /* IDLE态测量请求结束枚举，0－表示未结束 */ /* _H2ASN_MsgChoice RRC_PHY_IDLE_MEASURE_REQ_STRU */
    PHYITF_MEAS_REQ_END_FLAG_TRUE  = 1,    /* IDLE态测量请求结束枚举，1－表示结束 */   /* _H2ASN_MsgChoice RRC_PHY_IDLE_MEASURE_REQ_STRU */
    PHYITF_MEAS_REQ_END_FLAG_BUTT
};

typedef VOS_UINT16  PHYITF_MEAS_REQ_END_FLAG_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHYITF_PHYCH_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 物理信道类型枚举
*****************************************************************************/

enum    PHYITF_PHYCH_TYPE_ENUM
{

    PHYITF_PHY_NONE                     = 0,
    PHYITF_PHY_SCCPCH                   = 1,                /* _H2ASN_MsgChoice PHYITF_SCCPCH_PARA_STRU */
    PHYITF_PHY_DLDPCH                   = 2,                /* _H2ASN_MsgChoice PHYITF_DOWNLINK_DPCH_PARA_STRU */
    PHYITF_PHY_PICH                     = 4,                /* _H2ASN_MsgChoice PHYITF_PICH_STRU */
    PHYITF_PHY_AICH                     = 5,                /* _H2ASN_MsgChoice PHYITF_AICH_STRU */
    PHYITF_PHY_PRACH                    = 20,               /* _H2ASN_MsgChoice PHYITF_PRACH_STRU */
    PHYITF_PHY_ULDPCH                   = 22,               /* _H2ASN_MsgChoice PHYITF_UPLINK_DPCH_STRU */
    PHYITF_PHY_HSDPA                    = 32,               /* _H2ASN_MsgChoice PHYITF_HSDPA_PHY_STRU */
    PHYITF_PHY_UL_HSUPA                 = 64,               /* _H2ASN_MsgChoice PHYITF_UL_HSUPA_PHY_STRU */
    PHYITF_PHY_DL_HSUPA                 = 128,              /* _H2ASN_MsgChoice PHYITF_DL_HSUPA_PHY_STRU */
    PHYITF_PHY_FDPCH                    = 256,              /* _H2ASN_MsgChoice PHYITF_DOWNLINK_FDPCH_PARA_STRU */
/*V3 R7_7C1 Start */
    PHYITF_PHY_HSDPAPLUS                = 512,              /* _H2ASN_MsgChoice PHYITF_HSDPAPLUS_PHY_STRU */
/* V3 R7_7C1 End */

    PHYITF_PHY_FACH_HSDPAPLUS           = 513,              /* _H2ASN_MsgChoice PHYITF_FACH_HSDPAPLUS_PHY_STRU */
    PHYITF_PHY_SCND_HSDPAPLUS           = 514,              /* _H2ASN_MsgChoice PHYITF_SCND_HSDPAPLUS_PHY_STRU */
    PHYITF_PHY_SCND_UL_HSUPA            = 515,              /* _H2ASN_MsgChoice PHYITF_SCND_UL_HSUPA_PHY_STRU */
    PHYITF_PHY_SCND_DL_HSUPA            = 516,              /* _H2ASN_MsgChoice PHYITF_SCND_DL_HSUPA_PHY_STRU */
    PHYITF_PHY_SCND_FDPCH               = 517,              /* _H2ASN_MsgChoice PHYITF_SCND_DL_FDPCH_PARA_STRU */
    PHYITF_PHY_E_RACH                   = 518,             /* _H2ASN_MsgChoice PHYITF_E_RACH_REQ_STRU */
    PHYITF_PHY_BUTT

};
typedef VOS_UINT16 PHYITF_PHYCH_TYPE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHYITF_CCTRCH_ID_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : CCTRCH 信道ID
*****************************************************************************/

enum    PHYITF_CCTRCH_ID_ENUM
{

    PHYITF_CCTRCH_PCCPCH                = 0,    /*实际不需要RRC配置PCCPCH码组合传输信道参数，但因为PHY和MAC接口中有此参数，此处表明该值已被PCCPCH占用*/
    PHYITF_CCTRCH_SCCPCH                = 1,    /* _H2ASN_MsgChoice PHYITF_DL_CCTRCH_STRU */
    PHYITF_CCTRCH_DLDPCH                = 2,    /* _H2ASN_MsgChoice PHYITF_DL_CCTRCH_STRU */
    PHYITF_CCTRCH_PRACH                 = 3,    /* _H2ASN_MsgChoice PHYITF_UL_CCTRCH_STRU */
    PHYITF_CCTRCH_ULDPCH                = 4,    /* _H2ASN_MsgChoice PHYITF_UL_CCTRCH_STRU */
    PHYITF_CCTRCH_HSDPA                 = 6,    /*实际不需要RRC配置HSDPA码组合传输信道参数，但因为PHY和MAC接口中有此参数，此处表明该值已被HSDPA 占用*/
    PHYITF_CCTRCH_HSUPA                 = 7,    /*实际不需要RRC配置HSUPA码组合传输信道参数，但因为PHY和MAC接口中有此参数，此处表明该值已被HSUPA 占用*/

    PHYITF_CCTRCH_ALL                   = 255,  /*在释放所有传输信道时使用*/

    PHYITF_CCTRCH_BUTT

};
typedef VOS_UINT16 PHYITF_CCTRCH_ID_ENUM_UINT16;



/*****************************************************************************
 枚举名    : PHYITF_TIMING_INDIACTION_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : HHO 定时指示信息
*****************************************************************************/

enum    PHYITF_TIMING_INDIACTION_ENUM
{
    PHYITF_TIME_INITIALISE              = 0,    /* 标识硬切换，定时方式为初始化 */
    PHYITF_TIME_MAINTAIN                = 1,    /* 标识硬切换，定时方式为维持 */
    PHYITF_TIME_INITIAL_RESUME          = 2,    /* 标识硬切换失败，恢复定时初始化 */
    PHYITF_TIME_MAINTAIN_RESUME         = 3,    /* 标识硬切换失败，恢复定时维持 */
    PHYITF_TIME_INVALID_MAINTAIN        = 4,    /* 标识非硬切换*/
    PHYITF_TIME_INTERRAT_RESUME         = 5,    /* 异系统切换回退 */

    PHYITF_TIME_BUTT

};
typedef VOS_UINT16 PHYITF_TIMING_INDIACTION_ENUM_UINT16;



/*****************************************************************************
 枚举名    : PHYITF_CELL_ADJUGE_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : PHYITF_CELL_ADJUGE_PARA_INFO_STRU中的小区类型
*****************************************************************************/

enum    PHYITF_CELL_ADJUGE_TYPE_ENUM
{
    PHYITF_CELL_NO_HCS_TYPE     = 0,            /*非HCS小区*/
    PHYITF_CELL_HCS_TYPE        = 1,            /*HCS小区*/

    PHYITF_CELL_ADJUGE_TYPE_BUTT

};
typedef VOS_UINT16 PHYITF_CELL_ADJUGE_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_SERVE_CELL_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 服务小区状态
*****************************************************************************/

enum    PHYITF_SERVE_CELL_STATUS_ENUM
{
    PHYITF_SERV_CELL_NOT_BAR    = 0,
    PHYITF_SERV_CELL_BAR        = 1,

    PHYITF_SERV_CELL_STATUS_BUTT
};
typedef VOS_UINT16 PHYITF_SERVE_CELL_STATUS_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHYITF_CELL_SEARCH_FLAG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 小区选择标志
*****************************************************************************/

enum    PHYITF_CELL_SEARCH_FLAG_ENUM
{
    PHYITF_CELL_SEARCH_FLAG_ABSENT   = 0,
    PHYITF_CELL_SEARCH_FLAG_PRESENT  = 1,
    PHYITF_CELL_SEARCH_FLAG_INVALID  = 2,

    PHYITF_CELL_SEARCH_FLAG_BUTT
};
typedef VOS_UINT16 PHYITF_CELL_SEARCH_FLAG_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHYITF_MEAS_QUANTITY_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 小区选择标志
*****************************************************************************/

enum    PHYITF_MEAS_QUANTITY_ENUM
{
    PHYITF_MEAS_QUANTITY_RSCP        = 0,
    PHYITF_MEAS_QUANTITY_ECN0        = 1,

    PHYITF_MEAS_QUANTITY_BUTT
};
typedef VOS_UINT16 PHYITF_MEAS_QUANTITY_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHYITF_E_DPDCH_MAX_CHLS_CODES_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : HSUPA 的SF和码个数
*****************************************************************************/

enum    PHYITF_E_DPDCH_MAX_CHLS_CODES_ENUM
{
    PHYITF_E_DPDCH_MAX_CHLS_CODES_SF256             = 0,
    PHYITF_E_DPDCH_MAX_CHLS_CODES_SF128             = 1,
    PHYITF_E_DPDCH_MAX_CHLS_CODES_SF64              = 2,
    PHYITF_E_DPDCH_MAX_CHLS_CODES_SF32              = 3,
    PHYITF_E_DPDCH_MAX_CHLS_CODES_SF16              = 4,
    PHYITF_E_DPDCH_MAX_CHLS_CODES_SF8               = 5,
    PHYITF_E_DPDCH_MAX_CHLS_CODES_SF4               = 6,
    PHYITF_E_DPDCH_MAX_CHLS_CODES_SF4X2             = 7,
    PHYITF_E_DPDCH_MAX_CHLS_CODES_SF2X2             = 8,
    PHYITF_E_DPDCH_MAX_CHLS_CODES_SF4X2_AND_SF2X2   = 9,

    PHYITF_E_DPDCH_MAX_CHLS_CODES_SF_BUTT

};
typedef VOS_UINT16 PHYITF_E_DPDCH_MAX_CHLS_CODES_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHYITF_RVVERSION_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : HSUPA 的RV 版本
*****************************************************************************/

enum    PHYITF_RVVERSION_ENUM
{
    PHYITF_RVVERSION_RV0                = 0,
    PHYITF_RVVERSION_RVTABLE            = 1,

    PHYITF_RVVERSION_BUTT

};
typedef VOS_UINT16 PHYITF_RVVERSION_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHYITF_EDCH_TTI_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : HSUPA 的EDCH TTI
*****************************************************************************/

enum    PHYITF_EDCH_TTI_ENUM
{
    PHYITF_EDCH_TTI_10MS                = 0,
    PHYITF_EDCH_TTI_2MS                 = 1,

    PHYITF_EDCH_TTI_BUTT

};
typedef VOS_UINT16 PHYITF_EDCH_TTI_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_FACH_OCCASION_MEAS_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : FACH 测量时机类型
*****************************************************************************/

enum    PHYITF_FACH_OCCASION_MEAS_TYPE_ENUM
{
    PHYITF_FACH_OCCASION_MEAS_INTER_FREQ         = 0,

    PHYITF_FACH_OCCASION_MEAS_INTER_RAT          = 1,

    PHYITF_FACH_OCCASION_MEAS_INTER_FREQANDRAT   = 2,

    PHYITF_FACH_OCCASION_MEAS_BUTT

};
typedef VOS_UINT16 PHYITF_FACH_OCCASION_MEAS_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_E_CELLFACH_MEAS_PERIOD_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : E CELL_FACH 测量周期类型
*****************************************************************************/
enum    PHYITF_E_CELLFACH_MEAS_PERIOD_TYPE_ENUM
{
    PHYITF_E_CELLFACH_DRX_STATUS            = 0,                                /* CELL_FACH状态支持DRX,填写该值，对应结构PHYITF_E_CELLFACH_DRX_INFO_STRU */
    PHYITF_E_CELLFACH_OCCATION_STAUS        = 1,                                /* CELL_FACH状态下不支持DRX情况，填写该值,对应结构PHYITF_E_CELLFACH_MEAS_PARA_STRU */
    PHYITF_E_CELLFACH_MEAS_INVALID          = 2,                                /* 非CELL_FACH状态下填写该值 */
    PHYITF_E_CELLFACH_MEAS_PERIOD_TYPE_BUTT
};
typedef VOS_UINT16 PHYITF_E_CELLFACH_MEAS_PERIOD_TYPE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHYITF_SCRAMBLE_CODE_CHANGE_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 下行扰码改变标识
*****************************************************************************/

enum    PHYITF_SCRAMBLE_CODE_CHANGE_TYPE_ENUM
{
    PHYITF_SCRAMBLE_CODE_CHANGE            = 0,
    PHYITF_SCRAMBLE_CODE_NO_CHANGE         = 1,
    PHYITF_SCRAMBLE_CODE_CHANGE_INVALID    = 2,

    PHYITF_SCRAMBLE_CODE_CHANGE_TYPE_BUTT

};
typedef VOS_UINT16 PHYITF_SCRAMBLE_CODE_CHANGE_TYPE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHYITF_SCRAMBL_CODE_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 : ScramblingCodeType
 枚举说明  : 扰码类型
*****************************************************************************/
enum    PHYITF_SCRAMBL_CODE_TYPE_ENUM
{
    PHYITF_SHORT_SCRAMBL_CODE              = 0,
    PHYITF_LONG_SCRAMBL_CODE               = 1,
    PHYITF_SCRAMBL_CODE_TYPE_BUTT

} ;
typedef VOS_UINT16 PHYITF_SCRAMBL_CODE_TYPE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHYITF_UL_DPCH_PWRCTRL_ALGO_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 上行功控的算法
*****************************************************************************/
enum    PHYITF_UL_DPCH_PWRCTRL_ALGO_ENUM
{
    PHYITF_UL_DPCH_PWRCTRL_ALGOR1       = 1,
    PHYITF_UL_DPCH_PWRCTRL_ALGOR2       = 2,

    PHYITF_UL_DPCH_PWRCTRL_ALGOR_BUTT

} ;
typedef VOS_UINT16 PHYITF_UL_DPCH_PWRCTRL_ALGO_UINT16;


/*****************************************************************************
 枚举名    : PHYITF_DPC_MODE_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 下行功控 DPC Mode Type
*****************************************************************************/
enum    PHYITF_DPC_MODE_TYPE_ENUM
{
    PHYITF_DPC_MODE_SINGLE              = 1,
    PHYITF_DPC_MODE_TRIPLET             = 2,

    PHYITF_DPC_MODE_TYPE_BUTT

} ;
typedef VOS_UINT16 PHYITF_DPC_MODE_TYPE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHYITF_SCCPCH_DEMODULATE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : SCCPCH 解调指示
*****************************************************************************/

enum    PHYITF_SCCPCH_DEMODULATE_ENUM
{
    PHYITF_SCCPCH_NO_PICH               = 0 ,            /* 在激活时间规定的时刻启动SCCPCH解调 */
    PHYITF_SCCPCH_WITH_PICH             = 1 ,            /* 在有PI后启动SCCPCH解调 */

    PHYITF_SCCPCH_DEMODULATE_BUTT

};

typedef VOS_UINT16 PHYITF_SCCPCH_DEMODULATE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHYITF_COMPRS_MODE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 压缩模式。
             在R6的协议中已经删除了打孔方式，
             只有扩频因子减半和高层调度。
             6720芯片已经没有了打孔配置，
             而6511可以支持。
             所以若网络侧下发了打孔配置，而物理层
             不支持，则物理层要返回配置失败

*****************************************************************************/
enum    PHYITF_COMPRS_MODE_ENUM
{
    PHYITF_COMPRS_MODE_DUMMY                = 0,
    PHYITF_COMPRS_MODE_SF2                  = 1,
    PHYITF_COMPRS_MODE_HIGHER_LAYER_SCHEDUL = 2,

    PHYITF_COMPRS_MODE_BUTT

} ;

typedef VOS_UINT16 PHYITF_COMPRS_MODE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHYITF_QUA_MEAS_RPT_CRTR_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 质量测量的标准

*****************************************************************************/
enum    PHYITF_QUA_MEAS_RPT_CRTR_ENUM
{
    PHYITF_QUA_PERIODIC_REPORT                  = 0,    /* _H2ASN_MsgChoice PHYITF_QUA_PERIODIC_CRITERIA_STRU */
    PHYITF_QUA_EVENT_REPORT                     = 1,    /* _H2ASN_MsgChoice PHYITF_QUA_EVENT_CRITERIA_STRU */
    PHYITF_QUA_PERIODIC_AND_EVENT_REPORT        = 2,    /* 只用于RRC需要同时释放所有的质量测量 */

    PHYITF_QUA_REPORT_BUTT
};

typedef VOS_UINT16 PHYITF_QUA_MEAS_RPT_CRTR_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_QUA_MEAS_RPT_IND_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 质量测量的测量报告结构

*****************************************************************************/
enum    PHYITF_QUA_MEAS_RPT_IND_ENUM
{
    PHYITF_QUA_PERIODIC_RPT_IND              = 0,       /* _H2ASN_MsgChoice PHYITF_QUALITY_PERIO_REPORT_STRU */
    PHYITF_QUA_EVENT_RPT_IND                 = 1,       /* _H2ASN_MsgChoice PHYITF_QUALITY_EVENT_REPORT_STRU */

    PHYITF_QUA_RPT_IND_BUTT
};

typedef VOS_UINT16 PHYITF_QUA_MEAS_RPT_IND_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_MAC_E_SCHED_GRANT_INFO_CHOSEN_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 质量测量的测量报告结构

*****************************************************************************/
enum    PHYITF_MAC_E_SCHED_GRANT_INFO_CHOSEN_ENUM
{
    PHYITF_MAC_E_NON_SCHED_GRANT_INFO_CHOSEN              = 0,       /* _H2ASN_MsgChoice PHYITF_MAC_E_NON_SCHED_GRANT_STRU */
    PHYITF_MAC_E_SCHED_GRANT_INFO_CHOSEN                  = 1,       /* _H2ASN_MsgChoice VOS_UINT32 */

    PHYITF_MAC_E_SCHED_GRANT_INFO_CHOSEN_BUTT
};

typedef VOS_UINT16 PHYITF_MAC_E_SCHED_GRANT_INFO_CHOSEN_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_CHANNEL_CONFIG_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 信道配置结果指示

*****************************************************************************/
enum    PHYITF_CHANNEL_CONFIG_RESULT_ENUM
{
    PHYITF_CHANNEL_CONFIG_SUCCESS               = 0,     /*信道配置成功，包括建立、重配置、释放*/
    PHYITF_CHANNEL_SETUP_OVERLAP_ERROR          = 1,     /*信道被重复建立*/
    PHYITF_CHANNEL_SETUP_STATE_ERROR            = 2,     /*所建信道和当前系统状态不一致*/
    PHYITF_CHANNEL_MODIFY_WITHOUT_CHANNEL_ERROR = 3,     /*在信道重配置时，该信道不存在*/
    PHYITF_CHANNEL_CONFIG_PARA_ERROR            = 4,     /*信道参数错误*/
    PHYITF_CHANNEL_CONFIG_ERROR                 = 5,     /*信道配置失败*/

    PHYITF_CHANNEL_CONFIG_BUTT
};
typedef VOS_UINT16 PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_DPCH_COMPRESSED_MODE_STATUS_CHANGE_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 压缩模式改变结果指示
*****************************************************************************/
enum    PHYITF_DPCH_COMPRESSED_MODE_STATUS_CHANGE_RESULT_ENUM
{

    PHYITF_DPCH_COMPRESSED_MODE_STATUS_CHANGE_SUCC  = 0,  /*压模状态改变成功*/
    PHYITF_DPCH_COMPRESSED_MODE_STATUS_CHANGE_ERROR = 1,  /*压模状态改变失败*/

    PHYITF_DPCH_COMPRESSED_MODE_STATUS_CHANGE_BUTT

};
typedef VOS_UINT16 PHYITF_DPCH_COMPRESSED_MODE_STATUS_CHANGE_RESULT_ENUM_UINT16;



/*****************************************************************************
 枚举名    : PHYITF_CAMPED_MAINCELL_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 主小区驻留结果

*****************************************************************************/
enum    PHYITF_CAMPED_MAINCELL_RESULT_ENUM
{
    PHYITF_CAMPED_MAINCELL_SUCCESS              = 0,     /*主小区驻留成功*/
    PHYITF_CAMPED_MAINCELL_FAIL                 = 1,     /*主小区驻留失败*/

    PHYITF_CAMPED_MAINCELL_BUTT

};
typedef VOS_UINT16 PHYITF_CAMPED_MAINCELL_RESULT_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_CONNECT_MEAS_REQ_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 连接状态测量请求消息类型
*****************************************************************************/
enum PHYITF_CONNECT_MEAS_REQ_TYPE_ENUM
{
    PHYITF_CONNECT_MEAS_REQ_INTRA_CELL      = 41,                               /* _H2ASN_MsgChoice PHYITF_INTRA_FREQ_MEASURE_STRU */
    PHYITF_CONNECT_MEAS_REQ_INTER_CELL      = 42,                               /* _H2ASN_MsgChoice PHYITF_INTER_FREQ_MEASURE_STRU */
    PHYITF_CONNECT_MEAS_REQ_INTERNAL        = 43,                               /* _H2ASN_MsgChoice VOS_UINT16 */
    PHYITF_CONNECT_MEAS_REQ_CELLSEL         = 44,                               /* _H2ASN_MsgChoice PHYITF_CELL_SEL_MEASURE_STRU */
    PHYITF_CONNECT_MEAS_REQ_INTERRAT        = 45,
    PHYITF_CONNECT_MEAS_REQ_ADJACENTFREQ    = 46,                               /* _H2ASN_MsgChoice PHYITF_ADJACENT_FREQ_MEASURE_STRU */
    PHYITF_CONNECT_MEAS_REQ_INTER_RAT_LTE   = 47,                               /* _H2ASN_MsgChoice PHYITF_INTER_RAT_LTE_CELL_INFO_STRU */
    PHYITF_CONNECT_MEAS_REQ_TYPE_BUTT
};
typedef VOS_UINT16  PHYITF_CONNECT_MEAS_REQ_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_CONNECT_MEAS_IND_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 连接状态测量上报类型
*****************************************************************************/
enum PHYITF_CONNECT_MEAS_IND_TYPE_ENUM
{
    PHYITF_CONNECT_MEAS_IND_INTRA_CELL          = 51,           /* _H2ASN_MsgChoice PHYITF_INTRA_FREQ_REPORT_STRU */
    PHYITF_CONNECT_MEAS_IND_INTER_CELL          = 52,           /* _H2ASN_MsgChoice PHYITF_INTER_FREQ_REPORT_STRU */
    PHYITF_CONNECT_MEAS_IND_CELLSEL             = 54,           /* _H2ASN_MsgChoice PHYITF_CELL_SEL_REPORT_STRU   */
    PHYITF_CONNECT_MEAS_IND_TYPE_BUTT
};
typedef VOS_UINT16  PHYITF_CONNECT_MEAS_IND_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_MEASURE_COMMAND_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 测量命令类型
*****************************************************************************/
enum PHYITF_MEASURE_COMMAND_ENUM
{
    PHYITF_MEASURE_COMMAND_RELEASE          = 0,            /*测量释放*/
    PHYITF_MEASURE_COMMAND_SETUP            = 1,            /*测量建立和重配都用此命令,兼容2000*/
    PHYITF_MEASURE_COMMAND_MODIFY           = 2,            /*测量重配*/

    PHYITF_MEASURE_COMMAND_BUTT
};
typedef  VOS_UINT16 PHYITF_MEASURE_COMMAND_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_MODIFY_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 测量命令类型
*****************************************************************************/
enum PHYITF_MODIFY_TYPE_ENUM
{
    PHYITF_MEASURE_MODIFY_ALL                   = 0,            /*测量重配置测量列表和测量参数*/
    PHYITF_MEASURE_MODIFY_ONLY_MEAS_PARA        = 1,            /*仅重配测量参数*/

    PHYITF_MEASURE_MODIFY_BUTT
};
typedef  VOS_UINT16 PHYITF_MODIFY_TYPE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHYITF_64QAM_CONFIGURED_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 64QAM配置
*****************************************************************************/
enum PHYITF_64QAM_CONFIGURED_ENUM
{
    PHYITF_64QAM_CONFIGURED_NOT_PRESENT          = 0,            /* 64QAM不可用 */
    PHYITF_64QAM_CONFIGURED_PRESENT              = 1,            /* 64QAM可用 */

    PHYITF_64QAM_CONFIGURED_BUTT
};
typedef VOS_UINT16 PHYITF_64QAM_CONFIGURED_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_DL_SCND_CELL_INFO_CFG_INFO_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum  PHYITF_DL_SCND_CELL_INFO_CFG_INFO_ENUM
{
    PHYITF_DL_SCND_CELL_INFO_CFG_INFO_CONTINUE = 0,
    PHYITF_DL_SCND_CELL_INFO_CFG_INFO_NEW_CFG,
    PHYITF_DL_SCND_CELL_INFO_CFG_INFO_BUTT
};
typedef VOS_UINT16 PHYITF_DL_SCND_CELL_INFO_CFG_INFO_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHYITF_MAC_RPT_MODE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 配置BBP解析mac 头的模式
*****************************************************************************/
enum PHYITF_MAC_RPT_MODE_ENUM
{
    PHYITF_MAC_RPT_MODE_NO_MAC_HEADER          = 0,            /* BBP不解析mac头 */
    PHYITF_MAC_RPT_MODE_MAC_HS_HEADER          = 1,            /* BBP按照mac hs解析mac头 */
    PHYITF_MAC_RPT_MODE_MAC_EHS_HEADER         = 2,            /* BBP按照mac Ehs解析mac头 */
    PHYITF_MAC_RPT_MODE_BUTT
};
typedef VOS_UINT16 PHYITF_MAC_RPT_MODE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_MAC_RESET_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 配置reset 头类型
*****************************************************************************/
enum PHYITF_MAC_RESET_TYPE_ENUM
{
    PHYITF_MAC_HS_RESET                       = 0,            /* 指示reset mac hs实体 */
    PHYITF_MAC_EHS_RESET                      = 1,            /* 指示reset mac ehs 实体*/
    PHYITF_MAC_RESET_BUTT
};
typedef VOS_UINT16 PHYITF_MAC_RESET_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_MAC_E_I_RESET_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : MAC_E/MAC_I reset
*****************************************************************************/
enum PHYITF_MAC_E_I_RESET_TYPE_ENUM
{
    PHYITF_MAC_E_RESET                      = 0,                /* 指示reset mac hs实体 */
    PHYITF_MAC_I_RESET                      = 1,                /* 指示reset mac ehs 实体*/
    PHYITF_MAC_E_I_RESET_BUTT
};
typedef VOS_UINT16 PHYITF_MAC_E_I_RESET_TYPE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHYITF_HSDSCH_TB_SIZE_TABLE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : TB SIZE TABLE 对齐方式
*****************************************************************************/
enum PHYITF_HSDSCH_TB_SIZE_TABLE_ENUM
{
    PHYITF_HSDSCH_TB_SIZE_TABLE_BIT_ALIGNED     = 0,     /* 使用HS-DSCH TB SIZE TBLE BIT ALIGNED 方式*/
    PHYITF_HSDSCH_TB_SIZE_TABLE_OCTET_ALIGNED   = 1,     /* 使用HS-DSCH TB SIZE TBLE OCTET ALIGNED 方式*/

    PHYITF_HSDSCH_TB_SIZE_TABLE_BUTT
};
typedef VOS_UINT16 PHYITF_HSDSCH_TB_SIZE_TABLE_ENUM_UINT16;
/* V3 R7_7C1 End */


/*****************************************************************************
 枚举名    : PHYITF_MIMO_OPER_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : MIMO操作方式
*****************************************************************************/
enum  PHYITF_MIMO_OPER_ENUM
{
    PHYITF_MIMO_OPER_START                      = 0,                            /* 指示MIMO初始启动 */
    PHYITF_MIMO_OPER_CONTINUE,                                                  /* 指示MIMO继续当前配置  */
    PHYITF_MIMO_OPER_STOP,                                                      /* 指示MIMO停止 */
    PHYITF_MIMO_OPER_BUTT
};
typedef VOS_UINT16 PHYITF_MIMO_OPER_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_MIMO_N_M_RATIO_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : MIMO N/M RATIO
*****************************************************************************/
enum  PHYITF_MIMO_N_M_RATIO_ENUM
{
    PHYITF_MIMO_N_M_RATIO_MNM1_2 = 0,
    PHYITF_MIMO_N_M_RATIO_MNM2_3,
    PHYITF_MIMO_N_M_RATIO_MNM3_4,
    PHYITF_MIMO_N_M_RATIO_MNM4_5,
    PHYITF_MIMO_N_M_RATIO_MNM5_6,
    PHYITF_MIMO_N_M_RATIO_MNM6_7,
    PHYITF_MIMO_N_M_RATIO_MNM7_8,
    PHYITF_MIMO_N_M_RATIO_MNM8_9,
    PHYITF_MIMO_N_M_RATIO_MNM9_10,
    PHYITF_MIMO_N_M_RATIO_MNM1_1,
    PHYITF_MIMO_N_M_RATIO_BUTT
};
typedef VOS_UINT16 PHYITF_MIMO_N_M_RATIO_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHYITF_MIMO_SCPICH_PATTERN_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : S-CPICH PATTERN
*****************************************************************************/
enum  PHYITF_MIMO_SCPICH_PATTERN_ENUM
{
    PHYITF_MIMO_NORMAL                          = 0,
    PHYITF_MIMO_DIVERSITY,
    PHYITF_MIMO_PATTERN_BUTT
};
typedef VOS_UINT16 PHYITF_MIMO_SCPICH_PATTERN_ENUM_UINT16;
/*****************************************************************************
 枚举名    : PHYITF_PCPICH_USAGE_FOR_CH_EST_ENUM
 协议表格  :
 ASN.1描述 :   MinReduced-E-DPDCH-GainFactor
 枚举说明  : E_DPDCH功率回退因子
*****************************************************************************/
enum PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_ENUM
{
    PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_M815   = 0,
    PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_M1115     ,
    PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_M1515     ,
    PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_M2115     ,
    PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_M3015     ,
    PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_M4215     ,
    PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_M6015     ,
    PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_M8415     ,
    PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_BUTT
};
typedef VOS_UINT16 PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_DATA_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum PHYITF_LOCH_DATA_TYPE_ENUM
{
    PHYITF_LOCH_DATA_TYPE_CCCH          = 0,
    PHYITF_LOCH_DATA_TYPE_SRB              ,
    PHYITF_LOCH_DATA_TYPE_CS               ,
    PHYITF_LOCH_DATA_TYPE_PS               ,
    PHYITF_LOCH_DATA_TYPE_BUTT
};
typedef VOS_UINT16 PHYITF_LOCH_DATA_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_RLC_PDU_SIZE_LI_SIZE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum PHYITF_RLC_PDU_SIZE_LI_SIZE_ENUM
{
    PHYITF_FLEX_RLC_PDU_SIZE_LI_SIZE_7_BIT  = 7,
    PHYITF_FLEX_RLC_PDU_SIZE_LI_SIZE_15_BIT = 15,
    PHYITF_FLEX_RLC_PDU_SIZE_LI_SIZE_BUTT
};
typedef VOS_UINT16 PHYITF_RLC_PDU_SIZE_LI_SIZE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHYITF_TSN_BIT_LEN_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum PHYITF_TSN_BIT_LEN_ENUM
{
    PHYITF_TSN_LEN_6_BIT        = 6,
    PHYITF_TSN_LEN_14_BIT       = 14,
    PHYITF_TSN_LEN_BUTT
};
typedef VOS_UINT16 PHYITF_TSN_BIT_LEN_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_SYNC_NEED_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :  配置dpch/fdpch时是否需要同步的指示
*****************************************************************************/

enum PHYITF_SYNC_NEED_ENUM
{
    PHYITF_SYNC_NEED                      = 0,    /* 需要同步 */
    PHYITF_SYNC_NO_NEED                   = 1,    /* 无需同步 */
    PHYITF_SYNC_UNKOWN                    = 2,    /* WAS无法判断是否同步，由DSP判断 */
    PHYITF_SYNC_BUTT
};
typedef VOS_UINT16  PHYITF_SYNC_NEED_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_UE_MOBILITY_STATE_ENUM16
 协议表格  :
 ASN.1描述 :
 枚举说明  : UE移动状态的枚举
*****************************************************************************/
enum PHYITF_HIGH_RATE_FLAG_ENUM
{
    PHYITF_HIGH_RATE_FLAG_FALSE   = 0,                                        /* UE处于低速移动状态 */
    PHYITF_HIGH_RATE_FLAG_TRUE    = 1,                                        /* UE处于高速移动状态 */
    PHYITF_HIGH_RATE_FLAG_BUTT
};
typedef VOS_UINT16 PHYITF_HIGH_RATE_FLAG_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_RRC_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : RRC状态
*****************************************************************************/
enum PHYITF_RRC_STATUS_ENUM
{
    PHYITF_RRC_STATUS_IDLE          = 0,                                        /* IDLE态 */
    PHYITF_RRC_STATUS_PCH           = 1,                                        /* PCH状态 */
    PHYITF_RRC_STATUS_FACH          = 2,                                        /* FACH状态 */
    PHYITF_RRC_STATUS_DCH           = 3,                                        /* DCH状态 */

    PHYITF_RRC_STATUS_BUTT
};
typedef  VOS_UINT16 PHYITF_RRC_STATUS_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_W_BG_SEARCH_OTHER_RAT_CMD_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 开始或者停止背景搜
*****************************************************************************/
enum  PHYITF_W_BG_SEARCH_OTHER_RAT_CMD_ENUM
{
    PHYITF_W_BG_SEARCH_OTHER_RAT_CMD_START                  = 0,
    PHYITF_W_BG_SEARCH_OTHER_RAT_CMD_STOP                      ,
    PHYITF_W_BG_SEARCH_OTHER_RAT_CMD_BUTT
};
typedef VOS_UINT16 PHYITF_W_BG_SEARCH_OTHER_RAT_CMD_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_W_BG_SEARCH_RAT_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 背景搜L或者G
*****************************************************************************/
enum  PHYITF_W_BG_SEARCH_RAT_ENUM
{
    PHYITF_W_BG_SEARCH_RAT_L                                 = 0,
    PHYITF_W_BG_SEARCH_RAT_G                                    ,
    PHYITF_W_BG_SEARCH_RAT_BUTT
};
typedef VOS_UINT16 PHYITF_W_BG_SEARCH_RAT_ENUM_UINT16;

/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/**********************************所有接口消息的数据结构****************************/
/*****************************************************************************
 结构名    : RRC_PHY_MSG_HEAD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC-PHY的公共消息头,供WAS HPA使用
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16    enMsgID;                  /*_H2ASN_Skip*/  /* 原语类型*/
    VOS_UINT16                    usOPID;                   /* 操作标识 */
}RRC_PHY_MSG_HEAD_STRU;

/*****************************************************************************
 结构名    : RRC_PHY_UPLINK_MAXTXPWR_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 最大上行功率配置消息的数据结构, 此消息不需要CNF
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16    enMsgID;                  /*_H2ASN_Skip*/  /* 原语类型*/
    VOS_UINT16                    usOPID;                   /* 操作标识 */
    VOS_INT16                     sActiveTime;              /* 激活时间 */
    VOS_INT16                     sMaxTxPwr;                /* [-50，33],上行链路最大发射功率= min(Maximum allowed UL TX Power=网侧配置的最大功率, PMAX =UE的最大功率规格),dbm */

}RRC_PHY_UPLINK_MAXTXPWR_REQ_STRU;


/*****************************************************************************
 结构名    : PHY_RRC_UPLINK_MAXTXPWR_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上行功率配置Cnf ID_PHY_RRC_UPLINK_MAXTXPWR_CNF
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* 操作标识 */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16  enIndicator;      /* 配置结果,0代表成功，其它代表失败*/
    VOS_UINT16                                usReserve1;

}PHY_RRC_UPLINK_MAXTXPWR_CNF_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_UPLINK_MAXTXPWR_ACTIVATE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上行功率配置Active In ID_PHY_RRC_UPLINK_MAXTXPWR_ACTIVATE_IND
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* 操作标识 */
    VOS_UINT16                                usCFN;            /* 配置生效的CFN */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16  enIndicator;      /* 配置结果,0代表成功，其它代表失败*/

}PHY_RRC_UPLINK_MAXTXPWR_ACTIVATE_IND_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_CAMPED_MAINCELL_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 主小区驻留证实消息的数据结构

*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                            /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;        /*_H2ASN_Skip*/ /* 原语类型 */
    VOS_UINT16                                usOPID;         /* 操作标识 */

    PHYITF_CAMPED_MAINCELL_RESULT_ENUM_UINT16 enResult;       /*主小区驻留结果*/
    VOS_UINT16                                usReserve1;

}PHY_RRC_CAMPED_MAINCELL_CNF_STRU;


/******************************信道配置参数************************************/
/**********SCCPCH 信道参数******************/

/*****************************************************************************
 结构名    : PHYITF_FACH_OCCASION_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CELL_FACH 状态下进行异频和异系统的测量时机
*****************************************************************************/
typedef struct
{
    PHYITF_BOOL_ENUM_UINT16                     enValidIndicator;
    VOS_UINT16                                  usSameOrDifferent;      /* 0：表示参数新配置或参数发生变化，按照以下参数的指示在指定的时刻进行频间测量1：表示未变化 */
    VOS_UINT16                                  usStartSFN;             /* [0，4095] FACHOccasion周期里的偏移值 */
    VOS_UINT16                                  usMREP;                 /* [2，4096] frame FACHOccasion周期 */
    VOS_UINT16                                  usNTTI;                 /* Sccpch的最大TTI长度,{1,2,4,8}frame */
    PHYITF_FACH_OCCASION_MEAS_TYPE_ENUM_UINT16  enMeasTypeFlag;         /* 异频或者GSM测量指示 */
    VOS_UINT32                                  ulInterMeasPeriod;      /* CELL_FACH状态下异频测量的周期，单位ms */
    VOS_UINT16                                  usInterRatMeasPeriod;   /* 480,CELL_FACH状态下GSM测量的周期，此值为固定常数480单位ms。 */
    VOS_UINT16                                  usMinIntraCellNum;      /* CELL_FACH状态下同频测量的小区的最小个数 */

}PHYITF_FACH_OCCASION_STRU;


typedef struct
{
    VOS_UINT16                                  usMTTI;   /*承载CTCH的FACH 使用的TTI帧数*/
    VOS_UINT16                                  usN;      /* CTCH 分配在S-CCPCH的周期*/
    VOS_UINT16                                  usK;      /* CBS 帧偏移*/
    VOS_UINT16                                  usP;      /* 调度信息的周期 */

} PHYITF_CTCH_OCCASION_STRU;

typedef struct
{

    VOS_UINT16                                  usSFN;  /*当前收到调度消息时的SFN*/
    VOS_UINT16                                  usMTTI; /*承载CTCH的FACH 使用的TTI帧数*/

    VOS_UINT16                                  usDrxBSOffsetListLen;     /* CTCH BS offset列表有效长度 */
    VOS_UINT16                                  ausDrxBSOffsetList[RRC_PHY_MAX_DRXBS_OFFSETLSTLEN]; /* CTCH BS offset列表 */

} PHYITF_CBS_DRX_STRU;


/*****************************************************************************
 结构名    : PHYITF_SCCPCH_PARA_STRU
 协议表格  : RRC在使用RRC_PHY_RL_SETUP_REQ原语配置SCCPCH和PICH物理信道时，
             要保证在配置之前已经将以前的SCCPCH和PICH物理信道释放掉，
             否则会发生错误。或者使用RRC_PHY_RL_MODIFY_REQ原语进行修改，
             要保证同时下发CCPCH和PICH物理信道参数，否则会发生错误。
 ASN.1描述 :
 结构说明  : SCCPCH 信道参数
*****************************************************************************/
#if(RRC_PHY_CBS_SWITCH == FEATURE_OFF)

typedef struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16        enPhyChannelType;     /* 物理信道类型 *//*_H2ASN_Skip*/
    /*  sActiveTime 对于FACH映射的SCCPCH为CFN，在指定CFN开始解调
        -1表示立即启动解调; 对于PCH映射的SCCPCH该参数无效 */
    VOS_INT16                            sActiveTime;          /* [-1, 255]激活时间    */
    VOS_UINT16                           usFreqInfo;           /* [0,16383]频率信息    */
    VOS_UINT16                           usSlotFormat;         /* [0, 17]时隙格式号,指示SCCPCH物理信道的当前使用的时隙格式 */
    VOS_UINT16                           usFrameTimingOffset;  /* [0, 149]相对于CPICH信道的帧偏移,以256 chip为单位，范围0~38144 chip */
    PHYITF_TX_DIVER_IND_ENUM_UINT16      enTDIndicator;
    VOS_UINT16                           usFreqBandNo;         /* 频段号:1,2,3,4,5,6*/
    VOS_UINT16                           usTxRxFreqSeparation; /* 收发频差*/
    VOS_UINT16                           usSecScramCode;       /* [0, 15]第二扰码0：表示使用主扰码; */
    VOS_UINT16                           usOvsfCodeNum;        /* [0, 511]扩频码号,OVSF码号 */
    VOS_UINT16                           usReserve3;
    PHYITF_SCCPCH_DEMODULATE_ENUM_UINT16 enSccpchDemInd;       /* 解调指示 */

    PHYITF_FACH_OCCASION_STRU            stFACHOccasionInfo;   /* FACH Occation:phase 2 */

}PHYITF_SCCPCH_PARA_STRU;

#else

typedef struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16        enPhyChannelType;     /* 物理信道类型 *//*_H2ASN_Skip*/

    /*  sActiveTime 对于FACH映射的SCCPCH为CFN，在指定CFN开始解调
        -1表示立即启动解调; 对于PCH映射的SCCPCH该参数无效 */
    VOS_INT16                            sActiveTime;          /* [-1, 255]激活时间    */

    VOS_UINT16                           usFreqInfo;           /* [0,16383]频率信息    */
    VOS_UINT16                           usSlotFormat;         /* [0, 17]时隙格式号,指示SCCPCH物理信道的当前使用的时隙格式 */
    VOS_UINT16                           usFrameTimingOffset;  /* [0, 149]相对于CPICH信道的帧偏移,以256 chip为单位，范围0~38144 chip */
    PHYITF_TX_DIVER_IND_ENUM_UINT16      enTDIndicator;
    VOS_UINT16                           usFreqBandNo;         /* 频段号:1,2,3,4,5,6*/
    VOS_UINT16                           usTxRxFreqSeparation; /* 收发频差*/
    VOS_UINT16                           usSecScramCode;       /* [0, 15]第二扰码0：表示使用主扰码; */
    VOS_UINT16                           usOvsfCodeNum;        /* [0, 511]扩频码号,OVSF码号 */
    VOS_UINT16                           usSccpchIndex;        /* [0,1]  支持多条sccpch时，对应的索引号 */
    PHYITF_SCCPCH_DEMODULATE_ENUM_UINT16 enSccpchDemInd;       /* 解调指示 */

    PHYITF_FACH_OCCASION_STRU            stFACHOccasionInfo;   /* FACH Occation:phase 2 */
    PHYITF_BOOL_ENUM_UINT16              enSupportCtch;        /* 是否支持cbs */
    VOS_UINT16                           usReserve1;

}PHYITF_SCCPCH_PARA_STRU;

#endif

/*****************************CBS配置参数***************************************/
/*****************************************************************************
 枚举名    : PHYITF_CBS_ACTION_ENUM_UINT16
 协议表格  : cbs的启停动作
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum PHYITF_CBS_ACTION_ENUM
{
    PHYITF_CBS_START                = 0,
    PHYITF_CBS_STOP                 = 1,
    PHYITF_ACTION_BUTT
};
typedef VOS_UINT16 PHYITF_CBS_ACTION_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_CBS_CFGTYPE_ENUM_UINT16
 协议表格  : cbs的启动类型
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum PHYITF_CBS_CFGTYPE_ENUM
{
     PHYITF_CBS_CFG_CTCH_OCCASION           = 0,          /* CBS的配置采用CTCH_OCCASION_STRU中的配置 */  /* _H2ASN_MsgChoice PHYITF_CTCH_OCCASION_STRU */
     PHYITF_CBS_CFG_CBS_DRX                 = 1,          /* CBS的配置采用CBS_DRX_STRU中的配置 */    /* _H2ASN_MsgChoice PHYITF_CBS_DRX_STRU */

     PHYITF_CFGTYPE_BUTT
};
typedef VOS_UINT16 PHYITF_CBS_CFGTYPE_ENUM_UINT16;


/*****************************************************************************
 结构名    : RRC_PHY_CBS_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CBS配置请求
 *****************************************************************************/
typedef   struct
{
    VOS_MSG_HEADER /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;               /* 原语类型 */ /*_H2ASN_Skip */
    VOS_UINT16                          usOPID;                 /* 操作标识 */
    PHYITF_CBS_ACTION_ENUM_UINT16       enAction;               /* 开始或停止接收cbs */
    PHYITF_CBS_CFGTYPE_ENUM_UINT16      enCBSCfgTypeChoice;      /* _H2ASN_IeChoice_Export PHYITF_CBS_CFGTYPE_ENUM_UINT16 */
    union /*_H2ASN_Skip*/
    {     /*_H2ASN_Skip*/
        PHYITF_CTCH_OCCASION_STRU        stCtchOccationInfo;    /* _H2ASN_Skip */
        PHYITF_CBS_DRX_STRU              stCbsDrxInfo;
        /******************************************************************************************************
            _H2ASN_IeChoice_When        PHYITF_CBS_CFGTYPE_ENUM_UINT16
        ******************************************************************************************************/
    }u;  /* _H2ASN_Skip */
}RRC_PHY_CBS_CONFIG_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_CBS_CONFIG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : cbs 配置响应
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* 操作标识 */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16  enIndicator;      /* 配置结果,0代表成功，其它代表失败*/
    VOS_UINT16                                usReserve1;

}PHY_RRC_CBS_CONFIG_CNF_STRU;


/*****************************PICH 信道参数***************************************/
/*****************************************************************************
 结构名    : PHYITF_PAGING_OCCATION_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 寻呼时机
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usStartSFN;                             /*解调周期起始时刻*/
    VOS_UINT16                          usPeriodT;

}PHYITF_PAGING_OCCATION_STRU;

/*****************************************************************************
 结构名    : PHYITF_PICH_STRU
 协议表格  : RRC在使用RRC_PHY_RL_SETUP_REQ原语配置SCCPCH和PICH物理信道时，
             要保证在配置之前已经将以前的SCCPCH和PICH物理信道释放掉，
             否则会发生错误。或者使用RRC_PHY_RL_MODIFY_REQ原语进行修改，
             要保证同时下发CCPCH和PICH物理信道参数，否则会发生错误。
 ASN.1描述 :
 结构说明  : PICH 信道参数
*****************************************************************************/
typedef  struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16       enPhyChannelType;                       /* 物理信道类型                             *//*_H2ASN_Skip*/
    VOS_UINT16                          usFreqInfo;                             /* 频率信息                                 */
    VOS_UINT16                          usOvsfCodeNum;                          /* OVSF码号                                 */
    VOS_UINT16                          usPiNumber;                             /* 一帧中的Pi数量                           */
    VOS_INT16                           sPichPowerOffset;                       /* PICH功率偏移                             */
    VOS_UINT16                          usPI;                                   /* Pi位置参数                               */
    PHYITF_TX_DIVER_IND_ENUM_UINT16     enTDIndicator;
    VOS_UINT16                          usFreqBandNo;                           /* 频段号:1,2,3,4,5,6*/
    VOS_UINT16                          usTxRxFreqSeparation;                   /* 收发频差*/
    VOS_UINT16                          usReserve1;
    PHYITF_PAGING_OCCATION_STRU         stPaggingOccasion;

}PHYITF_PICH_STRU;


/*****************************AICH 信道参数***************************************/
/*****************************************************************************
 结构名    : PHYITF_AICH_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : AICH 信道参数
*****************************************************************************/
typedef   struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16       enPhyChannelType;                       /* 物理信道类型                             *//*_H2ASN_Skip*/
    VOS_UINT16                          usFreqInfo;                             /* 频率信息                                 */
    VOS_UINT16                          usOvsfCodeNum;                          /* 扩频码号                                 */
    VOS_UINT16                          usAichTransmissionTiming;               /* AICH定时参数                             */
    VOS_INT16                           sAichPowerOffset;                       /* AICH功率偏移                             */
    PHYITF_TX_DIVER_IND_ENUM_UINT16     enTDIndicator;
    VOS_UINT16                          usFreqBandNo;                          /* 频段号:1,2,3,4,5,6*/
    VOS_UINT16                          usTxRxFreqSeparation;                   /* 收发频差*/
}PHYITF_AICH_STRU;

/*****************************PRACH 信道参数***************************************/

/*****************************************************************************
 结构名    : PHYITF_AVAIL_SIGNATURE_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PRACH SIGNATURE 信道参数
*****************************************************************************/
/* AVAILABLE_SIGNATURE_INFO的数据结构 */
typedef struct
{
    VOS_UINT16                          usSignaltureNum;                        /* 可用的signature数 */
    VOS_UINT16                          usReserve1;
    VOS_INT16                           asAvailableSignature[RRC_PHY_MAX_SIGNATURE_NUM]; /* 每一个可用signature的编号 */

}PHYITF_AVAIL_SIGNATURE_INFO_STRU;


/*****************************************************************************
 结构名    : PHYITF_AVAIL_SUB_CHAN_NUM_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PRACH SUB CHANNEL 信道参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSubChanNum;                           /* 可用SubChan数目 */
    VOS_UINT16                          usReserve1;
    VOS_INT16                           asAvailableSubChanNum[RRC_PHY_MAX_SUBCHANNEL_NUM];  /* 存各可用SubChan 的表格 */

}PHYITF_AVAIL_SUB_CHAN_NUM_INFO_STRU;


/*****************************************************************************
 结构名    : PHYITF_ASC_ITEM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PRACH 每个 ACCESS SERVICE CLASS 参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usAvailSignatureStartIdx;               /* 可用Signature起始索引号 */
    VOS_UINT16                          usAvailSignatureStopIdx;                /* 可用Signature结束索引号 */
    VOS_INT16                           sAvailableSubChanCnt;                   /* 可使用的subchannel的数量 */
    VOS_UINT16                          usReserve1;
#if (INTERFACE_TYPE == INTERFACE_PS)
    VOS_UINT8                           aucAvailSubChanIdx[RRC_PHY_MAX_SUBCHANNEL_NUM]; /* Subchannel的索引 */
#elif (INTERFACE_TYPE == INTERFACE_DSP)
    VOS_UINT16                          ausAvailSubChanIdx[RRC_PHY_MAX_SUBCHANNEL_NUM/2]; /* _H2ASN_Skip Subchannel的索引 */
#endif
}PHYITF_ASC_ITEM_STRU;

/*****************************************************************************
 结构名    : PHYITF_ASC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PRACH 的总的 ACCESS SERVICE CLASS 参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usAscNum;                               /* 可用ASC数目  */
    VOS_UINT16                          usReserve1;
    PHYITF_ASC_ITEM_STRU                astAccessServiceClass[RRC_PHY_MAX_ASC_NUM];  /* 随机接入过程 */

}PHYITF_ASC_STRU;


/*****************************************************************************
 结构名    : PHYITF_PRACH_PWR_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PRACH 的功率控制参数
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sPrachInitialTxPower;                   /* Preamble初始功率控制,单位dBm */
    VOS_UINT16                          usPowerRampStep;                        /* 相邻两个Preamble的功率差值,单位dB */
    VOS_UINT16                          usPreambleRetryMax;                     /* 一次随机过程发送Preamble的最大允许次数 */
    VOS_INT16                           sSCellRscp;

}PHYITF_PRACH_PWR_CTRL_STRU;

/*****************************************************************************
 结构名    : PHYITF_PRACH_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PRACH 的信道参数
*****************************************************************************/
typedef  struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16       enPhyChannelType;                       /* 物理信道类型                    *//*_H2ASN_Skip*/
    VOS_UINT16                          usFreqInfo;                             /* 频率信息                        */
    VOS_UINT16                          usScramCodeNum;                         /* 扰码标号                        */
    VOS_UINT16                          usTTI;                                  /* PRACH的传输时间间隔
                                                                                   E-RACH复用这个结构时这个参数没有用，固定填写10ms */

    PHYITF_AVAIL_SIGNATURE_INFO_STRU    stAvailSignatureInfoEntity;             /* 该PRACH可用的SIGNATURE数据结构  */
    PHYITF_AVAIL_SUB_CHAN_NUM_INFO_STRU stAvailSubChanNumInfoEntity;            /* 该PRACH可用的SUBCHANNEL数据结构 */
    PHYITF_ASC_STRU                     stAccessServiceClassSEntity;            /* 每个ASC资源信息                 */
    PHYITF_PRACH_PWR_CTRL_STRU          stPrachPwrCtrlEntity;                   /* PRACH功率控制信息               */
    VOS_UINT16                          usFreqBandNo;                          /* 频段号:1,2,3,4,5,6*/
    VOS_UINT16                          usTxRxFreqSeparation;                   /* 收发频差*/
}PHYITF_PRACH_STRU;


/*****************************下行 DPCH 信道参数***************************************/

/*****************************************************************************
 结构名    : PHYITF_DOWNLINKINFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DOWNLINK 信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                    usSecScramCode;                         /* 第二扰码，如果不存在使用0表示无效 */
    VOS_INT16                                     sOvsfCodeNum;                           /* 扩频码   */
    VOS_UINT16                                    usReserve1;
    PHYITF_SCRAMBLE_CODE_CHANGE_TYPE_ENUM_UINT16  enScrambCodeChange;                     /* 扰码改变标志 */

}PHYITF_DOWNLINKINFO_STRU;

/*****************************************************************************
 结构名    : PHYITF_DL_MODE_COMPRESS_METHOD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 下行压缩方法
*****************************************************************************/
typedef struct
{
    PHYITF_COMPRS_MODE_ENUM_UINT16      enDLMethod;
    VOS_UINT16                          usReserve1;

}PHYITF_DL_COMPRESS_METHOD_STRU;

/*****************************************************************************
 结构名    : PHYITF_DL_MODE_COMPRESS_METHOD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上行压缩方法
*****************************************************************************/
typedef struct
{
    PHYITF_COMPRS_MODE_ENUM_UINT16      enULMethod;
    VOS_UINT16                          usReserve1;

}PHYITF_UL_COMPRESS_METHOD_STRU;

/*****************************************************************************
 结构名    : PHYITF_DL_AND_UL_COMPRESS_METHOD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上行和下行压缩方法
*****************************************************************************/
typedef struct
{
     PHYITF_COMPRS_MODE_ENUM_UINT16     enDLMethod;                             /* 下行压缩模式的方式 */
     PHYITF_COMPRS_MODE_ENUM_UINT16     enULMethod;                             /* 上行压缩模式的方式 */

}PHYITF_DL_AND_UL_COMPRESS_METHOD_STRU;

/*****************************************************************************
 枚举名    : PHYITF_TGMP_ENUM
 协议表格  :
 ASN.1描述 : TGMP
 枚举说明  : 压缩模式测量目的
*****************************************************************************/
enum PHYITF_TGMP_ENUM
{
    PHYITF_TGMP_TDD_MEAS                   = 0,
    PHYITF_TGMP_FDD_MEAS                   = 1,
    PHYITF_TGMP_GSM_CARR_RSSI_MEAS         = 2,
    PHYITF_TGMP_GSM_INIT_BSIC_ID           = 3,
    PHYITF_TGMP_GSM_BSIC_RECNF             = 4,
    PHYITF_TGMP_MULTI_CARR                 = 5,
    PHYITF_TGMP_E_UTRA                     = 6,
    PHYITF_TGMP_BUTT
};
typedef VOS_UINT16 PHYITF_TGMP_ENUM_UINT16;

/*****************************************************************************
 结构名    : PHYITF_COMPRESS_MODE_TGPS_CONFIGPARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TGPS 的配置参数
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sTGPRC;                                 /* TGP的个数包括TGP SEQUENCE                                */
    VOS_UINT16                          usTGMP;                                 /* TGP测试目标                              */
    VOS_UINT16                          usTGSN;                                 /* Transmission Gap 开始传送断开的次数包括TGCFN*/
    VOS_UINT16                          usTGL1;                                 /* 第一次Transmission Gap的长度包括TGP断开时*/
    VOS_UINT16                          usTGL2;                                 /* 第二次Transmission Gap的长度包括TGP PATTERN*/
    VOS_INT16                           sTGD;                                   /* Transmission gap distance                */
    VOS_UINT16                          usTGPL1;                                /* TGP1的持续                               */
    VOS_UINT16                          usTGPL2;                                /* TGP2的持续                               */
    VOS_UINT16                          usRPP;                                  /* TGP 过程中的Recovery Period Power控制模式*/
    VOS_UINT16                          usITP;                                  /* 压缩模式下的Initial Transmit Power*/
    VOS_UINT16                          usDLFrameType;                          /* 使用的帧类型                             */
    VOS_UINT16                          usDeltaSIR1;                            /* TGP 建立过程中Delta in DL SIR1的目标值*/
    VOS_UINT16                          usDeltaSIRafter1;                       /* TGP 建立过程后Delta in DL SIR1的目标值*/
    VOS_UINT16                          usDeltaSIR2;                            /* TGP 建立过程中Delta in DL SIR2的目标值*/
    VOS_UINT16                          usDeltaSIRafter2;                       /* TGP 建立过程后Delta in DL SIR2的目标值*/
    VOS_UINT16                          usNIdentifyabort;
    VOS_UINT16                          usTReconfirmabort;

    #define    PHYITF_COMPRESS_METHOD_UL_CHOSEN         0
    #define    PHYITF_COMPRESS_METHOD_DL_CHOSEN         1
    #define    PHYITF_COMPRESS_METHOD_UL_DL_CHOSEN      2

    VOS_UINT16                          usModeChoice;                           /* 压缩模式的使用选择                       */
    union
    {

        PHYITF_UL_COMPRESS_METHOD_STRU          stULMode;
        PHYITF_DL_COMPRESS_METHOD_STRU          stDLMode;
        PHYITF_DL_AND_UL_COMPRESS_METHOD_STRU   stDLAndULMode;

    } CompressMethod;
}PHYITF_COMPRESS_MODE_TGPS_CONFIGPARA_STRU;


/*****************************************************************************
 结构名    : PHYITF_COMPRESS_MODE_TGPS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 某个 TGPS 信息
 *****************************************************************************/
typedef struct
{
     VOS_UINT16                                 usTGPSI;                        /* TGPS标识       */
     VOS_UINT16                                 usTGPSStausFlag;                /* TGPS状态标志   */
     VOS_INT16                                  sTGCFN;                         /* TGCFN          */
     VOS_UINT16                                 usReserve1;
     PHYITF_COMPRESS_MODE_TGPS_CONFIGPARA_STRU  stTGPSConfigPara;

}PHYITF_COMPRESS_MODE_TGPS_INFO_STRU;


/*****************************************************************************
 结构名    : PHYITF_COMPRESS_MODE_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 压模信息
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTGPSCnt;                              /* TGPS个数 */
    VOS_UINT16                          usReserve1;
    PHYITF_COMPRESS_MODE_TGPS_INFO_STRU astTGPS[RRC_PHY_MAX_TGPS];

}PHYITF_COMPRESS_MODE_INFO_STRU;

/**********Second Cpich Info 参数******************/

/*****************************************************************************
 结构名    : PHYITF_SECOND_CPICH_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 辅导频配置信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16   usSecondDlScramblCode;       /* 0表示无效,其扰码和主导频扰码相同, 其它取值(1..15)*/
    VOS_UINT16   usOvsfCodeNum;               /* INTEGER(0..255) */
}PHYITF_SECOND_CPICH_STRU;

/*****************************************************************************
 结构名    : PHYITF_JUDGE_SYNC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 同失步判决参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16   usSyncDetect;              /* 同步初始检查，是否该时间内1帧都没有同步上，就不用等T312超时， 单位frame */
    VOS_UINT16   usT312;                    /* 同步判决定时器，单位frame， 范围100-1500 */
    VOS_UINT16   usN312;                    /* 同步判决门限 范围1-1000 */
    VOS_UINT16   usT313;                    /* 失步判决定时器， 单位frame 范围100-1500 */
    VOS_UINT16   usN313;                    /* 失步判决计数，范围1-200 */
    VOS_UINT16   usN315;                    /* 失步后恢复同步的门限计数，范围1-1000 */
    VOS_UINT16   usDisableUlDcchTimer;      /* 连续几帧失步后通知WAS不发送DCCH消息，同步后需再次通知，单位frame，目前固定为4 */
    VOS_UINT16   usResumeUlDcchTimer;       /* 停止发送测量报告后，连续几帧同步后，开始发送DCCH消息，单位frame，目前固定为1 */
}PHYITF_JUDGE_SYNC_STRU;

/*****************************************************************************
 结构名    : PHYITF_DOWNLINK_DPCH_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 下行专用物理信道参数
 *****************************************************************************/
typedef struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16           enPhyChannelType;                   /* 物理信道类型 *//*_H2ASN_Skip*/
    VOS_INT16                               sActiveTime;                        /* 激活时间 */
    VOS_UINT16                              usFreqInfo;                         /* 频率信息 */
    VOS_UINT16                              usSlotFormat;                       /* 时隙格式 */
    VOS_UINT16                              usDpchFrameOffset;                  /* 帧偏移 */
    PHYITF_TX_DIVER_IND_ENUM_UINT16         enTDIndicator;                      /* 分集指示 */
    VOS_UINT16                              usDpchChanNum;                      /* DPCH个数 */
    VOS_UINT16                              usDownLinkScramCode;                /* 下行链路主扰码号 */
    PHYITF_DOWNLINKINFO_STRU                astDownLinkInfoEntity[RRC_PHY_MAX_DLDPCH_CHAN_NUM]; /* 下行DPCH信息 */
    PHYITF_DPC_MODE_TYPE_ENUM_UINT16        enDpcMode;                          /* 下行功率控制*/
    VOS_UINT16                              usTpcCombIndex;                     /* TPC组合索引 */
    PHYITF_TIMING_INDIACTION_ENUM_UINT16    enTimingIndication;                 /* 硬切换定时指示 */
    VOS_INT16                               sCfnSfnOffset;                      /* CFN-targetSFN frame offset */

    PHYITF_COMPRESS_MODE_INFO_STRU          stCompressMode;                     /* 压缩模式 */
    VOS_UINT16                              usRsv1;

    /* 定义成3项，增加未知。软切换时，填no need。  非d到d，三个值都有可能。
      硬切换时，不允许填unkown。 普通重配，填no need。
      如果D2D定时维持时,不需要同步A,否则需要 */
    PHYITF_SYNC_NEED_ENUM_UINT16            enNeedSync;
    PHYITF_BOOL_ENUM_UINT16                 enPostVerification;                 /* 同步是否采取post verification过程，如果无需同步,该值无意义 */

    PHYITF_TX_DIVER_IND_ENUM_UINT16         enPcpichTDIndicator;                /*主导频信道是否使用发分集,0:不使用分集,1:STTD分集,0xFF:无法获得分集方式*/
    VOS_UINT16                              usBlindHhoFlag;                     /*盲切换标记 ，1:盲切换;0:非盲切换*/

    VOS_UINT16                              usFreqBandNo;                       /* 频段号:1,2,3,4,5,6*/
    VOS_UINT16                              usTxRxFreqSeparation;               /* 收发频差*/

    PHYITF_BOOL_ENUM_UINT16                 enSecndCpichValidInd;               /*辅导频是否有效标志*/
    PHYITF_SECOND_CPICH_STRU                stSecondCpichInfo;                  /*辅导频信息*/
    VOS_UINT16                              usPO2;                              /* Ptpc - Pdpdch (dB),取值范围 0-24,Step:0.25,即为实际值*4,若不存在则为0xFFFF*/
    VOS_UINT16                              usPO3;                              /* Ppilot - Pdpdch (dB),取值范围 0-24,Step:0.25,即为实际值*4*/

    PHYITF_JUDGE_SYNC_STRU                  stJudgeSync;                        /* 同失步判决参数 */
}PHYITF_DOWNLINK_DPCH_PARA_STRU;

/*****************************下行 FDPCH 信道参数***************************************/
/*****************************************************************************
 结构名    : PHYITF_DOWNLINK_FDPCH_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 下行部分专用信道参数
 *****************************************************************************/
typedef struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16           enPhyChannelType;                   /* 物理信道类型 *//*_H2ASN_Skip*/
    VOS_INT16                               sActiveTime;                        /* 激活时间 */
    VOS_UINT16                              usFreqInfo;                         /* 频率信息 */
    VOS_UINT16                              usFdpchFrameOffset;                 /* 帧偏移 */
    VOS_UINT16                              usFdpchSlotFormat;                  /* 时隙格式，INTEGER(0..9) */
    VOS_UINT16                              usBlindHhoFlag;                     /*盲切换的标志*/
    PHYITF_TX_DIVER_IND_ENUM_UINT16         enTDIndicator;                      /* 分集指示 */
    VOS_UINT16                              usDownLinkScramCode;                /* 下行链路主扰码号 */
    PHYITF_DPC_MODE_TYPE_ENUM_UINT16        enDpcMode;                          /* 下行功率控制*/
    VOS_UINT16                              usTpcCombIndex;                     /* TPC组合索引 */
    PHYITF_TIMING_INDIACTION_ENUM_UINT16    enTimingIndication;                 /* 硬切换定时指示 */
    VOS_INT16                               sCfnSfnOffset;                      /* CFN-targetSFN frame offset */
    VOS_UINT16                              usSecScramCode;                     /* 第二扰码，如果不存在使用0表示无效 */
    VOS_UINT16                              usOvsfCodeNum;                      /* 扩频码   */
    VOS_UINT16                              usTpcErrorRateTarget;               /*因为原值精度为0.01, 为了保持精度目前配置值是原始值扩大100倍*/
    VOS_INT16                               sInitialSirTarget;                  /*初始SirTarget用于外环功控*/
    VOS_INT16                               sDeltaSirTarget;                      /*DeltaSirTarget用于外环功控*/
    VOS_UINT16                              usUpStepSizeFactor ;
    VOS_UINT16                              usDownStepSizeFactor ;
    VOS_UINT16                              usFreqBandNo;                       /* 频段号:1,2,3,4,5,6*/
    VOS_UINT16                              usTxRxFreqSeparation;               /* 收发频差*/

    PHYITF_BOOL_ENUM_UINT16                 enSecndCpichValidInd;               /*辅导频有效指示标识,0:无效,若无效要使用主导频做信道估计,1:有效,要使用辅导频来做信道估计*/
    PHYITF_SECOND_CPICH_STRU                stSecondCpichInfo;                  /*辅导频配置信息*/

    PHYITF_COMPRESS_MODE_INFO_STRU          stCompressMode;                     /* 压缩模式 */

    VOS_UINT16                              usRsv1;

   /* 定义成3项，增加未知。软切换时，填no need。  非d到d，三个值都有可能。
     硬切换时，不允许填unkown。 普通重配，填no need。    */
    PHYITF_SYNC_NEED_ENUM_UINT16            enNeedSync;

    PHYITF_BOOL_ENUM_UINT16                 enPostVerification;                 /* 同步是否采取post verification过程，如果无需同步,该值无意义 */

    PHYITF_TX_DIVER_IND_ENUM_UINT16         enPcpichTDIndicator;                /*主导频信道是否使用发分集,0:不使用分集,1:STTD分集,0xFF:无法获得分集方式*/

    PHYITF_JUDGE_SYNC_STRU                  stJudgeSync;                        /* 同失步判决参数 */

}PHYITF_DOWNLINK_FDPCH_PARA_STRU;



/*****************************上行 DPCH 信道参数***************************************/

/*****************************************************************************
 结构名    : PHYITF_UlDPCH_POWER_CONTROL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上行专用物理功率控制信息
 *****************************************************************************/


typedef struct
{
    VOS_INT16                           sDpchInitialTxPower;                    /* 上行dpch初始传送功率，
                                                                                   E-RACH时没有该参数, 填写0，L2W切换或W2W切换失败回退时，
                                                                                   该参数无效，由DSP根据sUlDpcchPowerOffset计算得出 */
    VOS_UINT16                          usPcPreamble;                           /* 仅发送DPCCH的帧数 ,
                                                                                   E-RACH时没有该参数，填写0 */
    PHYITF_UL_DPCH_PWRCTRL_ALGO_UINT16  enPowerControlAlgorithm;                /* UE解释TPC命令使用的指定算法              */
    VOS_UINT16                          usTpcStepSize;
    VOS_INT16                           sUlDpcchPowerOffset;                    /* E-RACH时没有该参数，填写0 */
    VOS_UINT16                          usBlindHhoFlag;

}PHYITF_ULDPCH_POWER_CONTROL_STRU;

/*****************************************************************************
 结构名    : PHYITF_UPLINK_DPCH_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上行专用物理信道信息
 *****************************************************************************/
typedef struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16        enPhyChannelType;                       /* 物理信道类型 *//*_H2ASN_Skip*/
    VOS_INT16                            sActivateTime;                          /* 激活时间 */
    VOS_UINT16                           usFreqInfo;                             /* 频率信息 */
    PHYITF_SCRAMBL_CODE_TYPE_ENUM_UINT16 enScramCodeType;                        /* 扰码类型 */
    VOS_UINT32                           ulScramCodeNum;                         /* 扰码数 */
    PHYITF_ULDPCH_POWER_CONTROL_STRU     stUlDpchPowerControl;
    VOS_UINT16                           usDpchNum;                              /* 上行DPDCH的数量 */
    VOS_UINT16                           usSlotFormat;                           /* 上行DPCCH使用的时隙格式 */
    VOS_UINT16                           usFreqBandNo;                           /* 频段号:1,2,3,4,5,6*/
    VOS_UINT16                           usTxRxFreqSeparation;                   /* 收发频差*/
}PHYITF_UPLINK_DPCH_STRU;





/*==========================================================================
                              HSDPA 信道参数
============================================================================*/

/*****************************************************************************
 结构名    : PHYITF_MEAS_FEEDBACK_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSDPA 测量反馈信息
 *****************************************************************************/
typedef struct
{
    VOS_INT16                           sMeasPwrOffset;     /* INTEGER(-12..26),步长为0.5, 即实际值为配置值除2*/
    VOS_UINT16                          usFeedbackCycle;    /* 反馈周期,取值(0, 2, 4, 8, 10, 20, 40, 80, 160,16,32,64) ms*/
    VOS_UINT16                          usCqiRepetFactor;   /* INTEGER(1..4) */
    VOS_UINT16                          usDeltaCqi;         /* INTEGER(0..8) */

}PHYITF_MEAS_FEEDBACK_INFO_STRU;

/*****************************************************************************
 结构名    : PHYITF_HS_DPCCH_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSDPCCH 信息
 *****************************************************************************/
typedef  struct
{
    VOS_UINT16                          usDeltaAck;                             /* INTEGER(0..8)  OPTIONAL
                                                                                   E-RACH时，如果不存在填写8 */

    VOS_UINT16                          usDeltaNack;                            /* INTEGER(0..8)  OPTIONAL
                                                                                  E-RACH时，如果不存在填写8 */

    VOS_UINT16                          usAckNackRepetFactor;                   /* Ack_Nack重复因子(1-4)
                                                                                  E-RACH时，如果不存在填写1 */

    VOS_UINT16                          usHarqPrbMode;                          /* Harq 前导模式选择,当usHarqPrbMode为1有效
                                                                                 E-RACH时不携带该参数，填写0 */

    VOS_UINT16                          usReserve1;

    /*测量反馈信息,当enMeasFeedBackInfoValid为1有效*/
    PHYITF_BOOL_ENUM_UINT16             enMeasFeedBackValid;                    /* 指示 stMeasFeedBackInfo是否有效 */
    PHYITF_MEAS_FEEDBACK_INFO_STRU      stMeasFeedBackInfo;

}PHYITF_HS_DPCCH_INFO_STRU;

/*****************************************************************************
 结构名    : PHYITF_HARQ_EXPLI_MEMSIZE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HARQ 内存显示大小信息
 *****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCnt;
    VOS_UINT32                          aulMHarqMemorySize[RRC_PHY_MAX_HSDPA_PROCESSES];  /*HARQ_MEMORY_SIZE 大小*/

}PHYITF_HARQ_EXPLI_MEMSIZE_STRU;

/*****************************************************************************
 结构名    : PHYITF_HARQ_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HARQ 信息
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usNumOfProcesses;                       /* INTEGER(1..16),进程数 */
    VOS_UINT16                          usReserve1;
    PHYITF_HARQ_EXPLI_MEMSIZE_STRU      stMemoryPartition;                      /* 进程的内存分配大小*/

}PHYITF_HARQ_INFO_STRU;


/*****************************************************************************
 结构名    : PHYITF_HS_SCCH_CODE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HS_SCCH 信道码信息
 *****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCnt;
    VOS_UINT16                          ausHsScchCodes[RRC_PHY_MAX_HSSCCH_NUM];  /* INTEGER(0..127) */

}PHYITF_HS_SCCH_CODE_STRU;

/*****************************************************************************
 结构名    : PHYITF_HS_SCCH_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HS_SCCH 信息
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usReserve1;

    /* INTEGER(0..15)  OPTIONAL,辅扰码号.当usDlScramblCode取值为0表示使用主扰码,
        否则使用辅扰码 */
    VOS_UINT16                          usDlScramblCode;

    PHYITF_HS_SCCH_CODE_STRU            stHsScchCodeInfo;   /*HS_SCCH 使用的信道码信息*/

}PHYITF_HS_SCCH_INFO_STRU;

/*****************************************************************************
 结构名    : PHYITF_HS_PDSCH_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HS_PDSCH 信息
 *****************************************************************************/
typedef struct
{
    PHYITF_HS_SCCH_INFO_STRU            stHsScchInfo;    /* HsScchInfo,取自Downlink HS-PDSCH Information*/

}PHYITF_HS_PDSCH_INFO_STRU;


/*****************************************************************************
 结构名    : PHYITF_MAC_D_PDU_SIZE_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSDPA MAC_D PDU SIZE 信息结构
 *****************************************************************************/
typedef struct
{
    /* Mac_D Pdu 索引, INTEGER(0..7) */
    VOS_UINT16                             usMacDPduIndex;

    /* Mac_D Pdu Size的大小,INTEGER(1..5000) */
    VOS_UINT16                             usMacDPduSize;

} PHYITF_MAC_D_PDU_SIZE_INFO_STRU;

/*****************************************************************************
 结构名    : PHYITF_MAC_HS_QUEUE_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSDPA MAC_HS QUEUE 信息结构
 *****************************************************************************/
typedef struct
{

    /*MacHs 的队列ID,INTEGER(0..7)*/
    VOS_UINT16                             usMacHsQueueId;

    /*该队列的 Mac_D Pdu Size 的数目,INTEGE(1..8)*/
    VOS_UINT16                             usMacDPduSizeCnt;

    /*Mac_D Pdu Size 列表,存储了每个MacDPdu size的大小和索引*/
    PHYITF_MAC_D_PDU_SIZE_INFO_STRU        astMacDPduSizeInfoList[RRC_PHY_MAX_MAC_D_PDU_SIZES_NUM];

} PHYITF_MAC_HS_QUEUE_INFO_STRU;

/*****************************************************************************
 结构名    : PHYITF_MAC_HS_CFG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSDPA MAC_HS 配置信息结构
 *****************************************************************************/
typedef struct
{

    /*MacHs PDU上报的模式,0直接上报,1:将MAC 头解析后再上报,目前固定填为1*/
    PHYITF_MAC_RPT_MODE_ENUM_UINT16        enMacHsReportMode;

    /*每个队列是否存在C/T域标志, bit0~bit7分别对应queue0~queue7,其余位空闲
      Bit位为1表示包含C/T域, Bit为0表示不包含C/T域*/
    VOS_UINT16                             usMacHsQueueCTFlag;

    VOS_UINT16                             usReserve1;

    /*Mac_Hs 队列数目,INTEGE(1..8)*/
    VOS_UINT16                             usMacHsQueueCnt;

    /*Mac_Hs 队列信息列表*/
    PHYITF_MAC_HS_QUEUE_INFO_STRU          astMacHsQueueInfoList[RRC_PHY_MAX_QUEUE_NUM];

} PHYITF_MAC_HS_CFG_INFO_STRU;

/*V3 R7_7C1 Start */
typedef struct
{
    VOS_UINT16                             usMacHsQueueId;                  /* 队列ID */
    VOS_UINT16                             usLochID;                        /* 逻辑信道ID */

} PHYITF_MAC_EHS_QUEUE_INFO_STRU;

typedef struct
{
    VOS_UINT16                              usMacEHsLochCnt;                    /* 逻辑信道个数 */
    /*MacHs PDU上报的模式,0直接上报,1:将MAC 头解析后按照mac hs再上报,
     2 将mac头解析后按照mac ehs再上报 */
    PHYITF_MAC_RPT_MODE_ENUM_UINT16         enMacHsReportMode;
    PHYITF_MAC_EHS_QUEUE_INFO_STRU          astMacEHsQueueInfoList[RRC_PHY_MAX_LOCH_NUM]; /* 保存逻辑信道和队列映射关系 */

} PHYITF_MAC_EHS_CFG_INFO_STRU;
/* V3 R7_7C1 End */

/*****************************************************************************
 结构名    : PHYITF_HSDPA_PHY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSDPA 配置结构
 *****************************************************************************/
typedef   struct
{

    PHYITF_PHYCH_TYPE_ENUM_UINT16       enPhyChannelType; /*32*/                /* _H2ASN_Skip */
    VOS_INT16                           sActiveTime;                 /*激活的时间CFN,-1表示立即激活*/
    VOS_UINT16                          usServHsPdschPrimScramCode;  /*HsPdsch服务小区的导频主扰码,取自Downlink information for each radio link,1个用户只有1个*/
    VOS_UINT16                          usNewHRnti;                  /*新的HRnti,当 BitNewHRnti 置位时有效*/
/*V3 R7_7C1 Start */
    VOS_UINT16                          usHSDSCHPhyCategory;
    VOS_UINT16                          ausReserve1;
/* V3 R7_7C1 End */

    PHYITF_HS_PDSCH_INFO_STRU           stHsPdschInfo;               /*HsPdsch 信息,当BitHsPdschInfo置位时有效*/
    PHYITF_HS_DPCCH_INFO_STRU           stHsDpcchInfo;               /*HsDpcch 信息,当BitHsDpcchInfo置位时有效*/
    PHYITF_HARQ_INFO_STRU               stHarqInfo;                  /*HARQ 信息,当BitHarqInfo置位时有效*/

    PHYITF_MAC_HS_CFG_INFO_STRU         stMacHsCfgInfo;              /*MacHs的配置信息,用于BBP解析MAC头*/

}PHYITF_HSDPA_PHY_STRU;

/*****************************************************************************
 结构名    : PHYITF_MIMO_SCPICH_DIVERSITY_PAT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : s-cpich信道mimo参数
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usChanneCode;                           /* INTEGER(0..255) */
    VOS_INT16                           sSCpichPOMimo;                          /* INTEGER(-6..0), 网络不下时，配置0值 */
}PHYITF_MIMO_SCPICH_DIVERSITY_PAT_STRU;

/*****************************************************************************
 结构名    : PHYITF_MIMO_PILOT_CFG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MIMO PILOT CFG
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                              ausReserve[1];                      /* 四字节对齐，保留 */
    PHYITF_MIMO_SCPICH_PATTERN_ENUM_UINT16  enSCpichPat;
    PHYITF_MIMO_SCPICH_DIVERSITY_PAT_STRU   stSCpichDiversityPat;
}PHYITF_MIMO_PILOT_CFG_STRU;

/*****************************************************************************
 结构名    : PHYITF_MIMO_PARAMS_STRU
 协议表格  : 10.3.6.41a MIMO parameters
 ASN.1描述 :
 结构说明  : MIMO PARAMS
 *****************************************************************************/
typedef struct
{
    PHYITF_MIMO_OPER_ENUM_UINT16            enMimoOper;                         /* MIMO 操作模式 */

    PHYITF_MIMO_N_M_RATIO_ENUM_UINT16       enMimoNMRatio;                      /* MIMO N_cqi_typeA/M_cqi ratio */
    PHYITF_MIMO_PILOT_CFG_STRU              stMimoPilotCfg;                     /* MIMO pilot configuration */

    PHYITF_BOOL_ENUM_UINT16                 enPrecodingWeightSetRestric;        /* 网络携带时配置为true，否则配置false */

    PHYITF_BOOL_ENUM_UINT16                 enSingleStreamStrict;               /* 是否限制单码流 */
}PHYITF_MIMO_PARAMS_STRU;
/*****************************************************************************
 结构名    : PHYITF_HSDPAPLUS_PHY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSDPA+ 配置结构
 *****************************************************************************/
typedef  struct
{

    PHYITF_PHYCH_TYPE_ENUM_UINT16               enPhyChannelType;               /*512*/       /* _H2ASN_Skip */
    VOS_INT16                                   sActiveTime;                    /*激活的时间CFN,-1表示立即激活*/
    VOS_UINT16                                  usServHsPdschPrimScramCode;     /*HsPdsch服务小区的导频主扰码,取自Downlink information for each radio link,1个用户只有1个*/
    VOS_UINT16                                  usNewHRnti;                     /*新的HRnti,当 BitNewHRnti 置位时有效*/

    PHYITF_HS_PDSCH_INFO_STRU                   stHsPdschInfo;                  /*HsPdsch 信息,当BitHsPdschInfo置位时有效*/
    PHYITF_HS_DPCCH_INFO_STRU                   stHsDpcchInfo;                  /*HsDpcch 信息,当BitHsDpcchInfo置位时有效*/
    PHYITF_HARQ_INFO_STRU                       stHarqInfo;                     /*HARQ 信息,当BitHarqInfo置位时有效*/

    PHYITF_MAC_EHS_CFG_INFO_STRU                stMacEHsCfgInfo;

    PHYITF_64QAM_CONFIGURED_ENUM_UINT16         en64QAMConfig;                  /* HS DSCH信道是否使用64QAM */
    PHYITF_HSDSCH_TB_SIZE_TABLE_ENUM_UINT16     enHsDschTbSizeTable;            /* HsDsch TB table 使用模式*/

    VOS_UINT16                                  usTsnBitNum;                    /* dc+mimo 时配置14, 其他配置6 */

    PHYITF_BOOL_ENUM_UINT16                     enMimoParamsValid;              /* 指示MIMO PARAMS是否有效 */

    PHYITF_MIMO_PARAMS_STRU                     stMimoParams;
}PHYITF_HSDPAPLUS_PHY_STRU;

/* V5R1 E_CELLFACH Start */
/*****************************************************************************
 结构名    : PHYITF_HS_PDSCH_INFO_PCH_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CELL_PCH/URA_PCH下HS_PDSCH 信息，下行E_CELLFACH特性新增
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usDlScramblCode;                        /* INTEGER(0..15)  OPTIONAL,辅扰码号.当usDlScramblCode取值为0表示使用主扰码,否则使用辅扰码 */

    VOS_UINT16                          usHspdschChlCode;                       /* HS-PDSCH Channelisation Code,Integer (0..15) */

    VOS_UINT16                          usNumOfPcchTrans;                       /* Number of PCCH transmissions,Integer (1..5) */

    VOS_UINT16                          usTBSizeCnt;
    VOS_UINT16                          ausTBSizeIndex[RRC_PHY_MAX_TB_SIZE_NUM];

}PHYITF_HS_PDSCH_INFO_PCH_STRU;


/*******************************************************************************
 结构名    : PHYITF_E_CELLFACH_MEAS_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : E_CELLFACH 状态下进行异频和异系统的测量时机
 25.133 8.4.2.3.2 Measurements in CELL_FACH State when HS-DSCH discontinuous reception is ongoing
*******************************************************************************/
typedef struct
{
    VOS_UINT16                                  usStartSFN;                     /* [0，4095] FACHOccasion周期里的偏移值，协议8.5.11 */
    VOS_UINT16                                  usMREP;                         /* [2，4096] frame FACHOccasion周期 */
    PHYITF_FACH_OCCASION_MEAS_TYPE_ENUM_UINT16  enMeasTypeFlag;                 /* 异频或者GSM测量指示 */
    VOS_UINT16                                  usInterRatMeasPeriod;           /* 480,CELL_FACH状态下GSM测量的周期，此值为固定常数480单位ms。 */
    VOS_UINT32                                  ulInterMeasPeriod;              /* CELL_FACH状态下异频测量的周期，单位ms */
}PHYITF_E_CELLFACH_MEAS_PARA_STRU;


/*****************************************************************************
 结构名    : PHYITF_E_CELLFACH_DRX_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usT321;                                 /*100ms,200,400,800*/
    VOS_UINT16                          usHsDschDrxCycFach;                     /* Determines the length of the DRX Cycle during DRX operation, in frames (4, 8, 16, 32)*/
    VOS_UINT16                          usHsDschDrxBurstFach;                   /* in frames:1, 2, 4, 8, 16 */

    /* TRUE means that the DRX operation can be interrupted by HS-DSCH data.
    FALSE means that the DRX operation cannot be interrupted by HS-DSCH data */
    PHYITF_BOOL_ENUM_UINT16             enDrxIntrrptHsDsch;

}PHYITF_E_CELLFACH_DRX_INFO_STRU;


/*****************************************************************************
 结构名    : PHYITF_FACH_HSDPAPLUS_PHY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : E_CELLFACH 配置HSDPA+ 配置结构
 *****************************************************************************/
typedef  struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16                   enPhyChannelType;           /* 513 */       /* _H2ASN_Skip */
    VOS_INT16                                       sActiveTime;                /* 激活的时间CFN,-1表示立即激活 */
    VOS_UINT16                                      usServHsPdschPrimScramCode; /* HsPdsch服务小区的导频主扰码,取自Downlink information for each radio link,1个用户只有1个 */

    PHYITF_BOOL_ENUM_UINT16                         enHRntiValid;               /* 指示usHRnti是否有效,当enHRntiValid =PHYITF_VALID时,usHRnti有效,当enHRntiValid = PHYITF_INVALID时，表示盲检测 */
    VOS_UINT16                                      usHRnti;                    /* HRnti,当HS_DSCH_RECEPTION_OF_CCCH_ENABLED 为TRUE,选择Common HRNTI配置WDSP */
    VOS_UINT16                                      usBcchSpecHRnti;            /* BCCH specific H-RNTI,当HRNTI不存在时,usBcchSpecHRnti物理层不读取 */
    VOS_UINT16                                      usReserve1;
    VOS_UINT16                                      usBitHsPdschInfoForPch;     /* 1:表示当前在PCH,HSDSCH paging system，0:不在PCH或不存在 */
    PHYITF_HS_PDSCH_INFO_PCH_STRU                   stHsPdschInfoForPch;        /* HSPDSCH信息，取自SIB5中HS-DSCH paging system information,E_CELLFACH新增 ;
                                                                                   当usBitHsPdschInfoForPch 为1时，WAS都填写该结构。
                                                                                   HRNTI有效时，物理层不使用该参数； HRNTI无效情况下，物理层使用该参数*/
    PHYITF_HS_SCCH_INFO_STRU                        stHsScchInfo;               /* WAS都填写该结构；无H_RNTI时，物理层HsScchInfo不使用*/
    PHYITF_HARQ_INFO_STRU                           stHarqInfo;                 /* HARQ 信息,当BitHarqInfo置位时有效 */
    PHYITF_MAC_EHS_CFG_INFO_STRU                    stMacEHsCfgInfo;

    PHYITF_HSDSCH_TB_SIZE_TABLE_ENUM_UINT16         enHsDschTbSizeTable;        /* E_CELLFACH下都是配置 octet aligned */

    PHYITF_E_CELLFACH_MEAS_PERIOD_TYPE_ENUM_UINT16  enECellFachMeasPeriodType;  /*
                                                                                0：支持CELL_FACH下DRX配置，读取下面两个结构的参数；
                                                                                1：不支持CELL_FACH下DRX，但FACH occation有效，读取测量参数；
                                                                                2：不支持CELL_FACH下DRX，且FACH occation无效，无法异频异系统进行测量
                                                                                */
    PHYITF_E_CELLFACH_MEAS_PARA_STRU                stECellFachMeasPara;        /* E_CELLFACH下测量周期 */
    PHYITF_E_CELLFACH_DRX_INFO_STRU                 stECellFachDrxInfo;         /* E_CELLFACH DXR参数 */
}PHYITF_FACH_HSDPAPLUS_PHY_STRU;
/* V5 E_CELLFACH End */



/*****************************************************************************
 结构名    : RRC_PHY_RL_SETUP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 信道建立请求消息的数据结构
             包含了要建立的信道
             使用该原语的信道为:


             PHYITF_SCCPCH_PARA_STRU
             PHYITF_PICH_STRU
             PHYITF_AICH_STRU
             PHYITF_PRACH_STRU
             PHYITF_DOWNLINK_DPCH_PARA_STRU
             PHYITF_UPLINK_DPCH_STRU
             PHYITF_HSDPA_PHY_STRU
             PHYITF_HSUPA_PHY_STRU
             PHYITF_HSDPAPLUS_PHY_STRU
             PHYITF_PHY_FACH_HSDPAPLUS
             PHYITF_E_RACH_REQ_STRU
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                          usOPID;                 /* 操作标识 */
    VOS_UINT16                          usPhyChannelNum;        /* 物理信道数 *//* _H2ASN_IE_DYNAMIC_ARRAY_EXPORT STRUTYPE:VOS_UINT16 EXPORTNAME:usH2ASNPhyChannelNum */
    VOS_UINT16                          usParaSize;             /* 参数长度 */
#if (INTERFACE_TYPE == INTERFACE_PS)
    VOS_UINT8                           aucPhyChannelPara[4];   /* 物理信道配置参数 */
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:PHYITF_RL_PARA_STRU MINIDX:1 MAXIDX:8 EXPORTNAME:usH2ASNPhyChannelNum
    ******************************************************************************************************/
#elif (INTERFACE_TYPE == INTERFACE_DSP)
    VOS_UINT16                          ausPhyChannelPara[4/2];   /* _H2ASN_Skip  物理信道配置参数 */
#endif

}RRC_PHY_RL_SETUP_REQ_STRU;


/*****************************************************************************
 结构名    : RRC_PHY_RL_MODIFY_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 信道重配置请求消息的数据结构
             包含了要重配置的信道
             使用该原语的信道为:


             PHYITF_SCCPCH_PARA_STRU
             PHYITF_PICH_STRU
             PHYITF_AICH_STRU
             PHYITF_PRACH_STRU
             PHYITF_DOWNLINK_DPCH_PARA_STRU
             PHYITF_UPLINK_DPCH_STRU
             PHYITF_HSDPA_PHY_STRU
             PHYITF_HSUPA_PHY_STRU
             PHYITF_HSDPAPLUS_PHY_STRU
             PHYITF_PHY_FACH_HSDPAPLUS
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                          usOPID;                 /* 操作标识 */
    VOS_UINT16                          usPhyChannelNum;        /* 物理信道数 *//* _H2ASN_IE_DYNAMIC_ARRAY_EXPORT STRUTYPE:VOS_UINT16 EXPORTNAME:usH2ASNPhyChannelNum */
    VOS_UINT16                          usParaSize;             /* 物理信道参数长度 */
#if (INTERFACE_TYPE == INTERFACE_PS)
    VOS_UINT8                           aucPhyChannelPara[4];   /* 物理信道参数 */
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:PHYITF_RL_PARA_STRU MINIDX:1 MAXIDX:8 EXPORTNAME:usH2ASNPhyChannelNum
    ******************************************************************************************************/
#elif (INTERFACE_TYPE == INTERFACE_DSP)
    VOS_UINT16                          ausPhyChannelPara[4/2];   /* _H2ASN_Skip 物理信道参数 */
#endif

}RRC_PHY_RL_MODIFY_REQ_STRU;


/*****************************************************************************
 结构名    : PHYITF_PHY_AFFECTED_RL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PHYITF_PHY_REL_HSUPA_INFO_STRU 中每一条释放信道链路的结构
 *****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulAffectedRlScramCode;/*受到释放影响的RL(小区)的扰码*/
    PHYITF_BOOL_ENUM_UINT16             enRelEAGCHValid;      /*指示是否释放这个RL(小区)的E_AGCH信道*/
    PHYITF_BOOL_ENUM_UINT16             enRelEHICHValid;      /*指示是否释放这个RL(小区)的E_HICH信道*/
    PHYITF_BOOL_ENUM_UINT16             enRelERGCHValid;      /*指示是否释放这个RL(小区)的E_RGCH信道*/
    VOS_UINT16                          usReserve1;

}PHYITF_PHY_AFFECTED_RL_INFO_STRU;

/*****************************************************************************
 结构名    : PHYITF_PHY_REL_HSUPA_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PHYITF_PHY_REL_CHANNEL_INFO_STRU 中使用的要释放HSUPA物理信道结构
 *****************************************************************************/
typedef struct
{
    PHYITF_BOOL_ENUM_UINT16             enRelAllValid;       /*指示是否释放所有的Hsupa物理信道*/
    VOS_UINT16                          usRelAffectedRlNum;  /*释放影响的Rl(小区)数目*/

    /*要释放的每个Rl(小区)中的信道信息*/
    PHYITF_PHY_AFFECTED_RL_INFO_STRU    astRelAffectedRlInfo[RRC_PHY_MAX_RL_NUM];

}PHYITF_PHY_REL_HSUPA_INFO_STRU;

/*****************************************************************************
 结构名    : PHYITF_PHY_REL_CHANNEL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 6720 释放物理信道结构
 *****************************************************************************/

typedef struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16       enPhyChannelType;       /* 物理信道类型 */
    VOS_INT16                           sActiveTime;            /* 激活时间 */
#if FEATURE_WCBS == FEATURE_ON
    VOS_UINT16                          usPhyChIndex;           /* 物理信道索引，如果只有一条，固定填0 */
    VOS_UINT16                          usReserv1;
#endif
    VOS_UINT16                          usFreqInfo;             /* 频率信息 */
    VOS_INT16                           sSecondScramCode;       /* 第二扰码,仅对下行物理信道有效,如果要释放Hsupa则无效*/
    VOS_UINT32                          ulScramCode;            /* 扰码,如果要释放Hsupa则无效 */

    /*  enPhyChannelType == PHYITF_PHY_UL_HSUPA 或者
        PHYITF_PHY_DL_HSUPA
        stRelHsupaExtInfo 有效，否则无效. */
    PHYITF_PHY_REL_HSUPA_INFO_STRU      stRelHsupaInfo;         /* 扩展的要释放的Hsupa信息*/

}PHYITF_PHY_REL_CHANNEL_INFO_STRU;


/*****************************************************************************
 结构名    : RRC_PHY_RL_RELEASE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 信道释放请求消息的数据结构
             包含了要释放的信道

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                      /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;         /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                          usOPID;          /* 操作标识 */
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usPhyChannelNum; /* 物理信道数 */
    PHYITF_PHY_REL_CHANNEL_INFO_STRU    astPhyChInfo[RRC_PHY_MAX_PHYCHAN_NUM];

}RRC_PHY_RL_RELEASE_REQ_STRU;


/*****************************************************************************
 结构名    : PHY_RRC_RL_EACH_CHANNEL_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 每条物理信道的证实数据结构

*****************************************************************************/

typedef struct
{
    VOS_UINT16                                  usFreqInfo;                     /* 频率信息 */
    VOS_INT16                                   sSecondScrameCode;              /* 第二扰码 */
    VOS_INT32                                   lPrimaryScrameCode;             /* 主扰码   */
    PHYITF_PHYCH_TYPE_ENUM_UINT16               enPhyChannelType;
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16    enIndicator;                    /* 配置结果,0代表成功，其它代表失败*/
    PHYITF_SYNC_NEED_ENUM_UINT16                enSyncAIndicator;               /* 是否需要同步A的指示, 只针对dpch/fdpch , 只有对应req为unkown，填真实值，非unkown，和req同步指示保持一致 其他信道一律填NO NEED。*/
    VOS_UINT16                                  usRsv1;
}PHY_RRC_RL_EACH_CHANNEL_CNF_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_RL_SETUP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 信道建立证实消息的数据结构
             每条RRC_PHY_RL_SETUP_REQ_STRU消息对应一条CNF消息

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* 操作标识 */

    VOS_UINT16                          usReserve1;             /* 字节对齐*/
    VOS_UINT16                          usPhyChannelNum;        /* 物理信道Num数*/
    PHY_RRC_RL_EACH_CHANNEL_CNF_STRU    astPhyChannelCnf[RRC_PHY_MAX_PHYCHAN_NUM];

}PHY_RRC_RL_SETUP_CNF_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_RL_MODIFY_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 信道修改证实消息的数据结构
             每条RRC_PHY_RL_MODIFY_REQ_STRU消息对应一条CNF消息

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* 操作标识*/

    VOS_UINT16                          usReserve1;             /* 字节对齐*/
    VOS_UINT16                          usPhyChannelNum;        /* 物理信道Num数*/
    PHY_RRC_RL_EACH_CHANNEL_CNF_STRU    astPhyChannelCnf[RRC_PHY_MAX_PHYCHAN_NUM]; /* 配置结果，定义同setup*/

}PHY_RRC_RL_MODIFY_CNF_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_RL_RELEASE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 信道释放证实消息的数据结构
             每条RRC_PHY_RL_RELEASE_REQ_STRU消息对应一条CNF消息

*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* 操作标识 */

    VOS_UINT16                          usReserve1;             /* 字节对齐*/
    VOS_UINT16                          usPhyChannelNum;        /* 物理信道Num数*/
    PHY_RRC_RL_EACH_CHANNEL_CNF_STRU    astPhyChannelCnf[RRC_PHY_MAX_PHYCHAN_NUM]; /* 配置结果，定义同setup*/

}PHY_RRC_RL_RELEASE_CNF_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_ACTIVATE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 激活指示消息的数据结构
             每条配置请求消息对应一条激活指示消息

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* 操作标识 */
    VOS_UINT16                          usMode;                 /* Setup,Modify,Release原语的响应 */
    VOS_UINT16                          usReserve1;             /* 字节对齐*/

    VOS_UINT16                          usCFN;                  /* 配置生效的CFN */
    VOS_UINT16                          usPhyChannelNum;        /* 物理信道Num数*/
    PHY_RRC_RL_EACH_CHANNEL_CNF_STRU    astPhyChannelCnf[RRC_PHY_MAX_PHYCHAN_NUM]; /* 配置结果，定义同setup */


}PHY_RRC_ACTIVATE_IND_STRU;


/*****************************************************************************
 结构名    : PHYITF_CCTRCH_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 码组合传输信道结构
 *****************************************************************************/
typedef struct
{
    PHYITF_CCTRCH_ID_ENUM_UINT16        enCctrchId;  /* 传输信道类型 */
    VOS_UINT16                          usParamLen;  /* 配置的CcTrch长度 */
#if (INTERFACE_TYPE == INTERFACE_PS)
    VOS_INT8                            acCcTrchParam[RRC_PHY_CCTRCH_PARA_LEN]; /* 信道参数的数据 */
#elif (INTERFACE_TYPE == INTERFACE_DSP)
    VOS_INT16                           asCcTrchParam[RRC_PHY_CCTRCH_PARA_LEN/2]; /* _H2ASN_Skip  信道参数的数据 */
#endif
}PHYITF_CCTRCH_STRU;


/*****************************************************************************
 结构名    : RRC_PHY_TRCH_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 码组合传输信道配置请求消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* 操作标识 */
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usCcTrchNum;            /* 配置的CcTrch的个数 */
    PHYITF_CCTRCH_STRU                  astCcTrch[RRC_PHY_CCTRCH_NUM];   /* 结构体 */   /* _H2ASN_Replace PHYITF_CCTRCH_PARA_STRU astCcTrch[RRC_PHY_CCTRCH_NUM]; */

}RRC_PHY_TRCH_CONFIG_REQ_STRU;


/*****************************************************************************
 结构名    : RRC_PHY_TRCH_RELEASE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 码组合传输信道释放请求消息数据结构


*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* 操作标识 */
    VOS_UINT16                          usCcTrchID;             /* 码组合通道的标识 */
    VOS_INT16                           sActiveTime;            /* 传输信道释放激活时间 -1为立即激活 */
#if FEATURE_WCBS == FEATURE_ON
    VOS_UINT16                          usCcTrchIndex;          /* 码组合传输信道索引 */
    VOS_UINT16                          usReserve;              /* 保留 */
#endif
}RRC_PHY_TRCH_RELEASE_REQ_STRU;


/*****************************************************************************
 结构名    : PHY_RRC_TRCH_CONFIG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 码组合传输信道配置证实消息数据结构


*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* 操作标识 */
    VOS_UINT16                          usCcTrchID;             /* 码组合通道的标识 */
    VOS_UINT16                          usReserve1;

}PHY_RRC_TRCH_CONFIG_CNF_STRU;


/*****************************************************************************
 结构名    : PHY_RRC_TRCH_RELEASE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 码组合传输信道释放证实消息数据结构


*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* 操作标识 */
    VOS_UINT16                          usCcTrchID;             /* 码组合通道的标识 */
    VOS_UINT16                          usReserve1;

}PHY_RRC_TRCH_RELEASE_CNF_STRU;


/*****************************************************************************
 枚举名    : PHYITF_RELALL_REASON_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : REL ALL 原因枚举
*****************************************************************************/

enum    PHYITF_RELALL_REASON_ENUM
{

    PHYITF_RELALL_SYSHO                 = 0, /*系统间切换释放所有*/
    PHYITF_RELALL_POWER_OFF             = 1, /*关机释放所有*/
    PHYITF_RELALL_OTHER                 = 2, /*其它原因RelAll*/
    PHYITF_RELALL_REASON_BUTT

};
typedef VOS_UINT16 PHYITF_RELALL_REASON_ENUM_UINT16;


/*****************************************************************************
 结构名    : PHY_RRC_RELALL_PHYCH_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 释放所有信道及其相关资源，物理层回到初时状态。
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* 操作标识 */
    PHYITF_RELALL_REASON_ENUM_UINT16    enReason;               /*释放的原因*/
    VOS_INT16                           sActiveTime;            /* 激活时间 */
}RRC_PHY_RELALL_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_RELALL_PHYCH_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 释放所有信道及其相关资源，物理层回到初时状态。
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* 操作标识 */

} PHY_RRC_RELALL_CNF_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_RELALL_PHYCH_ACTIVATE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 释放所有信道及其相关资源，激活时间到物理层上报active ind
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* 操作标识 */
    VOS_UINT16                          usCFN;                  /* 配置生效的CFN */
    VOS_UINT16                          usReserve1;             /* 四字节对齐 */
}PHY_RRC_RELALL_PHYCH_ACTIVATE_IND_STRU;

/*****************************************************************************
 结构名    : PHYITF_POWER_CONTROL_QUALITY_TARGET_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 功率控制质量目标
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTrchID;        /* 传输信道标识                */
    VOS_INT16                           sQualityValue;   /* 代表-6.3~0的值，STEP= 0.1   */

}PHYITF_POWER_CONTROL_QUALITY_TARGET_STRU;

/*****************************************************************************
 结构名    : RRC_PHY_POWER_CONTROL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 功率控制请求消息数据结构
             每条对应一条PHY_RRC_POWER_CONTROL_CNF消息

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                  enMsgID;            /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usOPID;             /* 操作标识 */
    VOS_INT16                                   sActiveTime;        /* 激活时间 */
    VOS_UINT16                                  usTrchCnt;          /* 下面TRCH的数量 */
    PHYITF_POWER_CONTROL_QUALITY_TARGET_STRU    astQualityTarget[RRC_PHY_MAX_TRCH_NUM];

}RRC_PHY_POWER_CONTROL_REQ_STRU;


/*****************************************************************************
 结构名    : PHY_RRC_POWER_CONTROL_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 功率控制证实消息数据结构


*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* 操作标识 */

}PHY_RRC_POWER_CONTROL_CNF_STRU;



/*****************************************************************************
 结构名    : PHY_RRC_SYNC_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层同步指示消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_INT16                           sNoSense;               /* not defined yet */

}PHY_RRC_SYNC_IND_STRU;


/*****************************************************************************
 结构名    : PHY_RRC_OUT_OF_SYNC_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层失步指示消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    PHYITF_BOOL_ENUM_UINT16             enSyncAAFail;           /* 是否同步AA失败 */

}PHY_RRC_OUT_OF_SYNC_IND_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_RL_FAIL_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层链路失败消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_INT16                           sNoSense;               /* not defined yet */

}PHY_RRC_RL_FAIL_IND_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_DISABLE_ULDCCH_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 是否禁止发送上行dcch
 *****************************************************************************/
typedef   struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip */

    PHYITF_BOOL_ENUM_UINT16             enDisableUlDcch;        /* VALID表示禁止发送，invalid表示可以正常发送 */

}PHY_RRC_DISABLE_ULDCCH_IND_STRU;


/*****************************************************************************
 结构名    : RRC_PHY_RESET_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 复位物理层请求消息数据结构


*****************************************************************************/
typedef struct
 {

    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve1;

}RRC_PHY_RESET_REQ_STRU;


/*****************************************************************************
 结构名    : PHY_RRC_ERROR_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层出错指示消息数据结构


*****************************************************************************/
typedef  struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_INT16                           sErrorCode;             /* not defined yet */

}PHY_RRC_ERROR_IND_STRU;



/*****************************************************************************
 结构名    : PHYITF_CELL_SEARCH_FREQ_LIST_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 小区搜索离散频点信息，指明有多少个离散频点要搜索
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                              usFreqCnt;                       /* 频率列表中频点的数目,为0则表示没有 */
    VOS_UINT16                              usReserve1;
    VOS_UINT16                              ausFreqList[RRC_PHY_MAX_FREQ_NUM];/* 频率列表中具体的频点信息,每个值为实际频率值乘5*/

}PHYITF_CELL_SEARCH_FREQ_LIST_INFO_STRU;


/**************************小区测量相关的配置**************************************************/

/****************************能量测量数据结构***********************************/

/*****************************************************************************
 结构名    : PHYITF_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 小区信息
 *****************************************************************************/
typedef struct
{
    VOS_INT16                           sCellID;               /* 小区的ID */
    VOS_UINT16                          usPrimaryScramCode;    /* 小区的主扰码 */
    VOS_UINT16                          usRefTimeDifference;

    VOS_UINT16                          usReadSFNInd;           /* 是否需要读出SFN */
    VOS_UINT16                          usSFNSFNTimeDiffInd;    /* 否需要测量SFN -SFN Time Difference */
    VOS_UINT16                          usOFFInd;               /* 是否需要测量OFF */
    VOS_UINT16                          usTMInd;                /* 是否需要测量TM  */

    /* R准则计算使用的偏移量。遵循以下规则：
 　　  主小区测量量是EC\N０表示：ucQHyst2
       主小区测量量是RSCP表示：  ucQHyst1
　　   邻小区测量量是EC\N０表示：sQoffset2SN
　　　 邻小区测量量是RSCP表示：  sQoffset1SN */

    VOS_INT16                           sOffset1;
    VOS_INT16                           sOffset2;

    VOS_INT16                           sQqualmin;
    VOS_INT16                           sQrxlevmincompensation;

    VOS_UINT16                          usTDIndicator;          /*1表示使用发分集，0表示不使用发分集*/


}PHYITF_CELL_INFO_STRU;

/*****************************************************************************
 枚举名    : PHYITF_RAT_PRI_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum    PHYITF_RAT_PRI_ENUM
{
    PHYITF_RAT_PRI_NULL_PRI     = 0,                                            /* 对应接入技术不支持 */
    PHYITF_RAT_PRI_LOW          = 1,                                            /* 对应接入技术为低优先级 */
    PHYITF_RAT_PRI_MID          = 2,                                            /* 对应接入技术为中优先级 */
    PHYITF_RAT_PRI_HIGH         = 3,                                            /* 对应接入技术为高优先级 */

    PHYITF_RAT_PRI_BUTT
};
typedef VOS_UINT16 PHYITF_RAT_PRI_ENUM_UINT16;


/*****************************************************************************
 结构名    : PHYITF_CELL_ADJUGE_PARA_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_PHY_IDLE_MEASURE_REQ_STRU 和
             PHYITF_CELL_SEL_MEASURE_STRU  中小区判决参数
 *****************************************************************************/
typedef struct
{

    PHYITF_CELL_ADJUGE_TYPE_ENUM_UINT16  enCellType;
    PHYITF_CELL_SEARCH_FLAG_ENUM_UINT16  enSSearchFlag ;
    VOS_INT16                            sSSearch;
    PHYITF_MEAS_QUANTITY_ENUM_UINT16     enMeasQuantity;
    PHYITF_SERVE_CELL_STATUS_ENUM_UINT16 enServStatus;
    VOS_INT16                            sMeasStopThr;                          /* 高于该门限，则停测量 */
    VOS_UINT16                           usNlayers;                             /* 所有高优先级W异频,LTE频点和GSM频点组总个数 */
    PHYITF_BOOL_ENUM_UINT16              enHighPriMeasFlg;                      /* 高优先级测量标记 ,PHYITF_VALID表示要做高优先级测量,PHYITF_INVALID表示测量H+L */
    PHYITF_RAT_PRI_ENUM_UINT16           enWcdmaPri;                             /* WCDMA优先级 */
    PHYITF_RAT_PRI_ENUM_UINT16           enGsmPri;                               /* GSM优先级 */
    PHYITF_RAT_PRI_ENUM_UINT16           enLtePri;



    /* >Sprioritysearch1 MP Integer (0..62 by step of 2) dB REL-8 */
    VOS_UINT16                           usPriSearch1;                           /* [0~62] RSCP, dB */

    /* >Sprioritysearch2 MD Integer (0..7 by step of 1) dB, default value is 0 REL-8 */
    VOS_UINT16                           usPriSearch2;                           /* [0~7] dB, default value is 0 */

    PHYITF_CELL_SEARCH_FLAG_ENUM_UINT16  enPriSearchFlg ;
}PHYITF_CELL_ADJUGE_PARA_INFO_STRU;


/*****************************************************************************
 结构名    : PHYITF_INTRA_FREQ_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 同频小区信息
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;                                             /* 频点的频率信息            */

    VOS_UINT16                          usFreqBandNo;                                           /* 频段号:1,2,3,4,5,6*/
    VOS_UINT16                          usTxRxFreqSeparation;                                   /* 收发频差*/
    VOS_UINT16                          usFreqPriority;                         /* 频点优先级 */
    VOS_UINT16                          usReserve1;

    VOS_UINT16                          usIntraFreqCellNum;                     /* 需监视同频临近小区的数目  */
    PHYITF_CELL_INFO_STRU               astIntraFreqCell[RRC_PHY_MAX_INTRA_FREQ_CELL_NUM]; /* 同频临近小区列表的信息    */

}PHYITF_INTRA_FREQ_CELL_INFO_STRU;


/*****************************************************************************
 结构名    : PHYITF_INTER_FREQ_CELL_INFO_ITEM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 异频小区信元
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;   /* 频点的频率信息 */

    VOS_UINT16                          usFreqBandNo;                                           /* 频段号:1,2,3,4,5,6*/
    VOS_UINT16                          usTxRxFreqSeparation;                                   /* 收发频差*/
    VOS_UINT16                          usFreqPriority;                         /* 当W为从模时，此频点优先级固定为0. */
    VOS_UINT16                          usDetectedCellMeasureInd;                               /* 是否需要测量属于Detected集的小区 */

    VOS_UINT16                          usCellNum;                                              /* 一个频点下的小区数目 */
    PHYITF_CELL_INFO_STRU               astInterCellInfo[RRC_PHY_MAX_EACH_FREQ_CELL_NUM];    /* 小区的信息               */

}PHYITF_INTER_FREQ_CELL_INFO_ITEM_STRU;


/*****************************************************************************
 结构名    : PHYITF_INTER_FREQ_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 异频小区信息
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                              usInterFreqNum;  /* 需监视的异频频点数目       */
    VOS_UINT16                              usReserve1;      /* */
    PHYITF_INTER_FREQ_CELL_INFO_ITEM_STRU   astInterFreqCell[RRC_PHY_MAX_ADDITIONAL_CARRIER_NUM];

}PHYITF_INTER_FREQ_CELL_INFO_STRU;

/*****************************************************************************
 结构名    : PHYITF_INTER_RAT_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 异系统小区信息
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usReserve1[2];
}PHYITF_INTER_RAT_CELL_INFO_STRU;

/*****************************************************************************
 结构名    : PHYITF_LTE_FREQ_INFO_ITEM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : W为主模时，测量LTE邻区信息

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreq;                                 /* LTE频点号 */
    VOS_UINT16                          usFreqPriority;                         /* LTE频点优先级信息 , 0~9 */
}PHYITF_LTE_FREQ_INFO_ITEM_STRU;

/*****************************************************************************
 结构名    : PHYITF_INTER_RAT_LTE_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : W为主模时，测量LTE邻区信息

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqNum;     /*需要测量的小区数量*/
    VOS_UINT16                          usReserve1;
    PHYITF_LTE_FREQ_INFO_ITEM_STRU      astLteFreqInfo[RRC_PHY_MAX_INTER_RAT_LTE_FREQ];

}PHYITF_INTER_RAT_LTE_CELL_INFO_STRU;

/*****************************************************************************
 结构名    : RRC_PHY_IDLE_MEASURE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IDLE状态测量请求消息数据结构

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usOPID;                 /* 操作标识 */
    PHYITF_MEASURE_COMMAND_ENUM_UINT16          enCommand;              /* REQ的命令 */
    VOS_UINT16                                  usRelMeasTypeMask;      /* 如果是REL消息，则在这里指明需要释放的测量类型 */
    PHYITF_MODIFY_TYPE_ENUM_UINT16              enModifyType;           /* 重配置类型:重配置测量列表和测量参数, 仅重配置测量参数两种类型 */
    PHYITF_HIGH_RATE_FLAG_ENUM_UINT16           enHighRateFlag;         /* 是否是高速的标志，初始值，HCS小区或者网络携带参数时都填写为TRUE */
    PHYITF_CELL_ADJUGE_PARA_INFO_STRU           stCellParaInfo;
    PHYITF_MEAS_REQ_END_FLAG_ENUM_UINT16        usMeaReqEndFlag;        /* 测量请求结束标志 */  /* _H2ASN_IeChoice_Export PHYITF_MEAS_REQ_END_FLAG_ENUM_UINT16 */
    PHYITF_IDLE_MEAS_TYPE_ENUM_UINT16           enMeasTypeChoice;       /* 测量类型 */ /* _H2ASN_IeChoice_Export PHYITF_IDLE_MEAS_TYPE_ENUM_UINT16 */

    union                                                                   /*_H2ASN_Skip*/
    {/*_H2ASN_Skip*/
        PHYITF_INTRA_FREQ_CELL_INFO_STRU    stIntraFreqCellEntity;  /* _H2ASN_Skip 同频测量信息 */
        PHYITF_INTER_FREQ_CELL_INFO_STRU    stInterFreqCellEntity;  /* _H2ASN_Skip 异频测量信息 */
        PHYITF_INTER_RAT_CELL_INFO_STRU     stInterRatCellEntity;   /* _H2ASN_Skip 异系统间测量信息 */
        PHYITF_INTER_RAT_LTE_CELL_INFO_STRU stInterRatLteCellEntity;            /* W为主模时，测量LTE邻区 */
        /******************************************************************************************************
                _H2ASN_IeChoice_When        PHYITF_IDLE_MEAS_TYPE_ENUM_UINT16
        ******************************************************************************************************/
    }u;/*_H2ASN_Skip*/
}RRC_PHY_IDLE_MEASURE_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_IDLE_MEASURE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IDLE状态测量证实消息数据结构

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* 操作标识 */

}PHY_RRC_IDLE_MEASURE_CNF_STRU;


/*****************************************************************************
 结构名    : PHYITF_CELL_MEASURE_RESULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 每个小区的测量结果信息
 *****************************************************************************/
typedef struct
{
    VOS_INT16                           sCellID;                                /* 小区的ID                                 */
    VOS_UINT16                          usPrimaryScramCode;                     /* 小区的主扰码                             */
    VOS_INT32                           lSFNSFNTimeDifference;                  /* 本小区和主小区的SFN差                    */
    VOS_INT16                           sCpichRscp;                             /* CPICH RSCP测量值                         */
    VOS_INT16                           sCpichEcN0;                             /* CPICH EcN0测量值                         */
    VOS_INT16                           sOFF;                                   /* OFF测量结果                              */
    VOS_UINT16                          usSfn;                                  /* 当前的SFN,只用于向后台报告               */
    VOS_INT32                           lTM;                                    /* TM测量结果 */

} PHYITF_CELL_MEASURE_RESULT_STRU;

/*****************************************************************************
 结构名    : PHYITF_INTRA_FREQ_RESULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 同频小区测量结果
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;             /* 频率信息 */
    VOS_INT16                           sCarrierRSSI;           /* UtraCarrierRSSI结果 */
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usIntraFreqCellNum;    /* 频内小区的个数 */
    PHYITF_CELL_MEASURE_RESULT_STRU     astIntraFreqCell[PHY_RRC_MAX_REPORT_INTRA_FREQ_CELL_NUM];   /* 频内小区的测量结果                      */

} PHYITF_INTRA_FREQ_RESULT_STRU;

/*****************************************************************************
 结构名    : PHYITF_INTER_FREQ_RESULT_ITEM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 异频小区测量结果信元
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;   /* 频率信息*/
    VOS_INT16                           sCarrierRSSI; /* UtraCarrierRSSI测量值 */
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usCellNum;    /* 一个频点上上报的小区个数 */
    PHYITF_CELL_MEASURE_RESULT_STRU     astInterFreqCell[PHY_RRC_MAX_REPORT_EACH_FREQ_CELL_NUM];     /* 频间小区的测量结果                       */

} PHYITF_INTER_FREQ_RESULT_ITEM_STRU;

/*****************************************************************************
 结构名    : PHYITF_INTER_FREQ_RESULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 异频小区测量结果
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usInterFreqNum; /* 报告中频间频点的个数 */
    VOS_UINT16                          usReserve1;
    PHYITF_INTER_FREQ_RESULT_ITEM_STRU  astInterFreqReport[RRC_PHY_MAX_ADDITIONAL_CARRIER_NUM];

} PHYITF_INTER_FREQ_RESULT_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_IDLE_MEASURE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IDLE状态测量指示消息结构

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* 操作标识 */

    #define     PHYITF_IDLE_MEAS_IND_SERV_CELL_CHOSEN       0
    #define     PHYITF_IDLE_MEAS_IND_INTRA_CELL_CHOSEN      1
    #define     PHYITF_IDLE_MEAS_IND_INTER_CELL_CHOSEN      2

    VOS_UINT16                              usReserve1;
    VOS_UINT16                              usReportTypeChoice;     /* 本次报告的有效类型*/

    union
    {
        PHYITF_CELL_MEASURE_RESULT_STRU     stServingCellResult;    /* 当前服务小区的测量结果 */
        PHYITF_INTRA_FREQ_RESULT_STRU       stIntraFreqResult;      /* 同频小区的测量结果 */
        PHYITF_INTER_FREQ_RESULT_STRU       stInterFreqResult;      /* 异频小区的测量结果 */
    }unReportResult;
}PHY_RRC_IDLE_MEASURE_IND_STRU;


/*****************************************************************************
 结构名    : PHYITF_CELL_SEL_MEASURE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 连接状态下的小区选择的测量结构
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCurrentStatus;          /* 当前UE状态 */
    VOS_UINT16                          usReserve1;
    PHYITF_CELL_ADJUGE_PARA_INFO_STRU   stCellParaInfo;
    PHYITF_MEAS_REQ_END_FLAG_ENUM_UINT16   usMeaReqEndFlag;              /* 测量请求结束标志 */  /* _H2ASN_IeChoice_Export PHYITF_MEAS_REQ_END_FLAG_ENUM_UINT16 */
    PHYITF_CONN_MEAS_TYPE_ENUM_UINT16           enMeasTypeChoice;             /* 测量类型 */  /* _H2ASN_IeChoice_Export PHYITF_CONN_MEAS_TYPE_ENUM_UINT16 */
    union                                                                     /* _H2ASN_Skip */
    {                                                                         /* _H2ASN_Skip */
        PHYITF_INTRA_FREQ_CELL_INFO_STRU    stIntraFreqCellEntity;    /* _H2ASN_Skip 频内测量信息 */
        PHYITF_INTER_FREQ_CELL_INFO_STRU    stInterFreqCellEntity;    /* _H2ASN_Skip 频间测量信息 */
        PHYITF_INTER_RAT_CELL_INFO_STRU     stInterRatCellEntity;     /* _H2ASN_Skip 异系统GSM测量信息 */
        PHYITF_INTER_RAT_LTE_CELL_INFO_STRU stInterRatLteCellEntity;  /* W为主模PCH态时，测量LTE邻区 */
    /******************************************************************************************************
            _H2ASN_IeChoice_When        PHYITF_CONN_MEAS_TYPE_ENUM_UINT16
    ******************************************************************************************************/
    }u;/* _H2ASN_Skip */
}PHYITF_CELL_SEL_MEASURE_STRU;


/*****************************************************************************
 结构名    : PHYITF_INTRA_FREQ_MEASURE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 连接状态下的同频测量结构
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;                                             /* 频率信息 */

    VOS_UINT16                          usFreqBandNo;                                           /* 频段号:1,2,3,4,5,6*/
    VOS_UINT16                          usTxRxFreqSeparation;                                   /* 收发频差,该变量目前PHY没有使用*/

    VOS_UINT16                          usDetectedCellMeasureInd;                               /* 是否需要测量属于Detected集的小区 */
    VOS_UINT16                          usDetectedCellSynInfoInd;                               /* 检测集是否需要上报同步信息,如果要求上报该值设为1，否则为0 */
    VOS_UINT16                          usIntraAllCellListNum;                                  /* UE知道的所有小区的数目*/
    PHYITF_CELL_INFO_STRU               astIntraAllCellList[RRC_PHY_MAX_INTRA_FREQ_CELL_NUM];   /* UE知道的所有小区的信息列表 */
}PHYITF_INTRA_FREQ_MEASURE_STRU;

/*****************************************************************************
 结构名    : PHYITF_ADJACENT_FREQ_MEASURE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 连接状态下的邻频测量结构
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;                                             /* 频率信息 */

    VOS_UINT16                          usFreqBandNo;                                           /* 频段号:1,2,3,4,5,6*/
    VOS_UINT16                          usTxRxFreqSeparation;                                   /* 收发频差,该变量目前PHY没有使用 */

    VOS_UINT16                          usDetectedCellMeasureInd;                               /* 是否需要测量属于Detected集的小区 */
    VOS_UINT16                          usDetectedCellSynInfoInd;                               /* 检测集是否需要上报同步信息,如果要求上报该值设为1，否则为0 */

    VOS_UINT16                          usIntraInterAllCellListNum;                             /* UE知道的Intra Freq和Inter Freq都需要测量小区的数目,小区放在astAdjacentFreqCellList组数最前端，
                                                                                                   PHY需要将这部分小区在同频和异频测量IND中上报 */

    VOS_UINT16                          usIntraAllCellListNum;                                  /* UE知道的Intra Freq需要测量小区的数目,而Inter Freq不需要测量的小区的数目，小区在astAdjacentFreqCellList组数
                                                                                                   挨着usIntraInterAllCellListNum之后存放，PHY需要将这部分小区在同频测量IND中上报 */

    VOS_UINT16                          usInterAllCellListNum;                                  /* UE知道的Inter Freq需要测量小区的数目,而Intra Freq不需要测量的小区的数目，小区在astAdjacentFreqCellList组数
                                                                                                   挨着usIntraAllCellListNum之后存放,PHY需要将这部分小区在异频测量IND中上报 */

    PHYITF_CELL_INFO_STRU               astAdjacentFreqCellList[RRC_PHY_MAX_ADJACENT_FREQ_CELL_NUM];     /* UE知道所有需要测量小区的信息列表，按照Intra&Inter Freq、Intra Freq、Inter Freq 顺序紧凑排列*/
}PHYITF_ADJACENT_FREQ_MEASURE_STRU;


/*****************************************************************************
 结构名    : PHYITF_INTER_FREQ_ALL_CELL_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 连接状态下要测量的所有异频小区列表
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;                                             /* 异频的频点信息 */

    VOS_UINT16                          usFreqBandNo;                                           /* 频段号:1,2,3,4,5,6*/
    VOS_UINT16                          usTxRxFreqSeparation;                                   /* 收发频差*/

    VOS_UINT16                          usInterFreqCellNum;                                     /* 此频点下的小区的数目 */

    PHYITF_CELL_INFO_STRU               astInterFreqCellInfo[RRC_PHY_MAX_EACH_FREQ_CELL_NUM];   /* 一个频点下的所有小区的信息 */

}PHYITF_INTER_FREQ_ALL_CELL_LIST_STRU;

/*****************************************************************************
 结构名    : PHYITF_INTER_FREQ_MEASURE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 连接状态下的异频测量结构
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMeasPeriod;        /* 测量周期 */
    VOS_UINT16                          usMinIntraCellNum;   /* 需要测量的频内小区的数目 */
    VOS_UINT16                          usInterFreqNum;      /* UE知道的异频频点的数目 */
    VOS_UINT16                          usReserve1;

    PHYITF_INTER_FREQ_ALL_CELL_LIST_STRU astInterAllCellList[RRC_PHY_MAX_ADDITIONAL_CARRIER_NUM];

}PHYITF_INTER_FREQ_MEASURE_STRU;

/*****************************************************************************
 结构名    : RRC_PHYITF_CONNECT_MEASURE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 连接状态测量请求消息数据结构

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip */
    RRC_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                /* 原语类型 */ /*_H2ASN_Skip */
    VOS_UINT16                                  usOPID;                 /* 操作标识 */
    PHYITF_MEASURE_COMMAND_ENUM_UINT16          enCommand;              /* 测量命令,0:释放，1:建立 */
    VOS_UINT16                                  usRelMeasTypeMask;      /* 如果是REL消息，则在这里指明需要释放的测量类型 */
    PHYITF_MODIFY_TYPE_ENUM_UINT16              enModifyType;           /* 重配置类型:重配置测量列表和测量参数, 仅重配置测量参数两种类型 */
    PHYITF_HIGH_RATE_FLAG_ENUM_UINT16           enHighRateFlag;         /* 是否是高速的标志，初始值，HCS小区或者网络携带参数时都填写为TRUE，连接态只在PCH下有效 */
    VOS_UINT16                                  usReserve1;

    PHYITF_CONNECT_MEAS_REQ_TYPE_ENUM_UINT16    enMeasTypeChoice;  /* 连接状态下测量请求的类型 */   /* _H2ASN_IeChoice_Export PHYITF_CONNECT_MEAS_REQ_TYPE_ENUM_UINT16 */

    /* 测量信息 */
    union                                                                                                   /* _H2ASN_Skip */
    {                                                                                                       /* _H2ASN_Skip */
        PHYITF_INTRA_FREQ_MEASURE_STRU      stIntraFreqMeasureEntity;               /* 频内测量的参数     */    /* _H2ASN_Skip */
        PHYITF_INTER_FREQ_MEASURE_STRU      stInterFreqMeasureEntity;               /* 频间测量的参数     */    /* _H2ASN_Skip */
        VOS_UINT16                          usRptPeriod;                            /* 内部测量上报周期   */    /* _H2ASN_Skip */
        PHYITF_CELL_SEL_MEASURE_STRU        stCellSelMeasureEntity;                 /* 小区监视测量的参数 */    /* _H2ASN_Skip */
        PHYITF_INTER_RAT_CELL_INFO_STRU     stInterRatMeasureEntity;                /* 系统间测量的参数   */    /* _H2ASN_Skip */
        PHYITF_ADJACENT_FREQ_MEASURE_STRU   stAdjacentFreqMeasureEntity;            /* 邻频测量的参数     */    /* _H2ASN_Skip */
        PHYITF_INTER_RAT_LTE_CELL_INFO_STRU     stInterRatLteCellEntity;        /* W为主模时，测量LTE邻区 */
        /******************************************************************************************************
            _H2ASN_IeChoice_When        PHYITF_CONNECT_MEAS_REQ_TYPE_ENUM_UINT16
        ******************************************************************************************************/
    }u;                                                                         /* _H2ASN_Skip */
}RRC_PHYITF_CONNECT_MEASURE_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_CONNECT_MEASURE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 连接状态测量证实消息数据结构

*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* 操作标识 */

}PHY_RRC_CONNECT_MEASURE_CNF_STRU;



/*****************************************************************************
 结构名    : PHYITF_CELL_SEL_REPORT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 连接状态下的小区选择的测量报告
 *****************************************************************************/
typedef struct
{
    #define PHYITF_CELL_SEL_REPORT_SEV_CELL_CHOSEN          0
    #define PHYITF_CELL_SEL_REPORT_INTRA_CELL_CHOSEN        1
    #define PHYITF_CELL_SEL_REPORT_INTER_CELL_CHOSEN        2

    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usReportTypeChoice;  /* 报告的有效类型 */

    /* 上报信息的共同体 */
    union
    {
        PHYITF_CELL_MEASURE_RESULT_STRU stServingCellResult; /* 主小区的测量结果   */
        PHYITF_INTRA_FREQ_RESULT_STRU   stIntraFreqResult;   /* 频内小区的测量结果 */
        PHYITF_INTER_FREQ_RESULT_STRU   stInterFreqResult;   /* 频间小区的测量结果 */
    }unReportResult;

}PHYITF_CELL_SEL_REPORT_STRU;


/*****************************************************************************
 结构名    : PHYITF_INTRA_FREQ_REPORT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 连接状态下的同频测量报告
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usReportCellNum;                        /* 报告中包含的小区数目 */

    VOS_UINT16                          usReportSecUlFreqCellNum;               /* 报告中包含的SecULFreq小区数目 */

    PHYITF_CELL_MEASURE_RESULT_STRU     astReportCellResult[PHY_RRC_MAX_REPORT_INTRA_FREQ_CELL_NUM]; /* 小区的测量结果 */

    PHYITF_CELL_MEASURE_RESULT_STRU     astReportSecUlFreqCellResult[PHY_RRC_MAX_REPORT_SEC_UL_FREQ_CELL_NUM]; /* SecULFreq小区的测量结果 */

}PHYITF_INTRA_FREQ_REPORT_STRU;

/*****************************************************************************
 结构名    : PHYITF_INTER_FREQ_REPORT_ITEM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 连接状态下的异频测量报告信元
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;         /* 频率信息 */

    VOS_INT16                           sCarrierRSSI;       /* UtraCarrierRSSI测量值 */

    VOS_UINT16                          usInterFreqCellNum; /* 此频点下的小区的数目  */

    VOS_UINT16                          usReserve1;

    PHYITF_CELL_MEASURE_RESULT_STRU     astInterFreqCell[PHY_RRC_MAX_REPORT_EACH_FREQ_CELL_NUM];     /* 频间小区的测量结果 */

}PHYITF_INTER_FREQ_REPORT_ITEM_STRU;

/*****************************************************************************
 结构名    : PHYITF_INTER_FREQ_REPORT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 连接状态下的异频测量报告
 *****************************************************************************/
typedef struct

{
    VOS_UINT16                          usInterFreqNum;                         /* 报告中包含的频点数目 */

    VOS_UINT16                          usReserve1;

    PHYITF_INTER_FREQ_REPORT_ITEM_STRU  astInterFreqReport[RRC_PHY_MAX_ADDITIONAL_CARRIER_NUM];

}PHYITF_INTER_FREQ_REPORT_STRU;

/*****************************************************************************
 结构名    : PHYITF_INTERNAL_REPORT_RXTX_TIME_DIFFS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 连接状态下的内部测量的Rx_Tx差
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usRLPrimaryScramCode;    /* RL的主扰码      */

    VOS_UINT16                          usRxTxTimeDifference;    /* Rx和Tx的时间差  */
}PHYITF_INTERNAL_REPORT_RXTX_TIME_DIFFS_STRU;


/*****************************************************************************
 结构名    : PHYITF_INTERNAL_REPORT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 连接状态下的内部测量报告
 *****************************************************************************/
typedef struct
{
    VOS_INT16                                       sTxPower[RRC_PHY_MAX_SLOT_PLUS1_NUM];   /* UE发射功率,0~14个时隙上报量每帧上报一次  */

    VOS_INT16                                       sTxMaxPower;                            /*实际的最大上行发射功率*/

    VOS_INT16                                       sTxMinPower;                            /* 实际的最小上行发射功率*/

    VOS_INT16                                       sUtraCarrierRSSI;                       /* 载波的RSSI测量结果   */

    VOS_UINT16                                      usRLNum;                                /* 测量的无线连接的数目 */

    PHYITF_INTERNAL_REPORT_RXTX_TIME_DIFFS_STRU     astRxTxTimeDiffS[RRC_PHY_MAX_RL_NUM];   /* Rx和Tx的时间差数组   */

}PHYITF_INTERNAL_REPORT_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_CONNECT_MEASURE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 连接状态测量指示消息数据结构

*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                  enMsgID;            /*_H2ASN_Skip*/   /* 原语类型 */
    VOS_UINT16                                  usOPID;             /* 操作标识 */

    VOS_UINT16                                  usHighRailwayMode;  /* 高铁模式指示，在本频测量报告时有效，1为高铁模式，0为普通模式 */
    PHYITF_CONNECT_MEAS_IND_TYPE_ENUM_UINT16    enMeasTypeChoice;   /* 测量报告的类型 */   /* _H2ASN_IeChoice_Export PHYITF_CONNECT_MEAS_IND_TYPE_ENUM_UINT16 */
    union                                                                       /* _H2ASN_Skip */
    {                                                                           /* _H2ASN_Skip */
        PHYITF_INTRA_FREQ_REPORT_STRU           stIntraFreqRpt;                 /* _H2ASN_Skip */
        PHYITF_INTER_FREQ_REPORT_STRU           stInterFreqRpt;                 /* _H2ASN_Skip */
        PHYITF_CELL_SEL_REPORT_STRU             stCellSelRpt;
        /******************************************************************************************************
            _H2ASN_IeChoice_When        PHYITF_CONNECT_MEAS_IND_TYPE_ENUM_UINT16
        ******************************************************************************************************/
    }u;                                                                         /* _H2ASN_Skip */
}PHY_RRC_CONNECT_MEASURE_IND_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_AFC_LOCK_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : AFC锁定相关信息上报

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;            /* 原语类型*/   /*_H2ASN_Skip*/
    PHYITF_BOOL_ENUM_UINT16             enAfcLockFlag;
    VOS_UINT16                          usAfcCurrVal;
    VOS_INT16                           sProtectTemp;        /* 温保参数 */

} PHY_RRC_AFC_LOCK_IND_STRU;

/*****************************************************************************
 结构名    : RRC_PHY_DPCH_COMPRESSED_MODE_STATUS_CHANGE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 压模状态改变请求消息数据结构

*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;            /* 原语类型*/   /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;             /* 操作标识 */
    VOS_UINT16                          usParaLen;          /* 参数的长度 */
    VOS_UINT16                          usReserve1;
#if (INTERFACE_TYPE == INTERFACE_PS)
    VOS_UINT8                           aucCompModeChgPara[4]; /* 配置参数的第一个字节 */   /*_H2ASN_Replace PHYITF_COMP_MODE_CHG_PARA_STRU */
#elif (INTERFACE_TYPE == INTERFACE_DSP)
    VOS_UINT16                          ausCompModeChgPara[4/2]; /* _H2ASN_Skip 配置参数的第一个字节 */
#endif
}RRC_PHY_DPCH_COMPRESSED_MODE_STATUS_CHANGE_REQ_STRU;


/*****************************************************************************
 结构名    : PHY_RRC_DPCH_COMPRESSED_MODE_STATUS_CHANGE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 压模状态改变证实消息数据结构

*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                           /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                             /* 原语类型*/   /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                              /* 操作标识 */
    PHYITF_DPCH_COMPRESSED_MODE_STATUS_CHANGE_RESULT_ENUM_UINT16 enResult;   /* 压模配置结果 */
    VOS_UINT16                          usReserve1;

} PHY_RRC_DPCH_COMPRESSED_MODE_STATUS_CHANGE_CNF_STRU;



/*****************************************************************************
 结构名    : PHYITF_DPCH_COMPRESSED_MODE_TGPS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 压模指示PHY_RRC_DPCH_COMPRESSED_MODE_STATUS_IND_STRU 中的结构
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTgpsId;         /* TGPS ID    */
    VOS_UINT16                          usTgpsStatus;     /* TGPS的状态 */

}PHYITF_DPCH_COMPRESSED_MODE_TGPS_STRU;


/*****************************************************************************
 结构名    : PHY_RRC_DPCH_COMPRESSED_MODE_STATUS_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 压模状态状态指示消息数据结构

*****************************************************************************/
typedef struct
{

    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16              enMsgID;        /* 原语类型*/   /*_H2ASN_Skip*/
    VOS_UINT16                              usTgpsCnt;      /* 变更的TGPS个数 */
    VOS_UINT16                              usOverlapTgpsCnt;   /* 发生重叠的TGPS的个数 */
    VOS_UINT16                              usReserve1;

    VOS_UINT16                              ausOverlapTgpsId[RRC_PHY_MAX_TGPS];  /* 发生重叠的TGPS的ID */
    PHYITF_DPCH_COMPRESSED_MODE_TGPS_STRU   astTgps[RRC_PHY_MAX_TGPS];

}PHY_RRC_DPCH_COMPRESSED_MODE_STATUS_IND_STRU;




/**************************************质量测量数据结构*******************************/
/*****************************************************************************
 结构名    : PHYITF_QUA_PERIODIC_CRITERIA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 质量测量中的周期报告标准
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usInterval;
    VOS_UINT16                          usReportMount;

}PHYITF_QUA_PERIODIC_CRITERIA_STRU;


/*****************************************************************************
 结构名    : PHYITF_QUA_EVENT_TRCH_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 事件标准中的每条传输信道信息
 *****************************************************************************/
typedef struct
{
     VOS_UINT16                         usTrCHID;
     VOS_UINT16                         usTotalCRC;
     VOS_UINT16                         usBadCRC;
     VOS_UINT16                         usPendingTime;

}PHYITF_QUA_EVENT_TRCH_STRU;

/*****************************************************************************
 结构名    : PHYITF_QUA_PERIODIC_CRITERIA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 质量测量中的事件报告标准
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEventTrCHNum;
    VOS_UINT16                          usReserve1;
    PHYITF_QUA_EVENT_TRCH_STRU          astEventTrCH[RRC_PHY_MAX_TRCH_NUM];

}PHYITF_QUA_EVENT_CRITERIA_STRU;

/*****************************************************************************
 结构名    : RRC_PHY_QUALITY_MEASUREMENT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 质量测量请求消息数据结构。
             目前6720版本物理层质量测量能力如下:
             (1) BBP可以同时对最多8个传输信道进行周期性测量，其测量周期必须一致；
             (2) BBP可以同时对最多3个传输信道进行测量事件评估；
             (3) 上述周期性测量和事件评估测量可以同时存在；
             (4) 质量测量事件评估，放在PHY层做，比较合适，准确性高；

             综合上述质量测量支持能力，UE需要进行下述处理:
             (1) UTRAN->RRC: 新建质量测量时，需要检查判断当前是否存在相同报告准
             则的质量测量：
                 (1.1) 如果已经存在相同报告准则的质量测量，则拒绝新的质量测量，
                 向网络侧回FAILURE，原因值为UE不支持；
                 (1.2) 如果不存在相同报告准则的质量测量，则新建该质量测量。
             根据这个原则，RM可同时维护三个质量测量对象，其中之一的报告准则为周
             期报告，另一个的报告准则为事件报告，还可以维护一个报告准则为不报告
             模式的。

             (2) UTRAN->RRC: 新建质量测量，报告准则为周期上报时，RRC->PHY: 新建
             质量测量，报告准则填写为周期报告，在stPeriodic信元中指示上报周期和
             上报次数，并通过usMonitorTrchNum和ausMonitorTrchID信元指示物理层需
             要测量和上报的TrCH ID。

             (3) UTRAN->RRC: 新建质量测量，报告准则为事件上报时，RRC->PHY: 新建
             质量测量，报告准则填写为事件报告，在stEvent信元中指示需要进行事件评
             估的TrCH ID，和对应的事件评估参数。

             (4) RRC->PHY: 如果物理层当前已经存在质量测量，其上报准则为周期报告:
                 (4.1) RRC再次指示物理层新建上报准则为事件报告的质量测量，物理层
                 接受该事件报告准则的质量测量，并保证原先周期报告准则的质量测量
                 不受影响。之后，物理层继续上报质量测量结果，并指示是那种报告准
                 则的测量结果。
                 (4.2) RRC再次指示物理层新建上报准则为周期报告的质量测量，物理层
                 使用新的配置数据覆盖原先的质量测量，之后，物理层继续上报质量测
                 量结果。

             (5) RRC->PHY: 如果物理层当前已经存在质量测量，其上报准则为事件报告:
                 (5.1) RRC再次指示物理层新建上报准则为周期报告的质量测量，物理层
                 接受该周期报告准则的质量测量，并保证原先事件报告准则的质量测量
                 不受影响。之后，物理层继续上报质量测量结果，并指示是那种报告准
                 则的测量结果。
                 (5.2) RRC再次指示物理层新建上报准则为事件报告的质量测量，物理层
                 使用新的配置数据覆盖原先的质量测量，之后，物理层继续上报质量测
                 量结果。

             (6) UTRAN->RRC: 释放质量测量，被释放质量测量的报告准则为周期上报时，
             RRC->PHY: 释放质量测量，usReportCrtr填写为周期上报，即指示物理层释放
             报告准则为周期上报的质量测量，而报告准则为事件报告的质量测量，继续
             进行，不受影响。

             (7) UTRAN->RRC: 释放质量测量，被释放质量测量的报告准则为事件上报时，
             RRC->PHY: 释放质量测量，usReportCrtr填写为事件上报，即指示物理层释放
             报告准则为事件上报的质量测量，而报告准则为周期报告的质量测量，继续
             进行，不受影响。

             (8) 某些情况下，比如D->F状态转移时，RRC需要同时释放所有的质量测量，
             包括报告准则为周期报告和事件报告的质量测量。RRC->PHY: 释放质量测量，
             将usReportCrtr 填为"事件和周期"则可.

             (9) 其他说明: RRC->PHY的质量测量配置接口中的信元和空口基本保持一致，
             需要指出的是当UTRAN指示RRC新建质量测量，报告准则为不报告情况下，RRC
             指示PHY新建质量测量，报告准则为周期报告，PHY按照RRC的指示进行测量并
             向RRC上报测量结果，RRC收到该测量结果进行存储，不向网络上报，而是供
             其他测量参考使用。

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                               /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16              enMsgID;             /* 原语类型 *//*_H2ASN_Skip*/
    VOS_UINT16                              usOpID;

    PHYITF_MEASURE_COMMAND_ENUM_UINT16      enCommand;
    VOS_UINT16                              usMonitorTrchNum;
    VOS_UINT16                              ausMonitorTrchID[RRC_PHY_MAX_TRCH_NUM];

    VOS_UINT16                              usMeasId;
    PHYITF_QUA_MEAS_RPT_CRTR_ENUM_UINT16    enReportCrtrChoice;    /*报告的标准*/ /* _H2ASN_IeChoice_Export PHYITF_QUA_MEAS_RPT_CRTR_ENUM_UINT16 */

    union                                                                       /*_H2ASN_Skip*/
    {                                                                           /*_H2ASN_Skip*/
        PHYITF_QUA_PERIODIC_CRITERIA_STRU   stPeriodic;                         /*_H2ASN_Skip*/
        PHYITF_QUA_EVENT_CRITERIA_STRU      stEvent;
        /******************************************************************************************************
            _H2ASN_IeChoice_When        PHYITF_QUA_MEAS_RPT_CRTR_ENUM_UINT16
        ******************************************************************************************************/
    }unCriteria;                                                                /*_H2ASN_Skip*/

}RRC_PHY_QUALITY_MEASUREMENT_REQ_STRU;



/*****************************************************************************
 结构名    : PHY_RRC_QUALITY_MEASUREMENT_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 质量测量证实消息数据结构

*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;            /* 原语类型*/   /*_H2ASN_Skip*/
    VOS_UINT16                          usOpID;

}PHY_RRC_QUALITY_MEASUREMENT_CNF_STRU;



/*****************************************************************************
 结构名    : PHYITF_TRCH_QUA_REPORT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 每条传输信道报告的质量
 *****************************************************************************/

typedef  struct
{
    VOS_UINT16                          usTrCHID;
    VOS_UINT16                          usBLER;

}PHYITF_TRCH_QUA_REPORT_STRU;

/*****************************************************************************
 结构名    : PHYITF_QUALITY_PERIO_REPORT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 周期质量报告
 *****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMonitorTrCHNum;
    PHYITF_TRCH_QUA_REPORT_STRU         astTrCHReport[RRC_PHY_MAX_TRCH_NUM];

}PHYITF_QUALITY_PERIO_REPORT_STRU;

/*****************************************************************************
 结构名    : PHYITF_QUALITY_EVENT_REPORT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 事件质量报告
 *****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEventTrCHNum;
    VOS_UINT16                          ausEventTrCHID[RRC_PHY_MAX_TRCH_NUM];

}PHYITF_QUALITY_EVENT_REPORT_STRU;


/*****************************************************************************
 结构名    : PHY_RRC_QUALITY_MEASUREMENT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 质量测量指示消息数据结构

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16              enMsgID;            /* 原语类型 *//*_H2ASN_Skip*/
    VOS_UINT16                              usOpID;
    PHYITF_QUA_MEAS_RPT_IND_ENUM_UINT16     enReportCrtr;       /*报告的标准*/  /* _H2ASN_IeChoice_Export PHYITF_QUA_MEAS_RPT_IND_ENUM_UINT16 */
    VOS_UINT16                              usMeasId;
    union                                                                       /* _H2ASN_Skip */
    {                                                                           /* _H2ASN_Skip */
        PHYITF_QUALITY_PERIO_REPORT_STRU    stPeriodicReport;                   /* _H2ASN_Skip */
        PHYITF_QUALITY_EVENT_REPORT_STRU    stEventReport;
        /******************************************************************************************************
            _H2ASN_IeChoice_When        PHYITF_QUA_MEAS_RPT_IND_ENUM_UINT16
        ******************************************************************************************************/
    } unReportResult;                                                           /* _H2ASN_Skip */
}PHY_RRC_QUALITY_MEASUREMENT_IND_STRU;


/**************************************定位测量数据结构*******************************/

/*****************************************************************************
 结构名    : PHYITF_POS_BURST_MODE_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 突发模式参数信息
 *****************************************************************************/

typedef struct
{
    VOS_UINT16                          usBurstStart;
    VOS_UINT16                          usBurstLen;
    VOS_UINT16                          usBurstFreq;
    VOS_UINT16                          usReserve1;

} PHYITF_POS_BURST_MODE_PARA_STRU;

/*****************************************************************************
 结构名    : PHYITF_POS_IPDL_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IPDL 参数信息
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usIpSpacing;
    VOS_UINT16                          usIpLen;
    VOS_UINT16                          usIpOffset;
    VOS_UINT16                          usSeed;
    VOS_UINT16                          usReserve1;
    PHYITF_BOOL_ENUM_UINT16             enBurstModeParaValid;
    PHYITF_POS_BURST_MODE_PARA_STRU     stBurstModePara;

} PHYITF_POS_IPDL_PARA_STRU;

/*****************************************************************************
 结构名    : PHYITF_POS_NEIGHBOUR_CELL_SFNSFN_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 邻小区SFN_SFN差的定位信息
 *****************************************************************************/

typedef struct
{
    VOS_INT16                           sSfnSfnDrift;           /*1/256chip per second,[-100,100],0XFF代表无效*/
    VOS_INT16                           sSfnOffset;             /*[-1,0..4095],-1表示无效不存在,单位为1帧*/
    VOS_UINT16                          usSfnSfnReltimeDiff;    /*[0..38399] chips,单位为chip */
    VOS_UINT16                          usSearchWinSize;

    VOS_UINT16                          usReserve1;
    PHYITF_BOOL_ENUM_UINT16             enPosIpdlParaValid;
    PHYITF_POS_IPDL_PARA_STRU           stPosIpdlPara;

}PHYITF_POS_NEIGHBOUR_CELL_SFNSFN_INFO_STRU;


/*****************************************************************************
 结构名    : PHYITF_POS_NEIGHBOUR_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 邻小区定位信息
 *****************************************************************************/

typedef struct
{
    VOS_UINT16                          usPrimScramCode;
    VOS_UINT16                          usFreqInfo;

    /*表明是否需要测量Rx_Tx 时间差,0:不需要，1:需要*/
    VOS_UINT16                          usNeedRxTxTimeDiffType2Meas;

    /*表明是否需要测量SFN_SFN 观测时间差,0:不需要，1:需要*/
    VOS_UINT16                          usNeedSfnSfnObsTimeDiff2Meas;

    /*当需要测量SFN_SFN观测时间差时,stPosNebCellSfnSfnInfo有效*/
    PHYITF_POS_NEIGHBOUR_CELL_SFNSFN_INFO_STRU stPosNebCellSfnSfnInfo;

}PHYITF_POS_NEIGHBOUR_CELL_INFO_STRU;



/*****************************************************************************
 结构名    : PHYITF_POS_NEIGHBOUR_CELL_INFO_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 邻小区列表信息
 *****************************************************************************/

typedef struct
{
    VOS_UINT16                              usReserve1;
    VOS_UINT16                              usCellNum;
    PHYITF_POS_NEIGHBOUR_CELL_INFO_STRU     astNebCellInfo[RRC_PHY_MAX_POS_CELL_NUM];

 }PHYITF_POS_NEIGHBOUR_CELL_INFO_LIST_STRU ;


/*****************************************************************************
 结构名    : PHYITF_POS_REF_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 参考小区信息
 *****************************************************************************/

typedef struct
{
    VOS_UINT16                          usPrimScramCode;
    VOS_UINT16                          usFreqInfo;
    VOS_INT16                           sSfn;   /*-1代表无效*/

    /*表明是否需要测量Rx_Tx 时间差,0不需要，1需要*/
    VOS_UINT16                          usNeedRxTxTimeDiffType2Meas;

    VOS_UINT16                          usReserve1;
    PHYITF_BOOL_ENUM_UINT16             enPosIpdlParaValid; /*IPDL参数是否有效,0:无效，1:有效*/
    PHYITF_POS_IPDL_PARA_STRU           stPosIpdlPara;

} PHYITF_POS_REF_CELL_INFO_STRU;


/*****************************************************************************
 结构名    : PHYITF_POS_ASSIST_DATA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 定位辅助数据
 *****************************************************************************/

typedef struct
{
    PHYITF_BOOL_ENUM_UINT16                             enPosRefCellInfoValid;  /*参考小区信息是否有效,0:无效，1:有效*/
    PHYITF_BOOL_ENUM_UINT16                             enPosNeighbCellListValid;/*邻区列表信息是否有效,0:无效，1:有效*/
    PHYITF_POS_REF_CELL_INFO_STRU                       stPosRefCellInfo;       /*定位参考小区信息*/
    PHYITF_POS_NEIGHBOUR_CELL_INFO_LIST_STRU            stPosNeighbCellList;    /*定位邻区列表信息*/

} PHYITF_POS_ASSIST_DATA_STRU;


/*****************************************************************************
 结构名    : RRC_PHY_POSITION_MEASUREMENT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 定位测量请求
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                         /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;           /* 原语类型 *//*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;
    PHYITF_MEASURE_COMMAND_ENUM_UINT16  enCommand;         /*0释放，1建立(包括修改,和能量测量一致)*/
    VOS_UINT16                          usReserve1;

    VOS_UINT32                          ulRptTimeInterval; /*定位报告的周期,单位ms*/
    PHYITF_POS_ASSIST_DATA_STRU         stPosAssData;      /*定位的辅助数据*/

} RRC_PHY_POSITION_MEASUREMENT_REQ_STRU;


/*****************************************************************************
 结构名    : PHY_RRC_POSITION_MEASUREMENT_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 定位测量应答消息数据结构
 *****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                         /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;           /* 原语类型 *//*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;

} PHY_RRC_POSITION_MEASUREMENT_CNF_STRU;

/*****************************************************************************
 结构名    : PHYITF_POS_MEAS_QUAL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 定位测量质量
 *****************************************************************************/

typedef struct
{
    VOS_UINT16                          usStdResolution;    /*标准差的解析度*/
    VOS_UINT16                          usNumOfMeas;        /*此次标准差对应了多少次测量*/
    VOS_UINT16                          usStdOfMeas;        /*测量的标准差*/
    VOS_UINT16                          usReserve1;

} PHYITF_POS_MEAS_QUAL_STRU;

/*****************************************************************************
 结构名    : PHYITF_REF_CELL_MEAS_RSLT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 参考小区测量结果
 *****************************************************************************/

typedef struct
{
    VOS_UINT16                          usRefCellScramCode;             /*参考小区扰码,0-511*/

    /*若Rx_Tx时间差不需要测量或测量不到，则置0.
      [0.. 65535],物理层将RxTxTimeDiffType2测量结果
      (1/16chip精度）放大16倍后上报给协议栈,即测量
      结果是以1/16chip为单位的*/
    VOS_UINT16                          usRxTxTimeDiffType2Value;
    PHYITF_POS_MEAS_QUAL_STRU           stRxTxTimeDiffType2MeasQual;    /*若Rx_Tx时间差不需要测量或测量不到，则置0*/

} PHYITF_POS_REF_CELL_MEAS_RSLT_STRU;

/*****************************************************************************
 结构名    : PHYITF_NEIGHB_CELL_MEAS_RSLT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 邻区测量结果
 *****************************************************************************/

typedef struct
{
    VOS_UINT16                          usNeignbCellScramCode;          /*邻区扰码,0-511*/

    /*若Rx_Tx时间差不需要测量或测量不到，则置0.
      [0.. 65535],物理层将RxTxTimeDiffType2测量结果
      (1/16chip精度）放大16倍后上报给协议栈,即测量
      结果是以1/16chip为单位的*/
    VOS_UINT16                          usRxTxTimeDiffType2Value;
    PHYITF_POS_MEAS_QUAL_STRU           stRxTxTimeDiffType2MeasQual;    /*若Rx_Tx时间差不需要测量或测量不到，则置0*/

    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usSfnSfnObsTimeDiff2;           /*若Sfn_Sfn观测时间差不需要测量或测量不到，则置0*/
    PHYITF_POS_MEAS_QUAL_STRU           stSfnSfnObsTimeDiff2MeasQual;   /*若Sfn_Sfn观测时间差不需要测量或测量不到，则置0*/

} PHYITF_POS_NEIGHB_CELL_MEAS_RSLT_STRU;

/*****************************************************************************
 结构名    : PHYITF_POS_NEIGHB_CELLLIST_MEAS_RSLT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 邻区列表测量结果
 *****************************************************************************/

typedef struct
{

    VOS_UINT16                              usReserve1;
    VOS_UINT16                              usNeighbCellNum;    /*邻区数目*/
    PHYITF_POS_NEIGHB_CELL_MEAS_RSLT_STRU   astNeighbCellMeasRslt[RRC_PHY_MAX_POS_CELL_NUM];

} PHYITF_POS_NEIGHB_CELLLIST_MEAS_RSLT_STRU ;


/*****************************************************************************
 结构名    : PHYITF_POS_MEAS_RESULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 测量结果(包括了Tx_Rx测量结果和SFN_SFN观测时间差)
             参考小区和邻区可以分别上报,也可以一起上报

 *****************************************************************************/

typedef struct
{

    /*表明参考小区的测量结果是否有效,当物理层不需要测量参考小区的
      RxTxTimeDiffType2,或无法得到参考小区的RxTxTimeDiffType2时，则
      usRefCellMeasValid = 0, 否则为1*/
    PHYITF_BOOL_ENUM_UINT16             enRefCellMeasValid;

    /*表明邻区的测量结果是否有效,当物理层不需要测量或无法得到所有邻区的
      RxTxTimeDiffType2,且也不需要测量或无法得到所有邻区的SFN_SFN的测量值
      时, usNeighbCellMeasListValid = 0, 否则为1*/
    PHYITF_BOOL_ENUM_UINT16             enNeighbCellMeasListValid;

    /*最后一次测量值的SFN*/
    VOS_UINT16                          usSfn;
    VOS_UINT16                          usReserve1;

    /*参考小区测量结果*/
    PHYITF_POS_REF_CELL_MEAS_RSLT_STRU              stRefCellMeasRslt;

    /*邻小区测量结果*/
    PHYITF_POS_NEIGHB_CELLLIST_MEAS_RSLT_STRU       stNeighbCellListMeasRslt;

} PHYITF_POS_MEAS_RESULT_STRU;


/*****************************************************************************
 结构名    : PHY_RRC_POSITION_MEASUREMENT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 定位测量指示消息
 *****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                       /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16            enMsgID;       /* 原语类型 *//*_H2ASN_Skip*/
    VOS_UINT16                            usOPID;
    PHYITF_POS_MEAS_RESULT_STRU           stPosMeasRslt; /*定位测量结果*/

} PHY_RRC_POSITION_MEASUREMENT_IND_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_UE_INTERNAL_MEASUREMENT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 内部测量结果数据结构
 *****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;            /*_H2ASN_Skip*/   /* 原语类型 */
    VOS_UINT16                          usOPID;             /* 操作标识 */
    PHYITF_INTERNAL_REPORT_STRU         stInternalRpt;
}PHY_RRC_UE_INTERNAL_MEASUREMENT_IND_STRU;

/*==========================================================================
                              HSUPA 信道参数
============================================================================*/

/*****************************************************************************
 结构名    : PHYITF_E_AGCH_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : E_AGCH 信息
 *****************************************************************************/
typedef struct
{
    /*标识usPrimERnti是否有效，若有效，则enPrimERntiValid为1，否则enPrimERntiValid为0*/
    PHYITF_BOOL_ENUM_UINT16             enPrimERntiValid;

    /*标识usScndERnti是否有效，若有效，则enScndERntiValid为1，否则enScndERntiValid为0*/
    PHYITF_BOOL_ENUM_UINT16             enScndERntiValid;

    VOS_UINT16                          usEAgchChlsCode;                        /* INTEGER(0..255) */
    VOS_UINT16                          usPrimERnti;                            /*主E_Rnti,当 enPrimERntiValid 为1时有效*/
    VOS_UINT16                          usScndERnti;                            /*辅E_Rnti,当 enScndERntiValid 为1时有效*/
    VOS_UINT16                          usReserve1;

}PHYITF_E_AGCH_INFO_STRU;


/*****************************************************************************
 结构名    : PHYITF_E_RGCH_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : E_RGCH 的信息
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usChlsCode;                             /*  INTEGER(0..127),E_HICH 使用的信道码,
                                                                                    同一条链路的E_HICH和E_RGCH使用的信道码相同*/
    PHYITF_BOOL_ENUM_UINT16             enSignSeqValid;                         /* 指示usSignSeq是否存在 */
    VOS_UINT16                          usSignSeq;                              /* INTEGER(0..39),E_RGCH 使用的签名*/


    VOS_UINT16                          usERgchCombIndex;                       /* INTEGER(0..5),链路集合并索引,同一个链路集的链路索引是相同的,应该合并*/
                                                                                /* 对于E-RACH填写0 */
}PHYITF_E_RGCH_INFO_STRU;


/*****************************************************************************
 结构名    : PHYITF_E_HICH_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : E_HICH 的信息
 *****************************************************************************/
typedef struct
{
    /*INTEGER(0..127),E_HICH 使用的信道码,同一条链路的E_HICH和E_RGCH使用的信道码相同*/
    VOS_UINT16                          usChlsCode;

    /* INTEGER(0..39),E_HICH 使用的签名*/
    PHYITF_BOOL_ENUM_UINT16             enSignSeqValid;                         /* 指示usSignSeq是否有效 ，按协议10.3.6.123 */
    VOS_UINT16                          usSignSeq;

    /* INTEGER(0..5),链路集合并索引,同一个链路集的链路索引是相同的,应该合并
       RRC将每条RL 链路中的DPCH中的TPC combination index 赋给该值
       E-RACH时固定填写0 */
    VOS_UINT16                          usEHichCombIndex;

}PHYITF_E_HICH_INFO_STRU;


/*****************************************************************************
 结构名    : PHYITF_DL_PER_EDCH_RL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA 下行链路信息
 *****************************************************************************/
typedef struct
{

   /*EAgchInfo 是否有效，若有效，则enEAgchInfoValid为1，否则enEAgchInfoValid为0*/
   PHYITF_BOOL_ENUM_UINT16              enEAgchInfoValid;

   /*EHichInfo 是否有效，若有效，则enEHichInfoValid为1，否则enEHichInfoValid为0*/
   PHYITF_BOOL_ENUM_UINT16              enEHichInfoValid;

   /*ERgchInfo 是否有效，若有效，则enERgchInfoValid为1，否则enERgchInfoValid为0*/
   PHYITF_BOOL_ENUM_UINT16              enERgchInfoValid;

   /*指示这个小区是否是服务E_DCH小区*/
   PHYITF_BOOL_ENUM_UINT16              enServingEdchRlInd;

   /*这条链路的导频信道的主扰码，因为目前只支持主导频信道，
     所以E_HICH,E_AGCH,E_RGCH都使用这个扰码作为自己信道的扰码*/
   VOS_UINT16                           usPrimScramCode;

   VOS_UINT16                           usReserve1;

   PHYITF_E_AGCH_INFO_STRU              stEAgchInfo;                            /* OPTIONAL */
   PHYITF_E_HICH_INFO_STRU              stEHichInfo;                            /* OPTIONAL */
   PHYITF_E_RGCH_INFO_STRU              stERgchInfo;                            /* OPTIONAL */


}PHYITF_DL_PER_EDCH_RL_STRU;

/*****************************************************************************
 结构名    : PHYITF_DL_PER_EDCH_RL_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA 下行链路列表信息
             包含了EDCH 链路和非EDCH链路
 *****************************************************************************/
typedef struct
{

   /*指示EDCH 服务小区是否变更,0:不变更,1变更*/
   VOS_UINT16                           usEServCellChangeInd;

   /*
     在EDCH 服务小区变更且新的EDCH服务小区不属于原来的EDCH RLS时,
     应该触发Scheduling Information.
     usEServCellChangeTrigSiInd 指示是否应该触发SI,0:不触发,1触发
     如果同时存在RL SETUP和RL MODIFY的情况下该指示在两条原语中都同时配置
   */
   VOS_UINT16                           usEServCellChangeTrigSiInd;

   VOS_UINT16                           usDlFreqInfo;                   /* 下行频点，INTEGER(0..16383) */

   VOS_UINT16                           usFreqBandNo;                   /* 频段号*/
   VOS_UINT16                           usTxRxFreqSeparation;           /* 收发频差*/

   VOS_UINT16                           usCnt;
   PHYITF_DL_PER_EDCH_RL_STRU           astDlPerEdchRl[RRC_PHY_MAX_RL_NUM];

}PHYITF_DL_PER_EDCH_RL_LIST_STRU;

/*V3 R7_7C1 Start */
/*****************************************************************************
 结构名    : PHYITF_E_TFC_BOOST_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : E_TFC_BOOST_INFO 信道信息

 *****************************************************************************/

typedef struct
{
    VOS_UINT16                          usDeltaT2Tp;   /* INTEGER(0..6)  OPTIONAL  默认配置0 */

    VOS_UINT16                          usETfciBoost;  /* INTEGER(0..127)  默认配置127 */

}PHYITF_E_TFC_BOOST_INFO_STRU;
/* V3 R7_7C1 End */

/*****************************************************************************
 结构名    : PHYITF_E_DPCCH_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA 上行EDPCCH 信道信息

 *****************************************************************************/
typedef struct
{
    /* INTEGER(0..8) */
    VOS_UINT16                          usEDpcchDpcchPwrOffset;

    /* HappyBit 延时判决 */
    VOS_UINT16                          usHappyBitDelayCondi;
    /* EDpdchPwrInterpolation 是否有效 0表示无效 1表示有效  如果空口没有配置默认配置0*/
    VOS_UINT16                          usEDpdchPwrInterpolation;

    VOS_UINT16                          usResrve1;

    PHYITF_E_TFC_BOOST_INFO_STRU        stETfcBoostInfo;
}PHYITF_E_DPCCH_INFO_STRU;


/*****************************************************************************
 结构名    : PHYITF_E_DPDCH_SCHEDUL_TRANSM_CFG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA 调度授权信息

 *****************************************************************************/
typedef struct
{

    /* INTEGER(0..38) */
    VOS_UINT16                          usValue;

    /* 服务授权选择,0选择主的,1选择辅的*/
    VOS_UINT16                          usPrimScndGrantSelect;                  /* E-RACH时网络不携带，填写0 */

}PHYITF_E_DPDCH_SCHEDUL_TRANSM_CFG_STRU;

/*****************************************************************************
 结构名    : PHYITF_E_DPDCH_REF_E_TFCI_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA 上行EDPDCH 参考E_TFCI对应的Power Offset
             用于计算功率
 *****************************************************************************/
typedef struct
{
    /* INTEGER(0..127),参考E_TFCI*/
    VOS_UINT16                          usRefETfci;

    /* INTEGER(0..29),参考E_TFCI 对应的Power Offset*/
    VOS_UINT16                          usRefETfciPo;

}PHYITF_E_DPDCH_REF_E_TFCI_STRU;

/*****************************************************************************
 结构名    : PHYITF_E_DPDCH_REF_E_TFCI_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA 上行EDPDCH 参考E_TFCI列表
 *****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCnt;
    PHYITF_E_DPDCH_REF_E_TFCI_STRU      astDpdchRefETfci[RRC_PHY_MAX_EDCH_REFTFCI_NUM];

}PHYITF_E_DPDCH_REF_E_TFCI_LIST_STRU;


/*****************************************************************************
 结构名    : PHYITF_E_DPDCH_SCHED_INFO_CONFIG_STRU
 协议表格  : 10.3.6.99    E-DPDCH Info
                        Scheduling Information Configuration
 ASN.1描述 : E_DPDCH_SchedulingInfoConfiguration
 结构说明  : 调度信息
             NOTE:If the Periodicity is set to 4ms and the E-DCH TTI
             is set to 10ms, the UE shall interpret the periodicity value as 10ms.
*****************************************************************************/
typedef struct
{
    /*对于EDCH TTI=10ms,若RNC 配置usNoGrantPeriodic=4ms时,RRC取usNoGrantPeriodic为10ms配给物理层*/
    VOS_UINT16                          usNoGrantPeriodic;  /* 单位ms, (everyEDCHTTI = 0xffff,4,10,20,50,100,200,500,1000),Default value is "no report"用0表示 */

    /*对于EDCH TTI=10ms,若RNC 配置usGrantPeriodic=4ms时,RRC取usGrantPeriodic为10ms配给物理层*/
    VOS_UINT16                          usGrantPeriodic;    /* 单位ms, (everyEDCHTTI = 0xffff,4,10,20,50,100,200,500,1000),Default value is "no report"用0表示 */
    VOS_UINT16                          usSIPowOffset;      /* [0,6] */
    VOS_UINT16                          usReserve1;         /* 4字节对齐，保留 */

}PHYITF_E_DPDCH_SCHED_INFO_CONFIG_STRU;

/*****************************************************************************
 结构名    : PHYITF_E_DPDCH_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA 上行EDPDCH 信息
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                                          usETfciTableIndex;      /* INTEGER(0..1) */

    /*usEDchMinSetETfci 是否有效，若有效，则enEDchMinSetETfciValid为1，否则enEDchMinSetETfciValid为0*/
    PHYITF_BOOL_ENUM_UINT16                             enEDchMinSetETfciValid;
    VOS_UINT16                                          usEDchMinSetETfci;      /* INTEGER(0..127)  OPTIONAL */

    PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_ENUM_UINT16    enMinReducEDpdchGainFactor; /* 功率回退因子，不携带时使用默认值8/15*/

    VOS_UINT16                                          usThreeIndexStepThresh; /* INTEGER(0..37)  OPTIONAL */
    VOS_UINT16                                          usTwoIndexStepThresh;   /* INTEGER(0..37)  OPTIONAL */
    PHYITF_E_DPDCH_MAX_CHLS_CODES_ENUM_UINT16           enMaxChlsCodes;         /* ENUMERATED,取值PHYITF_MAX_CHLSCODES_ENUM中的值*/
    VOS_UINT16                                          usPlNonMax;             /* INTEGER(11..25) */

    PHYITF_E_DPDCH_REF_E_TFCI_LIST_STRU                 stRefETfcIs;

    PHYITF_E_DPDCH_SCHED_INFO_CONFIG_STRU               stSchedInfoConfig;


}PHYITF_E_DPDCH_INFO_STRU;

/*****************************************************************************
 结构名    : PHYITF_UL_16QAM_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
 *****************************************************************************/
typedef struct
{
    PHYITF_BOOL_ENUM_UINT16                 enUl16QamSetting;                   /*是否配置16QAM,0:无效;1:有效*/
    VOS_UINT16                              usBetaEdGainEAgchTableSelection;    /* 取值0或者1 */
}PHYITF_UL_16QAM_CONFIG_STRU;

/*****************************************************************************
 结构名    : PHYITF_UL_EDCH_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : EDCH 上行信息
 *****************************************************************************/
typedef struct
{
    /*调度传输 stSchedulTransmCfg 是否有效,若有效，则enSchedulTransmValid为1，否则enSchedulTransmValid为0*/
    PHYITF_BOOL_ENUM_UINT16                 enSchedulTransmValid;

    VOS_UINT16                              usReserve1;

    /* E_Dpcch信息 */
    PHYITF_E_DPCCH_INFO_STRU                stEDpcchInfo;

    /* E_Dpdch信息*/
    PHYITF_E_DPDCH_INFO_STRU                stEDpdchInfo;

    /* OPTIONAL，调度传输信息*/
    PHYITF_E_DPDCH_SCHEDUL_TRANSM_CFG_STRU  stSchedulTransmCfg;
    VOS_UINT16                              us2msSchedGrantProcAlloc;           /*BITMAP,2ms TTI,调度授权进程配置,该MAC-d流的数据
                                                                                只能在BIT位取值为1的进程上发送,Bit0对应进程7，Bit1对应进程6，以此类推...
                                                                                网络不携带表示全选，Default value is: transmission in all HARQ processes is allowed.*/
    VOS_UINT16                              usReserve2;
    PHYITF_UL_16QAM_CONFIG_STRU             stUl16QamConfig;
}PHYITF_UL_EDCH_INFO_STRU;



/*****************************************************************************
 结构名    : PHYITF_MAC_E_NON_SCHED_GRANT_STRU
 协议表格  : 10.3.5.1b    Added or reconfigured E-DCH MAC-d flow
 ASN.1描述 : transmissionGrantType
 结构说明  : 非调度授权
*****************************************************************************/
typedef struct
{
    /* */
    VOS_UINT16                          usEFlowMaxMacEPduSize;          /* [1...19982] bit */

    /* BITMAP,2ms TTI,非调度授权进程配置，
       bit位值为1时传送有效。Bit 0 corresponds to HARQ process 0, bit 1 corresponds to HARQ process 1...
     网络不携带，表示全配，Default value is: transmission in all HARQ processes is allowed.
     Bit 0 is the first/leftmost bit of the bit string.*/
    VOS_UINT16                          us2msNonSchedGrantProcAlloc;

}PHYITF_MAC_E_NON_SCHED_GRANT_STRU ;

/*****************************************************************************
 结构名    : PHYITF_MAC_EFLOW_TRANS_GRANT_INFO_STRU
 协议表格  : 10.3.5.1b    Added or reconfigured E-DCH MAC-d flow
 ASN.1描述 : transmissionGrantType
             E_DPDCH_SchedulingTransmConfiguration
             ms2_SchedTransmGrantHARQAlloc
 结构说明  : E DCH流的配置
*****************************************************************************/
typedef struct
{
    PHYITF_MAC_E_SCHED_GRANT_INFO_CHOSEN_ENUM_UINT16 enChoice;  /* _H2ASN_IeChoice_Export PHYITF_MAC_E_SCHED_GRANT_INFO_CHOSEN_ENUM_UINT16 */
    VOS_UINT16                                       usReserved1;

    union                                                                       /*_H2ASN_Skip*/
    {                                                                           /*_H2ASN_Skip*/
        PHYITF_MAC_E_NON_SCHED_GRANT_STRU    stNonSchedGrant;                   /*_H2ASN_Skip*//*只有当enChoice＝0时，该结构才有效；*/
        VOS_UINT32                           ulReserved;
        /******************************************************************************************************
            _H2ASN_IeChoice_When        PHYITF_MAC_E_SCHED_GRANT_INFO_CHOSEN_ENUM_UINT16
        ******************************************************************************************************/
    }u;                                                                         /*_H2ASN_Skip*/
}PHYITF_MAC_EFLOW_TRANS_GRANT_INFO_STRU;

/*****************************************************************************
 结构名    : PHYITF_MAC_EDCH_FLOW_STRU
 协议表格  : 10.3.5.1b    Added or reconfigured E-DCH MAC-d flow
 ASN.1描述 : E_DCH_AddReconf_MAC_d_Flow
 结构说明  : E DCH流的配置
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usEFlowId;                  /* [0,7] */
    VOS_UINT16                              usEFlowPwrOffset;           /* [0,6],dB 重配置时网络可能不携带，但是WAS固定配置给PHY */
    VOS_UINT16                              usEFlowMaxReTrans;          /* [0,15] 重配置时网络可能不携带，但是WAS固定配置给PHY*/
    VOS_UINT16                              usEFlowMuxlist;             /* BITMAP,Bit0对应MAC-d流0，Bit1对应MAC-d流1，
                                                                       以此类推，BIT值为1表明相应的MAC-d流可以与当前MAC-d流复用在同一MAC-e PDU中发送;
                                                                       如果配置全0，表示没有复用 */
    PHYITF_MAC_EFLOW_TRANS_GRANT_INFO_STRU  stEFlowTransGrantInfo;      /* Only allowed to be absent when already defined for this E-DCH MAC-d flow
                                                                       WAS每次都配置给MAC */
}PHYITF_MAC_EDCH_FLOW_STRU;


/*****************************************************************************
 结构名    : PHYITF_MAC_EDCH_FLOWLIST_STRU
 协议表格  : 10.3.5.1b    Added or reconfigured E-DCH MAC-d flow
 ASN.1描述 : E_DCH_AddReconf_MAC_d_FlowList
 结构说明  : E DCH流的配置
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usEdchFlowCnt;                                   /* FLOW的个数 */
    PHYITF_MAC_EDCH_FLOW_STRU           astEdchFlow[RRC_PHY_MAC_EDCH_MAX_MACD_FLOW_NUM]; /* 每个Edch Flow的信息 */

}PHYITF_MAC_EDCH_FLOW_LIST_STRU;

/* MOD UL_E_L2 BEGIN */
/*****************************************************************************
 结构名    : PHYITF_RLC_PDU_SIZE_FIXED_STRU
 协议表格  :
 ASN.1描述 :  ASN.1 文本 : RLC_PDU_SizeList
 结构说明  : RLC SIZE
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usDdi;                                  /* [0,62],MAC_I实体的时候，这个值WDSP是不使用的 */
    VOS_UINT16                          usRlcSizeCnt;                           /* [0,31] */
    VOS_UINT16                          ausRlcSize[RRC_PHY_MAX_RLC_PDU_SIZE_NUM_PER_LOCH];/* [16,5000],by step of 8 */
}PHYITF_RLC_PDU_SIZE_FIXED_STRU;

/*****************************************************************************
 结构名    : PHYITF_RLC_PDU_SIZE_FLEX_STRU
 协议表格  :
 ASN.1描述 : ASN.1 文本 : RLC-PDU-SizeConstraint
 结构说明  : RLC_PDU可变SIZE的参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usReserve1;
    PHYITF_RLC_PDU_SIZE_LI_SIZE_ENUM_UINT16 enLenIndSize;                       /* ENUMERATED  OPTIONAL，不存在时填写BUTT */
    VOS_UINT16                              usMinRlcPduSize;                    /* Integer (16..12040 by step of 8) */
    VOS_UINT16                              usLargestRlcPduSize;                /* Integer (16..12040 by step of 8) */
}PHYITF_RLC_PDU_SIZE_FLEX_STRU;

/*****************************************************************************
 结构名    : PHYITF_LOCH_MAPP_RLC_PDU_SIZE_STRU
 协议表格  :
 ASN.1描述 : UL_LogicalChannelMapping_r6
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usReserve1;

    #define    PHYITF_RLC_PDU_SIZE_FIXED_SIZE   0                               /* Fixed size */
    #define    PHYITF_RLC_PDU_SIZE_FLEX_SIZE    1                               /* Flexible size */

    VOS_UINT16                                  usChoice;

    union
    {
        PHYITF_RLC_PDU_SIZE_FIXED_STRU          stFixedSize;                    /* Fixed size */
        PHYITF_RLC_PDU_SIZE_FLEX_STRU           stFlexSize;                     /* Flexible Size */
    }u;

}PHYITF_LOCH_MAPP_RLC_PDU_SIZE_STRU;
/* MOD UL_E_L2 END */


/*****************************************************************************
 结构名    : PHYITF_MAC_EDCH_LOCH_STRU
 协议表格  : 10.3.4.21  RB mapping info
 ASN.1描述 : UL_LogicalChannelMapping_r6
 结构说明  : EDCH逻辑信道与传输信道的对应关系，以及逻辑信道可用的RLC SIZE
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usLochLabel;        /* 逻辑信道内部实现统一标识：[1*2+0,32*2+1],RB ID范围:[1..32] */
    VOS_UINT16                          usLochId;           /* INTEGER(1..15),0表示无效 */
    VOS_UINT16                          usEdchMacdFlowId;   /* [0,7] */
    VOS_UINT16                          usIncludeInSIInd;   /* 指示在触发Schedule Information Report时,是否应该考虑该逻辑信道,0:不考虑,1:考虑
                                                               E-RACH不携带填写0 */

    VOS_UINT16                          usLochPrio;         /* 逻辑信道优先级：[1,8] */
    PHYITF_LOCH_MAPP_RLC_PDU_SIZE_STRU  stRlcPduSize;       /* RLC PDU SIZE,CCCH时不填写 */
    PHYITF_LOCH_DATA_TYPE_ENUM_UINT16   enLochDataType;     /* 指示该LOCH对应的RB的数据类型 */

}PHYITF_MAC_EDCH_LOCH_STRU;


/*****************************************************************************
 结构名    : PHYITF_MAC_EDCH_LOCH_LIST_STRU

 结构说明  : E DCH逻辑信道列表的配置
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usEdchLochCnt;                              /*【1，RRC_PHY_MAC_EDCH_MAX_LOCH_NUM】 Edch 逻辑信道的个数 */
    PHYITF_MAC_EDCH_LOCH_STRU           astMacEdchLoch[PS_WUE_MAX_E_DCH_LOCH_NUM];  /* 每个Edch 逻辑信道的信息 */

}PHYITF_MAC_EDCH_LOCH_LIST_STRU;



/*****************************************************************************
 结构名    : PHYITF_UL_HSUPA_PHY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : UL HSUPA 信息
 *****************************************************************************/
typedef struct
{

    PHYITF_PHYCH_TYPE_ENUM_UINT16       enPhyChannelType;  /*64*/               /* _H2ASN_Skip */
    VOS_INT16                           sActiveTime;                            /*激活的时间CFN,-1表示立即激活,否则表示激活的CFN*/
    PHYITF_EDCH_TTI_ENUM_UINT16         enEDCHTTI;                              /*Edch TTI ,枚举 0:10ms or 1:2ms*/
    PHYITF_RVVERSION_ENUM_UINT16        enRVVersion;                            /*RV 版本号,ENUMERATED,取值 PHYITF_RVVERSION_ENUM 0 表示使用RV0,1表示使用RVTable */

    PHYITF_UL_EDCH_INFO_STRU            stUlEdchInfo;                           /*上行Edch 信息*/

}PHYITF_UL_HSUPA_PHY_STRU;


/*****************************************************************************
 结构名    : PHYITF_DL_HSUPA_PHY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DL HSUPA 信息
 *****************************************************************************/
typedef struct
{

    PHYITF_PHYCH_TYPE_ENUM_UINT16       enPhyChannelType;  /*128*/               /* _H2ASN_Skip */

    VOS_INT16                           sActiveTime;                            /*激活的时间CFN,-1表示立即激活,否则表示激活的CFN*/

    PHYITF_DL_PER_EDCH_RL_LIST_STRU     stDlRLInfo;                             /*下行RL 信息,当DlRLInfo置位时有效*/

}PHYITF_DL_HSUPA_PHY_STRU;

/*****************************************************************************
 结构名    : PHYITF_MAC_E_CFG_MODE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC-E配置方式
 *****************************************************************************/
enum    PHYITF_MAC_CFG_MODE_ENUM
{

    PHYITF_MAC_SETUP                     = 0,                         /* 新建 */
    PHYITF_MAC_MODIFY                    = 1,                         /* 重配 */
    PHYITF_MAC_REVERT                    = 2,                         /* 回退旧配置 */
    PHYITF_MAC_CFG_BUTT
};
typedef VOS_UINT16  PHYITF_MAC_CFG_MODE_ENUM_UINT16;

/*****************************************************************************
 结构名    : RRC_PHY_MACE_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA MACE 配置请求
 *****************************************************************************/
typedef   struct
{
    VOS_MSG_HEADER /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                          usOPID;                 /* 操作标识 */
    VOS_INT16                           sActiveTime;            /* 激活时间 */
    PHYITF_MAC_CFG_MODE_ENUM_UINT16     enMacECfgMode;          /*  MAC-E 配置方式 */
    PHYITF_MAC_EDCH_FLOW_LIST_STRU      stMacEdchFlowList;      /* Mac Edch Flow List Info*/
    PHYITF_MAC_EDCH_LOCH_LIST_STRU      stMacEdchLochList;      /* Mac Edch Loch List Info*/

}RRC_PHY_MACE_CONFIG_REQ_STRU;


/*****************************************************************************
 结构名    : PHY_RRC_MACE_CONFIG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA MACE 配置应答
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* 操作标识 */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16  enIndicator;      /* 配置结果,0代表成功，其它代表失败*/
    VOS_UINT16                                usReserve1;

}PHY_RRC_MACE_CONFIG_CNF_STRU;


/*****************************************************************************
 结构名    : RRC_PHY_MACE_RELEASE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA MACE 释放请求
 *****************************************************************************/
typedef   struct
{
    VOS_MSG_HEADER /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                          usOPID;                 /* 操作标识 */
    VOS_INT16                           sActiveTime;            /* 激活时间 */
    VOS_UINT16                          usReserve1;             /* 字节对齐*/

}RRC_PHY_MACE_RELEASE_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_MACE_RELEASE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA MACE 释放应答
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* 操作标识 */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16  enIndicator;      /* 配置结果,0代表成功，其它代表失败*/
    VOS_UINT16                                usReserve1;

}PHY_RRC_MACE_RELEASE_CNF_STRU;

/*****************************************************************************
 结构名    : RRC_PHY_MAC_E_I_RESET_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA MACE 重建指示
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* 操作标识 */
    VOS_INT16                                 sActiveTime;      /* 激活时间 */
    PHYITF_MAC_E_I_RESET_TYPE_ENUM_UINT16     enResetType;      /* 重建类型 */
}RRC_PHY_MAC_E_I_RESET_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_MAC_E_I_RESET_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA MACE 重建指示响应
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* 操作标识 */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16  enIndicator;      /* 配置结果,0代表成功，其它代表失败*/
    VOS_UINT16                                usReserve1;

}PHY_RRC_MAC_E_I_RESET_CNF_STRU;

/*V3 R7_7C1 Start */
/*****************************************************************************
 结构名    : RRC_PHY_MACHS_RESET_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSDPA MACHS 和 MACEHS 重建指示
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* 操作标识 */
    VOS_INT16                                 sActiveTime;      /* 激活时间 */
    PHYITF_MAC_RESET_TYPE_ENUM_UINT16         enResetType;      /* 重建类型 */
}RRC_PHY_MACHS_RESET_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_MACHS_RESET_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSDPA MACHS 和 MACEHS 重建指示响应
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* 操作标识 */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16  enIndicator;      /* 配置结果,0代表成功，其它代表失败*/
    VOS_UINT16                                usReserve1;
}PHY_RRC_MACHS_RESET_CNF_STRU;
/* V3 R7_7C1 End */


/*****************************************************************************
 结构名    : RRC_PHY_MACI_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC_I配置物理层
 *****************************************************************************/
typedef  struct
{
    VOS_MSG_HEADER /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                          usOPID;                 /* 操作标识 */
    VOS_INT16                           sActiveTime;            /* 激活时间 */
    PHYITF_MAC_CFG_MODE_ENUM_UINT16     enMacICfgMode;          /* MAC-I 配置方式 */
    PHYITF_TSN_BIT_LEN_ENUM_UINT16      enTsnBitLen;            /* DCHSUPA时配置14bit,否则为6bit */
    VOS_UINT16                          usReserve1;             /* 四字节对齐 */
    PHYITF_MAC_EDCH_FLOW_LIST_STRU      stMacEdchFlowList;      /* Mac Edch Flow List Info*/
    PHYITF_MAC_EDCH_LOCH_LIST_STRU      stMacEdchLochList;      /* Mac Edch Loch List Info*/

}RRC_PHY_MACI_CONFIG_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_MACI_CONFIG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA MACI 配置应答
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* 操作标识 */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16  enIndicator;      /* 配置结果,0代表成功，其它代表失败*/
    VOS_UINT16                                usReserve1;
}PHY_RRC_MACI_CONFIG_CNF_STRU;

/*****************************************************************************
 结构名    : RRC_PHY_MACI_RELEASE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA MACI 释放请求
 *****************************************************************************/
typedef   struct
{
    VOS_MSG_HEADER /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                          usOPID;                 /* 操作标识 */
    VOS_INT16                           sActiveTime;            /* 激活时间 */
    VOS_UINT16                          usReserve1;             /* 字节对齐*/
}RRC_PHY_MACI_RELEASE_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_MACI_RELEASE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA MACI 释放应答
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* 操作标识 */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16  enIndicator;      /* 配置结果,0代表成功，其它代表失败*/
    VOS_UINT16                                usReserve1;

}PHY_RRC_MACI_RELEASE_CNF_STRU;


/*****************************************************************************
 结构名    : PHY_RRC_MAC_ACTIVATE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HSUPA MACE 配置激活指示
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* 操作标识 */
    VOS_UINT16                                usCFN;            /* 配置生效的CFN */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16  enIndicator;      /* 配置结果,0代表成功，其它代表失败*/
/*V3 R7_7C1 Start */
}PHY_RRC_MAC_ACTIVATE_IND_STRU;
/* V3 R7_7C1 End */

/*****************************************************************************
 结构名    : PHYITF_DL_SCND_CELL_INFO_NEW_CFG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Downlink secondary cell info FDD参数
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usDlFreqInfo;                   /* 辅载波下行频点，INTEGER(0..16383) */
    VOS_UINT16                                  usPrimScramCode;                /* 主扰码 */
    VOS_UINT16                                  usSecondScramCode;              /* 辅扰码，INTEGER(1..15)  OPTIONAL ,辅扰码不存在填写0 */
    VOS_UINT16                                  usNewHRnti;

    PHYITF_64QAM_CONFIGURED_ENUM_UINT16         enDl64QAMConfig;                /* HS DSCH信道是否使用64QAM */
    PHYITF_HSDSCH_TB_SIZE_TABLE_ENUM_UINT16     enHsDschTbSizeTable;            /* HsDsch TB table 使用模式 */

    VOS_INT16                                   sMeasPwrOffset;                 /* INTEGER(-12..26) */
    PHYITF_BOOL_ENUM_UINT16                     enDiffTxModeFromServHsDschCell; /* TRUE:different;FALSE:not include */

    PHYITF_HS_SCCH_CODE_STRU                    stHsScchCodeInfo;               /* HS_SCCH 使用的信道码信息 */
    PHYITF_HARQ_INFO_STRU                       stHarqInfo;                     /* HARQ INFO,根据主小区的HARQ INFO得到 */

}PHYITF_DL_SCND_CELL_INFO_NEW_CFG_STRU;

/*****************************************************************************
 结构名    : PHYITF_SCND_HSDPAPLUS_PHY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DC HSDPA配置参数
*****************************************************************************/
typedef struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16                   enPhyChannelType;           /* 514 */ /* _H2ASN_Skip */
    VOS_INT16                                       sActiveTime;                /*激活的时间CFN,-1表示立即激活*/

    VOS_UINT16                                      usTsnBitNum;                /* 6： TSN长度为6bit；14：TSN长度为14bit; DC+MIMO使用14bit*/

    PHYITF_DL_SCND_CELL_INFO_CFG_INFO_ENUM_UINT16   enDlScndCellInfoCfgInfo;
    PHYITF_DL_SCND_CELL_INFO_NEW_CFG_STRU           stDlScndCellInfo;

    PHYITF_BOOL_ENUM_UINT16                         enNeedRevertOrder;          /* 是否需要回退HS_SCCH order,应用场景切换失败回退,SCND_RL_SETUP时才可能填写PS_TRUE */

    PHYITF_BOOL_ENUM_UINT16                         enMimoParamsValid;          /* 指示MIMO PARAMS是否有效 */
    PHYITF_MIMO_PARAMS_STRU                         stMimoParams;
}PHYITF_SCND_HSDPAPLUS_PHY_STRU;
/*****************************************************************************
 结构名    : ID_RRC_PHY_UPLINK_TRCH_CODEC_MAPPING_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 语音业务上行传输信道和AMR子流映射关系配置消息。
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                         /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;           /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;            /* 操作ID */
    VOS_INT16                           sActiveTime;      /* 激活时间[-1,255]ms  -1为立即激活 */
    VOS_UINT16                          ausUplinkTrchId[RRC_PHY_MAX_AMR_TRCH_NUM];/* [1,32]AMR的ABC子流分别对应的上行传输信道号，0xffff表示语音数据流不存在 */
} RRC_PHY_UPLINK_TRCH_CODEC_MAPPING_REQ_STRU;

/*****************************************************************************
 结构名    : ID_PHY_RRC_UPLINK_TRCH_CODEC_MAPPING_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 语音业务上行传输信道和AMR子流映射关系配置的CNF消息。
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16               enMsgID;           /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                               usOpId;            /* 操作ID */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16 enRslt;            /* 配置结果 */
    VOS_UINT16                               usReserved;
} PHY_RRC_UPLINK_TRCH_CODEC_MAPPING_CNF_STRU;

/*****************************************************************************
 结构名    : ID_RRC_PHY_DNLINK_TRCH_CODEC_MAPPING_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 语音业务下行传输信道和AMR子流映射关系配置消息。
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                         /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;           /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;            /* 操作ID */
    VOS_INT16                           sActiveTime;      /* 激活时间[-1,255]ms  -1为立即激活 */
    VOS_UINT16                          ausDnlinkTrchId[RRC_PHY_MAX_AMR_TRCH_NUM];/* [1,32]AMR的ABC子流分别对应的下行传输信道号，0xffff表示语音数据流不存在 */
} RRC_PHY_DNLINK_TRCH_CODEC_MAPPING_REQ_STRU;

/*****************************************************************************
 结构名    : ID_PHY_RRC_DNLINK_TRCH_CODEC_MAPPING_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 语音业务下行传输信道和AMR子流映射关系配置的CNF消息。
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16               enMsgID;           /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                               usOpId;            /* 操作ID */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16 enRslt;            /* 配置结果 */
    VOS_UINT16                               usReserved;
} PHY_RRC_DNLINK_TRCH_CODEC_MAPPING_CNF_STRU;

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
} PHYITF_DTX_E_DCH_TTI_STRU;

/*****************************************************************************
 结构名    : PHYITF_DTX_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DTX参数
*****************************************************************************/
typedef struct
{

    VOS_UINT16                          usReserved1;
    PHYITF_EDCH_TTI_ENUM_UINT16         enDtxEdchTti;                           /* edch tti */
    PHYITF_DTX_E_DCH_TTI_STRU           stDtxEdchTti;

    VOS_UINT16                          usUeDtxCycle2InactThresh;              /* Units of E-DCH TTIs.Enumerated (1, 4, 8, 16, 32, 64, 128, 256) */

    VOS_UINT16                          usUeDtxCycle2DefaultSg;                /* 不存在设置为0XFFFF,INTEGER(0..38)  OPTIONAL */

    VOS_UINT16                          usUeDtxLongPrbLen;                     /*Units of slots； Enumerated (4, 15)，default 2 */
    VOS_UINT16                          usMacInactThresh;                      /*Units of E-DCH TTIs；Infinity取值为0XFFFF; Enumerated (1, 2, 4, 8, 16, 32, 64, 128, 256, 512, Infinity) */
    VOS_UINT16                          usCqiDtxTimer;                         /* Infinity取值为0XFFFF;Units of subframes；Enumerated (0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, Infinity) */
    VOS_UINT16                          usUeDpcchBurst1;                       /* Units of sub-frames;Enumerated (1, 2, 5) */
    VOS_UINT16                          usUeDpcchBurst2;                       /* Units of sub-frames;Enumerated (1, 2, 5) */
    VOS_UINT16                          usReserved2;
}PHYITF_DTX_INFO_STRU;

/*****************************************************************************
 结构名    : PHYITF_DRX_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DRX参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usUeDrxCyc;                     /*Units of sub-frames*/
    VOS_UINT16                          usUeDrxCycInactThresh;          /*Units of subframes*/
    VOS_UINT16                          usUeGrantMonitorInactThresh;    /*Units of E-DCH TTIs*/
    PHYITF_BOOL_ENUM_UINT16             enUeDrxGrantMonitoring;         /* BOOLEAN */

}PHYITF_DRX_INFO_STRU;

/*****************************************************************************
 结构名    : PHYITF_DTX_DRX_NEW_TIM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CPC新的定时配置
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEnablingDelay;                        /*In radio frames, Enumerated (0, 1, 2, 4, 8, 16, 32, 64, 128) */

    VOS_UINT16                          usUeDtxDrxOffset;                       /*Units of subframes, INTEGER(0..159) */

} PHYITF_DTX_DRX_NEW_TIM_STRU;

/*****************************************************************************
 枚举名    : PHYITF_DTX_DRX_TIM_INFO_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : CPC定时配置方式
*****************************************************************************/
enum  PHYITF_DTX_DRX_TIM_INFO_ENUM
{
    PHYITF_DTX_DRX_TIM_CONTINUE = 0,                                            /* Used in reconfigurations without interruption of DTX-DRX and HS-SCCH less*/
    PHYITF_DTX_DRX_TIM_NEW_TIM,
    PHYITF_DTX_DRX_TIM_BUTT
};
typedef VOS_UINT16  PHYITF_DTX_DRX_TIM_INFO_ENUM_UINT16;


/*****************************************************************************
 结构名    : PHYITF_DTX_DRX_TIM_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : dtx-drx定时信息
*****************************************************************************/
typedef struct
{

    VOS_UINT16                          usReserved;

    PHYITF_DTX_DRX_TIM_INFO_ENUM_UINT16 enDtxDrxTimInfo;

    PHYITF_DTX_DRX_NEW_TIM_STRU         stDtxDrxNewTim;

}PHYITF_DTX_DRX_TIM_INFO_STRU;

/*****************************************************************************
 结构名    : PHYITF_DTX_DRX_PARAMS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DTX-DRX 相关参数
*****************************************************************************/
typedef struct
{

    PHYITF_BOOL_ENUM_UINT16             enDtxInfoValid;                         /* 是否存在DTX information*/
    PHYITF_BOOL_ENUM_UINT16             enDrxInfoValid;                         /* 是否存在DRX information*/

    PHYITF_DTX_INFO_STRU                stDtxInfo;
    PHYITF_DRX_INFO_STRU                stDrxInfo;

    VOS_UINT16                          usUlDpcchSlotFormatInfo;                /* Enumerated (1,4) */
    VOS_UINT16                          usReserved;

    PHYITF_DTX_DRX_TIM_INFO_STRU        stDtxDrxTimInfo;

}PHYITF_DTX_DRX_PARAMS_STRU;

/*****************************************************************************
 结构名    : PHYITF_HS_SCCH_LESS_TBS_LIST
 协议表格  :
 ASN.1描述 : Transport Block Size List
 结构说明  : CPC配置参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTBSizeIndex;                          /*Integer (1..90)*/

    PHYITF_BOOL_ENUM_UINT16             enHsPdschSndCodeSuppt;
} PHYITF_HS_SCCH_LESS_TBS_LIST_STRU;


/*****************************************************************************
 结构名    : PHYITF_HS_SCCH_LESS_NEW_OPERATION
 协议表格  :
 ASN.1描述 : New HS-SCCH less operation
 结构说明  : CPC配置参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usHsPdschCodeIndex;                     /* INTEGER(1..15) */
    VOS_UINT16                          usTBSizeCnt;                            /*1..< maxHS-SCCHLessTrBlk*/
    PHYITF_HS_SCCH_LESS_TBS_LIST_STRU   astHsScchLessTBsList[RRC_PHY_MAX_HSSCCH_LESS_TB_NUM];

} PHYITF_HS_SCCH_LESS_NEW_OPER_STRU;

/*****************************************************************************
 枚举名    : PHYITF_HS_SCCH_LESS_OPERATION_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum  PHYITF_HS_SCCH_LESS_OPERATION_ENUM
{
    PHYITF_HS_SCCH_LESS_OPERATION_CONTINUE = 0,
    PHYITF_HS_SCCH_LESS_OPERATION_NEW_OPERATION,
    PHYITF_HS_SCCH_LESS_OPERATION_BUTT
};
typedef VOS_UINT16  PHYITF_HS_SCCH_LESS_OPERATION_ENUM_UINT16;

/*****************************************************************************
 结构名    : PHYITF_HS_SCCH_LESS_INFO_STRU
 协议表格  :
 ASN.1描述 : HS-SCCH-LessInfo-r7
 结构说明  : HsScchLess 参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usReserved;

    PHYITF_HS_SCCH_LESS_OPERATION_ENUM_UINT16   enHsScchLessOperation;

    PHYITF_HS_SCCH_LESS_NEW_OPER_STRU           stHsScchLessNewOp;

} PHYITF_HS_SCCH_LESS_INFO_STRU;

/*****************************************************************************
 结构名    : RRC_PHY_CPC_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CPC配置参数
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;                                 /* 操作ID */

    VOS_INT16                           sActiveTime;                            /* 激活时间[-1,255], -1为立即激活 */
    PHYITF_BOOL_ENUM_UINT16             enNeedRevertDtxDrxOrder;                /* 是否需要回退DTX/DRX ORDER */
    PHYITF_BOOL_ENUM_UINT16             enNeedRevertHsscchLessOrder;            /* 是否需要回退HSSCCH-LESS ORDER */
    VOS_UINT16                          usRsv1;

    PHYITF_BOOL_ENUM_UINT16             enDtxDrxStatus;                         /* 0:DTX_DRX_STATUS为FALSE,1:DTX_DRX_STATUS为TRUE*/
    PHYITF_BOOL_ENUM_UINT16             enHsScchLessStatus;                     /* 0:HS_SCCH_LESS_STATUS为FALSE,1:HS_SCCH_LESS_STATUS为TRUE */

    PHYITF_DTX_DRX_PARAMS_STRU          stDtxDrxParams;

    PHYITF_HS_SCCH_LESS_INFO_STRU       stHsScchLessInfo;
}RRC_PHY_CPC_CONFIG_REQ_STRU;


/*****************************************************************************
 结构名    : PHY_RRC_CPC_CONFIG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CPC 配置应答
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;                          /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOpId;                           /* 操作标识 */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16  enIndicator;                      /* 配置结果,0代表成功，其它代表失败*/
    VOS_UINT16                                usReserve1;
}PHY_RRC_CPC_CONFIG_CNF_STRU;


/*****************************************************************************
 结构名    : RRC_PHY_CPC_DISABLE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 去激活和CPC的所有配置
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16              enMsgID;                            /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                              usOpId;                             /* 操作ID */
    VOS_INT16                               sActiveTime;                        /* 激活时间 */
    VOS_UINT16                              usReserve1;
}RRC_PHY_CPC_DISABLE_REQ_STRU;


/*****************************************************************************
 结构名    : PHY_RRC_CPC_DISABLE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 释放CPC所有的状态
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                                 /* 操作标识 */

} PHY_RRC_CPC_DISABLE_CNF_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*==========================================================================
               以下注释掉的结构用于生成ASN DLL结构
============================================================================*/

#if 0                                                                           /* _H2ASN_Skip */

/**************************************************************************
 结构名    : WAS_PHYITF_WRR_PHY_UL_POWER_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :上行功率控制结构

***************************************************************************/

typedef   struct
{
    /*增益因子选择域[1,2];
    1:Signal Gain Factor, 2:Computed Gain Factor*/
    VOS_UINT8                           ucGainFactor;
    VOS_UINT8                           ucReserved;

    VOS_UINT8                           ucBetaC;
    VOS_UINT8                           ucBetaD;

    /*[-1,3];-1:代表该TFC不做参考,即无效参考ID*/
    VOS_INT8                            cRefTfcId;

    /*[-5,10],*/
    VOS_INT8                            cPowerOffset;

}PHYITF_UL_POWER_CTRL_STRU;

/**************************************************************************
 结构名    : WAS_PHYITF_WRR_PHY_TFC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :传输格式组合结构

***************************************************************************/
typedef   struct
{
    VOS_UINT16                          usTfci;/*[0,1023]*/
    /*包含TRCH Num 个 数据*/
    VOS_UINT8                           aucTfiParam[4];
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:VOS_UINT16 MINIDX:1 MAXIDX:8 EXPORTNAME:usH2ASNTrchNum
    ******************************************************************************************************/

}PHYITF_DL_TFC_STRU;

/**************************************************************************
 结构名    : WAS_PHYITF_WRR_PHY_TFC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :传输格式组合结构

***************************************************************************/
typedef   struct
{
    VOS_UINT16                          usTfci;/*[0,1023]*/
    /*包含TRCH Num 个 数据*/
    VOS_UINT8                           aucTfiParam[4];
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:VOS_UINT16 MINIDX:1 MAXIDX:8 EXPORTNAME:usH2ASNTrchNum
    ******************************************************************************************************/
    PHYITF_UL_POWER_CTRL_STRU           stUlPowerCtrl;

}PHYITF_UL_TFC_STRU;

/**************************************************************************
 结构名    : WAS_PHYITF_WRR_PHY_TF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :传输格式数据结构

***************************************************************************/
typedef struct
{
    VOS_UINT16                          usTfi;          /*[0,32]*/
    VOS_UINT16                          usTBCnt;        /*[0,512];传输块个数*/
    VOS_UINT16                          usTBLen;        /*[0,5034];传输块长度*/

}PHYITF_TF_STRU;

/**************************************************************************
 结构名    : WAS_PHYITF_WRR_PHY_TFS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :TFS结构
***************************************************************************/
typedef struct
{
    /*[1,32];传输信道ID*/
    VOS_UINT8                           ucTrchID;

    /*[0,2]; 编码类型和编码效率；0-CC1/2,1-CC1/3,2-Turbo EnCoder*/
    VOS_UINT8                           ucCodeMethod;
    VOS_UINT16                          usRateMatch;    /*范围[1,256]*/
    VOS_UINT8                           ucCRCLen;       /*范围(0,8,12,16,24)*/
    VOS_UINT8                           ucTti;          /*范围(1,2,4,8)~(10,20,40,80)单位ms*/
    VOS_UINT16                          usTfNum;        /*TF的个数*/    /* _H2ASN_IE_DYNAMIC_ARRAY_EXPORT STRUTYPE:VOS_UINT16 EXPORTNAME:usH2ASNTfNum */
    VOS_UINT8                           aucTFListParam[4];
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:PHYITF_TF_STRU MINIDX:1 MAXIDX:32 EXPORTNAME:usH2ASNTfNum
    ******************************************************************************************************/

}PHYITF_TFS_STRU;


/**************************************************************************
 结构名    : WAS_PHYITF_WRR_PHY_TfcList
 协议表格  :
 ASN.1描述 :
 结构说明  :下行传输格式组合列表结构
***************************************************************************/
typedef struct
{
    VOS_UINT16                          usDlTfcCnt;   /* _H2ASN_IE_DYNAMIC_ARRAY_EXPORT STRUTYPE:VOS_UINT16 EXPORTNAME:usH2ASNDlTfcNum */

    VOS_UINT8                           aucDlTfcParam[4];
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:PHYITF_DL_TFC_STRU MINIDX:1 MAXIDX:128 EXPORTNAME:usH2ASNDlTfcNum
    ******************************************************************************************************/

}PHYITF_DL_TFCS_LIST_STRU;

/**************************************************************************
 结构名    : WAS_PHYITF_WRR_PHY_TfcList
 协议表格  :
 ASN.1描述 :
 结构说明  :上行传输格式组合列表结构
***************************************************************************/
typedef struct
{
    VOS_UINT16                          usUlTfcCnt;   /* _H2ASN_IE_DYNAMIC_ARRAY_EXPORT STRUTYPE:VOS_UINT16 EXPORTNAME:usH2ASNUlTfcNum */

    VOS_UINT8                           aucUlTfcParam[4];
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:PHYITF_UL_TFC_STRU MINIDX:1 MAXIDX:128 EXPORTNAME:usH2ASNUlTfcNum
    ******************************************************************************************************/

}PHYITF_UL_TFCS_LIST_STRU;

/**************************************************************************
 结构名    : WAS_PHYITF_WRR_PHY_UlCcTrch
 协议表格  :
 ASN.1描述 :
 结构说明  :下行CCTRCH结构
***************************************************************************/
typedef struct
{
    /*[3,4]; 3:PRACH, 4: ULDPCH*/
    VOS_UINT16                          usCcTrchId;

    /*[-1,255],-1 立即启动*/
    VOS_INT16                           sActiveTime;

    /*最小扩频因子(4,8,16,32,64,128,256)*/
    VOS_UINT16                          usMinSf;

    /*打空极限:(40,44,48,52,56,60,64,68,72,76,80,84,88,92,96,100)*/
    VOS_UINT16                          usPL;

    /*[1,32]*/
    VOS_UINT16                          usTrchNum;          /* _H2ASN_IE_DYNAMIC_ARRAY_EXPORT STRUTYPE:VOS_UINT16 EXPORTNAME:usH2ASNTrchNum */

    VOS_UINT8                           aucTrchParam[4];
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:PHYITF_TFS_STRU MINIDX:1 MAXIDX:8 EXPORTNAME:usH2ASNTrchNum
    ******************************************************************************************************/
    PHYITF_UL_TFCS_LIST_STRU            stUlTfcs;

}PHYITF_UL_CCTRCH_STRU;

typedef struct
{
    /*选择的传输信道条数,最大8条*/
    VOS_UINT8                           ucSelTrChNum;

    /*有效范围 [1~32,0XFF] 用于外环功控,第1条传输信道ID*/
    VOS_UINT8                           ucTrch1ID;

    /*有效范围 [1~32,0XFF] 用于外环功控,第2条传输信道ID*/
    VOS_UINT8                           ucTrch2ID;

    /*有效范围 [1~32,0XFF] 用于外环功控,第3条传输信道ID*/
    VOS_UINT8                           ucTrch3ID;

    /*有效范围 [1~32,0XFF] 用于外环功控,第4条传输信道ID*/
    VOS_UINT8                           ucTrch4ID;

    /*有效范围 [1~32,0XFF] 用于外环功控,第5条传输信道ID*/
    VOS_UINT8                           ucTrch5ID;

    /*有效范围 [1~32,0XFF] 用于外环功控,第6条传输信道ID*/
    VOS_UINT8                           ucTrch6ID;

    /*有效范围 [1~32,0XFF] 用于外环功控,第7条传输信道ID*/
    VOS_UINT8                           ucTrch7ID;

    /*有效范围 [1~32,0XFF] 用于外环功控,第8条传输信道ID*/
    VOS_UINT8                           ucTrch8ID;

    /*初始SirTarget*/
    VOS_UINT8                           ucInitailSirTarget;

    /*信令传输信道ID,0XFF代表无效*/
    VOS_UINT8                           ucSigTrchID;

    /*上行功控步长因子,步长0.1,即实际值为配置值*0.1 */
    VOS_UINT8                           ucUpStepSizeFactor;

    /*下行功控步长因子,步长0.1,即实际值为配置值*0.1 */
    VOS_UINT8                           ucDownStepSizeFactor;

    /*信令上行功控步长因子,步长0.1,即实际值为配置值*0.1 */
    VOS_UINT8                           ucSigUpStepSizeFactor;

    /*信令下行功控步长因子,步长0.1,即实际值为配置值*0.1 */
    VOS_UINT8                           ucSigDownStepSizeFactor;

    /*SirTarget的增量,[-128 --- 127]*/
    VOS_INT8                            cDeltaSirTarget;

	/*TOT OLPC FadeMargin的权值*/
    VOS_UINT16                           usMapWeight;

}PHYITF_OLPC_TRCHID_STRU;

/**************************************************************************
 结构名    : PHYITF_DL_CCTRCH_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 下行CCTRCH
***************************************************************************/
typedef struct
{
    /*[1,2]; 1:SCCPCH, 2:DLDPCH*/
    VOS_UINT16                          usCcTrchId;

#if FEATURE_WCBS == FEATURE_ON
    VOS_UINT16                           usCctrchIndex;        /* cctrch的索引和物理信道对应 */
    PHYITF_SCCPCH_DEMODULATE_ENUM_UINT16 enSccpchDemInd;       /* 解调指示，目前仅sccpch采用 */
    PHYITF_BOOL_ENUM_UINT16              enSupportCtch;        /* 是否支持cbs */
    VOS_UINT16                           usReserv1;            /* 保留 */
#endif

    /*[-1,255]; -1 立即启动*/
    VOS_INT16                           sActiveTime;

    /*[0,17]; 时隙格式*/
    VOS_UINT8                           ucSlotFmt;

    /*[0,1]; 0:flexible position, 1:fixed position*/
    VOS_UINT8                           ucDTXPos;

    /*[1,8]; 传输信道个数*/
    VOS_UINT16                          usDlTrchNum;    /* _H2ASN_IE_DYNAMIC_ARRAY_EXPORT STRUTYPE:VOS_UINT16 EXPORTNAME:usH2ASNTrchNum */

    VOS_UINT8                           aTrchParams[4];
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:PHYITF_TFS_STRU MINIDX:1 MAXIDX:8 EXPORTNAME:usH2ASNTrchNum
    ******************************************************************************************************/

    PHYITF_DL_TFCS_LIST_STRU            stDlTfcs;
    PHYITF_OLPC_TRCHID_STRU             stOlpcTrchId;

}PHYITF_DL_CCTRCH_STRU;

/*****************************************************************************
 结构名    : PHYITF_CCTRCH_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 码组合传输信道结构,用于ASN1生成的描述结构
*****************************************************************************/
typedef struct
{
    PHYITF_CCTRCH_ID_ENUM_UINT16        enCctrchId;  /* 传输信道类型 */         /* _H2ASN_IeChoice_Export PHYITF_CCTRCH_ID_ENUM_UINT16 */
    VOS_UINT16                          usParamLen;  /* 配置的CcTrch长度 */

    union                                                                       /* _H2ASN_Skip */
    {                                                                           /* _H2ASN_Skip */
        VOS_UINT16                      stPccpchPara;                           /* _H2ASN_Skip */
        VOS_UINT16                      stSccpchPara;                           /* _H2ASN_Skip */
        VOS_UINT16                      stDlDpchPara;                           /* _H2ASN_Skip */
        VOS_UINT16                      stPrachPara;                            /* _H2ASN_Skip */
        VOS_UINT16                      stUlDpchPara;                           /* _H2ASN_Skip */
        VOS_UINT16                      stHsdpaPara;                            /* _H2ASN_Skip */
        VOS_UINT16                      stHsupaPara;
        /******************************************************************************************************
            _H2ASN_IeChoice_When        PHYITF_CCTRCH_ID_ENUM_UINT16
        ******************************************************************************************************/
    }u;                                                                         /* _H2ASN_Skip */
}PHYITF_CCTRCH_PARA_STRU;

/* 用于生成ASN.1时RL动态数组的类型 */
typedef struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16       enPhyType;    /* _H2ASN_IeChoice_Export PHYITF_PHYCH_TYPE_ENUM_UINT16 */

    union                                                                       /* _H2ASN_Skip */
    {                                                                           /* _H2ASN_Skip */
        PHYITF_SCCPCH_PARA_STRU         stSccpchPara;                           /* _H2ASN_Skip */
        PHYITF_PICH_STRU                stPichPara;                             /* _H2ASN_Skip */
        PHYITF_AICH_STRU                stAichPara;                             /* _H2ASN_Skip */
        PHYITF_PRACH_STRU               stPrachPara;                            /* _H2ASN_Skip */
        PHYITF_DOWNLINK_DPCH_PARA_STRU  stDlDpchPara;                           /* _H2ASN_Skip */
        PHYITF_UPLINK_DPCH_STRU         stUlDpchPara;                           /* _H2ASN_Skip */
        PHYITF_HSDPA_PHY_STRU           stHsdpaPara;                            /* _H2ASN_Skip */
        PHYITF_UL_HSUPA_PHY_STRU        stUlHsupaPara;                          /* _H2ASN_Skip */
        PHYITF_DL_HSUPA_PHY_STRU        stDlHsupaPara;                          /* _H2ASN_Skip */
        PHYITF_DOWNLINK_FDPCH_PARA_STRU stDlFdpchPara;                          /* _H2ASN_Skip */
        PHYITF_HSDPAPLUS_PHY_STRU       stHsdpaPlusPara;                        /* _H2ASN_Skip */
        PHYITF_FACH_HSDPAPLUS_PHY_STRU  stFachHsdpaPlusPara;                    /* _H2ASN_Skip */
        PHYITF_E_RACH_REQ_STRU          stERachPara;                            /* _H2ASN_Skip */
        PHYITF_SCND_HSDPAPLUS_PHY_STRU  stScndHsdpaPlus;
        /******************************************************************************************************
            _H2ASN_IeChoice_When        PHYITF_PHYCH_TYPE_ENUM_UINT16
        ******************************************************************************************************/
    }u;                                                                         /* _H2ASN_Skip */
}PHYITF_RL_PARA_STRU;

/* 用于生成ASN.1时RL动态数组的类型 */
typedef struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16       enPhyType;    /* _H2ASN_IeChoice_Export PHYITF_PHYCH_TYPE_ENUM_UINT16 */
    PHYITF_UL_HSUPA_PHY_STRU            stUlHsupaPara;

}PHYITF_RL_PARA_UL_HSUPA_STRU;

/* 用于生成ASN.1时RL动态数组的类型 */
typedef struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16       enPhyType;    /* _H2ASN_IeChoice_Export PHYITF_PHYCH_TYPE_ENUM_UINT16 */
    PHYITF_AICH_STRU                    stAichPara;

}PHYITF_RL_PARA_AICH_STRU;


enum PHYITF_TGPS_STATE_ENUM
{
    PHYITF_TGPS_STATE_ACTIVE            = 0,
    PHYITF_TGPS_STATE_INACTIVE          = 1,
    PHYITF_TGPS_STATE_NOCHG_ACTIVE      = 2,    /* 状态不变，原状态为Active */
    PHYITF_TGPS_STATE_NOCHG_INACTIVE    = 3,    /* 状态不变，原状态为Inactive */
    PHYITF_TGPS_STATE_BUTT
};
typedef VOS_UINT16  PHYITF_TGPS_STATE_ENUM_UINT16;

typedef struct
{
    VOS_UINT16                          usTGPSI;
    PHYITF_TGPS_STATE_ENUM_UINT16       enTGPSFlag;
    VOS_UINT16                          usTGCfn;
}PHYITF_TGPS_PARA_STRU;

typedef struct
{
    VOS_UINT16                          usTGPSReCfgCfn;
    VOS_UINT16                          usTGPSNum;      /* _H2ASN_IE_DYNAMIC_ARRAY_EXPORT STRUTYPE:VOS_UINT16 EXPORTNAME:usH2ASNTGPSNum */
    VOS_UINT8                           astTGPSPara[4];
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:PHYITF_TGPS_PARA_STRU MINIDX:1 MAXIDX:6 EXPORTNAME:usH2ASNTGPSNum
    ******************************************************************************************************/
}PHYITF_COMP_MODE_CHG_PARA_STRU;


/*****************************************************************************
  H2ASN顶级消息结构定义,无头消息，搜网优化GTR工程定义
*****************************************************************************/
typedef struct
{
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;    /* _H2ASN_MsgChoice_Export RRC_PHY_MSG_ID_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          RRC_PHY_MSG_ID_ENUM_UINT16
    ****************************************************************************/
}RRC_PHY_MSG_DATA_NO_LENGTH;


/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;    /* _H2ASN_MsgChoice_Export RRC_PHY_MSG_ID_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          RRC_PHY_MSG_ID_ENUM_UINT16
    ****************************************************************************/
}RRC_PHY_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    RRC_PHY_MSG_DATA                    stMsgData;
}RrcPhyInterface_MSG;
#endif                                                                          /* _H2ASN_Skip */


/*==========================================================================
                              用于RTT测试的测试命令
============================================================================*/

/*****************************************************************************
 枚举名    : PHYITF_RTT_REG_CONFIG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 寄存器操作的枚举定义

*****************************************************************************/
enum    PHYITF_RTT_REG_CONFIG_ENUM
{
    PHYITF_RTT_REG_READ              = 0,       /* _H2ASN_MsgChoice PHYITF_RTT_REG_READ_STRU */
    PHYITF_RTT_REG_WRITE             = 1,       /* _H2ASN_MsgChoice PHYITF_RTT_REG_WRITE_STRU */
    PHYITF_RTT_REG_BUTT
};
typedef VOS_UINT16 PHYITF_RTT_REG_CONFIG_ENUM_UINT16;
typedef struct
{
    VOS_UINT32                          ulRegCfgAddr;       /* 配置寄存器地址 */
    VOS_UINT32                          ulRegCfgValue;      /* 配置寄存器值 */
} PHYITF_RTT_TEST_REG_WRITE_ADDR_STRU;

typedef struct
{
    VOS_UINT16                          usRegCfgNum;
    PHYITF_BOOL_ENUM_UINT16             usRptFlag;    /*0为停止周期上报，1为启动上报,非周期上报此IE无效*/
    VOS_UINT16                          usRptNum;   /*寄存器值上报的次数，0为周期性上报*/
    VOS_UINT16                          usRptPeriod;   /*上报的周期，10ms为单位*/
    VOS_UINT32                          ulRttTestRegReadAddr[RRC_PHY_MAX_RTT_REG_NUM];
} PHYITF_RTT_REG_READ_STRU;

typedef struct
{
    VOS_UINT16                                  usRegWriteNum;
    VOS_UINT8                                   ucReserve[2];
    PHYITF_RTT_TEST_REG_WRITE_ADDR_STRU         astRttTestRegWriteAddr[RRC_PHY_MAX_RTT_REG_NUM];
} PHYITF_RTT_REG_WRITE_STRU;
/*****************************************************************************
 结构名    : RRC_PHY_RTT_TEST_CFG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 用于RTT测试时，通过ITT下发配置命令，由HPA完成
             对于寄存器的配置，以及打印寄存器。
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16              enMsgID;            /* 原语类型 *//*_H2ASN_Skip*/
    PHYITF_RTT_REG_CONFIG_ENUM_UINT16       enRegCfgChoice;     /*对寄存器的操作选择*/ /* _H2ASN_IeChoice_Export PHYITF_RTT_REG_CONFIG_ENUM_UINT16 */

    union                                                                       /*_H2ASN_Skip*/
    {                                                                           /*_H2ASN_Skip*/
        PHYITF_RTT_REG_READ_STRU                stRegRead;      /*_H2ASN_Skip*/
        PHYITF_RTT_REG_WRITE_STRU               stRegWrite;
        /******************************************************************************************************
            _H2ASN_IeChoice_When        PHYITF_RTT_REG_CONFIG_ENUM_UINT16
        ******************************************************************************************************/
    }unRegMode;                                                                /*_H2ASN_Skip*/
} RRC_PHY_RTT_TEST_REG_CFG_REQ_STRU;
typedef struct
{
    VOS_UINT32  ulAddress;
    VOS_UINT32  ulValue;
} PHYITF_RTT_TEST_REG_INFO_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_RTT_TEST_REG_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 寄存器值的上报结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                      /*_H2ASN_Skip*/
    VOS_UINT16                      usMsgName;      /* 原语类型 *//*_H2ASN_Skip*/
    VOS_UINT16                      usCfn;
    VOS_UINT16                      usSfn;
    VOS_UINT16                      usCnt;      /* 上报的寄存器个数 */
    PHYITF_RTT_TEST_REG_INFO_STRU        astRegInfo[RRC_PHY_MAX_RTT_REG_NUM];

}PHY_RRC_RTT_TEST_REG_IND_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_RTT_TEST_CFG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 用于RTT测试时，通过ITT下发配置命令，由HPA完成
             对于寄存器的配置，以及打印寄存器。
             CNF消息返回当前配置的状态。
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;            /* 原语类型 *//*_H2ASN_Skip*/
    PHYITF_BOOL_ENUM_UINT16             enResult;           /* 配置结果 */
} PHY_RRC_RTT_TEST_CFG_CNF_STRU;

/*****************************************************************************
 结构名    : RRC_PHY_PRACH_INIT_TX_POWER_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 周期接收SIB7,根据接收的SIB7中的参数，配置物理层的发射功率
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                       /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                 /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_INT16                                   sPrachInitialTxPower;    /* 配置给物理层的初始发射功率 */
}RRC_PHY_PRACH_INIT_TX_POWER_IND_STRU;

/*****************************************************************************
 结构名    : RRC_PHY_SCND_RL_SETUP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 信道建立请求消息的数据结构
             包含了要建立的信道
             使用该原语的信道为:

             PHYITF_PHY_SCND_HSDPAPLUS
             PHYITF_PHY_SCND_FDPCH
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                          usOPID;                 /* 操作标识 */
    VOS_UINT16                          usPhyChannelNum;        /* 物理信道数 *//* _H2ASN_IE_DYNAMIC_ARRAY_EXPORT STRUTYPE:VOS_UINT16 EXPORTNAME:usH2ASNPhyChannelNum */
    VOS_UINT16                          usParaSize;             /* 参数长度 */

    VOS_UINT8                           aucPhyChannelPara[4];   /* 物理信道配置参数 */
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:PHYITF_RL_PARA_STRU MINIDX:1 MAXIDX:8 EXPORTNAME:usH2ASNPhyChannelNum
    ******************************************************************************************************/

}RRC_PHY_SCND_RL_SETUP_REQ_STRU;


/*****************************************************************************
 结构名    : RRC_PHY_SCND_RL_MODIFY_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 信道建立请求消息的数据结构
             包含了要建立的信道
             使用该原语的信道为:


             PHYITF_PHY_SCND_UL_HSUPA
             PHYITF_PHY_SCND_DL_HSUPA
             PHYITF_PHY_SCND_FDPCH
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                          usOPID;                 /* 操作标识 */
    VOS_UINT16                          usPhyChannelNum;        /* 物理信道数 *//* _H2ASN_IE_DYNAMIC_ARRAY_EXPORT STRUTYPE:VOS_UINT16 EXPORTNAME:usH2ASNPhyChannelNum */
    VOS_UINT16                          usParaSize;             /* 参数长度 */

    VOS_UINT8                           aucPhyChannelPara[4];   /* 物理信道配置参数 */
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:PHYITF_RL_PARA_STRU MINIDX:1 MAXIDX:8 EXPORTNAME:usH2ASNPhyChannelNum
    ******************************************************************************************************/

}RRC_PHY_SCND_RL_MODIFY_REQ_STRU;



/*****************************************************************************
 结构名    : PHY_RRC_SCND_RL_SETUP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 信道建立证实消息的数据结构
             每条RRC_PHY_SCND_RL_SETUP_REQ_STRU消息对应一条CNF消息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* 操作标识 */

    VOS_UINT16                          usReserve1;             /* 字节对齐*/
    VOS_UINT16                          usPhyChannelNum;        /* 物理信道Num数*/
    PHY_RRC_RL_EACH_CHANNEL_CNF_STRU    astPhyChannelCnf[RRC_PHY_MAX_PHYCHAN_NUM];

}PHY_RRC_SCND_RL_SETUP_CNF_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_SCND_RL_MODIFY_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 信道修改证实消息的数据结构
             每条RRC_PHY_SCND_RL_MODIFY_REQ_STRU消息对应一条CNF消息

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* 操作标识*/

    VOS_UINT16                          usReserve1;             /* 字节对齐*/
    VOS_UINT16                          usPhyChannelNum;        /* 物理信道Num数*/
    PHY_RRC_RL_EACH_CHANNEL_CNF_STRU    astPhyChannelCnf[RRC_PHY_MAX_PHYCHAN_NUM]; /* 配置结果，定义同setup*/

}PHY_RRC_SCND_RL_MODIFY_CNF_STRU;

/*****************************************************************************
 结构名    : RRC_PHY_SCND_RL_REL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 辅载波信道释放请求消息的数据结构
             包含了要释放的信道

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;            /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                          usOPID;             /* 操作标识 */
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usPhyChannelNum;    /* 物理信道数 */
    PHYITF_PHY_REL_CHANNEL_INFO_STRU    astPhyChInfo[RRC_PHY_MAX_PHYCHAN_NUM];

}RRC_PHY_SCND_RL_REL_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_SCND_RL_REL_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 信道释放证实消息的数据结构
             每条RRC_PHY_SCND_RL_RELEASE_REQ_STRU消息对应一条CNF消息

*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* 操作标识 */

    VOS_UINT16                          usReserve1;             /* 字节对齐*/
    VOS_UINT16                          usPhyChannelNum;        /* 物理信道Num数*/
    PHY_RRC_RL_EACH_CHANNEL_CNF_STRU    astPhyChannelCnf[RRC_PHY_MAX_PHYCHAN_NUM]; /* 配置结果，定义同setup*/

}PHY_RRC_SCND_RL_REL_CNF_STRU;


/*****************************************************************************
 结构名    :
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PHYITF_BOOL_ENUM_UINT16                 enSoffsetValid;                     /* 指示usSoffset是否存在  */
    VOS_UINT16                              usSoffset;                          /* 范围Integer(0..9) 单位 256chips */
    VOS_UINT16                              usFdpchCodeNum;                     /* F-DPCH Code number */

    PHYITF_BOOL_ENUM_UINT16                 enERgchValid;                       /* 指示stERgchInfo是否存在  */
    PHYITF_E_RGCH_INFO_STRU                 stERgchInfo;                        /* OPTIONAL */

    PHYITF_E_HICH_INFO_STRU                 stEHichInfo;                        /* MP */

    /*上行DPCCH相关配置 */
    PHYITF_SCRAMBL_CODE_TYPE_ENUM_UINT16    enScrambCodeType;                   /* Scrambling code type Enumerated(short, long)*/

    PHYITF_BOOL_ENUM_UINT16                 enScrambCodeNumValid;               /* 指示ulScrambCodeNum是否存在，MD计算按10.3.6.87b  */
    VOS_UINT32                              ulScrambCodeNum;                    /* Integer(0..16777215) */

}PHYITF_COMMON_EDCH_RES_CFG_INFO_STRU;

/*****************************************************************************
 结构名    : PHYITF_COMMON_EDCH_RES_CFG_INFO_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usRsv1;                             /* 四字节对齐，保留 */
    VOS_UINT16                              usCommEdchResNum;                   /* EDCH资源数 */
    PHYITF_COMMON_EDCH_RES_CFG_INFO_STRU    astCommonEdchResCfgInfo[PS_WUE_MAX_EDCHS];

}PHYITF_COMMON_EDCH_RES_CFG_INFO_LIST_STRU;


/*****************************************************************************
 结构名    : PHYITF_SCND_DL_FDPCH_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTpcErrorRateTarget;                   /* 因为原值精度为0.01, 为了保持精度目前配置值是原始值扩大100倍*/
    VOS_INT16                           sInitialSirTarget;                      /* 初始SirTarget用于外环功控 ,
                                                                                    E-RACH时每次配置都填写初始值,F2D重配填写初始值 */
    VOS_INT16                           sDeltaSirTarget;                        /* 用于DPCH与FDPCH切换时的补偿量，
                                                                                   E-RACH时填写0 */
    VOS_UINT16                          usUpStepSizeFactor ;
    VOS_UINT16                          usDownStepSizeFactor ;

    VOS_UINT16                          usReserve1;                             /* 四字节对齐，保留 */

}PHYITF_FDPCH_OLPC_PARA_STRU;

typedef struct
{

    PHYITF_FREQ_INFO_STRU                   stFdpchFreqInfo;                    /* 频率信息 */

    PHYITF_FDPCH_OLPC_PARA_STRU             stFdpchOlpcPara;                    /* 外环功控参数 */

    VOS_UINT16                              usFdpchSlotFormat;                  /* INTEGER(0..9)  OPTIONAL :根据331提供的默认参数进行配置 */
    PHYITF_TX_DIVER_IND_ENUM_UINT16         enTDIndicator;                      /* 分集指示 :配置为非分集*/
    VOS_UINT16                              usDownLinkScramCode;                /* 下行链路主扰码号  */
    PHYITF_DPC_MODE_TYPE_ENUM_UINT16        enDpcMode;                          /* 下行功率控制:根据331提供的默认参数进行配置 */

    PHYITF_TX_DIVER_IND_ENUM_UINT16         enPcpichTDIndicator;                /* 主导频信道是否使用发分集,0:不使用分集,1:STTD分集,0xFF:无法获得分集方式 */

    VOS_UINT16                              usReserve1;                         /* 四字节对齐，保留 */
}PHYITF_DOWNLINK_FDPCH_E_RACH_STRU;


/*****************************************************************************
 结构名    : PHYITF_UPLINK_DPCH_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上行专用物理信道信息
 *****************************************************************************/
typedef struct
{
    PHYITF_FREQ_INFO_STRU                stFreqInfo;
    PHYITF_ULDPCH_POWER_CONTROL_STRU     stUlDpchPowerControl;
    VOS_UINT16                           usDpchNum;                              /* 上行DPDCH的数量:固定填0 */
    VOS_UINT16                           usSlotFormat;                           /* 上行DPCCH使用的时隙格式 */
}PHYITF_UPLINK_DPCH_E_RACH_STRU;


/*****************************************************************************
 结构名    : PHYITF_E_RACH_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :上行增强CELL_FACH 相关参数结构
*****************************************************************************/

typedef struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16                   enPhyChannelType;           /* _H2ASN_Skip */
    VOS_INT16                                       sActiveTime;                /* 固定-1,表示立即激活 */

    PHYITF_PRACH_STRU                               stPrachPara;                /* _H2ASN_Replace PHYITF_RL_PARA_STRU *//* PRACH 信道相关参数配置 */

    VOS_INT16                                       sPowerOffsetPpE;            /* Power offset Pp-e [-5...10]*/

    PHYITF_BOOL_ENUM_UINT16                         enEAiInd;                   /* eai是否有效 */
    PHYITF_AICH_STRU                                stAichPara;                 /* _H2ASN_Replace PHYITF_RL_PARA_AICH_STRU *//* AICH 信道相关参数 */

    PHYITF_UPLINK_DPCH_E_RACH_STRU                  stUpLinkDpch;

    VOS_UINT16                                      usAddEdchTransBackOff;      /* 范围: (0..15) 单位: TTI Additional E-DCH transmission back off  */
    VOS_UINT16                                      usMaxAllocEdchResForCCCH;   /* Enumerated (8, 12, 16, 24, 32, 40, 80, 120),单位 TTI Maximum E-DCH resource allocation for CCCH */
    VOS_UINT16                                      usMaxPrdForCollision;       /* Maximum period for collision resolution phase Integer (8..24) TTI*/
    VOS_UINT16                                      usEdchTransContinuBackOff;  /* E-DCH transmission continuation back off Enumerated (0, 8, 16, 24, 40, 80, 120, infinity)， infinity时填0xffff */
    PHYITF_BOOL_ENUM_UINT16                         enAckNackValid;             /* 是否上报ack和nack */

    /* 这条链路的导频信道的主扰码，因为目前只支持主导频信道
    所以E_HICH,E_AGCH,E_RGCH都使用这个扰码作为自己信道的扰码 */
    VOS_UINT16                                      usPrimScramCode;
    PHYITF_E_AGCH_INFO_STRU                         stEAgchInfo;                /* MP */

    PHYITF_UL_HSUPA_PHY_STRU                        stUlHsupaPara;              /* _H2ASN_Replace PHYITF_RL_PARA_UL_HSUPA_STRU *//*上行HSUPA */

    PHYITF_DOWNLINK_FDPCH_E_RACH_STRU               stDlFdpchPara;              /* F-DPCH相关参数 */

    PHYITF_HS_DPCCH_INFO_STRU                       stHsDpcchInfo;              /* HS-DPCCH相关参数 */

    PHYITF_COMMON_EDCH_RES_CFG_INFO_LIST_STRU       stCommEdchResCfgList;       /* Common E-DCH Resource Configuration information list */

}PHYITF_E_RACH_REQ_STRU;

/* DC HSUPA BEGINE */
/*****************************************************************************
 结构名    : RRC_PHY_SCND_UL_FREQ_DEACTIVE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Secondary serving E-DCH cell info
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                          usOPID;                 /* 操作标识*/
}RRC_PHY_SCND_UL_FREQ_DEACTIVE_REQ_STRU;


/*****************************************************************************
 结构名    : PHY_RRC_SCND_UL_FREQ_DEACTIVE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 对于RRC_PHY_SCND_UL_FREQ_DEACTIVE_REQ的回复
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* 操作标识 */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16  enIndicator;      /* 配置结果,0代表成功，其它代表失败*/
    VOS_UINT16                                usReserve1;
}PHY_RRC_SCND_UL_FREQ_DEACTIVE_CNF_STRU;

/*****************************************************************************
 结构名    : PHYITF_SCND_EDCH_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Secondary serving E-DCH cell info
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                          usPcPrb;                    /* INTEGER(0..7) */
    PHYITF_SCRAMBL_CODE_TYPE_ENUM_UINT16                enScramCodeType;            /* 扰码类型 */
    VOS_UINT32                                          ulScramCodeNum;             /* 扰码数 */

    VOS_UINT16                                          us2msSchedGrantProcAlloc;   /*BITMAP,2ms TTI,调度授权进程配置,该MAC-d流的数据
                                                                                        只能在BIT位取值为1的进程上发送,Bit0对应进程7，Bit1对应进程6，以此类推...
                                                                                        网络不携带表示全选，Default value is: transmission in all HARQ processes is allowed.无效填写:0xFFFF*/
    VOS_UINT16                                          usPrimScndGrantSelect;      /* 服务授权选择,0选择主的,1选择辅的,OP*/
    PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_ENUM_UINT16    enMinReducEDpdchGainFactor; /* ENUMERATED  OPTIONAL */


    PHYITF_BOOL_ENUM_UINT16                             enEDchMinSetETfciValid; /* usEDchMinSetETfci 是否有效，若有效，则enEDchMinSetETfciValid为1，否则enEDchMinSetETfciValid为0 */
    VOS_UINT16                                          usEDchMinSetETfci;          /* INTEGER(0..127)  OPTIONAL */
    VOS_UINT16                                          usDpcchPwrOffsetScndUlFreq; /* INTEGER(0..7) */

}PHYITF_SCND_EDCH_INFO_COMM_STRU;

/*****************************************************************************
 结构名    : PHYITF_SCND_UL_HSUPA_PHY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{

    PHYITF_PHYCH_TYPE_ENUM_UINT16       enPhyChannelType;                       /* _H2ASN_Skip */
    VOS_INT16                           sActiveTime;                            /* 激活的时间CFN,-1表示立即激活,否则表示激活的CFN */
    VOS_UINT16                          usUlFreqInfo;                           /* 辅载波上行频率信息 */
    VOS_UINT16                          usFreqBandNo;                           /* 频段号:1,2,3,4,5,6*/
    VOS_UINT16                          usTxRxFreqSeparation;                   /* 收发频差*/
    VOS_UINT16                          usReserve1;
    PHYITF_SCND_EDCH_INFO_COMM_STRU     stScndEdchInfoComm;

}PHYITF_SCND_UL_HSUPA_PHY_STRU;

/*****************************************************************************
 结构名    : PHYITF_SCND_DL_HSUPA_PHY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{

    PHYITF_PHYCH_TYPE_ENUM_UINT16               enPhyChannelType;               /* _H2ASN_Skip */

    VOS_INT16                                   sActiveTime;                    /*激活的时间CFN,-1表示立即激活,否则表示激活的CFN*/

    PHYITF_DL_PER_EDCH_RL_LIST_STRU             stDlRLInfo;                     /*下行RL 信息,当DlRLInfo置位时有效*/
}PHYITF_SCND_DL_HSUPA_PHY_STRU;

/*****************************************************************************
 结构名    : PHYITF_FDPCH_INFO_ON_SND_UL_FREQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Downlink F-DPCH info for each RL 10.3.6.23ob
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usFdpchFrameOffset;             /* INTEGER(0..149) */
    VOS_UINT16                                  usFdpchSlotFormat;              /* INTEGER(0..9)  OPTIONAL */
    VOS_UINT16                                  usReserve1;

    PHYITF_BOOL_ENUM_UINT16                     enSecndCpichValidInd;           /* 是否存在*/
    PHYITF_SECOND_CPICH_STRU                    stSecondCpichInfo;              /*辅导频配置信息*/

    VOS_UINT16                                  usSecScramCode;                 /* 第二扰码，如果不存在使用0表示无效 */
    VOS_UINT16                                  usOvsfCodeNum;                  /* 扩频码   */
    VOS_UINT16                                  usTpcCombIndex;                 /* TPC组合索引 */
    PHYITF_TX_DIVER_IND_ENUM_UINT16             enTDIndicator;                  /* 分集指示 */

}PHYITF_FDPCH_INFO_ON_SCND_UL_FREQ_STRU;

/*****************************************************************************
 结构名    : PHYITF_SCND_DL_FDPCH_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{

    PHYITF_PHYCH_TYPE_ENUM_UINT16               enPhyChannelType;               /* _H2ASN_Skip */
    VOS_INT16                                   sActiveTime;                    /*激活的时间CFN,-1表示立即激活,否则表示激活的CFN*/
    VOS_UINT16                                  usPrimScramCode;                /* 主扰码 */
    VOS_UINT16                                  usReserve1;

    PHYITF_FREQ_INFO_STRU                       stFdpchFreqInfo;                /* 频率信息 */

    PHYITF_FDPCH_INFO_ON_SCND_UL_FREQ_STRU      stDlFdpchInfoPerRlSecUlFreq;
    PHYITF_FDPCH_OLPC_PARA_STRU                 stFdpchOlpcPara;
    PHYITF_BOOL_ENUM_UINT16                     enNeedRevertOrder;              /* 是否需要回退HS_SCCH order,应用场景切换失败回退,SCND_RL_SETUP时才可能填写PS_TRUE */
    PHYITF_TX_DIVER_IND_ENUM_UINT16             enPcpichTDIndicator;            /*主导频信道是否使用发分集,0:不使用分集,1:STTD分集,0xFF:无法获得分集方式*/
    PHYITF_JUDGE_SYNC_STRU                      stJudgeSync;                    /* 同失步判决参数 */

}PHYITF_SCND_DL_FDPCH_PARA_STRU;

/* DC HSUPA END */

/*****************************************************************************
 枚举名    : PHYITF_BUSINESS_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : SET WORK MODE的类型
*****************************************************************************/
enum    PHYITF_BUSINESS_TYPE_ENUM
{
    PHYITF_BUSINESS_TYPE_NORMAL        = 0,          /* 信令模式 */
    PHYITF_BUSINESS_TYPE_CT            = 1,
    PHYITF_BUSINESS_TYPE_NO_SIG_BT     = 2,
    PHYITF_BUSINESS_TYPE_SIG_BT        = 3,
    PHYITF_BUSINESS_TYPE_BUTT
};
typedef VOS_UINT16 PHYITF_BUSINESS_TYPE_ENUM_UINT16;

/*****************************************************************************
 结构名    : RRC_PHY_SET_WORK_MODE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知物理层当前物理层的模式为主模还是从模模式
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* 操作标识 */

    VOS_RATMODE_ENUM_UINT32              enMasterMode;          /* _H2ASN_Replace VOS_UINT32 enMasterMode; */
    VOS_RATMODE_ENUM_UINT32              enSlaveMode;           /* _H2ASN_Replace VOS_UINT32 enSlaveMode; */

    PHYITF_BUSINESS_TYPE_ENUM_UINT16    enBusinessType;          /* SET WORK MODE的类型，WAS固定填PHYITF_BUSINESS_TYPE_NORMAL */
    PHYITF_BOOL_ENUM_UINT16             enNvUpdateFlag;          /* 是否需要更新NV，信令模式固定填FALSE */
}RRC_PHY_SET_WORK_MODE_REQ_STRU;

/*****************************************************************************
 结构名    : RRC_PHY_SET_RAT_PRI_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 设置模式优先级
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* 操作标识 */

    PHYITF_RAT_PRI_ENUM_UINT16          enWcdmaPri;                             /* WCDMA优先级 */
    PHYITF_RAT_PRI_ENUM_UINT16          enGsmPri;                               /* GSM优先级 */
    PHYITF_RAT_PRI_ENUM_UINT16          enLtePri;                               /* LTE优先级 */
    VOS_UINT16                          usReserve1;             /* 字节对齐*/
}RRC_PHY_SET_RAT_PRI_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_SET_WORK_MODE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 对RRC_PHY_SET_WORK_MODE_REQ_STRU的回复
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* 操作标识 */

    VOS_UINT16                                ausReserve1[2];
}PHY_RRC_SET_WORK_MODE_CNF_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_SET_RAT_PRI_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 对于RRC_PHY_SET_RAT_PRI_REQ_STRU的回复
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* 操作标识 */

    VOS_UINT16                                ausReserve1[2];
}PHY_RRC_SET_RAT_PRI_CNF_STRU;


/*****************************************************************************
 结构名    : PHY_RRC_WCDMA_TIMING_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层上报W的定时信息的数据结构

*****************************************************************************/

typedef struct
{
    VOS_UINT16                          usSfn;
    VOS_UINT16                          usSlot;
    VOS_UINT16                          usChip;
    VOS_UINT16                          usReserve;
} PHY_RRC_WCDMA_TIMING_INFO_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_GSM_TIMING_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层上报G的定时信息的数据结构

*****************************************************************************/

typedef struct
{
    VOS_UINT32                          ulFn;
    VOS_UINT16                          usQb;
    VOS_UINT16                          usKvalue;
} PHY_RRC_GSM_TIMING_INFO_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_LTE_TIMING_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层上报L的定时信息的数据结构

*****************************************************************************/

typedef struct
{
    VOS_UINT16                          usSfn;                                  /* 0~1023 SFN计数 */
    VOS_UINT16                          usSlot;                                 /* 0~9 子帧计数 */
    VOS_UINT16                          usChip;                                 /* 0~30719 子帧内计数 */
    VOS_UINT16                          usReserve;
} PHY_RRC_LTE_TIMING_INFO_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_RAT_TIMING_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层上报不同接入技术的定时信息的数据结构

*****************************************************************************/

typedef struct
{
    VOS_UINT32                          ulCtuTime;
    PHY_RRC_WCDMA_TIMING_INFO_STRU      stWTime;
    PHY_RRC_GSM_TIMING_INFO_STRU        stGTime;
    PHY_RRC_LTE_TIMING_INFO_STRU        stLTime;
} PHY_RRC_RAT_TIMING_INFO_STRU;


#define RRC_PHY_MAX_WCDMA_CELL_TIMING_NUM   (6)                                 /* W小区定时信息的最大规格 */


/*****************************************************************************
 结构名    : PHY_RRC_WCDMA_CELL_FRAME_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 小区帧头信息的数据结构

*****************************************************************************/

typedef struct
{
    VOS_UINT16                          usSlotNum;                              /* 小区帧头的时隙信息 */
    VOS_UINT16                          usChipNum;                              /* 小区帧头的码片信息 */
} PHY_RRC_WCDMA_CELL_FRAME_INFO_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_WCDMA_CELL_TIMING_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 小区帧头信息的数据结构

*****************************************************************************/

typedef struct
{
    VOS_UINT16                          usPrimaryScramCode;                     /* 小区的主扰码       */
    VOS_UINT16                          usReserve1;
    PHY_RRC_WCDMA_CELL_FRAME_INFO_STRU  stFrameInfo;                            /* 帧头信息 */
} PHY_RRC_WCDMA_CELL_TIMING_INFO_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_WCDMA_CELL_TIMING_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层上报不同接入技术的定时信息的数据结构

*****************************************************************************/

typedef struct
{
    VOS_UINT16                          usFreqInfo;
    VOS_UINT16                          usCellNum;
    PHY_RRC_WCDMA_CELL_TIMING_INFO_STRU astWCellInfo[RRC_PHY_MAX_WCDMA_CELL_TIMING_NUM];
} PHY_RRC_WCDMA_FREQ_CELL_TIMING_INFO_STRU;


/*****************************************************************************
 结构名    : PHY_RRC_WCDMA_CELL_TIMING_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层上报不同接入技术的定时信息的数据结构

*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usFreqNum;
    VOS_UINT16                                  usReserve1;
    PHY_RRC_WCDMA_FREQ_CELL_TIMING_INFO_STRU    astWCellInfo[RRC_PHY_MAX_SLAVE_WCDMA_CARRIER_NUM];
} PHY_RRC_WCDMA_FREQ_TIMING_STRU;


/*****************************************************************************
 结构名    : PHY_RRC_WCDMA_CELL_TIMING_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层上报小区定时信息的数据结构

*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                                 /* 操作标识 */
    PHY_RRC_RAT_TIMING_INFO_STRU        stRatTiming;                            /* 不同接入技术的定时关系 */
    PHY_RRC_WCDMA_FREQ_TIMING_STRU      stWCellTiming;                          /* W小区的定时关系 */
}PHY_RRC_WCDMA_CELL_TIMING_IND_STRU;


/*****************************************************************************
 结构名    : PHY_RRC_WCDMA_TIMING_ERROR_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层上报小区定时错误信息的数据结构

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                                 /* 操作标识 */
    VOS_UINT32                          ulReserved;
}PHY_RRC_WCDMA_TIMING_ERROR_IND_STRU;


/*****************************************************************************
 结构名    : RRC_PHY_CAMPED_MAINCELL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 主小区驻留请求消息的数据结构
             PHY接收到这个原语之后必须用原语PHY_RRC_CAMPED_MAINCELL_CNF
             向RRC确认，并且配置PCPICH，改变系统的帧定时。
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                  /*_H2ASN_Skip*/  /* 原语类型*/
    VOS_UINT16                          usOPID;                   /* 操作标识 */
    VOS_INT16                           sFreqInfo;                /* [0,16383]CELL 的频率 */
    VOS_INT16                           sPriScramCode;            /* [0, 511]主扰码 */
    VOS_UINT16                          usFreqBandNo;             /* 频段号:1,2,3,4,5,6*/
    VOS_UINT16                          usTxRxFreqSeparation;     /* 收发频差*/
    PHYITF_CAMPED_TYPE_ENUM_UINT16      enCampedType;             /* 指示是L2W\G2W切换流程 */
    PHYITF_TX_DIVER_IND_ENUM_UINT16     enPcpichTDIndicator;      /* L2W/G2W切换时Pcpich分集方式 */
    PHY_RRC_RAT_TIMING_INFO_STRU        stRatTiming;              /* 不同接入技术的定时关系 */
    PHY_RRC_WCDMA_CELL_FRAME_INFO_STRU  stCellFrameInfo;          /* 驻留小区的定时信息 */
}RRC_PHY_CAMPED_MAINCELL_REQ_STRU;

/*****************************************************************************
 结构名    : RRC_PHY_PS_CS_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DSP低功耗需求，当建立CS存在的时候通知DSP该消息指示enCsExistFlg为TRUE,
 CS不存在的时候通知物理层enCsExistFlg为FALSE;是否同时存在cs和ps，由物理层通过两个标记位组合判断
 WRR初始建立PS时可不需要通知DSP，DSP初始状态就是非cs only;
 非D下信道存在时，物理层收到该消息不处理；
 离开D态时，物理层自己处理，WAS不需要通知业务类型。
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16              enMsgID;                            /* 原语类型 */ /*_H2ASN_Skip*/
    PHYITF_BOOL_ENUM_UINT16                 enCsExistFlg;                       /* PS_TRUE,表示是CS存在;PS_FALSE表示不是CS不存在 */
    PHYITF_BOOL_ENUM_UINT16                 enPsExistFlg;                       /* PS_TRUE,表示是PS存在;PS_FALSE表示不是PS不存在 */
    VOS_UINT16                              usReserve;
}RRC_PHY_CS_PS_IND_STRU;

/*****************************************************************************
 结构名    : RRC_PHY_INTRA_DETECT_CELL_SEARCH_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 满足一定门限后WAS通知DSP启动或停止三步法搜索
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16              enMsgID;                            /* 原语类型 */ /*_H2ASN_Skip*/
    PHYITF_BOOL_ENUM_UINT16                 enDetectCellSearchFlg;              /* PS_TRUE,表示启动测量非邻区小区;PS_FALSE表示停止非邻区小区测量 */
}RRC_PHY_INTRA_DETECT_CELL_SEARCH_IND_STRU;

/*****************************************************************************
 结构名    : PHYITF_SLAVE_MEAS_CELL_INFO_ITEM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : W为从模时，LTE测量WCDMA小区信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;                             /* 频点的频率信息 */

    VOS_UINT16                          usFreqBandNo;                           /* 频段号:1,2,3,4,5,6*/
    VOS_UINT16                          usTxRxFreqSeparation;                   /* 收发频差*/
    VOS_UINT16                          usDetectedCellMeasureInd;               /* 是否需要测量属于Detected集的小区 */
    VOS_UINT16                          usReserve1;

    VOS_UINT16                          usCellNum;                              /* 一个频点下的小区数目 */
    VOS_UINT16                          ausPrimaryScramCode[RRC_PHY_MAX_SLAVE_WCDMA_CELL_PER_FREQ_NUM];    /* 小区的信息               */
}PHYITF_SLAVE_MEAS_CELL_INFO_ITEM_STRU;

/*****************************************************************************
 结构名    : PHYITF_SLAVE_WCDMA_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : W为从模时，LTE测量WCDMA小区信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usFreqNum;                      /* 需要测量的 W频点数量 */
    VOS_UINT16                                  usReserve1;
    PHYITF_SLAVE_MEAS_CELL_INFO_ITEM_STRU       astSlaveMeasCellInfo[RRC_PHY_MAX_SLAVE_WCDMA_CARRIER_NUM];
}PHYITF_SLAVE_WCDMA_CELL_INFO_STRU;

/*****************************************************************************
 结构名    : RRC_PHY_SLAVE_MEASURE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : W从模测量请求消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip */
    RRC_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    PHYITF_BOOL_ENUM_UINT16                     enIdleStateFlag;                /* 主模是否是在IDLE态的标记 */
    PHYITF_MEASURE_COMMAND_ENUM_UINT16          enCommand;                      /* 测量命令,0:释放，1:建立，从模测量没有MODIFY */
    PHYITF_SLAVE_WCDMA_CELL_INFO_STRU           stSlaveWcdmaCellEntity;         /* W为从模时，LTE下测量W小区的内容 */
}RRC_PHY_SLAVE_MEASURE_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_SLAVE_MEASURE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 从模测量配置响应消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* 操作标识 */
}PHY_RRC_SLAVE_MEASURE_CNF_STRU;

/*****************************************************************************
 结构名    : PHYITF_SLAVE_CELL_MEASURE_RESULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 从模每个小区的测量结果信息
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPrimaryScramCode;                     /* 小区的主扰码                             */
    VOS_INT16                           sCpichRscp;                             /* CPICH RSCP测量值                         */
    VOS_INT16                           sCpichEcN0;                             /* CPICH EcN0测量值                         */
    VOS_UINT16                          usSfn;
} PHYITF_SLAVE_CELL_MEASURE_RESULT_STRU;

/*****************************************************************************
 结构名    : PHYITF_INTER_FREQ_REPORT_ITEM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 从模测量结果
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                                usFreqInfo;                       /* 频率信息 */
    VOS_INT16                                 sCarrierRSSI;                     /* UtraCarrierRSSI测量值 */
    VOS_UINT16                                usCellNum;                        /* 此频点下的小区的数目  */
    VOS_UINT16                                usReserve1;
    PHYITF_SLAVE_CELL_MEASURE_RESULT_STRU     astInterFreqCell[PHY_RRC_MAX_REPORT_EACH_FREQ_CELL_NUM];     /* 频间小区的测量结果 */
}PHYITF_SLAVE_MEAS_REPORT_ITEM_STRU;

/*****************************************************************************
 结构名    : PHYITF_SLAVE_WCDMA_MEAS_REPORT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : W作为从模时WCDMA测量报告
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqNum;                              /* 报告中包含的频点数目 */
    VOS_UINT16                          usReserve1;
    PHYITF_SLAVE_MEAS_REPORT_ITEM_STRU  astInterFreqReport[RRC_PHY_MAX_SLAVE_WCDMA_CARRIER_NUM];
}PHYITF_SLAVE_WCDMA_MEAS_REPORT_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_SLAVE_MEASURE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 从模测量上报消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /*_H2ASN_Skip*/   /* 原语类型 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    PHYITF_SLAVE_WCDMA_MEAS_REPORT_STRU         stSlaveWcdmaMeasRpt;
}PHY_RRC_SLAVE_MEASURE_IND_STRU;

/*****************************************************************************
 结构名    : RRC_PHY_BSIC_VERIFIED_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知WPHY开始GSM的BSIC验证
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;            /*_H2ASN_Skip*/  /* 原语类型*/
    VOS_UINT16                          usOPID;
} RRC_PHY_BSIC_VERIFIED_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_BSIC_VERIFIED_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : WPHY对开始GSM的BSIC验证的响应
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;            /* 原语类型 */    /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;
} PHY_RRC_BSIC_VERIFIED_CNF_STRU;

/*****************************************************************************
 结构名    : RRC_PHY_W_BG_SEARCH_OTHER_RAT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : W为主模时，背景搜L或者G通知WPHY给LPHY或者GPHY进行时间分配消息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                                enMsgID;          /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                                usOPID;           /* 操作标识 */
    PHYITF_W_BG_SEARCH_OTHER_RAT_CMD_ENUM_UINT16              enCtrlCmd;        /* 主模控制命令 */
    PHYITF_W_BG_SEARCH_RAT_ENUM_UINT16                        enSrchRat;        /* 背景搜的从模接入模式指示 */
}RRC_PHY_W_BG_SEARCH_OTHER_RAT_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_W_BG_SEARCH_OTHER_RAT_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : W为主模时，背景搜L或者G通知WPHY给LPHY或者GPHY进行时间分配响应消息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                                enMsgID;          /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                                usOPID;           /* 操作标识 */
    PHYITF_W_BG_SEARCH_OTHER_RAT_CMD_ENUM_UINT16              enCtrlCmd;        /* 主模控制命令 */
    VOS_UINT16                                                usReserve;
}PHY_RRC_W_BG_SEARCH_OTHER_RAT_CNF_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_RADIO_RESOURCE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 指示资源是否可用标志
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16 enMsgID;                                         /* 原语类型 */ /*_H2ASN_Skip*/
    PHYITF_BOOL_ENUM_UINT16 enAvailableFlg;                                     /* 资源可用标志 */
}PHY_RRC_RADIO_RESOURCE_IND_STRU;

/*****************************************************************************
 结 构 名  : RRC_PHY_AS_ACTIVE_DSDS_STATUS_IND_STRU
 结构说明  : ID_RRC_PHY_AS_ACTIVE_DSDS_STATUS_IND消息结构
 修改历史  :
  1.日  期   : 2014年9月24日
    作  者   : s00184266
    修改内容 : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16              enMsgID;                            /* 原语类型 */ /*_H2ASN_Skip*/
    PHYITF_BOOL_ENUM_UINT16                 enRfShareFlag;                      /* _VALID:共享RF(DSDS双卡模式)，_INVALID:独占RF(非DSDS双卡模式) */
}RRC_PHY_AS_ACTIVE_DSDS_STATUS_IND_STRU;


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_VOID   WAS_RRC_GetCurSfnFromPhy(VOS_UINT16 usCurSfn);

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

#endif /* end of RrcPhyInterface.h */

