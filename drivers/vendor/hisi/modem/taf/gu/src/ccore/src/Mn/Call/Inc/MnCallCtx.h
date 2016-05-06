/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnCallCtx.h
  版 本 号   : 初稿
  作    者   : s62952
  生成日期   : 2012年03月03日
  最近修改   :
  功能描述   : MnCallCtx.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : 创建文件

******************************************************************************/
#ifndef _MN_CALL_CTX_H_
#define _MN_CALL_CTX_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include  "MnCallApi.h"
#include  "NasCcAirMsg.h"

#include "NasMncc.h"

/* Added by l00167671 for NV拆分项目 , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV拆分项目 , 2013-05-17, end*/

/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, begin */
#include "VcCallInterface.h"
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, end */


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

#define  MN_CALL_MAX_SS_CMD_KEY_EVT_NUM    (10)                                  /* 补充业务操作管理结构 */

#define  MN_CALL_ENTITY_MAX_NUM            (1)                                  /*CALL模块支持的实体数，目前只有一个*/
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, end */
#define  MN_CALL_INVALID_CATEGORY          (128)                                /* 用户定制的紧急呼号码最大条数 */

#define MN_CALL_ONE_THOUSAND_MILLISECOND                    (1000)              /* 1000MS */



/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/* 补充业务后续操作 */
typedef enum
{
    MN_CALL_SS_SUBSEQ_OP_RPT_SUCC,                                              /* 向应用层上报操作成功 */
    MN_CALL_SS_SUBSEQ_OP_RPT_FAIL,                                              /* 向应用层上报操作失败 */
    MN_CALL_SS_SUBSEQ_OP_ACCPT_OTH                                              /* 接听另一个呼叫 */
} MN_CALL_SS_SUBSEQ_OP_ENUM;

/* 补充业务后续操作 */
typedef enum
{
    MN_CALL_CTRL_NULL,                                                          /* 向应用层上报操作成功 */
    MN_CALL_CTRL_PROCEEDING,                                                    /* 向应用层上报操作失败 */
    MN_CALL_CTRL_END,                                                           /* 接听另一个呼叫 */
    MN_CALL_CTRL_MAX
} MN_CALL_CTRL_STATE_ENUM;
typedef TAF_UINT32    MN_CALL_CTRL_STATE_ENUM_U32;

/* 补充业务进展事件 */
typedef enum
{
    MN_CALL_SS_PROG_EVT_REL,                                                    /* 有呼叫被挂断 */
    MN_CALL_SS_PROG_EVT_SETUP_COMPL,                                            /* 来电接听完成 */
    MN_CALL_SS_PROG_EVT_HOLD_CNF,                                               /* 呼叫保持成功 */
    MN_CALL_SS_PROG_EVT_HOLD_REJ,                                               /* 呼叫保持被拒绝 */
    MN_CALL_SS_PROG_EVT_RETRIEVE_CNF,                                           /* 呼叫恢复成功 */
    MN_CALL_SS_PROG_EVT_RETRIEVE_REJ,                                           /* 呼叫恢复被拒绝 */
    MN_CALL_SS_PROG_EVT_BUILD_MPTY_CNF,                                         /* 建立MPTY成功 */
    MN_CALL_SS_PROG_EVT_BUILD_MPTY_REJ,                                         /* 建立MPTY被拒绝 */
    MN_CALL_SS_PROG_EVT_SPLIT_MPTY_CNF,                                         /* 分离MPTY成功 */
    MN_CALL_SS_PROG_EVT_SPLIT_MPTY_REJ,                                         /* 分离MPTY被拒绝 */
    MN_CALL_SS_PROG_EVT_DEFLECT_CNF,                                            /* 呼叫偏转成功 */
    MN_CALL_SS_PROG_EVT_DEFLECT_REJ,                                            /* 呼叫偏转被拒绝 */
    MN_CALL_SS_PROG_EVT_ACT_CCBS_CNF,                                           /* 激活CCBS成功 */
    MN_CALL_SS_PROG_EVT_ACT_CCBS_REJ,                                           /* 激活CCBS被拒绝 */
    MN_CALL_SS_PROG_EVT_ECT_CNF,                                                /* ECT操作成功 */
    MN_CALL_SS_PROG_EVT_ECT_REJ,                                                /* ECT操作被拒绝 */
    MN_CALL_SS_PROG_EVT_MAX
} MN_CALL_SS_PROGRESS_EVT_ENUM;

