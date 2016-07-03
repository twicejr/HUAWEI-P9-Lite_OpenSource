/*
 * hisi_sim_hotplug.c - SIM HOTPLUG driver
 *
 * Copyright (C) 2012 huawei Ltd.
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file "COPYING" in the main directory of this
 * archive for more details.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <linux/module.h>
#include <linux/string.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/io.h>
#include <linux/clk.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/mutex.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/err.h>
#include <linux/of_irq.h>
#include <linux/of_gpio.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/interrupt.h>
#include "hisi_sim_hotplug.h"
#include <linux/wakelock.h>
#include <linux/hisi/hw_cmdline_parse.h> /*for runmode_is_factory*/


#define TAG                     "[SIM_HOTPLUG]"
#define LOGI(fmt, ...)          printk(KERN_INFO TAG" "fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...)          printk(KERN_ERR TAG" "fmt, ##__VA_ARGS__)


enum sim_func_select_state
{
    NOT_USE_MULTI_FUNC      = 0,
    USE_MULTI_FUNC          = 1,
    SELECT_STATE_OTHER      = 2,
};

// DET PIN normal close or normal open, NORMAL means card tray not insert.
enum sim_det_normal_direction
{
    NORMAL_CLOSE    = 0,
    NORMAL_OPEN     = 1,
    NORMAL_BUTT     = 2,
};

enum sim_card_tray_style
{
    SINGLE_CARD_IN_ONE_TRAY = 0,
    TWO_CARDS_IN_ONE_TRAY   = 1,
    CARD_TRAY_BUTT          = 2,
};

static const char *work_name[] =
{
    "sim0_debounce_check",
    "sim1_debounce_check"
};

struct hisi_sim_hotplug_info
{
    void __iomem *iomg_base;

    struct workqueue_struct *sim_hotplug_hpd_wq;
    struct workqueue_struct *sim_hotplug_det_wq;
    struct workqueue_struct *sim_debounce_delay_wq;
#ifdef SUPPORT_MULTI_FUNC
    struct pinctrl          *pctrl;
    struct pinctrl_state    *sim_default_state;
    struct pinctrl_state    *sim_idle_state;
#endif
    struct mutex            sim_hotplug_lock;
    struct wake_lock        sim_hotplug_wklock;
    struct work_struct      sim_hotplug_hpd_work;
    struct work_struct      sim_hotplug_det_work;
    struct delayed_work     sim_debounce_delay_work;

    int     hpd_irq;
    int     det_irq;
    int     det_gpio;
    int     old_det_gpio_level;
    int     det_debounce_checking;  //indicate det debounce is checking or not

    u32     sim_id;
    u32     card_tray_style;
    u32     send_msg_to_cp;
    u32     send_card_out_msg;
    u32     hpd_interrupt_to_close_ldo;
    u32     hpd_debounce_wait_time;
    u32     det_debounce_wait_time;
    u32     det_normal_direction;   // 1 indicats open by default(high level), 0 indicats closed by default
    u32     allocate_gpio;
    u32     shared_det_irq;

    u8      sim_pluged;
    u8      func_sel_state;         // 1 indicates on, 0 indicates off, 2 indicates no gpio set
    u32 pmu_status1_address;
    u32 pmu_irq3_address;
    u32 pmu_irq_mask3_address;
    u32 pmu_sim_ctrl_address;
    u32 pmu_sim_deb_ctrl_address;
    u32 pmu_ldo11_onoff_eco_address;
    u32 pmu_ldo11_vset_address;
    u32 pmu_ldo12_onoff_eco_address;
    u32 pmu_ldo12_vset_address;
    u32 pmu_ldo11_onoff_value;
    u32 pmu_ldo11_vset_value;
    u32 pmu_ldo12_onoff_value;
    u32 pmu_ldo12_vset_value;
};

typedef struct
{
    u32 time;
    u8 sim_no;          //sim_id
    u8 sim_status;      //sim_pluged
    u8 hpd_level;
    u8 det_level;
    u8 trace;
    u8 sim_mux[3];
} sim_log;

struct
{
    u8  sim0_det_normal_direction;
    u8  sim0_pluged;
    u8  sim1_det_normal_direction;
    u8  sim1_pluged;
} sim_plug_state;

#define SIM_HOTPLUG_STATE_UNKNOWN           (0)
#define SIM_HOTPLUG_STATE_IN                (1)
#define SIM_HOTPLUG_STATE_CLEAR             (0)

struct kobject *sim_kobj = NULL;
static int sim0_state = SIM_HOTPLUG_STATE_UNKNOWN;
static int sim1_state = SIM_HOTPLUG_STATE_UNKNOWN;
static int sim2_state = SIM_HOTPLUG_STATE_UNKNOWN;

/*line -emacro(750,*)*/
/*lint -e750*/

#if 0
#define MAX_SIM_HOTPLUG_LOG                 50
#define LOG_SIMHOTPLUG_BUF_LEN              600

//Next lines are hi3650 sim related GPIO Offset
#define USIM0_CLK_IOMG_OFFSET               (0x140)   //GPIO_83
#define USIM0_RST_IOMG_OFFSET               (0x144)   //GPIO_84
#define USIM0_DATA_IOMG_OFFSET              (0x148)   //GPIO_85
#define USIM1_CLK_IOMG_OFFSET               (0x14C)   //GPIO_86
#define USIM1_RST_IOMG_OFFSET               (0x150)   //GPIO_87
#define USIM1_DATA_IOMG_OFFSET              (0x154)   //GPIO_88
#endif

//Next lines are hi6421V500 sim related register address
#define HI6421_IRQ_LDO11_VALUE              (0x00)
#define HI6421_IRQ_LDO12_VALUE              (0x00)

#define SIM_HPD_LEAVE                       (3)

/*lint +e750*/
/*line +emacro(750,*)*/

#define READ_PMU_SIM(addr)          readl_relaxed(hisi_pmurtc_base + (addr << 2))
#define WRITE_PMU_SIM(value,addr)   writel_relaxed(value, hisi_pmurtc_base + (addr << 2))

#define DET_DEBOUNCE_CHECK_WAIT_TIME        (300)   //ms

u8 g_sim_log_idx = 0;


void __iomem *hisi_pmurtc_base = NULL;


/* static funciton declare */
static char* simplug_to_string(u32 plug);
static char* direction_to_string(u32 direction);
static char* func_sel_state_to_string(u32 sel_state);
static char* card_tray_style_to_string(u32 card_tray);

/* funciton implement */

static char* simplug_to_string(u32 plug)
{
    switch (plug)
    {
    case SIM_CARD_OUT:
        return "SIM_CARD_OUT";

    case SIM_CARD_IN:
        return "SIM_CARD_IN";

    default:
        return "SIM_PLUG_ERROR";
    }
}

static char* direction_to_string(u32 direction)
{
    switch (direction)
    {
    case NORMAL_CLOSE:
        return "NORMAL_CLOSE";

    case NORMAL_OPEN:
        return "NORMAL_OPEN";

    case NORMAL_BUTT:
    default:
        return "NORMAL_BUTT";
    }
}

