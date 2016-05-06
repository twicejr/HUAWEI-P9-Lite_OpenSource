/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEsmNwMsgDecode.h
    Description :
    History     :
     1.丁丽 00128736      2008-09-01  Draft Enact
     2.杨茜惠 00135146    2008-12-24  BA8D00792
     3.孙兵 49683         2009-01-06  BA8D00870
     4.杨茜惠 00135146    2009-03-06  Modify  BA8D01127
     5.李洪00150010       2009-08-03  Modify  BJ9D01608
     6.李洪00150010       2009-08-05  Modify  BJ9D01627
******************************************************************************/

#ifndef _NASESMNWMSGDECODE_H
#define _NASESMNWMSGDECODE_H

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include    "vos.h"
#include    "NasEsmPublic.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
/*****************************************************************************
      信息IEI
*****************************************************************************/


#define NAS_ESM_TFT_CREATE_TFT           (0x20)              /* 0010 0000*/
#define NAS_ESM_TFT_DELETE_TFT           (0x40)              /* 0100 0000*/
#define NAS_ESM_TFT_REPLACE_FILTER       (0x80)              /* 1000 0000*/
#define NAS_ESM_TFT_ADD_FILTER           (0x60)              /* 0110 0000*/
#define NAS_ESM_TFT_DELETE_FILTER        (0xA0)              /* 1010 0000*/
#define NAS_ESM_TFT_NO_OPERATION         (0xD0)              /* 1101 0000*/

#define NAS_ESM_TFT_PARA_LIST_ID         (0x03)
#define NAS_ESM_TAD_PFNUM_OFFSET         (0x00)
#define NAS_ESM_PACKET_FILTER_ID_OFFSET  (0x01)
#define NAS_ESM_PACKET_FILTER_LEN_OFFSET (0x03)
#define NAS_ESM_TFT_LOW_4_BIT_MASK       (0x0F)
#define NAS_ESM_TFT_HIGH_4_BIT_MASK      (0xF0)


#define NAS_ESM_PARAMETER_ID_OFFSET      (0x01)
#define NAS_ESM_PARAMETER_LEN_OFFSET     (0x02)


#define NAS_ESM_TFT_DIR_DL               (0x01)              /* 0000 0001*/
#define NAS_ESM_TFT_DIR_UL               (0x02)              /* 0000 0010*/
#define NAS_ESM_TFT_DIR_BI               (0x03)              /* 0000 0011*/
#define NAS_ESM_TFT_ONE_FILTER           (0x01)

/* 删掉此处的TFT PF COMPONENT TYPE的宏定义，改定义下面的枚举 */

#define NAS_ESM_PDN_IPV4                 (0x01)              /* 支持IPV4地址*/
#define NAS_ESM_PDN_IPV6                 (0x02)              /* 支持IPV6地址*/
#define NAS_ESM_PDN_IPV4_IPV6            (0x03)              /* 支持IPV4和IPV6地址*/
#define NAS_ESM_IP_ADDR_LEN_IPV4         (4)                 /* IPV4和IPV6地址*/

#define NAS_ESM_IP_ADDR_LEN_IPV6         (16)

#define NAS_ESM_IPCP_DNS_OPT             (1)

#define NAS_ESM_IPV6_IF_OFFSET           (8)
#define NAS_ESM_IPV6_IF_LEN              (8)

#define NAS_ESM_MSG_PD                   (0x02)              /*ESM 消息的PD(低4位)为0010*/
#define NAS_ESM_MAX_PCO_BYTE             (253)

#define NAS_ESM_MAX_APN_BYTE             (102)
#define NAS_ESM_MAX_EPS_QOS_BYTE         (15)               /* 扩展后，Qos的最大长度为15*/
#define NAS_ESM_QOS_LEN_ONLY_QCI         (1)                /* Qos 的长度可以取4，7，11 ,15*/
#define NAS_ESM_QOS_LEN_NO_EXT           (5)
#define NAS_ESM_QOS_LEN_ALL_QOS          (9)
#define NAS_ESM_QOS_LEN_ALL_WITH_EXT2    (13)

