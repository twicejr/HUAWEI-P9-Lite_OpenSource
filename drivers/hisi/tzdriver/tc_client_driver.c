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
#include <linux/fs.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <asm/cacheflush.h>
#include <linux/kthread.h>
#include <linux/freezer.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/of_irq.h>
#include <linux/atomic.h>
#include <linux/interrupt.h>
//#define TC_DEBUG
#include "smc.h"
#include "tee_client_constants.h"
#include "tc_ns_client.h"
#include "teek_ns_client.h"
#include "agent.h"
#include "mem.h"
#include "tee_rdr_register.h"
#include "tui.h"

#define ROUND_UP(N, S) ((((N) + (S) - 1) / (S)) * (S))

#define TEEC_PARAM_TYPES( param0Type, param1Type, param2Type, param3Type) \
    ((param3Type) << 12 | (param2Type) << 8 | (param1Type) << 4 | (param0Type))

#define TEEC_PARAM_TYPE_GET( paramTypes, index) \
    (((paramTypes) >> (4*(index))) & 0x0F)

enum timer_class_type {
    /* timer event using timer10*/
    TIMER_GENERIC,
    /* timer event using RTC*/
    TIMER_RTC
};
typedef struct{
    unsigned int type;
    unsigned int timer_id;
    unsigned int timer_class;
    unsigned int reserved2;
} TEEC_timer_property;
typedef struct {
    unsigned int dev_file_id;
    unsigned char uuid[16];
    unsigned int session_id;
    TEEC_timer_property property;
} tc_notify_data;

#define IRQ_TYPE_TP (1)  //irq from touchscreen
#define IRQ_TYPE_FP (2)  //irq from fingerprint
struct ts_tui_finger{
	int status;
	int x;
	int y;
	int area;
	int pressure;
	int orientation;
	int major;
	int minor;
	int event;
};
#define TS_TUI_MAX_FINGER (10)
struct ts_tui_fingers{
    struct ts_tui_finger fingers[TS_TUI_MAX_FINGER];
    int cur_finger_number;
    unsigned int gesture_wakeup_value;
    unsigned int special_button_key;
    unsigned int special_button_flag;
};
typedef struct {
    int irq_type;
    union {
        struct ts_tui_fingers tui_notify_data;
        int reserved[32];
    };
} tp_notify_data_t;
/**
	notify data
*/
#define NOTIFY_DATA_MAX_NUM  7
#define NOTIFY_DATA_ENTRY_SIZE  512
typedef union {
	tc_notify_data notify_context_timer;
	char notify_context_tp[504];
} notify_context;

typedef struct{
	uint32_t entry_type;
	uint32_t filled;
	notify_context notify_context;
} notify_data_entry;

enum notify_data_entry_type {
	NOTIFY_DATA_ENTRY_RESERVED,
	NOTIFY_DATA_ENTRY_TIMER,
	NOTIFY_DATA_ENTRY_TP,
	NOTIFY_DATA_ENTRY_MAX = 8
};

static void *notify_data = NULL;
static notify_data_entry *notify_data_entry_timer = NULL;
static notify_data_entry *notify_data_entry_tp = NULL;

static DEFINE_MUTEX(notify_data_lock);
static DEFINE_MUTEX(shared_buf_rel_lock);
static DEFINE_MUTEX(load_app_lock);
static int load_app_lock_flag = 0;
static DEFINE_MUTEX(device_file_cnt_lock);
/************global reference start***********/
static dev_t tc_ns_client_devt;
static struct class *driver_class;
static struct cdev tc_ns_client_cdev;
struct device_node *np = NULL;
static unsigned int device_file_cnt = 1;

typedef struct tag_TC_NS_DEV_List{
    unsigned int dev_file_cnt;
    struct mutex dev_lock;
    struct list_head dev_file_list;

} TC_NS_DEV_List;
static TC_NS_DEV_List tc_ns_dev_list;
typedef struct tag_TC_NS_Callback{
    unsigned char uuid[16];
    struct mutex callback_lock;
    void (* callback_func)(void *);
    struct list_head head;
}TC_NS_Callback;
typedef struct tag_TC_NS_Callback_List{
    unsigned int callback_count;
    struct mutex callback_list_lock;
    struct list_head callback_list;
} TC_NS_Callback_List;
static TC_NS_Callback_List ta_callback_func_list;

static TC_NS_DEV_List tc_ns_dev_list;

static struct task_struct *teecd_task = NULL;
static unsigned int agent_count=0;
/************global reference end*************/

typedef unsigned int (*rtc_timer_callback_func) (TEEC_timer_property*);
static int g_timer_type = 0;

int TC_NS_RegisterServiceCallbackFunc(char *uuid,  void *func, void *private_data);
void callback_demo_main(char *uuid);

static int TC_NS_SharedMemoryRelease(TC_NS_DEV_File *dev_file, void* user_addr);
extern int tui_send_event(int event);

notify_data_entry * acquire_notify_data_entry(int entry_type)
{
	/**every notify data entry is 512bytes;
	   total notify data mem is 4K(one page)*/
	int i = 0;
	notify_data_entry *ptr = (notify_data_entry *)notify_data;
	while(i < NOTIFY_DATA_MAX_NUM){
		if(ptr->entry_type == NOTIFY_DATA_ENTRY_RESERVED){
			ptr->entry_type = entry_type;
			ptr->filled = 0;
			break;
		}
		ptr++;
		i++;
	}
    return ptr;
}

static void TST_get_timer_type(int * type)
{
    *type = g_timer_type;
    return;
}
int tc_client_call(TC_NS_ClientContext *context, TC_NS_DEV_File *dev_file,
		   uint8_t flags);
int tc_user_param_valid(TC_NS_ClientContext *client_context, int n);

TC_NS_Service *tc_find_service(struct list_head *services, char *uuid)
{
    TC_NS_Service* service = NULL;
    //need service init or not
    list_for_each_entry(service, services, head){
	    if(memcmp(service->uuid, uuid, 16) == 0){
		    return service;
	    }
    }
    return NULL;
}

TC_NS_Session *tc_find_session(struct list_head *session_list,
					  unsigned int session_id)
{
	TC_NS_Session *session;
	list_for_each_entry(session, session_list, head){
		if(session->session_id == session_id){
			return session;
		}
	}

	return NULL;
}

static int close_session(TC_NS_DEV_File *dev, unsigned char *uuid, unsigned int session_id)
{
    TC_NS_ClientContext context;
    int ret;

    memset(&context, 0, sizeof(TC_NS_ClientContext));
    memcpy(context.uuid, uuid, sizeof(context.uuid));
    context.session_id = session_id;
    context.cmd_id = GLOBAL_CMD_ID_CLOSE_SESSION;

    ret = tc_client_call(&context, dev, TC_CALL_GLOBAL | TC_CALL_SYNC);
    if(ret)
        TCERR("close session failed, ret=0x%x\n", ret);
    return ret;
}

static int kill_session(TC_NS_DEV_File *dev, unsigned char *uuid, unsigned int session_id)
{
    TC_NS_ClientContext context;
    int ret;

    memset(&context, 0, sizeof(TC_NS_ClientContext));
    memcpy(context.uuid, uuid, sizeof(context.uuid));
    context.session_id = session_id;
    context.cmd_id = GLOBAL_CMD_ID_KILL_TASK;
    TCDEBUG("dev_file_id=%d\n", dev->dev_file_id);

    //do clear work in agent
    tee_agent_clear_work(&context, dev->dev_file_id);

    ret = tc_client_call(&context, dev, TC_CALL_GLOBAL | TC_CALL_SYNC);
    if(ret)
        TCERR("close session failed, ret=0x%x\n", ret);
    return ret;
}

extern int ts_tui_report_input(void *finger_data);

