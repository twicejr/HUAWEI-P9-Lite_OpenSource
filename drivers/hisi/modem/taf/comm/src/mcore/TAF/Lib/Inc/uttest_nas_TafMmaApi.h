/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafStdlib.h
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2013年5月25日
  最近修改   :
  功能描述   : TafStdlib.c的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年5月25日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
#ifndef _UTTEST_TAF_STD_LIB_H_
#define _UTTEST_TAF_STD_LIB_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafAppMma.h"
#include "Taf_Tafm_Remote.h"
#include "ATCmdProc.h"
#include "PsCommonDef.h"
#include "NVIM_Interface.h"
#include "TafClientApi.h"
#include "MnCommApi.h"
#include "AtParse.h"
#include "PsCommonDef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define    THIS_FILE_ID                 PS_FILE_ID_TAF_MMA_API_C

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

extern void * UT_V_MemCpy( void * Dest, const void * Src, unsigned int Count,
                       unsigned int ulFileID, int usLineNo );

extern void * UT_V_MemSet( void * ToSet, char Char, unsigned int Count,
                     unsigned int ulFileID, int usLineNo );

extern void * UT_V_MemMove( void * Dest, const void * Src, unsigned int Count,
                        unsigned int ulFileID, int usLineNo );

extern MsgBlock * UT_V_AllocMsg( unsigned int Pid, unsigned int ulLength,
                       unsigned int ulFileID, int usLineNo );


extern unsigned int UT_V_FreeMsg( unsigned int Pid, void **ppMsg,
                            unsigned int ulFileID, int usLineNo );

extern void * UT_V_MemAlloc( unsigned int ulInfo, unsigned char  ucPtNo, unsigned int ulSize,
                        unsigned int ulFileID, int usLineNo  );

extern unsigned int UT_V_MemFree( unsigned int ulInfo, void **ppAddr,
                          unsigned int ulFileID, int usLineNo );

extern char * UT_VOS_StrCpy( char *Dest, char *Src );

extern unsigned int UT_VOS_StrLen( char * Str );

extern char* UT_VOS_StrRChr( char * Str, char Char );

extern int UT_VOS_MemCmp( const void * Dest, const void * Src, unsigned int Count );

extern char * UT_VOS_StrStr( char * Str1, char * Str2 );

extern char * UT_VOS_StrNCpy( char *Dest, char *Src, unsigned int Count );

extern int UT_VOS_StrCmp( char *Str1, char *Str2 );

extern void * UT_VOS_MemChr( const void *buf, unsigned char c, int n );


extern unsigned int UT_Ps_SendMsg(signed char *cFileName, unsigned int ulLine, unsigned int ulPid, void * pMsg);


extern unsigned int UT_VOS_CharIsUpper( char Char );

extern char UT_VOS_CharToLower( char Char );

extern signed char UT_VOS_StrNiCmp( char * Str1, char * Str2, unsigned int Length );

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


#endif /* end of uttest_TafSpmCtx.h */


