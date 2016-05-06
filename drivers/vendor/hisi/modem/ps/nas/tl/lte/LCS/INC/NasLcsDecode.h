

#ifndef __NASLCSDECODE_H__
#define __NASLCSDECODE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "TafLcsInterface.h"


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


/*****************************************************************************
  2 Macro
*****************************************************************************/
/* 网络原因值偏移, CAUSE由两部分组成, 高8位为TAG值,低8位为实际CAUSE */
#define NAS_LCS_NW_CAUSE_ERROR_CODE_BASE    (0x0200)
#define NAS_LCS_NW_CASUE_REL_CAUSE_BASE     (0x0800)
#define NAS_LCS_NW_CAUSE_GENERAL_REJ_BASE   (0x8000)
#define NAS_LCS_NW_CAUSE_INVOKE_REJ_BASE    (0x8100)
#define NAS_LCS_NW_CAUSE_RTRN_RSLT_REJ_BASE (0x8200)
#define NAS_LCS_NW_CAUSE_RTRN_ERR_REJ_BASE  (0x8300)


#define NAS_LCS_ONE_BYTE_BIT_NUM            (8)

#define NAS_LCS_MSG_MIN_LEN                 (2)
#define NAS_LCS_CAUSE_IE_MIN_LEN            (4)
#define NAS_LCS_CAUSE_MAX_LEN               (30)
#define NAS_LCS_IE_FACILITY_MIN_LEN         (2)
#define NAS_LCS_REG_IE_FACILITY_MIN_LEN     (8)
#define NAS_LCS_MAX_COMPONENT_LENGTH        (0xFF)
#define NAS_LCS_MAX_SERVICE_TYPE_ID         (127)
#define NAS_LCS_LOC_ESTIMATE_MAX_LEN        (20)
#define NAS_LCS_ADD_LOC_ESTIMATE_MAX_LEN    (91)
#define NAS_LCS_VEL_ESTIMATE_MIN_LEN        (4)
#define NAS_LCS_VEL_ESTIMATE_MAX_LEN        (7)
#define NAS_LCS_HGMALC_ADD_MIN_LEN          (5)
#define NAS_LCS_HGMALC_ADD_MAX_LEN          (17)
#define NAS_LCS_REP_PLMN_MAX_NUM            (20)


/****************************Component type tag******************************/
#define NAS_LCS_COMPONENT_INVOKE_TAG        (0xA1)
#define NAS_LCS_COMPONENT_RETURN_RSLT_TAG   (0xA2)
#define NAS_LCS_COMPONENT_RETURN_ERR_TAG    (0xA3)
#define NAS_LCS_COMPONENT_REJECT            (0xA4)

typedef VOS_UINT8 NAS_LCS_COMPONENT_ENUM_UINT8;
/****************************************************************************/

/****************************Component ID tag********************************/
#define NAS_LCS_INVOKE_ID_TAG               (0x02)
#define NAS_LCS_LINKED_ID_TAG               (0x80)
#define NAS_LCS_NULL_TAG                    (0x05)
/****************************************************************************/

/***************************OPERATION CODE tag*******************************/
#define NAS_LCS_OPERATION_CODE_TAG          (0x02)
/****************************************************************************/

/***************************OPERATION CODE***********************************/
#define NAS_LCS_OPERATION_NULL                              (0)
#define NAS_LCS_OPERATION_MO_LR                             (115)
#define NAS_LCS_OPERATION_LOC_NOTIFICATION                  (116)
#define NAS_LCS_OPERATION_AREA_EVENT_REQUEST                (114)
#define NAS_LCS_OPERATION_AREA_EVENT_REPORT                 (113)
#define NAS_LCS_OPERATION_AREA_EVENT_CACELLATION            (112)
#define NAS_LCS_OPERATION_PERIODIDC_LOCATION_REQUEST        (111)
#define NAS_LCS_OPERATION_LOCATION_UPDATE                   (110)
#define NAS_LCS_OPERATION_PERIODIDC_LOCATION_CACELLATION    (109)


typedef VOS_UINT32 NAS_LCS_OPERATION_TYPE_UINT32;
/****************************************************************************/

