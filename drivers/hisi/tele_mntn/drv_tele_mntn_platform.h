/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_tele_mntn_platform.h
  版 本 号   : 初稿
  作    者   : 李彬彬 00186593
  生成日期   : 2014年5月17日
  最近修改   :
  功能描述   : drv_tele_mntn_platform.h
  函数列表   :
  修改历史   :
  1.日    期   : 2014年5月17日
    作    者   : 李彬彬 00186593
    修改内容   : 创建文件
  2.注    意   : 如下几个文件夹 .c .h 内容必须完全相同
                 vendor\hisi\confidential\lpmcu\driver\tele_mntn\
                 kernel\drivers\hisi\tele_mntn\

******************************************************************************/

#ifndef __DRV_TELE_MNTN_PLATFORM_H__
#define __DRV_TELE_MNTN_PLATFORM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#if defined(BSP_CORE_MODEM) || defined(__OS_VXWORKS__)||defined(__OS_RTOSCK__)
#define CONFIG_TELE_MNTN_CORE_MODEM
#elif defined(BSP_CORE_APP) || defined(__KERNEL__)
#define CONFIG_TELE_MNTN_CORE_APP
#elif defined(BSP_CORE_CM3) || defined(__CMSIS_RTOS)
#define CONFIG_TELE_MNTN_CORE_CM3
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "drv_tele_mntn_common.h"
#if defined(CONFIG_TELE_MNTN_CORE_MODEM)
#include  <global_ddr_map.h>
#include  <string.h>
#include  <osal.h>
#include  "mntnDrv.h"
#include  "BSP_GLOBAL.h"
#include  "mdrv_ipc_comm.h"
#include  "mdrv_rtc_common.h"
#include  <soc_sctrl_interface.h>
#include  <soc_acpu_baseaddr_interface.h>
#include  <soc_rtctimerwdtv100_interface.h>
#elif defined (CONFIG_TELE_MNTN_CORE_APP)
#include  <global_ddr_map.h>
#include  <linux/string.h>
#include  <linux/kernel.h>
#include  <linux/slab.h>
#include  <linux/bitops.h>
#include  <linux/io.h>  /*writel(/arch/arm/include/asm/io.h)*/
#include  <linux/spinlock.h>
#include  <linux/hwspinlock.h>
#include  <linux/hisi/hisi_rproc.h>
#include  <soc_sctrl_interface.h>
#include  <soc_acpu_baseaddr_interface.h>
#include  <soc_rtctimerwdtv100_interface.h>
#include  <m3_rdr_ddr_map.h>
#elif defined (CONFIG_TELE_MNTN_CORE_CM3)
#include  <m3_ddr_map.h>
#include  <string.h>
#include  "hisi_lpm3.h"
#include  "common.h"
#include  "log.h"
#include  "hwspinlock.h"
#include  "ipc_msg.h"
#include  "m3_ddr_map.h"
#include  "m3_sram_map.h"
#include  <soc_sctrl_interface.h>
#include  <soc_lpmcu_baseaddr_interface.h>
#include  <dma.h>
#include  "pwc_dpm.h"
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#if defined(CONFIG_TELE_MNTN_CORE_MODEM) /*C核*/

#define TELE_MNTN_AREA_ADDR                                 (HISI_RESERVED_LPMX_CORE_PHYMEM_BASE_UNIQUE)
#define TELE_MNTN_AREA_SIZE                                 (0x80000)

#define TELE_MNTN_LOCALLOCK_INIT(lock)
#define TELE_MNTN_LOCAL_LOCK(lock, flag)                    ((flag) = (u32_t)OSAL_IntLock())
#define TELE_MNTN_LOCAL_UNLOCK(lock, flag)                  OSAL_IntUnLock((s32_t)(flag))

#define TELE_MNTN_GLOBALLOCK_INIT(lock, val)                do{lock = (val);}while(0)
#define TELE_MNTN_GLOBAL_LOCK(lock, flag, ret)              do{ret = mdrv_ipc_spin_lock(lock);}while(0)
#define TELE_MNTN_CHECK_GLOBAL_LOCK_RET(ret, cmd, out)      do{ \
                                                                if(ret) \
                                                                { \
                                                                    cmd; \
                                                                    return out; \
                                                                } \
                                                            }while(0)
#define TELE_MNTN_GLOBAL_UNLOCK(lock, flag)                 mdrv_ipc_spin_unlock(lock)

#define TELE_MNTN_IPC_INT_REGISTER(ipc_int_num, func, para) mdrv_ipc_int_connect((ipc_int_num), (func), (para))
#define TELE_MNTN_IPC_INT_SEND(target, ipc_int_num)         (void_t)mdrv_ipc_int_send((target),(ipc_int_num))

#define TELE_MNTN_PHY_TO_VIRT(addr, size)                   ((u8_t *)(addr))

#define TELE_MNTN_AXI_PHY_TO_VIRT(addr, size)               ((u8_t *)(addr))

