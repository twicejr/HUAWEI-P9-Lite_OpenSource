/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : SpmImsaInterface.h
  版 本 号   : 初稿
  作    者   : 闫志吉 00213812
  生成日期   : 2013年6月27日
  功能描述   : SPM和IMSA接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年6月23日
    作    者   : 闫志吉 00213812
    修改内容   : 创建文件

******************************************************************************/
#ifndef  SPM_IMSA_INTERFACE_H
#define  SPM_IMSA_INTERFACE_H

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MnCallApi.h"
#include "TafClientApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 枚举定义
*****************************************************************************/
/* 移到MnCallApi.h */

/*****************************************************************************
枚举名    : SPM_IMSA_MSG_TYPE_ENUM
结构说明  : SPM 和IMSA的之间的消息

  1.日    期   : 2013年6月23日
    作    者   :  y00213812
    修改内容   : 定义SPM和IMSA之间的接口消息
*****************************************************************************/
enum SPM_IMSA_MSG_TYPE_ENUM
{
    ID_SPM_IMSA_CALL_ORIG_REQ               = TAF_SPM_IMSA_MSG_BASE,            /* _H2ASN_MsgChoice SPM_IMSA_CALL_ORIG_REQ_STRU */
    ID_SPM_IMSA_CALL_SUPS_CMD_REQ,                                              /* _H2ASN_MsgChoice SPM_IMSA_CALL_SUPS_CMD_REQ_STRU */
    ID_SPM_IMSA_CALL_GET_CALL_INFO_REQ,                                         /* _H2ASN_MsgChoice SPM_IMSA_CALL_GET_CALL_INFO_REQ_STRU */
    ID_SPM_IMSA_CALL_START_DTMF_REQ,                                            /* _H2ASN_MsgChoice SPM_IMSA_CALL_START_DTMF_REQ_STRU */
    ID_SPM_IMSA_CALL_STOP_DTMF_REQ,                                             /* _H2ASN_MsgChoice SPM_IMSA_CALL_STOP_DTMF_REQ_STRU */
    ID_SPM_IMSA_CALL_GET_CUDR_REQ,                                              /* _H2ASN_MsgChoice SPM_IMSA_CALL_GET_CUDR_REQ_STRU */
    ID_SPM_IMSA_CALL_GET_CLPR_REQ,                                              /* _H2ASN_MsgChoice SPM_IMSA_CALL_GET_CLPR_REQ_STRU */
    ID_SPM_IMSA_CALL_INVITE_NEW_PTPT_REQ,                                       /* _H2ASN_MsgChoice SPM_IMSA_CALL_INVITE_NEW_PTPT_REQ_STRU */

    ID_SPM_IMSA_CALL_MODIFY_REQ,                                                /* _H2ASN_MsgChoice SPM_IMSA_CALL_MODIFY_REQ_STRU */
    ID_SPM_IMSA_CALL_ANSWER_REMOTE_MODIFY_REQ,                                  /* _H2ASN_MsgChoice SPM_IMSA_CALL_ANSWER_REMOTE_MODIFY_REQ_STRU */
    ID_SPM_IMSA_CALL_ECONF_DIAL_REQ,                                            /* _H2ASN_MsgChoice SPM_IMSA_CALL_ECONF_DIAL_REQ_STRU */
    ID_SPM_IMSA_CALL_ECONF_ADD_USERS_REQ,                                       /* _H2ASN_MsgChoice SPM_IMSA_CALL_ECONF_ADD_USERS_REQ_STRU */
    ID_SPM_IMSA_CALL_GET_ECONF_CALLED_INFO_REQ,                                 /* _H2ASN_MsgChoice SPM_IMSA_CALL_GET_ECONF_CALLED_INFO_REQ_STRU*/
    ID_SPM_IMSA_REGISTER_SS_REQ             = TAF_SPM_IMSA_MSG_BASE+0x100,      /* _H2ASN_MsgChoice SPM_IMSA_REGISTER_SS_REQ_STRU */
    ID_SPM_IMSA_ERASE_SS_REQ,                                                   /* _H2ASN_MsgChoice SPM_IMSA_ERASE_SS_REQ_STRU */
    ID_SPM_IMSA_ACTIVATE_SS_REQ,                                                /* _H2ASN_MsgChoice SPM_IMSA_ACTIVATE_SS_REQ_STRU */
    ID_SPM_IMSA_DEACTIVATE_SS_REQ,                                              /* _H2ASN_MsgChoice SPM_IMSA_DEACTIVATE_SS_REQ_STRU */
    ID_SPM_IMSA_INTERROGATE_SS_REQ,                                             /* _H2ASN_MsgChoice SPM_IMSA_INTERROGATE_SS_REQ_STRU */
    ID_SPM_IMSA_PROCESS_USSD_REQ,                                               /* _H2ASN_MsgChoice SPM_IMSA_PROCESS_USSD_REQ_STRU */
    ID_SPM_IMSA_RELEASE_REQ,                                                    /* _H2ASN_MsgChoice SPM_IMSA_RELEASE_REQ_STRU */

