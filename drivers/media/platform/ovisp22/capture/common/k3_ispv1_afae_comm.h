/*
 *  Hisilicon K3 soc camera ISP afae driver header file
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

#ifndef __K3_ISPV1_AFAE_COMM_H__
#define __K3_ISPV1_AFAE_COMM_H__

/* Added for focus module */
#define REG_ISP_SCALE6_SELECT		(0x6502a)

#define REG_ISP_FOCUS_MIN_STAT_HF_NUM		(0x66111)
#define REG_ISP_FOCUS_STAT_THRESHOLD		(0x66112)

#define ISP_FOCUS_BINNING			(1<<2)
#define ISP_FOCUS_NONBINNING		(0<<2)
#define ISP_FOCUS_5X5_WINDOW		(1<<1)
#define ISP_FOCUS_SINGLE_WINDOW	(0<<1)
#define REG_ISP_FOCUS_AFCCTRL0		(0x66100)
#define REG_ISP_FOCUS_AFCCTRL2		(0x66102)
#define REG_ISP_FOCUS_AFCCTRL3		(0x66103)

/*windows definition registers*/

#define ISP_FOCUS_WINMODE_SINGLE	0
#define ISP_FOCUS_WINMODE_5X5		1
#define REG_ISP_FOCUS_WINMODE		(0x1c5b0)

#define ISP_FOCUS_IS_AUTO			1
#define ISP_FOCUS_ISNOT_AUTO		0
#define REG_ISP_FOCUS_IFAUTO		(0x1c5b1)

#define ISP_FOCUS_IS_WEIGHTED           1
#define ISP_FOCUS_ISNOT_WEIGHTED        0
#define REG_ISP_FOCUS_IFWEIGHTED        (0x1c5b2)
#define REG_ISP_FOCUS_ACTIVE_WINID      (0x1c5b3)

/*windows zone definition, include x0,y0,width,height,w1,h1*/
#define REG_ISP_FOCUS_WIN_X0			(0x66104)
#define REG_ISP_FOCUS_WIN_Y0			(0x66106)

#define REG_ISP_FOCUS_WIN_W0			(0x66108)
#define REG_ISP_FOCUS_WIN_H0			(0x6610a)

#define REG_ISP_FOCUS_WIN_W1			(0x6610c)
#define REG_ISP_FOCUS_WIN_H1			(0x6610e)

/*winid is 0-24*/
#define REG_ISP_FOCUS_WEIGHT_LIST(winid)		(0x1c5b4 + (winid) * 2)

/*AF control registers*/
#define REG_ISP_FOCUS_CONTRAST(n)		(0x1ca30 + (n) * 2)

#define REG_ISP_FOCUS_ACTIVE			(0x1cd0a)

#define ISP_FOCUS_VIDEO_MODE		1
#define ISP_FOCUS_SNAPSHOT_MODE	0
#define REG_ISP_FOCUS_MODE			(0x1cd0b)

#define REG_ISP_FOCUS_LOCK_AE			(0x1cd10)

/*motor registers*/
#define REG_ISP_FOCUS_MOTOR_OFFSETINIT			(0x1cca4)
#define REG_ISP_FOCUS_MOTOR_FULLRANGE			(0x1cca6)
#define REG_ISP_FOCUS_MOTOR_MINISTEP			(0x1cca8)
#define REG_ISP_FOCUS_MOTOR_COARSESTEP			(0x1ccaa)
#define REG_ISP_FOCUS_MOTOR_FINESTEP			(0x1ccac)


#define REG_ISP_FOCUS_1STEP_COMEBACK			(0x1ccb1)

#define REG_ISP_FOCUS_MOTOR_FRAMERATE			(0x1ccae)
#define REG_ISP_FOCUS_MOTOR_WAITFRAME			(0x1ccb0)
#define REG_ISP_FOCUS_MOTOR_RESTIME			(0x1ccb2)

#define REG_ISP_FOCUS_MOTOR_CURR				(0x1ccec)
#define REG_ISP_FOCUS_MOTOR_STARTPARTITION			(0x1cdd7)
#define REG_ISP_FOCUS_MOTOR_DRIVEMODE				(0x1cddc)
#define REG_ISP_FOCUS_MOTOR_CALIBRATE				(0x1cddd)

