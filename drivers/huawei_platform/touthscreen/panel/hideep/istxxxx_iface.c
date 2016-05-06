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

#ifdef ISTCORE_IF_DEVICE
#define ADDR_VR (0x0000)
#define ADDR_VR_END (0xFFFF)
#define ADDR_IMG (0x1000)
#define ADDR_UC (0x10000000)
/*------------------------------------------------------------------------------
 *
 *-----------------------------------------------------------------------------*/
#define IST510E_IOC_MAGIC 'k'
#define IST510E_CFG _IOW(IST510E_IOC_MAGIC,  1, struct ist510e_debug_cfg)
#define IST510E_RDIM _IOW(IST510E_IOC_MAGIC,  2, int)
#define IST510E_IOC_MAXNR 3

static bool hideep_dev_release_flag;

#define IST_Z_CALIB2 0x1004
#define IST_RELEASE_FILE_HANDLE 0x8000
#define IST_Z_CALIB2_READ 0x70007000
#define IST_VR_SIZE_LENGTH	4096

static int32_t hideep_get_vreg(struct ist510e *ts,u32 addr, u32 len)
{
	int32_t ret = 0;
	struct i2c_client *client = ts->client;
	struct ist510e_debug_dev  *debug_dev = &ts->debug_dev;

	TS_LOG_INFO("hideep_get_vreg start\n");
	ret = hideep_i2c_read(ts, addr, len, debug_dev->vr_buff  );
	if(ret < 0)
		goto i2c_err;
	TS_LOG_INFO("hideep_get_vreg(0x%02x:%d)\n", addr, len);

	return ret;
i2c_err:
	TS_LOG_ERR("hideep_get_vreg error\n");
	return ret;
}

static int32_t hideep_set_vreg(struct ist510e *ts, u32 addr, u32 len)
{
	int32_t ret = 0;
	struct i2c_client *client = ts->client;
	struct ist510e_debug_dev  *debug_dev = &ts->debug_dev;
	int32_t wr_remain = len;
	u32 vr_addr  = addr;
	int32_t wr_len = len;
	uint8_t* buff  = debug_dev->vr_buff;

	TS_LOG_INFO("hideep_set_vreg start\n");
	do{
		if(wr_remain >=  MAX_VR_BUFF)
			wr_len = MAX_VR_BUFF;
		else
			wr_len = wr_remain  ;
		ret = hideep_i2c_write(ts, vr_addr, wr_len, buff);
		if(ret < 0)
			goto i2c_err;
		wr_remain -= MAX_VR_BUFF;
		vr_addr   += MAX_VR_BUFF;
		buff      += MAX_VR_BUFF;
	}while(wr_remain>0);
	TS_LOG_INFO("(0x%02x:%d)\n",  addr, len);

	return ret;
i2c_err:
	TS_LOG_ERR("hideep_set_vreg error\n");
	return ret;
}

static size_t hideep_download_uc(struct ist510e *ts, const char __user *uc, int offset, size_t count)
{
	int ret;
	uint8_t * ucode;
	int len = offset;

	TS_LOG_INFO("start offset = 0x%0x, count = %d\n",offset, count);
	len += count;
	len -= 62*1024;
	if( len > 2048)
		goto hideep_download_uc_err;

	TS_LOG_INFO("hideep_download_uc processing\n");
	ucode = kmalloc(62*1024+(len)+count, GFP_KERNEL);
	if (ucode == NULL){
		goto hideep_download_uc_err;
	}
	ret = copy_from_user(ucode+offset, uc, count);
	if (ret < 0){
		TS_LOG_ERR("ADDR_UC : copy_to_user\n");
		kfree(ucode);
		return 0;
	}
	disable_irq(ts->irq);
	ret = hideep_fuse_ucode(ts->huawei_ts_data->bops, ucode, count, offset);
	enable_irq(ts->irq);
	if (ret < 0){
		TS_LOG_ERR("Fail fuse ucode\n");
		kfree(ucode);
		return 0;
	}
	kfree(ucode);
	TS_LOG_INFO("ist510e_download_uc(%d)\n", count);
	
	return count;
hideep_download_uc_err:
	TS_LOG_ERR("data(size = %d) to be downloaded is oversize \n",(offset)+ count);
	return -1;
}