/*BER编码TAG的类型定义*/
#define NAS_LCS_BOOLEAN_TAG                         (0x01)
#define NAS_LCS_INTEGER_TAG                         (0x02)
#define NAS_LCS_BITSTRING_TAG                       (0x03)
#define NAS_LCS_OCTETSTRING_TAG                     (0x04)
#define NAS_LCS_NULL_TAG                            (0x05)
#define NAS_LCS_ENUMERATED_TAG                      (0x0A)
#define NAS_LCS_NUMERICSTRING_TAG                   (0x12)
#define NAS_LCS_IA5STRING_TAG                       (0x16)
#define NAS_LCS_SEQUENCE_TAG                        (0x30)
#define NAS_LCS_SET_TAG                             (0x31)


/*定义标签模式*/
typedef VOS_UINT8 NAS_LCS_TAG_MODE_UINT8;
#define NAS_LCS_EXPLICIT_MODE                       (1)
#define NAS_LCS_IMPLICIT_MODE                       (0)

/**定义标签结构(原子式还是构成式)**/
#define NAS_LCS_PRIMITIVE_TAG                       (0)
#define NAS_LCS_CONSTRUCTED_TAG                     (1)

#define NAS_LCS_MULTI_BYTE_TAG_FLAG                 (0x1F)
#define NAS_LCS_MULTI_BYTE_TAG_CON_OCT_MIN_VALUE    (0x80)

#define NAS_LCS_ERROR_CODE_TAG                      (0x02)

#define NAS_LCS_MSG_CAUSE_IEI                       (0x08)
#define NAS_LCS_MSG_FACILITY_IEI                    (0x1C)

#define NAS_LCS_OP_TRUE                             (1)
#define NAS_LCS_OP_FALSE                            (0)

#define NAS_LCS_INDEF_LENGTH_FLAG                   (0x80)
#define NAS_LCS_LONG_LENGTH_FORMAT_MASK             (NAS_LCS_INDEF_LENGTH_FLAG - 1)

#define NAS_LCS_REQUESTOR_ID_STRING_MAX_LEN         (160)
#define NAS_LCS_CODE_WORD_STRING_MAX_LEN            (160)

#define NAS_LCS_BIT_STRING_MIN_LEN                  (2)
#define NAS_LCS_DATA_CODING_SCHEME_LEN              (1)

#define NAS_LCS_DECIPHER_KEYS_LEN                   (15)

#define NAS_LCS_MOLR_RESLT_OP_IE_MAX_NUM            (8)
#define NAS_LCS_LOC_NTF_OP_IE_MAX_NUM               (5)
#define NAS_LCS_CLIENT_EXT_ID_OP_MAX_NUM            (2)
#define NAS_LCS_PLMN_OP_IE_MAX_NUM                  (2)
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 结构名称: NAS_LCS_LOCATION_TYPE_ENUM
 协议表格:
 ASN.1 描述:
 结构说明:Location Type枚举
*****************************************************************************/
enum NAS_LCS_LOCATION_EST_TYPE_ENUM
{
    NAS_LCS_LOCATION_TYPE_CURR_LOC               = 0,
    NAS_LCS_LOCATION_TYPE_CURR_OR_LAST_KNOWN_LOC = 1,
    NAS_LCS_LOCATION_TYPE_INITIAL_LOC            = 2,
    NAS_LCS_LOCATION_TYPE_ACT_DEFER_LOC          = 3,
    NAS_LCS_LOCATION_TYPE_CANCEL_DEFER_LOC       = 4,
    NAS_LCS_LOCATION_TYPE_NTF_VERFI_ONLY         = 5,
    NAS_LCS_LOCATION_TYPE_BUTT
};
typedef VOS_UINT8 NAS_LCS_LOCATION_EST_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名称: NAS_LCS_NOTIFICATION_TYPE_ENUM
 协议表格:
 ASN.1 描述:
 结构说明:Notifcation Type枚举
*****************************************************************************/
enum NAS_LCS_NOTIFICATION_TYPE_ENUM
{
    NAS_LCS_NOTIFY_TYPE_NOTIFY_ALLOWED              = 0,
    NAS_LCS_NOTIFY_TYPE_LOC_ALLOWED_IF_NO_RSP       = 1,
    NAS_LCS_NOTIFY_TYPE_LOC_NOT_ALLOWED_IF_NO_RSP   = 2,
    NAS_LCS_NOTIFY_TYPE_LOC_NOT_ALLOWED             = 3,

    NAS_LCS_NOTIFY_TYPE_BUTT
};
typedef VOS_UINT8 NAS_LCS_NOTIFI_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名称: NAS_LCS_CAUSE_ENUM
 协议表格:
 ASN.1 描述:
 结构说明: LCS编解码原因值
