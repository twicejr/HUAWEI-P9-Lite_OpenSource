/*
 * Synaptics DSX touchscreen driver
 *
 * Copyright (C) 2012 Synaptics Incorporated
 *
 * Copyright (C) 2012 Alexandra Chin <alexandra.chin@tw.synaptics.com>
 * Copyright (C) 2012 Scott Lin <scott.lin@tw.synaptics.com>
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
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/input.h>
#include <linux/ctype.h>
#include <linux/hrtimer.h>
#include "synaptics.h"
#include <dsm/dsm_pub.h>
#include <../../huawei_touchscreen_chips.h>
#include "raw_data.h"
#define WATCHDOG_TIMEOUT_S 2
#define FORCE_TIMEOUT_100MS 10
#define STATUS_WORK_INTERVAL 20 /* ms */
#define MAX_I2C_MSG_LENS 0x3F

#define RX_NUMBER 89  //f01 control_base_addr + 57
#define TX_NUMBER 90  //f01 control_base_addr + 58
#define RX_NUMBER_S3207 39  //f11 control_base_addr + 39
#define TX_NUMBER_S3207 40  //f11 control_base_addr + 40
#define BOOTLOADER_ID_OFFSET 0
#define BOOTLOADER_ID_OFFSET_V7 1

#define STATUS_IDLE 0
#define STATUS_BUSY 1

#define DATA_REPORT_INDEX_OFFSET 1
#define DATA_REPORT_DATA_OFFSET 3

#define COMMAND_GET_REPORT 1
#define COMMAND_FORCE_CAL 2
#define COMMAND_FORCE_UPDATE 4
#define F54_READ_RATE_OFFSET 9

#define CONTROL_0_SIZE 1
#define CONTROL_1_SIZE 1
#define CONTROL_2_SIZE 2
#define CONTROL_3_SIZE 1
#define CONTROL_4_6_SIZE 3
#define CONTROL_7_SIZE 1
#define CONTROL_8_9_SIZE 3
#define CONTROL_10_SIZE 1
#define CONTROL_11_SIZE 2
#define CONTROL_12_13_SIZE 2
#define CONTROL_14_SIZE 1
#define CONTROL_15_SIZE 1
#define CONTROL_16_SIZE 1
#define CONTROL_17_SIZE 1
#define CONTROL_18_SIZE 1
#define CONTROL_19_SIZE 1
#define CONTROL_20_SIZE 1
#define CONTROL_21_SIZE 2
#define CONTROL_22_26_SIZE 7
#define CONTROL_27_SIZE 1
#define CONTROL_28_SIZE 2
#define CONTROL_29_SIZE 1
#define CONTROL_30_SIZE 1
#define CONTROL_31_SIZE 1
#define CONTROL_32_35_SIZE 8
#define CONTROL_36_SIZE 1
#define CONTROL_37_SIZE 1
#define CONTROL_38_SIZE 1
#define CONTROL_39_SIZE 1
#define CONTROL_40_SIZE 1
#define CONTROL_41_SIZE 1
#define CONTROL_42_SIZE 2
#define CONTROL_43_54_SIZE 13
#define CONTROL_55_56_SIZE 2
#define CONTROL_57_SIZE 1
#define CONTROL_58_SIZE 1
#define CONTROL_59_SIZE 2
#define CONTROL_60_62_SIZE 3
#define CONTROL_63_SIZE 1
#define CONTROL_64_67_SIZE 4
#define CONTROL_68_73_SIZE 8
#define CONTROL_74_SIZE 2
#define CONTROL_75_SIZE 1
#define CONTROL_76_SIZE 1
#define CONTROL_77_78_SIZE 2
#define CONTROL_79_83_SIZE 5
#define CONTROL_84_85_SIZE 2
#define CONTROL_86_SIZE 1
#define CONTROL_87_SIZE 1
#define CONTROL_88_SIZE 1

#define HIGH_RESISTANCE_DATA_SIZE 6
#define FULL_RAW_CAP_MIN_MAX_DATA_SIZE 4
#define TREX_DATA_SIZE 7

#define NO_AUTO_CAL_MASK 0x01
#define F54_BUF_LEN 80
#define TP_TEST_FAILED_REASON_LEN 20

static char tp_test_failed_reason[TP_TEST_FAILED_REASON_LEN] = {"-software_reason"};
static unsigned short report_rate_offset = 38;
static char buf_f54test_result[F54_BUF_LEN] = {0};//store mmi test result
extern char raw_data_limit_flag;
static int mmi_buf_size = 0;
static int rawdata_size = 0;
extern struct dsm_client *tp_dclient;
extern struct ts_data g_ts_data;

static int synaptics_rmi4_f54_attention(void);

enum f54_ctr_work_rate {
	F54_AUTO_RATE = 0,
	F54_60LOW_RATE = 2,
	F54_120HI_RATE = 4,
};

enum f54_data_work_rate {
	F54_DATA120_RATE = 8,
	F54_DATA60_RATE = 4,
};

enum f54_report_types {
	F54_8BIT_IMAGE = 1,
	F54_16BIT_IMAGE = 2,
	F54_RAW_16BIT_IMAGE = 3,
	F54_HIGH_RESISTANCE = 4,
	F54_TX_TO_TX_SHORT = 5,
	F54_RX_TO_RX1 = 7,
	F54_TRUE_BASELINE = 9,
	F54_FULL_RAW_CAP_MIN_MAX = 13,
	F54_RX_OPENS1 = 14,
	F54_TX_OPEN = 15,
	F54_TX_TO_GROUND = 16,
	F54_RX_TO_RX2 = 17,
	F54_RX_OPENS2 = 18,
	F54_FULL_RAW_CAP = 19,
	F54_FULL_RAW_CAP_RX_COUPLING_COMP = 20,
	F54_SENSOR_SPEED = 22,
	F54_ADC_RANGE = 23,
	F54_TREX_OPENS = 24,
	F54_TREX_TO_GND = 25,
	F54_TREX_SHORTS = 26,
	INVALID_REPORT_TYPE = -1,
};

enum f54_rawdata_limit {
	RAW_DATA_UP = 0,
	RAW_DATA_LOW = 1,
	DELT_DATA_UP = 2,
	DELT_DATA_LOW = 3,
	RX_TO_RX_UP = 4,
	RX_TO_RX_LOW = 5,
	TX_TO_TX_UP = 6,
	TX_TO_TX_LOW = 7,
};

struct f54_query {
	union {
		struct {
			/* query 0 */
			unsigned char num_of_rx_electrodes;

			/* query 1 */
			unsigned char num_of_tx_electrodes;

			/* query 2 */
			unsigned char f54_query2_b0__1:2;
			unsigned char has_baseline:1;
			unsigned char has_image8:1;
			unsigned char f54_query2_b4__5:2;
			unsigned char has_image16:1;
			unsigned char f54_query2_b7:1;

			/* queries 3.0 and 3.1 */
			unsigned short clock_rate;

			/* query 4 */
			unsigned char touch_controller_family;

			/* query 5 */
			unsigned char has_pixel_touch_threshold_adjustment:1;
			unsigned char f54_query5_b1__7:7;

			/* query 6 */
			unsigned char has_sensor_assignment:1;
			unsigned char has_interference_metric:1;
			unsigned char has_sense_frequency_control:1;
			unsigned char has_firmware_noise_mitigation:1;
			unsigned char has_ctrl11:1;
			unsigned char has_two_byte_report_rate:1;
			unsigned char has_one_byte_report_rate:1;
			unsigned char has_relaxation_control:1;

			/* query 7 */
			unsigned char curve_compensation_mode:2;
			unsigned char f54_query7_b2__7:6;

			/* query 8 */
			unsigned char f54_query8_b0:1;
			unsigned char has_iir_filter:1;
			unsigned char has_cmn_removal:1;
			unsigned char has_cmn_maximum:1;
			unsigned char has_touch_hysteresis:1;
			unsigned char has_edge_compensation:1;
			unsigned char has_per_frequency_noise_control:1;
			unsigned char has_enhanced_stretch:1;

			/* query 9 */
			unsigned char has_force_fast_relaxation:1;
			unsigned char has_multi_metric_state_machine:1;
			unsigned char has_signal_clarity:1;
			unsigned char has_variance_metric:1;
			unsigned char has_0d_relaxation_control:1;
			unsigned char has_0d_acquisition_control:1;
			unsigned char has_status:1;
			unsigned char has_slew_metric:1;

			/* query 10 */
			unsigned char has_h_blank:1;
			unsigned char has_v_blank:1;
			unsigned char has_long_h_blank:1;
			unsigned char has_startup_fast_relaxation:1;
			unsigned char has_esd_control:1;
			unsigned char has_noise_mitigation2:1;
			unsigned char has_noise_state:1;
			unsigned char has_energy_ratio_relaxation:1;

			/* query 11 */
			unsigned char has_excessive_noise_reporting:1;
			unsigned char has_slew_option:1;
			unsigned char has_two_overhead_bursts:1;
			unsigned char has_query13:1;
			unsigned char has_one_overhead_burst:1;
			unsigned char f54_query11_b5:1;
			unsigned char has_ctrl88:1;
			unsigned char has_query15:1;

			/* query 12 */
			unsigned char number_of_sensing_frequencies:4;
			unsigned char f54_query12_b4__7:4;
		} __packed;
		unsigned char data[14];
	};
};

struct f54_control_0 {
	union {
		struct {
			unsigned char no_relax:1;
			unsigned char no_scan:1;
			unsigned char force_fast_relaxation:1;
			unsigned char startup_fast_relaxation:1;
			unsigned char gesture_cancels_sfr:1;
			unsigned char enable_energy_ratio_relaxation:1;
			unsigned char excessive_noise_attn_enable:1;
			unsigned char f54_control0_b7:1;
		} __packed;
		struct {
			unsigned char data[1];
			unsigned short address;
		} __packed;
	};
};

