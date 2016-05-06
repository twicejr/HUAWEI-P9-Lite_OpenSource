/******************************************************************************

			  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
文 件 名   : drv_mailbox_vxworks.c
版 本 号   : 初稿
作	  者   : 莫南 00176101
生成日期   : 2012年9月24日
最近修改   :
功能描述   : mailbox C核  linux平台系统适配文件
函数列表   :

修改历史   :
1.日	期	 : 2012年10月24日
作	  者   : 陈易超 00209607
修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
1 头文件包含
*****************************************************************************/

#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/semaphore.h>
#include <linux/kthread.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/sched.h>
#include <linux/sched/rt.h>
#include <linux/delay.h>
#include <linux/freezer.h>
#include <linux/completion.h>
#include <linux/wakelock.h>
#include <linux/wait.h>
#include <linux/spinlock.h>

#ifndef _DRV_LLT_
//#include "excDrv.h"
//#include "BSP.h"
#endif
#include "drv_mailbox_cfg.h"
#include "drv_mailbox_debug.h"
//#include "drv_mailbox_linux.h"
#include "bsp_drv_ipc.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 可维可测信息中包含的C文件编号宏定义
*****************************************************************************/
#undef	_MAILBOX_FILE_
#define _MAILBOX_FILE_	 "linux"
/*lint -e750*/
#define MAILBOX_MILLISEC_PER_SECOND 					  1000

#define  MAILBOX_LINUX_SEND_FULL_DELAY_MS				  10		 /*发送满延迟毫秒*/

#define  MAILBOX_LINUX_SEND_FULL_DELAY_TIMES			  0 		 /*发送满延迟再尝试次数*/

enum MAILBOX_LOCK_TYPE
{
	MAILBOX_LOCK_SEMAPHORE = 0x00010000,
	MAILBOX_LOCK_SPINLOCK  = 0x00020000
};
/*****************************************************************************
  定义C核vxworks操作系统中邮箱数据的处理接口调用方式
*****************************************************************************/
#define MAILBOX_PROC_MASK  0x0000ffff
enum MAILBOX_LINUX_PROC_STYLE_E
{
    MAILBOX_SEND   = 0,  
    
    MAILBOX_RECEV_START,
    
    /*挂接在任务上的邮件处理队列开始*/
    MAILBOX_RECV_TASK_START,
    MAILBOX_RECV_TASK_NORMAL,
    MAILBOX_RECV_TASK_HIGH,

    /*挂接在任务上的邮件处理队列结束*/
    MAILBOX_RECV_TASK_END,

    /*tasklet里面处理的消息*/
    MAILBOX_RECV_TASKLET,
    MAILBOX_RECV_TASKLET_HI,

    /*在中断中处理的邮件处理队列*/
    MAILBOX_RECV_INT_IRQ,
    MAILBOX_RECV_END,
};

/*****************************************************************************
    定义C核邮箱单个任务挂接的邮箱工作队列及其数据
*****************************************************************************/
struct mb_local_work
{
    unsigned int             channel_id;      /*邮箱ID号，可能是核间连接ID,也可能是物理通道ID*/
    unsigned int             data_flag;       /*此邮箱是否有数据的标志位*/
    int		      (*cb)(unsigned int channel_id);
    struct mb_local_work            *next;          /*指向下一条*/
#ifdef MAILBOX_OPEN_MNTN                                  
    void                     *mb_priv;
#endif
};

/*****************************************************************************
  定义C核邮箱任务相关的数据
*****************************************************************************/
struct mb_local_proc
{
    signed char                 proc_name[16];   /*处理方式名字*/
    unsigned int               proc_id;         /*处理方式ID号*/
    signed int                 priority;       /*任务优先级*/
    struct mb_local_work       *work_list;      /*此任务挂接的邮箱处理队列*/
    wait_queue_head_t           wait;           /*任务方式等待的消息*/
    struct tasklet_struct       tasklet;        /*tasklet方式的句柄*/
    int                         incoming;

};

/*****************************************************************************
  定义邮箱物理通道和任务，核间中断及接收回调函数之间的对应关系
*****************************************************************************/
struct mb_local_cfg
{
    unsigned int               channel_id;      /*邮箱通道ID。*/
    unsigned int               property;      /*通道属性*/
    unsigned int               int_src;         /*邮箱通道所使用的核间中断资源号。*/
    unsigned int               dst_id;          /*邮箱通道所使用的核间中断目标CPU号*/
};

