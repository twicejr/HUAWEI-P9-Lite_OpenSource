#include <linux/kthread.h>
#include <linux/sched/rt.h>
#include <linux/random.h>
#include <huawei_platform/log/hw_log.h>
#include <dsm/dsm_pub.h>

#define HWLOG_TAG    DSM_RECOVERY
HWLOG_REGIST();

#define DSM_LOG_INFO(x...)      _hwlog_info(HWLOG_TAG, ##x)
#define DSM_LOG_ERR(x...)       _hwlog_err(HWLOG_TAG, ##x)
#define DSM_LOG_DEBUG(x...)     _hwlog_debug(HWLOG_TAG, ##x)

struct dsm_dev dsm_recovery = {
    .name = "dsm_recovery",
    .device_name = NULL,
    .ic_name = NULL,
    .module_name = NULL,
    .fops = NULL,
    .buff_size = 1024,
};

struct dsm_client *recovery_client = NULL;

static int __init dsm_recovery_init(void)
{
    if (!recovery_client) {
        recovery_client = dsm_register_client(&dsm_recovery);
    }
    if(!recovery_client){
        DSM_LOG_ERR("recovery_client reg failed\n");
    }
    return 0;
}
module_init(dsm_recovery_init);
