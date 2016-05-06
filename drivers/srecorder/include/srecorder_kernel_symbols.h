/**
    @copyright: Huawei Technologies Co., Ltd. 2012-2012. All rights reserved.
    
    @file: srecorder_kernel_symbols.h
    
    @brief: 读取内核符号的地址
    
    @version: 1.0 
    
    @author: QiDechun ID: 216641
    
    @date: 2012-06-21
    
    @history:
*/

#ifndef SRECORDER_KERNEL_SYMBOLS_H
#define SRECORDER_KERNEL_SYMBOLS_H


/*----includes-----------------------------------------------------------------------*/

#include <linux/version.h>
#include "srecorder_common.h"


/*----c++ support--------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


/*----export macroes-----------------------------------------------------------------*/


/*----export prototypes---------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----export function prototypes--------------------------------------------------------*/

#if defined(CONFIG_DUMP_SYS_INFO)
/**
    @function: srec_ksym_addr_t srecorder_get_cpu_name(void)
    @brief: 获取变量cpu_name的地址

    @param: none
    
    @return: 变量cpu_name的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_cpu_name(void);


/**
    @function: srec_ksym_addr_t srecorder_get_machine_name(void)
    @brief: 获取变量machine_name的地址

    @param: none
    
    @return: 变量machine_name的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_machine_name(void);


/**
    @function: srec_ksym_addr_t srecorder_get_all_bdevs(void)
    @brief: 获取变量all_bdevs的地址

    @param: none
    
    @return: 变量all_bdevs的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_all_bdevs(void);


/**
    @function: srec_ksym_addr_t srecorder_get_bdev_lock(void)
    @brief: 获取变量bdev_lock的地址

    @param: none
    
    @return: 变量bdev_lock的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_bdev_lock(void);


#ifdef CONFIG_SWAP
/**
    @function: srec_ksym_addr_t srecorder_get_nr_swapfiles(void)
    @brief: 获取变量nr_swapfiles的地址

    @param: none
    
    @return: 变量nr_swapfiles的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_nr_swapfiles(void);


/**
    @function: srec_ksym_addr_t srecorder_get_swap_info(void)
    @brief: 获取变量swap_info的地址

    @param: none
    
    @return: 变量swap_info的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_swap_info(void);


/**
    @function: srec_ksym_addr_t srecorder_get_swap_lock(void)
    @brief: 获取变量swap_lock的地址

    @param: none
    
    @return: 变量swap_lock的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_swap_lock(void);
#endif


/**
    @function: srec_ksym_addr_t srecorder_get_vmap_area_lock(void)
    @brief: 获取变量swap_lock的地址

    @param: none
    
    @return: 变量vmap_area_lock的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_vmap_area_lock(void);


/**
    @function: srec_ksym_addr_t srecorder_get_vmap_area_list(void)
    @brief: 获取变量swap_lock的地址

    @param: none
    
    @return: 变量vmap_area_list的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_vmap_area_list(void);
#endif


/**
    @function: srec_ksym_addr_t srecorder_get_register_oom_notifier(void)
    @brief: 获取函数register_oom_notifier的地址

    @param: none
    
    @return: 函数register_oom_notifier的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_register_oom_notifier(void);


/**
    @function: srec_ksym_addr_t srecorder_get_unregister_oom_notifier(void)
    @brief: 获取函数unregister_oom_notifier的地址

    @param: none
    
    @return: 函数unregister_oom_notifier的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_unregister_oom_notifier(void);


/**
    @function: srec_ksym_addr_t srecorder_get_register_jprobe(void)
    @brief: 获取函数register_jprobe的地址

    @param: none
    
    @return: 函数register_jprobe的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_register_jprobe(void);


/**
    @function: srec_ksym_addr_t srecorder_get_unregister_jprobe(void)
    @brief: 获取函数unregister_jprobe的地址

    @param: none
    
    @return: 函数unregister_jprobe的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_unregister_jprobe(void);


/**
    @function: srec_ksym_addr_t srecorder_get_jprobe_return(void)
    @brief: 获取函数jprobe_return的地址

    @param: none
    
    @return: 函数jprobe_return的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_jprobe_return(void);


#if defined(CONFIG_DUMP_CURRENT_PS_BACKTRACE)
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 36))
/**
    @function: srec_ksym_addr_t srecorder_get_vfsmount_lock_lock(void)
    @brief: 获取变量vfsmount_lock_lock的地址

    @param: none
    
    @return: 变量vfsmount_lock_lock的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_vfsmount_lock_lock(void);
#else
/**
    @function: srec_ksym_addr_t srecorder_get_vfsmount_lock(void)
    @brief: 获取变量vfsmount_lock的地址

    @param: none
    
    @return: 变量vfsmount_lock的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_vfsmount_lock(void);
#endif


#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 38))
/**
    @function: srec_ksym_addr_t srecorder_get_dcache_lock(void)
    @brief: 获取变量dcache_lock的地址

    @param: none
    
    @return: 变量dcache_lock的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_dcache_lock(void);
#else
/**
    @function: srec_ksym_addr_t srecorder_get_rename_lock(void)
    @brief: 获取变量rename_lock的地址

    @param: none
    
    @return: 变量rename_lock的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_rename_lock(void);
#endif


/**
    @function: srec_ksym_addr_t srecorder_get_arch_vma_name(void)
    @brief: 获取函数arch_vma_name的地址

    @param: none
    
    @return: 函数arch_vma_name的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_arch_vma_name(void);
#endif


#ifdef CONFIG_FUNCTION_GRAPH_TRACER
#endif


#ifdef CONFIG_ARM_UNWIND
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 2, 0))
/**
    @function: srec_ksym_addr_t srecorder_get___origin_unwind_idx(void)
    @brief: 获取变量__origin_unwind_idx的地址

    @param: none
    
    @return: 变量__origin_unwind_idx的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get___origin_unwind_idx(void);
#endif


/**
    @function: srec_ksym_addr_t srecorder_get_unwind_tables(void)
    @brief: 获取变量unwind_tables的地址

    @param: none
    
    @return: 变量unwind_tables的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_unwind_tables(void);


/**
    @function: srec_ksym_addr_t srecorder_get_unwind_lock(void)
    @brief: 获取变量unwind_lock的地址

    @param: none
    
    @return: 变量unwind_lock的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_unwind_lock(void);
#endif


#if defined(CONFIG_DUMP_ALLPS_INFO)
#endif


#if defined(CONFIG_DUMP_ALLCPU_STACK) || defined(CONFIG_DUMP_ALLPS_INFO)
#endif


#if defined(CONFIG_DUMP_ALLCPU_STACK)
#endif


/**
    @function: srec_ksym_addr_t srecorder_get_atomic_notifier_chain_register(void)
    @brief: 获取函数atomic_notifier_chain_register的地址

    @param: none
    
    @return: atomic_notifier_chain_register的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_atomic_notifier_chain_register(void);


/**
    @function: srec_ksym_addr_t srecorder_get_atomic_notifier_chain_unregister(void)
    @brief: 获取函数atomic_notifier_chain_unregister的地址

    @param: none
    
    @return: atomic_notifier_chain_unregister的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_atomic_notifier_chain_unregister(void);


#if defined(CONFIG_DUMP_DMESG)
/**
    @function: srec_ksym_addr_t srecorder_get_log_buf(void)
    @brief: 得到内核ring buffer的起始地址

    @param: none
    
    @return: 内核ring buffer起始地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_log_buf(void);


/**
    @function: srec_ksym_addr_t srecorder_get_log_buf_len(void)
    @brief: 得到内核变量log_buf_len的起始地址

    @param: none
    
    @return: 内核变量log_buf_len的起始地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_log_buf_len(void);


/**
    @function: srec_ksym_addr_t srecorder_get_log_end(void)
    @brief: 得到内核变量log_end的起始地址

    @param: none
    
    @return: 内核变量log_end的起始地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_log_end(void);
#endif


#if defined(CONFIG_DUMP_SLAB_INFO)
#ifdef CONFIG_SLAB
/**
    @function: srec_ksym_addr_t srecorder_get_cache_chain(void)
    @brief: 获取cache_chain的地址, slab的信息存在它里面
    
    @param: none
    
    @return: cache_chain

    @note: 
*/
srec_ksym_addr_t srecorder_get_cache_chain(void);


