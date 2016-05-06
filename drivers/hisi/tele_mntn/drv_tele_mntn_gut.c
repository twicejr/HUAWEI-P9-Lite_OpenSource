/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_tele_mntn_gut.c
  版 本 号   : 初稿
  作    者   : 李彬彬 00186593
  生成日期   : 2014年4月3日
  最近修改   :
  功能描述   : drv tele mntn gut
  函数列表   :
  修改历史   :
  1.日    期   : 2014年4月3日
    作    者   : 李彬彬 00186593
    修改内容   : 创建文件
  2.注    意   : 如下几个文件夹 .c .h 内容必须完全相同
                 vendor\hisi\confidential\lpmcu\driver\tele_mntn\
                 kernel\drivers\hisi\tele_mntn\

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "drv_tele_mntn_gut.h"
#include  "drv_tele_mntn_common.h"
#include  "drv_tele_mntn_platform.h"


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/*lint -e717 -e838 -e826*/
#ifdef WIN32
local_t u8_t g_pc_ut_test_buf[64] = {0};
#ifdef TELE_MNTN_AREA_ADDR
#undef TELE_MNTN_AREA_ADDR
#endif
#ifdef TELE_MNTN_AREA_SIZE
#undef TELE_MNTN_AREA_SIZE
#endif
#define TELE_MNTN_AREA_ADDR  ((u32_t)g_pc_ut_test_buf)
#define TELE_MNTN_AREA_SIZE  (sizeof(g_pc_ut_test_buf))
#endif

/*总控制句柄*/
TELE_MNTN_DATA_SECTION  TELE_MNTN_HANDLE   g_tele_mntn_handle = {0};
local_t TELE_MNTN_CFG_STRU g_tele_mntn_cfg_tbl = {
    TELE_MNTN_AREA_ADDR,
    TELE_MNTN_AREA_SIZE,
    TELE_MNTN_AREA_SIZE*3/4,
    600,
    64,
    0xFFFFFFFF/*unused*/,
    24/*IPC_SEM_TELE_MNTN*/,
};
/*****************************************************************************
  3 函数实现
*****************************************************************************/

s32_t tele_mntn_init(void_t)
{
    s32_t ret = TELE_MNTN_OK;

    if (TELE_MNTN_INIT_MAGIC == g_tele_mntn_handle.init_flag) {
        ret = TELE_MNTN_ALREADY_INIT;
        /*TELE_MNTN_TRACE_OUT(ret, 0);*/
        return ret;
    }

    TELE_MNTN_MEMSET(&g_tele_mntn_handle, 0x00, sizeof(TELE_MNTN_HANDLE));

    if(TELE_MNTN_OK != (ret = tele_mntn_common_init()))
    {
        TELE_MNTN_TRACE_OUT(ret, 0);
        return ret;
    }

    if(TELE_MNTN_OK != (ret = tele_mntn_init_cfg()))
    {
        TELE_MNTN_TRACE_OUT(ret, 0);
        return ret;
    }

    g_tele_mntn_handle.queue.base = g_tele_mntn_handle.data_virt_addr
        + TELE_MNTN_ALIGN((TELE_MNTN_HEAD_SIZE + (2*TELE_MNTN_PROTECT_LEN)), TELE_MNTN_ALIGN_SIZE);

    g_tele_mntn_handle.queue.length = (g_tele_mntn_cfg_tbl.data_size
        - TELE_MNTN_ALIGN((TELE_MNTN_HEAD_SIZE + (2*TELE_MNTN_PROTECT_LEN)), TELE_MNTN_ALIGN_SIZE))
        - TELE_MNTN_ALIGN((2*TELE_MNTN_PROTECT_LEN), TELE_MNTN_ALIGN_SIZE);

#ifdef TELE_MNTN_DEBUG_SW
    g_tele_mntn_handle.debug.peak_left_size = g_tele_mntn_handle.queue.length;
#endif

    TELE_MNTN_LOCALLOCK_INIT(&g_tele_mntn_handle.local_lock);
    TELE_MNTN_GLOBALLOCK_INIT(g_tele_mntn_handle.global_lock, g_tele_mntn_cfg_tbl.global_lock_num);

    g_tele_mntn_handle.init_flag = TELE_MNTN_INIT_MAGIC;

    return ret;
}
/*lint -e550*/
s32_t tele_mntn_init_cfg(void_t)
{
    s32_t ret = TELE_MNTN_OK;

#if defined (CONFIG_TELE_MNTN_CORE_CM3)
    u32_t protect_tmp[2] = {TELE_MNTN_PROTECT1, TELE_MNTN_PROTECT2};
    TELE_MNTN_HEAD_STRU head_tmp = {TELE_MNTN_PROTECT1, 0, 0, TELE_MNTN_PROTECT2};
#endif
    g_tele_mntn_handle.data_virt_addr = TELE_MNTN_PHY_TO_VIRT(g_tele_mntn_cfg_tbl.data_addr, g_tele_mntn_cfg_tbl.data_size);
    if(TELE_MNTN_NULL == g_tele_mntn_handle.data_virt_addr)
    {
        ret = TELE_MNTN_MUTEX_VIRT_ADDR_NULL;
        return ret;
    }

#if defined (CONFIG_TELE_MNTN_CORE_CM3)
    TELE_MNTN_WRITE_MEM((g_tele_mntn_handle.data_virt_addr + TELE_MNTN_HEAD_SIZE), &protect_tmp, 2*TELE_MNTN_PROTECT_LEN);
    TELE_MNTN_WRITE_MEM(((g_tele_mntn_handle.data_virt_addr + g_tele_mntn_cfg_tbl.data_size) - (2*TELE_MNTN_PROTECT_LEN)),
        (u8_t *)&protect_tmp, 2*TELE_MNTN_PROTECT_LEN);

    TELE_MNTN_WRITE_MEM(g_tele_mntn_handle.data_virt_addr, (u8_t *)&head_tmp, TELE_MNTN_HEAD_SIZE);

#endif

    return ret;
}
/*lint +e550*/

