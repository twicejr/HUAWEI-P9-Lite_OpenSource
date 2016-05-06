/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_APP_Define.h
  版 本 号   : 初稿
  作    者   : z00220931
  生成日期   : 2014年5月10日
  最近修改   :
  功能描述   : APP中相关变量和宏的定义
  函数列表   :
  修改历史   :
  1.日    期   : 2014年5月10日
    作    者   : z00220931
    修改内容   : 创建文件

******************************************************************************/
#ifndef __BST_APP_DEFINE_H__
#define __BST_APP_DEFINE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_Typedefine.h"
#include "BST_OS_Timer.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*public state*/
#define BST_EMAIL_UNCONNECT             ( 0x00 )
#define BST_EMAIL_CONNECTED             ( 0x01 )
#define BST_EMAIL_QUITED                ( 0x06 )
#define BST_EMAIL_EXCEPTION             ( 0x08 )
/*pop3 state*/
#define BST_EMAIL_POP3_LOGINED          ( 0x02 )
#define BST_EMAIL_POP3_AUTHED           ( 0x03 )
#define BST_EMAIL_POP3_QUERYNUMED       ( 0x04 )
#define BST_EMAIL_POP3_QUERYUIDED       ( 0x05 )
/*imap state*/
#define BST_EMAIL_IMAP_ID               ( 0x02 )
#define BST_EMAIL_IMAP_LOGINED          ( 0x03 )
#define BST_EMAIL_IMAP_SELECTED         ( 0x04 )
#define BST_EMAIL_IMAP_QUERYED          ( 0x05 )
/*exchange state*/
#define BST_EMAIL_EAS_QUERYED_INBOX     ( 0x02 )
#define BST_EMAIL_EAS_QUERYED_OUTBOX    ( 0x03 )
#define BST_EMAIL_EAS_QUERYED_CON       ( 0x04 )
#define BST_EMAIL_EAS_QUERYED_CAL       ( 0x05 )

#define BST_APP_MAIN_TASK_ID            ( 0x01 )

/*三次连接失败就上报*/
#define BST_CON_FAIL_NUM                ( 3 )
/*20s建链超时*/
#define BST_APP_CONNECT_TIME_OUT        ( 20 * BST_OS_MS_IN_S )
/*接收超时时间必需要大于socket读超时时间*/
#define BST_APP_RX_TIME_OUT             ( BST_IP_RX_TIME_OUT + BST_OS_MS_IN_S )


#define BST_APP_IsEncrpValid(Mode)     ( ( ( Mode ) > BST_APP_ENCRP_INVALID_TYPE )\
                                      && ( ( Mode ) < BST_APP_ENCRP_MODE_BUTT ) )
#define BST_APP_IsHbChkTypeValid(Type) ( ( ( Type ) > BST_APP_HB_INVALID_CHK_TYPE )\
                                      && ( ( Type ) < BST_APP_HB_CHK_TYPE_BUTT ) )

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/
enum OBJ_TYPE_ENUM
{
    BST_APP_TYPE_MIN                = 0,
    BST_APP_TYPE_SYSTASK,
    BST_APP_TYPE_MAILBOX,
    BST_APP_TYPE_HEARTBEAT,
    BST_OBJ_TYPE_MAX
};
typedef BST_UINT8                       BST_APP_TYPE_ENUM_UINT8;

enum BST_ENCRP_MODE_ENUM
{
    BST_APP_ENCRP_INVALID_TYPE          = 0,
    BST_APP_ENCRP_NO_TYPE,
    BST_APP_ENCRP_SSL_MODE,
    BST_APP_ENCRP_TLS_MODE,
    BST_APP_ENCRP_MODE_BUTT
};
typedef BST_UINT32                       BST_APP_ENCRP_MODE_ENUM_UINT32;

/*****************************************************************************
  5 类/结构定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : BST_HB_RETRY_INFO
 协议表格  :
 ASN.1描述 :
 枚举说明  : 定义应用发送重传所需的信息
*****************************************************************************/
typedef struct 
{
    BST_UINT32                          ulMaxReTimes;       /*最大重传次数*/
    BST_UINT32                          ulIntervals;        /*超时间隔时间*/
}BST_HB_RETRY_INFO;

/*****************************************************************************
 枚举名    : TX_HB_RETRY_TIMER_STRU
 协议表格  :
 ASN.1描述 :
 枚举说明  : 应用发送重传定时器的相关信息
*****************************************************************************/
typedef struct
{
    BST_OS_TIMERID_T      ulTimerId;
    BST_UINT32            usRetryNum;                       /*当前重传次数*/
    BST_HB_RETRY_INFO     stRetryInfo;
} TX_HB_RETRY_TIMER_STRU; 


/*****************************************************************************
  7 全局变量声明
*****************************************************************************/

/*****************************************************************************
  8 函数声明
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif

