


#include <linux/compiler.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/types.h>
#include <linux/videodev2.h>
#include <media/huawei/camera.h>
#include <media/v4l2-event.h>
#include <media/v4l2-fh.h>
#include <media/v4l2-subdev.h>
#include <media/videobuf2-core.h>
#include <linux/pm_qos.h>
#include <linux/ctype.h>
#include "hwisp_intf.h"
#include "cam_log.h"
#include "hw_isp_io.h"
#include "isp_ops.h"
#include "trace_ovisp23.h"
#include <dsm/dsm_pub.h>

static struct pm_qos_request qos_request_ddr_up_record;
static struct pm_qos_request qos_request_ddr_down_record;
static bool camera_record_fixddrfreq = false;
#define DDR_BLOCK_PROFILE	8000

struct dsm_client_ops ops1={
	.poll_state = NULL,
	.dump_func = NULL,
};

struct dsm_dev dev_ovisp23 = {
	.name = "dsm_ovisp23",
	.device_name = NULL,
	.ic_name = NULL,
	.module_name = NULL,
	.fops = &ops1,
	.buff_size = 30000,
};

struct dsm_client *client_ovisp23;

typedef enum _tag_ovisp23_constants
{
    OVISP23_MAX_STREAMS                         =   9,
} ovisp23_constants_t;
/*
typedef struct _tag_ovisp23_stream_res
{
    hwisp_stream_resource_t                     base;
} ovisp23_stream_res_t;
*/


typedef struct _tag_ovisp23
{
	struct platform_device*                     pdev;
	hwisp_intf_t                                intf;
	hwisp_notify_intf_t*                        notify;
	bool                                        power_on_state;
	struct list_head                            streams;
    char const*                                 name;
} ovisp23_t;

#define I2OV(i) container_of(i, ovisp23_t, intf)
#define I2STM(i) container_of(i, hwisp_stream_t, intf)


static char const* ovisp23_get_name(hwisp_intf_t* i);
static int ovisp23_power_on(hwisp_intf_t* i);
static int ovisp23_power_off(hwisp_intf_t* i);
static int ovisp23_reset(hwisp_intf_t* i);
static int ovisp23_config(hwisp_intf_t* i,void* cfg);
static int ovisp23_create_stream(hwisp_intf_t* i,struct video_device* vdev,hwisp_stream_info_t* info);
static int ovisp23_stream_start(hwisp_intf_t* i, hwisp_stream_intf_t* info);
static int ovisp23_stream_stop(hwisp_intf_t* i,hwisp_stream_intf_t* info);
static int ovisp23_record_fixddrfreq(hwisp_intf_t* i, void* ddrfreq);


u32 isp_debug_flag;

static hwisp_vtbl_t
s_vtbl_ovisp23 =
{
    .get_name = ovisp23_get_name,
    .power_on = ovisp23_power_on,
    .power_off = ovisp23_power_off,
    .reset = ovisp23_reset,
    .config = ovisp23_config,
    .create_stream = ovisp23_create_stream,
    .stream_start = ovisp23_stream_start,
    .stream_stop = ovisp23_stream_stop,
	.fix_ddrfreq = ovisp23_record_fixddrfreq,
};


static ovisp23_t
s_ovisp23 =
{
    .intf = { .vtbl = &s_vtbl_ovisp23, },
    .name = "ovisp2.3",
};

static const struct of_device_id
s_ovisp23_dt_match[] =
{
	{
        .compatible = "huawei,huawei_isp",
        .data = &s_ovisp23.intf,
    },
	{
    },
};

bool is_ovisp23_poweron(void)
{
	/* should remove this check!!! */
	return (s_ovisp23.power_on_state);
}

static char const*
ovisp23_get_name(
        hwisp_intf_t* i)
{
    ovisp23_t* ov = NULL;
    ov = I2OV(i);
    return ov->name;
}

static void k3_isp_fix_ddrfreq(unsigned int ddr_bandwidth)
{
	qos_request_ddr_up_record.pm_qos_class = 0;
	qos_request_ddr_down_record.pm_qos_class = 0;
	pm_qos_add_request(&qos_request_ddr_up_record,PM_QOS_MEMORY_THROUGHPUT_UP_THRESHOLD, ddr_bandwidth);
	pm_qos_add_request(&qos_request_ddr_down_record,PM_QOS_MEMORY_THROUGHPUT , ddr_bandwidth);
	return;
}

