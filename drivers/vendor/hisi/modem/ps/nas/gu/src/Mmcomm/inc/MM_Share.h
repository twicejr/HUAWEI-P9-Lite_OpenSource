/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : MM_Share.h
  Description :
  History     :
  1.  张志勇     2004.03.10  新规作成
  2.  l40632     2006-04-20 根据问题单A32D03300
  3.  x51137 2006/5/5 A32D03487

  4.日    期   : 2006年8月4日
    作    者   : liuyang id:48197
    修改内容   : 根据问题单号：A32D05223
  5.日    期   : 2006年08月09日
    作    者   : 蒋丽萍j60010247
    修改内容   : 问题单A32D03479，在PC机上实现时将#pragma pack(0)和#pragma pack()加编译开关
  6. x51137 A32D06629 2006 10 22
    Date         Updated By      PR Number
    2006-10-26   Li Jilin        A32D06630
  8.日    期   : 2006年11月17日
    作    者   : luojian id:60022475
    修改内容   : 根据问题单号：A32D06616
  9.日    期   : 2007年07月10日
    作    者   : s46746
    修改内容   : 根据问题单号：A32D12268
 10.日    期  : 2007年12月12日
    作    者  : l65478
    修改内容  : 问题单号:A32D13951
 11.日    期   : 2008年5月27日
    作    者   : s46746
    修改内容   : 问题单号:AT2D03209,增加列表搜索时响应寻呼处理
 12.日    期   : 2008年7月28日
    作    者   : s46746
    修改内容   : 问题单号:AT2D03915,修改联合RAU类型,CS如果已经单独LAU成功，需要
                 发起with IMSI Attach的RAU
 13.日    期   : 2008年09月03日
    作    者   : o00132663
    修改内容   : 问题单号：AT2D05472,扩展^CMM命令，支持修改接入模式和搜网模式。
 14.日    期   : 2009年01月15日
    作    者   : l00130025
    修改内容   : 问题单号:AT2D07018,LAU或RAU过程中搜网和SYSCFG设置,发起底层释放链接的操作
 15.日    期   : 2009年03月19日
    作    者   : l00130025
    修改内容   : 问题单号：AT2D09743,WAS的 D/F/P态下丢网处理
 16.日    期   : 2009年04月23日
    作    者   : l00130025
    修改内容   : 问题单号:AT2D11301,IMEISv处理错误导致Gmm/MM在联通网络被拒
*******************************************************************************/
#ifndef _MMSHARE_H_
#define _MMSHARE_H_

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasComm.h"
#include "NasMmlCtx.h"
#include "NasMmcCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*
<EMM Combined procedures Capability : bit >：这个域指示MS是否支持EMM联合注册。
0表示不支持EMM联合注册。
1表示支持EMM联合注册。
*/
enum NAS_EMM_COMB_CAPABILITY_ENUM
{
    NAS_EMM_COMB_CAPABILITY_UNSUPPORT,
    NAS_EMM_COMB_CAPABILITY_SUPPORT,
    NAS_EMM_COMB_CAPABILITY_BUTT
};
typedef VOS_UINT32 NAS_EMM_COMB_CAPABILITY_ENUM_U32;

/*
 <ISR support : bit >：这个域指示MS是否支持ISR功能，
 ISR功能（Idle Mode Signalling Reduction）主要是为了减少L模重选到GU模或GU模
 重选到L模空闲态下的信令。

0  表示不支持ISR功能。
1  表示支持ISR功能。
*/
enum NAS_EMM_ISR_SUPPORT_ENUM
{
    NAS_EMM_ISR_SUPPORT_UNSUPPORT,
    NAS_EMM_ISR_SUPPORT_SUPPORT,
    NAS_EMM_ISR_SUPPORT_BUTT
};
typedef VOS_UINT32 NAS_EMM_ISR_SUPPORT_ENUM_U32;

