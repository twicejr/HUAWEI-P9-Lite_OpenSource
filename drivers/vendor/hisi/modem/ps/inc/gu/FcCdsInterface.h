/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : FcCdsInterface.h
  版 本 号   : 初稿
  作    者   : g45205
  生成日期   : 2011年12月1日
  最近修改   :
  功能描述   : FcCdsInterface.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月1日
    作    者   : g45205
    修改内容   : 创建文件

******************************************************************************/

#ifndef __FCCDSINTERFACE_H__
#define __FCCDSINTERFACE_H__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "OmApi.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 消息头定义
*****************************************************************************/
enum CDS_FC_MSG_TYPE_ENUM
{
    ID_CDS_FC_START_CHANNEL_IND       = 0x0001,     /* _H2ASN_MsgChoice CDS_FC_START_CHANNEL_IND_STRU */
    ID_CDS_FC_STOP_CHANNEL_IND        = 0x0002,     /* _H2ASN_MsgChoice CDS_FC_STOP_CHANNEL_IND_STRU */
    ID_FC_CDS_DL_THRES_CHG_IND        = 0x0003,     /* _H2ASN_MsgChoice FC_CDS_THRES_CHG_IND_STRU */
    ID_CDS_FC_MSG_TYPE_BUTT           = 0xFFFF
};
typedef VOS_UINT32 CDS_FC_MSG_TYPE_ENUM_UINT32;


/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    CDS_FC_MSG_TYPE_ENUM_UINT32         enMsgName;          /* _H2ASN_Skip */
    MODEM_ID_ENUM_UINT16                enModemId;          /* _H2ASN_Replace VOS_UINT16  enModemId; */
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           aucReserved[1];
} CDS_FC_START_CHANNEL_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    CDS_FC_MSG_TYPE_ENUM_UINT32         enMsgName;          /* _H2ASN_Skip */
    MODEM_ID_ENUM_UINT16                enModemId;          /* _H2ASN_Replace VOS_UINT16  enModemId; */
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           aucReserved[1];
} CDS_FC_STOP_CHANNEL_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    CDS_FC_MSG_TYPE_ENUM_UINT32         enMsgName;          /* _H2ASN_Skip */
    VOS_UINT8                           ucThres;
    VOS_UINT8                           aucReserved[3];
}FC_CDS_THRES_CHG_IND_STRU;
/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    CDS_FC_MSG_TYPE_ENUM_UINT32         enMsgID;    /*_H2ASN_MsgChoice_Export CDS_FC_MSG_TYPE_ENUM_UINT32*/

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CDS_FC_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}FC_CDS_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    FC_CDS_MSG_DATA                     stMsgData;
}FcCdsInterface_MSG;


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern SPY_DATA_DOWNGRADE_RESULT_ENUM_UINT32 FC_DownUlGradeProcess(VOS_VOID);
extern SPY_DATA_UPGRADE_RESULT_ENUM_UINT32 FC_UpUlGradeProcess(VOS_VOID);
extern VOS_VOID FC_RecoverUlGradeProcess(VOS_VOID);
extern unsigned int FC_CPU_Process( unsigned int ulCpuLoad );


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of FcCdsInterface.h */

