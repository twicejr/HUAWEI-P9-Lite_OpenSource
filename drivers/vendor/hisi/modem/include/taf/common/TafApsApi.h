
#ifndef _TAF_APS_API_H_
#define _TAF_APS_API_H_


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafClientApi.h"
#include "TafTypeDef.h"
#include "PsTypeDef.h"
#include "TafApi.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define TAF_PS_MSG_ID_BASE                  (0x0000)
#define TAF_PS_EVT_ID_BASE                  (0x0A00)

/* "a1.a2.a3.a4 " */
#define TAF_IPV4_ADDR_LEN               (4)

/* "a1...a16" */
#define TAF_IPV6_ADDR_LEN               (16)
#define TAF_MAX_PREFIX_NUM_IN_RA        (6)

/* ^AUTHDATA */
#define TAF_MAX_AUTHDATA_USERNAME_LEN   (127)
#define TAF_MAX_AUTHDATA_PASSWORD_LEN   (127)
#define TAF_MAX_AUTHDATA_PLMN_LEN       (6)

/* ^CGAUTH */
#define TAF_MAX_PDP_AUTH_USERNAME_LEN   (99)
#define TAF_MAX_PDP_AUTH_PASSCODE_LEN   (99)

#define TAF_MAX_ACCESS_NUM_LEN          (32)
#define TAF_MAX_GW_AUTH_USERNAME_LEN    (255)
#define TAF_MAX_GW_AUTH_PASSWORD_LEN    (255)

#define TAF_MAX_PDP_PROFILE_NUM         (32)
#define TAF_MAX_SDF_PF_NUM              (16)

#define TAF_MAX_APN_LEN                 (99)

/*所支持最大的PDP参数表项目数*/

#if (FEATURE_ON == FEATURE_LTE)
#define TAF_MAX_CID                     (31)
#else
#define TAF_MAX_CID                     (11)
#endif
#define TAF_MAX_CID_NV                  (11)

#define TAF_INVALID_CID                 (0xFF)

/* 4 x 3 char dec nums + 3 x '.' + '\0' */
#define TAF_MAX_IPV4_ADDR_STR_LEN       (16)

/* 8 x 4 字符(HEX) + 7 x ':' + '\0' */
#define TAF_MAX_IPV6_ADDR_COLON_STR_LEN (40)

/* 32 x 3 字符(DEC) + 31 x '.' + '\0' */
#define TAF_MAX_IPV6_ADDR_DOT_STR_LEN   (128)

#define TAF_IPV6_STR_MAX_TOKENS         (16)                                    /* IPV6字符串格式使用的分隔符标记最大个数 */

#define TAF_IPV6_STR_RFC2373_TOKENS     (8)                                     /* RFC2373规定的IPV6字符串格式使用的分隔符标记最大个数 */

#define TAF_IPV4_STR_DELIMITER          '.'                                     /* RFC协议使用的IPV4文本表达方式使用的分隔符 */
#define TAF_IPV6_STR_DELIMITER          ':'                                     /* RFC2373使用的IPV6文本表达方式使用的分隔符 */

#define TAF_IPV6_PREFIX_LEN             (8)                                     /* IPv6地址前缀长度 */

#define TAF_MAX_USERNAME_LEN            (99)                                    /*AUTHLEN 为100，包含1个字节的Peer-ID Length和99字节的Peer-ID，故此处定义为99*/
#define TAF_MAX_PASSCODE_LEN            (99)                                    /*PASSWORDLEN 为100，包含1个字节的Passwd-Length和99字节的Passwd，故此处定义为99*/

#define TAF_PS_MAX_PDPID                (11)


/* password+auth */
#define TAF_PPP_PAP_REQ_MAX_LEN             (100 + 100)

/* code(1B)+id(1B)+length(2B)+challenge_size(1B)+challenge+name */
#define TAF_PPP_CHAP_CHALLENGE_MAX_LEN      (1 + 1 + 2 + 1 + 48 + 100)

/* code(1B)+id(1B)+length(2B)+response_size(1B)+response+name */
#define TAF_PPP_CHAP_RESPONSE_MAX_LEN       (1 + 1 + 2 + 1 + 100 + 100)

#define TAF_PPP_AUTH_FRAME_BUF_MAX_LEN      (256)

#define TAF_PPP_IPCP_FRAME_BUF_MAX_LEN      (256)

#define TAF_DEFAULT_DSFLOW_NV_WR_INTERVAL   (2)             /* DSFLOW流量统计NV写间隔, 单位(min) */

#define TAF_PS_CAUSE_APS_SECTION_BEGIN      (0x0000)
#define TAF_PS_CAUSE_SM_SECTION_BEGIN       (0x0080)
#define TAF_PS_CAUSE_SM_NW_SECTION_BEGIN    (0x0100)
#define TAF_PS_CAUSE_SM_NW_SECTION_END      (0x01FF)
#define TAF_PS_CAUSE_GMM_SECTION_BEGIN      (0x0200)
#define TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN   (0x0300)
#define TAF_PS_CAUSE_XCC_SECTION_BEGIN      (0x0400)
#define TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN   (0x0500)
#define TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN   (0x0600)
#define TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN (0X0700)
/* 偏移量0X0800已被占用，ril侧将对0 ~ 255的内部原因值往后偏移0X0800 */

#define TAF_PS_IS_SM_CAUSE_VALID(sm_cause)\
            ( (((sm_cause) + TAF_PS_CAUSE_SM_NW_SECTION_BEGIN) >= TAF_PS_CAUSE_SM_NW_OPERATOR_DETERMINED_BARRING)\
             && (((sm_cause) + TAF_PS_CAUSE_SM_NW_SECTION_BEGIN) <= TAF_PS_CAUSE_SM_NW_APN_RESTRICTION_INCOMPATIBLE) )

#define TAF_PS_CONVERT_SM_CAUSE_TO_PS_CAUSE(sm_cause)\
            ((sm_cause) + TAF_PS_CAUSE_SM_NW_SECTION_BEGIN)

#define TAF_PS_GET_MSG_CONTENT(pstMsg)\
            ((VOS_VOID *)(((TAF_PS_MSG_STRU *)(pstMsg))->aucContent))


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名称: TAF_PS_MSG_ID_ENUM
 枚举说明: PS域接口消息ID

 修改历史      :
  1.日    期   : 2013年06月18日
    作    者   : A00165503
    修改内容   : 新增枚举
*****************************************************************************/
enum TAF_PS_MSG_ID_ENUM
{
    /*----------------------------------------------------------------------
       标准命令[0x0000, 0x0099]
    *---------------------------------------------------------------------*/
    /* +CGDCONT */
    ID_MSG_TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ             = TAF_PS_MSG_ID_BASE + 0x0001,  /* _H2ASN_MsgChoice TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU */
    ID_MSG_TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ             = TAF_PS_MSG_ID_BASE + 0x0002,  /* _H2ASN_MsgChoice TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ_STRU */

    /* +CGDSCONT */
    ID_MSG_TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ              = TAF_PS_MSG_ID_BASE + 0x0003,  /* _H2ASN_MsgChoice TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU */
    ID_MSG_TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ              = TAF_PS_MSG_ID_BASE + 0x0004,  /* _H2ASN_MsgChoice TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ_STRU */

    /* +CGTFT */
    ID_MSG_TAF_PS_SET_TFT_INFO_REQ                          = TAF_PS_MSG_ID_BASE + 0x0005,  /* _H2ASN_MsgChoice TAF_PS_SET_TFT_INFO_REQ_STRU */
    ID_MSG_TAF_PS_GET_TFT_INFO_REQ                          = TAF_PS_MSG_ID_BASE + 0x0006,  /* _H2ASN_MsgChoice TAF_PS_GET_TFT_INFO_REQ_STRU */

    /* +CGQREQ */
    ID_MSG_TAF_PS_SET_GPRS_QOS_INFO_REQ                     = TAF_PS_MSG_ID_BASE + 0x0007,  /* _H2ASN_MsgChoice */
    ID_MSG_TAF_PS_GET_GPRS_QOS_INFO_REQ                     = TAF_PS_MSG_ID_BASE + 0x0008,  /* _H2ASN_MsgChoice */

    /* +CGQMIN */
    ID_MSG_TAF_PS_SET_GPRS_QOS_MIN_INFO_REQ                 = TAF_PS_MSG_ID_BASE + 0x0009,  /* _H2ASN_MsgChoice */
    ID_MSG_TAF_PS_GET_GPRS_QOS_MIN_INFO_REQ                 = TAF_PS_MSG_ID_BASE + 0x000A,  /* _H2ASN_MsgChoice */

    /* +CGEQREQ */
    ID_MSG_TAF_PS_SET_UMTS_QOS_INFO_REQ                     = TAF_PS_MSG_ID_BASE + 0x000B,  /* _H2ASN_MsgChoice TAF_PS_SET_UMTS_QOS_INFO_REQ_STRU */
    ID_MSG_TAF_PS_GET_UMTS_QOS_INFO_REQ                     = TAF_PS_MSG_ID_BASE + 0x000C,  /* _H2ASN_MsgChoice TAF_PS_GET_UMTS_QOS_INFO_REQ_STRU */

    /* +CGEQMIN */
    ID_MSG_TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ                 = TAF_PS_MSG_ID_BASE + 0x000D,  /* _H2ASN_MsgChoice TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU */
    ID_MSG_TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ                 = TAF_PS_MSG_ID_BASE + 0x000E,  /* _H2ASN_MsgChoice TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ_STRU */

    /* +CGEQNEG */
    ID_MSG_TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ             = TAF_PS_MSG_ID_BASE + 0x000F,  /* _H2ASN_MsgChoice TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ_STRU */

    /* +CGACT */
    ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ                 = TAF_PS_MSG_ID_BASE + 0x0010,  /* _H2ASN_MsgChoice TAF_PS_SET_PDP_STATE_REQ_STRU */
    ID_MSG_TAF_PS_GET_PDP_CONTEXT_STATE_REQ                 = TAF_PS_MSG_ID_BASE + 0x0011,  /* _H2ASN_MsgChoice TAF_PS_GET_PDP_STATE_REQ_STRU */

    /* +CGCMOD */
    ID_MSG_TAF_PS_CALL_MODIFY_REQ                           = TAF_PS_MSG_ID_BASE + 0x0012,  /* _H2ASN_MsgChoice TAF_PS_CALL_MODIFY_REQ_STRU */

    /* +CGANS */
    ID_MSG_TAF_PS_CALL_ANSWER_REQ                           = TAF_PS_MSG_ID_BASE + 0x0013,  /* _H2ASN_MsgChoice TAF_PS_CALL_ANSWER_REQ_STRU */
    ID_MSG_TAF_PS_CALL_HANGUP_REQ                           = TAF_PS_MSG_ID_BASE + 0x0014,  /* _H2ASN_MsgChoice TAF_PS_CALL_HANGUP_REQ_STRU */

    /* +CGPADDR */
    ID_MSG_TAF_PS_GET_PDP_IP_ADDR_INFO_REQ                  = TAF_PS_MSG_ID_BASE + 0x0015,  /* _H2ASN_MsgChoice TAF_PS_GET_PDP_IP_ADDR_INFO_REQ_STRU */

    ID_MSG_TAF_PS_GET_PDPCONT_INFO_REQ                      = TAF_PS_MSG_ID_BASE + 0x0016, /* _H2ASN_MsgChoice TAF_PS_GET_PDP_CONTEXT_INFO_REQ_STRU */

    /* +CGAUTO */
    ID_MSG_TAF_PS_SET_ANSWER_MODE_INFO_REQ                  = TAF_PS_MSG_ID_BASE + 0x0017,  /* _H2ASN_MsgChoice TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU */
    ID_MSG_TAF_PS_GET_ANSWER_MODE_INFO_REQ                  = TAF_PS_MSG_ID_BASE + 0x0018,  /* _H2ASN_MsgChoice TAF_PS_GET_ANSWER_MODE_INFO_REQ_STRU */

    /* +CGCONTRDP */
    ID_MSG_TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ     = TAF_PS_MSG_ID_BASE + 0x0019,  /* _H2ASN_MsgChoice TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU */

    /* +CGSCONTRDP */
    ID_MSG_TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ      = TAF_PS_MSG_ID_BASE + 0x001A,  /* _H2ASN_MsgChoice TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ_STRU */

    /* +CGTFTRDP */
    ID_MSG_TAF_PS_GET_DYNAMIC_TFT_INFO_REQ                  = TAF_PS_MSG_ID_BASE + 0x001B,  /* _H2ASN_MsgChoice TAF_PS_GET_DYNAMIC_TFT_INFO_REQ_STRU */

    /* +CGEQOS */
    ID_MSG_TAF_PS_SET_EPS_QOS_INFO_REQ                      = TAF_PS_MSG_ID_BASE + 0x001C,  /* _H2ASN_MsgChoice TAF_PS_SET_EPS_QOS_INFO_REQ_STRU */
    ID_MSG_TAF_PS_GET_EPS_QOS_INFO_REQ                      = TAF_PS_MSG_ID_BASE + 0x001D,  /* _H2ASN_MsgChoice TAF_PS_GET_EPS_QOS_INFO_REQ_STRU */

    /* +CGEQOSRDP */
    ID_MSG_TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ              = TAF_PS_MSG_ID_BASE + 0x001E,  /* _H2ASN_MsgChoice TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ_STRU */

    /*----------------------------------------------------------------------
       私有命令[0x0100, 0x0199]
    *---------------------------------------------------------------------*/
    /* ^NDISCONN/^NDISDUP */
    ID_MSG_TAF_PS_CALL_ORIG_REQ                             = TAF_PS_MSG_ID_BASE + 0x0101,  /* _H2ASN_MsgChoice TAF_PS_CALL_ORIG_REQ_STRU */
    ID_MSG_TAF_PS_CALL_END_REQ                              = TAF_PS_MSG_ID_BASE + 0x0102,  /* _H2ASN_MsgChoice TAF_PS_CALL_END_REQ_STRU */

    /* D */
    ID_MSG_TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ                = TAF_PS_MSG_ID_BASE + 0x0103,  /* _H2ASN_MsgChoice TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU */

    /* PPP */
    ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ                         = TAF_PS_MSG_ID_BASE + 0x0104,  /* _H2ASN_MsgChoice TAF_PS_PPP_DIAL_ORIG_REQ_STRU */

    /* ^DSFLOWQRY */
    ID_MSG_TAF_PS_GET_DSFLOW_INFO_REQ                       = TAF_PS_MSG_ID_BASE + 0x0105,  /* _H2ASN_MsgChoice TAF_PS_GET_DSFLOW_INFO_REQ_STRU */

    /* ^DSFLOWCLR */
    ID_MSG_TAF_PS_CLEAR_DSFLOW_REQ                          = TAF_PS_MSG_ID_BASE + 0x0106,  /* _H2ASN_MsgChoice TAF_PS_CLEAR_DSFLOW_REQ_STRU */

    /* ^DSFLOWRPT */
    ID_MSG_TAF_PS_CONFIG_DSFLOW_RPT_REQ                     = TAF_PS_MSG_ID_BASE + 0x0107,  /* _H2ASN_MsgChoice TAF_PS_CONFIG_DSFLOW_RPT_REQ_STRU */

    /* ^DWINS */
    ID_MSG_TAF_PS_CONFIG_NBNS_FUNCTION_REQ                  = TAF_PS_MSG_ID_BASE + 0x0108,  /* _H2ASN_MsgChoice TAF_PS_CONFIG_NBNS_FUNCTION_REQ_STRU */

    /* ^AUTHDATA */
    ID_MSG_TAF_PS_SET_AUTHDATA_INFO_REQ                     = TAF_PS_MSG_ID_BASE + 0x0109,  /* _H2ASN_MsgChoice TAF_PS_SET_AUTHDATA_INFO_REQ_STRU */
    ID_MSG_TAF_PS_GET_AUTHDATA_INFO_REQ                     = TAF_PS_MSG_ID_BASE + 0x010A,  /* _H2ASN_MsgChoice TAF_PS_GET_AUTHDATA_INFO_REQ_STRU */

    /* ^DNSQUERY */
    ID_MSG_TAF_PS_GET_NEGOTIATION_DNS_REQ                   = TAF_PS_MSG_ID_BASE + 0x010B,  /* _H2ASN_MsgChoice TAF_PS_GET_NEGOTIATION_DNS_REQ_STRU */

    /* ^CGAUTH */
    ID_MSG_TAF_PS_SET_PDP_AUTH_INFO_REQ                     = TAF_PS_MSG_ID_BASE + 0x010C,  /* _H2ASN_MsgChoice TAF_PS_SET_PDP_AUTH_INFO_REQ_STRU */
    ID_MSG_TAF_PS_GET_PDP_AUTH_INFO_REQ                     = TAF_PS_MSG_ID_BASE + 0x010D,  /* _H2ASN_MsgChoice TAF_PS_GET_PDP_AUTH_INFO_REQ_STRU */

    /* ^CGDNS */
    ID_MSG_TAF_PS_SET_PDP_DNS_INFO_REQ                      = TAF_PS_MSG_ID_BASE + 0x010E,  /* _H2ASN_MsgChoice TAF_PS_SET_PDP_DNS_INFO_REQ_STRU */
    ID_MSG_TAF_PS_GET_PDP_DNS_INFO_REQ                      = TAF_PS_MSG_ID_BASE + 0x010F,  /* _H2ASN_MsgChoice TAF_PS_GET_PDP_DNS_INFO_REQ_STRU */

    /* ^TRIG */
    ID_MSG_TAF_PS_TRIG_GPRS_DATA_REQ                        = TAF_PS_MSG_ID_BASE + 0x0110,  /* _H2ASN_MsgChoice TAF_PS_TRIG_GPRS_DATA_REQ_STRU */

    /*^LTECS*/
    ID_MSG_TAF_PS_GET_LTE_CS_REQ                            = TAF_PS_MSG_ID_BASE + 0x0111,  /* _H2ASN_MsgChoice TAF_PS_LTECS_REQ_STRU */

    /* ^PDPROFMOD */
    ID_MSG_TAF_PS_SET_PDPROFMOD_INFO_REQ                    = TAF_PS_MSG_ID_BASE + 0x0112,  /* _H2ASN_MsgChoice TAF_PS_SET_PROFILE_INFO_REQ_STRU */

    /* ^CEMODE */
    ID_MSG_TAF_PS_GET_CEMODE_REQ                            = TAF_PS_MSG_ID_BASE + 0x0113,  /* _H2ASN_MsgChoice TAF_PS_CEMODE_REQ_STRU */

    /* 异步接口获取SDF信息 */
    ID_MSG_TAF_PS_GET_CID_SDF_REQ                           = TAF_PS_MSG_ID_BASE + 0x0114,  /* _H2ASN_MsgChoice TAF_SDF_PARA_QUERY_INFO_STRU */

    /* 异步接口获取CID */
    ID_MSG_TAF_PS_GET_UNUSED_CID_REQ                        = TAF_PS_MSG_ID_BASE + 0x0115,  /* _H2ASN_MsgChoice */

    ID_MSG_TAF_PS_SET_CQOS_PRI_REQ                          = TAF_PS_MSG_ID_BASE + 0x0116,  /* _H2ASN_MsgChoice TAF_PS_SET_1X_CQOS_PRI_REQ_STRU */

    /* CDMA下，进入DORMANT状态指示 */
    ID_MSG_TAF_PS_CALL_ENTER_DORMANT_IND                    = TAF_PS_MSG_ID_BASE + 0x0117,  /* _H2ASN_MsgChoice TAF_PS_CALL_ENTER_DORMANT_IND_STRU */

    ID_MSG_TAF_PS_HAI_CHANGE_IND                            = TAF_PS_MSG_ID_BASE + 0x0118,  /* _H2ASN_MsgChoice TAF_PS_HAI_CHANGE_IND_STRU */

    /* ^APDSFLOWRPT */
    ID_MSG_TAF_PS_SET_APDSFLOW_RPT_CFG_REQ                  = TAF_PS_MSG_ID_BASE + 0x0119,  /* _H2ASN_MsgChoice TAF_PS_SET_APDSFLOW_RPT_CFG_REQ_STRU */
    ID_MSG_TAF_PS_GET_APDSFLOW_RPT_CFG_REQ                  = TAF_PS_MSG_ID_BASE + 0x011A,  /* _H2ASN_MsgChoice TAF_PS_GET_APDSFLOW_RPT_CFG_REQ_STRU */

    ID_MSG_TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ               = TAF_PS_MSG_ID_BASE + 0x011B,  /* _H2ASN_MsgChoice TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ_STRU */
    ID_MSG_TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ               = TAF_PS_MSG_ID_BASE + 0x011C,  /* _H2ASN_MsgChoice TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ_STRU */

    /* +CTA*/
    ID_MSG_TAF_PS_SET_CTA_INFO_REQ                          = TAF_PS_MSG_ID_BASE + 0x011D,  /* _H2ASN_MsgChoice TAF_PS_SET_CTA_INFO_REQ_STRU */
    ID_MSG_TAF_PS_GET_CTA_INFO_REQ                          = TAF_PS_MSG_ID_BASE + 0x011E,  /* _H2ASN_MsgChoice TAF_PS_GET_1X_CTA_INFO_REQ_STRU */

    ID_MSG_TAF_PS_SET_CDMA_DIAL_MODE_REQ                    = TAF_PS_MSG_ID_BASE + 0x011F,  /* _H2ASN_MsgChoice TAF_PS_CDATA_DIAL_MODE_REQ_STRU */

    ID_MSG_TAF_PS_GET_CGMTU_VALUE_REQ                       = TAF_PS_MSG_ID_BASE + 0x0120,  /* _H2ASN_MsgChoice TAF_PS_GET_CGMTU_VALUE_REQ_STRU */

    /* ^IMSPDPCFG */
    ID_MSG_TAF_PS_SET_IMS_PDP_CFG_REQ                       = TAF_PS_MSG_ID_BASE + 0x0121,  /* _H2ASN_MsgChoice TAF_PS_SET_IMS_PDP_CFG_REQ_STRU */

    /* ^CDORMTIMER */
    ID_MSG_TAF_PS_SET_1X_DORM_TIMER_REQ                     = TAF_PS_MSG_ID_BASE + 0x0122,  /* _H2ASN_MsgChoice TAF_PS_SET_1X_DORMANT_TIMER_REQ_STRU */
    ID_MSG_TAF_PS_GET_1X_DORM_TIEMR_REQ                     = TAF_PS_MSG_ID_BASE + 0X0123,  /* _H2ASN_MsgChoice TAF_PS_GET_1X_DORMANT_TIMER_REQ_STRU */

    ID_MSG_TAF_PS_BUTT

};
typedef VOS_UINT32 TAF_PS_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名称: TAF_PS_EVT_ID_ENUM
 枚举说明: TAF和APP之间的事件原语

 修改历史      :
  1.日    期   : 2011年10月19日
    作    者   : A00165503
    修改内容   : 新增枚举
*****************************************************************************/
enum TAF_PS_EVT_ID_ENUM
{
    /* PS CALL */
    ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF                     = TAF_PS_EVT_ID_BASE + 0x0001,           /* _H2ASN_MsgChoice TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU           */
    ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ                     = TAF_PS_EVT_ID_BASE + 0x0002,           /* _H2ASN_MsgChoice TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU           */
    ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_IND                     = TAF_PS_EVT_ID_BASE + 0x0003,           /* _H2ASN_MsgChoice TAF_PS_CALL_PDP_ACTIVATE_IND_STRU           */
    ID_EVT_TAF_PS_CALL_PDP_MANAGE_IND                       = TAF_PS_EVT_ID_BASE + 0x0004,           /* _H2ASN_MsgChoice TAF_PS_CALL_PDP_MANAGE_IND_STRU             */
    ID_EVT_TAF_PS_CALL_PDP_MODIFY_CNF                       = TAF_PS_EVT_ID_BASE + 0x0005,           /* _H2ASN_MsgChoice TAF_PS_CALL_PDP_MODIFY_CNF_STRU             */
    ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ                       = TAF_PS_EVT_ID_BASE + 0x0006,           /* _H2ASN_MsgChoice TAF_PS_CALL_PDP_MODIFY_REJ_STRU             */
    ID_EVT_TAF_PS_CALL_PDP_MODIFY_IND                       = TAF_PS_EVT_ID_BASE + 0x0007,           /* _H2ASN_MsgChoice TAF_PS_CALL_PDP_MODIFY_IND_STRU             */
    ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF                   = TAF_PS_EVT_ID_BASE + 0x0008,           /* _H2ASN_MsgChoice TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU         */
    ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND                   = TAF_PS_EVT_ID_BASE + 0x0009,           /* _H2ASN_MsgChoice TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU         */
    ID_EVT_TAF_PS_CALL_PDP_DISCONNECT_IND                   = TAF_PS_EVT_ID_BASE + 0x000A,           /* _H2ASN_MsgChoice TAF_PS_CALL_PDP_PDP_DISCONNECT_IND_STRU     */
    ID_EVT_TAF_PS_CALL_PDP_IPV6_INFO_IND                    = TAF_PS_EVT_ID_BASE + 0x000B,           /* _H2ASN_MsgChoice TAF_PS_IPV6_INFO_IND_STRU                   */