#ifdef TC_ASYNC_NOTIFY_SUPPORT
static void tc_notify_fn(struct work_struct *dummy)
{
    TC_NS_DEV_File *temp_dev_file;
    TC_NS_Service*temp_svc;
    TC_NS_Session*temp_ses = NULL;
    int enc_found = 0;
    rtc_timer_callback_func callback_func;
    TC_NS_Callback *callback_func_t;
    tp_notify_data_t *tp_nofity_data;
    tc_notify_data *tc_notify_data_timer = &(notify_data_entry_timer->notify_context.notify_context_timer);

    TCDEBUG("step into ipi_secure_notify\n");
    if(notify_data_entry_tp != NULL && notify_data_entry_tp->filled){
        tp_nofity_data = (tp_notify_data_t *)(&notify_data_entry_tp->notify_context.notify_context_tp);
        if (tp_nofity_data->irq_type == IRQ_TYPE_FP) {
            notify_data_entry_tp->filled = 0;
            tui_fp_notify();
            return;
        }
    }

    if(notify_data_entry_timer == NULL) {
        TCERR("notify_data is NULL\n");
        //TODO: send tp to touch driver
        return;
    }
	if(!notify_data_entry_timer->filled){
		TCDEBUG("notify_data is not filled\n");
		return;
	}else{
		notify_data_entry_timer->filled = 0;
	}

    TC_TIME_DEBUG("notify_data timer type is 0x%x, timer ID is 0x%x\n", tc_notify_data_timer->property.type, tc_notify_data_timer->property.timer_id);

    mutex_lock(&ta_callback_func_list.callback_list_lock);
    list_for_each_entry(callback_func_t, &ta_callback_func_list.callback_list, head){
        if(memcmp(callback_func_t->uuid, tc_notify_data_timer->uuid, 16) == 0){
            if (tc_notify_data_timer->property.timer_class == TIMER_RTC) {
                TC_TIME_DEBUG("start to call callback func\n");
                callback_func = (rtc_timer_callback_func)(callback_func_t->callback_func);
                (void)(callback_func)(&(tc_notify_data_timer->property));
                TC_TIME_DEBUG("end to call callback func\n");
            }
            else if (tc_notify_data_timer->property.timer_class == TIMER_GENERIC) {
                TC_TIME_DEBUG("timer60 do not need to  call callback func\n");
            }
        }
    }
    mutex_unlock(&ta_callback_func_list.callback_list_lock);

    mutex_lock(&tc_ns_dev_list.dev_lock);
    list_for_each_entry(temp_dev_file, &tc_ns_dev_list.dev_file_list,head) {
	    TCDEBUG("dev file id1 = %d, id2 = %d\n",temp_dev_file->dev_file_id,
		    tc_notify_data_timer->dev_file_id);
	    if(temp_dev_file->dev_file_id == tc_notify_data_timer->dev_file_id){
		    temp_svc = tc_find_service(&temp_dev_file->services_list,
					    tc_notify_data_timer->uuid);
		    if (temp_svc) {
			    temp_ses = tc_find_session(&temp_svc->session_list,
						    tc_notify_data_timer->session_id);
			    if(temp_ses) {
				    TCDEBUG("send cmd ses id %d \n",temp_ses->session_id);
				    enc_found = 1;
				    break;
			    }
			    break;
		    }
		    break;
	    }

    }
    mutex_unlock(&tc_ns_dev_list.dev_lock);
    if (tc_notify_data_timer->property.timer_class == TIMER_GENERIC) {
        TC_TIME_DEBUG("timer60 wake up event\n");
        if(enc_found && temp_ses) {
            temp_ses->wait_data.send_wait_flag = 1;
            wake_up_interruptible(&temp_ses->wait_data.send_cmd_wq);
        }
    }
    else {
        TC_TIME_DEBUG("RTC do not need to wakeup\n");
    }
    return;
}

static DECLARE_WORK(tc_notify_work, tc_notify_fn);

static irqreturn_t tc_secure_notify(int irq, void *dev_id)
{
    tp_notify_data_t *tp_nofity_data;
    if(notify_data_entry_tp != NULL && notify_data_entry_tp->filled){
        tp_nofity_data = (tp_notify_data_t *)(&notify_data_entry_tp->notify_context.notify_context_tp);
        if(tp_nofity_data->irq_type == IRQ_TYPE_TP) {
#if defined (CONFIG_TEE_TUI)
			ts_tui_report_input((void *)&tp_nofity_data->tui_notify_data);
#endif
            notify_data_entry_tp->filled = 0;
            //TODO: send tp to touch driver
        }
        else if (tp_nofity_data->irq_type == IRQ_TYPE_FP) {
            schedule_work(&tc_notify_work);
            notify_data_entry_tp->filled = 0;
#if defined (CONFIG_TEE_TUI)
            tui_fp_notify();
#endif
        }
    }else{
        schedule_work(&tc_notify_work);
    }
    tc_smc_wakeup();
    return IRQ_HANDLED;
}

#endif

static int TC_NS_ServiceInit(TC_NS_DEV_File* dev_file, unsigned char* uuid, TC_NS_Service** new_service){
    int ret = 0;
    TC_NS_Service* service;
    TC_NS_Service* temp;

    service = (TC_NS_Service*)kzalloc(sizeof(TC_NS_Service), GFP_KERNEL);
    if(!service){
        TCERR("kmalloc failed \n");
        ret = -ENOMEM;
        goto error;
    }

    memcpy(service->uuid, uuid, 16);
    dev_file->service_cnt++;
    INIT_LIST_HEAD(&service->session_list);
    mutex_init(&service->session_lock);
    mutex_lock(&dev_file->service_lock);
    list_add_tail(&service->head, &dev_file->services_list);
    mutex_unlock(&dev_file->service_lock);
    *new_service = service;
    goto clean;

error:
    if (!list_empty(&dev_file->services_list)) {
        mutex_lock(&dev_file->service_lock);
        list_for_each_entry_safe(service, temp, &dev_file->services_list, head){
            list_del(&service->head);
            kfree(service);
        }
        mutex_unlock(&dev_file->service_lock);
    }

clean:
    return ret;
}

uint32_t TC_NS_get_uid(void)
{
	struct task_struct *task = current;
	const struct cred *cred;
	cred = get_task_cred(task);
	if (!cred) {
		TCERR("failed to get task cred, so cannot get uid of the task\n");
		return -1;
	}
	TCDEBUG("current uid is %d\n", cred->uid);
	return cred->uid;
}

/* Modify the client context so params id 2 and 3 contain temp pointers to the
 * public key and package name for the open session. This is used for the 
 * TEEC_LOGIN_IDENTIFY open session method */
static int set_login_information(TC_NS_DEV_File* dev_file,
				 TC_NS_ClientContext *context)
{
	/* The daemon has failed to get login information or not supplied */
	if (dev_file->pkg_name_len == 0) {
		return -1;
	}
	/* get package name len and package name */
	context->params[3].memref.size_addr = (__u64)&dev_file->pkg_name_len;
	/* The 3rd parameter buffer points to the pkg name buffer in the 
	 * device file pointer */
	context->params[3].memref.buffer = (__u64)dev_file->pkg_name;

	/* Set public key len and public key*/
	if (dev_file->pub_key_len != 0) {
		context->params[2].memref.size_addr = (__u64)&dev_file->pub_key_len;
		context->params[2].memref.buffer = (__u64)dev_file->pub_key;
	} else {
		uint32_t ca_uid;
		/* If get public key failed, then get uid in kernel */
		ca_uid = TC_NS_get_uid();
		if (ca_uid == -1) {
			TCERR("Failed to get uid of the task\n");
			goto error;
		}
		dev_file->pub_key_len = sizeof(ca_uid);
		context->params[2].memref.size_addr  = (__u64)&dev_file->pub_key_len;

		memcpy(dev_file->pub_key, &ca_uid, dev_file->pub_key_len);
		context->params[2].memref.buffer = (__u64)dev_file->pub_key;
	}

	/* Now we mark the 2 parameters as input temp buffers */
	context->paramTypes = TEEC_PARAM_TYPES(
			       TEEC_PARAM_TYPE_GET(context->paramTypes, 0),
			       TEEC_PARAM_TYPE_GET(context->paramTypes, 1),
			       TEEC_MEMREF_TEMP_INPUT,
			       TEEC_MEMREF_TEMP_INPUT);

	return 0;
error:
	return -1;
}

