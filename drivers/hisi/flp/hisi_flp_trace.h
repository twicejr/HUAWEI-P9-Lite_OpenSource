#if !defined(_HISI_FLP_TRACE_H_) || defined(TRACE_HEADER_MULTI_READ)
#define _DRM_TRACE_H_

#include <linux/stringify.h>
#include <linux/types.h>
#include <linux/tracepoint.h>

#undef TRACE_SYSTEM
#define TRACE_SYSTEM hisi_flp
#define TRACE_SYSTEM_STRING __stringify(TRACE_SYSTEM)
#define TRACE_INCLUDE_FILE hisi_flp_trace

TRACE_EVENT(flp_pdr_event, /* [false alarm]:ftrace_raw_output_flp_pdr_event */
	    TP_PROTO(int x,  int y),
	    TP_ARGS(x, y),
	    TP_STRUCT__entry(
		    __field(int, x)
		    __field(int, y)
		    ),
	    TP_fast_assign(
		    __entry->x = x;
		    __entry->y = y;
		    ),
	    TP_printk("PDRDATA %d:%d", __entry->x, __entry->y)
);
TRACE_EVENT(flp_ar_event,
	    TP_PROTO(unsigned int x,  unsigned int y),
	    TP_ARGS(x, y),
	    TP_STRUCT__entry(
		    __field(unsigned int, x)
		    __field(unsigned int, y)
		    ),
	    TP_fast_assign(
		    __entry->x = x;
		    __entry->y = y;
		    ),
	    TP_printk("ARDATA %d:%d", __entry->x, __entry->y)
); /* [false alarm]:fortify */
#endif /* _HISI_FLP_TRACE_H_ */

/* This part must be outside protection */
#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH .
#include <trace/define_trace.h>
