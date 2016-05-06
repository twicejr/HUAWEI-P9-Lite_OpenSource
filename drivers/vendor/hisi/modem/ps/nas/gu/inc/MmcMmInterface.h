/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : MmcMmInterface.h
  Description : MMC与MM接口头文件
  History     :
      1.  张志勇   2003.11.26   新版作成

      2.日    期   : 2006年3月28日
        作    者   : liuyang id:48197
        修改内容   : 问题单号：A32D02606
      3.  s46746   2006-03-39   根据问题单A32D02486修改

      4.日    期   : 2006年5月4日
        作    者   : liuyang id:48197
        修改内容   : 问题单号:A32D03487
      5.日    期  : 2006年12月4日
        作    者  : luojian id:60022475
        修改内容  : 增加 #pragma pack(4)，问题单号:A32D07779
      6.日    期  : 2007年9月21日
        作    者  : luojian id:107747
        修改内容  : 问题单号：AT2D01703,MMCMM_COMBINED_RAU_ACCEPTED消息增加
                    RealFlag标志
      7.日    期  : 2007年10月06日
        作    者  : l65478
        修改内容  : 问题单号：A32D12977
      8.日    期   : 2009年01月15日
        作    者   : l00130025
        修改内容   : 问题单号:AT2D07018,LAU或RAU过程中搜网和SYSCFG设置,发起底层释放链接的操作
      9.日    期   : 2012年01月11日
        作    者   : w00176964
        修改内容   : asn 解析统一调整接口头文件
     10.日    期   : 2012年02月02日
        作    者   : w00176964
        修改内容   : V7R1 PhaseIV 合入
*******************************************************************************/
#ifndef _MMC_MM_INTERFACE_H_
#define _MMC_MM_INTERFACE_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "TafTypeDef.h"
#include "PsTypeDef.h"
#include "NasCommDef.h"
#include "Nasrrcinterface.h"
#include "NasMmlCtx.h"
#include "NasMmcCtx.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */
#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define     MMCMM_NAS_MAX_SIZE_NAS_GSM_MAP          RRC_NAS_MAX_SIZE_NAS_GSM_MAP                                  /* 协议值 : 8                               */
#define     NAS_MAX_EQUPLMN_NUM                     (15)

/* 消息MMCMM_SERVICE_STATUS_IND的结构体 */
/* ulServiceStatus */
#define     MMC_MM_NORMAL_SERVICE                   NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE
#define     MMC_MM_LIMITED_SERVICE                  NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE
#define     MMC_MM_LIMITED_SERVICE_REGION           NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE_REGION
#define     MMC_MM_NO_IMSI                          NAS_MSCC_PIF_SERVICE_STATUS_NO_IMSI
#define     MMC_MM_NO_SERVICE                       NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE

/* A32D12977==> */
/* 消息MMCMM_CM_SERVICE_IND的结构体 */
/* ulEmcFlg */
#define     MM_EMERGENCY_CALL_TRUE                  1
#define     MM_EMERGENCY_CALL_FALSE                 0

/* ulCsServFlg */
#define     MM_CS_SERV_NOT_EXIST                    0                            /* 没有CS域业务                             */
#define     MM_CS_SERV_EXIST                        1                            /* 有CS域业务                               */

#define     MMC_MM_RR_CONN_ABSENT                   0
#define     MMC_MM_RR_CONN_ESTING                   1
#define     MMC_MM_RR_CONN_ESTED                    2

/* ulForbiddenFlg 取值 */
#define     MMCMM_NO_FORBIDDEN                      0x00000000
#define     MMCMM_FORBIDDEN_PLMN                    0x00000001
#define     MMCMM_FORBIDDEN_PLMN_FOR_GPRS           0x00000002
#define     MMCMM_FORBIDDEN_LA_FOR_ROAM             0x00000004
#define     MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS     0x00000008

/* usMsgType 取值 */
#define     MMC_RECEIVE_ATTACH_REQ                  0                           /* 已经接收到MMCMM_ATTACH_REQ   */
#define     MMC_RECEIVE_SYS_INFO                    1                           /* 已经接收到MMCMM_SYS_INFO_IND */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : MMC_MM_MSG_TYPE_ENUM
 结构说明  : MMC和MM之间的原语ulMsgName
 1.日    期   : 2012年1月11日
   作    者   : w00176964
   修改内容   : ASN解析统一调整
