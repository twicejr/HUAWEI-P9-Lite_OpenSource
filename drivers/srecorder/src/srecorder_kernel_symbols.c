/**
    @copyright: Huawei Technologies Co., Ltd. 2012-2012. All rights reserved.
    
    @file: srecorder_kernel_symbols.c
    
    @brief: 读取内核符号的地址
    
    @version: 1.0 
    
    @author: QiDechun ID: 216641
    
    @date: 2012-06-21
    
    @history:
*/

/*----includes-----------------------------------------------------------------------*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <linux/slab.h>
#include <linux/kallsyms.h>
#include <linux/version.h>

#include <asm/uaccess.h>
//#include <asm/errno.h>

#include "../include/srecorder_common.h"
#include "../include/srecorder_kernel_symbols.h"


/*----local macroes------------------------------------------------------------------*/

//#define KALLSYMS_LOOKUP_NAME_FUNC ("kallsyms_lookup_name")


/*----local prototypes----------------------------------------------------------------*/

/*地址与符号对应结构*/
typedef struct __syschk_sym_addr
{
    char *symbol_name;
    srec_ksym_addr_t *symbol_address;
}syschk_sym_addr;

typedef srec_ksym_addr_t (*kallsyms_lookup_name_func)(const char *name);


/*----local variables------------------------------------------------------------------*/

/*kallsyms_lookup_name (获取内核符号) 函数内核虚地址*/
static kallsyms_lookup_name_func s_kallsyms_lookup_name = NULL;

#if !USE_LICENSE_GPL
static srec_ksym_addr_t s_atomic_notifier_chain_register = INVALID_KSYM_ADDR;
static srec_ksym_addr_t s_atomic_notifier_chain_unregister = INVALID_KSYM_ADDR;
#ifdef CONFIG_KPROBES
static srec_ksym_addr_t s_register_jprobe = INVALID_KSYM_ADDR;
static srec_ksym_addr_t s_unregister_jprobe = INVALID_KSYM_ADDR;
static srec_ksym_addr_t  s_jprobe_return = INVALID_KSYM_ADDR;
#endif
static srec_ksym_addr_t s_register_oom_notifier = INVALID_KSYM_ADDR;
static srec_ksym_addr_t s_unregister_oom_notifier = INVALID_KSYM_ADDR;
#endif


/*==================================================================*/
/*             local variables for dump crash time begin            */
/*==================================================================*/
#if defined(CONFIG_DUMP_CRASH_TIME)
#endif
/*==================================================================*/
/*             local variables for dump crash time end              */
/*==================================================================*/


/*==================================================================*/
/*             local variables for dump sys info begin              */
/*==================================================================*/
#if defined(CONFIG_DUMP_SYS_INFO)
static srec_ksym_addr_t s_cpu_name = INVALID_KSYM_ADDR;
static srec_ksym_addr_t s_machine_name = INVALID_KSYM_ADDR;
static srec_ksym_addr_t s_all_bdevs = INVALID_KSYM_ADDR;
static srec_ksym_addr_t s_bdev_lock = INVALID_KSYM_ADDR;

#ifdef CONFIG_SWAP
static srec_ksym_addr_t s_nr_swapfiles = INVALID_KSYM_ADDR;
static srec_ksym_addr_t s_swap_info = INVALID_KSYM_ADDR;
static srec_ksym_addr_t s_swap_lock = INVALID_KSYM_ADDR;
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 0))
static srec_ksym_addr_t s_vmap_area_lock = INVALID_KSYM_ADDR;
static srec_ksym_addr_t s_vmap_area_list = INVALID_KSYM_ADDR;
#endif
#endif
/*==================================================================*/
/*             local variables for dump sys info end                */
/*==================================================================*/


/*==================================================================*/
/*               local variables for dump dmesg begin               */
/*==================================================================*/
/*有关获取dmesg内核消息的静态变量*/
#if defined(CONFIG_DUMP_DMESG)
static srec_ksym_addr_t s_log_buf = INVALID_KSYM_ADDR;
static srec_ksym_addr_t s_log_buf_len = INVALID_KSYM_ADDR;
static srec_ksym_addr_t s_log_end = INVALID_KSYM_ADDR;
#endif
/*==================================================================*/
/*               local variables for dump dmesg end                 */
/*==================================================================*/


