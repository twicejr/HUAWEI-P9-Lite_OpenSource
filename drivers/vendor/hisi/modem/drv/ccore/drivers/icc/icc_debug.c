/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  icc_balong_debug.c
*
*   作    者 :  y00184236
*
*   描    述 :  可维可测
*
*   修改记录 :
       1> 2013年3月10日  v1.00  y00184236  创建
*      2> 2013年06月13日 v1.10  y00184236  增加mcore代码，且acore/ccore/mcore代码归一
*************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*lint --e{537} */
#include <bsp_pm_om.h>
#include <securec.h>
#include <icc_core.h>
#include <icc_platform.h>


struct icc_pm_om
{
	struct icc_channel_packet packet;
	read_cb_func read_cb;
	void *read_context;
};

struct icc_dbg g_icc_dbg ={0};

extern struct icc_control g_icc_ctrl;

s32 bsp_icc_debug_register(u32 channel_id, FUNCPTR_1 debug_routine, int param)
{
	struct icc_channel_vector *vector = NULL;

	if((GET_CHN_ID(channel_id)  >= ICC_CHN_ID_MAX) ||
	   (GET_FUNC_ID(channel_id) >= g_icc_ctrl.channels[GET_CHN_ID(channel_id)]->func_size))
	{
		icc_print_error("invalide parameter! channel_id=0x%x\n", channel_id);
		return ICC_INVALID_PARA;
	}
	/*lint --e{409} */
	vector = &(g_icc_ctrl.channels[GET_CHN_ID(channel_id)]->vector[GET_FUNC_ID(channel_id)]);
	vector->pm_debug.debug_routine = debug_routine;
	vector->pm_debug.para = param;

	return ICC_OK;
}

void run_icc_pm_debug_callback(void)
{
	u32 i = 0, j = 0;
	struct icc_channel *channel  = NULL;
	struct icc_channel_vector *vector = NULL;
	for(i = 0; i < ICC_CHN_ID_MAX; i++)
	{
		channel = g_icc_ctrl.channels[i];
		if (!channel)
		{
			continue;
		}
		for (j = 0; j < channel->func_size; j++)
		{
			vector =  &(channel->vector[j]);
			if(vector && vector->pm_debug.debug_routine) /*lint !e774 */
			{
				(void)vector->pm_debug.debug_routine(vector->pm_debug.para);
			}
		}
	}
}

void icc_help(void);

static void channel_fifo_dump(u32 real_channel_id, u32 fifo_type, const char* fifo_name)
{
	char *base_addr = 0;
	struct icc_channel* channel = g_icc_ctrl.channels[real_channel_id%g_icc_ctrl.channel_size];
	struct icc_channel_fifo* fifo = NULL;

	if(!channel)
	{
		icc_print_error("channel pointer is NULL!\n");
		return;
	}
	
	fifo = (0 == fifo_type)? channel->fifo_recv: channel->fifo_send;
	if(!fifo)
	{
		icc_print_error("fifo pointer is NULL!\n");
		return;
	}
	
	base_addr = (char*)fifo + sizeof(struct icc_channel_fifo);

	icc_print_info("***************************icc_channel_fifo:%s**********************************\n", fifo_name);
	icc_print_info("address:   0x%p\n", fifo);
	icc_print_info("base_addr: 0x%p\n", base_addr);
	icc_print_info("magic:     0x%x\n", fifo->magic);
	icc_print_info("size:      0x%x\n", fifo->size);
	icc_print_info("write:     0x%x\n", fifo->write);
	icc_print_info("read:      0x%x\n", fifo->read);
	icc_print_info("data:      0x%x\n\n", *((s32*)(fifo->data)));
}

void icc_control_dump(void)
{
	u32 i = 0;

	icc_print_info("**************************icc_control*****************************************\n");
	icc_print_info("cpuid:                  0x%x\n", g_icc_ctrl.cpu_id);
	icc_print_info("state:                  0x%x\n", g_icc_ctrl.state);
	icc_print_info("shared_task_id:         0x%x\n", g_icc_ctrl.shared_task_id);
	icc_print_info("shared_recv_ipc_irq_id: 0x%x\n", g_icc_ctrl.shared_recv_ipc_irq_id);
	for(i = 0; i < ICC_CHN_ID_MAX; i++)
	{
		icc_print_info("channels[%02d]:           0x%p\n", i, g_icc_ctrl.channels[i]);
	}
	icc_print_info("channel_size:           0x%x\n", g_icc_ctrl.channel_size);
	icc_print_info("***********************************************************************\n");
}

