/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Test_AtMntn.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2012年5月17日
  最近修改   :
  功能描述   : Test_AtMntn.cpp 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年5月17日
    作    者   : l60609
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TEST_ATMNTN_H__
#define __TEST_ATMNTN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "AtMntn.h"

#include "ATCmdProc.h"

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

extern VOS_VOID At_HookBufferCmd(VOS_UINT8 ucIndex, VOS_UINT8* pData, VOS_UINT16 usLen);
extern TAF_VOID At_HookResult(TAF_UINT8 ucIndex, TAF_UINT8* pData, TAF_UINT16 usLen);
extern VOS_VOID AT_MNTN_TraceEvent(VOS_VOID *pMsg);
extern VOS_VOID AT_MNTN_TraceInputMsc(
    VOS_UINT8                           ucIndex,
    AT_DCE_MSC_STRU                    *pstDceMsc
);
extern VOS_VOID AT_MNTN_TraceOutputMsc(
    VOS_UINT8                           ucIndex,
    AT_DCE_MSC_STRU                    *pstDceMsc
);
extern VOS_VOID AT_MNTN_TraceStartFlowCtrl(
    VOS_UINT8                           ucIndex,
    AT_FC_DEVICE_TYPE_ENUM_UINT32       enFcDevice
);
extern VOS_VOID AT_MNTN_TraceStopFlowCtrl(
    VOS_UINT8                           ucIndex,
    AT_FC_DEVICE_TYPE_ENUM_UINT32       enFcDevice
);
extern VOS_VOID AT_MNTN_TraceRegFcPoint(
    VOS_UINT8                           ucIndex,
    AT_FC_POINT_TYPE_ENUM_UINT32        enFcPoint
);
extern VOS_VOID AT_MNTN_TraceDeregFcPoint(
    VOS_UINT8                           ucIndex,
    AT_FC_POINT_TYPE_ENUM_UINT32        enFcPoint
);
extern VOS_VOID AT_InitHsUartStats(VOS_VOID);
extern VOS_VOID AT_InitModemStats(VOS_VOID);
extern VOS_VOID AT_ShowPsEntityInfo(VOS_UINT8 ucCallId);
extern VOS_VOID AT_ShowResetStatsInfo(VOS_VOID);
extern VOS_VOID AT_ShowHsUartNvStats(VOS_VOID);
extern VOS_VOID AT_ShowHsUartConfigInfo(VOS_VOID);
extern VOS_VOID AT_ShowHsUartIoctlStats(VOS_VOID);
extern VOS_VOID AT_ShowHsUartDataStats(VOS_VOID);
extern VOS_VOID AT_ShowModemDataStats(VOS_VOID);
extern VOS_VOID AT_ShowPsEntityInfo(VOS_UINT8 ucCallId);
extern VOS_VOID AT_Help(VOS_VOID);
extern AT_UART_FORMAT_PARAM_STRU *AT_HSUART_GetFormatParam(
    AT_UART_FORMAT_ENUM_UINT8           enFormat
);

extern void UT_STUB_INIT(void);



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

#endif /* end of Test_AtMntn.h */
