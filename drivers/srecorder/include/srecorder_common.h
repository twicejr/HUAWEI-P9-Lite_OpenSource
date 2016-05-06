/**
    @copyright: Huawei Technologies Co., Ltd. 2012-2012. All rights reserved.
    
    @file: srecorder_common.h
    
    @brief: 定义SRecorder整个工程中用到的全局资源
    
    @version: 1.0 
    
    @author: QiDechun ID: 216641
    
    @date: 2012-06-21
    
    @history:
*/

#ifndef SRECORDER_COMMON_H
#define SRECORDER_COMMON_H


/*----includes-----------------------------------------------------------------------*/

#include <linux/spinlock.h>
#include <linux/srecorder.h>


/*----c++ support--------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


/*----export macroes-----------------------------------------------------------------*/

/*==================================================================*/
/*                         模块License定义 begin                    */
/*==================================================================*/
#ifndef USE_LICENSE_GPL
#define USE_LICENSE_GPL (1)
#endif

#if USE_LICENSE_GPL
#define LICENSE_DESCRIPTION "GPL"
#else
#define LICENSE_DESCRIPTION "Proprietary"
#endif
/*==================================================================*/
/*                         模块License定义 end                      */
/*==================================================================*/


/*==================================================================*/
/*                       SRecorder控制开关 begin                    */
/*==================================================================*/
/* SRecorder Control Command */
#define SRECORDER_IOCTL_BASE 'S'
#define SRIOC_SET_DUMP_ENABLE_BIT _IOWR(SRECORDER_IOCTL_BASE, 0, unsigned long)
#define SRIOC_CLR_DUMP_ENABLE_BIT _IOWR(SRECORDER_IOCTL_BASE, 1, unsigned long)
#define SRIOC_SET_DUMP_ENABLE_BITS _IOWR(SRECORDER_IOCTL_BASE, 2, unsigned long)
#define SRIOC_GET_DUMP_ENABLE_BITS _IOWR(SRECORDER_IOCTL_BASE, 3, unsigned long)
#define SRIOC_ENABLE _IOWR(SRECORDER_IOCTL_BASE,  2012, unsigned long)
#define SRIOC_DISABLE _IOWR(SRECORDER_IOCTL_BASE,  2013, unsigned long)
#define SRIOC_CLEAN _IOWR(SRECORDER_IOCTL_BASE,  2014, unsigned long)
/*==================================================================*/
/*                       SRecorder控制开关 end                      */
/*==================================================================*/


/*==================================================================*/
/*                      日志导出高级功能开关 begin                  */
/*==================================================================*/
#ifdef CONFIG_POWERCOLLAPSE
#define DUMP_REBOOT_LOG (1) /* 处理系统重启 */
#else
#define DUMP_REBOOT_LOG (0) /* 不处理系统重启 */
#endif
/*==================================================================*/
/*                      日志导出高级功能开关 end                    */
/*==================================================================*/


/*==================================================================*/
/*                     与平台相关日志导出开关 begin                 */
/*==================================================================*/
#ifdef CONFIG_ARCH_MSM
#ifndef CONFIG_DUMP_MODEM_LOG_BY_FIQ
//#define CONFIG_DUMP_MODEM_LOG_BY_FIQ
#endif

#ifndef CONFIG_DUMP_MODEM_LOG_DELAY_MAX_MS
#define CONFIG_DUMP_MODEM_LOG_DELAY_MAX_MS (10) /* 在FIQ中延时10ms，针对高通平台 */
#endif

/* 用以从cpufreq模块获取cpu时钟频率失败时使用，默认值请根据实际平台更改 */
#ifndef CONFIG_CPU_FREQ_DEFAULT_VALUE
#define CONFIG_CPU_FREQ_DEFAULT_VALUE (1150000000UL) /* 1.15GHz */
#endif
#endif
/*==================================================================*/
/*                     与平台相关日志导出开关 end                   */
/*==================================================================*/


