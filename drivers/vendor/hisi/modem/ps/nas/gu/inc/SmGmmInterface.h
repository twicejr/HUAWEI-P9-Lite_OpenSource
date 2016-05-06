/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : SmGmmInterface.h
  Description : SM与GMM接口头文件
  History     :
      1.  张志勇     2003.12.05   文件头作成
      2.日    期  : 2006年12月4日
        作    者  : luojian id:60022475
        修改内容  : 增加 #pragma pack(4)，问题单号:A32D07779
      3.日    期   : 2007年10月27日
        作    者   : L47619
        修改内容   : 问题单号:A32D13038
      4.日    期   : 2011年04月23日
        作    者   : L00171473
        修改内容   : for V7R1 porting, 去掉枚举成员最后的逗号，避免编译WARNING
*******************************************************************************/

/*******************************************************************************
**************************  GMM－SM 原语标识  **********************************
*******************************************************************************/

#ifndef _SM_GMM_INTERFACE_H_
#define _SM_GMM_INTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */
#pragma pack(4)


/* SM发给GMM的消息 */
#define GMMSM_ESTABLISH_REQ                                 0
#define GMMSM_DATA_REQ                                      2
#define GMMSM_PDP_DEACTIVATED_IND                           (8)
#define GMMSM_PDP_MODIFY_IND                                (0x0A)

#define GMMSM_BEGIN_SESSION_NOTIFY                          (14)
#define GMMSM_END_SESSION_NOTIFY                            (16)

/* SM接收GMM的原语 */
#define GMMSM_ESTABLISH_CNF                                 1
#define GMMSM_DATA_IND                                      3
#define GMMSM_STATUS_IND                                    5
#define GMMSM_SERVICE_REJ                                   7
#define GMMSM_SYS_INFO_IND                                  9
#define GMMSM_REL_IND                                       11
/* SM与GMM之间的双向原语 */
#define GMMSM_PDP_STATUS_IND                                4 /* GMM收到此原语更新本地PDP状态;
                                                                 网侧指示PDP状态时GMM通过此原语通知SM*/
#define GMMSM_ABORT_REQ                                     12

#define GMMSM_SIG_CONN_IND                                  13

#define GMM_SM_CAUSE_GMM_SECTION_BEGIN      (0x0000)
#define GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN   (0x0100)

#define GMM_SM_CAUSE_GMM_NW_CAUSE_OFFSET    GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN


/*****************************************************************************
 枚举名  : GMM_SM_CAUSE_ENUM
 枚举说明: GMM上报的原因值

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 新增枚举
*****************************************************************************/
enum GMM_SM_CAUSE_ENUM
{
    /*----------------------------------------------------------------------
       GMM上报的内部原因值, 取值范围[0x0000, 0x00FF]
       方向: GMM -> SM
       说明: UNKNOWN为错误码分段的最后一个错误码
    *---------------------------------------------------------------------*/
    GMM_SM_CAUSE_SUCCESS                                = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 0),
    GMM_SM_CAUSE_GPRS_NOT_SUPPORT                       = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 1),
    GMM_SM_CAUSE_ATTACH_MAX_TIMES                       = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 2),
    GMM_SM_CAUSE_FORBID_LA                              = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 3),
    GMM_SM_CAUSE_AUTHENTICATION_FAIL                    = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 4),
    GMM_SM_CAUSE_AUTHENTICATION_REJ                     = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 5),
    GMM_SM_CAUSE_PS_DETACH                              = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 6),
    GMM_SM_CAUSE_RRC_EST_FAIL                           = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 7),
    GMM_SM_CAUSE_ACCESS_BARRED                          = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 8),
    GMM_SM_CAUSE_SIM_PS_DOMAIN_REG_INVALID              = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 9),
    GMM_SM_CAUSE_T3310_EXPIRED                          = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 10),
    GMM_SM_CAUSE_T3317_EXPIRED                          = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 11),
    GMM_SM_CAUSE_TIMER_SIGNALING_PROTECT_EXPIRED        = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 12),
    GMM_SM_CAUSE_STARTUP                                = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 13),
    GMM_SM_CAUSE_NULL                                   = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 14),
    GMM_SM_CAUSE_GMM_RESET                              = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 15),
    GMM_SM_CAUSE_LTE_MO_DETACH                          = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 16),
    GMM_SM_CAUSE_RAU_ACCEPT                             = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 17),
    GMM_SM_CAUSE_SERVICE_ACCEPT                         = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 18),
    GMM_SM_CAUSE_UNKNOWN                                = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 255),

    /*----------------------------------------------------------------------
       GMM上报的网络原因值, 取值范围[0x0100, 0x01FF]
       方向: GMM -> SM
       由于3GPP协议已经定义了具体的GMM网络原因值, GMM上报的取值为协议定义
       的原因值加上偏移量(0x100),
       Gmm Cause: Refer to TS 24.008 section 10.5.5.14
    *---------------------------------------------------------------------*/
    GMM_SM_CAUSE_IMSI_UNKNOWN_IN_HLR                    = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 2),
    GMM_SM_CAUSE_ILLEGAL_MS                             = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 3),
    GMM_SM_CAUSE_IMSI_NOT_ACCEPTED                      = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 5),
    GMM_SM_CAUSE_ILLEGAL_ME                             = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 6),
    GMM_SM_CAUSE_GPRS_SERV_NOT_ALLOW                    = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 7),
    GMM_SM_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW  = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 8),
    GMM_SM_CAUSE_MS_ID_NOT_DERIVED                      = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 9),
    GMM_SM_CAUSE_IMPLICIT_DETACHED                      = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 10),
    GMM_SM_CAUSE_PLMN_NOT_ALLOW                         = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 11),
    GMM_SM_CAUSE_LA_NOT_ALLOW                           = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 12),
    GMM_SM_CAUSE_ROAMING_NOT_ALLOW_IN_LA                = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 13),
    GMM_SM_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN            = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 14),
    GMM_SM_CAUSE_NO_SUITABL_CELL                        = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 15),
    GMM_SM_CAUSE_MSC_UNREACHABLE                        = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 16),
    GMM_SM_CAUSE_NETWORK_FAILURE                        = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 17),
    GMM_SM_CAUSE_MAC_FAILURE                            = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 20),
    GMM_SM_CAUSE_SYNCH_FAILURE                          = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 21),
    GMM_SM_CAUSE_PROCEDURE_CONGESTION                   = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 22),
    GMM_SM_CAUSE_GSM_AUT_UNACCEPTABLE                   = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 23),
    GMM_SM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG            = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 25),
    GMM_SM_CAUSE_NO_PDP_CONTEXT_ACT                     = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 40),
    GMM_SM_CAUSE_RETRY_UPON_ENTRY_CELL                  = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 60),
    GMM_SM_CAUSE_SEMANTICALLY_INCORRECT_MSG             = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 95),
    GMM_SM_CAUSE_INVALID_MANDATORY_INF                  = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 96),
    GMM_SM_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE             = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 97),
    GMM_SM_CAUSE_MSG_TYPE_NOT_COMPATIBLE                = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 98),
    GMM_SM_CAUSE_IE_NONEXIST_NOTIMPLEMENTED             = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 99),
    GMM_SM_CAUSE_CONDITIONAL_IE_ERROR                   = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 100),
    GMM_SM_CAUSE_MSG_NOT_COMPATIBLE                     = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 101),
    GMM_SM_CAUSE_PROTOCOL_ERROR                         = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 111),

    GMM_SM_CAUSE_BUTT
};
typedef VOS_UINT16 GMM_SM_CAUSE_ENUM_UINT16 ;


/*****************************************************************************
 结构名    : GMMSM_ABORT_REQ_STRU
 结构说明  : 原语GMMSM_ABORT_REQ的结构体
  1.日    期   : 2011年12月20日
    作    者   : A00165503
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* 消息头     */    /* _H2ASN_Skip */

} GMMSM_ABORT_REQ_STRU;
#define GMMSM_PDP_STATE_INACTIVE                            (0)                 /* PDP上下文非激活状态 */
#define GMMSM_PDP_STATE_ACTIVE                              (1)                 /* PDP上下文激活状态 */
#define GMMSM_PDP_STATE_ACTIVE_PENDING                      (2)                 /* PDP上下文激活过程中状态 */
#define GMMSM_PDP_STATE_INACTIVE_PENDING                    (3)               /* PDP上下文去激活过程中状态 */
#define GMMSM_MAX_NSAPI_NUM                                 (11)                /* NSAPI的最大值 */
/* 原语GMMSM_ESTABLISH_REQ的结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */
}GMMSM_ESTABLISH_REQ_STRU;

