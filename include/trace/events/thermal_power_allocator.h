#undef TRACE_SYSTEM
#define TRACE_SYSTEM thermal_power_allocator

#if !defined(_TRACE_THERMAL_POWER_ALLOCATOR_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_THERMAL_POWER_ALLOCATOR_H

#include <linux/tracepoint.h>

TRACE_EVENT(thermal_power_allocator,
	TP_PROTO(struct thermal_zone_device *tz, u32 *req_power,
		 u32 total_req_power, u32 *granted_power,
		 u32 total_granted_power, size_t num_actors,
		 u32 power_range, u32 max_allocatable_power,
		 unsigned long current_temp, s32 delta_temp),
	TP_ARGS(tz, req_power, total_req_power, granted_power,
		total_granted_power, num_actors, power_range,
		max_allocatable_power, current_temp, delta_temp),
	TP_STRUCT__entry(
		__field(int,           tz_id          )
		__dynamic_array(u32,   req_power, num_actors    )
		__field(u32,           total_req_power          )
		__dynamic_array(u32,   granted_power, num_actors)
		__field(u32,           total_granted_power      )
		__field(size_t,        num_actors               )
		__field(u32,           power_range              )
		__field(u32,           max_allocatable_power    )
		__field(unsigned long, current_temp             )
		__field(s32,           delta_temp               )
	),
	TP_fast_assign(
		__entry->tz_id = tz->id;
		memcpy(__get_dynamic_array(req_power), req_power,
			num_actors * sizeof(*req_power));
		__entry->total_req_power = total_req_power;
		memcpy(__get_dynamic_array(granted_power), granted_power,
			num_actors * sizeof(*granted_power));
		__entry->total_granted_power = total_granted_power;
		__entry->num_actors = num_actors;
		__entry->power_range = power_range;
		__entry->max_allocatable_power = max_allocatable_power;
		__entry->current_temp = current_temp;
		__entry->delta_temp = delta_temp;
	),

	TP_printk("thermal_zone_id=%d req_power={%s} total_req_power=%u granted_power={%s} total_granted_power=%u power_range=%u max_allocatable_power=%u current_temperature=%lu delta_temperature=%d",
		__entry->tz_id,
		__print_array(__get_dynamic_array(req_power),
                              __entry->num_actors, 4),
		__entry->total_req_power,
		__print_array(__get_dynamic_array(granted_power),
                              __entry->num_actors, 4),
		__entry->total_granted_power, __entry->power_range,
		__entry->max_allocatable_power, __entry->current_temp,
		__entry->delta_temp)
);/* [false alarm]:fortify */

TRACE_EVENT(thermal_power_allocator_pid,
	TP_PROTO(struct thermal_zone_device *tz, s32 err, s32 err_integral,
		 s64 p, s64 i, s64 d, s32 output),
	TP_ARGS(tz, err, err_integral, p, i, d, output),
	TP_STRUCT__entry(
		__field(int, tz_id       )
		__field(s32, err         )
		__field(s32, err_integral)
		__field(s64, p           )
		__field(s64, i           )
		__field(s64, d           )
		__field(s32, output      )
	),
	TP_fast_assign(
		__entry->tz_id = tz->id;
		__entry->err = err;
		__entry->err_integral = err_integral;
		__entry->p = p;
		__entry->i = i;
		__entry->d = d;
		__entry->output = output;
	),

	TP_printk("thermal_zone_id=%d err=%d err_integral=%d p=%lld i=%lld d=%lld output=%d",
		  __entry->tz_id, __entry->err, __entry->err_integral,
		  __entry->p, __entry->i, __entry->d, __entry->output)
);/* [false alarm]:fortify */

TRACE_EVENT(thermal_power_actor_cpu_limit,
	TP_PROTO(const struct cpumask *cpus, unsigned int freq,
		unsigned long cdev_state, u32 power),

	TP_ARGS(cpus, freq, cdev_state, power),

	TP_STRUCT__entry(
		__bitmask(cpumask, num_possible_cpus())
		__field(unsigned int,  freq      )
		__field(unsigned long, cdev_state)
		__field(u32,           power     )
	),

	TP_fast_assign(
		__assign_bitmask(cpumask, cpumask_bits(cpus),
				num_possible_cpus());
		__entry->freq = freq;
		__entry->cdev_state = cdev_state;
		__entry->power = power;
	),

	TP_printk("cpus=%s freq=%u cdev_state=%lu power=%u",
		__get_bitmask(cpumask), __entry->freq, __entry->cdev_state,
		__entry->power)
); /* [false alarm]:fortify */

TRACE_EVENT(thermal_power_actor_gpu_get_power,
	TP_PROTO(unsigned long freq, unsigned long load,
		 unsigned long dynamic_power, unsigned long static_power, unsigned long req_power),

	TP_ARGS(freq, load, dynamic_power, static_power, req_power),

	TP_STRUCT__entry(
		__field(unsigned long, freq          )
		__field(unsigned long, load          )
		__field(unsigned long, dynamic_power )
		__field(unsigned long, static_power  )
		__field(unsigned long, req_power  )
	),

	TP_fast_assign(
		__entry->freq = freq;
		__entry->load = load;
		__entry->dynamic_power = dynamic_power;
		__entry->static_power = static_power;
		__entry->req_power = req_power;
	),

	TP_printk("gpu freq=%lu load=%d% dynamic_power=%d static_power=%d req_power=%d",
		 __entry->freq, __entry->load,
		 __entry->dynamic_power, __entry->static_power, __entry->req_power)
);/* [false alarm]:fortify */

TRACE_EVENT(IPA_allocator,
	TP_PROTO(unsigned long current_temp, unsigned long control_temp, unsigned long switch_temp, s32 delta_temp,
	         u32 num_actors,
	         u32 power_range,
	         u32 *req_power, u32 total_req_power,
	         u32 *max_power, u32 max_allocatable_power,
	         u32 *granted_power, u32 total_granted_power
		),
	TP_ARGS(current_temp, control_temp, switch_temp, delta_temp, num_actors,
	        power_range,
	        req_power, total_req_power,
	        max_power, max_allocatable_power,
	        granted_power, total_granted_power
		),
	TP_STRUCT__entry(
	        __field(unsigned long, current_temp             )
	        __field(unsigned long, control_temp             )
	        __field(unsigned long, switch_temp             )
		__field(s32,           delta_temp               )
		__field(u32,           num_actors               )
		__field(u32,           power_range              )
		__dynamic_array(u32,   req_power, num_actors    )
		__field(u32,           total_req_power          )
		__dynamic_array(u32,   granted_power, num_actors)
		__field(u32,           total_granted_power      )
		__dynamic_array(u32,   max_power, num_actors    )
		__field(u32,           max_allocatable_power    )

	),
	TP_fast_assign(
	        __entry->current_temp = current_temp;
	        __entry->control_temp = control_temp;
	        __entry->switch_temp = switch_temp;
		__entry->delta_temp = delta_temp;
		__entry->num_actors = num_actors;
		__entry->power_range = power_range;
		memcpy(__get_dynamic_array(req_power), req_power,
			num_actors * sizeof(*req_power));
		__entry->total_req_power = total_req_power;
		memcpy(__get_dynamic_array(granted_power), granted_power,
			num_actors * sizeof(*granted_power));
		__entry->total_granted_power = total_granted_power;
		memcpy(__get_dynamic_array(max_power), max_power,
			num_actors * sizeof(*max_power));
		__entry->max_allocatable_power = max_allocatable_power;
	),

	TP_printk("%lu,%lu,%lu,%d,%u,%s,%u,%s,%u,%s,%u",
	        __entry->current_temp,__entry->control_temp,__entry->switch_temp,
	        __entry->delta_temp,
	        __entry->power_range,
		__print_u32_array(__get_dynamic_array(req_power),__entry->num_actors),
		__entry->total_req_power,
		__print_u32_array(__get_dynamic_array(max_power),__entry->num_actors),
		__entry->max_allocatable_power,
		__print_u32_array(__get_dynamic_array(granted_power),__entry->num_actors),
		__entry->total_granted_power
		)

);/* [false alarm]:fortify */

