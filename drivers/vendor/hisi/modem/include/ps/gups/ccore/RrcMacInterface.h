/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : RrcMacInterface.h
  版 本 号   : 初稿
  作    者   : Jinying
  生成日期   : 2006年9月5日
  最近修改   :
  功能描述   : RrcMacInterface.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2006年9月5日
    作    者   : Jinying
    修改内容   : 创建文件

  2.日    期   : 2007年12月21日
    作    者   : 查鸣峰、陈功
    修改内容   : 修改HSUPA接口

  3.日    期   : 2009年7月6日
   作    者   : 邓清珊、高财、杜霄鹏
   修改内容   : 修改HSPA+ MAC-ehs接口

******************************************************************************/

#ifndef __RRCMACINTERFACE_H__
#define __RRCMACINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
/* WCDMA协议栈各个子系统公共的数据结构 */
#include  "product_config.h"
#include "PsTypeDef.h"
#include "WUe.h"
#include "WUeL2L3.h"
#include "WUeSpec.h"

#pragma pack(4)

/*****************************************************************************
  1 消息头定义
*****************************************************************************/
enum RRC_MAC_MSG_TYPE_ENUM
{
    ID_MAC_RRC_ACTIVE_IND               = 0x0000,           /* _H2ASN_MsgChoice MAC_RRC_ACTIVE_IND_STRU */

    ID_MAC_RRC_STATUS_IND               = 0x0001,           /* _H2ASN_MsgChoice MAC_RRC_STATUS_IND_STRU */
                                                            /* RB0上行数据发送成功指示 */

    ID_RRC_MAC_C_CONFIG_REQ             = 0x0002,           /* _H2ASN_MsgChoice RRC_MAC_C_CONFIG_REQ_STRU */
    ID_MAC_RRC_C_CONFIG_CNF             = 0x0003,           /* _H2ASN_MsgChoice MAC_RRC_C_CONFIG_CNF_STRU */

    ID_RRC_MAC_D_CONFIG_REQ             = 0x0004,           /* _H2ASN_MsgChoice RRC_MAC_D_CONFIG_REQ_STRU */
    ID_MAC_RRC_D_CONFIG_CNF             = 0x0005,           /* _H2ASN_MsgChoice MAC_RRC_D_CONFIG_CNF_STRU */

    ID_RRC_MAC_E_VIRTUAL_CONFIG_REQ     = 0x0006,           /* _H2ASN_MsgChoice RRC_MAC_E_VIRTUAL_CONFIG_REQ_STRU */
    ID_MAC_RRC_E_VIRTUAL_CONFIG_CNF     = 0x0007,           /* _H2ASN_MsgChoice MAC_RRC_E_VIRTUAL_CONFIG_CNF_STRU */

    ID_RRC_MAC_HS_CONFIG_REQ            = 0x0008,           /* _H2ASN_MsgChoice RRC_MAC_HS_CONFIG_REQ_STRU */
    ID_MAC_RRC_HS_CONFIG_CNF            = 0x0009,           /* _H2ASN_MsgChoice MAC_RRC_HS_CONFIG_CNF_STRU */

    ID_RRC_MAC_HS_RESET_REQ             = 0x000C,           /* _H2ASN_MsgChoice RRC_MAC_HS_RESET_REQ_STRU */
    ID_MAC_RRC_HS_RESET_CNF             = 0x000D,           /* _H2ASN_MsgChoice MAC_RRC_HS_RESET_CNF_STRU */

    ID_RRC_MAC_RELEASE_REQ              = 0x000E,           /* _H2ASN_MsgChoice RRC_MAC_RELEASE_REQ_STRU */
    ID_MAC_RRC_RELEASE_CNF              = 0x000F,           /* _H2ASN_MsgChoice MAC_RRC_RELEASE_CNF_STRU */

    ID_RRC_MAC_TFC_CONTROL_REQ          = 0x0010,           /* _H2ASN_MsgChoice RRC_MAC_TFC_CONTROL_REQ_STRU */
                                                            /* RRC收到 TRANSPORT FORMAT COMBINATION CONTROL后，配置MAC */
    ID_MAC_RRC_TFC_CONTROL_IND          = 0x0011,           /* _H2ASN_MsgChoice MAC_RRC_TFC_CONTROL_IND_STRU */
                                                            /* 若AMR业务，需要改变语音编解码模块的AMR参数 */

    ID_RRC_MAC_CIPHER_CONFIG_REQ        = 0x0012,           /* _H2ASN_MsgChoice RRC_MAC_CIPHER_CONFIG_REQ_STRU */
                                                            /* RRC配置MAC加密信息 */
    ID_MAC_RRC_CIPHER_CONFIG_CNF        = 0x0013,           /* _H2ASN_MsgChoice MAC_RRC_CIPHER_CONFIG_CNF_STRU */

    ID_MAC_RRC_CIPHER_ACTIVE_IND        = 0x0014,           /* _H2ASN_MsgChoice MAC_RRC_CIPHER_ACTIVE_IND_STRU */
                                                            /* RRC收到该消息后，开始计算START值 */

    ID_RRC_MAC_MEAS_CONFIG_REQ          = 0x0015,           /* _H2ASN_MsgChoice RRC_MAC_MEAS_CONFIG_REQ_STRU */
                                                            /* RRC收到启动业务量测量控制后，配置MAC */
    ID_MAC_RRC_MEAS_CONFIG_CNF          = 0x0016,           /* _H2ASN_MsgChoice MAC_RRC_MEAS_CONFIG_CNF_STRU */

    ID_MAC_RRC_MEAS_IND                 = 0x0017,           /* _H2ASN_MsgChoice MAC_RRC_MEAS_IND_STRU */

    ID_RRC_MAC_MEAS_REL_REQ             = 0x0018,           /* _H2ASN_MsgChoice RRC_MAC_MEAS_REL_REQ_STRU */
                                                            /* RRC收到停止业务量测量控制后，配置MAC */
    ID_MAC_RRC_MEAS_REL_CNF             = 0x0019,           /* _H2ASN_MsgChoice MAC_RRC_MEAS_REL_CNF_STRU */

    ID_MAC_RRC_PCCH_DATA_IND            = 0x001A,           /* _H2ASN_MsgChoice MAC_RRC_PCCH_DATA_IND_STRU */
                                                            /* PCH传输信道上收到的消息，上报给RRC */

    ID_MAC_RRC_BCCH_DATA_IND            = 0x001B,           /* _H2ASN_MsgChoice MAC_RRC_BCCH_DATA_IND_STRU */
                                                            /* FACH传输信道，MAC收到SYSTEM INFORMATION CHANGE INDICATION*/

    ID_MAC_RRC_ERROR_IND                = 0x001C,           /* _H2ASN_MsgChoice MAC_RRC_ERROR_IND_STRU */


    ID_RRC_MAC_COMPRESS_MODE_CFG_REQ    = 0x001D,           /* _H2ASN_MsgChoice RRC_MAC_COMPRESS_MODE_CFG_REQ_STRU */
    ID_RRC_MAC_COMPRESS_MODE_CFG_CNF    = 0x001E,           /* _H2ASN_MsgChoice RRC_MAC_COMPRESS_MODE_CFG_CNF_STRU */

    ID_RRC_MAC_TFC_SLOT_CFG_REQ         = 0x0020,           /* _H2ASN_MsgChoice RRC_MAC_TFC_SLOT_CFG_REQ_STRU */
    ID_RRC_MAC_TFC_SLOT_CFG_CNF         = 0x0021,           /* _H2ASN_MsgChoice RRC_MAC_TFC_SLOT_CFG_CNF_STRU */

    ID_RRC_MAC_STOP_UL_TX_REQ           = 0x0022,           /* _H2ASN_MsgChoice RRC_MAC_STOP_UL_TX_REQ_STRU */
    ID_MAC_RRC_STOP_UL_TX_CNF           = 0x0023,           /* _H2ASN_MsgChoice MAC_RRC_STOP_UL_TX_CNF_STRU */

    ID_RRC_MAC_CONTINUE_UL_TX_REQ       = 0x0024,           /* _H2ASN_MsgChoice RRC_MAC_CONTINUE_UL_TX_REQ_STRU */
    ID_MAC_RRC_CONTINUE_UL_TX_CNF       = 0x0025,           /* _H2ASN_MsgChoice MAC_RRC_CONTINUE_UL_TX_CNF_STRU */

    ID_RRC_MAC_TGPS_PRE_CHK_REQ         = 0x0026,           /* _H2ASN_MsgChoice RRC_MAC_TGPS_PRE_CHK_REQ_STRU */
    ID_MAC_RRC_TGPS_PRE_CHK_CNF         = 0x0027,           /* _H2ASN_MsgChoice MAC_RRC_TGPS_PRE_CHK_CNF_STRU */

    /*V3 R7_7C1 Start */

    /*Add for MAC-ehs*/
    ID_RRC_MAC_EHS_CONFIG_REQ           = 0x0028,           /* _H2ASN_MsgChoice RRC_MAC_EHS_CONFIG_REQ_STRU */
    ID_MAC_RRC_EHS_CONFIG_CNF           = 0x0029,           /* _H2ASN_MsgChoice MAC_RRC_EHS_CONFIG_CNF_STRU */

    ID_RRC_MAC_EHS_RESET_REQ            = 0x002A,           /* _H2ASN_MsgChoice RRC_MAC_EHS_RESET_REQ_STRU */
    ID_MAC_RRC_EHS_RESET_CNF            = 0x002B,           /* _H2ASN_MsgChoice MAC_RRC_EHS_RESET_CNF_STRU */


    ID_RRC_MAC_BCBD_CALCULATE_REQ       = 0x002C,           /* _H2ASN_MsgChoice RRC_MAC_BCBD_CALCULATE_REQ_STRU */
    ID_MAC_RRC_BCBD_CALCULATE_CNF       = 0x002D,           /* _H2ASN_MsgChoice MAC_RRC_BCBD_CALCULATE_CNF_STRU  */


    ID_RRC_MAC_BHS_CALCULATE_REQ        = 0x002E,           /* _H2ASN_MsgChoice RRC_MAC_BHS_CALCULATE_REQ_STRU */
    ID_MAC_RRC_BHS_CALCULATE_CNF        = 0x002F,           /* _H2ASN_MsgChoice MAC_RRC_BHS_CALCULATE_CNF_STRU */

    ID_RRC_MAC_CIPHER_RESERVE_REQ       = 0x0030,           /* _H2ASN_MsgChoice  RRC_MAC_CIPHER_RESERVE_REQ_STRU */
    ID_MAC_RRC_CIPHER_RESERVE_CNF       = 0x0031,           /* _H2ASN_MsgChoice  MAC_RRC_CIPHER_RESERVE_CNF_STRU */

    ID_RRC_MAC_C_CONFIG_REQ_MNTN_COMM_PARAM = 0x0032,       /* _H2ASN_MsgChoice RRC_MAC_C_CONFIG_REQ_MNTN_COMM_PARAM_STRU */
    ID_RRC_MAC_C_CONFIG_REQ_MNTN_DLCCH1     = 0x0033,       /* _H2ASN_MsgChoice RRC_MAC_C_CONFIG_REQ_MNTN_DLCCH1_STRU */
    ID_RRC_MAC_C_CONFIG_REQ_MNTN_DLCCH2     = 0x0034,       /* _H2ASN_MsgChoice RRC_MAC_C_CONFIG_REQ_MNTN_DLCCH2_STRU */

    ID_MAC_RRC_EHS_RX_DATA_IND              = 0x0035,       /* _H2ASN_MsgChoice MAC_RRC_EHS_RX_DATA_IND_STRU */

    ID_RRC_MAC_I_VIRTUAL_CONFIG_REQ         = 0x0036,           /* _H2ASN_MsgChoice RRC_MAC_I_VIRTUAL_CONFIG_REQ_STRU */
    ID_MAC_RRC_I_VIRTUAL_CONFIG_CNF         = 0x0037,           /* _H2ASN_MsgChoice MAC_RRC_I_VIRTUAL_CONFIG_CNF_STRU */

    /* 周期接收SIB7新增接口 */
    ID_RRC_MAC_ASC_CONFIG_IND               = 0x0038,           /* _H2ASN_MsgChoice RRC_MAC_ASC_CONFIG_STRU */

    ID_RRC_MAC_AS_ACTIVE_DSDS_STATUS_IND    = 0x0039,           /* _H2ASN_MsgChoice RRC_MAC_AS_ACTIVE_DSDS_STATUS_IND_STRU */

    /* MAC_D_CONFIG_REQ和MAC_C_CONFIG_REQ精简结构，用于L2 ST测试使用，不用于实际接口中 */
    ID_RRC_MAC_C_CONFIG_REDUCE_REQ          = 0x8002,           /* _H2ASN_MsgChoice RRC_MAC_C_CONFIG_REDUCE_REQ_STRU */
    ID_RRC_MAC_D_CONFIG_REDUCE_REQ          = 0x8004,           /* _H2ASN_MsgChoice RRC_MAC_D_CONFIG_REDUCE_REQ_STRU */

    ID_WTTF_MEM_TEST_REQ                    = 0x8005,           /* _H2ASN_MsgChoice WTTF_MEM_TEST_REQ_STRU */
    ID_WTTF_MEM_TEST_CNF                    = 0x8006,           /* _H2ASN_MsgChoice WTTF_MEM_TEST_CNF_STRU */
    /* V3 R7_7C1 End */

    ID_RRC_MAC_QUIT_REQ                     = 0x8007,

    ID_RRC_MAC_MSG_TYPE_BUTT                = 0xFFFF
};
typedef VOS_UINT16 RRC_MAC_MSG_TYPE_ENUM_UINT16;

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 计算ASC的PI时统一扩大10000倍，保证精度，MAC计算随即数时也使用这个宏 */
#define    MACITF_ASC_PI_MULTIPLE       (10000)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*V3 R7_7C1 Start */
/* 回复RRC错误指示时的错误类型 */
enum MACITF_RRC_ERR_CODE_ENUM
{
    MACITF_RRC_ERR_CODE_EHS_ACT_FAIL        = 0,   /* 当MAC在激活时间到时激活配置出现了错误，通过该消息通知RRC */
    MACITF_RRC_ERR_CODE_BCBD_ACT_FAIL       = 1,   /* RRC配置的BCBD值出现错误，通过该消息通知RRC */
    MACITF_RRC_ERR_CODE_AMRRATES_CALC_FAIL  = 2,   /* RRC配置的AMR速率出现错误，通过该消息通知RRC */
    MACITF_RRC_ERR_CODE_MAC_STATE_ERR       = 3,   /* MAC状态异常，通过该消息通知RRC */

    MACITF_RRC_ERR_CODE_BUTT
};
typedef VOS_UINT32 MACITF_RRC_ERR_CODE_ENUM_UINT32;
/* V3 R7_7C1 End */


/* 事件评估的参数的结构体 */
/* 测量触发事件ID */
enum MACITF_TRAF_VOL_EVT_TYPE_ENUM
{
    MACITF_TRAF_VOL_EVT_4A              = 0,
    MACITF_TRAF_VOL_EVT_4B              = 1,
    MACITF_TRAF_VOL_EVT_BUTT
};
typedef VOS_UINT8 MACITF_TRAF_VOL_EVT_TYPE_ENUM_UINT8;

/* 消息MAC_RRC_TFC_CONTROL_IND的结构体 */
enum MACITF_TFC_CTRL_ENUM
{
    MACITF_TFC_CTRL_BEGIN               = 0,
    MACITF_TFC_CTRL_END                 = 1,
    MACITF_TFC_CTRL_BUTT
};
typedef VOS_UINT8 MACITF_TFC_CTRL_ENUM_UINT8;