/**
    @function: srec_ksym_addr_t srecorder_get_cache_chain_mutex(void)
    @brief: 获取cache_chain_mutex的地址, 用于同步对cache_chain的读写
    
    @param: none
    
    @return: cache_chain_mutex

    @note: 
*/
srec_ksym_addr_t srecorder_get_cache_chain_mutex(void);
#elif defined(CONFIG_SLUB)
/**
    @function: srec_ksym_addr_t srecorder_get_slab_caches(void)
    @brief: 获取slab_caches的地址, slab的信息存在它里面
    
    @param: none
    
    @return: slab_caches

    @note: 
*/
srec_ksym_addr_t srecorder_get_slab_caches(void);


/**
    @function: srec_ksym_addr_t srecorder_get_slub_lock(void)
    @brief: 获取slub_lock的地址, 用于同步对slab_caches的读写
    
    @param: none
    
    @return: slub_lock

    @note: 
*/
srec_ksym_addr_t srecorder_get_slub_lock(void);
#endif
#endif


#if defined(CONFIG_DUMP_MODEM_LOG)
/**
    @function: srec_ksym_addr_t srecorder_get_spinlocks_initialized(void)
    @brief: 获取变量spinlocks_initialized的地址

    @param: none
    
    @return: 变量spinlocks_initialized的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_spinlocks_initialized(void);


/**
    @function: srec_ksym_addr_t srecorder_get_remote_spinlock(void)
    @brief: 获取变量remote_spinlock的地址

    @param: none
    
    @return: 变量remote_spinlock的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_remote_spinlock(void);


/**
    @function: srec_ksym_addr_t srecorder_get_smem_areas(void)
    @brief: 获取变量smem_areas的地址

    @param: none
    
    @return: 变量smem_areas的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_smem_areas(void);


/**
    @function: srec_ksym_addr_t srecorder_get_num_smem_areas(void)
    @brief: 获取变量num_smem_areas的地址

    @param: none
    
    @return: 变量num_smem_areas的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_num_smem_areas(void);
#endif


/**
    @function: int srecorder_init_kernel_symbols(srecorder_module_init_params_t *pinit_params)
    @brief: 初始化s_kallsyms_lookup_name并给syschk_sym_addr_table结构中的各个
               符号查找对应的虚拟地址

    @param: pinit_params
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_init_kernel_symbols(srecorder_module_init_params_t *pinit_params);


#ifdef __cplusplus
}
#endif
#endif /* SRECORDER_KERNEL_SYMBOLS_H */

