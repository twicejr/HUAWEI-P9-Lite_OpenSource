/************************************************************
*
* Copyright (C), 1988-1999, Huawei Tech. Co., Ltd.
* FileName: switch_chip.h
* Author: lixiuna(00213837)       Version : 0.1      Date:  2013-09-01
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

#ifndef __DRIVERS_SWITCH_SMART_CHIP_H__
#define __DRIVERS_SWITCH_SMART_CHIP_H__

/******************************************************************************
* Register addresses
******************************************************************************/
#define FSA9685_REG_DEVICE_ID                 1
#define FSA9685_REG_CONTROL                   2
#define FSA9685_REG_INTERRUPT                 3
#define FSA9685_REG_INTERRUPT_MASK            4
#define FSA9685_REG_ADC                       5
#define FSA9685_REG_TIMING_SET_1              6
#define FSA9685_REG_DETACH_CONTROL            7
#define FSA9685_REG_DEVICE_TYPE_1             8
#define FSA9685_REG_DEVICE_TYPE_2             9
#define FSA9685_REG_DEVICE_TYPE_3            10
#define FSA9685_REG_MANUAL_SW_1              11
#define FSA9685_REG_MANUAL_SW_2              12
#define FSA9685_REG_TIMING_SET_2             13
#define FSA9685_REG_VBUS_STATUS              0X1b
#define FSA9685_REG_DCD                      0x1f

/* Register FSA9685_REG_CONTROL (02) */
#define FSA9685_INT_MASK             (1<<0)
#define FSA9685_WAIT                 (1<<1)
#define FSA9685_MANUAL_SW            (1<<2)
#define FSA9685_RAW_DATA             (1<<3)
#define FSA9685_SWITCH_OPEN          (1<<4)

/* Register FSA9685_REG_INTERRUPT (03) */
#define FSA9685_ATTACH                 (1<<0)
#define FSA9685_DETACH                 (1<<1)
#define FSA9685_VBUS_CHANGE            (1<<5)
#define FSA9685_RESERVED_ATTACH        (1<<6)
#define FSA9685_ADC_CHANGE             (1<<7)

/* Register FSA9685_REG_DEVICE_TYPE_1 (08)*/
#define FSA9685_FC_USB_DETECTED      (1<<0)
#define FSA9685_FC_RF_DETECTED       (1<<1)
#define FSA9685_USB_DETECTED         (1<<2)
#define FSA9685_UART_DETECTED        (1<<3)
#define FSA9685_MHL_DETECTED         (1<<4)
#define FSA9685_CDP_DETECTED         (1<<5)
#define FSA9685_DCP_DETECTED         (1<<6)
#define FSA9685_USBOTG_DETECTED      (1<<7)
#define FSA9685_DEVICE_TYPE1_UNAVAILABLE   (0x0a) //00001010

/* Register FSA9685_REG_DEVICE_TYPE_2 (09)*/
#define FSA9685_JIG_UART             (1<<2)
#define FSA9685_DEVICE_TYPE2_UNAVAILABLE   (0xf8) //11111000

/* Register FSA9685_REG_DEVICE_TYPE_3 (0A)*/
#define FSA9685_CUSTOMER_ACCESSORY5      (1<<5)
#define FSA9685_CUSTOMER_ACCESSORY6      (1<<6)
#define FSA9685_CUSTOMER_ACCESSORY7      (1<<7)
#define FSA9685_FM8_ACCESSORY            (1<<0)
#define FSA9685_DEVICE_TYPE3_UNAVAILABLE  (0x5e) //01011110

/*Register VBUS_VALID (1B)*/
#define FSA9685_VBUS_VALID               (1<<1)

/*ID validity detection*/
#define ID_VALID 1
#define ID_INVALID 0
#define MAX_DETECTION_TIMES 3

/*USB state*/
#define FSA9685_OPEN                       0
#define FSA9685_USB1_ID_TO_IDBYPASS        1
#define FSA9685_USB2_ID_TO_IDBYPASS        2
#define FSA9685_UART_ID_TO_IDBYPASS        3
#define FSA9685_MHL_ID_TO_CBUS             4
#define FSA9685_USB1_ID_TO_VBAT            5

/*Register FSA9685_REG_MANUAL_SW_1 value in different USB state*/
#define REG_VAL_FSA9685_OPEN    0
#define REG_VAL_FSA9685_USB1_ID_TO_IDBYPASS    ((2<<0) | (1<<2) | (1<<5))
#define REG_VAL_FSA9685_USB2_ID_TO_IDBYPASS    ((2<<0) | (2<<2) | (2<<5))
#define REG_VAL_FSA9685_UART_ID_TO_IDBYPASS    ((2<<0) | (3<<2) | (3<<5))
#define REG_VAL_FSA9685_MHL_ID_TO_CBUS         ((3<<0) | (4<<2) | (4<<5))
#define REG_VAL_FSA9685_USB1_ID_TO_VBAT        ((1<<5) | (1<<2) | (1<<0))


/******************************************************************************
* fcp related definitions
******************************************************************************/
#ifndef BIT
#define BIT(x)         (1 << (x))
#endif
#define FSA9685_REG_CONTROL2          0xe
#define FSA9685_REG_DEVICE_TYPE_4     0xf
#define FSA9685_REG_ACCP_STATUS       0x40
#define FSA9685_REG_ACCP_CNTL         0x41
#define FSA9685_REG_ACCP_CMD          0x44
#define FSA9685_REG_ACCP_ADDR         0x47
#define FSA9685_REG_ACCP_DATA         0x48
#define FSA9685_REG_ACCP_INTERRUPT1   0x59
#define FSA9685_REG_ACCP_INTERRUPT2   0x5a
#define FSA9685_REG_ACCP_INTERRUPT_MASK1   0x5b
#define FSA9685_REG_ACCP_INTERRUPT_MASK2   0x5c

