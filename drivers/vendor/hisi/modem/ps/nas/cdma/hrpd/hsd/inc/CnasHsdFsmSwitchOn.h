/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdFsmSwitchOn.h
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年12月9日
  最近修改   :
  功能描述   : CnasHsdFsmSwitchOn.c 的头文件
  函数列表   :
  修改历史      :
  1.日    期   : 2014年12月9日
    作    者   : h00300778
    修改内容   : 新生成函数

******************************************************************************/

#ifndef __CNAS_HSD_FSM_SWITCH_ON_H__
#define __CNAS_HSD_FSM_SWITCH_ON_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "hsd_mscc_pif.h"
#include "UsimPsInterface.h"
#include "CnasHsdCtx.h"


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
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

extern VOS_UINT32  CNAS_HSD_RcvCasStartCnf_SwitchOn_WaitCasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
extern VOS_UINT32  CNAS_HSD_RcvCardGetFileCnf_SwitchOn_WaitCardFileCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32  CNAS_HSD_RcvMsccStartReq_SwitchOn_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32  CNAS_HSD_RcvTiCasStartCnfExpired_SwitchOn_WaitCasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32  CNAS_HSD_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32  CNAS_HSD_RcvTiHsmStartCnfExpired_SwitchOn_WaitHsmStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32  CNAS_HSD_RcvTiHluStartCnfExpired_SwitchOn_WaitHluStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32  CNAS_HSD_RcvHsmStartCnf_SwitchOn_WaitHsmStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32  CNAS_HSD_RcvHluStartCnf_SwitchOn_WaitHluStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_VOID  CNAS_HSD_ReadNvimInfo_SwitchOn(VOS_UINT32 ul1xSupportFlag);

extern VOS_VOID  CNAS_HSD_SndCardReadFileReq(USIMM_CUIM_FILEID_ENUM_UINT16 enFileId);

extern VOS_VOID  CNAS_HSD_SaveCardStatus_SwitchOn(
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8     enCsimCardStatus,
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8     enUsimCardStatus
);

extern VOS_VOID CNAS_HSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf(VOS_UINT16 usEfId);


extern VOS_UINT32  CNAS_HSD_RcvEhsmStartCnf_SwitchOn_WaitEhsmStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32  CNAS_HSD_RcvTiEhsmStartCnfExpired_SwitchOn_WaitEhsmStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_VOID CNAS_HSD_ReadDefaultPrl(VOS_VOID);

extern VOS_UINT32 CNAS_HSD_Is1xSupport(MODEM_ID_ENUM_UINT16                enModemId);

#endif

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

#endif /* end of CnasHsdFsmSwitchOn.h */
