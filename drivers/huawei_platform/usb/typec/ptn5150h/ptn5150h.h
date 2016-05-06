/************************************************************
*
* Copyright (C), 1988-1999, Huawei Tech. Co., Ltd.
* FileName: switch_chip.h
* Author: Suoandajie(00318894)       Version : 0.1      Date:  2015-10-23
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
*  Description:    .h file for Nxp PTN5150H typec chip
*  Version:
*  Function List:
*  History:
*  <author>  <time>   <version >   <desc>
***********************************************************/

#ifndef _TYPEC_PTN5150H_H_
#define _TYPEC_PTN5150H_H_

#define PTN5150H_REGISTER_NUM    20

#ifndef BIT
#define BIT(x)        (1 << (x))
#endif

/* Register address */
#define PTN5150H_REG_DEVICE_ID                           0x01
#define PTN5150H_REG_CONTROL                             0x02
#define PTN5150H_REG_INT_STATUS                          0x03
#define PTN5150H_REG_CC_STATUS                           0x04
#define PTN5150H_REG_CON_DET                             0x09
#define PTN5150H_REG_VCONN_STATUS                        0x0a
#define PTN5150H_REG_RESET                               0x10
#define PTN5150H_REG_INT_MASK                            0x18
#define PTN5150H_REG_INT_REG_STATUS                      0x19

/* Register REG_DEVICE_ID  01 */
#define PTN5150H_REG_VERSION_ID                          (BIT(7) | BIT(6) | BIT(5) | BIT(4) | BIT(3))
#define PTN5150H_REG_VENDOR_ID                           (BIT(2) | BIT(1) | BIT(0))

/* Register REG_CONTROL 02*/
#define PTN5150H_REG_RP_DEFAULT                          0x00
#define PTN5150H_REG_RP_MEDIUM                           BIT(3)
#define PTN5150H_REG_RP_HIGH                             BIT(4)
#define PTN5150H_REG_RP_MODE                             (BIT(4) | BIT(3))
#define PTN5150H_REG_MODE_UFP                            0x00
#define PTN5150H_REG_MODE_DFP                            BIT(1)
#define PTN5150H_REG_MODE_DRP                            BIT(2)
#define PTN5150H_REG_PORT_MODE                           (BIT(2) | BIT(1))
#define PTN5150H_REG_INT_MASK_DETACHED_ATTACHED          BIT(0)

/* Register PTN5150H_REG_INT_STATUS 03 */
#define PTN5150H_REG_CABLE_DETACH_INT                    BIT(1)
#define PTN5150H_REG_CABLE_ATTACH_INT                    BIT(0)

/* Register PTN5150H_REG_CC_STATUS 04 */
#define PTN5150H_REG_VBUS_DETECTION                      BIT(7)
#define PTN5150H_REG_RP_DETECTION_STANDBY                0x00
#define PTN5150H_REG_RP_DETECTION_STDUSB                 BIT(5)
#define PTN5150H_REG_RP_DETECTION_1_5A                   BIT(6)
#define PTN5150H_REG_RP_DETECTION_3A                     (BIT(6) | BIT(5))
#define PTN5150H_REG_RP_DETECTION_CUR_MODE               (BIT(6) | BIT(5))
#define PTN5150H_REG_PORT_ATTACH_STATUS_NOT_CONNECTED    0x00
#define PTN5150H_REG_PORT_ATTACH_STATUS_DFP_ATTACHED     BIT(2)
#define PTN5150H_REG_PORT_ATTACH_STATUS_UFP_ATTACHED     BIT(3)
#define PTN5150H_REG_PORT_ATTACH_STATUS_AAA_ATTACHED     (BIT(3) | BIT(2))
#define PTN5150H_REG_PORT_ATTACH_STATUS_DA_ATTACHED      BIT(4)
#define PTN5150H_REG_CC_POPARITY_CABLE_NOT_ATTACHED      0x00
#define PTN5150H_REG_CC_POPARITY_CC1_CONNECTED		 BIT(0)
#define PTN5150H_REG_CC_POPARITY_CC2_CONNECTED		 BIT(1)
#define PTN5150H_REG_CC_POPARITY_CC_STATUS               (BIT(1) | BIT(0))


/* Register PTN5150H_REG_CON_DET 09 */
#define PTN5150H_REG_CON_DET_OUTPUT_DISABLE              BIT(0)
#define PTN5150H_REG_CON_DET_OUTPUT_ENABLE               0x00

/* Register PTN5150H_REG_VCONN_STATUS 0a */
#define PTN5150H_REG_VCONN_DETECT_STATUS_STANDBY         0x00
#define PTN5150H_REG_VCONN_DETECT_STATUS_CC1             BIT(0)
#define PTN5150H_REG_VCONN_DETECT_STATUS_CC2             BIT(1)

/* Register REG_RESET 10 */
#define PTN5150H_REG_RESET_ALLREG                        BIT(0)

/* Register PTN5150H_REG_INT_MASK 18 */
#define PTN5150H_REG_CC_COMPARATOR_CHANGE_MASK           BIT(4)
#define PTN5150H_REG_ROLE_CHANGE_MASK                    BIT(3)
#define PTN5150H_REG_ORIENTATION_FOUND_MASK              BIT(2)
#define PTN5150H_REG_DA_FOUND_MASK                       BIT(1)
#define PTN5150H_REG_AA_FOUND_MASK                       BIT(0)


/* Register PTN5150H_REG_INT_REG_STATUS 19 */
#define PTN5150H_REG_COMPARATOR_CHANGE_INT_DETECTED      BIT(4)
#define PTN5150H_REG_ROLE_CHANGE_INT_DETECTED            BIT(3)
#define PTN5150H_REG_ORIENTATION_FOUND_INT_DETECTED      BIT(2)
#define PTN5150H_REG_DA_FOUND_INT_DETECTED               BIT(1)
#define PTN5150H_REG_AA_FOUND_INT_DETECTED               BIT(0)


#endif /*_TYPEC_PTN5150H_H_*/
