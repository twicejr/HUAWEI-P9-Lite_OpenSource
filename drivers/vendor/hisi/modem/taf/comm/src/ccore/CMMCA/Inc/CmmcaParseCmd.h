/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CmmcaParseCmd.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2014年2月15日
  最近修改   :
  功能描述   : CmmcaParseCmd.c的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年2月15日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CMMCAPARSECMD_H__
#define __CMMCAPARSECMD_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "CmmcaCtxPkt.h"
#include "CmmcaCmdComm.h"
#include "CmmcaMmcInterface.h"
#include "CmmcaMtcInterface.h"

#include "CmmcaRcmInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#if (FEATURE_ON == FEATURE_CL_INTERWORK)

/* CBPCA发来的码流，对于不同的CmdId,定义其有效字节长度 */
/* REG 相关的CMD码流长度定义 Begin */
#define CMMCA_CMD_RAT_MODE_REQ_LEN                          (4)
#define CMMCA_CMD_RAT_MODE_RSP_LEN                          (4)

#define CMMCA_CMD_RAT_POWERUP_REQ_LEN                       (3)
#define CMMCA_CMD_RAT_POWERUP_RSP_LEN                       (4)

#define CMMCA_CMD_RAT_POWERDOWN_REQ_LEN                     (3)
#define CMMCA_CMD_RAT_POWERDOWN_RSP_LEN                     (3)

#define CMMCA_CMD_RAT_SEARCH_REQ_LEN                        (3)
#define CMMCA_CMD_RAT_SEARCH_RSP_LEN                        (14)

#define CMMCA_CMD_RAT_PS_REG_REQ_LEN                        (5)

#define CMMCA_CMD_RAT_PS_REG_RSP_LEN                        (17)

#define CMMCA_CMD_RAT_CELL_INFO_PS_REG_REQ_LEN              (57)

#define CMMCA_CMD_RAT_CELL_INFO_PS_REG_RSP_LEN              (18)

#define CMMCA_CMD_RAT_ACQ_REQ_LEN                           (4)
#define CMMCA_CMD_RAT_ACQ_RSP_LEN                           (16)

#define CMMCA_CMD_RAT_NO_SERVICE_REQ_LEN                    (4)
#define CMMCA_CMD_RAT_NO_SERVICE_RSP_LEN                    (4)

#define CMMCA_CMD_RAT_NTW_ST_CHG_IND_LEN                    (17)

#define CMMCA_CMD_RAT_REJ_IND_LEN                           (6)

#define CMMCA_CMD_RAT_PKT_DATA_CMD_REQ_LEN                  (4)
#define CMMCA_CMD_RAT_PKT_DATA_CMD_RSP_LEN                  (4)
/* REG 相关的CMD码流长度定义 End */

#define CMMCA_CMD_SYSTEM_CHG_RSP_LEN                        (5)

/* PKT 相关的CMD码流长度定义 Begin */
/* CBPCA发送过来pdn设置请求消息中，APN最大有效长度 */
#define CMMCA_SET_PDN_TAB_REQ_APN_MAX_LEN                   (101)

#define CMMCA_CMD_SET_PDN_TAB_REQ_LEN                       (sizeof(CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16) \
                                                            + sizeof(CMMCA_MMC_RAT_ID_ENUM_UINT8)\
                                                            + (CMMCA_SET_PDN_TAB_REQ_APN_MAX_LEN + sizeof(VOS_UINT8) + sizeof(CMMCA_PDN_REQUEST_TYPE_ENUM_UINT8)) * (CMMCA_SUPPORTED_PDN_NUM_MAX))
#define CMMCA_CMD_SET_PND_PCO_AUTH_RSP_LEN                  (4)

#define CMMCA_RAT_AUTH_MAX_MODEL_NAME_LEN                   (72)

#define CMMCA_RAT_AUTH_MAX_USER_NAME_LEN                    (72)

#define CMMCA_RAT_AUTH_MAX_PASSWORD_LEN                     (16)

#define CMMCA_CMD_SET_PDN_PCO_AUTH_REQ_LEN                  (sizeof(CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16) \
                                                            + sizeof(CMMCA_MMC_RAT_ID_ENUM_UINT8) \
                                                            + sizeof(VOS_UINT8) + sizeof(VOS_UINT8)\
                                                            + (sizeof(VOS_UINT8) * CMMCA_RAT_AUTH_MAX_MODEL_NAME_LEN) \
                                                            + (sizeof(VOS_UINT8) * CMMCA_RAT_AUTH_MAX_USER_NAME_LEN) \
                                                            + sizeof(VOS_UINT8) \
                                                            + (sizeof(VOS_UINT8) * CMMCA_RAT_AUTH_MAX_PASSWORD_LEN))

#define CDMA_CMD_CONN_STATE_INFO_LEN                        (7)

#define CDMA_CMD_MEASUREMENT_INFO_LEN                       (28)

#define CDMA_CMD_EVENT_INFO_LEN                             (4)



#define CMMCA_CMD_SET_PDN_TAB_RSP_LEN                       (4)

/* MMC接口中激活默认承载的码流长度为133字节，但是目前只使用前6个字节 */
#define CMMCA_CMD_DEFAULT_BEAR_CONN_REQ_LEN                 (6)
#define CMMCA_CMD_DEFAULT_BEAR_CONN_RSP_LEN                 (205)

#define CMMCA_CMD_BEAR_DISC_REQ_LEN                         (6)
#define CMMCA_CMD_BEAR_DISC_RSP_LEN                         (6)

#define CMMCA_CMD_BEAR_DISC_IND_LEN                         (5)

#define CMMCA_CMD_RAT_BEAR_DETACH_REQ_LEN                   (3)
#define CMMCA_CMD_RAT_BEAR_DETACH_RSP_LEN                   (4)
/* PKT 相关的CMD码流长度定义 End */


/* Max num of CDMA PNs configured by LTE for SIB8 measurements per band. it shall be 16*/
#define CMMCA_MMC_MAX_SIB8_REC_NUM                          (7)     /* limited by hw */

/* Max num of PLMNs configured by CDMA for LTE neighboring cell measurements*/
#define CMMCA_MMC_MAX_NUM_EUTRA_PLMN                        (8)

/*Maximum number of entries in each of the cell lists in a measurement object, it's 32 in TS 36.331*/
#define CMMCA_MMC_MAX_CELL_NUM                              (8)
#endif

/* 每个字节有8位，移位操作时使用 */
#define CMMCA_BITS_PER_OCTET                                (8)

#define CMMCA_OCTET_LOW_FOUR_BITS                           (0x0F)              /* 获取一个字节中的低4位 */
#define CMMCA_WORD_LOW_EIGHT_BITS                           (0xFF)              /* 获取一个字中的低8位 */

#define CMMCA_OCTET_MOVE_EIGHT_BITS                         (0x08)              /* 将一个字节移动8位 */
#define CMMCA_OCTET_MOVE_SIXTEEN_BITS                       (16)                /* 将一个字节移动16位 */
#define CMMCA_OCTET_MOVE_FOUR_BITS                          (0x04)              /* 将一个字节移动4位 */

#define CMMCA_U32_MCC_CONTAN_OCTET_NUM                      (4)
#define CMMCA_U16_MCC_CONTAN_OCTET_NUM                      (2)
#define CMMCA_U32_MNC_CONTAN_OCTET_NUM                      (4)
#define CMMCA_U16_MNC_CONTAN_OCTET_NUM                      (2)

#define CMMCA_BCD_PLMN_ZERO_TRANSFER                        (0x0A)              /* 设置PLMN ID的内容0转换为A */
#define CMMCA_MNC_THIRD_OCTECT_ZERO_CHANGE                  (0x0F)              /* MNC最后一位0X00转换为0X0F */
#define CMMCA_MNC_THIRD_OCTECT_INDEX                        (0x02)              /* MNC最后一位索引为2 */
#define CMMCA_U32_MNC_THIRD_OCTET_NON_EXIST_VALUE           (0X0F)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
 枚举名   :CMMCA_RAT_MMC_PKT_ERRCODE
 枚举说明 :回复PDN连接请求的错误码
 1.日    期   : 2014年01月23日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_RAT_MMC_PKT_ERRCODE
{
    /* Local */
    CMMCA_RAT_MMC_PKT_ERRCODE_CONN_IS_RELEASING = 0xA0,                         /* 正在断开拨号连接，又要发起拨号回复的错误码 */
    CMMCA_RAT_MMC_PKT_ERRCODE_WATI_IPV6_RA_EXP,                                 /* IPV6激活，等待RA超时 */

    CMMCA_RAT_MMC_PKT_ERRCODE_INVILID_PARA,
    CMMCA_RAT_MMC_PKT_ERRCODE_INVILID_CID,
    CMMCA_RAT_MMC_PKT_ERRCODE_SIM_INVILID,

    CMMCA_RAT_MMC_PKT_ERRCODE_UNKNOWN,

    /* Refer to TS 24.301 section 9.9.4.4  */
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_OPERATOR_DETERMINED_BARRING,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_INSUFFICIENT_RESOURCES,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_MISSING_OR_UKNOWN_APN,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_UNKNOWN_PDP_ADDR_OR_TYPE,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_USER_AUTHENTICATION_FAIL ,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_ACTIVATION_REJECTED_BY_GGSN,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_ACTIVATION_REJECTED_UNSPECIFIED,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_SERVICE_OPTION_NOT_SUPPORTED,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_SERVICE_OPTION_TEMP_OUT_ORDER,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_NSAPI_ALREADY_USED,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_REGULAR_DEACTIVATION,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_QOS_NOT_ACCEPTED,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_NETWORK_FAILURE,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_SEMANTIC_ERR_IN_TFT,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_SYNTACTIC_ERR_IN_TFT,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_UKNOWN_PDP_CONTEXT,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_SEMANTIC_ERR_IN_PACKET_FILTER,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_SYNCTACTIC_ERR_IN_PACKET_FILTER,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_PDP_CONTEXT_WITHOUT_TFT_ACTIVATED,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_LAST_PDN_DISCONN_NOT_ALLOWED,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_PDP_TYPE_IPV4_ONLY_ALLOWED,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_PDP_TYPE_IPV6_ONLY_ALLOWED,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_INFORMATION_NOT_RECEIVED,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_PDN_CONNECTION_DOES_NOT_EXIST,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_COLLISION_WITH_NW_INITIATED_REQUEST,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_UNSUPPORTED_QCI_VALUE,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_INVALID_TI,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_SEMANTICALLY_INCORRECT_MESSAGE,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_INVALID_MANDATORY_INFO,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_MSG_TYPE_NON_EXISTENT,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_MSG_TYPE_NOT_COMPATIBLE,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_IE_NON_EXISTENT,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_CONDITIONAL_IE_ERR,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_MSG_NOT_COMPATIBLE,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_PROTOCOL_ERR_UNSPECIFIED,
    CMMCA_RAT_MMC_PKT_ERRCODE_NW_APN_RESTRICTION_INCOMPATIBLE,

    CMMCA_RAT_MMC_PKT_ERRCODE_PS_DETACH,

    CMMCA_RAT_MMC_PKT_ERRCODE_DETACH_NOT_REATTACH,

    CMMCA_RAT_MMC_PKT_ERRCODE_NOERROR     = 0xff

};

