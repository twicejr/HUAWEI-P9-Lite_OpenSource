/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasGmmSndOm.h
  版 本 号   : 初稿
  作    者   : l00171473
  生成日期   : 2012年8月21日
  最近修改   :
  功能描述   : 定义GMM发送给OM的消息处理头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年8月21日
    作    者   : l00171473
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_GMM_SND_OM_H
#define _NAS_GMM_SND_OM_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "PsTypeDef.h"

#include "NasUtranCtrlInterface.h"

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
 枚举名    : NAS_GMM_OM_MSG_ID_ENUM_U32
 结构说明  : MM发送给OM的可维可测消息
  1.日    期   : 2012年8月21日
    作    者   : l00171473
    修改内容   : MM发送给OM的可维可测消息ID枚举
  2.日    期   : 2014年2月27日
    作    者   : w00242748
    修改内容   : 调用GAS接口获取UE能力
*****************************************************************************/
enum NAS_GMM_OM_MSG_ID_ENUM
{
    /* MM发送给OM的消息 */
    GMMOM_LOG_STATE_INFO_IND                       = 0x1000,      /*_H2ASN_MsgChoice  NAS_GMM_LOG_STATE_INFO_STRU */
    GMMOM_LOG_AUTH_INFO_IND                        = 0x1001,      /*_H2ASN_MsgChoice  NAS_GMM_LOG_AUTH_INFO_STRU */
    GMMOM_LOG_RADIAO_ACCESS_CAP                    = 0x1002,      /*_H2ASN_MsgChoice  NAS_GMM_LOG_GAS_RADIO_ACCESS_CAP_STRU */

    GMMOM_LOG_CTX_INFO_IND                         = 0x1003,      /*_H2ASN_MsgChoice  GMMOM_LOG_CTX_INFO_STRU */
    GMMOM_LOG_BUTT
};
typedef VOS_UINT32 NAS_GMM_OM_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_GMM_STATE_ID_ENUM_UINT32
 枚举说明  : MM状态ID枚举定义
 1.日    期   : 2012年8月21日
   作    者   : L00171473
   修改内容   : 新建
 2.日    期   : 2012年8月21日
   作    者   : L00171473
   修改内容   : V7R1C50_At_Abort, ASN解析调整
*****************************************************************************/
enum NAS_GMM_STATE_ID_ENUM
{
    STATE_GMM_ID_NULL                                     =  0x00,              /* GMM_NULL状态                             */
    STATE_GMM_REGISTERED_INITIATED                        =  0x01,              /* GMM-REGISTERED-INITIATED状态             */
    STATE_GMM_DEREGISTERED_INITIATED                      =  0x02,              /* GMM_DEREGISTERED_INITIATED               */
    STATE_GMM_ROUTING_AREA_UPDATING_INITIATED             =  0x03,              /* GMM_ROUTING_AREA_UPDATING_INITIATED      */
    STATE_GMM_SERVICE_REQUEST_INITIATED                   =  0x04,              /* GMM-SERVICE-REQUEST-INITIATED            */

    STATE_GMM_TC_ACTIVE                                   =  0x05,              /* GMM-TC-ACTIVE(进行TC时的状态)            */
    STATE_GMM_GPRS_SUSPENSION                             =  0x06,              /* (GSM only)GMM_GPRS_SUSPENSION */

    STATE_GMM_DEREGISTERED_NORMAL_SERVICE                 =  0x10,              /* GMM-DEREGISTERED.NORMAL-SERVICE          */
    STATE_GMM_DEREGISTERED_LIMITED_SERVICE                =  0x11,              /* GMM-DEREGISTERED.LIMITED-SERVICE         */
    STATE_GMM_DEREGISTERED_ATTACH_NEEDED                  =  0x12,              /* GMM-DEREGISTERED.ATTACH-NEEDED           */
    STATE_GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH           =  0x13,              /* GMM-DEREGISTERED.ATTEMPTING-TO-ATTACH    */
    STATE_GMM_DEREGISTERED_NO_CELL_AVAILABLE              =  0x14,              /* GMM-DEREGISTERED.NO-CELL-AVAILABLE       */
    STATE_GMM_DEREGISTERED_PLMN_SEARCH                    =  0x15,              /* GMM-DEREGISTERED.PLMN-SEARCH             */
    STATE_GMM_DEREGISTERED_NO_IMSI                        =  0x16,              /* GMM-DEREGISTERED.NO-IMSI                 */

