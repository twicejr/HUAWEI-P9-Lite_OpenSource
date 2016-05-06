/*******************************************************************************
* All rights reserved, Copyright (C) huawei LIMITED 2012
*------------------------------------------------------------------------------
* File Name   : tc_client_driver.c
* Description :
* Platform    :
* Author      : qiqingchao
* Version     : V1.0
* Date        : 2012.12.10
* Notes       :
*
*------------------------------------------------------------------------------
* Modifications:
*   Date        Author          Modifications
*******************************************************************************/
/*******************************************************************************
 * This source code has been made available to you by HUAWEI on an
 * AS-IS basis. Anyone receiving this source code is licensed under HUAWEI
 * copyrights to use it in any way he or she deems fit, including copying it,
 * modifying it, compiling it, and redistributing it either with or without
 * modifications. Any person who transfers this source code or any derivative
 * work must include the HUAWEI copyright notice and this paragraph in
 * the transferred software.
*******************************************************************************/

#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/kthread.h>
#include <linux/freezer.h>
#include <linux/module.h>
#include <linux/atomic.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#include "tee_client_constants.h"
#include "teek_ns_client.h"
#include "smc.h"
#include "agent.h"
#include "mem.h"
#include "tui.h"



struct __agent_control{
    spinlock_t lock;
    struct list_head agent_list;
};
static struct __agent_control agent_control;

void TC_NS_send_event_reponse_all(void)
{
    struct __smc_event_data *event_data = NULL;
    TC_NS_send_event_reponse(AGENT_FS_ID);
    event_data = find_event_control(AGENT_FS_ID);
    if(event_data)
	event_data->agent_alive = 0;
    TC_NS_send_event_reponse(AGENT_MISC_ID);
    event_data = find_event_control(AGENT_MISC_ID);
    if(event_data)
	event_data->agent_alive = 0;
    TC_NS_send_event_reponse(AGENT_SOCKET_ID);
    event_data = find_event_control(AGENT_SOCKET_ID);
    if(event_data)
	event_data->agent_alive = 0;
    return;
}
struct __smc_event_data* find_event_control(unsigned int agent_id)
{
	struct __smc_event_data *event_data, *tmp_data=NULL;
	unsigned long flags;

	spin_lock_irqsave(&agent_control.lock, flags);
	list_for_each_entry(event_data, &agent_control.agent_list, head){
		if(event_data->agent_id == agent_id){
			tmp_data = event_data;
			break;
		}
	}
	spin_unlock_irqrestore(&agent_control.lock, flags);

	return tmp_data;
}

unsigned int agent_process_work(TC_NS_SMC_CMD *smc_cmd,
			      unsigned int agent_id)
{
	struct __smc_event_data *event_data;

    TCDEBUG("agent_id=0x%x\n", agent_id);
	/* TODO: needs lock */
	event_data = find_event_control(agent_id);

	if(event_data == NULL || event_data->agent_alive == 0){
		/*TODO: if return, the pending task in S can't be resumed!!*/
		TCERR("agent %u not exist\n", agent_id);
		return TEEC_ERROR_GENERIC;
	}

	TCDEBUG("agent_process_work: returning client command");

	/* store tui working device for terminate tui
	 * when this device is closed.
	 */
	if (agent_id == TEE_TUI_AGENT_ID)
		set_tui_attach_device(smc_cmd->dev_file_id);

	event_data->ret_flag = 1;
	/* Keep a copy of the SMC cmd to return to TEE when the work is done */
	memcpy(&event_data->cmd, smc_cmd, sizeof(TC_NS_SMC_CMD));
	/* Wake up the agent that will process the command */
	TCDEBUG("agent_process_work: wakeup the agent");
	wake_up(&event_data->wait_event_wq);
	
	return TEEC_SUCCESS;
}

/*
 * Function:      is_agent_alive
 * Description:   This function check if the special agent is launched.Used For HDCP key.
 *                e.g. If sfs agent is not alive, you can not do HDCP key write to SRAM.
 * Parameters:   agent_id.
 * Return:      1:agent is alive
 *              0:agent not exsit.
 */
