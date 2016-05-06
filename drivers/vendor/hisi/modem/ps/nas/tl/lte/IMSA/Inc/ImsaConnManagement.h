/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : ImsaConnManagement.h
    Description : ImsaConnManagement.c头文件
    History     :
      1.sunbing 00049683    2013-06-19  Draft Enact


******************************************************************************/

#ifndef __IMSACONNMANAGEMENT_H__
#define __IMSACONNMANAGeMENT_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "ImsaIntraInterface.h"
#include    "vos.h"
#include    "ImsaPublic.h"
#include    "ImsaEntity.h"


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
#define IMSA_CONN_MAX_NV_SDF_NUM            (11)
#define IMSA_IPV6_PREFIX_LEN                (8)
#define IMSA_IPV6_PREFIX_BIT_LEN            (64)



#ifdef PS_ITT_PC_TEST_NAS
#define TI_IMSA_NRM_SIP_SIGAL_PDP_ORIG_TIMER_LEN        (10000)                  /*NRM_SIP_SIGAL_PDP_ORIG_TIMER的时间长度，in milliseconds*/
#define TI_IMSA_EMC_SIP_SIGAL_PDP_ORIG_TIMER_LEN        (10000)                  /*EMC_SIP_SIGAL_PDP_ORIG_TIMER的时间长度，in milliseconds*/
#define TI_IMSA_SIP_SIGAL_PDP_END_TIMER_LEN             (6000)                  /*SIP_SIGAL_PDP_END_TIMER的时间长度，in milliseconds*/
#define TI_IMSA_WAIT_IPV6_INFO_TIMER_LEN                (6000)                  /*WAIT_IPV6_INFO_TIMER的时间长度，in milliseconds*/
#else
#define TI_IMSA_NRM_SIP_SIGAL_PDP_ORIG_TIMER_LEN        (150000)                /*NRM_SIP_SIGAL_PDP_ORIG_TIMER的时间长度，in milliseconds*/
#define TI_IMSA_EMC_SIP_SIGAL_PDP_ORIG_TIMER_LEN        (30000)                 /*EMC_SIP_SIGAL_PDP_ORIG_TIMER的时间长度，in milliseconds*/
#define TI_IMSA_SIP_SIGAL_PDP_END_TIMER_LEN             (48000)                 /*SIP_SIGAL_PDP_END_TIMER的时间长度，in milliseconds*/
#define TI_IMSA_WAIT_IPV6_INFO_TIMER_LEN                (6000)                  /*WAIT_IPV6_INFO_TIMER的时间长度，in milliseconds*/
#endif



#define IMSA_CONN_SetupConnSucc(enConnType)\
    {\
        /* 将连接状态转到CONN态 */\
        IMSA_CONN_SetConnStatus((enConnType), IMSA_CONN_STATUS_CONN);\
\
        /* 通知SERVICE模块连接建立成功 */\
        IMSA_CONN_SndConnSetupInd(IMSA_CONN_RESULT_SUCCESS, (enConnType), IMSA_CONN_SIP_PDP_TYPE_SIGNAL);\
    }


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
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern VOS_CHAR                                g_acIpStringForSt_ipv4[IMSA_IPV4_ADDR_STRING_LEN + 1];
extern VOS_CHAR                                g_acIpStringForSt_ipv6[IMSA_IPV6_ADDR_STRING_LEN + 1];

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID IMSA_CONN_Init( VOS_VOID );
extern VOS_VOID IMSA_CONN_AssignOpid
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    VOS_UINT8                          *pucOpid
);
extern VOS_VOID IMSA_CONN_ProcConnSetupReq
(
    const IMSA_CONN_SETUP_REQ_STRU     *pstConnSetupReqMsg
);
extern VOS_VOID IMSA_CONN_ProcConnRelReq
(
    const IMSA_CONN_REL_REQ_STRU       *pstConnRelReqMsg
);
extern VOS_VOID IMSA_CONN_SndConnSetupInd
(
    IMSA_CONN_RESULT_ENUM_UINT32            enResult,
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType
);
extern VOS_VOID IMSA_CONN_SndConnMediaPdpModifyInd
(
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    IMSA_CONN_MEDIA_PDP_TYPE_ENUM_UINT32    enModifyType
);

