

#ifndef LINUX_SPI_FINGERPRINT_H
#define LINUX_SPI_FINGERPRINT_H

#include <huawei_platform/log/hw_log.h>

#define EVENT_HOLD	28
#define EVENT_CLICK		174
#define EVENT_DCLICK	111
#define EVENT_UP	103
#define EVENT_DOWN	108
#define EVENT_LEFT	105
#define EVENT_RIGHT	106

//NAVIGATION_ADJUST_NOREVERSE: 默认值，适配后置指纹模组
#define NAVIGATION_ADJUST_NOREVERSE 0
//NAVIGATION_ADJUST_NOREVERSE: 适配前置指纹模组
#define NAVIGATION_ADJUST_REVERSE 1
#define NAVIGATION_ADJUST_NOTURN 0
#define NAVIGATION_ADJUST_TURN90 90
#define NAVIGATION_ADJUST_TURN180 180
#define NAVIGATION_ADJUST_TURN270 270

#define FPC_TTW_HOLD_TIME 1000
#define FP_DEV_NAME      "fingerprint"
#define FP_CLASS_NAME   "fpsensor"
#define FP_IOC_MAGIC     'f'  //define magic number


//define commands
#define  FP_IOC_CMD_ENABLE_IRQ	      _IO(FP_IOC_MAGIC, 1)
#define  FP_IOC_CMD_DISABLE_IRQ	      _IO(FP_IOC_MAGIC, 2)
#define  FP_IOC_CMD_SEND_UEVENT	      _IO(FP_IOC_MAGIC, 3)
#define  FP_IOC_CMD_GET_IRQ_STATUS     _IO(FP_IOC_MAGIC, 4)
#define  FP_IOC_CMD_SET_WAKELOCK_STATUS  _IO(FP_IOC_MAGIC, 5)
#define  FP_IOC_CMD_SEND_SENSORID      _IO(FP_IOC_MAGIC, 6)

enum module_vendor_info
{
    MODULEID_LOW = 0,
    MODULEID_HIGT,
    MODULEID_FLOATING,
};

struct fp_data
{
    struct device* dev;
    struct spi_device* spi;
    struct cdev     cdev;
    struct class*    class;
    struct device*   device;
    dev_t             devno;
    struct platform_device* pf_dev;
    unsigned long finger_num;
    struct wake_lock ttw_wl;
    int irq_gpio;
    int cs0_gpio;
    int cs1_gpio;
    int rst_gpio;
    int moduleID_gpio;
    int module_vendor_info;
    int navigation_adjust1;
    int navigation_adjust2;
    struct input_dev* input_dev;
    int irq_num;
    int qup_id;
    char idev_name[32];
    int event_type;
    int event_code;
    struct mutex lock;
    bool prepared;
    bool wakeup_enabled;
    bool read_image_flag;
    unsigned int sensor_id;
    struct pinctrl* pctrl;
    struct pinctrl_state* pins_default;
    struct pinctrl_state* pins_idle;
};

#ifdef CONFIG_LLT_TEST
struct LLT_fingprint_ops {
    ssize_t (*irq_get)(struct device* device, struct device_attribute* attribute, char* buffer);
    irqreturn_t (*fingerprint_irq_handler) (int irq, void* handle);
    int (*fingerprint_request_named_gpio)(struct fp_data* fingerprint, const char* label, int* gpio);
    int (*fingerprint_open)(struct inode* inode, struct file* file);
    int (*fingerprint_get_irq_status)(struct fp_data* fingerprint );
    long (*fingerprint_ioctl)(struct file* file, unsigned int cmd, unsigned long arg);
    int (*fingerprint_reset_gpio_init)(struct fp_data* fingerprint);
    int (*finerprint_get_module_info)(struct fp_data* fingerprint);
    int (*fingerprint_probe)(struct spi_device* spi);
    int (*fingerprint_remove)(struct spi_device* spi);
};
extern struct LLT_fingprint_ops LLT_fingerprint;
#endif

#endif