/*****************************************************************************
 函 数 名  : tele_mntn_write_log
 功能描述  : 保存log接口
 输入参数  : TELE_MNTN_TYPE_ID type_id
             u32_t len
             void_t * data
 输出参数  : 无
 返 回 值  : s32_t
 调用函数  :
 被调函数  :
 说    明  : 该函数一次传输len最大值为64字节，建议len为8字节对齐。
             未避免多次调用影响性能，建议一个type_id一次流程的数据封装成结构体，一次性存入telemntn
 举    例  : hifi上电，该完整流程的log记录

             hifi上下电的typeid为 TELE_MNTN_PUPD_HIFI 表示上电和下电，可以分解为两个流程，上电和下电。
             对于上电流程，建议将PWC_TELE_MNTN_PU_STRU填充满后再调用执行tele_mntn_write_log接口，
             不建议一个流程调用执行多次tele_mntn_write_log接口。


             typedef struct PWC_TELE_MNTN_PU_STRU_S
             {
                 u32_t  wakeCount;
                 u32_t  wakeSrc0;
                 u32_t  wakeSrc1;
                 u32_t  wakeSrcIPC;
                 u8_t   wakeSrcGPIO[8];
             }PWC_TELE_MNTN_PU_STRU;

     	     typedef struct PWC_TELE_MNTN_PD_STRU_S
     	     {
     	         u32_t  sleepCount;
     	     }PWC_TELE_MNTN_PD_STRU;

             typedef struct PWC_TELE_MNTN_PUPD_STRU_S
             {
                 PWC_TELE_MNTN_PD_STRU pdStat;
                 PWC_TELE_MNTN_PU_STRU puStat; //该结构体数据log会记录到telemntn中
                 u32_t pdSliceTime;
                 u32_t puSliceTime;  //该时间为本地记录时间
             }PWC_TELE_MNTN_PUPD_STRU;

             g_hifi_log = (PWC_TELE_MNTN_PUPD_STRU *)0x25000; //全局变量，指向固定内存空间
             s32_t  pwc_power_up_hifi( void_t )
             {
                 //可维可测部分，先将一次完整流程的log记录到本地
                 g_hifi_log->puStat.wakeCount++;

                 上电处理……

                 //可维可测部分，先将一次完整流程的log记录到本地
                 g_hifi_log->puStat.wakeSrc0 = xxx;
                 g_hifi_log->puStat.wakeSrcIPC = xxx;
                 g_hifi_log->puStat.wakeSrcGPIO = xxx;
                 g_hifi_log->puSliceTime = get_slice_time();

                 //将该次完整流程记录到telemntn中，不带时间信息
                 (void)tele_mntn_write_log(TELE_MNTN_PUPD_HIFI,sizeof(g_hifi_log->puStat),&(g_hifi_log->puStat));

                 return RET_OK;
             }

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : 李彬彬 00186593
    修改内容   : 新生成函数

*****************************************************************************/
s32_t tele_mntn_write_log(TELE_MNTN_TYPE_ID type_id, u32_t len, const void_t * data)
{
    s32_t ret                     = TELE_MNTN_ERRO;
    u32_t data_len                = 0;
    TELE_MNTN_DATA_STRU *cur_data  = &g_tele_mntn_handle.data;
    TELE_MNTN_HANDLE *cur_handle  = &g_tele_mntn_handle;
    TELE_MNTN_CFG_STRU *cur_table = &g_tele_mntn_cfg_tbl;
    TELE_MNTN_BUF_TYPE buf_type   = TELE_MNTN_BUF_INCONTROLLABLE;

    if(TELE_MNTN_INIT_MAGIC != cur_handle->init_flag)
    {
        ret = TELE_MNTN_NOT_INIT;
        return ret;
    }

    if(TELE_MNTN_OK != tele_mntn_is_func_on(type_id))
    {
        return TELE_MNTN_FUNC_OFF;
    }

    if(TELE_MNTN_OK == tele_mntn_is_func_on(TELE_MNTN_NVME_LOGCAT))
    {
        buf_type = TELE_MNTN_BUF_CONTROLLABLE;
    }

    if(len > cur_table->user_data_threshold)
    {
        ret = TELE_MNTN_USER_DATA_OVERFLOW;
        return ret;
    }

    TELE_MNTN_MEMSET((u8_t *)cur_data, 0, sizeof(TELE_MNTN_DATA_STRU));
    TELE_MNTN_LOCAL_LOCK(&cur_handle->local_lock, cur_handle->local_flag);
    TELE_MNTN_GLOBAL_LOCK(cur_handle->global_lock, cur_handle->global_flag, ret);
    TELE_MNTN_CHECK_GLOBAL_LOCK_RET(ret, TELE_MNTN_LOCAL_UNLOCK(&cur_handle->local_lock, cur_handle->local_flag), TELE_MNTN_LOCK_FAIL);

    data_len         = TELE_MNTN_ALIGN(len, TELE_MNTN_ALIGN_SIZE);
    cur_data->protect = TELE_MNTN_PROTECT;
    /*lint -e571*/
    cur_data->type_id = (u32_t)type_id;
    cur_data->len     = data_len;
    /*lint +e571*/
    cur_data->idex    = cur_handle->idex++;
    cur_data->cpu_id  = TELE_MNTN_CUR_CPUID;
    cur_data->rtc     = TELE_MNTN_RTC_TIME_GET();
    cur_data->slice   = TELE_MNTN_SLICE_TIME_GET();

    if(TELE_MNTN_OK != (ret = tele_mntn_write_buf(cur_data, data, data_len, buf_type)))
    {
#ifdef TELE_MNTN_DEBUG_SW
        cur_handle->debug.discard_silce[(cur_handle->debug.discard_num) & (TELE_MNTN_DISCARD_SLICE_BUF_NUM -1)] = TELE_MNTN_SLICE_TIME_GET();
        cur_handle->debug.discard_num++;
#endif
        TELE_MNTN_GLOBAL_UNLOCK(cur_handle->global_lock, cur_handle->global_flag);
        TELE_MNTN_LOCAL_UNLOCK(&cur_handle->local_lock, cur_handle->local_flag);
        return ret;
    }

    TELE_MNTN_GLOBAL_UNLOCK(cur_handle->global_lock, cur_handle->global_flag);
    TELE_MNTN_LOCAL_UNLOCK(&cur_handle->local_lock, cur_handle->local_flag);

    return TELE_MNTN_OK;

}



