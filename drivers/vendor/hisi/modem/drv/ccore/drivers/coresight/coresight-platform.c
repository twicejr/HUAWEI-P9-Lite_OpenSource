/*************************************************************************
*   版权所有(C) 1987-2014, 深圳华为技术有限公司.
*
*   文 件 名 :  Coresight.c
*
*   作    者 :  l00169177
*
*   描    述 :  coresight框架
*
*   修改记录 :  2014年10月24日  v1.00  l00169177  创建
*************************************************************************/
#include <stdio.h>
#include "coresight-platform.h"
#include "osl_list.h"
#include "osl_sem.h"
#include "osl_types.h"
#include "osl_common.h"
#include "osl_malloc.h"
#include "securec.h"
/*lint --e{801, 830, 530, 539, 732, 534, 586, 522}*/

#define NONE_SINK		(-1)

static int current_sink = NONE_SINK;
static struct list_head coresight_devs;
static struct list_head coresight_orph_conns;
struct semaphore coresight_platform_mutex;


static void coresight_fixup_orphan_conns(struct coresight_platform_device_s *device)
{
	struct coresight_connection_info_s *connect, *temp;

	list_for_each_entry_safe(connect, temp, &coresight_orph_conns, link) {
		if (connect->child_id == device->id) {
			connect->child_dev = device;
			list_del(&connect->link);
		}
	}
}


static void coresight_fixup_device_conns(struct coresight_platform_device_s *device)
{
	unsigned int i;
	struct coresight_platform_device_s *temp_device;
	bool found;

	for (i = 0; i < device->nr_conns; i++) {
		found = false;
		list_for_each_entry(temp_device, &coresight_devs, dev_link) {
			if (device->conns[i].child_id == temp_device->id) {
				device->conns[i].child_dev = temp_device;
				found = true;
				break;
			}
		}
		if (found == true)
			list_add_tail(&device->conns[i].link,
				      &coresight_orph_conns);
	}
}


static int coresight_search_link_inport(struct coresight_platform_device_s *device)
{
	unsigned int i;
	struct coresight_platform_device_s *parent;
	struct coresight_connection_info_s *connect;

	parent = container_of(device->path_link.next, struct coresight_platform_device_s,
			     path_link);
	for (i = 0; i < parent->nr_conns; i++) {
		connect = &parent->conns[i];
		if (connect->child_dev == device)
			return connect->child_port;
	}

	cs_error("coresight: couldn't find inport, parent: %d, child: %d\n",
	       parent->id, device->id);
	return 0;
}


static int coresight_search_link_outport(struct coresight_platform_device_s *device)
{
	unsigned int i;
	struct coresight_platform_device_s *child;
	struct coresight_connection_info_s *connect;

	child = container_of(device->path_link.prev, struct coresight_platform_device_s,
			      path_link);
	for (i = 0; i < device->nr_conns; i++) {
		connect = &device->conns[i];
		if (connect->child_dev == child)
			return connect->outport;
	}

	cs_error("coresight: couldn't find outport, parent: %d, child: %d\n",
	       device->id, child->id);
	return 0;
}

static int coresight_sink_enable(struct coresight_platform_device_s *device)
{
	int ret;

	if (device->refcnt.sink_refcnt == 0) {
		if (device->ops->sink_ops->enable) {
			ret = device->ops->sink_ops->enable(device);
			if (ret == BSP_OK)/*lint !e830*/
                device->enable = true;/*lint !e525*/
            else/*lint !e525*/
                return ret;
		}
	}
	device->refcnt.sink_refcnt++;

	return 0;
}

static void coresight_sink_disable(struct coresight_platform_device_s *device)
{
	if (device->refcnt.sink_refcnt == 1) {
		if (device->ops->sink_ops->disable) {
			device->ops->sink_ops->disable(device);
			device->enable = false;
		}
	}
	device->refcnt.sink_refcnt--;
}

static int coresight_link_enable(struct coresight_platform_device_s *device)
{
	int ret;
	int port;
    int in;
    int out;

	in = coresight_search_link_inport(device);
	out = coresight_search_link_outport(device);

	if (device->subtype.link_subtype == CORESIGHT_DEV_SUBTYPE_LINK_MERG){
		port = in;
	}
	else{
		port = 0;
	}

	if (device->refcnt.link_refcnts[port] == 0) {
		if (device->ops->link_ops->enable) {
			ret = device->ops->link_ops->enable(device, in,
							   out);
			if (ret == BSP_OK)/*lint !e830*/
                device->enable = true;/*lint !e525*/
            else/*lint !e525*/
				return ret;
		}
	}
	device->refcnt.link_refcnts[port]++;

	return 0;
}