/* 原语GMMSM_ESTABLISH_CNF的结构体 */
/* ulEstResult 取值 */
#define    GMM_SM_EST_SUCCESS       1                                           /* 注册成功                                 */
#define    GMM_SM_EST_FAILURE       0                                           /* 注册失败                                 */

/*****************************************************************************
 结构名  : GMMSM_ESTABLISH_CNF_STRU
 结构说明: GMMSM_ESTABLISH_CNF原语结构

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 新增成员
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头              */

    VOS_UINT32                          ulEstResult ;       /* 注册结果            */
    GMM_SM_CAUSE_ENUM_UINT16            enCause;            /* GMM上报的失败原因值 */
    VOS_UINT8                           aucRsv[2];          /* 四字节对齐          */
} GMMSM_ESTABLISH_CNF_STRU;

/* 原语GMMSM_STATUS_IND的结构体 */
/* ulGmmStatus 取值 */
#define  GMM_SM_STATUS_DETACHED              0                                           /* GMM状态为detached                        */
#define  GMM_SM_STATUS_ATTACHED              1                                           /* GMM状态为attached                        */
/* GMM状态为attached,但收到了网络返回的SERVICE_REJ_MSG,并且
    Reject cause = "No PDP context activated"*/
#define  GMM_SM_SER_REJ_CAUSE_PDP_NOEXIT     2

/*****************************************************************************
 枚举名    : GMM_SM_STATUS_IND_CAUSE_ENUM
 结构说明  :
 1.日    期   : 2012年7月27日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
enum GMM_SM_STATUS_IND_CAUSE_ENUM
{
    GMM_SM_STATUS_IND_CAUSE_LTE_MO_DETACH,       /* LTE mo detach */
    GMM_SM_STATUS_IND_CAUSE_BUTT
};
typedef VOS_UINT8 GMM_SM_STATUS_IND_CAUSE_ENUM_UINT32;

/*****************************************************************************
 结构名  : GMMSM_STATUS_IND_STRU
 结构说明: GMMSM_STATUS_IND原语结构

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 新增成员
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头                                   */

    VOS_UINT32                          ulGmmStatus;        /* GMM状态 0 : detached; 1 : attached       */
    GMM_SM_CAUSE_ENUM_UINT16            enCause;            /* GMM上报的失败原因 */
    VOS_UINT8                           aucRsv[2];          /* 四字节对齐 */
} GMMSM_STATUS_IND_STRU;

/*****************************************************************************
 结构名  : GMMSM_PDP_STATUS_IND_STRU
 结构说明: GMMSM_PDP_STATUS_IND原语结构

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 新增成员
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头                                   */

    /*ulPdpContextStatus取值:高16位无效，低16位取值如下*/
    /*  7            6            5            4           3           2           1           0           bit                 */
    /*  NSAPI(12)    NSAPI(11)    NSAPI(10)    NSAPI(9)    NSAPI(8)    NSAPI(7)    NSAPI(6)    NSAPI(5)    octet 1             */
    /*  NSAPI(22)    NSAPI(19)    NSAPI(18)    NSAPI(17)   NSAPI(16)   NSAPI(15)   NSAPI(14)   NSAPI(13)   octet 2             */

    VOS_UINT8                           aucPdpContextStatus[GMMSM_MAX_NSAPI_NUM];  /* PDP context状态                          */
    VOS_UINT8                           aucRsv1[1];
    GMM_SM_CAUSE_ENUM_UINT16            enCause ;           /* GMM上报原因值 */
    VOS_UINT8                           aucRsv2[2];
} GMMSM_PDP_STATUS_IND_STRU;