int is_agent_alive(unsigned int agent_id)
{
    if (find_event_control(agent_id))
        return 1;
    else
        return 0;
}

int TC_NS_wait_event(unsigned int agent_id)
{
	int ret= -EINVAL;
	struct __smc_event_data *event_data;

	event_data = find_event_control(agent_id);

	if (TC_NS_get_uid() != 0) {
		TCERR("It is a fake tee agent\n");
		return -EACCES;
	}

	TCDEBUG("agent %u waits for command\n", agent_id);
	if (event_data){
		/* wait event will return either 0 or -ERESTARTSYS so just
		 * return it further to the ioctl handler */
		ret = wait_event_interruptible(event_data->wait_event_wq,
					       event_data->ret_flag);
	}

	return ret;
}

int TC_NS_sync_sys_time(TC_NS_Time *tc_ns_time)
{
    TC_NS_SMC_CMD smc_cmd = {0};
    int ret = 0;
    unsigned char uuid[17] = {0};
    TC_NS_Operation operation = {0};
    TC_NS_Time tmp_tc_ns_time = {0};
    if (TC_NS_get_uid() != 0) {
	TCERR("It is a fake tee agent\n");
	return TEEC_ERROR_GENERIC;
    }
    if(!tc_ns_time){
	TCERR("tc_ns_time is NULL input buffer\n");
	return -EINVAL;
    }
    if(copy_from_user(&tmp_tc_ns_time, tc_ns_time, sizeof(TC_NS_Time))) {
	TCERR("copy from user failed\n");
	return -EFAULT;
    }

    uuid[0] = 1;
    smc_cmd.uuid_phys = virt_to_phys(uuid);
    smc_cmd.cmd_id = GLOBAL_CMD_ID_ADJUST_TIME;
    smc_cmd.err_origin = (unsigned int)tmp_tc_ns_time.seconds;
    smc_cmd.ret_val = (unsigned int)tmp_tc_ns_time.millis;
    smc_cmd.operation_phys = virt_to_phys(&operation);

    ret = TC_NS_SMC(&smc_cmd, 0);
    if (ret) {
        TCERR("tee adjust time failed, return error %x\n", ret);
    }
    return ret;
}

int TC_NS_send_event_reponse(unsigned int agent_id)
{
	struct __smc_event_data *event_data = find_event_control(agent_id);

	if (TC_NS_get_uid() != 0) {
	    TCERR("It is a fake tee agent\n");
	    return -1;
	}
	
	TCDEBUG("agent %u sends answer back\n", agent_id);
	if (event_data && event_data->ret_flag) {
		event_data->send_flag = 1;
		event_data->ret_flag = 0;
		/* Send the command back to the TA session waiting for it */
		TC_NS_POST_SMC(&event_data->cmd);
		return 0;
	}
	return -EINVAL;
}

