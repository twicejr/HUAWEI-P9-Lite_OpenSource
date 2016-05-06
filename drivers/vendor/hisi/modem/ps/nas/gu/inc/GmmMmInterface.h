/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : GmmMmInterface.h
  版 本 号   : 初稿
  作    者   : huwen /44270
  生成日期   : 2011年07月01日
  最近修改   :
  功能描述   : GMM与MM间接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年07月01日
    作    者   : huwen /40661
    修改内容   : 创建文件
  2.日    期   : 2012年01月12日
    作    者   : w00176964
    修改内容   : ASN解析统一调整头文件

******************************************************************************/
#ifndef _GMM_MM_INTERFACE_H_
#define _GMM_MM_INTERFACE_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include "TafTypeDef.h"
#include "NasCommDef.h"
#include "Nasrrcinterface.h"
#include "NasMmlCtx.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  1 全局变量定义
*****************************************************************************/

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* GMM发送给MM的消息原语 */
/* MNCC Primitives defination */
/*****************************************************************************
 枚举名    : GMM_MM_MSG_TYPE_ENUM
 枚举说明  : GMM与MM相互间的消息原语定义
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
   
 2.日    期   : 2011年8月17日                 
   作    者   : w00167002                    
   修改内容   : V7R1 PHASEII 重构: 给枚举赋值初始化，进行SDT打印显示
 3.日    期   : 2012年1月12日
   作    者   : w00176964
   修改内容   : ASN解析统一调整头文件
 4.日    期   : 2015年1月5日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
enum GMM_MM_MSG_TYPE_ENUM
{
    /* 消息名称 */                      /*消息ID*/  /* 备注 */
/* GMM发给MM的原语 */
    GMMMM_LU_INITIATION                         = 0x1000,    /* _H2ASN_MsgChoice GMMMM_LU_INITIATION_STRU */

    GMMMM_COMBINED_ATTACH_INITIATION            = 0x1001,    /* _H2ASN_MsgChoice GMMMM_COMBINED_ATTACH_INITIATION_STRU */
    GMMMM_COMBINED_ATTACH_ACCEPTED              = 0x1002,    /* _H2ASN_MsgChoice GMMMM_COMBINED_ATTACH_ACCEPTED_STRU */
    GMMMM_COMBINED_ATTACH_REJECTED              = 0x1003,    /* _H2ASN_MsgChoice GMMMM_COMBINED_ATTACH_REJECTED_STRU */
    GMMMM_IMSI_DETACH_INITIATION                = 0x1004,    /* _H2ASN_MsgChoice GMMMM_IMSI_DETACH_INITIATION_STRU */
    GMMMM_IMSI_DETACH_COMPLETED                 = 0x1005,    /* _H2ASN_MsgChoice GMMMM_IMSI_DETACH_COMPLETED_STRU */
    GMMMM_GPRS_DETACH_INITIATION                = 0x1006,    /* _H2ASN_MsgChoice GMMMM_GPRS_DETACH_INITIATION_STRU */
    GMMMM_GPRS_DETACH_COMPLETED                 = 0x1007,    /* _H2ASN_MsgChoice GMMMM_GPRS_DETACH_COMPLETED_STRU */
    GMMMM_NETWORK_DETACH_IND                    = 0x1008,    /* _H2ASN_MsgChoice GMMMM_NETWORK_DETACH_IND_STRU */
    GMMMM_GMM_ACTION_RESULT_IND                 = 0x1009,    /* _H2ASN_MsgChoice GMMMM_GMM_ACTION_RESULT_IND_STRU */
    GMMMM_COMBINED_RAU_INITIATION               = 0x100a,    /* _H2ASN_MsgChoice GMMMM_COMBINED_RAU_INITIATION_STRU */
    GMMMM_COMBINED_RAU_ACCEPTED                 = 0x100b,    /* _H2ASN_MsgChoice GMMMM_COMBINED_RAU_ACCEPTED_STRU */
    GMMMM_COMBINED_RAU_REJECTED                 = 0x100c,    /* _H2ASN_MsgChoice GMMMM_COMBINED_RAU_REJECTED_STRU */
    GMMMM_AUTHENTICATON_FAILURE_IND             = 0x100d,    /* _H2ASN_MsgChoice GMMMM_AUTHENTICATON_FAILURE_IND_STRU */

    /* MM->GMM */
    MMGMM_LU_RESULT_IND                         = 0x2000,    /* _H2ASN_MsgChoice MMGMM_LU_RESULT_IND_STRU */
    MMGMM_AUTHENTICATON_FAILURE_IND             = 0x2001,    /* _H2ASN_MsgChoice MMGMM_AUTHENTICATON_FAILURE_IND_STRU */
    MMGMM_CS_CONNECT_IND                        = 0x2002,    /* _H2ASN_MsgChoice MMGMM_CS_CONNECT_IND_STRU */
    MMGMM_CM_SERVICE_REJECT_IND                 = 0x2003,    /* _H2ASN_MsgChoice MMGMM_CM_SERVICE_REJECT_IND_STRU */
    MMGMM_REGISTER_INITIATION                   = 0x2004,    /* _H2ASN_MsgChoice MMGMM_REGISTER_INITIATION_STRU */

    MMGMM_CS_LOCAL_DETACH_IND                   = 0x2005,    /* _H2ASN_MsgChoice MMGMM_CS_LOCAL_DETACH_IND_STRU */

    MMGMM_T3211_TIMER_EXPIRED_NOTIFY            = 0x2006,    /* _H2ASN_MsgChoice MMGMM_T3211_TIMER_EXPIRED_NOTIFY_STRU */

    GMMMM_MSG_TYPE_BUTT
} ;
typedef VOS_UINT16  GMM_MM_MSG_TYPE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : GMMMM_TIMER_FLG_ENUM
 枚举说明  : GMM定时器超时的类型
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
enum GMMMM_TIMER_FLG_ENUM
{
    GMMMM_NO_TIMER_EXPIRED,                                                     /* 无定时器超时 */
    GMMMM_T3312_EXPIRED,                                                        /* T3312超时 */
    GMMMM_T3311_EXPIRED,                                                        /* T3311超时 */
    GMMMM_T3302_EXPIRED,                                                        /* T3302超时 */
    GMMMM_T3330_EXPIRED,                                                        /* T3330超时 */
    GMMMM_T3412OrT3423_EXPIRED,                                                 /* L的T3412和T3423定时器超时 */
    GMMMM_TIMER_FLG_BUTT
};
typedef VOS_UINT32  GMMMM_TIMER_FLG_ENUM_UINT32;


