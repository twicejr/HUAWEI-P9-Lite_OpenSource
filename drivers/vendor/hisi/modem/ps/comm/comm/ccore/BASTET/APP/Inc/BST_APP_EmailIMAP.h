/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_APP_EmailIMAP.h
  版 本 号   : 初稿
  作    者   : z00220931
  生成日期   : 2014年5月10日
  最近修改   :
  功能描述   : BST_APP_CEmailIMAP的声明
  函数列表   :
  修改历史   :
  1.日    期   : 2014年5月10日
    作    者   : z00220931
    修改内容   : 创建文件

******************************************************************************/
#ifndef __BST_APP_IMAPMBXRAWPROC_H__
#define __BST_APP_IMAPMBXRAWPROC_H__
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_APP_EmailBaseProc.h"
#include "BST_APP_EmailPublic.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*默认的ID命令*/
#define BST_DEFAULT_IMAP_ID_CMD "ID (\"name\" \"com.android.email\" \"os\" \"android\")\r\n"
#define BST_APP_CR                      0x0d//回车符
#define BST_APP_UPDATE_IMAP_TAG(tag) \
    do {\
        if ( BST_IMAP_MAX_TAG == (tag) ){\
            (tag)                       = 0;\
        }(tag)++;\
     } while (0)

#define BST_APP_IMAP_CHECK(n)\
    if ( (n) >= BST_IMAP_COLUMN_MAX ){\
        return BST_ERR_PAR_OVERRUN;\
    }

/*****************************************************************************
  3 类/结构定义
*****************************************************************************/
class BST_APP_CEmailIMAP : BST_PUBLIC BST_APP_CEmailPacketProc
{
BST_PUBLIC:
                        BST_APP_CEmailIMAP( const EMAIL_ACCOUNT_STRU *pstInAccountInfo );
    virtual             ~BST_APP_CEmailIMAP( BST_VOID );

    BST_BOOL            IsConfigOk( BST_VOID );
    BST_UINT8           *ConfigOtherInfo(
        BST_CORE_PID_ENUM_UINT16    enParamId,
        BST_UINT16                  usLen,
        const BST_VOID             *const pData );
BST_PRIVATE:
    BST_BOOL            InitEmailProc( BST_CORE_CNPTask *pTaskProp );
    BST_ERR_ENUM_UINT8  SendID( BST_VOID );
    BST_ERR_ENUM_UINT8  LoginServer( BST_VOID );
    BST_ERR_ENUM_UINT8  SelectInBox( BST_VOID );
    BST_ERR_ENUM_UINT8  QueryServer(
        const BST_UINT8 *chrLastNum,
        BST_UINT16      usLen );
    BST_ERR_ENUM_UINT8  QuitServer( BST_VOID );
    BST_ERR_ENUM_UINT8  RunStateMachine( BST_VOID );
    BST_VOID            ResetMachine( BST_VOID );
    BST_ERR_ENUM_UINT8  ParseResponse(
        BST_UINT8      *pucData,
        BST_UINT16      usLength );
    BST_ERR_ENUM_UINT8  HandleWelcomResp( BST_VOID );
    BST_ERR_ENUM_UINT8  HandleImapIDResp( BST_VOID );
    BST_ERR_ENUM_UINT8  HandleAuthResp( BST_VOID );
    BST_ERR_ENUM_UINT8  HandleSelectResp( BST_VOID );
    BST_ERR_ENUM_UINT8  HandleQueryResp( BST_VOID );
    BST_ERR_ENUM_UINT8  HandleQuitResp( BST_VOID );
    BST_ERR_ENUM_UINT8  FirstTrsProc( BST_VOID );
    BST_UINT8          *SetEmailUID(
        const BST_UINT8 *pucUid,
        BST_UINT16      usLen );

    BST_UINT8          *SetImapIDCmd(
        const BST_UINT8 *pucImapIDCmd,
        BST_UINT16       usLen );
    BST_UINT16          MakeImapID( BST_VOID );
    BST_UINT16          m_usTag;
    BST_UINT8          *m_pcServerResponse0;
    BST_UINT8          *m_pcServerResponse1;
    BST_UINT8          *m_pcServerResponse2;
    BST_LIB_StrStru    *m_pstrImapIDCmd;    /*用来存储ID命令字符串*/
};
/*****************************************************************************
  4 OTHERS定义
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#endif
