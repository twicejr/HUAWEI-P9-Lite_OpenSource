/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_APP_HttpWbXmlDef.h
  版 本 号   : 初稿
  作    者   : z00220931
  生成日期   : 2014年5月10日
  最近修改   :
  功能描述   : exchange协议中web xml的相关变量定义
  函数列表   :
  修改历史   :
  1.日    期   : 2014年5月10日
    作    者   : z00220931
    修改内容   : 创建文件

******************************************************************************/
#ifndef __BST_APP_HTTPWBXMLDEF_H__
#define __BST_APP_HTTPWBXMLDEF_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_LIB_String.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_WBXML_HEADER               ( 4 )
/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum
{
    INVALID_SYNC_CMD                    = 0,
    PING_CMD,
    SYNC_CMD,
    REQ_CMD_BUTT
}BST_EMAIL_HTTP_REQ_CMD_ENUM;
typedef BST_UINT8                       BST_APP_EXCGREQ_TYPE_ENUM_UINT8;
typedef enum
{
    INVALID_SERVER_STATE                = 0,
    BST_APP_SERVER_NEW_MAIL,
    BST_APP_SERVER_NOT_NEW_MAIL,
    BST_APP_SERVER_UNUSUAL,
    BST_APP_SERVER_EXCRESCENT,          //表明包的剩余部分
    BST_APP_SERVER_PARSE_EXCEPT,        //解析错误
    BST_APP_SERVER_STATE_BUTT
}BST_EMAIL_SERVER_STATE_ENUM;
typedef BST_UINT8                       BST_EMAIL_SERVER_STATE_ENUM_UINT8;

enum
{
    BST_APP_EXCH_IN_EMAIL               = 0,
    BST_APP_EXCH_OUT_EMAIL,
    BST_APP_EXCH_CONTACT,
    BST_APP_EXCH_CALENDAR,
    BST_APP_EXCH_PING,
    BST_APP_EXCH_BUTT
};
/*****************************************************************************
  4 类/结构定义
*****************************************************************************/
typedef struct wb_xml_info_st
{
    BST_LIB_StrStru    *pstClcId;
    BST_LIB_StrStru    *pstSyncKey;
}BST_WB_XML_INFO_STRU;

typedef struct http_req_head_st
{
    BST_LIB_StrStru    *pstPrtcVer;
    BST_LIB_StrStru    *pstUsrAgent;
    BST_LIB_StrStru    *pstEncoding;
    BST_LIB_StrStru    *pstPolicyKey;
    BST_LIB_StrStru    *pstHostName;
}BST_EMAIL_HTTP_REQ_HEAD_STRU;

typedef struct wbxml_body_st
{
    BST_WB_XML_INFO_STRU    stEmlInWxmInfo;
    BST_WB_XML_INFO_STRU    stEmlOutWxmInfo;
    BST_WB_XML_INFO_STRU    stConWxmInfo;
    BST_WB_XML_INFO_STRU    stCalWxmInfo;
    BST_LIB_StrStru        *psWinSize;
}BST_EMAIL_WBXML_BODY_STRU;

/*****************************************************************************
  5 全局变量声明
*****************************************************************************/
/*wbxml*/
const  BST_CHAR BST_EMAIL_SWITCH_PAGE             = 0x00;
const  BST_CHAR BST_EMAIL_END                     = 0x01;
const  BST_CHAR BST_EMAIL_ENTITY                  = 0x02;
const  BST_CHAR BST_EMAIL_SIR_I                   = 0x03;
const  BST_CHAR BST_EMAIL_WITH_CONTENT            = 0x40;
/*base*/
const  BST_CHAR BST_EMAIL_SYNC                    = 0x00;
const  BST_CHAR BST_EMAIL_FOLDER                  = 0x07;
const  BST_CHAR BST_EMAIL_PING                    = 0x0D;
const  BST_CHAR BST_EMAIL_BASE                    = 0x11;

const  BST_CHAR BST_EMAIL_BASE_BODY_PREFERENCE    = 0x05;
const  BST_CHAR BST_EMAIL_BASE_TYPE               = 0x06;
const  BST_CHAR BST_EMAIL_BASE_TRUNCATION_SIZE    = 0x07;
/*Sync*/
const  BST_CHAR BST_EMAIL_SYNC_SYNC               = 0x05;
const  BST_CHAR BST_EMAIL_SYNC_SYNC_KEY           = 0x0B;
const  BST_CHAR BST_EMAIL_SYNC_STATUS             = 0x0E;
const  BST_CHAR BST_EMAIL_SYNC_COLLECTION         = 0x0F;
const  BST_CHAR BST_EMAIL_SYNC_COLLECTION_ID      = 0x12;
const  BST_CHAR BST_EMAIL_SYNC_GET_CHANGES        = 0x13;
const  BST_CHAR BST_EMAIL_SYNC_WINDOW_SIZE        = 0x15;
const  BST_CHAR BST_EMAIL_SYNC_COMMANDS           = 0x16;
const  BST_CHAR BST_EMAIL_SYNC_OPTIONS            = 0x17;
const  BST_CHAR BST_EMAIL_SYNC_FILTER_TYPE        = 0x18;
const  BST_CHAR BST_EMAIL_SYNC_COLLECTIONS        = 0x1C;
const  BST_CHAR BST_EMAIL_SYNC_DELETES_AS_MOVES   = 0x1E;
/*Ping*/
const  BST_CHAR BST_EMAIL_PING_PING               = 0x05;
const  BST_CHAR BST_EMAIL_PING_AUTD_STATE         = 0x06;
const  BST_CHAR BST_EMAIL_PING_STATUS             = 0x07;
const  BST_CHAR BST_EMAIL_PING_HEARTBEAT_INTERVAL = 0x08;
const  BST_CHAR BST_EMAIL_PING_FOLDERS            = 0x09;
const  BST_CHAR BST_EMAIL_PING_FOLDER             = 0x0A;
const  BST_CHAR BST_EMAIL_PING_ID                 = 0x0B;
const  BST_CHAR BST_EMAIL_PING_CLASS              = 0x0C;
const  BST_CHAR BST_EMAIL_PING_MAX_FOLDERS        = 0x0D;

/*new mail flag*/
#define  BST_EMAIL_EAS_NEW_MAIL_LEN              0x60

#define  BST_EMAIL_EAS_DEVICE_TYPE               "Android"
#define  BST_EMAIL_HTTP_VERSION                  "HTTP/1.1"
#define  BST_EMAIL_HTTP_CRLF                     "\r\n"
#define  BST_EMAIL_HTTP_STATUS_LINE              "200 OK\r\n"
#define  BST_EMAIL_HTTP_CODE_CONTENT             "Content-Length:" //使用Content-Length头信息,RFC1945
#define  BST_EMAIL_HTTP_CODE_CHUNKED             "Transfer-Encoding: chunked"//Transfer-Encoding: chunked的头信息,RFC2616
#define  BST_EMAIL_HTTP_CONTENT_ENCODING         "Content-Encoding: gzip" //使用gzip压缩数据
#define  BST_EMAIL_HTTP_HEAD_END                 "\r\n\r\n"
/*****************************************************************************
  6 OTHERS定义
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#endif
