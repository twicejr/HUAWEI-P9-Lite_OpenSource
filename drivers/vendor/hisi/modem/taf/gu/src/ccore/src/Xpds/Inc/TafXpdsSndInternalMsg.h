/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsSndInternalMsg.h
  版 本 号   : 初稿
  作    者   : g00261581
  生成日期   : 2015年8月21日
  最近修改   :
  功能描述   : TafXpdsSndInternalMsg.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年8月20日
    作    者   : g00261581
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAF_XPDS_SND_INTERNAL_MSG_H__
#define __TAF_XPDS_SND_INTERNAL_MSG_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafXpdsCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM
 枚举说明  : XPDS内部消息名枚举定义
 1.日    期   : 2015年8月21日
   作    者   : g00261581
   修改内容   : 新建
*****************************************************************************/
enum TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM
{
    ID_TAF_XPDS_XPDS_UP_LINK_CTRL_REQ                       = 0x0000, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU */
    ID_TAF_XPDS_XPDS_UP_LINK_CTRL_CNF                       = 0x0001, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_UP_LINK_CTRL_CNF_STRU */
    ID_TAF_XPDS_XPDS_INT_MPC_PROC_START_REQ                 = 0x0002, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_INT_MPC_PROC_START_REQ_STRU*/
    ID_TAF_XPDS_XPDS_INT_MPC_PROC_RSLT_IND                  = 0x0003, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_INT_MPC_PROC_RSLT_IND_STRU*/
    ID_TAF_XPDS_XPDS_INT_RCV_MPC_START_POS_RESP             = 0x0004, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_INT_RCV_MPC_START_POS_RESP_STRU*/
    ID_TAF_XPDS_XPDS_INT_RCV_MPC_POS_REPORT_RESP            = 0x0005, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_INT_RCV_MPC_POS_REPORT_RESP_STRU*/

    ID_TAF_XPDS_XPDS_CP_LINK_START_REQ                      = 0x0006, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_CP_LINK_PROC_START_REQ_STRU */
    ID_TAF_XPDS_XPDS_CP_LINK_RESULT_IND                     = 0x0007, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_CP_LINK_PROC_RSLT_IND_STRU */

    ID_TAF_XPDS_XPDS_CP_PDE_PROC_START_REQ                  = 0x0008, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_CP_PDE_PROC_START_REQ_STRU */
    ID_TAF_XPDS_XPDS_PDE_PROC_RSLT_IND                      = 0x0009, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_PDE_PROC_RSLT_IND_STRU */
    ID_TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND                   = 0x000A, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU */
    ID_TAF_XPDS_XPDS_PDE_PROC_START_REQ                     = 0x000B, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_PDE_PROC_START_REQ_STRU */
    ID_TAF_XPDS_XPDS_INT_XSMS_CANCEL_NI_TRACK_SESSION       = 0x000C, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_INT_RCV_MPC_POS_REPORT_RESP_STRU */
    ID_TAF_XPDS_XPDS_INT_XSMS_REFRESH_MR_TRACK_SESSION      = 0x000D, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_INT_XSMS_CANCEL_NI_TRACK_SESSION_STRU */

    ID_TAF_XPDS_XPDS_PPM_COMPLETE_NI                        = 0x000E, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_PPM_COMPLETE_MSG_STRU*/

    ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND    = 0x000F, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU */
    ID_TAF_XPDS_XPDS_CP_PDE_PROC_RSLT_IND                   = 0x0010, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_PDE_PROC_RSLT_IND_STRU */


    ID_TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_BUTT  = 0xFFFF
};
typedef VOS_UINT32 TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名    : TAF_XPDS_BIND_SERVER_ERROR_CAUSE_ENUM
 枚举说明  : 服务器bind/release 结果的错误原因值
 1.日    期   : 2015年8月27日
   作    者   : g00261581
   修改内容   : 新增
*****************************************************************************/
enum TAF_XPDS_BIND_SERVER_ERROR_CAUSE_ENUM
{
    TAF_XPDS_BIND_SERVER_NO_ERROR,

    TAF_XPDS_BIND_SERVER_MPC_CONNECT_FAIL,
    TAF_XPDS_BIND_SERVER_PDE_CONNECT_FAIL,

    TAF_XPDS_BIND_SERVER_ERROR_CAUSE_BUTT,
};
typedef VOS_UINT8 TAF_XPDS_BIND_SERVER_ERROR_CAUSE_ENUM_UINT8;

/*****************************************************************************
枚举名    : TAF_XPDS_SERVER_BIND_OPER_ENUM
枚举说明  : MPC/PDE Server Bind/Release控制

  1.日    期   : 2015年8月20日
    作    者   : g00261581
    修改内容   : 新增枚举
*****************************************************************************/
enum TAF_XPDS_SERVER_BIND_OPER_ENUM
{
    TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET,
    TAF_XPDS_SERVER_BIND_OPER_OPEN_SOCKET,

    TAF_XPDS_SERVER_BIND_OPER_BUTT
};
typedef VOS_UINT8 TAF_XPDS_SERVER_BIND_OPER_ENUM_UINT8;


