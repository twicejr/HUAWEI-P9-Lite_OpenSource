

#ifndef __NASEMMCPUBLIC_H__
#define __NASEMMCPUBLIC_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "NasLmmPubMOsa.h"
#include  "NasEmmcEmmInterface.h"
#include  "MmcLmmInterface.h"
#include  "NasEmmcMain.h"



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
#define NAS_EMMC_NULL_PTR               VOS_NULL_PTR

#define NAS_EMMC_BIT_SLCT               1
#define NAS_EMMC_BIT_NO_SLCT            0

#define NAS_EMMC_NULL                   0
#define NAS_EMMC_INVALID_CELLID         0xffff


#define NAS_EMMC_LEN_VOS_MSG_HEADER     20

#define NAS_EMMC_MAX_FORBTA_NUM         NAS_LMM_MAX_FORBLA_NUM

#define NAS_LMM_EMMC_LOG_INFO(String)     NAS_LMM_LOG_INFO(LOG_SUBMOD_ID_NAS_LMM_MMC, String)
#define NAS_LMM_EMMC_LOG_NORM(String)     NAS_LMM_LOG_NORM(LOG_SUBMOD_ID_NAS_LMM_MMC, String)
#define NAS_LMM_EMMC_LOG_WARN(String)     NAS_LMM_LOG_WARN(LOG_SUBMOD_ID_NAS_LMM_MMC, String)
#define NAS_LMM_EMMC_LOG_ERR( String)     NAS_LMM_LOG_ERR(LOG_SUBMOD_ID_NAS_LMM_MMC, String)

#define NAS_LMM_EMMC_LOG1_INFO(String, Para1)    NAS_LMM_LOG1_INFO(LOG_SUBMOD_ID_NAS_LMM_MMC, String, Para1)
#define NAS_LMM_EMMC_LOG1_NORM(String, Para1)    NAS_LMM_LOG1_NORM(LOG_SUBMOD_ID_NAS_LMM_MMC, String, Para1)
#define NAS_LMM_EMMC_LOG1_WARN(String, Para1)    NAS_LMM_LOG1_WARN(LOG_SUBMOD_ID_NAS_LMM_MMC, String, Para1)
#define NAS_LMM_EMMC_LOG1_ERR( String, Para1)    NAS_LMM_LOG1_ERR(LOG_SUBMOD_ID_NAS_LMM_MMC, String,  Para1)

#define NAS_LMM_EMMC_LOG2_INFO(String, Para1, Para2)     NAS_LMM_LOG2_INFO(LOG_SUBMOD_ID_NAS_LMM_MMC, String, Para1, Para2)
#define NAS_LMM_EMMC_LOG2_NORM(String, Para1, Para2)     NAS_LMM_LOG2_NORM(LOG_SUBMOD_ID_NAS_LMM_MMC, String, Para1, Para2)
#define NAS_LMM_EMMC_LOG2_WARN(String, Para1, Para2)     NAS_LMM_LOG2_WARN(LOG_SUBMOD_ID_NAS_LMM_MMC, String, Para1, Para2)
#define NAS_LMM_EMMC_LOG2_ERR( String, Para1, Para2)     NAS_LMM_LOG2_ERR(LOG_SUBMOD_ID_NAS_LMM_MMC, String,  Para1, Para2)

#define NAS_LMM_EMMC_LOG3_INFO(String, Para1, Para2, Para3)     NAS_LMM_LOG3_INFO(LOG_SUBMOD_ID_NAS_LMM_MMC, String, Para1, Para2, Para3)
#define NAS_LMM_EMMC_LOG3_NORM(String, Para1, Para2, Para3)     NAS_LMM_LOG3_NORM(LOG_SUBMOD_ID_NAS_LMM_MMC, String, Para1, Para2, Para3)
#define NAS_LMM_EMMC_LOG3_WARN(String, Para1, Para2, Para3)     NAS_LMM_LOG3_WARN(LOG_SUBMOD_ID_NAS_LMM_MMC, String, Para1, Para2, Para3)
#define NAS_LMM_EMMC_LOG3_ERR( String, Para1, Para2, Para3)     NAS_LMM_LOG3_ERR(LOG_SUBMOD_ID_NAS_LMM_MMC, String,  Para1, Para2, Para3)


/* 打包RRC消息头 */
#define NAS_EMMC_COMP_RRC_MSG_HEADER(pMsg, ulMsgLengthNoHeader) \
            {\
                (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID; \
                (pMsg)->ulSenderPid         = PS_PID_MM; \
                (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID; \
                (pMsg)->ulReceiverPid       = PS_PID_ERRC; \
                (pMsg)->ulLength            = (ulMsgLengthNoHeader); \
            }

/* 打包ERMM消息头 */
#define NAS_EMMC_COMP_ERMM_MSG_HEADER(pMsg, ulMsgLengthNoHeader) \
            {\
                (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID; \
                (pMsg)->ulSenderPid         = PS_PID_MM; \
                (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID; \
                (pMsg)->ulReceiverPid       = PS_PID_ERMM; \
                (pMsg)->ulLength            = (ulMsgLengthNoHeader); \
            }


/* 打包MM内部消息头 */
#define NAS_EMMC_COMP_MM_INTRAMSG_HEADER(pMsg, ulMsgLengthNoHeader) \
            {\
                (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID; \
                (pMsg)->ulSenderPid         = PS_PID_MM; \
                (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID; \
                (pMsg)->ulReceiverPid       = PS_PID_MM; \
                (pMsg)->ulLength            = (ulMsgLengthNoHeader); \
            }

/* 打包MMC消息头 */
#define NAS_EMMC_COMP_MMC_MSG_HEADER(pMsg, ulMsgLengthNoHeader) \
            {\
                (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID; \
                (pMsg)->ulSenderPid         = PS_PID_MM; \
                (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID; \
                (pMsg)->ulReceiverPid       = WUEPS_PID_MMC; \
                (pMsg)->ulLength            = (ulMsgLengthNoHeader); \
            }


/*#define NAS_EMMC_GetReqPlmnAddr()           (&(NAS_EMMC_GetEmmcInfoAddr()->stReqPlmn))*/



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
 结构名    : NAS_EMMC_OM_LOG_FORBIDDEN_PLMN_LIST_STRU
 结构说明  : Fobidden plmn list 上报
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                         stMsgHeader;     /*_H2ASN_Skip*/
    NAS_EMMC_USER_SPEC_PLMN_FLAG_UINT32     enUserSpecPlmnFlag;
    NAS_MM_PLMN_LIST_STRU                   stForbPlmn;
    NAS_MM_PLMN_LIST_STRU                   stForbPlmnForGprs;
    NAS_MM_FORB_TA_LIST_STRU                stForbTaForRoam;    /* forbidden tracking areas for roaming*/
    NAS_MM_FORB_TA_LIST_STRU                stForbTaForRpos;    /* forbidden tracking areas for
                                                               regional provision of service*/
    NAS_MM_FORB_TA_LIST_STRU                stForbTaForRej15;   /* 用户指定搜网，ATTACH或TAU拒绝#15后保存的列表*/
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST  stGradualForbTaList;    /* 渐进Forb临时列表 */
}NAS_EMMC_OM_LOG_FORBIDDEN_INFO_STRU;




/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID NAS_EMMC_FillRrcNasForbTaList
(
    LRRC_LNAS_FORB_TA_LIST_STRU           *pstRrcNasForbTaList
);

extern VOS_VOID NAS_EMMC_GetCurrentTa( NAS_MM_TA_STRU *pstTa );

extern VOS_VOID  NAS_EMMC_GetForbPlmnInfo
(
    NAS_MM_PLMN_LIST_STRU               *pstFPlmn,
    NAS_MM_PLMN_LIST_STRU               *pstFPlmnForGprs
);
extern VOS_VOID NAS_EMMC_GetCurrentForbInfo
(
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32  *pulForbdInfo
);
extern VOS_VOID  NAS_EMMC_ProcessMmcLteSysInfoInd
(
    const MMC_LMM_SYS_INFO_STRU        *pstLteInfoIndMsg,
    EMMC_EMM_CHANGE_INFO_ENUM_UINT32   *pulChangeInfo,
    EMMC_EMM_CELL_STATUS_ENUM_UINT32   *penCellStatus,
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32 *penForbdInfo
);
extern VOS_VOID NAS_EMMC_DeleteForbTa
(
    const NAS_MM_TA_STRU               *pstTa,
    NAS_MM_TA_LIST_STRU                *pstTaList
);
extern VOS_VOID  NAS_EMMC_UpdateForbTaList( VOS_VOID );
extern VOS_VOID  NAS_EMMC_DeleteCurrentAreaCellId( VOS_VOID );
extern VOS_VOID  NAS_EMMC_ProcessRrcAreaLostInd(VOS_VOID);
extern VOS_VOID  NAS_EMMC_ProcessMmcLteSysInfoIndTaOrCellID
(
    const MMC_LMM_SYS_INFO_STRU          *pstLteInfoIndMsg,
    VOS_UINT32                           *pulChangeInfo
);
extern VOS_VOID  NAS_EMMC_FillUserSpecRrcNasForbTaList
(
    const NAS_MM_PLMN_ID_STRU  *pstPlmnId,
    NAS_MM_TA_LIST_STRU  *pstTaList
);
extern VOS_UINT32 NAS_EMMC_PlmnMatchRej18PlmnList
(
    NAS_MM_PLMN_ID_STRU *pstPlmnId
);

VOS_UINT32 NAS_LMM_IsCellStatusNormal
(
    MMC_LMM_PLMN_ID_STRU               *pstPlmn,
    const   NAS_MM_TA_STRU             *pstTa
);

extern VOS_VOID NAS_EMMC_ProcessRrcNotCampOnInd(VOS_VOID);
extern VOS_UINT32 NAS_EMMC_IsBgListSearch(MMC_LMM_PLMN_SRCH_TYPE_ENUM_UINT32 ulSearchType);
extern VOS_VOID NAS_EMMC_SndOmLogForbiddenInfo(VOS_VOID);
#if(FEATURE_ON == FEATURE_CSG)
extern VOS_UINT32 NAS_EMMC_IsBgCsgListSearch(VOS_VOID);
#endif

extern VOS_UINT32  NAS_EMMC_GetUserSpecPlmnFlag(VOS_VOID);

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

#endif /* end of NasEmmcPublic.h */
