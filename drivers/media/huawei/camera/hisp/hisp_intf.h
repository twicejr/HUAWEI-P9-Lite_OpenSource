

#ifndef __HW_JACKY_KERNEL_HISP_INTERFACE_H__
#define __HW_JACKY_KERNEL_HISP_INTERFACE_H__

#include <linux/rpmsg.h>
#include <linux/platform_device.h>
#include <linux/videodev2.h>
#include <media/huawei/hisp_cfg.h>
#include <media/videobuf2-core.h>
#include <linux/clk.h>

#include "hwcam_intf.h"
#include "cam_log.h"

typedef struct _tag_hisp_vtbl hisp_vtbl_t;
typedef struct _tag_hisp_intf hisp_intf_t;
typedef struct _tag_hisp_notify_intf hisp_notify_intf_t;

#define HISP_WAIT_TIMEOUT	3000

//#define FAKE_FW 1
#undef FAKE_FW
/*define to 1 to disable lightweight runtime debugging checks */
#undef HISP_NDEBUG

#ifdef HISP_NDEBUG
#define hisp_assert(expr) do {} while (0)
#else
#define hisp_assert(expr) {\
	if (unlikely(!(expr))) {				\
		pr_err("Assertion failed! %s, %s,%s,line=%d\n",	\
		       #expr, __FILE__, __func__, __LINE__);	\
	}\
}
#endif

/**
 * hisp dts config info
 */
typedef struct _hisp_dt_data {
	struct clk *aclk;
	struct clk *aclk_dss;
	struct clk *pclk_dss;

	struct pinctrl *pinctrl;
	struct pinctrl_state *pinctrl_default;
	struct pinctrl_state *pinctrl_idle;
} hisp_dt_data_t;

typedef struct _tag_hisp_vtbl {
	char const *(*get_name) (hisp_intf_t *i);
	int (*config) (hisp_intf_t *i, void *cfg);
	int (*power_on) (hisp_intf_t *i);
	int (*power_off) (hisp_intf_t *i);
	int (*send_rpmsg) (hisp_intf_t *i, hisp_msg_t *m, size_t len);
	int (*recv_rpmsg) (hisp_intf_t *i, hisp_msg_t *m, size_t len);
} hisp_vtbl_t;

typedef struct _tag_hisp_intf {
	hisp_vtbl_t *vtbl;
} hisp_intf_t;

typedef struct _tag_hisp_notify_vtbl {
	void (*rpmsg_cb) (hisp_notify_intf_t *i, hisp_event_t *isp_ev);
} hisp_notify_vtbl_t;

typedef struct _tag_hisp_notify_intf {
	hisp_notify_vtbl_t *vtbl;
} hisp_notify_intf_t;

static inline void
hisp_notify_intf_rpmsg_cb(hisp_notify_intf_t *i, hisp_event_t *isp_ev)
{
	if (NULL == i){
		cam_err("func %s: i is NULL",__func__);
		return;
	}
	if (NULL == i->vtbl){
		cam_err("func %s: i->vtbl is NULL",__func__);
		return;
	}
	hisp_assert(NULL != i->vtbl->rpmsg_cb);
	return i->vtbl->rpmsg_cb(i, isp_ev);
}

static inline char  *hisp_intf_get_name(hisp_intf_t *i)
{
	if (NULL == i){
		return NULL;
	}
	if (NULL == i->vtbl){
		return NULL;
	}
	hisp_assert(NULL != i->vtbl->get_name);
	return (char *)i->vtbl->get_name(i);
}
extern int32_t
hisp_register(
	      hisp_intf_t *hw, hisp_notify_intf_t **notify);

extern void
hisp_unregister(hisp_intf_t* isp_intf);
int hisp_get_dt_data(struct platform_device *pdev, hisp_dt_data_t *dt);

#endif /*__HW_JACKY_KERNEL_HISP_INTERFACE_H__ */
