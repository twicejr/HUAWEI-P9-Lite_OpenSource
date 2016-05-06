/*
 *  Hisilicon K3 soc camera ISP driver source file
 *
 *  CopyRight (C) Hisilicon Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/time.h>
#include <linux/spinlock.h>
#include <linux/fs.h>
#include <linux/ctype.h>
#include <linux/slab.h>
#include <linux/pagemap.h>
#include <linux/vmalloc.h>
#include <linux/fb.h>
#include <linux/pci.h>
#include <linux/platform_device.h>
#include <linux/version.h>
#include <linux/io.h>
#include <linux/bug.h>
#include <linux/poll.h>
#include <linux/interrupt.h>
//#include <linux/android_pmem.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/clk.h>
#include <linux/time.h>
#include <linux/ktime.h>
#include <linux/completion.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
//#include <mach/irqs.h>
#include <mach/boardid.h>

//#include <mach/clk_name_interface.h>
#include "reg_ops.h"
#include "soc_ao_sctrl_interface.h"
#include "soc_pmctrl_interface.h"
#include "soc_sctrl_interface.h"
#include "soc_baseaddr_interface.h"
//#include "drv_regulator_user.h"

#include <trace/trace_kernel.h>
//#include <mach/gpio.h>
#include <linux/gpio.h>
#include "mini_cam_util.h"
#include "mini_cam_dbg.h"
#include "mini_k3_isp.h"
#include "mini_k3_ispv1.h"
#include "mini_k3_ispv1_afae.h"
#include "mini_k3_isp_io.h"
#include "mini_hwa_cam_tune.h"
#include "mini_hwa_cam_tune_common.h"
#include "mini_cam_log.h"
#include "camera_agent.h"

#define DEBUG_DEBUG 0

#ifdef  LOG_TAG
#undef LOG_TAG
#define LOG_TAG "K3_ISPV1"
#endif

#ifdef READ_BACK_RAW
/* the 0x3c771000 is K3 addr, can't use at balong platform */
#define RAW_PHYADDR 0x3c771000
#endif

#ifndef SCENE_NIGHT_MODE_FPS
/*FIXME: FPGA lower fps in dark than Asic*/

#define	SCENE_NIGHT_MODE_FPS			1//5
#endif

/* MACRO DEFINITION */

/* commond set done wait timeout*/
#ifndef WAIT_COMPLT_TIMEOUT
/*FPGA mcu will take longer time to response cmdset than Asic*/
#define WAIT_COMPLT_TIMEOUT         (7000)
//#define WAIT_COMPLT_TIMEOUT 1000
#endif
#define WAIT_ZOOM_CMD_TIMEOUT	(1000)
/* yuv down scale ratio = N/128 */
#define YUV_DOWN_SCALE_DIVIDEND	0x80
/* yuv up scale ratio = 256/M */
#define YUV_UP_SCALE_DIVIDEND	0x100

/* calc YUV down scale value*/
#define YUV_DOWN_VALUE(scale) \
	(((scale) * YUV_DOWN_SCALE_DIVIDEND) / YUV_SCALE_DIVIDEND)
/* calc YUV down scale value*/
#define YUV_UP_VALUE(scale) \
	(YUV_UP_SCALE_DIVIDEND * YUV_SCALE_DIVIDEND / (scale))

/* if capture framesize > 5M, we need use offline capture */
#ifdef CONFIG_MACH_TC45MSU3
#define IS_OFFLINE_BY_SIZE(w, h) ((w) * (h) >= (1296 * 972))	/* > quarter 5M */
#else
#define IS_OFFLINE_BY_SIZE(w, h) ((w) * (h) > (2592 * 1952))	/* > 5M */
#endif

/* calc bracket mode for value CMD_CAPTURE command set
 * [1]: 0 for 2 exposures, 1 for 3 exposures in bracket mode
 * [0]: 0 for normal, 1 for bracket mode
*/
#define	CALC_BRACKET_MODE(value, count) \
	do { \
		value = 0;			\
		if (count > 1)		\
			value = 1; 		\
		if (count == 3)		\
			value |= 2;		\
	} while (0)

/* Set input format bit array according MIPI1/MIPI2/DVP Type and if bypass isp */



#define CALC_ISP_IN_TYPE(fmt, sensor_type, is_bypass_isp) \
	do { \
		fmt = (is_bypass_isp) ? fmt & ~0x40 : fmt | 0x40; \
		switch (sensor_type) {	\
		case MIPI1:				\
			fmt = (fmt & 0xc7) | 0x08; break;	\
		case MIPI2:				\
			fmt = (fmt & 0xc7) | 0x10; break;	\
		default:				\
			fmt = (fmt & 0xc7);			\
			break;					\
		}					\
	} while (0)


/*
clk divider
Reg0x63023[3:0], or Reg0x63023[7:4]
* 0       {1'b0, 3'b000}
* 1       {1'b0, 3'b001}
* 2      {1'b0, 3'b010}
* 4      {1'b0, 3'b011}
* 6      {1'b1, 3'b000}   new
* 8      {1'b0, 3'b100}
* 10    {1'b1, 3'b001}    new
* 12    {1'b1, 3'b010}    new
* 14    {1'b1, 3'b011}    new
* 16    {1'b0, 3'b101}
* 18    {1'b1, 3'b100}    new
* 20    {1'b1, 3'b101}    new
* 22    {1'b1, 3'b110}    new
* 24    {1'b1, 3'b111}    new
* 26
* 28
* 30
* 32    {1'b0, 3'b110}
* 64    {1'b0, 3'b111}
*/
/*
 *  on FPGA borad, clk divider = 0x02
 *	       (or 0x03 to fix bugs on capture overflow, ).
 *		   on soc board, clk divider = 0x44
 *  clk divider
 *  Reg0x63023[3:0], or Reg0x63023[7:4]
 */
#if defined(CONFIG_MACH_TC45MSU3)
#define CLK_DIVIDER  0x03

	/* FIXME:
	   K3V2 of design-in version, isp clock is 131Mhz
	   clock divider is 8, mclk = 16.375M
	   mass-product version, isp clock is 160Mhz,
	   if it does not work, try change clock divider to 10.
	 */

#elif defined(CONFIG_MACH_HI6620SFT)

/*FIXME:FPGA OV8830 for isp sclk 20M Sensor Mclk 5M*/
//#ifdef CONFIG_HI6620_CAMERA_OV8830
//#define CLK_DIVIDER  0x44//0x33
//#else
#define CLK_DIVIDER  0x22
//#endif


#elif defined(CONFIG_ARCH_HI6620)
/* V9R1 CS isp clokc is 200Mhz, clock divider is 10, mclk = 20 */
#define CLK_DIVIDER  0x99
#endif

/* FIXME */
static u32 preview_ratio = EV_RATIO_DIVIDEND;
static u32 latest_preview_ratio = EV_RATIO_DIVIDEND;
static bool mini_burst_capture;
/* ISP INITIALIZE SEQUENCE */
const struct mini_isp_reg_t mini_isp_default_init_regs[] = {

};

/* FIXME need optimize
 *	this is isp register initial sequeuence for mipi camera
 *	default config:
 *	data interface:		MIPI(use MIPI1 channel)
 *	isp input format:	RAW10
 *	isp output format:	yuyv
 *	use I2C channel:	I2C1
 */
const struct mini_isp_reg_t mini_isp_mipi_init_regs1[] = {
	/* system initial */
	{0x63022, 0x84}, /*RAW10 input			*/
	{0x63023, 0x00}, /*sensor clk  4:/8  2:/2  8:/6 */
	{0x63800, 0x01},
	{0x63b34, 0x23}, /*overflow_dely_en*/
	{0x65800, 0x00},
	{0x65023, 0x41}, /*yuv dcw*/

	{0x1c174, 0x01}, /*y36721 set it as manual aec/agc at first.*/
	{0x1c139, 0x01}, /*AECAGC function write sensor enable      */
	{0x1c179, 0x00}, /*not hdr sensor                           */
	{0x1c528, 0x20}, /*pSensorDeviceID[0]                       */
	{0x1c529, 0x20},
	{0x1c52a, 0x09}, /*pSensorI2COption[0]*/
	{0x1c52b, 0x09},
	{0x1c52c, 0x35},
	{0x1c52d, 0x01},
	{0x1c52e, 0x35},
	{0x1c52f, 0x02},
	{0x1c530, 0x00},
	{0x1c531, 0x00},
	{0x1c532, 0x00},
	{0x1c533, 0x00},
	{0x1c534, 0x00},
	{0x1c535, 0x00},
	{0x1c536, 0x00},
	{0x1c537, 0x00},
	{0x1c538, 0x35},
	{0x1c539, 0x0a},
	{0x1c53a, 0x35},
	{0x1c53b, 0x0b},
	{0x1c53c, 0x00},
	{0x1c53d, 0x00},
	{0x1c53e, 0x00},
	{0x1c53f, 0x00},
	{0x1c540, 0x00},
	{0x1c541, 0x00},
	{0x1c542, 0x00},
	{0x1c543, 0x00},
	{0x1c55c, 0xff},
	{0x1c55d, 0xff},
	{0x1c55e, 0x00},
	{0x1c55f, 0x00},
	{0x1c560, 0x00},
	{0x1c561, 0x00},
	{0x1c562, 0xff},
	{0x1c563, 0xff},
	{0x1c564, 0x00},
	{0x1c565, 0x00},
	{0x1c566, 0x00},
	{0x1c567, 0x00},

	{0x60100, 0x01}, /*Software reset		*/
	{0x6301b, 0xf0}, /*isp clock enable             */
	{0x63025, 0x40}, /*clock divider                */
	{0x63c12, 0x01}, /*data type                    */
	{0x63c13, 0x22}, /*divider                      */
	{0x63c14, 0x01}, /*men_thre                     */
	{0x63c15, 0x53}, /*mem valid high&low number    */


	/* ISP TOP REG */
	{0x65000, 0x3f},
	{0x65001, 0x6f}, /*turn off local boost*/
	{0x65002, 0x9b},
	{0x65003, 0xff},
	{0x65004, 0x20},
	{0x65005, 0x52},
	{0x65006, 0x02},
	{0x65008, 0x00},
	{0x65009, 0x00},

	{0x1d998, 0x01}, //disable BLC auto activate.
};

/*	this is isp register initial sequeuence for dvp camera
 *	default config:
 *	data interface:		DVP
 *	isp input format:	RAW10
 *	isp output format:	yuyv
 *	use I2C channel:	I2C1
 */
const struct mini_isp_reg_t mini_isp_dvp_init_regs[] = {
	{0x60100, 0x01},
	/* frame out : dvp */
	{0x63108, 0x00},
	{0x63109, 0x00},
	{0x6301a, 0x70},
	{0x6301b, 0xf0},
	{0x63025, 0x40},
	/* isp input fomat : RAW10 */
	{0x63022, 0x84},
	/* isp output format : yuyv */
	{0x63b35, 0x04},

	/* cclk0 cclk2 enable */
	{0x63023, 0x0},

	{0x63400, 0x80},
	{0x63800, 0x01},

	/* yuv crop
	   {0x650f0, 0x00},
	   {0x650f1, 0x00},
	   {0x650f2, 0x00},
	   {0x650f3, 0x00},
	   {0x650f4, WIDTH_H},
	   {0x650f5, WIDTH_L},
	   {0x650f6, HEIGHT_H},
	   {0x650f7, HEIGHT_L},
	*/
	{0x65000, 0x0f},
	{0x65001, 0x6f},
	{0x65002, 0x83},
	{0x65003, 0xff},
	{0x65004, 0x20},
	{0x65005, 0x02},
	{0x65006, 0x02},
	{0x65008, 0x00},
	{0x65009, 0x08},

	{0x65800, 0x00},
	{0x65a00, 0x0b},
	{0x66500, 0x10},
	{0x66501, 0x01},
	{0x66502, 0x80},

	/* MCU control register */

	/* output image size to display
	   {0x1c134, WIDTH_H},
	   {0x1c135, WIDTH_L},
	   {0x1c136, HEIGHT_H},
	   {0x1c137, HEIGHT_L},
	 */
	{0x1c138, 0x02},
	{0x1c13d, 0x00},
	{0x1c13e, 0x00},
	{0x1c144, 0x88},
	{0x1c145, 0x00},


	{0x1c176, 0x03},
	{0x1c177, 0x48},
	{0x1c470, 0x01},
	{0x1c471, 0x00},
	{0x1c52a, 0x09},
	{0x1c52b, 0x09},
	{0x1c52c, 0x35},	/* pSensorAECAddr[0][0] */
	{0x1c52d, 0x01},
	{0x1c52e, 0x35},	/* pSensorAECAddr[0][1] */
	{0x1c52f, 0x02},
	{0x1c530, 0x00},	/* pSensorAECAddr[0][2] */
	{0x1c531, 0x00},
	{0x1c532, 0x00},	/* pSensorAECAddr[0][3] */
	{0x1c533, 0x00},
	{0x1c534, 0x00},	/* pSensorAECAddr[0][4] */
	{0x1c535, 0x00},
	{0x1c536, 0x00},	/* pSensorAECAddr[0][5] */
	{0x1c537, 0x00},
	{0x1c538, 0x35},	/* pSensorAECAddr[0][6] */
	{0x1c539, 0x0a},
	{0x1c53a, 0x35},	/* pSensorAECAddr[0][7] */
	{0x1c53b, 0x0b},
	{0x1c53c, 0x00},	/* pSensorAECAddr[0][8] */
	{0x1c53d, 0x00},
	{0x1c53e, 0x00},	/* pSensorAECAddr[0][9] */
	{0x1c53f, 0x00},
	{0x1c540, 0x00},	/* pSensorAECAddr[0][10] */
	{0x1c541, 0x00},
	{0x1c542, 0x00},	/* pSensorAECAddr[0][11] */
	{0x1c543, 0x00},
	{0x1c544, 0x00},
	{0x1c545, 0x00},
	{0x1c546, 0x00},
	{0x1c547, 0x00},
	{0x1c548, 0x00},
	{0x1c549, 0x00},
	{0x1c54a, 0x00},
	{0x1c54b, 0x00},
	{0x1c54c, 0x00},
	{0x1c54d, 0x00},
	{0x1c54e, 0x00},
	{0x1c54f, 0x00},
	{0x1c550, 0x00},
	{0x1c551, 0x00},
	{0x1c552, 0x00},
	{0x1c553, 0x00},
	{0x1c554, 0x00},
	{0x1c555, 0x00},
	{0x1c556, 0x00},
	{0x1c557, 0x00},
	{0x1c558, 0x00},
	{0x1c559, 0x00},
	{0x1c55a, 0x00},
	{0x1c55b, 0x00},
	{0x1c55c, 0xff},	/* pSensorAECMask[0][0] */
	{0x1c55d, 0xff},
	{0x1c55e, 0x00},
	{0x1c55f, 0x00},
	{0x1c560, 0x00},
	{0x1c561, 0x00},
	{0x1c562, 0xff},
	{0x1c563, 0xff},
	{0x1c564, 0x00},
	{0x1c565, 0x00},
	{0x1c566, 0x00},
	{0x1c567, 0x00},
	{0x1c568, 0x00},
	{0x1c569, 0x00},
	{0x1c56a, 0x00},
	{0x1c56b, 0x00},
	{0x1c56c, 0x00},
	{0x1c56d, 0x00},
	{0x1c56e, 0x00},
	{0x1c56f, 0x00},
	{0x1c570, 0x00},
	{0x1c571, 0x00},
	{0x1c572, 0x00},
	{0x1c573, 0x00},
	/* for reset sensor (hardware reset)
	   {0x63d61, 0x11},
	   {0x63d72, 0x11},
	   {0x63d74, 0x01},

	   * FIXME : this code control gpio to power and reset camera
	   *  sn_pwdn2_0 ---- pwdn
	   *  sn_rst_n1_0 ----reset
	   *
	 */

	/*
	   {0x6302f, 0x07},
	   {0x63031, 0x02},
	 */

	{0x1c4d6, 0x01},

	{0x66d71, 0x01},
	{0x66d72, 0x00},

	{0x66d71, 0x01},
	{0x66d72, 0x24},
	{0x66d73, 0x92},
	{0x63b34, 0x03},
	/* mem size
	   {0x63b36, WIDTH_H},
	   {0x63b37, WIDTH_L},
	   {0x63b38, WIDTH_H},
	   {0x63b39, WIDTH_L},
	   {0x63b3a, HEIGHT_H},
	   {0x63b3b, HEIGHT_L},
	 */
	{0x63b3d, 0xff},

	{0x1d998, 0x01}, //disable BLC auto activate.
};

/* GLOBAL VARIABLES */
static mini_isp_hw_controller 		ispv1_ctl;
mini_isp_hw_data_t 				mini_isp_hw_data;
static mini_isp_sensor_reg_controller 	ispv1_sensor_reg_ctl;
static void isr_do_tasklet(unsigned long data);

 /* point to global isp_data */
extern mini_k3_isp_data *mini_this_ispdata;

DECLARE_TASKLET(mini_isr_tasklet, isr_do_tasklet, (unsigned long)&(mini_isp_hw_data.irq_val));

/* format that supported by isp and camera sensor */

static u32 ispv1_sensor_pixfmt[2][6] = {
	{V4L2_PIX_FMT_NV21, V4L2_PIX_FMT_NV12, V4L2_PIX_FMT_YUYV, V4L2_PIX_FMT_YVU420,V4L2_PIX_FMT_YUV420,V4L2_PIX_FMT_INVALID},  /* for CS-chip */
	{V4L2_PIX_FMT_NV12, V4L2_PIX_FMT_YUYV, V4L2_PIX_FMT_YVU420,V4L2_PIX_FMT_YUV420, V4L2_PIX_FMT_INVALID},  /* for ES-chip */
};
static u32 mask_table[16] = {MASK_CMD_DONE_WRITEBACK_EXPO_GAIN, MASK_CMD_DONE_WRITEBACK_EXPO, MASK_CMD_DONE_WRITEBACK_GAIN,0, 0, 0, 0, 0, 0, 0, 0, 0,0,MASK_CMD_DONE_BRACKET_CAPTURE,MASK_CMD_DONE_FIRMWARE_DOWNLOAD,0};

/* FUNCTION DECLEARATION */
static int ispv1_hw_set_default(void);
static int wait_cmd_timeout(int cmd, int time_out);
static u16  ispv1_convert_input_fmt(u32 fmt);
static u16 ispv1_convert_output_fmt(u32 cmdset, u32 fmt);
static int __attribute__((unused)) k3_calc_stride(int width, int bpp);
static void ispv1_refresh_support_fmt(u32 **pixfmt, u32 *cnt);
static void ispv1_fill_fmt_info(struct v4l2_pix_format *fmt);
static void ispv1_disable_irq(void);
static void ispv1_enable_irq(void);
/*static int ispv1_update_zoom_setting(mini_pic_attr_t *pic_attr);*/
static int ispv1_set_zoom(u32 ratio, zoom_quality_t quality);
static int ispv1_offline_cmd(mini_pic_attr_t *pic_attr, u32 source_addr, u32 target_addr);
static int ispv1_capture_cmd(mini_pic_attr_t *pic_attr, u32 phyaddr, u32 count, int *ev, mini_camera_sensor *sensor, bool flash_on, camera_scene scene);
static int ispv1_start_capture_raw_with_preview_cmd(mini_pic_attr_t *pic_attr, mini_buffer_arr_t *buf_arr);
static int ispv1_start_capture_yuv_with_preview_cmd(mini_pic_attr_t *pic_attr, mini_buffer_arr_t *buf_arr);
#if 0
static int ispv1_suspend_capture_with_preview_cmd(void);
static int ispv1_resume_capture_with_preview_cmd(mini_pic_attr_t *pic_attr, mini_buffer_arr_t *buf_arr);
#endif
static int ispv1_stop_capture_with_preview_cmd(void);
static void calc_scale_param(mini_pic_attr_t *pic_attr, u32* dcw_e, u16* value, u32* up_nscale, u32* down_nscale);
static void calc_scale_param2(mini_pic_attr_t *pic_attr, u32* dcw_e, u16* value, u32* up_nscale, u32* down_nscale);
static int ispv1_preview_cmd(mini_pic_attr_t *pic_attr, mini_camera_sensor *sensor, bool cold_boot, camera_scene scene);
static int ispv1_start_preview(mini_pic_attr_t *pic_attr, mini_camera_sensor *sensor, bool cold_boot, camera_scene scene);
static int ispv1_start_process(mini_pic_attr_t *pic_attr, u8 mode, mini_buffer_arr_t *ipp_buf_arr);
static int ispv1_start_capture(mini_pic_attr_t *pic_attr, mini_camera_sensor *sensor, int *ev, bool flash_on, camera_scene scene,	mini_buffer_arr_t *buf_arr);
static int ispv1_stop_preview(void);
static int ispv1_stop_capture(void);
static int ispv1_stop_process(u8 mode);
static int ispv1_update_addr(u32 phyaddr,u32 statphyaddr,mini_uv_offset *puvoffset);
static int ispv1_check_config(struct v4l2_pix_format *pixfmt, camera_state state);
static void ispv1_set_i2c(struct mini_i2c_t *i2c);
static void ispv1_hw_init_regs(data_interface_t sensor_type);
static int ispv1_drop_handler(u8 buf_sel, u32 addr,u32 stats_addr, camera_state state);
static int ispv1_write_start_handler(camera_state state);
static int ispv1_overflow_handler(camera_state state);
static int ispv1_frame_done_handler(camera_state state);
#if 0
static int ispv1_zsl_frame_done_handler(void);
#endif
static irqreturn_t ispv1_isr(int irq, void *dev_id);
static int ispv1_hw_set_default (void);
static int ispv1_hw_init(struct platform_device *pdev, mini_data_queue_t* data_queue);
#if 0
static void ispv1_set_process_mode(u32 w, u32 h);
#else
static void ispv1_set_process_mode(capture_type process_mode);
/* end */
#endif
static isp_process_mode_t ispv1_get_process_mode(void);
static void ispv1_hw_deinit(void);
static mini_camera_frame_buf *ispv1_move_queue_element(struct list_head *source, u8 source_flag,
	struct list_head *target, u8 target_flag);
static mini_camera_frame_buf *ispv1_del_queue_element(struct list_head *list, u8 source_flag);

static int ispv1_write_sensor_byte(i2c_index_t index, u8 i2c_addr, u16 reg, u16 val, i2c_length length, u8 mask, i2c_length addr_len);
/* last modified for new mechanism of flash */
static bool ispv1_is_need_flash(mini_camera_sensor *sensor);
 #ifdef SUPPORT_ZSL_FLASH
static void zsl_sof_start_flash(void);
static void zsl_wait_to_start_capture_with_flash(void);
static int ispv1_set_ratio_cmd(u16 ratio);
static u32 zsl_flash_process=0;
 #endif
/*
 **************************************************************************
 * FunctionName: k3_calc_stride;
 * Description : calc stride
 * Input       : width,
 * bpp : bit per pixel
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int __attribute__((unused)) k3_calc_stride(int width, int bpp)
{
	int n = 0;
	int stride = 0;

#define AlignUp(val, al)    (((val) + ((al)-1)) & ~((al)-1))

	n = AlignUp((width * bpp) / 8, 64);
	stride = ((n / 64) % 2 == 0) ? (n + 64) : n;

	return stride;
}
static inline mini_effect_params *get_effect_ptr(void)
{
	return mini_this_ispdata->sensor->effect;
}

/*
 **************************************************************************
 * FunctionName: wait_cmd_timeout;
 * Description : wait for command set timeout;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int wait_cmd_timeout(int cmd, int time_out)
{
    struct semaphore    *sem    = NULL;
	long 			    jiffies = 0;

	jiffies = msecs_to_jiffies(time_out);

	if (CMD_CAPTURE_WITH_PREVIEW == cmd){
	    sem = &mini_isp_hw_data.sem_cap_raw_cmd_done;
	} else if (CMD_PROC_IMG_WITH_PREVIEW == cmd){
	    sem = &mini_isp_hw_data.sem_proc_img_cmd_done;
	} else {
	    sem = &mini_isp_hw_data.sem_cmd_done;
	}

	if (down_timeout(sem, jiffies)) {
		print_error("MCU not respond when do cmd[%d]! REG_ISP_INT_EN = 0x%0x.\n",
			cmd, GETREG8(REG_ISP_INT_EN));
		return -ETIME;
	} else if (cmd != CMD_FIRMWARE_DOWNLOAD && COMMAND_SET_SUCCESS != GETREG8(COMMAND_RESULT)) {
		print_error("Set failed when do cmd[%d], err = %d.!", cmd, GETREG8(COMMAND_RESULT));
		return -EINVAL;
	} else if (cmd != mini_isp_hw_data.command_set_id) {
		print_error("COMMAND_FINISHED[%d] not is cmd = %d\n", mini_isp_hw_data.command_set_id, cmd);
		return -EINVAL;
	} else {
		print_info("COMMAND_FINISHED, cmdid[%d]", cmd);
		return 0;
	}
}
/*
 **************************************************************************
 * FunctionName: ispv1_convert_input_fmt;
 * Description : convert input fmt to ispv1 command set parameters;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static u16 ispv1_convert_input_fmt(u32 fmt)
{
	u16 isp_fmt = 0;
	/* fmt [2:0]:
		 * 0 for RAW8,
	 * 1 for RAW10,
	 * 2 for RAW12,
	 * 3 for RAW14,
	 * 4 for YUV422,
	 * 5 for RGB565,
	 * 6 for RGB888
	 */

	switch (fmt) {
	case V4L2_PIX_FMT_RAW8:
		isp_fmt = 0;
		break;
	case V4L2_PIX_FMT_RAW10:
		isp_fmt = 1;
		break;
	case V4L2_PIX_FMT_RAW12:
		isp_fmt = 2;
		break;
	case V4L2_PIX_FMT_RAW14:
		isp_fmt = 3;
		break;
	case V4L2_PIX_FMT_YUYV:
		isp_fmt = 4;
		break;
	default:
		print_error("Bad format: %d", fmt);
		break;
	}

	return isp_fmt;
}


/*
 **************************************************************************
 * FunctionName: ispv1_config_idi;
 * Description : config idi receive capability depend on input fmt;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ispv1_config_idi(u32 fmt, bool bypass_isp, u8 *reg3c13, u8 *reg3c15)
{
	u8 use_isp = 1 - (u8)bypass_isp;

	/* Format	Data Path	3C13[5:4]	3C15[7:0]
	 *   		ISP process	0x2		0x11
	 * RAW8		Bypass ISP	0x0		0x11
	 *	    	ISP process	0x2		0x53
	 * RAW10	Bypass ISP	0x0		0x11
	 *	    	ISP process	0x2		0x31
	 * RAW12	Bypass ISP	0x0		0x11
	 *	    	ISP process	0x1		0x11
	 *YUV422/RGB565 Bypass ISP	0x0		0x11
	 * RGB888	Bypass ISP	0x0		0x11
	*/

	switch (fmt) {
	case V4L2_PIX_FMT_RAW8:
		*reg3c13 = GETREG8(REG_ISP_MEM_CTRL2) & 0xcf;
		*reg3c13 |= (0x2 * use_isp) << 4;
		*reg3c15 = 0x11;
		break;
	case V4L2_PIX_FMT_RAW10:
		*reg3c13 = GETREG8(REG_ISP_MEM_CTRL2) & 0xcf;
		*reg3c13 |= (0x2 * use_isp) << 4;
		*reg3c15 = 0x11 | 0x42*use_isp;
		break;
	case V4L2_PIX_FMT_RAW12:
		*reg3c13 = GETREG8(REG_ISP_MEM_CTRL2) & 0xcf;
		*reg3c13 |= (0x2 * use_isp) << 4;
		*reg3c15 = 0x11 | 0x20 * use_isp;
		break;
	case V4L2_PIX_FMT_YUYV:
		*reg3c13 = GETREG8(REG_ISP_MEM_CTRL2) & 0xcf;
		*reg3c13 |= (0x1 * use_isp) << 4;
		*reg3c15 = 0x11;
		break;
	default:
		print_error("Bad format: %d", fmt);
		break;
	}
	print_info("reg3c13[%#x], reg3c15[%#x]", *reg3c13, *reg3c15);
}

/*
 **************************************************************************
 * FunctionName: ispv1_convert_output_fmt;
 * Description : convert output fmt to ispv1 command set parameters;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static u16 ispv1_convert_output_fmt(u32 cmdset, u32 fmt)
{
	u16 isp_fmt = 0;

	print_debug("ispv1_convert_output_fmt:cmdset=%d",cmdset);

	switch (fmt) {
	case V4L2_PIX_FMT_YUYV:
		print_debug("fmt=yuyv");
		if (cmdset == CMD_SET_FORMAT || cmdset == CMD_CAPTURE || cmdset == CMD_OFFLINE_PROCESS)
        /* end */
			//isp_fmt = 4;
			isp_fmt = 0x40;
		else
			isp_fmt = 0;
		break;
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
		print_debug("NV12 or NV21");
		if (cmdset == CMD_SET_FORMAT || cmdset == CMD_CAPTURE || cmdset == CMD_OFFLINE_PROCESS)
        /* end */
			//isp_fmt = 5;
			isp_fmt = 0x50;
		else
			isp_fmt = 1;
		break;
    case V4L2_PIX_FMT_YUV420:
		print_debug("yuv420");
		if (cmdset == CMD_SET_FORMAT || cmdset == CMD_CAPTURE || cmdset == CMD_OFFLINE_PROCESS)
        /* end */
			isp_fmt = 0x80;
		else
			isp_fmt = 1;
		break;

	default:
		print_error("Bad format: %d", fmt);
		isp_fmt = 1;
		break;
	}


	return isp_fmt;
}

/*
 **************************************************************************
 * FunctionName: ispv1_convert_output_fmt2;
 * Description : convert output fmt to ispv1 command set parameters;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static u16 ispv1_convert_output_fmt2(u32 cmdset, u32 fmt)
{
	u16 isp_fmt = 0;
	print_debug("ispv1_convert_output_fmt2:cmdset=%d",cmdset);

	switch (fmt) {
	case V4L2_PIX_FMT_YUYV:
		print_debug("fmt=yuyv");
		if (cmdset == CMD_SET_FORMAT || cmdset == CMD_CAPTURE)
			//isp_fmt = 4;
			isp_fmt = 0x44;
		else
			isp_fmt = 0;
		break;
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
		print_debug("fmt=NV12 or NV21");
		if (cmdset == CMD_SET_FORMAT || cmdset == CMD_CAPTURE)
			//isp_fmt = 5;
			isp_fmt = 0x55;
		else
			isp_fmt = 1;
		break;
    case V4L2_PIX_FMT_YUV420:
		print_info("fmt=YUV420");
		if (cmdset == CMD_SET_FORMAT || cmdset == CMD_CAPTURE)
			isp_fmt = 0x88;
		else
			isp_fmt = 1;
		break;
	default:
		print_error("Bad format: %d", fmt);
		isp_fmt = 1;
		break;
	}

	return isp_fmt;
}

#if 0
static void ispv1_set_process_mode(u32 w, u32 h)
{
	/* mini_isp_hw_data.process_mode = (IS_OFFLINE_BY_SIZE(w, h)) ? ISP_CAPTURE_OFFLINE : ISP_CAPTURE_ONLINE;*/

#ifdef OVISP_OFFLINE_MODE
	mini_isp_hw_data.process_mode = ISP_CAPTURE_OFFLINE;
#else
	mini_isp_hw_data.process_mode = ISP_CAPTURE_ONLINE;
#endif
}
#else
static void ispv1_set_process_mode(capture_type process_mode)
{
    print_info("enter %s", __FUNCTION__);
    if(CAPTURE_OFFLINE == process_mode)
    {
        mini_isp_hw_data.process_mode = ISP_CAPTURE_OFFLINE;
        print_info("CAPTURE_OFFLINE");
    }
    else if(CAPTURE_ONLINE == process_mode)
    {
        mini_isp_hw_data.process_mode = ISP_CAPTURE_ONLINE;
        print_info("CAPTURE_ONLINE");
    }
    else
    {
        print_error("invalid type:%d.", process_mode);
    }
}

#endif
static isp_process_mode_t ispv1_get_process_mode(void)
{
	return mini_isp_hw_data.process_mode;
}
/* end */

/*
 **************************************************************************
 * FunctionName: ispv1_refresh_support_fmt;
 * Description : Get formats that supported by isp and camera sensor;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ispv1_refresh_support_fmt(u32 **pixfmt, u32 *cnt)
{
	u32 *pixformat_array;
	unsigned int chip_id;
	print_debug("enter %s", __func__);

	chip_id = get_chipid();
	if (chip_id == CS_CHIP_ID) {
		pixformat_array = ispv1_sensor_pixfmt[0];
	} else {
		pixformat_array = ispv1_sensor_pixfmt[1];
	}

	*cnt = 0;
	while (pixformat_array[*cnt] != V4L2_PIX_FMT_INVALID)
		(*cnt)++;
	*pixfmt = pixformat_array;

	print_debug("%s: cnt=%d", __func__, *cnt);
}

/*
 **************************************************************************
 * FunctionName: ispv1_set_auto_flash;
 * Description : enable or disable auto flash control;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ispv1_set_auto_flash(int status, camera_flash flash_mode)
{
	if (status == 1) {
		print_debug("---enable auto flash control---");
		/*FIXME:*/
		SETREG8(0x1c4dc, 0x1);
		SETREG8(0x1c4dd, 0x2);
	} else if (status == 0) {
		print_debug("---disable auto flash control---");
		/*FIXME:*/
		SETREG8(0x1c4dc, 0x0);
	}
	mini_isp_hw_data.flash_mode = flash_mode;
}


static bool ispv1_is_need_flash(mini_camera_sensor *sensor)
{
	mini_aec_data_t ae_data;
	u32 target_y_low = GETREG8(REG_ISP_TARGET_Y_LOW);
	bool ret;

	ae_data.lum = get_current_y();
	ae_data.gain = get_writeback_gain();

	if (mini_ae_is_need_flash(sensor, &ae_data, target_y_low) == true)
		ret = true;
	else
		ret = false;

	return ret;
}