/*==================================================================*/
/*           local variables for dump allcpu stack begin            */
/*==================================================================*/
#if defined(CONFIG_DUMP_ALLCPU_STACK)
#endif
/*==================================================================*/
/*            local variables for dump allcpu stack end             */
/*==================================================================*/


/*==================================================================*/
/*             local variables for dump modem log begin             */
/*==================================================================*/
#if defined(CONFIG_DUMP_MODEM_LOG)
static srec_ksym_addr_t s_spinlocks_initialized = INVALID_KSYM_ADDR;
static srec_ksym_addr_t s_remote_spinlock = INVALID_KSYM_ADDR;
static srec_ksym_addr_t s_smem_areas = INVALID_KSYM_ADDR;
static srec_ksym_addr_t s_num_smem_areas = INVALID_KSYM_ADDR;
#endif
/*==================================================================*/
/*             local variables for dump modem log end               */
/*==================================================================*/

#if defined(CONFIG_DUMP_ALLCPU_STACK) || defined(CONFIG_DUMP_ALLPS_INFO)
#endif


/*==================================================================*/
/*            local variables for doing backtrace begin             */
/*==================================================================*/
#ifdef CONFIG_FUNCTION_GRAPH_TRACER
#endif

#ifdef CONFIG_ARM_UNWIND
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 2, 0))
static srec_ksym_addr_t s___origin_unwind_idx = INVALID_KSYM_ADDR;
#endif
static srec_ksym_addr_t s_unwind_tables = INVALID_KSYM_ADDR;
static srec_ksym_addr_t s_unwind_lock = INVALID_KSYM_ADDR;
#endif
/*==================================================================*/
/*             local variables for doing backtrace end              */
/*==================================================================*/


/*==================================================================*/
/*            local variables for dump all ps info begin            */
/*==================================================================*/
#if defined(CONFIG_DUMP_ALLPS_INFO)
#endif
/*==================================================================*/
/*             local variables for dump all ps info end             */
/*==================================================================*/


/*==================================================================*/
/*        local variables for dump current ps backtrace begin       */
/*==================================================================*/
#if defined(CONFIG_DUMP_CURRENT_PS_BACKTRACE)
static srec_ksym_addr_t s_arch_vma_name = INVALID_KSYM_ADDR;

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 38))
static srec_ksym_addr_t s_dcache_lock = INVALID_KSYM_ADDR;
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 36))
static srec_ksym_addr_t s_vfsmount_lock_lock = INVALID_KSYM_ADDR;
#else
static srec_ksym_addr_t s_vfsmount_lock = INVALID_KSYM_ADDR;
#endif
#endif
/*==================================================================*/
/*         local variables for dump current ps backtrace end        */
/*==================================================================*/


/*==================================================================*/
/*             local variables for dump slab info begin             */
/*==================================================================*/
#if defined(CONFIG_DUMP_SLAB_INFO)
#ifdef CONFIG_SLAB
static srec_ksym_addr_t s_cache_chain = INVALID_KSYM_ADDR;
static srec_ksym_addr_t s_cache_chain_mutex = INVALID_KSYM_ADDR;
#elif defined(CONFIG_SLUB)
static srec_ksym_addr_t s_slab_caches = INVALID_KSYM_ADDR;
static srec_ksym_addr_t s_slub_lock = INVALID_KSYM_ADDR;
#endif
#endif
/*==================================================================*/
/*             local variables for dump slab info end               */
/*==================================================================*/

/* 将需要查找地址的符号放入该结构体数组 */
static syschk_sym_addr s_kernel_symbols_table[] = 
{      
    /*atomic_notifier_chain_register*/
#if !USE_LICENSE_GPL
    {"atomic_notifier_chain_register", &s_atomic_notifier_chain_register}, 
    {"atomic_notifier_chain_unregister", &s_atomic_notifier_chain_unregister}, 
#ifdef CONFIG_KPROBES
    {"register_jprobe", &s_register_jprobe}, 
    {"unregister_jprobe", &s_unregister_jprobe}, 
    {"jprobe_return", &s_jprobe_return}, 
#endif
    {"register_oom_notifier", &s_register_oom_notifier}, 
    {"unregister_oom_notifier", &s_unregister_oom_notifier}, 
#endif

    /*==================================================================*/
    /*             local variables for dump crash time begin            */
    /*==================================================================*/
#if defined(CONFIG_DUMP_CRASH_TIME)
#endif
    /*==================================================================*/
    /*             local variables for dump crash time end              */
    /*==================================================================*/


    /*==================================================================*/
    /*             local variables for dump sys info begin              */
    /*==================================================================*/
#if defined(CONFIG_DUMP_SYS_INFO)
    {"cpu_name", &s_cpu_name}, 
    {"machine_name", &s_machine_name}, 
    {"all_bdevs", &s_all_bdevs}, 
    {"bdev_lock", &s_bdev_lock}, 
    
#ifdef CONFIG_SWAP
    {"nr_swapfiles", &s_nr_swapfiles}, 
    {"swap_info", &s_swap_info}, 
    {"swap_lock", &s_swap_lock}, 
#endif
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 0))
    {"vmap_area_lock", &s_vmap_area_lock}, 
    {"vmap_area_list", &s_vmap_area_list}, 
