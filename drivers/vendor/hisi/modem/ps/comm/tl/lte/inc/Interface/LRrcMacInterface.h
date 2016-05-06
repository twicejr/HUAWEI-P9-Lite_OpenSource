/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : LRrcMacInterface.h
  Description     : RRC与MAC接口
  History           :
      1.XiaoJun 58160        2009-08-25  Draft Enact
      2.Dongning 00130305    2009-01-19  Modify
      3.Jiaguohua 00124430   2009-02-12  Modify
      4.Wang Yangcai 49178   2009-05-13  BJ9D00692:根据CP100平台修改消息ID
      5.dongning 130305   2009-06-30  BJ9D01351:修改RA发起原因
      6.lidui 00143774       2010-08-25 DTS2010082301481:切换流程中周期CQI和用户级SRS参数生效时机与协议不一致
******************************************************************************/

#ifndef __LRRCLMACINTERFACE_H__
#define __LRRCLMACINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "LPSCommon.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/

#define PS_MAX_UE_ID_LENGTH             6
#define PS_MAX_BCCH_MSG_LEN             1024
#define PS_MAX_PCCH_MSG_LEN             1024

#define ELRRC_LMAC_MSG_HDR                (PS_MSG_ID_RRC_TO_MAC_BASE)
#define LMAC_ELRRC_MSG_HDR                (PS_MSG_ID_MAC_TO_RRC_BASE)
#define ELRMM_LMAC_MSG_HDR                (PS_MSG_ID_RRC_TO_MAC_BASE + 0x40)
#define LMAC_ELRMM_MSG_HDR                (PS_MSG_ID_MAC_TO_RRC_BASE + 0x40)

#define LRRC_LMAC_SCELL_MAX_NUM              8
#define LRRC_LMAC_TAG_NUM                    4
#define LRRC_LMAC_TAG_ID_MAX_VALUE           3
#define LRRC_LMAC_SCELL_CONFIG               1
#define LRRC_LMAC_SCELL_NOT_CONFIG           0
#define LRRC_LMAC_SCELL_NUM_ZERO             0

/*****************************************************************************
  3 Message Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 结构名    : LRRC_LMAC_MSG_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC和MAC间的接口消息
*****************************************************************************/
enum LRRC_LMAC_MSG_TYPE_ENUM
{
    ID_LRRC_LMAC_BCCH_CONFIG_REQ          = (ELRMM_LMAC_MSG_HDR + 0x00),            /* _H2ASN_MsgChoice LRRC_LMAC_BCCH_CONFIG_REQ_STRU */         /* RRC配置MAC的BCCH的信道*/
    ID_LRRC_LMAC_BCCH_CONFIG_CNF          = (LMAC_ELRMM_MSG_HDR + 0x00),            /* _H2ASN_MsgChoice LRRC_LMAC_BCCH_CONFIG_CNF_STRU */         /* RRC配置MAC的BCCH的响应*/

    ID_LRRC_LMAC_BCCH_DATA_IND            = (LMAC_ELRMM_MSG_HDR + 0x01),            /* _H2ASN_MsgChoice LRRC_LMAC_BCCH_DATA_IND_STRU */           /* MAC上传给RRC的BCCH信道的数据*/

    ID_LRRC_LMAC_PCCH_CONFIG_REQ          = (ELRRC_LMAC_MSG_HDR + 0x01),            /* _H2ASN_MsgChoice LRRC_LMAC_PCCH_CONFIG_REQ_STRU */         /* RRC配置MAC的PCCH的信道*/
    ID_LRRC_LMAC_PCCH_CONFIG_CNF          = (LMAC_ELRRC_MSG_HDR + 0x02),            /* _H2ASN_MsgChoice LRRC_LMAC_PCCH_CONFIG_CNF_STRU */         /* RRC配置MAC的PCCH的响应*/

    ID_LRRC_LMAC_PCCH_DATA_IND            = (LMAC_ELRRC_MSG_HDR + 0x03),            /* _H2ASN_MsgChoice LRRC_LMAC_PCCH_DATA_IND_STRU */           /* MAC给RRC的PCCH上的数据 */