typedef VOS_UINT8 CMMCA_RAT_MMC_PKT_ERRCODE_UINT8;

/*****************************************************************************
 枚举名   :CMMCA_RAT_MMC_RESULT_ENUM
 枚举说明 :回复CMMC的结果
 1.日    期   : 2014年01月08日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_RAT_MMC_RESULT_ENUM
{
    /*
     TRUE = Success, FALSE = Failed, not legitimate
     */
    CMMCA_RAT_MMC_RESULT_FAIL,
    CMMCA_RAT_MMC_RESULT_SUCC,

    CMMCA_RAT_MMC_RESULT_BUTT
};

typedef VOS_UINT8 CMMCA_RAT_MMC_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名   :CMMCA_RAT_MMC_PDN_TAB_SET_RESULT_ENUM
 枚举说明 :RAT回复CMMC设置PDN TAB的结果
 1.日    期   : 2014年01月08日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_RAT_MMC_PDN_TAB_SET_RESULT_ENUM
{
    /* 0 = success
        1 = fail
     */
    CMMCA_RAT_MMC_PDN_TAB_SET_RESULT_SUCC,
    CMMCA_RAT_MMC_PDN_TAB_SET_RESULT_FAIL,

    CMMCA_RAT_MMC_PDN_TAB_SET_RESULT_BUTT
};

typedef VOS_UINT8 CMMCA_RAT_MMC_PDN_TAB_SET_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名   :CMMCA_SET_PDN_PCO_AUTH_RESULT_ENUM
 枚举说明 :鉴权的结果
 1.日    期   : 2014年10月27日
   作    者   : j00174725
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_SET_PDN_PCO_AUTH_RESULT_ENUM
{
    /* 0 = success
       1 = fail
     */
    CMMCA_SET_PDN_PCO_AUTH_RESULT_SUCC  = 0,
    CMMCA_SET_PDN_PCO_AUTH_RESULT_FAIL,

    CMMCA_SET_PDN_PCO_AUTH_RESULT_BUTT
};

typedef VOS_UINT8 CMMCA_SET_PDN_PCO_AUTH_RESULT_ENUM_UINT8;


/*****************************************************************************
 枚举名   :CMMCA_RAT_MMC_BEAR_CONN_RESULT_ENUM
 枚举说明 :RAT回复CMMC承载激活的结果
 1.日    期   : 2014年01月08日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_RAT_MMC_BEAR_CONN_RESULT_ENUM
{
    /* 0 = success
        1 = fail
        2 = duplicate
        3 = re-negotiate
     */
    CMMCA_RAT_MMC_BEAR_CONN_RESULT_SUCC,
    CMMCA_RAT_MMC_BEAR_CONN_RESULT_FAIL,

    CMMCA_RAT_MMC_BEAR_CONN_RESULT_BUTT
};

typedef VOS_UINT8 CMMCA_RAT_MMC_BEAR_CONN_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名   :CMMCA_MMC_MODE_RSP_RESULT_ENUM
 枚举说明 :RAT ID
 1.日    期   : 2014年01月27日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_MMC_MODE_RSP_RESULT_ENUM
{
    CMMCA_MMC_MODE_RSP_SUCC,
    CMMCA_MMC_MODE_RSP_FAIL,
    CMMCA_MMC_MODE_RSP_BUTT
};

typedef VOS_UINT8 CMMCA_MMC_MODE_RSP_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名   : CMMCA_IRAT_HO_CAUSE_ENUM
 枚举说明 : RAT_ID类型
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_IRAT_HO_CAUSE_ENUM
{
    CMMCA_IRAT_HO_CAUSE_REDIRECTION = 0,
    CMMCA_IRAT_HO_CAUSE_RESELECTION,
    CMMCA_IRAT_HO_CAUSE_CELLCHANGEORDER,
    CMMCA_IRAT_HO_CAUSE_HANDOVER,
    CMMCA_IRAT_HO_CAUSE_INVALID,
    CMMCA_IRAT_HO_CAUSE_HO_CAUSE_BUTT
};
typedef VOS_UINT8 CMMCA_IRAT_HO_CAUSE_ENUM_UINT8;

/*****************************************************************************
 枚举名   : CMMCA_RAT_ACQ_REQ_REASON_ENUM
 枚举说明 : 搜网请求原因
 1.日    期   : 2014年02月11日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_RAT_ACQ_REQ_REASON_ENUM
{
    CMMCA_RAT_ACQ_REQ_REASON_INIT_ACQ = 0,       /* LTE shall conduct the frequency band scan per relevant standard and 3GPP BST table. */
    CMMCA_RAT_ACQ_REQ_REASON_OOS_ACQ,            /* Sysytem Acq after Out of Service Wake*/
    CMMCA_RAT_ACQ_REQ_REASON_SYS_LOSS_ACQ,       /* System Acq due to other RAT lost   */
    CMMCA_RAT_ACQ_REQ_REASON_MCC_ACQ,            /* per VZW request, LTE shall scan frequency bands in the order defined in 3GPP BST table. */
    CMMCA_RAT_ACQ_REQ_REASON_BSR_ACQ,
    CMMCA_RAT_ACQ_REQ_REASON_BUTT
};
typedef VOS_UINT8 CMMCA_RAT_ACQ_REQ_REASON_ENUM_UINT8;

/*****************************************************************************
 枚举名   : CMMCA_RAT_ACQ_RESULT_ENUM
 枚举说明 : 搜网结果
 1.日    期   : 2014年02月11日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_RAT_ACQ_RESULT_ENUM
{
    CMMCA_RAT_ACQ_RESULT_ACQUIRED = 0, /* an acceptable system is acquired. The info will be included in RatSysInfo. */
    CMMCA_RAT_ACQ_RESULT_ACQFAILED,    /* no system is acquired. RatSysInfo is invalid. */
    CMMCA_RAT_ACQ_RESULT_CMD_REJ,      /* reject request for reasons. RatSysInfo is invalid. */
    CMMCA_RAT_ACQ_RESULT_RESULT_BUTT
};
typedef VOS_UINT8 CMMCA_RAT_ACQ_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名   : CMMCA_RAT_GMSS_PRIORITY_CLASS_ENUM
 枚举说明 : 搜网优先级类别
 1.日    期   : 2014年02月11日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_RAT_GMSS_PRIORITY_CLASS_ENUM
{
    CMMCA_RAT_GMSS_PRIORITY_CLASS_HOME = 0,
    CMMCA_RAT_GMSS_PRIORITY_CLASS_PREF,
    CMMCA_RAT_GMSS_PRIORITY_CLASS_ANY,
    CMMCA_RAT_GMSS_PRIORITY_CLASS_UNAVL,  /* sys is not acquried, priclass is not available */
    CMMCA_RAT_GMSS_PRIORITY_CLASS_NOCHG,  /* sys is acquried, priclass is same as before. MMC internal use */
    CMMCA_RAT_GMSS_PRIORITY_CLASS_BUTT
};
typedef VOS_UINT8 CMMCA_RAT_GMSS_PRIORITY_CLASS_ENUM_UINT8;

