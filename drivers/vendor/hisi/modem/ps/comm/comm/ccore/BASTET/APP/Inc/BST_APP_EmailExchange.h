/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_APP_EmailExchange.h
  版 本 号   : 初稿
  作    者   : z00220931
  生成日期   : 2014年5月10日
  最近修改   :
  功能描述   : BST_APP_CEmailExchange类的声明
  函数列表   :
  修改历史   :
  1.日    期   : 2014年5月10日
    作    者   : z00220931
    修改内容   : 创建文件

******************************************************************************/
#ifndef __BST_APP_EXCGMBXRAWPROC_H__
#define __BST_APP_EXCGMBXRAWPROC_H__
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_APP_EmailBaseProc.h"
#include "BST_APP_ExcgHttp.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif
/*****************************************************************************
  2 宏定义
*****************************************************************************/

#if( BST_VER_TYPE == BST_DBG_VER )
#define BST_APP_SOCKET_NUM_FACTOR       3
#else
#define BST_APP_SOCKET_NUM_FACTOR       1
#endif
#define BST_APP_SOCKET_NUM_MAX          ( 0x01 << BST_APP_SOCKET_NUM_FACTOR )
#define BST_APP_SOCKET_NUM_MASK         ( BST_APP_SOCKET_NUM_MAX - 1 )
#define BST_APP_IS_NUMBERORCHAR(ch)\
        ( ( ( (ch) >= 'A' ) && ( (ch) <= 'Z' ) ) || \
          ( ( (ch) >= 'a' ) && ( (ch) <= 'z' ) ) || \
          ( ( (ch) >= '0' ) && ( (ch) <= '9' ) ) )

#define BST_APP_IS_SPECIALCHAR(ch)\
        ( ( '.' == (ch) ) ||         \
          ( '-' == (ch) ) ||         \
          ( '_' == (ch) ) ||         \
          ( '*' == (ch) ) )

#define BST_APP_BuildHttpHead(pHead)\
    pHead        = ( BST_EMAIL_HTTP_REQ_HEAD_STRU * )\
                                BST_OS_MALLOC((BST_OS_SIZEOF(BST_EMAIL_HTTP_REQ_HEAD_STRU)));\
    if ( BST_NULL_PTR != pHead )\
    {\
        pHead->pstEncoding   = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );\
        pHead->pstHostName   = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );\
        pHead->pstPolicyKey  = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );\
        pHead->pstPrtcVer    = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );\
        pHead->pstUsrAgent   = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );\
    }          

#define BST_APP_BuildWbxmlBody( pWbxmlBody ) \
    pWbxmlBody  = ( BST_EMAIL_WBXML_BODY_STRU * )\
                   BST_OS_MALLOC((BST_OS_SIZEOF(BST_EMAIL_WBXML_BODY_STRU)));\
    if ( BST_NULL_PTR != pWbxmlBody )\
    {\
        pWbxmlBody->stEmlInWxmInfo.pstClcId     = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );\
        pWbxmlBody->stEmlInWxmInfo.pstSyncKey   = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );\
        pWbxmlBody->stEmlOutWxmInfo.pstClcId    = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );\
        pWbxmlBody->stEmlOutWxmInfo.pstSyncKey  = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );\
        pWbxmlBody->stConWxmInfo.pstClcId       = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );\
        pWbxmlBody->stConWxmInfo.pstSyncKey     = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );\
        pWbxmlBody->stCalWxmInfo.pstClcId       = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );\
        pWbxmlBody->stCalWxmInfo.pstSyncKey     = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );\
        pWbxmlBody->psWinSize       = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );\
    }


#define BST_APP_DeleteHttpHead( pHead )\
    if ( BST_NULL_PTR != pHead )\
    {\
        BST_LIB_StrDelete( pHead->pstEncoding );\
        BST_LIB_StrDelete( pHead->pstHostName );\
        BST_LIB_StrDelete( pHead->pstPolicyKey);\
        BST_LIB_StrDelete( pHead->pstPrtcVer  );\
        BST_LIB_StrDelete( pHead->pstUsrAgent );\
        BST_OS_FREE( pHead );\
    }

#define BST_APP_DeleteWbxmlBody( pWbxmlBody ) \
    if ( BST_NULL_PTR != pWbxmlBody )\
    {\
        BST_LIB_StrDelete( pWbxmlBody->stEmlInWxmInfo.pstClcId );   \
        BST_LIB_StrDelete( pWbxmlBody->stEmlInWxmInfo.pstSyncKey);  \
        BST_LIB_StrDelete( pWbxmlBody->stEmlOutWxmInfo.pstClcId );  \
        BST_LIB_StrDelete( pWbxmlBody->stEmlOutWxmInfo.pstSyncKey );\
        BST_LIB_StrDelete( pWbxmlBody->stConWxmInfo.pstClcId );     \
        BST_LIB_StrDelete( pWbxmlBody->stConWxmInfo.pstSyncKey );   \
        BST_LIB_StrDelete( pWbxmlBody->stCalWxmInfo.pstClcId );     \
        BST_LIB_StrDelete( pWbxmlBody->stCalWxmInfo.pstSyncKey );   \
        BST_LIB_StrDelete( pWbxmlBody->psWinSize );                 \
        BST_OS_FREE( pWbxmlBody );                                  \
    }
