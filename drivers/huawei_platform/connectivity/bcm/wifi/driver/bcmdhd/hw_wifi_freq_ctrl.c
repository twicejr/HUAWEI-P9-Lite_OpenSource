
/*********************************************************************
Copyright  (C),  2001-2012,  Huawei  Tech.  Co.,  Ltd.

**********************************************************************/

#include <asm/atomic.h>
#include <linux/err.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <linux/timer.h>
#include <linux/pm_qos.h>
#include <asm/uaccess.h>
#include <linux/time.h>
#include <linux/errno.h>
#include <linux/of.h>
#include "hw_wifi_freq_ctrl.h"
#include "dhd_dbg.h"

/**
 *  struct speed_freq_level_t
 *  @speed_level: current data transfer speed(bit/s)
 *  @min_cpu_freq: Minimal CPU Frequency for the speed level(KHz)
 *  @min_ddr_freq: Minimal DDR Frequency for the speed level(KHz)
 *                 0 means not need DDR Frequency lock
 */
typedef struct {
    unsigned long speed_level;
    unsigned int min_cpu_freq;
    unsigned int min_ddr_freq;
} speed_freq_level_t;

/**
 *  struct freq_lock_control_t
 *  @lock_mod: Frequency lock enable/disable mode
 *  @curr_lock_level: Current Lock Level
 *  @req_lock_level: Request Lock Level
 *  @lock_freq_mtx: Mutex for Resource Operation
 *  @speed_calc_lock: spin_lock for Rx/Tx Data Calculate
 *  @lock_freq_timer_list: Timer for release frequency lock
 *  @freq_ctl_wq: workqueue for freq lock and release
 *  @release_lock_work: work struct for lock frequency
 *  @do_freq_lock_work: work struct for release frequency
 */
typedef struct {
    unsigned int lock_mod;

    unsigned int curr_lock_level;
    unsigned int req_lock_level;

    struct mutex lock_freq_mtx;
    spinlock_t speed_calc_lock;

    struct timer_list lock_freq_timer_list;

    struct workqueue_struct* freq_ctl_wq;
    struct work_struct release_lock_work;
    struct work_struct do_freq_lock_work;
} freq_lock_control_t;


#define  FREQ_LOCK_TIMEOUT_VAL              1000  /*unit: ms*/
#define  LOCK_LEVEL_VAR_NUM                 3
/*
 * 5Mbits data bytes, unit:bytes
 * calculation bytes = (5*1024*1024/8)
 *
 * when total transfer data reached to 5M Bytes,
 * calculate the speed trigger speed (bits/s).
 */
#define  SPEED_CALC_TRIG_VALUE              655360

/*
 * set cpu freq A53-0
 * this function used on K3V3+ platform
 */
#define CPU_MAX_FREQ "/sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq"
#define CPU_MIN_FREQ "/sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq"

/*
 * set ddr freq
 * this function used on K3V3+ platform
 */
#define DDR_MAX_FREQ "/sys/class/devfreq/ddrfreq/max_freq"
#define DDR_MIN_FREQ "/sys/class/devfreq/ddrfreq/min_freq"

#define DTS_COMP_WIFI_POWER_NAME "hisilicon,bcm_wifi"

enum {
    /* indicate to set cpu/ddr max frequencies */
    SCALING_MAX_FREQ                        = 0,

    /* indicate to set cpu/ddr min frequencies */
    SCALING_MIN_FREQ                        = 1,
};

enum {
    /* indicate to set cpu/ddr to a low level */
    FREQ_DOWNGRADE                          = 0,

    /* indicate to set cpu/ddr to a high level */
    FREQ_UPGRADE                            = 1,

    /* indicate to set cpu/ddr to original level */
    FREQ_ORIGINAL                           = 2,
};

enum {
    /* frequency lock disable mode */
    FREQ_LOCK_DISABLE                       = 0,

    /* frequency lock enable mode */
    FREQ_LOCK_ENABLE                        = 1,
};

/*
 * Indicate the time for starting calculate transfer bytes.
 *
 * When transfer bytes reached to 5M,
 * calculate the transfer speed.
 */
static unsigned long pre_jiffies            = 0;