    ID_LRRC_LMAC_RACH_CONFIG_REQ          = (ELRRC_LMAC_MSG_HDR + 0x02),            /* _H2ASN_MsgChoice LRRC_LMAC_RACH_CONFIG_REQ_STRU */         /* RRC配置MAC的RACH的信道*/
    ID_LRRC_LMAC_RACH_CONFIG_CNF          = (LMAC_ELRRC_MSG_HDR + 0x04),            /* _H2ASN_MsgChoice LRRC_LMAC_RACH_CONFIG_CNF_STRU */         /* RRC配置MAC的RACH的响应*/

    ID_LRRC_LMAC_RA_REQ                   = (ELRRC_LMAC_MSG_HDR + 0x03),            /* _H2ASN_MsgChoice LRRC_LMAC_RA_REQ_STRU */                  /* RRC要求MAC发起随即接入的请求 */
    ID_LRRC_LMAC_RA_CNF                   = (LMAC_ELRRC_MSG_HDR + 0x05),            /* _H2ASN_MsgChoice LRRC_LMAC_RA_CNF_STRU */                  /* 随即接入的请求的CNF */

    ID_LRRC_LMAC_CONFIG_REQ               = (ELRRC_LMAC_MSG_HDR + 0x04),            /* _H2ASN_MsgChoice LRRC_LMAC_CONFIG_REQ_STRU */              /* RRC配置MAC的实体的信道*/
    ID_LRRC_LMAC_CONFIG_CNF               = (LMAC_ELRRC_MSG_HDR + 0x06),            /* _H2ASN_MsgChoice LRRC_LMAC_CONFIG_CNF_STRU */              /* RRC配置MAC的实体的响应*/

    ID_LRRC_LMAC_RELEASE_REQ              = (ELRRC_LMAC_MSG_HDR + 0x05),            /* _H2ASN_MsgChoice LRRC_LMAC_RELEASE_REQ_STRU */             /* RRC释放MAC*/
    ID_LRRC_LMAC_RELEASE_CNF              = (LMAC_ELRRC_MSG_HDR + 0x07),            /* _H2ASN_MsgChoice LRRC_LMAC_RELEASE_CNF_STRU */             /* RRC释放MAC的响应*/

    ID_LRRC_LMAC_RESET_REQ                = (ELRRC_LMAC_MSG_HDR + 0x06),            /* _H2ASN_MsgChoice LRRC_LMAC_RESET_REQ_STRU */               /* RRC重建MAC的请求*/
    ID_LRRC_LMAC_RESET_CNF                = (LMAC_ELRRC_MSG_HDR + 0x08),            /* _H2ASN_MsgChoice LRRC_LMAC_RESET_CNF_STRU */               /* RRC重建MAC的响应*/

    ID_LRRC_LMAC_ERROR_IND                = (LMAC_ELRRC_MSG_HDR + 0x09),            /* _H2ASN_MsgChoice LRRC_LMAC_ERROR_IND_STRU */               /* MAC通知RRC,MAC发生错误*/

    ID_LRRC_LMAC_PUCCH_SRS_RELEASE_IND    = (LMAC_ELRRC_MSG_HDR + 0x0a),            /* _H2ASN_MsgChoice LRRC_LMAC_PUCCH_SRS_RELEASE_IND_STRU */   /* MAC通知RRC释放SRS和  PUCCH资源*/
    ID_LRRC_LMAC_PUCCH_SRS_RELEASE_RSP    = (ELRRC_LMAC_MSG_HDR + 0x07),            /* _H2ASN_MsgChoice LRRC_LMAC_PUCCH_SRS_RELEASE_RSP_STRU */   /* RRC释放SRS和PUCCH资源后给MAC 的指示*/

    ID_LRRC_LMAC_TDD_CONFIG_REQ           = (ELRRC_LMAC_MSG_HDR + 0x08),            /* _H2ASN_MsgChoice LRRC_LMAC_TDD_CONFIG_REQ_STRU */          /* RRC配置MAC关于TDD 相关信息*/
    ID_LRRC_LMAC_TDD_CONFIG_CNF           = (LMAC_ELRRC_MSG_HDR + 0x0b),            /* _H2ASN_MsgChoice LRRC_LMAC_TDD_CONFIG_CNF_STRU */          /* RRC配置MAC关于TDD 相关信息确认指示*/

    ID_LRRC_LMAC_CRNTI_IND                = (LMAC_ELRRC_MSG_HDR + 0x0c),            /* _H2ASN_MsgChoice LRRC_LMAC_CRNTI_IND_STRU */          /*MAC上报CRNTI值 */