    STATE_GMM_REGISTERED_NORMAL_SERVICE                   =  0x20,              /* GMM-REGISTERED.NORMAL-SERVICE            */
    STATE_GMM_REGISTERED_LIMITED_SERVICE                  =  0x21,              /* GMM-REGISTERED.LIMITED-SERVICE           */
    STATE_GMM_REGISTERED_UPDATE_NEEDED                    =  0x22,              /* GMM-REGISTERED.UPDATE-NEEDED             */
    STATE_GMM_REGISTERED_ATTEMPTING_TO_UPDATE             =  0x23,              /* GMM-REGISTERED.ATTEMPTING-TO-UPDATE      */
    STATE_GMM_REGISTERED_NO_CELL_AVAILABLE                =  0x24,              /* GMM-REGISTERED.NO-CELL-AVAILABLE         */
    STATE_GMM_REGISTERED_PLMN_SEARCH                      =  0x25,              /* GMM-REGISTERED.PLMN-SEARCH               */
    STATE_GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM          =  0x26,              /* GMM-REGISTERED.ATTEMPTING-TO-UPDATE-MM   */
    STATE_GMM_REGISTERED_IMSI_DETACH_INITIATED            =  0x27,              /* GMM-REGISTERED.IMSI-DETACH-INITIATED     */

    STATE_GMM_SUSPENDED_NORMAL_SERVICE                    =  0x30,              /* GMM-SUSPENDED.NORMAL-SERVICE             */
    STATE_GMM_SUSPENDED_GPRS_SUSPENSION                   =  0x31,              /* GMM-SUSPENDED.GPRS-SUSPENSION            */
    STATE_GMM_SUSPENDED_WAIT_FOR_SYSINFO                  =  0x32,              /* GMM-SUSPENDED.WAIT-FOR-SYSINFO           */

    STATE_GMM_TYPE_BUTT
};
typedef VOS_UINT8 NAS_GMM_STATE_ID_ENUM_UINT8;

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
 结构名    : NAS_GMM_LOG_STATE_INFO_STRU
 结构说明  : 勾GMM的状态的结构

 修改记录  :
 1.日    期   : 2012年08月21日
   作    者   : l00171473
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头 */ /*_H2ASN_Skip*/

    NAS_GMM_STATE_ID_ENUM_UINT8         enGmmState;
    VOS_UINT8                           aucRsv3[3];
}NAS_GMM_LOG_STATE_INFO_STRU;

/*****************************************************************************
 结构名    : GMMOM_LOG_GMM_RAU_CTRL_INFO_STRU
 结构说明  : 勾GMM g_GmmRauCtrl全局变量相关信息

 修改记录  :
 1.日    期   : 2014年10月8日
   作    者   : z00161729
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucT3312ExpiredFlg; /* 记录g_GmmRauCtrl.ucT3312ExpiredFlg T3312定时器是否超时标识 */
    VOS_UINT8                           ucT3311ExpiredFlg; /* 记录g_GmmRauCtrl.ucT3311ExpiredFlg T3311是否超时标识 */
    VOS_UINT8                           aucReserved[2];
}GMMOM_LOG_GMM_RAU_CTRL_INFO_STRU;


/*****************************************************************************
 结构名    : GMMOM_LOG_GMM_REQ_CNF_MNG_INFO_STRU
 结构说明  : 勾GMM g_GmmReqCnfMng全局变量相关信息

 修改记录  :
 1.日    期   : 2014年10月8日
   作    者   : z00161729
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucCnfMask;     /* 记录g_GmmReqCnfMng.ucCnfMask*/
    VOS_UINT8                               aucReserved[3];
}GMMOM_LOG_GMM_REQ_CNF_MNG_INFO_STRU;


/*****************************************************************************
 结构名    : GMMOM_LOG_GMM_SERVICE_CTRL_INFO_STRU
 结构说明  : 勾GMM g_GmmServiceCtrl全局变量相关信息

 修改记录  :
 1.日    期   : 2014年10月8日
   作    者   : z00161729
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucRetrySrForRelCtrlFlg;     /* 记录g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg*/
    VOS_UINT8                               aucReserved[3];
}GMMOM_LOG_GMM_SERVICE_CTRL_INFO_STRU;



