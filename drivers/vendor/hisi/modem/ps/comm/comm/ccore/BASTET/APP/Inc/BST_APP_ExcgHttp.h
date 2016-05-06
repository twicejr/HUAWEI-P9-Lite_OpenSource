/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_APP_ExcgHttp.h
  版 本 号   : 初稿
  作    者   : z00220931
  生成日期   : 2013年10月9日
  最近修改   :
  功能描述   : BST_APP_ExcgHttp类的声明
  函数列表   :
  修改历史   :
  1.日    期   : 2013年10月9日
    作    者   : z00220931
    修改内容   : 创建文件

******************************************************************************/
#ifndef __BST_APP_EXCGHTTP_H__
#define __BST_APP_EXCGHTTP_H__
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_APP_HttpWbXmlDef.h"


#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define EXCG_WEB_XML_LEN                (10)
#define BST_EMAIL_NAME                  "Email"
#define BST_CONTACTS_NAME               "Contacts"
#define BST_CALENDAR_NAME               "Calendar"
#define BST_CREAT_SYNC_REQUEST(type)                                                        \
    do {                                                                                    \
        snprintf( (BST_CHAR *)pcBuf, EXCG_WEB_XML_LEN, "%d", usLen );                       \
        CreateRqstHeader( strUserNameAndPass, (BST_CHAR *)pcBuf, pstHttpReqHead, enCmdType );\
        BST_LIB_StrAddBytes( (type), m_pstrRequest->pData, m_pstrRequest->usUsed );         \
        BST_LIB_StrAddBytes( (type), m_pstrHttpBody->pData, m_pstrHttpBody->usUsed );       \
        BST_LIB_StrAddBytes( (type), m_pstrWbxml->pData, m_pstrWbxml->usUsed );             \
        BST_LIB_StrClear( m_pstrHttpBody );                                                 \
        BST_LIB_StrClear( m_pstrWbxml );                                                    \
    }while(0)
#define BST_CREAT_PING_XML(type,str)                                    \
    do{                                                                 \
        CreateWbxmlTag( BST_EMAIL_PING_FOLDER, BST_FALSE );             \
        CreateWbxmlData( (type).pstClcId->pData, BST_EMAIL_PING_ID );   \
        CreateWbxmlData( (str), BST_EMAIL_PING_CLASS );                 \
        BST_LIB_StrAddByte( m_pstrWbxml,  BST_EMAIL_END );              \
    }while(0)
#define BST_CREAT_SYNC_XML(type)                                                \
    do{                                                                         \
        CreateWbxmlData( (type).pstSyncKey->pData, BST_EMAIL_SYNC_SYNC_KEY );   \
        CreateWbxmlData( (type).pstClcId->pData, BST_EMAIL_SYNC_COLLECTION_ID );\
    }while(0)
/*****************************************************************************
  3 类/结构定义
*****************************************************************************/

class BST_APP_CExcgHttp
{
BST_PUBLIC:
                    BST_APP_CExcgHttp(BST_VOID);
    virtual        ~BST_APP_CExcgHttp(BST_VOID);

    BST_BOOL        ConfigRqst(
        const BST_CHAR                     *strUserName,
        const BST_CHAR                     *strUserNameAndPass,
        const BST_CHAR                     *strDeviceId,
        const BST_EMAIL_HTTP_REQ_HEAD_STRU *pstHttpReqHead,
        const BST_EMAIL_WBXML_BODY_STRU    *pstWbxmlBody,
        const BST_APP_EXCGREQ_TYPE_ENUM_UINT8 enCmdType);

    BST_VOID        CreateRqstLine(
        const BST_CHAR                         *strUserName,
        const BST_CHAR                         *strDeviceId,
        const BST_APP_EXCGREQ_TYPE_ENUM_UINT8   enCmdType );

    BST_VOID        CreateRqstHeader(
        const BST_CHAR                         *strUserNameAndPass,
        const BST_CHAR                         *strBodyLen,
        const BST_EMAIL_HTTP_REQ_HEAD_STRU     *pstHttpReqHead,
        const BST_APP_EXCGREQ_TYPE_ENUM_UINT8   enCmdType);

    BST_UINT16      CreatePingBody(
        const BST_EMAIL_WBXML_BODY_STRU        *pstWbxmlBody );

    BST_UINT16      CreateSyncBody(
        const BST_EMAIL_WBXML_BODY_STRU    *pstWbxmlBody,
        BST_UINT16                          usType );

    BST_EMAIL_SERVER_STATE_ENUM_UINT8   ParseRspns(
        const BST_CHAR         *pcResponse,
        BST_UINT16              Length );

    BST_EMAIL_SERVER_STATE_ENUM_UINT8   ParseSyncRspns(
        const BST_CHAR         *pstRspStr,
        const BST_UINT16        usLen );
    BST_EMAIL_SERVER_STATE_ENUM_UINT8   ParsePingRspns(
        const BST_CHAR         *pstRspStr,
        const BST_UINT16        usLength);
    BST_INT32       ParsePingStatus(
        const BST_CHAR         *pstRspStr,
        const BST_UINT16        usLength);
    BST_INT32       HandleResponse(
        const BST_CHAR         *pstRspStr,
        const BST_UINT16        usLength);
    BST_LIB_StrStru *GetRequest(
        BST_UINT16              usType );

    BST_UINT16      CreatePingWbxml(
        const BST_EMAIL_WBXML_BODY_STRU    *pstWbxmlBody );

    BST_UINT16      CreateSyncWbxml(
        const BST_EMAIL_WBXML_BODY_STRU    *pstWbxmlBody,
        BST_UINT16                          usType );

    BST_UINT16      CreateWbxmlHeader( BST_VOID );

    BST_INT32       HexStrToInt(
        const BST_UINT8        *pHexStr,
        const BST_UINT16        usLen );

BST_PRIVATE:
    BST_VOID        CreateWbxmlTag(
        const BST_CHAR          cTag,
        const BST_BOOL          bNoContent );

    BST_VOID        CreateWbxmlData(
        const BST_CHAR* strData,
        const BST_CHAR  cTag );
    BST_LIB_StrStru            *m_pstrHttpBody;
    BST_LIB_StrStru            *m_pstrRequest;
    BST_LIB_StrStru            *m_pstrReqIn;
    BST_LIB_StrStru            *m_pstrReqOut;
    BST_LIB_StrStru            *m_pstrReqCon;
    BST_LIB_StrStru            *m_pstrReqCal;
    BST_LIB_StrStru            *m_pstrWbxml;
    BST_UINT8                   m_enCmdType;
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