

#ifndef __NASEMMSECUOM_H__
#define __NASEMMSECUOM_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "NasLmmPubMOsa.h"
#include    "NasEmmSecuAuth.h"
#include    "NasEmmPubUGlobal.h"
#include    "MmcLmmInterface.h"
#include    "GmmLmmInterface.h"

/*#include    "LRabmPdcpInterface.h"*/
/*lint -e7*/
/*lint -e322*/
#include  "TlPsDrv.h"
/*lint +e322*/
/*lint +e7*/


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
#define NAS_EMM_CATCH_OP_UINT           32

#define NAS_EMM_SECU_INTER_RAT_HO_NOT_MAPPED 0
#define NAS_EMM_SECU_INTER_RAT_HO_MAPPED     1


#define NAS_EMM_COMP_GMM_MSG_HEADER(pMsg,MsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = WUEPS_PID_GMM;\
            (pMsg)->ulLength            = (MsgLenthNoHeader);\
        }


#define NAS_EMM_GetSecuCtrlAddr()           (&g_NasEmmSecuControl)

/*current security context*/
#define NAS_EMM_GetSecuCurCntxtAddr()       (&((NAS_EMM_GetSecuCtrlAddr())->stCurSecuContext))
#define NAS_EMM_GetSecuCurKSIsgsn()         (NAS_EMM_GetSecuCurCntxtAddr()->ucKSIsgsn)
#define NAS_EMM_GetSecuCurKSIasme()         (NAS_EMM_GetSecuCurCntxtAddr()->ucKSIasme)
#define NAS_EMM_GetSecuCurKasmeAddr()       (NAS_EMM_GetSecuCurCntxtAddr()->aucKasme)
#define NAS_EMM_GetSecuDlNasCount()         (NAS_EMM_GetSecuCurCntxtAddr()->ulDlNasCount)
#define NAS_EMM_GetSecuUlNasCount()         (NAS_EMM_GetSecuCurCntxtAddr()->ulUlNasCount)
#define NAS_EMM_GetSecuUlSn()               (VOS_UINT8)(NAS_EMM_GetSecuUlNasCount() & NAS_EMM_SECU_MASK_NAS_COUNT_SQN)
#define NAS_EMM_GetSecuAlg()                (NAS_EMM_GetSecuCurCntxtAddr()->ucSecuAlg)
#define NAS_EMM_GetSecuEia()                (VOS_UINT8)(NAS_EMM_GetSecuAlg() & NAS_EMM_LOW_3_BITS_F)
#define NAS_EMM_GetSecuEca()                (VOS_UINT8)(((VOS_UINT8)(NAS_EMM_GetSecuAlg() >> 4))& NAS_EMM_LOW_3_BITS_F)

#define NAS_EMM_GetSecuCurNasKeyAddr()      (&(NAS_EMM_GetSecuCurCntxtAddr()->stNasKey))
#define NAS_EMM_GetSecuCurNasCkAddr()       (NAS_EMM_GetSecuCurNasKeyAddr()->aucKNasEnc)
#define NAS_EMM_GetSecuCurNasIkAddr()       (NAS_EMM_GetSecuCurNasKeyAddr()->aucKNasInt)

#define NAS_EMM_SetSecuCurKSIsgsn(KSI)      ((NAS_EMM_GetSecuCurCntxtAddr()->ucKSIsgsn) = (KSI))
#define NAS_EMM_SetSecuCurKSIasme(KSI)      ((NAS_EMM_GetSecuCurCntxtAddr()->ucKSIasme) = (KSI))
#define NAS_EMM_SetSecuAlg(SecuAlg)         ((NAS_EMM_GetSecuCurCntxtAddr()->ucSecuAlg) = (SecuAlg))
#define NAS_EMM_SetSecuDlNasCount(DlNasCount) ((NAS_EMM_GetSecuDlNasCount()) = (DlNasCount))
#define NAS_EMM_SetSecuUlNasCount(UlNasCount) ((NAS_EMM_GetSecuUlNasCount()) = (UlNasCount))

