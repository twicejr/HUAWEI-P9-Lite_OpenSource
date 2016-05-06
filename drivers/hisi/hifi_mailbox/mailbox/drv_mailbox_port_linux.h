/******************************************************************************

			  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
文 件 名   : drv_mailbox_port_linux.h
版 本 号   : 初稿
作	  者   : 莫南 00176101
生成日期   : 2012年9月24日
最近修改   :
功能描述   : mailbox C核  linux平台系统实现适配头文件
函数列表   :

修改历史   :
1.日	期	 : 2012年9月24日
作	  者   : 莫南 00176101
修改内容   : 创建文件

******************************************************************************/
#ifndef _DRV_MAILBOX_PORT_LINUX_H_
#define _DRV_MAILBOX_PORT_LINUX_H_


/*****************************************************************************
1 头文件包含
*****************************************************************************/
#include <linux/kernel.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*虚实地址转换接口定义*/
#if 0
#ifndef _DRV_LLT_
#include <mach/hardware.h>

/*ACPU实地址向虚拟地址映射的转换接口*/
#define MEM_CORE_SHARE_PHY2VIRT(phy)		 (((unsigned int)phy) - IPC_SHARE_MEM_ADDR + IPC_SHARE_MEM_VIRT_ADDR)
#define MEM_CORE_SHARE_VIRT2PHY(virt)		 (((unsigned int)virt) - IPC_SHARE_MEM_VIRT_ADDR + IPC_SHARE_MEM_ADDR)

#else

/*ACPU实地址向虚拟地址映射的转换接口*/
#define MEM_CORE_SHARE_PHY2VIRT(phy)		 (phy)
#define MEM_CORE_SHARE_VIRT2PHY(virt)		 (virt)
#endif
#endif

/*目前k3还未做预留虚拟地址空间的预映射，在init函数中再做映射*/
#define MEM_CORE_SHARE_PHY2VIRT(phy)		 (phy)
#define MEM_CORE_SHARE_VIRT2PHY(virt)		 (virt)


/*邮箱通道，功能，核等相关配置接口定义*/
/*表明此CPU的ID*/
#define MAILBOX_LOCAL_CPUID 						MAILBOX_CPUID_ACPU

/*定义C核平台相关的 邮箱通道 总数，关心收发通道 */
#define MAILBOX_CHANNEL_NUM \
( MAILBOX_CHANNEL_BUTT(ACPU, HIFI)	 \
+ MAILBOX_CHANNEL_BUTT(HIFI, ACPU)	 \
)

/*定义C核平台相关的 邮件 总数 , 只关心接收通道*/
#define MAILBOX_USER_NUM	\
( MAILBOX_USER_BUTT(HIFI, ACPU, MSG) \
)

/*打印输出相关配置定义*/
/*控制台打印输出接口*/
#ifdef _DRV_LLT_
#define mailbox_out(p)								(printk p)
#else
#define mailbox_out(p)								(printk p)
#endif

/*定义宏控制是否打印行数*/
#define _MAILBOX_LINE_								__LINE__

/*定义宏控制是否打印文件名,(不打印文件名可节省代码空间)*/
#define _MAILBOX_FILE_								(void*)(0) /*__FILE__*/

#define MAILBOX_LOG_LEVEL							MAILBOX_LOG_ERROR


/*邮箱调试功能相关配置定义*/
/*表明在此CPU上打开可维可测功能*/
#ifndef MAILBOX_OPEN_MNTN
#define MAILBOX_OPEN_MNTN
#endif

/*可维可测记录的最大传送ID数*/
#define MAILBOX_RECORD_USEID_NUM					(64)

#define RT	"\n"   /*打印回车符号*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif	/*_DRV_MAILBOX_LINUX_H_*/

