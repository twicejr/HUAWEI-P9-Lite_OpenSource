/*!
 *****************************************************************************
 *
 * @File       sysos_api_km.c
 * @Description    This file contains the OS Kernel Mode API.
 * ---------------------------------------------------------------------------
 *
 * Copyright (c) Imagination Technologies Ltd.
 * 
 * The contents of this file are subject to the MIT license as set out below.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 * 
 * Alternatively, the contents of this file may be used under the terms of the 
 * GNU General Public License Version 2 ("GPL")in which case the provisions of
 * GPL are applicable instead of those above. 
 * 
 * If you wish to allow use of your version of this file only under the terms 
 * of GPL, and not to allow others to use your version of this file under the 
 * terms of the MIT license, indicate your decision by deleting the provisions 
 * above and replace them with the notice and other provisions required by GPL 
 * as set out in the file called "GPLHEADER" included in this distribution. If 
 * you do not delete the provisions above, a recipient may use your version of 
 * this file under the terms of either the MIT license or GPL.
 * 
 * This License is also included in this distribution in the file called 
 * "MIT_COPYING".
 *
 *****************************************************************************/

#include <linux/stddef.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/mutex.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/signal.h>
#include <linux/spinlock.h>
#include <linux/timer.h>
#include <linux/workqueue.h>
#include <linux/hardirq.h>
#include <linux/spinlock.h>
#include <linux/device.h>
#include <linux/delay.h>

#include <asm/atomic.h>
#include "sysos_api_km.h"
#include "lst.h"
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/err.h>
#include <asm/atomic.h>
#include <linux/version.h>
#include <linux/uaccess.h>
#include "system.h"
#include <linux/highmem.h>
#include <linux/pagemap.h>
#include <linux/vmalloc.h>
#include <linux/mm.h>
#include <asm/cacheflush.h>
#include <linux/kallsyms.h>
#include <linux/syscalls.h>
#include <linux/module.h>

#include <linux/debugfs.h>
#include <linux/seq_file.h>
#define IMGSYS_ACPI IMGSYS_MODULE_NAME "_ACPI"

#include <sysmem_utils.h>
#include <linux/version.h>

#include "report_api.h"

#define SYSOS_API_KM "sysos_api_km"

DECLARE_WAIT_QUEUE_HEAD (sysos_wait_queue);

/*!
******************************************************************************
 Mutex structure
******************************************************************************/
typedef struct
{
    struct mutex  sMutex;            //!< Linux mutex.
    pid_t         sPid;              //!< process id owning the mutex (or 0)
    IMG_UINT32    ui32NestingCount;  //!< reentrant locking

} SYSOSKM_sMutex;

/*!
******************************************************************************
 Event object structure
******************************************************************************/
typedef struct
{
    IMG_BOOL           bSignalled;  //!< IMG_TRUE when signalled.

} SYSOSKM_sEvent;

/*!
******************************************************************************
 Timer object structure
******************************************************************************/
typedef struct
{
    struct timer_list  sTimer;     //!< Linux timer.
    SYSOSKM_pfnTimer   pfnTimer;   //!< Pointer to timer callback
    IMG_VOID *         pvParam;    //!< Callback parameter
    IMG_UINT32         ui32Delay;  //!< Delay - in jiffies

} SYSOSKM_sTimer;

/*!
******************************************************************************
 HISR message structure
******************************************************************************/
typedef struct
{
    struct work_struct    sWork;         //!< Linux work structure - MUST be at the start of this structure.

    SYSOSKM_pfnDevKmHisr  pfnDevKmHisr;  //!< Pointer to HISR callback
    IMG_VOID *            pvParam;       //!< Callback parameter

} SYSOSKM_sHisrMsg;

/*!
******************************************************************************
 HISR object structure
******************************************************************************/
typedef struct
{
    struct workqueue_struct *  psWorkQueue;   //!< Work Queue
    SYSOSKM_sHisrMsg           psMsg;         //!< work queue message

    SYSOSKM_pfnDevKmHisr       pfnDevKmHisr;  //!< Pointer to HISR callback
    IMG_VOID *                 pvParam;       //!< Callback parameter

} SYSOSKM_sHisr;

/*!
******************************************************************************

 Recursive spinlock(s)

******************************************************************************/
typedef struct s_nestlock
{
    spinlock_t     lock;
    void *         uniq;
    atomic_t       count;
    unsigned long  flags;

} nestlock_t;

static void nestlock_init(
    nestlock_t *  nestlock
)
{
    spin_lock_init(&nestlock->lock);
    nestlock->uniq = NULL;
    atomic_set(&nestlock->count, 0);
    nestlock->flags = 0;
}

#if 0
static void nestlock_lock(
    nestlock_t *  nestlock
)
{
    if (nestlock->uniq == current) {
        atomic_inc(&nestlock->count);
    } else {
        preempt_disable();
        spin_lock(&nestlock->lock);
        atomic_inc(&nestlock->count);
        nestlock->uniq = current;
    }
}

static void nestlock_unlock(
    nestlock_t *  nestlock
)
{
    if (atomic_dec_and_test(&nestlock->count)) {
        nestlock->uniq = NULL;
        spin_unlock(&nestlock->lock);
        preempt_enable();
    }
}

static void nestlock_lock_irqsave(
    nestlock_t *  nestlock
)
{
    if (nestlock->uniq == current) {
        atomic_inc(&nestlock->count);
    } else {
        spin_lock_irqsave(&nestlock->lock, nestlock->flags);
        atomic_inc(&nestlock->count);
        nestlock->uniq = current;
    }
}

void nestlock_unlock_irqrestore(
    nestlock_t *  nestlock
)
{
    if (atomic_dec_and_test(&nestlock->count)) {
        nestlock->uniq = NULL;
        spin_unlock_irqrestore(&nestlock->lock, nestlock->flags);
    }
}
#endif

/*!
******************************************************************************

 Power Information structure

******************************************************************************/
typedef struct
{
    SYSOSKM_pfnKmPowerEvent  pfnKmPowerEvent;
    IMG_VOID *               pvParam;

} SYSOSKM_sPowerInfo;

static IMG_BOOL    gInitialised = IMG_FALSE;    //!< Indicates where the API has been initialised

static IMG_UINT32  gui32InitCnt = 0;            //!< Count of call to SYSOSKM_Initialise() - decremented on call to SYSOSKM_Deinitialise()

static atomic_t    gsActiveMutexCnt = {.counter=0 };  //!< Count of active mutexes
static atomic_t    gsActiveEventCnt = {.counter=0 };  //!< Count of active event objects
static atomic_t    gsActiveTimerCnt = {.counter=0 };  //!< Count of active timer
static atomic_t    gsActiveHisrCnt  = {.counter=0 };  //!< Count of active HISRs


static nestlock_t gsListLock;

static struct dentry *     gpsDebugfsRoot;  //<! root for device debugfs directory
static SYSOSKM_sPowerInfo  gaPowerInfo;

/* Platform driver related stuffs.  */
static IMG_INT32 imgsys_suspend_handler(
    struct platform_device *  pdev,
    pm_message_t              state
)
{
    gaPowerInfo.pfnKmPowerEvent(SYSOSKM_POWERTRANS_PRE, SYSOSKM_POWERSTATE_S5, gaPowerInfo.pvParam);

    gaPowerInfo.pfnKmPowerEvent(SYSOSKM_POWERTRANS_POST, SYSOSKM_POWERSTATE_S5, gaPowerInfo.pvParam);

    return IMG_SUCCESS;
}

static IMG_INT32 imgsys_resume_handler(
    struct platform_device *  pdev
)
{
        gaPowerInfo.pfnKmPowerEvent(SYSOSKM_POWERTRANS_PRE, SYSOSKM_POWERSTATE_S0, gaPowerInfo.pvParam);

        gaPowerInfo.pfnKmPowerEvent(SYSOSKM_POWERTRANS_POST, SYSOSKM_POWERSTATE_S0, gaPowerInfo.pvParam);

    return IMG_SUCCESS;
}

static struct platform_device *  imgsys_acpi_pdev;
static struct platform_driver    imgsys_acpi_pdriver = {
    .driver = {
        .name  = IMGSYS_ACPI,
        .owner = THIS_MODULE,
    },
    .suspend = imgsys_suspend_handler,
    .resume  = imgsys_resume_handler,
};

static const char *  imgsys_acpi_state = NULL;

static ssize_t imgsys_acpi_state_show(
    struct device *            dev,
    struct device_attribute *  attr,
    char *                     buf
)
{
    if(imgsys_acpi_state)
        return sprintf(buf, "%s\n", imgsys_acpi_state);
    else
        return sprintf(buf, "unknown\n");
}
static DEVICE_ATTR(acpi_state, 0444, imgsys_acpi_state_show, NULL);
static struct attribute *imgsys_attrs[] = {
    &dev_attr_acpi_state.attr,
    NULL,
};
static struct attribute_group imgsys_acpi_attr_grp = {
    .name = NULL,
    .attrs = imgsys_attrs,
};

#if defined(__i386__) || defined(__x86_64__)
/* Pointer to function that flushes the process entries in the TLB */
static void (*p_flush_tlb_mm)(struct mm_struct *mm);
static void (*p_flush_tlb_mm_range)(struct mm_struct *mm, unsigned long start,
                                    unsigned long end, unsigned long vmflag);
#endif

/*!
******************************************************************************

    @Function     SYSOSKM_PowerEventStateNotify

*****************************************************************************/

IMG_VOID SYSOSKM_PowerEventStateNotify(
    const char *  new_state
)
{
    imgsys_acpi_state = new_state;
}

