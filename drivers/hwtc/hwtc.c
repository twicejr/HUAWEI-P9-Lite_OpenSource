


#include <linux/debugfs.h>
#include <linux/pagemap.h>
#include <linux/linkage.h>
#include <linux/uaccess.h>
#include <linux/kprobes.h>
#include <linux/module.h>
#include <linux/percpu.h>
#include <linux/splice.h>
#include <linux/kdebug.h>
#include <linux/string.h>
#include <linux/rwsem.h>
#include <linux/slab.h>
#include <linux/ctype.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/syscalls.h>
#include <linux/miscdevice.h>
#include <linux/kobject.h>
/* #include <math.h> */
#include <huawei_platform/log/hw_log.h>
#include "hwtc.h"
#include <chipset_common/hwtc/hwtc_kernel.h>


#define HWTC_DEBUG 0

#define FILE_NAME_LEN	64
#define DUMP_BUFFER_LEN 1024
#define FILE_NAME_TAG_OFFSET     4
#define CODE_MOD                 4
#define DMD_REPORTED_MIN_INTERVAL    60000000

#define PATH_ROOT           "/data/hwzd_logs/"
#define PATH_HWTC           "hwtc_log"
#define HWTC_LOG_NAME       "hwtc-log"
#define BETA_DOMESTIC_SYSTEM  "/system/etc/log_collect_service_beta.xml"
#define BETA_DOMESTIC_DATA    "/data/hw_init/system/etc/log_collect_service_beta.xml"
#define BETA_OVERSEA_SYSTEM   "/system/etc/log_collect_service_oversea.xml"
#define BETA_OVERSEA_DATA     "/data/hw_init/system/etc/log_collect_service_oversea.xml"

#define TABLES_TO_ENTRY(table, id) (&(table[HWTC_TABLE((id))].entry[HWTC_INDEX((id))]))

#define HWLOG_TAG HWTC
HWLOG_REGIST();

static struct hwtc_array global_hwtc;
static bool hwtc_is_enable = false;
static struct kobject *hwtc_kobj = NULL;
static struct work_struct hwtc_rpt_wk;
static struct hwtc_dmd_block_ring_t dmd_block_ring;
static struct hwtc_dmd_block_t global_dmd_block[MAX_DMD_BLOCK_COUNT];
static struct dsm_dev dev_hwtc = {
	.name = "dsm_hwtc",
	.device_name = NULL,
	.ic_name = NULL,
	.module_name = NULL,
	.fops = NULL,
	.buff_size = 512,
};

DEFINE_MUTEX(hwtc_types_lock);

struct hwtc_map_table_t map_table[] = {
    {HWTC_TAG_CAMERA,             "CAMERA" },
    {HWTC_TAG_DISPLAY,            "DISPALY"},
    {ALL_TAG,                     "ALL_MODULE"}
};



static uint32_t hwtc_average(struct hwtc_time_t time[], uint32_t count)
{
    uint32_t sum = 0;
    int i;

    if (0 == count) {
        return 0;
    }

    for (i=0; i<count; i++) {
        sum += time[i].time_delta;
    }

    return sum/count;
}

static uint32_t hwtc_variance(struct hwtc_time_t time[], uint32_t count, uint32_t average)
{
    uint32_t variance = 0;
    int i;

    if ((0 == count) || (1 == count)) {
        return 0;
    }

    for (i=0; i<count; i++) {
        variance += (time[i].time_delta - average)*(time[i].time_delta - average);
    }

    return (variance/(count-1)); /* should sqrt() */
}

/*******************************************************************************
Function:       hwtc_entry_statistic
Description:    when a entry is not full, it will statistic part entry's time data
Input:          entry: statistic entry
Output:         statistic data
Return:         -1 : error, 0 : ok
********************************************************************************/
static int hwtc_get_statistic(
    struct hwtc_entry_t *entry,
    struct hwtc_statistic_t *statistic)
{
    struct hwtc_time_t *time = entry->time;
    uint32_t count = entry->time_index;

    statistic->max = entry->max_time_delta;
    statistic->min = entry->min_time_delta;
    statistic->count = count;
    statistic->average = hwtc_average(time, count);
    statistic->variance = hwtc_variance(time, count, statistic->average);

    return 0;
}

