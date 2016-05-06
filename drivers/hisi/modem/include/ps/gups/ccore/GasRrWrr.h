/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : GasInternal.h
  Author      : 张燕忠(47368)
  Version     : V200R001
  Date        : 2005-09-09
  Description : 该头文件定义了GAS 内部模块之间的消息数据结构
  History     :
  1. Date:2005-09-09
     Author: 张燕忠(47368)
     Modification:Create
  2. Date:2005-09-28
     Author: 赵见磊(41416)
     Modification:增加WRRC与RR之间的接口
  3. Date:2005-09-28
     Author: 张红军(49106)
     Modification: 将PACK1调整为PACK4
  4. Date:2006-08-09
     Author: j60010247
     Modification:根据问题单A32D03479，在PC机上实现时将#pragma pack(0)和#pragma pack()加编译开关
  5. Date:2010-04-29
    Author: d00132956
    Modification:根据问题单AT2D18757，添加疑系统重选时的重选类型,决定是否判断等效PLMN
************************************************************************/

#ifndef _GAS_RR_WRR_H_
#define _GAS_RR_WRR_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "PsTypeDef.h"
#include  "GUCommInterface.h"

#pragma pack(4)

extern VOS_UINT32 g_ulWasHoInfoR3Stub ;


/*====================== RR-WRRC之间消息的宏定义 ============================*/
enum RR_WRRC_MSG_TYPE_ENUM
{
    /* 新增GToW切换原语宏定义 */
    RRWRRC_CELL_CHANGE_REQ                                  = 0x9901,       /* _H2ASN_MsgChoice RRWRRC_CELL_CHANGE_REQ_ST */
    RRWRRC_CELL_CHANGE_CNF                                  = 0x9902,       /* _H2ASN_MsgChoice RRWRRC_CELL_CHANGE_CNF_ST */
    RRWRRC_HANDOVER_REQ                                     = 0x9903,       /* _H2ASN_MsgChoice RRWRRC_HANDOVER_REQ_ST */
    RRWRRC_HANDOVER_CNF                                     = 0x9904,       /* _H2ASN_MsgChoice RRWRRC_HANDOVER_CNF_ST */
    RRWRRC_CELL_RESEL_REQ                                   = 0x9905,       /* _H2ASN_MsgChoice RRWRRC_CELL_RESEL_REQ_ST */
    RRWRRC_CELL_RESEL_CNF                                   = 0x9906,       /* _H2ASN_MsgChoice RRWRRC_CELL_RESEL_CNF_ST */

    /* 新增WToG切换原语宏定义 */
    WRRCRR_CELL_CHANGE_REQ                                  = 0x9907,       /* _H2ASN_MsgChoice WRRCRR_CELL_CHANGE_REQ_ST */
    WRRCRR_CELL_CHANGE_CNF                                  = 0x9908,       /* _H2ASN_MsgChoice WRRCRR_CELL_CHANGE_CNF_ST */
    WRRCRR_CELL_CHANGE_TIMER_EXPIRED_REQ                    = 0x9909,       /* _H2ASN_MsgChoice WRRCRR_CELL_CHANGE_TIMER_EXPIRED_REQ_ST */
    WRRCRR_CELL_CHANGE_TIMER_EXPIRED_CNF                    = 0x9910,       /* _H2ASN_MsgChoice WRRCRR_CELL_CHANGE_TIMER_EXPIRED_CNF_ST */
    WRRCRR_HANDOVER_REQ                                     = 0x9911,       /* _H2ASN_MsgChoice WRRCRR_HANDOVER_REQ_ST */
    WRRCRR_HANDOVER_CNF                                     = 0x9912,       /* _H2ASN_MsgChoice WRRCRR_HANDOVER_CNF_ST */
    WRRCRR_CELL_RESEL_REQ                                   = 0x9913,       /* _H2ASN_MsgChoice WRRCRR_CELL_RESEL_REQ_ST */
    WRRCRR_CELL_RESEL_CNF                                   = 0x9914,       /* _H2ASN_MsgChoice WRRCRR_CELL_RESEL_CNF_ST */
    RRWRRC_CELL_CHANGE_TIMER_EXPIRED_REQ                    = 0x9915,       /* _H2ASN_MsgChoice RRWRRC_CELL_CHANGE_TIMER_EXPIRED_REQ_ST */
    RRWRRC_CELL_CHANGE_TIMER_EXPIRED_CNF                    = 0x9916,       /* _H2ASN_MsgChoice RRWRRC_CELL_CHANGE_TIMER_EXPIRED_CNF_ST */
    WRRCRR_CELL_RESEL_TIMER_EXPIRED_REQ                     = 0x9917,       /* _H2ASN_MsgChoice WRRCRR_CELL_RESEL_TIMER_EXPIRED_REQ_ST */
    WRRCRR_CELL_RESEL_TIMER_EXPIRED_CNF                     = 0x9918,       /* _H2ASN_MsgChoice WRRCRR_CELL_RESEL_TIMER_EXPIRED_CNF_ST */

    WRRCRR_PLMN_SEARCH_REQ                                  = 0x9919,       /* _H2ASN_MsgChoice WRRCRR_PLMN_SEARCH_REQ_ST */
    WRRCRR_PLMN_SEARCH_CNF                                  = 0x9920,       /* _H2ASN_MsgChoice WRRCRR_PLMN_SEARCH_CNF_ST */
    WRRCRR_PLMN_SEARCH_STOP_REQ                             = 0x9921,       /* _H2ASN_MsgChoice WRRCRR_PLMN_SEARCH_STOP_REQ_ST */
    WRRCRR_PLMN_SEARCH_STOP_CNF                             = 0x9922,       /* _H2ASN_MsgChoice WRRCRR_PLMN_SEARCH_STOP_CNF_ST */

    /* 获取inter rat info 的定义 */
    RRWRRC_INTER_RAT_HANDOVER_INFO_REQ      = 0x9923,       /* _H2ASN_MsgChoice RRWRRC_INTER_RAT_HANDOVER_INFO_REQ_ST */
    RRWRRC_INTER_RAT_HANDOVER_INFO_CNF      = 0x9924,       /* _H2ASN_MsgChoice RRWRRC_INTER_RAT_HANDOVER_INFO_CNF_ST */

    RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_REQ                 = 0x9925,         /* _H2ASN_MsgChoice RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_REQ_ST */
    RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_CNF                 = 0x9926,         /* _H2ASN_MsgChoice RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_CNF_ST */

    RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_TIMER_EXPIRED_REQ   = 0x9927,         /*_H2ASN_MsgChoice RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_TIMER_EXPIRED_REQ_ST */
    RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_TIMER_EXPIRED_CNF   = 0x9928,         /*_H2ASN_MsgChoice RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_TIMER_EXPIRED_CNF_ST */

    WRRCRR_CELL_SEL_REDIRECTION_REQ                       = 0x9929,         /* _H2ASN_MsgChoice WRRCRR_CELL_SEL_REDIRECTION_REQ_ST */
    WRRCRR_CELL_SEL_REDIRECTION_CNF                       = 0x992A,         /* _H2ASN_MsgChoice WRRCRR_CELL_SEL_REDIRECTION_CNF_ST */

    WRRCRR_CELL_SEL_REDIRECTION_ABORT_REQ                 = 0x992B,         /*_H2ASN_MsgChoice WRRCRR_CELL_SEL_REDIRECTION_ABORT_REQ_ST */
    WRRCRR_CELL_SEL_REDIRECTION_ABORT_CNF                 = 0x992C,         /*_H2ASN_MsgChoice WRRCRR_CELL_SEL_REDIRECTION_ABORT_CNF_ST */

    RRWRRC_CLASSMARK_CHANGE_IND                           = 0x992D,         /*_H2ASN_MsgChoice RRWRRC_CLASSMARK_CHANGE_IND_ST */

    RRWRRC_CELL_RESEL_STOP_REQ                              = 0x992E,       /*_H2ASN_MsgChoice RRWRRC_CELL_RESEL_STOP_REQ_ST */
    RRWRRC_CELL_RESEL_STOP_CNF                              = 0x992F,       /*_H2ASN_MsgChoice RRWRRC_CELL_RESEL_STOP_CNF_ST */

    WRRCRR_INTERRAT_PLMN_SEARCH_REQ                         = 0x9930,       /*_H2ASN_MsgChoice WRRCRR_INTERRAT_PLMN_SEARCH_REQ_ST */
    WRRCRR_INTERRAT_PLMN_SEARCH_CNF                         = 0x9931,       /*_H2ASN_MsgChoice WRRCRR_INTERRAT_PLMN_SEARCH_CNF_ST */
    WRRCRR_INTERRAT_PLMN_SEARCH_IND                         = 0x9951,       /*_H2ASN_MsgChoice WRRCRR_INTERRAT_PLMN_SEARCH_IND_ST */

    WRRCRR_INTERRAT_PLMN_SEARCH_STOP_REQ                    = 0x9932,       /*_H2ASN_MsgChoice WRRCRR_INTERRAT_PLMN_SEARCH_STOP_REQ_ST */
    WRRCRR_INTERRAT_PLMN_SEARCH_STOP_CNF                    = 0x9933,       /*_H2ASN_MsgChoice WRRCRR_INTERRAT_PLMN_SEARCH_STOP_CNF_ST */
    WRRCRR_INTERRAT_PLMN_SEARCH_SUSPEND_REQ                 = 0x9934,       /*_H2ASN_MsgChoice WRRCRR_INTERRAT_PLMN_SEARCH_SUSPEND_REQ_ST */
    WRRCRR_INTERRAT_PLMN_SEARCH_SUSPEND_CNF                 = 0x9935,       /*_H2ASN_MsgChoice WRRCRR_INTERRAT_PLMN_SEARCH_SUSPEND_CNF_ST */
    WRRCRR_INTERRAT_PLMN_SEARCH_RESUME_REQ                  = 0x9936,       /*_H2ASN_MsgChoice WRRCRR_INTERRAT_PLMN_SEARCH_RESUME_REQ_ST */
    WRRCRR_INTERRAT_PLMN_SEARCH_RESUME_CNF                  = 0x9937,       /*_H2ASN_MsgChoice WRRCRR_INTERRAT_PLMN_SEARCH_RESUME_CNF_ST */
    WRRCRR_INTER_RAT_HANDOVER_INFO_REQ                      = 0x9938,       /*_H2ASN_MsgChoice WRRCRR_INTER_RAT_HANDOVER_INFO_REQ_ST */
    WRRCRR_INTER_RAT_HANDOVER_INFO_CNF                      = 0x9939,       /*_H2ASN_MsgChoice WRRCRR_INTER_RAT_HANDOVER_INFO_CNF_ST */

    RRWRRC_INTERRAT_PLMN_SEARCH_REQ                       = 0x9942,       /*_H2ASN_MsgChoice RRWRRC_INTERRAT_PLMN_SEARCH_REQ_ST */
    RRWRRC_INTERRAT_PLMN_SEARCH_CNF                       = 0x9943,       /*_H2ASN_MsgChoice RRWRRC_INTERRAT_PLMN_SEARCH_CNF_ST */
    RRWRRC_INTERRAT_PLMN_SEARCH_IND                       = 0x9952,       /*_H2ASN_MsgChoice RRWRRC_INTERRAT_PLMN_SEARCH_IND_ST */

