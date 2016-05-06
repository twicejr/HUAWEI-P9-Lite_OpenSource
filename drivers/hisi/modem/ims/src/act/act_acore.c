#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/poll.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/list.h>

//BSP
//#include "bsp_icc.h"
#include "mdrv_icc.h"

#define BUFFERSIZE 256
#define DEVICE_MAJOR 250 /*设置一个主设备号*/
#define DEVICE_MINOR 0   /*次设备号*/

//#define VT_AP_CP_CHID  ((ICC_CHN_GUOM0 << 16) || GUOM0_FUNC_ID_VT_AC)
#define VT_AP_CP_CHID  MDRV_ICC_VT_VOIP

/*----------------------------------------------*
 * Global Variable                                    *
 *----------------------------------------------*/
//osl_sem_id g_ActSemId;               //tunnel signal


static bool hasData = false;

struct act_cdev_data {
    struct list_head msg_list;
    u32 len;
    u8  data[];
};

struct act_cdev {
    struct cdev cdev; /*cdev结构体，与字符设备对应*/
    wait_queue_head_t inq;
    u32 len;
    struct list_head msg_list;
    spinlock_t list_lock;//新增一个成员，定义一个spin锁,访问链表时需要加锁
};

struct act_cdev *act_cdevp     = NULL; /*设备结构体指针*/
static struct class *act_class = NULL;
static int act_major = 0;


s32 act_msgProc(u32 channel_id , u32 len, void* context)
{
    struct act_cdev_data *data = NULL;
    unsigned long flags    = 0;
    //u8 data[BUFFERSIZE]    = {0};  //声明一个缓冲链表，用于存放数据
    int ret                = 0;

    printk(KERN_INFO "Enter act_msgProc len(%d).\n", len);

    if (len > BUFFERSIZE)
    {
       printk(KERN_ERR "the length(%d) received exceed the MAX BUFFERSIZE.\n", len);
       return -1;
    }

    //分配链表内存kmalloc，用于存储数据
    data = (struct act_cdev_data*)kmalloc(sizeof(struct act_cdev_data) + len, GFP_KERNEL);
    if (!data)
    {
        ret = -ENOMEM;
        printk(KERN_ERR "act_msgProc: kmalloc data failed.\n");
        return ret;
    }

    //调用bsp_icc_read读取数据到分配的内存中
    //ret = bsp_icc_read(channel_id, data->data, len);
	ret = mdrv_icc_read(channel_id, data->data, len);
    data->len = len;

    //获取信号量 spinlock_irq_save(lock)
    spin_lock_irqsave(&(act_cdevp->list_lock), flags);

    //挂接到链表，spinlick_irq_restore释放锁
    list_add(&(data->msg_list), &(act_cdevp->msg_list));

    //释放信号量
    spin_unlock_irqrestore(&(act_cdevp->list_lock), flags);

    /*
    osl_sem_down(&g_ActSemId);

    //init the buffer
    memset(act_cdevp->data, 0, BUFFERSIZE);

    ret = bsp_icc_read(channel_id, act_cdevp->data, len);
    if (ret != len)
    {
        printk(KERN_ERR "MsgProc: get cmd para failed with ret len %d\n", ret);
    }
    printk(KERN_ERR "MsgProc: read  %d\n", ret);

    act_cdevp->len = len;
    */    
    hasData = true;

    wake_up(&(act_cdevp->inq)); //wake up the read process

    printk(KERN_INFO "End act_msgProc result(%d).\n", ret);

    return ret;
}

static int act_open(struct inode *node, struct file *filp)
{
    int ret = 0;

    filp->private_data = act_cdevp;

//    osl_sem_init(1, &g_ActSemId);
//
    printk(KERN_INFO "Enter act_open.\n");
//    ret = bsp_icc_event_register(VT_AP_CP_CHID, act_msgProc, NULL, NULL, NULL);
//    if (0 != ret)
//    {
//        printk(KERN_ERR "act_open: failed to init actunel with the code(0x%x)\n", ret);
//    }

    return ret;
}

