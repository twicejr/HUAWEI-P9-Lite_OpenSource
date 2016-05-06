


#ifndef __HW_ALAN_KERNEL_EXTISP_INTERFACE_H__
#define __HW_ALAN_KERNEL_EXTISP_INTERFACE_H__

#include <linux/videodev2.h>
#include <media/huawei/camera.h>
#include <media/huawei/extisp_cfg.h>
#include <media/videobuf2-core.h>

#include "hwcam_intf.h"

typedef struct _tag_hwextisp_notify_vtbl hwextisp_notify_vtbl_t;
typedef struct _tag_hwextisp_notify_intf hwextisp_notify_intf_t;

typedef struct _tag_hwextisp_notify_vtbl
{
    void (*cmd_finish)(hwextisp_notify_intf_t* i, hwextisp_event_t* extisp_ev);
    void (*error)(hwextisp_notify_intf_t* i, hwextisp_event_t* extisp_ev);
    void (*dump)(hwextisp_notify_intf_t* i, hwextisp_event_t* extisp_ev);
} hwextisp_notify_vtbl_t;

typedef struct _tag_hwextisp_notify_intf
{
    hwextisp_notify_vtbl_t*                        vtbl;
} hwextisp_notify_intf_t;


typedef struct _tag_hwextisp_vtbl hwextisp_vtbl_t;
typedef struct _tag_hwextisp_intf hwextisp_intf_t;

typedef struct _tag_hwextisp_vtbl
{
    char const* (*get_name)(const hwextisp_intf_t* i);
    int (*power_on)(const hwextisp_intf_t* i);
    int (*power_off)(const hwextisp_intf_t* i);
    int (*reset)(const hwextisp_intf_t* i);
    int (*load_firmware)(const hwextisp_intf_t* i, hwextisp_config_data_t *data);
    int (*init_reg)(const hwextisp_intf_t* i);
    int (*exec_cmd)(const hwextisp_intf_t* i, hwextisp_config_data_t *data);
	int (*matchid)(const hwextisp_intf_t* i, hwextisp_config_data_t *data);
    int (*mini_isp_get_dt_data) (const hwextisp_intf_t *, struct device_node *);
    int (*mini_isp_register_attribute)(const hwextisp_intf_t *, struct device *);

} hwextisp_vtbl_t;

typedef struct _tag_hwextisp_intf
{
    hwextisp_vtbl_t*                            vtbl;
} hwextisp_intf_t;

static inline char const*
hwextisp_intf_get_name(const hwextisp_intf_t* i)
{
    return i->vtbl->get_name(i);
}

static inline int
hwextisp_intf_power_on(const hwextisp_intf_t* i)
{
    return i->vtbl->power_on(i);
}

static inline int
hwextisp_intf_power_off(const hwextisp_intf_t* i)
{
    return i->vtbl->power_off(i);
}

static inline int
hwextisp_intf_reset(const hwextisp_intf_t* i)
{
    return i->vtbl->reset(i);
}

static inline int
hwextisp_intf_load_firmware(const hwextisp_intf_t* i, hwextisp_config_data_t *data)
{
    return i->vtbl->load_firmware(i, data);
}

static inline void
hwextisp_intf_notify_cmd_finish(hwextisp_notify_intf_t* i, hwextisp_event_t* extisp_ev)
{
    return i->vtbl->cmd_finish(i,extisp_ev);
}

static inline void
hwextisp_intf_notify_error(hwextisp_notify_intf_t* i, hwextisp_event_t* extisp_ev)
{
    return i->vtbl->error(i,extisp_ev);
}

static inline void
hwextisp_intf_notify_dump(hwextisp_notify_intf_t* i, hwextisp_event_t* extisp_ev)
{
    return i->vtbl->dump(i,extisp_ev);
}

extern int32_t hwextisp_register(struct platform_device* pdev, const hwextisp_intf_t* i,hwextisp_notify_intf_t** notify);

#endif // __HW_ALAN_KERNEL_EXTISP_INTERFACE_H__