/*
<EPC capability: bit >：这个域指示MS是否支持EPC接入网络的能力。
0表示不支持EPC，EPC的接入仅包含PDN的网关。
1表示支持EPC，EPC的接入仅包含PDN的网关，GERAN以及UTRAN
*/
enum NAS_EMM_EPC_CAPABILITY_ENUM
{
    NAS_EMM_EPC_CAPABILITY_UNSUPPORT,
    NAS_EMM_EPC_CAPABILITY_SUPPORT,
    NAS_EMM_EPC_CAPABILITY_BUTT
};
typedef VOS_UINT32 NAS_EMM_EPC_CAPABILITY_ENUM_U32;


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
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/



/* 老代码，需逐步清理 */

/* MM子层共享变量结构 */
#define     MM_TIMER_TICK               10


/* SUSPEND时，若当前定时器已超时，但还未收到VOS_TIMER的超时消息，则暂时取一个1s，待超时消息收到后，清除 */

#define     MM_EXTRA_DELAY_TIME_LEN  1000



/************** ucSimType 取值 ****************************/
#define     MMC_SIM_TYPE_SIM            (0)
#define     MMC_SIM_TYPE_USIM           (1)


/* 终端可配置需求，定义终端与网络交互时依据的协议版本 */
#define PS_CUSTOM_REL_VER_R97                               0
#define PS_CUSTOM_REL_VER_R99                               1
#define PS_CUSTOM_REL_VER_AUTO                              2

/* 终端可配置需求，定义终端与网络交互时依据的协议版本 */
#define PS_STEERING_OF_ROAMING_NOT_SUPPORT                  0
#define PS_STEERING_OF_ROAMING_SUPPORT                      1

#define Mm_StartRelTimer(phTm, Pid, ulLength, ulName, ulParam, ucMode) \
        NAS_StartRelTimer(phTm, Pid, ulLength, ulName, ulParam, ucMode)
#define Mm_StopRelTimer(Pid, ulName, phTm) \
        NAS_StopRelTimer(Pid, ulName, phTm)


typedef VOS_UINT8 MM_REG_STATE_TYPE;
#define MM_REG_NOT_REGISTERED_NOT_SEARCH   0                /* 未注册，未启动搜索 PLMN，但用户可以启动注册，允许服务 */
#define MM_REG_REGISTERED_HOME_NETWORK     1                /* 注册，注册在 HOME PLMN */
#define MM_REG_NOT_REGISTERED_SEARCHING    2                /* 未注册，正在搜索PLMN或者正在附着过程 */
#define MM_REG_REGISTERED_DENIED           3                /* 注册被拒绝，当前用户不可以启动注册，启动服务被禁止 */
#define MM_REG_UNKNOWN                     4                /* 其余情况 */
#define MM_REG_REGISTERED_ROAM             5                /* 注册，注册在非 HOME PLMN */

typedef VOS_UINT8 MM_SUSPEND_CAUSE;
#define MM_SUSPEND_FOR_HANDOVER         0                   /* 发生的异系统切换时，MM 有业务存在 */
#define MM_SUSPEND_FOR_RESELECT         1                   /* 发生的异系统切换时，MM 空闲，无业务 */
#define MM_INVALID_SUSPEND_CAUSE        2                   /* 无效切换原因 */

#define MM_PAGING_PLMNSRCH_FALSE        0
#define MM_PAGING_PLMNSRCH_TRUE         1

#define MM_UPDATED_SPECIFIC_PROCEDURE        0
#define MM_NOT_UPDATED_SPECIFIC_PROCEDURE    1