    RRWRRC_INTERRAT_PLMN_SEARCH_STOP_REQ                  = 0x9944,       /*_H2ASN_MsgChoice RRWRRC_INTERRAT_PLMN_SEARCH_STOP_REQ_ST */
    RRWRRC_INTERRAT_PLMN_SEARCH_STOP_CNF                  = 0x9945,       /*_H2ASN_MsgChoice RRWRRC_INTERRAT_PLMN_SEARCH_STOP_CNF_ST */
    RRWRRC_INTERRAT_PLMN_SEARCH_SUSPEND_REQ               = 0X9946,       /*_H2ASN_MsgChoice RRWRRC_INTERRAT_PLMN_SEARCH_SUSPEND_REQ_ST */
    RRWRRC_INTERRAT_PLMN_SEARCH_SUSPEND_CNF               = 0X9947,       /*_H2ASN_MsgChoice RRWRRC_INTERRAT_PLMN_SEARCH_SUSPEND_CNF_ST */
    RRWRRC_INTERRAT_PLMN_SEARCH_RESUME_REQ                = 0X9948,       /*_H2ASN_MsgChoice RRWRRC_INTERRAT_PLMN_SEARCH_RESUME_REQ_ST */
    RRWRRC_INTERRAT_PLMN_SEARCH_RESUME_CNF                = 0X9949,       /*_H2ASN_MsgChoice RRWRRC_INTERRAT_PLMN_SEARCH_RESUME_CNF_ST */

    RRWRRC_SLAVE_MEAS_REQ                                 = 0x9953,       /*_H2ASN_MsgChoice RRWRRC_SLAVE_MEAS_REQ_STRU */
    RRWRRC_SLAVE_MEAS_CNF                                 = 0x9954,       /*_H2ASN_MsgChoice RRWRRC_SLAVE_MEAS_CNF_STRU */
    RRWRRC_SLAVE_MEAS_IND                                 = 0x9955,       /*_H2ASN_MsgChoice RRWRRC_SLAVE_MEAS_IND_STRU */

    WRRCRR_SLAVE_MEAS_REQ                                 = 0x9960,       /*_H2ASN_MsgChoice WRRCRR_SLAVE_MEAS_REQ_STRU */
    WRRCRR_SLAVE_MEAS_CNF                                 = 0x9961,       /*_H2ASN_MsgChoice WRRCRR_SLAVE_MEAS_CNF_STRU */
    WRRCRR_SLAVE_MEAS_IND                                 = 0x9962,       /*_H2ASN_MsgChoice WRRCRR_SLAVE_MEAS_IND_STRU */

    /* W -> G  Gsm Cell Bsic Verify  */
    WRRCRR_BSIC_VERIFIED_REQ                              = 0x9970,       /* _H2ASN_MsgChoice WRRCRR_BSIC_VERIFIED_REQ_STRU */
    WRRCRR_BSIC_VERIFIED_CNF                              = 0x9971,       /* _H2ASN_MsgChoice WRRCRR_BSIC_VERIFIED_CNF_STRU */
    WRRCRR_BSIC_VERIFIED_IND                              = 0x9972,       /* _H2ASN_MsgChoice WRRCRR_BSIC_VERIFIED_IND_STRU */

    /* W -> G  rel all  */
    WRRCRR_RELEASE_ALL_REQ                                = 0x9975,       /* _H2ASN_MsgChoice WRRCRR_RELEASE_ALL_REQ_STRU */
    WRRCRR_RELEASE_ALL_CNF                                = 0x9976,       /* _H2ASN_MsgChoice WRRCRR_RELEASE_ALL_CNF_STRU */

    RRWRRC_HANDOVER_STOP_REQ                              = 0x9977,       /* _H2ASN_MsgChoice RRWRRC_HANDOVER_STOP_REQ_STRU */
    RRWRRC_HANDOVER_STOP_CNF                              = 0x9978,       /* _H2ASN_MsgChoice RRWRRC_HANDOVER_STOP_CNF_STRU */
    WRRCRR_HANDOVER_STOP_REQ                              = 0x9979,       /* _H2ASN_MsgChoice WRRCRR_HANDOVER_STOP_REQ_STRU */  
    WRRCRR_HANDOVER_STOP_CNF                              = 0x997A,       /* _H2ASN_MsgChoice WRRCRR_HANDOVER_STOP_CNF_STRU */  
    
    RR_WRRC_MSG_TYPE_BUTT
};
typedef VOS_UINT16 RR_WRRC_MSG_TYPE_ENUM_UINT16;

/*================== RR 模块与WRR模块之间的消息结构 ==========================*/

/*****************************************************************************
 消息名称  : RRWRRC_CELL_CHANGE_REQ
 功能描述  : RR接收到网络发送的小区变更命令消息，通过此原语指示WRRC进行小区变更
 修改历史  :
  1.日    期   : 2005年09月09日
    作    者   : Zhangyanzhong(47368)
    修改内容   : 新生成结构
*****************************************************************************/
#define BANDWIDTH_EXIST       1
#define BANDWIDTH_NOEXIST     0
/* GERAN SI的最大个数 */
#define WRRC_RR_MAX_GERAN_SI_CNT                (8)

/* 每个SI内容的最大长度 */
#define WRRC_RR_MAX_GERAN_SI_LEN                (23)

#define WRRC_RR_MAX_FORBLA_NUM                  (32)

/* W和G之间搜网透传消息最大长度 */
#define RRWRRC_RR_PHY_MAX_MSG_SIZE              (80) /* 通过WAS透传的GAS与物理层之间消息的最大长度 */

#define WRRCRR_RRC_PHY_MAX_MSG_SIZE             (230)/* 通过GAS透传的WRRC与物理层之间消息的最大长度 */

#define RRWRR_INVALID_RXLEV                     (0X00FF)

/* W和G之间NET SCAN搜网小区最大个数 */
#define WRRC_RR_MAX_NET_SCAN_CELL_NUM            (20)

/* W测量支持的最大频点个数 */
#define WRRC_RR_MAX_UTRAN_PHY_MAX_SUPPORT_CARRIER_NUM  (3)

/* UTRAN 单个频点支持小区最大数目 */
#define WRRC_RR_MAX_UTRAN_CELL_PER_FREQ_NUM            (32)

/* W测G的小区最大数目 */
#define WRRC_RR_MAX_SLAVE_GSM_CELL_NUM                 (64)

/* G下上报的最大的BSIC小区个数 */
#define WRRC_RR_MAX_SLAVE_GSM_BSIC_RPT_CELL_NUM        (8)

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT16                          usUarfcn;           /* UTRAN绝对无线载频号*/
    VOS_UINT8                           ucDiversity;        /* 1表示W小区使用Diversity, 0 表示没有使用Diversity */
    VOS_UINT8                           ucBandwidthFlag;    /* 带宽信息存在是否标识 */
    VOS_UINT8                           ucBandwidth;        /*  W小区信道带宽 */
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */
    VOS_UINT16                          usScramblingCode;   /* W小区主扰码 */

    /* 专有优先级信息, 0: 表示不存在，1 表示存在*/
    GURRC_VALID_FLAG_ENUM_UINT8                             enDPriInfoPresent;
    VOS_UINT8                                               ucResv[3];
    GURRC_DEDICATED_PRI_INFO_STRU                           stDPriInfo;
}RRWRRC_CELL_CHANGE_REQ_ST;

/*****************************************************************************
 消息名称  : RRWRRC_CELL_CHANGE_CNF
 功能描述  : 对消息的RRWRRC_CELL_CHANGE_CNF 的回复
 修改历史  :
  1.日    期   : 2005年09月09日
    作    者   : Zhangyanzhong(47368)
    修改内容   : 新生成结构
  2.日    期   : 2010年09月11日
    作    者   : Yaoqinbo(00142674)
    修改内容   : 问题单DTS2010090602491，增加小区重选不允许接入枚举和定时器长度
*****************************************************************************/
#define WRRC_RR_CELL_RESEL_ACCESS_NOT_PERMIT_TIMER_LEN          100  /*100s*/

typedef enum
{
    EN_SUCCESS    = 0,                                          /* 切换成功                         */
    EN_FAILURE,                                                 /* 切换失败                         */
    EN_MESSAGE_INVALID,                                         /* 接收的消息无效                   */
    EN_PROTOCOL_ERROR,                                          /* 消息协议错                       */
    EN_UNSUPORTED_CONFIGURATION,                                /* 消息中包含不支持的配置           */
    EN_PHY_CHANNEL_FAILURE,                                     /* 物理链路失败                     */
    EN_CELL_REG_REJED_FAIL,                                     /* 重选小区在异系统下注册失败       */

    /* 以下原因值用于重选时 */
    EN_CELL_RESEL_FAIL_REASON_CELL_BAR,                         /* 小区被Bar                        */
    EN_CELL_RESEL_FAIL_REASON_PLMN_CHECK_FAIL            ,      /* PLMN判断失败                     */
    EN_CELL_RESEL_FAIL_REASON_NOT_SUITABLE_S_CRITERION   ,      /* 不满足S准则                      */
    EN_CELL_RESEL_FAIL_REASON_OTHERS                     ,      /* 其他原因                         */

    EN_CELL_CHANGE_RRC_CONN_REJ                          ,      /* RRC连接被拒 */
    EN_CELL_RESEL_FAIL_REASON_ACCESS_NOT_PERMIT          ,      /* 接入等级不允许                   */

    
    EN_CELL_RESEL_FAIL_REASON_NON_NCELL_NOT_AVAILABLE    ,      /* 非邻区小区不可用, GAS 内部转换使用, WRR 不使用该值 */

    EN_CELL_RESEL_FAIL_REASON_S_OR_C1_CHECK_FAIL         ,     /* GW之间重选不满足W的S准则或者不满足G的C1准则，用于防止乒乓重选  */
    
    EN_CELL_RESEL_FAIL_REASON_BUTT
}RRC_RR_CNF_ENUM;
typedef VOS_UINT32     RRC_RR_CNF_ENUM_UINT32;

typedef enum
{
    EN_RRC_RR_RESEL_NORMAL    = 0,                  /* W2G正常重选，需要GAS判断等效plmn列表以及forbid la信息*/
    EN_RRC_RR_RESEL_ANYCELL_CAMP,                   /* W下anycell驻留，不需要GAS判断等效plmn列表以及forbid la信息*/
    EN_RRC_RR_RESEL_BUTT
}RRC_RR_RESEL_TYPE_ENUM;
typedef VOS_UINT32     RRC_RR_RESEL_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RRC_RR_MEAS_CMD_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : GU之间MEAS 命令
*****************************************************************************/
enum RRC_RR_MEAS_CMD_ENUM
{
    EN_RRC_RR_MEAS_CMD_RELEASE                             = 0,
    EN_RRC_RR_MEAS_CMD_SETUP                                  ,

    EN_RRC_RR_MEAS_CMD_BUTT
};
typedef VOS_UINT8 RRC_RR_MEAS_CMD_ENUM_UINT8;


