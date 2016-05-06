#include "huawei_touchscreen_algo.h"
#include <linux/ktime.h>


static struct timespec curr_time[FILTER_GLOVE_NUMBER] = {{0,0}};

static struct timespec pre_finger_time[FILTER_GLOVE_NUMBER] = {{0,0}};

static int touch_pos_x[FILTER_GLOVE_NUMBER] = {-1, -1, -1, -1};
static int touch_pos_y[FILTER_GLOVE_NUMBER] = {-1, -1, -1, -1};
static enum TP_state_machine  touch_state = INIT_STATE;

static int filter_illegal_glove(u8 n_finger, struct ts_fingers *in_info)
{
	u8 report_flag = 0;
	long interval_time;
	u8 new_mode;
	int x = in_info->fingers[n_finger].x;
	int y = in_info->fingers[n_finger].y;
	new_mode = in_info->fingers[n_finger].status;

	if (new_mode == TP_FINGER) { /*the new interrupt is a finger signal*/
		touch_state = FINGER_STATE;
		report_flag = 1;
	} else if ((new_mode == TP_GLOVE) || (new_mode == TP_STYLUS)) { /*the new interrupt is a glove signal.*/
		switch (touch_state) {
			case INIT_STATE:
				report_flag = 1;
				touch_state = GLOVE_STATE;
				break;

			case FINGER_STATE:
				ktime_get_ts(&curr_time[n_finger]);
				interval_time = (curr_time[n_finger].tv_sec - pre_finger_time[n_finger].tv_sec)*1000
					+ (curr_time[n_finger].tv_nsec - pre_finger_time[n_finger].tv_nsec)/1000000;
				if (interval_time > 0 && interval_time <= FINGER_REL_TIME) {
					ktime_get_ts(&pre_finger_time[n_finger]);
				} else {
					touch_state = ZERO_STATE;
				}
				break;

			case ZERO_STATE:
				if ((touch_pos_x[n_finger] == -1) && (touch_pos_y[n_finger] == -1)) {
					touch_pos_x[n_finger] = x;
					touch_pos_y[n_finger] = y;
				} else {
					if (((touch_pos_x[n_finger] - x)*(touch_pos_x[n_finger] - x)
						+ (touch_pos_y[n_finger] - y)*(touch_pos_y[n_finger] - y))
						>= (PEN_MOV_LENGTH * PEN_MOV_LENGTH)) {
						touch_state = GLOVE_STATE;
					}
				}
				break;

			case GLOVE_STATE:
				report_flag = 1;
				break;

			default:
				TS_LOG_ERR("error: touch_state = %d\n", touch_state);
				break;
		}
	}else {
		TS_LOG_ERR("error:cur_mode=%d\n", new_mode);
		report_flag = 1;
	}

	return report_flag;
}


int ts_algo_t2(struct ts_device_data *dev_data, struct ts_fingers *in_info, struct ts_fingers *out_info)
{
	int index;
	int id = 0;

	for(index = 0, id = 0; index < TS_MAX_FINGER; index++, id++) {
		if (in_info->cur_finger_number == 0) {
			out_info->fingers[0].status = TS_FINGER_RELEASE;
			if (id >= 1)
				out_info->fingers[id].status = 0;
		} else {
			if ((in_info->fingers[index].x != 0) ||(in_info->fingers[index].y != 0)) {
				out_info->fingers[id].x = in_info->fingers[index].x;
				out_info->fingers[id].y = in_info->fingers[index].y;
				out_info->fingers[id].pressure = in_info->fingers[index].pressure;
				out_info->fingers[id].status = TS_FINGER_PRESS;
			} else
				out_info->fingers[id].status = 0;
		}
	}

	out_info->gesture_wakeup_value = in_info->gesture_wakeup_value;
	out_info->special_button_key = in_info->special_button_key;
	out_info->special_button_flag = in_info->special_button_flag;

	return NO_ERR;
}


int ts_algo_t1(struct ts_device_data *dev_data, struct ts_fingers *in_info, struct ts_fingers *out_info)
{
	int index;
	int id;

	for(index = 0, id = 0; index < TS_MAX_FINGER; index++, id++) {
		if (in_info->cur_finger_number == 0) {
			if (index < FILTER_GLOVE_NUMBER) {
				touch_pos_x[index] = -1;
				touch_pos_y[index] = -1;
				if (touch_state == FINGER_STATE) {/*this is a finger release*/
				 	ktime_get_ts(&pre_finger_time[index]);
				}
			}
			out_info->fingers[0].status = TS_FINGER_RELEASE;
			if (id >= 1)
				out_info->fingers[id].status = 0;
		} else {
			if ((in_info->fingers[index].x != 0) ||(in_info->fingers[index].y != 0)) {
				if (index < FILTER_GLOVE_NUMBER) {
					if (filter_illegal_glove(index, in_info) == 0) {
						out_info->fingers[id].status = 0;
					} else {
						out_info->fingers[id].x = in_info->fingers[index].x;
						out_info->fingers[id].y = in_info->fingers[index].y;
						out_info->fingers[id].pressure = in_info->fingers[index].pressure;
						out_info->fingers[id].status = TS_FINGER_PRESS;
					}
				} else {
					out_info->fingers[id].x = in_info->fingers[index].x;
					out_info->fingers[id].y = in_info->fingers[index].y;
					out_info->fingers[id].pressure = in_info->fingers[index].pressure;
					out_info->fingers[id].status = TS_FINGER_PRESS;
				}
			} else
				out_info->fingers[id].status = 0;
		}
	}

	out_info->gesture_wakeup_value = in_info->gesture_wakeup_value;
	out_info->special_button_key = in_info->special_button_key;
	out_info->special_button_flag = in_info->special_button_flag;

	return NO_ERR;
}

struct ts_algo_func ts_algo_f1=
{
	.algo_name = "ts_algo_f1",
	.chip_algo_func = ts_algo_t1,
};

struct ts_algo_func ts_algo_f2 =
{
	.algo_name = "ts_algo_f2",
	.chip_algo_func = ts_algo_t2,
};

int ts_register_algo_func(struct ts_device_data *chip_data)
{
	int retval = 0;

	retval = register_algo_func(chip_data, &ts_algo_f1);	//put algo_f1 into list contained in chip_data, named algo_t1
	if (retval < 0) {
		TS_LOG_ERR("alog 1 failed, retval = %d\n", retval);
		return retval;
	}

	retval = register_algo_func(chip_data, &ts_algo_f2);	//put algo_f2 into list contained in chip_data, named algo_t2
	if (retval < 0) {
		TS_LOG_ERR("alog 2 failed, retval = %d\n", retval);
		return retval;
	}

	return retval;
}