    ID_IMSA_SPM_CALL_MSG                    = TAF_SPM_IMSA_MSG_BASE+0x200,      /* _H2ASN_MsgChoice IMSA_SPM_CALL_MSG_STRU */
    ID_IMSA_SPM_CALL_GET_CALL_INFO_CNF,                                         /* _H2ASN_MsgChoice IMSA_SPM_CALL_GET_CALL_INFO_CNF_STRU */
    ID_IMSA_SPM_CHANNEL_INFO_IND,                                               /* _H2ASN_MsgChoice IMSA_SPM_CHANNEL_INFO_IND_STRU */
    ID_IMSA_SPM_CALL_GET_CLPR_CNF,                                              /* _H2ASN_MsgChoice IMSA_SPM_CALL_GET_CLPR_CNF_STRU */
    ID_IMSA_SPM_CALL_START_DTMF_CNF,                                            /* _H2ASN_MsgChoice IMSA_SPM_CALL_START_DTMF_CNF_STRU */
    ID_IMSA_SPM_CALL_START_DTMF_RSLT_IND,                                       /* _H2ASN_MsgChoice IMSA_SPM_CALL_START_DTMF_RSLT_IND_STRU */
    ID_IMSA_SPM_CALL_STOP_DTMF_CNF,                                             /* _H2ASN_MsgChoice IMSA_SPM_CALL_STOP_DTMF_CNF_STRU */
    ID_IMSA_SPM_CALL_STOP_DTMF_RSLT_IND,                                        /* _H2ASN_MsgChoice IMSA_SPM_CALL_STOP_DTMF_RSLT_IND_STRU */
    ID_IMSA_SPM_CALL_INVITE_NEW_PTPT_CNF,                                       /* _H2ASN_MsgChoice IMSA_SPM_CALL_INVITE_NEW_PTPT_CNF_STRU */
    ID_IMSA_SPM_CALL_TYPE_CHANGE_INFO_IND  ,                                    /* _H2ASN_MsgChoice IMSA_SPM_CALL_TYPE_CHANGE_INFO_IND_STRU */
    ID_IMSA_SPM_CALL_MODIFY_CNF,                                                /* _H2ASN_MsgChoice IMSA_SPM_CALL_MODIFY_CNF_STRU */
    ID_IMSA_SPM_CALL_ANSWER_REMOTE_MODIFY_CNF,                                  /* _H2ASN_MsgChoice IMSA_SPM_CALL_ANSWER_REMOTE_MODIFY_CNF_STRU */
    ID_IMSA_SPM_CALL_MODIFY_STATUS_IND,                                         /* _H2ASN_MsgChoice IMSA_SPM_CALL_MODIFY_STATUS_IND_STRU */
    ID_IMSA_SPM_CALL_ECONF_DIAL_CNF,                                            /* _H2ASN_MsgChoice IMSA_SPM_CALL_ECONF_DIAL_CNF_STRU */
    ID_IMSA_SPM_CALL_ECONF_ADD_USERS_CNF,                                       /* _H2ASN_MsgChoice IMSA_SPM_CALL_ECONF_ADD_USERS_CNF_STRU */
    ID_IMSA_SPM_CALL_GET_ECONF_CALLED_INFO_CNF,                                 /* _H2ASN_MsgChoice IMSA_SPM_CALL_GET_ECONF_CALLED_INFO_CNF_STRU*/
    ID_IMSA_SPM_CALL_ECONF_NOTIFY_IND,                                          /* _H2ASN_MsgChoice IMSA_SPM_CALL_ECONF_NOTIFY_IND_STRU */
    ID_IMSA_SPM_SS_MSG                      = TAF_SPM_IMSA_MSG_BASE+0x300,     /* _H2ASN_MsgChoice IMSA_SPM_SS_MSG_STRU */