*****************************************************************************/
enum NAS_LCS_CAUSE_ENUM
{
    NAS_LCS_CAUSE_SUCCESS                                   = 0,            /* 译码成功 */
    NAS_LCS_CAUSE_FAIL                                      = 1,            /* 译码失败, 不需要回复网侧Rel */
    NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE                       = 2,            /* 信元值不在协议范围内, 回复网侧Rel(return Error) */
    NAS_LCS_CAUSE_UNRECOGNIZED_COMPONENT                    = 3,            /* Component非法,回复网侧Rel(return Rej) */
    NAS_LCS_CAUSE_MISTYPED_PARAMETER                        = 4,            /* 丢失必选信元,回复网侧Rel(return Rej) */
    NAS_LCS_CAUSE_MSG_TYPE_ERR_OR_NOT_IMPLEMENT             = 5,            /* 消息错误回复网侧Rel(return Error) */

    NAS_LCS_CAUSE_BUTT
};
typedef VOS_UINT32 NAS_LCS_CAUSE_ENUM_UINT32;

/*****************************************************************************
 结构名称: NAS_LCS_LOC_SHAP_TYPE_ENUM
 协议表格:
 ASN.1 描述:
 结构说明: LCS位置形状枚举
*****************************************************************************/
enum NAS_LCS_LOC_SHAP_TYPE_ENUM
{
    NAS_LCS_LOC_SHAP_ELLIPSOID_POINT                                            = 0,
    NAS_LCS_LOC_SHAP_ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE                    = 1,
    NAS_LCS_LOC_SHAP_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE                   = 3,
    NAS_LCS_LOC_SHAP_POLYGON                                                    = 5,
    NAS_LCS_LOC_SHAP_ELLIPSOID_POINT_WITH_ALTITUDE                              = 8,
    NAS_LCS_LOC_SHAP_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID    = 9,
    NAS_LCS_LOC_SHAP_ELLIPSOIDARC                                               = 10,

    NAS_LCS_LOC_SHAP_BUTT
};
typedef VOS_UINT32 NAS_LCS_LOC_SHAP_TYPE_ENUM_UINT32;

/*****************************************************************************
 结构名称: NAS_LCS_VELOCITY_TYPE_ENUM
 协议表格:
 ASN.1 描述:
 结构说明: 速度类型枚举
*****************************************************************************/
enum NAS_LCS_VELOCITY_TYPE_ENUM
{
    NAS_LCS_VELOCITY_TYPE_HORIZONTAL_VELOCITY                                   = 0,
    NAS_LCS_VELOCITY_TYPE_HORIZONTAL_WITH_VERTICAL_VELOCITY                     = 1,
    NAS_LCS_VELOCITY_TYPE_HORIZONTAL_VELOCITY_WITH_UNCERTAINTY                  = 2,
    NAS_LCS_VELOCITY_TYPE_HORIZONTAL_WITH_VERTICAL_VELOCITY_AND_UNCERTAINTY     = 3,

    NAS_LCS_VELOCITY_TYPE_BUTT
};
typedef VOS_UINT32 NAS_LCS_VELOCITY_TYPE_ENUM_UINT32;


/*****************************************************************************
 结构名称: NAS_LCS_NW_CAUSE_ENUM
 协议表格:
 ASN.1 描述:
 结构说明: 网络原因值枚举, 使用16位表示, 其中高8位为TAG值, 低8位为实际网络原因值
*****************************************************************************/
enum NAS_LCS_NW_CAUSE_ENUM
{
    /* Error Code原因值 */
    NAS_LCS_CAUSE_NW_ERR_SS_SUBVIOLATION                  = (NAS_LCS_NW_CAUSE_ERROR_CODE_BASE + 19),   /* 超过用户权限 */
    NAS_LCS_CAUSE_NW_ERR_FACILITY_NOT_SUPPORT             = (NAS_LCS_NW_CAUSE_ERROR_CODE_BASE + 21),   /* Facility不支持 */
    NAS_LCS_CAUSE_NW_ERR_SYSTEM_FAIL                      = (NAS_LCS_NW_CAUSE_ERROR_CODE_BASE + 34),   /* 网络异常 */
    NAS_LCS_CAUSE_NW_ERR_DATA_MISSING                     = (NAS_LCS_NW_CAUSE_ERROR_CODE_BASE + 35),   /* 缺失数据 */
    NAS_LCS_CAUSE_NW_ERR_UNEXPECT_DATA_VALUE              = (NAS_LCS_NW_CAUSE_ERROR_CODE_BASE + 36),   /* 非法数据 */
    NAS_LCS_CAUSE_NW_ERR_POSITION_METHOD_FAIL             = (NAS_LCS_NW_CAUSE_ERROR_CODE_BASE + 54),   /* 定位方式错误 */