struct f54_control_1 {
	union {
		struct {
			unsigned char bursts_per_cluster:4;
			unsigned char f54_ctrl1_b4__7:4;
		} __packed;
		struct {
			unsigned char data[1];
			unsigned short address;
		} __packed;
	};
};

struct f54_control_2 {
	union {
		struct {
			unsigned short saturation_cap;
		} __packed;
		struct {
			unsigned char data[2];
			unsigned short address;
		} __packed;
	};
};

struct f54_control_3 {
	union {
		struct {
			unsigned char pixel_touch_threshold;
		} __packed;
		struct {
			unsigned char data[1];
			unsigned short address;
		} __packed;
	};
};

struct f54_control_4__6 {
	union {
		struct {
			/* control 4 */
			unsigned char rx_feedback_cap:2;
			unsigned char bias_current:2;
			unsigned char f54_ctrl4_b4__7:4;

			/* control 5 */
			unsigned char low_ref_cap:2;
			unsigned char low_ref_feedback_cap:2;
			unsigned char low_ref_polarity:1;
			unsigned char f54_ctrl5_b5__7:3;

			/* control 6 */
			unsigned char high_ref_cap:2;
			unsigned char high_ref_feedback_cap:2;
			unsigned char high_ref_polarity:1;
			unsigned char f54_ctrl6_b5__7:3;
		} __packed;
		struct {
			unsigned char data[3];
			unsigned short address;
		} __packed;
	};
};

struct f54_control_7 {
	union {
		struct {
			unsigned char cbc_cap:3;
			unsigned char cbc_polarity:1;
			unsigned char cbc_tx_carrier_selection:1;
			unsigned char f54_ctrl7_b5__7:3;
		} __packed;
		struct {
			unsigned char data[1];
			unsigned short address;
		} __packed;
	};
};

struct f54_control_8__9 {
	union {
		struct {
			/* control 8 */
			unsigned short integration_duration:10;
			unsigned short f54_ctrl8_b10__15:6;

			/* control 9 */
			unsigned char reset_duration;
		} __packed;
		struct {
			unsigned char data[3];
			unsigned short address;
		} __packed;
	};
};

struct f54_control_10 {
	union {
		struct {
			unsigned char noise_sensing_bursts_per_image:4;
			unsigned char f54_ctrl10_b4__7:4;
		} __packed;
		struct {
			unsigned char data[1];
			unsigned short address;
		} __packed;
	};
};

struct f54_control_11 {
	union {
		struct {
			unsigned short f54_ctrl11;
		} __packed;
		struct {
			unsigned char data[2];
			unsigned short address;
		} __packed;
	};
};

struct f54_control_12__13 {
	union {
		struct {
			/* control 12 */
			unsigned char slow_relaxation_rate;

			/* control 13 */
			unsigned char fast_relaxation_rate;
		} __packed;
		struct {
			unsigned char data[2];
			unsigned short address;
		} __packed;
	};
};

struct f54_control_14 {
	union {
		struct {
				unsigned char rxs_on_xaxis:1;
				unsigned char curve_comp_on_txs:1;
				unsigned char f54_ctrl14_b2__7:6;
		} __packed;
		struct {
			unsigned char data[1];
			unsigned short address;
		} __packed;
	};
};

struct f54_control_15n {
	unsigned char sensor_rx_assignment;
};

struct f54_control_15 {
	struct f54_control_15n *data;
	unsigned short address;
	unsigned char length;
};

struct f54_control_16n {
	unsigned char sensor_tx_assignment;
};

struct f54_control_16 {
	struct f54_control_16n *data;
	unsigned short address;
	unsigned char length;
};

struct f54_control_17n {
	unsigned char burst_count_b8__10:3;
	unsigned char disable:1;
	unsigned char f54_ctrl17_b4:1;
	unsigned char filter_bandwidth:3;
};

struct f54_control_17 {
	struct f54_control_17n *data;
	unsigned short address;
	unsigned char length;
};

struct f54_control_18n {
	unsigned char burst_count_b0__7;
};

struct f54_control_18 {
	struct f54_control_18n *data;
	unsigned short address;
	unsigned char length;
};

struct f54_control_19n {
	unsigned char stretch_duration;
};

struct f54_control_19 {
	struct f54_control_19n *data;
	unsigned short address;
	unsigned char length;
};

struct f54_control_20 {
	union {
		struct {
			unsigned char disable_noise_mitigation:1;
			unsigned char f54_ctrl20_b1__7:7;
		} __packed;
		struct {
			unsigned char data[1];
			unsigned short address;
		} __packed;
	};
};

struct f54_control_21 {
	union {
		struct {
			unsigned short freq_shift_noise_threshold;
		} __packed;
		struct {
			unsigned char data[2];
			unsigned short address;
		} __packed;
	};
};

struct f54_control_22__26 {
	union {
		struct {
			/* control 22 */
			unsigned char f54_ctrl22;

			/* control 23 */
			unsigned short medium_noise_threshold;

			/* control 24 */
			unsigned short high_noise_threshold;

			/* control 25 */
			unsigned char noise_density;

			/* control 26 */
			unsigned char frame_count;
		} __packed;
		struct {
			unsigned char data[7];
			unsigned short address;
		} __packed;
	};
};

struct f54_control_27 {
	union {
		struct {
			unsigned char iir_filter_coef;
		} __packed;
		struct {
			unsigned char data[1];
			unsigned short address;
		} __packed;
	};
};

struct f54_control_28 {
	union {
		struct {
			unsigned short quiet_threshold;
		} __packed;
		struct {
			unsigned char data[2];
			unsigned short address;
		} __packed;
	};
};

struct f54_control_29 {
	union {
		struct {
			/* control 29 */
			unsigned char f54_ctrl29_b0__6:7;
			unsigned char cmn_filter_disable:1;
		} __packed;
		struct {
			unsigned char data[1];
			unsigned short address;
		} __packed;
	};
};

struct f54_control_30 {
	union {
		struct {
			unsigned char cmn_filter_max;
		} __packed;
		struct {
			unsigned char data[1];
			unsigned short address;
		} __packed;
	};
};

struct f54_control_31 {
	union {
		struct {
			unsigned char touch_hysteresis;
		} __packed;
		struct {
			unsigned char data[1];
			unsigned short address;
		} __packed;
	};
};

struct f54_control_32__35 {
	union {
		struct {
			/* control 32 */
			unsigned short rx_low_edge_comp;

			/* control 33 */
			unsigned short rx_high_edge_comp;

			/* control 34 */
			unsigned short tx_low_edge_comp;

			/* control 35 */
			unsigned short tx_high_edge_comp;
		} __packed;
		struct {
			unsigned char data[8];
			unsigned short address;
		} __packed;
	};
};

struct f54_control_36n {
	unsigned char axis1_comp;
};

struct f54_control_36 {
	struct f54_control_36n *data;
	unsigned short address;
	unsigned char length;
};

struct f54_control_37n {
	unsigned char axis2_comp;
};

struct f54_control_37 {
	struct f54_control_37n *data;
	unsigned short address;
	unsigned char length;
};

struct f54_control_38n {
	unsigned char noise_control_1;
};

struct f54_control_38 {
	struct f54_control_38n *data;
	unsigned short address;
	unsigned char length;
};

struct f54_control_39n {
	unsigned char noise_control_2;
};

struct f54_control_39 {
	struct f54_control_39n *data;
	unsigned short address;
	unsigned char length;
};

struct f54_control_40n {
	unsigned char noise_control_3;
};

struct f54_control_40 {
	struct f54_control_40n *data;
	unsigned short address;
	unsigned char length;
};

struct f54_control_41 {
	union {
		struct {
			unsigned char no_signal_clarity:1;
			unsigned char f54_ctrl41_b1__7:7;
		} __packed;
		struct {
			unsigned char data[1];
			unsigned short address;
		} __packed;
	};
};

struct f54_control_57 {
	union {
		struct {
			unsigned char cbc_cap_0d:3;
			unsigned char cbc_polarity_0d:1;
			unsigned char cbc_tx_carrier_selection_0d:1;
			unsigned char f54_ctrl57_b5__7:3;
		} __packed;
		struct {
			unsigned char data[1];
			unsigned short address;
		} __packed;
	};
};

struct f54_control_88 {
	union {
		struct {
			unsigned char tx_low_reference_polarity:1;
			unsigned char tx_high_reference_polarity:1;
			unsigned char abs_low_reference_polarity:1;
			unsigned char abs_polarity:1;
			unsigned char cbc_polarity:1;
			unsigned char cbc_tx_carrier_selection:1;
			unsigned char charge_pump_enable:1;
			unsigned char cbc_abs_auto_servo:1;
		} __packed;
		struct {
			unsigned char data[1];
			unsigned short address;
		} __packed;
	};
};

struct f54_control {
	struct f54_control_0 *reg_0;
	struct f54_control_1 *reg_1;
	struct f54_control_2 *reg_2;
	struct f54_control_3 *reg_3;
	struct f54_control_4__6 *reg_4__6;
	struct f54_control_7 *reg_7;
	struct f54_control_8__9 *reg_8__9;
	struct f54_control_10 *reg_10;
	struct f54_control_11 *reg_11;
	struct f54_control_12__13 *reg_12__13;
	struct f54_control_14 *reg_14;
	struct f54_control_15 *reg_15;
	struct f54_control_16 *reg_16;
	struct f54_control_17 *reg_17;
	struct f54_control_18 *reg_18;
	struct f54_control_19 *reg_19;
	struct f54_control_20 *reg_20;
	struct f54_control_21 *reg_21;
	struct f54_control_22__26 *reg_22__26;
	struct f54_control_27 *reg_27;
	struct f54_control_28 *reg_28;
	struct f54_control_29 *reg_29;
	struct f54_control_30 *reg_30;
	struct f54_control_31 *reg_31;
	struct f54_control_32__35 *reg_32__35;
	struct f54_control_36 *reg_36;
	struct f54_control_37 *reg_37;
	struct f54_control_38 *reg_38;
	struct f54_control_39 *reg_39;
	struct f54_control_40 *reg_40;
	struct f54_control_41 *reg_41;
	struct f54_control_57 *reg_57;
	struct f54_control_88 *reg_88;
};

