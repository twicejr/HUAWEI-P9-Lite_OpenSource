#ifndef __MACH_K3V2_BOARD_H
#define __MACH_K3V2_BOARD_H

#include <linux/types.h>

void __init k3v2_common_init(void);
void __init k3v2_map_common_io(void);
void __init k3v2_init_irq(void);
void __init k3v2_init_clock(void);

extern struct sys_timer k3v2_timer;
#endif

