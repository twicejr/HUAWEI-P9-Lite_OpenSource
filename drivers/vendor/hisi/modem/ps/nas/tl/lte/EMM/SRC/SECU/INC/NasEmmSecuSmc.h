

#ifndef __NASEMMSECUSMC_H__
#define __NASEMMSECUSMC_H__



/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "LRrcLNasInterface.h"
#include    "NasEmmSecuInterface.h"
#include    "NasEmmPubUGlobal.h"
#include    "NasEmmSecuAuth.h"
#include    "LRabmPdcpInterface.h"
#include    "NasEmmSecuProtect.h"
#include    "NasEmmPubUCnMsgDecode.h"

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
#define NAS_EMM_SECU_SMC_MT_POSE                  7
#define NAS_EMM_SECU_SMC_ALG_POSE                 8
#define NAS_EMM_SECU_SMC_KSI_POSE                 9
#define NAS_EMM_SECU_SMC_CAP_LEN_POSE             10
#define NAS_EMM_SECU_SMC_CAP_POSE                 11
#define NAS_EMM_LOCAL_UE_NET_CAP_POSE             1

#define NAS_EMM_SECU_MSG_HEAD_LEN                 6
#define NAS_EMM_SECU_PLAIN_MSG_POS                6
#define NAS_EMM_SECU_MAC_POS                      1
#define NAS_EMM_SECU_MAC_LEN                      4

#define NAS_EMM_SECU_MSG_SN_POS                   5
#define NAS_EMM_SECU_HEADTYPE_MAC_LEN             5

#define NAS_EMM_SECU_HIGHEST_BIT                  0x80

#define NAS_EMM_SECU_KSI_TYPE_BIT_POS             3
#define NAS_EMM_SECU_KSI_TYPE_NATIVE              0
#define NAS_EMM_SECU_KSI_TYPE_MAPPED              1

#define NAS_EMM_SECU_IMEISV_IEI                   0x23

#define NAS_EMM_SMC_FIX_LEN                       5
#define NAS_EMM_SMC_NONCE_MME_IE_LEN              5
#define NAS_EMM_SMC_NONCE_UE_IE_LEN               5
#define NAS_EMM_PLAIN_SMC_CAP_LEN_POS             4
#define NAS_EMM_PLAIN_SMC_ALG_POSE                2
#define NAS_EMM_SMC_IMEISV_REQ_IEI                0xC0
#define NAS_EMM_SMC_NONCE_UE_IEI                  0x55
#define NAS_EMM_SMC_NONCE_MME_IEI                 0x56

#define NAS_EMM_SMC_IMEISV_REQ                    0xC1

#define NAS_EMM_SMC_MIN_UE_SECU_CAP_LEN           2
#define NAS_EMM_SMC_MAX_UE_SECU_CAP_LEN           5

#define NAS_EMM_SMC_UE_SECU_CAP_LEN               5

#define NAS_EMM_UE_NET_CAP_EEA_POS                0
#define NAS_EMM_UE_NET_CAP_EIA_POS                1
#define NAS_EMM_UE_NET_CAP_UEA_POS                2
#define NAS_EMM_UE_NET_CAP_UIA_POS                3



#define NAS_EMM_SMC_MIN_LEN                       13
#define NAS_EMM_SMC_MAX_LEN                       27

#define NAS_EMM_SECU_ALG_EIA0                     0
#define NAS_EMM_SECU_ALG_EEA0                     0

#define NAS_EMM_SECU_ALG_EIA1                     1
#define NAS_EMM_SECU_ALG_EEA1                     1

#define NAS_EMM_SECU_ALG_EIA2                     2
#define NAS_EMM_SECU_ALG_EEA2                     2


#define NAS_EMM_SECU_ALG_EIA3                     3
#define NAS_EMM_SECU_ALG_EEA3                     3

#define NAS_EMM_GetEia0Kasme()                    (g_aucEia0Kasme)

/* SECU_MODE_COMM消息必选信元的长度*/
#define NAS_EMM_SECU_M_IE_LEN(pMsg)\
        (NAS_EMM_SMC_FIX_LEN + pMsg[NAS_EMM_PLAIN_SMC_CAP_LEN_POS])

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum    NAS_EMM_SECU_PROC_SMC_RSLT_EUNM
{
    NAS_EMM_SECU_PROC_SMC_NEW_SUCC,     /*激活新安全上下文的 SMC消息*/
    NAS_EMM_SECU_PROC_SMC_CUR_SUCC,
    NAS_EMM_SECU_PROC_SMC_FAIL,
    NAS_EMM_SECU_PROC_SMC_ERR,
    NAS_EMM_SECU_PROC_SMC_BUTT
};
typedef VOS_UINT32 NAS_EMM_SECU_PROC_SMC_RSLT_EUNM_UINT32;

enum    NAS_EMM_SMC_REJ_CAUSE_ENUM
{
    NAS_EMM_SMC_REJ_SECU_CAP_MISMATCH             = 0x17,
    NAS_EMM_SMC_REJ_UNSPECIFIED                   = 0x18,
    NAS_EMM_SMC_REJ_CAUSE_BUTT
};
typedef VOS_UINT8 NAS_EMM_SMC_REJ_CAUSE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_EMM_SECU_UNPROTECT_RLT_ENUM
 结构说明  : 解密,完整性保护是否成功
*****************************************************************************/
enum NAS_EMM_SECU_UNPROT_RLT_ENUM
{
    NAS_EMM_SECU_UNPROT_RLT_SUCC               = 0,   /* 解保护成功 */
    NAS_EMM_SECU_UNPROT_FAIL_NO_INTRA_MSG      = 1,   /* 解保护失败，无内部消息 */
    NAS_EMM_SECU_UNPROT_FAIL_WITH_INTRA_MSG    = 2,   /* 解保护失败，有内部消息 */
    NAS_EMM_SECU_UNPROT_RLT_BUTT
};
typedef VOS_UINT32 NAS_EMM_SECU_UNPROT_RLT_ENUM_UINT32;


/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/*****************************************************************************
结构名称    : NAS_LMM_UE_SECURITY_CAP_STRU
使用说明    : 24301-950 9.9.3.36
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUeSeuCapLen;   /*UE安全能力长度*/

    VOS_UINT8                           ucEEA;  /*LTE 加密算法*/
    VOS_UINT8                           ucEIA;  /*LTE 完整性保护算法*/
    VOS_UINT8                           ucUEA;  /*UMTS加密算法*/
    VOS_UINT8                           ucUIA;  /*UMTS完整性保护算法*/
    VOS_UINT8                           ucGEA;  /*GPRS加密算法*/

    VOS_UINT8                           aucRsv[2];
}NAS_LMM_UE_SECURITY_CAP_STRU;

/*****************************************************************************
结构名称    :NAS_EMM_SMC_CMD_STRU
使用说明    :Table 8.2.20.1: SECURITY MODE COMMAND message content
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                bitImeisvReq  :1;
    VOS_UINT32                                bitNonceUe    :1;
    VOS_UINT32                                bitNonceMme   :1;
    VOS_UINT32                                bitSpare      :29;

    VOS_UINT8                                 ucPdSt;           /* 协议头和安全头*/
    VOS_UINT8                                 ucMt;             /* 消息类型*/
    VOS_UINT8                                 ucSelAlgrthm;     /* UE选择的加密和完整性保护算法 */
    VOS_UINT8                                 ucKSI;            /* 密钥的索引 */
    NAS_LMM_UE_SECURITY_CAP_STRU              stUeSecuCap;      /* UE安全能力*/
    NAS_EMM_IMEISV_REQUEST_INFO_ENUM_UINT8    ucImeisvRsq;      /* 回复的消息是否需要IMEISV */
    VOS_UINT8                                 aucRsv[3];
    VOS_UINT8                                 aucNonceUe[NAS_EMM_SECU_NONCE_UE_LEN];
    VOS_UINT8                                 aucNonceMme[NAS_EMM_SECU_NONCE_MME_LEN];
}NAS_EMM_SECU_SMC_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern VOS_UINT8                           g_aucEia0Kasme[NAS_LMM_SECU_AUTH_KEY_ASME_LEN];

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

extern VOS_VOID    NAS_EMM_UpdateCurSecuCntxt(VOS_VOID);

extern VOS_UINT32  NAS_EMM_NotEia0SmcVerifyKsi(VOS_UINT8  ucSqn, VOS_UINT8 ucKsi);
extern VOS_UINT32  NAS_EMM_SmcVerifyNativeKsi( VOS_UINT8 ucKsiValue);
extern VOS_UINT32  NAS_EMM_SmcVerifyMappedKsi(VOS_UINT8  ucSqn ,VOS_UINT8 ucKsiValue);

extern VOS_UINT32  NAS_EMM_IsAlgUeSupported( VOS_UINT8 ucSelEca, VOS_UINT8 ucSelEia);
extern VOS_UINT32 NAS_EMM_Eia0SmcVerifyAlg( VOS_UINT8 ucSelEca, VOS_UINT8 ucSelEia);
extern VOS_UINT32  NAS_EMM_SmcCommProcess(
                              LRRC_LNAS_MSG_STRU  *pstSmcMsg);
extern NAS_EMM_IMEISV_REQUEST_INFO_ENUM_UINT8  NAS_EMM_IsImeisvReq( VOS_VOID );
extern  VOS_VOID    NAS_EMM_SecuSendSmcCmp(
                        NAS_EMM_IMEISV_REQUEST_INFO_ENUM_UINT8  enIfImeisvReq);
extern  VOS_VOID    NAS_EMM_SecuSendSmcRej(
                              NAS_EMM_SMC_REJ_CAUSE_ENUM_UINT8 enCause);
extern VOS_VOID     NAS_EMM_DeriveNewNasKey(
                              VOS_UINT8  *pucKasme,
                              VOS_UINT8   ucEca,
                              VOS_UINT8   ucEia);
extern VOS_UINT32   NAS_EMM_ComputeNasKey(
                              VOS_UINT8  *pucKasme,
                              VOS_UINT8  *pNasK,
                              NAS_EMM_SECU_NAS_KEY_TYPE_ENUM_UINT8 enNasKeyType,
                              VOS_UINT8   enProtAlgoType);
extern VOS_VOID     NAS_EMM_SendSecuParamToRrc( VOS_VOID );
extern VOS_UINT32  NAS_EMM_SmcVerifyUeSecuCap(
                        const NAS_LMM_UE_SECURITY_CAP_STRU    *pstUeSecuCap );
extern VOS_UINT32  NAS_EMM_SmcVerifyNonceUE(
                                        const NAS_EMM_SECU_SMC_STRU *pstSmcStru );
extern VOS_UINT32  NAS_EMM_DecodeSmcMsg(
                                        LRRC_LNAS_MSG_STRU      *pstCnSmcMsg,
                                        NAS_EMM_SECU_SMC_STRU   *pstSecurModeCtrl);
extern VOS_UINT32   NAS_EMM_SmcVerifyParam( LRRC_LNAS_MSG_STRU  *pstSmcMsg );
extern VOS_VOID     NAS_EMM_SecuGetNonceMmeInSmc( VOS_VOID );
extern VOS_VOID     NAS_EMM_NotEia0SmcIntCheckPara(
                                        LRRC_LNAS_MSG_STRU      *pstSmcMsg,
                                        NAS_EMM_PROT_PARAM_STRU *pstUnProtParam);
extern VOS_UINT32   NAS_EMM_SmcIntCheck( LRRC_LNAS_MSG_STRU  *pstSmcMsg );
extern VOS_VOID  NAS_EMM_SmcSucc( const LRRC_LNAS_MSG_STRU    *pstSmcMsg );
extern CIPHER_ALGORITHM_E NAS_EMM_GetIntegrityAlg( VOS_UINT8 ucSelEia);
extern CIPHER_ALGORITHM_E NAS_EMM_GetSecurityAlg( VOS_UINT8 ucSelEca);
extern VOS_UINT32 NAS_EMM_Eia0SmcVerifyKsi
(
    VOS_UINT8                           ucKsi
);
extern VOS_UINT32  NAS_EMM_NotEia0SmcVerifyParam
(
    const NAS_EMM_SECU_SMC_STRU              *pstSmcStru,
    VOS_UINT8                           ucSqn
);
extern VOS_UINT32  NAS_EMM_Eia0SmcVerifyParam
(
    const NAS_EMM_SECU_SMC_STRU              *pstSmcStru
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

#endif /* end of NasEmmSecuSmc.h */