extern VOS_VOID IMSA_CONN_SndConnRegPcscfInvalid( IMSA_CONN_TYPE_ENUM_UINT32 enConnType );
extern VOS_VOID IMSA_CONN_SndConnRelInd
(
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType
);
extern VOS_VOID IMSA_CONN_SndCdsSetImsBearerReq( VOS_VOID );
extern VOS_VOID IMSA_CONN_StartTimer
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_TIMER_ID_ENUM_UINT16           enTimerId
);
extern VOS_VOID IMSA_CONN_SetConnStatus
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_CONN_STATUS_ENUM_UINT8         enConnStatus
);
extern VOS_VOID IMSA_CONN_GetPrimPdpCntFromSelSdfPara
(
    const IMSA_SEL_SDF_PARA_STRU       *pstSelectedSdfPara,
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt
);
extern VOS_VOID IMSA_CONN_GetImsDailParaFromSelSdfPara
(
    const IMSA_SEL_SDF_PARA_STRU       *pstSelectedSdfPara,
    TAF_PS_DIAL_PARA_STRU              *pstDialParaInfo
);
extern VOS_VOID IMSA_CONN_SaveCurReqPdnType
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_IP_TYPE_ENUM_UINT8             enIpType
);
extern IMSA_PDP_STATE_ENUM_UINT8 IMSA_CONN_GetSipSignalPdpState
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_IP_TYPE_ENUM_UINT8             enIpType
);
extern VOS_VOID IMSA_CONN_ClearConnResource
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType
);
extern VOS_VOID IMSA_CONN_SaveFirstReqPdnType
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_IP_TYPE_ENUM_UINT8             enIpType
);
extern VOS_UINT32 IMSA_CONN_GetConnTypeByOpid
(
    VOS_UINT8                           ucOpid,
    IMSA_CONN_TYPE_ENUM_UINT32         *penConnType
);
extern VOS_UINT32 IMSA_CONN_IsConnStatusEqual
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_CONN_STATUS_ENUM_UINT8         enImsaConnStatus
);
extern VOS_VOID IMSA_CONN_SaveSipSignalPdpInfo
(
    IMSA_PDP_CNTXT_INFO_STRU                   *pstPdpInfo,
    const TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU    *pstPdpActivateCnf
);
extern VOS_VOID IMSA_CONN_ConfigPdpInfo2Reg
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    const IMSA_PDP_CNTXT_INFO_STRU     *pstPdpInfo
);
extern VOS_VOID IMSA_CONN_StopTimer
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_TIMER_ID_ENUM_UINT16           enTimerId
);
extern VOS_VOID IMSA_CONN_ConfigPdpInfo2Bsp
(
    const IMSA_PDP_CNTXT_INFO_STRU     *pstPdpInfo
);
extern VOS_VOID IMSA_CONN_ConfigPdpIPv6Info2Bsp
(
    const IMSA_PDP_CNTXT_INFO_STRU     *pstPdpInfo
);
extern VOS_UINT32 IMSA_CONN_GetPdpContextByPdpId
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    VOS_UINT8                           ucPdpId,
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32 *penSipPdpType,
    IMSA_PDP_CNTXT_INFO_STRU          **ppstPdpContext
);
extern VOS_UINT32 IMSA_CONN_SaveMediaPdpInfoWithSamePdpId
(
    IMSA_CONN_TYPE_ENUM_UINT32                  enConnType,
    const TAF_PS_CALL_PDP_ACTIVATE_IND_STRU    *pstPdpActivateInd
);

extern VOS_UINT32 IMSA_CONN_SaveMediaPdpInfoWithSameQci
(
    IMSA_CONN_TYPE_ENUM_UINT32                  enConnType,
    const TAF_PS_CALL_PDP_ACTIVATE_IND_STRU    *pstPdpActivateInd
);

extern VOS_VOID IMSA_CONN_SaveSipMediaPdpInfo
(
    IMSA_CONN_TYPE_ENUM_UINT32                  enConnType,
    const TAF_PS_CALL_PDP_ACTIVATE_IND_STRU    *pstPdpActivateInd
);
extern VOS_VOID IMSA_CONN_ModifySipPdpInfo
(
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32          enSipPdpType,
    IMSA_PDP_CNTXT_INFO_STRU                   *pstPdpInfo,
    const TAF_PS_CALL_PDP_MODIFY_IND_STRU      *pstPdpModifyInd
);
extern VOS_UINT32 IMSA_CONN_GetPdpContextByCid
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    VOS_UINT8                           ucCid,
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32 *penSipPdpType,
    IMSA_PDP_CNTXT_INFO_STRU          **ppstPdpContext
);
extern VOS_VOID IMSA_CONN_DeletePdpInfo
(
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    VOS_UINT8                               ucCid,
    VOS_UINT8                               ucRabId,
    VOS_UINT32                             *pulRegParaValid
);

extern VOS_UINT32 IMSA_CONN_HasActiveSipSignalPdp
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType
);
extern VOS_VOID IMSA_CONN_RequestApsRelConn
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType
);
extern VOS_VOID IMSA_CONN_SndConnRegParaInvalid( VOS_VOID );
extern VOS_VOID IMSA_CONN_SaveIpv6Info
(
    IMSA_PDP_CNTXT_INFO_STRU                   *pstPdpInfo,
    const TAF_PS_IPV6_INFO_IND_STRU            *pstIpv6InfoInd
);
extern VOS_VOID IMSA_CONN_ConvertIpAddress2String
(
    IMSA_IP_TYPE_ENUM_UINT8             enIpType,
    const VOS_UINT8                    *pucSrc,
    VOS_CHAR                           *pcDst
);

extern VOS_VOID IMSA_CONN_ClearResource( VOS_VOID );
extern VOS_UINT32 IMSA_CONN_IsEqualToSelectedCid
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    VOS_UINT8                           ucCid
);
extern VOS_VOID IMSA_CONN_PrintNrmConnState( VOS_VOID );
extern VOS_VOID IMSA_CONN_PrintEmcConnState( VOS_VOID );

extern VOS_UINT32 IMSA_CONN_FindSipSignalReStablishDialPara
(
    VOS_UINT8                           ucCid,
    VOS_UINT32                          ulSdfNum,
    const TAF_SDF_PARA_STRU            *pstSdfPara,
    VOS_UINT32                         *pulIndex
);

extern VOS_UINT32 IMSA_CONN_GetPdpContextByCidOrPdpId
(
    VOS_UINT8                                   ucCid,
    VOS_UINT8                                   ucPdpId,
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32          *penSipPdpType,
    IMSA_PDP_CNTXT_INFO_STRU                    **ppstPdpContext,
    IMSA_CONN_TYPE_ENUM_UINT32                  *penConnType
);


extern VOS_VOID IMSA_CONN_ClearNicPdpInfo(VOS_VOID);
extern VOS_VOID IMSA_CONN_DeletePdpId2Nic(VOS_VOID);
extern VOS_VOID IMSA_CONN_PrintNicPdpInfo(VOS_VOID);
extern VOS_UINT32 IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo(const IMSA_CONN_NIC_PDP_INFO_STRU *pstNicPdpInfo);
extern VOS_UINT32 IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo(const IMSA_CONN_NIC_PDP_INFO_STRU *pstNicPdpInfo);
extern VOS_VOID IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo(VOS_VOID);
extern VOS_UINT32 IMSA_CONN_Ipv4PdpAddrIsExistInNicPdpInfo(const IMSA_IP_ADDRESS_STRU *pstPdpAddr);
extern VOS_UINT32 IMSA_CONN_Ipv6PdpAddrIsExistInNicPdpInfo(const IMSA_IP_ADDRESS_STRU *pstPdpAddr);
extern VOS_UINT32 IMSA_CONN_PdpIdIsExistInNicPdpInfo(VOS_UINT8 ucPdpId, VOS_UINT32 *pulArrayIndex);
extern VOS_UINT32 IMSA_CONN_InquireNotUsedInNicPdpInfo(VOS_UINT32 *pulArrayIndex);
extern VOS_VOID IMSA_CONN_SaveNicPdpInfo(VOS_UINT8 ucPdpId,        VOS_UINT8 ucIsEmc, \
                                            VOS_UINT32 ulArrayIndex, const IMSA_IP_ADDRESS_STRU *pstPdpAddr);

extern VOS_VOID IMSA_CONN_ProcIPV4PdpInfoForNic(VOS_UINT8 ucIsEmc, IMSA_PDP_CNTXT_INFO_STRU *pstPdpCntxtInfo);
extern VOS_VOID IMSA_CONN_ProcIPV6PdpInfoForNic(VOS_UINT8 ucIsEmc, IMSA_PDP_CNTXT_INFO_STRU *pstPdpCntxtInfo);
extern VOS_VOID IMSA_CONN_ProcIPV4V6PdpInfoForNic(VOS_UINT8 ucIsEmc, IMSA_PDP_CNTXT_INFO_STRU *pstPdpCntxtInfo);
extern VOS_VOID IMSA_CONN_AddNormalPdpInfo2NicPdpInfo(VOS_VOID);
extern VOS_VOID IMSA_CONN_AddEmcPdpInfo2NicPdpInfo(VOS_VOID);
extern VOS_VOID IMSA_CONN_AddPdpInfo2NicPdpInfo(VOS_VOID);

extern VOS_UINT32 IMSA_CONN_SipSignalPdpActOrig
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    VOS_UINT8                           ucCid,
    IMSA_IP_TYPE_ENUM_UINT8             enIpType
);

extern VOS_UINT32 IMSA_CONN_IsVoiceMediaPdpType
(
    IMSA_PDP_TFT_INFO_STRU              *pstTft,
    VOS_UINT8                           ucQCI
);

extern VOS_VOID IMSA_CONN_ClearConnResourceExeptMedia
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType
);
#if (FEATURE_ON == FEATURE_PTM)
extern IMSA_ERR_LOG_PDNREJ_CAUSE_ENUM_UINT32  IMSA_PDN_CnRejCauseProc
(
    TAF_PS_CAUSE_ENUM_UINT32 enCause
);
extern IMSA_ERR_LOG_PDNREJ_CAUSE_ENUM_UINT32  IMSA_PDN_InterRejCauseProc
(
    IMSA_CONN_RESULT_ENUM_UINT32    enResult,
    TAF_PS_CAUSE_ENUM_UINT32        enCause
);
#endif
extern VOS_VOID IMSA_CONN_SetupConnFail
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_CONN_RESULT_ENUM_UINT32        enResult,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);
extern VOS_VOID IMSA_CONN_SndConnMediaSetupInd
(
    IMSA_CONN_RESULT_ENUM_UINT32            enResult,
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    IMSA_CONN_MEDIA_PDP_TYPE_ENUM_UINT32    enMediaPdpType
);

#if (FEATURE_ON == FEATURE_PTM)
extern IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_ENUM_UINT32  IMSA_Norm_PDN_RejCauseProc
(
    IMSA_CONN_RESULT_ENUM_UINT32    enResult
);
#endif
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

#endif /* end of ImsaConnManagement.h */




