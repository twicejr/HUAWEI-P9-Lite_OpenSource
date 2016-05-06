

#ifndef _NV_DEBUG_H_
#define _NV_DEBUG_H_


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define NV_DUMP_SIZE     (4*1024)


enum nv_debug_delta_e
{
    NV_DEBUG_DELTA_WRITE_FILE   = 0,    /*写文件系统最大时长*/
    NV_DEBUG_DELTA_GET_IPC      = 1,    /*获取IPC锁最大时长*/
    NV_DEBUG_DELTA_BUTT
};
enum{
    NV_DEBUG_WRITEEX_START = 1,
    NV_DEBUG_WRITEEX_GET_IPC_START = 2,
    NV_DEBUG_WRITEEX_GET_IPC_END = 3,
    NV_DEBUG_WRITEEX_GIVE_IPC = 4,
    NV_DEBUG_WRITEEX_MEM_START = 5,
    NV_DEBUG_WRITEEX_FILE_START = 6,
    NV_DEBUG_FLUSH_START = 7,
    NV_DEBUG_FLUSH_END = 8,
    NV_DEBUG_REQ_FLUSH_START = 9,
    NV_DEBUG_REQ_FLUSH_END = 10,
    NV_DEBUG_FLUSHEX_START = 11,
    NV_DEBUG_FLUSHEX_OPEN_START = 12,
    NV_DEBUG_FLUSHEX_OPEN_END = 13,
    NV_DEBUG_FLUSHEX_GET_PROTECT_SEM_START = 14,
    NV_DEBUG_FLUSHEX_GET_PROTECT_SEM_END = 15,
    NV_DEBUG_FLUSHEX_GIVE_IPC = 16,
    NV_DEBUG_FLUSHEX_GIVE_SEM = 17,
    NV_DEBUG_FLUSHEX_WRITE_FILE_START = 18,
    NV_DEBUG_FLUSHEX_WRITE_FILE_END = 19,
    NV_DEBUG_WRITEEX_END = 20,
    NV_DEBUG_RECEIVE_ICC = 21,
    NV_DEBUG_SEND_ICC = 22,
    NV_DEBUG_READ_ICC = 23,
    NV_DEBUG_BUTT
};
typedef struct nv_queue_elemnt_str
{
    u32 state;
    u32 slice;
}nv_queue_elemnt;

typedef struct
{
    u32 maxNum;
    u32 front;
    u32 rear;
    u32 num;
    nv_queue_elemnt data[1];
} dump_queue_t;

typedef struct
{
    u32 state;
    char *info;
}debug_table_t;

union debug_ctrl_union
{
    u32 value;
    struct ctrl_bits_stru
    {
        u32 write_print_ctrl    :1;     /*写NV过程是否打印,1 打印 0 不打印*/
        u32 write_dump_ctrl     :1;     /*写NV过程是否记录到dump中,1 记录 0 不记录*/
        u32 reserved            :29;
    }ctrl_bits;
};

struct nv_debug_stru
{
    dump_queue_t *          nv_dump_queue;
    debug_table_t *         write_debug_table;
    union debug_ctrl_union  debug_ctrl;
    u32                     delta_time[NV_DEBUG_DELTA_BUTT];
};


u32 nv_debug_init(void);
void nv_debug_record(u32 current_state);
void nv_debug_print_dump_queue(void);
void nv_debug_record_delta_time(u32 type, u32 start, u32 end);
void nv_debug_print_delta_time();
u32 nv_debug_switch(u32 value);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /*_NV_DEBUG_H_*/