/*
 **************************************************************************
 * FunctionName: mini_ispv1_set_aecagc_mode;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void mini_ispv1_set_aecagc_mode(aecagc_mode_t mode)
{
	mode=1;
	SETREG8(REG_ISP_AECAGC_MANUAL_ENABLE, mode);
}

void mini_ispv1_set_awb_mode(awb_mode_t mode)
{
	mode=1;
	SETREG8(REG_ISP_AWB_MANUAL_ENABLE, mode);
}

static int ispv1_cold_boot_set(mini_camera_sensor *sensor)
{
	u32 expo, gain;
	int level;
	u16 full_fps, basic_vts, step, frame_index;
	u32 vts = 0;

	/* config sensor gain and exposure. */
	expo = get_writeback_expo();
	gain = get_writeback_gain();

	if ((sensor->set_gain) && (gain < 0xff))
		sensor->set_gain(gain);
	if (sensor->set_exposure)
		sensor->set_exposure(expo);

	/* config sensor vts. */
	level = mini_ispv1_get_frame_rate_level();
	if ((CAMERA_USE_K3ISP == sensor->isp_location)	&& (NULL != sensor->set_vts)) {
		frame_index = sensor->preview_frmsize_index;
		basic_vts = sensor->frmsize_list[frame_index].vts;
		full_fps = sensor->frmsize_list[frame_index].fps;
		step = 1;

		sensor->fps = full_fps - level * step;
		vts = basic_vts * full_fps / sensor->fps;
		sensor->set_vts(vts);
	}

	print_info("%s:expo 0x%x, gain 0x%x, level %d, vts 0x%x", __func__, expo, gain, level, vts);

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ispv1_fill_fmt_info;
 * Description : Fill v4l2_format according to pixelformat;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ispv1_fill_fmt_info(struct v4l2_pix_format *fmt)
{
	print_debug("enter %s", __func__);
	switch (fmt->pixelformat) {
	case V4L2_PIX_FMT_RAW8:
	case V4L2_PIX_FMT_RAW10:
	case V4L2_PIX_FMT_RAW12:
		/* yuv422(packet) */
	case V4L2_PIX_FMT_YUYV:
		{
			fmt->bytesperline = fmt->width * mini_bits_per_pixel(fmt->pixelformat)/8;
			fmt->sizeimage = fmt->bytesperline * fmt->height;
			break;
		}
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
    case V4L2_PIX_FMT_YUV420:
		{
			fmt->bytesperline = fmt->width;
			fmt->sizeimage = fmt->width * fmt->height
			    * (mini_bits_per_pixel(fmt->pixelformat)) / 8;
			break;
		}

	default:
		{
			print_error("invalid pix format [0x%08X]", fmt->pixelformat);
			return;
		}
	}
}

/*
 **************************************************************************
 * FunctionName: ispv1_move_queue_element;
 * Description : move one elem from a queue to another;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : the elem moved;
 * Other       : NA;
 **************************************************************************
 */
static mini_camera_frame_buf *ispv1_move_queue_element(struct list_head *source, u8 source_flag,
	struct list_head *target, u8 target_flag)
{
	unsigned long lock_flags;
	mini_camera_frame_buf *frame = NULL;

	spin_lock_irqsave(&mini_isp_hw_data.data_queue_ref->queue_lock, lock_flags);
	if (!list_empty(source)) {
		frame = list_entry(source->next, mini_camera_frame_buf, queue);
		mini_del_from_queue(frame, source_flag);
		mini_add_to_queue(frame, target, target_flag);
	} else {
		print_error("queue empty state:%d, queue flag %d, line=%d", mini_isp_hw_data.cur_state, source_flag, __LINE__);
	}
	spin_unlock_irqrestore(&mini_isp_hw_data.data_queue_ref->queue_lock, lock_flags);
	return frame;
}

/*
 **************************************************************************
 * FunctionName: ispv1_move_queue_element;
 * Description : delete one elem from a queue
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : the elem deleted;
 * Other       : NA;
 **************************************************************************
 */
static mini_camera_frame_buf *ispv1_del_queue_element(struct list_head *list, u8 flag)
{
	unsigned long lock_flags;
	mini_camera_frame_buf *frame = NULL;

	spin_lock_irqsave(&mini_isp_hw_data.data_queue_ref->queue_lock, lock_flags);
	if (!list_empty(list)) {
		frame = list_entry(list->next, mini_camera_frame_buf, queue);
		 mini_del_from_queue(frame, flag);
	} else {
		print_error("queue empty , queue flag %d", flag);
	}
	spin_unlock_irqrestore(&mini_isp_hw_data.data_queue_ref->queue_lock, lock_flags);
	return frame;
}

static int ispv1_write_i2c_buf(const struct _mini_sensor_reg_t *addr, u8 num, u8 start, i2c_length len)
{
	int i = 0;
	if(len == I2C_8BIT) {
		for (i = 0; i < num; i++) {
			SETREG8((COMMAND_BUFFER + 0 + 4 * (i + start)), ((addr[i].subaddr & 0xff00)>>8));
			SETREG8((COMMAND_BUFFER + 1 + 4 * (i + start)), (addr[i].subaddr & 0xff));
			SETREG8((COMMAND_BUFFER + 2 + 4 * (i + start)), addr[i].value);
			SETREG8((COMMAND_BUFFER + 3 + 4 * (i + start)), ~(addr[i].mask));
		}
	} else if (len == I2C_16BIT) {
		for (i = 0; i < num; i++) {
			SETREG8((COMMAND_BUFFER + 0 + 4 * (i + start)), ((addr[i].subaddr & 0xff00)>>8));
			SETREG8((COMMAND_BUFFER + 1 + 4 * (i + start)), (addr[i].subaddr & 0xff));
			SETREG8((COMMAND_BUFFER + 2 + 4 * (i + start)), ((addr[i].value & 0xff00) >>8));
			SETREG8((COMMAND_BUFFER + 3 + 4 * (i + start)), (addr[i].value & 0xff));
		}
	} else {
		print_error("the length do not support");
	}

	return 0;
}


/*
 **************************************************************************
 * FunctionName: ispv1_clear_irq;
 * Description : Enable or disable interrupt(s) that used by isp;
 * Input       : mask, bits to set;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ispv1_disable_irq(void)
{
    //SETREG8(REG_ISP_INT_EN, MASK_CMDSET_INT_ENABLE | MASK_MAC_INT_ENABLE); /* CMD_SET MAC_INT int reserved */
    SETREG8(REG_ISP_INT_EN, 0); /* Disable all INT */

	SETREG8(REG_ISP_MAC_INT_EN_H, 0x00);
	SETREG8(REG_ISP_MAC_INT_EN_L, 0x00);
	SETREG8(REG_BASE_ADDR_READY, 0);
}

/*
 **************************************************************************
 * FunctionName: ispv1_enable_irq;
 * Description : Enable or disable interrupt(s) that used by isp;
 * Input       : mask, bits to set;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ispv1_enable_irq(void)
{
	SETREG8(REG_ISP_INT_EN,
		MASK_EOF_INT_ENABLE | MASK_CMDSET_INT_ENABLE | MASK_MAC_INT_ENABLE);
	SETREG8(REG_ISP_MAC_INT_EN_H, ISP_MAC_INT_H);
	SETREG8(REG_ISP_MAC_INT_EN_L, ISP_MAC_INT_L);
}

/*
 **************************************************************************
 * FunctionName: ispv1_update_zoom_setting;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
#if 0
static int ispv1_update_zoom_setting(mini_pic_attr_t *pic_attr)
{
	u32 raw_dcw = 0;
	u32 yuv_dcw = 0;
	u32 raw_dcw_e = 0;
	u32 yuv_dcw_e = 0;
	u32 yuv_nscale_up = 0;
	u32 yuv_nscale_down = 0;

	print_debug("enter %s", __func__);
	raw_dcw = pic_attr->raw_scale_down;
	yuv_dcw = pic_attr->yuv_dcw;

	/* chage scale to exponent value */
	while ((raw_dcw / 2) != 0) {
		raw_dcw_e++;
		raw_dcw /= 2;
	}
	while ((yuv_dcw / 2) != 0) {
		yuv_dcw_e++;
		yuv_dcw /= 2;
	}

	yuv_nscale_down = YUV_SCALE_DIVIDEND * YUV_DOWN_SCALE_DIVIDEND / pic_attr->yuv_down_scale_nscale;
	yuv_nscale_up = pic_attr->yuv_up_scale_nscale * YUV_UP_SCALE_DIVIDEND / YUV_SCALE_DIVIDEND;

	print_debug("yuv_nscale_down=%d, yuv_nscale_up=%d, raw_dcw=%d, raw_dcw_e=%d, yuv_dcw_e=%d, yuv_dcw=%d",
		yuv_nscale_down, yuv_nscale_up, raw_dcw, raw_dcw_e, yuv_dcw_e, yuv_dcw);
	/*
	 *print_debug("yuv_in_w=%d", pic_attr->yuv_in_width);
	 *print_debug("yuv_in_h=%d", pic_attr->yuv_in_height);
	 *print_debug("crop_w=%d", pic_attr->crop_width);
	 *print_debug("crop_h=%d", pic_attr->crop_height);
	 *print_debug("out_w=%d", pic_attr->out_width);
	 *print_debug("out_h=%d", pic_attr->out_height);
	 */

	/* disable frame start interrupt */
	/* SETREG8(0x63b53, GETREG8(0x63b53)&(~0x01)); */
	REG_SET_RAW_DCW_ENABLE(raw_dcw > 1);
	REG_SET_YUV_SCALE_UP_ENABLE(YUV_SCALE_DIVIDEND > pic_attr->yuv_up_scale_nscale);

	REG_SET_ISP_IN_SIZE(pic_attr->in_width, pic_attr->in_height);

	REG_SET_RAW_DCW_RATIO(raw_dcw_e);
	REG_SET_SCALE_OUT_SIZE(pic_attr->yuv_in_width, pic_attr->yuv_in_height);

	REG_SET_YUV_CROP_POSE(pic_attr->crop_x, pic_attr->crop_y);
	REG_SET_YUV_CROP_SIZE(pic_attr->crop_width, pic_attr->crop_height);

	REG_SET_YUV_DCW_RATIO(yuv_dcw_e, yuv_dcw_e);
	REG_SET_YUV_DOWN_NSCALE(yuv_nscale_down, yuv_nscale_down);
	REG_SET_YUV_UP_NSCALE(yuv_nscale_up, yuv_nscale_up);
	REG_SET_ISP_OUT_SIZE(pic_attr->out_width, pic_attr->out_height);

	/* enable frame start interrupt */
	/* SETREG8(0x63b53, GETREG8(0x63b53)|(0x01)); */
	return 0;
}
#endif
/*
 **************************************************************************
 * FunctionName: ispv1_set_zoom;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ispv1_set_zoom(u32 zoom, zoom_quality_t quality)
{
	int ret = 0;
	u32 ratio;

	print_debug("%s: zoom = 0x%x", __func__, zoom);

    /* set preview zoom */
	ratio = isp_zoom_to_ratio(zoom, mini_this_ispdata->video_stab);
	SETREG8(COMMAND_REG1, quality);
	SETREG16(COMMAND_REG2, ratio);
	SETREG16(COMMAND_REG4, ratio);

    /* set capture yuv stream zoom */
    if((CAMERA_ZSL_ON == mini_this_ispdata->zsl_ctrl.zsl_state)
    && (CAMERA_ZSL_ONLINE == mini_this_ispdata->zsl_ctrl.zsl_proc_mode))
    {
        print_info("set capture yuv zoom.");
	    ratio = isp_zoom_to_ratio(zoom, false);
    	SETREG8(COMMAND_REG6, CAP_YUV_ZOOM_ENABLE | CAP_YUV_ZOOM_HIGH_QUALITY_MODE);
    	SETREG16(COMMAND_REG7, ratio);
    	SETREG16(COMMAND_REG9, ratio);
	}

	SETREG8(COMMAND_REG0, CMD_ZOOM_IN_MODE);
	ret = wait_cmd_timeout(CMD_ZOOM_IN_MODE, WAIT_ZOOM_CMD_TIMEOUT);
    //mini_dump_ispzyk_reg();

	return ret;
}

static void ispv1_get_yuv_crop_rect(mini_crop_rect_s *rect)
{
	GETREG16(REG_ISP_YUV_CROP_WIDTH, rect->crop_width);
	GETREG16(REG_ISP_YUV_CROP_HEIGHT, rect->crop_height);

	rect->crop_width &= 0x1FFF;
	rect->crop_height &= 0x0FFF;
	rect->ori_width = mini_this_ispdata->pic_attr[STATE_PREVIEW].in_width;
	rect->ori_height= mini_this_ispdata->pic_attr[STATE_PREVIEW].in_height;
}
static void ispv1_set_yuv_crop_pos(int point)
{
	mini_this_ispdata->next_crop_pos = point;
}

void mini_ispv1_refresh_yuv_crop_pos(void)
{
	int x, y;
	print_debug("%s, 0x%08x", __func__, mini_this_ispdata->next_crop_pos);

	x = mini_this_ispdata->next_crop_pos >> 16;
	y = mini_this_ispdata->next_crop_pos & 0x0000FFFF;

    x = (x) & (~3);
    y = (y) & (~3);

	SETREG16(REG_ISP_YUV_CROP_LEFT, x);
	SETREG16(REG_ISP_YUV_CROP_TOP, y);
	mini_this_ispdata->cur_crop_pos = mini_this_ispdata->next_crop_pos;
}




int mini_ispv1_get_fps(mini_camera_sensor *sensor, camera_fps fps)
{
	int ret = 0;

	if (CAMERA_FPS_MAX == fps) {
		ret = sensor->fps_max;
	} else {
		ret = sensor->fps_min;
	}

	return ret;
}

int mini_ispv1_set_fps(mini_camera_sensor *sensor, camera_fps fps, u8 value)
{
	if (CAMERA_FPS_MAX == fps) {
		sensor->fps_max = value;
		mini_isp_hw_data.fps_max = value;
	} else if (CAMERA_FPS_MIN == fps) {
		sensor->fps_min = value;
		mini_isp_hw_data.fps_min = value;
	} else {
		mini_isp_hw_data.fps_mid = value;
	}

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ispv1_hardware_update_addr;
 * Description : update address registers;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void ispv1_hardware_update_addr(u32 phyaddr, u32 statphyaddr,mini_uv_offset *puvoffset, char buf_select)
{
	WARN_ON(BUF_LEFT != buf_select && BUF_RIGHT != buf_select);

    if ((0 == phyaddr) || (NULL == puvoffset)){
        print_error("%s:null ptr.phyaddr=%p.statphyaddr=%p.puvoffset=%p.",phyaddr,statphyaddr,puvoffset);
        return;
    }

	if (BUF_LEFT == buf_select) {
		/* print_debug("Trigger Buffer 0, phyaddr=%#x", phyaddr); */
		//print_info("phyaddr=0x%x,uoffset=%d.",phyaddr, puvoffset->uoffset);
		REG_SET_ADDR(REG_BASE_ADDR0_Y, REG_BASE_ADDR0_UV, phyaddr, (phyaddr + puvoffset->uoffset));
		REG_SET_ADDR_STAT(REG_SONY_STATS_BASE_ADDR0, statphyaddr);
		SETREG8(REG_BASE_ADDR_READY, WRITE_ADDR0_READY | GETREG8(REG_BASE_ADDR_READY));
	} else {
		/* print_debug("Trigger Buffer 1, phyaddr=%#x", phyaddr); */
		//print_info("phyaddr=0x%x,uoffset=%d.",phyaddr, puvoffset->uoffset);
		REG_SET_ADDR(REG_BASE_ADDR1_Y, REG_BASE_ADDR1_UV, phyaddr, (phyaddr + puvoffset->uoffset));
		REG_SET_ADDR_STAT(REG_SONY_STATS_BASE_ADDR1, statphyaddr);
		SETREG8(REG_BASE_ADDR_READY, WRITE_ADDR1_READY | GETREG8(REG_BASE_ADDR_READY));
	}
}

/*
 **************************************************************************
 * FunctionName: ispv1_zsl_update_addr;
 * Description : update address registers;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void ispv1_zsl_update_addr(u32 out_fmt,u32 phyaddr,mini_uv_offset *puvoffset)
{
    switch(out_fmt){
        case V4L2_PIX_FMT_NV12:
            SETREG32(ISP_MAC_OUTPUT_ADDR4, phyaddr);
            SETREG32(ISP_MAC_OUTPUT_ADDR5, phyaddr + puvoffset->uoffset);
            break;
        case V4L2_PIX_FMT_NV21:
            SETREG32(ISP_MAC_OUTPUT_ADDR4, phyaddr);
            SETREG32(ISP_MAC_OUTPUT_ADDR5, phyaddr + puvoffset->voffset);
            break;
        case V4L2_PIX_FMT_YUYV:
            SETREG32(ISP_MAC_OUTPUT_ADDR4, phyaddr);
            break;
        case V4L2_PIX_FMT_YUV420:
            SETREG32(ISP_MAC_OUTPUT_ADDR4, phyaddr);
            SETREG32(ISP_MAC_OUTPUT_ADDR5, phyaddr + puvoffset->uoffset);
            SETREG32(ISP_MAC_OUTPUT_ADDR6, phyaddr + puvoffset->voffset);
            break;
        default:
            print_error("%s:unknown pic_attr->out_fmt.",__func__);
    }

}

/*
 **************************************************************************
 * FunctionName: ispv1_hdr_cmd;
 * Description : hdr cmd set;
 * Input       : source_addr:mac in addr,   target_addr:mac out addr;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_hdr_cmd(mini_pic_attr_t *pic_attr, u32 addr_long, u32 addr_short, u32 target_addr)
{

#if 0
	/*u32 value = 0;
	u32 dcw_e = 0;
	u32 up_nscale = 0;
	u32 down_nscale = 0;*/
	u8 in_fmt = 0;
	u8 out_fmt = 0;
	u16 long_exposure = 0;
	u16 short_exposure = 0;
	u16 long_gain = 0;
	u16 short_gain = 0;

	in_fmt = ispv1_convert_input_fmt(pic_attr->in_fmt);
	out_fmt = ispv1_convert_output_fmt(CMD_FULL_SZIE_HDR, pic_attr->out_fmt);
	/*calc_scale_param(pic_attr, &dcw_e, &value, &up_nscale, &down_nscale);*/

	SETREG8(REG_ISP_INPUT_CHANNEL, ISP_INPUT_CHANNEL_MAC);
	SETREG8(ISP_HDR_PROCESS_CONTROL, 0x04);

	REG_SET_BYTESWITCH(true);
	HDR_GET_EXPOSURE_AND_GAIN(long_exposure, short_exposure, long_gain, short_gain);

	CMD_SET_HDR_READ_MEM_STRIDE(pic_attr->in_width);
	CMD_SET_HDR_IN_SIZE(in_fmt, pic_attr->in_width, pic_attr->in_height);
	CMD_SET_HDR_OUT_SIZE(out_fmt, pic_attr->out_width, pic_attr->out_height);
	CMD_SET_HDR_WRITE_MEME_STRIDE(pic_attr->out_stride);

	/* offline hdr
	CMD_SET_HDR_ISP_FUNCTION_CTRL(value);
	CMD_SET_HDR_SCALE_DOWN_RATIO_1(dcw_e, dcw_e);
	CMD_SET_HDR_SCALE_DOWN_RATIO_2(down_nscale, down_nscale);
	CMD_SET_HDR_SCALE_UP_RATIO(up_nscale, up_nscale);
	CMD_SET_HDR_YUV_CROP_START_POS(pic_attr->crop_x, pic_attr->crop_y);
	CMD_SET_HDR_YUV_CROP_SIZE(pic_attr->crop_width, pic_attr->crop_height);
	*/

	CMD_SET_HDR_OUT_BASE_ADDR(target_addr, target_addr + pic_attr->out_stride * pic_attr->out_height);
	CMD_SET_HDR_EXPOSURE_AND_GAIN(long_exposure, short_exposure, long_gain, short_gain);

	/* input addr */
	SETREG32(ISP_HDR_INPUT_BASE_ADDR_LONG, addr_long);
	SETREG32(ISP_HDR_INPUT_BASE_ADDR_SHORT, addr_short);

	SETREG8(COMMAND_REG0, CMD_FULL_SZIE_HDR);
	return wait_cmd_timeout(CMD_FULL_SZIE_HDR, WAIT_COMPLT_TIMEOUT);
#else
        return 0;
#endif

}

/*
 **************************************************************************
 * FunctionName: ispv1_offline_cmd;
 * Description : offline_process cmd set;
 * Input       : source_addr:mac in addr,   target_addr:mac out addr;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_offline_cmd(mini_pic_attr_t *pic_attr, u32 source_addr, u32 target_addr)
{
	u32 dcw_e = 0;
	u32 up_nscale = 0;
	u32 down_nscale = 0;
	u16 value = 0;
	u16 in_fmt = 0;
	u16 out_fmt = 0;
	u8 reg5 = 0;
	int ret=0;
	u8 vc_state = mini_this_ispdata->meta_data_vc_on;

	print_info("%s, in_width=%d, in_height=%d, out_width=%d, out_height=%d, "
		" out_stride=%d\n, source_addr=%#x, target_addr=%#x, offline_state=%d",
		__func__, pic_attr->in_width, pic_attr->in_height,
		pic_attr->out_width, pic_attr->out_height,
		pic_attr->out_stride, source_addr, target_addr, mini_isp_hw_data.offline_state);
	print_debug("addr ready 0x%0x", GETREG8(REG_BASE_ADDR_READY));

	if (mini_isp_hw_data.offline_state == OFFLINE_READY) {
		SETREG8(COMMAND_REG1, (GETREG8(COMMAND_REG1) & 0xfe));
		mini_isp_hw_data.offline_state = OFFLINE_RUNNING;
	} else {
		SETREG8(COMMAND_REG1, (GETREG8(COMMAND_REG1) | 0x01));
	}

	in_fmt = ispv1_convert_input_fmt(pic_attr->in_fmt);
	out_fmt = ispv1_convert_output_fmt(CMD_OFFLINE_PROCESS, pic_attr->out_fmt);
	calc_scale_param(pic_attr, &dcw_e, &value, &up_nscale, &down_nscale);

	if (vc_state == true)
		mini_isp_meta_data_vc_switch(0);

	/* 1. ISP input setting: instead of MAC (REG_SET_ISP_IN_CHANNEL(mac))*/
	SETREG8(REG_ISP_INPUT_CHANNEL, ISP_INPUT_CHANNEL_MAC);


#if 0
	/* FIXME: set byteswitch */
	REG_SET_BYTESWITCH(false);

	if (pic_attr->out_fmt == V4L2_PIX_FMT_NV21) {
			SETREG8(REG_ISP_TOP7, REG_UV_ORDER_V_AHEAD);
	} else if (pic_attr->out_fmt == V4L2_PIX_FMT_NV12) {
			SETREG8(REG_ISP_TOP7, REG_UV_ORDER_U_AHEAD);
	}
#else
    REG_SET_W_SWITCH_CTRL0(pic_attr->out_fmt);
#endif


	/* 2. Sensor out: instead of MAC Read */
	CMD_SET_IN_BASE_ADDR_OFFLINE(BUF_LEFT, source_addr);

	/*CMD_SET_READ_MEM_STRIDE_OFFLINE(pic_attr->in_width);*/

	/* 3. ISP input */
	//CMD_SET_ISP_IN_FMT_SIZE_OFFLINE(in_fmt, pic_attr->in_width, pic_attr->in_height);
    CMD_SET_ISP_IN_FMT_SIZE_OFFLINE(in_fmt|0x60, pic_attr->in_width, pic_attr->in_height);
	/* 4. ISP output */
	CMD_SET_ISP_OUT_FMT_SIZE_OFFLINE(out_fmt, pic_attr->out_width, pic_attr->out_height);
	CMD_SET_WRITE_MEM_STRIDE_OFFLINE(pic_attr->out_stride);

	/* 5. Scale and Crop config */
	CMD_SET_ISP_FUNCTION_CTRL_OFFLINE(value);

	CMD_SET_ISP_RAW_YUV_DCW_OFFLINE(dcw_e, dcw_e);
	CMD_SET_SCALE_DOWN_RATIO_1_OFFLINE(down_nscale, down_nscale);

	/*CMD_SET_SCALE_DOWN_RATIO_2_OFFLINE(down_nscale, down_nscale);*/

	CMD_SET_SCALE_UP_RATIO_OFFLINE(up_nscale, up_nscale);

	CMD_SET_YUV_CROP_START_POS_OFFLINE(pic_attr->crop_x, pic_attr->crop_y);
	CMD_SET_YUV_CROP_SIZE_OFFLINE(pic_attr->crop_width, pic_attr->crop_height);

	/* 6. Tune config: none */

	/* 6.1 Special configure*/
	CMD_SET_OUT_BASE_ADDR_OFFLINE(BUF_LEFT, target_addr, target_addr + pic_attr->out_stride * pic_attr->out_height);

	mini_dump_cmd_reg();

	/* 7. Send command */
	reg5 = ISP_MACINT_SET_ENABLE;
	SETREG8(COMMAND_REG5, reg5);
	SETREG8(COMMAND_REG0, CMD_OFFLINE_PROCESS);

	ret = wait_cmd_timeout(CMD_OFFLINE_PROCESS, WAIT_COMPLT_TIMEOUT);

	if (vc_state == true)
		mini_isp_meta_data_vc_switch(1);

	return ret;
}

/*
 **************************************************************************
 * FunctionName: ispv1_cal_ev_ratio;
 * Description : calculate ev ratio of next frame
 * Input       : ev: ev level
 * Output      : ratio of next frame;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ispv1_cal_ev_ratio(int ev, u32 *ratio)
{
	mini_effect_params *effect = get_effect_ptr();
	mini_ae_params_s *this_ae = &effect->ae_param;
	int i = 0;
	*ratio = EV_RATIO_DIVIDEND;
	if (ev >= 0) {
		for (i = 0; i < ev; i++) {
			*ratio *= this_ae->ev_denominator;
			*ratio /= this_ae->ev_numerator;
		}
	} else {
		ev = -ev;
		for (i = 0; i < ev; i++) {
			*ratio *= this_ae->ev_numerator;
			*ratio /= this_ae->ev_denominator;
		}
	}
}

#define BANDING_STEP_50HZ	0
#define BANDING_STEP_60HZ	1
/*
 **************************************************************************
 * FunctionName: ispv1_cal_banding_step;
 * Description : calculate banding step, 50hz or 60hz
 * Input       : hz:0 is 50Hz, 1 is 60Hz; fps,vts
 * Output      : banding line number
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static u32 ispv1_cal_banding_step(int hz, u32 fps, u32 vts)
{
	u32 banding_step;
	u32 banding_us;
	u32 line_ns;

	if (hz == BANDING_STEP_50HZ) /* 50hz */
		banding_us = 1000*10;
	else if (hz == BANDING_STEP_60HZ)
		banding_us = 1000*1000/120;
	else
		return 0;

	line_ns = 1000*1000*1000/fps/vts;
	banding_step = banding_us*1000/line_ns;

	return banding_step;
}

#if 0
static u32 ispv1_get_curr_banding_step(int hz)
{
	u32 banding_step;

	if (hz == BANDING_STEP_50HZ) {
		GETREG16(REG_ISP_BANDING_STEP_50HZ, banding_step);
	} else if (hz == BANDING_STEP_60HZ) {
		GETREG16(REG_ISP_BANDING_STEP_60HZ, banding_step);
	} else
		return 0;

	banding_step >>= 4;

	return banding_step;
}
#endif


void mini_ispv1_get_banding_step(mini_camera_sensor *sensor, u32 frame_index, u32 *step_50hz, u32 *step_60hz)
{
	u32 banding_step_50hz, banding_step_60hz;
	u16 full_fps, basic_vts;
	u32 chip_id;
	u32 fps, fps_es;

	banding_step_50hz = sensor->frmsize_list[frame_index].banding_step_50hz;
	banding_step_60hz = sensor->frmsize_list[frame_index].banding_step_60hz;

	if ((banding_step_50hz != 0) && (banding_step_60hz != 0)) {
		chip_id = get_chipid();
		if ((DI_CHIP_ID != chip_id) && (CS_CHIP_ID != chip_id)) {
			print_error("----bad chip id, please check---");
			goto ret_out;
		}

		if (chip_id == DI_CHIP_ID) {	/* design-in chip */
			fps = sensor->frmsize_list[frame_index].fps;
			fps_es = sensor->frmsize_list[frame_index].fps_es;
			banding_step_50hz = banding_step_50hz * fps_es / fps;
			banding_step_60hz = banding_step_60hz * fps_es / fps;
		}
	} else {
		full_fps = sensor->frmsize_list[frame_index].fps;
		basic_vts = sensor->frmsize_list[frame_index].vts;
		banding_step_50hz = ispv1_cal_banding_step(BANDING_STEP_50HZ, full_fps, basic_vts);
		banding_step_60hz = ispv1_cal_banding_step(BANDING_STEP_60HZ, full_fps, basic_vts);
	}
ret_out:
	*step_50hz = banding_step_50hz;
	*step_60hz = banding_step_60hz;
}

#if 0
static int ispv1_switch_config(mini_camera_sensor *sensor, camera_state state, bool flash_on, u32 expo_line)
{
	u8 sharpness;

	if (sensor->isp_location == CAMERA_USE_SENSORISP)
		return 0;

	if (state == STATE_PREVIEW) {
		SETREG8(REG_ISP_SDE_YOFFSET, 0x00); /* yoffset */
		mini_ispv1_switch_contrast(STATE_PREVIEW, mini_this_ispdata->contrast); /* ygain */
		mini_ispv1_switch_brightness(STATE_PREVIEW, mini_this_ispdata->brightness); /* ybright */

		#ifndef OVISP_DEBUG_MODE
		mini_ispv1_set_sharpness_zoom(mini_this_ispdata->zoom);
		#endif
	} else if (state == STATE_CAPTURE) {
		SETREG8(REG_ISP_SDE_YOFFSET, 0x00); /* yoffset */
		mini_ispv1_switch_contrast(STATE_CAPTURE, mini_this_ispdata->contrast); /* ygain */
		mini_ispv1_switch_brightness(STATE_CAPTURE, mini_this_ispdata->brightness); /* ybright */

		#ifndef OVISP_DEBUG_MODE
        sharpness = sensor->effect->sharpness[0].sharpness_capture;
		SETREG8(REG_ISP_SHARPNESS, sharpness);
		#endif
	}
	#ifndef OVISP_DEBUG_MODE
	mini_ispv1_switch_dns(sensor, state, flash_on, expo_line);
	#endif

	return 0;
}
#endif

static const mini_expo_table_t capture_expo_table[]= {
	{30, 100}, /* max expo is 3 band(50Hz), 4band(60Hz) */
	{23, 250}, /* max expo is 4 band(50Hz), 5band(60Hz) */
	{20, 500}, /* max expo is 5 band(50Hz), 6band(60Hz) */

	{14, 800}, /* max expo is 7 band(50Hz), 8band(60Hz) */
};

static int ispv1_check_expo_table(u32 expo_1x, bool summary, u32 fps, u32 vts)
{
	int gain, expo, iso, index, expo_line;
	int array_size = ARRAY_SIZE(capture_expo_table);
    mini_effect_params *effect = get_effect_ptr();
    mini_expo_table_t *this_expo_table;

	if (CAMERA_USE_K3ISP == mini_this_ispdata->sensor->isp_location) {
		this_expo_table = effect->ae_param.cap_expo_table;
	} else {
		return fps;
	}
	for (array_size = 0; array_size < CAMERA_MAX_EXPO_TABLE_SIZE; array_size++) {
		if(this_expo_table[array_size].expo == 0 && this_expo_table[array_size].iso == 0)
			break;
	}
	for (index = 0; index < array_size; index++) {
		expo = this_expo_table[index].expo;
		iso = this_expo_table[index].iso;

		expo_line = ispv1_expo_time2line(expo, fps, vts);
		gain = mini_ispv1_iso2gain(iso, summary);

		if (expo_1x < (expo_line * gain / 0x10))
			break;
	}

	if (index > (array_size - 1))
		index = (array_size - 1);

	return(this_expo_table[index].expo);
}
static int ispv1_get_min_capfps(void)
{
	int idx = 0;
	int minfps = 1000;
	int array_size;
	mini_expo_table_t *this_expo_table;
	mini_effect_params *effect = get_effect_ptr();
	if (CAMERA_USE_K3ISP == mini_this_ispdata->sensor->isp_location) {
		this_expo_table = effect->ae_param.cap_expo_table;
	} else {
		return CAMERA_MIN_CAP_FRAMERATE;
	}
	for (array_size = 0; array_size < CAMERA_MAX_EXPO_TABLE_SIZE; array_size++) {
		if(this_expo_table[array_size].expo == 0 && this_expo_table[array_size].iso == 0)
			break;
	}
	while (idx < array_size && this_expo_table[idx].expo != 0) {
		minfps = this_expo_table[idx].expo;
		idx++;
	}
	return minfps;
}

/*
 **************************************************************************
 * FunctionName: ispv1_capture_cmd;
 * Description : offline_process cmd set;
 * Input       : phyaddr:mac out addr,
 * raw_count: count of buffer used for raw data;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_capture_cmd(mini_pic_attr_t *pic_attr, u32 phyaddr, u32 count, int *ev,
	mini_camera_sensor *sensor, bool flash_on, camera_scene scene)
{
	u16 value = 0;
	u8 reg5 = 0;
	u8 reg3c13 = 0x22;
	u8 reg3c15 = 0x53;
	u16 in_fmt = 0;
	u16 out_fmt = 0;
	bool is_bypass_isp;
	u32 size;
	u32 frame_index;
	u32 vts_addr = 0;
	u32 vts = 0;
	u32 banding_step_50hz, banding_step_60hz;
	u32 ratio0 = EV_RATIO_DIVIDEND;
	u32 ratio1 = EV_RATIO_DIVIDEND;
	u32 ratio2 = EV_RATIO_DIVIDEND;
	u16 full_fps, basic_vts;
	int capture_level;
	int preview_level = mini_ispv1_get_frame_rate_level();
	volatile u8 target_y_low;
	bool summary;

	u32 max_expo;
	u32 preview_gain, preview_expo;
	u32 capture_el_1x; /* calculated exposure line in 1x gain */
	u32 el_expected; /* expected capture Exposure line */
	u32 et_reciprocal; /* reciprocal of Exposure time */
	u8 rgain = 0x80;
	u8 bgain = 0x80;
	u32 max_gain;
	u8 min_fps = CAMERA_MIN_FRAMERATE;
	u8 min_cap_fps = ispv1_get_min_capfps();
	u32 dns_expo = get_writeback_expo() / 0x10;

	u32 delay_clk;
	u8 ap_writeAE_mode;
	u16 max_expo_gap;
	u8 sence_night_expo;
	u8 sence_action_expo;

	mini_effect_params *effect = get_effect_ptr();

	if(effect != NULL){
		mini_ae_params_s *this_ae = &effect->ae_param;
		max_expo_gap = this_ae->max_expo_gap;
		sence_night_expo = this_ae->expo_night;
		sence_action_expo = this_ae->expo_action;
	}else{
		max_expo_gap = 14;
		sence_night_expo = 5;
		sence_action_expo = 100;
	}

	mini_ispv1_set_aecagc_mode(MANUAL_AECAGC);


	/*
	 * for AWB, capture will return CCM pre-gain back to 0x80/0x80/0x80
	 */
	frame_index = sensor->capture_frmsize_index;

	if ((false == flash_on) && (sensor->get_ccm_pregain != NULL)) {
		sensor->get_ccm_pregain(STATE_CAPTURE, frame_index, &bgain, &rgain);
	}

	summary = sensor->frmsize_list[frame_index].summary;

