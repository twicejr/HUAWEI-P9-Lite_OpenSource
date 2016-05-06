/*
 * Copyright (c) 2011 Hisilicon Technologies Co., Ltd. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <linux/module.h>
#include <linux/string.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/mutex.h>
#include <linux/ipps.h>

struct ipps_client_data {
	struct list_head  list;
	struct ipps_client *client;
	void *data;
};

static LIST_HEAD(device_list);
static LIST_HEAD(client_list);

/*
 * device_mutex protects access to both device_list and client_list.
 * There's no real point to using multiple locks or something fancier
 * like an rwsem: we always access both lists, and we're always
 * modifying one list or the other list.  In any case this is not a
 * hot path so there's no point in trying to optimize.
 */
static DEFINE_MUTEX(device_mutex);

static struct ipps_device *__ipps_device_get_by_name(const char *name)
{
	struct ipps_device *device;

	list_for_each_entry(device, &device_list, core_list)
		if (!strncmp(name, device->name, IPPS_DEVICE_NAME_MAX))
			return device;

	return NULL;
}

static int alloc_name(char *name)
{
	unsigned long *inuse;
	char buf[IPPS_DEVICE_NAME_MAX];
	struct ipps_device *device;
	int i;

	inuse = (unsigned long *) get_zeroed_page(GFP_KERNEL);
	if (!inuse)
		return -ENOMEM;

	list_for_each_entry(device, &device_list, core_list) {
		if (!sscanf(device->name, name, &i))
			continue;
		if (i < 0 || i >= PAGE_SIZE * 8)
			continue;
		snprintf(buf, sizeof buf, name, i);
		if (!strncmp(buf, device->name, IPPS_DEVICE_NAME_MAX))
			set_bit(i, inuse);
	}

	i = find_first_zero_bit(inuse, PAGE_SIZE * 8);
	free_page((unsigned long) inuse);
	snprintf(buf, sizeof buf, name, i);

	if (__ipps_device_get_by_name(buf))
		return -ENFILE;

	strlcpy(name, buf, IPPS_DEVICE_NAME_MAX);
	return 0;
}

/**
 * ipps_alloc_device - allocate an IPPS device struct
 * @size:size of structure to allocate
 *
 * Low-level drivers should use ib_alloc_device() to allocate &struct
 * ib_device.  @size is the size of the structure to be allocated,
 * including any private data used by the low-level driver.
 * ib_dealloc_device() must be used to free structures allocated with
 * ib_alloc_device().
 */
struct ipps_device *ipps_alloc_device(size_t size)
{
	BUG_ON(size < sizeof (struct ipps_device));

	return kzalloc(size, GFP_KERNEL);
}
EXPORT_SYMBOL(ipps_alloc_device);

/**
 * ipps_dealloc_device - free an IPPS device struct
 * @device:structure to free
 *
 * Free a structure allocated with ipps_alloc_device().
 */
void ipps_dealloc_device(struct ipps_device *device)
{
	if (device->reg_state == IPPS_DEV_UNINITIALIZED) {
		kfree(device);
		return;
	}

	BUG_ON(device->reg_state != IPPS_DEV_UNREGISTERED);
}
EXPORT_SYMBOL(ipps_dealloc_device);


static int add_client_context(struct ipps_device *device, struct ipps_client *client)
{
	struct ipps_client_data *context;
	unsigned long flags;

	context = kmalloc(sizeof *context, GFP_KERNEL);
	if (!context) {
		printk(KERN_WARNING "Couldn't allocate client context for %s/%s\n",
		       device->name, client->name);
		return -ENOMEM;
	}

	context->client = client;
	context->data   = NULL;

	spin_lock_irqsave(&device->client_data_lock, flags);
	list_add(&context->list, &device->client_data_list);
	spin_unlock_irqrestore(&device->client_data_lock, flags);

	return 0;
}

/**
 * ipps_register_device - Register an IPPS device with IPPS core
 * @device:Device to register
 *
 * Low-level drivers use ipps_register_device() to register their
 * devices with the IPPS core.  All registered clients will receive a
 * callback for each device that is added. @device must be allocated
 * with ipps_alloc_device().
 */
int ipps_register_device(struct ipps_device *device)
{
	int ret = 0;

	mutex_lock(&device_mutex);

	if (strchr(device->name, '%')) {
		ret = alloc_name(device->name);
		if (ret)
			goto out;
	}

	INIT_LIST_HEAD(&device->client_data_list);
	spin_lock_init(&device->client_data_lock);

	list_add_tail(&device->core_list, &device_list);

	device->reg_state = IPPS_DEV_REGISTERED;

	{
		struct ipps_client *client;

		list_for_each_entry(client, &client_list, list)
			if (client->add && !add_client_context(device, client))
				client->add(device);
	}

 out:
	mutex_unlock(&device_mutex);
	return ret;
}
EXPORT_SYMBOL(ipps_register_device);

/**
 * ipps_unregister_device - Unregister an IPPS device
 * @device:Device to unregister
 *
 * Unregister an IPPS device.  All clients will receive a remove callback.
 */
void ipps_unregister_device(struct ipps_device *device)
{
	struct ipps_client *client;
	struct ipps_client_data *context, *tmp;
	unsigned long flags;

	mutex_lock(&device_mutex);

	list_for_each_entry_reverse(client, &client_list, list)
		if (client->remove)
			client->remove(device);

	list_del(&device->core_list);

	mutex_unlock(&device_mutex);

	spin_lock_irqsave(&device->client_data_lock, flags);
	list_for_each_entry_safe(context, tmp, &device->client_data_list, list)
		kfree(context);
	spin_unlock_irqrestore(&device->client_data_lock, flags);

	device->reg_state = IPPS_DEV_UNREGISTERED;
}
EXPORT_SYMBOL(ipps_unregister_device);

