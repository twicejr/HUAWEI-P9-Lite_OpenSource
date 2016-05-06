#include <of.h>
#include <osl_malloc.h>
#include <bsp_edma.h>
#include <bsp_slice.h>
#include <c_sys_bus_core.h>
#include <c_sys_bus_pressure.h>
#include <c_sys_edma.h>

u32 edma_lli_loop_src[edma_ddr_size/4] ;
u32 edma_lli_loop_des[edma_ddr_size/4] ;
struct sys_edma g_sys_edma[2];

void * dma_alloc_coherent(void* none, u32 size, edma_addr_t *handle, u32 none2)
{
    void * memory;
    memory = osl_cachedma_malloc(size);
    *handle = (edma_addr_t)memory;
	return memory;
}

/* update time and totalsize and restart */
void sys_edma_ddr_irq_handler(unsigned int channel_arg, unsigned int int_status)
{
    if(bsp_slice_getcurtime(&g_sys_edma[0].end_t)!= 0)
    {
        sys_bus_trace("get 64bit timestamp error\n");
    }

    g_sys_edma[0].totaltime = g_sys_edma[0].end_t - g_sys_edma[0].start_t;
    g_sys_edma[0].totalsize += 1;

    if(g_sys_edma[0].flag)
    {
        sys_edma_lli_start(&g_sys_edma[0]);
    }
}

/* update time and totalsize and restart */
void sys_edma_sram_irq_handler(unsigned int channel_arg, unsigned int int_status)
{
    if(bsp_slice_getcurtime(&g_sys_edma[1].end_t)!= 0)
    {
        sys_bus_trace("get 64bit timestamp error\n");
    }

    g_sys_edma[1].totaltime = g_sys_edma[1].end_t - g_sys_edma[1].start_t;
    g_sys_edma[1].totalsize += 1;

    if(g_sys_edma[1].flag)
    {
        sys_edma_lli_start(&g_sys_edma[1]);
    }
}

void sys_edma_lli_config(struct sys_edma* sys_edma)
{
    edma_addr_t  phy_edma_addr    = 0;
    edma_addr_t  phy_edma_addr_tmp    = 0;
    struct edma_cb *psttemp   = NULL;
    u32 lli_num = sys_edma->lli_num;
    u32 i = 0;

    sys_edma->edma_cb = (struct edma_cb *)dma_alloc_coherent(NULL,(lli_num * sizeof(struct edma_cb)),
                                                                   &phy_edma_addr, GFP_DMA|__GFP_WAIT);
    if (NULL == sys_edma->edma_cb)
    {
        sys_bus_trace("sys_edma_lli_config alloc failed!\n");
    	return;
    }

    psttemp = sys_edma->edma_cb;
    phy_edma_addr_tmp = phy_edma_addr;

    for(i = 0; i < lli_num; i++)
    {
        phy_edma_addr_tmp += sizeof(struct edma_cb);
        if(i == (lli_num -1))
        {
            psttemp->lli = EDMA_SET_LLI(phy_edma_addr_tmp, 1);
        }
        else
        {
            psttemp->lli = EDMA_SET_LLI(phy_edma_addr_tmp, 0);
        }
        psttemp->config = EDMA_SET_CONFIG(sys_edma->req, EDMA_M2M, EDMA_TRANS_WIDTH_64, EDMA_BUR_LEN_16);
        psttemp->src_addr = sys_edma->src;
        psttemp->des_addr = sys_edma->dst;
        psttemp->cnt0 = sys_edma->size;
        psttemp->bindx = 0;
        psttemp->cindx = 0;
        psttemp->cnt1  = 0;
        psttemp++;
    }

    sys_edma->channel_id = bsp_edma_channel_init(sys_edma->req, sys_edma->handler, 0, EDMA_INT_DONE);
    if (sys_edma->channel_id < 0)
    {
        sys_bus_trace("error ret_id = 0x%X\n\n",sys_edma->channel_id);
        return;
    }

}

