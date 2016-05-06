/**
    @copyright: Huawei Technologies Co., Ltd. 2012-2012. All rights reserved.
    
    @file: srecorder_save_log.c
    
    @brief: 定义保存定位信息的方式，保存成文件仅供测试用
    
    @version: 1.0 
    
    @author: QiDechun ID: 216641
    
    @date: 2012-06-22
    
    @history:
*/

/*----includes-----------------------------------------------------------------------*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <asm/uaccess.h>

#include "../include/srecorder_save_log.h"


/*----local macroes------------------------------------------------------------------*/


/*----local prototypes----------------------------------------------------------------*/

typedef struct
{
    srecorder_info_type_e type;
    char *desciprion;
} srecorder_header_info_type_description_t;


/*----local variables------------------------------------------------------------------*/

static srecorder_header_info_type_description_t s_srecorder_head_info[] = 
{
    {CRASH_REASON_TIME_BIT0, CRASH_REASON_KEYWORD},
    {SYS_INFO_BIT1, SYSINFO_KEYWORD}, 
    {DMESG_BIT2, DMESG_KEYWORD},
    {ALL_CPU_STACK_BIT3, ALL_CPU_CALL_STACK_KEYWORD},
    {ALL_PS_INFO_BIT4, ALL_PS_INFO_KEYWORD},
    {CURRENT_PS_BACKTRACE_BIT5, CURRENT_PS_BACKTRACE_KEYWORD},
    {SLABINFO_BIT6, SLABINFO_KEYWORD},
    {MODEM_ERR_BIT7, MODEM_ERR_KEYWORD},
    {MODEM_ERR_F3_BIT8, MODEM_ERR_F3_KEYWORD},
	{LOGCAT_BIT9, LOGCAT_KEYWORD},
};


/*----global variables-----------------------------------------------------------------*/


/*----local function prototypes---------------------------------------------------------*/


/*----function definitions--------------------------------------------------------------*/

/**
    @function: int srecorder_renew_meminfo(srecorder_reserved_mem_info_for_log_t *pmem_info, int bytes_read)
    @brief: 更改SRecorder保留内存区描述信息数据结构

    @param: pmem_info 
    @param: bytes_read 
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_renew_meminfo(srecorder_reserved_mem_info_t *pmem_info, int bytes_read)
{
    pmem_info->bytes_read += bytes_read;
    pmem_info->bytes_per_type += bytes_read;
    pmem_info->bytes_left = pmem_info->mem_size - pmem_info->bytes_read;

    return 0;
}


/**
    @function:int srecorder_write_info_header(srecorder_reserved_mem_info_for_log_t *pmem_info, 
        srecorder_info_type_e type, 
        psrecorder_info_header_t *pinfo_header)
    @brief: 初始化给类信息的头部数据结构

    @param: pmem_info SRecorder的保留内存信息
    @param: type 信息类型
    @param: pinfo_header 信息头部校验数据结构
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_write_info_header(srecorder_reserved_mem_info_t *pmem_info, 
    srecorder_info_type_e type, 
    psrecorder_info_header_t *pinfo_header)
{
    int bytes_read = 0;
/* 删除此处定义 */
#ifndef CONFIG_SRECORDER_DUMP_LOG_TO_STORAGECARD
    int info_header_size = sizeof(srecorder_info_header_t);
#endif

    if (unlikely(NULL == pmem_info || NULL == pmem_info->start_addr || NULL == pinfo_header 
        || (LOG_TYPE_COUNT <= (int)type || (int)type < 0)))
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return -1;
    }

#ifndef CONFIG_SRECORDER_DUMP_LOG_TO_STORAGECARD
    /*把校验信息的头部结构留出来*/
    /* 删除此处 */
    if ((pmem_info->bytes_read + info_header_size) > pmem_info->mem_size)
    {
        return -1;
    }

    *pinfo_header = (psrecorder_info_header_t)(pmem_info->start_addr + pmem_info->bytes_read);
    memset(*pinfo_header, 0, info_header_size);
    ((psrecorder_info_header_t)*pinfo_header)->type = type;
    
    pmem_info->bytes_read += (info_header_size);
#endif

    pmem_info->bytes_per_type = 0;

    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
        "%s\n", s_srecorder_head_info[type].desciprion);
    srecorder_renew_meminfo(pmem_info, bytes_read);
    
    return 0;
}


/**
    @function: int srecorder_validate_info_header(srecorder_info_header_t *pheader, unsigned long data_len)
    @brief: 对各种定位信息的头部并进行校验

    @param: pheader 各类信息的校验头
    @param: data_len 每类信息的数据长度，不包括校验头的数据
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_validate_info_header(srecorder_info_header_t *pheader, unsigned long data_len)
{
#ifndef CONFIG_SRECORDER_DUMP_LOG_TO_STORAGECARD
    unsigned long buf[2] = {0, 0};

    if (unlikely(NULL == pheader))
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return -1;
    }
       
    pheader->data_len = data_len;/* [false alarm]:pheader have protect  */
    buf[0] = (unsigned long)pheader->type;
    buf[1] = (unsigned long)pheader->data_len;
    pheader->crc32 = srecorder_get_crc32((unsigned char *)buf, sizeof(buf));
#endif

    return 0;
}


#if 0 /* 以下这段代码作为内核读写文件的参考即可 */
/**
    @function: int srecorder_save_log(char *file_path, char *pbuf, int data_len)
    @brief: 在内核中将信息保存到文件中

    @param: file_path 文件路径
    @param: pbuf 存放信息的内存起始地址
    @param: pbuf 要保存的数据长度
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_save_log(char *file_path, char *pbuf, int data_len)
{
    mm_segment_t old_fs;
    loff_t pos;
    struct file *fp;
    
    if (NULL == file_path || NULL == pbuf || data_len <= 0)
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return -1;
    }

    /*0644文件读写执行权限，所有者:读写、用户组:读、其他:读*/
    fp = filp_open(file_path, O_WRONLY | O_CREAT, 0644); 
    if (NULL != fp)
    {
        old_fs = get_fs();
        set_fs(KERNEL_DS);
        pos = 0;
        vfs_write(fp, pbuf, data_len, &pos);
        /*
        char buf[1024];        
        memset(buf, 0, sizeof(buf));
        pos = 0;
        vfs_read(fp, buf, sizeof(buf) - 1, &pos);*/
        filp_close(fp, NULL);
        set_fs(old_fs);        
    }

    return 0;
}
#endif