/*****************************************************************************
 结构名    : GMMOM_LOG_GMM_TIMER_MNG_INFO_STRU
 结构说明  : 勾GMM g_GmmTimerMng全局变量相关信息

 修改记录  :
 1.日    期   : 2014年10月8日
   作    者   : z00161729
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    VOS_UINT32                               ulTimerRunMask;     /* 记录g_GmmTimerMng.ulTimerRunMask*/
}GMMOM_LOG_GMM_TIMER_MNG_INFO_STRU;


/*****************************************************************************
 结构名    : GMMOM_LOG_GMM_SUSPEND_CTRL_INFO_STRU
 结构说明  : 勾GMM gstGmmSuspendCtrl相关全局变量信息

 修改记录  :
 1.日    期   : 2014年10月8日
   作    者   : z00161729
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPreRat;     /* 记录gstGmmSuspendCtrl.ucPreRat切换时接入技术 */
    VOS_UINT8                           ucT3312State; /* 记录gstGmmSuspendCtrl.ucT3312State T3312定时器运行状态 */
    VOS_UINT8                           ucNetModeChange; /*记录gstGmmSuspendCtrl.ucNetModeChange 异系统改变时网络模式改变的类型 */
    VOS_UINT8                           ucPreSrvState;   /* 记录gstGmmSuspendCtrl.ucPreSrvState*/
}GMMOM_LOG_GMM_SUSPEND_CTRL_INFO_STRU;

/*****************************************************************************
 结构名    : GMMOM_LOG_GMM_GLOBAL_CTRL_INFO_STRU
 结构说明  : 勾GMM g_GmmGlobalCtrl相关全局变量信息

 修改记录  :
 1.日    期   : 2014年10月8日
   作    者   : z00161729
   修改内容   : 新增
 2.日    期   : 2015年2月7日
   作    者   : b00269685
   修改内容   : at&t dam修改
 3.日    期   : 2015年6月15日
   作    者   : z00161729
   修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucPlmnSrchPreSta;        /* 记录搜网前的状态 */
    VOS_UINT8                                   ucSpecProc;              /* 记录g_GmmGlobalCtrl.ucSpecProc当前gmm的专有流程 */
    VOS_UINT8                                   UeInfo_UeId_ucUeIdMask;  /* 记录g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask UeId存在标识 */
    VOS_UINT8                                   CsInfo_ucCsTransFlg;     /* 记录g_GmmGlobalCtrl.CsInfo.ucCsTransFlg CS域是否通信中标志*/
    VOS_UINT8                                   ucSigConFlg;             /* 记录g_GmmGlobalCtrl.ucSigConFlg*/
    VOS_UINT8                                   ucRaiChgRelFlg;          /* 记录g_GmmGlobalCtrl.ucRaiChgRelFlg*/
    VOS_UINT8                                   SysInfo_ucNetMod;        /* 记录g_GmmGlobalCtrl.SysInfo.ucNetMod*/
    VOS_UINT8                                   ucCvrgAreaLostFlg;       /* 记录g_GmmGlobalCtrl.ucCvrgAreaLostFlg*/
    VOS_UINT8                                   ucDetachType;            /* 记录g_GmmGlobalCtrl.stDetachInfo.enDetachType*/
    VOS_UINT8                                   ucRelCause;              /*记录g_GmmGlobalCtrl.ucRelCause*/
    VOS_UINT8                                   ucSpecProcInCsTrans;     /*记录g_GmmGlobalCtrl.ucSpecProcInCsTrans*/
    VOS_UINT8                                   SysInfo_ucCellChgFlg;    /*记录g_GmmGlobalCtrl.SysInfo.ucCellChgFlg*/
    VOS_UINT8                                   UeInfo_ucMsRadioCapSupportLteFromAs; /*记录g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs*/
    GMM_RAI_STRU                                SysInfo_Rai;             /* 记录g_GmmGlobalCtrl.SysInfo.Rai*/
    VOS_UINT8                                   UeInfo_ucMsRadioCapSupportLteFromRegReq; /*记录g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromRegReq*/
    NAS_MML_RAI_STRU                            stAttemptToUpdateRai;    /* 记录GMM迁到ATTEMPT TO UPDATE状态且update status迁到2时的RAI信息 */
    NAS_MML_VOICE_DOMAIN_PREFERENCE_ENUM_UINT8  UeInfo_enVoiceDomainFromRegRq; /* 记录g_GmmGlobalCtrl.UeInfo.enVoiceDomainFromRegReq */
    VOS_UINT8                                   aucReserved[3];

    NAS_MML_PLMN_WITH_RAT_STRU                  stAllocT3302ValuePlmnWithRat; /* g_GmmGlobalCtrl.stAllocT3302ValuePlmnWithRat*/
}GMMOM_LOG_GMM_GLOBAL_CTRL_INFO_STRU;

