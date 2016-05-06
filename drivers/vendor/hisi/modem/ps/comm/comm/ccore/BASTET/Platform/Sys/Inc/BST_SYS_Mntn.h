/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_SYS_Mntn.h
  版 本 号   : 初稿
  作    者   : s00211350
  生成日期   : 2014年09月16日
  最近修改   :
  功能描述   : Bastet可维可测私有定义接口
  函数列表   :

  修改历史   :
  1.日    期   : 2014年09月16日
    作    者   : s00211350
    修改内容   : 创建文件

******************************************************************************/

#ifndef __BST_SYSMNTN_H__
#define __BST_SYSMNTN_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_OS_Timer.h"
#include "BST_Typedefine.h"
#include "BST_LIB_List.h"
#include "OmBastetInterface.h"


#if (BST_OS_VER != BST_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*获取APP信息表头*/
#define BST_SYS_MNTN_GetAppListHead()       ( &g_stBstMntnEntity.stAppList )
/*获取当前加载的APP数量（含main_task）*/
#define BST_SYS_MNTN_GetAppNumber()         ( g_stBstMntnEntity.stAppList.count )
/*获取上报TIMER_ID*/
#define BST_SYS_MNTN_GetTimerId()           ( g_stBstMntnEntity.stReportTimer )
/*获取当前本地IP地址内容*/
#define BST_SYS_MNTN_GetLocalIpHead()       ( &g_stBstMntnEntity.aucLocalIp[0] )
/*查看上一次3秒内，是否有mntn内容被操作*/
#define BST_SYS_MNTN_IsMntnMsgChanged()     ( BST_TRUE == g_stBstMntnEntity.ucChanged )
/*获取MNTN系统是否被初始化信息*/
#define BST_SYS_MNTN_IsMntnInited()         ( BST_TRUE == g_stBstMntnEntity.ucIsInit )
/*设置操作标识*/
#define BST_SYS_MNTN_SetMntnMsgChgFlag()    ( g_stBstMntnEntity.ucChanged = BST_TRUE )
/*清楚操作标识*/
#define BST_SYS_MNTN_ClrMntnMsgChgFlag()    ( g_stBstMntnEntity.ucChanged = BST_FALSE)
/*无操作上报周期*/
#define BST_SYS_MNTN_REPORT_TIMER_LEN       ( 3000U )
/*消息头长度*/
#define BST_OM_HEADER_LEN                   ( 4U )
/*最大承载APP数量，maintask也算一份*/
#define BST_SYS_MNTN_MAX_APP_NUMBER         ( BST_MAX_APP_NUMBER+1)
/*最大流量值，防止累加溢出*/
#define BST_SYS_MNTN_MAX_TRAFFIC_FLOW       ( 0x7FFFFFFF )

/*可维可测消息包内存分配*/
#define BST_ALLOC_MSG(ulSndPid, pSndMsg,ulMsgLen)\
        {\
            pSndMsg = (BST_VOID *)PS_ALLOC_MSG(ulSndPid, ((ulMsgLen) - VOS_MSG_HEAD_LENGTH ));\
            if (BST_NULL_PTR != (pSndMsg))\
            {\
                PS_MEM_SET((BST_UINT8 *)pSndMsg, 0, ulMsgLen);\
                ((MsgBlock *)pSndMsg)->ulLength = (ulMsgLen) - VOS_MSG_HEAD_LENGTH;\
            }\
        }

/*可维可测消息包内存释放*/
#define BST_FREE_MSG(ulPid, pMsg)             PS_FREE_MSG( ulPid, (pMsg) )
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/

/*****************************************************************************
  5 STRUCT定义
*****************************************************************************/
/*****************************************************************************
 结构名    : BST_SYS_MNTN_ENTITY_STRU
 结构说明  : 
*****************************************************************************/
typedef struct
{
    LIST                                stAppList;                      /*应用数据链表*/
    BST_OS_TIMERID_T                    stReportTimer;                  /*无操作超时触发定时器*/
    BST_UINT8                           aucLocalIp[OM_BST_IP_ADDR_LEN]; /*当前本地IP地址*/
    BST_UINT8                           ucChanged;                      /*操作标识*/
    BST_UINT8                           ucIsInit;                       /*操作标识*/
    BST_UINT8                           aucReserved[2];
}BST_SYS_MNTN_ENTITY_STRU;
/*****************************************************************************
 结构名    : BST_SYS_MNTN_APP_NODE_STRU
 结构说明  : 
*****************************************************************************/
typedef struct
{
    NODE                                node;
    OM_BST_APP_INFO_STRU                stAppInfo;
}BST_SYS_MNTN_APP_NODE_STRU;

/*****************************************************************************
  6 UNION定义
*****************************************************************************/


/*****************************************************************************
  7 全局变量声明
*****************************************************************************/


/*****************************************************************************
  8 函数声明
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

#if (BST_OS_VER != BST_WIN32)
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

