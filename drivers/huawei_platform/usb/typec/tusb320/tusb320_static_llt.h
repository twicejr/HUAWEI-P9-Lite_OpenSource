#ifndef _tusb320_static_llt_h_
#define _tusb320_static_llt_h_

struct tusb320_static_ops {
	int (*tusb320_read_reg)(u8 reg, u8 *val);
	int (*tusb320_detect_input_current)(void);
};

#endif