    ID_SPM_IMSA_MSG_TYPE_BUTT
};
typedef  VOS_UINT32  SPM_IMSA_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
枚举名    : SPM_IMSA_CALL_MODIFY_STATUS_ENUM
结构说明  : SPM和IMSA的之间MODIFY过程中的状态

  1.日    期   : 2013年6月23日
    作    者   : f00179208
    修改内容   : 新增枚举
*****************************************************************************/
enum SPM_IMSA_CALL_MODIFY_STATUS_ENUM
{
    SPM_IMSA_CALL_MODIFY_REMOTE_USER_REQUIRE_TO_MODIFY,                         /* 远程用户发起的modify */
    SPM_IMSA_CALL_MODIFY_PROC_BEGIN,                                            /* modify流程开始 */
    SPM_IMSA_CALL_MODIFY_PROC_END,                                              /* modify流程结束 */
    SPM_IMSA_CALL_MODIFY_STATUS_BUTT
};
typedef  VOS_UINT8  SPM_IMSA_CALL_MODIFY_STATUS_ENUM_UINT8;

/*****************************************************************************
  3 类型定义
*****************************************************************************/
/*****************************************************************************
 结构名  : SPM_IMSA_REGISTER_SS_REQ_STRU
 结构说明: SS注册操作

 修改历史      :
  1.日    期   : 2013年6月23日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserved2[1];
    TAF_SS_REGISTERSS_REQ_STRU          stRegSsReq;
} SPM_IMSA_REGISTER_SS_REQ_STRU;

/*****************************************************************************
 结构名  : SPM_IMSA_ERASE_SS_REQ_STRU
 结构说明: SS删除操作

 修改历史      :
  1.日    期   : 2013年6月23日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserved2[1];
    TAF_SS_ERASESS_REQ_STRU             stSsEraseReq;
} SPM_IMSA_ERASE_SS_REQ_STRU;

/*****************************************************************************
 结构名  : SPM_IMSA_ACTIVATE_SS_REQ_STRU
 结构说明: SS激活操作

 修改历史      :
  1.日    期   : 2013年6月23日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserved2[1];
    TAF_SS_ACTIVATESS_REQ_STRU          stSsActivateReq;
} SPM_IMSA_ACTIVATE_SS_REQ_STRU;

/*****************************************************************************
 结构名  : SPM_IMSA_DEACTIVATE_SS_REQ_STRU
 结构说明: SS去激活操作

 修改历史      :
  1.日    期   : 2013年6月23日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserved2[1];
    TAF_SS_DEACTIVATESS_REQ_STRU        stDeactivateSsReq;
} SPM_IMSA_DEACTIVATE_SS_REQ_STRU;

/*****************************************************************************
 结构名  : SPM_IMSA_INTERROGATE_SS_REQ_STRU
 结构说明: SS查询操作

 修改历史      :
  1.日    期   : 2013年6月23日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserved2[1];
    TAF_SS_INTERROGATESS_REQ_STRU       stInterrogateSsReq;
} SPM_IMSA_INTERROGATE_SS_REQ_STRU;

/*****************************************************************************
 结构名  : SPM_IMSA_PROCESS_USSD_REQ_STRU
 结构说明: USSD操作

 修改历史      :
  1.日    期   : 2013年6月23日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserved2[1];
    TAF_SS_PROCESS_USS_REQ_STRU         stProcUssdReq;
} SPM_IMSA_PROCESS_USSD_REQ_STRU;

/*****************************************************************************
 结构名  : SPM_IMSA_RELEASE_REQ_STRU
 结构说明: 释放当前补充业务的会话

 修改历史      :
  1.日    期   : 2013年6月23日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserved2[1];
} SPM_IMSA_RELEASE_REQ_STRU;

/*****************************************************************************
 结构名  : IMSA_SPM_SS_MSG_STRU
 结构说明: 呼叫无关补充业务的操作结果或者主动上报

 修改历史      :
  1.日    期   : 2013年6月23日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    VOS_UINT16                          usLen;
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU  stSsEventInfo;
} IMSA_SPM_SS_MSG_STRU;

/*****************************************************************************
 结构名  : SPM_IMSA_CALL_ORIG_REQ_STRU
 结构说明: IMSA模块发起呼叫

 修改历史      :
  1.日    期   : 2013年6月23日
    作    者   : Y00213812
    修改内容   : 新增结构
  2.日    期   : 2013年12月20日
    作    者   : y00245242
    修改内容   : 修改数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserved[1];
    MN_CALL_ORIG_PARAM_STRU             stOrig;
}SPM_IMSA_CALL_ORIG_REQ_STRU;

/*****************************************************************************
 结构名  : SPM_IMSA_CALL_INVITE_NEW_PTPT_REQ_STRU
 结构说明: 拉会议第三方请求

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : l00150010
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserved[1];
    MN_CALL_CALLED_NUM_STRU             stNewPtptNumber;                        /* 新的第三方电话 */
}SPM_IMSA_CALL_INVITE_NEW_PTPT_REQ_STRU;