/*******************************************************************************
Function:       hwtc_entry_statistic
Description:    when a entry is full,it will statistic entry's time data
Input:          entry: statistic entry
Output:         statistic data
Return:         -1 : error, 0 : ok
********************************************************************************/
static int hwtc_entry_statistic(struct hwtc_entry_t *entry)
{
    struct hwtc_time_t *time = entry->time;
    uint32_t count = entry->time_index;
    struct hwtc_statistic_t *statistic = NULL;

    if (entry->statistic_index < MAX_STATISTIC_RECORD_COUNT) {
        statistic = &entry->statistic[entry->statistic_index];
    } else {
        entry->statistic_index = 0;
        statistic = &entry->statistic[entry->statistic_index];   
    }

    entry->statistic_index++;

    statistic->max = entry->max_time_delta;
    statistic->min = entry->min_time_delta;
    statistic->count = count;
    statistic->average = hwtc_average(time, count);
    statistic->variance = hwtc_variance(time, count, statistic->average);

    return 0;
}

static void __hwtc_array_get(struct hwtc_array *this_tr)
{
    /* WARN_ON(!this_tr->ref); */
    this_tr->ref++;
}

int hwtc_array_get(struct hwtc_array *this_tr)
{
    mutex_lock(&hwtc_types_lock);
    __hwtc_array_get(this_tr);
    mutex_unlock(&hwtc_types_lock);

    return 0;
}

static void __hwtc_array_put(struct hwtc_array *this_tr)
{
    /* WARN_ON(!this_tr->ref); */
    this_tr->ref--;
}

void hwtc_array_put(struct hwtc_array *this_tr)
{
    mutex_lock(&hwtc_types_lock);
    __hwtc_array_put(this_tr);
    mutex_unlock(&hwtc_types_lock);
}

/*******************************************************************************
Function:       hwtc_open 
Description:    alloc a table for every filp, which be used to save alloc 
                table id value, when this process is killed, it will close
                file node, and release alloc table entry as backup id.
Return:         -1 : error, 0 : ok
********************************************************************************/
static int hwtc_open(struct inode *inode, struct file *filp)
{
    struct hwtc_private_data_t *pd = NULL;
    int ret = 0;

    if (hwtc_array_get(&global_hwtc) < 0)
        return -ENODEV;

    pd = (struct hwtc_private_data_t*)kmalloc(sizeof(struct hwtc_private_data_t), GFP_KERNEL);
    if (NULL == pd) {
        hwlog_err("%s failed to alloc hwtc_private_data_t.\n", __func__);
        ret = -ENOMEM;
        goto err1;
    }

    pd->id_tbl = (uint32_t*)kmalloc(sizeof(uint32_t)*ID_TABLE_SIZE, GFP_KERNEL);
    if (NULL == pd->id_tbl) {
        hwlog_err("%s failed to alloc id table.\n", __func__);
        ret = -ENOMEM;
        goto err2;
    }

    pd->size = ID_TABLE_SIZE;
    pd->index = 0;
    pd->private = &global_hwtc;

    filp->private_data = pd;
    return 0;

    err2:
    kfree(pd);
    err1:
    return ret;
}

static int hwtc_release(struct inode *inode, struct file *filp)
{
    struct hwtc_private_data_t *pd = filp->private_data;
    struct hwtc_array *tr = (struct hwtc_array*)pd->private;
    int i;

    for (i=0; i<pd->index; i++) {
#if HWTC_DEBUG
        hwlog_info("%s id(%d).\n", __func__, pd->id_tbl[i]);
#endif
        memset(&tr->table[0].entry[pd->id_tbl[i]],
                0, sizeof(struct hwtc_entry_t));
    }

    hwtc_array_put(tr);
    kfree(pd->id_tbl);
    kfree(pd);

	return 0;
}

/*******************************************************************************
Function:       hwtc_record_id 
Description:    record alloc table id to filp table
Input:          
Output:         
Return:         -1 : error, 0 : ok
********************************************************************************/
static int32_t hwtc_record_id(int32_t id, struct hwtc_private_data_t *pd)
{
    int ret = 0;

    if (NULL == pd) {
        return -1;
    }

    if (pd->index < pd->size) {
        pd->id_tbl[pd->index++] = id;
    } else {
        int32_t *temp_id_tbl = NULL;
        temp_id_tbl = pd->id_tbl;
        pd->id_tbl = (int32_t*)kmalloc(sizeof(int32_t) * pd->size * 2, GFP_KERNEL);
        if (NULL == pd->id_tbl) {
            hwlog_err("%s failed to alloc id_tbl.\n", __func__);
            ret = -1;
            pd->id_tbl = temp_id_tbl;
        } else {
            memcpy(pd->id_tbl, temp_id_tbl, sizeof(int32_t)*pd->size);
            kfree(temp_id_tbl);
            pd->size *= 2;
            pd->id_tbl[pd->index++] = id;
        }
    }
    return ret;
}