/*==================================================================*/
/*                       系统控制开关 begin                         */
/*==================================================================*/
#if defined(CONFIG_ARCH_MSM)
#define LET_MODEM_OR_WATCHDOG_RESET_SYSTEM (1) /* 为了不改变系统原有的错误处理流程，建议使用该配置 */
#else
#define LET_MODEM_OR_WATCHDOG_RESET_SYSTEM (0) /* 采用该配置时，SRecorder导完日志之后会立即重启系统 */
#endif
/*==================================================================*/
/*                         系统控制开关 end                         */
/*==================================================================*/


/*==================================================================*/
/*                         模块全局常量定义 begin                   */
/*==================================================================*/
#ifndef CONFIG_SRECORDER_VERSION
#define CONFIG_SRECORDER_VERSION ("0.0.0.1") /* 采用IPV4的模式 */
#endif

#define INVALID_KSYM_ADDR (0UL) /* 定义符号的错误地址为0 */
#define DMESG_MAX_LENGTH (0x20000) /*(128 * 1024)*/ /*128KB*/
/*==================================================================*/
/*                         模块全局常量定义 end                     */
/*==================================================================*/


/*==================================================================*/
/*                          调试开关定义 begin                      */
/*==================================================================*/
#ifdef CONFIG_DEBUG_SRECORDER
#define DEBUG_SRECORDER (CONFIG_DEBUG_SRECORDER) /* 总调试开关 */
#else
#define DEBUG_SRECORDER 1 /* 总调试开关 */
#endif

#define DEBUG_KERNEL_SYMBOLS 1           /* 调试内核符号读取模块 */
#define DEBUG_CRASH_TIME 1                   /* 调试死机的时间获取模块 */
#define DEBUG_SYS_INFO 1                       /* 调试系统信息 */
#define DEBUG_DMESG 1                            /* 调试dmesg信息获取 */
#define DEBUG_ALLCPU_STACK 1                /* 调试所有CPU调用栈 */
#define DEBUG_ALLPS_INFO 1                    /* 调试所有进程信息 */
#define DEBUG_CURRENT_PS_BACKTRACE 1 /* 调试当前正在运行进程调用栈 */
#define DEBUG_SLAB_INFO 1                      /* 调试slab 信息 */
/*==================================================================*/
/*                          调试开关定义 end                        */
/*==================================================================*/


/*==================================================================*/
/*                          打印函数定义 begin                      */
/*==================================================================*/
#define SRECORDER_PRINTK printk

#if DEBUG_SRECORDER
#define PRINTLINE printk("%s -%d - [%s]\n", __FILE__, __LINE__, __FUNCTION__)
#define PRINT_INFO(info, condition)\
do\
{\
    if (0 != condition)\
    {\
        printk info;\
    }\
} while (0)
#else
#define PRINTLINE
#define PRINT_INFO(info, condition)
#endif
/*==================================================================*/
/*                          打印函数定义 end                        */
/*==================================================================*/


/*==================================================================*/
/*                         全局宏函数定义 begin                     */
/*==================================================================*/
#define K(x) ((x) << (PAGE_SHIFT - 10)) /* 字节B到KB的转换，在sys info和all ps info中有用到 */
#define MAX(a, b) ((a) > (b)) ? (a) : (b)
#define MIN(a, b) ((a) > (b)) ? (b) : (a)
#define LOG_BUF_MASK(log_buf_len) ((log_buf_len) - 1)

/* log_buf_len must equal 2 ^ n ((n >= 0) && (n <= 32)) or the result may be wrong*/
#define LOG_OFFSET(len, log_buf_len) ((len) & LOG_BUF_MASK(log_buf_len))
/*==================================================================*/
/*                         全局宏函数定义 end                       */
/*==================================================================*/


