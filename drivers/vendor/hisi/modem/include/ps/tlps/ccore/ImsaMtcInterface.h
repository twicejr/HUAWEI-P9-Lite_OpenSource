

#ifndef __IMSAMTCINTERFACE_H__
#define __IMSAMTCINTERFACE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/



/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
 枚举名    : IMSA_MTC_MSG_ID_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : IMSA和MTC之间消息ID定义
*****************************************************************************/
enum    IMSA_MTC_MSG_ID_ENUM
{
    /* IMSA->MTC */
    ID_IMSA_MTC_SRV_CONN_STATUS_NOTIFY    = 0x0001,             /* _H2ASN_MsgChoice IMSA_MTC_SRV_CONN_STATUS_NOTIFY_STRU */


    /* IMSA->MTC */
    ID_MTC_IMSA_MODEM1_INFO_IND           = 0x1001,             /* _H2ASN_MsgChoice MTC_IMSA_MODEM1_INFO_IND_STRU */

    ID_IMSA_MTC_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 IMSA_MTC_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum    IMSA_SRV_CONN_STATUS_EXIST_ENUM
{
    IMSA_SRV_CONN_STATUS_ISNOT_EXIST,
    IMSA_SRV_CONN_STATUS_IS_EXIST,
    IMSA_SRV_CONN_STATUS_BUTT
};
typedef VOS_UINT8 IMSA_SRV_CONN_STATUS_EXIST_ENUM_UINT8;


enum MTC_IMSA_MODEM_POWER_STATE_ENUM
{
    MTC_IMSA_MODEM_POWER_OFF            = 0x00,
    MTC_IMSA_MODEM_POWER_ON,

    MTC_IMSA_MODEM_POWER_STATE_BUTT
};
typedef VOS_UINT8 MTC_IMSA_MODEM_POWER_STATE_ENUM_UINT8;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
 结构名    : IMSA_MTC_SRV_CONN_STATUS_NOTIFY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSA_MTC_SRV_CONN_STATUS_NOTIFY_STRU消息结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /* _H2ASN_Skip */
    VOS_UINT32                              ulMsgId;            /* _H2ASN_Skip */
    IMSA_SRV_CONN_STATUS_EXIST_ENUM_UINT8   enIsImsSrvExist;    /* 是否存在IMS业务  0表示不存在， 1表示存在*/
    VOS_UINT8                               aucReserved[3];
} IMSA_MTC_SRV_CONN_STATUS_NOTIFY_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    IMSA_MTC_MSG_ID_ENUM_UINT32                     ulMsgId;                    /*_H2ASN_Skip*/
    MTC_IMSA_MODEM_POWER_STATE_ENUM_UINT8           enPowerState;               /* Modem1开关机状态 */
    VOS_UINT8                                       aucReserved[3];
}MTC_IMSA_MODEM1_INFO_IND_STRU;



typedef struct
{
    VOS_UINT32                          ulMsgId;            /*_H2ASN_MsgChoice_Export IMSA_MTC_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          IMSA_MTC_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}IMSA_MTC_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    IMSA_MTC_MSG_DATA                     stMsgData;
}ImsaMtcInterface_MSG;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif

#endif /* end of ImsaIntraInterface.h */