static void k3_isp_release_ddrfreq(void)
{
	pm_qos_remove_request(&qos_request_ddr_up_record);
	pm_qos_remove_request(&qos_request_ddr_down_record);
	return;
}

static void k3_isp_update_ddrfreq_up2down(unsigned int ddr_bandwidth)
{
	pm_qos_update_request(&qos_request_ddr_down_record, ddr_bandwidth);
	pm_qos_update_request(&qos_request_ddr_up_record, ddr_bandwidth);
	return;
}

static void k3_isp_update_ddrfreq_down2up(unsigned int ddr_bandwidth)
{
	pm_qos_update_request(&qos_request_ddr_up_record, ddr_bandwidth);
	pm_qos_update_request(&qos_request_ddr_down_record, ddr_bandwidth);
	return;
}

static int
ovisp23_power_on(
        hwisp_intf_t* i)
{
	int rc = 0;
	ovisp23_t* ov = I2OV(i);

	cam_info("%s enter", __func__);

	/*
	 * WARNNING: do not use atomic cnt to keep reference
	 * when in process of powering, but POWER has not been really done yet,
	 * another thread invokes it, will consider power has been done.
	 *
	 * (1) use power_on_state to indicate POWERON done state
	 * (2) hold lock to make sure it never be invoked by more than one thread
	 */
	if (!ov->power_on_state) {
		rc |= hw_isp_init(&ov->pdev->dev);
		rc |= hw_isp_poweron();
		k3_isp_fix_ddrfreq(DDR_BLOCK_PROFILE);
		ov->power_on_state = true;
	} else {
		cam_notice("%s no need to do this", __func__);
	}

	return 0;
}

static int
ovisp23_power_off(
        hwisp_intf_t* i)
{
	int rc = 0;
	ovisp23_t* ov = I2OV(i);

	cam_info("%s enter", __func__);

	if (ov->power_on_state) {
		ov->power_on_state = false;
		rc |= hw_isp_poweroff();
		rc |= hw_isp_deinit(&ov->pdev->dev);
		k3_isp_release_ddrfreq();
	} else {
		cam_notice("%s no need to do this", __func__);
	}
    return 0;
}

static int
ovisp23_reset(
        hwisp_intf_t* i)
{
    ovisp23_t* ov = NULL;
	ov = I2OV(i);
    return 0;
}
/*
static int
ovisp23_load_firmware(
        hwisp_intf_t* i)
{
    ovisp23_t* ov = NULL;
	ov = I2OV(i);
    return 0;
}

static int
ovisp23_init_reg(
        hwisp_intf_t* i)
{
    ovisp23_t* ov = NULL;
	ov = I2OV(i);
    return 0;
}
*/
/*
static hwisp_stream_resource_t*
ovisp23_allocate_stream_resource(
        hwisp_intf_t* i,
        hwisp_stream_info_t* si)
{
    // TODO: just let testing code go
    ovisp23_t* ov = I2OV(i);
    return (hwisp_stream_resource_t*)&ov->stream_res[0];
}

static int
ovisp23_release_stream_resource(
        hwisp_intf_t* i,
        hwisp_stream_resource_t* sr)
{
    ovisp23_t* ov = NULL;
	ov = I2OV(i);
    return 0;
}
*/
static int ovisp23_read_reg(struct isp_cfg_reg *data)
{
	switch(data->val_bits)
	{
		case 8:
			data->val = ISP_GETREG8(data->reg);
			break;
		case 16:
			data->val = ISP_GETREG16(data->reg);
			break;
		case 32:
			data->val = ISP_GETREG32(data->reg);
			break;
		default:
			data->val = 0xffffffff;
			cam_err("%s wrong isp reg bits length = %d,set val to 0xffffffff",__func__,data->val_bits);
			return -1;
			break;
	}
	cam_debug("reg = 0x%x bits = %d val = 0x%x",data->reg,data->val_bits,data->val);
	// TODO support mask read
	return 0;
}