#define NAS_ESM_PDP_QOS_LEN_NO_EXTEND    (14)                /* PDP Qos 的长度可以取14，16，18 */
#define NAS_ESM_PDP_QOS_LEN_NO_UP_EXTEND (16)
#define NAS_ESM_PDP_QOS_LEN_ALL_QOS      (18)

#define NAS_ESM_PDP_QOS_DELAY_CLASS                         (0x38)    /* 0011 1000*/
#define NAS_ESM_PDP_QOS_RELIABILITY_CLASS                   (0x07)    /* 0000 0111*/
#define NAS_ESM_PDP_QOS_PEAK_THROUGHPUT                     (0xF0)    /* 1111 0000*/
#define NAS_ESM_PDP_QOS_PRECEDENCE_CLASS                    (0x07)    /* 0000 0111*/
#define NAS_ESM_PDP_QOS_MEAN_THROUGHPUT                     (0x1F)    /* 0001 1111*/
#define NAS_ESM_PDP_QOS_TRAFFIC_CLASS                       (0xE0)    /* 1110 0000*/
#define NAS_ESM_PDP_QOS_DELIVERY_ORDER                      (0x18)    /* 0001 1000*/
#define NAS_ESM_PDP_QOS_DELIVERY_ERRORNEOUS_SDU             (0x07)    /* 0000 0111*/
#define NAS_ESM_PDP_QOS_RESIDUAL_BER                        (0xF0)    /* 1111 0000*/
#define NAS_ESM_PDP_QOS_SDU_ERROR_RATIO                     (0x0F)    /* 0000 1111*/
#define NAS_ESM_PDP_QOS_TRANSFER_DELAY                      (0Xfc)    /* 1111 1100*/
#define NAS_ESM_PDP_QOS_TRAFFIC_HANDLING_PRIORITY           (0x03)    /* 0000 0011*/
#define NAS_ESM_PDP_QOS_SSD                                 (0x0F)    /* 0000 1111*/
#define NAS_ESM_PDP_QOS_SIGNALLING_INDICATION               (0x10)    /* 0001 0000*/

#define NAS_ESM_MAX_TFT_BYTE             (255)
#define NAS_ESM_MAX_APN_AMBR_BYTE        (8)

#define NAS_ESM_MIN_APN_AMBR_BYTE        (4)
#define NAS_ESM_MIN_APN_BYTE             (3)
#define NAS_ESM_MIN_EPS_QOS_BYTE         (3)
#define NAS_ESM_MIN_PDN_BYTE             (7)
#define NAS_ESM_MIN_TFT_BYTE             (3)
#define NAS_ESM_MIN_PCO_BYTE             (3)

#define NAS_ESM_IPCP_PACKET_HEAD_LEN     (4)
#define NAS_ESM_IPCP_OPTION_DNS_LEN      (6)
#define NAS_ESM_IPCP_OPTION_HEAD_LEN     (2)

#define NAS_ESM_EPS_QOS_NULL_RATE        (0x0)
#define NAS_ESM_EPS_QOS_NULL_RATE2       (0xFF)

#define NAS_ESM_APN_AMBR_NULL_RATE       (0x0)
#define NAS_ESM_APN_AMBR_NULL_RATE2      (0xFF)
#define NAS_ESM_APN_AMBR_LEN_NO_EXT      (2)                /* APN-AMBR 的长度可以取2，4，6 */
#define NAS_ESM_APN_AMBR_LEN_EXT1        (4)
#define NAS_ESM_APN_AMBR_LEN_EXT2        (6)


#define NAS_ESM_EPS_QOS_RATE_EXT         (0xFE)

#define NAS_ESM_SIGN_BIT                 (0x80)

#define NAS_ESM_HIGH_3_BITS_F            (0x70)
#define NAS_ESM_MSG_LINK_EPSBID_IEI     (0x00)

#define NAS_ESM_MSG_PDN_IEI             (0x59)
#define NAS_ESM_MSG_TFT_IEI             (0x36)
#define NAS_ESM_MSG_PCO_IEI             (0x27)
#define NAS_ESM_MSG_APN_IEI             (0x28)
#define NAS_ESM_MSG_EPS_QOS_IEI         (0x5B)
#define NAS_ESM_MSG_ESM_CAU_IEI         (0x58)
#define NAS_ESM_MSG_TI_IEI              (0x5D)
#define NAS_ESM_MSG_NQOS_IEI            (0x30)
#define NAS_ESM_MSG_NLS_IEI             (0x32)
#define NAS_ESM_MSG_PFI_IEI             (0x34)
#define NAS_ESM_MSG_RADIO_PRIO_IEI      (0x80)
#define NAS_ESM_MSG_ESMTXFG_IEI         (0xD0)
#define NAS_ESM_MSG_APN_AMBR_IEI        (0x5E)
#define NAS_ESM_MSG_NI_IEI              (0x00)