static int TC_NS_Client_Login(TC_NS_DEV_File* dev_file, void __user *buffer)
{
	int ret = -EINVAL;
	uint8_t *cert_buffer, *buf;

	if(dev_file->login_setup) {
		TCERR("Login information cannot be set twice!\n");
		return -EINVAL;
	}

	dev_file->login_setup = 1;

	if (buffer == NULL) {
		/* We accept no debug information because the daemon might
		 * have failed */
		TCDEBUG("No debug information\n");
		dev_file->pkg_name_len = 0;
		dev_file->pub_key_len = 0;
		return 0;
	}
#define CERT_BUFFER_SIZE (MAX_PACKAGE_NAME_LEN + MAX_PUBKEY_LEN +\
			  sizeof(dev_file->pkg_name_len) + \
			  sizeof(dev_file->pub_key_len))
	buf = cert_buffer = kmalloc(CERT_BUFFER_SIZE, GFP_KERNEL);
	if(!cert_buffer) {
		TCERR("Failed to allocate login buffer!");
		return -EFAULT;
	}

	/* GET PACKAGE NAME AND APP CERTIFICATE:
	 * The proc_info format is as follows:
	 * package_name_len(4 bytes) || package_name || apk_cert_len(4 bytes) || apk_cert.
	 * or package_name_len(4 bytes) || package_name || exe_uid_len(4 bytes) || exe_uid.
	 * The apk certificate format is as follows:
	 * modulus_size(4bytes) ||modulus buffer || exponent size || exponent buffer
	 */

	/* get package name len and package name */
	if(copy_from_user(cert_buffer, buffer, CERT_BUFFER_SIZE)) {
		TCERR("Failed to get user login info!\n");
		ret = -EINVAL;
		goto error;
	}
	memcpy(&dev_file->pkg_name_len, cert_buffer,
	       sizeof(dev_file->pkg_name_len));
	TCDEBUG("package_name_len is %u\n", dev_file->pkg_name_len);
	if(dev_file->pkg_name_len == 0 ||
	   dev_file->pkg_name_len >= MAX_PACKAGE_NAME_LEN) {
		TCERR("Invalid size of package name len login info!\n");
		ret = -EINVAL;
		goto error;
	}

	cert_buffer += sizeof(dev_file->pkg_name_len);
	strncpy(dev_file->pkg_name, cert_buffer, dev_file->pkg_name_len);
	TCDEBUG("package name is %s\n", dev_file->pkg_name);

	cert_buffer += dev_file->pkg_name_len;

	/* get public key len and public key */
	memcpy(&dev_file->pub_key_len, cert_buffer, sizeof(dev_file->pub_key_len));
	TCDEBUG("publick_key_len is %d\n", dev_file->pub_key_len);
	if(dev_file->pub_key_len >  MAX_PUBKEY_LEN) {
		TCERR("Invalid public key length in login info!\n");
		ret = -EINVAL;
		goto error;
	}
	if (dev_file->pub_key_len != 0) {
		cert_buffer += sizeof(dev_file->pub_key_len);
		TCDEBUG("public_key first 4 bytes %x,%x,%x,%x\n", cert_buffer[0],
			cert_buffer[1], cert_buffer[2], cert_buffer[3]);
		memcpy(dev_file->pub_key, cert_buffer, dev_file->pub_key_len);
		cert_buffer += dev_file->pub_key_len;
	}

	ret = 0;
error:
	kfree(buf);
	return ret;
}

int TC_NS_OpenSession(TC_NS_DEV_File *dev_file, TC_NS_ClientContext *context)
{
	int ret = -EINVAL;
	TC_NS_Service *service;
	TC_NS_Session *session;
	bool success = false;
	uint8_t flags = TC_CALL_GLOBAL;

	mutex_lock(&tc_ns_dev_list.dev_lock);
	service = tc_find_service(&dev_file->services_list, context->uuid);
	/* Need service init or not */
	if (service) {
		goto find_service;
	}
	/* Create a new service if we couldn't find it in list */
	ret = TC_NS_ServiceInit(dev_file, context->uuid, &service);
	if(ret){
		TCERR("service init failed");
	}
	else
		goto find_service;
	mutex_unlock(&tc_ns_dev_list.dev_lock);
	TCERR("find service failed");
	return ret;

find_service:
	mutex_unlock(&tc_ns_dev_list.dev_lock);
	session = (TC_NS_Session *)kzalloc(sizeof(TC_NS_Session), GFP_KERNEL);
	if(!session) {
		TCERR("kmalloc failed\n");
		ret =  -ENOMEM;
		return ret;
	}

	if (context->login.method == TEEC_LOGIN_IDENTIFY) {
		/* Check if params 0 and 1 are valid */
		if (tc_user_param_valid(context, 0) ||
		    tc_user_param_valid(context, 1)) {
			ret = -EFAULT;
			goto error;
		}
		ret = set_login_information(dev_file, context);
		TCDEBUG("login method is IDENTIFY\n");
		if (ret != 0) {
			TCERR("set_login_information failed ret =%d\n", ret);
			goto error;
		}
		flags |= TC_CALL_LOGIN;
	}
	mutex_init(&session->ta_session_lock);
	mutex_lock(&tc_ns_dev_list.dev_lock);
	//send smc
	ret = tc_client_call(context, dev_file, flags);
	mutex_unlock(&tc_ns_dev_list.dev_lock);
	/*
	 * 小于0是系统出错，直接返回负数
	 * 大于0是SMC返回错误，需要copy_to_user，再返回正数
	 * 等于0是正确，需要copy_to_user，再返回0
	 */
	if (ret < 0) {
		TCERR("smc_call returns error, ret=0x%x\n", ret);
		goto error;
	} else if (ret > 0) {
		TCERR("smc_call returns error, ret>0\n");
		goto error1;
	} else {
		TCDEBUG("smc_call returns right\n");
		success = true;
	}
	session->session_id = context->session_id;
	TCDEBUG("------------>session id is %x\n",context->session_id);
#ifdef TC_ASYNC_NOTIFY_SUPPORT
	session->wait_data.send_wait_flag=0;
	init_waitqueue_head(&session->wait_data.send_cmd_wq);
#endif

	mutex_lock(&service->session_lock);
	list_add_tail(&session->head, &service->session_list);
	mutex_unlock(&service->session_lock);

error1:
	if (success)
		return ret;
error:
	kfree(session);
	return ret;
}

int TC_NS_CloseSession(TC_NS_DEV_File *dev_file,  TC_NS_ClientContext *context)
{
    int ret = -EINVAL;
    TC_NS_Service *service;
    TC_NS_Session *session;

    mutex_lock(&tc_ns_dev_list.dev_lock);
    service = tc_find_service(&dev_file->services_list, context->uuid);
    if(service) {
	    session = tc_find_session(&service->session_list, context->session_id);
	    if(session) {
		    mutex_lock(&session->ta_session_lock);
		    ret = close_session(dev_file, context->uuid, context->session_id);
		    mutex_unlock(&session->ta_session_lock);
		    if (ret == TEEC_SUCCESS) {
			    TCDEBUG("close session smc success.\n");
		    } else {
			    TCERR("close session smc failed, ret=%d, context.returns.code=%x, context.returns.origin=%x\n", ret, context->returns.code, context->returns.origin);
		    }
		    list_del(&session->head);
		    kfree(session);
		    ret = TEEC_SUCCESS;
	    }
    }
#if 0
session_close_fail:
    if(ret == TEEC_SUCCESS)
        ret = TEEC_ERROR_GENERIC;
    TCDEBUG("close session failed\n");
#endif
    mutex_unlock(&tc_ns_dev_list.dev_lock);
    return ret;
}

