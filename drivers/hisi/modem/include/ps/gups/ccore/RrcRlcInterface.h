/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : RrcRlcInterface.h
  版 本 号   : 初稿
  作    者   : Jinying
  生成日期   : 2006年8月31日
  最近修改   :
  功能描述   : RrcRlcInterface.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2006年8月31日
    作    者   : liukai 53535
    修改内容   : 创建文件
  2.日    期   : 2010年1月27日
    作    者   : 施海军62578 何峰 163499
    修改内容   : 增加Special HE支持功能

******************************************************************************/

#ifndef __RRCRLCINTERFACE_H__
#define __RRCRLCINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
/* WCDMA协议栈各个子系统公共的数据结构 */
#include "PsTypeDef.h"
#include "WUe.h"
#include "WUeL2L3.h"
#include "WUeSpec.h"

#pragma pack(4)

/*****************************************************************************
  1 消息类型定义
*****************************************************************************/
enum RRC_RLC_MSG_TYPE_ENUM
{
    ID_RRC_RLC_AM_DATA_REQ              =  0x0000,      /* _H2ASN_MsgChoice RRC_RLC_AM_DATA_REQ_STRU */
    ID_RLC_RRC_AM_DATA_CNF              =  0x0001,      /* _H2ASN_MsgChoice RLC_RRC_AM_DATA_CNF_STRU */
    ID_RRC_RLC_UM_DATA_REQ              =  0x0002,      /* _H2ASN_MsgChoice RRC_RLC_UM_DATA_REQ_STRU */
    ID_RLC_RRC_AM_DATA_IND              =  0x0003,      /* _H2ASN_MsgChoice RLC_RRC_AM_DATA_IND_STRU */
    ID_RRC_RLC_TM_DATA_REQ              =  0x0004,      /* _H2ASN_MsgChoice RRC_RLC_TM_DATA_REQ_STRU */
    ID_RLC_RRC_UM_DATA_IND              =  0x0005,      /* _H2ASN_MsgChoice RLC_RRC_UM_DATA_IND_STRU */
    ID_RRC_RLC_AM_CONFIG_REQ            =  0x0006,      /* _H2ASN_MsgChoice RRC_RLC_AM_CONFIG_REQ_STRU */
    ID_RLC_RRC_TM_DATA_IND              =  0x0007,      /* _H2ASN_MsgChoice RLC_RRC_TM_DATA_IND_STRU */
    ID_RRC_RLC_UM_CONFIG_REQ            =  0x0008,      /* _H2ASN_MsgChoice RRC_RLC_UM_CONFIG_REQ_STRU */
    ID_RLC_RRC_CONFIG_CNF               =  0x0009,      /* _H2ASN_MsgChoice RLC_RRC_CONFIG_CNF_STRU */
    ID_RRC_RLC_TM_CONFIG_REQ            =  0x000a,      /* _H2ASN_MsgChoice RRC_RLC_TM_CONFIG_REQ_STRU */
    ID_RLC_RRC_RELEASE_CNF              =  0x000b,      /* _H2ASN_MsgChoice RLC_RRC_RELEASE_CNF_STRU */
    ID_RRC_RLC_RELEASE_REQ              =  0x000c,      /* _H2ASN_MsgChoice RRC_RLC_RELEASE_REQ_STRU */
    ID_RLC_RRC_SUSPEND_CNF              =  0x000d,      /* _H2ASN_MsgChoice RLC_RRC_SUSPEND_CNF_STRU */
    ID_RRC_RLC_SUSPEND_REQ              =  0x000e,      /* _H2ASN_MsgChoice RRC_RLC_SUSPEND_REQ_STRU */
    ID_RLC_RRC_RESUME_CNF               =  0x000f,      /* _H2ASN_MsgChoice RLC_RRC_RESUME_CNF_STRU */
    ID_RRC_RLC_RESUME_REQ               =  0x0010,      /* _H2ASN_MsgChoice RRC_RLC_RESUME_REQ_STRU */
    ID_RLC_RRC_STOP_CNF                 =  0x0011,      /* _H2ASN_MsgChoice RLC_RRC_STOP_CNF_STRU */
    ID_RRC_RLC_STOP_REQ                 =  0x0012,      /* _H2ASN_MsgChoice RRC_RLC_STOP_REQ_STRU */
    ID_RLC_RRC_CONTINUE_CNF             =  0x0013,      /* _H2ASN_MsgChoice RLC_RRC_CONTINUE_CNF_STRU */
    ID_RRC_RLC_CONTINUE_REQ             =  0x0014,      /* _H2ASN_MsgChoice RRC_RLC_CONTINUE_REQ_STRU */
    ID_RLC_RRC_STATUS_IND               =  0x0015,      /* _H2ASN_MsgChoice RLC_RRC_STATUS_IND_STRU */
    ID_RRC_RLC_MODE_CHANGE_REQ          =  0x0016,      /* _H2ASN_MsgChoice RRC_RLC_MODE_CHANGE_REQ_STRU */
    ID_RLC_RRC_ULDATA_TX_IND            =  0x0017,      /* _H2ASN_MsgChoice RLC_RRC_ULDATA_TX_IND_STRU */
    ID_RRC_RLC_CIPHER_CONFIG_REQ        =  0x0018,      /* _H2ASN_MsgChoice RRC_RLC_CIPHER_CONFIG_REQ_STRU */

    ID_RLC_RRC_MODE_CHANGE_CNF          =  0x0019,      /* _H2ASN_MsgChoice RLC_RRC_MODE_CHANGE_CNF_STRU */

    ID_RLC_RRC_CIPHER_CONFIG_CNF        =  0x001b,      /* _H2ASN_MsgChoice RLC_RRC_CIPHER_CONFIG_CNF_STRU */
    ID_RLC_RRC_CIPHERING_ACTIVE_IND     =  0x001d,      /* _H2ASN_MsgChoice RLC_RRC_CIPHER_ACTIVE_IND_STRU */
    ID_RLC_RRC_MSG_TYPE_BUTT
};
typedef VOS_UINT16 RRC_RLC_MSG_TYPE_ENUM_UINT16;


/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 针对CTCH定义的特殊RB ID，在UM RLC建立，释放时使用 */
#define RLCITF_CTCH_RB_ID               33

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 结构名    : RLCITF_DISCARD_MODE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : 配置SDU丢弃模式
*****************************************************************************/
enum RLCITF_DISCARD_MODE_ENUM
{
    RLCITF_TIMER_EXP                    = 0,            /* Timer based discard */
    RLCITF_MAXDAT_RETX                  = 1,            /* SDU discard after MaxDAT number of transmission */
    RLCITF_NO_DISCARD                   = 2,            /* No discard */
    RLCITF_DISCARD_MODE_BUTT
};
typedef VOS_UINT8 RLCITF_DISCARD_MODE_ENUM_UINT8;

