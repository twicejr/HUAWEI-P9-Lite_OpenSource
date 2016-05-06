/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File Name       : NasLmmPubMEntry.h
    Description     : NasLmmPubMEntry.c header file
    History     :
******************************************************************************/

#ifndef __NASLMMPUBMENTRY_H__
#define __NASLMMPUBMENTRY_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include    "vos.h"
#include    "NasLmmPublic.h"
#include    "NasLmmPubMFsm.h"
#include    "NasEmmPubUCnMsgDecode.h"

#include    "LRrcLNasInterface.h"
#include    "EmmEsmInterface.h"
#include    "EmmRabmInterface.h"
#include    "NasLmmPubMIntraMsg.h"
#include    "NasEmmcEmmInterface.h"
#include    "NasEmmSecuInterface.h"
#include    "NasLmmPubMNvim.h"

#include    "NasEmmSecuOm.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define NAS_EMM_GET_USIM_FILE_TYPE()        g_enReadUsimFileType
#define NAS_EMM_GET_SEND_COUNTER()          g_ulSendMsgCounter
#define NAS_EMM_GET_USIM_SECU_FILE_LEN()    g_ulUsimSecuFileLen

#define NAS_LMM_GET_USIM_EPS_SECU_CONTEXT_ADDR()      g_aucUsimSecuContext


#define NAS_EMM_SOFT_USIM_SEND_MSG_NUM  1

#define NAS_EMM_INTRA_APP_START_OPID    0xffff

#define NAS_EMM_PROC_OVER               1                   /* 消息已被处理 */
#define NAS_EMM_PORC_NO                 0                   /* 消息没有处理 */

#define NAS_EMM_SEND_MMC_ERR            VOS_ERR
#define NAS_EMM_SEND_MMC_OK             VOS_OK

#define NAS_EMM_SEND_RRC_ERR            VOS_ERR
#define NAS_EMM_SEND_RRC_OK             VOS_OK

#define NAS_EMM_BIT_NO_SLCT             0
#define NAS_EMM_BIT_SLCT                1

#define NAS_EMM_IS_SUSPEND              1
#define NAS_EMM_NOT_SUSPEND             0
#define NAS_LMM_MAX_MSG_PROC_LOOP        0x08
#define NAS_LMM_MSGID_DPID_POS           0x00FFFFFF

#define NAS_LMM_CN_MSG_MT_POS            0x1
#define NAS_LMM_INTRA_DATA_IND_MT_POS    0x2

#define NAS_LMM_CONTINUE_TO_PROC_BUF_MSG 1
#define NAS_LMM_STOP_PROCING_BUF_MSG     0

#define NAS_USIM_AVAIL                  1
#define NAS_USIM_INAVAIL                0
#define NAS_USIM_INAVAIL_CS             9

#define NAS_LMM_SERTAB_SUPPORT_NONE      0


#define NAS_LMM_BYTE_FF                 0xFF                /* 1111  1111  */
#define NAS_LMM_LOW_HALF_BYTE_F         0x0F                /* 0000  1111  */
#define NAS_LMM_LOW_3_BITS_F            0x07                /* 0000  0111  */

/*
#define NAS_LMM_TIMER_EXP_EVT_SKELETON   \
            (0x00000000UL | (VOS_PID_TIMER << NAS_LMM_MOVEMENT_16_BITS))
*/

#define NAS_LMM_SER_TABLE_UPLMN_BIT     20
#define NAS_LMM_SER_TABLE_OPLMN_BIT     42
#define NAS_LMM_SER_TABLE_HPLMNACT_BIT  43
#define NAS_LMM_SER_TABLE_LPPLMNSI_BIT  74
#define NAS_LMM_SER_TABLE_EMMINFO_BIT   85

#define NAS_LMM_ESM_CAUSE_PDN_CONNECTION_DOES_NOT_EXIST    54


/*
BYTE1 ，消息类型：
0x00-模块间消息
0x01-保留
0x02-空口消息
0x03-普通命令
0x04-实时监控命令
0x05-关键事件
0x06-透明命令
*/


#define MSG_TYPE_BETWEEN_PID            0x00000000