#define TELE_MNTN_SLICE_TIME_GET()                          omTimerGet()

#define TELE_MNTN_RTC_TIME_GET()                            mdrv_rtc_get_value()

#define TELE_MNTN_TRACE_OUT(_ret, _para0)                   BSP_TRACE((BSP_LOG_LEVEL_E)BSP_LOG_LEVEL_ERROR,BSP_MODU_MNTN,"%s: ret=0x%08x, para0=0x%08x\r\n",__FUNCTION__,(u32_t)(_ret),(u32_t)(_para0))

#define TELE_MNTN_MEMSET(m, c, size)                        (void_t)memset((void_t *)(m),(s32_t)(c),(u32_t)(size))
#define TELE_MNTN_MEMCPY(d, s, size)                        (void_t)memcpy((void_t *)(d),(void_t *)(s),(u32_t)(size))

#define TELE_MNTN_WRITE_MEM(mem, local, size)               TELE_MNTN_MEMCPY(mem, local, size)
#define TELE_MNTN_READ_MEM(mem, local, size)                TELE_MNTN_MEMCPY(local, mem, size)

#define TELE_MNTN_CUR_CPUID                                 1/*IPC_CORE_CCPU*/

#define TELE_MNTN_WRITE_REG(val, addr)                      writel((u32_t)(val), (void_t *)(addr))
#define TELE_MNTN_READ_REG(addr)                            readl((void_t *)addr)
#define TELE_MNTN_SET_BIT(nr, addr)                         set_bit((u32_t)(nr), (void_t *)(addr))
#define TELE_MNTN_CLR_BIT(nr, addr)                         clr_bit((u32_t)(nr), (void_t *)(addr))

#define TELE_MNTN_DATA_SECTION

#define TELE_MNTN_CHECK_DDR_SELF_REFRESH()                  (0)

#elif defined (CONFIG_TELE_MNTN_CORE_APP) /*A核*/

#define TELE_MNTN_AREA_ADDR                                 (HISI_RESERVED_LPMX_CORE_PHYMEM_BASE_UNIQUE)
#define TELE_MNTN_AREA_SIZE                                 (0x80000)

#define TELE_MNTN_LOCALLOCK_INIT(lock)                      spin_lock_init((spinlock_t *)(lock))
#define TELE_MNTN_LOCAL_LOCK(lock, flag)                    spin_lock_irqsave((spinlock_t *)(lock), flag)
#define TELE_MNTN_LOCAL_UNLOCK(lock, flag)                  spin_unlock_irqrestore((spinlock_t *)(lock),(udy_t)(flag))

#define TELE_MNTN_GLOBALLOCK_INIT(lock, val)                do{ \
                                                                lock = (u8_t *)hwspin_lock_request_specific(val); \
                                                                if(TELE_MNTN_IS_NULL(lock)) \
                                                                    return TELE_MNTN_ERRO; \
                                                            }while(0)
#define TELE_MNTN_GLOBAL_LOCK(lock, flag, ret)              do{ret = hwspin_lock_timeout((struct hwspinlock *)(lock), TELE_MNTN_LOCK_TIMEOUT);}while(0)
#define TELE_MNTN_CHECK_GLOBAL_LOCK_RET(ret, cmd, out)      do{ \
                                                                if(ret) \
                                                                { \
                                                                    cmd; \
                                                                    return out; \
                                                                } \
                                                            }while(0)
#define TELE_MNTN_GLOBAL_UNLOCK(lock, flag)                 hwspin_unlock((struct hwspinlock *)(lock))

#define TELE_MNTN_IPC_INT_REGISTER(ipc_int_num, func, para) BSP_IPC_IntConnect((ipc_int_num), (func), (para))
#define TELE_MNTN_IPC_INT_SEND(target, ipc_int_num)         (void_t)BSP_IPC_IntSend((target),(ipc_int_num))

#define TELE_MNTN_PHY_TO_VIRT(addr, size)                   ((u8_t*)ioremap((addr),(size)))

#define TELE_MNTN_AXI_PHY_TO_VIRT(addr, size)               ((u8_t*)ioremap((addr),(size)))

#define TELE_MNTN_RTC_TIME_GET()                            get_rtc_time()

#define TELE_MNTN_SLICE_TIME_GET()                          get_slice_time()

#define TELE_MNTN_TRACE_OUT(_ret, _para0)                   printk(KERN_ERR"%s: ret=%u, para0=%u\r\n",__FUNCTION__,(u32_t)(_ret),(u32_t)(_para0))

#define TELE_MNTN_MEMSET(m, c, size)                        (void_t)memset((void_t *)(m),(s32_t)(c),(u32_t)(size))
#define TELE_MNTN_MEMCPY(d, s, size)                        (void_t)memcpy((void_t *)(d),(void_t *)(s),(u32_t)(size))