/*****************************************************************************
 枚举名    : RRC_RR_MEAS_GAS_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : GAS主模测量时将GAS目前的状态带给WRRC;
*****************************************************************************/
enum RRC_RR_MEAS_GAS_STATUS_ENUM
{
    EN_RRC_RR_MEAS_GAS_STATUS_IDLE                           = 0,               /* IDLE态 */
    EN_RRC_RR_MEAS_GAS_STATUS_CONNECT                           ,               /* CONNECT态 */

    EN_RRC_RR_MEAS_GAS_STATUS_BUTT
};
typedef VOS_UINT8 RRC_RR_MEAS_GAS_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : RRC_RR_WAS_STATUS_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  : WAS的协议状态
*****************************************************************************/
enum RRC_RR_WAS_STATUS_ENUM
{
    EN_RRC_RR_WAS_STATUS_IDLE                             = 0,                  /* _H2ASN_MsgChoice RRC_RR_DRX_BSIC_TIMER_PARA_STRU */
    EN_RRC_RR_WAS_STATUS_URA_PCH                             ,                  /* _H2ASN_MsgChoice RRC_RR_DRX_BSIC_TIMER_PARA_STRU */
    EN_RRC_RR_WAS_STATUS_CELL_PCH                            ,                  /* _H2ASN_MsgChoice RRC_RR_DRX_BSIC_TIMER_PARA_STRU */
    EN_RRC_RR_WAS_STATUS_FACH                                ,                  /* _H2ASN_MsgChoice RRC_RR_FACH_BSIC_TIMER_PARA_STRU */
    EN_RRC_RR_WAS_STATUS_DCH                                 ,                  /* _H2ASN_MsgChoice RRC_RR_DCH_BSIC_TIMER_PARA_STRU */

    EN_RRC_RR_WAS_STATUS_BUTT
};
typedef VOS_UINT8 RRC_RR_WAS_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : RRC_RR_REL_REASON_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : GU之间REL ALL命令的释放原因值
*****************************************************************************/
enum RRC_RR_REL_REASON_ENUM
{
    EN_RRC_RR_REL_REASON_SYSHO                             = 0,
    EN_RRC_RR_REL_REASON_OTHER                                  ,

    EN_RRC_RR_REL_REASON_BUTT
};
typedef VOS_UINT8 RRC_RR_REL_REASON_ENUM_UINT8;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */
    RRC_RR_CNF_ENUM_UINT32              enResult;        /* 切换结果 */
}RRWRRC_CELL_CHANGE_CNF_ST;


/*****************************************************************************
 消息名称  : WRRCRR_CELL_CHANGE_REQ
 功能描述  : WRRC接收到网络发送的小区变更命令消息，通过此原语指示RR进行小区变更
 修改历史  :
  1.日    期   : 2005年09月28日
    作    者   : z41416
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNCC;
    VOS_UINT8                           ucBCC;
}RRC_BSIC_INFO_ST;

typedef struct
{
    VOS_UINT32                                  ulCnt;            /* 指示数组长度1-23*//* 有效值为1~23 */
    VOS_UINT8                                   aucGeranSysInfoBlock[WRRC_RR_MAX_GERAN_SI_LEN];
    VOS_UINT8                                   aucReserved[1];
}RRC_GSM_GREAN_SYS_INFO_ST;

typedef struct
{
    VOS_UINT8                                   aucReserved[2];
    RRC_GSM_GERAN_SYS_INFO_ENUM_UINT8           enGeranInfoInd;     /* ucGeranSysInfoCnt为0时，此值无效 */
    VOS_UINT8                                   ucGeranSysInfoCnt;                     /* 有效值为 0~ 8 */
    RRC_GSM_GREAN_SYS_INFO_ST                   stGeranSysInfor[WRRC_RR_MAX_GERAN_SI_CNT];
}RRC_CELL_CHANGE_GSM_CELL_SYS_INFO_BLOCK_ST;

typedef struct
{
    RRC_BSIC_INFO_ST                    stBsicInfo;

    VOS_INT16                           sRxlev;              /* G小区信号电平，单位是dBm,没有测到信号电平时赋值为RRWRR_INVALID_RXLEV */

    /*网络下发cellchangefromutran给WAS时，WAS查一下维护的G邻区列表，如果频点、BCC、NCC与网络下发的一致，则ulSyncFlag值填写VOS_TRUE，bcc、ncc、Timealignment、fnoffset按照维护值填写；
      若频点、BCC、NCC任何一个值与本地维护的不一致，则ulSyncValid值填写VOS_FALSE */
    VOS_UINT32                          ulSyncFlag;              /* 0:表示同步无效 1: 表示同步有效 */
    VOS_INT32                           lFNOffset;
    VOS_UINT32                          ulTimeAlignmt;

    RRC_GSM_BAND_INDICATOR_ENUM_UINT32  enBandIndictor;
    VOS_UINT16                          usBcchArfcn;
    VOS_UINT8                           ucNCmodeFlag;        /* NCMode存在标志 */
    VOS_UINT8                           ucNCmode;
    RRC_CELL_CHANGE_GSM_CELL_SYS_INFO_BLOCK_ST stGeranSysInfo;
}RRC_CELL_CHANGE_GSM_CELL_INFO_ST;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */
    RRC_CELL_CHANGE_GSM_CELL_INFO_ST    stGsmCellInfo; /* GSM小区信息 */

    /* 专有优先级信息, 0: 表示不存在，1 表示存在*/
    GURRC_VALID_FLAG_ENUM_UINT8                             enDPriInfoPresent;
    VOS_UINT8                                               ucResv[3];
    GURRC_DEDICATED_PRI_INFO_STRU                           stDPriInfo;
}WRRCRR_CELL_CHANGE_REQ_ST;

/*****************************************************************************
 消息名称  : WRRCRR_CELL_CHANGE_CNF
 功能描述  : WRRC用此原语应答RR发送的WRRCRR_CELL_CHANGE_REQ
 修改历史  :
  1.日    期   : 2005年09月28日
    作    者   : z41416
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */
    RRC_RR_CNF_ENUM_UINT32              enResult;      /* CELL CHANGE切换结果 */
}WRRCRR_CELL_CHANGE_CNF_ST;

/*****************************************************************************
 消息名称  : RRWRRC_HANDOVER_REQ
 功能描述  : RR发送此原语指示WRRC进行系统间切换流程
 修改历史  :
  1.日    期   : 2005年09月09日
    作    者   : Zhangyanzhong(47368)
    修改内容   : 新生成结构
*****************************************************************************/
enum RRC_RAT_TYPE_ENUM
{
    RRC_RAT_WCDMA_FDD               = 0,                /* only WCDMA    */
    RRC_RAT_WCDMA_GSM               = 1,                /* WCDMA and GSM */
    RRC_RAT_GSM                     = 2,                /* only GSM      */
    RRC_RAT_TYPE_BUTT
};
typedef VOS_UINT32  RRC_RAT_TYPE_ENUM_UINT32;

typedef enum
{
    EN_RRC_RR_SEARCH_RESULT_SUCC                 = 0,       /* 成功 */
    EN_RRC_RR_SEARCH_RESULT_FAIL                    ,       /* 失败 */
    EN_RRC_RR_SEARCH_RESULT_ABNORMAL                ,       /* 异常 */
    EN_RRC_RR_SEARCH_RESULT_STATE_NOT_ALLOWED       ,       /* 当前状态不允许 */
    EN_RRC_RR_SEARCH_RESULT_FREQ_LOCK               ,       /* 锁频 */
    EN_RRC_RR_SEARCH_RESULT_PARA_ERROR              ,       /* 参数错误 */

    EN_RRC_RR_SEARCH_RESULT_BUTT
}RRC_RR_SEARCH_RESULT_ENUM;
typedef VOS_UINT32 RRC_RR_SEARCH_RESULT_ENUM_UINT32;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */
    RRC_SINGAL_INFO_ENUM_UINT32         enSignalInfo;       /* 信令连接的类型 */
    RRC_CIPHER_ACTIVE_ENUM_UINT32       enCipherActiveFlg;  /* 指示GSM加密是否激活 */
    VOS_UINT32                          ulMcc;              /* 国家码 */
    
    PS_BOOL_ENUM_UINT8                  enLteOriginatedFlg; /* 当前业务是否是 L 下发起的 */
    VOS_UINT8                           aucRsv[3];

    VOS_UINT16                          usHandOverInfoLen;               /* 切换时空口消息中包含的信息的长度 */
    VOS_UINT8                           aucHandOverInfo[2];              /* 切换时空口消息中包含的信息的地址 */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}RRWRRC_HANDOVER_REQ_ST;


/*****************************************************************************
 消息名称  : RRWRRC_HANDOVER_CNF
 功能描述  : WRRC用此消息应答RR发送的RRWRRC_HANDOVER_REQ消息
 修改历史  :
  1.日    期   : 2005年09月09日
    作    者   : Zhangyanzhong(47368)
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */
    RRC_RR_CNF_ENUM_UINT32              enResult;
    VOS_UINT8                           ucDataFlag;      /* 切换时WRRC回复的消息中存在数据的标志 */
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    VOS_UINT16                          usDataLen;       /* WRRC回复的消息的长度 */
    VOS_UINT8                           aucData[2];      /* WRRC回复的消息的内容 */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}RRWRRC_HANDOVER_CNF_ST;

/*****************************************************************************
 消息名称  : RRWRRC_HANDOVER_STOP_REQ
 功能描述  : RR发送的RRWRRC_HANDOVER_STOP_REQ消息
 修改历史  :
  1.日    期   : 2014-5-13
    作    者   : t00106267
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve[4];      /* 保留位 */
}RRWRRC_HANDOVER_STOP_REQ_STRU;

/*****************************************************************************
 消息名称  : RRWRRC_HANDOVER_STOP_CNF
 功能描述  : WRRC用此消息应答RR发送的RRWRRC_HANDOVER_STOP_REQ消息
 修改历史  :
  1.日    期   : 2014-5-13
    作    者   : t00106267
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve[4];      /* 保留位 */
}RRWRRC_HANDOVER_STOP_CNF_STRU;

/*****************************************************************************
 消息名称  : WRRCRR_HANDOVER_STOP_REQ
 功能描述  : WRR发送的WRRCRR_HANDOVER_STOP_REQ消息
 修改历史  :
  1.日    期   : 2014-5-13
    作    者   : t00106267
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve[4];      /* 保留位 */
}WRRCRR_HANDOVER_STOP_REQ_STRU;

/*****************************************************************************
 消息名称  : WRRCRR_HANDOVER_STOP_CNF
 功能描述  : RR用此消息应答WRR发送的WRRCRR_HANDOVER_STOP_REQ消息
 修改历史  :
  1.日    期   : 2014-5-13
    作    者   : t00106267
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve[4];      /* 保留位 */
}WRRCRR_HANDOVER_STOP_CNF_STRU;

/*****************************************************************************
 消息名称  : WRRCRR_HANDOVER_REQ
 功能描述  : WRRC发送此原语指示RR进行系统间切换流程
 修改历史  :
  1.日    期   : 2005年09月09日
    作    者   : Zhangyanzhong(47368)
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */
    RRC_HANDOVER_GSM_GPRS_INFO_ST       struGsmGprsCellInfo;
    RRC_SINGAL_INFO_ENUM_UINT32         enSignalInfo;
    VOS_UINT32                          ulMcc;              /* 国家码 */
    
    PS_BOOL_ENUM_UINT8                  enLteOriginatedFlg; /* 当前业务是否是 L 下发起的 */
    VOS_UINT8                           aucRsv[3];
}WRRCRR_HANDOVER_REQ_ST;