struct f54_query_13 {
	union {
		struct {
			unsigned char has_ctrl86:1;
			unsigned char has_ctrl87:1;
			unsigned char has_ctrl87_sub0:1;
			unsigned char has_ctrl87_sub1:1;
			unsigned char has_ctrl87_sub2:1;
			unsigned char has_cidim:1;
			unsigned char has_noise_mitigation_enhancement:1;
			unsigned char has_rail_im:1;
		} __packed;
		unsigned char data[1];
	};
};

struct f54_query_15 {
	union {
		struct {
			unsigned char has_ctrl90:1;
			unsigned char has_transmit_strength:1;
			unsigned char has_ctrl87_sub3:1;
			unsigned char has_query16:1;
			unsigned char has_query20:1;
			unsigned char has_query21:1;
			unsigned char has_query22:1;
			unsigned char has_query25:1;
		} __packed;
		unsigned char data[1];
	};
};

struct f54_query_16 {
	union {
		struct {
			unsigned char has_query17:1;
			unsigned char has_data17:1;
			unsigned char has_ctrl92:1;
			unsigned char has_ctrl93:1;
			unsigned char has_ctrl94_query18:1;
			unsigned char has_ctrl95_query19:1;
			unsigned char has_ctrl99:1;
			unsigned char has_ctrl100:1;
		} __packed;
		unsigned char data[1];
	};
};

struct f54_query_21 {
	union {
		struct {
			unsigned char has_abs_rx:1;
			unsigned char has_abs_tx:1;
			unsigned char has_ctrl91:1;
			unsigned char has_ctrl96:1;
			unsigned char has_ctrl97:1;
			unsigned char has_ctrl98:1;
			unsigned char has_data19:1;
			unsigned char has_query24_data18:1;
		} __packed;
		unsigned char data[1];
	};
};

struct f55_query {
	union {
		struct {
			/* query 0 */
			unsigned char num_of_rx_electrodes;

			/* query 1 */
			unsigned char num_of_tx_electrodes;

			/* query 2 */
			unsigned char has_sensor_assignment:1;
			unsigned char has_edge_compensation:1;
			unsigned char curve_compensation_mode:2;
			unsigned char reserved:4;
		} __packed;
		unsigned char data[3];
	};
};


struct synaptics_rmi4_fn55_desc {
	unsigned short query_base_addr;
	unsigned short control_base_addr;
};
struct synaptics_fn54_statics_data {
	short RawimageAverage;
	short RawimageMaxNum;
	short RawimageMinNum;
	short RawimageNULL;
};
enum bl_version {
	V5 = 5,
	V6 = 6,
	V7 = 7,
};

struct synaptics_rmi4_f54_handle {
	bool no_auto_cal;
	unsigned char status;
	unsigned char intr_mask;
	unsigned char intr_reg_num;
	unsigned char *report_data;
	unsigned char bootloader_id[2];
	unsigned short query_base_addr;
	unsigned short control_base_addr;
	unsigned short data_base_addr;
	unsigned short command_base_addr;
	unsigned short fifoindex;
	unsigned int report_size;
	unsigned int data_buffer_size;

	enum bl_version bl_version;
	enum f54_report_types report_type;

	char *mmi_buf;
	int *rawdatabuf;
	struct f54_query query;
	struct f54_query_13 query_13;
	struct f54_query_15 query_15;
	struct f54_query_16 query_16;
	struct f54_query_21 query_21;
	struct f54_control control;
	struct kobject *attr_dir;
	struct synaptics_fn54_statics_data raw_statics_data;
	struct synaptics_fn54_statics_data delta_statics_data;
	struct synaptics_rmi4_exp_fn_ptr *fn_ptr;
	struct synaptics_rmi4_data *rmi4_data;
	struct synaptics_rmi4_fn55_desc *fn55;
	struct synaptics_rmi4_fn_desc f34_fd;
};


static struct synaptics_rmi4_f54_handle *f54;

DECLARE_COMPLETION(f54_remove_complete);

static void set_report_size(void)
{
	int rc = 0;
	switch (f54->report_type) {
	case F54_8BIT_IMAGE:
		f54->report_size = f54->rmi4_data->num_of_rx * f54->rmi4_data->num_of_tx;
		break;
	case F54_16BIT_IMAGE:
	case F54_RAW_16BIT_IMAGE:
	case F54_TRUE_BASELINE:
	case F54_FULL_RAW_CAP:
	case F54_FULL_RAW_CAP_RX_COUPLING_COMP:
	case F54_SENSOR_SPEED:
		f54->report_size = 2 * f54->rmi4_data->num_of_rx * f54->rmi4_data->num_of_tx;
		break;
	case F54_HIGH_RESISTANCE:
		f54->report_size = HIGH_RESISTANCE_DATA_SIZE;
		break;
	case F54_TX_TO_TX_SHORT:
	case F54_TX_OPEN:
		f54->report_size =  (f54->rmi4_data->num_of_tx + 7) / 8;
		break;
	case F54_TX_TO_GROUND:
		f54->report_size = 3;
		break;
	case F54_RX_TO_RX1:
	//edw
		if (f54->rmi4_data->num_of_rx < f54->rmi4_data->num_of_tx)
			f54->report_size = 2 * f54->rmi4_data->num_of_rx * f54->rmi4_data->num_of_rx;
		else
			f54->report_size = 2 * f54->rmi4_data->num_of_rx * f54->rmi4_data->num_of_tx;
		break;
	//edw
	case F54_RX_OPENS1:
		if (f54->rmi4_data->num_of_rx < f54->rmi4_data->num_of_tx)
			f54->report_size = 2 * f54->rmi4_data->num_of_rx * f54->rmi4_data->num_of_rx;
		else
			f54->report_size = 2 * f54->rmi4_data->num_of_rx * f54->rmi4_data->num_of_tx;
		break;
	case F54_FULL_RAW_CAP_MIN_MAX:
		f54->report_size = FULL_RAW_CAP_MIN_MAX_DATA_SIZE;
		break;
	case F54_RX_TO_RX2:
	case F54_RX_OPENS2:
		if (f54->rmi4_data->num_of_rx <= f54->rmi4_data->num_of_tx)
			f54->report_size = 0;
		else
			f54->report_size = 2 * f54->rmi4_data->num_of_rx * (f54->rmi4_data->num_of_rx - f54->rmi4_data->num_of_tx);
		break;
	case F54_ADC_RANGE:
		if (f54->query.has_signal_clarity) {
			rc = f54->fn_ptr->read(f54->rmi4_data,
					f54->control.reg_41->address,
					f54->control.reg_41->data,
					sizeof(f54->control.reg_41->data));
			if (rc < 0) {
				TS_LOG_INFO("Failed to read control reg_41\n");
				f54->report_size = 0;
				break;
			}
			if (!f54->control.reg_41->no_signal_clarity) {
				if (f54->rmi4_data->num_of_tx % 4)
					f54->rmi4_data->num_of_tx += 4 - (f54->rmi4_data->num_of_tx % 4);
			}
		}
		f54->report_size = 2 * f54->rmi4_data->num_of_rx * f54->rmi4_data->num_of_tx;
		break;
	case F54_TREX_OPENS:
	case F54_TREX_TO_GND:
	case F54_TREX_SHORTS:
		f54->report_size = TREX_DATA_SIZE;
		break;
	default:
		f54->report_size = 0;
	}

	return;
}


/* when the report type is  3 or 9, we call this function to  to find open
* transmitter electrodes, open receiver electrodes, transmitter-to-ground
* shorts, receiver-to-ground shorts, and transmitter-to-receiver shorts. */
static int f54_rawimage_report (void)
{
	short Rawimage;
	short Result = 0;

	int i;
	int raw_cap_uplimit = f54->rmi4_data->synaptics_chip_data->raw_limit_buf[RAW_DATA_UP];
	int raw_cap_lowlimit = f54->rmi4_data->synaptics_chip_data->raw_limit_buf[RAW_DATA_LOW];
	int RawimageSum = 0;
	short RawimageAverage = 0;
	short RawimageMaxNum,RawimageMinNum;

	TS_LOG_INFO("f54_rawimage_report: rx = %d, tx = %d, mmibuf_size =%d, raw_cap_uplimit = %d,raw_cap_lowlimit = %d\n", f54->rmi4_data->num_of_rx, f54->rmi4_data->num_of_tx, mmi_buf_size, raw_cap_uplimit, raw_cap_lowlimit);

	RawimageMaxNum = (f54->mmi_buf[0]) | (f54->mmi_buf[1] << 8);
	RawimageMinNum = (f54->mmi_buf[0]) | (f54->mmi_buf[1] << 8);
	for ( i = 0; i < mmi_buf_size; i+=2)
	{
		Rawimage = (f54->mmi_buf[i]) | (f54->mmi_buf[i+1] << 8);
		RawimageSum += Rawimage;
		if(RawimageMaxNum < Rawimage)
			RawimageMaxNum = Rawimage;
		if(RawimageMinNum > Rawimage)
			RawimageMinNum = Rawimage;
	}
	RawimageAverage = RawimageSum/(mmi_buf_size/2);
	f54->raw_statics_data.RawimageAverage = RawimageAverage;
	f54->raw_statics_data.RawimageMaxNum = RawimageMaxNum;
	f54->raw_statics_data.RawimageMinNum = RawimageMinNum;

	for ( i = 0; i < mmi_buf_size; i+=2)
	{
		Rawimage = (f54->mmi_buf[i]) | (f54->mmi_buf[i+1] << 8);
		if(raw_data_limit_flag){
			raw_cap_uplimit = RawCapUpperLimit[i/2];
			raw_cap_lowlimit = RawCapLowerLimit[i/2];
		}
		if ((Rawimage >= raw_cap_lowlimit) && (Rawimage <= raw_cap_uplimit))
		{
			Result++;
		}
		else{
			TS_LOG_INFO("[%d,%d]\n",i/2,Rawimage);
		}
	}

	if (Result == (mmi_buf_size/2)) {
		TS_LOG_DEBUG("rawdata is all right, Result = %d\n", Result);
		return 1;
	} else {
		TS_LOG_ERR("rawdata is out of range, Result = %d\n", Result);
	#if defined (CONFIG_HUAWEI_DSM)
		if (!dsm_client_ocuppy(tp_dclient)) {
			TS_LOG_INFO("try to client record 20002 for rawdata \n");
			dsm_client_record(tp_dclient, "device status for 20002 is :%d\n", Result);
			dsm_client_notify(tp_dclient, DSM_TP_RAWDATA_ERROR_NO);
		}
	#endif
		return 0;
	}
}