#define REG_ISP_FOCUS_PREMOVE				(0x1cd0e)

#define REG_ISP_FOCUS_IGNORE_AEC_STABLE	(0x1cd04)

/* Reg focus failure position choise: 0-max position(default); 1-infinity. */
#define REG_ISP_FOCUS_FAILURE_POS			(0x1cd05)
#define REG_ISP_FOCUS_FORCE_START			(0x1cd06)

/*VCM registers*/
#define REG_ISP_FOCUS_I2COPTION		(0x1cdc6)
#define REG_ISP_FOCUS_DEVICEID		(0x1cdc7)
#define REG_ISP_FOCUS_MOVELENS_ADDR0		(0x1cdc8)
#define REG_ISP_FOCUS_MOVELENS_ADDR1	(0x1cdca)

#define REG_ISP_FOCUS_BUSY_ADDR		(0x1cdcc)

#define REG_ISP_FOCUS_WIN_NUM		(0x1cdce)
/*num 0-3*/
#define REG_ISP_FOCUS_WIN_LIST(num)		(0x1cdcf+(num))

#define REG_ISP_FOCUS_STATUS		(0x1cdd4)
#define REG_ISP_FOCUS_REDRAW		(0x1cdd5)

/*here these register also can get focus result*/
#define REG_ISP_FOCUS_FRAME_WIDTH		(0x1c774)
#define REG_ISP_FOCUS_FRAME_HEIGHT		(0x1c776)
/*num 0-3*/
#define REG_ISP_FOCUS_FRAME_POSX(num)		(0x1c778+4*(num))
#define REG_ISP_FOCUS_FRAME_POSY(num)		(0x1c77a+4*(num))

/*performance related*/
#define REG_ISP_FOCUS_nT_compare_1x		(0x1cc92)
#define REG_ISP_FOCUS_nT_compare_16x	(0x1cc94)

#define REG_ISP_FOCUS_nT_sad_1x			(0x1cc96)
#define REG_ISP_FOCUS_nT_sad_16x			(0x1cc98)

#define REG_ISP_FOCUS_nT_presad_1x		(0x1cc9a)
#define REG_ISP_FOCUS_nT_presad_16x		(0x1cc9c)

#define REG_ISP_FOCUS_nT_hist_1x			(0x1cc9e)
#define REG_ISP_FOCUS_nT_hist_16x			(0x1cca0)

#define REG_ISP_FOCUS_nT_contrast_diff		(0x1cca2)

/* target Y definitions */
#define DEFAULT_TARGET_Y_LOW			0x2c
#define DEFAULT_TARGET_Y_HIGH			0x4c
#define DEFAULT_TARGET_Y_FLASH		0x30

#define METERING_CWA_WIDTH_PERCENT		60
#define METERING_CWA_HEIGHT_PERCENT	60
#define METERING_SPOT_WIDTH_PERCENT	60
#define METERING_SPOT_HEIGHT_PERCENT	60

#define METERING_AECAGC_WINDOW_PERCENT	85
#define METERING_ROIWIN_BRIGHT_PERCENT	30
#define METERING_ROIWIN_DARK_PERCENT		75
#define MIN_METERING_RAW_WIDTH			80
#define MIN_METERING_RAW_HEIGHT			60
#define MIN_STAT_RAW_WIDTH			120
#define MIN_STAT_RAW_HEIGHT			90
/* AE registers */
#define REG_ISP_CURRENT_Y				(0x1c758)//(0x1c75e)

#define REG_ISP_TARGET_Y				(0x1c5aa)
#define REG_ISP_TARGET_Y_LOW			(0x1c146)
#define REG_ISP_TARGET_Y_LOW_SHORT		(0x1c147)

#define REG_ISP_TARGET_Y_HIGH			(0x1c596)//(0x1c5a0)

#define DEFAULT_FLASH_AEC_FAST_STEP		0x18
#define DEFAULT_FLASH_AEC_SLOW_STEP		0x10
#define DEFAULT_FLASH_AWB_STEP			0x0c

//k3 4.2 update, todo check reg
#define REG_ISP_AWB_STEP		(0x1c184)

