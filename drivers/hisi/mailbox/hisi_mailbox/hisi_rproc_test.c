#include <linux/module.h>
#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/semaphore.h>
#include <linux/kthread.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/syscalls.h>
#include <linux/time.h>
#include <linux/hisi/hisi_rproc.h>
#include <linux/hisi/ipc_msg.h>
/*total pressure times once*/
#define PRESSURE_TIMES  500
#define PERFORMANC_TIMES 100
/*show only 5 middle time cost*/
#define PERFORMANC_SHOW_NUM  5
#define PERFORMANC_SHOW_INDEX   (PERFORMANC_TIMES/PERFORMANC_SHOW_NUM)
/*the standard time cost, if longer, failed */
#define PERFORMANC_FAIL_NSEC  2000000
#define SYNC_SEND  1
#define ASYNC_SEND  2

#define test_rproc_get_slice()		(0xFFFFFFFF)
#define TEST_RPROC_NULL		((void*)0)
#define test_rproc_slice_diff(s,e)	(((e) >= (s))?((e) - (s)) : (0xFFFFFFFF - (s) + (e)))

struct test_rproc_cb
{
    void *           done_sema;
    void *           sync_sema;
    unsigned int    start_slice;       /*for calculate boundwidth*/
    unsigned int    end_slice;         /*for calculate boundwidth*/
    unsigned int    msg_count;
    unsigned int    sync_task_cnt;
    unsigned int    done_task_cnt;
    int    		    check_ret;
};

typedef int (*test_rproc_send_func)(unsigned int sync_id, 
	unsigned char rp_id, 
	unsigned int msg_len, 
	unsigned int msg_num,
	struct test_rproc_cb *rproc_cb);

struct test_rproc_proc
{
	test_rproc_send_func proc_cb;
	unsigned int sync_id;
	unsigned char rp_id;
	unsigned int msg_len;
	unsigned int msg_num;
	unsigned int task_num;
	struct test_rproc_cb *rproc_cb;
};

static char data_buf[] = "hello, the message looping back.";
static struct semaphore send_mutex_sema;
static struct semaphore task_mutex_sema;
static struct notifier_block nb;
int interval_v = 0;


int test_rproc_msg_send(unsigned int sync_id, 
		unsigned char rp_id,
		unsigned int msg_len,
		unsigned int msg_num, 
		struct test_rproc_cb *rproc_cb)
{
	int ret = 0;
	rproc_msg_t tx_buffer[8] = {0};
	rproc_msg_t ack_buffer[8] = {0};
	struct semaphore *complete_sema;
	unsigned int start_slice = 0;
	unsigned int end_slice = 0;
    unsigned int sync_task_cnt = 0;

	if (sync_id > 0x3) {
		printk(KERN_ERR "wrong sync id!\n");
		return -1;
	}

	if (msg_len > 8) {
		printk(KERN_ERR "illegal message length!\n");
		return -1;
	}

	if(rproc_cb) {
        down(&task_mutex_sema);
		rproc_cb->sync_task_cnt--;
        sync_task_cnt = rproc_cb->sync_task_cnt;
        up(&task_mutex_sema);
		if ((0 == sync_task_cnt) 
		&& (TEST_RPROC_NULL != rproc_cb->sync_sema)) {
			rproc_cb->start_slice = test_rproc_get_slice();
			up(rproc_cb->sync_sema);
		}

		/*进程同步*/
		if (TEST_RPROC_NULL != rproc_cb->sync_sema) {
			down(rproc_cb->sync_sema);
			up(rproc_cb->sync_sema);
		}
	}

