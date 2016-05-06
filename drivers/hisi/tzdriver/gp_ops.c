#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/vmalloc.h>

#include "smc.h"
#include "tee_client_constants.h"
#include "tc_ns_client.h"
#include "teek_ns_client.h"
#include "agent.h"

#define MAX_SHARED_SIZE 0x100000 /* 1 MiB */

#ifdef CONFIG_TEELOG
#define TZLOGCAT
#ifdef TZLOGCAT
extern void tz_log_write(void);
extern int tlogger_store_lastmsg(void);
#endif
#endif

#define TEEC_PARAM_TYPES( param0Type, param1Type, param2Type, param3Type) \
    ((param3Type) << 12 | (param2Type) << 8 | (param1Type) << 4 | (param0Type))

#define TEEC_PARAM_TYPE_GET( paramTypes, index) \
    (((paramTypes) >> (4*(index))) & 0x0F)
#define ROUND_UP(N, S) ((((N) + (S) - 1) / (S)) * (S))
int tc_user_param_valid(TC_NS_ClientContext *client_context, int n)
{
	TC_NS_ClientParam *client_param;
	unsigned int param_type;
	client_param = &(client_context->params[n]);

	param_type = TEEC_PARAM_TYPE_GET(client_context->paramTypes, n);
	TCDEBUG("Param %u type is %x\n", n, param_type);
	/* temp buffers we need to allocate/deallocate for every
	* operation */
	if ((param_type == TEEC_MEMREF_TEMP_INPUT) ||
		(param_type == TEEC_MEMREF_TEMP_OUTPUT) ||
		(param_type  == TEEC_MEMREF_TEMP_INOUT) ||
		(param_type == TEEC_MEMREF_PARTIAL_INPUT) ||
		(param_type == TEEC_MEMREF_PARTIAL_OUTPUT) ||
		(param_type == TEEC_MEMREF_PARTIAL_INOUT)) {
		uint32_t size;
		/* Check the size and buffer addresses have valid userspace addresses */
		if (!access_ok(VERIFY_READ, client_param->memref.size_addr, sizeof(uint32_t)))
			return -EFAULT;

		get_user(size, (uint32_t *)client_param->memref.size_addr);
		/* Check if the buffer address is valid user space address */
		if (!access_ok(VERIFY_READ, client_param->memref.buffer, size))
			return -EFAULT;
	}
	/* value */
	else if((param_type == TEEC_VALUE_INPUT)||
		(param_type == TEEC_VALUE_OUTPUT)||
		(param_type == TEEC_VALUE_INOUT)){
	if (!access_ok(VERIFY_READ, client_param->value.a_addr, sizeof(uint32_t)))
		return -EFAULT;
	if (!access_ok(VERIFY_READ, client_param->value.b_addr, sizeof(uint32_t)))
		return -EFAULT;
	}
	return 0;
}

/* These 2 functions handle copying from client. Because client here can be
 * kernel client or user space client, we must use the proper copy function */
static inline int copy_from_client(void *dest, void __user *src, size_t size, uint8_t kernel_api)
{
	int ret = 0;
	if(!src){
	    TCERR("src is NULL input buffer\n");
	    return -EINVAL;
	}
	/* Source is kernel valid address */
	if (kernel_api && (virt_addr_valid(src) || vmalloc_addr_valid(src))) {
	    memcpy(dest, src, size);
	}
	/* buffer is in user space(CA call TEE API) */
	else {
	    if(copy_from_user(dest, src, size)) {
		ret = -EFAULT;
	    }
	}
	return ret;
}

static inline int copy_to_client(void __user *dest, void *src, size_t size, uint8_t kernel_api)
{
	int ret = 0;
	/* Source is kernel valid address */
	if (kernel_api && virt_addr_valid(dest)) {
	    memcpy(dest, src, size);
	}
	/* buffer is in user space(CA call TEE API) */
	else {
	    if(copy_to_user(dest, src, size)) {
		ret = -EFAULT;
	    }
	}
	return ret;
}

