

#ifndef __TAFAPSMAIN_H__
#define __TAFAPSMAIN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "Ps.h"
#include  "TafFsm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
extern TAF_STA_STRU                           g_astTafApsMainFsmStaTbl[];
#define TAF_APS_GetMainFsmStaTbl()            (g_astTafApsMainFsmStaTbl)


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
extern VOS_VOID  TAF_APS_InitTask( VOS_VOID );

extern VOS_UINT32 TAF_APS_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pMsg
);

extern VOS_UINT32 TAF_APS_PreProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pMsg
);


extern VOS_VOID TAF_APS_RegMainFsm( VOS_VOID  );


extern VOS_VOID TAF_APS_RegSubFsm( VOS_VOID  );


extern VOS_VOID TAF_APS_RegPreFsm( VOS_VOID  );

extern VOS_UINT32 TAF_APS_FSM_ProcessEvent(
    VOS_UINT32                          ulCurState,
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg,
    TAF_FSM_DESC_STRU                  *pstFsmDesc
);

extern VOS_VOID  TAF_APS_InitCtx( VOS_VOID );

extern VOS_VOID  TAF_APS_ProcMsg(
    struct MsgCB                       *pstMsg
);

extern VOS_VOID  TAF_APS_RegFsm( VOS_VOID );

extern VOS_VOID  TAF_APS_PostProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_BuildEventType(
    struct MsgCB                       *pstMsg
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

#endif /* end of TafApsMain.h */