#if 0
	/* config CCM pre-gain to cmdset params */
	SETREG8(ISP_CMDSET_CCM_PREGAIN_B, bgain);
	SETREG8(ISP_CMDSET_CCM_PREGAIN_G, 0x80);
	SETREG8(ISP_CMDSET_CCM_PREGAIN_R, rgain);
	SETREG8(ISP_CMDSET_CCM_PREGAIN_ENABLE, 2);
#endif
	full_fps = sensor->frmsize_list[frame_index].fps;
	basic_vts = sensor->frmsize_list[frame_index].vts;

	mini_ispv1_get_banding_step(sensor, frame_index, &banding_step_50hz, &banding_step_60hz);

	/* get the max auto frame rate level at capture */
	if (full_fps <= sensor->fps_min)
		capture_level = 0;
	else
		capture_level = full_fps - sensor->fps_min;

	capture_level = capture_level > preview_level ? preview_level : capture_level;
	sensor->fps = full_fps - capture_level;

	print_info("capture_level %d, preview_level %d, full_fps %d, fps %d, band50Hz 0x%x, band60Hz 0x%x, bgain 0x%x, rgain 0x%x",
	    capture_level, preview_level, full_fps, sensor->fps, banding_step_50hz, banding_step_60hz, bgain, rgain);

	if ((CAMERA_USE_K3ISP == sensor->isp_location)	&& (NULL != sensor->get_vts_reg_addr)) {
		vts_addr = sensor->get_vts_reg_addr();
		/* some night scene, force frame rate is 5fps.*/
		if ((CAMERA_SCENE_NIGHT == scene)
			|| (CAMERA_SCENE_NIGHT_PORTRAIT == scene)
			|| (CAMERA_SCENE_THEATRE == scene)
			|| (CAMERA_SCENE_FIREWORKS == scene)
			|| (CAMERA_SCENE_CANDLELIGHT == scene)) {
			sensor->fps = sence_night_expo;
		}
		vts = basic_vts * full_fps / sensor->fps;
	} else {
		vts = basic_vts;
	}

	#if 0
	if (CAMERA_USE_SENSORISP == sensor->isp_location && CAMERA_SENSOR_PRIMARY == sensor->sensor_index) {
		SETREG8(ISP_SKIP_WAITING_FRAME, 0x01);
		SETREG8(ISP_AGC_SENSOR_TYPE, sensor->sensor_type);
	} else {
		SETREG8(ISP_SKIP_WAITING_FRAME, 0x00);
		SETREG8(ISP_AGC_SENSOR_TYPE, 0x00);
	}
	#endif

	is_bypass_isp = (ISP_CAPTURE_OFFLINE == (ispv1_get_process_mode()));

	print_info("%s, in_width=%d, in_height=%d, out_width=%d, out_height=%d,"
			" out_stride=%d, phyaddr=%#x, count=%d, bypass=%d, sensor setting:%d",
			__func__, pic_attr->in_width, pic_attr->in_height,
			pic_attr->out_width, pic_attr->out_height, pic_attr->out_stride,
			phyaddr, count, is_bypass_isp, frame_index);

	in_fmt  = ispv1_convert_input_fmt(pic_attr->in_fmt);
	out_fmt = ispv1_convert_output_fmt(CMD_CAPTURE, pic_attr->out_fmt);
	CALC_ISP_IN_TYPE(in_fmt, sensor->interface_type, is_bypass_isp);

	/* 1. ISP input setting */
	REG_SET_ISP_IN_CHANNEL(sensor->interface_type);

#if 0
	/*  FIXME: set byteswitch ? */
	if (is_bypass_isp) {
		REG_SET_BYTESWITCH(false);
	} else {
		REG_SET_BYTESWITCH(true);
	}
#endif

	/* 2. Sensor out */
	/*CMD_SET_SENSOR_START_POS(0, 0);
	CMD_SET_SENSOR_START_3D_POS(0, 0);
	*/
	CMD_SET_SENSOR_OUT_SIZE(pic_attr->sensor_width, pic_attr->sensor_height);

	if (is_bypass_isp) {
		REG_SET_W_SWITCH_CTRL0(V4L2_PIX_FMT_RAW10);
		/* 3. ISP input */
		CMD_SET_ISP_IN_START_POS(pic_attr->startx, pic_attr->starty);

                /*
		CMD_SET_ISP_IN_START_3D_POS(0, 0);
		*/
		CMD_SET_ISP_IN_START_POS2(pic_attr->startx, pic_attr->starty);

		CMD_SET_ISP_INPUT_MODE(0);
		CMD_SET_ISP_IN_FMT_SIZE(in_fmt, pic_attr->in_width, pic_attr->in_height);

		/* 4. ISP output */
		/* use input format as output format RAW or YUV422*/

		out_fmt = (in_fmt & 0x7)<<4; /* use LOWBYTE of input format but output format [7:4] bit*/
		CMD_SET_ISP_OUT_FMT_SIZE(out_fmt, pic_attr->in_width, pic_attr->in_height);

		CMD_SET_MAC_MEM_STRIDE(pic_attr->in_width);

		CMD_SET_MAC_MEM_UV_STRIDE(pic_attr->in_width/2);

		/* 5. Scale and Crop config */
		/* do not need scale */
		CMD_SET_ISP_FUNCTION_CTRL(0x00);

		CMD_SET_ISP_SCALE_DOWN_RATIO1(0x80, 0x80);
		CMD_SET_ISP_RAW_YUV_DCW(0, 0);

		CMD_SET_ISP_SCALE_UP_RATIO(0x100, 0x100);

		CMD_SET_ISP_YUV_CROP_POS(0, 0);
		CMD_SET_ISP_YUV_CROP_SIZE(pic_attr->in_width, pic_attr->in_height);
	} else {
		u32 dcw_e = 0;
		u32 up_nscale = 0;
		u32 down_nscale = 0;
		u32 isp_input_x = 0;
		u32 isp_input_y = 0;

		isp_input_x = (pic_attr->sensor_width - pic_attr->in_width) / 2;
		isp_input_y = (pic_attr->sensor_height - pic_attr->in_height) / 2;

		/* 3. ISP input */
		CMD_SET_ISP_IN_START_POS(pic_attr->startx, pic_attr->starty);

                /*
		CMD_SET_ISP_IN_START_3D_POS(0, 0);
		*/
		CMD_SET_ISP_IN_START_POS2(pic_attr->startx, pic_attr->starty);

		CMD_SET_ISP_INPUT_MODE(0);
		CMD_SET_ISP_IN_FMT_SIZE(in_fmt, pic_attr->in_width, pic_attr->in_height);


    #if 0
		/* 4. ISP output */
		/* FIXME:
		   add by chenwei for SC chip,
		   we need 0x63b35=0x00 when output format is YUV420,
		   but 0x63b35=0x04 when output format is YUV422I;
		   so set it true when YUV422I
		*/
		if (pic_attr->out_fmt == V4L2_PIX_FMT_YUYV) {
			REG_SET_BYTESWITCH(true);
		} else {
			REG_SET_BYTESWITCH(false);
		}

		if (pic_attr->out_fmt == V4L2_PIX_FMT_NV21) {
			SETREG8(REG_ISP_TOP7, REG_UV_ORDER_V_AHEAD);
		} else if (pic_attr->out_fmt == V4L2_PIX_FMT_NV12) {
			SETREG8(REG_ISP_TOP7, REG_UV_ORDER_U_AHEAD);
		} else if (pic_attr->out_fmt == V4L2_PIX_FMT_YUYV) {
			SETREG8(REG_ISP_TOP7, REG_UV_ORDER_U_AHEAD);
		}
    #else
		/* 4. ISP output */
        REG_SET_W_SWITCH_CTRL0(pic_attr->out_fmt);
    #endif
		CMD_SET_ISP_OUT_FMT_SIZE(out_fmt, pic_attr->out_width, pic_attr->out_height);
		CMD_SET_MAC_MEM_STRIDE(pic_attr->out_width);

		CMD_SET_MAC_MEM_UV_STRIDE(pic_attr->out_width/2);

		/* 5. Scale and Crop config */
		calc_scale_param(pic_attr, &dcw_e, &value, &up_nscale, &down_nscale);

		CMD_SET_ISP_FUNCTION_CTRL(value);

        CMD_SET_ISP_SCALE_DOWN_RATIO1(down_nscale, down_nscale);
		CMD_SET_ISP_RAW_YUV_DCW(dcw_e, dcw_e);

                /*
		CMD_SET_ISP_SCALE_DOWN_RATIO2(down_nscale, down_nscale);
		*/

		CMD_SET_ISP_SCALE_UP_RATIO(up_nscale, up_nscale);
		CMD_SET_ISP_YUV_CROP_POS(pic_attr->crop_x, pic_attr->crop_y);
		CMD_SET_ISP_YUV_CROP_SIZE(pic_attr->crop_width, pic_attr->crop_height);
	}

	/* 6. Tune config */
	switch (count) {
	case 3:
		ispv1_cal_ev_ratio(ev[2] - ev[0], &ratio2);
	case 2:
		ispv1_cal_ev_ratio(ev[1] - ev[0], &ratio1);
		ispv1_cal_ev_ratio(ev[0], &ratio0);
		CMD_SET_BRACKET_RATIO(ratio1, ratio2);
		break;
	default:
		break;
	}
	ratio0 = ratio0 * sensor->frmsize_list[frame_index].capture_ratio / latest_preview_ratio;

	target_y_low = GETREG8(REG_ISP_TARGET_Y_LOW);

	if (true == flash_on) {
		ratio0 = ratio0 * mini_isp_hw_data.ratio_factor / 0x100;
		mini_isp_hw_data.flash_resume = true;
	} else {
		if (0 != mini_isp_hw_data.preview_ae.lum) {
			if ((mini_isp_hw_data.preview_ae.lum < target_y_low)
				&& (CAMERA_ISO_AUTO == mini_this_ispdata->iso)) {
				ratio0 = ratio0 * target_y_low / mini_isp_hw_data.preview_ae.lum;
			}
		}
	}

	if (ratio0 > ISP_EXPOSURE_RATIO_MAX)
		ratio0 = ISP_EXPOSURE_RATIO_MAX;

	if (CAMERA_SCENE_ACTION == scene) {
		max_expo = full_fps * basic_vts / sence_action_expo;
	}else if (sensor->fps == sence_night_expo) {
		max_expo = vts - max_expo_gap;
	} else {
		/* default max expo is vts-14. */
		max_expo = vts - max_expo_gap;

		if ((CAMERA_ISO_AUTO == mini_this_ispdata->iso) && (1 == count)) {
			if (false == flash_on) {
				/*
				 * some case set max expo time below 1/30s to avoid handshake.
				 */
				preview_gain = mini_isp_hw_data.preview_ae.gain;
				preview_expo = mini_isp_hw_data.preview_ae.expo;

				/* get expected capture expo line at gain 0x10 */
				capture_el_1x = ((preview_gain * preview_expo) >> 8) * ratio0 / EV_RATIO_DIVIDEND;
			} else {
				
				preview_gain = mini_isp_hw_data.preflash_ae.gain;
				preview_expo = mini_isp_hw_data.preflash_ae.expo;

				capture_el_1x = ((preview_gain * preview_expo) >> 8) * ratio0 / EV_RATIO_DIVIDEND;
				dns_expo = capture_el_1x;
			}

			/* look up expo table to select the best expo-gain */
			et_reciprocal = ispv1_check_expo_table(capture_el_1x, summary, sensor->fps, vts);

			print_info("@@@@@@ preview:gain 0x%x, expo 0x%x, ratio0 0x%x, capture_el_1x 0x%x, et_reciprocal %d",
				preview_gain, preview_expo, ratio0, capture_el_1x, et_reciprocal);

			if (et_reciprocal < sensor->fps) {
				/* update new frame rate and vts */
				vts = sensor->fps * vts / et_reciprocal;
				sensor->fps = et_reciprocal;
			}

			/* convert target expo time to expo line */
			el_expected = full_fps * basic_vts / et_reciprocal;

			if (el_expected < basic_vts)
				max_expo = el_expected;
			else
				max_expo = el_expected - 14;
		}
	}

    //FIXME:to be check
    //ispv1_switch_config(sensor, STATE_CAPTURE, flash_on, dns_expo);

	/* vts maybe re-configured, so move here. */
	CMD_SET_SENSOR_VTS(vts);

	//size = sensor->frmsize_list[frame_index].sensor_setting.seq_size;
	//sensor->stream_on(STATE_CAPTURE);
	//ispv1_write_i2c_buf(sensor->frmsize_list[frame_index].sensor_setting.setting, size, 0, sensor->i2c_config.val_bits);
      #if 0
      if ((CAMERA_USE_K3ISP == sensor->isp_location)	&& (NULL != sensor->get_vts_reg_addr)) {
		const struct _mini_sensor_reg_t vts_regs[] = {
			{vts_addr, (vts >> 8) & 0xff},
			{vts_addr + 1, vts & 0xff},
		};

		if (0 != vts_addr) {
			//ispv1_write_i2c_buf(vts_regs, ARRAY_SIZE(vts_regs), size, I2C_8BIT);
			//size += ARRAY_SIZE(vts_regs);
		}
	}
      #endif
	size = 0;
	SETREG8(COMMAND_REG3, size); /* number of registers needed be written */

	if(sensor->effect != NULL){
		min_fps = sensor->effect->ae_param.fps[2];
		min_cap_fps = sensor->effect->ae_param.fps[3];
	}

	if( (sensor->frmsize_list[frame_index].summary == true)
	|| (false == sensor->support_summary)){
		max_gain = sensor->max_gain * min_cap_fps / min_fps;
		CMD_SET_ISP_SET_GAIN_RANGE(max_gain, sensor->min_gain);
	}
	else {
		/* revise max gain to keep preview and capture brightness are same. */
		max_gain = sensor->max_gain * 2 * min_cap_fps / min_fps;
		CMD_SET_ISP_SET_GAIN_RANGE(max_gain, sensor->min_gain);
	}


	CMD_SET_ISP_SET_EXPOSURE_RANGE(max_expo, 0x003);
	CMD_SET_ISP_SET_EXPOSURE_RATIO(ratio0);


	SETREG8(ISP_BANDING_STEP_50HZ, (banding_step_50hz >> 4));
	SETREG8(ISP_BANDING_STEP_50HZ + 1, ((banding_step_50hz & 0x0f) << 4));
	SETREG8(ISP_BANDING_STEP_60HZ, (banding_step_60hz >> 4));
	SETREG8(ISP_BANDING_STEP_60HZ + 1, ((banding_step_60hz & 0x0f) << 4));

	switch (count) {
	case 1:
		preview_ratio = EV_RATIO_DIVIDEND * EV_RATIO_DIVIDEND / ratio0;
		break;
	case 2:
		preview_ratio = (EV_RATIO_DIVIDEND * EV_RATIO_DIVIDEND / ratio1) * EV_RATIO_DIVIDEND / ratio0;
		break;
	case 3:
		preview_ratio = (EV_RATIO_DIVIDEND * EV_RATIO_DIVIDEND / ratio2) * EV_RATIO_DIVIDEND / ratio0;
		break;
	default:
		print_warn("%s count %d error", __func__, count);
		break;
	}

	if ((false == flash_on) && (0 != mini_isp_hw_data.preview_ae.lum)
		&& (mini_isp_hw_data.preview_ae.lum < target_y_low))
		preview_ratio = preview_ratio * target_y_low / mini_isp_hw_data.preview_ae.lum;

	if (true == flash_on) {
		if (mini_isp_hw_data.preview_ratio_lum != 0)
			preview_ratio = preview_ratio * mini_isp_hw_data.preview_ae.lum / mini_isp_hw_data.preview_ratio_lum;
		else
			preview_ratio = 0xffff;
	}

	/* 6.1. Special config for Capture */
	REG_SET_ADDR(REG_BASE_ADDR0_Y, REG_BASE_ADDR0_UV, phyaddr, (phyaddr + mini_isp_hw_data.capture_uv_offset.uoffset));
	REG_SET_ADDR(REG_BASE_ADDR1_Y, REG_BASE_ADDR1_UV, phyaddr, (phyaddr + mini_isp_hw_data.capture_uv_offset.uoffset));
	CMD_SET_BASE_ADDR(BUF_LEFT, phyaddr);

	if (((out_fmt & 0x70)>>4) > 3) {
		phyaddr += pic_attr->out_width * pic_attr->out_height;
		SETREG32(ISP_BASE_ADDR_LEFT_UV, (phyaddr));
	}

	/* bracket mode */
	/* [0]: 0 for normal, 1 for bracket mode */
	/* [1]: 0 for 2 exposures, 1 for 3 exposures in bracket mode */
	CALC_BRACKET_MODE(reg5, count);
#ifdef OVISP_DEBUG_MODE
	reg5 |= ISP_INIT_MODE_DISABLE | ISP_MACINT_SET_ENABLE | ISP_EXPO_RATIO_ENABLE | ISP_IDI_CONFIG_ENABLE;
#else
	reg5 |= ISP_INIT_MODE_ENABLE | ISP_MACINT_SET_ENABLE | ISP_EXPO_RATIO_ENABLE;
#endif
	ispv1_config_idi(pic_attr->in_fmt, is_bypass_isp, &reg3c13, &reg3c15);

    /* init IDI */
    CMD_SET_IDI_CTRL(mini_this_ispdata->idi);

	SETREG8(COMMAND_REG10, 1);

	/* firmware 2013-0130 support set gain effect mode, next or next 2 frames. */
	if (sensor->sensor_type == SENSOR_OV)
		SETREG8(REG_ISP_GAIN_EFFECT_MODE, SENSOR_GAIN_EFFECT_NEXT);
	else
		SETREG8(REG_ISP_GAIN_EFFECT_MODE, SENSOR_GAIN_EFFECT_NEXT2);

	/* 7. Send command */

	if (I2C_16BIT == sensor->i2c_config.val_bits)
		SETREG8(COMMAND_REG1, 0x8c | ((mini_isp_hw_data.i2c_config.index == I2C_PRIMARY) ? 1 : 2));
	else
		SETREG8(COMMAND_REG1, 0x88 | ((mini_isp_hw_data.i2c_config.index == I2C_PRIMARY) ? 1 : 2));

	SETREG8(COMMAND_REG2, mini_isp_hw_data.i2c_config.addr);

#if 1
	SETREG8(COMMAND_REG4, CLK_DIVIDER);
#else
	if (CAMERA_SENSOR_PRIMARY == sensor->sensor_index)
		SETREG8(COMMAND_REG4, 0x0f & CLK_DIVIDER);
	else
		SETREG8(COMMAND_REG4, 0xf0 & CLK_DIVIDER);
#endif

	SETREG8(COMMAND_REG5, reg5);
	//SETREG8(COMMAND_REG6, reg3c13);
	//SETREG8(COMMAND_REG7, reg3c15);
	//	mini_dump_cmd_reg();
	mini_dump_ispzyk_reg();

	ap_writeAE_mode = GETREG8(REG_ISP_AECAGC_WRITESENSOR_ENABLE);
	ap_writeAE_mode &= 0x1;
	if (ap_writeAE_mode == ISP_WRITESENSOR_DISABLE) {
		delay_clk = sensor->ap_writeAE_delay;
		/* check if delay time is longer than 10ms*/
		if (delay_clk > 10000)
			delay_clk = 10000;
		delay_clk *= (ISP_CLOCK / 1000000);
		delay_clk /= 256;
	} else {
		delay_clk = 0;
	}
	SETREG8(COMMAND_REG8, (delay_clk >> 8));
	SETREG8(COMMAND_REG9, (delay_clk & 0xff));

	SETREG8(COMMAND_REG0, CMD_CAPTURE);
	/* mini_dump_cmd_reg(); */
	sensor->stream_on(STATE_CAPTURE);

	wait_cmd_timeout(CMD_CAPTURE, WAIT_COMPLT_TIMEOUT);

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ispv1_start_capture_raw_with_preview_cmd;
 * Description : capture_stream_with_preview cmd set;
 * Input       : mini_pic_attr_t *pic_attr, mini_buffer_arr_t *buf_arr
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_start_capture_raw_with_preview_cmd(mini_pic_attr_t *pic_attr, mini_buffer_arr_t *buf_arr)
{
	u8		buf_cnt;
	int 		ret;

	print_info("enter %s.buf_cnt=%d.",__func__,buf_arr->buf_count);

	buf_cnt = buf_arr->buf_count ;

	/* capture stream buffer count check */
	if ((buf_cnt < CAPTURE_WITH_PREVIEW_BUF_MIN_NUM)
	|| (buf_cnt > CAPTURE_WITH_PREVIEW_BUF_MAX_NUM))
	{
		print_error("invalid buf cnt=%d.should between [%d,%d].",buf_cnt,CAPTURE_WITH_PREVIEW_BUF_MIN_NUM,CAPTURE_WITH_PREVIEW_BUF_MAX_NUM);
		return -EINVAL;
	}

	/* FIXME:sensor ouput width an height */
	CMD_SET_SENSOR_OUT_SIZE(pic_attr->sensor_width, pic_attr->sensor_height);

	/* crop start x&y in capture stream */
	CMD_SET_ISP_IN_START_POS2(pic_attr->startx, pic_attr->starty);

	/* crop width and height in capture stream */
	SETREG16(ISP_INPUT_WIDTH, pic_attr->in_width);
	SETREG16(ISP_INPUT_HEIGHT, pic_attr->in_height);

	/* output buffer in capture stream */
	SETREG32(ISP_MAC_OUTPUT_ADDR1, buf_arr->buffers[0].phyaddr);
	SETREG32(ISP_MAC_OUTPUT_ADDR2, buf_arr->buffers[1].phyaddr);
	SETREG32(ISP_MAC_OUTPUT_ADDR3, buf_arr->buffers[2].phyaddr);
	SETREG32(ISP_MAC_OUTPUT_ADDR4, buf_arr->buffers[3].phyaddr);
	SETREG32(ISP_MAC_OUTPUT_ADDR5, buf_arr->buffers[4].phyaddr);
	SETREG32(ISP_MAC_OUTPUT_ADDR6, buf_arr->buffers[5].phyaddr);
	SETREG32(ISP_MAC_OUTPUT_ADDR7, buf_arr->buffers[6].phyaddr);
	SETREG32(ISP_MAC_OUTPUT_ADDR8, buf_arr->buffers[7].phyaddr);

	/* output buffer mem width in capture stream */
	SETREG16(ISP_MAC_MEM_WIDTH3, pic_attr->in_width);

	/* set frame interval in capture stream. */
	SETREG8(COMMAND_REG2, mini_this_ispdata->zsl_ctrl.zsl_cap_int);

	/* enable offline capture stream */
	SETREG8(COMMAND_REG1, CAPTURE_STREAM_ENABLE
	                | CAPTURE_STREAM_OFFLINE
	                | CAPTURE_STREAM_START
	                | (buf_cnt-1));

	/* To avoid conflict interrupt of ap write ae and capture raw done, it need to lock AECAGC */

	mini_ispv1_set_aecagc_mode(MANUAL_AECAGC);

    sema_init(&mini_isp_hw_data.sem_cap_raw_cmd_done, 0);

	SETREG8(COMMAND_REG0, CMD_CAPTURE_WITH_PREVIEW);

	/*
	print_info("sensor width=%d,height=%d.",pic_attr->sensor_width,pic_attr->sensor_height);
	print_info("buf_arr->buffers[0].phyaddr=%x.",buf_arr->buffers[0].phyaddr);
	print_info("buf_arr->buffers[1].phyaddr=%x.",buf_arr->buffers[1].phyaddr);
	print_info("buf_arr->buffers[2].phyaddr=%x.",buf_arr->buffers[2].phyaddr);
	print_info("buf_arr->buffers[3].phyaddr=%x.",buf_arr->buffers[3].phyaddr);
	print_info("buf_arr->buffers[4].phyaddr=%x.",buf_arr->buffers[4].phyaddr);
	print_info("buf_arr->buffers[5].phyaddr=%x.",buf_arr->buffers[5].phyaddr);
	print_info("buf_arr->buffers[6].phyaddr=%x.",buf_arr->buffers[6].phyaddr);
	print_info("buf_arr->buffers[7].phyaddr=%x.",buf_arr->buffers[7].phyaddr);
	print_info("leave %s.",__func__);
	*/
	ret = wait_cmd_timeout(CMD_CAPTURE_WITH_PREVIEW, WAIT_COMPLT_TIMEOUT);

	mini_ispv1_set_aecagc_mode(AUTO_AECAGC);

	return ret;
}

/*
 **************************************************************************
 * FunctionName: ispv1_start_capture_yuv_with_preview_cmd;
 * Description : capture_stream_with_preview cmd set;
 * Input       : mini_pic_attr_t *pic_attr, mini_buffer_arr_t *buf_arr
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_start_capture_yuv_with_preview_cmd(
            mini_pic_attr_t              *pic_attr,
            mini_buffer_arr_t            *buf_arr)
{
    u8                                  buf_cnt;
	u16                                 out_fmt;
	u32                                 dcw_e                   = 0;
	u16                                 val                     = 0;
	u32                                 up_nscale               = 0;
	u32                                 down_nscale             = 0;
	u32                                 chn1_offset;
	u32                                 chn2_offset;
	int		ret;

	print_info("enter %s.",__func__);

	buf_cnt = buf_arr->buf_count;
	print_info("buf_cnt=%d.",buf_cnt);

	/* buffer count check */
	if ((buf_cnt < CAPTURE_WITH_PREVIEW_BUF_MIN_NUM)
	|| (buf_cnt > CAPTURE_WITH_PREVIEW_BUF_MAX_NUM))
	{
	print_error("invalid buf cnt=%d.should between [%d,%d].",buf_cnt,CAPTURE_WITH_PREVIEW_BUF_MIN_NUM,CAPTURE_WITH_PREVIEW_BUF_MAX_NUM);
	return -EINVAL;
	}

	CMD_SET_SENSOR_OUT_SIZE(pic_attr->sensor_width, pic_attr->sensor_height);


	SETREG16(ISP_SENSOR_OUTPUT_MODE, SENSOR_OUTPUT_MODE_NO_SKIP
                            	| SENSOR_OUTPUT_MODE_NO_BINNING
                            	| SENSOR_OUTPUT_MODE_FLIP_DISABLE
                            	| SENSOR_OUTPUT_MODE_MIRROR_DISABLE);

	SETREG16(ISP_IDI_CONTROL, mini_this_ispdata->idi);


	SETREG16(ISP_INPUT_TYPE,INPUT_TYPE_DUAL_SOURCE_ENABLE
                    		| INPUT_TYPE_ISP_PROCESS_ENABLE
                    		| INPUT_TYPE_PRIMARY_MIPI_SENSOR
                    		| INPUT_TYPE_RAW10);

	CMD_SET_ISP_IN_START_POS2(pic_attr->startx, pic_attr->starty);

	SETREG16(ISP_INPUT_WIDTH,pic_attr->in_width);
	SETREG16(ISP_INPUT_HEIGHT,pic_attr->in_height);

	calc_scale_param2(pic_attr, &dcw_e, &val, &up_nscale, &down_nscale);
	CMD_SET_ISP_FUNCTION_CTRL(val);

	CMD_SET_ISP_RAW_YUV_DCW2(dcw_e, dcw_e);
	CMD_SET_ISP_SCALE_DOWN_RATIO2(down_nscale, down_nscale);
	CMD_SET_ISP_SCALE_UP_RATIO2(up_nscale, up_nscale);

	SETREG16(ISP_YUV_CROP_H_START2, pic_attr->crop_x);
	SETREG16(ISP_YUV_CROP_V_START2, pic_attr->crop_y);
	SETREG16(ISP_YUV_CROP_WIDTH2, pic_attr->crop_width);
	SETREG16(ISP_YUV_CROP_HEIGHT2, pic_attr->crop_height);
	SETREG16(ISP_OUTPUT_WIDTH_2, pic_attr->out_width);
	SETREG16(ISP_OUTPUT_HEIGHT_2, pic_attr->out_height);

	out_fmt = ispv1_convert_output_fmt2(CMD_CAPTURE, pic_attr->out_fmt);
	SETREG16(ISP_OUTPUT_FORMAT, out_fmt);

	chn1_offset = pic_attr->out_width*pic_attr->out_height;
	chn2_offset = chn1_offset*5/4;

	/* set isp output */
	REG_SET_W_SWITCH_CTRL2(pic_attr->out_fmt);
	switch(pic_attr->out_fmt){
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
    #if 0
        REG_SET_BYTESWITCH2(false);
		if (V4L2_PIX_FMT_NV12 == pic_attr->out_fmt)
		{
		    print_info("Online:NV12.");
		    SETREG8(REG_ISP_TOP7, REG_UV_ORDER_U_AHEAD);
		}
		else
		{
		    print_info("Online:NV21.");
		    SETREG8(REG_ISP_TOP7, REG_UV_ORDER_V_AHEAD);
		}
    #endif
		SETREG32(ISP_MAC_OUTPUT_ADDR1, buf_arr->buffers[0].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR2, buf_arr->buffers[0].phyaddr + chn1_offset);
		SETREG32(ISP_MAC_OUTPUT_ADDR3, buf_arr->buffers[1].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR4, buf_arr->buffers[1].phyaddr + chn1_offset);
		SETREG32(ISP_MAC_OUTPUT_ADDR5, buf_arr->buffers[2].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR6, buf_arr->buffers[2].phyaddr + chn1_offset);
		SETREG32(ISP_MAC_OUTPUT_ADDR7, buf_arr->buffers[3].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR8, buf_arr->buffers[3].phyaddr + chn1_offset);
		SETREG32(ISP_MAC_OUTPUT_ADDR9, buf_arr->buffers[4].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR10,buf_arr->buffers[4].phyaddr + chn1_offset);
		SETREG32(ISP_MAC_OUTPUT_ADDR11,buf_arr->buffers[5].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR12,buf_arr->buffers[5].phyaddr + chn1_offset);
		break;
	case V4L2_PIX_FMT_YUYV:
	#if 0
	    print_info("Online:YUYV.");
	    REG_SET_BYTESWITCH2(true);
	    SETREG8(REG_ISP_TOP7, REG_UV_ORDER_U_AHEAD);
    #endif
		SETREG32(ISP_MAC_OUTPUT_ADDR1, buf_arr->buffers[0].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR2, buf_arr->buffers[1].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR3, buf_arr->buffers[2].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR4, buf_arr->buffers[3].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR5, buf_arr->buffers[4].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR6, buf_arr->buffers[5].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR7, buf_arr->buffers[6].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR8, buf_arr->buffers[7].phyaddr);
		break;
	case V4L2_PIX_FMT_YUV420:
	#if 0
	    REG_SET_BYTESWITCH2(false);
	    SETREG8(REG_ISP_TOP7, REG_UV_ORDER_U_AHEAD);
    #endif
		SETREG32(ISP_MAC_OUTPUT_ADDR1, buf_arr->buffers[0].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR2, buf_arr->buffers[0].phyaddr + chn1_offset);
		SETREG32(ISP_MAC_OUTPUT_ADDR3, buf_arr->buffers[0].phyaddr + chn2_offset);
		SETREG32(ISP_MAC_OUTPUT_ADDR4, buf_arr->buffers[1].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR5, buf_arr->buffers[1].phyaddr + chn1_offset);
		SETREG32(ISP_MAC_OUTPUT_ADDR6, buf_arr->buffers[1].phyaddr + chn2_offset);
		SETREG32(ISP_MAC_OUTPUT_ADDR7, buf_arr->buffers[2].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR8, buf_arr->buffers[2].phyaddr + chn1_offset);
		SETREG32(ISP_MAC_OUTPUT_ADDR9, buf_arr->buffers[2].phyaddr + chn2_offset);
		SETREG32(ISP_MAC_OUTPUT_ADDR10,buf_arr->buffers[3].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR11,buf_arr->buffers[3].phyaddr + chn1_offset);
		SETREG32(ISP_MAC_OUTPUT_ADDR12,buf_arr->buffers[3].phyaddr + chn2_offset);
		break;
	default:
	    print_error("%s:unknown pic_attr->out_fmt.",__func__);
		return -EINVAL;
	}


	SETREG16(MAC_MEMORY_WIDTH2, pic_attr->out_stride);
	SETREG16(MAC_MEMORY_UV_WIDTH2, pic_attr->out_stride/2);

	/* set capture frame interval. */
	SETREG8(COMMAND_REG2, mini_this_ispdata->zsl_ctrl.zsl_cap_int);

	SETREG8(COMMAND_REG1, CAPTURE_STREAM_ENABLE
	                | CAPTURE_STREAM_ONLINE
	                | CAPTURE_STREAM_START
	                | (buf_cnt-1));

	/* To avoid conflict interrupt of ap write ae and capture raw done, it need to lock AECAGC */

	mini_ispv1_set_aecagc_mode(MANUAL_AECAGC);

	SETREG8(COMMAND_REG0, CMD_CAPTURE_WITH_PREVIEW);

	/*
	print_info("pic_attr->crop_x=%d,pic_attr->crop_y=%d.",pic_attr->crop_x,pic_attr->crop_y);
	print_info("pic_attr->crop_width=%d,pic_attr->crop_height=%d.",pic_attr->crop_width,pic_attr->crop_height);
	print_info("pic_attr->out_width=%d,pic_attr->out_height=%d.",pic_attr->out_width,pic_attr->out_height);
	print_info("chn1_offset=%d,chn2_offset=%d.",chn1_offset,chn2_offset);
	print_info("buffers[0].phyaddr=%x.",buf_arr->buffers[0].phyaddr);
	print_info("buffers[1].phyaddr=%x.",buf_arr->buffers[1].phyaddr);
	print_info("buffers[2].phyaddr=%x.",buf_arr->buffers[2].phyaddr);
	print_info("buffers[3].phyaddr=%x.",buf_arr->buffers[3].phyaddr);
	print_info("buffers[4].phyaddr=%x.",buf_arr->buffers[4].phyaddr);
	print_info("buffers[5].phyaddr=%x.",buf_arr->buffers[5].phyaddr);
	print_info("buffers[6].phyaddr=%x.",buf_arr->buffers[6].phyaddr);
	print_info("buffers[7].phyaddr=%x.",buf_arr->buffers[7].phyaddr);
	print_info("pic_attr->out_stride=%d.",pic_attr->out_stride);
	print_info("leave %s.",__func__);
	*/
	sema_init(&mini_isp_hw_data.sem_cap_raw_cmd_done, 0);

	ret = wait_cmd_timeout(CMD_CAPTURE_WITH_PREVIEW, WAIT_COMPLT_TIMEOUT);

	mini_ispv1_set_aecagc_mode(AUTO_AECAGC);

	return ret;

}
#if 0
/*
 **************************************************************************
 * FunctionName: ispv1_suspend_capture_with_preview_cmd;
 * Description : capture_stream_with_preview cmd set;
 * Input       :
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_suspend_capture_with_preview_cmd()
{
    u32                                 ret;

    print_info("enter %s.",__func__);

#ifdef ISP_DEBUG_ZSL
    mini_this_ispdata->zsl_ctrl.zsl_back_idx = ZSL_IMAGE_BACK_IDX;
#endif

    /* set which buffer we need */
    SETREG8(COMMAND_REG3, mini_this_ispdata->zsl_ctrl.zsl_back_idx);

    SETREG8(COMMAND_REG1,CAPTURE_STREAM_ENABLE | CAPTURE_STREAM_ONLINE | CAPTURE_STREAM_SUSPEND);

 	SETREG8(COMMAND_REG0, CMD_CAPTURE_WITH_PREVIEW);

	ret = wait_cmd_timeout(CMD_CAPTURE_WITH_PREVIEW, WAIT_COMPLT_TIMEOUT);

    /* get buf index from firmware */
	mini_this_ispdata->zsl_ctrl.history_buf_idx = GETREG8(ISP_CAP_STREAM_BUF_REG) & ISP_CAP_STREAM_BUF_MASK;

	print_info("want back idx=%d.ret buf idx=%d.",mini_this_ispdata->zsl_ctrl.zsl_back_idx,mini_this_ispdata->zsl_ctrl.history_buf_idx);

	print_info("leave %s.",__func__);
	return ret;
}

