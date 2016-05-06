/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmSyscfg.h
  版 本 号   : 初稿
  作    者   : z00161729
  生成日期   : 2011年7月5日
  最近修改   :
  功能描述   : NasMmcFsmSyscfg.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年7月5日
    作    者   : z00161729
    修改内容   : 创建文件

******************************************************************************/
#ifndef __NASMMCFSMSYSCFG_H__
#define __NASMMCFSMSYSCFG_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"

/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

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
VOS_UINT32  NAS_MMC_RcvMsccSysCfgSetReq_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32  NAS_MMC_RcvGasSysCfgCnf_SysCfg_WaitGasSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGasSuspendInd_SysCfg_WaitGasSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGasSysCfgCnfExpired_SysCfg_WaitGasSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvWasSysCfgCnf_SysCfg_WaitWasSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvWasSuspendInd_SysCfg_WaitWasSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvWasSysCfgCnfExpired_SysCfg_WaitWasSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGmmSignalingStatusInd_SysCfg_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_MMC_RcvMmConnInfoInd_SysCfg_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcMmRelInd_SysCfg_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmRelInd_SysCfg_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32  NAS_MMC_RcvGmmTbfRelInd_SysCfg_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvWasSuspendInd_SysCfg_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGasSuspendInd_SysCfg_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitRrcConnRelExpired_SysCfg_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32  NAS_MMC_RcvLmmSysCfgCnf_SysCfg_WaitLmmSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmSuspendInd_SysCfg_WaitLmmSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmSysCfgCnfExpired_SysCfg_WaitLmmSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmMmcStatusInd_SysCfg_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitEpsConnRelIndExpired_SysCfg_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32  NAS_MMC_RcvLmmSuspendInd_SysCfg_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#endif

/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
VOS_UINT32  NAS_MMC_IsPlmnSelectionNeeded_SysCfg(
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgSetParm
);

VOS_UINT32  NAS_MMC_IsCurrentBandSetted_SysCfg(
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgSetParm
);
VOS_UINT32  NAS_MMC_IsCurrentRatSetted_SysCfg(
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgSetParm
);

VOS_VOID  NAS_MMC_SaveUserSyscfgInfo_SysCfg(
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgMsg
);

VOS_VOID NAS_MMC_SetRatModeSysCfgReq_SysCfg(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat,
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgMsg
);
VOS_VOID  NAS_MMC_UpdateCellInfo_SysCfg(VOS_VOID);

VOS_UINT32  NAS_MMC_CheckRoamSettingPlmnSelection_SysCfg(
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgSetParm
);

NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetDestModeRat_SysCfg(
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgSetParm
);

/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */


VOS_UINT32 NAS_MMC_IsNeedAttachPs_SysCfg(VOS_VOID);

VOS_VOID  NAS_MMC_Save3Gpp2RatPrio_Syscfg(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
);

VOS_VOID   NAS_MMC_ConvertMsccRatTypeToMml3GPP2RatType(
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enMsccRatType,
    NAS_MML_3GPP2_RAT_TYPE_ENUM_UINT8                      *penMml3GPP2RatType
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

#endif /* end of NasMmcSuspendProcAct.h */

