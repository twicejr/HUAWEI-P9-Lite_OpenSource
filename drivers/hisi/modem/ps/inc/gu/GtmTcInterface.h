/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : GtmTcInterface.h
  Author      : l46160
  Version     : V200R001
  Date        : 2006-04-01
  Description : 该头文件定义了---GTM模块对TC提供的接口
  History     :
  1. Date:2006-04-01
     Author: l46160
     Modification:Create
************************************************************************/

#ifndef _GTM_TC_INTERFACE_H_
#define _GTM_TC_INTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define     GTM_STATUS_SETUP_OK     0x00        /* GPRS TEST MODE建立成功 */
#define     GTM_STATUS_SETUP_ERROR  0x01        /* GPRS TEST MODE建立失败 */

/*******************************************************************************
  3 枚举定义
*******************************************************************************/
/*====================*/ /* 消息ID定义 */
enum GRM_TC_MSG_ID_ENUM
{
    /* TC与GRM之间的原语 */
    ID_GRM_GTM_SETUP_REQ    = 0x003C,       /* GRM建立环回请求 */
    ID_TC_GTM_SETUP_CNF     = 0x003D,       /* GRM建立环回确认 */

    ID_TC_GTM_REL_IND       = 0x003E,       /* GRM释放环回指示 */
    ID_GRM_GTM_REL_RSP      = 0x003F,       /* NAS释放GPRS环回响应 */

    ID_TC_GTM_SRB_SETUP_REQ = 0x004C,       /* SRB环回建立请求 */
    ID_GTM_TC_SRB_SETUP_CNF = 0x004D,    	/* SRB环回建立确认 */

    ID_GTM_TC_SRB_REL_IND   = 0x004E,    	/* SRB环回释放指示 */
    ID_TC_GTM_SRB_REL_RSP   = 0x004F     	/* SRB环回释放响应 */

};

typedef VOS_UINT16 GRM_TC_MSG_ID_ENUM_UINT16;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/
#pragma pack(4)

typedef struct
{
    GRM_TC_MSG_ID_ENUM_UINT16   enMsgID;    /*_H2ASN_MsgChoice_Export      GRM_TC_MSG_ID_ENUM_UINT16*/

    VOS_UINT8                   aucMsgBlock[2];
    /******************************************************************************************************
        _H2ASN_MsgChoice_When_Comment          GRM_TC_MSG_ID_ENUM_UINT16
    ******************************************************************************************************/

}GRM_TC_MSG_DATA;
/*_H2ASN_Length UINT32*/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    GRM_TC_MSG_DATA         stMsgData;
}GtmTcInterface_MSG;

typedef struct
{
    VOS_UINT8  ucPduDescript1;          /* GPRS_TEST_MODE消息中的第一个PDU Descript字节 */
    VOS_UINT8  ucPduDescript2;          /* GPRS_TEST_MODE消息中的第二个PDU Descript字节 */
    VOS_UINT8  ucModeFlag;              /* GPRS_TEST_MODE消息中的Mode Flag字节 */
    VOS_UINT8  Rsv;                     /* 四字节对齐 */
}GPRS_TEST_MODE_ST;

/*接口消息定义*/
typedef struct
{
    VOS_MSG_HEADER                      /*_H2ASN_Skip*/
    /*消息类型*/
    VOS_UINT16          usMsgType;      /*_H2ASN_Skip*/

    /*子进程标识,用于定位子进程*/
    VOS_UINT16          usTransId;
} GPRS_LOOP_NO_CONTENT_MSG;

/*接口消息定义*/
typedef struct
{
    VOS_MSG_HEADER                      /*_H2ASN_Skip*/
    /*消息类型*/
    VOS_UINT16              usMsgType;  /*_H2ASN_Skip*/

    /*子进程标识,用于定位子进程*/
    VOS_UINT16              usTransId;
    GPRS_TEST_MODE_ST       stGLSetupReq;
} GRM_GTM_SETUP_REQ_MSG;

/*接口消息定义*/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    VOS_UINT16                          usMsgType;          /* 消息类型 */      /*_H2ASN_Skip*/

    VOS_UINT16                          usModeFlg;          /* 环回模式, 使用前8个bit */

} TC_GTM_SRB_SETUP_REQ_STRU;

/*接口消息定义*/
typedef GPRS_LOOP_NO_CONTENT_MSG TC_GTM_REL_IND_MSG;
typedef GPRS_LOOP_NO_CONTENT_MSG GRM_GTM_REL_RSP_MSG;


/* TC_GTM_SETUP_CNF_MSG的TransId是作为GPRS TEST MODE建立成功或失败的指示 */
typedef GPRS_LOOP_NO_CONTENT_MSG TC_GTM_SETUP_CNF_MSG;

/*EGPRS Interface*/
typedef TC_GTM_SRB_SETUP_REQ_STRU TC_GTM_SRB_SETUP_REQ_MSG;

/* GTM_TC_SRB_SETUP_CNF的TransId是作为EGPRS TEST MODE建立成功或失败的指示 */
typedef GPRS_LOOP_NO_CONTENT_MSG GTM_TC_SRB_SETUP_CNF_MSG;

typedef GPRS_LOOP_NO_CONTENT_MSG GTM_TC_SRB_REL_IND_MSG;
typedef GPRS_LOOP_NO_CONTENT_MSG TC_GTM_SRB_REL_RSP_MSG;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of MapsTemplate.h*/
