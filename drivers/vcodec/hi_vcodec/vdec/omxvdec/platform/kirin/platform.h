

#ifndef __PLATFORM_H__
#define	__PLATFORM_H__

#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/version.h>
#include <linux/kthread.h>
#include <linux/seq_file.h>
#include <linux/semaphore.h>
#include <linux/platform_device.h>
#include <asm/uaccess.h>

#ifdef CONFIG_COMPAT //Modified for 64-bit platform
#include <linux/compat.h>
#endif

#include "memory.h"
#include "regulator.h"

typedef enum 
{
    MODULE_VFMW,    /* vfmw */
    MODULE_VPSS,    /* vpss */
    MODULE_BPP,     /* bpp  */
    MODULE_BUTT,
}OMX_MODULE_E;


#define VDEC_INIT_MUTEX(pSem)              \
do {                                      \
    sema_init(pSem, 1);                    \
}while(0)

#define VDEC_DOWN_INTERRUPTIBLE(pSem)      \
do {                                      \
    if(down_interruptible(pSem))           \
    {                                     \
        OmxPrint(OMX_FATAL, "%s down_interruptible failed!\n", __func__); \
        return HI_FAILURE;                \
    }                                     \
}while(0)
    
#define VDEC_UP_INTERRUPTIBLE(pSem)        \
do {                                      \
    up(pSem);                              \
}while(0)
    
#define PROC_PRINT(arg...)  seq_printf(arg)

typedef int (*drv_proc_read_fn)(struct seq_file *, void *);
typedef int (*drv_proc_write_fn)(struct file *file, const char __user *buf, size_t count, loff_t *ppos);

HI_S32  VDEC_MODULE_GetFunction(OMX_MODULE_E u32ModuleID, HI_VOID** ppFunc);
HI_S32  VDEC_SYS_GetTimeStampMs(HI_U32 *pu32TimeMs);
HI_S32  VDEC_PROC_Create(HI_CHAR *proc_name, drv_proc_read_fn pfn_read, drv_proc_write_fn pfn_write);
HI_VOID VDEC_PROC_Destroy(HI_CHAR *proc_name);
HI_VOID VDEC_PROC_EchoHelper(const HI_CHAR *fmt, ...);

#endif