/* Register FSA9685_REG_DEVICE_ID (0x1) */
#define FSA9688_VERSION_ID             0x2
#define FAS9685_VERSION_ID_BIT_MASK   (0x1F<<3)
#define FAS9685_VERSION_ID_BIT_SHIFT   0x3

#define FSA9688C_VERSION_ID            0x3

/* Register FSA9685_REG_CONTROL2 (0x0e) */
#define FSA9685_ACCP_AUTO_ENABLE      (1<<6)
#define FSA9685_ACCP_ENABLE           (1<<7)
#define FSA9685_ACCP_OSC_ENABLE           (1<<5)
#define FSA9685_DCD_TIME_OUT_MASK      (BIT(0))

/* Register FSA9685_REG_DEVICE_TYPE_4 (0xf)*/
#define FSA9685_ACCP_CHARGER_DET      (1<<7)

/* Register FSA9685_REG_ACCP_STATUS (0x40)*/
#define FSA9688_ACCP_STATUS_MASK      (BIT(7) | BIT(6) | BIT(0))
#define FSA9688_ACCP_STATUS_SLAVE_GOOD     (BIT(7) | BIT(6) | BIT(0))
#define FAS9685_ACCP_SLAVE_DET        (BIT(7) |BIT(6))
#define FSA9685_ACCP_DEV_ATTACH       (1<<0)

/* Register FSA9685_REG_ACCP_CNTL (0x41)*/
#define FSA9685_ACCP_IS_ENABLE       (1<<3)
#define FSA9685_ACCP_MSTR_RST        (1<<2)
#define FAS9685_ACCP_SENDCMD         (1<<0)
#define FAS9685_ACCP_CNTL_MASK      (BIT(0) | BIT(2) | BIT(3))

/* Register FSA9685_REG_ACCP_INTERRUPT1 (0x59)*/
#define FAS9685_CMDCPL               (1<<7)
#define FAS9685_ACK                  (1<<6)
#define FAS9685_NACK                 (1<<4)
#define FAS9685_CRCPAR               (1<<3)

/* Register FSA9685_REG_ACCP_INTERRUPT2 (0x5a)*/
#define FAS9685_CRCRX                (1<<4)
#define FAS9685_PARRX                (1<<3)
#define FAS9685_PROSTAT              (1<<1)
#define FAS9685_DSDVCSTAT            (1<<0)

#define FCP_CMD_SBRRD      0x0c
#define FCP_CMD_SBRWR      0x0b

#define FCP_SLAVE_REG_ID_OUT0               0x04
#define FCP_SLAVE_REG_DISCRETE_CAPABILITIES 0x21
#define FCP_SLAVE_REG_MAX_PWR               0x22
#define FCP_SLAVE_REG_OUTPUT_CONTROL        0x2b
#define FCP_SLAVE_REG_VOUT_CONFIG           0x2c

#define FCP_SLAVE_REG_DISCRETE_OUT_V(n)     (0x30+(n))

/* Register FCP_SLAVE_OUTPUT_CONTROL (0x2b)*/
#define FCP_SLAVE_SET_VOUT   (1<<0)

#define FCP_VOL_STEP         10
#define FCP_OUTPUT_VOL_5V     5
#define FCP_OUTPUT_VOL_9V     9
#define FCP_OUTPUT_VOL_12V   12


#define FCP_POLL_TIME        (100)   /* 100ms */
#define FCP_DETECT_MAX_COUT  (20)  /* fcp detect MAX COUT */
#define FCP_RETRY_MAX_TIMES     (3)  /* fcp retry max times */

enum fcp_mmi_test_result{
    FCP_TEST_SUCC,
    FCP_TEST_FAIL,
    FCP_NOT_SUPPORT,
};

/******************************************************************************
* fcp definitions  end
******************************************************************************/

/*usb otg wake lock flag*/
#define USB_SWITCH_NEED_WAKE_LOCK 1
#define USB_SWITCH_NEED_WAKE_UNLOCK 0

/*for phone-off current drain test*/
#define MANUAL_DETACH 0
#define MANUAL_SWITCH 1

/*jig pin control for battery cut test*/
#define JIG_PULL_DEFAULT_DOWN   0
#define JIG_PULL_UP             1
#define REG_JIG_DEFAULT_DOWN 0x01
#define REG_JIG_UP (~REG_JIG_DEFAULT_DOWN)

enum err_oprt_reg_num
{
    ERR_FSA9685_REG_MANUAL_SW_1 = 1,
    ERR_FSA9685_READ_REG_CONTROL = 2,
    ERR_FSA9685_WRITE_REG_CONTROL = 3,
};

enum err_oprt_irq_num
{
    ERR_REQUEST_THREADED_IRQ = 50,
    ERR_GPIO_DIRECTION_INPUT = 51,
    ERR_GPIO_REQUEST = 52,
    ERR_GPIO_TO_IRQ = 53,
    ERR_OF_GET_NAME_GPIO = 54,
    ERR_SWITCH_USB_DEV_REGISTER = 55,
    ERR_NO_DEV = 56,
};

extern int get_swstate_value(void);
extern void switch_usb2_access_through_ap(void);
extern void switch_usb_set_state_to_mhl(void);
extern void usb_custom_acc5_event(int pedestal_attach);

#endif /* __DRIVERS_SWITCH_SMART_CHIP_H__ */