/*****************************************************************************
 枚举名   : CMMCA_RAT_REG_RESULT_ENUM
 枚举说明 : 注册结果
 1.日    期   : 2014年02月11日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_RAT_REG_RESULT_ENUM
{
    CMMCA_RAT_REG_RESULT_REGISTERED = 0, /* LTE has registered on the qualified system. System info will be included in RatSysInfo. */
    CMMCA_RAT_REG_RESULT_ACQUIRED,       /* an acceptable system is acquired but registration fails. System info will be included inRatSysInfo. */
    CMMCA_RAT_REG_RESULT_ACQFAILED,      /* no system is acquired. RatSysInfo is invalid. */
    CMMCA_RAT_REG_RESULT_CMD_REJ,        /* reject request for reasons. RatSysInfo is invalid. */
    CMMCA_RAT_REG_RESULT_BUTT
};
typedef VOS_UINT8 CMMCA_RAT_REG_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CMMCA_RAT_CL_REG_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : CL的VIA形态使用的ATTACH注册结果上报时所处的阶段
*****************************************************************************/
enum CMMCA_RAT_CL_REG_STATUS_ENUM
{
    CMMCA_RAT_CL_REG_STATUS_ATTACH_NOT_SEND            = 0x00,
    CMMCA_RAT_CL_REG_STATUS_ATTACH_SEND_WAIT_CN_RSP    = 0x01,
    CMMCA_RAT_CL_REG_STATUS_ATTACH_RCV_CN_REJ          = 0x02,
    CMMCA_RAT_CL_REG_STATUS_ATTACH_RCV_CN_ACP          = 0x03,
    CMMCA_RAT_CL_REG_STATUS_ATTACH_T3410_EXP           = 0x04,
    CMMCA_RAT_CL_REG_STATUS_ATTACH_CMP_SEND            = 0x05,
    CMMCA_RAT_CL_REG_STATUS_NOT_ATTACH_PROCEDURE       = 0x06
};
typedef VOS_UINT8 CMMCA_RAT_ATTACH_CL_REG_STATUS_ENUM8;

/*****************************************************************************
 枚举名   : CMMCA_RAT_ATTACH_TYPE_ENUM
 枚举说明 : 注册结果
 1.日    期   : 2014年02月11日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_RAT_ATTACH_TYPE_ENUM
{
    CMMCA_RAT_ATTACH_TYPE_INITIAL  = 1,
    CMMCA_RAT_ATTACH_TYPE_HANDOVER = 3,
    CMMCA_RAT_ATTACH_TYPE_BUTT
};
typedef VOS_UINT8 CMMCA_RAT_ATTACH_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名   : CMMCA_RAT_NOTIFY_CAUSE_ENUM
 枚举说明 : RAT NOTIFY CAUSE
 1.日    期   : 2014年02月11日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_RAT_NOTIFY_CAUSE_ENUM
{
    CMMCA_RAT_NOTIFY_CAUSE_AUTOMATIC = 0,     /* reason not specified below. For update LTE status to MMC. */
    CMMCA_RAT_NOTIFY_CAUSE_SYSLOST,           /* after LTE loses system, if no qualified system can be acquired after recovery scan, LTE shall send Ind with this cause. */
    CMMCA_RAT_NOTIFY_CAUSE_PS_REL,            /* PS service released without request from MMC. */
    CMMCA_RAT_NOTIFY_CAUSE_PS_CHG,            /* reserved. not use */
    CMMCA_RAT_NOTIFY_CAUSE_PRI_CHG,           /* LTE camps on a new LTE network with a different priority class from before. */
    CMMCA_RAT_NOTIFY_CAUSE_RECOVERY,          /* after sending LTE_SYSLOST, once LTE is reacquired, send Ind with this cause to report this event. */
    CMMCA_RAT_NOTIFY_CAUSE_HO_REQ,            /* reserved. not use */
    CMMCA_RAT_NOTIFY_CAUSE_ACQED,             /* LTE camps on a new system. */
    CMMCA_RAT_NOTIFY_CAUSE_SUSPEND,           /* network or internal RAT case where no activity allowed on RAT until RAT_RESUME or power cycle*/
    CMMCA_RAT_NOTIFY_CAUSE_RESUME,            /* Exit RAT suspend state*/
    CMMCA_RAT_NOTIFY_CAUSE_PS_DEREGED = 0x20, /* LTE report detached from network */
    CMMCA_RAT_NOTIFY_CAUSE_BUTT
};
typedef VOS_UINT8 CMMCA_RAT_NOTIFY_CAUSE_ENUM_UINT8;

/*****************************************************************************
 枚举名   : CMMCA_MMC_RAT_CPST_ENUM
 枚举说明 : CAMP STATE
 1.日    期   : 2014年02月11日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_RAT_CPST_ENUM
{
    CMMCA_RAT_CPST_SYSLOST = 0, /* LTE loses system. */
    CMMCA_RAT_CPST_INIT,        /* initial state after power up. */
    CMMCA_RAT_CPST_ACQUIRED,    /* LTE has camped on the best available system but registration has not succeeded or not conducted. */
    CMMCA_RAT_CPST_REGISTERED,  /* LTE has succeeded registration and attach on the best available system. */
    CMMCA_RAT_CPST_CONNECT,     /* LTE is in connected state. */
    CMMCA_RAT_CPST_DISABLED,    /* LTE is in Disabled state after No_Service_Req. */
    CMMCA_RAT_CPST_POWERED_DOWN,   /* LTE is in powered down state. */
    CMMCA_RAT_CPST_BUTT
};
typedef VOS_UINT8 CMMCA_RAT_CPST_ENUM_UINT8;

/*****************************************************************************
 枚举名   : CMMCA_RAT_PS_TYPE_ENUM
 枚举说明 : PS TYPE
 1.日    期   : 2014年02月19日
   作    者   : b00269685
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_RAT_PS_TYPE_ENUM
{
    CMMCA_RAT_PS_TYPE_NO_PS = 0,
    CMMCA_RAT_PS_TYPE_1xRTT,
    CMMCA_RAT_PS_TYPE_HRPD,
    CMMCA_RAT_PS_TYPE_EHRPD,
    CMMCA_RAT_PS_TYPE_LTE,
    CMMCA_RAT_PS_TYPE_UTRAN,
    CMMCA_RAT_PS_TYPE_GERAN,
    CMMCA_RAT_PS_TYPE_BUTT
};
typedef VOS_UINT8 CMMCA_RAT_PS_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名   : CMMCA_RAT_SYSTEM_TYPE_ENUM
 枚举说明 : SYSTEM TYPE原因
 1.日    期   : 2014年02月11日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_RAT_SYSTEM_TYPE_ENUM
{
    CMMCA_RAT_SYSTEM_TYPE_CDMA = 0,
    CMMCA_RAT_SYSTEM_TYPE_UTRAN,
    CMMCA_RAT_SYSTEM_TYPE_GERAN,
    CMMCA_RAT_SYSTEM_TYPE_EUTRAN,
    CMMCA_RAT_SYSTEM_TYPE_INVALID,
    CMMCA_RAT_SYSTEM_TYPE_BUTT
};
typedef VOS_UINT8 CMMCA_RAT_SYSTEM_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名   : CMMCA_MMC_RAT_NOSVC_CAUSE_ENUM
 枚举说明 : NO SERVICE原因
 1.日    期   : 2014年02月11日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_MMC_RAT_NOSVC_CAUSE_ENUM
{
    CMMCA_MMC_RAT_NOSVC_CAUSE_INITIAL_SCAN,
    CMMCA_MMC_RAT_NOSVC_CAUSE_RAT_NO_IN_MSPL,
    CMMCA_MMC_RAT_NOSVC_CAUSE_OTHER_RAT_FOUND,    /* Another RAT acquired, Maybe equal or less preferred */
    CMMCA_MMC_RAT_NOSVC_CAUSE_MORE_PREF_RAT_FOUND,/* More Preferred RAT acquired */
    CMMCA_MMC_RAT_NOSVC_CAUSE_PKT_SVC_CMD,        /* Cmd from MMC Packet Service Module */
    CMMCA_MMC_RAT_NOSVC_CAUSE_OPMODE_CHANGE,      /* Operation Mode change(Global, LTE Only, ...) */
    CMMCA_MMC_RAT_NOSVC_CAUSE_RAT_BLOCKED,
    CMMCA_MMC_RAT_NOSVC_CAUSE_OOSA,
    CMMCA_MMC_RAT_NOSVC_CAUSE_UICC_ERROR,
    CMMCA_MMC_RAT_NOSVC_CAUSE_BUTT
};
typedef VOS_UINT8 CMMCA_MMC_RAT_NOSVC_CAUSE_ENUM_UINT8;

