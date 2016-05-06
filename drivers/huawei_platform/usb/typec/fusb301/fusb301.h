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
*  Description:    .h file for Fairchild fusb301 typec chip
*  Version:
*  Function List:
*  History:
*  <author>  <time>   <version >   <desc>
***********************************************************/

#ifndef _TYPEC_FUSB301_H_
#define _TYPEC_FUSB301_H_

#define FUSB301_REGISTER_NUM    32

#ifndef BIT
#define BIT(x)        (1 << (x))
#endif

#define DISABLE_DURATION_MS    10

/* Register address */
#define FUSB301_REG_DEVICE_ID            0x01
#define FUSB301_REG_PORT_MODE            0x02
#define FUSB301_REG_CONTROL              0x03
#define FUSB301_REG_MANUAL               0x04
#define FUSB301_REG_RESET                0x05
#define FUSB301_REG_MASK                 0x10
#define FUSB301_REG_STATUS               0x11
#define FUSB301_REG_TYPE                 0x12
#define FUSB301_REG_INT                  0x13

/* Register REG_PORT_MODE 02 to control port mode as a host */
#define FUSB301_REG_SET_DRP_ACC                 BIT(5)
#define FUSB301_REG_SET_DRP                     BIT(4)
#define FUSB301_REG_SET_UFP_ACC                 BIT(3)
#define FUSB301_REG_SET_UFP                     BIT(2)
#define FUSB301_REG_SET_DFP_ACC                 BIT(1)
#define FUSB301_REG_SET_DFP                     BIT(0)

/* Register REG_CONTROL 03 */
#define FUSB301_REG_SET_DRPTOG_35UFP            0x00
#define FUSB301_REG_SET_DRPTOG_30UFP            (BIT(5) | BIT(4))
#define FUSB301_REG_SET_DRPTOG_25DFP            BIT(5)
#define FUSB301_REG_SET_DRPTOG_30DFP            BIT(4)
#define FUSB301_REG_HOST_CUR_NONE               0x00
#define FUSB301_REG_HOST_CUR_HIGH               (BIT(2) | BIT(1))
#define FUSB301_REG_HOST_CUR_MID                BIT(2)
#define FUSB301_REG_HOST_CUR_DEFAULT            BIT(1)
#define FUSB301_REG_HOST_CUR_MODE               (BIT(2) | BIT(1))
#define FUSB301_REG_INT_MASK                    BIT(0)

/* Register REG_RESET 05 */
#define FUSB301_RESET                           BIT(0)

/* Register REG_MASK 10 */
#define FUSB301_REG_MASK_DETACH                 BIT(1)
#define FUSB301_REG_MASK_ATTACH                 BIT(0)

/* Register REG_STATUS 11 */
#define FUSB301_REG_NO_CC_DETECTED              0x00
#define FUSB301_REG_CC_FAULT                    (BIT(5) | BIT(4))
#define FUSB301_REG_CC2_DETECTED                BIT(5)
#define FUSB301_REG_CC1_DETECTED                BIT(4)
#define FUSB301_REG_CC_STATUS                   (BIT(5) | BIT(4))
#define FUSB301_REG_VBUSOK                      BIT(3)
#define FUSB301_REG_UNATTACHED_UFP              0x00
#define FUSB301_REG_DEV_CUR_HIGH                (BIT(2) | BIT(1))
#define FUSB301_REG_DEV_CUR_MID                 BIT(2)
#define FUSB301_REG_DEV_CUR_DEFAULT             BIT(1)
#define FUSB301_REG_DEV_CUR_MODE                (BIT(2) | BIT(1))
#define FUSB301_REG_ATTACH                      BIT(0)

/*  REG_TYPE 12 */
#define FUSB301_REG_STATUS_DFP                  BIT(4)
#define FUSB301_REG_STATUS_UFP                  BIT(3)
#define FUSB301_REG_STATUS_POWERACC             BIT(2)
#define FUSB301_REG_STATUS_DEBUGACC             BIT(1)
#define FUSB301_REG_STATUS_AUDIOACC             BIT(0)

/* Register REG_INTERRUPT 13  */
#define FUSB301_REG_INT_ACC_CH                  BIT(3) //interrupt of accessory change
#define FUSB301_REG_INT_CC_CUR_CH               BIT(2) //interrupt of cc current change
#define FUSB301_REG_INT_DETACH                  BIT(1)
#define FUSB301_REG_INT_ATTACH                  BIT(0)

#define TYPEC_STATE_UNATTACHED_SINK                                0
#define TYPEC_STATE_UNATTACHED_SOURCE                           1
#define TYPEC_STATE_UNATTACHED_DISABLED                        2
#define TYPEC_STATE_UNATTACHED_ERRORRECOVERY            3

#define FUSB301_REG_MANUAL_UNATTACHED_SINK                            BIT(3)
#define FUSB301_REG_MANUAL_UNATTACHED_SOURCE                       BIT(2)
#define FUSB301_REG_MANUAL_UNATTACHED_DISABLED                    BIT(1)
#define FUSB301_REG_MANUAL_UNATTACHED_ERRORRECOVERY        BIT(0)


#endif /*_TYPEC_FUSB301_H_*/