/*
 * these four static global variables used to
 * save original cpu/ddr frequency. these variables will be read
 * when call @hw_wifi_freq_ctrl_init. and will be resume to original
 * when call @hw_wifi_freq_ctrl_destroy or time expired.
 *
 * @orig_cpu_min_freq: to save original scaling_min_freq for A53_0.
 * @orig_cpu_max_freq: to save original scaling_max_freq for A53_0.
 * @orig_ddr_min_freq: to save original min_freq for DDR.
 * @orig_ddr_max_freq: to save original max_freq for DDR.
 */
static unsigned int orig_cpu_min_freq       = 0;
static unsigned int orig_cpu_max_freq       = 0;
static unsigned int orig_ddr_min_freq       = 0;
static unsigned int orig_ddr_max_freq       = 0;

/*
 * Save the total transfer bytes every tx/rx.
 *
 * When transfer bytes reached to 5M,
 * calculate the transfer speed.
 */
static unsigned long wifi_rxtx_tot          = 0;

/*
 * Open the debug log.
 *
 * You can echo 1 to module parameter
 * to enable log print dynamiclly.
 */
int debug_wifi_freq_lock                    = 0;

#define lf_dbg(format, arg...) { \
    if (debug_wifi_freq_lock) \
        printk("Freq gov msg: "format, ##arg); \
}

static uint                 g_freq_lock_num         = 0;
static speed_freq_level_t*  g_speed_freq_level      = NULL;

static freq_lock_control_t* freq_lock_control_ptr = NULL;

static struct pm_qos_request *pq_req = NULL;


static int get_cpu_freq_raw(int freq, uint* value)
{
    struct file* filp = NULL;
    mm_segment_t old_fs;
    char buf[12] = {0};

    if (freq == SCALING_MAX_FREQ)
        filp = filp_open(CPU_MAX_FREQ, O_RDONLY, 0);
    else if (freq == SCALING_MIN_FREQ)
        filp = filp_open(CPU_MIN_FREQ, O_RDONLY, 0);
    else
        return -1;

    if (IS_ERR(filp)) {
        HW_PRINT_HI("get_cpu_freq_raw:¡¡freq¡¡= %d error\n", freq);
        return -1;
    }
    old_fs = get_fs();
    set_fs(KERNEL_DS);
    filp->f_pos = 0;
    filp->f_op->read(filp, buf, 12, &filp->f_pos);
    filp_close(filp, NULL);
    set_fs(old_fs);

    if (kstrtouint(buf, 10, value) != 0) {
        HW_PRINT_HI("error to get cpu freq\n");
        return -1;
    }

    return 0;
}

static int set_cpu_freq_raw(int freq, uint value)
{
    struct file* filp = NULL;
    mm_segment_t old_fs;
    char buf[12] = {0};

    snprintf(buf, 12, "%d", value);
    lf_dbg("set_cpu_freq_raw:  freq = %d,  buf = %s\n",  freq, buf);

    if (freq == SCALING_MIN_FREQ)
        filp = filp_open(CPU_MIN_FREQ, O_RDWR, 0);
    else if (freq == SCALING_MAX_FREQ)
        filp = filp_open(CPU_MAX_FREQ, O_RDWR, 0);
    else
        return -1;

    if (IS_ERR(filp)) {
        HW_PRINT_HI("set_cpu_freq_raw:¡¡freq¡¡= %d error\n", freq);
        return -1;
    }
    old_fs = get_fs();
    set_fs(KERNEL_DS);
    filp->f_pos = 0;
    filp->f_op->write(filp, buf, 12, &filp->f_pos);
    filp_close(filp, NULL);
    set_fs(old_fs);

    return 0;
}

static int get_ddr_freq_raw(int freq, uint* value)
{
    struct file* filp = NULL;
    mm_segment_t old_fs;
    char buf[12] = {0};

    if (freq == SCALING_MAX_FREQ)
        filp = filp_open(DDR_MAX_FREQ, O_RDONLY, 0);
    else if (freq == SCALING_MIN_FREQ)
        filp = filp_open(DDR_MIN_FREQ, O_RDONLY, 0);
    else
        return -1;

    if (IS_ERR(filp)) {
        HW_PRINT_HI("get_ddr_freq_raw:¡¡freq¡¡= %d error£\\n", freq);
        return -1;
    }
    old_fs = get_fs();
    set_fs(KERNEL_DS);
    filp->f_pos = 0;
    filp->f_op->read(filp, buf, 12, &filp->f_pos);
    filp_close(filp, NULL);
    set_fs(old_fs);

    if (kstrtouint(buf, 10, value) != 0) {
        HW_PRINT_HI("error to get cpu freq\n");
        return -1;
    }

    return 0;
}

