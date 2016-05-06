/********************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : SmsGmmInterface.h
  Description : SMS与GMM接口头文件
  History     :
      1.  张志勇   2004.02.24   新版作成
*******************************************************************************/
#ifndef _SMS_GMM_INTERFACE_H_
#define _SMS_GMM_INTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */


#pragma pack(4)

/* SMS发给GMM的消息                         */
#define PMMSMS_EST_REQ                                      1
#define PMMSMS_UNITDATA_REQ                                 5
#define PMMSMS_REL_REQ                                      7

#define GMMSMS_BEGIN_SESSION_NOTIFY                         (9)

/* SMS接收GMM的原语                         */
#define GMMSMS_REG_STATE_IND                                0
#define PMMSMS_EST_CNF                                      2
#define PMMSMS_UNITDATA_IND                                 4
#define PMMSMS_ERROR_IND                                    6
#define GMMSMS_SERVICE_STATUS_IND                           8

#define GMMSMS_END_SESSION_NOTIFY                           (10)

/* GMM错误原因 */
#define    GMM_SMS_SIGN_NO_EXIST          201
#define    GMM_SMS_SPEC_PROC_ONGOING      202

/* 原语GMMSMS_REG_STATE_IND的结构体         */
typedef struct
{
    MSG_HEADER_STRU            MsgHeader;                                       /* 消息头                                   */
#define    GMM_SMS_REG_ATTACHED       0                                         /* 已经注册                                 */
#define    GMM_SMS_REG_DETTACHED      1                                         /* 没有注册                                 */
    VOS_UINT32                      ulRegSts;                                        /* 注册状态                                 */
}GMMSMS_REG_STATE_IND_STRU;


/* 原语PMMSMS_EST_REQ的结构体               */
typedef struct
{
    MSG_HEADER_STRU            MsgHeader;                                       /* 消息头                                   */
    VOS_UINT32                      ulEstCause;                                      /* RRC连接建立原因                          */
}PMMSMS_EST_REQ_STRU;

/* 原语PMMSMS_REL_REQ的结构体               */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                                          /* 消息头                                   */
}PMMSMS_REL_REQ_STRU;

/* 原语PMMSMS_EST_CNF的结构体               */
typedef struct
{
    MSG_HEADER_STRU            MsgHeader;                                       /* 消息头                                   */
}PMMSMS_EST_CNF_STRU;

/* 原语PMMSMS_UNITDATA_REQ的结构体          */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */
    NAS_MSG_STRU            SmsMsg;                                             /* SMS MSG                                  */
}PMMSMS_UNITDATA_REQ_STRU;

/* 原语PMMSMS_UNITDATA_IND的结构体          */
typedef struct
{
    MSG_HEADER_STRU     MsgHeader;                                              /* 消息头                                   */
    NAS_MSG_STRU        SmsMsg;                                                 /* SMS MSG                                  */
} PMMSMS_UNITDATA_IND_STRU;
typedef struct
{
    VOS_UINT32                          ulNasMsgSize;       
    VOS_UINT8                           aucNasMsg[256];     
}NAS_MSG_TEMP_STRU;

typedef struct
{
    MSG_HEADER_STRU     MsgHeader;                                              /* 消息头                                   */
    NAS_MSG_TEMP_STRU   SmsMsg;                                                 /* SMS MSG                                  */
} PMMSMS_UNITDATA_IND_TEMP_STRU;

/* 原语PMMSMS_ERROR_IND的结构体             */
typedef struct
{
    MSG_HEADER_STRU     MsgHeader;                                              /* 消息头                                   */
    VOS_UINT32               ulCause;                                                /* 原因值                                   */
} PMMSMS_ERROR_IND_STRU;

enum GMMSMS_SERVICE_STATUS_ENUM
{
    GMM_SMS_NO_SERVICE        = 0,
    GMM_SMS_NORMAL_SERVICE    = 1,
    GMM_SERVICE_STATUS_BUTT
};
typedef VOS_UINT32 GMMSMS_SERVICE_STATUS_ENUM_UINT32;

/* 原语GMMSMS_SERVICE_STATUS_IND的结构体         */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头                                   */
    GMMSMS_SERVICE_STATUS_ENUM_UINT32   enServiceSts;                           /* 服务状态                                 */
}GMMSMS_SERVICE_STATUS_IND_STRU;

/*****************************************************************************
 枚举名    : GMMSMS_SESSION_TYPE_ENUM_UINT8
 枚举说明  : SMS域SESSION类型
 1.日    期   : 2014年5月28日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
enum GMMSMS_SESSION_TYPE_ENUM
{
    GMMSMS_SESSION_TYPE_MO_SMS,
    GMMSMS_SESSION_TYPE_MT_SMS,
    GMMSMS_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 GMMSMS_SESSION_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名    : GMMSMS_BEGIN_SESSION_NOTIFY_STRU
 结构说明  : SESSION开始指示
 1.日    期   : 2014年5月28日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;                /*_H2ASN_Skip*/
    GMMSMS_SESSION_TYPE_ENUM_UINT8                  enSessionType;
    VOS_UINT8                                       aucReserved[3];
} GMMSMS_BEGIN_SESSION_NOTIFY_STRU;

/*****************************************************************************
 结构名    : GMMSMS_END_SESSION_NOTIFY_STRU
 结构说明  : SESSION结束指示
 1.日    期   : 2014年5月28日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;                /*_H2ASN_Skip*/
    GMMSMS_SESSION_TYPE_ENUM_UINT8                  enSessionType;
    VOS_UINT8                                       aucReserved[3];
} GMMSMS_END_SESSION_NOTIFY_STRU;


extern VOS_UINT32  NAS_SMS_IsPsDomainIdle(VOS_VOID);

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