	tx_buffer[0] = (OBJ_TEST << 16) | (CMD_TEST << 8)/*0x00120500*/;
	memcpy((void*)&tx_buffer[1], (void*)&data_buf[0], sizeof(tx_buffer) - sizeof(tx_buffer[0]));
	switch(sync_id)
	{
		case 0:/*同步发送同步消息*/
			while(msg_num--){
				ret = RPROC_SYNC_SEND(rp_id,tx_buffer, msg_len,ack_buffer,msg_len);
				if (ret || (((OBJ_TEST << 16) | (CMD_TEST << 8)) != ack_buffer[0]) || (0x12345678 != ack_buffer[1])) {
					printk(KERN_ERR "rproc send error, ret %d, rp %d, sync %d, ack[0x%x][0x%x]!\r\n", 
							ret, rp_id, sync_id, ack_buffer[0], ack_buffer[1]);
					return -1;
				}
				if(rproc_cb)
					rproc_cb->msg_count++;
			}
			break;

		case 1:/*同步发送异步消息*/
			while(msg_num--){
				ret = RPROC_SYNC_SEND(rp_id ,tx_buffer, msg_len,NULL,0);
				if (ret) {
					printk(KERN_ERR "rproc send error, ret %d, rp %d, sync %d!\r\n", ret, rp_id, sync_id);
					return -1;
				}
				if(rproc_cb)
					rproc_cb->msg_count++;
			}
			break;

		case 2:/*异步发送同步消息*/
			while (msg_num--) {
				complete_sema = (struct semaphore*)kmalloc(sizeof(struct semaphore), GFP_KERNEL);
				sema_init(complete_sema, 0);
				ret = RPROC_ASYNC_SEND(rp_id,tx_buffer,msg_len);
				if (ret) {
					printk(KERN_ERR "rproc send error, ret %d, rp %d, sync %d!\r\n", ret, rp_id, sync_id);
					kfree(complete_sema);
					return -1;
				}
				start_slice = test_rproc_get_slice();
				if (0 != down_timeout(complete_sema, msecs_to_jiffies(1000)))
				{
					printk(KERN_ERR "msg_send timeout rp_id:%d rproc async send err!\r\n", rp_id);
					kfree(complete_sema);
					return -1;
				}
				end_slice = test_rproc_get_slice();
				printk(KERN_INFO "async send sync msg spend %d slice!\r\n",
						test_rproc_slice_diff(start_slice, end_slice));
				kfree(complete_sema);
				if(rproc_cb)
					rproc_cb->msg_count++;
			}
			break;

		case 3:/*异步发送异步消息*/
			while (msg_num--) {
				ret = RPROC_ASYNC_SEND(rp_id,tx_buffer,msg_len);
				if (ret) {
					printk(KERN_ERR "rproc send error, ret %d, rp %d, sync %d!\r\n", ret, rp_id, sync_id);
					return ret;
				}
				if(rproc_cb)
					rproc_cb->msg_count++;
			}
			break;

		default:
			printk(KERN_ERR "wrong sync ID!\n");
			return -1;
	}
	printk(KERN_INFO "rproc send ok, rp %d, sync %d!\n", rp_id, sync_id);

	return ret;
}

void test_rproc_msg_send_entry(void* _proc)
{
	struct test_rproc_proc *rproc_proc = _proc;
	struct test_rproc_cb *rproc_cb = TEST_RPROC_NULL;
    unsigned int done_task_cnt = 0;
    

	if (!rproc_proc) {
		printk(KERN_ERR "test_rproc_msg_send_entry rproc_proc is NULL\n ");
		return ;
	}

	if (!rproc_proc->proc_cb) {
		printk(KERN_ERR "test_rproc_msg_send_entry proc_cb is NULL\n ");
		kfree(rproc_proc);
		return ;
	}

	if (!rproc_proc->rproc_cb) {
		printk(KERN_ERR "test_rproc_msg_send_entry rproc_cb is NULL\n ");
		kfree(rproc_proc);
		return ;
	}

	rproc_cb = rproc_proc->rproc_cb;
	rproc_cb->check_ret = rproc_proc->proc_cb(
		rproc_proc->sync_id,
		rproc_proc->rp_id,
		rproc_proc->msg_len,
		rproc_proc->msg_num,
		rproc_cb);
	kfree(rproc_proc);

    down(&task_mutex_sema);
	rproc_cb->done_task_cnt--;
    done_task_cnt = rproc_cb->done_task_cnt;
    up(&task_mutex_sema);
	if ((0 == done_task_cnt) 
	&& (TEST_RPROC_NULL != rproc_cb->done_sema)) {
		up(rproc_cb->done_sema);
	}
}

void test_rproc_msg_create_task(test_rproc_send_func entryPtr,
                unsigned int sync_id,
                unsigned char rp_id,
                unsigned int msg_len,
                unsigned int msg_num,
                unsigned int task_num,
                struct test_rproc_cb *rproc_cb)
{
	struct test_rproc_proc *pEntryParam = kmalloc(sizeof(struct test_rproc_proc), GFP_KERNEL);
	char task_name[32] = {0};