/*******************************************************************************
Function:       hwtc_alloc 
Description:    alloc a entry from alloc table
Input:          tbl: alloc table
Output:         NA
Return:         -1 : error, >0 : valid alloc table id
********************************************************************************/
static int32_t hwtc_alloc(
    struct hwtc_table_t *tbl,
    struct hwtc_info_t *info,
    char **pname,
    struct hwtc_private_data_t *pd)
{
    int32_t id = -1;
    int32_t index;

    mutex_lock(&tbl->lock);
    if (tbl->index < MAX_ENTRY_COUNT) {
        *pname = tbl->entry[tbl->index].name[0];
        tbl->entry[tbl->index].threshold = info->threshold;
        tbl->entry[tbl->index].tag = info->tag;
        tbl->entry[tbl->index].use = BE_USE;
        id = tbl->index++;
        if (NULL != pd) {
            hwtc_record_id(id, pd);
        }
    } else {
        for (index=0; index<MAX_ENTRY_COUNT; index++) {
            if (0 == tbl->entry[index].use) {
                id = index;
                break;
            }
        }

        if (MAX_ENTRY_COUNT == index) {
            hwlog_warn("%s failed to allocate entry, table index(%d).\n",
                        __func__, tbl->index);
        } else {
            if (NULL != pd) {
                hwtc_record_id(id, pd);
            }
        }
    }
    mutex_unlock(&tbl->lock);

    return id;
}

/*******************************************************************************
Function:       hwtc_setup 
Description:    setup a entry in static table according to define id value
Input:          tbl: static table
                info: include define id
Output:         output pname pointer to entry's name item
Return:         -1 : error, 0 : ok
********************************************************************************/
static int32_t hwtc_setup(
    struct hwtc_table_t *tbl,
    struct hwtc_info_t *info,
    char **pname)
{
    if (MAX_ENTRY_COUNT <= HWTC_INDEX(info->id)) {
        hwlog_warn("%s failed to setup entry, table index(%d).\n",
                        __func__, HWTC_INDEX(info->id));
        return -1;
    }

    *pname = tbl->entry[HWTC_INDEX(info->id)].name[HWTC_BE(info->id)];
    if (!HWTC_BE(info->id)) {
        tbl->entry[HWTC_INDEX(info->id)].tag = info->tag;
        tbl->entry[HWTC_INDEX(info->id)].threshold = info->threshold;
    }
    tbl->entry[HWTC_INDEX(info->id)].use |= (1 << HWTC_BE(info->id));
    return info->id;
}

static void hwtc_report_work(struct work_struct *work)
{
    struct dsm_client *client_dev = global_hwtc.dclient;
    if(!dsm_client_ocuppy(client_dev)) {
        dsm_client_notify(client_dev, DSM_HWTC_ERROR_NO);
    }
}

static bool hwtc_dmd_report_judge(struct hwtc_entry_t *entry)
{
    struct hwtc_time_t *pre_time = NULL;
    struct hwtc_time_t *cur_time = NULL;
    int i;
    uint32_t time_delta;
    bool ret = false;

    cur_time = &entry->time[entry->time_index];
    i = (entry->time_index + MAX_TIME_RECORD_COUNT - 1) % MAX_TIME_RECORD_COUNT;
    for (; i != entry->time_index; i = ((i + MAX_TIME_RECORD_COUNT - 1) % MAX_TIME_RECORD_COUNT)) {
        pre_time = &entry->time[i];
        if (0 != pre_time->dmd_reported) {
            time_delta = (cur_time->time[1].tv_sec*USEC_PER_SEC + cur_time->time[1].tv_usec)
            - (pre_time->time[1].tv_sec*USEC_PER_SEC + pre_time->time[1].tv_usec);
            hwlog_info("%s time_delta: %d\n", __func__, time_delta);
            if (time_delta < DMD_REPORTED_MIN_INTERVAL) {
                ret = true;
                break;
            }
        }
    }
    return ret;
}