int TC_NS_register_agent(TC_NS_DEV_File* dev_file, unsigned int agent_id,
			 TC_NS_Shared_MEM* shared_mem)
{
    TC_NS_SMC_CMD smc_cmd = {0};
    struct __smc_event_data *event_data=NULL;
    int ret;
    int find_flag = 0;
    unsigned long flags;
    unsigned char uuid[17] = {0};
    TC_NS_Operation operation = {0};

    if (TC_NS_get_uid() != 0) {
	TCERR("It is a fake tee agent\n");
	ret = TEEC_ERROR_GENERIC;
	goto error;
    }

    spin_lock_irqsave(&agent_control.lock, flags);
    list_for_each_entry(event_data, &agent_control.agent_list, head){
        if(event_data->agent_id == agent_id){
            find_flag = 1;
            break;
        }
    }
    spin_unlock_irqrestore(&agent_control.lock, flags);

    if(find_flag){
	if((agent_id == AGENT_FS_ID) || (agent_id == AGENT_MISC_ID) || (agent_id == AGENT_SOCKET_ID)){
	    event_data->ret_flag = 0;
	    event_data->send_flag = 0;
	    event_data->owner = dev_file;
	    event_data->agent_alive = 1;
	    init_waitqueue_head(&(event_data->wait_event_wq));
	    init_waitqueue_head(&(event_data->send_response_wq));
	    ret = TEEC_SUCCESS;
	}
	else
	    ret = TEEC_ERROR_GENERIC;
        goto error;
    }

    if(!shared_mem){
        TCERR("shared mem is not exist\n");
        ret = TEEC_ERROR_GENERIC;
        goto error;
    }

    operation.paramTypes = TEE_PARAM_TYPE_VALUE_INPUT;
    operation.paramTypes = operation.paramTypes << 12;
    operation.params[0].value.a = virt_to_phys(shared_mem->kernel_addr);
    operation.params[0].value.b = SZ_4K;

    uuid[0] = 1;
    smc_cmd.uuid_phys = virt_to_phys(uuid);
    smc_cmd.cmd_id = GLOBAL_CMD_ID_REGISTER_AGENT;
    smc_cmd.operation_phys = virt_to_phys(&operation);
    smc_cmd.agent_id = agent_id;

    ret = TC_NS_SMC(&smc_cmd, 0);

    if(ret == TEEC_SUCCESS){
        event_data = kmalloc(sizeof(struct __smc_event_data), GFP_KERNEL);
        if(!event_data){
            ret = -ENOMEM;
            goto error;
        }
        event_data->agent_id = agent_id;
        mutex_init(&event_data->work_lock);
        event_data->ret_flag = 0;
        event_data->send_flag = 0;
        event_data->buffer = shared_mem;
	event_data->owner = dev_file;
	event_data->agent_alive = 1;
        init_waitqueue_head(&(event_data->wait_event_wq));
        init_waitqueue_head(&(event_data->send_response_wq));
        INIT_LIST_HEAD(&event_data->head);

        spin_lock_irqsave(&agent_control.lock, flags);
        list_add_tail(&event_data->head, &agent_control.agent_list);
        spin_unlock_irqrestore(&agent_control.lock, flags);
    }

error:
    return ret;
}

int TC_NS_unregister_agent(unsigned int agent_id)
{
    struct __smc_event_data *event_data=NULL;
    int ret;
    int find_flag = 0;
    unsigned long flags;
    TC_NS_SMC_CMD smc_cmd = {0};
    unsigned char uuid[17] = {0};
    TC_NS_Operation operation = {0};
    if (TC_NS_get_uid() != 0) {
        TCERR("It is a fake tee agent\n");
        return TEEC_ERROR_GENERIC;
    }

    spin_lock_irqsave(&agent_control.lock, flags);
    list_for_each_entry(event_data, &agent_control.agent_list, head){
        if(event_data->agent_id == agent_id){
            find_flag = 1;
            list_del(&event_data->head);
            break;
        }
    }
    spin_unlock_irqrestore(&agent_control.lock, flags);

    if(!find_flag){
        TCERR("agent is not found\n");
        return TEEC_ERROR_GENERIC;
    }
    operation.paramTypes = TEE_PARAM_TYPE_VALUE_INPUT;
    operation.paramTypes = operation.paramTypes << 12;
    operation.params[0].value.a= virt_to_phys(event_data->buffer->kernel_addr);
    operation.params[0].value.b = SZ_4K;

    uuid[0] = 1;
    smc_cmd.uuid_phys = virt_to_phys(uuid);
    smc_cmd.cmd_id = GLOBAL_CMD_ID_UNREGISTER_AGENT;
    smc_cmd.operation_phys = virt_to_phys(&operation);
    smc_cmd.agent_id = agent_id;

    mutex_lock(&event_data->work_lock);
    TCDEBUG("Unregistering agent %u\n", agent_id);
    ret = TC_NS_SMC(&smc_cmd, 0);
    mutex_unlock(&event_data->work_lock);

    kfree(event_data);

    return ret;
}

int TC_NS_unregister_agent_client(TC_NS_DEV_File* dev_file)
{
    struct __smc_event_data *event_data = NULL, *tmp;
    list_for_each_entry_safe(event_data, tmp, &agent_control.agent_list, head){
        if(event_data->owner == dev_file) {
		TC_NS_unregister_agent(event_data->agent_id);
        }
    }
    return TEEC_SUCCESS;
}

