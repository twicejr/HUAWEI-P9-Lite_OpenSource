

#ifndef __NAS_MSCC_SND_HSD_H__
#define __NAS_MSCC_SND_HSD_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "MmaMsccInterface.h"
#include  "hsd_mscc_pif.h"
#include  "NasMsccFsmMain.h"
#include  "MsccMmcInterface.h"
#include  "NasMsccMlplMsplParse.h"

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
VOS_VOID NAS_MSCC_SndHsdStartReq(
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enCsimStatus,
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enUsimStatus,
    NAS_MSCC_PIF_RAT_PRIO_STRU                             *pstRatPrio
);

VOS_VOID NAS_MSCC_SndHsdPowerOffReq(
    MSCC_HSD_POWER_OFF_CAUSE_ENUM_UINT32                    enCause
);

VOS_VOID NAS_MSCC_SndHsdCdmaMoCallStartNtf(
    MMA_MSCC_CDMA_MO_CALL_START_NTF_STRU         *pstCdmaMoCallStartNtf
);

VOS_VOID NAS_MSCC_SndHsdSysAcqReq(
    MSCC_HSD_ACQUIRE_REASON_ENUM_UINT32 enAcqReason,
    VOS_UINT8                           ucHighPrioHrpdNum,
    VOS_VOID                           *pucHighPrioHrpdList
);

VOS_VOID NAS_MSCC_SndHsdCdmaMoCallRedialSysAcqNtf(
    MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU         *pstCdmaMoCallRedialSysAcqNtf
);

VOS_VOID NAS_MSCC_SndHsdCdmaMoCallSuccessNtf(
    MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU         *pstCdmaMoCallSuccessNtf
);

VOS_VOID NAS_MSCC_SndHsdCdmaMoCallEndNtf(
    MMA_MSCC_CDMA_MO_CALL_END_NTF_STRU *pstCdmaMoCallEndNtf
);

VOS_VOID NAS_MSCC_SndHsdCfreqLockNtf(
    MMA_MSCC_CFREQ_LOCK_NTF_STRU       *pstCfreqLockNtf
);

VOS_VOID NAS_MSCC_SndHsdCdmacsqSetReq(
    MMA_MSCC_CDMACSQ_SET_REQ_STRU       *pstCdmacsqSetReq
);
VOS_VOID NAS_MSCC_SndHsdDisableLteNtf(VOS_VOID);

VOS_VOID NAS_MSCC_SndHsd1xSysChgInd(
    VOS_UINT8                           ucIs1xAvail,
    MSCC_HSD_1X_SYS_INFO_STRU          *pst1xSysInfo
);

VOS_VOID NAS_MSCC_SndHsdPowerSaveReq(VOS_VOID);

VOS_VOID NAS_MSCC_SndHsdBgSearchReq(
    VOS_RATMODE_ENUM_UINT32             enRatMode
);

VOS_VOID NAS_MSCC_SndHsdStopBgSearchReq(VOS_VOID);

VOS_VOID NAS_MSCC_SndHsdQryHrpdSysInfoReq(
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8                  enDestBsrSysType,
    VOS_UINT8                                               ucHrpdSysNum,
    MSCC_MMC_HRPD_SYS_STRU                                 *pstHrpdSysList
);

VOS_VOID NAS_MSCC_SndHsdSysCfgReq(
    MMA_MSCC_SYS_CFG_SET_REQ_STRU      *pstSysCfgReq
);

VOS_VOID NAS_MSCC_SndHsdHdrcsqSetReq(
    MMA_MSCC_HDR_CSQ_SET_REQ_STRU       *pstHdrcsqSetReq
);

VOS_VOID NAS_MSCC_SndHsdSrvAcqReq(
    MMA_MSCC_SRV_ACQ_REQ_STRU          *pstSrvAcqReq
);

VOS_VOID NAS_MSCC_SndHsdBeginSessionNotify(
    MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU *pstBeginSessionNtf
);

VOS_VOID NAS_MSCC_SndHsdEndSessionNotify(
    MMA_MSCC_END_SESSION_NOTIFY_STRU   *pstEndSessionNtf
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

#endif /* end of NasMsccSndHsd.h */
