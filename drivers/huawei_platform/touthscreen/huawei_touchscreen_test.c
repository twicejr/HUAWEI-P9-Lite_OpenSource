/*
 * Huawei Touchscreen Driver
 *
 * Copyright (C) 2013 Huawei Device Co.Ltd
 * License terms: GNU General Public License (GPL) version 2
 *
 */
 
#include <linux/module.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/input/mt.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/regulator/consumer.h>
#include <linux/string.h>
#include <linux/of_gpio.h>
#include <linux/kthread.h>
#include <linux/workqueue.h>
#include <linux/wakelock.h>
#if defined(CONFIG_HAS_EARLYSUSPEND)
#include <linux/earlysuspend.h>
#endif
#include <huawei_platform/touthscreen/huawei_touchscreen.h>
#include <linux/completion.h>

enum ts_test_item_enum{
	TEST_CMDQ_ITEM_1 = 0,
	TEST_CMDQ_ITEM_2,
	TEST_CMDQ_ITEM_3,
	TEST_INPUT_ITEM_1,
	TEST_INVAL_ITEM = 255,
};

struct ts_test_item{
	char *item_name;
	u32    item_switch;
	int (*test_func)(void* data);
	void *item_data;
};

extern struct ts_data g_ts_data;

struct wake_lock ts_test_wake_lock;
struct completion cq_test_sync_1, cq_test_sync_2;
int cq_test_buff[50];


static int cq_test_buff_index = 0;
int test_dbg_cmd_test(struct ts_cmd_node *in_cmd,struct ts_cmd_node *out_cmd)
{
	enum ts_test_item_enum test_item = (enum ts_test_item_enum)in_cmd->cmd_param.prv_params;
	int error = NO_ERR;
	int rec_v, cal_v;
	struct ts_fingers test_pos;

	switch(test_item){
		case TEST_CMDQ_ITEM_1:
			complete(&cq_test_sync_1);
			break;
		case TEST_CMDQ_ITEM_2:
			TS_LOG_INFO("cpu id:%d\n", smp_processor_id());
			complete(&cq_test_sync_1);
			break;
		case TEST_CMDQ_ITEM_3:
			if(!cq_test_buff_index){
				wait_for_completion(&cq_test_sync_1); //wait for send finish
				smp_mb();
			}
			cal_v = cq_test_buff[cq_test_buff_index];
			rec_v = in_cmd->cmd_param.pub_params.algo_param.algo_order;
			TS_LOG_INFO("index :%d, rec data:%d, cal data:%d, result: %s\n",
					cq_test_buff_index, rec_v, cal_v, (rec_v==cal_v)?"pass":"fail");
			cq_test_buff_index++;
			if(cq_test_buff[cq_test_buff_index] == -1){//whether reach the end of buffer
				TS_LOG_INFO("REACH TEST BUFF END, index :%d\n", cq_test_buff_index);
				cq_test_buff_index = 0;
				complete(&cq_test_sync_2);
			}
			break;
		case TEST_INPUT_ITEM_1:
			test_pos.fingers[0].x = 0;
			test_pos.fingers[0].y = 0;
			test_pos.fingers[0].area = 0;
			test_pos.fingers[0].pressure = 0;
			test_pos.fingers[0].status= 0;
			memcpy(&out_cmd->cmd_param.pub_params.report_info, &test_pos, sizeof(struct ts_fingers));
			out_cmd->command = TS_REPORT_INPUT;
			break;
		default:
			TS_LOG_ERR("unsupport item :%d \n", test_item);
			break;
	}
	TS_LOG_INFO("test item :%d result :%d\n", test_item, error);
	return error;
}

int cq_item_1_func(void* data)
{
	int i;
	ktime_t start_time, stop_time,delta;
	long long delta_us, delta_ms;
	struct ts_cmd_node cmd;

	cmd.command = TS_TEST_CMD;
	cmd.cmd_param.prv_params = data;
	TS_LOG_INFO("called paras:%d\n", (int)cmd.cmd_param.prv_params);

	for(i=0; i<100; i++)
	{
		init_completion(&cq_test_sync_1);
		start_time = ktime_get();
		if (NO_ERR == put_one_cmd(&cmd)) {
			if(wait_for_completion_timeout(&cq_test_sync_1, 5*HZ)){
				stop_time = ktime_get();
				delta = ktime_sub(stop_time, start_time);
				delta_us = (long long)ktime_to_us(delta);
				delta_ms = (long long)ktime_to_ms(delta);
				TS_LOG_INFO("CMD PROCESS ELAPSED TIME: %lldms%lldus\n", delta_ms, delta_us);
			}
			else
				TS_LOG_ERR("ts thread process TEST CMD expire 5 sec\n");
		}else
			TS_LOG_ERR("put cmd error\n");
	}
	return 0;
}

int cq_item_2_func(void* data)
{
	int i;
	struct ts_cmd_node cmd;

	cmd.command = TS_TEST_CMD;
	cmd.cmd_param.prv_params = data;
	TS_LOG_INFO("called paras:%d\n", (int)cmd.cmd_param.prv_params);

	for (i=0; i<100; i++)
	{
		init_completion(&cq_test_sync_1);
		if (NO_ERR == put_one_cmd(&cmd)) {
			if(wait_for_completion_timeout(&cq_test_sync_1, 5*HZ)){
				TS_LOG_INFO("CMD PROCESS %d FINISH - cpu id:%d\n", i, smp_processor_id());
			}
			else
				TS_LOG_ERR("ts thread process TEST CMD expire 5 sec\n");
		}else
			TS_LOG_ERR("put cmd error\n");
	}
	return 0;
}