/*****************************************************************************
 结构名    : RRC_RLC_CFG_MODE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_RLC_AM_CONFIG_REQ原语操作类别
*****************************************************************************/
enum RRC_RLC_CFG_MODE_ENUM
{
    RRC_RLC_CFG_MODE_SETUP              = 0,            /* 对AM/UM/TM RLC实体的建立 */
    RRC_RLC_CFG_MODE_REEST              = 1,            /* 对AM/UM    RLC实体的重建 */
    RRC_RLC_CFG_MODE_MODIFY             = 2,            /* 对AM/UM/TM RLC实体参数的修改 */
    RRC_RLC_CFG_MODE_NO_CHANGE          = 3,            /* 对AM/UM/TM RLC实体的配置不变 */
    RRC_RLC_CFG_MODE_BUTT
} ;
typedef VOS_UINT8 RRC_RLC_CFG_MODE_ENUM_UINT8;

/*****************************************************************************
 结构名    : RLCITF_AM_REEST_SIDE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : AM实体重建上下行指示
*****************************************************************************/
enum RLCITF_AM_REEST_SIDE_ENUM
{
    RLCITF_AM_TX_REEST                 = 0,             /* AM实体发送端重建 */
    RLCITF_AM_RX_REEST                 = 1,             /* AM实体接收端重建 */
    RLCITF_AM_BOTH_REEST               = 2,             /* AM实体接收端/发送端重建 */
    RLCITF_AM_REEST_BUTT
};
typedef VOS_UINT8 RLCITF_AM_REEST_SIDE_ENUM_UINT8;

/*****************************************************************************
 结构名    : RLCITF_EVENT_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC层发生需要上报的事件类别
*****************************************************************************/
enum RLCITF_EVENT_TYPE_ENUM
{
    RLCITF_EVENT_DATALINK_LOSS          = 0,            /* RLC层发生数据链路丢失事件                */
    RLCITF_EVENT_RESET                  = 1,            /* RLC层发生RESET事件                       */
    RLCITF_EVENT_UM_DECIPHER_ABNORMAL   = 2,            /* RLC层发生下行UM解密异常事件                       */

    RLCITF_EVENT_BUTT
};
typedef VOS_UINT8 RLCITF_EVENT_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名    : RLCITF_TM_SDU_ERR_ACT_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : TM SDU CRC Fail deliver methord
*****************************************************************************/
enum RLCITF_TM_SDU_ERR_ACT_TYPE_ENUM
{
    RLC_TM_CRC_FAIL_SDU_NULL            =   0x000,      /*为方便IT测试时做消息，增加该项，无其他意义 */
    RLC_TM_CRC_FAIL_SDU_NO_DETECT       =   0x001,      /*不检测SDU是否正确*/
    RLC_TM_CRC_FAIL_SDU_DELIVER         =   0x010,      /*检测到错误时，将错误SDU传送给上层*/
    RLC_TM_CRC_FAIL_SDU_NO_DELIVER      =   0x011,      /*检测到错误时，直接将SDU丢弃 */
    RLC_TM_CRC_FAIL_BUTT
} ;
typedef VOS_UINT8 RLCITF_TM_SDU_ERR_ACT_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名    : RLCITF_RSLT_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC配置结果
*****************************************************************************/
enum RLCITF_RSLT_ENUM
{
    RLCITF_SUCC                         = 0,
    RLCITF_FAIL                            ,

    RLCITF_RSLT_BUTT
};
typedef VOS_UINT32   RLCITF_RSLT_ENUM_UINT32;

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
 结构名    : RLCITF_POLL_INFO_STRU
 协议表格  : 10.3.4.4 Polling info
 ASN.1描述 : PollingInfo
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTimerPollProh;    /* Timer_Poll_Prohibit定时器初值, 为0时表示未配置该定时器 10..550 by step of 10; 600..1000 by step of 50; 0 */
    VOS_UINT16                          usTimerPoll;        /* Timer_Poll定时器初值, 为0时表示未配置该定时器 10..550 by step of 10; 600..1000 by step of 50; 0 */
    VOS_UINT8                           ucPollPdu;          /* 每发送该参数指定个数的PDU时触发一次POLL, 为0时表示未配置此触发方式 0, 1, 2, 4, 8, 16, 32, 64, 128 */
    VOS_UINT8                           ucPollSdu;          /* 每发送该参数指定个数的SDU时触发一次POLL, 为0时表示未配置此触发方式 0, 1, 4, 16, 64 */
    PS_BOOL_ENUM_UINT8                  enLastTxPduPoll;    /* 在TX BUF中最后一个PDU被发送时是否进行POLL */
    PS_BOOL_ENUM_UINT8                  enLastReTxPduPoll;  /* 在RETX BUF中最后一个PDU被发送时是否进行POLL */
    VOS_UINT8                           ucPollWnd;          /* 状态变量J大于等于该值时触发一次POLL, 为0时表示未配置此触发方式 0, 50, 60, 70, 80, 85, 90, 95, 99 */
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */
    VOS_UINT16                          usTimerPollPrd;     /* Timer_Poll_Periodic定时器初值, 为0时表示未配置该定时器 0, 100, 200, 300, 400, 500, 750, 1000, 2000 */
}RLCITF_POLL_INFO_STRU;

/*****************************************************************************
 结构名    : RLCITF_EXPLI_DISCARD_STRU
 协议表格  :
 ASN.1描述 : ExplicitDiscard
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTimerMrw;         /*  单位ms. Timer_MRW定时器初值, 该定时器用来触发MRW SUFI的重传.
                                                               Integer(50,60, 70, 80, 90, 100, 120, 140, 160, 180, 200, 300, 400, 500, 700, 900) */
    VOS_UINT16                          usTimerDiscard;     /*  单位ms.Timer_discard定时器初值, 该定时器用来触发发送侧相应SDU的丢弃 100,
                                                                250, 500, 750, 1000, 1250, 1500, 1750, 2000, 2500, 3000, 3500, 4000,
                                                                4500, 5000, 7500*/
    VOS_UINT8                           ucMaxMrw;           /*MRW SUFI可以被重传的最大次数 1, 4, 6, 8, 12 16, 24, 32*/
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
} RLCITF_EXPLI_DISCARD_STRU;

/*****************************************************************************
 结构名    : RLCITF_MAX_DAT_RETRANS_STRU
 协议表格  :
 ASN.1描述 : MaxDAT_Retransmissions
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMaxDat;           /*  当一个AMD PDU重传次数超过该值时, 丢弃该PDU中包含的所有SDU segments
                                                                1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 20, 25, 30, 35, 40*/
    VOS_UINT8                           ucMaxMrw;           /*  MRW SUFI可以被重传的最大次数 1, 4, 6, 8, 12 16, 24, 32 */
    VOS_UINT16                          usTimerMrw;         /*  单位ms.Timer_MRW定时器初值,该定时器用来触发MRWSUFI的重传 50, 60,
                                                                70,80, 90, 100, 120,140, 160, 180, 200,300, 400, 500, 700,900*/
} RLCITF_MAX_DAT_RETRANS_STRU;


