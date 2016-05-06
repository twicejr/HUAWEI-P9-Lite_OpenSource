

#ifndef _LINUX_CYTTSP5_HW_H
#define _LINUX_CYTTSP5_HW_H

#include <huawei_platform/log/hw_log.h>
#include <linux/regulator/consumer.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/seq_file.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/debugfs.h>
#include <linux/platform_device.h>
#include <linux/proc_fs.h>

#define PHONE_NAME_ALICE    "Alice"
#define CY_DATA_HEAD_LEN      10
#define CY_READ_CMD_MAX_LEN   128
#define CY_READ_DATA_LEN      100
#define CYTTSP5_GET_OPENS     1
#define CYTTSP5_DATA_ONE_BYTE 1
#define CYTTSP5_DATA_TWO_BYTE 2
#define CY_MAX_RAW_DATA_LEN   1024
#define CHECK_RETRY_TIMES     3
#define RAW_DATA_SIZE (PAGE_SIZE * 32)

#define HWLOG_TAG    TS
HWLOG_REGIST();
#define TS_LOG_INFO(x...)        _hwlog_info(HWLOG_TAG, ##x)
#define TS_LOG_ERR(x...)        _hwlog_err(HWLOG_TAG, ##x)
#define TS_LOG_DEBUG(x...)    \
do { \
    if (g_ts_log_level)    \
        _hwlog_info(HWLOG_TAG, ##x);    \
}while(0)


/* external varible*/
extern u8 g_ts_log_level;

#define CYTTSP5_FW_FROM_SD_NAME "/sdcard/cyttsp5_fw.bin"
#define HW_MMI_TEST_TIMES           4


#define RETRY_OR_EXIT(retry_cnt, retry_label, exit_label) \
do { \
    if (retry_cnt) \
        goto retry_label; \
    goto exit_label; \
} while (0)


/*idac:3 ,  localPWC:2 ,  opens:7
  mutual rawdata:3 ,  self rawdata:3
  self localPWC:5 ,  mmi test times:4
*/
#define MMI_TEST_IDAC_NUM           3
#define MMI_TEST_LOCALPWC_NUM       2
#define MMI_TEST_OPENS_NUM          7
#define MMI_TEST_MUT_RAEDATA_NUM    3
#define MMI_TEST_SELF_RAEDATA_NUM   3
#define MMI_TEST_SELF_LOCALPWC_NUM  5
    
#define MMI_TEST_LIMIT_NUM   ((MMI_TEST_IDAC_NUM +\
                                   MMI_TEST_LOCALPWC_NUM +\
                                   MMI_TEST_OPENS_NUM +\
                                   MMI_TEST_MUT_RAEDATA_NUM  + \
                                   MMI_TEST_SELF_RAEDATA_NUM + \
                                   MMI_TEST_SELF_LOCALPWC_NUM)*HW_MMI_TEST_TIMES)

#define CSV_TX_NUM    36
#define CSV_RX_NUM    24

#define  STRUCT_NAME_LEN  30

#define TX_MUL_RX_NUM    (CSV_TX_NUM*CSV_RX_NUM) 
#define TX_ADD_RX_NUM    (CSV_TX_NUM+CSV_RX_NUM) 


struct cyttsp5_sensor_opens{
    int min[TX_MUL_RX_NUM];
    int ebye_rx[TX_MUL_RX_NUM];
    int ebye_rx_allowed_max;
    int ebye_rx_allowed_max_num;
    int ebye_tx[TX_MUL_RX_NUM];
    int ebye_tx_allowed_max;
    int ebye_tx_allowed_max_num;
};

struct cyttsp5_sensor_idac{
    int max[CSV_TX_NUM];
    int min[CSV_TX_NUM];
    int delta[CSV_TX_NUM];
};

struct cyttsp5_sensor_localPWC{
    int max[TX_MUL_RX_NUM];
    int min[TX_MUL_RX_NUM];
};

struct cyttsp5_sensor_mutual_noise {
    int max[TX_MUL_RX_NUM];
};

struct cyttsp5_sensor_mutual_rawdata{
    int max[TX_MUL_RX_NUM];
    int min[TX_MUL_RX_NUM];
};


struct cyttsp5_sensor_self_noise {
    int max[TX_ADD_RX_NUM];
};

struct cyttsp5_sensor_self_rawdata {
    int max[TX_ADD_RX_NUM];
    int min[TX_ADD_RX_NUM];
};

struct cyttsp5_sensor_selflocalPWC {
    int self_gidac_max_rx;
    int self_gidac_max_tx;
    int self_gidac_min_rx;
    int self_gidac_min_tx;
    int max[TX_ADD_RX_NUM];
    int min[TX_ADD_RX_NUM];
    int delta[TX_ADD_RX_NUM];
};


struct cyttsp5_sensor_info_limit {
    int tx_num;
    int rx_num;
    struct cyttsp5_sensor_opens opens;
    struct cyttsp5_sensor_idac idac;
    struct cyttsp5_sensor_localPWC localPWC;
    struct cyttsp5_sensor_mutual_noise mutual_noise;
    struct cyttsp5_sensor_mutual_rawdata mutual_rawdata;
    struct cyttsp5_sensor_self_noise self_noise;
    struct cyttsp5_sensor_self_rawdata self_rawdata;
    struct cyttsp5_sensor_selflocalPWC selflocalPWC;
};

