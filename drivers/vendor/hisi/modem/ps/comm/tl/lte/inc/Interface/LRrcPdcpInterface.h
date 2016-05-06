/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : LRrcPdcpInterface.h
  Description     : LRrcPdcpInterface.h header file
  History         :
     1.XiaoJun 58160       2008-09-08  Draft Enact
     2.XieQiang 00124992   2009-01-19  Modify
     3.Wang Yangcai 49178  2009-05-13  BJ9D00692:根据CP100平台修改消息ID
     4.Wang Yangcai 49178  2009-05-23  BJ9D00827:修改COUNTER CHECK在RRC实现
     5.Wang Yangcai 49178  2009-12-15  BJ9D02529:完善安全完整性功能
******************************************************************************/

#ifndef __LRRCPDCPINTERFACE_H__
#define __LRRCPDCPINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "LPSCommon.h"
#include "PsTypeDef.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/

/* 最大RB的个数 */
#define PS_MAX_RB_NUM                   (16)

/* 能够发送的最大AM数据的长度 */
#define PS_MAX_AM_MSG_LEN               (1024 * 2)

/* 能够发送的最大UM数据的长度 */
#define PS_MAX_UM_MSG_LEN               (1024)

/* 能够发送的最大TM数据的长度 */
#define PS_MAX_TM_MSG_LEN               (1024)

#define LRRC_LPDCP_MSG_HDR                (PS_MSG_ID_RRC_TO_PDCP_BASE)
#define LPDCP_LRRC_MSG_HDR                (PS_MSG_ID_PDCP_TO_RRC_BASE)

/*ROHC最大的算法个数*/
#define LRRC_LPDCP_MAX_PROFILE_NUM        (16)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 结构名    : LRRC_LPDCP_MSG_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC和PDCP间的接口消息
*****************************************************************************/
enum LRRC_LPDCP_MSG_TYPE_ENUM
{
    ID_LRRC_LPDCP_CONFIG_REQ              = (LRRC_LPDCP_MSG_HDR + 0x00),            /* _H2ASN_MsgChoice LRRC_LPDCP_CONFIG_REQ_STRU */       /* 配置PDCP  */
    ID_LRRC_LPDCP_CONFIG_CNF              = (LPDCP_LRRC_MSG_HDR + 0x00),            /* _H2ASN_MsgChoice LRRC_LPDCP_CONFIG_CNF_STRU */       /* 配置PDCP的confirm  */

    ID_LRRC_LPDCP_RELEASE_REQ             = (LRRC_LPDCP_MSG_HDR + 0x01),            /* _H2ASN_MsgChoice LRRC_LPDCP_RELEASE_REQ_STRU */      /* 释放PDCP  */
    ID_LRRC_LPDCP_RELEASE_CNF             = (LPDCP_LRRC_MSG_HDR + 0x01),            /* _H2ASN_MsgChoice LRRC_LPDCP_RELEASE_CNF_STRU */      /* 释放PDCP的confirm*/

    ID_LRRC_LPDCP_STOP_REQ                = (LRRC_LPDCP_MSG_HDR + 0x02),            /* _H2ASN_MsgChoice LRRC_LPDCP_STOP_REQ_STRU */         /* 停止用户面数据的传输  */
    ID_LRRC_LPDCP_STOP_CNF                = (LPDCP_LRRC_MSG_HDR + 0x02),            /* _H2ASN_MsgChoice LRRC_LPDCP_STOP_CNF_STRU */         /* 停止用户面数据的传输的confirm*/

    ID_LRRC_LPDCP_CONTINUE_REQ            = (LRRC_LPDCP_MSG_HDR + 0x03),            /* _H2ASN_MsgChoice LRRC_LPDCP_CONTINUE_REQ_STRU */     /* 重新开始用户面数据的传输  */
    ID_LRRC_LPDCP_CONTINUE_CNF            = (LPDCP_LRRC_MSG_HDR + 0x03),            /* _H2ASN_MsgChoice LRRC_LPDCP_CONTINUE_CNF_STRU */     /* 重新开始用户面数据的传输的confirm*/

    ID_LRRC_LPDCP_SECU_CONFIG_REQ         = (LRRC_LPDCP_MSG_HDR + 0x04),            /* _H2ASN_MsgChoice LRRC_LPDCP_SECU_CONFIG_REQ_STRU */  /* 加密和完整性保护的算法 */
    ID_LRRC_LPDCP_SECU_CONFIG_CNF         = (LPDCP_LRRC_MSG_HDR + 0x04),            /* _H2ASN_MsgChoice LRRC_LPDCP_SECU_CONFIG_CNF_STRU */  /* 加密和完整性保护的配置响应 */

