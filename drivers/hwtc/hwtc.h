


#ifndef __HWTC_H__
#define __HWTC_H__

#include <linux/types.h>
#include <linux/time.h>
#include <linux/fs.h>
#include <linux/atomic.h>
#include <linux/sched.h>
#include <linux/workqueue.h>
#include <dsm/dsm_pub.h>


#define MAX_TAG_SIZE                64
#define MAX_NAME_SIZE               256
#define NAME_SIZE_PAD               2
#define MAX_TIME_RECORD_COUNT       10
#define MAX_STATISTIC_RECORD_COUNT  5
#define MAX_ENTRY_COUNT             500
#define MAX_ID_SIZE                 40
#define ID_TABLE_SIZE               100
#define MAX_DMD_BLOCK_COUNT         10
#define DSM_HWTC_ERROR_NO           22500

#ifndef USEC_PER_SEC
#define USEC_PER_SEC                1000000
#endif

/****************************************************
 * id mean:
 * bit[31]    : 1:fail or initilization , 0:success;
 * bit[30]    : begin/end time flag,
 *              the value is 0:begin,1:end;
 * bit[29:28]    : trace counter table type,
 *              the value is in enum hwtc_table_type;
 ****************************************************/
#define HWTC_INDEX(id)                          ((id) & 0x0FFFFFFF)
#define HWTC_TABLE(id)                          (((id) >> 28) & 0x03)
#define HWTC_BE(id)                             (((id) >> 30) & 0x01)
#define HWTC_INITILIZATION(id)                  (((id) >> 31) & 0x01)
#define HWTC_INITILIZATION_CLEAR(id)            ((id) &= ~(1 << 31))

#define HWTC_SET_BEGIN(id)                      ((id) &= ~(1 << 30))
#define HWTC_SET_END(id)                        ((id) |= (1 << 30))

#define HWTC_INVALID_ID                                  (0x0FFFFFFF)

#define HWTC_MAIN_TAG(tag)                               ((tag)>>0)

#define BE_USE                                              (0x3)
#define ALL_TAG                                             (0xFFFFFFFF)



/* HUAWEI TRACE COUNTER TABLE TYPE DEFINE */
enum hwtc_table_type_t {
    HWTC_CTBL_ALLOC          = 0,
    HWTC_CTBL_LOW            = 1, //for framework, hal and kernel
    HWTC_CTBL_HIGH           = 2, //for java layer
    HWTC_CTBL_SUPER          = 3,
    HWTC_CTBL_MAX
};

struct hwtc_time_t {
    struct timeval time[2];
    uint32_t time_delta;  /* in us */
    uint32_t dmd_reported;
};

struct hwtc_statistic_t {
    uint32_t average;
    uint32_t variance;
    uint32_t min;
    uint32_t max;
    uint32_t count;
};

struct hwtc_entry_t {
    char name[2][MAX_NAME_SIZE+NAME_SIZE_PAD];
    struct hwtc_time_t time[MAX_TIME_RECORD_COUNT];
    struct hwtc_statistic_t statistic[MAX_STATISTIC_RECORD_COUNT];
    struct hwtc_statistic_t total_statistic;
    int32_t output[MAX_TIME_RECORD_COUNT];
    uint32_t max_time_delta;       /* in us */
    uint32_t min_time_delta;       /* in us */
    uint32_t time_index;
    uint32_t statistic_index;
    uint32_t threshold;
    uint32_t tag;
    uint8_t use;
};

struct hwtc_table_t {
    struct hwtc_entry_t entry[MAX_ENTRY_COUNT];
    int32_t  index;
    struct mutex lock;
};

struct hwtc_array {
    int    ref;
    struct dsm_client *dclient;
    struct hwtc_table_t table[HWTC_CTBL_MAX];
};

struct hwtc_info_t {
    uint32_t tag;
    int32_t id;
    uint32_t threshold;
    int32_t output;
};

struct hwtc_private_data_t {
    void *private;
    uint32_t *id_tbl;
    uint32_t index;
    uint32_t size;
};

struct hwtc_map_table_t {
    uint32_t tag;
    const char *name;
    uint32_t code;
};

struct hwtc_dmd_block_t
{
    uint32_t tag;
    char module_name[32];
    char function_name[256];
    uint32_t threshold;
    int32_t  output;
    struct hwtc_time_t time[MAX_TIME_RECORD_COUNT];
};

struct hwtc_dmd_block_ring_t
{
    uint32_t write_p;
    uint32_t read_p;
    uint32_t block_count;
    struct mutex lock;
};


#endif /* __HWTC_H__ */