/*!
******************************************************************************

 @Function                sysoskm_RegisterDevices

******************************************************************************/
static IMG_RESULT sysoskm_RegisterDevices(IMG_VOID)
{
    IMG_UINT32 ui32Result;

    /* Platform driver initialisation.  */
    ui32Result = platform_driver_register(&imgsys_acpi_pdriver);
    IMG_ASSERT(ui32Result == 0);
    if (ui32Result)
    {
        return ui32Result;
    }

    /* Device initialisation */
    imgsys_acpi_pdev = platform_device_register_simple(IMGSYS_ACPI, -1,
                                                       NULL, 0);
    IMG_ASSERT(IS_ERR(imgsys_acpi_pdev) == 0);
    if (IS_ERR(imgsys_acpi_pdev))
    {
        ui32Result = PTR_ERR(imgsys_acpi_pdev);
        imgsys_acpi_pdev = NULL;

        return ui32Result;
    }

    ui32Result = sysfs_create_group(&imgsys_acpi_pdev->dev.kobj, &imgsys_acpi_attr_grp);
    if(ui32Result)
    {
        IMG_ASSERT(ui32Result == 0);
        return ui32Result;
    }
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                SYSOSKM_Initialise

******************************************************************************/
IMG_RESULT SYSOSKM_Initialise(IMG_VOID)
{
    IMG_UINT32 ui32Result;

    /*** NOTE: Some of this code is NOT thread safe as we have no OS to rely on...*/
    /* If not initialised...*/
    if (!gInitialised)
    {
        /* Register OS devices.  */
        ui32Result = sysoskm_RegisterDevices();
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if(ui32Result)
            return ui32Result;

        /* Initialise ISR structures.  */
        nestlock_init(&gsListLock);
#define IMGSYS_DRV_NAME "DebugFS_VDEC_TESTNAME"
        gpsDebugfsRoot = debugfs_create_dir(IMGSYS_DRV_NAME, NULL);
        if (gpsDebugfsRoot == IMG_NULL)
        {
            pr_err("Cannot create folder '%s' in debugfs (0x%p)", IMGSYS_DRV_NAME, gpsDebugfsRoot);
            gpsDebugfsRoot = NULL;
        }

        /* Now we are initialised..*/
        gInitialised = IMG_TRUE;
    }

    /* Update count...*/
    gui32InitCnt++;

    /* flush_tlb_mm is not exported, so we need to look at the kernel symbol table */
#if defined(__i386__) || defined(__x86_64__)
    p_flush_tlb_mm_range = (void *) kallsyms_lookup_name("flush_tlb_mm_range");
    if (!p_flush_tlb_mm_range)
    {
        p_flush_tlb_mm = (void *) kallsyms_lookup_name("flush_tlb_mm");
        if (!p_flush_tlb_mm)
        {
            REPORT(SYSOS_API_KM, REPORT_WARNING, "flush_tlb_mm_* not found\n");
        }
    }
#endif

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                SYSOSKM_Deinitialise


******************************************************************************/
IMG_VOID SYSOSKM_Deinitialise(IMG_VOID)
{
    /* Update count...*/
    IMG_ASSERT(gui32InitCnt != 0);
    gui32InitCnt--;

    /* If we are initialised and this is the last de-initialise...*/
    if ( (gInitialised) && (gui32InitCnt == 0) )
    {
        /* Ensure that all of the object have been destroyed...*/
        IMG_ASSERT(gsActiveMutexCnt.counter == 0);
        IMG_ASSERT(gsActiveEventCnt.counter == 0);
        IMG_ASSERT(gsActiveTimerCnt.counter == 0);
        IMG_ASSERT(gsActiveHisrCnt.counter == 0);
        if (gpsDebugfsRoot)
        {
            debugfs_remove_recursive(gpsDebugfsRoot);
            gpsDebugfsRoot = NULL;
        }

        SYSOSKM_RemoveKmPowerEventCb();

        sysfs_remove_group(&imgsys_acpi_pdev->dev.kobj, &imgsys_acpi_attr_grp);
        platform_driver_unregister(&imgsys_acpi_pdriver);
        platform_device_unregister(imgsys_acpi_pdev);

        /* Now we are de-initialised..*/
        gInitialised = IMG_FALSE;
    }
}


/*!
******************************************************************************

 @Function                SYSOSKM_GetProcessId

******************************************************************************/
IMG_HANDLE SYSOSKM_GetProcessId(IMG_VOID)
{
    IMG_ASSERT(gInitialised == IMG_TRUE);

    return (IMG_HANDLE) (IMG_UINTPTR)current->tgid;
}


/*!
******************************************************************************

 @Function                SYSOSKM_DisableInt

******************************************************************************/
IMG_VOID SYSOSKM_DisableInt(IMG_VOID)
{
    if (gsListLock.uniq == current)
    {
        atomic_inc(&gsListLock.count);
    }
    else
    {
        spin_lock_irqsave(&gsListLock.lock, gsListLock.flags);
        atomic_inc(&gsListLock.count);
        gsListLock.uniq = current;
    }
}
IMGVIDEO_EXPORT_SYMBOL(SYSOSKM_DisableInt)


/*!
******************************************************************************

 @Function                SYSOSKM_EnableInt

******************************************************************************/
IMG_VOID SYSOSKM_EnableInt(IMG_VOID)
{
    if (atomic_dec_and_test(&gsListLock.count))
    {
        gsListLock.uniq = NULL;
        spin_unlock_irqrestore(&gsListLock.lock, gsListLock.flags);
    }
}
IMGVIDEO_EXPORT_SYMBOL(SYSOSKM_EnableInt)


/*!
******************************************************************************

 @Function                SYSOSKM_CreateMutex

******************************************************************************/
IMG_RESULT SYSOSKM_CreateMutex(
    IMG_HANDLE *  phMutexHandle
)
{
    SYSOSKM_sMutex *  psMutex = IMG_NULL;

    IMG_ASSERT(gInitialised == IMG_TRUE);

    psMutex = IMG_MALLOC(sizeof(SYSOSKM_sMutex));
    IMG_ASSERT(psMutex != IMG_NULL);
    if (psMutex == IMG_NULL)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }

    /* Initialise mutex */
    mutex_init(&psMutex->sMutex);
    psMutex->sPid = 0;
    psMutex->ui32NestingCount = 0;

    /* Update count...*/
    atomic_inc(&gsActiveMutexCnt);

    /* Return the mutex structure...*/
    *phMutexHandle = (IMG_HANDLE) psMutex;

    return IMG_SUCCESS;
}

IMGVIDEO_EXPORT_SYMBOL(SYSOSKM_CreateMutex)

/*!
******************************************************************************

 @Function                SYSOSKM_DestroyMutex

******************************************************************************/
IMG_VOID SYSOSKM_DestroyMutex(
    IMG_HANDLE  hMutexHandle
)
{
    SYSOSKM_sMutex *  psMutex = (SYSOSKM_sMutex *)hMutexHandle;

    IMG_ASSERT(gInitialised == IMG_TRUE);

    IMG_ASSERT(hMutexHandle != IMG_NULL);
    if (hMutexHandle == IMG_NULL)
    {
        return;
    }

    /* Update count...*/
    atomic_dec(&gsActiveMutexCnt);

    /* Destroy mutex */
    mutex_destroy(&psMutex->sMutex);

    /* Free structure...*/
    IMG_FREE(psMutex);
}

IMGVIDEO_EXPORT_SYMBOL(SYSOSKM_DestroyMutex)

/*!
******************************************************************************

 @Function                SYSOSKM_LockMutex

******************************************************************************/
IMG_VOID SYSOSKM_LockMutex(
    IMG_HANDLE  hMutexHandle
)
{
    SYSOSKM_sMutex *  psMutex = (SYSOSKM_sMutex *)hMutexHandle;

    IMG_ASSERT(hMutexHandle != IMG_NULL);
    if (hMutexHandle == IMG_NULL)
    {
        return;
    }
    if(current->pid == psMutex->sPid)
    {
        ++psMutex->ui32NestingCount;
        printk("WARNING: nested mutex %s:%u\n", __FILE__, __LINE__);
        return;
    }

    mutex_lock(&psMutex->sMutex);
    psMutex->sPid = current->pid;
    ++psMutex->ui32NestingCount;
}
IMGVIDEO_EXPORT_SYMBOL(SYSOSKM_LockMutex)


/*!
******************************************************************************

 @Function                SYSOSKM_LockMutex

******************************************************************************/
IMG_RESULT SYSOSKM_LockMutex_Interruptible(
    IMG_HANDLE  hMutexHandle
)
{
    SYSOSKM_sMutex *  psMutex = (SYSOSKM_sMutex *)hMutexHandle;

    IMG_ASSERT(hMutexHandle != IMG_NULL);
    if (hMutexHandle == IMG_NULL)
    {
        return IMG_ERROR_GENERIC_FAILURE;
    }
    if(current->pid == psMutex->sPid)
    {
        ++psMutex->ui32NestingCount;
        printk("WARNING: nested mutex %s:%u\n", __FILE__, __LINE__);
        return IMG_ERROR_GENERIC_FAILURE;
    }

    if(mutex_lock_interruptible(&psMutex->sMutex) != 0) {
    	return IMG_ERROR_INTERRUPTED;
    }

    psMutex->sPid = current->pid;
    ++psMutex->ui32NestingCount;
    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(SYSOSKM_LockMutex_Interruptible)

/*!
******************************************************************************

 @Function                SYSOSKM_UnlockMutex

******************************************************************************/
IMG_VOID SYSOSKM_UnlockMutex(
    IMG_HANDLE  hMutexHandle
)
{
    SYSOSKM_sMutex *  psMutex = (SYSOSKM_sMutex *)hMutexHandle;

    IMG_ASSERT(hMutexHandle != IMG_NULL);
    if (hMutexHandle == IMG_NULL)
    {
        return;
    }

    if(--psMutex->ui32NestingCount)
    {
        return;
    }
    psMutex->sPid = 0;
    mutex_unlock(&psMutex->sMutex);
}
IMGVIDEO_EXPORT_SYMBOL(SYSOSKM_UnlockMutex)


/*!
******************************************************************************

 @Function                SYSOSKM_CreateAtomic

******************************************************************************/
IMG_RESULT SYSOSKM_CreateAtomic(IMG_HANDLE *atomic)
{
	IMG_HANDLE obj;
	obj = (IMG_HANDLE)IMG_MALLOC(sizeof(atomic_t));
	IMG_ASSERT(obj != IMG_NULL);
	if(!obj)
	{
		return IMG_ERROR_OUT_OF_MEMORY;
	}

	atomic_set((atomic_t *)obj, 0);

	*atomic = obj;

	return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(SYSOSKM_CreateAtomic)


/*!
******************************************************************************

 @Function                SYSOSKM_DestroyAtomic

******************************************************************************/
IMG_VOID SYSOSKM_DestroyAtomic(IMG_HANDLE atomic)
{
	IMG_ASSERT(gInitialised == IMG_TRUE);

	IMG_ASSERT(atomic != NULL);
	if(!atomic)
	{
		return;
	}

	IMG_FREE(atomic);
	return;
}
IMGVIDEO_EXPORT_SYMBOL(SYSOSKM_DestroyAtomic)


/*!
******************************************************************************

 @Function                SYSOSKM_ReadAtomic

******************************************************************************/
IMG_INT SYSOSKM_ReadAtomic(IMG_HANDLE atomic)
{
	return atomic_read((atomic_t *)atomic);
}
IMGVIDEO_EXPORT_SYMBOL(SYSOSKM_ReadAtomic)


/*!
******************************************************************************

 @Function                SYSOSKM_SetAtomic

******************************************************************************/
IMG_VOID SYSOSKM_SetAtomic(IMG_HANDLE atomic, IMG_INT value)
{
	atomic_set((atomic_t *)atomic, value);
}
IMGVIDEO_EXPORT_SYMBOL(SYSOSKM_SetAtomic)


/*!
******************************************************************************

 @Function                SYSOSKM_IncrementReturnAtomic

******************************************************************************/
IMG_INT SYSOSKM_IncrementReturnAtomic(IMG_HANDLE atomic)
{
	return atomic_inc_return((atomic_t *)atomic);
}
IMGVIDEO_EXPORT_SYMBOL(SYSOSKM_IncrementReturnAtomic)


/*!
******************************************************************************

 @Function                SYSOSKM_DecrementReturnAtomic

******************************************************************************/
IMG_INT SYSOSKM_DecrementReturnAtomic(IMG_HANDLE atomic)
{
	return atomic_dec_return((atomic_t *)atomic);
}
IMGVIDEO_EXPORT_SYMBOL(SYSOSKM_DecrementReturnAtomic)

/*!
******************************************************************************

 @Function                SYSOSKM_CreateEventObject

******************************************************************************/
IMG_RESULT SYSOSKM_CreateEventObject(
    IMG_HANDLE *  phEventHandle
)
{
    SYSOSKM_sEvent *  psEvent;

    IMG_ASSERT(gInitialised == IMG_TRUE);

    /* Allocate a Sync structure...*/
    psEvent = IMG_MALLOC(sizeof(*psEvent));
    IMG_ASSERT(psEvent != IMG_NULL);
    if (psEvent == IMG_NULL)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    IMG_MEMSET(psEvent, 0, sizeof(*psEvent));

    /* Update count...*/
    atomic_inc(&gsActiveEventCnt);

    /* Return the event structure...*/
    *phEventHandle = (IMG_HANDLE) psEvent;

    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(SYSOSKM_CreateEventObject)


/*!
******************************************************************************

 @Function                SYSOSKM_DestroyEventObject

******************************************************************************/
IMG_VOID SYSOSKM_DestroyEventObject(
    IMG_HANDLE  hEventHandle
)
{
    SYSOSKM_sEvent *  psEvent = (SYSOSKM_sEvent *)hEventHandle;

    IMG_ASSERT(gInitialised == IMG_TRUE);

    IMG_ASSERT(hEventHandle != IMG_NULL);
    if (hEventHandle == IMG_NULL)
    {
        return;
    }

    /* Update count...*/
    atomic_dec(&gsActiveEventCnt);

    /* Free structure...*/
    IMG_FREE(psEvent);
}
IMGVIDEO_EXPORT_SYMBOL(SYSOSKM_DestroyEventObject)


/*!
******************************************************************************

 @Function                SYSOSKM_WaitEventObject

******************************************************************************/
IMG_RESULT SYSOSKM_WaitEventObject(
    IMG_HANDLE  hEventHandle,
    IMG_BOOL    bUninterruptible
)
{
    SYSOSKM_sEvent *  psEvent = (SYSOSKM_sEvent *)hEventHandle;
    int               ret;

    IMG_ASSERT(gInitialised == IMG_TRUE);

    IMG_ASSERT(hEventHandle != IMG_NULL);
    if (hEventHandle == IMG_NULL)
    {
        return IMG_ERROR_GENERIC_FAILURE;
    }
    if (bUninterruptible)
    {
        ret = 0;
        wait_event(sysos_wait_queue, psEvent->bSignalled);
    }
    else
    {
        ret = wait_event_interruptible(sysos_wait_queue,
                                       psEvent->bSignalled);
    }

    /* If there are signals pending...*/
    if(ret == -ERESTARTSYS)
    {
        /* We where interrupted...*/
        return IMG_ERROR_INTERRUPTED;
    }

    /* If there was no signal...*/
	IMG_ASSERT (psEvent->bSignalled == IMG_TRUE);

    /* Clear signal pending...*/
    psEvent->bSignalled = IMG_FALSE;

    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(SYSOSKM_WaitEventObject)


/*!
******************************************************************************

 @Function                SYSOSKM_SignalEventObject

******************************************************************************/
IMG_VOID SYSOSKM_SignalEventObject(
    IMG_HANDLE  hEventHandle
)
{
    SYSOSKM_sEvent *  psEvent = (SYSOSKM_sEvent *)hEventHandle;

    IMG_ASSERT(gInitialised == IMG_TRUE);

    IMG_ASSERT(hEventHandle != IMG_NULL);
    if (hEventHandle == IMG_NULL)
    {
        return;
    }

    psEvent->bSignalled = IMG_TRUE;
    wake_up(&sysos_wait_queue);
}
IMGVIDEO_EXPORT_SYMBOL(SYSOSKM_SignalEventObject)


/*!
******************************************************************************

 @Function    sysoskm_fnTimer

******************************************************************************/
static IMG_VOID sysoskm_fnTimer(
    unsigned long  ulData
)
{
    SYSOSKM_sTimer *  psTimer = (SYSOSKM_sTimer *)ulData;
    IMG_BOOL          bReschedule;

    /* Call timer callback */
    bReschedule = psTimer->pfnTimer(psTimer->pvParam);

    /* If reschedule...*/
    if (bReschedule)
    {
        mod_timer(&psTimer->sTimer, psTimer->ui32Delay + jiffies);
    }
}

/*!
******************************************************************************

 @Function                SYSOSKM_CreateTimer

******************************************************************************/
IMG_RESULT SYSOSKM_CreateTimer(
    SYSOSKM_pfnTimer  pfnTimer,
    IMG_VOID *        pvParam,
    IMG_UINT32        ui32TimeOut,
    IMG_HANDLE *      phTimerHandle
)
{
    SYSOSKM_sTimer *  psTimer;

    IMG_ASSERT(gInitialised == IMG_TRUE);

    /* Allocate a timer structure...*/
    psTimer = IMG_MALLOC(sizeof(*psTimer));
    IMG_ASSERT(psTimer != IMG_NULL);
    if (psTimer == IMG_NULL)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    IMG_MEMSET(psTimer, 0, sizeof(*psTimer));

    psTimer->pfnTimer    = pfnTimer;
    psTimer->pvParam    = pvParam;

    /*
        HZ = ticks per second
        ui32MsTimeout = required ms delay
        ticks = (Hz * ui32MsTimeout) / 1000
    */
    if ((HZ * ui32TimeOut) < 1000)
    {
        psTimer->ui32Delay = 1;
    }
    else
    {
        psTimer->ui32Delay = ((HZ * ui32TimeOut) / 1000);
    }

    /* Initialise object */
    init_timer(&psTimer->sTimer);

    /* Setup timer object */
    psTimer->sTimer.function = sysoskm_fnTimer;
    psTimer->sTimer.data     = (IMG_UINTPTR)psTimer;
    psTimer->sTimer.expires  = psTimer->ui32Delay + jiffies;

    /* Add the timer to the list */
    add_timer(&psTimer->sTimer);

    /* Update count...*/
    atomic_inc(&gsActiveTimerCnt);

    /* Return the timer structure...*/
    *phTimerHandle = (IMG_HANDLE) psTimer;

    return IMG_SUCCESS;
}

IMGVIDEO_EXPORT_SYMBOL(SYSOSKM_CreateTimer)

/*!
******************************************************************************

 @Function                SYSOSKM_DestroyTimer

******************************************************************************/
IMG_VOID SYSOSKM_DestroyTimer(
    IMG_HANDLE  hTimerHandle
)
{
    SYSOSKM_sTimer *  psTimer = (SYSOSKM_sTimer *)hTimerHandle;

    IMG_ASSERT(gInitialised == IMG_TRUE);

    IMG_ASSERT(hTimerHandle != IMG_NULL);
    if (hTimerHandle == IMG_NULL)
    {
        return;
    }

    /* Remove timer */
    del_timer_sync(&psTimer->sTimer);

    /* Free structure...*/
    IMG_FREE(psTimer);

    /* Update count...*/
    atomic_dec(&gsActiveTimerCnt);
}

IMGVIDEO_EXPORT_SYMBOL(SYSOSKM_DestroyTimer)


#if 0
/*!
******************************************************************************

 @Function                SYSOSKM_CpuUmAddrToCpuPAddr

******************************************************************************/
IMG_UINT64 SYSOSKM_CpuUmAddrToCpuPAddr(
    IMG_VOID * pvCpuUmAddr
)
{
    struct page *  pg[1];
    IMG_UINT64     physaddr = 0ULL;
    int            ret;

    down_read(&current->mm->mmap_sem);
    ret = get_user_pages(current, current->mm, (unsigned long)pvCpuUmAddr & PAGE_MASK, 1, 0, 0, pg, NULL);
    up_read(&current->mm->mmap_sem);
    if(ret <= 0)
    {
        IMG_ASSERT(!"failed to get address of user page");
    }
    else
    {
        physaddr  = page_to_pfn(pg[0]) << PAGE_SHIFT;
        physaddr |= ((unsigned long)pvCpuUmAddr & (-1^PAGE_MASK));
        /* do not keep hold of the page:
         * it is up to the calling function to ensure that the page is already locked
         */
        put_page(pg[0]);
    }
    return physaddr;
}
#endif


/*!
******************************************************************************

 @Function    sysoskm_fnHisrCb

******************************************************************************/
static IMG_VOID sysoskm_fnHisrCb(
    struct work_struct *  psWork
)
{
    SYSOSKM_sHisrMsg *  psHisrMsg = (SYSOSKM_sHisrMsg *) psWork;

    IMG_ASSERT(psHisrMsg != IMG_NULL);
    if (psHisrMsg != IMG_NULL)
    {
        /* Call the HISR callback...*/
        psHisrMsg->pfnDevKmHisr(psHisrMsg->pvParam);
    }
}



/*!
******************************************************************************

 @Function                SYSOSKM_CreateKmHisr

******************************************************************************/
IMG_RESULT SYSOSKM_CreateKmHisr(
    SYSOSKM_pfnDevKmHisr  pfnDevKmHisr,
    IMG_VOID *            pvParam,
    IMG_HANDLE *          phHISRHandle
)
{
    SYSOSKM_sHisr *  psHisr;

    IMG_ASSERT(gInitialised == IMG_TRUE);

    /* Allocate a HISR structure...*/
    psHisr = IMG_MALLOC(sizeof(*psHisr));
    IMG_ASSERT(psHisr != IMG_NULL);
    if (psHisr == IMG_NULL)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    IMG_MEMSET(psHisr, 0, sizeof(*psHisr));

    /* Save the parameters...*/
    psHisr->pfnDevKmHisr = pfnDevKmHisr;
    psHisr->pvParam      = pvParam;

    /* Create the work queue...*/
    psHisr->psWorkQueue = create_singlethread_workqueue(IMGSYS_DRV_NAME"_wq");
    IMG_ASSERT(psHisr->psWorkQueue != IMG_NULL);
    if (psHisr->psWorkQueue == IMG_NULL)
    {
        IMG_FREE(psHisr);
        return IMG_ERROR_GENERIC_FAILURE;
    }
    IMG_MEMSET(&psHisr->psMsg, 0, sizeof(psHisr->psMsg));
    /* Initialise the work structure */
    INIT_WORK(&psHisr->psMsg.sWork, sysoskm_fnHisrCb);

    /* Update count...*/
    atomic_inc(&gsActiveHisrCnt);

    /* Return a pointer to the internal structure...*/
    *phHISRHandle = (IMG_HANDLE) psHisr;

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                SYSOSKM_DestroyKmHisr

******************************************************************************/
IMG_VOID SYSOSKM_DestroyKmHisr(
    IMG_HANDLE  hHISRHandle
)
{
    SYSOSKM_sHisr *  psHisr = (SYSOSKM_sHisr *)hHISRHandle;

    IMG_ASSERT(gInitialised == IMG_TRUE);

    IMG_ASSERT(hHISRHandle != IMG_NULL);
    if (hHISRHandle == IMG_NULL)
    {
        return;
    }

    /* Flush and destroy the work queue...*/
    flush_workqueue(psHisr->psWorkQueue);
    destroy_workqueue(psHisr->psWorkQueue);

    IMG_FREE(psHisr);

    /* Update count...*/
    atomic_dec(&gsActiveHisrCnt);
}



/*!
******************************************************************************

 @Function                SYSOSKM_ActivateKmHisr

******************************************************************************/
IMG_VOID SYSOSKM_ActivateKmHisr(
    IMG_HANDLE  hHISRHandle
)
{
    SYSOSKM_sHisr *     psHisr = (SYSOSKM_sHisr *)hHISRHandle;
    SYSOSKM_sHisrMsg *  psHisrMsg = NULL;
    int                 ret;

    IMG_ASSERT(gInitialised == IMG_TRUE);
    IMG_ASSERT(hHISRHandle != IMG_NULL);
    if (hHISRHandle == IMG_NULL)
    {
        return;
    }

    /* Allocate a HISR structure...*/
    psHisrMsg = &psHisr->psMsg;

    if (psHisr == IMG_NULL)
    {
        IMG_ASSERT(psHisrMsg != IMG_NULL);
        return;
    }

    psHisrMsg->pfnDevKmHisr = psHisr->pfnDevKmHisr;
    psHisrMsg->pvParam        = psHisr->pvParam;

    /* Schedule this work...
     * If the hisr workqueue is already running, this will fail,
     * but that does not matter: we just need to wake it up if it was asleep.
     */
    ret = queue_work(psHisr->psWorkQueue, &psHisrMsg->sWork);
    if(ret == 0)
    {
        // This is to fix a potential race condition:
        // if the work queue completes its work (and marks the sWork as complete) halfway
        // through the previous queue_work call, I think it would not wake up again.
        // so call queue_work again. In normal circumstances, this will just return 0 ("work already on queue")
        queue_work(psHisr->psWorkQueue, &psHisrMsg->sWork);
    }
}



/*!
******************************************************************************

 @Function                SYSOSVKM_GetBoolEnvVar

******************************************************************************/
static int example_bool = 0;
module_param(example_bool, int, S_IRUGO);

IMG_BOOL SYSOSVKM_GetBoolEnvVar(
    IMG_CHAR *  pszName
)
{
    if (strcmp(pszName, "example_bool") == 0)
    {
        return example_bool;
    }
    else
    {
        /* Var not recognised...*/
        IMG_ASSERT(IMG_FALSE);
    }
    return IMG_FALSE;
}


/*!
******************************************************************************

 @Function                SYSOSKM_GetIntEnvVar

******************************************************************************/
static int example_int = 0;
module_param(example_int, int, S_IRUGO);

IMG_INT32 SYSOSKM_GetIntEnvVar(
    IMG_CHAR *  pszName
)
{
    if (strcmp(pszName, "example_int") == 0)
    {
        return example_int;
    }
    else
    {
        /* Var not recognised...*/
        IMG_ASSERT(IMG_FALSE);
    }
    return 0;
}


/*!
******************************************************************************

 @Function                SYSOSKM_GetStrEnvVar

 ******************************************************************************/
static char * example_str = IMG_NULL;
module_param(example_str, charp, S_IRUGO);

IMG_CHAR * SYSOSKM_GetStrEnvVar(
    IMG_CHAR *  pszName
)
{
    if (strcmp(pszName, "example_str") == 0)
    {
        return example_str;
    }
    else
    {
        /* Var not recognised...*/
        IMG_ASSERT(IMG_FALSE);
    }
    return IMG_NULL;
}

/*!
******************************************************************************

 @Function                SYSOSKM_GetSymbolAddr

******************************************************************************/
IMG_VOID * SYSOSKM_GetSymbolAddr(
    IMG_CHAR *  pszName
)
{
#if defined (USE_SGX_SERVICES)
    /* We only know about "PVRGetBufferClassJTable"...*/
    if (IMG_STRCMP("PVRGetBufferClassJTable", pszName) == 0)
    {
        /* Return address of the function...*/
        return * (&PVRGetBufferClassJTable);
    }
    else
#endif

    return IMG_NULL;
}

/*!
******************************************************************************
 @Function              SYSOSKM_CopyFromUser
******************************************************************************/
IMG_RESULT SYSOSKM_CopyFromUserRaw(
    IMG_VOID *               pvToCpuKmAddr,
    const IMG_VOID __user *  pvFromCpuAddr,
    IMG_SIZE                 stNumBytes
)
{
#ifdef IMG_KERNEL_MODULE
    if (0 != copy_from_user(pvToCpuKmAddr, pvFromCpuAddr, stNumBytes))
        return IMG_ERROR_FATAL;
    return IMG_SUCCESS;
#else
    IMG_MEMCPY(pvToCpuKmAddr, pvFromCpuAddr, stNumBytes);
    return IMG_SUCCESS;
#endif
}
IMGVIDEO_EXPORT_SYMBOL(SYSOSKM_CopyFromUserRaw)

/*!
******************************************************************************
 @Function              SYSOSKM_CopyToUser
******************************************************************************/
IMG_RESULT SYSOSKM_CopyToUserRaw(
    IMG_VOID __user *  pvToCpuUmAddr,
    const IMG_VOID *   pvFromCpuKmAddr,
    IMG_SIZE           stNumBytes
)
{
#ifdef IMG_KERNEL_MODULE
    if (0 != copy_to_user((void __user *) pvToCpuUmAddr, pvFromCpuKmAddr, stNumBytes))
        return IMG_ERROR_FATAL;
    return IMG_SUCCESS;
#else
    IMG_MEMCPY(pvToCpuUmAddr, pvFromCpuKmAddr, stNumBytes);
    return IMG_SUCCESS;
#endif
}
IMGVIDEO_EXPORT_SYMBOL(SYSOSKM_CopyToUserRaw)

#if defined(__i386__) || defined(__x86_64__)
/*!
******************************************************************************
 @Function              sysoskm_setPTE
******************************************************************************/
static inline void sysoskm_setPTE(
    unsigned long  addr,
    struct page *  pg,
    pgprot_t       newProt
)
{
    pgd_t *pgd;
    pmd_t *pmd;
    pte_t *ptep, pte;
    pud_t *pud;
    struct mm_struct *mm = current->mm;

    pgd = pgd_offset(mm, addr);
    if (pgd_none(*pgd) || pgd_bad(*pgd))
        goto out;

    pud = pud_offset(pgd, addr);
    if (pud_none(*pud) || pud_bad(*pud))
        goto out;

    pmd = pmd_offset(pud, addr);
    if (pmd_none(*pmd) || pmd_bad(*pmd))
        goto out;

    ptep = pte_offset_map(pmd, addr);
    /* Somebody could have released (free) the buffer in user space */
    if (!ptep || !(ptep->pte))
        goto out;

    pte = mk_pte(pg, newProt);
    set_pte(ptep, pte);

    pte_unmap(ptep);

out:
    return;
}

static inline pgprot_t sysoskm_setPTE_UC(
    unsigned long  addr,
    struct page *  pg
)
{
    pgd_t *pgd;
    pmd_t *pmd;
    pte_t *ptep, pte;
    pud_t *pud;
    struct mm_struct *mm = current->mm;
    pgprot_t currprot = {0}, newprot;

    pgd = pgd_offset(mm, addr);
    if (pgd_none(*pgd) || pgd_bad(*pgd))
        goto out;

    pud = pud_offset(pgd, addr);
    if (pud_none(*pud) || pud_bad(*pud))
        goto out;

    pmd = pmd_offset(pud, addr);
    if (pmd_none(*pmd) || pmd_bad(*pmd))
        goto out;

    ptep = pte_offset_map(pmd, addr);
    if (!ptep)
        goto out;

    currprot = pte_pgprot(*ptep);
    newprot = pgprot_noncached(currprot);

    pte = mk_pte(pg, newprot);
    set_pte(ptep, pte);

    pte_unmap(ptep);

out:
    return currprot;
}


static pgprot_t oldProt_s;
#endif
/*!
******************************************************************************
 @Function              SYSOSKM_CpuUmAddrToCpuPAddrArray
******************************************************************************/
IMG_RESULT SYSOSKM_CpuUmAddrToCpuPAddrArray(
    const IMG_VOID __user *  pvCpuUmAddr,
    IMG_PHYSADDR *           ppaPhysAddrArray,
    IMG_UINT                 numPages,
    IMG_PVOID *              ppvKernAddr
)
{
#ifdef IMG_KERNEL_MODULE

    struct page           **  pages = NULL;
    struct vm_area_struct **  vmas  = NULL;
    int                       ret;
    IMG_RESULT                result = IMG_ERROR_GENERIC_FAILURE;
    unsigned long             umAddr = (unsigned long) pvCpuUmAddr;

    /* Check alignment */
    if (umAddr & (PAGE_SIZE - 1))
    {
        REPORT(SYSOS_API_KM, REPORT_ERR, "Error 0x%p user address not aligned\n",
               pvCpuUmAddr);
        return result;
    }

    pages = IMG_BIGALLOC(numPages*sizeof(struct page *));
    vmas  = IMG_BIGALLOC(numPages*sizeof(struct vm_area_struct *));
    if (pages == NULL || vmas == NULL)
    {
        result = IMG_ERROR_OUT_OF_MEMORY;
        goto exitFailPagesAlloc;
    }

    down_write(&current->mm->mmap_sem);
    ret = get_user_pages(current, current->mm, umAddr,
                         numPages, 1, 0, pages, vmas);

#if defined(__i386__) || defined(__x86_64__)
    /* Set memory as uncached */
    if (ret == numPages)
    {
        size_t pg_i;
        unsigned long umLoopAddr = umAddr;

        /* The allocation comes from a malloc, so it should be a single vma */
        flush_cache_range(vmas[0], umAddr, umAddr + numPages*PAGE_SIZE);
        for (pg_i = 0; pg_i < numPages; ++pg_i)
        {
            oldProt_s = sysoskm_setPTE_UC(umLoopAddr, pages[pg_i]);
            umLoopAddr += PAGE_SIZE;
        }
        if (p_flush_tlb_mm_range)
            p_flush_tlb_mm_range(vmas[0]->vm_mm, umAddr, umAddr + numPages*PAGE_SIZE,
                                 vmas[0]->vm_flags);
        else if (p_flush_tlb_mm)
            p_flush_tlb_mm(current->mm);
    }
#else
    REPORT(SYSOS_API_KM, REPORT_WARNING, "flush_tlb_mm not implemented\n");
#endif

    up_write(&current->mm->mmap_sem);

    REPORT(SYSOS_API_KM, REPORT_INFO,
           "SYSOSKM_CpuUmAddrToCpuPAddrArray UM address 0x%p mapped to %d pages\n",
           pvCpuUmAddr, ret);

    if (ret != numPages)
    {
        REPORT(SYSOS_API_KM, REPORT_ERR,
               "get_user_pages ERROR for UM address 0x%p (%d pages, ret is %d)\n",
               pvCpuUmAddr, numPages, ret);
        result = IMG_ERROR_GENERIC_FAILURE;
    }
    else
    {
        pgprot_t pageProt = PAGE_KERNEL;
        size_t pg_i;

        for (pg_i = 0; pg_i < numPages; ++pg_i)
        {
            ppaPhysAddrArray[pg_i] = page_to_pfn(pages[pg_i]) << PAGE_SHIFT;
        }
        pageProt = pgprot_noncached(pageProt);
        *ppvKernAddr = vmap(pages, numPages, VM_MAP, pageProt);

        result = IMG_SUCCESS;
    }


exitFailPagesAlloc:
    if(pages)
        IMG_BIGFREE(pages);
    if(vmas)
        IMG_BIGFREE(vmas);
    return result;

#else   // IMG_KERNEL_MODULE

    const char *pcCpuUmByAddr = pvCpuUmAddr;
    int pg_i;

    /* fake platform */
    *ppvKernAddr = (char *) pcCpuUmByAddr;
    for (pg_i = 0; pg_i < numPages; ++pg_i)
    {
        ppaPhysAddrArray[pg_i] = (IMG_PHYSADDR)(IMG_UINTPTR) pcCpuUmByAddr;
        pcCpuUmByAddr += HOST_MMU_PAGE_SIZE;
    }

    return IMG_SUCCESS;

#endif  // IMG_KERNEL_MODULE
}

/*!
******************************************************************************

 @Function                SYSOSKM_ReleaseCpuPAddrArray

******************************************************************************/
IMG_RESULT SYSOSKM_ReleaseCpuPAddrArray(
    IMG_PVOID                pvKernAddr,
    IMG_HANDLE               pvUmAddr,
    const IMG_PHYSADDR *     ppaPhysAddrArray,
    IMG_UINT                 numPages
)
{
    IMG_RESULT      result = IMG_ERROR_GENERIC_FAILURE;
    struct page **  ppsPage;
    size_t          pg_i;
#if defined(__i386__) || defined(__x86_64__)
    struct vm_area_struct *  vma;
    unsigned long            umAddr = (unsigned long) pvUmAddr;
    unsigned long            umLoopAddr;
#endif

    /* Get pages */
    ppsPage = IMG_BIGORSMALL_ALLOC(numPages*sizeof(struct page *));
    IMG_ASSERT(IMG_NULL != ppsPage);
    if(IMG_NULL == ppsPage)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    for (pg_i = 0; pg_i < numPages; ++pg_i)
    {
        ppsPage[pg_i] = pfn_to_page(ppaPhysAddrArray[pg_i] >> PAGE_SHIFT);
    }

#if defined(__i386__) || defined(__x86_64__)
    /* Check if we still have a process */
    if (current && current->mm)
    {
        /* Change page protection to its previous value */
        down_write(&current->mm->mmap_sem);

        vma = find_vma(current->mm, umAddr);
        if (vma)
        {
            flush_cache_range(vma, umAddr, umAddr + numPages*PAGE_SIZE);
            umLoopAddr = umAddr;
            for (pg_i = 0; pg_i < numPages; ++pg_i)
            {
                sysoskm_setPTE(umLoopAddr, ppsPage[pg_i], oldProt_s);
                umLoopAddr += PAGE_SIZE;
            }
            if (p_flush_tlb_mm)
            {
                p_flush_tlb_mm(current->mm);
            }
        }
        else
        {
            REPORT(SYSOS_API_KM, REPORT_ERR, "vma not found for user address 0x%lx\n", umAddr);
        }
        REPORT(SYSOS_API_KM, REPORT_INFO, "SYSOSKM revert protection of 0x%lx to 0x%llx\n",
               umAddr, (unsigned long long)oldProt_s.pgprot);

        up_write(&current->mm->mmap_sem);
    }
#else
    REPORT(SYSOS_API_KM, REPORT_ERR, "cache flush not implemented on this architecture\n");
#endif

    vunmap(pvKernAddr);
    for (pg_i = 0; pg_i < numPages; ++pg_i)
    {
        /* Free page */
        page_cache_release(ppsPage[pg_i]);
    }

    IMG_BIGORSMALL_FREE(numPages*sizeof(*ppsPage), ppsPage);

    return result;
}

/*!
******************************************************************************

 @Function                SYSOSKM_RegisterKmPowerEventCb

******************************************************************************/
IMG_VOID SYSOSKM_RegisterKmPowerEventCb(
    SYSOSKM_pfnKmPowerEvent  pfnKmPowerEvent,
    IMG_VOID *               pvParam
)
{
    gaPowerInfo.pfnKmPowerEvent = pfnKmPowerEvent;
    gaPowerInfo.pvParam         = pvParam;
}


/*!
******************************************************************************

@Function                SYSOSKM_RemoveKmPowerEventCb

******************************************************************************/
IMG_VOID SYSOSKM_RemoveKmPowerEventCb(IMG_VOID)
{
    gaPowerInfo.pfnKmPowerEvent = IMG_NULL;
    gaPowerInfo.pvParam         = IMG_NULL;
}

/*!
******************************************************************************

 @Function                SYSOSKM_ResumeDevice

******************************************************************************/
IMG_RESULT SYSOSKM_ResumeDevice(IMG_VOID)
{
    if(gaPowerInfo.pfnKmPowerEvent != NULL)
    {
        imgsys_resume_handler(NULL);

        return IMG_SUCCESS;
    }

    return IMG_ERROR_FATAL;
}


/*!
******************************************************************************

 @Function                SYSOSKM_SuspendDevice

******************************************************************************/
IMG_RESULT SYSOSKM_SuspendDevice(IMG_VOID)
{
    if(gaPowerInfo.pfnKmPowerEvent != NULL)
    {
        pm_message_t state = {0};

        imgsys_suspend_handler(NULL, state);

        return IMG_SUCCESS;
    }

    return IMG_ERROR_FATAL;
}

/*!
******************************************************************************
 Type with information needed in a debug file
******************************************************************************/
typedef struct
{
    struct dentry *        debugfile;
    void *                 data;
    debug_open_callback_t  open_callback;

} debug_callback_data;

/*!
******************************************************************************
 @Function                debug_status_show
 Calls provided callback that writes information to the debug file
******************************************************************************/
static int debug_status_show(
    struct seq_file *  s,
    void *             unused)
{
    debug_callback_data* psCallbackData = s->private;

    psCallbackData->open_callback(psCallbackData->data,
                                  (debug_printf_t) seq_printf, s);
    return 0;
}

/*!
******************************************************************************
 @Function                debug_status_open
 Open operation for debug file
******************************************************************************/
static int debug_status_open(
    struct inode *  inode,
    struct file *   file)
{
    return single_open(file, debug_status_show, inode->i_private);
}

/*!
******************************************************************************
 Operations for debug files
******************************************************************************/
static const struct file_operations debug_status_fops = {
    .open    = debug_status_open,
    .read    = seq_read,
    .llseek  = seq_lseek,
    .release = single_release,
};

/*!
******************************************************************************
 @Function                SYSOSKM_CreateDebugFile
******************************************************************************/
IMG_HANDLE SYSOSKM_CreateDebugFile(
    const char *           filename,
    void *                 data,
    debug_open_callback_t  open_callback
)
{
    IMG_HANDLE hCallbackData = NULL;
    struct dentry * root = gpsDebugfsRoot;

    IMG_ASSERT(root);

    if(root)
    {
        struct dentry *debfile = NULL;
        debug_callback_data *pCallbackData = IMG_MALLOC(sizeof(*pCallbackData));
        IMG_ASSERT(pCallbackData);
        if (pCallbackData) {
            pCallbackData->data = data;
            pCallbackData->open_callback = open_callback;
            debfile = debugfs_create_file(filename, 0664, root,
                                          pCallbackData, &debug_status_fops);
            pCallbackData->debugfile = debfile;
            if (debfile == IMG_NULL)
            {
                REPORT(REPORT_MODULE_DMAN, REPORT_INFO,
                       "SYSOSKM_CreateDebugFile Cannot create %s debug file (0x%p)",
                       filename, debfile);
                IMG_FREE(pCallbackData);
            }
            else
            {
                hCallbackData = pCallbackData;
            }
        }
    }

    return hCallbackData;
}
IMGVIDEO_EXPORT_SYMBOL(SYSOSKM_CreateDebugFile)

/*!
******************************************************************************
 @Function                DMANKM_RemoveDebugFile
******************************************************************************/
IMG_VOID SYSOSKM_RemoveDebugFile(
    IMG_HANDLE  hDebugFile
)
{
    debug_callback_data *pCallbackData = hDebugFile;

    IMG_ASSERT(pCallbackData);
    if(pCallbackData)
    {
        debugfs_remove(pCallbackData->debugfile);
        IMG_FREE(pCallbackData);
    }
}

IMGVIDEO_EXPORT_SYMBOL(SYSOSKM_RemoveDebugFile)
/*!
******************************************************************************

 @Function              SYSOSKM_GetTimeOfDay

******************************************************************************/
IMG_RESULT SYSOSKM_GetTimeOfDay(
    struct timespec *  psTimespec
)
{
    getnstimeofday(psTimespec);
    return IMG_SUCCESS;
}
