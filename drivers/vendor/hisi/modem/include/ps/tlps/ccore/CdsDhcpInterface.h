/******************************************************************************

                  版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CdsDhcpInterface.h
  版 本 号   : 初稿
  作    者   : w00316385
  生成日期   : 2015年05月18日
  最近修改   :
  功能描述   : CDS与DHCP之间的接口
  函数列表   :
  修改历史   :
  1.日    期   : 2015年05月18日
    作    者   : w00316385
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CDSDHCPINTERFACE_H__
#define __CDSDHCPINTERFACE_H__

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
#endif


/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define DHCP_CDS_MSG_HDR                      (PS_MSG_ID_DHCP_TO_CDS_BASE)
#define CDS_DHCP_MSG_HDR                      (PS_MSG_ID_CDS_TO_DHCP_BASE)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 结构名    : DHCP_CDS_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS向DHCP返回的确认消息
*****************************************************************************/
enum DHCP_CDS_RESULT_ENUM
{
    DHCP_CDS_RESULT_SUCC                     = 0x00,
    DHCP_CDS_RESULT_FAIL                     = 0x01,

    DHCP_CDS_RESULT_BUTT
};
typedef VOS_UINT32 DHCP_CDS_RESULT_ENUM_UINT32;

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
 结构名    : DHCP_CDS_MSG_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : DHCP和CDS模块间的接口消息
*****************************************************************************/
enum DHCP_CDS_MSG_TYPE_ENUM
{
    ID_DHCP_CDS_START_FILTER_REQ             = (DHCP_CDS_MSG_HDR + 0x00),       /* DHCP通知CDS开启过滤 */
    ID_CDS_DHCP_START_FILTER_CNF             = (CDS_DHCP_MSG_HDR + 0x00),       /* 上述消息确认消息 */

    ID_DHCP_CDS_STOP_FILTER_REQ              = (DHCP_CDS_MSG_HDR + 0x01),       /* DHCP通知CDS停止过滤 */
    ID_CDS_DHCP_STOP_FILTER_CNF              = (CDS_DHCP_MSG_HDR + 0x01),       /* 上述消息确认消息 */

    ID_DHCP_CDS_DATA_REQ                     = (DHCP_CDS_MSG_HDR + 0x02),       /* DHCP向CDS发送消息 */

    ID_DHCP_CDS_MSG_TYPE_END
};
typedef VOS_UINT16 DHCP_CDS_MSG_TYPE_ENUM_UINT16;

/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/*****************************************************************************
 结构名    : DHCP_CDS_DATA_REQ
 协议表格  :
 ASN.1描述 :
 结构说明  : DHCP向CDS发送消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    DHCP_CDS_MSG_TYPE_ENUM_UINT16      enMsgId;             /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16               enModemId;           /*ModemId*/
    VOS_UINT8                          ucRabId;             /* RAB标识，取值范围:[5,15] */
    VOS_UINT8                          aucRev[3];           /*保留位*/
    TTF_MEM_ST                        *pstIpPacket;         /*数据包指针*/
} DHCP_CDS_DATA_REQ_STRU;

/*****************************************************************************
 结构名    : DHCP_CDS_START_FILTER_REQ
 协议表格  :
 ASN.1描述 :
 结构说明  : DHCP向CDS发送开启包过滤消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    DHCP_CDS_MSG_TYPE_ENUM_UINT16       enMsgId;            /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /*ModemId*/
} DHCP_CDS_START_FILTER_REQ_STRU;

/*****************************************************************************
 结构名    : CDS_DHCP_START_FILTER_CNF
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS向DHCP回复开启DHCP包过滤消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    DHCP_CDS_MSG_TYPE_ENUM_UINT16       enMsgId;            /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /*ModemId*/
    DHCP_CDS_RESULT_ENUM_UINT32         enRslt;
} CDS_DHCP_START_FILTER_CNF_STRU;

/*****************************************************************************
 结构名    : DHCP_CDS_STOP_FILTER_REQ
 协议表格  :
 ASN.1描述 :
 结构说明  : DHCP向CDS发送停止包过滤消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    DHCP_CDS_MSG_TYPE_ENUM_UINT16       enMsgId;            /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /*ModemId*/
} DHCP_CDS_STOP_FILTER_REQ_STRU;

/*****************************************************************************
 结构名    : CDS_DHCP_STOP_FILTER_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS向DHCP回复停止包过滤消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    DHCP_CDS_MSG_TYPE_ENUM_UINT16       enMsgId;            /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /*ModemId*/
    DHCP_CDS_RESULT_ENUM_UINT32         enRslt;
} CDS_DHCP_STOP_FILTER_CNF_STRU;

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

#endif /* end of CdsDhcpInterface.h */

