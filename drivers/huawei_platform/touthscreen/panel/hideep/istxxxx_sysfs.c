/*******************************************************************************
 * Copyright (C) 2014 HiDeep, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 *******************************************************************************/

#include "ist520e.h"

extern struct ist510e *g_istxxxx_data;
extern struct ts_data g_ts_data;

 ssize_t mode_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct ist510e *ts = g_istxxxx_data;
	struct ist510e_debug_dev  *dev_info = &ts->debug_dev;

	TS_LOG_INFO("Mode = %d\n", dev_info->im_r_en);
	memcpy(buf,&dev_info->im_r_en,1);
	return 1;
}

ssize_t mode_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct ist510e *ts = g_istxxxx_data;
	struct ist510e_debug_dev  *dev_info = &ts->debug_dev;
	unsigned char mode;

	if(count !=1)
		goto mode_store_err;
	sscanf (buf,"%x\n", &mode);
	TS_LOG_INFO("mode = %d\n", mode);
	dev_info->im_r_en = mode;
	if(mode == 1){
		dev_info->vr_buff[0] = OPM_MOD_CAP;		// select frame mode...
	}else{
		dev_info->vr_buff[0] = OPM_TOUCH_A;		// select touch mode...
	}
	return count;
mode_store_err:
	TS_LOG_ERR("incorrect count = %d\n", count);
	if(count)
		TS_LOG_ERR("buf[0] = 0x%x\n", buf[0]);
	return -1;
}

 ssize_t im_size_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct ist510e *ts = g_istxxxx_data;
	struct ist510e_debug_dev  *dev_info = &ts->debug_dev;

	TS_LOG_INFO("im_size = 0x%04x\n", dev_info->im_size);
	memcpy(&buf[0],&dev_info->im_size,2);
	return 4;
}

ssize_t im_size_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct ist510e *ts = g_istxxxx_data;
	struct ist510e_debug_dev  *dev_info = &ts->debug_dev;
	unsigned short * im_size;

	if(count!=2)
		goto  im_size_store_err;
	im_size = (unsigned short *)buf;
	TS_LOG_INFO("im_size = 0x%04x\n", *im_size);
	dev_info->im_size = *im_size;
	return count;
im_size_store_err:
	TS_LOG_ERR("incorrect count = %d\n", count);
	return -1;
}

 ssize_t vr_size_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct ist510e *ts = g_istxxxx_data;
	struct ist510e_debug_dev  *dev_info = &ts->debug_dev;

	TS_LOG_INFO("vr_size = 0x%04x\n", dev_info->vr_size);
	memcpy(&buf[0],&dev_info->vr_size,2);
	return 4;
}

ssize_t vr_size_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct ist510e *ts = g_istxxxx_data;
	struct ist510e_debug_dev  *dev_info = &ts->debug_dev;
	unsigned short * vr_size;

	if(count!=2)
		goto  vr_size_store_err;
	vr_size = (unsigned short *)buf;
	TS_LOG_INFO("vr_size = 0x%04x\n", *vr_size);
	dev_info->vr_size = *vr_size;
	return count;
vr_size_store_err:
	TS_LOG_ERR("incorrect count = %d\n", count);
	return -1;
}

ssize_t status_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct ist510e *ts = g_istxxxx_data;
	struct ist510e_debug_dev  *dev_info = &ts->debug_dev;
	int ret;

	TS_LOG_INFO("status = %d\n", dev_info->i_rdy);
	memcpy(buf,&dev_info->i_rdy,1);
	return 1;
}

ssize_t status_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{    
	struct ist510e *ts = g_istxxxx_data;
	struct ist510e_debug_dev  *dev_info = &ts->debug_dev;
	unsigned char ready;

	if(count !=1)
		goto status_store_err;
	sscanf (buf,"%x\n", &ready);
	TS_LOG_INFO("status = %d\n", ready);
	dev_info->i_rdy = ready;
	return count;
status_store_err:
	TS_LOG_ERR("incorrect count = %d\n", count);
	return -1;
}