static char* func_sel_state_to_string(u32 sel_state)
{
    switch (sel_state)
    {
    case NOT_USE_MULTI_FUNC:
        return "NOT_USE_MULTI_FUNC";

    case USE_MULTI_FUNC:
        return "USE_MULTI_FUNC";

    case SELECT_STATE_OTHER:
    default:
        return "SELECT_STATE_OTHER";
    }
}

static char* card_tray_style_to_string(u32 card_tray)
{
    switch (card_tray)
    {
    case SINGLE_CARD_IN_ONE_TRAY:
        return "SINGLE_CARD_IN_ONE_TRAY";

    case TWO_CARDS_IN_ONE_TRAY:
        return "TWO_CARDS_IN_ONE_TRAY";

    case CARD_TRAY_BUTT:
    default:
        return "CARD_TRAY_STYLE_UNKNOWN";
    }
}
static void sim_pmu_hpd_read(struct hisi_sim_hotplug_info *info)
{
    u32 pmu_status1         = 0;
    u32 pmu_irq3            = 0;
    u32 pmu_irq_mask3       = 0;
    u32 pmu_sim_ctrl        = 0;
    u32 pmu_sim_deb_ctrl    = 0;
    u32 pmu_ldo11_onoff     = 0;
    u32 pmu_ldo11_vset      = 0;
    u32 pmu_ldo12_onoff     = 0;
    u32 pmu_ldo12_vset      = 0;

    pmu_status1         = READ_PMU_SIM(info->pmu_status1_address);
    pmu_irq3            = READ_PMU_SIM(info->pmu_irq3_address);
    pmu_irq_mask3       = READ_PMU_SIM(info->pmu_irq_mask3_address);
    pmu_sim_ctrl        = READ_PMU_SIM(info->pmu_sim_ctrl_address);
    pmu_sim_deb_ctrl    = READ_PMU_SIM(info->pmu_sim_deb_ctrl_address);
    pmu_ldo11_onoff     = READ_PMU_SIM(info->pmu_ldo11_onoff_eco_address);
    pmu_ldo11_vset      = READ_PMU_SIM(info->pmu_ldo11_vset_address);
    pmu_ldo12_onoff     = READ_PMU_SIM(info->pmu_ldo12_onoff_eco_address);
    pmu_ldo12_vset      = READ_PMU_SIM(info->pmu_ldo12_vset_address);

    LOGI("%s: pmu_status1: 0x%02X, pmu_irq3: 0x%02X, pmu_irq_mask3: 0x%02X, "
            "pmu_sim_ctrl: 0x%02X, pmu_sim_deb_ctrl: 0x%02X\n",
            __func__, pmu_status1, pmu_irq3, pmu_irq_mask3, pmu_sim_ctrl, pmu_sim_deb_ctrl);
    LOGI("%s: pmu_ldo11_onoff: 0x%02X, pmu_ldo11_vset: 0x%02X, "
            "pmu_ldo12_onoff: 0x%02X, pmu_ldo12_vset: 0x%02X\n",
            __func__, pmu_ldo11_onoff, pmu_ldo11_vset, pmu_ldo12_onoff, pmu_ldo12_vset);
}

static void sim_pmu_hpd_write(struct hisi_sim_hotplug_info *info)
{
    if (NULL == info)
    {
        LOGE("%s: end error, info is null.\n", __func__);
        return;
    }

    if (0xFF == info->hpd_interrupt_to_close_ldo || 0x00 == info->hpd_interrupt_to_close_ldo)
    {
        LOGE("%s: end error, hpd_interrupt_to_close_ldo: 0x%02X\n", __func__, info->hpd_interrupt_to_close_ldo);
        return;
    }
    // set close ldo when interrupt happened
    WRITE_PMU_SIM(info->hpd_interrupt_to_close_ldo, info->pmu_sim_ctrl_address);

    // set debounce waiting time
    WRITE_PMU_SIM(info->hpd_debounce_wait_time, info->pmu_sim_deb_ctrl_address);

    // enable PMU, set 1.8v by default
    WRITE_PMU_SIM(info->pmu_ldo11_onoff_value,    info->pmu_ldo11_onoff_eco_address);
    WRITE_PMU_SIM(info->pmu_ldo11_vset_value,      info->pmu_ldo11_vset_address);
    WRITE_PMU_SIM(info->pmu_ldo12_onoff_value,    info->pmu_ldo12_onoff_eco_address);
    WRITE_PMU_SIM(info->pmu_ldo12_vset_value,      info->pmu_ldo12_vset_address);
}

