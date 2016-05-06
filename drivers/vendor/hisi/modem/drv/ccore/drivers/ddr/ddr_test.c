#include <osl_bio.h>
#include <osl_malloc.h>
#include <bsp_hardtimer.h>
#include <bsp_edma.h>
#include <of.h>

#include "ddr_test.h"

static inline void _read_test( unsigned start_addr, unsigned int size, unsigned int cnt)
{
    unsigned int i,cur_addr,end_addr;
    end_addr = start_addr + size;
    for(i=0; i<cnt; i++){
        for(cur_addr = start_addr; cur_addr<end_addr; ){
            (void)readl_relaxed(cur_addr);
            cur_addr += 4;
        }
    }
}

static inline void _write_test( unsigned start_addr, unsigned int size, unsigned int cnt)
{
    unsigned int i,cur_addr,end_addr;
    end_addr = start_addr + size;
    for(i=0; i<cnt; i++){
        for(cur_addr = start_addr; cur_addr<end_addr; ){
            writel_relaxed(0, cur_addr);
            cur_addr += 4;
        }
    }
}

void ddr_test_cpu(enum ddr_access_type access_type, enum ddr_mmu_type mmu_type, unsigned size, unsigned cnt)
{
    unsigned start_addr = 0;
    u32 slice_value[2] = {0,0};
    u32 slice_delta;
    unsigned long flags;
    switch (mmu_type){
        case ddr_test_cacheable :
            start_addr = (unsigned)osl_malloc(size);
            break;
            
        case ddr_test_nocacheable:
            start_addr = (unsigned)osl_cachedma_malloc(size);
            break;
            
        default:
            ddr_test_print("mmu_type=%d error. cacheable = %d nocacheable = %d \n",mmu_type,ddr_test_cacheable, ddr_test_nocacheable);
            return;
    }

    if(!start_addr){
        ddr_test_print("alloc failed\n");
        return;
    }
    ddr_test_print("interrupt locked when test is running\n");

    local_irq_save(flags);

    slice_value[0] = bsp_get_slice_value();

    switch (access_type){
        case ddr_test_read :
            _read_test( start_addr, size, cnt);
            break;
            
        case ddr_test_write:
            _write_test( start_addr, size, cnt);
            break;
            
        default:
            ddr_test_print("access_type=%d error. read = %d write = %d \n",access_type,ddr_test_read, ddr_test_write);
            
            local_irq_restore(flags);
            return;
    }
    
    slice_value[1] = bsp_get_slice_value();

    local_irq_restore(flags);
    slice_delta = get_timer_slice_delta(slice_value[0], slice_value[1]);
    ddr_test_print("test size=%d Bytes for %d times\n", size, cnt );
    ddr_test_print("test begin:0x%x, end:0x%x, delta:0x%x = %dus\n", slice_value[0], slice_value[1]\
        , slice_delta, slice_delta*1000000/32768 );
    
    switch (mmu_type){
        case ddr_test_cacheable :
            osl_free( (void*)start_addr );
            break;
            
        case ddr_test_nocacheable:
            osl_cachedma_free( (void*)start_addr );
            break;
            
        default:
            /* unreachable */
            return;
    }
}

u32 ddr_test_cpu_args[][2]=
{
    {ddr_test_type_reserved},
    {ddr_test_read , ddr_test_cacheable   },
    {ddr_test_read , ddr_test_nocacheable },
    {ddr_test_write, ddr_test_cacheable   },
    {ddr_test_write, ddr_test_nocacheable },
};

unsigned ddr_test_size = DEFAULT_SIZE;

void ddr_test_set(unsigned size)
{
    ddr_test_size = size;
}

struct edma_cb ddr_test_edma_configs =
{
    .lli = 0,
    .bindx = 0,
    .cindx = 0,
    .cnt1 = 0,
    .cnt0 = 0x3fff4000,
    .src_addr = 0,
    .des_addr = 0,
    .config = 0x0FF22000,
};

