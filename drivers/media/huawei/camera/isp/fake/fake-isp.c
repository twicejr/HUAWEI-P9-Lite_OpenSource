


#include <linux/compiler.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/kthread.h>
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

#include "hwisp_intf.h"

typedef struct _tag_fake
{
    hwisp_intf_t                                intf; 

    char const*                                 name; 

	wait_queue_head_t                           wq;
	struct task_struct*                         port;

    struct list_head                            streams; 
} fake_isp_t; 

#define I2F(i) container_of(i, fake_isp_t, intf)

char const* 
fake_isp_get_name(
        hwisp_intf_t* i)
{
    fake_isp_t* fake = NULL; 
    fake = I2F(i); 
    return fake->name; 
}

static int 
fake_isp_power_on(
        hwisp_intf_t* i)
{
    fake_isp_t* fake = NULL; 
    fake = I2F(i); 
    return 0; 
}

static int 
fake_isp_power_off(
        hwisp_intf_t* i)
{
    fake_isp_t* fake = NULL; 
    fake = I2F(i); 
    return 0; 
}

static int 
fake_isp_reset(
        hwisp_intf_t* i)
{
    fake_isp_t* fake = NULL; 
    fake = I2F(i); 
    return 0; 
}

static int 
fake_isp_load_firmware(
        hwisp_intf_t* i)
{
    fake_isp_t* fake = NULL; 
    fake = I2F(i); 
    return 0; 
}

static int 
fake_isp_init_reg(
        hwisp_intf_t* i)
{
    fake_isp_t* fake = NULL; 
    fake = I2F(i); 
    return 0; 
}

static int 
fake_isp_create_stream(
        hwisp_intf_t* i, 
        struct video_device* vdev, 
        hwisp_stream_info_t* info)
{
    fake_isp_t* fake = NULL; 
    fake = I2F(i); 
    HWCAM_CFG_INFO("fake isp create stream. \n"); 
    return hwisp_create_stream(vdev, i, info, &fake->streams); 
}

static int 
fake_isp_thread(
        void *data)
{
	fake_isp_t* fake = (fake_isp_t*)data;

    HWCAM_CFG_INFO("fake isp thread enter. \n"); 

	while (1) {
        int timeout = msecs_to_jiffies(33);
        struct list_head* pos = NULL; 
		if (kthread_should_stop()) {
			break;
        }

        list_for_each(pos, &fake->streams) {
            hwisp_stream_intf_t* stm = NULL;
            hwisp_buf_t* buf = NULL; 

            stm = hwisp_stream_get_by_node(pos);
            if (!stm) {
                continue; 
            }

            buf = hwisp_stream_intf_get_buf(stm); 
            if (buf) {
                hwisp_stream_intf_buf_done(stm, buf); 
            }
            else {
            }
        }

        schedule_timeout_interruptible(timeout);
	}

    HWCAM_CFG_INFO("fake isp thread exit. \n"); 
	return 0;
}

static int 
fake_isp_stream_start(
        hwisp_intf_t* i, 
        hwisp_stream_intf_t* stm)
{
    fake_isp_t* fake = NULL; 
    fake = I2F(i); 
	fake->port = kthread_run(fake_isp_thread, fake, "hwcam fake isp");
    return 0; 
}

static int 
fake_isp_stream_stop(
        hwisp_intf_t* i, 
        hwisp_stream_intf_t* stm)
{
    fake_isp_t* fake = NULL; 
    fake = I2F(i); 
	if (fake->port) {
		kthread_stop(fake->port);
		fake->port = NULL;
	}
    return 0; 
}

static hwisp_vtbl_t
s_vtbl_fake = 
{
    .get_name = fake_isp_get_name, 
    .power_on = fake_isp_power_on, 
    .power_off = fake_isp_power_off, 
    .reset = fake_isp_reset, 
    .load_firmware = fake_isp_load_firmware, 
    .init_reg = fake_isp_init_reg, 
    .create_stream = fake_isp_create_stream, 
    .stream_start = fake_isp_stream_start, 
    .stream_stop = fake_isp_stream_stop, 
}; 

static fake_isp_t 
s_fake = 
{
    .intf = { .vtbl = &s_vtbl_fake, }, 
}; 

static const struct of_device_id 
s_fake_isp_dt_match[] = 
{
	{
        .compatible = "huawei,fake-isp", 
        .data = &s_fake.intf, 
    },
	{
    }, 
};

MODULE_DEVICE_TABLE(of, s_fake_isp_dt_match);

static struct platform_driver 
s_fake_isp_driver = 
{
	.driver = 
    {
		.name = "huawei,fake-isp",
		.owner = THIS_MODULE,
		.of_match_table = s_fake_isp_dt_match,
	},
};

static int32_t 
fake_isp_platform_probe(
        struct platform_device* pdev)
{
    int32_t ret = -1; 
    fake_isp_t* fake = (fake_isp_t*)kzalloc(sizeof(fake_isp_t), GFP_KERNEL); 

    if (!fake) {
        return -ENOMEM; 
    }
    fake->intf.vtbl = &s_vtbl_fake; 

	init_waitqueue_head(&fake->wq);
    fake->port = NULL; 
    fake->name = "fake-isp"; 
    INIT_LIST_HEAD(&fake->streams); 

    ret = hwisp_register(pdev, &fake->intf); 
    if (ret < 0) {
        kfree(fake); 
    }
    return ret; 
}

static int __init 
fake_isp_init_module(void)
{
    return platform_driver_probe(&s_fake_isp_driver, 
            fake_isp_platform_probe);
}

static void __exit 
fake_isp_exit_module(void)
{
    platform_driver_unregister(&s_fake_isp_driver);
}

module_init(fake_isp_init_module);
module_exit(fake_isp_exit_module);
MODULE_DESCRIPTION("hwcam fake isp");
MODULE_LICENSE("GPL v2");

