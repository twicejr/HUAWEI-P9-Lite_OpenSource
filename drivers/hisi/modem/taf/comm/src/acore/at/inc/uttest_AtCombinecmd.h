/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : uutest_AtCombinecmd.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年5月17日
  最近修改   :
  功能描述   : uttest_AtCombinecmd.cpp 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年5月17日
    作    者   : l60609
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TEST_ATCOMBINECMD_H__
#define __TEST_ATCOMBINECMD_H__

/*****************************************************************************
  1 其他头文件包含                            
*****************************************************************************/
#include "AtCheckFunc.h"

#include "ATCmdProc.h"

#include "TafTypeDef.h"
#include "hi_list.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义 
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_AT_COMBINEDCMD_C
#define PRIVATE
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

extern PRIVATE VOS_UINT32 At_BasicCombineCmdParse(HI_LIST_S* pstCombList, VOS_UINT8 *pDataIn, VOS_UINT16 usLenIn);
extern VOS_UINT32 At_BasicExCombineCmdParse(HI_LIST_S* pstCombList, VOS_UINT8 *pDataIn, VOS_UINT16 usLenIn, VOS_UINT16 usFirIndex);
extern VOS_BOOL At_CombCmdisFinal(VOS_UINT8 ucIndex);
extern VOS_VOID At_CombCmdProcAfterCmd(VOS_UINT8 ucClientId);
extern VOS_UINT32 At_CombineCmdChkProc(VOS_UINT8 ucClientId, IN VOS_UINT8 *pDataIn, VOS_UINT16 usLenIn);
extern PRIVATE VOS_UINT32 At_CombineCmdPreProc(HI_LIST_S* pstCombList, VOS_UINT8 *pDataIn, VOS_UINT16 usLenIn);
extern VOS_UINT32 At_CombineCmdProc(VOS_UINT8 ucClientId);
extern VOS_UINT32 At_GetFirstCmdLen(IN VOS_UINT8 *pData, VOS_UINT16 usLen);
extern VOS_UINT32 At_GetSecondAddr(VOS_UINT8 *pData,VOS_UINT16 usLen, VOS_UINT8** ppDataOut);
extern VOS_VOID At_PrintCombinCmd(VOS_VOID);
extern VOS_VOID At_ResetCombinCmdInfo(HI_LIST_S* pstCombList);
extern VOS_VOID At_ResetCombinParseInfo(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_SemicolonCmdParse(HI_LIST_S* pstCombList, VOS_UINT8 *pDataIn, VOS_UINT16 usLenIn);
extern PRIVATE VOS_UINT32 At_StoreSubCombCmd(HI_LIST_S* pstCombList, VOS_UINT8 *pDataIn, VOS_UINT16 usLenIn);
extern PRIVATE VOS_VOID At_UpStringCmdName(VOS_UINT8 *pData, VOS_UINT16 usLen);

extern VOS_VOID At_FilterDCmdSpecCharacter(
    VOS_UINT32                  *pulParaLen,
    VOS_UINT8                   *pucPara
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

#endif /* end of Test_AtCombinecmd.h */
