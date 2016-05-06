


#ifndef _NV_COMM_H_
#define _NV_COMM_H_


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/* yangzhi RTOSck */
#if (defined(__OS_RTOSCK__) || defined(__OS_VXWORKS__))
/*lint -save -e537*/
//#include <memLib.h>
//#include <taskLib.h>
#include "osl_common.h"
#include "osl_spinlock.h"
#include "osl_sem.h"
#include "osl_list.h"
#include "osl_bio.h"
#include "osl_cache.h"
#include "osl_spinlock.h"
#include "osl_malloc.h"
#include "osl_thread.h"
#include "osl_bio.h"
#include <stdlib.h>
#include <string.h>
#include <osl_irq.h>
#else
#include "osl_malloc.h"
#include "osl_thread.h"
#include "osl_bio.h"
#endif
#include <bsp_nvim.h>
#include <bsp_shared_ddr.h>
#include <bsp_ipc.h>
#include <bsp_icc.h>
#include <bsp_om.h>
#include "bsp_hardtimer.h"
#include "drv_nv_def.h"
#include "drv_nv_id.h"
#include "msp_nv_id.h"
#include "drv_nv_def.h"

/*lint -restore*/
#ifdef __KERNEL__

#define nv_malloc(a)     kmalloc(a,GFP_KERNEL)
#define nv_free(p)       kfree(p)
#ifndef printf
#define printf(fmt,...)     bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_NV,fmt,##__VA_ARGS__)
#endif

#define nv_taskdelay(n)      msleep(n)

/* yangzhi RTOSck */
#elif defined(__OS_VXWORKS__ ) /*vxworks*/

#define nv_malloc(a)     malloc(a)
#define nv_free(p)       free(p)
#define nv_taskdelay(n)  taskDelay(n)

#endif

/* yangzhi RTOSck */
#ifdef __OS_RTOSCK__ /* rtosck */

#define nv_malloc(a)     osl_malloc(a)
#define nv_free(p)       osl_free(p)
#define nv_taskdelay(n)  osl_task_delay(n)
#endif
#define nv_flush_cache(p,n)   cache_sync()

extern struct nv_global_ctrl_info_stru g_nv_ctrl;
#define nv_printf(fmt, ...) \
    bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_NV,"[nv]: <%s> line = %d  "fmt, __FUNCTION__,__LINE__, ##__VA_ARGS__)