/*****************************************************************************
 结构名    : IMSA_SPM_CALL_INVITE_NEW_PTPT_CNF_STRU
 结构说明  : 拉会议第三方回复结果

  1.日    期   : 2014年01月27日
    作    者   : L00150010
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserve[1];
    TAF_CS_CAUSE_ENUM_UINT32            enCause;                                /* Cause Value of the Call Control */
}IMSA_SPM_CALL_INVITE_NEW_PTPT_CNF_STRU;

/*****************************************************************************
 结构名  : SPM_IMSA_CALL_SUPS_CMD_REQ_STRU
 结构说明: IMSA模块发起呼叫相关的补充业务操作

 修改历史      :
  1.日    期   : 2013年6月23日
    作    者   : Y00213812
    修改内容   : 新增结构
  2.日    期   : 2013年12月20日
    作    者   : y00245242
    修改内容   : 修改数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserved[1];
    MN_CALL_SUPS_PARAM_STRU             stCallMgmtCmd;
}SPM_IMSA_CALL_SUPS_CMD_REQ_STRU;

/*****************************************************************************
 结构名  : SPM_IMSA_CALL_GET_CALL_INFO_REQ_STRU
 结构说明: IMSA模块获取呼叫信息

 修改历史      :
  1.日    期   : 2013年6月23日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                                              ulMsgId;            /* _H2ASN_Skip */
    MN_CLIENT_ID_T                                          usClientId;
    MN_OPERATION_ID_T                                       ucOpId;
    CALL_IMSA_GET_CALL_INFO_REQ_TYPE_ENMU_UINT8             enReqType;          /* 请求类型 */
} SPM_IMSA_CALL_GET_CALL_INFO_REQ_STRU;

/*****************************************************************************
 结构名  : SPM_IMSA_CALL_START_DTMF_REQ_STRU
 结构说明: IMSA模块启动DTMF过程

 修改历史      :
  1.日    期   : 2013年6月23日
    作    者   : Y00213812
    修改内容   : 新增结构
  2.日    期   : 2013年10月25日
    作    者   : y00245242
    修改内容   : 适配新的DTMF接口修改
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    VOS_UINT32                                              ulMsgId;                                  /* _H2ASN_Skip */
    MN_CLIENT_ID_T                                          usClientId;
    MN_OPERATION_ID_T                                       ucOpId;
    VOS_UINT8                                               aucReserved[1];
    TAF_CALL_DTMF_PARAM_STRU                                stDtmf;
}SPM_IMSA_CALL_START_DTMF_REQ_STRU;

/*****************************************************************************
 结构名  : SPM_IMSA_CALL_STOP_DTMF_REQ_STRU
 结构说明: IMSA模块停止DTMF过程

 修改历史      :
  1.日    期   : 2013年6月23日
    作    者   : Y00213812
    修改内容   : 新增结构
  2.日    期   : 2013年10月25日
    作    者   : y00245242
    修改内容   : 适配新的DTMF接口修改
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    VOS_UINT32                                              ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                                          usClientId;
    MN_OPERATION_ID_T                                       ucOpId;
    VOS_UINT8                                               aucReserved[1];
    TAF_CALL_DTMF_PARAM_STRU                                stDtmf;
}SPM_IMSA_CALL_STOP_DTMF_REQ_STRU;

/*****************************************************************************
 结构名  : IMSA_SPM_CALL_START_DTMF_CNF_STRU
 结构说明: IMSA给SPM确认START DTMF接收

 修改历史      :
  1.日    期   : 2013年10月24日
    作    者   : y00245242
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    VOS_UINT32                                              ulMsgId;                                  /* _H2ASN_Skip */
    MN_CLIENT_ID_T                                          usClientId;
    MN_OPERATION_ID_T                                       ucOpId;
    MN_CALL_ID_T                                            ucCallId;                               /* 暂不使用，待后续扩展 */

    TAF_CALL_DTMF_STATE_ENUM_UINT8                          enDtmfState;                            /* 暂不使用，待后续扩展 */
    VOS_UINT8                                               ucDtmfCnt;                              /* 暂不使用，待后续扩展 */
    VOS_UINT8                                               aucReserved[2];
    TAF_CS_CAUSE_ENUM_UINT32                                enCause;                                /* 错误码 */

}IMSA_SPM_CALL_START_DTMF_CNF_STRU;

