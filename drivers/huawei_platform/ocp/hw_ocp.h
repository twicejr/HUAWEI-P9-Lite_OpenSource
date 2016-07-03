

#ifndef HW_OCP_H
#define HW_OCP_H
#include <linux/mutex.h>
#include <linux/ioctl.h>
#include <linux/err.h>

struct hw_ocp_info {
	unsigned int num;
	unsigned int ocp_support;
	unsigned int lcd_single_ldo4;
	struct notifier_block lcd_nb;
};

struct hw_ocp_conf {
	const char *power_name;
	const char *device_name;
	unsigned int power_support;
};

struct hw_ocp_attr
{
    char *name;
    int (*handler) (char *name);
};

#define DTS_COMP_OCP	"huawei,ocp-config"
#define LCD_OCP_TIME_MS	1500

#define SUPPLY_LCD       "ldo4"
#define SUPPLY_TP       "ldo17"

#define SIZEOF_ARRAY(array) (sizeof((array))/sizeof((array)[0]))
#define OCP_COUNT_MAX       5
#define HWLOG_TAG   HW_OCP
HWLOG_REGIST();

#define HW_OCP_LOG_INFO(x...)       _hwlog_info(HWLOG_TAG, ##x)
#define HW_OCP_LOG_ERR(x...)        _hwlog_err(HWLOG_TAG, ##x)
#define HW_OCP_LOG_DEBUG(x...)  _hwlog_debug(HWLOG_TAG, ##x)

/*extern*/
extern int hisi_lcd_ocp_recover(struct notifier_block *nb,
		unsigned long event, void *data);

int hw_ocp_lcd_handler(const char *name);
int hw_ocp_tp_handler(const char *name);
#endif
