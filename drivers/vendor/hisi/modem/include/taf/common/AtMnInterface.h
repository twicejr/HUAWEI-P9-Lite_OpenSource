

#ifndef  AT_MN_INTERFACE_H
#define  AT_MN_INTERFACE_H

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "product_config.h"
#include "vos.h"
#include "PsTypeDef.h"
#include "PsCommonDef.h"
#include "v_msg.h"
#include "TafTypeDef.h"
#include "TafClientApi.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 常量定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* Added by f62575 for AT Project，2011-10-03,  Begin*/
/*****************************************************************************
 枚举名    : MN_AT_MSGTYPE_ENUM
 枚举说明  : AT与MN模块间的原语
 1.日    期   : 2012年6月11日
   作    者   : w00166186
   修改内容   : AT&T&DCM项目
 2.日    期   : 2013年07月22日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseI项目
*****************************************************************************/
enum AT_MN_MSGTYPE_ENUM
{
    /* 消息名称 */                                          /*消息ID*/          /* 备注 */
    /* AT与CALL模块间消息 */
    MN_APP_MSG_CLASS_CALL                                   = TAF_CALL_APP_MSG_BASE,
    /* Added by f00179208 for AT Project，2011-10-14,  Begin*/
    /* 发起呼叫 */
    MN_CALL_APP_ORIG_REQ                                    = 0x0001,           /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    /* 结束呼叫 */
    MN_CALL_APP_END_REQ,                                                        /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    /* 应答来电 */
    MN_CALL_APP_ANSWER_REQ,                                                     /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    /* 开始发送DTMF */
    MN_CALL_APP_START_DTMF_REQ,                                                 /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    /* 停止发送DTMF */
    MN_CALL_APP_STOP_DTMF_REQ,                                                  /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    /* 发起呼叫相关补充业务操作 */
    MN_CALL_APP_SUPS_CMD_REQ,                                                   /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    /* 获取呼叫信息 */
    MN_CALL_APP_GET_INFO_REQ,                                                   /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    /* 获取通话时长 */
    MN_CALL_APP_GET_CDUR_REQ,                                                   /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    MN_CALL_APP_SET_UUSINFO_REQ,                                                /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    MN_CALL_APP_QRY_UUSINFO_REQ,                                                /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    MN_CALL_APP_SET_ALS_REQ,                                                    /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    MN_CALL_APP_QRY_ALS_REQ,                                                    /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */

    MN_CALL_APP_MAX_REQ,
    /* Added by f00179208 for AT Project，2011-10-14,  End */

    MN_CALL_APP_CUSTOM_ECC_NUM_REQ,                                             /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */

    ID_TAFAGENT_MN_GET_CALL_INFO_REQ,                                           /* TAFAGENT_>MN  获取通话信息请求消息*/

    MN_CALL_APP_CLPR_GET_REQ,                                                   /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */

    MN_CALL_APP_XLEMA_REQ,                                                      /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */

    /* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    MN_CALL_APP_SET_CSSN_REQ,                                                   /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    /* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-29, begin */
    MN_CALL_QRY_ECALL_INFO_REQ,                                                 /* _H2ASN_MsgChoice MN_CALL_QRY_ECALL_INFO_REQ_STRU */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-29, end */

    TAF_CALL_APP_SEND_FLASH_REQ,                                                /* _H2ASN_MsgChoice TAF_CALL_APP_SEND_FLASH_REQ_STRU*/

    TAF_CALL_APP_SEND_BURST_DTMF_REQ,                                           /* _H2ASN_MsgChoice TAF_CALL_BURST_DTMF_REQ_MSG_STRU*/

    TAF_CALL_APP_SEND_CUSTOM_DIAL_REQ,

    MN_CALL_APP_CALL_MODIFY_REQ,                                                /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    MN_CALL_APP_CALL_ANSWER_REMOTE_MODIFY_REQ,                                  /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */

    TAF_CALL_APP_ECONF_DIAL_REQ,                                                /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    TAF_CALL_APP_GET_ECONF_CALLED_INFO_REQ,                                     /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */

    TAF_CALL_APP_SEND_CONT_DTMF_REQ,                                            /* _H2ASN_MsgChoice TAF_CALL_CONT_DTMF_REQ_MSG_STRU*/

    TAF_CALL_APP_SEND_CCLPR_REQ,                                                 /* _H2ASN_MsgChoice TAF_CALL_SND_CCLPR_REQ_MSG_STRU */