    ID_LRRC_LPDCP_COUNTER_CHECK_REQ       = (LRRC_LPDCP_MSG_HDR + 0x05),            /* _H2ASN_MsgChoice LRRC_LPDCP_COUNTER_CHECK_REQ_STRU */  /* RRC发送Counter Check请求 */
    ID_LRRC_LPDCP_COUNTER_CHECK_CNF       = (LPDCP_LRRC_MSG_HDR + 0x05),            /* _H2ASN_MsgChoice LRRC_LPDCP_COUNTER_CHECK_CNF_STRU */  /* PDCP发送Counter Check响应 */

    ID_LRRC_LPDCP_AM_DATA_REQ             = (LRRC_LPDCP_MSG_HDR + 0x06),            /* _H2ASN_MsgChoice LRRC_LPDCP_AM_DATA_REQ_STRU */      /* RRC发送AM数据的请求     */
    ID_LRRC_LPDCP_UM_DATA_REQ             = (LRRC_LPDCP_MSG_HDR + 0x07),            /* _H2ASN_MsgChoice LRRC_LPDCP_UM_DATA_REQ_STRU */      /* RRC发送UM数据的请求     */
    ID_LRRC_LPDCP_DATA_CNF                = (LPDCP_LRRC_MSG_HDR + 0x06),            /* _H2ASN_MsgChoice LRRC_LPDCP_DATA_CNF_STRU */         /* RRC发送AM和TM数据的确认 */

    ID_LRRC_LPDCP_AM_DATA_IND             = (LPDCP_LRRC_MSG_HDR + 0x07),            /* _H2ASN_MsgChoice LRRC_LPDCP_AM_DATA_IND_STRU */      /*  PDCP向RRC发送接收到AM数据   */
    ID_LRRC_LPDCP_UM_DATA_IND             = (LPDCP_LRRC_MSG_HDR + 0x08),            /* _H2ASN_MsgChoice LRRC_LPDCP_UM_DATA_IND_STRU */      /*  RPDCP向RRC发送接收到UM数据  */

    ID_LRRC_LPDCP_SMC_CMP_REQ             = (LRRC_LPDCP_MSG_HDR + 0x08),            /* _H2ASN_MsgChoice LRRC_LPDCP_SMC_CMP_REQ_STRU */  /* RRC发送RRC_SMC_CMP信令 */

    ID_LRRC_LPDCP_ERROR_IND               = (LPDCP_LRRC_MSG_HDR + 0x09),            /* _H2ASN_MsgChoice LRRC_LPDCP_ERROR_IND_STRU */        /* PDCP层发生错误报告    */
/* gaojishan-fast-dorm-cfg */
    ID_LRRC_LPDCP_FAST_DORMANCY_REQ       = (LRRC_LPDCP_MSG_HDR + 0x09),            /* _H2ASN_MsgChoice LRRC_LPDCP_FAST_DORMANCY_REQ_STRU */ /* RRC向PDCP发送FAST_DORMANCY请求*/
    ID_LRRC_LPDCP_FAST_DORMANCY_CNF       = (LPDCP_LRRC_MSG_HDR + 0x0a),            /* _H2ASN_MsgChoice LRRC_LPDCP_FAST_DORMANCY_CNF_STRU */ /* PDCP向RRC回复FAST_DORMANCY响应*/

    ID_LRRC_LPDCP_FAST_DORMANCY_IND       = (LPDCP_LRRC_MSG_HDR + 0x0b),            /* _H2ASN_MsgChoice LRRC_LPDCP_FAST_DORMANCY_IND_STRU */ /* PDCP向RRC发送FAST_DORMANCY指示*/

    ID_LRRC_LPDCP_REQ_END                 = (LRRC_LPDCP_MSG_HDR + 0x0a),
    ID_LRRC_LPDCP_IND_END                 = (LPDCP_LRRC_MSG_HDR + 0x0c)
};
typedef VOS_UINT32 LRRC_LPDCP_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 结构名    : LRRC_LPDCP_CFG_MODE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC配置PDCP的命令类型
*****************************************************************************/
enum LPDCP_CFG_MODE_ENUM
{
    LPDCP_CFG_MODE_SETUP                 = 0,                                    /* 初始配置 */
    LPDCP_CFG_MODE_RECFG                 = 1,                                    /* 重配置 */
    LPDCP_CFG_MODE_BUTT
};
typedef VOS_UINT8 LPDCP_CFG_MODE_ENUM_UINT8;