/*****************************************************************************
 结构名    : RLCITF_DISCARD_MODE_CHOICE_STRU
 协议表格  : 10.3.4.25 Transmission RLC Discard
 ASN.1描述 : TransmissionRLC_Discard
 结构说明  : RLC的丢弃模式
*****************************************************************************/
typedef struct
{
    #define    RLCITF_TIMER_BASED_EXPLI_DISCARD_MODE_CHOSEN        0
    #define    RLCITF_TIMER_BASED_NO_EXPLI_DISCARD_MODE_CHOSEN     1
    #define    RLCITF_MAX_DAT_RETRANS_DISCARD_MODE_CHOSEN          2
    #define    RLCITF_NO_DISCARD_DISCARD_MODE_CHOSEN               3

    VOS_UINT32                          ulChoice;

    union
    {
        RLCITF_EXPLI_DISCARD_STRU       stTimerBasedExpli;  /* 丢弃模式为Timer based discard with
                                                               explicit signaling时的丢弃参数配置     */
        VOS_UINT8                       ucTimerBasedNoExpli;/* Elapsed time in milliseconds before a SDU is discarded.
                                                               10,20,30,40,50,60,70,80,90,100  */
        RLCITF_MAX_DAT_RETRANS_STRU     stMaxDatRetrans;    /* 丢弃模式为SDU discard after MaxDAT
                                                               number of transmission时的丢弃参数配置 */
        VOS_UINT8                       ucNoDisMaxDat;      /* 丢弃模式为No discard时的丢弃参数配置 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 20, 25, 30, 35, 40 */
    } u;
}RLCITF_DISCARD_MODE_CHOICE_STRU;

/*****************************************************************************
 结构名    : RLCITF_UL_AM_RLC_STRU
 协议表格  :
 ASN.1描述 : UL_AM_RLC_Mode
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitPollInfo    : 1;
    VOS_UINT32                          bitSpare       : 31;

    RLCITF_DISCARD_MODE_CHOICE_STRU     stRlcDiscardMode;
    /* ASN.1 文本 : TransmissionWindowSize */
    VOS_UINT16                          usTxWndSize;        /* 发送窗长度 1, 8, 16, 32, 64, 128, 256, 512, 768, 1024, 1536, 2047, 2560, 3072, 3584, 4095                    */
    /* ASN.1 文本 : TimerRST */
    VOS_UINT16                          usTimerRst;         /* Timer_RST定时器初值 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 700, 800, 900, 1000           */
    /* ASN.1 文本 : MaxRST */
    VOS_UINT8                           ucMaxRst;           /* RESET PDU可以被重传的最大次数 1, 4, 6, 8, 12 16, 24, 32 */
    PS_BOOL_ENUM_UINT8                  enSendMrwInd;       /* 如果该RLC实体是PS域，并且满足"Support for lossless SRNS relocation or for lossless DL RLC PDU size change"，则配置为PS_TRUE;*/
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
    RLCITF_POLL_INFO_STRU               stPollInfo;         /* POLL配置 */
}RLCITF_UL_AM_RLC_STRU;

/*****************************************************************************
 结构名    : RLCITF_DL_RLC_STATUS_INFO_STRU
 协议表格  : 10.3.4.1 Downlink RLC STATUS info
 ASN.1描述 : DL_RLC_StatusInfo
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTimerStaProh;     /* 单位ms.Timer_Status_Prohibit定时器初值, 为0时表示未配置该定时器 10..550 by step of 10; 550..1000 by step of 50; */
    VOS_UINT16                          usTimerStaPeriod;   /* 单位ms.Timer_Status_Periodic定时器初值, 为0时表示未配置该定时器 0, 100, 200, 300, 400, 500, 750, 1000, 2000 */
    PS_BOOL_ENUM_UINT8                  enMissPduInd;       /* 接收侧检测到RLC PDU丢失时是否发送状态报告 */
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */
}RLCITF_DL_RLC_STATUS_INFO_STRU;

/*V3 R7_7C1 Start */

/*Flexible Size*/
enum   RLCITF_FLEX_RLC_PDU_SIZE_LI_SIZE_ENUM
{
    RLCITF_LI_SIZE_FOR_FLEXIBLE_PDU_SIZE_7_BIT        = 7,
    RLCITF_LI_SIZE_FOR_FLEXIBLE_PDU_SIZE_15_BIT       = 15,
    RLCITF_LI_SIZE_FOR_FLEXIBLE_PDU_SIZE_BUTT
};

typedef VOS_UINT16   RLCITF_FLEX_RLC_PDU_SIZE_LI_SIZE_ENUM_UINT16;

/*****************************************************************************
 结构名    : DL_RLC_PDU_SIZE_CHOICE_STRU
 协议表格  : 10.3.4.23 RLC info
 ASN.1描述 : CHOICE DL RLC PDU size
 结构说明  : DL RLC PDU size 选择
*****************************************************************************/

typedef struct
{
#define    RLCITF_DL_AM_PDU_FIXED_SIZE_CHOSEN        0/*Fixed size*/
#define    RLCITF_DL_AM_PDU_FLEXIBLE_SIZE_CHOSEN     1/*Flexible size*/

    VOS_UINT32                          ulChoice;
    union
    {
        VOS_UINT16                                          usDlRlcAmPduFixedSize;                  /*Fixed size的DL RLC PDU size，单位bit,Integer(16..5000 by step of 8)*/
        RLCITF_FLEX_RLC_PDU_SIZE_LI_SIZE_ENUM_UINT16        enDlRlcAmPduLiSizeForFlexibleSize;      /*Flexible Size: 7bits or 15bits  */
    } u;
    VOS_UINT8                           aucRsv[2];
}RLCITF_DL_AM_PDU_SIZE_CHOICE_STRU;
/* V3 R7_7C1 End */

/*****************************************************************************
 结构名    : RLCITF_DL_AM_RLC_STRU
 协议表格  :
 ASN.1描述 : DL_AM_RLC_Mode
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitDlRlcPduSize    : 1;/*当stDlRlcPduSize.ulChoice 为FIXED_SIZE时， 0: AMD PDU size is not configured
                                                                 当stDlRlcPduSize.ulChoice 为FLEXIBLE_SIZE时   无效*/
    VOS_UINT32                          bitSpare           : 31;

    /*V3 R7_7C1 Start */
    RLCITF_DL_AM_PDU_SIZE_CHOICE_STRU   stDlRlcPduSize;     /*DL RLC PDU size*/
    PS_BOOL_ENUM_UINT8                  enInSeqDeliv;       /* 是否按SN顺序向上层提交SDU */
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    /* V3 R7_7C1 End */

    VOS_UINT16                          usRxWndSize;        /* 接收窗长度 1, 8, 16, 32, 64, 128, 256, 512, 768, 1024, 1536, 2047, 2560, 3072, 3584, 4095   */
    RLCITF_DL_RLC_STATUS_INFO_STRU      stDlRlcStaInfo;
}RLCITF_DL_AM_RLC_STRU;