void icc_channel_dump(u32 real_channel_id)
{
	struct icc_channel* channel = g_icc_ctrl.channels[real_channel_id%g_icc_ctrl.channel_size];
	u32 i = 0;

	if(!channel)
	{
		icc_print_error("channel pointer is NULL!\n");
		return;
	}

	icc_print_info("*******************************icc_channel****************************************\n");
	icc_print_info("address:                  0x%p\n", channel);
	icc_print_info("id:                       0x%x\n", channel->id);
	icc_print_info("state:                    0x%x\n", channel->state);
	icc_print_info("mode:                     0x%x\n", channel->mode.val);
	icc_print_info("task_id:                  0x%x\n", channel->private_task_id);
	icc_print_info("ipc_send_irq_id:          0x%x\n", channel->ipc_send_irq_id);
	icc_print_info("ipc_recv_irq_id:          0x%x\n", channel->ipc_recv_irq_id);
	icc_print_info("fifo_recv:                0x%p\n", channel->fifo_recv);
	icc_print_info("fifo_send:                0x%p\n", channel->fifo_send);
	for(i = 0; i < channel->func_size; i++)
	{
		icc_print_info("channel->vecotr[%02d]:      0x%p\n", i, &channel->vector[i]);
	}
	icc_print_info("func_size:                0x%x\n", channel->func_size);
	icc_print_info("***********************************************************************\n");
}

void icc_channel_fifo_dump(u32 real_channel_id)
{
	channel_fifo_dump(real_channel_id, 0, "recv fifo");
	channel_fifo_dump(real_channel_id, 1, "send fifo");
	icc_print_info("**********************************************************************\n");
}

void icc_channel_vector_dump(u32 channel_id, u32 func_id)
{
	struct icc_channel_vector* vector = NULL;
	channel_id %= g_icc_ctrl.channel_size;
	func_id    %= g_icc_ctrl.channels[channel_id]->func_size;
	vector = &(g_icc_ctrl.channels[channel_id]->vector[func_id]);

	if(!vector) /*lint !e774 */
	{
		icc_print_error("vector pointer is NULL!\n");
		return;
	}
	icc_print_info("**********************icc_channel_vector**********************\n");
	icc_print_info("base addr:      0x%p\n", vector);
	icc_print_info("read_cb:        0x%p\n", vector->read_cb);
	icc_print_info("read_context:   0x%p\n", vector->read_context);
	icc_print_info("write_cb:       0x%p\n", vector->write_cb);
	icc_print_info("write_context:  0x%p\n", vector->write_context);
	icc_print_info("**************************************************************\n");
}

static inline void icc_pm_om_log(struct icc_channel_packet *packet, read_cb_func read_cb, void *read_context)
{
	struct icc_pm_om pm_om;

	(void)memset_s((void *)&pm_om, sizeof(pm_om), 0, sizeof(pm_om));
	(void)memcpy_s((void *)&pm_om.packet, sizeof(*packet), (void *)packet, sizeof(*packet));
	pm_om.read_cb      = read_cb;
	pm_om.read_context = read_context;

	(void)bsp_pm_log(PM_OM_CICC, sizeof(pm_om), (void *)&pm_om);
}

int icc_channel_packet_dump(struct icc_channel_packet *packet)
{
	struct icc_channel *channel = NULL;
	const char *name = NULL;
	struct icc_channel_vector *vector = NULL;
	read_cb_func read_cb = NULL;
	void *read_context = NULL;
	int ret = ICC_OK;

	channel = g_icc_ctrl.channels[GET_CHN_ID(packet->channel_id)];
	name = channel->name;
	vector = &channel->vector[GET_FUNC_ID(packet->channel_id)];
	read_cb = vector->read_cb;
	read_context = vector->read_context;

	if ((0 == g_icc_dbg.msg_print_sw) && (0 == g_icc_ctrl.wake_up_flag) && (0 == g_icc_ctrl.sleep_flag))
	{
		return ret;
	}

	if (1 == g_icc_ctrl.wake_up_flag)
	{
		g_icc_ctrl.wake_up_flag = 0;
		icc_pm_om_log(packet, read_cb, read_context);
		return ret;
	}

	if (1 == g_icc_ctrl.sleep_flag)
	{
		g_icc_ctrl.sleep_flag = 0;
		return ret;
	}

	icc_print_info("*******************icc[%s]*******************\n", name);
	icc_print_info("channel_id  : 0x%x\n", packet->channel_id);
	icc_print_info("len         : 0x%x\n", packet->len);
	icc_print_info("src_cpu_id  : 0x%x\n", packet->src_cpu_id);
	icc_print_info("timestamp   : 0x%x\n", packet->timestamp);
	icc_print_info("task_id     : 0x%x\n", packet->task_id);
	icc_print_info("read_cb     : %p\n",   read_cb);
	icc_print_info("read_context: %p\n",   read_context);
	icc_print_info("**********************************************\n");
	return ret;
}

void icc_packet_print(struct icc_channel_packet *packet)
{
	icc_print_info("*****************icc_packet*******************\n");
	icc_print_info("channel_id  : 0x%x\n", packet->channel_id);
	icc_print_info("len         : 0x%x\n", packet->len);
	icc_print_info("src_cpu_id  : 0x%x\n", packet->src_cpu_id);
	icc_print_info("timestamp   : 0x%x\n", packet->timestamp);
	icc_print_info("task_id     : 0x%x\n", packet->task_id);
	icc_print_info("**********************************************\n");
}

void icc_dbg_print_sw(u32 sw)
{
	g_icc_dbg.msg_print_sw = sw;
}

void icc_dbg_info_print(const char *fifo_name, u32 channel_id, u8 *data, u32 data_len)
{
	if(g_icc_dbg.msg_print_sw)
	{
		icc_print_error("%s: channel[0x%x], msg[0x%p]: 0x%x, len[%d]:\n", fifo_name, channel_id, data, *(u32 *)data, data_len);
	}
}

/* 如果在中断中，则返回0 */
u32 icc_taskid_get(void)
{

    char *tskName = NULL;
	if (osl_int_context())
	{
		return 0;
	}
	else
	{
		(void)osl_task_name_get(osl_task_self(),&tskName);
		return (u32)(osl_task_self());
	}
}

void icc_msg_queue_init(struct icc_msg_fifo *queue)
{
	queue->front = queue->rear = 0;
	queue->size = 0;
}

static void icc_send_msg_queue_in(struct icc_msg_fifo *queue, struct icc_uni_msg_info *msg)
{
	/* when full, abandon old message */
	if((queue->front == queue->rear) && (queue->size == ICC_STAT_MSG_NUM))
	{
		queue->front = (queue->front + 1) % ICC_STAT_MSG_NUM;
		queue->size = queue->size - 1;
	}

	(void)memcpy_s((void *)(&queue->msg[queue->rear]), sizeof(*msg), msg, sizeof(*msg));
	queue->rear = (queue->rear + 1) % ICC_STAT_MSG_NUM;
	queue->size = queue->size + 1;
}

static void icc_recv_msg_queue_in(struct icc_msg_fifo_recv *queue, struct icc_recv_msg_info *msg)
{
	/* when full, abandon old message */
	if((queue->front == queue->rear) && (queue->size == ICC_STAT_MSG_NUM))
	{
		queue->front = (queue->front + 1) % ICC_STAT_MSG_NUM;
		queue->size = queue->size - 1;
	}

	(void)memcpy_s((void *)(&queue->msg[queue->rear]), sizeof(*msg), msg, sizeof(*msg));
	queue->rear = (queue->rear + 1) % ICC_STAT_MSG_NUM;
	queue->size = queue->size + 1;
}