typedef struct
{
#define     MM_STATUS_ATTACHED                          0                       /* attached                                 */
#define     MM_STATUS_DETACHED                          1                       /* detached                                 */
    VOS_UINT8                               ucCsAttachState;                        /* attach状态                               */

#define     MM_UPDATE_STATUS_U1                         0                       /* U1                                       */
#define     MM_UPDATE_STATUS_U2                         1                       /* U2                                       */
#define     MM_UPDATE_STATUS_PLMN_NOT_ALLOWED           2                       /* U3                                       */
#define     MM_UPDATE_STATUS_LA_NOT_ALLOWED             3                       /* U3                                       */
#define     MM_UPDATE_STATUS_U3     MM_UPDATE_STATUS_LA_NOT_ALLOWED             /* U3                                       */

    VOS_UINT8                               ucUpdateSts;                            /* 更新状态                                 */

#define     MM_SPECIFIC_ON                              0                       /* GMM不能作detach                          */
#define     MM_SPECIFIC_OFF                             1                       /* GMM能作detach                            */
    VOS_UINT8                               ucCsSpecificFlg;

    VOS_UINT8                                  MmSuspendEvent;
    VOS_UINT8                                  ucPagingPlmnSrch;
    VOS_UINT8                                   ucSpecProFlg;                       /*MM是否成功进行过专有过程标志*/
    NAS_MML_RRC_INTEGRITY_PROTECT_ENUM_UINT8    ucCsIntegrityProtect;

    VOS_UINT8                           ucReserve;
}MM_SHARE_STRU;

typedef VOS_UINT8 GMM_REG_STATE_TYPE;
#define GMM_REG_NOT_REGISTERED_NOT_SEARCH   0                /* 未注册，未启动搜索 PLMN，但用户可以启动注册，允许服务 */
#define GMM_REG_REGISTERED_HOME_NETWORK     1                /* 注册，注册在 HOME PLMN */
#define GMM_REG_NOT_REGISTERED_SEARCHING    2                /* 未注册，正在搜索PLMN或者正在附着过程 */
#define GMM_REG_REGISTERED_DENIED           3                /* 注册被拒绝，当前用户不可以启动注册，启动服务被禁止 */
#define GMM_REG_UNKNOWN                     4                /* 其余情况 */
#define GMM_REG_REGISTERED_ROAM             5                /* 注册，注册在非 HOME PLMN */

typedef struct
{
#define     GMM_STATUS_DETACHED                               0                 /* detached                                 */
#define     GMM_STATUS_ATTACHED                               1                 /* attached                                 */
    VOS_UINT8                               ucAttachSta;                        /* attach状态                               */

#define     GMM_DETACH_DISABLE                               0                  /* GMM不能作detach                          */
#define     GMM_DETACH_ABLE                                  1                  /* GMM能作detach                            */
    VOS_UINT8                               ucDeatchEnableFlg;                  /* 是否能作detach标志                       */
#define     GMM_SPECIFIC_ON                                   0                 /* GMM不能作detach                          */
#define     GMM_SPECIFIC_OFF                                  1                 /* GMM能作detach                            */
    VOS_UINT8                               ucPsSpecificFlg;

    VOS_UINT8                ucGsAssociationFlg;                                /* 当前是否存在Gs关联，0：不存在， 1:存在 */
    NAS_MML_RRC_INTEGRITY_PROTECT_ENUM_UINT8   ucPsIntegrityProtect;
    VOS_UINT8                           aucReserve[3];
}GMM_SHARE_STRU;

/*typedef struct
{
    MMC_SHARE_STRU  MmcShare;
    MM_SHARE_STRU   MmShare;
    GMM_SHARE_STRU  GmmShare;
}MM_SUB_LAYER_SHARE_STRU;*/

/*网络状态定义*/
typedef enum
{
    MMC_NET_TYPE_GSM_ENUM = 0,
    MMC_NET_TYPE_WCDMA_ENUM,
    MMC_NET_TYPE_BUTT,
}MMC_NET_TYPE_ENUM;