/*****************************************************************************
 枚举名    : MN_CALL_SRVCC_STATE_ENUM_UINT8
 枚举说明  : SRVCC状态
 1.日    期   : 2013年12月25日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum MN_CALL_SRVCC_STATE_ENUM
{
    MN_CALL_SRVCC_STATE_START,
    MN_CALL_SRVCC_STATE_SUCCESS,
    MN_CALL_SRVCC_STATE_FAIL,

    MN_CALL_SRVCC_STATE_BUTT
};
typedef VOS_UINT8 MN_CALL_SRVCC_STATE_ENUM_UINT8;

/* Modified by z00234330 for PCLINT清理, 2014-07-03, begin */
/* VP功能的NV设置状态 */
enum MN_CALL_VP_NV_CFG_STATE_ENUM
{
    MN_CALL_VP_MO_MT_BOTH               = 0,                                    /* 允许视频呼叫(包括主叫和被叫) */
    MN_CALL_VP_NONE                     = 1,                                    /* 禁止视频主叫和被叫 */
    MN_CALL_VP_MO_ONLY                  = 2,                                    /* 允许视频主叫，禁止视频被叫 */
    MN_CALL_VP_MT_ONLY                  = 3,                                    /* 禁止视频主叫，允许视频被叫 */
    MN_CALL_VP_BUTT
};
typedef VOS_UINT8   MN_CALL_VP_NV_CFG_STATE_ENUM_U8;
/* Modified by z00234330 for PCLINT清理, 2014-07-03, end */

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
 结构名    : TAF_CALL_REDIAL_CFG_STRU
 结构说明  : 记录呼叫重建配置信息
  1.日    期   : 2015年8月24日
    作    者   : n00355355
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCallRedialSupportFlg;                 /* 支持呼叫重建功能标志，VOS_TRUE:支持；VOS_FALSE:不支持*/
    VOS_UINT8                           ucCallRedialCmSrvRejCauseNum;           /* 呼叫被cm service reject拒绝的原因值*/
    VOS_UINT8                           aucReserved1[2];
    VOS_UINT32                          ulCallRedialPeriod;                     /* 呼叫重建特性打开时，呼叫重建最大时长，单位毫秒 */
    VOS_UINT32                          ulCallRedialInterval;                   /* 呼叫重建特性打开时，呼叫重拨间隔单位毫秒 */
    VOS_UINT8                           aucCallRedialCmSrvRejCause[TAF_NVIM_CALL_REDIAL_CAUSE_MAX_NUM];
}TAF_CALL_REDIAL_CFG_STRU;

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-3, begin */
/*****************************************************************************
 结构名    : MN_CALL_REDIAL_CFG_INFO_STRU
 结构说明  : 记录呼叫重拨配置信息
 1.日    期   : 2014年04月03日
   作    者   : y00245242
   修改内容   : 为eCall feature增加
*****************************************************************************/
typedef struct
{
    TAF_CALL_REDIAL_CFG_STRU            stCallRedialCfg;            /* call呼叫配置信息 */
    MN_CALL_REDIAL_CFG_STRU             stEcallRedialCfg;           /* ecall呼叫重拨配置信息 */
}MN_CALL_REDIAL_CFG_INFO_STRU;
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-3, end */

