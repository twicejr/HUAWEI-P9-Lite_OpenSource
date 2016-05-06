/**
    @copyright: Huawei Technologies Co., Ltd. 2012-2013. All rights reserved.
    
    @file: srecorder_modem_log.c
    
    @brief: 导出modem死机堆栈和运行日志。
    
    @version: 1.0 
    
    @author: QiDechun ID: 216641
    
    @date: 2013-01-18
    
    @history:
*/

/*----includes-----------------------------------------------------------------------*/

#include <linux/stddef.h>
#include <linux/timer.h>
#include <linux/timex.h>
#include <linux/rtc.h>

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <asm/uaccess.h>
#include <linux/ctype.h>
#include <linux/cpufreq.h>
#include <asm/sizes.h>

#ifdef CONFIG_ARM
#include <asm/cpu.h>
#endif

#include "../include/srecorder_kernel_symbols.h"
#include "../include/srecorder_modem_log.h"
#include "../include/srecorder_snprintf.h"
#include "../include/srecorder_save_log.h"
#include "../include/srecorder_common.h"

#if defined(CONFIG_DUMP_MODEM_LOG)

#include <linux/remote_spinlock.h>
#include <mach/msm_smsm.h>
#include <mach/msm_iomap.h>


/*----local macroes------------------------------------------------------------------*/

#define SZ_DIAG_ERR_MSG 0xC8
#define ID_DIAG_ERR_MSG SMEM_DIAG_ERR_MESSAGE
#define SMD_HEAP_SIZE 512
#define BASE_ADDR_MASK 0xfffffffc

#define MODEM_CRASH_LOG_MAX_LENGTH (0x20000) /* 128KB */


/*----local prototypes----------------------------------------------------------------*/

struct smem_proc_comm
{
    unsigned command;
    unsigned status;
    unsigned data1;
    unsigned data2;
};

struct smem_heap_info
{
    unsigned initialized;
    unsigned free_offset;
    unsigned heap_remaining;
    unsigned reserved;
};

struct smem_heap_entry 
{
    unsigned allocated;
    unsigned offset;
    unsigned size;
    unsigned reserved; /* bits 1:0 reserved, bits 31:2 aux smem base addr */
};

struct smem_shared 
{
    struct smem_proc_comm proc_comm[4];
    unsigned version[32];
    struct smem_heap_info heap_info;
    struct smem_heap_entry heap_toc[SMD_HEAP_SIZE];
};

struct smem_area 
{
    void *phys_addr;
    unsigned size;
    void __iomem *virt_addr;
};


/*----local variables------------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----local function prototypes---------------------------------------------------------*/

static void *srecorder_smem_range_check(void *base, unsigned offset);
static void *srecorder_smem_get_entry(unsigned id, unsigned *size);
static void *srecorder_smem_find(unsigned id, unsigned size_in);
#if defined(CONFIG_DUMP_MODEM_LOG_BY_FIQ)
static void srecorder_do_delay(volatile unsigned long loop_times);
#endif
static int srecorder_debug_modem_err(srecorder_reserved_mem_info_t *pmem_info);
static int srecorder_debug_modem_err_f3(srecorder_reserved_mem_info_t *pmem_info);


/*----function definitions--------------------------------------------------------------*/

static void *srecorder_smem_range_check(void *base, unsigned offset)
{
    int i = 0;
    void *phys_addr = NULL;
    unsigned size;
    uint32_t num_smem_areas = 0;
    struct smem_area *smem_area = NULL;
    
    if (unlikely(INVALID_KSYM_ADDR == srecorder_get_num_smem_areas() 
        || INVALID_KSYM_ADDR == srecorder_get_smem_areas()))
    {
        return NULL;
    }
    
    num_smem_areas = *(int *)srecorder_get_num_smem_areas();
    smem_area = (struct smem_area *)(*(srec_ksym_addr_t *)srecorder_get_smem_areas());
    if (unlikely(NULL == smem_area))
    {
        return NULL;
    }
    
    for (i = 0; i < num_smem_areas; ++i) 
    {
        phys_addr = smem_area[i].phys_addr;
        size = smem_area[i].size;
        if (base < phys_addr)
        {
            return NULL;
        }
        
        if (base > phys_addr + size)
        {
            continue;
        }
        
        if (base >= phys_addr && base + offset < phys_addr + size)
        {
            return smem_area[i].virt_addr + offset;
        }
    }

    return NULL;
}