static bool hwtc_dmd_data_handle(struct hwtc_entry_t *entry, int32_t output)
{
    uint32_t index;
    uint32_t tag = entry->tag;
    bool ret = true;

    hwlog_info("%s called\n", __func__);
    /* if time interval after last time this error reported < 1 min, discard it */
    if (hwtc_dmd_report_judge(entry) == true) {
        return false;
    }
    mutex_lock(&dmd_block_ring.lock);
    /* if count reach MAX limit, do nothing */
    if (dmd_block_ring.block_count >=  MAX_DMD_BLOCK_COUNT) {
        hwlog_warn("%s dmd block count exceed the max value.\n", __func__);
        ret = false;
    } else {
        index = dmd_block_ring.write_p;
        /* copy dmd block data to global_dmd_block[]*/
        global_dmd_block[index].tag = tag;
        strncpy(global_dmd_block[index].module_name, map_table[tag-1].name,
                sizeof(global_dmd_block[index].module_name) - 1);
        strncpy(global_dmd_block[index].function_name, entry->name[0],
                sizeof(global_dmd_block[index].function_name) - 1);
        global_dmd_block[index].threshold = entry->threshold;
        global_dmd_block[index].output = output;
        entry->time[entry->time_index].dmd_reported = 1;
        memcpy(global_dmd_block[index].time, entry->time, sizeof(entry->time));
        dmd_block_ring.write_p = (dmd_block_ring.write_p + 1) % MAX_DMD_BLOCK_COUNT;
        dmd_block_ring.block_count++;
        hwlog_info("%s cout = %d, write_p = %d\n", __func__, dmd_block_ring.block_count, dmd_block_ring.write_p);
    }
    mutex_unlock(&dmd_block_ring.lock);

    return ret;
}

/*******************************************************************************
Function:       hwtc_mark 
Description:    mark timestamp to entry
Input:          tbl: counter table
                id: table id
                output: output info
Return:         -1 : error, 0 : ok
********************************************************************************/
static int32_t hwtc_mark(
    struct hwtc_table_t *tbl,
    int32_t id,
    int32_t output)
{
    struct hwtc_entry_t *entry = &tbl->entry[HWTC_INDEX(id)];
    uint32_t time_index = entry->time_index;
    uint32_t time_delta;
    uint32_t threshold = entry->threshold;

    if (MAX_ENTRY_COUNT <= HWTC_INDEX(id)) {
        hwlog_warn("%s failed to mark entry, id(0x%x).\n", __func__, id);
        return -1;
    }

    do_gettimeofday(
            &entry->time[time_index].time[HWTC_BE(id)]);

#if HWTC_DEBUG
    hwlog_info("%s name:%s,id:0x%x, time:%ld.%ld.\n",
            __func__, tbl->entry[HWTC_INDEX(id)].name, id,
            tbl->entry[HWTC_INDEX(id)].time[time_index].time[HWTC_BE(id)].tv_sec,
            tbl->entry[HWTC_INDEX(id)].time[time_index].time[HWTC_BE(id)].tv_usec);
#endif

    if (HWTC_BE(id)) {
        time_delta = (entry->time[time_index].time[1].tv_sec*USEC_PER_SEC
            + entry->time[time_index].time[1].tv_usec)
            - (entry->time[time_index].time[0].tv_sec*USEC_PER_SEC
            + entry->time[time_index].time[0].tv_usec);

        entry->time[time_index].time_delta = time_delta;
        entry->time[time_index].dmd_reported = 0;
        entry->output[time_index] = output;

        if (0 == entry->time_index) {
            entry->max_time_delta = time_delta;
            entry->min_time_delta = time_delta;
        } else {
            if (entry->max_time_delta < time_delta) {
                entry->max_time_delta = time_delta;
            }

            if (entry->min_time_delta > time_delta) {
                entry->min_time_delta = time_delta;
            }
        }

        if (threshold != 0 && (output != 0 || time_delta > threshold)) {
            if (hwtc_dmd_data_handle(entry,output)){
                schedule_work(&hwtc_rpt_wk);
            }
        }

        entry->time_index++;
        if (MAX_TIME_RECORD_COUNT == entry->time_index) {
            hwtc_entry_statistic(entry);
            entry->time_index = 0;
        }
    }
    return 0;
}

