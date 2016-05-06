/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_APP_EmailPublic.h
  版 本 号   : 初稿
  作    者   : z00220931
  生成日期   : 2014年5月10日
  最近修改   :
  功能描述   : Email的相关数据结构
  函数列表   :
  修改历史   :
  1.日    期   : 2014年5月10日
    作    者   : z00220931
    修改内容   : 创建文件

******************************************************************************/
#ifndef __BST_APP_EMAILPUBLIC_H__
#define __BST_APP_EMAILPUBLIC_H__
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_LIB_String.h"
#include "BST_Platform.h"
#include "BST_APP_Define.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_EMAIL_MAX_UID_LEN           ( 32U )

/*POP3*/
#define BST_POP3_COLUMN_MAX             ( BST_EMAIL_MAX_UID_LEN )

#define BST_POP3_USER_NAME_MAX_LEN      ( 64 )
#define BST_POP3_PASS_WORD_MAX_LEN      ( 64 )
/*IMAP*/
#define BST_IMAP_START_TAG              ( 0x0001 )
#define BST_IMAP_MAX_TAG                ( 0xFFFF )
#define BST_IMAP_COLUMN_MAX             ( BST_EMAIL_MAX_UID_LEN )
#define BST_IMAP_AUTH_CMD_MAX_LEN       ( 128 )
/*ID命令的最大长度*/
#define BST_IMAP_ID_CMD_MAX_LEN         ( 256 )
/* other*/
#define BST_OTHER_CMD_MAX_LEN           ( 32 )
#define BST_EXCG_URL_NAME_LEN           ( 64 )
#define BST_SEND_BUF_SIZE               ( 2024 )

#define BST_EMAIL_MULINFO_LEN_FLAG      ( 2 )
#define BST_EMAIL_L                     ( 0 )
#define BST_EMAIL_H                     ( 1 )
/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum
{
    MBX_TYPE_INVALID                    = 0,
    MBX_TYPE_POP3,
    MBX_TYPE_IMAP,
    MBX_TYPE_EXCG,
    MBX_TYPE_BUTT
} MAIL_BOX_TYPE_ENUM;
typedef BST_UINT32                      MAIL_BOX_TYPE_ENUM_UINT32;

typedef enum
{
    SYNC_INVALID = 0,
    SYNC_PUSH,
    SYNC_INTERVAL,
    SYNC_TYPE_BUTT
} SYNC_TYPE_ENUM; 
typedef BST_UINT32                       SYNC_TYPE_ENUM_UINT32;

typedef enum
{
    PROTO_VER = 0,
    USERAGENT,
    ENCODING,
    POLICYKEY,
    HOSTNAME
}EMAIL_HEAD_ENUM;
typedef BST_UINT8                       EMAIL_HEAD_ENUM_UINT8;

/*****************************************************************************
  4 类/结构定义
*****************************************************************************/
typedef struct
{
    BST_LIB_StrStru                    *pMailBoxFolder;
    BST_LIB_StrStru                    *pLastUid;
}BST_EMAIL_UID_INFO_STRU;

typedef struct
{
    BST_LIB_StrStru                    *pUserName;
    BST_LIB_StrStru                    *pPassWord;
    BST_LIB_StrStru                    *pCipherKey;
    BST_APP_ENCRP_MODE_ENUM_UINT32      enEcryptionType;
    MAIL_BOX_TYPE_ENUM_UINT32           enMbxType;
    SYNC_TYPE_ENUM_UINT32               enSyncType;
} EMAIL_ACCOUNT_STRU;
/*****************************************************************************
  5 OTHERS定义
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#endif
