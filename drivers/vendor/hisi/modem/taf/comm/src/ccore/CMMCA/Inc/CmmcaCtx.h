

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

typedef struct
{
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                          *pucMsgInfo;
    VOS_UINT32                          ulMsgInfoLen;
}CMMCA_CMD_BUFFER_STRU;


typedef struct
{
    VOS_UINT8                           ucIsRoamActive;
    VOS_UINT8                           aucReserved[3];
}CMMCA_USER_CFG_INFO_STRU;


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