#endif
#endif
    /*==================================================================*/
    /*             local variables for dump sys info end                */
    /*==================================================================*/

    
    /*==================================================================*/
    /*               local variables for dump dmesg begin               */
    /*==================================================================*/
#if defined(CONFIG_DUMP_DMESG)
#endif
    /*==================================================================*/
    /*               local variables for dump dmesg end                 */
    /*==================================================================*/
    

    /*==================================================================*/
    /*           local variables for dump allcpu stack begin            */
    /*==================================================================*/
#if defined(CONFIG_DUMP_ALLCPU_STACK)
    /*如下变量用于获取系统信息*/
#endif
    /*==================================================================*/
    /*            local variables for dump allcpu stack end             */
    /*==================================================================*/


    /*==================================================================*/
    /*             local variables for dump modem log begin             */
    /*==================================================================*/
#if defined(CONFIG_DUMP_MODEM_LOG)
    {"spinlocks_initialized", &s_spinlocks_initialized}, 
    {"remote_spinlock", &s_remote_spinlock}, 
    {"smem_areas", &s_smem_areas}, 
    {"num_smem_areas", &s_num_smem_areas}, 
#endif
    /*==================================================================*/
    /*             local variables for dump modem log end               */
    /*==================================================================*/
    
#if defined(CONFIG_DUMP_ALLCPU_STACK) || defined(CONFIG_DUMP_ALLPS_INFO)
    /*如下变量用于获取所有进程信息*/
#endif

    /*如下变量用于获取内核调用栈*/    
    /*==================================================================*/
    /*            local variables for doing backtrace begin             */
    /*==================================================================*/
    /* 以下变量用于获取内核调用栈信息 */
#ifdef CONFIG_FUNCTION_GRAPH_TRACER
#endif

#ifdef CONFIG_ARM_UNWIND
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 2, 0))
    {"__origin_unwind_idx", &s___origin_unwind_idx}, 
#endif
    {"unwind_tables", &s_unwind_tables}, 
    {"unwind_lock", &s_unwind_lock}, 
#endif
    /*==================================================================*/
    /*             local variables for doing backtrace end              */
    /*==================================================================*/


    /*==================================================================*/
    /*            local variables for dump all ps info begin            */
    /*==================================================================*/
#if defined(CONFIG_DUMP_ALLPS_INFO)
#endif
    /*==================================================================*/
    /*             local variables for dump all ps info end             */
    /*==================================================================*/


    /*==================================================================*/
    /*        local variables for dump current ps backtrace begin       */
    /*==================================================================*/
#if defined(CONFIG_DUMP_CURRENT_PS_BACKTRACE)
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 36))
    {"vfsmount_lock_lock", &s_vfsmount_lock_lock}, 
#else
    {"vfsmount_lock", &s_vfsmount_lock}, 
#endif

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 38))
    {"dcache_lock", &s_dcache_lock}, 
#endif

    /* 用于得到当前进程用户态调用栈 */
    {"arch_vma_name", &s_arch_vma_name}, 
#endif
    /*==================================================================*/
    /*         local variables for dump current ps backtrace end        */
    /*==================================================================*/

    
    /*==================================================================*/
    /*             local variables for dump slab info begin             */
    /*==================================================================*/
#if defined(CONFIG_DUMP_SLAB_INFO)
#ifdef CONFIG_SLAB
    {"cache_chain", &s_cache_chain}, 
    {"cache_chain_mutex", &s_cache_chain_mutex}, 
#elif defined(CONFIG_SLUB)
    {"slab_caches", &s_slab_caches}, 
    {"slub_lock", &s_slub_lock}, 