/* 消息RRC_MAC_RELEASE_REQ的结构体 */
enum MACITF_REL_MODE_ENUM
{
    MACITF_REL_MAC_C                    = 0,
    MACITF_REL_MAC_D                    = 1,                /* 如果释放MAC-D，则MAC-E/MAC-HS都释放 */
    MACITF_REL_VIRTUAL_MAC_E            = 2,                /* MAC-E,MAC-ES一起释放 */
    MACITF_REL_MAC_HS                   = 3,                /* 释放MAC-HS实体 */
    MACITF_REL_MAC_ALL                  = 4,                /* 释放所有的MAC实体 */

    /*V3 R7_7C1 Start */
    MACITF_REL_MAC_EHS                  = 5,                /*add for MAC-ehs*/
    MACITF_REL_VIRTUAL_MAC_I            = 6,                /* MAC-I,MAC-IS一起释放 */

    MACITF_REL_MODE_BUTT
};
typedef VOS_UINT8 MACITF_REL_MODE_ENUM_UINT8;

/* 传输信道类型 */
enum MACITF_TRCH_TYPE_ENUM
{
    MACITF_FACH_TYPE                    = 0,
    MACITF_PCH_TYPE                     = 1,

    MACITF_TRCH_TYPE_BUTT
};
typedef VOS_UINT8 MACITF_TRCH_TYPE_ENUM_UINT8;

/* TTI定义，以10ms为单位。 */
enum MACITF_TTI_ENUM
{
    MACITF_TTI_NULL                     = 0,                /*为方便IT测试时做消息，增加该项，无其他意义 */
    MACITF_TTI_10MS                     = 1,
    MACITF_TTI_20MS                     = 2,
    MACITF_TTI_40MS                     = 4,
    MACITF_TTI_80MS                     = 8,
    MACITF_TTI_BUTT
};
typedef VOS_UINT8   MACITF_TTI_ENUM_UINT8;

enum MACITF_CRC_SIZE_ENUM
{
    MACITF_CRC_SIZE_0BIT                = 0,
    MACITF_CRC_SIZE_8BIT                = 8,
    MACITF_CRC_SIZE_12BIT               = 12,
    MACITF_CRC_SIZE_16BIT               = 16,
    MACITF_CRC_SIZE_24BIT               = 24,
    MACITF_CRC_SIZE_BUTT
};
typedef VOS_UINT8   MACITF_CRC_SIZE_ENUM_UINT8;

enum MACITF_RSLT_ENUM
{
    MACITF_SUCC                         = 0,
    MACITF_FAIL                         ,
    MACITF_RSLT_BUTT
};
typedef VOS_UINT32   MACITF_RSLT_ENUM_UINT32;

/* RRC配置的压模序列的状态定义 */
enum MACITF_TGPS_CFG_STATUS_ENUM
{
    MACITF_TGPS_CFG_CHANGED_ACTIVED         = 0 ,
    MACITF_TGPS_CFG_CHANGED_INACTIVED       = 1 ,
    MACITF_TGPS_CFG_UNCHANGED_ACTIVED       = 2 ,
    MACITF_TGPS_CFG_UNCHANGED_INACTIVED     = 3 ,
    MACITF_TGPS_CFG_BUTT
};
typedef VOS_UINT16 MACITF_TGPS_CFG_STATUS_ENUM_UINT16;

/* 同频硬切换或者异系统切换加密回退的加密状态定义 */
enum MACITF_CIPHER_STATUS_ENUM
{
    MACITF_CIPHER_STA_BACKUP                       = 0,      /*通知MAC备份cipher相关参数*/
    MACITF_CIPHER_STA_REVERT                       = 1,  /* 通知MAC重新计算加密配置 */
    MACITF_CIPHER_STA_BUTT
};
typedef VOS_UINT16 MACITF_CIPHER_STATUS_ENUM_UINT16;

/*****************************************************************************
 枚举名    : MACITF_RNTI_CFG_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  : 指示当前UE配置了H-RNTI情况，DL_E_CELLFACH新增
*****************************************************************************/
enum MACITF_RNTI_CFG_ENUM
{
    MACITF_RNTI_CFG_COMM_HRNTI      = 0,    /* UE当前配置了COMMON H-RNTI */
    MACITF_RNTI_CFG_DEDICATE_HRNTI  = 1,    /* UE当前前配置了DEDICATE H-RNTI */
    MACITF_RNTI_CFG_NO_HRNTI        = 2,    /* UE当前未配置 H-RNTI,DL_E_CELLFACH盲检测场景 */
    MACITF_RNTI_CFG_BUTT
};
typedef VOS_UINT8 MACITF_RNTI_CFG_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MACITF_FLEX_RLC_PDU_SIZE_LI_SIZE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 在配置AM RB为弹性size时, 描述LI是使用7-bit, 还是15-bit
*****************************************************************************/
enum   MACITF_FLEX_RLC_PDU_SIZE_LI_SIZE_ENUM
{
    MACITF_FLEX_RLC_PDU_SIZE_LI_SIZE_7_BIT  = 7,
    MACITF_FLEX_RLC_PDU_SIZE_LI_SIZE_15_BIT = 15,
    MACITF_FLEX_RLC_PDU_SIZE_LI_SIZE_BUTT
};
typedef VOS_UINT16   MACITF_FLEX_RLC_PDU_SIZE_LI_SIZE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : MACITF_EDCH_FLOW_TYPE_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  : 用于描述一个逻辑信道是承载在调度流上, 还是非调度流上
*****************************************************************************/
enum   MACITF_EDCH_FLOW_TYPE_ENUM
{
    MACITF_EDCH_FLOW_SCHED_TYPE     = 0,
    MACITF_EDCH_FLOW_NON_SCHED_TYPE = 1,
    MACITF_EDCH_FLOW_TYPE_BUTT
};
typedef VOS_UINT8   MACITF_EDCH_FLOW_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MACITF_RLC_PDU_SIZE_TYPE_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  : 用于描述一个逻辑信道是使用弹性size, 还是变长size
*****************************************************************************/
enum   MACITF_RLC_PDU_SIZE_TYPE_ENUM
{
    MACITF_RLC_PDU_SIZE_FIXED_SIZE_TYPE     = 0,
    MACITF_RLC_PDU_SIZE_FLEX_SIZE_TYPE      = 1,
    MACITF_RLC_PDU_SIZE_TYPE_BUTT
};
typedef VOS_UINT8   MACITF_RLC_PDU_SIZE_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MACITF_LOCH_DATA_TYPE_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  : 用于描述一个逻辑信道上承载的业务类别
*****************************************************************************/
enum MACITF_LOCH_DATA_TYPE_ENUM
{
    MACITF_LOCH_DATA_TYPE_CCCH          = 0,
    MACITF_LOCH_DATA_TYPE_SRB              ,
    MACITF_LOCH_DATA_TYPE_CS               ,
    MACITF_LOCH_DATA_TYPE_PS               ,
    MACITF_LOCH_DATA_TYPE_BUTT
};
typedef VOS_UINT8   MACITF_LOCH_DATA_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MACITF_EDCH_TTI_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : HSUPA 的EDCH TTI
*****************************************************************************/

enum    MACITF_EDCH_TTI_ENUM
{
    MACITF_EDCH_TTI_10MS                = 0,
    MACITF_EDCH_TTI_2MS                 = 1,

    MACITF_EDCH_TTI_BUTT

};
typedef VOS_UINT16 MACITF_EDCH_TTI_ENUM_UINT16;

enum MACITF_STATUS_ENUM
{
    MACITF_UP_TX_DATA_START             = 0,   /* 上行开始发数 */
    MACITF_UP_TX_DATA_END                  ,   /* 上行发数结束 */
    MACITF_UP_TX_DATA_FAIL                 ,   /* 上行发数失败 */
    MACITF_STATUS_BUTT
};
typedef VOS_UINT32   MACITF_STATUS_ENUM_UINT32;
enum MACITF_MAC_EHS_TSN_BIT_LEN_ENUM
{
    MACITF_MAC_EHS_TSN_BIT_LEN_6_ENUM             = 6,   /* MAC-ehs TSN=6bits */
    MACITF_MAC_EHS_TSN_BIT_LEN_14_ENUM            = 14,  /* MAC-ehs TSN=14bits */
    MACITF_MAC_EHS_TSN_BIT_LEN_BUTT
};
typedef VOS_UINT8    MACITF_MAC_EHS_TSN_BIT_LEN_ENUM_UINT8;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  6 消息定义
*****************************************************************************/

/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDchTrchId;        /* [1,32] */
    VOS_UINT8                           ucDschTrchId;
}MACITF_CH_ID_DCH_DSCH_STRU;

typedef struct
{
    VOS_UINT8                           ucDchTrchId;        /* [1,32] */
    VOS_UINT8                           ucHsdschMacDFlowId; /* [0,7] */
}MACITF_MACD_FLOW_ID_DCH_HSDSCH_STRU;

/*****************************************************************************
 结构名    : MACITF_UL_TRCH_ID_CHOICE_STRU
 协议表格  : 10.3.7.69 Traffic volume measurement event results
 ASN.1描述 : UL_TrCH_Identity
             UL_TransportChannelType
 结构说明  : 下行传输信道
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulChoice;

    #define    MACITF_UL_TRCH_DCH_CHOSEN            0
    #define    MACITF_UL_TRCH_RACH_CHOSEN           1
    #define    MACITF_UL_TRCH_E_DCH_CHOSEN          2       /* 仅用于流量测量 */

    union
    {
        VOS_UINT8                       ucUlDchId;          /* [PS_WUE_MIN_TRCH_ID,PS_WUE_MAX_TRCH_ID] */
        PS_NULL_STRU                    stRach;
        PS_NULL_STRU                    stEDch;
    }u;
}MACITF_UL_TRCH_ID_CHOICE_STRU;



/*****************************************************************************
 结构名    : MACITF_UL_PER_LOCH_MAPP_CHOICE_STRU
 协议表格  : 10.3.4.21  RB mapping info
 ASN.1描述 : UL_LogicalChannelMapping_r6
 结构说明  : RACH,DCH逻辑信道与传输信道的对应关系，以及逻辑信道可用的RLC SIZE
*****************************************************************************/
typedef struct
{
    MACITF_UL_TRCH_ID_CHOICE_STRU       stTrchId;
    VOS_UINT8                           ucLochLabel;        /* 逻辑信道内部实现统一标识：[0,[0,34*2-1]] */
    VOS_UINT8                           ucLochId;           /* 逻辑信道ID：[1,15]，0表示无效 */
    VOS_UINT8                           ucLochPrio;         /* 逻辑信道优先级：[1,8] */
    /* ASN.1 文本 : RLC_SizeExplicitList */
    VOS_UINT8                           ucRlcSizeCnt;       /* 可用的RLC Size 个数 */
    /* 对应astTfPerRlcSize[PS_WUE_MAX_TF_NUM]数组下标索引,协议值为[1,PS_WUE_MAX_TF_NUM],代码实现值为[0,PS_WUE_MAX_TF_NUM-1] */
    VOS_UINT8                           aucRlcSizeIdx[PS_WUE_MAX_TF_NUM];
}MACITF_RACH_DCH_LOCH_MAPP_STRU;

/*****************************************************************************
 结构名    : MACITF_RLC_PDU_FIXED_SIZE_STRU
 协议表格  :
 ASN.1描述 : ASN.1 文本 : RLC_PDU_SizeList
 结构说明  : RLC_PDU固定SIZE的参数
*****************************************************************************/
typedef struct
{
   VOS_UINT8                           aucReserve[3];
   VOS_UINT8                           ucRlcSizeCnt;                            /* [1,32] */
   VOS_UINT16                          ausRlcSize[PS_WUE_MAX_RLC_PDU_SIZE_NUM_PER_LOCH];/* [16,5000],by step of 8, unit: bit */
}MACITF_RLC_PDU_FIXED_SIZE_STRU;

/*****************************************************************************
 结构名    : MACITF_EDCH_RLC_PDU_SIZE_FIXED_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC_PDU固定SIZE时, EDCH配置的参数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucDdi;                          /* [0,62] */
    VOS_UINT8                                   aucReserve1[3];                 /* 4字节对齐，保留 */
    MACITF_RLC_PDU_FIXED_SIZE_STRU              stFixedSize;                    /* Fixed Size */
}MACITF_EDCH_RLC_PDU_SIZE_FIXED_STRU;

/*****************************************************************************
 结构名    : MACITF_RLC_PDU_FLEX_SIZE_STRU
 协议表格  :
 ASN.1描述 : ASN.1 文本 : RLC-PDU-SizeConstraint
 结构说明  : RLC_PDU可变SIZE的参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      ucReserve;
    MACITF_FLEX_RLC_PDU_SIZE_LI_SIZE_ENUM_UINT16    enLenIndSize;               /* ENUMERATED  OPTIONAL,网络没有携带的时候填写BUTT */
    VOS_UINT16                                      usMinRlcPduSize;            /* Integer (16..12040 by step of 8), unit: bit, 空口数据*8 */
    VOS_UINT16                                      usLargestRlcPduSize;        /* Integer (16..12040 by step of 8), unit: bit, 空口数据*8 */
}MACITF_RLC_PDU_FLEX_SIZE_STRU;

/*****************************************************************************
 结构名    : MACITF_EDCH_RLC_PDU_SIZE_FLEX_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC_PDU可变SIZE时, EDCH配置的参数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   aucExt[8];                      /* 保留8字节待今后扩展使用 */
    MACITF_RLC_PDU_FLEX_SIZE_STRU               stFlexSize;                     /*Flexible Size*/
}MACITF_EDCH_RLC_PDU_SIZE_FLEX_STRU;


/*****************************************************************************
 结构名    : MACITF_EDCH_LOCH_MAPP_STRU
 协议表格  : 10.3.4.21  RB mapping info
 ASN.1描述 : UL_LogicalChannelMapping_r6
 结构说明  : EDCH逻辑信道与传输信道的对应关系，以及逻辑信道可用的RLC SIZE
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucLochLabel;                    /* 逻辑信道内部实现统一标识：[0,[0,34*2-1]] */
    VOS_UINT8                                   ucLochId;                       /* INTEGER(1..15),0表示无效 */
    VOS_UINT8                                   ucEdchMacdFlowId;               /* [0,7] */
    PS_BOOL_ENUM_UINT8                          enIncSI;                        /* 该MAC-d流对应的逻辑信道是否允许触发SI，bIncludeInSchedulInfo*/
    VOS_UINT8                                   ucLochPrio;                     /* 逻辑信道优先级：[1,8] */

    VOS_UINT8                                   aucReserve1[3];                 /* 4字节对齐，保留 */

    #define    MACITF_EDCH_RLC_PDU_SIZE_FIXED_SIZE   0                          /* Fixed size*/
    #define    MACITF_EDCH_RLC_PDU_SIZE_FLEX_SIZE    1                          /* Flexible size*/

    VOS_UINT32                                  ulChoice;

    union
    {
        MACITF_EDCH_RLC_PDU_SIZE_FIXED_STRU     stEdchFixedSize;                /* Fixed size */
        MACITF_EDCH_RLC_PDU_SIZE_FLEX_STRU      stEdchFlexSize;                 /* Flexible Size */
    } u;
}MACITF_EDCH_LOCH_MAPP_STRU;

/******************************* 测量信息的数据结构 ***********************************/
/* 需要测量的传输信道列表 */
typedef struct
{
    VOS_UINT8                           aucReserve1[3];                         /* 4字节对齐，保留 */
    VOS_UINT8                           ucTrchCnt;                              /* 对DCH测量:
                                                                                如果网侧未配置Traffic volume measurement Object,则RRC配置ucTrchCnt = 0,MAC在RLC实体重配置后，将当前所有DCH更新为MAC MEASUREMENT OBJECT;
                                                                                如果网侧配置了Traffic volume measurement Object,则将本结构配置的DCH ID作为MAC MEASUREMENT OBJECT,MAC在RLC实体重配置后不进行任何更新
                                                                                对RACH/EDCH测量:ucTrchCnt;一定为1 */
    MACITF_UL_TRCH_ID_CHOICE_STRU       astTrchId[PS_WUE_MAX_MEAS_TRCH_NUM];    /* 需要测量的传输信道的标记*/
}MACITF_MEAS_OBJ_LIST_STRU;

