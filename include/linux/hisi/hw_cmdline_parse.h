#ifndef _HW_COMDLINE_PARSE_H
#define _HW_COMDLINE_PARSE_H

/* Format of hex string: 0x12345678 */
#define HEX_STRING_MAX   (10)
#define TRANSFER_BASE    (16)

#define RUNMODE_FLAG_NORMAL  0
#define RUNMODE_FLAG_FACTORY 1


extern int get_logctl_value(void);
extern unsigned int runmode_is_factory(void);
extern int get_uart0_config(void);



#endif