/* 原语GMMSM_DATA_REQ的结构体 */
/* ulEstCause 取值 */
#define   GMM_SM_RRC_EST_CAUSE_ORG_ST_CALL      0                               /* Originating Subscribed traffic Call      */
#define   GMM_SM_RRC_EST_CAUSE_ORG_CONV_CALL    1                               /* Originating Conversational Call          */
#define   GMM_SM_RRC_EST_CAUSE_ORG_STM_CALL     2                               /* Originating Streaming Call               */
#define   GMM_SM_RRC_EST_CAUSE_ORG_INTER_CALL   3                               /* Originating Interactive Call             */
#define   GMM_SM_RRC_EST_CAUSE_ORG_BG_CALL      4                               /* Originating Background Call              */
#define   GMM_SM_RRC_EST_CAUSE_ORG_HP_SIGNAL    5                               /* Originating High Priority Signalling     */

#define   GMM_PDP_ACT_ERR_CODE_NULL             (0)                             /* 错误码为空 */


typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */
    VOS_UINT32              ulEstCause;                                         /* RRC Connection Setup原因                 */
    NAS_MSG_STRU            SmMsg;                                              /* SM MSG                                   */
}GMMSM_DATA_REQ_STRU;

/* 原语GMMSM_DATA_IND的结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */
    NAS_MSG_STRU            SmMsg;                                              /* SM MSG                                   */
}GMMSM_DATA_IND_STRU;

/*****************************************************************************
 结构名  : GMMSM_SERVICE_REJ_STRU
 结构说明: GMMSM_SERVICE_REJ原语结构

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 新增成员
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头 */

    GMM_SM_CAUSE_ENUM_UINT16            enCause ;           /* GMM上报原因值 */
    VOS_UINT8                           aucRsv[2];         /* 四字节对齐 */
} GMMSM_SERVICE_REJ_STRU;


/* 原语GMMSM_SYS_INFO_IND的结构体 */
enum
{
    GMMSM_SGSN_RELEASE98_OR_OLDER        = 0,
    GMMSM_SGSN_RELEASE99_ONWARDS         = 1,
    GMMSM_SGSN_REL_VER_BUTT
};
typedef VOS_UINT8   GMMSM_SGSN_REL_VER_ENUM;

typedef struct
{
    MSG_HEADER_STRU             MsgHeader;                  /* 消息头 */
    GMMSM_SGSN_REL_VER_ENUM     ucSgsnRelVer;               /* SGSN版本信息 */
    VOS_UINT8                   aucRsv[3];                  /* 字节对齐 */
}GMMSM_SYS_INFO_IND_STRU;

/* 在GMM某些流程中收到PDP激活请求，会将消息缓存，等待流程完成后发送激活请求，但可能出现消息发送
   出去后，网络侧不回应并释放链接的情况，导致T3380定时器30秒超时后才重发PDP激活请求，用户体验不佳*/
typedef struct
{
    MSG_HEADER_STRU             MsgHeader;                  /* 消息头 */
}GMMSM_REL_IND_STRU;

#define  GMM_SM_PDP_CONTEXT_NOT_EXIST        (0)
/* 原语GMMSM_PDP_DEACTIVATED_IND_STRU的结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */

    /* ulPdpContextStatus取值:高16位无效，低16位取值如下 */
    /*  8           7           6           5           4           3           2           1           bit                 */
    /*  NSAPI(7)    NSAPI(6)    NSAPI(5)    NSAPI(4)    NSAPI(3)    NSAPI(2)    NSAPI(1)    NSAPI(0)    octet 1             */
    /*  NSAPI(15)   NSAPI(14)   NSAPI(13)   NSAPI(12)   NSAPI(11)   NSAPI(10)   NSAPI(9)    NSAPI(8)    octet 2             */
    VOS_UINT32              ulPdpContextStatus;                                 /* PDP context状态                          */
}GMMSM_PDP_DEACTIVATED_IND_STRU;

/*****************************************************************************
 结构名    : GMMSM_PDP_MODIFY_IND_STRU
 结构说明  : 指定NSAPI对应的PDP上下文修改信息
 1.日    期   : 2012年2月27日
   作    者   : z00161729
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU         stMsgHeader;                                        /* 消息头 */
    VOS_UINT8               ucNsapi;                                            /* 指定的NSAPI */
    VOS_UINT8               aucReserved[3];
}GMMSM_PDP_MODIFY_IND_STRU;



