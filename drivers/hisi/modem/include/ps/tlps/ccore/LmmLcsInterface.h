

#ifndef __LMMLCSINTERFACE_H__
#define __LMMLCSINTERFACE_H__

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
#include "LPSCommon.h"


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif



/*****************************************************************************
  2 Macro
*****************************************************************************/
#define PS_MSG_ID_LCS_TO_LMM_BASE 0
#define PS_MSG_ID_LMM_TO_LCS_BASE 100

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : LMM_LCS_MSG_ID_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LMM与LCS之间的消息枚举
*****************************************************************************/
enum    LMM_LCS_MSG_ID_ENUM
{
    /* LCS发给LMM的消息原语 */
    ID_LCS_LMM_EST_REQ                  = 0x01+PS_MSG_ID_LCS_TO_LMM_BASE,       /* _H2ASN_MsgChoice LCS_LMM_EST_REQ_STRU */
    ID_LCS_LMM_DATA_REQ                 = 0x02+PS_MSG_ID_LCS_TO_LMM_BASE,       /* _H2ASN_MsgChoice LCS_LMM_DATA_REQ_STRU */


    /* LMM发送给LCS的消息原语*/
    ID_LMM_LCS_EST_CNF                  = 0x01+PS_MSG_ID_LMM_TO_LCS_BASE,       /* _H2ASN_MsgChoice LMM_LCS_EST_CNF_STRU */
    ID_LMM_LCS_DATA_CNF                 = 0x02+PS_MSG_ID_LMM_TO_LCS_BASE,       /* _H2ASN_MsgChoice LMM_LCS_DATA_CNF_STRU */
    ID_LMM_LCS_DATA_IND                 = 0x03+PS_MSG_ID_LMM_TO_LCS_BASE,       /* _H2ASN_MsgChoice LMM_LCS_DATA_IND_STRU */
    ID_LMM_LCS_POS_CAP_INFO_IND         = 0x04+PS_MSG_ID_LMM_TO_LCS_BASE,       /* _H2ASN_MsgChoice LMM_LCS_POS_CAP_INFO_IND_STRU */
    ID_LMM_LCS_REL_IND                  = 0x05+PS_MSG_ID_LMM_TO_LCS_BASE,       /* _H2ASN_MsgChoice LMM_LCS_REL_IND_STRU */

    ID_LMM_LCS_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 LMM_LCS_MSG_ID_ENUM_UINT32;


/*****************************************************************************
 枚举名    : LMM_LCS_EST_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 建链结果枚举
*****************************************************************************/
enum LMM_LCS_EST_RESULT_ENUM
{
    LMM_LCS_EST_RSLT_SUCC                           = 0,/* 建链成功 */
    LMM_LCS_EST_RSLT_FAIL_PS_NOT_ATTACHED           = 1,/* PS域未注册 */
    LMM_LCS_EST_RSLT_FAIL_PS_ATTACH_NOT_ALLOWED     = 2,/* PS不允许注册 */
    LMM_LCS_EST_RSLT_FAIL_USIM_PS_INVALID           = 3,/* USIM卡无效 */
    LMM_LCS_EST_RSLT_FAIL_ACCESS_BARRED             = 4,/* 被BAR */
    LMM_LCS_EST_RSLT_FAIL_STATE_CANNOT_SERVICE      = 5,/* 当前状态无法发起SERVICE */
    LMM_LCS_EST_RSLT_FAIL_EPC_LCS_NOT_SUPPORT       = 6,/* EPC-LCS不支持 */
    LMM_LCS_EST_RSLT_FAIL_3411_RUNNING              = 7,/* 3411在运行 */
    LMM_LCS_EST_RSLT_FAIL_SERVICE_FAIL              = 8,/* SERVICE失败 */
    LMM_LCS_EST_RSLT_FAIL_OTHERS                    = 9,/* 其他失败原因值 */

    LMM_LCS_EST_RSLT_BUTT
};
typedef VOS_UINT32 LMM_LCS_EST_RESULT_ENUM_UINT32;

/*****************************************************************************
 结构名称: LMM_LCS_SEND_RSLT_ENUM
 协议表格:
 ASN.1 描述:
 结构说明:消息发送结果枚举
*****************************************************************************/
enum LMM_LCS_SEND_RSLT_ENUM
{
    LMM_LCS_SEND_RSLT_SUCCESS                       = 0,/* 发送成功 */
    LMM_LCS_SEND_RSLT_FAIL_PS_NOT_ATTACHED          = 1,/* PS域未注册 */
    LMM_LCS_SEND_RSLT_FAIL_PS_ATTACH_NOT_ALLOWED    = 2,/* PS不允许注册 */
    LMM_LCS_SEND_RSLT_FAIL_USIM_PS_INVALID          = 3,/* USIM卡无效 */
    LMM_LCS_SEND_RSLT_FAIL_ACCESS_BARRED            = 4,/* 被BAR */
    LMM_LCS_SEND_RSLT_FAIL_RRC_CONN_NOT_EXIST       = 5,/* 连接状态不存在，SS接着用EST_REQ请求建链 */
    LMM_LCS_SEND_RSLT_FAIL_EPC_LCS_NOT_SUPPORT      = 6,/* EPC-LCS不支持 */
    LMM_LCS_SEND_RSLT_RSLT_FAIL_3411_RUNNING        = 7,/* 3411在运行 */
    LMM_LCS_SEND_RSLT_FAIL_LOW_LAYER                = 8,/* 底层发送失败 */
    LMM_LCS_SEND_RSLT_FAIL_OHTERS                   = 9,/* 其他失败原因值 */