#define NAS_ESM_MSG_MIN_LEN                                 (3)
#define NAS_ESM_MIN_ESM_INFO_REQ_MSG_LEN                    (3)
#define NAS_ESM_MIN_ESM_STATUS_MSG_LEN                      (4)
#define NAS_ESM_MIN_PDN_CONN_REJ_MSG_LEN                    (4)
#define NAS_ESM_MIN_PDN_DISCONN_REJ_MSG_LEN                 (4)
#define NAS_ESM_MIN_BEARER_RES_ALLOC_REJ_MSG_LEN            (4)
#define NAS_ESM_MIN_BEARER_RES_MOD_REJ_MSG_LEN              (4)
#define NAS_ESM_MIN_DEACT_BEARER_MSG_LEN                    (4)
#define NAS_ESM_MIN_ACT_DEFAULT_BEARER_REQ_MSG_LEN          (13)
#define NAS_ESM_MIN_ACT_DEDICATED_BEARER_REQ_MSG_LEN        (8)
#define NAS_ESM_MIN_MOD_BEARER_CONTTEXT_REQ_MSG_LEN         (3)

#define NAS_ESM_TAD_BYTE                                    (1)
#define NAS_ESM_SUM_LEN_OF_PD_EBI_PTI                       (2)
#define NAS_ESM_SUM_LEN_OF_PFID_PRECEDENCE_LEN              (3)
#define NAS_ESM_SUM_LEN_OF_QCI_ULMBR_DLMBR                  (3)
#define NAS_ESM_SUM_LEN_OF_IEI_CAUSE                        (2)
#define NAS_ESM_SUM_LEN_OF_IEI_LEN                          (2)
#define NAS_ESM_LEN_IE_OCTETS                               (1)

#define NAS_ESM_PCO_ITEM_LEN_OFFSET                         (3)
#define NAS_ESM_PCO_LEN_ONLY_CONFIGURAION_PROTOCOL          (1)
#define NAS_ESM_SUM_LEN_OF_ID_LEN                           (3)

#define NAS_ESM_SRC_STATISTICS_DESCRIPTROR_SPEECH           (1)


#define NAS_ESM_QOS_IS_NULL_RATE(ulQosRate)     ((NAS_ESM_EPS_QOS_NULL_RATE == ulQosRate) \
                                                    || (NAS_ESM_EPS_QOS_NULL_RATE2 == ulQosRate))
#define NAS_ESM_APN_AMBR_IS_NULL_RATE(ucApnAmbrRate)\
                                ((NAS_ESM_APN_AMBR_NULL_RATE == ucApnAmbrRate) \
                                || (NAS_ESM_APN_AMBR_NULL_RATE2 == ucApnAmbrRate))

/* 判断是否是必选信元 */
#define NAS_ESM_IsMandatoryIei(enMsgFormat) \
((NAS_MSG_FORMAT_V == (enMsgFormat))||(NAS_MSG_FORMAT_LV == (enMsgFormat)))

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
enum NAS_MSG_FORMAT_ENUM
{
    NAS_MSG_FORMAT_TLV = 0,
    NAS_MSG_FORMAT_LV,
    NAS_MSG_FORMAT_TV,
    NAS_MSG_FORMAT_V,
    NAS_MSG_FORMAT_REESV
};
typedef VOS_UINT8  NAS_MSG_FORMAT_ENUM_UINT8;

enum NAS_ESM_INFO_FLAG_ENUM
{
    NAS_ESM_INFO_FLAG_OFF = 0,
    NAS_ESM_INFO_FLAG_ON,

    NAS_ESM_INFO_FLAG_BUTT
};
typedef VOS_UINT8  NAS_ESM_INFO_FLAG_ENUM8;


