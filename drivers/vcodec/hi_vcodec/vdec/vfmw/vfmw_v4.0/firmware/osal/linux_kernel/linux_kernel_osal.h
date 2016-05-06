

#ifndef __VFMW_LINUX_KERNEL_OSAL_HEADER__
#define  __VFMW_LINUX_KERNEL_OSAL_HEADER__

#include <asm/cacheflush.h>
#include <linux/kthread.h>
#include <linux/hrtimer.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/wait.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/vmalloc.h>
#include <linux/mm.h>
#include <linux/poll.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/fcntl.h>
#include <linux/miscdevice.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/string.h>
#include <linux/delay.h>
#include <linux/version.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <asm/ioctl.h>
#include <linux/semaphore.h>

#include "vfmw_osal_ext.h"


/*======================================================================*/
/*                            struct define                             */
/*======================================================================*/
typedef struct hiKERN_EVENT_S
{
	wait_queue_head_t   queue_head;
	SINT32              flag;    
} OSAL_EVENT;

typedef struct hiKERN_IRQ_LOCK_S
{
    spinlock_t     irq_lock;
    unsigned long  irq_lockflags;
    int            isInit;
} OSAL_IRQ_SPIN_LOCK;


/*======================================================================*/
/*                              define                                  */
/*======================================================================*/
typedef  struct task_struct*    OSAL_TASK;
typedef  struct file            OSAL_FILE;    
typedef  struct semaphore       OSAL_SEMA;
typedef  OSAL_EVENT             OSAL_TASK_MUTEX;


/*======================================================================*/
/*                          function declare                            */
/*======================================================================*/

/************************************************************************/
/* spinlock: init/lock/unlock */
/************************************************************************/
VOID       OSAL_SpinLockIRQInit(OSAL_IRQ_SPIN_LOCK *pIntrMutex);
SINT32     OSAL_SpinLockIRQ(OSAL_IRQ_SPIN_LOCK *pIntrMutex);
SINT32     OSAL_SpinUnLockIRQ(OSAL_IRQ_SPIN_LOCK *pIntrMutex);

/************************************************************************/
/* sleep: sleep in ms */
/************************************************************************/
#define    OSAL_MSLEEP(nMs)    msleep(nMs)

/************************************************************************/
/* time: get in ms/us */
/************************************************************************/
UINT32     OSAL_GetTimeInMs(VOID);
UINT32     OSAL_GetTimeInUs(VOID);

/************************************************************************/
/* virtual memory: alloc/free */
/************************************************************************/
VOID      *OSAL_AllocVirMem(SINT32 Size);
VOID       OSAL_FreeVirMem(VOID *p);

/************************************************************************/
/* task: create/wakeup/delete */
/************************************************************************/
SINT32     OSAL_CreateTask( OSAL_TASK *pTask, SINT8 TaskName[], VOID *pTaskFunction );
SINT32     OSAL_WakeupTask( OSAL_TASK *pTask );
SINT32     OSAL_DeleteTask(OSAL_TASK *pTask);

/************************************************************************/
/* event: init/post/wait */
/************************************************************************/
SINT32     OSAL_InitEvent( OSAL_EVENT *pEvent, SINT32 InitVal );
SINT32     OSAL_GiveEvent( OSAL_EVENT *pEvent ); 
SINT32     OSAL_WaitEvent( OSAL_EVENT *pEvent, SINT32 msWaitTime ); 

/************************************************************************/
/* file: open/close/read/write */
/************************************************************************/
OSAL_FILE *OSAL_FileOpen(const char *filename, int flags, int mode);
VOID       OSAL_FileClose(struct file *filp);
SINT32     OSAL_FileRead(char *buf, unsigned int len, struct file *filp);
SINT32     OSAL_FileWrite(char *buf, int len, struct file *filp);

/************************************************************************/
/* yuv: dump yuv interface */
/************************************************************************/
VOID OSAL_WriteYuv(VID_STD_E eVidStd, IMAGE *pImage, OSAL_FILE *fpYuv, SINT32 WithCrop);

/************************************************************************/
/* memory: alloc/free/map/unmap */
/************************************************************************/
SINT32     OSAL_MemMalloc(UINT8 * MemName, UINT32 len, UINT32 align, UINT32 IsCached, MEM_DESC_S *pMemDesc);
SINT32     OSAL_MemFree(MEM_DESC_S *pMemDesc);
SINT8     *OSAL_RegisterMap(UADDR PhyAddr, UINT32 RegByteLen);
VOID       OSAL_RegisterUnMap(UINT8 *VirAddr);
UINT8     *OSAL_Mmap(UADDR phyaddr, UINT32 len);
UINT8     *OSAL_MmapCache(UADDR phyaddr, UINT32 len);
VOID       OSAL_Munmap(UINT8 *p );

/************************************************************************/
/* semaphore: init/get/release */
/************************************************************************/
VOID       OSAL_SEMA_INTIT(OSAL_SEMA *pSem);
SINT32     OSAL_DOWN_INTERRUPTIBLE(OSAL_SEMA *pSem);
VOID       OSAL_UP(OSAL_SEMA *pSem);

/************************************************************************/
/* linux kernel osal function pointer initialize */
/************************************************************************/
VOID       OSAL_InitInterface(VOID);

#endif