/*****************************************************************************
 枚举名    : GMMMM_ATTACH_RESLUT_ENUM
 枚举说明  : GMM手机侧发起ATTACH的结果类型
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
enum GMMMM_ATTACH_RESLUT_ENUM
{
    GMMMM_ATTACH_RESLUT_PS_ONLY,                                                /* 只有PS域ATTACH成功 */
    GMMMM_ATTACH_RESLUT_COMBINED,                                               /* 只有COMBINED ATTACH成功 */
    GMMMM_ATTACH_RESLUT_BUTT
};
typedef VOS_UINT32  GMMMM_ATTACH_RESLUT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : GMMMM_DETACH_RESLUT_ENUM
 枚举说明  : GMM手机侧发起DETACH类型
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
enum GMMMM_DETACH_TYPE_ENUM
{
    GMMMM_COMBINED_DETACH_NORMAL,                                               /* 只有COMBINED ATTACH成功 */
    GMMMM_GPRS_DETACH_NORMAL,                                                   /* 只有PS域DETACH成功 */
    GMMMM_DETACH_RESLUT_BUTT
};
typedef VOS_UINT32  GMMMM_DETACH_TYPE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : GMMMM_NET_DETACH_RESLUT_ENUM
 枚举说明  : 网络侧发起DETACH的结果类型
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
enum GMMMM_NET_DETACH_TYPE_ENUM
{
    GMMMM_NET_DETACH_IMSI,                                                      /* 网络发起IMSI DETACH */
    GMMMM_NET_DETACH_NOATTACH,                                                  /* 网络发起 DETACH后MS不再ATTACH */
    GMMMM_NET_DETACH_REATTACH,                                                  /* 网络发起 DETACH后MS再ATTACH */
    GMMMM_NET_DETACH_RESLUT_BUTT
};
typedef VOS_UINT32  GMMMM_NET_DETACH_TYPE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : GMMMM_ACTION_TYPE_ENUM
 枚举说明  : GMM的ACTION类型
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
enum GMMMM_ACTION_TYPE_ENUM
{
    GMMMM_ACTION_RAU,                                                           /* 当前发起RAU */
    GMMMM_ACTION_ATTACH,                                                        /* 当前发起ATTACH */
    GMMMM_ACTION_SR,                                                            /* 当前发起SERVICE REQUEST */
    GMMMM_ACTION_TYPE_BUTT
};
typedef VOS_UINT32  GMMMM_ACTION_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : GMMMM_ACTION_TYPE_ENUM
 枚举说明  : GMM的ACTION结果
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
enum GMMMM_ACTION_RESULT_ENUM
{
    GMMMM_ACTION_SUCCESS,
    GMMMM_ACTION_FAILURE,
    GMMMM_ACTION_RESULT_BUTT
};
typedef VOS_UINT32  GMMMM_ACTION_RESULT_ENUM_UINT32;