    /* Rej Compnent Problem原因值 */
    /*********************** General Problem Codes ********************/
    NAS_LCS_NW_CAUSE_UNRECOGNIZED_COMPONENT                = NAS_LCS_NW_CAUSE_GENERAL_REJ_BASE + 0,
    NAS_LCS_NW_CAUSE_MISTYPED_COMPONENT                    = NAS_LCS_NW_CAUSE_GENERAL_REJ_BASE + 1,
    NAS_LCS_NW_CAUSE_BADLY_STRUCTURED_COMPONENT            = NAS_LCS_NW_CAUSE_GENERAL_REJ_BASE + 2,

    /************************Invoke Problem Codes***********************/
    NAS_LCS_NW_CAUSE_DUPLICATE_INVOKE_ID                   = NAS_LCS_NW_CAUSE_INVOKE_REJ_BASE + 0,
    NAS_LCS_NW_CAUSE_UNRECOGNIZED_OPERATION                = NAS_LCS_NW_CAUSE_INVOKE_REJ_BASE + 1,
    NAS_LCS_NW_CAUSE_INVOKE_MISTYPED_PARAMETER             = NAS_LCS_NW_CAUSE_INVOKE_REJ_BASE + 2,
    NAS_LCS_NW_CAUSE_RESOURCE_LIMITATION                   = NAS_LCS_NW_CAUSE_INVOKE_REJ_BASE + 3,
    NAS_LCS_NW_CAUSE_INITIATING_RELEASE                    = NAS_LCS_NW_CAUSE_INVOKE_REJ_BASE + 4,
    NAS_LCS_NW_CAUSE_UNRECOGNIZED_LINKED_ID                = NAS_LCS_NW_CAUSE_INVOKE_REJ_BASE + 5,
    NAS_LCS_NW_CAUSE_LINKED_RESPONSE_UNEXPECTED            = NAS_LCS_NW_CAUSE_INVOKE_REJ_BASE + 6,
    NAS_LCS_NW_CAUSE_UNEXPECTED_LINKED_OPERATION           = NAS_LCS_NW_CAUSE_INVOKE_REJ_BASE + 7,
    NAS_LCS_NW_CAUSE_INVALID_MANDATORY_IE                  = NAS_LCS_NW_CAUSE_INVOKE_REJ_BASE + 8,

    /**********************Return Result Problem Codes******************/
    NAS_LCS_NW_CAUSE_RETURN_RSLT_UNRECOGNIZED_INVOKE_ID    = NAS_LCS_NW_CAUSE_RTRN_RSLT_REJ_BASE + 0,
    NAS_LCS_NW_CAUSE_RETURN_RSLT_UNEXPECTED                = NAS_LCS_NW_CAUSE_RTRN_RSLT_REJ_BASE + 1,
    NAS_LCS_NW_CAUSE_RETURN_RSLT_MISTYPED_PARAMETER        = NAS_LCS_NW_CAUSE_RTRN_RSLT_REJ_BASE + 3,

    /**********************Return Error Problem Codes********************/
    NAS_LCS_NW_CAUSE_RETURN_ERROR_UNRECOGNIZED_INVOKE_ID   = NAS_LCS_NW_CAUSE_RTRN_ERR_REJ_BASE + 0,
    NAS_LCS_NW_CAUSE_RETURN_ERROR_UNEXPECTED               = NAS_LCS_NW_CAUSE_RTRN_ERR_REJ_BASE + 1,
    NAS_LCS_NW_CAUSE_RETURN_ERROR_UNRECOGNIZED_ERROR       = NAS_LCS_NW_CAUSE_RTRN_ERR_REJ_BASE + 2,
    NAS_LCS_NW_CAUSE_RETURN_ERROR_UNEXPECTED_ERROR         = NAS_LCS_NW_CAUSE_RTRN_ERR_REJ_BASE + 3,
    NAS_LCS_NW_CAUSE_RETURN_ERROR_MISTYPED_PARAMETER       = NAS_LCS_NW_CAUSE_RTRN_ERR_REJ_BASE + 4,