/*****************************************************************************
 消息名称  : WRRCRR_HANDOVER_CNF
 功能描述  : RR用此原语应答WRRC发送的WRRCRR_HANDOVER_REQ消息
 修改历史  :
  1.日    期   : 2005年09月09日
    作    者   : Zhangyanzhong(47368)
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */
    RRC_RR_CNF_ENUM_UINT32              enResult;
    VOS_UINT8                           ucDataFlag;
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           aucData[2];
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}WRRCRR_HANDOVER_CNF_ST;

/*****************************************************************************
 消息名称  : WRRCRR_PLMN_ID_STRU
 功能描述  : PLMN ID
 修改历史  :
  1.日    期   : 2009年2月26日
    作    者   : c59720
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;              /* MCC,3 bytes      */
    VOS_UINT32                          ulMnc;              /* MNC,2 or 3 bytes */
}WRRCRR_PLMN_ID_STRU;

#define     WRRCRR_MAX_HIGH_PLMN_NUM           (16)                 /* 高质量的PLMN的最大个数 */
#define     WRRCRR_MAX_LOW_PLMN_NUM            (16)                 /* 低质量的PLMN的最大个数 */
#define     WRRCRR_MAX_AVAIL_PLMN_NUM          (18)                 /*out of service时,was带给GAS最大PLMN个数*/
#define     WRRCRR_MAX_EQUAL_PLMN_NUM          (16)                  /*重定向时,was带给GAS最大EPLMN个数*/


/*****************************************************************************
 消息名称  : WRRCRR_PLMN_SEARCH_REQ_ST
 功能描述  : 出服务区流程新增，WAS通知GAS进行PLMN LIST搜索，
             ulGsmCellCnt =0表示全频搜索，
             如果ulGsmCellCnt>0，表示是W小区的邻区，G只作搜索这些邻区的PLMN
 修改历史  :
  1.日    期   : 2009年2月26日
    作    者   : c59720
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */

    VOS_UINT32                          ulGsmCellCnt;       /* 如果有GSM邻区，则只需要找到这些邻区的PLMN即可,取值范围 0 ~ 32,0表示没有邻区，需要GAS作全频段搜索 */
    RRC_SAVE_CELL_INFO_FOR_GAS_ST       astGsmCellInfo[RRC_MAX_INTER_GSM_CELL_NUM];   /* 每个GSM小区信息 */

    VOS_UINT32                          ulAvailPlmnIdNum;        /* PLMN ID个数 */
    WRRCRR_PLMN_ID_STRU                 astAvailPlmnIdList[WRRCRR_MAX_AVAIL_PLMN_NUM];       /* PlMN标识 */
}WRRCRR_PLMN_SEARCH_REQ_ST;

/*****************************************************************************
 消息名称  : WRRCRR_LOW_PLMN_INFO_STRU
 功能描述  : 低质量的PLMN ID
 修改历史  :
  1.日    期   : 2009年2月26日
    作    者   : c59720
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    WRRCRR_PLMN_ID_STRU                 stPlmnId;             /* PLMN ID    */
    RRC_RAT_TYPE_ENUM_UINT32            lRat;               /* 接入技术 */
}WRRCRR_PLMN_ID_WITH_RAT_STRU;

typedef struct
{
    WRRCRR_PLMN_ID_STRU                 stPlmnId;             /* PLMN ID    */
    VOS_INT32                           lRscp;              /* RSCP测量值 */
}WRRCRR_LOW_PLMN_INFO_STRU;

/*****************************************************************************
 消息名称  : WRRCRR_PLMN_ID_LIST_STRU
 功能描述  : PLMN LIST
 修改历史  :
  1.日    期   : 2009年2月26日
    作    者   : c59720
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulHighPlmnNum;                          /* 高质量PLMN的个数 */
    VOS_UINT32                          ulLowPlmnNum;                           /* 低质量PLMN的个数 */
    WRRCRR_PLMN_ID_STRU                 astHighPlmnList[WRRCRR_MAX_HIGH_PLMN_NUM];   /* 高质量PLMN列表   */
    WRRCRR_LOW_PLMN_INFO_STRU           astLowPlmnList[WRRCRR_MAX_LOW_PLMN_NUM];     /* 低质量PLMN列表   */
}WRRCRR_PLMN_ID_LIST_STRU;

/*****************************************************************************
 消息名称  : WRRCRR_PLMN_SEARCH_CNF_ST
 功能描述  : 出服务区特性新增接口:GAS通知WAS搜索到的PLMN LIST
 修改历史  :
  1.日    期   : 2009年2月26日
    作    者   : c59720
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */

    RRC_RR_SEARCH_RESULT_ENUM_UINT32    enResult;           /* 仅使用其中的两个原因值:EN_SUCCESS or EN_FAILURE */

    /* enResult原因值为EN_SUCCESS时,才需要查找是否有PLMN，如果没有PLMN，则认为也是失败 */
    WRRCRR_PLMN_ID_LIST_STRU            PlmnIdList;         /* 上报的PLMN ID列表 */
}WRRCRR_PLMN_SEARCH_CNF_ST;

/*****************************************************************************
 消息名称  : WRRCRR_PLMN_SEARCH_STOP_REQ_ST
 功能描述  : 出服务区特性新增接口:WAS通知GAS停止此次PLMN搜索
 修改历史  :
  1.日    期   : 2009年2月26日
    作    者   : c59720
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];
}WRRCRR_PLMN_SEARCH_STOP_REQ_ST;

/*****************************************************************************
 消息名称  : WRRCRR_PLMN_SEARCH_STOP_CNF_ST
 功能描述  : 出服务区特性新增接口:GAS在停止PLMN 搜索后，给WAS的响应
 修改历史  :
  1.日    期   : 2009年2月26日
    作    者   : c59720
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];
}WRRCRR_PLMN_SEARCH_STOP_CNF_ST;

/*****************************************************************************
 消息名称  : RR_RRC_RESEL_TYPE_ENUM
 功能描述  :
 修改历史  :
  1.日    期   : 2010年9月7日
    作    者   : Chenwenfeng 59720
    修改内容   : 新生成枚举
*****************************************************************************/
typedef enum
{
    EN_RR_RRC_RESEL_NORMAL        = 0,                                          /* G2W正常重选，需要WAS判断等效plmn列表以及forbid la信息*/
    EN_RR_RRC_RESEL_ANYCELL_CAMP     ,                                          /* G下anycell驻留，不需要wAS判断等效plmn列表以及forbid la信息*/
    EN_RR_RRC_RESEL_BUTT
}RR_RRC_RESEL_TYPE_ENUM;
typedef VOS_UINT32 RR_RRC_RESEL_TYPE_ENUM_UINT32;

/*****************************************************************************
 消息名称  : RRWRRC_CELL_RESEL_REQ
 功能描述  : RR接收到网络发送的小区重选命令消息，通过此原语指示WRRC进行小区重选
 修改历史  :
  1.日    期   : 2005年09月28日
    作    者   : z41416
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT16                          usFreqInfo;                             /* 频率 */
    VOS_UINT16                          usPrimaryScramCode;                     /* 小区扰码 */
    VOS_UINT8                           ucDiversity;                            /* 分集指示 */
    VOS_UINT8                           aucReserve1[3];                         /* 4字节对齐，保留 */
    RRC_SINGAL_INFO_ENUM_UINT32         enSignalInfo;
    RR_RRC_RESEL_TYPE_ENUM_UINT32       enReselType;                            /* 需要目标小区是按照ANYCELL或者SUITABLE驻留准则进行驻留 */

    /* 专有优先级信息, 0: 表示不存在，1 表示存在*/
    GURRC_VALID_FLAG_ENUM_UINT8                             enDPriInfoPresent;
    VOS_UINT8                                               ucResv[3];
    GURRC_DEDICATED_PRI_INFO_STRU                           stDPriInfo;
}RRWRRC_CELL_RESEL_REQ_ST;

/*****************************************************************************
 消息名称  : RRWRRC_CELL_RESEL_CNF
 功能描述  : WRRC用此原语应答RR发送的RRWRRC_CELL_RESEL_REQ
 修改历史  :
  1.日    期   : 2005年09月28日
    作    者   : z41416
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */
    RRC_RR_CNF_ENUM_UINT32              enCnf;
    VOS_UINT32                          ulTBarLen;      /* 单位为S，仅在enCnf为EN_CELL_RESEL_FAIL_REASON_CELL_BAR时有效 */

    /* 当GW重选无法驻留时，填写此sQrxLevValue为按照协议计算后的实际门限值 */
    /* 此参数只能与EN_CELL_RESEL_FAIL_REASON_S_OR_C1_CHECK_FAIL同时使用 */
    VOS_INT16                           sQrxlevMin;   /* RSRP最低接入门限，单位1/8dB*/

    VOS_INT16                           sQqualMin;    /* Ec/No最低接入门限，单位1/8dB*/
}RRWRRC_CELL_RESEL_CNF_ST;

/*****************************************************************************
 消息名称  : WRRCRR_CELL_RESEL_REQ
 功能描述  : WRRC接收到网络发送的小区重选命令消息，通过此原语指示RR进行小区重选
 修改历史  :
  1.日    期   : 2005年09月28日
    作    者   : z41416
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */
    RRC_SAVE_CELL_INFO_FOR_GAS_ST       stGsmCellInfo;
    RRC_SINGAL_INFO_ENUM_UINT32         enSignalInfo;
    RRC_RR_RESEL_TYPE_ENUM_UINT32         enReselType;   /* W2G重选GAS需不需要判断等效plmn和forbid LA 标志*/

    /* 专有优先级信息, 0: 表示不存在，1 表示存在*/
    GURRC_VALID_FLAG_ENUM_UINT8                             enDPriInfoPresent;
    VOS_UINT8                                               ucResv[3];
    GURRC_DEDICATED_PRI_INFO_STRU                           stDPriInfo;
}WRRCRR_CELL_RESEL_REQ_ST;

/*****************************************************************************
 消息名称  : WRRCRR_CELL_RESEL_CNF
 功能描述  : RR用此原语应答WRRC发送的WRRCRR_CELL_RESEL_REQ
 修改历史  :
  1.日    期   : 2005年09月28日
    作    者   : z41416
    修改内容   : 新生成结构
  2.日    期   : 2015年11月11日
    作    者   : w00146666
    修改内容   : for DTS2015112600361, 增加惩罚时间    
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */
    RRC_RR_CNF_ENUM_UINT32              enResult;

    VOS_UINT32                          ulTBarLen;          /* 单位为毫秒， 仅在enCnf为EN_CELL_RESEL_FAIL_REASON_CELL_BAR时有效 */    

    /* 当usResult 原因值为EN_CELL_RESEL_FAIL_REASON_S_OR_C1_CHECK_FAIL时， sC1Param参数有效
        表示与C1值计算相关的参数，WAS计算公式C1= sRxlev- sC1Param, Rxlev为一精度   */
    VOS_INT16                                               sC1Param;
    VOS_UINT8                                               aucReserved[2];       
}WRRCRR_CELL_RESEL_CNF_ST;