/*****************************************************************************
  3 类/结构定义
*****************************************************************************/

class BST_APP_CEmailExchange : BST_PUBLIC BST_APP_CEmailPacketProc
{
BST_PUBLIC:
                    BST_APP_CEmailExchange( const EMAIL_ACCOUNT_STRU *pstInAccountInfo );
    virtual         ~BST_APP_CEmailExchange( BST_VOID );
    BST_BOOL        InitEmailProc  ( BST_CORE_CNPTask *pTaskProp );
    BST_BOOL        IsConfigOk     ( BST_VOID );
    BST_VOID        EntryProc      ( BST_VOID );
BST_PRIVATE:
    BST_BOOL        InitRegedit    ( BST_CORE_CNPTask *pTaskProp );
    BST_UINT8       *ConfigOtherInfo(
        BST_CORE_PID_ENUM_UINT16 enParamId,
        BST_UINT16               usLen,
        const BST_VOID          *const pData );
    BST_UINT8       *SetDeviceID(
        const BST_UINT8 *pucDeviceId,
        BST_UINT16       usLen );
    BST_UINT8       *SetExcgInfo(
        const BST_UINT8 *pucExcgInfo,
        BST_UINT16       usLen );
    BST_UINT8       *SetExcgWbxmlInfo(
        const BST_UINT8 *pucExcgWbxmlInfo, 
        BST_UINT16       usInfoLen );
    BST_UINT8       *SetExcgCollectionId(
        const BST_UINT8 *pucExcgCollectionId, 
        BST_UINT16       usLen,
        BST_UINT16       usType );
    BST_UINT8       *SetExcgSyncKey(
        const BST_UINT8 *pucExcgSyncKey,
        BST_UINT16       usLen,
        BST_UINT16       usType );
    BST_VOID        SetOtherSocketType(
        const BST_VOID *const pData,
        BST_UINT16      usLen);
    BST_VOID        FillHttpHead( BST_EMAIL_HTTP_REQ_HEAD_STRU *pstHttpReqHead );
    BST_VOID        FillWbxmlBody( BST_EMAIL_WBXML_BODY_STRU *pstWbxmlBody );
    BST_UINT16      ComposeHttpPack(
        const BST_CHAR * strUserName,
        const BST_CHAR * strUserNameAndPass,
        const BST_CHAR * strDeviceId,
        const BST_EMAIL_HTTP_REQ_HEAD_STRU *pstHttpReqHead,
        const BST_EMAIL_WBXML_BODY_STRU *pstWbxmlBody );
    BST_ERR_ENUM_UINT8  QueryServer( BST_VOID );
    BST_BOOL            BuildRequest( BST_VOID );
    BST_ERR_ENUM_UINT8  RunStateMachine( BST_VOID );

    BST_ERR_ENUM_UINT8  HandleInBox( BST_VOID );
    BST_ERR_ENUM_UINT8  HandleOutBox( BST_VOID );
    BST_ERR_ENUM_UINT8  HandleContacts( BST_VOID );

    BST_ERR_ENUM_UINT8      ParseResponse  (
        BST_UINT8 *pucData,
        BST_UINT16 usLength );
    BST_ERR_ENUM_UINT8  FirstTrsProc   ( BST_VOID );
    BST_ERR_ENUM_UINT8  SendCommand    (
        const BST_UINT8 *pucCmd,
        BST_UINT16      usLength );
    BST_UINT8       *EncodeBase64(
        const BST_UINT8     *pstrIn,
        BST_UINT16          usLength ) const;
    BST_UINT8       *EncodeUrl(
        const BST_UINT8  *str,
        BST_UINT8        *pstrResult,
        const BST_UINT16 usStrSize,
        const BST_UINT16 usResultSize ) const;
    BST_VOID                UpdateSocket   ( BST_VOID );
    BST_BOOL                InitOtherSocket( BST_VOID );
    BST_APP_CExcgHttp      *m_pExcgHttp;
    BST_LIB_StrStru        *m_pDeviceID;
    BST_LIB_StrStru        *m_pExcgHttpInfo;
    BST_WB_XML_INFO_STRU    m_stEmailInBox;
    BST_WB_XML_INFO_STRU    m_stEmailOutBox;
    BST_WB_XML_INFO_STRU    m_stContacts;
    BST_WB_XML_INFO_STRU    m_stCalendar;
    BST_IP_CSocket         *m_SocketArray[BST_APP_SOCKET_NUM_MAX];
    BST_UINT16              m_usSocketCnt;
    BST_BOOL                m_bCfgChgFlag;
};

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
const BST_UINT8 acBase64Table[] =
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/', '\0'
};
/*****************************************************************************
  5 OTHERS定义
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#endif