struct mb_mutex
{
    void          *lock;
    unsigned long  flags;
    unsigned int  type;
};

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
static struct wake_lock mb_lpwr_lock; /*防止在唤醒后，处理邮件过程中进入睡眠*/

/*邮箱任务属性列表*/
MAILBOX_LOCAL struct mb_local_proc g_mailbox_local_proc_tbl[] =
{
    /*任务方式的邮件数据处理*/
    {"mailboxNormal",   MAILBOX_RECV_TASK_NORMAL,   86,  0, },
    {"mailboxHigh",     MAILBOX_RECV_TASK_HIGH,     99,  0, },

    /*tasklet 方式处理消息*/
    {"mailboxTasklet",  MAILBOX_RECV_TASKLET,     0,  0, },
    {"mailboxTasklet",  MAILBOX_RECV_TASKLET_HI,     0,  0, },

    /*中断方式的邮件数据处理*/
    {"mailboxInt",      MAILBOX_RECV_INT_IRQ,     0,  0, },

    /*请在此后新增处理方式项目，否则会影响UT用例*/

    /*结束*/
};

/*A核的邮箱通道资源与平台系统资源对应关系配置表*/
MAILBOX_LOCAL struct mb_local_cfg g_mb_local_cfg_tbl[] =
{
    /*接收通道的配置*/
    /*ChannelID*/                                   /*通道属性*/             
    {MAILBOX_MAILCODE_RESERVED(MCU,  ACPU, MSG),    MAILBOX_RECV_TASKLET_HI,     0    },
    {MAILBOX_MAILCODE_RESERVED(HIFI, ACPU, MSG),    MAILBOX_RECV_TASKLET_HI,     0    },
    {MAILBOX_MAILCODE_RESERVED(CCPU, ACPU, MSG),    MAILBOX_RECV_TASKLET_HI,     0    },
    {MAILBOX_MAILCODE_RESERVED(CCPU, ACPU, IFC),    MAILBOX_RECV_TASK_NORMAL,   0    },
    {MAILBOX_MAILCODE_RESERVED(MCU, ACPU, IFC),     MAILBOX_RECV_TASK_HIGH,   0    },

    /*发送通道配置*/
    /*ChannelID*/                                   /*通道属性*/                
    {MAILBOX_MAILCODE_RESERVED( ACPU, MCU,  MSG),   MAILBOX_SEND | MAILBOX_LOCK_SPINLOCK,   0    },
    {MAILBOX_MAILCODE_RESERVED( ACPU, HIFI, MSG),   MAILBOX_SEND | MAILBOX_LOCK_SPINLOCK,   0    },

    {MAILBOX_MAILCODE_RESERVED( ACPU, CCPU, MSG),   MAILBOX_SEND |
     MAILBOX_LOCK_SEMAPHORE /*如果消息通道作为IFC的返回通道，且这个IFC执行方的
                               函数有睡眠动作，此消息通道就只能用信号量来保护*/
    ,   0    },
    
    {MAILBOX_MAILCODE_RESERVED( ACPU, CCPU, IFC),   MAILBOX_SEND | MAILBOX_LOCK_SEMAPHORE,   0    },
    {MAILBOX_MAILCODE_RESERVED( ACPU, MCU,  IFC),   MAILBOX_SEND | MAILBOX_LOCK_SEMAPHORE,   0    },
    
    /*请在此后新增通道配置，否则会影响UT用例*/

    /*结束标志*/
    {MAILBOX_MAILCODE_INVALID, 0,0}
};