/*****************************************************************************
 结构名    : LRLC_MODE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
enum LRLC_MODE_ENUM
{
    LRLC_MODE_AM                         = 0,                                    /* AM */
    LRLC_MODE_UM                         = 1,                                    /* UM */
    LRLC_MODE_TM                         = 2,                                    /* TM */
    LRLC_MODE_BUTT
};
typedef VOS_UINT8 LRLC_MODE_ENUM_UINT8;

/*****************************************************************************
 结构名    : LPDCP_STOP_CAUSE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
enum LPDCP_STOP_CAUSE_ENUM
{
    LPDCP_STOP_CAUSE_HO                  = 0,                                    /* HO 造成的PDCP停止数传 */
    LPDCP_STOP_CAUSE_REEST               = 1,                                    /* RRC连接重建立造成的PDCP停止数传 */
    LPDCP_STOP_CAUSE_RSVED               = 2,                                    /* 保留 */

    LPDCP_STOP_CAUSE_BUTT
};
typedef VOS_UINT8 LPDCP_STOP_CAUSE_ENUM_UINT8;

/*****************************************************************************
 结构名    : LPDCP_CONTINUE_CAUSE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
enum LPDCP_CONTINUE_CAUSE_ENUM
{
    LPDCP_CONTINUE_CAUSE_HO              = 0,                                    /* HO成功 造成的PDCP恢复数传 */
    LPDCP_CONTINUE_CAUSE_REEST           = 1,                                    /* RRC连接重建立成功，造成的PDCP恢复数传 */
    LPDCP_CONTINUE_CAUSE_RSVED           = 2,                                    /* 保留 */

    LPDCP_CONTINUE_CAUSE_BUTT
};
typedef VOS_UINT8 LPDCP_CONTINUE_CAUSE_ENUM_UINT8;

/*****************************************************************************
 结构名    : LPDCP_ERROR_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
enum LPDCP_ERROR_ENUM
{
    LPDCP_ERROR_INTEGRITY_VERIFY         = 0,                                    /*完整性验证错误*/
    LPDCP_ERROR_OTHER                    = 1,

    LPDCP_ERROR_BUTT
};
typedef VOS_UINT8 LPDCP_ERROR_ENUM_UINT8;

/*****************************************************************************
 结构名    : LPDCP_SN_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
enum LPDCP_SN_TYPE_ENUM
{
    LPDCP_SN_TYPE_7_BITS                 = 0,                                    /* UM模式的PDCP SN占用7bits */
    LPDCP_SN_TYPE_12_BITS                = 1,                                    /* AM/UM模式的PDCP SN占用12bits */
    LPDCP_SN_TYPE_15_BITS                = 2,                                    /* AM模式的PDCP SN占用15bits */
    LPDCP_SN_TYPE_BUTT
};
typedef VOS_UINT8 LPDCP_SN_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名    : LPDCP_RSLT_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : PDCP层配置的结果:成功还是失败
*****************************************************************************/
enum LPDCP_RSLT_ENUM
{
    LPDCP_SUCC                           = 0,
    LPDCP_FAIL                           = 1,
    LPDCP_RSLT_BUTT
};
typedef VOS_UINT8   LPDCP_RSLT_ENUM_UINT8;

/*****************************************************************************
 结构名    : LRRC_LPDCP_SECU_CFG_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : PDCP层安全配置模式
*****************************************************************************/
enum LRRC_LPDCP_SECU_CFG_ENUM
{
    LRRC_LPDCP_SECU_CFG_INTE_CIPH         = 0,               /*同时配置完整性、加解密*/
    LRRC_LPDCP_SECU_CFG_FAIL,                                /* SMC CMD完整性验证失败 */

    LRRC_LPDCP_SECU_CFG_BUTT
};
typedef VOS_UINT8   LRRC_LPDCP_SECU_CFG_ENUM_UINT8;

/*****************************************************************************
 结构名    : LRRC_LPDCP_CIPHER_ALG_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : LPDCP层加密算法
*****************************************************************************/
enum LRRC_LPDCP_CIPHER_ALG_ENUM
{
    LRRC_LPDCP_CIPHER_ALG_NULL            = 0,                /*不加密*/
    LRRC_LPDCP_CIPHER_ALG_SNOW_3G         = 1,                /*SNOW 3G算法加密*/
    LRRC_LPDCP_CIPHER_ALG_AES             = 2,                /*AES 算法加密*/
    LRRC_LPDCP_CIPHER_ALG_ZUC             = 3,                /*ZUC 算法加密*/