/*****************************************************************************
 消息名称  : RRWRRC_CELL_CHANGE_TIMER_EXPIRED_REQ
 功能描述  : RR用此原语通知WRRC定时器超时
 修改历史  :
  1.日    期   : 2005年10月12日
    作    者   : z41416
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[4];     /* 4字节对齐，保留 */
}RRWRRC_CELL_CHANGE_TIMER_EXPIRED_REQ_ST;

/*****************************************************************************
 消息名称  : RRWRRC_CELL_CHANGE_TIMER_EXPIRED_CNF
 功能描述  : WRRC用此原语应答RR发送的RRWRRC_CELL_CHANGE_TIMER_EXPIRED_REQ
 修改历史  :
  1.日    期   : 2005年10月12日
    作    者   : z41416
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[4];     /* 4字节对齐，保留 */
}RRWRRC_CELL_CHANGE_TIMER_EXPIRED_CNF_ST;


/*****************************************************************************
 消息名称  : WRRCRR_CELL_CHANGE_TIMER_EXPIRED_REQ
 功能描述  : WRRC用此原语通知RR定时器超时
 修改历史  :
  1.日    期   : 2005年10月12日
    作    者   : z41416
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[4];     /* 4字节对齐，保留 */
}WRRCRR_CELL_CHANGE_TIMER_EXPIRED_REQ_ST;

/*****************************************************************************
 消息名称  : WRRCRR_CELL_CHANGE_TIMER_EXPIRED_CNF
 功能描述  : RR用此原语应答WRRC发送的WRRCRR_CELL_CHANGE_TIMER_EXPIRED_REQ
 修改历史  :
  1.日    期   : 2005年10月12日
    作    者   : z41416
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[4];     /* 4字节对齐，保留 */
}WRRCRR_CELL_CHANGE_TIMER_EXPIRED_CNF_ST;

/*****************************************************************************
 消息名称  : WRRCRR_CELL_RESEL_TIMER_EXPIRED_REQ
 功能描述  : WRR用此原语通知重选超时
 修改历史  :
  1.日    期   : 2006年12月25日
    作    者   : Jinying
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[4];     /* 4字节对齐，保留 */
}WRRCRR_CELL_RESEL_TIMER_EXPIRED_REQ_ST;

/*****************************************************************************
 消息名称  : WRRCRR_CELL_RESEL_TIMER_EXPIRED_CNF
 功能描述  : RR用此原语应答WRRCRR_CELL_RESEL_TIMER_EXPIRED_REQ_ST
 修改历史  :
  1.日    期   : 2006年12月25日
    作    者   : Jinying
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[4];     /* 4字节对齐，保留 */
}WRRCRR_CELL_RESEL_TIMER_EXPIRED_CNF_ST;

#define RR_WRRC_INTER_RAT_HANDOVER_INFO_LEN                (250)                /* INTER_RAT_HANDOVER_INFO 长度, 最长250字节 */


/*******************************************************************************
 结构名    : RRWRRC_INTER_RAT_HANDOVER_INFO_REQ_ST
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息 RRWRRC_INTER_RAT_HANDOVER_INFO_REQ 的结构
             该消息用于向WRR获取inter rat hand over info。
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    PS_BOOL_ENUM_UINT8                  enNeedCmprVer;                          /* 是否需要压缩版本的信息 */
    VOS_UINT8                           aucReserve1[3];                         /* 保留字段,便于将来扩展 */
    VOS_UINT32                          ulMcc;                                  /* 当前驻留国家码，中国PLMN */
}RRWRRC_INTER_RAT_HANDOVER_INFO_REQ_ST;

/*******************************************************************************
 结构名    : RRWRRC_INTER_RAT_HANDOVER_INFO_CNF_ST
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息 RRWRRC_INTER_RAT_HANDOVER_INFO_CNF 的结构
             该消息用于向GAS回复 inter rat hand over info。
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                    MsgHeader;          /* 消息头 */         /*_H2ASN_Skip*/
    VOS_UINT16                         usDataLen;
    VOS_UINT8                          aucData[RR_WRRC_INTER_RAT_HANDOVER_INFO_LEN];
}RRWRRC_INTER_RAT_HANDOVER_INFO_CNF_ST;

/*******************************************************************************
 结构名    : WRRCRR_INTER_RAT_HANDOVER_INFO_REQ_ST
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息 WRRCRR_INTER_RAT_HANDOVER_INFO_REQ 的结构
             该消息用于向GAS获取GSM能力信息。
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT32                          ulMcc;                                  /* 当前驻留国家码，中国PLMN */
}WRRCRR_INTER_RAT_HANDOVER_INFO_REQ_ST;

/*******************************************************************************
 结构名    : WRRCRR_INTER_RAT_HANDOVER_INFO_CNF_ST
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息 WRRCRR_INTER_RAT_HANDOVER_INFO_CNF 的结构
             该消息用于向WAS回复 GSM能力信息。
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                    MsgHeader;          /* 消息头 */         /*_H2ASN_Skip*/
    VOS_UINT8                          ucClassmark2Len;                        /* Classmark2 长度 */
    VOS_UINT8                          aucClassmark2[GSM_CLASSMARK2_MAX_LEN];  /* Classmark2 内容 */
    VOS_UINT8                          ucClassmark3Len;                        /* Classmark3 长度 */
    VOS_UINT8                          aucClassmark3[GSM_CLASSMARK3_MAX_LEN];  /* Classmark3 内容 */
    VOS_UINT8                          aucReserve1[2];                         /* 4字节对齐，保留 */
}WRRCRR_INTER_RAT_HANDOVER_INFO_CNF_ST;

#define RR_WRRC_MAX_3GNCELL_NUM          96                              /* channel release GAS最多携带96个小区 */

/*****************************************************************************
 消息名称  : RRC_CELL_SEL_3GNCELL_ST
 功能描述  : channel release携带的3G小区列表
 修改历史  :
  1.日    期   : 2010年03月08日
    作    者   :
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  usFreq;                             /* 频点 */
    VOS_UINT16                  usScramblingCode;                   /* 如果扰码无效使用0xFFFF值 */
    VOS_UINT8                   ucDiversity;                        /* 小区是否使用分集指示,如果扰码无效，分集指示也无效 */
    VOS_UINT8                   ucBandWidth;                        /*  W小区信道带宽 *//* W暂时不用 */
    VOS_UINT8                   aucReserve1[2];                     /* 4字节对齐，保留 */

}RRC_CELL_SEL_3GNCELL_ST;

/*****************************************************************************
 消息名称  : RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_REQ_ST
 功能描述  : G channel release后，给W发的消息
 修改历史  :
  1.日    期   : 2010年03月08日
    作    者   :
    修改内容   : 新生成结构
*****************************************************************************/

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[3];                         /* 4字节对齐，保留 */
    VOS_UINT8                           uc3GNCellCnt;                           /* total valid cell number */
    RRC_CELL_SEL_3GNCELL_ST             ast3GNCell[RR_WRRC_MAX_3GNCELL_NUM];

    /* 专有优先级信息, 0: 表示不存在，1 表示存在*/
    GURRC_VALID_FLAG_ENUM_UINT8                             enDPriInfoPresent;
    VOS_UINT8                                               ucResv[3];
    GURRC_DEDICATED_PRI_INFO_STRU                           stDPriInfo;
}RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_REQ_ST;

/*****************************************************************************
 消息名称  : RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_CNF_ST
 功能描述  : 对RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_REQ的回复
 修改历史  :
  1.日    期   : 2010年03月08日
    作    者   :
    修改内容   : 新生成结构
*****************************************************************************/

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */

    RRC_RR_CNF_ENUM_UINT32              enResult;                               /* 重选结果 */
}RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_CNF_ST;

/*****************************************************************************
 消息名称  : RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_TIMER_EXPIRED_REQ_ST
 功能描述  : 对RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_REQ超时的消息
 修改历史  :
  1.日    期   : 2010年03月08日
    作    者   :
    修改内容   : 新生成结构
*****************************************************************************/

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];                         /* 4字节对齐，保留 */
}RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_TIMER_EXPIRED_REQ_ST;


/*****************************************************************************
 消息名称  : RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_TIMER_EXPIRED_CNF_ST
 功能描述  : 对RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_TIMER_EXPIRED_REQ_ST消息的回复
              该消息不需要原因值，不管成功失败,Gas处理都一样
 修改历史  :
  1.日    期   : 2010年03月08日
    作    者   :
    修改内容   : 新生成结构
*****************************************************************************/

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];     /* 4字节对齐，保留 */
}RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_TIMER_EXPIRED_CNF_ST;


/*****************************************************************************
 消息名称  : WRRCRR_CELL_SEL_REDIRECTION_REQ_ST
 功能描述  : ulGsmCellCnt =0表示全频搜索，否则先搜这些小区，搜不到再全频搜
             ulAvailPlmnIdNum = 0; 不存在SIM卡时，驻留任意受限小区，标识不限定PLMN范围，
             否则搜到的小区要限定PLMN范围
 修改历史  :
  1.日    期   : 2010年8月31日
    作    者   : s58750
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */

    VOS_UINT32                          ulGsmCellCnt;
    RRC_SAVE_CELL_INFO_FOR_GAS_ST       astGsmCellInfo[RRC_MAX_INTER_GSM_CELL_NUM];   /* 每个GSM小区信息 */
    VOS_UINT32                          ulEquPlmnIdNum;                              /* PLMN ID个数 ,PLMN NUM = 0表示任意驻留*/
    WRRCRR_PLMN_ID_STRU                 astEquPlmnIdList[WRRCRR_MAX_EQUAL_PLMN_NUM];  /* PlMN标识，只带EPLMN*/
    VOS_UINT32                          ulWaitTimeLen;                          /* wait time时间，单位是ms */

    /* 专有优先级信息, 0: 表示不存在，1 表示存在*/
    GURRC_VALID_FLAG_ENUM_UINT8                             enDPriInfoPresent;
    VOS_UINT8                                               ucResv[3];
    GURRC_DEDICATED_PRI_INFO_STRU                           stDPriInfo;
}WRRCRR_CELL_SEL_REDIRECTION_REQ_ST;

/*****************************************************************************
 消息名称  : WRRCRR_CELL_SEL_REDIRECTION_CNF_ST
 功能描述  : 对WRRCRR_CELL_SEL_REDIRECTION_REQ_ST的回复
 修改历史  :
  1.日    期   : 2010年8月31日
    作    者   : s58750
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */

    RRC_RR_CNF_ENUM_UINT32              enResult;                               /* 搜索小区结果 */
}WRRCRR_CELL_SEL_REDIRECTION_CNF_ST;

/*****************************************************************************
 消息名称  : WRRCRR_CELL_SEL_REDIRECTION_ABORT_REQ_ST
 功能描述  : 对WRRCRR_CELL_SEL_REDIRECTION_REQ_ST超时的消息
 修改历史  :
  1.日    期   : 2010年8月31日
    作    者   : s58750
    修改内容   : 新生成结构
*****************************************************************************/

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];                         /* 4字节对齐，保留 */
}WRRCRR_CELL_SEL_REDIRECTION_ABORT_REQ_ST;