/*****************************************************************************
 枚举名   : CMMCA_RAT_MMC_STATUS_ENUM
 枚举说明 : RAT STATUS
 1.日    期   : 2014年02月11日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_RAT_MMC_STATUS_ENUM
{
    CMMCA_RAT_MMC_STATUS_SUCCESS=0,        /* Success */
    CMMCA_RAT_MMC_STATUS_ACQ_FAIL,         /* System could not be acquired */
    CMMCA_RAT_MMC_STATUS_PS_REG_FAIL,      /* PS registration failed on the system */
    CMMCA_RAT_MMC_STATUS_PS_SESSION_FAIL,  /* PS session could not be opened on the system */
    CMMCA_RAT_MMC_STATUS_FAIL,             /* Failure due to other unknown reasons */
    CMMCA_RAT_MMC_STATUS_CMD_INVALID,
    CMMCA_RAT_MMC_STATUS_CHG_HRPD_SUCCESS,

    CMMCA_RAT_MMC_STATUS_BUTT
} ;
typedef VOS_UINT8 CMMCA_RAT_MMC_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名   : CMMCA_CDMA_TYPE_ENUM
 枚举说明 : CDMA TYPE
 1.日    期   : 2014年02月11日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_CDMA_TYPE_ENUM
{
   CMMCA_CDMA_TYPE_1XRTT = 0,
   CMMCA_CDMA_TYPE_HRPD,
   CMMCA_CDMA_TYPE_NULL,
   CMMCA_CDMA_TYPE_BUTT
};
typedef VOS_UINT8 CMMCA_CDMA_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名   : CMMCA_UTRAN_CELL_TYPE_ENUM
 枚举说明 : Utran cell type定义
 1.日    期   : 2014年02月11日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_UTRAN_CELL_TYPE_ENUM
{
    CMMCA_UTRAN_CELL_TYPE_FDD,
    CMMCA_UTRAN_CELL_TYPE_TDD,
    CMMCA_UTRAN_CELL_TYPE_BUTT
};
typedef VOS_UINT8 CMMCA_UTRAN_CELL_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名   : CMMCA_GERAN_BAND_IND_ENUM
 枚举说明 : geran band ind定义
 1.日    期   : 2014年02月11日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_GERAN_BAND_IND_ENUM
{
    CMMCA_GERAN_BAND_IND_DCS1800,
    CMMCA_GERAN_BAND_IND_PCS1900,
    CMMCA_GERAN_BAND_IND_BUTT
};
typedef VOS_UINT8 CMMCA_GERAN_BAND_IND_ENUM_UINT8;

/*****************************************************************************
 枚举名   : CMMCA_RAT_MODE_ENUM
 枚举说明 : MODE定义
 1.日    期   : 2014年02月11日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_RAT_MODE_ENUM
{
   CMMCA_RAT_MODE_LTE,
   CMMCA_RAT_MODE_GUL,
   CMMCA_RAT_MODE_BUTT
} ;
typedef VOS_UINT8 CMMCA_RAT_MODE_ENUM_UINT8;


/*****************************************************************************
 枚举名   : CMMCA_RAT_CMD_REJ_REASON_ENUM
 枚举说明 : 拒绝原因值
 1.日    期   : 2014年02月11日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_RAT_CMD_REJ_REASON_ENUM
{
    CMMCA_RAT_CMD_REJ_REASON_NOT_CACHABLE = 0, /* the cmd comes while previous cmd is being handling, LTE can not buffer and handle it.*/
    CMMCA_RAT_CMD_REJ_REASON_WRONG_MODE,       /* LTE can not handle the cmd due to LTE is in improper operation mode. */
    CMMCA_RAT_CMD_REJ_REASON_WRONG_RESUME,     /* LTE can not handle the PS Resume cmd due to LTE has entered improper state.*/
    CMMCA_RAT_CMD_REJ_REASON_WRONG_SUSPEND,    /* LTE can not handle the PS Suspend cmd due to LTE has entered improper  state. */
    CMMCA_RAT_CMD_REJ_REASON_WRONG_PWR_DOWN,   /* LTE can not handle the cmd due to LTE is powering down. */
    CMMCA_RAT_CMD_REJ_REASON_NO_REASON,
    CMMCA_RAT_CMD_REJ_REASON_BUTT
};
typedef VOS_UINT8 CMMCA_RAT_CMD_REJ_REASON_ENUM_UINT8;



/*****************************************************************************
 枚举名   : CMMCA_RAT_POWERUP_RESULT_RSP_ENUM
 枚举说明 : 开机响应原因值定义
 1.日    期   : 2014年02月11日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_RAT_POWERUP_RSP_RESULT_ENUM
{
    CMMCA_RAT_POWERUP_RSP_RESULT_SUCCESS,
    CMMCA_RAT_POWERUP_RSP_RESULT_FAIL,
    CMMCA_RAT_POWERUP_RSP_RESULT_BUTT
};
typedef VOS_UINT8 CMMCA_RAT_POWERUP_RSP_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名   : CMMCA_IRAT_DATA_CONNECT_CMD_REQ_ENUM
 枚举说明 : DataConnectCmd值定义
 1.日    期   : 2014年02月11日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_IRAT_DATA_CONNECT_CMD_REQ_ENUM
{
    CMMCA_IRAT_DATA_CONNECT_CMD_REQ_SUSPEND = 0,
    CMMCA_IRAT_DATA_CONNECT_CMD_REQ_RESUME,
    CMMCA_IRAT_DATA_CONNECT_CMD_REQ_DISABLE,
    CMMCA_IRAT_DATA_CONNECT_CMD_REQ_RELEASE,
    CMMCA_IRAT_DATA_CONNECT_CMD_REQ_BUTT
};
typedef VOS_UINT8 CMMCA_IRAT_DATA_CONNECT_CMD_REQ_ENUM_UINT8;


/*****************************************************************************
 枚举名   : CMMCA_IRAT_DATA_CONNECT_CMD_RSP_ENUM
 枚举说明 : DataConnectCmdRsp值定义
 1.日    期   : 2014年02月11日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_IRAT_DATA_CONNECT_CMD_RSP_ENUM
{
   CMMCA_IRAT_DATA_CONNECT_CMD_RSP_PKT_ACTIVE,
   CMMCA_IRAT_DATA_CONNECT_CMD_RSP_PKT_DORMANT,
   CMMCA_IRAT_DATA_CONNECT_CMD_RSP_PKT_IDLE,
   CMMCA_IRAT_DATA_CONNECT_CMD_RSP_PKT_SUSPENDED,
   CMMCA_IRAT_DATA_CONNECT_CMD_RSP_PKT_DISABLED,
   CMMCA_IRAT_DATA_CONNECT_CMD_RSP_PKT_ON_1XTCH,
   CMMCA_IRAT_DATA_CONNECT_CMD_RSP_RELEASED,
   CMMCA_IRAT_DATA_CONNECT_CMD_RSP_BUTT
};
typedef VOS_UINT8 CMMCA_IRAT_DATA_CONNECT_CMD_RSP_ENUM_UINT8;

/*****************************************************************************
 枚举名   :CMMCA_MMC_NO_SERV_RSP_RESULT_ENUM
 枚举说明 :RAT ID
 1.日    期   : 2014年01月27日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_MMC_NO_SERV_RSP_RESULT_ENUM
{
    CMMCA_MMC_NO_SERV_RSP_SUCC,
    CMMCA_MMC_NO_SERV_RSP_FAIL,
    CMMCA_MMC_NO_SERV_RSP_BUTT
};
typedef VOS_UINT8 CMMCA_MMC_NO_SERV_RSP_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名   :CMMCA_MMC_BEAR_DETACH_RSP_RESULT_ENUM
 枚举说明 : Bearer Detach结果枚举
 1.日    期   : 2014年07月07日
   作    者   : g00261581
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_MMC_BEAR_DETACH_RSP_RESULT_ENUM
{
    CMMCA_MMC_BEAR_DETACH_RSP_FAIL,
    CMMCA_MMC_BEAR_DETACH_RSP_SUCC,

    CMMCA_MMC_BEAR_DETACH_RSP_BUTT
};
typedef VOS_UINT8 CMMCA_MMC_BEAR_DETACH_RSP_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名   :CMMCA_IRAT_SYSTEM_CHG_RESULT_ENUM
 枚举说明 :
 1.日    期   : 2014年02月08日
   作    者   : g00261581
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_IRAT_SYSTEM_CHG_RESULT_ENUM
{
    CMMCA_IRAT_SYSTEM_CHG_SUCCESS,
    CMMCA_IRAT_SYSTEM_CHG_ACQ_FAIL,
    CMMCA_IRAT_SYSTEM_CHG_PS_REG_FAIL,
    CMMCA_IRAT_SYSTEM_CHG_PS_SESSION_FAIL,
    CMMCA_IRAT_SYSTEM_CHG_FAIL,
    CMMCA_IRAT_SYSTEM_CHG_CMD_INVALID,
    CMMCA_IRAT_SYSTEM_CHG_HRPD_SUCCESS,

    CMMCA_IRAT_SYSTEM_CHG_RESULT_BUTT
};

typedef VOS_UINT8  CMMCA_IRAT_SYSTEM_CHG_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名   :CMMCA_RAT_AUTH_MODE_ENUM
 枚举说明 :AUTH MODE
 1.日    期   : 2014年10月24日
   作    者   : j00174725
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_RAT_AUTH_MODE_ENUM
{
    CMMCA_RAT_AUTH_MODE_NONE    = 0,
    CMMCA_RAT_AUTH_MODE_PAP,
    CMMCA_RAT_AUTH_MODE_CHAP,

    CMMCA_RAT_AUTH_MODE_BUTT
};
typedef VOS_UINT8 CMMCA_MMC_RAT_AUTH_MODE_ENUM_UINT8;


#endif

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
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
 结构名    : CMMCA_RAT_MMC_3GPP_RAT_INFO_STRU
 结构说明  : 3GPP_RAT_INFO信息结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEarfcn; /* EUTRAN channel number */
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          ulPlmn;
}CMMCA_RAT_MMC_3GPP_RAT_INFO_STRU;

/*****************************************************************************
 结构名    : CMMCA_RAT_MMC_RAT_SYS_INFO_STRU
 结构说明  : RAT_SYS_INFO信息结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;      /* MMC_GMSS_MCC_UNAVL means MCC Srch Failed */
    VOS_UINT32                          ulMnc;      /* MMC_GMSS_MNC_UNAVL means MNC unavailable */
    CMMCA_RAT_MMC_3GPP_RAT_INFO_STRU    stEutran;
}CMMCA_RAT_MMC_RAT_SYS_INFO_STRU;