static int hideep_iface_open(struct inode *inode, struct file *file)
{
	struct ist510e_debug_dev *dev_info;

	TS_LOG_INFO("hideep_iface_open start\n");
	dev_info = container_of(inode->i_cdev, struct ist510e_debug_dev, cdev);
	if (dev_info == NULL){
		TS_LOG_ERR("No such char device node\n");
		return -ENODEV;
	}
	file->private_data = dev_info;
	hideep_dev_release_flag = false;
	dev_info->ts->z_flag_calib2 = false;
	TS_LOG_INFO("hideep_iface_open end\n");

	return 0;
}

static int hideep_iface_release(struct inode *inode, struct file *file)
{
	TS_LOG_INFO("hideep_iface_release start, release_flag = %d\n", hideep_dev_release_flag);
	if(!hideep_dev_release_flag)
	    return -1;
	hideep_dev_release_flag = false;
	file->private_data = NULL;
	return 0;
}

static unsigned int hideep_iface_poll(struct file *file, struct poll_table_struct *wait)
{
	u32 mask = 0;
	struct ist510e_debug_dev *dev_info = file->private_data;

	TS_LOG_INFO("hideep_iface_poll start\n");
	if(!file->private_data){
		TS_LOG_ERR("file->private_data is NULL\n");
		return -EFAULT;
	}

	poll_wait(file, &dev_info->i_packet, wait);
	if(dev_info->i_rdy){
	    mask |= POLLIN | POLLRDNORM;
	    dev_info->i_rdy = 0;
	}
	TS_LOG_INFO("hideep_iface_poll end\n");
	return mask;
}

static ssize_t hideep_iface_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
{
	int ret = 0, i;
	struct ist510e_debug_dev *drv_info = file->private_data;
	ssize_t rd_len = 0;
	uint8_t* rd_buffer = NULL;
	u16* p_z;

	TS_LOG_DEBUG("hideep_iface_read start count = %d, (*offset) = %d(0x%x)\n",count,*offset,*offset);
	if(!file->private_data){
		TS_LOG_ERR("file->private_data is NULL\n");
		return -EFAULT;
	}
	if((IST_Z_CALIB2==(*offset))&&(((drv_info->ts->z_calib_end-drv_info->ts->z_calib_start+1)*2+2)==count) && (drv_info->ts->z_flag_ready)){
		TS_LOG_DEBUG("z_data read, index = %d\n, start = %d, end = %d", drv_info->ts->z_index, drv_info->ts->z_calib_start, drv_info->ts->z_calib_end);
		rd_buffer = drv_info->vr_buff;
		drv_info->ts->z_flag_calib2 = false;
		drv_info->ts->z_flag_ready = false;
		memcpy(rd_buffer+0, &drv_info->ts->z_index,2);
		memcpy(rd_buffer+2, &drv_info->ts->z_data[drv_info->ts->z_calib_start],count-2);
		rd_len = count;
	}else if( (*offset) <ADDR_VR_END && (*offset) != ADDR_IMG){
		TS_LOG_INFO("reading vr\n");
		drv_info->vr_size = count;
		rd_buffer = drv_info->vr_buff;
		rd_len = count;
		if(( IST_FIRST_Z_VALUE ==(*offset))&&(2==count) && (drv_info->ts->z_status)){
			TS_LOG_DEBUG("z_buffer read %d\n", drv_info->ts->z_buffer);
			drv_info->ts->z_status = false;
			p_z = drv_info->vr_buff;
			*p_z = drv_info->ts->z_buffer;
			rd_len = 2;
			ret = 0;
		}else if(( IST_APPLE_WEIGHT_VALUE ==(*offset))&&(2==count) && (drv_info->ts->apple_weight_flag)){
			TS_LOG_DEBUG("apple weight read %d\n", drv_info->ts->apple_weight_buff);
			drv_info->ts->apple_weight_flag = false;
			memcpy(rd_buffer, &drv_info->ts->apple_weight_buff,2);
			rd_len = 2;
			ret = 0;
		}else
			ret = hideep_get_vreg(drv_info->ts, *offset, rd_len);
		if(ret < 0)
			rd_len = 0;
	}else if( (*offset) == ADDR_IMG){
		TS_LOG_INFO("reading image\n");
		drv_info->im_size = count;
		rd_buffer = drv_info->im_buff;
		rd_len = count;
	} else {
		TS_LOG_ERR("ist510e_read : undefined address\n");
		return -EFAULT;
	}
	if(rd_buffer == NULL){
		TS_LOG_ERR("hideep_iface_read error\n");
		goto hideep_iface_read_err;
	}
	if(g_ts_log_cfg>=1) {
		for(i=0; i<rd_len; i++) {
			TS_LOG_DEBUG("0x%02x\n", rd_buffer[i]);
		}
	}
	ret = copy_to_user(buf, rd_buffer, rd_len);
	if (ret < 0){
		TS_LOG_ERR("error : copy_to_user\n");
		return -EFAULT;
	}
	TS_LOG_INFO("hideep_iface_read end\n");
	return rd_len;
hideep_iface_read_err:
	return -1;
}

