

#ifndef __SCCTX_H__
#define __SCCTX_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "ScCommCtx.h"
#include "ScComm.h"
#include "ScFactory.h"
#include "ScApSec.h"

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


extern VOS_VOID  SC_CTX_InitFacGlobalVar( VOS_VOID );


extern SC_AUTH_STATUS_ENUM_UINT8  SC_CTX_GetFacAuthStatus( VOS_VOID );


extern VOS_VOID  SC_CTX_SetFacAuthStatus( SC_AUTH_STATUS_ENUM_UINT8 enScAuthStatus );


VOS_UINT8  SC_CTX_GetIdentifyStartFlg( VOS_VOID );


VOS_VOID  SC_CTX_SetIdentifyStartFlg( VOS_UINT8 ucIdentifyStartFlg );


extern VOS_UINT8*  SC_CTX_GetFacRandDataAddr( VOS_VOID );


extern VOS_UINT32*  SC_CTX_GetApSecInitStateAddr(VOS_VOID);


extern SC_APSEC_ITEM_STRU*  SC_CTX_GetApSecItemBaseAddr(VOS_VOID);


extern VOS_UINT8 SC_CTX_GetSecATkeyFlg( VOS_VOID );


extern VOS_VOID SC_CTX_SetSecATkeyFlg( VOS_UINT8 ucSecATkeyFlg );


extern VOS_UINT8* SC_CTX_GetSecATkeyAddr( VOS_VOID );


VOS_UINT8 SC_CTX_GetApSecSeqID(VOS_VOID);


VOS_VOID SC_CTX_SetApSecSeqID(VOS_UINT8 ucSeqID);


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

#endif
