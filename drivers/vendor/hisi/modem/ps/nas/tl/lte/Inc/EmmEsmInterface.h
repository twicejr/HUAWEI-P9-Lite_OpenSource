

#ifndef __EMMESMINTERFACE_H__
#define __EMMESMINTERFACE_H__

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
#include "AppNasComm.h"

#include    "LnasErrlogInterface.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif
/*****************************************************************************
  2 macro
*****************************************************************************/

#define EMM_ESM_MAX_EPS_BEARER_NUM       11

/*EMM->SM Command消息前3个字节宏定义 EMM->SM*/
#define EMM_ESM_MSG_ID_HEADER            PS_MSG_ID_EMM_TO_ESM_BASE

/*ESM ->EMM Command消息前3个字节宏定义 SM->EMM*/
#define ESM_EMM_MSG_ID_HEADER            PS_MSG_ID_ESM_TO_EMM_BASE

#define ESM_EMM_PLMN_ID_LEN             (3)
#define ESM_EMM_MAX_EQUPLMN_NUM         (16)

#define ESM_EMM_RELEASE_R11             (0x00000b00)


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : EMM_ESM_MSG_TYPE_ENUM
 枚举说明  : EMM与SM消息类型
*****************************************************************************/
enum EMM_ESM_MSG_TYPE_ENUM
{
    /*消息原语*/
    /*ESM 发送给EMM的消息原语*/
    ID_EMM_ESM_EST_REQ                   = (0x01+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_EST_REQ_STRU */
    ID_EMM_ESM_BEARER_STATUS_REQ         = (0x03+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_BEARER_STATUS_REQ_STRU */
    ID_EMM_ESM_DATA_REQ                  = (0x05+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_DATA_REQ_STRU */
    ID_EMM_ESM_REL_REQ                   = (0x07+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_REL_REQ_STRU */
    ID_EMM_ESM_PDN_CON_RSP               = (0x09+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_PDN_CON_RSP_STRU */
    ID_EMM_ESM_PDN_CON_SUCC_REQ          = (0x0B+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_PDN_CON_SUCC_REQ_STRU */
    ID_EMM_ESM_SUSPEND_RSP               = (0x0D+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_SUSPEND_RSP_STRU */
    ID_EMM_ESM_RESUME_RSP                = (0x0F+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_RESUME_RSP_STRU */
    ID_EMM_ESM_BEARER_MODIFY_REQ         = (0x11+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_BEARER_MODIFY_REQ_STRU */
    ID_EMM_ESM_CLR_ESM_PROC_RES_NOTIFY   = (0x13+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_CLR_ESM_PROC_RES_NOTIFY_STRU */
    ID_EMM_ESM_BEGIN_SESSION_NOTITY      = (0x15+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice  EMM_ESM_BEGIN_SESSION_NOTIFY_STRU */
    ID_EMM_ESM_END_SESSION_NOTITY        = (0x16+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice  EMM_ESM_END_SESSION_NOTIFY_STRU */
    ID_EMM_ESM_SAVE_ERRLOG_IND           = (0x19+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice  EMM_ESM_SAVE_ERRLOG_IND_STRU */

    ID_EMM_ESM_CL_LOCAL_DETACH_NOTIFY    = (0x1a+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice  EMM_ESM_CL_LOCAL_DETACH_NOTIFY_STRU */

    /*EMM发送给SM的消息原语*/
    ID_EMM_ESM_EST_CNF                   = (0x02+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_EST_CNF_STRU */
    ID_EMM_ESM_STATUS_IND                = (0x04+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_STATUS_IND_STRU */
    ID_EMM_ESM_DATA_IND                  = (0x06+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_DATA_IND_STRU */
    ID_EMM_ESM_REL_IND                   = (0x08+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_REL_IND_STRU */
    ID_EMM_ESM_PDN_CON_IND               = (0x0A+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_PDN_CON_IND_STRU */
    ID_EMM_ESM_BEARER_STATUS_IND         = (0x0C+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_BEARER_STATUS_IND_STRU */
    ID_EMM_ESM_SUSPEND_IND               = (0x0D+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_SUSPEND_IND_STRU */
    ID_EMM_ESM_RESUME_IND                = (0x10+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_RESUME_IND_STRU */
    ID_EMM_ESM_DEACT_NON_EMC_BEARER_IND  = (0x12+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_DEACT_NON_EMC_BEARER_IND_STRU */
    ID_EMM_ESM_REPLAY_EXPORT_CTX_IND     = (0x14+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_EXPORT_CTX_IND_STRU */
    ID_EMM_ESM_STOP_NOTIFY_IND          = (0x15+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_STOP_NOTIFY_IND_STRU */

    ID_EMM_ESM_START_NOTIFY_IND          = (0x16+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_START_NOTIFY_IND_STRU */
    ID_EMM_ESM_PLMN_CHANGE_IND           = (0x17+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_PLMN_CHANGE_IND_STRU */

    ID_EMM_ESM_DATA_CNF                  = (0x18+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice  EMM_ESM_DATA_CNF_STRU*/

    ID_EMM_ESM_CLEAR_CL_BEARER_NOTIFY    = (0x19+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_CLEAR_CL_BEARER_NOTIFY_STRU */


    ID_EMM_ESM_BUTT
};
typedef VOS_UINT32 EMM_ESM_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : EMM_ESM_PDN_CON_RSLT_ENUM
 枚举说明  : PDN连接请求的结果类型
*****************************************************************************/
enum EMM_ESM_PDN_CON_RSLT_ENUM
{
    EMM_ESM_PDN_CON_RSLT_SUCC            = 0x00,
    EMM_ESM_PDN_CON_RSLT_FAIL            = 0x01,
    EMM_ESM_PDN_CON_RSLT_BUTT
};
typedef VOS_UINT32 EMM_ESM_PDN_CON_RSLT_ENUM_UINT32;

enum EMM_ESM_PDN_CON_REQ_TYPE_ENUM
{
    EMM_ESM_PDN_CON_REQ_TYPE_INITIAL              = 0,    /* 根据承载类型判断该填initial或emergency */
    EMM_ESM_PDN_CON_REQ_TYPE_HANDOVER           = 1,    /* 填handover */
    EMM_ESM_PDN_CON_REQ_TYPE_BUTT
};
typedef VOS_UINT32 EMM_ESM_PDN_CON_REQ_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : EMM_ESM_ATTACH_STATUS_ENUM
 枚举说明  : SM注册状态的类型
*****************************************************************************/
enum EMM_ESM_ATTACH_STATUS_ENUM
{
    EMM_ESM_ATTACH_STATUS_DETACHED       = 0x00,
    EMM_ESM_ATTACH_STATUS_ATTACHED       = 0x01,
    EMM_ESM_ATTACH_STATUS_AREA_RE_ENTRY  = 0x02,
    EMM_ESM_ATTACH_STATUS_EMC_ATTACHING  = 0x03,
    EMM_ESM_ATTACH_STATUS_BUTT
};
typedef VOS_UINT32 EMM_ESM_ATTACH_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : EMM_ESM_ATTACH_RESULT_ENUM
 枚举说明  : SM注册结果的类型
*****************************************************************************/
enum EMM_ESM_ATTACH_RESULT_ENUM
{
    EMM_ESM_ATTACH_RESULT_FAIL          = 0x00,
    EMM_ESM_ATTACH_RESULT_SUCC          = 0x01,

    EMM_ESM_ATTACH_RESULT_BUTT
};
typedef VOS_UINT32 EMM_ESM_ATTACH_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : EMM_ESM_BEARER_CNTXT_MOD_ENUM
 枚举说明  : ESM修改承载上下文的方式
*****************************************************************************/
enum EMM_ESM_BEARER_CNTXT_MOD_ENUM
{
    EMM_ESM_BEARER_CNTXT_MOD_MUTUAL         = 0x00, /*成功与网侧交互，修改承载上下文*/
    EMM_ESM_BEARER_CNTXT_MOD_LOCAL          = 0x01, /*ESM本地修改承载上下文*/

    EMM_ESM_BEARER_CNTXT_MOD_BUTT
};
typedef VOS_UINT32 EMM_ESM_BEARER_CNTXT_MOD_ENUM_UINT32;

/*****************************************************************************
 枚举名    : EMM_ESM_UP_SINGNAL_PENDING_ENUM
 枚举说明  : ESM是否存在上行信令阻塞
*****************************************************************************/
enum EMM_ESM_UP_SINGNAL_PENDING_ENUM
{
    EMM_ESM_NO_UP_SINGNAL_PENDING      = 0x00, /*不存在上行信令阻塞*/
    EMM_ESM_UP_SINGNAL_PENDING         = 0x01, /*存在上行信令阻塞*/

    EMM_ESM_UP_SINGNAL_PENDING_BUTT
};
typedef VOS_UINT32 EMM_ESM_UP_SINGNAL_PENDING_ENUM_UINT32;

/*****************************************************************************
 枚举名    : EMM_ESM_RSLT_TYPE_ENUM
 枚举说明  : ESM回复EMM消息结果枚举
*****************************************************************************/
enum EMM_ESM_RSLT_TYPE_ENUM
{
    EMM_ESM_RSLT_TYPE_SUCC             = 0x00, /*成功*/
    EMM_ESM_RSLT_TYPE_FAIL             = 0x01, /*失败*/

    EMM_ESM_RSLT_TYPE_BUTT
};
typedef VOS_UINT32 EMM_ESM_RSLT_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : EMM_ESM_RAT_TYPE_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  : UE支持的接入技术类型
*****************************************************************************/
enum EMM_ESM_RAT_TYPE_ENUM
{
    /* 不存在某种或者所有接入技术 */
    EMM_ESM_RAT_NONE                = 0,
    EMM_ESM_RAT_LTE_FDD             = 1,
    EMM_ESM_RAT_LTE_TDD             = 2,
    EMM_ESM_RAT_LTE_ALL             = 3,
    EMM_ESM_RAT_UTRAN_FDD           = 4,
    EMM_ESM_RAT_UTRAN_TDD           = 8,
    EMM_ESM_RAT_UTRAN_ALL           = 12,
    EMM_ESM_RAT_GERAN               = 16,
    EMM_ESM_RAT_ALL                 = 31,
    EMM_ESM_RAT_BUTT
};
typedef VOS_UINT8 EMM_ESM_RAT_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : ESM_EMM_SESSION_TYPE_ENUM
 枚举说明  :
*****************************************************************************/
enum EMM_ESM_SESSION_TYPE_ENUM
{
    EMM_ESM_SESSION_TYPE_ESM = 0,/*后续可以细分可扩展*/
    EMS_ESM_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 EMM_ESM_SESSION_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : EMM_ESM_SEND_RSLT_ENUM
 枚举说明  :
*****************************************************************************/
enum EMM_ESM_SEND_RSLT_ENUM
{
    EMM_ESM_SEND_RSLT_SUCCESS    = 0,
    EMM_ESM_SEND_RSLT_EMM_DISCARD,
    EMM_ESM_SEND_RSLT_FAILURE_HO,
    EMM_ESM_SEND_RSLT_FAILURE_CONN_REL,
    EMM_ESM_SEND_RSLT_FAILURE_CTRL_NOT_CONN,
    EMM_ESM_SEND_RSLT_FAILURE_TXN,
    EMM_ESM_SEND_RSLT_FAILURE_RLF,
    EMM_ESM_SEND_RSLT_NORF,
    EMM_ESM_SEND_RSLT_BUTT
};
typedef VOS_UINT32 EMM_ESM_SEND_RSLT_ENUM_UINT32;

/*****************************************************************************
 5. STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : EMM_ESM_FAIL_CAUSE_NOTIFY_STRU
 结构说明  : EMM_ESM_FAIL_CAUSE_NOTIFY_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           ucEsmCause;           /* ESM Cause*/
    VOS_UINT8                           ucRsv[3];
} EMM_ESM_FAIL_CAUSE_NOTIFY_STRU;

/*****************************************************************************
 结构名    : EMM_ESM_MSG_STRU
 结构说明  : EMM_ESM_MSG_STRU空口消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulEsmMsgSize;
    VOS_UINT8                          aucEsmMsg[4];       /* 消息的前四个字节内容             */
    /*************************************************************************
        _H2ASN_Array2String
    *************************************************************************/
}EMM_ESM_MSG_STRU;


/*****************************************************************************
 结构名    : EMM_ESM_EST_REQ_STRU
 结构说明  : EMM_ESM_EST_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/    /*msg ID*/

    VOS_UINT32                          ulOpId;              /* Operation Id */

    VOS_UINT32                          ulIsEmcType;         /* 是否是紧急PDN连接请求 */
    EMM_ESM_MSG_STRU                    stEsmMsg;            /* SM MSG */
} EMM_ESM_EST_REQ_STRU;

/*****************************************************************************
 结构名    : EMM_ESM_EST_CNF_STRU
 结构说明  : EMM_ESM_EST_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    EMM_ESM_ATTACH_RESULT_ENUM_UINT32   ulEstRst;           /*ATTACH 结果:    "1:success,0:fail"*/
} EMM_ESM_EST_CNF_STRU;


/*****************************************************************************
 结构名    : EMM_ESM_BEARER_STATUS_REQ_STRU
 结构说明  : EMM_ESM_BEARER_STATUS_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* 消息头 */
    EMM_ESM_BEARER_CNTXT_MOD_ENUM_UINT32 enBearerCntxtMod;  /*是否本地修改了承载上下文*/
    VOS_UINT32                          ulExistEmcPdnFlag;  /*当前是否存在紧急PDN连接*/
    VOS_UINT32                          ulEpsIdNum;         /*当前已激活的EPSID个数*/
    VOS_UINT32                          aulEsmEpsId[EMM_ESM_MAX_EPS_BEARER_NUM];     /*存贮已激活的EPS BID  */
} EMM_ESM_BEARER_STATUS_REQ_STRU;

/*****************************************************************************
 结构名    : EMM_ESM_BEARER_STATUS_IND_STRU
 结构说明  : EMM_ESM_BEARER_STATUS_IND_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* 消息头 */
    VOS_UINT32                          ulEpsIdNum;         /* 当前已激活的EPSID个数 */
    VOS_UINT32                          aulEsmEpsId[EMM_ESM_MAX_EPS_BEARER_NUM];     /*存贮已激活的EPS BID  */
} EMM_ESM_BEARER_STATUS_IND_STRU;

/*****************************************************************************
 结构名    : EMM_ESM_DATA_REQ_STRU
 结构说明  : EMM_ESM_DATA_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* 消息头 */

    VOS_UINT32                          ulOpId;              /* Operation Id */

    VOS_UINT32                          ulIsEmcType;         /* 是否是紧急PDN连接请求 */
    EMM_ESM_MSG_STRU                    stEsmMsg;           /* SM MSG :SM模块向SAE携带参数消息*/
}EMM_ESM_DATA_REQ_STRU;

/*****************************************************************************
 结构名    : EMM_ESM_DATA_IND_STRU
 结构说明  : EMM_ESM_DATA_IND_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* 消息头 */

    EMM_ESM_MSG_STRU                    stEsmMsg;           /* SM MSG :SM模块向SAE携带参数消息*/
}EMM_ESM_DATA_IND_STRU;

/*****************************************************************************
 结构名    : EMM_ESM_REL_REQ_STRU
 结构说明  : EMM_ESM_REL_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                           ulMsgId;            /*_H2ASN_Skip*/            /* 消息头 */
    VOS_UINT32                           ulReserved;         /* 保留字 */
}EMM_ESM_REL_REQ_STRU;

typedef EMM_ESM_REL_REQ_STRU EMM_ESM_REL_IND_STRU;

/*****************************************************************************
 结构名    : EMM_ESM_PDN_CON_SUCC_REQ_STRU
 结构说明  : EMM_ESM_PDN_CON_SUCC_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* 消息头 */
    EMM_ESM_MSG_STRU                    stEsmMsg;           /* SM MSG :SM模块向SAE携带参数消息*/
}EMM_ESM_PDN_CON_SUCC_REQ_STRU;

/*****************************************************************************
 结构名    : EMM_ESM_PDN_CON_IND_STRU
 结构说明  : EMM_ESM_PDN_CON_IND_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                           ulMsgId;            /*_H2ASN_Skip*/           /* 消息头 */
    VOS_UINT32                           ulCId;             /*承载上下文Id */ /*range:0~31*/
    EMM_ESM_PDN_CON_REQ_TYPE_ENUM_UINT32 enPdnReqType;      /* EMM指定ESM发起的PDN连接请求类型 */
}EMM_ESM_PDN_CON_IND_STRU;

/*****************************************************************************
 结构名    : EMM_ESM_PDN_CON_RSP_STRU
 结构说明  : EMM_ESM_PDN_CON_RSP_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* 消息头 */

    EMM_ESM_PDN_CON_RSLT_ENUM_UINT32    ulRst;              /* 响应结果 ,   0:succ,1:fail  */
    EMM_ESM_MSG_STRU                    stEsmMsg;            /* ATTACH 过程中包含的PDN_CON_REQ消息*/
} EMM_ESM_PDN_CON_RSP_STRU;


/*****************************************************************************
 结构名    : EMM_ESM_STATUS_IND_STRU
 结构说明  : EMM_ESM_STATUS_IND_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* 消息头 */
    EMM_ESM_ATTACH_STATUS_ENUM_UINT32   enEMMStatus;        /*当前EMM注册状态 */
                                                            /*0:DETACHED,1:ATTACHED*/
}EMM_ESM_STATUS_IND_STRU;

/*****************************************************************************
 结构名称: EMM_ESM_SUSPEND_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明:EMM->ESM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           aucRsv[4];
} EMM_ESM_SUSPEND_IND_STRU;

/*****************************************************************************
 结构名称: EMM_ESM_SUSPEND_RSP_STRU
 协议表格:
 ASN.1 描述:
 结构说明:ESM->EMM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    EMM_ESM_RSLT_TYPE_ENUM_UINT32       enRslt;
} EMM_ESM_SUSPEND_RSP_STRU;

/*****************************************************************************
 结构名称: EMM_ESM_RESUME_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明:EMM->ESM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           aucRsv[4];
} EMM_ESM_RESUME_IND_STRU;


/*****************************************************************************
 结构名称: EMM_ESM_DEACT_NON_EMC_BEARER_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明:EMM->ESM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           aucRsv[4];
} EMM_ESM_DEACT_NON_EMC_BEARER_IND_STRU;


/*****************************************************************************
 结构名称: EMM_ESM_RESUME_RSP_STRU
 协议表格:
 ASN.1 描述:
 结构说明:ESM->EMM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    EMM_ESM_RSLT_TYPE_ENUM_UINT32       enRslt;
} EMM_ESM_RESUME_RSP_STRU;


/*****************************************************************************
 结构名    : EMM_ESM_BEARER_MODIFY_REQ_STRU
 结构说明  : EMM_ESM_BEARER_MODIFY_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* 消息头 */
    VOS_UINT32                          ulEpsId;         /* 当前修改的EPSID*/
} EMM_ESM_BEARER_MODIFY_REQ_STRU;

/*****************************************************************************
 结构名    : EMM_ESM_ERRLOG_STRU
 结构说明  : ESM发给EMM的ERRLOG信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulEsmMsgSize;
    VOS_UINT8                          aucEsmMsg[4];       /* ERRLOG的前四个字节内容*/
}EMM_ESM_ERRLOG_STRU;

/*****************************************************************************
结构名    : EMM_ESM_SAVE_ERRLOG_IND_STRU
结构说明  : EMM_ESM_SAVE_ERRLOG_IND_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                /*_H2ASN_Skip*/
    VOS_UINT32                                      ulMsgId;      /*_H2ASN_Skip*/

    EMM_ESM_ERRLOG_STRU                             stEmmEsmErrlog;
}EMM_ESM_SAVE_ERRLOG_IND_STRU;

/*****************************************************************************
 结构名    : ESM_EMM_SESSION_NOTIFY_STRU
 结构说明  : ESM_EMM_SESSION_NOTIFY_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                /*_H2ASN_Skip*/
    VOS_UINT32                                      ulMsgId;      /*_H2ASN_Skip*/

    EMM_ESM_SESSION_TYPE_ENUM_UINT8                 enSessionType;
    VOS_UINT8                                       aucReserved[3];
} EMM_ESM_SESSION_NOTIFY_STRU;

typedef EMM_ESM_SESSION_NOTIFY_STRU     EMM_ESM_BEGIN_SESSION_NOTIFY_STRU;
typedef EMM_ESM_SESSION_NOTIFY_STRU     EMM_ESM_END_SESSION_NOTIFY_STRU;


/*****************************************************************************
结构名    : EMM_ESM_CL_LOCAL_DETACH_NOTIFY_STRU
结构说明  : EMM_ESM_CL_LOCAL_DETACH_NOTIFY_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                    /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;      /*_H2ASN_Skip*/

    VOS_UINT8                           aucRsv[4];
}EMM_ESM_CL_LOCAL_DETACH_NOTIFY_STRU;



/*****************************************************************************
 结构名    : EMM_ESM_DATA_CNF_STRU
 结构说明  : EMM_ESM_DATA_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                  /*_H2ASN_Skip*/
    VOS_UINT32                                  ulMsgId;            /*_H2ASN_Skip*/

    EMM_ESM_SEND_RSLT_ENUM_UINT32               enDataCnfRst;
    VOS_UINT32                                  ulEsmEmmOpId;
}EMM_ESM_DATA_CNF_STRU;

/*****************************************************************************
 结构名    : EMM_ESM_CLR_ESM_PROC_RES_NOTIFY_STRU
 结构说明  : EMM_ESM_CLR_ESM_PROC_RES_NOTIFY_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT32                          ulOpId;              /*Operation Id*/
    VOS_UINT32                          ulIsEmcType;         /*是否是紧急PDN对应的ESM流程*/
} EMM_ESM_CLR_ESM_PROC_RES_NOTIFY_STRU;

/*****************************************************************************
 结构名    : EMM_ESM_EXPORT_CTX_IND_STRU
 结构说明  : EMM_ESM_EXPORT_CTX_IND_STRU数据结构,PC回放消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* 消息头 */
    VOS_UINT8                           aucRsv[4];

}EMM_ESM_EXPORT_CTX_IND_STRU;
/*****************************************************************************
结构名    :ESM_EMM_PLMN_ID_STRU中
协议表格  :
ASN.1描述 :
结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPlmnId[ESM_EMM_PLMN_ID_LEN];
    VOS_UINT8                           ucRsv;
}ESM_EMM_PLMN_ID_STRU;

/*****************************************************************************
结构名    :ESM_EMM_EPLMN_LIST_STRU中
协议表格  :
ASN.1描述 :
结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEplmnNum;

    ESM_EMM_PLMN_ID_STRU                astEplmnList[ESM_EMM_MAX_EQUPLMN_NUM];
}ESM_EMM_EPLMN_LIST_STRU;

/*****************************************************************************
 结构名    : ESM_EMM_CURRENT_CAMP_INFO_STRU
 结构说明  : ESM_EMM_CURRENT_CAMP_INFO_STRU数据结构
*****************************************************************************/
typedef struct
{
    ESM_EMM_PLMN_ID_STRU                stPlmnId;
}ESM_EMM_CURRENT_CAMP_INFO_STRU;


/*****************************************************************************
 结构名    : EMM_ESM_STOP_NOTIFY_IND_STRU
 结构说明  : EMM_ESM_STOP_NOTIFY_IND_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* 消息头 */
    VOS_UINT8                           aucRsv[4];

}EMM_ESM_STOP_NOTIFY_IND_STRU;


/*****************************************************************************
 结构名    : EMM_ESM_START_NOTIFY_IND_STRU
 结构说明  : EMM_ESM_START_NOTIFY_IND_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* 消息头 */
    VOS_UINT8                           aucRsv[4];
}EMM_ESM_START_NOTIFY_IND_STRU;

/*****************************************************************************
 结构名    : EMM_ESM_PLMN_CHANGE_IND_STRU
 结构说明  : EMM_ESM_PLMN_CHANGE_IND_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* 消息头 */
    VOS_UINT8                           aucRsv[4];
}EMM_ESM_PLMN_CHANGE_IND_STRU;

/*****************************************************************************
 结构名    : EMM_ESM_CLEAR_CL_BEARER_NOTIFY_STRU
 结构说明  : EMM_ESM_CLEAR_CL_BEARER_NOTIFY_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                           aucRsv[4];
}EMM_ESM_CLEAR_CL_BEARER_NOTIFY_STRU;


typedef struct
{
    EMM_ESM_MSG_TYPE_ENUM_UINT32        enMsgID;            /*_H2ASN_MsgChoice_Export EMM_ESM_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          EMM_ESM_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}EMM_ESM_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    EMM_ESM_MSG_DATA                     stMsgData;
}EmmEsmInterface_MSG;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern VOS_UINT32 g_ulDsdsRFSharedFlag;


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern EMM_ESM_UP_SINGNAL_PENDING_ENUM_UINT32 NAS_ESM_IsUpSingnalPending( VOS_VOID );
extern VOS_UINT32  NAS_EMM_lteRatIsExist(VOS_VOID);

extern VOS_UINT32 NAS_ESM_DecodeNwEsmMsgGetEsmCause
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT32                          ulMsgLen,
    VOS_UINT8                          *enEsmCause
);

extern VOS_VOID NAS_EMM_GetCurrentCampInfo
(
    ESM_EMM_PLMN_ID_STRU *pstCurrentCampInfo
);
extern VOS_VOID NAS_EMM_GetEplmnList
(
    NAS_ESM_PLMN_LIST_STRU *pstEplmnList
);
extern VOS_UINT32 NAS_EMM_GetNasRelease(VOS_VOID);
extern VOS_UINT16 NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_ENUM_UINT16 enAlmId);
extern VOS_UINT32 NAS_EMM_IsErrLogNeedRecord(VOS_UINT16 usLevel);
extern VOS_UINT32 NAS_LMM_GetPositionInfo(LNAS_OM_ERRLOG_POSITION_INFO_STRU *pstPositionInfo);

extern VOS_UINT32  NAS_EMM_IsEhrpdOr1XRatExist(VOS_VOID);

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

#endif /* end of EmmEsmInterface.h */