static int sim_read_pmu_dts(struct hisi_sim_hotplug_info *info, struct device_node *np)
{
    int ret                         = 0;
    u32 hpd_interrupt_to_close_ldo  = 0;
    u32 hpd_debounce_wait_time      = 0;
    u32 pmu_status1_address         = 0;
    u32 pmu_irq3_address            = 0;
    u32 pmu_irq_mask3_address       = 0;
    u32 pmu_sim_ctrl_address        = 0;
    u32 pmu_sim_deb_ctrl_address    = 0;
    u32 pmu_ldo11_onoff_eco_address     = 0;
    u32 pmu_ldo11_vset_address      = 0;
    u32 pmu_ldo12_onoff_eco_address     = 0;
    u32 pmu_ldo12_vset_address      = 0;
    u32 pmu_ldo11_onoff_value= 0;
    u32 pmu_ldo11_vset_value= 0;
    u32 pmu_ldo12_onoff_value= 0;
    u32 pmu_ldo12_vset_value= 0;

    ret = of_property_read_u32(np, "hpd_interrupt_to_close_ldo", &hpd_interrupt_to_close_ldo);
    if (ret < 0)
    {
        LOGE("failed to read hpd_interrupt_to_close_ldo.\n");
        return ret;
    }
    info->hpd_interrupt_to_close_ldo = hpd_interrupt_to_close_ldo;

    ret = of_property_read_u32(np, "hpd_debounce_wait_time", &hpd_debounce_wait_time);
    if (ret < 0)
    {
        LOGE("failed to read hpd_debounce_wait_time.\n");
        return ret;
    }
    info->hpd_debounce_wait_time = hpd_debounce_wait_time;//austin should be config to 0x22

    LOGI("%s: hpd_interrupt_to_close_ldo: 0x%02X, hpd_debounce_wait_time: 0x%02X\n",
            __func__, hpd_interrupt_to_close_ldo, hpd_debounce_wait_time);
    ret = of_property_read_u32(np, "pmu_status1_address", &pmu_status1_address);
    if (ret < 0)
    {
        LOGE("failed to read pmu_status1_address.\n");
        return ret;
    }
    info->pmu_status1_address = pmu_status1_address;

    ret = of_property_read_u32(np, "pmu_irq3_address", &pmu_irq3_address);
    if (ret < 0)
    {
        LOGE("failed to read pmu_irq3_address.\n");
        return ret;
    }
    info->pmu_irq3_address = pmu_irq3_address;

    ret = of_property_read_u32(np, "pmu_irq_mask3_address", &pmu_irq_mask3_address);
    if (ret < 0)
    {
        LOGE("failed to read pmu_irq_mask3_address.\n");
        return ret;
    }
    info->pmu_irq_mask3_address = pmu_irq_mask3_address;

    ret = of_property_read_u32(np, "pmu_sim_ctrl_address", &pmu_sim_ctrl_address);
    if (ret < 0)
    {
        LOGE("failed to read pmu_sim_ctrl_address.\n");
        return ret;
    }
    info->pmu_sim_ctrl_address = pmu_sim_ctrl_address;

    ret = of_property_read_u32(np, "pmu_sim_deb_ctrl_address", &pmu_sim_deb_ctrl_address);
    if (ret < 0)
    {
        LOGE("failed to read pmu_sim_deb_ctrl_address.\n");
        return ret;
    }
    info->pmu_sim_deb_ctrl_address = pmu_sim_deb_ctrl_address;

   ret = of_property_read_u32(np, "pmu_ldo11_onoff_eco_address", &pmu_ldo11_onoff_eco_address);
    if (ret < 0)
    {
        LOGE("failed to read pmu_ldo11_onoff_eco_address.\n");
        return ret;
    }
    info->pmu_ldo11_onoff_eco_address = pmu_ldo11_onoff_eco_address;

    ret = of_property_read_u32(np, "pmu_ldo11_vset_address", &pmu_ldo11_vset_address);
    if (ret < 0)
    {
        LOGE("failed to read pmu_ldo11_vset_address.\n");
        return ret;
    }
    info->pmu_ldo11_vset_address = pmu_ldo11_vset_address;

    ret = of_property_read_u32(np, "pmu_ldo12_onoff_eco_address", &pmu_ldo12_onoff_eco_address);
    if (ret < 0)
    {
        LOGE("failed to read pmu_ldo12_onoff_eco_address.\n");
        return ret;
    }
    info->pmu_ldo12_onoff_eco_address = pmu_ldo12_onoff_eco_address;

    ret = of_property_read_u32(np, "pmu_ldo12_vset_address", &pmu_ldo12_vset_address);
    if (ret < 0)
    {
        LOGE("failed to read pmu_ldo12_vset_address.\n");
        return ret;
    }
    info->pmu_ldo12_vset_address = pmu_ldo12_vset_address;

    ret = of_property_read_u32(np, "pmu_ldo11_onoff_value", &pmu_ldo11_onoff_value);
    if (ret < 0)
    {
        LOGE("failed to read pmu_ldo11_onoff_value.\n");
        return ret;
    }
    info->pmu_ldo11_onoff_value = pmu_ldo11_onoff_value;

    ret = of_property_read_u32(np, "pmu_ldo11_vset_value", &pmu_ldo11_vset_value);
    if (ret < 0)
    {
        LOGE("failed to read pmu_ldo11_vset_value.\n");
        return ret;
    }
    info->pmu_ldo11_vset_value = pmu_ldo11_vset_value;

    ret = of_property_read_u32(np, "pmu_ldo12_onoff_value", &pmu_ldo12_onoff_value);
    if (ret < 0)
    {
        LOGE("failed to read pmu_ldo12_onoff_value.\n");
        return ret;
    }
    info->pmu_ldo12_onoff_value = pmu_ldo12_onoff_value;

    ret = of_property_read_u32(np, "pmu_ldo12_vset_value", &pmu_ldo12_vset_value);
    if (ret < 0)
    {
        LOGE("failed to read pmu_ldo12_vset_value.\n");
        return ret;
    }

    info->pmu_ldo12_vset_value = pmu_ldo12_vset_value;

    LOGI("%s: pmu_status1_address: 0x%02X, pmu_irq3_address: 0x%02X, pmu_irq_mask3_address: 0x%02X, "
            "pmu_sim_ctrl_address: 0x%02X, pmu_sim_deb_ctrl_address: 0x%02X\n",
            __func__, pmu_status1_address, pmu_irq3_address, pmu_irq_mask3_address, pmu_sim_ctrl_address, pmu_sim_deb_ctrl_address);
    LOGI("%s: pmu_ldo12_onoff_eco_address: 0x%02X, pmu_ldo11_vset_address: 0x%02X, "
            "pmu_ldo12_onoff_eco_address: 0x%02X, pmu_ldo12_vset_address: 0x%02X\n",
            __func__, pmu_ldo11_onoff_eco_address, pmu_ldo11_vset_address, pmu_ldo12_onoff_eco_address, pmu_ldo12_vset_address);

    LOGI("%s: pmu_ldo11_onoff_value: 0x%02X, pmu_ldo11_vset_value: 0x%02X, "
            "pmu_ldo12_onoff_value: 0x%02X, pmu_ldo12_vset_value: 0x%02X\n",
            __func__, pmu_ldo11_onoff_value, pmu_ldo11_vset_value, pmu_ldo12_onoff_value, pmu_ldo12_vset_value);

    return ret;
}

static int sim_pmu_hpd_init(struct hisi_sim_hotplug_info *info, struct device_node *np)
{
    int ret = -1;
    struct device_node *node = NULL;

    if (hisi_pmurtc_base)
    {
        return 0;
    }

    LOGI("%s: start\n", __func__);

    node = of_find_compatible_node(NULL, NULL, "hisilicon,sim-hotplug0");
    if (!node)
    {
        LOGE("%s: of_find_compatible_node failed.\n", __func__);
        goto err;
    }

    hisi_pmurtc_base = of_iomap(node->parent, 0);
    if (!hisi_pmurtc_base)
    {
        LOGE("%s: of_iomap failed.\n", __func__);
        goto err;
    }
    LOGI("%s: hisi_pmurtc_base: 0x%p\n", __func__, hisi_pmurtc_base);

    sim_read_pmu_dts(info, np);
    sim_pmu_hpd_write(info);
    sim_pmu_hpd_read(info);

    ret = 0;

err:
    LOGI("%s: finished\n", __func__);
    return ret;
}

static ssize_t sim_plug_state_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    LOGI("%s: sim0 det_normal_direction: %s, pluged: %s; "
            "sim1 det_normal_direction: %s, pluged: %s\n",
            __func__,
            direction_to_string(sim_plug_state.sim0_det_normal_direction),
            simplug_to_string(sim_plug_state.sim0_pluged),
            direction_to_string(sim_plug_state.sim1_det_normal_direction),
            simplug_to_string(sim_plug_state.sim1_pluged));

    memcpy(buf, &sim_plug_state, sizeof(sim_plug_state));
    return (ssize_t)sizeof(sim_plug_state);
}

static ssize_t sim0_hotplug_state_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return snprintf(buf, PAGE_SIZE - 1, "%d\n", sim0_state);
}

static ssize_t sim0_hotplug_state_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int val = 0;

    if (kstrtoint(buf, 10, &val))
    {
        LOGE("%s: EINVAL!\n", __func__);
        return -EINVAL;
    }

    LOGI("%s: old sim0_state: %d, val: %d\n", __func__, sim0_state, val);

    sim0_state = val;

    return (ssize_t)count;
}

static ssize_t sim1_hotplug_state_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return snprintf(buf, PAGE_SIZE - 1, "%d\n", sim1_state);
}