static ssize_t
hwtc_write(struct file *filp, const char __user *ubuf,
            size_t cnt, loff_t *ppos)
{
    struct hwtc_private_data_t *pd = (struct hwtc_private_data_t *)filp->private_data;
    struct hwtc_array *tr = (struct hwtc_array*)pd->private;
    unsigned long addr = (unsigned long)ubuf;
    struct hwtc_entry_t *entry = NULL;
    struct hwtc_info_t info = {0};
    char buffer[MAX_ID_SIZE] = {0};
    struct page *pages[2];
    void *map_page[2];
    int nr_pages = 1;
    int offset;
    int ret = 0;
    char *pname = NULL;
    char *iendp;
    char *tendp;

    int len;
    int i;

    if (cnt > MAX_NAME_SIZE) {
        cnt = MAX_NAME_SIZE;
    }

    BUILD_BUG_ON(MAX_NAME_SIZE >= PAGE_SIZE);

    /* check if we cross pages */
    if ((addr & PAGE_MASK) != ((addr + cnt) & PAGE_MASK)) {
        nr_pages = 2;
    }

    offset = addr & (PAGE_SIZE - 1);
    addr &= PAGE_MASK;

    ret = get_user_pages_fast(addr, nr_pages, 0, pages);
    if (ret < nr_pages) {
        while (--ret >= 0) {
            put_page(pages[ret]);
        }
        return -EFAULT;
    }

    for (i = 0; i < nr_pages; i++) {
        map_page[i] = kmap_atomic(pages[i]);
    }

    preempt_disable_notrace();

    if (nr_pages == 2) {
        len = PAGE_SIZE - offset;

        if (len >= MAX_ID_SIZE) {
            memcpy(buffer, map_page[0] + offset, MAX_ID_SIZE);
        } else {
            memcpy(buffer, map_page[0] + offset, len);
            memcpy(&buffer[len], map_page[1], MAX_ID_SIZE - len);
        }
    } else {
        memcpy(buffer, map_page[0] + offset, MAX_ID_SIZE);
    }

    info.id = (int32_t)simple_strtoul(&buffer[2], &iendp, 16);

    if (HWTC_INVALID_ID == HWTC_INDEX(info.id)) {
        info.tag = simple_strtoul(iendp+1, &tendp, 0);
        info.threshold = simple_strtoul(tendp+1, NULL, 0);
        info.id = hwtc_alloc(&tr->table[0], &info, &pname, pd);
    } else {
        entry = TABLES_TO_ENTRY(tr->table, info.id);
        if (0 == (0x01 & (entry->use >> HWTC_BE(info.id)))) {
            info.tag = simple_strtoul(iendp+1, &tendp, 0);
            if (HWTC_BE(info.id)) {
                info.output = simple_strtoul(tendp+1, NULL, 0);
            } else {
                info.threshold = simple_strtoul(tendp+1, NULL, 0);
            }
            info.id = hwtc_setup(&tr->table[HWTC_TABLE(info.id)], &info, &pname);
        } else {
            info.tag = simple_strtoul(iendp+1, &tendp, 0);
            info.output = simple_strtoul(tendp+1, NULL, 0);
        }
    }

    if (NULL != pname) {
        if (nr_pages == 2) {
            len = PAGE_SIZE - offset;
            memcpy(pname, map_page[0] + offset, len);
            memcpy(pname, map_page[1], cnt - len);
        } else {
            memcpy(pname, map_page[0] + offset, cnt);
        }

        if (pname[cnt - 1] != '\n') {
            pname[cnt] = '\n';
            pname[cnt + 1] = '\0';
        } else {
            pname[cnt] = '\0';
        }
    }
    hwtc_mark(&tr->table[HWTC_TABLE(info.id)], info.id, info.output);

    preempt_enable_notrace();

    for (i = nr_pages - 1; i >= 0; i--) {
        kunmap_atomic(map_page[i]);
        put_page(pages[i]);
    }

    return (ssize_t)info.id;
}

/*******************************************************************************
Function:       hwtc_dump_entry
Description:    dump counter table's entry to log file which is decided by fd.
Input:          fd:  dump log file fd.
                entry: dump entry.
Output:         NA
Return:         -1 : error, 0 : ok
********************************************************************************/
static int hwtc_dump_entry(long fd, struct hwtc_entry_t *entry)
{
    char buffer[DUMP_BUFFER_LEN] = {0};
    struct hwtc_time_t *time;
    struct hwtc_statistic_t statistic;
    struct hwtc_statistic_t *pstatistic;
    int i,k,s;
    int len;

    len = snprintf(buffer, DUMP_BUFFER_LEN, "\nB:%sE:%s", entry->name[0],
                (entry->name[1][0] == '\0' ? "NA\n" : entry->name[1]));

    sys_write(fd, buffer, len);

    k = (entry->time_index + MAX_TIME_RECORD_COUNT - 1) % MAX_TIME_RECORD_COUNT;
    for (i = 0; i < MAX_TIME_RECORD_COUNT; i++) {
        time = &entry->time[k];
        if (0 != time->time_delta) {
            len = snprintf(buffer, DUMP_BUFFER_LEN, "B:%ld.%06ld s, E:%ld.%06ld s, Delta:%u us, Output:%d.\n",
                        time->time[0].tv_sec, time->time[0].tv_usec,
                        time->time[1].tv_sec, time->time[1].tv_usec,
                        time->time_delta, entry->output[k]);
            sys_write(fd, buffer, len);
        }
        k = (k + MAX_TIME_RECORD_COUNT - 1) % MAX_TIME_RECORD_COUNT;
    }

    if (entry->time_index != 0) {
        pstatistic = &statistic;
        hwtc_get_statistic(entry, pstatistic);
        len = snprintf(buffer, DUMP_BUFFER_LEN, "COUNT:%u, AVG:%u, VAR:%u, MAX:%u, MIN:%u.\n",
                            pstatistic->count, pstatistic->average, pstatistic->variance, pstatistic->max, pstatistic->min);
        sys_write(fd, buffer, len);
    }

    s = (entry->statistic_index + MAX_STATISTIC_RECORD_COUNT -1) % MAX_STATISTIC_RECORD_COUNT;
    for (i = 0; i < MAX_STATISTIC_RECORD_COUNT; i++) {
        pstatistic = &entry->statistic[s];
        if (0 != pstatistic->count) {
            len = snprintf(buffer, DUMP_BUFFER_LEN, "COUNT:%u, AVG:%u, VAR:%u, MAX:%u, MIN:%u.\n",
                        pstatistic->count, pstatistic->average, pstatistic->variance, pstatistic->max, pstatistic->min);
            sys_write(fd, buffer, len);
        }
        s = (s + MAX_TIME_RECORD_COUNT - 1) % MAX_TIME_RECORD_COUNT;
    }

    return 0;
}