/*****************************************************************************
 结构名  : IMSA_SPM_CALL_START_DTMF_RSLT_IND_STRU
 结构说明: IMSA指示SPM网络对START DTMF回复结果

 修改历史      :
  1.日    期   : 2013年10月24日
    作    者   : y00245242
    修改内容   : 新增结构
*****************************************************************************/
typedef IMSA_SPM_CALL_START_DTMF_CNF_STRU  IMSA_SPM_CALL_START_DTMF_RSLT_IND_STRU;

/*****************************************************************************
 结构名  : IMSA_SPM_CALL_STOP_DTMF_CNF_STRU
 结构说明: IMSA给SPM确认STOP DTMF接收

 修改历史      :
  1.日    期   : 2013年10月24日
    作    者   : y00245242
    修改内容   : 新增结构
*****************************************************************************/
typedef IMSA_SPM_CALL_START_DTMF_CNF_STRU  IMSA_SPM_CALL_STOP_DTMF_CNF_STRU;

/*****************************************************************************
 结构名  : IMSA_SPM_CALL_STOP_DTMF_RSLT_IND_STRU
 结构说明: IMSA指示SPM网络对STOP DTMF回复结果

 修改历史      :
  1.日    期   : 2013年10月24日
    作    者   : y00245242
    修改内容   : 新增结构
*****************************************************************************/
typedef IMSA_SPM_CALL_START_DTMF_CNF_STRU  IMSA_SPM_CALL_STOP_DTMF_RSLT_IND_STRU;

/*****************************************************************************
 结构名  : SPM_IMSA_CALL_GET_CUDR_REQ_STRU
 结构说明: IMSA模块获取当前的通话时长

 修改历史      :
  1.日    期   : 2013年6月23日
    作    者   : Y00213812
    修改内容   : 新增结构
  2.日    期   : 2013年12月20日
    作    者   : y00245242
    修改内容   : 修改数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    MN_CALL_ID_T                        callId;
}SPM_IMSA_CALL_GET_CUDR_REQ_STRU;

/*****************************************************************************
 结构名  : SPM_IMSA_CALL_GET_CLPR_REQ_STRU
 结构说明: IMSA模块获取呼叫源信息

 修改历史      :
  1.日    期   : 2013年6月23日
    作    者   : Y00213812
    修改内容   : 新增结构
  2.日    期   : 2013年12月20日
    作    者   : y00245242
    修改内容   : 修改数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    MN_CALL_ID_T                        callId;
}SPM_IMSA_CALL_GET_CLPR_REQ_STRU;

/*****************************************************************************
 结构名  : MN_CALL_EVT_ORIG_CNF_STRU
 结构说明: CALL模块呼叫相关的操作结果回复

 修改历史      :
  1.日    期   : 2013年6月23日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    MN_CALL_EVENT_ENUM_U32              enEventType;
    MN_CALL_INFO_STRU                   stCallInfo;
} MN_CALL_EVT_ORIG_CNF_STRU;

/*****************************************************************************
 结构名  : MN_CALL_EVT_ORIG_CNF_STRU
 结构说明: CALL模块呼叫相关的补充业务操作结果回复

 修改历史      :
  1.日    期   : 2013年6月23日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef MN_CALL_EVT_ORIG_CNF_STRU   MN_CALL_EVT_SUPS_CMD_CNF_STRU;

/*****************************************************************************
 结构名  : IMSA_SPM_CALL_MSG_STRU
 结构说明: IMSA模块呼叫相关的操作结果或者主动上报

 修改历史      :
  1.日    期   : 2013年6月23日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    VOS_UINT16                          usLen;
    MN_CALL_EVENT_ENUM_U32              enEventType;
    MN_CALL_INFO_STRU                   stCallInfo;
} IMSA_SPM_CALL_MSG_STRU;

/*****************************************************************************
 结构名    : IMSA_SPM_CALL_GET_CALL_INFO_CNF_STRU
 结构说明  : IMSA与SPM模块间查询Call信息的消息结构

  1.日    期   : 2013年7月16日
    作    者   : s00217060
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                                              ulMsgId;            /* _H2ASN_Skip */
    MN_CLIENT_ID_T                                          usClientId;                               /* 用户ID */
    VOS_UINT8                                               ucNumOfCalls;                           /* 所有正在通话的个数 */
    CALL_IMSA_GET_CALL_INFO_REQ_TYPE_ENMU_UINT8             enReqType;                              /* 请求类型 */
    MN_CALL_INFO_PARAM_STRU                                 astCallInfo[MN_CALL_MAX_NUM];           /* 所用正在通话的信息 */
} IMSA_SPM_CALL_GET_CALL_INFO_CNF_STRU;

