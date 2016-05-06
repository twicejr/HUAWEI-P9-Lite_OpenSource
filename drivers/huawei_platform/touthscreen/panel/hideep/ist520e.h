/*
 * include/linux/HiDeep_ts.h - platform data structure for iST Series sensor
 *
 * Copyright (C) 2012 Hideep, Inc.
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
 */

#ifndef _LINUX_HIDEEP_TS_H
#define _LINUX_HIDEEP_TS_H

#include <linux/ktime.h>
#include <linux/module.h>
#include <linux/firmware.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/hrtimer.h>
#include <linux/i2c.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/input.h>
#include <linux/input/mt.h> // slot
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/completion.h>
#include <linux/platform_device.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <linux/gfp.h>
#include <linux/firmware.h>
#include <linux/regulator/consumer.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/cdev.h>
#include <linux/poll.h>
#include <linux/kthread.h>
#include <linux/dma-mapping.h>
#include <linux/gpio.h> 
#include <linux/of_gpio.h>
#include <huawei_platform/touthscreen/huawei_touchscreen.h>
#include <../../huawei_touchscreen_chips.h>
#include "../../huawei_touchscreen_algo.h"

#define ISTCORE_IF_DEVICE
#define IST510E_KEYBUTTON
#define PROTOCOL_HIDEEP_20

#define IST_GREEN  0
#define IST_CRIMSON  1
#define IST_INDIGO  2
#define CRIMSON

#define HIDEEP_CHIP_INFO "hideep-"
#define ISTCORE_DEV_NAME  "crimson: "
#define ISTCORE_I2C_NAME "ist5001z"
#define ISTCORE_I2C_ADDR 0x6C
#define ISTCORE_I2C_BUS 5
#define ISTCORE_IF_DEVICE_NAME "ist510e_debug"
#define MAX_TRANSACTION_LENGTH 8
#define MAX_I2C_DMA_LENGTH 252
#define MAX_I2C_SPEED 400
#define MAX_VR_BUFF 0x80                                    // vr write unit..


#define HIDEEP_IRQ_GPIO "attn_gpio"
#define HIDEEP_RST_GPIO "reset_gpio"
#define HIDEEP_VDDIO_GPIO_CTRL "vddio_ctrl_gpio"
#define HIDEEP_VCI_GPIO_CTRL "vci_ctrl_gpio"
#define HIDEEP_IRQ_CFG "irq_config"

#define HIDEEP_ALGO_ID "algo_id"
#define HIDEEP_IC_TYPES	"ic_type"
#define HIDEEP_X_MAX "x_max"
#define HIDEEP_Y_MAX "y_max"
#define HIDEEP_X_MAX_MT "x_max_mt"
#define HIDEEP_Y_MAX_MT "y_max_mt"
#define HIDEEP_TP_FUNC_FLAG "tp_func_flag"

#define HIDEEP_VCI_GPIO_TYPE "vci_gpio_type"
#define HIDEEP_VCI_REGULATOR_TYPE	"vci_regulator_type"
#define HIDEEP_VDDIO_GPIO_TYPE "vddio_gpio_type"
#define HIDEEP_VDDIO_REGULATOR_TYPE "vddio_regulator_type"
/*??_VBUS "hideep-io" is 1.8V  , hideep_VDD	 is 2.8 or 3.1V*/
#define HIDEEP_VDD "hideep-vdd"
#define HIDEEP_VBUS "hideep-io"
/*set the vci ldo voltage 3.1V for JDI*/
#define HIDEEP_UNIT_CAP_TEST_INTERFACE "unite_cap_test_interface"
#define HIDEEP_VCI_LDO_JDI_VALUE (3300000)


#define ISTCORE_PWR_NORMAL 1
#define ISTCORE_PWR_SLEEP 2
#define ISTCORE_PWR_PGM 3

#define TOUCH_MAX_COUNT 10
#define KEYS_MAX_COUNT 1
#define TOUCH_COUNT_ADDR 0x0240
#define TOUCH_READ_START_ADDR 0x0242
#define KEY_READ_START_ADDR (0x0242 + (sizeof(struct ist510e_touch_evt)) * TOUCH_MAX_COUNT)
#define VR_ADDR_IMAGE 0x1000
#define VR_ADDR_BASE 0x0000
#define DWZ_ADDR 0x0400
#define VR_VERSION_ADDR 0x801A
#define VR_READ_ROI_DATA_ADDR 0x8100
#define VR_READ_ROI_EN_ADDR 0x0814
#define VR_SINGLE_TOUCH 0x818

#define PRODUCT_ID_LENGTH 10
#define HIDEEP_RX_COUNT 28
#define HIDEEP_TX_COUNT 16
#define HIDEEP_RX_3D_COUNT 3
#define HIDEEP_TX_3D_COUNT 5

