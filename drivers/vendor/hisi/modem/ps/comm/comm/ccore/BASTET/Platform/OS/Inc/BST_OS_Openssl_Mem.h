
#ifndef _BST_OS_OPENSSL_MEM_H_
#define _BST_OS_OPENSSL_MEM_H_

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_Typedefine.h"
/*****************************************************************************
  2 函数声明
*****************************************************************************/
BST_VOID *BST_OPENSSL_Malloc( BST_UINT32 ulSize );
BST_VOID BST_OPENSSL_Free( BST_VOID *pData );
BST_VOID *BST_OPENSSL_Realloc( BST_VOID *pMemAddress, BST_UINT32 ulNewSize );

#endif