MAILBOX_LOCAL void *mailbox_mutex_create(struct mb_local_cfg *local_cfg);
/*****************************************************************************
  3 函数定义
*****************************************************************************/
MAILBOX_LOCAL void mailbox_receive_process(unsigned long data)
{
    struct mb_local_proc *proc = (struct mb_local_proc *)data;
    struct mb_local_work *work = proc->work_list;

    
    while (MAILBOX_NULL != work) {
        /*遍历标志位，如果有置位，调用对应的邮箱ID号的回调函数*/
        if (MAILBOX_TRUE == work->data_flag) {
            work->data_flag = MAILBOX_FALSE;
#ifdef MAILBOX_OPEN_MNTN                              
            mailbox_record_sche_recv(work->mb_priv);
#endif               
            if (MAILBOX_NULL != work->cb) {
                if (MAILBOX_OK !=  work->cb(work->channel_id))
                {
                     mailbox_logerro_p1(MAILBOX_ERR_LINUX_CALLBACK_ERRO, work->channel_id);
                }
            } else {
                mailbox_logerro_p1(MAILBOX_ERR_LINUX_CALLBACK_NOT_FIND, work->channel_id);
                #ifdef _DRV_LLT_
                goto process_exit;
                #endif
            }
        }
        work = work->next;
    }
#ifdef _DRV_LLT_
process_exit:
#endif
    wake_unlock(&mb_lpwr_lock);
}
/*****************************************************************************
 函 数 名  : mailbox_receive_task
 函数类型  : 对内接口
 功能描述  : 数据接收任务函数调度
 输入参数  :struct mb_local_proc *pProcCfg - 邮箱任务处理配置句柄

 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月19日
    作    者   : 莫南 00176101
    修改内容   : 新生成函数

*****************************************************************************/
MAILBOX_LOCAL int mailbox_receive_task(void * data)
{
    struct mb_local_proc *proc = (struct mb_local_proc *)data;
    struct sched_param param;

    param.sched_priority = (proc->priority < MAX_RT_PRIO) ? proc->priority : (MAX_RT_PRIO-1);
    (void)sched_setscheduler(current, SCHED_FIFO, &param);

#ifndef _DRV_LLT_
    /*set_freezable();*/          /*  advised by l56193         */
#endif

    do {
        wait_event(proc->wait, proc->incoming);
        proc->incoming = MAILBOX_FALSE;

        mailbox_receive_process((unsigned long)data);
        
    }while (!kthread_should_stop());
    return MAILBOX_OK;
}

/*本邮箱核的对外提供接口*/
/*****************************************************************************
 函 数 名  : mailbox_init_platform
 接口类型  : 对外接口
 功能描述  : 邮箱模块平台适配部分初始化,初始化邮箱并初始化与平台相关的差异化部分，在邮箱初始化的时候调用。
 输入参数  :

 输出参数  : 无
 返 回 值  : 线程操作句柄
 调用函数  :
 被调函数  : mailbox_init_platform()

 修改历史      :
  1.日    期   : 2012年9月24日
    作    者   : 莫南 00176101
    修改内容   : 新生成函数

*****************************************************************************/
MAILBOX_EXTERN int mailbox_init_platform(void)
{
    struct mb_local_proc     *local_proc    = &g_mailbox_local_proc_tbl[0];
    unsigned int            count    =  sizeof(g_mailbox_local_proc_tbl) / sizeof(struct mb_local_proc);
    unsigned int            proc_id;
    struct task_struct *task = MAILBOX_NULL;

    wake_lock_init(&mb_lpwr_lock, WAKE_LOCK_SUSPEND, "mailbox_low_power_wake_lock");

    /*创建平台任务中断信号量部分*/
    while(count) {
        /*为任务处理方式的邮箱通道创建任务*/
        proc_id = local_proc->proc_id;
        if((proc_id > MAILBOX_RECV_TASK_START) && (proc_id < MAILBOX_RECV_TASK_END)) {
            
            /* 创建邮箱接收任务等待信号量*/
            init_waitqueue_head(&local_proc->wait);
                
            /* 创建邮箱收数据处理任务*/
            task = kthread_run(mailbox_receive_task, (void*)local_proc, local_proc->proc_name);
            if (IS_ERR(task)) {
                return mailbox_logerro_p1(MAILBOX_ERR_LINUX_TASK_CREATE, proc_id);
            }
        }

        if ((MAILBOX_RECV_TASKLET == proc_id) || 
           (MAILBOX_RECV_TASKLET_HI == proc_id)) {
	        tasklet_init(&local_proc->tasklet,
		    mailbox_receive_process, (unsigned long)local_proc);
        
        }
        count--;
        local_proc++;
    }

    return MAILBOX_OK;
}