int TC_NS_Send_CMD(TC_NS_DEV_File *dev_file, TC_NS_ClientContext *context)
{
    int ret = -EINVAL;
    TC_NS_Service *service;
    TC_NS_Session *session;

    TCDEBUG("session id :%x\n",context->session_id);
    //check sessionid is validated or not
    mutex_lock(&tc_ns_dev_list.dev_lock);
    service = tc_find_service(&dev_file->services_list, context->uuid);
    if (service) {
	    session = tc_find_session(&service->session_list, context->session_id);
	    if (session) {
		    TCDEBUG("send cmd find session id %x\n", context->session_id);
		    goto find_session;
	    }
    }
    mutex_unlock(&tc_ns_dev_list.dev_lock);
    TCERR("send cmd can not find session id %d\n", context->session_id);
    return ret;

find_session:
    mutex_unlock(&tc_ns_dev_list.dev_lock);

    //send smc
	mutex_lock(&session->ta_session_lock);
    ret = tc_client_call(context, dev_file, 0);
	mutex_unlock(&session->ta_session_lock);


    //TCVERBOSE("end of send smc call to non_secure in tc_ns send _cmd\n");

    /*
     * 小于0是系统出错，可以直接返回，
     * 大于0是SMC返回错误，需要copy_to_user
     * 等于0是正确，需要copy_to_user
     */
    if (ret < 0) {
        TCERR("smc_call returns error, ret=%d\n", ret);
        goto error;
    } else if (ret > 0) {
        TCERR("smc_call returns error, ret=%d\n", ret);
    } else {
        TCDEBUG("smc_call returns right\n");
    }
error:
    return ret;
}
static int TC_NS_TST_CMD(TC_NS_DEV_File *dev_id, void* argp){
    int ret = 0;
    TC_NS_ClientContext client_context;
    int cmd_id;
    int timer_type;

    if(!argp){
	TCERR("argp is NULL input buffer\n");
	ret = -EINVAL;
	return ret;
    }

    if(copy_from_user(&client_context, argp, sizeof(TC_NS_ClientContext))){
        TCERR("copy from user failed\n");
        ret =  -ENOMEM;
        return ret;
    }

    //a_addr contain the command id
    if(copy_from_user(&cmd_id, (void *)client_context.params[0].value.a_addr, sizeof(cmd_id))){
        TCERR("copy from user failed:cmd_id\n");
        ret =  -ENOMEM;
        return ret;
    }
    switch(cmd_id)
    {
        case TST_CMD_01:
            callback_demo_main((char *)client_context.uuid);
            break;
        case TST_CMD_02:
            TST_get_timer_type(&timer_type);
            if(copy_to_user((void *)client_context.params[1].value.a_addr, &timer_type, sizeof(timer_type))){
                TCERR("copy to user failed:timer_type\n");
                ret =  -ENOMEM;
                return ret;
            }
            break;
        default:
            break;
    }
    if(copy_to_user(argp, (void *)&client_context, sizeof(client_context))){
        TCERR("copy to user failed:client context\n");
        ret =  -ENOMEM;
        return ret;
    }
    return ret;
}
static int TC_NS_SharedMemoryRelease(TC_NS_DEV_File *dev_file, void* user_addr)
{
    int ret = TEEC_SUCCESS;
    TC_NS_Shared_MEM *shared_mem, *shared_mem_temp;

    mutex_lock(&tc_ns_dev_list.dev_lock);
    list_for_each_entry_safe(shared_mem, shared_mem_temp, &dev_file->shared_mem_list, head){
	    if(shared_mem && shared_mem->user_addr == user_addr){
		    list_del(&shared_mem->head);
		    tc_mem_free(shared_mem);
		    dev_file->shared_mem_cnt--;
		    break;
	    }
    }
    mutex_unlock(&tc_ns_dev_list.dev_lock);

    return ret;
}

#ifdef TC_ASYNC_NOTIFY_SUPPORT
void timer_callback_func(TEEC_timer_property * timer_property)
{
	TC_TIME_DEBUG("timer_property->type = %x, timer_property->timer_id = %x\n", timer_property->type, timer_property->timer_id);
    g_timer_type = (int)timer_property->type;
}

void callback_demo_main(char *uuid)
{
	int ret;
    TC_TIME_DEBUG("step into callback_demo_main\n");
	ret = TC_NS_RegisterServiceCallbackFunc(uuid,  (void *)&timer_callback_func, NULL);
    if (ret != 0)
        TCERR("failed to TC_NS_RegisterServiceCallbackFunc\n");

}

int TC_NS_RegisterServiceCallbackFunc(char *uuid,  void *func, void *private_data)
{
    TC_NS_Callback *callback_func;
    TC_NS_Callback *new_callback = NULL;
    int ret = 0;

    mutex_lock(&ta_callback_func_list.callback_list_lock);
    list_for_each_entry(callback_func, &ta_callback_func_list.callback_list, head){
        if(memcmp(callback_func->uuid, uuid, 16) == 0){
            callback_func->callback_func = (void (*)(void *))func;
            TCDEBUG("succeed to find uuid ta_callback_func_list\n");
            goto find_callback;
        }
    }

    //create a new callback struct if we couldn't find it in list
    TCDEBUG("failed to find callback func in list, malloc for ta callback func\n");
    new_callback = (TC_NS_Callback *)kzalloc(sizeof(TC_NS_Callback), GFP_KERNEL);
    if(!new_callback){
        TCERR("kmalloc failed \n");
        ret = -ENOMEM;
        goto find_callback;
    }
    memcpy(new_callback->uuid, uuid, 16);
    ta_callback_func_list.callback_count++;
    TCDEBUG("ta_callback_func_list.callback_count is %d\n", ta_callback_func_list.callback_count);
    INIT_LIST_HEAD(&new_callback->head);
    new_callback->callback_func = (void (*)(void *))func;
    mutex_init(&new_callback->callback_lock);
    list_add_tail(&new_callback->head, &ta_callback_func_list.callback_list);

find_callback:
    mutex_unlock(&ta_callback_func_list.callback_list_lock);
    return ret;
}

static int TC_NS_register_notify_data_memery(void)
{

    TC_NS_SMC_CMD smc_cmd = {0};
    int ret;
    unsigned char uuid[17] = {0};
    TC_NS_Operation operation = {0};

    operation.paramTypes = TEE_PARAM_TYPE_VALUE_INPUT;
    operation.paramTypes = operation.paramTypes << 12;
    operation.params[0].value.a= virt_to_phys(notify_data);
    operation.params[0].value.b = 4096;

    uuid[0] = 1;
    smc_cmd.uuid_phys = virt_to_phys((void*)uuid);
    smc_cmd.cmd_id = GLOBAL_CMD_ID_REGISTER_NOTIFY_MEMORY;
    smc_cmd.operation_phys = virt_to_phys(&operation);

    TCDEBUG("cmd. context_phys:%x\n",smc_cmd.context_id);
    ret = TC_NS_SMC(&smc_cmd, 0);

    return ret;
}

static int TC_NS_unregister_notify_data_memory(void)
{

    TC_NS_SMC_CMD smc_cmd = {0};
    int ret;
    unsigned char uuid[17] = {0};
    TC_NS_Operation operation = {0};

    operation.paramTypes = TEE_PARAM_TYPE_VALUE_INPUT;
    operation.paramTypes = operation.paramTypes << 12;
    operation.params[0].value.a= virt_to_phys(notify_data);
    operation.params[0].value.b = 4096;

    uuid[0] = 1;
    smc_cmd.uuid_phys = virt_to_phys((void*)uuid);
    smc_cmd.cmd_id = GLOBAL_CMD_ID_UNREGISTER_NOTIFY_MEMORY;
    smc_cmd.operation_phys = virt_to_phys(&operation);
    TCDEBUG("cmd. context_phys:%x\n",smc_cmd.context_id);

    ret = TC_NS_SMC(&smc_cmd, 0);

    return ret;
}
#endif