    ID_LRRC_LMAC_RA_SUCC_IND              = (LMAC_ELRRC_MSG_HDR + 0x0d),            /* _H2ASN_MsgChoice LRRC_LMAC_RA_SUCC_IND_STRU */              /* MAC上报随机接入成功指示 */

    ID_LRRC_LMAC_RELEASE_SCELL_REQ        = (LMAC_ELRRC_MSG_HDR + 0x0e),            /* _H2ASN_MsgChoice LRRC_LMAC_RELEASE_SCELL_REQ_STRU */        /* RRC删除指定某个SCELL和多个SCELL的命令 */
    ID_LRRC_LMAC_RELEASE_SCELL_CNF        = (ELRRC_LMAC_MSG_HDR + 0x09),            /* _H2ASN_MsgChoice LRRC_LMAC_RELEASE_SCELL_CNF_STRU */         /* MAC回复RRC删除SCELL命令的回复消息 */
    ID_LRRC_LMAC_MSG_TYPE_END
};
typedef VOS_UINT32 LRRC_LMAC_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 结构名    : LRRC_LMAC_CFG_MODE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC配置MAC的命令类型
*****************************************************************************/
enum LRRC_LMAC_CFG_MODE_ENUM
{
    LRRC_LMAC_CFG_MODE_SETUP                  = 0,                                    /* 初始配置 */
    LRRC_LMAC_CFG_MODE_RECFG                  = 1,                                    /* 重配置 */
    LRRC_LMAC_CFG_MODE_BUTT
};
typedef VOS_UINT8 LRRC_LMAC_CFG_MODE_ENUM_UINT8;

/*****************************************************************************
 结构名    : LRRC_LMAC_CFG_MODE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC配置MAC的命令类型
*****************************************************************************/
enum LRRC_LMAC_CFG_RAT_MODE_ENUM
{
    LRRC_LMAC_CFG_RAT_MODE_FDD                  = 0,                                    /* 初始配置 */
    LRRC_LMAC_CFG_RAT_MODE_TDD                  = 1,                                    /* 重配置 */
    LRRC_LMAC_CFG_RAT_MODE_BUTT
};
typedef VOS_UINT8 LRRC_LMAC_CFG_RAT_MODE_ENUM_UINT8;

/*****************************************************************************
 结构名    : LRRC_LMAC_RA_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC请求MAC的随机接入类型
*****************************************************************************/
enum LRRC_LMAC_RA_TYPE_ENUM
{
    LRRC_LMAC_RA_TYPE_CONTENTION              = 0,                                    /* 竞争机的 */
    LRRC_LMAC_RA_TYPE_NON_CONTENTION          = 1,                                    /* 非竞争的 */
    LRRC_LMAC_RA_TYPE_BUTT
};
typedef VOS_UINT8 LRRC_LMAC_RA_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名    : LRRC_LMAC_RA_CAUSE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC请求MAC随机接入的原因
*****************************************************************************/
enum LRRC_LMAC_RA_CAUSE_ENUM
{
    LRRC_LMAC_RA_CAUSE_CONN                   = 0,                                    /* 链接建立的 */
    LRRC_LMAC_RA_CAUSE_HO                     = 1,                                    /* 切换的 */
    LRRC_LMAC_RA_CAUSE_REEST                  = 2,                                    /* RRC链接重建立的 */
    LRRC_LMAC_RA_CAUSE_WAITTA_TIMEOUT         = 3,                                    /* 等待TA超时 */
    LRRC_LMAC_RA_CAUSE_SENDSR                 = 4,                                    /* 利用随机接入发送SR信息 */
    LRRC_LMAC_RA_CAUSE_BUTT
};
typedef VOS_UINT8 LRRC_LMAC_RA_CAUSE_ENUM_UINT8;

