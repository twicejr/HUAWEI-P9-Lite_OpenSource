

#ifndef __IMSALRRCINTERFACE_H__
#define __IMSALRRCINTERFACE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"
#include    "LPSCommon.h"


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
#define  IMSA_LRRC_MSG_HDR   (PS_MSG_ID_IMSA_TO_ERRC_BASE)





/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

enum    IMSA_LRRC_MSG_ID_ENUM
{
    ID_IMSA_LRRC_BEGIN_SESSION_NOTIFY     = (IMSA_LRRC_MSG_HDR + 0x00),     /* _H2ASN_MsgChoice IMSA_LRRC_BEGIN_SESSION_NOTIFY_STRU */
    ID_IMSA_LRRC_END_SESSION_NOTIFY       = (IMSA_LRRC_MSG_HDR + 0x01),     /* _H2ASN_MsgChoice IMSA_LRRC_END_SESSION_NOTIFY_STRU */

    ID_IMSA_LRRC_HIFI_SYNC_SWITCH_IND     = (IMSA_LRRC_MSG_HDR + 0x02),     /* _H2ASN_MsgChoice IMSA_LRRC_HIFI_SYNC_SWITCH_IND_STRU */

    ID_IMSA_LRRC_VOLTE_STATUS_NOTIFY      = (IMSA_LRRC_MSG_HDR + 0x03),    /* _H2ASN_MsgChoice IMSA_LRRC_VOLTE_STATUS_NOTIFY_STRU */

    ID_IMSA_LRRC_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32   IMSA_LRRC_MSG_ID_ENUM_UINT32;



/*****************************************************************************
  4 Enum
*****************************************************************************/

enum IMSA_LRRC_SESSION_TYPE_ENUM
{
    IMSA_LRRC_SESSION_TYPE_MO_NORMAL_CALL,
    IMSA_LRRC_SESSION_TYPE_MT_NORMAL_CALL,
    IMSA_LRRC_SESSION_TYPE_EMERGENCY_CALL,
    IMSA_LRRC_SESSION_TYPE_MO_SS,
    IMSA_LRRC_SESSION_TYPE_MT_SS,
    IMSA_LRRC_SESSION_TYPE_MO_SMS,
    IMSA_LRRC_SESSION_TYPE_MT_SMS,
    IMSA_LRRC_SESSION_TYPE_REGISTER,
    IMSA_LRRC_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 IMSA_LRRC_SESSION_TYPE_ENUM_UINT8;


enum IMSA_LRRC_VOLTE_STATUS_ENUM
{
    IMSA_LRRC_VOLTE_STATUS_INIT,
    IMSA_LRRC_VOLTE_STATUS_START,
    IMSA_LRRC_VOLTE_STATUS_END,

    IMSA_LRRC_VOLTE_STATUS_BUTT
};
typedef VOS_UINT8  IMSA_LRRC_VOLTE_STATUS_ENUM_UINT8;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/

typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;          /* 消息头    */   /*_H2ASN_Skip*/
    IMSA_LRRC_SESSION_TYPE_ENUM_UINT8               enSessionType;
    VOS_UINT8                                       aucReserved[3];
}IMSA_LRRC_BEGIN_SESSION_NOTIFY_STRU;


typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;          /* 消息头    */   /*_H2ASN_Skip*/
    IMSA_LRRC_SESSION_TYPE_ENUM_UINT8               enSessionType;
    VOS_UINT8                                       aucReserved[3];
}IMSA_LRRC_END_SESSION_NOTIFY_STRU;


typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;          /* 消息头    */   /*_H2ASN_Skip*/
    VOS_UINT8                                       ucHifiSyncEnabled;    /* 0表示关闭；1表示打开 */
    VOS_UINT8                                       ucPowerState;         /* Modem1开关机状态，0表示关闭;1表示打开 */
    VOS_UINT8                                       aucReserved[2];
}IMSA_LRRC_HIFI_SYNC_SWITCH_IND_STRU;


/*****************************************************************************
 函数名称: IMSA_LRRC_GetSsacInfo
 协议表格:
 ASN.1 描述:
 函数说明:
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucBarFactorForVoice;   /*取值范围:0~15枚举值*/
    VOS_UINT8    ucBarTimeForVoice;     /*取值范围:0~7枚举值,单位:s*/
    VOS_UINT8    ucBarFactorForVideo;   /*取值范围:0~15枚举值*/
    VOS_UINT8    ucBarTimeForVideo;     /*取值范围:0~7枚举值,单位:s*/
}IMSA_LRRC_SSAC_INFO_STRU;

/*****************************************************************************
 结构名    : IMSA_LRRC_VOLTE_STATUS_NOTIFY_STRU
 结构说明  : IMSA通知LRRC VOLTE流程启动以及结束
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;          /*_H2ASN_Skip*/
    IMSA_LRRC_VOLTE_STATUS_ENUM_UINT8               enVolteStatus;
    VOS_UINT8                                       aucReserved[3];
}IMSA_LRRC_VOLTE_STATUS_NOTIFY_STRU;


/*****************************************************************************
 函数名称: IMSA_LRRC_GetSsacInfo
 协议表格:
 ASN.1 描述:
 函数说明:LRRC提供给IMSA SSAC相关信息
*****************************************************************************/
extern VOS_UINT32  IMSA_LRRC_GetSSACInfo
(
    IMSA_LRRC_SSAC_INFO_STRU *pstSsacInfo
);



extern VOS_UINT32 IMSA_LRRC_JudgeCurrCellSingalQuality(VOS_VOID);
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

#endif /* end of ImsaLrrcInterface.h */








