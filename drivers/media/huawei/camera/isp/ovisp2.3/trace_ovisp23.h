#undef TRACE_SYSTEM
#define TRACE_SYSTEM hwisp

#if !defined(__TRACE_OVISP23_H__) || defined(TRACE_HEADER_MULTI_READ)
#define __TRACE_OVISP23_H__

#include <linux/tracepoint.h>
#include <media/huawei/camera.h>
#include <media/huawei/isp_cfg.h>
#include <media/huawei/extisp_cfg.h>
#include "isp_ops.h" 

TRACE_EVENT(hw_ovisp23_irq_handler_entry,/* [false alarm]:will not cause error */

	TP_PROTO(struct irq_reg_t* reg),

	TP_ARGS(reg),

	TP_STRUCT__entry(
        __field(uint8_t,    mac1_s0);
        __field(uint8_t,    mac1_s1);
        __field(uint8_t,    mac2_s0);
        __field(uint8_t,    mac2_s1);
	),

	TP_fast_assign(
		__entry->mac1_s0    = reg->mac1_irq_status_s0;
		__entry->mac1_s1    = reg->mac1_irq_status_s1;
		__entry->mac2_s0    = reg->mac2_irq_status_s0;
		__entry->mac2_s1    = reg->mac2_irq_status_s1;
	),

	TP_printk("mac1_s0=0x%02x mac1_s1=0x%02x mac2_s0=0x%02x mac2_s1=0x%02x", 
              __entry->mac1_s0, __entry->mac1_s1, __entry->mac2_s0, __entry->mac2_s1)
);

DECLARE_EVENT_CLASS(hw_ovisp23_write_internel,/* [false alarm]:will not cause error */

	TP_PROTO(uint32_t port),

	TP_ARGS(port),

	TP_STRUCT__entry(
		__field(uint32_t,   port)
	),

	TP_fast_assign(
		__entry->port       = port;
	),

	TP_printk("port=%d", __entry->port)
);

DEFINE_EVENT(hw_ovisp23_write_internel, hw_ovisp23_write_start,

	TP_PROTO(uint32_t port),

	TP_ARGS(port)
);

DEFINE_EVENT(hw_ovisp23_write_internel, hw_ovisp23_write_done,

	TP_PROTO(uint32_t port),

	TP_ARGS(port)
);

DEFINE_EVENT(hw_ovisp23_write_internel, hw_ovisp23_write_drop,

	TP_PROTO(uint32_t port),

	TP_ARGS(port)
);

DEFINE_EVENT(hw_ovisp23_write_internel, hw_ovisp23_write_overflow,

	TP_PROTO(uint32_t port),

	TP_ARGS(port)
);

TRACE_EVENT(hw_ovisp23_cmd_ready,/* [false alarm]:will not cause error */

	TP_PROTO(uint32_t cmd, uint32_t result),

	TP_ARGS(cmd, result),

	TP_STRUCT__entry(
        __field(uint32_t,   cmd);
        __field(uint32_t,   result);
	),

	TP_fast_assign(
		__entry->cmd        = cmd;
		__entry->result     = result;
	),

	TP_printk("cmd=%d result=%d", 
              __entry->cmd, __entry->result)
);

DECLARE_EVENT_CLASS(hw_ovisp23_event_internel,/* [false alarm]:will not cause error */

	TP_PROTO(uint32_t pipeline),

	TP_ARGS(pipeline),

	TP_STRUCT__entry(
		__field(uint32_t,	pipeline)
	),

	TP_fast_assign(
		__entry->pipeline   = pipeline;
	),

    TP_printk("pipeline=%d", __entry->pipeline)
);

DEFINE_EVENT(hw_ovisp23_event_internel, hw_ovisp23_event_sof,

	TP_PROTO(uint32_t pipeline),

	TP_ARGS(pipeline)
);

DEFINE_EVENT(hw_ovisp23_event_internel, hw_ovisp23_event_eof,

	TP_PROTO(uint32_t pipeline),

	TP_ARGS(pipeline)
);

#endif /*  __TRACE_OVISP23_H__ */

/* This part must be outside protection */
#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH .
#define TRACE_INCLUDE_FILE trace_ovisp23
#include <trace/define_trace.h>

