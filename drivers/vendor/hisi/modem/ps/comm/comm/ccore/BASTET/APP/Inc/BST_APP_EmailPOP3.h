
#ifndef __BST_APP_POP3MBXRAWPROC_H__
#define __BST_APP_POP3MBXRAWPROC_H__
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
#define BST_APP_POP3_CHECK(n)\
    if ( (n) >= BST_POP3_COLUMN_MAX ){\
        return BST_ERR_PAR_OVERRUN;\
    }
/*****************************************************************************
  3 类/结构定义
*****************************************************************************/
class BST_APP_CEmailPOP3 : BST_PUBLIC BST_APP_CEmailPacketProc
{
BST_PUBLIC:
    BST_APP_CEmailPOP3( const EMAIL_ACCOUNT_STRU *penInAccountInfo );
    virtual ~BST_APP_CEmailPOP3( BST_VOID );
    
    BST_BOOL            IsConfigOk( BST_VOID );
    BST_UINT8 *ConfigOtherInfo ( 
        BST_CORE_PID_ENUM_UINT16 enParamId,
        BST_UINT16               usLen,
        const BST_VOID          *const pData );
BST_PRIVATE:
    BST_ERR_ENUM_UINT8  LoginServer     ( BST_VOID );
    BST_ERR_ENUM_UINT8  LoginAuth       ( BST_VOID );
    BST_ERR_ENUM_UINT8  QueryNumOfEmail( BST_VOID );
    BST_ERR_ENUM_UINT8  QueryUidOfLast( 
        const BST_UINT8 *chrLastSeq, BST_UINT16 usLen );
    BST_ERR_ENUM_UINT8  QuitServer( BST_VOID );
    BST_ERR_ENUM_UINT8  ParseResponse( BST_UINT8 *pucData, BST_UINT16 usLength );
    BST_ERR_ENUM_UINT8  HandleWelcomResp( BST_VOID );
    BST_ERR_ENUM_UINT8  HandleUserResp( BST_VOID );
    BST_ERR_ENUM_UINT8  HandlePassResp( BST_VOID );
    BST_ERR_ENUM_UINT8  HandleNumResp ( BST_VOID );
    BST_ERR_ENUM_UINT8  HandleQueryResp( BST_VOID );
    BST_ERR_ENUM_UINT8  RunStateMachine( BST_VOID );
    BST_VOID            ResetMachine( BST_VOID );
    BST_ERR_ENUM_UINT8  FirstTrsProc    ( BST_VOID );
    BST_UINT8          *SetEmailUID( const BST_UINT8 *pucUid, BST_UINT16 usLen );
    BST_APP_CEmailPOP3( const BST_APP_CEmailPOP3& EmailPop3 );
    BST_APP_CEmailPOP3& operator = ( const BST_APP_CEmailPOP3& EmailPop3 );
    BST_UINT8          *m_pcServerResponse0;
    BST_UINT8          *m_pcServerResponse1;
    BST_UINT8          *m_pcServerResponse2;
};
/*****************************************************************************
  3 OTHERS定义
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#endif