/* 周期性报告的参数的结构体 */
/* 协议表格 : 10.3.7.53 Periodical reporting criteria  */
/* ASN.1 文本 : PeriodicalReportingCriteria */
typedef struct
{
    VOS_UINT16                          usRptInterval;      /*单位ms,(250, 500, 1000, 2000, 3000, 4000, 6000, 8000, 12000, 16000, 20000, 24000, 28000, 32000, 64000),周期报告的时间间隔 */
    /* ASN.1 文本 : ReportingIntervalLong */
    VOS_UINT8                           ucRepAmount;        /* 周期报告的最大次数,(1, 2, 4, 8, 16, 32, 64, Infinity = 0)   */
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */
}MACITF_PERIOD_RPT_CRTR_STRU;

/* 协议表格 : 10.3.7.72 Traffic volume measurement reporting criteria  */
/* ASN.1 文本 : TrafficVolumeEventParam */
typedef struct
{
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */
    MACITF_TRAF_VOL_EVT_TYPE_ENUM_UINT8 enEvtType;          /* 事件的标识 */
    /* 网络如果不携带Trigger Time，默认为立即触发，ulTriggerTime配置为0，
       网络如果不携带Pending After Trigger,默认为立即触发，ulPendTimeAftTrig配置为0,
       网络如果不携带Tx interruption after trigger,,默认为不停止发送DTCH/RACH数据，ulPendTimeAftTrig配置为0.
       参考25.331 14.4.2    Traffic Volume reporting triggers */
    VOS_UINT16                          usTriggerTime;      /* 单位ms,(0, 10, 20, 40, 60, 80, 100, 120, 160, 200, 240, 320, 640, 1280, 2560, 5000)trigger time */
    VOS_UINT16                          usPendTimeAftTrig;  /* 单位ms,(0, 250, 500, 1000, 2000, 4000, 8000, 16000)两次测量报告之间的最小时间间隔 */
    VOS_UINT16                          usTxIntrrptAftTrig; /* 单位ms,(0, 250, 500, 1000, 2000, 4000, 8000, 16000)Time in milliseconds.
                                                               Indicates how long the UE shall block DTCH transmissions on the RACH after a measurement report is triggered.
                                                               如果是增强CELL_FACH(UL)下, TxIntrrptAftTrig配置为0 */
    /* ASN.1 文本 : TrafficVolumeThreshold */
    VOS_UINT32                          ulRptThresh;        /* 单位byte,(8,16,32,64,128,256,512,1024,2K,3K,4K,6K,8K,12K,16K,24K,32K,48K,64K,96K,128K,192K,256K,384K,512K,768K)事件评估的阈值 */

}MACITF_MAC_EVT_PARA_STRU;


/* 每个TRCH的事件评估的参数 */
/* ASN.1 文本 : TransChCriteria */
typedef struct
{
    MACITF_UL_TRCH_ID_CHOICE_STRU       stTrchId;
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucEvtNum;           /* 事件评估的个数，必然有效 */
    MACITF_MAC_EVT_PARA_STRU            astEvtPara[PS_WUE_MAX_MEAS_PAR_EV_NUM];
}MACITF_TRAF_VOL_RPT_INFO_STRU;

/* 事件触发报告的参数的结构体 */
typedef struct
{
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucTrchCnt;          /* 用于事件评估的TrCH数,
                                                               对DCH进行测量时:
                                                                   如果网侧没有配置event trig 的DCH ID,RRC则配置ucTrchCnt = 0，并在 astTrafVolRptInfo[0]处填一套触发标准，
                                                                   MAC在RLC实体重配置后,将MACITF_MEAS_OBJ_LIST_STRU中有效的DCH作为MAC MEASUREMENT OBJECT，所有DCH相关触发参数均使用astTrafVolRptInfo[0]中的配置;
                                                                   如果网侧配置了event trig 的DCH ID，则使用配置的DCH ID,MAC在RLC实体重配置后,不进行任何更新
                                                               对RACH/EDCH测量时:
                                                                   ucTrchCnt一定是1
                                                               */
    MACITF_TRAF_VOL_RPT_INFO_STRU       astTrafVolRptInfo[PS_WUE_MAX_MEAS_TRCH_NUM];/* 每个TRCH的事件评估的参数 */
}MACITF_TRAF_VOL_RPT_CRTR_STRU;

/*****************************************************************************
 结构名    : MACITF_PERIOD_RPT_RSLT_STRU
 协议表格  : 14.4.2    Traffic Volume reporting triggers
 ASN.1描述 : TrafficVolumeMeasuredResults
 结构说明  : MAC上报测量结果,周期触发报告的参数的结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpVarBO          : 1;
    VOS_UINT32                          bitOpAveBO          : 1;
    VOS_UINT32                          bitOpBO             : 1;
    VOS_UINT32                          bitSpare            : 29;

    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucRbId;             /* [1,32],RB的ID */
    VOS_UINT16                          usVarBO;            /* 单位:字节，(0, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2K, 4K, 8K, 16K),N Kbytes = N*1024 bytes,RLC负载的方差 */
    VOS_UINT32                          ulAveBO;            /* 单位:字节，(0, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2K, 4K, 8K, 16K, 32K, 64K, 128K, 256K, 512K, 1024K),N Kbytes = N*1024 bytes,RLC负载的均值 */
    VOS_UINT32                          ulBO;               /* 单位:字节，(0, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2K, 4K, 8K, 16K, 32K, 64K, 128K, 256K, 512K, 1024K),N Kbytes = N*1024 bytes,RLC负载 */
}MACITF_PERIOD_RPT_RB_RESULT_STRU;

/*****************************************************************************
 结构名    : MACITF_PERIOD_RPT_RSLT_STRU
 协议表格  : 14.4.2    Traffic Volume reporting triggers
 ASN.1描述 : TrafficVolumeMeasuredResultsList
 结构说明  : MAC上报测量结果,周期触发报告的参数的结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucRbCnt;            /*[0,32],报告的RB个数 */
    MACITF_PERIOD_RPT_RB_RESULT_STRU    astRbRslt[PS_WUE_MAX_RB_NUM];/* RB的测量结果 */
} MACITF_MEAS_RSLT_STRU;


/*****************************************************************************
 结构名    : MACITF_EVENT_RPT_RSLT_STRU
 协议表格  : 14.4.2    Traffic Volume reporting triggers
 ASN.1描述 : TrafficVolumeEventResults
 结构说明  : MAC上报测量结果,事件
*****************************************************************************/
/* 事件触发结果的参数的结构体 */
typedef struct
{
    /*ASN.1:measuredResults                MeasuredResults*/
    MACITF_MEAS_RSLT_STRU               stMeasRslt;

    /*ASN.1:eventResults                EventResults*/
    MACITF_UL_TRCH_ID_CHOICE_STRU       stUlTrchId;         /* 传输信道标识 */
    MACITF_TRAF_VOL_EVT_TYPE_ENUM_UINT8 enEvtId;            /* 事件的标识 */
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
}MACITF_EVENT_RPT_RSLT_STRU;

/*****************************************************************************
 结构名    : MACITF_RACH_TRANS_PARAMS_STRU
 协议表格  : 10.3.6.67 RACH transmission parameters
 ASN.1描述 : RACH_TransmissionParameters
 结构说明  : 随即接入的重传信息
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMmax;             /* [1,32],preamble part最大发送次数 */
    VOS_UINT8                           ucNB01Min;          /* [0,50],用于产生随机数NBO1的下限值， 0 <= NBO1min <= NBO1 <= NBO1max */
    VOS_UINT8                           ucNB01Max;          /* [0,50],用于产生随机数NBO1的上限值， 0 <= NBO1min <= NBO1 <= NBO1max */
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */
}MACITF_RACH_TRANS_PARAMS_STRU;

/*****************************************************************************
 结构名    : MACITF_RACH_ASC_INFO_STRU
 协议表格  : 10.3.6.48    Persistence scaling factors
             10.3.6.1    AC-to-ASC mapping
 ASN.1描述 : PRACH_SystemInformation
             AC_To_ASC_MappingTable
             PersistenceScalingFactorList
 结构说明  : RACH的接入信息
             P(N) = 2^[-(N - 1)]，N来自SIB5,SIB6的WAS_DYN_PERSIST_LEV_LIST_STRU，
             值域为1..8。
             Si = Persistence scaling factors,Real(0.9..0.2, by step of 0.1)
             Pi = si * P(N)。
             概率最小的情况为，N = 8，Si = 0.2,
              Pi = 0.2 * 0.0078125 = 0.0015625
             概率最大的情况为，N = 1, 做紧急呼叫
              Pi = 1 * 1 = 1。
             接口上AscPi = Pi * MACITF_ASC_PI_MULTIPLE，保证精度。
             [注]CCB表中的WAS_PERSIST_SCALING_FACTOR_LIST_STRU值在保存时已经
                 扩大了MACITF_ASC_PI_MULTIPLE倍.
*****************************************************************************/
typedef struct
{
    /* 当UE没有配置URNTI时，WAS根据AC算出ucAscWithoutURnti */
    VOS_UINT8                           ucAscWithoutURnti;

    /* ucAscCnt = ucNumAsc+1,ucNumAsc的范围0..7，ASC的实际取值i:0 <= i <= NumASC <= 7,在IDEL、PCH态，RRC配置的ucAscCnt=0 */
    VOS_UINT8                           ucAscCnt;
    /* 当UE已经配置URNTI时使用，数组下标是ASC值，数组元素值为ASC对应的Pi值 */
    VOS_UINT16                          ausAscPi[PS_WUE_MAX_ASC_NUM];
}MACITF_RACH_ASC_INFO_STRU;

/*****************************************************************************
 结构名    : MACITF_RACH_ACCESS_INFO_STRU
 协议表格  : 10.2.48.8.8 System Information Block type 5
 ASN.1描述 : SysInfoType5
             PRACH_SystemInformation
 结构说明  : RACH的接入信息
*****************************************************************************/
typedef struct
{
    MACITF_RACH_TRANS_PARAMS_STRU       stRachTransParams;  /* RACH 发送参数 */
    MACITF_RACH_ASC_INFO_STRU           stRachAscInfo;      /* RACH ASC信息 */
}MACITF_RACH_ACCESS_INFO_STRU;

/* ASN.1 文本 : MAC_d_FlowIdentityDCHandHSDSCH */
typedef struct {
    VOS_UINT8                           ucDchId;            /* INTEGER(1..32) */
    VOS_UINT8                           ucHsdschMacDFlowId; /* INTEGER(0..7) */
}MACITF_MACD_FLOW_ID_DCH_HSDSCH;

/*V3 R7_7C1 Start */
typedef struct {
    VOS_UINT8                           ucDchId;            /* INTEGER(1..32) */
    VOS_UINT8                           ucHsdschMacEhsQueueId;/*INTEGER(0..7),for MAC-ehs*/
}MACITF_MACEHS_QUEUE_ID_DCH_HSDSCH;

/* V3 R7_7C1 End */

/*****************************************************************************
 结构名    : MACITF_UL_PER_LOCH_MAPP_CHOICE_STRU
 协议表格  : 10.3.4.21    RB mapping info
 ASN.1描述 : UL_LogicalChannelMappingList_r6
 结构说明  : 上行TRCH和LOCH的映射关系，包括RACH,DCH,EDCH
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulChoice;

    #define      MACITF_UL_D_RACH_DCH_MAPP_CHOSEN                 0
    #define      MACITF_UL_D_EDCH_MAPP_CHOSEN                     1

    union
    {
        MACITF_RACH_DCH_LOCH_MAPP_STRU  stRachDchMapp;
        MACITF_EDCH_LOCH_MAPP_STRU      stEdchMapp;
    }u;
}MACITF_UL_PER_LOCH_MAPP_CHOICE_STRU;

/*****************************************************************************
 结构名    : MACITF_DL_TRCH_TYPE_CHOICE_STRU
 协议表格  : 10.3.4.21    RB mapping info
 ASN.1描述 : DL_TransportChannelType_r5
 结构说明  : 下行传输信道
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulChoice;

    #define      MACITF_TRCH_TYPE_DCH_CHOSEN                  0
    #define      MACITF_TRCH_TYPE_FACH_CHOSEN                 1
    #define      MACITF_TRCH_TYPE_DSCH_CHOSEN                 2
    #define      MACITF_TRCH_TYPE_DCH_AND_DSCH_CHOSEN         3
    #define      MACITF_TRCH_TYPE_HSDSCH_CHOSEN               4
    #define      MACITF_TRCH_TYPE_DCH_HSDSCH_CHOSEN           5
    /*V3 R7_7C1 Start */
    #define      MACITF_TRCH_TYPE_MACEHS_QUEUE_CHOSEN         6    /* for MAC-ehs */
    #define      MACITF_TRCH_TYPE_DCH_MACEHS_QUEUE_CHOSEN     7    /* for MAC-ehs multi mapping */
    /* V3 R7_7C1 End */


    /* The IE "Downlink transport channel type" values " DSCH" and
       "DCH+DSCH " should not be used for FDD. If received the UE
       behaviour is unspecified. */
    union
    {
        VOS_UINT8                           ucDchId;            /* [PS_WUE_MIN_TRCH_ID,PS_WUE_MAX_TRCH_ID] */
        PS_NULL_STRU                        stFach;             /* FACH时，MAC通过CT域获得映射关系 */
        PS_NULL_STRU                        stDschId;           /* TDD */
        PS_NULL_STRU                        stDchDschId;        /* TDD */
        VOS_UINT8                           ucHsdschMacDFlowId; /* INTEGER(0..7) */
        MACITF_MACD_FLOW_ID_DCH_HSDSCH      stDchHsdschId;
        /*V3 R7_7C1 Start */
        VOS_UINT8                           ucHsdschMacEhsQueueId;/*INTEGER(0..7),for MAC-ehs*/
        MACITF_MACEHS_QUEUE_ID_DCH_HSDSCH   stDchMacEhsHsdschId;    /* for MAC-ehs */
        /* V3 R7_7C1 End */

    }u;
}MACITF_DL_TRCH_TYPE_CHOICE_STRU;

/*****************************************************************************
 结构名    : MACITF_DL_PER_LOCH_MAPP_STRU
 协议表格  : 10.3.4.21    RB mapping info
 ASN.1描述 : DL_LogicalChannelMappingList_r5
 结构说明  : 下行逻辑信道与传输信道的映射
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucLochLabel;        /* 逻辑信道内部实现统一标识：[0,[0,34*2-1]] */
    VOS_UINT8                           ucLochId;           /* INTEGER(1..15),0表示无效 */
    MACITF_DL_TRCH_TYPE_CHOICE_STRU     stTrchInfo;
}MACITF_DL_PER_LOCH_MAPP_STRU;

/*****************************************************************************
 结构名    : MACITF_DL_LOCH_MAPP_STRU
 协议表格  : 10.3.4.21    RB mapping info
 ASN.1描述 : DL_LogicalChannelMappingList_r5
 结构说明  : 下行逻辑信道与传输信道的映射
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucDlPerRlcLochCnt;  /* [1,2] */
    MACITF_DL_PER_LOCH_MAPP_STRU        astDlLochInfo[PS_WUE_MAX_LOCH_PER_RLC_NUM];/*对于下行信道，不需要逻辑信道优先级*/
}MACITF_DL_LOCH_MAPP_STRU;

/*****************************************************************************
 结构名    : MACITF_UL_LOCH_MAPP_STRU
 协议表格  : 10.3.4.21    RB mapping info
 ASN.1描述 : UL_LogicalChannelMappingList_r6
 结构说明  : 上行逻辑信道与传输信道的映射
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucUlPerRlcLochCnt;  /* [1,2] */
    MACITF_UL_PER_LOCH_MAPP_CHOICE_STRU astUlLochInfo[PS_WUE_MAX_LOCH_PER_RLC_NUM];
}MACITF_UL_LOCH_MAPP_STRU;