    ID_EVT_TAF_PS_CALL_ORIG_CNF                             = TAF_PS_EVT_ID_BASE + 0x0031,           /* _H2ASN_MsgChoice TAF_PS_CALL_ORIG_CNF_STRU                   */
    ID_EVT_TAF_PS_CALL_END_CNF                              = TAF_PS_EVT_ID_BASE + 0x0032,           /* _H2ASN_MsgChoice TAF_PS_CALL_END_CNF_STRU                    */
    ID_EVT_TAF_PS_CALL_MODIFY_CNF                           = TAF_PS_EVT_ID_BASE + 0x0033,           /* _H2ASN_MsgChoice TAF_PS_CALL_MODIFY_CNF_STRU                 */
    ID_EVT_TAF_PS_CALL_ANSWER_CNF                           = TAF_PS_EVT_ID_BASE + 0x0034,           /* _H2ASN_MsgChoice TAF_PS_CALL_ANSWER_CNF_STRU                 */
    ID_EVT_TAF_PS_CALL_HANGUP_CNF                           = TAF_PS_EVT_ID_BASE + 0x0035,           /* _H2ASN_MsgChoice TAF_PS_CALL_HANGUP_CNF_STRU                 */

    /* D */
    ID_EVT_TAF_PS_GET_D_GPRS_ACTIVE_TYPE_CNF                = TAF_PS_EVT_ID_BASE + 0x0100,           /* _H2ASN_MsgChoice TAF_PS_GET_D_GPRS_ACTIVE_TYPE_CNF_STRU      */

    /* PPP */
    ID_EVT_TAF_PS_PPP_DIAL_ORIG_CNF                         = TAF_PS_EVT_ID_BASE + 0x0101,           /* _H2ASN_MsgChoice TAF_PS_PPP_DIAL_ORIG_CNF_STRU               */

    /* +CGDCONT */
    ID_EVT_TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_CNF             = TAF_PS_EVT_ID_BASE + 0x0102,           /* _H2ASN_MsgChoice TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_CNF_STRU   */
    ID_EVT_TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF             = TAF_PS_EVT_ID_BASE + 0x0103,           /* _H2ASN_MsgChoice TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF_STRU   */

    /* +CGDSCONT */
    ID_EVT_TAF_PS_SET_SEC_PDP_CONTEXT_INFO_CNF              = TAF_PS_EVT_ID_BASE + 0x0104,           /* _H2ASN_MsgChoice TAF_PS_SET_SEC_PDP_CONTEXT_INFO_CNF_STRU    */
    ID_EVT_TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF              = TAF_PS_EVT_ID_BASE + 0x0105,           /* _H2ASN_MsgChoice TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF_STRU    */

    /* +CGTFT */
    ID_EVT_TAF_PS_SET_TFT_INFO_CNF                          = TAF_PS_EVT_ID_BASE + 0x0106,           /* _H2ASN_MsgChoice TAF_PS_SET_TFT_INFO_CNF_STRU                */
    ID_EVT_TAF_PS_GET_TFT_INFO_CNF                          = TAF_PS_EVT_ID_BASE + 0x0107,           /* _H2ASN_MsgChoice TAF_PS_GET_TFT_INFO_CNF_STRU                */

    /* +CGQREQ */
    ID_EVT_TAF_PS_SET_GPRS_QOS_INFO_CNF                     = TAF_PS_EVT_ID_BASE + 0x0108,           /* _H2ASN_MsgChoice */
    ID_EVT_TAF_PS_GET_GPRS_QOS_INFO_CNF                     = TAF_PS_EVT_ID_BASE + 0x0109,           /* _H2ASN_MsgChoice */

    /* +CGQMIN */
    ID_EVT_TAF_PS_SET_GPRS_QOS_MIN_INFO_CNF                 = TAF_PS_EVT_ID_BASE + 0x010A,           /* _H2ASN_MsgChoice */
    ID_EVT_TAF_PS_GET_GPRS_QOS_MIN_INFO_CNF                 = TAF_PS_EVT_ID_BASE + 0x010B,           /* _H2ASN_MsgChoice */

    /* +CGEQREQ */
    ID_EVT_TAF_PS_SET_UMTS_QOS_INFO_CNF                     = TAF_PS_EVT_ID_BASE + 0x010C,           /* _H2ASN_MsgChoice TAF_PS_SET_UMTS_QOS_INFO_CNF_STRU           */
    ID_EVT_TAF_PS_GET_UMTS_QOS_INFO_CNF                     = TAF_PS_EVT_ID_BASE + 0x010D,           /* _H2ASN_MsgChoice TAF_PS_GET_UMTS_QOS_INFO_CNF_STRU           */

    /* +CGEQMIN */
    ID_EVT_TAF_PS_SET_UMTS_QOS_MIN_INFO_CNF                 = TAF_PS_EVT_ID_BASE + 0x010E,           /* _H2ASN_MsgChoice TAF_PS_SET_UMTS_QOS_MIN_INFO_CNF_STRU       */
    ID_EVT_TAF_PS_GET_UMTS_QOS_MIN_INFO_CNF                 = TAF_PS_EVT_ID_BASE + 0x010F,           /* _H2ASN_MsgChoice TAF_PS_GET_UMTS_QOS_MIN_INFO_CNF_STRU       */

    /* +CGEQNEG */
    ID_EVT_TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_CNF             = TAF_PS_EVT_ID_BASE + 0x0110,           /* _H2ASN_MsgChoice TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_CNF_STRU   */

    /* +CGACT */
    ID_EVT_TAF_PS_SET_PDP_CONTEXT_STATE_CNF                 = TAF_PS_EVT_ID_BASE + 0x0111,           /* _H2ASN_MsgChoice TAF_PS_SET_PDP_STATE_CNF_STRU       */
    ID_EVT_TAF_PS_GET_PDP_CONTEXT_STATE_CNF                 = TAF_PS_EVT_ID_BASE + 0x0112,           /* _H2ASN_MsgChoice TAF_PS_GET_PDP_STATE_CNF_STRU       */

    /* +CGPADDR */
    ID_EVT_TAF_PS_GET_PDP_IP_ADDR_INFO_CNF                  = TAF_PS_EVT_ID_BASE + 0x0113,           /* _H2ASN_MsgChoice TAF_PS_GET_PDP_IP_ADDR_INFO_CNF_STRU        */
    ID_EVT_TAF_PS_GET_PDP_CONTEXT_INFO_CNF                  = TAF_PS_EVT_ID_BASE + 0x0114,           /* _H2ASN_MsgChoice TAF_PS_GET_PDP_CONTEXT_INFO_CNF_STRU        */

    /* +CGAUTO */
    ID_EVT_TAF_PS_SET_ANSWER_MODE_INFO_CNF                  = TAF_PS_EVT_ID_BASE + 0x0115,           /* _H2ASN_MsgChoice TAF_PS_SET_ANSWER_MODE_INFO_CNF_STRU        */
    ID_EVT_TAF_PS_GET_ANSWER_MODE_INFO_CNF                  = TAF_PS_EVT_ID_BASE + 0x0116,           /* _H2ASN_MsgChoice TAF_PS_GET_ANSWER_MODE_INFO_CNF_STRU        */

    /* +CGCONTRDP */
    ID_EVT_TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF     = TAF_PS_EVT_ID_BASE + 0x0117,           /* _H2ASN_MsgChoice TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU */

    /* +CGSCONTRDP */
    ID_EVT_TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF      = TAF_PS_EVT_ID_BASE + 0x0118,           /* _H2ASN_MsgChoice TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF_STRU */

    /* +CGTFTRDP */
    ID_EVT_TAF_PS_GET_DYNAMIC_TFT_INFO_CNF                  = TAF_PS_EVT_ID_BASE + 0x0119,           /* _H2ASN_MsgChoice TAF_PS_GET_DYNAMIC_TFT_INFO_CNF_STRU        */

    /* +CGEQOS */
    ID_EVT_TAF_PS_SET_EPS_QOS_INFO_CNF                      = TAF_PS_EVT_ID_BASE + 0x011A,           /* _H2ASN_MsgChoice TAF_PS_SET_EPS_QOS_INFO_CNF_STRU            */
    ID_EVT_TAF_PS_GET_EPS_QOS_INFO_CNF                      = TAF_PS_EVT_ID_BASE + 0x011B,           /* _H2ASN_MsgChoice TAF_PS_GET_EPS_QOS_INFO_CNF_STRU            */

    /* +CGEQOSRDP */
    ID_EVT_TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF              = TAF_PS_EVT_ID_BASE + 0x011C,           /* _H2ASN_MsgChoice TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF_STRU    */

    /* ^DSFLOWQRY */
    ID_EVT_TAF_PS_GET_DSFLOW_INFO_CNF                       = TAF_PS_EVT_ID_BASE + 0x011D,           /* _H2ASN_MsgChoice TAF_PS_GET_DSFLOW_INFO_CNF_STRU             */

    /* ^DSFLOWCLR */
    ID_EVT_TAF_PS_CLEAR_DSFLOW_CNF                          = TAF_PS_EVT_ID_BASE + 0x011E,           /* _H2ASN_MsgChoice TAF_PS_CLEAR_DSFLOW_CNF_STRU                */

    /* ^DSFLOWRPT */
    ID_EVT_TAF_PS_CONFIG_DSFLOW_RPT_CNF                     = TAF_PS_EVT_ID_BASE + 0x011F,           /* _H2ASN_MsgChoice TAF_PS_CONFIG_DSFLOW_RPT_CNF_STRU           */

    /* ^DSFLOWRPT */
    ID_EVT_TAF_PS_REPORT_DSFLOW_IND                         = TAF_PS_EVT_ID_BASE + 0x0120,           /* _H2ASN_MsgChoice TAF_PS_REPORT_DSFLOW_IND_STRU               */

    /* ^CGAUTH */
    ID_EVT_TAF_PS_SET_PDP_AUTH_INFO_CNF                     = TAF_PS_EVT_ID_BASE + 0x0121,           /* _H2ASN_MsgChoice TAF_PS_SET_PDP_AUTH_INFO_CNF_STRU           */
    ID_EVT_TAF_PS_GET_PDP_AUTH_INFO_CNF                     = TAF_PS_EVT_ID_BASE + 0x0122,           /* _H2ASN_MsgChoice TAF_PS_GET_PDP_AUTH_INFO_CNF_STRU           */

    /* ^CGDNS */
    ID_EVT_TAF_PS_SET_PDP_DNS_INFO_CNF                      = TAF_PS_EVT_ID_BASE + 0x0123,           /* _H2ASN_MsgChoice TAF_PS_SET_PDP_DNS_INFO_CNF_STRU            */
    ID_EVT_TAF_PS_GET_PDP_DNS_INFO_CNF                      = TAF_PS_EVT_ID_BASE + 0x0124,           /* _H2ASN_MsgChoice TAF_PS_GET_PDP_DNS_INFO_CNF_STRU            */

    /* ^TRIG */
    ID_EVT_TAF_PS_TRIG_GPRS_DATA_CNF                        = TAF_PS_EVT_ID_BASE + 0x0125,           /* _H2ASN_MsgChoice TAF_PS_TRIG_GPRS_DATA_CNF_STRU              */

    /* ^DWINS */
    ID_EVT_TAF_PS_CONFIG_NBNS_FUNCTION_CNF                  = TAF_PS_EVT_ID_BASE + 0x0126,           /* _H2ASN_MsgChoice TAF_PS_CONFIG_NBNS_FUNCTION_CNF_STRU        */

    /* ^AUTHDATA */
    ID_EVT_TAF_PS_SET_AUTHDATA_INFO_CNF                     = TAF_PS_EVT_ID_BASE + 0x0127,           /* _H2ASN_MsgChoice TAF_PS_SET_AUTHDATA_INFO_CNF_STRU           */
    ID_EVT_TAF_PS_GET_AUTHDATA_INFO_CNF                     = TAF_PS_EVT_ID_BASE + 0x0128,           /* _H2ASN_MsgChoice TAF_PS_GET_AUTHDATA_INFO_CNF_STRU           */

    /* ^DNSQUERY */
    ID_EVT_TAF_PS_GET_NEGOTIATION_DNS_CNF                   = TAF_PS_EVT_ID_BASE + 0x0129,           /* _H2ASN_MsgChoice TAF_PS_GET_NEGOTIATION_DNS_CNF_STRU         */

    /* ^LTECS */
    ID_EVT_TAF_PS_LTECS_INFO_CNF                            = TAF_PS_EVT_ID_BASE + 0x012A,           /* _H2ASN_MsgChoice TAF_PS_LTECS_CNF_STRU                       */

    /* ^PDPROFMOD */
    ID_EVT_TAF_PS_SET_PDP_PROF_INFO_CNF                     = TAF_PS_EVT_ID_BASE + 0x012B,           /* _H2ASN_MsgChoice TAF_PS_SET_PDP_PROF_INFO_CNF_STRU           */

    /* +CEMODE */
    ID_EVT_TAF_PS_CEMODE_INFO_CNF                           = TAF_PS_EVT_ID_BASE + 0x012C,           /* _H2ASN_MsgChoice TAF_PS_CEMODE_CNF_STRU                      */

    /* 异步接口获取SDF信息 */
    ID_EVT_TAF_PS_GET_CID_SDF_CNF                           = TAF_PS_EVT_ID_BASE + 0x012D,           /* _H2ASN_MsgChoice TAF_PS_SDF_INFO_CNF_STRU                    */

    /* ^CQOSPRI */
    ID_EVT_TAF_PS_SET_CQOS_PRI_CNF                          = TAF_PS_EVT_ID_BASE + 0x012E,           /* _H2ASN_MsgChoice TAF_PS_SET_CQOS_PRI_CNF_STRU                */

    /* ^APDSFLOWRPT */
    ID_EVT_TAF_PS_SET_APDSFLOW_RPT_CFG_CNF                  = TAF_PS_EVT_ID_BASE + 0x012F,           /* _H2ASN_MsgChoice TAF_PS_SET_APDSFLOW_RPT_CFG_CNF_STRU */
    ID_EVT_TAF_PS_GET_APDSFLOW_RPT_CFG_CNF                  = TAF_PS_EVT_ID_BASE + 0x0130,           /* _H2ASN_MsgChoice TAF_PS_GET_APDSFLOW_RPT_CFG_CNF_STRU */
    ID_EVT_TAF_PS_APDSFLOW_REPORT_IND                       = TAF_PS_EVT_ID_BASE + 0x0131,           /* _H2ASN_MsgChoice TAF_PS_APDSFLOW_REPORT_IND_STRU */

    ID_EVT_TAF_PS_SET_DSFLOW_NV_WRITE_CFG_CNF               = TAF_PS_EVT_ID_BASE + 0x0132,           /* _H2ASN_MsgChoice TAF_PS_SET_DSFLOW_NV_WRITE_CFG_CNF_STRU */
    ID_EVT_TAF_PS_GET_DSFLOW_NV_WRITE_CFG_CNF               = TAF_PS_EVT_ID_BASE + 0x0133,           /* _H2ASN_MsgChoice TAF_PS_GET_DSFLOW_NV_WRITE_CFG_CNF_STRU */

    /* +CTA */
    ID_EVT_TAF_PS_SET_CTA_INFO_CNF                          = TAF_PS_EVT_ID_BASE + 0x0134,           /* _H2ASN_MsgChoice TAF_PS_SET_CTA_INFO_CNF_STRU */
    ID_EVT_TAF_PS_GET_CTA_INFO_CNF                          = TAF_PS_EVT_ID_BASE + 0x0135,           /* _H2ASN_MsgChoice TAF_PS_GET_CTA_INFO_CNF_STRU */

    /* +CRM */
    ID_EVT_TAF_PS_SET_CDMA_DIAL_MODE_CNF                    = TAF_PS_EVT_ID_BASE + 0x0136,           /* _H2ASN_MsgChoice TAF_PS_CDATA_DIAL_MODE_CNF_STRU                */

    ID_EVT_TAF_PS_GET_CGMTU_VALUE_CNF                       = TAF_PS_EVT_ID_BASE + 0x0137,          /* _H2ASN_MsgChoice TAF_PS_GET_CGMTU_VALUE_CNF_STRU                */
    ID_EVT_TAF_PS_CGMTU_VALUE_CHG_IND                       = TAF_PS_EVT_ID_BASE + 0x0138,          /* _H2ASN_MsgChoice TAF_PS_CGMTU_VALUE_CHG_IND_STRU                */

    /* 其它事件 */
    /* APS->IMSA通知SRVCC CANCEL */
    ID_EVT_TAF_PS_SRVCC_CANCEL_NOTIFY_IND                   = TAF_PS_EVT_ID_BASE + 0x0200,           /* _H2ASN_MsgChoice TAF_SRVCC_CANCEL_NOTIFY_IND_STRU */

    ID_EVT_TAF_PS_SET_IMS_PDP_CFG_CNF                       = TAF_PS_EVT_ID_BASE + 0x0201,           /* _H2ASN_MsgChoice TAF_PS_SET_IMS_PDP_CFG_CNF_STRU */

    ID_EVT_TAF_PS_SET_1X_DORM_TIMER_CNF                     = TAF_PS_EVT_ID_BASE + 0x0202,           /* _H2ASN_MsgChoice TAF_PS_SET_1X_DORM_TIMER_CNF_STRU */
    ID_EVT_TAF_PS_GET_1X_DORM_TIMER_CNF                     = TAF_PS_EVT_ID_BASE + 0x0203,           /* _H2ASN_MsgChoice TAF_PS_GET_1X_DORM_TIMER_CNF_STRU */

    ID_EVT_TAF_PS_BUTT
};
typedef VOS_UINT32 TAF_PS_EVT_ID_ENUM_UINT32;