/*****************************************************************************
 结构名    : GMMOM_LOG_GMM_ATTACH_CTRL_INFO_STRU
 结构说明  : 勾GMM GmmAttachCtrl相关全局变量信息

 修改记录  :
 1.日    期   : 2014年10月8日
   作    者   : z00161729
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRetryAttachForRelCtrlFlg;     /* 记录GmmAttachCtrl.ucRetryAttachForRelCtrlFlg Attach流程被异常释放，需要在收到系统消息后重新发起 */
    VOS_UINT8                           ucRetryFlg;                     /*记录g_GmmAttachCtrl.ucRetryFlg*/
    VOS_UINT8                           ucAttachAttmptCnt;              /*记录g_GmmAttachCtrl.ucAttachAttmptCnt*/
    VOS_UINT8                           ucReserved;
}GMMOM_LOG_GMM_ATTACH_CTRL_INFO_STRU;

/*****************************************************************************
 结构名    : GMMOM_LOG_GMM_CAS_GLOBAL_CTRL_INFO_STRU
 结构说明  : 勾GMM gstGmmCasGlobalCtrl相关全局变量信息

 修改记录  :
 1.日    期   : 2014年10月8日
   作    者   : z00161729
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    VOS_UINT8               ucLastDataSender;            /*记录gstGmmCasGlobalCtrl.ucLastDataSender*/
    VOS_UINT8               ucSuspendLlcCause;           /*记录gstGmmCasGlobalCtrl.ucSuspendLlcCause*/
    VOS_UINT8               ucTlliAssignFlg;             /*记录gstGmmCasGlobalCtrl.ucTlliAssignFlg*/
    VOS_UINT8               ucReserved;
}GMMOM_LOG_GMM_CAS_GLOBAL_CTRL_INFO_STRU;

/*****************************************************************************
 结构名    : GMMOM_LOG_MML_CTX_INFO_STRU
 结构说明  : 勾mml相关全局变量信息

 修改记录  :
 1.日    期   : 2014年10月8日
   作    者   : z00161729
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    NAS_MML_TIN_TYPE_ENUM_UINT8              enTinType;     /* 记录NAS_MML_GetTinType TIN类型 */
    VOS_UINT8                                ucT3423State;  /* 记录NAS_MML_GetT3423Status T3423定时器运行状态 */
    VOS_UINT8                                ucPsRegStatus; /* 记录NAS_MML_GetSimPsRegStatus PS域的SIM卡注册信息*/
    VOS_UINT8                                ucWSysInfoDrxLen; /*记录NAS_MML_GetWSysInfoDrxLen*/
    NAS_MML_RAI_STRU                         stPsLastSuccRai;  /*记录NAS_MML_GetPsLastSuccRai*/
    NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8 enPsUpdateStatus; /*记录NAS_MML_GetPsUpdateStatus*/
    VOS_UINT8                                ucPsServiceBufferStatusFlg; /*记录NAS_MML_GetPsServiceBufferStatusFlg*/
    NAS_MML_MS_MODE_ENUM_UINT8               enMsMode;         /*记录NAS_MML_GetMsMode*/
    VOS_UINT8                                ucIsTmsiValid;    /*记录NAS_MML_IsTmsiValid*/
    NAS_MML_PS_BEARER_CONTEXT_STRU           astPsBearerContext[NAS_MML_MAX_PS_BEARER_NUM];  /* 记录NAS_MML_GetPsBearerCtx */
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8      enCurrUtranMode;  /*记录NAS_UTRANCTRL_GetCurrUtranMode*/
    VOS_UINT8                                aucReserved[3];
}GMMOM_LOG_MML_CTX_INFO_STRU;

