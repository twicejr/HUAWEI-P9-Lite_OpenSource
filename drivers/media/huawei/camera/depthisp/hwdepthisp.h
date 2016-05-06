


#ifndef __HW_ALAN_KERNEL_DEPTHISP_INTERFACE_H__
#define __HW_ALAN_KERNEL_DEPTHISP_INTERFACE_H__

#include <linux/videodev2.h>
#include <media/huawei/camera.h>
#include <media/huawei/depthisp_cfg.h>
#include <media/videobuf2-core.h>

#include "hwcam_intf.h"

typedef struct _tag_hwdepthisp_notify_vtbl hwdepthisp_notify_vtbl_t;
typedef struct _tag_hwdepthisp_notify_intf hwdepthisp_notify_intf_t;

typedef struct _tag_hwdepthisp_notify_vtbl
{
    void (*cmd_finish)(hwdepthisp_notify_intf_t* i, hwdepthisp_event_t* extisp_ev);
    void (*error)(hwdepthisp_notify_intf_t* i, hwdepthisp_event_t* extisp_ev);
    void (*dump)(hwdepthisp_notify_intf_t* i, hwdepthisp_event_t* extisp_ev);
} hwdepthisp_notify_vtbl_t;

typedef struct _tag_hwdepthisp_notify_intf
{
    hwdepthisp_notify_vtbl_t*                        vtbl;
} hwdepthisp_notify_intf_t;


typedef struct _tag_hwdepthisp_vtbl hwdepthisp_vtbl_t;
typedef struct _tag_hwdepthisp_intf hwdepthisp_intf_t;

typedef struct _tag_hwdepthisp_vtbl
{
    char const* (*get_name)(const hwdepthisp_intf_t* i);
    int (*power_on)(const hwdepthisp_intf_t* i);
    int (*power_off)(const hwdepthisp_intf_t* i);
    int (*reset)(const hwdepthisp_intf_t* i);
    int (*load_firmware)(const hwdepthisp_intf_t* i, hwdepthisp_config_data_t *data);
    int (*init_reg)(const hwdepthisp_intf_t* i);
    int (*exec_cmd)(const hwdepthisp_intf_t* i, hwdepthisp_config_data_t *data);
	int (*matchid)(const hwdepthisp_intf_t* i, hwdepthisp_config_data_t *data);
    int (*depth_isp_get_dt_data) (const hwdepthisp_intf_t *, struct device_node *);
    int (*depth_isp_register_attribute)(const hwdepthisp_intf_t *, struct device *);

} hwdepthisp_vtbl_t;

typedef struct _tag_hwdepthisp_intf
{
    hwdepthisp_vtbl_t*                            vtbl;
} hwdepthisp_intf_t;

static inline char const*
hwdepthisp_intf_get_name(const hwdepthisp_intf_t* i)
{
    return i->vtbl->get_name(i);
}

static inline int
hwdepthisp_intf_power_on(const hwdepthisp_intf_t* i)
{
    return i->vtbl->power_on(i);
}

static inline int
hwdepthisp_intf_power_off(const hwdepthisp_intf_t* i)
{
    return i->vtbl->power_off(i);
}

static inline int
hwdepthisp_intf_reset(const hwdepthisp_intf_t* i)
{
    return i->vtbl->reset(i);
}

static inline int
hwdepthisp_intf_load_firmware(const hwdepthisp_intf_t* i, hwdepthisp_config_data_t *data)
{
    return i->vtbl->load_firmware(i, data);
}

static inline void
hwdepthisp_intf_notify_cmd_finish(hwdepthisp_notify_intf_t* i, hwdepthisp_event_t* extisp_ev)
{
    return i->vtbl->cmd_finish(i,extisp_ev);
}

static inline void
hwdepthisp_intf_notify_error(hwdepthisp_notify_intf_t* i, hwdepthisp_event_t* extisp_ev)
{
    return i->vtbl->error(i,extisp_ev);
}

static inline void
hwdepthisp_intf_notify_dump(hwdepthisp_notify_intf_t* i, hwdepthisp_event_t* extisp_ev)
{
    return i->vtbl->dump(i,extisp_ev);
}

extern int32_t hwdepthisp_register(struct platform_device* pdev, const hwdepthisp_intf_t* i,hwdepthisp_notify_intf_t** notify);

#endif // __HW_ALAN_KERNEL_EXTISP_INTERFACE_H__