/*****************************************************************************
 枚举名    : GMMMM_REAL_FLAG_ENUM
 枚举说明  : 用来标记是否为真实消息
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
enum GMMMM_REAL_FLAG_ENUM
{
    GMMMM_REAL_PROCEDURE,                                                       /* 表示真消息,MM需要更新TMSI */
    GMMMM_UNREAL_PROCEDURE,                                                     /* 表示假消息,MM不能更新TMSI */
    GMMMM_PROCEDURE_BUTT
};
typedef VOS_UINT32 GMMMM_REAL_FLAG_ENUM_UINT32;

/*****************************************************************************
 枚举名    : GMMMM_RAU_RESULT_ENUM
 枚举说明  : GMM RAU的结果
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
enum GMMMM_RAU_RESULT_ENUM
{
    GMMMM_RAU_RESULT_PS_ONLY,                                                   /* 只有PS域RAU成功 */
    GMMMM_RAU_RESULT_COMBINED,                                                  /* Combined RAU成功 */
    GMMMM_RAU_RESULT_BUTT
};
typedef VOS_UINT32 GMMMM_RAU_RESULT_ENUM_UINT32;


/*****************************************************************************
 枚举名    : GMMMM_MS_ID_TYPE_ENUM
 枚举说明  : MS ID的类型
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
enum GMMMM_MS_ID_TYPE_ENUM
{
    GMMMM_MS_ID_TYPE_NULL,
    GMMMM_MS_ID_TYPE_IMSI,                                                      /* IMSI */
    GMMMM_MS_ID_TYPE_TMSI,                                                      /* TMSI */
    GMMMM_MS_ID_TYPE_BUTT
};
typedef VOS_UINT32 GMMMM_MS_ID_TYPE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : MMGMM_LU_RESULT_ENUM
 枚举说明  : MM LU结果
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
enum MMGMM_LU_RESULT_ENUM
{
    MMGMM_LU_SUCCESS,                                                           /* LU SUCCESS */
    MMGMM_LU_FAILURE,                                                           /* LU FAILURE */
    MMGMM_LU_RESULT_BUTT
};
typedef VOS_UINT32 MMGMM_LU_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MMGMM_CS_CONNECT_STATUS_ENUM
 枚举说明  : MM LU结果
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
enum MMGMM_CS_CONNECT_STATUS_ENUM
{
    MMGMM_CS_CONNECT_NOT_EXIST,                                                 /* 没有CS域业务 */
    MMGMM_CS_CONNECT_ESTING,                                                    /* 有CS域业务 */
    MMGMM_CS_CONNECT_EXIST,                                                     /* 有CS域业务 */
    MMGMM_CS_CONNECT_BUTT
};
typedef VOS_UINT32 MMGMM_CS_CONNECT_STATUS_ENUM_UINT32;

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
 结构名    : GMMMM_LU_INITIATION_STRU
 结构说明  : GMM通知MM LU发起
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头 */ /*_H2ASN_Skip*/
    GMMMM_TIMER_FLG_ENUM_UINT32         enTimerExpiredFlg;                      /* timer超时标记 */
}GMMMM_LU_INITIATION_STRU;


/*****************************************************************************
 结构名    : GMMMM_COMBINED_ATTACH_INITIATION_STRU
 结构说明  : GMM通知MM COMBINED ATTACH开始
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头 */ /*_H2ASN_Skip*/
}GMMMM_COMBINED_ATTACH_INITIATION_STRU;

/*****************************************************************************
 结构名    : GMMMM_MS_IDENTITY_STRU
 结构说明  : MS ID的结构体类型
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    GMMMM_MS_ID_TYPE_ENUM_UINT32        enMsIdType;                             /* Ms类型 */
    VOS_UINT8                           aucTmsi[4];                             /* TMSI */
}GMMMM_MS_IDENTITY_STRU;