static int ovisp23_write_reg(struct isp_cfg_reg *data)
{
	cam_debug("reg = 0x%x bits = %d val = 0x%x",data->reg,data->val_bits,data->val);
	switch(data->val_bits)
	{
		case 8:
			ISP_SETREG8(data->reg,data->val);
			break;
		case 16:
			ISP_SETREG16(data->reg,data->val);
			break;
		case 32:
			ISP_SETREG32(data->reg,data->val);
			break;
		default:
			data->val = 0xffffffff;
			cam_err("%s wrong isp reg bits length = %d,set val to 0xffffffff",__func__,data->val_bits);
			return -1;
			break;
	}
	// TODO support mask write
	return 0;
}

static int ovisp23_read_reg_setting(struct isp_cfg_reg_array *data)
{
	int ret = 0;
	uint32_t data_length = sizeof(struct isp_cfg_reg)*data->length;
	uint32_t i;
	struct isp_cfg_reg *settings = NULL;

	cam_debug("ovisp read reg array:%d", data->length);

	settings = (struct isp_cfg_reg *)kzalloc(data_length, GFP_KERNEL);

	if(settings == NULL)
	{
		cam_err("allocate setting memory fail %s", __func__);
		return -ENOMEM;
	}
	if(copy_from_user((void *)settings, (void __user *) data->reg_array, data_length)){
		cam_err("%s copy_from_user error.", __func__);
		ret = -EFAULT;
		goto out;
	}

	if(data->length == 0){
		cam_info("setting length is zero");
		ret = -1;
		goto out;
	}

	for(i=0;i<data->length;i++){

		switch(settings[i].val_bits)
		{
			case 8:
				settings[i].val = ISP_GETREG8(settings[i].reg);
				break;
			case 16:
				settings[i].val = ISP_GETREG16(settings[i].reg);
				break;
			case 32:
				settings[i].val = ISP_GETREG32(settings[i].reg);
				break;
			default:
				settings[i].val = 0xffffffff;
				cam_err("%s wrong isp reg bits length = %d,set val to 0xffffffff",__func__,settings[i].val_bits);
				break;
		}
		// TODO support mask read
	}

	if (copy_to_user((void __user *)data->reg_array,
		settings, data_length)) {
		cam_err("%s copy_to_user error.\n", __func__);
		ret = -EFAULT;
		goto out;
	}
out:
	kfree(settings);
	return ret;
}

static int ovisp23_write_reg_setting(struct isp_cfg_reg_array *data)
{
	int ret = 0;
	uint32_t data_length = sizeof(struct isp_cfg_reg)*data->length;
       uint32_t i;
	 uint32_t temp =0;
	struct isp_cfg_reg *settings = NULL;

	cam_debug("ovisp write reg array:%d", data->length);

	settings = (struct isp_cfg_reg *)kzalloc(data_length, GFP_KERNEL);

	if(settings == NULL)
	{
		cam_err("allocate setting memory fail %s", __func__);
		return -ENOMEM;
	}
	if(copy_from_user((void *)settings, (void __user *) data->reg_array, data_length)){
		cam_err("%s copy_from_user error.", __func__);
		ret = -EFAULT;
		goto out;
	}

	if(data->length == 0){
		cam_info("setting length is zero");
		ret = -1;
		goto out;
	}

	for(i=0;i<data->length;i++){

		switch(settings[i].val_bits)
		{
			case 8:
				if(settings[i].mask!=0){
					temp = ISP_GETREG8(settings[i].reg)&settings[i].mask;
					ISP_SETREG8(settings[i].reg,(settings[i].val|temp));
				}else
					ISP_SETREG8(settings[i].reg,settings[i].val);
				break;
			case 16:
				if(settings[i].mask!=0){
					temp = ISP_GETREG16(settings[i].reg);
					temp = temp&settings[i].mask;
					ISP_SETREG16(settings[i].reg,(settings[i].val|temp));
				}else
					ISP_SETREG16(settings[i].reg,settings[i].val);
				break;
			case 32:
				if(settings[i].mask!=0){
					temp = ISP_GETREG32(settings[i].reg);
					temp = temp&settings[i].mask;
					ISP_SETREG32(settings[i].reg,(settings[i].val|temp));
				}else
					ISP_SETREG32(settings[i].reg,settings[i].val);
				break;
			default:
				settings[i].val = 0xffffffff;
				cam_err("%s wrong isp reg bits length = %d,set val to 0xffffffff",__func__,settings[i].val_bits);
				break;
		}
		// TODO support mask read
	}

out:
	kfree(settings);
	return ret;
}