/*****************************************************************************
 函 数 名  : mailbox_ipc_process
 接口类型  : 对内接口
 功能描述  : 设置根据邮件号设置对应的邮件工作队列标志位，并发送消息通知邮箱任务。
 输入参数  :  struct mb_local_work *pQueueList   --  邮箱工作队列
              struct mb_local_proc    *pMailBoxTask --  邮箱处理句柄
              unsigned long ChannelId -- 邮箱通道号
              unsigned long ProcId    -- 邮箱通道处理方式ID
 输出参数  : 无
 返 回 值  : 成功或者失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月24日
    作    者   : 莫南 00176101
    修改内容   : 新生成函数

*****************************************************************************/
MAILBOX_LOCAL int mailbox_ipc_process(
                struct mb_local_work  *local_work,
                struct mb_local_proc  *local_proc,
                unsigned int channel_id,
                unsigned int proc_id)
{
    unsigned int is_find = MAILBOX_TRUE;

    while (local_work) {
        /*从邮箱工作队列中找到对应的邮箱，设置标志位并释放信号量通知处理任务*/
        if (channel_id  == local_work->channel_id) {
            /*设置任务邮箱工作队列链表中此邮箱的数据标志位*/
            local_work->data_flag = MAILBOX_TRUE;
            
#ifdef MAILBOX_OPEN_MNTN              
            mailbox_record_sche_send(local_work->mb_priv);
#endif             
            wake_lock(&mb_lpwr_lock);

            if ((proc_id > MAILBOX_RECV_TASK_START)
                && (proc_id < MAILBOX_RECV_TASK_END)) {
             
                /*释放信号量，通知任务*/
                local_proc->incoming = MAILBOX_TRUE;
                wake_up(&local_proc->wait);

            } else if(MAILBOX_RECV_TASKLET_HI == proc_id) {
                 /*tasklet处理方式，在tasklet中处理邮箱数据*/
                tasklet_hi_schedule(&local_proc->tasklet);
                 
            } else if(MAILBOX_RECV_TASKLET == proc_id) {
                 /*tasklet处理方式，在tasklet中处理邮箱数据*/
                tasklet_schedule(&local_proc->tasklet);
                 
            } else if(MAILBOX_RECV_INT_IRQ == proc_id) {
                /*中断处理方式，在中断中直接处理邮箱数据*/
                mailbox_receive_process((unsigned long)local_proc);
                
            } else {
                is_find = MAILBOX_FALSE;
            }

		}

		local_work = local_work->next;
	}

	return is_find;
}

/*****************************************************************************
 函 数 名  : mailbox_ipc_int_handle
 接口类型  : 对内接口
 功能描述  : 设置根据邮件号设置对应的邮件工作队列标志位，并发送消息通知邮箱任务。
 输入参数  :  unsigned long    MailBoxID  --邮箱内部的邮箱号，邮箱内部定义的全系统唯一的序列号，


 输出参数  : 无
 返 回 值  : 成功或者失败
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年9月24日
	作	  者   : 莫南 00176101
	修改内容   : 新生成函数

*****************************************************************************/
MAILBOX_LOCAL int mailbox_ipc_int_handle(unsigned int int_num)
{
    struct mb_local_cfg         *local_cfg    =  &g_mb_local_cfg_tbl[0];
    struct mb_local_proc        *local_proc   =   MAILBOX_NULL;
    struct mb_local_work        *local_work      =   MAILBOX_NULL;
    unsigned int count = sizeof(g_mailbox_local_proc_tbl)/sizeof(struct mb_local_proc);
    unsigned int proc_id = 0;
    unsigned int channel_id = 0;
    unsigned int is_find = MAILBOX_FALSE;
    unsigned int ret_val = MAILBOX_OK;

    /*找到传入ID对应的邮箱配置*/
    while (MAILBOX_MAILCODE_INVALID != local_cfg->channel_id) {
        /*处理所有挂接到这个中断号的接收邮箱通道*/
        proc_id = local_cfg->property;
        if ((int_num == local_cfg->int_src) && (MAILBOX_SEND 
              != (MAILBOX_PROC_MASK & local_cfg->property))) {
            channel_id = local_cfg->channel_id;


            local_proc   =  &g_mailbox_local_proc_tbl[0];
            count          =   sizeof(g_mailbox_local_proc_tbl)/sizeof(struct mb_local_proc);
            while (count) {
                /*找到此邮箱通道对应的任务信息*/
                if (proc_id == local_proc->proc_id) {
                    local_work = local_proc->work_list;
                    is_find = mailbox_ipc_process( local_work,
                                                 local_proc,
                                                 channel_id,
                                                 proc_id);
                    break;
                }
                count--;
                local_proc++;
            }

			if (0 == count) {
				ret_val = mailbox_logerro_p1(MAILBOX_ERR_LINUX_MAIL_TASK_NOT_FIND, channel_id);
			}
		}
		local_cfg++;
	}

	if (MAILBOX_TRUE != is_find) {
		ret_val = mailbox_logerro_p1(MAILBOX_ERR_LINUX_MAIL_INT_NOT_FIND, channel_id);
	}

	return ret_val;
}