/*==================================================================*/
/*                   进程堆栈dump类型掩码定义 begin                 */
/*==================================================================*/
#define SRECORDER_SHOW_VMA (1 << 0)
#define SRECORDER_SHOW_CMD (1 << 1)
#define SRECORDER_SHOW_ENV (1 << 2)
#define SRECORDER_SHOW_KSTK (1 << 3)
#define SRECORDER_SHOW_USTK (1 << 4)
#define SRECORDER_SHOW_KTRACE (1 << 5)
#define SRECORDER_SHOW_UTRACE (1 << 6)
#define SRECORDER_SHOW_ALL (SRECORDER_SHOW_VMA | SRECORDER_SHOW_CMD| SRECORDER_SHOW_ENV \
    | SRECORDER_SHOW_KSTK | SRECORDER_SHOW_USTK | SRECORDER_SHOW_KTRACE \
    | SRECORDER_SHOW_UTRACE)

#define SRECORDER_SHOW_COMMON (SRECORDER_SHOW_CMD | SRECORDER_SHOW_KSTK | SRECORDER_SHOW_USTK \
    | SRECORDER_SHOW_KTRACE | SRECORDER_SHOW_UTRACE)

#define SRECORDER_NOT_SHOW_VMA (SRECORDER_SHOW_ALL & (~SRECORDER_SHOW_VMA))
#define SRECORDER_NOT_SHOW_KSTK (SRECORDER_SHOW_ALL & (~SRECORDER_SHOW_KSTK))
#define SRECORDER_NOT_SHOW_USTK (SRECORDER_SHOW_ALL & (~SRECORDER_SHOW_USTK))
/*==================================================================*/
/*                   进程堆栈dump类型掩码定义 end                   */
/*==================================================================*/


/*----export prototypes---------------------------------------------------------------*/

typedef struct __srecorder_module_init_params_t
{
    char *srecorder_reserved_mem_start_addr; /* SRecorder保留内存区的起始地址 */
    char *srecorder_log_temp_buf; /* It is allocted by vmalloc */
    int srecorder_reserved_mem_size; /* SRecorder保留内存区的长度 */
    int srecorder_log_len;
} srecorder_module_init_params_t, *psrecorder_module_init_params_t;

typedef struct __srecorder_reserved_mem_info_for_log
{
    spinlock_t lock; /* 同步对以下变量的操作 */
    char *start_addr; /* SRecorder's temp buffer to save log, allocated by vmalloc */
#ifdef CONFIG_SRECORDER_RESERVED_MEM_PHYS_ADDR
    char *start_addr_mapped_by_ioremap; /* SRecorder's reserved buffer */
#endif
    int bytes_read; /* 已往SRecorder保留内存dump的字节数 */
    int bytes_left; /* SRecorder保留内存区剩余空间大小 */
    int bytes_per_type; /* 每类信息的字节数，不包括信息头部的校验数据 */
    int mem_size; /* SRecorder保留内存区存储有效信息的大小, 不包括该头部信息 */
    char *crash_reason1; /* 系统发生panic的第一个原因 */
    char *crash_reason2; /* 系统发生panic的第二个原因，比如第一个原因是oops，紧跟着就发生panic，panic可以看做第二原因 */
    bool dump_modem_crash_log_only; /* 判断是否是dump modem日志 */
    bool do_delay_when_dump_modem_log; /* 判断在dump modem日志时是否需要延时 */ 
    bool log_has_been_dumped_previously; /* 日志已经被dump */
} srecorder_reserved_mem_info_t, *psrecorder_reserved_mem_info_t;

/*srec means SRecorder*/
typedef unsigned long srec_ul32;
typedef unsigned long long srec_ul64;
typedef srec_ul32 srec_ksym_addr_t; /*内核符号地址的类型，目前设为32位，根据具体平台改变*/
typedef srec_ul32 srec_reserved_mem_t; /*目前假设是32位系统，在其他位数的系统上根据实际需求更改*/