#endif
#endif
    /*==================================================================*/
    /*             local variables for dump slab info end               */
    /*==================================================================*/
};


/*----global variables-----------------------------------------------------------------*/

#if defined(CONFIG_DUMP_SYS_INFO) && !(defined(CONFIG_DEBUG_KERNEL) && defined(CONFIG_KALLSYMS_ALL))
extern unsigned long get_cpu_name(void);
extern unsigned long get_machine_name(void);
extern unsigned long get_all_bdevs(void);
extern unsigned long get_bdev_lock(void);
extern unsigned long get_nr_swapfiles(void);
extern unsigned long get_swap_lock(void);
extern unsigned long get_swap_info(void);
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 0))
extern unsigned long get_vmap_area_lock(void);
extern unsigned long get_vmap_area_list(void);
#endif
#endif

#if defined(CONFIG_DUMP_SLAB_INFO) && !(defined(CONFIG_DEBUG_KERNEL) && defined(CONFIG_KALLSYMS_ALL))
#ifdef CONFIG_SLAB
extern unsigned long get_cache_chain(void);
extern unsigned long get_cache_chain_mutex(void);
#elif defined(CONFIG_SLUB)
extern unsigned long get_slab_caches(void);
extern unsigned long get_slub_lock(void);
#endif
#endif


/*----local function prototypes---------------------------------------------------------*/

static int srecorder_get_other_symbols(void);

#ifndef CONFIG_KALLSYMS
static int srecorder_get_symbol_kallsyms_lookup_name(const char *line, int len);
#endif


/*----function definitions--------------------------------------------------------------*/