/*new Mapped security context*/
#define NAS_EMM_GetSecuNewMappedCntxtAddr() (&((NAS_EMM_GetSecuCtrlAddr())->stNewMappedSecuContext))
#define NAS_EMM_GetSecuNewMappedKSIsgsn()   (NAS_EMM_GetSecuNewMappedCntxtAddr()->ucKSIsgsn)
#define NAS_EMM_GetSecuNewMappedKasmeAddr() (NAS_EMM_GetSecuNewMappedCntxtAddr()->aucKasme)
#define NAS_EMM_GetSecuNewMappedNasKeyAddr() (&(NAS_EMM_GetSecuNewMappedCntxtAddr()->stNasKey))
#define NAS_EMM_GetSecuNewMappedNasCkAddr() (NAS_EMM_GetSecuNewMappedCntxtAddr()->aucKNasEnc)
#define NAS_EMM_GetSecuNewMappedNasIkAddr() (NAS_EMM_GetSecuNewMappedCntxtAddr()->aucKNasInt)

#define NAS_EMM_SetSecuNewMappedKSIsgsn(KSIsgsn) ((NAS_EMM_GetSecuNewMappedCntxtAddr()->ucKSIsgsn) = (KSIsgsn))

/*new native security context*/
#define NAS_EMM_GetSecuNewNativeCntxtAddr() (&((NAS_EMM_GetSecuCtrlAddr())->stNewNativeSecuContext))
#define NAS_EMM_GetSecuNewNativeKSIasme()   (NAS_EMM_GetSecuNewNativeCntxtAddr()->ucKSIasme)
#define NAS_EMM_GetSecuNewNativeKasmeAddr() (NAS_EMM_GetSecuNewNativeCntxtAddr()->aucKasme)
#define NAS_EMM_GetSecuNewNativeNasKeyAddr() (&(NAS_EMM_GetSecuNewNativeCntxtAddr()->stNasKey))
#define NAS_EMM_GetSecuNewNativeNasCkAddr() (NAS_EMM_GetSecuNewNativeCntxtAddr()->aucKNasEnc)
#define NAS_EMM_GetSecuNewNativeNasIkAddr() (NAS_EMM_GetSecuNewNativeCntxtAddr()->aucKNasInt)

#define NAS_EMM_SetSecuNewNativeKSIasme(KSI) ((NAS_EMM_GetSecuNewNativeCntxtAddr()->ucKSIasme) = (KSI))

/*non-current native security context*/
#define NAS_EMM_GetSecuNonCurNativeCntxtAddr() (&((NAS_EMM_GetSecuCtrlAddr())->stNonCurNativeSecuContext))
#define NAS_EMM_GetSecuNonCurNativeKSIasme()   (NAS_EMM_GetSecuNonCurNativeCntxtAddr()->ucKSIasme)
#define NAS_EMM_GetSecuNonCurNativeKasmeAddr() (NAS_EMM_GetSecuNonCurNativeCntxtAddr()->aucKasme)
#define NAS_EMM_GetSecuNonCurNativeNasKeyAddr()(&(NAS_EMM_GetSecuNonCurNativeCntxtAddr()->stNasKey))
#define NAS_EMM_GetSecuNonCurNativeNasCkAddr() (NAS_EMM_GetSecuNonCurNativeNasKeyAddr()->aucKNasEnc)
#define NAS_EMM_GetSecuNonCurNativeNasIkAddr() (NAS_EMM_GetSecuNonCurNativeNasKeyAddr()->aucKNasInt)
#define NAS_EMM_GetSecuNonCurAlg()             (NAS_EMM_GetSecuNonCurNativeCntxtAddr()->ucSecuAlg)
#define NAS_EMM_GetSecuNonCurDlNasCount()      (NAS_EMM_GetSecuNonCurNativeCntxtAddr()->ulDlNasCount)
#define NAS_EMM_GetSecuNonCurUlNasCount()      (NAS_EMM_GetSecuNonCurNativeCntxtAddr()->ulUlNasCount)

#define NAS_EMM_SetSecuNonCurNativeKSIasme(KSI) ((NAS_EMM_GetSecuNonCurNativeKSIasme()) = (KSI))


/*temp Nas KEY*/
#define NAS_EMM_GetSecuTempNasKeyAddr()     (&(NAS_EMM_GetSecuCtrlAddr()->stTempNasKey))
#define NAS_EMM_GetSecuTempNasCkAddr()      (NAS_EMM_GetSecuTempNasKeyAddr()->aucKNasEnc)
#define NAS_EMM_GetSecuTempNasIkAddr()      (NAS_EMM_GetSecuTempNasKeyAddr()->aucKNasInt)