/*MMC挂起前状态*/
typedef struct
{
    MM_PLMN_ID_STRU                     stPlmn;
    VOS_UINT8                           aucMsgBuf[71];      /*发送挂起之前缓
                                                              存消息，用于挂
                                                              起后继续执行该
                                                              消息*/
    VOS_UINT8                           ucPlmnFlg;          /*取值为MMC_TRUE 或 MMC_FALSE，表示当前plmn可用与否*/
}MMC_PLMN_INFO_ST;




/* 对原有数据结构 MM_SUB_LAYER_SHARE_STRU 重新进行了定义,该数据结构的定义在MM_Share.h文件中 */
typedef struct
{
    MM_SHARE_STRU                       MmShare;              /* 原有数据成员                      */
    GMM_SHARE_STRU                      GmmShare;             /* 原有数据成员                      */
    MM_SUSPEND_SHARE_STRU               MmSuspendShare; /* 为MM与GMM挂起状态新增全局变量结构 */
  }MM_SUB_LAYER_SHARE_STRU;

typedef struct
{
    VOS_UINT32                          ulNasMsgSize;
    VOS_UINT8                           aucNasMsg[255];
}NAS_MSG_FOR_PCLINT_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  ulCnDomainId;
    NAS_MSG_FOR_PCLINT_STRU             RcvNasMsg;
}RRMM_DATA_IND_FOR_PCLINT_STRU;

typedef struct
{
    MSG_HEADER_STRU              MsgHeader;
    VOS_UINT32                   ulTi;
    NAS_MSG_FOR_PCLINT_STRU      SmsMsg;
}MMSMS_DATA_IND_FOR_PCLINT_STRU;

#define AUTHENTICATION_REQ_UMTS_CHALLENGE           0
#define AUTHENTICATION_REQ_GSM_CHALLENGE            1

#define     GMM_PROCEDURE_SRCHPLMN_SUCCESS     0x00
#define     GMM_PROCEDURE_SRCHPLMN_FAILURE     0x01
#define     GMM_PROCEDURE_ATTACH_SUCCESS       0x02
#define     GMM_PROCEDURE_ATTACH_FAILURE       0x03
#define     GMM_PROCEDURE_SERVICE_SUCCESS      0x04
#define     GMM_PROCEDURE_SERVICE_FAILURE      0x05
#define     GMM_PROCEDURE_RAU_SUCCESS          0x06
#define     GMM_PROCEDURE_RAU_FAILURE          0x07
#define     GMM_PROCEDURE_PTMSI_RELOC          0x08
#define     GMM_PROCEDURE_DETACH_OVER          0x09
#define     VOS_RELATIVE_TIMER                 0x02

#define     MM_AUTH_PRO                             0x0
#define     MM_LAU_SUCCESS                          0x1
#define     MM_LAU_FAILURE                          0x2
#define     MM_SERVICE_SUCCESS                      0x5
#define     MM_SERVICE_FAILURE                      0x6
#define     MM_TMSI_RELOC                           0x7
#define     MM_DETACH_COMPLETE                      0x8

#define     RRC_NAS_MASK_NULL           0x0000
#define     RRC_NAS_MASK_ATTACH         0x0001
#define     RRC_NAS_MASK_USIM_INVALID   0x0002
#define     RRC_NAS_MASK_SECURITY_KEY   0x0004
#define     RRC_NAS_MASK_DRX            0x0008
#define     RRC_NAS_MASK_TMSI_LAI       0x0010
#define     RRC_NAS_MASK_PTMSI_RAI      0x0020
#define     RRC_NAS_MASK_DEL_KEY        0x0040
#define     RRC_NAS_MASK_GSM_GMM_STATE  0x0080  /* GSM网络下GMM状态信息有效标志 */
#define     RRC_NAS_MASK_READY_TIMER    0x0100  /* READY TIMER值有效标志        */
#define     RRC_NAS_MASK_MS_GPRS_MODE   0x0200  /* MS GPRS模式值有效标志 */
#define     RRC_NAS_MASK_MAPPED_SECURITY_KEY 0x0400