void icc_msg_dump(struct icc_msg_fifo *queue, u32 start, u32 end)
{
	u32 i = 0;
	for(i = start; i < end; i++)
	{
		icc_print_info("[C SR]*******the latest [%d] msg*******\n", i-start);
		icc_print_info("channel_id  : 0x%x\n", queue->msg[i].channel_id);
		icc_print_info("send_task_id: 0x%x\n", queue->msg[i].send_task_id);
		icc_print_info("recv_task_id: 0x%x\n", queue->msg[i].recv_task_id);
		icc_print_info("length      : 0x%x\n", queue->msg[i].len);
		icc_print_info("write_pos   : 0x%x\n", queue->msg[i].write_pos);
		icc_print_info("read_pos    : 0x%x\n", queue->msg[i].read_pos);
	}

}

#if 0
void icc_msg_record_show(u32 msg_type, u32 msg_num)
{
	u32 part1 = 0;
	u32 part2 = 0;
	struct icc_msg_fifo *msg_queue = NULL;

	msg_num = (msg_num - 1) % ICC_STAT_MSG_NUM  + 1;
	msg_queue = msg_type? &(g_icc_dbg.msg_stat.send): &(g_icc_dbg.msg_stat.recv);

	/* get part1: from queue front to queue end(queue is always full) */
	part1 = ICC_MIN(msg_num, (ICC_STAT_MSG_NUM - msg_queue->front));
	icc_msg_dump(msg_queue, msg_queue->front, msg_queue->front + part1);

	/* get part2(if left): from queue start to queue rear */
	part2 = ICC_MIN((msg_num - part1), msg_queue->rear);
	icc_msg_dump(msg_queue, 0, part2);
}
#endif

/* msg_type: 0, recv; 1, send */
void icc_channel_info_show(u32 msg_type, u32 real_channel_id)
{
	struct icc_uni_channel_info *channel = NULL;
	channel = msg_type? &(g_icc_dbg.channel_stat[real_channel_id]->send): &(g_icc_dbg.channel_stat[real_channel_id]->recv);

	icc_print_info("******************channel[0x%x]****************\n", real_channel_id);
	icc_print_info("msg_len     : 0x%x\n", channel->total.sum_len);
	icc_print_info("msg_num     : 0x%x\n", channel->total.sum_num);
	icc_print_info("msg_num_prev: 0x%x\n", channel->total.sum_num_prev);
	icc_print_info("func_size   : 0x%x\n", channel->func_size);
	channel->total.sum_num_prev = channel->total.sum_num;
}

void icc_sub_channel_info_show(u32 msg_type, u32 real_channel_id, u32 func_id)
{
	struct icc_uni_channel_info *channel = NULL;
	channel = msg_type? &(g_icc_dbg.channel_stat[real_channel_id]->send): &(g_icc_dbg.channel_stat[real_channel_id]->recv);
	func_id %= channel->func_size;

	icc_print_info("***********sub channel[0x%x]***********\n", func_id);
	icc_print_info("msg_len     : 0x%x\n", channel->sub_chn[func_id].sum_len);
	icc_print_info("msg_num     : 0x%x\n", channel->sub_chn[func_id].sum_num);
	icc_print_info("sum_num_prev: 0x%x\n", channel->sub_chn[func_id].sum_num_prev);
	channel->sub_chn[func_id].sum_num_prev = channel->sub_chn[func_id].sum_num;
}

void icc_sub_channel_info_show_all(u32 msg_type, u32 real_channel_id)
{
	struct icc_uni_channel_info *channel = NULL;
	u32 i = 0;
	channel = msg_type? &(g_icc_dbg.channel_stat[real_channel_id]->send): &(g_icc_dbg.channel_stat[real_channel_id]->recv);

	for(i = 0; i < channel->func_size; i++)
	{
		if(channel->sub_chn[i].sum_num_prev != channel->sub_chn[i].sum_num)
		{
			icc_print_info("***********sub channel[0x%x]***********\n", i);
			icc_print_info("msg_len     : 0x%x\n", channel->sub_chn[i].sum_len);
			icc_print_info("msg_num     : 0x%x\n", channel->sub_chn[i].sum_num);
			icc_print_info("sum_num_prev: 0x%x\n", channel->sub_chn[i].sum_num_prev);
		}
		channel->sub_chn[i].sum_num_prev = channel->sub_chn[i].sum_num;
	}
}

void icc_recv_ipc_int_show(void)
{
	icc_print_info("*******icc收到的ipc中断统计*******\n");
	icc_print_info("ipc_int_cnt: %d\n", g_icc_dbg.ipc_int_cnt);
}

void icc_errno_show(void)
{
	icc_print_info("******************icc错误码信息******************\n");
	icc_print_info("0x%x: channel init error\n",ICC_CHN_INIT_FAIL);
	icc_print_info("0x%x: malloc channel memory fail\n",ICC_MALLOC_CHANNEL_FAIL);
	icc_print_info("0x%x: malloc rector memory fail\n",ICC_MALLOC_VECTOR_FAIL);
	icc_print_info("0x%x: create task fail\n",ICC_CREATE_TASK_FAIL);
	icc_print_info("0x%x: debug init error\n",ICC_DEBUG_INIT_FAIL);
	icc_print_info("0x%x: create semaphore fail\n",ICC_CREATE_SEM_FAIL);
	icc_print_info("0x%x: register ipc int fail\n",ICC_REGISTER_INT_FAIL);
	icc_print_info("0x%x: interface parameter error\n",ICC_INVALID_PARA);
	icc_print_info("0x%x: fifo is full\n",ICC_INVALID_NO_FIFO_SPACE);
	icc_print_info("0x%x: sem take timeout\n",ICC_WAIT_SEM_TIMEOUT);
	icc_print_info("0x%x: send len != expected\n",ICC_SEND_ERR);
	icc_print_info("0x%x: recv len != expected\n",ICC_RECV_ERR);
	icc_print_info("0x%x: register read callback fail\n",ICC_REGISTER_CB_FAIL);
	icc_print_info("0x%x: register dpm fail\n",ICC_REGISTER_DPM_FAIL);
	icc_print_info("0x%x: malloc memory fail\n",ICC_MALLOC_MEM_FAIL);
	icc_print_info("0x%x: null pointer\n",ICC_NULL_PTR);
}

void icc_print_level_set(u32 level)
{
    (void)bsp_mod_level_set(BSP_MODU_ICC, level);
    icc_print_info("bsp_mod_level_set(BSP_MODU_ICC=%d, level=%d)\n", BSP_MODU_ICC, level);
}

void icc_struct_dump(void)
{
	icc_print_info("***************************icc结构体信息***************************\n");
	icc_print_info("icc初始化信息            : icc_init_info_dump channel_id\n");
	icc_print_info("icc_control结构体        : icc_control_dump\n");
	icc_print_info("icc_channel结构体        : icc_channel_dump channel_id\n");
	icc_print_info("icc_channel_fifo结构体   : icc_channel_fifo_dump channel_id\n");
	icc_print_info("icc_channel_vector结构体 : icc_channel_vector_dump channel_id func_id\n");
	icc_print_info("结构体显示函数参数说明   : channel_id, 主通道号; fucn_id,子通道号\n");
}

void icc_help(void)
{
	icc_print_info("***************************************icc调试帮助信息***************************************\n");
	icc_print_info("结构体信息dump          : icc_struct_dump\n");
	icc_print_info("调试打印开关            : icc_dbg_print_sw 0|1\n");
	icc_print_info("错误码说明              : icc_errno_show\n");
	icc_print_info("收到ipc中断统计         : icc_recv_ipc_int_show\n");
	icc_print_info("最近n条收发消息显示     : icc_msg_record_show msg_type msg_num\n");
	icc_print_info("单个通道统计信息        : icc_channel_info_show msg_type channel_id\n");
	icc_print_info("所有子通道统计信息      : icc_sub_channel_info_show_all msg_type channel_id\n");
	icc_print_info("单个子通道统计信息      : icc_sub_channel_info_show msg_type channel_id func_id\n");
	icc_print_info("收发消息显示函数参数说明: msg_type, 消息类型(0: 接收; 1: 发送); msg_num, 显示消息个数(<=10)\n");
	icc_print_info("通道统计信息函数参数说明: msg_type, 同上; channel_id, 主通道号; fucn_id, 子通道号\n");
}