static ssize_t sim1_hotplug_state_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int val = 0;

    if (kstrtoint(buf, 10, &val))
    {
        LOGE("%s: EINVAL!\n", __func__);
        return -EINVAL;
    }

    LOGI("%s: old sim1_state: %d, val: %d\n", __func__, sim1_state, val);

    sim1_state = val;

    return (ssize_t)count;
}

static ssize_t sim2_hotplug_state_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return snprintf(buf, PAGE_SIZE - 1, "%d\n", sim2_state);
}

static ssize_t sim2_hotplug_state_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int val = 0;

    if (kstrtoint(buf, 10, &val))
    {
        LOGE("%s: EINVAL!\n", __func__);
        return -EINVAL;
    }

    LOGI("%s: old sim2_state: %d, val: %d\n", __func__, sim2_state, val);

    sim2_state = val;

    return (ssize_t)count;
}

static struct kobj_attribute sim0_attribute =
    __ATTR(sim0_hotplug_state, 0664, sim0_hotplug_state_show, sim0_hotplug_state_store);

static struct kobj_attribute sim1_attribute =
    __ATTR(sim1_hotplug_state, 0664, sim1_hotplug_state_show, sim1_hotplug_state_store);

static struct kobj_attribute sim2_attribute =
    __ATTR(sim2_hotplug_state, 0664, sim2_hotplug_state_show, sim2_hotplug_state_store);

static struct kobj_attribute sim_plug_state_attribute =
    __ATTR(sim_hotplug_state, 0664, sim_plug_state_show, NULL);


static struct attribute *attrs[] =
{
    &sim0_attribute.attr,
    &sim1_attribute.attr,
    &sim2_attribute.attr,
    &sim_plug_state_attribute.attr,
    NULL
};

static struct attribute_group sim_attr_group =
{
    .attrs = attrs
};

static int sys_add_sim_node(void)
{
    int retval;
    LOGI("%s: begin\n", __func__);

    /* wait for kernel_kobj node ready: */
    while (NULL == kernel_kobj)
    {
        msleep(1000);
    }

    /* Create kobject named "sim",located under /sys/kernel/ */
    sim_kobj = kobject_create_and_add("sim", kernel_kobj);
    if (!sim_kobj)
    {
        return -ENOMEM;
    }

    /* Create the files associated with this kobject */
    retval = sysfs_create_group(sim_kobj, &sim_attr_group);
    if (retval)
    {
        kobject_put(sim_kobj);
    }

    LOGI("%s: end, retval: %d\n", __func__, retval);
    return retval;
}

static void update_sim_state_info(int sim_id, int sim_pluged)
{
    if (SIM0 == sim_id)
    {
        if (SIM_CARD_IN == sim_pluged)
        {
            sim0_state = SIM_HOTPLUG_STATE_IN;
        }
        else
        {
            sim0_state = SIM_HOTPLUG_STATE_CLEAR;
        }
    }
    else if (SIM1 == sim_id)
    {
        if (SIM_CARD_IN == sim_pluged)
        {
            sim1_state = SIM_HOTPLUG_STATE_IN;
        }
        else
        {
            sim1_state = SIM_HOTPLUG_STATE_CLEAR;
        }
    }
    else
    {
        LOGE("%s: invalid sim_id: %d\n", __func__, sim_id);
    }
}

static void save_sim_status_log(struct hisi_sim_hotplug_info *info, u32 sim_id, u32 sim_pluged, u32 trace)
{
    struct timeval time;
    sim_log log_temp;
    memset((void *)&log_temp, 0x00, sizeof(log_temp));

    do_gettimeofday(&time);
    log_temp.time = time.tv_sec;
    log_temp.sim_no = sim_id;
    log_temp.sim_status = sim_pluged;
    log_temp.hpd_level = -1;
    log_temp.det_level = gpio_get_value(info->det_gpio);
    log_temp.trace = trace;

    if (SIM0 == info->sim_id)
    {
#if 0
        log_temp.sim_mux[0] = readl(info->iomg_base + USIM0_CLK_IOMG_OFFSET);
        log_temp.sim_mux[1] = readl(info->iomg_base + USIM0_RST_IOMG_OFFSET);
        log_temp.sim_mux[2] = readl(info->iomg_base + USIM0_DATA_IOMG_OFFSET);
#endif
        sim_plug_state.sim0_pluged = (u8)sim_pluged;
    }
    else if (SIM1 == info->sim_id)
    {
#if 0
        log_temp.sim_mux[0] = readl(info->iomg_base + USIM1_CLK_IOMG_OFFSET);
        log_temp.sim_mux[1] = readl(info->iomg_base + USIM1_RST_IOMG_OFFSET);
        log_temp.sim_mux[2] = readl(info->iomg_base + USIM1_DATA_IOMG_OFFSET);
#endif
        sim_plug_state.sim1_pluged = (u8)sim_pluged;
    }
    else
    {
        LOGE("%s: sim%d is err!\n", __func__, info->sim_id);
    }

#if 0
    if (SIM1 == info->sim_id && TWO_CARDS_IN_ONE_TRAY == info->card_tray_style)
    {
        LOGI("%s: sim1, TWO_CARDS_IN_ONE_TRAY, do not add to log history.\n", __func__);
    }
    else
    {
        if (g_sim_log_idx > MAX_SIM_HOTPLUG_LOG - 1)
        {
            g_sim_log_idx = 0;
        }
        ++g_sim_log_idx;
    }
#endif

    LOGI("%s: sim%d, sim_pluged: %s, det_level: %d\n", __func__, sim_id,
            simplug_to_string(sim_pluged), log_temp.det_level);
}

static int sim_set_active(struct hisi_sim_hotplug_info *info)
{
#ifdef SUPPORT_MULTI_FUNC
    int err = 0;

    if (USE_MULTI_FUNC == info->func_sel_state)
    {
        err = pinctrl_select_state(info->pctrl, info->sim_default_state);
        if (err < 0)
        {
            LOGE("set iomux normal error, err: %d\n", err);
            return err;
        }
    }
#endif

    LOGI("%s: sim%d, sim_pluged: %s, set iomux normal state ok!\n",
            __func__, info->sim_id, simplug_to_string(info->sim_pluged));
    return 0;
}

static int sim_set_inactive(struct hisi_sim_hotplug_info *info)
{
#ifdef SUPPORT_MULTI_FUNC
    int err = 0;

    if (USE_MULTI_FUNC == info->func_sel_state)
    {
        err = pinctrl_select_state(info->pctrl, info->sim_idle_state);
        if (err < 0)
        {
            LOGE("set iomux idle error, err: %d\n", err);
            return err;
        }
    }
#endif

    LOGI("%s: sim%d, sim_pluged: %s, set iomux idle state ok!\n",
            __func__, info->sim_id, simplug_to_string(info->sim_pluged));
    return 0;
}

