
/* list_for_each_entry   lint --e{413,xxx} */
/*lint --e{413}*/

#include <string.h>
#include "securec.h"
#include <osl_malloc.h>
#include <osl_irq.h>
#include <osl_list.h>
#include <osl_spinlock.h>
#include <bsp_rsracc.h>
#include <bsp_dpm.h>
#include "edma_core.h"

u32 edma_irq_trace_enable = 0;
struct edma_ctrl edma_info;

struct edma_driver *get_edma_driver(struct edma_device *device)
{
    struct edma_driver *drv = NULL;
    unsigned long flags;

    spin_lock_irqsave(&edma_info.lock, flags);
    if (!list_empty(&edma_info.driver_list)) {
        list_for_each_entry(drv, &edma_info.driver_list, list) {
            if (drv->edma_type == device->edma_type){
                spin_unlock_irqrestore(&edma_info.lock, flags);
                return drv;
            }
        }
    }
    spin_unlock_irqrestore(&edma_info.lock, flags);

    return NULL;
}

struct edma_device * get_edma_device( u32 edma_id)
{
    struct edma_device * device = NULL;
    unsigned long flags;
    
    spin_lock_irqsave(&edma_info.lock, flags);
    list_for_each_entry(device, &edma_info.device_list, list) {
        if (device->edma_id == edma_id){
            spin_unlock_irqrestore(&edma_info.lock, flags);
            return device;
        }
    }
    spin_unlock_irqrestore(&edma_info.lock, flags);
    return device;
}
irqreturn_t edma_isr(void* edma_id)
{
    struct edma_device * device = NULL;

    device = get_edma_device( (u32)edma_id );
    if(device)
        return device->driver->global_ops->irq_handler(device);
    else{
        edma_error("edma_id=%d is error\n",edma_id);
    }
    return IRQ_HANDLED;
}

int edma_driver_register(struct edma_driver *driver)
{
    unsigned long flags;

    spin_lock_irqsave(&edma_info.lock, flags);
    list_add_tail(&driver->list, &edma_info.driver_list);
    spin_unlock_irqrestore(&edma_info.lock, flags);
    return 0;
}

void edma_chan_map_register(struct edma_request_maps_info *map_info, u32 chan_id_start)
{
    u32 i = 0;
    u32 request_id;
    struct edma_chan_request_map * maps;
    u32 num;

    maps = map_info->maps;
    num  = map_info->number_of_maps;

    if((maps == NULL)||(num==0)){
        edma_error("no chan map for chan_id_start=%d\n", chan_id_start);
        return;
    }else{
        for(i=0;i<num;i++){
            request_id = maps[i].request_id;
            edma_info.chan_map_table[request_id].channel_id = chan_id_start + maps[i].channel_id;
            edma_info.chan_map_table[request_id].peripheral = maps[i].peripheral;
        }
    }
}

int edma_device_chan_match(void)
{
    struct edma_device * device = NULL;
    struct edma_chan * chan = NULL;
    u32 chan_id = 0;
    u32 phy_chan_id = 0;

    chan = edma_info.chans;
    /* edma_list -> edma_chan */
    list_for_each_entry(device, &edma_info.device_list, list){
        if( chan >= (edma_info.chans+edma_info.number_of_chans) ){
            edma_error("no chan for edma %d",device->edma_id);
            return ERROR;
        }else{
            device->edma_chans = chan;
            for(phy_chan_id=0;phy_chan_id<device->num_of_chans;phy_chan_id++){
                chan->device = device;
                chan->chan_id = chan_id;
                chan->phy_chan_id = phy_chan_id;
                chan_id++;
                chan++;
            }
        }
    }
    return OK;
}

int edma_chans_register( struct edma_device *device )
{
    u32 num = 0;
    u32 sz = 0;
    void * p = NULL;

    num = device->num_of_chans;
    if(0==num){
        edma_error(" edma id ,chan num =0");
        return 0;
    }
    if(NULL==edma_info.chans){
        sz = sizeof(struct edma_chan) * num;
        p = osl_malloc( sz );
        if(p){
            (void)memset_s(p, sz, 0, sz);
            device->chan_id_start = 0;
            edma_info.number_of_chans = num;
            edma_info.chans = (struct edma_chan *) p;
        }else{
            edma_error("edma_info.chans osl_malloc(%d) error\n",sz);
        }
    }else{
        sz = sizeof(struct edma_chan) * ( num+edma_info.number_of_chans );
        p = osl_malloc( sz );
        if(p){
            (void)memset_s(p, sz, 0, sz);
            sz = sizeof(struct edma_chan) * edma_info.number_of_chans;
            (void)memcpy_s(p, sz, edma_info.chans, sz);
            osl_free((void *)edma_info.chans);
            device->chan_id_start = edma_info.number_of_chans;
            edma_info.number_of_chans += num;
            edma_info.chans = (struct edma_chan *) p;
        }else{
            edma_error("edma_info.chans malloc error\n");
        }
    }
    if( edma_device_chan_match() )
        return ERROR;
    else{
        edma_chan_map_register(&device->request_map_info, device->chan_id_start);
        return OK;
    }
}