enum TAF_XPDS_MPC_OPER_TYPE_ENUM
{
    TAF_XPDS_MPC_OPER_START_POS_REQ = 0x01,
    TAF_XPDS_MPC_OPER_POS_REPORT,

    TAF_XPDS_MPC_OPER_BUTT,
};
typedef VOS_UINT32 TAF_XPDS_MPC_OPER_TYPE_ENUM_UINT32;

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
 结构名    : TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU
 结构说明  : MPC/PDE Server Socket Bind Req
 1.日    期   : 2015年08月22日
   作    者   : g00261581
   修改内容   : MPC/PDE Server的操作请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* 消息头 */    /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    TAF_XPDS_SERVER_BIND_OPER_ENUM_UINT8                    enMpcBindOpt;
    TAF_XPDS_SERVER_BIND_OPER_ENUM_UINT8                    enPdeBindOpt;
    VOS_UINT8                                               aucReserved[2];
} TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_XPDS_UP_LINK_CTRL_CNF_STRU
 结构说明  : MPC/PDE Server Socket Bind Req
 1.日    期   : 2015年08月23日
   作    者   : g00261581
   修改内容   : MPC/PDE的操作回复
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                                                  /* 消息头 */    /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32                      enRslt;
}TAF_XPDS_XPDS_UP_LINK_CTRL_CNF_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_XPDS_PDE_PROC_START_REQ_STRU
 结构说明  : XPDS PDE Proc Start Req内部消息结构体定义
 1.日    期   : 2015年08月27日
   作    者   : y00174758
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* _H2ASN_Skip */
    TAF_XPDS_FIX_MODE_ENUM_UINT8                            enFixMode;
    VOS_UINT8                                               aucRsv[3];
}TAF_XPDS_XPDS_PDE_PROC_START_REQ_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_XPDS_CP_PDE_PROC_START_REQ_STRU
 结构说明  : XPDS PDE Proc Start Req内部消息结构体定义
 1.日    期   : 2015年08月27日
   作    者   : c00299064
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* _H2ASN_Skip */
    TAF_XPDS_FIX_MODE_ENUM_UINT8                            enFixMode;
    VOS_UINT8                                               aucRsv[3];
}TAF_XPDS_XPDS_CP_PDE_PROC_START_REQ_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_XPDS_CP_PDE_PROC_START_REQ_STRU
 结构说明  : XPDS PDE Proc Start Req内部消息结构体定义
 1.日    期   : 2015年08月27日
   作    者   : c00299064
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* _H2ASN_Skip */
}TAF_XPDS_XPDS_CP_LINK_PROC_START_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32                      enRslt;
}TAF_XPDS_XPDS_PDE_PROC_RSLT_IND_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU
 结构说明  : XPDS Forward Pde Data Ind内部消息结构体定义
 1.日    期   : 2015年08月27日
   作    者   : y00174758
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT32                                              ulDataMask;
    TAF_XPDS_CALL_TYPE_ENUM_UINT8                           enCallType;
    VOS_UINT8                                               aucRsv[3];
}TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU;


/*****************************************************************************
 结构名    : TAF_XPDS_XPDS_INT_MPC_PROC_START_REQ_STRU
 结构说明  : XPDS MPC PROC START REQ内部消息结构体定义
 1.日    期   : 2015年08月27日
   作    者   : c00299064
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* _H2ASN_Skip */
    TAF_XPDS_MPC_OPER_TYPE_ENUM_UINT32                      enMpcOperation;
}TAF_XPDS_XPDS_INT_MPC_PROC_START_REQ_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_XPDS_INT_MPC_PROC_RSLT_IND_STRU
 结构说明  : XPDS Receive MPC Data Ind内部消息结构体定义
 1.日    期   : 2015年08月27日
   作    者   : c00299064
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* _H2ASN_Skip */
    TAF_XPDS_MPC_OPER_TYPE_ENUM_UINT32                      enMpcOperation;
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32                      enMpcOperRslt;
}TAF_XPDS_XPDS_INT_MPC_PROC_RSLT_IND_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_XPDS_INT_RCV_MPC_START_POS_RESP_STRU
 结构说明  : TAF_XPDS_XPDS_INT_RCV_MPC_START_POS_RESP_STRU 内部消息结构体定义
 1.日    期   : 2015年08月27日
   作    者   : c00299064
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* _H2ASN_Skip */
    TAF_XPDS_MPC_START_POS_RSP_STRU                         stStartPosRsp;
}TAF_XPDS_XPDS_INT_RCV_MPC_START_POS_RESP_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_XPDS_INT_RCV_MPC_POS_REPORT_RESP_STRU
 结构说明  : TAF_XPDS_XPDS_INT_RCV_MPC_POS_REPORT_RESP_STRU 内部消息结构体定义
 1.日    期   : 2015年08月27日
   作    者   : c00299064
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* _H2ASN_Skip */
    TAF_XPDS_MPC_POS_REPORT_RSP_STRU                        stPosReportRsp;
}TAF_XPDS_XPDS_INT_RCV_MPC_POS_REPORT_RESP_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_XPDS_INT_XSMS_CANCEL_NI_TRACK_SESSION
 结构说明  : TAF_XPDS_XPDS_INT_XSMS_CANCEL_NI_TRACK_SESSION 内部消息结构体定义
 1.日    期   : 2015年08月27日
   作    者   : c00299064
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* _H2ASN_Skip */
}TAF_XPDS_XPDS_INT_XSMS_CANCEL_NI_TRACK_SESSION_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_XPDS_INT_XSMS_CANCEL_NI_TRACK_SESSION
 结构说明  : TAF_XPDS_XPDS_INT_XSMS_CANCEL_NI_TRACK_SESSION 内部消息结构体定义
 1.日    期   : 2015年08月27日
   作    者   : c00299064
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32   enMsgId;                                /* _H2ASN_Skip */
}TAF_XPDS_XPDS_PPM_COMPLETE_MSG_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU
 结构说明  : TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU 内部消息结构体定义
 1.日    期   : 2015年09月10日
   作    者   : g00261581
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* _H2ASN_Skip */
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32                      enAbortScene;
}TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_XPDS_INT_XSMS_CANCEL_NI_TRACK_SESSION
 结构说明  : TAF_XPDS_XPDS_INT_XSMS_CANCEL_NI_TRACK_SESSION 内部消息结构体定义
 1.日    期   : 2015年08月27日
   作    者   : c00299064
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* _H2ASN_Skip */
    TAF_XPDS_REJ_MR_TRACK_CAUSE_CODE_ENUM_UINT8             enCauseCode;
    VOS_UINT8                                               aucRsv[3];
}TAF_XPDS_XPDS_INT_XSMS_REFRESH_MR_TRACK_SESSION_STRU;