/*******************************************************************************
Function:       hwtc_dump
Description:    dump counter table to log file as tag.
Input:          tr:  dump counter table array.
                tag: it will decide to dump which entry.
Output:         NA
Return:         -1 : error, 0 : ok
********************************************************************************/
static int hwtc_dump(struct hwtc_array *tr, uint32_t tag, uint32_t code)
{
    struct hwtc_table_t *ptbl = NULL;
    char file_name[FILE_NAME_LEN];
    char exce_dir[FILE_NAME_LEN] = "";
    mm_segment_t fs;
    long fd;
    int ret = 0;
    int i,j;

    fs = get_fs();
    set_fs(KERNEL_DS);

    snprintf(exce_dir, FILE_NAME_LEN, "%s%s/", PATH_ROOT, PATH_HWTC);

    fd = sys_open(exce_dir, O_DIRECTORY, 0);

    /* if dir is not exist,then create new dir */
    if (fd < 0) {
        fd  = sys_mkdir(exce_dir, 0775);
        if (fd < 0) {
            hwlog_err("%s failed to mkdir %s, fd(%ld)\n", __func__, exce_dir, fd);
            return fd;
        }
    }
    else {
        sys_close(fd);
    }

    snprintf(file_name, FILE_NAME_LEN, "%s%s.%d", exce_dir, HWTC_LOG_NAME, ((tag<<FILE_NAME_TAG_OFFSET) | code));
    fd = sys_open(file_name, O_CREAT|O_WRONLY|O_TRUNC, 0664);
    if (fd < 0) {
        hwlog_err("%s failed to open %s.", __func__, file_name);
        ret = -1;
        set_fs(fs);
        return ret;
    }

    /* dump table entry */
    for (i=0; i<HWTC_CTBL_MAX; i++) {
        ptbl = &tr->table[i];
        for (j=0; j<MAX_ENTRY_COUNT; j++) {
            if ((HWTC_MAIN_TAG(ptbl->entry[j].tag) == HWTC_MAIN_TAG(tag)) || (ALL_TAG == tag)) {
                hwtc_dump_entry(fd, &ptbl->entry[j]);
            }
        }
    }

    sys_close(fd);

    set_fs(fs);
    return ret;
}

static const struct file_operations hwtc_fops = {
    .open       = hwtc_open,
    .read       = NULL,
    .llseek     = NULL,
    .release    = hwtc_release,
    .write      = hwtc_write,
};

/*******************************************************************************
Function:       hwtc_dump_store
Description:    control interface which dump table entry statistic info
Input:          buf: input tag value, dump this tag entry statistic info,
                if tag is 0xffffffff, it will dump all entry statistic info
Return:         <0 : error, >0 : ok
********************************************************************************/
static ssize_t hwtc_dump_store(struct device *dev,
                                struct device_attribute *attr,
                                const char *buf, size_t cnt)
{
    uint32_t tag = 0;
    uint32_t code = 0;
    int ret;
    int i;

    if (NULL == buf) {
        return -EINVAL;
    }

    for (i=0; i<sizeof(map_table)/sizeof(map_table[0]); i++) {
        if (!strncmp(map_table[i].name, buf, strlen(map_table[i].name))) {
            tag = map_table[i].tag;
            code = map_table[i].code;
            map_table[i].code = (code + 1) % CODE_MOD;
        }
    }

#if HWTC_DEBUG
    hwlog_info("%s tag(0x%x).\n", __func__, tag);
#endif
    if (!tag) {
        return -EFAULT;
    }

    ret = hwtc_dump(&global_hwtc, tag, code);
    if (ret < 0) {
        hwlog_err("%s failed to dump hwtc log.\n", __func__);
        return ret;
    }

    return ((tag<<FILE_NAME_TAG_OFFSET) | code);
}

