/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CdsImsProc.h
  版 本 号   : 初稿s
  作    者   : y00151394
  生成日期   : 2013年07月30日
  最近修改   :
  功能描述   : 处理和IMS相关的功能
  函数列表   :
  修改历史   :
  1.日    期   : 2013年07月30日
    作    者   : y00151394
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CDS_IMS_PROC_H__
#define __CDS_IMS_PROC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "CdsSoftFilter.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CDS_IMS_MIN_SPEECH_FRM   84


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/

/*定义*/
#define CDS_TRACE_PKT_TO_PC_MASK            (0x01)
#define CDS_TRACE_PKT_TO_OM_MASK            (0x02)

#define CDS_IMS_DL_FRAGMENT_BUFF_SIZE       (50)            /*CDS IMS 下行分片处理缓存*/

/*****************************************************************************
   5 STRUCT定义
*****************************************************************************/


/*****************************************************************************
 结构名    : CDS_IMS_SDU_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMS SDU结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRabId;            /* RAB ID值 */
    VOS_UINT8                           ucDrbId;            /* DRB ID*/
    VOS_UINT8                           aucRev[2];          /* 保留位 */
    VOS_UINT32                          ulSduLen;           /* 数据长度 */
    TTF_MEM_ST                         *pstSdu;             /* 上下行数据指针 */
}CDS_IMS_SDU_STRU;


/*****************************************************************************
 结构名    : CDS_IMS_DL_FRAGMENT_BUFF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMS 下行分片缓存
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulIndex;
    CDS_IP_DATA_INFO_STRU              astIpPktInfo[CDS_IMS_DL_FRAGMENT_BUFF_SIZE];
}CDS_IMS_DL_FRAGMENT_BUFF_STRU;

extern CDS_IMS_DL_FRAGMENT_BUFF_STRU    g_stCdsImsDlFragInfoBuff;

#define CDS_IMS_GET_DL_FRAGMENT_BUFF()  (&g_stCdsImsDlFragInfoBuff)

/*****************************************************************************
  6 UNION定义
*****************************************************************************/


/*****************************************************************************
  7 全局变量声明
*****************************************************************************/


/*****************************************************************************
  8 函数声明
*****************************************************************************/
extern VOS_UINT32 CDS_IsImsBearer(VOS_UINT8 ucRabId,const CDS_ENTITY_STRU *pstCdsEntity);
extern VOS_VOID   CDS_DlProcImsData(CDS_IMS_SDU_STRU *pstSdu, const CDS_ENTITY_STRU *pstCdsEntity);
extern VOS_VOID   CDS_IMSA_MsgProc(MsgBlock  *pstMsg);
extern VOS_VOID   CDS_UlProcImsData(MODEM_ID_ENUM_UINT16 enModemId);
extern VOS_UINT8 CDS_JudgIpPktType(VOS_UINT8 ucRabId, const CDS_ENTITY_STRU *pstCdsEntity, TTF_MEM_ST *pstIpPkt);


/*****************************************************************************
  9 OTHERS定义
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

#endif