#define IST_TOUCH 1
#define IST_KEY 0

#define EV_ALWAYS_REPORT 0   //0x01
#define EV_TOUCHED 1   //0x02
#define EV_FIRST_CONTACT 2   //0x04
#define EV_DRAG_MOVE 3   //0x08
#define EV_RELEASED 4   //0x10
#define EV_PINCH 5   //0x20
#define EV_PRESSURE 6   //0x40

#define KY_RELEASED 0x20            // touch key.....
#define KY_PRESSED 0x40
#define KY_FIRST_PRESSED 0x80
#define KY_PRESSED_MASK 0xC0

#define OPM_RAW_FLAG (0x80)
#define OPM_TOUCH_A (0x00)
#define OPM_MOD (0x80)
#define OPM_MOD_CAP (0x81)
#define OPM_MOD_PRS (0x82)
#define OPM_FRAME_PRS (0x84)
#define OPM_DEMOD (0x85)
#define OPM_DEMOD_CAP (0x86)
#define OPM_DEMOD_PRS (0x87)
#define OPM_FRAME (0x88)
#define OPM_FRAME_CAP (0x89)
#define OPM_DIFF (0x8A)
#define OPM_DIFF_CAP (0x8B)
#define OPM_DIFF_PRS (0x8C)
#define OPM_BASELINE_CAP (0x8D)
#define OPM_AULU_DIFF (0x8E)
#define OPM_AULU_DATA (0x8F)
#define OPM_STATUS (0x90)
#define OPM_LASTDIFF (0x91)
#define OPM_PARM0 (0x92)
#define OPM_PARM1 (0x93)
#define OPM_PARM2 (0x94)
#define OPM_PARM3 (0x95)
//#define HIDEEP_READ_I2C_CNT_DATA
//#define HIDEEP_TRACE_TOUCH_EVENT
#ifdef HIDEEP_TRACE_TOUCH_EVENT
#define MAX_DEBUG_COUNT 1000
#endif
/*------------------------------------------------------------------------*//**
 * command list
 *//*--------------------------------------------------------------------------*/
#define IST_EMPTY (0x0000)
#define IST_ENTER_SANDMAN (0x080F)                                    // enter sleep mode
#define IST_RESET (0x0802)                                    // software reset
#define IST_TEST_MODE (0x0804)                                    //
#define IST_FIRST_Z_VALUE (0x246)
#define IST_APPLE_WEIGHT_VALUE (0x2b4)

#define VR_HOLSTER 0x0812
#define VR_GLOVE 0x0813
#define VR_LPWU 0x0815
#define VR_PALM 0x0000
#define VR_SCAN_SWITCH 0x0817

#define HIDEEP_GES_DOUBLE_TAP	1
#define HIDEEP_GES_CHAR 2
#define HIDEEP_APPLE_WEIGHT_READY 3
#define HIDEEP_CHAR_C (1)
#define HIDEEP_CHAR_E (2)
#define HIDEEP_CHAR_M (3)
#define HIDEEP_CHAR_W (4)

#ifdef  PROTOCOL_HIDEEP_20
struct ist510e_touch_evt
{
	 u16 x;
	 u16 y;
	 u16 z;
	 u8 w;
	 u8 flag;
	 u8 type;                       // not included version 1.0
	 u8 index;
};
#else
struct ist510e_touch_evt
{
	 u8 flag;
	 u8 index;
	 u16 x;
	 u16 y;
	 u8 z;
	 u8 w;
};
#endif

struct ist510e_touch_key
{
	u8 flag;
	u8 z;
};

enum
{
	None = 0,
	TOUCH_SCREEN,
	TOUCH_KEY,
};

typedef struct pannel_info_t
{
	u16 vendor;
	u16 product;
	u16 version;

	u16 dp_w;            // display width
	u16 dp_h;            // display height
	u8  tx  ;
	u8  rx  ;
	u8  tx_stride;
	u8  key_nr;
	u16 key[10];
} PANNEL_INFO_T;

typedef struct dwz_info_t
{
    //-------------------------------------------
	u32 c_begin;         // code start address
	u32 c_len  ;         // code length
	u16 c_crc[4];        // code crc

	u32 d_begin;         // custom code
	u16 d_len  ;         // custom code length
	u16 rsv0   ;

	u32 v_begin;         // vreg   code
	u16 v_len  ;         // vreg   code length
	u16 rsv1   ;

	u32 f_begin;         // vreg   code
	u16 f_len  ;         // vreg   code length
	u16 rsv2   ;

	u16 ver_b  ;         // version information
	u16 ver_c  ;
	u16 ver_d  ;
	u16 ver_v  ;

	u32 model  ;         // model
	u32 c_code ;
	u16 p_code ;
	u16 extra_option;
	u16 ver_ft_major;
	u16 ver_ft_minor;

	PANNEL_INFO_T  pannel;
} DWZ_INFO_T;
/*------------------------------------------------------------------------------
 * driver information for iST510e
 *-----------------------------------------------------------------------------*/
struct hideep_platform_data
{
	u32 version;
	u32 gpio_int;
	u32 max_x;
	u32 max_y;
	u32 max_z;
	u32 max_w;
	u32 (*power)(int on);
};

typedef struct ist510e_debug_dev
{
	u8 *data;
	struct cdev cdev;
	wait_queue_head_t i_packet;           // read raw
	u32 i_rdy;
	u16 vr_addr;
	u8 *vr_buff;
	u8 *im_buff;
	u16 im_size;
	u16 vr_size;
	u8 im_r_en;

	struct ist510e *ts    ;
} ist510e_debug_dev_t;

typedef struct ist510e_debug_cfg
{
	u16 im_size;
	u16 vr_size;
} ist510e_debug_cfg_t;

struct ist510e_touch_debug_evt
{
	u8 count;
	struct ist510e_touch_evt  events[TOUCH_MAX_COUNT];
};

struct hideep_roi
{
	u8 enable;
	u8 diff[ROI_DATA_READ_LENGTH];
};

struct ist510e
{
	DWZ_INFO_T dwz_info;
	long tch_bit;
	u8 glove_mode;
	u8 gesture_enable;
	u8 holster_mode;
	u16 addr;
	struct  i2c_client *client;
	struct  input_dev *input_dev;
	struct  hideep_platform_data *pdata;
	struct  work_struct work;
	u16 z_buffer;
	bool z_status;
	
	u32 z_calib_start;
	u32 z_calib_end;
	bool z_flag_calib2;
	bool z_flag_ready;
	u16 z_data[4096];
	u32 z_index;

	u32 flags;
	s32 irq;
	s32 dev_state;
	u32 (*power)(int on);
	struct mutex i2c_mutex;                                  // for dma memory
	struct mutex dev_mutex;
#ifdef ISTCORE_IF_DEVICE
    // informations for debug driver
	u32 debug_dev_no;
	struct ist510e_debug_dev debug_dev  ;
	struct class *debug_class;
#endif
	u32 input_touch_nr;                              // touch count
	u32 input_key_nr;                              // key count
	u32 input_event_nr;                              // event count
	struct ist510e_touch_evt input_evt[TOUCH_MAX_COUNT];
#ifdef HIDEEP_READ_I2C_CNT_DATA
	u8 i2c_buf[TOUCH_MAX_COUNT*sizeof(struct ist510e_touch_evt)+2];
#endif
#ifdef HIDEEP_TRACE_TOUCH_EVENT
	struct ist510e_touch_debug_evt  *debug_evt;
	u32 debug_index;
	u32 debug_total;
	struct timespec *event_time;
#endif
	struct ist510e_touch_key input_key[KEYS_MAX_COUNT ];
	u8 seg_buff[256];
	// for sysfs
	u32 vr_addr;
	u32 vr_data;
	u32 vr_size;
	//apple weight
	int apple_weight_init;
	int apple_weight_flag;
	u16 apple_weight_buff;
	int apple_weight_timeout;
	struct work_struct apple_weight_work;
	struct workqueue_struct *apple_weight_workqueue;
	
	// huawei interface
	struct ts_device_data *huawei_ts_data;
	struct platform_device  *huawei_ts_dev ;
	struct regulator  *tp_vci;
	struct regulator *tp_vddio;
	struct pinctrl *pctrl;
	struct pinctrl_state *pins_default;
	struct pinctrl_state *pins_idle;
	struct hideep_roi roi;
};
#ifdef ISTCORE_IF_DEVICE
s32 hideep_get_image(struct ist510e *ts);
#endif
#ifdef HIDEEP_REPEAT_START
int huawei_ts_i2c_read(u8 *reg_addr, u16 reg_len, u8 *buf, u16 len);
#endif
int hideep_sysfs_init(struct ist510e *ts);
int hideep_sysfs_uninit(struct ist510e *ts);
int hideep_load_ucode(struct ist510e *ts_drv, const char *fn,u16 ver);
int hideep_i2c_read(struct ist510e *ts, u16 addr, u16 len, u8 *buf);
int hideep_i2c_write(struct ist510e *ts, u16 addr, u16 len, u8 *buf);
int hideep_iface_init(struct ist510e *ts);
void hideep_iface_uninit(struct ist510e *ts);
int hideep_fuse_ucode( struct ts_bus_info *ext_io, const u8 *code, size_t len, int offset);
void hideep_reset_ic(void);
int hideep_sysfs_exit(struct ist510e *ts);
int hideep_get_rawdata(struct ts_rawdata_info *info, struct ts_cmd_node *out_cmd);
#endif /* _LINUX_HIDEEP_TS_H */