static int set_ddr_freq_raw(int freq, uint value)
{
    struct file* filp = NULL;
    mm_segment_t old_fs;
    char buf[12] = {0};

    snprintf(buf, 12, "%d", value);

    lf_dbg("set_ddr_freq_raw:  freq = %d,  buf = %s\n",  freq, buf);

    if (freq == SCALING_MIN_FREQ)
        filp = filp_open(DDR_MIN_FREQ, O_RDWR, 0);
    else if (freq == SCALING_MAX_FREQ)
        filp = filp_open(DDR_MAX_FREQ, O_RDWR, 0);
    else
        return -1;

    if (IS_ERR(filp)) {
        HW_PRINT_HI("set_ddr_freq_raw:¡¡freq¡¡= %d error£Ün", freq);
        return -1;
    }
    old_fs = get_fs();
    set_fs(KERNEL_DS);
    filp->f_pos = 0;
    filp->f_op->write(filp, buf, 12, &filp->f_pos);
    filp_close(filp, NULL);
    set_fs(old_fs);

    return 0;
}

static int set_cpu_freq(uint value, int type)
{
    int ret;
    uint cur_cpu_max_freq;

    ret = get_cpu_freq_raw(SCALING_MAX_FREQ, &cur_cpu_max_freq);
    if(ret != 0) {
        return -1;
    }

    if(type == FREQ_UPGRADE) {
        /* if dest freq is higher then current freq,
           scaling_max_freq should be set, then scaling_min_freq */
        if(value > cur_cpu_max_freq)
            set_cpu_freq_raw(SCALING_MAX_FREQ, value);
        set_cpu_freq_raw(SCALING_MIN_FREQ, value);
    } else if (type == FREQ_DOWNGRADE) {
        /* if dest freq is lower then current freq,
           scaling_min_freq should be set, then scaling_max_freq */
        set_cpu_freq_raw(SCALING_MIN_FREQ, value);
        if(value > cur_cpu_max_freq)
            set_cpu_freq_raw(SCALING_MAX_FREQ, value);
    } else if (type == FREQ_ORIGINAL) {
        /* set scaling_max_freq and scaling_min_freq to original */
        set_cpu_freq_raw(SCALING_MIN_FREQ, orig_cpu_min_freq);
        set_cpu_freq_raw(SCALING_MAX_FREQ, orig_cpu_max_freq);
    } else {
        HW_PRINT_HI("error set_cpu_freq, invalid types\n");
        return -1;
    }

    return 0;
}

static int set_ddr_freq(uint value, int type)
{
    int ret;
    uint cur_ddr_max_freq;

    ret = get_ddr_freq_raw(SCALING_MAX_FREQ, &cur_ddr_max_freq);
    if(ret != 0) {
        return -1;
    }

    if(type == FREQ_UPGRADE) {
        /* if dest freq is higher then current freq,
           max_freq should be set, then min_freq */
        if(value > cur_ddr_max_freq)
            set_ddr_freq_raw(SCALING_MAX_FREQ, value);
        set_ddr_freq_raw(SCALING_MIN_FREQ, value);
    } else if(type == FREQ_DOWNGRADE) {
        /* if dest freq is lower then current freq,
           min_freq should be set, then max_freq */
        set_ddr_freq_raw(SCALING_MIN_FREQ, value);
        if(value > cur_ddr_max_freq)
            set_ddr_freq_raw(SCALING_MAX_FREQ, value);
    } else if (type == FREQ_ORIGINAL) {
        /* set max_freq and min_freq to original */
        set_ddr_freq_raw(SCALING_MIN_FREQ, orig_ddr_min_freq);
        set_ddr_freq_raw(SCALING_MAX_FREQ, orig_ddr_max_freq);
    } else {
        HW_PRINT_HI("error set_ddr_freq, invalid types\n");
        return -1;
    }

    return 0;
}
//this function used on K3V3 platform