/*****************************************************************************
 枚举名称: TAF_PS_CAUSE_ENUM
 枚举说明: TAF上报的PS域呼叫原因值

 修改历史      :
  1.日    期   : 2012年8月23日
    作    者   : A00165503
    修改内容   : 新增枚举
*****************************************************************************/
enum TAF_PS_CAUSE_ENUM
{
    /*----------------------------------------------------------------------
       TAF上报的内部原因值, 取值范围[0x0000, 0x007F]
    *---------------------------------------------------------------------*/
    TAF_PS_CAUSE_SUCCESS                                    = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 0),
    TAF_PS_CAUSE_INVALID_PARAMETER                          = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 1),
    TAF_PS_CAUSE_CID_INVALID                                = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 2),
    TAF_PS_CAUSE_PDP_ACTIVATE_LIMIT                         = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 3),
    TAF_PS_CAUSE_SIM_INVALID                                = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 4),
    TAF_PS_CAUSE_APS_TIME_OUT                               = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 5),
    TAF_PS_CAUSE_OPERATION_CONFLICT                         = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 6),
    TAF_PS_CAUSE_XCC_TIME_OUT                               = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 7),
    TAF_PS_CAUSE_PPP_TIME_OUT                               = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 8),
    TAF_PS_CAUSE_PPP_NEGOTIATE_FAIL                         = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 9),
    TAF_PS_CAUSE_1X_NO_SERVICE                              = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 10),
    TAF_PS_CAUSE_HRPD_NO_SERVICE                            = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 11),
    TAF_PS_CAUSE_HSM_TIME_OUT                               = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 12),
    TAF_PS_CAUSE_PPP_MODE_CHANGE                            = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 13),
    TAF_PS_CAUSE_EHSM_TIME_OUT                              = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 14),
    TAF_PS_CAUSE_RAT_TYPE_CHANGE                            = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 15),
    TAF_PS_CAUSE_DHCP_TIME_OUT                              = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 16),
    TAF_PS_CAUSE_PDP_TYPE_IPV4_ONLY_ALLOWED                 = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 17),
    TAF_PS_CAUSE_PDP_TYPE_IPV6_ONLY_ALLOWED                 = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 18),
    TAF_PS_CAUSE_PPP_NW_DISC                                = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 19),
    TAF_PS_CAUSE_UNSUPPORT_PCSCF                            = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 20),
    TAF_PS_CAUSE_SYSCFG_MODE_CHANGE                         = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 21),
    TAF_PS_CAUSE_UNKNOWN                                    = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 127),

    /*----------------------------------------------------------------------
       TAF上报的SM内部原因值, 取值范围[0x0080, 0x00FF]
    *---------------------------------------------------------------------*/
    TAF_PS_CAUSE_SM_CONN_ESTABLISH_MAX_TIME_OUT             = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 1),
    TAF_PS_CAUSE_SM_MAX_TIME_OUT                            = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 2),
    TAF_PS_CAUSE_SM_INVALID_NSAPI                           = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 3),
    TAF_PS_CAUSE_SM_MODIFY_COLLISION                        = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 4),
    TAF_PS_CAUSE_SM_DUPLICATE                               = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 5),
    TAF_PS_CAUSE_SM_RAB_SETUP_FAILURE                       = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 6),
    TAF_PS_CAUSE_SM_SGSN_VER_PRE_R99                        = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 7),
    TAF_PS_CAUSE_SM_FAILURE                                 = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 8),
    TAF_PS_CAUSE_SM_ERR_UNSPECIFIED_ERROR                   = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 9),
    TAF_PS_CAUSE_SM_ERR_INSUFFICIENT_RESOURCES              = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 10),
    TAF_PS_CAUSE_SM_CALL_CID_INVALID                        = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 11),
    TAF_PS_CAUSE_SM_CALL_CID_ACTIVE                         = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 12),
    TAF_PS_CAUSE_SM_CALL_CID_NOT_MATCH_BEARER               = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 13),
    TAF_PS_CAUSE_SM_BEARER_TYPE_NOT_DEDICATED               = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 14),
    TAF_PS_CAUSE_SM_BEARER_INACTIVE                         = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 15),
    TAF_PS_CAUSE_SM_LINK_CID_INVALID                        = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 16),
    TAF_PS_CAUSE_SM_LINK_BEARER_INACTIVE                    = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 17),
    TAF_PS_CAUSE_SM_APN_LEN_ILLEGAL                         = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 18),
    TAF_PS_CAUSE_SM_APN_SYNTACTICAL_ERROR                   = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 19),
    TAF_PS_CAUSE_SM_AUTH_TYPE_ILLEGAL                       = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 20),
    TAF_PS_CAUSE_SM_USER_NAME_TOO_LONG                      = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 21),
    TAF_PS_CAUSE_SM_USER_PASSWORD_TOO_LONG                  = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 22),
    TAF_PS_CAUSE_SM_ACCESS_NUM_TOO_LONG                     = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 23),
    TAF_PS_CAUSE_SM_CALL_CID_IN_OPERATION                   = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 24),
    TAF_PS_CAUSE_SM_BEARER_TYPE_NOT_DEFAULT                 = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 25),
    TAF_PS_CAUSE_SM_BEARER_TYPE_ILLEGAL                     = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 26),
    TAF_PS_CAUSE_SM_MUST_EXIST_DEFAULT_TYPE_CID             = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 27),
    TAF_PS_CAUSE_SM_PDN_TYPE_ILLEGAL                        = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 28),
    TAF_PS_CAUSE_SM_IPV4_ADDR_ALLOC_TYPE_ILLEGAL            = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 29),
    TAF_PS_CAUSE_SM_SUSPENDED                               = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 30),
    TAF_PS_CAUSE_SM_MULTI_EMERGENCY_NOT_ALLOWED             = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 31),
    TAF_PS_CAUSE_SM_NON_EMERGENCY_NOT_ALLOWED               = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 32),
    TAF_PS_CAUSE_SM_MODIFY_EMERGENCY_NOT_ALLOWED            = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 33),
    TAF_PS_CAUSE_SM_DEDICATED_FOR_EMERGENCY_NOT_ALLOWED     = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 34),
    TAF_PS_CAUSE_SM_BACKOFF_ALG_NOT_ALLOWED                 = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 35),

    TAF_PS_CAUSE_SM_UNKNOWN                                 = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 127),

    /*----------------------------------------------------------------------
       TAF上报的SM网络原因值, 取值范围[0x0100, 0x01FF]
       由于3GPP协议已经定义了具体的(E)SM网络原因值, (E)SM上报的取值为协议
       定义的原因值加上偏移量(0x100)
       (1) SM Cause : Refer to TS 24.008 section 10.5.6.6
       (2) ESM Cause: Refer to TS 24.301 section 9.9.4.4
    *---------------------------------------------------------------------*/
    TAF_PS_CAUSE_SM_NW_OPERATOR_DETERMINED_BARRING          = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 8),
    TAF_PS_CAUSE_SM_NW_MBMS_BC_INSUFFICIENT                 = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 24),
    TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE                 = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 25),
    TAF_PS_CAUSE_SM_NW_INSUFFICIENT_RESOURCES               = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 26),
    TAF_PS_CAUSE_SM_NW_MISSING_OR_UKNOWN_APN                = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 27),
    TAF_PS_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE             = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 28),
    TAF_PS_CAUSE_SM_NW_USER_AUTHENTICATION_FAIL             = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 29),
    TAF_PS_CAUSE_SM_NW_ACTIVATION_REJECTED_BY_GGSN_SGW_OR_PGW = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 30),
    TAF_PS_CAUSE_SM_NW_ACTIVATION_REJECTED_UNSPECIFIED      = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 31),
    TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_NOT_SUPPORTED         = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 32),
    TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED     = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 33),
    TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER        = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 34),
    TAF_PS_CAUSE_SM_NW_NSAPI_ALREADY_USED                   = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 35),
    TAF_PS_CAUSE_SM_NW_REGULAR_DEACTIVATION                 = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 36),
    TAF_PS_CAUSE_SM_NW_QOS_NOT_ACCEPTED                     = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 37),
    TAF_PS_CAUSE_SM_NW_NETWORK_FAILURE                      = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 38),
    TAF_PS_CAUSE_SM_NW_REACTIVATION_REQUESTED               = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 39),
    TAF_PS_CAUSE_SM_NW_FEATURE_NOT_SUPPORT                  = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 40),
    TAF_PS_CAUSE_SM_NW_SEMANTIC_ERR_IN_TFT                  = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 41),
    TAF_PS_CAUSE_SM_NW_SYNTACTIC_ERR_IN_TFT                 = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 42),
    TAF_PS_CAUSE_SM_NW_UKNOWN_PDP_CONTEXT                   = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 43),
    TAF_PS_CAUSE_SM_NW_SEMANTIC_ERR_IN_PACKET_FILTER        = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 44),
    TAF_PS_CAUSE_SM_NW_SYNCTACTIC_ERR_IN_PACKET_FILTER      = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 45),
    TAF_PS_CAUSE_SM_NW_PDP_CONTEXT_WITHOUT_TFT_ACTIVATED    = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 46),
    TAF_PS_CAUSE_SM_NW_MULTICAST_GROUP_MEMBERHHSHIP_TIMEOUT = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 47),
    TAF_PS_CAUSE_SM_NW_REQUEST_REJECTED_BCM_VIOLATION       = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 48),
    TAF_PS_CAUSE_SM_NW_LAST_PDN_DISCONN_NOT_ALLOWED         = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 49),
    TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED           = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 50),
    TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED           = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 51),
    TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED     = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 52),
    TAF_PS_CAUSE_SM_NW_INFORMATION_NOT_RECEIVED             = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 53),
    TAF_PS_CAUSE_SM_NW_PDN_CONNECTION_DOES_NOT_EXIST        = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 54),
    TAF_PS_CAUSE_SM_NW_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 55),
    TAF_PS_CAUSE_SM_NW_COLLISION_WITH_NW_INITIATED_REQUEST  = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 56),
    TAF_PS_CAUSE_SM_NW_UNSUPPORTED_QCI_VALUE                = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 59),
    TAF_PS_CAUSE_SM_NW_BEARER_HANDLING_NOT_SUPPORTED        = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 60),
    TAF_PS_CAUSE_SM_NW_INVALID_TI                           = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 81),
    TAF_PS_CAUSE_SM_NW_SEMANTICALLY_INCORRECT_MESSAGE       = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 95),
    TAF_PS_CAUSE_SM_NW_INVALID_MANDATORY_INFO               = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 96),
    TAF_PS_CAUSE_SM_NW_MSG_TYPE_NON_EXISTENT                = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 97),
    TAF_PS_CAUSE_SM_NW_MSG_TYPE_NOT_COMPATIBLE              = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 98),
    TAF_PS_CAUSE_SM_NW_IE_NON_EXISTENT                      = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 99),
    TAF_PS_CAUSE_SM_NW_CONDITIONAL_IE_ERR                   = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 100),
    TAF_PS_CAUSE_SM_NW_MSG_NOT_COMPATIBLE                   = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 101),
    TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED             = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 111),
    TAF_PS_CAUSE_SM_NW_APN_RESTRICTION_INCOMPATIBLE         = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 112),

    /*----------------------------------------------------------------------
       TAF上报的GMM内部原因值, 取值范围[0x0200, 0x02FF]
    *---------------------------------------------------------------------*/
    TAF_PS_CAUSE_GMM_GPRS_NOT_SUPPORT                       = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 1),
    TAF_PS_CAUSE_GMM_FORBID_LA                              = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 2),
    TAF_PS_CAUSE_GMM_AUTHENTICATION_FAIL                    = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 3),
    TAF_PS_CAUSE_GMM_PS_DETACH                              = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 4),
    TAF_PS_CAUSE_GMM_ACCESS_BARRED                          = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 5),
    TAF_PS_CAUSE_GMM_NO_PDP_CONTEXT                         = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 6),
    TAF_PS_CAUSE_GMM_ATTACH_MAX_TIMES                       = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 7),
    TAF_PS_CAUSE_GMM_RRC_EST_FAIL                           = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 8),
    TAF_PS_CAUSE_GMM_T3310_EXPIRED                          = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 9),
    TAF_PS_CAUSE_GMM_T3317_EXPIRED                          = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 10),
    TAF_PS_CAUSE_GMM_TIMER_SIGNALING_PROTECT_EXPIRED        = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 11),
    TAF_PS_CAUSE_GMM_NULL                                   = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 12),
    TAF_PS_CAUSE_GMM_DETACH_NOT_REATTACH                    = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 13),
    TAF_PS_CAUSE_GMM_UNKNOWN                                = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 127),

    /*----------------------------------------------------------------------
       TAF上报的GMM网络原因值, 取值范围[0x0300, 0x03FF]
       由于3GPP协议已经定义了具体的GMM网络原因值, 平台上报的GMM网络原因值
       取值为协议定义的原因值加上偏移量(0x100)
       Gmm Cause: Refer to TS 24.008 section 10.5.5.14
    *---------------------------------------------------------------------*/
    TAF_PS_CAUSE_GMM_NW_IMSI_UNKNOWN_IN_HLR                 = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 2),
    TAF_PS_CAUSE_GMM_NW_ILLEGAL_MS                          = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 3),
    TAF_PS_CAUSE_GMM_NW_IMSI_NOT_ACCEPTED                   = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 5),
    TAF_PS_CAUSE_GMM_NW_ILLEGAL_ME                          = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 6),
    TAF_PS_CAUSE_GMM_NW_GPRS_SERV_NOT_ALLOW                 = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 7),
    TAF_PS_CAUSE_GMM_NW_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 8),
    TAF_PS_CAUSE_GMM_NW_MS_ID_NOT_DERIVED                   = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 9),
    TAF_PS_CAUSE_GMM_NW_IMPLICIT_DETACHED                   = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 10),
    TAF_PS_CAUSE_GMM_NW_PLMN_NOT_ALLOW                      = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 11),
    TAF_PS_CAUSE_GMM_NW_LA_NOT_ALLOW                        = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 12),
    TAF_PS_CAUSE_GMM_NW_ROAMING_NOT_ALLOW_IN_LA             = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 13),
    TAF_PS_CAUSE_GMM_NW_GPRS_SERV_NOT_ALLOW_IN_PLMN         = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 14),
    TAF_PS_CAUSE_GMM_NW_NO_SUITABL_CELL                     = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 15),
    TAF_PS_CAUSE_GMM_NW_MSC_UNREACHABLE                     = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 16),
    TAF_PS_CAUSE_GMM_NW_NETWORK_FAILURE                     = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 17),
    TAF_PS_CAUSE_GMM_NW_MAC_FAILURE                         = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 20),
    TAF_PS_CAUSE_GMM_NW_SYNCH_FAILURE                       = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 21),
    TAF_PS_CAUSE_GMM_NW_PROCEDURE_CONGESTION                = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 22),
    TAF_PS_CAUSE_GMM_NW_GSM_AUT_UNACCEPTABLE                = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 23),
    TAF_PS_CAUSE_GMM_NW_NOT_AUTHORIZED_FOR_THIS_CSG         = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 25),
    TAF_PS_CAUSE_GMM_NW_NO_PDP_CONTEXT_ACT                  = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 40),
    TAF_PS_CAUSE_GMM_NW_RETRY_UPON_ENTRY_CELL               = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 60),
    TAF_PS_CAUSE_GMM_NW_SEMANTICALLY_INCORRECT_MSG          = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 95),
    TAF_PS_CAUSE_GMM_NW_INVALID_MANDATORY_INF               = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 96),
    TAF_PS_CAUSE_GMM_NW_MSG_NONEXIST_NOTIMPLEMENTE          = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 97),
    TAF_PS_CAUSE_GMM_NW_MSG_TYPE_NOT_COMPATIBLE             = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 98),
    TAF_PS_CAUSE_GMM_NW_IE_NONEXIST_NOTIMPLEMENTED          = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 99),
    TAF_PS_CAUSE_GMM_NW_CONDITIONAL_IE_ERROR                = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 100),
    TAF_PS_CAUSE_GMM_NW_MSG_NOT_COMPATIBLE                  = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 101),
    TAF_PS_CAUSE_GMM_NW_PROTOCOL_ERROR                      = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 111),

    /*----------------------------------------------------------------------
       TAF上报的CDMA 1X网络原因值, 取值范围[0x400, 0x04FF]
       取值为协议定义的原因值加上偏移量(0x400)
    *---------------------------------------------------------------------*/
    TAF_PS_CAUSE_XCC_OTHER_SERVICE_IN_TCH                   = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 1),
    TAF_PS_CAUSE_XCC_CCS_NOT_SUPPORT                        = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 2),
    TAF_PS_CAUSE_XCC_CONNECT_ORDER_ACK_FAILURE              = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 3),
    TAF_PS_CAUSE_XCC_INCOMING_RSP_TIME_OUT                  = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 4),
    TAF_PS_CAUSE_XCC_L2_ACK_TIME_OUT                        = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 5),
    TAF_PS_CAUSE_XCC_POWER_DOWN_IND                         = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 6),
    TAF_PS_CAUSE_XCC_CONNID_NOT_FOUND                       = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 7),
    TAF_PS_CAUSE_XCC_ACCESS_CNF_TIMEOUT                     = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 8),
    TAF_PS_CAUSE_XCC_ACCESS_TCH_TIMEOUT                     = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 9),
    TAF_PS_CAUSE_XCC_T53M_TIME_OUT                          = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 10),
    TAF_PS_CAUSE_XCC_XCALL_HANGUP                           = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 11),
    TAF_PS_CAUSE_XCC_CALL_NOT_ALLOWED                       = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 12),
    TAF_PS_CAUSE_XCC_ABNORMAL_STATE                         = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 13),
    TAF_PS_CAUSE_XCC_ENCODE_FAIL                            = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 14),
    TAF_PS_CAUSE_XCC_WAIT_L2_ACK_CALL_RELEASE               = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 15),
    TAF_PS_CAUSE_XCC_CANNOT_FIND_CALL_INSTANCE              = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 16),
    TAF_PS_CAUSE_XCC_ABORTED_BY_RECEIVED_MO_CALL            = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 17),
    TAF_PS_CAUSE_XCC_ABORTED_BY_RECEIVED_MT_CALL            = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 18),
    TAF_PS_CAUSE_XCC_CAUSE_L2_ACK_FAIL                      = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 19),
    TAF_PS_CAUSE_XCC_CAUSE_ALLOC_SRID_FAIL                  = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 20),
    TAF_PS_CAUSE_XCC_CAUSE_NO_RF                            = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 21),
    TAF_PS_CAUSE_XCC_CAUSE_PROTOTAL_REV_NOT_SUPPORT         = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 22),
    TAF_PS_CAUSE_XCC_MT_SMS_IN_TCH                          = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 23),

    /*----------------------------------------------------------------------
       接入层上报原因值对应到PS域，取值范围[0x500, 0x05FF]
       由于3GPP2协议已经定义了具体的1X网络原因值, 平台上报的1X网络原因值
       取值为协议定义的原因值加上偏移量(0x500)
    *---------------------------------------------------------------------*/
    TAF_PS_CAUSE_XCC_AS_NO_SERVICE                          = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 1),
    TAF_PS_CAUSE_XCC_AS_MAX_ACCESS_PROBES                   = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 2),
    TAF_PS_CAUSE_XCC_AS_REORDER                             = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 3),
    TAF_PS_CAUSE_XCC_AS_INTERCEPT                           = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 4),
    TAF_PS_CAUSE_XCC_AS_ACCESS_DENIED                       = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 5),
    TAF_PS_CAUSE_XCC_AS_LOCK                                = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 6),
    TAF_PS_CAUSE_XCC_AS_ACCT_BLOCK                          = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 7),
    TAF_PS_CAUSE_XCC_AS_NDSS                                = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 8),
    TAF_PS_CAUSE_XCC_AS_REDIRECTION                         = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 9),
    TAF_PS_CAUSE_XCC_AS_ACCESS_IN_PROGRESS                  = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 10),
    TAF_PS_CAUSE_XCC_AS_ACCESS_FAIL                         = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 11),
    TAF_PS_CAUSE_XCC_AS_ABORT                               = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 12),
    TAF_PS_CAUSE_XCC_AS_SIGNAL_FADE_IN_ACH                  = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 13),
    TAF_PS_CAUSE_XCC_AS_CHANNEL_ASSIGN_TIMEOUT              = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 14),
    TAF_PS_CAUSE_XCC_AS_BS_RELEASE                          = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 15),
    TAF_PS_CAUSE_XCC_AS_NOT_ACCEPT_BY_BS                    = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 16),
    TAF_PS_CAUSE_XCC_AS_SO_REJ                              = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 17),
    TAF_PS_CAUSE_XCC_AS_RELEASE_TIME_OUT                    = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 18),
    TAF_PS_CAUSE_XCC_AS_MS_NORMAL_RELEASE                   = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 19),
    TAF_PS_CAUSE_XCC_AS_RETRY_FAIL                          = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 20),
    TAF_PS_CAUSE_XCC_AS_NW_NORMAL_RELEASE                   = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 21),
    TAF_PS_CAUSE_XCC_AS_SIGNAL_FADE_IN_TCH                  = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 22),

    TAF_PS_CAUSE_HSM_AS_CONN_FAIL                           = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 1),
    TAF_PS_CAUSE_HSM_AS_MAX_ACCESS_PROBES                   = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 2),
    TAF_PS_CAUSE_HSM_AS_CONNECTION_DENY                     = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 3),
    TAF_PS_CAUSE_HSM_AS_RTC_RTCACK_FAILURE                  = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 4),
    TAF_PS_CAUSE_HSM_AS_SIGNAL_FADE                         = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 5),
    TAF_PS_CAUSE_HSM_AS_SESSION_NOT_EXIST                   = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 6),
    TAF_PS_CAUSE_HSM_AS_CAN_NOT_EST_CONN                    = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 7),
    TAF_PS_CAUSE_HSM_AS_TIMEOUT                             = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 8),
    TAF_PS_CAUSE_HSM_AS_HRPD_SLAVE                          = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 9),
    TAF_PS_CAUSE_HSM_AS_HANDOFF_FAIL                        = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 10),
    TAF_PS_CAUSE_HSM_AS_IN_UATI_PROCEDURE                   = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 11),
    TAF_PS_CAUSE_HSM_AS_IN_SCP_PROCEDURE                    = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 12),
    TAF_PS_CAUSE_HSM_AS_CONNECTION_EXIST                    = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 13),
    TAF_PS_CAUSE_HSM_AS_NO_RF                               = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 14),
    TAF_PS_CAUSE_HSM_AS_REDIRECT                            = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 15),
    TAF_PS_CAUSE_HSM_AS_HRPD_HANDOFF_TO_1X                  = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 16),

    TAF_PS_CAUSE_HSM_AS_HRPD_PREFER_CH_NOT_VALID            = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 17),

    TAF_PS_CAUSE_EHSM_CTTF_NOT_SUPPORT_EHRPD                = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 1),
    TAF_PS_CAUSE_EHSM_NOT_SUPPORT_EHRPD                     = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 2),
    TAF_PS_CAUSE_EHSM_IN_SUSPEND                            = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 3),
    TAF_PS_CAUSE_EHSM_LAST_PDN                              = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 4),
    TAF_PS_CAUSE_EHSM_CONN_EST_FAIL                         = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 5),
    TAF_PS_CAUSE_EHSM_POWER_OFF                             = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 6),
    TAF_PS_CAUSE_EHSM_INVALID_PDN_ID                        = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 7),
    TAF_PS_CAUSE_EHSM_PPP_DETACH                            = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 8),
    TAF_PS_CAUSE_EHSM_HSM_CONN_FAIL                         = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 9),
    TAF_PS_CAUSE_EHSM_HSM_MAX_ACCESS_PROBES                 = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 10),
    TAF_PS_CAUSE_EHSM_HSM_CONN_DENY                         = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 11),
    TAF_PS_CAUSE_EHSM_HSM_RTCACK_RAILURE                    = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 12),
    TAF_PS_CAUSE_EHSM_HSM_SIGNAL_FADE                       = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 13),
    TAF_PS_CAUSE_EHSM_HSM_CAN_NOT_EST_CONN                  = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 14),
    TAF_PS_CAUSE_EHSM_HSM_TIME_OUT                          = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 15),
    TAF_PS_CAUSE_EHSM_HSM_HRPD_SLAVE                        = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 16),
    TAF_PS_CAUSE_EHSM_HSM_SESSION_NOT_EXSIT                 = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 17),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_GENERAL_ERROR               = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 18),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_UNAUTHORIZED_APN            = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 19),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_PDN_LIMIT_EXCEEDED          = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 20),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_NO_PGW_AVAILABLE            = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 21),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_PGW_UNREACHABLE             = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 22),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_PGW_REJECT                  = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 23),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_INSUFFICIENT_PARAMETERS     = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 24),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_RESOURCE_UNAVAILABLE        = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 25),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_ADMIN_PROHIBITED            = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 26),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_PDNID_ALREADY_IN_USE        = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 27),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_SUBSCRIPTION_LIMITATION     = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 28),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_PDN_CONNECTION_ALREADY_EXISTS_FOR_THIS_APN      = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 29),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_EMERGENCY_SERVICES_NOT_SUPPORTED                = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 30),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_RECONNECT_TO_THIS_APN_NOT_ALLOWED               = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 31),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_LCP_EAP_FAILURE             = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 32),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_LCP_OTHER_FAILURE           = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 33),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_TIME_OUT                    = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 34),
    TAF_PS_CAUSE_EHSM_NW_DISC_IND                           = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 35),
    TAF_PS_CAUSE_EHSM_HSM_RSLT_IN_UATI_PROCEDURE            = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 36),
    TAF_PS_CAUSE_EHSM_HSM_RSLT_IN_SCP_PROCEDURE             = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 37),
    TAF_PS_CAUSE_EHSM_HSM_NO_RF                             = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 38),
    TAF_PS_CAUSE_EHSM_HSM_REDIRECT                          = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 39),

    TAF_PS_CAUSE_BUTT                                       = 0xFFFFFFFF
};
typedef VOS_UINT32 TAF_PS_CAUSE_ENUM_UINT32;

/** ****************************************************************************
 * Name        : TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum TAF_PS_CDATA_BEAR_STATUS_ENUM
{
    TAF_PS_CDATA_BEAR_STATUS_INACTIVE     = 0x00,
    TAF_PS_CDATA_BEAR_STATUS_IDLE         = 0x01,
    TAF_PS_CDATA_BEAR_STATUS_ACTIVE       = 0x02,
    TAF_PS_CDATA_BEAR_STATUS_SUSPEND      = 0x03,
    TAF_PS_CDATA_BEAR_STATUS_BUTT         = 0x04
};
typedef VOS_UINT8 TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8;


/*****************************************************************************
 枚举名称: TAF_PDP_TYPE_ENUM
 枚举说明: PDP类型

 修改历史      :
  1.日    期   : 2011年10月19日
    作    者   : A00165503
    修改内容   : 新增枚举
*****************************************************************************/
enum TAF_PDP_TYPE_ENUM
{
    TAF_PDP_IPV4                        = 0x01,
    TAF_PDP_IPV6                        = 0x02,
    TAF_PDP_IPV4V6                      = 0x03,
    TAF_PDP_PPP                         = 0x04,

    TAF_PDP_TYPE_BUTT                   = 0xFF
};
typedef VOS_UINT8 TAF_PDP_TYPE_ENUM_UINT8;


/*****************************************************************************
 枚举名称: TAF_PDP_AUTH_TYPE_ENUM
 枚举说明: 鉴权类型

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增枚举

  2.日    期   : 2015年12月9日
    作    者   : y00322978
    修改内容   : 枚举值修改
*****************************************************************************/
enum TAF_PDP_AUTH_TYPE_ENUM
{
    TAF_PDP_AUTH_TYPE_NONE              = 0x00,
    TAF_PDP_AUTH_TYPE_PAP               = 0x01,
    TAF_PDP_AUTH_TYPE_CHAP              = 0x02,

    TAF_PDP_AUTH_TYPE_PAP_OR_CHAP       = 0x03,

    TAF_PDP_AUTH_TYPE_BUTT
};
typedef VOS_UINT8 TAF_PDP_AUTH_TYPE_ENUM_UINT8;


/*****************************************************************************
 枚举名称: TAF_AUTH_TYPE_ENUM
 枚举说明: PDP激活时鉴权标志
 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增枚举
*****************************************************************************/
enum TAF_AUTH_TYPE_ENUM
{
    TAF_PDP_ACTIVATE_NO_AUTH            = 0x00,                                 /*PDP激活时不需要鉴权用户*/
    TAF_PDP_ACTIVATE_AUTH               = 0x01,                                 /*PDP激活时需要鉴权用户*/

    TAF_AUTH_BUTT                       = 0xFF
};
typedef VOS_UINT8 TAF_AUTH_TYPE_ENUM_UINT8;


/*****************************************************************************
 枚举名称: TAF_PDP_ACTIVE_STATUS_ENUM
 枚举说明: PDP激活/未激活标志
 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增枚举
*****************************************************************************/
enum TAF_PDP_ACTIVE_STATUS_ENUM
{
    TAF_PDP_INACTIVE                    = 0x00,                                 /*PDP未激活*/
    TAF_PDP_ACTIVE                      = 0x01,                                 /*PDP已激活*/

    TAF_PDP_ACTIVE_BUTT                 = 0xFF
};
typedef VOS_UINT8 TAF_PDP_ACTIVE_STATUS_ENUM_UINT8;


/*****************************************************************************
 枚举名称: TAF_GPRS_ACTIVE_TYPE_ENUM
 枚举说明: D命令GPRS激活类型

 修改历史      :
  1.日    期   : 2011年10月19日
    作    者   : A00165503
    修改内容   : 新增枚举
*****************************************************************************/
enum TAF_GPRS_ACTIVE_TYPE_ENUM
{
    TAF_IP_ACTIVE_TE_PPP_MT_PPP_TYPE            = 0x00,
    TAF_PPP_ACTIVE_TE_PPP_MT_NOT_PPP_TYPE       = 0x01,
    TAF_IP_ACTIVE_TE_NOT_PPP_MT_NOT_PPP_TYPE    = 0x02,

    TAF_IP_ACTIVE_TE_BUTT
};
typedef VOS_UINT8 TAF_GPRS_ACTIVE_TYPE_UINT8;


/*****************************************************************************
 结构名称: TAF_L2P_TYPE_ENUM
 结构说明: L2P类型

 修改历史      :
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
enum TAF_L2P_TYPE_ENUM
{
    TAF_L2P_PPP                         = 0x00,
    TAF_L2P_NULL                        = 0x01,

    TAF_L2P_BUTT
};
typedef VOS_UINT8 TAF_L2P_TYPE_ENUM_UINT8;


/*****************************************************************************
 枚举名称: TAF_PDP_H_COMP_ENUM
 枚举说明: PDP header compression type

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增枚举
*****************************************************************************/
enum TAF_PDP_H_COMP_ENUM
{
    TAF_PDP_H_COMP_OFF                  = 0x00,             /* default if value is omitted */
    TAF_PDP_H_COMP_ON                   = 0x01,             /* manufacturer preferred compression */
    TAF_PDP_H_COMP_RFC1144              = 0x02,             /* RFC 1144 */
    TAF_PDP_H_COMP_RFC2507              = 0x03,             /* RFC 2507 */

    TAF_PDP_H_COMP_BUTT                 = 0xFF
};
typedef VOS_UINT8 TAF_PDP_H_COMP_ENUM_UINT8;


/*****************************************************************************
 枚举名称: TAF_PDP_D_COMP_ENUM
 枚举说明: PDP data compression type, refer to TS 44.065 (section 6.6.1.1.4)
 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增枚举
*****************************************************************************/
enum TAF_PDP_D_COMP_ENUM
{
    TAF_PDP_D_COMP_OFF                  = 0x00,             /* default if value is omitted */
    TAF_PDP_D_COMP_ON                   = 0x01,             /* manufacturer preferred compression */
    TAF_PDP_D_COMP_V42                  = 0x02,             /* V.42 compression */

    TAF_PDP_D_COMP_BUTT                 = 0xFF
};
typedef VOS_UINT8 TAF_PDP_D_COMP_ENUM_UINT8;


/*****************************************************************************
 枚举名称: TAF_UMTS_QOS_TRAFFIC_CLASS_ENUM
 枚举说明: QOS Traffic Class

 修改历史      :
  1.日    期   : 2011年10月19日
    作    者   : A00165503
    修改内容   : 新增枚举
*****************************************************************************/
enum TAF_UMTS_QOS_TRAFFIC_CLASS_ENUM
{
    TAF_UMTS_QOS_TRAFFIC_CLASS_SUBS     = 0x00,                                 /* Subscribed                  */
    TAF_UMTS_QOS_TRAFFIC_CLASS_CONV     = 0x01,                                 /* Conversational              */
    TAF_UMTS_QOS_TRAFFIC_CLASS_STRM     = 0x02,                                 /* Streaming                   */
    TAF_UMTS_QOS_TRAFFIC_CLASS_INTR     = 0x03,                                 /* Interactive                 */
    TAF_UMTS_QOS_TRAFFIC_CLASS_BACK     = 0x04,                                 /* Background                  */
    TAF_UMTS_QOS_TRAFFIC_CLASS_BUTT     = 0xff                                  /* force max to 0xff so that
                                                                                    enum is defined as a byte   */
};
typedef VOS_UINT8 TAF_UMTS_QOS_TRAFFIC_CLASS_ENUM_UINT8;