TRACE_EVENT(IPA_allocator_pid,
	TP_PROTO(s32 err, s32 err_integral, s64 p, s64 i, s64 d, s32 output),
	TP_ARGS(err, err_integral, p, i, d, output),
	TP_STRUCT__entry(
		__field(s32, err         )
		__field(s32, err_integral)
		__field(s64, p           )
		__field(s64, i           )
		__field(s64, d           )
		__field(s32, output      )
	),
	TP_fast_assign(
		__entry->err = err;
		__entry->err_integral = err_integral;
		__entry->p = p;
		__entry->i = i;
		__entry->d = d;
		__entry->output = output;
	),

	TP_printk("%d,%d,%lld,%lld,%lld,%d",
		__entry->err, __entry->err_integral,
		__entry->p, __entry->i, __entry->d, __entry->output)
);/* [false alarm]:fortify */

TRACE_EVENT(IPA_actor_cpu_get_power,
	TP_PROTO(const struct cpumask *cpus, unsigned long freq, u32 *load,
		size_t load_len, u32 dynamic_power, u32 static_power, u32 req_power),

	TP_ARGS(cpus, freq, load, load_len, dynamic_power, static_power, req_power),

	TP_STRUCT__entry(
		__bitmask(cpumask, num_possible_cpus())
		__field(unsigned long, freq          )
		__dynamic_array(u32,   load, load_len)
		__field(size_t,        load_len      )
		__field(u32,           dynamic_power )
		__field(u32,           static_power  )
		__field(u32,           req_power     )
	),

	TP_fast_assign(
		__assign_bitmask(cpumask, cpumask_bits(cpus),
				num_possible_cpus());
		__entry->freq = freq;
		memcpy(__get_dynamic_array(load), load,
			load_len * sizeof(*load));
		__entry->load_len = load_len;
		__entry->dynamic_power = dynamic_power;
		__entry->static_power = static_power;
		__entry->req_power = req_power;
	),

	TP_printk("%s,%lu,%s,%u,%u,%u",
		__get_bitmask(cpumask),
		__entry->freq,
		__print_u32_array(__get_dynamic_array(load), __entry->load_len),
		__entry->dynamic_power,
		__entry->static_power,
		__entry->req_power)
);/* [false alarm]:fortify */

TRACE_EVENT(IPA_actor_cpu_limit,
	TP_PROTO(const struct cpumask *cpus, unsigned int freq,
		unsigned long cdev_state, u32 power),

	TP_ARGS(cpus, freq, cdev_state, power),

	TP_STRUCT__entry(
		__bitmask(cpumask, num_possible_cpus())
		__field(unsigned int,  freq      )
		__field(unsigned long, cdev_state)
		__field(u32,           power     )
	),

	TP_fast_assign(
		__assign_bitmask(cpumask, cpumask_bits(cpus),
				num_possible_cpus());
		__entry->freq = freq;
		__entry->cdev_state = cdev_state;
		__entry->power = power;
	),

	TP_printk("%s,%u,%lu,%u",
		__get_bitmask(cpumask), __entry->freq, __entry->cdev_state,
		__entry->power)
); /* [false alarm]:fortify */

