/************************************************************
*
* Copyright (C), 1988-1999, Huawei Tech. Co., Ltd.
* FileName: switch_chip.h
* Author: WangJing(00270068)       Version : 0.1      Date:  2015-04-14
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
*  Description:    .h file for Pericom30216 typec chip
*  Version:
*  Function List:
*  History:
*  <author>  <time>   <version >   <desc>
***********************************************************/

#ifndef _TYPEC_PERICOM30216_H_
#define _TYPEC_PERICOM30216_H_

#define PERICOM30216_REGISTER_NUM   4

#ifndef BIT
#define BIT(x)        (1 << (x))
#endif

#define DISABLE_SET 0
#define DISABLE_CLEAR 1
#define PERICOM_RESET_DURATION_MS    25
#define PERICOM_DURATION_MS    25

/* Register address */
#define PERICOM30216_REG_DEVICE_ID            0x01
#define PERICOM30216_REG_CONTROL              0x02
#define PERICOM30216_REG_INTERRUPT            0x03
#define PERICOM30216_REG_CC_STATUS            0x04

/* Register REG_CONTROL 02 */
#define PERICOM30216_REG_CONTROL_INT_MASK            BIT(0)
#define PERICOM30216_REG_CONTROL_SET_DFP             BIT(1)
#define PERICOM30216_REG_CONTROL_SET_DRP             BIT(2)
#define PERICOM30216_REG_CONTROL_SET_UFP             0x00
#define PERICOM30216_REG_SET_PORT_STATUS             (BIT(2) | BIT(1))
#define PERICOM30216_REG_CONTROL_MID_CURRENT         BIT(3)
#define PERICOM30216_REG_CONTROL_HIGH_CURRENT        BIT(4)
#define PERICOM30216_REG_CONTROL_DEFAULT_CURRENT     0x00
#define PERICOM30216_REG_SET_CURRENT_STATUES         (BIT(4) | BIT(3))
#define PERICOM30216_REG_CONTROL_POWER_SAVING        BIT(7)

/* Register REG_INTERRUPT 03 */
#define PERICOM30216_REG_ATTACH                      BIT(0)
#define PERICOM30216_REG_DETACH                      BIT(1)

/* Register REG_CC STATUS 04 */
#define PERICOM30216_REG_CC1_CONNECTED               BIT(0)
#define PERICOM30216_REG_CC2_CONNECTED               BIT(1)
#define PERICOM30216_REG_CC_UNDERTERMINED            (BIT(1) | BIT(0))
#define PERICOM30216_REG_CC_CONNECTED_STATUS         (BIT(1) | BIT(0))
#define PERICOM30216_REG_STATUS_UFP                  BIT(2)
#define PERICOM30216_REG_STATUS_DFP                  BIT(3)
#define PERICOM30216_REG_PORT_MODE                   (BIT(4) | BIT(3) | BIT(2))
#define PERICOM30216_REG_STATUS_AUDIO                (BIT(3) | BIT(2))
#define PERICOM30216_REG_STATUS_DEBUG                BIT(4)
#define PERICOM30216_REG_INVALID_STATUS              (BIT(4) | BIT(2))
#define PERICOM30216_REG_DEFAULT_CURRENT             BIT(5)
#define PERICOM30216_REG_MID_CURRENT                 BIT(6)
#define PERICOM30216_REG_HIGH_CURRENT                (BIT(6) | BIT(5))
#define PERICOM30216_REG_DEV_CURRENT_MODE            (BIT(6) | BIT(5))
#define PERICOM30216_REG_VBUS_DEDECTED               BIT(7)



#endif