/*****************************************************************************
 结构名    : MACITF_RB_MAPP_STRU
 协议表格  : 10.3.4.21    RB mapping info
 ASN.1描述 : RB_MappingOption_r6
 结构说明  : 上行，下行逻辑信道与传输信道的映射
*****************************************************************************/
typedef struct
{
    MACITF_UL_LOCH_MAPP_STRU            stUlLochMapp;       /* 上行逻辑信道信息 */
    MACITF_DL_LOCH_MAPP_STRU            stDlLochMapp;       /* 下行逻辑信道信息 */
}MACITF_RB_MAPP_STRU;

/*****************************************************************************
 结构名    : MACITF_RB_MAPP_INFO_STRU
 协议表格  : 10.3.4.21    RB mapping info
 ASN.1描述 : RB_MappingInfo
 结构说明  : 逻辑信道与传输信道的映射信息
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucRbId;             /* RB ID */
    WUE_CN_DOMAIN_TYPE_ENUM_UINT8       enCnDomain;         /* 用于加密,如果是信令RB，则填:WUE_CN_DOMAIN_TYPE_BUTT */
    WUE_TRAFFIC_TYPE_ENUM_UINT8         enTrafficType;      /* 当enCnDomain = WUE_CS_DOMAIN时有效，用于区分AMR和CSD业务 */
    MACITF_RB_MAPP_STRU                 stRbMapp;
}MACITF_RB_MAPP_INFO_STRU;

/*****************************************************************************
 结构名    : MACITF_RB_MAPPING_INFO_STRU
 协议表格  : 10.3.4.24 Signalling RB information to setup
             10.3.4.20 RB information to setup
             10.3.4.19 RB information to release
 ASN.1描述 : RB_InformationReconfig_r6
             RB_InformationAffected_r6
             SRB_InformationSetup
             RB_InformationSetup
 结构说明  : 建立，修改，释放，逻辑信道与传输信道的映射信息，
             WAS每次使用全套配置配置MAC，MAC只需要对该套配置做独立的参数检查，
             不需要与前一套配置做校验。
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucRbCnt;            /* 0表示不选中 */
    MACITF_RB_MAPP_INFO_STRU            astRbInfoSetup[PS_WUE_MAX_RB_NUM];/* UU_MAX_LCH-->PS_WUE_MAX_RB_NUM */
}MACITF_RB_MAPP_INFO_LIST_STRU;

/*****************************************************************************
 结构名    : MACITF_TB_CNT_INFO_STRU
 协议表格  : 10.3.5.2a  Additional Dynamic Transport Format Information for CCCH
             Dynamic Transport Format Information
 ASN.1描述 : NumberOfTransportBlocks
 结构说明  : 每种RLCSIZE对应的TB CNT信息
             2> consider the first instance of the parameter Number of TBs
             and TTI List within the Dynamic transport format information to
             correspond to transport format 0 for this transport channel,
             the second to transport format 1 and so on;
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucTfi;              /* 传输格式指示 */
    VOS_UINT16                          usTbCnt;            /*[0，512],TB数目,HI4131 规格最大32*/
} MACITF_TB_CNT_INFO_STRU;

/*****************************************************************************
 结构名    : MACITF_TF_INFO_STRU
 协议表格  : 10.3.5.2a  Additional Dynamic Transport Format Information for CCCH
             Dynamic Transport Format Information
 ASN.1描述 : DedicatedDynamicTF_Info
             CommonDynamicTF_Info
 结构说明  : 传输格式信息
             TF信息,TFI对应的就是这个结构的数组下标，根据TB的个数排序
*****************************************************************************/
typedef struct
{
    /* 对于专用信道，RLC size反映的是RLC PDU的大小。
       对于公共信道，RLC size反映了实际的TB大小。
       参考8.6.5.1  Transport Format Set最后 */

    VOS_UINT16                          usRlcSize;          /* 单位：Bit */
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucTbCntInfoNum;     /* 每种RLC SIZE下的TF个数*/
    MACITF_TB_CNT_INFO_STRU             astTbCntInfo[PS_WUE_MAX_TF_NUM]; /* Tb数目［0，512］*/
}MACITF_TF_INFO_STRU;

/*****************************************************************************
 结构名    : MACITF_DCH_TFI_LIST_STRU
 协议表格  : 10.3.5.13    TFCS Explicit Configuration
 ASN.1描述 : TFCS对应的TFI的列表
 结构说明  : DCH的传输格式组合
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTfiNum;           /* ucTfiNum = TrchNum */
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT8                           aucTfi[PS_WUE_MAX_DCH_NUM];/*该数组下标的排列顺序与MACITF_UL_DCH_INFO_LIST_STRU中astUlDchInfo[PS_WUE_MAX_DCH_NUM]的下标排列顺序完全一致*/
}MACITF_DCH_TFI_LIST_STRU;


/*****************************************************************************
 结构名    : MACITF_UL_DCH_TFC_INFO_STRU
 协议表格  : 10.3.5.13    TFCS Explicit Configuration
 ASN.1描述 : TFCS
 结构说明  : 上行DCH的传输格式组合
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCtfc;             /* 可能的BIT范围：2,4,6,8,12,16,24 BIT */
    PS_BOOL_ENUM_UINT8                  enTfcMinSetInd;     /* 预留接口，目前不使用标志此TFC是否属于最小集，minimum set of TFC必然属于set of valid TFCs，因为MAC TFC选择暂不考虑功率因素，因此最小集概念暂不需要使用，RRC配置MAC的接口中带有enTfcMinSetInd，留作以后扩展实现用 */
    PS_BOOL_ENUM_UINT8                  enTfcValidInd;      /*该TFC是否有效标记，网侧可能会删除某个TFC，此时该标记置为PS_FALSE*/
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
    MACITF_DCH_TFI_LIST_STRU            stTfiList;
} MACITF_UL_DCH_TFC_INFO_STRU;

/*****************************************************************************
 结构名    : MACITF_UL_DCH_TFCS_STRU
 协议表格  : 10.3.5.13    TFCS Explicit Configuration
 ASN.1描述 : TFCS
 结构说明  : 上行DCH的传输格式组合
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
    VOS_UINT16                          usUlTfcCnt;         /* UL TFC个数 */
    MACITF_UL_DCH_TFC_INFO_STRU         astUlTfc[PS_WUE_MAX_UL_TFC_NUM]; /*数组下标就是TFCI*/
}MACITF_UL_DCH_TFCS_STRU;

typedef struct
{
    VOS_UINT16                          usTfcSubSetCnt;     /* ultfc cnt is less than dl tfc */                                                         /* TFC个数                                  */
    VOS_UINT16                          ausTfcSubSetIdx[PS_WUE_MAX_TFC_SUB_NUM];/* [0...MAX_TFC_SUB],协议规格1024,所以定义UINT16便于扩展，允许的TFCI
                                                                                   该数组元素的值对应数组astUlTfc[PS_WUE_MAX_UL_TFC_NUM]的下标，就是TFCI*/
}MACITF_UL_DCH_TFC_SUBSET_STRU;

/*****************************************************************************
 结构名    : MACITF_UL_DCH_COMM_INFO_STRU
 协议表格  : 10.3.5.13    TFCS Explicit Configuration
 ASN.1描述 : TFCS
 结构说明  : 上行DCH的传输格式组合
*****************************************************************************/
typedef struct
{
    MACITF_UL_DCH_TFCS_STRU             stUlTfcs;
    MACITF_UL_DCH_TFC_SUBSET_STRU       stUlTfcsSubset;
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
}MACITF_UL_DCH_COMM_INFO_STRU;

/*****************************************************************************
 结构名    : MACITF_RACH_TFC_INFO_STRU
 协议表格  : 10.3.6.55    PRACH system information list
 ASN.1描述 : PRACH_SystemInformation
             rach_TFCS  TFCS
 结构说明  : 上行公共信道的传输格式组合
*****************************************************************************/
typedef struct
{
    /* 可能的BIT范围：2,4,6,8,12,16,24 BIT */
    VOS_UINT32                          ulCtfc;
    VOS_UINT8                           ucTfi;              /* [0,31] */
    PS_BOOL_ENUM_UINT8                  enTfcMinSetInd;     /* 预留接口，目前不使用标志此TFC是否属于最小集，minimum set of TFC必然属于set of valid TFCs，因为MAC TFC选择暂不考虑功率因素，因此最小集概念暂不需要使用，RRC配置MAC的接口中带有enTfcMinSetInd，留作以后扩展实现用 */
    VOS_INT8                            cPwrOffsetPpM;      /* 兼容4121接口，所以增加这个IE在MAC接口，INTEGER(-5..10)  OPTIONAL */
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */
}MACITF_RACH_TFC_INFO_STRU;

/*****************************************************************************
 结构名    : MACITF_RACH_CCCH_TFC_INFO_STRU
 协议表格  : 10.3.6.55    PRACH system information list
 ASN.1描述 : PRACH_SystemInformation
             rach_TFCS  TFCS
             AdditionalPRACH_TF_and_TFCS_CCCH_IEs
             参考CR RP28 RP-050392
 结构说明  : 8.1.1.6.5  System Information Block type 5 and 5bis
             1>  if the IE "Additional Dynamic Transport Format Information for CCCH"
                 is included for the selected PRACH:
                 2>  use this transport format for transmission of the CCCH.
             1>  else:
                 2>  use the first instance of the list of transport formats as
                 in the IE "RACH TFS" for the used RACH received in the IE
                 "PRACH system information list" when using the CCCH.
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTfi;              /* [0,31] */
    VOS_INT8                            cPwrOffsetPpM;      /* 兼容4121接口，所以增加这个IE在MAC接口，INTEGER(-5..10)  OPTIONAL */
}MACITF_RACH_CCCH_TFC_INFO_STRU;

/*****************************************************************************
 结构名    : MACITF_RACH_COMM_INFO_STRU
 协议表格  : 10.3.6.55    PRACH system information list
 ASN.1描述 : PRACH_SystemInformation
             rach_TFCS
 结构说明  : 上行公共信道的传输格式组合集
             对应RACH，一个PRACH对应一个RACH，所以不需要TRCH ID，
             TFC的个数就是TF的个数
*****************************************************************************/
typedef struct
{
    /*  1>  if the IE "Additional Dynamic Transport Format Information for CCCH"    */
    /*      is included for the selected PRACH:                                     */
    /*  2>  use this transport format for transmission of the CCCH.                 */
    /*  1>  else:                                                                   */
    /*  2>  use the first instance of the list of transport formats as in the       */
    /*      IE "RACH TFS" for the used RACH received in the IE                      */
    /*      "PRACH system information list" when using the CCCH.                    */
    /* AdditionalPRACH_TF_and_TFCS_CCCH_IEs，参考CR RP28 RP-050392 */
    PS_BOOL_ENUM_UINT8                  enAddCcchTfcExist;              /* stCcchTfc是否存在 */
    MACITF_RACH_CCCH_TFC_INFO_STRU      stCcchTfc;                      /* AdditionalPRACH_TF_and_TFCS_CCCH_IEs时配置，其他情况不配置 */
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */

    VOS_UINT16                          usUlTfcCnt;                     /* UL TFC个数 */
    MACITF_RACH_TFC_INFO_STRU           astRachTfc[PS_WUE_CAP_MAX_TF_UL];   /* 非AdditionalPRACH的TFC配置 */
}MACITF_RACH_COMM_INFO_STRU;

/*****************************************************************************
 结构名    : MACITF_REF_E_TFCI_STRU
 协议表格  : 10.3.6.99    E-DPDCH Info
             E-DCH minimum set E-TFCI
 ASN.1描述 : E_DPDCH_Reference_E_TFCI
 结构说明  : EDCH的TFCI
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRefETfci;         /* [0,127] */
    VOS_UINT8                           ucRefETfciPo;       /* [0,31] */
}MACITF_REF_E_TFCI_STRU;

/*****************************************************************************
 结构名    : MACITF_EDCH_TFCS_STRU
 协议表格  : 10.3.6.99    E-DPDCH Info
 ASN.1描述 : E_DPDCH_Info
 结构说明  : EDCH的TFCS
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucETfciTblIdx;     /* 0:E-DCH Transport Block Size Table 0;1:Table 1 */
    VOS_UINT8                           ucMinSetETfci;     /* [0,127]，如果网侧未配置，则填PS_NULL_UINT8，表示无效 */
    /* ASN.1 文本 : E_DPDCH_Reference_E_TFCIList */
    VOS_UINT8                           ucRefETfciCnt;     /* [0,8],0表示不选中 */
    MACITF_REF_E_TFCI_STRU              astRefETfci[PS_WUE_MAX_REF_E_TFCI_NUM];
}MACITF_EDCH_TFCS_STRU;

/* MAC_D_CONFIG_REQ 和 MAC_C_CONFIG_REQ 精简结构 用于L2 ST测试使用，不用于实际接口中 */
/*========================*/            /* RRC_MAC_D_CONFIG_REDUCE_REQ_STRU */
typedef struct
{
    VOS_UINT8                           ucTfi;
    VOS_UINT8                           ucRlcSizeIdx;
    VOS_UINT16                          usTbCnt;
}MACITF_TF_INFO_REDUCE_STRU;


/*****************************************************************************
 结构名    : MACITF_TRCH_INFO_STRU
 协议表格  : 10.3.5.2    Added or Reconfigured UL TrCH information
 ASN.1描述 : CommonDynamicTF_Info
             DedicatedTransChTFS
 结构说明  : 上行传输信道传输格式，公共信道和专用信道通用
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTrchId;                           /* [PS_WUE_MIN_TRCH_ID,PS_WUE_MAX_TRCH_ID] */
    MACITF_TTI_ENUM_UINT8               enTti;                              /* 单位10ms,根据实际取值配置MAC */
    MACITF_CRC_SIZE_ENUM_UINT8          enCrcSize;                          /* CRC bit长度: 0、8、12、16、24，TEST LOOP MODE2，TM RLC时用 */

    VOS_UINT8                           ucRlcSizeNum;                       /*[0,PS_WUE_MAX_TF_NUM],该传输信道RLC SIZE的个数 */
    VOS_UINT16                          astRlcSize[PS_WUE_MAX_TF_NUM];      /* 每种RLC SIZE下的TF信息,数组下标对应一种RLC SIZE的索引 */
    VOS_UINT8                           ucTfNum;                            /*[0,PS_WUE_CAP_MAX_TF_DL],该传输信道TF的个数 */
    VOS_UINT8                           aucRsv[3];
    MACITF_TF_INFO_REDUCE_STRU          astTfs[PS_WUE_CAP_MAX_TF_DL];       /* 每种传输信道下的TF信息,数组下标对应一种TF的索引 */
}MACITF_TRCH_INFO_STRU;

/*****************************************************************************
 结构名    : MACITF_UL_DCH_INFO_LIST_STRU
 协议表格  : 10.3.5.2    Added or Reconfigured UL TrCH information
 ASN.1描述 : UL_AddReconfTransChInformation
 结构说明  : 上行所有的专用传输信道传输格式集
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucUlDchCnt;                     /* 0..PS_WUE_MAX_DCH_NUM - 1 */
    MACITF_TRCH_INFO_STRU               astUlDchInfo[PS_WUE_MAX_DCH_NUM];
}MACITF_UL_DCH_INFO_LIST_STRU;