static void *srecorder_smem_get_entry(unsigned id, unsigned *size)
{
    struct smem_shared *shared = (void *)MSM_SHARED_RAM_BASE;
    struct smem_heap_entry *toc = shared->heap_toc;
    void *ret = NULL;
    int spinlocks_initialized = 0;
    int has_lock = 0;
    unsigned long flags = 0;
    
    if (INVALID_KSYM_ADDR == srecorder_get_spinlocks_initialized() || INVALID_KSYM_ADDR == srecorder_get_remote_spinlock())
    {
        return ret;
    }

    if (id >= SMEM_NUM_ITEMS)
    {
        return ret;
    }
    
    spinlocks_initialized= *(int *)srecorder_get_spinlocks_initialized();
    if (0 != spinlocks_initialized)
    {
        has_lock = remote_spin_trylock_irqsave((remote_spinlock_t *)srecorder_get_remote_spinlock(), flags);
    }

    if (0 == spinlocks_initialized || (0 != spinlocks_initialized && 0 != has_lock))
    {
        /* toc is in device memory and cannot be speculatively accessed */
        if (toc[id].allocated)
        {
            *size = toc[id].size;
            barrier();
            if (!(toc[id].reserved & BASE_ADDR_MASK))
            {
                ret = (void *) (MSM_SHARED_RAM_BASE + toc[id].offset);
            }
            else
            {
                ret = srecorder_smem_range_check((void *)(toc[id].reserved & BASE_ADDR_MASK), toc[id].offset);
            }
        } 
        else 
        {
            *size = 0;
        }
    }
    
    if (0 != spinlocks_initialized && 0 != has_lock)
    {
        remote_spin_unlock_irqrestore((remote_spinlock_t *)srecorder_get_remote_spinlock(), flags);
    }
    
    return ret;
}


static void *srecorder_smem_find(unsigned id, unsigned size_in)
{
    unsigned size;
    void *ptr;

    ptr = srecorder_smem_get_entry(id, &size);
    if (NULL == ptr)
    {
        return NULL;
    }

    size_in = ALIGN(size_in, 8);
    if (size_in != size) 
    {
        pr_err("smem_find(%d, %d): wrong size %d\n", id, size_in, size);
        return 0;
    }

    return ptr;
}


#if defined(CONFIG_DUMP_MODEM_LOG_BY_FIQ)
static void srecorder_do_delay(volatile unsigned long loop_times)
{
    volatile unsigned long i = 0;
    
    while (i < loop_times)
    {
        i++;
    }
}
#endif


static int srecorder_debug_modem_err(srecorder_reserved_mem_info_t *pmem_info)
{
    char *x;
    int size;
    int i = 0;
    int bytes_read = 0;

    int max = MIN(MODEM_CRASH_LOG_MAX_LENGTH, pmem_info->bytes_left - (DMESG_MAX_LENGTH + SZ_1K));

    x = srecorder_smem_find(ID_DIAG_ERR_MSG, SZ_DIAG_ERR_MSG);
    if (NULL != x) 
    {
        x[SZ_DIAG_ERR_MSG - 1] = 0;
        bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, max - i, 
            "smem: DIAG '%s'\n", x);
        srecorder_renew_meminfo(pmem_info, bytes_read);
        i += bytes_read;
    }

    x = srecorder_smem_get_entry(SMEM_ERR_CRASH_LOG, &size);
    if (NULL != x) 
    {
        x[size - 1] = 0;
        bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, max - i, 
            "smem: CRASH LOG\n'%s'\n", x);
        srecorder_renew_meminfo(pmem_info, bytes_read);
        i += bytes_read;
    }
    
    /* 删除此处3行 */
    
    return i;
}


/* 修正此函数的实现 */
static int srecorder_debug_modem_err_f3(srecorder_reserved_mem_info_t *pmem_info)
{
    char *x = NULL;
    int size = 0;
    int i = 0;
    int mod_value = 0;
    int data_len = sizeof(unsigned long long);

    x = srecorder_smem_get_entry(SMEM_ERR_F3_TRACE_LOG, &size);
    if (NULL == x) 
    {
        return 0;
    }
    
    mod_value = (int)(pmem_info->start_addr + pmem_info->bytes_read) % 4; /* 4字节对齐，否则会出现对齐错误 */
    if (0 != mod_value)
    {
        srecorder_renew_meminfo(pmem_info, 4 - mod_value); /* 同上 */
    }
    
    size = MIN(size, pmem_info->bytes_left);
    while (size > 0)
    {
        if (size >= data_len)
        {
            *((unsigned long long*)(pmem_info->start_addr + pmem_info->bytes_read)) = *(unsigned long long*)x;
            srecorder_renew_meminfo(pmem_info, data_len);
            x += data_len;
            size -= data_len;
        }
        else
        {
            for (i = 0; i < size; i++)
            {
                *(pmem_info->start_addr + pmem_info->bytes_read) = *(x + i);
            }
            srecorder_renew_meminfo(pmem_info, size);
            break;
        }
    }
   
    return i;
}

