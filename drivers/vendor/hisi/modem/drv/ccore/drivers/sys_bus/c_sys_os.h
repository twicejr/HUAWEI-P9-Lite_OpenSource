#ifndef __C_SYS_OS_H__
#define __C_SYS_OS_H__

#include <osl_types.h>
#include <c_sys_bus_pressure.h>

/*½á¹¹Ìå*/
struct sys_os_hwi{
    u32 int_num;
    u32 spend_time;
    u32 maxtime;
    u64 total_time;
    u32 count;
};
struct sys_os_task{
    char *name;
    u32 pid;
    u32 spend_time;
    u32 maxtime;
    u64 total_utime;
    u64 total_mtime;
    u32 count;
};

/*api*/
void sys_os_start(struct master* master);
void sys_os_stop(struct master* master);
void sys_os_report(struct master* master);
#endif
