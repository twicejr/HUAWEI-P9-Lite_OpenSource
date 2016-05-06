/*board internal declare */
#ifndef __MACH_K3V2_BOARD_H
#define __MACH_K3V2_BOARD_H

#include <linux/types.h>
#include <asm/mach/time.h>
#include <linux/proc_fs.h>
#include <mach/clock.h>

extern struct sys_timer board_timer;

void __init plat_clk_reg(void);
void __init plat_clk_init_from_table(struct clk_init_table *table);

#endif