*****************************************************************************/
enum MMC_MM_MSG_TYPE_ENUM
{
    /* 消息名称 */                      /*消息ID*/  /* 备注 */
/* MMC发给MM的原语 */
    MMCMM_SYS_INFO_IND                  = 0,   /* _H2ASN_MsgChoice MMCMM_SYS_INFO_IND_STRU */
    MMCMM_COVERAGE_LOST_IND             = 2,   /* _H2ASN_MsgChoice MMCMM_COVERAGE_LOST_IND_STRU */
    MMCMM_PLMN_SEARCH_INITIATED         = 4,   /* _H2ASN_MsgChoice MMCMM_PLMN_SEARCH_INITIATED_STRU */
    MMCMM_START_REQ                     = 6,   /* _H2ASN_MsgChoice MMCMM_START_REQ_STRU */
    MMCMM_DETACH_REQ                    = 8,   /* _H2ASN_MsgChoice MMCMM_DETACH_REQ_STRU */
    MMCMM_POWER_OFF_REQ                 = 10,  /* _H2ASN_MsgChoice MMCMM_POWER_OFF_REQ_STRU */
    /* MMCMM_PLMN_USER_SEL_REQ不再使用，删除 */
    MMCMM_ATTACH_REQ                    = 14,  /* _H2ASN_MsgChoice MMCMM_ATTACH_REQ_STRU */
    MMCMM_MODE_CHANGE_REQ               = 16,  /* _H2ASN_MsgChoice MMCMM_MODE_CHANGE_REQ_STRU */
    MMCMM_SUSPEND_IND                   = 18,  /* _H2ASN_MsgChoice MMCMM_SUSPEND_IND_STRU */
    MMCMM_RESUME_IND                    = 20,  /* _H2ASN_MsgChoice MMCMM_RESUME_IND_STRU */
    MMCMM_GSM_SYS_INFO_IND              = 22,  /* _H2ASN_MsgChoice MMCMM_GSM_SYS_INFO_IND_ST */
    MMCMM_REL_REQ                       = 24,  /* _H2ASN_MsgChoice MMCMM_REL_REQ_STRU */
    /* MMC发给MM LMM的注册结果 */
    MMCMM_LMM_ATTACH_IND                = 26,  /* _H2ASN_MsgChoice MMCMM_LMM_ATTACH_IND_STRU */
    MMCMM_LMM_TAU_RESULT_IND            = 28,  /* _H2ASN_MsgChoice MMCMM_LMM_TAU_RESULT_IND_STRU */
    MMCMM_LMM_MT_DETACH_IND             = 30,  /* _H2ASN_MsgChoice MMCMM_LMM_MT_DETACH_IND_STRU */
    MMCMM_LMM_SERVICE_RESULT_IND        = 32,  /* _H2ASN_MsgChoice MMCMM_LMM_SERVICE_RESULT_IND_STRU */

    MMCMM_LTE_SYS_INFO_IND              = 34,   /* _H2ASN_MsgChoice MMC_MM_LTE_SYS_INFO_IND_STRU */

    MMCMM_LMM_MO_DETACH_IND             = 36,  /* _H2ASN_MsgChoice MMCMM_LMM_MO_DETACH_IND_STRU */
    MMCMM_LMM_LOCAL_DETACH_IND          = 38,  /* _H2ASN_MsgChoice MMCMM_LMM_LOCAL_DETACH_IND_STRU */

    MMCMM_W_AC_INFO_CHANGE_IND          = 40,   /* _H2ASN_MsgChoice MMMMC_CS_REG_RESULT_IND_STRU */

    MMCMM_LMM_TIMER_STATE_NOTIFY        = 42,

    MMCMM_SRVCC_INFO_NOTIFY             = 44,   /* _H2ASN_MsgChoice MMCMM_SRVCC_INFO_NOTIFY_STRU */

    MMCMM_RAT_CHANGE_IND                = 46,   /* _H2ASN_MsgChoice MMCMM_RAT_CHANGE_IND_STRU */

    MMCMM_LAU_REQ                       = 48,   /* _H2ASN_MsgChoice MMCMM_LAU_REQ_STRU */


/* MM发给MMC的原语 */
    MMCMM_CM_SERVICE_IND                = 1,   /* _H2ASN_MsgChoice MMCMM_CM_SERVICE_IND_STRU */
    MMCMM_CM_SERVICE_REJECT_IND         = 3,   /* _H2ASN_MsgChoice MMCMM_CM_SERVICE_REJECT_IND_STRU */
    MMCMM_START_CNF                     = 5,   /* _H2ASN_MsgChoice MMCMM_START_CNF_STRU */
    MMCMM_DETACH_CNF                    = 7,   /* _H2ASN_MsgChoice MMCMM_DETACH_CNF_STRU */
    MMCMM_POWER_OFF_CNF                 = 9,   /* _H2ASN_MsgChoice MMCMM_POWER_OFF_CNF_STRU */
    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-15, begin */

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-15, end */
    MMCMM_RR_CONN_INFO_IND              = 13,  /* _H2ASN_MsgChoice MMCMM_RR_CONN_INFO_IND_STRU */
    MMCMM_RESUME_RSP                    = 15,  /* _H2ASN_MsgChoice MMCMM_RESUME_RSP_STRU */
    MMCMM_REGISTER_STATE_CHANGE_IND     = 17,  /* _H2ASN_MsgChoice MMCMM_REGISTER_STATE_CHANGE_IND_ST */
    MMCMM_INFO_IND                      = 19,  /* _H2ASN_MsgChoice MMCMM_INFO_IND_STRU */
    MMCMM_RR_REL_IND                    = 21,  /* _H2ASN_MsgChoice MMCMM_RR_REL_IND_ST */
    MMCMM_SUSPEND_RSP                   = 23,  /* _H2ASN_MsgChoice MMCMM_SUSPEND_RSP_ST */
    MMCMM_DEREGISTER_INITIATION         = 25,  /* _H2ASN_MsgChoice MMCMM_DEREGISTER_INITIATION_STRU */
    MMMMC_CS_REG_RESULT_IND             = 27,   /* _H2ASN_MsgChoice MMMMC_CS_REG_RESULT_IND_STRU */
    MMCMM_ATTACH_CNF                    = 29,   /* _H2ASN_MsgChoice MMCMM_ATTACH_CNF_STRU */
    MMMMC_ABORT_IND                     = 31,   /* _H2ASN_MsgChoice MMMMC_ABORT_IND_STRU */
    MMCMM_SIM_AUTH_FAIL_IND             = 33,   /* _H2ASN_MsgChoice MMCMM_SIM_AUTH_FAIL_IND_STRU */
    MMCMM_PLMN_SEARCH_IND               = 35,
    MMCMM_CSFB_ABORT_IND                = 36,