/*****************************************************************************
 消息名称  : WRRCRR_CELL_SEL_REDIRECTION_ABORT_CNF_ST
 功能描述  : 对WRRCRR_CELL_SEL_REDIRECTION_ABORT_REQ_ST消息的回复
              该消息不需要原因值，
 修改历史  :
  1.日    期   : 2010年8月31日
    作    者   : s58750
    修改内容   : 新生成结构
*****************************************************************************/

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];     /* 4字节对齐，保留 */
}WRRCRR_CELL_SEL_REDIRECTION_ABORT_CNF_ST;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */

    VOS_UINT8                           ucClassmark2Len;                        /* Classmark2 长度 */
    VOS_UINT8                           aucClassmark2[GSM_CLASSMARK2_MAX_LEN];  /* Classmark2 内容 */

    VOS_UINT8                           ucClassmark3Len;                        /* Classmark3 长度 */
    VOS_UINT8                           aucClassmark3[GSM_CLASSMARK3_MAX_LEN];  /* Classmark3 内容 */

    VOS_UINT8                           aucReserve1[2];                         /* 4字节对齐，保留 */

}RRWRRC_CLASSMARK_CHANGE_IND_ST;

/*****************************************************************************
 消息名称  : WRRCRR_INTERRAT_PLMN_SEARCH_REQ
 功能描述  : WRRC通过此消息通知GAS在DEACTIVE状态下进行搜网
 修改历史  :
  1.日    期   : 2010年10月19日
    作    者   : L00128652
    修改内容   : 新生成结构
  2.日    期   : 2013年8月23日
    作    者   : L00128652
    修改内容   : 增加NET SCAN类型

*****************************************************************************/
typedef enum
{
    EN_RRC_RR_SEARCH_BG                 = 0,                                    /* WAS/GAS通知GAS/WAS做背景搜 */
    EN_RRC_RR_SEARCH_PLMN_LIST             ,                                    /* WAS/GAS通知GAS/WAS做PLMN LIST搜  */
    EN_RRC_RR_SEARCH_NET_SCAN              ,                                    /* WAS/GAS通知GAS/WAS做NET SCAN搜  */
    EN_RRC_RR_SEARCH_BG_HIGH_RAT           ,                                    /* 高优先级RAT BG搜 */
    EN_RRC_RR_SEARCH_BUTT
}RRC_RR_SEARCH_TYPE_ENUM;

typedef VOS_UINT32 RRC_RR_SEARCH_TYPE_ENUM_UINT32;

typedef struct
{
    WRRCRR_PLMN_ID_STRU                 PlmnId;             /* PlMN标识       */
    VOS_UINT32                          ulForbLac;          /* 禁止注册区信息 */
}WRRCRR_FORB_LA_STRU;

/*****************************************************************************
 消息名称  : WRRCRR_NET_SCAN_REQ_INFO_STRU
 功能描述  : 此消息结构通知做NET_SCAN搜网
 修改历史  :
  1.日    期   : 2013年8月23日
    作    者   : L00128652
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCellInfoNum;                          /* 要求上报的小区个数，范围1~20 */
    VOS_INT16                           sCellPwrThreshold;                      /* 小区上报能量门限，取值范围为-110~-47 */
    VOS_UINT32                          ulBand;                                 /* 要搜索的BAND信息，如果需要搜索所有支持频段设置为0xFFFFFFFF */
}WRRCRR_NET_SCAN_REQ_INFO_STRU;

/*****************************************************************************
 消息名称  : WRRCRR_CELL_INFO_STRU
 功能描述  : NET SCAN过程搜到的小区信息
 修改历史  :
  1.日    期   : 2013年8月23日
    作    者   : L00128652
    修改内容   : 新生成结构
  2.日    期   : 2014年11月04日
    作    者   : j00204253
    修改内容   : 新增PSC数据，修改Cell Id定义 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usArfcn;                        /* 绝对频率 */
    VOS_UINT16                                  usC1;                           /* cell reselection coefficient,W上报0 */
    VOS_UINT16                                  usC2;                           /* cell reselection coefficient,W上报0 */
    VOS_UINT16                                  usLocAreaCode;                  /* LAC */
    VOS_UINT32                                  ulMcc;                          /* MCC,3 bytes      */
    VOS_UINT32                                  ulMnc;                          /* MNC,2 or 3 bytes */
    VOS_UINT16                                  usBsic;                         /* W上报0 */
    VOS_INT16                                   sRxlev;                         /* W则上报RSCP */
    VOS_INT16                                   sRssi;                          /* W则上报RSCP */
    VOS_UINT16                                  usPSC;                          /* G小区上报0xFFFF，W上报PSC */
    VOS_UINT32                                  ulCellId;                       /* 小区ID */
    VOS_UINT32                                  ulBand;                         /* 小区BAND信息 */
}WRRCRR_CELL_INFO_STRU;

/*****************************************************************************
 消息名称  : WRRCRR_NET_SCAN_INFO_STRU
 功能描述  : 此消息回复NET_SCAN搜网结果
 修改历史  :
  1.日    期   : 2013年8月23日
    作    者   : L00128652
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCellInfoNum;                          /* 实际上报的小区个数 */
    VOS_UINT8                           aucRsv[2];

    WRRCRR_CELL_INFO_STRU               astCellInfoList[WRRC_RR_MAX_NET_SCAN_CELL_NUM];    /* 上报的满足条件的小区信息 */
}WRRCRR_NET_SCAN_INFO_STRU;

/*****************************************************************************
 消息名称  : WRRCRR_INTERRAT_PLMN_SEARCH_REQ_ST
 功能描述  : WAS通过此消息通知GAS在DEACTIVE状态下进行搜网
 修改历史  :
  1.日    期   : 2010年10月19日
    作    者   : L00128652
    修改内容   : 新生成结构
  2.日    期   : 2013年8月23日
    作    者   : L00128652
    修改内容   : 增加NET SCAN结构

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */
    RRC_RR_SEARCH_TYPE_ENUM_UINT32      enSearchType;                           /* WAS通知GAS是做背景搜还是PLMN LIST搜 */
    WRRCRR_PLMN_ID_STRU                 stPlmnId;                               /* PlMN标识，只在背景搜有效 */
    VOS_UINT32                          ulForbLaNum;                            /* 禁止注册区的个数 */
    WRRCRR_FORB_LA_STRU                 aForbLaList[WRRC_RR_MAX_FORBLA_NUM];    /* 禁止注册区列表 */
    WRRCRR_NET_SCAN_REQ_INFO_STRU       stNetScanReqInfo;                       /* NET SCAN请求信息 */
}WRRCRR_INTERRAT_PLMN_SEARCH_REQ_ST;

/*****************************************************************************
 消息名称  : WRRCRR_INTERRAT_PLMN_SEARCH_CNF_ST
 功能描述  : GAS通过此消息通知WAS在DEACTIVE状态下的搜网配置的确认
 修改历史  :
  1.日    期   : 2010年10月19日
    作    者   : L00128652
    修改内容   : 新生成结构
  2.日    期   : 2013年8月23日
    作    者   : L00128652
    修改内容   : 增加NET SCAN结构

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */
    RRC_RR_SEARCH_RESULT_ENUM_UINT32    enResult;                               /* 背景搜成功或失败，NET SCAN搜GAS可以携带成功，失败，参数检查失败 */
}WRRCRR_INTERRAT_PLMN_SEARCH_CNF_ST;

/*****************************************************************************
 消息名称  : WRRCRR_INTERRAT_PLMN_SEARCH_IND_ST
 功能描述  : GAS通过此消息通知WAS在DEACTIVE状态下的搜网结果
 修改历史  :
  1.日    期   : 2014年4月23日
    作    者   : L00128652
    修改内容   : 新生成结构

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */
    RRC_RR_SEARCH_RESULT_ENUM_UINT32    enResult;                               /* 背景搜成功或失败，NET SCAN搜GAS只携带成功 */
    RRC_RR_SEARCH_TYPE_ENUM_UINT32      enSearchType;                           /* WAS通知GAS是做背景搜还是PLMN LIST搜 */
    WRRCRR_PLMN_ID_LIST_STRU            stPlmnIdList;                           /* 上报的PLMN ID列表 */
    WRRCRR_NET_SCAN_INFO_STRU           stNetScanInfo;                          /* 上报的NET SCAN的结果 */

}WRRCRR_INTERRAT_PLMN_SEARCH_IND_ST;

/*****************************************************************************
 消息名称  : WRRCRR_INTERRAT_PLMN_SEARCH_STOP_REQ_ST
 功能描述  : WAS通知GAS停止搜网
 修改历史  :
  1.日    期   : 2010年10月19日
    作    者   : L00128652
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];
}WRRCRR_INTERRAT_PLMN_SEARCH_STOP_REQ_ST;

/*****************************************************************************
 消息名称  : WRRCRR_INTERRAT_PLMN_SEARCH_STOP_CNF_ST
 功能描述  : GAS收到WAS停止搜网消息后的响应
 修改历史  :
  1.日    期   : 2010年10月19日
    作    者   : L00128652
    修改内容   : 新生成结构
  2.日    期   : 2013年8月23日
    作    者   : L00128652
    修改内容   : 增加NET SCAN结构

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */
    RRC_RR_SEARCH_TYPE_ENUM_UINT32      enSearchType;                           /*背景搜，PLMN LIST搜还是NET SCAN */
    WRRCRR_NET_SCAN_INFO_STRU           stNetScanInfo;                          /* 上报的NET SCAN的结果 */
}WRRCRR_INTERRAT_PLMN_SEARCH_STOP_CNF_ST;

/*****************************************************************************
 消息名称  : WRRCRR_INTERRAT_PLMN_SEARCH_SUSPEND_REQ_ST
 功能描述  : WAS通知GAS暂停搜网
 修改历史  :
  1.日    期   : 2010年10月19日
    作    者   : L00128652
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];
}WRRCRR_INTERRAT_PLMN_SEARCH_SUSPEND_REQ_ST;

/*****************************************************************************
 消息名称  : WRRCRR_INTERRAT_PLMN_SEARCH_SUSPEND_CNF_ST
 功能描述  : GAS收到WAS暂停搜网消息后的响应
 修改历史  :
  1.日    期   : 2010年10月19日
    作    者   : L00128652
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];
}WRRCRR_INTERRAT_PLMN_SEARCH_SUSPEND_CNF_ST;

/*****************************************************************************
 消息名称  : WRRCRR_INTERRAT_PLMN_SEARCH_RESUME_REQ_ST
 功能描述  : WAS通知GAS重启搜网
 修改历史  :
  1.日    期   : 2010年10月19日
    作    者   : L00128652
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];
}WRRCRR_INTERRAT_PLMN_SEARCH_RESUME_REQ_ST;

/*****************************************************************************
 消息名称  : WRRCRR_INTERRAT_PLMN_SEARCH_RESUME_CNF_ST
 功能描述  : GAS收到WAS重启搜网消息后的响应
 修改历史  :
  1.日    期   : 2010年10月19日
    作    者   : L00128652
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];
}WRRCRR_INTERRAT_PLMN_SEARCH_RESUME_CNF_ST;

/*****************************************************************************
 消息名称  : RRWRRC_INTERRAT_PLMN_SEARCH_REQ_ST
 功能描述  : GAS通过此消息通知WAS在DEACTIVE状态下做全频段搜网
 修改历史  :
  1.日    期   : 2010年10月19日
    作    者   : L00128652
    修改内容   : 新生成结构
  2.日    期   : 2013年8月23日
    作    者   : L00128652
    修改内容   : 增加NET SCAN结构

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */
    RRC_RR_SEARCH_TYPE_ENUM_UINT32      enSearchType;                           /* GAS通知WAS是做背景搜还是PLMN LIST搜 */
    WRRCRR_PLMN_ID_STRU                 stPlmnId;                               /* PlMN标识 */
    VOS_UINT32                          ulForbLaNum;                            /* 禁止注册区的个数 */
    WRRCRR_FORB_LA_STRU                 aForbLaList[WRRC_RR_MAX_FORBLA_NUM];    /* 禁止注册区列表                           */
    WRRCRR_NET_SCAN_REQ_INFO_STRU       stNetScanReqInfo;                       /* 请求的NET SCAN的信息 */
}RRWRRC_INTERRAT_PLMN_SEARCH_REQ_ST;