static int act_release(struct inode *node, struct file *filp)
{
    struct act_cdev_data *data = NULL;
	struct act_cdev_data *temp_data = NULL;
    unsigned long flags    = NULL;
    int ret = 0;    
    
    //获取信号量 spinlock_irq_save(lock)
    spin_lock_irqsave(&(act_cdevp->list_lock), flags);
    
    list_for_each_entry_safe(data, temp_data, &(act_cdevp->msg_list), msg_list) 
    {
        list_del(data);
        kfree(data);
    }
    
    //释放信号量
    spin_unlock_irqrestore(&(act_cdevp->list_lock), flags);
    
    printk(KERN_INFO "Enter act_release.\n");
//    ret = bsp_icc_event_unregister(VT_AP_CP_CHID);

    return ret;
}

static size_t act_read(struct file *filp, char __user *buf, size_t size, loff_t *ppos)
{
    int ret = 0;
    unsigned long flags    = NULL;
    struct act_cdev_data *data = NULL;

    printk(KERN_INFO "Enter act_read size_t(%d).\n", size);

    while(!hasData)
    {
        if (filp->f_flags & O_NONBLOCK)
        {
            printk(KERN_ERR "act_read: NONBLOCK\n");
            //osl_sem_up(&g_ActSemId);
            return -EAGAIN;
        }

        wait_event_interruptible(act_cdevp->inq, hasData);
    }

    printk(KERN_INFO "act_read start read Data(%d).\n", act_cdevp->len);

    //获取信号量 spinlock_irq_save(lock)
    spin_lock_irqsave(&(act_cdevp->list_lock), flags);
   
    //读取数据链表
    if (! list_empty(&(act_cdevp->msg_list))) 
    {
        data = list_first_entry(&(act_cdevp->msg_list), struct act_cdev_data, msg_list);

        /*read data to user space*/
        if (copy_to_user(buf, (void*)(data->data), data->len))
        {
            ret = -EFAULT;
            printk(KERN_ERR "act_read error\n");
        }
        else
        {
           ret = data->len; 
           list_del(data);
           kfree(data);
           printk(KERN_INFO "act_read has read %d bytes.\n", ret);
        }
    }
    
    //判断链表是否为空 list_empty(act_cdevp->data)；如果是空，false；如果非空，true; 
    if (list_empty(&(act_cdevp->msg_list)))
        hasData = false; //has no data to read
    else
        hasData = true; //has data to read

    //释放信号量
    spin_unlock_irqrestore(&(act_cdevp->list_lock), flags);
        
    //osl_sem_up(&g_ActSemId);
    return ret;
}

static size_t act_write(struct file *filp, const char __user *buf, size_t size, loff_t *ppos)
{
    size_t len = size;
    u8 data[BUFFERSIZE];

    if (BUFFERSIZE <= size)
    {
        printk(KERN_ERR "act_write input size long than buffer.");
        return -E2BIG;
    }

    memset(data, 0, BUFFERSIZE);

    if (NULL == buf)
    {
       printk(KERN_ERR "buf is null");
    }
   
    if (copy_from_user(data, buf, size))
    {
        printk(KERN_ERR "act_write failed.");
        return -EFAULT;
    }

    //osl_sem_down(&g_ActSemId);
    //len = bsp_icc_send(ICC_CPU_MODEM, VT_AP_CP_CHID, data, (u32)size);
	len = mdrv_icc_write(MDRV_ICC_VT_VOIP, data, (u32)size);
    //osl_sem_up(&g_ActSemId);

    printk(KERN_INFO "act_write: send data (%d) bytes\n", len);
    return len;
}

static unsigned int act_poll(struct file* filp, poll_table *wait)
{
    unsigned int mask = 0;

    printk(KERN_INFO "Enter act_poll.\n");
   /*put the queue into poll_table*/
    poll_wait(filp, &(act_cdevp->inq), wait);

    if (hasData) 
    {
       mask |= POLLIN | POLLRDNORM;
       printk(KERN_INFO "notify read  process");
    }

    return mask;
}