    LRRC_LPDCP_CIPHER_ALG_BUTT
};
typedef VOS_UINT8   LRRC_LPDCP_CIPHER_ALG_ENUM_UINT8;

/*****************************************************************************
 结构名    : LRRC_LPDCP_INTEGRITY_ALG_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : 完整性算法
*****************************************************************************/
enum LRRC_LPDCP_INTEGRITY_ALG_ENUM
{
    LRRC_LPDCP_INTEGRITY_ALG_NULL         = 0,
    LRRC_LPDCP_INTEGRITY_ALG_SNOW_3G      = 1,
    LRRC_LPDCP_INTEGRITY_ALG_AES          = 2,
    LRRC_LPDCP_INTEGRITY_ALG_ZUC          = 3,

    LRRC_LPDCP_INTEGRITY_ALG_BUTT
};
typedef VOS_UINT8   LRRC_LPDCP_INTEGRITY_ALG_ENUM_UINT8;

/*****************************************************************************
 结构名    : LRRC_LPDCP_ROHC_PROFILE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : 头压缩算法
*****************************************************************************/
enum LRRC_LPDCP_ROHC_PROFILE_ENUM
{
    LRRC_LPDCP_ROHC_PROFILE_NULL          = 0x0000,
    LRRC_LPDCP_ROHC_PROFILE_RTP_UDP_IP    = 0x0001,
    LRRC_LPDCP_ROHC_PROFILE_UDP_IP        = 0x0002,
    LRRC_LPDCP_ROHC_PROFILE_ESP_IP        = 0x0003,
    LRRC_LPDCP_ROHC_PROFILE_IP            = 0x0004,
    LRRC_LPDCP_ROHC_PROFILE_TCP_IP        = 0x0006,
    LRRC_LPDCP_ROHC_PROFILE_RTP_UDP_IP_V2 = 0x0101,
    LRRC_LPDCP_ROHC_PROFILE_UDP_IP_V2     = 0x0102,
    LRRC_LPDCP_ROHC_PROFILE_ESP_IP_V2     = 0x0103,
    LRRC_LPDCP_ROHC_PROFILE_IP_V2         = 0x0104,

    LRRC_LPDCP_ROHC_PROFILE_BUTT
};
typedef VOS_UINT16   LRRC_LPDCP_ROHC_PROFILE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPDCP_ENTITY_REL_FALG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 指示PDCP实体是否释放
*****************************************************************************/
enum LRRC_LPDCP_ENTITY_REL_FALG_ENUM
{
    LRRC_LPDCP_ENTITY_REL_NOT_NEED         = 0,                                    /* 不需要释放 */
    LRRC_LPDCP_ENTITY_REL_NEED,                                                    /* 需要释放 */
    LRRC_LPDCP_ENTITY_REL_BUTT
};
typedef VOS_UINT8 LRRC_LPDCP_ENTITY_REL_FALG_ENUM_UINT8;
/* gaojishan-fast-dorm-cfg */
/*****************************************************************************
 枚举名    : LRRC_LPDCP_FAST_DORMANCY_CMD_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 指示PDCP启动或停止FAST_DORMANCY
*****************************************************************************/
enum LRRC_LPDCP_FAST_DORMANCY_CMD_ENUM
{
    LRRC_LPDCP_FAST_DORMANCY_STOP         = 0,                                  /* 停止FAST_DORMANCY */
    LRRC_LPDCP_FAST_DORMANCY_START,                                             /* 启动FAST_DORMANCY */
    LRRC_LPDCP_FAST_DORMANCY_BUTT
};
typedef VOS_UINT8 LRRC_LPDCP_FAST_DORMANCY_CMD_ENUM_UINT8;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
 结构名    : LPDCP_UM_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    LPDCP_SN_TYPE_ENUM_UINT8             enPdcpSnLgthType;
    VOS_UINT8                           aucRsv[3];
} LPDCP_UM_INFO_STRU;