#if defined(CONFIG_DUMP_SYS_INFO)
/**
    @function: srec_ksym_addr_t srecorder_get_cpu_name(void)
    @brief: 获取变量cpu_name的地址

    @param: none
    
    @return: 变量cpu_name的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_cpu_name(void)
{
#if !(defined(CONFIG_DEBUG_KERNEL) && defined(CONFIG_KALLSYMS_ALL))
    s_cpu_name = get_cpu_name();
#endif
    
    return s_cpu_name;
}


/**
    @function: srec_ksym_addr_t srecorder_get_machine_name(void)
    @brief: 获取变量machine_name的地址

    @param: none
    
    @return: 变量machine_name的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_machine_name(void)
{
#if !(defined(CONFIG_DEBUG_KERNEL) && defined(CONFIG_KALLSYMS_ALL))
    s_machine_name = get_machine_name();
#endif
    
    return s_machine_name;
}


/**
    @function: srec_ksym_addr_t srecorder_get_all_bdevs(void)
    @brief: 获取变量all_bdevs的地址

    @param: none
    
    @return: 变量all_bdevs的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_all_bdevs(void)
{
#if !(defined(CONFIG_DEBUG_KERNEL) && defined(CONFIG_KALLSYMS_ALL))
    s_all_bdevs = get_all_bdevs();
#endif
    
    return s_all_bdevs;
}


/**
    @function: srec_ksym_addr_t srecorder_get_bdev_lock(void)
    @brief: 获取变量bdev_lock的地址

    @param: none
    
    @return: 变量bdev_lock的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_bdev_lock(void)
{
#if !(defined(CONFIG_DEBUG_KERNEL) && defined(CONFIG_KALLSYMS_ALL))
    s_bdev_lock = get_bdev_lock();
#endif
    
    return s_bdev_lock;
}


#ifdef CONFIG_SWAP
/**
    @function: srec_ksym_addr_t srecorder_get_nr_swapfiles(void)
    @brief: 获取变量nr_swapfiles的地址

    @param: none
    
    @return: 变量nr_swapfiles的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_nr_swapfiles(void)
{
#if !(defined(CONFIG_DEBUG_KERNEL) && defined(CONFIG_KALLSYMS_ALL))
    s_nr_swapfiles = get_nr_swapfiles();
#endif

    return s_nr_swapfiles;
}


/**
    @function: srec_ksym_addr_t srecorder_get_swap_info(void)
    @brief: 获取变量swap_info的地址

    @param: none
    
    @return: 变量swap_info的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_swap_info(void)
{
#if !(defined(CONFIG_DEBUG_KERNEL) && defined(CONFIG_KALLSYMS_ALL))
    s_swap_info = get_swap_info();
#endif

    return s_swap_info;
}


/**
    @function: srec_ksym_addr_t srecorder_get_swap_lock(void)
    @brief: 获取变量swap_lock的地址

    @param: none
    
    @return: 变量swap_lock的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_swap_lock(void)
{
#if !(defined(CONFIG_DEBUG_KERNEL) && defined(CONFIG_KALLSYMS_ALL))
    s_swap_lock = get_swap_lock();
#endif

    return s_swap_lock;
}
#endif


/**
    @function: srec_ksym_addr_t srecorder_get_vmap_area_lock(void)
    @brief: 获取变量swap_lock的地址

    @param: none
    
    @return: 变量vmap_area_lock的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_vmap_area_lock(void)
{
#if !(defined(CONFIG_DEBUG_KERNEL) && defined(CONFIG_KALLSYMS_ALL))
    s_vmap_area_lock = get_vmap_area_lock();
#endif

    return s_vmap_area_lock;
}


/**
    @function: srec_ksym_addr_t srecorder_get_vmap_area_list(void)
    @brief: 获取变量swap_lock的地址

    @param: none
    
    @return: 变量vmap_area_list的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_vmap_area_list(void)
{
#if !(defined(CONFIG_DEBUG_KERNEL) && defined(CONFIG_KALLSYMS_ALL))
    s_vmap_area_list = get_vmap_area_list();
#endif

    return s_vmap_area_list;
}
#endif


#if defined(CONFIG_DUMP_MODEM_LOG)
/**
    @function: srec_ksym_addr_t srecorder_get_spinlocks_initialized(void)
    @brief: 获取变量spinlocks_initialized的地址

    @param: none
    
    @return: 变量spinlocks_initialized的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_spinlocks_initialized(void)
{
    return s_spinlocks_initialized;
}


/**
    @function: srec_ksym_addr_t srecorder_get_remote_spinlock(void)
    @brief: 获取变量remote_spinlock的地址

    @param: none
    
    @return: 变量remote_spinlock的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_remote_spinlock(void)
{
    return s_remote_spinlock;
}


/**
    @function: srec_ksym_addr_t srecorder_get_smem_areas(void)
    @brief: 获取变量smem_areas的地址

    @param: none
    
    @return: 变量smem_areas的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_smem_areas(void)
{
    return s_smem_areas;
}


/**
    @function: srec_ksym_addr_t srecorder_get_num_smem_areas(void)
    @brief: 获取变量num_smem_areas的地址

    @param: none
    
    @return: 变量num_smem_areas的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_num_smem_areas(void)
{
    return s_num_smem_areas;
}
#endif


#if defined(CONFIG_DUMP_CURRENT_PS_BACKTRACE)
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 36))
/**
    @function: srec_ksym_addr_t srecorder_get_vfsmount_lock_lock(void)
    @brief: 获取变量vfsmount_lock_lock的地址

    @param: none
    
    @return: 变量vfsmount_lock_lock的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_vfsmount_lock_lock(void)
{
    return s_vfsmount_lock_lock;
}
#else
/**
    @function: srec_ksym_addr_t srecorder_get_vfsmount_lock(void)
    @brief: 获取变量vfsmount_lock的地址

    @param: none
    
    @return: 变量vfsmount_lock的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_vfsmount_lock(void)
{
    return s_vfsmount_lock;
}
#endif


#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 38))
/**
    @function: srec_ksym_addr_t srecorder_get_dcache_lock(void)
    @brief: 获取变量dcache_lock的地址

    @param: none
    
    @return: 变量dcache_lock的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_dcache_lock(void)
{
    return s_dcache_lock;
}
#else
/**
    @function: srec_ksym_addr_t srecorder_get_rename_lock(void)
    @brief: 获取变量rename_lock的地址

    @param: none
    
    @return: 变量rename_lock的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_rename_lock(void)
{
    return (srec_ksym_addr_t)&rename_lock;
}
#endif


/**
    @function: srec_ksym_addr_t srecorder_get_arch_vma_name(void)
    @brief: 获取函数arch_vma_name的地址

    @param: none
    
    @return: 函数arch_vma_name的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_arch_vma_name(void)
{
    return s_arch_vma_name;
}
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
srec_ksym_addr_t srecorder_get___origin_unwind_idx(void)
{
    return s___origin_unwind_idx;
}
#endif


/**
    @function: srec_ksym_addr_t srecorder_get_unwind_tables(void)
    @brief: 获取变量unwind_tables的地址

    @param: none
    
    @return: 变量unwind_tables的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_unwind_tables(void)
{
    return s_unwind_tables;
}


/**
    @function: srec_ksym_addr_t srecorder_get_unwind_lock(void)
    @brief: 获取变量unwind_lock的地址

    @param: none
    
    @return: 变量unwind_lock的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_unwind_lock(void)
{
    return s_unwind_lock;
}
#endif


#if defined(CONFIG_DUMP_ALLPS_INFO)
#endif


#if defined(CONFIG_DUMP_ALLCPU_STACK) || defined(CONFIG_DUMP_ALLPS_INFO)
#endif


#if defined(CONFIG_DUMP_ALLCPU_STACK)
#endif


#if !USE_LICENSE_GPL
/**
    @function: srec_ksym_addr_t srecorder_get_atomic_notifier_chain_register(void)
    @brief: 获取函数atomic_notifier_chain_register的地址

    @param: none
    
    @return: atomic_notifier_chain_register的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_atomic_notifier_chain_register(void)
{
    return s_atomic_notifier_chain_register;
}


/**
    @function: srec_ksym_addr_t srecorder_get_atomic_notifier_chain_unregister(void)
    @brief: 获取函数atomic_notifier_chain_unregister的地址

    @param: none
    
    @return: atomic_notifier_chain_unregister的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_atomic_notifier_chain_unregister(void)
{
    return s_atomic_notifier_chain_unregister;
}


#ifdef CONFIG_KPROBES
/**
    @function: srec_ksym_addr_t srecorder_get_register_jprobe(void)
    @brief: 获取函数register_jprobe的地址

    @param: none
    
    @return: 函数register_jprobe的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_register_jprobe(void)
{
    return s_register_jprobe;
}


/**
    @function: srec_ksym_addr_t srecorder_get_unregister_jprobe(void)
    @brief: 获取函数unregister_jprobe的地址

    @param: none
    
    @return: 函数unregister_jprobe的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_unregister_jprobe(void)
{
    return s_unregister_jprobe;
}
#endif


/**
    @function: srec_ksym_addr_t srecorder_get_jprobe_return(void)
    @brief: 获取函数jprobe_return的地址

    @param: none
    
    @return: 函数jprobe_return的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_jprobe_return(void)
{
    return s_jprobe_return;
}


/**
    @function: srec_ksym_addr_t srecorder_get_register_oom_notifier(void)
    @brief: 获取函数register_oom_notifier的地址

    @param: none
    
    @return: 函数register_oom_notifier的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_register_oom_notifier(void)
{
    return s_register_oom_notifier;
}


/**
    @function: srec_ksym_addr_t srecorder_get_unregister_oom_notifier(void)
    @brief: 获取函数unregister_oom_notifier的地址

    @param: none
    
    @return: 函数unregister_oom_notifier的地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_unregister_oom_notifier(void)
{
    return s_unregister_oom_notifier;
}
#endif


#if defined(CONFIG_DUMP_DMESG)
/**
    @function: srec_ksym_addr_t srecorder_get_log_buf(void)
    @brief: 得到内核ring buffer的起始地址

    @param: none
    
    @return: 内核ring buffer起始地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_log_buf(void)
{
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 5, 0))
    if (INVALID_KSYM_ADDR == s_log_buf)
    {
        get_log_buf_info(&s_log_buf, &s_log_end, &s_log_buf_len);
    }
#endif
    return s_log_buf;
}


/**
    @function: srec_ksym_addr_t srecorder_get_log_buf_len(void)
    @brief: 得到内核变量log_buf_len的起始地址

    @param: none
    
    @return: 内核变量log_buf_len的起始地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_log_buf_len(void)
{
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 5, 0))
    if (INVALID_KSYM_ADDR == s_log_buf_len)
    {
        get_log_buf_info(&s_log_buf, &s_log_end, &s_log_buf_len);
    }
#endif

    return s_log_buf_len;
}


/**
    @function: srec_ksym_addr_t srecorder_get_log_end(void)
    @brief: 得到内核变量log_end的起始地址

    @param: none
    
    @return: 内核变量log_end的起始地址

    @note: 
*/
srec_ksym_addr_t srecorder_get_log_end(void)
{
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 5, 0))
    if (INVALID_KSYM_ADDR == s_log_end)
    {
        get_log_buf_info(&s_log_buf, &s_log_end, &s_log_buf_len);
    }