static void hisi_sim_det_msg_to_ccore(struct hisi_sim_hotplug_info *info, u8 sim_pluged)
{
    int det_gpio_level  = 0;
    s32 ret             = 0;
#ifdef CONFIG_HISI_BALONG_MODEM
    u32 channel_id      = 0;
#endif

    if (runmode_is_factory())
    {
        LOGE("%s: runmode is factory, don't support hotplug function, just return.\n", __func__);
        return;
    }

    if (NULL == info)
    {
        LOGE("%s: input param is null, so return.\n", __func__);
        return;
    }

    if (0 == info->send_msg_to_cp)
    {
        LOGE("%s: send_msg_to_cp is 0, so return.\n", __func__);
        return;
    }

    if (SIM_CARD_OUT != sim_pluged && SIM_CARD_IN != sim_pluged)
    {
        LOGE("%s: sim_pluged is invalid and it is %s.\n", __func__, simplug_to_string(sim_pluged));
        return;
    }

    det_gpio_level = gpio_get_value(info->det_gpio);
    LOGI("%s: sim%d, old_det_gpio_level: %d, det_gpio_level: %d\n",
            __func__, info->sim_id, info->old_det_gpio_level, det_gpio_level);
    if (det_gpio_level == info->old_det_gpio_level)
    {
        LOGI("%s: det_gpio_level is same with old_det_gpio_level, so return.\n", __func__);
        return;
    }
    info->old_det_gpio_level = det_gpio_level;

#ifdef CONFIG_HISI_BALONG_MODEM
    if (SIM0 == info->sim_id)
    {
        channel_id = SIM0_CHANNEL_ID;
    }
    else if (SIM1 == info->sim_id)
    {
        channel_id = SIM1_CHANNEL_ID;
    }
    else
    {
        LOGE("%s: sim%d invalid.\n", __func__, info->sim_id);
        return;
    }

    LOGI("%s: sim%d, sim_pluged = %s, bsp_icc_send to CP.\n",
            __func__, info->sim_id, simplug_to_string(sim_pluged));
    ret = bsp_icc_send(ICC_CPU_MODEM, channel_id, &sim_pluged, sizeof(sim_pluged));
    if (ret != sizeof(sim_pluged))
    {
         LOGE("%s: sim%d, bsp_icc_send failed.\n", __func__, info->sim_id);
    }
#else
    LOGI("%s: CONFIG_HISI_BALONG_MODEM undefined, so not call bsp_icc_send.\n", __func__);
#endif
    update_sim_state_info(info->sim_id, sim_pluged);
}

static void hisi_sim_hpd_msg_to_ccore(struct hisi_sim_hotplug_info *info)
{
#ifdef CONFIG_HISI_BALONG_MODEM
    u32 channel_id  = 0;
    s32 ret         = 0;
    u8 sim_state    = SIM_HPD_LEAVE;

    if (NULL == info)
    {
        LOGE("%s: input param is null, so return.\n", __func__);
        return;
    }

    if (SIM0 == info->sim_id)
    {
        channel_id = SIM0_CHANNEL_ID;
    }
    else if (SIM1 == info->sim_id)
    {
        channel_id = SIM1_CHANNEL_ID;
    }
    else
    {
        LOGE("%s: sim%d, error sim id, so return.\n", __func__, info->sim_id);
        return;
    }

    LOGI("%s: sim%d, SIM_HPD_LEAVE bsp_icc_send to CP.\n", __func__, info->sim_id);
    ret = bsp_icc_send(ICC_CPU_MODEM, channel_id, &sim_state, sizeof(sim_state));
    if (ret != sizeof(sim_state))
    {
        LOGE("%s: sim%d, bsp_icc_send failed.\n", __func__, info->sim_id);
    }
#else
    LOGI("%s: CONFIG_HISI_BALONG_MODEM undefined, so not call bsp_icc_send.\n", __func__);
#endif
}

static void det_irq_set_sim_insert(struct hisi_sim_hotplug_info *info)
{
    info->sim_pluged = SIM_CARD_IN;

    LOGI("%s: sim%d, SIM_CARD_IN\n", __func__, info->sim_id);
    sim_set_active(info);
    hisi_sim_det_msg_to_ccore(info, SIM_CARD_IN);
    save_sim_status_log(info, info->sim_id, info->sim_pluged, 0);
}

static void det_irq_set_sim_remove(struct hisi_sim_hotplug_info *info)
{
    info->sim_pluged = SIM_CARD_OUT;

    LOGI("%s: sim%d, SIM_CARD_OUT\n", __func__, info->sim_id);
    sim_set_inactive(info);
    hisi_sim_det_msg_to_ccore(info, SIM_CARD_OUT);
    save_sim_status_log(info, info->sim_id, info->sim_pluged, 1);
}

static void sim_manage_sim_state(int det_gpio_level, struct hisi_sim_hotplug_info *info)
{
    LOGI("%s: sim%d, old_det_gpio_level: %d, det_gpio_level: %d\n",
            __func__, info->sim_id, info->old_det_gpio_level, det_gpio_level);

    if (0 == det_gpio_level)
    {
        if (NORMAL_OPEN == info->det_normal_direction && SIM_CARD_OUT == info->sim_pluged)
        {
            det_irq_set_sim_insert(info);
        }
        else if (NORMAL_CLOSE == info->det_normal_direction && SIM_CARD_IN == info->sim_pluged)
        {
            det_irq_set_sim_remove(info);
        }
    }
    else
    {
        if (NORMAL_OPEN == info->det_normal_direction  && SIM_CARD_IN == info->sim_pluged)
        {
            det_irq_set_sim_remove(info);
        }
        else if (NORMAL_CLOSE == info->det_normal_direction && SIM_CARD_OUT == info->sim_pluged)
        {
            det_irq_set_sim_insert(info);
        }
    }
}

static void inquiry_sim_det_irq_reg(struct work_struct *work)
{
    struct hisi_sim_hotplug_info *info =
            container_of(work, struct hisi_sim_hotplug_info, sim_hotplug_det_work);
    int det_gpio_level = 0;

    det_gpio_level = gpio_get_value(info->det_gpio);
    LOGI("%s: sim%d, old sim_pluged: %s, det_gpio_level: %d\n",
            __func__, info->sim_id, simplug_to_string(info->sim_pluged), det_gpio_level);

    if (1 == info->send_msg_to_cp)
    {
        if (0 == info->det_debounce_checking && NULL != info->sim_debounce_delay_wq)
        {
            info->det_debounce_checking = 1;
            queue_delayed_work(info->sim_debounce_delay_wq,
                               &info->sim_debounce_delay_work,
                               msecs_to_jiffies(info->det_debounce_wait_time));
            LOGI("%s: sim%d, det debounce check begin.\n", __func__, info->sim_id);
        }
        else
        {
            LOGI("%s: sim%d, det debounce check is ongoing.\n", __func__, info->sim_id);
        }
    }
    else
    {
        sim_manage_sim_state(det_gpio_level, info);
    }
}

static irqreturn_t sim_det_irq_handler(int irq, void *data)
{
    struct hisi_sim_hotplug_info *info = data;
    if (NULL == info)
    {
        LOGE("%s: info is NULL.\n", __func__);
        return IRQ_HANDLED;
    }

    LOGI("%s: sim%d sim_hotplug_det_work begin.\n", __func__, info->sim_id);

    queue_work(info->sim_hotplug_det_wq, &info->sim_hotplug_det_work);
    return IRQ_HANDLED;
}