int TC_NS_alloc_exception_mem(void)
{
    TC_NS_SMC_CMD smc_cmd = {0};
    int ret = TEEC_ERROR_GENERIC;
    unsigned char uuid[17] = {0};
    void *exception_mem;
    TC_NS_Operation operation = {0};

    exception_mem = (void *)kzalloc(EXCEPTION_MEM_SIZE, GFP_KERNEL);
    if(!exception_mem) {
	    return TEEC_ERROR_GENERIC;
    }

    TCDEBUG(KERN_INFO"exception_mem virt addr = 0x%lx, phys addr = %lx\n", exception_mem, virt_to_phys(exception_mem));

    //memset(&smc_cmd, 0, sizeof(TC_NS_SMC_CMD));
    uuid[0] = 1;
    smc_cmd.uuid_phys = virt_to_phys(uuid);
    smc_cmd.cmd_id = GLOBAL_CMD_ID_ALLOC_EXCEPTION_MEM;

    operation.paramTypes = TEE_PARAM_TYPE_VALUE_INPUT;
    operation.paramTypes = operation.paramTypes << 12;
    operation.params[0].value.a= virt_to_phys(exception_mem);
    operation.params[0].value.b = EXCEPTION_MEM_SIZE;

    smc_cmd.operation_phys = virt_to_phys(&operation);

    ret = TC_NS_SMC(&smc_cmd, 0);

    return ret;
}

static int def_tee_agent_work(struct tee_agent_kernel_ops* agent_instance)
{
    int ret;

    while (!kthread_should_stop()) {
        TCDEBUG("%s agent loop++++\n", agent_instance->agent_name);
        ret = TC_NS_wait_event(agent_instance->agent_id);
        if (ret) {
            TCERR("%s wait event fail\n", agent_instance->agent_name);
            break;
        }

        if (agent_instance->tee_agent_work)
            agent_instance->tee_agent_work(agent_instance);

        ret = TC_NS_send_event_reponse(agent_instance->agent_id);
        if (ret) {
            TCERR("%s send event response fail\n", agent_instance->agent_name);
            break;
        }
        TCDEBUG("%s agent loop----\n", agent_instance->agent_name);
    }

    return ret;
}

#define AGENT_BUFF_SIZE (4*1024)
static int def_tee_agent_run(struct tee_agent_kernel_ops* agent_instance)
{
    TC_NS_Shared_MEM *shared_mem = NULL;
    TC_NS_DEV_File dev;
    int ret;

    /*1. Allocate agent buffer */
    shared_mem = tc_mem_allocate(&dev, AGENT_BUFF_SIZE);
    if (IS_ERR(shared_mem)) {
        TCERR("allocate agent buffer fail\n");
        ret = PTR_ERR(shared_mem);
        goto out;
    }
    agent_instance->agent_buffer = shared_mem;

    /*2. Register agent buffer to TEE */
    ret = TC_NS_register_agent(&dev, agent_instance->agent_id, shared_mem);
    if (ret) {
        TCERR("register agent buffer fail\n");
        ret = -1;
        goto out;
    }

    /*3. Creat thread to run agent */
    agent_instance->agent_thread
        = kthread_run(def_tee_agent_work, agent_instance, "agent_%s", agent_instance->agent_name);
    if (IS_ERR(agent_instance->agent_thread)) {
        TCERR("kthread creat fail\n");
        ret = PTR_ERR(agent_instance->agent_thread);
        agent_instance->agent_thread = NULL;
        goto out;
    }
    return 0;

out:
    if(!IS_ERR_OR_NULL(shared_mem))
        tc_mem_free(shared_mem);
    if (!IS_ERR_OR_NULL(agent_instance->agent_thread)) {
        kthread_stop(agent_instance->agent_thread);
        agent_instance->agent_thread = NULL;
    }

    return ret;
}

static int def_tee_agent_stop(struct tee_agent_kernel_ops* agent_instance)
{
    TC_NS_send_event_reponse(agent_instance->agent_id);
    TC_NS_unregister_agent(agent_instance->agent_id);
    if (!IS_ERR_OR_NULL(agent_instance->agent_thread)) {
        kthread_stop(agent_instance->agent_thread);
    }
    return 0;
}