/*****************************************************************************
 结构名    : IMSA_SPM_CALL_GET_CALL_INFO_IND_STRU
 结构说明  : IMSA与SPM模块间查询Call信息的消息结构

  1.日    期   : 2014年5月26日
    作    者   : w00209181
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucNumOfCalls;                           /* 所有正在通话的个数 */
    VOS_UINT8                                               aucReserve[3];
    MN_CALL_INFO_PARAM_STRU                                 astCallInfo[MN_CALL_MAX_NUM];           /* 所用正在通话的信息 */
} IMSA_SPM_CALL_GET_CALL_INFO_IND_STRU;


/*****************************************************************************
 结构名    : IMSA_SPM_CHANNEL_INFO_IND_STRU
 结构说明  : IMSA与SPM模块间语音带宽信息上报的消息结构

  1.日    期   : 2013年7月16日
    作    者   : s00217060
    修改内容   : 新增结构
  2.日    期   : 2013年3月29日
    作    者   : w00176964
    修改内容   : DTS2014032901140:优化接口,将不用的channel event信息拿掉
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;

    VOS_UINT8                           ucIsLocalAlertingFlag;                  /* 是否为本地播放回铃音标识1:本地播放回铃音；0:网络放音*/
    MN_CALL_CODEC_TYPE_ENUM_U8          enCodecType;                            /* codec type */
} IMSA_SPM_CHANNEL_INFO_IND_STRU;


/*****************************************************************************
 结构名    : IMSA_SPM_CALL_GET_CLPR_CNF_STRU
 结构说明  : 查询呼叫源号码回复结果

  1.日    期   : 2013年09月18日
    作    者   : Y00213812
    修改内容   : VOLTE 项目新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          ulRet;                                  /* MT_call&成功VOS_OK ，MO CALL或者失败时VOS_ERR */
    MN_CALL_REDIRECT_INFO               stRedirectInfo;                         /* IMS暂时不支持，回复0 */
}IMSA_SPM_CALL_GET_CLPR_CNF_STRU;
/*****************************************************************************
 结构名  : IMSA_SPM_CALL_TYPE_CHANGE_INFO_IND_STRU
 结构说明: IMSA 主动上报呼叫类型变更的消息

 修改历史      :
  1.日    期   : 2014年7月18日
    作    者   : w00209181
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                                      ulMsgId;                    /* _H2ASN_Skip */
    MN_CLIENT_ID_T                                  usClientId;
    MN_OPERATION_ID_T                               ucOpId;
    MN_CALL_ID_T                                    ucCallId;                     /* Call ID */
    MN_CALL_TYPE_ENUM_U8                            enSrcCallType;             /* 源呼叫类型 */
    MN_CALL_TYPE_ENUM_U8                            enDestCallType;           /* 目的呼叫类型 */
    VOS_UINT8                                       aucReserved[2];
    MN_CALL_EMERGENCY_CAT_STRU                      stEmergencyCat;           /* Emergency Catory */
}IMSA_SPM_CALL_TYPE_CHANGE_INFO_IND_STRU;