static int TC_NS_load_image_operation(TC_NS_ClientContext *client_context,
        TC_NS_Operation *operation, TC_NS_DEV_File *dev_file)
{
    int index = 0;
    int ret = 1;
    TC_NS_Shared_MEM *shared_mem = NULL;
    TC_NS_ClientParam *client_param = NULL;
    unsigned int param_type;
    unsigned int trans_paramtype_to_tee[4];

        client_param = &(client_context->params[index]);
        param_type = TEEC_PARAM_TYPE_GET(client_context->paramTypes, index);
        operation->params[index].memref.buffer = 0;

        /* TCDEBUG("--->param type is %d\n", param_type); */
	if(param_type != TEEC_MEMREF_PARTIAL_INOUT){
	    TCERR("not valid param_type for load app\n");
	    ret = -1;
	    return ret;
	}else{
	    if(copy_from_user(&operation->params[index].memref.size,
			(void *)client_param->memref.size_addr, sizeof(unsigned int))) {
		TCERR("allocate buffer client_param->memref.size_addr copy from user failed\n");
		ret = -1;
		return ret;
	    }

	    list_for_each_entry(shared_mem, &dev_file->shared_mem_list, head) {
		if (shared_mem->user_addr == (void *)client_param->memref.buffer) {
		    if(shared_mem->len >= operation->params[index].memref.size){
			operation->params[index].memref.buffer =
			    virt_to_phys((void *)shared_mem->kernel_addr + client_param->memref.offset);
		    }
		    /* TCDEBUG("---:memref buff: 0x%x\n", operation->params[index].memref.buffer); */
		    break;
		}
	    }
	    if (!operation->params[index].memref.buffer) {
		TCERR("can not find shared buffer, exit\n");
		ret = -1;
		return ret;
	    }
	}

        if((param_type == TEEC_MEMREF_TEMP_INPUT) ||
            (param_type == TEEC_MEMREF_TEMP_OUTPUT)||
            (param_type  == TEEC_MEMREF_TEMP_INOUT)){
            trans_paramtype_to_tee[index] = param_type; //TEEC_MEMREF_TEMP_INPUT equal to TEE_PARAM_TYPE_MEMREF_INPUT
        } else if((param_type == TEEC_MEMREF_PARTIAL_INPUT)||
            (param_type == TEEC_MEMREF_PARTIAL_OUTPUT)||
            (param_type == TEEC_MEMREF_PARTIAL_INOUT)){
            trans_paramtype_to_tee[index] = param_type - 8; //TEEC_MEMREF_PARTIAL_INPUT - TEE_PARAM_TYPE_MEMREF_INPUT = 8
        } else if((param_type == TEEC_VALUE_INPUT)||
            (param_type == TEEC_VALUE_OUTPUT)||
            (param_type == TEEC_VALUE_INOUT)){
            trans_paramtype_to_tee[index] = param_type; //TEEC_VALUE_INPUT equal to TEE_PARAM_TYPE_VALUE_INPUT
        } else{
            TCDEBUG("param_type = TEEC_NONE\n");
            trans_paramtype_to_tee[index] = TEE_PARAM_TYPE_NONE;
        }

    operation->paramTypes = TEEC_PARAM_TYPES(
        trans_paramtype_to_tee[0],
        TEE_PARAM_TYPE_NONE,
        TEE_PARAM_TYPE_NONE,
        TEE_PARAM_TYPE_NONE);

    return ret;
}

static int TC_NS_load_image(TC_NS_DEV_File *dev_file, void* argp, unsigned cmd)
{
    int ret;
    TC_NS_SMC_CMD *smc_cmd = NULL;
    TC_NS_Operation *operation = NULL;
    TC_NS_ClientContext client_context;
    int load_flag;
    unsigned char uuid[17] = {0};

    if (!dev_file) {
        TCERR("dev file id erro\n");
        return IMG_LOAD_FIND_NO_DEV_ID;
    }
    if(!argp){
	TCERR("argp is NULL input buffer\n");
	return -EINVAL;
    }

    if(copy_from_user(&client_context, argp, sizeof(TC_NS_ClientContext))){
        TCERR("copy from user failed\n");
        ret =  -ENOMEM;
        return ret;
    }

    smc_cmd = (TC_NS_SMC_CMD *)kzalloc(sizeof(TC_NS_SMC_CMD), GFP_KERNEL);
    if(!smc_cmd){
        TCERR("smc_cmd malloc failed");
        ret = -ENOMEM;
        return ret;
    }

    /* load image operation */
    operation = (TC_NS_Operation *)kzalloc(sizeof(TC_NS_Operation), GFP_KERNEL);
    if(!operation){
        TCERR("login malloc failed");
        ret = -ENOMEM;
        goto operation_erro;
    }
    if (TC_NS_CLIENT_IOCTL_NEED_LOAD_APP == cmd) {
        client_context.cmd_id = GLOBAL_CMD_ID_NEED_LOAD_APP;
    }
    else if (TC_NS_CLIENT_IOCTL_LOAD_APP_REQ == cmd) {
        client_context.cmd_id = GLOBAL_CMD_ID_LOAD_SECURE_APP;
    }
    else {
        TCERR("cmd is is not correct(%d)\n", client_context.cmd_id);
        ret = -EFAULT;
        goto buf_erro;
    }
    ret = TC_NS_load_image_operation(&client_context, operation, dev_file);
    if (ret < 0){
        ret = IMG_LOAD_FIND_NO_SHARE_MEM;
        goto buf_erro;
    }

    /* load image smc command */
    TCDEBUG("smc cmd id %d\n", client_context.cmd_id);
    smc_cmd->cmd_id = client_context.cmd_id;
    uuid[0] = 1;
    smc_cmd->uuid_phys = virt_to_phys((void*)uuid);
    smc_cmd->dev_file_id = dev_file->dev_file_id;
    smc_cmd->context_id = 0;
    smc_cmd->operation_phys = virt_to_phys(operation);

    TCDEBUG("secure app load smc command\n");
    ret = TC_NS_SMC(smc_cmd, 0);

    if(ret != 0){
        TCERR("smc_call returns error ret 0x%x\n",ret);
        ret = IMG_LOAD_SECURE_RET_ERROR;
    }

    /* get ret flag in share memory buffer */
    if(!(client_context.params[0].memref.buffer)){
	TCERR("it is NULL input buffer\n");
	ret = -EINVAL;
	goto buf_erro;
    }
    if(copy_from_user(&load_flag, (int*)client_context.params[0].memref.buffer, sizeof(int))){
	TCERR("copy from user failed\n");
	ret =  -ENOMEM;
	goto buf_erro;
    }

    TCDEBUG("load flag is %d, buffer %p\n", load_flag, client_context.params[0].memref.buffer);
    if (load_flag != 1) {
        /* no need to continue load, need load again, load flag will be 1 */
        TCDEBUG("no need to continue load cmd\n");
        load_app_lock_flag = 0;
    }

    /* error: */
buf_erro:
    kfree(operation);
operation_erro:
    kfree(smc_cmd);

    return ret;
}


int TC_NS_ClientOpen(TC_NS_DEV_File **dev_file, uint8_t kernel_api)
{
    int ret = TEEC_ERROR_GENERIC;
    TC_NS_DEV_File *dev;

    TCDEBUG("tc_client_open\n");
    dev = (TC_NS_DEV_File *)kzalloc(sizeof(TC_NS_DEV_File), GFP_KERNEL);
    if(!dev){
        TCERR("dev malloc failed");
        return ret;
    }
    mutex_lock(&tc_ns_dev_list.dev_lock);
    list_add_tail(&dev->head, &tc_ns_dev_list.dev_file_list);
    mutex_unlock(&tc_ns_dev_list.dev_lock);

    mutex_lock(&device_file_cnt_lock);
    tc_ns_dev_list.dev_file_cnt++;
    dev->dev_file_id = device_file_cnt;
    device_file_cnt++;
    mutex_unlock(&device_file_cnt_lock);

    dev->service_cnt = 0;
    INIT_LIST_HEAD(&dev->services_list);

    dev->shared_mem_cnt = 0;
    INIT_LIST_HEAD(&dev->shared_mem_list);

    dev->login_setup = 0;

    dev->kernel_api = kernel_api;
    dev->load_app_flag = 0;
    mutex_init(&dev->service_lock);
    mutex_init(&dev->shared_mem_lock);
    *dev_file = dev;
    ret = TEEC_SUCCESS;
    return ret;
}

int TC_NS_ClientClose(TC_NS_DEV_File *dev, int flag){
	int ret = TEEC_ERROR_GENERIC;
	TC_NS_Service *service = NULL, *service_temp;
	TC_NS_Shared_MEM *shared_mem = NULL;
	TC_NS_Shared_MEM *shared_mem_temp = NULL;

	mutex_lock(&tc_ns_dev_list.dev_lock);
	list_for_each_entry_safe(service, service_temp, &dev->services_list, head){
		if(service){
			/* close unclosed session */
			if(!list_empty(&service->session_list)){
				TC_NS_Session *session, *tmp_session;
				list_for_each_entry_safe(session, tmp_session, &service->session_list, head){
					TCDEBUG("terminate opened service 0x%x\n", *(uint32_t*)service->uuid);
                    mutex_lock(&session->ta_session_lock);
					kill_session(dev, service->uuid, session->session_id);
                    mutex_unlock(&session->ta_session_lock);
					kfree(session);
				}
			}
			list_del(&service->head);
			kfree(service);
			dev->service_cnt--;
		}
	}
	list_for_each_entry_safe(shared_mem, shared_mem_temp, &dev->shared_mem_list, head){
		if(shared_mem){
			list_del(&shared_mem->head);
			if(!flag)
			    tc_mem_free(shared_mem);
			dev->shared_mem_cnt--;
		}
	}
	if(!flag)
	    TC_NS_unregister_agent_client(dev);
	if(dev->service_cnt == 0 && list_empty(&dev->services_list)){
		ret = TEEC_SUCCESS;
		//del dev from the list
		list_del(&dev->head);
		kfree(dev);
	}
	else{
		TCERR("There are some service at the device,pls realse them first!");
	}
	TCDEBUG("dev list  dev file cnt:%d\n",tc_ns_dev_list.dev_file_cnt);
	if(tc_ns_dev_list.dev_file_cnt != 0){
		tc_ns_dev_list.dev_file_cnt--;
		TCDEBUG("dev list  dev file cnt:%d\n",tc_ns_dev_list.dev_file_cnt);
	}
	else
		TCERR("dev file list had been empty already");
	mutex_unlock(&tc_ns_dev_list.dev_lock);

	return ret;
}


void shared_vma_open(struct vm_area_struct *vma){
}

void shared_vma_close(struct vm_area_struct *vma){
	TC_NS_Shared_MEM *shared_mem, *shared_mem_temp;
	TC_NS_DEV_File *dev_file = vma->vm_private_data;
	void *user_addr = (void *)(vma->vm_start);

	mutex_lock(&tc_ns_dev_list.dev_lock);
	list_for_each_entry_safe(shared_mem, shared_mem_temp, &dev_file->shared_mem_list, head){
		if(shared_mem && shared_mem->user_addr == (void *)user_addr){
			list_del(&shared_mem->head);
			tc_mem_free(shared_mem);
			dev_file->shared_mem_cnt--;
			break;
		}
	}
	mutex_unlock(&tc_ns_dev_list.dev_lock);
}

static struct vm_operations_struct shared_remap_vm_ops = {
    .open = shared_vma_open,
    .close = shared_vma_close,
};

static int tc_client_mmap(struct file *filp, struct vm_area_struct *vma)
{
	int ret = TEEC_SUCCESS;
	TC_NS_DEV_File *dev_file = filp->private_data;
	unsigned long len = vma->vm_end - vma->vm_start;
	TC_NS_Shared_MEM *shared_mem =NULL;
	struct __smc_event_data* event_control = NULL;

	if(!dev_file){
		TCERR("can not find dev in malloc shared buffer!\n");
		return -1;
	}

	if((teecd_task == current->group_leader)&&(!TC_NS_get_uid())) {
	    if(vma->vm_pgoff == 1) {
		event_control = find_event_control(AGENT_FS_ID);
	    } else if(vma->vm_pgoff == 2) {
		event_control = find_event_control(AGENT_MISC_ID);
	    } else if(vma->vm_pgoff == 3) {
		event_control = find_event_control(AGENT_SOCKET_ID);
	    }
	    if(event_control){
		shared_mem = event_control->buffer;
	    }
	}
	if(!shared_mem)
	    shared_mem = tc_mem_allocate(dev_file, len);
	if (IS_ERR(shared_mem)) {
		return -1;
	}

	if (remap_pfn_range(vma, vma->vm_start, 
			    virt_to_phys(shared_mem->kernel_addr) >> PAGE_SHIFT,
			    len, vma->vm_page_prot)) {
		TCERR("can not remap_pfn_range!\n");
		if(event_control)
		    return -1;
		else{
		    tc_mem_free(shared_mem);
		    return -1;
		}
	}


	shared_mem->user_addr = (void*)vma->vm_start;

	mutex_lock(&tc_ns_dev_list.dev_lock);
	dev_file->shared_mem_cnt++;
	vma->vm_private_data = (void *)dev_file;
	list_add_tail(&shared_mem->head, &dev_file->shared_mem_list);
	mutex_unlock(&tc_ns_dev_list.dev_lock);

	return ret;
}


static long tc_client_session_ioctl(struct file *file, unsigned cmd,
			    unsigned long arg)
{
	int ret = TEEC_ERROR_GENERIC;
	void *argp = (void __user *) arg;
	TC_NS_DEV_File *dev_file = file->private_data;
	TC_NS_ClientContext context;
	if(!argp){
	    TCERR("argp is NULL input buffer\n");
	    ret = -EINVAL;
	    return ret;
	}
	if(copy_from_user(&context, argp, sizeof(TC_NS_ClientContext))) {
	    TCERR("copy from user failed\n");
	    return -EFAULT;
	}

	switch(cmd){
	case TC_NS_CLIENT_IOCTL_SES_OPEN_REQ:{
		ret = TC_NS_OpenSession(dev_file, &context);

		if(copy_to_user(argp, &context, sizeof(context))) {
			ret = -EFAULT;
			/* Need to close session? or wait for fd close ?*/
		}
		break;
	}
	case TC_NS_CLIENT_IOCTL_SES_CLOSE_REQ:{
		ret = TC_NS_CloseSession(dev_file, &context);
		break;
	}
	case TC_NS_CLIENT_IOCTL_SEND_CMD_REQ:{
		ret = TC_NS_Send_CMD(dev_file, &context);

		if(copy_to_user(argp, &context, sizeof(context))) {
			ret =  -EFAULT;
		}
		break;
	}
	default:
		TCERR("invalid cmd!");
		return ret;
	}
	return ret;
}

