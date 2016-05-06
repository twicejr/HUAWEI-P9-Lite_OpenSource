/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CdsRabmInterface.h
  版 本 号   : 初稿
  作    者   : o00132663
  生成日期   : 2011年12月9日
  最近修改   :
  功能描述   : CDS和RABM之间的接口
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月9日
    作    者   : o00132663
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CDSRABMINTERFACE_H__
#define __CDSRABMINTERFACE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TTFMemInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define RABM_CDS_MSG_HDR                (0x00)
#define CDS_RABM_MSG_HDR                (0x10)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
枚举名    : RABM_RAB_STATUS_ENUM
结构说明  : RABID状态枚举

  1.日    期   : 2011年12月9日
    作    者   : 欧阳飞/o00132663
    修改内容   : 创建
*****************************************************************************/
enum RABM_RAB_STATUS_ENUM
{
    RABM_RAB_STATUS_IDLE                = 0x00,             /* RAB空闲态 */
    RABM_RAB_STATUS_ACTIVE              = 0x01,             /* RAB连接态 */
    RABM_RAB_STATUS_SUSPEND             = 0x02,             /* RAB挂起态 */
    RABM_RAB_STATUS_FAIL                = 0x03,             /* PDP未激活，RAB不存在 */
    RABM_RAB_STATUS_BUTT
};
typedef VOS_UINT32 RABM_RAB_STATUS_ENUM_UINT32;

/*****************************************************************************
枚举名    : CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_ENUM
结构说明  : RABM发送数据指示类型枚举

  1.日    期   : 2011年12月9日
    作    者   : 欧阳飞/o00132663
    修改内容   : 创建
*****************************************************************************/
enum CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_ENUM
{
    CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_SERVICE_SUCC    = 0,                   /* 数传重建成功 */
    CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_DRB_CONN        = 1,                   /* GU模RABM不维护DRB状态，暂未使用 */
    CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_BUTT
};
typedef VOS_UINT32 CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_ENUM_UINT32;

/* QCI类型 */
enum QCI_TYPE_ENUM
{
    QCI_TYPE_QCI1_GBR           = 1,
    QCI_TYPE_QCI2_GBR           = 2,
    QCI_TYPE_QCI3_GBR           = 3,
    QCI_TYPE_QCI4_GBR           = 4,
    QCI_TYPE_QCI5_NONGBR        = 5,
    QCI_TYPE_QCI6_NONGBR        = 6,
    QCI_TYPE_QCI7_NONGBR        = 7,
    QCI_TYPE_QCI8_NONGBR        = 8,
    QCI_TYPE_QCI9_NONGBR        = 9,

    QCI_TYPE_BUTT
};

typedef VOS_UINT8  QCI_TYPE_ENUM_UINT8;

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
枚举名    : CDS_RABM_MSG_ID_ENUM
结构说明  : CDS与RABM的消息名枚举

  1.日    期   : 2011年12月9日
    作    者   : 欧阳飞/o00132663
    修改内容   : 创建
*****************************************************************************/
enum CDS_RABM_MSG_ID_ENUM
{
    /* CDS发给RABM的消息 */
    ID_CDS_RABM_SERVICE_IND             = CDS_RABM_MSG_HDR + 0x00,              /* 业务请求消息，促发RABM进行数传重建 */

    /* RABM发给CDS的消息 */
    ID_RABM_CDS_SEND_BUFF_DATA_IND      = RABM_CDS_MSG_HDR + 0x00,              /* RABM通知CDS，指示可以发送数据 */
    ID_RABM_CDS_FREE_BUFF_DATA_IND      = RABM_CDS_MSG_HDR + 0x01,              /* RABM通知CDS，指示释放缓存数据包 */
    ID_QOS_FC_RABM_RAB_CREATE_IND       = RABM_CDS_MSG_HDR + 0x02,              /* _H2ASN_MsgChoice CDS_FC_START_CHANNEL_IND_STRU */
    ID_QOS_FC_RABM_RAB_RELEASE_IND      = RABM_CDS_MSG_HDR + 0x03,              /* _H2ASN_MsgChoice CDS_FC_STOP_CHANNEL_IND_STRU */
    ID_RABM_CDS_VOICEPREFER_ACT_IND     = RABM_CDS_MSG_HDR + 0x04,              /* _H2ASN_MsgChoice RABM_CDS_VOICEPREFER_ACT_IND_STRU */
    ID_RABM_CDS_MSG_ID_BUTT
};
typedef VOS_UINT32 CDS_RABM_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
结构名    : CDS_RABM_SERVICE_IND_STRU
结构说明  : CDS与RABM的SERVICE IND消息结构定义

  1.日    期   : 2011年12月9日
    作    者   : 欧阳飞/o00132663
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CDS_RABM_MSG_ID_ENUM_UINT32         enMsgId;            /* 消息名 */
    VOS_UINT8                           ucRabId;            /* Rab ID */
    VOS_UINT8                           aucReserved[3];     /* 保留位 */
} CDS_RABM_SERVICE_IND_STRU;