#define REG_ISP_SLOW_RANGE			(0x1c148)
#define REG_ISP_SLOW_RANGE_SHORT		(0x1c149)
#define REG_ISP_UNSTABLE2STABLE_RANGE		(0x1c14a)
#define REG_ISP_STABLE2UNSTABLE_RANGE		(0x1c14b)
#define REG_ISP_FAST_STEP			(0x1c14c)
#define REG_ISP_FAST_STEP_SHORT		(0x1c14d)
#define REG_ISP_SLOW_STEP			(0x1c14e)
#define REG_ISP_SLOW_STEP_SHORT		(0x1c14f)

#define REG_ISP_AECAGC_STATWIN_LEFT			(0x66401)
#define REG_ISP_AECAGC_STATWIN_TOP			(0x66403)
#define REG_ISP_AECAGC_STATWIN_RIGHT		(0x66405)
#define REG_ISP_AECAGC_STATWIN_BOTTOM		(0x66407)

#define METERING_AECAGC_WINDOW_PERCENT	85

#define REG_ISP_AECAGC_CENTER_LEFT			(0x66409)
#define REG_ISP_AECAGC_CENTER_LEFT_SHORT	(0x6640b)
#define REG_ISP_AECAGC_CENTER_TOP			(0x6640d)
#define REG_ISP_AECAGC_CENTER_TOP_SHORT	(0x6640f)
#define REG_ISP_AECAGC_CENTER_WIDTH		(0x66411)
#define REG_ISP_AECAGC_CENTER_WIDTH_SHORT	(0x66413)
#define REG_ISP_AECAGC_CENTER_HEIGHT		(0x66415)
#define REG_ISP_AECAGC_CENTER_HEIGHT_SHORT	(0x66417)

/* win:0-12 */
#define REG_ISP_AECAGC_WIN_WEIGHT(num)			(0x6642eL+(num))
#define REG_ISP_AECAGC_WIN_WEIGHT_SHORT(num)	(0x6643bL+(num))

#define REG_ISP_AECAGC_WIN_WEIGHT_SHIFT		(0x6644e)

/* ROI definition */
#define REG_ISP_AECAGC_ROI_LEFT			(0x66419)
#define REG_ISP_AECAGC_ROI_LEFT_SHORT	(0x6641b)
#define REG_ISP_AECAGC_ROI_TOP			(0x6641d)
#define REG_ISP_AECAGC_ROI_TOP_SHORT	(0x6641f)
#define REG_ISP_AECAGC_ROI_RIGHT		(0x66421)
#define REG_ISP_AECAGC_ROI_RIGHT_SHORT	(0x66423)
#define REG_ISP_AECAGC_ROI_BOTTOM		(0x66425)
#define REG_ISP_AECAGC_ROI_BOTTOM_SHORT	(0x66427)

#define REG_ISP_AECAGC_ROI_SHIFT	(0x66429)

#define REG_ISP_AECAGC_ROI_WEIGHT_IN			(0x6642a)
#define REG_ISP_AECAGC_ROI_WEIGHT_OUT			(0x6642b)
#define REG_ISP_AECAGC_ROI_WEIGHT_IN_SHORT		(0x6642c)
#define REG_ISP_AECAGC_ROI_WEIGHT_OUT_SHORT	(0x6642d)

#define REG_ISP_AECAGC_MANUAL_ENABLE			(0x1c174)

#define ISP_WRITESENSOR_ENABLE					(1)
#define ISP_WRITESENSOR_DISABLE					(0)
#define REG_ISP_AECAGC_WRITESENSOR_ENABLE		(0x1c139)

/* 0x1cddf for focus aecagc stable status. 1 for stable, 0 for unstable. */
#define REG_ISP_AECAGC_STABLE	(0x1c60c)//(0x1cddf)



#define YUV_EDGE_STAT_MODE

#define FOCUS_PARAM_JUDGE_BASE_LOW	0x04
#define FOCUS_PARAM_JUDGE_BASE_HIGH	0x10

#define FOCUS_PARAM_ULTRALOW_CONTRAST		0x80
#define FOCUS_PARAM_LOW_CONTRAST			0x140