#endif

    return s_log_end;
}
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
srec_ksym_addr_t srecorder_get_cache_chain(void)
{
#if !(defined(CONFIG_DEBUG_KERNEL) && defined(CONFIG_KALLSYMS_ALL))
    s_cache_chain = get_cache_chain();
#endif
    
    return s_cache_chain;
}


/**
    @function: srec_ksym_addr_t srecorder_get_cache_chain_mutex(void)
    @brief: 获取cache_chain_mutex的地址, 用于同步对cache_chain的读写
    
    @param: none
    
    @return: cache_chain_mutex

    @note: 
*/
srec_ksym_addr_t srecorder_get_cache_chain_mutex(void)
{
#if !(defined(CONFIG_DEBUG_KERNEL) && defined(CONFIG_KALLSYMS_ALL))
    s_cache_chain_mutex = get_cache_chain_mutex();
#endif
    
    return s_cache_chain_mutex;
}
#elif defined(CONFIG_SLUB)
/**
    @function: srec_ksym_addr_t srecorder_get_slab_caches(void)
    @brief: 获取slab_caches的地址, slab的信息存在它里面
    
    @param: none
    
    @return: slab_caches

    @note: 
*/
srec_ksym_addr_t srecorder_get_slab_caches(void)
{
#if !(defined(CONFIG_DEBUG_KERNEL) && defined(CONFIG_KALLSYMS_ALL))
    s_slab_caches = get_slab_caches();
#endif

    return s_slab_caches;
}


