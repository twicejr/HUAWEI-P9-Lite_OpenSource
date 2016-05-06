#include <linux/module.h>
#include <linux/init.h>
#include <linux/hisi/hi6xxx-boardid.h>

extern int camera_init(void);
extern void camera_exit(void);

extern int mini_isp_camera_init(void);
extern void mini_isp_camera_exit(void);

DEFINE_SPINLOCK(io_lock);
static int video_nr = -1;
//static int chip_id = 0;

static int __init camera_module_init(void)
{
    int    ret = 0;
#if 0
    u32 val;

    if(get_hw_config_int("camera/miniisp", &val, NULL) == true){
       if(val == 1){
#if defined(CONFIG_CAMERA_MINI_ISP)
           	ret = mini_isp_camera_init();
#endif
       }
    }
    else{
        ret = camera_init();
    }
#else
    ret = camera_init();
#endif
    return ret;
}

static void __exit camera_module_exit(void)
{
#if 0
    u32 val;
    if(get_hw_config_int("camera/miniisp", &val, NULL) == true){
       if(val == 1){
#if defined(CONFIG_CAMERA_MINI_ISP)
           	mini_isp_camera_exit();
#endif
       }
    }
    else{
        camera_exit();
    }
#else
    camera_exit();
#endif
}

module_init(camera_module_init);
module_exit(camera_module_exit);
module_param(video_nr, int, 0444);

MODULE_AUTHOR("HISILICON");
MODULE_DESCRIPTION("V4L2 capture driver for K3 based cameras");
MODULE_LICENSE("GPL");
MODULE_SUPPORTED_DEVICE("video");