static int ovisp23_config(hwisp_intf_t* i,void* cfg)
{
	int ret = 0;
	ovisp23_t* ov = NULL;
	struct isp_cfg_data *pcfg = NULL;

	pcfg = (struct isp_cfg_data *)cfg;
	ov = I2OV(i);

	switch(pcfg->cfgtype){
		case CONFIG_POWER_ON:
			ret = ovisp23_power_on(i);
			break;
		case CONFIG_POWER_OFF:
			ret = ovisp23_power_off(i);
			break;
		case CONFIG_READ_REG:
			ret= ovisp23_read_reg(&pcfg->reg_s.reg);
			break;
		case CONFIG_WRITE_REG:
			ret= ovisp23_write_reg(&pcfg->reg_s.reg);
			break;
		case CONFIG_READ_REG_SETTINGS:
			ret= ovisp23_read_reg_setting(&pcfg->reg_s.reg_settings);
			break;
		case CONFIG_WRITE_REG_SETTINGS:
			ret= ovisp23_write_reg_setting(&pcfg->reg_s.reg_settings);
			break;
		case CONFIG_BUFFER_TO_ISP:
           	ret = isp_cmd_update_buffer_cmd(pcfg->data);
		    	break;
		case CONFIG_REPROCESS_CMD:
			ret = isp_reprocess_cmdset(&pcfg->reg_s.reprocess_params);
			break;
		default:
			break;
	}
    return ret;
}


#define PIPELINE(id) (id)
void ovisp23_notify_sof( uint32_t id)
{
    hwisp_event_t isp_ev;
    isp_ev.kind = HWISP_SOF;
    isp_ev.data.sof.pipeline = PIPELINE(id);
    hwisp_notify_intf_sof(s_ovisp23.notify,&isp_ev);

    trace_hw_ovisp23_event_sof(id); 
}

void ovisp23_notify_eof(uint32_t id)
{
    hwisp_event_t isp_ev;
    isp_ev.kind = HWISP_EOF;
    isp_ev.data.eof.pipeline = PIPELINE(id);
    hwisp_notify_intf_eof(s_ovisp23.notify,&isp_ev);

    trace_hw_ovisp23_event_eof(id); 
}

void ovisp23_notify_cmd_ready(uint32_t cmd, uint32_t result)
{
    hwisp_event_t isp_ev;
    isp_ev.kind = HWISP_READY;
    isp_ev.data.ready.cmd = cmd;
    isp_ev.data.ready.result = result;
    cam_debug("%s cmd = %d result = %d",__func__,cmd,result);
    hwisp_notify_intf_cmd_ready(s_ovisp23.notify,&isp_ev);

    trace_hw_ovisp23_cmd_ready(cmd, result); 
}

static int
ovisp23_record_fixddrfreq(hwisp_intf_t* i, void* pddrfreq)
{
    uint32_t ddrfreq = *((uint32_t*)pddrfreq);
    if(ddrfreq <= 0  || ddrfreq > DDR_BLOCK_PROFILE )
    {
        cam_err("%s isp fix an error ddrfreq(%d)",__func__,ddrfreq);
        return -1;
    }
    k3_isp_update_ddrfreq_up2down(ddrfreq);
    camera_record_fixddrfreq = true;
    return 0;
}
static int
ovisp23_create_stream(
        hwisp_intf_t* i,
        struct video_device* vdev,
        hwisp_stream_info_t* info)
{
	ovisp23_t* ov = I2OV(i);
	return hwisp_create_stream(vdev, i, info, &ov->streams);
}