    MMCMM_MSG_TYPE_BUTT
};
typedef VOS_UINT16 MMC_MM_MSG_TYPE_ENUM_UINT16;

enum MM_MMC_PLMN_SEARCH_TYPE_ENUM
{
    MM_MMC_PLMN_SEARCH_TYPE_NORMAL          = 0,
    MM_MMC_PLMN_SEARCH_TYPE_EMERGENCY       = 1,
    MM_MMC_PLMN_SEARCH_TYPE_CSFB_BACK_LTE   = 2,

    MM_MMC_PLMN_SEARCH_TYPE_CSFB_END        = 3,

    MM_MMC_PLMN_SEARCH_TYPE_BUTT
};
typedef VOS_UINT32 MM_MMC_PLMN_SEARCH_TYPE_ENUM_U32;

/*****************************************************************************
 枚举名    : MM_MMC_LU_RESULT_ENUM
 结构说明  : MMMMC_REG_RESULT_IND_STRU消息中LAU的结果
*****************************************************************************/
enum MM_MMC_LU_RESULT_ENUM
{
    MM_MMC_LU_RESULT_SUCCESS    = 0,    /*LAU成功*/
    MM_MMC_LU_RESULT_FAILURE    = 1,    /*LAU失败*/
    MM_MMC_LU_RESULT_BUTT
};
typedef VOS_UINT32 MM_MMC_LU_RESULT_ENUM_U32;

/*****************************************************************************
 枚举名    : MM_MMC_LU_PROC_ENUM
 结构说明  : MMMMC_REG_RESULT_IND_STRU消息中LAU过程类型
*****************************************************************************/
enum MM_MMC_LU_PROC_ENUM
{
    MM_MMC_LU_PROC_TRUE     = 0,    /* 真流程标志 */
    MM_MMC_LU_PROC_FALSE    = 1,    /* 假流程标志 */
    MM_MMC_LU_PROC_BUTT
};
typedef VOS_UINT32 MM_MMC_LU_PROC_ENUM_U32;

/*****************************************************************************
 枚举名: MMC_MM_DETACH_TYPE_ENUM
 枚举说明:ATTACH类型
 1.日    期   : 2011年7月01日
   作    者   : w00166186
   修改内容   : 调整消息结构体内容
*****************************************************************************/
enum MMC_MM_DETACH_TYPE_ENUM
{
    MMC_MM_PS_DETACH        = 1,
    MMC_MM_CS_DETACH        = 2,
    MMC_MM_PS_CS_DETACH     = 3,
    MMC_MM_DETACH_BUTT
};
typedef VOS_UINT32 MMC_MM_DETACH_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MMC_MM_DETACH_REASON_ENUM
 结构说明  : detach原因
 1.日    期   : 2015年4月11日
   作    者   : y00245242
   修改内容   : iteration 13开发
*****************************************************************************/
enum MMC_MM_DETACH_REASON_ENUM
{
    MMC_MM_DETACH_REASON_USER_DETACH           = 0,/* 用户触发的detach操作 */
    MMC_MM_DETACH_REASON_RAT_OR_BAND_DETACH    = 1,/* system configure中RAT或band设置触发的detach */
    MMC_MM_DETACH_REASON_SRV_DOMAIN_DETACH     = 2,/* system configure中服务域触发的detach */

    MMC_MM_PIF_DETACH_REASON_BUTT
};
typedef VOS_UINT32 MMC_MM_DETACH_REASON_ENUM_UINT32;

/*****************************************************************************
 枚举名: MMC_MM_ATTACH_TYPE_ENUM
 枚举说明:ATTACH类型
 1.日    期   : 2011年7月01日
   作    者   : w00166186
   修改内容   : 新建
*****************************************************************************/
enum MMC_MM_ATTACH_TYPE_ENUM
{
    MMC_MM_ATTACH_TYPE_NULL          = 0,
    MMC_MM_ATTACH_TYPE_GPRS          = 1,
    MMC_MM_ATTACH_TYPE_IMSI          = 2,
    MMC_MM_ATTACH_TYPE_GPRS_IMSI     = 3,
    MMC_MM_ATTACH_TYPE_BUTT
};
typedef VOS_UINT32 MMC_MM_ATTACH_TYPE_ENUM_UINT32;


