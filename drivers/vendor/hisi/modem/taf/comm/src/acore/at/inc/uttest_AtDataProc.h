/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Test_AtDataProc.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2012年5月17日
  最近修改   :
  功能描述   : Test_AtDataProc.cpp 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年5月17日
    作    者   : l60609
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TEST_ATDATAPROC_H__
#define __TEST_ATDATAPROC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "mdrv.h"
#include "product_config.h"
#include "AtTafAgentInterface.h"
#include "TafApsApi.h"
#include "AtInputProc.h"
#include "PppInterface.h"
#include "AtPppInterface.h"
#include "ATCmdProc.h"
#include "AtDataProc.h"
#include "AtInputProc.h"
#include "AtCsdInterface.h"
#include "AtEventReport.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_AT_DATAPROC_C
/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

extern VOS_UINT8               g_ucAtSystemAppConfigAddr;

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
extern VOS_UINT32   At_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase);
extern VOS_VOID     AT_ReadSharePdpInfoNV(VOS_VOID);
extern VOS_VOID AT_InitPort(VOS_VOID);
extern VOS_VOID AT_UsbModemInit(VOS_VOID);
extern VOS_VOID AT_HsicModemInit(VOS_VOID);
extern VOS_VOID AT_SetPcuiPsCallFlag(VOS_UINT8 ucFlag, VOS_UINT16 usClientId);
extern VOS_UINT32 AT_EnableNdisFlowCtl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
    );
extern VOS_UINT32 AT_DisableNdisFlowCtl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
    );

#if( FEATURE_ON == FEATURE_CSD )
extern VOS_UINT32 AT_VpResetFlowCtl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
    );
#endif


extern TAF_PS_EVT_STRU* TEST_Build_ApsAtMsg(
    VOS_UINT32                          ulEvtId,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
    );
extern TAF_VOID At_MsgProc(MsgBlock* pMsg);


extern TAF_PS_EVT_STRU* TEST_Build_ApsAtMsg(
    VOS_UINT32                          ulEvtId,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
    );
extern TAF_VOID At_MsgProc(MsgBlock* pMsg);

extern VOS_VOID AT_InitModemPsCtx(
    MODEM_ID_ENUM_UINT16                enModemId
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

#endif /* end of Test_AtDataProc.h */
