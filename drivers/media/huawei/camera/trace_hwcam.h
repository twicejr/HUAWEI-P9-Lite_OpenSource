#undef TRACE_SYSTEM
#define TRACE_SYSTEM hwcamcfgdrv

#if !defined(__TRACE_HWCAM_H__) || defined(TRACE_HEADER_MULTI_READ)
#define __TRACE_HWCAM_H__

#include <linux/tracepoint.h>
#include <media/huawei/camera.h>
#include <media/huawei/isp_cfg.h>
#include <media/huawei/extisp_cfg.h>

DECLARE_EVENT_CLASS(hwcam_cfgdev_req_internel,/* [false alarm]:will not cause error */

	TP_PROTO(hwcam_cfgreq_t* req),

	TP_ARGS(req),

	TP_STRUCT__entry(
		__field(uint32_t,	kind)
		__field(uint32_t,	seq)
	),

	TP_fast_assign(
		__entry->kind		= (*(uint32_t*)(req + 1));
		__entry->seq		= req->seq;
	),

	TP_printk("kind=0x%x seq=%d",
		  __entry->kind, __entry->seq)
);

DEFINE_EVENT(hwcam_cfgdev_req_internel, hwcam_cfgdev_send_req_begin,

	TP_PROTO(hwcam_cfgreq_t* req),

	TP_ARGS(req)
);

DEFINE_EVENT(hwcam_cfgdev_req_internel, hwcam_cfgdev_send_req_end,

	TP_PROTO(hwcam_cfgreq_t* req),

	TP_ARGS(req)
);

#endif /*  __TRACE_HWCAM_H__ */

/* This part must be outside protection */
#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH .
#define TRACE_INCLUDE_FILE trace_hwcam
#include <trace/define_trace.h>