/*****************************************************************************
 结构名    : LRRC_LMAC_ERR_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
enum LRRC_LMAC_ERR_TYPE_ENUM
{
    LRRC_LMAC_ERR_FATAL                        = 0,                                   /*MAC自身发生不可恢复性错误*/
    LRRC_LMAC_RA_ERR_MAX_TX_NUM                = 1,                                   /*发送随机接入Preamble达到最大次数*/
    LRRC_LMAC_RA_ERR_MAX_HARQ_NUM              = 2,                                   /*随机接入过程发送消息3达到最大次数*/
    LRRC_LMAC_ERR_NO_RF_RA                     = 3,                                   /*随机接入时没有RF*/
    LRRC_LMAC_ERR_NO_RF_TIMEROUT               = 4,                                   /*RF保护定时器超时*/
    LRRC_LMAC_ERR_RF_RESUME_SYNC               = 5,                                   /*RF恢复后防止与网侧不同步*/
    LRRC_LMAC_ERR_BUTT
};
typedef VOS_UINT8 LRRC_LMAC_ERR_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名    : LRRC_LMAC_RSLT_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC层配置的结果:成功还是失败
*****************************************************************************/
enum LRRC_LMAC_RSLT_ENUM
{
    LRRC_LMAC_SUCC                            = 0,
    LRRC_LMAC_FAIL                            = 1,
    LRRC_LMAC_RSLT_BUTT
};
typedef VOS_UINT8   LRRC_LMAC_RSLT_ENUM_UINT8;

/*****************************************************************************
结构名    : LRRC_LMAC_PATH_LOSS_CHANGE_ENUM
协议表格  :
ASN.1描述 :
结构说明  :
*****************************************************************************/
enum LRRC_LMAC_PATH_LOSS_CHANGE_ENUM
{
    LRRC_LMAC_PATH_LOSS_CHANGE_1DB            = 0,
    LRRC_LMAC_PATH_LOSS_CHANGE_3DB               ,
    LRRC_LMAC_PATH_LOSS_CHANGE_6DB               ,
    LRRC_LMAC_PATH_LOSS_CHANGE_INFINITY          ,
    LRRC_LMAC_PATH_LOSS_CHANGE_BUTT
};
typedef VOS_UINT8   LRRC_LMAC_PATH_LOSS_CHANGE_ENUM_UINT8;

/*****************************************************************************
结构名    : LRRC_LMAC_PWR_OFFSET_GROUPB_ENUM
协议表格  :
ASN.1描述 :
结构说明  :
*****************************************************************************/
enum LRRC_LMAC_PWR_OFFSET_GROUPB_ENUM
{
    LRRC_LMAC_PWR_OFFSET_GROUPB_MINUSINFINIT  = 0,
    LRRC_LMAC_PWR_OFFSET_GROUPB_0DB              ,
    LRRC_LMAC_PWR_OFFSET_GROUPB_5DB              ,
    LRRC_LMAC_PWR_OFFSET_GROUPB_8DB              ,
    LRRC_LMAC_PWR_OFFSET_GROUPB_10DB             ,
    LRRC_LMAC_PWR_OFFSET_GROUPB_12DB             ,
    LRRC_LMAC_PWR_OFFSET_GROUPB_15DB             ,
    LRRC_LMAC_PWR_OFFSET_GROUPB_18DB             ,
    LRRC_LMAC_PWR_OFFSET_GROUPB_BUTT
};
typedef VOS_UINT8   LRRC_LMAC_PWR_OFFSET_GROUPB_ENUM_UINT8;