#define CQ_ITEM_3_TEST_COUNT	20
int cq_item_3_func(void* data)
{
	int i;
	struct ts_cmd_node cmd;

	cmd.command = TS_TEST_CMD;
	cmd.cmd_param.prv_params = data;
	TS_LOG_INFO("called paras:%d\n", (int)cmd.cmd_param.prv_params);
	memset(cq_test_buff, -1, sizeof(cq_test_buff));
	init_completion(&cq_test_sync_1);
	init_completion(&cq_test_sync_2);

	for(i=0; i<TS_CMD_QUEUE_SIZE+5; i++){
		cmd.cmd_param.pub_params.algo_param.algo_order = i;
		cq_test_buff[i] = i;
		if(put_one_cmd(&cmd)){
			TS_LOG_INFO("SEND COMPLETE i:%d\n", i);
			if(!i)
				goto out;//unput any cmd, just break;
			cq_test_buff[i] = -1;
			smp_mb();
			complete(&cq_test_sync_1);
			if(try_wait_for_completion(&cq_test_sync_2) ||
				wait_for_completion_timeout(&cq_test_sync_2, 10*HZ))
			{
				TS_LOG_INFO("CMD PROCESS FINISH\n");
			}
			else
				TS_LOG_ERR("ts thread process TEST CMD expire 10 sec\n");
			goto out;//finish 1 test break form internal loop
		}
	}

out:
	return 0;
}

int input_item_1_func(void* data)
{
	struct ts_cmd_node cmd;

	cmd.command = TS_TEST_CMD;
	cmd.cmd_param.prv_params = data;
	TS_LOG_INFO("called paras:%d\n", (int)cmd.cmd_param.prv_params);

	if (NO_ERR != put_one_cmd(&cmd)) {
		TS_LOG_ERR("put cmd failed\n");
	}

	return 0;
}

struct ts_test_item g_test_items[] = {
	[0] = {
		.item_name = "cmd_queue_item_1",
		.item_switch = 0,
		.test_func = cq_item_1_func,
		.item_data = (void *)TEST_CMDQ_ITEM_1,
	},
	[1] = {
		.item_name = "cmd_queue_item_2",
		.item_switch = 0,
		.test_func = cq_item_2_func,
		.item_data = (void *)TEST_CMDQ_ITEM_2,
	},
	[2] = {
		.item_name = "cmd_queue_item_3",
		.item_switch = 0,
		.test_func = cq_item_3_func,
		.item_data = (void *)TEST_CMDQ_ITEM_3,
	},
	[3] = {
		.item_name = "input_event_item_1",
		.item_switch = 0,
		.test_func = input_item_1_func,
		.item_data = (void *)TEST_INPUT_ITEM_1,
	},
};

static int test_create_debugfs(void)
{
	struct dentry *root = g_ts_data.dbg_root;
	struct dentry *dir;
	struct dentry *dent;
	int i;
	int error = -EINVAL;

	if(!root){
		TS_LOG_ERR("g_ts_data dont have dbg_root\n");
		goto out;
	}

	dir = debugfs_create_dir("test_dir", root);
	if (!dir) {
		TS_LOG_ERR("failed to create test_dir directory\n");
		goto out;
	}

	for(i = 0; i<ARRAY_SIZE(g_test_items); i++){
		dent = debugfs_create_u32(g_test_items[i].item_name, S_IRUGO | S_IWUSR, dir, &g_test_items[i].item_switch);
		if (!dent) {
			TS_LOG_ERR("failed to create %s file\n", g_test_items[i].item_name);
			debugfs_remove_recursive(dir);
			break;
		}
	}

	if(i==ARRAY_SIZE(g_test_items))
		error = NO_ERR;

out:
	return error;
}

#define WAIT_MAX_COUNT		(20)

static int ts_test_thread(void *p)
{
	int i = 0;
	int ret;

	while(atomic_read(&g_ts_data.state) != TS_WORK && i < WAIT_MAX_COUNT){
		TS_LOG_INFO("touchscreen module init not finish\n");
		msleep(1000);
		i++;
	}

	TS_LOG_INFO("touchscreen test init\n");

	if(test_create_debugfs()){
		TS_LOG_ERR("touchscreen test create debugfs failed\n");
		goto out;
	}

	TS_LOG_INFO("touchscreen test start polling\n");

	wake_lock_init(&ts_test_wake_lock, WAKE_LOCK_IDLE, "ts_test");

repeat:
	msleep(1000);
	for(i = 0, ret = -99; i<ARRAY_SIZE(g_test_items); i++){
		if(!g_test_items[i].item_switch)
			continue;
		wake_lock(&ts_test_wake_lock);
		TS_LOG_INFO("touchscreen test :%s begin\n", g_test_items[i].item_name);
		if(g_test_items[i].test_func)
			ret = g_test_items[i].test_func(g_test_items[i].item_data);
		TS_LOG_INFO("touchscreen test :%s end, ret:%d\n",  g_test_items[i].item_name, ret);
		g_test_items[i].item_switch = 0;
		wake_unlock(&ts_test_wake_lock);
	}
	goto repeat;

out:
	return 0;
}

static int __init ts_test_init(void)
{
	struct task_struct *test_task;

	TS_LOG_INFO("ts_test_init called here\n");
	return 0;

	test_task = kthread_create_on_node(ts_test_thread, NULL,  cpu_to_node(2), "ts_test_thread");
	if (IS_ERR(test_task))
		TS_LOG_ERR("create ts_thread failed\n");
	else
		wake_up_process(test_task);

	return 0;
}

late_initcall(ts_test_init);

MODULE_AUTHOR(" wangyuxiang <robin.wangyuxiang@huawei.com>");
MODULE_DESCRIPTION("Huawei TouchScreen Driver");
MODULE_LICENSE("GPL");