	pEntryParam->proc_cb  = (test_rproc_send_func)entryPtr;
	pEntryParam->sync_id  = sync_id;
	pEntryParam->rp_id = rp_id;
	pEntryParam->msg_len  = msg_len;
	pEntryParam->msg_num    = msg_num;
	pEntryParam->task_num = task_num;
	pEntryParam->rproc_cb = rproc_cb;

	snprintf(task_name, sizeof(task_name), "trproc_task%d", (int)task_num);

	kthread_run((int (*)(void *))test_rproc_msg_send_entry, (void*)pEntryParam, task_name);
}

int test_rproc_msg_multi_send(unsigned int sync_id,
		unsigned char rp_id,
		unsigned int msg_len, 
		unsigned int msg_num, 
		unsigned int task_num)
{
	struct test_rproc_cb * rproc_cb = 0;
	unsigned int time_diff = 0;
	unsigned int task_num_t = task_num;
	int ret = 0;

	down(&send_mutex_sema);
	/*创建回调用户句柄*/
	rproc_cb = kcalloc(sizeof(struct test_rproc_cb), 1, GFP_KERNEL);
	if (!rproc_cb) {
		printk(KERN_ERR "error test_rproc_msg_multi_send kcalloc\n");
		up(&send_mutex_sema);
		return -1;
	}

	rproc_cb->done_sema = (struct semaphore*)kmalloc(sizeof(struct semaphore), GFP_KERNEL);
	sema_init(rproc_cb->done_sema, 0);
	rproc_cb->sync_sema = (struct semaphore*)kmalloc(sizeof(struct semaphore), GFP_KERNEL);
	sema_init(rproc_cb->sync_sema, 0);
	rproc_cb->check_ret = -1;
	rproc_cb->sync_task_cnt = task_num;
	rproc_cb->done_task_cnt = task_num;
	rproc_cb->msg_count = 0;

	/*创建诺干个任务，任务入口函数为本核往其他核发送消息的函数*/
	while (task_num) {
		test_rproc_msg_create_task(test_rproc_msg_send,
				sync_id,
				rp_id,
				msg_len,
				msg_num,
				task_num,
				rproc_cb);

		task_num--;
	}

	down(rproc_cb->done_sema);
	kfree(rproc_cb->done_sema);
	rproc_cb->done_sema = TEST_RPROC_NULL;
	kfree(rproc_cb->sync_sema);
	rproc_cb->sync_sema = TEST_RPROC_NULL;

	rproc_cb->end_slice= test_rproc_get_slice();

	time_diff = test_rproc_slice_diff(rproc_cb->start_slice, rproc_cb->end_slice);
	printk(KERN_INFO "rp: %d, sync: %d, total:%d(4byte), latency: %d (slice)\n", rp_id, sync_id,
		(int)(msg_len * msg_num * task_num_t), (int)time_diff);

	if(0 != rproc_cb->check_ret) {
		printk(KERN_ERR "test_rproc_msg_multi_send: CheckRet error\n");
		ret = -1;
	} else if(msg_num * task_num_t != rproc_cb->msg_count) {
		printk(KERN_ERR "test_rproc_msg_multi_send: MsgCount(%d) error\n", (int)rproc_cb->msg_count);
		ret = -1;
	} else {
		printk(KERN_INFO "test_rproc_msg_multi_send: Success!\n");
		ret = 0;
	}

	kfree(rproc_cb);
	up(&send_mutex_sema);
	return ret;
}

/*****************************************************************************
 函 数 名  : test_rproc_single_task
 功能描述  : 单线程对外测试函数
 输入参数  : int msg_type 0:sync 1:async
             int rp_id    rproc id
             int msg_len   邮件长度
             int msg_num   邮件数目

*****************************************************************************/
void test_rproc_single_task_sync(unsigned int msg_type, unsigned char rp_id, unsigned int msg_len, unsigned int msg_num)
{
	int ret = 0;
	unsigned int sync_id = 0;

	sync_id = (0 == msg_type) ? 0 : 1;
	ret = test_rproc_msg_multi_send(sync_id, rp_id, msg_len, msg_num, 1);
	if(0 != ret)
		printk(KERN_ERR "test_rproc_single_task_sync: Fail\r\n");
	else
		printk(KERN_ERR "test_rproc_single_task_sync: Success\r\n");
}