/*****************************************************************************
 结构名    : MACITF_NON_SCHED_GRANT_STRU
 协议表格  : 10.3.5.1b    Added or reconfigured E-DCH MAC-d flow
 ASN.1描述 : transmissionGrantType
 结构说明  : 非调度授权
*****************************************************************************/
typedef struct
{
    /* ASN.1 : maxMAC_e_PDUContents */
    VOS_UINT16                          usEFlowMaxMacEPduSize;          /* [1...19982] bit */
    /* ASN.1 : ms2_NonSchedTransmGrantHARQAlloc */
    VOS_UINT8                           uc2msNonSchedGrantProcAlloc;    /* BITMAP,2ms TTI,非调度授权进程配置，
                                                                           bit位值为1时传送有效
                                                                           Bit 0 corresponds to HARQ process 0, bit 1 corresponds to HARQ process 1...
                                                                           网络不携带，表示全配，Default value is: transmission in all HARQ processes is allowed. */
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */
}MACITF_NON_SCHED_GRANT_STRU ;

/*****************************************************************************
 结构名    : MACITF_EFLOW_TRANS_GRANT_INFO_STRU
 协议表格  : 10.3.5.1b    Added or reconfigured E-DCH MAC-d flow
 ASN.1描述 : transmissionGrantType
             E_DPDCH_SchedulingTransmConfiguration
             ms2_SchedTransmGrantHARQAlloc
 结构说明  : E DCH流的配置
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulChoice;

    #define      MACITF_NON_SCHED_GRANT_INFO_CHOSEN                0
    #define      MACITF_SCHED_GRANT_INFO_CHOSEN                    1

    union
    {
        MACITF_NON_SCHED_GRANT_STRU     stNonSchedGrant;           /*只有当ucEFlowTransGrantType＝0时，该结构才有效；*/
        /* ASN.1 : E_DPDCH_SchedulingTransmConfiguration */
        VOS_UINT8                       uc2msSchedGrantProcAlloc;  /*BITMAP,2ms TTI,调度授权进程配置,该MAC-d流的数据
                                                                     只能在BIT位取值为1的进程上发送,Bit0对应进程0，Bit1对应进程1，以此类推...
                                                                     网络不携带表示全选，Default value is: transmission in all HARQ processes is allowed.*/
    }u;
}MACITF_EFLOW_TRANS_GRANT_INFO_STRU;

/*****************************************************************************
 结构名    : MACITF_EDCH_FLOW_STRU
 协议表格  : 10.3.5.1b    Added or reconfigured E-DCH MAC-d flow
 ASN.1描述 : E_DCH_AddReconf_MAC_d_Flow
 结构说明  : E DCH流的配置
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEFlowId;                  /* [0,7] */
    VOS_UINT8                           ucEFlowPwrOffset;           /* [0,6],dB 重配置时网络可能不携带，但是WAS固定配置给MAC */
    VOS_UINT8                           ucEFlowMaxReTrans;          /* [0,15] 重配置时网络可能不携带，但是WAS固定配置给MAC */
    VOS_UINT8                           ucEFlowMuxlist;             /* BITMAP,Bit0对应MAC-d流0，Bit1对应MAC-d流1，
                                                                       以此类推，BIT值为1表明相应的MAC-d流可以与当前MAC-d流复用在同一MAC-e PDU中发送;
                                                                       如果配置全0，表示没有复用 */
    MACITF_EFLOW_TRANS_GRANT_INFO_STRU  stEFlowTransGrantInfo;      /* Only allowed to be absent when already defined for this E-DCH MAC-d flow
                                                                       WAS每次都配置给MAC */
}MACITF_EDCH_FLOW_STRU;

/*****************************************************************************
 结构名    : MACITF_DL_CCH_INFO_STRU
 协议表格  : 10.3.5.23    Transport Format Set
             Dynamic Transport Format Information
 ASN.1描述 : FACH_PCH_Information
 结构说明  : 下行公共信道传输格式集
*****************************************************************************/
typedef struct
{
    MACITF_TRCH_TYPE_ENUM_UINT8         enTrchType;             /* FACH,PCH */
    PS_BOOL_ENUM_UINT8                  enCtchInd;              /* ctch_Indicator BOOLEAN */
    MACITF_TRCH_INFO_STRU               stDlCchInfo;            /* 每个TF的信息 */
}MACITF_DL_CCH_INFO_STRU;

/*****************************************************************************
 结构名    : MACITF_DL_CCH_INFO_LIST_STRU
 协议表格  : 10.3.5.23    Transport Format Set
 ASN.1描述 : FACH_PCH_InformationList CommonTransChTFS
 结构说明  : 下行所有的公共传输信道的传输格式集
             每个SCCPCH只能承载一个PCH，如果这个SCCPCH上映射有PCH，
             则这个SCCPCH信息会携带PICH INFO，同时PCH的TFS会作为
             MACITF_FACH_PCH_TFS_LIST_STRU的第一个元素。
             参考25.304 8.1   Paging Channel selection
             25.331 10.3.6.72    Secondary CCPCH system information
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCctrchIndex;                          /* 码组合传输信道索引 */
    VOS_UINT8                           ucDlCchCnt;                      /* FACH和PCH的信道个数之和 */
    MACITF_DL_CCH_INFO_STRU             astDlCchInfo[PS_WUE_MAX_FACH_PCH_NUM];  /* 每个FACH/PCH的信息 */
}MACITF_DL_CCH_INFO_LIST_STRU;

/*****************************************************************************
 结构名    : MACITF_DL_DCH_INFO_LIST_STRU
 协议表格  : 10.3.5.1    Added or Reconfigured DL TrCH information
  ASN.1描述 : DL_AddReconfTransChInfo2List
  结构说明  : 专用信道的传输格式集
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucDlDchCnt;                      /* DL DCH数 */
    MACITF_TRCH_INFO_STRU               astDlDchInfo[PS_WUE_MAX_DCH_NUM];  /* 每个DL DCH的信息 */
}MACITF_DL_DCH_INFO_LIST_STRU;

/*****************************************************************************
 结构名    : MACITF_HS_PDU_SIZE_INFO_STRU
 协议表格  : 10.3.5.1a    Added or reconfigured MAC-d flow
 ASN.1描述 : MAC_d_PDU_SizeInfo_List
 结构说明  : MAC D PDU大小
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMacdPduSize;  /* [1,5000]bit */
    VOS_UINT8                           ucHsPduSizeIdx; /* [0,7] ,对应MAC-hs PDU HEADER中的SID*/
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */
}MACITF_HS_PDU_SIZE_INFO_STRU;

/*****************************************************************************
 结构名    : MACITF_HS_QUEUE_INFO_STRU
 协议表格  : 10.3.5.1a    Added or reconfigured MAC-d flow
 ASN.1描述 : MAC_hs_AddReconfQueue
 结构说明  : HS的队列信息
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHsQueueId;    /* [0,7] */
    VOS_UINT8                           ucHsFlowId;     /* [0,7] */
    VOS_UINT16                          usT1;           /* Integer(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 120, 140, 160, 200, 300, 400)ms */
    VOS_UINT8                           ucHsWinSize;    /* Integer(4, 6, 8, 12, 16, 24, 32) */


    VOS_UINT8                           ucMacdPduSizeCnt;/* 1..PS_WUE_MAX_MAC_D_PDU_SIZES_NUM */
    MACITF_HS_PDU_SIZE_INFO_STRU        astHsPduSizeInfo[PS_WUE_MAX_MAC_D_PDU_SIZES_NUM];
}MACITF_HS_QUEUE_INFO_STRU;

/*****************************************************************************
 结构名    : MACITF_DCH_INFO_STRU
 协议表格  : 10.3.5.1    Added or Reconfigured DL TrCH information
             10.3.5.2    Added or Reconfigured UL TrCH information
             10.3.5.4    Deleted DL TrCH information
             10.3.5.5    Deleted UL TrCH information
 ASN.1描述 : UL_AddReconfTransChInfoList
             DL_AddReconfTransChInfo2List
             UL_DeletedTransChInfoList
             DL_DeletedTransChInfoList
 结构说明  : 专用信道的传输格式集，如果删除传输信道，
             WAS负责同时配置MACD，把映射在这个传输信道上的逻辑信道也删除。
             WAS每次使用全套配置配置MAC，MAC只需要对该套配置做独立的参数检查，
             不需要与前一套配置做校验。
*****************************************************************************/
typedef struct
{
    MACITF_UL_DCH_INFO_LIST_STRU            stUlDchInfoList;
    MACITF_DL_DCH_INFO_LIST_STRU            stDlDchInfoList;
}MACITF_DCH_INFO_STRU;

/*****************************************************************************
 结构名    : MACITF_HS_DSCH_INFO_STRU
 协议表格  : 10.3.6.23a    Downlink HS-PDSCH Information
 ASN.1描述 : HSDSCH_Info
             DL_DeletedTransChInfoList_r5
 结构说明  : HS DSCH的信息
             25.321 11.6.1.1    Scheduler
             Each MAC-d flow contains HS-DSCH MAC-d PDUs for one or more priority queues.
             25.331 10.3.5.1a    Added or reconfigured MAC-d flow
             The MAC-hs queue ID is unique across all MAC-d flows.
             所以一个FLOW可以包含多个QUEUE，但是一个QUEUE不能属于多个FLOW。
             如果网络通过DL-DeletedTransChInfoList_r5发起一个FLOW的删除，
             WAS遍历出需要释放的QUEUE，通过释放QUEUE释放MAC。
             对于这种情况，WAS负责同时配置MACD，把映射的逻辑信道也删除。
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucMacHsQueueCnt;       /* [1,PS_WUE_MAX_QUEUE_NUM] */
    MACITF_HS_QUEUE_INFO_STRU           astHsQueueInfo[PS_WUE_MAX_QUEUE_NUM];
}MACITF_HS_DSCH_INFO_STRU;


/*****************************************************************************
 结构名    : MACITF_CCTRCH_INFO_STRU
 协议表格  :
 ASN.1描述 : SysInfoType5
 结构说明  : 码组合传输信道列表
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCnt;                                  /* 码组合传输信道数 */
    VOS_UINT8                           aucReserve1[1];                         /* 4字节对齐，保留 */
    MACITF_DL_CCH_INFO_LIST_STRU        stDlCchInfoList[PS_WUE_MAX_SCCPCH_CCTRCH_NUM];  /*  */
}MACITF_CCTRCH_INFO_STRU;


/*****************************************************************************
 结构名    : MACITF_CCH_INFO_STRU
 协议表格  :
 ASN.1描述 : SysInfoType5
 结构说明  : 公共传输信道的传输格式集
*****************************************************************************/
typedef struct
{
    MACITF_TRCH_INFO_STRU               stRachInfo;       /* RRC全配置 */
    MACITF_CCTRCH_INFO_STRU             stCctrchInfo;  /* RRC全配置 */
}MACITF_CCH_INFO_STRU;


/* 协议表格 : 10.3.7.68 Traffic volume measurement  */
/* ASN.1 文本 : TrafficVolumeReportCriteria */
typedef struct
{
    #define     MACITF_TRAF_VOL_RPT_CRTR_CHOSEN         0
    #define     MACITF_PERIOD_RPT_CRTR_CHOSEN           1
    #define     MACITF_NO_RPT_CHOSEN                    2

    VOS_UINT32                          ulChoice;           /* 测量的报告模式:周期或事件  */
    union
    {
        MACITF_TRAF_VOL_RPT_CRTR_STRU   stTrafVolRptCrtr;   /* 事件触发报告的参数 */
        MACITF_PERIOD_RPT_CRTR_STRU     stPeriodRptCrtr;    /* 周期报告的参数 */
        PS_NULL_STRU                    stNoRpt;            /* MAC周期性上报RRC测量结果,暂定周期8000ms*/
    }u;
}MACITF_TRAF_MEAS_RPT_CRTR_CHOICE_STRU;


/*****************************************************************************
 结构名    : MACITF_TRAF_MEAS_RSLT_CHOICE_STRU
 协议表格  : 14.4.2    Traffic Volume reporting triggers
 ASN.1描述 : TrafficVolumeMeasuredResults
 结构说明  : MAC上报测量结果
*****************************************************************************/
typedef  struct
{
    #define     MACITF_EVENT_RPT_RSLT_CHOSEN            0
    #define     MACITF_PERIOD_RPT_RSLT_CHOSEN           1
    VOS_UINT32                          ulRptTypeChoice;     /* 报告的模式:周期或事件报告 */

    union
    {
        MACITF_EVENT_RPT_RSLT_STRU      stEvtRptRslt;       /* 事件报告结果 */
        MACITF_MEAS_RSLT_STRU           stPeriodRptRslt;    /* 周期报告结果 */
    }u;

}MACITF_TRAF_MEAS_RSLT_CHOICE_STRU;


/*****************************************************************************
 结构名    : MACITF_UE_ID_INFO_STRU
 协议表格  :
 ASN.1描述 : U_RNTI
             C_RNTI
 结构说明  : MAC C使用的UE ID
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpURnti          : 1;    /* URNTI与CRNTI可能同时存在 */
    VOS_UINT32                          bitOpCRnti          : 1;
    VOS_UINT32                          bitSpare            : 30;

    VOS_UINT32                          ulURnti;                    /* 32 bit */
    VOS_UINT16                          usCRnti;                    /* 16 bit */
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
}MACITF_UE_ID_INFO_STRU;

/*****************************************************************************
 结构名    : MACITF_HSUPA_INFO_STRU
 协议表格  : 10.3.6.99    E-DPDCH Info
                        Scheduling Information Configuration
 ASN.1描述 : E_DPDCH_SchedulingInfoConfiguration
 结构说明  : 调度信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usNoGrantPeriodic;  /* 单位ms, (everyEDCHTTI = 0xffff,4,10,20,50,100,200,500,1000),Default value is "no report"用0表示 */
    VOS_UINT16                          usGrantPeriodic;    /* 单位ms, (everyEDCHTTI = 0xffff,4,10,20,50,100,200,500,1000),Default value is "no report"用0表示 */
    VOS_UINT8                           ucSIPowOffset;      /* [0,6] */
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */
}MACITF_SCHED_INFO_CONFIG_STRU;

/*******************************************************************************
 结构名    : RRC_MAC_D_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息RRC_MAC_C_CONFIG_REQ的结构体
             对于MAC C实体，MAC实体上包含公共传输信道映射，以及CCCH,CTCH的逻辑信道映射配置，
             DTCH,DCCH的逻辑信道映射的配置在MAC D中，通过MAC D与MAC C的映射来完成
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* 操作标识 */

    VOS_UINT32                          bitTrchInfo         : 1;                /* 是否存在TRCH INFO */
    VOS_UINT32                          bitRachTfcs         : 1;                /* 是否存在tfcs */
    VOS_UINT32                          bitSpare            :30;
    VOS_INT16                           sActTime;           /*[0,255],加密激活时间CFN,PS_NEG_ONE表示立即激活 */

    MACITF_CCH_INFO_STRU                stTrchInfo;         /* 传输信道相关参数(TFS) */

    MACITF_RACH_COMM_INFO_STRU          stRachTfcs;         /* RACH的TFC信息*/

    MACITF_UE_ID_INFO_STRU              stUeIdInfo;         /* UE ID相关参数 */

    MACITF_RACH_ACCESS_INFO_STRU        stRachAcsInfo;      /* RACH 接入相关参数 */
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
}RRC_MAC_C_CONFIG_REQ_STRU;

/*******************************************************************************
 结构名    : RRC_MAC_C_CONFIG_REQ_MNTN_COMM_PARAM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息RRC_MAC_C_CONFIG_REQ的结构体
             可维可测消息结构PART1,除CCTRCH外所有配置
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* 操作标识 */

    VOS_INT16                           sActTime;           /*[0,255],加密激活时间CFN,PS_NEG_ONE表示立即激活 */
    VOS_UINT8                           ucCctrchCnt;        /* 码组合传输信道数 */
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */

    MACITF_TRCH_INFO_STRU               stRachInfo;         /* RRC全配置 */
    MACITF_RACH_COMM_INFO_STRU          stRachTfcs;         /* RACH的TFC信息*/
    MACITF_UE_ID_INFO_STRU              stUeIdInfo;         /* UE ID相关参数 */
    MACITF_RACH_ACCESS_INFO_STRU        stRachAcsInfo;      /* RACH 接入相关参数 */
    VOS_UINT8                           aucReserve2[2];     /* 4字节对齐，保留 */
}RRC_MAC_C_CONFIG_REQ_MNTN_COMM_PARAM_STRU;