/*****************************************************************************
 消息名称  : RRWRRC_INTERRAT_PLMN_SEARCH_CNF_ST
 功能描述  : WAS通过此消息通知GAS在DEACTIVE状态下的搜网配置的确认
 修改历史  :
  1.日    期   : 2010年10月19日
    作    者   : L00128652
    修改内容   : 新生成结构
  2.日    期   : 2013年8月23日
    作    者   : L00128652
    修改内容   : 增加NET SCAN结构

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */
    RRC_RR_SEARCH_RESULT_ENUM_UINT32    enResult;                               /* 背景搜成功或失败 */
}RRWRRC_INTERRAT_PLMN_SEARCH_CNF_ST;


/*****************************************************************************
 消息名称  : RRWRRC_INTERRAT_PLMN_SEARCH_IND_ST
 功能描述  : WAS通过此消息通知GAS在DEACTIVE状态下的搜网结果
 修改历史  :
  1.日    期   : 2014年3月11日
    作    者   : L00128652
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */
    RRC_RR_SEARCH_RESULT_ENUM_UINT32    enResult;                               /* 背景搜成功或失败 */
    RRC_RR_SEARCH_TYPE_ENUM_UINT32      enSearchType;                           /* GAS通知WAS是做背景搜还是PLMN LIST搜 */
    WRRCRR_PLMN_ID_LIST_STRU            PlmnIdList;                             /* 上报的PLMN ID列表 */
    WRRCRR_NET_SCAN_INFO_STRU           stNetScanInfo;                          /* 上报的NET SCAN的结果 */
}RRWRRC_INTERRAT_PLMN_SEARCH_IND_ST;

/*****************************************************************************
 消息名称  : RRWRRC_INTERRAT_PLMN_SEARCH_STOP_REQ_ST
 功能描述  : GAS通知WAS停止搜网
 修改历史  :
  1.日    期   : 2010年10月19日
    作    者   : f48555
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];
}RRWRRC_INTERRAT_PLMN_SEARCH_STOP_REQ_ST;

/*****************************************************************************
 消息名称  : RRWRRC_INTERRAT_PLMN_SEARCH_STOP_CNF_ST
 功能描述  : WAS收到GAS停止搜网消息后的响应
 修改历史  :
  1.日    期   : 2010年10月19日
    作    者   : f48555
    修改内容   : 新生成结构
  2.日    期   : 2013年8月23日
    作    者   : L00128652
    修改内容   : 增加NET SCAN结构

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */
    RRC_RR_SEARCH_TYPE_ENUM_UINT32      enSearchType;                           /* 背景搜，PLMN LIST搜还是NET SCAN */
    WRRCRR_NET_SCAN_INFO_STRU           stNetScanInfo;                          /* 上报的NET SCAN的结果 */
}RRWRRC_INTERRAT_PLMN_SEARCH_STOP_CNF_ST;

/*****************************************************************************
 消息名称  : RRWRRC_PLMN_SEARCH_SUSPEND_REQ_ST
 功能描述  : GAS通知WAS暂停搜网
 修改历史  :
  1.日    期   : 2010年10月21日
    作    者   : f48555
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];
}RRWRRC_INTERRAT_PLMN_SEARCH_SUSPEND_REQ_ST;

/*****************************************************************************
 消息名称  : RRWRRC_PLMN_SEARCH_SUSPEND_CNF_ST
 功能描述  : WAS收到GAS暂停搜网消息后的响应
 修改历史  :
  1.日    期   : 2010年10月21日
    作    者   : f48555
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];
}RRWRRC_INTERRAT_PLMN_SEARCH_SUSPEND_CNF_ST;

/*****************************************************************************
 消息名称  : RRWRRC_PLMN_SEARCH_RESUME_REQ_ST
 功能描述  : GAS通知WAS重启搜网
 修改历史  :
  1.日    期   : 2010年10月21日
    作    者   : f48555
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];
}RRWRRC_INTERRAT_PLMN_SEARCH_RESUME_REQ_ST;

/*****************************************************************************
 消息名称  : RRWRRC_PLMN_SEARCH_RESUME_CNF_ST
 功能描述  : WAS收到GAS重启搜网消息后的响应
 修改历史  :
  1.日    期   : 2010年10月21日
    作    者   : f48555
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];
}RRWRRC_INTERRAT_PLMN_SEARCH_RESUME_CNF_ST;

/*****************************************************************************
 结 构 名  : RRWRRC_CELL_RESEL_STOP_REQ_ST
 结构说明  :
 修改历史  :
  1.日  期   : 2013年7月31日
    作  者   : s00184266
    修改内容 : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[4];
}RRWRRC_CELL_RESEL_STOP_REQ_ST;

/*****************************************************************************
 结 构 名  : RRWRRC_CELL_RESEL_STOP_CNF_ST
 结构说明  :
 修改历史  :
  1.日  期   : 2013年7月31日
    作  者   : s00184266
    修改内容 : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[4];
}RRWRRC_CELL_RESEL_STOP_CNF_ST;

/*****************************************************************************
 结 构 名  : RRWRRC_WCELL_INFO_LIST_STRU
 结构说明  :
 修改历史  :
  1.日    期   : 2014年1月27日
    作    者   : L00128652
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usArfcn;                            /* 频点信息 [0，16383] */
    PS_BOOL_ENUM_UINT8                      enDetectedCellMeasInd;              /* 是否需要测量Detected小区 */
    VOS_UINT8                               aucReserve1[3];
    VOS_UINT16                              usCellNum;                          /* 一个频点下的小区数目,[1，32] */
    VOS_UINT16                              ausPrimaryScramCode[WRRC_RR_MAX_UTRAN_CELL_PER_FREQ_NUM];
} RRWRRC_WCELL_INFO_LIST_STRU;

/*****************************************************************************
 结构名    : WRRC_UTRAN_CELL_INFO_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : UTRAN异系统信息列表
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqNum;                              /* 需测量的WCDMA频点数目，[0，3] */
    VOS_UINT8                           aucRsv[2];
    RRWRRC_WCELL_INFO_LIST_STRU         astFreqInfo[WRRC_RR_MAX_UTRAN_PHY_MAX_SUPPORT_CARRIER_NUM];
}RRWRRC_UTRAN_CELL_INFO_LIST_STRU;


/*****************************************************************************
 消息名称  : RRWRRC_SLAVE_MEAS_REQ_STRU
 功能描述  :
 修改历史  :
  1.日    期   : 2014年1月27日
    作    者   : L00128652
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    RRC_RR_MEAS_CMD_ENUM_UINT8          enMeasCmd;
    RRC_RR_MEAS_GAS_STATUS_ENUM_UINT8   enGasStatus;                        /* G主模是否是空闲状态的标记 */
    RRWRRC_UTRAN_CELL_INFO_LIST_STRU    stUtranCellInfoLst;
}RRWRRC_SLAVE_MEAS_REQ_STRU;

/*****************************************************************************
 枚举名    : RR_WRRC_MEAS_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : G2W从模测量配置结果
*****************************************************************************/
enum RR_WRRC_MEAS_RESULT_ENUM
{
    RR_WRRC_MEAS_RESULT_SUCC                             = 0,
    RR_WRRC_MEAS_RESULT_FAIL                                ,
    RR_WRRC_MEAS_RESULT_BUTT
};
typedef VOS_UINT32  RR_WRRC_MEAS_RESULT_ENUM_UINT32;

/*****************************************************************************
 消息名称  : RRWRRC_SLAVE_MEAS_CNF_STRU
 功能描述  :
 修改历史  :
  1.日    期   : 2014年1月27日
    作    者   : L00128652
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucReserve1[2];
    RR_WRRC_MEAS_RESULT_ENUM_UINT32     enResult;
}RRWRRC_SLAVE_MEAS_CNF_STRU;

/*****************************************************************************
 结 构 名  : RRWRRC_WCELL_MEAS_RESULT_STRU
 结构说明  :
 修改历史  :
  1.日    期   : 2014年1月27日
    作    者   : L00128652
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usPrimaryCode;
    VOS_UINT8                                               aucReserved[2];
    VOS_INT16                                               sRscp;              /* 精度1/8 */
    VOS_INT16                                               sEcN0;              /* 精度1/8 */
}RRWRRC_WCELL_MEAS_RESULT_STRU;

/*****************************************************************************
 结 构 名  : RRWRRC_WCELL_MEAS_RESULT_STRU
 结构说明  :
 修改历史  :
  1.日    期   : 2014年1月27日
    作    者   : L00128652
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;
    VOS_INT16                                               sRssi;              /* 精度1/8 */
    VOS_UINT8                                               aucReserved[2];
    VOS_UINT16                                              usCellNum;
    RRWRRC_WCELL_MEAS_RESULT_STRU                           astUtranCellInfo[WRRC_RR_MAX_UTRAN_CELL_PER_FREQ_NUM];
} RRWRRC_WCELL_FREQ_MEAS_RESULT_STRU;

/*****************************************************************************
 结 构 名  : RRWRRC_SLAVE_MEAS_RESULT_STRU
 结构说明  :
 修改历史  :
  1.日    期   : 2014年1月27日
    作    者   : L00128652
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqNum;
    RRWRRC_WCELL_FREQ_MEAS_RESULT_STRU  astFreqMeasResult[WRRC_RR_MAX_UTRAN_PHY_MAX_SUPPORT_CARRIER_NUM];
} RRWRRC_SLAVE_MEAS_RESULT_STRU;

/*****************************************************************************
 消息名称  : RRWRRC_SLAVE_MEAS_IND_STRU
 功能描述  :
 修改历史  :
  1.日    期   : 2014年1月27日
    作    者   : L00128652
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    RRWRRC_SLAVE_MEAS_RESULT_STRU       stMeasResult;
}RRWRRC_SLAVE_MEAS_IND_STRU;

/*****************************************************************************
 结构名    : WRRCRR_GSM_CELL_INFO_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GSM 小区信息
 *****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCellID;                               /* 小区的ID */
    VOS_UINT8                           aucReserve1[1];
    VOS_UINT16                          usBcchArfcn;                            /*GSM的载频号*/
    RRC_GSM_BAND_INDICATOR_ENUM_UINT32  enFreqBandInd;                          /*频带指示*/
}WRRCRR_GCELL_INFO_LIST_STRU;

