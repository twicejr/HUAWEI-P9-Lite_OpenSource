/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdFsmSwitchOn.h
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年7月3日
  最近修改   :
  功能描述   : CnasXsdFsmSwitchOn.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年7月3日
    作    者   : y00245242
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_XSD_FSM_SWITCH_ON_H__
#define __CNAS_XSD_FSM_SWITCH_ON_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "xsd_mscc_pif.h"
#include  "UsimPsInterface.h"
#include  "CnasCcb.h"


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

VOS_UINT32  CNAS_XSD_RcvCasStartCnf_SwitchOn_WaitCasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  CNAS_XSD_RcvCardGetFileCnf_SwitchOn_WaitCardFileCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  CNAS_XSD_RcvMsccStartReq_SwitchOn_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  CNAS_XSD_RcvTiCasStartCnfExpired_SwitchOn_WaitCasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  CNAS_XSD_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  CNAS_XSD_RcvTiXccStartCnfExpired_SwitchOn_WaitXccStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  CNAS_XSD_RcvTiXregStartCnfExpired_SwitchOn_WaitXregStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  CNAS_XSD_RcvXccStartCnf_SwitchOn_WaitXccStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  CNAS_XSD_RcvXregStartCnf_SwitchOn_WaitXregStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID  CNAS_XSD_ReadNvimInfo_SwitchOn(VOS_VOID);

VOS_VOID  CNAS_XSD_SndCardReadFileReq(USIMM_DEF_FILEID_ENUM_UINT32 enFileId);

VOS_VOID  CNAS_XSD_SaveCardStatus_SwitchOn(
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8    enCardStatus
);
VOS_VOID CNAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf(
    VOS_UINT16                          usEfId
);

VOS_VOID CNAS_XSD_ReadDefaultPrl(VOS_VOID);

VOS_VOID CNAS_XSD_ProcTestConfig_SwitchOn_Init(
    VOS_UINT8                           ucIsReadNvPrlDirectly,
    VOS_UINT8                           ucIsReadDefaultPrl,
    CNAS_CCB_CARD_STATUS_ENUM_UINT8     enCsimCardStatus,
    USIMM_DEF_FILEID_ENUM_UINT32        enHomeSidNidFileId
);

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

#endif /* end of CnasXsdFsmSwitchOn.h */