enum NAS_ESM_PCO_ITEM_TYPE_ENUM
{
    NAS_ESM_PCO_ITEM_TYPE_PAP                       = 0xC023,
    NAS_ESM_PCO_ITEM_TYPE_CHAP                      = 0xC223,
    NAS_ESM_PCO_ITEM_TYPE_IPCP                      = 0x8021,
    NAS_ESM_PCO_ITEM_TYPE_PCSCF_IPV6                = 0x0001,
    NAS_ESM_PCO_ITEM_TYPE_IM_CN_SIGNAL_FLAG         = 0x0002,
    NAS_ESM_PCO_ITEM_TYPE_DNS_SERVER_IPV6           = 0x0003,
    NAS_ESM_PCO_ITEM_TYPE_BCM                       = 0x0005,
    NAS_ESM_PCO_ITEM_TYPE_NAS_SIGNALING             = 0x000A,
    NAS_ESM_PCO_ITEM_TYPE_PCSCF_IPV4                = 0x000C,
    NAS_ESM_PCO_ITEM_TYPE_DNS_SERVER_IPV4           = 0x000D,
    NAS_ESM_PCO_ITEM_TYPE_LOCAL_ADDRESS             = 0x0011,

    NAS_ESM_PCO_ITEM_TYPE_BUTT
};
typedef VOS_UINT16  NAS_ESM_PCO_ITEM_TYPE_ENUM16;

/*rfc 1661 and rfc 1332*/
enum NAS_ESM_IPCP_MSG_TYPE_ENUM
{
    NAS_ESM_IPCP_MSG_TYPE_CONFIGURE_REQ             = 1,
    NAS_ESM_IPCP_MSG_TYPE_CONFIGURE_ACK             ,
    NAS_ESM_IPCP_MSG_TYPE_CONFIGURE_NAK             ,
    NAS_ESM_IPCP_MSG_TYPE_CONFIGURE_REJ             ,

    NAS_ESM_IPCP_MSG_TYPE_BUTT
};
typedef VOS_UINT8  NAS_ESM_IPCP_MSG_TYPE_ENUM8;

enum NAS_ESM_IPCP_OPTIONS_ENUM
{
    NAS_ESM_IPCP_OPTIONS_PRI_DNS_ADDR               = 0x81,
    NAS_ESM_IPCP_OPTIONS_SEC_DNS_ADDR               = 0x83,

    NAS_ESM_IPCP_OPTIONS_BUTT
};
typedef VOS_UINT8  NAS_ESM_IPCP_OPTIONS_ENUM8;

enum NAS_ESM_NOTIFICATION_INDICATOR_ENUM
{
    NAS_ESM_NOTIFICATION_INDICATOR_SRVCC_HO_CANCEL  = 0x01,

    NAS_ESM_NOTIFICATION_INDICATOR_BUTT
};
typedef VOS_UINT8  NAS_ESM_NOTIFICATION_INDICATOR_ENUM_ENUM8;

/*****************************************************************************
 Struct Name   : NAS_ESM_TFT_PF_COP_TYPE_ENUM
 Description   : PF的component类型枚举
 History       :
    1.sunjitan 00193151      2015-04-25  Draft Enact
*****************************************************************************/
enum NAS_ESM_TFT_PF_COP_TYPE_ENUM
{
    NAS_ESM_TFT_PF_COP_TYPE_IPV4_ADDR            = 0x10, /* IPv4 remote address type              */
    NAS_ESM_TFT_PF_COP_TYPE_IPV4_LOCAL_ADDR      = 0x11, /* IPv4 local address type               */
    NAS_ESM_TFT_PF_COP_TYPE_IPV6_ADDR            = 0x20, /* IPv6 remote address type              */
    NAS_ESM_TFT_PF_COP_TYPE_IPV6_LOCAL_ADDR      = 0x23, /* IPv6 local address/prefix length type */
    NAS_ESM_TFT_PF_COP_TYPE_PROTOCOL_ID          = 0x30, /* Protocol identifier/Next header type  */
    NAS_ESM_TFT_PF_COP_TYPE_SINGLE_LOCAL_PORT    = 0x40, /* Single local port type                */
    NAS_ESM_TFT_PF_COP_TYPE_LOCAL_PORT_RANGE     = 0x41, /* Local port range type                 */
    NAS_ESM_TFT_PF_COP_TYPE_SINGLE_REMOTE_PORT   = 0x50, /* Single remote port type               */
    NAS_ESM_TFT_PF_COP_TYPE_REMOTE_PORT_RANGE    = 0x51, /* Remote port range type                */
    NAS_ESM_TFT_PF_COP_TYPE_SPI                  = 0x60, /* Security parameter index type         */
    NAS_ESM_TFT_PF_COP_TYPE_TOS                  = 0x70, /* Type of service/Traffic class type    */
    NAS_ESM_TFT_PF_COP_TYPE_FLOW_LABLE           = 0x80, /* Flow label type                       */

