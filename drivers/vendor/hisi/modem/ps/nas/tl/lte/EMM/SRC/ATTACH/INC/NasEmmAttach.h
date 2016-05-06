


#ifndef __NASEMMATTACH_H__
#define __NASEMMATTACH_H__




/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "NasEmmPubUCnMsgDecode.h"
#include    "NasLmmPubMFsm.h"
#include    "NasLmmPubMEntry.h"
#include    "NasEmmcEmmInterface.h"
#include    "NasEmmAttDetInterface.h"
#include    "NasEmmPlmn.h"



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
  2 Macro
*****************************************************************************/

#define NAS_EMM_ATTACH_LOG_INFO(String)                     NAS_LMM_LOG_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_ATTACH, String)
#define NAS_EMM_ATTACH_LOG_NORM(String)                     NAS_LMM_LOG_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_ATTACH, String)
#define NAS_EMM_ATTACH_LOG_WARN(String)                     NAS_LMM_LOG_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_ATTACH, String)
#define NAS_EMM_ATTACH_LOG_ERR(String)                      NAS_LMM_LOG_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_ATTACH, String)

#define NAS_EMM_ATTACH_LOG1_INFO(String, Para1)             NAS_LMM_LOG1_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_ATTACH, String, Para1)
#define NAS_EMM_ATTACH_LOG1_NORM(String, Para1)             NAS_LMM_LOG1_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_ATTACH, String, Para1)
#define NAS_EMM_ATTACH_LOG1_WARN(String, Para1)             NAS_LMM_LOG1_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_ATTACH, String, Para1)
#define NAS_EMM_ATTACH_LOG1_ERR(String,  Para1)             NAS_LMM_LOG1_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_ATTACH, String,  Para1)

#define NAS_EMM_ATTACH_LOG2_INFO(String, Para1, Para2)      NAS_LMM_LOG2_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_ATTACH, String, Para1, Para2)
#define NAS_EMM_ATTACH_LOG2_NORM(String, Para1, Para2)      NAS_LMM_LOG2_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_ATTACH, String, Para1, Para2)
#define NAS_EMM_ATTACH_LOG2_WARN(String, Para1, Para2)      NAS_LMM_LOG2_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_ATTACH, String, Para1, Para2)
#define NAS_EMM_ATTACH_LOG2_ERR(String,  Para1, Para2)      NAS_LMM_LOG2_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_ATTACH, String,  Para1, Para2)

#define NAS_EMM_ATTACH_LOG3_INFO(String, Para1, Para2, Para3)    NAS_LMM_LOG3_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_ATTACH, String, Para1, Para2, Para3)
#define NAS_EMM_ATTACH_LOG3_NORM(String, Para1, Para2, Para3)    NAS_LMM_LOG3_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_ATTACH, String, Para1, Para2, Para3)
#define NAS_EMM_ATTACH_LOG3_WARN(String, Para1, Para2, Para3)    NAS_LMM_LOG3_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_ATTACH, String, Para1, Para2, Para3)
#define NAS_EMM_ATTACH_LOG3_ERR(String,  Para1, Para2, Para3)    NAS_LMM_LOG3_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_ATTACH, String,  Para1, Para2, Para3)



/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/


/*======================= 定时器相关 =======================*/

enum    NAS_EMM_ATTACH_CAUSE_ENUM
{
    EMM_ATTACH_CAUSE_APP                = 0x01,     /* OM发起ATTACH */
    EMM_ATTACH_CAUSE_ESM                      ,     /* ESM发起ATTACH */
    EMM_ATTACH_CAUSE_CN_DETACH_REATTACH       ,     /* CN要求REATTACH类型的DETACH */
    EMM_ATTACH_CAUSE_TIMER_EXP                ,     /*定时器超时发起的ATTACH*/
    EMM_ATTACH_CAUSE_ESM_EMC_ATTACH           ,     /* ESM触发的紧急注册 */
    EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER, /* ESM紧急PDN建立触发的普通注册 */

