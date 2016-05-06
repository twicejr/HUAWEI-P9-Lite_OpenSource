

#ifndef __ATCMDCAGPSPROC_H__
#define __ATCMDCAGPSPROC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "AtCtx.h"
#include "AtParse.h"
#include "ATCmdProc.h"
#include "AtXpdsInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define AT_XPDS_AGPS_DATAUPLEN_MAX      (240)

#define AT_AGPS_EPH_INFO_MAX_SEG_NUM                        ( 5 )
#define AT_AGPS_EPH_INFO_FIRST_SEG_STR_LEN                  ( 8 )
#define AT_AGPS_EPH_INFO_NOT_FIRST_SEG_STR_LEN              ( 960 )

#define AT_AGPS_ALM_INFO_MAX_SEG_NUM                        ( 3 )
#define AT_AGPS_ALM_INFO_FIRST_SEG_STR_LEN                  ( 8 )
#define AT_AGPS_ALM_INFO_NOT_FIRST_SEG_STR_LEN              ( 896 )


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

/*****************************************************************************
 结构名    : AT_CAGPS_CMD_NAME_TLB_STRU
 结构说明  : 回复的AT命令名字

  1.日    期   : 2015年7月27日
    作    者   : g00256031
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    AT_XPDS_MSG_TYPE_ENUM_UINT32        enMsgType;
    VOS_UINT32                          ulReserved;
    VOS_CHAR                           *pcATCmd;
}AT_CAGPS_CMD_NAME_TLB_STRU;

/*****************************************************************************
 结构名    : AT_CAGPS_CMD_OPT_TLB_STRU
 结构说明  : 回复的AT操作名

  1.日    期   : 2015年7月27日
    作    者   : g00256031
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    AT_XPDS_MSG_TYPE_ENUM_UINT32        enMsgType;
    AT_CMD_CURRENT_OPT_ENUM             enCmdOpt;
}AT_CAGPS_CMD_OPT_TLB_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

extern VOS_UINT32 At_SetAgpsDataCallStatus(
    VOS_UINT8                               ucIndex
);

extern VOS_UINT32 At_SetAgpsUpBindStatus(
    VOS_UINT8                               ucIndex
);

extern VOS_UINT32 At_SetAgpsForwardData(
    VOS_UINT8                               ucIndex
);

extern VOS_UINT32 AT_RcvXpdsAgpsDataCallReq(
    VOS_VOID                            *pstMsg
);

extern VOS_UINT32 AT_RcvXpdsAgpsServerBindReq(
    VOS_VOID                            *pstMsg
);

extern VOS_UINT32 AT_RcvXpdsAgpsReverseDataInd(
    VOS_VOID                            *pstMsg
);

extern VOS_UINT32 AT_CagpsSndXpdsReq(
    VOS_UINT8                           ucIndex,
    AT_XPDS_MSG_TYPE_ENUM_UINT32        enMsgType,
    VOS_UINT32                          ulMsgStructSize
);

extern VOS_UINT32 AT_SetCagpsCfgPosMode(
    VOS_UINT8                           ucIndex
);

extern VOS_UINT32 AT_SetCagpsStart(
    VOS_UINT8                           ucIndex
);

extern VOS_UINT32 AT_SetCagpsStop(
    VOS_UINT8                           ucIndex
);

extern VOS_UINT32 AT_SetCagpsCfgMpcAddr(
    VOS_UINT8                           ucIndex
);

extern VOS_UINT32 AT_SetCagpsCfgPdeAddr(
    VOS_UINT8                           ucIndex
);

extern VOS_UINT32 AT_SetCagpsQryRefloc(
    VOS_UINT8                           ucIndex
);

extern VOS_UINT32 AT_SetCagpsQryTime(
    VOS_UINT8                           ucIndex
);

extern VOS_UINT32 AT_SetCagpsPrmInfo(
    VOS_UINT8                           ucIndex
);

extern VOS_UINT32 AT_SetCagpsReplyNiReq(
    VOS_UINT8                           ucIndex
);

extern VOS_UINT32 At_SetCagpsPosInfo(
    VOS_UINT8                           ucIndex
);

extern VOS_CHAR* AT_SearchCagpsATCmd(
    AT_XPDS_MSG_TYPE_ENUM_UINT32        enMsgType
);

extern VOS_UINT32 AT_RcvXpdsCagpsCnf(
    VOS_VOID                           *pMsg
);

AT_CMD_CURRENT_OPT_ENUM AT_SearchCagpsATCmdOpt(
    AT_XPDS_MSG_TYPE_ENUM_UINT32        enMsgType
);

extern VOS_UINT32 AT_RcvXpdsCagpsRlstCnf(
    VOS_VOID                           *pMsg
);

VOS_UINT32 AT_RcvXpdsEphInfoInd(
    VOS_VOID                           *pstMsg
);

VOS_UINT32 AT_RcvXpdsAlmInfoInd(
    VOS_VOID                           *pstMsg
);

extern VOS_UINT32 At_SetCgpsControlStart(
    VOS_UINT8                           ucIndex
);

extern VOS_UINT32 At_SetCgpsControlStop(
    VOS_UINT8                           ucIndex
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

#endif
