/**
    @copyright: Huawei Technologies Co., Ltd. 2012-2012. All rights reserved.
    
    @file: srecorder_dmesg.c
    
    @brief: 读取内核循环缓冲中的内容，即内核中用printk打印的信息。
    
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
#include <linux/ctype.h>
#include <linux/highmem.h>

#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/version.h>
#include <linux/time.h>

#include "../include/srecorder_dmesg.h"
#include "../include/srecorder_kernel_symbols.h"
#include "../include/srecorder_save_log.h"
#include "../include/srecorder_snprintf.h"
#include "../include/srecorder_memory.h"


#if defined(CONFIG_DUMP_DMESG)

/*----local macroes------------------------------------------------------------------*/

#define NEW_LINE_SYMBOL_LEN (1)


/*----local prototypes----------------------------------------------------------------*/


/*----local variables------------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----local function prototypes---------------------------------------------------------*/

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 5, 0))
#if 0
static unsigned long srecorder_write_data(srecorder_write_kernel_log_param_t *psrecorder_write_kernel_log_param);
#endif
#else
static int srecorder_write_data(char *pdst, const char *psrc, int bytes_to_write);
#endif


/*----function definitions--------------------------------------------------------------*/

/**
    @function: static int srecorder_write_data(char *pdst, const char *psrc, int bytes_to_write)
    @brief: 向IO内存写数据

    @param: pdst - IO地址
    @param: psrc - 原始数据地址
    @param: bytes_to_write - 需要写入的字节数
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 5, 0))
#if 0
static unsigned long srecorder_write_data(srecorder_write_kernel_log_param_t *psrecorder_write_kernel_log_param)
{
    kernel_log_t *plog = NULL;
    char *pdst = NULL;
    unsigned long bytes_saved_total = 0;
    unsigned long bytes_can_be_saved_this_time = 0;
    unsigned long bytes_left_in_srecorder = 0;
    char print_time[32] = {0};
    unsigned long time_info_len = 0;
    
    if (NULL == psrecorder_write_kernel_log_param
        || NULL == psrecorder_write_kernel_log_param->psrecorder_buf
        || NULL == psrecorder_write_kernel_log_param->kernel_log_buf)
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return 0;
    }

    bytes_left_in_srecorder = psrecorder_write_kernel_log_param->bytes_left_in_srecorder;
    pdst = psrecorder_write_kernel_log_param->psrecorder_buf;
    while ((psrecorder_write_kernel_log_param->kernel_log_idx 
        < psrecorder_write_kernel_log_param->kernel_log_buf_len)
        && (bytes_left_in_srecorder > 0))
    {
        bool newline = true;
        plog = (kernel_log_t *)(psrecorder_write_kernel_log_param->kernel_log_buf 
            + psrecorder_write_kernel_log_param->kernel_log_idx);
        if (0 == plog->len) /* this is the end */
        {
            break;
        }
        
        if (plog->flags & SRECORDER_LOG_CONT)
        {
            if (!(plog->flags & SRECORDER_LOG_NEWLINE))
            {
                newline = false;
            }
        }

        {
            struct timeval tv = ns_to_timeval(plog->ts_nsec);
            memset(print_time, 0, sizeof(print_time));
            snprintf(print_time, sizeof(print_time), "[%5lu.%06u] ", (unsigned long)tv.tv_sec, (unsigned)tv.tv_usec);
            time_info_len = strlen(print_time);
            bytes_can_be_saved_this_time = time_info_len;
        }
        
        bytes_can_be_saved_this_time += ((newline) ? (plog->text_len + NEW_LINE_SYMBOL_LEN) : (plog->text_len));
        bytes_can_be_saved_this_time = (bytes_can_be_saved_this_time < bytes_left_in_srecorder) 
            ? (bytes_can_be_saved_this_time) : (bytes_left_in_srecorder);
        
        /* copy time info */
        if (time_info_len >= bytes_can_be_saved_this_time)
        {
            memcpy(pdst, print_time, bytes_can_be_saved_this_time);
            bytes_saved_total += bytes_can_be_saved_this_time;
            break;
        }
        else
        {
            memcpy(pdst, print_time, (time_info_len));
        }
        
        /* copy kernel message */
        if (newline)
        {
            memcpy(pdst + time_info_len, ((char *)plog + psrecorder_write_kernel_log_param->header_len), 
                bytes_can_be_saved_this_time - time_info_len - NEW_LINE_SYMBOL_LEN);
            *(pdst + bytes_can_be_saved_this_time - 1) = '\n';
        }
        else
        {
            memcpy(pdst + time_info_len, ((char *)plog + psrecorder_write_kernel_log_param->header_len), 
                bytes_can_be_saved_this_time - time_info_len);
        }
        
        pdst += bytes_can_be_saved_this_time;
        bytes_saved_total += bytes_can_be_saved_this_time;
        bytes_left_in_srecorder -= bytes_can_be_saved_this_time;
        psrecorder_write_kernel_log_param->kernel_log_idx += plog->len;
    }

    return bytes_saved_total;
}
#endif
#else
static int srecorder_write_data(char *pdst, const char *psrc, int bytes_to_write)
{
    int i = 0;
    int j = 0;
    
    if (NULL == pdst || NULL == psrc)
    {
        return 0; 
    }

    
    for (i = 0; i < bytes_to_write; i++)
    {     
        if (!isascii(psrc[i]) || psrc[i] == '\0')
        {
            continue;
        }
        
        *(pdst + j) = *(psrc + i);
        j++;
    }

    return j;
}
#endif


