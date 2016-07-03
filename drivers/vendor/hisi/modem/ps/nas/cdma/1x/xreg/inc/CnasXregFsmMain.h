

#ifndef __CNAS_XREG_FSM_MAIN_H__
#define __CNAS_XREG_FSM_MAIN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"


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

extern VOS_UINT32 CNAS_XREG_RcvStartReq_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_RcvSwitchOnRslt_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_RcvPowerOffReq_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_RcvStartReq_UnReg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


extern VOS_UINT32 CNAS_XREG_RcvPowerOffReq_UnReg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_RcvAccessInd_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_RcvRegedDataInd_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_RcvRegReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_RcvRegCnf_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_SIDNIDRegTimeout_Reged(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_ZoneRegTimeout_Reged(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_VOID CNAS_XREG_WriteNvimInfo_PowerOff(VOS_VOID);

extern VOS_VOID CNAS_XREG_ProcPowerOffReq(VOS_VOID);

extern VOS_UINT32 CNAS_XREG_RcvPwrOffTimeOut_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
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

#endif /* end of CnasXregFsmMain.h */
