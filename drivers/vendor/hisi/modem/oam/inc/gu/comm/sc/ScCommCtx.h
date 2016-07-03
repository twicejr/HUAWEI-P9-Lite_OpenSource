



#ifndef __SCCOMMCTX_H__
#define __SCCOMMCTX_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "ScComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define     SC_RAND_DATA_LEN            (4)         /* 随机数的字节数 */

#define     SC_SEC_AT_KEY_LEN           (16)                /* 安全AT key的长度 */

#define     SC_SECURITY_ITEM_NUM        (16)                /* 安全存储项个数 */


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum SC_AUTH_STATUS_ENUM
{
    SC_AUTH_STATUS_UNDO          = 0x00,             /* 未进行鉴权 */
    SC_AUTH_STATUS_DONE          = 0x01,             /* 已经鉴权 */
    SC_AUTH_STATUS_BUTT
};
typedef VOS_UINT8 SC_AUTH_STATUS_ENUM_UINT8;


enum SC_APSEC_FILE_STATE_INIT_ENUM
{
    SC_SECURITY_FILE_STATE_INIT         =   0x5A5A5A5A,     /* 安全存储文件初始化完成 */
    SC_SECURITY_FILE_STATE_IDEL         =   0x5A5A55AA,     /* 安全存储文件初始化未完成 */
    SC_SECURITY_FILE_STATE_BUTT,
};
typedef VOS_UINT32 SC_APSEC_FILE_STATE_INIT_ENUM_UINT32;

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

typedef struct
{
    VOS_CHAR                           *acSecretFileName[SC_SECRET_FILE_TYPE_BUTT];
    VOS_CHAR                           *acSignFileName[SC_SECRET_FILE_TYPE_BUTT];
}SC_COMM_GLOBAL_STRU;


typedef struct
{
    SC_AUTH_STATUS_ENUM_UINT8               enScFacAuthStatus;
    VOS_UINT8                               aucScFacRandData[SC_RAND_DATA_LEN];
    /* 发起产线鉴权标志 VOS_FALSE: 未发起产线鉴权; VOS_TRUE: 已发起产线鉴权 */
    VOS_UINT8                               ucIdentifyStartFlg;
    VOS_UINT8                               aucReserved[2];         /* 保留字节，用于四字节对齐 */
}SC_FAC_GLOBAL_STRU;


typedef struct
{
    VOS_UINT32                          ulItemLen;
    VOS_CHAR                           *pucContent;
    VOS_UINT8                           aucHash[SC_HASH_LEN];
}SC_APSEC_ITEM_STRU;


typedef struct
{
    VOS_UINT8                                               ucSeqID;
    VOS_UINT8                                               aucReserved[2];
    VOS_UINT8                                               ucSecATkeyFlg;
    VOS_UINT8                                               aucSecATkey[SC_SEC_AT_KEY_LEN];
    SC_APSEC_FILE_STATE_INIT_ENUM_UINT32                    ulInitState;
    SC_APSEC_ITEM_STRU                                      astApSecItem[SC_SECURITY_ITEM_NUM];
    VOS_CHAR                                               *pApSecFileA;
    VOS_CHAR                                               *pApSecFileC;
}SC_APSEC_GLOBAL_STRU;


typedef struct
{
    SC_COMM_GLOBAL_STRU                 stScCommGlobalVar;
    SC_FAC_GLOBAL_STRU                  stScFacGlobalVar;
    SC_APSEC_GLOBAL_STRU                stScApSecGlobalVar;
}SC_CONTEXT_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/


extern SC_COMM_GLOBAL_STRU*  SC_CTX_GetCommGlobalVarAddr( VOS_VOID );


extern SC_CONTEXT_STRU* SC_CTX_GetScCtxAddr(VOS_VOID);

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
