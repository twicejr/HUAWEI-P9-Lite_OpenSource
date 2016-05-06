/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsMntn.h
  版 本 号   : 初稿
  作    者   : Y00213812
  生成日期   : 2013年12月13日
  最近修改   :
  功能描述   : TafApsMntn.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年12月13日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAFAPSMNTN_H__
#define __TAFAPSMNTN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafApsTimerMgmt.h"
#include "TafApsCtx.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* 以下消息可维可测[0x0800, 0x0899] */
enum TAF_PS_APS_MNTN_MSG_ID_ENUM
{
    ID_MSG_TAF_PS_APS_MNTN_DFS_INFO                         = TAF_PS_MSG_ID_BASE + 0x0800,  /* _H2ASN_MsgChoice TAF_APS_MNTN_DFS_INFO_STRU */

    ID_MSG_TAF_PS_CDATA_EPDSZID_CHANGED                     = TAF_PS_MSG_ID_BASE + 0x0801,  /* _H2ASN_MsgChoice TAF_APS_EPDSZID_INFO_STRU */

    ID_MSG_TAF_PS_APS_FSM_INFO                              = TAF_PS_MSG_ID_BASE + 0x0802,  /* _H2ASN_MsgChoice TAF_APS_FSM_MNTN_INFO_STRU*/

    ID_MSG_TAF_PS_APS_PDP_ENTITY                            = TAF_PS_MSG_ID_BASE + 0x0803,  /* _H2ASN_MsgChoice TAF_APS_PDP_ENTITY_STRU*/

    ID_MSG_TAF_APS_LOG_READ_NV_INFO_IND                     = TAF_PS_MSG_ID_BASE + 0x0804,  /* _H2ASN_MsgChoice TAF_APS_LOG_READ_NV_INFO_IND_STRU*/

    ID_MSG_TAF_PS_OLD_NEW_PDP_RATTYPE_INFO                  = TAF_PS_MSG_ID_BASE + 0x0805,  /* _H2ASN_MsgChoice TAF_APS_OLD_NEW_PDP_RATTYPE_INFO_STRU*/

    ID_MSG_TAF_PS_MNTN_BUTT

};
typedef VOS_UINT32 TAF_PS_APS_MNTN_MSG_ID_ENUM_UINT32;


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
/*****************************************************************************
 结构名    : TAF_APS_MNTN_DFS_INFO_STRU
 结构说明  : DDR调频信息可维可测勾包结构
 1.日    期   : 2013年12月17日
   作    者   : f00179208
   修改内容   : 新建结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          enMsgId;            /* 消息类型     */  /* _H2ASN_Skip */
    TAF_APS_SWITCH_DDR_RATE_INFO_STRU   stDfsInfo;
}TAF_APS_MNTN_DFS_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_APS_EPDSZID_INFO_STRU
 结构说明  : EPDSZID信息可维可测勾包结构
 1.日    期   : 2015年01月17日
   作    者   : y00213812
   修改内容   : 新建结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          enMsgId;            /* 消息类型     */  /* _H2ASN_Skip */
    TAF_APS_CDATA_EPDSZID_CTX_STRU      stEpdszidInfo;
}TAF_APS_EPDSZID_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_APS_FSM_STATUS_INFO_STRU
 结构说明  : EPDSZID信息可维可测勾包结构
 1.日    期   : 2015年03月27日
   作    者   : y00213812
   修改内容   : 新建结构