    NAS_ESM_TFT_PF_COP_TYPE_BUTT
};
typedef VOS_UINT8  NAS_ESM_TFT_PF_COP_TYPE_ENUM_ENUM8;

enum NAS_ESM_CN_MSG_IE_TYPE_ENUM
{
    NAS_ESM_CN_MSG_PDN_IE               = 0x01,
    NAS_ESM_CN_MSG_TFT_IE               = 0x02,
    NAS_ESM_CN_MSG_EPS_QOS_IE           = 0x03,
    NAS_ESM_CN_MSG_APN_IE               = 0x04,
    NAS_ESM_CN_MSG_PCO_IE               = 0x05,
    NAS_ESM_CN_MSG_ESM_CAUSE_IE         = 0x06,
    NAS_ESM_CN_MSG_NQOS_IE              = 0x07,
    NAS_ESM_CN_MSG_TI_IE                = 0x08,
    NAS_ESM_CN_MSG_NLS_IE               = 0x09,
    NAS_ESM_CN_MSG_PFI_IE               = 0x0a,
    NAS_ESM_CN_MSG_RADIO_PRIO_IE        = 0x0b,
    NAS_ESM_CN_MSG_APN_AMBR_IE          = 0x0c,
    NAS_ESM_CN_MSG_EPSBID_IE            = 0x0d,
    NAS_ESM_CN_MSG_PTI_IE               = 0x0e,
    NAS_ESM_CN_MSG_LINKED_EPSBID_IE     = 0x0f,
    NAS_ESM_CN_MSG_MSG_TYPE_IE          = 0x10,
    NAS_ESM_CN_MSG_IE_NOIE              = 0x11,
    NAS_ESM_CN_MSG_MANDAN_IE            = 0x12,
    NAS_ESM_CN_MSG_OPTION_IE            = 0x13,

    NAS_ESM_CN_MSG_IE_BUTT
};
typedef VOS_UINT32 NAS_ESM_CN_MSG_IE_TYPE_ENUM_UINT32;


enum NAS_ESM_DECODE_CN_MSG_FAIL_CAUSE_ENUM
{
    ESM_DECODE_CN_MSG_IE_LEN_INVALID                        = 1,
    ESM_DECODE_CN_MSG_IE_TYPE_INVALID                       = 2,
    ESM_DECODE_CN_MSG_PD_INVALID                            = 3,
    ESM_DECODE_CN_MSG_MSG_TYPE_INVALID                      = 4,
    ESM_DECODE_CN_MSG_NOT_PARA_LIST_ID                      = 5,
    ESM_DECODE_CN_MSG_TAD_TYPE_INVALID                      = 6,
    ESM_DECODE_CN_MSG_PF_NUM_INVALID                        = 7,/*ulValue填为PF数*/
    ESM_DECODE_CN_MSG_SAME_PF_ID                            = 8,
    ESM_DECODE_CN_MSG_SAME_PF_PRECEDENCE                    = 9,
    ESM_DECODE_CN_MSG_SIGLE_PORT_AND_PORT_RANGE_COEXIST     = 10,
    ESM_DECODE_CN_MSG_IP_LEN_INVALID                        = 11,/*ulValue填为IP长度*/
    ESM_DECODE_CN_MSG_BCM_TYPE_INVALID                      = 12,/*ulValue填为BCM值*/
    ESM_DECODE_CN_MSG_PCO_CONFIG_PROTOCOL_INVALID           = 13,
    ESM_DECODE_CN_MSG_IP_TYPE_INVALID                       = 14,
    ESM_DECODE_CN_MSG_QOS_RATE_0                            = 15,
    ESM_DECODE_CN_MSG_PF_ITEM_TYPE_INVALID                  = 16,
    ESM_DECODE_CN_MSG_APN_CHARACTER_INVALID                 = 17,
    ESM_DECODE_CN_MSG_PARA_LIST_ID_INVALID                  = 18,
    ESM_DECODE_CN_MSG_IPV4_LEN_INVALID                      = 19,
    ESM_DECODE_CN_MSG_IPV6_LEN_INVALID                      = 20,
    ESM_DECODE_CN_MSG_BCM_LEN_INVALID                       = 21,
    ESM_DECODE_CN_MSG_IPCP_LEN_INVALID                      = 22,
    ESM_DECODE_CN_MSG_IPCP_PRI_DNS_LEN_INVALID              = 23,
    ESM_DECODE_CN_MSG_IPCP_SEC_DNS_LEN_INVALID              = 24,
    ESM_DECODE_CN_MSG_IPCP_OTHER_LEN_INVALID                = 25,
    ESM_DECODE_CN_MSG_LEN_INVALID                           = 26,
    ESM_DECODE_CN_MSG_ESM_MSG_PD_INVALID                    = 27,
    ESM_DECODE_CN_MSG_ESM_MSG_TYPE_INVALID                  = 28,

