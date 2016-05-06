/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : RegeditryDefine.h
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年4月16日
  最近修改   :
  功能描述   : 注册表类的一些枚举定义头文件
  函数列表   :

  修改历史   :
  1.日    期   : 2014年04月16日
    作    者   : d00173029
    修改内容   : 创建文件

******************************************************************************/

#ifndef __BST_CORE_REGISTRYDEFINE_H__
#define __BST_CORE_REGISTRYDEFINE_H__
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_Platform.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_CORE_REGTABL_INIT                                                                                           \
    { BST_PID_INVALID,                  BST_CORE_PID_FIX_LEN,   0                                                   },  \
    { BST_PID_FEATURE_SUPPORT,          BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF(BST_UINT32)                           },  \
    { BST_PID_NET_STATE,                BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF(BST_NET_STATE_STRU)                   },  \
    { BST_PID_TIMESTAMP,                BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF(BST_DRV_NET_TIME_CLBRT_STRU)          },  \
    { BST_PID_SOCKET_INFO,              BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF(BST_IP_SOCKET_ADD_T)                  },  \
    { BST_PID_PERIODIC,                 BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF(BST_UINT32)                           },  \
    { BST_PID_PROTOCOL_TYPE,            BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF(BST_PRTC_TYPE_ENUM_UINT32)            },  \
    { BST_PID_SOCKET_PROPERTY,          BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF( BST_IP_SKT_PROPTY_STRU )             },  \
    { BST_PID_CIPHER_MODE,              BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF(BST_APP_ENCRP_MODE_ENUM_UINT32)       },  \
    { BST_PID_CIPHER_CODE,              BST_CORE_PID_VAR_LEN,   0                                                   },  \
    { BST_PID_TRAFFIC_FLOW,             BST_CORE_PID_VAR_LEN,   0                                                   },  \
    { BST_PID_TRAFFIC_LIMITE,           BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF( BST_UINT32 )                         },  \
    { BST_PID_MODEM_RAB_ID,             BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF( BST_DRV_NET_MODEM_RABID_STRU )       },  \
    { BST_PID_NETWORK_QUALITY,          BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF( BST_UINT32 )                         },  \
    { BST_PID_AP_SLEEP_STATE,           BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF( BST_UINT32 )                         },  \
    { BST_PID_GET_CONGESTION,           BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF( BST_UINT32 )                         },  \
    { BST_PID_SET_CONGESTION,           BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF( BST_UINT32 )                         },  \
    { BST_PID_SOCKET_FD,                BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF( BST_UINT32 )                         },  \
    { BST_PID_SET_RRC_KEEP_TIME,        BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF( BST_UINT32 )                         },  \
    /*Email*/                                                                                                           \
    { BST_PID_EMAIL_PROTOCOL_TYPE,      BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF( MAIL_BOX_TYPE_ENUM_UINT32 )          },  \
    { BST_PID_EMAIL_SYNC_TYPE,          BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF( SYNC_TYPE_ENUM_UINT32)               },  \
    { BST_PID_EMAIL_ACCOUNT,            BST_CORE_PID_VAR_LEN,   0                                                   },  \
    { BST_PID_EMAIL_PASSWORD,           BST_CORE_PID_VAR_LEN,   0                                                   },  \
    { BST_PID_EMAIL_LAST_UID,           BST_CORE_PID_VAR_LEN,   0                                                   },  \
    { BST_PID_EMAIL_DEVICE_ID,          BST_CORE_PID_VAR_LEN,   0                                                   },  \
    { BST_PID_EMAIL_EXCG_HTTP_INFO,     BST_CORE_PID_VAR_LEN,   0                                                   },  \
    { BST_PID_IMAP_ID_CMD,              BST_CORE_PID_VAR_LEN,   0                                                   },  \
    { BST_PID_EMAIL_EXCG_WXML_INFO,     BST_CORE_PID_VAR_LEN,   0                                                   },  \
    /*Heartbeat*/                                                                                                       \
    { BST_PID_HB_SEND_CONTENT,          BST_CORE_PID_VAR_LEN,   0                                                   },  \
    { BST_PID_HB_RESP_CONTENT,          BST_CORE_PID_VAR_LEN,   0                                                   },  \
    { BST_PID_HB_SERIAL_NUM,            BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF(SERNO_HB_INFO_STRU)                   },  \
    { BST_PID_HB_CHECK_TYPE,            BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF(BST_APP_HB_CHECK_TYPE_ENUM_UINT32)    },  \
    { BST_PID_HB_TX_RETRY_MAX,          BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF( BST_HB_RETRY_INFO )                  },  \
    { BST_PID_LH_RELINK_ENABLE,         BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF( BST_UINT32 )                         },  \
    { BST_PID_LH_SOCKET_EST,            BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF( BST_UINT32 )                         },  \
    { BST_PID_LH_SOCKET_PARAM,          BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF( BST_IP_SKT_PARAM_STRU )              },  \
    { BST_PID_LH_IS_DETECTOR,           BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF( BST_UINT32 )                         },  \
    { BST_PID_HB_CONF_CYC,              BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF( BST_UINT32 )                         },  \
    { BST_PID_SYNC_PROPERTY_START,      BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF( BST_IP_SKT_PROPTY_STRU )             },  \
    { BST_PID_SYNC_PROPERTY_STOP,       BST_CORE_PID_FIX_LEN,   BST_OS_SIZEOF( BST_UINT32 )                         },  \


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
enum BST_PARAM_ID_ENUM
{
    BST_PID_INVALID                     = 0,
    BST_PID_FEATURE_SUPPORT,            /*1 */
    BST_PID_NET_STATE,                  /*2 */
    BST_PID_TIMESTAMP,                  /*3 */
    BST_PID_SOCKET_INFO,                /*4 */
    BST_PID_PERIODIC,                   /*5 */
    BST_PID_PROTOCOL_TYPE,              /*6 */
    BST_PID_SOCKET_PROPERTY,            /*7 */
    BST_PID_CIPHER_MODE,                /*8 */
    BST_PID_CIPHER_CODE,                /*9 */
    BST_PID_TRAFFIC_FLOW,               /*10*/
    BST_PID_TRAFFIC_LIMITE,             /*11*/
    BST_PID_MODEM_RAB_ID,               /*12*/
    BST_PID_NETWORK_QUALITY,            /*13*/
    BST_PID_AP_SLEEP_STATE,             /*14*/
    BST_PID_GET_CONGESTION,             /*15*/
    BST_PID_SET_CONGESTION,             /*16*/
    BST_PID_SOCKET_FD,                  /*17*//*Modem没有注册，只在此文件中添加*/
    BST_PID_SET_RRC_KEEP_TIME,          /*18*/
    /*email*/
    BST_PID_EMAIL_PROTOCOL_TYPE,        /*19*/
    BST_PID_EMAIL_SYNC_TYPE,            /*20*/
    BST_PID_EMAIL_ACCOUNT,              /*21*/
    BST_PID_EMAIL_PASSWORD,             /*22*/
    BST_PID_EMAIL_LAST_UID,             /*23*/
    BST_PID_EMAIL_DEVICE_ID,            /*24*/
    BST_PID_EMAIL_EXCG_HTTP_INFO,       /*25*/
    BST_PID_IMAP_ID_CMD,                /*26*/
    BST_PID_EMAIL_EXCG_WXML_INFO,       /*27*/

    /*heartbeat*/
    BST_PID_HB_SEND_CONTENT,            /*28*/
    BST_PID_HB_RESP_CONTENT,            /*29*/
    BST_PID_HB_SERIAL_NUM,              /*30*/
    BST_PID_HB_CHECK_TYPE,              /*31*/
    BST_PID_HB_TX_RETRY_MAX,            /*32*/
    BST_PID_LH_RELINK_ENABLE,           /*33*/
    BST_PID_LH_SOCKET_EST,              /*34*/
    BST_PID_LH_SOCKET_PARAM,            /*35*/
    BST_PID_LH_IS_DETECTOR,             /*36*/
    BST_PID_HB_CONF_CYC,                /*37*/
    BST_PID_SYNC_PROPERTY_START,        /*38*/
    BST_PID_SYNC_PROPERTY_STOP,         /*39*/
    BST_PID_DEF_BUTT
};
typedef BST_UINT16                      BST_CORE_PID_ENUM_UINT16;

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#endif
