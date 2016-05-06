#include "dsm_core.h"
#include <linux/kthread.h>
#include <linux/sched/rt.h>
#include <linux/random.h>
#include <linux/hw_log.h>
#include <dsm/dsm_pub.h>

#define HWLOG_TAG	DSM_TEST
HWLOG_REGIST();
#define DSM_LOG_INFO(x...)		_hwlog_info(HWLOG_TAG, ##x)
#define DSM_LOG_ERR(x...)		_hwlog_err(HWLOG_TAG, ##x)
#define DSM_LOG_DEBUG(x...)	_hwlog_debug(HWLOG_TAG, ##x)

int poll (void)
{
	unsigned int random;
	int result;

	random = get_random_int();
	result = (random%2) ? 0 : 5;
	DSM_LOG_INFO("%s enter random num %u, poll result %d\n", __func__, random, result);
	return result;
}
int dump (int type, void *buff, int size)
{
	int used_size = 0;
	char *ptr = buff;

	DSM_LOG_INFO("%s called, type %d\n", __func__, type);
	used_size += snprintf(ptr, (size - used_size), "dump called:\n");
	ptr = buff + used_size;
	used_size += snprintf(ptr, (size - used_size), "Today is saturday\n");
	ptr = buff + used_size;
	used_size += snprintf(ptr, (size - used_size), "Tempeature is 10 degree\n");
	ptr = buff + used_size;
	used_size += snprintf(ptr, (size - used_size), "Wheather is sunny\n");
	ptr = buff + used_size;
	used_size += snprintf(ptr, (size - used_size), "Fit to do sports or have a picnic\n");

	return used_size;
}

struct dsm_client_ops ops={
	.poll_state = poll,
	.dump_func = dump,
};

struct dsm_dev dev1 = {
	.name = "test_dev_1",
	.device_name = NULL,
	.ic_name = NULL,
	.module_name = NULL,
	.fops = &ops,
	.buff_size = 500,
};

struct dsm_dev dev2 = {
	.name = "test_dev_2",
	.device_name = NULL,
	.ic_name = NULL,
	.module_name = NULL,
	.fops = &ops,
	.buff_size = 1024,
};

struct dsm_dev dev3 = {
	.name = "test_dev_3",
	.device_name = NULL,
	.ic_name = NULL,
	.module_name = NULL,
	.fops = &ops,
	.buff_size = 10240,
};

struct dsm_dev dev4 = {
	.name = "test_dev_4",
	.device_name = NULL,
	.ic_name = NULL,
	.module_name = NULL,
	.fops = &ops,
	.buff_size = 300,
};

struct dsm_dev dev5 = {
	.name = "test_dev_5",
	.device_name = NULL,
	.ic_name = NULL,
	.module_name = NULL,
	.fops = &ops,
	.buff_size = 500,
};

struct dsm_client *c1;
struct dsm_client *c2;
struct dsm_client *c3;
struct dsm_client *c4;
struct dsm_client *c5;

static u8 test_buff[16] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','\n'};

static inline void test_copy(struct dsm_client *client, int count)
{
	while(count/16){
		dsm_client_copy(client, test_buff, 16);
		count -= 16;
	}
	if(count)
		dsm_client_copy(client, test_buff, count);
}


void notify_work(void)
{
	struct dsm_client *curr;
	unsigned int random;
	int result;

	random = get_random_int();
	result = random%5;
	DSM_LOG_INFO("%s enter random num %u, result %d\n", __func__, random, result);
	switch(result){
		case 0:
			goto notify_1;
		case 1:
			goto notify_2;
		case 2:
			goto notify_3;
		case 3:
			goto notify_4;
		case 4:
			goto notify_5;
	}

notify_5:
	curr = c1;
	if(!dsm_client_ocuppy(curr)){
		test_copy(curr, 300);
		dsm_client_notify(curr, 5);
		DSM_LOG_INFO("%s dsm_client_notify \n", curr->client_name);
	}

notify_4:
	curr = c2;
	if(!dsm_client_ocuppy(curr)){
		test_copy(curr, 1024);
		dsm_client_notify(curr, 5);
		DSM_LOG_INFO("%s dsm_client_notify \n", curr->client_name);
	}

notify_3:
	curr = c3;
	if(!dsm_client_ocuppy(curr)){
		test_copy(curr, 10240);
		dsm_client_notify(curr, 5);
		DSM_LOG_INFO("%s dsm_client_notify \n", curr->client_name);
	}

notify_2:
	curr = c4;
	if(!dsm_client_ocuppy(curr)){
		dsm_client_record(curr, "Kaka is an amazing palyer\n");
		dsm_client_record(curr, "Ronaldo is an amazing palyer\n");
		dsm_client_record(curr, "Ronney is an amazing palyer\n");
		dsm_client_record(curr, "Henny is an amazing palyer\n");
		dsm_client_record(curr, "Veri is an amazing palyer\n");
		dsm_client_notify(curr, 5);
		DSM_LOG_INFO("%s dsm_client_notify \n", curr->client_name);
	}

notify_1:
	curr = c5;
	if(!dsm_client_ocuppy(curr)){
		dsm_client_record(curr, "National derby:\n");
		dsm_client_record(curr, "Real Madrid vs  Barcelona\n");
		dsm_client_record(curr, "Manchester United vs Chelsea\n");
		dsm_client_record(curr, "AC milan vs Juventus\n");
		dsm_client_record(curr, "Bayern Munich vs Hertha BSC\n");
		dsm_client_notify(curr, 5);
		DSM_LOG_INFO("%s dsm_client_notify \n", curr->client_name);
	}
}

static int dsm_test_thread(void *data)
{
	static const struct sched_param param = {
		.sched_priority = MAX_USER_RT_PRIO/2,
	};

	sched_setscheduler(current, SCHED_FIFO, &param);

	while (!kthread_should_stop()) {
		set_current_state(TASK_INTERRUPTIBLE);
		DSM_LOG_INFO("%s sleep in\n", __func__);
		schedule_timeout(10*HZ);
		DSM_LOG_INFO("%s sleep out\n", __func__);
		set_current_state(TASK_RUNNING);
		notify_work();
	}
	return 0;
}

struct task_struct *dsm_task;

static int __init dsm_test(void)
{
	c1 = dsm_register_client(&dev1);
	if(!c1)
		DSM_LOG_ERR("dsm1 reg failed\n");

	c2 = dsm_register_client(&dev2);
	if(!c2)
		DSM_LOG_ERR("dsm2 reg failed\n");

	c3 = dsm_register_client(&dev3);
	if(!c3)
		DSM_LOG_ERR("dsm3 reg failed\n");

	c4 = dsm_register_client(&dev4);
	if(!c4)
		DSM_LOG_ERR("dsm4 reg failed\n");

	c5 = dsm_register_client(&dev5);
	if(!c5)
		DSM_LOG_ERR("dsm5 reg failed\n");

	dsm_task = kthread_create(dsm_test_thread, NULL, "dsm_thread");
	wake_up_process(dsm_task);

	return 0;
}
module_init(dsm_test);