#define NAS_LMM_CMP_MSGID(NAS_LMM_MSG_HEAD, ucMsgId)\
            (NAS_LMM_MSG_HEAD |ucMsgId)




#define NAS_LMM_PARA_FSM_ID_INVALID(enParalFsmId)\
            (NAS_LMM_PARALLEL_FSM_BUTT <= enParalFsmId)


/* ID_BETWEEN_MODEL_MSGID => EVENT TYPE */
#define NAS_LMM_GET_BT_MD_ET(ID_BT_MD_MSGID)\
            (ID_BT_MD_MSGID & NAS_LMM_MSGID_DPID_POS)

#define NAS_LMM_GET_BT_RCV_MD_ET(ID_BT_MD_MSGID)\
            (ID_BT_MD_MSGID & NAS_LMM_MSGID_DPID_POS)

#define NAS_LMM_GET_BT_SND_MD_ET(ID_BT_MD_MSGID)\
            (ID_BT_MD_MSGID & NAS_LMM_MSGID_DPID_POS)

#define NAS_LMM_GET_CN_ET(ID_BT_MD_MSGID, CN_MSG_TYPE)\
            (NAS_LMM_GET_BT_MD_ET(ID_BT_MD_MSGID) | CN_MSG_TYPE)

#define NAS_LMM_GET_RRC_MM_DATA_IND_CN_ET(CN_MSG_TYPE)\
            (NAS_LMM_GET_CN_ET((ID_LRRC_LMM_DATA_IND), (CN_MSG_TYPE<< NAS_LMM_MOVEMENT_24_BITS)))


/* TIMER EXP MSG =>  EVENT TYPE * */
/*
#define NAS_LMM_TIMER_EXP_MSG_ET(usNasMmTi)\
            (NAS_LMM_TIMER_EXP_EVT_SKELETON | usNasMmTi)
*/
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
  结构类型    : NAS_LMM_LOCAL_DETACH_FLAG_ENUM
  使用说明    : CMCC需求，无论L当前是否满足能够发起空口DETACH的条件，只要此标识
                有效，LMM在收到MMC的DETACH请求时即直接做本地DETACH，此标识的值由
                GU通过MML接口提供
*****************************************************************************/

enum NAS_LMM_LOCAL_DETACH_FLAG_ENUM
{
    NAS_LMM_LOCAL_DETACH_FLAG_INVALID                = 0X00,
    NAS_LMM_LOCAL_DETACH_FLAG_VALID                  = 0X01,
    NAS_LMM_LOCAL_DETACH_FLAG_BUTT
};
typedef  VOS_UINT8    NAS_LMM_LOCAL_DETACH_FLAG_ENUM_UINT8;

/*****************************************************************************
结构类型    : NAS_EMM_EVENT_TYPE_ENUM
使用说明    : OSA, EMM的内部消息ID, 可能再组合上其他信息, 形成事件类型
               EVENT_TYPE, PUBLIC_U模块根据当前状态和事件类型调用各模块
               提供的函数



NAS_EMM_EVENT_TYPE_ENUM
-----------------------------------------------------------
  字节高位                                      字节低位
-----------------------------------------------------------
| BYTE4高4位 + 0000 |  BYTE3    |   BYTE2    |    BYTE1   |
-----------------------------------------------------------
0000：协议模块间消息|  源模块号 | CN MSG TYPE| 消息号0-255
-----------------------------------------------------------
0001：L2 LOG        |           |            |
-----------------------------------------------------------
0010：空口消息      |           |            |
-----------------------------------------------------------
0011：普通命令      |           |            |
-----------------------------------------------------------
0100：实时监控命令  |           |            |
-----------------------------------------------------------
0101：关键事件      |           |            | 保留不用
-----------------------------------------------------------


NAS_EMM_EVENT_TYPE_ENUM 与 ulMsgID的结构的区别:
BYTE2:  ulMsgID中的目的模块号在一定是MM的模块号，
        NAS_EMM_EVENT_TYPE_ENUM中改为 CN MSG TYPE；

ulMsgID包括4部分:
---------------------------------------------------------->
  字节高位                                      字节低位
-----------------------------------------------------------
|   BYTE1           |   BYTE2   |   BYTE3    |    BYTE4   |
-----------------------------------------------------------
0000：协议模块间消息|  源模块号 |  目的模块号| 消息号0-255
-----------------------------------------------------------

BYTE1 ，消息类型：
0x00-模块间消息
0x01-保留
0x02-空口消息
0x03-普通命令
0x04-实时监控命令
0x05-关键事件
0x06-透明命令

BYTE2：源模块ID，取值参见2.1，2.2节
BYTE3：目的模块，取值范围同BYTE2
BYTE4：消息号，0~255


TIMER MSG的EVENT TYPE结构
-----------------------------------------------------------
  字节高位                                      字节低位
-----------------------------------------------------------
| BYTE4高4位 + 0000 |  BYTE3    |   BYTE2    |    BYTE1   |
-----------------------------------------------------------
00FF：TIMER 消息   |VOS_PID_TIMER|  0000     |     TI
-----------------------------------------------------------
同: NAS_LMM_TIMER_EXP_EVT_SKELETON

*****************************************************************************/

