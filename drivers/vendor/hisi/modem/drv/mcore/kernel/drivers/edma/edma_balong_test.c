

#include "edma_balong.h"
#include "bsp_sram.h"
#include <printk.h>

/* 测试使用较大的memory 在p531上验证 使用
sram128k 以后 从 SRAM_MEM_TOP_ADDR 开始*/
#define M3_EDMA_TEST_BASE_ADDR SRAM_MEM_TOP_ADDR

/****arm与ldsp复用****低功耗备份恢复  m2m */
/* 定义在 drv_edma_enum.h中
#define	EDMA_CH_LOAD_LDSP_TCM  EDMA_CH_LDSP_API_USED_0
#define	EDMA_CH_LOAD_TDSP_TCM  EDMA_CH_LDSP_API_USED_1
*/
#define M3_EDMA_TEST_CHAN1   (EDMA_CH_LOAD_LDSP_TCM)
#define M3_EDMA_TEST_CHAN2   (EDMA_CH_LOAD_TDSP_TCM)

void * edma_test_data_build(void * m, char c, u32 size)
{
    u32 index ;
    char *p = m;
    for( index=0;index<size; index++ )
    {
        *p++ = c++;
    }
    return m;
}
void * edma_test_data_show(void * m, u32 size)
{
    u32 index ;
    char *p = m;
    for( index=0;index<size; index++ )
    {
        printk(" %c", *(p++));
    }
    printk(" \n");
    return m;
}

u32 edma_test_verify(void * src, void *dest, u32 size)
{
    u32 index ;
    char * src_char;
    char * dest_char;
    src_char = (char*) src;
    dest_char = (char*) dest;
    for( index=1;index<=size; index++ ) /*index!=0 start from 1*/
    {
        if(*(src_char++) != *(dest_char++))
            return index;
    }
    return 0;
}

s32 edma_test_m2m(u32 src, u32 dest, u32 len)
{
    u32 edma_stat;
    u32 error;
    u32 src_use;
    u32 dest_use;

    src = SRAM_MEM_TOP_ADDR;
    src_use = src+4;
    dest = SRAM_MEM_TOP_ADDR+len+8;
    dest_use = dest +4;
    printk("NEW src_use=0x%x, dest_use=0x%x  on SRAM\n", src_use, dest_use);

    edma_test_data_build((void *)src, 'a', len+8);
    edma_test_data_show((void *)src, 20);
    edma_test_data_build((void *)dest, 'b', len+8);
    edma_test_data_show((void *)dest, 20);
    bsp_edma_m2m_channel( 0, src_use, dest_use, len);
    edma_stat = bsp_edma_state();
    while(edma_stat)
    {
        printk( "edma_stat = %d \n",edma_stat);
        edma_stat = bsp_edma_state();
    }
    /* 验证 源-目的 区域内全相同 */
    error = edma_test_verify((void*) src_use,(void*) dest_use, len);
    edma_test_data_show((void *) (src_use+error-4), 20);
    edma_test_data_show((void *) (dest_use+error-4), 20);

    if(0!=error)
    {
        printk( "verif return %d \n", error);
        return error;
    }
    /* 验证 区域前后 都不相同 */
    error = edma_test_verify((void*) src,(void*) dest, len);
    if(0==error)
    {
        printk( " data from src - dest \n");
        edma_test_data_show((void *) (src), 20);
        edma_test_data_show((void *) (dest), 20);
        return -1;
    }
    error = edma_test_verify((void*) src_use,(void*) dest_use, len+4);
    if(0==error)
    {
        printk( " data from src_use+len - dest_use+len \n");
        edma_test_data_show((void *) (src_use+len), 20);
        edma_test_data_show((void *) (dest_use+len), 20);
        return -1;
    }
    return 0;
}

/*
传参 0x2000 可更直观看出各个通道一个一个的完成传输。
打印 通道 0 - n 逐一完成
*/
u32 edma_test_state(u32 chans ,u32 len)
{
    u32 edma_stat;
    u32 error;
    u32 src = 0;
    u32 dest = 0;
    u32 index = 0;

    src = SRAM_MEM_TOP_ADDR;
    dest = SRAM_MEM_TOP_ADDR+len;
    printk( "NEW src=0x%x, dest=0x%x  on SRAM\n", src, dest);

    edma_test_data_build((void *)src, 'a', len);
    edma_test_data_show((void *)src, 20);
    edma_test_data_build((void *)dest, 'b', len);
    edma_test_data_show((void *)dest, 20);
    for(index=0;index<16;index++)
    {
        if(chans&(0x1<<index))
            bsp_edma_m2m_channel( index, src, dest, len);
    }
    edma_stat = bsp_edma_state();
    while(edma_stat)
    {
        printk("edma_stat = %d \n",edma_stat);
        edma_stat = bsp_edma_state();
    }
    error = edma_test_verify((void *) src,(void *) dest, len);
    edma_test_data_show((void *) (src+error), 10);
    edma_test_data_show((void *) (dest+error), 10);

    return error;
}



