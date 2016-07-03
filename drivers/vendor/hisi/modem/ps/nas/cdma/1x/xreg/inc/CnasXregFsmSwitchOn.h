

#ifndef __CNAS_XREG_FSM_SWITCH_ON_H__
#define __CNAS_XREG_FSM_SWITCH_ON_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "UsimPsInterface.h"


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

VOS_UINT32  CNAS_XREG_RcvXsdStartReq_SwitchOn_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  CNAS_XREG_RcvCardGetFileCnf_SwitchOn_WaitCardFileCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  CNAS_XREG_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID    CNAS_XREG_SndCardReadFileReq(USIMM_CUIM_FILEID_ENUM_UINT16 enFileId);

VOS_VOID    CNAS_XREG_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf(
    VOS_UINT16                          usEfId
);

VOS_VOID CNAS_XREG_ReadNvimInfo_SwitchOn(VOS_VOID);

extern VOS_UINT8 TAF_SDC_GetSimType(VOS_VOID);
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

