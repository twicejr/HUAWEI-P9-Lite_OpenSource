/* Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 and
* only version 2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
*/
#ifndef __HW_SOUNDTRIGGER_EVENT_H__
#define __HW_SOUNDTRIGGER_EVENT_H__

enum hw_soundtrigger_event{
	HW_SOUNDTRIGGER_OEM_TRIGGER,
	HW_SOUNDTRIGGER_OEM_COMMAND1,
	HW_SOUNDTRIGGER_OKGOOGLE,
	HW_SOUNDTRIGGER_RESERVED1,
	HW_SOUNDTRIGGER_RESERVED2,
};

extern void hw_soundtrigger_event_input(unsigned int soundtrigger_event);
extern void hw_soundtrigger_event_uevent(unsigned int soundtrigger_event);

#endif /* __HW_SOUNDTRIGGER_EVENT_H__ */
