/******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : LinuxInterface.h
  Author      : Wangrong
  Version     :
  Date        : 2011-10-24
  Description : 该头文件包含要使用的Linux内核的头文件
  History     :
  1. Date:         2011-10-24
     Author:       Wangrong
     Modification: Create

******************************************************************************/

#ifndef __LINUXINTERFACE_H_
#define __LINUXINTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/******************************************************************************
  1 其他头文件包含
******************************************************************************/
#if (VOS_OS_VER == VOS_WIN32)
#include "LinuxStub.h"
#include "skbuff.h"
#else
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/init.h>
#include <linux/if.h>
#include <linux/kernel.h>
#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <asm-generic/errno-base.h>
#include <linux/delay.h>
#include <linux/gfp.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_arp.h>
#include <linux/netfilter_ipv4.h>
#include <linux/netfilter_ipv6.h>
#include <linux/netfilter_bridge.h>
#include <linux/fs.h>
#include <linux/wait.h>
#include <asm/uaccess.h>
#include <linux/inet.h>
#include <linux/types.h>
#include <linux/stat.h>
#include <linux/fcntl.h>
#include <linux/unistd.h>
#include <linux/signal.h>
#include <linux/time.h>
#include <linux/poll.h>
#include <linux/socket.h>
#include <linux/in.h>
#include <linux/inet.h>
#include <linux/tcp.h>
#include <linux/ip.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/rcupdate.h>
#include <linux/inetdevice.h>
#endif

/******************************************************************************
  2 宏定义
******************************************************************************/
#if (VOS_OS_VER == VOS_WIN32) || defined (__UT_CENTER__)
#define UEPS_FID_RNIC    (0)
#define ACPU_FID_NFEXT   (1)
#endif

/******************************************************************************
  3 枚举定义
******************************************************************************/


/******************************************************************************
  4 全局变量声明
******************************************************************************/


/******************************************************************************
  5 消息头定义
******************************************************************************/


/******************************************************************************
  6 消息定义
******************************************************************************/


/******************************************************************************
  7 STRUCT定义
******************************************************************************/
#pragma pack(4)



#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


/******************************************************************************
  8 UNION定义
******************************************************************************/


/******************************************************************************
  9 OTHERS定义
******************************************************************************/




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* LINUXInterface.h */