static int write_to_f54_register(unsigned char report_type)
{
	unsigned char command;
	int result;

	TS_LOG_INFO("report type = %d\n", report_type);

	command = report_type;
	/*set report type*/
	if (F54_RX_TO_RX1 != command)
	{
		result = f54->fn_ptr->write(f54->rmi4_data, f54->data_base_addr, &command, 1);
		if (result < 0){
		       TS_LOG_ERR("Could not write report type to 0x%x\n", f54->data_base_addr);
			return result;
		}
	}
	mdelay(5);

	/*set get_report to 1*/
	command = (unsigned char)COMMAND_GET_REPORT;
	result = f54->fn_ptr->write(f54->rmi4_data, f54->command_base_addr, &command, 1);
	msleep(100);

	return result;
}

static int mmi_add_static_data(void)
{
	int i;

	i = strlen(buf_f54test_result);
	if (i >= F54_BUF_LEN) {
		return -EINVAL;
	}
	snprintf((buf_f54test_result+i), F54_BUF_LEN-i,
		"[%4d,%4d,%4d]",
		f54->raw_statics_data.RawimageAverage,
		f54->raw_statics_data.RawimageMaxNum,
		f54->raw_statics_data.RawimageMinNum);

	i = strlen(buf_f54test_result);
	if (i >= F54_BUF_LEN) {
		return -EINVAL;
	}
	snprintf((buf_f54test_result+i), F54_BUF_LEN-i,
		"[%4d,%4d,%4d]",
		f54->delta_statics_data.RawimageAverage,
		f54->delta_statics_data.RawimageMaxNum,
		f54->delta_statics_data.RawimageMinNum);

        return 0;
}

static int f54_deltarawimage_report (void)
{
	short Rawimage;
	int i;
	int delt_cap_uplimit = f54->rmi4_data->synaptics_chip_data->raw_limit_buf[DELT_DATA_UP];
	int delt_cap_lowlimit = f54->rmi4_data->synaptics_chip_data->raw_limit_buf[DELT_DATA_LOW];
	int DeltaRawimageSum = 0;
	short DeltaRawimageAverage = 0;
	short DeltaRawimageMaxNum,DeltaRawimageMinNum;
	short result = 0;

	TS_LOG_INFO("f54_deltarawimage_report enter, delt_cap_uplimit = %d, delt_cap_lowlimit = %d\n", delt_cap_uplimit, delt_cap_lowlimit);

	DeltaRawimageMaxNum = (f54->mmi_buf[0]) | (f54->mmi_buf[1] << 8);
	DeltaRawimageMinNum = (f54->mmi_buf[0]) | (f54->mmi_buf[1] << 8);
	for ( i = 0; i < mmi_buf_size; i+=2)
	{
		Rawimage = (f54->mmi_buf[i]) | (f54->mmi_buf[i+1] << 8);
		DeltaRawimageSum += Rawimage;
		if(DeltaRawimageMaxNum < Rawimage)
			DeltaRawimageMaxNum = Rawimage;
		if(DeltaRawimageMinNum > Rawimage)
			DeltaRawimageMinNum = Rawimage;
	}
	DeltaRawimageAverage = DeltaRawimageSum/(mmi_buf_size/2);
	f54->delta_statics_data.RawimageAverage = DeltaRawimageAverage;
	f54->delta_statics_data.RawimageMaxNum = DeltaRawimageMaxNum;
	f54->delta_statics_data.RawimageMinNum = DeltaRawimageMinNum;
	if(raw_data_limit_flag){
		delt_cap_lowlimit = NoiseCapLowerLimit;
		delt_cap_uplimit = NoiseCapUpperLimit;
	}
	for ( i = 0; i < mmi_buf_size; i+=2)
	{
		Rawimage = (f54->mmi_buf[i]) | (f54->mmi_buf[i+1] << 8);
		if ((Rawimage >= delt_cap_lowlimit) && (Rawimage <= delt_cap_uplimit)) {
			result++;
		}
		else{
			TS_LOG_INFO("[%d,%d]\n",i/2,Rawimage);
		}
	}

	if (result == (mmi_buf_size/2)) {
		TS_LOG_DEBUG("deltadata is all right, Result = %d\n", result);
		return 1;
	} else {
		TS_LOG_ERR("deltadata is out of range, Result = %d\n", result);
	#if defined (CONFIG_HUAWEI_DSM)
		if (!dsm_client_ocuppy(tp_dclient)) {
			TS_LOG_INFO("try to client record 20002 for noisedata \n");
			dsm_client_record(tp_dclient, "device status for 20002 is :%d\n", result);
			dsm_client_notify(tp_dclient, DSM_TP_RAWDATA_ERROR_NO);
		}
	#endif
		return 0;
	}

}

static void mmi_deltacapacitance_test(void)
{
	unsigned char command;
	int result = 0;
	command = (unsigned char) F54_16BIT_IMAGE;
	TS_LOG_INFO("mmi_deltacapacitance_test called\n");
	write_to_f54_register(command);
	f54->report_type = command;
	result = synaptics_rmi4_f54_attention();
	if(result < 0){
		TS_LOG_ERR("Failed to get data\n");
		strncat(buf_f54test_result, "-3F", MAX_STR_LEN);
		return;
	}
	result = f54_deltarawimage_report();
	if(1 == result) {
		strncat(buf_f54test_result, "-3P", MAX_STR_LEN);
	} else {
		TS_LOG_ERR("deltadata test is out of range, test result is 3F\n");
		strncat(buf_f54test_result, "-3F", MAX_STR_LEN);
		strncpy(tp_test_failed_reason,"-panel_reason",TP_TEST_FAILED_REASON_LEN);
	}
	return;
}

