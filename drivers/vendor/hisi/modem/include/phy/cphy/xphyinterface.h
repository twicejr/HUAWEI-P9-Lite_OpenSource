
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
