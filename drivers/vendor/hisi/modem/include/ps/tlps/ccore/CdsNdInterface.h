/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CdsNdInterface.h
  版 本 号   : 初稿
  作    者   : h00159435
  生成日期   : 2011年12月9日
  最近修改   :
  功能描述   : CDS与ND CLIENT之间的接口
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月9日
    作    者   : h00159435
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CDSNDINTERFACE_H__
#define __CDSNDINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "vos.h"
#include "LPSCommon.h"
#include "PsTypeDef.h"
#include "TTFMemInterface.h"

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#pragma warning(disable:4200)
#endif


/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define NDCLIENT_CDS_MSG_HDR                  (PS_MSG_ID_NDCLIENT_TO_CDS_BASE)
#define CDS_NDCLIENT_MSG_HDR                  (PS_MSG_ID_CDS_TO_NDCLIENT_BASE)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 结构名    : NDCLIENT_CDS_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS向ND CLIENT返回的确认消息
*****************************************************************************/
enum NDCLIENT_CDS_RESULT_ENUM
{
    NDCLIENT_CDS_RESULT_SUCC                 = 0x00,
    NDCLIENT_CDS_RESULT_FAIL                 = 0x01,

    NDCLIENT_CDS_RESULT_BUTT
};
typedef VOS_UINT32 NDCLIENT_CDS_RESULT_ENUM_UINT32;

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
 结构名    : NDCLIENT_CDS_MSG_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : ND CLIENT和CDS模块间的接口消息
*****************************************************************************/
enum NDCLIENT_CDS_MSG_TYPE_ENUM
{
    ID_NDCLIENT_CDS_START_FILTER_REQ         = (NDCLIENT_CDS_MSG_HDR + 0x00), /**/    /* NDCLIENT通知CDS开启RA过滤 */
    ID_CDS_NDCLIENT_START_FILTER_CNF         = (CDS_NDCLIENT_MSG_HDR + 0x00), /**/    /* 上述消息确认消息 */

    ID_NDCLIENT_CDS_STOP_FILTER_REQ          = (NDCLIENT_CDS_MSG_HDR + 0x01), /**/    /* NDCLIENT通知CDS停止RA过滤 */
    ID_CDS_NDCLIENT_STOP_FILTER_CNF          = (CDS_NDCLIENT_MSG_HDR + 0x01), /**/    /* 上述消息确认消息 */

    ID_NDCLIENT_CDS_DATA_REQ                 = (NDCLIENT_CDS_MSG_HDR + 0x02), /**/    /* ND CLIENT向CDS发送RS消息 */

    ID_CDS_NDCLIENT_ND_DATA_IND              = (CDS_NDCLIENT_MSG_HDR + 0x02), /**/    /* IMS下，上报ND DATA IND */

    ID_NDCLIENT_CDS_MSG_TYPE_END
};
typedef VOS_UINT32 NDCLIENT_CDS_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/*****************************************************************************
 结构名    : NDCLIENT_CDS_DATA_REQ
 协议表格  :
 ASN.1描述 :
 结构说明  : ND CLIENT向CDS发送RS消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    NDCLIENT_CDS_MSG_TYPE_ENUM_UINT32  ulMsgId;             /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16               enModemId;           /*ModemId*/
    VOS_UINT8                          ucRabId;             /* RAB标识，取值范围:[5,15] */
    VOS_UINT8                          aucRev[1];           /*保留位*/
    TTF_MEM_ST                        *pstIpPacket;         /*数据包指针*/
} NDCLIENT_CDS_DATA_REQ_STRU;

/*****************************************************************************
 结构名    : NDCLIENT_CDS_START_FILTER_REQ
 协议表格  :
 ASN.1描述 :
 结构说明  : ND CLIENT向CDS发送开启RA包过滤消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    NDCLIENT_CDS_MSG_TYPE_ENUM_UINT32   ulMsgId;            /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /*ModemId*/
    VOS_UINT8                           aucReserved[2];
} NDCLIENT_CDS_START_FILTER_REQ_STRU;

/*****************************************************************************
 结构名    : CDS_NDCLIENT_START_FILTER_CNF
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS向ND CLIENT回复开启RA包过滤消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    NDCLIENT_CDS_MSG_TYPE_ENUM_UINT32   ulMsgId;            /*_H2ASN_Skip*/
    NDCLIENT_CDS_RESULT_ENUM_UINT32     enRslt;
    MODEM_ID_ENUM_UINT16                enModemId;          /*ModemId*/
    VOS_UINT8                           aucReserved[2];
} CDS_NDCLIENT_START_FILTER_CNF_STRU;

/*****************************************************************************
 结构名    : NDCLIENT_CDS_STOP_FILTER_REQ
 协议表格  :
 ASN.1描述 :
 结构说明  : ND CLIENT向CDS发送停止RA包过滤消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    NDCLIENT_CDS_MSG_TYPE_ENUM_UINT32   ulMsgId;            /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /*ModemId*/
    VOS_UINT8                           aucReserved[2];
} NDCLIENT_CDS_STOP_FILTER_REQ_STRU;

/*****************************************************************************
 结构名    : CDS_NDCLIENT_STOP_FILTER_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS向ND CLIENT回复停止RA包过滤消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    NDCLIENT_CDS_MSG_TYPE_ENUM_UINT32   ulMsgId;            /*_H2ASN_Skip*/
    NDCLIENT_CDS_RESULT_ENUM_UINT32     enRslt;
    MODEM_ID_ENUM_UINT16                enModemId;          /*ModemId*/
    VOS_UINT8                           aucReserved[2];
} CDS_NDCLIENT_STOP_FILTER_CNF_STRU;

/*****************************************************************************
 结构名    : CDS_NDCLIENT_STOP_FILTER_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 在启用IMS IPV6承载场景下，CDS对ND包软过滤后上报给向ND CLIENT.
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    NDCLIENT_CDS_MSG_TYPE_ENUM_UINT32   enMsgId;                                /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucRabId;                                /* RAB标识，取值范围:[5,15] */
    VOS_UINT8                           aucRsv[1];                              /*保留位*/
    VOS_UINT32                          ulLen;                                  /*数据包长度*/
    VOS_UINT8                           aucData[0];                             /*数据包内容*/
}CDS_NDCLIENT_ND_DATA_IND_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/



/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
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

#endif /* end of CdsNdInterface.h */

