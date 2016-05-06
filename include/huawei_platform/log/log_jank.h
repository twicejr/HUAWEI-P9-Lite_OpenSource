#ifndef __LINUX_LOG_JANK_H__
#define __LINUX_LOG_JANK_H__

#include <huawei_platform/log/janklogconstants.h>

#define LOG_JANK_FS "/dev/hwlog_jank"

#define JANK_LOG_PRIO_VERBOSE  (2)
#define JANK_LOG_PRIO_DEBUG (3)
#define JANK_LOG_PRIO_INFO (4)
#define JANK_LOG_PRIO_WARN (5)
#define JANK_LOG_PRIO_ERROR (6)


#if defined (CONFIG_LOG_JANK)
int log_to_jank(int tag, int prio,const char* fmt, ...);

//for the forward compatibility ,JANK_LOG_PRIO_DEBUG level is just for jank service.
//and the interface name stay the same "pr_jank"
//use LOG_JANK_W LOG_JANK_V  LOG_JANK_I   LOG_JANK_E  for other purpose
#ifndef pr_jank
#define pr_jank(tag, fmt, ...) log_to_jank(tag,JANK_LOG_PRIO_DEBUG,fmt,##__VA_ARGS__)
#endif

#ifndef LOG_JANK_D
#define LOG_JANK_D(tag, fmt, ...) log_to_jank(tag,JANK_LOG_PRIO_DEBUG,fmt,##__VA_ARGS__)
#endif

#ifndef LOG_JANK_W
#define LOG_JANK_W(tag, fmt, ...) log_to_jank(tag,JANK_LOG_PRIO_WARN,fmt,##__VA_ARGS__)
#endif

#ifndef LOG_JANK_V
#define LOG_JANK_V(tag, fmt, ...) log_to_jank(tag,JANK_LOG_PRIO_VERBOSE,fmt,##__VA_ARGS__)
#endif

#ifndef LOG_JANK_I
#define LOG_JANK_I(tag, fmt, ...) log_to_jank(tag,JANK_LOG_PRIO_INFO,fmt,##__VA_ARGS__)
#endif

#ifndef LOG_JANK_E
#define LOG_JANK_E(tag, fmt, ...) log_to_jank(tag,JANK_LOG_PRIO_ERROR,fmt,##__VA_ARGS__)
#endif

#else
#define pr_jank(tag, fmt, ...)	(-ENOENT)
#define LOG_JANK_D(tag, fmt, ...)	(-ENOENT)
#define LOG_JANK_W(tag, fmt, ...)	(-ENOENT)
#define LOG_JANK_V(tag, fmt, ...)	(-ENOENT)
#define LOG_JANK_I(tag, fmt, ...)	(-ENOENT)
#define LOG_JANK_E(tag, fmt, ...)	(-ENOENT)
#endif

#endif
