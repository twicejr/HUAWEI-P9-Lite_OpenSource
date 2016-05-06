/******************************************************************************

			  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
文 件 名	 : drv_mailbox_platform.h
版 本 号	 : 初稿
作	者	 : 莫南 00176101
生成日期	 : 2012年9月24日
最近修改	 :
功能描述	 : mailbox 各平台平台系统适配接口公共头文件
函数列表	 :

修改历史	 :
1.日	  期   : 2012年9月24日
作	  者   : 莫南 00176101
修改内容   : 创建文件

******************************************************************************/
#ifndef _DRV_MAILBOX_PLATFORM_H_
#define _DRV_MAILBOX_PLATFORM_H_

/*****************************************************************************
1 头文件包含
*****************************************************************************/
#if defined(BSP_CORE_MODEM) /*C核的系统适配头文件*/
#include "drv_mailbox_port_vxworks.h"

#elif defined (BSP_CORE_APP) /*A核的系统适配头文件*/
#include "drv_mailbox_port_linux.h"

#elif defined (BSP_CORE_CM3)  /*M核的系统适配头文件*/
#include "drv_mailbox_port_mcu.h"

#endif
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#ifndef MAILBOX_TRUE
#define MAILBOX_TRUE								(1)
#endif

#ifndef MAILBOX_FALSE
#define MAILBOX_FALSE								(0)
#endif

#ifndef MAILBOX_NULL
#define MAILBOX_NULL								(void*)(0)
#endif

/*邮箱接口类型定义*/
#ifdef _DRV_LLT_
#define MAILBOX_LOCAL											/*文件内部调用接口(PC工程)*/
#else
#ifndef MAILBOX_LOCAL
#define MAILBOX_LOCAL								static		/*文件内部调用接口(单板)*/
#endif
#endif

#ifndef MAILBOX_EXTERN
#define MAILBOX_EXTERN											/*模块内部调用接口*/
#endif

#ifndef MAILBOX_GLOBAL
#define MAILBOX_GLOBAL											/*本模块提供给外部的功能接口*/
#endif

/*定义邮箱通道数组数目及方向*/
#define MIALBOX_DIRECTION_INVALID					(0) 			/*表示通道方向无效*/
#define MIALBOX_DIRECTION_SEND						(1) 			/*表示当前核发送给其他核的通道*/
#define MIALBOX_DIRECTION_RECEIVE					(2) 			/*表示其他核发送给当前核的通道*/

/*无效邮件号*/
#define  MAILBOX_MAILCODE_INVALID					(unsigned long)(0xffffffff)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 实 体 名  : MAILBOX_DELAY_SCENE_E
 功能描述  : 传入给平台层延迟函数的场景号。
*****************************************************************************/
enum MAILBOX_DELAY_SCENE_E
{
	MAILBOX_DELAY_SCENE_MSG_FULL ,			/*发送msg邮件时，邮箱满场景的延时等待号*/
	MAILBOX_DELAY_SCENE_IFC_FULL			/*发送ifc邮件时，邮箱满场景的延时等待号*/
};

/*****************************************************************************
  4 消息头定义
*****************************************************************************/

/*****************************************************************************
  5 消息定义
*****************************************************************************/

/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/

/*****************************************************************************
  7 UNION定义
*****************************************************************************/

/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  9 全局变量声明
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
/*邮箱内部文件之间调用的接口*/
extern MAILBOX_EXTERN void  mailbox_assert(unsigned int ErroNo);

extern MAILBOX_EXTERN int mailbox_mutex_lock(void **mutexId);

extern MAILBOX_EXTERN void mailbox_mutex_unlock(void **mutexId);

extern MAILBOX_EXTERN int mailbox_int_context(void);

extern MAILBOX_EXTERN int mailbox_get_timestamp(void);

extern MAILBOX_EXTERN int mailbox_process_register(
                unsigned int channel_id, 
                 int (*cb)(unsigned int channel_id),
                 void *priv);

extern MAILBOX_EXTERN int mailbox_channel_register(
                unsigned int ChannelID, 
                unsigned int IntNum,
                unsigned int DstID,
                unsigned int Direct,
                void   **mutex);

extern MAILBOX_EXTERN void *mailbox_memcpy(void *dst, const void *src, unsigned int size);

extern MAILBOX_EXTERN void *mailbox_memset(void * m, int c, unsigned int size);

extern MAILBOX_EXTERN int mailbox_delivery(unsigned int channel_id);

extern MAILBOX_EXTERN int mailbox_init_platform(void);

extern MAILBOX_EXTERN int mailbox_scene_delay(
                unsigned int scene_id,
                int *try_times);

extern MAILBOX_EXTERN void *mailbox_init_completion(void);

extern MAILBOX_EXTERN int mailbox_wait_completion(void **mutexId, unsigned int timeout);

extern MAILBOX_EXTERN void mailbox_complete(void **wait_id);

extern MAILBOX_EXTERN void mailbox_del_completion(void **wait);
extern void mailbox_ifc_test_init(void);

#if defined (BSP_CORE_CM3)
extern void mailbox_dpm_device_get(void);
extern void mailbox_dpm_device_put(void);
#else
#define mailbox_dpm_device_get()
#define mailbox_dpm_device_put()
#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif	/*_DRV_MAILBOX_PLATFORM_H_*/