static TC_NS_Operation *alloc_operation(TC_NS_DEV_File *dev_file,
					TC_NS_ClientContext *client_context,
					TC_NS_Temp_Buf local_temp_buffer[4],
					uint8_t flags)
{
	TC_NS_Operation *operation;
	TC_NS_ClientParam *client_param;
	TC_NS_Shared_MEM *shared_mem = NULL;
	int ret = 0;
	unsigned int param_type;
	int i;
	uint32_t buffer_size = 0;
	void *temp_buf;
	unsigned int trans_paramtype_to_tee[4];
	uint8_t kernel_params = (flags & TC_CALL_LOGIN) || dev_file->kernel_api;

	if(!client_context){
		TCERR("client_context is null");
		return ERR_PTR(-EINVAL);
	}

	if (client_context->paramTypes == 0) {
		return NULL;
	}
	operation = (TC_NS_Operation *)kzalloc(sizeof(TC_NS_Operation), GFP_KERNEL);
	if(!operation){
		TCERR("login malloc failed");
		return ERR_PTR(-ENOMEM);
	}
	TCDEBUG("Allocating param types %08X\n", client_context->paramTypes);
	/* Get the 4 params from the client context */
	for(i = 0; i < 4; i++){
		client_param = &(client_context->params[i]);

		param_type = TEEC_PARAM_TYPE_GET(client_context->paramTypes, i);
		TCDEBUG("Param %u type is %x\n", i, param_type);
		/* temp buffers we need to allocate/deallocate for every
		 * operation */
		if((param_type == TEEC_MEMREF_TEMP_INPUT) ||
		   (param_type == TEEC_MEMREF_TEMP_OUTPUT)||
		   (param_type  == TEEC_MEMREF_TEMP_INOUT)){
			/* For interface compatibility sake we assume buffer
			 * size to be 32bits */
			if (copy_from_client(&buffer_size,
				     (uint32_t __user *)client_param->memref.size_addr,
				     sizeof(uint32_t), kernel_params)) {
				TCERR("temp buffer client_param->memref.size_addr copy from user failed\n");
				ret = -EFAULT;
				break;
			}
			/* Don't allow unbounded malloc requests */
			if(buffer_size > MAX_SHARED_SIZE){
				TCERR("buffer_size %u from user is too large\n",
				    buffer_size);
				ret = -EFAULT;
				break;
			}
			temp_buf = (void *)__get_free_pages(GFP_KERNEL, get_order(ROUND_UP(buffer_size, SZ_4K)));
			/* If buffer size is zero or malloc failed */
			if(!temp_buf){
				TCERR("temp_buf malloc failed");
				ret = -ENOMEM;
				break;
			}
			else
			{
			    memset(temp_buf, 0x0, ROUND_UP(buffer_size, SZ_4K));
			}
			if(ZERO_OR_NULL_PTR(temp_buf))
				temp_buf = NULL;
			if((param_type == TEEC_MEMREF_TEMP_INPUT) ||
			   (param_type  == TEEC_MEMREF_TEMP_INOUT)){
				TCVERBOSE("client_param->memref.buffer=0x%x\n", client_param->memref.buffer);
				/* Kernel side buffer */
				if(copy_from_client(temp_buf,
					  (void *)client_param->memref.buffer,
					  buffer_size, kernel_params)) {
					TCERR("copy from user failed \n");
					ret = -EFAULT;
					break;
				}
			}
			operation->params[i].memref.buffer = virt_to_phys((void *)temp_buf);
			local_temp_buffer[i].temp_buffer = temp_buf;
			local_temp_buffer[i].size = buffer_size;
			operation->params[i].memref.size = buffer_size;
			trans_paramtype_to_tee[i] = param_type; //TEEC_MEMREF_TEMP_INPUT equal to TEE_PARAM_TYPE_MEMREF_INPUT
		}
		/* MEMREF_PARTIAL buffers are already allocated so we just need
		 * to search for the shared_mem ref */ 
		else if((param_type == TEEC_MEMREF_PARTIAL_INPUT)||
			(param_type == TEEC_MEMREF_PARTIAL_OUTPUT)||
			(param_type == TEEC_MEMREF_PARTIAL_INOUT)){
			/* For interface compatibility sake we assume buffer
			 * size to be 32bits */
			if (copy_from_client(&buffer_size,
				     (uint32_t __user *)client_param->memref.size_addr,
				     sizeof(buffer_size), kernel_params)) {
				TCERR("temp buffer client_param->memref.size_addr copy from user failed\n");
				ret = -EFAULT;
				break;
			}
			if(!buffer_size){
				TCERR("buffer_size from user is 0\n");
				ret = -ENOMEM;
				break;
			}
			operation->params[i].memref.buffer = 0;
			/* find kernel addr refered to user addr */
			list_for_each_entry(shared_mem, &dev_file->shared_mem_list, head){
				if(shared_mem->user_addr == (void *)client_param->memref.buffer){
					if(shared_mem->len >= buffer_size){
						operation->params[i].memref.buffer =
							virt_to_phys((void *)shared_mem->kernel_addr + client_param->memref.offset);
					}
					else {
						TCERR("Unexpected shared buffer size %u vs %u",
						      shared_mem->len,
						      buffer_size);
					}
					break;
				}
			}
			if(!operation->params[i].memref.buffer){
				TCERR("can not find shared buffer, exit\n");
				ret = -EINVAL;
				break;
			}
			operation->params[i].memref.size = buffer_size;
			/* TEEC_MEMREF_PARTIAL_INPUT - TEE_PARAM_TYPE_MEMREF_INPUT = 8 */
			trans_paramtype_to_tee[i] = param_type - (TEEC_MEMREF_PARTIAL_INPUT - TEE_PARAM_TYPE_MEMREF_INPUT);
		}
		/* value */
		else if((param_type == TEEC_VALUE_INPUT)||
			(param_type == TEEC_VALUE_OUTPUT)||
			(param_type == TEEC_VALUE_INOUT)){
			if (copy_from_client(&operation->params[i].value.a,
					client_param->value.a_addr,
					sizeof(operation->params[i].value.a),
					kernel_params)) {
				TCERR("client_param->value.a_addr copy from user failed\n");
				ret = -EFAULT;
				break;
			}
			if (copy_from_client(&operation->params[i].value.b,
					     client_param->value.b_addr,
					     sizeof(operation->params[i].value.b),
					     kernel_params)) {
				TCERR("client_param->value.b_addr copy from user failed\n");
				ret = -EFAULT;
				break;
			}
			/* TEEC_VALUE_INPUT equal to TEE_PARAM_TYPE_VALUE_INPUT */
			trans_paramtype_to_tee[i] = param_type;
		}
		else{
			TCDEBUG("param_type = TEEC_NONE\n");
			trans_paramtype_to_tee[i] = TEE_PARAM_TYPE_NONE;
		}
	}
	if(!ret) {
		operation->paramTypes = TEEC_PARAM_TYPES(
							 trans_paramtype_to_tee[0],
							 trans_paramtype_to_tee[1],
							 trans_paramtype_to_tee[2],
							 trans_paramtype_to_tee[3]);
		return operation;
	}
	else {
		kfree(operation);
		return ERR_PTR(ret);
	}
}