s32_t tele_mntn_write_buf(const TELE_MNTN_DATA_STRU *head_data, const void_t * data, u32_t len, TELE_MNTN_BUF_TYPE buf_type)
{
    TELE_MNTN_QUEUE_STRU *cur_queue = &g_tele_mntn_handle.queue;
    TELE_MNTN_HEAD_STRU *head       = (TELE_MNTN_HEAD_STRU*)g_tele_mntn_handle.data_virt_addr;
    TELE_MNTN_HEAD_STRU *head_tmp   = &g_tele_mntn_handle.head;
    u32_t size_to_bottom            = 0;

    if(TELE_MNTN_CHECK_DDR_SELF_REFRESH())
    {
        return TELE_MNTN_DDR_SELF_REFRESH;
    }
    TELE_MNTN_MEMSET((u8_t *)head_tmp, 0, sizeof(TELE_MNTN_HEAD_STRU));
    TELE_MNTN_READ_MEM((u8_t *)head, (u8_t *)head_tmp, TELE_MNTN_HEAD_SIZE);
    if(TELE_MNTN_PROTECT1 != head_tmp->protect_word1
    || TELE_MNTN_PROTECT2 != head_tmp->protect_word2)
    {
        return TELE_MNTN_PROTECT_ERR;
    }

    cur_queue->front = cur_queue->base + head_tmp->front * TELE_MNTN_ALIGN_SIZE;
    if(TELE_MNTN_BUF_CONTROLLABLE == buf_type)
    {
        cur_queue->rear  = cur_queue->base + head_tmp->rear * TELE_MNTN_ALIGN_SIZE;
    }
    else
    {
        cur_queue->rear  = cur_queue->front;
    }

    if(cur_queue->front >= cur_queue->rear)
    {
        size_to_bottom = (u32_t)(cur_queue->base + cur_queue->length - cur_queue->front);
        if(size_to_bottom <= len + TELE_MNTN_DATA_SIZE)
            cur_queue->front = cur_queue->base;
    }

    if(cur_queue->front < cur_queue->rear)
    {
        size_to_bottom = (u32_t)(cur_queue->rear - cur_queue->front) - TELE_MNTN_ALIGN_SIZE;
    }

    if(size_to_bottom > len + TELE_MNTN_DATA_SIZE)
    {
        TELE_MNTN_WRITE_MEM(cur_queue->front, (u8_t *)head_data, TELE_MNTN_DATA_SIZE);
        cur_queue->front += TELE_MNTN_DATA_SIZE;
        TELE_MNTN_WRITE_MEM(cur_queue->front, (u8_t *)data, len);
        cur_queue->front += len;
        head_tmp->front = ((u32_t)(cur_queue->front - cur_queue->base))/TELE_MNTN_ALIGN_SIZE;
        if(TELE_MNTN_BUF_CONTROLLABLE != buf_type)
        {
            TELE_MNTN_WRITE_MEM((u8_t *)head, (u8_t *)head_tmp, TELE_MNTN_HEAD_SIZE);
        }
        else
        {
            TELE_MNTN_WRITE_MEM((u8_t *)head, (u8_t *)head_tmp, 2*sizeof(u32_t));
        }
    }
    else
    {
        return TELE_MNTN_BUF_FULL;
    }

    return TELE_MNTN_OK;

}