static struct list_head tee_agent_list;
static struct tee_agent_kernel_ops def_tee_agent_ops = {
    .agent_name = "default",
    .agent_id = 0,
    .tee_agent_init = NULL,
    .tee_agent_run = def_tee_agent_run,
    .tee_agent_work = NULL,
    .tee_agent_exit = NULL,
    .tee_agent_stop = def_tee_agent_stop,
    .tee_agent_crash_work = NULL,
    .list = LIST_HEAD_INIT(def_tee_agent_ops.list)
};

static int tee_agent_kernel_init(void)
{
    struct tee_agent_kernel_ops *agent_ops = NULL;
    int ret = 0;

    list_for_each_entry(agent_ops, &tee_agent_list, list){
        /* Check the agent validity */
        if ((agent_ops->agent_id == 0) || (agent_ops->agent_name == NULL) ||
            (agent_ops->tee_agent_work == NULL)) {
            TCERR("agent is invalid\n");
            continue;
        }
        TCDEBUG("ready to init %s agent, id=0x%x\n",
            agent_ops->agent_name, agent_ops->agent_id);

        /* Initialize the agent */
        if (agent_ops->tee_agent_init)
            ret = agent_ops->tee_agent_init(agent_ops);
        else if(def_tee_agent_ops.tee_agent_init)
            ret = def_tee_agent_ops.tee_agent_init(agent_ops);
        if (ret) {
            TCERR("tee_agent_init %s failed\n", agent_ops->agent_name);
            continue;
        }

        /* Run the agent */
        if (agent_ops->tee_agent_run)
            ret = agent_ops->tee_agent_run(agent_ops);
        else if(def_tee_agent_ops.tee_agent_run)
            ret = def_tee_agent_ops.tee_agent_run(agent_ops);
        if (ret) {
            TCERR("tee_agent_run %s failed\n", agent_ops->agent_name);
            if (agent_ops->tee_agent_exit)
                agent_ops->tee_agent_exit(agent_ops);
            continue;
        }
    }

    return 0;
}

static int tee_agent_kernel_exit(void)
{
    struct tee_agent_kernel_ops *agent_ops = NULL;

    list_for_each_entry(agent_ops, &tee_agent_list, list) {
        /* Uninitialize the agent */
        if (agent_ops->tee_agent_exit)
            agent_ops->tee_agent_exit(agent_ops);
        else if (def_tee_agent_ops.tee_agent_exit)
            def_tee_agent_ops.tee_agent_exit(agent_ops);

        /* Stop the agent */
        if (agent_ops->tee_agent_stop)
            agent_ops->tee_agent_stop(agent_ops);
        else if (def_tee_agent_ops.tee_agent_stop)
            def_tee_agent_ops.tee_agent_stop(agent_ops);
    }
    return 0;
}

int tee_agent_clear_work(TC_NS_ClientContext *context, unsigned int dev_file_id)
{
    struct tee_agent_kernel_ops *agent_ops = NULL;

    list_for_each_entry(agent_ops, &tee_agent_list, list) {
        if (agent_ops->tee_agent_crash_work)
            agent_ops->tee_agent_crash_work(agent_ops, context, dev_file_id);
    }
    return 0;
}

int tee_agent_kernel_register(struct tee_agent_kernel_ops* new_agent)
{
    INIT_LIST_HEAD(&new_agent->list);
    list_add_tail(&new_agent->list, &tee_agent_list);
    return 0;
}

#ifdef CONFIG_HISI_MMC_SECURE_RPMB
extern int rpmb_agent_register(void);
#endif
int agent_init(void)
{
    spin_lock_init(&agent_control.lock);
    INIT_LIST_HEAD(&agent_control.agent_list);

    INIT_LIST_HEAD(&tee_agent_list);
#ifdef CONFIG_HISI_MMC_SECURE_RPMB
    rpmb_agent_register();
#endif
    tee_agent_kernel_init();
    return 0;
}

int agent_exit(void)
{
    tee_agent_kernel_exit();
    return 0;
}