/*Umts security context*/
#define NAS_EMM_GetUmtsSecuContextAddr()    (&(NAS_EMM_GetSecuCtrlAddr()->stUmtsSecuContext))
#define NAS_EMM_GetUmtsKsi()                (NAS_EMM_GetUmtsSecuContextAddr()->ucKSI)
#define NAS_EMM_GetUmtsCkAddr()             (NAS_EMM_GetUmtsSecuContextAddr()->aucCK)
#define NAS_EMM_GetUmtsIkAddr()             (NAS_EMM_GetUmtsSecuContextAddr()->aucIK)

#define NAS_EMM_SetUmtsKsi(KSI)             ((NAS_EMM_GetUmtsSecuContextAddr()->ucKSI) = (KSI))

/*NonceUE, NonceMME*/
#define NAS_EMM_GetSecuNonceUEAddr()        (NAS_EMM_GetSecuCtrlAddr()->aucNonceUE)
#define NAS_EMM_GetSecuNonceMMEAddr()       (NAS_EMM_GetSecuCtrlAddr()->aucNonceMME)


#define NAS_EMM_GetSecuUsimAuthParamAddr()  (&(NAS_EMM_GetSecuCtrlAddr()->stNasUsimAuthParam))
#define NAS_EMM_GetSecuAuthOpRand()       (NAS_EMM_GetSecuUsimAuthParamAddr()->bitOpRand)
#define NAS_EMM_GetSecuAuthRandAddr()       (NAS_EMM_GetSecuUsimAuthParamAddr()->aucRand)
#define NAS_EMM_GetSecuAuthAutsAddr()       (NAS_EMM_GetSecuUsimAuthParamAddr()->aucAuts)
#define NAS_EMM_GetSecuAuthResAddr()        (&(NAS_EMM_GetSecuUsimAuthParamAddr()->stRes))
#define NAS_EMM_GetSecuAuthOpId()           (NAS_EMM_GetSecuUsimAuthParamAddr()->ucOpId)

#define NAS_EMM_GetSecuAuthResLen()         (NAS_EMM_GetSecuAuthResAddr()->ucResLen)
#define NAS_EMM_GetSecuAuthResVAddr()       (NAS_EMM_GetSecuAuthResAddr()->aucRes)

#define NAS_EMM_GetAuthReqParamAddr()       (&(NAS_EMM_GetSecuCtrlAddr()->stAuthReqParam))
#define NAS_EMM_AuthReqKsi()                (NAS_EMM_GetAuthReqParamAddr()->ucKsi)
#define NAS_EMM_AuthReqRandAddr()           (NAS_EMM_GetAuthReqParamAddr()->aucRand)
#define NAS_EMM_AuthReqAutnAddr()           (NAS_EMM_GetAuthReqParamAddr()->aucAutn)

#define NAS_EMM_GetSecuBufSpace()           ((NAS_EMM_GetSecuCtrlAddr())->aucSecuBuf)

#define NAS_EMM_GetSmcType()                (NAS_EMM_GetSecuCtrlAddr()->enSmcType)
#define NAS_EMM_SetSmcType(SmcType)         ((NAS_EMM_GetSecuCtrlAddr()->enSmcType) = (SmcType))

#define NAS_EMM_GetAuthFailTimes()          (NAS_EMM_GetSecuCtrlAddr()->ulFailTimes)

/*异系统切换是否产生了映射的安全上下文*/
#define NAS_EMM_GetFlagInterRatHoMapped() (NAS_EMM_GetSecuCtrlAddr()->ulFlagInterRatHoMapped)
#define NAS_EMM_SetFlagInterRatHoMapped(InterRatHoMapped)\
        ((NAS_EMM_GetSecuCtrlAddr()->ulFlagInterRatHoMapped) = (InterRatHoMapped))

#define NAS_EMM_SECU_LOG_INFO(String)                     NAS_LMM_LOG_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_SECU, String)
#define NAS_EMM_SECU_LOG_NORM(String)                     NAS_LMM_LOG_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_SECU, String)
#define NAS_EMM_SECU_LOG_WARN(String)                     NAS_LMM_LOG_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_SECU, String)
#define NAS_EMM_SECU_LOG_ERR(String)                      NAS_LMM_LOG_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_SECU, String)

