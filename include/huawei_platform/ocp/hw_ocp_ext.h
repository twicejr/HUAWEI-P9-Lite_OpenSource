#ifndef HW_OCP_EXT_H
#define HW_OCP_EXT_H

enum {
	/*LCD Event*/
	HW_OCP_LCD_EVENT = 0,
	/*TP Event*/
	HW_OCP_TP_EVENT,
	/*Speaker-D Event*/
	HW_OCP_SPK_EVENT,
};
extern int hw_ocp_handler(char *name);
#endif