void test_rproc_single_task_async(unsigned int msg_type, 
	unsigned char rp_id, 
	unsigned int msg_len, 
	unsigned int msg_num)
{
	int ret = 0;
	unsigned int sync_id = 0;

	sync_id = (0 == msg_type) ? 2 : 3;
	ret = test_rproc_msg_multi_send(sync_id, rp_id, msg_len, msg_num, 1);
	if(0 != ret)
		printk(KERN_ERR "test_rproc_single_task_async: Fail\r\n");
	else
		printk(KERN_ERR "test_rproc_single_task_async: Success\r\n");
}

void test_rproc_multi_task_sync(unsigned int msg_type, 
	unsigned char task_num, 
	unsigned char rp_id, 
	unsigned int msg_len, 
	unsigned int msg_num)
{
	int ret = 0;
	unsigned int sync_id = 0;

	sync_id = (0 == msg_type) ? 0 : 1;
	ret = test_rproc_msg_multi_send(sync_id, rp_id, msg_len, msg_num, task_num);
	if(0 != ret)
		printk(KERN_ERR "test_rproc_multi_task_sync: Fail\r\n");
	else
		printk(KERN_ERR "test_rproc_multi_task_sync: Success\r\n");
}

void test_rproc_multi_task_async(unsigned int msg_type, 
	unsigned char task_num, 
	unsigned char rp_id, 
	unsigned int msg_len, 
	unsigned int msg_num)
{
	int ret = 0;
	unsigned int sync_id = 0;

	sync_id = (0 == msg_type) ? 2 : 3;
	ret = test_rproc_msg_multi_send(sync_id, rp_id, msg_len, msg_num, task_num);
	if(0 != ret)
		printk(KERN_ERR "test_rproc_multi_task_async: Fail\r\n");
	else
		printk(KERN_ERR "test_rproc_multi_task_async: Success\r\n");
}

static int mbox_recv_from_lpmcu(struct notifier_block *nb, unsigned long len, void *msg)
{
	int i;

 	pr_err("$$$$$$$$$$$$$$$$$$$$$----%s--->\n",__func__);
	for (i = 0; i < len; ++i) 
	{
	        pr_err("-------->msg[%d] = %#.8x\n",  i, ((int *)msg)[i]);
	}
	return 0;
}
        
static void test_all_sync_ipc_init(void)
{
    int ret, rproc_id = 0;
    static int times = 0;
    /*init just once*/
    if(times)
    {
        return;
    }
	rproc_id = HISI_RPROC_LPM3_MBX0;
	
	nb.next = NULL;
	nb.notifier_call = mbox_recv_from_lpmcu;

	/* register the rx notify callback */
	ret = RPROC_MONITOR_REGISTER(rproc_id, &nb);
	if (ret)
	{
		pr_err("%s:RPROC_MONITOR_REGISTER failed", __func__);
	}
    times++;
}