    /* AT与MSG模块间消息 */
    MN_APP_MSG_CLASS_MSG                                    = TAF_MSG_APP_MSG_BASE,
    MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT                       = 0x1001,           /* _H2ASN_MsgChoice MN_MSG_SEND_PARM_STRU */
    MN_MSG_MSGTYPE_SEND_RPDATA_FROMMEM                      = 0x1002,           /* _H2ASN_MsgChoice MN_MSG_SEND_FROMMEM_PARM_STRU */
    MN_MSG_MSGTYPE_SEND_RPRPT                               = 0x1003,           /* _H2ASN_MsgChoice MN_MSG_SEND_ACK_PARM_STRU */
    MN_MSG_MSGTYPE_WRITE                                    = 0x1004,           /* _H2ASN_MsgChoice MN_MSG_WRITE_PARM_STRU */
    MN_MSG_MSGTYPE_READ                                     = 0x1005,           /* _H2ASN_MsgChoice MN_MSG_READ_PARM_STRU */
    MN_MSG_MSGTYPE_LIST                                     = 0x1006,           /* _H2ASN_MsgChoice MN_MSG_LIST_PARM_STRU */
    MN_MSG_MSGTYPE_DELETE                                   = 0x1007,           /* _H2ASN_MsgChoice MN_MSG_DELETE_PARAM_STRU */
    MN_MSG_MSGTYPE_DELETE_TEST                              = 0x1008,           /* _H2ASN_MsgChoice MN_MSG_MEM_STORE_ENUM_U8 */
    MN_MSG_MSGTYPE_WRITE_SRV_PARA                           = 0x1009,           /* _H2ASN_MsgChoice MN_MSG_WRITE_SRV_PARAM_STRU */
    MN_MSG_MSGTYPE_READ_SRV_PARA                            = 0x100a,           /* _H2ASN_MsgChoice MN_MSG_READ_COMM_PARAM_STRU */
    MN_MSG_MSGTYPE_DELETE_SRV_PARA                          = 0x100b,           /* _H2ASN_MsgChoice MN_MSG_DELETE_PARAM_STRU */
    MN_MSG_MSGTYPE_MODIFY_STATUS                            = 0x100c,           /* _H2ASN_MsgChoice MN_MSG_MODIFY_STATUS_PARM_STRU */
    MN_MSG_MSGTYPE_SET_RCVPATH                              = 0x100d,           /* _H2ASN_MsgChoice MN_MSG_SET_RCVMSG_PATH_PARM_STRU */
    MN_MSG_MSGTYPE_GET_RCVPATH                              = 0x100e,           /* _H2ASN_MsgChoice MN_MSG_GET_RCVMSG_PATH_PARM_STRU */
    MN_MSG_MSGTYPE_GET_STORAGESTATUS                        = 0x100f,           /* _H2ASN_MsgChoice MN_MSG_GET_STORAGE_STATUS_PARM_STRU */
    MN_MSG_MSGTYPE_READ_STARPT                              = 0x1010,           /* _H2ASN_MsgChoice MN_MSG_READ_COMM_PARAM_STRU */
    MN_MSG_MSGTYPE_DELETE_STARPT                            = 0x1011,           /* _H2ASN_MsgChoice MN_MSG_DELETE_PARAM_STRU */
    MN_MSG_MSGTYPE_GET_STARPT_FROMMOMSG                     = 0x1012,           /* _H2ASN_MsgChoice MN_MSG_SEND_PARM_STRU */
    MN_MSG_MSGTYPE_GET_MOMSG_FROMSTARPT                     = 0x1013,           /* _H2ASN_MsgChoice MN_MSG_SEND_PARM_STRU */
    MN_MSG_MSGTYPE_SET_MEMSTATUS                            = 0x1014,           /* _H2ASN_MsgChoice MN_MSG_SET_MEMSTATUS_PARM_STRU */
    MN_MSG_MSGTYPE_SET_RELAY_LINK_CTRL                      = 0x1015,           /* _H2ASN_MsgChoice MN_MSG_SET_LINK_CTRL_STRU */
    MN_MSG_MSGTYPE_GET_RELAY_LINK_CTRL                      = 0x1016,           /* _H2ASN_MsgChoice  */
    MN_MSG_MSGTYPE_STUB                                     = 0x1017,           /* _H2ASN_MsgChoice MN_MSG_STUB_MSG_STRU */
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    MN_MSG_MSGTYPE_GET_ALLCBMIDS                            = 0x1018,           /* _H2ASN_MsgChoice  */
    MN_MSG_MSGTYPE_ADD_CBMIDS                               = 0x1019,           /* _H2ASN_MsgChoice MN_MSG_CBMIR_LIST_STRU */
    MN_MSG_MSGTYPE_DELETE_CBMIDS                            = 0x101a,           /* _H2ASN_MsgChoice MN_MSG_CBMIR_LIST_STRU */
    MN_MSG_MSGTYPE_EMPTY_CBMIDS                             = 0x101b,           /* _H2ASN_MsgChoice  */
#endif

    MN_MSG_MSGTYPE_MAX,

    /* AT与SSA模块间消息 */
    MN_APP_MSG_CLASS_SSA                                    = TAF_SSA_APP_MSG_BASE,
    /*补充业务发起操作时的消息类型*/
    TAF_MSG_REGISTERSS_MSG,
    TAF_MSG_ERASESS_MSG,
    TAF_MSG_ACTIVATESS_MSG,
    TAF_MSG_DEACTIVATESS_MSG,
    TAF_MSG_INTERROGATESS_MSG,
    TAF_MSG_REGPWD_MSG,
    TAF_MSG_PROCESS_USS_MSG,
    TAF_MSG_ERASECCENTRY_MSG,
    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2014-01-06, begin */
    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2014-01-06, end */
    TAF_MSG_RLEASE_MSG,
    TAF_MSG_SET_USSDMODE_MSG,