static int f54_delta_rx_report (void)
{
	short Rawimage_rx;
	short Rawimage_rx1;
	short Rawimage_rx2;
	short Result = 0;
	int i = 0;
	int j = 0;
	int step = 0;
	int delt_cap_uplimit = f54->rmi4_data->synaptics_chip_data->raw_limit_buf[RX_TO_RX_UP];
	int delt_cap_lowlimit = f54->rmi4_data->synaptics_chip_data->raw_limit_buf[RX_TO_RX_LOW];

	TS_LOG_INFO("rx = %d, tx = %d, delt_cap_uplimit = %d, delt_cap_lowlimit = %d\n",f54->rmi4_data->num_of_rx, f54->rmi4_data->num_of_tx, delt_cap_uplimit, delt_cap_lowlimit);

	for ( i = 0; i < mmi_buf_size; i+=2)
	{
		Rawimage_rx1 = (f54->mmi_buf[i]) | (f54->mmi_buf[i+1] << 8);
		Rawimage_rx2 = (f54->mmi_buf[i+2]) | (f54->mmi_buf[i+3] << 8);
		Rawimage_rx = Rawimage_rx2 - Rawimage_rx1;
		if(raw_data_limit_flag){
			delt_cap_uplimit = RxDeltaCapUpperLimit[i/2 - step];
			delt_cap_lowlimit = RxDeltaCapLowerLimit[i/2 - step];
		}
		if ((Rawimage_rx <= delt_cap_uplimit) && (Rawimage_rx >= delt_cap_lowlimit)){
			Result++;
		}
		else{
			TS_LOG_INFO("[%d,%d]\n",i/2 - step,Rawimage_rx);
		}
		j++;
		if (j == f54->rmi4_data->num_of_rx-1) {
			i += 2;
			j = 0;
			step += 1;
		}
	}
	if (Result == (mmi_buf_size/2 - f54->rmi4_data->num_of_tx)) {
		TS_LOG_DEBUG("rawdata rx diff is all right, Result = %d\n", Result);
		return 1;
	}
	else {
		TS_LOG_ERR("rawdata rx diff is out of range, Result = %d\n", Result);
	#if defined (CONFIG_HUAWEI_DSM)
		if (!dsm_client_ocuppy(tp_dclient)) {
			TS_LOG_INFO("try to client record 20002 for rx diff \n");
			dsm_client_record(tp_dclient, "device status for 20002 is :%d\n", Result);
			dsm_client_notify(tp_dclient, DSM_TP_RAWDATA_ERROR_NO);
		}
	#endif
		return 0;
	}

}
static int f54_delta_tx_report (void)
{
	short *Rawimage_tx = NULL;
	short Rawimage_delta_tx;
	int i,j,tx_n,rx_n;
	int Result=0;
	int tx_to_tx_cap_uplimit = f54->rmi4_data->synaptics_chip_data->raw_limit_buf[TX_TO_TX_UP];
	int tx_to_tx_cap_lowlimit = f54->rmi4_data->synaptics_chip_data->raw_limit_buf[TX_TO_TX_LOW];

	TS_LOG_INFO("rx = %d, tx = %d, tx_to_tx_cap_uplimit = %d, tx_to_tx_cap_lowlimit = %d\n",f54->rmi4_data->num_of_rx, f54->rmi4_data->num_of_tx, tx_to_tx_cap_uplimit, tx_to_tx_cap_lowlimit);

	Rawimage_tx = (short *)kzalloc(mmi_buf_size, GFP_KERNEL);
	if (!Rawimage_tx) {
		TS_LOG_ERR("Rawimage_tx kzalloc error\n");
		return 0;
	}

	for ( i = 0, j = 0; i < mmi_buf_size; i+=2, j++)
		Rawimage_tx[j] = (f54->mmi_buf[i]) | (f54->mmi_buf[i+1] << 8);

	for( tx_n = 0; tx_n < f54->rmi4_data->num_of_tx - 1; tx_n++)
	{
		for(rx_n = 0; rx_n < f54->rmi4_data->num_of_rx; rx_n++)
		{
			if(raw_data_limit_flag){
				tx_to_tx_cap_uplimit = TxDeltaCapUpperLimit[tx_n*f54->rmi4_data->num_of_rx+rx_n];
				tx_to_tx_cap_lowlimit = TxDeltaCapLowerLimit[tx_n*f54->rmi4_data->num_of_rx+rx_n];
			}
			Rawimage_delta_tx = Rawimage_tx[(tx_n+1)*f54->rmi4_data->num_of_rx+rx_n] - Rawimage_tx[tx_n*f54->rmi4_data->num_of_rx+rx_n];
			if((Rawimage_delta_tx <= tx_to_tx_cap_uplimit) && (Rawimage_delta_tx >= tx_to_tx_cap_lowlimit)){
				Result++;
			}
			else{
				TS_LOG_INFO("[%d,%d]\n",tx_n*f54->rmi4_data->num_of_rx+rx_n,Rawimage_delta_tx);
			}
		}
	}
	kfree(Rawimage_tx);

	if (Result == (mmi_buf_size/2 -f54->rmi4_data->num_of_rx)) {
		TS_LOG_DEBUG("rawdata tx diff is all right, Result = %d\n", Result);
		return 1;
	}
	else {
		TS_LOG_ERR("rawdata tx diff is out of range, Result = %d\n", Result);
	#if defined (CONFIG_HUAWEI_DSM)
		if (!dsm_client_ocuppy(tp_dclient)) {
			TS_LOG_INFO("try to client record 20002 for tx diff \n");
			dsm_client_record(tp_dclient, "device status for 20002 is :%d\n", Result);
			dsm_client_notify(tp_dclient, DSM_TP_RAWDATA_ERROR_NO);
		}
	#endif
		return 0;
	}
}

static void mmi_rawcapacitance_test(void)
{
	unsigned char command;
	int result = 0;

	command = (unsigned char) F54_RAW_16BIT_IMAGE;

	TS_LOG_INFO("mmi_rawcapacitance_test called\n");

	write_to_f54_register(command);
	f54->report_type = command;
	result = synaptics_rmi4_f54_attention();
	if(result < 0){
		TS_LOG_ERR("Failed to get data\n");
		strncat(buf_f54test_result, "1F", MAX_STR_LEN);
		return;
	}
	result = f54_rawimage_report();
	if (1 == result) {
		strncat(buf_f54test_result, "1P", MAX_STR_LEN);
	} else {
		TS_LOG_ERR("raw data is out of range, , test result is 1F\n");
		strncat(buf_f54test_result, "1F", MAX_STR_LEN);
		strncpy(tp_test_failed_reason,"-panel_reason",TP_TEST_FAILED_REASON_LEN);
	}
	if (1 == (f54_delta_rx_report() && f54_delta_tx_report())) {
		strncat(buf_f54test_result, "-2P", MAX_STR_LEN);
	} else {
		TS_LOG_ERR("raw data diff is out of range, test result is 2F\n");
		strncat(buf_f54test_result, "-2F", MAX_STR_LEN);
		strncpy(tp_test_failed_reason,"-panel_reason",TP_TEST_FAILED_REASON_LEN);
	}
	return;
}

static int synaptics_f54_malloc(void)
{
	f54 = kzalloc(sizeof(struct synaptics_rmi4_f54_handle), GFP_KERNEL);
	if (!f54) {
		TS_LOG_ERR("Failed to alloc mem for f54\n");
		return -ENOMEM;
	}

	f54->fn_ptr = kzalloc(sizeof(struct synaptics_rmi4_exp_fn_ptr), GFP_KERNEL);
	if (!f54->fn_ptr) {
		TS_LOG_ERR("Failed to alloc mem for fn_ptr\n");
		return -ENOMEM;
	}

	f54->fn55 = kzalloc(sizeof(struct synaptics_rmi4_fn55_desc), GFP_KERNEL);
	if (!f54->fn55) {
		TS_LOG_ERR("Failed to alloc mem for fn55\n");
		return -ENOMEM;
	}

	return NO_ERR;
}

static void synaptics_f54_free(void)
{
	TS_LOG_INFO("kfree f54 memory\n");
	if (f54 && f54->fn_ptr)
		kfree(f54->fn_ptr);
	if (f54 && f54->fn55)
		kfree(f54->fn55);
	if (f54 && f54->mmi_buf)
		kfree(f54->mmi_buf);
	if (f54 && f54->rawdatabuf)
		kfree(f54->rawdatabuf);
	if (f54) {
		kfree(f54);
		f54 = NULL;
	}
}

static void put_capacitance_data (int index)
{
	int i , j;
	short temp;
	f54->rawdatabuf[0] = f54->rmi4_data->num_of_rx;
	f54->rawdatabuf[1] = f54->rmi4_data->num_of_tx;
	for(i = 0, j = index + 2; i < mmi_buf_size; i+=2, j++) {
		temp = (f54->mmi_buf[i]) | (f54->mmi_buf[i+1] << 8);
		f54->rawdatabuf[j] = temp;
	}
}

static void synaptics_change_report_rate(void)
{
	int rc = NO_ERR;
	unsigned char command = 0;
	unsigned char report_rate120 = 0;
	unsigned char report_rate60 = 0;

	if (0 == f54->rmi4_data->synaptics_chip_data->report_rate_test) {
		strncat(buf_f54test_result, "-4P", MAX_STR_LEN);
		TS_LOG_INFO("s3207 change_report_rate default pass\n");
		return;
	}
	TS_LOG_INFO("change report rate 120 first then to 60\n");
	command = (unsigned char)F54_120HI_RATE;
	rc = f54->fn_ptr->write(f54->rmi4_data, f54->control_base_addr + report_rate_offset, &command, 1);
	if(rc < 0){
		TS_LOG_ERR("set ic to 120HZ error because of i2c error");
		strncat(buf_f54test_result, "-4F", MAX_STR_LEN);
		return;
	}
	msleep(50);
	rc = f54->fn_ptr->read(f54->rmi4_data, f54->data_base_addr + F54_READ_RATE_OFFSET, &report_rate120, 1);
	if(rc < 0){
		TS_LOG_ERR("read 120HZ from ic error because of i2c error");
		strncat(buf_f54test_result, "-4F", MAX_STR_LEN);
		return;
	}
       TS_LOG_INFO("work report_rate 120 = %d\n", report_rate120);

	command = (unsigned char)F54_60LOW_RATE;
	rc = f54->fn_ptr->write(f54->rmi4_data, f54->control_base_addr + report_rate_offset, &command, 1);
	if(rc < 0){
		TS_LOG_ERR("write ic to 60HZ error because of i2c error");
		strncat(buf_f54test_result, "-4F", MAX_STR_LEN);
		return;
	}
	msleep(50);
       rc = f54->fn_ptr->read(f54->rmi4_data, f54->data_base_addr + F54_READ_RATE_OFFSET, &report_rate60, 1);
	if(rc < 0){
		TS_LOG_ERR("read 60HZ from ic error because of i2c error");
		strncat(buf_f54test_result, "-4F", MAX_STR_LEN);
		return;
	}
	TS_LOG_INFO("work report_rate 60 = %d\n", report_rate60);

	if((F54_DATA120_RATE == report_rate120) && (F54_DATA60_RATE == report_rate60)) {
		TS_LOG_DEBUG("change rate success\n");
		strncat(buf_f54test_result, "-4P", MAX_STR_LEN);
	} else {
		TS_LOG_ERR("change rate error");
		strncat(buf_f54test_result, "-4F", MAX_STR_LEN);
		strncpy(tp_test_failed_reason,"-panel_reason",TP_TEST_FAILED_REASON_LEN);
		#if defined (CONFIG_HUAWEI_DSM)
			if (atomic_read(&g_ts_data.state) != TS_WORK_IN_SLEEP) {
				if (!dsm_client_ocuppy(tp_dclient)) {
					TS_LOG_INFO("try to client record 20006 for change report rate error \n");
					dsm_client_record(tp_dclient, "for 20006 report_rate120 is :%d, report_rate60 is : %d\n", report_rate120, report_rate60);
					dsm_client_notify(tp_dclient, DSM_TP_CHANGE_REPORT_ERROR_NO);
				}
			}
		#endif
	}
	return;
}