void icc_dump_hook(void)
{/*lint --e{539}*/
    char *dump_buf = g_icc_dbg.dump_buf_addr;
    u32  dump_size = g_icc_dbg.dump_buf_size;

    /* do nothing, if om init fail */
    if (0 == dump_size || NULL == dump_buf)
    {
        return;
    }

	(void)memcpy_s((void *)g_icc_dbg.dump_buf_addr, sizeof(struct icc_msg_info), 
		(void *)&g_icc_dbg.msg_stat, sizeof(struct icc_msg_info));

    return;
}

void icc_dump_init(void)
{
    /* reg the dump callback to om */
	if(BSP_ERROR == bsp_dump_register_hook("ICC",(dump_hook)icc_dump_hook))
	{
	    goto err_ret; /*lint !e801 */
	}

    g_icc_dbg.dump_buf_addr = (char *)bsp_dump_register_field(ICC_DUMP_SAVE_MOD, "ICC", 0, 0, ICC_DUMP_EXT_SIZE, 0x0001);
    if(g_icc_dbg.dump_buf_addr == NULL)
    {
        goto err_ret; /*lint !e801 */
    }
    g_icc_dbg.dump_buf_size = ICC_DUMP_EXT_SIZE;

    return;

err_ret:
	g_icc_dbg.dump_buf_addr = NULL;
	g_icc_dbg.dump_buf_size = 0;
	icc_print_error("try to use dump fail!\n");
	return;
}

s32  icc_debug_init(u32 channel_num)
{
	u32 i = 0;
	struct icc_channel_info * channel = NULL;
	struct icc_channel_stat_info *sub_channel = NULL;
	struct icc_channel *icc_channel = NULL;
	
	(void)memset_s(&g_icc_dbg, sizeof(struct icc_dbg), 0, sizeof(struct icc_dbg));

	for(i = 0; i < channel_num; i++)
	{
		/* 使用g_icc_ctrl而不是g_icc_init_info，因为测试编进去以后，统计通道不需要再处理 */
		if (!g_icc_ctrl.channels[i])
		{
		    continue ;
		}
		
		icc_channel = g_icc_ctrl.channels[i];
		channel = (struct icc_channel_info *)osl_malloc(sizeof(struct icc_channel_info));
		if (!channel)
		{
			icc_print_error("malloc icc_channel_info memory fail!\n");
			return (s32)ICC_ERR;
		}

		/* 收发子通道一同分配 */
		sub_channel = (struct icc_channel_stat_info *)osl_malloc(sizeof(struct icc_channel_stat_info) * icc_channel->func_size * 2);
		if (!sub_channel)
		{
			osl_free((void *)channel);
			icc_print_error("malloc icc_channel_stat_info memory fail!\n");
			return (s32)ICC_ERR;
		}

		/* channel init */
		(void)memset_s((void *)channel, sizeof(struct icc_channel_info), 0, sizeof(struct icc_channel_info));
		channel->id = icc_channel->id;
		channel->recv.func_size= icc_channel->func_size;
		channel->send.func_size= icc_channel->func_size;

		/* sub channel init */
		(void)memset_s((void *)sub_channel, sizeof(struct icc_channel_stat_info) * icc_channel->func_size * 2,
			0, sizeof(struct icc_channel_stat_info) * icc_channel->func_size * 2); /*lint !e665 */
		channel->send.sub_chn  = sub_channel;
		channel->recv.sub_chn  = &(sub_channel[icc_channel->func_size]);
		
		g_icc_dbg.channel_stat[channel->id] = channel;
	}

	icc_dump_init();

	return ICC_OK;
}

static void icc_channel_msg_stat(struct icc_channel_stat_info *channel, u32 msg_len, u32 recv_task_id)
{
	if(!channel)
	{
		return;
	}
	channel->task_id = recv_task_id;
	channel->sum_len += msg_len;
	channel->sum_num++;
}

void icc_debug_in_isr(void)
{
	g_icc_dbg.ipc_int_cnt++;
}

static struct icc_uni_msg_info msg_tx = {0};

void icc_debug_before_send(struct icc_channel_packet *packet)
{
	msg_tx.duration_prev = bsp_get_slice_value();
	msg_tx.send_task_id = icc_taskid_get();
	/* 发送数据包的任务ID及时间戳 */	
	packet->timestamp = msg_tx.duration_prev;
	packet->task_id = msg_tx.send_task_id;
}