/*****************************************************************************
 结构名    : LPDCP_AM_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enStatusRptReq;
    LPDCP_SN_TYPE_ENUM_UINT8             enPdcpSnLgthType;
    VOS_UINT8                            aucRsv[2];
} LPDCP_AM_INFO_STRU;

/*****************************************************************************
 结构名    : LPDCP_CFG_INFO_CHOICE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    LRLC_MODE_ENUM_UINT8                 enRlcMode;
    VOS_UINT8                           aucRsv[3];

    union
    {
        LPDCP_UM_INFO_STRU               stUmPdcpInfo;
        LPDCP_AM_INFO_STRU               stAmPdcpInfo;
    }u;

} LPDCP_CFG_INFO_CHOICE_STRU;

/*****************************************************************************
 结构名    : LRRC_LPDCP_ROHC_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 头压缩/解压缩配置参数结构
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enCompressFlag;
    VOS_UINT8                           aucRev[3];
    VOS_UINT16                          usMaxUlCid;
    VOS_UINT16                          usUsedProfileNum;
    LRRC_LPDCP_ROHC_PROFILE_ENUM_UINT16   ausProfile[LRRC_LPDCP_MAX_PROFILE_NUM];
}LRRC_LPDCP_ROHC_INFO_STRU;

/*****************************************************************************
 结构名    : LPDCP_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRbId;
    /* 指示PDCP实体是否需要先释放再配置,0:不需要释放,1:需要先释放,然后根据最新参数进行配置  */
    LRRC_LPDCP_ENTITY_REL_FALG_ENUM_UINT8 enRelInd;
    VOS_UINT8                           ucEpsbId;
    VOS_UINT8                           aucRsv[1];
    VOS_UINT32                          ulDiscardTimer;

    LRRC_LPDCP_ROHC_INFO_STRU             stRohcInfo;
    LPDCP_CFG_INFO_CHOICE_STRU           stPdcpCfgChoice;
} LPDCP_INFO_STRU;

/*============================= RRC和PDCP间的接口 =============================*/
/*****************************************************************************
 结构名    : LRRC_LPDCP_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    LPDCP_CFG_MODE_ENUM_UINT8            enConfigMode;

    VOS_UINT8                           ucPdcpNum;

    LPDCP_INFO_STRU                      stPdcpInfo[PS_MAX_RB_NUM];
} LRRC_LPDCP_CONFIG_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPDCP_CONFIG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    LPDCP_RSLT_ENUM_UINT8                enResult;
    VOS_UINT8                           aucRsv[1];
} LRRC_LPDCP_CONFIG_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPDCP_RELEASE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    VOS_UINT8                           aucRsv[1];
    VOS_UINT8                           ucPdcpNum;

    VOS_UINT8                           aucPdcpRbId[PS_MAX_RB_NUM];
} LRRC_LPDCP_RELEASE_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPDCP_RELEASE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    LPDCP_RSLT_ENUM_UINT8                enResult;
    VOS_UINT8                           aucRsv[1];
} LRRC_LPDCP_RELEASE_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPDCP_STOP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    LPDCP_STOP_CAUSE_ENUM_UINT8          enStopCause;

    VOS_UINT8                           ucPdcpNum;
    VOS_UINT8                           aucPdcpRbId[PS_MAX_RB_NUM];
    VOS_UINT8                           ucUmDrbContRohcFlg;
    VOS_UINT8                           aucResv[3];
} LRRC_LPDCP_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPDCP_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef LRRC_LPDCP_CONFIG_CNF_STRU LRRC_LPDCP_STOP_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPDCP_CONTINUE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    LPDCP_CONTINUE_CAUSE_ENUM_UINT8      enContinueCause;

    VOS_UINT8                           ucPdcpNum;
    VOS_UINT8                           aucPdcpRbId[PS_MAX_RB_NUM];
} LRRC_LPDCP_CONTINUE_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPDCP_CONTINUE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef LRRC_LPDCP_CONFIG_CNF_STRU LRRC_LPDCP_CONTINUE_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPDCP_AM_DATA_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usSeqNum;

    VOS_UINT8                           ucRbId;

    /* 当AM RLC实体确认对端接收到RLC SDU后,是否需要使用PDCP_CNF原语向高层发送确认
        1:表示RRC需要等待CNF消息， 0:表示RRC不需要等CNF消息 */
    PS_BOOL_ENUM_UINT8                  enCnfIndFlg;

    VOS_UINT32                          ulDataLength;
    VOS_UINT8                           aucData[4];
} LRRC_LPDCP_AM_DATA_REQ_STRU;