*****************************************************************************/
typedef struct
{
    /* 状态机标识 */
    TAF_APS_FSM_ID_ENUM_UINT32          enFsmId;

    /* 状态 */
    VOS_UINT32                          ulState;

}TAF_APS_FSM_STATUS_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_APS_FSM_MNTN_INFO_STRU
 结构说明  : FSM_MNTN_INFO信息可维可测勾包结构
 1.日    期   : 2015年03月27日
   作    者   : y00213812
   修改内容   : 新建结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          enMsgId;            /* 消息类型     */  /* _H2ASN_Skip */

    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucSuspendStatus;
    VOS_UINT8                           ucAllowDefPdnTeardownFlg;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulExist1XService;                       /* 记录是否存在1X的数据服务 */
    VOS_UINT32                          ulClDelaySearch;                       /* CL模式下记录是否完成DO和LTE的搜网 */
    VOS_UINT32                          ulIsHrpdDisabled;

    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType;

    /* 处理前状态机状态 */
    TAF_APS_FSM_STATUS_INFO_STRU        stPriFsmInfo;

    /* 处理后状态机状态 */
    TAF_APS_FSM_STATUS_INFO_STRU        stCurrFsmInfo;

}TAF_APS_FSM_MNTN_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_APS_PDP_ENTITY_STRU
 结构说明  : PDP_ENTITY信息可维可测勾包结构
 1.日    期   : 2015年03月27日
   作    者   : y00213812
   修改内容   : 新建结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                                              enMsgId;            /* 消息类型     */  /* _H2ASN_Skip */

    VOS_UINT8                                               ucPdpId;
    VOS_UINT8                                               ucRabId;
    VOS_UINT8                                               ucLinkedNsapi;      /*主激活的NSAPI,若激活类型是二次激活,则此成员有效*/
    VOS_UINT8                                               ucDoQuickAcqProtect;

    TAF_APS_CDATA_AIR_LINK_STATUS_ENUM_UINT8                enAirLinkStatus;
    APS_PDP_ACT_TYPE_ENUM_UINT8                             enActType;            /*激活类型*/
    VOS_UINT8                                               aucReserved[2];

    TAF_APS_RAT_TYPE_ENUM_UINT32                            enCurrCdataServiceMode;
    TAF_APS_CLIENT_INFO_STRU                                stClientInfo;
    APS_PDP_ADDR_ST                                         PdpAddr;

}TAF_APS_PDP_ENTITY_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_PS_APS_MNTN_MSG_ID_ENUM_UINT32      enMsgId;                            /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT16                              enNvItem;
    VOS_UINT16                              usNvDataLength;
    VOS_UINT8                               aucNvInfo[4];/* NV内容 */
}TAF_APS_LOG_READ_NV_INFO_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_PS_APS_MNTN_MSG_ID_ENUM_UINT32      enMsgId;                            /* 消息ID */    /* _H2ASN_Skip */
    TAF_APS_RAT_TYPE_ENUM_UINT32            enOldRatType;                       /* 数据接入技术 */
    TAF_APS_RAT_TYPE_ENUM_UINT32            enNewRatType;                       /* 新的数据接入技术 */

}TAF_APS_OLD_NEW_PDP_RATTYPE_INFO_STRU;

/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    TAF_PS_APS_MNTN_MSG_ID_ENUM_UINT32  ulMsgId;                                /*_H2ASN_MsgChoice_Export TAF_PS_APS_MNTN_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_PS_APS_MNTN_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_APS_MNTN_REQ;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    TAF_APS_MNTN_REQ                    stMsgReq;
}TafApsMntn_MSG;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_VOID DIAG_TraceReport(VOS_VOID *pMsg);

VOS_VOID  TAF_APS_TraceSyncMsg(
    VOS_UINT32                          ulMsgId,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulLength
);

VOS_VOID  TAF_APS_TraceApsEvt(
    VOS_UINT32                          ulEvtId,
    VOS_UINT32                          ulLength,
    VOS_UINT8                          *pucData
);

VOS_VOID  TAF_APS_TraceTimer(
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus,
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT32                          ulPara
);

VOS_VOID TAF_APS_TraceEpdszidInfo(VOS_VOID);


VOS_VOID  TAF_APS_LogPdpEntityInfo(
    VOS_UINT8                           ucPdpId
);

VOS_VOID  TAF_APS_LogFsmMntnInfo(
    TAF_APS_FSM_STATUS_INFO_STRU       *pstPriFsmInfo,
    TAF_APS_FSM_STATUS_INFO_STRU       *pstCurrFsmInfo
);


VOS_VOID  TAF_APS_SndOmDfsInfo(TAF_APS_SWITCH_DDR_RATE_INFO_STRU *pstSwitchDdrInfo);

VOS_VOID TAF_APS_LogReadNVInfo(
    VOS_UINT16                              enNvItem,
    VOS_UINT16                              usNvDataLength,
    VOS_UINT32                              ulPid,
    VOS_UINT8                              *pucData
);

VOS_VOID  TAF_APS_LogOldNewPdpRatType(
    TAF_APS_RAT_TYPE_ENUM_UINT32            enNewRatType,
    TAF_APS_RAT_TYPE_ENUM_UINT32            enOldRatType
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

#endif /* end of TafApsMntn.h */