/*****************************************************************************
 函 数 名  : mailbox_process_register
 接口类型  : 对外接口
 功能描述  : 建立MailBoxID和pProcessCallBack相关一套机制，根据MailBoxID注册本系统的对应核间邮件通知中断，
				在收到邮件通知以后，调用对应的pProcessCallBack回调函数
 输入参数  :  unsigned long 			   MailBoxID  --邮箱内部的邮箱号，邮箱内
											部定义的全系统唯一的序列号，
											   --此ID的内部结构由DRV_MAILBOX_ID_STRU定义。
			 MAILBOX_PROCSS_FUNCPTR pMainThreadCallBack --邮箱收到邮件后的处理回调函数,
												此函数的入口参数是上面的参数MailBoxID的值

 输出参数  : 无
 返 回 值  : 成功或者失败
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年9月24日
	作	  者   : 莫南 00176101
	修改内容   : 新生成函数

*****************************************************************************/
MAILBOX_EXTERN int mailbox_process_register(
                unsigned int channel_id, 
                 int (*cb)(unsigned int channel_id),
                 void *priv)
{
    struct mb_local_work        *local_work    =   MAILBOX_NULL;
    struct mb_local_cfg         *local_cfg  =  &g_mb_local_cfg_tbl[0];
    struct mb_local_proc        *local_proc =  &g_mailbox_local_proc_tbl[0];
    struct mb_local_cfg*         find_cfg     =   MAILBOX_NULL;
    unsigned int count = sizeof(g_mailbox_local_proc_tbl)/sizeof(struct mb_local_proc);

	while (MAILBOX_MAILCODE_INVALID != local_cfg->channel_id) {
		/*找到与传入邮箱ID最适配的系统邮箱配置*/
		if (local_cfg->channel_id ==  channel_id) {
			find_cfg = local_cfg;
			break;
		}
		local_cfg++;
	}

	if (find_cfg) {
		/*加入邮箱任务对应的邮箱工作队列*/
		while (count) {
			if (find_cfg->property == local_proc->proc_id) {
				if (local_proc->work_list) {
					local_work = local_proc->work_list;
					while (MAILBOX_NULL != local_work->next) {
						local_work = local_work->next;
					}
					local_work->next			= (struct mb_local_work *)kcalloc(
													  sizeof(struct mb_local_work), 1, GFP_KERNEL);
					if (NULL == local_work->next)  {
						(void)printk(KERN_ERR "%s: memory alloc error!\n",__func__);
						return MAILBOX_ERR_LINUX_ALLOC_MEMORY;
					}
					local_work->next->channel_id = find_cfg->channel_id;
					local_work->next->cb  = cb;
					local_work->next->next = MAILBOX_NULL;
					local_work->next->mb_priv = priv;

				} else {
					local_proc->work_list	  = (struct mb_local_work *)kcalloc(
													sizeof(struct mb_local_work), 1, GFP_KERNEL);
					if (NULL == local_proc->work_list) {
						(void)printk(KERN_ERR "%s: memory alloc error!\n",__func__);
						return MAILBOX_ERR_LINUX_ALLOC_MEMORY;
					}
					local_proc->work_list->channel_id = find_cfg->channel_id;
					local_proc->work_list->cb  = cb;
					local_proc->work_list->next = MAILBOX_NULL;
					local_proc->work_list->mb_priv = priv;
				}

			}
			count--;
			local_proc++;
		}

		return MAILBOX_OK;
	}

	return	mailbox_logerro_p1(MAILBOX_ERR_LINUX_CHANNEL_NOT_FIND, channel_id);

}