/*
 **************************************************************************
 * FunctionName: ispv1_resume_capture_with_preview_cmd;
 * Description : capture_stream_with_preview cmd set;
 * Input       : mini_pic_attr_t              *pic_attr,
                 mini_buffer_arr_t            *buf_arr
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_resume_capture_with_preview_cmd(
            mini_pic_attr_t              *pic_attr,
            mini_buffer_arr_t            *buf_arr)
{
    u8                                  buf_cnt;
	u8                                  out_fmt;
	u32                                 chn1_offset;
	u32                                 chn2_offset;
    u32                                 ret;

    print_info("enter %s.",__func__);

    buf_cnt = buf_arr->buf_count;
    print_info("buf_cnt=%d.",buf_cnt);

    /* buffer count check */
    if ((buf_cnt < CAPTURE_WITH_PREVIEW_BUF_MIN_NUM)
     || (buf_cnt > CAPTURE_WITH_PREVIEW_BUF_MAX_NUM))
    {
        print_error("invalid buf cnt=%d.should between [%d,%d].",buf_cnt,CAPTURE_WITH_PREVIEW_BUF_MIN_NUM,CAPTURE_WITH_PREVIEW_BUF_MAX_NUM);
        return -EINVAL;
    }

    out_fmt = ispv1_convert_output_fmt2(CMD_CAPTURE, pic_attr->out_fmt);
    SETREG16(ISP_OUTPUT_FORMAT, out_fmt);

    chn1_offset = pic_attr->out_width*pic_attr->out_height;
    chn2_offset = chn1_offset*5/4;

    /* set isp output */
    REG_SET_W_SWITCH_CTRL2(pic_attr->out_fmt);

    switch(pic_attr->out_fmt){
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
    #if 0
        REG_SET_BYTESWITCH2(false);
		if (V4L2_PIX_FMT_NV12 == pic_attr->out_fmt)
		{
		    print_info("Online:NV12.");
		    SETREG8(REG_ISP_TOP7, REG_UV_ORDER_U_AHEAD);
		}
		else
		{
		    print_info("Online:NV21.");
		    SETREG8(REG_ISP_TOP7, REG_UV_ORDER_V_AHEAD);
		}
    #endif
		SETREG32(ISP_MAC_OUTPUT_ADDR1, buf_arr->buffers[0].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR2, buf_arr->buffers[0].phyaddr + chn1_offset);
		SETREG32(ISP_MAC_OUTPUT_ADDR3, buf_arr->buffers[1].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR4, buf_arr->buffers[1].phyaddr + chn1_offset);
		SETREG32(ISP_MAC_OUTPUT_ADDR5, buf_arr->buffers[2].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR6, buf_arr->buffers[2].phyaddr + chn1_offset);
		SETREG32(ISP_MAC_OUTPUT_ADDR7, buf_arr->buffers[3].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR8, buf_arr->buffers[3].phyaddr + chn1_offset);
		SETREG32(ISP_MAC_OUTPUT_ADDR9, buf_arr->buffers[4].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR10,buf_arr->buffers[4].phyaddr + chn1_offset);
		SETREG32(ISP_MAC_OUTPUT_ADDR11,buf_arr->buffers[5].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR12,buf_arr->buffers[5].phyaddr + chn1_offset);
		break;
	case V4L2_PIX_FMT_YUYV:
	#if 0
	    REG_SET_BYTESWITCH2(true);
	    SETREG8(REG_ISP_TOP7, REG_UV_ORDER_U_AHEAD);
    #endif
		SETREG32(ISP_MAC_OUTPUT_ADDR1, buf_arr->buffers[0].phyaddr);
        SETREG32(ISP_MAC_OUTPUT_ADDR2, buf_arr->buffers[1].phyaddr);
        SETREG32(ISP_MAC_OUTPUT_ADDR3, buf_arr->buffers[2].phyaddr);
        SETREG32(ISP_MAC_OUTPUT_ADDR4, buf_arr->buffers[3].phyaddr);
        SETREG32(ISP_MAC_OUTPUT_ADDR5, buf_arr->buffers[4].phyaddr);
        SETREG32(ISP_MAC_OUTPUT_ADDR6, buf_arr->buffers[5].phyaddr);
        SETREG32(ISP_MAC_OUTPUT_ADDR7, buf_arr->buffers[6].phyaddr);
        SETREG32(ISP_MAC_OUTPUT_ADDR8, buf_arr->buffers[7].phyaddr);
		break;
	case V4L2_PIX_FMT_YUV420:
	#if 0
	    REG_SET_BYTESWITCH2(false);
	    SETREG8(REG_ISP_TOP7, REG_UV_ORDER_U_AHEAD);
	#endif
		SETREG32(ISP_MAC_OUTPUT_ADDR1, buf_arr->buffers[0].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR2, buf_arr->buffers[0].phyaddr + chn1_offset);
		SETREG32(ISP_MAC_OUTPUT_ADDR3, buf_arr->buffers[0].phyaddr + chn2_offset);
		SETREG32(ISP_MAC_OUTPUT_ADDR4, buf_arr->buffers[1].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR5, buf_arr->buffers[1].phyaddr + chn1_offset);
		SETREG32(ISP_MAC_OUTPUT_ADDR6, buf_arr->buffers[1].phyaddr + chn2_offset);
		SETREG32(ISP_MAC_OUTPUT_ADDR7, buf_arr->buffers[2].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR8, buf_arr->buffers[2].phyaddr + chn1_offset);
		SETREG32(ISP_MAC_OUTPUT_ADDR9, buf_arr->buffers[2].phyaddr + chn2_offset);
		SETREG32(ISP_MAC_OUTPUT_ADDR10,buf_arr->buffers[3].phyaddr);
		SETREG32(ISP_MAC_OUTPUT_ADDR11,buf_arr->buffers[3].phyaddr + chn1_offset);
		SETREG32(ISP_MAC_OUTPUT_ADDR12,buf_arr->buffers[3].phyaddr + chn2_offset);
		break;
	default:
	    print_error("%s:unknown pic_attr->out_fmt.",__func__);
		return -EINVAL;
	}

    /* set frame interval in capture stream. */
    SETREG8(COMMAND_REG2, mini_this_ispdata->zsl_ctrl.zsl_cap_int);

    SETREG8(COMMAND_REG1, CAPTURE_STREAM_ENABLE
                        | CAPTURE_STREAM_ONLINE
                        | CAPTURE_STREAM_RESUME
                        | (buf_cnt-1));

	SETREG8(COMMAND_REG0, CMD_CAPTURE_WITH_PREVIEW);

	ret = wait_cmd_timeout(CMD_CAPTURE_WITH_PREVIEW, WAIT_COMPLT_TIMEOUT);

	print_info("leave %s.",__func__);

	return ret;
}
#endif
/*
 **************************************************************************
 * FunctionName: ispv1_stop_capture_with_preview_cmd;
 * Description : capture_stream_with_preview cmd set;
 * Input       :
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_stop_capture_with_preview_cmd()
{
	u32                                 ret;

	print_info("enter %s.",__func__);

	/* set which buffer we need */
	SETREG8(COMMAND_REG3, mini_this_ispdata->zsl_ctrl.zsl_proc_idx);

    /* init return idx to invalid */
	SETREG8(ISP_CAP_STREAM_BUF_REG, mini_this_ispdata->zsl_ctrl.history_buf_cnt);

	if (CAMERA_ZSL_OFFLINE == mini_this_ispdata->zsl_ctrl.zsl_proc_mode){
	    SETREG8(COMMAND_REG1, CAPTURE_STREAM_DISABLE | CAPTURE_STREAM_OFFLINE);
	}
	else{
	    SETREG8(COMMAND_REG1, CAPTURE_STREAM_DISABLE | CAPTURE_STREAM_ONLINE);
	}

	/* To avoid conflict interrupt of ap write ae and capture raw done, it need to lock AECAGC */

	mini_ispv1_set_aecagc_mode(MANUAL_AECAGC);

	SETREG8(COMMAND_REG0, CMD_CAPTURE_WITH_PREVIEW);

    sema_init(&mini_isp_hw_data.sem_cap_raw_cmd_done, 0);

	ret = wait_cmd_timeout(CMD_CAPTURE_WITH_PREVIEW, WAIT_COMPLT_TIMEOUT);

	mini_ispv1_set_aecagc_mode(AUTO_AECAGC);

	if (ret != 0)
	{
	    print_error("%s:wait_cmd_timeout fail.ret=%d",__func__,ret);
	}

	/* get buf index from firmware */
	mini_this_ispdata->zsl_ctrl.history_buf_idx = GETREG8(ISP_CAP_STREAM_BUF_REG) & ISP_CAP_STREAM_BUF_MASK;

	print_info("want back idx=%d.ret buf idx=%d.",mini_this_ispdata->zsl_ctrl.zsl_proc_idx,mini_this_ispdata->zsl_ctrl.history_buf_idx);

    /* check if return idx is valid */
    if (mini_this_ispdata->zsl_ctrl.history_buf_idx >= mini_this_ispdata->zsl_ctrl.history_buf_cnt){
        print_error("history_buf_cnt=%d.history_buf_idx=%d.",mini_this_ispdata->zsl_ctrl.history_buf_cnt,mini_this_ispdata->zsl_ctrl.history_buf_idx);
        ret = -EINVAL;
    }
	//print_info("leave %s.",__func__);

    return ret;
}


/*
 **************************************************************************
 * FunctionName: ispv1_start_proc_img_with_preview;
 * Description : proc_img_with_preview cmd set;
 * Input       :
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_start_proc_img_with_preview_cmd(
                mini_pic_attr_t      *pic_attr,
                mini_buffer_arr_t    *ipp_buf_arr,
                u32             target_addr)
{
    u16                                 out_fmt                = 0;
	u32                                 dcw_e                   = 0;
	u16                                  val                     = 0;
	u32                                 up_nscale               = 0;
	u32                                 down_nscale             = 0;
    //unsigned long                       lock_flags;
    u8                                  proce_src               = 0;
    u32                                 ret                     = 0;

    print_info("enter %s.target_addr=0x%x,zsl_proc_idx=%d",__func__,target_addr,mini_this_ispdata->zsl_ctrl.zsl_proc_idx);

    /* enable dual source */
	SETREG16(ISP_INPUT_TYPE, INPUT_TYPE_DUAL_SOURCE_ENABLE
                           | INPUT_TYPE_ISP_PROCESS_ENABLE
                           | INPUT_TYPE_PRIMARY_MIPI_SENSOR
                           | INPUT_TYPE_RAW10);


	SETREG16(ISP_SENSOR_OUTPUT_MODE, SENSOR_OUTPUT_MODE_NO_SKIP
                                   | SENSOR_OUTPUT_MODE_NO_BINNING
                                   | SENSOR_OUTPUT_MODE_FLIP_DISABLE
                                   | SENSOR_OUTPUT_MODE_MIRROR_DISABLE);


	SETREG16(SENSOR_OUTPUT_WIDTH, pic_attr->sensor_width);
	SETREG16(SENSOR_OUTPUT_HEIGHT, pic_attr->sensor_height);

    SETREG16(ISP_INPUT_WIDTH,pic_attr->in_width);
    SETREG16(ISP_INPUT_HEIGHT,pic_attr->in_height);


	SETREG16(ISP_IDI_CONTROL, mini_this_ispdata->idi);

	SETREG16(ISP_OUTPUT_WIDTH_2, pic_attr->out_width);
	SETREG16(ISP_OUTPUT_HEIGHT_2, pic_attr->out_height);

    /* Y channel output mem width should be the width of the final image */
	SETREG16(MAC_MEMORY_WIDTH2, pic_attr->out_stride);
	SETREG16(MAC_MEMORY_UV_WIDTH2, pic_attr->out_stride/2);
	SETREG16(ISP_MAC_MEMORY_WIDTH_RAW, pic_attr->in_width);

	out_fmt = ispv1_convert_output_fmt2(CMD_CAPTURE, pic_attr->out_fmt);
	SETREG16(ISP_OUTPUT_FORMAT, out_fmt);

	SETREG16(ISP_YUV_CROP_H_START2, pic_attr->crop_x);
	SETREG16(ISP_YUV_CROP_V_START2, pic_attr->crop_y);
    SETREG16(ISP_YUV_CROP_WIDTH2, pic_attr->crop_width);
	SETREG16(ISP_YUV_CROP_HEIGHT2, pic_attr->crop_height);

    calc_scale_param2(pic_attr, &dcw_e, &val, &up_nscale, &down_nscale);
    CMD_SET_ISP_FUNCTION_CTRL(val);

#ifdef ISP_ZSL_ZOOM_FIX
    if ((pic_attr->out_width == 2592)
     && (pic_attr->out_height == 1952))
    {
        if ((mini_this_ispdata->zoom == 4)
          || (mini_this_ispdata->zoom == 14)
          || (mini_this_ispdata->zoom == 19)
          || (mini_this_ispdata->zoom == 29))
        {
            if ((mini_this_ispdata->pic_attr[STATE_PREVIEW].out_width == 960)
             && (mini_this_ispdata->pic_attr[STATE_PREVIEW].out_height == 720)
             && (pic_attr->sensor_width == 3264)
             && (pic_attr->sensor_height == 2448))
            {
                /* FIXME:fix pre:960x720;8M->5M zsl,zoom:1.4 */
        		if (mini_this_ispdata->zoom == 4)
                	up_nscale = 232;  //229
                /* FIXME:fix pre:960x720;8M->5M zsl,zoom:2.9 */
        		else if (mini_this_ispdata->zoom == 19)
                	up_nscale = 112;  //110
                else{
                }
            }
            else if ((mini_this_ispdata->pic_attr[STATE_PREVIEW].out_width == 720)
             && (mini_this_ispdata->pic_attr[STATE_PREVIEW].out_height == 544)
             && (pic_attr->sensor_width == 3264)
             && (pic_attr->sensor_height == 2448))
            {
                /* FIXME:fix pre:720x544;8M->5M zsl,zoom:2.4 */
        		if (mini_this_ispdata->zoom == 14)
                	up_nscale = 136; //133

            }
            else if ((mini_this_ispdata->pic_attr[STATE_PREVIEW].out_width == 640)
             && (mini_this_ispdata->pic_attr[STATE_PREVIEW].out_height == 480)
             && (pic_attr->sensor_width == 3264)
             && (pic_attr->sensor_height == 2448))
            {
                /* FIXME:fix pre:640x480;8M->5M zsl,zoom:3.9 */
        		if (mini_this_ispdata->zoom == 29)
                	up_nscale = 84; //82

            }
            else
            {
            }
        }
    }
    else if ((pic_attr->out_width == 2592)
          && (pic_attr->out_height == 1936))
    {
        /* FIXME:fix pre:960x720;8M->5M zsl,zoom:2.4 */
		if (mini_this_ispdata->zoom == 14)
		{
            if ((mini_this_ispdata->pic_attr[STATE_PREVIEW].out_width == 960)
             && (mini_this_ispdata->pic_attr[STATE_PREVIEW].out_height == 720)
             && (pic_attr->sensor_width == 3264)
             && (pic_attr->sensor_height == 2448))
            {
                up_nscale = 136; //134

            }
        }
    }
    else
    {
    }
#endif

    CMD_SET_ISP_RAW_YUV_DCW2(dcw_e, dcw_e);
    CMD_SET_ISP_SCALE_DOWN_RATIO2(down_nscale, down_nscale);
    CMD_SET_ISP_SCALE_UP_RATIO2(up_nscale, up_nscale);

    /* set isp output */
    REG_SET_W_SWITCH_CTRL2(pic_attr->out_fmt);
    mini_isp_hw_data.pix_fmt = pic_attr->out_fmt;
    ispv1_zsl_update_addr(pic_attr->out_fmt,target_addr,&mini_isp_hw_data.capture_uv_offset);


    if (mini_this_ispdata->zsl_ctrl.zsl_proc_type == ZSL_PROC_IMG_HISTORY_BACKWARD_ONE)
    {
        print_info("process image type:backward one.");
        proce_src   = PROC_IMAGE_OFFLINE;
    }
    else
    {
        print_error("invalid process image type %d.",mini_this_ispdata->zsl_ctrl.zsl_proc_type);
    }

#ifdef SUPPORT_ZSL_FLASH
	if(zsl_flash_process==1)
		mini_this_ispdata->zsl_ctrl.zsl_proc_idx = 0;
#endif

//    spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
    mini_isp_hw_data.irq_val.mac_irqstatus_h_done_cnt = 0;
//    spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);

    /* set max drop or overflow we can tolerate while processing image with preview.
    when processing slice raw data occures drop or overflow,firmware will do the process again */
    SETREG8(ISP_PROC_IMAGE_MAC_DROP_OVERFLOW_THRESHHOLD,PROC_IMAGE_MAC_DROP_OVERFLOW_THRESHHOLD);

    SETREG8(COMMAND_REG1, proce_src
                        | mini_this_ispdata->zsl_ctrl.zsl_proc_idx);/* [7]:1for offline;0:capture new;[2:0]:0:cur frame,n last n frame */


    sema_init(&mini_isp_hw_data.sem_proc_img_cmd_done, 0);

	SETREG8(COMMAND_REG0, CMD_PROC_IMG_WITH_PREVIEW);

    //print_info("idi=%d,target_addr=0x%x",mini_this_ispdata->idi,target_addr);
    //print_info("%s:pic_attr->out_stride=%d",__func__,pic_attr->out_width);
    //print_info("no need to wait for cmd 8 finished.");
	//print_info("leave %s.",__func__);
    //mini_dump_ispzyk_reg();
    ret = wait_cmd_timeout(CMD_PROC_IMG_WITH_PREVIEW, WAIT_COMPLT_TIMEOUT);
    if (0 != ret){
        print_warn("%s:wait_cmd_timeout fail.ret=%d.",__func__,ret);
        return ret;
    }

    /* check if cost 4 times */
    if (mini_isp_hw_data.irq_val.mac_irqstatus_h_done_cnt != 4)
    {
        print_warn("mini_isp_hw_data.irq_val.mac_irqstatus_h_done_cnt=%d",mini_isp_hw_data.irq_val.mac_irqstatus_h_done_cnt);
    }

    return ret;
}

static void calc_scale_param(mini_pic_attr_t *pic_attr, u32* dcw_e, u16* value, u32* up_nscale, u32* down_nscale)
{
	u32 dcw = 0;
	BUG_ON(pic_attr == NULL || dcw_e == NULL || value == NULL || up_nscale == NULL || down_nscale == NULL);
	print_debug("enter %s", __func__);

	if (YUV_SCALE_DIVIDEND > pic_attr->yuv_up_scale_nscale) {
		*value = 0x05;	/* scale up */
		dcw = 0;
	} else if (pic_attr->raw_scale_down > 1) {
		*value = 0x0b;	/* scale down */
		dcw = pic_attr->raw_scale_down;
	} else if (pic_attr->yuv_dcw > 1
		|| pic_attr->yuv_down_scale_nscale > YUV_SCALE_DIVIDEND) {
		*value = 0x03;	/* only yuv scale down */
		dcw = pic_attr->yuv_dcw;
	} else {
		*value = 0x01;
		dcw = 0x0;
	}

	/* change scale to exponent value */
	*dcw_e = 0;
	while ((dcw / 2) != 0) {
		(*dcw_e)++;
		dcw /= 2;
	}

	*down_nscale = (YUV_SCALE_DIVIDEND * YUV_DOWN_SCALE_DIVIDEND
		 + pic_attr->yuv_down_scale_nscale - 1)
		/ pic_attr->yuv_down_scale_nscale;
	*up_nscale = pic_attr->yuv_up_scale_nscale * YUV_UP_SCALE_DIVIDEND / YUV_SCALE_DIVIDEND;

	print_debug("dcw_e=%d, fun_value=%#x, down_nscale=%#x, up_nscale=%#x",
		*dcw_e, *value, *down_nscale, *up_nscale);
}

static void calc_scale_param2(mini_pic_attr_t *pic_attr, u32* dcw_e, u16* value, u32* up_nscale, u32* down_nscale)
{
	u32 dcw = 0;
	BUG_ON(pic_attr == NULL || dcw_e == NULL || value == NULL || up_nscale == NULL || down_nscale == NULL);
	print_debug("enter %s", __func__);

	if (YUV_SCALE_DIVIDEND > pic_attr->yuv_up_scale_nscale) {
		*value = 0x50;	/* second channel scale up */
		dcw = 0;
	} else if (pic_attr->raw_scale_down > 1) {
		*value = 0xb0;	/* second channel scale down */
		dcw = pic_attr->raw_scale_down;
	} else if (pic_attr->yuv_dcw > 1
		|| pic_attr->yuv_down_scale_nscale > YUV_SCALE_DIVIDEND) {
		*value = 0x30;	/* second channel only yuv scale down */
		dcw = pic_attr->yuv_dcw;
	} else {
		*value = 0x10;
		dcw = 0x0;
	}

	/* second channel change scale to exponent value */
	*dcw_e = 0;
	while ((dcw / 2) != 0) {
		(*dcw_e)++;
		dcw /= 2;
	}

	*down_nscale = (YUV_SCALE_DIVIDEND * YUV_DOWN_SCALE_DIVIDEND
		 + pic_attr->yuv_down_scale_nscale - 1)
		/ pic_attr->yuv_down_scale_nscale;
	*up_nscale = pic_attr->yuv_up_scale_nscale * YUV_UP_SCALE_DIVIDEND / YUV_SCALE_DIVIDEND;

	print_debug("dcw_e=%d, fun_value=%#x, down_nscale=%#x, up_nscale=%#x",
		*dcw_e, *value, *down_nscale, *up_nscale);
}


/*
 **************************************************************************
 * FunctionName: ispv1_preview_cmd;
 * Description : config registers of firmware to start preview;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_preview_cmd(mini_pic_attr_t *pic_attr,
			     mini_camera_sensor *sensor, bool cold_boot, camera_scene scene)
{
	u32 dcw_e = 0;
	u16 value = 0;
	u8 reg5 = 0;
	u8 reg3c13 = 0x22;
	u8 reg3c15 = 0x53;
	u32 up_nscale = 0;
	u32 down_nscale = 0;
	u16 in_fmt = 0;
	u16 out_fmt = 0;
	u32 size = 0;
	u32 frame_index;
	u32 vts_addr = 0;
	u32 vts = 0;
	u16 full_fps;
	u32 basic_vts;
	u16 step;

	int level;
	u32 banding_step_50hz, banding_step_60hz;
	static u32 previous_frame_index;
	u8 rgain = 0x80;
	u8 bgain = 0x80;

	u32 delay_clk;
	u8 ap_writeAE_mode;

    //FIXME:to be check;
	//ispv1_switch_config(sensor, STATE_PREVIEW, false, 0);

	/*
	 * preview will set CCM pre-gain 0x8x/0x80/0x8x to compensate for preview
	 */
	frame_index = sensor->preview_frmsize_index;
	if (sensor->get_ccm_pregain != NULL) {
		sensor->get_ccm_pregain(STATE_PREVIEW, frame_index, &bgain, &rgain);
	}

#if 0
	/* config CCM pre-gain to cmdset params */
	SETREG8(ISP_CMDSET_CCM_PREGAIN_B, bgain);
	SETREG8(ISP_CMDSET_CCM_PREGAIN_G, 0x80);
	SETREG8(ISP_CMDSET_CCM_PREGAIN_R, rgain);
	SETREG8(ISP_CMDSET_CCM_PREGAIN_ENABLE, 2);
#endif

	full_fps = sensor->frmsize_list[frame_index].fps;
	basic_vts = sensor->frmsize_list[frame_index].vts;

	mini_ispv1_get_banding_step(sensor, frame_index, &banding_step_50hz, &banding_step_60hz);

	print_info("%s, in_width=%d, in_height=%d, out_width=%d, out_height=%d, cold_boot %d, band50Hz 0x%x, band60Hz 0x%x",
		__func__, pic_attr->in_width, pic_attr->in_height,
		pic_attr->out_width, pic_attr->out_height, cold_boot,
		banding_step_50hz, banding_step_60hz);

	
	level = mini_ispv1_get_frame_rate_level();

	if ((cold_boot == true) || (frame_index != previous_frame_index) ||
		(sensor->fps_max == sensor->fps_min)) {
		if ((CAMERA_SCENE_NIGHT != scene) &&
			(CAMERA_SCENE_NIGHT_PORTRAIT != scene) &&
			(CAMERA_SCENE_THEATRE != scene) &&
			(CAMERA_SCENE_FIREWORKS != scene)	&&
			(CAMERA_SCENE_CANDLELIGHT != scene)) {
			level = 0;
			mini_ispv1_set_frame_rate_level(0);
			mini_ispv1_set_frame_rate_state(CAMERA_FPS_STATE_HIGH);
			previous_frame_index = frame_index;
		}
	}

	if ((CAMERA_USE_K3ISP == sensor->isp_location)	&& (NULL != sensor->get_vts_reg_addr)) {
		vts_addr = sensor->get_vts_reg_addr();
		step = 1;
		sensor->fps = full_fps - level * step;
		vts = sensor->frmsize_list[frame_index].vts * full_fps / sensor->fps;
	}
	CMD_SET_SENSOR_VTS(vts);

	#if 0
	if (CAMERA_USE_SENSORISP == sensor->isp_location && CAMERA_SENSOR_PRIMARY == sensor->sensor_index) {
		SETREG8(ISP_SKIP_WAITING_FRAME, 0x01);
		SETREG8(ISP_AGC_SENSOR_TYPE, sensor->sensor_type);
	} else {
		SETREG8(ISP_SKIP_WAITING_FRAME, 0x00);
		SETREG8(ISP_AGC_SENSOR_TYPE, 0x00);
	}
	#endif

	if ((cold_boot == false)) {
		sensor->stream_on(STATE_PREVIEW);
		size = sensor->frmsize_list[frame_index].sensor_setting.seq_size;
		ispv1_write_i2c_buf(sensor->frmsize_list[frame_index].sensor_setting.setting, size, 0, sensor->i2c_config.val_bits);
		if(CAMERA_USE_K3ISP == sensor->isp_location) {
			const struct _mini_sensor_reg_t vts_regs[] = {
				{vts_addr, (vts >> 8) & 0xff},
				{vts_addr + 1, vts & 0xff},
			};

			if (0 != vts_addr) {
				ispv1_write_i2c_buf(vts_regs, ARRAY_SIZE(vts_regs), size, I2C_8BIT);
				size += ARRAY_SIZE(vts_regs);
			}
		}
	} else {
		size = 0;
	}
	size = 0;
	SETREG8(COMMAND_REG3, size); /* number of registers needed be written */

	in_fmt = ispv1_convert_input_fmt(pic_attr->in_fmt);
	out_fmt = ispv1_convert_output_fmt(CMD_SET_FORMAT, pic_attr->out_fmt);
	calc_scale_param(pic_attr, &dcw_e, &value, &up_nscale, &down_nscale);

	/* preview always output yuv data, but back sensor always output raw data and
	* many front sensors have no scale up function.
	* So: never bypass isp when preview.
	*/
	CALC_ISP_IN_TYPE(in_fmt, sensor->interface_type, 0);

	/* Start configure ..................................*/
	/* 1. ISP input setting */
	REG_SET_ISP_IN_CHANNEL(sensor->interface_type);

	/* 2. Sensor out */

        /*
	CMD_SET_SENSOR_START_POS(0, 0);
	CMD_SET_SENSOR_START_3D_POS(0, 0);
	*/
	CMD_SET_SENSOR_OUT_SIZE(pic_attr->sensor_width, pic_attr->sensor_height);

	/* 3. ISP input */
	CMD_SET_ISP_IN_START_POS(pic_attr->startx, pic_attr->starty);

	CMD_SET_ISP_IN_START_POS2(pic_attr->startx, pic_attr->starty);
        /*
	CMD_SET_ISP_IN_START_3D_POS(0, 0);
	*/
	CMD_SET_ISP_IN_FMT_SIZE(in_fmt, pic_attr->in_width, pic_attr->in_height);
	CMD_SET_ISP_INPUT_MODE(0);

#if 0
	/* 4. ISP output */
	/* FIXME:
	   add by chenwei for CS chip,
	   we need 0x63b35=0x00 when output format is YUV420,
	   but 0x63b35=0x04 when output format is YUV422I;
	   so set it true when YUV422I
	*/
	if (pic_attr->out_fmt == V4L2_PIX_FMT_YUYV) {
		REG_SET_BYTESWITCH(true);
	} else {
		REG_SET_BYTESWITCH(false);
	}

	if (pic_attr->out_fmt == V4L2_PIX_FMT_NV21) {
		SETREG8(REG_ISP_TOP7, REG_UV_ORDER_V_AHEAD);
	} else if (pic_attr->out_fmt == V4L2_PIX_FMT_NV12) {
		SETREG8(REG_ISP_TOP7, REG_UV_ORDER_U_AHEAD);
	} else if (pic_attr->out_fmt == V4L2_PIX_FMT_YUYV) {
		SETREG8(REG_ISP_TOP7, REG_UV_ORDER_U_AHEAD);
	}
#else
	/* 4. ISP output */
    REG_SET_W_SWITCH_CTRL0(pic_attr->out_fmt);
#endif

	CMD_SET_ISP_OUT_FMT_SIZE(out_fmt, pic_attr->out_width, pic_attr->out_height);
        CMD_SET_ISP_OUT_FMT_SIZE2(out_fmt, pic_attr->out_width, pic_attr->out_height);

    print_info("mem_stride:%d",pic_attr->out_stride);

    print_info("UV_stride:%d",pic_attr->out_stride/2);

	CMD_SET_MAC_MEM_STRIDE(pic_attr->out_stride);
        CMD_SET_MAC_MEM_UV_STRIDE(pic_attr->out_width/2);

        CMD_SET_MAC_MEM_STRIDE2(pic_attr->out_stride);
        CMD_SET_MAC_MEM_UV_STRIDE2(pic_attr->out_width/2);

	/* 5. Scale and Crop config */
	CMD_SET_ISP_FUNCTION_CTRL(value);

	CMD_SET_ISP_RAW_YUV_DCW(dcw_e, dcw_e);
	CMD_SET_ISP_SCALE_DOWN_RATIO1(down_nscale, down_nscale);
        CMD_SET_ISP_SCALE_DOWN_RATIO2(down_nscale, down_nscale);

	CMD_SET_ISP_SCALE_UP_RATIO(up_nscale, up_nscale);
        CMD_SET_ISP_SCALE_UP_RATIO2(up_nscale, up_nscale);

	CMD_SET_ISP_YUV_CROP_POS(pic_attr->crop_x, pic_attr->crop_y);
	CMD_SET_ISP_YUV_CROP_SIZE(pic_attr->crop_width, pic_attr->crop_height);

	CMD_SET_ISP_YUV_CROP_POS2(pic_attr->crop_x, pic_attr->crop_y);
	CMD_SET_ISP_YUV_CROP_SIZE2(pic_attr->crop_width, pic_attr->crop_height);

	/* 6. Tune config */
	if (preview_ratio != 0xffff)
		CMD_SET_ISP_SET_EXPOSURE_RATIO(preview_ratio * sensor->frmsize_list[frame_index].capture_ratio / latest_preview_ratio);
	else
		CMD_SET_ISP_SET_EXPOSURE_RATIO(preview_ratio);
	latest_preview_ratio = sensor->frmsize_list[frame_index].capture_ratio;
	preview_ratio = EV_RATIO_DIVIDEND;

	/* y36721 fix:In preview cmd, banding step should set to ISP registers, not firmware registers */
	SETREG8(REG_ISP_BANDING_STEP_50HZ, (banding_step_50hz >> 4));
	SETREG8(REG_ISP_BANDING_STEP_50HZ + 1, ((banding_step_50hz & 0x0f) << 4));
	SETREG8(REG_ISP_BANDING_STEP_60HZ, (banding_step_60hz >> 4));
	SETREG8(REG_ISP_BANDING_STEP_60HZ + 1, ((banding_step_60hz & 0x0f) << 4));

	mini_ispv1_set_wb_value(&mini_isp_hw_data.preview_awb);
	if (CAMERA_SCENE_ACTION == scene)
		CMD_SET_ISP_SET_EXPOSURE_RANGE(full_fps * sensor->frmsize_list[frame_index].vts / 100, 0x003);
	else
		CMD_SET_ISP_SET_EXPOSURE_RANGE((vts - 14) , 0x003); /* y36721 2012-04-05 changed. */

	if( (sensor->frmsize_list[frame_index].summary == true)
	||(false == sensor->support_summary)){
		CMD_SET_ISP_SET_GAIN_RANGE(sensor->max_gain, sensor->min_gain);
	}
	else{
		CMD_SET_ISP_SET_GAIN_RANGE(sensor->max_gain * 2, sensor->min_gain);
	}





#ifdef OVISP_DEBUG_MODE
	if (cold_boot == true)
		reg5 = ISP_INIT_MODE_ENABLE | ISP_MACINT_SET_DISABLE | ISP_EXPO_RATIO_ENABLE | ISP_IDI_CONFIG_ENABLE;
	else
        reg5 = ISP_INIT_MODE_DISABLE | ISP_MACINT_SET_DISABLE | ISP_EXPO_RATIO_ENABLE | ISP_IDI_CONFIG_ENABLE;