typedef struct __srecorder_virt_zone_info_t
{
    struct page *start_page; /* 第一个起始页面 */
    char *virt_start; /* 虚拟起始地址 */
    char *ptr; /* 映射后的实际读写位置 */
    unsigned long phys_addr; /* 物理起始地址 */
    unsigned long size; /* 要映射的内存长度 */
    unsigned long page_delta; /* 相邻两个物理页面对应的page差值 */
    unsigned long virt_page_count; /* 虚拟页面的数量 */
    int mapped_size; /* 已经映射的物理空间长度 */
} srecorder_virt_zone_info_t, *psrecorder_virt_zone_info_t;


/*----global variables-----------------------------------------------------------------*/


/*----export function prototypes--------------------------------------------------------*/

/**
    @function: void srecorder_enable(unsigned long bit)
    @brief: enable SRecorder

    @param: none 
    
    @return: none

    @note: 
*/
void srecorder_enable(void);


/**
    @function: void srecorder_disable(unsigned long bit)
    @brief: disable SRecorder

    @param: bit 
    
    @return: none

    @note: 
*/
void srecorder_disable(void);


/**
    @function: bool srecorder_has_been_enabled(unsigned long bit)
    @brief: check if SRecorder has been enabled

    @param: bit 
    
    @return: none

    @note: 
*/
bool srecorder_has_been_enabled(void);


/**
    @function: void srecorder_set_log_dumped_bit(unsigned long bit)
    @brief: set bit to indicate that log with some type has been dumped completely

    @param: bit 
    
    @return: none

    @note: 
*/
void srecorder_set_log_dumped_bit(unsigned long bit);


/**
    @function: void srecorder_clear_log_dumped_bit(unsigned long bit)
    @brief: clear some bit to indicate that log with some type has not been dumped

    @param: bit 
    
    @return: none

    @note: 
*/
void srecorder_clear_log_dumped_bit(unsigned long bit);


/**
    @function: bool srecorder_log_has_been_dumped(unsigned long bit)
    @brief: check if log with some type has been dumped or not

    @param: bit 
    
    @return: a unsigned long long num

    @note: 
*/
bool srecorder_log_has_been_dumped(unsigned long bit);


/**
    @function: void srecorder_set_dump_enable_bit(unsigned long bit)
    @brief: 设置位

    @param: bit 
    
    @return: none

    @note: 
*/
void srecorder_set_dump_enable_bit(unsigned long bit);


/**
    @function: void srecorder_clear_dump_enable_bit(unsigned long bit)
    @brief: 清除位

    @param: bit 
    
    @return: none

    @note: 
*/
void srecorder_clear_dump_enable_bit(unsigned long bit);


/**
    @function: bool srecorder_dump_enable_bit_has_been_set(unsigned long bit)
    @brief: 获取某一位的值

    @param: bit 
    
    @return: none

    @note: 
*/
bool srecorder_dump_enable_bit_has_been_set(unsigned long bit);


/**
    @function: srecorder_reserved_mem_info_t* srecorder_get_reserved_mem_info(void)
    @brief: 获取SRecorder保留内存信息

    @param: none
    
    @return: SRecorder保留内存信息

    @note: 
*/
srecorder_reserved_mem_info_t* srecorder_get_reserved_mem_info(void);


/**
    @function: unsigned long srecorder_get_reserved_mem_addr(void)
    @brief: 获取SRecorder保留内存起始地址

    @param: none
    
    @return: SRecorder保留内存起始地址

    @note: 
*/
unsigned long srecorder_get_reserved_mem_addr(void);

/**
    @function: int srecorder_init_common(srecorder_module_init_params_t *pinit_params)
    @brief: 初始化common模块

    @param: pinit_params 模块初始化数据
        
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_init_common(srecorder_module_init_params_t *pinit_params);


/**
    @function: void srecorder_exit_common(void)
    @brief: 退出common模块

    @param: none
    
    @return: none

    @note: 
*/
void srecorder_exit_common(void);


#ifdef __cplusplus
}
#endif
#endif /* SRECORDER_COMMON_H */