static int test_all_send_to_lpmcu(void *arg)
{
	rproc_msg_t ack_buffer[2] = {0};
	int err = 0;
	int index = 0;
	union ipc_data * lpm3Msg = NULL;
	int syntypye = 0;
	int idata = 0;
	
	lpm3Msg = (union ipc_data * )kmalloc(sizeof(union ipc_data), GFP_KERNEL);

	lpm3Msg->cmd_mix.cmd_src = OBJ_AP;
	lpm3Msg->cmd_mix.cmd_obj = OBJ_LPM3;
	lpm3Msg->cmd_mix.cmd  = CMD_SETTING;
	lpm3Msg->cmd_mix.cmd_type = TYPE_TEST;	
/*****************************************************************************************************
	data[0]: 0x0008030D 
	data[1]: 0xAABBCCDD
	AA: 00(sec or not)
	BB: mailbox id, lpmcu-->ap is 0
	CC: dest core (1:A53, 2:Maia, 4:Sensorhub, 8:LPMCU, 16:HIFI, 32:MODEM, 64:BBE16, 128:IVP)
	DD:	mode, 1 for autoack
*****************************************************************************************************/	
	lpm3Msg->data[0] = 0x0008030F;
	lpm3Msg->data[1] = 0x01000101;
	
	while(1)
	{
		syntypye++;
		idata++;
		if(0 == syntypye%10000)
		{
			pr_err("xxxxxxxxx pressure test have succeed %d cycles\n",syntypye);
		}

		lpm3Msg->data[2] = idata;
		lpm3Msg->data[3] = idata+0x10;
		lpm3Msg->data[4] = idata+0x100;
		lpm3Msg->data[5] = idata+0x1000;
		lpm3Msg->data[6] = idata+0x10000;
		lpm3Msg->data[7] = idata+0x100000;
		for(index =HISI_RPROC_LPM3_MBX13; index<HISI_RPROC_ISP_MBX0; index++)
		{
			if(HISI_RPROC_LPM3_MBX17 <  index && HISI_RPROC_LPM3_MBX27 >index)
			{
				continue; /*just only lpmcu's channel*/
			}

			if(syntypye%2)
				err = RPROC_ASYNC_SEND(index, (rproc_msg_t *)lpm3Msg, 8);
			else
				err = RPROC_SYNC_SEND(index,(rproc_msg_t *) lpm3Msg,8, ack_buffer, 2);
			if (err ) 
			{
				kfree(lpm3Msg);
				lpm3Msg = NULL;
				pr_err("xxxxxxxxx pressure test failed and break with  err %d!\n",err);
				return  -1;
			}
			msleep(*(int *)arg);
		}
	}
	if (lpm3Msg){
		kfree(lpm3Msg);
		lpm3Msg = NULL;
	}
	return 0;
}

static int rproc_performance_cnt(struct timespec *ptimespec, unsigned char rproc_id,  union ipc_data *msg, 
									unsigned char len,  unsigned char synctpye)
{
	unsigned int index = 0;
	rproc_msg_t ack_buffer[2] = {0};
	struct timespec time_begin, time_end;
	int sleepcnt = 0;	
	int ret = 0;

	for(index = 0; index < PRESSURE_TIMES; index++)
	{
		
		/*count the first PERFORMANC_TIMES 's cost only*/
		if(index < PERFORMANC_TIMES)
		{
			getnstimeofday(&time_begin);		
		}

		if(SYNC_SEND == synctpye)
		{
			ret |= RPROC_SYNC_SEND(rproc_id,(rproc_msg_t *) msg, len, ack_buffer, 2);
		}
		else if(ASYNC_SEND == synctpye)
		{
			ret |= RPROC_ASYNC_SEND(rproc_id,(rproc_msg_t *) msg,len);
		}
				
		if(index < PERFORMANC_TIMES)
		{
			getnstimeofday(&time_end);
			ptimespec[index].tv_sec = time_end.tv_sec - time_begin.tv_sec;
			if(time_end.tv_nsec < time_begin.tv_nsec && ptimespec[index].tv_sec)
			{
				ptimespec[index].tv_sec -=1;
				ptimespec[index].tv_nsec = time_end.tv_nsec + 1000000000  - time_begin.tv_nsec;
			}
			else
			{
				ptimespec[index].tv_nsec = time_end.tv_nsec - time_begin.tv_nsec;
			}
			/*if cost more than PERFORMANC_FAIL_NSEC, then break and fail*/
			if(ptimespec[index].tv_sec || PERFORMANC_FAIL_NSEC < ptimespec[index].tv_nsec)
			{
				sleepcnt++;
				pr_err("rproc_performance: rproc_id %d  index-%d cost  %lu sec, %lu nsec\n", rproc_id, index, (unsigned long)ptimespec[index].tv_sec, ptimespec[index].tv_nsec);
				/*The remote processor like HIFI, SENSORHUB may fall into sleep and the first IPC will wakeup it, this may cost a lot time*/
				if(10 <  sleepcnt )
					ret |=  -1;
			}
		}

		if(ret)
			break;
			
		 if(ASYNC_SEND == synctpye)
			msleep(1);
	}

	return ret;

}