static ssize_t hideep_iface_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
	int ret = 0;
	struct ist510e_debug_dev *drv_info = file->private_data;
	struct ist510e_debug_dev  *debug_dev = &drv_info->ts->debug_dev;
	int wr_len = 0;

	TS_LOG_DEBUG("hideep_iface_write count = %d, (*offset) = %d(0x%x)\n",count,*offset,*offset);
	if(!file->private_data){
		TS_LOG_ERR("file->private_data is NULL\n");
		return -EFAULT;
	}
	if((*offset) <ADDR_VR_END ){
		wr_len = (count < IST_VR_SIZE_LENGTH)? count : IST_VR_SIZE_LENGTH;
		TS_LOG_INFO("writing vr\n");
		ret = copy_from_user(drv_info->vr_buff, buf, wr_len);
		if (ret < 0){
			TS_LOG_ERR("error : copy_to_user\n");
			return -EFAULT;
		}
		if(( VR_SINGLE_TOUCH ==(*offset))&&(1==count)){
			TS_LOG_DEBUG("apple weight vr\n");
			switch(drv_info->vr_buff[0]){
				case 0:
					TS_LOG_DEBUG("apple weight STOP\n");
					//cancel_work_sync(&drv_info->ts->apple_weight_work);
					drv_info->ts->apple_weight_init = 0;
					drv_info->ts->apple_weight_timeout = 0;
					ret = hideep_set_vreg(drv_info->ts, *offset, wr_len);
					break;
				case 1:
					if(!drv_info->ts->apple_weight_init){
						TS_LOG_DEBUG("apple weight INIT\n");
						drv_info->ts->apple_weight_init = 1;
						drv_info->ts->apple_weight_timeout = 0;
						if(drv_info->ts->apple_weight_workqueue)
							queue_work(drv_info->ts->apple_weight_workqueue, &drv_info->ts->apple_weight_work);
					}else{
						TS_LOG_DEBUG("apple weight INIT2\n");
						drv_info->ts->apple_weight_timeout = 0;
					}
					ret = hideep_set_vreg(drv_info->ts, *offset, wr_len);
					break;
				case 2:
					TS_LOG_DEBUG("apple weight RESET\n");
					drv_info->ts->apple_weight_timeout=0;
					break;
				default:
					TS_LOG_ERR("error apple weight incorrect parameter\n");
					break;
			}
			return 1;
		}else
			ret = hideep_set_vreg(drv_info->ts, *offset, wr_len);
		if(ret < 0)
			wr_len = 0;
	}else if(((*offset)&ADDR_UC) == ADDR_UC){
		TS_LOG_INFO("download fw vr, offset = 0x%x, count = %d\n", (*offset),count);
		wr_len = hideep_download_uc(drv_info->ts, buf, (*offset)&0xffff, count);
	}else{
		TS_LOG_ERR("ist510e_write : undefined address\n");
		return 0;
	}
	TS_LOG_INFO("hideep_iface_write end\n");

	return wr_len;
}