/*****************************************************************************
 结构名    : GMMMM_COMBINED_ATTACH_ACCEPTED_STRU
 结构说明  : GMM通知MM COMBINED ATTACH ACCEPT
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
 2.日    期   : 2012年8月21日
   作    者   : l00171473
   修改内容   : DTS2012081705828, 4字节对齐
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头 */ /*_H2ASN_Skip*/

    GMMMM_ATTACH_RESLUT_ENUM_UINT32     enAttachResult;                         /* 注册结果 */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;                                /* 注册失败原因 */
    VOS_UINT8                           aucReserve[2];
    GMMMM_MS_IDENTITY_STRU              stMsIdentity;                           /* MS ID */
    VOS_UINT32                          ulAttachAttCounter;                     /* Attach attempt counter */
}GMMMM_COMBINED_ATTACH_ACCEPTED_STRU;

/*****************************************************************************
 结构名    : GMMMM_COMBINED_ATTACH_REJECTED_STRU
 结构说明  : GMM通知MM COMBINED ATTACH REJECTED
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头 */ /*_H2ASN_Skip*/
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;                                /* 注册失败原因 */
    VOS_UINT8                           aucReserve[2];                          /* 保留位 */
    VOS_UINT32                          ulAttachAttCounter;                     /* Attach attempt counter */
}GMMMM_COMBINED_ATTACH_REJECTED_STRU;

/*****************************************************************************
 结构名    : GMMMM_IMSI_DETACH_INITIATION_STRU
 结构说明  : GMM通知MM 发起IMSI DETACH
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulReserved;                     /* 保留*/
}GMMMM_IMSI_DETACH_INITIATION_STRU;

/*****************************************************************************
 结构名    : GMMMM_IMSI_DETACH_COMPLETED_STRU
 结构说明  : GMM通知MM IMSI DETACH完成
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulReserved;                     /* 保留*/
}GMMMM_IMSI_DETACH_COMPLETED_STRU;

/*****************************************************************************
 结构名    : GMMMM_GPRS_DETACH_INITIATION_STRU
 结构说明  : GMM通知MM GPRS DETACH发起
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头 */ /*_H2ASN_Skip*/
    GMMMM_DETACH_TYPE_ENUM_UINT32       enDetachType;                           /* DETACH的类型 */
}GMMMM_GPRS_DETACH_INITIATION_STRU;

/*****************************************************************************
 结构名    : GMMMM_GPRS_DETACH_COMPLETED_STRU
 结构说明  : GMM通知MM GPRS DETACH完成
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulReserved;                     /* 保留*/
}GMMMM_GPRS_DETACH_COMPLETED_STRU;


/*****************************************************************************
 结构名    : GMMMM_NETWORK_DETACH_IND_STRU
 结构说明  : GMM通知MM 网络发起DETACH
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头 */ /*_H2ASN_Skip*/
    GMMMM_NET_DETACH_TYPE_ENUM_UINT32   enDetachType;                           /* Detach类型 */
    VOS_UINT32                          ulDetachCause;                          /* Detach原因 */
}GMMMM_NETWORK_DETACH_IND_STRU;

/*****************************************************************************
 结构名    : GMMMM_GMM_ACTION_RESULT_IND_STRU
 结构说明  : GMM通知MM ACTION RESULT
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头 */ /*_H2ASN_Skip*/
    GMMMM_ACTION_TYPE_ENUM_UINT32       enGmmActionType;                        /* GMM进行操作的类型 */
    GMMMM_ACTION_RESULT_ENUM_UINT32     enActionResult;                         /* 操作结果 */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;                                /* 操作失败原因 */
    VOS_UINT8                           ucAttCounter;                           /* attempt counter */    
    VOS_UINT8                           aucReserve[1];                          /* 保留位 */    
}GMMMM_GMM_ACTION_RESULT_IND_STRU;

/*****************************************************************************
 结构名    : GMMMM_COMBINED_RAU_INITIATION_STRU
 结构说明  : GMM通知MM COMBINED RAU发起
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulReserved;                             /* 保留*/
}GMMMM_COMBINED_RAU_INITIATION_STRU;


/*****************************************************************************
 结构名    : GMMMM_COMBINED_RAU_ACCEPTED_STRU
 结构说明  : GMM通知MM COMBINED RAU完成
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                              /* 消息头 */ /*_H2ASN_Skip*/
    GMMMM_RAU_RESULT_ENUM_UINT32        enRauResult;                            /* 更新结果 */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;                                /* 操作失败原因 */
    VOS_UINT8                           aucReserve[2];                          /* 保留位 */
    GMMMM_MS_IDENTITY_STRU              stMsIdentity;                           /* MS identity */
    VOS_UINT32                          ulRauAttCounter;                        /* RAU attempt counter */
    GMMMM_REAL_FLAG_ENUM_UINT32         enRealProFlg;                           /* 真假流程标识 */
}GMMMM_COMBINED_RAU_ACCEPTED_STRU;


