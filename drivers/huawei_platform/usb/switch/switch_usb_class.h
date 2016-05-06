/************************************************************
*
* Copyright (C), 1988-1999, Huawei Tech. Co., Ltd.
* FileName: switch_usb_class.h
* Author: lixiuna(00213837)       Version : 0.1      Date:  2013-11-07
*
* This software is licensed under the terms of the GNU General Public
* License version 2, as published by the Free Software Foundation, and
* may be copied, distributed, and modified under those terms.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
*  Description:    .h file for switch chip
*  Version:
*  Function List:
*  History:
*  <author>  <time>   <version >   <desc>
***********************************************************/
#define FSA9685_OPEN        0
#define FSA9685_USB1        1
#define FSA9685_USB2        2
#define FSA9685_MHL     4
#define FSA9685_USB1_ID_TO_IDBYPASS             1

struct switch_usb_info {
    struct atomic_notifier_head charger_type_notifier_head;
    spinlock_t reg_flag_lock;
};

extern int fsa9685_manual_sw(int input_select);
extern int fsa9685_manual_detach(void);
