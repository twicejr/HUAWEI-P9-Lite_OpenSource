#ifndef _LINUX_PM_QOS_PARAMS_H
#define _LINUX_PM_QOS_PARAMS_H
/* interface for the pm_qos_power infrastructure of the linux kernel.
 *
 * Mark Gross <mgross@linux.intel.com>
 */
#include <linux/plist.h>
#include <linux/notifier.h>
#include <linux/miscdevice.h>

#define PM_QOS_RESERVED 0
#define PM_QOS_CPU_DMA_LATENCY 1
#define PM_QOS_NETWORK_LATENCY 2
#define PM_QOS_NETWORK_THROUGHPUT 3

#define PM_QOS_DDR_MINFREQ          (4)
#define PM_QOS_DDR_MAXFREQ          (5)
#define PM_QOS_ACPU_MINFREQ         (6)
#define PM_QOS_ACPU_MAXFREQ         (7)
#define PM_QOS_GPU_MINFREQ          (8)
#define PM_QOS_GPU_MAXFREQ          (9)

#define PM_QOS_NUM_CLASSES 10

#define PM_QOS_DEFAULT_VALUE -1

#define PM_QOS_CPU_DMA_LAT_DEFAULT_VALUE    (2000 * USEC_PER_SEC)
#define PM_QOS_NETWORK_LAT_DEFAULT_VALUE    (2000 * USEC_PER_SEC)
#define PM_QOS_NETWORK_THROUGHPUT_DEFAULT_VALUE 0

#define PM_QOS_PWRCTRL_DFS_DEFAULT_VALUE    (0)

struct pm_qos_request_list {
    struct plist_node list;
    int pm_qos_class;
};


enum  {
    IPC_QOS = 1,   /*IPC信号量有32票，占用32个投票值, 1-32*/
    I2C_QOS  = 40, /*I2C 0-5, 40-45*/
    MMC_QOS = 50, /*MMC 0-2, 50-52*/
    USB_QOS = 60,
    IDLE_QOS,
};


void pm_qos_add_request(struct pm_qos_request_list *l, int pm_qos_class, s32 value);
void pm_qos_update_request(struct pm_qos_request_list *pm_qos_req,
        s32 new_value);
void pm_qos_remove_request(struct pm_qos_request_list *pm_qos_req);

int pm_qos_request(int pm_qos_class);
int pm_qos_add_notifier(int pm_qos_class, struct notifier_block *notifier);
int pm_qos_remove_notifier(int pm_qos_class, struct notifier_block *notifier);
int pm_qos_request_active(struct pm_qos_request_list *req);

#endif