static loff_t hideep_iface_llseek(struct file *file, loff_t off, int whence)
{
	loff_t newpos=0;
	struct ist510e_debug_dev *drv_info = file->private_data;

	TS_LOG_INFO("start, whence = %d, offset = 0x%08x\n", whence, off);
	if(!file->private_data){
		TS_LOG_ERR("file->private_data is NULL\n");
		return -EFAULT;
	}
	switch(whence){
		case 0  :
			newpos = off;
			break;
		/* set the raw mode or touch mode.*/
		case 1  :
			TS_LOG_INFO("hideep_iface_llseek set mode, off = 0x%08x\n",off);
			if(off == 0x1000){
				drv_info->im_r_en = 1;
				drv_info->vr_buff[0] = OPM_MOD_CAP;		// select frame mode...
				hideep_set_vreg(drv_info->ts, 0x00, 1);
				newpos=file->f_pos;
			}else if(off == 0x240){
				drv_info->im_r_en = 0;
				drv_info->vr_buff[0] = OPM_TOUCH_A;
				hideep_set_vreg(drv_info->ts, 0x00, 1);
				newpos=file->f_pos;
			}else if(off == IST_RELEASE_FILE_HANDLE){
				TS_LOG_DEBUG("hideep_iface_llseek set release flag \n");
				hideep_dev_release_flag = true;
				newpos=file->f_pos;
	        }else if((off & IST_Z_CALIB2_READ)==IST_Z_CALIB2_READ){
				drv_info->ts->z_calib_start = off&0x0fff;
				drv_info->ts->z_calib_end = (off>>16)&0x0fff;
				if((drv_info->ts->z_calib_end -drv_info->ts->z_calib_start+1)>(1024*4)){
					TS_LOG_ERR("hideep_iface_llseek set the frames is oversize\n");
					return -EINVAL;
			}
				TS_LOG_DEBUG("hideep_iface_llseek set calib2 start = %d, end = %d\n", drv_info->ts->z_calib_start, drv_info->ts->z_calib_end);
				drv_info->ts->z_flag_calib2 = true;
				drv_info->ts->z_flag_ready = false;
				drv_info->ts->z_index = 0;
				memset(drv_info->ts->z_data, 0x0, 4096*2);
				newpos=off;
			}else{
			newpos=file->f_pos;
			}
			break;
		/* set the config of im/vr size.*/
		case 2  :
			TS_LOG_INFO("set im/vr size, off = 0x%08x\n",off);
			drv_info->im_size = off&0xffff;
			drv_info->vr_size = (off>>16)&0xffff;
			TS_LOG_INFO("ISTCORE_IFACE_CFG : %d\n", drv_info->im_size);
			TS_LOG_INFO("ISTCORE_IFACE_CFG : %d\n", drv_info->vr_size);
			newpos=file->f_pos;
			break;
		default:
			return -EINVAL;
		}
	if (newpos < 0)
		return -EINVAL;
	file->f_pos = newpos;
	TS_LOG_INFO("hideep_iface_llseek end\n");

	return newpos;
}

static long hideep_iface_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct ist510e_debug_dev *drv_info = file->private_data;
	int err = 0;
	int ret = 0;
	struct ist510e_debug_cfg config;

	TS_LOG_INFO("hideep_iface_ioctl start\n");

	if(!file->private_data){
		TS_LOG_ERR("file->private_data is NULL\n");
		goto hideep_iface_ioctl_null;
	}
	TS_LOG_INFO("cmd = 0x%8x,IST510E_CFG = 0x%8x,IST510E_RDIM = 0x%8x\n",\
		cmd,(unsigned int)IST510E_CFG,(unsigned int)IST510E_RDIM);
	if (_IOC_TYPE(cmd) != IST510E_IOC_MAGIC)
		goto hideep_iface_ioctl_notty;
	if (_IOC_NR(cmd)    > IST510E_IOC_MAXNR)
		goto hideep_iface_ioctl_notty2;
	if (_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err =  !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
	if(err)
		goto hideep_iface_ioctl_err;

	switch(cmd){
		case IST510E_CFG:
			ret = copy_from_user(&config , (void*)arg, sizeof(struct ist510e_debug_cfg));
			drv_info->im_size = config.im_size;
			drv_info->vr_size = config.vr_size;
			TS_LOG_INFO("ISTCORE_IFACE_CFG : im_size = %d,vr_size = %d\n", \
				drv_info->im_size,drv_info->vr_size);
			break;
		case IST510E_RDIM:
			TS_LOG_INFO("IST510E_RDIM\n");
			ret = __get_user(drv_info->im_r_en , (uint8_t __user *)arg);
			if(drv_info->im_r_en != 0){
				drv_info->vr_buff[0] = OPM_MOD_CAP;
			}else{
				drv_info->vr_buff[0] = OPM_TOUCH_A;
			}
			hideep_set_vreg(drv_info->ts, 0x00, 1);
			break;
		default:
			return -ENOTTY;
	}
	TS_LOG_INFO("hideep_iface_ioctl end\n");

	return 0;
hideep_iface_ioctl_null:
	TS_LOG_ERR("null\n");
	return -EFAULT;
hideep_iface_ioctl_notty:
	TS_LOG_ERR("notty not match magic\n");
	return -ENOTTY;
hideep_iface_ioctl_notty2:
	TS_LOG_ERR("notty over max\n");
	return -ENOTTY;
hideep_iface_ioctl_err:
	TS_LOG_ERR("err = 0x%x\n",err);
	return -EFAULT;
}