    ESM_DECODE_CN_MSG_IE_FAIL_CAUSE_BUTT
};
typedef VOS_UINT32 NAS_ESM_DECODE_CN_MSG_FAIL_CAUSE_ENUM_UINT32;






/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/* 动作处理函数的类型定义 */
typedef NAS_ESM_CAUSE_ENUM_UINT8  ( * NAS_ESM_DECODE_IE_FUN )
(
    VOS_UINT16             usMsgLen,
    const VOS_UINT8       *pucMsg,
    NAS_ESM_NW_MSG_STRU   *pstMsgIE
);

/* ESM消息定义-消息解码用 */
typedef struct
{
    VOS_UINT8                           ucIei;
    VOS_UINT8                           ucMask;
    NAS_MSG_FORMAT_ENUM_UINT8           enType;
    VOS_UINT8                           ucFormatLen;
    VOS_UINT16                          usMinLen;
    VOS_UINT16                          usMaxLen;
    NAS_ESM_DECODE_IE_FUN               pfDecodeFun;
}NAS_ESM_MSG_IE_STRU;

/* ESM消息解码表 */
typedef struct
{
    NAS_ESMCN_MSG_TYPE_ENUM_UINT8       enMsgTyep;
    VOS_UINT8                           ulWithLinkEpsb;
    OM_PS_AIR_MSG_ENUM_UINT8            enAirMsgId;
    VOS_UINT8                           ucMsgTableSize;
    NAS_ESM_MSG_IE_STRU                 *pstEsmMsgIE;
}NAS_ESM_DECODE_TABLE_STRU;
/*packet filter component type 对应的内容长度*/
typedef struct
{
    NAS_ESM_TFT_PF_COP_TYPE_ENUM_ENUM8       ucType;
    VOS_UINT8                                ucLen;
}NAS_ESM_PF_CONPONET_TYPE_LEN_TABLE_STRU;
/* ESM QOS RETE解析表 */
typedef VOS_VOID  ( * NAS_ESM_DECODE_QOSRATE_FUN )
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
);

typedef struct
{
    NAS_ESM_QOS_OFFSET_ENUM_UINT8       enQosRate;
    NAS_ESM_DECODE_QOSRATE_FUN          pfDecodeFun;
}NAS_ESM_DECODE_QOSRATE_TABLE_STRU;


/*****************************************************************************
 Function type  : NAS_ESM_DECODE_TFT_PF_COP_FUN
 Description    : 解析TFT的PF component type id 的函数指针定义
 History        :
      1. sunjitan 00193151  2015-04-25  Draft Enact
*****************************************************************************/
typedef VOS_VOID  (* NAS_ESM_DECODE_TFT_PF_COP_FUN)
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
);