/*****************************************************************************
 结构名    : RLCITF_UL_UM_RLC_STRU
 协议表格  :
 ASN.1描述 : UL_UM_RLC_Mode
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitTxRlcDiscard       : 1;
    VOS_UINT32                          bitSpare              : 31;

    /* 10.3.4.25    Transmission RLC Discard */
    /* UM RLC丢弃参数可选，如果配置，只能配置非显示丢弃 */
    VOS_UINT8                           ucTimerBasedNoExpli;/* Elapsed time in milliseconds before a SDU is discarded.
                                                               10,20,30,40,50,60,70,80,90,100  */
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
}RLCITF_UL_UM_RLC_STRU;

/*****************************************************************************
 结构名    : RLCITF_DL_UM_RLC_STRU
 协议表格  :
 ASN.1描述 : DL_UM_RLC_Mode_r6
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitDlUmRlcLiSize    : 1;
    VOS_UINT32                          bitDlRecpWinSize    : 1;
    VOS_UINT32                          bitSpare            : 30;

    VOS_UINT8                           ucDlUmRlcLiSize;    /* R5新增, 7, 15 */
    VOS_UINT8                           ucDlRecpWinSize;    /* R6新增,MBMS功能，暂不使用，32, 48, 64, 80, 96, 112 */
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
}RLCITF_DL_UM_RLC_STRU;

/*****************************************************************************
 结构名    : RLCITF_UL_TM_RLC_STRU
 协议表格  :
 ASN.1描述 : UL_TM_RLC_Mode
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitTxRlcDiscard      : 1;
    VOS_UINT32                          bitSpare             : 31;

    /* TM RLC丢弃参数可选，如果配置，只能配置非显示丢弃 */
    VOS_UINT8                           ucTimerBasedNoExpli;/* Elapsed time in milliseconds before a SDU is discarded.
                                                               10,20,30,40,50,60,70,80,90,100  */
    PS_BOOL_ENUM_UINT8                  enSegInd;           /* 分段指示 */
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
}RLCITF_UL_TM_RLC_STRU;

/*****************************************************************************
 结构名    : RLCITF_DL_TM_RLC_STRU
 协议表格  :
 ASN.1描述 : DL_TM_RLC_Mode
 结构说明  :
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enSegInd;           /* 分段指示 */
    RLCITF_TM_SDU_ERR_ACT_TYPE_ENUM_UINT8     enErrSduInd;  /* CRC fail SDU传送指示   */
    VOS_UINT8                               aucReserve1[2];     /* 4字节对齐，保留 */
}RLCITF_DL_TM_RLC_STRU;

/*****************************************************************************
 结构名    : RLCITF_SUSPEND_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucRbId;             /* 要挂起数据传输的RB号, [1, 31]  */
    VOS_UINT16                          usN;                /* 挂起前可继续传送的PDU数目, 简化实现，RRC固定配为0 AM: [0, 4096] UM:[0, 1024]*/
}RLCITF_SUSPEND_INFO_STRU;

/*****************************************************************************
 结构名    : RLCITF_RLC_SN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucRbId;             /* radio bear identity, [1, 31] */
    VOS_UINT16                          usCurSn;            /* VT(S)/VT(US) */
}RLCITF_RLC_SN_STRU;

/*****************************************************************************
 结构名    : RLCITF_RB_CIPHER_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitUlActTimeRlcSn        : 1;
    VOS_UINT32                          bitDlActTimeRlcSn        : 1;
    VOS_UINT32                          bitSpare                 : 30;

    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucRbId;             /* RB标识,对应的CN域标识, 在RLC配置消息中提供 [1, 31] */
    VOS_INT16                           sUlActTimeRlcSn;    /* -1表示立即激活，上行加密激活时间; RLC SN, AM:0..4095, UM:0..127 */
    VOS_INT16                           sDlActTimeRlcSn;    /* -1表示立即激活，下行加密激活时间; RLC SN, AM:0..4095, UM:0..127 */
}RLCITF_RB_CIPHER_INFO_STRU;

/*****************************************************************************
 结构名    : RRC_RLC_AM_DATA_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 配置AM RLC
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /*_H2ASN_Skip*/

    VOS_UINT8                           ucRbId;             /* 发送上层PDU使用的RB号, [2, 32]     */
    PS_BOOL_ENUM_UINT8                  enCnfIndFlg;        /* 当AM RLC实体确认对端接收到RLC SDU后,
                                                            是否需要使用RLC_RRC_AM_DATA_CNF原语向高层发送确认 */
    VOS_UINT32                          ulMui;              /* 上层PDU编号 */
    PS_BOOL_ENUM_UINT8                  enDiscardIndFlg;    /* 该IE暂不使用，当上层PDU被丢弃时,是否需要使用RLC_RRC_AM_DATA_CNF原语向上层指示*/
    PS_BOOL_ENUM_UINT8                  enNeedProtect;      /* 是否需要信令保护 */
    VOS_UINT16                          usDataLen;          /* 数据部分长度, 单位: byte         */
    VOS_UINT8                           aucData[4];         /* 上层数据,与前面的参数一起占据连续的消息包内存 */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}RRC_RLC_AM_DATA_REQ_STRU;

/*****************************************************************************
 结构名    : RLC_RRC_AM_DATA_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 配置AM RLC响应
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /*_H2ASN_Skip*/

    VOS_UINT8                           ucRbId;             /* 发送上层PDU使用的RB号, [2, 31]    */
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */
    VOS_UINT32                          ulMui;              /* 上层PDU编号 */
    RLCITF_RSLT_ENUM_UINT32             enRslt;             /* 上层PDU发送结果 */
}RLC_RRC_AM_DATA_CNF_STRU;

/*****************************************************************************
 结构名    : RRC_RLC_UM_DATA_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 配置UM RLC
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /*_H2ASN_Skip*/

    VOS_UINT8                           ucRbId;             /* 发送上层PDU使用的RB号, 1, 5-31     */
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    VOS_UINT16                          usDataLen;          /* 数据部分长度, 单位: byte          */
    VOS_UINT8                           aucData[4];         /* 上层数据,与前面的参数一起占据连续的消息包内存 */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}RRC_RLC_UM_DATA_REQ_STRU;

/*****************************************************************************
 结构名    : RLC_RRC_AM_DATA_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : AM RLC的数据上报
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /*_H2ASN_Skip*/
    VOS_UINT8                           ucRbId;             /* 接收到上层PDU的RB号 */
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    VOS_UINT16                          usDataLen;          /* 数据部分长度, 单位: byte     */
    VOS_UINT8                           aucData[4];         /* 上层数据,与前面的参数一起占据连续的消息包内存 */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}RLC_RRC_AM_DATA_IND_STRU;

/*****************************************************************************
 结构名    : RLC_RRC_UM_DATA_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : UM RLC的数据上报
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /*_H2ASN_Skip*/

    VOS_UINT8                           ucRbId;             /* 接收到上层PDU的RB号, 0-1, 5-31 */

    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    VOS_UINT16                          usDataLen;          /* 数据部分长度, 单位: byte     */
    VOS_UINT8                           aucData[4];         /* 上层数据,与前面的参数一起占据连续的消息包内存 */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}RLC_RRC_UM_DATA_IND_STRU;

