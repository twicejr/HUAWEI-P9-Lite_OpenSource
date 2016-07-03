

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include <linux/io.h>
#include "util.h"
#include <linux/proc_fs.h>
#include <linux/rtc.h>

/*****************************************************************************
    可维可测信息中包含的C文件编号宏定义
*****************************************************************************/
/*lint -e(767)*/
#define THIS_FILE_NAME                    "AT_UTIL"

/*****************************************************************************
  2 全局变量与宏定义定义
*****************************************************************************/

#define REG_VIR_ADDR_MAP(phyAddr)       ioremap(phyAddr,sizeof(unsigned long))
#define REG_VIR_ADDR_UNMAP(virAddr)     iounmap(virAddr)


struct  file    *at_log_fp    = NULL;
/*****************************************************************************
  3 函数实现
*****************************************************************************/


unsigned int at_util_reg_read_u32(unsigned int pAddr)
{
    unsigned int  value     = 0;
    void __iomem *virAddr   = NULL;

    virAddr = REG_VIR_ADDR_MAP(pAddr);
    value = *(volatile unsigned int *)(virAddr);
    REG_VIR_ADDR_UNMAP(virAddr);

    return value;
}


void at_util_reg_write_u32(unsigned int pAddr, unsigned int value)
{
    void __iomem *virAddr = NULL;

    virAddr = REG_VIR_ADDR_MAP(pAddr);
    *(volatile unsigned int *)(virAddr)=value;
    REG_VIR_ADDR_UNMAP(virAddr);
}


int at_util_reg_test (struct at_util_reg_test_type regs[],
                        int size,
                        int (*reg_read)     (unsigned int reg),
                        void(*reg_write)    (unsigned int reg, unsigned int value))
{
    int i;
    int read_v = 0;

    if((NULL==reg_read) || (NULL==reg_write)){
        return AT_FAILED;
    }

    pr_info("Audio: test Read only reg\n");
    for (i = 0; i < size; i++) {
      if (RO == regs[i].rt) {
        pr_info("Audio: test Read reg offset = %d\n",regs[i].offset);
        read_v = reg_read(regs[i].offset);
        if ((regs[i].default_value & read_v) == regs[i].default_value){
            pr_info("Audio: offset %#8x reg read right\n", regs[i].offset);
        } else {
            pr_info("Audio: offset %#8x reg read error.expect v:%#8x;\t read v:%#8x\n",
                regs[i].offset, regs[i].default_value,read_v);
            return AT_FAILED;
        }
      }
    }


    pr_info("Audio: test Read write reg\n");
    for (i = 0; i < size; i++) {
        if (RW == regs[i].rt) {
            read_v = reg_read(regs[i].offset);
            reg_write(regs[i].offset, regs[i].value | read_v);
            read_v = reg_read(regs[i].offset);
            if ((regs[i].expect_value & read_v) == regs[i].expect_value){
                pr_info("Audio: offset %#8x reg read write right.\n", regs[i].offset);
            } else {
                pr_info("Audio: offset %#8x reg read write error.write v:%#8x;\t expect v:%#8x;\t read v:%#8x\n",
                    regs[i].offset, regs[i].value,regs[i].expect_value,read_v);
                return AT_FAILED;
            }
        }
    }
    pr_info("Audio: test Read write reg end\n");

    pr_info("Audio: test write only reg\n");
    for (i = 0; i < size; i++) {
        if (WO == regs[i].rt ) {
           reg_write(regs[i].offset, regs[i].value);
           pr_info("Audio: offset %#8x reg write, write v:%#8x.\n",
                regs[i].offset,regs[i].value);
        }
    }
    pr_info("Audio: test write only reg end\n");
    return AT_SUCCESS;
}




void *at_util_mem_remap_type(unsigned long phys_addr, size_t size, pgprot_t pgprot)
{
    int i;
    u8* vaddr;
    int npages;
    unsigned long offset;
    struct page **pages;

    /* 获取映射物理页数 */
    npages = PAGE_ALIGN((phys_addr & (PAGE_SIZE - 1)) + size) >> PAGE_SHIFT;

    /* 获取物理地址页内偏移 */
    offset = phys_addr & (PAGE_SIZE - 1);

    /* 获取物理地址页描述数组 */
    pages = vmalloc(sizeof(struct page *) * npages);
    if (!pages)
    {
        printk(KERN_ERR "%s: vmalloc return NULL!\n", __FUNCTION__);
        return NULL;
    }
    pages[0] = phys_to_page(phys_addr);
    for (i = 0; i < npages - 1 ; i++) {
        pages[i + 1] = pages[i] + 1;
    }

    /* 将物理页映射入内核虚拟空间中  */
    vaddr = (u8*)vmap(pages, npages, VM_MAP, pgprot);
    if(vaddr == 0)
    {
        printk(KERN_ERR "%s: vmap return NULL!\n", __FUNCTION__);
    }
    else
    {
        vaddr += offset;
    }

    /* 释放物理地址页描述数组*/
    vfree(pages);
    printk(KERN_DEBUG "%s: phys_addr:0x%08lx size:0x%08lx npages:%d vaddr:%p, offset:0x%08lx\n",\
            __FUNCTION__, phys_addr, (unsigned long)size, npages, vaddr, offset);
    return (void *)vaddr;
}


