/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmSwitchOn.h
  版 本 号   : 初稿
  作    者   : luokaihui / 00167671
  生成日期   : 2011年4月7日
  最近修改   :
  功能描述   : NasMmcFsmSwitchOn.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年4月7日
    作    者   : luokaihui / 00167671
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#ifndef __NASMMCFSMSWITCHON_H__
#define __NASMMCFSMSWITCHON_H__

#include  "vos.h"
#include "NasMmlCtx.h"
#include "MsccMmcInterface.h"





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
VOS_UINT32  NAS_MMC_RcvStartReq_SwitchOn_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvUsimGetFileRsp_SwitchOn_WaitSimFilesCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn_WaitSimFilesCnf(
    USIMM_DEF_FILEID_ENUM_UINT32        enEfId
);

VOS_UINT32  NAS_MMC_RcvTiReadSimFilesExpired_SwitchOn_WaitSimFilesCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmStartCnf_SwitchOn_WaitMmStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGmmStartCnf_SwitchOn_WaitMmStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiMmStartCnfExpired_SwitchOn_WaitMmStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGasStartCnf_SwitchOn_WaitGasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvWasStartCnf_SwitchOn_WaitWasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitGasStartCnfExpired_SwitchOn_WaitGasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvTiWaitWasStartCnfExpired_SwitchOn_WaitWasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if   (FEATURE_ON == FEATURE_LTE)
VOS_UINT32  NAS_MMC_RcvLmmStartCnf_SwitchOn_WaitLStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvTiLmmStartCnfExpired_SwitchOn_WaitLStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#endif

VOS_UINT32  NAS_MMC_GetLastRplmn_SwitchOn(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstLasRplmn
);


VOS_UINT32  NAS_MMC_IsImsiChange_SwitchOn(VOS_VOID);

VOS_UINT32 NAS_MMC_IsNeedClearCksn_SwitchOn(VOS_VOID);

VOS_VOID NAS_MMC_InitUserSpecPlmnId_SwitchOn(VOS_VOID);

VOS_VOID    NAS_MMC_ReadNvimInfo_SwitchOn(VOS_VOID);

VOS_VOID    NAS_MMC_UpdateNvRplmnWithSimRplmn_SwitchOn(VOS_VOID);

VOS_UINT32  NAS_MMC_IsSimRplmnInNvRplmn_SwitchOn(
    NAS_MML_PLMN_ID_STRU               *pstSimRplmnId
);

VOS_VOID    NAS_MMC_UpdateEplmn_SwitchOn(VOS_VOID);

VOS_VOID NAS_MMC_UpdateLastRplmnRat_LastRplmnRatInvalid_SwitchOn(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstLasRplmn,
    VOS_UINT8                           ucLastRplmnExistFlag
);



VOS_VOID NAS_MMC_RcvStartCnf_SwitchOn_ProcAsRatCapabilityStatus (VOS_VOID);

VOS_VOID NAS_MMC_RcvStartCnf_SwitchOn_InitRatForbidListCfg (VOS_VOID);

/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
VOS_VOID NAS_MMC_SavePlmnRatPrio_SwitchOn(
    MSCC_MMC_PLMN_RAT_PRIO_STRU          *pRcvPlmnRatPrio
);
/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

/* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
VOS_VOID NAS_MMC_Save3Gpp2RatPrio_SwitchOn(
    MSCC_MMC_3GPP2_RAT_STRU             *pst3Gpp2Rat
);
/* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

VOS_VOID NAS_MMC_SaveAllowRegDomain_SwitchOn(
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM_UINT8                   enRegDomain
);

VOS_VOID NAS_MMC_SndRatModeSwitchOnReq_SwitchOn(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat
);

VOS_VOID NAS_MMC_UpdateEhplmnInfo_SwitchOn(
    VOS_UINT8                           *pucImsi
);

VOS_VOID NAS_MMC_InitLastRplmnRat_SwitchOn(VOS_VOID);




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

#endif