#define     RRC_NAS_MASK_SYNC_WRR       ( (RRC_NAS_MASK_ATTACH) | (RRC_NAS_MASK_PTMSI_RAI) )


#define     RRC_NAS_MASK_SYNC_GAS     ((RRC_NAS_MASK_ATTACH) | (RRC_NAS_MASK_DRX)                  \
                                      | (RRC_NAS_MASK_PTMSI_RAI) | (RRC_NAS_MASK_GSM_GMM_STATE)     \
                                      | (RRC_NAS_MASK_READY_TIMER) | (RRC_NAS_MASK_MS_GPRS_MODE))



#define     RRC_NAS_SYS_MSK_PLMN        0x0001
#define     RRC_NAS_SYS_MSK_CS_DRX      0x0002
#define     RRC_NAS_SYS_MSK_PS_DRX      0x0004
#define     RRC_NAS_SYS_MSK_CSPS_INFO   0x0008

#define     MM_LOCK_SUCCESS       WUEPS_SEMAPHORE_LOCK_SUCCESS                  /* 加锁成功                                 */
#define     MM_LOCK_FAILURE       WUEPS_SEMAPHORE_LOCK_FAILURE                  /* 加锁失败                                 */
#define     MM_UNLOCK_SUCCESS     WUEPS_SEMAPHORE_UNLOCK_SUCCESS                /* 解锁成功                                 */
#define     MM_UNLOCK_FAILURE     WUEPS_SEMAPHORE_UNLOCK_FAILURE                /* 解锁失败                                 */

#define EVT_NAS_MM_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY   0xaaaa          /* 为PC工程回放定义的消息 */

/*****************************************************************************
 Structure      : NAS_MM_OUTSIDE_RUNNING_CONTEXT_ST
 Description    : PC回放工程，存储所有MM相关的全局变量
 Message origin :
*****************************************************************************/

typedef struct
{
    VOS_UINT8                               pc_gucMmProcessFlg;
    VOS_UINT8                               pc_g_T3211Flag;
    MM_NSD_INFO_ST                          pc_g_stMmNsd;

    MM_GLOBAL_CTRL_STRU                     pc_g_MmGlobalInfo;

    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, begin */
    MM_TIMER_STRU                           pc_gstMmTimer[MM_TIMER_MAX];
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, end */
} NAS_MM_OUTSIDE_RUNNING_CONTEXT_ST;

/*****************************************************************************
 Structure      : NAS_MM_OUTSIDE_RUNNING_CONTEXT_ST
 Description    : PC回放工程，所有MM相关的全局变量通过以下消息结构发送
 Message origin :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                           ulMsgID;
    NAS_MM_OUTSIDE_RUNNING_CONTEXT_ST    stOutsideCtx;
}NAS_MM_SDT_MSG_ST;


#define EVT_NAS_GMM_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY   0xaaaa          /* 为PC工程回放定义的消息 */

/*****************************************************************************
 枚举名    : NAS_MM_LOG_OM_INFO_ENUM
 结构说明  : 可维可测消息id
 1.日    期   : 2012年3月17日
   作    者   : z00161729
   修改内容   : 新建结构
*****************************************************************************/
enum NAS_MM_LOG_OM_INFO_ENUM
{
    NAS_MM_LOG_TIN_TYPE_INFO_IND       = 0xa00,
    NAS_MM_LOG_BUTT
};
typedef VOS_UINT32 NAS_MM_LOG_OM_INFO_ENUM_UINT32;

/*****************************************************************************
 结构名    : NAS_MM_LOG_TIN_INFO_STRU
 结构说明  : MM TIN值更新时通知om勾消息，可维可测使用
  1.日    期   : 2012年3月17日
    作    者   : z00161729
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;                              /* TIN类型 */
    VOS_UINT8                           aucReserve[3];
}NAS_MM_LOG_TIN_INFO_STRU;




