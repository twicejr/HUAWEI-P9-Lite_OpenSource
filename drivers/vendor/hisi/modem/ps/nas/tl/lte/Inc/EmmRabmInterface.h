

#ifndef __EMMRABMINTERFACE_H__
#define __EMMRABMINTERFACE_H__

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

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define EMM_ERABM_MAX_EPSB_NUM           11

/*EMM->RABM Command消息前3个字节宏定义 EMM->RABM*/
#define EMM_ERABM_MSG_ID_HEADER          PS_MSG_ID_EMM_TO_RABM_BASE

/*RABM->EMM Command消息前3个字节宏定义 RABM->EMM*/
#define ERABM_EMM_MSG_ID_HEADER          PS_MSG_ID_RABM_TO_EMM_BASE

#define ERABM_EMM_RELEASE_R11             (0x00000b00)
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : EMM_ERABM_MSG_TYPE_ENUM
 枚举说明  : EMM与RABM消息类型
*****************************************************************************/
enum EMM_ERABM_MSG_TYPE_ENUM
{
    /* 消息名称 */                      /*消息ID*/
    /* RABM发给EMM的原语 */
    ID_EMM_ERABM_REEST_REQ               = (0x02+ERABM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ERABM_REEST_REQ_STRU */
    ID_EMM_ERABM_DRB_SETUP_IND           = (0x04+ERABM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ERABM_DRB_SETUP_IND_STRU */
    ID_EMM_ERABM_REL_REQ                 = (0x06+ERABM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ERABM_REL_REQ_STRU */
    ID_EMM_ERABM_SUSPEND_RSP             = (0x08+ERABM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ERABM_SUSPEND_RSP_STRU */
    ID_EMM_ERABM_RESUME_RSP              = (0x0a+ERABM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ERABM_RESUME_RSP_STRU */

    /* EMM发给RABM的原语 */
    ID_EMM_ERABM_REEST_IND               = (0x01+EMM_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ERABM_REEST_IND_STRU */
    ID_EMM_ERABM_REL_IND                 = (0x03+EMM_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ERABM_REL_IND_STRU */
    ID_EMM_ERABM_RRC_CON_REL_IND         = (0x05+EMM_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ERABM_RRC_CON_REL_IND_STRU */
    ID_EMM_ERABM_SUSPEND_IND             = (0x07+EMM_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ERABM_SUSPEND_IND_STRU */
    ID_EMM_ERABM_RESUME_IND              = (0x09+EMM_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ERABM_RESUME_IND_STRU */

    ID_EMM_ERABM_BUTT
};
typedef VOS_UINT32 EMM_ERABM_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : EMM_ERABM_REEST_STATE_ENUM_UINT32
 枚举说明  : reest的状态类型
*****************************************************************************/
enum EMM_ERABM_REEST_STATE_ENUM
{
    EMM_ERABM_REEST_STATE_SUCC          = 0x00,             /*SR成功*/
    EMM_ERABM_REEST_STATE_FAIL,                             /*SR失败*/
    EMM_ERABM_REEST_STATE_INITIATE,                         /*SR发起*/

    EMM_ERABM_REEST_STATE_BUTT
};
typedef VOS_UINT32 EMM_ERABM_REEST_STATE_ENUM_UINT32;
/*****************************************************************************
 枚举名    : EMM_ERABM_REL_CAUSE_ENUM
 枚举说明  : 释放原因值
*****************************************************************************/
enum EMM_ERABM_REL_CAUSE_ENUM
{
    EMM_ERABM_REL_CAUSE_NULL          = 0x00,
    EMM_ERABM_REL_CAUSE_NO_RF,                     /* 释放原因为no rf */

    EMM_ERABM_REL_CAUSE_BUTT
};
typedef VOS_UINT32 EMM_ERABM_REL_CAUSE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : EMM_ERABM_UP_DATA_PENDING_ENUM
 枚举说明  : RABM是否存在上行数据阻塞
*****************************************************************************/
enum EMM_ERABM_UP_DATA_PENDING_ENUM
{
    EMM_ERABM_NO_UP_DATA_PENDING      = 0x00, /*不存在上行数据阻塞*/
    EMM_ERABM_UP_DATA_PENDING         = 0x01, /*存在上行数据阻塞*/

    EMM_ERABM_UP_DATA_PENDING_BUTT
};
typedef VOS_UINT32 EMM_ERABM_UP_DATA_PENDING_ENUM_UINT32;

/*****************************************************************************
 枚举名    : EMM_ERABM_RSLT_TYPE_ENUM
 枚举说明  : RABM回复EMM消息结果枚举
*****************************************************************************/
enum EMM_ERABM_RSLT_TYPE_ENUM
{
    EMM_ERABM_RSLT_TYPE_SUCC             = 0x00, /*成功*/
    EMM_ERABM_RSLT_TYPE_FAIL             = 0x01, /*失败*/

    EMM_ERABM_RSLT_TYPE_BUTT
};
typedef VOS_UINT32 EMM_ERABM_RSLT_TYPE_ENUM_UINT32;

/*****************************************************************************
 结构名称   : EMM_ERABM_SYS_CHNG_TYPE_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : 系统变更的类型
*****************************************************************************/
enum EMM_ERABM_SYS_CHNG_TYPE_ENUM
{
    EMM_ERABM_SYS_CHNG_TYPE_RESEL       = 0,
    EMM_ERABM_SYS_CHNG_TYPE_HO,
    EMM_ERABM_SYS_CHNG_TYPE_CCO,
    EMM_ERABM_SYS_CHNG_TYPE_REDIR,

    EMM_ERABM_SYS_CHNG_TYPE_RESEL_REVERSE,
    EMM_ERABM_SYS_CHNG_TYPE_HO_REVERSE,
    EMM_ERABM_SYS_CHNG_TYPE_CCO_REVERSE,
    EMM_ERABM_SYS_CHNG_TYPE_REDIR_REVERSE,

    EMM_ERABM_SYS_CHNG_TYPE_BUTT
};
typedef VOS_UINT32 EMM_ERABM_SYS_CHNG_TYPE_ENUM_UINT32;


/*****************************************************************************
   5 STRUCT
*****************************************************************************/

/*****************************************************************************
 结构名    : EMM_ERABM_REEST_REQ_STRU
 结构说明  : EMM_ERABM_REEST_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulIsEmcType;
} EMM_ERABM_REEST_REQ_STRU;

/*****************************************************************************
 结构名    : EMM_ERABM_DRB_SETUP_IND_STRU
 结构说明  : EMM_ERABM_DRB_SETUP_IND_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;           /*_H2ASN_Skip*/
} EMM_ERABM_DRB_SETUP_IND_STRU;

/*****************************************************************************
 结构名    : EMM_ERABM_REL_REQ_STRU
 结构说明  : EMM_ERABM_REL_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                           ulMsgId;           /*_H2ASN_Skip*/            /* 消息头*/
    VOS_UINT32                           ulReserved;         /* 保留字*/
}EMM_ERABM_REL_REQ_STRU;

/*****************************************************************************
 结构名    : EMM_ERABM_REL_IND_STRU
 结构说明  : EMM_ERABM_REL_IND_STRU数据结构
*****************************************************************************/
typedef EMM_ERABM_REL_REQ_STRU EMM_ERABM_REL_IND_STRU;

/*****************************************************************************
 结构名    : EMM_ERABM_RRC_CON_REL_IND_STRU
 结构说明  : EMM_ERABM_RRC_CON_REL_IND_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                           ulMsgId;           /*_H2ASN_Skip*/            /* 消息头*/
    EMM_ERABM_REL_CAUSE_ENUM_UINT32      enRelCause;        /* 增加释放原因 */
}EMM_ERABM_RRC_CON_REL_IND_STRU;


/*****************************************************************************
 结构名    : EMM_ERABM_REEST_IND_STRU
 结构说明  : EMM_ERABM_REEST_IND_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/                                          /*_H2ASN_Skip*/
    VOS_UINT32                           ulMsgId;           /*_H2ASN_Skip*/
    EMM_ERABM_REEST_STATE_ENUM_UINT32     enReEstState;
} EMM_ERABM_REEST_IND_STRU;

/*****************************************************************************
 结构名称: EMM_ERABM_SUSPEND_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明:EMM->RABM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    EMM_ERABM_SYS_CHNG_TYPE_ENUM_UINT32 enSysChngType;

    VOS_UINT8                           aucRsv[4];
} EMM_ERABM_SUSPEND_IND_STRU;

/*****************************************************************************
 结构名称: EMM_ERABM_SUSPEND_RSP_STRU
 协议表格:
 ASN.1 描述:
 结构说明:RABM->EMM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    EMM_ERABM_RSLT_TYPE_ENUM_UINT32      enRslt;
} EMM_ERABM_SUSPEND_RSP_STRU;

/*****************************************************************************
 结构名称: EMM_ERABM_RESUME_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明:EMM->RABM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    EMM_ERABM_SYS_CHNG_TYPE_ENUM_UINT32 enSysChngType;

    VOS_UINT8                           aucRsv[4];
} EMM_ERABM_RESUME_IND_STRU;


/*****************************************************************************
 结构名称: EMM_ERABM_RESUME_RSP_STRU
 协议表格:
 ASN.1 描述:
 结构说明:RABM->EMM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    EMM_ERABM_RSLT_TYPE_ENUM_UINT32      enRslt;
} EMM_ERABM_RESUME_RSP_STRU;


typedef struct
{
    EMM_ERABM_MSG_TYPE_ENUM_UINT32       enMsgId;            /*_H2ASN_MsgChoice_Export EMM_ERABM_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          EMM_ERABM_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}EMM_ERABM_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    EMM_ERABM_MSG_DATA                     stMsgData;
}EmmRabmInterface_MSG;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern EMM_ERABM_UP_DATA_PENDING_ENUM_UINT32 NAS_ERABM_IsDataPending( VOS_VOID );
extern VOS_VOID NAS_EMM_SaveMoSerStartTimeStamp(VOS_VOID);

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

#endif /* end of RabmEmmInterface.h */