void show_rproc_performance(struct timespec *ptimespec, unsigned char rproc_id, unsigned char synctpye)
{
	unsigned int index = 0;
	for(index = 0; index < PERFORMANC_TIMES; index++)
	{
		/*just show the some of the index*/
		if(0 == index%PERFORMANC_SHOW_INDEX)
		{
			if(SYNC_SEND == synctpye)
				pr_err("rproc_performance: rproc_id %d sync send cost %lu sec, %lu nsec\n", rproc_id, (unsigned long)ptimespec[index].tv_sec, ptimespec[index].tv_nsec);
			else if(ASYNC_SEND == synctpye)
				pr_err("rproc_performance: rproc_id %d async send cost %lu sec, %lu nsec\n", rproc_id, (unsigned long)ptimespec[index].tv_sec, ptimespec[index].tv_nsec);
		}
	}
}
/*
 * Function name:test_rproc_performance.
 * Discription:test all the core's performance with AP .
 * Parameters:
 *      @ objmax:the remote proccessor number to send ipc msg.  Sometimes like HIFI,ISP,etc. are in sleepmode and not suitable for pressure test.
 * return value:
 *      @ 0:success, others failed.
 */
 int test_rproc_performance(unsigned char objmax)
{
	unsigned char rproc_id = 0;
	union ipc_data * msg  = NULL;
	int i, ret = 0,max_index;
	struct timespec *ptimespec = NULL;
	
	unsigned char rproc_table[] = {HISI_RPROC_LPM3_MBX13, HISI_RPROC_HIFI_MBX18, HISI_RPROC_IOM3_MBX10 ,  HISI_RPROC_ISP_MBX2};
	
	msg = (union ipc_data * )kmalloc(sizeof(union ipc_data), GFP_KERNEL);
	
	ptimespec =(struct timespec *)kmalloc(sizeof(struct timespec) * PERFORMANC_TIMES, GFP_KERNEL);
	
	if(NULL == msg || NULL == ptimespec)
	{
		ret = -1;
		goto out;
	}
	
	/*we don't care the msg's content*/
	memset((void *)msg, 0xFF, sizeof(union ipc_data));

	max_index = objmax < sizeof(rproc_table)/sizeof(unsigned char)?objmax:sizeof(rproc_table)/sizeof(unsigned char);

	for(i = 0; i<objmax; i++)
	{
		rproc_id = rproc_table[i];
		ret  |= rproc_performance_cnt(ptimespec, rproc_id, msg, MAX_MAIL_SIZE, SYNC_SEND);
		show_rproc_performance(ptimespec, rproc_id, SYNC_SEND);
		ret  |= rproc_performance_cnt(ptimespec, rproc_id, msg, MAX_MAIL_SIZE, ASYNC_SEND);
		show_rproc_performance(ptimespec, rproc_id, ASYNC_SEND);	
	}

out:
	if(ret)
		pr_err("rproc_performance and pressure failed\n");
	else
		pr_err("rproc_performance and pressure pass\n");

	if(msg )
		kfree(msg);
	if(ptimespec )
		kfree(ptimespec);		
		
	return ret;
}


static int test_async_send_to_lpmcu(void *arg)
{
	int err = 0, rproc_lpm3 = 0;
	union ipc_data * lpm3Msg = NULL;
	
	lpm3Msg = (union ipc_data * )kmalloc(sizeof(union ipc_data), GFP_KERNEL);

	lpm3Msg->cmd_mix.cmd_src = OBJ_AP;
	lpm3Msg->cmd_mix.cmd_obj = OBJ_LPM3;
	lpm3Msg->cmd_mix.cmd  = CMD_SETTING;
	lpm3Msg->cmd_mix.cmd_type = TYPE_TEST;	
/*****************************************************************************************************
	data[0]: 0x0008030D 
	data[1]: 0xAABBCCDD
	AA: 00(sec or not)
	BB: mailbox id, lpmcu-->ap is 0
	CC: dest core (1:A53, 2:Maia, 4:Sensorhub, 8:LPMCU, 16:HIFI, 32:MODEM, 64:BBE16, 128:IVP)
	DD:	mode, 1 for autoack
*****************************************************************************************************/	
	lpm3Msg->data[0] = 0x0008030F;
	lpm3Msg->data[1] = 0x01000101;
	lpm3Msg->data[2] = 0x22222222;
	lpm3Msg->data[3] = 0x33333333;
	lpm3Msg->data[4] = 0x44444444;
	lpm3Msg->data[5] = 0x55555555;
	lpm3Msg->data[6] = 0x66666666;
	lpm3Msg->data[7] = 0x77777777;
	
	rproc_lpm3 = HISI_RPROC_LPM3_MBX13;
	while(1)
	{
		err = RPROC_ASYNC_SEND(rproc_lpm3, (rproc_msg_t *)lpm3Msg, 8);

		if (err ) 
		{
			pr_err("xxxxxxxxx pressure test failed and break with  err %d!\n",err );
			kfree(lpm3Msg);
			lpm3Msg = NULL;
			return  -1;
		}
		msleep(*(int *)arg);
	}
	return 0;
}


