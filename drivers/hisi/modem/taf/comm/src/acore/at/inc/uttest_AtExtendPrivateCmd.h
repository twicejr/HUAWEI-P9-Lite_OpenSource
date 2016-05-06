/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : uttest_AtExtendPrivateCmd.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2012年5月17日
  最近修改   :
  功能描述   : uttest_AtExtendPrivateCmd.cpp 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年5月17日
    作    者   : l60609
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TEST_ATEXTENDPRIVATECMD_H__
#define __TEST_ATEXTENDPRIVATECMD_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "AtParse.h"
#include "ATCmdProc.h"
//#include "Taf_Tafm_Remote.h"
#include "AtInputProc.h"

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

extern VOS_UINT32 AT_GetPortInfoIndex(VOS_UINT8   ucPortType, VOS_UINT8 *pucIndex);
extern VOS_UINT32 AT_QryDloadVerPara( VOS_UINT8 ucIndex );
extern VOS_UINT32 At_RegisterExPrivateCmdTable(VOS_VOID);
extern VOS_UINT32  AT_SetDissdCmd(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetSdrebootCmd(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestApRptPortSelectPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestChdataPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_TestCmlckPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestCpnnPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestGpioPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestImsichgPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestIpv6capPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestOplPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestPnnPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestRsfrPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestRsfwPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestRstriggerPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestSetPort(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestStgiPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestStgrPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestStsfPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestSyscfg(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestSyscfgEx(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestUsbSwitchPara(VOS_UINT8 ucIndex);
extern VOS_VOID  AT_InitPort(VOS_VOID);
extern VOS_VOID Test_AT_InitMuxClientTab(VOS_VOID);

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

#endif /* end of Test_AtExtendPrivateCmd.h */