static int update_client_operation(TC_NS_DEV_File *dev_file,
			  TC_NS_ClientContext *client_context,
			  TC_NS_Operation *operation,
			  TC_NS_Temp_Buf local_temp_buffer[4],
			  bool incomplete)
{
	TC_NS_ClientParam *client_param;
	int ret = 0;
	unsigned int param_type;
	int i;
	uint32_t buffer_size = 0;

	for(i = 0; i < 4; i++){
		client_param = &(client_context->params[i]);
		param_type = TEEC_PARAM_TYPE_GET(client_context->paramTypes, i);
		if((param_type ==  TEEC_MEMREF_TEMP_OUTPUT)||
		   (param_type  == TEEC_MEMREF_TEMP_INOUT)){
			/* temp buffer */
			buffer_size = operation->params[i].memref.size;
			/* Size is updated all the time */
			if (copy_to_client((void *)client_param->memref.size_addr,
					   &buffer_size,
					   sizeof(buffer_size),
					   dev_file->kernel_api)) {
				TCERR("copy to user failed while copying tempbuf size\n");
				ret = -EFAULT;
				break;
			}

			/* Only update the buffer is the buffer size is valid in
			 * incomplete case, otherwise see next param */
			if(!incomplete && buffer_size <
			   operation->params[i].memref.size)
				continue;

			if (copy_to_client((void *)client_param->memref.buffer,
					   local_temp_buffer[i].temp_buffer,
					   operation->params[i].memref.size,
					   dev_file->kernel_api)) {
				TCERR("copy to user failed while copying tempbuf\n");
				ret = -ENOMEM;
				break;
			}

		} else if((param_type ==  TEEC_MEMREF_PARTIAL_OUTPUT)||
			  (param_type  == TEEC_MEMREF_PARTIAL_INOUT)){
			/* update size */
			buffer_size = operation->params[i].memref.size;
			if (copy_to_client((void *)client_param->memref.size_addr,
					   &buffer_size,
					   sizeof(buffer_size),
					   dev_file->kernel_api)) {
				TCERR("copy to user failed while copying buf size\n");
				ret = -EFAULT;
				break;
			}
		} else if(incomplete && ((param_type == TEEC_VALUE_OUTPUT)||
					 (param_type == TEEC_VALUE_INOUT))){
			/* value */
			if (copy_to_client(client_param->value.a_addr,
					   &operation->params[i].value.a,
					   sizeof(operation->params[i].value.a),
					   dev_file->kernel_api)) {
				TCERR("client_param->value.a_addr copy from user failed\n");
				ret = -EFAULT;
				break;
			}
			if (copy_to_client(client_param->value.b_addr,
					   &operation->params[i].value.b,
					   sizeof(operation->params[i].value.b),
					   dev_file->kernel_api)) {
				TCERR("client_param->value.b_addr copy from user failed\n");
				ret = -EFAULT;
				break;
			}
		}
	}
	return ret;
}