#else
	if (cold_boot == true)
		reg5 = ISP_INIT_MODE_ENABLE | ISP_MACINT_SET_DISABLE | ISP_EXPO_RATIO_ENABLE;
	else
		reg5 = ISP_INIT_MODE_ENABLE | ISP_MACINT_SET_DISABLE | ISP_EXPO_RATIO_ENABLE;
#endif
    if (DVP == sensor->interface_type)
    {
        reg5 = (reg5&0xef);
    }

	ispv1_config_idi(pic_attr->in_fmt, false, &reg3c13, &reg3c15);

    print_info("idi=%d.",mini_this_ispdata->idi);
    CMD_SET_IDI_CTRL(mini_this_ispdata->idi);

	/* 7. Send command */

	if (I2C_16BIT == sensor->i2c_config.val_bits)
		SETREG8(COMMAND_REG1, 0x8c | ((mini_isp_hw_data.i2c_config.index == I2C_PRIMARY) ? 1 : 2));
	else
		SETREG8(COMMAND_REG1, 0x88 | ((mini_isp_hw_data.i2c_config.index == I2C_PRIMARY) ? 1 : 2));

	SETREG8(COMMAND_REG2, mini_isp_hw_data.i2c_config.addr);

#if 1
	SETREG8(COMMAND_REG4, CLK_DIVIDER);
#else
	if (CAMERA_SENSOR_PRIMARY == sensor->sensor_index)
		SETREG8(COMMAND_REG4, 0x0f & CLK_DIVIDER);
	else
		SETREG8(COMMAND_REG4, 0xf0 & CLK_DIVIDER);
#endif

	SETREG8(COMMAND_REG5, reg5);
#if 0
    if (DVP != sensor->interface_type)
    {
    	SETREG8(COMMAND_REG6, reg3c13);
    	SETREG8(COMMAND_REG7, reg3c15);
    }
#endif
#ifdef READ_BACK_RAW
	SETREG8(ISP_INPUT_FORMAT, 0x61);
#endif

	ap_writeAE_mode = GETREG8(REG_ISP_AECAGC_WRITESENSOR_ENABLE);
	ap_writeAE_mode &= 0x1;
	if (ap_writeAE_mode == ISP_WRITESENSOR_DISABLE) {
		delay_clk = sensor->ap_writeAE_delay;
		/* check if delay time is longer than 10ms*/
		if (delay_clk > 10000)
			delay_clk = 10000;
		delay_clk *= (ISP_CLOCK / 1000000);
		delay_clk /= 256;
	} else {
		delay_clk = 0;
	}
	SETREG8(COMMAND_REG8, (delay_clk >> 8));
	SETREG8(COMMAND_REG9, (delay_clk & 0xff));

#ifdef CONFIG_MACH_HI6620SFT
    /*FIXME:FPGA cause 24M of DDR we set line blanking longer in zoom in mode in asic do not need set*/
    SETREG8(REG_ISP_SCALE_UP_COUNT_OF_FRAME,0x64);
#endif

	SETREG8(COMMAND_REG0, CMD_SET_FORMAT);

	return wait_cmd_timeout(CMD_SET_FORMAT, WAIT_COMPLT_TIMEOUT);
}

int mini_atoi16(char *s)
{
	char *p = s;
	char c;
	int pos = 0;
	bool b16 = false;
	int ret = 0;

	if (s == NULL)
		return 0;
	while ((c = *p++) != '\0') {
		pos++;
		if (c == '0' && ((*p == 'x') || (*p == 'X'))) {
			pos++;
			b16 = true;
			break;
		}
	}
	if (b16) {
		p = s + pos;
		while ((c = *p++) != '\0') {
			if ('0' <= c && c <= '9') {
				ret *= 16;
				ret += c - '0';
			} else if ('a' <= c && c <= 'f') {
				ret *= 16;
				ret += c - 'a' + 10;
			} else if ('A' <= c && c <= 'Z') {
				ret *= 16;
				ret += c - 'A' + 10;
			} else {
				break;
			}
		}
	}
	return ret;
}

#if 0
static int ispv1_load_isp_setting(char *filename)
{
	struct kstat stat;
	mm_segment_t fs;
	struct file *fp = NULL;
	int file_flag = O_RDONLY;
	ssize_t ret = 0;
	u32 addr = 0;
	u8 value;
	char addr_array[8] = {0};
	char value_array[6] = {0};
	char temp;
	bool bRegStart = false;

	if (NULL == filename) {
		print_error("%s param error", __func__);
		return -EINVAL;
	}

	print_debug("enter %s", __func__);

	/* must have the following 2 statement */
	fs = get_fs();
	set_fs(KERNEL_DS);

	fp = filp_open(filename, file_flag, 0666);
	if (IS_ERR_OR_NULL(fp)) {
		print_info("open file error!\n");
		return -1;
	}

	if (0 != vfs_stat(filename, &stat)) {
		print_error("failed to get file state!");
		goto ERROR;
	}
	print_debug("file size : %d", (u32) stat.size);
	while (0 < vfs_read(fp, &temp, 1, &fp->f_pos)) {
		switch (temp) {
		case '{':
			bRegStart = true;
			if (0 == vfs_read(fp, addr_array, 7, &fp->f_pos))
				goto ERROR;
			addr = mini_atoi16(addr_array);
			break;

		case '}':
			bRegStart = false;
			break;

		case ',':
			if (bRegStart) {
				if (0 == vfs_read(fp, value_array, 5, &fp->f_pos))
					goto ERROR;
				value = mini_atoi16(value_array);
				bRegStart = false;

				/*write reg*/
				print_debug("addr=0x%x, value=0x%x", addr, value);
				SETREG8(addr, value);
			}
			break;

		default:
			break;
		}
	}

	/* must have the following 1 statement */
	set_fs(fs);

ERROR:
	if (NULL != fp)
		filp_close(fp, 0);
	return ret;
}
#endif
/*
 **************************************************************************
 * FunctionName: ispv1_start_preview;
 * Description : call cmdset to start preview;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_start_preview(mini_pic_attr_t *pic_attr, mini_camera_sensor *sensor, bool cold_boot, camera_scene scene)
{
	mini_camera_frame_buf *frame = NULL;

	mini_isp_hw_data.cur_state = STATE_PREVIEW;

    if (CAMERA_ZSL_ON == mini_this_ispdata->zsl_ctrl.zsl_state){
	    mini_this_ispdata->zsl_ctrl.focused_frame_cnt = 1;
	}

	mini_isp_hw_data.frame_count = 0;
	mini_isp_hw_data.irq_val.mcu_cmd_finish = 0;
    SETREG8(REG_ISP_INT_EN, MASK_CMDSET_INT_ENABLE | MASK_MAC_INT_ENABLE);/* Enable CMD_SET MAC_INT int */

	ispv1_preview_cmd(pic_attr, sensor, cold_boot, scene);

	mini_dump_size_reg();

	frame = ispv1_move_queue_element(&mini_isp_hw_data.data_queue_ref->ready_q[STATE_PREVIEW],
				CAMERA_FLAG_READYQ,
				&mini_isp_hw_data.data_queue_ref->work_q[STATE_PREVIEW],
				CAMERA_FLAG_WORKQ);
	if (frame)
		ispv1_hardware_update_addr(frame->phyaddr, frame->statphyaddr,&mini_isp_hw_data.preview_uv_offset, BUF_LEFT);
	else
		return -ENOMEM;

	ispv1_enable_irq();

#ifdef ISP_DEBUG_ZSL
	mini_isp_debug_dump_cmd_reg();
#endif

	#ifdef READ_BACK_RAW
	u32 viraddr = 0;
	viraddr = ioremap_nocache(RAW_PHYADDR, 3264 * 2448 * 2);//1600 * 1200 * 2   3264 * 2448 * 2
	if(0 != viraddr) {
		if (0 <= mini_load_raw_file("/data/raw10.raw", viraddr))
			print_info("read raw file ok!!!");
		else
			print_info("please push raw file to phone as /data/raw10.raw!!!");

		mb();
		iounmap(viraddr);
	} else {
		print_info("don't have enough memory");
	}
	SETREG32(0x63b20, RAW_PHYADDR);
	SETREG32(0x63b24, RAW_PHYADDR);
	SETREG32(0x63b28, RAW_PHYADDR);
	SETREG32(0x63b2c, RAW_PHYADDR);
	SETREG8(0x63b57, 1);
	#endif

	mini_isp_hw_data.preview_stop = false;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ispv1_start_proc_img;
 * Description : call cmdset to start process; raw -> yuv,process image with previe
 * Input       : mini_pic_attr_t *pic_attr, ipp_mode mode, mini_buffer_arr_t *ipp_buf_arr;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_start_proc_img(mini_pic_attr_t *pic_attr, ipp_mode mode, mini_buffer_arr_t *ipp_buf_arr)
{
    int                                 ret = 0;
    mini_camera_frame_buf                    *framesrc = NULL;
    mini_camera_frame_buf                    *framedst = NULL;
    unsigned long                       lock_flags;
    struct list_head                    *source;
    struct list_head                    *target;
	u8 __iomem                          *src_viraddr;
	u8 __iomem                          *dst_viraddr;
	u8                                  proc_cnt  = 0;

    print_debug("enter %s", __func__);
    print_debug("%s:CAMERA_ZSL_ON", __func__);
    if (CAMERA_ZSL_OFFLINE == mini_this_ispdata->zsl_ctrl.zsl_proc_mode){
        print_debug("%s:CAMERA_ZSL_OFFLINE", __func__);

        framedst = ispv1_move_queue_element(&mini_isp_hw_data.data_queue_ref->ready_q[STATE_CAPTURE],
                                            CAMERA_FLAG_READYQ,
                                            &mini_isp_hw_data.data_queue_ref->work_q[STATE_CAPTURE],
                                            CAMERA_FLAG_WORKQ);
        if (framedst == NULL) {
            print_error("%s:framedst == NULL", __func__);
            return -EINVAL;
        }

        while ((proc_cnt < PROC_IMAGE_TRY_MAX_TIMES) && (true == mini_this_ispdata->zsl_ctrl.zsl_proc_valid)){
            proc_cnt = proc_cnt + 1;
            ret = ispv1_start_proc_img_with_preview_cmd(pic_attr,ipp_buf_arr,framedst->phyaddr);
            if (0 == ret){
                break;
            } else {
                print_warn("%s:ispv1_start_proc_img fail.proc_cnt=%d.",__func__,proc_cnt);
            }
        }

        if (false == mini_this_ispdata->zsl_ctrl.zsl_proc_valid){
            print_warn("%s:zsl_proc_valid = false.cancel proc.",__func__);
            return -EPERM;
        } else {
            /* FIXME: */
            if (0 != ret){
                print_error("%s:ispv1_start_proc_img try max times fail.",__func__);
                //ret = 0;//return err to notify HAL.
            }
        }

        if (0 == ret){
            framedst = ispv1_move_queue_element(&mini_isp_hw_data.data_queue_ref->work_q[STATE_CAPTURE],
                    				CAMERA_FLAG_WORKQ,
                    				&mini_isp_hw_data.data_queue_ref->done_q[STATE_CAPTURE],
                    				CAMERA_FLAG_DONEQ);
            if (NULL == framedst){
                print_error("%s:ispv1_move_queue_element fail.frame null.",__func__);
                return -EINVAL;
            }

            wake_up_interruptible(&mini_isp_hw_data.data_queue_ref->queue[STATE_CAPTURE]);

            /* process raw buffer one by one */
            if (mini_this_ispdata->zsl_ctrl.zsl_proc_idx > 0){
                mini_this_ispdata->zsl_ctrl.zsl_proc_idx = mini_this_ispdata->zsl_ctrl.zsl_proc_idx - 1;
            }
        } else {
            print_error("%s:ispv1_start_proc_img_with_preview_cmd fail.ret=%d.",__func__,ret);

            framedst = ispv1_move_queue_element(&mini_isp_hw_data.data_queue_ref->work_q[STATE_CAPTURE],
                    				CAMERA_FLAG_WORKQ,
                    				&mini_isp_hw_data.data_queue_ref->ready_q[STATE_CAPTURE],
                    				CAMERA_FLAG_READYQ);
            if (NULL == framedst){
                print_error("%s:ispv1_move_queue_element fail.framedst NULL.",__func__);
                return -EINVAL;
            }
        }

        return ret;

    }
    else{
        print_debug("%s:CAMERA_ZSL_ONLINE", __func__);

        if (mini_this_ispdata->zsl_ctrl.history_buf_idx >= mini_this_ispdata->zsl_ctrl.history_buf_cnt){
            print_error("invalid capture buffer index:%d.",mini_this_ispdata->zsl_ctrl.history_buf_idx);
            return -EINVAL;
        }

        framesrc    = &(ipp_buf_arr->buffers[mini_this_ispdata->zsl_ctrl.history_buf_idx]);
        spin_lock_irqsave(&mini_isp_hw_data.data_queue_ref->queue_lock, lock_flags);

        source = &mini_isp_hw_data.data_queue_ref->ready_q[STATE_CAPTURE];
        target = &mini_isp_hw_data.data_queue_ref->done_q[STATE_CAPTURE];

        if (!list_empty(source)) {
            framedst = list_entry(source->next, mini_camera_frame_buf, queue);
            mini_del_from_queue(framedst, CAMERA_FLAG_READYQ);
        } else {
            print_error("queue empty state:%d, queue flag %d, line=%d", mini_isp_hw_data.cur_state, CAMERA_FLAG_READYQ, __LINE__);
            spin_unlock_irqrestore(&mini_isp_hw_data.data_queue_ref->queue_lock, lock_flags);
            return -EINVAL;
        }

        spin_unlock_irqrestore(&mini_isp_hw_data.data_queue_ref->queue_lock, lock_flags);

#ifdef ISP_ZSL_NO_MEMCPY
        /* switch buf between IPP buf and Capture buf.   */
        memcpy(&frametmp,framesrc,sizeof(frametmp));
        memcpy(framesrc,framedst,sizeof(frametmp));
        memcpy(framedst,&frametmp,sizeof(frametmp));
#else
        /* use memcpy to move buf from IPP queue to Capture queue.   */
        dst_viraddr = ioremap_nocache(framedst->phyaddr, framedst->size);
        if(0 == dst_viraddr) {
            print_debug("%s:dst_viraddr null,ioremap fail.", __func__);
            return -EINVAL;
        }
        print_debug("%s:framedst->phyaddr=0x%x,dst_viraddr=0x%x", __func__,framedst->phyaddr,dst_viraddr);

        src_viraddr = ioremap_nocache(framesrc->phyaddr, framedst->size);
        if(0 == src_viraddr) {
            print_debug("%s:src_viraddr null,ioremap fail.", __func__);
            iounmap(dst_viraddr);
            return -EINVAL;
        }
        print_debug("%s:framesrc->phyaddr=0x%x,src_viraddr=0x%x", __func__,framesrc->phyaddr,src_viraddr);

#ifdef ISP_DEBUG_ZSL
        if (zsl_copy_flg == 1){
            memcpy(dst_viraddr,src_viraddr,framesrc->size);
        }
#else
        memcpy(dst_viraddr,src_viraddr,framesrc->size);
#endif

        iounmap(dst_viraddr);
        iounmap(src_viraddr);
#endif
        spin_lock_irqsave(&mini_isp_hw_data.data_queue_ref->queue_lock, lock_flags);
        mini_add_to_queue(framedst, target, CAMERA_FLAG_DONEQ);
        wake_up_interruptible(&mini_isp_hw_data.data_queue_ref->queue[STATE_CAPTURE]);

        spin_unlock_irqrestore(&mini_isp_hw_data.data_queue_ref->queue_lock, lock_flags);

        print_info("zsl_proc_idx=%d,cap_buf_idx=%d", mini_this_ispdata->zsl_ctrl.zsl_proc_idx,mini_this_ispdata->zsl_ctrl.history_buf_idx);

        /* decrease idx to support execute multi proc_img_with_preview after stop_cap_with_preview  */
        if (mini_this_ispdata->zsl_ctrl.zsl_proc_idx > 0){
            mini_this_ispdata->zsl_ctrl.zsl_proc_idx = mini_this_ispdata->zsl_ctrl.zsl_proc_idx - 1;
            mini_this_ispdata->zsl_ctrl.history_buf_idx  = (mini_this_ispdata->zsl_ctrl.history_buf_idx + 1)%mini_this_ispdata->zsl_ctrl.history_buf_cnt;
        }

        return 0;
    }

}

/*
 **************************************************************************
 * FunctionName: ispv1_start_process;
 * Description : call cmdset to start process; raw -> yuv,process image with previe
 * Input       : mini_pic_attr_t *pic_attr, ipp_mode mode, mini_buffer_arr_t *ipp_buf_arr;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_start_process(mini_pic_attr_t *pic_attr, u8 mode, mini_buffer_arr_t *ipp_buf_arr)
{
	int                                 ret = 0;
	mini_camera_frame_buf                    *framesrc = NULL;
	mini_camera_frame_buf                    *framedst = NULL;
	u32                                 addr_hdr_long, addr_hdr_short;

    print_debug("enter %s", __func__);
    /* if ZSL switch on */
    if (CAMERA_ZSL_ON == mini_this_ispdata->zsl_ctrl.zsl_state){
        if (false == mini_this_ispdata->zsl_ctrl.zsl_proc_valid)
        {
            print_warn("%s:zsl_proc_valid=false.",__func__);
            return -EPERM;
        }
	#ifdef SUPPORT_ZSL_FLASH
	  zsl_wait_to_start_capture_with_flash();
	 #endif
        ret = ispv1_start_proc_img(pic_attr, mode, ipp_buf_arr);
        if (0 != ret){
            print_warn("%s:ispv1_start_proc_img fail.ret=%d.",__func__,ret);;
        }

        return ret;
	}


	framedst = ispv1_move_queue_element(&mini_isp_hw_data.data_queue_ref->ready_q[STATE_IPP],
				CAMERA_FLAG_READYQ,
				&mini_isp_hw_data.data_queue_ref->work_q[STATE_IPP],
				CAMERA_FLAG_WORKQ);
	if (framedst == NULL) {
		return -EINVAL;
	}

	framesrc = ispv1_del_queue_element(&mini_isp_hw_data.data_queue_ref->ready_q[STATE_CAPTURE], CAMERA_FLAG_READYQ);
	if (framesrc == NULL) {
		return -EINVAL;
	}

	mini_isp_hw_data.cur_state = STATE_IPP;

    SETREG8(REG_ISP_INT_EN, MASK_CMDSET_INT_ENABLE | MASK_MAC_INT_ENABLE);/* Enable CMD_SET MAC_INT int */

	if (mode == CAMERA_IPP_MODE_HDR) {
		volatile unsigned short reg;
		addr_hdr_long = framesrc->phyaddr;
		framesrc = ispv1_del_queue_element(&mini_isp_hw_data.data_queue_ref->ready_q[STATE_CAPTURE], CAMERA_FLAG_READYQ);
		if (framesrc == NULL) {
			return -EINVAL;
		}
		addr_hdr_short = framesrc->phyaddr;
		reg = GETREG8(REG_ISP_TOP4);
		ispv1_enable_irq();
		ret = ispv1_hdr_cmd(pic_attr, addr_hdr_long, addr_hdr_short, framedst->phyaddr);
		SETREG8(REG_ISP_TOP4,  reg);
		if (0 != ret)
			print_error("hdr cmd  set failed.\n");
	} else {
		print_debug("****framesrc=0x%p, idx=%d, flag=%d, phy=0x%x****",
			framesrc, framesrc->index, framesrc->flags, framesrc->phyaddr);
		ret = ispv1_offline_cmd(pic_attr, framesrc->phyaddr, framedst->phyaddr);
		if (0 != ret)
			print_error("bypass cmd set failed.\n");
	}

#ifdef READ_BACK_RAW
		u32 viraddr = 0;
		viraddr = ioremap_nocache(framedst->phyaddr, 3264 * 2448 * 2);//1600 * 1200 * 2   3264*2448*2
		if(0 != viraddr) {
			memset(viraddr, 0, 3264 * 2448 * 2);//1600 * 1200 * 2  3264*2448*2
			mb();
			iounmap(viraddr);
		}
		msleep(100);
		ret = ispv1_offline_cmd(pic_attr, RAW_PHYADDR, framedst->phyaddr);
//#else
//		ret = ispv1_offline_cmd(pic_attr, framesrc->phyaddr, framedst->phyaddr);
#endif

#ifdef DUMP_CAP_FILE
	mini_dump_file("/data/nv12.yuv", framedst->viraddr,
		  pic_attr->out_width * pic_attr->out_height * 3 / 2);
#endif

	return ret;

}

#ifdef READ_BACK_RAW
void ispv1_update_read_ready(u8 buf_used)
{
	if (BUF_LEFT == buf_used)
		SETREG8(0x63b57, 1);
	else
		SETREG8(0x63b57, 2);
}
#endif
/*
 **************************************************************************
 * FunctionName: ispv1_start_capture;
 * Description : call cmdset to start capture;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_start_capture(mini_pic_attr_t *pic_attr, mini_camera_sensor *sensor, int *ev, bool flash_on, camera_scene scene,	mini_buffer_arr_t *buf_arr)
{
	int ret = 0;
	mini_camera_frame_buf *frame = NULL;
	int count = 1;
	mini_isp_hw_data.irq_val.mcu_cmd_finish = 0;
	print_debug("enter %s", __func__);

    /* if ZSL switch on */
    if (CAMERA_ZSL_ON == mini_this_ispdata->zsl_ctrl.zsl_state) {
        if ((true == mini_this_ispdata->zsl_ctrl.zsl_online_enable) && (CAMERA_ZSL_ONLINE == mini_this_ispdata->zsl_ctrl.zsl_proc_mode)){
            if (CAMERA_ZSL_CAP_CMD_RESUME == mini_this_ispdata->zsl_ctrl.zsl_cap_cmd) {
                //ret = ispv1_resume_capture_with_preview_cmd(pic_attr, buf_arr);
                ret = ispv1_start_capture_yuv_with_preview_cmd(pic_attr, buf_arr);
                if (0 != ret){
                    print_error("resume capture yuv with preview fail.ret=%d",ret);
                }
            } else {
                ret = ispv1_start_capture_yuv_with_preview_cmd(pic_attr, buf_arr);
                if (0 != ret){
                    print_error("start capture yuv with preview fail.ret=%d",ret);
                }
            }
        } else {
        #ifdef ISP_DEBUG_ZSL
            /* in order to print reg after offline process finished */
			mini_isp_debug_dump_cmd_reg();
		#endif
            ret = ispv1_start_capture_raw_with_preview_cmd(pic_attr, buf_arr);
            if (0 != ret){
                print_error("start capture raw with preview fail.ret=%d",ret);
            }
        }
    #ifdef ISP_DEBUG_ZSL
        mini_isp_debug_dump_cmd_reg();
    #endif
        return ret;
    }

	mini_isp_hw_data.frame_count = 0;

	/* if (ispv1_get_process_mode() == ISP_CAPTURE_OFFLINE) */
	if (CAMERA_SHOOT_BURST == mini_this_ispdata->shoot_mode)
		mini_burst_capture = true;
	else
		mini_burst_capture = false;
	count = mini_get_queue_size(&mini_isp_hw_data.data_queue_ref->ready_q[STATE_CAPTURE]);

	if (count > 3) {
		//mini_burst_capture = true;
		count = 1;
	} else {
		//mini_burst_capture = false;
	}

	frame = ispv1_move_queue_element(&mini_isp_hw_data.data_queue_ref->ready_q[STATE_CAPTURE],
				CAMERA_FLAG_READYQ,
				&mini_isp_hw_data.data_queue_ref->work_q[STATE_CAPTURE],
				CAMERA_FLAG_WORKQ);
	if (NULL == frame) {
		return -EINVAL;
	}
	mini_isp_hw_data.offline_state = OFFLINE_READY;
	mini_isp_hw_data.cur_state = STATE_CAPTURE;

    SETREG8(REG_ISP_INT_EN, MASK_CMDSET_INT_ENABLE | MASK_MAC_INT_ENABLE);/* Enable CMD_SET MAC_INT int */

	#ifndef READ_BACK_RAW
	ret = ispv1_capture_cmd(pic_attr, frame->phyaddr, count, ev, sensor, flash_on, scene);
	if (0 != ret) {
		print_error("capture cmd set failed.\n");
		return -EINVAL;
	}

	mini_dump_size_reg();
	#else
	ispv1_frame_done_handler(mini_isp_hw_data.cur_state);
	#endif

#ifdef DUMP_CAP_FILE
	mini_dump_file("/data/raw.raw", frame->viraddr,
			pic_attr->sensor_width * pic_attr->sensor_height * 2);
#endif

	print_debug("capture cmdset ok");
	return ret;
}

extern u32 misp_cmd_delay_time;
#define WAIT_3A_LOCK_TIMEOUT (200)
static int ispv1_stop_preview(void)
{
	mini_camera_sensor *sensor = mini_this_ispdata->sensor;

	print_info("enter %s", __func__);

	sensor->stream_off(STATE_PREVIEW);

	ispv1_disable_irq();
	mini_isp_hw_data.preview_stop = true;
	tasklet_kill(&mini_isr_tasklet);

#if 0 /* k3 force overflow code */
	/* force ISP mac overflow */
#ifdef OVISP_OFFLINE_MODE
	/*Do not set 0x63b31*/
#else
	SETREG8(0x63b31, (GETREG8(0x63b31) | 0x01));
#endif
#endif

/* for K3V2, there is some problem with frame control, so k3 use force overflow reg;
   after isp2.0, use new frame control, not need force overflow. */
#if 0 /* balong force overflow code */
    if(CAPTURE_OFFLINE != ispv1_get_process_mode())
    {
      SETREG8(0x63b31, (GETREG8(0x63b31) | 0x01));
    }
    print_info("%s, mini_k3_isp_get_process_mode:%d", __FUNCTION__, ispv1_get_process_mode());
    /* end */
#endif

	mini_isp_hw_data.cur_state = STATE_MAX;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ispv1_stop_capture;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_stop_capture(void)
{
    int ret = 0;
	mini_camera_sensor *sensor = mini_this_ispdata->sensor;

    /* if ZSL switch on */
    if (CAMERA_ZSL_ON == mini_this_ispdata->zsl_ctrl.zsl_state) {
        if ((CAMERA_ZSL_ONLINE == mini_this_ispdata->zsl_ctrl.zsl_proc_mode)
           && (CAMERA_ZSL_CAP_CMD_SUSPEND == mini_this_ispdata->zsl_ctrl.zsl_cap_cmd)){
            ret = ispv1_stop_capture_with_preview_cmd();
            //ret = ispv1_suspend_capture_with_preview_cmd();
            if (0 != ret){
                print_error("suspend capture yuv with preview fail.ret=%d",ret);
            }
        }
        else{
            ret = ispv1_stop_capture_with_preview_cmd();
            if (0 != ret){
                print_error("%s:ispv1_stop_capture_with_preview_cmd fail.ret=%d",__func__,ret);
            }
        }
        return ret;
    }
	if(sensor->stream_off!=NULL)
		sensor->stream_off(STATE_CAPTURE);//by wind++

	ispv1_disable_irq();
	mini_burst_capture = false;
	print_info("enter %s", __func__);
	tasklet_kill(&mini_isr_tasklet);
	mini_isp_hw_data.cur_state = STATE_MAX; /* isr should executed before this sentence */

	/* double resume(another is preview_cmd) preview awb value to make sure it take effect. */
	if (mini_isp_hw_data.flash_resume == true) {
		mini_ispv1_set_wb_value(&mini_isp_hw_data.preview_awb);
		mini_isp_hw_data.flash_resume = false;
	}

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ispv1_stop_proc_img;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_stop_proc_img(void)
{
#ifdef SUPPORT_ZSL_FLASH
	if(zsl_flash_process==1)
	{
		zsl_flash_process = 0;
	}
#endif
    return 0;
}

/*
 **************************************************************************
 * FunctionName: ispv1_stop_process;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_stop_process(u8 mode)
{
    if (CAMERA_ZSL_ON == mini_this_ispdata->zsl_ctrl.zsl_state){
        return ispv1_stop_proc_img();
    } else {
        ispv1_disable_irq();
        print_info("enter %s", __func__);
        mini_isp_hw_data.cur_state = STATE_MAX; /* isr should executed before this sentence */
        return 0;
    }
}

/*
 **************************************************************************
 * FunctionName: ispv1_update_addr;
 * Description : Update the address that used for preview data;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_update_addr(u32 phyaddr,u32 statphyaddr,mini_uv_offset *puvoffset)
{
	/*print_debug("enter %s, phyaddr is 0x%0x", __func__, phyaddr); */
	assert(phyaddr);
	assert(puvoffset);

	if (REG_BASE_ADDR1_WRITING & GETREG8(REG_BASE_WORKING_ADDR)) {
		if (WRITE_ADDR0_READY & GETREG8(REG_BASE_ADDR_READY)) {
			print_error("BUF_LEFT:buf has been set before\n");
			return -EFAULT;
		} else {
			ispv1_hardware_update_addr(phyaddr, statphyaddr,puvoffset, BUF_LEFT);
		}
	} else {
		if (WRITE_ADDR1_READY & GETREG8(REG_BASE_ADDR_READY)) {
			print_error("BUF_RIGHT:buf has been set before\n");
			return -EFAULT;
		} else {
			ispv1_hardware_update_addr(phyaddr, statphyaddr,puvoffset, BUF_RIGHT);
		}
	}

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ispv1_check_config;
 * Description : Set yuv offset according to width, height and format;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_check_config(struct v4l2_pix_format *pixfmt,camera_state state)
{
    mini_uv_offset        *puvoffset = NULL;

    if (pixfmt == NULL) {
        print_error("%s:null ptr.pixfmt=%d.", __func__, pixfmt);
        return -EINVAL;
    }

    if (state == STATE_PREVIEW){
        puvoffset = &mini_isp_hw_data.preview_uv_offset;
    } else if (state == STATE_CAPTURE) {
        puvoffset = &mini_isp_hw_data.capture_uv_offset;
    } else {
        print_error("%s:invalid state=%d.", __func__, state);
        return -EINVAL;
    }

	switch (pixfmt->pixelformat) {
		/* YUV422 packet */
	case V4L2_PIX_FMT_YUYV:
		{
			puvoffset->uoffset = 0;
			puvoffset->voffset = 0;
			break;
		}

		/* YUV420 semi-planar */
	case V4L2_PIX_FMT_NV21:
	case V4L2_PIX_FMT_NV12:
		{
			puvoffset->uoffset = pixfmt->width * pixfmt->height;
			puvoffset->voffset = puvoffset->uoffset;
			break;
		}
	case V4L2_PIX_FMT_YVU420:
		{
			puvoffset->voffset = pixfmt->width * pixfmt->height;
			puvoffset->uoffset = puvoffset->voffset + (((pixfmt->width / 2) + 0xf) & (~0xf)) * pixfmt->height / 2;
			break;
		}
	case V4L2_PIX_FMT_YUV420:
		{
			puvoffset->uoffset = pixfmt->width * pixfmt->height;
			puvoffset->voffset = puvoffset->uoffset + (((pixfmt->width / 2) + 0xf) & (~0xf)) * pixfmt->height / 2;
			break;
		}

	default:
		{
			print_error("Invalid isp_data.out_fmt[%08x]", pixfmt->pixelformat);
			return -EINVAL;
		}
	}

	return 0;

}

#define I2C_GROUP_WRITE       0
#define ISP_I2C_POLL_INTERVAL 10 /*10us*/
#define ISP_I2C_POLL_MAX_COUNT 4000 /* 4000x10us=40ms */

static inline int get_i2c_bus_mutex(int wait_flag)
{
	int count = 0;

	if (wait_flag == SCCB_BUS_MUTEX_NOWAIT) {
		if ((GETREG8(REG_SCCB_BUS_MUTEX) & SCCB_MASTER_LOCK) != SCCB_MASTER_LOCK) {
			SETREG8(REG_SCCB_BUS_MUTEX, SCCB_MASTER_LOCK);
			return 0;
		} else {
			print_error("%s: bus mutex lock, wait_flag %d", __func__, wait_flag);
			return -1;
		}
	} else if (wait_flag == SCCB_BUS_MUTEX_WAIT) {
		while (count < ISP_I2C_POLL_MAX_COUNT) {
			if ((GETREG8(REG_SCCB_BUS_MUTEX) & SCCB_MASTER_LOCK) != SCCB_MASTER_LOCK) {
				SETREG8(REG_SCCB_BUS_MUTEX, SCCB_MASTER_LOCK);
				break;
			}
			udelay(ISP_I2C_POLL_INTERVAL);
			if(0 == count % 1000 )
			print_error("%s: bus mutex lock and timeout, wait_flag %d, count %d", __func__, wait_flag, count);
			count++;
		}
		if (count >= ISP_I2C_POLL_MAX_COUNT) {
			print_error("%s: bus mutex lock failed, count %d", __func__, count);
			return -1;
		}
		return 0;
	} else {
		print_error("%s: invalid wait_flag %d", __func__, wait_flag);
		return -1;
	}
}

static inline void free_i2c_bus_mutex(void)
{
	SETREG8(REG_SCCB_BUS_MUTEX, SCCB_MASTER_UNLOCK);
}

static inline int wait_i2c_bus_idle(u32 reg_status)
{
	int count = 0;

	while (count < ISP_I2C_POLL_MAX_COUNT) {
		if ((GETREG8(reg_status) & SCCB_MASTER_BUSY) != SCCB_MASTER_BUSY)
			break;
		udelay(ISP_I2C_POLL_INTERVAL);
		count++;
	}
	if (count >= ISP_I2C_POLL_MAX_COUNT) {
		return -1;
	}
	return 0;
}

static DEFINE_SPINLOCK(i2c_lock);
/*
 **************************************************************************
 * FunctionName: ispv1_update_flip;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ispv1_update_lenc_offset(u8 flip_state, u16 width, u16 height)
{
	print_info("%s, width:0x%0x, height:0x%0x", __func__, width, height);
	switch (flip_state) {
	case 1:
		SETREG16(REG_ISP_LENC_HORIZONTAL_OFFSET, width);
		SETREG16(REG_ISP_LENC_VERITAL_OFFSET, 0x00);
		break;
	case 2:
		SETREG16(REG_ISP_LENC_HORIZONTAL_OFFSET, 0x00);
		SETREG16(REG_ISP_LENC_VERITAL_OFFSET, height);
		break;
	case 3:
		SETREG16(REG_ISP_LENC_HORIZONTAL_OFFSET, width);
		SETREG16(REG_ISP_LENC_VERITAL_OFFSET, height);
		break;
	default:
		SETREG16(REG_ISP_LENC_HORIZONTAL_OFFSET, 0x00);
		SETREG16(REG_ISP_LENC_VERITAL_OFFSET, 0x00);
	}
}

/*
 **************************************************************************
 * FunctionName: ispv1_update_flip;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
     [1:0]pixel order descriptions
     00 - GR/BG
     01 - RG/GB
     10 - BG/GR
     11 - GB/RG
 **************************************************************************
 */