static void add_ddr_request(void)
{
    pq_req = kmalloc(sizeof(struct pm_qos_request), GFP_KERNEL);
    if(pq_req == NULL){
        HW_PRINT_HI("%s: malloc error\n", __FUNCTION__);
        return;
    }
    pq_req->pm_qos_class = 0;
    pm_qos_add_request(pq_req, PM_QOS_MEMORY_THROUGHPUT,
        PM_QOS_MEMORY_THROUGHPUT_DEFAULT_VALUE);

    return;
}

static void del_ddr_request(void)
{
    pm_qos_remove_request(pq_req);
    kfree(pq_req);
    pq_req = NULL;
}

/*****************************************************************************
Description    : once frequency control release timer timeout, this function will be triggered.
                 It will release the minimal CPU and DDR frequency lock.
                 This function run in the frequency control work quenue.
Prototype      : void hw_wifi_release_freq_lock_work(struct work_struct *work)
Input  Param   :
Output  Param  :
Return  Value  :
******************************************************************************/
static void hw_wifi_release_freq_lock_work(struct work_struct *work)
{
    freq_lock_control_t *fl_control_ptr =
        container_of(work, freq_lock_control_t, release_lock_work);

    lf_dbg("hw_wifi_release_freq_lock_work call enter.\n");

    if (NULL == fl_control_ptr) {
        HW_PRINT_HI("hw_wifi_release_freq_lock_work  NULL point error!\n");
        return;
    }

    mutex_lock(&fl_control_ptr->lock_freq_mtx);

    if (FREQ_LOCK_ENABLE == fl_control_ptr->lock_mod) {
        /* lock freq timer timeout,
           do frequency lock release process here.
           release frequency to original value */
        set_cpu_freq(0, FREQ_ORIGINAL);
        set_ddr_freq(0, FREQ_ORIGINAL);
        fl_control_ptr->lock_mod = FREQ_LOCK_DISABLE;
    }

    mutex_unlock(&fl_control_ptr->lock_freq_mtx);

}

/*****************************************************************************
Description    :
Prototype      : void hw_wifi_release_freq_lock_timer(unsigned long data)
Input  Param   :
Output  Param  :
Return  Value  :
******************************************************************************/
static void hw_wifi_release_freq_lock_timer(unsigned long data)
{
    freq_lock_control_t  * fl_control_ptr =
        (freq_lock_control_t  *) data;

    if(NULL == fl_control_ptr) {
        HW_PRINT_HI("hw_wifi_release_freq_lock_timer  NULL point error!\n");
        return;
    }

    /*!! Can not and not need use mutex_lock here. this function is a softirq,
	* not allow schedule and sleep that are trigger by mutex_lock in this function.*/
    if (freq_lock_control_ptr->freq_ctl_wq != NULL) {
        queue_work(fl_control_ptr->freq_ctl_wq,
                    &fl_control_ptr->release_lock_work);
    }
}