/*******************************************************************************
Function:       hwtc_dmd_dump_show
Description:    read interface for dmd dump
Input:          
Return:         0 : no data , >0 : count of read number, <0: read error
********************************************************************************/
static ssize_t hwtc_dmd_dump_show(struct device *dev,
                                   struct device_attribute *attr,
                                   char *buf)
{
    int ret = 0;

    hwlog_info("%s called\n", __func__);
    mutex_lock(&dmd_block_ring.lock);
    if (dmd_block_ring.block_count > 0) {
        memcpy(buf, &global_dmd_block[dmd_block_ring.read_p], sizeof(struct hwtc_dmd_block_t));
        ret = sizeof(struct hwtc_dmd_block_t);
        dmd_block_ring.block_count--;
        dmd_block_ring.read_p = (dmd_block_ring.read_p + 1) % MAX_DMD_BLOCK_COUNT;
        hwlog_info("%s cout = %d, read_p = %d\n", __func__, dmd_block_ring.block_count, dmd_block_ring.read_p);
    }
    mutex_unlock(&dmd_block_ring.lock);

    return ret;
}

/*******************************************************************************
Function:       hwtc_enable_show
Description:    read interface for hwtc enable
********************************************************************************/
static ssize_t hwtc_enable_show(struct device *dev,
                                   struct device_attribute *attr,
                                   char *buf)
{
    hwlog_info("%s called hwtc_is_enable = %d\n", __func__, hwtc_is_enable);
    return snprintf(buf, 4, "%d\n", hwtc_is_enable);
}

/*******************************************************************************
Function:       hwtc_enable_store
Description:    control interface for init to check bata version
********************************************************************************/
static ssize_t hwtc_enable_store(struct device *dev,
                                struct device_attribute *attr,
                                const char *ubuf, size_t cnt)
{
    mm_segment_t old_fs;

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    if ((sys_access(BETA_OVERSEA_SYSTEM, O_RDONLY) < 0) &&
        (sys_access(BETA_OVERSEA_DATA, O_RDONLY) < 0)) {
        if ((sys_access(BETA_DOMESTIC_SYSTEM, O_RDONLY) == 0) ||
            (sys_access(BETA_DOMESTIC_DATA, O_RDONLY) == 0)) {
            hwlog_info("%s this version is domestic beta version.\n", __func__);
            hwtc_is_enable = true;
        }
    }
    set_fs(old_fs);
    return cnt;
}
/*******************************************************************************
Function:       hwtc_record 
Description:    use to record timestamp in kernel function
Input:          tag: module tag value, use to distinguish module
                name: function name
                id: table id
                input: when call in hwtc_begin, it should be time diff threshold,
                           when time diff reach this threshold,it may do error process
                           when call in hwtc_end, it should be the output info
Return:         -1 : error, >0 : ok
********************************************************************************/
static int32_t
hwtc_record(uint32_t tag, const char *name, int32_t id,
    int32_t input)
{
    struct hwtc_array *tr = (struct hwtc_array*)&global_hwtc;
    struct hwtc_info_t info = {0};
    struct hwtc_entry_t *entry = NULL;
    char *pname = NULL;
    int cnt;

    preempt_disable_notrace();

    info.id = id;
    if (HWTC_BE(info.id)) {
        info.output = input;
    }

    if (HWTC_INVALID_ID == HWTC_INDEX(info.id)) {
        info.tag = tag;
        info.threshold = input;
        info.id = hwtc_alloc(&tr->table[0], &info, &pname, NULL);
    } else {
        entry = TABLES_TO_ENTRY(tr->table, info.id);
        if (0 == (0x01 & (entry->use >> HWTC_BE(info.id)))) {
            info.tag = tag;
            info.threshold = input;
            info.id = hwtc_setup(&tr->table[HWTC_TABLE(info.id)], &info, &pname);
        }
    }

    if (NULL != pname) {
        cnt = strlen(name);
        if (cnt > MAX_NAME_SIZE) {
            cnt = MAX_NAME_SIZE;
        }
        memcpy(pname, name, cnt);

        if (pname[cnt - 1] != '\n') {
            pname[cnt] = '\n';
            pname[cnt + 1] = '\0';
        } else {
            pname[cnt] = '\0';
        }
    }

    hwtc_mark(&tr->table[HWTC_TABLE(info.id)], info.id, info.output);

    preempt_enable_notrace();

    return info.id;
}