/*****************************************************************************
 结构名称: TAF_PF_TRANS_DIRECTION_ENUM
 结构说明: TFT过滤器方向
 1.日    期   : 2011年12月18日
   作    者   : l00198894
   修改内容   : Added for PS融合
*****************************************************************************/
enum TAF_PF_TRANS_DIRECTION_ENUM
{
    TAF_PF_TRANS_DIRECTION_PRE_REL7     = 0x00,             /* 0 - Pre-Release 7 TFT filter (see 3GPP TS 24.008 [8], table 10.5.162) */
    TAF_PF_TRANS_DIRECTION_UPLINK       = 0x01,             /* 1 - Uplink */
    TAF_PF_TRANS_DIRECTION_DOWNLINK     = 0x02,             /* 2 - Downlink */
    TAF_PF_TRANS_DIRECTION_BIDIRECTION  = 0x03,             /* 3 - Birectional (Up & Downlink) (default if omitted) */

    TAF_PF_TRANS_DIRECTION_BUTT         = 0xFF
};
typedef VOS_UINT8 TAF_PF_TRANS_DIRECTION_ENUM_UINT8;


/*****************************************************************************
 结构名    : TAF_DSFLOW_CLEAR_MODE_ENUM
 结构说明  : DS FLOW流量清除模式定义
 1.日    期   : 2011年12月14日
   作    者   : 欧阳飞 00132663
   修改内容   : 新建
*****************************************************************************/
enum TAF_DSFLOW_CLEAR_MODE_ENUM
{
    TAF_DSFLOW_CLEAR_TOTAL              = 1,   /*清零所有RABID的流量*/
    TAF_DSFLOW_CLEAR_WITH_RABID,               /*清零指定RABID的流量*/

    TAF_DSFLOW_CLEAR_BUTT
};
typedef VOS_UINT8 TAF_DSFLOW_CLEAR_MODE_ENUM_UINT8;


/*****************************************************************************
 枚举名称: TAF_PDP_EMC_IND_ENUM
 枚举说明: PDP上下文是否为紧急呼
 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增枚举
*****************************************************************************/
enum TAF_PDP_EMC_IND_ENUM
{
    TAF_PDP_NOT_FOR_EMC                 = 0x00,
    TAF_PDP_FOR_EMC                     = 0x01,

    TAF_PDP_EMC_IND_BUTT                = 0xFF
};
typedef VOS_UINT8 TAF_PDP_EMC_IND_ENUM_UINT8;


/*****************************************************************************
 枚举名称: TAF_PDP_IPV4_ADDR_ALLOC_TYPE_ENUM
 枚举说明: IPV4类型地址分配类型
 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增枚举
*****************************************************************************/
enum TAF_PDP_IPV4_ADDR_ALLOC_TYPE_ENUM
{
    TAF_PDP_IPV4_ADDR_ALLOC_TYPE_NAS    = 0x00,
    TAF_PDP_IPV4_ADDR_ALLOC_TYPE_DHCP   = 0x01,

    TAF_PDP_IPV4_ADDR_ALLOC_BUTT        = 0xFF
};
typedef VOS_UINT8 TAF_PDP_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT8;


/*****************************************************************************
 枚举名  : TAF_PDP_PCSCF_DISCOVERY_ENUM
 枚举说明: P-CSCF DISCOVERY

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增枚举
*****************************************************************************/
enum TAF_PDP_PCSCF_DISCOVERY_ENUM
{
    TAF_PDP_PCSCF_DISCOVERY_NOT_INFLUENCED  = 0x00,
    TAF_PDP_PCSCF_DISCOVERY_THROUGH_NAS_SIG = 0x01,
    TAF_PDP_PCSCF_DISCOVERY_THROUGH_DHCP    = 0x02,

    TAF_PDP_PCSCF_DISCOVERY_BUTT            = 0xFF
};
typedef VOS_UINT8 TAF_PDP_PCSCF_DISCOVERY_ENUM_UINT8;


/*****************************************************************************
 枚举名  : TAF_PDP_IM_CN_SIG_FLAG_ENUM
 枚举说明: IMS专有承载标志

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增枚举
*****************************************************************************/
enum TAF_PDP_IM_CN_SIG_FLAG_ENUM
{
    TAF_PDP_NOT_FOR_IMS_CN_SIG_ONLY     = 0x00,
    TAF_PDP_FOR_IM_CN_SIG_ONLY          = 0x01,

    TAF_PDP_IM_CN_SIG_FLAG_BUTT         = 0xFF
};
typedef VOS_UINT8 TAF_PDP_IM_CN_SIG_FLAG_ENUM_UINT8;


/*****************************************************************************
 枚举名称: TAF_PDP_ANSWER_TYPE_ENUM
 枚举说明: 应答类型

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增枚举
*****************************************************************************/
enum TAF_PDP_ANSWER_TYPE_ENUM
{
    TAF_PDP_ANSWER_TYPE_ACCEPT             = 0x00,             /* 接受呼叫 */
    TAF_PDP_ANSWER_TYPE_REJECT             = 0x01,             /* 拒绝呼叫 */

    TAF_PDP_ANSWER_TYPE_BUTT
};
typedef VOS_UINT8 TAF_PDP_ANSWER_TYPE_ENUM_UINT8;


/*****************************************************************************
 枚举名称: TAF_PDP_ANSWER_MODE_ENUM
 枚举说明: 应答模式

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增枚举
*****************************************************************************/
enum TAF_PDP_ANSWER_MODE_ENUM
{
    TAF_PDP_ANSWER_MODE_MANUAL             = 0x00,             /* 人工应答方式 */
    TAF_PDP_ANSWER_MODE_AUTO               = 0x01,             /* 自动应答方式 */

    TAF_PDP_ANSWER_MODE_BUTT
};
typedef VOS_UINT8 TAF_PDP_ANSWER_MODE_ENUM_UINT8;

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 结构名称: TAF_SRVCC_CANCEL_NOTIFY_ENUM
 结构说明: APS->IMSA通知SRVCC CANECL
*****************************************************************************/
enum TAF_SRVCC_CANCEL_NOTIFY_ENUM
{
    TAF_SRVCC_CANCEL_NOTIFY_HO_CANCELLED    = 0,

    TAF_SRVCC_CANCEL_NOTIFY_IND_BUTT
};
typedef VOS_UINT32 TAF_SRVCC_CANCEL_NOTIFY_ENUM_UINT32;

#endif

/* Added by l60609 for L-C互操作项目, 2014-01-06, Begin */
/*****************************************************************************
 枚举名   :TAF_PDP_REQUEST_TYPE_ENUM_UINT8
 枚举说明 :PDN连接请求类型
 1.日    期   : 2014年01月08日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
enum TAF_PDP_REQUEST_TYPE_ENUM
{
    TAF_PDP_REQUEST_TYPE_INITIAL        = 0x1,
    TAF_PDP_REQUEST_TYPE_HANDOVER       = 0x2,
    TAF_PDP_REQUEST_TYPE_UNUSED         = 0x3,
    TAF_PDP_REQUEST_TYPE_EMERGENCY      = 0x4,
    TAF_PDP_REQUEST_TYPE_BUTT
};
typedef VOS_UINT8 TAF_PDP_REQUEST_TYPE_ENUM_UINT8;
/* Added by l60609 for L-C互操作项目, 2014-01-06, End */

/** ****************************************************************************
 * Name        : TAF_PS_CDATA_1X_QOS_NON_ASSURED_PRI_ENUM_UINT8
 *
 * Description : User Priority Adjustment Values
 * Refer to  C.S0017-012-A_v2.0_060522 2.2.8 Table 15
 *******************************************************************************/
enum TAF_PS_CDATA_1X_QOS_NON_ASSURED_PRI_ENUM
{
    TAF_PS_CDATA_1X_QOS_DESIRED_NON_ASSURED_PRI_MIN         = 0x00, /**< min value */
    TAF_PS_CDATA_1X_QOS_DESIRED_NON_ASSURED_PRI_DEFAULT     = 0x0D, /**< default value */
    TAF_PS_CDATA_1X_QOS_DESIRED_NON_ASSURED_PRI_MAX         = 0x0F, /**< max value */
    TAF_PS_CDATA_1X_QOS_NON_ASSURED_PRI_BUTT                = 0x10
};
typedef VOS_UINT8 TAF_PS_CDATA_1X_QOS_NON_ASSURED_PRI_ENUM_UINT8;


/*****************************************************************************
 枚举名    : TAF_PS_CDATA_DIAL_MODE_ENUM_UINT32
 结构说明  : 当前的接入技术
 1.日    期   : 2015年04月02日
   作    者   : y00314741
   修改内容   : 新建
*****************************************************************************/
enum TAF_PS_CDATA_DIAL_MODE_ENUM
{
    TAF_PS_CDATA_DIAL_MODE_ASYNC_CALL   = 0x00,
    TAF_PS_CDATA_DIAL_MODE_RELAY        = 0x01,                                 /* 数据传输模式中继模式 */
    TAF_PS_CDATA_DIAL_MODE_NETWORK      = 0x02,                                 /* 数据传输模式网络模式  */
    TAF_PS_CDATA_DIAL_MODE_BUTT
};
typedef VOS_UINT32 TAF_PS_CDATA_DIAL_MODE_ENUM_UINT32;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 枚举名    : TAF_APS_READ_SIM_FILES_CNF_ENUM
 结构说明  : 用于标记读取USIM文件的回复消息
1.日    期   : 2015年11月30日
  作    者   : Y00322978
  修改内容   : AT&T 支持EONS特性修改

*****************************************************************************/
enum  TAF_APS_READ_SIM_FILES_CNF_ENUM
{
    TAF_APS_READ_USIM_FILE_FLG_NULL                         = 0x0,

    TAF_APS_READ_USIMM_CDMA_EFSIPCAP_ID_FLG                 = 0x1,
    TAF_APS_READ_USIMM_CDMA_EFSIPUPP_ID_FLG                 = 0x2,
    TAF_APS_READ_USIMM_CDMA_EFSIPSP_ID_FLG                  = 0x4,
    TAF_APS_READ_USIMM_CDMA_EFSIPPAPSS_ID_FLG               = 0x8,


    TAF_APS_READ_USIMM_CSIM_EFSIPCAP_ID_FLG                 = 0x10,
    TAF_APS_READ_USIMM_CSIM_EFSIPUPP_ID_FLG                 = 0x20,
    TAF_APS_READ_USIMM_CSIM_EFSIPSP_ID_FLG                  = 0x40,
    TAF_APS_READ_USIMM_CSIM_EFSIPPAPSS_ID_FLG               = 0x80,


    TAF_APS_READ_USIM_FILE_CNF_BUTT
};

typedef VOS_UINT32 TAF_APS_READ_SIM_FILES_CNF_ENUM_UINT32;
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

/*****************************************************************************
 结构名称: TAF_PS_EVT_STRU
 结构说明: PS域事件结构

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stHeader;
    VOS_UINT32                          ulEvtId;
    VOS_UINT8                           aucContent[4];

} TAF_PS_EVT_STRU;


/*****************************************************************************
 结构名    : TAF_DSFLOW_INFO_STRU
 结构说明  : DS FLOW连接流量信息结构体定义
 1.日    期   : 2011年12月14日
   作    者   : 欧阳飞 00132663
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDSLinkTime;                           /* DS连接时间 */
    VOS_UINT32                          ulDSSendFluxLow;                        /* DS发送流量低四个字节 */
    VOS_UINT32                          ulDSSendFluxHigh;                       /* DS发送流量高四个字节 */
    VOS_UINT32                          ulDSReceiveFluxLow;                     /* DS接收流量低四个字节 */
    VOS_UINT32                          ulDSReceiveFluxHigh;                    /* DS接收流量高四个字节 */

} TAF_DSFLOW_INFO_STRU;


/*****************************************************************************
 结构名    : TAF_DSFLOW_REPORT_STRU
 结构说明  : 流量信息上报结构定义
 1.日    期   : 2011年12月17日
   作    者   : 欧阳飞 00132663
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCurrentSendRate;                      /*当前发送速率*/
    VOS_UINT32                          ulCurrentReceiveRate;                   /*当前接收速率*/
    VOS_UINT32                          ulQosSendRate;                          /*QOS协商发送速率*/
    VOS_UINT32                          ulQosReceiveRate;                       /*QOS协商接收速率*/
    TAF_DSFLOW_INFO_STRU                stCurrentFlowInfo;                      /*当前连接流量信息*/

} TAF_DSFLOW_REPORT_STRU;


/*****************************************************************************
 结构名    : TAF_DSFLOW_QUERY_INFO_STRU
 结构说明  : DS FLOW 流量查询结构体
 1.日    期   : 2011年12月14日
   作    者   : 欧阳飞 00132663
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_DSFLOW_INFO_STRU                stCurrentFlowInfo;  /*当前连接流量信息*/
    TAF_DSFLOW_INFO_STRU                stTotalFlowInfo;    /*累计流量信息*/

} TAF_DSFLOW_QUERY_INFO_STRU;


/*****************************************************************************
 结构名    : TAF_EPS_QOS_STRU
 结构说明  : EPS QOS 参数结构, 仅提供给LTE使用
 修改记录  :
 1.日    期   : 2012年01月04日
   作    者   : l00198894
   修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    /* 0 QCI is selected by network
       [1 - 4]value range for guranteed bit rate Traffic Flows
       [5 - 9]value range for non-guarenteed bit rate Traffic Flows */
    VOS_UINT8                           ucQCI;

    VOS_UINT8                           aucReserved[3];

    /* DL GBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulDLGBR;

    /* UL GBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulULGBR;

    /* DL MBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulDLMBR;

    /* UL MBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulULMBR;

}TAF_EPS_QOS_STRU;


/*****************************************************************************
 结构名    : TAF_PDP_AUTH_STRU
 结构说明  : 鉴权参数结构
 修改记录  :
 1.日    期   : 2012年01月04日
   作    者   : l00198894
   修改内容   : PS Project，4字节对齐, 扩展用户名, 密码最大长度为255
*****************************************************************************/
typedef struct
{
    TAF_AUTH_TYPE_ENUM_UINT8            enAuth;                                   /*目前仅支持是否鉴权，以后扩充为支持哪种鉴权算法*/

    VOS_UINT8                           aucReserved[3];

    /* aucUserName[0]放置用户名长度 */
    VOS_UINT8                           aucUserName[TAF_MAX_PDP_AUTH_USERNAME_LEN + 1];

    /* aucPassword[0]放置密码长度 */
    VOS_UINT8                           aucPassword[TAF_MAX_PDP_AUTH_PASSCODE_LEN + 1];

} TAF_PDP_AUTH_STRU;


/*****************************************************************************
 结构名称: TAF_PDP_APN_STRU
 结构说明: PDP上下文中APN信息

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLength;
    VOS_UINT8                           aucValue[TAF_MAX_APN_LEN];

} TAF_PDP_APN_STRU;


/*****************************************************************************
 结构名称: TAF_PDP_DNS_STRU
 结构说明: DNS信息

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPrimDnsAddr    : 1;
    VOS_UINT32                          bitOpSecDnsAddr     : 1;
    VOS_UINT32                          bitOpSpare          : 30;

    VOS_UINT8                           aucPrimDnsAddr[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecDnsAddr[TAF_IPV4_ADDR_LEN];

} TAF_PDP_DNS_STRU;


/*****************************************************************************
 结构名称: TAF_PDP_NBNS_STRU
 结构说明: NBNS信息

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPrimNbnsAddr   : 1;
    VOS_UINT32                          bitOpSecNbnsAddr    : 1;
    VOS_UINT32                          bitOpSpare          : 30;

    VOS_UINT8                           aucPrimNbnsAddr[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecNbnsAddr[TAF_IPV4_ADDR_LEN];

} TAF_PDP_NBNS_STRU;


/*****************************************************************************
 结构名称: TAF_PDP_GATEWAY_STRU
 结构说明: 网关地址结构

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpGateWayAddr    : 1;
    VOS_UINT32                          bitOpSpare          : 31;

    VOS_UINT8                           aucGateWayAddr[TAF_IPV4_ADDR_LEN];

} TAF_PDP_GATEWAY_STRU;


/*****************************************************************************
 结构名称: TAF_PDP_PCSCF_STRU
 结构说明: P-CSCF地址结构

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPrimPcscfAddr  : 1;
    VOS_UINT32                          bitOpSecPcscfAddr   : 1;
    VOS_UINT32                          bitOpThiPcscfAddr   : 1;
    VOS_UINT32                          bitOpSpare          : 29;

    VOS_UINT8                           aucPrimPcscfAddr[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecPcscfAddr[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucThiPcscfAddr[TAF_IPV4_ADDR_LEN];

} TAF_PDP_PCSCF_STRU;


/*****************************************************************************
 结构名称: TAF_PDP_IPV6_PCSCF_STRU
 结构说明: IPv6 P-CSCF地址结构体

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPrimPcscfAddr  : 1;
    VOS_UINT32                          bitOpSecPcscfAddr   : 1;
    VOS_UINT32                          bitOpThiPcscfAddr   : 1;
    VOS_UINT32                          bitOpSpare          : 29;

    VOS_UINT8                           aucPrimPcscfAddr[TAF_IPV6_ADDR_LEN];
    VOS_UINT8                           aucSecPcscfAddr[TAF_IPV6_ADDR_LEN];
    VOS_UINT8                           aucThiPcscfAddr[TAF_IPV6_ADDR_LEN];

} TAF_PDP_IPV6_PCSCF_STRU;


/*****************************************************************************
 结构名称: TAF_PDP_IPV6_DNS_STRU
 结构说明: IPv6 DNS地址结构

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPrimDnsAddr    : 1;
    VOS_UINT32                          bitOpSecDnsAddr     : 1;
    VOS_UINT32                          bitOpSpare          : 30;

    VOS_UINT8                           aucPrimDnsAddr[TAF_IPV6_ADDR_LEN];
    VOS_UINT8                           aucSecDnsAddr[TAF_IPV6_ADDR_LEN];

} TAF_PDP_IPV6_DNS_STRU;


/*****************************************************************************
 结构名称: TAF_PDP_ADDR_STRU
 结构说明: IP地址结构

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    /* IPV4:1, IPV6:2, IPV4V6:3, PPP:4 */
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucIpv4Addr[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucIpv6Addr[TAF_IPV6_ADDR_LEN];
} TAF_PDP_ADDR_STRU;


/*****************************************************************************
 结构名    : TAF_PDP_PRIM_CONTEXT_STRU
 结构说明  : 主PDP上下文结构
 修改记录  :
 1.日    期   : 2012年01月04日
   作    者   : l00198894
   修改内容   : PS Project，确保4字节对齐
*****************************************************************************/
typedef struct
{
    TAF_PDP_ADDR_STRU                   stPdpAddr;
    TAF_PDP_APN_STRU                    stApn;
    TAF_PDP_D_COMP_ENUM_UINT8           enPdpDcomp;
    TAF_PDP_H_COMP_ENUM_UINT8           enPdpHcomp;

    /* 0 - IPv4 Address Allocation through NAS Signaling (default if omitted)
       1 - IPv4 Address Allocated through DHCP */
    TAF_PDP_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT8 enIpv4AddrAlloc;

    /* 0 - PDP context is not for emergency bearer services
       1 - PDP context is for emergency bearer services */
    TAF_PDP_EMC_IND_ENUM_UINT8          enEmergencyInd;

    TAF_PDP_PCSCF_DISCOVERY_ENUM_UINT8  enPcscfDiscovery;

    TAF_PDP_IM_CN_SIG_FLAG_ENUM_UINT8   enImCnSignalFlg;

    VOS_UINT8                           aucReserved2[2];

}TAF_PDP_PRIM_CONTEXT_STRU;

/*****************************************************************************
 结构名称: TAF_PDP_AUTHDATA_STRU
 结构说明: NDIS鉴权参数结构

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_PDP_AUTH_TYPE_ENUM_UINT8        enAuthType;
    VOS_UINT8                           aucPlmn[TAF_MAX_AUTHDATA_PLMN_LEN + 1];
    VOS_UINT8                           aucPassword[TAF_MAX_AUTHDATA_PASSWORD_LEN + 1];
    VOS_UINT8                           aucUsername[TAF_MAX_AUTHDATA_USERNAME_LEN + 1];
}TAF_PDP_AUTHDATA_STRU;


/*****************************************************************************
 结构名    : TAF_PDP_PF_STRU
 结构说明  : TFT参数结构表
 修改记录  :
 1.日    期   : 2012年01月04日
   作    者   : l00198894
   修改内容   : PS Project, 调整为与LTE的TFT表结构一致
 2.日    期   : 2015年9月28日
   作    者   : W00316404
   修改内容   : R11 TFT 协议升级
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpRmtIpv4AddrAndMask     : 1;
    VOS_UINT32                          bitOpRmtIpv6AddrAndMask     : 1;
    VOS_UINT32                          bitOpProtocolId             : 1;
    VOS_UINT32                          bitOpSingleLocalPort        : 1;
    VOS_UINT32                          bitOpLocalPortRange         : 1;
    VOS_UINT32                          bitOpSingleRemotePort       : 1;
    VOS_UINT32                          bitOpRemotePortRange        : 1;
    VOS_UINT32                          bitOpSecuParaIndex          : 1;
    VOS_UINT32                          bitOpTypeOfService          : 1;
    VOS_UINT32                          bitOpFlowLabelType          : 1;
    VOS_UINT32                          bitOpLocalIpv4AddrAndMask   : 1;
    VOS_UINT32                          bitOpLocalIpv6AddrAndMask   : 1;
    VOS_UINT32                          bitOpSpare                  : 20;

    VOS_UINT8                           ucPacketFilterId;
    VOS_UINT8                           ucNwPacketFilterId;
    TAF_PF_TRANS_DIRECTION_ENUM_UINT8   enDirection;
    VOS_UINT8                           ucPrecedence;                           /* packet filter evaluation precedence */

    VOS_UINT32                          ulSecuParaIndex;                        /* SPI */
    VOS_UINT16                          usSingleLcPort;
    VOS_UINT16                          usLcPortHighLimit;
    VOS_UINT16                          usLcPortLowLimit;
    VOS_UINT16                          usSingleRmtPort;
    VOS_UINT16                          usRmtPortHighLimit;
    VOS_UINT16                          usRmtPortLowLimit;
    VOS_UINT8                           ucProtocolId;                           /* 协议号 */
    VOS_UINT8                           ucTypeOfService;                        /* TOS */
    VOS_UINT8                           ucTypeOfServiceMask;                    /* TOS Mask */
    VOS_UINT8                           aucReserved[1];

    /* aucRmtIpv4Address[0]为IP地址高字节位
       aucRmtIpv4Address[3]为低字节位 */
    VOS_UINT8                           aucRmtIpv4Address[TAF_IPV4_ADDR_LEN];

    /* aucRmtIpv4Mask[0]为IP地址高字节位 ,
       aucRmtIpv4Mask[3]为低字节位*/
    VOS_UINT8                           aucRmtIpv4Mask[TAF_IPV4_ADDR_LEN];

    /* ucRmtIpv6Address[0]为IPv6接口标识高字节位
       ucRmtIpv6Address[7]为IPv6接口标识低字节位 */
    VOS_UINT8                           aucRmtIpv6Address[TAF_IPV6_ADDR_LEN];

    /* ucRmtIpv6Mask[0]为高字节位
       ucRmtIpv6Mask[7]为低字节位*/
    VOS_UINT8                           aucRmtIpv6Mask[TAF_IPV6_ADDR_LEN];

    VOS_UINT32                          ulFlowLabelType;                        /*FlowLabelType*/

    VOS_UINT8                           aucLocalIpv4Addr[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucLocalIpv4Mask[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucLocalIpv6Addr[TAF_IPV6_ADDR_LEN];
    VOS_UINT8                           ucLocalIpv6Prefix;
    VOS_UINT8                           aucReserved2[3];
}TAF_PDP_PF_STRU;


/*****************************************************************************
 结构名    : TAF_UMTS_QOS_STRU
 结构说明  : QOS参数结构
 修改记录  :
 1.日    期   : 2012年01月04日
   作    者   : l00198894
   修改内容   : PS Project，4字节对齐调整
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTrafficClass;                         /*UMTS承载服务优化类型*/
    VOS_UINT8                           ucDeliverOrder;                         /*SDU队列是否发送UMTS承载*/
    VOS_UINT8                           ucDeliverErrSdu;                        /*SDU错误是否发送*/
    VOS_UINT8                           aucReserved1[1];
    VOS_UINT16                          usMaxSduSize;                           /*SDU大小最大值*/
    VOS_UINT8                           aucReserved2[2];
    VOS_UINT32                          ulMaxBitUl;                             /*上行最大速率 kbits/s*/
    VOS_UINT32                          ulMaxBitDl;                             /*下行最大速率 kbits/s*/
    VOS_UINT8                           ucResidualBer;
    VOS_UINT8                           ucSduErrRatio;                          /*SDU误码率*/
    VOS_UINT16                          usTransDelay;                           /*传输延时, 单位毫秒*/
    VOS_UINT8                           ucTraffHandlePrior;                     /*处理UMTS承载的SDU对比其他承载的SDU*/
    VOS_UINT8                           aucReserved3[1];
    VOS_UINT8                           ucSrcStatisticsDescriptor;
    VOS_UINT8                           ucSignallingIndication;
    VOS_UINT32                          ulGuarantBitUl;                         /*保证上行传输速率 kbits/s*/
    VOS_UINT32                          ulGuarantBitDl;                         /*保证下行传输速率 kbits/s*/
}TAF_UMTS_QOS_STRU;


