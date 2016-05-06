


#ifndef _NV_COMM_H_
#define _NV_COMM_H_


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -save -e537*/
#include <string.h>
#include <cmsis_os.h>
#include <osl_common.h>
#include <osl_sem.h>
#include <bsp_nvim.h>
#include <bsp_shared_ddr.h>
#include <bsp_ipc.h>
#include <bsp_icc.h>
#include <bsp_om.h>
/*lint -restore +e537*/



#undef printf
#define printf     printk

#define nv_malloc(a)     malloc(a)
#define nv_free(p)       free(p)
#define nv_taskdelay(n)  osDelay(n)

extern struct nv_global_ctrl_info_stru g_nv_ctrl;


#define NV_ID_SYS_MAX_ID          0xd1ff
#define NV_ID_SYS_MIN_ID          0xd100

#define nv_spin_lock(nvflag,lock) \
do{\
    local_irq_save(nvflag);\
    (void)bsp_ipc_spin_lock(lock);\
}while(0)

#define nv_spin_unlock(nvflag,lock) \
do{\
    (void)bsp_ipc_spin_unlock(lock);\
    local_irq_restore(nvflag);\
}while(0)



/*global info type define*/
struct nv_global_ctrl_info_stru
{
#ifdef __VXWORKS__
    osl_sem_id rw_sem;      /*lock the write*/
    osl_sem_id cc_sem;      /*lock the core comm*/
#endif
    u32 mid_prio;    /*nv priority*/
    u32 debug_sw;
    u32 shared_addr;
};

u32 nv_read_from_mem(u8 * pdata, u32 size,u32 file_id ,u32 offset);
bool nv_read_right(u32 itemid);
u32 nv_search_byid(u32 itemid,u8 * pdata, struct nv_ref_data_info_stru * ref_info, struct nv_file_list_info_stru * file_info);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif





#endif /*_NV_COMM_H_*/