/*****************************************************************************
 结构名    : CMMCA_RAT_MMC_RAT_SYS_INFO_RPC_STRU
 结构说明  : RAT SYS INFO RPC信息结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef  struct
{
    CMMCA_RAT_GMSS_PRIORITY_CLASS_ENUM_UINT8                enPriorityClass; /* PLMN priority class */
    VOS_UINT8                                               aucReserved1[3];
    VOS_UINT32                                              ulMcc;
    VOS_UINT32                                              ulMnc;
    VOS_UINT8                                               ucRatInfoValid;
    VOS_UINT8                                               aucReserved2[3];
    CMMCA_RAT_MMC_3GPP_RAT_INFO_STRU                        stEutran;
}CMMCA_RAT_MMC_RAT_SYS_INFO_RPC_STRU;


/*****************************************************************************
 结构名    : CMMCA_PLMNID_RPC_STRU
 结构说明  : PLMNID RPC信息结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMcc;  /* 3 digits */
    VOS_UINT16                          usMnc;  /* 2-3 digits */
}CMMCA_PLMNID_RPC_STRU;

/*****************************************************************************
 结构名    : CMMCA_UTRAN_CELL_GLOBALID_RPC_STRU
 结构说明  : CARRIER INFO CDMA RPC信息结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_PLMNID_RPC_STRU               stPlmnId;
    VOS_UINT32                          ulCellId;   /* 28 bits */
}CMMCA_UTRAN_CELL_GLOBALID_RPC_STRU;


/*****************************************************************************
 结构名    : CMMCA_MMC_CARRIER_INFO_UTRAN_RPC_STRU
 结构说明  : CARRIER INFO CDMA RPC信息结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;        /* UTRAN carrier frequency,(0-16383) */
    CMMCA_UTRAN_CELL_TYPE_ENUM_UINT8    enCellType;     /* FDD=0, TDD=1 */
    VOS_UINT16                          usPhysCellId;   /* FDD(0-511), TDD(0-127) */
    CMMCA_UTRAN_CELL_GLOBALID_RPC_STRU  stCellGlobalId;
    VOS_UINT16                          usLocationAreaCode;
    VOS_UINT8                           ucRoutingAreaCode;
    VOS_UINT8                           bNeedConn;
} CMMCA_MMC_CARRIER_INFO_UTRAN_RPC_STRU;

/*****************************************************************************
 结构名    : CMMCA_GERAN_CELLGLOBALID_RPC_STRU
 结构说明  : 载波信息参数
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef  struct
{
    CMMCA_PLMNID_RPC_STRU               stPlmnId;
    VOS_UINT16                          uslocationAreaCode;    /* 16 bits */
    VOS_UINT16                          uscellId;              /* 16 bits */
}CMMCA_GERAN_CELLGLOBALID_RPC_STRU;


/*****************************************************************************
 结构名    : CMMCA_MMC_CARRIER_INFO_PARAM_RPC_UNION
 结构说明  : 载频信息参数
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;  /* 0-1023 */
    CMMCA_GERAN_BAND_IND_ENUM_UINT8     enBandIndicator;
}CMMCA_GERAN_CARRIER_FREQ_RPC_STRU;


/*****************************************************************************
 结构名    : CMMCA_GERAN_PHYS_CELLID_RPC_STRU
 结构说明  : GERAN PHYS CELLID信息参数
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNwColourCode;   /* 3 bits,network colour code as defined in TS 23.003 */
    VOS_UINT8                           ucBsColourCode;   /* 3 bits, Base station Colour Code as defined in TS 23.003 */
}CMMCA_GERAN_PHYS_CELLID_RPC_STRU;

/*****************************************************************************
 结构名    : CMMCA_GERAN_CGI_INFO_RPC_STRU
 结构说明  : GERAN CGI信息参数
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef  struct
{
    CMMCA_GERAN_CELLGLOBALID_RPC_STRU   stcellGlobalId;
    VOS_UINT8                           ucroutingAreacode;/* The RAC identity read from broadcast information, as defined in TS 23.003 色*/
}CMMCA_GERAN_CGI_INFO_RPC_STRU;

/*****************************************************************************
 结构名    : CMMCA_RAT_MMC_RAT_SYS_INFO_RPC_STRU
 结构说明  : CDMA载波信息结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_CDMA_TYPE_ENUM_UINT8          enType;                      /* Type of the CDMA system, 1xRTT or HRPD */
    VOS_UINT8                           ucBand;                      /* Contains CDMA band information */
    VOS_UINT16                          usChannel;                   /* Contains CDMA channel information */
    VOS_UINT8                           ucNumPn;                     /* Number of CDMA PNs included. It shall be set to 0x00 if "Cause" of the system change is REDIRECTION.Max valid value is 16*/
    VOS_UINT16                          ausPn[CMMCA_MMC_MAX_SIB8_REC_NUM]; /* CDMA pilot PN list. It shall be set to Pn received in IratCdmaPilotMeasResultT of LteMmcAPI_IRAT_SIB8_Meas_Ind
                                                                        for which cell reselection criteria has met. Total number of elements shall not exceed NumPn*/
}CMMCA_MMC_CARRIER_INFO_CDMA_RPC_STRU;

/*****************************************************************************
 结构名    : CMMCA_MMC_CARRIER_INFO_PARAM_RPC_UNION
 结构说明  : GERAN载波信息参数
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_GERAN_CARRIER_FREQ_RPC_STRU   stCarrierInfo;
    CMMCA_GERAN_PHYS_CELLID_RPC_STRU    stPhysCellId;
    CMMCA_GERAN_CGI_INFO_RPC_STRU       stCgiInfo;
}CMMCA_MMC_CARRIER_INFO_GERAN_RPC_STRU;

/*****************************************************************************
 结构名    : CMMCA_MMC_CARRIER_INFO_EUTRAN_RPC_STRU
 结构说明  : EUTRAN载波信息参数
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEarfcn;
    VOS_UINT8                           usNumCell;
    VOS_UINT16                          ausCellId[CMMCA_MMC_MAX_CELL_NUM];
    VOS_UINT8                           ucNumPlmn;
    VOS_UINT32                          aulMcc[CMMCA_MMC_MAX_NUM_EUTRA_PLMN];
    VOS_UINT32                          aulMnc[CMMCA_MMC_MAX_NUM_EUTRA_PLMN];
}CMMCA_MMC_CARRIER_INFO_EUTRAN_RPC_STRU;


/*****************************************************************************
 结构名    : CMMCA_MMC_TARGET_SYSTEM_CARRIER_INFO_RPC_STRU
 结构说明  : TARGET SYSTEM CARRIER INFO结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_RAT_SYSTEM_TYPE_ENUM_UINT8                        enTargetSystemType;    /* Type of the system to which CarrierInfoParam belongs */
    CMMCA_MMC_CARRIER_INFO_EUTRAN_RPC_STRU                  stCarrierInfoEutran;       /* Contains carrier and channel information of EUTRAN system. To be defined in later phase */
}CMMCA_MMC_TARGET_SYSTEM_CARRIER_INFO_RPC_STRU;

/*****************************************************************************
 结构名    : CMMCA_MMC_SYSTEM_CHANGE_REQ_RPC_STRU
 结构说明  : SYSTEM_CHANGE_REQ结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_IRAT_HO_CAUSE_ENUM_UINT8                          enCause;                             /* Cause of the system change request from LTE to other RAT */
    CMMCA_MMC_TARGET_SYSTEM_CARRIER_INFO_RPC_STRU           stTargetSystemCarrierInfo; /* Contains target system type and frequency information to which system change is requested */
}CMMCA_MMC_SYSTEM_CHANGE_REQ_RPC_STRU;

/*****************************************************************************
 结构名    : CMMCA_MMC_RAT_SYS_INFO_RPC_STRU
 结构说明  : RAT系统信息结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef  struct
{
    VOS_UINT16                                              usEarfcn;                    /* channel number */
    CMMCA_RAT_GMSS_PRIORITY_CLASS_ENUM_UINT8                enPriorityClass;             /* PLMN priority class */
    VOS_UINT32                                              ulPlmnId;                    /* PLMN identity to which E-UTRAN cell belongs */
}CMMCA_MMC_RAT_SYS_INFO_RPC_STRU;


/*****************************************************************************
 结构名    : CMMCA_RAT_MMC_CELL_INFO_PS_REG_RSP_STRU
 结构说明  : RAT_CELLINFO_PS_REG_RSP_RPC结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
 2.日    期   : 2015年4月22日
   作    者   : wx270776
   修改内容   : DTS2015031602665: 增加cl attach注册状态
*****************************************************************************/
typedef  struct
{
    CMMCA_RAT_MMC_STATUS_ENUM_UINT8                          enResult; /* Status of registration response. Rest of the fields are valid only in case Result is set to IRAT_SUCCESS */
    CMMCA_RAT_ATTACH_CL_REG_STATUS_ENUM8                     enLmAttachRegStatus;
    CMMCA_RAT_SYSTEM_TYPE_ENUM_UINT8                         enTargetSystemType;
    VOS_UINT8                                                aucReserved[1];
    CMMCA_RAT_MMC_RAT_SYS_INFO_RPC_STRU                      stRatSysInfo;
}CMMCA_MMC_RAT_CELLINFO_PS_REG_RSP_RPC_STRU;

