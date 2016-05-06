/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : Extern.h
  Description :
  History     :
      1.  张志勇   2003.11.27   新版作成
      2.  张志勇   2005.03.15   将()替换成(VOS_VOID)
      3.  s46746   2005.11.08   修改
      4. s46746    2006-03-29   根据问题单A32D02486修改
      5. s46746    2006-03-30   根据问题单A32D02606修改
      6. s46746    2006-04-20   根据问题单A32D03040修改
      7  x51137 2006/5/5 A32D03487
      8. s46746  2006-07-27 根据问题单A32D03975修改
      9.日    期   : 2006年10月6日
        作    者   : s46746
        修改内容   : 问题单号:A32D05960

      10.x51137 2006/11/3 A32D06511
      11.x51137 2006/11/3 A32D06821
      12.日    期   : 2006年11月6日
        作    者   : s46746
        修改内容   : 问题单号:A32D06442
      13.日    期   : 2006年11月23日
         作    者   : d49431
         修改内容   : 问题单号:A32D07452
      14.日    期   : 2007年03月09日
         作    者   : luojian id:60022475
         修改内容   : 根据问题单A32D09099修改
      15.日    期   : 2007年03月29日
         作    者   : luojian id:60022475
         修改内容   : 根据问题单A32D09756修改
      16.日    期   : 2007年06月01日
         作    者   : luojian id:60022475
         修改内容   : 根据问题单A32D10964修改
      17.日    期   : 2007年9月29日
         作    者   : luojian id:107747
         修改内容   : 根据问题单号：A32D12966,增加部分状态对RRMM_REL_IND的处理
      18.日    期   : 2007年10月06日
         作    者   : l65478
         修改内容   : 问题单号：A32D12977
      19.日    期   : 2007年12月11日
         作    者   : s46746
         修改内容   : 根据问题单号：A32D13845,出服务区后，MMC立即启动异系统相同PLMN
                      搜索
      20.日    期   : 2008年5月27日
         作    者   : s46746
         修改内容   : 问题单号:AT2D03209,增加列表搜索时响应寻呼处理
      21.日    期   : 2008年8月22日
         作    者   : o00132663
         修改内容   : 问题单号:AT2D05008,增加函数 Mm_Cell_S4_E31
      22.日    期   : 2008年12月2日
         作    者   : s62952
         修改内容   : 问题单号:AT2D07110

      23.日    期   : 2009年07月24日
        作    者   : z40661
        修改内容   : 异系统重选后，紧急呼叫不能接通
      24.日    期   : 2009年08月6日
        作    者   : l65478
        修改内容   : 问题单号：AT2D13610，测试GCF用例26.7.4.3.1失败，原因是在重选到原来的小区后发起了LAU

*******************************************************************************/

#ifndef __MM_EXT_H__
#define __MM_EXT_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "MM_Message.h"
#include "Nasrrcinterface.h"
#include "MmCcInterface.h"
#include "SmsMmInterface.h"
#include "GmmMmInterface.h"
#include "UsimPsInterface.h"
#include "MM_Share.h"

/* Added by l00208543 STK升级 2013-07-23 begin */
#include "NasStkInterface.h"
/* Added by l00208543 STK升级 2013-07-23 end */

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, begin */
#if (FEATURE_ON == FEATURE_LTE)
#include "MmLmmInterface.h"
#endif
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, end */
/* Added by w00176964 for V3R3C60_eCall项目, 2014-5-15, begin */
#include "MmSsInterface.h"
/* Added by w00176964 for V3R3C60_eCall项目, 2014-5-15, end */

#if (FEATURE_ON == FEATURE_PTM)
#include "NasErrorLog.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NAS_MM_GET_T3212_START_SCENE_CFG_TBL_PTR()          (g_astNasMmT3212StartSceneCfgTbl)
#define NAS_MM_GET_T3212_START_SCENE_CFG_TBL_SIZE()         (sizeof(g_astNasMmT3212StartSceneCfgTbl)/sizeof(NAS_MM_T3212_START_SCENE_CFG_TBL_STRU))
#define NAS_MM_T3212_START_SCENE_COUNTER_MAX_VALUE          (0XFFFFFFFF)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


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
typedef struct
{
    RRC_REL_CAUSE_ENUM_UINT32       enRrcRelCause;
    NAS_MMCM_REL_CAUSE_ENUM_UINT32  enMmCcRelCause;
}RRC_TO_MMCC_REL_CAUSE_STRU;

typedef struct
{
    RRC_NAS_EST_RESULT_ENUM_UINT32  enEstRslt;
    NAS_MMCM_REL_CAUSE_ENUM_UINT32  enMmCcRelCause;
}EST_RSLT_TO_MMCC_REL_CAUSE_STRU;

typedef struct
{
    MM_LMM_CSFB_SERVICE_RSLT_ENUM_UINT32    enCsfbRslt;
    NAS_MMCM_REL_CAUSE_ENUM_UINT32          enMmCcRelCause;
}CSFB_RSLT_TO_MMCC_REL_CAUSE_STRU;


/*****************************************************************************
 结构名    : NAS_MM_LAU_EST_CNF_TO_T3212_START_SCEAN_STRU
 结构说明  : LAU建联失败值转换为T3212启动场景配置表
  1.日    期   : 2015年3月14日
    作    者   : W00167002
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    RRC_NAS_EST_RESULT_ENUM_UINT32                          enEstRslt;
    NAS_MM_T3212_START_SCENE_ENUM_UINT32                    enT3212StartScene;
}NAS_MM_LAU_EST_CNF_TO_T3212_START_SCENE_STRU;


/*****************************************************************************
 结构名    : NAS_MM_T3212_START_SCEAN_CFG_TBL_STRU
 结构说明  : T3212启动场景控制BIT索引配置表，若改变，需要更新NV手册描述
  1.日    期   : 2015年3月14日
    作    者   : W00167002
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulT3212StartSceneCtrlBitIndex;
    NAS_MM_T3212_START_SCENE_ENUM_UINT32                    enT3212StartScene;
}NAS_MM_T3212_START_SCENE_CFG_TBL_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/




/* 老代码，待逐步清理 */


/* MMC发给MM的原语实体声明 */

/*extern MMCMM_START_REQ_STRU                    g_MmcMmStartReq;*/

/* CC发给MM的原语实体声明 */
extern MMCC_EST_REQ_ST                       g_MmCcEstReq;
extern MMCC_REL_REQ_ST                       g_MmCcRelReq;
extern MMCC_ABORT_REQ_ST                     g_MmCcAbortReq;
/*extern MMCC_DATA_REQ_ST                      g_MmCcDataReq;*/
extern MMCC_REEST_REQ_ST                     g_MmCcReestReq;
extern MMCC_PROMPT_REJ_ST                    g_MmCcPromptRej;


/* SS发给MM的原语实体声明 */
extern MMSS_EST_REQ_ST                       g_MmSsEstReq;
extern MMSS_REL_REQ_ST                       g_MmSsRelReq;
/*extern MMSS_DATA_REQ_STRU                      g_MmSsDataReq;*/
extern MMSS_ABORT_REQ_ST                     g_MmSsAbortReq;

/* SMS发给MM的原语实体声明 */
extern MMSMS_EST_REQ_ST                       g_MmSmsEstReq;
extern MMSMS_REL_REQ_ST                       g_MmSmsRelReq;
/*extern MMSMS_DATA_REQ_STRU                      g_MmSmsDataReq;*/
extern MMSMS_ABORT_REQ_ST                    g_MmSmsAbortReq;

/* RRC发给MM的原语实体声明 */
extern RRMM_SYNC_IND_ST                      g_RrMmSyncInd;

/* MM内部全局变量的外部声明 */
extern MM_GLOBAL_CTRL_STRU                     g_MmGlobalInfo;
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, begin */
extern MM_TIMER_STRU                           gstMmTimer[MM_TIMER_MAX];
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, end */

extern MM_SUB_LAYER_SHARE_STRU     g_MmSubLyrShare;

extern NAS_MM_IMPORTED_FUNC_LIST_STRU          g_NasMmImportFunc;

extern MM_NSD_INFO_ST                          g_stMmNsd;

extern VOS_UINT8     g_T3211Flag;

extern VOS_UINT8 gucMmProcessFlg;



/*****************************************************************************
  10 函数声明
*****************************************************************************/
/* MM实体函数声明 */
/* 发送公共处理声明 */
extern  VOS_VOID Mm_SndMmcInfoInd(VOS_VOID);
extern  VOS_VOID Mm_SndMmcCmSvcInd( VOS_UINT32 );
extern  VOS_VOID Mm_SndMmcCmSvcRejInd(VOS_UINT32);
extern  VOS_VOID Mm_SndMmcStartCnf(VOS_VOID);
/* Deleted by s00261364 for V3R360_eCall项目, 2014-4-11, begin */

/* Deleted by s00261364 for V3R360_eCall项目, 2014-4-11, end */
extern  VOS_VOID Mm_SndCcEstCnf(VOS_UINT32 , VOS_UINT32);
extern  VOS_VOID Mm_SndCcEstInd(VOS_UINT32, VOS_UINT32 , VOS_UINT8*);
extern  VOS_VOID Mm_SndCcRelInd(VOS_UINT32,VOS_UINT32);
extern  VOS_VOID Mm_SndCcDataInd(VOS_UINT32, VOS_UINT32, VOS_UINT8 *);
extern  VOS_VOID Mm_SndCcSyncInd(VOS_VOID);
extern  VOS_VOID Mm_SndCcReestCnf(VOS_UINT32, VOS_UINT32);
extern  VOS_VOID Mm_SndCcErrInd(
    VOS_UINT32                          ucTi,
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enCause
);

/* Added by n00355355 for 呼叫重建, 2015-9-17, begin */
VOS_VOID NAS_Mm_SndCcGetCallInfoReq(VOS_VOID);

/* Added by n00355355 for 呼叫重建, 2015-9-17, end */

extern VOS_VOID NAS_MM_SndMmcPlmnSearchInd(MM_MMC_PLMN_SEARCH_TYPE_ENUM_U32 enPlmnSearchType);
extern VOS_VOID NAS_MM_SndMmcCsfbAbortInd(VOS_VOID);


VOS_VOID Mm_SndCcEmergencyNumberList(NAS_MML_EMERGENCY_NUM_LIST_STRU *pEmergencyList);

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, begin */
#if (FEATURE_ON == FEATURE_IMS)
extern VOS_VOID NAS_MM_SndCcSrvccStatusInd(
    NAS_MMCC_SRVCC_STATUS_ENUM_UINT32   enSrvccSta
);
#endif
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, end */

extern  VOS_VOID Mm_SndRrEstReq(VOS_UINT32,VOS_UINT8,VOS_UINT32,VOS_UINT8*);
extern  VOS_VOID Mm_SndRrDataReq(VOS_UINT32,VOS_UINT8 *,VOS_UINT8);
extern  VOS_VOID Mm_SndRrRelReq(RRC_CELL_BAR_ENUM_UINT32  enBarValidFlg);