static int
ovisp23_stream_start(
        hwisp_intf_t* isp_intf,
        hwisp_stream_intf_t* stm_intf)
{
	bool found = false;
	uint32_t attach_port, port;
	ovisp23_t* ov = NULL;
	hwisp_stream_t* stm = I2STM(stm_intf);
	ov = I2OV(isp_intf);

	if (stm->port.id == ISP_PORT_VC0) {
		/* better to use spinlock to iterate list */
		for (port = ISP_PORT_WRITE0; port <= ISP_PORT_WRITE5; port++) {
			list_for_each_entry(stm, &ov->streams, node) {
				if (stm->port.id == port) {
					found  = true;
					break;
				}
			}

			if (found) { break; }
		}
		attach_port = (found) ? port : ISP_PORT_VC0;
		meta_data_ctrl(META_CTRL_ENABLE, attach_port);
	}

	if (stm->port.id <= ISP_PORT_WRITE5) {
		hw_isp_setup_port(stm->port.id);
	}

	cam_debug("%s %d",__func__,stm->port.id);
	return 0;
}

static int
ovisp23_stream_stop(
        hwisp_intf_t* isp_intf,
        hwisp_stream_intf_t* stm_intf)
{
    ovisp23_t* ov = NULL;
    hwisp_stream_t* stm = I2STM(stm_intf);
    ov = I2OV(isp_intf);

	if (stm->port.id == ISP_PORT_VC0) {
		meta_data_ctrl(META_CTRL_DISABLE, ISP_PORT_VC0);
	}

	if(stm->port.id <= ISP_PORT_WRITE5) {
		hw_isp_clear_port(stm->port.id);
	}

    if(camera_record_fixddrfreq)
    {
	    k3_isp_update_ddrfreq_down2up(DDR_BLOCK_PROFILE);
        camera_record_fixddrfreq = false;
    }

	cam_debug("%s %d",__func__,stm->port.id);
	return 0;
}

hwisp_buf_t* ovisp23_get_buf_from_readyq(isp_port_e port)
{
    struct list_head* pos = NULL;
    hwisp_stream_t* stm = NULL;
    hwisp_buf_t* buf = NULL;
    list_for_each(pos, &s_ovisp23.streams) {
        hwisp_stream_intf_t* intf = hwisp_stream_get_by_node(pos);
        if (!intf) {
            continue;
        }
        stm = I2STM(intf);
/*    stm can't be null
        if(!stm)
        {
            cam_err("stm = NULL");
            continue;
        }*/
        if(stm->port.id != port){
            continue;
        }
        /*
           if(port == 0 && buf_count%2 ==1){
           HWCAM_CFG_INFO("no more empty buf in readyq!");
           return NULL;
           }
           if(port == 1 && buf_count%2 ==0){
           return NULL;
           }
           buf_count++;
           */
        //if(port !=0)
        //return NULL;
        buf = hwisp_stream_intf_get_buf(intf);
        if (!buf) {
            HWCAM_CFG_INFO("no more empty buf in readyq for stream[%ld %d]!",stm->stream_type,stm->port.id);
            return NULL;
        }
        buf->info.port.pix_format = stm->port.pix_format;
        buf->info.port.use_phy_memory = stm->port.use_phy_memory;
        return buf;
    }
    cam_err("There is no stream match the port %d",port);
    return NULL;
}


int ovisp23_put_buf_to_doneq(isp_port_e port,hwisp_buf_t* buf)
{
    struct list_head* pos = NULL;
    hwisp_stream_t* stm;
    list_for_each(pos, &s_ovisp23.streams) {
        hwisp_stream_intf_t* intf = hwisp_stream_get_by_node(pos);
        if (!intf) {
            continue;
        }

        stm = I2STM(intf);
/*	stm can't be null
        if(!stm)
        {
            cam_err("stm = NULL");
            continue;
        }*/
        if(stm->port.id != port){
            continue;
        }
        if (buf) {
            hwisp_stream_intf_buf_done(intf, buf);
        return 0;
        }
    }
    return 0;
}