    LMM_LCS_SEND_RSLT_BUTT
};
typedef VOS_UINT32 LMM_LCS_SEND_RSLT_ENUM_UINT32;

/*****************************************************************************
 结构名称: LMM_LCS_NW_EPC_LCS_ENUM
 协议表格:
 ASN.1 描述:
 结构说明:网侧的EPC-LCS能力
*****************************************************************************/
enum LMM_LCS_NW_EPC_LCS_ENUM
{
    LMM_LCS_NW_EPC_LCS_NOT_SUPPORT          = 0,
    LMM_LCS_NW_EPC_LCS_SUPPORT              = 1,

    LMM_LCS_NW_EPC_LCS_BUTT
};
typedef VOS_UINT32 LMM_LCS_NW_EPC_LCS_ENUM_UINT32;

/*****************************************************************************
 结构名称: LMM_LCS_NW_CS_LCS_ENUM
 协议表格:
 ASN.1 描述:
 结构说明:网侧的CS-LCS能力
*****************************************************************************/
enum LMM_LCS_NW_CS_LCS_ENUM
{
    LMM_LCS_NW_CS_LCS_NO_INFORMATION        = 0,
    LMM_LCS_NW_CS_LCS_SUPPORT               = 1,
    LMM_LCS_NW_CS_LCS_NOT_SUPPORT           = 2,
    LMM_LCS_NW_CS_LCS_RESERVED              = 3,

    LMM_LCS_NW_CS_LCS_BUTT
};
typedef VOS_UINT32 LMM_LCS_NW_CS_LCS_ENUM_UINT32;

/*****************************************************************************
 结构名称: LMM_LCS_REL_CAUSE_ENUM
 协议表格:
 ASN.1 描述:
 结构说明:释放原因值
*****************************************************************************/
enum LMM_LCS_REL_CAUSE_ENUM
{
    LMM_LCS_REL_CAUSE_USER_INACTIVITY       = 0,
    LMM_LCS_REL_CAUSE_USER_OHTERS           = 1,

    LMM_LCS_REL_CAUSE_BUTT
};
typedef VOS_UINT32 LMM_LCS_REL_CAUSE_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名称: LCS_LMM_EST_REQ_STRU
 协议表格:
 ASN.1 描述:
 结构说明:SS请求LMM建链
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LMM_LCS_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
} LCS_LMM_EST_REQ_STRU;

/*****************************************************************************
 结构名称: LMM_LCS_EST_CNF_STRU
 协议表格:
 ASN.1 描述:
 结构说明:LMM对SS的建链回复
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LMM_LCS_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    LMM_LCS_EST_RESULT_ENUM_UINT32      enEstRst;           /*建链结果*/
} LMM_LCS_EST_CNF_STRU;

/*****************************************************************************
 结构名    : LMM_LCS_MSG_STRU
 结构说明  : LCS空口消息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulLcsMsgSize;
    VOS_UINT8                          aucLcsMsg[4];       /* 消息的前四个字节内容             */
    /*************************************************************************
        _H2ASN_Array2String
    *************************************************************************/
}LMM_LCS_MSG_STRU;


/*****************************************************************************
 结构名称: LCS_LMM_DATA_REQ_STRU
 协议表格:
 ASN.1 描述:
 结构说明:LCS请求数据发送
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LMM_LCS_MSG_ID_ENUM_UINT32           ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                           ulOpId;

    LMM_LCS_MSG_STRU                     stLcsMsg;
} LCS_LMM_DATA_REQ_STRU;


/*****************************************************************************
 结构名称: LMM_LCS_DATA_CNF_STRU
 协议表格:
 ASN.1 描述:
 结构说明:LMM对SS数据发送结果回复
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LMM_LCS_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    LMM_LCS_SEND_RSLT_ENUM_UINT32       enDataCnfRst;       /* Data cnf结果 */
} LMM_LCS_DATA_CNF_STRU;


/*****************************************************************************
 结构名称: LMM_LCS_DATA_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明:网侧发送的SS空口消息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LMM_LCS_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    LMM_LCS_MSG_STRU                    stLcsMsg;
} LMM_LCS_DATA_IND_STRU;

/*****************************************************************************
 结构名称: LMM_LCS_POS_CAP_INFO_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明: 网侧的LCS和LPP能力上报
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LMM_LCS_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    LMM_LCS_NW_EPC_LCS_ENUM_UINT32      enNwEpcLcs;
    LMM_LCS_NW_CS_LCS_ENUM_UINT32       enNwCsLcs;
} LMM_LCS_POS_CAP_INFO_IND_STRU;


/*****************************************************************************
 结构名称: LMM_LCS_REL_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明: LMM通知LCS链路释放
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LMM_LCS_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    LMM_LCS_REL_CAUSE_ENUM_UINT32       enRelCause;
} LMM_LCS_REL_IND_STRU;


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

#endif /* end of LmmLcsInterface.h */

