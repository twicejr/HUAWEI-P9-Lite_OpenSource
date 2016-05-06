/*************************************************************************
*   版权所有(C) 2008-2015, 华为技术有限公司.
*
*   文 件 名 :  icc_platform.h
*
*   作    者 :  h00277960
*
*   描    述 :  平台相关头文件
*
*   修改记录 :  2015年4月20日  v1.00  h00277960  创建
*************************************************************************/

#ifndef ICC_PLATFORM_H
#define ICC_PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <securec.h>
#include <osl_common.h>
#include <osl_types.h>
#include <osl_sem.h>
#include <osl_thread.h>
#include <osl_spinlock.h>
#include <osl_wait.h>
#include <osl_list.h>
#include <osl_malloc.h>
#include <osl_module.h>
#include <bsp_sram.h>
#include <bsp_shared_ddr.h>
#include <bsp_hardtimer.h>
#include <bsp_dump.h>
#include <bsp_om.h>
#include <of.h>
#include <bsp_ipc.h>
#include <bsp_icc.h>
#include <bsp_reset.h>

#define ICC_CHANNEL_INIT_COMPITABLE  "hisilicon,icc_balong_mdm"

#define  ICC_THIS_CPU                 (ICC_CPU_MODEM)
#define  ICC_SEND_CPU                 (ICC_CPU_APP)
#define  ICC_RECV_IPC_SHARED          (IPC_CCPU_INT_SRC_ACPU_ICC)
#define  ICC_TASK_STK_SIZE            (0x1000)
#define  NOTIFY_STOP_MASK             (0x8000)
#define  ICC_DUMP_SAVE_MOD            DUMP_CP_ICC
#define  ICC_DUMP_EXT_SIZE            (0x800)
#define ICC_SDDR_START_ADDR_ON_THIS_CORE    (ICC_DBG_MSG_ADDR_IN_DDR + ICC_DBG_MSG_LEN_IN_DDR)
#define ICC_SDDR_S_START_ADDR_ON_THIS_CORE  (ICC_DBG_MSG_ADDR_IN_DDR_S + ICC_DBG_MSG_LEN_IN_DDR_S)
#define ICC_SRAM_START_ADDR_ON_THIS_CORE    (ADDR_MCCORE_SEND)

typedef  u32  icc_task_id;

#define WAKE_LOCK_SUSPEND (0)

#define  icc_print_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ICC, "%s "fmt, __FUNCTION__, ##__VA_ARGS__))
#define  icc_print_info(fmt, ...)     (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ICC, fmt, ##__VA_ARGS__))
#define  icc_print_notice(fmt, ...)   (bsp_trace(BSP_LOG_LEVEL_NOTICE, BSP_MODU_ICC, "%s "fmt, __FUNCTION__, ##__VA_ARGS__))
#define  icc_print_debug(fmt, ...) \
do {                               \
    if (g_icc_dbg.msg_print_sw)    \
        icc_print_error(fmt, ##__VA_ARGS__);\
} while (0)

/* 数据类型定义start */
struct icc_pm_debug{
	FUNCPTR_1 debug_routine;
	int para;
};

struct icc_channel_vector
{
	read_cb_func  read_cb;        /* 接收向量的读回调函数指针 */
	void          *read_context;  /* 接收向量的读回调函数context */
	write_cb_func write_cb;       /* 接收向量的写回调函数指针 */
	void          *write_context; /* 接收向量的写回调函数context */
	struct icc_pm_debug pm_debug;
};

struct wake_lock
{
	int lock;
};

struct icc_control
{
	u32                cpu_id;                    /* 当前核cpu id */
	u32                state;                     /* icc控制结构体状态: 可用|不可用 */
	icc_task_id        shared_task_id;            /* 通道共享任务id */
	u32                shared_recv_ipc_irq_id;    /* 通道共享的接收数据使用ipc中断 */
	osl_sem_id         shared_task_sem;           /* 唤醒通道共享任务的信号量 */
	u32                wake_up_flag;
	u32                sleep_flag;
	struct icc_channel *channels[ICC_CHN_ID_MAX]; /* icc_channel的结构体指针数组 */
	u32                channel_size;              /* 通道数目 */
	struct             wake_lock wake_lock;
};

void icc_system_error(u32 mod_id, u32 arg1, u32 arg2, char *data, u32 length);
static inline void icc_wake_lock_init(struct wake_lock *lock, int lock_id, const char *name){return ;}
static inline void icc_wake_lock(struct wake_lock *lock){return ;}
static inline void icc_wake_unlock(struct wake_lock *lock){return ;}
void bsp_icc_channel_uninit(u32 real_channel_id);
int icc_pm_init(void);
static inline int icc_ccore_is_reseting(u32 cpuid) {return 0;}

void icc_packet_print(struct icc_channel_packet *packet);
int icc_channel_packet_dump(struct icc_channel_packet *packet);
u32 bsp_icc_channel_status_get(u32 real_channel_id, u32 *channel_stat);

void icc_debug_in_isr(void);
s32  icc_debug_init(u32 channel_num);
void icc_debug_before_send(struct icc_channel_packet *packet);
void icc_debug_after_send(struct icc_channel *channel, struct icc_channel_packet *packet, u8 *data);
void icc_debug_before_recv(struct icc_channel_packet *pkg_header);
void icc_debug_in_read_cb(u32 channel_id, u8 *buf, u32 buf_len, u32 read_ptr, u32 write_ptr);
void icc_debug_after_recv(struct icc_channel_packet *pkg_header);

#ifdef __cplusplus
}
#endif

#endif