    EMM_ATTACH_CAUSE_OTHER                    ,

    EMM_ATTACH_CAUSE_BUTT
};
typedef VOS_UINT8   NAS_EMM_ATTACH_CAUSE_ENUM_UINT8;

enum    NAS_EMM_CONN_REL_CAUSE_ENUM
{

    EMM_CONN_REL_CAUSE_T3410_EXP        = 0x01,
    EMM_CONN_REL_CAUSE_T3440_EXP              ,
    EMM_CONN_REL_CAUSE_T3411_EXP              ,
    EMM_CONN_REL_CAUSE_T3402_EXP              ,
    EMM_CONN_REL_CAUSE_REJVAL_OTHER           ,
    EMM_CONN_REL_CAUSE_NEW_TA                 ,
    EMM_CONN_REL_CAUSE_FORB_TA                ,
    EMM_CONN_REL_CAUSE_EPS_ONLY_REJVAL_OTHER  ,
    EMM_CONN_REL_CAUSE_AUTH_REJ               ,

    EMM_CONN_REL_CAUSE_BUTT
};
typedef VOS_UINT8   NAS_EMM_CONN_REL_CAUSE_ENUM_UINT8;

enum    NAS_EMM_ATTACH_RSLT_ENUM
{
    EMM_ATTACH_RSLT_EPS_ONLY                = 0x01, /*网侧响应的结果 */
    EMM_ATTACH_RSLT_COMBINED_ATTACH         ,

    EMM_ATTACH_RSLT_BUTT
};
typedef VOS_UINT8   NAS_EMM_ATTACH_RSLT_UINT8;



/*****************************************************************************
  5 STRUCT
*****************************************************************************/





/* ATTACH控制消息结构 */
typedef struct
{
    VOS_UINT32                              ulBitOpEmmCau           :1;
    VOS_UINT32                              ulBitOpLai              :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                              ulBitOpMsId             :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                              ulBitOpAttExtCause      :1; /* 指示被15拒绝之后是否有扩展原因值*/
    VOS_UINT32                              ulBitRsv                :28;

    VOS_UINT8                               ucAttAtmpCnt;        /* ATTACH attempt counter */
    VOS_UINT8                               ucAttRej19AtmpCnt;   /* ATTACH 被#19拒绝的计数 */
    VOS_UINT8                               aucRsv1[2];

    NAS_EMM_ATTACH_CAUSE_ENUM_UINT8         ucAttCause;     /* ATTACH 的原因*/
    NAS_EMM_CN_CAUSE_ENUM_UINT8             ucAttRejCause;  /* 一次ATTACH流程被拒的原因,
                                                               当ATTACH成功后,清除此域*/
    NAS_EMM_CN_CAUSE_ENUM_UINT8             ucAttRejEsmCause;
    NAS_EMM_CN_CAUSE_ENUM_UINT8             ucEMMCause;
    NAS_EMM_CN_MSGCON_STRU                  stEsmMsg;
    MMC_LMM_ATT_REQ_TYPE_ENUM_UINT32        ulAttReqType;
    MMC_LMM_ATTACH_TYPE_ENUM_UINT32         ulAttCnType;
    NAS_EMM_ATTACH_RSLT_UINT8               ucAttRslt;
    VOS_UINT8                               ucAttRejExtendedEmmCause; /*attach被15拒绝之后的扩展原因值，指示是否是未开户场景*/

    MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8      enClAttRegStatus; /* VIA CL多模使用的ATTACH流程阶段上报 */
    VOS_UINT8                               aucRsv;
    NAS_EMM_LA_STRU                         stLai;
    NAS_EMM_MSID_STRU                       stMsId;

    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32     ulForbInfo;
}NAS_EMM_ATTACH_CTRL_STRU;



