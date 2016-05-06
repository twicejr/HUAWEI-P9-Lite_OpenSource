#ifndef _BOOT_LOG_H
#define _BOOT_LOG_H
int boot_log_console_read(char __user *buff, u32 size);
int boot_log_register(void);
#endif
