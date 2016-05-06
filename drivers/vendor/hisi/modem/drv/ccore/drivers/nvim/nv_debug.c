
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include <securec.h>
#include "bsp_dump.h"
#include "bsp_slice.h"
#include "bsp_nvim.h"
#include "nv_comm.h"
#include "nv_debug.h"

struct nv_debug_stru g_nv_debug_info = {};
debug_table_t g_nv_write_debug_table[NV_DEBUG_BUTT] = {
    {NV_DEBUG_WRITEEX_START,            "write nv start"},
    {NV_DEBUG_WRITEEX_GET_IPC_START,    "for check crc,start to get ipc sem"},
    {NV_DEBUG_WRITEEX_GET_IPC_END,      "get ipc sem end"},
    {NV_DEBUG_WRITEEX_GIVE_IPC,         "check crc end, release ipc sem"},
    {NV_DEBUG_WRITEEX_MEM_START,        "write to mem start"},
    {NV_DEBUG_WRITEEX_FILE_START,       "write to file start"},
    {NV_DEBUG_FLUSH_START,              "flush nv list start"},
    {NV_DEBUG_FLUSH_END,                "flush nv list end"},
    {NV_DEBUG_REQ_FLUSH_START,          "req flush nv list start"},
    {NV_DEBUG_REQ_FLUSH_END,            "req flush nv list end"},
    {NV_DEBUG_FLUSHEX_START,            "flush nv to file start"},
    {NV_DEBUG_FLUSHEX_OPEN_START,       "open nv file start"},
    {NV_DEBUG_FLUSHEX_OPEN_END,          "open nv file end"},
    {NV_DEBUG_FLUSHEX_GET_PROTECT_SEM_START,"before write to file get ipc and sem start"},
    {NV_DEBUG_FLUSHEX_GET_PROTECT_SEM_END,"before write to file get ipc and sem end"},
    {NV_DEBUG_FLUSHEX_GIVE_IPC,         "write to file release ipc"},
    {NV_DEBUG_FLUSHEX_GIVE_SEM,         "release sem"},
    {NV_DEBUG_FLUSHEX_WRITE_FILE_START, "write to nv.bin start"},
    {NV_DEBUG_FLUSHEX_WRITE_FILE_END,   "write to nv.bin end"},
    {NV_DEBUG_WRITEEX_END,              "write nv end"},
    {NV_DEBUG_RECEIVE_ICC,              "receive icc msg from acore"},
    {NV_DEBUG_SEND_ICC,                 "send icc msg to acore"},
    {NV_DEBUG_READ_ICC,                 "read icc from ccore"}

};


void nv_debug_QueueInit(dump_queue_t *Q, u32 elementNum);


void nv_debug_QueueInit(dump_queue_t *Q, u32 elementNum)
{
    Q->maxNum = elementNum;
    Q->front = 0;
    Q->rear = 0;
    Q->num = 0;

    /*lint --e{419 } */
    (void)memset_s((void *)Q->data,(size_t)(elementNum*sizeof(nv_queue_elemnt)), 0, (size_t)(elementNum*sizeof(nv_queue_elemnt)));
}

__inline__ s32 nv_debug_QueueIn(dump_queue_t *Q, nv_queue_elemnt element)
{
    if (Q->num == Q->maxNum)
    {
        return -1;
    }

    Q->data[Q->rear].state = element.state;
    Q->data[Q->rear].slice = element.slice;
    Q->rear = (Q->rear+1) % Q->maxNum;
    Q->num++;

    return 0;
}

__inline__ s32 nv_debug_QueueLoopIn(dump_queue_t *Q, nv_queue_elemnt element)
{
    if (Q->num < Q->maxNum)
    {
        return nv_debug_QueueIn(Q, element);
    }
    else
    {
        Q->data[Q->rear].state = element.state;
        Q->data[Q->rear].slice = element.slice;
        Q->rear = (Q->rear+1) % Q->maxNum;
        Q->front = (Q->front+1) % Q->maxNum;
    }

    return 0;
}

u32 nv_debug_init(void)
{
    g_nv_debug_info.write_debug_table = g_nv_write_debug_table;

    g_nv_debug_info.nv_dump_queue = (dump_queue_t *)bsp_dump_register_field(DUMP_CP_NV, "NVC", 0, 0, NV_DUMP_SIZE, 0x0000);
    if(g_nv_debug_info.nv_dump_queue)
    {
        nv_debug_QueueInit(g_nv_debug_info.nv_dump_queue, NV_DUMP_SIZE/sizeof(nv_queue_elemnt));
    }
    else
    {
        nv_printf("alloc dump buffer fail, field id = 0x%x\n", DUMP_AP_NV);
        return BSP_ERR_NV_MALLOC_FAIL;
    }

    g_nv_debug_info.debug_ctrl.ctrl_bits.write_dump_ctrl = 1;
    return NV_OK;
}