s32_t tele_mntn_wake_up_acore(void_t)
{
#if defined (CONFIG_TELE_MNTN_CORE_CM3)
    struct ipc_msg msg;
#endif
    TELE_MNTN_HANDLE *cur_handle    = &g_tele_mntn_handle;
    TELE_MNTN_QUEUE_STRU *cur_queue = &g_tele_mntn_handle.queue;
    TELE_MNTN_CFG_STRU *cur_table   = &g_tele_mntn_cfg_tbl;
    TELE_MNTN_HEAD_STRU head_tmp    = {0};
    u8_t *cur_front = TELE_MNTN_NULL;
    u8_t *cur_rear  = TELE_MNTN_NULL;
    u32_t left_size = 0;
    u32_t cur_slice = 0;

#ifdef TELE_MNTN_DEBUG_SW
    TELE_MNTN_DEBUG_STRU *cur_debug = &g_tele_mntn_handle.debug;
#endif
    if(TELE_MNTN_OK != tele_mntn_is_func_on((TELE_MNTN_TYPE_ID)TELE_MNTN_NVME_WAKEUP_ACPU))
    {
        return TELE_MNTN_OK;
    }
    if(TELE_MNTN_INIT_MAGIC != g_tele_mntn_handle.init_flag)
    {
        return TELE_MNTN_NOT_INIT;
    }

    TELE_MNTN_READ_MEM(g_tele_mntn_handle.data_virt_addr, (u8_t *)&head_tmp, TELE_MNTN_HEAD_SIZE);

    cur_front = cur_queue->base + head_tmp.front * TELE_MNTN_ALIGN_SIZE;;
    cur_rear = cur_queue->base + head_tmp.rear * TELE_MNTN_ALIGN_SIZE;


    if(cur_front < cur_rear)
    {
        left_size = (u32_t)(cur_rear - cur_front) - TELE_MNTN_ALIGN_SIZE;
    }
    else
    {
        left_size = (cur_queue->length - (u32_t)(cur_front - cur_rear)) - TELE_MNTN_ALIGN_SIZE;
    }

    if(left_size < cur_table->wake_threshold)
    {
        cur_slice = TELE_MNTN_SLICE_TIME_GET();
        if((cur_slice - cur_handle->prior_wakeup_acore_slice) >= TELE_MNTN_SECOND_TO_SLICE(cur_table->wake_interval_threshold))
        {
#if defined (CONFIG_TELE_MNTN_CORE_CM3)
            (msg.cmd_mix).cmd_type = TYPE_MODE;
            (msg.cmd_mix).cmd = CMD_SETTING;
            (msg.cmd_mix).cmd_obj = OBJ_TELEMNTN;
            (msg.cmd_mix).cmd_src = OBJ_LPM3;
            ipc_msg_send(OBJ_AP, &msg, ASYNC_MODE);
#endif
            cur_handle->prior_wakeup_acore_slice = cur_slice;
        }

#ifdef TELE_MNTN_DEBUG_SW
        cur_debug->wakeup_accore_silce[(cur_debug->wakeup_accore_num)&(TELE_MNTN_WUACORE_SLICE_BUF_NUM-1)] = cur_slice;
        cur_debug->wakeup_accore_num++;
#endif

    }

#ifdef TELE_MNTN_DEBUG_SW
    if(left_size < cur_debug->peak_left_size)
    {
        cur_debug->peak_left_size = left_size;
        cur_debug->peak_left_slice = TELE_MNTN_SLICE_TIME_GET();
    }
#endif
    return TELE_MNTN_OK;
}