static void sim_debounce_check_func(struct work_struct *work)
{
    struct hisi_sim_hotplug_info *info =
            container_of(work, struct hisi_sim_hotplug_info, sim_debounce_delay_work.work);
    int det_gpio_level = 0;

    det_gpio_level = gpio_get_value(info->det_gpio);

    LOGI("%s: sim%d, old sim_pluged: %s, det_gpio_level: %d, det debounce check end.\n",
            __func__, info->sim_id, simplug_to_string(info->sim_pluged), det_gpio_level);
    sim_manage_sim_state(det_gpio_level, info);
    info->det_debounce_checking = 0;
}

static void sim_hpd_mask_irq(struct hisi_sim_hotplug_info *info, bool mask)
{
    struct irq_desc *sim_hpd_irq_desc;

    sim_hpd_irq_desc = irq_to_desc(info->hpd_irq);
    if (!sim_hpd_irq_desc)
    {
        LOGE("%s: sim_hpd_irq_desc error\n", __FUNCTION__);
        return;
    }

    if (mask)
    {
        /* mask interrupts */
        sim_hpd_irq_desc->irq_data.chip->irq_mask(&sim_hpd_irq_desc->irq_data);
    }
    else
    {
        /* unmask interrupts */
        sim_hpd_irq_desc->irq_data.chip->irq_unmask(&sim_hpd_irq_desc->irq_data);
    }
}

static irqreturn_t sim_hpd_irq_handler(int irq, void *data)
{
    struct hisi_sim_hotplug_info *info = data;
    if (NULL == info)
    {
        LOGE("%s: info is NULL.\n", __func__);
        return IRQ_HANDLED;
    }

    LOGI("%s: sim%d sim_hotplug_hpd_work.\n", __func__, info->sim_id);

    sim_hpd_mask_irq(info, 1);

    if (SIM0 == info->sim_id)
    {
        /* close ldo11 */
        WRITE_PMU_SIM(HI6421_IRQ_LDO11_VALUE,info->pmu_ldo11_onoff_eco_address);
        LOGI("%s: IRQ HPD0 happend, software close ldo11.\n", __func__);
    }
    else if (SIM1 == info->sim_id)
    {
        /* close ldo12 */
        WRITE_PMU_SIM(HI6421_IRQ_LDO12_VALUE, info->pmu_ldo12_onoff_eco_address);
        LOGI("%s: IRQ HPD1 happend, software close ldo12.\n", __func__);
    }

    queue_work(info->sim_hotplug_hpd_wq, &info->sim_hotplug_hpd_work);
    return IRQ_HANDLED;
}

static void inquiry_sim_hpd_irq_reg(struct work_struct *work)
{
    struct hisi_sim_hotplug_info *info =
            container_of(work, struct hisi_sim_hotplug_info, sim_hotplug_hpd_work);

    hisi_sim_hpd_msg_to_ccore(info);
    sim_hpd_mask_irq(info, 0);
}

static int sim_init_debounce_check_wq(struct hisi_sim_hotplug_info *info)
{
    int ret = 0;

    LOGI("%s: for sim%d\n", __func__, info->sim_id);
    if (NULL == info)
    {
        LOGE("%s: info is NULL, error.\n", __func__);
        ret = -EINVAL;
    }
    else
    {
        if (1 == info->send_msg_to_cp)
        {
            info->det_debounce_checking = 0;
            info->sim_debounce_delay_wq = create_singlethread_workqueue(work_name[info->sim_id]);
            if (NULL == info->sim_debounce_delay_wq)
            {
                LOGE("%s: sim_debounce_delay_wq create failed.\n", __func__);
                ret = -ENOMEM;
            }
            else
            {
                INIT_DELAYED_WORK(&(info->sim_debounce_delay_work), sim_debounce_check_func);
            }
        }
    }

    LOGI("%s: ret: %d, end\n", __func__, ret);
    return ret;
}

static int sim_hotplug_dts_init(struct hisi_sim_hotplug_info *info, struct device_node *np)
{
    int ret                     = 0;
    u32 sim_id                  = 0;
    u32 allocate_gpio           = 0;
    u32 shared_det_irq          = 0;
    u32 send_msg_to_cp          = 0;
    u32 send_card_out_msg       = 0;
    u32 card_tray_style         = 0;
    u32 det_debounce_wait_time  = 0;
    const char *str_func_sel_state = NULL;
    const char *str_det_normal_direction = NULL;
    enum of_gpio_flags flags;

    ret = of_property_read_u32_array(np, "sim_id", &sim_id, 1);
    if (ret)
    {
        LOGE("%s: no sim hotplug sim_id, so return.\n", __func__);
        return ret;
    }
    info->sim_id = sim_id;

    ret = of_property_read_string(np, "func_sel_state", &str_func_sel_state);
    if (ret < 0)
    {
        LOGE("%s: failed to read func_sel_state.\n", __func__);
        return ret;
    }

    if (0 == strcmp(str_func_sel_state, "use_multi_func"))
    {
        info->func_sel_state = USE_MULTI_FUNC;
    }
    else if (0 == strcmp(str_func_sel_state, "not_use_multi_func"))
    {
        info->func_sel_state = NOT_USE_MULTI_FUNC;
    }
    else
    {
        info->func_sel_state = SELECT_STATE_OTHER;
    }

    if (SELECT_STATE_OTHER == info->func_sel_state)
    {
        LOGI("%s: func_sel_state is SELECT_STATE_OTHER(2), so return.\n", __func__);
        return -EINVAL;
    }

    ret = of_property_read_string(np, "det_normal_direction", &str_det_normal_direction);
    if (ret < 0)
    {
        LOGE("%s: failed to read det_normal_direction.\n", __func__);
        return ret;
    }

    if (0 == strcmp(str_det_normal_direction, "open"))
    {
        info->det_normal_direction = NORMAL_OPEN;
    }
    else if (0 == strcmp(str_det_normal_direction, "closed"))
    {
        info->det_normal_direction = NORMAL_CLOSE;
    }
    else
    {
        info->det_normal_direction = NORMAL_BUTT;
    }

    if (SIM0 == sim_id)
    {
        sim_plug_state.sim0_det_normal_direction = (u8)(info->det_normal_direction);
    }
    else if (SIM1 == sim_id)
    {
        sim_plug_state.sim1_det_normal_direction = (u8)(info->det_normal_direction);
    }

    if (NORMAL_BUTT == info->det_normal_direction)
    {
        LOGI("%s: det_normal_direction is NORMAL_BUTT(2) and set to NORMAL_OPEN(1).\n", __func__);
        info->det_normal_direction = NORMAL_OPEN;
    }

    /* read det pin gpio number */
    info->det_gpio = of_get_gpio_flags(np, 0, &flags);
    if (info->det_gpio < 0)
    {
        LOGE("%s: det_gpio_number: %d, error.\n", __func__, info->det_gpio);
        return info->det_gpio;
    }

    if (!gpio_is_valid(info->det_gpio))
    {
        LOGE("%s: det_gpio_number: %d, gpio_is_valid is invalid, error.\n", __func__, info->det_gpio);
        return -EINVAL;
    }

    if (of_property_read_u32(np, "allocate_gpio", &allocate_gpio))
    {
        LOGI("%s: allocate_gpio property not found, using 0 as default.\n", __func__);
        allocate_gpio = 0;
    }
    info->allocate_gpio = allocate_gpio;
    if (1 == allocate_gpio)
    {
        LOGI("%s: sim%d, gpio_request_one, det_gpio: %d\n", __func__, sim_id, info->det_gpio);
        ret = gpio_request_one(info->det_gpio, GPIOF_IN, "sim_det");
        if (ret < 0)
        {
            LOGE("failed to gpio_request_one for sim%d det_gpio: %d.\n", sim_id, info->det_gpio);
            return ret;
        }
    }
    info->det_irq = gpio_to_irq(info->det_gpio);

    if (of_property_read_u32(np, "shared_det_irq", &shared_det_irq))
    {
        LOGI("%s: shared_det_irq property not found, using 0 as default.\n", __func__);
        shared_det_irq = 0;
    }
    info->shared_det_irq = shared_det_irq;

    ret = of_property_read_u32(np, "send_msg_to_cp", &send_msg_to_cp);
    if (ret < 0)
    {
        LOGI("failed to read send_msg_to_cp, so set it to 0.\n");
        send_msg_to_cp = 0;
    }
    info->send_msg_to_cp = send_msg_to_cp;

    ret = of_property_read_u32(np, "send_card_out_msg_when_init", &send_card_out_msg);
    if (ret < 0)
    {
        LOGI("failed to read send_card_out_msg_when_init, so set it to 0.\n");
        send_card_out_msg = 0;
    }
    info->send_card_out_msg = send_card_out_msg;

    ret = of_property_read_u32(np, "card_tray_style", &card_tray_style);
    if (ret < 0)
    {
        LOGE("failed to read card_tray_style.\n");
        return ret;
    }
    info->card_tray_style = card_tray_style;

    LOGI("%s: sim%d, func_sel_state: %s, det_gpio_number: %d, det_normal_direction: %s\n",
            __func__, sim_id, func_sel_state_to_string(info->func_sel_state), info->det_gpio,
            direction_to_string(info->det_normal_direction));
    LOGI("%s: sim%d, allocate_gpio: %d, shared_det_irq: %d, send_msg_to_cp: %d, send_card_out_msg: %d, card_tray_style: %s\n",
            __func__, sim_id, allocate_gpio, shared_det_irq,
            send_msg_to_cp, send_card_out_msg,
            card_tray_style_to_string(card_tray_style));

    /* create det workqueue */
    info->sim_hotplug_det_wq = create_singlethread_workqueue("sim_hotplug_det");
    if (NULL == info->sim_hotplug_det_wq)
    {
        LOGE("failed to create work queue.\n");
        return -ENOMEM;
    }

    INIT_WORK(&info->sim_hotplug_det_work, (void *)inquiry_sim_det_irq_reg);

    if (1 == send_msg_to_cp)
    {
        ret = of_property_read_u32(np, "det_debounce_wait_time", &det_debounce_wait_time);
        if (ret < 0)
        {
            det_debounce_wait_time = DET_DEBOUNCE_CHECK_WAIT_TIME;
        }

        info->det_debounce_wait_time = det_debounce_wait_time;
        LOGI("%s: sim%d, det_debounce_wait_time: %d\n", __func__, sim_id, det_debounce_wait_time);
    }

    ret = sim_init_debounce_check_wq(info);

    return ret;
}