/*****************************************************************************
 结构名    : WRRCRR_GSM_CELL_INFO_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GSM 小区信息
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCellNum;                              /*需要测量的小区数量*/
    VOS_UINT8                           aucReserve1[2];
    WRRCRR_GCELL_INFO_LIST_STRU         astGSMCellInfo[WRRC_RR_MAX_SLAVE_GSM_CELL_NUM];
}WRRCRR_GSM_CELL_INFO_LIST_STRU;

/*****************************************************************************
 消息名称  : WRRCRR_SLAVE_MEAS_REQ_STRU
 功能描述  :
 修改历史  :
  1.日    期   : 2014年1月27日
    作    者   : L00128652
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    RRC_RR_WAS_STATUS_ENUM_UINT8        enWasStatus;
    RRC_RR_MEAS_CMD_ENUM_UINT8          enMeasCmd;
    WRRCRR_GSM_CELL_INFO_LIST_STRU      stGsmCellInfoLst;
}WRRCRR_SLAVE_MEAS_REQ_STRU;

/*****************************************************************************
 消息名称  : WRRCRR_SLAVE_MEAS_CNF_STRU
 功能描述  :
 修改历史  :
  1.日    期   : 2014年1月27日
    作    者   : L00128652
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucReserve1[2];
    RR_WRRC_MEAS_RESULT_ENUM_UINT32     enResult;
}WRRCRR_SLAVE_MEAS_CNF_STRU;

/*****************************************************************************
 结构名    : WRRCRR_SLAVE_GCELL_MEAS_RESULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 每个GSM小区测量结果
 *****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCellID;                               /* 小区的ID */
    VOS_UINT8                           aucReserve1[3];
    VOS_INT16                           sCarrierRSSI;                           /* GSM的载波强度 */
    VOS_UINT16                          usBcchArfcn;                            /* GSM的绝对载频号 */
    RRC_GSM_BAND_INDICATOR_ENUM_UINT32  enFreqBandInd;                          /* GSM的频带指示 */
} WRRCRR_SLAVE_GCELL_MEAS_RESULT_STRU;

/*****************************************************************************
 消息名称  : WRRCRR_SLAVE_GCELL_MEAS_RESULT_LIST_STRU
 功能描述  :
 修改历史  :
  1.日    期   : 2014年1月27日
    作    者   : L00128652
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                            usGsmCellNum;      /*物理层测量得到GSM载波的数量*/
    VOS_UINT8                             aucReserve1[2];
    WRRCRR_SLAVE_GCELL_MEAS_RESULT_STRU   astGsmCellResult[WRRC_RR_MAX_SLAVE_GSM_CELL_NUM];   /*GSM小区的测量结果*/
}WRRCRR_SLAVE_GCELL_MEAS_RESULT_LIST_STRU;

/*****************************************************************************
 消息名称  : WRRCRR_SLAVE_MEAS_IND_STRU
 功能描述  :
 修改历史  :
  1.日    期   : 2014年1月27日
    作    者   : L00128652
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                            MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT16                                 usOpId;
    VOS_UINT8                                  aucReserve1[2];
    WRRCRR_SLAVE_GCELL_MEAS_RESULT_LIST_STRU   stGsmCellResultList;             /*GSM小区的测量结果*/
}WRRCRR_SLAVE_MEAS_IND_STRU;

/*****************************************************************************
 结构名    : WRRCRR_GSM_CARRIER_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : BSIC Verify 请求中的GSM小区的载频信息
 *****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCellID;                               /* 小区的ID */
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT16                          usBcchArfcn;
    RRC_BSIC_INFO_ST                    stInitBsicInfo;                         /* 初始的BSIC信息 */
    RRC_GSM_BAND_INDICATOR_ENUM_UINT32  enFreqBandInd;
}WRRCRR_GSM_CARRIER_INFO_STRU;

/*****************************************************************************
 结构名    : PHYITF_DRX_BSIC_TIMER_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DRX状态(IDLE态或者PCH态)GPHY计算BSIC验证最长时间的参数
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPeriodT;
    VOS_UINT8                           ucReserve1[2];
}RRC_RR_DRX_BSIC_TIMER_PARA_STRU;

/*****************************************************************************
 结构名    : PHYITF_FACH_BSIC_TIMER_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : FACH状态GPHY计算BSIC验证最长时间的参数
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usMREP;                         /* [2，4096] frame FACHOccasion周期 */
    VOS_UINT16                                  usNTTI;                         /* Sccpch的最大TTI长度,{1,2,4,8}frame */
    PS_BOOL_ENUM_UINT8                          enInterFreqMeasExistFlag;       /* 异频测量是否存在的标记 */
    VOS_UINT8                                   ucReserve1[3];
}RRC_RR_FACH_BSIC_TIMER_PARA_STRU;

/*****************************************************************************
 结构名    : RRC_RR_DCH_BSIC_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DCH状态GPHY计算BSIC验证最长时间的参数
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTGL1;                                 /* 第一次Transmission Gap的长度包括TGP断开时*/
    VOS_UINT16                          usTGL2;                                 /* 第二次Transmission Gap的长度包括TGP PATTERN*/
    VOS_UINT16                          usTGD;                                   /* Transmission gap distance                */
    VOS_UINT16                          usTGPL1;                                /* TGP1的持续                               */
}RRC_RR_DCH_BSIC_PARA_STRU;

/*****************************************************************************
 结构名    : PHYITF_DCH_BSIC_TIMER_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DCH状态GPHY计算BSIC验证最长时间的参数
 *****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                 enReConfirmParaValidFlag;                /* 重确认压模参数是否存在的标记 */
    VOS_UINT8                          ucReserve1[3];
    RRC_RR_DCH_BSIC_PARA_STRU          stInitBsicTimerPara;                     /* D态初始确认GPHY计算BSIC验证最长时间的参数 */ 
    RRC_RR_DCH_BSIC_PARA_STRU          stReConfirmBsicTimerPara;                /* D态重确认GPHY计算BSIC验证最长时间的参数 */ 
}RRC_RR_DCH_BSIC_TIMER_PARA_STRU;

/*****************************************************************************
 消息名称  : WRRCRR_BSIC_VERIFIED_REQ_STRU
 功能描述  :
 修改历史  :
  1.日    期   : 2014年1月27日
    作    者   : L00128652
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                         MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT8                               ucReserve1[2];
    VOS_UINT16                              usGsmCarrierNum;
    WRRCRR_GSM_CARRIER_INFO_STRU            astGSMCarrierInfo[WRRC_RR_MAX_SLAVE_GSM_BSIC_RPT_CELL_NUM];
    RRC_RR_WAS_STATUS_ENUM_UINT8            enWasStatus;                        /* _H2ASN_IeChoice_Export RRC_RR_WAS_STATUS_ENUM_UINT8 */
    VOS_UINT8                               ucReserve2[3];
    union                                                                       /*_H2ASN_Skip*/
    {                                                                           /*_H2ASN_Skip*/
        RRC_RR_DRX_BSIC_TIMER_PARA_STRU          stDrxBsicTimerPara;            /*_H2ASN_Skip*//* DRX状态(IDLE态或者PCH态)GPHY计算BSIC验证最长时间的参数 */ 
        RRC_RR_FACH_BSIC_TIMER_PARA_STRU         stFachBsicTimerPara;           /*_H2ASN_Skip*//* FACH状态GPHY计算BSIC验证最长时间的参数 */ 
        RRC_RR_DCH_BSIC_TIMER_PARA_STRU          stDchBsicTimerPara;            /* DCH状态GPHY计算BSIC验证最长时间的参数 */ 
        /******************************************************************************************************
            _H2ASN_IeChoice_When        RRC_RR_WAS_STATUS_ENUM_UINT8
        ******************************************************************************************************/
    } u;                                                                        /*_H2ASN_Skip*/
}WRRCRR_BSIC_VERIFIED_REQ_STRU;

/*****************************************************************************
 消息名称  : WRRCRR_BSIC_VERIFIED_CNF_STRU
 功能描述  :
 修改历史  :
  1.日    期   : 2014年1月27日
    作    者   : L00128652
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[4];
}WRRCRR_BSIC_VERIFIED_CNF_STRU;

/*****************************************************************************
 结构名    : WRRCRR_BSIC_VERIFIED_RESULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : BSIC Verify 指示中的GSM载频测量结果
 *****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCellID;                               /* 小区的ID */
    VOS_UINT8                           aucReserve1[1];
    VOS_UINT16                          usBcchArfcn;
    RRC_GSM_BAND_INDICATOR_ENUM_UINT32  enFreqBandInd;
    RRC_BSIC_INFO_ST                    stBsic;
    VOS_UINT8                           aucReserve2[2];
    VOS_UINT16                          usObservedTimeDiffToGSMCell;            /* 这个是否还需要liuyin */
    VOS_UINT16                          usTimeAlignmt;
    VOS_INT32                           lFNOffset;
} WRRCRR_BSIC_VERIFIED_RESULT_STRU;

/*****************************************************************************
 消息名称  : WRRCRR_BSIC_VERIFIED_IND_STRU
 功能描述  :
 修改历史  :
  1.日    期   : 2014年1月27日
    作    者   : L00128652
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT16                          usGsmCarrierNum;
    VOS_UINT8                           aucReserve1[2];
    WRRCRR_BSIC_VERIFIED_RESULT_STRU    astGSMCarrierResult[WRRC_RR_MAX_SLAVE_GSM_BSIC_RPT_CELL_NUM];
}WRRCRR_BSIC_VERIFIED_IND_STRU;

/*****************************************************************************
 消息名称  : WRRCRR_RELEASE_ALL_REQ_STRU
 功能描述  :
 修改历史  :
  1.日    期   : 2014年1月27日
    作    者   : L00128652
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */
    RRC_RR_REL_REASON_ENUM_UINT8        enRelReason;                            /* 释放原因 */ 
    VOS_UINT8                           aucReserve1[3];
}WRRCRR_RELEASE_ALL_REQ_STRU;

/*****************************************************************************
 消息名称  : WRRCRR_RELEASE_ALL_CNF_STRU
 功能描述  :
 修改历史  :
  1.日    期   : 2014年1月27日
    作    者   : L00128652
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[4];
}WRRCRR_RELEASE_ALL_CNF_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    RR_WRRC_MSG_TYPE_ENUM_UINT16        enMsgID;    /*_H2ASN_MsgChoice_Export RR_WRRC_MSG_TYPE_ENUM_UINT32*/
                                                    /* 为了兼容GAS的消息头定义，所以转换ASN.1使用GAS_RRC_MSG_TYPE_ENUM_UINT32 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          RR_WRRC_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}RR_WRRC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    RR_WRRC_MSG_DATA                    stMsgData;
}GasRrWrr_MSG;

#define RRWRR_INVALID_SCRAMBLING_CODE            0xFFFF
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

#endif /* end of GasRrWrr.h*/