    NAS_LCS_NW_CAUSE_BUTT
};
typedef VOS_UINT32 NAS_LCS_NW_CAUSE_ENUM_UINT32;
/*****************************************************************************
 结构名称: NAS_LCS_LENGTH_TYPE_ENUM
 协议表格:
 ASN.1 描述:
 结构说明: BER LEN类型
*****************************************************************************/
enum NAS_LCS_LENGTH_TYPE_ENUM
{
    NAS_LCS_LENGTH_TYPE_SHORT_DEF                   = 0,
    NAS_LCS_LENGTH_TYPE_LONG_DEF                    = 1,
    NAS_LCS_LENGTH_TYPE_INDEF                       = 2,

    NAS_LCS_LENGTH_TYPE_BUTT
};
typedef VOS_UINT8 NAS_LCS_LENGTH_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名称: NAS_LCS_FORMAT_INDICATOR_ENUM
 协议表格:
 ASN.1 描述:
 结构说明: ROMAT INDICATOR枚举
*****************************************************************************/
enum NAS_LCS_FORMAT_INDICATOR_ENUM
{
    NAS_LCS_FORMAT_LOGICALNAME                      = 0,
    NAS_LCS_FORMAT_EMAIL_ADDR                       = 1,
    NAS_LCS_FORMAT_MSISDN                           = 2,
    NAS_LCS_FORMAT_URL                              = 3,
    NAS_LCS_FORMAT_SIP_URL                          = 4,

    NAS_LCS_FORMAT_BUTT
};
typedef VOS_UINT8 NAS_LCS_FORMAT_INDICATOR_ENUM_UINT8;

/*****************************************************************************
 结构名称: NAS_LCS_RAN_TECH_ENUM
 协议表格:
 ASN.1 描述:
 结构说明: Ran Technology枚举类型
*****************************************************************************/
enum NAS_LCS_RAN_TECH_ENUM
{
    NAS_LCS_RAN_TECH_GSM                            = 0,
    NAS_LCS_RAN_TECH_UMTS                           = 1,

    NAS_LCS_RAN_TECH_BUTT
};
typedef VOS_UINT8 NAS_LCS_RAN_TECH_ENUM_UINT8;

/*****************************************************************************
 结构名称: NAS_LCS_PROBLEM_TAG_ENUM
 协议表格:
 ASN.1 描述:
 结构说明: Problem Tag枚举类型
*****************************************************************************/
enum NAS_LCS_PROBLEM_TAG_ENUM
{
    NAS_LCS_PROBLEM_GENERAL_TAG                     = 0x80,             /* 1 0 0 0 0 0 0 0 General       */
    NAS_LCS_PROBLEM_INVOKE_TAG                      = 0x81,             /* 1 0 0 0 0 0 0 1 Invoke        */
    NAS_LCS_PROBLEM_RTN_RSLT_TAG                    = 0x82,             /* 1 0 0 0 0 0 1 0 Return Result */
    NAS_LCS_PROBLEM_RTN_ERR_TAG                     = 0x83,             /* 1 0 0 0 0 0 1 1 Return Error  */