static void ispv1_update_flip(u8 flip_changed, u16 width, u16 height, pixel_order changed)
{
	volatile u8 reg_val = GETREG8(REG_ISP_TOP6);
	u8 mask;
	switch (flip_changed) {
	case 1:
		print_info("%s, mirror change, reg_val:0x%0x", __func__, reg_val);
		mask = 0x04 | (changed & 0x01);
        reg_val = reg_val ^ mask;
		break;
	case 2:
		print_info("%s, flip change, reg_val:0x%0x", __func__, reg_val);
		mask = 0x08 | (changed & 0x02);
		reg_val = reg_val ^ mask;
		break;
	case 3:
		print_info("%s, mirror and flip change, reg_val:0x%0x", __func__, reg_val);
		mask = 0x0c | (changed & 0x03);
        reg_val = reg_val ^ mask;
		break;
	default:
		print_info("%s, mirror and flip is not change", __func__);
	}
	SETREG8(REG_ISP_TOP6, reg_val);
	ispv1_update_lenc_offset((reg_val >> 2) & 0x03, width, height);
}

/*
 **************************************************************************
 * FunctionName: ispv1_read_sensor_byte;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_read_sensor_byte(i2c_index_t index, u8 i2c_addr, u16 reg, u16 *val, i2c_length length, i2c_length addr_len)
{
	unsigned long flags;
	int reg_device_id, reg_reg_h, reg_reg_l, reg_cmd, reg_status, reg_value_h, reg_value_l, reg_value_len;
	volatile int val_h, val_l;
	u8 byte_ctrl = 0;

return 0;
	print_debug("%s:i2c group %d, id:0x%x, reg:0x%x!", __func__, index, i2c_addr, reg);

	if (index == I2C_PRIMARY) {
		reg_device_id = REG_SCCB_MAST1_SLAVE_ID;
		reg_reg_h = REG_SCCB_MAST1_ADDRESS_H;
		reg_reg_l = REG_SCCB_MAST1_ADDRESS_L;
		reg_cmd = REG_SCCB_MAST1_COMMAND;
		reg_status = REG_SCCB_MAST1_STATUS;
		reg_value_h = REG_SCCB_MAST1_INPUT_DATA_H;
		reg_value_l = REG_SCCB_MAST1_INPUT_DATA_L;
		reg_value_len = REG_SCCB_MAST1_2BYTE_CONTROL;
	} else {
		reg_device_id = REG_SCCB_MAST2_SLAVE_ID;
		reg_reg_h = REG_SCCB_MAST2_ADDRESS_H;
		reg_reg_l = REG_SCCB_MAST2_ADDRESS_L;
		reg_cmd = REG_SCCB_MAST2_COMMAND;
		reg_status = REG_SCCB_MAST2_STATUS;
		reg_value_h = REG_SCCB_MAST2_INPUT_DATA_H;
		reg_value_l = REG_SCCB_MAST2_INPUT_DATA_L;
		reg_value_len = REG_SCCB_MAST2_2BYTE_CONTROL;
	}

	if (get_i2c_bus_mutex(SCCB_BUS_MUTEX_WAIT)) {
		print_error("%s, line %d: I2c get mutex timeout!", __func__, __LINE__);
		return -EFAULT;
	}

	if (wait_i2c_bus_idle(reg_status)) {
		print_error("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
		goto error_out2;
	}

	if(I2C_16BIT == addr_len)
		byte_ctrl |= MASK_16BIT_ADDR_ENABLE;
	spin_lock_irqsave(&i2c_lock, flags);
	if (I2C_8BIT == length) {
		SETREG8(reg_value_len, byte_ctrl);
		SETREG8(reg_device_id, i2c_addr);
		SETREG8(reg_reg_h, reg >> 8 & 0xff);
		SETREG8(reg_reg_l, reg & 0xff);
		SETREG8(reg_cmd, 0x33);
		if (wait_i2c_bus_idle(reg_status)) {
			print_error("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
			goto error_out1;
		}

		SETREG8(reg_cmd, 0xf9);
		if (wait_i2c_bus_idle(reg_status)) {
			print_error("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
			goto error_out1;
		}

		*(u8 *)val = GETREG8(reg_value_l);
	} else {
		byte_ctrl |= MASK_16BIT_DATA_ENABLE;
		SETREG8(reg_value_len, byte_ctrl);
		SETREG8(reg_device_id, i2c_addr);
		SETREG8(reg_reg_h, reg >> 8 & 0xff);
		SETREG8(reg_reg_l, reg & 0xff);
		SETREG8(reg_cmd, 0x33);
		if (wait_i2c_bus_idle(reg_status)) {
			print_error("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
			goto error_out1;
		}

		SETREG8(reg_value_len, byte_ctrl & ~MASK_16BIT_DATA_ENABLE);
		SETREG8(reg_cmd, 0x59);

		if (wait_i2c_bus_idle(reg_status)) {
			print_error("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
			goto error_out1;
		}

		val_h = GETREG8(REG_SCCB_MAST1_INPUT_DATA_L);

		SETREG8(reg_cmd, 0xa8);
		if (wait_i2c_bus_idle(reg_status)) {
			print_error("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
			goto error_out1;
		}
		val_l = GETREG8(REG_SCCB_MAST1_INPUT_DATA_L);

		*val = (val_h << 8) | val_l;
	}
	spin_unlock_irqrestore(&i2c_lock, flags);
	free_i2c_bus_mutex();
	return 0;

error_out1:
	spin_unlock_irqrestore(&i2c_lock, flags);
error_out2:
	*val = 0xff;
	free_i2c_bus_mutex();
	return -EFAULT;
}

/*
 **************************************************************************
 * FunctionName: ispv1_read_sensor_byte;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
#if 0

static int ispv1_read_sensor_byte_addr8(i2c_index_t index, u8 i2c_addr, u16 reg, u16 *val, i2c_length length)
{
	unsigned long flags;
	int reg_device_id, reg_firmware_id,reg_reg_h, reg_reg_l, reg_cmd, reg_status, reg_value_h, reg_value_l, reg_value_len;
	volatile int val_h, val_l;

	volatile int device_id, firmware_id;
return 0;
	print_debug("%s:i2c group %d, id:0x%x, reg:0x%x!", __func__, index, i2c_addr, reg);

	if (index == I2C_PRIMARY) {
		reg_device_id = REG_SCCB_MAST1_SLAVE_ID;
		reg_firmware_id = REG_SCCB_FIRMWARE1_ID;
		reg_reg_h = REG_SCCB_MAST1_ADDRESS_H;
		reg_reg_l = REG_SCCB_MAST1_ADDRESS_L;
		reg_cmd = REG_SCCB_MAST1_COMMAND;
		reg_status = REG_SCCB_MAST1_STATUS;
		reg_value_h = REG_SCCB_MAST1_INPUT_DATA_H;
		reg_value_l = REG_SCCB_MAST1_INPUT_DATA_L;
		reg_value_len = REG_SCCB_MAST1_2BYTE_CONTROL;
	} else {
		reg_device_id = REG_SCCB_MAST2_SLAVE_ID;
		reg_firmware_id = REG_SCCB_FIRMWARE2_ID;
		reg_reg_h = REG_SCCB_MAST2_ADDRESS_H;
		reg_reg_l = REG_SCCB_MAST2_ADDRESS_L;
		reg_cmd = REG_SCCB_MAST2_COMMAND;
		reg_status = REG_SCCB_MAST2_STATUS;
		reg_value_h = REG_SCCB_MAST2_INPUT_DATA_H;
		reg_value_l = REG_SCCB_MAST2_INPUT_DATA_L;
		reg_value_len = REG_SCCB_MAST2_2BYTE_CONTROL;
	}

	if (get_i2c_bus_mutex(SCCB_BUS_MUTEX_WAIT)) {
		print_error("%s, line %d: I2c get mutex timeout!", __func__, __LINE__);
		return -EFAULT;
	}

	if (wait_i2c_bus_idle(reg_status)) {
		print_error("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
		goto error_out2;
	}

	spin_lock_irqsave(&i2c_lock, flags);
//backup i2c id in isp reg
	firmware_id = GETREG8(reg_firmware_id);
	device_id = GETREG8(reg_device_id);
	if (I2C_8BIT == length) {
		SETREG8(reg_value_len, 0x00);
		SETREG8(reg_device_id, i2c_addr);
		SETREG8(reg_firmware_id,i2c_addr);
		SETREG8(reg_reg_h, reg >> 8 & 0xff);
		SETREG8(reg_reg_l, reg & 0xff);
		SETREG8(reg_cmd, 0x33);
		if (wait_i2c_bus_idle(reg_status)) {
			print_error("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
			goto error_out1;
		}

		SETREG8(reg_cmd, 0xf9);
		if (wait_i2c_bus_idle(reg_status)) {
			print_error("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
			goto error_out1;
		}

		*(u8 *)val = GETREG8(reg_value_l);
	} else {
		SETREG8(reg_value_len, 0x03);
		SETREG8(reg_device_id, i2c_addr);
		SETREG8(reg_firmware_id, i2c_addr);
		SETREG8(reg_reg_h, reg >> 8 & 0xff);
		SETREG8(reg_reg_l, reg & 0xff);
		SETREG8(reg_cmd, 0x33);
		if (wait_i2c_bus_idle(reg_status)) {
			print_error("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
			goto error_out1;
		}

		SETREG8(reg_value_len, 0x01);
		SETREG8(reg_cmd, 0x59);

		if (wait_i2c_bus_idle(reg_status)) {
			print_error("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
			goto error_out1;
		}

		val_h = GETREG8(REG_SCCB_MAST1_INPUT_DATA_L);

		SETREG8(reg_cmd, 0xa8);
		if (wait_i2c_bus_idle(reg_status)) {
			print_error("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
			goto error_out1;
		}
		val_l = GETREG8(REG_SCCB_MAST1_INPUT_DATA_L);

		*val = (val_h << 8) | val_l;
		}

//restore i2c id to isp reg
	SETREG8(reg_firmware_id,firmware_id);
	SETREG8(reg_device_id, device_id);

	spin_unlock_irqrestore(&i2c_lock, flags);
	free_i2c_bus_mutex();
	return 0;

error_out1:
	spin_unlock_irqrestore(&i2c_lock, flags);
error_out2:
	*val = 0xff;
	free_i2c_bus_mutex();
	return -EFAULT;
}
#endif

/*
 **************************************************************************
 * FunctionName: ispv1_write_sensor_byte;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_write_sensor_byte(i2c_index_t index, u8 i2c_addr, u16 reg, u16 val, i2c_length length, u8 mask, i2c_length addr_len)
{
	unsigned long flags;
	int reg_device_id, reg_reg_h, reg_reg_l, reg_cmd, reg_status, reg_value_h, reg_value_l, reg_value_len;
	u16 old_val = 0;
	u8 byte_ctrl = 0;

	/* print_debug("%s:i2c group %d, id:0x%x, reg:0x%x!", __func__, index, i2c_addr, reg); */
return 0;
	if (index == I2C_PRIMARY) {
		reg_device_id = REG_SCCB_MAST1_SLAVE_ID;
		reg_reg_h = REG_SCCB_MAST1_ADDRESS_H;
		reg_reg_l = REG_SCCB_MAST1_ADDRESS_L;
		reg_cmd = REG_SCCB_MAST1_COMMAND;
		reg_status = REG_SCCB_MAST1_STATUS;
		reg_value_h = REG_SCCB_MAST1_OUTPUT_DATA_H;
		reg_value_l = REG_SCCB_MAST1_OUTPUT_DATA_L;
		reg_value_len = REG_SCCB_MAST1_2BYTE_CONTROL;
	} else {
		reg_device_id = REG_SCCB_MAST2_SLAVE_ID;
		reg_reg_h = REG_SCCB_MAST2_ADDRESS_H;
		reg_reg_l = REG_SCCB_MAST2_ADDRESS_L;
		reg_cmd = REG_SCCB_MAST2_COMMAND;
		reg_status = REG_SCCB_MAST2_STATUS;
		reg_value_h = REG_SCCB_MAST2_OUTPUT_DATA_H;
		reg_value_l = REG_SCCB_MAST2_OUTPUT_DATA_L;
		reg_value_len = REG_SCCB_MAST2_2BYTE_CONTROL;
	}

	if (mask != 0x00) {
		ispv1_read_sensor_byte(index, i2c_addr, reg, &old_val, length, addr_len);
		old_val &= mask;
		val = old_val | (val & ~mask);
	}

	if (get_i2c_bus_mutex(SCCB_BUS_MUTEX_WAIT)) {
		print_error("%s, line %d: I2c get mutex timeout!", __func__, __LINE__);
		return -EFAULT;
	}

	if (wait_i2c_bus_idle(reg_status)) {
		print_error("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
		goto error_out2;
	}

	if(I2C_16BIT == addr_len)
		byte_ctrl |= MASK_16BIT_ADDR_ENABLE;
	spin_lock_irqsave(&i2c_lock, flags);

	SETREG8(reg_device_id, i2c_addr);
	SETREG8(reg_reg_h, (reg >> 8) & 0xff);
	SETREG8(reg_reg_l, reg & 0xff);

	if (I2C_8BIT == length) {
		SETREG8(reg_value_l, val);
		SETREG8(reg_value_len, byte_ctrl);
	} else {
		byte_ctrl |= MASK_16BIT_DATA_ENABLE;
		SETREG8(reg_value_h, (val >> 8) & 0xff);
		SETREG8(reg_value_l, val & 0xff);
		SETREG8(reg_value_len, byte_ctrl);
	}
	SETREG8(reg_cmd, 0x37);
	if (wait_i2c_bus_idle(reg_status)) {
		print_error("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
		goto error_out1;
	}

	spin_unlock_irqrestore(&i2c_lock, flags);
	free_i2c_bus_mutex();

	if (I2C_16BIT == length)
		udelay(50);

	return 0;

error_out1:
	spin_unlock_irqrestore(&i2c_lock, flags);
error_out2:
	free_i2c_bus_mutex();
	return -EFAULT;
}

/*
 **************************************************************************
 * FunctionName: mini_ispv1_write_vcm;
 * Description : using for write ad register(set position) of vcm driver ic by i2c bus;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
 int mini_ispv1_write_vcm(u8 i2c_addr, u16 reg, u16 val, i2c_length length, int mutex_wait)
 {
	unsigned long flags;
	volatile u8 original_config;
	return 0;
	if (get_i2c_bus_mutex(mutex_wait)) {
		print_error("%s, line %d: I2c get mutex timeout!", __func__, __LINE__);
		return -EFAULT;
	}

	if (wait_i2c_bus_idle(REG_SCCB_MAST1_STATUS)) {
		print_error("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
		goto error_out2;
	}
	original_config = GETREG8(REG_SCCB_MAST1_2BYTE_CONTROL);
	spin_lock_irqsave(&i2c_lock, flags);

	if (I2C_16BIT == length) {
		if (0 == reg) {
			/*enable 16bit data,disable 16bit address*/
			SETREG8(REG_SCCB_MAST1_2BYTE_CONTROL, 0x02);
		} else {
			/*enable 16bit data,enable 16bit address*/
			SETREG8(REG_SCCB_MAST1_2BYTE_CONTROL, 0x03);
		}
	} else {
		/*disable 16bit data,disable 16bit address*/
		SETREG8(REG_SCCB_MAST1_2BYTE_CONTROL, 0x00);
	}
	SETREG8(REG_SCCB_MAST1_SLAVE_ID, i2c_addr);
	/*input address*/
	if (0 != reg) {
		if (I2C_16BIT == length) {
			SETREG8(REG_SCCB_MAST1_ADDRESS_H, (reg >> 8) & 0xff);
		}
		SETREG8(REG_SCCB_MAST1_ADDRESS_L, reg & 0xff);
	}
	/*input data*/
	if (I2C_16BIT == length) {
		SETREG16(REG_SCCB_MAST1_OUTPUT_DATA_H, val);
	} else {
		SETREG8(REG_SCCB_MAST1_OUTPUT_DATA_L, val);
	}

	if (0 != reg) {
		SETREG8(REG_SCCB_MAST1_COMMAND, 0x37);
	} else {
		/*no address case*/
		SETREG8(REG_SCCB_MAST1_COMMAND, 0x35);
	}
	SETREG8(REG_SCCB_MAST1_2BYTE_CONTROL, original_config);
	if (wait_i2c_bus_idle(REG_SCCB_MAST1_STATUS)) {
		print_error("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
		goto error_out1;
	}

	spin_unlock_irqrestore(&i2c_lock, flags);
	free_i2c_bus_mutex();
	return 0;

error_out1:
	spin_unlock_irqrestore(&i2c_lock, flags);
error_out2:
	free_i2c_bus_mutex();
	return -EFAULT;
}
/*
 **************************************************************************
 * FunctionName: ispv1_write_sensor_seq;
 * Description : write sequeuence to select I2C though isp command set;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_write_sensor_seq(i2c_index_t index, u8 i2c_addr, const struct _mini_sensor_reg_t *buf,
	u32 size, i2c_length length, u8 mask, i2c_length addr_len)
{
	int i2c_left = size;	/*array left */
	int i = 0;

	print_debug("%s:index = %d size=%d", __FUNCTION__, index, size);
return 0;
	/*wicky! can be optimize? */
	if ((STATE_CAPTURE == mini_isp_hw_data.cur_state) && (i2c_left > I2C_MAX)) {
		print_error("sensor capture sequence to long!");
		return -EINVAL;
	}
#if I2C_GROUP_WRITE
	int i2c_write_num = 0;
	int i2c_writen = 0;	/*i2c group writen num */

	u8 cmd_byte = 0x80;
	bool val_8bit = true;
	if(I2C_16BIT == length) {
		cmd_byte |= 0x04;
		val_8bit = false;
	}
	if(I2C_16BIT == addr_len)
		cmd_byte |= 0x08;
	/* use i2c group write command set */
	do {
		i2c_write_num = (i2c_left < I2C_MAX) ? i2c_left : I2C_MAX;
		print_debug("write_seq_thr_isp buf[%#x], i2c_writen=%d, i2c_write_num=%d",
			(int)buf, i2c_writen, i2c_write_num);

		for (i = 0; i < i2c_write_num; i++) {
			SETREG8(COMMAND_BUFFER + 0 + 4 * i, ((buf[i2c_writen + i].subaddr) >> 8) & 0xff);
			SETREG8(COMMAND_BUFFER + 1 + 4 * i, (buf[i2c_writen + i].subaddr) & 0xff);
			SETREG8(COMMAND_BUFFER + 2 + 4 * i, val_8bit ? buf[i2c_writen + i].value : ((buf[i2c_writen + i].value) >> 8) & 0xff);
			SETREG8(COMMAND_BUFFER + 3 + 4 * i, val_8bit ? ~buf[i2c_writen + i].mask : (buf[i2c_writen + i].value) & 0xff);
		}

		SETREG8(COMMAND_REG1, cmd_byte | ((index == I2C_PRIMARY) ? 1 : 2));
		SETREG8(COMMAND_REG2, i2c_addr);
		SETREG8(COMMAND_REG3, i2c_write_num);
		SETREG8(COMMAND_REG0, CMD_I2C_GRP_WR);

		if (wait_cmd_timeout(CMD_I2C_GRP_WR, WAIT_COMPLT_TIMEOUT) < 0) {
			print_error("%s WAIT_COMPLT_TIMEOUT!", __func__);
			return -EINVAL;
		}

		i2c_left -= i2c_write_num;
		i2c_writen += i2c_write_num;
	} while (i2c_left > 0);
#else
	/* use AP write mode */
	for (i = 0; i < size; i++) {
		ispv1_write_sensor_byte(index, i2c_addr, buf[i].subaddr, buf[i].value, length, mask, addr_len);

        /*For FPGA, need to wait some time after I2C write*/
        //msleep(SENSOR_I2C_WAIT_TIMEOUT);
	}
#endif
	return 0;

}

static int ispv1_set_i2c_buf(u32 offset, u16 addr, u32 value, u8 num)
{
	int i = 0;
	for (i = num; i > 0; i--) {
		SETREG8(COMMAND_BUFFER + 4 * (offset + num - i), 0xff);
		SETREG8(COMMAND_BUFFER + 1 + 4 * (offset + num - i), (value >> ((i - 1) * 8)) & 0xff);
		SETREG8(COMMAND_BUFFER + 2 + 4 * (offset + num - i), addr & 0xff);
		SETREG8(COMMAND_BUFFER + 3 + 4 * (offset + num - i), (addr >> 8) & 0xff);
		print_debug("{0x%04x, 0x%02x}", addr, (value >> ((i - 1) * 8)) & 0xff);
		addr++;
	}
	return addr;
}

/*
 **************************************************************************
 * FunctionName: ispv1_write_sensor_group_seq;
 * Description : write sequeuence to select I2C though isp command set;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_write_sensor_group_seq(i2c_index_t index, u8 i2c_addr,
				 const struct _mini_sensor_reg_t *buf, u32 size)
{
	const struct _mini_sensor_reg_t *sensor_reg = buf;
	int i2c_write_num = 0;
	int bytes_read = 0;
	u16 addr = 0;		/*reg addr */
	u16 count = 0;		/*reg num , should less than 319 */
	u32 value = 0;		/*reg value */
return 0;
	print_debug("array size : %d, sizeof(*sensor_reg) is %d, i2c_addr is 0x%0x",
		size, sizeof(*sensor_reg), i2c_addr);


	do {
		for (i2c_write_num = 0; (i2c_write_num < I2C_MAX) && (bytes_read < size);) {
			count = sensor_reg->size;
			if (i2c_write_num + count > I2C_MAX)
				break;
			if (count > sizeof(sensor_reg->value)) {
				bytes_read += count + sizeof(sensor_reg->subaddr) + sizeof(sensor_reg->size);
			} else {
				bytes_read += sizeof(*sensor_reg);
			}

			addr = sensor_reg->subaddr;
			/*addr = 0, do sleep */
			if (0 == addr) {
				value = sensor_reg->value;
				sensor_reg = (struct _mini_sensor_reg_t *)((char *)sensor_reg + sizeof(*sensor_reg));
				break;
			}

			if (count <= sizeof(sensor_reg->value)) {
				value = sensor_reg->value;
				ispv1_set_i2c_buf(i2c_write_num, addr, value, count);
				i2c_write_num += count;
			}
			/*print_debug("before increase sensor_reg is 0x%0x", sensor_seq); */
			if (count <= sizeof(sensor_reg->value)) {
				sensor_reg = (struct _mini_sensor_reg_t *)((char *)sensor_reg + sizeof(*sensor_reg));
			} else {
				sensor_reg = (struct _mini_sensor_reg_t *)((char *)sensor_reg + count * sizeof(0x01) +
					sizeof(sensor_reg->subaddr) + sizeof(sensor_reg->size));
			}
			/*print_debug("after increase sensor_reg is 0x%0x", sensor_reg);*/

		}

		SETREG8(COMMAND_REG1, 0x88 | ((index == I2C_PRIMARY) ? 1 : 2));
		SETREG8(COMMAND_REG2, i2c_addr);
		SETREG8(COMMAND_REG3, i2c_write_num);
		SETREG8(COMMAND_REG0, CMD_I2C_GRP_WR);

		if (wait_cmd_timeout(CMD_I2C_GRP_WR, WAIT_COMPLT_TIMEOUT) < 0) {
			return -EINVAL;
		}
		if (0 == addr) {
			print_debug("msleep(%d)", value);
			msleep(value);
		}
	} while (bytes_read < size);

	return 0;

}

/*
 **************************************************************************
 * FunctionName: ispv1_set_i2c;
 * Description : i2c;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ispv1_set_i2c(struct mini_i2c_t *i2c)
{
	unsigned int chip_id = 0;
	int speed = 0;

	print_info("%s, addr=%#x, i2c speed %d", __func__, i2c->addr,
		    i2c->speed);
	memcpy(&mini_isp_hw_data.i2c_config, i2c, sizeof(struct mini_i2c_t));

	chip_id = get_chipid();
	if ((DI_CHIP_ID != chip_id)	&& (CS_CHIP_ID != chip_id))
		print_error("----bad chip id, please check---");
	speed = mini_camera_get_i2c_speed(chip_id, i2c->speed);

	if (i2c->index == I2C_PRIMARY) {
    #ifdef CONFIG_ARCH_HI6620
        /* set isp I2C0 pull up,I2C1 OD mode, leakage protection */
        phy_reg_writel(SOC_SC_OFF_BASE_ADDR,
                   SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_ADDR(0),
                   SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_ISP_I2C0OD_START,
                   SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_ISP_I2C1OD_END,
                   0x2);
    #endif
		SETREG8(REG_SCCB_MAST1_SPEED, speed);
		SETREG8(REG_SCCB_MAST1_SLAVE_ID, i2c->addr);
		SETREG8(REG_SCCB_FIRMWARE1_ID, i2c->addr);
		SETREG8(REG_SCCB_MAST1_2BYTE_CONTROL, MASK_16BIT_ADDR_ENABLE);
        SETREG8(REG_SCCB_I2C_CONFIGURE,0x09);
	} else {
    #ifdef CONFIG_ARCH_HI6620
        /* set isp I2C1 pull up,I2C0 OD mode, leakage protection */
        phy_reg_writel(SOC_SC_OFF_BASE_ADDR,
                   SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_ADDR(0),
                   SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_ISP_I2C0OD_START,
                   SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_ISP_I2C1OD_END,
                   0x1);
    #endif
		SETREG8(REG_SCCB_MAST2_SPEED, speed);
		SETREG8(REG_SCCB_MAST2_SLAVE_ID, i2c->addr);
		SETREG8(REG_SCCB_FIRMWARE2_ID, i2c->addr);
		SETREG8(REG_SCCB_MAST2_2BYTE_CONTROL, MASK_16BIT_ADDR_ENABLE);
        SETREG8(REG_SCCB_I2C_CONFIGURE,0x0a);
	}
}

/*
 **************************************************************************
 * FunctionName: ispv1_power_sensor;
 * Description : power down or power on sensor through gpio;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
//vcm pwd:isp pwn1, sub cam pwd:isp pwd2
static void ispv1_power_sensor(sensor_index_t sensor_index,
			camera_power_state power_state,
			electrical_valid_t pd_valid,
			electrical_valid_t vcmpd_valid)
{
	print_info("%s, sensor_type:%d, pd_valid:%d", __func__, sensor_index,
		    pd_valid);
	SETREG8(REG_ISP_GPIO_SEL, 0x01);
	SETREG8(REG_GPIO_R_REQ_CTRL_72, 0x73);
	SETREG8(REG_GPIO_R_REQ_CTRL_74, 0x73);

	if (((POWER_ON == power_state) && (LOW_VALID == pd_valid)) ||
		((POWER_OFF == power_state) && (HIGH_VALID == pd_valid))) {
		if (CAMERA_SENSOR_PRIMARY == sensor_index) {
			/*SETREG8(REG_ISP_GPIO_CTL_L, 0x20 | GETREG8(REG_ISP_GPIO_CTL_L));*/
			SETREG8(REG_ISP_GPIO_CTL_L, 0x10 | GETREG8(REG_ISP_GPIO_CTL_L));
		} else {
			SETREG8(REG_ISP_GPIO_CTL_L, 0x40 | GETREG8(REG_ISP_GPIO_CTL_L));
		}
	} else {
		if (CAMERA_SENSOR_PRIMARY == sensor_index) {
			/*SETREG8(REG_ISP_GPIO_CTL_L, 0xdf & GETREG8(REG_ISP_GPIO_CTL_L));*/
			SETREG8(REG_ISP_GPIO_CTL_L, 0xef & GETREG8(REG_ISP_GPIO_CTL_L));
		} else {
			SETREG8(REG_ISP_GPIO_CTL_L, 0xbf & GETREG8(REG_ISP_GPIO_CTL_L));
		}
	}

	/*added by y36721 for AF power down*/
	/* for OV8830-DW9714 driver IC, power down active low*/
	if (CAMERA_SENSOR_PRIMARY == sensor_index) {
		if (((POWER_ON == power_state) && (LOW_VALID == vcmpd_valid)) ||
		((POWER_OFF == power_state) && (HIGH_VALID == vcmpd_valid))) {
			/*primary sensor' AF driver IC power down is GPIO_075(ISP_GPIO6)*/
			/* For ISP IP, it is 0x63030 gpio_ctrl[15:8]:bit[2] manual sn_frex0_o, when gpio_sel = 1, gpio12*/
			/*SETREG8(REG_ISP_GPIO_CTL_H, 0x04 | GETREG8(REG_ISP_GPIO_CTL_H));*/
			SETREG8(REG_ISP_GPIO_CTL_L, 0x20 | GETREG8(REG_ISP_GPIO_CTL_L));

		} else {
			/*SETREG8(REG_ISP_GPIO_CTL_H, (~(0x04)) & GETREG8(REG_ISP_GPIO_CTL_H));*/
			SETREG8(REG_ISP_GPIO_CTL_L, 0xdf & GETREG8(REG_ISP_GPIO_CTL_L));
		}
	}
    return;

}

/*
 **************************************************************************
 * FunctionName: ispv1_reset_sensor;
 * Description : reset sensor through gpio;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ispv1_reset_sensor(sensor_index_t sensor_index, camera_power_state power_state,
			electrical_valid_t reset_valid)
{
	print_info("%s sensor_type:%d, reset_valid:%d", __func__, sensor_index, reset_valid);

	SETREG8(REG_ISP_GPIO_SEL, 0x01);
	if (POWER_ON == power_state) {
		if (CAMERA_SENSOR_PRIMARY == sensor_index) {
			SETREG8(REG_ISP_GPIO_CTL_L, 0x01 | GETREG8(REG_ISP_GPIO_CTL_L));
		} else {
			SETREG8(REG_ISP_GPIO_CTL_L, 0x02 | GETREG8(REG_ISP_GPIO_CTL_L));
		}
	} else {
		if (CAMERA_SENSOR_PRIMARY == sensor_index) {
			SETREG8(REG_ISP_GPIO_CTL_L, GETREG8(REG_ISP_GPIO_CTL_L) & 0xfe);
		} else {
			SETREG8(REG_ISP_GPIO_CTL_L, GETREG8(REG_ISP_GPIO_CTL_L) & 0xfd);
		}
	}
}

/*
 **************************************************************************
 * FunctionName: ispv1_enable_mclk;
 * Description : enable or disable sensor mclk;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ispv1_enable_mclk(mclk_state state, sensor_index_t sensor_index)
{
	u8 clk = 0;
#if 1
	clk = CLK_DIVIDER;

	if (MCLK_ENABLE == state)
		SETREG8(REG_ISP_CLK_DIVIDER, clk);	/* clkdvide */
	else if (MCLK_DISABLE == state)
		SETREG8(REG_ISP_CLK_DIVIDER, 0);	/* clkdvide */
	else
		print_error("error mclk_state:%d", state);
#else
	if (CAMERA_SENSOR_PRIMARY == sensor_index) {
		clk = 0x0f & CLK_DIVIDER;
	} else {
		clk = 0xf0 & CLK_DIVIDER;
	}
	if (MCLK_ENABLE == state)
		SETREG8(REG_ISP_CLK_DIVIDER, clk);	/* clkdvide */
	else if (MCLK_DISABLE == state)
		SETREG8(REG_ISP_CLK_DIVIDER, 0);	/* clkdvide */
	else
		print_error("error mclk_state:%d", state);
#endif
}

/*
 **************************************************************************
 * FunctionName: ispv1_write_isp_seq;
 * Description : pseq: sequence array
 * seq_size: sequence size
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ispv1_write_isp_seq(const struct mini_isp_reg_t *pseq, u32 seq_size)
{
	int i = 0;

	for (i = 0; i < seq_size; i++) {
        if (pseq[i].subaddr == 0)
            break;
		SETREG8(pseq[i].subaddr, pseq[i].value);
	}
}

/*
 **************************************************************************
 * FunctionName: ispv1_read_isp_seq;
 * Description : pseq: sequence array
 * seq_size: sequence size
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ispv1_read_isp_seq(struct mini_isp_reg_t *pseq, u32 seq_size)
{
	int i = 0;

	for (i = 0; i < seq_size; i++) {
        if (pseq[i].subaddr == 0)
            break;
		pseq[i].value = GETREG8(pseq[i].subaddr);
	}
}

/*
 **************************************************************************
 * FunctionName: ispv1_hw_init_regs;
 * Description : Init isp registers;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ispv1_hw_init_regs(data_interface_t sensor_type)
{
	print_debug("enter %s", __func__);

	/* download isp init sequeuence */
	if (MIPI1 == sensor_type || MIPI2 == sensor_type) {
		SETREG8(0x60100, 0x01);
		ispv1_write_isp_seq(mini_isp_mipi_init_regs1,
				sizeof(mini_isp_mipi_init_regs1)/sizeof(mini_isp_mipi_init_regs1[0]));
		print_debug("download isp mipi init seqenence");

	#ifdef OVISP_DEBUG_MODE
		char *filename = "/data/ov-debug.txt";
		ispv1_load_isp_setting(filename);
	#endif
	} else if (DVP == sensor_type) {
		ispv1_write_isp_seq(mini_isp_dvp_init_regs,
			sizeof(mini_isp_dvp_init_regs) / sizeof(mini_isp_dvp_init_regs[0]));
	} else {
		print_error("%s, sensor_type error:%d", __func__, sensor_type);
	}

}

