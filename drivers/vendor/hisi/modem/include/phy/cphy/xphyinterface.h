/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : xphyinterface.h
  版 本 号   : 初稿
  作    者   : honghuiyong(164941)
  生成日期   : 2015年6月13日
  最近修改   :
  功能描述   : 定义邮箱，BBP基地址等。针对ARM和TENSILICA访问同一个地方，看到的
            地址不一样进行处理，例如协议栈和DSP都要访问同一邮箱，但其基地址在
            ARM侧和TENSILCA侧看到的并不一样，通过本文件定义为同一的宏，大家使用
            相同的名字即可。

  函数列表   :
  修改历史   :
******************************************************************************/
#ifndef __XPHY_INTERFACE_H__
#define __XPHY_INTERFACE_H__

#include "uphy_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#define SHARE_MAILBOX_SIZE                          (0x4800)
#define XPHY_MAILBOX_BASE_ADDR                      (g_aucMailboxBuf)

/* 共享邮箱大小定义*/
#define XPHY_MAILBOX_LHPA_UP_SIZE                   (0x00002000UL)  /*8K字节，PS上行邮箱大小*/
#define XPHY_MAILBOX_LHPA_DOWN_SIZE                 (0x00002000UL)  /*8k字节，PS下行邮箱大小*/
#define XPHY_MAILBOX_OM_DOWN_SIZE                   (0x00000800UL)  /*2k字节，OM下行邮箱大小*/


#define XPHY_MAILBOX_LHPA_UP_BASE_ADDR              (XPHY_MAILBOX_BASE_ADDR)
#define XPHY_MAILBOX_LHPA_DOWN_BASE_ADDR            (XPHY_MAILBOX_LHPA_UP_BASE_ADDR + XPHY_MAILBOX_LHPA_UP_SIZE)
#define XPHY_MAILBOX_OM_DOWN_BASE_ADDR              (XPHY_MAILBOX_LHPA_DOWN_BASE_ADDR + XPHY_MAILBOX_LHPA_DOWN_SIZE)

extern UINT8 g_aucMailboxBuf[SHARE_MAILBOX_SIZE];
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif /* __MEM_MAP_BASE_H__ */
