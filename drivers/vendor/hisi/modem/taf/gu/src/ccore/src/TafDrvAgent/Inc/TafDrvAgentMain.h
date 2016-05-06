/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafDrvAgentMain.h
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2011年10月4日
  最近修改   :
  功能描述   : DRVAGENTMain.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年10月4日
    作    者   : l60609
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DRVAGENTMAIN_H__
#define __DRVAGENTMAIN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "TafDrvAgent.h"
#include  "TafDrvAgentMsgProc.h"
#include  "PsCommonDef.h"
#include  "MnComm.h"
#include  "ScInterface.h"


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


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern VOS_UINT16  *g_pusDrvAgentUsimTempTable;         /*SIM hkadc转换表*/
extern VOS_UINT16  *g_pusDrvAgentBatTempTable;          /*Battery hkadc转换表*/
extern VOS_UINT16  *g_pusDrvAgentAdcTable;              /*PA hkadc转换表*/

/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*消息处理函数指针*/
typedef VOS_UINT32 (*DRV_AGENT_MSG_PROC_FUNC)(VOS_VOID* pMsg);

/*****************************************************************************
 结构名    : DRV_AGENT_MSG_PROC_STRU
 结构说明  : 消息与对应处理函数的结构

  1.日    期   : 2011年10月29日
    作    者   : 鲁琳/l60609
    修改内容   : AT Project：定义DRV AGENT消息与对应处理函数的结构
*****************************************************************************/
typedef struct
{
    DRV_AGENT_MSG_TYPE_ENUM_UINT32      ulMsgType;
    DRV_AGENT_MSG_PROC_FUNC             pMsgProcFunc;
}DRV_AGENT_MSG_PROC_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_UINT32  DRVAGENT_Init(enum VOS_INIT_PHASE_DEFINE  ip);

VOS_VOID  DRVAGENT_DispatchMsg (struct MsgCB * pstMsg);

VOS_VOID DRVAGENT_ProcMsgFromAt(VOS_VOID *pMsg);

VOS_VOID DRVAGENT_ProcMsgFromSPY(VOS_VOID *pMsg);

VOS_VOID DRVAGENT_SendMsg(
    VOS_UINT32                          ulRcvPid,
    VOS_UINT32                          ulMsgId,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pData
);
VOS_UINT8* DRVAGENT_GetSystemAppConfigAddr(VOS_VOID);

VOS_UINT32 DRVAGENT_TempReadInit(VOS_VOID);

DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32 DRVAGENT_ConvertScErr(
    SC_ERROR_CODE_ENUM_UINT32           enErrCode
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

#endif /* end of TafDrvAgentMain.h */