enum NAS_LMM_USIM_FILE_TYPE_ENUM
{
    NAS_LMM_USIM_MANDATORY_FILE                 = 0, /*必读文件*/
    NAS_LMM_USIM_OPTIONAL_FILE                  = 1, /*可选文件*/
    NAS_LMM_USIM_TYPE_BUTT
};
typedef  VOS_UINT32    NAS_LMM_USIM_FILE_TYPE_ENUM_UINT32;

typedef  VOS_UINT32    NAS_LMM_EVENT_TYPE_ENUM_UINT32;
typedef  VOS_UINT32    NAS_EMMC_EVENT_TYPE_ENUM_UINT32;
typedef  VOS_UINT32    NAS_EMM_EVENT_TYPE_ENUM_UINT32;



/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*************************************************
结构描述: Errorlog建链失败以及直传失败时候处理结构
作    者: lifuxin 00253982 2015-02-10s
*************************************************/
typedef VOS_VOID (* NAS_LMM_ERRLOG_ACT_FUN )
(
    VOS_VOID*,
    EMM_OM_ERRLOG_TYPE_ENUM_UINT16
);

typedef struct
{
    NAS_LMM_MAIN_STATE_ENUM_UINT16              enCurState;
    NAS_LMM_ERRLOG_ACT_FUN                      pfErrlogFun;
}NAS_LMM_ERRLOG_ACT_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern  NAS_LMM_USIM_FILE_TYPE_ENUM_UINT32 g_enReadUsimFileType;
extern  VOS_UINT32 g_ulUsimSecuFileLen;

extern  VOS_UINT8  g_aucUsimSecuContext[NAS_NVIM_SECU_CONTEXT_MAX_LEN];


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern  VOS_UINT32  MM_FidInit (    enum VOS_INIT_PHASE_DEFINE ip );

#if (VOS_OS_VER == VOS_WIN32)/*在PC环境下，才会调用PID初始化函数，单板环境下，由GU MM负责初始化*/
extern  VOS_UINT32 NAS_MMC_PidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern  VOS_UINT32 NAS_GMM_PidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern  VOS_UINT32 NAS_GUMM_PidInit ( enum VOS_INIT_PHASE_DEFINE ip );

extern  VOS_UINT32 NAS_SMS_PidInit ( enum VOS_INIT_PHASE_DEFINE ip );

extern void   NAS_MmcStub_TaskEntry (MsgBlock *pMsg);
extern void   NAS_GmmStub_TaskEntry (MsgBlock *pMsg);
extern VOS_VOID  NAS_GUMmStub_TaskEntry( MsgBlock* pMsg );

VOS_VOID  NAS_SmsStub_TaskEntry( MsgBlock* pMsg );
#endif

extern  VOS_UINT32  NAS_LMM_Entry(       MsgBlock *pMsg);
extern  VOS_UINT32  NAS_LMM_MsgHandle(   MsgBlock *          pMsg,
                                        VOS_UINT32          ulEventType);