/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_UINT32 Mm_AtTest_GetGprsState(MM_TEST_AT_RSLT_STRU *pstAtCmdRslt);
extern VOS_UINT32 Mm_AtTest_GetGmmState(MM_TEST_AT_RSLT_STRU *pstAtCmdRslt);
extern VOS_UINT32 Mm_AtTest_GetMmState(MM_TEST_AT_RSLT_STRU *pstAtCmdRslt);
extern VOS_UINT32 Mm_AtTest_GetMmRegState(MM_TEST_AT_RSLT_STRU *pstAtCmdRslt);
extern VOS_UINT32 Mm_AtTest_GetGmmRegState(MM_TEST_AT_RSLT_STRU *pstAtCmdRslt);
extern VOS_UINT32 Mm_AtTest_SetPlmnSearchMode(VOS_UINT32 ulPlmnSearchMode);
extern VOS_UINT32 Mm_AtTest_SetRatMode(VOS_UINT32 ulRatMode);
VOS_UINT32 Mm_AtTest_SetOriginalRejectCause(
    VOS_UINT32                          ulOriginalUeCause
);
extern VOS_UINT32 Gmm_GetState(VOS_VOID);
extern VOS_UINT32 Gmm_GetGprsState(VOS_VOID);

extern VOS_UINT32 Mm_GetState(VOS_VOID);

extern VOS_UINT32 Mm_AtTest(VOS_VOID *pInput,VOS_VOID *pRslt);

extern VOS_VOID Mm_FillNasMmInfo(NAS_OM_MM_CONFIRM_STRU *pMsg);
extern VOS_VOID Gmm_FillNasMmInfo(NAS_OM_MM_CONFIRM_STRU *pMsg);
extern VOS_VOID Mmc_FillNasMmInfo(NAS_OM_MM_CONFIRM_STRU *pMsg);
extern VOS_VOID Mm_OmQuery(VOS_VOID *pMsg);
/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
/* Deleted Mm_TranslateNtwkName2Str */
/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */
extern VOS_UINT8 NAS_MM_GetMncLenFromBCCHMnc(
    VOS_UINT32                          ulBcchMnc
);

extern VOS_VOID NAS_MM_SndOutsideContextData(VOS_VOID);
extern VOS_VOID NAS_GMM_SndOutsideContextData(VOS_VOID);
extern VOS_INT8 NAS_Common_Get_Supported_3GPP_Version(VOS_UINT32 ulCnDomainId);
extern VOS_UINT32 NAS_MMC_IsRoam();
extern VOS_VOID MMC_ComGetRatType(VOS_UINT8 *pucRatType);

extern VOS_BOOL NAS_MM_NeedSendEPlmnConnFail(VOS_VOID);

extern VOS_UINT8 NAS_MM_CheckIfMmIsEstablishRRConnection(VOS_VOID);

extern VOS_VOID NAS_MM_HandleGmmCauseValAsLuAccept(VOS_VOID);

extern VOS_VOID NAS_MM_UpdateCsServiceConnStatusFlg(VOS_VOID);

extern VOS_VOID NAS_MM_UpdateCsServiceBufferStatusFlg(VOS_VOID);

VOS_UINT32 NAS_MM_IsGURplmnChanged(
    NAS_MML_PLMN_ID_STRU               *pstRPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat
);

VOS_VOID NAS_MM_WriteRplmnWithRatNvim(
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo
);

VOS_VOID NAS_MM_GenerateEPlmnInfo(
    VOS_UINT32                          ulLauAcceptPlmnNum,
    MM_PLMN_ID_STRU                    *pstLauAcceptPlmnList,
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
);

VOS_VOID NAS_MM_WriteEplmnNvim(
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnAddr
);

extern VOS_VOID NAS_MM_UpdateEquPlmnInfo(
    VOS_UINT32                          ulCause
);


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

#endif /* MMSHARE_H */