static int free_operation(TC_NS_ClientContext *client_context,
			  TC_NS_Operation *operation,
			  TC_NS_Temp_Buf local_temp_buffer[4])
{
	int ret = 0;
	unsigned int param_type;
	int i;
	void *temp_buf;

	if(!operation)
		return -EFAULT;

	if(!client_context)
		return -EFAULT;

	for(i = 0; i < 4; i++){
		param_type = TEEC_PARAM_TYPE_GET(client_context->paramTypes, i);
		if((param_type == TEEC_MEMREF_TEMP_INPUT)||
		   (param_type ==  TEEC_MEMREF_TEMP_OUTPUT)||
		   (param_type  == TEEC_MEMREF_TEMP_INOUT)) {
			/* free temp buffer */
			/* TODO: this is all sorts of bad */
			temp_buf = local_temp_buffer[i].temp_buffer;
			TCDEBUG("Free temp buf %p\n", temp_buf);
			if(virt_addr_valid(temp_buf) &&
			   !ZERO_OR_NULL_PTR(temp_buf))
				free_pages((unsigned long)temp_buf, get_order(ROUND_UP(local_temp_buffer[i].size, SZ_4K)));
		}
	}
	kfree(operation);
	return ret;
}

int tc_client_call(TC_NS_ClientContext *client_context, TC_NS_DEV_File *dev_file,
		   uint8_t flags)
{
	int ret;
	unsigned int tee_ret;
	TC_NS_Operation *operation = NULL;
	TC_NS_SMC_CMD *smc_cmd = NULL;
	TC_NS_Session *session=NULL;
	TC_NS_Service *service=NULL;
	struct TC_wait_data *wq=NULL;
	TC_NS_Temp_Buf local_temp_buffer[4] = {{0,0},{0,0},{0,0},{0,0}};
	unsigned char uuid[17];
	bool global = flags & TC_CALL_GLOBAL;

	if(!client_context){
		TCERR("client_context is null");
		ret = -EINVAL;
		goto error;
	}

	smc_cmd = (TC_NS_SMC_CMD *)kzalloc(sizeof(TC_NS_SMC_CMD), GFP_KERNEL);
	if(!smc_cmd){
		TCERR("smc_cmd malloc failed");
		ret = -ENOMEM;
		goto error;
	}

	TCDEBUG("Calling command %08x\n", client_context->cmd_id);

	if(client_context->paramTypes != 0){
	    operation = alloc_operation(dev_file, client_context, local_temp_buffer, flags);
		if(IS_ERR_OR_NULL(operation)){
			ret = PTR_ERR(operation);
			operation = NULL;
			TCERR("login malloc failed");
			goto error;
		}
	}

	uuid[0] = ((global == true ) ? 1 : 0);
	memcpy(uuid + 1, client_context->uuid, 16);
	smc_cmd->uuid_phys = virt_to_phys((void*)uuid);
	smc_cmd->cmd_id = client_context->cmd_id;
	smc_cmd->dev_file_id=dev_file->dev_file_id;
	smc_cmd->context_id = client_context->session_id;
	smc_cmd->err_origin = 0;
	smc_cmd->started = client_context->started;
	smc_cmd->uid = current_uid();//TC_NS_get_uid();
	TCVERBOSE("current uid is %d\n", smc_cmd->uid);
	TCVERBOSE("operation start is :%d\n",smc_cmd->started);
	if(operation) {
		smc_cmd->operation_phys = virt_to_phys(operation);
	} else
		smc_cmd->operation_phys = 0;

	smc_cmd->login_method = client_context->login.method;
	smc_cmd->login_data = client_context->login.mdata;

	/* send smc to secure world */
	tee_ret = TC_NS_SMC(smc_cmd, flags);

	client_context->session_id = smc_cmd->context_id;

	if(tee_ret != 0){
#ifdef  TC_ASYNC_NOTIFY_SUPPORT
		while(tee_ret == TEEC_PENDING){
			if(tee_ret == TEEC_PENDING){
				mutex_lock(&dev_file->service_lock);
				service = tc_find_service(&dev_file->services_list,
							  client_context->uuid);
				if (service) {
					session = tc_find_session(&service->session_list,
								  client_context->session_id);
					if (session) {
						TCVERBOSE("come into wait data\n");
						wq=&session->wait_data;
					}

				}
				mutex_unlock(&dev_file->service_lock);

				if(wq){
					TCVERBOSE("before wait event\n");
					if(wait_event_interruptible(wq->send_cmd_wq,
								    wq->send_wait_flag)) {
						ret = -ERESTARTSYS;
						TCDEBUG("wait event error\n");
						goto error;
					}
					wq->send_wait_flag = 0;
				}

				TCVERBOSE("operation start is :%d\n",smc_cmd->started);
				//TCVERBOSE("service id:0x%x ,cmd id:0x%x  session_id:0x%x\n",notify_data->service_id,cmd_id,notify_data->session_id);
				TCVERBOSE("TC_ASYNC_NOTIFY_SUPPORT before TC_NS_SMC\n");
				tee_ret = TC_NS_SMC_WITH_NO_NR(smc_cmd, flags);
			}
		}
#endif
		/* Client was interrupted, return and let it handle it's own
		 * signals first then retry */
		if (tee_ret == TEEC_CLIENT_INTR) {
			ret = -ERESTARTSYS;
			goto error;
		}
		else if(tee_ret){
			TCERR("smc_call returns error ret 0x%x\n",tee_ret);
			goto error1;
		}

		client_context->session_id = smc_cmd->context_id;
	}

	/* wake_up tee log reader */
#ifdef TZLOGCAT
	tz_log_write();
#endif

	if(operation){
		ret = update_client_operation(dev_file, client_context,
					      operation, local_temp_buffer,
					      true);
		if(ret)
			goto error;
	}

	ret = 0;
	goto error;

error1:
	if (tee_ret == TEEC_ERROR_SHORT_BUFFER) {
		/* update size */
		if(operation){
			ret = update_client_operation(dev_file, client_context,
						      operation,
						      local_temp_buffer,
						      false);
			if(ret)
				goto error;
		}
	}

	client_context->returns.code = tee_ret;
	client_context->returns.origin = smc_cmd->err_origin;
	ret = EFAULT;
error:
	if(smc_cmd)
		kfree(smc_cmd);

	if(operation){
		free_operation(client_context, operation, local_temp_buffer);
	}
	return ret;
}