    NAS_LCS_PROBLEM_TAG_BUTT
};
typedef VOS_UINT8 NAS_LCS_PROBLEM_TAG_ENUM_UINT8;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名称: NAS_LCS_EXTERNAL_ADDR_STRU
 协议表格:
 ASN.1 描述:
 结构说明: 空口Client External ADDR结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucLen;
    VOS_UINT8                               aucRsv[3];
    VOS_UINT8                               aucAddr[LCS_CLIENT_EXID_MAX_LEN];
}NAS_LCS_EXTERNAL_ADDR_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_CLIENT_EXTERNAL_ID_STRU
 协议表格:
 ASN.1 描述:
 结构说明: 空口Client External Id结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              bitOpExternalAddr       :1;
    VOS_UINT32                              bitOpSpare              :31;

    NAS_LCS_EXTERNAL_ADDR_STRU              stExternalAddr;
}NAS_LCS_CLIENT_EXTERNAL_ID_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_NAME_STRING_STRU
 协议表格:
 ASN.1 描述:
 结构说明: 空口Client Name String结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucLen;
    VOS_UINT8                               aucRsv[3];
    VOS_UINT8                               aucNameString[LCS_CLIENT_NAME_MAX_LEN];
}NAS_LCS_NAME_STRING_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_CLIENT_NAME_STRU
 协议表格:
 ASN.1 描述:
 结构说明: 空口Client Name结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              bitOpLcsFormat          :1;
    VOS_UINT32                              bitOpSpare              :31;

    VOS_UINT8                               ucDataCodeScheme;
    NAS_LCS_FORMAT_INDICATOR_ENUM_UINT8     enLcsFormat;
    VOS_UINT8                               aucRsv[2];
    NAS_LCS_NAME_STRING_STRU                stNameString;
}NAS_LCS_CLIENT_NAME_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_REQUESTOR_ID_STRING_STRU
 协议表格:
 ASN.1 描述:
 结构说明: 空口Requertor Id String结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucLen;
    VOS_UINT8                               aucRsv[3];
    VOS_UINT8                               aucReqIdString[NAS_LCS_REQUESTOR_ID_STRING_MAX_LEN];
}NAS_LCS_REQUESTOR_ID_STRING_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_REQUESTOR_ID_STRU
 协议表格:
 ASN.1 描述:
 结构说明: 空口Requertor Id结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              bitOpLcsFormat          :1;
    VOS_UINT32                              bitOpSpare              :31;

    VOS_UINT8                               ucDataCodeScheme;
    NAS_LCS_FORMAT_INDICATOR_ENUM_UINT8     enLcsFormat;
    VOS_UINT8                               aucRsv[2];
    NAS_LCS_REQUESTOR_ID_STRING_STRU        stReqString;
}NAS_LCS_REQUESTOR_ID_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_CODE_WORD_STRING_STRU
 协议表格:
 ASN.1 描述:
 结构说明: 空口 Code Word String结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucLen;
    VOS_UINT8                               aucRsv[3];
    VOS_UINT8                               aucCodeWord[NAS_LCS_CODE_WORD_STRING_MAX_LEN];
}NAS_LCS_CODE_WORD_STRING_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_CODE_WORD_STRU
 协议表格:
 ASN.1 描述:
 结构说明: 空口 Code Word结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucDataCodeScheme;
    VOS_UINT8                               aucRsv[3];
    NAS_LCS_CODE_WORD_STRING_STRU           stCodeWord;
}NAS_LCS_CODE_WORD_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_LOCATION_TYPE_STRU
 协议表格:
 ASN.1 描述:
 结构说明: Location type结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              bitOpDeferLocEventType  :1;
    VOS_UINT32                              bitOpSpare              :31;

    NAS_LCS_LOCATION_EST_TYPE_ENUM_UINT8    enLocType;

    /* bit8表示msAvailable,bit7表示enteringIntoArea,bit6表示leavingFromArea,bit5表示beginInsideArea,bit4表示perodicLDR */
    VOS_UINT8                               ucDeferLocEventType;
    VOS_UINT8                               aucRsv[2];
}NAS_LCS_LOCATION_TYPE_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_LOC_NOTFICATION_STRU
 协议表格:
 ASN.1 描述:
 结构说明: MT-LR lcs-LocationNotification空口结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              bitOpClientExternalId   :1;
    VOS_UINT32                              bitOpClientName         :1;
    VOS_UINT32                              bitOpRequestorId        :1;
    VOS_UINT32                              bitOpCodeWord           :1;
    VOS_UINT32                              bitOpServiceTypeId      :1;
    VOS_UINT32                              bitOpSpare              :27;

    NAS_LCS_LOCATION_TYPE_STRU              stLocationType;
    NAS_LCS_CLIENT_EXTERNAL_ID_STRU         stClientExternalId;
    NAS_LCS_CLIENT_NAME_STRU                stClientName;
    NAS_LCS_REQUESTOR_ID_STRU               stRequestorId;
    NAS_LCS_CODE_WORD_STRU                  stCodeWord;
    NAS_LCS_NOTIFI_TYPE_ENUM_UINT8          enNtfType;
    VOS_UINT8                               ucServiceTypeId;
    VOS_UINT8                               aucRsv[2];
}NAS_LCS_LOC_NOTFICATION_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_HGMLC_ADDR_STRU
 协议表格:
 ASN.1 描述:
 结构说明: MO LR信元h gmlc address结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucLen;
    VOS_UINT8                               aucHGmlcAddr[NAS_LCS_HGMALC_ADD_MAX_LEN];
    VOS_UINT8                               aucRsv[2];
}NAS_LCS_HGMLC_ADDR_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_PLMN_ID_STRU
 协议表格:
 ASN.1 描述:
 结构说明: MO LR信元plmn id结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPlmnId[3];
    VOS_UINT8                           ucRsv;
}NAS_LCS_PLMN_ID_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_PLMN_STRU
 协议表格:
 ASN.1 描述:
 结构说明: MO LR信元plmn结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              bitOpRanTech            :1;
    VOS_UINT32                              bitOpRanPerLocSupp      :1;
    VOS_UINT32                              bitOpSpare              :30;

    NAS_LCS_PLMN_ID_STRU                    stPlmnId;
    NAS_LCS_RAN_TECH_ENUM_UINT8             enRanTech;
    VOS_UINT8                               aucRsv[3];
}NAS_LCS_PLMN_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_PLMN_LIST_STRU
 协议表格:
 ASN.1 描述:
 结构说明: MO LR信元plmn list结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucPlmnNum;
    VOS_UINT8                               ucRsv[3];
    NAS_LCS_PLMN_STRU                       astPlmn[NAS_LCS_REP_PLMN_MAX_NUM];
}NAS_LCS_PLMN_LIST_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_REPORT_PLMN_LIST_STRU
 协议表格:
 ASN.1 描述:
 结构说明: MO LR信元reporting plmn list结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              bitOpPlmnPriority       :1;
    VOS_UINT32                              bitOpSpare              :31;

    NAS_LCS_PLMN_LIST_STRU                  stPlmnList;
}NAS_LCS_REPORT_PLMN_LIST_STRU;
/*****************************************************************************
 结构名称: NAS_LCS_MOLR_RESULT_STRU
 协议表格:
 ASN.1 描述:
 结构说明: MO LR网侧回复定位结果解析结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              bitOpDecipherKeys       :1;
    VOS_UINT32                              bitOpReferNumber        :1;
    VOS_UINT32                              bitOpHGmlcAddr          :1;
    VOS_UINT32                              bitOpShortCircuit       :1;
    VOS_UINT32                              bitOpRepPlmnList        :1;
    VOS_UINT32                              bitOpLocationEstimate   :1;
    VOS_UINT32                              bitOpVelocityEstimate   :1;
    VOS_UINT32                              bitOpSpare              :25;

    VOS_UINT8                               aucDecipherKeys[NAS_LCS_DECIPHER_KEYS_LEN];
    VOS_UINT8                               ucReferNumber;
    NAS_LCS_HGMLC_ADDR_STRU                 stHGmlcAddr;
    NAS_LCS_REPORT_PLMN_LIST_STRU           stRepPlmnList;
    LOC_COM_COORDINATE_STRU                 stLocationEstimate;             /* 位置信息 */
    LOC_COM_VELOCITY_STRU                   stVelocityEstimate;             /* 速度信息 */
}NAS_LCS_MOLR_RESULT_STRU;
/*****************************************************************************
 结构名称: NAS_LCS_CN_MSG_TYPE_ENUM_UINT32
 协议表格:
 ASN.1 描述:
 结构说明: LCS消息名
*****************************************************************************/
enum NAS_LCS_CN_MSG_TYPE_ENUM
{
    NAS_LCS_CN_MSG_REL_CML      = 0x2A,
    NAS_LCS_CN_MSG_FACILITY     = 0x3A,
    NAS_LCS_CN_MSG_REGISTER     = 0x3B,