/*****************************************************************************
结构名    : CDS_RABM_SEND_BUFF_DATA_IND_STRU
结构说明  : CDS与RABM的发送数据指示消息结构定义

  1.日    期   : 2011年12月9日
    作    者   : 欧阳飞/o00132663
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CDS_RABM_MSG_ID_ENUM_UINT32                             enMsgId;                                /* 消息名 */
    CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_ENUM_UINT32        enSndBuffDataAllowedType;               /* 发送数据指示类型 */
    VOS_UINT8                                               ucRabId;                                /* Rab ID */
    VOS_UINT8                                               aucReserved[3];                         /* 保留位 */
} CDS_RABM_SEND_BUFF_DATA_IND_STRU;

/*****************************************************************************
结构名    : CDS_RABM_FREE_BUFF_DATA_IND_STRU
结构说明  : CDS与RABM的释放缓存数据指示消息结构定义

  1.日    期   : 2011年12月9日
    作    者   : 欧阳飞/o00132663
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CDS_RABM_MSG_ID_ENUM_UINT32         enMsgID;            /* 消息名 */
    VOS_UINT8                           ucRabId;            /* Rab ID */
    VOS_UINT8                           aucReserved[3];     /* 保留位 */
} CDS_RABM_FREE_BUFF_DATA_IND_STRU;

/*****************************************************************************
结构名    : CDS_RABM_TRANS_DATA_STRU
结构说明  : CDS与RABM的上下行数据结构定义

  1.日    期   : 2011年12月9日
    作    者   : 欧阳飞/o00132663
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRabId;            /* RAB ID值 */
    VOS_UINT8                           aucRev[3];          /* 保留位 */
    VOS_UINT32                          ulSduLen;           /* 数据长度 */
    TTF_MEM_ST                         *pstSdu;             /* 上下行数据指针 */
}CDS_RABM_TRANS_DATA_STRU;

typedef struct
{
    VOS_MSG_HEADER
    CDS_RABM_MSG_ID_ENUM_UINT32         enMsgId;
    QCI_TYPE_ENUM_UINT8                 enQci;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           ucLinkRabId;
    VOS_UINT8                           ucRev;
} QOS_FC_RAB_CREATE_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER
    CDS_RABM_MSG_ID_ENUM_UINT32         enMsgId;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           ucRev[3];
} QOS_FC_RAB_RELEASE_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER
    CDS_RABM_MSG_ID_ENUM_UINT32         enMsgId;
    VOS_UINT32                          ulVoicePreferActInd;
}RABM_CDS_VOICEPREFER_ACT_IND_STRU;
/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
RABM_RAB_STATUS_ENUM_UINT32 NAS_RABM_GetRabIdStatus
(
    VOS_UINT8                           ucRabId
);

VOS_VOID NAS_RABM_UL_DataReq
(
    CDS_RABM_TRANS_DATA_STRU           *pstUlData
);

extern VOS_VOID CDS_GSM_DL_DataInd
(
    CDS_RABM_TRANS_DATA_STRU           *pstDlData,
    MODEM_ID_ENUM_UINT16                enModemId
);
extern VOS_VOID CDS_UMTS_DL_DataInd
(
    CDS_RABM_TRANS_DATA_STRU           *pstDlData,
    MODEM_ID_ENUM_UINT16                enModemId
);

extern VOS_VOID NAS_RABM_SetFinIpInRdFlag(VOS_UINT32 ulFlag);

VOS_UINT32 NAS_RABM_GetDefaultRabId(
    VOS_UINT8                           ucRabId,
    VOS_UINT8                          *pucDeftRabId
);


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

#endif /* end of CdsRabmInterface.h */