/*******************************************************************************
 结构名    : RRC_MAC_C_CONFIG_REQ_MNTN_DLCCH1_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息RRC_MAC_C_CONFIG_REQ的结构体
             可维可测消息结构PART2,第一条DLCCH配置
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* 操作标识 */

    MACITF_DL_CCH_INFO_LIST_STRU        stDlCchInfoList;   /*  */
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
}RRC_MAC_C_CONFIG_REQ_MNTN_DLCCH1_STRU;

/*******************************************************************************
 结构名    : RRC_MAC_C_CONFIG_REQ_MNTN_DLCCH2_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息RRC_MAC_C_CONFIG_REQ的结构体
             可维可测消息结构PART2,第二条DLCCH配置
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* 操作标识 */

    MACITF_DL_CCH_INFO_LIST_STRU        stDlCchInfoList;   /*  */
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
}RRC_MAC_C_CONFIG_REQ_MNTN_DLCCH2_STRU;


/*******************************************************************************
 结构名    : MAC_RRC_C_CONFIG_CNF
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息RRC_MAC_C_CONFIG_REQ的响应消息
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* 操作标识 */
    MACITF_RSLT_ENUM_UINT32             enRslt;
}MAC_RRC_C_CONFIG_CNF_STRU;

/*****************************************************************************
 结构名    : MACITF_UL_SCHED_INFO_STRU
 协议表格  : 10.3.6.99    E-DPDCH Info
                        Scheduling Information Configuration
             10.3.6.98    E-DPCCH Info
 ASN.1描述 : E_DPCCH_Info
             E_DPDCH_SchedulingInfoConfiguration
 结构说明  : MAC上行调度信息
*****************************************************************************/
typedef struct
{
    /* E_DPCCH_Info中包含HappyBit_DelayCondition */
    VOS_UINT16                          usHappyBitDelayCond;/* (2ms, 10ms,20ms,50ms, 100ms, 200ms, 500ms, 1000ms) */
    /* E_DPDCH_SchedulingInfoConfiguration */
    MACITF_SCHED_INFO_CONFIG_STRU       stSchedInfoConfig;
}MACITF_UL_SCHED_INFO_STRU;

/*****************************************************************************
 结构名    : RRC_MAC_D_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息RRC_MAC_D_CONFIG_REQ的结构体
             对于MAC D实体，DTCH,DCCH的逻辑信道映射的配置在MAC D中，
             DCH的TRCH映射配置在MAC D中，
             HS-DSCH,E DCH的传输信道映射分别配置在MAC HS,MAC E中
             RACH,FACH的映射配置在MAC C中，通过MAC D与MAC C建立逻辑信道与传输信道的映射。
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* 操作标识 */

    VOS_INT16                           sActTime;           /*[0,255],加密激活时间CFN,PS_NEG_ONE表示立即激活 */
    VOS_INT8                            cMaxUeTxPwr;        /* [-50，33],上行链路最大发射功率= min(Maximum allowed UL TX Power=网侧配置的最大功率, PMAX =UE的最大功率规格),dbm */
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */

    VOS_UINT32                          bitOpTrchInfo       : 1;    /* 1:stTrchInfo存在，    0:不存在,在CELL_PCH/URA_PCH、CELL_FACH态配置MAC_D时，需要将bitOpTrchInfo设为0；在CELL_DCH状态下，如果上行专用传输信道只有E-DCH且下行专用物理信道只有F-DPCH时，也需要将bitOpTrchInfo设为0 */
    VOS_UINT32                          bitOpUlTrchTfcs     : 1;    /* 1:bitOpUlTrchTfcs存在，0:不存在,在CELL_PCH/URA_PCH、CELL_FACH态配置MAC_D时，需要将bitOpUlTrchTfcs设为0；在CELL_DCH状态下，如果上行专用传输信道只有E-DCH，也需要将bitOpUlTrchTfcs设为0 */
    VOS_UINT32                          bitSpare            : 30;

    MACITF_RB_MAPP_INFO_LIST_STRU       stRbMappInfoList;   /* RB映射相关参数 */

    MACITF_DCH_INFO_STRU                stTrchInfo;         /* 传输信道相关参数(TFS) */

    MACITF_UL_DCH_COMM_INFO_STRU        stUlTrchTfcs;       /* 上行DCH的TFC信息*/

}RRC_MAC_D_CONFIG_REQ_STRU;


/* 消息MAC_RRC_D_CONFIG_CNF的结构体 */
typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_D_CONFIG_CNF_STRU;


/*******************************************************************************
 结构名    : MACITF_MAC_E_VIRTUAL_LOCH_INFO
 协议表格  :
 ASN.1描述 :
 结构说明  : 配置MAC_E上复用的逻辑信道参数
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLochId;                               /* 范围:[1..15],各个逻辑信道的标识，不需要知道RB ID，因为E-DCH不需要进行业务量测量上报 */
    VOS_UINT8                           ucLochLabel;                            /* 范围:[2..65],MAC与RLC间内部通信只使用ucLochLabel,因此需要配置ID与Label间的映射关系 */
    VOS_UINT8                           ucEFlowId;                              /* [0,7] */
    MACITF_EDCH_FLOW_TYPE_ENUM_UINT8    enEdchMacdFlowType;                     /* MAC-d流类别: 调度流, 非调度流 */
    MACITF_RLC_PDU_FIXED_SIZE_STRU      stFixedSize;                            /* 当enRlcPduSizeType为fix size时, 有效 */
    MACITF_LOCH_DATA_TYPE_ENUM_UINT8    enLochDataType;                         /* 指示该LOCH对应的RB的数据类型 */
    VOS_UINT8                           aucReserve[3];
} MACITF_MAC_E_VIRTUAL_LOCH_INFO;

/*******************************************************************************
 结构名    : RRC_MAC_E_VIRTUAL_CONFIG_REQ
 协议表格  :
 ASN.1描述 :
 结构说明  : 配置MAC_E虚拟实体参数
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* 操作标识 */
    VOS_INT16                           sActTime;           /* [0,255],加密激活时间CFN,PS_NEG_ONE表示立即激活 */
    MACITF_EDCH_TTI_ENUM_UINT16         enEDCHTTI;          /* Edch TTI */
    PS_BOOL_ENUM_UINT8                  enFlushVBO;         /* 是否需要清除VirtualBO标志，PS_TRUE: 清除，PS_FALSE: 不清除*/
    VOS_UINT8                           aucReserve[2];
    VOS_UINT8                           ucLochCnt;          /* 映射到E-DCH上的逻辑信道个数 */
    MACITF_MAC_E_VIRTUAL_LOCH_INFO      astVirtualLochInfo[PS_WUE_MAX_E_DCH_LOCH_NUM]; /* VIRTUAL MAC_e/es实体逻辑信道信息 */
} RRC_MAC_E_VIRTUAL_CONFIG_REQ_STRU;

typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_E_VIRTUAL_CONFIG_CNF_STRU;


/*******************************************************************************
 结构名    : RRC_MAC_I_VIRTUAL_CONFIG_REQ
 协议表格  :
 ASN.1描述 :
 结构说明  : 配置MAC_I虚拟实体参数
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLochId;                               /* 范围:[1..15],各个逻辑信道的标识，不需要知道RB ID,15表示CCCH */
    VOS_UINT8                           ucLochLabel;                            /* 范围:[0..65],MAC与RLC间内部通信只使用ucLochLabel,因此需要配置ID与Label间的映射关系, CCCH配置0 */
    VOS_UINT8                           ucEFlowId;                              /* [0,7] */
    MACITF_EDCH_FLOW_TYPE_ENUM_UINT8    enEdchMacdFlowType;                     /* MAC-d流类别: 调度流, 非调度流 */
    MACITF_LOCH_DATA_TYPE_ENUM_UINT8    enLochDataType;                         /* 指示该LOCH对应的RB的数据类型 */
    MACITF_RLC_PDU_SIZE_TYPE_ENUM_UINT8 enRlcPduSizeType;                       /* Fixed size or Flexible size */
    VOS_UINT8                           aucReserve[2];
    MACITF_RLC_PDU_FIXED_SIZE_STRU      stFixedSize;                            /* 当enRlcPduSizeType为fix size时, 有效 */
} MACITF_MAC_I_VIRTUAL_LOCH_INFO;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;                              /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;                                 /* 操作标识 */
    VOS_INT16                           sActTime;                               /* [0,255],加密激活时间CFN,PS_NEG_ONE表示立即激活 */
    MACITF_EDCH_TTI_ENUM_UINT16         enEDCHTTI;                              /* Edch TTI */
    PS_BOOL_ENUM_UINT8                  enFlushVBO;                             /* 是否需要清除VirtualBO标志，PS_TRUE: 清除，PS_FALSE: 不清除*/
    VOS_UINT8                           ucLochCnt;                              /* 映射到E-DCH上的逻辑信道个数 当配置CCCH时, ucLochCnt个数一定为1 */
    VOS_UINT8                           aucReserve[2];
    MACITF_MAC_I_VIRTUAL_LOCH_INFO      astVirtualLochInfo[PS_WUE_MAX_E_DCH_LOCH_NUM]; /* VIRTUAL MAC_i/is实体逻辑信道信息 */
} RRC_MAC_I_VIRTUAL_CONFIG_REQ_STRU;

typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_I_VIRTUAL_CONFIG_CNF_STRU;

/*******************************************************************************
 结构名    : RRC_MAC_HS_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息RRC_MAC_HS_CONFIG_REQ_STRU的结构体
             RRC每次都全配置MSC_HS信息,不会增量配置。
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* 操作标识 */

    VOS_INT16                           sActTime;           /*[0,255], CFN,PS_NEG_ONE表示立即激活 */
    MACITF_HS_DSCH_INFO_STRU            stHsDschInfo;       /*HS-DSCH信息*/
}RRC_MAC_HS_CONFIG_REQ_STRU;

typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_HS_CONFIG_CNF_STRU;

/* 消息MAC_RRC_D_CONFIG_CNF的结构体 */
typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_E_RESET_CNF_STRU;

/* 消息MAC_RRC_HS_RESET_CNF_STRU的结构体 */
typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_HS_RESET_CNF_STRU;
typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_CONFIG_CNF_STRU;

/*******************************************************************************
 结构名    : RRC_MAC_RELEASE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 释放MAC实体
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* 操作标识 */
    MACITF_REL_MODE_ENUM_UINT8          enRelMode;          /* [0,1]，释放模式 */
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐, 保留 */
    VOS_INT16                           sActTime;           /* [0,255], 释放MAC实体激活时间CFN, PS_NEG_ONE表示立即激活 */
}RRC_MAC_RELEASE_REQ_STRU;

typedef RRC_MAC_RELEASE_REQ_STRU RRC_MAC_QUIT_REQ_STRU ;
/* 消息MAC_RRC_RELEASE_CNF的结构体 */
typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_RELEASE_CNF_STRU;

/*******************************************************************************
 结构名    : RRC_MAC_TFC_CONTROL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TFC CONTROL 过程只用于DCH
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpID;             /* 操作标识*/
    VOS_INT16                           sActTime;           /*[0,255],加密激活时间CFN,PS_NEG_ONE表示立即激活 */
    VOS_UINT16                          usDuration;         /* 单位ms,10,20,40,80,160,240,320,480,640,1280,1920,2560,5120;0表示一直存在*/
    MACITF_UL_DCH_TFC_SUBSET_STRU       stTfcsSubSet;
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
}RRC_MAC_TFC_CONTROL_REQ_STRU;

/*******************************************************************************
 结构名    : MAC_RRC_TFC_CONTROL_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TFC CONTROL IND，MAC指示RRC开始使用TFC子集，
             或者duration超时
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpID;             /* 操作标识*/
    MACITF_TFC_CTRL_ENUM_UINT8          enTfcCtrlFlag;      /* TFC子集使用信息:
                                                               MAC_TFC_CTL_BEGIN:激活时间到，开始使用CURRENT TFCS;
                                                               MAC_TFC_CTL_END:  duration超时，使用结束，恢复DEFAULT TFCS集合 */
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
}MAC_RRC_TFC_CONTROL_IND_STRU;


/* 消息RRC_MAC_CIPHER_CONFIG_REQ的结构体 */
typedef struct
{
    WUEL2L3_CIPHER_ALGO_ENUM_UINT8      enCipherAlgo;       /* [0,1],加密算法 0： MAC_CIPHER_UEA0，1：MAC_CIPHER_UEA1 */
    PS_BOOL_ENUM_UINT8                  enHfnChangFlag;     /* PS_FALSE：Hfn不随Cfn的复位而变化；PS_TRUE：Cfn每次发生复位后Hfn加1 */
    PS_BOOL_ENUM_UINT8                  enHfnAddOneInd;     /* PS_TRUE，RRC初始配置的HFN要增加1后，MAC再正常维护,请参见25.331 (8.3.6.3)、(8.6.4.3)、(8.6.6.28)
                                                               increment the HFN component of the COUNT-C variable by one even if the "COUNT-C activation time" is set to zero*/
    VOS_UINT8                           ucCsRBCnt;          /* [0,4]，CS域RB个数,其中不包含SRB,ucCsRbCnt=0，表明CS域不需要加密 */
    VOS_UINT8                           aucCsRBId[PS_WUE_MAX_CS_RB_NUM];/* [5,32],CS域业务RB列表*/
    VOS_UINT8                           aucCsCk[PS_WUE_CIPHER_KEY_LEN];/* 128bit,CS域加密密钥*/
    VOS_INT16                           sCsActTimeCfn;      /* 激活时间，[0,255], -1表示立即激活 */
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
    VOS_UINT32                          ulCsRbCountCMsb;    /* 对于TM RLC: ulCsRbCountCMsb(20BIT MSB) + 0000 + CFN(8BIT LSB)直接用于形成对应RB的CS域COUNT_C; */

    VOS_UINT8                           aucReserve2[2];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucPsRBCnt;          /* [0,2],PS域RB个数,其中不包含SRB，我们的规格最多同时支持2个PS域业务RB */
    VOS_UINT8                           aucPsRBId[PS_WUE_MAX_PS_RB_NUM];/* [5,32],PS域业务RB列表 */
    VOS_UINT8                           aucPsCk[PS_WUE_CIPHER_KEY_LEN];/* 128bit,PS域加密密钥 */

    VOS_INT16                           sPsActTimeCfn;         /* 激活时间，[0,255], -1表示立即激活*/
    PS_BOOL_ENUM_UINT8                  enActPrevCipherCfgFlag;/*在定时初始化硬切换或者非D2D接收到非rb setup消息时,配置mac加密时如果有上一次加密的加密时间没到，直接覆盖第一次加密参数*/
    VOS_UINT8                           aucReserve3;           /* 4字节对齐，保留 */
    VOS_UINT32                          ulPsRbCountCMsb;       /* 对于TM RLC: ulPsRbCountCMsb(20BIT MSB) + 0000 + CFN(8BIT LSB)直接用于形成对应RB的PS域COUNT_C; */
}MACITF_CIPHER_CONFIG_INFO_STRU;

/*******************************************************************************
 结构名    : RRC_MAC_CIPHER_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC加密配置
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpID;             /* 操作标识*/
    MACITF_CIPHER_CONFIG_INFO_STRU      stCipherInfo;
}RRC_MAC_CIPHER_CONFIG_REQ_STRU;


/*******************************************************************************
 结构名    : MAC_RRC_CIPHER_CONFIG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC加密配置响应
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpID;             /* 操作标识 */
    MACITF_RSLT_ENUM_UINT32             enRslt;
}MAC_RRC_CIPHER_CONFIG_CNF_STRU;


/*******************************************************************************
 结构名    : MAC_RRC_CIPHER_ACTIVE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC加密激活时间
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* 操作标识 */
    WUE_CN_DOMAIN_TYPE_ENUM_UINT8       enCnDomainId;       /* [0,1],加密激活的核心网域标识,MAC_CS_DOMAIN:CS域;MAC_PS_DOMAIN,PS域 */
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
}MAC_RRC_CIPHER_ACTIVE_IND_STRU;

/*****************************************************************************
 结构名    : MACITF_TRAF_MEAS_QUANT_CHOICE_STRU
 协议表格  : 10.3.7.71 Traffic volume measurement quantity
             10.3.7.74    Traffic volume reporting quantity
 ASN.1描述 : TrafficVolumeMeasQuantity 配置Average和Variance的上报间隔，CHOICE忽略。
             如果同时配置了Average和Variance，则间隔是一样的。
             TrafficVolumeReportingQuantity 表示上报什么内容。
 结构说明  : 业务量测量量，
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */
    PS_BOOL_ENUM_UINT8                  enRlcBufPayload;        /* 是否需要使用RlcBufPayload方式上报 */
    VOS_UINT16                          usAvgRlcBufPayload;     /* 单位ms,0表示不使用AvgRlcBufPayload方式上报，(20, 40, ..260, by steps of 20) */
    VOS_UINT16                          usVarRlcBufPayload;     /* 单位ms,0表示不使用VarRlcBufPayload方式上报，(20, 40, ..260, by steps of 20) */
}MACITF_TRAF_RPT_QUANT_STRU;

/*****************************************************************************
 结构名    : RRC_MAC_MEAS_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 : TrafficVolumeMeasurement
 结构说明  : 业务量测量
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /* 消息头  */   /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16            enMsgName;          /* 消息标识*/   /* _H2ASN_Skip */
    VOS_UINT16                              usOpId;             /* 操作标识*/

    VOS_UINT8                               aucReserve1[3];     /* 4字节对齐，保留 */
    VOS_UINT8                               ucMeasId;           /* INTEGER(1..16) */
    MACITF_MEAS_OBJ_LIST_STRU               stMeasObjList;      /* 需要监视TrCH的列表 */
    MACITF_TRAF_RPT_QUANT_STRU              stMeasQuant;
    VOS_UINT8                               aucReserve2[2];     /* 4字节对齐，保留 */
    MACITF_TRAF_MEAS_RPT_CRTR_CHOICE_STRU   stMeasRptCrtr;
}RRC_MAC_MEAS_CONFIG_REQ_STRU;


/*******************************************************************************
 结构名    : MAC_RRC_MEAS_CONFIG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC业务量测量配置响应
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头  */       /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息标识*/       /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* 操作标识*/

    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
    /* Traffic Volume Indicator 指示 当为TRUE时:4A事件且测量ID为4，
       BO大于门限值，可请求网侧由F_RB0态切换到D态，否则为FALSE.
       上述做法目的: UE需要通过"uplink data transmission"触发CU时,
       判断一下4a是否满足, 并告知网络, 这样网络能够直接在CU_CNF时分配足够的资源
       对EDCH测量时由于不通过CU来切换状态, 直接填写FALSE */
    PS_BOOL_ENUM_UINT8                  enTrVolumeInd;
    VOS_UINT8                           ucMeasId;           /* 测量标识 */
    MACITF_RSLT_ENUM_UINT32             enRslt;
}MAC_RRC_MEAS_CONFIG_CNF_STRU;

/*******************************************************************************
 结构名    : MAC_RRC_MEAS_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上报业务量测量结果
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头  */       /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息ID  */       /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;

    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucMeasId;           /* 测量标识 */
    MACITF_TRAF_MEAS_RSLT_CHOICE_STRU   stTrafMeasInd;

}MAC_RRC_MEAS_IND_STRU;


/*******************************************************************************
 结构名    : RRC_MAC_MEAS_REL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 释放业务量测量
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头  */       /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息ID  */       /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;

    VOS_UINT8                           ucMeasCnt;          /* 数量 */
    VOS_UINT8                           aucMeasId[PS_WUE_MAX_NO_OF_MEAS_NUM];
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
}RRC_MAC_MEAS_REL_REQ_STRU;

/*******************************************************************************
 结构名    : RRC_MAC_MEAS_REL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 释放业务量测量响应
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头  */       /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息ID  */       /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* 操作标识  */

    MACITF_RSLT_ENUM_UINT32             enRslt;
}MAC_RRC_MEAS_REL_CNF_STRU;

/*******************************************************************************
 结构名    : MAC_RRC_PCCH_DATA_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PCCH消息
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
    VOS_UINT32                          ulBitLen;           /* 以bit为单位的数据长度 */
    VOS_UINT8                           aucData[4];         /* 数据部分，与前面字节一起属于连续的消息内存空间 */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}MAC_RRC_PCCH_DATA_IND_STRU;


/*******************************************************************************
 结构名    : MAC_RRC_BCCH_DATA_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : BCCH(system information change indication)
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
    VOS_UINT32                          ulBitLen;           /* 以bit为单位的数据长度 */
    VOS_UINT8                           aucData[4];         /* 数据部分，与前面字节一起属于连续的消息内存空间 */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}MAC_RRC_BCCH_DATA_IND_STRU;


/*******************************************************************************
 结构名    : MAC_RRC_ACTIVE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC配置或复位或释放激活时间指示
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* 操作标识 */
    VOS_INT16                           sActTime;           /*[0,255],配置激活时间CFN,PS_NEG_ONE表示立即激活 */
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
}MAC_RRC_ACTIVE_IND_STRU;


/*******************************************************************************
 结构名    : MAC_RRC_STATUS_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RB0随机接入结果上报
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
    MACITF_STATUS_ENUM_UINT32           enStatus;

}MAC_RRC_STATUS_IND_STRU;


/*******************************************************************************
 结构名    : MAC_RRC_ERROR_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC发生异常，指示RRC释放
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
    MACITF_RRC_ERR_CODE_ENUM_UINT32     enErrCode;          /* 错误类型指示 */
}MAC_RRC_ERROR_IND_STRU;

/*******************************************************************************
 结构名    : RRC_MAC_HS_RESET_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RESET MAC HS实体
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* 操作标识 */
    VOS_INT16                           sActTime;           /*[0,255], CFN,PS_NEG_ONE表示立即激活 */

    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
}RRC_MAC_HS_RESET_REQ_STRU;


/*****************************************************************************
 结构名    : RRC_MAC_COMPRESS_MODE_TGPS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 某个 TGPS 信息
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usTGPSI;                        /* TGPS标识       */
    MACITF_TGPS_CFG_STATUS_ENUM_UINT16          enTGPSCfgStausFlag;             /* TGPS状态标志   */
    VOS_INT16                                   sTGCFN;                         /* 该TGPS的激活时间, [0,255],当TGPS状态不是CHANGED_ACTIVED, 激活时间配置为-1 */
    VOS_UINT16                                  usReserve1;
    VOS_UINT16                                  usTGPRC;                        /* TGPS包括的TGP个数，[0, 511]，0表示不限制 */
    VOS_UINT16                                  usTGPL1;                        /* TGP的持续时间，以帧为单位，[1,144] */
    VOS_UINT8                                   aucFrameTxSlots[PS_WUE_MAX_TGPL];   /* TGP中每帧能发送的时隙数 */
}RRC_MAC_TGPS_INFO_STRU;

/*****************************************************************************
 结构名    : RRC_MAC_COMPRESS_MODE_CFG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 压模信息
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16            enMsgName;                          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                              usOpId;                             /* 操作标识 */
    VOS_INT16                               sTgpsRecfgCfn;                      /* 上一次压模配置去激活时间,[0,255],-1表示没有上一次的压模配置，当前配置立即生效 */
    VOS_UINT16                              usTGPSCnt;                          /* TGPS个数 */
    RRC_MAC_TGPS_INFO_STRU                  astTGPSInfo[PS_WUE_MAX_TGPS_NUM];
}RRC_MAC_COMPRESS_MODE_CFG_REQ_STRU;

/* 消息RRC_MAC_COMPRESS_MODE_CFG_CNF_STRU的结构体 */
typedef MAC_RRC_C_CONFIG_CNF_STRU   RRC_MAC_COMPRESS_MODE_CFG_CNF_STRU;

/*****************************************************************************
 结构名    : RRC_MAC_COMPRESS_MODE_CFG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 压模信息
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16            enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                              usOpId;             /* 操作标识 */
    VOS_INT16                               sActTime;           /*[0,255],加密激活时间CFN,PS_NEG_ONE表示立即激活 */
    VOS_UINT16                              usTfcCnt;                                   /* UL TFC全集TFC个数 */
    VOS_UINT8                               aucTfcTxSlots[PS_WUE_MAX_UL_TFC_NUM];       /* 数组下标就是TFCI, 元素值为该TFC每帧发送至少需要的时隙数,[0,16],16表示无效值，RRC计算结果大于16，都配置成16 */
}RRC_MAC_TFC_SLOT_CFG_REQ_STRU;

/* 消息RRC_MAC_TFC_SLOT_CFG_CNF_STRU的结构体 */
typedef MAC_RRC_C_CONFIG_CNF_STRU   RRC_MAC_TFC_SLOT_CFG_CNF_STRU;

/*****************************************************************************
 结构名    : RRC_MAC_STOP_UL_TX_REQ_STRU
 协议表格  : 无
 ASN.1描述 :
 结构说明  : 为了精确控制上行停止发送的时间, 增加此消息. RRC在释放物理层前
             通过此消息通知MAC在激活时间到达时停止向RLC要数
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16            enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                              usOpId;             /* 操作标识 */
    VOS_INT16                               sActTime;           /*[0,255], 停止MAC要数激活时间CFN,PS_NEG_ONE表示立即激活 */
    VOS_UINT8                               aucReserve1[2];     /* 4字节对齐, 保留 */
}RRC_MAC_STOP_UL_TX_REQ_STRU;

/* 消息MAC_RRC_STOP_UL_TX_CNF的结构体 */
typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_STOP_UL_TX_CNF_STRU;

/*****************************************************************************
 结构名    : RRC_MAC_CONTINUE_UL_TX_REQ_STRU
 协议表格  : 无
 ASN.1描述 :
 结构说明  : 为了精确控制上行停止发送的时间, 增加此消息. RRC收到物理层的同步指示后,
             通过RRC_MAC_CONTINUE_UL_TX_REQ的消息通知MAC立即恢复向RLC要数
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16            enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                              usOpId;             /* 操作标识 */
}RRC_MAC_CONTINUE_UL_TX_REQ_STRU;

/* 消息MAC_RRC_CONTINUE_UL_TX_CNF的结构体 */
typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_CONTINUE_UL_TX_CNF_STRU;

/*****************************************************************************
 结构名    : RRC_MAC_TGPS_PRE_CHK_REQ_STRU
 协议表格  : 无
 ASN.1描述 :
 结构说明  : 压模激活以前，对压模参数的合法性检查
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16            enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                              usOpId;             /* 操作标识 */
    VOS_INT16                               sTgpsRecfgCfn;                      /* 上一次压模配置去激活时间,[0,255],-1表示没有上一次的压模配置，当前配置立即生效 */
    VOS_UINT8                               aucReserve1[1];
    VOS_UINT8                               ucTgpsCnt;                          /* 保存的所有压模序列的个数 */
    RRC_MAC_TGPS_INFO_STRU                  astTgpsInfo[PS_WUE_MAX_TGPS_NUM];
}RRC_MAC_TGPS_PRE_CHK_REQ_STRU;


/*******************************************************************************
 结构名    : MAC_RRC_TGPS_PRE_CHK_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息RRC_MAC_TGPS_PRE_CHK_REQ_STRU的响应消息
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* 操作标识 */
    MACITF_RSLT_ENUM_UINT32             enRslt;                                 /* 下发参数无效(不包括重叠)时，返回失败(配置中无激活的TGPS时，返回失败)，其他返回成功 */
    VOS_UINT8                           aucReserve1[2];
    VOS_UINT8                           ucOverLapCnt;                           /* 重叠的压模序列个数 */
    VOS_UINT8                           aucTgpsi[PS_WUE_MAX_TGPS_NUM - 1];      /* 重叠的压模标识，当两个序列重叠时，返回tgpsi较大的一个 */
}MAC_RRC_TGPS_PRE_CHK_CNF_STRU;

/*V3 R7_7C1 Start */

typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_EHS_CONFIG_CNF_STRU;
typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_EHS_RESET_CNF_STRU;
typedef RRC_MAC_HS_RESET_REQ_STRU   RRC_MAC_EHS_RESET_REQ_STRU;

typedef struct
{
   VOS_UINT8                            ucLochLabel;        /* 逻辑信道内部实现统一标识：[0,[0,34*2-1]] */
   VOS_UINT8                            ucLochId;           /* 逻辑信道ID：[1,15]，0表示无效,当PCCH，BCCH映射到HS-DSCH时，usLochId的值为1111 */
   VOS_UINT8                            ucEhsQueueId;       /*[0，8]，当usLoch值为1111时，存在没有Queue的情况，在实现上，将usHsQueueId的值设成8*/
   VOS_UINT8                            aucReserved[1];     /*四字节对齐*/
}MACITF_EHS_MAPPING_INFO_STRU;

typedef struct
{
    VOS_UINT8                           ucEhsQueueId;       /* [0,7] */
    VOS_UINT8                           ucEhsWinSize;       /* Integer(4, 6, 8, 12, 16, 24, 32,64,128) */
    VOS_UINT16                          usT1Len;            /* Integer(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 120, 140, 160, 200, 300, 400)ms */
    VOS_UINT16                          usTresetLen;        /* Integer  ms */
    VOS_UINT8                           aucReserve1[2];
}MACITF_EHS_QUEUE_INFO_STRU;

typedef struct
{
    MACITF_RNTI_CFG_ENUM_UINT8              enHrntiFlag;                        /* 标识当前H-RNTI配置状态*/

    MACITF_MAC_EHS_TSN_BIT_LEN_ENUM_UINT8   enTsnBitLen;                        /* DC+MIMO时, 配置14bits, 否则配置6bits */
    VOS_UINT8                               aucReserve1[1];

    VOS_UINT8                               ucMappingCount;                     /* 映射count,MACITF_RNTI_CFG_COMM_HRNTI当只配置MAC_C,MAC_EHS时，这里最多配置个数为2，SRB0或SRB0,SRB1 ;
                                                                                   CELL_PCH/URA_PCH也只配置MAC_C,MAC_EHS
                                                                                   当存在MAC_D时，这里配置的是所有RB的映射，如果DL E_CELLFACH则包含RB0,否则不包含 */
    MACITF_EHS_MAPPING_INFO_STRU            astMappingInfo[PS_WUE_MAX_LOCH_NUM];/* 队列和LOCH ID映射关系 */

    VOS_UINT8                               aucReserve2[3];

    VOS_UINT8                               ucMacEhsQueueCnt;                       /* [1,PS_WUE_MAX_QUEUE_NUM] */
    MACITF_EHS_QUEUE_INFO_STRU              astEhsQueueInfo[PS_WUE_MAX_QUEUE_NUM];  /* PS_WUE_MAX_QUEUE_NUM is defined in WUeSpec.h */
}MACITF_EHS_HS_DSCH_INFO_STRU;

typedef struct
{
   VOS_MSG_HEADER                                           /* _H2ASN_Skip */
   RRC_MAC_MSG_TYPE_ENUM_UINT16         enMsgName;          /*Msg type*/        /* _H2ASN_Skip */
   VOS_UINT16                           usOpId;             /*operation id*/

   VOS_INT16                            sActTime;           /*[0,255],CFN,PS_NEG_ONE:立即激活*/
   VOS_UINT8                            aucRsv[2];
   MACITF_EHS_HS_DSCH_INFO_STRU         stEhsInfo;          /**/
}RRC_MAC_EHS_CONFIG_REQ_STRU;