/*****************************************************************************
 Struct Name   : NAS_ESM_DECODE_ADD_FILTER_TFT_TABLE_STRU
 Description   : 译码增加FILTER TFT的操作表
 History       :
    1.sunjitan 00193151      2015-04-25  Draft Enact
*****************************************************************************/
typedef struct
{
    NAS_ESM_TFT_PF_COP_TYPE_ENUM_ENUM8    enTftPfCopType;
    NAS_ESM_DECODE_TFT_PF_COP_FUN         pfDecodeFun;
}NAS_ESM_DECODE_ADD_FILTER_TFT_TABLE_STRU;



typedef struct
{
    MSG_HEADER_STRU                                      stMsgHeader;
    NAS_ESM_CN_MSG_IE_TYPE_ENUM_UINT32                   enIeType;
    NAS_ESM_DECODE_CN_MSG_FAIL_CAUSE_ENUM_UINT32         enCause;
    VOS_UINT32                                           ulValue;
}NAS_ESM_OM_LOG_DECODE_CN_MSG_FAIL_STRU;


typedef struct
{
    NAS_ESM_CN_MSG_IE_TYPE_ENUM_UINT32                   ulIeType;
    VOS_UINT8                                            aucPrintStr[NAS_COMM_PRINT_MAX_ITEM_LEN];
}NAS_ESM_OM_CN_MSG_IE_PRINT_STR_STRU;

typedef struct
{
    NAS_ESM_DECODE_CN_MSG_FAIL_CAUSE_ENUM_UINT32         ulFailCause;
    VOS_UINT8                                            aucPrintStr[NAS_COMM_PRINT_MAX_ITEM_LEN];
}NAS_ESM_OM_DECODE_CN_MSG_FAIL_CAUSE_PRINT_STR_STRU;





/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeTftAddFilter
       (
            NAS_ESM_NW_MSG_STRU                *pstMsgIE,
            VOS_UINT8                          *pTmp,
            VOS_UINT8                           ucToDecodePfNum
        );
extern NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeAddOneFilterTFT
       (
           NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
           const VOS_UINT8                    *pucTFTMsg,
           VOS_UINT8                          *pucLength
       );
extern NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodeNwTftValue(
                                    VOS_UINT16             usMsgLen,
                                    const VOS_UINT8       *pucMsg,
                                    NAS_ESM_NW_MSG_STRU   *pstMsgIE);
extern NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeFilterContent
      (
           NAS_ESM_NW_MSG_STRU           *pstMsgIE,
           VOS_UINT8                     *pucTmp,
           VOS_UINT8                      ucToDecodePfNum
);
extern NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeNwAPNValue(
                                           VOS_UINT16             usMsgLen,
                                           const VOS_UINT8       *pucMsg,
                                           NAS_ESM_NW_MSG_STRU   *pstMsgIE);
extern NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodeNwApnAmbrValue(
                                           VOS_UINT16  usMsgLen,
                                           const VOS_UINT8 *pucMsg,
                                           NAS_ESM_NW_MSG_STRU   *pstMsgIE);
extern NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodeNwPco
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
);
extern NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeNwPDNValue(
                                           VOS_UINT16             usMsgLen,
                                           const VOS_UINT8       *pucMsg,
                                           NAS_ESM_NW_MSG_STRU   *pstMsgIE);
extern NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeNwSdfQosValue(
                                           VOS_UINT16             usMsgLen,
                                           const VOS_UINT8       *pucMsg,
                                           NAS_ESM_NW_MSG_STRU   *pstMsgIE);
extern NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeNwMsg(VOS_UINT8 *pucMsg,
                                                VOS_UINT32 *pulMsgLen,
                                                NAS_ESM_NW_MSG_STRU *pstMsgIE);

extern VOS_VOID  NAS_ESM_EpsQosRateDecodeTo32
(
    VOS_UINT32                          ulRate32,
    VOS_UINT32                         *pulRate32
);
extern NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_SdfQosRateTran
(
    VOS_UINT8                           ucTmpLength,
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
);

extern NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_CheckNwApnAmbr(
                                        VOS_UINT16          ulUnDecodeMsgLength,
                                        VOS_UINT16         *ulDecodeLen
                                        );
extern NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodeNwApnAmbrRate
(
                                   VOS_UINT32                          *pulIndex,
                                   const VOS_UINT8                     *pucMsg,
                                   NAS_ESM_NW_MSG_STRU                 *pstMsgIE
);
extern NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodeEsmCause(
                                           VOS_UINT16  usMsgLen,
                                           const VOS_UINT8 *pucMsg,
                                           NAS_ESM_NW_MSG_STRU   *pstMsgIE);