s32_t tele_mntn_get_head(struct tele_mntn_queue *queue)
{
    s32_t ret = TELE_MNTN_OK;
    TELE_MNTN_QUEUE_STRU *cur_queue = &g_tele_mntn_handle.queue;
    TELE_MNTN_HEAD_STRU head_tmp    = {0};

    if(TELE_MNTN_IS_NULL(queue))
    {
        ret = TELE_MNTN_PARA_INVALID;
        return ret;
    }

    if(TELE_MNTN_INIT_MAGIC != g_tele_mntn_handle.init_flag)
    {
        ret = TELE_MNTN_NOT_INIT;
        return ret;
    }

    TELE_MNTN_READ_MEM(g_tele_mntn_handle.data_virt_addr, (u8_t *)&head_tmp, TELE_MNTN_HEAD_SIZE);

    if(TELE_MNTN_PROTECT1 != head_tmp.protect_word1
    || TELE_MNTN_PROTECT2 != head_tmp.protect_word2)
    {
        ret = TELE_MNTN_PROTECT_ERR;
        return ret;
    }

    queue->base   = cur_queue->base;
    queue->length = cur_queue->length;
    queue->front  = cur_queue->base + head_tmp.front * TELE_MNTN_ALIGN_SIZE;
    queue->rear   = cur_queue->base + head_tmp.rear * TELE_MNTN_ALIGN_SIZE;


    return ret;

}