/**
    @function: int srecorder_get_dmesg(srecorder_reserved_mem_info_for_log_t *pmem_info)
    @brief: 读取内核循环缓冲区内容

    @param: pmem_info SRecorder的保留内存信息
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_get_dmesg(srecorder_reserved_mem_info_t *pmem_info)
{
    int bytes_read1 = 0; /**/
    int bytes_read2 = 0; /**/
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 5, 0))
    int bytes_to_read = 0;
    int log_buf_len = 0;
    char *log_buf = NULL;  
    const char *start1 = NULL;
    const char *start2 = NULL;
    unsigned log_end = 0; /* Index into log_buf: most-recently-written-char + 1 */
#endif
    psrecorder_info_header_t pinfo_header = NULL;
    
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 5, 0))
    unsigned long record_seq = 0;
    unsigned long bytes_traversed = 0;
    kernel_log_t *plog = NULL;
    bool kernel_log_buf_overflowed = false;
    kernel_log_buf_content_header_info_t kernel_log_buf_content_header_info = {0};
    kernel_log_buf_info_t kernel_log_buf_info = {0};
    srecorder_write_kernel_log_param_t srecorder_write_kernel_log_param = {0};
#endif

    if (NULL == pmem_info 
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 5, 0))
        || INVALID_KSYM_ADDR == srecorder_get_log_buf()
        || INVALID_KSYM_ADDR == srecorder_get_log_buf_len()
        || INVALID_KSYM_ADDR == srecorder_get_log_end()
#endif
        )
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param or kernel symbol addr!\n", __FILE__, __LINE__);
        return -1;
    }

    if (srecorder_log_has_been_dumped(DMESG_BIT2))
    {
        SRECORDER_PRINTK("dmesg has been dumped successfully!\n");
        return 0;
    }
    
    if (0 != srecorder_write_info_header(pmem_info, DMESG_BIT2, &pinfo_header))
    {
        return -1;
    }
    
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 5, 0))
#if 1
    bytes_read1 = srecorder_get_all_syslog(pmem_info->start_addr + pmem_info->bytes_read,
        pmem_info->bytes_left - 1);
    srecorder_renew_meminfo(pmem_info, bytes_read1);