void sys_edma_lli_start(struct sys_edma* sys_edma)
{
    struct edma_cb *psttemp   = NULL;

    /*获取首节点寄存器地址*/
    psttemp = bsp_edma_channel_get_lli_addr(sys_edma->channel_id);
    if (NULL == psttemp)
    {
        sys_bus_trace("failed!\n\n");
        return;
    }

    /*配置首节点寄存器*/
    psttemp->lli = sys_edma->edma_cb->lli;
    psttemp->config = sys_edma->edma_cb->config & 0xFFFFFFFE;
    psttemp->src_addr = sys_edma->edma_cb->src_addr;
    psttemp->des_addr = sys_edma->edma_cb->des_addr;
    psttemp->cnt0 = sys_edma->edma_cb->cnt0;
    psttemp->bindx = 0;
    psttemp->cindx = 0;
    psttemp->cnt1  = 0;
    if (bsp_edma_channel_lli_async_start(sys_edma->channel_id))
    {
        sys_bus_trace("FAILED!\n\n");
    }
}
void sys_edma_record(struct master* master)
{

}

void sys_edma_report(struct master* master)
{
    u64 s_time = 0;
    u32 M_size = 0;
    sys_bus_trace("sys edma analysis :\n");

    s_time = g_sys_edma[0].totaltime>>15;
    M_size = g_sys_edma[0].totalsize;
    sys_bus_trace(" ddr total time :%d s\n", (u32)s_time);
    sys_bus_trace(" ddr total size :%d MB\n", M_size);
    if(s_time)
    {
        sys_bus_trace(" ddr rate :%d MB/s\n", M_size/(u32)s_time);
	}

    s_time = g_sys_edma[1].totaltime>>15;
    M_size = g_sys_edma[1].totalsize;
    sys_bus_trace("sram total time :%d s\n", s_time);
    sys_bus_trace("sram total size :%d MB\n", M_size);
	if(s_time)
    {
    	sys_bus_trace("sram rate :%d MB/s\n", M_size/(u32)s_time);
	}
}

void sys_edma_start(struct master* master)
{
    //master->start_flag = 1;
    /* 0 is ddr , 1 is sram */
    g_sys_edma[0].handler = sys_edma_ddr_irq_handler;
    g_sys_edma[0].src = (u32)edma_lli_loop_src;
    g_sys_edma[0].dst = (u32)edma_lli_loop_des;
    g_sys_edma[0].size = edma_ddr_size;
    g_sys_edma[0].lli_num = 1024*1024/edma_ddr_size;
    g_sys_edma[0].flag = 1;
    g_sys_edma[0].totalsize = 0;
    g_sys_edma[0].totaltime = 0;

    g_sys_edma[1].handler = sys_edma_sram_irq_handler;
    g_sys_edma[1].src = (u32)SRAM_SYS_EDMA_ADDR;
    g_sys_edma[1].dst = (u32)SRAM_SYS_EDMA_ADDR;
    g_sys_edma[1].size = SRAM_SYS_EDMA_SIZE;
    g_sys_edma[1].lli_num = 1024*1024/SRAM_SYS_EDMA_SIZE;
    g_sys_edma[1].flag = 1;
    g_sys_edma[1].totalsize = 0;
    g_sys_edma[1].totaltime = 0;

    sys_edma_lli_config(&g_sys_edma[0]);
    sys_edma_lli_config(&g_sys_edma[1]);
	if(bsp_slice_getcurtime(&g_sys_edma[0].start_t)!= 0)
    {
        sys_bus_trace("get 64bit timestamp error\n");
    }
	if(bsp_slice_getcurtime(&g_sys_edma[1].start_t)!= 0)
    {
        sys_bus_trace("get 64bit timestamp error\n");
    }

    sys_edma_lli_start(&g_sys_edma[0]);
    sys_edma_lli_start(&g_sys_edma[1]);
  }

void sys_edma_stop(struct master* master)
{
    //master->start_flag = 0;
    g_sys_edma[0].flag = 0;
    g_sys_edma[1].flag = 0;
}

void sys_edma_init(struct master* master)
{
    int ret;
    master->start = sys_edma_start;
    master->stop = sys_edma_stop;
    master->record = sys_edma_record;
    master->report = sys_edma_report;

    ret = of_property_read_u32_index(master->np, "edma_req_id_ddr", 0, &g_sys_edma[0].req);
    if(ret)
    {
        sys_bus_trace("read edma_req_id_ddr err\n");
        return;
    }

    ret = of_property_read_u32_index(master->np, "edma_req_id_sram", 0, &g_sys_edma[1].req);
    if(ret)
    {
        sys_bus_trace("read edma_req_id_sram err\n");
        return;
    }

    //g_sys_edma[0].req = EDMA_SCI0_RX;
    //g_sys_edma[1].req = EDMA_SCI1_RX;

    master->init_flag = 1;
    sys_bus_trace("ok\n");
}