int synaptics_get_cap_data(struct ts_rawdata_info *info)
{
	int rc = NO_ERR;
	unsigned char command;

	TS_LOG_INFO("synaptics_get_cap_data called\n");

	memset(buf_f54test_result, 0, sizeof(buf_f54test_result));
	memset(f54->rawdatabuf, 0, rawdata_size*sizeof(int));

	rc = f54->rmi4_data->status_save(f54->rmi4_data);
	if (rc < 0) {
		TS_LOG_ERR("failed to save glove/holster/palm or other status!\n");
	}

	rc = f54->fn_ptr->read(f54->rmi4_data, f54->data_base_addr, &command, 1);
	if (rc < 0) {		/*i2c communication failed, mmi result is all failed*/
		memcpy(buf_f54test_result, "0F-1F-2F", (strlen("0F-1F-2F")+1));
	} else {
		memcpy(buf_f54test_result, "0P-", (strlen("0P-")+1));
		mmi_rawcapacitance_test();		/*report type == 3*/
		put_capacitance_data(0);
		mmi_deltacapacitance_test();		/*report type == 2*/
		synaptics_change_report_rate();
		put_capacitance_data(mmi_buf_size/2);
		mmi_add_static_data();
	}

	rc = f54->rmi4_data->reset_device(f54->rmi4_data);
	if (rc < 0) {
		TS_LOG_ERR("failed to write command to f01 reset!\n");
		goto exit;
	}
	rc = f54->rmi4_data->status_resume(f54->rmi4_data);
	if (rc < 0) {
		TS_LOG_ERR("failed to resume glove/holster/palm or other status!\n");
	}

	memcpy(info->buff, f54->rawdatabuf, rawdata_size*sizeof(int));
	if (0 == strlen(buf_f54test_result) || strstr(buf_f54test_result, "F")){
		strncat(buf_f54test_result, tp_test_failed_reason, strlen(tp_test_failed_reason));
	}

	switch(f54->rmi4_data->synaptics_chip_data->ic_type) {
		case SYNAPTICS_S3207:
			strncat(buf_f54test_result, "-synaptics_3207", strlen("-synaptics_3207"));
			break;
		case SYNAPTICS_S3350:
			strncat(buf_f54test_result, "-synaptics_3350", strlen("-synaptics_3350"));
			break;
		case SYNAPTICS_S3320:
			strncat(buf_f54test_result, "-synaptics_3320", strlen("-synaptics_3320"));
			break;
		case SYNAPTICS_S3718:
			strncat(buf_f54test_result, "-synaptics_", strlen("-synaptics_"));
			strncat(buf_f54test_result, f54->rmi4_data->rmi4_mod_info.product_id_string,
				strlen(f54->rmi4_data->rmi4_mod_info.product_id_string));
			break;
		default:
			TS_LOG_ERR("failed to recognize ic_ver\n");
			break;
		}

	memcpy(info->result, buf_f54test_result, strlen(buf_f54test_result));
	info->used_size = rawdata_size;
	TS_LOG_INFO("info->used_size = %d\n", info->used_size);
	rc = NO_ERR;
exit:
	synaptics_f54_free();
	return rc;
}

static int synaptics_rmi4_f54_attention(void)
{
	int retval;
	int l;
	unsigned char report_index[2];
	int i = 0;
	unsigned int report_times_max = 0;
	unsigned int report_size_temp = MAX_I2C_MSG_LENS;
	unsigned char *report_data_temp = NULL;

	set_report_size();

	if (f54->report_size == 0) {
		TS_LOG_ERR("Report data size = 0\n");
		retval = -EINVAL;
		goto error_exit;
	}

	if (f54->data_buffer_size < f54->report_size){
		if ((f54->data_buffer_size) && (f54->report_data)) {
			kfree(f54->report_data);
			f54->report_data = NULL;
		}
		f54->report_data = kzalloc(f54->report_size, GFP_KERNEL);
		if (!f54->report_data) {
			TS_LOG_ERR("Failed to alloc mem for data buffer\n");
			f54->data_buffer_size = 0;
			retval = -ENOMEM;
			goto error_exit;
		}
		f54->data_buffer_size = f54->report_size;
	}

	report_times_max = f54->report_size/MAX_I2C_MSG_LENS;
	if(f54->report_size%MAX_I2C_MSG_LENS != 0)
	{
		report_times_max += 1;
	}

	report_index[0] = 0;
	report_index[1] = 0;

	retval = f54->fn_ptr->write(f54->rmi4_data,
			f54->data_base_addr + DATA_REPORT_INDEX_OFFSET,
			report_index,
			sizeof(report_index));
	if (retval < 0) {
		TS_LOG_ERR("Failed to write report data index\n");
		retval = -EINVAL;
		goto error_exit;
	}

	/* Point to the block data about to transfer */
	report_data_temp = f54->report_data;
	TS_LOG_INFO("report_size = %d.\n",f54->report_size);
	TS_LOG_INFO("report_times_max = %d.\n",report_times_max);

	for(i = 0;i < report_times_max;i ++){
		if(i == (report_times_max - 1))
		{
			/* The last time transfer the rest of the block data */
			report_size_temp = f54->report_size%MAX_I2C_MSG_LENS;
			/* Bug:if f54->report_size % MAX_I2C_MSG_LENS == 0,
			the last time transfer data len is MAX_I2C_MSG_LENS.
			*/
			report_size_temp = (report_size_temp != 0) ? report_size_temp : MAX_I2C_MSG_LENS;
		}
		TS_LOG_DEBUG("i = %d,report_size_temp = %d.\n",i,report_size_temp);
		retval = f54->fn_ptr->read(f54->rmi4_data,
			f54->data_base_addr + DATA_REPORT_DATA_OFFSET,
			report_data_temp,
			report_size_temp);
		if (retval < 0) {
			TS_LOG_ERR("%s: Failed to read report data\n",__func__);
			retval = -EINVAL;
			//mutex_unlock(&f54->data_mutex);
			goto error_exit;
		}
		/* Point to the next 256bytes data */
		report_data_temp += MAX_I2C_MSG_LENS;
	}

	/*get report data, one data contains two bytes*/
	for (l = 0; l < f54->report_size; l += 2)
	{
		f54->mmi_buf[l] = f54->report_data[l];
		f54->mmi_buf[l+1] = f54->report_data[l+1];
	}

	retval = NO_ERR;

error_exit:
	return retval;
}

static int synaptics_read_f34(void)
{
	int retval = NO_ERR;
	unsigned char f12_2d_data[14]={0};

	if (SYNAPTICS_S3718 != f54->rmi4_data->synaptics_chip_data->ic_type) {
		retval = f54->fn_ptr->read(f54->rmi4_data,
			f54->f34_fd.query_base_addr + BOOTLOADER_ID_OFFSET,
			f54->bootloader_id,
			sizeof(f54->bootloader_id));
		if (retval < 0) {
			TS_LOG_ERR("Failed to read bootloader ID\n");
			return retval;
		}
	} else {
		retval = f54->fn_ptr->read(f54->rmi4_data,
			f54->f34_fd.query_base_addr + BOOTLOADER_ID_OFFSET_V7,
			f54->bootloader_id,
			sizeof(f54->bootloader_id));
		if (retval < 0) {
			TS_LOG_ERR("Failed to read bootloader ID\n");
			return retval;
		}
	}
	/*V5 V6 version is char data, as '5' '6', V7 is int data, 7*/
	TS_LOG_INFO("bootloader_id[1] = %c, %d\n", f54->bootloader_id[1], f54->bootloader_id[1]);

	switch (f54->bootloader_id[1]) {
		case '5':
			f54->bl_version = V5;
			break;
		case '6':
			f54->bl_version = V6;
			break;
		case 7:
			f54->bl_version = V7;
			break;
		default:
			TS_LOG_ERR("unknown %d %c\n", f54->bootloader_id[1],f54->bootloader_id[1]);
		break;
	}

	if (SYNAPTICS_S3207 != f54->rmi4_data->synaptics_chip_data->ic_type) {
		if (V5 == f54->bl_version) {
			/*get tx and rx value by read register from F11_2D_CTRL77 and F11_2D_CTRL78 */
			retval = f54->fn_ptr->read(f54->rmi4_data, f54->rmi4_data->rmi4_feature.f01_ctrl_base_addr+RX_NUMBER, &f54->rmi4_data->num_of_rx, 1);
			if (retval < 0){
				TS_LOG_ERR("Could not read RX value from 0x%04x\n", f54->rmi4_data->rmi4_feature.f01_ctrl_base_addr + RX_NUMBER);
				return -EINVAL;
			}

			retval = f54->fn_ptr->read(f54->rmi4_data, f54->rmi4_data->rmi4_feature.f01_ctrl_base_addr + TX_NUMBER, &f54->rmi4_data->num_of_tx, 1);
			if (retval < 0){
				TS_LOG_ERR("Could not read TX value from 0x%04x\n", f54->rmi4_data->rmi4_feature.f01_ctrl_base_addr + TX_NUMBER);
				return -EINVAL;
			}
		}
	} else {
		retval = f54->fn_ptr->read(f54->rmi4_data, f54->rmi4_data->rmi4_feature.f11_ctrl_base_addr + RX_NUMBER_S3207, &f54->rmi4_data->num_of_rx, 1);
		if (retval < 0){
			TS_LOG_ERR("Could not read RX value from 0x%04x\n", f54->rmi4_data->rmi4_feature.f11_ctrl_base_addr + RX_NUMBER_S3207);
			return -EINVAL;
		}

		retval = f54->fn_ptr->read(f54->rmi4_data,  f54->rmi4_data->rmi4_feature.f11_ctrl_base_addr + TX_NUMBER_S3207, &f54->rmi4_data->num_of_tx, 1);
		if (retval < 0){
			TS_LOG_ERR("Could not read TX value from 0x%04x\n", f54->rmi4_data->rmi4_feature.f11_ctrl_base_addr + TX_NUMBER_S3207);
			return -EINVAL;
		}
	}
	rawdata_size = (f54->rmi4_data->num_of_tx)*(f54->rmi4_data->num_of_rx)*2+2;
	mmi_buf_size = (f54->rmi4_data->num_of_tx)*(f54->rmi4_data->num_of_rx)*2;

	TS_LOG_INFO("rx = %d, tx = %d, rawdata_size = %d, mmi_buf_size = %d\n", f54->rmi4_data->num_of_rx, f54->rmi4_data->num_of_tx, rawdata_size, mmi_buf_size);
	return NO_ERR;
}