/*****************************************************************************
Description    : Set the frequency control as the req_lock_level indicate and start or refresh
                 the 1s frequency control release timer.
                 This function run in the frequency control work quenue.
Prototype      : void  hw_wifi_do_freq_lock_work(struct work_struct *work)
Input  Param   :
Output  Param  :
Return  Value  :
******************************************************************************/
static void  hw_wifi_do_freq_lock_work(struct work_struct *work){
    unsigned char req_lock_level = 0;
    freq_lock_control_t *fl_control_ptr =
        container_of(work, freq_lock_control_t, do_freq_lock_work);

    if (NULL == fl_control_ptr) {
        HW_PRINT_HI("hw_wifi_do_freq_lock_work  NULL point error!\n");
        return;
    }

    mutex_lock(&fl_control_ptr->lock_freq_mtx);

    req_lock_level = fl_control_ptr->req_lock_level;
    if ((g_speed_freq_level == NULL) ||
        (req_lock_level > g_freq_lock_num) ||
        (0 == req_lock_level)) {
        HW_PRINT_HI("hw_wifi_do_freq_lock_work  invalid lock_level error!\n");
        mutex_unlock(&fl_control_ptr->lock_freq_mtx);
        return;
    }

    if (FREQ_LOCK_ENABLE == fl_control_ptr->lock_mod) {
        lf_dbg("hw_wifi_do_freq_lock_work, lock_mod = FREQ_LOCK_ENABLE\n");

        if (req_lock_level > fl_control_ptr->curr_lock_level) {
            lf_dbg("hw_wifi_do_freq_lock_work, lock level upgrade\n");
            /* Frequency lock level has been changed. Do new level's frequency lock here.*/
            set_cpu_freq(g_speed_freq_level[req_lock_level-1].min_cpu_freq, FREQ_UPGRADE);
            set_ddr_freq(g_speed_freq_level[req_lock_level-1].min_ddr_freq, FREQ_UPGRADE);

            fl_control_ptr->curr_lock_level = req_lock_level;
        } else if (req_lock_level < fl_control_ptr->curr_lock_level) {
            lf_dbg("hw_wifi_do_freq_lock_work, lock level downgrade\n");
            set_cpu_freq(g_speed_freq_level[req_lock_level-1].min_cpu_freq, FREQ_DOWNGRADE);
            set_ddr_freq(g_speed_freq_level[req_lock_level-1].min_ddr_freq, FREQ_DOWNGRADE);

            fl_control_ptr->curr_lock_level = req_lock_level;
        } else {
            /* request freq is equal to current freq, do nothing */
            lf_dbg("do not need set new freq\n");
        }
    } else {
        lf_dbg("hw_wifi_do_freq_lock_work, lock_mod = FREQ_LOCK_DISABLE\n");
        /*freq lock is disabled, enable it now*/
        fl_control_ptr->lock_mod = FREQ_LOCK_ENABLE;
        fl_control_ptr->curr_lock_level = req_lock_level;

        set_cpu_freq(g_speed_freq_level[req_lock_level-1].min_cpu_freq, FREQ_UPGRADE);
        set_ddr_freq(g_speed_freq_level[req_lock_level-1].min_ddr_freq, FREQ_UPGRADE);
    }

    /*start or reset release timer */
    mod_timer(&freq_lock_control_ptr->lock_freq_timer_list,
                  jiffies +
                  msecs_to_jiffies(FREQ_LOCK_TIMEOUT_VAL));

    mutex_unlock(&fl_control_ptr->lock_freq_mtx);
}