static int sim_state_init(struct hisi_sim_hotplug_info *info, struct device *dev)
{
#ifdef SUPPORT_MULTI_FUNC
    info->pctrl = devm_pinctrl_get(dev);
    if (IS_ERR(info->pctrl))
    {
        LOGE("failed to devm pinctrl get.\n");
        return -EINVAL;
    }

    info->sim_default_state = pinctrl_lookup_state(info->pctrl, PINCTRL_STATE_DEFAULT);
    if (IS_ERR(info->sim_default_state))
    {
        LOGE("failed to pinctrl lookup state default.\n");
        return -EINVAL;
    }

    info->sim_idle_state = pinctrl_lookup_state(info->pctrl, PINCTRL_STATE_IDLE);
    if (IS_ERR(info->sim_idle_state))
    {
        LOGE("failed to pinctrl lookup state idle.\n");
        return -EINVAL;
    }
#endif

    if (0 == gpio_get_value(info->det_gpio))
    {
        info->old_det_gpio_level = 0;
        if (NORMAL_CLOSE == info->det_normal_direction)
        {
            info->sim_pluged = SIM_CARD_OUT;
            sim_set_inactive(info);
            save_sim_status_log(info, info->sim_id, info->sim_pluged, 3);
            if (1 == info->send_card_out_msg)
            {
                info->old_det_gpio_level = 1;
                hisi_sim_det_msg_to_ccore(info, SIM_CARD_OUT);
            }
        }
        else
        {
            info->sim_pluged = SIM_CARD_IN;
            sim_set_active(info);
            save_sim_status_log(info, info->sim_id, info->sim_pluged, 2);
        }
    }
    else
    {
        info->old_det_gpio_level = 1;
        if (NORMAL_CLOSE == info->det_normal_direction)
        {
            info->sim_pluged = SIM_CARD_IN;
            sim_set_active(info);
            save_sim_status_log(info, info->sim_id, info->sim_pluged, 2);
        }
        else
        {
            info->sim_pluged = SIM_CARD_OUT;
            sim_set_inactive(info);
            save_sim_status_log(info, info->sim_id, info->sim_pluged, 3);
            if (1 == info->send_card_out_msg)
            {
                info->old_det_gpio_level = 0;
                hisi_sim_det_msg_to_ccore(info, SIM_CARD_OUT);
            }
        }
    }

    mutex_init(&(info->sim_hotplug_lock));
    wake_lock_init(&info->sim_hotplug_wklock, WAKE_LOCK_SUSPEND, "android-simhotplug");

    return 0;
}

static int sim_hpd_init(struct hisi_sim_hotplug_info *info, struct platform_device *pdev)
{
    int ret = 0;

    if (SIM0 == info->sim_id)
    {
        info->hpd_irq = platform_get_irq_byname(pdev, "hpd0_falling");
    }
    else if (SIM1 == info->sim_id)
    {
        info->hpd_irq = platform_get_irq_byname(pdev, "hpd1_falling");
    }
    else
    {
        LOGE("%s: sim%d, error sim id, so return.\n", __func__, info->sim_id);
        return -EINVAL;
    }
    if (info->hpd_irq < 0)
    {
        return -ENOENT;
    }

    /* create hpd workqueue */
    info->sim_hotplug_hpd_wq = create_singlethread_workqueue("sim_hotplug_hpd");
    if (NULL == info->sim_hotplug_hpd_wq)
    {
        LOGE("sim_hotplug_hpd_wq failed to create work queue.\n");
        return -EINVAL;
    }

    INIT_WORK(&info->sim_hotplug_hpd_work, (void *)inquiry_sim_hpd_irq_reg);
    ret = request_threaded_irq(info->hpd_irq, sim_hpd_irq_handler, NULL,
            IRQF_DISABLED | IRQF_NO_SUSPEND, "sim_hpd", info);
    if (ret < 0)
    {
        LOGE("sim%d_hpd failed to request_threaded_irq!\n", info->sim_id);
    }

    LOGI("%s: sim%d hpd_irq: %d\n", __func__, info->sim_id, info->hpd_irq);
    return ret;
}

