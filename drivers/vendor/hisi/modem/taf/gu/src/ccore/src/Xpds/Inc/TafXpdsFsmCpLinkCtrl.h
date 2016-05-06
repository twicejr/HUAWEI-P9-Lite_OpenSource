/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsFsmUpLinkCtrl.h
  版 本 号   : 初稿
  作    者   : OM_AcpuIccInfoInit
  生成日期   : 2015年8月27日
  最近修改   :
  功能描述   : TafXpdsFsmUpLinkCtrl.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年8月27日
    作    者   : OM_AcpuIccInfoInit
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAFXPDSFSMUPLINKCTRL_H__
#define __TAFXPDSFSMUPLINKCTRL_H__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include "TafXpdsFsmCpLinkCtrlTbl.h"

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

extern VOS_UINT32 TAF_XPDS_RcvTimerExpireForExitFsm_CpLinkCtrl(
       VOS_UINT32                          ulEventType,
       struct MsgCB                       *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXccAnsCallCnf_CpLinkCtrl_WaitAnsCallCnf(
       VOS_UINT32                          ulEventType,
       struct MsgCB                       *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXccIncomingCallInd_CpLinkCtrl_Init(
       VOS_UINT32                          ulEventType,
       struct MsgCB                       *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXccOrigCallCnf_CpLinkCtrl_Init(
       VOS_UINT32                          ulEventType,
       struct MsgCB                       *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXccCallConnInd_CpLinkCtrl_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXccServConnInd_CpLinkCtrl_WaitServConnIndMO(
       VOS_UINT32                          ulEventType,
       struct MsgCB                       *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXccServConnInd_CpLinkCtrl_WaitServConnIndMT(
           VOS_UINT32                          ulEventType,
           struct MsgCB                       *pstMsg
       );
extern VOS_UINT32  TAF_XPDS_RcvXpdsCtrlPlaneReq_CpLinkCtrl_Init(
       VOS_UINT32                          ulEventType,
       struct MsgCB                       *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvDataIndMsg_CpLinkCtrl(
    VOS_UINT32                          ulEventType,
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

#endif /* end of TafXpdsFsmUpLinkCtrl.h */

