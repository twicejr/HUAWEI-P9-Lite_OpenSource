#include <linux/interrupt.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/semaphore.h>
#include <linux/spinlock.h>
#include <linux/fs.h>
#include <linux/mm.h>
//#include <linux/rwlock.h>

#include <linux/module.h>
#include <linux/init.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
//#include "hi_drv_struct.h"
#include "drv_venc_osal.h"
#include "hi_drv_venc.h"
#include "hi_drv_mem.h"
#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

static HI_VOID (*ptrVencCallBack)(HI_VOID);

static irqreturn_t VENC_DRV_OsalVencISR(HI_S32 Irq, HI_VOID* DevID)
{
    (*ptrVencCallBack)();
    return IRQ_HANDLED;
}

HI_S32 VENC_DRV_OsalIrqInit( HI_U32 Irq, HI_VOID (*ptrCallBack)(HI_VOID))
{
    HI_S32 ret = 0;

    if (Irq != 0)
    {
        ptrVencCallBack = ptrCallBack;
//        ret = request_irq(Irq, VENC_DRV_OsalVencISR, IRQF_DISABLED, "hi_venc_irq", NULL);
//        ret = request_irq(Irq, VENC_DRV_OsalVencISR, IRQF_DISABLED, "DT_device", NULL);
        ret = request_irq(Irq, VENC_DRV_OsalVencISR, 0, "DT_device", NULL);
    }
    else
    {
        HI_ERR_VENC("%s, params is invaild! Irq:%d  invalid_argument!\n", __func__, Irq);
		ret = HI_FAILURE;
    }

    if (ret == 0)
    {
        return HI_SUCCESS;
    }
    else
    {
        HI_ERR_VENC("%s, request_irq failed!\n", __func__);
		return HI_FAILURE;
    }
}

HI_VOID VENC_DRV_OsalIrqFree( HI_U32 Irq )
{
    free_irq(Irq, NULL);
}

HI_S32 VENC_DRV_OsalLockCreate( HI_VOID**phLock )
{
    spinlock_t *pLock = NULL;

    pLock = (spinlock_t *)kmalloc(sizeof(spinlock_t), GFP_KERNEL);

    if (pLock == NULL)
    {
        HI_ERR_VENC("kmalloc failed!\n");
		return HI_FAILURE;
    }

    spin_lock_init( pLock );
    *phLock = pLock;

    return HI_SUCCESS;
}

HI_VOID VENC_DRV_OsalLockDestroy( HI_VOID* hLock )
{
    if(hLock)
    {
		kfree((HI_VOID *)hLock);
		hLock = NULL;
    }
}

HI_VOID VENC_DRV_OsalLock( HI_VOID* hLock, VEDU_LOCK_FLAG *pFlag )
{
    spin_lock_irqsave((spinlock_t *)hLock, *pFlag);
}

HI_VOID VENC_DRV_OsalUnlock( HI_VOID* hLock, VEDU_LOCK_FLAG *pFlag )
{
    spin_unlock_irqrestore((spinlock_t *)hLock, *pFlag);
}

HI_S32 VENC_DRV_OsalCreateTask(HI_VOID **phTask, HI_S8 TaskName[], HI_VOID *pTaskFunction )
{
    *phTask = (HI_VOID *)kthread_create(pTaskFunction, NULL, TaskName);
    if(NULL == (*phTask))
    {
        HI_ERR_VENC("%s, Creat thread failed! task:%s\n", __func__, TaskName);
		return HI_FAILURE;
    }

    wake_up_process((struct task_struct*) (*phTask));
    return HI_SUCCESS;
}

HI_S32 VENC_DRV_OsalDeleteTask(HI_VOID *hTask)
{
 //   kthread_stop( (struct task_struct*) hTask );// task线程释放随机挂死
    return HI_SUCCESS;
}

