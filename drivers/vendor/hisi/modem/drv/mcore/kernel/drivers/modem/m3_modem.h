#ifndef _M3_MODEM_H_
#define _M3_MODEM_H_

#define MODEM_ALREADY_INIT_MAGIC    0x5a5a5a5a
#define PM_MODEM_SLEEP               0
#define PM_MODEM_WAKE                1

typedef struct
{
	u32 init_flag;
}T_MODEM_ST;

extern u32 get_modem_init_flag(void);
extern void set_modem_status(u32 status);
extern u32 get_modem_status(void);
#endif /* end of _M3_MODEM_H_*/