/*****************************************************************************
 结构名    : RLC_RRC_TM_DATA_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TM RLC的数据上报
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /*_H2ASN_Skip*/

    VOS_UINT8                           ucRbId;             /* 接收到上层PDU的RB号, 5-31     */

    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */
    VOS_UINT32                          ulDatabitLen;       /* 提交的上层PDU的长度, 单位: bit  */

    VOS_UINT8                           aucData[4];         /* 上层数据,与前面的参数一起占据连续的消息包内存 */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}RLC_RRC_TM_DATA_IND_STRU;

/*****************************************************************************
 结构名    : RRC_RLC_TM_DATA_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TM RLC的数据下发
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /*_H2ASN_Skip*/

    VOS_UINT8                           ucRbId;             /* 发送上层PDU使用的RB号, 0, 5-31        */

    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */
    VOS_UINT32                          ulDataBitLen;       /* 上层PDU数据长度, 单位: bit  */
    VOS_UINT8                           aucData[4];         /* 上层数据,与前面的参数一起占据连续的消息包内存 */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}RRC_RLC_TM_DATA_REQ_STRU;

/*****************************************************************************
 结构名    : RLCITF_UL_LOCH_RLC_PDU_FIXED_SIZE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上行逻辑信道PDUSize列表, 单位: Bit
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve[3];

    VOS_UINT8                           ucPduSizeCnt;       /* 上行逻辑信道可使用的PduSize的种类数*/
    VOS_UINT16                          ausPduSize[PS_WUE_MAX_RLC_PDU_SIZE_NUM_PER_LOCH];/*该数组下标与RrcMacInterface.h接口中的MACITF_RACH_DCH_LOCH_MAPP_STRU中aucRlcSizeIdx[PS_WUE_MAX_RLC_PDU_SIZE_NUM_PER_LOCH]的数组下标排列顺序一致
                                                                                           根据25.331 8.6.5.1   Transport Format Set的描述，
                                                                                           DCCH/DTCH:
                                                                                           如果该逻辑信道映射到DCH，  那么，数组元素值就是RrcMacInterface.h接口中TFS对应的RLC SIZE值;
                                                                                           如果该逻辑信道映射到RACH， 那么，数组元素值是RrcMacInterface.h接口中TFS对应的RLC SIZE值 - 24bit(TCTF、UE-Id type、C-RNTI、C/T);
                                                                                           如果该逻辑信道映射到E-DCH，那么，数组元素值是RrcMacInterface.h接口中RB MAPPING中对应的RLC SIZE值
                                                                                           CCCH:
                                                                                           如果该逻辑信道映射到RACH， 那么，数组元素值是RrcMacInterface.h接口中TFS对应的RLC SIZE值 - 2bit(TCTF)
                                                                                         */
}RLCITF_UL_LOCH_RLC_PDU_FIXED_SIZE_STRU;


/*****************************************************************************
 结构名    : RLCITF_UL_LOCH_RLC_PDU_FLEX_SIZE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : UL RLC PDU flexible SIZE
             对于UL AM MODE RLC,LI必存在，UM TM模式，LI不存在.
             见协议25.331: If "CHOICE Uplink RLC mode" in the IE "RLC info"
             that applies for that RB  is "AM RLC " this IE is mandatory present.
             Otherwise the IE is not needed
             MinRlcPduSize，usLargestRlcPduSize 25.322对于TM模式没有描述使用，
             目前理解TM网络不配置配置FLEXIBLE size
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                       aucReserve1[2];             /* 4字节对齐，保留 */
    RLCITF_FLEX_RLC_PDU_SIZE_LI_SIZE_ENUM_UINT16    enLenIndSize;               /* 不存在LI时填写BUTT */
    VOS_UINT16                                      usMinRlcPduSize;            /* Integer (16..12040 by step of 8) */
    VOS_UINT16                                      usLargestRlcPduSize;        /* Integer (16..12040 by step of 8) */
}RLCITF_UL_LOCH_RLC_PDU_FLEX_SIZE_STRU;

/*****************************************************************************
 结构名    : RLCITF_UL_LOCH_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC的逻辑信道配置
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[2];                         /* 4字节对齐，保留 */
    VOS_UINT8                           ucLochLabel;                            /* 逻辑信道内部实现统一标识：[0,34*2-1] */
    VOS_UINT8                           ucLochPrio;                             /* [1,8],上行逻辑信道优先级,数字越小,优先级越高 */

    #define    RLCITF_RLC_PDU_SIZE_FIXED_SIZE   0                               /* Fixed size */
    #define    RLCITF_RLC_PDU_SIZE_FLEX_SIZE    1                               /* Flexible size */

    VOS_UINT32                                  ulChoice;

    union
    {
        RLCITF_UL_LOCH_RLC_PDU_FIXED_SIZE_STRU  stFixedSize;                    /* Fixed size */
        RLCITF_UL_LOCH_RLC_PDU_FLEX_SIZE_STRU   stFlexSize;                     /* Flexible Size */
    } u;

}RLCITF_UL_LOCH_INFO_STRU;

/*****************************************************************************
 结构名    : RLCITF_UL_LOCH_INFO_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上行逻辑信道映射，一个RB可能映射1个或者2个逻辑信道
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucLochCnt;          /* RB映射的逻辑信道个数 */
    RLCITF_UL_LOCH_INFO_STRU            astUlLochInfo[PS_WUE_MAX_LOCH_PER_RLC_NUM];/*数组下标为0时对应第一个逻辑信道, 数组下标为1时对应第二个逻辑信道*/
}RLCITF_UL_LOCH_INFO_LIST_STRU;

/*****************************************************************************
 结构名    : RLCITF_DL_LOCH_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DL RLC的逻辑信道配置
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLochLabel;        /* 逻辑信道内部实现统一标识：[0,[0,34*2-1]] */
    /* 下行不需要配置RLC SIZE，由MAC指示RLC，WAS在MAC的TFS中指示MAC */
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
}RLCITF_DL_LOCH_INFO_STRU;

/*****************************************************************************
 结构名    : RLCITF_DL_LOCH_INFO_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 下行逻辑信道映射，一个RB可能映射1个或者2个逻辑信道,AM RLC实体可能对应2个
             逻辑信道，该结构只是AM RLC使用。
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLochCnt;          /* RB映射的逻辑信道个数 */
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    RLCITF_DL_LOCH_INFO_STRU            astDlLochInfo[PS_WUE_MAX_LOCH_PER_RLC_NUM];
}RLCITF_DL_LOCH_INFO_LIST_STRU;

/*****************************************************************************
 结构名    : RLCITF_UL_TM_RLC_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : UL TM RLC配置信息
*****************************************************************************/
typedef struct
{
    RLCITF_UL_LOCH_INFO_STRU            stTmUlLochInfo;
    RLCITF_UL_TM_RLC_STRU               stUlTmPara;      /* RLC TM实体上行参数  */
}RLCITF_UL_TM_RLC_INFO_STRU;