/*****************************************************************************
 结构名称: TAF_PRI_PDP_QUERY_INFO_STRU
 结构说明: ID_EVT_TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF消息结构

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
    TAF_PDP_PRIM_CONTEXT_STRU           stPriPdpInfo;

}TAF_PRI_PDP_QUERY_INFO_STRU;


/*****************************************************************************
 结构名称: TAF_TFT_QUREY_INFO_STRU
 结构说明: ID_EVT_TAF_PS_GET_TFT_INFO_CNF消息结构

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucPfNum;                                /* pf个数 */
    VOS_UINT8                           aucReserved[2];
    TAF_PDP_PF_STRU                     astPfInfo[TAF_MAX_SDF_PF_NUM];          /* pf表 */

}TAF_TFT_QUREY_INFO_STRU;

/*****************************************************************************
 结构名称: TAF_UMTS_QOS_QUERY_INFO_STRU
 结构说明: QOS查询消息结构

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
    TAF_UMTS_QOS_STRU                   stQosInfo;

} TAF_UMTS_QOS_QUERY_INFO_STRU;


/*****************************************************************************
 结构名称: TAF_DNS_QUERY_INFO_STRU
 结构说明: DNS查询消息结构

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
    TAF_PDP_DNS_STRU                    stDnsInfo;

}TAF_DNS_QUERY_INFO_STRU;

/*****************************************************************************
 结构名称: TAF_AUTH_QUERY_INFO_STRU
 结构说明: 鉴权参数查询

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
    TAF_PDP_AUTH_STRU                   stAuthInfo;

}TAF_AUTH_QUERY_INFO_STRU;

/*****************************************************************************
 结构名称: TAF_AUTHDATA_QUERY_INFO_STRU
 结构说明: ID_EVT_TAF_PS_GET_AUTHDATA_INFO_CNF鉴权参数查询消息结构

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
    TAF_PDP_AUTHDATA_STRU               stAuthDataInfo;

}TAF_AUTHDATA_QUERY_INFO_STRU;

/*****************************************************************************
 结构名称: TAF_PDP_TFT_STRU
 结构说明: TFT信息结构

 修改历史      :
  1.日    期   : 2014年06月16日
    作    者   : f00179208
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPfNum;                                /* pf个数 */
    TAF_PDP_PF_STRU                     astPf[TAF_MAX_SDF_PF_NUM];              /* pf表 */
}TAF_PDP_TFT_STRU;

/*****************************************************************************
 结构名称: TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU
 结构说明: 主动PDP激活成功返回结果的结构

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT32                          bitOpLinkdRabId     : 1;
    VOS_UINT32                          bitOpPdpAddr        : 1;
    VOS_UINT32                          bitOpApn            : 1;
    VOS_UINT32                          bitOpEmergencyInd   : 1;
    VOS_UINT32                          bitOpImCnSignalFlg  : 1;
    VOS_UINT32                          bitOpCause          : 1;
    VOS_UINT32                          bitOpUmtsQos        : 1;
    VOS_UINT32                          bitOpEpsQos         : 1;
    VOS_UINT32                          bitOpTft            : 1;
    VOS_UINT32                          bitOpSpare          : 23;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           ucLinkdRabId;
    TAF_PDP_EMC_IND_ENUM_UINT8          enEmergencyInd;
    TAF_PDP_IM_CN_SIG_FLAG_ENUM_UINT8   enImCnSignalFlg;
    VOS_UINT8                           aucReserved[3];
    TAF_PS_CAUSE_ENUM_UINT32            enCause;

    TAF_PDP_ADDR_STRU                   stPdpAddr;
    TAF_PDP_APN_STRU                    stApn;
    TAF_UMTS_QOS_STRU                   stUmtsQos;
    TAF_EPS_QOS_STRU                    stEpsQos;

    TAF_PDP_DNS_STRU                    stDns;
    TAF_PDP_NBNS_STRU                   stNbns;
    TAF_PDP_PCSCF_STRU                  stPcscf;
    TAF_PDP_GATEWAY_STRU                stGateWay;
    TAF_PDP_IPV6_DNS_STRU               stIpv6Dns;
    TAF_PDP_IPV6_PCSCF_STRU             stIpv6Pcscf;
    TAF_PDP_TFT_STRU                    stTft;

} TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU;


/*****************************************************************************
 结构名称: TAF_PS_CALL_PDP_ACTIVATE_IND_STRU
 结构说明: 网侧PDP激活上报的结构

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU TAF_PS_CALL_PDP_ACTIVATE_IND_STRU;

/*****************************************************************************
 结构名称: TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU
 结构说明: PDP激活被拒

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT32                          bitOpCauseEx        : 1;
    VOS_UINT32                          bitOpSpare          : 31;

    VOS_UINT8                           ucCid;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    VOS_UINT8                           aucReserved[2];
    TAF_PS_CAUSE_ENUM_UINT32            enCause;

    /*----------------------------------------------------------------------
       enCauseEx存在条件:
       enPdpType为IPv4/IPv6/PPP.

       enCauseEx可能的取值:
       TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED
       TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED
       TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED

       enCauseEx如何使用:
       用户发起双栈业务建立请求(IPv4v6), TAF上报了REJECT事件, 如果enPdpType
       为单栈(IPv4/IPv6), 用户需要根据enCauseEx, 决定是否继续发起业务请求.

       enCauseEx使用事例:
       用户发起双栈业务建立请求(IPv4v6), 网侧建立IPv4类型承载, 同时携带原因值
       TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED, 由于该承载不满足
       最小QOS, 被内部去激活, TAF上报REJECT事件, IP类型为IPv4, enCause为
       QOS_NOT_ACCEPT, enCauseEx为TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED,
       用户需要尝试发起IPv6业务建立请求.
    *---------------------------------------------------------------------*/
    TAF_PS_CAUSE_ENUM_UINT32            enCauseEx;

} TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU;

/*****************************************************************************
 结构名称: TAF_PS_CALL_PDP_MANAGE_IND_STRU
 结构说明: 网侧PDP激活，等待手动应答

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT32                          bitOpApn            : 1;
    VOS_UINT32                          bitOpPdpAddr        : 1;
    VOS_UINT32                          bitLinkdRabId       : 1;
    VOS_UINT32                          bitEmergencyInd     : 1;
    VOS_UINT32                          bitImCnSignalFlg    : 1;
    VOS_UINT32                          bitOpSpare          : 27;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           ucLinkdRabId;
    TAF_PDP_EMC_IND_ENUM_UINT8          enEmergencyInd;
    TAF_PDP_IM_CN_SIG_FLAG_ENUM_UINT8   enImCnSignalFlg;
    VOS_UINT8                           aucReserved[3];

    TAF_PDP_ADDR_STRU                   stPdpAddr;
    TAF_PDP_APN_STRU                    stApn;

} TAF_PS_CALL_PDP_MANAGE_IND_STRU;


/*****************************************************************************
 结构名称: TAF_PS_CALL_PDP_MODIFY_CNF_STRU
 结构说明: 主动MODIFY成功

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构

*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT32                          bitLinkdRabId       : 1;
    VOS_UINT32                          bitOpUmtsQos        : 1;
    VOS_UINT32                          bitOpEpsQos         : 1;
    VOS_UINT32                          bitOpTft            : 1;
    VOS_UINT32                          bitOpSpare          : 28;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           ucLinkdRabId;
    VOS_UINT8                           aucReserved[1];

    TAF_UMTS_QOS_STRU                   stUmtsQos;
    TAF_EPS_QOS_STRU                    stEpsQos;

    TAF_PDP_DNS_STRU                    stDns;
    TAF_PDP_NBNS_STRU                   stNbns;
    TAF_PDP_PCSCF_STRU                  stPcscf;
    TAF_PDP_IPV6_DNS_STRU               stIpv6Dns;
    TAF_PDP_IPV6_PCSCF_STRU             stIpv6Pcscf;
    TAF_PDP_TFT_STRU                    stTft;
} TAF_PS_CALL_PDP_MODIFY_CNF_STRU;

/*****************************************************************************
 结构名称: TAF_PS_CALL_PDP_MODIFY_IND_STRU
 结构说明: 网络MODIFY上报

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef TAF_PS_CALL_PDP_MODIFY_CNF_STRU TAF_PS_CALL_PDP_MODIFY_IND_STRU;

/*****************************************************************************
 结构名称: TAF_PS_CALL_PDP_MODIFY_REJ_STRU
 结构说明: MODIFY被拒

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           aucReserved[2];
    TAF_PS_CAUSE_ENUM_UINT32            enCause;

} TAF_PS_CALL_PDP_MODIFY_REJ_STRU;


/*****************************************************************************
 结构名称: TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU
 结构说明: 主动去激活成功

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucRabId;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    VOS_UINT8                           aucReserved[1];
    TAF_PS_CAUSE_ENUM_UINT32            enCause;

} TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU;


/*****************************************************************************
 结构名称: TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU
 结构说明: 网络侧去激活

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU;


/*****************************************************************************
 结构名称: TAF_PS_CALL_PDP_PDP_DISCONNECT_IND_STRU
 结构说明: 断开连接

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

} TAF_PS_CALL_PDP_PDP_DISCONNECT_IND_STRU;


/*****************************************************************************
 结构名    : TAF_PS_COMMON_CNF_STRU
 结构说明  : PS域事件通用结构体
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
} TAF_PS_COMMON_CNF_STRU;


/*****************************************************************************
 结构名    : TAF_PDP_PRIM_CONTEXT_EXT_STRU
 结构说明  : +CGDCONT命令参数, 见TS 27.007 section 10.1.1
 1.日    期 : 2011年10月19日
   作    者 : A00165503
   修改内容 : 创建文件
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPdpType        : 1;                /* PdpType*/
    VOS_UINT32                          bitOpApn            : 1;                /* aucApn*/
    VOS_UINT32                          bitOpPdpAddr        : 1;                /* aucPdpAddr*/
    VOS_UINT32                          bitOpPdpDcomp       : 1;                /* PdpDcomp*/
    VOS_UINT32                          bitOpPdpHcomp       : 1;                /* PdpHcomp*/
    VOS_UINT32                          bitOpIpv4AddrAlloc  : 1;                /* Ipv4AddrAlloc*/
    VOS_UINT32                          bitOpEmergencyInd   : 1;                /* Emergency Indication*/
    VOS_UINT32                          bitOpPcscfDiscovery : 1;                /* P-CSCF discovery */
    VOS_UINT32                          bitOpImCnSignalFlg  : 1;                /* IM CN Signalling Flag */
    VOS_UINT32                          bitOpSpare          : 23;

    VOS_UINT8                           ucDefined;                              /* 0:undefined, 1:defined */

    VOS_UINT8                           ucCid;

    /* 1 IP Internet Protocol (IETF STD 5) */
    /* 2 IPV6 Internet Protocol, version 6 (IETF RFC 2460) */
    /* 3 IPV4V6 Virtual <PDP_type> introduced to handle dual IP stack UE capability. (See 3GPP TS 24.301 [83]) */
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;

    VOS_UINT8                           aucReserved[1];

    /* Access Point Name*/
    VOS_UINT8                           aucApn[TAF_MAX_APN_LEN + 1];

    /* the MT in the address space applicable to the PDP.*/
    TAF_PDP_ADDR_STRU                   stPdpAddr;

    /* 0 - off  (default if value is omitted) */
    /* 1 - on (manufacturer preferred compression) */
    /* 2 - V.42bis */
    /* 3 - V.44 */
    TAF_PDP_D_COMP_ENUM_UINT8           enPdpDcomp;

    /* 0 - off (default if value is omitted) */
    /* 1 - on (manufacturer preferred compression) */
    /* 2 - RFC1144 (applicable for SNDCP only) */
    /* 3 - RFC2507*/
    /* 4 - RFC3095 (applicable for PDCP only)*/
    TAF_PDP_H_COMP_ENUM_UINT8           enPdpHcomp;

    /* 0 - IPv4 Address Allocation through NAS Signaling (default if omitted) */
    /* 1 - IPv4 Address Allocated through DHCP */
    TAF_PDP_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT8 enIpv4AddrAlloc;

    /* 0 - PDP context is not for emergency bearer services */
    /* 1 - PDP context is for emergency bearer services */
    TAF_PDP_EMC_IND_ENUM_UINT8          enEmergencyFlg;

    /* 0 - Preference of P-CSCF address discovery not influenced by +CGDCONT */
    /* 1 - Preference of P-CSCF address discovery through NAS Signalling */
    /* 2 - Preference of P-CSCF address discovery through DHCP */
    TAF_PDP_PCSCF_DISCOVERY_ENUM_UINT8  enPcscfDiscovery;

    /* 0 - UE indicates that the PDP context is not for IM CN subsystem-related signalling only */
    /* 1 - UE indicates that the PDP context is for IM CN subsystem-related signalling only */
    TAF_PDP_IM_CN_SIG_FLAG_ENUM_UINT8   enImCnSignalFlg;

    VOS_UINT8                           aucReserved2[2];

}TAF_PDP_PRIM_CONTEXT_EXT_STRU;

/*****************************************************************************
 结构名称: TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU
 结构说明: ID_MSG_TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ、
           ID_EVT_TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_CNF消息

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PDP_PRIM_CONTEXT_EXT_STRU       stPdpContextInfo;
} TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_CNF_STRU;

/*****************************************************************************
 结构名称: TAF_SET_IMS_PDP_CFG_STRU
 结构说明: ^IMSPDPCFG命令参数

 修改历史      :
  1.日    期   : 2015年07月30日
    作    者   : z00301431
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucImsFlag;
    VOS_UINT8                           aucReserved[2];
} TAF_IMS_PDP_CFG_STRU;

/*****************************************************************************
 结构名称: TAF_PS_SET_IMS_PDP_CFG_REQ_STRU
 结构说明: ID_MSG_TAF_PS_SET_IMS_PDP_CFG_REQ
           ID_EVT_TAF_PS_SET_IMS_PDP_CFG_CNF消息

 修改历史      :
  1.日    期   : 2015年07月30日
    作    者   : z00301431
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_IMS_PDP_CFG_STRU                stImsPdpCfg;
} TAF_PS_SET_IMS_PDP_CFG_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_IMS_PDP_CFG_CNF_STRU;

/*****************************************************************************
 结构名称  : TAF_PS_SET_1X_DORMANT_TIMER_REQ_STRU
 结构说明  : ID_MSG_TAF_PS_SET_1X_MAX_NO_DATA_TIME_LEN_REQ消息结构体

  1.日    期   : 2015年4月20日
    作    者   : y00314741
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT8                           ucDormantTimer;
    VOS_UINT8                           aucReserved[3];
}TAF_PS_SET_1X_DORM_TIMER_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_1X_DORM_TIMER_CNF_STRU;

/*****************************************************************************
 结构名称  : TAF_PS_GET_1X_DORM_TIMER_VALUE_REQ_STRU
 结构说明  : ID_MSG_TAF_PS_GET_CGMTU_VALUE_REQ消息结构体

  1.日    期   : 2015年4月20日
    作    者   : y00314741
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
}TAF_PS_GET_1X_DORM_TIMER_REQ_STRU;

/*****************************************************************************
 结构名称  : TAF_PS_GET_CGMTU_VALUE_CNF_STRU
 结构说明  : ID_EVT_TAF_PS_GET_CGMTU_VALUE_CNF消息结构体

  1.日    期   : 2015年4月20日
    作    者   : y00314741
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    VOS_UINT8                           ucSocmDormTiVal;
    VOS_UINT8                           ucUserCfgDormTival;
    VOS_UINT8                           aucReserved[2];
}TAF_PS_GET_1X_DORM_TIMER_CNF_STRU;

/*****************************************************************************
 结构名称: TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ_STRU
 结构说明: ID_MSG_TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ消息

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ_STRU;


/*****************************************************************************
 结构名称: TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ_STRU
 结构说明: ID_MSG_TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF消息

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_PRI_PDP_QUERY_INFO_STRU         astPdpContextQueryInfo[0];
} TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF_STRU;

/*****************************************************************************
 描述 : 针对命令 +CGDSCONT
 ID   : ID_MSG_TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ
        ID_MSG_TAF_PS_SET_SEC_PDP_CONTEXT_INFO_CNF
        ID_MSG_TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ
        ID_MSG_TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF
 REQ  : TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU; TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ_STRU
 CNF  : TAF_PS_SET_SEC_PDP_CONTEXT_INFO_CNF_STRU; TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF_STRU
 IND  : -
 说明 : ...
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpLinkdCid       : 1;
    VOS_UINT32                          bitOpPdpDcomp       : 1;
    VOS_UINT32                          bitOpPdpHcomp       : 1;
    VOS_UINT32                          bitOpSpare          : 29;

    VOS_UINT8                           ucDefined;          /* 0:undefined, 1:defined */
    VOS_UINT8                           ucCid;              /* dedicated EPS Bearer context */
    VOS_UINT8                           ucLinkdCid;         /* Default EPS Bearer context */
    TAF_PDP_D_COMP_ENUM_UINT8           enPdpDcomp;         /* no used in LTE */
    TAF_PDP_H_COMP_ENUM_UINT8           enPdpHcomp;         /* no used in LTE */
    VOS_UINT8                           aucReserved[3];

} TAF_PDP_SEC_CONTEXT_EXT_STRU;


/*****************************************************************************
 结构名    : TAF_PDP_SEC_CONTEXT_STRU
 结构说明  : 次PDP上下文结构
 修改记录  :
 1.日    期   : 2012年07月24日
   作    者   : Y00213812
   修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;              /* [1，11] */
    VOS_UINT8                           ucLinkdCid;         /* [1，11] */
    TAF_PDP_D_COMP_ENUM_UINT8           enPdpDcomp;         /*数据压缩算法*/
    TAF_PDP_H_COMP_ENUM_UINT8           enPdpHcomp;         /*头压缩算法*/

}TAF_PDP_SEC_CONTEXT_STRU;


/*****************************************************************************
 结构名    : TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU
 结构说明  : 次PDP上下文设置结构
 修改记录  :
 1.日    期   : 2012年07月24日
   作    者   : Y00213812
   修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PDP_SEC_CONTEXT_EXT_STRU        stPdpContextInfo;

} TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_SEC_PDP_CONTEXT_INFO_CNF_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_PDP_SEC_CONTEXT_STRU            astPdpContextQueryInfo[0];
} TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF_STRU;


/*****************************************************************************
 描述 : 针对命令 +CGACT
 ID   : ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ
        ID_MSG_TAF_PS_SET_PDP_STATE_CNF
        ID_MSG_TAF_PS_GET_PDP_CONTEXT_STATE_REQ
        ID_MSG_TAF_PS_GET_PDP_STATE_CNF
 REQ  : TAF_PS_SET_PDP_STATE_REQ_STRU     TAF_PS_GET_PDP_STATE_REQ_STRU
 CNF  : TAF_PS_SET_PDP_STATE_CNF_STRU TAF_PS_GET_PDP_STATE_CNF_STRU
 IND  : -
 说明 : ...
*****************************************************************************
*****************************************************************************
 结构名    : TAF_CID_LIST_STRU
 结构说明  : CID列表结构体
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucCid[TAF_MAX_CID + 1];
} TAF_CID_LIST_STRU;

/*****************************************************************************
 结构名    : TAF_CID_STATE_STRU
 结构说明  : CID状态结构体
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucState;
    VOS_UINT8                           aucReserved[2];
} TAF_CID_STATE_STRU;

/*****************************************************************************
 结构名    : TAF_CID_LIST_STATE_STRU
 结构说明  : CID列表状态结构体
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucState;                                /* 0 - deactivated,1 - activated */
    VOS_UINT8                           aucReserved[3];

    VOS_UINT8                           aucCid[TAF_MAX_CID + 1];
} TAF_CID_LIST_STATE_STRU;

/*****************************************************************************
 结构名    : TAF_PS_SET_PDP_STATE_REQ_STRU
 结构说明  : CID状态结构体
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_CID_LIST_STATE_STRU             stCidListStateInfo;
} TAF_PS_SET_PDP_STATE_REQ_STRU;

/*****************************************************************************
 结构名    : TAF_PS_CALL_END_REQ_STRU
 结构说明  : ID_EVT_TAF_PS_SET_PDP_CONTEXT_STATE_CNF事件结构

 修改历史      :
  1.日    期   : 2011年08月22日
    作    者   : A00165503
    修改内容   : 新增结构

  2.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 修改成员
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
} TAF_PS_SET_PDP_STATE_CNF_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_PDP_STATE_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_CID_STATE_STRU                  astCidStateInfo[0];
} TAF_PS_GET_PDP_STATE_CNF_STRU;


/*****************************************************************************
 描述 : 针对命令 +CGTFT
 ID   : ID_MSG_L4A_SET_CGTFT_REQ
        ID_MSG_L4A_SET_CGTFT_CNF
        ID_MSG_L4A_READ_CGTFT_REQ
        ID_MSG_L4A_READ_CGTFT_CNF
 REQ  : L4A_SET_CGTFT_REQ_STRU;L4A_READ_CGTFT_REQ_STRU;
 CNF  : L4A_SET_CGTFT_CNF_STRU;L4A_READ_CGTFT_CNF_STRU;
 IND  : -
 说明 : ...
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPktFilterId    : 1;    /* ucPacketFilterId*/
    VOS_UINT32                          bitOpPrecedence     : 1;    /* ucPrecedence*/
    VOS_UINT32                          bitOpSrcIp          : 1;    /* aucSourceIpAddr,Mask*/
    VOS_UINT32                          bitOpProtocolId     : 1;    /* ucProtocolId*/
    VOS_UINT32                          bitOpDestPortRange  : 1;    /* destination port range*/
    VOS_UINT32                          bitOpSrcPortRange   : 1;    /* source port range*/
    VOS_UINT32                          bitOpSpi            : 1;    /* ipsec security parameter index*/
    VOS_UINT32                          bitOpTosMask        : 1;    /* type of service*/
    VOS_UINT32                          bitOpFlowLable      : 1;    /* ulFlowLable*/
    VOS_UINT32                          bitOpDirection      : 1;    /* Direction*/
    VOS_UINT32                          bitOpNwPktFilterId  : 1;    /* NWPacketFltId*/
    VOS_UINT32                          bitOpLocalIpv4AddrAndMask      : 1;
    VOS_UINT32                          bitOpLocalIpv6AddrAndMask      : 1;
    VOS_UINT32                          bitOpSpare          : 19;

    VOS_UINT8                           ucCid;

    VOS_UINT8                           ucDefined;

    VOS_UINT8                           ucPacketFilterId;       /* Packet Filter Id,value range from 1 to 16*/

    VOS_UINT8                           ucPrecedence;           /* evaluation precedence index,The value range is from 0 to 255*/

    VOS_UINT8                           ucProtocolId;           /* protocol number,value range from 0 to 255*/

    VOS_UINT8                           aucReserved[3];

    /* source address and subnet mask*/
    TAF_PDP_ADDR_STRU                   stSourceIpaddr;
    TAF_PDP_ADDR_STRU                   stSourceIpMask;

    /* destination port range*/
    VOS_UINT16                          usLowDestPort;                          /* value range from 0 to 65535*/
    VOS_UINT16                          usHighDestPort;                         /* value range from 0 to 65535*/

    /* source port range*/
    VOS_UINT16                          usLowSourcePort;                        /* value range from 0 to 65535*/
    VOS_UINT16                          usHighSourcePort;                       /* value range from 0 to 65535*/

    /* ipsec security parameter index*/
    VOS_UINT32                          ulSecuParaIndex;

    /* only for ipv6*/
    VOS_UINT32                          ulFlowLable;                            /* value range is from 00000 to FFFFF*/

    /* type of service*/
    VOS_UINT8                           ucTypeOfService;                        /* value range from 0 to 255*/
    VOS_UINT8                           ucTypeOfServiceMask;                    /* value range from 0 to 255*/

    /* 0 - Pre-Release 7 TFT filter (see 3GPP TS 24.008 [8], table 10.5.162)*/
    /* 1 - Uplink*/
    /* 2 - Downlink*/
    /* 3 - Birectional (Up & Downlink) (default if omitted)*/
    VOS_UINT8                           ucDirection;

    /* only for CGTFTRDP*/
    VOS_UINT8                           ucNwPktFilterId;                        /* value range from 1 to 16*/

    /* local address and subnet mask*/
    VOS_UINT8                           aucLocalIpv4Addr[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucLocalIpv4Mask[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucLocalIpv6Addr[TAF_IPV6_ADDR_LEN];
    VOS_UINT8                           ucLocalIpv6Prefix;
    VOS_UINT8                           aucReserved2[3];
} TAF_TFT_EXT_STRU;

typedef struct
{
    VOS_UINT32                          ulCid;
    VOS_UINT32                          ulPFNum;
    TAF_TFT_EXT_STRU                    astTftInfo[TAF_MAX_SDF_PF_NUM];
} TAF_PF_TFT_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_TFT_EXT_STRU                    stTftInfo;
} TAF_PS_SET_TFT_INFO_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_TFT_INFO_CNF_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_TFT_INFO_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_TFT_QUREY_INFO_STRU             astTftQueryInfo[0];
} TAF_PS_GET_TFT_INFO_CNF_STRU;