static void Synaptics_test_free_control_mem(void)
{
	struct f54_control control = f54->control;

	kfree(control.reg_7);
	kfree(control.reg_41);
	kfree(control.reg_57);
	kfree(control.reg_88);

	return;
}

static int Synaptics_test_set_controls(void)
{
	unsigned char length;
	unsigned char num_of_sensing_freqs;
	unsigned short reg_addr = f54->control_base_addr;
	struct f54_control *control = &f54->control;

	num_of_sensing_freqs = f54->query.number_of_sensing_frequencies;

	/* control 0 */
	reg_addr += CONTROL_0_SIZE;

	/* control 1 */
	if ((f54->query.touch_controller_family == 0) ||
			(f54->query.touch_controller_family == 1))
		reg_addr += CONTROL_1_SIZE;

	/* control 2 */
	reg_addr += CONTROL_2_SIZE;

	/* control 3 */
	if (f54->query.has_pixel_touch_threshold_adjustment == 1)
		reg_addr += CONTROL_3_SIZE;

	/* controls 4 5 6 */
	if ((f54->query.touch_controller_family == 0) ||
			(f54->query.touch_controller_family == 1))
		reg_addr += CONTROL_4_6_SIZE;

	/* control 7 */
	if (f54->query.touch_controller_family == 1) {
		control->reg_7 = kzalloc(sizeof(*(control->reg_7)),
				GFP_KERNEL);
		if (!control->reg_7)
			goto exit_no_mem;
		control->reg_7->address = reg_addr;
		reg_addr += CONTROL_7_SIZE;
	}

	/* controls 8 9 */
	if ((f54->query.touch_controller_family == 0) ||
			(f54->query.touch_controller_family == 1))
		reg_addr += CONTROL_8_9_SIZE;

	/* control 10 */
	if (f54->query.has_interference_metric == 1)
		reg_addr += CONTROL_10_SIZE;

	/* control 11 */
	if (f54->query.has_ctrl11 == 1)
		reg_addr += CONTROL_11_SIZE;

	/* controls 12 13 */
	if (f54->query.has_relaxation_control == 1)
		reg_addr += CONTROL_12_13_SIZE;

	/* controls 14 15 16 */
	if (f54->query.has_sensor_assignment == 1) {
		reg_addr += CONTROL_14_SIZE;
		reg_addr += CONTROL_15_SIZE * f54->query.num_of_rx_electrodes;
		reg_addr += CONTROL_16_SIZE * f54->query.num_of_tx_electrodes;
	}

	/* controls 17 18 19 */
	if (f54->query.has_sense_frequency_control == 1) {
		reg_addr += CONTROL_17_SIZE * num_of_sensing_freqs;
		reg_addr += CONTROL_18_SIZE * num_of_sensing_freqs;
		reg_addr += CONTROL_19_SIZE * num_of_sensing_freqs;
	}

	/* control 20 */
	reg_addr += CONTROL_20_SIZE;

	/* control 21 */
	if (f54->query.has_sense_frequency_control == 1)
		reg_addr += CONTROL_21_SIZE;

	/* controls 22 23 24 25 26 */
	if (f54->query.has_firmware_noise_mitigation == 1)
		reg_addr += CONTROL_22_26_SIZE;

	/* control 27 */
	if (f54->query.has_iir_filter == 1)
		reg_addr += CONTROL_27_SIZE;

	/* control 28 */
	if (f54->query.has_firmware_noise_mitigation == 1)
		reg_addr += CONTROL_28_SIZE;

	/* control 29 */
	if (f54->query.has_cmn_removal == 1)
		reg_addr += CONTROL_29_SIZE;

	/* control 30 */
	if (f54->query.has_cmn_maximum == 1)
		reg_addr += CONTROL_30_SIZE;

	/* control 31 */
	if (f54->query.has_touch_hysteresis == 1)
		reg_addr += CONTROL_31_SIZE;

	/* controls 32 33 34 35 */
	if (f54->query.has_edge_compensation == 1)
		reg_addr += CONTROL_32_35_SIZE;

	/* control 36 */
	if ((f54->query.curve_compensation_mode == 1) ||
			(f54->query.curve_compensation_mode == 2)) {
		if (f54->query.curve_compensation_mode == 1) {
			length = max(f54->query.num_of_rx_electrodes,
					f54->query.num_of_tx_electrodes);
		} else if (f54->query.curve_compensation_mode == 2) {
			length = f54->query.num_of_rx_electrodes;
		}
		reg_addr += CONTROL_36_SIZE * length;
	}

	/* control 37 */
	if (f54->query.curve_compensation_mode == 2)
		reg_addr += CONTROL_37_SIZE * f54->query.num_of_tx_electrodes;

	/* controls 38 39 40 */
	if (f54->query.has_per_frequency_noise_control == 1) {
		reg_addr += CONTROL_38_SIZE * num_of_sensing_freqs;
		reg_addr += CONTROL_39_SIZE * num_of_sensing_freqs;
		reg_addr += CONTROL_40_SIZE * num_of_sensing_freqs;
	}

	/* control 41 */
	if (f54->query.has_signal_clarity == 1) {
		control->reg_41 = kzalloc(sizeof(*(control->reg_41)),
				GFP_KERNEL);
		if (!control->reg_41)
			goto exit_no_mem;
		control->reg_41->address = reg_addr;
		reg_addr += CONTROL_41_SIZE;
	}

	/* control 42 */
	if (f54->query.has_variance_metric == 1)
		reg_addr += CONTROL_42_SIZE;

	/* controls 43 44 45 46 47 48 49 50 51 52 53 54 */
	if (f54->query.has_multi_metric_state_machine == 1)
		reg_addr += CONTROL_43_54_SIZE;

	/* controls 55 56 */
	if (f54->query.has_0d_relaxation_control == 1)
		reg_addr += CONTROL_55_56_SIZE;

	/* control 57 */
	if (f54->query.has_0d_acquisition_control == 1) {
		control->reg_57 = kzalloc(sizeof(*(control->reg_57)),
				GFP_KERNEL);
		if (!control->reg_57)
			goto exit_no_mem;
		control->reg_57->address = reg_addr;
		reg_addr += CONTROL_57_SIZE;
	}

	/* control 58 */
	if (f54->query.has_0d_acquisition_control == 1)
		reg_addr += CONTROL_58_SIZE;

	/* control 59 */
	if (f54->query.has_h_blank == 1)
		reg_addr += CONTROL_59_SIZE;

	/* controls 60 61 62 */
	if ((f54->query.has_h_blank == 1) ||
			(f54->query.has_v_blank == 1) ||
			(f54->query.has_long_h_blank == 1))
		reg_addr += CONTROL_60_62_SIZE;

	/* control 63 */
	if ((f54->query.has_h_blank == 1) ||
			(f54->query.has_v_blank == 1) ||
			(f54->query.has_long_h_blank == 1) ||
			(f54->query.has_slew_metric == 1) ||
			(f54->query.has_slew_option == 1) ||
			(f54->query.has_noise_mitigation2 == 1))
		reg_addr += CONTROL_63_SIZE;

	/* controls 64 65 66 67 */
	if (f54->query.has_h_blank == 1)
		reg_addr += CONTROL_64_67_SIZE * 7;
	else if ((f54->query.has_v_blank == 1) ||
			(f54->query.has_long_h_blank == 1))
		reg_addr += CONTROL_64_67_SIZE;

	/* controls 68 69 70 71 72 73 */
	if ((f54->query.has_h_blank == 1) ||
			(f54->query.has_v_blank == 1) ||
			(f54->query.has_long_h_blank == 1))
		reg_addr += CONTROL_68_73_SIZE;

	/* control 74 */
	if (f54->query.has_slew_metric == 1)
		reg_addr += CONTROL_74_SIZE;

	/* control 75 */
	if (f54->query.has_enhanced_stretch == 1)
		reg_addr += CONTROL_75_SIZE * num_of_sensing_freqs;

	/* control 76 */
	if (f54->query.has_startup_fast_relaxation == 1)
		reg_addr += CONTROL_76_SIZE;

	/* controls 77 78 */
	if (f54->query.has_esd_control == 1)
		reg_addr += CONTROL_77_78_SIZE;

	/* controls 79 80 81 82 83 */
	if (f54->query.has_noise_mitigation2 == 1)
		reg_addr += CONTROL_79_83_SIZE;

	/* controls 84 85 */
	if (f54->query.has_energy_ratio_relaxation == 1)
		reg_addr += CONTROL_84_85_SIZE;

	/* control 86 */
	if ((f54->query.has_query13 == 1) && (f54->query_13.has_ctrl86 == 1)){
		report_rate_offset = reg_addr - f54->control_base_addr;
		TS_LOG_INFO("no 2 offset = %d, report_rate_offset = %d\n", reg_addr, report_rate_offset);
		reg_addr += CONTROL_86_SIZE;
	}

	/* control 87 */
	if ((f54->query.has_query13 == 1) && (f54->query_13.has_ctrl87 == 1))
		reg_addr += CONTROL_87_SIZE;

	/* control 88 */
	if (f54->query.has_ctrl88 == 1) {
		control->reg_88 = kzalloc(sizeof(*(control->reg_88)),
				GFP_KERNEL);
		if (!control->reg_88)
			goto exit_no_mem;
		control->reg_88->address = reg_addr;
		reg_addr += CONTROL_88_SIZE;
	}

	return 0;

exit_no_mem:
	TS_LOG_ERR("Failed to alloc mem for control registers\n");
	return -ENOMEM;
}