/*****************************************************************************
 函 数 名  : mailbox_channel_register
 接口类型  : 对外接口
 功能描述  : 把邮箱通道配置注册到具体操作系统平台
 输入参数  :  unsigned long ChannelID -- 邮箱通道号
			  unsigned long IntNum	  -- 中断号
			  unsigned long Direct	  -- 发送方向
			  void	 **mutex		  -- 此通道的资源保护锁
 输出参数  : 无
 返 回 值  : 成功或者失败
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年9月24日
	作	  者   : 莫南 00176101
	修改内容   : 新生成函数

*****************************************************************************/
MAILBOX_EXTERN int mailbox_channel_register(
                unsigned int channel_id,
                unsigned int int_src,
                unsigned int dst_id,
                unsigned int direct,
                void   **mutex)
{
	struct mb_local_cfg    *local_cfg  =  &g_mb_local_cfg_tbl[0];
	while (MAILBOX_MAILCODE_INVALID != local_cfg->channel_id) {
		if (channel_id == local_cfg->channel_id) {
			*mutex = mailbox_mutex_create(local_cfg);
			if (MAILBOX_NULL == *mutex) {
				return mailbox_logerro_p1(MAILBOX_CRIT_PORT_CONFIG, channel_id);
			}

			/*通道资源配置已找到，注册IPC中断*/
			local_cfg->int_src = int_src;
			local_cfg->dst_id  = dst_id;

			if(MIALBOX_DIRECTION_RECEIVE == direct) {
				IPC_IntConnect((IPC_INT_LEV_E)int_src , (VOIDFUNCPTR)mailbox_ipc_int_handle, int_src);
				IPC_IntEnable ((IPC_INT_LEV_E)int_src);

				/*板侧ST用例通道注册*/
				//test_mailbox_msg_reg(channel_id);
			}
			break;
		}

		local_cfg++;
	}

	/*如果适配层找不到对应的配置，报错*/
	if (MAILBOX_MAILCODE_INVALID == local_cfg->channel_id) {
		return mailbox_logerro_p1(MAILBOX_ERR_LINUX_CHANNEL_NOT_FIND, channel_id);
	}

	return MAILBOX_OK;
}

/*****************************************************************************
 函 数 名  : mailbox_delivery
 接口类型  : 对外接口
 功能描述  : 通知对方核接收邮件。
 输入参数  : unsigned long MailBoxID	-	全系统唯一的邮箱通道ID号

 输出参数  : 无
 返 回 值  : 成功或者失败
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年9月24日
	作	  者   : 莫南 00176101
	修改内容   : 新生成函数

 详细描述: 在写完新邮件后，发送核间通知，通知对方核接收邮件。
*****************************************************************************/
MAILBOX_EXTERN int mailbox_delivery(unsigned int channel_id)
{
	struct mb_local_cfg 	*local_cfg	  =  &g_mb_local_cfg_tbl[0];
	struct mb_local_cfg 	*find_cfg		=	MAILBOX_NULL;

	channel_id = channel_id;
	while (MAILBOX_MAILCODE_INVALID != local_cfg->channel_id) {
		/*找到与传入邮箱ID最适配的系统邮箱配置*/
		if (local_cfg->channel_id == channel_id) {
			find_cfg = local_cfg;
			break;
		}
		local_cfg++;
	}

    if (MAILBOX_NULL != find_cfg) {
        return (int)IPC_IntSend((IPC_INT_CORE_E)find_cfg->dst_id,
                                (IPC_INT_LEV_E)find_cfg->int_src);
    }

	return mailbox_logerro_p1(MAILBOX_ERR_LINUX_CHANNEL_NOT_FIND, channel_id);
}


