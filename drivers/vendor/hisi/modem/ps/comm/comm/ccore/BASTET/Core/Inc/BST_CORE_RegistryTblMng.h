/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_CORE_RegistryTblMng.h
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年4月16日
  最近修改   :
  功能描述   : 注册表输入数据检查表的处理头文件
  函数列表   :

  修改历史   :
  1.日    期   : 2014年04月16日
    作    者   : d00173029
    修改内容   : 创建文件

******************************************************************************/
#ifndef __BST_CORE_REGISTRYTBLMNG_H__
#define __BST_CORE_REGISTRYTBLMNG_H__
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_CORE_RegistryDefine.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_CORE_OPENSSL_ERR            ( 0 )
#define BST_CORE_OPENSSL_SUCCESS        ( 1 )
#define BST_CORE_PID_LEN                ( 2 )
#define BST_CORE_NO_PID_CHECK           ( BST_NULL_PTR )
#define BST_CORE_IsPidValid(enParamId)  ( ( ( enParamId ) > BST_PID_INVALID ) \
                                        &&( ( enParamId ) < BST_PID_DEF_BUTT ) )

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
enum BST_CORE_PID_LEN_ENUM
{
    BST_CORE_PID_VAR_LEN                = 0,
    BST_CORE_PID_FIX_LEN
};
typedef BST_UINT8                       BST_CORE_PID_LEN_ENUM_UINT8;

/*****************************************************************************
  4 类型/结构体定义
*****************************************************************************/
typedef BST_UINT16 BST_CORE_PID_LEN_T;

typedef BST_BOOL( *BST_CORE_PID_CHKFUN_T )( const BST_VOID *const   pvContent,
                                            BST_UINT16              usLen );

typedef struct
{
    BST_CORE_PID_ENUM_UINT16            enPid;
    BST_CORE_PID_LEN_T                  usLen;
    BST_VOID                           *pvContent;
} BST_CORE_PID_STRU;

typedef struct
{
    BST_CORE_PID_ENUM_UINT16            enPid;
    BST_CORE_PID_LEN_ENUM_UINT8         enLenType;
    BST_CORE_PID_LEN_T                  usPlen;
} BST_CORE_PID_LUT_STRU;

/*****************************************************************************
  8 函数声明
*****************************************************************************/
BST_CORE_PID_LUT_STRU  *BST_CORE_GetPidHandle   ( BST_CORE_PID_ENUM_UINT16 enParamId );
#ifdef   BST_SSL_SUPPORT
BST_ERR_ENUM_UINT8      BST_CORE_EncryptChk     ( BST_CORE_PID_ENUM_UINT16  enPid,
                                                  const BST_VOID           *pvData,
                                                  BST_UINT16                usLen,
                                                  BST_VOID                **ppOutData,
                                                  BST_UINT16               *pusOutLen );
BST_ERR_ENUM_UINT8      BST_CORE_DencryptChk    ( BST_CORE_PID_ENUM_UINT16  enPid,
                                                  const BST_VOID           *pvData,
                                                  BST_UINT16                usLen,
                                                  BST_VOID                **ppOutData,
                                                  BST_UINT16               *pusOutLen );
#endif

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif


#endif