/*****************************************************************************
 结构名    : CMMCA_MMC_RAT_MODE_REQ_STRU
 结构说明  : ID_CMMCA_MMC_RAT_RAT_MODE_REQ的消息结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId;
    CMMCA_RAT_MODE_ENUM_UINT8           enMode;
    VOS_UINT8                           aucReserved[2];
}CMMCA_MMC_RAT_MODE_REQ_STRU;

/*****************************************************************************
 结构名    : CMMCA_RAT_MMC_RAT_MODE_RSP_STRU
 结构说明  : ID_CMMCA_RAT_MMC_RAT_MODE_RSP的消息结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_ID_ENUM_UINT8                             enRatId;
    CMMCA_MMC_MODE_RSP_RESULT_ENUM_UINT8                    enResult;   /*  0 - success others - fail */
    VOS_UINT8                                               aucReserved[2];
}CMMCA_RAT_MMC_RAT_MODE_RSP_STRU;


/*****************************************************************************
 结构名    : CMMCA_MMC_RAT_POWERUP_REQ_STRU
 结构说明  : ID_CMMCA_MMC_RAT_POWERUP_REQ的消息结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId;
    VOS_UINT8                           aucReserved[3];
}CMMCA_MMC_RAT_POWERUP_REQ_STRU;

/*****************************************************************************
 结构名    : CMMCA_RAT_MMC_POWERUP_RSP_STRU
 结构说明  : ID_CMMCA_RAT_MMC_POWERUP_RSP的消息结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_ID_ENUM_UINT8                             enRatId;
    CMMCA_RAT_POWERUP_RSP_RESULT_ENUM_UINT8                 enResult;
    VOS_UINT8                                               aucReserved[2];
}CMMCA_RAT_MMC_POWERUP_RSP_STRU;

/*****************************************************************************
 结构名    : CMMCA_MMC_RAT_POWERDOWN_REQ_STRU
 结构说明  : ID_CMMCA_MMC_RAT_POWERDOWN_REQ的消息结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId;
    VOS_UINT8                           aucReserved[3];
}CMMCA_MMC_RAT_POWERDOWN_REQ_STRU;

/*****************************************************************************
 结构名    : CMMCA_RAT_MMC_POWERDOWN_RSP_STRU
 结构说明  : ID_CMMCA_RAT_MMC_POWERDOWN_RSP的消息结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId;
    VOS_UINT8                           aucReserved[3];
}CMMCA_RAT_MMC_POWERDOWN_RSP_STRU;

/*****************************************************************************
 结构名    : CMMCA_MMC_RAT_ACQ_REQ_STRU
 结构说明  : ID_CMMCA_MMC_RAT_ACQ_REQ的消息结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId;
    CMMCA_RAT_ACQ_REQ_REASON_ENUM_UINT8 enCause;
    VOS_UINT8                           aucReserved[2];
}CMMCA_MMC_RAT_ACQ_REQ_STRU;

/*****************************************************************************
 结构名    : MMCA_RAT_MMC_ACQ_RSP_STRU
 结构说明  : ID_CMMCA_RAT_MMC_ACQ_RSP的消息结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId;
    CMMCA_RAT_ACQ_RESULT_ENUM_UINT8     enResult;
    VOS_UINT8                           aucReserved[2];
    CMMCA_RAT_MMC_RAT_SYS_INFO_RPC_STRU stRatSysInfo;
}CMMCA_RAT_MMC_ACQ_RSP_STRU;

/*****************************************************************************
 结构名    : CMMCA_MMC_RAT_MCC_SEARCH_REQ_STRU
 结构说明  : ID_CMMCA_MMC_RAT_MCC_SEARCH_REQ的消息结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId;
    VOS_UINT8                           aucReserved[3];
}CMMCA_MMC_RAT_MCC_SEARCH_REQ_STRU;

/*****************************************************************************
 结构名    : CMMCA_RAT_MMC_MCC_SEARCH_RSP_STRU
 结构说明  : ID_CMMCA_RAT_MMC_MCC_SEARCH_RSP的消息结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId;
    VOS_UINT8                           aucReserved1[3];
    VOS_UINT32                          ulMcc;      /* MMC_GMSS_MCC_UNAVL means MCC Srch Failed */
    VOS_UINT32                          ulMnc;      /* MMC_GMSS_MNC_UNAVL means MNC unavailable */
    VOS_UINT8                           ucRatInfoValid;
    VOS_UINT8                           aucReserved2[3];
    CMMCA_RAT_MMC_3GPP_RAT_INFO_STRU    stEutran;

}CMMCA_RAT_MMC_MCC_SEARCH_RSP_STRU;

/*****************************************************************************
 结构名    : CMMCA_MMC_RAT_PS_REG_REQ_STRU
 结构说明  : ID_CMMCA_MMC_RAT_PS_REG_REQ的消息结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_ID_ENUM_UINT8                             enRatId;
    CMMCA_RAT_GMSS_PRIORITY_CLASS_ENUM_UINT8                enPriorityClass; /* PLMN priority class */
    CMMCA_RAT_ATTACH_TYPE_ENUM_UINT8                        ucAttachType;
    VOS_UINT8                                               aucReserved[1];
}CMMCA_MMC_RAT_PS_REG_REQ_STRU;

/*****************************************************************************
 结构名    : CMMCA_RAT_MMC_PS_REG_RSP_STRU
 结构说明  : ID_CMMCA_RAT_MMC_PS_REG_RSP的消息结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
 2.日    期   : 2015年4月22日
   作    者   : wx270776
   修改内容   : DTS2015031602665: 增加cl attach注册状态
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_ID_ENUM_UINT8                             enRatId;
    CMMCA_RAT_REG_RESULT_ENUM_UINT8                         enResult;
    CMMCA_RAT_ATTACH_CL_REG_STATUS_ENUM8                    enLmmAttachRegStatus;
    VOS_UINT8                                               aucReserved[1];
    CMMCA_RAT_MMC_RAT_SYS_INFO_RPC_STRU                     stRatSysInfo;
}CMMCA_RAT_MMC_PS_REG_RSP_STRU;

/*****************************************************************************
 结构名    : CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ_STRU
 结构说明  : ID_CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ的消息结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_ID_ENUM_UINT8                             enRatId;
    VOS_UINT8                                               aucReserved[3];
    CMMCA_MMC_SYSTEM_CHANGE_REQ_RPC_STRU                    stSystemChangeReq;
}CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ_STRU;


/*****************************************************************************
 结构名    : CMMCA_RAT_MMC_CELL_INFO_PS_REG_RSP_STRU
 结构说明  : ID_CMMCA_RAT_MMC_CELL_INFO_PS_REG_RSP的消息结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_ID_ENUM_UINT8                             enRatId;
    VOS_UINT8                                               aucReserved[3];
    CMMCA_MMC_RAT_CELLINFO_PS_REG_RSP_RPC_STRU              stIratRegRsp;
}CMMCA_RAT_MMC_CELL_INFO_PS_REG_RSP_STRU;


/*****************************************************************************
 结构名    : CMMCA_MMC_RAT_NO_SERVICE_REQ_STRU
 结构说明  : ID_CMMCA_MMC_RAT_NO_SERVICE_REQ的消息结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_ID_ENUM_UINT8                             enRatId;
    CMMCA_MMC_RAT_NOSVC_CAUSE_ENUM_UINT8                    enCause;
    VOS_UINT8                                               aucReserved[2];
}CMMCA_MMC_RAT_NO_SERVICE_REQ_STRU;

/*****************************************************************************
 结构名    : CMMCA_RAT_MMC_NO_SERVICE_RSP_STRU
 结构说明  : ID_CMMCA_RAT_MMC_NO_SERVICE_RSP的消息结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId;
    VOS_UINT8                           ucStatus;
    VOS_UINT8                           aucReserved[2];
}CMMCA_RAT_MMC_NO_SERVICE_RSP_STRU;

/*****************************************************************************
 结构名    : CMMCA_RAT_MMC_NTW_ST_CHG_IND_STRU
 结构说明  : ID_CMMCA_RAT_MMC_NTW_ST_CHG_IND的消息结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_ID_ENUM_UINT8                             enRatId;
    CMMCA_RAT_CPST_ENUM_UINT8                               enStatus;
    CMMCA_RAT_NOTIFY_CAUSE_ENUM_UINT8                       enCause;
    CMMCA_RAT_GMSS_PRIORITY_CLASS_ENUM_UINT8                enSysPri;
    CMMCA_RAT_PS_TYPE_ENUM_UINT8                            enPsType;
    VOS_UINT8                                               aucReserved[3];
    VOS_UINT32                                              ulMcc;
    VOS_UINT32                                              ulMnc;
    CMMCA_RAT_MMC_3GPP_RAT_INFO_STRU                        stEutran;
}CMMCA_RAT_MMC_NTW_ST_CHG_IND_STRU;


/*****************************************************************************
 结构名    : CMMCA_MMC_SYSTEM_CHANGE_REQ_STRU
 结构说明  : CMD REJ IND结构
   1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enSourceRat;
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    enApiID;
    CMMCA_RAT_CMD_REJ_REASON_ENUM_UINT8 enCause;
}CMMCA_MMC_CMD_REJ_IND_STRU;


/*****************************************************************************
 结构名    : CMMCA_MMC_RAT_PKT_DATA_CMD_REQ_STRU
 结构说明  : PKT DATA CMD REQ结构
   1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
   CMMCA_MMC_RAT_ID_ENUM_UINT8                                 enRatId;
   CMMCA_IRAT_DATA_CONNECT_CMD_REQ_ENUM_UINT8                  enCmd;
   VOS_UINT8                                                   aucReserved[2];
}CMMCA_MMC_RAT_PKT_DATA_CMD_REQ_STRU;

/*****************************************************************************
 结构名    : CMMCA_RAT_MMC_PKT_DATA_CMD_RSP_STRU
 结构说明  : PKT DATA CMD RSP结构
   1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_ID_ENUM_UINT8                             enRatId;
    CMMCA_IRAT_DATA_CONNECT_CMD_RSP_ENUM_UINT8              enCmdRsp;
    VOS_UINT8                                               aucReserved[2];
}CMMCA_RAT_MMC_PKT_DATA_CMD_RSP_STRU;

/*****************************************************************************
 结构名    : CMMCA_PDN_INFO_STRU
 结构说明  : PDN信息
 1.日    期   : 2014年01月08日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPdnId;
    CMMCA_IP_TYPE_ENUM_UINT8            enPdnType;
    VOS_UINT8                           ucApnLen;
    VOS_UINT8                           aucApn[CMMCA_APN_LEN_MAX];
    VOS_UINT8                           aucReserved[2];
}CMMCA_PDN_INFO_STRU;

/*****************************************************************************
 结构名    : CMMCA_MMC_RAT_SET_PDN_TAB_REQ_STRU
 结构说明  : ID_CMMCA_MMC_RAT_PDN_TABLE_SETUP_REQ的消息结构
 1.日    期   : 2014年01月10日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTotalNum;
    CMMCA_PDN_INFO_STRU                 astPdnInfo[CMMCA_SUPPORTED_PDN_NUM_MAX];
}CMMCA_MMC_RAT_SET_PDN_TAB_REQ_STRU;

/*****************************************************************************
 结构名    : CMMCA_RAT_MMC_SET_PDN_TAB_CNF_STRU
 结构说明  : ID_CMMCA_RAT_MMC_PDN_TABLE_SETUP_RSP的消息结构
 1.日    期   : 2014年01月10日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_RAT_MMC_PDN_TAB_SET_RESULT_ENUM_UINT8     enRslt;
    VOS_UINT8                                       aucReserved[3];
}CMMCA_RAT_MMC_SET_PDN_TAB_CNF_STRU;

/*****************************************************************************
 结构名    : CMMCA_MMC_RAT_DEFAULT_BEAR_CONN_REQ_STRU
 结构说明  : ID_CMMCA_MMC_RAT_DEFAULTBEARER_REQ的消息结构
 1.日    期   : 2014年01月10日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPdnId;
    CMMCA_IP_TYPE_ENUM_UINT8            enPdnType;
    CMMCA_PDN_REQUEST_TYPE_ENUM_UINT8   enRequestType;
    VOS_UINT8                           ucPdpFlag;                              /*0 = P-CSCF address is not required 1 = P-CSCF address is required*/
    VOS_UINT8                           ucApnLen;
    VOS_UINT8                           aucApn[CMMCA_APN_LEN_MAX];
    VOS_UINT8                           aucIpv6Addr[CMMCA_IPV6_ADDR_LEN];
    VOS_UINT8                           aucIpv4Addr[CMMCA_IPV4_ADDR_LEN];
    VOS_UINT8                           aucIpv4DefRouterAddr[CMMCA_IPV4_ADDR_LEN];
}CMMCA_MMC_RAT_DEFAULT_BEAR_CONN_REQ_STRU;