/*****************************************************************************
 函 数 名  : mailbox_mutex_create
 功能描述  : 创建邮箱资源多线程互斥信号量
 输入参数  : void
 输出参数  : 无
 返 回 值  : 成功返回句柄或者失败返回空
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年9月24日
	作	  者   : 莫南 00176101
	修改内容   : 新生成函数

*****************************************************************************/
MAILBOX_LOCAL void *mailbox_mutex_create(struct mb_local_cfg *local_cfg)
{
    unsigned int channel_id = local_cfg->channel_id;
	struct mb_mutex* mtx = MAILBOX_NULL;

	/*根据不同通道类型申请不同的资源保护锁*/
	mtx = (struct mb_mutex*)kmalloc(sizeof(struct mb_mutex), GFP_KERNEL);
	if (!mtx) {
		mailbox_logerro_p1(MAILBOX_ERR_LINUX_CHANNEL_NOT_FIND, channel_id);
		goto error_exit;
	}

	if ((local_cfg->property > MAILBOX_RECEV_START) &&
		(local_cfg->property < MAILBOX_RECV_END)) {
		/*接收通道互斥使用自旋锁，用于回调注册保护*/
		mtx->lock = kmalloc(sizeof(spinlock_t), GFP_KERNEL);
		if (mtx->lock) {
			spin_lock_init((spinlock_t*)mtx->lock);
			mtx->type = MAILBOX_LOCK_SPINLOCK;
		} else {
			mailbox_logerro_p1(MAILBOX_CRIT_PORT_CONFIG, channel_id);
			goto error_exit;
		}
	} else {
		if (MAILBOX_LOCK_SEMAPHORE & local_cfg->property) {
			mtx->lock = kmalloc(sizeof(struct semaphore), GFP_KERNEL);
			if (mtx->lock) {
				sema_init(mtx->lock, 1);
				mtx->type = MAILBOX_LOCK_SEMAPHORE;
			} else {
				mailbox_logerro_p1(MAILBOX_CRIT_PORT_CONFIG, channel_id);
				goto error_exit;
			}
		} else if (MAILBOX_LOCK_SPINLOCK & local_cfg->property) {
			mtx->lock = kmalloc(sizeof(spinlock_t), GFP_KERNEL);
			if (mtx->lock) {
				spin_lock_init((spinlock_t*)mtx->lock);
				mtx->type = MAILBOX_LOCK_SPINLOCK;
			} else {
				mailbox_logerro_p1(MAILBOX_CRIT_PORT_CONFIG, channel_id);
				goto error_exit;
			}
		} else {
			mailbox_logerro_p1(MAILBOX_CRIT_PORT_CONFIG, channel_id);
			goto error_exit;
		}
	}
	return mtx;

error_exit:
	if (mtx)
		kfree(mtx);

	return (void *)0;
}

/*****************************************************************************
 函 数 名  : mailbox_mutex_lock
 功能描述  : 邮箱通道资源互斥进入
 输入参数  : void **mutexId  指向互斥操作句柄的指针
 输出参数  : 无
 返 回 值  : 成功或者失败
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年9月24日
	作	  者   : 莫南 00176101
	修改内容   : 新生成函数

 详细描述: 使用等信号量或者锁中断方式实现,对多任务访问的较大段代码或资源进行保护。

*****************************************************************************/
MAILBOX_EXTERN int mailbox_mutex_lock(void **mutexId)
{
	struct mb_mutex *mtx = (struct mb_mutex *)*mutexId;

	if (MAILBOX_LOCK_SEMAPHORE == mtx->type ) {
		down((struct semaphore*)mtx->lock);
	} else if (MAILBOX_LOCK_SPINLOCK == mtx->type ) {
		spin_lock_irqsave((spinlock_t*)mtx->lock, mtx->flags);
	}

	return MAILBOX_OK;
}

/*****************************************************************************
 函 数 名  : mailbox_mutex_lock
 功能描述  : 邮箱通道资源互斥退出
 输入参数  : void **mutexId  指向互斥操作句柄的指针
 输出参数  : 无
 返 回 值  : 成功或者失败
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年9月24日
	作	  者   : 莫南 00176101
	修改内容   : 新生成函数

 详细描述: 使用释放信号量或者解锁中断方式实现

*****************************************************************************/
MAILBOX_EXTERN void mailbox_mutex_unlock(void **mutexId)
{
	struct mb_mutex *mtx = (struct mb_mutex *)*mutexId;

	if (MAILBOX_LOCK_SEMAPHORE == mtx->type ) {
		up((struct semaphore*)mtx->lock);
	} else	if (MAILBOX_LOCK_SPINLOCK == mtx->type ) {
		spin_unlock_irqrestore((spinlock_t*)mtx->lock, mtx->flags);
	}

	return ;
}

MAILBOX_EXTERN void *mailbox_init_completion(void)
{
	struct completion *wait;
	wait = (struct completion*)kmalloc(sizeof(struct completion), GFP_KERNEL);
	if(!wait) {
		return MAILBOX_NULL;
	}
	init_completion(wait);

	return (void*)wait;
}

MAILBOX_EXTERN int mailbox_wait_completion(void **wait, unsigned int timeout)
{
	long jiffies = msecs_to_jiffies(timeout);
	long ret =	wait_for_completion_timeout(*wait, jiffies);

	return (ret > 0) ? MAILBOX_OK : MAILBOX_ERRO ;
}