void icc_debug_after_send(struct icc_channel *channel, struct icc_channel_packet *packet, u8* data)
{
	msg_tx.write_pos = channel->fifo_send->write;
	msg_tx.read_pos = channel->fifo_send->read;
	msg_tx.len = packet->len;
    msg_tx.channel_id = packet->channel_id;
	msg_tx.recv_task_id = 0;
	msg_tx.duration_post = bsp_get_slice_value();

	(void)memcpy_s((void *)msg_tx.data, ICC_MSG_RECORED_DATA_LEN, (void *)data, min(msg_tx.len, (u32)ICC_MSG_RECORED_DATA_LEN));

	icc_send_msg_queue_in(&(g_icc_dbg.msg_stat.send), &msg_tx);
	icc_channel_msg_stat(&(g_icc_dbg.channel_stat[GET_CHN_ID(msg_tx.channel_id)]->send.total), msg_tx.len, msg_tx.send_task_id);
	icc_channel_msg_stat(&(g_icc_dbg.channel_stat[GET_CHN_ID(msg_tx.channel_id)]->send.sub_chn[GET_FUNC_ID(msg_tx.channel_id)]), msg_tx.len, msg_tx.send_task_id);

	icc_dbg_info_print("fifo_send", msg_tx.channel_id, data, packet->len);
}

static struct icc_recv_msg_info msg_rx = {0};

void icc_debug_before_recv(struct icc_channel_packet *pkg_header)
{
	msg_rx.before_recv_slice = bsp_get_slice_value();
	msg_rx.channel_id        = pkg_header->channel_id;
	msg_rx.send_task_id      = pkg_header->task_id;
	msg_rx.len               = pkg_header->len;
	g_icc_dbg.send_cpu_id    = pkg_header->src_cpu_id;
	(void)icc_channel_packet_dump(pkg_header);
}

void icc_debug_in_read_cb(u32 channel_id, u8 *buf, u32 buf_len, u32 read_ptr, u32 write_ptr)
{
	msg_rx.in_read_cb_slice = bsp_get_slice_value();
	msg_rx.recv_task_id     = icc_taskid_get();
	msg_rx.write_pos        = write_ptr;
	msg_rx.read_pos         = read_ptr;
	icc_dbg_info_print("fifo_recv", channel_id, buf, buf_len);
}

#define ICC_PERF_COUNT_MAX (10000)
void icc_debug_after_recv(struct icc_channel_packet *pkg_header)
{
    u32 delta_slice = 0;
	u32 channel_id = pkg_header->channel_id;
	
	msg_rx.after_recv_slice = bsp_get_slice_value();
	delta_slice = get_timer_slice_delta(msg_rx.before_recv_slice, msg_rx.after_recv_slice);
	if (delta_slice > msg_rx.perf.max_readcb_consume_slice)
	{
		msg_rx.perf.max_readcb_consume_slice = delta_slice;
		msg_rx.perf.max_readcb_channel_id    = channel_id;
	}

	if (msg_rx.perf.cnt >= ICC_PERF_COUNT_MAX)
	{
		msg_rx.perf.cnt = 0;
		msg_rx.perf.sum = 0;
	}

	delta_slice = get_timer_slice_delta(pkg_header->timestamp, msg_rx.after_recv_slice);
	msg_rx.perf.cnt++;
	msg_rx.perf.sum += delta_slice;
	msg_rx.perf.avg = msg_rx.perf.sum / msg_rx.perf.cnt;

	icc_recv_msg_queue_in(&(g_icc_dbg.msg_stat.recv), &msg_rx);
	icc_channel_msg_stat(&(g_icc_dbg.channel_stat[GET_CHN_ID(channel_id)]->recv.total), msg_rx.len, msg_rx.recv_task_id);
	icc_channel_msg_stat(&(g_icc_dbg.channel_stat[GET_CHN_ID(channel_id)]->recv.sub_chn[GET_FUNC_ID(channel_id)]), \
		msg_rx.len, msg_rx.recv_task_id);
}

#ifdef __cplusplus
}
#endif