/*****************************************************************************
 结构名    : TAF_XPDS_XPDS_CP_LINK_PROC_RSLT_IND_STRU
 结构说明  : The message for cp link proc result
 1.日    期   : 2015年09月22日
   作    者   : a00903922
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32                      enRslt;
}TAF_XPDS_XPDS_CP_LINK_PROC_RSLT_IND_STRU;



/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId; /* _H2ASN_MsgChoice_Export TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                                               aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_XPDS_INTERNAL_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    TAF_XPDS_INTERNAL_MSG_DATA          stMsgData;
}TafXpdsSndInternalMsg_MSG;

/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID TAF_XPDS_SndInternalServerBindOperReq(
    TAF_XPDS_SERVER_BIND_OPER_ENUM_UINT8                    enMpcBindOpt,
    TAF_XPDS_SERVER_BIND_OPER_ENUM_UINT8                    enPdeBindOpt
);

VOS_VOID TAF_XPDS_SndInternalServerBindRsltCnf(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enRslt
);

VOS_VOID TAF_XPDS_SndInternalPdeProcStartReq(
    TAF_XPDS_FIX_MODE_ENUM_UINT8                            enFixMode
);

VOS_VOID TAF_XPDS_SndInternalPdeProcRsltInd(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enRslt
);

VOS_VOID TAF_XPDS_SndInternalCpPdeProcRsltInd(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32                      enRslt
);

VOS_VOID TAF_XPDS_SndInternalForwardPdeDataInd(
    VOS_UINT32                                              ulDataMask,
    TAF_XPDS_CALL_TYPE_ENUM_UINT8                           enCallType
);


VOS_VOID TAF_XPDS_SndInternalStartMpcProcess(
    TAF_XPDS_MPC_OPER_TYPE_ENUM_UINT32                      enMpcOperation
);

VOS_VOID TAF_XPDS_SndInternalMpcRslt(
    TAF_XPDS_MPC_OPER_TYPE_ENUM_UINT32                      enMpcOperation,
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32                      enMpcOperRslt
);

VOS_VOID TAF_XPDS_SndInternalMpcStartPosResp(
    TAF_XPDS_MPC_START_POS_RSP_STRU                         *pstStartPosRsp
);

VOS_VOID TAF_XPDS_SndInternalMpcPosReportResp(
    TAF_XPDS_MPC_POS_REPORT_RSP_STRU                        *pstPosReportRsp
);

VOS_VOID TAF_XPDS_SndInternalXsmsCancelNiTracking(
    VOS_VOID
);

VOS_VOID TAF_XPDS_SndInternalXsmsRefreshMrTracking(
    TAF_XPDS_REJ_MR_TRACK_CAUSE_CODE_ENUM_UINT8             enCauseCode
);

VOS_VOID TAF_XPDS_SndInternalCpPdeProcStartReq(
    VOS_VOID
);

extern VOS_VOID TAF_XPDS_SndInternalPpmCompleteMsg(
    VOS_VOID
);

VOS_VOID TAF_XPDS_SndInternalAbnormalAbortAgpsSessionInd(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32                      enAbortScene
);

VOS_UINT32 TAF_XPDS_SndControlPlaneLinkStart_CpLinkCtrl(
   VOS_VOID
);

extern VOS_UINT32 TAF_XPDS_SndInternalCpLinkResultMsg_CpLinkCtrl(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32 enRslt
);


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

#endif /* end of CnasXsdSndInternalMsg.h */