/**
    @function: srec_ksym_addr_t srecorder_get_slub_lock(void)
    @brief: 获取slub_lock的地址, 用于同步对slab_caches的读写
    
    @param: none
    
    @return: slub_lock

    @note: 
*/
srec_ksym_addr_t srecorder_get_slub_lock(void)
{
#if !(defined(CONFIG_DEBUG_KERNEL) && defined(CONFIG_KALLSYMS_ALL))
    s_slub_lock = get_slub_lock();
#endif
    
    return s_slub_lock;
}
#endif
#endif


/**
    @function: static int srecorder_get_other_symbols(void)
    @brief: 给s_kernel_symbols_table表中的内核符号找到对应的地址

    @param: none
    
    @return: 0 - 成功；<0-失败

    @note: 
*/
static int srecorder_get_other_symbols(void)
{
    int i = 0;
    int symbols_table_size = sizeof(s_kernel_symbols_table) / sizeof(s_kernel_symbols_table[0]);  

    for (i = 0; i < symbols_table_size; i++)
    {
        /*调用kallsyms_lookup_name查找符号对应的地址*/
        if (unlikely(NULL == s_kernel_symbols_table[i].symbol_name || NULL == s_kernel_symbols_table[i].symbol_address))
        {
            continue;
        }
        
        *(s_kernel_symbols_table[i].symbol_address) = s_kallsyms_lookup_name(s_kernel_symbols_table[i].symbol_name);
        if (INVALID_KSYM_ADDR == *(s_kernel_symbols_table[i].symbol_address))
        {
            PRINT_INFO(("Get %s failed.\n", s_kernel_symbols_table[i].symbol_name), DEBUG_KERNEL_SYMBOLS);
            continue; /*return -EFAULT; */ /* 不要因为一个符号的失败影响到其他符号的读取 */
        }
    }
    
    return 0;
}


#ifndef CONFIG_KALLSYMS
/**
    @function: static int srecorder_get_symbol_kallsyms_lookup_name(const char *line, int len)
    @brief: 给s_kernel_symbols_table表中的内核符号找到对应的地址

    @param: line - 在/proc/kallsyms中所读的一行内容
    @param: len - 暂时没用
    
    @return: 0 - 成功；<0-失败

    @note: 
*/
static int srecorder_get_symbol_kallsyms_lookup_name(const char *line, int len)
{
    int ret = 0;
    srec_ksym_addr_t address;    
    char *psymbolname = NULL;
    char *pmodulename = NULL;
    char dummy;

    if (NULL == line)
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return -EINVAL;
    }

    psymbolname = kmalloc(NAME_MAX, GFP_KERNEL);
    if (NULL == psymbolname)
    {
        ret = -ENOMEM;
        goto err_out;
    }

    pmodulename = kmalloc(NAME_MAX, GFP_KERNEL);
    if (NULL == pmodulename)
    {        
        ret = -ENOMEM;
        goto err_out;
    }

    memset(psymbolname, 0, NAME_MAX);
    memset(pmodulename, 0, NAME_MAX);

    /* 
   * 包含kallsyms_lookup_name的line的格式为"[address] [type] [symboleName]" 
   * 遇到"[address] [type] [symboleName] [moduleName]"格式直接返回 
   * /proc/kallsyms中每行一般3个参数
   */
    if (3 != sscanf(line, "%lx %c %s [%s]", &address, &dummy, psymbolname, pmodulename))
    {
        ret = -ENOENT;
        goto err_out;
    }

    /*判断是否是需要的符号kallsyms_lookup_name*/
    if (strncmp(KALLSYMS_LOOKUP_NAME_FUNC, psymbolname, NAME_MAX) != 0)
    {
        ret = -ENOENT;
        goto err_out;
    }

    s_kallsyms_lookup_name =  (kallsyms_lookup_name_func)address;
    ret = 0;