/*****************************************************************************
 枚举名: MMC_MM_LAU_REQ_REASON_ENUM
 枚举说明:MMC通知MM的LAU的原因
 1.日    期   : 2014年5月21日
   作    者   : w00167002
   修改内容   : 新建
*****************************************************************************/
enum MMC_MM_LAU_REQ_REASON_ENUM
{
    MMC_MM_LAU_REQ_REASON_SOR          = 0,
    MMC_MM_LAU_REQ_REASON_BUTT
};
typedef VOS_UINT32 MMC_MM_LAU_REQ_REASON_ENUM_UINT32;


/*****************************************************************************
 枚举名: MMC_MM_SYS_INFO_TYPE_ENUM
 枚举说明:MMC通知MM的sys info type
 1.日    期   : 2015年6月11日
   作    者   : b00269685
   修改内容   : 新建
*****************************************************************************/
enum MMC_MM_SYS_INFO_TYPE_ENUM
{
    MMC_MM_SYS_INFO_TYPE_OTA           = 0,                /* 当前是ota */
    MMC_MM_SYS_INFO_TYPE_SYS           = 1,                /* 当前是系统消息 */
    MMC_MM_SYS_INFO_TYPE_BUTT
};
typedef VOS_UINT8 MMC_MM_SYS_INFO_TYPE_ENUM_UINT8;

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
/* 原语MMCMM_SYS_INFO_IND的结构体 */
#ifndef _PLMN_ID_
#define _PLMN_ID_
    typedef struct
    {
        VOS_UINT32                               ulMcc;                                  /* MCC,3 bytes                              */
        VOS_UINT32                               ulMnc;                                  /* MNC,2 or 3 bytes                         */
    }MM_PLMN_ID_STRU;
#endif
#ifndef _LAI_
#define _LAI_
    typedef struct
    {
        MM_PLMN_ID_STRU                     PlmnId;
        VOS_UINT32                               ulLac;                                  /* BIT STRING(SIZE(16))                     */
    }MM_LAI_STRU;
#endif


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头    */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulMask;                                 /* 以下各IE的有效标志                         */
    MMC_MM_SYS_INFO_TYPE_ENUM_UINT8     enSysInfoType;
    VOS_UINT8                           aucReserve1[3];
    MM_PLMN_ID_STRU                     PlmnId;                                 /* 本小区所在PLMN的ID                        */
    VOS_UINT32                          ulCsDrxLength;                          /* CS域DRX长度系数                           */
    VOS_UINT32                          ulPsDrxLength;                          /* PS域DRX长度系数                           */
    VOS_UINT32                          ulForbiddenFlg;                         /* 与本小区相关的禁止信息                */
    VOS_UINT32                          ulCellId;
    VOS_UINT16                          usLac;
    VOS_UINT8                           ucCnCommonSize;
    VOS_UINT8                           ucCsInfoSize;
    VOS_UINT8                           ucPsInfoSize;
    VOS_UINT8                           ucAttachDetach;
    VOS_UINT8                           ucLRTimerT3212;
    VOS_UINT8                           ucGprsSupportInd;
    VOS_UINT8                           ucRac;
    VOS_UINT8                           ucNetworkOperationMode;
    VOS_UINT8                           ucUserSpecificSearchFlg;                /* 标志是否本次驻留的小区为用户指定搜网引起 0: 否, 1: 是 */
    VOS_UINT8                           ucCsChanged2UnBarFlg;                   /* 是否CS域从bar转为不bar: 0 无，1 有 */
    VOS_UINT8                           ucPsChanged2UnBarFlg;                   /* 是否PS域从bar转为不bar: 0 无，1 有 */
    VOS_UINT8                           aucReserve2[3];
}MMCMM_SYS_INFO_IND_STRU;


/* 原语MMCMM_COVERAGE_LOST_IND的结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserve;                                          /* 保留                                     */
}MMCMM_COVERAGE_LOST_IND_STRU;

/*******************************************************************************
 结构名    : MMMMC_CS_REG_RESULT_IND_STRU
 结构说明  : MM向MMC发送LAU结果消息的结构体
 1.日    期   : 2011年7月11日
   作    者   : h44270
   修改内容   : 新建

 2.日    期   : 2012年2月9日
   作    者   : w00167002
   修改内容   : 删除真假流程的判断字段
 3.日    期   : 2012年3月1日
   作    者   : w00176964
   修改内容   : DTS2012022407450:CS注册结果中指示MMC是否为联合注册的结果

*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    MM_MMC_LU_RESULT_ENUM_U32           enLuResult;                             /* LU结果            */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetType;                              /* 当前注册的网络类型 */
    VOS_UINT8                           ucIsComBined;                           /* 是否为联合注册   */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enRegFailCause;                         /* 操作失败原因     */
    VOS_UINT32                          ulServiceStatus ;                       /* 服务状态          */
    VOS_UINT32                          ulCsUpdateStatus ;                      /* CS 域更新状态     */
    VOS_UINT32                          ulLuAttemptCnt ;                        /* LU Attempt counter */
    MM_LAI_STRU                         stOldLai ;                              /* 旧LAI              */
}MMMMC_CS_REG_RESULT_IND_STRU;

