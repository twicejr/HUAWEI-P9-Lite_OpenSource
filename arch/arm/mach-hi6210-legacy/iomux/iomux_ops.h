#ifndef __MACH_IOMUX_OPS_H
#define __MACH_IOMUX_OPS_H

#include "iomux.h"

int mach_pinmux_func(struct iomux_pin *pin, enum lowlayer_func pin_func);

int mach_pinmux_setpullupdown(struct iomux_pin *pin,
		enum pull_updown pin_pull_updown);


int mach_pinmux_setdrivestrength(struct iomux_pin *pin,
	enum drive_strength pin_drive_strength);


int mach_block_setfunc(struct iomux_block  *blockmux,
	struct block_config *config, enum iomux_func newfunc);


#endif