static long tc_agent_ioctl(struct file *file, unsigned cmd,
			    unsigned long arg)
{

	int ret = TEEC_ERROR_GENERIC;
	TC_NS_DEV_File *dev_file = file->private_data;

	switch(cmd){
	case TC_NS_CLIENT_IOCTL_WAIT_EVENT:{
		ret = TC_NS_wait_event((unsigned int)arg);
		break;
	}
	case TC_NS_CLIENT_IOCTL_SEND_EVENT_REPONSE:{
		ret = TC_NS_send_event_reponse((unsigned int)arg);
		break;
	}
	case TC_NS_CLIENT_IOCTL_REGISTER_AGENT:{
		TC_NS_Shared_MEM* shared_mem=NULL, *tmp_mem=NULL;
		//find sharedmem
		mutex_lock(&tc_ns_dev_list.dev_lock);
		list_for_each_entry(tmp_mem, &dev_file->shared_mem_list, head){
			if(tmp_mem){
				shared_mem = tmp_mem;
				break;
			}
		}
		mutex_unlock(&tc_ns_dev_list.dev_lock);
		ret = TC_NS_register_agent(dev_file, (unsigned int)arg, shared_mem);
		break;
	}
	case TC_NS_CLIENT_IOCTL_UNREGISTER_AGENT:{
		ret = TC_NS_unregister_agent((unsigned int)arg);
		break;
	}
        case TC_NS_CLIENT_IOCTL_SYC_SYS_TIME:{
            ret = TC_NS_sync_sys_time((TC_NS_Time *)arg);
            break;
        }
	default:
		TCERR("invalid cmd!");
		return ret;
	}

	TCDEBUG("TC_NS_ClientIoctl ret = 0x%x\n", ret);
	return ret;
}

#if defined (CONFIG_TEE_TUI)
static int TC_NS_tui_event(TC_NS_DEV_File *dev_file, void* argp)
{
    int ret = 0;
    TEEC_TUI_Parameter tui_param;

    if (!dev_file) {
        TCERR("dev file id erro\n");
        return IMG_LOAD_FIND_NO_DEV_ID;
    }

    if(!argp){
	TCERR("argp is NULL input buffer\n");
	ret = -EINVAL;
	return ret;
    }
    if(copy_from_user(&tui_param, argp, sizeof(TEEC_TUI_Parameter))){
        TCERR("copy from user failed\n");
        ret =  -ENOMEM;
        return ret;
    }

    if(tui_param.event_type <= TUI_POLL_MAX){
        ret = tui_send_event(tui_param.event_type);
    }else{
        //todo: use to get keyCode
	TCDEBUG("now poll keyCode-------------\n");
	tui_param.value =  tui_get_keyCode();
	if(copy_to_user(argp, &tui_param, sizeof(TEEC_TUI_Parameter))){
		ret = -ENOMEM;
		TCERR("copy to user failed\n");
	}
    }

    return ret;
}
#endif

static long tc_client_ioctl(struct file *file, unsigned cmd,
			    unsigned long arg)
{

	int ret = TEEC_ERROR_GENERIC;
	void *argp = (void __user *) arg;
	TC_NS_DEV_File *dev_file = file->private_data;
	TC_NS_ClientContext client_context = {0};

	switch(cmd){
	/* IOCTLs for the CAs */
	case TC_NS_CLIENT_IOCTL_SES_OPEN_REQ:
	case TC_NS_CLIENT_IOCTL_SES_CLOSE_REQ:
	case TC_NS_CLIENT_IOCTL_SEND_CMD_REQ:
		ret = tc_client_session_ioctl(file, cmd, arg);
		break;
#if 1
	case TC_NS_CLIENT_IOCTL_SHRD_MEM_RELEASE:{
		ret = TC_NS_SharedMemoryRelease(dev_file, (void *)arg);
		break;
	}
#endif

	case TC_NS_CLIENT_IOCTL_NEED_LOAD_APP:{
		mutex_lock(&load_app_lock);
		load_app_lock_flag = 1;
		ret = TC_NS_load_image(dev_file, argp, cmd);
		if (ret != 0)
			load_app_lock_flag = 0;
                mutex_lock(&dev_file->service_lock);
                dev_file->load_app_flag = load_app_lock_flag;
                mutex_unlock(&dev_file->service_lock);

		if (load_app_lock_flag == 0) {
			/* if no need to load app, or if ret fail, mutex unlock */
			mutex_unlock(&load_app_lock);
		}
		break;
	}
	case TC_NS_CLIENT_IOCTL_LOAD_APP_REQ:{
		ret = TC_NS_load_image(dev_file, argp, cmd);
		if (ret != 0)
			load_app_lock_flag = 0;

		if (load_app_lock_flag == 0) {
			/* if load app complete, mutex unlock */
                    mutex_lock(&dev_file->service_lock);
                    dev_file->load_app_flag = load_app_lock_flag;
                    mutex_unlock(&dev_file->service_lock);
                    mutex_unlock(&load_app_lock);
		}
		break;
	}
	case TC_NS_CLIENT_IOCTL_LOAD_APP_EXCEPT:{
		ret = TEEC_SUCCESS;
		load_app_lock_flag = 0;
		mutex_unlock(&load_app_lock);
		break;
	}
	case TC_NS_CLIENT_IOCTL_ALLOC_EXCEPTING_MEM:
	    //ret = TC_NS_alloc_exception_mem();
		break;
	case TC_NS_CLIENT_IOCTL_CANCEL_CMD_REQ:
		TCDEBUG("come into cancel cmd\n");
		if(!argp){
		    TCERR("argp is NULL input buffer\n");
		    ret = -EINVAL;
		    return ret;
		}
		if(copy_from_user(&client_context, argp, sizeof(TC_NS_ClientContext))){
		    TCERR("copy from user failed\n");
		    ret =  -ENOMEM;
		    return ret;
		}
		ret = TC_NS_Send_CMD(dev_file, &client_context);
		TCDEBUG("cancel cmd end\n");
		break;
	/* This is the login information and is set teecd when client opens a
	 * new session */
	case TC_NS_CLIENT_IOCTL_LOGIN: {
		ret = TC_NS_Client_Login(dev_file, argp);
		break;
	}
	/* IOCTLs for the secure storage daemon */
        case TC_NS_CLIENT_IOCTL_WAIT_EVENT:
        case TC_NS_CLIENT_IOCTL_SEND_EVENT_REPONSE:
        case TC_NS_CLIENT_IOCTL_REGISTER_AGENT:
        case TC_NS_CLIENT_IOCTL_UNREGISTER_AGENT:
        case TC_NS_CLIENT_IOCTL_SYC_SYS_TIME:
		ret = tc_agent_ioctl(file, cmd, arg);
		break;
	case TC_NS_CLIENT_IOCTL_TST_CMD_REQ:{
		TCDEBUG("come into tst cmd\n");
		ret = TC_NS_TST_CMD(dev_file, argp);
		break;
	}
#if defined (CONFIG_TEE_TUI)
       /* for tui service inform TUI TA  event type*/
        case TC_NS_CLIENT_IOCTL_TUI_EVENT:{
             TCDEBUG("come into tui cmd\n");
             ret = TC_NS_tui_event(dev_file, argp);
             break;
        }
#endif
	default:
		TCERR("invalid cmd!");
		return ret;
	}

	TCDEBUG("TC_NS_ClientIoctl ret = 0x%x\n", ret);
	return ret;
}

static int tc_client_open(struct inode *inode, struct file *file)
{
	int ret = TEEC_ERROR_GENERIC;
	TC_NS_DEV_File *dev = NULL;

	if(!teecd_task){
	    teecd_task = current->group_leader;
	    agent_count = 2;//currently we have 2 agents need to care for.
	}
	file->private_data = NULL;
	ret = TC_NS_ClientOpen(&dev, TEE_REQ_FROM_USER_MODE);
	if (ret == TEEC_SUCCESS)
		file->private_data = dev;
	return ret;
}