/*****************************************************************************
 结构名    : RLCITF_DL_TM_RLC_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DL TM RLC配置信息
*****************************************************************************/
typedef struct
{
    RLCITF_DL_LOCH_INFO_STRU            stTmDlLochInfo;
    RLCITF_DL_TM_RLC_STRU               stDlTmPara;      /* RLC TM实体下行参数  */
}RLCITF_DL_TM_RLC_INFO_STRU;

/*****************************************************************************
 结构名    : RLCITF_UL_UM_RLC_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : UL UM RLC配置信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulUlHfn;        /*参见RLCITF_UL_AM_RLC_INFO_STRU中对HFN的描述*/
    RLCITF_UL_LOCH_INFO_STRU            stUmUlLochInfo;
    RLCITF_UL_UM_RLC_STRU               stUlUmPara;     /* RLC UM实体上行参数  */
}RLCITF_UL_UM_RLC_INFO_STRU;

/*****************************************************************************
 结构名    : RLCITF_DL_UM_RLC_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DL UM RLC配置信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDlHfn;        /*参见RLCITF_DL_AM_RLC_INFO_STRU中对HFN的描述*/
    RLCITF_DL_LOCH_INFO_STRU            stUmDlLochInfo;
    RLCITF_DL_UM_RLC_STRU               stDlUmPara;     /* RLC UM实体下行参数  */
}RLCITF_DL_UM_RLC_INFO_STRU;

/*****************************************************************************
 结构名    : RLCITF_UL_AM_RLC_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : UL AM RLC配置信息
*****************************************************************************/
typedef struct
{
    /*****************************************************************************
    HFN
     1) RRC在新建、重建AM/UM RLC实体时，需要配置HFN，
        RLC以RLC SN=0、配置的HFN开始维护COUNT-C值；
     2) RRC在配置加密参数时，也需要对AM/UM RLC实体配置HFN，
        激活时间到时，RLC开始基于新配置的HFN、
        激活时间RLC SN,开始维护COUNT-C,(激活时间到前继续维护原来的COUNT-C)

        RRC_RLC_CFG_MODE_MODIFY时，ulUlHfn RRC不做配置，RLC不做处理;
        RRC_RLC_CFG_MODE_SETUP/RRC_RLC_CFG_MODE_REEST时,ulUlHfn RRC要做配置，RLC必须做处理
    *****************************************************************************/
    VOS_UINT32                          ulUlHfn;
    RLCITF_UL_LOCH_INFO_LIST_STRU       stAmUlLochInfo;
    RLCITF_UL_AM_RLC_STRU               stUlAmPara;      /* RLC AM实体上行参数  */
}RLCITF_UL_AM_RLC_INFO_STRU;

/*****************************************************************************
 结构名    : RLCITF_DL_AM_RLC_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DL AM RLC配置信息
*****************************************************************************/
typedef struct
{
    /*  RRC_RLC_CFG_MODE_MODIFY时，ulDlHfn RRC不做配置，RLC不做处理;
        RRC_RLC_CFG_MODE_SETUP/RRC_RLC_CFG_MODE_REEST时,ulDlHfn RRC要做配置，RLC必须做处理
    */
    VOS_UINT32                          ulDlHfn;
    RLCITF_DL_LOCH_INFO_LIST_STRU       stAmDlLochInfo;
    RLCITF_DL_AM_RLC_STRU               stDlAmPara;      /* RLC AM实体下行参数  */
}RLCITF_DL_AM_RLC_INFO_STRU;

/*****************************************************************************
 结构名    : RRC_RLC_AM_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : AM RLC配置消息, 参数全配，非增量配置
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* Operation ID     */

    VOS_UINT8                           ucRbId;             /* 要配置的RB号, 2-31    */
    WUE_CN_DOMAIN_TYPE_ENUM_UINT8       enCnDomain;         /* 标识当前RB属于哪个CN域，信令RB时填BUTT */

    RRC_RLC_CFG_MODE_ENUM_UINT8         enUlCfgMode;        /* 上行配置模式 */
    RRC_RLC_CFG_MODE_ENUM_UINT8         enDlCfgMode;        /* 下行配置模式 */

    /*V3 R7_SpecialHE Start */
    PS_BOOL_ENUM_UINT8                  enSpecialHEField;  /*Special HE Field是否使用 PS_TRUE表示使用，PS_FALSE表示不使用 */
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    /* V3 R7_SpecialHE End */

    RLCITF_UL_AM_RLC_INFO_STRU          stUlAmRlcInfo;      /* 上行AM RLC参数*/
    RLCITF_DL_AM_RLC_INFO_STRU          stDlAmRlcInfo;      /* 下行AM RLC参数*/
}RRC_RLC_AM_CONFIG_REQ_STRU;

/*****************************************************************************
 结构名    : RRC_RLC_UM_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : UM RLC配置消息, 参数全配，非增量配置
             对于RB0，只填写
             enCfgMode = RLC_RRC_CONFIG_MODE_SETUP;
             ucRbId = 0;
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* Operation ID */

    VOS_UINT8                           ucRbId;             /* [0,32]或者RLCITF_CTCH_RB_ID,*/
    WUE_CN_DOMAIN_TYPE_ENUM_UINT8       enCnDomain;         /* 标识当前RB属于哪个CN域，信令RB时填BUTT */

    RRC_RLC_CFG_MODE_ENUM_UINT8         enUlCfgMode;        /* 上行配置模式 */
    RRC_RLC_CFG_MODE_ENUM_UINT8         enDlCfgMode;        /* 下行配置模式 */

    /*V3 R7_7C1 Start */
    PS_BOOL_ENUM_UINT8                  enEBit;           /*E-bit:The absence of this IE implies: "normal E-bit interpretation"*/
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    /* V3 R7_7C1 End */

    RLCITF_UL_UM_RLC_INFO_STRU          stUlUmRlcInfo;      /* 上行UM RLC参数*/
    RLCITF_DL_UM_RLC_INFO_STRU          stDlUmRlcInfo;      /* 下行UM RLC参数*/

}RRC_RLC_UM_CONFIG_REQ_STRU;


/*****************************************************************************
 结构名    : RRC_RLC_TM_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TM RLC配置消息, 参数全配, 非增量配置
             对于RB0, 只填写
             enUlCfgMode = RRC_RLC_CFG_MODE_SETUP;
             enDlCfgMode = RRC_RLC_CFG_MODE_NO_CHANGE;
             ucRbId = 0;
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* 操作标识     */

    VOS_UINT8                           ucRbId;             /* 要配置的RB号, 0, 5-32    */
    WUE_CN_DOMAIN_TYPE_ENUM_UINT8       enCnDomain;         /* 标识当前RB属于哪个CN域，信令RB时填BUTT */
    PS_BOOL_ENUM_UINT8                  enSrbInd;           /* RBs whose identities shall be set between 5 and 32 may be used as
                                                               signalling radio bearer for the RRC messages on the DCCH sent in RLC transparent mode (RLC-TM).*/
    VOS_UINT8                           aucReserve[3];     /* 4字节对齐，保留 */

    RRC_RLC_CFG_MODE_ENUM_UINT8         enUlCfgMode;        /* 上行配置模式 */
    RRC_RLC_CFG_MODE_ENUM_UINT8         enDlCfgMode;        /* 下行配置模式 */

    RLCITF_UL_TM_RLC_INFO_STRU          stUlTmRlcInfo;      /* 上行TM RLC参数, enUlCfgMode = RRC_RLC_CFG_MODE_NO_CHANGE无效 */
    RLCITF_DL_TM_RLC_INFO_STRU          stDlTmRlcInfo;      /* 下行TM RLC参数, enDlCfgMode = RRC_RLC_CFG_MODE_NO_CHANGE无效*/

}RRC_RLC_TM_CONFIG_REQ_STRU;