/*****************************************************************************
 结构名    : MN_CALL_CUSTOM_CFG_INFO_STRU
 结构说明  : NVIM项中的MS定制需求信息
 1.日    期   : 2012年03月03日
   作    者   : s62952
   修改内容   : 新建
 2.日    期   : 2012年06月11日
   作    者   : w00166186
   修改内容   : AT&T&DCM项目增加定制紧急呼号码
 3.日    期   : 2012年10月29日
   作    者   : z00161729
   修改内容   : DTS2012083102536:支持cc呼叫重建
 4.日    期   : 2013年12月09日
   作    者   : f62575
   修改内容   : DTS2013120411878，终端不支持VOICE/VIDEO CALL，回复RELEASE COMPLETE
消息原因定制值
 5.日    期   : 2014年04月15日
   作    者   : y00245242
   修改内容   : 为eCall feature增加
 6.日    期   : 2014年6月23日
    作    者   : z00161729
    修改内容   : DSDS III新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCcbsSupportFlg;                       /*CCBS(遇忙呼叫完成)业务*/
    /* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, begin */

    /* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, end */
    VOS_UINT8                           ucCallDeflectionSupportFlg;             /*支持呼叫偏转业务 */
    VOS_UINT8                           ucAlsSupportFlg;                        /*支持线路切换业务*/

    VOS_UINT8                           ucReportEccNumFlg;

    VOS_UINT8                           ucVoiceCallNotSupportedCause;
    VOS_UINT8                           ucVideoCallNotSupportedCause;

    /* Modified by z00234330 for PCLINT清理, 2014-07-03, begin */
    VOS_UINT8                           ucTafCallStatusControl;
    VOS_UINT8                           ucTafMultiSimCallStatusControl;
    MN_CALL_VP_NV_CFG_STATE_ENUM_U8     enVpNvCfgState;  /* NV项，用控制是否支持可视电话的特性 */
    /* Modified by z00234330 for PCLINT清理, 2014-07-03, end */
    VOS_UINT8                           aucReserve[2];

    VOS_UINT8                           ucAtaReportOkAsyncFlag;


    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-3, begin */
    MN_CALL_REDIAL_CFG_INFO_STRU         stCallRedialCfgInfo;
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-3, end */

    TAF_CALL_CCWA_CTRL_MODE_ENUM_U8     enCcwaCtrlMode;
}MN_CALL_CUSTOM_CFG_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_CALL_APP_CFG_INFO_STRU
 结构说明  : AP配置的信息
 1.日    期   : 2015年08月24日
   作    者   : n00269697
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    /* 在VOLTE网络下(NV2340配置CCWA控制模式是UE控制)，默认支持呼叫等待 */
    VOS_UINT8                           ucCcwaiFlg;
    VOS_UINT8                           aucReserve[3];

}TAF_CALL_APP_CFG_INFO_STRU;

/*****************************************************************************
 结构名    : MN_CALL_MS_CFG_INFO_STRU
 结构说明  : MS支持的MS配置能力
 1.日    期   : 2012年03月03日
   作    者   : s62952
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MN_CALL_CUSTOM_CFG_INFO_STRU        stCustomCfg;                            /* NVIM中的定制信息 */
    TAF_CALL_APP_CFG_INFO_STRU          stAppCfg;                                /* AP配置的信息 */
}MN_CALL_MS_CFG_INFO_STRU;

/*****************************************************************************
 结构名    : MN_CALL_MGMT_STRU
 结构说明  : 呼叫管理结构
 1.日    期   : 2012年03月03日
   作    者   : s62952
   修改内容   : 新建
 2.日    期   : 2012年09月20日
   作    者   : f62575
   修改内容   : STK&DCM 项目, 删除enCallCtrlState， dataCfg
 3.日    期   : 2012年10月11日
   作    者   : h44270
   修改内容   : STK&DCM 项目, 增加ulDtmfInProc，标记是否存在DTMF过程
 4.日    期   : 2013年07月11日
   作    者   : l00198894
   修改内容   : V9R1 STK升级项目
****************************************************************************/
typedef struct
{
    VOS_BOOL                            bUsed;                                  /* 是否已被使用 */
    VOS_UINT32                          ulTi;                                   /* 该呼叫对应的CC实体的Ti */
    MN_CALL_CLIR_CFG_ENUM_U8            enClirCfg;                              /* 主叫号码限制的配置 */
    VOS_UINT8                           ucSrvccLocalAlertedFlag;                /* 在alerting状态SRVCC时，是否已经本地振铃 */
    VOS_UINT8                           aucReserved[2];
    MN_CALL_CUG_CFG_STRU                stCugCfg;                               /* CUG的配置 */
    VOS_BOOL                            bRbSet;
    VOS_UINT32                          ulRbId;
    VOS_BOOL                            bVpChannelOpenFlg;                      /*记录呼叫类型为可视电话情况下业务信道是否已打开*/
    /* Deleted by l00198894 for V9R1 STK升级, 2013/07/11 */
    MN_CALL_INFO_STRU                   stCallInfo;                             /* 呼叫信息 */
} MN_CALL_MGMT_STRU;

