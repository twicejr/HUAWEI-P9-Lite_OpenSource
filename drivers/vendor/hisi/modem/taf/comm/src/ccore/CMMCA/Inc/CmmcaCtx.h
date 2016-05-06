/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CmmcaCtx.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2014年1月8日
  最近修改   :
  功能描述   : CmmcaCtx.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年1月8日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CMMCACTX_H__
#define __CMMCACTX_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"

#include "TafAppMma.h"
#include "CmmcaCtxPkt.h"
#include "CmmcaTimerMgmt.h"
#include "CmmcaMntn.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#if (FEATURE_ON == FEATURE_CL_INTERWORK)

#define CMMCA_OPID_INVILID_VALUE                            (0xFF)
#define CMMCA_OPID_MIN_VALUE                                (1)
#define CMMCA_OPID_MAX_VALUE                                (200)

/* CMMCA 上下文地址 */
#define CMMCA_GetCtxAddr()                                  (&g_stCmmcaCtx)

/* 获取当前的OPID */
#define CMMCA_GetCurMaxOpid()                               (CMMCA_GetCtxAddr()->ucCurMaxOpid)

/* 设置当前的OPID */
#define CMMCA_SetCurMaxOpid(ucCurMaxOpid)                   (CMMCA_GetCurMaxOpid() = (ucCurMaxOpid))

/* 获取当前Modem的状态 */
#define CMMCA_GetModemStatus()                              (CMMCA_GetCtxAddr()->enModemStatus)

/* 设置当前Modem的状态 */
#define CMMCA_SetModemStatus(enModemStatus)                 (CMMCA_GetModemStatus() = (enModemStatus))

/* 等待消息结果的队列长度 */
#define CMMCA_MAX_CMD_BUFFER_QUEUE_SIZE                     (5)

/* CMMCA收发的消息结构中，数据临时长度 */
#define CMMCA_MSG_DATA_RSV_LEN                              (4)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名   :CMMCA_MODEM_STATUS_ENUM_UINT8
 枚举说明 :CMMCA维护的modem状态
 1.日    期   : 2014年03月20日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_MODEM_STATUS_ENUM
{
    CMMCA_MODEM_STATUS_INACTIVE,                                                /* Modem状态处于关机或Power Save状态或L重选到C */
    CMMCA_MODEM_STATUS_ACTIVE,                                                  /* Modem处于正在搜网注册或已经注册状态 */
    CMMCA_MODEM_STATUS_BUTT
};
typedef VOS_UINT8 CMMCA_MODEM_STATUS_ENUM_UINT8;

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
 结构名    : CMMCA_CMD_BUFFER_STRU
 结构说明  : 缓存命令的信息结构
 1.日    期   : 2014年01月27日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                          *pucMsgInfo;
    VOS_UINT32                          ulMsgInfoLen;
}CMMCA_CMD_BUFFER_STRU;

/*****************************************************************************
 结构名    : CMMCA_USER_CFG_INFO_STRU
 结构说明  : 用户配置上下文的信息结构
 1.日    期   : 2014年03月7日
   作    者   : w00167002
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsRoamActive;
    VOS_UINT8                           aucReserved[3];
}CMMCA_USER_CFG_INFO_STRU;

/*****************************************************************************
 结构名    : CMMCA_REG_CTX_STRU
 结构说明  : Reg上下文的信息结构
 1.日    期   : 2014年01月27日
   作    者   : s00246516
   修改内容   : 新建
 2.日    期   : 2015年7月20日
   作    者   : w000316404
   修改内容   : R11协议升级(LTE频点配置值扩展)
*****************************************************************************/
typedef struct
{
    TAF_PHONE_SERVICE_STATUS                                ucCsSrvSta;         /*CS服务状态*/
    TAF_PHONE_SERVICE_STATUS                                ucPsSrvSta;         /*PS服务状态*/
    VOS_UINT8                                               ucCsSimValid;       /* CS卡是否有效，VOS_TRUE:有效，VOS_FALSE:无效 */
    VOS_UINT8                                               ucPsSimValid;       /* PS卡是否有效，VOS_TRUE:有效，VOS_FALSE:无效 */
    TAF_PLMN_ID_STRU                                        stPlmnId;
    VOS_UINT32                                              ulArfcn;
    TAF_MMA_PLMN_PRIORITY_CLASS_ENUM_UINT8                  enPrioClass;
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8                       enSrvDomain;
    VOS_UINT8                                               aucReserve[2];
    CMMCA_USER_CFG_INFO_STRU                                stUserCfgInfo;
}CMMCA_REG_CTX_STRU;

/*****************************************************************************
 结构名    : CMMCA_CTX_STRU
 结构说明  : CMMCA的上下文
 1.日    期   : 2014年01月27日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCurMaxOpid;                           /* 当前分配出去的最大OPID */

    CMMCA_MODEM_STATUS_ENUM_UINT8       enModemStatus;

    VOS_UINT8                           aucReserved[2];

    /* CMMCA命令消息缓存 */
    CMMCA_CMD_BUFFER_STRU               astCmdBufferQueue[CMMCA_MAX_CMD_BUFFER_QUEUE_SIZE];

    /* Packet Data 相关的全局变量 */
    CMMCA_PKT_CTX_STRU                  stPktCtx;

    CMMCA_REG_CTX_STRU                  stRegCtx;

    /* CMMCA定时器上下文 */
    CMMCA_TIMER_CTX_STRU                astCmmcaTimer[CMMCA_MAX_TIMER_NUM];
}CMMCA_CTX_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
extern CMMCA_CTX_STRU                          g_stCmmcaCtx;


/*****************************************************************************
  10 函数声明
*****************************************************************************/
CMMCA_REG_CTX_STRU* CMMCA_REG_GetCtxAddr(VOS_VOID);

VOS_VOID CMMCA_REG_InitCtx(VOS_VOID);

VOS_VOID CMMCA_REG_ReadRoamCfgInfoNvim(VOS_VOID);

CMMCA_TIMER_CTX_STRU* CMMCA_GetTiCtx(VOS_VOID);

VOS_VOID CMMCA_InitCtx(VOS_VOID);

VOS_VOID CMMCA_AssignOpid(
    VOS_UINT8                          *pucOpid
);

CMMCA_CMD_BUFFER_STRU* CMMCA_GetCmdBufferQueueAddr(VOS_VOID);

VOS_VOID CMMCA_InitCmdBufferQueue(
    CMMCA_CMD_BUFFER_STRU              *pstCmdBufferQueue
);

VOS_VOID CMMCA_DelItemInCmdBufferQueue(
    VOS_UINT8                           ucOpId
);

VOS_UINT8 CMMCA_SaveItemInCmdBufferQueue(
    VOS_UINT8                           ucOpId,
    VOS_UINT8                          *pucMsgInfo,
    VOS_UINT32                          ulMsgInfoLen
);

CMMCA_CMD_BUFFER_STRU* CMMCA_GetItemFromCmdBufferQueue(
    VOS_UINT8                           ucOpId
);
#endif

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

#endif /* end of CmmcaCtx.h */
