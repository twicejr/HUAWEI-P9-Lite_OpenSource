
/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasEmmDetach.h
  Description     : NasEmmDetach.h
  History           :
      1.leili       00132387  2008-09-04  Draft Enact
      2.zhengjunyan 00148421  2009-07-31  24301_CR37:收到网侧re-attach类型的DETACH,
                                          释放当前连接，再发起ATTACH
      3.zhengjunyan 00148421   2009-07-17  CR165:Add value reserved for detach type
******************************************************************************/

#ifndef __NASEMMDETACH_H__
#define __NASEMMDETACH_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "NasEmmPubUGlobal.h"
#include    "NasEmmPubUCnMsgDecode.h"
#include    "NasEmmAttach.h"
#include    "EmmEsmInterface.h"


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


#define NAS_EMM_DETACH_LOG_INFO(String)  NAS_LMM_LOG_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_DETACH, String)
#define NAS_EMM_DETACH_LOG_NORM(String)  NAS_LMM_LOG_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_DETACH, String)
#define NAS_EMM_DETACH_LOG_WARN(String)  NAS_LMM_LOG_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_DETACH, String)
#define NAS_EMM_DETACH_LOG_ERR(String)   NAS_LMM_LOG_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_DETACH, String)

#define NAS_EMM_DETACH_LOG1_INFO(String, Para1)    NAS_LMM_LOG1_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_DETACH, String, Para1)
#define NAS_EMM_DETACH_LOG1_NORM(String, Para1)    NAS_LMM_LOG1_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_DETACH, String, Para1)
#define NAS_EMM_DETACH_LOG1_WARN(String, Para1)    NAS_LMM_LOG1_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_DETACH, String, Para1)
#define NAS_EMM_DETACH_LOG1_ERR(String,  Para1)    NAS_LMM_LOG1_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_DETACH, String,  Para1)

#define NAS_EMM_DETACH_LOG2_INFO(String, Para1, Para2)    NAS_LMM_LOG2_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_DETACH, String, Para1, Para2)
#define NAS_EMM_DETACH_LOG2_NORM(String, Para1, Para2)    NAS_LMM_LOG2_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_DETACH, String, Para1, Para2)
#define NAS_EMM_DETACH_LOG2_WARN(String, Para1, Para2)    NAS_LMM_LOG2_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_DETACH, String, Para1, Para2)
#define NAS_EMM_DETACH_LOG2_ERR(String,  Para1, Para2)    NAS_LMM_LOG2_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_DETACH, String,  Para1, Para2)

#define NAS_EMM_DETACH_LOG3_INFO(String, Para1, Para2, Para3)    NAS_LMM_LOG3_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_DETACH, String, Para1, Para2, Para3)
#define NAS_EMM_DETACH_LOG3_NORM(String, Para1, Para2, Para3)    NAS_LMM_LOG3_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_DETACH, String, Para1, Para2, Para3)
#define NAS_EMM_DETACH_LOG3_WARN(String, Para1, Para2, Para3)    NAS_LMM_LOG3_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_DETACH, String, Para1, Para2, Para3)
#define NAS_EMM_DETACH_LOG3_ERR(String,  Para1, Para2, Para3)    NAS_LMM_LOG3_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_DETACH, String,  Para1, Para2, Para3)




/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
enum    NAS_EMM_DETACH_MODE_ENUM
{
    NAS_EMM_DETACH_MODE_NOT_SWITCH_OFF  = 0x00,
    NAS_EMM_DETACH_MODE_SWITCH_OFF      = 0x08,


    NAS_EMM_DETACH_MODE_BUTT
};
typedef VOS_UINT8   NAS_EMM_DETACH_MODE_ENUM_UINT8;

