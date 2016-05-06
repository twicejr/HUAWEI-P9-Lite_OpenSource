#ifndef _LOG_SWITCH_H
#define _LOG_SWITCH_H


#define LOGCTL_NV_NUM		301
#define LOGCTL_NV_NAME		"LOGCTL"

#define LOGCTL_OFF		0
#define LOGCTL_ON		1

enum {
	LOGCTL_SUCCESS = 0,
	LOGCTL_READ_ERR = -1,
	LOGCTL_WRITE_ERR = -2,
};

#if defined (CONFIG_LOG_SWITCH)
extern int get_logctl_flag(void);
#else
#define get_logctl_flag()      (LOGCTL_ON)
#endif


#define __LOGCTL_IO    0xBE

#define LOGCTL_GET_STATE        _IO(__LOGCTL_IO, 1) /* state of logctl */

#endif	//#ifndef _LOG_SWITCH_H