/************************************************************************/
/* 初始化事件                                                           */
/************************************************************************/
HI_S32 VENC_DRV_OsalInitEvent( VEDU_OSAL_EVENT *pEvent, HI_S32 InitVal )
{
	pEvent->flag = InitVal;
	init_waitqueue_head( &(pEvent->queue_head) );
	return HI_SUCCESS;
}

/************************************************************************/
/* 发出事件唤醒                                                             */
/************************************************************************/
HI_S32 VENC_DRV_OsalGiveEvent( VEDU_OSAL_EVENT *pEvent )
{
	pEvent->flag = 1;
	//wake_up_interruptible ( &(pEvent->queue_head) );
	wake_up( &(pEvent->queue_head) );
	return HI_SUCCESS;
}

/************************************************************************/
/* 等待事件                                                             */
/* 事件发生返回OSAL_OK，超时返回OSAL_ERR 若condition不满足就阻塞等待    */
/* 被唤醒返回 0 ，超时返回非-1                                          */
/************************************************************************/
HI_S32 VENC_DRV_OsalWaitEvent( VEDU_OSAL_EVENT *pEvent, HI_U32 msWaitTime )
{
	HI_S32 l_ret = 0;

    if ( msWaitTime != 0xffffffff)
    {
       //l_ret = wait_event_interruptible_timeout( pEvent->queue_head, (pEvent->flag != 0), ((msWaitTime*10+50)/(msWaitTime)) );
       l_ret = wait_event_interruptible_timeout( pEvent->queue_head, (pEvent->flag != 0), msecs_to_jiffies(msWaitTime)/*msWaitTime/10*/ );

       pEvent->flag = 0;//(pEvent->flag>0)? (pEvent->flag-1): 0;

	   return (l_ret != 0)? HI_SUCCESS: HI_FAILURE;
    }
	else
	{
	   l_ret = wait_event_interruptible( pEvent->queue_head, (pEvent->flag != 0));
	   //wait_event(pEvent->queue_head, (pEvent->flag != 0));
	   pEvent->flag = 0;
	   return (l_ret == 0)? HI_SUCCESS: HI_FAILURE;
	}
}

/************************************************************************/
/* 文件tell position                                                    */
/************************************************************************/

struct file *VENC_DRV_OsalFopen(const char *filename, int flags, int mode)
{
    struct file *filp = filp_open(filename, flags, mode);
    return (IS_ERR(filp)) ? NULL : filp;//modify by ljhfilp;//
}

void VENC_DRV_OsalFclose(struct file *filp)
{
    if (filp)
    {
        filp_close(filp, NULL);
    }
}

int VENC_DRV_OsalFread(char *buf, unsigned int len, struct file *filp)
{
    int readlen = 0;
    mm_segment_t oldfs;

    if (filp == NULL)
            return -ENOENT;
    if (filp->f_op->read == NULL)
            return -ENOSYS;
    if (((filp->f_flags & O_ACCMODE) & (O_RDONLY | O_RDWR)) == 0)
            return -EACCES;
    oldfs = get_fs();
    set_fs(KERNEL_DS);
    readlen = filp->f_op->read(filp, buf, len, &filp->f_pos);
    set_fs(oldfs);

    return readlen;
}

int VENC_DRV_OsalFwrite(char *buf, int len, struct file *filp)
{
    int writelen = 0;
    mm_segment_t oldfs;
#if 0
        if (filp == NULL)
                return -ENOENT;
        if (filp->f_op->write == NULL)
                return -ENOSYS;
        if (((filp->f_flags & O_ACCMODE) & (O_WRONLY | O_RDWR)) == 0)
                return -EACCES;
        oldfs = get_fs();
        set_fs(KERNEL_DS);
        writelen = filp->f_op->write(filp, buf, len, &filp->f_pos);
        set_fs(oldfs);
#else
    loff_t pos = 0;
    oldfs = get_fs();
    set_fs(KERNEL_DS);
    writelen = vfs_write(filp, (char __user*)buf, len, &pos);
    pos = 0;
    set_fs(oldfs);
#endif
    return writelen;
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif
