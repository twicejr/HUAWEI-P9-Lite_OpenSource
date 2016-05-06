/************************************************************
*
* Copyright (C), 1988-1999, Huawei Tech. Co., Ltd.
* FileName: switch_fsa9685.h
* Author: huxiaoqiang(00272253)       Version : 0.1      Date:  2013-11-07
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
*  Description:    .h file for switch fsa9685
*  Version:
*  Function List:
*  History:
*  <author>  <time>   <version >   <desc>
***********************************************************/
#include <linux/huawei/usb/hisi_usb.h>

enum hisi_charger_type fsa9685_get_charger_type(void);
int fcp_read_switch_status (void);
int fcp_read_adapter_status(void);
void switch_dump_register(void);
void fsa9685_reg_dump(char* ptr);
int is_fcp_charger_type(void);
int fsa9685_dcd_timeout_enable(bool enable_flag);
/*fcp detect */
#define FCP_ADAPTER_DETECT_FAIL 1
#define FCP_ADAPTER_DETECT_SUCC 0
#define FCP_ADAPTER_DETECT_OTHER -1
/*fcp adapter status */
#define FCP_ADAPTER_STATUS 0x28
#define FCP_ADAPTER_OVLT 0x04
#define FCP_ADAPTER_OCURRENT 0x02
#define FCP_ADAPTER_OTEMP 0x01
