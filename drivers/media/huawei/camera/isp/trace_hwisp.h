#undef TRACE_SYSTEM
#define TRACE_SYSTEM hwisp

#if !defined(__TRACE_HWISP_H__) || defined(TRACE_HEADER_MULTI_READ)
#define __TRACE_HWISP_H__

#include <linux/tracepoint.h>
#include <media/huawei/camera.h>
#include <media/huawei/isp_cfg.h>
#include <media/huawei/extisp_cfg.h>
#include "hwisp_intf.h" 

DECLARE_EVENT_CLASS(hwisp_stream_buf_internel,/* [false alarm]:will not cause error */

	TP_PROTO(hwisp_buf_t* buf),

	TP_ARGS(buf),

	TP_STRUCT__entry(
		__field(uint32_t,	pixfmt)
		__field(uint8_t,	phy)
		__field(void*,	    handle)
        __field(uint32_t,   y_addr)
        __field(uint32_t,   u_addr)
        __field(uint32_t,   v_addr)
	),

	TP_fast_assign(
		__entry->pixfmt		= buf->info.port.pix_format;
		__entry->phy        = buf->info.port.use_phy_memory;
		__entry->handle     = buf->info.user_buffer_handle;
        __entry->y_addr     = buf->info.port.use_phy_memory
                            ? buf->info.y_addr_phy
                            : buf->info.y_addr_iommu;
        __entry->u_addr     = buf->info.port.use_phy_memory
                            ? buf->info.u_addr_phy
                            : buf->info.u_addr_iommu;
        __entry->v_addr     = buf->info.port.use_phy_memory
                            ? buf->info.v_addr_phy
                            : buf->info.v_addr_iommu;
	),

    TP_printk("pixfmt=%d phy=%d "
              "handle=0x%p y_addr=0x%x u_addr=0x%x v_addr=0x%x",
              __entry->pixfmt, __entry->phy, 
              __entry->handle, __entry->y_addr, __entry->u_addr, __entry->v_addr)
);

DEFINE_EVENT(hwisp_stream_buf_internel, hwisp_stream_buf_get,

	TP_PROTO(hwisp_buf_t* buf),

	TP_ARGS(buf)
);

DEFINE_EVENT(hwisp_stream_buf_internel, hwisp_stream_buf_put,

	TP_PROTO(hwisp_buf_t* buf),

	TP_ARGS(buf)
);

DEFINE_EVENT(hwisp_stream_buf_internel, hwisp_stream_buf_done,

	TP_PROTO(hwisp_buf_t* buf),

	TP_ARGS(buf)
);

#endif /*  __TRACE_HWISP_H__ */

/* This part must be outside protection */
#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH .
#define TRACE_INCLUDE_FILE trace_hwisp
#include <trace/define_trace.h>