/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern  NAS_EMM_ATTACH_CTRL_STRU        g_stEmmAttCtrl;


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern  VOS_VOID    NAS_EMM_AttachInit(VOS_VOID);
extern  VOS_VOID    NAS_EMM_FreeAttDyn( VOS_VOID );
extern  VOS_UINT32  NAS_EMM_IntraAttReqChk(const  NAS_LMM_INTRA_ATTACH_REQ_STRU *pMsgMsg);
extern  VOS_UINT32  NAS_EMM_SysInfoMsgChk(EMMC_EMM_SYS_INFO_IND_STRU *pMsgMsg);

extern  VOS_VOID    NAS_EMM_AdStateConvert(NAS_EMM_MAIN_STATE_ENUM_UINT16 ucMs,
                                   NAS_EMM_SUB_STATE_ENUM_UINT16 ucSs,
                                   NAS_EMM_STATE_TI_ENUM_UINT16 ucStaTId);
extern  VOS_VOID    NAS_EMM_EsmSendRelInd(VOS_VOID);
extern  VOS_VOID    NAS_EMM_AtmpCntLess5Proc(VOS_VOID);
extern  VOS_VOID    NAS_EMM_AtmpCntEqual5Proc(VOS_VOID);
extern  VOS_VOID    NAS_EMM_ProcRejCauOtherAbnormal( VOS_VOID );
extern  VOS_VOID    NAS_EMM_AttProcEpsOnlyRejValueOther( VOS_VOID );
extern  VOS_VOID    NAS_EMM_AttSendEsmResult( EMM_ESM_ATTACH_STATUS_ENUM_UINT32 attStatus );
extern  VOS_VOID    NAS_EMM_AttNrmFailProc( VOS_VOID );
extern  VOS_VOID    NAS_EMM_SetAttType( VOS_VOID );
extern  VOS_VOID    NAS_EMM_UpdateCnAttTypeOfUserReq( VOS_VOID );
extern  VOS_VOID    NAS_EMM_UpdateCnAttTypeOfNotUserReq( VOS_VOID );
extern  VOS_VOID    NAS_EMM_SetUeUsageSetting (VOS_VOID );
extern  VOS_UINT32  NAS_EMM_GetCsService (VOS_VOID );
extern  VOS_UINT32  NAS_EMM_GetVoiceDomain(VOS_VOID );
extern  VOS_UINT32  NAS_EMM_GetClassMark2OpBit(VOS_VOID );
extern  VOS_UINT32  NAS_EMM_GetClassMark3OpBit(VOS_VOID );
extern  VOS_UINT32  NAS_EMM_GetSuppSrvccToGU(VOS_VOID );
extern  VOS_VOID    NAS_EMM_ProcCause161722TauAttemptCont(VOS_VOID );
extern  VOS_VOID    NAS_EMM_ProcRrcDataCnfSucc( VOS_VOID );
extern  VOS_VOID    NAS_EMM_SetAttachRegDomain( VOS_VOID );
extern VOS_VOID     NAS_EMM_Attach_SuspendInitClearResourse(VOS_VOID);
extern VOS_VOID     NAS_EMM_SendRrcClearBuffNotify(VOS_VOID);
extern  VOS_VOID    NAS_EMM_ProcAttachConnFailOtherCause( VOS_VOID );
extern VOS_UINT32 NAS_EMM_SndAttachCmpFailProc(VOS_VOID* pMsg,VOS_UINT32 *pulIsDelBuff);
extern VOS_UINT32 NAS_EMM_SndAttachCmpSuccProc(VOS_VOID* pMsg);
extern VOS_VOID  NAS_EMM_MsRegInitSsWtCnAttCnfProcMsgRrcRelInd(VOS_UINT32 ulCause);
extern VOS_VOID  NAS_EMM_DamAttachRej19CountProc(VOS_VOID);

extern VOS_VOID NSA_EMM_SndImsaAttachBeginInd(VOS_VOID);

/*****************************************************************************
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

#endif










































