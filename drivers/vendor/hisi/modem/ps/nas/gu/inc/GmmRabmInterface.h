/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : GmmRabmInterface.h
  版 本 号   : 初稿
  作    者   : anhuiqing / 00165503
  生成日期   : 2011年04月11日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2011年03月30日
    作    者   : anhuiqing / 00165503
    修改内容   : 创建文件

******************************************************************************/
#ifndef _GMM_RABM_INTERFACE_H_
#define _GMM_RABM_INTERFACE_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define GMM_RABM_RRC_EST_CAUSE_ORG_SUBS_CALL    (0)         /* Originating Subscribed traffic clas Call */
#define GMM_RABM_RRC_EST_CAUSE_ORG_CONV_CALL    (1)         /* Originating Conversational Call          */
#define GMM_RABM_RRC_EST_CAUSE_ORG_STM_CALL     (2)         /* Originating Streaming Call               */
#define GMM_RABM_RRC_EST_CAUSE_ORG_INTER_CALL   (3)         /* Originating Interactive Call             */
#define GMM_RABM_RRC_EST_CAUSE_ORG_BG_CALL      (4)         /* Originating Background Call              */


/* SERVICE REQUEST成功失败标志 */
#define GMM_RABM_SERVICEREQ_SUCCESS             (0)         /* SERVICE REQUEST成功 */
#define GMM_RABM_SERVICEREQ_FAILURE             (1)         /* SERVICE REQUEST失败 */

#define GMM_RABM_SERVICEREQ_DELAYED             (2)         /* SERVICE REQUEST延迟重发 */

#define GMM_RABM_SERVICEREQ_OOS                 (3)         /* AS搜网导致建链失败 */

/* RABM接收PDU数据的最大长度 */
#ifndef RABM_RECV_N_PDU_NUM_LIST_IE_MAXLEN
#define RABM_RECV_N_PDU_NUM_LIST_IE_MAXLEN      (19)
#endif

/* ucGmmRauCause */
#define GMM_RABM_RAU_UNDER_NORMAL               (0)         /* 在正常条件下发起RAU       */
#define GMM_RABM_RAU_UNDER_HANDOVER             (1)         /* 在异系统切换条件下发起RAU */


/* ucResult */
#define GMM_RABM_RAU_SUCCESS                    (0)
#define GMM_RABM_RAU_FAILURE                    (1)


/* ucNpduValidFlg 宏值定义 */
#define GMM_RABM_NPDU_INVALID                   (0)         /* N-PDU数据无效 */
#define GMM_RABM_NPDU_VALID                     (1)         /* N-PDU数据有效 */


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 结构名称   : GMM_RABM_MSG_ID_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : GMM和RABM之间的原语
*****************************************************************************/
enum GMM_RABM_MSG_ID_ENUM
{
    ID_RABM_GMM_REESTABLISH_REQ                 = 0x0000,           /* _H2ASN_MsgChoice GMMRABM_REESTABLISH_REQ_STRU */
    ID_RABM_GMM_RAB_REL_IND                     = 0x0001,           /* _H2ASN_MsgChoice GMMRABM_RAB_REL_IND_STRU */
    ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP         = 0x0002,           /* _H2ASN_MsgChoice GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG */
    ID_RABM_GMM_MML_PROC_STATUS_QRY_REQ         = 0x0003,           /* _H2ASN_MsgChoice RABM_GMM_MML_RPOCEDURE_SERVICE_QRY_REQ_STRU */

    ID_RABM_GMM_RAB_SETUP_IND                   = 0x0004,           /* _H2ASN_MsgChoice GMMRABM_RAB_SETUP_IND_STRU */

    ID_GMM_RABM_REESTABLISH_CNF                 = 0x1000,           /* _H2ASN_MsgChoice GMMRABM_REESTABLISH_CNF_STRU */
    ID_GMM_RABM_SYS_SRV_CHG_IND                 = 0x1001,           /* _H2ASN_MsgChoice GMM_RABM_SYS_SRV_CHG_IND_STRU */
    ID_GMM_RABM_ROUTING_AREA_UPDATE_IND         = 0x1002,           /* _H2ASN_MsgChoice GMMRABM_ROUTING_AREA_UPDATE_IND_MSG */
    ID_GMM_RABM_MML_PROC_STATUS_QRY_CNF         = 0x1003,           /* _H2ASN_MsgChoice GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU */

    ID_GMM_RABM_MSG_BUTT
};
typedef VOS_UINT32 GMM_RABM_MSG_ID_ENUM_UINT32;


typedef VOS_UINT32 GMM_RABM_NET_RAT_ENUM_UINT32;


/* 当前RABM工作状态 */
typedef enum
{
    RABM_3G_ENUM = 0,
    RABM_2G_ENUM
} RABM_CUR_NET_ENUM;

enum RABM_RELRRC_OPERATE_ENUM
{
    RABM_FASTDORM_ENUM      = 0,
    RABM_RELEASE_RRC_ENUM   = 1,
    RABM_VOICEPREFER_ENUM   = 2
};
typedef VOS_UINT32 RABM_RELRRC_OPERATE_ENUM_UINT32;

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
 结构名    : GMMRABM_REESTABLISH_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 原语ID_RABM_GMM_REESTABLISH_REQ的结构体
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT32                          ulRrcEstCause;      /* RRC连接建立的原因 */
    VOS_UINT16                          usPdpContextStatus; /* 需要填充的PDP Context状态 */
#if(PS_UE_REL_VER >= PS_PTL_VER_R7)
    VOS_UINT16                          usUplinkDataStatus; /* 需要填充的PDP Context状态 */
#else
    VOS_UINT8                           aucRsv[2];          /* 4字节对齐                 */
#endif

} GMMRABM_REESTABLISH_REQ_STRU;


/*****************************************************************************
 结构名    : GMMRABM_REESTABLISH_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 原语ID_GMM_RABM_REESTABLISH_CNF的结构体
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT32                          ulResult;           /* SERVICE REQUEST成功失败标志 */

} GMMRABM_REESTABLISH_CNF_STRU;


/*****************************************************************************
 结构名    : GMMRABM_ROUTING_AREA_UPDATE_IND_MSG
 协议表格  :
 ASN.1描述 :
 结构说明  : 原语ID_RABM_GMM_ROUTING_AREA_UPDATE_IND的结构体
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT32                          ulTLLI;             /* 更新的TLLI值 */
    VOS_UINT8                           aucRecvNPDUNumListIE[RABM_RECV_N_PDU_NUM_LIST_IE_MAXLEN];
    VOS_UINT8                           ucGmmRauCause;      /* 当前GMM发起RAU时的原因 */
    VOS_UINT8                           ucResult;
    VOS_UINT8                           aucReserve[3];
} GMMRABM_ROUTING_AREA_UPDATE_IND_MSG;


/*****************************************************************************
 结构名    : GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG
 协议表格  :
 ASN.1描述 :
 结构说明  : 原语ID_GMM_RABM_ROUTING_AREA_UPDATE_IND的结构体
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT8                           ucNpduValidFlg;     /* N-PDU number有效标志 */
    VOS_UINT8                           aucRecvNPDUNumListIE[RABM_RECV_N_PDU_NUM_LIST_IE_MAXLEN];

} GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG;


/*****************************************************************************
 结构名    : GMMRABM_RAB_REL_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 原语ID_RABM_GMM_RAB_REL_IND的结构体
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */

} GMMRABM_RAB_REL_IND_STRU;

/*****************************************************************************
 结构名    : GMMRABM_RAB_SETUP_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 原语ID_RABM_GMM_RAB_SETUP_IND的结构体
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */        /* _H2ASN_Skip */

} GMMRABM_RAB_SETUP_IND_STRU;


/*****************************************************************************
 结构名    : GMM_RABM_SYS_SRV_CHG_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 原语GMMRABM_SYS_SRV_CHG_IND的结构体
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* 消息头         */ /* _H2ASN_Skip */
    GMM_RABM_NET_RAT_ENUM_UINT32        enSysMode;          /* 当前系统模式   */
    VOS_BOOL                            bRatChangeFlg;      /* 异系统切换标志 */
    VOS_BOOL                            bDataSuspendFlg;    /* 挂起指示标志   */
    VOS_UINT8                           ucReserve[3];
    VOS_UINT8                           ucRebuildRabFlag;    /* 是否需要重建RB信息 */
} GMM_RABM_SYS_SRV_CHG_IND_STRU;

/*****************************************************************************
 结构名    : RABM_GMM_MML_PROC_STATUS_QRY_REQ_STRU
 结构说明  : RABM使用此原语，向GMM查询，当前MM子层的信令流程状态和业务状态
 1.日    期   : 2011年10月18日
   作    者   : h44270
   修改内容   : 新生成函数
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                     stMsgHeader;

    RABM_RELRRC_OPERATE_ENUM_UINT32                     enOptFlag;
} RABM_GMM_MML_PROC_STATUS_QRY_REQ_STRU;

/*****************************************************************************
 结构名    : RABM_GMM_MML_PROC_STATUS_STRU
 结构说明  : 包含当前是否有GMM专有流程，PS域短信，CS域信令连接
 1.日    期   : 2011年10月18日
   作    者   : h44270
   修改内容   : 新生成函数
 2.日    期   : 2013年7月11日
    作    者   : M00217266
    修改内容  : Optimize RIL:
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpGmmSpecificProcedure: 1;           /* 是否存在GMM专有流程 */
    VOS_UINT32                          bitOpPsSmsService: 1;                   /* 是否存在PS域短信 */
    VOS_UINT32                          bitOpCsSignal: 1;                       /* 是否存在CS域信令连接 */

    VOS_UINT32                          bitSpare: 29;
    RABM_RELRRC_OPERATE_ENUM_UINT32     enOptFlag;
} RABM_GMM_MML_PROC_STATUS_STRU;



/*****************************************************************************
 结构名    : GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU
 结构说明  : GMM通过此原语，告知RABM当前MM子层的信令流程状态和业务状态
 1.日    期   : 2011年10月18日
   作    者   : h44270
   修改内容   : 新生成函数
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    RABM_GMM_MML_PROC_STATUS_STRU       stMmlProcStatus;                        /* GMM专有流程，PS域短信，CS域信令连接状态 */
} GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU;



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
    GMM_RABM_MSG_ID_ENUM_UINT32         enMsgId;            /* _H2ASN_MsgChoice_Export GMM_RABM_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          GMM_RABM_MSG_ID_ENUM_UINT32
    ****************************************************************************/
} GMM_RABM_INTERFACE_MSG_DATA;
/* _H2ASN_Length UINT32 */

typedef struct
{
    VOS_MSG_HEADER
    GMM_RABM_INTERFACE_MSG_DATA         stMsgData;
} GmmRabmInterface_MSG;


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_UINT32 NAS_RABM_IsPsRbExist(VOS_VOID);


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