static int Synaptics_test_set_queries(void)
{
	int retval;
	unsigned char offset;
	struct synaptics_rmi4_data *rmi4_data = f54->rmi4_data;

	retval = f54->fn_ptr->read(rmi4_data,
			f54->query_base_addr,
			f54->query.data,
			sizeof(f54->query.data));
	if (retval < 0)
		return retval;
	offset = sizeof(f54->query.data);

	/* query 12 */
	if (f54->query.has_sense_frequency_control == 0)
		offset -= 1;

	/* query 13 */
	if (f54->query.has_query13) {
		retval = f54->fn_ptr->read(rmi4_data,
				f54->query_base_addr + offset,
				f54->query_13.data,
				sizeof(f54->query_13.data));
		if (retval < 0)
			return retval;
		offset += 1;
	}

	/* query 14 */
	if ((f54->query.has_query13) && (f54->query_13.has_ctrl87))
		offset += 1;

	/* query 15 */
	if (f54->query.has_query15) {
		retval = f54->fn_ptr->read(rmi4_data,
				f54->query_base_addr + offset,
				f54->query_15.data,
				sizeof(f54->query_15.data));
		if (retval < 0)
			return retval;
		offset += 1;
	}

	/* query 16 */
	retval = f54->fn_ptr->read(rmi4_data,
			f54->query_base_addr + offset,
			f54->query_16.data,
			sizeof(f54->query_16.data));
	if (retval < 0)
		return retval;
	offset += 1;

	/* query 17 */
	if (f54->query_16.has_query17)
		offset += 1;

	/* query 18 */
	if (f54->query_16.has_ctrl94_query18)
		offset += 1;

	/* query 19 */
	if (f54->query_16.has_ctrl95_query19)
		offset += 1;

	/* query 20 */
	if ((f54->query.has_query15) && (f54->query_15.has_query20))
		offset += 1;

	/* query 21 */
	retval = f54->fn_ptr->read(rmi4_data,
			f54->query_base_addr + offset,
			f54->query_21.data,
			sizeof(f54->query_21.data));
	if (retval < 0)
		return retval;

	return 0;
}
static int match_module_name(const char* module_name)
{
	TS_LOG_INFO("%s: module_name = %s,product_name=%s\n", __func__, module_name,g_ts_data.product_name);
	if(strcmp(g_ts_data.product_name,"chm") == 0) {
		if (strcmp(module_name, "oflim") == 0){
			RawCapUpperLimit = RawCapUpperLimit_oflim_chm;
			RawCapLowerLimit = RawCapLowerLimit_oflim_chm;
			RxDeltaCapUpperLimit = RxDeltaCapUpperLimit_oflim_chm;
			RxDeltaCapLowerLimit = RxDeltaCapLowerLimit_oflim_chm;
			TxDeltaCapUpperLimit = TxDeltaCapUpperLimit_oflim_chm;
			TxDeltaCapLowerLimit = TxDeltaCapLowerLimit_oflim_chm;
			return NO_ERR;
		}
		else if (strcmp(module_name, "lensone") == 0){
			RawCapUpperLimit = RawCapUpperLimit_lensone_chm;
			RawCapLowerLimit = RawCapLowerLimit_lensone_chm;
			RxDeltaCapUpperLimit = RxDeltaCapUpperLimit_lensone_chm;
			RxDeltaCapLowerLimit = RxDeltaCapLowerLimit_lensone_chm;
			TxDeltaCapUpperLimit = TxDeltaCapUpperLimit_lensone_chm;
			TxDeltaCapLowerLimit = TxDeltaCapLowerLimit_lensone_chm;
			return NO_ERR;
		}
		else if (strcmp(module_name, "truly") == 0){
			RawCapUpperLimit = RawCapUpperLimit_truly_chm;
			RawCapLowerLimit = RawCapLowerLimit_truly_chm;
			RxDeltaCapUpperLimit = RxDeltaCapUpperLimit_truly_chm;
			RxDeltaCapLowerLimit = RxDeltaCapLowerLimit_truly_chm;
			TxDeltaCapUpperLimit = TxDeltaCapUpperLimit_truly_chm;
			TxDeltaCapLowerLimit = TxDeltaCapLowerLimit_truly_chm;
			return NO_ERR;
		}
		else{
			TS_LOG_ERR("%s: Failed to match module_name \n", __func__);
			return -EINVAL;
		}
	}
}
int synaptics_rmi4_f54_init(struct synaptics_rmi4_data *rmi4_data,const char *module_name)
{
	int retval = -EINVAL;
	bool hasF54 = false;
	bool hasF55 = false;
	bool hasF34 = false;
	unsigned short ii;
	unsigned char page;
	unsigned char intr_count = 0;
	struct synaptics_rmi4_fn_desc rmi_fd;

	if(raw_data_limit_flag){
		retval = match_module_name(module_name);
		if( retval < 0 ){
			retval = -ENOMEM;
			return retval;
		}
	}
	if (synaptics_f54_malloc() != NO_ERR)
		goto exit_free_mem;

	f54->rmi4_data = rmi4_data;
	f54->fn_ptr->read = rmi4_data->i2c_read;
	f54->fn_ptr->write = rmi4_data->i2c_write;

	for (page = 0; page < PAGES_TO_SERVICE; page++) {
		for (ii = PDT_START; ii > PDT_END; ii -= PDT_ENTRY_SIZE) {
			ii |= (page << 8);

			retval = f54->fn_ptr->read(rmi4_data, ii, (unsigned char *)&rmi_fd, sizeof(rmi_fd));
			if (retval < 0) {
				TS_LOG_ERR("i2c read error, page = %d, ii = %d\n", page, ii);
				goto exit_free_mem;
			}

			if (!rmi_fd.fn_number) {
				TS_LOG_INFO("!rmi_fd.fn_number,page=%d,ii=%d\n",page,ii);
				retval = -EINVAL;
				break;
			}

			if (rmi_fd.fn_number == SYNAPTICS_RMI4_F54) {
				hasF54 = true;
				f54->query_base_addr =
					rmi_fd.query_base_addr | (page << 8);
				f54->control_base_addr =
					rmi_fd.ctrl_base_addr | (page << 8);
				f54->data_base_addr =
					rmi_fd.data_base_addr | (page << 8);
				f54->command_base_addr =
					rmi_fd.cmd_base_addr | (page << 8);
				TS_LOG_DEBUG("f54->control_base_addr = 0x%x, f54->data_base_addr = 0x%x, f54->query_base_addr = 0x%x\n", f54->control_base_addr, f54->data_base_addr, f54->query_base_addr);
			} else if (rmi_fd.fn_number == SYNAPTICS_RMI4_F55) {
				hasF55 = true;
				f54->fn55->query_base_addr = rmi_fd.query_base_addr | (page << 8);
				f54->fn55->control_base_addr = rmi_fd.ctrl_base_addr | (page << 8);
			} else if (rmi_fd.fn_number == SYNAPTICS_RMI4_F34) {
				hasF34 = true;
				f54->f34_fd.query_base_addr = rmi_fd.query_base_addr;
				f54->f34_fd.ctrl_base_addr = rmi_fd.ctrl_base_addr;
				f54->f34_fd.data_base_addr = 	rmi_fd.data_base_addr;
			}

			if (hasF54 && hasF55 && hasF34)
				goto found;

			if (!hasF54)
				intr_count += (rmi_fd.intr_src_count & MASK_3BIT);
		}
	}

	TS_LOG_INFO("f54->control_base_addr = 0x%x, f54->data_base_addr = 0x%x\n", f54->control_base_addr, f54->data_base_addr);

	if (!hasF54 || !hasF34) {
		TS_LOG_ERR("Funtion  is not available, hasF54=%d, hasF34 = %d\n", hasF54, hasF34);
		retval = -EINVAL;
		goto exit_free_mem;
	}

found:
#if 0
	f54->intr_reg_num = (intr_count + 7) / 8;
	if (f54->intr_reg_num != 0)
		f54->intr_reg_num -= 1;

	f54->intr_mask = 0;
	intr_offset = intr_count % 8;
	for (ii = intr_offset; ii < ((rmi_fd.intr_src_count & MASK_3BIT) + intr_offset); ii++) {
		f54->intr_mask |= 1 << ii;
	}
#endif
	retval = f54->fn_ptr->read(rmi4_data, f54->query_base_addr, f54->query.data,
			sizeof(f54->query.data));
	if (retval < 0) {
		TS_LOG_ERR("Failed to read query registers\n");
		goto exit_free_mem;
	}

	retval = Synaptics_test_set_queries();
	if (retval < 0) {
		TS_LOG_ERR("Failed to set up f54 queries registers\n");
		goto exit_free_mem;
	}

	retval = Synaptics_test_set_controls();
	if (retval < 0) {
		TS_LOG_ERR("Failed to set up f54 control registers\n");
		goto exit_free_control;
	}

	retval = synaptics_read_f34();
	if (retval) {
		TS_LOG_ERR("Read F34 failed, retval = %d\n", retval);
		goto exit_free_mem;
	}

	f54->mmi_buf = (char *)kzalloc(mmi_buf_size, GFP_KERNEL);
	if (!f54->mmi_buf) {
		TS_LOG_ERR("Failed to alloc mmi_buf\n");
		retval = -ENOMEM;
		goto exit_free_mem;
	}

	f54->rawdatabuf = (int *)kzalloc(rawdata_size*sizeof(int), GFP_KERNEL);
	if (!f54->rawdatabuf) {
		TS_LOG_ERR(" Failed to alloc rawdatabuf\n");
		retval = -ENOMEM;
		goto exit_free_mem;
	}

	return NO_ERR;

exit_free_control:
	Synaptics_test_free_control_mem();

exit_free_mem:
	synaptics_f54_free();
	return retval;
}