int ovisp23_put_buf_to_idelq(isp_port_e port,hwisp_buf_t* buf)
{
    struct list_head* pos = NULL;
    hwisp_stream_t* stm;
    list_for_each(pos, &s_ovisp23.streams) {
        hwisp_stream_intf_t* intf = hwisp_stream_get_by_node(pos);
        if (!intf) {
            continue;
        }
        stm = I2STM(intf);
/*	stm can't be null
        if(!stm)
        {
            cam_err("stm = NULL");
            continue;
        }*/
        if(stm->port.id != port){
            continue;
        }
        if (buf) {
            hwisp_stream_intf_put_buf(intf, buf);
            cam_debug("%s buf phyadd = 0x%x",__func__,buf->info.y_addr_phy);
            return 0;
        }
    }
    return 0;
}

hwisp_stream_t* ovisp23_get_stream(isp_port_e port)
{
    struct list_head* pos = NULL;
    hwisp_stream_t* stm = NULL;
	bool found = false;

    list_for_each(pos, &s_ovisp23.streams) {
        stm = container_of(pos, hwisp_stream_t, node);
		if (stm->port.id == port) {
			found  = true;
			break;
		}
    }

    return (found ? stm : NULL);
}

static int ovisp23_suspend(struct platform_device *pdev, pm_message_t state)
{
	int rc = 0;
	ovisp23_t *ov = &s_ovisp23;

	cam_notice("%s +",__func__);

	if (ov->power_on_state) {
		rc = hw_isp_poweroff();
		k3_isp_release_ddrfreq();
	}

	cam_notice("%s -",__func__);
	return rc;
}


static int ovisp23_resume(struct platform_device *pdev)
{
	int rc = 0;
	ovisp23_t *ov = &s_ovisp23;

	cam_notice("%s +",__func__);

	if (ov->power_on_state) {
		k3_isp_fix_ddrfreq(DDR_BLOCK_PROFILE);
		rc = hw_isp_poweron();
	}

	cam_notice("%s -",__func__);
	return rc;
}
MODULE_DEVICE_TABLE(of, s_ovisp23_dt_match);

static struct platform_driver
s_ovisp23_driver =
{
	.suspend = ovisp23_suspend,
	.resume = ovisp23_resume,
	.driver =
    {
		.name = "huawei,huawei_isp",
		.owner = THIS_MODULE,
		.of_match_table = s_ovisp23_dt_match,
	},
};


static ssize_t ovisp23_debug_show(struct device *dev,
				struct device_attribute *attr, char *buf);
static ssize_t ovisp23_debug_store(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count);
static DEVICE_ATTR(ovisp23_debug, 0644, ovisp23_debug_show, ovisp23_debug_store);

static ssize_t ovisp23_debug_show(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	int ret;

	cam_info("%s - enter", __func__);
	ret = snprintf(buf, PAGE_SIZE, "isp_debug_flag=0x%x\n", isp_debug_flag);
	return ret;
}

static ssize_t ovisp23_debug_store(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
	cam_info("%s - enter", __func__);
	isp_debug_flag = simple_strtoul(buf, NULL, 0);
	return count;
}


static int32_t
ovisp23_platform_probe(
        struct platform_device* pdev)
{
	int32_t ret;
	INIT_LIST_HEAD(&s_ovisp23.streams);
	ret = hwisp_register(pdev,&s_ovisp23.intf, &s_ovisp23.notify);

	s_ovisp23.pdev = pdev;
	s_ovisp23.power_on_state = false;
	ret |= hw_alloc_firmware_memory();

	client_ovisp23 = dsm_register_client(&dev_ovisp23);

	ret |= meta_data_buf_prepare(&pdev->dev);
	ret |= device_create_file(&pdev->dev, &dev_attr_ovisp23_debug);
	return ret;
}

static int __init
ovisp23_init_module(void)
{
    return platform_driver_probe(&s_ovisp23_driver,
            ovisp23_platform_probe);
}

static void __exit
ovisp23_exit_module(void)
{
    hw_free_firmware_memory();
    hwisp_unregister(&s_ovisp23.intf);
    platform_driver_unregister(&s_ovisp23_driver);
}

module_init(ovisp23_init_module);
module_exit(ovisp23_exit_module);
MODULE_DESCRIPTION("ovisp23");
MODULE_LICENSE("GPL v2");