s32_t tele_mntn_set_head(const struct tele_mntn_queue *queue)
{
    s32_t ret = TELE_MNTN_OK;
    TELE_MNTN_HEAD_STRU *head       = (TELE_MNTN_HEAD_STRU*)g_tele_mntn_handle.data_virt_addr;
    TELE_MNTN_HEAD_STRU head_tmp    = {0};

    if(TELE_MNTN_IS_NULL(queue))
    {
        ret = TELE_MNTN_PARA_INVALID;
        return ret;
    }

    if(TELE_MNTN_INIT_MAGIC != g_tele_mntn_handle.init_flag)
    {
        ret = TELE_MNTN_NOT_INIT;
        return ret;
    }

    TELE_MNTN_READ_MEM((u8_t *)head, (u8_t *)&head_tmp, TELE_MNTN_HEAD_SIZE);

    if(TELE_MNTN_PROTECT1 != head_tmp.protect_word1
    || TELE_MNTN_PROTECT2 != head_tmp.protect_word2)
    {
        ret = TELE_MNTN_PROTECT_ERR;
        return ret;
    }

    head_tmp.rear = ((u32_t)(queue->rear - queue->base))/TELE_MNTN_ALIGN_SIZE;
    TELE_MNTN_WRITE_MEM((u8_t *)&(head->rear), (u8_t *)&(head_tmp.rear), sizeof(head->rear));

    return ret;

}

#ifdef TELE_MNTN_DEBUG_SW
void_t tele_mntn_debug_out(void_t)
{
    u32_t debug_idex = 0;
    TELE_MNTN_DEBUG_STRU *cur_debug = &g_tele_mntn_handle.debug;
    TELE_MNTN_TRACE_OUT(TELE_MNTN_BUF_FULL, cur_debug->discard_num);
    for(debug_idex = 0; debug_idex < TELE_MNTN_DISCARD_SLICE_BUF_NUM; debug_idex ++)
    {
        TELE_MNTN_TRACE_OUT(TELE_MNTN_BUF_FULL, cur_debug->discard_silce[debug_idex]);
    }

    TELE_MNTN_TRACE_OUT(TELE_MNTN_WAKEUP_ACORE_SUCC, cur_debug->wakeup_accore_num);
    for(debug_idex = 0; debug_idex < TELE_MNTN_WUACORE_SLICE_BUF_NUM; debug_idex ++)
    {
        TELE_MNTN_TRACE_OUT(TELE_MNTN_WAKEUP_ACORE_SUCC, cur_debug->wakeup_accore_silce[debug_idex]);
    }

    TELE_MNTN_TRACE_OUT(TELE_MNTN_PROTECT_ERR, g_tele_mntn_cfg_tbl.data_addr);
    TELE_MNTN_TRACE_OUT(TELE_MNTN_PROTECT_ERR, g_tele_mntn_cfg_tbl.data_size);
    TELE_MNTN_TRACE_OUT(TELE_MNTN_PROTECT_ERR, g_tele_mntn_cfg_tbl.wake_threshold);
    TELE_MNTN_TRACE_OUT(TELE_MNTN_PROTECT_ERR, g_tele_mntn_cfg_tbl.wake_interval_threshold);
    TELE_MNTN_TRACE_OUT(TELE_MNTN_PROTECT_ERR, g_tele_mntn_cfg_tbl.user_data_threshold);
    TELE_MNTN_TRACE_OUT(TELE_MNTN_PROTECT_ERR, g_tele_mntn_cfg_tbl.ipc_int_num);
    TELE_MNTN_TRACE_OUT(TELE_MNTN_PROTECT_ERR, g_tele_mntn_cfg_tbl.global_lock_num);
    TELE_MNTN_TRACE_OUT(TELE_MNTN_PROTECT_ERR, (udy_t)(g_tele_mntn_handle.data_virt_addr));

}
#endif
/*lint +e717 +e838 +e826*/
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