ssize_t data_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct ist510e *ts = g_istxxxx_data;
	struct ist510e_debug_dev  *dev_info = &ts->debug_dev;
	int ret;

	TS_LOG_INFO("copy to buf\n");
	memcpy(buf,dev_info->im_buff,dev_info->im_size);
	return dev_info->im_size;
}

/*------------------------------------------------------------------------------
 * vr_addr
 *-----------------------------------------------------------------------------*/
 ssize_t
vr_addr_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct ist510e *ts = g_istxxxx_data;
	struct ist510e_debug_dev  *dev_info = &ts->debug_dev;

	TS_LOG_INFO("vr_addr = 0x%04x\n", dev_info->vr_addr);
	memcpy(buf,&dev_info->i_rdy,2);
	return 2;
}

ssize_t vr_addr_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct ist510e *ts = g_istxxxx_data;
	struct ist510e_debug_dev  *dev_info = &ts->debug_dev;
	unsigned short* addr;

	if(count!=2)
		goto  vr_addr_store_err;
	addr = (unsigned short *)buf;
	TS_LOG_INFO("vr_addr = %d\n", *addr);
	dev_info->vr_addr = *addr;
	return count;
vr_addr_store_err:
	TS_LOG_ERR("incorrect count = %d\n", count);
	return -1;
}

 ssize_t vr_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct ist510e *ts = g_istxxxx_data;
	struct ist510e_debug_dev  *dev_info = &ts->debug_dev;
	int ret = 0;

	ret = hideep_i2c_read(ts, dev_info->vr_addr, dev_info->vr_size, dev_info->vr_buff);
	if(ret < 0)
		goto vr_show_err;
	TS_LOG_INFO("copy vr to user\n");
	memcpy(buf,dev_info->vr_buff,dev_info->vr_size);
	return dev_info->vr_size;
vr_show_err:
	TS_LOG_INFO("vr show error ret = 0x%x\n", ret);
	return -1;
}

ssize_t vr_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct ist510e *ts = g_istxxxx_data;
	struct ist510e_debug_dev  *dev_info = &ts->debug_dev;
	int ret = 0;
	unsigned char val = 0;

	if(count != dev_info->vr_size){
		ret = hideep_i2c_write(ts, dev_info->vr_addr, dev_info->vr_size, buf);
		if(ret < 0)
			goto vr_store_err;
	}
	TS_LOG_INFO("Value(0x%04x)= 0x%02x\n", dev_info->vr_addr, val);
	return dev_info->vr_size;
vr_store_err:
	TS_LOG_INFO("vr store error ret = 0x%x\n", ret);
	return -1;
}

#ifdef HIDEEP_TRACE_TOUCH_EVENT
 ssize_t touch_event_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct ist510e *ts = g_istxxxx_data;
	u32 i;
	u32 j;
	u32 index_buf;
	u32 offset=0;
	u32 max_count;
	struct ist510e_touch_evt *te;
	struct timespec *time;

	TS_LOG_INFO("touch_event_show enter \n");
	if(ts->debug_evt==NULL)
	return -1;
	if(ts->debug_total>=MAX_DEBUG_COUNT){
		offset = ts->debug_index;
		max_count = MAX_DEBUG_COUNT;
	}else {
		offset = 0;
		max_count = ts->debug_total;
	}
	for(i=0;i<max_count;i++){
		index_buf = i+offset>MAX_DEBUG_COUNT?i+offset-MAX_DEBUG_COUNT:i+offset;
		printk("touch count = %d\n\n",ts->debug_evt[index_buf].count);
		if(ts->debug_evt[index_buf].count>TOUCH_MAX_COUNT)
			continue;
		time = &ts->event_time[index_buf];
		printk("T= %d.%09d\n\n",time->tv_sec,time->tv_nsec);
		for(j=0;j<ts->debug_evt[index_buf].count;j++){
			te = &ts->debug_evt[index_buf].events[j];
			printk("flag=0x%02x, type=0x%02x, index=0x%02x,x=%d,y=%d,z=%d,w=%d\n\n",
			    te->flag,te->type,te->index,te->x,te->y,te->z,te->w);
		}
	}
}
#endif