#define NAS_EMM_SECU_LOG1_INFO(String, Para1)             NAS_LMM_LOG1_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_SECU, String, Para1)
#define NAS_EMM_SECU_LOG1_NORM(String, Para1)             NAS_LMM_LOG1_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_SECU, String, Para1)
#define NAS_EMM_SECU_LOG1_WARN(String, Para1)             NAS_LMM_LOG1_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_SECU, String, Para1)
#define NAS_EMM_SECU_LOG1_ERR(String,  Para1)             NAS_LMM_LOG1_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_SECU, String,  Para1)

#define NAS_EMM_SECU_LOG2_INFO(String, Para1, Para2)      NAS_LMM_LOG2_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_SECU, String, Para1, Para2)
#define NAS_EMM_SECU_LOG2_NORM(String, Para1, Para2)      NAS_LMM_LOG2_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_SECU, String, Para1, Para2)
#define NAS_EMM_SECU_LOG2_WARN(String, Para1, Para2)      NAS_LMM_LOG2_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_SECU, String, Para1, Para2)
#define NAS_EMM_SECU_LOG2_ERR(String,  Para1, Para2)      NAS_LMM_LOG2_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_SECU, String,  Para1, Para2)

#define NAS_EMM_SECU_LOG3_INFO(String, Para1, Para2, Para3)    NAS_LMM_LOG3_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_SECU, String, Para1, Para2, Para3)
#define NAS_EMM_SECU_LOG3_NORM(String, Para1, Para2, Para3)    NAS_LMM_LOG3_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_SECU, String, Para1, Para2, Para3)
#define NAS_EMM_SECU_LOG3_WARN(String, Para1, Para2, Para3)    NAS_LMM_LOG3_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_SECU, String, Para1, Para2, Para3)
#define NAS_EMM_SECU_LOG3_ERR(String,  Para1, Para2, Para3)    NAS_LMM_LOG3_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_SECU, String,  Para1, Para2, Para3)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
   5 STRUCT
*****************************************************************************/

/*****************************************************************************
结构名称    : NAS_LMM_HO_LRRC_SECU_PARA_STRU
使用说明    : GU->L切换过程中，从LRRC获取的安全参数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucNonceMME[NAS_EMM_SECU_NONCE_MME_LEN];
    VOS_UINT8                           ucSecuAlg;
    VOS_UINT8                           ucKsiType;
    VOS_UINT8                           ucKsiValue;
    VOS_UINT8                           ucRsv;
}NAS_LMM_HO_LRRC_SECU_PARA_STRU;

typedef struct
{
    VOS_UINT8                           aucKeyParam[NAS_LMM_SECU_AUTH_KEY_ASME_LEN];
    VOS_UINT32                          ulBuflen;
    VOS_UINT8                           aucAlgParam[NAS_EMM_SECU_MAX_ALG_PARAM_LEN];
}NAS_LMM_BSP_INPUT_PARA_STRU;

typedef struct
{
    VOS_UINT32                          ulOutKeyLen;
    VOS_UINT8                           aucKasme[NAS_LMM_SECU_AUTH_KEY_ASME_LEN];
}NAS_LMM_BSP_OUTPUT_PARA_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern  VOS_VOID    NAS_EMM_SecuPrintCipherPara(
                                        CIPHER_SINGLE_CFG_S const *pstSingleSecuPara,
                                        VOS_UINT8  const *pucSrc);
extern  VOS_UINT32  NAS_EMM_SecuSetKeyByKeyIndex( const VOS_UINT8 *pucKeyAddr,
                                    NAS_EMM_SECU_NAS_KEY_TYPE_ENUM_UINT8 enKeyType );
/*extern  VOS_UINT8 * NAS_EMM_SecuGetKeyByIndex( VOS_UINT32 ulKeyIndex );*/
extern  VOS_UINT32 NAS_EMM_SecuGetKeyByIndex(   VOS_UINT32      ulKeyIndex,
                                                KEY_GET_S      *pstKeyGet);
extern  VOS_INT32   NAS_CIPHER_SingleSubmitTask(CIPHER_SINGLE_CFG_S   *pstSingleSecuPara);
extern VOS_VOID     NAS_LMM_CompLmmReselSecuInfoCnf(
                    LMM_GMM_RESEL_SECU_INFO_CNF_STRU   *pstLmmReselSecuInfoCnf );