/* 消息MMCMM_INFO_IND的结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_MM_INFO_IND_STRU    stMmInfo;                                           /* MM INFORMATION(GMM INFORMATION)          */
}MMCMM_INFO_IND_STRU;

typedef struct
{
    MSG_HEADER_STRU                 MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                      ulCsServFlg;                                        /* CS域业务有无标志                         */
    VOS_UINT32                      ulEmcFlg;/* 标志是否是紧急呼叫,当ulCsServFlg为MM_CS_SERV_NOT_EXIST时且此标志为MM_TRUE时,用于终止PLMN搜索 */
}MMCMM_CM_SERVICE_IND_STRU;
/* A32D12977<== */

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    MM_MMC_PLMN_SEARCH_TYPE_ENUM_U32    enPlmnSearchType;                           /* 指示MM给MMC发送的搜网类型 */
}MMCMM_PLMN_SEARCH_IND_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulReserve;                           /* 指示MM给MMC发送的搜网类型 */
}MMCMM_CSFB_ABORT_IND_STRU;

/* 消息MMCMM_CM_SERVICE_REJECT_IND的结构体 */
typedef struct
{
    MSG_HEADER_STRU                 MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                      ulCause;                                            /* 失败原因                                 */
    VOS_UINT32                      ulServiceStatus ;
}MMCMM_CM_SERVICE_REJECT_IND_STRU;

/* 消息MMCMM_PLMN_SEARCH_INITIATED的结构体 */
typedef struct
{
    MSG_HEADER_STRU                 MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                      ulReserve;                                          /* 保留                                     */
} MMCMM_PLMN_SEARCH_INITIATED_STRU;

/* 消息MMCMM_ABORT_REQ的结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserve;                                          /* 保留                                     */
} MMCMM_REL_REQ_STRU;

/* 消息MMCMM_START_REQ的结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserve;                                          /* 保留                                     */
}MMCMM_START_REQ_STRU;

/* 删除消息MMCMM_PLMN_USER_SEL_REQ的结构体 */

/* 消息MMCMM_START_CNF的结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserve;                                          /* 保留                                     */
} MMCMM_START_CNF_STRU;

/*****************************************************************************
 结构名    : MMCMM_DETACH_REQ_STRU
 结构说明  : MMCMM_DETACH_REQ消息的数据结构
 1.日    期   : 2011年7月01日
   作    者   : w00166186
   修改内容   : 调整消息结构体内容
 2.日    期   : 2015年4月11日
   作    者   : y00245242
   修改内容   : iteration 13开发
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpid;                                 /* MMA定义使用，记录ATTACH编号 */
    MMC_MM_DETACH_TYPE_ENUM_UINT32      enDetachType ;                         /* DETACH 类型 */
    MMC_MM_DETACH_REASON_ENUM_UINT32    enDetachReason;
} MMCMM_DETACH_REQ_STRU;

/*****************************************************************************
 结构名    : MMCMM_DETACH_CNF_STRU
 结构说明  : MMCMM_DETACH_CNF消息的数据结构
 1.日    期   : 2011年7月01日
   作    者   : w00166186
   修改内容   : 调整消息结构体内容
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpid;                                 /* MMA定义使用，记录ATTACH编号 */
    VOS_UINT32                          ulServiceStatus ;                       /* CS域服务状态 */
    VOS_UINT32                          ulDetachType;                           /* detach 类型 */
} MMCMM_DETACH_CNF_STRU;

/*****************************************************************************
 结构名    : MMCMM_W_AC_INFO_CHANGE_IND_STRU
 结构说明  : MMCMM_W_AC_INFO_CHANGE_IND消息的数据结构
 1.日    期   : 2012年2月15日
   作    者   : w00166186
   修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                         MsgHeader;                          /* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_MML_RESTRICTION_CHANGE_ENUM_UINT8   enCsRestrictRegisterChange;         /* CS注册受限改变情况 */
    NAS_MML_RESTRICTION_CHANGE_ENUM_UINT8   enPsRestrictRegisterChange;         /* PS注册受限改变情况 */
}MMCMM_W_AC_INFO_CHANGE_IND_STRU;

/* 消息MMCMM_POWER_OFF_REQ的结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserve;                                          /* 保留                                     */
} MMCMM_POWER_OFF_REQ_STRU;

/* 消息MMCMM_POWER_OFF_CNF的结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserve;                                          /* 保留                                     */
} MMCMM_POWER_OFF_CNF_STRU;

