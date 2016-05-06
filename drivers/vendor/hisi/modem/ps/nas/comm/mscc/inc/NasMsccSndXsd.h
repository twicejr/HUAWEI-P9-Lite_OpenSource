

#ifndef __NAS_MSCC_SND_XSD_H__
#define __NAS_MSCC_SND_XSD_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "xsd_mscc_pif.h"
#include  "NasMsccPifInterface.h"
#include  "PsCommonDef.h"
#include  "NasMsccCtx.h"
#include  "MmaMsccInterface.h"
#include  "NasMsccFsmMain.h"
#include  "hsd_mscc_pif.h"

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
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID NAS_MSCC_SndXsdStartReq(
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enCsimStatus,
    NAS_MSCC_PIF_RAT_PRIO_STRU                             *pstRatPrio
);

VOS_VOID NAS_MSCC_SndXsdPowerOffReq(
    NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM_UINT32                    enCause
);

VOS_VOID NAS_MSCC_SndXsdCdmaMoCallStartNtf(
    MMA_MSCC_CDMA_MO_CALL_START_NTF_STRU         *pstCdmaMoCallStartNtf
);

VOS_VOID NAS_MSCC_SndXsdCdmaMoCallRedialSysAcqNtf(
    MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU         *pstCdmaMoCallRedialSysAcqNtf
);

VOS_VOID NAS_MSCC_SndXsdCdmaMoCallSuccessNtf(
    MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU         *pstCdmaMoCallSuccessNtf
);

VOS_VOID NAS_MSCC_SndXsdCdmaMoCallEndNtf(
    MMA_MSCC_CDMA_MO_CALL_END_NTF_STRU *pstCdmaMoCallEndNtf
);

VOS_VOID NAS_MSCC_SndXsdCfreqLockNtf(
    MMA_MSCC_CFREQ_LOCK_NTF_STRU       *pstCfreqLockNtf,
    VOS_UINT32                          ulIsSupport1x
);

VOS_VOID NAS_MSCC_SndXsdCdmacsqSetReq(
    MMA_MSCC_CDMACSQ_SET_REQ_STRU       *pstCdmacsqSetReq
);

VOS_VOID NAS_MSCC_SndXsdSysAcqReq(
    MSCC_XSD_SYS_ACQ_TYPE_ENUM_UINT8    enXsdSystemAcqType
);


VOS_VOID NAS_MSCC_SndXsdSysCfgReq(
    MMA_MSCC_SYS_CFG_SET_REQ_STRU      *pstSysCfgReq
);
VOS_VOID NAS_MSCC_SndXsdHrpdCasStatusInd(
    HSD_MSCC_CAS_STATUS_IND_STRU       *pstCasStatusInd
);

VOS_VOID NAS_MSCC_SndXsdPowerSaveReq(
    NAS_MSCC_PIF_POWER_SAVE_TYPE_ENUM_UINT8                 enPowerSaveReason
);

VOS_VOID NAS_MSCC_SndXsdHandsetInfoQryReq(
    VOS_UINT32                          ulInfoType
);


VOS_VOID NAS_MSCC_SndXsdSrvAcqReq(
    MMA_MSCC_SRV_ACQ_REQ_STRU          *pstSrvAcqReq
);

VOS_VOID NAS_MSCC_SndXsdBeginSessionNotify(
    MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU *pstBeginSessionNtf
);

VOS_VOID NAS_MSCC_SndXsdEndSessionNotify(
    MMA_MSCC_END_SESSION_NOTIFY_STRU   *pstEndSessionNtf
);

VOS_VOID NAS_MSCC_SndXsdEndEmcCallBackNtf( VOS_VOID );

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

#endif /* end of NasMsccSndXsd.h */