#define TELE_MNTN_WRITE_MEM(mem, local, size)               TELE_MNTN_MEMCPY(mem, local, size)
#define TELE_MNTN_READ_MEM(mem, local, size)                TELE_MNTN_MEMCPY(local, mem, size)

#define TELE_MNTN_CUR_CPUID                                 0/*IPC_CORE_ACPU*/

#define TELE_MNTN_WRITE_REG(val, addr)                      writel((u32_t)(val), (void_t *)(addr))
#define TELE_MNTN_READ_REG(addr)                            readl((void_t *)addr)
#define TELE_MNTN_SET_BIT(nr, addr)                         set_bit((u32_t)(nr), (void_t *)(addr))
#define TELE_MNTN_CLR_BIT(nr, addr)                         clear_bit((u32_t)(nr), (void_t *)(addr))

#define TELE_MNTN_DATA_SECTION

#define TELE_MNTN_CHECK_DDR_SELF_REFRESH()                  (0)

#elif defined (CONFIG_TELE_MNTN_CORE_CM3)  /*M核*/

#define TELE_MNTN_LOCALLOCK_INIT(lock)
#define TELE_MNTN_LOCAL_LOCK(lock, flag)                    m3_local_irq_save(flag)
#define TELE_MNTN_LOCAL_UNLOCK(lock, flag)                  m3_local_irq_restore(flag)

#define TELE_MNTN_GLOBALLOCK_INIT(lock, val)                do{lock = (val);}while(0)
#define TELE_MNTN_GLOBAL_LOCK(lock, flag, ret)              do{ret = hwspin_lock_timeout((s32_t)(lock), TELE_MNTN_LOCK_TIMEOUT);}while(0)
#define TELE_MNTN_CHECK_GLOBAL_LOCK_RET(ret, cmd, out)      do{ \
                                                                if(ret) \
                                                                { \
                                                                    cmd; \
                                                                    return out; \
                                                                } \
                                                            }while(0)
#define TELE_MNTN_GLOBAL_UNLOCK(lock, flag)                 hwspin_unlock((s32_t)(lock))

#define TELE_MNTN_IPC_INT_REGISTER(ipc_int_num, func, para) BSP_IPC_RegIntSrc((ipc_int_num), (func), (para))
#define TELE_MNTN_IPC_INT_SEND(target, ipc_int_num)         (void_t)BSP_IPC_SendInt((target),(ipc_int_num))

#define TELE_MNTN_PHY_TO_VIRT(addr, size)                   ((u8_t *)((u32_t)addr))/*((u8_t *)DRV_PHY_TO_VIRT(addr))*/

#define TELE_MNTN_AXI_PHY_TO_VIRT(addr, size)               ((u8_t *)(addr))

#define TELE_MNTN_SLICE_TIME_GET()                          get_slice_time()
#define TELE_MNTN_RTC_TIME_GET()                            get_rtc_time()

#define TELE_MNTN_TRACE_OUT(_ret, _para0)                   PRINT_NOW("ret:%x,val:%x\n", (_ret),(_para0))

#define TELE_MNTN_MEMSET(m, c, size)                        (void_t)memset((void_t *)(m),(u32_t)(c),(u32_t)(size))
#define TELE_MNTN_MEMCPY(d, s, size)                        (void_t)dma_transfer((u32_t)(s),(u32_t)(d),(u32_t)(size), DMA_SYNC_MODE)

#define TELE_MNTN_WRITE_MEM(mem, local, size)               TELE_MNTN_MEMCPY(mem, (u8_t *)LPRAM_ADDR_TO_AP_ADDR((u32_t)(local)), size)
#define TELE_MNTN_READ_MEM(mem, local, size)                TELE_MNTN_MEMCPY((u8_t *)LPRAM_ADDR_TO_AP_ADDR((u32_t)(local)), mem, size)

#define TELE_MNTN_CUR_CPUID                                 2/*IPC_CORE_MCU*/

#define TELE_MNTN_WRITE_REG(val, addr)                      writel((u32_t)(val), (void_t *)(addr))
#define TELE_MNTN_READ_REG(addr)                            (u32_t)readl((u32_t *)addr)
#define TELE_MNTN_SET_BIT(nr, addr)                         set_bit((u32_t)(nr), (void_t *)(addr))
#define TELE_MNTN_CLR_BIT(nr, addr)                         clr_bit((u32_t)(nr), (void_t *)(addr))

#define TELE_MNTN_DATA_SECTION                              __ao_data

#define TELE_MNTN_CHECK_DDR_SELF_REFRESH()                  (0 == dpm_device_state(DPM_DEVICE_ID_DDR))

#endif
/*****************************************************************************
  3 枚举定义
*****************************************************************************/


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
#if !defined(CONFIG_TELE_MNTN_CORE_CM3)
extern unsigned int get_slice_time(void);
extern unsigned int get_rtc_time(void);
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of drv_tele_mntn_platform.h */