TRACE_EVENT(IPA_actor_cpu_cooling,
	TP_PROTO(const struct cpumask *cpus, unsigned int freq,
		unsigned long cdev_state),

	TP_ARGS(cpus, freq, cdev_state),

	TP_STRUCT__entry(
		__bitmask(cpumask, num_possible_cpus())
		__field(unsigned int,  freq      )
		__field(unsigned long, cdev_state)
	),

	TP_fast_assign(
		__assign_bitmask(cpumask, cpumask_bits(cpus),
				num_possible_cpus());
		__entry->freq = freq;
		__entry->cdev_state = cdev_state;
	),

	TP_printk("%s,%u,%lu",
		__get_bitmask(cpumask), __entry->freq, __entry->cdev_state)
); /* [false alarm]:fortify */

TRACE_EVENT(IPA_actor_gpu_limit,
	TP_PROTO(unsigned long freq, unsigned long cdev_state, u32 power),

	TP_ARGS(freq, cdev_state, power),

	TP_STRUCT__entry(
		__field(unsigned long,  freq      )
		__field(unsigned long, cdev_state)
		__field(u32,           power     )
	),

	TP_fast_assign(
		__entry->freq = freq;
		__entry->cdev_state = cdev_state;
		__entry->power = power;
	),

	TP_printk("%lu,%lu,%u",
		__entry->freq, __entry->cdev_state,
		__entry->power)
);/* [false alarm]:fortify */

TRACE_EVENT(IPA_actor_gpu_cooling,
	TP_PROTO(unsigned long freq, unsigned long cdev_state),

	TP_ARGS(freq, cdev_state),

	TP_STRUCT__entry(
		__field(unsigned long,  freq      )
		__field(unsigned long, cdev_state)
	),

	TP_fast_assign(
		__entry->freq = freq;
		__entry->cdev_state = cdev_state;
	),

	TP_printk("%lu,%lu",
		__entry->freq, __entry->cdev_state)
);/* [false alarm]:fortify */

TRACE_EVENT(IPA_actor_gpu_get_power,
	TP_PROTO(unsigned long freq, unsigned long load,
		 unsigned long dynamic_power, unsigned long static_power, unsigned long req_power),

	TP_ARGS(freq, load, dynamic_power, static_power, req_power),

	TP_STRUCT__entry(
		__field(unsigned long, freq          )
		__field(unsigned long, load          )
		__field(unsigned long, dynamic_power )
		__field(unsigned long, static_power  )
		__field(unsigned long, req_power  )
	),

	TP_fast_assign(
		__entry->freq = freq;
		__entry->load = load;
		__entry->dynamic_power = dynamic_power;
		__entry->static_power = static_power;
		__entry->req_power = req_power;
	),

	TP_printk("%lu,%lu,%lu,%lu,%lu",
		 __entry->freq, __entry->load,
		 __entry->dynamic_power, __entry->static_power, __entry->req_power)
);/* [false alarm]:fortify */


TRACE_EVENT(IPA_get_tsens_value,
	TP_PROTO(unsigned long tsens_value0, unsigned long tsens_value1, unsigned long tsens_value2,
	         unsigned long tsens_value_max),

	TP_ARGS(tsens_value0, tsens_value1, tsens_value2, tsens_value_max),

	TP_STRUCT__entry(
		__field(unsigned long, tsens_value0   )
		__field(unsigned long, tsens_value1   )
		__field(unsigned long, tsens_value2   )
		__field(unsigned long, tsens_value_max)
	),

	TP_fast_assign(
		__entry->tsens_value0 = tsens_value0;
		__entry->tsens_value1 = tsens_value1;
		__entry->tsens_value2 = tsens_value2;
		__entry->tsens_value_max = tsens_value_max;
	),

	TP_printk("%lu,%lu,%lu,%lu",
		 __entry->tsens_value0, __entry->tsens_value1, __entry->tsens_value2,
		 __entry->tsens_value_max)
); /* [false alarm]:fortify */


#endif /* _TRACE_THERMAL_POWER_ALLOCATOR_H */

/* This part must be outside protection */
#include <trace/define_trace.h>
