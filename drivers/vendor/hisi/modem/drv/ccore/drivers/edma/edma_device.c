
#include <securec.h>
#include <string.h>
#include <osl_thread.h>
#include <mdrv_public.h>
#include <mdrv_int_comm.h>
#include <of.h>
#include <osl_bio.h>
#include <osl_irq.h>
#include <osl_malloc.h>
#include <bsp_edma.h>
#include <bsp_clk.h>
#include "edma_core.h"

int edma_ip_of_parse(struct device_node *child_node)
{
    struct edma_device * device = NULL;
    struct edma_chan_request_map *maps = NULL;
    u32 map_size = 0;
    void * p = NULL;
    s32 ret = 0;
    
    p = osl_malloc( sizeof(struct edma_device) );
    if(!p){
        edma_error("edma device malloc failed \n");
        return ERROR;
    }else{
        (void)memset_s(p, sizeof(struct edma_device), 0, sizeof(struct edma_device));
        device = (struct edma_device *)p;
    }

    ret |= of_property_read_u32( child_node, "edma_id", &device->edma_id );
    ret |= of_property_read_u32( child_node, "edma_type", &device->edma_type );
    ret |= of_property_read_u32( child_node, "interrupts_idx", &device->irq_index);
    ret |= of_property_read_u32( child_node, "num_of_chans", &device->num_of_chans );
    ret |= of_property_read_u32( child_node, "channels_suspend", &device->dpm_global.mask);
    if(ret){
        edma_error("edma device node read failed \n");
        edma_error("0x%x,0x%x,0x%x,0x%x,0x%x \n", device->edma_id,device->edma_type,
            device->irq_index,device->num_of_chans,device->dpm_global.mask);
        osl_free((void *) device);
        return ERROR;
    }else{}
    
    if(of_property_read_string(child_node, "clk_name", &device->clk_name)){
        edma_error("can not get clk_name, edma_id=%d need not clk control\n",device->edma_id);
    }else{
	    device->clk = clk_get(NULL, device->clk_name);
        if(IS_ERR(device->clk)){
            edma_error("fail to get clk,clk_name:%s\n",device->clk_name);
            osl_free((void *) device);
            return ERROR;
        }else{
            if(clk_enable(device->clk)){
                edma_error("clk_enable error,clk_name:%s\n",device->clk_name);
            }
        }
    }

    device->base_addr = (u32)of_iomap(child_node, 0);
    if(!device->base_addr){
        edma_error("of_iomap failed, edma_id = %d \n", device->edma_id);
        osl_free((void *) device);
        return ERROR;
    }
    device->irq_no = irq_of_parse_and_map(child_node, 0);

    if( NULL == of_get_property(child_node, "chan_req_map", (int*)(&map_size))){
        edma_error("no chan_req_map for edma_id %d \n", device->edma_id);
        return OK;
    }
    if(0==map_size){
        edma_error("no chan_req_map for edma_id %d \n", device->edma_id);
        return OK;
    }
    p = osl_malloc( map_size );
    if(!p){
        edma_error("edma maps malloc failed,size=%d \n", map_size);
        osl_free((void *) device);
        return ERROR;
    }else{
        (void)memset_s(p, map_size, 0, map_size);
        maps = (struct edma_chan_request_map *)p;
    }
    (void)of_property_read_u32_array( child_node,"chan_req_map", (unsigned int *)maps, map_size/4);
    device->request_map_info.maps = maps;
    device->request_map_info.number_of_maps = map_size / sizeof(struct edma_chan_request_map);

    if(edma_device_register(device)){
        osl_free((void *) device);
        osl_free((void *) maps);
        return ERROR;
    }
    else
        return OK;
}

int edma_device_init(void)
{
	struct device_node *np = NULL;
    struct device_node *child_node = NULL;

    np = of_find_compatible_node(NULL, NULL, "hisilicon,edma");
    if (!np){
        edma_error("can not find node\n");
        return ERROR;
    }
    for_each_child_of_node(np, child_node){
        if(edma_ip_of_parse(child_node))
            return ERROR;
    }
    return OK;
}

