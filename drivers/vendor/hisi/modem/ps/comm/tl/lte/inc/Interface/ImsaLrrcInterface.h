/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

******************************************************************************
    File name   : ImsaLrrcInterface.h
    Description : Imsa与Lrrc 头文件
    History     :
      1.leili 00132387   2013-10-11  Draft Enact


******************************************************************************/

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
/*****************************************************************************
 枚举名    : IMSA_LRRC_MSG_ID_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : IMSA和LRRC之间的消息接口
 1.日    期   : 2014年7月26日
   作    者   : c00134407
   修改内容   : 新建
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
/*****************************************************************************
 枚举名    : IMSA_LRRC_SESSION_TYPE_ENUM_UINT8
 枚举说明  : SESSION类型
 1.日    期   : 2014年5月22日
   作    者   : h00246512
   修改内容   : 新建
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

/*****************************************************************************
 枚举名   : IMSA_LRRC_VOLTE_STATUS_ENUM_UINT8
 枚举说明  : LMM通知LRRC VOLTE操作的类型
 1.日    期   : 2015年11月30日
   作    者   : l00195322
   修改内容   : 新建
*****************************************************************************/
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
/*****************************************************************************
结构名    : IMSA_LRRC_BEGIN_SESSION_NOTIFY_STRU
结构说明  : SESSION开始指示
1.日    期   : 2014年5月22日
  作    者   : h00246512
  修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;          /* 消息头    */   /*_H2ASN_Skip*/
    IMSA_LRRC_SESSION_TYPE_ENUM_UINT8               enSessionType;
    VOS_UINT8                                       aucReserved[3];
}IMSA_LRRC_BEGIN_SESSION_NOTIFY_STRU;

/*****************************************************************************
 结构名    : IMSA_LRRC_END_SESSION_NOTIFY_STRU
 结构说明  : SESSION终止指示
 1.日    期   : 2014年5月22日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;          /* 消息头    */   /*_H2ASN_Skip*/
    IMSA_LRRC_SESSION_TYPE_ENUM_UINT8               enSessionType;
    VOS_UINT8                                       aucReserved[3];
}IMSA_LRRC_END_SESSION_NOTIFY_STRU;

/*****************************************************************************
 结构名    : IMSA_LRRC_HIFI_SYNC_SWITCH_IND_STRU
 结构说明  : 通知LRRC HIFI同步开关指示
 1.日    期   : 2014年11月14日
   作    者   : l00150010
   修改内容   : 新建
*****************************************************************************/
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

/*****************************************************************************
 Function Name   : IMSA_LRRC_JudgeCurrCellSingalQuality
 Description     : LRRC提供给IMSA接口，用于评估当前信号质量
 Input           : None
 Output          : None
 Return          : 0,信号质量好，LTE上能发起VOLTE电话
                   1,信号质量不好，信号质量差，直接去GU打CS电话

 History         :

    1.l00195322     2015-12-3
*****************************************************************************/

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