/*****************************************************************************
 结构名    : MN_CALL_SUPS_CMD_ENUM_U8_KEY_EVT_STRU
 结构说明  : 被关注的补充业务操作事件 结构
 1.日    期   : 2012年03月03日
   作    者   : s62952
   修改内容   : 新建

****************************************************************************/
typedef struct
{
    MN_CALL_ID_T                        callId;                                 /* 产生事件的呼叫ID */
    VOS_UINT8                           aucReserved[3];
    MN_CALL_SS_PROGRESS_EVT_ENUM        enEvt;                                  /* 事件的类型 */
    MN_CALL_SS_SUBSEQ_OP_ENUM           enSubseqOp;                             /* 收到该事件的后续操作 */
} MN_CALL_SUPS_CMD_ENUM_U8_KEY_EVT_STRU;

/*****************************************************************************
 结构名    : MN_CALL_SUPS_CMD_ENUM_U8_MGMT_STRU
 结构说明  : 补充业务管理结构
 1.日    期   : 2012年03月03日
   作    者   : s62952
   修改内容   : 新建

****************************************************************************/
typedef struct
{
    VOS_UINT8                               bInProgress;                        /* 是否有操作正在进行 */
    MN_CALL_SUPS_CMD_ENUM_U8                enCallSupsCmd;                      /* 当前的操作 */
    MN_CLIENT_ID_T                          clientId;                           /* 发起操作的Client的ID */
    MN_OPERATION_ID_T                       opId;
    VOS_UINT8                               ucNumOfKeyEvt;                      /* 关注的事件个数 */
    VOS_UINT8                               ucInvokeId;
    VOS_UINT8                               aucReserved[1];
    MN_CALL_SUPS_CMD_ENUM_U8_KEY_EVT_STRU   astKeyEvts[MN_CALL_MAX_SS_CMD_KEY_EVT_NUM];  /* 关注的事件 */
} MN_CALL_SUPS_CMD_ENUM_U8_MGMT_STRU;

/*****************************************************************************
 结构名    : MN_CALL_MSG_BUFF_STRU
 结构说明  : 缓存普通呼叫或紧急呼叫setup消息和rel消息
 1.日    期   : 2012年10月29日
   作    者   : z00161729
   修改内容   : 支持呼叫重建新增结构

****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpBufferedSetupMsg : 1;
    VOS_UINT32                          bitOpBufferedRejIndMsg : 1;
    VOS_UINT32                          bitSpare : 30;
    MNCC_REQ_PRIM_MSG_STRU              stBufferedSetupMsg;
    MNCC_IND_PRIM_MSG_STRU              stBufferedRejIndMsg;
} MN_CALL_MSG_BUFF_STRU;


/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-8, begin */
/*****************************************************************************
 结构名    : MN_CALL_ECALL_CTX_STRU
 结构说明  : eCall相关的上下文数据结构
 1.日    期   : 2014年04月08日
   作    者   : y00245242
   修改内容   : 为ecall特性功能增加
****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucWaitMtEcallFlag;            /* 等待mt eCall标记 */
    VC_CALL_ECALL_TRANS_STATUS_ENUM_UINT8                   enEcallTransStatus;           /* eCall MSD当前传输状态 */
    VOS_UINT8                                               ucInternalHangUpFlag;         /* 内部挂机标志 */
    VOS_UINT8                                               aucReserved[1];               /* 保留位 */
    VOS_UINT32                                              ulEcallPeriodTimerLen;        /* 记录eCall period剩余时长 */
}MN_CALL_ECALL_CTX_STRU;
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-8, end */

/*****************************************************************************
 结构名    : MN_CALL_CONTEXT_STRU
 结构说明  : MN CALL 模块运行上下文
 1.日    期   : 2012年03月03日
   作    者   : s62952
   修改内容   : 新建
 2.日    期   : 2012年10月29日
   作    者   : z00161729
   修改内容   : DTS2012083102536:支持cc呼叫重建
 3.日    期   : 2014年04月08日
   作    者   : y00245242
   修改内容   : 为ecall特性功能修改
*****************************************************************************/
typedef struct
{
    MN_CALL_MGMT_STRU                         stCallMgmtInfo;                   /* 呼叫管理信息 */
    MN_CALL_SUPS_CMD_ENUM_U8_KEY_EVT_STRU     stSimInfo;                        /*被关注的补充业务操作事件*/
    MN_CALL_MS_CFG_INFO_STRU                  stMsCfgInfo;                      /* MS的配置信息 */
    MN_CALL_SUPS_CMD_ENUM_U8_MGMT_STRU        stNetworkInfo;                    /* 补充业务管理结构*/

    MN_CALL_MSG_BUFF_STRU                     stMnCallBufferedMsg;              /* 呼叫重建功能需要缓冲普通呼叫或紧急呼叫set up消息 */

    MN_CALL_SRVCC_STATE_ENUM_UINT8            enSrvccState;

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-8, begin */
    MN_CALL_ECALL_CTX_STRU                    stEcallCtx;                       /* 增加保存eCall 上下文信息 */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-8, end */
}MN_CALL_CONTEXT_STRU;

/* 任意点回放导出全局变量使用*/
typedef struct
{
    MN_CALL_MGMT_STRU                   pc_g_f_astCallMgmtEntities[MN_CALL_MAX_NUM];
    MN_CALL_SUPS_CMD_ENUM_U8_MGMT_STRU  pc_g_f_stCallSupsCmdMgmt;

    /*CCBS功能打开时,保留的Setup消息 */
    NAS_CC_MSG_SETUP_MO_STRU            pc_g_f_stCcbsSetup;

    MN_CALL_ALS_LINE_NO_ENUM_U8         pc_g_f_enAlsLineNo;
    VOS_UINT8                           pc_g_gucTafCallStatusControl;
    VOS_UINT8                           pc_g_gucTafMultiSimCallStatusControl;
    VOS_UINT8                           pc_g_g_enVpNvCfgState;
} NAS_CALL_OUTSIDE_RUNNING_CONTEXT_ST;

typedef struct
{
    MN_CALL_UUS1_MSG_TYPE_ENUM_U32      enCallMsgType;
    NAS_CC_MSG_TYPE_ENUM_U8             enCcMsgType;
}MN_CALL_MATCH_MSG_TYPE_STRU;


/*****************************************************************************
 Structure      : NAS_CC_SDT_MSG_ST
 Description    : PC回放工程，CC相关的全局变量通过以下消息结构发送
 Message origin :
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                        MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_CALL_OUTSIDE_RUNNING_CONTEXT_ST    stOutsideCtx;
}NAS_CALL_SDT_MSG_ST;

/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, end */


/* Deleted by l00198894 for V9R1 STK升级, 2013/07/11 */

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/



/*****************************************************************************
  10 函数声明
*****************************************************************************/

/*****************************************************************************
 函 数 名  : MN_CALL_GetCustomCfgInfo
 功能描述  : 获取CALL中保存特性定制特性信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CALL中保存特性定制特性信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月3日
   作    者   : s62952
   修改内容   : 新生成函数

*****************************************************************************/
MN_CALL_CUSTOM_CFG_INFO_STRU* MN_CALL_GetCustomCfgInfo( VOS_VOID );

VOS_UINT32 MN_CALL_GetCallRedialSupportFlg(VOS_VOID);
MN_CALL_MSG_BUFF_STRU*  MN_CALL_GetBufferedMsg( VOS_VOID );
VOS_VOID MN_CALL_ClearBufferedMsg(VOS_VOID);
VOS_VOID MN_CALL_InitCtx(VOS_VOID);