extern NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeLlcSapi
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
);

extern NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodePacketFlowId
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
);

extern NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeRadioPriority
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
);

extern NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeTransactionId
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
);

extern NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeNegotiatedQos
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
);

extern NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeNotificationIndicator
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
);

extern VOS_VOID  NAS_ESM_DecodePcoBcm
(
    const VOS_UINT8                     *pucMsg,
    NAS_ESM_CONTEXT_PCO_STRU            *pstPco
);

extern VOS_VOID  NAS_ESM_DecodePcoBcm
(
    const VOS_UINT8                     *pucMsg,
    NAS_ESM_CONTEXT_PCO_STRU            *pstPco
);
extern VOS_VOID NAS_ESM_SdfQosUlMaxRateTran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
);
extern VOS_VOID NAS_ESM_SdfQosDlMaxRateTran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
);
extern VOS_VOID NAS_ESM_SdfQosUlGMaxRateTran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
);
extern VOS_VOID NAS_ESM_SdfQosDlGMaxRateTran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
);
extern VOS_VOID NAS_ESM_SdfQosUlMaxRateExtTran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
);
extern VOS_VOID NAS_ESM_SdfQosDlMaxRateExtTran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
);
extern VOS_VOID NAS_ESM_SdfQosUlGMaxRateExtTran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
);
extern VOS_VOID NAS_ESM_SdfQosDlGMaxRateExtTran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
);
extern VOS_VOID NAS_ESM_SdfQosUlMaxRateExt2Tran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
);
extern VOS_VOID NAS_ESM_SdfQosDlMaxRateExt2Tran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
);
extern VOS_VOID NAS_ESM_SdfQosUlGMaxRateExt2Tran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
);
extern VOS_VOID NAS_ESM_SdfQosDlGMaxRateExt2Tran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
);


extern VOS_VOID NAS_ESM_DecodeIpv4LocalAddr
(
    NAS_ESM_CONTEXT_TFT_STRU            *pstTFTInfo,
    const VOS_UINT8                     *pTmp,
    VOS_UINT8                           *pucIndex
);
extern VOS_VOID NAS_ESM_DecodeIpv6LocalAddr
(
    NAS_ESM_CONTEXT_TFT_STRU            *pstTFTInfo,
    const VOS_UINT8                     *pTmp,
    VOS_UINT8                           *pucIndex
);
extern VOS_VOID NAS_ESM_TFT_DecodePfCopTypeIpv4LocalAddr
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
);
extern VOS_VOID NAS_ESM_TFT_DecodePfCopTypeIpv6LocalAddr
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
);
extern VOS_VOID NAS_ESM_TFT_DecodePfCopTypeIpv4Addr
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
);
extern VOS_VOID NAS_ESM_TFT_DecodePfCopTypeIpv6Addr
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
);
extern VOS_VOID NAS_ESM_TFT_DecodePfCopTypeProtocolId
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
);
extern VOS_VOID NAS_ESM_TFT_DecodePfCopTypeSingleLocalPort
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
);
extern VOS_VOID NAS_ESM_TFT_DecodePfCopTypeLocalPortRange
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
);
extern VOS_VOID NAS_ESM_TFT_DecodePfCopTypeSingleRemotePort
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
);
extern VOS_VOID NAS_ESM_TFT_DecodePfCopTypeRemotePortRange
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
);
extern VOS_VOID NAS_ESM_TFT_DecodePfCopTypeSpi
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
);
extern VOS_VOID NAS_ESM_TFT_DecodePfCopTypeTos
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
);
extern VOS_VOID NAS_ESM_TFT_DecodePfCopTypeFlowLable
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
);

extern VOS_VOID NAS_ESM_SndOmLogCnMsgDecodeFail
(
    NAS_ESM_CN_MSG_IE_TYPE_ENUM_UINT32                  enIeType,
    NAS_ESM_DECODE_CN_MSG_FAIL_CAUSE_ENUM_UINT32        enCause,
    VOS_UINT32                                          ulValue
 );

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

#endif /* end of NasEsmNwMsgProc.h*/