/*****************************************************************************
 结构名    : RLC_RRC_CONFIG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC配置响应
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* 操作标识 */
    RLCITF_RSLT_ENUM_UINT32             enRslt;             /* 配置结果, 若RB配置失败或REQ参数错误, 回失败 */
}RLC_RRC_CONFIG_CNF_STRU;

/*****************************************************************************
 结构名    : RRC_RLC_RELEASE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC释放请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* Operation ID            */

    VOS_UINT8                           ucCnt;              /* [0,PS_WUE_MAX_RB_NUM],释放的RB的数目, 为0时全释放  */
    VOS_UINT8                           aucRbId[PS_WUE_MAX_RB_NUM]; /* 释放的RB ID的列表，[0,32]或者RLCITF_CTCH_RB_ID */
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
}RRC_RLC_RELEASE_REQ_STRU;

/*****************************************************************************
 结构名    : RLC_RRC_RELEASE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC释放响应, 若释放一个未配置的RB或RRC_RLC_RELEASE_REQ消息参数错误，回失败;
*****************************************************************************/
typedef RLC_RRC_CONFIG_CNF_STRU         RLC_RRC_RELEASE_CNF_STRU;

/*****************************************************************************
 结构名    : RRC_RLC_SUSPEND_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC挂起请求
             RRC配置RLC加密参数，或者RRC发生切换时挂起RLC。
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* Operation ID        */

    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucSuspendRbCnt;     /* 需要挂起的RB个数, [1, 31] */
    RLCITF_SUSPEND_INFO_STRU            astSuspendInfo[PS_WUE_MAX_RB_NUM];
}RRC_RLC_SUSPEND_REQ_STRU;

/*****************************************************************************
 结构名    : RLC_RRC_SUSPEND_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC挂起响应
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* operation identity */

    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucSuspendRbCnt;            /* 被挂起的RB个数, [1, 31] */
    RLCITF_RLC_SN_STRU                  astRlcSn[PS_WUE_MAX_RB_NUM];/* suspended result */

    RLCITF_RSLT_ENUM_UINT32             enRslt;             /* suspend result为VOS_NG时, aResult和usRB2Sn无效 */
}RLC_RRC_SUSPEND_CNF_STRU;

/*****************************************************************************
 结构名    : RRC_RLC_RESUME_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC恢复
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;             /* Operation ID            */

    VOS_UINT8                           ucResumeRbCnt;      /* 被恢复数据传输的RB个数, [1, 31] */
    VOS_UINT8                           aucRbId[PS_WUE_MAX_RB_NUM]; /* 要恢复数据传输的RB号, [1, 31]    */
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
}RRC_RLC_RESUME_REQ_STRU;

/*****************************************************************************
 结构名    : RLC_RRC_RESUME_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC恢复响应
*****************************************************************************/
typedef RLC_RRC_CONFIG_CNF_STRU        RLC_RRC_RESUME_CNF_STRU;

/*******************************************************************************
 结构名    : RRC_RLC_STOP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 1) 当RRC收到网侧消息中IE中"RB information to reconfigure"
                带有子IE"RB stop/continue"值为stop, 则发起RRC_RLC_STOP_REQ原语,
                用来停止RB ID大于2的RLC实体;
             2) 发生硬切换时;
             3) D2D重配时;
             4) CELL/URA UPDATE时;
             5) 发生异系统切换和重选时, 在收到NAS回的挂起响应消息后,
                会触发该原语停止所有的RLC实体;
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;             /* Operation ID                */

    VOS_UINT8                           ucStopRbCnt;        /* 被停止的RB个数 [1, 31] */
    VOS_UINT8                           aucRbId[PS_WUE_MAX_RB_NUM]; /* 要停止数据传输的RB号 [1, 31]   */
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
}RRC_RLC_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : RLC_RRC_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC停止响应
*****************************************************************************/
typedef RLC_RRC_CONFIG_CNF_STRU         RLC_RRC_STOP_CNF_STRU;

/*****************************************************************************
 结构名    : RRC_RLC_CONTINUE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 停止的RLC继续发送
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* Operation ID                */

    VOS_UINT8                           ucContinueRbCnt;    /* 要继续数据传输的RB个数, [1, 31] */
    VOS_UINT8                           aucRbId[PS_WUE_MAX_RB_NUM]; /* 要继续数据传输的RB号, [1, 31]    */
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
}RRC_RLC_CONTINUE_REQ_STRU;

/*****************************************************************************
 结构名    : RLC_RRC_CONTINUE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef RLC_RRC_CONFIG_CNF_STRU         RLC_RRC_CONTINUE_CNF_STRU;

/*******************************************************************************
 结构名    : RLC_RRC_STATUS_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 1) 当RLC RESET过程结束后, 发送该原语
             2) 当数据链路层连接丢失的时候, 发送该原语
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /*_H2ASN_Skip*/

    VOS_UINT8                           ucRbId;             /* 发生事件的RB的编号, [2, 32]        */

    RLCITF_EVENT_TYPE_ENUM_UINT8        enEventType;        /* 事件类型                    */
}RLC_RRC_STATUS_IND_STRU;

/*****************************************************************************
 结构名    : RLC_RRC_ULDATA_TX_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC上行数传指示
             当RLC层的所有实体在接收到RRC的进入CELL_PCH或URA_PCH状态的通知后,
             若有上行数据需要发送, 使用该条原语向RRC进行指示
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /*_H2ASN_Skip*/

    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
}RLC_RRC_ULDATA_TX_IND_STRU;

/*****************************************************************************
 结构名    : RRC_RLC_MODE_CHANGE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC模式改变请求
             用于指示按照配置的上行数据传送模式进行数据传输
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* operation identity */
    WUEL2L3_UL_MODE_ENUM_UINT8          enMode;             /* L2发送模式  */
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
}RRC_RLC_MODE_CHANGE_REQ_STRU;

/*****************************************************************************
 结构名    : RLC_RRC_MODE_CHANGE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC模式改变请求响应
*****************************************************************************/
typedef RLC_RRC_CONFIG_CNF_STRU         RLC_RRC_MODE_CHANGE_CNF_STRU;