/* 消息MMCMM_REGISTER_INITIATION的结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                              /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserve;                                          /* 保留                                     */
} MMCMM_REGISTER_INITIATION_STRU;

/* 消息MMCMM_DEREGISTER_INITIATION的结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserve;                                          /* 保留                                     */
} MMCMM_DEREGISTER_INITIATION_STRU;

/* 消息MMCMM_RR_CONN_INFO_IND的结构体 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRrConnFlg ;
} MMCMM_RR_CONN_INFO_IND_STRU;

/*****************************************************************************
 结构名    : MMCMM_ATTACH_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MMCMM_ATTACH_REQ消息的数据结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpid;                                 /* MMA定义使用，记录ATTACH编号 */
    MMC_MM_ATTACH_TYPE_ENUM_UINT32      enAttachType;                           /* 注册请求类型                                 */
} MMCMM_ATTACH_REQ_STRU;

/*****************************************************************************
 结构名    : MMCMM_ATTACH_CNF_STRU
 结构说明  : MMCMM_ATTACH_CNF消息的数据结构
 1.日    期   : 2011年7月01日
   作    者   : w00166186
   修改内容   : 调整消息结构体内容
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpid;                                 /* MMA定义使用，记录ATTACH编号 */
    VOS_UINT32                          ulServiceStatus ;                       /* CS域的服务状态 */
}MMCMM_ATTACH_CNF_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulServiceStatus ;
} MMCMM_SERVICE_STATUS_IND_STRU;

/* 消息MMCMM_ MODE_CHANGE_REQ的结构体 */
typedef struct
{
    MSG_HEADER_STRU             MsgHeader;                                      /* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_MML_MS_MODE_ENUM_UINT8  enMsMode;
    VOS_UINT8                   aucReservel[3];
} MMCMM_MODE_CHANGE_REQ_STRU;

/* 消息 MMCMM_REGISTER_STATE_CHANGE_IND 结构体 */
typedef struct
{

    MSG_HEADER_STRU             stMsgHeader;                                            /*_H2ASN_Skip*/
    VOS_UINT8                   MmRegState;
    VOS_UINT8                   aucReservel[3];
}MMCMM_REGISTER_STATE_CHANGE_IND_ST;

/* 消息 MMCMM_GSM_SYS_INFO_IND 结构体 */
typedef struct
{
    MSG_HEADER_STRU     MsgHeader;                                              /*_H2ASN_Skip*/
    RRC_PLMN_ID_STRU    stPlmnId;                     /* 本小区PLMN ID */
    VOS_UINT32          ulCellId;
    VOS_UINT32          ulForbiddenFlg;               /* 与本小区相关的禁止信息                     */
    VOS_UINT16          usLac;                        /* [0x0001－0xFFFE] 位置区码  */
    VOS_UINT8           ucAttachDetach;               /* [0-1] 用于通知MS，在本小区内是否允许进行IMSI结合和分离允许过程:
                                                         0表示不允许手机启动IMSI附着和分离过程，
                                                         1则表示手机必须启动附着和分离过程，message origin:SI3,PSI2 */
    VOS_UINT8           ucLRTimerT3212;               /* [0-255] 周期位置更新定时器,确定了手机进行周期位置更新的频度,
                                                         每1个单位表示6分钟的时间，为0则表示不进行位置更新，message origin:SI3,PSI2 */

    VOS_UINT8           ucGprsSupportInd;             /* [0-1] GPRS支持指示:0-不支持;1-支持*/
    VOS_UINT8           ucRac;                        /* 路由区域码*/
    VOS_UINT8           ucNetworkOperationMode;       /*   网络运行模式:
                                                           0-无效;
                                                           1-网络运行模式I;
                                                           2-网络运行模式II;
                                                           3-网络运行模式III; */
    VOS_UINT8           ucMsrRelease;                 /* [0-1] 0 MSC is Release '98 or older
                                                               1 MSC is Release '99 onwards */


    VOS_UINT8           ucUserSpecificSearchFlg;     /* 标志是否本次驻留的小区为用户指定搜网引起 : 0: 否， 1: 是 */

    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    RRC_NAS_RESTRICTION_UN              unAcInfo;
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    VOS_UINT8           ucCsChanged2UnBarFlg;             /* 是否CS域从bar转为不bar: 0 无，1 有 */
    VOS_UINT8           ucPsChanged2UnBarFlg;             /* 是否PS域从bar转为不bar: 0 无，1 有 */

}MMCMM_GSM_SYS_INFO_IND_ST;


/*MMCMM_RR_REL_IND消息结构定义*/
/* MMCMM_RR_REL_IND_ST ulRrcConnStatus取值 */
typedef struct
{
    MSG_HEADER_STRU                 MsgHeader;                                  /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                      ulCnDomainId;                                               /* 释放信令连接的所属域                     */
    VOS_UINT32                      ulRrcConnStatus;                                            /* 释放信令连接后RRC连接是否存在，取值见宏定义             */
    VOS_UINT32                      ulRelCause;                                                 /* 信令释放原因，取值见宏定义               */
}MMCMM_RR_REL_IND_ST;

/*消息 MMCMM_SUSPEND_RSP 结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                     /* 保留*/
}MMCMM_SUSPEND_RSP_ST;