MAILBOX_EXTERN void mailbox_complete(void **wait)
{
	complete(*wait);
}

MAILBOX_EXTERN void mailbox_del_completion(void **wait)
{
	kfree(*wait);
}

/*****************************************************************************
 函 数 名  : mailbox_memcpy
 功能描述  : 内存拷贝函数
 输入参数  : void		*Destination  -- 目的地址
			 const void *Source 	  -- 源地址
			 long		 Size		   -- 长度
 输出参数  : 无
 返 回 值  : 成功或者失败
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年11月07日
	作	  者   : 莫南 00176101
	修改内容   : 新生成函数

 详细描述: 实现memcpy功能

*****************************************************************************/
MAILBOX_EXTERN void *mailbox_memcpy(void *Destination, const void *Source, unsigned int Size)
{

	return (void *)memcpy(Destination, Source, Size);
}

/*****************************************************************************
 函 数 名  : mailbox_memset
 功能描述  : 内存拷贝函数
 输入参数  : void		*Destination  -- 目的地址
			 const void *Source 	  -- 源地址
			 long		 Size		   -- 长度
 输出参数  : 无
 返 回 值  : 成功或者失败
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年11月07日
	作	  者   : 莫南 00176101
	修改内容   : 新生成函数

 详细描述: 实现memset功能

*****************************************************************************/
MAILBOX_EXTERN void *mailbox_memset(void * m, int c, unsigned int size)
{

	return memset(m, c, size);
}

/*****************************************************************************
 函 数 名  : mailbox_assert
 功能描述  : 异常断言，用于调试。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功或者失败
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年9月24日
	作	  者   : 莫南 00176101
	修改内容   : 新生成函数
*****************************************************************************/
MAILBOX_EXTERN void mailbox_assert(unsigned int ErroNo)
{
#ifndef _DRV_LLT_

#endif
}

/*****************************************************************************
 函 数 名  : mailbox_int_context
 功能描述  : 检查是不是在中断上下文中
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功或者失败
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年10月25日
	作	  者   : 莫南 00176101
	修改内容   : 新生成函数
*****************************************************************************/
MAILBOX_EXTERN int mailbox_int_context(void)
{
#ifdef _DRV_LLT_
	return 0;
#else
	return	in_interrupt();
#endif
}


/*****************************************************************************
 函 数 名  : mailbox_scene_delay
 功能描述  : 根据传入的场景号，进行延迟并返回新状态
 输入参数  : unsigned long SceneID		--	延时场景号
			 unsigned long TryTimes 	--	此场景第几次等待
 输出参数  : 无
 返 回 值  : 是否继续等待
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年11月29日
	作	  者   : 莫南 00176101
	修改内容   : 新生成函数
*****************************************************************************/
MAILBOX_EXTERN int mailbox_scene_delay(unsigned int scene_id, int *try_times)
{
    unsigned int go_on = MAILBOX_FALSE;
    unsigned int delay_ms = 0;

    switch (scene_id)
    {
        case MAILBOX_DELAY_SCENE_MSG_FULL:
        case MAILBOX_DELAY_SCENE_IFC_FULL:

			delay_ms = MAILBOX_LINUX_SEND_FULL_DELAY_MS;

			go_on = (*try_times >= MAILBOX_LINUX_SEND_FULL_DELAY_TIMES) ?
					MAILBOX_FALSE : MAILBOX_TRUE;

			break;
		default:

			break;
	}

	if (MAILBOX_TRUE == go_on) {
		msleep(delay_ms);
	}

	*try_times = *try_times + 1;
	return go_on;
}

/*****************************************************************************
 函 数 名  : mailbox_get_timestamp
 功能描述  : 获得时间戳
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 系统时间戳，单位(us)
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年10月16日
	作	  者   : 莫南 00176101
	修改内容   : 新生成函数

函数描述: 整个系统的时间戳，各个CPU共用，作为消息滞留时间或者处理时间的参照。
*****************************************************************************/
extern void * g_slice_reg;
MAILBOX_EXTERN int mailbox_get_timestamp(void)
{
#ifndef _DRV_LLT_
	if (g_slice_reg) {
		return (long)readl(g_slice_reg);
	}
	return 0;
#else
	return 0;
#endif

}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

