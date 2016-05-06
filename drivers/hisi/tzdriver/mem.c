/*******************************************************************************
 * All rights reserved, Copyright (C) huawei LIMITED 2012
 *
 * This source code has been made available to you by HUAWEI on an
 * AS-IS basis. Anyone receiving this source code is licensed under HUAWEI
 * copyrights to use it in any way he or she deems fit, including copying it,
 * modifying it, compiling it, and redistributing it either with or without
 * modifications. Any person who transfers this source code or any derivative
 * work must include the HUAWEI copyright notice and this paragraph in
 * the transferred software.
*******************************************************************************/
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/freezer.h>
#include <linux/module.h>

#include "smc.h"
#include "tee_client_constants.h"
#include "tc_ns_client.h"
#include "teek_ns_client.h"
#include "agent.h"

#define ROUND_UP(N, S) ((((N) + (S) - 1) / (S)) * (S))

static DEFINE_MUTEX(shared_buf_rel_lock);

static DEFINE_MUTEX(prealloc_lock);
/************global reference end*************/
static void *g_mem_pre_allocated = NULL;
#define PRE_ALLOCATE_SIZE (1024*1024)

int tc_mem_free(TC_NS_Shared_MEM *shared_mem)
{
	if(shared_mem->kernel_addr &&
	   (shared_mem->kernel_addr != g_mem_pre_allocated)) {
		free_pages((unsigned long)shared_mem->kernel_addr,
			   get_order(ROUND_UP(shared_mem->len, SZ_4K)));
	}
	if(shared_mem->kernel_addr == g_mem_pre_allocated){
		mutex_unlock(&prealloc_lock);
	}
	kfree(shared_mem);
	return 0;
}

TC_NS_Shared_MEM *tc_mem_allocate(TC_NS_DEV_File *dev, size_t len)
{
	TC_NS_Shared_MEM *shared_mem;
	void *addr;

	if(!dev){
		TCERR("can not find dev in malloc shared buffer!\n");
		return ERR_PTR(-EFAULT);
	}

	shared_mem = (TC_NS_Shared_MEM *)kmalloc(sizeof(TC_NS_Shared_MEM), GFP_KERNEL);
	if (!shared_mem) {
		TCERR("shared_mem kmalloc failed\n");
		return ERR_PTR(-ENOMEM);
	}

	addr =  (void *) __get_free_pages(GFP_KERNEL, get_order(ROUND_UP(len, SZ_4K)));
	if(!addr) {
		TCERR("get free pages failed\n");
		if(mutex_trylock(&prealloc_lock)) {
			if(g_mem_pre_allocated && (len <= PRE_ALLOCATE_SIZE)) {
				TCDEBUG("use pre allocted mem to work\n");
				memset(g_mem_pre_allocated, 0, PRE_ALLOCATE_SIZE);
				addr = g_mem_pre_allocated;
			/* In case we could not use the preallocated memory
			 * unlock the mutex */
			} else
				mutex_unlock(&prealloc_lock);
		}
		/* If we couldn't use the preallocated memory then return */
		if(!addr) {
			TCERR("g_mem_pre_allocated is null or size is too large\n");
			kfree(shared_mem);
			return ERR_PTR(-ENOMEM);
		}
	}else{
	    memset(addr, 0, ROUND_UP(len, SZ_4K));
	}

	shared_mem->kernel_addr = addr;
	shared_mem->len = len;

	return shared_mem;
}

int tc_mem_init(void)
{
	TCDEBUG("tc_mem_init\n");
	/* pre-allocated memory for large use */
	g_mem_pre_allocated = (void*) __get_free_pages(GFP_KERNEL,
				get_order(ROUND_UP(PRE_ALLOCATE_SIZE, SZ_4K)));
	if(!g_mem_pre_allocated)
		TCERR("g_mem_pre_allocated failed\n");

	return 0;
}

void tc_mem_destroy(void)
{
	TCDEBUG("otz_client exit\n");
	mutex_lock(&prealloc_lock);
	if(g_mem_pre_allocated)
		free_pages((unsigned long)g_mem_pre_allocated,
			   get_order(ROUND_UP(PRE_ALLOCATE_SIZE, SZ_4K)));
	mutex_unlock(&prealloc_lock);
}