    /* AT与MMA模块间消息 */
    MN_APP_MSG_CLASS_MMA                                    = TAF_MMA_APP_MSG_BASE,

    /* AT与MN模块间设置操作相关消息，未优化部分，待优化后删除 */
    MN_APP_MSG_CLASS_SET                                    = TAF_APP_SET_MSG_BASE,

    /* AT与MN模块间查询操作相关消息，未优化部分，待优化后删除 */
    MN_APP_MSG_CLASS_QRY                                    = TAF_APP_QRY_MSG_BASE,

    /* AT与PS适配模块间消息 */
    MN_APP_MSG_CLASS_PS                                     = TAF_APS_MSG_BASE,

    /* Deleted by Y00213812 for VoLTE_PhaseI 项目, 2013-6-29, begin */
    /* 这部分消息的定义迁移到TafAppAps.h文件中 */
    /* Deleted by Y00213812 for VoLTE_PhaseI 项目, 2013-6-29, end */


    MN_APP_MSG_CLASS_MASK                                   = TAF_IMSA_MSG_MASK
};
typedef VOS_UINT16 AT_MN_MSGTYPE_ENUM_UINT16;

typedef AT_MN_MSGTYPE_ENUM_UINT16 MN_MSG_MSGTYPE_ENUM_U16;

typedef VOS_UINT32  MN_CALL_APP_REQ_ENUM_UINT32;
/* Added by f62575 for AT Project，2011-10-03,  End*/

/*****************************************************************************
 枚举名    : AT_CC_MSGTYPE_ENUM
 枚举说明  : AT与CC模块间的原语
*****************************************************************************/
enum AT_CC_MSGTYPE_ENUM
{
    /* 消息名称 */                                          /*消息ID*/          /* 备注 */
    /* AT发给CC的消息 */
    AT_CC_MSG_STATE_QRY_REQ                                 = 0x0000,

    /* CC发给AT的消息 */
    AT_CC_MSG_STATE_QRY_CNF                                 = 0x0001,

    AT_CC_MSG_BUTT

 };
typedef VOS_UINT16 AT_CC_MSGTYPE_ENUM_UINT16;

/*****************************************************************************
  4 宏定义
*****************************************************************************/
#define ECALL_MAX_DIAL_NUM_LEN               (18)

/*****************************************************************************
  5 STRUCT定义
*****************************************************************************/
/*****************************************************************************
 结构名    : AT_APPCTRL_STRU
 结构说明  : AT APP 控制结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
} AT_APPCTRL_STRU;

/* Added by f62575 for AT Project，2011-10-03,  Begin*/
/* MN发往AT的事件结构 */
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT16                          usMsgName;                              /* _H2ASN_Skip *//* 消息ID */
    VOS_UINT8                           aucReserved1[2];
    MN_CLIENT_ID_T                      clientId;
    VOS_UINT16                          usLen;
    VOS_UINT8                           aucContent[4];
}MN_AT_IND_EVT_STRU;

/*****************************************************************************
 结构名称  : TAF_MNTN_LOG_PRINT_STRU
 结构说明  : 可维可测LOG信息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           aucReserve[2];
    VOS_CHAR                            acLog[4];           /* 打印字符串 */
} TAF_MNTN_LOG_PRINT_STRU;


/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    AT_MN_MSGTYPE_ENUM_UINT16           enMsgID;                                /*_H2ASN_MsgChoice_Export AT_MN_MSGTYPE_ENUM_U32*/
                                                                                /* 为了兼容NAS的消息头定义，所以转换ASN.1使用AT_MN_MSGTYPE_ENUM_U32 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          AT_MN_MSGTYPE_ENUM_U32
    ****************************************************************************/
}AT_MN_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    AT_MN_MSG_DATA                      stMsgData;
}AtMnInterface_MSG;
/* Added by f62575 for AT Project，2011-10-03,  End*/

/*****************************************************************************
 枚举名    : MN_APP_REQ_MSG_STRU
 结构说明  : 来自APP的请求消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgName;                              /* 消息名 */
    VOS_UINT8                           aucReserve1[2];                             /* 保留 */
    MN_CLIENT_ID_T                      clientId;                               /* Client ID */
    MN_OPERATION_ID_T                   opId;                                   /* Operation ID */
    VOS_UINT8                           aucReserve2[1];                         /* 保留 */
    VOS_UINT8                           aucContent[4];                          /* 消息内容 */
} MN_APP_REQ_MSG_STRU;


/* Deleted by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
/* Deleted by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */



/*****************************************************************************
  6 函数声明
*****************************************************************************/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


#endif /* end of AtMnInterface.h */
