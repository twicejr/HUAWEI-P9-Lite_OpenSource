/******************************************************************************

                  版权所有 (C), 2005-2007, 华为技术有限公司


  文 件 名   : MmcRabmInterface.h
  版 本 号   : 初稿
  作    者   : liuyang id:48197
  生成日期   : 2006年5月4日
  最近修改   :
  功能描述   : MMC与RABM接口文件
  函数列表   :
      ---
      ---
      ---
  修改历史   :
  1.日    期   : 2006年5月4日
    作    者   : liuyang id:48197
    修改内容   : 创建文件
  2.日    期   : 2006年5月4日
    作    者   : ---
    修改内容   : Add function ... 问题单号:
  3.日    期  : 2006年12月4日
    作    者  : luojian id:60022475
    修改内容  : 增加 #pragma pack(4)，问题单号:A32D07779
******************************************************************************/

#ifndef _MMC_RABM_INTERFACE_H_
#define _MMC_RABM_INTERFACE_H_


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/******************************************************************************
   1 头文件包含
 *****************************************************************************/
#include "vos.h"
/*****************************************************************************
   2 内部函数原型说明
 *****************************************************************************/

/*****************************************************************************
   3 全局变量定义
 *****************************************************************************/

/*****************************************************************************
   4 模块级变量
 *****************************************************************************/

/*****************************************************************************
   5 常量定义
 *****************************************************************************/

/*****************************************************************************
   6 宏定义
 *****************************************************************************/
#pragma pack(4)
/* MMC->RABM */
#define MMCRABM_SUSPEND_IND                                   2
#define MMCRABM_RESUME_IND                                    4

/* RABM->MMC */
#define MMCRABM_SUSPEND_RSP                                   1

/***********************新增接口MMC－>RABM***************************/
/* 消息 MMCRABM_SUSPEND_IND 结构体 */
/* ucSuspendCause 取值 */
#define MMCRABM_SUSPEND_CAUSE_HANDOVER                  0x00
#define MMCRABM_SUSPEND_CAUSE_CELLRESELECT              0x01
#define MMCRABM_SUSPEND_CAUSE_CELLCHANGE                0x02

/* ucSuspendOrigen/ucResumeOrigen 取值 */
#define MMCRABM_SUSPEND_ORIGEN_GSM                      0x00
#define MMCRABM_SUSPEND_ORIGEN_WCDMA                    0x01

typedef enum
{
    MMCRABM_2G_TO_3G_ENUM = 0,
    MMCRABM_3G_TO_2G_ENUM,

    MMCRABM_SYS_CHANGE_ENUM_BUTT
}MMCRABM_SYS_CHANGE_DIR_ENUM;

typedef struct
{
    MSG_HEADER_STRU                 MsgHeader;
    MMCRABM_SYS_CHANGE_DIR_ENUM     SysChangeDir;
}MMCRABM_SUSPEND_IND_ST;


/* 消息 MMCRABM_RESUME_IND 结构体 */
/* ResumeResult 取值 */
#define MMCRABM_RESUME_RESULT_SUCCESS    0x00
#define MMCRABM_RESUME_RESULT_FAILURE    0x01
#define MMCRABM_RESUME_GPRS_SUSPENSION   0x02

/* ucResumeOrigen 取值 */
#define MMCRABM_RESUME_ORIGEN_GSM        0x00
#define MMCRABM_RESUME_ORIGEN_WCDMA      0x01

typedef enum
{
    MMCRABM_3G_ENUM = 0,
    MMCRABM_2G_ENUM
}MMCRABM_CUR_NET_ENUM;

typedef enum
{
    MMCRABM_SUCC_ENUM = 0,
    MMCRABM_FAIL_ENUM
}MMCRABM_SYS_CHANGE_RESULT_ENUM;

typedef struct
{
    MSG_HEADER_STRU                   MsgHeader;
    MMCRABM_SYS_CHANGE_DIR_ENUM       SysChangeDir;     /* 通知RABM切换状态改变方向 */
    MMCRABM_CUR_NET_ENUM              CurNet;           /* 当前RABM工作状态 */
    VOS_UINT32                        ulPsResumeResult; /* PS域切换结果 */
}MMCRABM_RESUME_IND_ST;

/***********************新增接口RABM－>MMC***************************/
/*消息 MMCRABM_SUSPEND_RSP 结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;
    VOS_UINT32              ulReserved;                     /* 保留*/
}MMCRABM_SUSPEND_RSP_ST;


/*****************************************************************************
   7 对外函数接口说明
 *****************************************************************************/

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

#endif