/*****************************************************************************
 结构名    : CMMCA_RAT_MMC_DEFAULT_BEAR_CONN_CNF_STRU
 结构说明  : ID_CMMCA_RAT_MMC_DEFAULTBEARER_RSP的消息结构
 1.日    期   : 2014年01月10日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                    ucPdnId;
    VOS_UINT8                                    ucBearerId;                    /* 0xf0|RabId */
    CMMCA_RAT_MMC_BEAR_CONN_RESULT_ENUM_UINT8    enRslt;
    CMMCA_IP_TYPE_ENUM_UINT8                     enPdnType;
    VOS_UINT8                                    aucIpv6Addr[CMMCA_IPV6_ADDR_LEN];
    VOS_UINT8                                    aucIpv4Addr[CMMCA_IPV4_ADDR_LEN];

    VOS_UINT8                                    ucPcscf6Num;
    VOS_UINT8                                    ucDns6Num;
    VOS_UINT8                                    ucPcscf4Num;
    VOS_UINT8                                    ucDns4Num;

    VOS_UINT8                                    aucPcscf6Addr[CMMCA_SUPPORTED_ADDR_NUM_MAX][CMMCA_IPV6_ADDR_LEN];
    VOS_UINT8                                    aucDns6Addr[CMMCA_SUPPORTED_ADDR_NUM_MAX][CMMCA_IPV6_ADDR_LEN];
    VOS_UINT8                                    aucPcscf4Addr[CMMCA_SUPPORTED_ADDR_NUM_MAX][CMMCA_IPV4_ADDR_LEN];
    VOS_UINT8                                    aucDns4Addr[CMMCA_SUPPORTED_ADDR_NUM_MAX][CMMCA_IPV4_ADDR_LEN];

    VOS_UINT8                                    aucRouteAddr[CMMCA_IPV4_ADDR_LEN];
    VOS_UINT8                                    aucIp6InterfaceId[CMMCA_IPV6_INTERFACE_ID_BYTE_LEN];
    CMMCA_PDN_SEL_BEARER_CTRL_MODE_ENUM_UINT8    enSelBearerCtrlMode;
    CMMCA_RAT_MMC_PKT_ERRCODE_UINT8              enErrCode;
    VOS_UINT8                                    aucReserved[2];
}CMMCA_RAT_MMC_DEFAULT_BEAR_CONN_CNF_STRU;

/*****************************************************************************
 结构名    : CMMCA_MMC_RAT_BEAR_DISC_REQ_STRU
 结构说明  : ID_CMMCA_MMC_RAT_BEARER_DISCONNECT_REQ的消息结构
 1.日    期   : 2014年01月10日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           ucBearerId;                             /* 0xf0|RabId */
    VOS_UINT8                           ucIsDefaultBearer;                      /* TRUE = Default, FALSE = Dedicated */
    VOS_UINT8                           aucReserved[1];
}CMMCA_MMC_RAT_BEAR_DISC_REQ_STRU;

/*****************************************************************************
 结构名    : CMMCA_RAT_MMC_BEAR_DISC_CNF_STRU
 结构说明  : ID_CMMCA_RAT_MMC_BEARER_DISCONNECT_RSP的消息结构
 1.日    期   : 2014年01月10日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           ucBearerId;                             /* 0xf0|RabId */
    CMMCA_RAT_MMC_RESULT_ENUM_UINT8     enRslt;
    VOS_UINT8                           aucReserved[1];
}CMMCA_RAT_MMC_BEAR_DISC_CNF_STRU;

/*****************************************************************************
 结构名    : CMMCA_RAT_MMC_BEAR_DISC_IND_STRU
 结构说明  : ID_CMMCA_RAT_MMC_BEARER_DISCONNECT_IND的消息结构
 1.日    期   : 2014年01月10日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           ucBearerId;                             /* 0xf0|RabId */
    VOS_UINT8                           aucReserved1[2];
}CMMCA_RAT_MMC_BEAR_DISC_IND_STRU;