static int get_rate_freq_data_from_dts()
{
    struct device_node *np;
    speed_freq_level_t *p_table;
    unsigned int table_num;
    int i;
    const char *propname = "freq_table_t";
    struct property *prop = NULL;

    np = of_find_compatible_node(NULL, NULL, DTS_COMP_WIFI_POWER_NAME);
    if (np == NULL) {
		HW_PRINT_HI("Unable to find bcm_wifi power\n");
		return -1;
	}

    prop = of_find_property(np, propname, NULL);
    if (prop == NULL) {
        HW_PRINT_HI("Can not get transfer rate data\n");
        return -1;
    }

    /* Calculate the number of table: speed_freq_level_t */
    table_num = prop->length / sizeof(u32);
    table_num /= LOCK_LEVEL_VAR_NUM;
    p_table = kzalloc(sizeof(speed_freq_level_t) * table_num, GFP_KERNEL);
    if(!p_table) {
        HW_PRINT_HI("Unable to alloc enough buffer\n");
        return -1;
    }

    for (i = 0; i < table_num; i++) {
        of_property_read_u32_index(np, propname, i * LOCK_LEVEL_VAR_NUM,
                                &(p_table[i].speed_level));
        of_property_read_u32_index(np, propname, i * LOCK_LEVEL_VAR_NUM + 1,
                                &(p_table[i].min_cpu_freq));
        of_property_read_u32_index(np, propname, i * LOCK_LEVEL_VAR_NUM + 2,
                                &(p_table[i].min_ddr_freq));
        lf_dbg("p_table[%d].speed_level = %lu, min_cpu_freq = %d, min_ddr_freq = %d\n",
                        i,
                        p_table[i].speed_level,
                        p_table[i].min_cpu_freq,
                        p_table[i].min_ddr_freq);

    }

    g_freq_lock_num = table_num;
    g_speed_freq_level = p_table;

    return 0;
}
/*****************************************************************************
Description    : Do  memory allocation, workqueue set up etc while the WiFi driver opening.
Prototype      : int  hw_wifi_freq_ctrl_init(void)
Input  Param   :
Output  Param  :
Return  Value  :
******************************************************************************/
int  hw_wifi_freq_ctrl_init(void)
{
    int ret;
    /*start cumulate rx tx bytes, record the first start time*/
    pre_jiffies = jiffies;

    wifi_rxtx_tot = 0;
    lf_dbg("hw_wifi_freq_ctrl_init enter\n");
    /*init frequency lock control module.*/
    freq_lock_control_ptr = kzalloc(sizeof(freq_lock_control_t), GFP_KERNEL);
    if (!freq_lock_control_ptr) {
        HW_PRINT_HI("hw_wifi_wifi_freq_ctl_init kzalloc error!\n");
        goto out;
    }

    ret = get_rate_freq_data_from_dts();
    if(ret != 0) {
        HW_PRINT_HI("Can not get transfer rate and CPU/DDR freq table\n");
        goto cleanup;
    }

    mutex_init(&freq_lock_control_ptr->lock_freq_mtx);

    mutex_lock(&freq_lock_control_ptr->lock_freq_mtx);

    spin_lock_init(&freq_lock_control_ptr->speed_calc_lock);

    INIT_WORK(&freq_lock_control_ptr->release_lock_work,
                    hw_wifi_release_freq_lock_work);
    INIT_WORK(&freq_lock_control_ptr->do_freq_lock_work,
                    hw_wifi_do_freq_lock_work);

    setup_timer(&freq_lock_control_ptr->lock_freq_timer_list,
                    hw_wifi_release_freq_lock_timer,
                    (unsigned long) freq_lock_control_ptr);

    freq_lock_control_ptr->freq_ctl_wq =
        create_singlethread_workqueue("wifi_lock_freq");
    if (!freq_lock_control_ptr->freq_ctl_wq) {
        HW_PRINT_HI("hw_wifi_wifi_freq_ctl_init  create_singlethread_workqueue  error!\n");
        mutex_unlock(&freq_lock_control_ptr->lock_freq_mtx);
        goto cleanup;
    }

    add_ddr_request();

    get_cpu_freq_raw(SCALING_MIN_FREQ, &orig_cpu_min_freq);
    get_cpu_freq_raw(SCALING_MAX_FREQ, &orig_cpu_max_freq);
    get_ddr_freq_raw(SCALING_MIN_FREQ, &orig_ddr_min_freq);
    get_ddr_freq_raw(SCALING_MAX_FREQ, &orig_ddr_max_freq);

    mutex_unlock(&freq_lock_control_ptr->lock_freq_mtx);
    lf_dbg("hw_wifi_freq_ctrl_init ok!\n");
    return 0;

cleanup:
    kfree(freq_lock_control_ptr);
    freq_lock_control_ptr = NULL;

out:
    if(g_speed_freq_level != NULL) {
        kfree(g_speed_freq_level);
        g_speed_freq_level = NULL;
        g_freq_lock_num = 0;
    }
    return -1;
}

/*****************************************************************************
Description    : Do  workqueue release , mamery freee etc while the WiFi driver closing.
Prototype      : int  hw_wifi_freq_ctrl_destroy(void)
Input  Param   :
Output  Param  :
Return  Value  :
******************************************************************************/
int  hw_wifi_freq_ctrl_destroy(void)
{
    lf_dbg("hw_wifi_freq_ctrl_destroy  enter\n");

    if (NULL == freq_lock_control_ptr) {
        HW_PRINT_HI("freq_lock_control_ptr NULL pointer!\n");
        return 0;
    }

    mutex_lock(&freq_lock_control_ptr->lock_freq_mtx);

    del_timer_sync(&freq_lock_control_ptr->lock_freq_timer_list);

    /*If the Wi-Fi is closing, but the frequency lock release timer is not timeout,
    * must release the lock directly here!*/
    if (FREQ_LOCK_ENABLE == freq_lock_control_ptr->lock_mod) {
        set_cpu_freq(0, FREQ_ORIGINAL);
        set_ddr_freq(0, FREQ_ORIGINAL);
        del_ddr_request();
        freq_lock_control_ptr->lock_mod = FREQ_LOCK_DISABLE;
        lf_dbg("hw_wifi_freq_ctrl_destroy freq lock release here!\n");
    }
    else {
        lf_dbg("hw_wifi_freq_ctrl_destroy freq lock has already been released!\n");
    }

    cancel_work_sync(&freq_lock_control_ptr->release_lock_work);
    cancel_work_sync(&freq_lock_control_ptr->do_freq_lock_work);
    destroy_workqueue(freq_lock_control_ptr->freq_ctl_wq);

    mutex_unlock(&freq_lock_control_ptr->lock_freq_mtx);

    mutex_destroy(&freq_lock_control_ptr->lock_freq_mtx);
    kfree(freq_lock_control_ptr);
    freq_lock_control_ptr = NULL;

    if(g_speed_freq_level != NULL) {
        kfree(g_speed_freq_level);
        g_speed_freq_level = NULL;
        g_freq_lock_num = 0;
    }

    lf_dbg("hw_wifi_freq_ctrl_destroy exit ok!\n");

    return 0;
}