#define FOCUS_PARAM_JUDGE_ERROR_MINDIFF		0x18
#define FOCUS_PARAM_JUDGE_ERROR_MINSTEPS	0x08
#define FOCUS_PARAM_JUDGE_LOW_CONTRAST		0xC0
#define FOCUS_PARAM_JUDGE_ERROR_LUM			0x04

/* AF from one stage to another, should hold some frames first */
#define FOCUS_PARAM_STAGE_HOLDING_FRAMES	1

/* 
 * decide Picture CAF first stage should try or not.
 * if current position >= 1/RANGE_OF_TRY and <= (RANGE_OF_TRY - 1)/RANGE_OF_TRY
 * Picture CAF should first try.
 */
#define FOCUS_PARAM_RANGE_OF_TRY		5
#define FOCUS_PARAM_STAT_THRESHOLD_PERCENT	95

/* AF difference compare ratio or var definitions */
#define FOCUS_PARAM_COMPARE_RATIO_CONTRAST	3
#define FOCUS_PARAM_COMPARE_RATIO_LUM			3
#define FOCUS_PARAM_COMPARE_RATIO_AE			4
#define FOCUS_PARAM_COMPARE_RATIO_AWB		10
#define FOCUS_PARAM_COMPARE_DIFF_XYZ			0x28

#define FOCUS_PARAM_VAR_RATIO_CONTRAST		25 /* more larger, more difficulty to trigger CAF. */
#define FOCUS_PARAM_VAR_RATIO_LUM		16 /* more larger, more difficulty to trigger CAF. */
#define FOCUS_PARAM_VAR_DIFF_XYZ		100 /* more small, more difficulty to trigger CAF. */

#define FOCUS_PARAM_MIN_TRIGGER_LUM	0xc /* minimum lum CAF can trigger. */

#define FOCUS_PARAM_MIN_TRIGGER_CONTRAST_DIFF	4 /* minimum contrast diff CAF will trigger. */
#define FOCUS_PARAM_MIN_TRIGGER_LUM_DIFF	4 /* minimum lum diff CAF will trigger. */

/* if unpeace caused by Gsensor more than XX seconds, force VCM go to infinite */
#define FOCUS_PARAM_GOTO_INFINITE_TIMEOUT	2000

#define CAF_STAT_COMPARE_START_FRAME		2
#define CAF_STAT_COMPARE_END_FRAME			6
#define CAF_STAT_COMPARE_FRAMES \
	(CAF_STAT_COMPARE_END_FRAME - CAF_STAT_COMPARE_START_FRAME + 1)

#define CAF_STAT_SKIP_FRAME		15

#define CAF_STAT_FRAME			6
#define CAF_STAT_FRAME_LOW		4

#define FOCUS_PARAM_LARGE_STRIDE_BASE				0x10

/* if focus RECT size is large than this value, edge calc will use coarse flag. */
#define FOCUS_PARAM_EDGE_CALC_COARSE_SIZE		(1280 * 720)

#define FOCUS_PARAM_ASSISTANT_AF_LUMTH_1X		0x10
#define FOCUS_PARAM_ASSISTANT_AF_LUMTH_9X		0x30
#define FOCUS_PARAM_ASSISTANT_AF_GAINTH_HIGH	0xA0

#define FOCUS_PARAM_MIN_HEIGHT_RATIO	5

#define FOCUS_PARAM_CAF_RESTART_DIFF_XYZ		0x40

#define FLASH_TEST_MAX_COUNT	30
#define FLASH_CAP_RAW_OVER_EXPO	0xe0
#define FLASH_PREFLASH_LOWLIGHT_TH	0x20
#define FLASH_PREVIEW_LOWCT_TH	0x140

#define ISP_LUM_WIN_WIDTH_NUM	8
#define ISP_LUM_WIN_HEIGHT_NUM	6

#define MIN_CONTRAST_INIT			1000000
#define MIN_STEP_NEEDED				7
#define CONTRAST_RATIO				2
#define CONTRAST_THRESHOLD_PERCENT	90
#define CAF_LARGE_FOCUS_WIN_TH		1
#define AF_LARGE_FOCUS_WIN_TH		3
#define CONTRAST_TH_FOR_SMALL_WIN	500
#define CONTRAST_TH_FOR_LARGE_WIN	600
#define NORMAL_RECT_SIZE			156