int edma_device_register(struct edma_device *device)
{
    struct edma_driver *drv;
    unsigned long flags;

    spin_lock_irqsave(&edma_info.lock, flags);
    list_add_tail(&device->list, &edma_info.device_list);
    spin_unlock_irqrestore(&edma_info.lock, flags);
    edma_info.number_of_devices++;

    /*for each drivers,get driver by pid, set p->driver= driver*/
    drv = get_edma_driver(device);
    if (NULL == drv){
        edma_error("edma_id = %d can not find driver\n",device->edma_id);
        return ERROR;
    }
    device->driver = drv;
    if(edma_chans_register( device )){
        edma_error("edma_chans_register error, edma_id = %d \n", device->edma_id);
        return ERROR;
    }

    if (request_irq(device->irq_no, (irq_handler_t)edma_isr, 0, "edma", (void*)device->edma_id))
    {
        edma_error("request_irq failed, edma_id = %d \n", device->edma_id);
        return ERROR;
    }
    return OK;
}

int is_request_id_valiad(u32 request_id)
{    return (request_id<EDMA_REQ_MAX);  }
int is_channel_id_valiad(u32 channel_id)
{   return (channel_id<edma_info.number_of_chans);   }

u32 edma_request_chan_id(enum edma_req_id request_id)
{
    if(request_id < EDMA_REQ_MAX){
        return edma_info.chan_map_table[request_id].channel_id;
    }else{
        return (u32)ERROR;
    }
}

u32 edma_request_to_peri(enum edma_req_id request_id)
{
    u32 peripheral = (u32)-1;
    if(request_id < EDMA_REQ_MAX){
        peripheral = edma_info.chan_map_table[request_id].peripheral;
    }
    return peripheral;
}

void edma_clear_chan_cfg(struct edma_chan * chan)
{
    u32 sz = 0;

    sz = sizeof(struct edma_chan_cfg);
    (void)memset_s((void*)(&chan->desc.chan_cfg), sz, 0, sz);
}

struct edma_chan * chan_id_to_chan(u32 channel_id)
{
    if(!is_channel_id_valiad(channel_id)){
        edma_error("channel_id=%d invalid \n", channel_id);
        return NULL;
    }else
        return &edma_info.chans[channel_id];
}

s32 bsp_edma_suspend(struct dpm_device *dev)
{
    struct edma_device * device = NULL;
    s32 ret = 0;
    list_for_each_entry(device, &edma_info.device_list, list) {
        ret = device->driver->global_ops->suspend(device);
        if(ret)
            return ret;
    }
    return OK;
}

s32 bsp_edma_resume(struct dpm_device *dev)
{
    struct edma_device * device = NULL;
    list_for_each_entry(device, &edma_info.device_list, list) {
        device->driver->global_ops->resume(device);
    }
    return OK;
}

#include <bsp_hardtimer.h>
s32 edma_dpm_test(void)
{
    u32 stamp[2];
    stamp[0] = bsp_get_slice_value();
    if(bsp_edma_suspend(NULL))
        return -1;
    else
        (void)bsp_edma_resume(NULL);
    
    stamp[1] = bsp_get_slice_value();
    edma_error("stamps = 0x%x \n", stamp[1]-stamp[0]);
    return 0;
}

struct dpm_device edma_dpm = {
    .device_name = "edma_dpm",
    .prepare = NULL,
    .suspend = NULL,
    .suspend_late = bsp_edma_suspend,
    .resume_early = bsp_edma_resume,
    .resume = NULL,
    .complete = NULL,
};

s32 edma_device_pm_init(void)
{
    s32 ret = 0;
    ret = bsp_device_pm_add(&edma_dpm);
    return ret;
}


extern s32 edma_rsracc_dpm_init(struct edma_device *device);

void edma_dpm_init(void)
{
    s32 ret = 0;
    struct edma_device * device = NULL;

    if(bsp_rsracc_support()){
        list_for_each_entry(device, &edma_info.device_list, list) {
            ret = edma_rsracc_dpm_init(device);
            if(ret){
                edma_error("edma_rsracc_dpm_init error \n");
                return;
            }
        }
    }else{
        ret = bsp_device_pm_add(&edma_dpm);
        if(ret){
            edma_error("fail to add edma dpm device\n");
        }
    }
}

int ccpu_reset_edmac_and_wait_idle(void)
{
    struct edma_device * device = NULL;
    s32 ret = 0;
    list_for_each_entry(device, &edma_info.device_list, list) {
        ret = device->driver->global_ops->reset_and_wait_idle(device);
        if(ret)
            return ret;
    }
    return OK;
}


s32 edma_core_init(void)
{
    u32 i = 0;
    struct edma_chan_request_map *map_table = NULL;
    s32 ret = 0;

    spin_lock_init(&edma_info.lock);
    INIT_LIST_HEAD(&edma_info.device_list);
    INIT_LIST_HEAD(&edma_info.driver_list);
    edma_info.number_of_devices  = 0;
    edma_info.number_of_chans    = 0;
    edma_info.chans              = NULL;
    map_table = edma_info.chan_map_table;
    for(i=0;i<EDMA_REQ_MAX;i++){
        map_table[i].request_id = i;
        map_table[i].channel_id = (u32)(-1);
        map_table[i].peripheral = (u32)(-1);
    }

    return ret;
}


