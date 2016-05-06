
#include <osl_types.h>
#include <osl_thread.h>
#include <osl_irq.h>
#include <bsp_reset.h>
#include <bsp_edma.h>
#include "edma_core.h"

extern int edma_driver_init(void);
extern int edma_device_init(void);
extern void edma_dpm_init(void);

s32 bsp_edma_init(void)
{
    if(edma_core_init()){
        edma_error("edma_core_init failed \n");
        return ERROR;
    }
    (void)edma_driver_init();
    if(edma_device_init()){
        edma_error("edma_device_init failed \n");
        return ERROR;
    }

    edma_dpm_init();
    (void)bsp_register_master_idle(EDMAC_IDLE, ccpu_reset_edmac_and_wait_idle);
    edma_error("edma_init ok\n");
    return OK;
}

s32 bsp_edma_channel_init (enum edma_req_id request_id, channel_isr pFunc, u32 channel_arg, u32 int_flag)
{
    u32 chan_id = 0xFFFFFFFF;
    struct edma_chan * chan = NULL;
    struct edma_chan_isr chan_isr = {0};
    u32 peri = 0;

    if(!is_request_id_valiad(request_id)){
        edma_error("request_id=%d invalid.\n", request_id);
        return ERROR;
    }

    chan_id = edma_request_chan_id( request_id );
    if((s32)chan_id == ERROR){
        edma_error("request_id=%d ok, but chan_id=%d err \n", request_id, chan_id);
        return ERROR;
    }
    else{
        chan = chan_id_to_chan( chan_id );
        if(chan){
            edma_clear_chan_cfg(chan);
            peri = bsp_edma_get_physical_req(request_id);
            chan->device->driver->chan_ops->set_peri( chan, peri );
            chan_isr.callback = pFunc;
            chan_isr.chan_arg = channel_arg;
            chan_isr.int_stat = int_flag;
            chan->device->driver->chan_ops->register_isr( chan, &chan_isr );
            return (s32)chan_id;
        }else{
            edma_error("request_id=%d, chan_id=%d ok, but get no chan \n", request_id, chan_id);
            return ERROR;
        }
    }
}

s32 bsp_edma_channel_free (u32 channel_id)
{
    struct edma_chan * chan = NULL;

    chan = chan_id_to_chan( channel_id );
    if(!chan){
        edma_error("channel_id=%d err\n", channel_id);
        return ERROR;
    }

    chan->device->driver->chan_ops->unregister_isr(chan);
    edma_clear_chan_cfg(chan);
    return OK;
}

s32 bsp_edma_current_transfer_address(u32 channel_id)
{
    s32 ret = 0;
    struct edma_chan * chan = NULL;

    chan = chan_id_to_chan( channel_id );
    if(chan){
        ret = (s32)chan->device->driver->chan_ops->get_cur_trans_addr(chan);
        return ret;
    }else{
        edma_error("channel_id=%d err \n", channel_id);
        return -1;
    }
}

u64 bsp_edma_current_cnt(u32 channel_id)
{
    struct edma_chan * chan = NULL;
    u64 size = 0;

    chan = chan_id_to_chan( channel_id );
    if(chan){
        size = chan->device->driver->chan_ops->get_cur_cnt( chan ); 
        return size;
    }else{
        edma_error("channel_id=%d err \n", channel_id);
        return (u64)(-1);
    }
}

s32 bsp_edma_channel_stop(u32 channel_id)
{
    struct edma_chan * chan = NULL;
    s32 cur_addr = 0;

    chan = chan_id_to_chan( channel_id );
    if(chan){
        chan->device->driver->chan_ops->stop( chan );
        cur_addr = bsp_edma_current_transfer_address(channel_id);
        return cur_addr;
    }else{
        edma_error("channel_id=%d err \n", channel_id);
        return ERROR;
    }
    
}

s32 bsp_edma_channel_is_idle (u32 channel_id)
{
    struct edma_chan * chan = NULL;
    u32 ret = 0;

    chan = chan_id_to_chan( channel_id );
    if(chan){
        ret = chan->device->driver->chan_ops->get_ch_stat( chan );
        if(ret == 1)
            return 0;
        else
            return 1;
    }else{
        edma_error("chan_id=%d err\n", channel_id);
        return ERROR;
    }
}

s32 bsp_edma_chanmap_is_idle (u32 channel_map)
{
    return 0;
}

unsigned int bsp_edma_get_physical_req(BALONG_DMA_REQ_E request_id)
{
    u32 peri = (u32)(-1);
    
    peri = edma_request_to_peri( request_id);

    if (peri<edma_peri_req_max)
        return peri;
    else
        return edma_peri_req_max;
}

s32 bsp_edma_channel_set_config (u32 channel_id, u32 direction, u32 burst_width, u32 burst_len)
{
    struct edma_chan * chan = NULL;
    if((direction>EDMA_M2M)||(direction<EDMA_P2M)
        ||(burst_width>EDMA_TRANS_WIDTH_64)||(burst_len>EDMA_BUR_LEN_16)){
        edma_error("configs err: direction=%d, burst_width=%d, burst_len=%d \n",
            direction,burst_width,burst_len);
        return ERROR;
    }

    chan = chan_id_to_chan( channel_id );
    if(chan){
        chan->device->driver->chan_ops->set_direction( chan, direction );
        chan->device->driver->chan_ops->set_burst( chan, burst_width, burst_len );
        return OK;
    }else{
        edma_error("chan_id=%d err\n", channel_id);
        return ERROR;
    }
}