typedef struct
{
    VOS_UINT8                           ucTrchId;           /* [PS_WUE_MIN_TRCH_ID,PS_WUE_MAX_TRCH_ID] */
    MACITF_TTI_ENUM_UINT8               enTti;              /* 单位10ms,根据实际取值配置MAC */
    MACITF_CRC_SIZE_ENUM_UINT8          enCrcSize;          /* CRC bit长度: 0、8、12、16、24，TEST LOOP MODE2，TM RLC时用 */
    VOS_UINT8                           ucRlcSizeNum;
    VOS_UINT16                          astRlcSize[PS_WUE_MAX_TF_NUM];
    VOS_UINT8                           ucTfNum;            /*[0,PS_WUE_MAX_TF_NUM],该传输信道RLC SIZE的个数 */
    VOS_UINT8                           aucRsv[3];
    MACITF_TF_INFO_REDUCE_STRU          astTfs[PS_WUE_MAX_TF_NUM]; /* 每种RLC SIZE下的TF信息,数组下标对应一种RLC SIZE的索引 */
}MACITF_TRCH_INFO_REDUCE_STRU;

typedef struct
{
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucUlDchCnt;                     /* 0..PS_WUE_MAX_DCH_NUM - 1 */
    MACITF_TRCH_INFO_REDUCE_STRU        astUlDchInfo[PS_WUE_MAX_DCH_NUM];
}MACITF_UL_DCH_INFO_LIST_REDUCE_STRU;

typedef struct
{
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucDlDchCnt;                      /* DL DCH数 */
    MACITF_TRCH_INFO_REDUCE_STRU        astDlDchInfo[PS_WUE_MAX_DCH_NUM];  /* 每个DL DCH的信息 */
}MACITF_DL_DCH_INFO_LIST_REDUCE_STRU;


typedef struct
{
    MACITF_UL_DCH_INFO_LIST_REDUCE_STRU stUlDchInfoList;
    MACITF_DL_DCH_INFO_LIST_REDUCE_STRU stDlDchInfoList;
}MACITF_DCH_INFO_REDUCE_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* 操作标识 */

    VOS_INT16                           sActTime;           /*[0,255],加密激活时间CFN,PS_NEG_ONE表示立即激活 */
    VOS_INT8                            cMaxUeTxPwr;        /* [-50，33],上行链路最大发射功率= min(Maximum allowed UL TX Power=网侧配置的最大功率, PMAX =UE的最大功率规格),dbm */
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */

    VOS_UINT32                          bitOpTrchInfo       : 1;    /* 1:stTrchInfo存在，    0:不存在,在CELL_PCH/URA_PCH、CELL_FACH态配置MAC_D时，需要将bitOpTrchInfo设为0；在CELL_DCH状态下，如果上行专用传输信道只有E-DCH且下行专用物理信道只有F-DPCH时，也需要将bitOpTrchInfo设为0 */
    VOS_UINT32                          bitOpUlTrchTfcs     : 1;    /* 1:bitOpUlTrchTfcs存在，0:不存在,在CELL_PCH/URA_PCH、CELL_FACH态配置MAC_D时，需要将bitOpUlTrchTfcs设为0；在CELL_DCH状态下，如果上行专用传输信道只有E-DCH，也需要将bitOpUlTrchTfcs设为0 */
    VOS_UINT32                          bitSpare            : 30;

    MACITF_RB_MAPP_INFO_LIST_STRU       stRbMappInfoList;   /* RB映射相关参数 */

    MACITF_DCH_INFO_REDUCE_STRU         stTrchInfo;         /* 传输信道相关参数(TFS) */

    MACITF_UL_DCH_COMM_INFO_STRU        stUlTrchTfcs;       /* 上行DCH的TFC信息*/

}RRC_MAC_D_CONFIG_REDUCE_REQ_STRU;
/*========================*/            /* RRC_MAC_D_CONFIG_REDUCE_REQ_STRU end */


/*========================*/            /* RRC_MAC_C_CONFIG_REDUCE_REQ_STRU */
typedef struct
{
    MACITF_TRCH_TYPE_ENUM_UINT8         enTrchType;             /* FACH,PCH */
    PS_BOOL_ENUM_UINT8                  enCtchInd;              /* ctch_Indicator BOOLEAN */
    MACITF_TRCH_INFO_REDUCE_STRU        stDlCchInfo;            /* 每个TF的信息 */
}MACITF_DL_CCH_INFO_REDUCE_STRU;

typedef struct
{
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucDlCchCnt;                      /* FACH和PCH的信道个数之和 */
    MACITF_DL_CCH_INFO_REDUCE_STRU      astDlCchInfo[PS_WUE_MAX_FACH_PCH_NUM];  /* 每个FACH/PCH的信息 */
}MACITF_DL_CCH_INFO_LIST_REDUCE_STRU;

typedef struct
{
    VOS_UINT8                           ucCnt;                                  /* 码组合传输信道数 */
    VOS_UINT8                           aucReserve1[1];                         /* 4字节对齐，保留 */
    MACITF_DL_CCH_INFO_LIST_REDUCE_STRU stDlCchInfoList[PS_WUE_MAX_SCCPCH_CCTRCH_NUM];  /*  */
}MACITF_CCTRCH_INFO_REDUCE_STRU;

typedef struct
{
    MACITF_TRCH_INFO_REDUCE_STRU        stRachInfo;       /* RRC全配置 */
    MACITF_CCTRCH_INFO_REDUCE_STRU      stCctrchInfo;     /* RRC全配置 */
}MACITF_CCH_INFO_REDUCE_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* 操作标识 */

    VOS_UINT32                          bitTrchInfo         : 1;                /* 是否存在TRCH INFO */
    VOS_UINT32                          bitRachTfcs         : 1;                /* 是否存在tfcs */
    VOS_UINT32                          bitSpare            :30;
    VOS_INT16                           sActTime;           /*[0,255],加密激活时间CFN,PS_NEG_ONE表示立即激活 */

    MACITF_CCH_INFO_REDUCE_STRU         stTrchInfo;         /* 传输信道相关参数(TFS) */

    MACITF_RACH_COMM_INFO_STRU          stRachTfcs;         /* RACH的TFC信息*/

    MACITF_UE_ID_INFO_STRU              stUeIdInfo;         /* UE ID相关参数 */

    MACITF_RACH_ACCESS_INFO_STRU        stRachAcsInfo;      /* RACH 接入相关参数 */
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
}RRC_MAC_C_CONFIG_REDUCE_REQ_STRU;
/*========================*/            /* RRC_MAC_C_CONFIG_REDUCE_REQ_STRU end */

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* 操作标识 */
    MACITF_RSLT_ENUM_UINT32             enRslt;
}WTTF_MEM_TEST_CNF_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgID;            /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* 操作标识 */
}WTTF_MEM_TEST_REQ_STRU;
/* 精简结构结束 */

/* V3 R7_7C1 End */

/*****************************************************************************
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

#if 0                                                                           /*_H2ASN_Skip*/
enum MACITF_TRAF_MEAS_RPT_CRTR_TYPE_ENUM
{
    MACITF_TRAF_VOL_RPT_CRTR            = 0,                /* _H2ASN_MsgChoice MACITF_TRAF_VOL_RPT_CRTR_STRU */
    MACITF_PERIOD_RPT_CRTR              = 1,                /* _H2ASN_MsgChoice MACITF_PERIOD_RPT_CRTR_STRU */
    MACITF_NO_RPT                       = 2,                /* _H2ASN_MsgChoice PS_NULL_STRU */
    MACITF_TRAF_MEAS_RPT_CRTR_TYPE_BUTT
};
typedef VOS_UINT32  MACITF_TRAF_MEAS_RPT_CRTR_TYPE_ENUM_UINT32;

typedef struct
{
    MACITF_TRAF_MEAS_RPT_CRTR_TYPE_ENUM_UINT32  ulChoice;   /* _H2ASN_IeChoice_Export MACITF_TRAF_MEAS_RPT_CRTR_TYPE_ENUM_UINT32 */

    union                                                                       /* _H2ASN_Skip */
    {                                                                           /* _H2ASN_Skip */
        MACITF_TRAF_VOL_RPT_CRTR_STRU   stTrafVolRptCrtr;                       /* _H2ASN_Skip */
        MACITF_PERIOD_RPT_CRTR_STRU     stPeriodRptCrtr;                        /* _H2ASN_Skip */
        PS_NULL_STRU                    stNoRpt;
        /******************************************************************************************************
            _H2ASN_IeChoice_When        MACITF_TRAF_MEAS_RPT_CRTR_TYPE_ENUM_UINT32
        ******************************************************************************************************/
    }u;                                                                         /* _H2ASN_Skip */
}MACITF_TRAF_MEAS_RPT_CRTR_STRU;
#endif                                                                          /*_H2ASN_Skip*/

/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgID;    /*_H2ASN_MsgChoice_Export RRC_MAC_MSG_TYPE_ENUM_UINT16*/

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          RRC_MAC_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}RRC_MAC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    RRC_MAC_MSG_DATA                    stMsgData;
}RrcMacInterface_MSG;

/* V3 R7_7C1 Start */
enum MACITF_TRCH_ENCODE_TYPE_ENUM
{
    MACITF_TRCH_ENCODE_TYPE_CONV_HALF_RATE             = 0,
    MACITF_TRCH_ENCODE_TYPE_CONV_TRIPLE_RATE           = 1,
    MACITF_TRCH_ENCODE_TYPE_TURBO_CODING               = 2,
    MACITF_TRCH_ENCODE_TYPE_BUTT
};

typedef VOS_UINT16 MACITF_TRCH_ENCODE_TYPE_ENUM_UINT16;

typedef struct
{
    VOS_UINT8   ucBcRef;                                /*取值 0~15 */
    VOS_UINT8   ucBdRef;                                /*取值 0~15 */
    VOS_UINT8   ucTfcRefId;                             /*取值 0~3 */
    VOS_UINT8   aucReserve1[1];

}RRC_MAC_TFC_SIGNAL_STRU;

typedef struct
{
    VOS_UINT8   ucTfcRefId;
    VOS_UINT8   aucReserve1[3];
}RRC_MAC_TFC_COMPUTED_STRU;


typedef struct
{

    #define MACITF_SIGNAL_GAIN_FACTOR_CHOSEN              0                                       /*高层指定的增益因子计算方式*/
    #define MACITF_COMPUTED_GAIN_FACTOR_CHOSEN            1                                       /*物理层计算的增益因子计算方式*/

    VOS_UINT32                              ulChoice;
    union
    {
        RRC_MAC_TFC_SIGNAL_STRU             stTfcSignalInfo;
        RRC_MAC_TFC_COMPUTED_STRU           stTfcComputedInfo;
    }u;

}RRC_MAC_BCBD_TFC_STRU;


typedef struct
{
    VOS_UINT8                                    ucTrchId;           /* [PS_WUE_MIN_TRCH_ID,PS_WUE_MAX_TRCH_ID] */
    VOS_UINT8                                    aucReserved[3];     /* 四字节对齐 */
    VOS_UINT16                                   usRM;               /* 0..256 */
    MACITF_TRCH_ENCODE_TYPE_ENUM_UINT16          enCodeType;         /* 0..2 */


}RRC_MAC_BCBDREF_TRCH_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* 操作标识 */

    VOS_INT16                           sActTime;           /*[0,255],-1表示立即激活 */
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */

    VOS_UINT8                           ucTrchCnt;         /* 0..PS_WUE_MAX_DCH_NUM  */
    RRC_MAC_BCBDREF_TRCH_STRU           astTrchInfo[PS_WUE_MAX_DCH_NUM];


    VOS_UINT8                           aucReserve2[2];     /* 4字节对齐，保留 */
    VOS_UINT16                          usTfcCnt;          /* 0..PS_WUE_MAX_UL_TFC_NUM  */
    RRC_MAC_BCBD_TFC_STRU               astBcBdTfcInfo[PS_WUE_MAX_UL_TFC_NUM];
}RRC_MAC_BCBD_CALCULATE_REQ_STRU;

typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_BCBD_CALCULATE_CNF_STRU;


/* V3 R7_7C1 BHS */
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* 操作标识 */

    VOS_INT16                           sActTime;           /*[0,255],加密激活时间CFN,PS_NEG_ONE表示立即激活 */
    VOS_UINT8                           ucBhs;              /* Bhs，[5, 6, 8, 9, 12, 15, 19, 24, 30];*/
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */

}RRC_MAC_BHS_CALCULATE_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* 操作标识 */
    MACITF_CIPHER_STATUS_ENUM_UINT16    enCipherSta;        /* 同频硬切换或者异系统切换回退要求MAC的加密处理: 0: 通知MAC备份cipher相关参数 1:通知MAC重新计算加密配置 */
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */

}RRC_MAC_CIPHER_RESERVE_REQ_STRU;


/* DL E CELL PCH(有专用H-RNTI)状态下, MAC接收到数据后，通知RRC */
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16         enMsgName;         /* Msg type */        /* _H2ASN_Skip */
    VOS_UINT16                           usOpId;            /* 操作标识 */
    VOS_UINT8                            aucRsv2[4];        /* 扩展 */
}MAC_RRC_EHS_RX_DATA_IND_STRU;

typedef MAC_RRC_CIPHER_CONFIG_CNF_STRU MAC_RRC_CIPHER_RESERVE_CNF_STRU;

typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_BHS_CALCULATE_CNF_STRU;
/* V3 R7_7C1 End */

/* 随机接入ASC参数配置指示 */
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* Msg type */      /* _H2ASN_Skip */

    /* ucAscCnt = ucNumAsc+1,ucNumAsc的范围0..7，ASC的实际取值i:0 <= i <= NumASC <= 7,在IDEL、PCH态，RRC配置的ucAscCnt=0 */
    VOS_UINT8                           ucAscCnt;
    VOS_UINT8                           ucReserve;

    /* 当UE已经配置URNTI时使用，数组下标是ASC值，数组元素值为ASC对应的Pi值 */
    VOS_UINT16                          ausAscPi[PS_WUE_MAX_ASC_NUM];
}RRC_MAC_ASC_CONFIG_STRU;

/*****************************************************************************
 枚举名    : MACITF_BOOL_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 接口中的有效性标识
*****************************************************************************/

enum MACITF_BOOL_ENUM
{
    MACITF_INVALID                      = 0,    /*用于对接口中的valid标志置位，若有效则使用1*/
    MACITF_VALID                        = 1,    /*用于对接口中的valid标志置位，若无效则使用0*/

    MACITF_BUTT

};
typedef VOS_UINT16  MACITF_BOOL_ENUM_UINT16;

/*****************************************************************************
 结 构 名  : RRC_MAC_AS_ACTIVE_DSDS_STATUS_IND_STRU
 结构说明  : RRC_MAC_AS_ACTIVE_DSDS_STATUS_IND_STRU消息结构
 修改历史  :
  1.日  期   : 2015年04月24日
    作  者   :
    修改内容 : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_MAC_MSG_TYPE_ENUM_UINT16            enMsgName;                          /* 原语类型 */ /*_H2ASN_Skip*/
    MACITF_BOOL_ENUM_UINT16                 enRfShareFlag;                      /* _VALID:共享RF(DSDS双卡模式)，_INVALID:独占RF(非DSDS双卡模式) */
}RRC_MAC_AS_ACTIVE_DSDS_STATUS_IND_STRU;

/*****************************************************************************
  10 函数声明
*****************************************************************************/
/*MAC维护CFN,提供接口函数给RRC*/
extern VOS_VOID WTTF_MAC_GetCurrentCfn(VOS_UINT8 *pucCfn);

/*接口函数返回值PS_SUCC表明该CN DOMAIN对应的CountC有效;PS_FAIL表明该CN DOMAIN对应的CountC无效*/
extern VOS_UINT32 WTTF_MAC_GetCurrentCountC(WUE_CN_DOMAIN_TYPE_ENUM_UINT8 enCnDomain,VOS_UINT32 *pulCountC);

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

#endif /* end of RrcMacInterface.h */


