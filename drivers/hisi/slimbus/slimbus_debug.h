/*
 *	slimbus is a kernel driver which is used to manager SLIMbus devices
 *	Copyright (C) 2014	Hisilicon

 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.

 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.

 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef __SLIMBUS_DEBUG_H__
#define __SLIMBUS_DEBUG_H__

extern uint32_t	slimbus_log_count;
extern uint32_t	slimbus_rdwrerr_times;
extern volatile uint32_t	slimbus_drv_log_count;
extern volatile uint32_t	lostms_times;

/* used	to print read/write	error */
#define	SLIMBUS_LIMIT_ERR(msg, ...)		\
	do {	\
		slimbus_rdwrerr_times++;		\
		if (slimbus_rdwrerr_times <	slimbus_log_count)	\
			printk(KERN_ERR	"[SLIMbus %s:%d] times:%d "msg, __FUNCTION__,__LINE__, slimbus_rdwrerr_times, ## __VA_ARGS__);	\
	} while	(0)

#define	SLIMBUS_LIMIT_INFO(msg,	...)	\
	do {	\
		slimbus_rdwrerr_times++;		\
		if (slimbus_rdwrerr_times <	slimbus_log_count)	\
			printk(KERN_INFO "[SLIMbus %s:%d] "msg,	__FUNCTION__,__LINE__, ## __VA_ARGS__);	\
	} while	(0)

#define	SLIMBUS_RECOVER_INFO(msg, ...)	\
	do {	\
		if (slimbus_rdwrerr_times > 0)	\
			printk(KERN_INFO "[SLIMbus %s:%d] "msg,	__FUNCTION__,__LINE__, ## __VA_ARGS__);	\
		slimbus_rdwrerr_times =	0;		\
	} while	(0)

/* used	to print slimbus_drv.c such	as LOST_MS	*/
#define	SLIMBUS_DRV_LIMIT_ERR(msg, ...)	\
	do {	\
		slimbus_rdwrerr_times++;		\
		if (slimbus_rdwrerr_times <	slimbus_log_count)	\
			printk(KERN_ERR	"[SLIMbus %s:%d] "msg, __FUNCTION__,__LINE__, ## __VA_ARGS__);	\
	} while	(0)

#define	SLIMBUS_DEV_LIMIT_INFO(msg,	...)	\
	do {	\
		lostms_times++;		\
		if (lostms_times < slimbus_drv_log_count)	\
			printk(KERN_INFO "[SLIMbus %s:%d] "msg,	__FUNCTION__,__LINE__, ## __VA_ARGS__);	\
	} while	(0)

#define	SLIMBUS_DEV_LIMIT_ERR(msg,	...)	\
	do {	\
		lostms_times++; 	\
		if (lostms_times < slimbus_drv_log_count)	\
			printk(KERN_ERR "[SLIMbus %s:%d] "msg, __FUNCTION__,__LINE__, ## __VA_ARGS__); \
	} while (0)

#define	SLIMBUS_DEV_LOSTMS_RECOVER(msg,	...)	\
	do {	\
		if (lostms_times > 0)	\
			printk(KERN_INFO "[SLIMbus %s:%d] "msg, __FUNCTION__,__LINE__, ## __VA_ARGS__);	\
		lostms_times = 0;		\
		dsm_notify_limit = 0;	\
	} while (0)

/* core	driver */
#define	SLIMBUS_CORE_LIMIT_ERR(msg,	...)	\
	do {	\
		slimbus_rdwrerr_times++;	\
		if (slimbus_rdwrerr_times <	slimbus_log_count)	\
			printk(KERN_ERR	"[SLIMbus %s:%d] "msg, __FUNCTION__,__LINE__, ## __VA_ARGS__);	\
	} while	(0)

#endif