static int tc_client_close(struct inode *inode, struct file *file)
{
	int ret = TEEC_ERROR_GENERIC;
	TC_NS_DEV_File *dev = file->private_data;

        mutex_lock(&dev->service_lock);
        if (dev->load_app_flag) {
                TCERR("=====load_app_lock_flag is %d\n", load_app_lock_flag);
                dev->load_app_flag = 0;
		load_app_lock_flag = 0;
		mutex_unlock(&load_app_lock);
        }
        mutex_unlock(&dev->service_lock);
	/* release tui resource */
#if defined (CONFIG_TEE_TUI)
	if (dev->dev_file_id == tui_attach_device())
		send_tui_msg_adapt(TUI_POLL_CANCEL, 0, NULL);
#endif
	if((teecd_task == current->group_leader)&&(!TC_NS_get_uid())) {
	    TCERR("teecd is killed, something bad must be happened!!!\n");
	    TC_NS_send_event_reponse_all();
	    ret = TC_NS_ClientClose(dev, 1);
	    if(--agent_count == 0)
		teecd_task = NULL;
	} else {
	    ret = TC_NS_ClientClose(dev, 0);
	}
	file->private_data = NULL;
	return ret;
}

#ifdef CONFIG_COMPAT
long tc_compat_client_ioctl(struct file *flie, unsigned int cmd,
			   unsigned long arg)
{
    long ret = -ENOIOCTLCMD;
    arg = (unsigned long) compat_ptr(arg);
    ret = tc_client_ioctl(flie, cmd, arg);
    return ret;
}
#endif


static const struct file_operations TC_NS_ClientFops = {
        .owner = THIS_MODULE,
        .open = tc_client_open,
        .release = tc_client_close,
        .unlocked_ioctl = tc_client_ioctl,
        .mmap = tc_client_mmap,
#ifdef CONFIG_COMPAT
        .compat_ioctl = tc_compat_client_ioctl,
#endif
};

static __init int tc_init(void)
{
	struct device *class_dev;
	int ret = 0;
	unsigned int irq;

	TCDEBUG("tc_ns_client_init");
	np = of_find_compatible_node(NULL, NULL, "trusted_core");
	if (!np) {
		TCERR("No trusted_core compatible node found.\n");
		return -ENODEV;
	}
	ret = alloc_chrdev_region(&tc_ns_client_devt, 0, 1, TC_NS_CLIENT_DEV);
	if (ret < 0) {
		TCERR("alloc_chrdev_region failed %d", ret);
		return -EFAULT;
	}

	driver_class = class_create(THIS_MODULE, TC_NS_CLIENT_DEV);
	if (IS_ERR(driver_class)) {
		ret = -ENOMEM;
		TCERR("class_create failed %d", ret);
		goto unregister_chrdev_region;
	}

	class_dev = device_create(driver_class, NULL, tc_ns_client_devt, NULL,
				  TC_NS_CLIENT_DEV);
	if (!class_dev) {
		TCERR("class_device_create failed");
		ret = -ENOMEM;
		goto class_destroy;
	}
	class_dev->of_node = np;

	cdev_init(&tc_ns_client_cdev, &TC_NS_ClientFops);
	tc_ns_client_cdev.owner = THIS_MODULE;

	ret = cdev_add(&tc_ns_client_cdev,
		       MKDEV(MAJOR(tc_ns_client_devt), 0), 1);
	if (ret < 0) {
		TCERR("cdev_add failed %d", ret);
		goto class_device_destroy;
	}
#ifdef TC_ASYNC_NOTIFY_SUPPORT
	TCDEBUG("register secure notify handler\n");
	/* Map IRQ 0 from the OF interrupts list */
	irq = irq_of_parse_and_map(np, 0);
	ret = devm_request_irq(class_dev, irq, tc_secure_notify,
			       0, TC_NS_CLIENT_DEV, NULL);
	if(ret < 0) {
		TCERR("device irq %u request failed %u", irq, ret);
		goto class_device_destroy;
	}
#endif
	memset(&tc_ns_dev_list, 0, sizeof(tc_ns_dev_list));
	tc_ns_dev_list.dev_file_cnt = 0;
	INIT_LIST_HEAD(&tc_ns_dev_list.dev_file_list);
	mutex_init(&tc_ns_dev_list.dev_lock);

	memset(&ta_callback_func_list, 0, sizeof(ta_callback_func_list));
	ta_callback_func_list.callback_count = 0;
	INIT_LIST_HEAD(&ta_callback_func_list.callback_list);
	mutex_init(&ta_callback_func_list.callback_list_lock);
	ret = smc_init_data(class_dev);
	if (ret < 0)
		goto class_device_destroy;

	ret = agent_init();
	if (ret < 0)
		goto smc_data_free;

	if (tc_mem_init())
		goto smc_data_free;

	ret = TC_NS_register_rdr_mem();
	if (ret) {
	    TCERR("TC_NS_register_rdr_mem failed %x\n", ret);
	}
	ret = teeos_register_exception(); //0:error
	if (ret == 0)
		TCERR("teeos_register_exception to rdr failed\n");
	else
		ret = 0;

#ifdef TC_ASYNC_NOTIFY_SUPPORT
	mutex_lock(&notify_data_lock);
	if(!notify_data){
		notify_data = (void* )__get_free_page(GFP_KERNEL | __GFP_ZERO);
		if(!notify_data){
			TCERR("__get_free_page failed for notification data\n");
			ret = -ENOMEM;
			mutex_unlock(&notify_data_lock);
			goto smc_data_free;
		}
		memset(notify_data, 0, 4096);
		ret=TC_NS_register_notify_data_memery();
		if(ret != TEEC_SUCCESS) {
			TCERR("Shared memory registration for secure world notification failed ret is 0x%x\n", ret);
			ret = -1;
			mutex_unlock(&notify_data_lock);
			goto free_notify_mem;
		}
	}
	mutex_unlock(&notify_data_lock);
	notify_data_entry_timer = acquire_notify_data_entry(NOTIFY_DATA_ENTRY_TIMER);
#endif
	if (of_get_property(np, "tui-enable", NULL)) {
		ret = init_tui();
		if (ret) {
			TCERR("init_tui failed 0x%x\n", ret);
			goto free_shared_mem;
		}else{
			notify_data_entry_tp = acquire_notify_data_entry(NOTIFY_DATA_ENTRY_TP);
			TCDEBUG("NOTIFY MEM: notify_data=0x%x , notify_data_entry_timer=0x%x, notify_data_entry_tp=0x%x-------\n",
			(int)virt_to_phys(notify_data), (int)virt_to_phys(notify_data_entry_timer), (int)virt_to_phys(notify_data_entry_tp));
		}
	}

	return 0;
	/* if error happens */
free_notify_mem:
	free_page((unsigned long)notify_data);
	notify_data = NULL;
free_shared_mem:
	tc_mem_destroy();
smc_data_free:
	smc_free_data();
class_device_destroy:
	device_destroy(driver_class, tc_ns_client_devt);
class_destroy:
	class_destroy(driver_class);
unregister_chrdev_region:
	unregister_chrdev_region(tc_ns_client_devt, 1);

	return ret;
}

static void tc_exit(void)
{
	TCDEBUG("otz_client exit");
#ifdef TC_ASYNC_NOTIFY_SUPPORT
	if(notify_data)
		TC_NS_unregister_notify_data_memory();
#endif
	if (of_get_property(np, "tui-enable", NULL)) {
            tui_exit();
        }
	device_destroy(driver_class, tc_ns_client_devt);
	class_destroy(driver_class);
	unregister_chrdev_region(tc_ns_client_devt, 1);
	smc_free_data();

    agent_exit();
	tc_mem_destroy();
}

EXPORT_SYMBOL(TC_NS_RegisterServiceCallbackFunc);
MODULE_AUTHOR("q00209673");
MODULE_DESCRIPTION("TrustCore ns-client driver");
MODULE_VERSION("1.10");
fs_initcall_sync(tc_init);
module_exit(tc_exit);