/*****************************************************************************
 结构名  : SPM_IMSA_CALL_MOIDY_REQ_STRU
 结构说明: IMSA模块modify 呼叫类型

 修改历史      :
  1.日    期   : 2014年6月4日
    作    者   : h00246512
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    MN_CALL_ID_T                        callId;                                 /* Call ID */
    MN_CALL_TYPE_ENUM_U8                enCurrCallType;                         /* 当前呼叫类型 */
    MN_CALL_TYPE_ENUM_U8                enExpectCallType;                       /* 期望呼叫类型 */
    VOS_UINT8                           aucReserved1[2];
}SPM_IMSA_CALL_MODIFY_REQ_STRU;

/*****************************************************************************
 结构名  : SPM_IMSA_CALL_MODIFY_CNF_STRU
 结构说明: IMSA模块modify 呼叫的结果

 修改历史      :
  1.日    期   : 2014年6月4日
    作    者   : h00246512
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    MN_CALL_ID_T                        callId;                                 /* Call ID */
    TAF_CS_CAUSE_ENUM_UINT32            enCause;                                /* 错误码 */
}IMSA_SPM_CALL_MODIFY_CNF_STRU;

/*****************************************************************************
 结构名  : SPM_IMSA_CALL_ANSWER_REMOTE_MODIFY_REQ_STRU
 结构说明: IMSA模块应答modify 呼叫的请求

 修改历史      :
  1.日    期   : 2014年6月4日
    作    者   : h00246512
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    MN_CALL_ID_T                        callId;                                 /* Call ID */
    MN_CALL_TYPE_ENUM_U8                enCurrCallType;                         /* 当前呼叫类型 */
    MN_CALL_TYPE_ENUM_U8                enExpectCallType;                       /* 期望呼叫类型 */
    VOS_UINT8                           aucReserved1[2];
}SPM_IMSA_CALL_ANSWER_REMOTE_MODIFY_REQ_STRU;

/*****************************************************************************
 结构名  : IMSA_SPM_CALL_ANSWER_REMOTE_MODIFY_CNF_STRU
 结构说明: IMSA模块应答modify呼叫的请求的回复

 修改历史      :
  1.日    期   : 2014年6月4日
    作    者   : h00246512
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    MN_CALL_ID_T                        callId;                                 /* Call ID */
    TAF_CS_CAUSE_ENUM_UINT32            enCause;                                /* 错误码 */
}IMSA_SPM_CALL_ANSWER_REMOTE_MODIFY_CNF_STRU;

/*****************************************************************************
 结构名  : SPM_IMSA_CALL_MODIFY_STATUS_IND_STRU
 结构说明: IMSA主动上报modify流程相关状态信息

 修改历史      :
  1.日    期   : 2014年6月4日
    作    者   : h00246512
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                                      ulMsgId;                    /* _H2ASN_Skip */
    MN_CLIENT_ID_T                                  usClientId;
    MN_OPERATION_ID_T                               ucOpId;
    MN_CALL_ID_T                                    callId;                     /* Call ID */
    SPM_IMSA_CALL_MODIFY_STATUS_ENUM_UINT8          enModifyStatus;             /* 当前的MODIFY的过程状态 */
    TAF_CALL_VOICE_DOMAIN_ENUM_UINT8                enVoiceDomain;              /* VOICE DOMAIN，这里始终是IMS域 */
    MN_CALL_TYPE_ENUM_U8                            enCurrCallType;             /* 当前呼叫类型 */
    MN_CALL_TYPE_ENUM_U8                            enExpectCallType;           /* 期望呼叫类型 */
    TAF_CS_CAUSE_ENUM_UINT32                        enCause;                    /* 错误码，仅在MODIFY_PROC_END有异常时才使用 */
}IMSA_SPM_CALL_MODIFY_STATUS_IND_STRU;


/*****************************************************************************
 结构名  : SPM_IMSA_CALL_ECONF_DIAL_REQ_STRU
 结构说明: SPM模块发起增强型多方通话

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : w00209181
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserved[1];
    TAF_CALL_ECONF_DIAL_REQ_STRU        stDialReq;
}SPM_IMSA_CALL_ECONF_DIAL_REQ_STRU;

/*****************************************************************************
 结构名  : SPM_IMSA_CALL_ECONF_ADD_USERS_REQ_STRU
 结构说明: SPM模块添加增强型多方通话与会者

 修改历史      :
  1.日    期   : 2014年11月28日
    作    者   : f00179208
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserved[1];
    TAF_CALL_ECONF_CALL_LIST_STRU       stEconfCalllist;                        /* 邀请参加多方通话会议者的信息 */
}SPM_IMSA_CALL_ECONF_ADD_USERS_REQ_STRU;