/*****************************************************************************
 结构名    : GMMMM_COMBINED_RAU_ACCEPTED_STRU
 结构说明  : GMM通知MM COMBINED RAU被拒
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头 */ /*_H2ASN_Skip*/
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;                                /* 操作失败原因 */
    VOS_UINT8                           aucReserve[2];                          /* 保留位 */
    VOS_UINT32                          ulRauAttCounter;                        /* RAU attempt counter */
    GMMMM_REAL_FLAG_ENUM_UINT32         enRealProFlg;                           /* 是否真正发起流程标志 */
}GMMMM_COMBINED_RAU_REJECTED_STRU;


/*****************************************************************************
 结构名    : GMMMM_AUTHENTICATON_FAILURE_IND_STRU
 结构说明  : GMM通知MM鉴权被拒
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
     MSG_HEADER_STRU                    stMsgHeader;                            /* 消息头 */ /*_H2ASN_Skip*/
     VOS_UINT32                         ulReserved;                     /* 保留*/
}GMMMM_AUTHENTICATON_FAILURE_IND_STRU;


/*****************************************************************************
 结构名    : MMGMM_LU_RESULT_IND_STRU
 结构说明  : MM通知GMM LU结果
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头 */ /*_H2ASN_Skip*/

    MMGMM_LU_RESULT_ENUM_UINT32         enLuResult;                             /* LU结果 */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;                                /* 操作失败原因 */
    VOS_UINT8                           aucReserve[2];                          /* 保留位 */
}MMGMM_LU_RESULT_IND_STRU;

/*****************************************************************************
 结构名    : MMGMM_AUTHENTICATON_FAILURE_IND_STRU
 结构说明  : MM通知GMM 鉴权失败
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                              /* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulReserved;                     /* 保留*/
}MMGMM_AUTHENTICATON_FAILURE_IND_STRU;


/*****************************************************************************
 结构名    : MMGMM_CS_CONNECT_IND_STRU
 结构说明  : MM通知GMM 当前CS连接状态
 1.日    期   : 2011年7月16日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{

    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头 */ /*_H2ASN_Skip*/
    MMGMM_CS_CONNECT_STATUS_ENUM_UINT32 enCsConnectStatus;                      /* CS域连接有无标志  */
}MMGMM_CS_CONNECT_IND_STRU;

/*****************************************************************************
 结构名    : MMGMM_CM_SERVICE_REJECT_IND_STRU
 结构说明  : MM通知GMM 当前CS域业务被拒绝
 1.日    期   : 2011年7月16日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{

    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头 */ /*_H2ASN_Skip*/
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;                                /* 失败原因 */
}MMGMM_CM_SERVICE_REJECT_IND_STRU;


/*****************************************************************************
 结构名    : MMGMM_REGISTER_INITIATION_STRU
 结构说明  : MM通知GMM 当前CS域发起注册
 1.日    期   : 2011年8月10日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{

    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                     /* 保留*/
} MMGMM_REGISTER_INITIATION_STRU;

/*****************************************************************************
 结构名    : MMGMM_CS_LOCAL_DETACH_IND_STRU
 结构说明  : MM通知GMM 当前CS域本地去注册了
 1.日    期   : 2013年6月12日
   作    者   : w00167002
   修改内容   : 新建
*****************************************************************************/
typedef struct
{

    MSG_HEADER_STRU         stMsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                     /* 保留*/
} MMGMM_CS_LOCAL_DETACH_IND_STRU;


/*****************************************************************************
 结构名    : MMGMM_T3211_TIMER_EXPIRED_NOTIFY_STRU
 结构说明  : MM通知GMM T3211定时器超时
 1.日    期   : 2015年1月5日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
typedef struct
{

    MSG_HEADER_STRU         stMsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT8               ucRejectCause;                      /* 记录启动T3211时mm lau被拒的原因值 */
    VOS_UINT8               aucReserved[3];                     /* 保留*/
} MMGMM_T3211_TIMER_EXPIRED_NOTIFY_STRU;


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
    GMM_MM_MSG_TYPE_ENUM_UINT16         enMsgID;    /*_H2ASN_MsgChoice_Export GMM_MM_MSG_TYPE_ENUM_UINT16*/
                                                    /* 为了兼容NAS的消息头定义，所以转换ASN.1使用GMM_MM_MSG_TYPE_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          GMM_MM_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}GMM_MM_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    GMM_MM_MSG_DATA                    stMsgData;
}GmmMmInterface_MSG;



/*****************************************************************************
  10 函数声明
*****************************************************************************/


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

#endif /* end of GmmMmInterface.h */