/*****************************************************************************
 函 数 名  : nv_debug_switch
 功能描述  : nv debug功能开关
 输入参数  : void
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
u32 nv_debug_switch(u32 value)
{
    g_nv_debug_info.debug_ctrl.value = value;
    return g_nv_debug_info.debug_ctrl.value;
}
/*****************************************************************************
 函 数 名  : nv_debug_record
 功能描述  : 对读写操作过程记录打点时间
 输入参数  : void
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void nv_debug_record(u32 current_state)
{
    nv_queue_elemnt new_record = {};
    u32 table_index = 0;

    if(1 == g_nv_debug_info.debug_ctrl.ctrl_bits.write_print_ctrl)
    {
        for(table_index = 0; table_index < NV_DEBUG_BUTT; table_index++)
        {
            if(g_nv_debug_info.write_debug_table[table_index].state == (current_state&0xFFFF) )
            {
                nv_printf_info("%s\n", g_nv_debug_info.write_debug_table[table_index].info);
                break;
            }
        }
        switch (current_state&0xFFFF)
        {
            case NV_DEBUG_WRITEEX_START:
            case NV_DEBUG_WRITEEX_END:
                nv_printf_info(" nv id: 0x%x\n", current_state>>16);
                break;
            case NV_DEBUG_SEND_ICC:
            case NV_DEBUG_READ_ICC:
                nv_printf_info(" msg type: 0x%x\n", current_state>>16);
                break;
            default:
                break;
        }
    }

    if((!g_nv_debug_info.nv_dump_queue)||(0 == g_nv_debug_info.debug_ctrl.ctrl_bits.write_dump_ctrl))
    {
        return;
    }

    new_record.slice = bsp_get_slice_value();
    new_record.state = current_state;
    nv_debug_QueueLoopIn(g_nv_debug_info.nv_dump_queue, new_record);

    return;
}
/*****************************************************************************
 函 数 名  : nv_debug_print_dump_queue
 功能描述  : 打印dump队列中的信息
 输入参数  : void
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void nv_debug_print_dump_queue(void)
{
    u32 queue_index = 0;
    u32 queue_num = 0;
    u32 state_str_index = 0;
    u32 current_state = 0;
    char * state_str_info = NULL;

    if(!g_nv_debug_info.nv_dump_queue)
    {
        nv_printf("dump queue is NULL\n");
        return;
    }

    queue_num = g_nv_debug_info.nv_dump_queue->num > g_nv_debug_info.nv_dump_queue->maxNum?\
                    g_nv_debug_info.nv_dump_queue->maxNum:g_nv_debug_info.nv_dump_queue->num;

    for(queue_index = g_nv_debug_info.nv_dump_queue->front; queue_index < queue_num; queue_index++)
    {
        current_state = g_nv_debug_info.nv_dump_queue->data[queue_index].state;

        for(state_str_index =0; state_str_index < NV_DEBUG_BUTT; state_str_index++)
        {
            if(g_nv_debug_info.write_debug_table[state_str_index].state == (current_state&0xFFFF))
            {
                state_str_info = g_nv_debug_info.write_debug_table[state_str_index].info;
                break;
            }
        }
        nv_printf("slice:0x%x state:0x%x %s\n", g_nv_debug_info.nv_dump_queue->data[queue_index].slice, \
                current_state&0xFFFF, state_str_info);

        switch (current_state&0xFFFF)
        {
            case NV_DEBUG_WRITEEX_START:
            case NV_DEBUG_WRITEEX_END:
                nv_printf_info("nv id: 0x%x\n", current_state>>16);
                break;
            case NV_DEBUG_SEND_ICC:
            case NV_DEBUG_READ_ICC:
                nv_printf_info("msg type: 0x%x\n", current_state>>16);
                break;
            default:
                break;
                /*do noting*/
        }
    }
    return;
}
/*****************************************************************************
 函 数 名  : nv_debug_record_delta_time
 功能描述  : 记录操作最大时间
 输入参数  : void
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void nv_debug_record_delta_time(u32 type, u32 start, u32 end)
{
    u32 delta = 0;

    delta = get_timer_slice_delta(start, end);
    if(delta > g_nv_debug_info.delta_time[type])
    {
        g_nv_debug_info.delta_time[type] = delta;
    }
    return;
}
void nv_debug_print_delta_time()
{
    u32 type = 0;
    for(type = 0;type < NV_DEBUG_DELTA_BUTT; type++)
    {
        nv_printf_info("type 0x%x max delta time 0x%x\n", type, g_nv_debug_info.delta_time[type]);
    }
    return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