/*****************************************************************************
 描述 : 针对命令 +CGEQREQ
 ID   :



 REQ  :
 CNF  :
 IND  : -
 说明 : ...
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpTrafficClass       : 1;
    VOS_UINT32                          bitOpDeliverOrder       : 1;
    VOS_UINT32                          bitOpDeliverErrSdu      : 1;
    VOS_UINT32                          bitOpMaxSduSize         : 1;
    VOS_UINT32                          bitOpMaxBitUl           : 1;
    VOS_UINT32                          bitOpMaxBitDl           : 1;
    VOS_UINT32                          bitOpResidualBer        : 1;
    VOS_UINT32                          bitOpSduErrRatio        : 1;
    VOS_UINT32                          bitOpTransDelay         : 1;
    VOS_UINT32                          bitOpTraffHandlePrior   : 1;
    VOS_UINT32                          bitOpGtdBitUl           : 1;
    VOS_UINT32                          bitOpGtdBitDl           : 1;
    VOS_UINT32                          bitOpSrcStatisticsDes   : 1;
    VOS_UINT32                          bitOpSignalIndication   : 1;
    VOS_UINT32                          bitOpSpare              : 18;

    VOS_UINT8                           ucDefined;

    VOS_UINT8                           ucCid;

    VOS_UINT8                           ucTrafficClass;     /* 0 : Conversational class
                                                               1 : Streaming class
                                                               2 : Interactive class
                                                               3 : Background class
                                                               4 : Subscribed value */
    VOS_UINT8                           ucSduErrRatio;      /* 0 : subscribed value
                                                               1 : 1*10-2
                                                               2 : 7*10-3
                                                               3 : 1*10-3
                                                               4 : 1*10-4
                                                               5 : 1*10-5
                                                               6 : 1*10-6
                                                               7 : 1*10-1 */
    VOS_UINT16                          usMaxSduSize;       /* 0 : Subscribed value
                                                               1~1520: 1 ~1520 octets */

    VOS_UINT8                           ucDeliverOrder;     /* 0 : Without delivery order
                                                               1 : With delivery order
                                                               2 : Subscribed value */

    VOS_UINT8                           ucDeliverErrSdu;    /* 0 : Erroneous SDUs are not delivered
                                                               1 : Erroneous SDUs are delivered
                                                               2 : No detect
                                                               3 : subscribed value */

    VOS_UINT32                          ulMaxBitUl;         /* 0 : Subscribed value
                                                               1~256000: 1kbps ~ 256000kbps*/
    VOS_UINT32                          ulMaxBitDl;         /* 同ulMaxBitUl */
    VOS_UINT32                          ulGtdBitUl;         /* 同ulMaxBitUl */
    VOS_UINT32                          ulGtdBitDl;         /* 同ulMaxBitUl */
    VOS_UINT8                           ucResidualBer;      /* 0 : subscribed value
                                                               1 : 5*10-2
                                                               2 : 1*10-2
                                                               3 : 5*10-3
                                                               4 : 4*10-3
                                                               5 : 1*10-3
                                                               6 : 1*10-4
                                                               7 : 1*10-5
                                                               8 : 1*10-6
                                                               9 : 6*10-8 */
    VOS_UINT8                           ucTraffHandlePrior; /* 0 : Subscribed value
                                                               1 : Priority level 1
                                                               2 : Priority level 2
                                                               3 : Priority level 3 */
    VOS_UINT16                          usTransDelay;       /* 0 : Subscribed value
                                                               1~4100 : 1ms~4100ms */

    VOS_UINT8                           ucSrcStatisticsDes; /* 0: Characteristics of SDUs is unknown
                                                               1: Characteristics of SDUs corresponds to a speech source */

    VOS_UINT8                           ucSignalIndication; /* 0: PDP context is not optimized for signalling
                                                               1: PDP context is optimized for signalling */

    VOS_UINT8                           aucReserved[2];

} TAF_UMTS_QOS_EXT_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_UMTS_QOS_EXT_STRU               stUmtsQosInfo;
} TAF_PS_SET_UMTS_QOS_INFO_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_UMTS_QOS_INFO_CNF_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_UMTS_QOS_INFO_REQ_STRU;

/*****************************************************************************
 结构名称: TAF_UMTS_QOS_QUERY_INFO_STRU
 结构说明: ID_EVT_TAF_PS_GET_UMTS_QOS_INFO_CNF消息结构

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_UMTS_QOS_QUERY_INFO_STRU        astUmtsQosQueryInfo[0];
} TAF_PS_GET_UMTS_QOS_INFO_CNF_STRU;


/*****************************************************************************
 描述 : 针对命令 +CGEQMIN
 ID   :



 REQ  :
 CNF  :
 IND  : -
 说明 : ...
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_UMTS_QOS_EXT_STRU               stUmtsQosMinInfo;
} TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_UMTS_QOS_MIN_INFO_CNF_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ_STRU;

/*****************************************************************************
 结构名称: TAF_UMTS_QOS_QUERY_INFO_STRU
 结构说明: ID_EVT_TAF_PS_GET_UMTS_QOS_MIN_INFO_CNF消息结构

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_UMTS_QOS_QUERY_INFO_STRU        astUmtsQosQueryInfo[0];
} TAF_PS_GET_UMTS_QOS_MIN_INFO_CNF_STRU;


/*****************************************************************************
 描述 : 针对命令 +CGEQNEG
 ID   :



 REQ  :
 CNF  :
 IND  : -
 说明 : ...
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_CID_LIST_STRU                   stCidListInfo;
} TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_UMTS_QOS_QUERY_INFO_STRU        astUmtsQosQueryInfo[0];
} TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_CNF_STRU;


/*****************************************************************************
 描述 : 针对命令 +CGMOD
 ID   :



 REQ  :
 CNF  :
 IND  : -
 说明 : ...
*****************************************************************************/

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_CID_LIST_STRU                   stCidListInfo;
} TAF_PS_CALL_MODIFY_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_CALL_MODIFY_CNF_STRU;


/*****************************************************************************
 描述 : 针对命令 +CGANS
 ID   : ID_MSG_L4A_SET_CGANS_RSP
        ID_MSG_L4A_SET_CGANS_CNF
        ID_MSG_L4A_CGANS_IND
 RSP  : L4A_SET_CGANS_RSP_STRU
 CNF  : L4A_SET_CGANS_CNF_STRU
 IND  : L4A_CGANS_IND_STRU
 说明 : L4A_CGANS_IND_STRU 是网络发起事件,后续可能不会使用该原语
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucL2P[20];
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucAnsExtFlg;                            /* 如果是^CGANS命令，为VOS_TRUE。否则为VOS_FALSE */
    VOS_UINT8                           aucReserved[2];
} TAF_PS_ANSWER_STRU;


typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_ANSWER_STRU                  stAnsInfo;
} TAF_PS_CALL_ANSWER_REQ_STRU;


typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;

    VOS_UINT8                           ucCid;

    VOS_UINT8                           aucReserved[3];
}TAF_PS_CALL_ANSWER_CNF_STRU;


typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_CALL_HANGUP_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_CALL_HANGUP_CNF_STRU;


/*****************************************************************************
 描述 : 针对命令 +CGPADDR
 ID   :


 REQ  :
 CNF  :
 IND  : -
 说明 : ...
*****************************************************************************/
/*****************************************************************************
 结构名称   : TAF_PDP_ADDR_STRU
 协议表格   :
 结构说明   :
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];

    /* the MT in the address space applicable to the PDP */
    TAF_PDP_ADDR_STRU                   stPdpAddr;
} TAF_PDP_ADDR_QUERY_INFO_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_CID_LIST_STRU                   stCidListInfo;
} TAF_PS_GET_PDP_IP_ADDR_INFO_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_PDP_ADDR_QUERY_INFO_STRU        astPdpAddrQueryInfo[0];
} TAF_PS_GET_PDP_IP_ADDR_INFO_CNF_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    VOS_UINT32                          ulCid[TAF_MAX_CID+1];
} TAF_PS_GET_PDP_CONTEXT_INFO_CNF_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_PDP_CONTEXT_INFO_REQ_STRU;

/*****************************************************************************
 描述 : 针对命令 +CGAUTO
 ID   : ID_MSG_L4A_SET_CGAUTO_REQ
        ID_MSG_L4A_SET_CGAUTO_CNF
        ID_MSG_L4A_READ_CGAUTO_REQ
        ID_MSG_L4A_READ_CGAUTO_CNF
 REQ  : L4A_SET_CGAUTO_REQ_STRU; L4A_READ_CGAUTO_REQ_STRU
 CNF  : L4A_SET_CGAUTO_CNF_STRU; L4A_READ_CGAUTO_CNF_STRU
 IND  : -
 说明 : ...
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT32                          ulAnsMode;
} TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_ANSWER_MODE_INFO_CNF_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_ANSWER_MODE_INFO_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulAnsMode;
} TAF_PS_GET_ANSWER_MODE_INFO_CNF_STRU;


/*****************************************************************************
 描述 : 针对命令 +CGCONTRDP
 ID   : ID_MSG_L4A_SET_CGCONTRDP_REQ
        ID_MSG_L4A_SET_CGCONTRDP_CNF
 REQ  : L4A_SET_CGCONTRDP_REQ_STRU
 CNF  : L4A_SET_CGCONTRDP_CNF_STRU
 IND  : -
 说明 : ...
******************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpBearerId       : 1;                /* BearerId*/
    VOS_UINT32                          bitOpApn            : 1;                /* aucApn*/
    VOS_UINT32                          bitOpIpAddr         : 1;                /* aucIpaddr*/
    VOS_UINT32                          bitOpSubMask        : 1;                /* aucSubnetMask*/
    VOS_UINT32                          bitOpGwAddr         : 1;                /* aucGWAddr*/
    VOS_UINT32                          bitOpDNSPrimAddr    : 1;                /* aucDNSPrimAddr*/
    VOS_UINT32                          bitOpDNSSecAddr     : 1;                /* aucDNSSecAddr*/
    VOS_UINT32                          bitOpPCSCFPrimAddr  : 1;                /* aucPCSCFPrimAddr*/
    VOS_UINT32                          bitOpPCSCFSecAddr   : 1;                /* aucPCSCFSecAddr*/
    VOS_UINT32                          bitOpImCnSignalFlg  : 1;
    VOS_UINT32                          bitOpSpare          : 22;

    VOS_UINT8                           ucPrimayCid;                            /* default EPS bearer context*/
    VOS_UINT8                           ucBearerId;                             /* a numeric parameter which identifies the bearer*/

    /* the IM CN subsystem-related signalling flag */
    TAF_PDP_IM_CN_SIG_FLAG_ENUM_UINT8   enImCnSignalFlg;

    VOS_UINT8                           aucReserved[1];

    /* Access Pointer Name*/
    VOS_UINT8                           aucApn[TAF_MAX_APN_LEN + 1];

    /* the IP Address of the MT*/
    TAF_PDP_ADDR_STRU                   stPdpAddr;

    /* the subnet mask for the IP Address of the MT*/
    TAF_PDP_ADDR_STRU                   stSubnetMask;

    /* the Gateway Address of the MT*/
    TAF_PDP_ADDR_STRU                   stGWAddr;

    /* the IP Address of the primary DNS Server*/
    TAF_PDP_ADDR_STRU                   stDNSPrimAddr;

    /* the IP address of the secondary DNS Server*/
    TAF_PDP_ADDR_STRU                   stDNSSecAddr;

    /* the IP Address of the primary P-CSCF Server*/
    TAF_PDP_ADDR_STRU                   stPCSCFPrimAddr;

    /* the IP Address of the secondary P-CSCF Server*/
    TAF_PDP_ADDR_STRU                   stPCSCFSecAddr;

} TAF_PDP_DYNAMIC_PRIM_EXT_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    /* 0xff-if the parameter <cid> is omitted */
    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
} TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_PDP_DYNAMIC_PRIM_EXT_STRU       astPdpContxtInfo[0];
} TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU;


/*****************************************************************************
 描述 : 针对命令 +CGSCONTRDP
 ID   : ID_MSG_L4A_SET_CGSCONTRDP_REQ
        ID_MSG_L4A_SET_CGSCONTRDP_CNF
 REQ  : L4A_SET_CGSCONTRDP_REQ_STRU
 CNF  : L4A_SET_CGSCONTRDP_CNF_STRU
 IND  : -
 说明 : ...
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;

    /* default EPS bearer context */
    VOS_UINT8                           ucPrimaryCid;

    /* a numeric parameter which identifies the bearer */
    VOS_UINT8                           ucBearerId;

    VOS_UINT8                           ucReserved[1];
} TAF_PDP_DYNAMIC_SEC_EXT_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    /* 0xff-if the parameter <cid> is omitted */
    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
} TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_PDP_DYNAMIC_SEC_EXT_STRU        astPdpContxtInfo[0];
} TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF_STRU;


/*****************************************************************************
 描述 : 针对命令 +CGTFTRDP
 ID   : ID_MSG_L4A_SET_CGTFTRDP_REQ
        ID_MSG_L4A_SET_CGTFTRDP_CNF
 REQ  : L4A_SET_CGTFTRDP_REQ_STRU
 CNF  : L4A_SET_CGTFTRDP_CNF_STRU
 IND  : -
 说明 : ...
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    /* 0xff-if the parameter <cid> is omitted */
    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
} TAF_PS_GET_DYNAMIC_TFT_INFO_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_PF_TFT_STRU                     astPfTftInfo[0];
} TAF_PS_GET_DYNAMIC_TFT_INFO_CNF_STRU;


/*****************************************************************************
 描述 : 针对命令 +CGEQOS
 ID   : ID_MSG_L4A_SET_CGEQOS_REQ
        ID_MSG_L4A_SET_CGEQOS_CNF
        ID_MSG_L4A_READ_CGEQOS_REQ
        ID_MSG_L4A_READ_CGEQOS_CNF
 REQ  : L4A_SET_CGEQOS_REQ_STRU L4A_READ_CGEQOS_REQ_STRU
 CNF  : L4A_SET_CGEQOS_CNF_STRU L4A_READ_CGEQOS_CNF_STRU
 IND  : -
 说明 : ...
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpQCI            : 1;                /* QCI*/
    VOS_UINT32                          bitOpDLGBR          : 1;                /* DLGBR*/
    VOS_UINT32                          bitOpULGBR          : 1;                /* ULGBR*/
    VOS_UINT32                          bitOpDLMBR          : 1;                /* DLMBR*/
    VOS_UINT32                          bitOpULMBR          : 1;                /* ULMBR*/
    VOS_UINT32                          bitOpSpare          : 27;

    VOS_UINT8                           ucCid;

    /* 0 QCI is selected by network*/
    /* [1 - 4]value range for guranteed bit rate Traffic Flows*/
    /* [5 - 9]value range for non-guarenteed bit rate Traffic Flows*/
    VOS_UINT8                           ucQCI;

    VOS_UINT8                           ucReserved[2];

    /* DL GBR in case of GBR QCI, The value is in kbit/s*/
    VOS_UINT32                          ulDLGBR;

    /* UL GBR in case of GBR QCI, The value is in kbit/s*/
    VOS_UINT32                          ulULGBR;

    /* DL MBR in case of GBR QCI, The value is in kbit/s*/
    VOS_UINT32                          ulDLMBR;

    /* UL MBR in case of GBR QCI, The value is in kbit/s*/
    VOS_UINT32                          ulULMBR;
}TAF_EPS_QOS_EXT_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_EPS_QOS_EXT_STRU                stEpsQosInfo;
} TAF_PS_SET_EPS_QOS_INFO_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_EPS_QOS_INFO_CNF_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_EPS_QOS_INFO_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_EPS_QOS_EXT_STRU                astEpsQosInfo[0];
} TAF_PS_GET_EPS_QOS_INFO_CNF_STRU;


/*****************************************************************************
 描述 : 针对命令 +CGEQOSRDP
 ID   : ID_MSG_L4A_SET_CGEQOSRDP_REQ
        ID_MSG_L4A_SET_CGEQOSRDP_CNF
 REQ  : L4A_SET_CGEQOSRDP_REQ_STRU
 CNF  : L4A_SET_CGEQOSRDP_CNF_STRU
 IND  : -
 说明 : ...
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    /* 0xff-if the parameter <cid> is omitted */
    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
} TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_EPS_QOS_EXT_STRU                astEpsQosInfo[0];
} TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF_STRU;


/*****************************************************************************
 结构名    : TAF_PS_GET_DSFLOW_INFO_REQ_STRU
 结构说明  : ID_MSG_TAF_PS_GET_DSFLOW_INFO_REQ消息结构体, 获取流量信息
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT8                           aucReserve[4];
} TAF_PS_GET_DSFLOW_INFO_REQ_STRU;

/*****************************************************************************
 结构名    : TAF_PS_GET_DSFLOW_INFO_CNF_STRU
 结构说明  : ID_MSG_TAF_PS_GET_DSFLOW_INFO_CNF消息结构体, 获取流量信息
  1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件

  2.日    期   : 2011年12月23日
    作    者   : o00132663
    修改内容   : PS融合项目，流量上报使用新结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    TAF_DSFLOW_QUERY_INFO_STRU          stQueryInfo;
} TAF_PS_GET_DSFLOW_INFO_CNF_STRU;


/*****************************************************************************
 描述 : 针对命令 ^DSFLOWCLR
 ID   :

 REQ  :
 CNF  :
 IND  : -
 说明 : ...
*****************************************************************************/
/*****************************************************************************
 结构名    : TAF_DSFLOW_CLEAR_CONFIG_STRU
 结构说明  : 流量清除配置
*****************************************************************************/
typedef struct
{
    TAF_DSFLOW_CLEAR_MODE_ENUM_UINT8    enClearMode;
    VOS_UINT8                           ucNsapi;
    VOS_UINT8                           aucReserved[2];
} TAF_DSFLOW_CLEAR_CONFIG_STRU;

/*****************************************************************************
 结构名    : TAF_PS_CLEAR_DSFLOW_REQ_STRU
 结构说明  : ID_MSG_TAF_PS_CLEAR_DSFLOW_REQ消息结构体, 清除流量信息
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_DSFLOW_CLEAR_CONFIG_STRU        stClearConfigInfo;
} TAF_PS_CLEAR_DSFLOW_REQ_STRU;

/*****************************************************************************
 结构名    : TAF_PS_CLEAR_DSFLOW_CNF_STRU
 结构说明  : ID_MSG_TAF_PS_CLEAR_DSFLOW_CNF消息结构体, 清除流量信息
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
typedef TAF_PS_COMMON_CNF_STRU TAF_PS_CLEAR_DSFLOW_CNF_STRU;


/*****************************************************************************
 描述 : 针对命令 ^DSFLOWRPT
 ID   :

 REQ  :
 CNF  :
 IND  : -
 说明 : ...
*****************************************************************************/
/*****************************************************************************
 结构名    : TAF_DSFLOW_REPORT_CONFIG_STRU
 结构说明  : 流量上报配置结构体
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRptEnabled;       /* 流量上报开启标记   */
    VOS_UINT32                          ulTimerLength;      /* 流量上报定时器时长 */
} TAF_DSFLOW_REPORT_CONFIG_STRU;

/*****************************************************************************
 结构名    : TAF_PS_CONFIG_DSFLOW_RPT_REQ_STRU
 结构说明  : ID_MSG_TAF_PS_CONFIG_DSFLOW_RPT_REQ消息结构体, 控制流量上报
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_DSFLOW_REPORT_CONFIG_STRU       stReportConfigInfo;
} TAF_PS_CONFIG_DSFLOW_RPT_REQ_STRU;

/*****************************************************************************
 结构名    : TAF_PS_CONFIG_DSFLOW_RPT_CNF_STRU
 结构说明  : ID_MSG_TAF_PS_CONFIG_DSFLOW_RPT_CNF消息结构体, 控制流量上报
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
typedef TAF_PS_COMMON_CNF_STRU TAF_PS_CONFIG_DSFLOW_RPT_CNF_STRU;

/*****************************************************************************
 结构名    : TAF_PS_DSFLOW_RPT_IND_STRU
 结构说明  : ID_MSG_TAF_PS_DSFLOW_RPT_IND消息结构体, 流量上报信息
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件

  2.日    期   : 2011年12月23日
    作    者   : o00132663
    修改内容   : PS融合项目，流量上报结构使用新结构TAF_DSFLOW_REPORT_STRU

*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    TAF_DSFLOW_REPORT_STRU              stDsFlowRptInfo;
} TAF_PS_REPORT_DSFLOW_IND_STRU;


/*****************************************************************************
 描述 : 针对命令 ^APDSFLOWRPT
 ID   :

 REQ  :
 CNF  :
 IND  : -
 说明 : ...
*****************************************************************************/
/*****************************************************************************
 结构名称  : TAF_APDSFLOW_RPT_CFG_STRU
 结构说明  : AP流量上报配置结构体

  1.日    期   : 2015年2月2日
    作    者   : A00165503
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRptEnabled;       /* 流量上报开启标记   */
    VOS_UINT32                          ulFluxThreshold;    /* 流量上报门限, 单位KByte */
} TAF_APDSFLOW_RPT_CFG_STRU;


/*****************************************************************************
 结构名    : TAF_APDSFLOW_REPORT_STRU
 结构说明  : 流量信息上报结构定义

  1.日    期   : 2015年2月2日
    作    者   : A00165503
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCurrentTxRate;    /*当前发送速率*/
    VOS_UINT32                          ulCurrentRxRate;    /*当前接收速率*/
    TAF_DSFLOW_INFO_STRU                stCurrentFlowInfo;  /*当前连接流量信息*/
    TAF_DSFLOW_INFO_STRU                stTotalFlowInfo;    /*累计流量信息*/
} TAF_APDSFLOW_REPORT_STRU;


/*****************************************************************************
 结构名称  : TAF_PS_CONFIG_APDSFLOW_RPT_REQ_STRU
 结构说明  : ID_MSG_TAF_PS_SET_APDSFLOW_CFG_REQ消息结构体

  1.日    期   : 2015年2月2日
    作    者   : A00165503
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_APDSFLOW_RPT_CFG_STRU           stRptCfg;
} TAF_PS_SET_APDSFLOW_RPT_CFG_REQ_STRU;


/*****************************************************************************
 结构名称  : TAF_PS_SET_APDSFLOW_RPT_CFG_CNF_STRU
 结构说明  : ID_EVT_TAF_PS_SET_APDSFLOW_RPT_CFG_CNF消息结构体

  1.日    期   : 2015年2月2日
    作    者   : A00165503
    修改内容   : 新增结构
*****************************************************************************/
typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_APDSFLOW_RPT_CFG_CNF_STRU;


/*****************************************************************************
 结构名称  : TAF_PS_GET_APDSFLOW_RPT_CFG_REQ_STRU
 结构说明  : ID_MSG_TAF_PS_GET_APDSFLOW_RPT_CFG_REQ消息结构体

  1.日    期   : 2015年2月2日
    作    者   : A00165503
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_APDSFLOW_RPT_CFG_REQ_STRU;


/*****************************************************************************
 结构名称  : TAF_PS_GET_APDSFLOW_RPT_CFG_CNF_STRU
 结构说明  : ID_EVT_TAF_PS_GET_APDSFLOW_RPT_CFG_CNF消息结构体

  1.日    期   : 2015年2月2日
    作    者   : A00165503
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    TAF_APDSFLOW_RPT_CFG_STRU           stRptCfg;
} TAF_PS_GET_APDSFLOW_RPT_CFG_CNF_STRU;


/*****************************************************************************
 结构名称  : TAF_PS_APDSFLOW_REPORT_IND_STRU
 结构说明  : ID_EVT_TAF_PS_APDSFLOW_REPORT_IND消息结构体

  1.日    期   : 2015年2月2日
    作    者   : A00165503
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_APDSFLOW_REPORT_STRU            stApDsFlowRptInfo;
} TAF_PS_APDSFLOW_REPORT_IND_STRU;


/*****************************************************************************
 结构名称  : TAF_DSFLOW_NV_WRITE_CFG_STRU
 结构说明  : 流量写NV配置结构体

  1.日    期   : 2015年2月2日
    作    者   : A00165503
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnabled;          /* 流量写NV开启标记   */
    VOS_UINT8                           ucInterval;         /* 流量写NV周期, 单位min */
    VOS_UINT8                           aucReserved[2];     /* 保留字节 */
} TAF_DSFLOW_NV_WRITE_CFG_STRU;


/*****************************************************************************
 结构名称  : TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ_STRU
 结构说明  : ID_MSG_TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ消息结构体

  1.日    期   : 2015年2月12日
    作    者   : A00165503
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_DSFLOW_NV_WRITE_CFG_STRU        stNvWriteCfg;
} TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ_STRU;


/*****************************************************************************
 结构名称  : TAF_PS_SET_DSFLOW_NV_WRITE_CFG_CNF_STRU
 结构说明  : ID_EVT_TAF_PS_SET_DSFLOW_NV_WRITE_CFG_CNF消息结构体

  1.日    期   : 2015年2月12日
    作    者   : A00165503
    修改内容   : 新增结构
*****************************************************************************/
typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_DSFLOW_NV_WRITE_CFG_CNF_STRU;