extern  VOS_UINT32  NAS_LMM_GetEventType(MsgBlock                        *pMsg,
                                        NAS_EMM_EVENT_TYPE_ENUM_UINT32  *pulEmmEt );
/*extern  VOS_VOID    NAS_LMM_PrintCnMsg(  LRRC_LMM_DATA_IND_STRU                *pMsg );*/
extern  VOS_UINT32  NAS_LMM_MsgPreProcess(MsgBlock *         pMsg );
extern  VOS_UINT32  NAS_LMM_PreProcAppStopReq(   MsgBlock  * pMsg);
extern  VOS_UINT32  NAS_LMM_PreProcAppStartReq(   MsgBlock  * pMsg);
/* leixiantiao 00258641 降低圈复杂度 2014-7-30 begin */
extern VOS_UINT32  NAS_LMM_ProcAppDetReq
(
    const MMC_LMM_DETACH_REQ_STRU            *pstAppDetReq
);
/* leixiantiao 00258641 降低圈复杂度 2014-7-30 end */

extern  VOS_UINT32  NAS_LMM_PreProcAppDetReq(MsgBlock  * pMsg);
extern  VOS_UINT32  NAS_LMM_PreProcIntraSystemInfoInd(MsgBlock  * pMsg);
extern  VOS_UINT32  NAS_LMM_IntraMsgProcess(VOS_VOID);
extern  VOS_UINT32  NAS_LMM_BufMsgProcess(VOS_VOID);
extern  VOS_UINT32  NAS_LMM_EmmBufMsgProcess(    VOS_VOID );
extern  VOS_UINT32  NAS_LMM_MmcBufMsgProcess(    VOS_VOID);

/*extern  VOS_UINT32  NAS_EMM_JudgeFirstBufMsgCanBeProc(  NAS_EMM_EVENT_TYPE_ENUM_UINT32  ulEmmEt );
 */
extern  VOS_VOID    NAS_LMM_PUBM_Init(           VOS_VOID );
extern  VOS_VOID    NAS_LMM_PUBM_Init_FidInit(   VOS_VOID );
extern  VOS_VOID    NAS_LMM_MainContextInit(     VOS_VOID );
extern  VOS_VOID    NAS_LMM_AuxFsmInit(          VOS_VOID);
extern  VOS_VOID    NAS_LMM_TimerInit(           VOS_VOID);
extern  VOS_VOID    NAS_LMM_IntraMsgQueueInit(   VOS_VOID);
extern  VOS_UINT32  NAS_EMM_JudgeStableState(   VOS_VOID);
/* H41410 FRO UE MODE 此函数无用
extern  VOS_VOID    NAS_LMM_SmRabmAbnormalClearEmmSource(  VOS_VOID);*/
extern  VOS_UINT32  NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf( MsgBlock  * pMsg);
extern  VOS_UINT32  NAS_LMM_MsNullSsNullReadingUsimTimerExp (MsgBlock  * pMsg);
extern  VOS_VOID    NAS_LMM_EmmAndMmcGlobInfoClear( VOS_VOID );
extern  VOS_VOID    NAS_LMM_EmmSubModGlobInit(VOS_VOID );
extern VOS_VOID  NAS_LMM_EmmSubModGlobClear(VOS_VOID);
extern  VOS_UINT32  NAS_LMM_MsNullSsWaitUsimReadyMsgUsimStatusInd( VOS_VOID );
extern  VOS_UINT32  NAS_LMM_PreProcUsimSetCnf(   MsgBlock  * pMsg);
extern  VOS_VOID    NAS_LMM_SetImsiUnavail( VOS_VOID );

extern  VOS_VOID  NAS_LMM_ReadUsimEmmInfoFile( VOS_VOID );
extern  VOS_VOID  NAS_LMM_FreeDynMem( VOS_VOID );
extern  VOS_VOID  NAS_LMM_SubModFreeDyn( VOS_VOID );
extern  VOS_VOID  NAS_LMM_SendRabmRrcConRelInd(EMM_ERABM_REL_CAUSE_ENUM_UINT32      enRelCause);
extern  VOS_VOID  NAS_LMM_SendCssStopInd( VOS_VOID );
extern  VOS_VOID  NAS_LMM_SendCssStartInd( VOS_VOID );
extern  VOS_UINT32  NAS_LMM_PreProcMsgUsimStatusInd( MsgBlock  *pMsg );