int ddr_test_edma(void)
{
    unsigned start_addr = 0;
    u32 slice_value[2] = {0,0};
    u32 slice_delta;
    unsigned long flags;

    u32 edma_lli_addr,reg_val;

    u32 edma_base_addr;
    unsigned chan_id;


	struct device_node *np = NULL;
    struct device_node *child_node = NULL;

    np = of_find_compatible_node(NULL, NULL, "hisilicon,edma");
    if (!np){
        ddr_test_print("can not find edma dts \n");
        return ERROR;
    }
    child_node = of_get_next_child(np, NULL);
    
    if(of_property_read_u32_index(child_node,"reg",0,&edma_base_addr)){
        ddr_test_print("can not find edma_base_addr\n");
        return ERROR;
    }

    chan_id = bsp_edma_channel_init(EDMA_PWC_LDSP_TCM, (channel_isr)0, 0, 0);

    if( (0==edma_base_addr) || ((unsigned) ERROR == chan_id) ){
        ddr_test_print("edma_base_addr=0x%x chan_id=%d, error\n", edma_base_addr, chan_id);
        return ERROR;
    }else{
        ddr_test_print("edma_base_addr=0x%x chan_id=%d\n", edma_base_addr, chan_id);
    }


    start_addr = (unsigned)osl_malloc(256);
    if(!start_addr){
        ddr_test_print("alloc failed\n");
        return ERROR;
    }

    /* configs */
    ddr_test_edma_configs.src_addr = start_addr;
    ddr_test_edma_configs.des_addr = start_addr+128;
    edma_lli_addr = edma_base_addr + 0x800 + chan_id*0x40;
    if( readl(edma_lli_addr + 0x1C)&0x1 ){
        ddr_test_print("edma busy now, test failed\n");
        osl_free((void*)start_addr);
        return ERROR;
    }
    
    local_irq_save(flags);
    
    writel(ddr_test_edma_configs.lli     , edma_lli_addr + 0x0);
    writel(ddr_test_edma_configs.bindx   , edma_lli_addr + 0x4);
    writel(ddr_test_edma_configs.cindx   , edma_lli_addr + 0x8);
    writel(ddr_test_edma_configs.cnt1    , edma_lli_addr + 0xc);
    writel(ddr_test_edma_configs.cnt0    , edma_lli_addr + 0x10);
    writel(ddr_test_edma_configs.src_addr, edma_lli_addr + 0x14);
    writel(ddr_test_edma_configs.des_addr, edma_lli_addr + 0x18);
    writel(ddr_test_edma_configs.config  , edma_lli_addr + 0x1C);

    /* start */
    slice_value[0] = bsp_get_slice_value();
    writel(ddr_test_edma_configs.config|0x1  , edma_lli_addr + 0x1C);
    do{
        reg_val = readl(edma_lli_addr + 0x1C);
    }while(reg_val&0x1);
    slice_value[1] = bsp_get_slice_value();

    local_irq_restore(flags);


    ddr_test_print("test use ddr_addr=0x%x, test size=0x%x Bytes\n", start_addr\
        , ((ddr_test_edma_configs.cnt1+1)*(((ddr_test_edma_configs.cnt0&0xFFFF0000)>>16)+1)*(ddr_test_edma_configs.cnt0&0xFFFF)));

    slice_delta = get_timer_slice_delta(slice_value[0], slice_value[1]);

    ddr_test_print("time begin:0x%x, end:0x%x, delta:0x%x = %d us\n", slice_value[0], slice_value[1],
    slice_delta, slice_delta*1000000/32768  );
    
    osl_free((void*)start_addr);
    return OK;
}


void ddr_test(enum ddr_test_type test_type, unsigned cnt)
{
    u32 index;
    if(0 == cnt){
        ddr_test_print("cnt=0 is invaliad \n");
        return;
    }
    if((test_type>ddr_test_type_reserved) && (test_type<ddr_test_dma_copy)){
        ddr_test_cpu(ddr_test_cpu_args[test_type][0], ddr_test_cpu_args[test_type][1], ddr_test_size, cnt);
    }
    else if(ddr_test_dma_copy==test_type){
        for(index=0;index<cnt;index++){
            if(ddr_test_edma())
                ddr_test_print("ddr_test_edma error and stop \n");
        }
    }else{
        ddr_test_print("test_type=%d not surpported \n", test_type);
    }
}

void ddr_test_help(void)
{
    ddr_test_print("Warning: Cpu may be locked for seconds, please keep wdt closed \n");
    ddr_test_print("         Dfs have effects on the result of test \n");
    ddr_test_print("ddr_test cpu read/write ddr, ddr_test_size=%d \n", ddr_test_size );
    ddr_test_print("use  ddr_test_set(size) to change it \n\n");
    
    ddr_test_print("ddr_test 1 +times: cpu read  cacheable   ddr \n");
    ddr_test_print("ddr_test 2 +times: cpu read  nocacheable ddr \n");
    ddr_test_print("ddr_test 3 +times: cpu write cacheable   ddr \n");
    ddr_test_print("ddr_test 4 +times: cpu write nocacheable ddr \n");
    ddr_test_print(" e.g. \"ddr_test 1 40000\" \n\n");

    ddr_test_print("ddr_test 5 +times: edma do ddr copy, e.g.: \"ddr_test 5 1\"  \n");
    ddr_test_print("                   make sure PS-poweroff when use edma \n");

}


