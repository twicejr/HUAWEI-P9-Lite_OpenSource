/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : GmmCasGlobal.h
  Author      : Roger Leo
  Version     : V200R001
  Date        : 2005-08-25
  Description : 定义了GMM模块公共接入层全局共享的数据结构
  History     :
  1. Date:2005-08-25
     Author: Roger Leo
     Modification:update
  2.日    期   : 2006年08月09日
    作    者   : 蒋丽萍j60010247
    修改内容   : 问题单A32D03479，在PC机上实现时将#pragma pack(0)和#pragma pack()加编译开关
  3.日    期   : 2007年05月15日
    作    者   : luojian id:60022475
    修改内容   : 问题单号：A32D10978
************************************************************************/

#ifndef _GMM_CAS_GLOBAL_H_
#define _GMM_CAS_GLOBAL_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "GmmCasDef.h"


#pragma pack(4)         /* 1字节对齐，数据结构定义保证4字节对齐 */
                        /* 放在include后，不影响其他头文件的pack参数 */
/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 打印输出级别定义 */
#define GMM_PRINT_INFO                      PS_LOG_LEVEL_INFO
#define GMM_PRINT_NORMAL                    PS_LOG_LEVEL_NORMAL
#define GMM_PRINT_WARNING                   PS_LOG_LEVEL_WARNING
#define GMM_PRINT_ERROR                     PS_LOG_LEVEL_ERROR

/* Modified by L00171473 for V7R1 porting, 2011-04-23, begin, 避免重定义WARNING */

/* 打印输出宏定义 */
#ifndef SUBMOD_NULL
#define SUBMOD_NULL                         0
#endif


#define GMM_LOG_INFO(String)      \
            PS_NAS_LOG(WUEPS_PID_GMM, SUBMOD_NULL, GMM_PRINT_INFO, String)
#define GMM_LOG_NORM(String)      \
            PS_NAS_LOG(WUEPS_PID_GMM, SUBMOD_NULL, GMM_PRINT_NORMAL, String)
#define GMM_LOG_WARN(String)      \
            PS_NAS_LOG(WUEPS_PID_GMM, SUBMOD_NULL, GMM_PRINT_WARNING, String)
#define GMM_LOG_ERR(String)       \
            PS_NAS_LOG(WUEPS_PID_GMM, SUBMOD_NULL, GMM_PRINT_ERROR, String)


/*******************************************************************************
  3 枚举定义
*******************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
/* 指针＋全局标识＋类型＋模块名＋意义描述 */
/* GMM内部公用的全局变量声明 */
extern GMM_CAS_CTRL_STRU        gstGmmCasGlobalCtrl;        /* GMM CAS全局控制结构变量 */
extern GMM_CAS_MSG_BUFFER_STRU  gstGmmCasMsgBuf;            /* 挂起消息缓存链表 */

/*extern VOS_UINT8                gaucGmmNasMsgTmp[GMM_NAS_MSG_DATA_MAX];*/          /* 传递NAS消息的临时数据区 */
/*extern VOS_UINT8                gaucGmmLlcDataReq[GMM_LLC_MSG_PDULEN_MAX];*/      /* 向LLC发送data req的消息数据内容 */
/*extern const GMM_CELL_FUN_TYPE* apfGmmCasStateTable[GMM_MATRIX_EVENT_MAX];*/


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
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of GmmCasGlobal.h*/
