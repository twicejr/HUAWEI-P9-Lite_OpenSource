#ifndef _SENSOR_SYS_INFO_H
#define _SENSOR_SYS_INFO_H

int open_send_current(int (*send)(int));
int close_send_current(void);
int check_if_need_current(void);
#endif