static void coresight_link_disable(struct coresight_platform_device_s *device)
{
	int port;
    int in;
    int out;

	in = coresight_search_link_inport(device);
	out = coresight_search_link_outport(device);

	if (device->subtype.link_subtype == CORESIGHT_DEV_SUBTYPE_LINK_MERG){
		port = in;
	}
	else{
		port = 0;
	}

	if (device->refcnt.link_refcnts[port] == 1) {
		if (device->ops->link_ops->disable) {
			device->ops->link_ops->disable(device, in, out);
			device->enable = false;
		}
	}
	device->refcnt.link_refcnts[port]--;
}

static int coresight_source_enable(struct coresight_platform_device_s *device)
{
	int ret;

	if (device->refcnt.source_refcnt == 0) {
		if (device->ops->source_ops->enable) {
			ret = device->ops->source_ops->enable(device);
			if (ret == BSP_OK)/*lint !e830*/
				device->enable = true;/*lint !e525*/
            else/*lint !e525*/
                return ret;
		}
	}
	device->refcnt.source_refcnt++;

	return 0;
}

static void coresight_source_disable(struct coresight_platform_device_s *device)
{
	if (device->refcnt.source_refcnt == 1) {
		if (device->ops->source_ops->disable) {
			device->ops->source_ops->disable(device);
			device->enable = false;
		}
	}
	device->refcnt.source_refcnt--;
}

static struct list_head *coresight_platform_create_path(struct coresight_platform_device_s *device,
					      struct list_head *path)
{
	unsigned int i;
	struct list_head *list;
	struct coresight_connection_info_s * connect;

	if (device->id == current_sink) {
		list_add_tail(&device->path_link, path);
		return path;
	}

	for (i = 0; i < device->nr_conns; i++) {
		connect = &device->conns[i];
		list = coresight_platform_create_path(connect->child_dev, path);
		if (list) {
			list_add_tail(&device->path_link, list);
			return list;
		}
	}
	return NULL;
}

static void coresight_platform_delete_path(struct list_head *path)
{
	struct coresight_platform_device_s *device, *temp;

	list_for_each_entry_safe(device, temp, path, path_link)
		list_del(&device->path_link);
}

static int coresight_platform_path_enable(struct list_head *path, bool incl_source)
{
	int ret = 0;
	struct coresight_platform_device_s *device;

	list_for_each_entry(device, path, path_link) {
		if (device == list_first_entry(path, struct coresight_platform_device_s,
					   path_link)) {
			ret = coresight_sink_enable(device);
		} else if (list_is_last(&device->path_link, path)) {
			if (incl_source)
				ret = coresight_source_enable(device);
		} else {
			ret = coresight_link_enable(device);
		}
		if (ret)
			goto err;
	}
	return 0;
err:
	list_for_each_entry_continue_reverse(device, path, path_link) {
		if (device == list_first_entry(path, struct coresight_platform_device_s,
					   path_link)) {
			coresight_sink_disable(device);
		} else if (list_is_last(&device->path_link, path)) {
			if (incl_source)
				coresight_source_disable(device);
		} else {
			coresight_link_disable(device);
		}
	}
	return ret;
}

static void coresight_platform_path_disable(struct list_head *path, bool incl_source)
{
	struct coresight_platform_device_s *device;

	list_for_each_entry(device, path, path_link) {
		if (device == list_first_entry(path, struct coresight_platform_device_s,
					   path_link)) {
			coresight_sink_disable(device);
		} else if (list_is_last(&device->path_link, path)) {
			if (incl_source)
				coresight_source_disable(device);
		} else {
			coresight_link_disable(device);
		}
	}
}

int coresight_platform_device_enable(struct coresight_platform_device_s *device)
{
	int ret = 0;
	LIST_HEAD(path);
    if(IS_ERR_OR_NULL(device))
    {
        return BSP_ERROR;
    }

	if (device->type != CORESIGHT_DEV_TYPE_SOURCE) {
		ret = -EINVAL;
		return ret;
	}
	if (device->enable)
	{
		return ret;
	}
	coresight_platform_create_path(device, &path);
	ret = coresight_platform_path_enable(&path, true);
	coresight_platform_delete_path(&path);

    return ret;
}

void coresight_platform_device_disable(struct coresight_platform_device_s *device)
{
	LIST_HEAD(path);

	if (IS_ERR_OR_NULL(device))
		return;

	if (device->type != CORESIGHT_DEV_TYPE_SOURCE) {
		return;
	}
	if (!device->enable)
		return;

	coresight_platform_create_path(device, &path);
	coresight_platform_path_disable(&path, true);
	coresight_platform_delete_path(&path);
}

void coresight_platform_device_abort(void)
{
	struct coresight_platform_device_s *device;

    down(&coresight_platform_mutex);
	if (current_sink == NONE_SINK)
		goto out;

	list_for_each_entry(device, &coresight_devs, dev_link) {
		if (device->id == current_sink) {
			if (device->enable && device->ops->sink_ops->abort) {
				device->ops->sink_ops->abort(device);
				device->enable = false;
			}
		}
	}
out:
	up(&coresight_platform_mutex);
}

struct coresight_platform_device_s *coresight_platform_device_register(struct coresight_platform_desc_s *desc)
{
	unsigned int i;
	unsigned int nr_refcnts;
	int *refcnts = NULL;
	struct coresight_platform_device_s *device = NULL;
	struct coresight_connection_info_s *connect = NULL;

    if(IS_ERR_OR_NULL(desc))
    {
        return NULL;
    }

    device = osl_malloc(sizeof(struct coresight_platform_device_s));
	if (!device) {
		goto err_malloc_device;
	}
    memset_s(device, sizeof(struct coresight_platform_device_s), 0, sizeof(struct coresight_platform_device_s));
	device->id = desc->pdata->id;

	if (desc->type == CORESIGHT_DEV_TYPE_LINK ||
	    desc->type == CORESIGHT_DEV_TYPE_LINKSINK) {
		if (desc->subtype.link_subtype == CORESIGHT_DEV_SUBTYPE_LINK_MERG)
			nr_refcnts = (unsigned int)desc->pdata->nr_inports;
		else
			nr_refcnts = 1;

        refcnts = osl_malloc(sizeof(int) * nr_refcnts);
		if (!refcnts) {
			goto err_malloc_refcnts;
		}
        memset_s(refcnts, sizeof(int) * nr_refcnts, 0, sizeof(int) * nr_refcnts);
		device->refcnt.link_refcnts = refcnts;
	}

	device->nr_conns = desc->pdata->nr_outports;

    if(device->nr_conns > 0)
    {
        connect = osl_malloc(sizeof(struct coresight_connection_info_s) * device->nr_conns);
	    if (!connect) {
		    goto err_malloc_conns;
	    }
        memset_s(connect, sizeof(struct coresight_connection_info_s) * device->nr_conns, 0, sizeof(struct coresight_connection_info_s) * device->nr_conns);
	    for (i = 0; i < device->nr_conns; i++) {
		    connect[i].outport = desc->pdata->outports[i];
		    connect[i].child_id = desc->pdata->child_ids[i];
		    connect[i].child_port = desc->pdata->child_ports[i];
	    }
	    device->conns = connect;
    }

	device->type     = desc->type;
	device->subtype  = desc->subtype;
    device->ops      = desc->ops;
    device->drvdata  = desc->drvdata;

	down(&coresight_platform_mutex);
	if (desc->pdata->default_sink) {
		if (current_sink == NONE_SINK) {
			current_sink = device->id;
		} else {
			goto err_sink;
		}
	}
	coresight_fixup_device_conns(device);
	coresight_fixup_orphan_conns(device);
	list_add_tail(&device->dev_link, &coresight_devs);
	up(&coresight_platform_mutex);
	return device;

err_sink:
	up(&coresight_platform_mutex);
    osl_free(connect);
err_malloc_conns:
    osl_free(refcnts);
err_malloc_refcnts:
    osl_free(device);
err_malloc_device:
	return NULL;
}

int coresight_platform_init(void)
{
    sema_init(&coresight_platform_mutex, SEM_FULL);

    INIT_LIST_HEAD(&coresight_devs);
    INIT_LIST_HEAD(&coresight_orph_conns);

    cs_error(" ok.\n");
    return 0;
}

