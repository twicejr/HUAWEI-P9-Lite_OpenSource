


#ifndef __HW_ALAN_KERNEL_HWISP_INTERFACE_H__
#define __HW_ALAN_KERNEL_HWISP_INTERFACE_H__

#include <linux/platform_device.h>
#include <linux/videodev2.h>
#include <media/huawei/isp_cfg.h>
#include <media/videobuf2-core.h>

#include "hwcam_intf.h"

typedef struct _tag_hwisp_vtbl hwisp_vtbl_t; 
typedef struct _tag_hwisp_intf hwisp_intf_t; 

typedef struct _tag_hwisp_notify_vtbl hwisp_notify_vtbl_t; 
typedef struct _tag_hwisp_notify_intf hwisp_notify_intf_t; 

typedef struct _tag_hwisp_stream_vtbl hwisp_stream_vtbl_t; 
typedef struct _tag_hwisp_stream_intf hwisp_stream_intf_t; 

typedef struct _tag_hwisp_vtbl
{
    char const* (*get_name)(hwisp_intf_t* i); 
    int (*power_on)(hwisp_intf_t* i);   
    int (*power_off)(hwisp_intf_t* i);   
    int (*reset)(hwisp_intf_t* i);   
    int (*load_firmware)(hwisp_intf_t* i); 
    int (*init_reg)(hwisp_intf_t* i);   
    int (*config)(hwisp_intf_t* i,void* cfg);

    int (*create_stream)(hwisp_intf_t* i, 
                         struct video_device* vdev,  
                         hwisp_stream_info_t* info); 
    int (*stream_start)(hwisp_intf_t* i, 
                        hwisp_stream_intf_t* stm);   
    int (*stream_stop)(hwisp_intf_t* i, 
                       hwisp_stream_intf_t* stm);   
    int (*fix_ddrfreq)(hwisp_intf_t* i,void* ddrfreq);
} hwisp_vtbl_t; 

typedef struct _tag_hwisp_intf
{
    hwisp_vtbl_t*                               vtbl; 
} hwisp_intf_t; 

static inline char const* 
hwisp_intf_get_name(hwisp_intf_t* i)
{
    return i->vtbl->get_name(i); 
}

static inline int 
hwisp_intf_power_on(hwisp_intf_t* i)
{
    return i->vtbl->power_on(i); 
}

static inline int 
hwisp_intf_power_off(hwisp_intf_t* i)
{
    return i->vtbl->power_off(i); 
}

static inline int 
hwisp_intf_reset(hwisp_intf_t* i)
{
    return i->vtbl->reset(i); 
}

static inline int 
hwisp_intf_load_firmware(hwisp_intf_t* i)
{
    return i->vtbl->load_firmware(i); 
}

static inline int 
hwisp_intf_init_reg(hwisp_intf_t* i)
{
    return i->vtbl->init_reg(i); 
}

static inline int
hwisp_stream_intf_fix_ddrfreq(hwisp_intf_t* intf,void* ddrfreq)
{
    return intf->vtbl->fix_ddrfreq(intf, ddrfreq);
}

static inline int 
hwisp_intf_create_stream(hwisp_intf_t* i, 
                         struct video_device* vdev, 
                         hwisp_stream_info_t* si)
{
    return i->vtbl->create_stream(i, vdev, si); 
}

static inline int 
hwisp_intf_stream_start(hwisp_intf_t* i, 
                        hwisp_stream_intf_t* stm)
{
    return i->vtbl->stream_start(i, stm); 
}

static inline int 
hwisp_intf_stream_stop(hwisp_intf_t* i, 
                       hwisp_stream_intf_t* stm)
{
    return i->vtbl->stream_stop(i, stm); 
}

typedef struct _tag_hwisp_notify_vtbl
{
    void (*sof)(hwisp_notify_intf_t* i, hwisp_event_t* isp_ev);
    void (*eof)(hwisp_notify_intf_t* i, hwisp_event_t* isp_ev);
    void (*cmd_ready)(hwisp_notify_intf_t* i, hwisp_event_t* isp_ev); 
} hwisp_notify_vtbl_t; 

typedef struct _tag_hwisp_notify_intf
{
    hwisp_notify_vtbl_t*                        vtbl; 
} hwisp_notify_intf_t; 