/**
 * ipps_register_client - Register an IPPS client
 * @client:Client to register
 *
 * Upper level users of the IPPS drivers can use ipps_register_client() to
 * register callbacks for IPPS device addition and removal.  When an IPPS
 * device is added, each registered client's add method will be called
 * (in the order the clients were registered), and when a device is
 * removed, each client's remove method will be called (in the reverse
 * order that clients were registered).  In addition, when
 * ipps_register_client() is called, the client will receive an add
 * callback for all devices already registered.
 */
int ipps_register_client(struct ipps_client *client)
{
	struct ipps_device *device;

	mutex_lock(&device_mutex);

	list_add_tail(&client->list, &client_list);
	list_for_each_entry(device, &device_list, core_list)
		if (client->add && !add_client_context(device, client))
			client->add(device);

	mutex_unlock(&device_mutex);

	return 0;
}
EXPORT_SYMBOL(ipps_register_client);

/**
 * ipps_unregister_client - Unregister an IPPS client
 * @client:Client to unregister
 *
 * Upper level users use ipps_unregister_client() to remove their client
 * registration.  When ipps_unregister_client() is called, the client
 * will receive a remove callback for each IPPS device still registered.
 */
void ipps_unregister_client(struct ipps_client *client)
{
	struct ipps_client_data *context, *tmp;
	struct ipps_device *device;
	unsigned long flags;

	mutex_lock(&device_mutex);

	list_for_each_entry(device, &device_list, core_list) {
		if (client->remove)
			client->remove(device);

		spin_lock_irqsave(&device->client_data_lock, flags);
		list_for_each_entry_safe(context, tmp, &device->client_data_list, list)
			if (context->client == client) {
				list_del(&context->list);
				kfree(context);
			}
		spin_unlock_irqrestore(&device->client_data_lock, flags);
	}
	list_del(&client->list);

	mutex_unlock(&device_mutex);
}
EXPORT_SYMBOL(ipps_unregister_client);

int ipps_command(struct ipps_client *client, enum ipps_cmd_type cmd,
			unsigned int object, void *data)
{
	int ret = 0;
	struct ipps_device *device;

	list_for_each_entry(device, &device_list, core_list) {
		if (device->object & object) {
			if (device->command) {
				ret = device->command(device->dev, cmd, object, data);
			}
			if (ret)
				break;
			object &= ~(device->object);
		}
	}

	return ret;
}

int ipps_get_freqs_table(struct ipps_client *client, unsigned int object,
			struct cpufreq_frequency_table *table)
{
	return ipps_command(client, IPPS_GET_FREQS_TABLE, object, (void *)table);
}

int ipps_get_current_freq(struct ipps_client *client, unsigned int object,
			unsigned int *freq)
{
	return ipps_command(client, IPPS_GET_CUR_FREQ, object, (void *)freq);
}

int ipps_set_current_freq(struct ipps_client *client, unsigned int object,
			unsigned int *freq)
{
	return ipps_command(client, IPPS_SET_CUR_FREQ, object, (void *)freq);
}

int ipps_get_current_policy(struct ipps_client *client, unsigned int object,
			unsigned int *policy)
{
	return ipps_command(client, IPPS_GET_CUR_POLICY, object, (void *)policy);
}

int ipps_set_current_policy(struct ipps_client *client, unsigned int object,
			unsigned int *policy)
{
	return ipps_command(client, IPPS_SET_CUR_POLICY, object, (void *)policy);
}

int ipps_get_parameter(struct ipps_client *client, unsigned int object,
			struct ipps_param_stru *param)
{
	return ipps_command(client, IPPS_GET_PARAM, object, (void *)param);
}

int ipps_set_parameter(struct ipps_client *client, unsigned int object,
			struct ipps_param_stru *param)
{
	return ipps_command(client, IPPS_SET_PARAM, object, (void *)param);
}

int ipps_get_mode(struct ipps_client *client, unsigned int object,
			unsigned int *mode)
{
	return ipps_command(client, IPPS_GET_MODE, object, (void *)mode);
}

int ipps_set_mode(struct ipps_client *client, unsigned int object,
			unsigned int *mode)
{
	return ipps_command(client, IPPS_SET_MODE, object, (void *)mode);
}

int ipps_get_func(struct ipps_client *client, unsigned int object,
			unsigned int *func)
{
	return ipps_command(client, IPPS_GET_FUNC, object, (void *)func);
}

int ipps_set_func(struct ipps_client *client, unsigned int object,
			unsigned int *func)
{
	return ipps_command(client, IPPS_SET_FUNC, object, (void *)func);
}

int ipps_set_capacity_limit(struct ipps_client *client, unsigned int object,
			int *param)
{
	return ipps_command(client, IPPS_CAPACITY_LIMIT, object, (void *)param);
}

int ipps_get_current_profile(struct ipps_client *client, unsigned int object,
			unsigned int *profile)
{
	return ipps_command(client, IPPS_GET_CUR_PROFILE, object, (void *)profile);
}

int ipps_set_current_profile(struct ipps_client *client, unsigned int object,
			unsigned int *profile)
{
	return ipps_command(client, IPPS_SET_CUR_PROFILE, object, (void *)profile);
}
MODULE_LICENSE("GPL");