enum    EMM_DETACH_ABNORMAL_CAUSE_ENUM
{
    EMM_DETACH_ABNORMAL_CAUSE_ACCESS_BARRED             = 0x01,
    EMM_DETACH_ABNORMAL_CAUSE_LOWER_LAYER_FAIL          = 0x02,
    EMM_DETACH_ABNORMAL_CAUSE_T3421_EXP                 = 0x03,
    EMM_DETACH_ABNORMAL_CAUSE_DETACH_COLLISION          = 0x04,
    EMM_DETACH_ABNORMAL_CAUSE_COMMON_COLLISION          = 0x05,
    EMM_DETACH_ABNORMAL_CAUSE_TAU_CHANGE                = 0x06,

    EMM_DETACH_ABNORMAL_CAUSE_BUTT
};
typedef VOS_UINT8   EMM_DETACH_ABNORMAL_CAUSE_ENUM_UINT8;





/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/* DETACH控制消息结构 */
typedef struct
{
    VOS_UINT32                              ulBitOpEmmCau           :1;
    VOS_UINT32                              ulBitRsv                :31;

    MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32      ulDetachTypeMo;
    NAS_EMM_DETACH_MODE_ENUM_UINT8          ucDetachMode;
    VOS_UINT8                               ucDetachAtmpCnt;    /* DETACH attempt counter */
    VOS_UINT8                               ucMtDetachAccTxCnt;
    VOS_UINT8                               ucUsimPollOutFlag;  /* 拔卡标识 */
    NAS_EMM_CN_CAUSE_ENUM_UINT8             ucEmmCause;
}NAS_EMM_DETACH_CTRL_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern  NAS_EMM_DETACH_CTRL_STRU                g_stEmmDetCtrl;
/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern  VOS_VOID    NAS_EMM_DetachInit(VOS_VOID);
extern  VOS_VOID    NAS_EMM_FreeDetDyn( VOS_VOID );
extern  VOS_UINT32  NAS_EMM_IntraDetReqChk(const NAS_LMM_INTRA_DETACH_REQ_STRU *pMsgMsg);
extern  VOS_VOID    NAS_EMM_DetachToTAU(VOS_VOID);
extern  VOS_VOID    NAS_EMM_RcvTauIntraMsgDetReq(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru);
extern  VOS_VOID    NAS_EMM_CompCnDetachReqMo(NAS_EMM_MRRC_DATA_REQ_STRU *pDetReqMoMsg);

extern  VOS_VOID    NAS_EMM_MrrcSendDetReqMo(VOS_VOID);
extern  VOS_VOID    NAS_EMM_RrcRelCauseCnDetachSrcClrAttemptToAtt(VOS_VOID);

/*extern  VOS_VOID    NAS_EMM_DetSndIntraAttReq(VOS_VOID);*/
extern  VOS_VOID    NAS_EMM_CompCnDetachReqMoNasMsg(VOS_UINT8 *pucCnMsg,  VOS_UINT32 *pulIndex);
extern  VOS_VOID    NAS_EMM_MsDrgInitSsWtCnDetCnfProcMsgRrcRelInd( VOS_UINT32 ulCause);
extern  VOS_VOID  NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_ENUM_UINT32 ulAppRslt  );
extern  VOS_VOID NAS_EMM_SendImsiDetachReqMo( VOS_VOID );
extern  MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32 NAS_EMM_GetDetachType( VOS_VOID );
extern  MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32 NAS_EMM_GetSwitchOffDetachType( VOS_VOID );

extern VOS_UINT32 NAS_EMM_SndDetachReqFailProc(VOS_VOID* pMsg,VOS_UINT32 *pulIsDelBuff);

extern VOS_UINT32 NAS_EMM_SndMtDetachAccFailProc(VOS_VOID* pMsg,VOS_UINT32 *pulIsDelBuff);

extern VOS_UINT32 NAS_EMM_SndDetachReqSuccProc(VOS_VOID* pMsg);

extern VOS_VOID    NAS_EMM_SndRrcDetachInd(VOS_VOID);

extern VOS_VOID NAS_EMM_LocalDetachErrRecord(
        EMM_ERR_LOG_LOCAL_DETACH_TYPE_ENUM_UINT16       enLocalDetType);
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