/*****************************************************************************
 结构名称  : TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ_STRU
 结构说明  : ID_MSG_TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ消息结构体

  1.日    期   : 2015年2月12日
    作    者   : A00165503
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ_STRU;


/*****************************************************************************
 结构名称  : TAF_PS_GET_DSFLOW_NV_WRITE_CFG_CNF_STRU
 结构说明  : ID_EVT_TAF_PS_GET_DSFLOW_NV_WRITE_CFG_CNF消息结构体

  1.日    期   : 2015年2月12日
    作    者   : A00165503
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    TAF_DSFLOW_NV_WRITE_CFG_STRU        stNvWriteCfg;
} TAF_PS_GET_DSFLOW_NV_WRITE_CFG_CNF_STRU;

/*****************************************************************************
 结构名称  : TAF_PS_SET_CTA_INFO_REQ_STRU
 结构说明  : ID_MSG_TAF_PS_SET_1X_MAX_NO_DATA_TIME_LEN_REQ消息结构体

  1.日    期   : 2015年4月20日
    作    者   : c00299063
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT8                           ucPktCdataInactivityTmrLen;
    VOS_UINT8                           aucReserved[3];
}TAF_PS_SET_CTA_INFO_REQ_STRU;

/*****************************************************************************
 结构名称  : TAF_PS_GET_CTA_INFO_REQ_STRU
 结构说明  : ID_MSG_TAF_PS_GET_1X_MAX_NO_DATA_TIME_LEN_REQ消息结构体

  1.日    期   : 2015年4月20日
    作    者   : c00299063
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

}TAF_PS_GET_CTA_INFO_REQ_STRU;



/*****************************************************************************
 结构名称  : TAF_PS_SET_CTA_INFO_CNF_STRU
 结构说明  : ID_MSG_TAF_PS_SET_1X_MAX_NO_DATA_TIME_LEN_CNF消息结构体

  1.日    期   : 2015年4月20日
    作    者   : c00299063
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    VOS_UINT32                          ulRslt;

}TAF_PS_SET_CTA_INFO_CNF_STRU;

/*****************************************************************************
 结构名称  : TAF_PS_GET_CTA_INFO_CNF_STRU
 结构说明  : ID_MSG_TAF_PS_GET_1X_MAX_NO_DATA_TIME_LEN_CNF消息结构体

  1.日    期   : 2015年4月20日
    作    者   : c00299063
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    VOS_UINT32                          ulRslt;

    VOS_UINT8                           ucPktCdataInactivityTmrLen;
    VOS_UINT8                           aucReserved[3];

}TAF_PS_GET_CTA_INFO_CNF_STRU;


/*****************************************************************************
 结构名称  : TAF_PS_GET_CGMTU_VALUE_REQ_STRU
 结构说明  : ID_MSG_TAF_PS_GET_CGMTU_VALUE_REQ消息结构体

  1.日    期   : 2015年5月24日
    作    者   : g00261581
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
}TAF_PS_GET_CGMTU_VALUE_REQ_STRU;

/*****************************************************************************
 结构名称  : TAF_PS_GET_CGMTU_VALUE_CNF_STRU
 结构说明  : ID_EVT_TAF_PS_GET_CGMTU_VALUE_CNF消息结构体

  1.日    期   : 2015年5月24日
    作    者   : g00261581
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    VOS_UINT32                          ulMtuValue;
}TAF_PS_GET_CGMTU_VALUE_CNF_STRU;

/*****************************************************************************
 结构名称  : TAF_PS_CGMTU_VALUE_CHG_IND_STRU
 结构说明  : ID_EVT_TAF_PS_CGMTU_VALUE_CHG_IND消息结构体

  1.日    期   : 2015年5月24日
    作    者   : g00261581
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    VOS_UINT32                          ulMtuValue;
}TAF_PS_CGMTU_VALUE_CHG_IND_STRU;


/*****************************************************************************
 描述 : 针对命令 ^CGAUTH
 ID   :

 REQ  :
 CNF  :
 IND  : -
 说明 : ...
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpAuth           : 1;
    VOS_UINT32                          bitOpUserName       : 1;
    VOS_UINT32                          bitOpPassword       : 1;
    VOS_UINT32                          bitOpSpare          : 29;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucDefined;          /* 0:undefined, 1:defined */
    VOS_UINT8                           ucAuth;             /* 目前仅支持是否鉴权，以后扩充为支持哪种鉴权算法*/
    VOS_UINT8                           aucReserved[1];
    VOS_UINT8                           aucUserName[TAF_MAX_PDP_AUTH_USERNAME_LEN + 1];
    VOS_UINT8                           aucPassWord[TAF_MAX_PDP_AUTH_PASSCODE_LEN + 1];
} TAF_PDP_AUTH_EXT_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PDP_AUTH_EXT_STRU               stPdpAuthInfo;
} TAF_PS_SET_PDP_AUTH_INFO_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_PDP_AUTH_INFO_CNF_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_PDP_AUTH_INFO_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_AUTH_QUERY_INFO_STRU            astPdpAuthQueryInfo[0];
} TAF_PS_GET_PDP_AUTH_INFO_CNF_STRU;


/*****************************************************************************
 描述 : 针对命令 ^CGDNS
 ID   :

 REQ  :
 CNF  :
 IND  : -
 说明 : ...
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPrimDnsAddr    : 1;
    VOS_UINT32                          bitOpSecDnsAddr     : 1;
    VOS_UINT32                          bitOpSpare          : 30;

    VOS_UINT8                           ucCid;              /* [1，11] 如果仅包含此参数，表示删除该Cid的DNS */
    VOS_UINT8                           ucDefined;          /* 0:undefined, 1:defined */
    VOS_UINT8                           aucReserved[2];
    VOS_UINT8                           aucPrimDnsAddr[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecDnsAddr[TAF_IPV4_ADDR_LEN];
} TAF_PDP_DNS_EXT_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PDP_DNS_EXT_STRU                stPdpDnsInfo;
} TAF_PS_SET_PDP_DNS_INFO_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_PDP_DNS_INFO_CNF_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_PDP_DNS_INFO_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_DNS_QUERY_INFO_STRU             astPdpDnsQueryInfo[0];
} TAF_PS_GET_PDP_DNS_INFO_CNF_STRU;


/*****************************************************************************
 描述 : 针对命令 ^TRIG
 ID   :

 REQ  :
 CNF  :
 IND  : -
 说明 : ...
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMode;
    VOS_UINT8                           ucNsapi;
    VOS_UINT8                           ucTimes;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulMillisecond;
} TAF_GPRS_DATA_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_GPRS_DATA_STRU                  stGprsDataInfo;
} TAF_PS_TRIG_GPRS_DATA_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_TRIG_GPRS_DATA_CNF_STRU;


/*****************************************************************************
 描述 : 针对命令 ^DWINS
 ID   :

 REQ  :
 CNF  :
 IND  : -
 说明 : ...
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    /* 0:disabled, 1:enabled */
    VOS_UINT32                          ulEnabled;
} TAF_PS_CONFIG_NBNS_FUNCTION_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_CONFIG_NBNS_FUNCTION_CNF_STRU;


/*****************************************************************************
 结构名称  : TAF_PS_DIAL_PARA_STRU
 结构说明  : 拨号参数
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpAuthType       : 1;
    VOS_UINT32                          bitOpApn            : 1;
    VOS_UINT32                          bitOpIpAddr         : 1;
    VOS_UINT32                          bitOpUserName       : 1;
    VOS_UINT32                          bitOpPassWord       : 1;
    VOS_UINT32                          bitOpReqType        : 1;
    VOS_UINT32                          bitOpPdpDcomp       : 1;
    VOS_UINT32                          bitOpPdpHcomp       : 1;
    VOS_UINT32                          bitOpIpv4AddrAlloc  : 1;
    VOS_UINT32                          bitOpEmergencyInd   : 1;
    VOS_UINT32                          bitOpPcscfDiscovery : 1;
    VOS_UINT32                          bitOpImCnSignalFlg  : 1;
    VOS_UINT32                          bitOpSpare          : 20;

    /* connect id [1, 20] */
    VOS_UINT8                           ucCid;

    /* 0 - no auth */
    /* 1 - PAP */
    /* 2 - CHAP */
    /* 3 - MS_CHAP_V2 */
    TAF_PDP_AUTH_TYPE_ENUM_UINT8        enAuthType;

    /* 0 - IPv4 */
    /* 1 - IPv6 */
    /* 2 - IPv4v6 */
    /* 3 - PPP */
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;

    /* 1 - initial request */
    /* 2 - Handover */
    /* 3 - Unused. If received, the network shall interpret this as "initial request". */
    /* 4 - emergency */
    TAF_PDP_REQUEST_TYPE_ENUM_UINT8     enPdpRequestType;

    /* access point name string with '\0' end */
    VOS_UINT8                           aucApn[TAF_MAX_APN_LEN + 1];

    /* staitc address if needed */
    TAF_PDP_ADDR_STRU                   stPdpAddr;

    /* user name string with '\0' end */
    VOS_UINT8                           aucUserName[TAF_MAX_GW_AUTH_USERNAME_LEN + 1];

    /* user name string with '\0' end */
    VOS_UINT8                           aucPassWord[TAF_MAX_GW_AUTH_PASSWORD_LEN + 1];

    /* 0 - off (default if value is omitted) */
    /* 1 - on (manufacturer preferred compression) */
    /* 2 - V.42bis */
    /* 3 - V.44 */
    TAF_PDP_D_COMP_ENUM_UINT8           enPdpDcomp;

    /* 0 - off (default if value is omitted) */
    /* 1 - on (manufacturer preferred compression) */
    /* 2 - RFC1144 (applicable for SNDCP only) */
    /* 3 - RFC2507 */
    /* 4 - RFC3095 (applicable for PDCP only) */
    TAF_PDP_H_COMP_ENUM_UINT8           enPdpHcomp;

    /* 0 - IPv4 Address Allocation through NAS Signaling (default if omitted) */
    /* 1 - IPv4 Address Allocated through DHCP */
    TAF_PDP_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT8 enIpv4AddrAlloc;

    /* 0 - PDP context is not for emergency bearer services */
    /* 1 - PDP context is for emergency bearer services */
    TAF_PDP_EMC_IND_ENUM_UINT8          enEmergencyInd;

    /* 0 - Preference of P-CSCF address discovery not influenced by +CGDCONT */
    /* 1 - Preference of P-CSCF address discovery through NAS Signalling */
    /* 2 - Preference of P-CSCF address discovery through DHCP */
    TAF_PDP_PCSCF_DISCOVERY_ENUM_UINT8  enPcscfDiscovery;

    /* 0 - UE indicates that the PDP context is not for IM CN subsystem-related signalling only */
    /* 1 - UE indicates that the PDP context is for IM CN subsystem-related signalling only */
    TAF_PDP_IM_CN_SIG_FLAG_ENUM_UINT8   enImCnSignalFlg;

    VOS_UINT8                           aucReserved[2];

} TAF_PS_DIAL_PARA_STRU;

/*****************************************************************************
 结构名    : TAF_PS_CALL_ORIG_REQ_STRU
 结构说明  : ID_MSG_TAF_PS_CALL_ORIG_REQ消息结构
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_DIAL_PARA_STRU               stDialParaInfo;
} TAF_PS_CALL_ORIG_REQ_STRU;

/*****************************************************************************
 结构名    : TAF_PS_CALL_END_REQ_STRU
 结构说明  : ID_MSG_TAF_PS_GET_DIAL_PARA_INFO_CNF事件结构

 修改历史      :
  1.日    期   : 2011年08月22日
    作    者   : A00165503
    修改内容   : 新增结构

  2.日    期   : 2012年8月23日
    作    者   : A00165503
    修改内容   : 修改成员
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
    TAF_PS_CAUSE_ENUM_UINT32            enCause;
} TAF_PS_CALL_ORIG_CNF_STRU;

/*****************************************************************************
 结构名    : TAF_PS_CALL_END_REQ_STRU
 结构说明  : ID_MSG_TAF_PS_CALL_END_REQ消息结构, 挂断PS CALL
1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
} TAF_PS_CALL_END_REQ_STRU;

/*****************************************************************************
 结构名称: TAF_PS_CALL_END_CNF_STRU
 结构说明: ID_MSG_TAF_PS_CALL_END_CNF消息结构
           断开呼叫正常 - enCause为TAF_PS_CAUSE_SUCCESS
           断开呼叫异常 - enCause为TAF_PS_CAUSE_CID_INVALID
                          指定的CID没有对应的呼叫实体激活
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
    TAF_PS_CAUSE_ENUM_UINT32            enCause;

} TAF_PS_CALL_END_CNF_STRU;

/*****************************************************************************
 描述 : 针对命令 ^AUTHDATA
 ID   : ID_MSG_TAF_PS_SET_AUTHDATA_INFO_REQ
      : ID_MSG_TAF_PS_SET_AUTHDATA_INFO_CNF
      : ID_MSG_TAF_PS_GET_AUTHDATA_INFO_REQ
      : ID_MSG_TAF_PS_GET_AUTHDATA_INFO_CNF
 REQ  : TAF_PS_SET_AUTHDATA_INFO_REQ_STRU; TAF_PS_GET_AUTHDATA_INFO_REQ_STRU
 CNF  : TAF_PS_SET_AUTHDATA_INFO_CNF_STRU; TAF_PS_GET_AUTHDATA_INFO_CNF_STRU
 说明 : ...
*****************************************************************************/
/*****************************************************************************
 结构名    : TAF_PDP_AUTHDATA_EXT_STRU
 结构说明  : 鉴权参数(NDIS)
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpAuthType       : 1;
    VOS_UINT32                          bitOpPlmn           : 1;
    VOS_UINT32                          bitOpPassWord       : 1;
    VOS_UINT32                          bitOpUserName       : 1;
    VOS_UINT32                          bitOpSpare          : 28;

    VOS_UINT8                           ucDefined;          /* 0:undefined, 1:defined */
    VOS_UINT8                           ucCid;
    TAF_PDP_AUTH_TYPE_ENUM_UINT8        enAuthType;
    VOS_UINT8                           aucReserved1[1];
    VOS_UINT8                           aucPlmn[TAF_MAX_AUTHDATA_PLMN_LEN + 1];
    VOS_UINT8                           aucReserved2[1];
    VOS_UINT8                           aucPassWord[TAF_MAX_AUTHDATA_USERNAME_LEN + 1];
    VOS_UINT8                           aucUserName[TAF_MAX_AUTHDATA_PASSWORD_LEN + 1];
} TAF_AUTHDATA_EXT_STRU;

/*****************************************************************************
 结构名    : TAF_PS_SET_AUTHDATA_INFO_REQ_STRU
 结构说明  : ID_MSG_TAF_PS_SET_AUTHDATA_INFO_REQ消息结构体, 设置鉴权参数(NDIS)
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_AUTHDATA_EXT_STRU               stAuthDataInfo;
} TAF_PS_SET_AUTHDATA_INFO_REQ_STRU;

/*****************************************************************************
 结构名    : TAF_PS_SET_AUTHDATA_INFO_CNF_STRU
 结构说明  : ID_MSG_TAF_PS_SET_AUTHDATA_INFO_CNF消息结构体, 设置鉴权参数(NDIS)
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_AUTHDATA_INFO_CNF_STRU;

/*****************************************************************************
 结构名    : TAF_PS_GET_AUTHDATA_INFO_REQ_STRU
 结构说明  : ID_MSG_TAF_PS_GET_AUTHDATA_INFO_REQ消息结构体, 获取鉴权参数(NDIS)
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_AUTHDATA_INFO_REQ_STRU;

/*****************************************************************************
 结构名    : TAF_PS_GET_AUTHDATA_INFO_CNF_STRU
 结构说明  : ID_EVT_TAF_PS_GET_AUTHDATA_INFO_CNF消息结构体, 获取鉴权参数(NDIS)
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_AUTHDATA_QUERY_INFO_STRU        astAuthDataQueryInfo[0];
} TAF_PS_GET_AUTHDATA_INFO_CNF_STRU;


/*****************************************************************************
 描述 : 针对命令 D
 ID   : ID_MSG_TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ
      : ID_EVT_TAF_PS_GET_D_GPRS_ACTIVE_TYPE_CNF
      :
      :
 REQ  : TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU
 CNF  : TAF_PS_GET_D_GPRS_ACTIVE_TYPE_CNF_STRU
 说明 : ...
*****************************************************************************/

/*****************************************************************************
 结构名    : TAF_ATD_PARA_STRU
 结构说明  : D命令拨号参数
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpL2p            : 1;
    VOS_UINT32                          bitOpSpare          : 31;

    VOS_UINT8                           ucCid;
    TAF_L2P_TYPE_ENUM_UINT8             enL2p;
    VOS_UINT8                           aucReserved[2];
} TAF_ATD_PARA_STRU;

/*****************************************************************************
 结构名    : TAF_CID_GPRS_ACTIVE_TYPE_STRU
 结构说明  : CID对应的GPRS激活类型
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;
    TAF_GPRS_ACTIVE_TYPE_UINT8          enActiveType;
    VOS_UINT8                           aucReserved[2];
} TAF_CID_GPRS_ACTIVE_TYPE_STRU;

/*****************************************************************************
 结构名    : TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU
 结构说明  : ID_MSG_TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ消息结构体, 获取D命令GPRS类型
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_ATD_PARA_STRU                   stAtdPara;
} TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU;

/*****************************************************************************
 结构名    : TAF_PS_GET_D_GPRS_ACTIVE_TYPE_CNF_STRU
 结构说明  : ID_EVT_TAF_PS_GET_D_GPRS_ACTIVE_TYPE_CNF消息结构体, 获取D命令GPRS类型
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    TAF_CID_GPRS_ACTIVE_TYPE_STRU       stCidGprsActiveType;
} TAF_PS_GET_D_GPRS_ACTIVE_TYPE_CNF_STRU;


/*****************************************************************************
 结构名称: TAF_PPP_AUTH_PAP_CONTENT_STRU
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPapReqLen;                            /*request长度: 24.008要求在[3,253]字节*/
    VOS_UINT8                           aucReserve[2];                          /* 对齐保留 */
    VOS_UINT8                           aucPapReqBuf[TAF_PPP_PAP_REQ_MAX_LEN];  /*request*/
} TAF_PPP_AUTH_PAP_CONTENT_STRU;

/*****************************************************************************
 结构名称: TAF_PPP_AUTH_CHAP_CONTENT_STRU
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usChapChallengeLen;                     /*challenge长度: 24.008要求在[3,253]字节*/
    VOS_UINT16                          usChapResponseLen;                      /*response长度: 24.008要求在[3,253]字节*/
    VOS_UINT8                           aucChapChallengeBuf[TAF_PPP_CHAP_CHALLENGE_MAX_LEN];    /*challenge,153B*/
    VOS_UINT8                           aucChapResponseBuf[TAF_PPP_CHAP_RESPONSE_MAX_LEN];      /*response,205B*/
    VOS_UINT8                           aucReserve[2];                          /* 对齐保留 */
} TAF_PPP_AUTH_CHAP_CONTENT_STRU;

/*****************************************************************************
 结构名称: TAF_PPP_REQ_AUTH_CONFIG_INFO_STRU
 结构说明:
*****************************************************************************/
typedef struct
{
    TAF_PDP_AUTH_TYPE_ENUM_UINT8        enAuthType;
    VOS_UINT8                           aucReserve[3];

    union
    {
        TAF_PPP_AUTH_PAP_CONTENT_STRU   stPapContent;
        TAF_PPP_AUTH_CHAP_CONTENT_STRU  stChapContent;
    } enAuthContent;

} TAF_PPP_REQ_AUTH_CONFIG_INFO_STRU;

/*****************************************************************************
 结构名称: TAF_PPP_REQ_CONFIG_INFO_STRU
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usIpcpLen;                              /*Ipcp帧长度*/
    VOS_UINT8                           aucReserve[2];                          /* 对齐保留 */
    VOS_UINT8                           aucIpcp[TAF_PPP_IPCP_FRAME_BUF_MAX_LEN];/*Ipcp帧*/
} TAF_PPP_REQ_IPCP_CONFIG_INFO_STRU;

/*****************************************************************************
 结构名称: TAF_PPP_REQ_CONFIG_INFO_STRU
 结构说明:
*****************************************************************************/
typedef struct
{
    TAF_PPP_REQ_AUTH_CONFIG_INFO_STRU   stAuth;
    TAF_PPP_REQ_IPCP_CONFIG_INFO_STRU   stIPCP;
} TAF_PPP_REQ_CONFIG_INFO_STRU;

/*****************************************************************************
 描述 : 针对PPP拨号
 ID   : ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ
      : ID_EVT_TAF_PS_PPP_DIAL_ORIG_CNF
      :
      :
 REQ  : TAF_PS_PPP_DIAL_ORIG_REQ_STRU
 CNF  : TAF_PS_PPP_DIAL_ORIG_CNF_STRU
 说明 : ...
*****************************************************************************/
/*****************************************************************************
 结构名    : TAF_PS_PPP_DIAL_ORIG_REQ_STRU
 结构说明  : ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息结构体, PPP拨号
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPppConfigInfo  : 1;
    VOS_UINT32                          bitOpSpare          : 31;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
    TAF_PPP_REQ_CONFIG_INFO_STRU        stPppReqConfigInfo;
} TAF_PPP_DIAL_PARA_STRU;

/*****************************************************************************
 结构名    : TAF_PS_PPP_DIAL_ORIG_REQ_STRU
 结构说明  : ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息结构体, PPP拨号
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PPP_DIAL_PARA_STRU              stPppDialParaInfo;
} TAF_PS_PPP_DIAL_ORIG_REQ_STRU;

/*****************************************************************************
 结构名    : TAF_PS_PPP_DIAL_ORIG_CNF_STRU
 结构说明  : ID_EVT_TAF_PS_PPP_DIAL_ORIG_CNF事件结构

 修改历史      :
  1.日    期   : 2011年10月19日
    作    者   : A00165503
    修改内容   : 创建文件

  2.日    期   : 2012年8月23日
    作    者   : A00165503
    修改内容   : 修改成员
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
} TAF_PS_PPP_DIAL_ORIG_CNF_STRU;

/*****************************************************************************
结构名    : TAF_PDP_IPV6_PREFIX_STRU
结构说明  : IPV6 前缀信息结构
  1.日    期   : 2011年12月24日
    作    者   : 陈志敏/c00173809
    修改内容   : 定义结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBitL          :1;                     /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ulBitA          :1;
    VOS_UINT32                          ulBitPrefixLen  :8;
    VOS_UINT32                          ulBitRsv        :22;

    VOS_UINT32                          ulValidLifeTime;
    VOS_UINT32                          ulPreferredLifeTime;
    VOS_UINT8                           aucPrefix[TAF_IPV6_ADDR_LEN];
}TAF_PDP_IPV6_PREFIX_STRU;

/*****************************************************************************
结构名    : TAF_PDP_IPV6_RA_INFO_STRU
结构说明  : IPV6 RA参数结构
  1.日    期   : 2011年12月24日
    作    者   : 陈志敏/c00173809
    修改内容   : 定义结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpMtu            :1;
    VOS_UINT32                          bitOpSpare          :31;

    VOS_UINT32                          ulBitCurHopLimit    :8;
    VOS_UINT32                          ulBitM              :1;
    VOS_UINT32                          ulBitO              :1;
    VOS_UINT32                          ulBitRsv            :22;

    VOS_UINT32                          ulMtu;                                  /* MTU大小 */
    VOS_UINT32                          ulPrefixNum;                            /* IPV6地址前缀个数 */
    TAF_PDP_IPV6_PREFIX_STRU            astPrefixList[TAF_MAX_PREFIX_NUM_IN_RA];/* IPV6地址前缀数组 */

} TAF_PDP_IPV6_RA_INFO_STRU;


/*****************************************************************************
结构名    : TAF_PS_IPV6_INFO_IND_STRU
结构说明  : ID_EVT_TAF_PS_IPV6_INFO_IND事件结构体
  1.日    期   : 2011年12月24日
    作    者   : 陈志敏/c00173809
    修改内容   : 定义结构

  2.日    期   : 2012年6月30日
    作    者   : A00165503
    修改内容   : DTS2012062900707: IPv6拨号成功, 应用获取IPv6地址前缀异常
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           aucReserved[2];
    TAF_PDP_IPV6_RA_INFO_STRU           stIpv6RaInfo;

} TAF_PS_IPV6_INFO_IND_STRU;

/*****************************************************************************
 结构名    : TAF_PS_GET_NEGOTIATION_DNS_REQ_STRU
 结构说明  : ID_MSG_TAF_PS_GET_NEGOTIATION_DNS_REQ事件结构体
   1.日    期   : 2012年02月17日
     作    者   : l00198894
     修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
} TAF_PS_GET_NEGOTIATION_DNS_REQ_STRU;

/*****************************************************************************
 结构名    : TAF_PS_GET_NEGOTIATION_DNS_CNF_STRU
 结构说明  : ID_EVT_TAF_PS_GET_NEGOTIATION_DNS_CNF事件结构体
   1.日    期   : 2012年02月17日
     作    者   : l00198894
     修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    TAF_DNS_QUERY_INFO_STRU             stNegotiationDns;
} TAF_PS_GET_NEGOTIATION_DNS_CNF_STRU;


#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
结构名    : TAF_PH_LTECS_STRU
结构说明  : ^LTECS命令LPS返回的信息
  1.日    期   : 2012年04月22日
    作    者   : h00135900
    修改内容   : AT 融合新增结构体说明
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSG;
    VOS_UINT8                           ucIMS;
    VOS_UINT8                           ucCSFB;
    VOS_UINT8                           ucVCC;
    VOS_UINT8                           ucVoLGA;
    VOS_UINT8                           aucReserved[3];
}TAF_PH_LTECS_STRU;

/*****************************************************************************
结构名    : TAF_PH_LTECS_STRU
结构说明  : ^LTECS命令PS返回的信息
  1.日    期   : 2012年04月22日
    作    者   : h00135900
    修改内容   : AT 融合新增结构体说明
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
}TAF_PS_LTECS_REQ_STRU;

/*****************************************************************************
结构名    : TAF_PS_LTECS_CNF_STRU
结构说明  : ^LTECS命令TAF返回给AT 模块的消息格式
  1.日    期   : 2012年04月22日
    作    者   : h00135900
    修改内容   : AT 融合新增结构体说明
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    TAF_PH_LTECS_STRU                   stLteCs;
}TAF_PS_LTECS_CNF_STRU;


/*****************************************************************************
结构名    : TAF_PH_CEMODE_STRU
结构说明  : ^CEMODE命令PS返回的信息
  1.日    期   : 2012年04月22日
    作    者   : h00135900
    修改内容   : AT 融合新增结构体说明
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          enCurrentUeMode;                        /*当前UE模式*/
    VOS_UINT32                          ulSupportModeCnt;                       /*UE能够支持的模式的个数*/
    VOS_UINT32                          aenSupportModeList[4];                  /*UE能够支持的模式*/
}TAF_PH_CEMODE_STRU;