void *at_util_mem_remap_and_init (unsigned int phys_addr, size_t size,
            unsigned int init_value)
{
    void *virt_addr = NULL;
    unsigned int i;

    /* 如果物理地址位于低3G空间，则认为是ddr空间，否则认为是IO空间  */
    if(phys_addr < 0xc0000000){
        pr_info("audio: mmap ddr address \n");
        virt_addr = at_util_mem_remap_writecombine (phys_addr, size);
    }
    else {
       pr_info("audio: mmap IO address \n");
       virt_addr = ioremap(phys_addr, size);
    }
    /* 将空间初始化为用户指定值，使用32bit写  */
    pr_info("audio:init src memery to init_value \n");
    for (i = 0; i < size;i=i+4) {
        *((unsigned int *)(virt_addr+i)) = init_value;
        pr_info("addr = 0x%p, value = 0x%x \n",virt_addr+i,\
                    *((unsigned int *)(virt_addr+i)));
    }


    return virt_addr;
}


struct  file* at_util_log_file_open(char *path, char *file_name)
{
    int     ret         = 0;
    int     file_flag   = O_RDWR | O_APPEND;

    char    file_name_full[128];
    int     file_name_len;

    char    tmp_buf[64];
    int     tmp_len;
    ssize_t size ;

    struct  kstat   file_stat;
    mm_segment_t fs;

    file_name_len = sprintf(file_name_full,"%s%s",path,file_name);
    pr_info("file_name_full = %s.\n", file_name_full);

    /* 如果文件未创建，创建log文件  */
    ret = vfs_stat(file_name_full, &file_stat);
    if (ret < 0) {
        pr_info("there isn't a log file, and need to create.\n");
        file_flag |= O_CREAT;
    }


    /* 打开log文件 */
   at_log_fp = filp_open(file_name_full, file_flag, 0755);
   // fp = filp_open("/data/at_log", O_RDWR|O_CREAT, 0755);
    if (IS_ERR(at_log_fp)) {
        pr_info("open file fail: %s.\n", file_name_full);
        goto END;
    }

    fs = get_fs();
    set_fs(KERNEL_DS);
    memset(tmp_buf, 0, 64);
    tmp_len = sprintf(tmp_buf, "%s", "Open at_log_fs.\n");
    size = vfs_write(at_log_fp, tmp_buf, tmp_len, &at_log_fp->f_pos);
    //vfs_write(fp, is_log, strlen(is_log), &fp->f_pos);
    set_fs(fs);
    pr_info("size = %ld\n",size);
    //filp_close(fp, 0);

END:
    return at_log_fp;
}




int at_util_log_file_close(void)
{
    if(NULL == at_log_fp){
        return AT_FAILED;
    }
    filp_close(at_log_fp, 0);
    return AT_SUCCESS;
}

extern int at_util_log(void *data_addr,unsigned int data_len)
{
    char tmp_buf[64];
    int  tmp_len;
    struct rtc_time cur_tm;
    struct timespec now;
    mm_segment_t fs;


    if(NULL==data_addr){
        return AT_FAILED;
    }

    pr_info("at_util_log\n");


    fs = get_fs();
    set_fs(KERNEL_DS);


    now = current_kernel_time();
    rtc_time_to_tm(now.tv_sec, &cur_tm);

    memset(tmp_buf,0,64);
    tmp_len = sprintf(tmp_buf, "%04d-%02d-%02d %02d:%02d:%02d.\n",
                                cur_tm.tm_year+1900, cur_tm.tm_mon+1,
                                cur_tm.tm_mday, cur_tm.tm_hour,
                                cur_tm.tm_min, cur_tm.tm_sec);

    pr_info("%s\n",tmp_buf);

    vfs_write(at_log_fp, tmp_buf, tmp_len, &at_log_fp->f_pos);
    vfs_write(at_log_fp, data_addr, data_len, &at_log_fp->f_pos);

    set_fs(fs);
    return AT_SUCCESS;
}

EXPORT_SYMBOL(at_util_log_file_open);
EXPORT_SYMBOL(at_util_log_file_close);
EXPORT_SYMBOL(at_util_log);
EXPORT_SYMBOL(at_util_reg_read_u32);
EXPORT_SYMBOL(at_util_reg_write_u32);
EXPORT_SYMBOL(at_util_reg_test);
EXPORT_SYMBOL(at_util_mem_remap_and_init);