/*****************************************************************************
 结构名    : IMSA_SPM_CALL_ECONF_DIAL_CNF_STRU
 结构说明  : 创建增强型多方通话回复结果

  1.日    期   : 2014年10月31日
    作    者   : w00209181
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           ucCallId;
    TAF_CS_CAUSE_ENUM_UINT32            enCause;
}IMSA_SPM_CALL_ECONF_DIAL_CNF_STRU;

/*****************************************************************************
 结构名    : IMSA_SPM_CALL_ECONF_ADD_USERS_CNF_STRU
 结构说明  : 增强型多方通话添加与会者回复结果

  1.日    期   : 2014年11月28日
    作    者   : f0179208
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserve[1];
    TAF_CS_CAUSE_ENUM_UINT32            enCause;
}IMSA_SPM_CALL_ECONF_ADD_USERS_CNF_STRU;

/*****************************************************************************
 结构名  : SPM_IMSA_CALL_GET_ECONF_CALLED_INFO_STRU
 结构说明: IMSA模块获取增强型多方通话参与者的信息

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : w00209181
    修改内容   : 新增结构
*****************************************************************************/
typedef SPM_IMSA_CALL_GET_CALL_INFO_REQ_STRU  SPM_IMSA_CALL_GET_ECONF_CALLED_INFO_REQ_STRU;

/*****************************************************************************
 结构名    : IMSA_SPM_CALL_GET_ECONF_CALLED_INFO_CNF_STRU
 结构说明  : IMSA与SPM模块间查询Call信息的消息结构

  1.日    期   : 2014年10月30日
    作    者   : W00209181
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                                              ulMsgId;            /* _H2ASN_Skip */
    MN_CLIENT_ID_T                                          usClientId;         /* 用户ID */
    MN_OPERATION_ID_T                                       ucOpId;
    VOS_UINT8                                               ucNumOfMaxCalls;
    VOS_UINT8                                               ucNumOfCalls;       /* 所有正在通话的个数 */
    CALL_IMSA_GET_CALL_INFO_REQ_TYPE_ENMU_UINT8             enReqType;          /* 请求类型 */
    VOS_UINT8                                               aucReserve[2];
    TAF_CALL_ECONF_INFO_PARAM_STRU                          astCallInfo[TAF_CALL_MAX_ECONF_CALLED_NUM];     /* 所用正在通话的信息 */
} IMSA_SPM_CALL_GET_ECONF_CALLED_INFO_CNF_STRU;

/*****************************************************************************
 结构名  : IMSA_SPM_CALL_ECONF_NOTIFY_IND_STRU
 结构说明: IMSA主动上报ECONF NOTIFY流程相关状态信息

 修改历史      :
  1.日    期   : 2014年11月28日
    作    者   : f00179208
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                                      ulMsgId;                    /* _H2ASN_Skip */
    MN_CLIENT_ID_T                                  usClientId;
    MN_OPERATION_ID_T                               ucOpId;
    VOS_UINT8                                       ucNumOfCalls;               /* 所有正在通话的个数 */
    TAF_CALL_ECONF_INFO_PARAM_STRU                  astCallInfo[TAF_CALL_MAX_ECONF_CALLED_NUM];     /* 所用正在通话的信息 */
}IMSA_SPM_CALL_ECONF_NOTIFY_IND_STRU;


typedef struct
{
    VOS_UINT32                          ulMsgId;                                /*_H2ASN_MsgChoice_Export SPM_IMSA_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          SPM_IMSA_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}SPM_IMSA_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    SPM_IMSA_INTERFACE_MSG_DATA           stMsgData;
} SpmImsaInterface_MSG;

/*****************************************************************************
  4 宏定义
*****************************************************************************/


/*****************************************************************************
  5 全局变量声明
*****************************************************************************/


/*****************************************************************************
  6 接口函数声明
*****************************************************************************/
extern VOS_UINT32 IMSA_SpmGetCallInfo(IMSA_SPM_CALL_GET_CALL_INFO_IND_STRU *pstCallInfo);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* SPM_IMSA_INTERFACE_H */