static inline void 
hwisp_notify_intf_sof(hwisp_notify_intf_t* i, 
                      hwisp_event_t* isp_ev)
{
    return i->vtbl->sof(i, isp_ev); 
}

static inline void 
hwisp_notify_intf_eof(hwisp_notify_intf_t* i, 
                      hwisp_event_t* isp_ev)
{
    return i->vtbl->eof(i, isp_ev); 
}

static inline void 
hwisp_notify_intf_cmd_ready(hwisp_notify_intf_t* i, 
                            hwisp_event_t* isp_ev)
{
    return i->vtbl->cmd_ready(i, isp_ev); 
}

typedef struct _tag_hwisp_buf
{
    hwisp_stream_buf_info_t                     info; 
    struct list_head                            node; 
} hwisp_buf_t; 

typedef struct _tag_hwisp_stream_vtbl
{
    void (*get)(hwisp_stream_intf_t* i);   
    int (*put)(hwisp_stream_intf_t* i);   

    int (*start)(hwisp_stream_intf_t* i);   
    int (*stop)(hwisp_stream_intf_t* i);   

    hwisp_buf_t* (*get_buf)(hwisp_stream_intf_t* intf); 
    int (*put_buf)(hwisp_stream_intf_t* intf, 
                   hwisp_buf_t* buf); 
    int (*buf_done)(hwisp_stream_intf_t* intf, 
                    hwisp_buf_t* buf); 
} hwisp_stream_vtbl_t; 

typedef struct _tag_hwisp_stream_intf
{
	uint32_t				port;
	hwisp_stream_vtbl_t*	vtbl; 
} hwisp_stream_intf_t; 

hwisp_stream_intf_t*
hwisp_stream_get_by_node(struct list_head* node); 

static inline void
hwisp_stream_intf_get(hwisp_stream_intf_t* intf)
{
    intf->vtbl->get(intf); 
}

static inline int
hwisp_stream_intf_put(hwisp_stream_intf_t* intf)
{
    return intf->vtbl->put(intf); 
}

static inline int
hwisp_stream_intf_start(hwisp_stream_intf_t* intf)
{
    return intf->vtbl->start(intf); 
}

static inline int
hwisp_stream_intf_stop(hwisp_stream_intf_t* intf)
{
    return intf->vtbl->stop(intf); 
}

static inline hwisp_buf_t*
hwisp_stream_intf_get_buf(hwisp_stream_intf_t* intf)
{
    return intf->vtbl->get_buf(intf); 
}

static inline int
hwisp_stream_intf_put_buf(hwisp_stream_intf_t* intf, 
                          hwisp_buf_t* vb)
{
    return intf->vtbl->put_buf(intf, vb); 
}

static inline int
hwisp_stream_intf_buf_done(hwisp_stream_intf_t* intf, 
                           hwisp_buf_t* vb)
{
    return intf->vtbl->buf_done(intf, vb); 
}

extern int32_t 
hwisp_register(struct platform_device* pdev, 
        hwisp_intf_t* isp,
        hwisp_notify_intf_t** notify); 

extern void
hwisp_unregister(hwisp_intf_t* isp_intf);

extern void
hwisp_tasklet(unsigned long data);

extern int 
hwisp_create_stream(struct video_device* vdev, 
                    hwisp_intf_t* isp, 
                    hwisp_stream_info_t* si, 
                    struct list_head* streams); 

struct ion_client;

typedef struct _tag_hwisp_stream
{
    struct v4l2_fh                              rq;

    hwisp_stream_intf_t                         intf; 
    struct kref                                 ref; 
    struct list_head	                        node;
    struct mutex                                lock; 

    unsigned long                               stream_type;
    unsigned long                               stream_direction;
    ovisp23_port_info_t                         port; 

    struct semaphore                            buffer_readyQ;
    wait_queue_head_t                           wait;
    uint8_t                                     down_flag;

    hwisp_intf_t*                               isp;
	struct ion_client							*ion_vc;
    spinlock_t                                  lock_bufq; 
    struct list_head                            bufq_invalid;
    struct list_head                            bufq_idle;
    struct list_head                            bufq_busy;
    struct list_head                            bufq_done;
    struct list_head                            bufq_user;
	unsigned long								enque_buf_count;
	hwisp_buf_t                                 buf[0];
} hwisp_stream_t; 


#endif // __HW_ALAN_KERNEL_HWISP_INTERFACE_H__