/*消息 MMCMM_RESUME_RSP结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                     /* 保留*/
}MMCMM_RESUME_RSP_STRU;


/*****************************************************************************
 结构名称: MMCMM_RESUME_IND_STRU
 结构说明: MMCMM_RESUME_IND消息的结构体内容
 1.日    期   : 2011年7月12日
   作    者   : h44270
   修改内容   : V7R1 PhaseII阶段调整，增加MMCMM_RESUME_IND消息的结构
 2.日    期   : 2013年11月26日
   作    者   : w00176964
   修改内容   : Volte PhaseII调整:增加信令连接存在标记
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /*_H2ASN_Skip*/
    MMC_RESUME_RESULT_ENUM_UINT8        ucCsResumeResult;                       /* CS域切换结果 */
    MMC_RESUME_RESULT_ENUM_UINT8        ucPsResumeResult;                       /* PS域切换结果 */
    MMC_RESUME_ORIGEN_ENUM_UINT8        ucResumeOrigen;                         /* 消息发起方，RRMM_ORIGEN_GSM:GSM，RRMM_ORIGEN_WCDMA:WCDMA */
    VOS_UINT8                           ucCsSigExistFlg;                        /* CS信令连接存在标记 */
}MMCMM_RESUME_IND_STRU;


/*****************************************************************************
 结构名称: MMCMM_SUSPEND_IND_STRU
 结构说明: MMCMM_SUSPEND_IND消息的结构体内容
 1.日    期   : 2011年7月12日
   作    者   : h44270
   修改内容   : V7R1 PhaseII阶段调整，增加MMCMM_RESUME_IND消息的结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /*_H2ASN_Skip*/
    MMC_SUSPEND_CAUSE_ENUM_UINT8        ucSuspendCause;                         /* 挂起原因 */
    MMC_SUSPEND_ORIGEN_UINT8            ucSuspendOrigen;                        /* 消息发起方，RRMM_ORIGEN_GSM:GSM，RRMM_ORIGEN_WCDMA:WCDMA*/
    MMC_SUSPEND_DESTINATION_UINT8       ucSuspendDestination;                   /* 挂起的目的方 */
    VOS_UINT8                           aucReserve1[1];                         /* 保留 */
    NAS_RRC_RE_TX_MSG_STRU              astReTxMsg[NAS_RRC_MAX_RE_TX_MSG_NUM];  /* 缓存重发的消息 */
}MMCMM_SUSPEND_IND_STRU;


/*****************************************************************************
 结构名称: MMMMC_ABORT_IND_STRU
 结构说明: MMMMC_ABORT_IND消息的结构体内容
 1.日    期   : 2012年7月12日
   作    者   : s00217060
   修改内容   : for sync lmm cs state，增加MMMMC_ABORT_IND消息的结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                              /*_H2ASN_Skip*/
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enAbortCause;                           /* Abort原因 */
    VOS_UINT8                           aucReserve1[2];                         /* 保留 */
}MMMMC_ABORT_IND_STRU;

/*****************************************************************************
 结构名    : MMCMM_SIM_AUTH_FAIL_IND_STRU
 结构说明  : MMCMM_SIM_AUTH_FAIL_IND_STRU的数据结构
 1.日    期: 2013年11月16日
   作    者: m00217266
   修改内容:
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                         MsgHeader;                          /* 消息头  */ /*_H2ASN_Skip*/
    NAS_MML_SIM_AUTH_FAIL_ENUM_UINT16       enSimAuthFailValue;
    VOS_UINT8                               ucReservel;
    NAS_MM_COM_SERVICE_DOMAIN_ENUM_UINT8    enSrvDomain;
}MMCMM_SIM_AUTH_FAIL_IND_STRU;

/*****************************************************************************
 结构名称: MMCMM_SRVCC_INFO_NOTIFY_STRU
 结构说明: MMCMM_SRVCC_INFO_NOTIFY消息的结构体内容
 1.日    期   : 2013年11月26日
   作    者   : W00176964
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                 MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT8                       aucRsv[4];                                          /* 保留                                     */
}MMCMM_SRVCC_INFO_NOTIFY_STRU;



/*****************************************************************************
 结构名    : RRMM_RAT_CHANGE_IND_STRU
 结构说明  : RRMM_RAT_CHANGE_IND_STRU的数据结构
 1.日    期: 2014年3月27日
   作    者: y00176023
   修改内容: V8R1 DSDS II 增加RAT变化时的通知
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /*_H2ASN_Skip*/
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType;       /* NAS RAT */
    VOS_UINT8                           aucReserve1[3];     /* 保留 */
}MMCMM_RAT_CHANGE_IND_STRU;