/*****************************************************************************
 结构名    : LRRC_LMAC_CHANNEL_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC接收广播信息时对应的物理信道类型
*****************************************************************************/
enum LRRC_LMAC_CHANNEL_TYPE_ENUM
{
    LRRC_LMAC_CHANNEL_TYPE_PBCH               = 0,                                    /* PBCH信道接收的信息 */
    LRRC_LMAC_CHANNEL_TYPE_PDSCH                 ,                                    /* PDSCH信道接收的信息 */
    LRRC_LMAC_CHANNEL_TYPE_BUTT
};
typedef VOS_UINT8 LRRC_LMAC_CHANNEL_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : LTE_PROTOCOL_VER_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  : 协议版本类型
*****************************************************************************/
enum    LTE_PROTOCOL_VER_ENUM
{
    LTE_PROTOCOL_VER_V8  = 0x01,
    LTE_PROTOCOL_VER_V9  = 0x02,
    LTE_PROTOCOL_VER_V10 = 0x04,
    LTE_PROTOCOL_VER_V11 = 0x08,
    LTE_PROTOCOL_VER_BUTT
};
typedef VOS_UINT8   LTE_PROTOCOL_VER_ENUM_UINT8;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : LRRC_LMAC_BCCH_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :该原语保留，暂时不使用
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    /*广播信息进程号*/
    VOS_UINT8                           ucHarqProcNum;
    VOS_UINT8                           aucRev[1];

    /*广播信息修改周期系数*/
    VOS_UINT32                          ulModifyPeriodCoeff;

} LRRC_LMAC_BCCH_CONFIG_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_BCCH_CONFIG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :该原语保留，暂时不使用
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    LRRC_LMAC_RSLT_ENUM_UINT8                 enRslt;
    VOS_UINT8                           aucRev[1];

} LRRC_LMAC_BCCH_CONFIG_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_BCCH_DATA_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT8                           ucAntennaPortsCount;

    VOS_UINT8                           ucSubFrame;
    VOS_UINT16                          usFrame;

    LRRC_LMAC_CHANNEL_TYPE_ENUM_UINT8         enMacChannelType;
    VOS_UINT8                           aucRev[3];

    /*最大长度由PS_MAX_BCCH_MSG_LEN确定，单位字节*/
    VOS_UINT32                          ulDataLength;
    VOS_UINT8                           aucData[4];
} LRRC_LMAC_BCCH_DATA_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_PCCH_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明 :该原语保留，暂时不使用
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];

    /*用于系统信息修改时得周期*/
    VOS_UINT32                          ulDefaultPagingCycle;

} LRRC_LMAC_PCCH_CONFIG_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_PCCH_CONFIG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明   :该原语保留，暂时不使用
*****************************************************************************/
typedef LRRC_LMAC_BCCH_CONFIG_CNF_STRU LRRC_LMAC_PCCH_CONFIG_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_PCCH_DATA_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT8                           ucSubFrame;
    VOS_UINT8                           ucRev;

    VOS_UINT16                          usFrame;

    /*最大长度由PS_MAX_PCCH_MSG_LEN确定单位字节*/
    VOS_UINT32                          ulDataLength;
    VOS_UINT8                           aucData[4];

} LRRC_LMAC_PCCH_DATA_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_GROUPA_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPblGrpASize;                          /*Group A所对应的Preamble个数:如果空口没有，就配置成 0 */
    LRRC_LMAC_PWR_OFFSET_GROUPB_ENUM_UINT8    enMessagePowerOffsetGroupB;             /*协议36.321的参数MESSAGE_POWER_OFFSET_GROUP_B,取值协议待定*/

    VOS_UINT16                          usMessageSizeGroupA;                    /*协议36.321的参数MESSAGE_SIZE_GROUP_A*/

} LRRC_LMAC_GROUPA_CONFIG_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_RACH_COMM_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RACH-ConfigCommon有相关
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitGroupAValid  :1;                     /*Group A信息是否有效标志，0:无效，1:有效*/
    VOS_UINT32                          bitSpare        :31;

    LRRC_LMAC_GROUPA_CONFIG_STRU              stGroupAConfig;

    VOS_UINT8                           ucPblNum;                               /*Group A和B所对应的总Preamble个数*/
    VOS_UINT8                           ucPblPwrStep;                           /*Preamble功率爬升因子*/
    VOS_INT16                           sPblInitTargetPwr;                      /*Preamble在eNB的期望接收功率*/

    VOS_UINT8                           ucPblMaxTxNum;                          /*随机接入Preamble最大发送次数*/
    VOS_UINT8                           ucRarWindowSize;                        /*接收随机接入响应消息的窗口*/
    VOS_UINT8                           ucContentTimer;                         /*竞争解决定时器*/
    VOS_UINT8                           ucMaxHarqMsg3Tx;                        /*Msg3进行HARQ的最大发送次数*/

    VOS_INT8                            cPMax;                                  /*最大发射功率，缺省时使用UE能力中的最大发射功率*/
    VOS_INT8                            cDeltaPblMsg3;                          /*Preamble与Msg3之间的OFFSET*/
    VOS_UINT8                           ucUlBandwidth;                           /*系统带宽*/
    VOS_UINT8                           aucRev1[1];

    VOS_UINT32                          ulCellTaTimer;                          /*小区级的TA定时器*/


} LRRC_LMAC_RACH_COMM_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_PRACH_INFO
 协议表格  :
 ASN.1描述 :
 结构说明  :PRACH-Configuration
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPrachConfigIndex;                          /*已经确认:Prach-ConfigurationIndex,0-63*/
    VOS_UINT8                           aucRev[3];
}LRRC_LMAC_PRACH_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_RACH_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    LRRC_LMAC_CFG_MODE_ENUM_UINT8             enConfigType;
    LRRC_LMAC_CFG_RAT_MODE_ENUM_UINT8         enFddOrTddRatMod;                          /* 0是FDD; 1 TDD */

    LRRC_LMAC_RACH_COMM_INFO_STRU             stRachCommInfo;                         /*36.331 6.3.2节RACH-ConfigCommon*/

    LRRC_LMAC_PRACH_INFO_STRU                 stPrachInfo;                            /*36.331 6.3.2节PRACH-Configuration*/

    /*UE长度，暂定字节为单位*/
    VOS_UINT8                           ucUeIdLength;
    VOS_UINT8                           aucRev2[1];
    VOS_UINT8                           aucUeId[PS_MAX_UE_ID_LENGTH];           /*ue id的格式和类型*/
} LRRC_LMAC_RACH_CONFIG_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_RACH_CONFIG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef LRRC_LMAC_BCCH_CONFIG_CNF_STRU LRRC_LMAC_RACH_CONFIG_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_RA_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    LRRC_LMAC_RA_TYPE_ENUM_UINT8              enRaType;

    LRRC_LMAC_RA_CAUSE_ENUM_UINT8             enRaCause;

    VOS_UINT8                           ucDediPreambleId;
    VOS_UINT8                           ucPrachMaskIndex;
    VOS_UINT8                           aucRev[2];

    VOS_INT16                           sPathLoss ;                             /*取值不清楚，暂时保留用于选择Group A或B的实际路损，该值需要确认获取方式 */
    VOS_UINT16                          usMsg3Size;                             /* 用于选择Group A或B的消息3大小值 ，数值使用的单位确认:byte */
} LRRC_LMAC_RA_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_RA_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef LRRC_LMAC_BCCH_CONFIG_CNF_STRU LRRC_LMAC_RA_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_PHR_CONFIG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPeriodPhrTimer;
    VOS_UINT16                          usProhibitPhrTimer;

    LRRC_LMAC_PATH_LOSS_CHANGE_ENUM_UINT8     enDlPathLossChange;
    PS_BOOL_ENUM_UINT8                        enExtendPhr;
    PS_BOOL_ENUM_UINT8                        enSimulPUCCH_PUSCH;
    VOS_UINT8                                 aucRev[1];
    /* V7R2 RRC-L2 INTF END */
}LRRC_LMAC_PHR_CONFIG_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_SR_CONFIG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSrConfigIndex;                        /*SR传输周期索引*/
    VOS_UINT8                           ucSrTransMaxNum;                        /*SR最大传输次数，见协议36.321 的DSR_TRANS_MAX*/
    VOS_UINT8                           aucRev[2];
}LRRC_LMAC_SR_CONFIG_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_UL_SCH_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPeriodBsrTimer;
    VOS_UINT32                          ulRetxBsrTimer;

    PS_BOOL_ENUM_UINT8                  enExtendBsrSize;
    /* V7R2 RRC-L2 INTF END */
    VOS_UINT8                           ucUlMaxHarqTxNum;
    PS_BOOL_ENUM_UINT8                  enTtiBundling;
    VOS_UINT8                           aucRev[1];
    /* V7R2 RRC-L2 INTF END */
} LRRC_LMAC_UL_SCH_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_DL_SCH_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucRev[4];
} LRRC_LMAC_DL_SCH_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_SPS_DL_CONFIG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSpsIntervalDL;
    VOS_UINT8                           aucRev[2];

}LRRC_LMAC_SPS_DL_CONFIG_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_SPS_UL_CONFIG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSpsIntervalUL;
    VOS_UINT8                           ucImplicitReleaseAfter;
    VOS_UINT8                           aucRev[1];

}LRRC_LMAC_SPS_UL_CONFIG_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_SPS_CONFIG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitSpsDlValid:1;
    VOS_UINT32                          bitSpsUlValid:1;
    VOS_UINT32                          bitSpare:30;

    LRRC_LMAC_SPS_DL_CONFIG_INFO_STRU         stSpsDlConfig;
    LRRC_LMAC_SPS_UL_CONFIG_INFO_STRU         stSpsUlConfig;
}LRRC_LMAC_SPS_CONFIG_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_SCELL_RACH_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : SCELL的rach信息
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucPblPwrStep;                          /*Preamble功率爬升因子*/
    VOS_UINT8                            ucPblMaxTxNum;                         /*随机接入Preamble最大发送次数*/
    VOS_INT16                            sPblInitRxTargetPwr;                   /*Preamble在eNB的期望接收功率 */

    VOS_UINT8                            ucRarWindowSize;                       /*接收随机接入响应消息的窗口 */
    VOS_UINT8                            aucResv[3];                           /*预留*/
} LRRC_LMAC_SCELL_RACH_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_SCELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : SCELL的配置信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           bitScellRachValid : 1;                 /*scell rach信息有效指示，0:无效，1:有效*/
    VOS_UINT32                           bitSpare          : 31;

    VOS_UINT8                            ucScellIndex;                          /*Scell 索引*/
    VOS_UINT8                            ucConfigUlValid;                       /*Scell小区下行配置状态  1:配置，0:未配置*/
    VOS_UINT8                            ucConfigDlValid;                       /*Scell小区上行配置状态  1:配置，0:未配置*/
    VOS_UINT8                            ucTagId;                               /*TAG标识，用于指示该SCELL所属的TAG*/

    LRRC_LMAC_CFG_RAT_MODE_ENUM_UINT8    enFrameType;                           /*LTE 帧类型*/
    VOS_UINT8                            ucSubFrameAssig;                       /*特殊子帧配比*/
    VOS_UINT8                            aucResv[2];
    LRRC_LMAC_SCELL_RACH_INFO_STRU       stScellRachInfo;                       /*Scell的rach信息*/
}LRRC_LMAC_SCELL_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_CA_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CA相关配置. 若usServCellIdxBmp为0，enScellDeactTimer无意义
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulScellDeactTimer;                     /*Scell去激活定时器*/
    VOS_UINT32                           ulScellNum;                            /*Scell个数*/
    LRRC_LMAC_SCELL_INFO_STRU            astScellInfo[LRRC_LMAC_SCELL_MAX_NUM]; /*Scell的状态信息*/
} LRRC_LMAC_CA_CONFIG_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_TAG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TAG配置信息
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucTagId;                               /*TAG标识*/
    VOS_UINT8                            aucResv[3];

    VOS_UINT32                           ulTagTimerLen;                         /*TAG定时器长度*/
} LRRC_LMAC_TAG_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_TAG_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TAG相关配置.
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulTagNum;                              /*配置TAG个数*/
    LRRC_LMAC_TAG_INFO_STRU              astTagInfo[LRRC_LMAC_TAG_NUM];         /*配置的TAG信息*/
} LRRC_LMAC_TAG_CONFIG_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    LRRC_LMAC_CFG_MODE_ENUM_UINT8       enConfigType;
    LTE_PROTOCOL_VER_ENUM_UINT8         enProtoType;
    VOS_UINT32                          bitCrntiValid   : 1;                    /*C-RNTI是否有效指示*/
    VOS_UINT32                          bitSrProhbTimerValid   :1;              /*sr-ProhibitTimer-r9是否有效指示*/
    VOS_UINT32                          bitTaTimerValid : 1;                    /*TATimer信息是否有效指示*/
    VOS_UINT32                          bitUlSCHValid   : 1;                    /*上行SCH信息是否有效指示*/
    VOS_UINT32                          bitDlSCHValid   : 1;                    /*下行SCH信息是否有效指示*/
    VOS_UINT32                          bitPhrCfgValid  : 1;
    VOS_UINT32                          bitSrCfgValid   : 1;
    VOS_UINT32                          bitSpsCfgValid  : 1;
    VOS_UINT32                          bitCaCfgValid   : 1;                    /*CA信息是否有效指示, 释放SCELL可通过此标志无效设置 */
    VOS_UINT32                          bitTagCfgValid  :1;
    VOS_UINT32                          bitSpare        : 22;
    /*C-RNTI*/
    VOS_UINT16                          usCrnti;

    VOS_UINT8                           ucSrProhbTimer;                         /* sr-ProhibitTimer-r9 (0..7) */
    VOS_UINT8                           ucReserved;

    /*TA定时器时长*/
    VOS_UINT32                          ulTaTimer;

    /*上行传输信道信息*/
    LRRC_LMAC_UL_SCH_INFO_STRU                stUlSCHInfo;

    /*下行传输信道信息*/
    LRRC_LMAC_DL_SCH_INFO_STRU                stDlSCHInfo;

    /* PHR相关参数信息 */
    LRRC_LMAC_PHR_CONFIG_INFO_STRU        stPhrConfigInfo;

    /* 调度请求相关参数信息 */
    LRRC_LMAC_SR_CONFIG_INFO_STRU         stSrConfigInfo;


    /*半静态调度信息*/
    LRRC_LMAC_SPS_CONFIG_INFO_STRU        stSpsConfigInfo;

    LRRC_LMAC_CA_CONFIG_STRU              stCaConfig;
    LRRC_LMAC_TAG_CONFIG_STRU             stTagConfig;
} LRRC_LMAC_CONFIG_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_CONFIG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef LRRC_LMAC_BCCH_CONFIG_CNF_STRU LRRC_LMAC_CONFIG_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_RELEASE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    VOS_UINT8                           aucRev[2];

} LRRC_LMAC_RELEASE_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_RELEASE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef LRRC_LMAC_BCCH_CONFIG_CNF_STRU LRRC_LMAC_RELEASE_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_RESET_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    VOS_UINT8                           aucRev[2];

} LRRC_LMAC_RESET_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_RESET_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef LRRC_LMAC_BCCH_CONFIG_CNF_STRU LRRC_LMAC_RESET_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_ERROR_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                            /*_H2ASN_Skip*/

    LRRC_LMAC_ERR_TYPE_ENUM_UINT8         enErrorType;
    VOS_UINT8                             ucPblSentNum;                         /*Preamble发送次数*/
    PS_BOOL_ENUM_UINT8                    enMaxTxPowerReached;                  /*用于指示Preamble是否达到最大发送功率,1:达到，0:没达到*/
    PS_BOOL_ENUM_UINT8                    enContentionDetected;                 /*是否有竞争，0:非竞争随机接入，1:竞争随机接入*/

} LRRC_LMAC_ERROR_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_PUCCH_SRS_RELEASE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32      enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucTagId;
    VOS_UINT8                           aucRev[1];
} LRRC_LMAC_PUCCH_SRS_RELEASE_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_PUCCH_SRS_RELEASE_RSP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    VOS_UINT8                           aucRev[2];

} LRRC_LMAC_PUCCH_SRS_RELEASE_RSP_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_TDD_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    VOS_UINT8                           ucSubFrameAssig;

    VOS_UINT8                           aucRev[1];

} LRRC_LMAC_TDD_CONFIG_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_TDD_CONFIG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef LRRC_LMAC_BCCH_CONFIG_CNF_STRU LRRC_LMAC_TDD_CONFIG_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_CRNTI_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usCrnti;

    VOS_UINT8                           aucRev[2];

} LRRC_LMAC_CRNTI_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_RA_SUCC_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 用来通知RRC MAC随机接入成功
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32      enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT8                           ucPblSentNum;                           /*MAC随机接入成功后，上报Preambles发送次数 */
    PS_BOOL_ENUM_UINT8                  enContentionDetected;                   /*用来指示MAC发送的Preamble中是否有竞争方式 1:有，0:没有*/
    VOS_UINT8                           ucServCellIndex;
    PS_BOOL_ENUM_UINT8                  enMaxTxPowerReached;                  /*用于指示Preamble是否达到最大发送功率,1:达到，0:没达到*/
} LRRC_LMAC_RA_SUCC_IND_STRU;