TAF_CALL_CCWA_CTRL_MODE_ENUM_U8 TAF_CALL_GetCcwaCtrlMode(VOS_VOID);
VOS_VOID TAF_CALL_SetCcwaCtrlMode(
    TAF_CALL_CCWA_CTRL_MODE_ENUM_U8     enCcwaCtrlMode
);
TAF_CALL_APP_CFG_INFO_STRU* MN_CALL_GetAppCfgInfo(VOS_VOID);
VOS_VOID TAF_CALL_SetCcwaiFlg(
    VOS_UINT8                           bCcwaiFlg
);
VOS_UINT8 TAF_CALL_GetCcwaiFlg(VOS_VOID);

VOS_VOID TAF_CALL_SetAtaReportOkAsyncFlag(
    VOS_UINT8                           ucAtaReportOkAsyncFlag
);
VOS_UINT8 TAF_CALL_GetAtaReportOkAsyncFlag(VOS_VOID);

TAF_CALL_REDIAL_CFG_STRU *MN_CALL_GetCallRedialCfg(VOS_VOID);
#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID TAF_CALL_SetSrvccState(MN_CALL_SRVCC_STATE_ENUM_UINT8 enSrvccState);

MN_CALL_SRVCC_STATE_ENUM_UINT8 TAF_CALL_GetSrvccState(VOS_VOID);
#endif

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-8, begin */
#if (FEATURE_ON == FEATURE_ECALL)
MN_CALL_REDIAL_CFG_STRU *TAF_CALL_GetEcallRedialCfg(VOS_VOID);
VOS_UINT8 TAF_CALL_GetEcallRedialSupportFlg(VOS_VOID);
VC_CALL_ECALL_TRANS_STATUS_ENUM_UINT8 TAF_CALL_GetEcallMsdTransStatus(VOS_VOID);
VOS_VOID TAF_CALL_SetEcallMsdTransStatus(VC_CALL_ECALL_TRANS_STATUS_ENUM_UINT8 enEcallTransStatus);
VOS_UINT8 TAF_CALL_GetWaitingMtEcallFlag(VOS_VOID);
VOS_VOID TAF_CALL_SetWaitingMtEcallFlag(VOS_UINT8 ucWaitMtEcallFlag);
VOS_VOID TAF_CALL_SetInternalHangUpFlag(VOS_UINT8 ucIntHangUpFlag);
VOS_UINT8 TAF_CALL_GetInternalHangUpFlag(VOS_VOID);
VOS_VOID TAF_CALL_ResetEcallPeriodRemainTimerLen(VOS_VOID);
VOS_VOID TAF_CALL_UpdateEcallPeriodRemainTimerLen(VOS_UINT32 ulEcallPeriodTimerLen);
VOS_UINT32 TAF_CALL_GetEcallPeriodRemainTimerLen(VOS_VOID);
#endif

VOS_UINT32 TAF_CALL_GetRedialSupportFlg(VOS_UINT8 ucCallId);
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-8, end */

/* Modified by z00234330 for PCLINT清理, 2014-07-03, begin */

VOS_VOID TAF_CALL_SetCallStatusControl(
    VOS_UINT8                           ucCallStatus
);

VOS_UINT8 TAF_CALL_GetCallStatusControl( VOS_VOID  );

VOS_VOID TAF_CALL_SetMultiSimCallStatusControl(
    VOS_UINT8                           ucMultiSimCallStatus
);

VOS_UINT8 TAF_CALL_GetMultiSimCallStatusControl( VOS_VOID  );

VOS_VOID TAF_CALL_SetVpCfgState(
    MN_CALL_VP_NV_CFG_STATE_ENUM_U8     enVpStateStatus
);

MN_CALL_VP_NV_CFG_STATE_ENUM_U8 TAF_CALL_GetVpCfgState( VOS_VOID  );



/* Modified by z00234330 for PCLINT清理, 2014-07-03, end */

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

#endif /* end of MnCallCtx.h */