err_out:
    if (NULL != psymbolname)
    {
        kfree(psymbolname);
        psymbolname = NULL;
    }

    if (NULL != pmodulename)
    {
        kfree(pmodulename);
        pmodulename = NULL;
    }

    return ret;
}
#endif


/**
    @function: int srecorder_init_kernel_symbols(srecorder_module_init_params_t *pinit_params)
    @brief: 初始化s_kallsyms_lookup_name并给syschk_sym_addr_table结构中的各个
               符号查找对应的虚拟地址

    @param: pinit_params
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_init_kernel_symbols(srecorder_module_init_params_t *pinit_params)
{
    int ret;
    
#ifndef CONFIG_KALLSYMS
    int linelen = 0;
    int readlen = 0;
    int i = 0;
    int symbol_found = 0; /*0-没找到，非0-找到*/
    char *szbuff = NULL;
    char *szLine = NULL;
    struct file *file = NULL;
    mm_segment_t old_fs;

    szbuff = kmalloc(PAGE_SIZE, GFP_KERNEL);
    if (NULL == szbuff)
    {
        ret = -ENOMEM;
        goto err_out;
    }

    szLine = kmalloc(PAGE_SIZE, GFP_KERNEL);
    if (NULL == szLine)
    {
        ret = -ENOMEM;
        goto err_out;
    }

    file = filp_open("/proc/kallsyms", O_RDONLY, 0);
    if (IS_ERR(file))
    {
        ret = PTR_ERR(file);
        goto err_out;
    }

    if (!S_ISREG(file->f_path.dentry->d_inode->i_mode))
    {
        ret = -EACCES;
        goto err_out;
    }

    if (NULL == file->f_op->read)
    {
        ret = -EIO;
        goto err_out;
    }

    old_fs = get_fs();
    set_fs(get_ds());
    while ((readlen = file->f_op->read(file, (char*)szbuff, PAGE_SIZE - 1, &file->f_pos)) > 0
        && (0 == symbol_found))
    {
        /*找到一行，并赋值给szline后，调用函数kbox_testing_dump_get_kallsyms解析此行*/
        for (i = 0; i < readlen; i++)
        {
            if (linelen >= PAGE_SIZE - 1)
            {
                linelen = 0;
            }

            szLine[linelen] = szbuff[i];
            if (szLine[linelen] == '\n' )
            {
                szLine[linelen + 1] = 0;
                ret = srecorder_get_symbol_kallsyms_lookup_name(szLine, linelen + 1);
                linelen = 0;

                /*如果找到对应的函数地址，则退出循环*/
                if (0 == ret)
                {
                    symbol_found = 1;
                    break;
                }
                continue;
            }

            linelen++;
        }
    }

    /*判断是否找到kallsyms_lookup_name函数*/
    if (NULL == (void *)s_kallsyms_lookup_name)
    {
        PRINT_INFO(("can not find address for %s\n", KALLSYMS_LOOKUP_NAME_FUNC), DEBUG_KERNEL_SYMBOLS);
        ret = -EFAULT;
        goto err_out;
    }

    ret = srecorder_get_other_symbols();

    filp_close(file, NULL);
    file = NULL;
    set_fs(old_fs);

err_out:
    if (NULL != file)
    {
        filp_close(file, NULL);
    }

    if (NULL != szbuff)
    {
        kfree(szbuff);
    }

    if (NULL != szLine)
    {
        kfree(szLine);
    }
#else
    s_kallsyms_lookup_name = kallsyms_lookup_name;
#endif
    ret = srecorder_get_other_symbols();
    
    return ret;
}