s32 bsp_edma_channel_dest_set_config(u32 channel_id, u32 dest_width, u32 dest_len)
{
    struct edma_chan * chan = NULL;
    if((dest_width>EDMA_TRANS_WIDTH_64)||(dest_len>EDMA_BUR_LEN_16)){
            edma_error("configs err: dest_width=%d, dest_len=%d \n", dest_width, dest_len);
            return ERROR;
    }

    chan = chan_id_to_chan( channel_id );
    if(chan){
        chan->device->driver->chan_ops->set_des_config( chan, dest_width, dest_len);
        return OK;
    }else{
        edma_error("chan_id=%d err\n", channel_id);
        return ERROR;
    }
}

s32 bsp_edma_channel_2vec_start (u32 channel_id, u32 src_addr, u32 des_addr, u32 len, u32 size_align)
{

    struct edma_chan * chan = NULL;
    struct edma_chan_ops* chan_ops = NULL;
    u32 reg_v = 0;
    u32 bindx_set = 0;
    struct edma_chan_cfg * chan_cfg = NULL;
    u32 a_count, b_count;

    chan = chan_id_to_chan( channel_id );
    if(!chan){
        edma_error("chan_id=%d err\n", channel_id);
        return ERROR;
    }

    a_count = size_align;
    if((a_count>=0x8000)||(0==a_count)){
        edma_error(" input a_count=0x%X is invalide \n",a_count);
        return ERROR;
    }
    if( len%size_align != 0){
        edma_error("input len=0x%X not aligned \n",len);
        return ERROR;
    }
    b_count = (len/size_align)-1;
    if( 0x10000 <= b_count ){
        edma_error("input len=0x%X too big, try increase size_align \n",len);
        return ERROR;
    }
    chan_cfg = &chan->desc.chan_cfg;
    /* if src_index is inc, src_bindx should be set to size_align;
       if not, src_bindx is set to 0 */
    reg_v = chan_cfg->config;
    if(reg_v&EDMAC_TRANSFER_CONFIG_SOUR_INC){
        bindx_set |= (size_align<<16);
    }
    if(reg_v&EDMAC_TRANSFER_CONFIG_DEST_INC){
        bindx_set |= (size_align);
    }

    chan_cfg->lli       = 0;
    chan_cfg->bindx     = bindx_set;
    chan_cfg->cindx     = 0;
    chan_cfg->cnt1      = 0;
    chan_cfg->cnt0      = (b_count<<16|a_count);
    chan_cfg->src_addr  = src_addr;
    chan_cfg->des_addr  = des_addr;
    chan_ops = chan->device->driver->chan_ops;
    chan_ops->submit( chan, &chan->desc );
    chan_ops->start( chan );
    return OK;

}

s32 bsp_edma_channel_async_start (u32 channel_id, u32 src_addr, u32 des_addr, u32 len)
{
    struct edma_chan * chan = NULL;
    struct edma_chan_ops* chan_ops = NULL;
    u32 a_count = 0;
    u32 b_count = 0;

    chan = chan_id_to_chan( channel_id );
    if(!chan){
        edma_error("chan_id=%d err\n", channel_id);
        return ERROR;
    }
    if(len >= SZ_64K){
        /* try 2 vec */
        b_count = (!(len%SZ_16K)) ? (len/SZ_16K - 1) \
                : (!(len%SZ_8K )) ? (len/SZ_8K  - 1) \
                : (!(len%SZ_4K )) ? (len/SZ_4K  - 1) : 0;
        if(0==b_count){
            edma_error(" len=0x%x is too large, and try 2vec failed \n",len);
            return ERROR;
        }else{
            a_count = len / (b_count+1);
            return bsp_edma_channel_2vec_start (channel_id, src_addr, des_addr, len, a_count);
        }
    }else{
        chan->desc.chan_cfg.lli       = 0;
        chan->desc.chan_cfg.bindx     = 0;
        chan->desc.chan_cfg.cindx     = 0;
        chan->desc.chan_cfg.cnt1      = 0;
        chan->desc.chan_cfg.cnt0      = len;
        chan->desc.chan_cfg.src_addr = src_addr;
        chan->desc.chan_cfg.des_addr = des_addr;

        chan_ops = chan->device->driver->chan_ops;
        chan_ops->submit( chan, &chan->desc );
        chan_ops->start( chan );
    }
    return OK;

}

s32 bsp_edma_channel_start (u32 channel_id, u32 src_addr, u32 des_addr, u32 len)
{
    if(bsp_edma_channel_async_start( channel_id, src_addr, des_addr, len))
        return ERROR;
    while(!bsp_edma_channel_is_idle(channel_id)){
        (void)osl_task_delay(1);
    }
    return OK;
}


struct edma_cb *bsp_edma_channel_get_lli_addr (u32 channel_id)
{
    struct edma_chan * chan = NULL;

    chan = chan_id_to_chan( channel_id );
    if(!chan){
        return NULL;
    }
    return (struct edma_cb *)chan->device->driver->chan_ops->get_lli_addr( chan );
}

s32 bsp_edma_channel_lli_async_start (u32 channel_id)
{
    struct edma_chan * chan = NULL;
    struct edma_chan_ops* chan_ops = NULL;

    chan = chan_id_to_chan( channel_id );
    if(!chan){
        return ERROR;
    }
    chan_ops = chan->device->driver->chan_ops;
    chan_ops->submit( chan, &chan->desc );
    chan_ops->start( chan );
    return OK;
}

s32 bsp_edma_channel_lli_start (u32 channel_id)
{
    if(bsp_edma_channel_lli_async_start( channel_id ))
        return ERROR;
    while(!bsp_edma_channel_is_idle(channel_id)){
        (void)osl_task_delay(1);
    }
    return OK;
}