/*
 **************************************************************************
 * FunctionName: ispv1_power_region_set;
 * Description : isp hardware poweron region set;
 * Input       : ispv1_power_enmu;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ispv1_power_region_set(camera_power_state type)
{
    print_debug("%s enter, parameter = %d", __func__, type);

    if (POWER_ON == type) {
        /* ISP RST DISABLE */
        phy_reg_writel(SOC_SC_ON_BASE_ADDR,
                       SOC_AO_SCTRL_SC_PW_RSTDIS0_ADDR(0),
                       SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_5isp_START,
                       SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_5isp_END,
                       0x1);

		/* ISP ISO DISABLE */
        phy_reg_writel(SOC_SC_ON_BASE_ADDR,
                       SOC_AO_SCTRL_SC_PW_ISODIS0_ADDR(0),
                       SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_5isp_START,
                       SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_5isp_END,
                       0x1);

		/* ISP CLKREG ENABLE */
        phy_reg_writel(SOC_SC_ON_BASE_ADDR,
                       SOC_AO_SCTRL_SC_PW_CLKEN0_ADDR(0),
                       SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_5isp_START,
                       SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_5isp_END,
                       0x1);
    } else if (POWER_OFF == type) {
        /* ISP CLKREG DISABLE */
        phy_reg_writel(SOC_SC_ON_BASE_ADDR,
                       SOC_AO_SCTRL_SC_PW_CLKDIS0_ADDR(0),
                       SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_5isp_START,
                       SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_5isp_END,
                       0x1);

        /* ISP ISO ENABLE */
        phy_reg_writel(SOC_SC_ON_BASE_ADDR,
                       SOC_AO_SCTRL_SC_PW_ISOEN0_ADDR(0),
                       SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_5isp_START,
                       SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_5isp_END,
                       0x1);

        /* ISP RST ENABLE */
        phy_reg_writel(SOC_SC_ON_BASE_ADDR,
                       SOC_AO_SCTRL_SC_PW_RSTEN0_ADDR(0),
                       SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_5isp_START,
                       SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_5isp_END,
                       0x1);
	} else {
        print_error("%s, ispv1_power_enum input error:%d", __func__, type);
	}

	return;
}

/*
 **************************************************************************
 * FunctionName: ispv1_clkregion_rstdis;
 * Description : isp hardware poweron clkregion disable reset;
 * Input       : ispv1_power_enmu;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ispv1_clkregion_rstdis(camera_power_state type)
{
	print_debug("%s enter, parameter = %d", __func__, type);

    if (POWER_ON == type) {
        /* SOC_SCTRL_SC_PERIPH_RSTDIS7 */
        phy_reg_writel(SOC_SC_OFF_BASE_ADDR,
                       SOC_SCTRL_SC_PERIPH_RSTDIS7_ADDR(0),
                       SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_10isppower_START,
                       SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_12ispwork_END,
                       0x7);
    } else if (POWER_OFF == type) {
        /* SOC_SCTRL_SC_PERIPH_RSTEN7 */
        phy_reg_writel(SOC_SC_OFF_BASE_ADDR,
                       SOC_SCTRL_SC_PERIPH_RSTEN7_ADDR(0),
                       SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_10isppower_START,
                       SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_12ispwork_END,
                       0x7);
    } else {
        print_error("%s, ispv1_power_enum input error:%d", __func__, type);
	}

    return;
}


/*
 **************************************************************************
 * FunctionName: ispv1_poweron;
 * Description : isp hardware poweron and init;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_poweron(void)
{
	unsigned int chip_id;
	/*unsigned int *sys_ctl = (unsigned int *)REG_BASE_SCTRL_VIRT;*/

    if (0 == mini_get_cam_pwdn_status(DEBUGFS_PWDN_ISP)) {
#if 0   /*buck3 power on with system, not need to control*/
    	if (mini_isp_hw_data.inter_ldo == NULL || regulator_enable(mini_isp_hw_data.inter_ldo)) {
    		print_error("%s: regulator enable failed!", __func__);
    		return -EINVAL;
    	}
#endif

        /* setup isp region powerup */
        ispv1_power_region_set(POWER_ON);

    	/*
    	   1. sclk: isp_core/csi controller
    	   2. sclk_mipi: isp mipi interface reference clk
    	   3. phy_config_clk: phy
    	 */

    	print_info("enable isp clock.");

#ifdef CONFIG_ARCH_HI6620
        /* FPGA platform, don't need to set clock source;
           CS platform, set isp clock source, is DSPPLL 1200Mhz*/
        if (clk_set_parent(mini_isp_hw_data.isp_gated_clk_mux, mini_isp_hw_data.dsppll_clk)) {
    		print_error("Error: %s, set isp clk src failed", __func__);
    		return -EFAULT;
        }
#endif

    	if (mini_isp_hw_data.isp_clk == NULL || clk_prepare_enable(mini_isp_hw_data.isp_clk)) {
    		print_error("Error: %s, isp clk enable failed", __func__);
    		return -EFAULT;
    	}

    	chip_id = get_chipid();
    	if (chip_id == CS_CHIP_ID) {
    		print_info("CS_CHIP!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
            /* FPGA platform, isp clock source is 480Mhz, clock divider is 12, sclk = 40Mhz
               CS platform, isp clock source is DSPPLL 1200Mhz, clock divider is 6, sclk = 200Mhz*/
    		if (clk_set_rate(mini_isp_hw_data.isp_clk, ISP_CLOCK)) {
    			print_error("%s, Fail to set isp_clk", __func__);
    			return -EFAULT;
    		}

    		if (mini_isp_hw_data.ispmipi_clk == NULL || clk_prepare_enable(mini_isp_hw_data.ispmipi_clk)) {
    			print_error("Error: %s, ispmipi clk enable failed", __func__);
    			return -EFAULT;
    		}

            /* FPGA platform, ref clock source is 480Mhz, clock divider is 12, ref clk = 40Mhz
               CS platform, ref clock source is PERIPLL 1440Mhz, clock divider is 8, ref clk = 180Mhz*/
    		if (clk_set_rate(mini_isp_hw_data.ispmipi_clk, ISP_MIPI_CLOCK)) {
    			print_error("%s, Fail to set ispmipi_clk", __func__);
    			return -EFAULT;
    		}

    		if (mini_isp_hw_data.isp_aclk == NULL || clk_prepare_enable(mini_isp_hw_data.isp_aclk)) {
    			print_error("Error: %s, isp aclk enable failed", __func__);
    			return -EFAULT;
    		}

    		if (mini_isp_hw_data.isp_csi_clk == NULL || clk_prepare_enable(mini_isp_hw_data.isp_csi_clk)) {
    			print_error("Error: %s, isp APB MUX clk enable failed", __func__);
    			return -EFAULT;
    		}

    		if (mini_isp_hw_data.isp_hclk == NULL || clk_prepare_enable(mini_isp_hw_data.isp_hclk)) {
    			print_error("Error: %s, isp AHB Slave clk enable failed", __func__);
    			return -EFAULT;
    		}
    	} else {
    		print_info("ES_CHIP!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    	}

        /* rst disable clk region */
        ispv1_clkregion_rstdis(POWER_ON);

#ifdef CONFIG_ARCH_HI6620
        /* set isp I2C0/I2C1 OD mode, leakage protection */
        phy_reg_writel(SOC_SC_OFF_BASE_ADDR,
                   SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_ADDR(0),
                   SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_ISP_I2C0OD_START,
                   SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_ISP_I2C1OD_END,
                   0x0);
#endif
        mini_set_cam_pwdn_status(DEBUGFS_PWDN_ISP, 1);
    }

    print_info("%s, isp debugfs pwdn config = %d, isp pwdn status = %d\n",
        __func__, mini_get_cam_dbgfs_pwdncfg(), mini_get_cam_pwdn_status(DEBUGFS_PWDN_ISP));

#ifdef DUMP_SCCTRL_ISP_REG
    mini_dump_scctrl_isp_reg();
#endif

	/* Reset ISP  */
	SETREG8(REG_ISP_SOFT_RST, DO_SOFT_RST);

	SETREG8(REG_ISP_SOFT_STANDBY, DO_SOFTWARE_STAND_BY);
	udelay(1);

	SETREG8(REG_ISP_CLK_USED_BY_MCU, 0xf1);

	/* 3.download firmware from file to ram of mcu */
	if (0 > mini_load_file(FIRMWARE_FILE_NAME, (u8 *) mini_isp_hw_data.base)) {
		print_error("download firmware file error!");
		return -EINVAL;
	}

	/* enable interrupt (only set_cmd_done interrupt) */
	SETREG8(REG_ISP_INT_EN, MASK_CMDSET_INT_ENABLE);

	/*5. MCU initialize */
	/* enable the clk used by mcu */
	SETREG8(REG_ISP_CLK_USED_BY_MCU, 0xf0);

	if (wait_cmd_timeout(CMD_FIRMWARE_DOWNLOAD, WAIT_COMPLT_TIMEOUT) < 0) {
		return -EINVAL;
	}

	/* Init isp sensor nonrelated- registers */
	/* FIXME: add isp configuration to isp_default_init_reg[]*/
	ispv1_write_isp_seq(mini_isp_default_init_regs,
		sizeof(mini_isp_default_init_regs)/sizeof(mini_isp_default_init_regs[0]));

	print_info("%s success, clk divider is %#x", __func__, CLK_DIVIDER);

#ifdef ISP_DEBUG_ZSL
    mini_isp_debug_init();
#endif

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ispv1_poweroff;
 * Description : isp hardware poweroff;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ispv1_poweroff(void)
{
	unsigned int chip_id = 0;

	print_debug("%s", __func__);

	SETREG8(REG_ISP_SOFT_RST, DO_SOFT_RST);
	ispv1_disable_irq();
	//SETREG8(REG_ISP_INT_EN, 0); /* Disable CMD_SET int at last */

    if (0 != mini_get_cam_dbgfs_pwdncfg()) {
        /* RST ENABLE */
        ispv1_clkregion_rstdis(POWER_OFF);

    	if (mini_isp_hw_data.isp_clk) {
    		clk_disable_unprepare(mini_isp_hw_data.isp_clk);
    	}

    	chip_id = get_chipid();
    	if (chip_id == CS_CHIP_ID) {
    		if (mini_isp_hw_data.ispmipi_clk) {
    			clk_disable_unprepare(mini_isp_hw_data.ispmipi_clk);
    		}

    		if (mini_isp_hw_data.isp_aclk) {
    			clk_disable_unprepare(mini_isp_hw_data.isp_aclk);
    		}

    		if (mini_isp_hw_data.isp_csi_clk) {
    			clk_disable_unprepare(mini_isp_hw_data.isp_csi_clk);
    		}

    		if (mini_isp_hw_data.isp_hclk) {
    			clk_disable_unprepare(mini_isp_hw_data.isp_hclk);
    		}
    	}

    #ifdef CONFIG_ARCH_HI6620
        /* set isp I2C0/I2C1 OD mode, leakage protection */
        phy_reg_writel(SOC_SC_OFF_BASE_ADDR,
                   SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_ADDR(0),
                   SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_ISP_I2C0OD_START,
                   SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_ISP_I2C1OD_END,
                   0x3);
    #endif

        /* clk region rst enable */
    	ispv1_power_region_set(POWER_OFF);

#if 0   /*buck3 power on with system, not need to control*/
    	if (mini_isp_hw_data.inter_ldo) {
	        int rc = 1;
    		rc = regulator_disable(mini_isp_hw_data.inter_ldo);
    		if (rc) {
      			printk(KERN_ERR "Regulator isp disable failed rc=%d\n", rc);
      		}
    	}
#endif

        mini_set_cam_pwdn_status(DEBUGFS_PWDN_ISP, 0);
    }

    print_info("%s, isp debugfs pwdn config = %d, isp pwdn status = %d\n",
        __func__, mini_get_cam_dbgfs_pwdncfg(), mini_get_cam_pwdn_status(DEBUGFS_PWDN_ISP));

#ifdef DUMP_SCCTRL_ISP_REG
    mini_dump_scctrl_isp_reg();
#endif
#ifdef ISP_DEBUG_ZSL
    mini_isp_debug_deinit();
#endif
}


/*
 **************************************************************************
 * FunctionName: ispv1_drop_handler;
 * Description : Called by isp interrupt handler when one frame data drop;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_drop_handler(u8 buf_sel, u32 addr,u32 stats_addr, camera_state state)
{
	u8 rdy_current = 0;
	u8 rdy_another = 0;
	mini_uv_offset *puvoffset = NULL;

#ifdef ISP_DEBUG_ZSL
	/* FIXME:zsl debug only,removed them after zsl is ok. */
	mini_isp_debug_dump_irq_reg();
#endif

    if (state == STATE_PREVIEW){
        puvoffset = &mini_isp_hw_data.preview_uv_offset;
    } else if (state == STATE_CAPTURE) {
        puvoffset = &mini_isp_hw_data.capture_uv_offset;
    } else {
        print_error("%s:invalid state=%d.", __func__, state);
        return -EINVAL;
    }


	if (BUF_LEFT == buf_sel) {
		/* FIXME left buffer is writing */
		if ((REG_BASE_ADDR1_WRITING & GETREG8(REG_BASE_WORKING_ADDR)) == 0)
		{
			print_info("REG_BASE_WORKING_ADDR ==  %#x \n   ", GETREG8(REG_BASE_WORKING_ADDR));
			return 0;
		}

		rdy_current = WRITE_ADDR0_READY;
		rdy_another = WRITE_ADDR1_READY;
	} else {
		/* right buffer is writing */
		if ((REG_BASE_ADDR1_WRITING & GETREG8(REG_BASE_WORKING_ADDR)) != 0)
		{
			print_info("REG_BASE_WORKING_ADDR ==  %#x \n   ", GETREG8(REG_BASE_WORKING_ADDR));
			return 0;
		}

		rdy_current = WRITE_ADDR1_READY;
		rdy_another = WRITE_ADDR0_READY;
	}

	if (rdy_current & GETREG8(REG_BASE_ADDR_READY)) {
		print_error("REG_BASE_ADDR_READY aready set 0x%0x", GETREG8(REG_BASE_ADDR_READY));
	} else if (rdy_another & GETREG8(REG_BASE_ADDR_READY)) {
		SETREG8(REG_BASE_ADDR_READY, 0);
    		ispv1_hardware_update_addr(addr, stats_addr,puvoffset, buf_sel);
	} else {
		mini_camera_frame_buf *frame = NULL;
		frame = ispv1_move_queue_element(&mini_isp_hw_data.data_queue_ref->ready_q[state],
				CAMERA_FLAG_READYQ,
				&mini_isp_hw_data.data_queue_ref->work_q[state],
				CAMERA_FLAG_WORKQ);
		if (frame) {
			ispv1_hardware_update_addr(frame->phyaddr, frame->statphyaddr,puvoffset, buf_sel);
		} else {
#if 0
			if (STATE_PREVIEW == mini_isp_hw_data.cur_state) /* for debug */
				print_info("ready queue %d, work queue %d, done queue %d",
					mini_get_queue_size(&mini_isp_hw_data.data_queue_ref->ready_q[mini_isp_hw_data.cur_state]),
					mini_get_queue_size(&mini_isp_hw_data.data_queue_ref->work_q[mini_isp_hw_data.cur_state]),
					mini_get_queue_size(&mini_isp_hw_data.data_queue_ref->done_q[mini_isp_hw_data.cur_state]));
#endif
			return -ENOMEM;
		}
	}

	return 0;
}


/*
 **************************************************************************
 * FunctionName: ispv1_write_start_handler;
 * Description : Called by isp interrupt handler when one frame data start;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_write_start_handler(camera_state state)
{
	int                 ret = 0;
	mini_camera_frame_buf    *frame     = NULL;
	unsigned long       lock_flags;
	struct list_head    *work_q    = NULL;
	struct list_head    *ready_q   = NULL;
	mini_uv_offset           *puvoffset = NULL;

	/* print_debug("enter %s", __func__); */


    if (state == STATE_PREVIEW){
        puvoffset = &mini_isp_hw_data.preview_uv_offset;
    } else if (state == STATE_CAPTURE) {
        puvoffset = &mini_isp_hw_data.capture_uv_offset;
    } else {
        print_error("%s:invalid state=%d.", __func__, state);
        return -EINVAL;
    }

	spin_lock_irqsave(&mini_isp_hw_data.data_queue_ref->queue_lock, lock_flags);
	ready_q = &mini_isp_hw_data.data_queue_ref->ready_q[state];
	work_q = &mini_isp_hw_data.data_queue_ref->work_q[state];



	if (!list_empty(ready_q)) {
		/* add a new ready buffer to work_q */
		frame = list_entry(ready_q->next, mini_camera_frame_buf, queue);
		if (0 == ispv1_update_addr(frame->phyaddr,frame->statphyaddr,puvoffset)) {
			mini_del_from_queue(frame, CAMERA_FLAG_READYQ);
			mini_add_to_queue(frame, work_q, CAMERA_FLAG_WORKQ);
		}
	} else {
		print_warn("%s, no more empty buffer !!!",  __func__);
#if 0
		if (STATE_PREVIEW == mini_isp_hw_data.cur_state) /* for debug */
			print_info("ready queue %d, work queue %d, done queue %d",
				mini_get_queue_size(&mini_isp_hw_data.data_queue_ref->ready_q[mini_isp_hw_data.cur_state]),
				mini_get_queue_size(&mini_isp_hw_data.data_queue_ref->work_q[mini_isp_hw_data.cur_state]),
				mini_get_queue_size(&mini_isp_hw_data.data_queue_ref->done_q[mini_isp_hw_data.cur_state]));
#endif
		ret = -EINVAL;
	}
	spin_unlock_irqrestore(&mini_isp_hw_data.data_queue_ref->queue_lock, lock_flags);


	return ret;
}
/*
 **************************************************************************
 * FunctionName: ispv1_overflow_handler;
 * Description : Called by isp interrupt handler when one frame data overflow;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_overflow_handler(camera_state state)
{
	int ret = 0;
	struct list_head *work_q = NULL;
	struct list_head *ready_q = NULL;

#ifdef ISP_DEBUG_ZSL
	mini_isp_debug_dump_irq_reg();
#endif

	work_q = &mini_isp_hw_data.data_queue_ref->work_q[state];
	ready_q = &mini_isp_hw_data.data_queue_ref->ready_q[state];
	if (NULL == ispv1_move_queue_element(work_q, CAMERA_FLAG_WORKQ, ready_q, CAMERA_FLAG_READYQ)) {
		print_error("%s, no more empty work buffer",  __func__);
		ret = -EINVAL;
	}

	return ret;
}

/*
 **************************************************************************
 * FunctionName: ispv1_frame_done_handler;
 * Description : Called by isp interrupt handler when one frame data completed;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static bool flash_done_flag = false;
extern u32 misp_skip_cap_frame;

static int ispv1_frame_done_handler(camera_state state)
{
	int ret = 0;
	struct list_head *work_q = NULL;
	struct list_head *done_q = NULL;
	struct list_head *ready_q = NULL;
	mini_camera_frame_buf *frame = NULL;
	unsigned long lock_flags;

#ifdef ISP_DEBUG_ZSL
	mini_isp_debug_dump_irq_reg();
#endif

	/* print_debug("enter %s", __func__);*/
	if ((mini_isp_hw_data.frame_count == 5) && (state == STATE_PREVIEW)) {
		if ((FLASH_TESTING != mini_this_ispdata->flash_flow) && (FLASH_FROZEN != mini_this_ispdata->flash_flow)) {

			if (CAMERA_ZSL_OFF == mini_this_ispdata->zsl_ctrl.zsl_state && mini_this_ispdata->ae_lock == AUTO_AECAGC) {
				mini_ispv1_set_aecagc_mode(AUTO_AECAGC);
			}

				mini_ispv1_set_awb_mode(AUTO_AWB);
		}
	}

	spin_lock_irqsave(&mini_isp_hw_data.data_queue_ref->queue_lock, lock_flags);
	ready_q = &mini_isp_hw_data.data_queue_ref->ready_q[state];
	work_q = &mini_isp_hw_data.data_queue_ref->work_q[state];
	done_q = &mini_isp_hw_data.data_queue_ref->done_q[state];
	if (!list_empty(work_q)) {
		frame = list_entry(work_q->next, mini_camera_frame_buf, queue);
		mini_del_from_queue(frame, CAMERA_FLAG_WORKQ);
		mini_add_to_queue(frame, done_q, CAMERA_FLAG_DONEQ);
		if (mini_isp_hw_data.frame_count < mini_this_ispdata->sensor->skip_frames)
			memset(&frame->timestamp, 0, sizeof(struct timeval));
		else
			frame->timestamp = ktime_to_timeval(ktime_get());

		frame->viraddr = NULL;

		/* using for calculate ext_contrast coefficient */
		mini_this_ispdata->current_frame = frame;
        if (CAMERA_ZSL_ON == mini_this_ispdata->zsl_ctrl.zsl_state){
            /* save continuous focused frame count. */
            if (STATUS_FOCUSED == mini_get_focus_result()
             || (STATUS_OUT_FOCUS == mini_get_focus_result())){
                if (mini_this_ispdata->zsl_ctrl.focused_frame_cnt < CAPTURE_WITH_PREVIEW_BUF_MAX_NUM)
                    mini_this_ispdata->zsl_ctrl.focused_frame_cnt++;
            } else {
                mini_this_ispdata->zsl_ctrl.focused_frame_cnt = 1;
            }
        }
	} else {
		print_error("queue empty state:%d, queue flag %d, line=%d", state, CAMERA_FLAG_WORKQ, __LINE__);
		ret = -EINVAL;
		goto OUT;
	}

	if ((mini_isp_hw_data.preview_stop == true) && (state == STATE_PREVIEW))
		goto OUT;

	if (state == STATE_CAPTURE && (ISP_CAPTURE_OFFLINE != (ispv1_get_process_mode()))) {
		if (mini_isp_hw_data.frame_count < misp_skip_cap_frame) {
			mini_del_from_queue(frame, CAMERA_FLAG_DONEQ);
			mini_add_to_queue(frame, ready_q, CAMERA_FLAG_READYQ);
			print_info("discard capture frame:%d", mini_isp_hw_data.frame_count);
			goto OUT;
		}
	}

	wake_up_interruptible(&mini_isp_hw_data.data_queue_ref->queue[state]);
OUT:
	spin_unlock_irqrestore(&mini_isp_hw_data.data_queue_ref->queue_lock, lock_flags);
	/*print_debug("%s:ID is %d, phyaddr is 0x%0x", __func__, frame->index, frame->phyaddr); */
	return ret;
}

#if 0
/*
 **************************************************************************
 * FunctionName: ispv1_zsl_frame_done_handler;
 * Description : Called by isp interrupt handler when one frame data completed;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_zsl_frame_done_handler(void)
{
    camera_state        state   = STATE_CAPTURE;
    struct list_head    *work_q = NULL;
    struct list_head    *done_q = NULL;
    mini_camera_frame_buf    *frame  = NULL;
    int                 ret     = 0;
    unsigned long       lock_flags;


    spin_lock_irqsave(&mini_isp_hw_data.data_queue_ref->queue_lock, lock_flags);
    work_q = &mini_isp_hw_data.data_queue_ref->work_q[state];
    done_q = &mini_isp_hw_data.data_queue_ref->done_q[state];
    if (!list_empty(work_q)) {
    frame = list_entry(work_q->next, mini_camera_frame_buf, queue);
        mini_del_from_queue(frame, CAMERA_FLAG_WORKQ);
        mini_add_to_queue(frame, done_q, CAMERA_FLAG_DONEQ);
    } else {
        print_error("queue empty state:%d, queue flag %d, line=%d", state, CAMERA_FLAG_WORKQ, __LINE__);
        ret = -EINVAL;
        goto OUT;
    }
    mini_isp_hw_data.irq_val.mac_irqstatus_h_done_cnt = 0;
    wake_up_interruptible(&mini_isp_hw_data.data_queue_ref->queue[state]);
    OUT:
    spin_unlock_irqrestore(&mini_isp_hw_data.data_queue_ref->queue_lock, lock_flags);
    return ret;
}
#endif
/*
 **************************************************************************
 * FunctionName: ispv1_zsl_slice_done_handle;
 * Description : Called by isp interrupt handler when one frame data completed;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
#if 0
static int ispv1_zsl_slice_done_handle(void)
{
    int                 ret     = 0;


    if (mini_this_ispdata->zsl_ctrl.zsl_proc_type != ZSL_PROC_IMG_HISTORY_BACKWARD_ONE)
    {
        print_error("invalid process image type.");
    }

    return ret;
}
#endif


/*
 **************************************************************************
 * FunctionName: ispv1_isr;
 * Description : isp interrupt handler;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
 #ifdef SUPPORT_ZSL_FLASH
static void flash_handler(void);
static void zsl_stop_capture_with_preview_cmd_handler(struct work_struct *work);

#define NR_FRAME_SKIP_TO_WAIT_FOR_WB	2

static u32 nr_frame_skip = 0;
static u32 flash_flag = 0;
static u32 set_ratio_cmd_done = 0;
static u32 skip_ap_write_ae_flag = 0;

DECLARE_COMPLETION(mini_zsl_flash_capture_completion);
DECLARE_WORK(mini_zsl_flash_stop_cap_work, zsl_stop_capture_with_preview_cmd_handler);

static void zsl_stop_capture_with_preview_cmd_handler(struct work_struct *work)
{
	wait_cmd_timeout(CMD_CAPTURE_WITH_PREVIEW, WAIT_COMPLT_TIMEOUT);
	mini_this_ispdata->zsl_ctrl.history_buf_idx = GETREG8(ISP_CAP_STREAM_BUF_REG) & ISP_CAP_STREAM_BUF_MASK;
	print_info("want back idx=%d.ret buf idx=%d.",mini_this_ispdata->zsl_ctrl.zsl_back_idx,mini_this_ispdata->zsl_ctrl.history_buf_idx);
	complete(&mini_zsl_flash_capture_completion);
}

static int zsl_stop_capture_with_preview_cmd(void)
{
	u32                                 ret=0;

	print_debug("enter %s.",__func__);

	/* set which buffer we need */
	//for online flash
	SETREG8(COMMAND_REG3, 0);

	if (CAMERA_ZSL_OFFLINE == mini_this_ispdata->zsl_ctrl.zsl_proc_mode){
		SETREG8(COMMAND_REG1, CAPTURE_STREAM_DISABLE | CAPTURE_STREAM_OFFLINE);
	}
	else{
		SETREG8(COMMAND_REG1, CAPTURE_STREAM_DISABLE | CAPTURE_STREAM_ONLINE);
	}

	SETREG8(COMMAND_REG0, CMD_CAPTURE_WITH_PREVIEW);

	schedule_work(&mini_zsl_flash_stop_cap_work);
	return ret;
}

static int ispv1_set_ratio_cmd(u16 ratio)
{

	SETREG8(COMMAND_REG1, (ratio >> 8));
	SETREG8(COMMAND_REG2, (ratio & 0xff));
	SETREG8(COMMAND_REG0, CMD_SET_RATIO);
	print_debug("%s",__func__);
	return wait_cmd_timeout(CMD_SET_RATIO, WAIT_COMPLT_TIMEOUT);
}

static void zsl_set_ratio(void)
{
	mini_camera_sensor *sensor	;
	u32 frame_index;
	u32 ratio0 = EV_RATIO_DIVIDEND;

	sensor = mini_this_ispdata->sensor;
	frame_index = sensor->capture_frmsize_index;

	ratio0 = ratio0 * mini_isp_hw_data.ratio_factor / 0x100;

	if (ratio0 > ISP_EXPOSURE_RATIO_MAX)
		ratio0 = ISP_EXPOSURE_RATIO_MAX;

	ispv1_set_ratio_cmd(ratio0);
	if(flash_flag == 1)
		skip_ap_write_ae_flag = 1;
}

static void flash_handler(void)
{
	mini_camera_flashlight *flashlight = mini_get_camera_flash();

	print_debug("flash_handler flash_flag = %d\n ",flash_flag);
	if(flash_flag == 1)
		flashlight->turn_on(FLASH_MODE,mini_this_ispdata->sensor->effect->flash.flash_capture.capflash_level);
	else
	{
		flashlight->turn_off();
		mini_this_ispdata->flash_flow = FLASH_DONE;
		mini_this_ispdata->flash_on = false;
		mini_this_ispdata->flash_state = FLASH_OFF;
		skip_ap_write_ae_flag = 0;
	}
}

static void zsl_sof_start_flash(void)
{
	if(set_ratio_cmd_done == 1)
	{
		if (nr_frame_skip++ < NR_FRAME_SKIP_TO_WAIT_FOR_WB)
		{
			return;
		}
		zsl_stop_capture_with_preview_cmd();
		set_ratio_cmd_done = 0;
		nr_frame_skip = 0;
	}
}

static void zsl_wait_to_start_capture_with_flash(void)
{
	mini_camera_flashlight *flashlight = mini_get_camera_flash();

	if(true == mini_this_ispdata->flash_on)
	{
		print_debug("%s  mini_this_ispdata->flash_on = %d",__func__,mini_this_ispdata->flash_on);

		zsl_flash_process = 1;//now we are in zsl flash process
              //turn off pre flash
		if ((mini_this_ispdata->sensor->sensor_index == CAMERA_SENSOR_PRIMARY) && (flashlight != NULL))
		{
			if ( flashlight)
			{
				flashlight->turn_off();
			}
		}
		//set manual gc/ec/wb
		mini_ispv1_set_aecagc_mode(MANUAL_AECAGC);
		mini_ispv1_set_awb_mode(MANUAL_AWB);
		//turn on flash
		flash_flag = 1;
		flash_handler();
		//set capture ratio
		set_ratio_cmd_done = 0;
		zsl_set_ratio();
		set_ratio_cmd_done = 1;
		//zsl_start_flash_flag = 1;//to start zsl flash process
		wait_for_completion(&mini_zsl_flash_capture_completion); //wait signal
		flash_done_flag = true;
		//turn off flash
		flash_flag = 0;
		flash_handler();

		mini_ispv1_set_aecagc_mode(AUTO_AECAGC);
		//ispv1_set_ratio_cmd(0x100);
		mini_ispv1_set_awb_mode(AUTO_AWB);
	}
}
#endif

extern mini_axis_triple mini_mXYZ;
static void meta_data_process_handler(struct work_struct *work)
{
	mini_camera_frame_buf *frame = mini_this_ispdata->current_frame;
	camera_state cur_state = mini_isp_hw_data.cur_state;

	if(false == mini_this_ispdata->is_using_mini_isp || NULL == mini_this_ispdata->meta_data) {
		print_error("this product don't support mini-isp or meta_data is NULL");
		return;
	}

	if(NULL != mini_this_ispdata->meta_data->parse)
		mini_this_ispdata->meta_data->parse((char *)frame->statphyaddr, mini_this_ispdata->meta_data);

	if (cur_state == STATE_CAPTURE) {
		mini_this_ispdata->capture_iso = mini_this_ispdata->meta_data->data.ae_info.iso;
		mini_this_ispdata->capture_expo_time = mini_this_ispdata->meta_data->data.ae_info.expo_time;
	}

	mini_ov_set_wb_value(mini_this_ispdata->meta_data);
	mini_ov_set_ae_value(mini_this_ispdata->meta_data);
	mini_ov_get_val_meta_data(mini_this_ispdata->meta_data);
	mini_isp_flash_controller(mini_this_ispdata->meta_data);
	if(mini_this_ispdata->sensor->af_enable) {
		mini_ov_set_af_status(mini_this_ispdata->meta_data);
		camera_agent_set_GSensorInfo(&mini_mXYZ);//by wind
	}
}

DECLARE_WORK(meta_work, meta_data_process_handler);