static const struct file_operations ist510e_debug_fops =
{
	.owner = THIS_MODULE    ,
	.open = hideep_iface_open   ,
	.poll = hideep_iface_poll   ,
	.release = hideep_iface_release,
	.read = hideep_iface_read   ,
	.write = hideep_iface_write  ,
	.llseek = hideep_iface_llseek ,
	.unlocked_ioctl = hideep_iface_ioctl ,
};
static void hideep_iface_unregister(struct ist510e *ts)
{
	struct ist510e_debug_dev  *dev  = &ts->debug_dev;

	TS_LOG_INFO("hideep_iface_unregister start\n");
	device_destroy(ts->debug_class, ts->debug_dev_no);
	cdev_del(&dev->cdev);

	if(dev->im_buff)
		kfree(dev->im_buff);
	if(dev->vr_buff)
		kfree(dev->vr_buff);

	return;
}
static int hideep_iface_register(struct ist510e *ts, u32 minor)
{
	int err = 0;
	struct device *device = NULL;
	struct ist510e_debug_dev  *dev  = &ts->debug_dev;
	dev_t devno = ts->debug_dev_no;

	TS_LOG_INFO("hideep_iface_register start\n");
	cdev_init(&dev->cdev, &ist510e_debug_fops);
	dev->cdev.owner = THIS_MODULE;
	err = cdev_add(&dev->cdev, ts->debug_dev_no, 1);
	if (err){
		goto err;
	}
	device = device_create(ts->debug_class,NULL,devno,NULL, ISTCORE_IF_DEVICE_NAME, MINOR(devno));
	if (IS_ERR(device)){
		err = PTR_ERR(device);
		cdev_del(&dev->cdev);
		goto err;
	}
	TS_LOG_INFO("hideep_iface_register end\n");

	return 0;
err:
	TS_LOG_ERR("ist510e_debug_register failed\n");
	return err;
}

void hideep_iface_uninit(struct ist510e *ts)
{
	hideep_iface_unregister(ts);
	if(ts->debug_class)
		class_destroy(ts->debug_class);
	unregister_chrdev_region(ts->debug_dev_no, 1);
	return;
}
static char* hideep_char_devnode(struct device *dev, mode_t *mode)
{
	if (!mode)
		return NULL;
	*mode = (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        TS_LOG_INFO("/dev/%s\n", dev_name(dev));
	return kasprintf(GFP_KERNEL, "/dev/%s\n", dev_name(dev));
}
int hideep_iface_init(struct ist510e *ts)
{
	int ret = 0;
	dev_t dev_id = 0;
	struct ist510e_debug_dev *debug_drv = &ts->debug_dev;

	ret = alloc_chrdev_region(&dev_id, 0, 1, ISTCORE_IF_DEVICE_NAME);
	if (ret < 0){
		return ret;
	}
	ts->debug_class  = class_create(THIS_MODULE, ISTCORE_IF_DEVICE_NAME);
	ts->debug_dev_no = dev_id;
	ts->debug_class->devnode = hideep_char_devnode;
	if (IS_ERR(ts->debug_class)){
		ret = PTR_ERR(ts->debug_class);
		goto fail;
	}
	ret = hideep_iface_register(ts, 0);
	if (ret){
		goto fail;
	}
	init_waitqueue_head(&debug_drv->i_packet);
	debug_drv->ts = ts;
	debug_drv->im_r_en = 0;                                                  // disable
	debug_drv->im_size = 4096;
	debug_drv->vr_size = IST_VR_SIZE_LENGTH;
	debug_drv->im_buff = kmalloc(debug_drv->im_size, GFP_KERNEL);
	debug_drv->vr_buff = kmalloc(debug_drv->vr_size, GFP_KERNEL);
	if(!debug_drv->im_buff || !debug_drv->vr_buff){
		goto fail;
	}
	TS_LOG_INFO("istxxxx_iface_init done\n");

	return 0;

fail:
	hideep_iface_uninit(ts);
	TS_LOG_ERR("failed\n");
	return ret;
}
#endif