static int get_iomux_base_addr(struct hisi_sim_hotplug_info *info)
{
    struct device_node *np = NULL;

    np = of_find_compatible_node(NULL, NULL, "pinctrl-single0");
    if (!np)
    {
        LOGE("failed to find pinctrl-single0 node!\n");
        return -1;
    }

    info->iomg_base = of_iomap(np, 0);
    if (!info->iomg_base)
    {
        LOGE("unable to map pinctrl-single0 dist registers!\n");
        return -1;
    }

    return 0;
}

static int hisi_sim_hotplug_probe(struct platform_device *pdev)
{
    struct device *dev                  = NULL;
    struct device_node *np              = NULL;
    struct hisi_sim_hotplug_info *info  = NULL;
    int     ret = 0;

    if (NULL == pdev)
    {
        LOGE("%s: error, pdev is NULL.\n", __func__);
        return -EINVAL;
    }

    dev = &pdev->dev;
    np = dev->of_node;

    info = devm_kzalloc(&pdev->dev, sizeof(*info), GFP_KERNEL);
    if (!info)
    {
        LOGE("%s: failed to allocate memory.\n", __func__);
        return -ENOMEM;
    }

    ret = get_iomux_base_addr(info);
    if (ret < 0)
    {
        LOGE("%s: failed to get iomux base addr.\n", __func__);
        return ret;
    }


    ret = sim_pmu_hpd_init(info, np);
    if (ret < 0)
    {
        LOGE("%s: sim_pmu_hpd_init failed.\n", __func__);
        return ret;
    }

    ret = sim_hotplug_dts_init(info, np);
    if (ret < 0)
    {
        LOGE("%s: sim_hotplug_dts_init failed.\n", __func__);
        return ret;
    }

    ret = sim_state_init(info, dev);
    if (ret < 0)
    {
        LOGE("%s: sim_state_init failed.\n", __func__);
        goto free_sim_det_wq;
    }

    if (1 == info->shared_det_irq)
    {
        ret = request_threaded_irq(info->det_irq, sim_det_irq_handler, NULL,
                IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING | IRQF_NO_SUSPEND | IRQF_SHARED,
                "sim_det", info);
    }
    else
    {
        ret = request_threaded_irq(info->det_irq, sim_det_irq_handler, NULL,
                IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING | IRQF_NO_SUSPEND,
                "sim_det", info);
    }
    if (ret < 0)
    {
        LOGE("%s: request_threaded_irq failed.\n", __func__);
        goto free_sim_lock;
    }

    ret = sim_hpd_init(info, pdev);
    if (ret < 0)
    {
        LOGE("%s: sim_hpd_init failed.\n", __func__);
        goto free_sim_lock;
    }

    if (0 == info->sim_id)
    {
        sys_add_sim_node();
    }

    platform_set_drvdata(pdev, info);

    return ret;

free_sim_lock:
    wake_lock_destroy(&info->sim_hotplug_wklock);
    mutex_destroy(&info->sim_hotplug_lock);

free_sim_det_wq:
    if (info->sim_hotplug_det_wq)
    {
        destroy_workqueue(info->sim_hotplug_det_wq);
    }
    if (info->sim_hotplug_hpd_wq)
    {
        destroy_workqueue(info->sim_hotplug_hpd_wq);
    }

    return ret;
}

static int hisi_sim_hotplug_remove(struct platform_device *pdev)
{
    struct hisi_sim_hotplug_info *info;

    /*get hisi_sim_hotplug_info*/
    info = platform_get_drvdata(pdev);
    if (NULL == info)
    {
        LOGE("%s: platform_get_drvdata is NULL.\n", __func__);
        return -1;
    }

    mutex_destroy(&info->sim_hotplug_lock);
    wake_lock_destroy(&info->sim_hotplug_wklock);

    if (info->sim_hotplug_det_wq)
    {
        destroy_workqueue(info->sim_hotplug_det_wq);
    }
    if (info->sim_hotplug_hpd_wq)
    {
        destroy_workqueue(info->sim_hotplug_hpd_wq);
    }

    if (1 == info->send_msg_to_cp && info->sim_debounce_delay_wq)
    {
        LOGI("%s: remove delay work for sim%d\n", __func__, info->sim_id);
        cancel_delayed_work(&info->sim_debounce_delay_work);
        flush_workqueue(info->sim_debounce_delay_wq);
        destroy_workqueue(info->sim_debounce_delay_wq);
    }

    return 0;
}

static struct of_device_id hisi_sim_hotplug_of_match[] =
{
    { .compatible = "hisilicon,sim-hotplug0", },
    { .compatible = "hisilicon,sim-hotplug1", },
    { },
};
MODULE_DEVICE_TABLE(of, hisi_sim_hotplug_of_match);

#ifdef CONFIG_PM
static int hisi_sim_hotplug_suspend(struct platform_device *pdev, pm_message_t state)
{
    struct hisi_sim_hotplug_info *info;

    LOGI("%s: suspend+\n", __func__);
    /*get hisi_sim_hotplug_info*/
    info = platform_get_drvdata(pdev);
    if (NULL == info)
    {
        LOGE("%s: platform_get_drvdata is NULL.\n", __func__);
        return -1;
    }

    if (!mutex_trylock(&info->sim_hotplug_lock))
    {
        LOGE("%s: mutex_trylock failed.\n", __func__);
        return -EAGAIN;
    }

    LOGI("%s: suspend-\n", __func__);
    return 0;
}

static int hisi_sim_hotplug_resume(struct platform_device *pdev)
{
    struct hisi_sim_hotplug_info *info;

    LOGI("%s: resume+\n", __func__);
    /*get hisi_sim_hotplug_info*/
    info = platform_get_drvdata(pdev);
    if (NULL == info)
    {
        LOGE("%s: platform_get_drvdata is NULL.\n", __func__);
        return -1;
    }

    mutex_unlock(&(info->sim_hotplug_lock));

    LOGI("%s: resume-\n", __func__);
    return 0;
}
#endif

static struct platform_driver hisi_sim_hotplug_driver =
{
    .probe      = hisi_sim_hotplug_probe,
    .remove     = hisi_sim_hotplug_remove,
    .driver     =
    {
        .owner      = THIS_MODULE,
        .name       = "hisi-sim_hotplug",
        .of_match_table = hisi_sim_hotplug_of_match,
    },
#ifdef CONFIG_PM
    .suspend        = hisi_sim_hotplug_suspend,
    .resume         = hisi_sim_hotplug_resume,
#endif
};

int __init hisi_sim_hotplug_init(void)
{
    return platform_driver_register(&hisi_sim_hotplug_driver);
}

static void __exit hisi_sim_hotplug_exit(void)
{
    platform_driver_unregister(&hisi_sim_hotplug_driver);
}

late_initcall(hisi_sim_hotplug_init);
module_exit(hisi_sim_hotplug_exit);

MODULE_DESCRIPTION("Sim hotplug driver");
MODULE_LICENSE("GPL v2");