/*****************************************************************************
 结构名称: MMCMM_LAU_REQ_STRU
 结构说明: MMCMM_LAU_REQ_STRU消息的结构体内容
 1.日    期   : 2013年11月26日
   作    者   : W00167002
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                                         /* 消息头                                   */ /*_H2ASN_Skip*/
    MMC_MM_LAU_REQ_REASON_ENUM_UINT32   enLauReqReason;                                    /* MMC触发LAU的原因                         */
}MMCMM_LAU_REQ_STRU;


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 结构名    : MMCMM_LMM_ATTACH_IND_STRU
 结构说明  : MMCMM_LMM_ATTACH_IND的数据结构
 1.日    期: 2011年10月26日
   作    者: w00176964
   修改内容: V7R1 PhaseIII阶段调整:新增MMC通知MM关于LMM的attach结果的数据结构
*****************************************************************************/
typedef  LMM_MMC_ATTACH_IND_STRU MMCMM_LMM_ATTACH_IND_STRU;

/*****************************************************************************
 结构名    : MMCMM_LMM_TAU_RESULT_IND_STRU
 结构说明  : MMCMM_LMM_TAU_RESULT_IND的数据结构
 1.日    期: 2011年10月26日
   作    者: w00176964
   修改内容: V7R1 PhaseIII阶段调整:新增MMC通知MM关于LMM的TAU结果的数据结构
*****************************************************************************/
typedef  LMM_MMC_TAU_RESULT_IND_STRU MMCMM_LMM_TAU_RESULT_IND_STRU;


/*****************************************************************************
 结构名    : MMCMM_LMM_MT_DETACH_IND_STRU
 结构说明  : MMCMM_LMM_MT_DETACH_IND的数据结构
 1.日    期: 2011年10月26日
   作    者: w00176964
   修改内容: V7R1 PhaseIII阶段调整:新增MMC通知MM关于LMM的detach结果的数据结构
*****************************************************************************/
typedef  LMM_MMC_DETACH_IND_STRU MMCMM_LMM_MT_DETACH_IND_STRU;

/*****************************************************************************
 结构名    : MMCMM_LMM_SERVICE_RESULT_IND_STRU
 结构说明  : MMCMM_LMM_SERVICE_RESULT_IND的数据结构
 1.日    期: 2011年10月26日
   作    者: w00176964
   修改内容: V7R1 PhaseIII阶段调整:新增MMC通知MM关于LMM的service结果的数据结构
*****************************************************************************/
typedef  LMM_MMC_SERVICE_RESULT_IND_STRU MMCMM_LMM_SERVICE_RESULT_IND_STRU;

/*****************************************************************************
 结构名    : MMCMM_LMM_MO_DETACH_IND_STRU
 结构说明  : MMCMM_LMM_MO_DETACH_IND的数据结构
 1.日    期: 2011年11月28日
   作    者: w00176964
   修改内容: V7R1 PhaseIV阶段调整:新增MMC通知MM关于LMM的UE detach结果的数据结构
*****************************************************************************/
typedef  LMM_MMC_DETACH_CNF_STRU MMCMM_LMM_MO_DETACH_IND_STRU;

/*****************************************************************************
 结构名    : MMCMM_LMM_LOCAL_DETACH_IND_STRU
 结构说明  : MMCMM_LMM_LOCAL_DETACH_IND_STRU的数据结构
 1.日    期: 2011年12月6日
   作    者: w00176964
   修改内容: V7R1 PhaseIV阶段调整:新增MMC通知MM关于LMM的LOCAL detach结果的数据结构
*****************************************************************************/
typedef  LMM_MMC_DETACH_IND_STRU MMCMM_LMM_LOCAL_DETACH_IND_STRU;

/*****************************************************************************
 结构名    : MMC_MM_LTE_SYS_INFO_IND_STRU
 结构说明  : MMC_MM_LTE_SYS_INFO_IND的数据结构
 1.日    期: 2012年04月26日
   作    者: w00166186
   修改内容: 新增结构
*****************************************************************************/
typedef  LMM_MMC_SYS_INFO_IND_STRU MMC_MM_LTE_SYS_INFO_IND_STRU;


/*****************************************************************************
 结构名    : MMCMM_LMM_TIMER_STATE_NOTIFY_STRU
 结构说明  : MMCMM_LMM_TIMER_STATUS_NOTIFY_STRU的数据结构
 1.日    期: 2012年2月27日
   作    者: z00161729
   修改内容: V7R1 C50 支持ISR功能调整:新增MMC通知MM关于LMM定时器状态的数据结构
*****************************************************************************/
typedef  LMM_MMC_TIMER_STATE_NOTIFY_STRU MMCMM_LMM_TIMER_STATE_NOTIFY_STRU;

#endif

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
    MMC_MM_MSG_TYPE_ENUM_UINT16         enMsgID;    /*_H2ASN_MsgChoice_Export MMC_MM_MSG_TYPE_ENUM_UINT16*/
                                                    /* 为了兼容NAS的消息头定义，所以转换ASN.1使用MMC_MM_MSG_TYPE_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MMC_MM_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}MMC_MM_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    MMC_MM_MSG_DATA                    stMsgData;
}MmcMmInterface_MSG;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif/* __cpluscplus */

#endif