/*extern  VOS_VOID    NAS_LMM_ProcUsimStatusIndWhenUsimInvalid( VOS_VOID );*/
extern  VOS_VOID    NAS_LMM_PUBM_ClearResource(VOS_VOID);
extern  VOS_VOID    NAS_LMM_DeregReleaseResource(VOS_VOID);
extern  VOS_UINT32  NAS_LMM_MsRegSsWaitAccessGrantIndMsgUsimStausInd(VOS_VOID);
extern  VOS_UINT32  NAS_LMM_MsRegInitSsAttachWaitEsmPdnRspMsgUsimStausInd(VOS_VOID);
extern  VOS_UINT32  NAS_LMM_MsAnyStateSsWaitRrcRelIndMsgUsimStausInd(VOS_VOID);
extern  VOS_VOID    NAS_EMM_SendDetachReqMo(VOS_VOID);
extern  VOS_VOID    NAS_EMM_ProcLocalNoUsim( VOS_VOID );
extern  VOS_UINT32  NAS_EMM_PreProcMsgDelForbTaTimerExpire( MsgBlock *pMsg );
extern  VOS_UINT32  NAS_EMM_PreProcMsgWaitSyscfgCnfTimerExpire( MsgBlock *pMsg );
extern  VOS_UINT32  NAS_LMM_PreProcMmcRelReq( MsgBlock *          pMsg );
extern  VOS_UINT32  NAS_EMM_PreProcMsgT3416Exp     ( MsgBlock *        pMsg );
extern  VOS_UINT32  NAS_EMM_PreProcMsgSwithOffTimerExp( MsgBlock *        pMsg );
extern  VOS_UINT32  NAS_LMM_MsResumeSsResumeRrcOriWaitSysInfoIndMsgUsimStausInd( VOS_VOID );
extern VOS_UINT32 NAS_LMM_PreProcInfoChangeNotifyReq
(
    MsgBlock                           *pstMsg
);
extern VOS_UINT32  NAS_LMM_PreProcRrcSysCfgCnf( MsgBlock  *pMsg );
extern VOS_UINT32  NAS_LMM_PreProcMmcSysCfgReq( MsgBlock  *pMsg );
extern VOS_UINT32  NAS_LMM_SendMmcSysCfgCnf( MMC_LMM_RESULT_ID_ENUM_UINT32 ulRst );
extern VOS_VOID  NAS_LMM_SaveCurRatToPreRat(VOS_VOID );
extern VOS_UINT32  NAS_LMM_SendRrcSysCfgReq( MsgBlock  *pMsg );
extern VOS_UINT32  NAS_LMM_PreProcMsgAppMmAttachReq( MsgBlock *        pMsg );
extern VOS_VOID NAS_LMM_ImsiDetachReleaseResource( VOS_VOID );
extern MMC_LMM_ATTACH_RSLT_ENUM_UINT32  NAS_LMM_SupendResumeAttachRslt( MsgBlock  *pMsg );
extern VOS_VOID  NAS_EMM_SendLrrcOssStateReq( VOS_VOID );
extern VOS_UINT32  NAS_LMM_PreProcMmcOocStateReq( MsgBlock  *pMsg );
extern VOS_UINT32  NAS_LMM_PreProcRrcDataCnf( MsgBlock  *pMsg );

extern VOS_UINT32  NAS_LMM_PreProcIntraCoverageLostInd( MsgBlock  *pMsg );
extern VOS_UINT32  NAS_EMM_PreProcMsgT3402Exp( MsgBlock *          pMsg );

extern VOS_UINT32  NAS_EMM_PreProcMsgCsfbDelayTimerExp( MsgBlock *          pMsg );