static void isr_do_tasklet(unsigned long data)
{
	unsigned long lock_flags;
	u8 volatile isp_cmd_id = 0;
	u32 volatile buffer_set_B = 0;
	u32 volatile buffer_set_A = 0;
	u32 volatile sony_stats_buffer_set_B = 0;
	u32 volatile sony_stats_buffer_set_A = 0;
	u8 intr_count = 0;
	u32 temp = mini_isp_hw_data.irq_val.mac_irqstatus_l;
	camera_state cur_state;
	mini_uv_offset *puvoffset = NULL;



    if (mini_this_ispdata) {
        if (CAMERA_ZSL_ON == mini_this_ispdata->zsl_ctrl.zsl_state) {
            cur_state = STATE_PREVIEW;
        }
        else {
            cur_state = mini_isp_hw_data.cur_state;
        }
    }
    else {
        cur_state = mini_isp_hw_data.cur_state;
    }


    if (cur_state == STATE_PREVIEW){
        puvoffset = &mini_isp_hw_data.preview_uv_offset;
    } else if (cur_state == STATE_CAPTURE) {
        puvoffset = &mini_isp_hw_data.capture_uv_offset;
    } else {
        puvoffset = &mini_isp_hw_data.capture_uv_offset;
    }


	print_debug("irq_status=%#x, mac_int_ctrl1=%#x, mac_int_ctrl0=%#x",
		    mini_isp_hw_data.irq_val.irq_status, mini_isp_hw_data.irq_val.mac_irqstatus_h, mini_isp_hw_data.irq_val.mac_irqstatus_l);
	/* Check multi intr */
	while (temp > 0) {
		if (temp & 0x01)
			intr_count++;
		temp >>= 1;
	}
	if (intr_count > 1)
		print_warn("multi intrrupt occured at the same time, mac_irqstatus_l:%#x", mini_isp_hw_data.irq_val.mac_irqstatus_l);

	GETREG32(REG_BASE_ADDR0_Y, buffer_set_A);
	GETREG32(REG_BASE_ADDR1_Y, buffer_set_B);
	GETREG32(REG_SONY_STATS_BASE_ADDR0, sony_stats_buffer_set_A);
	GETREG32(REG_SONY_STATS_BASE_ADDR1, sony_stats_buffer_set_B);

	/* EACH BIT SHOULD BE EXECUTED*/

	/* command set done interrupt */
	if (mini_isp_hw_data.irq_val.irq_status & ISP_COMMAND_DONE_INT) {
		print_debug("+++++++++++++++cmd done process %x", mini_isp_hw_data.irq_val.mcu_cmd_finish);
		if (mini_isp_hw_data.irq_val.mcu_cmd_finish&MASK_CMD_DONE_WRITEBACK_EXPO_GAIN){
			mini_isp_hw_data.aec_cmd_id = CMD_WRITEBACK_EXPO_GAIN;
			mini_ispv1_aeag_excute();
			spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
			mini_isp_hw_data.irq_val.mcu_cmd_finish &= ~(MASK_CMD_DONE_WRITEBACK_EXPO_GAIN);
			spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);
		}
		if (mini_isp_hw_data.irq_val.mcu_cmd_finish&MASK_CMD_DONE_WRITEBACK_EXPO){
			mini_isp_hw_data.aec_cmd_id = CMD_WRITEBACK_EXPO;
			mini_ispv1_aeag_excute();
			spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
			mini_isp_hw_data.irq_val.mcu_cmd_finish &= ~(MASK_CMD_DONE_WRITEBACK_EXPO);
			spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);
		}
		if (mini_isp_hw_data.irq_val.mcu_cmd_finish&MASK_CMD_DONE_WRITEBACK_GAIN){
			mini_isp_hw_data.aec_cmd_id = CMD_WRITEBACK_GAIN;
			mini_ispv1_aeag_excute();
			spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
			mini_isp_hw_data.irq_val.mcu_cmd_finish &= ~(MASK_CMD_DONE_WRITEBACK_GAIN);
			spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);
		}
		if(mini_isp_hw_data.irq_val.mcu_cmd_finish&MASK_CMD_DONE_ZOOM){
			isp_cmd_id = CMD_ZOOM_IN_MODE;
			//if (org_cmd_id == isp_cmd_id){
				mini_isp_hw_data.command_set_id = isp_cmd_id;
				up(&mini_isp_hw_data.sem_cmd_done);
				spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
				mini_isp_hw_data.irq_val.mcu_cmd_finish &= ~(MASK_CMD_DONE_ZOOM);
				spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);
			//}
		}
		if(mini_isp_hw_data.irq_val.mcu_cmd_finish&MASK_CMD_DONE_FIRMWARE_DOWNLOAD){
			isp_cmd_id = CMD_FIRMWARE_DOWNLOAD;
			//if (org_cmd_id == isp_cmd_id){
				mini_isp_hw_data.command_set_id = isp_cmd_id;
				up(&mini_isp_hw_data.sem_cmd_done);
				spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
				mini_isp_hw_data.irq_val.mcu_cmd_finish &= ~(MASK_CMD_DONE_FIRMWARE_DOWNLOAD);
				spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);
			//}
		}
		if(mini_isp_hw_data.irq_val.mcu_cmd_finish&MASK_CMD_DONE_BRACKET_CAPTURE){
			//if (org_cmd_id != 0){
				ispv1_write_start_handler(cur_state);
				spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
				mini_isp_hw_data.irq_val.mcu_cmd_finish &= ~(MASK_CMD_DONE_BRACKET_CAPTURE);
				spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);
			//}
		}
		if(mini_isp_hw_data.irq_val.mcu_cmd_finish&MASK_CMD_DONE_SET_FORMAT){
			isp_cmd_id = CMD_SET_FORMAT;
				mini_isp_hw_data.command_set_id = isp_cmd_id;
				up(&mini_isp_hw_data.sem_cmd_done);
				spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
				mini_isp_hw_data.irq_val.mcu_cmd_finish &= ~(MASK_CMD_DONE_SET_FORMAT);
				spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);
		}
		if(mini_isp_hw_data.irq_val.mcu_cmd_finish&MASK_CMD_DONE_CAPTURE){
			isp_cmd_id = CMD_CAPTURE;
			//if (org_cmd_id == isp_cmd_id){
				mini_isp_hw_data.command_set_id = isp_cmd_id;
				up(&mini_isp_hw_data.sem_cmd_done);
				spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
				mini_isp_hw_data.irq_val.mcu_cmd_finish &= ~(MASK_CMD_DONE_CAPTURE);
				spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);
			//}
		}
		if(mini_isp_hw_data.irq_val.mcu_cmd_finish&MASK_CMD_DONE_OFFLINE_PROCESS){
			isp_cmd_id = CMD_OFFLINE_PROCESS;
			//if (org_cmd_id == isp_cmd_id){
				mini_isp_hw_data.command_set_id = isp_cmd_id;
				up(&mini_isp_hw_data.sem_cmd_done);
				spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
				mini_isp_hw_data.irq_val.mcu_cmd_finish &= ~(CMD_OFFLINE_PROCESS);
				spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);
			//}
		}
		if(mini_isp_hw_data.irq_val.mcu_cmd_finish&MASK_CMD_DONE_CAPTURE_WITH_PREVIEW){
			isp_cmd_id = CMD_CAPTURE_WITH_PREVIEW;
			//if (org_cmd_id == isp_cmd_id){
				mini_isp_hw_data.command_set_id = isp_cmd_id;
				up(&mini_isp_hw_data.sem_cap_raw_cmd_done);
				spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
				mini_isp_hw_data.irq_val.mcu_cmd_finish &= ~(MASK_CMD_DONE_CAPTURE_WITH_PREVIEW);
				spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);
			//}
		}
		/* this cmd do not need return immediately*/
		if(mini_isp_hw_data.irq_val.mcu_cmd_finish&MASK_CMD_DONE_PROC_IMG_WITH_PREVIEW){
			isp_cmd_id = CMD_PROC_IMG_WITH_PREVIEW;
			//if (org_cmd_id == isp_cmd_id){
				mini_isp_hw_data.command_set_id = isp_cmd_id;
				up(&mini_isp_hw_data.sem_proc_img_cmd_done);
			#if 0
			   	ispv1_zsl_frame_done_handler();
		    #endif
				spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
				mini_isp_hw_data.irq_val.mcu_cmd_finish &= ~(MASK_CMD_DONE_PROC_IMG_WITH_PREVIEW);
				spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);
			//}
		}
#ifdef SUPPORT_ZSL_FLASH
		if(mini_isp_hw_data.irq_val.mcu_cmd_finish&MASK_CMD_DONE_SET_RATIO){
			isp_cmd_id = CMD_SET_RATIO;
			//if (org_cmd_id == isp_cmd_id){
				mini_isp_hw_data.command_set_id = isp_cmd_id;
				up(&mini_isp_hw_data.sem_cmd_done);
				spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
				mini_isp_hw_data.irq_val.mcu_cmd_finish &= ~(MASK_CMD_DONE_SET_RATIO);
				spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);
			//}
		}
#endif
#if 0
		isp_cmd_id = GETREG8(COMMAND_FINISHED);

	    /* "proc img with preview" will return while finished offline proc */
	    print_debug("cmdint cmdid[%d].result=[%d].", isp_cmd_id,GETREG8(COMMAND_RESULT));

		if (CMD_BRACKET_CAPTURE == isp_cmd_id) {
			/* print_debug("bracket capture..............."); */
			ispv1_write_start_handler(cur_state);
		} else if ((CMD_WRITEBACK_EXPO_GAIN == isp_cmd_id)  ||
				(CMD_WRITEBACK_EXPO == isp_cmd_id) ||
				(CMD_WRITEBACK_GAIN == isp_cmd_id)) {
			mini_isp_hw_data.aec_cmd_id = isp_cmd_id;
			mini_ispv1_cmd_id_do_ecgc(cur_state);
		} else if (CMD_PROC_IMG_WITH_PREVIEW == isp_cmd_id) {
		    /* "proc img with preview" will return while finished offline proc */
		    //print_info("COMMAND_FINISHED, cmdid[%d].result=[%d].", isp_cmd_id,GETREG8(COMMAND_RESULT));
		    ispv1_zsl_frame_done_handler();
		} else {
			mini_isp_hw_data.command_set_id = isp_cmd_id;
			up(&mini_isp_hw_data.sem_cmd_done);
		}
#endif
		spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
		mini_isp_hw_data.irq_val.irq_status &= ~ISP_COMMAND_DONE_INT;
		spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);
	}

	/* EOF and SOF interrupt */
	if (mini_isp_hw_data.irq_val.irq_status & MASK_EOF_INT_ENABLE) {
		spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
		mini_isp_hw_data.irq_val.irq_status &= ~MASK_EOF_INT_ENABLE;
		spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);
		if (STATE_PREVIEW == cur_state)
			mini_ispv1_preview_done_do_tune();
	}

	if (mini_isp_hw_data.irq_val.irq_status & MASK_SOF_INT_ENABLE) {
		spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
		mini_isp_hw_data.irq_val.irq_status &= ~MASK_SOF_INT_ENABLE;
		spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);
 #ifdef SUPPORT_ZSL_FLASH
     zsl_sof_start_flash();
 #endif
	}

	/* done */
	if (mini_isp_hw_data.irq_val.mac_irqstatus_l & ISP_WRITE_DONE_INT0) {
		//print_info("done0========================");
		//if (STATE_PREVIEW == cur_state) {
			ispv1_frame_done_handler(cur_state);
			mini_isp_hw_data.frame_count++;
		//} else {
		//	ispv1_frame_done_handler(cur_state);
		//	isp_hw_data.frame_count++;
		//}
		spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
		mini_isp_hw_data.irq_val.mac_irqstatus_l &= ~ISP_WRITE_DONE_INT0;
		spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);
		if(mini_this_ispdata->is_using_mini_isp)
			schedule_work(&meta_work);  //add by zhoutian for mini-ISP meta data
	}

	if (mini_isp_hw_data.irq_val.mac_irqstatus_l & ISP_WRITE_DONE_INT1) {
		//if (STATE_PREVIEW == cur_state) {
			ispv1_frame_done_handler(cur_state);
			mini_isp_hw_data.frame_count++;
		//} else {
		//	ispv1_frame_done_handler(cur_state);
		//	isp_hw_data.frame_count++;
		//}
		spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
		mini_isp_hw_data.irq_val.mac_irqstatus_l &= ~ISP_WRITE_DONE_INT1;
		spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);
		if(mini_this_ispdata->is_using_mini_isp)
			schedule_work(&meta_work);  //add by zhoutian for mini-ISP meta data
	}

	/* write start */
	/* each write start interrupt excute one time */
	if (mini_isp_hw_data.irq_val.mac_irqstatus_l & ISP_WRITE_START_INT0) {
		//print_info("start0========================");
		//if (STATE_PREVIEW == cur_state) {
			ispv1_write_start_handler(cur_state);
		//} else if (true == burst_capture) {
		//	ispv1_write_start_handler(cur_state);
		//}
		spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
		mini_isp_hw_data.irq_val.mac_irqstatus_l &= ~ISP_WRITE_START_INT0;
		spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);
	}

	if (mini_isp_hw_data.irq_val.mac_irqstatus_l & ISP_WRITE_START_INT1) {
		//if (STATE_PREVIEW == cur_state) {
			ispv1_write_start_handler(cur_state);
		//} else if (true == burst_capture) {
		//	ispv1_write_start_handler(cur_state);
		//}
		spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
		mini_isp_hw_data.irq_val.mac_irqstatus_l &= ~ISP_WRITE_START_INT1;
		spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);
	}

	/* drop */
	if (mini_isp_hw_data.irq_val.mac_irqstatus_l & ISP_FRAME_DROP_INT0) {
		print_info("DROP0, ready_reg:%#x", GETREG8(REG_BASE_ADDR_READY));
		//if (STATE_PREVIEW == cur_state || true == burst_capture)
			ispv1_drop_handler(BUF_LEFT, buffer_set_B,sony_stats_buffer_set_B, cur_state);
		spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
		mini_isp_hw_data.irq_val.mac_irqstatus_l &= ~ISP_FRAME_DROP_INT0;
		spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);
	}

	if (mini_isp_hw_data.irq_val.mac_irqstatus_l & ISP_FRAME_DROP_INT1) {
		print_info("DROP1, ready_reg:%#x", GETREG8(REG_BASE_ADDR_READY));
		//if (STATE_PREVIEW == cur_state || true == burst_capture)
			ispv1_drop_handler(BUF_RIGHT, buffer_set_A,sony_stats_buffer_set_A, cur_state);
		spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
		mini_isp_hw_data.irq_val.mac_irqstatus_l &= ~ISP_FRAME_DROP_INT1;
		spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);
	}

	/* FIFO overflow */
	if (mini_isp_hw_data.irq_val.mac_irqstatus_l & ISP_OVERFLOW_INT0) {
		print_info("ISP Intr OVERFLOW0!");
		ispv1_overflow_handler(cur_state);
		spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
		mini_isp_hw_data.irq_val.mac_irqstatus_l &= ~ISP_OVERFLOW_INT0;
		spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);
	}
	if (mini_isp_hw_data.irq_val.mac_irqstatus_l & ISP_OVERFLOW_INT1) {
		print_info("ISP Intr OVERFLOW1");
		ispv1_overflow_handler(cur_state);
		spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
		mini_isp_hw_data.irq_val.mac_irqstatus_l &= ~ISP_OVERFLOW_INT1;
		spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);
	}


	/* ZSL:proc image with preview done */
    if (mini_isp_hw_data.irq_val.mac_irqstatus_h & 2) {
    	print_info("zsl slice r ok");
    	spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
    	mini_isp_hw_data.irq_val.mac_irqstatus_h &= ~2;
        mini_isp_hw_data.irq_val.mac_irqstatus_h_done_cnt = mini_isp_hw_data.irq_val.mac_irqstatus_h_done_cnt + 1;
    	spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);

#if 0
		if (1 == mini_isp_hw_data.irq_val.mac_irqstatus_h_done_cnt)
        {
            ispv1_zsl_slice_done_handle();
        }
#endif

        if (4 == mini_isp_hw_data.irq_val.mac_irqstatus_h_done_cnt)
        {
		    print_info("ZSL slice finished");
        }

    }

}

static irqreturn_t ispv1_isr(int irq, void *dev_id)
{
	unsigned long lock_flags;
	unsigned long irq_status_tmp = 0;
	u8 volatile cmd_id = 0;
	spin_lock_irqsave(&mini_isp_hw_data.irq_status_lock, lock_flags);
	//mini_isp_hw_data.irq_val.irq_status |= ioread8_mutex((mini_isp_hw_data.base + (REG_ISP_INT_STAT)));//GETREG8(REG_ISP_INT_STAT);

    /* need to read REG_ISP_INT_STAT before COMMAND_FINISHED */
	irq_status_tmp = ioread8_mutex((mini_isp_hw_data.base + (REG_ISP_INT_STAT)));
	cmd_id = ioread8_mutex((mini_isp_hw_data.base + (COMMAND_FINISHED)));//GETREG8(COMMAND_FINISHED);

	if (irq_status_tmp & ISP_COMMAND_DONE_INT){
		if (cmd_id > 0xf0){
			cmd_id &= 0x0f;
			mini_isp_hw_data.irq_val.mcu_cmd_finish|= mask_table[cmd_id - 1];
		}else if(cmd_id != 0){
			mini_isp_hw_data.irq_val.mcu_cmd_finish |= (1 << cmd_id);
		}
		else{
		}
	}
	mini_isp_hw_data.irq_val.irq_status |= irq_status_tmp;
	mini_isp_hw_data.irq_val.mac_irqstatus_h |= ioread8_mutex((mini_isp_hw_data.base + (REG_ISP_MAC_INT_STAT_H))); //GETREG8(REG_ISP_MAC_INT_STAT_H);
	mini_isp_hw_data.irq_val.mac_irqstatus_l |=  ioread8_mutex((mini_isp_hw_data.base + (REG_ISP_MAC_INT_STAT_L)));//GETREG8(REG_ISP_MAC_INT_STAT_L);
	//org_cmd_id = ioread8_mutex((mini_isp_hw_data.base + (COMMAND_REG0)));

	spin_unlock_irqrestore(&mini_isp_hw_data.irq_status_lock, lock_flags);

	/*isr_time = *((u32*)REG_BASE_TIMER0_VIRT + 9);*/
	tasklet_schedule(&mini_isr_tasklet);
	return IRQ_HANDLED;
}

/*
 **************************************************************************
 * FunctionName: ispv1_hw_init;
 * Description : get isp hardware resource;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_hw_init(struct platform_device *pdev, mini_data_queue_t* data_queue)
{
	struct resource *res = 0;
	static struct clk *camera_clk;
	static struct clk *camera_mipi_clk;
	static struct clk *camera_aclk;
	static struct clk *camera_csi_clk;
	static struct clk *camera_hclk;
    static struct clk *dsppll_clk;
    static struct clk *isp_gated_clk_mux;
	static struct regulator *camera_inter_ldo;
	int ret = 0;
	unsigned int chip_id = 0;
    struct device *dev = &pdev->dev;


	print_debug("enter %s", __func__);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		print_error("failed to get io men resource");
		return -ENXIO;
	}


    /*FIXME: BSP has not support the interface IO_ADDRESS*/
	mini_isp_hw_data.base = ioremap(res->start, resource_size(res));

	if (NULL == mini_isp_hw_data.base) {
                print_error("failed to get mini_isp_hw_data.base");
	        return -ENOMEM;
	}

	mini_register_cam_dbg_info(DBG_INFO_ISP_BASE, (void *) mini_isp_hw_data.base);

	/* get resource */
	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (res == NULL) {
		print_error("failed to get irq: isp_irq");
		return -ENXIO;
	}

	ret = request_irq(res->start, ispv1_isr, 0, "isp_irq", 0);
	if (ret != 0) {
		print_error("fail to request irq [%d]", res->start);
		return ret;
	}
	mini_isp_hw_data.irq = res->start;

	ret = ispv1_hw_set_default();
	if (ret != 0) {
		print_error("ispv1_hw_set_default failed!");
		goto fail;
	}

	/* get isp clock */
	camera_clk = clk_get(dev, "clk_isp");
	if (IS_ERR_OR_NULL(camera_clk)) {
		print_error("failed to get isp clock");
		ret = -ENXIO;
		goto fail;
	}
	mini_isp_hw_data.isp_clk = camera_clk;

	chip_id = get_chipid();
	if (chip_id == CS_CHIP_ID) {
		camera_mipi_clk = clk_get(dev, "clk_isp_ref");
		if (IS_ERR_OR_NULL(camera_mipi_clk)) {
			print_error("failed to get isp mipi clock");
			ret = -ENXIO;
			goto fail;
		}
		mini_isp_hw_data.ispmipi_clk = camera_mipi_clk;

		camera_aclk = clk_get(dev, "clk_isp_axi");
		if (IS_ERR_OR_NULL(camera_aclk)) {
			print_error("failed to get isp aclock");
			ret = -ENXIO;
			goto fail;
		}
		mini_isp_hw_data.isp_aclk = camera_aclk;

		camera_csi_clk = clk_get(dev, "clk_csi_apb_mux");
		if (IS_ERR_OR_NULL(camera_csi_clk)) {
			print_error("failed to get CSI APB MUX clk");
			ret = -ENXIO;
			goto fail;
		}
		mini_isp_hw_data.isp_csi_clk = camera_csi_clk;

		camera_hclk = clk_get(dev, "clk_isp_cfg_clk");
		if (IS_ERR_OR_NULL(camera_hclk)) {
			print_error("failed to get AHB Slave clk");
			ret = -ENXIO;
			goto fail;
		}
		mini_isp_hw_data.isp_hclk = camera_hclk;

        /* DSPPLL CLK controlled */
		dsppll_clk = clk_get(dev, "clk_dsppll");/*1200Mhz*/
		if (IS_ERR_OR_NULL(dsppll_clk)) {
			print_error("failed to get dsppll clock");
			ret = -ENXIO;
			goto fail;
		}
		mini_isp_hw_data.dsppll_clk = dsppll_clk;

        /* ISP GATED CLK MUX controlled */
		isp_gated_clk_mux = clk_get(dev, "clk_peripll_isp_gated_mux");
		if (IS_ERR_OR_NULL(isp_gated_clk_mux)) {
			print_error("failed to get isp gated mux clock");
			ret = -ENXIO;
			goto fail;
		}
		mini_isp_hw_data.isp_gated_clk_mux = isp_gated_clk_mux;
	}

	/* get isp regulator */
	camera_inter_ldo = regulator_get(dev,"ISP_VDD");
	if (IS_ERR_OR_NULL(camera_inter_ldo)) {
		print_error("%s: Could not get regulator : %s\n", __func__, "vcc_isp");
		ret = -ENXIO;
		goto fail;
	}

	mini_isp_hw_data.inter_ldo = camera_inter_ldo;
	mini_isp_hw_data.data_queue_ref = data_queue;

	sema_init(&mini_isp_hw_data.sem_cmd_done, 0);
	sema_init(&mini_isp_hw_data.sem_cap_raw_cmd_done, 0);
	sema_init(&mini_isp_hw_data.sem_proc_img_cmd_done, 0);
	sema_init(&mini_isp_hw_data.sem_wrt_done, 0);
	spin_lock_init(&mini_isp_hw_data.irq_status_lock);

	print_debug("startisp OK basereg[%#x]\n", mini_isp_hw_data.base);
	return 0;

fail:
	if (mini_isp_hw_data.irq) {
		free_irq(mini_isp_hw_data.irq, 0);
		mini_isp_hw_data.irq = 0;
	}
	if (mini_isp_hw_data.isp_clk) {
		clk_put(mini_isp_hw_data.isp_clk);
		mini_isp_hw_data.isp_clk = NULL;
	}
	if (chip_id == CS_CHIP_ID) {
		if (mini_isp_hw_data.ispmipi_clk) {
			clk_put(mini_isp_hw_data.ispmipi_clk);
			mini_isp_hw_data.ispmipi_clk = NULL;
		}
		if (mini_isp_hw_data.isp_aclk) {
			clk_put(mini_isp_hw_data.isp_aclk);
			mini_isp_hw_data.isp_aclk = NULL;
		}

		if (mini_isp_hw_data.isp_csi_clk) {
			clk_put(mini_isp_hw_data.isp_csi_clk);
			mini_isp_hw_data.isp_csi_clk = NULL;
		}

		if (mini_isp_hw_data.isp_hclk) {
			clk_put(mini_isp_hw_data.isp_hclk);
			mini_isp_hw_data.isp_hclk = NULL;
		}

		if (mini_isp_hw_data.dsppll_clk) {
			clk_put(mini_isp_hw_data.dsppll_clk);
			mini_isp_hw_data.dsppll_clk = NULL;
		}

		if (mini_isp_hw_data.isp_gated_clk_mux) {
			clk_put(mini_isp_hw_data.isp_gated_clk_mux);
			mini_isp_hw_data.isp_gated_clk_mux = NULL;
		}
	}

	if (ispv1_ctl.isp_tune_ops) {
		kfree(ispv1_ctl.isp_tune_ops);
		ispv1_ctl.isp_tune_ops = NULL;
	}

	return ret;
}

/*
 **************************************************************************
 * FunctionName: ispv1_hw_deinit;
 * Description : release isp hardware resource;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ispv1_hw_deinit(void)
{
	unsigned int chip_id;
	print_debug("enter %s", __func__);

	if (ispv1_ctl.isp_tune_ops) {
		kfree(ispv1_ctl.isp_tune_ops);
		ispv1_ctl.isp_tune_ops = NULL;
	}

	/* ispv1_poweroff(); */

	if (mini_isp_hw_data.irq) {
		free_irq(mini_isp_hw_data.irq, 0);
		mini_isp_hw_data.irq = 0;
	}

	if (mini_isp_hw_data.isp_clk) {
		clk_put(mini_isp_hw_data.isp_clk);
		mini_isp_hw_data.isp_clk = NULL;
	}

	chip_id = get_chipid();
	if (chip_id == CS_CHIP_ID) {
		if (mini_isp_hw_data.ispmipi_clk) {
			clk_put(mini_isp_hw_data.ispmipi_clk);
			mini_isp_hw_data.ispmipi_clk = NULL;
		}
		if (mini_isp_hw_data.isp_aclk) {
			clk_put(mini_isp_hw_data.isp_aclk);
			mini_isp_hw_data.isp_aclk = NULL;
		}

		if (mini_isp_hw_data.isp_csi_clk) {
			clk_put(mini_isp_hw_data.isp_csi_clk);
			mini_isp_hw_data.isp_csi_clk = NULL;
		}

		if (mini_isp_hw_data.isp_hclk) {
			clk_put(mini_isp_hw_data.isp_hclk);
			mini_isp_hw_data.isp_hclk = NULL;
		}

		if (mini_isp_hw_data.dsppll_clk) {
			clk_put(mini_isp_hw_data.dsppll_clk);
			mini_isp_hw_data.dsppll_clk = NULL;
		}

		if (mini_isp_hw_data.isp_gated_clk_mux) {
			clk_put(mini_isp_hw_data.isp_gated_clk_mux);
			mini_isp_hw_data.isp_gated_clk_mux = NULL;
		}
	}

#if 0   /*buck3 power on with system, not need to control*/
	if (mini_isp_hw_data.inter_ldo) {
		regulator_put(mini_isp_hw_data.inter_ldo);
		mini_isp_hw_data.inter_ldo = NULL;
	}
#endif


    /*FIXME: BSP has not support the interface IO_ADDRESS*/
    iounmap(mini_isp_hw_data.base );

}

int mini_ispv1_get_current_vts(mini_camera_sensor *sensor)
{
	u32 frame_index = sensor->preview_frmsize_index;
	u16 full_fps = sensor->frmsize_list[frame_index].fps;
	print_debug("enter %s", __func__);
	return sensor->frmsize_list[frame_index].vts * full_fps / sensor->fps;
}

int mini_ispv1_get_current_fps(mini_camera_sensor *sensor)
{
	print_debug("enter %s", __func__);
	return sensor->fps;
}

int mini_ispv1_get_band_threshold(mini_camera_sensor *sensor, camera_anti_banding banding)
{
	#if 1
	return mini_ov_get_band_threshold(sensor, banding);
	#else
	u32 banding_step = ispv1_get_curr_banding_step(banding - 1);

	if (0 == banding_step)
		return 0;
	return (get_writeback_expo()>>4) >= banding_step;
	#endif
}

/*
 **************************************************************************
 * FunctionName: ispv1_hw_set_default;
 * Description : Set default value of ispv1_ctl struct;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_hw_set_default (void)
{
	print_debug("enter %s", __func__);

	ispv1_ctl.set_i2c			= ispv1_set_i2c;
	ispv1_ctl.isp_hw_init			= ispv1_hw_init;
	ispv1_ctl.isp_hw_deinit			= ispv1_hw_deinit;
	ispv1_ctl.isp_hw_init_regs		= ispv1_hw_init_regs;
	ispv1_ctl.isp_get_process_mode		= ispv1_get_process_mode;
	ispv1_ctl.isp_set_process_mode		= ispv1_set_process_mode;
	#ifdef READ_BACK_RAW
	ispv1_ctl.update_read_ready		= ispv1_update_read_ready;
	#endif
	ispv1_ctl.isp_check_config		= ispv1_check_config;
	ispv1_ctl.start_preview			= ispv1_start_preview;
	ispv1_ctl.start_capture			= ispv1_start_capture;
	ispv1_ctl.start_process			= ispv1_start_process;
	ispv1_ctl.stop_preview			= ispv1_stop_preview;
	ispv1_ctl.stop_capture			= ispv1_stop_capture;
	ispv1_ctl.stop_process			= ispv1_stop_process;
	ispv1_ctl.refresh_support_fmt		= ispv1_refresh_support_fmt;
	ispv1_ctl.isp_fill_fmt_info		= ispv1_fill_fmt_info;
	ispv1_ctl.isp_poweron			= ispv1_poweron;
	ispv1_ctl.isp_poweroff			= ispv1_poweroff;
	ispv1_ctl.isp_tune_ops			= (mini_isp_tune_ops *)kmalloc(sizeof(mini_isp_tune_ops), GFP_KERNEL);
	ispv1_ctl.isp_set_auto_flash		= ispv1_set_auto_flash;
	ispv1_ctl.isp_is_need_flash 		= ispv1_is_need_flash;
	ispv1_ctl.isp_set_aecagc_mode		= mini_ispv1_set_aecagc_mode;

	/*h00206029_0218*/
	ispv1_ctl.isp_set_awb_mode		= mini_ispv1_set_awb_mode;
	ispv1_ctl.cold_boot_set		= ispv1_cold_boot_set;

	ispv1_ctl.isp_check_flash_prepare		= mini_ispv1_check_flash_prepare;

	if (ispv1_ctl.isp_tune_ops == NULL) {
		print_error("failed to kmalloc mini_isp_tune_ops");
		return -ENOMEM;
	}

	ispv1_ctl.isp_set_zoom			= ispv1_set_zoom;
	ispv1_ctl.isp_set_ae_lock       = mini_ispv1_set_aecagc_mode;
	ispv1_ctl.isp_get_fps 			= mini_ispv1_get_fps;
	ispv1_ctl.isp_set_fps 			= mini_ispv1_set_fps;

	ispv1_ctl.isp_get_current_vts		= mini_ispv1_get_current_vts;
	ispv1_ctl.isp_get_current_fps		= mini_ispv1_get_current_fps;
	ispv1_ctl.isp_get_band_threshold	= mini_ispv1_get_band_threshold;

	ispv1_ctl.isp_tune_ops_init 		= mini_ispv1_tune_ops_init;
	ispv1_ctl.isp_tune_ops_prepare 		= mini_ispv1_tune_ops_prepare;
	ispv1_ctl.isp_tune_ops_withdraw 	= mini_ispv1_tune_ops_withdraw;
	ispv1_ctl.isp_tune_ops_exit 		= mini_ispv1_tune_ops_exit;

	/* param: please refer to "camera_focus" */
	ispv1_ctl.isp_tune_ops->isp_set_focus_mode			= mini_ispv1_set_focus_mode;
	/* param: int flag=1 start, flag=0 cancel */
	ispv1_ctl.isp_tune_ops->isp_auto_focus				= mini_ispv1_auto_focus;
	/* param: focus_zone_s *zone, zone definition, max 25 rectangle */
	ispv1_ctl.isp_tune_ops->isp_set_focus_area			= mini_ispv1_set_focus_area;
	ispv1_ctl.isp_tune_ops->isp_get_focus_result			= mini_ispv1_get_focus_result;
	ispv1_ctl.isp_tune_ops->isp_set_focus_zoom			= mini_ispv1_set_focus_zoom;
	ispv1_ctl.isp_tune_ops->isp_set_sharpness_zoom			= mini_ispv1_set_sharpness_zoom;

	/* For anti-shaking */
	ispv1_ctl.isp_tune_ops->isp_set_anti_shaking			= mini_ispv1_set_anti_shaking;
	ispv1_ctl.isp_tune_ops->isp_set_anti_shaking_block		= mini_ispv1_set_anti_shaking_block;
	ispv1_ctl.isp_tune_ops->isp_get_anti_shaking_coordinate		= mini_ispv1_get_anti_shaking_coordinate;
	/* auto, 100, 200, 400, 800... */
	ispv1_ctl.isp_tune_ops->set_iso				= mini_ispv1_set_iso;
	/* -2, -1, 0, +1, +2, ... */
	ispv1_ctl.isp_tune_ops->set_ev				= mini_ispv1_set_ev;
	/* spot/cwa/average */
	ispv1_ctl.isp_tune_ops->set_metering_mode			= mini_ispv1_set_metering_mode; /*spot/cwa/average*/
	ispv1_ctl.isp_tune_ops->set_metering_area	= mini_ispv1_set_metering_area;

	ispv1_ctl.isp_tune_ops->set_gsensor_stat	= mini_ispv1_set_gsensor_stat;

	/* auto, 50Hz, 60Hz, off; in fact, it is needed in door. */
	ispv1_ctl.isp_tune_ops->set_anti_banding			= mini_ispv1_set_anti_banding;
	ispv1_ctl.isp_tune_ops->get_anti_banding			= mini_ispv1_get_anti_banding;

	/* auto, mwb:daylight, cloudy, incandescence, fluorescence ... */
	ispv1_ctl.isp_tune_ops->set_awb = mini_ispv1_set_awb;

	ispv1_ctl.isp_tune_ops->isp_get_focus_distance = mini_ispv1_get_focus_distance;
	ispv1_ctl.isp_tune_ops->isp_set_fps_lock = mini_ispv1_set_fps_lock;

	/* 0, 1, 2, 3, 4... */
	ispv1_ctl.isp_tune_ops->set_sharpness			= mini_ispv1_set_sharpness;
	ispv1_ctl.isp_tune_ops->set_saturation			= mini_ispv1_set_saturation;
	ispv1_ctl.isp_tune_ops->set_contrast			= mini_ispv1_set_contrast;
	ispv1_ctl.isp_tune_ops->set_scene				= mini_ispv1_set_scene;
	ispv1_ctl.isp_tune_ops->set_brightness			= mini_ispv1_set_brightness;
	ispv1_ctl.isp_tune_ops->set_effect				= mini_ispv1_set_effect;

	ispv1_ctl.isp_tune_ops->isp_get_actual_iso			= mini_ispv1_get_actual_iso;
	ispv1_ctl.isp_tune_ops->isp_get_exposure_time			= mini_ispv1_get_exposure_time;
	ispv1_ctl.isp_tune_ops->isp_get_awb_gain			= mini_ispv1_get_awb_gain;
	ispv1_ctl.isp_tune_ops->isp_get_focus_code			= mini_ispv1_get_focus_code;
	ispv1_ctl.isp_tune_ops->isp_get_focus_rect			= mini_ispv1_get_focus_rect;
	ispv1_ctl.isp_tune_ops->isp_get_expo_line			= mini_ispv1_get_expo_line;
	ispv1_ctl.isp_tune_ops->isp_get_sensor_vts			= mini_ispv1_get_sensor_vts;

	ispv1_ctl.isp_get_yuv_crop_rect = ispv1_get_yuv_crop_rect;
	ispv1_ctl.isp_set_yuv_crop_pos = ispv1_set_yuv_crop_pos;
	ispv1_ctl.isp_tune_ops->isp_get_current_ccm_rgain		= mini_ispv1_get_current_ccm_rgain;
	ispv1_ctl.isp_tune_ops->isp_get_current_ccm_bgain		= mini_ispv1_get_current_ccm_bgain;
	ispv1_sensor_reg_ctl.isp_power_sensor				= ispv1_power_sensor;
	ispv1_sensor_reg_ctl.isp_reset_sensor				= ispv1_reset_sensor;
	ispv1_sensor_reg_ctl.isp_read_sensor_reg			= ispv1_read_sensor_byte;
	ispv1_sensor_reg_ctl.isp_update_flip				= ispv1_update_flip;
	ispv1_sensor_reg_ctl.isp_write_sensor_reg			= ispv1_write_sensor_byte;
	ispv1_sensor_reg_ctl.isp_write_sensor_seq			= ispv1_write_sensor_seq;
	ispv1_sensor_reg_ctl.isp_write_sensor_group_seq			= ispv1_write_sensor_group_seq;
	ispv1_sensor_reg_ctl.isp_write_isp_seq				= ispv1_write_isp_seq;
	ispv1_sensor_reg_ctl.isp_read_isp_seq			= ispv1_read_isp_seq;
	ispv1_sensor_reg_ctl.isp_enable_mclk				= ispv1_enable_mclk;

	mini_isp_hw_data.cur_state	= STATE_MAX;
	mini_isp_hw_data.pix_fmt	= V4L2_PIX_FMT_NV12;
	mini_isp_hw_data.flash_mode = CAMERA_FLASH_AUTO;

	mini_isp_hw_data.flash_resume = false;
	mini_isp_hw_data.ae_resume = false;

    mini_isp_hw_data.process_mode = ISP_CAPTURE_ONLINE;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: get_isp_hw_controller;
 * Description : return mini_isp_hw_controller interface;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
mini_isp_hw_controller *mini_get_isp_hw_controller(void)
{
	/*
	 * we need to set isp_hw_init field first,
	 * because it is an invalid value at the
	 * first calling of this function.
	 */
	ispv1_ctl.isp_hw_init = ispv1_hw_init;
	return &ispv1_ctl;
}

/*
 **************************************************************************
 * FunctionName: mini_get_isp_sensor_reg_controller;
 * Description : return mini_isp_sensor_reg_controller to isp_io;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
mini_isp_sensor_reg_controller *mini_get_isp_sensor_reg_controller(void)
{
	return &ispv1_sensor_reg_ctl;
}

/******************* END ********************/