struct cyttsp5_power_control {
    int irq_gpio;
    int reset_gpio;
    int irq_config;     // 0 - LOW LEVEL  1 - HIGH LEVEL  2 - RAISE EDGE  3 - FALL EDGE
    int vci_power_type; // 0 - gpio control  1 - regulator  2 - boost & gpio
    int vci_gpio_ctrl;
    int vci_boost_ctrl;
    int vddio_power_type;// 0 - gpio control  1 - regulator
    int vddio_gpio_ctrl;
    struct regulator *vci;
    struct regulator *vddio;
};


enum cyttsp5_sensor_check {
    CYTTSP_I2C_PING = 0,
    CYTTSP_MUTUAL_RAWDATA,
    CYTTSP_GLOBAL_IDAC,
    CYTTSP_MUTUAL_LOCALPWC,
    CYTTSP_OPENS_DATA,
    CYTTSP_SELF_LOCALPWC,
    CYTTSP_SELF_RAWDATA,
    CYTTSP_SHORT_INFO,
    CYTTSP_MUTUAL_BASELINE,
    CYTTSP_SELF_BASELINE,
    CYTTSP_MUTUAL_DIFF,
    CYTTSP_SELF_DIFF,
    CYTTSP_MUTUAL_NOISE,
    CYTTSP_SELF_NOISE,
    CYTTSP_SYSTEM_INFO,
    CYTTSP_CHECK_MAX,
};

struct cyttsp5_check_func_ {
    int index;
    int (* func)(struct device *dev);
};

#define CYPRESS_VCI_POWER_TYPE          "vci_power_type"
#define CYPRESS_VCI_ENABLE              "vci_gpio_enable"
#define CYPRESS_VCI_REGULATOR         "cypress_vci"
#define CYPRESS_VCI_BOOST_ENABLE      "vci_boost_enable"

#define CYPRESS_VDDIO_POWER_TYPE      "vddio_power_type"
#define CYPRESS_VDDIO_GPIO_ENABLE      "vddio_gpio_enable"
#define CYPRESS_VDDIO_REGULATOR       "cypress_vddio"

#define CYPRESS_IRQ_GPIO              "attn_gpio"
#define CYPRESS_RST_GPIO              "reset_gpio"
#define CYPRESS_IRQ_CFG               "irq_config"

#define CYPRESS_MMI_READ_LEN          "cy,i2c_read_length"


#define GPIO_IS_VALID(gpio_num,exit_label) \
do { \
    if (!gpio_is_valid(gpio_num)){ \
        TS_LOG_ERR("gpio is not valid,gpio = %d,line = %d\n",gpio_num,__LINE__);\
        goto exit_label; \
    }\
} while (0)

#define OF_READ_ERROR(retval,exit_label) \
do { \
    if (retval){ \
        TS_LOG_ERR("%s,Of get value is failed,line = %d.\n",__func__,__LINE__);\
        retval = -EINVAL;\
        goto exit_label; \
    }\
} while (0)

#define ERROR_AND_EXIT(retval,exit_label) \
do { \
    if (retval < 0){ \
        TS_LOG_ERR("%s, error occur here, line= %d.\n",__func__,__LINE__);\
        goto exit_label; \
    }\
} while (0)

enum cyttsp5_vci_power_typr{
    VCI_GPIO_CTRL_MODE = 0,
    VCI_LDO_CTRL_MODE,
    VCI_BOOST_CTRL_MODE,
};

enum cyttsp5_vddio_power_typr{
    VDDIO_GPIO_CTRL_MODE = 0,
    VDDIO_LDO_CTRL_MODE,
};

enum cyttsp5_product_module_name {
    FW_OFILM = 0,
    FW_EELY = 1,
    FW_TRULY = 2,
    FW_GIS = 4,
    FW_JUNDA = 5,
    FW_LENSONE = 6,
    FW_YASSY = 7,

    UNKNOW_PRODUCT_MODULE = 0xff,
};

enum tp_state{
	TS_UNINIT = 0,
	TS_WORK,
	TS_STATE_UNDEFINE = 255,
};

struct cyttsp5_tp_info {
    u8 *product_name;
    u8 panel_id;
    u8 *module_name;
};
struct kobject* tp_get_virtual_key_obj(char *name);

int cyttsp5_ic_parse_input(struct device *dev, const char *buf,
        size_t buf_size, u8 *ic_buf, size_t ic_buf_size);

void cyttsp5_procfs_create(void);
int cyttsp5_check_items(struct device *dev,enum 
        cyttsp5_sensor_check item, bool reset,int *data_buf);
int cyttsp5_send_command(struct device *dev,char *buf);
int cyttsp5_command_response(struct device *dev,u8 *buf);
u8 cyttsp5_command_status(struct device *dev);
extern struct device *gdev;
extern struct cyttsp5_core_commands *gcmd;
int cyttsp5_get_mmi_test_limit(struct device_node *node);

#endif /* _LINUX_CYTTSP5_HW_H */