/*****************************************************************************
 结构名    : RRC_PDCP_SMC_CMP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef LRRC_LPDCP_AM_DATA_REQ_STRU LRRC_LPDCP_SMC_CMP_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPDCP_DATA_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usSeqNum;

    LPDCP_RSLT_ENUM_UINT8                enResult;
    VOS_UINT8                           aucRsv[1];
} LRRC_LPDCP_DATA_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPDCP_UM_DATA_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usSeqNum;

    VOS_UINT8                           ucRbId;
    VOS_UINT8                           aucRsv[1];

    VOS_UINT32                          ulDataLength;
    VOS_UINT8                           aucData[4];
} LRRC_LPDCP_UM_DATA_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPDCP_AM_DATA_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT8                           ucRbId;
    VOS_UINT8                           ucPdcpHdr;
    VOS_UINT8                           aucRsv[2];

    VOS_UINT32                          ulDataLength;
    VOS_UINT32                          ulCount;
    VOS_UINT8                           aucData[4];
} LRRC_LPDCP_AM_DATA_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LPDCP_UM_DATA_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT8                           ucRbId;
    VOS_UINT8                           aucRsv[3];

    VOS_UINT32                          ulDataLength;
    VOS_UINT32                          ulCount;
    VOS_UINT8                           aucData[4];
} LRRC_LPDCP_UM_DATA_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LPDCP_ERROR_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    LPDCP_ERROR_ENUM_UINT8               enErrInd;
    VOS_UINT8                           aucRsv[3];

} LRRC_LPDCP_ERROR_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LPDCP_SECU_CONFIG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    LRRC_LPDCP_INTEGRITY_ALG_ENUM_UINT8   enIntegrityProtAlg;
    LRRC_LPDCP_CIPHER_ALG_ENUM_UINT8      enCipherAlg;
    LRRC_LPDCP_SECU_CFG_ENUM_UINT8        enConfigMode;
    VOS_UINT8                           ucRev;
} LRRC_LPDCP_SECU_CONFIG_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPDCP_SECU_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
    LRRC_LPDCP_SECU_CONFIG_INFO_STRU      stSecuConfigInfo;
} LRRC_LPDCP_SECU_CONFIG_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPDCP_SECU_CONFIG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef LRRC_LPDCP_CONFIG_CNF_STRU LRRC_LPDCP_SECU_CONFIG_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPDCP_COUNTER_CHECK_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LRRC_LPDCP_COUNTER_CHECK_REQ_STRU;

/*****************************************************************************
 结构名    : RRC_PDCP_COUNTER_CHECK_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRbId;
    VOS_UINT8                           aucRev[3];
    VOS_UINT32                          ulUlCount;
    VOS_UINT32                          ulDlCount;
} LRRC_LPDCP_COUNTER_CHECK_CNF_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPDCP_COUNTER_CHECK_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRsv[1];
    VOS_UINT8                           ucPdcpNum;

    LRRC_LPDCP_COUNTER_CHECK_CNF_INFO_STRU     stCounterCheckCnfInfo[PS_MAX_RB_NUM];
} LRRC_LPDCP_COUNTER_CHECK_CNF_STRU;
/* gaojishan-fast-dorm-cfg */
/*****************************************************************************
 结构名    : LRRC_LPDCP_FAST_DORMANCY_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32          enMsgName;                         /*_H2ASN_Skip*/

    VOS_UINT16                               usOpId;

    LRRC_LPDCP_FAST_DORMANCY_CMD_ENUM_UINT8  enFastDormancyCmd;
    VOS_UINT8                                aucRsv[1];

    VOS_UINT32                               ulFastDormancyTimer;               /*定时器时长以ms为单位*/
} LRRC_LPDCP_FAST_DORMANCY_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPDCP_FAST_DORMANCY_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                            /*_H2ASN_Skip*/

    VOS_UINT16                            usOpId;

    LPDCP_RSLT_ENUM_UINT8                 enResult;
    VOS_UINT8                             aucRsv[1];
} LRRC_LPDCP_FAST_DORMANCY_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPDCP_FAST_DORMANCY_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                            /*_H2ASN_Skip*/

} LRRC_LPDCP_FAST_DORMANCY_IND_STRU;

typedef struct
{
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgID;            /*_H2ASN_MsgChoice_Export LRRC_LPDCP_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LRRC_LPDCP_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}LRRC_LPDCP_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    LRRC_LPDCP_MSG_DATA                    stMsgData;
}LRrcPdcpInterface_MSG;

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