    NAS_LCS_CN_MSG_BUTT
};
typedef VOS_UINT32 NAS_LCS_CN_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 结构名称: NAS_LCS_CN_MSG_STRU
 协议表格:
 ASN.1 描述:
 结构说明: LCS空口结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              bitOpNwCause            :1;
    VOS_UINT32                              bitOpLinkedId           :1;
    VOS_UINT32                              bitOperationCode        :1;
    VOS_UINT32                              bitOpLocNotification    :1;
    VOS_UINT32                              bitOpMolrResult         :1;
    VOS_UINT32                              bitOpInvokeId           :1;
    VOS_UINT32                              bitOpSpare              :26;

    NAS_LCS_CN_MSG_TYPE_ENUM_UINT32         enCnMsgType;
    VOS_UINT8                               ucTi;
    VOS_UINT8                               ucInvokeId;
    VOS_UINT8                               ucLinkedId;
    VOS_UINT8                               ucOperationCode;
    VOS_UINT8                               ucComponentType;
    VOS_UINT8                               aucRsv[3];
    NAS_LCS_LOC_NOTFICATION_STRU            stLocNotication;
    NAS_LCS_MOLR_RESULT_STRU                stMolrResult;
    NAS_LCS_NW_CAUSE_ENUM_UINT32            enNwCause;
}NAS_LCS_CN_MSG_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_TAG_STRU
 协议表格:
 ASN.1 描述:
 结构说明: LCS TAG结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8               ucClass;
    VOS_UINT8               ucStructed;
    VOS_UINT8               aucRsv[2];
    VOS_UINT32              ulNumber;
}NAS_LCS_TAG_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/
/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern NAS_LCS_CN_MSG_STRU                     g_stLcsCnDecodeMsgStru;
/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeCnMsg
(
    VOS_UINT8                           *pucMsg,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeRegister
(
    VOS_UINT8                           *pucMsg,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeFacility
(
    VOS_UINT8                           *pucMsg,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeRelCmpl
(
    VOS_UINT8                           *pucMsg,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeIeFacility
(
    VOS_UINT8                           *pucMsg,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeCause
(
    VOS_UINT8                           *pucMsg,
    VOS_UINT32                          *puLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeComponent
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeRtrnRslt
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeMoLrResult
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_MOLR_RESULT_STRU            *pstLocNtfStru
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeRtrnErr
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeReject
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeInvoke
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeInvokeId
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulDecodeMsgLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLinkedId
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulDecodeMsgLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeOperationCode
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulDecodeMsgLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru,
    VOS_UINT8                           *pucOperationCode
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLocNotification
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_LOC_NOTFICATION_STRU        *pstLocNtfStru
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeNotificationOpIe
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_LOC_NOTFICATION_STRU        *pstLocNtfStru
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeRequestorID
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_REQUESTOR_ID_STRU           *pstRequestorId
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeRequestorIDString
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_REQUESTOR_ID_STRING_STRU    *pstReqString
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeCodeWord
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CODE_WORD_STRU              *pstCodeWord
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeCodeWordString
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CODE_WORD_STRING_STRU       *pstCodeWord
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeServiceTypeId
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    VOS_UINT8                           *pucServiceTypeId
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeCilentExtId
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CLIENT_EXTERNAL_ID_STRU     *pstClientExternalId
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeExternalAddr
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CLIENT_EXTERNAL_ID_STRU     *pstClientExternalId
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeExtensionContainer
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CLIENT_EXTERNAL_ID_STRU     *pstClientExternalId
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeClientName
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CLIENT_NAME_STRU            *pstClientName
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeFormatIndicator
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_FORMAT_INDICATOR_ENUM_UINT8 *penLcsFormat
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeClientNameString
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CLIENT_NAME_STRU            *pstClientName
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeDataCodingScheme
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    VOS_UINT8                           *pucDataCodeScheme
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeNotificationType
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    VOS_UINT8                           *pucNtfType
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLocationType
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_LOCATION_TYPE_STRU          *pstLocationType
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeDeferLocEventType
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    VOS_UINT8                           *pucDeferLocEventType
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeTL
(
    VOS_UINT8                           *pucSrc,
    NAS_LCS_TAG_STRU                    *pstTagStru,
    VOS_UINT32                          *pulVaulueLen,
    VOS_UINT32                          *pulLen
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeTag
(
    VOS_UINT8                           *pucSrc,
    NAS_LCS_TAG_STRU                    *pstTagStru,
    VOS_UINT32                          *pulLen
);
extern NAS_LCS_CAUSE_ENUM_UINT32  NAS_LCS_DecodeLength
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pucLen,
    VOS_UINT32                          *pulDecodeLen
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_CheckIeLenVaild
(
    VOS_UINT32                          ulUndecodeLen,
    VOS_UINT32                          ulTLlen,
    VOS_UINT32                          ulValueLen
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLocEstimate
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    LOC_COM_COORDINATE_STRU             *pstLocationEstimate
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeReportPlmnList
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_REPORT_PLMN_LIST_STRU       *pstRepPlmnList
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodePlmnList
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_PLMN_LIST_STRU              *pstPlmnList
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodePlmn
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_PLMN_STRU                   *pstPlmn
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeHGmlcAddr
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_HGMLC_ADDR_STRU             *pstHGmlcAddr
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeVelEstimate
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    LOC_COM_VELOCITY_STRU               *pstVelEstimate
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeAddLocEstimate
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    LOC_COM_COORDINATE_STRU             *pstLocationEstimate
);
extern NAS_LCS_OPERATION_TYPE_UINT32 NAS_LCS_GetRegisterOperaCode
(
    VOS_UINT8                          *pucFacilityIe,
    VOS_UINT32                          ulLen
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeIndefLen(VOS_UINT8 *pucSrc, VOS_UINT8 *pucLen);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_CheckOperationCode(NAS_LCS_OPERATION_TYPE_UINT32 ulOperationCode);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_CheckProblemTagVaild(NAS_LCS_PROBLEM_TAG_ENUM_UINT8 enProblemTag);
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

#endif /* end of NasLcsPubuGlobal.h */