static const struct file_operations act_cdev_fops =
{
    .owner   = THIS_MODULE,
    .read    = act_read,
    .write   = act_write,
    .open    = act_open,
    .release = act_release,
    .poll    = act_poll,
};

static void act_cdev_setup( struct act_cdev *dev,  int index)
{
    int err = 0;
    dev_t devno = MKDEV(act_major, index); 

    printk(KERN_INFO "Enter act_cdev_setup.");

    //Init the device
    cdev_init( &dev->cdev, &act_cdev_fops ); 
    dev->cdev.owner = THIS_MODULE; 
    dev->cdev.ops = &act_cdev_fops;

    //add the device into devices list
    err = cdev_add( &dev->cdev, devno, 1 );
    if (err)
    {
        printk(KERN_NOTICE "Error %d adding ACT Device Failed", err); 
        return;
    }
}

/* Init the ACT device*/
static int __init act_cdev_init(void)
{
    int    ret = 0;
    dev_t devno = MKDEV(DEVICE_MAJOR, 0);

    printk(KERN_INFO "Enter act_cdev_init.");

    if (act_major)
    {
        ret = register_chrdev_region(devno, 1, "act");
    }
    else
    {
        ret = alloc_chrdev_region(&devno, 0, 1, "act");
        act_major = MAJOR(devno);
    }

    if (ret < 0)
    {
        printk(KERN_ERR "Error(%d) Init ACT device failed.", ret);
        return ret;
    }

    //alloc the reource
    act_cdevp = (struct act_cdev*)kmalloc(sizeof(struct act_cdev), GFP_KERNEL);
    if (!act_cdevp)
    {
        ret = -ENOMEM;
        printk(KERN_ERR "act_cdev_init: kmalloc failed.\n");
        unregister_chrdev_region(devno, 1);
        return ret;
    }

    memset(act_cdevp, 0, sizeof(struct act_cdev));

    act_cdev_setup(act_cdevp, 0);

    //create the device node
    act_class = class_create(THIS_MODULE, "act");
    if (IS_ERR(act_class))
    {
       printk(KERN_ERR "Act_Init: failed to create class.\n");
       ret = -EFAULT;
    }
    else
    {
       device_create(act_class, NULL, MKDEV(act_major, 0), NULL, "act");
    }

    //初始化
    INIT_LIST_HEAD(&(act_cdevp->msg_list));
	
	spin_lock_init(&(act_cdevp->list_lock));

    //init wait queue
    init_waitqueue_head(&(act_cdevp->inq));
	
	ICC_CHAN_ATTR_S chanAttr;
	memset(&chanAttr, 0, sizeof(chanAttr));

    //osl_sem_init(1, &g_ActSemId);
	chanAttr.read_cb = (icc_read_cb)act_msgProc;
    //ret = bsp_icc_event_register(VT_AP_CP_CHID, act_msgProc, NULL, NULL, NULL);
	ret = mdrv_icc_open (MDRV_ICC_VT_VOIP, &chanAttr);
    if (0 != ret)
    {
        printk(KERN_ERR "act_open: failed to init actunel with the code(0x%x)\n", ret);
    }

    return ret;
}

static void __exit act_cdev_exit(void)
{
    dev_t devno = MKDEV(act_major, 0);

    printk(KERN_INFO "Enter act_cdev_exit.");

    //bsp_icc_event_unregister(VT_AP_CP_CHID);
	mdrv_icc_close(MDRV_ICC_VT_VOIP);

    //release device file
    cdev_del(&(act_cdevp->cdev));

    device_destroy(act_class, devno);
    class_destroy(act_class);

    kfree(act_cdevp);
    unregister_chrdev_region(devno, 1);
}

MODULE_AUTHOR("HUAWEI");
MODULE_LICENSE("Dual BSD/GPL");

module_init(act_cdev_init);
module_exit(act_cdev_exit);