static DEVICE_ATTR(hideep_mode           , 0666,  mode_show      	, mode_store);
static DEVICE_ATTR(hideep_im_size        , 0666,  im_size_show   	, im_size_store);
static DEVICE_ATTR(hideep_vr_size        , 0666,  vr_size_show   	, vr_size_store);
static DEVICE_ATTR(hideep_status         , 0666,  status_show    	, status_store);
static DEVICE_ATTR(hideep_data           , 0666,  data_show      	, NULL);
static DEVICE_ATTR(hideep_vr_addr        , 0666,  vr_addr_show   	, vr_addr_store);
static DEVICE_ATTR(hideep_vr             , 0666,  vr_show        	, vr_store);
#ifdef HIDEEP_TRACE_TOUCH_EVENT
static DEVICE_ATTR(hideep_touch_event    , 0666,  touch_event_show  , NULL);
#endif

static struct attribute *ist510e_ts_sysfs_entries[] =
{
	&dev_attr_hideep_mode.attr,
	&dev_attr_hideep_im_size.attr,
	&dev_attr_hideep_vr_size.attr,
	&dev_attr_hideep_status.attr,
	&dev_attr_hideep_data.attr,
	&dev_attr_hideep_vr_addr.attr,
	&dev_attr_hideep_vr.attr,
#ifdef HIDEEP_DEBUG_LEVEL
	&dev_attr_hideep_debug.attr,
#endif
#ifdef HIDEEP_TRACE_TOUCH_EVENT
	&dev_attr_hideep_touch_event.attr,
#endif
	NULL
};

static struct attribute_group ist510e_ts_attr_group =
{
	.attrs  = ist510e_ts_sysfs_entries,
};

int hideep_sysfs_init(struct ist510e *ts)
{
	int ret = 0;
	struct  i2c_client *client = ts->client;

	TS_LOG_INFO("hideep_sysfs_init enter\n");
#ifdef HIDEEP_TRACE_TOUCH_EVENT
	TS_LOG_INFO("debug_buf size = %d\n",sizeof(struct ist510e_touch_debug_evt)*MAX_DEBUG_COUNT);
	ts->debug_evt = kmalloc(sizeof(struct ist510e_touch_debug_evt)*MAX_DEBUG_COUNT,GFP_KERNEL);
	if(ts->debug_evt == NULL){
		TS_LOG_ERR("evt no memory\n");
		goto err_evt_no_memory;
	}
	ts->event_time = kmalloc(sizeof(struct timespec)*MAX_DEBUG_COUNT,GFP_KERNEL);
	if(ts->event_time == NULL){
		TS_LOG_ERR("time no memory\n");
		goto err_time_no_memory;
	}
	ts->debug_index = MAX_DEBUG_COUNT;
	ts->debug_total = 0;
#endif

	ret = sysfs_create_group(&g_ts_data.ts_dev->dev.kobj, &ist510e_ts_attr_group);
	if (ret != 0){
		TS_LOG_ERR("unable to create sysfs group.\n");
		goto err;
	}
	TS_LOG_INFO("hideep_sysfs_init finished\n");

	return ret;
err:
#ifdef HIDEEP_TRACE_TOUCH_EVENT
	if (ts->event_time)
		kfree(ts->event_time);
err_time_no_memory:
	if (ts->debug_evt)
		kfree(ts->debug_evt);
err_evt_no_memory:
#endif
	return ret;
}

int hideep_sysfs_uninit(struct ist510e *ts)
{
	struct  i2c_client *client = ts->client;

	TS_LOG_INFO("hideep_sysfs_exit\n");
#ifdef HIDEEP_TRACE_TOUCH_EVENT
	if(ts->debug_evt)
		kfree(ts->debug_evt);
	if(ts->event_time)
		kfree(ts->event_time);
#endif
	sysfs_remove_group(&g_ts_data.ts_dev->dev.kobj, &ist510e_ts_attr_group);
	return 0;
}
