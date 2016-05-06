/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Test_AtOutputProc.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2012年5月17日
  最近修改   :
  功能描述   : Test_AtOutputProc.cpp 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年5月17日
    作    者   : l60609
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TEST_ATOUTPUTPROC_H__
#define __TEST_ATOUTPUTPROC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "ATCmdProc.h"
#include "AtCheckFunc.h"
#include "AtParseCmd.h"
#include "AtInputProc.h"
#include "AtTafAgentInterface.h"

#include "AtDataProc.h"
#include "cpm.h"


#define    THIS_FILE_ID        PS_FILE_ID_AT_OUTPUTPROC_C



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

extern VOS_VOID At_BufferorSendResultData(
           VOS_UINT8                           ucIndex,
           VOS_UINT8                          *pucData,
           VOS_UINT16                          usLength
       );
extern VOS_UINT32 AT_CstDlDataInd(
           VOS_UINT8                          *pucDlData,
           VOS_UINT16                          usDataLen
       );
extern VOS_VOID  AT_DisplayResultData (
           VOS_UINT8                           ucIndex,
           VOS_UINT16                          usLen
       );
extern VOS_VOID AT_DisplaySelResultData(
           VOS_UINT16                          usLen,
           VOS_UINT8                           ucIndex
       );
extern VOS_VOID At_FormatResultData(
           VOS_UINT8                           ucIndex,
           VOS_UINT32                          ulReturnCode);
extern VOS_UINT32 AT_GetDlRateDisplayIndex(
           VOS_UINT8                           ucWasCategory
       );
extern VOS_UINT32 AT_GetNdisStub(VOS_VOID);
extern VOS_UINT32 AT_GetR7DlRateDisplayIndex(
           VOS_UINT8                           ucWasCategory
       );
extern VOS_UINT32 AT_GetR8DlRateDisplayIndex(
           VOS_UINT8                           ucWasCategory
       );
extern VOS_UINT32 AT_GetR9DlRateDisplayIndex(
           VOS_UINT8                           ucWasCategory
       );
extern VOS_UINT32 AT_GetRateDisplayIndexForGsm(
	       TAF_AGENT_SYS_MODE_STRU            *pstSysMode
       );
extern VOS_UINT32 AT_GetRateDisplayIndexForWcdma(
           AT_DOWNLINK_RATE_CATEGORY_STRU     *pstDlRateCategory
       );
extern VOS_UINT32 AT_GetReturnCodeId(
           VOS_UINT32                          ulReturnCode,
           VOS_UINT32                         *pulIndex
       );
extern TAF_UINT32  At_JudgeCombineCmdSubSequentProcess(TAF_UINT8 ucIndex, TAF_UINT32 ReturnCode);
extern TAF_UINT32 At_SendData(TAF_UINT8 ucIndex,TAF_UINT8 ucType,TAF_UINT8* pData,TAF_UINT16 usLen);
extern VOS_VOID At_SendResultData(
           VOS_UINT8                           ucIndex,
           VOS_UINT8                          *pData,
           VOS_UINT16                          usLen
       );
extern VOS_UINT32 AT_SetNdisStub(VOS_UINT32 ulNidsStub);
extern TAF_VOID At_SndResult_Stub(TAF_UINT8 ucIndex, TAF_UINT8* pData, TAF_UINT16 usLen);

extern VOS_UINT32  At_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase);
extern VOS_VOID AT_InitPort(VOS_VOID);

extern VOS_UINT32 APP_VCOM_Send (VOS_UINT8 ucDevIndex, VOS_UINT8 *pData, VOS_UINT32 uslength);
extern VOS_VOID AT_SendBroadCastResultData(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pData,
    VOS_UINT16                          usLen
);
extern VOS_VOID At_TimeOutProc(REL_TIMER_MSG *pMsg);

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

#endif /* end of Test_AtOutputProc.h */