extern  VOS_VOID Mm_SndRrNasInfoChgReq(VOS_UINT32);


extern VOS_VOID NAS_MM_NotifyAsInfoChgReq(VOS_VOID);

extern VOS_VOID MM_SndMmcRrRelInd(VOS_UINT32 ulRelCause);
extern VOS_VOID NAS_MM_SndMmcResumeRsp(VOS_VOID);
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-22, begin */
extern VOS_VOID NAS_MM_SndMmcSuspendRsp(VOS_VOID);
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-22, end */
/* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-29, begin */

/* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-29, end */
extern  VOS_VOID Mm_ComAttachRejectCause2(VOS_VOID);
extern  VOS_VOID Mm_ComAuthenRcvAuthenRej(VOS_VOID);
extern  VOS_VOID Mm_ComAttachRejectCause3(VOS_VOID);
extern  VOS_VOID Mm_ComCheckDelayMmConn( VOS_UINT8 );
extern MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeMobileId(
    VOS_UINT16          *pusIndex,
    VOS_UINT8           *pucRcvMsg,
    VOS_UINT16          usMsgSize,
    VOS_UINT8           *pucMobileIdFlg,
    VOS_UINT8           *pucEventId);
extern MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeFollowOn(
    VOS_UINT16          *pusIndex,
    VOS_UINT8           *pucRcvMsg,
    VOS_UINT16          usMsgSize);
extern MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeEplmn(
    VOS_UINT16          *pusIndex,
    VOS_UINT8           *pucRcvMsg,
    VOS_UINT16          usMsgSize,
    VOS_UINT8           *pucEventId);
extern MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeCTS(
    VOS_UINT16          *pusIndex,
    VOS_UINT8           *pucRcvMsg,
    VOS_UINT16          usMsgSize);
extern MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeOtherOptionalIE(
    VOS_UINT16          *pusIndex,
    VOS_UINT8           *pucRcvMsg,
    VOS_UINT16          usMsgSize,
    VOS_UINT8           *pucEventId);

extern  VOS_UINT8 Mm_ComMsgLuAccptRcv ( VOS_UINT8*,VOS_UINT16 );
extern  VOS_UINT8 Mm_ComMsgLuRejctRcv ( VOS_UINT8*,VOS_UINT16 );

extern  VOS_UINT8 Mm_ComMsgSvcPromptRcv ( VOS_UINT8*,VOS_UINT16 );

extern  VOS_VOID Mm_ComCheckDelayDetach(VOS_VOID);
extern  VOS_UINT32 Mm_ComJudgeCsServExist(VOS_VOID);