#define nv_warn_printf(fmt, ...) \
    bsp_trace(BSP_LOG_LEVEL_WARNING,BSP_MODU_NV,"[nv]: <%s> line = %d  "fmt, __FUNCTION__,__LINE__, ##__VA_ARGS__)
#define nv_info_printf(fmt, ...) \
            bsp_trace(BSP_LOG_LEVEL_INFO,BSP_MODU_NV,"[nv]: <%s> line = %d  "fmt, __FUNCTION__,__LINE__, ##__VA_ARGS__)
#define nv_debug_printf(fmt, ...) \
    bsp_trace(BSP_LOG_LEVEL_DEBUG,BSP_MODU_NV,"[nv]: <%s> line = %d  "fmt, __FUNCTION__,__LINE__, ##__VA_ARGS__)
#define nv_error_printf(fmt, ...) \
    bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_NV,"[nv]: <%s> line = %d  "fmt, __FUNCTION__,__LINE__, ##__VA_ARGS__)
#define nv_printf_info(fmt, ...) \
            bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_NV, fmt, ##__VA_ARGS__)


#define NV_ID_SYS_MAX_ID          0xd1ff
#define NV_ID_SYS_MIN_ID          0xd100

/*lint -save -e607*/
#define nv_debug_trace(pdata,len)\
    if(g_nv_ctrl.debug_sw == true)\
    {\
        u32 i;\
        nv_printf("len :0x%x\n",len);\
        for(i=0;i<len;i++)\
        {\
            nv_printf("%02x ",*((u8*)pdata+i));\
        }\
        nv_printf("\n");\
    };
/*lint -restore*/

#define nv_pm_trace(icc_cnf)\
    if(g_nv_ctrl.pmSw == true)\
    {\
        (void)bsp_pm_log_type(PM_OM_NVC, 0, sizeof(icc_cnf), (void *)&icc_cnf);\
        g_nv_ctrl.pmSw = false;\
    };

#define nv_spin_lock(nvflag,lock) \
do{\
    spin_lock_irqsave(&g_nv_ctrl.spinlock, nvflag);\
    (void)bsp_ipc_spin_lock(lock);\
}while(0)

#define nv_spin_unlock(nvflag,lock) \
do{\
    (void)bsp_ipc_spin_unlock(lock);\
    spin_unlock_irqrestore(&g_nv_ctrl.spinlock, nvflag);\
}while(0)


#define IPC_SME_TIME_OUT   (1000)
#define nv_ipc_sem_take(sem, timeout) \
do{\
    u32 start = 0;\
    u32 end = 0;\
    osl_sem_down(&g_nv_ctrl.rw_sem);\
    start = bsp_get_slice_value();\
    if(bsp_ipc_sem_take(sem, timeout))\
    {\
        nv_printf("[0x%x] take ipc sem fail\n", bsp_get_slice_value());\
        return BSP_ERR_NV_TIME_OUT_ERR;\
    }\
    end = bsp_get_slice_value();\
    nv_debug_record_delta_time(NV_DEBUG_DELTA_GET_IPC, start, end);\
}while(0)

#define nv_ipc_sem_give(sem) \
do{\
    if(bsp_ipc_sem_give(sem))\
    {\
        nv_printf("[0x%x]give ipc sem fail\n", bsp_get_slice_value());\
        return BSP_ERR_NV_GIVE_IPC_ERR;\
    }\
    osl_sem_up(&g_nv_ctrl.rw_sem);\
}while(0)


/*nv debug info*/
struct nv_global_debug_stru
{
    u32 callnum;
    u32 reseved1;
    u32 reseved2;
    u32 reseved3;
    u32 reseved4;
};


#define NV_MAX_WAIT_TICK             (5000)


#define NV_ICC_BUF_LEN               64
#define NV_ICC_SEND_COUNT            5
enum
{
    NV_MODE_FACTORY     = 1,
    NV_MODE_USER        = 2,
    NV_MODE_BUTT
};

struct nv_flush_list_node_stru
{
    u16  itemid;     /* NV ID */
    u16  nv_len;     /* NV Length */
    u32  nv_off;     /* Offset of the NV ID start address at the ctrl NV file */
    struct list_head stList;
};

/*global info type define*/
struct nv_global_ctrl_info_stru
{

    u8 nv_icc_buf[NV_ICC_BUF_LEN];
#if (defined(__OS_RTOSCK__) || defined(__OS_VXWORKS__))
    osl_sem_id rw_sem;      /*与IPC锁同时使用保证本核访问的互斥*/
    osl_sem_id cc_sem;      /*lock the core comm*/
#endif
    u32 mid_prio;    /*nv priority*/
    NV_SELF_CTRL_STRU nv_self_ctrl;
    u32 debug_sw;
    spinlock_t spinlock;
    struct nv_global_ddr_info_stru* shared_addr;
    struct list_head stList;
    bool statis_sw;
    bool pmSw;

    struct list_head nv_list;                   /*存储待写入的list的*/
    osl_sem_id nv_list_sem;                     /*用于保护nv_list的信号量*/
    u32 resered;
};
struct nv_write_list_stru
{
    u32 itemid;
    u32 count;
    u32 slice;
    struct list_head stList;
};

u32 nv_write_to_mem(u8 * pdata, u32 size, u32 file_id, u32 offset);
u32 nv_read_from_mem(u8 * pdata, u32 size,u32 file_id ,u32 offset);
u32 nv_icc_chan_init(void);
s32 nv_icc_msg_proc(u32 chanid,u32 len, void * pdata);
u32 nv_icc_read(u32 chanid, u32 len);
u32 nv_icc_send(u8 * pdata, u32 len);
bool nv_read_right(u32 itemid);
bool nv_write_right(u32 itemid);
u32 nv_write_to_file(struct nv_ref_data_info_stru* ref_info);
u32 nv_search_byid(u32 itemid,u8 * pdata, struct nv_ref_data_info_stru * ref_info, struct nv_file_list_info_stru * file_info);
void nv_debug(u32 type, u32 reseverd1, u32 reserved2, u32 reserved3, u32 reserved4);
void nv_help(u32 type);
void show_ddr_info(void);
/*lint -save -e123*/
void show_ref_info(u32 min, u32 max);
/*lint -restore*/
void nv_print_file(void);
void show_all_nv_data(void);
void nv_modify_print_sw(u32 arg);
bool nv_isSysNv(u16 itemid);
u32 nv_check_nv_data_crc(u32 offset, u32 datalen);
u32 nv_check_part_ddr_crc(u8 *pData, u32 old_crc, u32 size);
u32 nv_resume_ddr_from_img(void);
u32 nv_make_nv_data_crc(u32 offset, u32 datalen);
u32  nv_pushNvFlushList(struct nv_ref_data_info_stru* ref_info);
u32 nv_flushList(void);
u32 nv_request_flush(void);
u32 nv_pop_list_to_glb_list(void);
u32 nv_push_to_local_list(struct nv_ref_data_info_stru* ref_info);
u32 nv_check_local_list(u32 itemid);
void show_local_list(void);
u32 nv_show_ref_info(u16 itemid);
void nv_wr_process_set(u8* pdata,u32 size,u32 file_id,u32 offset);
void nv_wr_process_clear(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif



#endif /*_NV_COMM_H_*/