/* struct definition */
typedef enum _METERING_STATWIN_MODE {
	METERING_STATWIN_NORMAL = 0,
	METERING_STATWIN_ENHANCE_DARK,
	METERING_STATWIN_ENHANCE_BRIGHT,
} METERING_STATWIN_MODE;
typedef enum {
	FOCUS_STATE_STOPPED = 0,
	FOCUS_STATE_CAF_PREPARING,
	FOCUS_STATE_CAF_DETECTING,
	FOCUS_STATE_CAF_RUNNING,
	FOCUS_STATE_AF_PREPARING,
	FOCUS_STATE_AF_RUNNING,
	FOCUS_STATE_S1_ABORT,
	FOCUS_STATE_MAX,
} focus_state_e;

typedef enum {
	CAMERA_AUTO_SNAPSHOT_MODE = 0,
	CAMERA_SINGLE_SNAPSHOT_MODE,
	CAMERA_WEIGHTED_SNAPSHOT_MODE,
	CAMERA_VIDEO_SERVO_MODE,
} camera_af_mode;

typedef enum {
	FOCUS_SCHEDULE_CASE_AF_MOVE = 0,
	FOCUS_SCHEDULE_CASE_CAF_PICTURE_DETECT,
	FOCUS_SCHEDULE_CASE_CAF_PICTURE_MOVE,

	FOCUS_SCHEDULE_CASE_CAF_VIDEO_DETECT,
	FOCUS_SCHEDULE_CASE_CAF_VIDEO_MOVE,

	FOCUS_SCHEDULE_CASE_AF_HOLDING,

	FOCUS_SCHEDULE_CASE_VAF_MOVE,
	FOCUS_SCHEDULE_CASE_AF_FAST_SHOOT,
} focus_schedule_case;

#define VCAF_RUN_RETRY_COUNT_MAX		100

typedef enum {
	AF_RUN_DIRECTION_BACKWARD = -1,
	AF_RUN_DIRECTION_FORWARD = 1,
} af_run_direction;

typedef enum {
	AF_RUN_STAGE_PREPARE = 0,
	AF_RUN_STAGE_PREPARE_POST,
	AF_RUN_STAGE_TRY,
	AF_RUN_STAGE_TRY_POST,
	AF_RUN_STAGE_COARSE,
	AF_RUN_STAGE_COARSE_POST,
	AF_RUN_STAGE_FINE,
	AF_RUN_STAGE_END,

	VCAF_RUN_STAGE_PREPARE,
	VCAF_RUN_STAGE_STARTUP,
	VCAF_RUN_STAGE_TRY,
	VCAF_RUN_STAGE_TRYREWIND,
	VCAF_RUN_STAGE_FORWARD,
	VCAF_RUN_STAGE_REWIND,

	AF_RUN_STAGE_BREAK,
} af_run_stage;

typedef enum {
	FOCUS_POSITION_PART_LEFT = 0,
	FOCUS_POSITION_PART_CENTER_LEFT,
	FOCUS_POSITION_PART_CENTER_RIGHT,
	FOCUS_POSITION_PART_RIGHT,
} focus_position_e;

typedef enum {
	AF_CODE_STEP_COARSE = 0,
	AF_CODE_STEP_FINE,
	AF_CODE_STEP_VIDEO,
} af_code_step;

typedef enum {
	CAF_DETECT_RESULT_NONE = 0,
	CAF_DETECT_RESULT_TRIGGER,
	CAF_DETECT_RESULT_INFINITE,
	CAF_DETECT_RESULT_NOISE,
} caf_detect_result;

typedef enum {
	CAF_FORCESTART_CLEAR = 0, /* clear force start all bits */
	CAF_FORCESTART_FORCEWAIT = 0x0f00, /* force start: should wait peace */
	CAF_FORCESTART_FORCE = 0xf000, /* force start: do not need wait peace */
} caf_forcestart_type;

typedef enum {
	CAMERA_FALSE = 0,
	CAMERA_TRUE,
}camera_bool_e;
#endif /*__K3_ISPV1_AFAE_H__ */
/********************************* END ****************************************/