/*
 * Function name:test_all_kind_ipc.
 * Discription:test all the ipc channel .
 * Parameters:
 *      @ type: 1, send sync msg, 2, send async msg , 3, pressure test with lpmcu through all channels, 4,pressure test with lpmcu async
 *      @ objmax:the remote proccessor number to send ipc msg.  Sometimes like HIFI,ISP,etc. are in sleepmode and not suitable for pressure test.
 *      @ interval: to delay, ms
 *      @ threads:  thread num to create 
 * return value:
 *      @ 0:success, others failed.
 */
 int test_all_kind_ipc(int type, unsigned char objmax, int interval, int threads)
{
	rproc_msg_t ack_buffer[2] = {0};
	int err = 0;
	int index = 0, max_id = 0;
	union ipc_data * lpm3Msg = NULL;

	interval_v = interval;
	max_id = HISI_RPROC_ISP_MBX0;
	lpm3Msg = (union ipc_data * )kmalloc(sizeof(union ipc_data), GFP_KERNEL);
	if (lpm3Msg == NULL)
   		return -1;
	lpm3Msg->data[0] = 0x00000000;
	lpm3Msg->data[1] = 0x11111111;
	lpm3Msg->data[2] = 0x22222222;
	lpm3Msg->data[3] = 0x33333333;
	lpm3Msg->data[4] = 0x44444444;
	lpm3Msg->data[5] = 0x55555555;
	lpm3Msg->data[6] = 0x66666666;
	lpm3Msg->data[7] = 0x77777777;
	/*register the rx callback*/
	test_all_sync_ipc_init();

	if(1 ==  type)/*traverse all the ipc channel in sync mode*/
	{
		for(index =0; index<max_id; index++)
		{
			err = RPROC_SYNC_SEND(index,(rproc_msg_t *) lpm3Msg,8, ack_buffer, 2);
			if (err ) 
				pr_err("xxxxxxxxx mailbox channel %d:   send err!\n",index);
			else
				pr_err("xxxxxxxxx mailbox channel %d:   send ok, ack is 0x%x, 0x%x!\n",index, ack_buffer[0], ack_buffer[1]);

			msleep(interval);
		}
	}
	else  if(2 ==  type)/*traverse all the ipc channel in async mode*/
	{

		for(index =0; index<max_id; index++)
		{
			err = RPROC_ASYNC_SEND(index, (rproc_msg_t *)lpm3Msg, 8);
			if (err ) 
				pr_err("xxxxxxxxx mailbox channel %d:   send err!\n",index);
			else
				pr_err("xxxxxxxxx mailbox channel %d:   send ok, ack is 0x%x, 0x%x!\n",index, ack_buffer[0], ack_buffer[1]);

			msleep(interval);
		}
	}
	else  if(3 ==  type) /*send to lpmcu and will receive msg from lpmcu, use for pressure test*/
	{
	      for(index =0; index<threads; index++)
	      {
                    kthread_run(test_all_send_to_lpmcu, (void *)&interval_v, "all_to_lpmcu");
	      }
	}
	else  if(4 ==  type) /*send to lpmcu and will receive msg from lpmcu, use for pressure test*/
	{
	      for(index =0; index<threads; index++)
	      {
                    kthread_run(test_async_send_to_lpmcu, (void *)&interval_v, "async_to_lpmcu");
	      }	
	}
	else  if(5 ==  type) /*performance and  pressure test*/
	{
		err = test_rproc_performance(objmax);
	}	
	kfree(lpm3Msg);
	lpm3Msg = NULL;
	
	return err;
}

static int __init test_rproc_init(void)
{
	sema_init(&send_mutex_sema, 1);
	sema_init(&task_mutex_sema, 1);
       return 0;
}

static void __exit test_rproc_exit(void)
{
}

module_init(test_rproc_init);
module_exit(test_rproc_exit);
MODULE_DESCRIPTION("hisi_rproc_test");
MODULE_LICENSE("GPL v2");