/*****************************************************************************
Description    : Calculate the WiFi throughput base on the duration time length
                 and total transimit and receive data length in this time duration.
                 And check if the throughput reach any of the three frequency
                 control level.
Prototype      : int hw_wifi_speed_calc_process (uint bytes)
Input Param    : total transimit and receive data length in the speed calculation time duration.
Output Param   : None
Return Value   : 0 for success; -1 for error.
******************************************************************************/
static int hw_wifi_speed_calc_process (unsigned long bytes) {
    unsigned long duration;
    unsigned long temp_jiffies;
    unsigned long speed;
    unsigned int level_idx;

    temp_jiffies = jiffies;
    duration = jiffies_to_msecs(temp_jiffies - pre_jiffies);
    /*reset next triger start time record.*/
    pre_jiffies = temp_jiffies;

    /*duration maybe 0, need this check*/
    if (0 == duration) {
        return 0;
    }

    speed = bytes * 8 / duration; /*unit: kbits/s */

    lf_dbg("Speed calc triger in total bytes: %lu,"
                "speed calculation duration: %lu.%lu s,"
                "speed:%lu kbits/s\n",
                bytes, duration/1000, duration%1000, speed);

    if ((g_speed_freq_level == NULL) ||
        (g_freq_lock_num == 0) ) {
        HW_PRINT_HI("Unable to get transfer data, may be is not config is dts\n");
        return 0;
    }

    /* In most condition, the speed will lower than lock level 1,
       so we should try level 1 first.*/
    for (level_idx = 0; level_idx < g_freq_lock_num; level_idx++) {
        if (speed > g_speed_freq_level[level_idx].speed_level) {
            continue;/*try next lock level*/
        } else {
            break;
        }
    }

    if (level_idx > 0) {
        if (NULL == freq_lock_control_ptr) {
            HW_PRINT_HI("hw_wifi_speed_calc_process  NULL point error!\n");
            return -1;
        }

        /* the new frequency lock level is : level_idx */
        freq_lock_control_ptr->req_lock_level = level_idx;
        /* If call hw_wifi_do_freq_lock_work(i) directly,
          fatal error will happen.*/
        if (freq_lock_control_ptr->freq_ctl_wq != NULL) {
            queue_work(freq_lock_control_ptr->freq_ctl_wq,
                    &freq_lock_control_ptr->do_freq_lock_work);
        }
    }

    return 0;
}

/*****************************************************************************
Description    : This function called every rx and tx packet, the effection is very important!!!
Prototype      : int hw_wifi_tx_rx_counter(uint size)
Input  Param   : size:  uint
Output  Param  :
Return  Value  :
******************************************************************************/
int hw_wifi_tx_rx_counter(uint size) {
    unsigned long  tot_bytes = 0;
    if (NULL == freq_lock_control_ptr) {
        lf_dbg("freq_lock_control_ptr is NULL\n");
        return -1;
    }

    /*
     * Should use spin_lock_bh to block softirq.
     * It may cause deadlock by using spin_lock here
     * because softirq can call this function too
     */
    spin_lock_bh(&freq_lock_control_ptr->speed_calc_lock);
    wifi_rxtx_tot += size;
    if (wifi_rxtx_tot > SPEED_CALC_TRIG_VALUE) {
        tot_bytes = wifi_rxtx_tot;
        wifi_rxtx_tot = 0;
    }
    spin_unlock_bh(&freq_lock_control_ptr->speed_calc_lock);

    if (0 != tot_bytes)
        hw_wifi_speed_calc_process(tot_bytes);

    return 0;
}
