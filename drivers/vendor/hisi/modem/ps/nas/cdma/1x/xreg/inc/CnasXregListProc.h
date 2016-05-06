/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXregListProc.h
  版 本 号   : 初稿
  作    者   :
  生成日期   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2014年09月05日
    作    者   :
    修改内容   : 创建文件
******************************************************************************/
#ifndef _CNAS_XREG_LIST_PROC_H_
#define _CNAS_XREG_LIST_PROC_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "CnasXregProcess.h"
#include  "hi_list.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define CNAS_XREG_ZONE_NODE_MAX_NUM     (7)     /* 协议规定的最小值:N9m */
#define CNAX_XREG_SIDNID_NODE_MAX_NUM   (4)     /* 协议规定的最小值:N10m */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum CNAS_XREG_LIST_ENUM
{
    CNAS_XREG_ZONE_USED_LIST_ID = 0,
    CNAS_XREG_ZONE_FREE_LIST_ID,
    CNAS_XREG_SIDNID_USED_LIST_ID,
    CNAS_XREG_SIDNID_FREE_LIST_ID,
    CNAS_XREG_LIST_BUTT
};

typedef VOS_UINT8  CNAS_XREG_LIST_ID_ENUM_UINT8;

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
    HI_LIST_S                           stListNode;
    VOS_UINT32                          ulSecNum;
    VOS_UINT16                          usRegZone;
    VOS_UINT16                          usRsv;
    VOS_UINT16                          usSid;
    VOS_UINT16                          usNid;
    CNAS_XREG_BLKSYS_ENUM_UINT8         enBlkSys;
    VOS_UINT8                           ucRsv1;
    VOS_UINT16                          usBandClass;
}CNAS_XREG_ZONE_NODE_STRU;

typedef struct
{
    HI_LIST_S                           stListNode;
    VOS_UINT32                          ulSecNum;
    VOS_UINT16                          usSid;
    VOS_UINT16                          usNid;
    CNAS_XREG_BLKSYS_ENUM_UINT8         enBlkSys;
    VOS_UINT8                           ucRsv;
    VOS_UINT16                          usBandClass;
}CNAS_XREG_SIDNID_NODE_STRU;

typedef struct
{
    VOS_UINT32                          ulNodeCount;
    HI_LIST_S                           stListHeader;
}CNAS_XREG_LIST_HEADER_STRU;

typedef struct
{
    VOS_UINT32                          ulPreSlice;     /* 上一次的SLICE值，单位为1/32768秒 */
    VOS_UINT32                          ulSecNum;       /* 从单板上电后开始时间，单位为秒 */
}CNAS_XREG_TIME_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    CNAS_XREG_MNTN_MSGID_ENUM_UINT32    enMsgId;
    VOS_UINT32                          ulCurSlice;
    CNAS_XREG_ZONE_NODE_STRU            astZoneNode[CNAS_XREG_ZONE_NODE_MAX_NUM];
}CNAS_XREG_ZONE_LIST_MNTN_STRU;

typedef struct
{
    VOS_MSG_HEADER
    CNAS_XREG_MNTN_MSGID_ENUM_UINT32    enMsgId;
    CNAS_XREG_TIME_INFO_STRU            stTimeInfo;
    CNAS_XREG_SIDNID_NODE_STRU          astSidNidNode[CNAX_XREG_SIDNID_NODE_MAX_NUM];
}CNAS_XREG_SIDNID_LIST_MNTN_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT8 CNAS_XREG_GetNodeCount(CNAS_XREG_LIST_ID_ENUM_UINT8 enListId);

VOS_VOID CNAS_XREG_SetNodeCount(CNAS_XREG_LIST_ID_ENUM_UINT8 enListId, VOS_UINT32 ulNodeCount);

VOS_VOID CNAS_XREG_IncNodeCount(CNAS_XREG_LIST_ID_ENUM_UINT8 enListId);

VOS_VOID CNAS_XREG_DecNodeCount(CNAS_XREG_LIST_ID_ENUM_UINT8 enListId);

HI_LIST_S* CNAS_XREG_GetListHeader(CNAS_XREG_LIST_ID_ENUM_UINT8 enListId);

HI_LIST_S* CNAS_XREG_AllocListNode(CNAS_XREG_LIST_ID_ENUM_UINT8 enListId);

VOS_VOID CNAS_XREG_RelCurrZoneNode(VOS_VOID);

VOS_VOID CNAS_XREG_RelZoneListNode(HI_LIST_S *pstZoneNode);

VOS_VOID CNAS_XREG_RelCurrSidNidNode(VOS_VOID);

VOS_VOID CNAS_XREG_RelSidNidListNode(HI_LIST_S *pstSidNidNode);

VOS_VOID CNAS_XREG_InitList(VOS_VOID);

VOS_VOID CNAS_XREG_ClearList(VOS_VOID);

VOS_VOID CNAS_XREG_RestoreList(VOS_VOID);

VOS_VOID CNAS_XREG_SaveList(VOS_VOID);

VOS_VOID CNAS_XREG_AddZoneNode(CNAS_XREG_ZONE_NODE_STRU *pstZoneNode);

VOS_VOID CNAS_XREG_AddCurrZoneNode(VOS_UINT16 usSid, VOS_UINT16 usNid,
                                        VOS_UINT16 usRegZone, VOS_UINT8 ucZoneTimer);

VOS_VOID CNAS_XREG_AddCurrSidNidNode(VOS_UINT16 usSid, VOS_UINT16 usNid,
                                                    VOS_UINT8 ucZoneTimer);

VOS_VOID CNAS_XREG_AddSidNidNode(CNAS_XREG_SIDNID_NODE_STRU *pstSidNidNode);

VOS_VOID CNAS_XREG_RefreshLists(VOS_VOID);

VOS_VOID CNAS_XREG_TotalZones(VOS_UINT8 ucRegZoneNum);

VOS_VOID CNAS_XREG_DelNodesByBandBlkSys(XSD_XREG_SYS_INFO_STRU *pstSysInfo);

CNAS_XREG_ZONE_NODE_STRU *CNAS_XREG_FindZoneNode(VOS_UINT16 usSid, VOS_UINT16 usNid, VOS_UINT16 usRegZone);

CNAS_XREG_SIDNID_NODE_STRU *CNAS_XREG_FindSidNidNode(VOS_UINT16 usSid, VOS_UINT16 usNid);

VOS_VOID CNAS_XREG_UpdateZoneList(XSD_XREG_SYS_INFO_STRU *pstSysInfo, VOS_UINT16 usSid, VOS_UINT16 usNid,
                                    VOS_UINT16 usRegZone, VOS_UINT8 ucZoneTimer);

VOS_VOID CNAS_XREG_UpdateSidNidList(XSD_XREG_SYS_INFO_STRU *pstSysInfo, VOS_UINT16 usSid,
                                                VOS_UINT16 usNid, VOS_UINT8 ucZoneTimer);

VOS_VOID CNAS_XREG_DelMultSids(VOS_VOID);

VOS_VOID CNAS_XREG_DelMultNids(VOS_VOID);

VOS_UINT32 CNAS_XREG_SidNidListIsEmpty(VOS_VOID);
VOS_UINT32 CNAS_XREG_GetSlice(VOS_VOID);

VOS_VOID CNAS_XREG_SidNidListMntn(VOS_VOID);
VOS_VOID CNAS_XREG_ZoneListMntn(VOS_VOID);

#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