typedef struct
{
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgID;            /*_H2ASN_MsgChoice_Export LRRC_LMAC_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LRRC_LMAC_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}LRRC_LMAC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    LRRC_LMAC_MSG_DATA                    stMsgData;
}RrcMacInterface_MSG;

/*****************************************************************************
 结构名    : LRRC_LMAC_RELEASE_SCELL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC用来通知MAC删除SCELL的请求消息
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32      enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucResv[2];

    VOS_UINT32                          ulCellNum;                              /*需要删除的scell个数*/

    VOS_UINT8                           aucScellIndex[8];                       /*需要删除的scellIndex*/

} LRRC_LMAC_RELEASE_SCELL_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LMAC_RELEASE_SCELL_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC用来回复RRC删除SCELL的回应消息
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucResult;                               /* 0:成功，1:失败 */
    VOS_UINT8                           aucResv;

} LRRC_LMAC_RELEASE_SCELL_CNF_STRU;


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
 Function Name   : LRRC_LMAC_SetLastGetTaTimeStamp;
 Description     : 收到TA控制元时记录当前时刻的时间戳
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.l00195322      2016-1-13  Draft Enact

*****************************************************************************/
extern VOS_VOID LRRC_LMAC_SetLastGetTaTimeStamp(VOS_VOID);
/*****************************************************************************
  9 OTHERS
*****************************************************************************/





#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