/*****************************************************************************
 结构名    : GMMOM_LOG_MM_SUBLYR_SHARE_GMM_SHARE_INFO_STRU
 结构说明  : 勾g_MmSubLyrShare.GmmShare相关全局变量信息

 修改记录  :
 1.日    期   : 2014年10月8日
   作    者   : z00161729
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    VOS_UINT8               GmmShare_ucGsAssociationFlg;            /*记录g_MmSubLyrShare.GmmShare.ucGsAssociationFlg*/
    VOS_UINT8               aucReserved[3];
}GMMOM_LOG_MM_SUB_LYR_SHARE_INFO_STRU;

/*****************************************************************************
 结构名    : GMMOM_LOG_CTX_INFO_STRU
 结构说明  : 勾GMM的全局变量的结构

 修改记录  :
 1.日    期   : 2014年10月8日
   作    者   : z00161729
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                          stMsgHeader;/* 消息头 */ /*_H2ASN_Skip*/

    GMMOM_LOG_GMM_SUSPEND_CTRL_INFO_STRU     stGmmSuspendCtrlInfo;
    GMMOM_LOG_GMM_RAU_CTRL_INFO_STRU         stGmmRauCtrlInfo;
    GMMOM_LOG_GMM_GLOBAL_CTRL_INFO_STRU      stGmmGlobalCtrlInfo;
    GMMOM_LOG_GMM_CAS_GLOBAL_CTRL_INFO_STRU  stGmmGasGlobalCtrlInfo;
    GMMOM_LOG_GMM_REQ_CNF_MNG_INFO_STRU      stGmmReqCnfMngInfo;
    GMMOM_LOG_GMM_SERVICE_CTRL_INFO_STRU     stGmmServiceCtrlInfo;
    GMMOM_LOG_GMM_TIMER_MNG_INFO_STRU        stGmmTimerMngInfo;
    GMMOM_LOG_MML_CTX_INFO_STRU              stMmlCtxInfo;
    GMMOM_LOG_MM_SUB_LYR_SHARE_INFO_STRU     stMmSubLyrShareInfo;
}GMMOM_LOG_CTX_INFO_STRU;




/*****************************************************************************
 结构名    : NAS_GMM_LOG_GAS_RADIO_ACCESS_CAP_STRU
 结构说明  : 勾GMM调用GAS接口获取的数据值

 修改记录  :
 1.日    期   : 2014年2月27日
   作    者   : w0024274
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头 */ /*_H2ASN_Skip*/

    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucMsCapType;
    VOS_UINT8                           ucRsv;
    VOS_UINT16                          usSize;
    VOS_UINT8                           aucData[MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE];
}NAS_GMM_LOG_GAS_RADIO_ACCESS_CAP_STRU;


/*****************************************************************************
 ???    : NAS_GMM_LOG_AUTH_INFO_STRU
 ????  : ?????GMM???????

 ????  :
 1.?    ?   : 2013?11?30?
   ?    ?   : l65478
   ????   : ??

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* ??? */ /*_H2ASN_Skip*/
    VOS_UINT8                           ucExpectOpId;
    VOS_UINT8                           ucRcvOpId;
    VOS_UINT8                           aucRsv[2];
}NAS_GMM_LOG_AUTH_INFO_STRU;


/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    NAS_GMM_OM_MSG_ID_ENUM_UINT32       enMsgID;    /*_H2ASN_MsgChoice_Export NAS_GMM_OM_MSG_ID_ENUM_UINT32*/

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_GMM_OM_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}NAS_GMM_SND_OM_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    NAS_GMM_SND_OM_MSG_DATA             stMsgData;
}NasGmmSndOm_MSG;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_VOID  NAS_GMM_LogGmmStateInfo(
    VOS_UINT8                           ucGmmState
);

extern VOS_VOID  NAS_GMM_LogGmmCtxInfo(VOS_VOID);

extern VOS_VOID NAS_GMM_LogGasGmmRadioAccessCapability(
    VOS_UINT32                          ulRst,
    VOS_UINT8                           ucMsCapType,
    VOS_UINT16                          usSize,
    VOS_UINT8                          *pucData
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

#endif