/*****************************************************************************
 结构名    : RLCITF_CIPHER_CONFIG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC加密配置
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enHfnAddOneInd;     /* PS_TRUE，RRC初试配置的HFN要增加1后，RLC再正常维护,请参见25.331,8.3.6.3、8.3.3.3、8.2.2.3节描述*/
    WUEL2L3_CIPHER_ALGO_ENUM_UINT8      enCipherAlgo;       /* 加密算法 */

    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucCsRbCnt;          /* AM,UM模式CS域RB数量,如果ucCsRbCnt个数为0, 则表明CS域不需要加密 0..3 */
    RLCITF_RB_CIPHER_INFO_STRU          astCsRbCipherInfo[PS_WUE_MAX_CS_RB_NUM];   /* CS域RB列表及该RB对应的上下行加密激活时间 */
    VOS_UINT8                           aucCsCk[WUE_CIPHER_KEY_LEN];/* CS域加密密钥 */
    VOS_UINT32                          ulCsRbCountCMsb;    /* 对于AM RLC: ulCsRbCountCMsb(20BIT MSB) + ulUlActTimeRlcSn(12BIT LSB)直接用于形成对应RB的CS域上行COUNT_C; ulCsRbCountCMsb(20BIT MSB) + ulDlActTimeRlcSn(12BIT LSB)直接用于形成对应RB的CS域下行COUNT_C;
                                                               对于UM RLC: ulCsRbCountCMsb(20BIT MSB) + 00000(5BIT ) + ulUlActTimeRlcSn(7BIT LSB)直接用于形成对应RB的CS域上行COUNT_C; ulCsRbCountCMsb(20BIT MSB)  + 00000(5BIT ) +  ulDlActTimeRlcSn(7BIT LSB)直接用于形成对应RB的CS域下行COUNT_C; */

    VOS_UINT8                           aucReserve2[3];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucPsRbCnt;          /* AM,UM模式PS域RB数量, 如果ucPsRbCnt个数为0, 则表明PS域不需要加密 0..3 */
    RLCITF_RB_CIPHER_INFO_STRU          astPsRbCipherInfo[PS_WUE_MAX_PS_RB_NUM];   /* PS域RB列表及该RB对应的上下行加密激活时间 */
    VOS_UINT8                           aucPsCk[WUE_CIPHER_KEY_LEN]; /* PS域加密密钥 */
    VOS_UINT32                          ulPsRbCountCMsb;    /* 对于AM RLC: ulPsRbCountCMsb(20BIT MSB) + ulUlActTimeRlcSn(12BIT LSB)直接用于形成对应RB的PS域上行COUNT_C; ulPsRbCountCMsb(20BIT MSB) + ulDlActTimeRlcSn(12BIT LSB)直接用于形成对应RB的PS域下行COUNT_C;
                                                               对于UM RLC: ulPsRbCountCMsb(20BIT MSB) + 00000(5BIT ) + ulUlActTimeRlcSn(7BIT LSB)直接用于形成对应RB的PS域上行COUNT_C; ulPsRbCountCMsb(20BIT MSB)  + 00000(5BIT ) +  ulDlActTimeRlcSn(7BIT LSB)直接用于形成对应RB的PS域下行COUNT_C; */

    VOS_UINT8                           aucReserve3[3];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucSrbCnt;           /* [0,4],AM,UM模式SRB数量，如果ucSrbCnt个数为0, 则表明没有配置信令RB加密参数，或者信令RB不需要加密 */
    RLCITF_RB_CIPHER_INFO_STRU          astSrbCipherInfo[PS_WUE_MAX_SRB_NUM];    /* SRB列表及该RB对应的上下行加密激活时间 */
    VOS_UINT8                           aucLatestDomainCk[WUE_CIPHER_KEY_LEN];/* 最近域的加密密钥 */
    VOS_UINT32                          ulLatestDomainCountCMsb;  /* 信令RB2-4,使用AM RLC: ulLatestDomainCountCMsb(20BIT MSB) + ulUlActTimeRlcSn(12BIT LSB)直接用于形成对应RB的上行COUNT_C; ulLatestDomainCountCMsb(20BIT MSB) + ulDlActTimeRlcSn(12BIT LSB)直接用于形成对应RB的下行COUNT_C;
                                                                     信令RB1,  使用UM RLC: ulLatestDomainCountCMsb(20BIT MSB) + 00000(5BIT ) + ulUlActTimeRlcSn(7BIT LSB)直接用于形成对应RB的上行COUNT_C; ulLatestDomainCountCMsb(20BIT MSB)  + 00000(5BIT ) +  ulDlActTimeRlcSn(7BIT LSB)直接用于形成对应RB的下行COUNT_C; */
}RLCITF_CIPHER_CONFIG_INFO_STRU;

/*****************************************************************************
 结构名    : RRC_RLC_CIPHER_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC加密配置请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /*_H2ASN_Skip*/
    VOS_UINT16                          usOpID;             /* 操作标识*/

    RLCITF_CIPHER_CONFIG_INFO_STRU      stCipherInfo;
}RRC_RLC_CIPHER_CONFIG_REQ_STRU;

/*****************************************************************************
 结构名    : RLC_RRC_CIPHER_CONFIG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC加密配置请求响应
*****************************************************************************/
typedef RLC_RRC_CONFIG_CNF_STRU         RLC_RRC_CIPHER_CONFIG_CNF_STRU;

/*****************************************************************************
 结构名    : RLC_RRC_CIPHER_ACTIVE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : UM,AM的RLC通过这个原语通知WAS，TM的由MAC通知WAS
             通知RRC该RB上行/下行加密配置已经激活
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 消息类型 */      /*_H2ASN_Skip*/

    VOS_UINT8                           ucRbId;             /* RB identity, [0, 31] */
    WUEL2L3_DIR_ENUM_UINT8               enDir;              /* indicate uplink or downlink direction ciphering active  */
}RLC_RRC_CIPHER_ACTIVE_IND_STRU;


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


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
    RRC_RLC_MSG_TYPE_ENUM_UINT16        enMsgID;    /*_H2ASN_MsgChoice_Export RRC_RLC_MSG_TYPE_ENUM_UINT16*/

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          RRC_RLC_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}RRC_RLC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    RRC_RLC_MSG_DATA                    stMsgData;
}RrcRlcInterface_MSG;

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_UINT32 WTTF_RLC_GetMaxCountCForCipher(VOS_UINT8 ucRbId,VOS_UINT32 *pulUlCountC,VOS_UINT32 *pulDlCountC);
extern VOS_UINT32 WTTF_RLC_GetRbDlRlcPduSize(VOS_UINT8 ucRbId, RLCITF_DL_AM_PDU_SIZE_CHOICE_STRU *pstDlRlcPduSize);
extern VOS_UINT32 WTTF_RLC_AmGetUlActTimeRlcSn(VOS_UINT8 ucRbId, VOS_UINT32 ulLastSduByteLen, VOS_UINT32 *pulActTimeRlcSn);
extern VOS_UINT32 WTTF_RLC_GetEntityState(VOS_UINT8 ucRbId);
extern VOS_UINT32 WTTF_RLC_GetAmSrbSendState
(
    VOS_UINT8                           ucRbId,
    VOS_UINT32                         *pulThreshold,
    VOS_UINT32                         *pulBo
);


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

#endif /* end of RrcRlcInterface.h */