extern VOS_VOID     NAS_LMM_CompLmmHoSecuInfoCnf(
                    LMM_GMM_HO_SECU_INFO_CNF_STRU   *pstLmmHoSecuInfoCnf );
extern VOS_UINT32   NAS_EMM_SecuGetUmtsSecuContext( VOS_VOID );
extern VOS_VOID     NAS_EMM_ClearNewMappedSecuCntxt( VOS_VOID );
extern VOS_VOID     NAS_EMM_SecuDecodeRrcSecuPara(
                                 const  VOS_UINT8 *pucSecuParaHo,
                                        NAS_LMM_HO_LRRC_SECU_PARA_STRU *pstHoLrrcSecuPara);
extern VOS_UINT32   NAS_EMM_NotEia0SecuVerifyRrcSecuPara(
                        const NAS_LMM_HO_LRRC_SECU_PARA_STRU *pstHoLrrcSecuPara );
extern VOS_UINT32  NAS_EMM_Eia0SecuVerifyRrcSecuPara
(
    const NAS_LMM_HO_LRRC_SECU_PARA_STRU *pstHoLrrcSecuPara
);
extern VOS_VOID     NAS_EMM_SecuSaveCurNativeToNonCurNative( VOS_VOID );
extern VOS_VOID     NAS_EMM_SecuRecovNonCurNativeToCurNative( VOS_VOID );
extern VOS_UINT32   NAS_EMM_SecuHoCurMappedSecuCntxt(
                        const NAS_LMM_HO_LRRC_SECU_PARA_STRU *pstHoLrrcSecuPara );
extern VOS_VOID     NAS_EMM_SecuSendLrrcSecuParaRsp( VOS_VOID );
extern VOS_VOID     NAS_EMM_SecuGetUmtsSecuCntxtAndNasTokenIdle(
                        LMM_GMM_RESEL_SECU_INFO_STRU       *pstReselSecuInfo );
extern VOS_VOID     NAS_EMM_SecuGetUmtsSecuCntxtHo(
                                LMM_GMM_UMTS_SECU_CONTEXT_STRU *pstUmtsSecuCntxt);
extern VOS_UINT32   NAS_EMM_DeriveRandNonceUE( VOS_UINT8 *pucNonceUE );
extern VOS_UINT32   NAS_EMM_DeriveKasmeFromUmtsIdle( VOS_UINT8 *pucKasme );
extern VOS_UINT32   NAS_EMM_DeriveKasmeFromUmtsHo( VOS_UINT8 *pucKasme );
extern VOS_UINT32   NAS_EMM_DeriveUmtsCkIkFromEpsIdle(
                                                           VOS_UINT8 *pucUmtsCK,
                                                           VOS_UINT8 *pucUmtsIk );
extern VOS_UINT32   NAS_EMM_DeriveUmtsCkIkFromEpsHo(
                                                            VOS_UINT8 *pucUmtsCK,
                                                            VOS_UINT8 *pucUmtsIk);
extern VOS_UINT32   NAS_EMM_DeriveNasToken( VOS_UINT8 *pucNasToken );

extern VOS_VOID  NAS_EMM_SecuCurrentContextUpNasCountBack(VOS_VOID);

extern VOS_UINT32  NAS_EMM_DeriveUmtsCkIkFromEpsSrvcc( VOS_UINT8 *pucUmtsCK,
                                                            VOS_UINT8 *pucUmtsIk);

extern VOS_VOID    NAS_LMM_CompLmmMmHoSecuInfoCnf(LMM_MM_HO_SECU_INFO_CNF_STRU   *pstLmmHoSecuInfoCnf );
extern VOS_VOID    NAS_EMM_SecuGetMmUmtsSecuCntxtHo(MM_LMM_GU_SECU_CONTEXT_STRU *pstUmtsSecuCntxt);
extern VOS_VOID NAS_LMM_LogBspKdfKeyMake
(
    const NAS_LMM_BSP_INPUT_PARA_STRU         *pstBspInputPara,
    const NAS_LMM_BSP_OUTPUT_PARA_STRU        *pstBspOutputPara,
    VOS_INT32                          ulRslt
);

/*****************************************************************************
  9 OTHERS
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

#endif /* end of NasEmmSecuOm.h */