/*****************************************************************************
 结构名    : GMMSM_SIG_CONN_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 信令连接建立成功指示
  1.日    期   : 2012年8月1日
    作    者   : A00165503
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头 */
}GMMSM_SIG_CONN_IND_STRU;

/*****************************************************************************
 枚举名    : GMMSM_SESSION_TYPE_ENUM_UINT8
 枚举说明  : PS域信令流程的SESSION类型
 1.日    期   : 2014年5月28日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
enum GMMSM_SESSION_TYPE_ENUM
{
    GMMSM_SESSION_TYPE_CONVERSAT_CALL,
    GMMSM_SESSION_TYPE_STREAM_CALL,
    GMMSM_SESSION_TYPE_INTERACT_CALL,
    GMMSM_SESSION_TYPE_BACKGROUND_CALL,
    GMMSM_SESSION_TYPE_SUBSCRIB_TRAFFIC_CALL,
    GMMSM_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 GMMSM_SESSION_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名    : GMMSM_BEGIN_SESSION_NOTIFY_STRU
 结构说明  : SESSION开始指示
 1.日    期   : 2014年5月28日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    GMMSM_SESSION_TYPE_ENUM_UINT8       enSessionType;
    VOS_UINT8                           aucReserved[3];
} GMMSM_BEGIN_SESSION_NOTIFY_STRU;

/*****************************************************************************
 结构名    : GMMSM_END_SESSION_NOTIFY_STRU
 结构说明  : SESSION结束指示
 1.日    期   : 2014年5月28日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    GMMSM_SESSION_TYPE_ENUM_UINT8       enSessionType;
    VOS_UINT8                           aucReserved[3];
} GMMSM_END_SESSION_NOTIFY_STRU;


/*****************************************************************************
 枚举名    : GMMSM_DATA_REQ_MSGTYPE_ENUM_UINT32
 协议表格  :
 枚举说明  : SM和GMM通过GMMSM_DATA_REQ交互时具体的消息类型
*****************************************************************************/
enum GMMSM_DATA_REQ_MSGTYPE_ENUM
{
    SM_ACT_PDP_CONTEXT_REQ              = 0x41,
    SM_ACT_PDP_CONTEXT_ACC              = 0x42,
    SM_ACT_PDP_CONTEXT_REJ              = 0x43,
    SM_REQ_PDP_CONTEXT_ACT              = 0x44,
    SM_REQ_PDP_CONTEXT_REJ              = 0x45,
    SM_DEACT_PDP_CONTEXT_REQ            = 0x46,
    SM_DEACT_PDP_CONTEXT_ACC            = 0x47,
    SM_MOD_PDP_CONTEXT_REQ_N2M          = 0x48,
    SM_MOD_PDP_CONTEXT_ACC_M2N          = 0x49,                                 /* Modify PDP context accept (MS to network direction) */
    SM_MOD_PDP_CONTEXT_REQ_M2N          = 0x4A,                                 /* Modify PDP context request(MS to network direction)  */
    SM_MOD_PDP_CONTEXT_ACC_N2M          = 0x4B,                                 /* Modify PDP context accept (Network to MS direction) */
    SM_MOD_PDP_CONTEXT_REJ              = 0x4C,                                 /* Modify PDP context reject  */
    SM_ACT_SEC_PDP_CONTEXT_REQ          = 0x4D,                                 /* Activate secondary PDP context request   */
    SM_ACT_SEC_PDP_CONTEXT_ACC          = 0x4E,                                 /* Activate secondary PDP context accept    */
    SM_ACT_SEC_PDP_CONTEXT_REJ          = 0x4F,                                 /* SM_Activate secondary PDP context reject */
    SM_STATUS                           = 0x55,                                 /* SM_stasus */
    SM_DATA_REQ_MSGTYPE_BUTT
};
typedef VOS_UINT32 GMMSM_DATA_REQ_MSGTYPE_ENUM_UINT32;


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif
