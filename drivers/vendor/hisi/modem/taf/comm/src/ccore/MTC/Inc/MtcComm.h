/******************************************************************************

                  版权所有 (C), 2001-2013, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MtcComm.h
  版 本 号   : 初稿
  作    者   : l00198894
  生成日期   : 2013年8月13日
  最近修改   :
  功能描述   : MtcComm.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年8月13日
    作    者   : l00198894
    修改内容   : 创建文件

******************************************************************************/

#ifndef __MTCCOMM_H__
#define __MTCCOMM_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#include "MtcMmaInterface.h"

#include "MtcPsTransfer.h"

#include "MtcRcmInterface.h"

#include "CmmcaMtcInterface.h"
/* Added by wx270776 for OM融合, 2015-8-23, begin */
#include "TafNvInterface.h"
/* Added by wx270776 for OM融合, 2015-8-23, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CMMCA_MAX_EUTRA_NEIGHBOR_PLMN_NUM       (8)
#define CMMCA_MAX_ARFCN_NUM                     (8)
#define CBPCA_MSG_DATA_RSV_LEN                  (4)                 /* CBPCA收发的消息结构体中，数据临时长度 */

#define MTC_ALLOC_MSG_WITH_HDR(ulMsglen)\
            PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MTC, (ulMsglen))

#define MTC_GET_MSG_ENTITY(pstMsg)\
            ((VOS_VOID *)&(((MSG_HEADER_STRU *)(pstMsg))->ulMsgName))

#define MTC_GET_MSG_LENGTH(pstMsg)\
            (((MSG_HEADER_STRU *)(pstMsg))->ulLength)

#define MTC_CFG_MSG_HDR(pstMsg, ulRecvPid, ulMsgId)\
            ((MSG_HEADER_STRU *)(pstMsg))->ulSenderCpuId   = VOS_LOCAL_CPUID;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulSenderPid     = UEPS_PID_MTC;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulReceiverCpuId = VOS_LOCAL_CPUID;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulReceiverPid   = (ulRecvPid);\
            ((MSG_HEADER_STRU *)(pstMsg))->ulMsgName       = (ulMsgId)

#define MTC_CFG_I1_GAS_MSG_HDR(pstMsg, ulMsgId)\
            MTC_CFG_MSG_HDR(pstMsg, I1_UEPS_PID_GAS, ulMsgId)

#define MTC_SEND_MSG(pstMsg)\
            if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstMsg))\
            {\
                MTC_ERROR_LOG("MTC_SEND_MSG: Send message fail!\n");\
            }

/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
#define MTC_CFG_RCM_MSG_HDR(pstMsg, ulMsgId)\
            MTC_CFG_MSG_HDR(pstMsg, DSP_PID_RCM, ulMsgId)
/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */

#define MTC_CFG_IMSA_MSG_HDR(pstMsg, ulMsgId)\
            MTC_CFG_MSG_HDR(pstMsg, PS_PID_IMSA, ulMsgId)

#define MTC_NO_SESSION_INFO          (0)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
#if 0
/*****************************************************************************
 枚举名    : CMMCA_RAT_ID_ENUM_UINT8
 枚举说明  : CDMA接口枚举: 接入技术

  1.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
enum CMMCA_RAT_ID_ENUM
{
    CMMCA_RAT_NULL,
    CMMCA_CDMA2K1X      = 2,        /* 1X */
    CMMCA_GERAN,                    /* GSM */
    CMMCA_CDMA2KHRPD,               /* DO */
    CMMCA_UTRAN,                    /* 3GPP */
    CMMCA_CDMA2KAI,                 /* 1X&DO, for matching type MMSS_SYS_CDMA2000_AI */
    CMMCA_EUTRAN        = 9,        /* LTE */
    CMMCA_3GPPAI,                   /* GSM&UMTS&LTE, for matching type MMSS_SYS_3GPP_AI */
    CMMCA_RAT_ID_BUTT
};
typedef VOS_UINT8 CMMCA_RAT_ID_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16
 枚举说明  : CDMA接口枚举: cmd id

  1.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
enum CMMCA_MMC_RAT_CMD_ID_ENUM
{
    ID_CMMCA_MMC_RAT_OTHER_RAT_INFO_IND             = 0x18,
    ID_CMMCA_MMC_RAT_CMD_MAX,
};
typedef VOS_UINT8 CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16;
#endif

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
#if 0
/*****************************************************************************
 结构名    : CMMCA_OTHER_RAT_INFO_STRU
 结构说明  : CDMA发来的数据结构: LTE邻区信息

 1.日    期   : 2014年01月17日
   作    者   : l00198894
   修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEarfcn;                               /* EUTRA channel number */
    /* priority of EARFCN of the neighbir EUTRA system. 0xff means not provided */
    VOS_UINT8                           ucEarfcnPri;
    /* Min required signal threshold used for selecting an EARFCN,
        The actual threshold value in dB used to compare against the measured reference signal receive Power(RSRP).*/
    VOS_UINT8                           ucThreshX;
    /* Min ref power level to select EUTRA, which in dBm is equal to the minimum
        reference signal received power(RSRP) level of a EUTRA cell required for the UE to reselect EUTRA.*/
    VOS_UINT16                          usRxLevMinEutra;
    /* Offset to min ref power level to select EUTRA. 0xff means not provided */
    VOS_UINT8                           ucRxLevMinEutraOffset;
    /* Max TX power level UE may use when transmitting up-link of EUTRA */
    VOS_UINT8                           ucPeMax;
    /* measurement bandwidth Nrb value, Table 7.1-1 */
    VOS_UINT8                           ucMeasBandWidth;
    VOS_UINT8                           aucReserved1[2];
    VOS_UINT8                           ucNumPlmn;                              /* number of PLMN on this EARFCN channel */
    /* PLMN ID of the neighbor EUTRA system. 0xffffffff means not provided */
    VOS_UINT32                          aulPlmnId[CMMCA_MAX_EUTRA_NEIGHBOR_PLMN_NUM];
} CMMCA_OTHER_RAT_INFO_STRU;


/*****************************************************************************
 结构名    : CMMCA_OTHER_RAT_INFO_IND_STRU
 结构说明  : CDMA发来的数据结构: LTE邻区信息指示消息结构体

 1.日    期   : 2014年01月17日
   作    者   : l00198894
   修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    enCmdId;
    CMMCA_RAT_ID_ENUM_UINT8             enRatId;
    VOS_UINT8                           aucReserved1[1];
    VOS_UINT16                          usEarfcnListSize;
    CMMCA_OTHER_RAT_INFO_STRU           astOtherRatInfo[CMMCA_MAX_ARFCN_NUM];
}CMMCA_OTHER_RAT_INFO_IND_STRU;
#endif

/*****************************************************************************
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID MTC_RcvMmaRatModeInd(VOS_VOID *pMsg);

VOS_VOID MTC_SndMmaOtherModemDplmnNplmnInfoNotify(
    MODEM_ID_ENUM_UINT16                enModemId,
    MODEM_ID_ENUM_UINT16                enOtherModemId
);

VOS_VOID MTC_RcvMmaPowerStateInd(VOS_VOID *pMsg);

VOS_VOID MTC_RcvTafCsSrvInfoInd(VOS_VOID *pMsg);

VOS_VOID MTC_RcvMmaRegStatusInd(VOS_VOID *pMsg);

VOS_VOID MTC_RcvMmaCurrCampPlmnInfoInd(VOS_VOID *pMsg);

VOS_VOID MTC_SndMmaOtherModemInfoNotify(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MMA_PLMN_ID_STRU               *pstPlmnId,
    MTC_MMA_EPLMN_INFO_STRU            *pstEplmnInfo
);

VOS_VOID MTC_RcvMmaImsaStateInd(VOS_VOID *pMsg);

VOS_VOID MTC_RcvMmaEplmnInfoInd(VOS_VOID *pMsg);

VOS_VOID MTC_RcvRrcNcellInfoInd(VOS_VOID * pMsg);

VOS_VOID MTC_SndMmaNcellInfoInd(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MMA_TDS_NCELL_INFO_STRU        *pstTddNcellInfo,
    MTC_MMA_LTE_NCELL_INFO_STRU        *pstLteNcellInfo
);

VOS_UINT32 MTC_GetOtherModemId(
    MODEM_ID_ENUM_UINT16                enModemId,
    MODEM_ID_ENUM_UINT16               *penOtherModemId
);

#if 0
VOS_VOID MTC_RcvCbpcaDataInd(VOS_VOID *pMsg);

VOS_VOID MTC_ParseCmmcaOtherRatInfo(
    VOS_UINT8                         **ppMsgBuff,
    CMMCA_OTHER_RAT_INFO_STRU          *pstOtherRatInfo
);

VOS_UINT32 MTC_ParseCmmcaOtherRatInfoInd(
    VOS_UINT8                          *pMsg,
    CMMCA_OTHER_RAT_INFO_IND_STRU      *pstOtherRatInfoInd
);
#endif

VOS_VOID MTC_TransCdmaPlmnId(
    VOS_UINT32                          ulSrcPlmnId,
    MTC_MMA_PLMN_ID_STRU               *pstDetPlmnId
);

VOS_UINT32 MTC_IsContainPlmnId(
    MTC_MMA_PLMN_ID_STRU               *pstPlmnId,
    VOS_UINT32                          ulPlmnNum,
    MTC_MMA_PLMN_ID_STRU               *pastSrcPlmnId
);

VOS_UINT32 MTC_GetEplmnFromOtherRatInfoInd(
    MTC_MMA_EPLMN_INFO_STRU            *pstEplmnInfo,
    CMMCA_OTHER_RAT_INFO_IND_STRU      *pstOtherRatInfoInd
);

VOS_UINT32 MTC_GetLteNcellInfoFromOtherRatInfoInd(
    MTC_MMA_LTE_NCELL_INFO_STRU        *pstLteNcellInfo,
    CMMCA_OTHER_RAT_INFO_IND_STRU      *pstOtherRatInfoInd
);

VOS_VOID MTC_RcvCmmcaOtherRatInfoInd(VOS_VOID* pMsg);

/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
VOS_VOID MTC_ProcSetCdmaExtModemConnStateInfo(VOS_VOID* pMsg);

VOS_VOID MTC_ProcModemServiceConnStateInd(VOS_VOID *pMsg);

VOS_VOID MTC_ProcImsaSrvConnStateInfo(VOS_VOID* pMsg);

VOS_VOID MTC_ProcUsimmStateInd(VOS_VOID *pMsg);

/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */

VOS_VOID MTC_RcvGsmCellInfoExInd(VOS_VOID *pMsg);

VOS_VOID MTC_RcvMtaGsmCellInfoQryReq(VOS_VOID *pMsg);

VOS_VOID MTC_RcvTcStatusInfo(
    VOS_VOID                           *pMsg
);
MTC_RCM_RAT_MODE_ENUM_UINT16 MTC_ConvertRcmRatMode(
    MTC_NAS_RAT_MODE_ENUM_UINT16        enMtcNasRatMode
);
MTC_RCM_MODEM_RAT_CFG_ENUM_UINT16 MTC_ConvertToRcmRatCfg(
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16    enUsimmState,
    MTC_MODEM_RAT_CONFIG_STRU               *pstRatCfg
);

VOS_VOID MTC_RcvMmaImsVoiceCapInd(VOS_VOID *pMsg);

VOS_VOID MTC_RcvMmaRatCfgInd(
    VOS_VOID                           *pMsg
);

VOS_VOID MTC_ProcBeginSessionInd(VOS_VOID *pMsg);

VOS_VOID MTC_ProcEndSessionInd(VOS_VOID *pMsg);

PS_BOOL_ENUM_UINT8 MTC_IsNeedSndTasCsInfo2Rcm(
    MODEM_ID_ENUM_UINT16                enModemId,
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCsSrvConnState,
    MTC_CS_TYPE_ENUM_UINT8              enCsType
);

PS_BOOL_ENUM_UINT8 MTC_IsNeedBufModem0Msg(VOS_UINT32 ulSendPid);

PS_BOOL_ENUM_UINT8 MTC_IsNeedPopModem0BufMsg(VOS_UINT32 ulSendPid);

VOS_VOID MTC_ProcModem0BufMsg(VOS_VOID);


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

#endif /* end of MtcComm.h */