#else
    memset((void *)&kernel_log_buf_content_header_info, 0, sizeof(kernel_log_buf_content_header_info_t));
    memset((void *)&kernel_log_buf_info, 0, sizeof(kernel_log_buf_info_t));
    memset((void *)&srecorder_write_kernel_log_param, 0, sizeof(srecorder_write_kernel_log_param_t));

    /* get log_buf information  */
    get_log_buf_header_info(&kernel_log_buf_content_header_info);
    get_log_buf_info(&kernel_log_buf_info);
    srecorder_write_kernel_log_param.psrecorder_buf = pmem_info->start_addr + pmem_info->bytes_read;
    srecorder_write_kernel_log_param.kernel_log_buf = (char *)(*(unsigned long *)kernel_log_buf_info.log_buf);
    srecorder_write_kernel_log_param.header_len = kernel_log_buf_content_header_info.header_len;
    srecorder_write_kernel_log_param.align_base = kernel_log_buf_content_header_info.align_base;
    
    /* calculate record count */
    plog = (kernel_log_t *)srecorder_write_kernel_log_param.kernel_log_buf;
    while (bytes_traversed < *(unsigned long *)kernel_log_buf_info.log_next_idx)
    {
        if (0 == plog->len)
        {
            break;
        }
        bytes_traversed += plog->len;
        plog = (kernel_log_t *)((char *)plog + plog->len);
        record_seq++;
    }
    
    kernel_log_buf_overflowed = (record_seq < *(unsigned long long*)kernel_log_buf_info.log_next_seq) ? (true) : (false);
    if (kernel_log_buf_overflowed)
    {
        srecorder_write_kernel_log_param.bytes_left_in_srecorder = pmem_info->bytes_left;
        srecorder_write_kernel_log_param.kernel_log_idx = *(unsigned long *)kernel_log_buf_info.log_first_idx;
        srecorder_write_kernel_log_param.kernel_log_buf_len = kernel_log_buf_info.log_buf_len;
        bytes_read1 = (int)srecorder_write_data(&srecorder_write_kernel_log_param);
        srecorder_renew_meminfo(pmem_info, bytes_read1);
    }
    
    srecorder_write_kernel_log_param.psrecorder_buf = pmem_info->start_addr + pmem_info->bytes_read;
    srecorder_write_kernel_log_param.bytes_left_in_srecorder = pmem_info->bytes_left;
    srecorder_write_kernel_log_param.kernel_log_idx = 0x0;
    srecorder_write_kernel_log_param.kernel_log_buf_len = *(unsigned long *)kernel_log_buf_info.log_next_idx;
    bytes_read2 = (int)srecorder_write_data(&srecorder_write_kernel_log_param);
    srecorder_renew_meminfo(pmem_info, bytes_read2);
#endif
#else
    log_buf = (char *)(*(srec_ksym_addr_t*)srecorder_get_log_buf());
    if (NULL == log_buf)
    {
        return -1;
    }

    /* 下面的判断不可少，否则有造成内存越界的潜在风险，进而异常嵌套，系统不能正常复位，只能依赖于带外复位 */
    log_buf_len = (int)srecorder_get_log_buf_len();

    /* 
    * Theoretically, the log could move on after we do this, but
    * there's not a lot we can do about that. The new messages
    * will overwrite the start of what we dump. 
    */
    log_end = (*(srec_ksym_addr_t *)srecorder_get_log_end()) & LOG_BUF_MASK(log_buf_len);
    bytes_to_read = MIN((pmem_info->bytes_left - 1), MIN(log_buf_len, log_buf_len));

    if (log_end >= bytes_to_read)
    {
        start1 = log_buf + log_end - bytes_to_read;
        bytes_read1 = srecorder_write_data(pmem_info->start_addr + pmem_info->bytes_read, start1, bytes_to_read);
        srecorder_renew_meminfo(pmem_info, bytes_read1);
    }
    else
    {
        start1 = log_buf + log_buf_len - (bytes_to_read - log_end);
        bytes_read1 = srecorder_write_data(pmem_info->start_addr + pmem_info->bytes_read, start1, (bytes_to_read - log_end));
        srecorder_renew_meminfo(pmem_info, bytes_read1);
        start2 = log_buf;
        bytes_read2 = srecorder_write_data(pmem_info->start_addr + pmem_info->bytes_read, start2, log_end);
        srecorder_renew_meminfo(pmem_info, bytes_read2);
    } 
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 5, 0))
    bytes_read1 = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, 
        pmem_info->bytes_left, "\n", 1);
#else
    /* 写入"\n" */
    bytes_read1 = srecorder_write_data(pmem_info->start_addr + pmem_info->bytes_read, "\n", 1);
#endif
    srecorder_renew_meminfo(pmem_info, bytes_read1);

    /* 填写信息头部验证信息 */
    srecorder_validate_info_header(pinfo_header, pmem_info->bytes_per_type);
    
    return 0;
}


/**
    @function: int srecorder_init_dmesg(srecorder_module_init_params_t *pinit_params)
    @brief: 初始化dmesg模块

    @param: pinit_params 模块初始化数据
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_init_dmesg(srecorder_module_init_params_t *pinit_params)
{
    srecorder_clear_log_dumped_bit(DMESG_BIT2);
    
    return 0;
}


/**
    @function: void srecorder_exit_dmesg(void)
    @brief: 退出dmesg模块

    @param: none
    
    @return: none

    @note: 
*/
void srecorder_exit_dmesg(void)
{
    srecorder_set_log_dumped_bit(DMESG_BIT2);
}
#else
int srecorder_get_dmesg(srecorder_reserved_mem_info_t *pmem_info)
{
    return 0;
}


int srecorder_init_dmesg(srecorder_module_init_params_t *pinit_params)
{
    return 0;
}


void srecorder_exit_dmesg(void)
{
    return;
}
#endif

