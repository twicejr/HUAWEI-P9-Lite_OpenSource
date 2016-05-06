/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Test_AtCmdProc.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2012年5月17日
  最近修改   :
  功能描述   : Test_AtCmdProc.cpp 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年5月17日
    作    者   : l60609
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TEST_ATCMDPROC_H__
#define __TEST_ATCMDPROC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include "ATCmdProc.h"
#include "AtCheckFunc.h"
#include "PppInterface.h"

#include "UsimPsInterface.h"
#include "Taf_MmiStrParse.h"
#include "AppVcApi.h"
#include "AtDataProc.h"
#include "MnMsgApi.h"
#include "AtCmdMsgProc.h"
#include "AtInputProc.h"
#include "AtTestParaCmd.h"

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
extern VOS_UINT32  At_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase);
extern TAF_VOID At_MsgProc(MsgBlock* pMsg);

extern VOS_UINT32 LimitedCmdProc(VOS_UINT8 ucClientId, VOS_UINT8 *pData, VOS_UINT16 usLen, AT_PAR_CMD_ELEMENT_STRU* pstCmdElement);

extern VOS_VOID At_InterTimerOutProc(
    VOS_UINT8 ucIndex
);
extern TAF_UINT32  At_SendPduMsgAck(
    TAF_UINT8                           ucIndex,
    TAF_UINT8                           *pData,
    TAF_UINT32                          ulLen
);

extern TAF_UINT32 At_SmsTextProc ( TAF_UINT8 ucIndex, TAF_UINT8 *pData, TAF_UINT16 usLen);
extern TAF_UINT32 At_SmsPduProc ( TAF_UINT8 ucIndex, TAF_UINT8 *pData, TAF_UINT16 usLen);

extern VOS_VOID  AT_InitPort(VOS_VOID);
extern VOID Test_AT_InitMuxClientTab(VOS_VOID);

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

#endif /* end of Test_AtCmdProc.h */
