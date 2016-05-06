


#ifndef __HW_ALAN_KERNEL_CAMERA_OBJ_MDL_INTERFACE__
#define __HW_ALAN_KERNEL_CAMERA_OBJ_MDL_INTERFACE__ 

#include <linux/dma-buf.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/videodev2.h>
#include <media/huawei/camera.h>
#include <media/v4l2-subdev.h>
#include <media/videobuf2-core.h>

struct ion_handle; 

#define HWCAM_CFG_ERR(fmt, arg...) \
    printk(KERN_ERR "%s(%d, %d): " fmt "\n", \
           __func__, __LINE__, current->pid, ## arg)

#define HWCAM_CFG_INFO(fmt, arg...) \
    printk(KERN_INFO "%s(%d, %d): " fmt "\n", \
           __func__, __LINE__, current->pid, ## arg)

#define HWCAM_CFG_DEBUG(fmt, arg...) \
    printk(KERN_DEBUG "%s(%d, %d): " fmt "\n", \
           __func__, __LINE__, current->pid, ## arg)

typedef struct _tag_hwcam_cfgreq_vtbl hwcam_cfgreq_vtbl_t; 
typedef struct _tag_hwcam_cfgreq_intf hwcam_cfgreq_intf_t; 

typedef struct _tag_hwcam_cfgreq_mount_pipeline_vtbl hwcam_cfgreq_mount_pipeline_vtbl_t; 
typedef struct _tag_hwcam_cfgreq_mount_pipeline_intf hwcam_cfgreq_mount_pipeline_intf_t; 

typedef struct _tag_hwcam_cfgreq_mount_stream_vtbl hwcam_cfgreq_mount_stream_vtbl_t; 
typedef struct _tag_hwcam_cfgreq_mount_stream_intf hwcam_cfgreq_mount_stream_intf_t; 

typedef struct _tag_hwcam_cfgack hwcam_cfgack_t; 

typedef struct _tag_hwcam_user_vtbl hwcam_user_vtbl_t; 
typedef struct _tag_hwcam_user_intf hwcam_user_intf_t; 

typedef struct _tag_hwcam_dev_vtbl hwcam_dev_vtbl_t; 
typedef struct _tag_hwcam_dev_intf hwcam_dev_intf_t; 

typedef struct _tag_hwcam_cfgpipeline_vtbl hwcam_cfgpipeline_vtbl_t; 
typedef struct _tag_hwcam_cfgpipeline_intf hwcam_cfgpipeline_intf_t; 

typedef struct _tag_hwcam_cfgstream_vtbl hwcam_cfgstream_vtbl_t; 
typedef struct _tag_hwcam_cfgstream_intf hwcam_cfgstream_intf_t; 


typedef struct _tag_hwcam_vbuf
{
    struct vb2_buffer                           buf;
    struct list_head                            node; 
} hwcam_vbuf_t;


////////////////////////////////////////////////////////////////////////////////
//
//          hwcam_cfgreq interface definition begin
//
////////////////////////////////////////////////////////////////////////////////

typedef struct _tag_hwcam_cfgreq_vtbl
{
    void (*get)(hwcam_cfgreq_intf_t* intf);
    int (*put)(hwcam_cfgreq_intf_t* intf); 
    int (*on_req)(hwcam_cfgreq_intf_t* intf, 
                  struct v4l2_event* ev); 
    int (*on_cancel)(hwcam_cfgreq_intf_t* intf, 
                     int reason); 
    int (*on_ack)(hwcam_cfgreq_intf_t* intf, 
                  hwcam_cfgack_t* ack); 
} hwcam_cfgreq_vtbl_t; 

typedef struct _tag_hwcam_cfgreq_intf
{
    hwcam_cfgreq_vtbl_t const*                  vtbl; 
} hwcam_cfgreq_intf_t; 

static inline void 
hwcam_cfgreq_intf_get(hwcam_cfgreq_intf_t* intf)
{
    return intf->vtbl->get(intf); 
}

static inline int 
hwcam_cfgreq_intf_put(hwcam_cfgreq_intf_t* intf)
{
    return intf->vtbl->put(intf); 
}

static inline int 
hwcam_cfgreq_intf_on_req(hwcam_cfgreq_intf_t* intf, 
                         struct v4l2_event* ev)
{
    return intf->vtbl->on_req(intf, ev); 
}

static inline int 
hwcam_cfgreq_intf_on_cancel(hwcam_cfgreq_intf_t* intf, 
                            int reason)
{
    return intf->vtbl->on_cancel(intf, reason); 
}

static inline int 
hwcam_cfgreq_intf_on_ack(hwcam_cfgreq_intf_t* intf, 
                         hwcam_cfgack_t* ack)
{
    return intf->vtbl->on_ack(intf, ack); 
}

static inline int 
hwcam_cfgreq_on_ack_noop(hwcam_cfgreq_intf_t* pintf, 
                         hwcam_cfgack_t* ack)
{
    return 0; 
}

typedef void (*pfn_hwcam_cfgdev_release_ack)(hwcam_cfgack_t* ack);

typedef struct _tag_hwcam_cfgack
{
    struct list_head                            node; 
    pfn_hwcam_cfgdev_release_ack                release; 
    struct v4l2_event                           ev; 
} hwcam_cfgack_t; 

static inline int 
hwcam_cfgack_result(hwcam_cfgack_t* ack)
{
    return ((hwcam_cfgreq_t*)ack->ev.u.data)->rc; 
}

typedef struct _tag_hwcam_cfgreq_mount_pipeline_vtbl
{
    hwcam_cfgreq_vtbl_t                         base; 
    void (*get_result)(hwcam_cfgreq_mount_pipeline_intf_t* intf, 
                      hwcam_cfgpipeline_intf_t** pl); 
} hwcam_cfgreq_mount_pipeline_vtbl_t; 

typedef struct _tag_hwcam_cfgreq_mount_pipeline_intf
{
    hwcam_cfgreq_mount_pipeline_vtbl_t const*   vtbl; 
} hwcam_cfgreq_mount_pipeline_intf_t; 

static inline void 
hwcam_cfgreq_mount_pipeline_intf_get_result(hwcam_cfgreq_mount_pipeline_intf_t* pintf, 
                                            hwcam_cfgpipeline_intf_t** pl)
{
    pintf->vtbl->get_result(pintf, pl); 
}

extern int
hwcam_cfgpipeline_mount_req_create_instance(struct video_device* vdev, 
                                            hwcam_dev_intf_t* cam, 
                                            int moduleID, 
                                            hwcam_cfgreq_mount_pipeline_intf_t** req); 

typedef struct _tag_hwcam_cfgreq_mount_stream_vtbl
{
    hwcam_cfgreq_vtbl_t                         base; 
    void (*get_result)(hwcam_cfgreq_mount_stream_intf_t* intf, 
                      hwcam_cfgstream_intf_t** st); 
} hwcam_cfgreq_mount_stream_vtbl_t; 

typedef struct _tag_hwcam_cfgreq_mount_stream_intf
{
    hwcam_cfgreq_mount_stream_vtbl_t const*     vtbl; 
} hwcam_cfgreq_mount_stream_intf_t; 

static inline void 
hwcam_cfgreq_mount_stream_intf_get_result(hwcam_cfgreq_mount_stream_intf_t* pintf, 
                                          hwcam_cfgstream_intf_t** st)
{
    pintf->vtbl->get_result(pintf, st); 
}

extern int
hwcam_cfgstream_mount_req_create_instance(struct video_device* vdev, 
                                          struct list_head* streams, 
                                          hwcam_cfgpipeline_intf_t* pl, 
                                          hwcam_user_intf_t* user, 
                                          hwcam_stream_info_t* info, 
                                          hwcam_cfgreq_mount_stream_intf_t** req); 

//  hwcam_cfgreq interface definition end


////////////////////////////////////////////////////////////////////////////////
//
//          hwcam_usr interface definition begin
//
////////////////////////////////////////////////////////////////////////////////

typedef struct _tag_hwcam_user_vtbl 
{
    void (*get)(hwcam_user_intf_t* intf);
    int (*put)(hwcam_user_intf_t* intf); 
    void (*wait_begin)(hwcam_user_intf_t* intf); 
    void (*wait_end)(hwcam_user_intf_t* intf); 
    void (*notify)(hwcam_user_intf_t* intf, 
                   struct v4l2_event* ev); 
} hwcam_user_vtbl_t; 

typedef struct _tag_hwcam_user_intf
{
    hwcam_user_vtbl_t const*                    vtbl; 
} hwcam_user_intf_t; 

static inline void
hwcam_user_intf_get(hwcam_user_intf_t* intf)
{
    intf->vtbl->get(intf); 
}

static inline int
hwcam_user_intf_put(hwcam_user_intf_t* intf)
{
    return intf->vtbl->put(intf); 
}

static inline void
hwcam_user_intf_wait_begin(hwcam_user_intf_t* intf)
{
    intf->vtbl->wait_begin(intf); 
}

static inline void
hwcam_user_intf_wait_end(hwcam_user_intf_t* intf)
{
    intf->vtbl->wait_end(intf); 
}

static inline void
hwcam_user_intf_notify(hwcam_user_intf_t* intf, 
                       struct v4l2_event* ev)
{
    intf->vtbl->notify(intf, ev); 
}

//  hwcam_usr interface definition end


////////////////////////////////////////////////////////////////////////////////
//
//          hwcam_dev interface definition begin
//
////////////////////////////////////////////////////////////////////////////////

extern int 
hwcam_dev_create(struct device* dev, int* dev_num);

typedef struct _tag_hwcam_dev_vtbl 
{
    void (*notify)(hwcam_dev_intf_t* intf, 
                   struct v4l2_event* ev); 
} hwcam_dev_vtbl_t; 

typedef struct _tag_hwcam_dev_intf
{
    hwcam_dev_vtbl_t const*                     vtbl; 
} hwcam_dev_intf_t; 

static inline void
hwcam_dev_intf_notify(hwcam_dev_intf_t* intf, 
                      struct v4l2_event* ev)
{
    intf->vtbl->notify(intf, ev); 
}
//  hwcam_dev interface definition end


////////////////////////////////////////////////////////////////////////////////
//
//          hwcam_cfgdev interface definition begin
//
////////////////////////////////////////////////////////////////////////////////

typedef struct _tag_hwcam_cfgdev_graphic_buffer
{
    struct list_head                            node; 
    hwcam_buf_info_t                            info; 
    struct ion_handle*                          handle; 
} hwcam_cfgdev_graphic_buffer_t;

extern void 
hwcam_cfgdev_lock(void); 

extern void 
hwcam_cfgdev_unlock(void); 

extern int 
hwcam_cfgdev_queue_ack(struct v4l2_event* ev); 

extern int 
hwcam_cfgdev_send_req(hwcam_user_intf_t* user, 
                      struct v4l2_event* ev, 
                      struct v4l2_fh* target, 
                      int one_way, 
                      int* rc); 

extern int
hwcam_cfgdev_mount_pipeline(hwcam_user_intf_t* user, 
                            hwcam_dev_intf_t* cam, 
                            int moduleID, 
                            hwcam_cfgpipeline_intf_t** pl); 

extern int 
hwcam_cfgdev_register_subdev(struct v4l2_subdev* subdev); 

extern int 
hwcam_cfgdev_unregister_subdev(struct v4l2_subdev* subdev); 

extern hwcam_data_table_t*  
hwcam_cfgdev_import_data_table(char const* name, 
                               hwcam_buf_info_t const* bi, 
                               struct ion_handle** handle); 

extern void
hwcam_cfgdev_release_data_table(struct ion_handle* handle); 

extern struct ion_handle* 
hwcam_cfgdev_import_graphic_buffer(int fd); 

extern int
hwcam_cfgdev_share_graphic_buffer(struct ion_handle* hdl); 

extern void
hwcam_cfgdev_release_graphic_buffer(struct ion_handle* hdl); 

//  hwcam_cfgdev interface definition end


////////////////////////////////////////////////////////////////////////////////
//
//          hwcam_cfgpipeline interface definition begin
//
////////////////////////////////////////////////////////////////////////////////

typedef struct _tag_hwcam_cfgpipeline_vtbl 
{
    void (*get)(hwcam_cfgpipeline_intf_t* intf);
    int (*put)(hwcam_cfgpipeline_intf_t* intf); 
    int (*umount)(hwcam_cfgpipeline_intf_t* intf); 

    int (*mount_buf)(hwcam_cfgpipeline_intf_t* intf, 
                     hwcam_user_intf_t* user, 
                     hwcam_buf_info_t* buf); 
    int (*unmount_buf)(hwcam_cfgpipeline_intf_t* intf, 
                       hwcam_user_intf_t* user, 
                       hwcam_buf_info_t* buf); 

    int (*enum_fmt)(hwcam_cfgpipeline_intf_t* intf, 
                    hwcam_user_intf_t* user, 
                    struct v4l2_fmtdesc* fd); 
    int (*query_cap)(hwcam_cfgpipeline_intf_t* intf,
                     hwcam_user_intf_t* user); 
    int (*query_param)(hwcam_cfgpipeline_intf_t* intf, 
                       hwcam_user_intf_t* user); 
    int (*change_param)(hwcam_cfgpipeline_intf_t* intf, 
                        hwcam_user_intf_t* user); 

    hwcam_cfgstream_intf_t* (*mount_stream)(hwcam_cfgpipeline_intf_t* intf, 
                                            hwcam_user_intf_t* user, 
                                            hwcam_stream_info_t* info); 
} hwcam_cfgpipeline_vtbl_t; 

typedef struct _tag_hwcam_cfgpipeline_intf
{
    hwcam_cfgpipeline_vtbl_t const*             vtbl; 
} hwcam_cfgpipeline_intf_t; 

static inline void
hwcam_cfgpipeline_intf_get(hwcam_cfgpipeline_intf_t* intf)
{
    intf->vtbl->get(intf); 
}

static inline int
hwcam_cfgpipeline_intf_put(hwcam_cfgpipeline_intf_t* intf)
{
    return intf->vtbl->put(intf); 
}

static inline int
hwcam_cfgpipeline_intf_umount(hwcam_cfgpipeline_intf_t* intf)
{
    return intf->vtbl->umount(intf); 
}

static inline int 
hwcam_cfgpipeline_intf_mount_buf(hwcam_cfgpipeline_intf_t* intf, 
                                 hwcam_user_intf_t* user,  
                                 hwcam_buf_info_t* buf)
{
    return intf->vtbl->mount_buf(intf, user, buf); 
}

static inline int 
hwcam_cfgpipeline_intf_unmount_buf(hwcam_cfgpipeline_intf_t* intf, 
                                   hwcam_user_intf_t* user,  
                                   hwcam_buf_info_t* buf)
{
    return intf->vtbl->unmount_buf(intf, user, buf); 
}

static inline int
hwcam_cfgpipeline_intf_query_param(hwcam_cfgpipeline_intf_t* intf, 
                                   hwcam_user_intf_t* user)
{
    return intf->vtbl->query_param(intf, user); 
}

static inline int 
hwcam_cfgpipeline_intf_query_cap(hwcam_cfgpipeline_intf_t* intf, 
                                 hwcam_user_intf_t* user)
{
    return intf->vtbl->query_cap(intf, user); 
}

static inline int 
hwcam_cfgpipeline_intf_enum_fmt(hwcam_cfgpipeline_intf_t* intf, 
                                hwcam_user_intf_t* user, 
                                struct v4l2_fmtdesc* fd)
{
    return intf->vtbl->enum_fmt(intf, user, fd); 
}

static inline int
hwcam_cfgpipeline_intf_change_param(hwcam_cfgpipeline_intf_t* intf, 
                                    hwcam_user_intf_t* user)
{
    return intf->vtbl->change_param(intf, user); 
}

static inline hwcam_cfgstream_intf_t*
hwcam_cfgpipeline_intf_mount_stream(hwcam_cfgpipeline_intf_t* intf, 
                                    hwcam_user_intf_t* user, 
                                    hwcam_stream_info_t* info)
{
    return intf->vtbl->mount_stream(intf, user, info); 
}

extern int
hwcam_cfgpipeline_wait_idle(hwcam_dev_intf_t* cam, 
                            int timeout); 

//  hwcam_cfgpipeline interface definition end


////////////////////////////////////////////////////////////////////////////////
//
//          hwcam_cfgstream interface definition begin
//
////////////////////////////////////////////////////////////////////////////////

typedef struct _tag_hwcam_cfgstream_vtbl 
{        
    void (*get)(hwcam_cfgstream_intf_t* intf);
    int (*put)(hwcam_cfgstream_intf_t* intf); 
    int (*umount)(hwcam_cfgstream_intf_t* intf); 

    int (*try_fmt)(hwcam_cfgstream_intf_t* intf, 
                   struct v4l2_format* fmt); 

    int (*mount_buf)(hwcam_cfgstream_intf_t* intf, 
                     hwcam_buf_info_t* buf); 
    int (*unmount_buf)(hwcam_cfgstream_intf_t* intf, 
                       hwcam_buf_info_t* buf); 
    int (*mount_graphic_buf)(hwcam_cfgstream_intf_t* intf, 
                             hwcam_graphic_buf_info_t* buf); 
    int (*unmount_graphic_buf)(hwcam_cfgstream_intf_t* intf, 
                               int index); 
    int (*query_param)(hwcam_cfgstream_intf_t* intf); 
    int (*change_param)(hwcam_cfgstream_intf_t* intf); 

    void (*buf_queue)(hwcam_cfgstream_intf_t* intf, 
                      hwcam_vbuf_t* buf); 

    int (*start)(hwcam_cfgstream_intf_t* intf); 
    int (*stop)(hwcam_cfgstream_intf_t* intf); 
} hwcam_cfgstream_vtbl_t; 

typedef struct _tag_hwcam_cfgstream_intf
{
    hwcam_cfgstream_vtbl_t const*               vtbl; 
} hwcam_cfgstream_intf_t; 

extern hwcam_cfgstream_intf_t*
hwcam_cfgstream_get_by_fd(int fd); 

static inline void
hwcam_cfgstream_intf_get(hwcam_cfgstream_intf_t* intf)
{
    intf->vtbl->get(intf); 
}

static inline int
hwcam_cfgstream_intf_put(hwcam_cfgstream_intf_t* intf)
{
    return intf->vtbl->put(intf); 
}

static inline int
hwcam_cfgstream_intf_umount(hwcam_cfgstream_intf_t* intf)
{
    return intf->vtbl->umount(intf); 
}

static inline int 
hwcam_cfgstream_intf_try_fmt( hwcam_cfgstream_intf_t* intf, 
                              struct v4l2_format* fmt)
{
    return intf->vtbl->try_fmt(intf, fmt); 
}

static inline int 
hwcam_cfgstream_intf_mount_buf(hwcam_cfgstream_intf_t* intf, 
                               hwcam_buf_info_t* buf)
{
    return intf->vtbl->mount_buf(intf, buf); 
}

static inline int 
hwcam_cfgstream_intf_unmount_buf(hwcam_cfgstream_intf_t* intf, 
                                 hwcam_buf_info_t* buf)
{
    return intf->vtbl->unmount_buf(intf, buf); 
}

static inline int 
hwcam_cfgstream_intf_mount_graphic_buf(hwcam_cfgstream_intf_t* intf, 
                                       hwcam_graphic_buf_info_t* buf)
{
    return intf->vtbl->mount_graphic_buf(intf, buf); 
}

static inline int 
hwcam_cfgstream_intf_unmount_graphic_buf(hwcam_cfgstream_intf_t* intf, 
                                         int index)
{
    return intf->vtbl->unmount_graphic_buf(intf, index); 
}

static inline int
hwcam_cfgstream_intf_query_param(hwcam_cfgstream_intf_t* intf)
{
    return intf->vtbl->query_param(intf); 
}

static inline int
hwcam_cfgstream_intf_change_param(hwcam_cfgstream_intf_t* intf)
{
    return intf->vtbl->change_param(intf); 
}

static inline void 
hwcam_cfgstream_intf_buf_queue(hwcam_cfgstream_intf_t* intf, 
                               hwcam_vbuf_t* buf)
{
    return intf->vtbl->buf_queue(intf, buf); 
}

static inline int
hwcam_cfgstream_intf_start(hwcam_cfgstream_intf_t* intf)
{
    return intf->vtbl->start(intf); 
}

static inline int
hwcam_cfgstream_intf_stop(hwcam_cfgstream_intf_t* intf)
{
    return intf->vtbl->stop(intf); 
}

//  hwcam_cfgstream interface definition end

#endif // __HW_ALAN_KERNEL_CAMERA_OBJ_MDL_INTERFACE__ 