void
hwtc_begin(uint32_t tag, const char *name, int32_t *id,
    uint32_t threshold)
{
    char buf[MAX_NAME_SIZE];
    int32_t ret;

    if (unlikely(0 == tag)) {
        return;
    }

    if (hwtc_is_enable) {
        HWTC_SET_BEGIN(*id);
        snprintf(buf, MAX_NAME_SIZE, "0x%x|0x%x|%d|pid(%ld)|%s", *id, tag, threshold, sys_getpid(), name);
        ret = hwtc_record(tag, buf, *id, threshold);
        if (ret < 0) {
            hwlog_warn("%s faild to hwtc record, ret(%d).\n", __func__, ret);
        } else {
            *id = ret;
        }   
    }
}

void
hwtc_end(uint32_t tag, const char *name, int32_t *id, int32_t *output)
{
    char buf[MAX_NAME_SIZE];
    int32_t ret;

    if (unlikely(0 == tag)) {
        return;
    }

    if (hwtc_is_enable) {
        HWTC_SET_END(*id);
        snprintf(buf, MAX_NAME_SIZE, "0x%x|0x%x|0x%x|pid(%ld)|%s", *id, tag, *output,sys_getpid(), name);
        ret = hwtc_record(tag, buf, *id, *output);
        if (ret < 0) {
            hwlog_warn("%s faild to hwtc record, ret(%d).\n", __func__, ret);
        } else {
            *id = ret;
        }
    }
}

static struct miscdevice hwtc_dev = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "hwtc",
    .fops = &hwtc_fops
};

/* used for jank to dump hwtc data */
static struct device_attribute hwtc_dump_attr =
__ATTR(hwtc_dump, 0220, NULL, hwtc_dump_store);

/* used for dmd to dump hwtc data */
static struct device_attribute hwtc_dmd_dump_attr =
__ATTR(hwtc_dmd_dump, 0440, hwtc_dmd_dump_show, NULL);

/* used for init to check bata version */
static struct device_attribute hwtc_enable_attr =
__ATTR(hwtc_enable, 0660, hwtc_enable_show, hwtc_enable_store);

static struct attribute *hwtc_attributes[] = {
    &hwtc_dump_attr.attr,
    &hwtc_dmd_dump_attr.attr,
    &hwtc_enable_attr.attr,
    NULL
};

static const struct attribute_group hwtc_attr_group = {
    .attrs = hwtc_attributes,
};

static int hwtc_init_data(struct hwtc_array *tr)
{
    int i;

    hwlog_info("hwtc counter table size is %ld bytes.\n", sizeof(struct hwtc_array));

    for (i=0; i<HWTC_CTBL_MAX; i++) {
        mutex_init(&tr->table[i].lock);
    }

    return 0;
}

static void hwtc_dmd_init_data(void)
{
    dmd_block_ring.write_p = 0;
    dmd_block_ring.read_p = 0;
    dmd_block_ring.block_count = 0;
    mutex_init(&dmd_block_ring.lock);
    INIT_WORK(&hwtc_rpt_wk, hwtc_report_work);
    global_hwtc.dclient = dsm_register_client(&dev_hwtc);
}

static __init int hwtc_module_init(void)
{
    hwlog_info("%s: enter\n", __func__);
    hwtc_init_data(&global_hwtc);

    /* Register sysfs hooks */
    hwtc_kobj = kobject_create_and_add("hwtc", kernel_kobj);
    if (!hwtc_kobj) {
        hwlog_err("%s: Could not create kobject for hwtc\n", __func__);
        return -ENOMEM;
    }

    if (sysfs_create_group(hwtc_kobj, &hwtc_attr_group)) {
        hwlog_err("%s: Could not create attr group for hwtc\n", __func__);
        kobject_put(hwtc_kobj);
        return -ENOMEM;
    }

    /* to register hwtc as a misc device */
    if (misc_register(&hwtc_dev) != 0) {
        hwlog_err("%s: Could not register misc. dev for hwtc\n", __func__);
        sysfs_remove_group(hwtc_kobj, &hwtc_attr_group);
        kobject_put(hwtc_kobj);
        return -1;
    }
    hwtc_dmd_init_data();
    return 0;
}

static void __exit hwtc_module_exit(void)
{
    sysfs_remove_group(hwtc_kobj, &hwtc_attr_group);
    kobject_put(hwtc_kobj);
    misc_deregister(&hwtc_dev);
    mutex_destroy(&dmd_block_ring.lock);

}

module_init(hwtc_module_init);
module_exit(hwtc_module_exit);
MODULE_AUTHOR("huawei");
MODULE_DESCRIPTION("hwtc device");
MODULE_LICENSE("GPL");