/**
    @function: int srecorder_get_modem_log(srecorder_reserved_mem_info_for_log_t *pmem_info)
    @brief: 读取modem死机堆栈和运行日志

    @param: pmem_info SRecorder的保留内存信息
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_get_modem_log(srecorder_reserved_mem_info_t *pmem_info)
{
    psrecorder_info_header_t pinfo_header = NULL;
    
    if (unlikely(NULL == pmem_info))
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param or kernel symbol addr!\n", __FILE__, __LINE__);
        return -1;
    }

    if (srecorder_log_has_been_dumped(MODEM_ERR_BIT7))
    {
        SRECORDER_PRINTK("modem err has been dumped successfully!\n");
    }

    if (srecorder_log_has_been_dumped(MODEM_ERR_F3_BIT8))
    {
        SRECORDER_PRINTK("modem err f3 has been dumped successfully!\n");
    }
    
    if (pmem_info->dump_modem_crash_log_only)
    {
#if defined(CONFIG_DUMP_MODEM_LOG_BY_FIQ)
        if (pmem_info->do_delay_when_dump_modem_log)
        {
            /* do delay about 10ms */
            unsigned long ips = 0;
            
            ips = cpufreq_get_directly(smp_processor_id()) * 1000; /* KHZ = 1000*/
            if (unlikely(0x0 == ips))
            {
                ips = CONFIG_CPU_FREQ_DEFAULT_VALUE;
            }
            
            if (likely(0x0 != CONFIG_DUMP_MODEM_LOG_DELAY_MAX_MS))
            {
                srecorder_do_delay(ips / (1000 / CONFIG_DUMP_MODEM_LOG_DELAY_MAX_MS));
            }
        }
#endif

#if !defined(CONFIG_ARCH_MSM8930)
        if (!srecorder_log_has_been_dumped(MODEM_ERR_BIT7))
        {
            if (0 != srecorder_write_info_header(pmem_info, MODEM_ERR_BIT7, &pinfo_header))
            {
                return -1;
            }
            srecorder_debug_modem_err(pmem_info);
            srecorder_validate_info_header(pinfo_header, pmem_info->bytes_per_type);
        }
#else
#endif
        
#if !defined(CONFIG_ARCH_MSM8930)
        if (!srecorder_log_has_been_dumped(MODEM_ERR_F3_BIT8))
        {
            if (0 != srecorder_write_info_header(pmem_info, MODEM_ERR_F3_BIT8, &pinfo_header))
            {
                return -1;
            }
            srecorder_debug_modem_err_f3(pmem_info);
            srecorder_validate_info_header(pinfo_header, pmem_info->bytes_per_type);
        }
#else
#endif
    }
    
    return 0;
}


/**
    @function: int srecorder_init_modem_log(srecorder_module_init_params_t *pinit_params)
    @brief: 初始化modem日志模块

    @param: pinit_params 模块初始化数据
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_init_modem_log(srecorder_module_init_params_t *pinit_params)
{
    srecorder_clear_log_dumped_bit(MODEM_ERR_BIT7);
    srecorder_clear_log_dumped_bit(MODEM_ERR_F3_BIT8);
    
    return 0;
}


/**
    @function: void srecorder_exit_modem_log(void)
    @brief: 退出modem日志模块

    @param: none
    
    @return: none

    @note: 
*/
void srecorder_exit_modem_log(void)
{
    srecorder_set_log_dumped_bit(MODEM_ERR_BIT7);
    srecorder_set_log_dumped_bit(MODEM_ERR_F3_BIT8);
}
#else
int srecorder_get_modem_log(srecorder_reserved_mem_info_t *pmem_info)
{
    return 0;
}


int srecorder_init_modem_log(srecorder_module_init_params_t *pinit_params)
{
    return 0;
}


void srecorder_exit_modem_log(void)
{
    return;
}
#endif