/* 接收公共处理声明 */
extern  VOS_UINT8   Mm_RcvMmcStartReq( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvMmcReStartReq( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvMmcPlmnSrchIni( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvMmcPlmnUserSelReq( VOS_VOID* );
/* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-4, begin */
extern VOS_UINT8    NAS_MM_CheckMmcMmSysInfoIE( VOS_VOID* );
extern VOS_VOID     NAS_MM_UpdateNetworkInfo_GasSysInfo ( VOS_VOID* );
extern VOS_VOID     NAS_MM_UpdateNetworkInfo_WasSysInfo ( VOS_VOID* );
extern VOS_UINT8    NAS_MM_IsClassAAndNmoIMode(
    VOS_UINT8                               ucCurNtMod
);
/* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-4, end */
extern  VOS_UINT8   Mm_RcvGmmCombinedAttachIni( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvGmmCombinedAttachAccept( VOS_VOID* );
extern  VOS_UINT8   NAS_MM_RcvGmmCombinedAttachRej( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvGmmImsiDetechIni( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvGmmImsiDetechComplete( VOS_VOID* );
extern  VOS_UINT8   NAS_MM_RcvGmmNetworkDetechInd( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvGmmGmmActionResultInd( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvGmmAuthFailInd( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvGmmCombinedRauInitiation( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvGmmCombinedRauAccepted( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvGmmCombinedRauRejected( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvMmcInfoInd( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvMmcCoverageLostInd( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvCcEstReq( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvCcRelReq( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvCcAbortReq( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvCcDataReq( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvCcReestReq( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvRrcPagingInd( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvRrcEstCnf( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvRrcRelInd( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvRrcSecurityInd( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvRrcSyncInd( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvRrcDataInd_AuthReq( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvRrcDataInd_AuthRej( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvRrcDataInd_IdentityReq( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvRrcDataInd_TmsiReallocCmd( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvRrcDataInd_CmServiceAccept( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvRrcDataInd_CmServiceRej( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvRrcDataInd_FirstCmMsg( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvRrcDataInd_Abort( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvRrcDataInd_MmInfo( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvRrcDataInd_MmSta( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvAgntUsimStatusInd( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvAgntUsimReadFileCnf( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvAgntUsimAuthenticationCnf( VOS_VOID* );

extern  VOS_UINT8   Mm_RcvMmcAttachReq( VOS_VOID* );

extern  VOS_VOID   Mm_ComT3214orT3216Expired(VOS_VOID);
extern  VOS_VOID   Mm_ComT3218Expired(VOS_VOID);
extern  VOS_VOID   Mm_T3230Expire(VOS_VOID);
extern  VOS_VOID   Mm_T3240Expire(VOS_VOID);

extern  VOS_VOID Mm_SndAgentUsimStatusReq(VOS_VOID);
extern  VOS_VOID Mm_SndAgentUsimReadFileReq(VOS_UINT16);
extern  VOS_VOID NAS_MM_WriteKCInCard(VOS_VOID);
extern  VOS_VOID NAS_MM_WriteCkIkInCard(VOS_VOID);
extern  VOS_VOID NAS_MM_WriteLocaInCard(VOS_VOID);



extern  VOS_VOID Mm_SndAgentUsimUpdateFileReq(VOS_UINT16);
extern  VOS_VOID Mm_SndAgentUsimAuthenReq(VOS_VOID);




/* Timer公共处理 */
extern  VOS_VOID    Mm_TimerStart( VOS_UINT8 );
extern  VOS_VOID    Mm_TimerStop( VOS_UINT8 );
extern  VOS_VOID    Mm_TimerPause( VOS_UINT8 );
extern  VOS_VOID    Mm_TimerResume( VOS_UINT8 );

extern VOS_VOID NAS_MM_TimerStopExceptSpecialTimers(
    VOS_UINT8                           ucTimerNum,
    VOS_UINT8                          *pucTimer
);

extern VOS_UINT32  NAS_MM_QryTimerStatus(VOS_UINT8);

/*extern  VOS_INT32    Mm_SendMsg(MSGQUE_ID*,VOS_UINT32* );
 */

extern  VOS_VOID Mm_ComMsgCmSvcReqSnd ( MM_MSG_CM_SVC_REQ_STRU * );

/* 定义MM收到的消息实体 */
extern  MM_MSG_AUTHENTICATION_REQ_STRU          g_MmMsgAuthReq;
extern  MM_MSG_CM_SVC_RJCT_STRU                 g_MmMsgCmSvcRjct;
extern  MM_MSG_ABORT_STRU                       g_MmMsgAbort;
extern  MM_MSG_ID_REQ_STRU                      g_MmMsgIdReq;
extern  MM_MSG_LU_ACCPT_STRU                    g_MmMsgLuAccpt;
extern  MM_MSG_LU_RJCT_STRU                     g_MmMsgLuRjct;
extern  MM_MSG_MM_INFO_STRU                     g_MmMsgMmInfo;
extern  MM_MSG_TMSI_REALLOC_CMD_STRU            g_MmMsgTmsiReallocCmd;
extern  MM_MSG_MM_STATUS_STRU                   g_MmMsgMmStatus;

extern  VOS_UINT32    g_MmMutexCnt;


extern  VOS_UINT8 Mm_ComMsgAuthReqRcv (
                            VOS_UINT8      *pucRcvMsg,                              /* 当前处理的消息                           */
                            VOS_UINT16      usMsgSize                               /* 消息长度,以字节为单位                    */
                            );
extern  VOS_UINT8 Mm_ComMsgCmSvcRjctRcv (
                            VOS_UINT8      *pucRcvMsg,                              /* 当前处理的消息                           */
                            VOS_UINT16      usMsgSize                               /* 消息长度,以字节为单位                    */
                            );
extern  VOS_UINT8 Mm_ComMsgChkProc(
                        RRMM_DATA_IND_FOR_PCLINT_STRU       *pMsg                   /* 当前处理的消息                           */
                        );

extern  VOS_VOID NAS_MM_ChangeRegRejCauseAvoidInvalidSim (
    VOS_UINT8      *pucRcvMsg,                          /* 当前处理的消息          */
    VOS_UINT16      usMsgSize                           /* 消息长度,以字节为单位   */
);

extern VOS_VOID NAS_MM_ChangeMmAbortCauseAvoidInvalidSim (
    VOS_UINT8                          *pucRcvMsg,
    VOS_UINT16                          usMsgSize
);

extern VOS_VOID NAS_MM_ChangeCmSerRejCauseAvoidInvalidSim (
    VOS_UINT8                          *pucRcvMsg,
    VOS_UINT16                          usMsgSize
);

extern VOS_VOID NAS_MM_HandleHplmnRejCauseChange(
    NAS_MML_CHANGE_REJ_TYPE_ENUM_UINT8  enChangeRejType,
    VOS_UINT8                          *pucRcvMsg);
extern VOS_VOID NAS_MM_HandleVplmnRejCauseChange(
    NAS_MML_CHANGE_REJ_TYPE_ENUM_UINT8  enChangeRejType,
    VOS_UINT8                          *pucRcvMsg);
extern VOS_VOID NAS_MM_ResetRejCauseChangedCounter(VOS_VOID);

/* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-1, begin */

extern VOS_VOID NAS_MM_ConvertMmlLaiFormatToMMFormat(
    NAS_MML_LAI_STRU                   *pstSrcLai,
    MM_LAI_STRU                        *pstDstLai
);
/* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-1, end */

extern  VOS_UINT8 Mm_ComMsgAbortRcv (
                            VOS_UINT8      *pucRcvMsg,                              /* 当前处理的消息                           */
                            VOS_UINT16      usMsgSize                               /* 消息长度,以字节为单位                    */
                            );
extern  VOS_UINT8 Mm_ComMsgIdReqRcv (
                            VOS_UINT8      *pucRcvMsg,                              /* 当前处理的消息                           */
                            VOS_UINT16      usMsgSize                               /* 消息长度,以字节为单位                    */
                            );
extern  VOS_UINT8 Mm_ComMsgMmInfoRcv (
                            VOS_UINT8      *pucRcvMsg,                              /* 当前处理的消息                           */
                            VOS_UINT16      usMsgSize                               /* 消息长度,以字节为单位                    */
                            );
extern  VOS_UINT8 Mm_ComMsgMmStatusRcv (
                            VOS_UINT8      *pucRcvMsg,                              /* 当前处理的消息                           */
                            VOS_UINT16      usMsgSize                               /* 消息长度,以字节为单位                    */
                            );
extern  VOS_UINT8 Mm_ComMsgTmsiReallocCmdRcv (
                            VOS_UINT8      *pucRcvMsg,                              /* 当前处理的消息                           */
                            VOS_UINT16      usMsgSize                               /* 消息长度,以字节为单位                    */
                            );
extern  VOS_UINT32  MM_ComCheckNoOtherMmConnection(VOS_VOID);
extern VOS_UINT32 MM_ComCmpLai(MM_LAI_STRU stLai1,MM_LAI_STRU stLai2);

extern VOS_UINT32 MM_ComCheckLauIntegrityProtection(VOS_UINT8 *pucMsgContent, VOS_UINT16  usMsgLen);

extern  VOS_UINT32 MM_ComCheckIntegrityProtection(VOS_UINT8 *pucMsgContent, VOS_UINT16  usMsgLen);



extern  VOS_VOID Mm_ComMsgAuthRspSnd(
                          MM_MSG_AUTHENTICATION_RSP_STRU    *pMsg               /* 要发送的消息的指针                       */
                         );
extern  VOS_VOID Mm_ComMsgAuthFailSnd(
                          MM_MSG_AUTHENTICATION_FAIL_STRU    *pMsg              /* 要发送的消息的指针                       */
                            );
extern  VOS_VOID Mm_ComMsgCmSvcReqSnd(
                          MM_MSG_CM_SVC_REQ_STRU    *pMsg                       /* 要发送的消息的指针                       */
                            );
extern  VOS_UINT8 Mm_ComMsgSetMobileId(
                            VOS_UINT8                  *pucSndMsg,                  /* 消息的首地址                             */
                            VOS_UINT16                 *pusMsgSize,                 /* 消息目前的长度                           */
                            MM_MOBILE_ID_STRU          *pMobileId                   /* 源数据指针                               */
                            );
extern  VOS_UINT8 Mm_ComMsgSetMobileIdForEmc(
                            VOS_UINT8                  *pucSndMsg,                  /* 消息的首地址                             */
                            VOS_UINT16                 *pusMsgSize,                 /* 消息目前的长度                           */
                            MM_MOBILE_ID_STRU          *pMobileId                   /* 源数据指针                               */
                            );
extern  VOS_VOID Mm_ComMsgCmReEstReqSnd(
                            MM_MSG_RE_EST_REQ_STRU    *pMsg                     /* 要发送的消息的指针                       */
                            );
extern  VOS_VOID Mm_ComMsgIdRspSnd(
                          MM_MSG_ID_RSP_STRU    *pMsg                           /* 要发送的消息的指针                       */
                            );
extern  VOS_VOID    Mm_ComMsgMmStatusSnd(
                          MM_MSG_MM_STATUS_STRU    *pMsg                        /* 要发送的消息的指针                       */
                            );
extern  VOS_VOID    Mm_ComMsgTmsiRelocCpltSnd(VOS_VOID);
extern  VOS_VOID    Mm_ComMsgPagingRspSnd(
                            MM_MSG_PAGING_RSP_STRU    *pMsg                     /* 要发送的消息的指针                       */
                            );
extern  VOS_VOID    Mm_ComMsgCmSvcAbortSnd(VOS_VOID);

extern  VOS_UINT8*  Mm_ComMsgCmSvcReqOfRrEstReq(
                                    MM_MSG_CM_SVC_REQ_STRU    *pMsg,            /* 要发送的消息的指针                       */
                                    VOS_UINT16                    *pusMsgSize       /* 消息的长度指针                           */
                                    );

extern  VOS_UINT8   Mm_ComMsgCcMsgInteChk (
                              RRMM_DATA_IND_FOR_PCLINT_STRU       *pMsg         /* 当前处理的消息                           */
                               );
extern  VOS_UINT8   Mm_ComMsgCmSvcAcceptRcv (
                                  RRMM_DATA_IND_FOR_PCLINT_STRU       *pMsg     /* 当前处理的消息                           */
                                  );
extern  VOS_UINT8   Mm_ComMsgAuthRjctRcv (VOS_VOID);

/* MM连接公共处理 */
extern  VOS_VOID    Mm_CheckDelayMmConn( VOS_VOID );
extern  VOS_VOID    Mm_ComAuthenRcvAuthenReq(VOS_VOID);
extern  VOS_VOID    Mm_ComIdentity(VOS_VOID);
extern  VOS_VOID    Mm_ComTmsiReloc(VOS_VOID);
extern  VOS_VOID    Mm_ComRejectCause4(VOS_VOID);
extern  VOS_VOID    Mm_ComRejectCause6(VOS_VOID);
extern  VOS_VOID    Mm_ComAbortCause6(VOS_VOID);
extern  VOS_VOID    Mm_ComAbortCause17(VOS_VOID);
extern  VOS_VOID    Mm_ComInfo(VOS_VOID);
extern  VOS_VOID    Mm_ComStart(VOS_VOID);

extern  VOS_VOID    Mm_SndAgentUsimUpdateFileReq( VOS_UINT16 usEfId );
extern  VOS_UINT8   NAS_MM_RcvGmmGprsDetechIni(VOS_VOID*);
extern  VOS_UINT8   Mm_RcvGmmGprsDetechCmpl(VOS_VOID*);

/* extern  AGENT_USIM_AUTHENTICATION_CNF_STRU      g_AgentUsimAuthCnf; */
extern  MM_USIM_AUTHENTICATION_CNF_STRU      g_AgentUsimAuthCnf;


extern  VOS_VOID    Mm_ComSaveLai(
                   VOS_UINT8            *pucLai,                                    /* 消息中的LAI存放地址                      */
                   MM_LAI_STRU      *pLai                                       /* LAI全局量的地址                          */
                   );
extern  VOS_VOID    Mm_ComSvcStaJudge(VOS_UINT8);
extern VOS_VOID  NAS_MM_FillMobileID(
    MM_MOBILE_ID_STRU                  *pstMobileID
);
extern  VOS_VOID    Mm_ComLuOnly(VOS_VOID);

extern VOS_VOID Mm_ComRelAllMmConn(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause
);


extern  VOS_VOID Mm_ComRelAllMmConnExcEmergencyCall(
        NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause
);


extern  VOS_VOID    Mm_SndAgentUsimAuthenReq(VOS_VOID);

extern  VOS_VOID    Mm_ComInit (VOS_VOID);

extern  VOS_VOID    Mm_ComNasInfoSav (VOS_UINT8,VOS_UINT8);
extern  VOS_VOID    Mm_ComRejectCause11(VOS_UINT8);
extern  VOS_VOID    Mm_ComRejectCause13(VOS_UINT8);
extern  VOS_VOID    Mm_ComRejectCause15(VOS_UINT8);
extern  VOS_VOID    Mm_ComAttUsimSav(VOS_UINT8,VOS_UINT8);
extern  VOS_VOID    MM_Fill_IE_ClassMark1(VOS_UINT8 *pClassMark1);
extern  VOS_VOID    MM_Fill_IE_ClassMark2(VOS_UINT8 *pClassMark2);
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-29, begin */
extern  VOS_VOID    Mm_ComSetMmState(NAS_MM_STATE_ENUM_UINT8 ulState);
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-29, end */
extern MMCC_CHANNEL_MODE_ENUM_U32 MM_ComGetChanMode(NAS_RR_CHANNEL_MODE_ENUM_U8 enChanMode);

extern NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8 NAS_MM_GetLauUptNeededCsSrvStatus(VOS_VOID);
extern VOS_VOID NAS_MM_ProcCsAcChgRegisterNetModeII(VOS_VOID);
extern VOS_UINT32 NAS_MM_IsLaiChange();
VOS_VOID NAS_MM_UpdateMmStateCsRegRestrictBarToUnbar(VOS_VOID);

/* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-26, begin */
VOS_VOID NAS_MM_ProcEccNumList_RcvSysinfo(
    VOS_UINT32                          ulMcc
);

/* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-26, end */


VOS_UINT32  NAS_MM_IsLauNeededLaiNoChange_LInterSys(VOS_VOID);

extern  VOS_VOID    Mm_Cell_S3_E24(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S4_E24(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E24(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S10_E24(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S11_E24(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S19_E24(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S10_E25(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S13_E25(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S16_E25(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S2_E26(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E26(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S16_E26(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S10_E27(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S13_E28(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S2_E31(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S3_E31(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S4_E31(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S12_E32(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S14_E32(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E33(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S10_E33(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S11_E33(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S12_E33(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S14_E33(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S16_E33(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S22_E33(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S25_E33(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E34 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S10_E34(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S14_E34(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E35 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E36 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E37 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E38 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E39 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E40 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E41 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S14_E41(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E42 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E43 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E50 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S0_E1  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S0_E2  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S1_E1  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S1_E2  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S1_E3  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S3_E6  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E1  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E2  (VOS_VOID*);
/* 删除Mm_Cell_S9_E4 */
extern  VOS_VOID    Mm_Cell_S10_E1 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S10_E2 (VOS_VOID*);
/* 删除Mm_Cell_S10_E4 */
extern  VOS_VOID    Mm_Cell_S11_E1 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S11_E2 (VOS_VOID*);
/* MMCMM_PLMN_USER_SEL_REQ不再使用，删除Mm_Cell_S11_E4 */
extern  VOS_VOID    Mm_Cell_S12_E1 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S12_E2 (VOS_VOID*);
/* MMCMM_PLMN_USER_SEL_REQ不再使用，删除Mm_Cell_S12_E4 */
extern  VOS_VOID    Mm_Cell_S13_E1 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S13_E2 (VOS_VOID*);
/* MMCMM_PLMN_USER_SEL_REQ不再使用，删除Mm_Cell_S13_E4 */
extern  VOS_VOID    Mm_Cell_S14_E1 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S14_E2 (VOS_VOID*);
/* MMCMM_PLMN_USER_SEL_REQ不再使用，删除Mm_Cell_S14_E4 */
extern  VOS_VOID    Mm_Cell_S16_E1 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S16_E2 (VOS_VOID*);
/* MMCMM_PLMN_USER_SEL_REQ不再使用，删除Mm_Cell_S16_E4 */
/* MMCMM_PLMN_USER_SEL_REQ不再使用，删除Mm_Cell_S16_E4 */
extern  VOS_VOID    Mm_Cell_S1_E5  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S2_E5  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S2_E21 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S14_E21 (VOS_VOID*);
extern  VOS_VOID    Mm_RcvRrmmRelInd(VOS_VOID);
extern  VOS_VOID    Mm_RcvRrmmEstCnf(VOS_VOID);
extern  VOS_VOID    Mm_Cell_S9_E21 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S3_E5  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S3_E9  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S3_E11 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S3_E12 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S3_E13 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S3_E15 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S3_E16 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S3_E17 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S17_E17 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S3_E21 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S4_E5  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S4_E15 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S6_E15 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S4_E16 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S4_E17 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S4_E21 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S5_E5  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S5_E15 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S5_E16 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S5_E17 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S5_E21 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S5_E31 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S6_E31 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S6_E15 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S6_E16 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S6_E17 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S6_E21 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S8_E21 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E9  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E11 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E12 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E13 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E14 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E16 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E44 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S11_E9 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S11_E11(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S11_E12(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S11_E13(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S11_E14(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S11_E16(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S12_E9 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S12_E11(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S12_E12(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S12_E13(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S12_E14(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S12_E16(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S17_E5 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S17_E7 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S17_E8 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S17_E9 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S17_E11(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S17_E12(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S17_E13(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S17_E15(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S17_E16(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S17_E18(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S17_E19(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S17_E21(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S18_E5 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S18_E10(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S18_E12(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S18_E15(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S18_E16(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S18_E17(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S18_E21(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S0_E45 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S0_E47 (VOS_VOID*);

extern  VOS_VOID    Mm_Cell_S3_E49 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S11_E49 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S22_E49 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S23_E49 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S24_E49 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S25_E49 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S26_E49 (VOS_VOID*);

extern  VOS_VOID    Mm_Cell_S1_E46 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S3_E46 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E46 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E48 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E55  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E56  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E57  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E59  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S11_E60 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S0_E61  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S1_E61  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S12_E61 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S13_E61 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S10_E46 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S11_E46 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S12_E46 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S13_E46 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S14_E46 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S16_E46 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S17_E46 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S18_E46 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S19_E46 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S11_E50(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S14_E40(VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S13_E9 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S1_E47 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S0_E3 (VOS_VOID*);

extern  VOS_VOID    Mm_ComAuthenRcvUsimCnf(VOS_VOID);
extern  VOS_VOID    Mm_ComDelRandRes(VOS_VOID);

extern VOS_UINT8    Mm_Get_UserSpecificSearchFlg_From_SysInfo(VOS_VOID *);

/* extern  const   MM_CELL_FUN_TYPE*       aMmStateTable[82]; */
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-2, begin */
extern  const   MM_CELL_FUN_TYPE*       gaMmStateTable[91];
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-2, end */



extern  VOS_VOID    Mm_Nop(VOS_VOID*);



extern VOS_VOID     Mm_MakeCcEstReq(MMCC_EST_REQ_STRU *);
extern VOS_VOID     Mm_MakeSmsEstReq(MMSMS_EST_REQ_STRU *);
/* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-15, begin */
extern VOS_VOID     Mm_MakeSsEstReq(MMSS_EST_REQ_STRU *);
/* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-15, end */
extern VOS_VOID     Mm_DealWithBuffMsg(VOS_VOID);

extern VOS_VOID     Mm_MakeGPagingInd(GRRMM_PAGING_IND_ST *pMsg);
extern VOS_VOID     Mm_MakeWPagingInd(RRMM_PAGING_IND_STRU *pMsg);

/********************* CELL处理 ***********************/
extern  VOS_VOID    Mm_Cell_S3_E62  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E62  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S10_E62 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S11_E62 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S10_E63 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S3_E65  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E65  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S10_E65 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S11_E65 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S10_E66 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S12_E66 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S27_E68 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E71  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S10_E71 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S27_E27 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S3_E14  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S4_E14  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S5_E14  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S6_E14  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S17_E14 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S23_E14 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S3_E15  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S4_E15  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S5_E15  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S6_E15  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S17_E15 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S14_E16 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S25_E16 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S26_E16 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S0_E20  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E20  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S12_E21 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S1_E22  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S2_E22  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S3_E22  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S4_E22  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S5_E22  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S6_E22  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E22  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S12_E22 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S14_E22 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S17_E22 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S23_E22 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S24_E22 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S0_E23  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S22_E23 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E25  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S22_E32 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S25_E32 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S23_E33 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S24_E33 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S26_E33 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S23_E44 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S24_E44 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S26_E44 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S27_E44 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S23_E45 (VOS_VOID*);
/* Added by l00208543 for V9R1 STK升级, 2013-07-09, begin */
extern VOS_VOID NAS_MM_SndStkLauRej(VOS_UINT8 ucCause);
/* Added by l00208543 for V9R1 STK升级, 2013-07-09, end */

VOS_VOID Mm_Cell_S12_E25(VOS_VOID  *pRcvMsg);

/* Added by l00208543 for V9R1 STK升级, 2013-07-22, begin */
extern NAS_STK_UPDATE_TYPE_ENUM_UINT8 NAS_MM_ConvertMmLuTypeToStkLuType (LAU_TYPE_ENUM_UINT8 enMmLuType);

extern TAF_MMA_RAT_TYPE_ENUM_UINT8 NAS_MM_ConvertMmRatTypeToStkRatType (NAS_MML_NET_RAT_TYPE_ENUM_UINT8 enMmRatType);

/* Added by l00208543 for V9R1 STK升级, 2013-07-22, end */

extern  VOS_VOID    Mm_Cell_S23_E46 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E47  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S10_E47 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S11_E47 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S26_E48 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S23_E51 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S3_E52  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E52  (VOS_VOID*);

VOS_VOID NAS_MM_SndGmmT3211ExpiredNotify(
    VOS_UINT8                           ucRejectCause
);

extern  VOS_VOID    Mm_Cell_S1_E53  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S3_E53  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E55  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S14_E55 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S26_E55 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S14_E56 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S26_E56 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S26_E58 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S24_E60 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E71  (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S10_E71 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S14_E13 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S14_E14 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S14_E16 (VOS_VOID*);

/********************* 接收公共处理 ***********************/
extern  VOS_UINT8   Mm_RcvSmsEstReq ( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvSmsRelReq ( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvSmsDataReq( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvSsEstReq  ( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvSsRelReq  ( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvSsDataReq ( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvCcPromptRej( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvMmcDetachReq( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvMmcPowerOffReq( VOS_VOID* );

/********************* 发送公共处理 ***********************/
extern  VOS_VOID    Mm_SndSsEstInd( VOS_UINT32  ulTransactionId, VOS_UINT32  ulSize, \
                                VOS_UINT8 *pucSsMsg );
extern  VOS_VOID    Mm_SndSsDataInd( VOS_UINT32  ulTransactionId, VOS_UINT32 ulSize, \
                                 VOS_UINT8 *pucSSMsg );
extern  VOS_VOID    Mm_SndSsEstCnf  ( VOS_UINT32 ulTi, VOS_UINT32 ulResult );

extern VOS_VOID Mm_SndSsRelInd(
    VOS_UINT32                          ulTransactionId,
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmssRelCause
);
extern  VOS_VOID    Mm_SndSmsEstCnf ( VOS_UINT32 ulTi );
extern  VOS_VOID    Mm_SndMmcRrConnInfInd( VOS_UINT32 ulRrConnFlg );
extern  VOS_VOID    Mm_SndSmsEstInd( VOS_UINT32  ulTransactionId, VOS_UINT32  ulSize,\
                                 VOS_UINT8  *pucSmsMsg );
extern  VOS_VOID    Mm_SndSmsDataInd( VOS_UINT32 ulTransactionId, VOS_UINT32 ulSize, \
                                  VOS_UINT8   *pucSmsMsg );
extern  VOS_VOID    Mm_SndSmsRelInd ( VOS_UINT32 ulTi,VOS_UINT32 ulRelCause );
extern  VOS_VOID    Mm_SndCcPromptInd( VOS_VOID );
extern  VOS_VOID    NAS_MM_SndMmcDetachCnf(VOS_UINT8);
extern  VOS_VOID NAS_MM_SndMmcAttachCnf(VOS_VOID);
extern  VOS_VOID    Mm_SndMmcPowerOffCnf(VOS_VOID);
extern  VOS_VOID    Mm_SndMmcDeRegisterInit(VOS_VOID);
VOS_VOID NAS_MM_SndGmmLuResultInd(
    VOS_UINT32                          ulLuResult,
    VOS_UINT32                          ulCause
);
VOS_VOID NAS_MM_SndMmcCsRegResultInd(
    VOS_UINT32                          ulRealFlg,
    VOS_UINT32                          ulLuResult,
    VOS_UINT32                          ulCause
);

VOS_VOID NAS_MM_SndMmcAbortInd(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enAbortCause
);

VOS_VOID NAS_MM_SndGmmAuthFailInd(VOS_VOID);
VOS_VOID NAS_MM_SndGmmCsConnectInd(
    MMGMM_CS_CONNECT_STATUS_ENUM_UINT32    enCsConnectStatus
);

VOS_VOID NAS_MM_SndGmmCsLocalDetachInd(VOS_VOID);

VOS_VOID NAS_MM_SndGmmCmSvcRejInd(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
);

VOS_VOID NAS_MM_SndGmmRegisterInit(VOS_VOID);

/********************* 其它公共处理 ***********************/
VOS_VOID NAS_MM_ConvertToMmcServiceStatus(
    VOS_UINT8                           ucMmServiceStatus,
    VOS_UINT32                         *pCsServiceStatus
);
extern  VOS_VOID    Mm_ComCauseHandleAllProc(
                                        VOS_UINT8   ucProcType,
                                        VOS_UINT16  usCause
                                        );
extern  VOS_VOID    Mm_ComLuCauseHandle(
                                    VOS_UINT16   usCause
                                    );
extern  VOS_VOID    Mm_ComGmmAttachCauseHandle(
                                        VOS_UINT16   usCause
                                        );
extern  VOS_VOID    Mm_ComGmmRauCauseHandle(
                                        VOS_UINT16   usCause
                                        );
extern  VOS_VOID    Mm_ComGmmSrCauseHandle(
                                        VOS_UINT16   usCause
                                        );
extern  VOS_VOID    Mm_ComNetDetachCauseHandle(
                                        VOS_UINT16   usCause
                                        );
extern  VOS_VOID    Mm_ComToU2Handle( VOS_VOID );
extern  VOS_VOID    NAS_MM_DelLaiTmsiCK(VOS_VOID);
extern  VOS_VOID    Mm_ComToNoImsiHandle( VOS_VOID );
extern VOS_VOID     Mm_ComSysInfoHandleWithLaiNoChange(VOS_UINT8);

extern VOS_VOID  NAS_MM_RcvSysInfoPsRestrictRegLaiNoChangeU1(VOS_VOID);

extern  VOS_VOID    Mm_ComRcvSysHandle( VOS_UINT8 );
extern  VOS_UINT8   Mm_ComMmConnExist( VOS_VOID );

extern  VOS_VOID   Mm_ComSaveProcAndCauseVal(
                                            VOS_UINT8   ucProc,
                                            VOS_UINT16  usCauseVal
                                            );
extern  VOS_UINT8   Mm_ComJudgeLimitSvc( VOS_VOID );
extern  VOS_VOID    Mm_ComFillInCMSncReq(
                                    VOS_UINT8                       ucCMSvcType,
                                    VOS_UINT8                       ucPrioLeveFlg,
                                    MM_MSG_CM_SVC_REQ_STRU      *CmSvcReq
                                    );
extern  VOS_VOID   Mm_ComFollowOnProc( VOS_VOID );

extern  VOS_VOID   Mm_ComMsgImsiDetachIniSndOfEstReq(MM_MSG_IMSI_DETACH_IND_STRU * );

extern  VOS_VOID   Mm_ComMsgImsiDetachIniSndOfDataReq(MM_MSG_IMSI_DETACH_IND_STRU *);



extern  VOS_UINT8  Mm_RcvMmcRelReq(VOS_VOID* );
extern  VOS_UINT8   Mm_RcvMmcModeChngReq( VOS_VOID* );

extern VOS_UINT8 Mm_RcvGmmLuIni( VOS_VOID* );
extern VOS_VOID  Mm_ComMsgLuReqSndOfEstReq(MM_MSG_LU_REQ_STRU* );

extern VOS_VOID Mm_ComProcCauseProcess(VOS_VOID);


extern  VOS_VOID    Mm_Cell_S22_E1 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S22_E4 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S23_E4 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S26_E4 (VOS_VOID*);
/* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-1, begin */

/* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-1, end */
extern  VOS_VOID    Mm_Cell_S18_E13 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S3_E23 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E23 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S12_E23 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S14_E23 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S25_E23 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S4_E62 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S1_E63 (VOS_VOID*);

extern VOS_VOID Mm_Cell_S32_E63(
    VOS_VOID                           *pRcvMsg
);


extern  VOS_VOID    Mm_Cell_S10_E63 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S12_E63 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S16_E63 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S10_E64 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S4_E65 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S10_E66 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S16_E66 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S10_E67 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E69 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S11_E69 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E70 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S11_E70 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S11_E70 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S19_E2 (VOS_VOID*);
VOS_VOID NAS_MM_RcvAttachReq_InterRatChange(
    VOS_VOID                          *pMsg
);
extern  VOS_VOID    Mm_Cell_S3_E12 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S4_E12 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S4_E2 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S1_E20 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S3_E20 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E20 (VOS_VOID*);

extern  VOS_VOID    Mm_Cell_S11_E27 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S14_E50 (VOS_VOID*);



extern  VOS_VOID    Mm_Cell_S6_E5 (VOS_VOID*);



extern  VOS_VOID    Mm_Cell_S5_E53 (VOS_VOID*);



extern  VOS_VOID    Mm_ComDelLai (VOS_VOID);




extern  VOS_VOID    Mm_Cell_S22_E5 (VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S23_E5 (VOS_VOID*);
/* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-1, begin */

/* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-1, end */


extern  VOS_VOID    Mm_ComT3212(VOS_UINT32);



extern  VOS_VOID    Mm_Cell_S8_E22 (VOS_VOID*);

extern  VOS_VOID    Mm_ComProcCauseClear( VOS_VOID );


extern  VOS_VOID    Mm_Cell_S5_E22( VOS_VOID* );


extern  VOS_VOID    Mm_Cell_S6_E53( VOS_VOID* );



extern  VOS_VOID    Mm_Cell_S0_E14( VOS_VOID* );
extern  VOS_VOID    Mm_Cell_S0_E13( VOS_VOID* );



extern  VOS_VOID    Mm_Cell_S6_E24( VOS_VOID* );
extern  VOS_VOID    Mm_Cell_S6_E62( VOS_VOID* );
extern  VOS_VOID    Mm_Cell_S6_E65( VOS_VOID* );



extern  VOS_VOID    Mm_Cell_S5_E24( VOS_VOID* );
extern  VOS_VOID    Mm_Cell_S5_E62( VOS_VOID* );
extern  VOS_VOID    Mm_Cell_S5_E65( VOS_VOID* );



extern  VOS_VOID    Mm_Cell_S0_E22( VOS_VOID* );



extern  VOS_VOID    Mm_Cell_S0_E59( VOS_VOID* );



extern  VOS_VOID    Mm_Cell_S0_E60( VOS_VOID* );



extern  VOS_VOID    Mm_Cell_S11_E36( VOS_VOID* );
extern  VOS_VOID    Mm_Cell_S11_E37( VOS_VOID* );
extern  VOS_VOID    Mm_Cell_S11_E38( VOS_VOID* );
extern  VOS_VOID    Mm_Cell_S11_E39( VOS_VOID* );
extern  VOS_VOID    Mm_Cell_S11_E43( VOS_VOID* );
extern  VOS_VOID    Mm_Cell_S11_E44( VOS_VOID* );
extern  VOS_VOID    Mm_Cell_S11_E47( VOS_VOID* );



extern  VOS_VOID    Mm_Cell_S5_E62( VOS_VOID* );
extern  VOS_VOID    Mm_Cell_S5_E65( VOS_VOID* );
extern  VOS_VOID    Mm_Cell_S22_E24( VOS_VOID* );



extern  VOS_VOID    Mm_Cell_S11_E40( VOS_VOID* );



extern  VOS_VOID    Mm_Cell_S1_E24( VOS_VOID*);



extern  VOS_UINT8    Mm_ComChkLu( VOS_VOID );

/* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-18, begin */

/* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-18, end */
extern  VOS_VOID    Mm_Cell_S9_E71( VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S31_E72( VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E73( VOS_VOID*);
extern  VOS_VOID    Mm_SndTcDataInd( VOS_UINT32,VOS_UINT8*);
extern  VOS_VOID    Mm_Cell_S31_E71( VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S31_E33( VOS_VOID*);

extern  VOS_VOID    Mm_Cell_S0_E21( VOS_VOID*);

extern  VOS_VOID    Mm_Cell_S3_E34( VOS_VOID*);


extern  VOS_VOID    Mm_Cell_S0_E33( VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S2_E33( VOS_VOID*);

extern VOS_VOID Mm_SndAgentInfo(VOS_VOID);
extern VOS_VOID MmMsgProc (struct MsgCB* );

extern  VOS_VOID    Mm_Cell_S25_E24( VOS_VOID*);

extern  VOS_VOID    Mm_Cell_S22_E13( VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S23_E13( VOS_VOID*);

extern  VOS_VOID    Mm_Cell_S0_E16( VOS_VOID*);

extern  VOS_VOID    Mm_ComAuthMsRej(VOS_VOID);

extern  VOS_VOID    Mm_Cell_S24_E14( VOS_VOID*);

extern  VOS_VOID    Mm_Cell_S25_E37( VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S26_E37( VOS_VOID*);

extern  VOS_VOID    Mm_Cell_S17_E22( VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S17_E23( VOS_VOID*);

extern  VOS_VOID    Mm_Cell_S25_E76( VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E75( VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S12_E77( VOS_VOID*);

extern  VOS_VOID    Mm_Cell_S14_E77( VOS_VOID*);

extern  VOS_VOID    Mm_Cell_S22_E77( VOS_VOID*);

extern  VOS_UINT8    Mm_ComTempIdJudge( VOS_VOID );

extern  VOS_VOID    Mm_Cell_S6_E74( VOS_VOID*);
extern  VOS_UINT8   Mm_RcvRrcAcInfoChgInd( VOS_VOID* );


extern  VOS_VOID    Mm_Cell_S0_E24( VOS_VOID*);

extern  VOS_VOID    Mm_Cell_S10_E40( VOS_VOID*);
extern  VOS_UINT8    MM_IeChkLai(VOS_UINT8*);
extern  VOS_UINT8    MM_IeChkMblId(VOS_UINT8*);
extern  VOS_UINT8    MM_IeChkFlwOnPrcd(VOS_UINT8*);
extern  VOS_UINT8    MM_IeChkCtsPrmsn(VOS_UINT8*);
extern  VOS_UINT8    MM_IeChkPlmnLst(VOS_UINT8*);
extern  VOS_UINT8    MM_IeChkRjctCaus(VOS_UINT8*);
extern  VOS_UINT8    MM_IeChkCksn(VOS_UINT8*);
extern  VOS_UINT8    MM_IeChkSprHalfOctet(VOS_UINT8*);
extern  VOS_UINT8    MM_IeChkRand(VOS_UINT8*);
extern  VOS_UINT8    MM_IeChkAutn(VOS_UINT8*);
extern  VOS_UINT8    MM_IeChkIdType(VOS_UINT8*);
extern  VOS_UINT8    MM_IeChkNtwkNam(VOS_UINT8*);
extern  VOS_UINT8    MM_IeChkTimZone(VOS_UINT8*);
extern  VOS_UINT8    MM_IeChkTimAndTimZone(VOS_UINT8*);
extern  VOS_UINT8    MM_IeChkLsaIdtfr(VOS_UINT8*);
extern  VOS_UINT8    MM_IeChkDayLightSavTim(VOS_UINT8*);
extern  VOS_UINT8    MM_IeChkPdAndSapi(VOS_UINT8*);


extern  VOS_VOID    Mm_Cell_S31_E1( VOS_VOID*);

extern  VOS_VOID    Mm_Cell_S0_E78( VOS_VOID*);
extern  VOS_UINT8   Mm_RcvMmAgentInquire( VOS_VOID* );
extern VOS_UINT8 Mm_RcvMmAgentTransCmd(VOS_VOID   *pRcvMsg );

extern  VOS_VOID    Mm_Cell_S31_E23( VOS_VOID*);

extern  VOS_VOID    Mm_Cell_S12_E79( VOS_VOID*);

extern  VOS_VOID    Mm_Cell_S13_E79( VOS_VOID*);


extern VOS_VOID Mm_Cell_S4_E13(VOS_VOID* pMsg);
extern VOS_VOID Mm_Cell_S5_E13(VOS_VOID* pMsg);
extern VOS_UINT8 Mm_ComRrConnRelChk(VOS_VOID);
extern VOS_UINT8 Mm_ComTiChk(VOS_VOID);
extern VOS_VOID Mm_ComSigRelForDelayMmConnRej(VOS_VOID);

extern  VOS_VOID    Mm_Cell_S9_E15( VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E5( VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S12_E5(VOS_VOID* pMsg);

extern  VOS_VOID    Mm_Cell_S10_E26(VOS_VOID*);

extern  VOS_VOID    Mm_Cell_S12_E26(VOS_VOID*);

extern  VOS_VOID    Mm_Cell_S10_E50( VOS_VOID*);

extern  VOS_UINT8   Mm_RcvSsAbortReq( VOS_VOID* );
extern  VOS_UINT8   Mm_RcvSmsAbortReq( VOS_VOID* );
extern  VOS_VOID    Mm_Cell_S5_E80( VOS_VOID*);

extern VOS_VOID Mm_Cell_S32_E80(
    VOS_VOID                           *pRcvMsg
);


extern  VOS_VOID    Mm_Cell_S9_E80( VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S10_E80( VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S12_E80( VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S16_E80( VOS_VOID*);

extern  VOS_VOID    Mm_Cell_S32_E80( VOS_VOID*);

extern  VOS_VOID    Mm_Cell_S5_E81( VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S9_E81( VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S10_E81( VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S12_E81( VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S16_E81( VOS_VOID*);
extern  VOS_VOID    Mm_Com_UsimAuthenticationCnfChgFormat(
                                               USIMM_AUTHENTICATION_CNF_STRU *
                                                     );
extern  VOS_VOID Mm_ComNetModeChange(VOS_VOID);

extern  VOS_VOID    Mm_Cell_S16_E63( VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S16_E66( VOS_VOID*);
extern  VOS_VOID    Mm_Cell_S27_E82( VOS_VOID*);
/* Mm_Cell_S27_E33_Handling_REL_CAUSE_RL_FAILURE不再使用，删除 */
extern VOS_VOID Mm_SndSmsRegStsInd( VOS_UINT8 );
extern VOS_UINT8 MM_SndSapi3EstReq(VOS_VOID);
extern VOS_VOID Mm_Cell_S9_E83(VOS_VOID*);
extern VOS_VOID Mm_Cell_S6_E54(VOS_VOID* pMsg);
extern VOS_VOID Mm_Cell_S3_E84( VOS_VOID* );
extern VOS_VOID Mm_Cell_S32_E85( VOS_VOID* );
extern VOS_VOID Mm_Cell_S32_TimerExpire( VOS_VOID* );
extern VOS_VOID Mm_Cell_S32_DataTransfer( VOS_VOID* );
extern VOS_VOID Mm_Cell_S32_CCEstREQ( VOS_VOID* );
extern VOS_VOID Mm_Cell_S32_SMSEstREQ( VOS_VOID* );
extern VOS_VOID Mm_Cell_S32_SSEstREQ( VOS_VOID* );
extern VOS_VOID Mm_Cell_S32_E23( VOS_VOID* );
extern VOS_VOID Mm_Cell_S6_E86(VOS_VOID *pRcvMsg);
extern VOS_VOID Mm_Cell_S27_E87(
                            VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                        );

extern VOS_VOID Mm_Cell_S32_E22( VOS_VOID* );

extern VOS_VOID Mm_Cell_S3_E88( VOS_VOID* );
extern VOS_VOID Mm_Cell_S5_E88( VOS_VOID* );

extern VOS_VOID Mm_Cell_S6_E88( VOS_VOID* );
extern VOS_VOID Mm_Cell_S9_E88( VOS_VOID* );

extern VOS_VOID Mm_Cell_S3_E54(VOS_VOID* pMsg);

extern VOS_UINT32 NAS_MM_IsExistBufferService(VOS_VOID);

extern VOS_UINT8  NAS_MM_CheckIfMmIsEstablishRRConnection(VOS_VOID);

extern  VOS_UINT8 NAS_MM_RetryCurrentProcedureCheck(
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause,
    RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus
);

VOS_UINT8 NAS_MM_IsRrRelCauseNeedRetryLau(
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause
);
extern  VOS_VOID NAS_MM_RetryMmConnectionProc(
    VOS_UINT8                           ucMMConnEstingPD
);

extern  VOS_VOID NAS_MM_GetPDFromConnCtrlEnum(
    NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl,
    VOS_UINT8                           *pucMMConnEstingPD
);

extern  VOS_VOID NAS_MM_EstMmConnection(
    NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl
);

extern  VOS_VOID NAS_MM_UpdateConnCtrlInfo(
    NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl
);

/* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, begin */
extern  VOS_UINT32 NAS_MM_IsCcServiceNeedTriggerPlmnSearch(VOS_VOID);
/* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, end */


extern  VOS_VOID NAS_MM_GetCMSvcType(
    NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl,
    VOS_UINT8                           *pucCmSrvType
);

extern  VOS_VOID NAS_MM_GetRrcEstCause(
    NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl,
    VOS_UINT32                          *pulRrcEstCause
);

extern  VOS_VOID NAS_MM_UpdateMmLinkCtrlStru(VOS_VOID);

extern  VOS_VOID NAS_MM_ClearMmLinkCtrlStru( VOS_VOID );

extern  VOS_VOID NAS_MM_ClearConnCtrlInfo(VOS_UINT8 ucMMConnEstingPD);

extern  VOS_VOID NAS_MM_ProcEstCnfSuccessCauseAtState12(VOS_VOID);

extern VOS_VOID NAS_MM_InformCmLayerEstFail(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult
);

extern  VOS_VOID NAS_MM_ProcEstCnfOtherFailCauseAtState12(RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult);

extern  VOS_VOID NAS_MM_ProcEstCnfCauseAtState12(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult
);

extern  MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeFullNameForNetworkIe(
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT16                          *pusIndex,
    VOS_UINT8                           *pucEventId,
    VOS_UINT8                           *pucLongNetWorkNameExist
);

extern  MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeShortNameForNetworkIe(
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT16                          *pusIndex,
    VOS_UINT8                           *pucEventId,
    VOS_UINT8                           *pucShortNetWorkNameExist
);

extern  MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeLocalTimeZoneIe(
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT16                          *pusIndex,
    VOS_UINT8                           *pucEventId
);

extern  MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeUniversalTimeAndLocalTimeZoneIe(
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT16                          *pusIndex,
    VOS_UINT8                           *pucEventId
);

extern  MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeLocalizedServiceAreaIe(
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT16                          *pusIndex,
    VOS_UINT8                           *pucEventId
);

extern  MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeNetworkDaylightSavingTimeIe(
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT16                          *pusIndex,
    VOS_UINT8                           *pucEventId
);

extern VOS_UINT32 NAS_GMM_IsRegisteredOrRegistering(VOS_VOID);


extern VOS_BOOL NAS_MM_CheckIfTmsiIsValid(VOS_VOID);

extern VOS_VOID NAS_MM_FillNasMmState(
    NAS_OM_MM_IND_STRU                  *pMsg
);
extern VOS_UINT8 NAS_MM_RcvMmcAttachReq_PreProc(
    VOS_VOID                           *pstRcvMsg
);
extern VOS_UINT8  NAS_MM_RcvMmcDetachReq_PreProc(
    VOS_VOID                           *pstRcvMsg
);

extern VOS_VOID NAS_MM_SetLikeBFlg(VOS_VOID);

extern VOS_VOID NAS_MM_SndTcRrRelInd(VOS_VOID);

extern VOS_VOID NAS_MM_ProcInterRatReselInLuProcedure(VOS_VOID);

extern VOS_VOID NAS_MM_ProcDelayService(VOS_VOID);

VOS_VOID Mm_ComProcCauseProcess_Handling_LU_PROC(VOS_VOID);

extern VOS_VOID NAS_MM_ProcSysInfoWithLaiNoChgWhenNotPlmnSrch(VOS_VOID);

extern VOS_VOID Mm_Cell_S32_E26(VOS_VOID  *pRcvMsg);

extern VOS_UINT8 NAS_MM_RcvMmcRatChangeInd(
        VOS_VOID                           *pstRcvMsg
    );



#if (FEATURE_ON == FEATURE_LTE)
extern VOS_VOID NAS_MM_RcvSsEstReq_CSFB(VOS_VOID);
extern VOS_VOID NAS_MM_RcvCcEstReq_CSFB(VOS_VOID);
extern VOS_VOID NAS_MM_SndLmmCsfbServiceStartNotify(VOS_VOID);
extern VOS_VOID NAS_MM_SndLmmCsfbServiceAbortNotify(VOS_VOID);
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-11, begin */
extern VOS_VOID NAS_MM_SndLmmHoSecuInfoReq(VOS_VOID);
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-11, end */
extern VOS_VOID NAS_MM_RcvSysInfo_CSFB(VOS_VOID);
extern VOS_VOID NAS_MM_ResumeBackToGU_CSFB(
    MMCMM_RESUME_IND_STRU                                  *pstResumeInd,
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCsfbServiceStatus
);
extern VOS_VOID NAS_MM_EndCsfbFlow(
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8 enCsfbServiceStatus,
    NAS_MMCM_REL_CAUSE_ENUM_UINT32         enRelCause
);

VOS_VOID NAS_MM_PerformBufferedSsService(VOS_VOID);
VOS_VOID NAS_MM_ResponseLmmPagingInd_CSFB(VOS_VOID);


extern VOS_VOID Mm_Cell_S3_E89(
    VOS_VOID                           *pRcvMsg
);

extern VOS_VOID Mm_Cell_S5_E89(
    VOS_VOID                           *pRcvMsg
);

extern VOS_UINT32 NAS_MM_IsT3412ExpiredNeedRegist(
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg,
    NAS_MML_TIN_TYPE_ENUM_UINT8                             enTinType,
    NAS_MML_TIMER_INFO_ENUM_UINT8                           enT3412Status
);

extern VOS_UINT32 NAS_MM_IsT3423StatusChangeNeedRegist(
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg,
    NAS_MML_TIN_TYPE_ENUM_UINT8                             enTinType,
    NAS_MML_TIMER_INFO_ENUM_UINT8                           enT3423Status
);

extern VOS_VOID  NAS_MM_WriteTinInfoNvim(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType,
    VOS_UINT8                          *pucImsi
);
extern VOS_UINT32 NAS_MM_IsNeedDeactiveIsrAfterLau(VOS_VOID);

VOS_UINT32 NAS_MM_IsNeedDeactiveIsrLauInit(VOS_VOID);

extern VOS_VOID NAS_MM_LogTinTypeInfo(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType
);

VOS_UINT32 NAS_MM_RcvSysInfoSurpportLte_PreProc(VOS_VOID);

#if(FEATURE_ON == FEATURE_DSDS)
extern VOS_VOID NAS_MM_SndLmmBeginSessionNotify(
    MM_LMM_SESSION_TYPE_ENUM_UINT8      enSessionType
);

extern VOS_VOID NAS_MM_SndLmmEndSessionNotify(
    MM_LMM_SESSION_TYPE_ENUM_UINT8      enSessionType
);
#endif

#endif

VOS_UINT8 NAS_MM_GetStaOfRcvXXEstReq_CSFB(VOS_VOID);

VOS_UINT8 NAS_MM_GetLuType(VOS_VOID);

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, begin */
extern VOS_UINT32 NAS_MM_IsCcTiValid(VOS_VOID);
extern VOS_VOID NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(
    VOS_UINT32                          ulLaiChangeFlag,
    VOS_UINT8                           ucLuType
);
extern  VOS_VOID NAS_MM_ClearConnCtrlInfoExcEmgCall(VOS_UINT8 ucMMConnEstingPD);
/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, end */

VOS_UINT32  NAS_MM_IsCsEnableLau( VOS_VOID );

extern VOS_UINT8 NAS_MM_GetIdnnsType_CsfbMt(VOS_VOID);

extern VOS_UINT8 NAS_MM_SetPagingRspMobileId(
    VOS_UINT8                          *pucSndMsg,
    VOS_UINT16                         *pusMsgSize,
    MM_MOBILE_ID_STRU                  *pMobileId
);


VOS_UINT32  NAS_MM_IsNeedLauCsSigRel( VOS_VOID );

VOS_VOID NAS_MM_ProcConnFailLauAttmptCntLess4_RcvRelInd(
    RRC_REL_CAUSE_ENUM_UINT32                   enRelCauses
);

VOS_VOID NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(
    VOS_UINT32                          ulCurFobidnFlg
);

VOS_VOID NAS_MM_SndMmcRrConn_RcvRelInd(VOS_VOID);



extern VOS_UINT32  NAS_MM_IsNeedCmServiceRetry_RelIndResult(RRC_REL_CAUSE_ENUM_UINT32 enRelCause);
extern  VOS_UINT32  NAS_MM_IsAbleRecover_EstCnfFailResult(RRC_NAS_EST_RESULT_ENUM_UINT32 enEstResult);


VOS_VOID NAS_MM_InitCcoFallbackCtx(VOS_VOID);
extern VOS_VOID NAS_MM_RcvMmTimerProtectCsDetachExpired(VOS_VOID);
extern VOS_VOID NAS_MM_LocalDetach_MmInterRatChange(VOS_VOID);
extern VOS_VOID NAS_MM_LocalDetach(VOS_VOID);
extern VOS_VOID NAS_MM_StartDetachProtectingTimer(
    MMCMM_DETACH_REQ_STRU              *pstMsg
);

VOS_VOID Mm_Cell_S9_E49(
    VOS_VOID                           *pRcvMsg
);
VOS_VOID Mm_Cell_S10_E49(
    VOS_VOID                           *pRcvMsg
);
VOS_VOID Mm_Cell_S12_E49(
    VOS_VOID                           *pRcvMsg
);

extern VOS_VOID NAS_MM_RcvRrMmEstCnf_ExistCsDetachBuffer(
    RRMM_EST_CNF_STRU                  *pRrcEstCnf
);

VOS_UINT32 NAS_MM_IsNeedGmmProcUserDetach(VOS_VOID);

VOS_UINT32 NAS_MM_IsLauNeeded_NetModeChange(VOS_VOID);

VOS_UINT32 NAS_MM_IsEmergencyCallEndTrigLau(VOS_VOID);
VOS_VOID NAS_MM_RelEstingMmConn(
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause
);

VOS_VOID NAS_MM_RelBufferedServiceEstReq(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause
);

VOS_VOID NAS_MM_RelBufferedServiceEstReqExceptEmergencyCall(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause
);


VOS_UINT32 NAS_MM_NotifyBufferedServiceRRConnNotExist(VOS_VOID);

VOS_VOID NAS_MM_LocalDetach_MmNoImsi(VOS_VOID);

VOS_VOID Mm_Cell_S2_E15(
    VOS_VOID                           *pRcvMsg
);

VOS_UINT32 NAS_MM_IsDisableGprsCombineAttach(VOS_VOID);
VOS_VOID NAS_MM_RestartT3240_WaitForNetworkCommand(VOS_VOID);
VOS_VOID NAS_MM_ResumeMmStateToPreState_LocationUpdatingPending(VOS_VOID);

VOS_VOID NAS_MM_EndBufferedCSServiceExceptEmergencyCall_ImmediateAssignReject(VOS_VOID);


VOS_UINT8 NAS_MM_ProcessLuAfterCsConnectNotExist(VOS_VOID);

#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID NAS_MM_SndAcpuOmChangeTmsi(VOS_VOID);

VOS_VOID NAS_MM_SndAcpuOmFaultErrLogInd(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulDataLen,
    NAS_ERR_LOG_ALM_ID_ENUM_U16         usAlmId
);
VOS_VOID NAS_MM_CsPagingFailRecord(
    NAS_ERR_LOG_CS_PAGING_CAUSE_ENUM_U32    enCause
);
VOS_VOID NAS_MM_CsfbMtFailRecord(VOS_VOID);

VOS_VOID NAS_MM_IDResInfoRecord(
    VOS_UINT8                           ucIDType
);

VOS_VOID NAS_MM_ParseErrLogCsPagingInfo(
    VOS_VOID                     *pRcvMsg
);
VOS_VOID NAS_MM_RecordCsPagingFail_WaitForRrConnection(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult
);
VOS_VOID NAS_MM_SrvccFailRecord(
    NAS_ERR_LOG_SRVCC_FAIL_CAUSE_ENUM_UINT8                 enSrvccFailCause
);
#endif

VOS_VOID NAS_MM_RecordErrorLogInfo(
    NAS_ERR_LOG_BASE_STATE_ENUM_U32     enBaseState,
    VOS_UINT32                          ulCause
);
VOS_VOID NAS_MM_ClearErrorLogInfo(VOS_VOID);
VOS_VOID NAS_MM_FillCsfbMtInfo(
    NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32  enCsfbMtState,
    VOS_UINT32                          ulCause
);

VOS_VOID Mm_Cell_S1_E65(VOS_VOID *pRcvMsg);
VOS_VOID Mm_Cell_S25_E65(VOS_VOID  *pRcvMsg);
VOS_VOID Mm_Cell_S32_E32(
    VOS_VOID                           *pRcvMsg
);


VOS_VOID NAS_MM_SndMmcSimAuthFailInfo(
    NAS_MML_SIM_AUTH_FAIL_ENUM_UINT16   enSimFailValue
);

VOS_VOID NAS_MM_SndRrMmServiceAbortNotify(
    VOS_UINT32                          ulReceiverPid
);



VOS_VOID  NAS_MM_LogAuthInfo(
    VOS_UINT8                           ucRcvOpId,
    VOS_UINT8                           ucExpectOpId
);

VOS_VOID  NAS_MM_LogMmCtxInfo(VOS_VOID);



VOS_VOID  NAS_MM_ClearAuthInfo(VOS_VOID);

RRC_NAS_EST_RESULT_ENUM_UINT32 NAS_MM_GetEstCnfResult(VOS_VOID);
VOS_VOID NAS_MM_SetEstCnfResult(RRC_NAS_EST_RESULT_ENUM_UINT32 enEstCnfFailCause);

/* Added by n00355355 for 呼叫重建, 2015-9-29, begin */
VOS_UINT32 NAS_MM_GetTransactionEnqSenderPid(VOS_VOID);
VOS_VOID NAS_MM_SetTransactionEnqSenderPid(VOS_UINT32 ulSenderPid);
/* Added by n00355355 for 呼叫重建, 2015-9-29, end */


VOS_VOID NAS_MM_RcvProtectingMtCsfbPagingProcedureExpired(VOS_VOID);



/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-22, begin */
#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MM_RcvMmTimerGetHoSecuInfoCnfExpired(VOS_VOID);

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, begin */
VOS_VOID NAS_MM_ConvertToLmmSrvccStatus(
    NAS_MMCC_SRVCC_STATUS_ENUM_UINT32   enSrvccStatus,
    MM_LMM_SRVCC_STATUS_ENUM_UINT32    *penMmlSrvccStatus
);

VOS_VOID NAS_MM_SndLmmSrvccStatusNotify(
    NAS_MMCC_SRVCC_STATUS_ENUM_UINT32   enSrvccStatus
);

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, end */

VOS_UINT8 NAS_MM_IsNeedSetCsmtFlg(VOS_VOID);
VOS_UINT8 NAS_MM_IsNeedSetCsmoFlg(VOS_VOID);
VOS_VOID NAS_MM_SetCsfbAdditionalUpdateParameters(
    VOS_UINT8                           ucCsmtFlg,
    VOS_UINT8                           ucCsmoFlg,
    VOS_UINT16                         *pusMsgSize,
    VOS_UINT8                          *pucSndMsg
);
#endif

#if (FEATURE_ON == FEATURE_LTE)
extern VOS_UINT8 NAS_MM_GetSrvccFlg(VOS_VOID);
extern VOS_VOID NAS_MM_SetSrvccFlg(
    VOS_UINT8                           ucFlg
);
#endif

VOS_UINT8 NAS_MM_GetRcvSrvccCallInfoFlg(VOS_VOID);
VOS_VOID NAS_MM_SetRcvSrvccCallInfoFlg(
    VOS_UINT8                           ucFlg
);

#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID NAS_MM_RcvMmcSrvccInfoNtf(
    VOS_VOID                           *pstRcvMsg
);


VOS_VOID NAS_MM_RcvCcSrvccCallInfoNtf(
    MMCC_SRVCC_CALL_INFO_NOTIFY_STRU   *pstCcMsg
);
#endif
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-22, end */

VOS_VOID NAS_MM_RcvMmcLauReq(
    VOS_VOID                           *pstRcvMsg
);

VOS_UINT8 NAS_MM_GetCsfbMtLauFlg(VOS_VOID);
VOS_VOID NAS_MM_SetCsfbMtLauFlg(
    VOS_UINT8                           ucFlg
);



VOS_UINT32 Mm_IsMultiSrvCollisionAllow(NAS_MM_CONN_CTRL_ENUM_UINT8 ucMmConnCtrl);
/* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
VOS_VOID NAS_MM_ProcResumeToHRPD(
    MMCMM_RESUME_IND_STRU              *pstResumeMsg
);
#endif
/* Added by s00246516 for L-C互操作项目, 2014-01-27, End */

/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-17, begin */
VOS_VOID NAS_MM_ProcMmcMmSysInfoInd_CsAttachNotAllow( VOS_VOID );


VOS_UINT32 NAS_MM_IsCsForbidden( VOS_VOID );

VOS_UINT8 NAS_MM_IsCsNotSupport(
    VOS_VOID                           *pRcvMsg
);

VOS_VOID NAS_MM_ProcMmcMmSysInfoInd_CsRegisterRestrict( VOS_VOID );

VOS_BOOL NAS_MM_IsIdleState( VOS_VOID );

VOS_VOID NAS_MM_UpdateT3212Value_RcvGuSysInfo(
    VOS_UINT8                           ucLRTimerT3212
);

VOS_VOID NAS_MM_UpdateT3212Value_RcvLauAccept(
    VOS_UINT8                            ucMsgTimerValue
);

VOS_UINT32 NAS_MM_IsNeedUpdateT3212Value_RcvGuSysInfo(VOS_VOID);

extern VOS_UINT32 NAS_MM_IsNeedStartT3212RcvGmmDetachInd( VOS_VOID );

VOS_UINT32 NAS_MM_IsNeedProcBufferedCsDetach_RcvLauEstCnf(
    RRC_NAS_EST_RESULT_ENUM_UINT32      enEstCnfResult
);

VOS_VOID NAS_MM_SetMsNetworkFeatureSupportIE(
    VOS_UINT16                         *pusMsgSize,
    VOS_UINT8                          *pucSndMsg
);
VOS_UINT32 NAS_MM_IsNeedSetMsNetworkFeatureSupportIELauReq(VOS_VOID);



VOS_VOID NAS_MM_UpdateNetModeInfo_RcvGuSysInfo(
    VOS_UINT8                           ucNetworkOperationMode
);

VOS_UINT8 NAS_MM_IsNeedClearAttemptCounter( VOS_VOID );

VOS_VOID NAS_MM_SndMmcForbidenRslt(VOS_VOID);

VOS_VOID NAS_MM_RcvSysInfoAccessBar_ProcBufferedCsService(VOS_VOID);

/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-17, end */

MM_LAI_STRU *NAS_MM_GetAttemptUpdateLaiInfo(VOS_VOID);

VOS_VOID NAS_MM_InitLaiInfo(
    MM_LAI_STRU                        *pstLai
);

VOS_UINT32 NAS_MM_IsSameLaiInfo(
    MM_LAI_STRU                        *pstCurrLai,
    MM_LAI_STRU                        *pstOldLai
);

VOS_VOID NAS_MM_LocationUpdateAttemptCounter(
    VOS_UINT32                          ulMmCause
);
VOS_VOID NAS_MM_UpdateLauRetryFlg_RcvRelInd(
    RRMM_REL_IND_STRU                  *pRrcRelInd
);

extern VOS_VOID NAS_MM_ProcCsfbServiceStatusChange(
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCurStatus,
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enTargetStatus
);

NAS_MML_LAI_STRU *NAS_MM_GetAllocT3212ValueLaiInfo(VOS_VOID);
VOS_VOID NAS_MM_SetNetworkT3212ValueType(
    NAS_MM_NETWORK_T3212_VALUE_TYPE_ENUM_UINT8              enT3212ValueType
);
NAS_MM_NETWORK_T3212_VALUE_TYPE_ENUM_UINT8 NAS_MM_GetNetworkT3212ValueType(VOS_VOID);

VOS_UINT32 NAS_MM_GetNetworkAllocT3212Len(VOS_VOID);
VOS_VOID  NAS_MM_SetNetworkAllocT3212Len(
    VOS_UINT32                          ulNetworkAllocT3212Len
);
VOS_VOID  NAS_MM_LogT3212Info(VOS_VOID);
VOS_VOID NAS_MM_StartT3212Timer(
    NAS_MM_T3212_START_SCENE_ENUM_UINT32                    enT3212StartScean
);
VOS_VOID NAS_MM_IncreaseT3212Counter(VOS_VOID);
VOS_VOID NAS_MM_InitT3212Counter(VOS_VOID);
VOS_UINT32 NAS_MM_GetT3212StartCount(VOS_VOID);

VOS_UINT32 NAS_MM_GetNetworkT3212RandLen(VOS_VOID);
VOS_VOID  NAS_MM_SetNetworkT3212RandLen(
    VOS_UINT32                          ulCurrT3212Len
);
VOS_UINT32 NAS_MM_IsNeedUseTheNvimT3212TimerLen(
    NAS_MM_T3212_START_SCENE_ENUM_UINT32                    enT3212StartScean
);

VOS_UINT32 NAS_MM_MapT3212StartSceneToCtrlBitIndex(
    NAS_MM_T3212_START_SCENE_ENUM_UINT32                    enT3212StartScene
);

VOS_UINT32 NAS_MM_GetT3212StartSceneCtrlBitIndexValue(
    VOS_UINT32                          ulT3212StartSceneCtrlBitIndex
);

VOS_UINT32 NAS_MM_GetT3212StartSceneTimerLen(
    NAS_MM_T3212_START_SCENE_ENUM_UINT32                    enT3212StartScean,
    NAS_MM_T3212_LEN_TYPE_ENUM_UINT8                       *penT3212LenType
);
#if(FEATURE_ON == FEATURE_DSDS)
extern VOS_VOID NAS_MM_SndBeginSessionNotify(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enSessionType
);

extern VOS_VOID NAS_MM_SndEndSessionNotify(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enSessionType
);

extern VOS_VOID NAS_MM_NotifySessionAccordingStateChg(
    VOS_UINT8                           ucCurState,
    VOS_UINT8                           ucTargetState
);

extern VOS_VOID NAS_MM_RcvMmccBeginSessionNotify(
    MMCC_BEGIN_SESSION_NOTIFY_STRU     *pstRcvMsg
);

extern VOS_VOID NAS_MM_RcvMmccEndSessionNotify(
    MMCC_END_SESSION_NOTIFY_STRU     *pstRcvMsg
);

extern VOS_VOID NAS_MM_RcvMmssBeginSessionNotify(
    MMSS_BEGIN_SESSION_NOTIFY_STRU     *pstRcvMsg
);

extern VOS_VOID NAS_MM_RcvMmssEndSessionNotify(
    MMSS_END_SESSION_NOTIFY_STRU       *pstRcvMsg
);

extern VOS_VOID NAS_MM_RcvMmsmsBeginSessionNotify(
    MMSMS_BEGIN_SESSION_NOTIFY_STRU    *pstRcvMsg
);

extern VOS_VOID NAS_MM_RcvMmsmsEndSessionNotify(
    MMSMS_END_SESSION_NOTIFY_STRU      *pstRcvMsg
);

#endif
VOS_UINT8 NAS_MM_CheckCallStatusNtyValid(
    MMCC_CALL_STATUS_NTF_STRU          *pstCallStatusNty
);
VOS_UINT8 NAS_MM_CheckSsStatusNtyValid(
    MMSS_STATUS_NTY_STRU               *pstSsStatusNty
);
VOS_VOID NAS_MM_RcvMmccCallStatusNty(
    MMCC_CALL_STATUS_NTF_STRU          *pstCallStatusNty
);
VOS_VOID NAS_MM_RcvMmssStatusNty(
    MMSS_STATUS_NTY_STRU               *pstSsStatusNty
);
VOS_VOID NAS_MM_ParseT3246IE(
    VOS_UINT8                          *pucRcvMsg,                          /* 当前处理的消息                           */
    VOS_UINT16                          usMsgSize,                          /* 消息长度,以字节为单位                    */
    VOS_UINT8                          *pucIsT3246Exist
);

/* Added by n00355355 for 呼叫重建, 2015-9-17, begin */
VOS_VOID NAS_MM_RcvMmccGetCallInfoCnf(
    MMCC_GET_CALL_INFO_CNF_STRU        *pstMsg
);

/* Added by n00355355 for 呼叫重建, 2015-9-17, end */



NAS_MMCM_REL_CAUSE_ENUM_UINT32 NAS_MM_ConvertRrcRelCauseToMmCcRelCause(
    RRC_REL_CAUSE_ENUM_UINT32           enRrcRelCause
);
NAS_MMCM_REL_CAUSE_ENUM_UINT32 NAS_MM_ConvertEstCnfRsltToMmCcRelCause(
    RRC_NAS_EST_RESULT_ENUM_UINT32     enEstCnfRslt
);
NAS_MM_T3212_START_SCENE_ENUM_UINT32 NAS_MM_ConvertLauEstCnfRsltToT3212StartScean(
    RRC_NAS_EST_RESULT_ENUM_UINT32      enEstCnfRslt
);
#if   (FEATURE_ON == FEATURE_LTE)
NAS_MMCM_REL_CAUSE_ENUM_UINT32 NAS_MM_ConvertCsfbSrvRsltToMmCcRelCause(
    LMM_MM_CSFB_SERVICE_END_IND_STRU   *pstCsfbEndInd
);
#endif
VOS_UINT32 NAS_MM_IsGsmOnlyEstCnfRslt(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult
);

VOS_UINT8 NAS_MM_RcvCspagingInd_PreProc(
    VOS_VOID                           *pstRcvMsg
);

VOS_UINT8 NAS_MM_IsHoBetweenGU(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSrcRatType,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRatType,
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause
);

VOS_VOID NAS_MM_StartHoWaitSysInfoTimer(
    VOS_UINT8                           ucTimerId
);


VOS_VOID NAS_MM_SndRrcTransactionStatusNotify(
    VOS_UINT32                          ulRcvPid,
    RRMM_TRANSACTION_STATUS_ENUM_UINT8  enTranStatus
);

VOS_UINT32 NAS_MM_GetRrcPidFromCurrRatType(
    VOS_UINT32                         *pulPid
);

VOS_VOID NAS_MM_SndCcRrcConnectRelInd(VOS_VOID);

VOS_UINT32 NAS_MM_IsNeedLauFirst_CsfbMoEmcExist(VOS_VOID);
VOS_VOID NAS_MM_SndMmcCsRegResultInd_CsfbMoEmcExist(VOS_VOID);
VOS_UINT8 NAS_MM_IsLauRejNeedRetry(
    VOS_UINT8                           ucCause
);
VOS_VOID NAS_MM_SndTransactionStatusNotify(
    RRMM_TRANSACTION_STATUS_ENUM_UINT8  enTranStatus
);
VOS_VOID NAS_MM_ConvertCallStatusToTransactionStatus(
    MMCC_CALL_STATUS_ENUM_UINT8         enCallStatus,
    RRMM_TRANSACTION_STATUS_ENUM_UINT8 *penTransStatus
);
VOS_VOID NAS_MM_ConvertSsStatusToTransactionStatus(
    MMSS_STATUS_ENUM_UINT8              enSsStatus,
    RRMM_TRANSACTION_STATUS_ENUM_UINT8 *penTransStatus
);
VOS_VOID NAS_MM_UpdateCallStatus_RcvCcEstReq(
    MMCC_EST_REQ_STRU                   *pstEstReq
);
VOS_VOID NAS_MM_UpdateCallStatus_RcvCallStatusNty(
    MMCC_CALL_STATUS_ENUM_UINT8         enCallStatus
);
VOS_VOID NAS_MM_UpdateSsStatus_RcvSsStatusNty(
    MMSS_STATUS_ENUM_UINT8              enSsStatus
);

/* Added by n00355355 for 呼叫重建, 2015-9-17, begin */
VOS_VOID NAS_MM_SndAsCsTransactionStatus(
    RRC_NAS_CS_TRANSACTION_ENUM_UINT8   enCsTransactionStatus,
    VOS_UINT32                          ulSenderEnqPid,
    VOS_UINT8                           ucIsCallActive
);

VOS_VOID NAS_MM_RcvRrMmGetTransactionReq(
    RRMM_TRANSACTION_INFO_ENQ_STRU      *pMsgHeader
);


/* Added by n00355355 for 呼叫重建, 2015-9-17, end */

VOS_VOID NAS_MM_ProcT3213AttemptCounter(
    VOS_UINT32  ulT3213Status
);
VOS_VOID NAS_MM_ProcLuAttemptCounter(
    RRC_NAS_EST_RESULT_ENUM_UINT32 enEstResult
);
VOS_VOID NAS_MM_ComProcPsRandomAccessFailCnt(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enRegFailCause,
    VOS_UINT32                          ulRegAttemptCounter
);

VOS_VOID NAS_MM_ProcLauEstCnfNoRf(VOS_VOID);

VOS_VOID NAS_MM_ConvertToMmlSessionType(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8   enMmSessionType,
    NAS_MML_SESSION_TYPE_ENUM_UINT8  *penMmlSessionType
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

#endif /*End of __MM_EXT_H__*/