/*****************************************************************************
 结构名    : CMMCA_MMC_RAT_BEAR_DETACH_REQ_STRU
 结构说明  : ID_CMMCA_MMC_RAT_BEARER_DETACH_REQ的消息结构
 1.日    期   : 2014年07月07日
   作    者   : g00261581
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId;
    VOS_UINT8                           aucReserved[3];
}CMMCA_MMC_RAT_BEAR_DETACH_REQ_STRU;

/*****************************************************************************
 结构名    : CMMCA_RAT_MMC_BEAR_DETACH_RSP_STRU
 结构说明  : ID_CMMCA_RAT_MMC_BEARER_DETACH_RSP的消息结构
 1.日    期   : 2014年07月07日
   作    者   : g00261581
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId;
    VOS_UINT8                           ucStatus;
    VOS_UINT8                           aucReserved[2];
}CMMCA_RAT_MMC_BEAR_DETACH_RSP_STRU;

/*****************************************************************************
 结构名    : CMMCA_MMC_RAT_IRAT_SYSTEM_CHG_RSP_STRU
 结构说明  : ID_CMMCA_MMC_RAT_IRAT_SYSTEM_CHG_RSP的消息结构
 1.日    期   : 2014年02月08日
   作    者   : g00261581
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_IRAT_SYSTEM_CHG_RESULT_ENUM_UINT8       enResult;
}CMMCA_MMC_RAT_IRAT_SYSTEM_CHG_RSP_STRU;

#endif

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_UINT16 CMMCA_ConvertDoubleOctetStrToU16(VOS_UINT8 *pucStr);
VOS_UINT32 CMMCA_ConvertFourOctetStrToU32(VOS_UINT8 *pucStr);
VOS_VOID CMMCA_ConvertU16ToDoubleOctetStr(
    VOS_UINT16                          usResult,
    VOS_UINT8                          *pucStr
);
VOS_VOID CMMCA_ConvertU32ToFourOctetStr(
    VOS_UINT32                          ulResult,
    VOS_UINT8                          *pucStr
);

VOS_VOID CMMCA_ConvertNasMccToTwoBcdMccOctetStr(
    VOS_UINT32                          ulNasMcc,
    VOS_UINT8                          *pucMccStr
);

VOS_VOID CMMCA_ConvertNasMncToTwoBcdMncOctetStr(
    VOS_UINT32                          ulNasMnc,
    VOS_UINT8                          *pucMncStr
);

VOS_VOID CMMCA_ConvertNasPlmnToBcdPlmnOctetStr(
    VOS_UINT32                          ulNasMcc,
    VOS_UINT32                          ulNasMnc,
    VOS_UINT8                          *pucPlmnStr
);

VOS_VOID CMMCA_ConvertTwoBcdMccOctetStrToNasMcc(
    VOS_UINT8                          *pucMccStr,
    VOS_UINT32                         *pulNasMcc

);

VOS_VOID CMMCA_ConvertTwoBcdMncOctetStrToNasMnc(
    VOS_UINT8                          *pucMncStr,
    VOS_UINT32                         *pulNasMnc

);

VOS_VOID CMMCA_ConvertFourBcdMccMncOctetStrToNasPlmn(
    VOS_UINT8                          *pucPlmnStr,
    VOS_UINT32                         *pulNasMcc,
    VOS_UINT32                         *pulNasMnc
);

#if (FEATURE_ON == FEATURE_CL_INTERWORK)

VOS_UINT32 CMMCA_ParseModeReq(
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk,
    CMMCA_MMC_RAT_MODE_REQ_STRU        *pstModeReq
);

VOS_UINT32 CMMCA_PackModeRsp(
    CMMCA_RAT_MMC_RAT_MODE_RSP_STRU    *pstModeRsp,
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk
);

VOS_UINT32 CMMCA_ParsePowerUpReq(
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk,
    CMMCA_MMC_RAT_POWERUP_REQ_STRU     *pstPowerUpReq
);

VOS_UINT32 CMMCA_PackPowerUpRsp(
    CMMCA_RAT_MMC_POWERUP_RSP_STRU     *pstPowerUpRsp,
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk
);

VOS_UINT32 CMMCA_ParsePowerDownReq(
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk,
    CMMCA_MMC_RAT_POWERDOWN_REQ_STRU   *pstPowerDownReq
);

VOS_UINT32 CMMCA_PackPowerDownRsp(
    CMMCA_RAT_MMC_POWERDOWN_RSP_STRU   *pstPowerDownRsp,
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk
);

VOS_UINT32 CMMCA_ParseAcqReq(
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk,
    CMMCA_MMC_RAT_ACQ_REQ_STRU         *pstAcqReq
);

VOS_UINT32 CMMCA_PackAcqRsp(
    CMMCA_RAT_MMC_ACQ_RSP_STRU         *pstAcqRsp,
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk
);

VOS_UINT32 CMMCA_ParseNoServiceReq(
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk,
    CMMCA_MMC_RAT_NO_SERVICE_REQ_STRU  *pstNoServReq
);

VOS_UINT32 CMMCA_PackNoServiceRsp(
    CMMCA_RAT_MMC_NO_SERVICE_RSP_STRU  *pstNoServRsp,
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk
);

VOS_UINT32 CMMCA_PackMccSearchRsp(
    CMMCA_RAT_MMC_MCC_SEARCH_RSP_STRU  *pstMccSearchRsp,
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk
);

VOS_UINT32 CMMCA_ParsePsRegReq(
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk,
    CMMCA_MMC_RAT_PS_REG_REQ_STRU      *pstPsRegReq
);

VOS_UINT32 CMMCA_PackPsRegRsp(
    CMMCA_RAT_MMC_PS_REG_RSP_STRU      *pstPsRegRsp,
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk
);

VOS_UINT32 CMMCA_ParseCellInfoPsRegReq(
    VOS_UINT16                                              usParamBlklength,
    VOS_UINT8                                              *pucParamBlk,
    CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ_STRU                *pstCellInfoPsRegReq
);

VOS_UINT32 CMMCA_PackCellInfoPsRegRsp(
    CMMCA_RAT_MMC_CELL_INFO_PS_REG_RSP_STRU                *pstCellInfoPsRegRsp,
    VOS_UINT16                                              usParamBlklength,
    VOS_UINT8                                              *pucParamBlk
);

VOS_UINT32 CMMCA_PackNtwStateChangeInd(
    CMMCA_RAT_MMC_NTW_ST_CHG_IND_STRU  *pstNtwStChgInd,
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk
);

VOS_UINT32 CMMCA_PackCmdRejInd(
    CMMCA_MMC_CMD_REJ_IND_STRU         *pstCmdRejInd,
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk
);

VOS_UINT32 CMMCA_PackPktDataCmdRsp(
    CMMCA_RAT_MMC_PKT_DATA_CMD_RSP_STRU                    *pstDataCmdRsp,
    VOS_UINT16                                              usParamBlklength,
    VOS_UINT8                                              *pucParamBlk
);

VOS_UINT32 CMMCA_ParseSetPdnTabReq(
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk,
    CMMCA_MMC_RAT_SET_PDN_TAB_REQ_STRU *pstSetPdnTabReq
);

VOS_UINT32 CMMCA_PackSetPdnTabRsp(
    CMMCA_RAT_MMC_SET_PDN_TAB_CNF_STRU *pstSetPdnTabCnf,
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk
);

VOS_UINT32 CMMCA_ParseDefaultBearConnReq(
    VOS_UINT16                                              usParamBlklength,
    VOS_UINT8                                              *pucParamBlk,
    CMMCA_MMC_RAT_DEFAULT_BEAR_CONN_REQ_STRU               *pstDefaultBearConnReq
);

VOS_UINT32 CMMCA_PackDefaultBearConnRsp(
    CMMCA_RAT_MMC_DEFAULT_BEAR_CONN_CNF_STRU               *pstDefaultBearConnCnf,
    VOS_UINT16                                              usParamBlklength,
    VOS_UINT8                                              *pucParamBlk
);

VOS_UINT32 CMMCA_ParseBearDiscReq(
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk,
    CMMCA_MMC_RAT_BEAR_DISC_REQ_STRU   *pstBearDiscReq
);

VOS_UINT32 CMMCA_PackBearDiscRsp(
    CMMCA_RAT_MMC_BEAR_DISC_CNF_STRU   *pstBearDiscCnf,
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk
);

VOS_UINT32 CMMCA_PackBearDiscInd(
    CMMCA_RAT_MMC_BEAR_DISC_IND_STRU   *pstBearDiscInd,
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk
);

VOS_UINT32 CMMCA_ParseSystemChangeRsp(
    VOS_UINT16                                              usParamBlklength,
    VOS_UINT8                                              *pucParamBlk,
    CMMCA_MMC_RAT_IRAT_SYSTEM_CHG_RSP_STRU                 *pstSystemChgInd
);

VOS_UINT32 CMMCA_ParseOtherRatInfoInd(
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk,
    CMMCA_OTHER_RAT_INFO_IND_STRU      *pstOtherRatInfoInd
);

VOS_UINT32 CMMCA_ParseBearDetachReq(
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk,
    CMMCA_MMC_RAT_BEAR_DETACH_REQ_STRU *pstBearDetachReq
);

VOS_UINT32 CMMCA_PackBearDetachRsp(
    CMMCA_RAT_MMC_BEAR_DETACH_RSP_STRU *pstBearDetachRsp,
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk
);
VOS_UINT32 CMMCA_PackSetPdnPcoAuthRsp(
    CMMCA_SET_PDN_PCO_AUTH_RESULT_ENUM_UINT8        enRslt,
    VOS_UINT16                                      usParamBlklength,
    VOS_UINT8                                      *pucParamBlk
);

VOS_UINT32 CMMCA_ConvertCdmaSetPdnPcoAuthModeToTaf(
    CMMCA_MMC_RAT_AUTH_MODE_ENUM_UINT8  enAuthMode,
    TAF_PDP_AUTH_TYPE_ENUM_UINT8       *penTafMode
);

VOS_UINT32 CMMCA_ParseSetPdnPcoAuthReq(
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk,
    TAF_AUTHDATA_EXT_STRU              *pstTafAuthDataExt
);

VOS_UINT32 CMMCA_ConvertCdmaCardStatus(
    TAF_MTC_CDMA_USIMM_CARD_ENUM_UINT8      enCardStatus,
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16  *penDestCardStatus
);

VOS_UINT32 CMMCA_ParseStateInfo(
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk,
    TAF_MTC_CDMA_STATE_INFO_STRU       *pstMtcCdmaState
);

VOS_UINT32 CMMCA_ParseMeasurementInfo(
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk,
    CMMCA_RCM_MEASUREMENT_INFO_STRU    *pstMeasure
);

VOS_UINT32 CMMCA_ParseEventInfo(
    VOS_UINT16                          usParamBlklength,
    VOS_UINT8                          *pucParamBlk,
    CDMA_TAS_EVENT_INFO_STRU           *pstEvent
);



#endif

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

#endif /* end of CmmcaPktMgmt.h */