extern VOS_UINT32  NAS_LMM_PreProcrRrcDataInd      ( MsgBlock *        pMsg );
extern  VOS_UINT32  NAS_LMM_PreProcMsgEsmClrEsmPrcResNotify
(
    MsgBlock                           *pMsg
);

extern VOS_UINT32 NAS_EMM_IsSuspended( VOS_VOID );

extern VOS_VOID  NAS_LMM_SendMmcSuspendInfoChangeRatChange(
                LMM_MMC_RAT_CHANGE_TYPE_ENUM_UINT32 ulRatChangeType);
extern VOS_VOID  NAS_EMM_TcSendRelInd(VOS_VOID);
extern VOS_UINT32 NAS_LMM_RevMmcModemInfoReq(MsgBlock *  pMsg);

extern VOS_UINT32  NAS_LMM_MsSuspendOrResumePreProcAppDetReq
(
    const MMC_LMM_DETACH_REQ_STRU            *pstAppDetReq
);

extern VOS_UINT32  NAS_LMM_IsSvlteOrLcNeedLocalDetach(VOS_VOID);

extern VOS_VOID  NAS_LMM_MsRegSsAnyLocalDetStateTrans(VOS_VOID);

extern VOS_UINT32  NAS_LMM_SvlteOrLcPsLocalDetachProc
(
    const MMC_LMM_DETACH_REQ_STRU            *pstAppDetReq
);


extern VOS_UINT32  NAS_EMM_PreProcMsgRrcMmEstCnf(MsgBlock * pMsg);
extern VOS_UINT32  NAS_EMM_PreProcMsgTIWaitRrcConnTO(MsgBlock * pMsg);
extern VOS_UINT32  NAS_EMM_PreProcMsgRrcMmRelCnf(MsgBlock * pMsg);
extern VOS_UINT32  NAS_EMM_PreProcMsgTiWaitRrcRelTO(MsgBlock * pMsg);
extern VOS_UINT32  NAS_EMM_PreProcMsgWaitRrcRel3440TO(MsgBlock * pMsg);
extern VOS_UINT32  NAS_EMM_PreProcMsgReAttachDelayTO(MsgBlock * pMsg);

/*chengmin for L signal report begin*/
extern VOS_UINT32 NAS_LMM_SendRrcCellSignReportNotify(VOS_UINT8 ucMinRptTimerInterval, VOS_UINT8 ucSignThreshold);
extern VOS_UINT32 NAS_LMM_SendMccCellSignReportInd(MsgBlock  *pstMsg);
extern VOS_UINT32 NAS_EMM_PreProcMsgRrcCellSignReportInd(MsgBlock  *pstMsg);
extern VOS_UINT32 NAS_LMM_PreProcMmcCellSignReportNotify(MsgBlock  *pstMsg);
/*chengmin for L signal report end*/
extern VOS_UINT32 NAS_EMM_PreProcMsgRrcPagingInd(MsgBlock  *pstMsg);

extern VOS_VOID NAS_EMM_ProcErrlogEstCnfOrDataCnfFail(
                 VOS_VOID*                         pstEmmProcessFail,
                 EMM_OM_ERRLOG_TYPE_ENUM_UINT16    enErrType);

VOS_VOID  NAS_LMM_SendRrcDisableLteNotify(VOS_VOID);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
extern VOS_UINT32  NAS_LMM_PreProcMsgEsmClLocalDetachNotify(
    MsgBlock                           *pMsg
);
#endif
extern VOS_UINT32 NAS_LMM_PreProcMsgGradualForbTimerExpire(MsgBlock *pstMsg);
extern VOS_UINT32 NAS_LMM_PreProcMsgGradualForbAgingTimerExpire(MsgBlock *pstMsg);
extern VOS_UINT32 NAS_EMM_RcvMtaSetUECenterReq(MsgBlock *pstMsg);
extern VOS_UINT32  NAS_EMM_RcvMtaQryUECenterReq(MsgBlock *pMsg);
extern VOS_UINT32  NAS_EMM_PreProcMsgUeCapChangeInd( MsgBlock  *pMsg );
/****************************************************************************
  9 OTHERS
*****************************************************************************/

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasLmmPubMEntry.h*/