/*****************************************************************************
结构名    : TAF_PS_CEMODE_REQ_STRU
结构说明  : ^CEMODE命令请求消息结构
  1.日    期   : 2012年04月22日
    作    者   : h00135900
    修改内容   : AT 融合新增结构体说明
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
}TAF_PS_CEMODE_REQ_STRU;

/*****************************************************************************
结构名    : TAF_PS_CEMODE_CNF_STRU
结构说明  : ^CEMODE命令回复命令格式
  1.日    期   : 2012年04月22日
    作    者   : h00135900
    修改内容   : AT 融合新增结构体说明
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    TAF_PH_CEMODE_STRU                  stCemode;
}TAF_PS_CEMODE_CNF_STRU;



/* DTS2012031901936            : x00126983 2012-3-19 字节对齐 + */
/*****************************************************************************
 结构名    : TAF_PDP_PROFILE_EXT_STRU
 结构说明  : ^PDPROFMOD命令参数
 日    期 : 2012年3月12日
 作    者 : x00126983
 修改内容 : 创建文件
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPdpType        : 1;                /* PdpType*/
    VOS_UINT32                          bitOpApn            : 1;                /* aucApn*/
    VOS_UINT32                          bitOpUsername       : 1;                /* AuthUsername*/
    VOS_UINT32                          bitOpPassword       : 1;                /* AuthPassword*/
    VOS_UINT32                          bitOpAuthType       : 1;                /* AuthType*/
    VOS_UINT32                          bitOpSpare          : 27;

    VOS_UINT8                           ucDefined;                              /* 0:undefined, 1:defined */

    VOS_UINT8                           ucCid;

    /* 1 IP Internet Protocol (IETF STD 5)*/
    /* 2 IPV6 Internet Protocol, version 6 (IETF RFC 2460)*/
    /* 3 IPV4V6 Virtual <PDP_type> introduced to handle dual IP stack UE capability. (See 3GPP TS 24.301 [83])*/
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;

    VOS_UINT8                           aucReserved1[1];

    /* Access Point Name*/
    VOS_UINT8                           aucApn[TAF_MAX_APN_LEN + 1];

    VOS_UINT8                           aucPassWord[TAF_MAX_AUTHDATA_PASSWORD_LEN + 1];
    VOS_UINT8                           aucUserName[TAF_MAX_AUTHDATA_USERNAME_LEN + 1];
    VOS_UINT8                           ucAuthType;
    VOS_UINT8                           aucReserved2[3];

}TAF_PDP_PROFILE_EXT_STRU;
/* DTS2012031901936            : x00126983 2012-3-19 字节对齐 - */

/*****************************************************************************
 结构名    : TAF_PS_SET_PROFILE_INFO_REQ_STRU
 结构说明  : ID_MSG_TAF_PS_SET_AUTHDATA_INFO_REQ消息结构体, 设置鉴权参数(NDIS)
 1.日    期   : 2011年10月19日
   作    者   : A00165503
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PDP_PROFILE_EXT_STRU            stPdpProfInfo;
} TAF_PS_SET_PROFILE_INFO_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_PDP_PROF_INFO_CNF_STRU;

#endif

/*****************************************************************************
 结构名称: TAF_GW_AUTH_STRU
 结构说明: 网关鉴权参数结构体
*****************************************************************************/
typedef struct
{
    TAF_PDP_AUTH_TYPE_ENUM_UINT8        enAuthType;
    VOS_UINT8                           ucAccNumLen;
    VOS_UINT8                           aucReserved[2];
    VOS_UINT8                           auAccessNum[TAF_MAX_ACCESS_NUM_LEN];
    VOS_UINT8                           ucUserNameLen;
    VOS_UINT8                           aucUserName[TAF_MAX_GW_AUTH_USERNAME_LEN];
    VOS_UINT8                           ucPwdLen;
    VOS_UINT8                           aucPwd[TAF_MAX_GW_AUTH_PASSWORD_LEN];

} TAF_GW_AUTH_STRU;


/*****************************************************************************
 结构名称: TAF_SDF_PARA_STRU
 结构说明: SDF参数结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpLinkdCid       : 1;
    VOS_UINT32                          bitOpPdnType        : 1;
    VOS_UINT32                          bitOpApn            : 1;
    VOS_UINT32                          bitOpUmtsQos        : 1;
    VOS_UINT32                          bitOpEpsQos         : 1;
    VOS_UINT32                          bitOpGwAuthInfo     : 1;
    VOS_UINT32                          bitOpEmergencyInd   : 1;
    VOS_UINT32                          bitOpIpv4AddrAllocType: 1;
    VOS_UINT32                          bitOpPcscfDiscovery : 1;
    VOS_UINT32                          bitOpImCnSignalFlg  : 1;
    VOS_UINT32                          bitOpImsSuppFlg     : 1;
    VOS_UINT32                          bitOpSpare          : 21;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucLinkdCid;
    TAF_PDP_TYPE_ENUM_UINT8             enPdnType;
    TAF_PDP_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT8 enIpv4AddrAllocType;

    TAF_PDP_EMC_IND_ENUM_UINT8          enEmergencyInd;
    TAF_PDP_PCSCF_DISCOVERY_ENUM_UINT8  enPcscfDiscovery;
    TAF_PDP_IM_CN_SIG_FLAG_ENUM_UINT8   enImCnSignalFlg;
    VOS_UINT8                           ucPfNum;
    VOS_UINT8                           ucImsSuppFlg;
    VOS_UINT8                           aucReserved[3];

    TAF_UMTS_QOS_STRU                   stUmtsQosInfo;
    TAF_EPS_QOS_STRU                    stEpsQosInfo;
    TAF_PDP_APN_STRU                    stApnInfo;
    TAF_GW_AUTH_STRU                    stGwAuthInfo;
    TAF_PDP_PF_STRU                     astCntxtTftInfo[TAF_MAX_SDF_PF_NUM];

}TAF_SDF_PARA_STRU;


/*****************************************************************************
 结构名称: TAF_SDF_PARA_QUERY_INFO_STRU
 结构说明: SDF配置参数查询结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSdfNum;
    TAF_SDF_PARA_STRU                   astSdfPara[TAF_MAX_CID_NV];

} TAF_SDF_PARA_QUERY_INFO_STRU;

/*****************************************************************************
结构名    : TAF_SDF_PARA_QUERY_INFO_STRU
结构说明  : SDF配置参数异步查询结构体
  1.日    期   : 2013年07月22日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目新增
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
}TAF_PS_SDF_INFO_REQ_STRU;


/*****************************************************************************
结构名    : TAF_PS_SDF_INFO_CNF_STRU
结构说明  : SDF配置参数异步查询结构体
  1.日    期   : 2013年07月22日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目新增
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_SDF_PARA_QUERY_INFO_STRU        stSdfInfo;
}TAF_PS_SDF_INFO_CNF_STRU;


/*****************************************************************************
 结构名    : TAF_PS_PDP_QOS_QUERY_PARA_STRU
 结构说明  : QOS查询参数集，包括QOS参数、MIN QOS参数
 1.日    期   : 2013年06月29日
   作    者   : l60609
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucQosFlag;                              /* 0：Qos表无效，1：Qos表有效 */
    VOS_UINT8                           ucMinQosFlag;                           /* 0:定义了最小可接受Qos,1:没有最小可接受Qos */
    VOS_UINT8                           aucReserved[2];

    TAF_UMTS_QOS_STRU                   stQos;                                  /* Qos表 */
    TAF_UMTS_QOS_STRU                   stMinQos;                               /* MINQos表 */
}TAF_PS_PDP_QOS_QUERY_PARA_STRU;

/*****************************************************************************
 结构名    : TAF_PS_PDP_QOS_SET_PARA_STRU
 结构说明  : QOS查询参数集，包括QOS参数、MIN QOS参数
 1.日    期   : 2013年06月29日
   作    者   : l60609
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    TAF_UMTS_QOS_EXT_STRU               stQos;                                  /* Qos表 */
    TAF_UMTS_QOS_EXT_STRU               stMinQos;                               /* MINQos表 */
}TAF_PS_PDP_QOS_SET_PARA_STRU;


#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 结构名称: TAF_SRVCC_CANCEL_NOTIFY_IND_STRU
 结构说明: APS->IMSA通知SRVCC CANECL
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                           stCtrl;
    TAF_SRVCC_CANCEL_NOTIFY_ENUM_UINT32     enNotificationIndicator;
}TAF_SRVCC_CANCEL_NOTIFY_IND_STRU;
#endif

/******************************************************************************
 结构名    : TAF_PS_SET_1X_CQOS_PRI_REQ_STRU
 结构说明  : 配置CDMA QOS请求结构体
   1.日    期   : 2013年10月15日
     作    者   : Y00213812
     修改内容   : CDMA 1X 项目新增
 *******************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                                           stCtrl;
    TAF_PS_CDATA_1X_QOS_NON_ASSURED_PRI_ENUM_UINT8          enPri;
    VOS_UINT8                                               aucReserved[3];
}TAF_PS_SET_1X_CQOS_PRI_REQ_STRU;

/******************************************************************************
 结构名    : TAF_PS_SET_CQOS_PRI_CNF_STRU
 结构说明  : 配置CDMA QOS结果结构体
   1.日    期   : 2013年10月15日
     作    者   : Y00213812
     修改内容   : CDMA 1X 项目新增
 *******************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    VOS_UINT32                          ulRslt;
}TAF_PS_SET_CQOS_PRI_CNF_STRU;

/** ****************************************************************************
 结构名    : TAF_PS_CALL_DORMANT_IND_STRU
 结构说明  : CDMA模式下数据服务进入DORMANT状态结构体
   1.日    期   : 2013年10月15日
     作    者   : Y00213812
     修改内容   : CDMA 1X 项目新增
 *******************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           aucReserved[2];
}TAF_PS_CALL_DORMANT_IND_STRU;

/** ****************************************************************************
 * Name        : APS_APS_ENTER_DORMANT_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* _H2ASN_Skip */
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           aucReserved[3];
}TAF_PS_CALL_ENTER_DORMANT_IND_STRU;


/** ****************************************************************************
 * Name        : TAF_PS_HAI_CHANGE_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* _H2ASN_Skip */
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           aucReserved[3];
}TAF_PS_HAI_CHANGE_IND_STRU;


/** ****************************************************************************
 * Name        : TAF_PS_CDMA_DIAL_MODE_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                          stCtrl;


    TAF_PS_CDATA_DIAL_MODE_ENUM_UINT32    enDialMode;
}TAF_PS_CDATA_DIAL_MODE_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_CDATA_DIAL_MODE_CNF_STRU;

/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    TAF_PS_MSG_ID_ENUM_UINT32           ulMsgId;                                /*_H2ASN_MsgChoice_Export TAF_PS_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_PS_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_PS_MSG_REQ;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    TAF_PS_MSG_REQ                      stMsgReq;
}TafApsApi_MSG;

typedef struct
{
    TAF_PS_EVT_ID_ENUM_UINT32           ulEvtId;                                /*_H2ASN_MsgChoice_Export TAF_PS_EVT_ID_ENUM_UINT32*/
    VOS_UINT8                           aucEvtBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_PS_EVT_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_PS_EVT_CNF;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    TAF_PS_EVT_CNF                      stEvtCnf;
}TafApsApi_EVT;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/



/*****************************************************************************
  10 函数声明
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_PS_SetPrimPdpContextInfo
 功能描述  : 设置Primary PDP上下文信息
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstPdpContextInfo          - Primary PDP上下文信息
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_SetPrimPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpContextInfo
);

/*****************************************************************************
 函 数 名  : TAF_PS_GetPrimPdpContextInfo
 功能描述  : 获取Primary PDP上下文信息
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetPrimPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 函 数 名  : TAF_PS_GetPdpContextInfo
 功能描述  : 获取PDP上下文信息
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);
/*****************************************************************************
 函 数 名  : TAF_PS_SetSecPdpContextInfo
 功能描述  : 设置Secondary PDP上下文信息
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstPdpContextInfo          - Secondary PDP上下文信息
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_SetSecPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PDP_SEC_CONTEXT_EXT_STRU       *pstPdpContextInfo
);

/*****************************************************************************
 函 数 名  : TAF_PS_GetSecPdpContextInfo
 功能描述  : 获取Secondary PDP上下文信息
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetSecPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 函 数 名  : TAF_PS_SetTftInfo
 功能描述  : 设置PDP TFT参数
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstTftInfo                 - TFT参数
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_SetTftInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_TFT_EXT_STRU                   *pstTftInfo
);

/*****************************************************************************
 函 数 名  : TAF_PS_GetTftInfo
 功能描述  : 获取PDP TFT参数
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetTftInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 函 数 名  : TAF_PS_SetUmtsQosInfo
 功能描述  : 设置UMTS QOS参数信息
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstUmtsQosInfo             - UMTS QOS参数
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_SetUmtsQosInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_UMTS_QOS_EXT_STRU              *pstUmtsQosInfo
);

/*****************************************************************************
 函 数 名  : TAF_PS_GetUmtsQosInfo
 功能描述  : 获取UMTS QOS参数信息
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetUmtsQosInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 函 数 名  : TAF_PS_SetUmtsQosMinInfo
 功能描述  : 设置UMTS MIN QOS参数信息
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstUmtsQosMinInfo          - UMTS MIN QOS参数
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_SetUmtsQosMinInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_UMTS_QOS_EXT_STRU              *pstUmtsQosMinInfo
);

/*****************************************************************************
 函 数 名  : TAF_PS_GetUmtsQosMinInfo
 功能描述  : 获取UMTS MIN QOS参数信息
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetUmtsQosMinInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 函 数 名  : TAF_PS_GetDynamicUmtsQosInfo
 功能描述  : 获取动态UMTS QOS参数信息
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstCidListInfo             - CID列表
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetDynamicUmtsQosInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_CID_LIST_STRU                  *pstCidListInfo
);

/*****************************************************************************
 函 数 名  : TAF_PS_SetPdpContextState
 功能描述  : 设置指定CID(表)对应的PDP的状态
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstCidListStateInfo        - CID列表状态
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_SetPdpContextState(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_CID_LIST_STATE_STRU            *pstCidListStateInfo
);

/*****************************************************************************
 函 数 名  : TAF_PS_GetPdpContextState
 功能描述  : 获取所有已定义CID对应的PDP的状态
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetPdpContextState(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 函 数 名  : TAF_PS_CallModify
 功能描述  : 修改PS CALL参数
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             TAF_CID_LIST_STRU          - CID列表
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_CallModify(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_CID_LIST_STRU                  *pstCidListInfo
);

/*****************************************************************************
 函 数 名  : TAF_PS_CallAnswer
 功能描述  : 应答PS CALL
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstAnsInfo                 - PS CALL应答信息
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_CallAnswer(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PS_ANSWER_STRU                 *pstAnsInfo
);

/*****************************************************************************
 函 数 名  : TAF_PS_CallHangup
 功能描述  : 挂断PS CALL
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_CallHangup(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 函 数 名  : TAF_PS_CallOrig
 功能描述  : 发起PS CALL
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstDialParaInfo            - PS CALL参数
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_CallOrig(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PS_DIAL_PARA_STRU              *pstDialParaInfo
);

/*****************************************************************************
 函 数 名  : TAF_PS_CallEnd
 功能描述  : 结束PS CALL
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             stCidListInfo              - CID列表
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_CallEnd(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid
);

/*****************************************************************************
 函 数 名  : TAF_PS_GetPdpIpAddrInfo
 功能描述  : 获取指定CID(表)的PDP IP地址信息
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstCidListInfo             - CID列表
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetPdpIpAddrInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_CID_LIST_STRU                  *pstCidListInfo
);

/*****************************************************************************
 函 数 名  : TAF_PS_SetAnsModeInfo
 功能描述  : 设置PS域呼叫应答模式信息
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             ulAnsMode                  - 应答模式信息
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_SetAnsModeInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT32                          ulAnsMode
);

/*****************************************************************************
 函 数 名  : TAF_PS_GetAnsModeInfo
 功能描述  : 获取PS域呼叫应答模式信息
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetAnsModeInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 函 数 名  : TAF_PS_GetDynamicPrimPdpContextInfo
 功能描述  : 获取指定的已定义CID的动态Primary PDP上下文信息
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             ucCid                      - CID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetDynamicPrimPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid
);

/*****************************************************************************
 函 数 名  : TAF_PS_GetDynamicSecPdpContextInfo
 功能描述  : 获取指定的已定义CID的动态Secondary PDP上下文信息
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             ucCid                      - CID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetDynamicSecPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid
);

/*****************************************************************************
 函 数 名  : TAF_PS_GetDynamicTftInfo
 功能描述  : 获取指定的已定义CID的动态TFT信息
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             ucCid                      - CID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetDynamicTftInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid
);

/*****************************************************************************
 函 数 名  : TAF_PS_SetEpsQosInfo
 功能描述  : 设置指定CID的EPS QOS参数信息
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstEpsQosInfo              - EPS QOS参数信息
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_SetEpsQosInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_EPS_QOS_EXT_STRU               *pstEpsQosInfo
);

/*****************************************************************************
 函 数 名  : TAF_PS_GetEpsQosInfo
 功能描述  : 获取EPS QOS参数信息
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetEpsQosInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 函 数 名  : TAF_PS_GetDynamicEpsQosInfo
 功能描述  : 获取指定的已定义CID的动态EPS QOS参数
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             ucCid                      - CID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetDynamicEpsQosInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid
);

/*****************************************************************************
 函 数 名  : TAF_PS_GetDsFlowInfo
 功能描述  : 获取数据流量信息
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstQueryConfigInfo         - DSFLOW查询配置参数
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetDsFlowInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 函 数 名  : TAF_PS_ClearDsFlowInfo
 功能描述  : 清除数据流量信息
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstClearConfigInfo         - 流量清除配置参数信息
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_ClearDsFlowInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_DSFLOW_CLEAR_CONFIG_STRU       *pstClearConfigInfo
);

/*****************************************************************************
 函 数 名  : TAF_PS_ConfigDsFlowRpt
 功能描述  : 配置流量上报模式
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstReportConfigInfo        - 流量上报配置参数信息
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_ConfigDsFlowRpt(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_DSFLOW_REPORT_CONFIG_STRU      *pstReportConfigInfo
);

/*****************************************************************************
 函 数 名  : TAF_PS_SetPdpDnsInfo
 功能描述  : 设置PDP DNS信息
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstPdpDnsInfo              - PDP DNS信息
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_SetPdpDnsInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PDP_DNS_EXT_STRU               *pstPdpDnsInfo
);

/*****************************************************************************
 函 数 名  : TAF_PS_GetPdpDnsInfo
 功能描述  : 获取PDP DNS信息
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetPdpDnsInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 函 数 名  : TAF_PS_TrigGprsData
 功能描述  : 发送上行GPRS数据
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstGprsDataInfo            - GPRS数据信息
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_TrigGprsData(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_GPRS_DATA_STRU                 *pstGprsDataInfo
);

/*****************************************************************************
 函 数 名  : TAF_PS_ConfigNbnsFunction
 功能描述  : 配置NBNS功能
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             ulEnabled                  - NBNS功能使能标记
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_ConfigNbnsFunction(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT32                          ulEnabled
);

/*****************************************************************************
 函 数 名  : TAF_PS_GetNdisStateInfo
 功能描述  : 获取NDIS状态信息
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetNdisStateInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 函 数 名  : TAF_PS_SetAuthDataInfo
 功能描述  : 设置鉴权参数信息(NDIS)
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstAuthDataInfo            - 鉴权参数
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_SetAuthDataInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_AUTHDATA_EXT_STRU              *pstAuthDataInfo
);

/*****************************************************************************
 函 数 名  : TAF_PS_GetAuthDataInfo
 功能描述  : 获取鉴权参数信息(NDIS)
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetAuthDataInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 函 数 名  : TAF_PS_GetGprsActiveType
 功能描述  : 获取D命令GPRS类型(PPP拨号)
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstAtdPara                 - D命令拨号参数
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetGprsActiveType(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_ATD_PARA_STRU                  *pstAtdPara
);

/*****************************************************************************
 函 数 名  : TAF_PS_PppDialOrig
 功能描述  : 发起PPP拨号
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             ucCid                      - CID
             pstPppReqConfigInfo        - PPP配置参数
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_PppDialOrig(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid,
    TAF_PPP_REQ_CONFIG_INFO_STRU       *pstPppReqConfigInfo
);

#if(FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_PS_GetLteCsInfo
 功能描述  :
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetLteCsInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 函 数 名  : TAF_PS_GetCemodeInfo
 功能描述  :
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetCemodeInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 函 数 名  : TAF_PS_SetPdpProfInfo
 功能描述  :
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstPdpProfInfo             - PdpProfile 配置参数
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_SetPdpProfInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PDP_PROFILE_EXT_STRU           *pstPdpProfInfo
);
#endif

/*****************************************************************************
 函 数 名  : TAF_PS_GetCidSdfParaInfo
 功能描述  : 获取所有NV项中的SDF配置信息, 支持同步和异步两种方式
             输出参数非空 --- 同步方式(目前仅支持C核)
             输出参数为空 --- 异步方式
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : pstSdfQueryInfo            - SDF配置信息
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetCidSdfParaInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_SDF_PARA_QUERY_INFO_STRU       *pstSdfQueryInfo
);


/*****************************************************************************
 函 数 名  : TAF_PS_GetUnusedCid
 功能描述  : 获取空闲未激活的CID
             输出参数非空 --- 同步方式(目前仅支持C核)
             输出参数为空 --- 异步方式
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : puCid                      - 空闲未激活CID
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetUnusedCid(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                          *puCid
);

/*****************************************************************************
 函 数 名  : TAF_PS_GetDynamicDnsInfo
 功能描述  : 获取指定CID的DNS信息
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             ucCid                      - CID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetDynamicDnsInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid
);

VOS_UINT32 TAF_PS_SetCqosPriInfo(
    VOS_UINT32                                      ulModuleId,
    VOS_UINT16                                      usClientId,
    TAF_PS_CDATA_1X_QOS_NON_ASSURED_PRI_ENUM_UINT8  enPri
);

/*****************************************************************************
 函 数 名  : TAF_PS_SetApDsFlowRptCfg
 功能描述  : 设置AP流量上报参数
 输入参数  : ulModuleId                 - PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstRptCfg                  - 配置信息
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_SetApDsFlowRptCfg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_APDSFLOW_RPT_CFG_STRU          *pstRptCfg
);

/*****************************************************************************
 函 数 名  : TAF_PS_GetApDsFlowRptCfg
 功能描述  : 获取AP流量上报参数
 输入参数  : ulModuleId                 - PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetApDsFlowRptCfg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 函 数 名  : TAF_PS_SetDsFlowNvWriteCfg
 功能描述  : 设置流量写NV配置
 输入参数  : ulModuleId                 - PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstNvWriteCfg              - 流量写NV配置
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_SetDsFlowNvWriteCfg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_DSFLOW_NV_WRITE_CFG_STRU       *pstNvWriteCfg
);

/*****************************************************************************
 函 数 名  : TAF_PS_GetDsFlowNvWriteCfg
 功能描述  : 获取流量写NV配置
 输入参数  : ulModuleId                 - PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 TAF_PS_GetDsFlowNvWriteCfg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 TAF_PS_SetCdataDialModeInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    TAF_PS_CDATA_DIAL_MODE_ENUM_UINT32 enDialMode
);

VOS_UINT32 TAF_PS_SetImsPdpCfg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_IMS_PDP_CFG_STRU               *pstImsPdpCfg
);

VOS_UINT32 TAF_PS_GetCtaInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 TAF_PS_SetCtaInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucTimeLen
);

VOS_UINT32 TAF_PS_GetCgmtuInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 TAF_PS_SetCdmaDormantTimer(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucDormantTimer
);

VOS_UINT32 TAF_PS_ProcCdmaDormTimerQryReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);


TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8 TAF_PS_GetCdataBearStatus(
    VOS_UINT8                                               ucPdpId
);

TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8  TAF_PS_GetPppStatus( VOS_VOID );



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

#endif

